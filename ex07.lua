-- Example 7. A sample class for 2-D vector objects
-- Create the vector class object.
local vector = {}
vector.__index = vector
-- Create a new vector with the given components.
function vector.new(x, y)
  local v = {x = x, y = y}
  return setmetatable(v, vector)
end
-- Overload length operator to compute magnitude.
function vector.__len(v)
  return math.sqrt(v.x^2 + v.y^2)
end
-- Overload addition operator to add two vectors.
function vector.__add(v1, v2)
  assert(getmetatable(v1) == getmetatable(v2),
         "vectors expected")
  return vector.new(v1.x + v2.x, v1.y + v2.y)
end
-- Overload subtraction operator to subtract vectors.
function vector.__sub(v1, v2)
  assert(getmetatable(v1) == getmetatable(v2),
         "vectors expected")
  return vector.new(v1.x - v2.x, v1.y - v2.y)
end
-- Overload multiplication operator to compute vector
-- dot product or scale a vector.
function vector.__mul(v1, v2)
  if getmetatable(v1) == getmetatable(v2) then
    return v1.x * v2.x + v1.y * v2.y
  elseif tonumber(v1) or tonumber(v2) then
    local scalar = tonumber(v1) or v2
    local v = not tonumber(v1) and v1 or v2
    return vector.new(scalar * v.x, scalar * v.y)
  else
    error("vectors or scalar and vector expected")
  end
end
-- Normalize a vector in-place.
function vector:normalize()
  local magnitude = #self
  self.x = self.x / magnitude
  self.y = self.y / magnitude
end
-- Overload exponentiation operator to compute angle
-- between vectors.
function vector.__pow(v1, v2)
  assert(getmetatable(v1) == getmetatable(v2),
         "vectors expected")
  return math.acos(v1 * v2 / (#v1 * #v2))
end
-- Return a vector's direction angle from x-axis.
function vector:angle()
  return self ^ vector.new(1, 0)
end
-- Return a vector's string representation.
function vector:__tostring()
  return string.format("<%.3f, %.3f>", self.x, self.y)
end

--8<----------------------------------------------------------------------------
local v1 = vector.new(1, 2)
local v2 = vector.new(-1, 1)
print(v1, #v1)
print(v2, #v2)
print(v1 + v2, v1 - v2)
print(v1 * v2)
print(3 * v2)
print((v1 + v2):angle())
v2:normalize()
print(v2)
--8<----------------------------------------------------------------------------
