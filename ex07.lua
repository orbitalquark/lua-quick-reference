-- Example 6. Create a read-only table
local t = { --[[ read-only table contents ]] }
t = setmetatable({}, {
  __index = t,
  __newindex = function() error("read-only table") end
})

--8<----------------------------------------------------------------------------
rawset(t,'x', 1)
rawset(t,'y', 2)
print(t.x, t.y)
t.z = 3
--8<----------------------------------------------------------------------------
