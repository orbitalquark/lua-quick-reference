-- Example 10. Control global variable access and assignment
setmetatable(_G, {
  __index = function(t, key)
    local errmsg = "Unknown global '%s'"
    error(string.format(errmsg, key))
  end,
  __newindex = function(t, key, value)
    local errmsg = "Attempt to create global '%s'. \z
                    Use rawset() instead."
    error(string.format(errmsg, key))
  end
})

--8<----------------------------------------------------------------------------
xpcall(function() print(x) end, print)
xpcall(function() x = 1 end, print)
--8<----------------------------------------------------------------------------
