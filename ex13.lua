-- Example 12. Save game data in a binary format
-- Saved player data comprises a name, level (1-100),
-- attribute stats (0-255), map xy-coordinate position,
-- and inventory of items. Inventory items each have an
-- id (0-65535) and count (0-255).
local info_fmt = "zI1"
local stats_fmt = "I1I1"
local position_fmt = "ii"
local inventory_item_fmt = "I2I1"
function save_player_data(player)
  -- Generate static player save data.
  local data = {
    info_fmt:pack(player.name, player.level),
    stats_fmt:pack(player.strength, player.defense),
    position_fmt:pack(player.x, player.y),
    string.pack("I1", #player.inventory)
  }
  -- Generate dynamic player save data.
  for i = 1, #player.inventory do
    local item = player.inventory[i]
    data[#data + 1] = string.pack(inventory_item_fmt,
                                  item.id, item.count)
  end
  data = table.concat(data)
  --[[ save data ]]
  --8<--------------------------------------------------------------------------
  return data
  --8<--------------------------------------------------------------------------
end
function load_player_data(player--[[]],data--[[]])
  --[[ read data ]]
  local name, level, stats, x, y, inventory_size, pos
  -- Read static player save data.
  name, level, pos = info_fmt:unpack(data)
  stats = {stats_fmt:unpack(data, pos)}
  x, y, pos = position_fmt:unpack(data, stats[3])
  -- Read dynamic player save data.
  inventory_size, pos = string.unpack("I1", data, pos)
  local inventory = {}
  for i = 1, inventory_size do
    local id, ct
    id, ct, pos = inventory_item_fmt:unpack(data, pos)
    inventory[#inventory + 1] = {id = id, count = ct}
  end
  -- Load player data.
  player.name, player.level = name, level
  player.strength, player.defense = stats[1], stats[2]
  player.x, player.y = x, y
  player.inventory = inventory
end

--8<----------------------------------------------------------------------------
local player = {
  name = 'm', level = 50, strength = 100, defense = 255, x = -1, y = -10,
  inventory = {
    {id = 1, count = 10, name = 'potion'},
    {id = 0, count = 1, name = 'elixir'},
    {id = 2, count = 5, name = 'phoenix down'}
  }
}
local loaded_player = {}
load_player_data(loaded_player, save_player_data(player))
for k, v in pairs(loaded_player) do
  if type(v) ~= 'table' then
    print(k, v)
  else
    print(k)
    for _, item in ipairs(v) do
      print('', item.id, item.count)
    end
  end
end
--8<----------------------------------------------------------------------------
