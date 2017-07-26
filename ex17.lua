-- Example 17. Generate list permutations
-- Permutes a list by taking each element and
-- recursively re-ordering the remaining elements.
-- For instance, given {1, 2, 3}:
-- Takes 1 and re-orders 2 and 3 (1, 2, 3 and 1, 3, 2).
-- Takes 2 and re-orders 1 and 3 (2, 1, 3 and 2, 3, 1).
-- Takes 3 and re-orders 1 and 2 (3, 1, 2 and 3, 2, 1).
local function permute(list, i)
  i = i or 1
  if i > #list then
    coroutine.yield(list)
  else
    for j = i, #list do
      list[i], list[j] = list[j], list[i]
      permute(list, i + 1)
      list[i], list[j] = list[j], list[i]
    end
  end
end
-- Iterator.
local function permutations(list)
  return coroutine.wrap(function() permute(list) end)
end
for permutation in permutations{1, 2, 3} do
  --[[ process permutation ]]
  --8<--------------------------------------------------------------------------
  print(table.unpack(permutation))
  --8<--------------------------------------------------------------------------
end
