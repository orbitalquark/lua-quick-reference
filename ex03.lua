-- Example 3. Numerical antiderivative (integral) function
local function F(f, dx)
  dx = dx or 1e-4
  -- Trapezoidal numeric integration function that uses
  -- upvalues 'f' and 'dx'.
  return function(b)
    local sum, a = 0, 0
    for x = a, b, dx do
      sum = sum + (f(x) + f(x + dx)) / 2 * dx
    end
    return sum
  end
end
-- x2 = ∫ 2x dx
local x2 = F(function(x) return 2 * x end)
-- x2(0), x2(1), x2(2), x2(3) gives approx. 0, 1, 4, 9

--8<----------------------------------------------------------------------------
print(x2(0), x2(1), x2(2), x2(3))
--8<----------------------------------------------------------------------------
