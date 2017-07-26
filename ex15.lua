-- Example 15. Pretty print a table

--8<----------------------------------------------------------------------------
t = {a = 1, b = 2, c = 3}
--8<----------------------------------------------------------------------------

-- Print something like "{a = 1, b = 2, c = 3}".
local items = {}
for k, v in pairs(t) do
  items[#items + 1] = string.format("%s = %s", k, v)
end
table.sort(items)
print(string.format("{%s}", table.concat(items, ", ")))
