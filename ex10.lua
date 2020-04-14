-- Example 9. Control global variable access and assignment
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
print(x)
x = 1
--8<----------------------------------------------------------------------------
