-- Example 5. Overload concatenation for a list
local t1, t2 = {1, 2, 3}, {4, 5, 6}
local mt = {}
function mt.__concat(a, b)
  local t = {}
  -- Add all elements of a to t.
  for i = 1, #a do t[#t + 1] = a[i] end
  -- Add all elements of b to t.
  for i = 1, #b do t[#t + 1] = b[i] end
  return t
end
setmetatable(t1, mt)
local t3 = t1 .. t2 -- results in {1, 2, 3, 4, 5, 6}

--8<----------------------------------------------------------------------------
print(table.unpack(t3))
--8<----------------------------------------------------------------------------
