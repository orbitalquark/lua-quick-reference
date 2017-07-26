-- Example 14. Iterate over a table in order by string keys
-- Create the table to be iterated over.
local t = {a = 1, b = 2, c = 3, z = 26}
-- Create intermediate list of keys and sort it.
local keys = {}
for k, v in pairs(t) do
  keys[#keys + 1] = k
end
table.sort(keys)
-- Now iterate in key order.
for _, k in ipairs(keys) do
  local v = t[k]
  --[[ process v ]]
  --8<--------------------------------------------------------------------------
  print(k, v)
  --8<--------------------------------------------------------------------------
end
