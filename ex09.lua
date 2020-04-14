-- Example 8. Define, load, and use a Lua module.
-- File "trig.lua".
local M = {}
-- Radians mode.
M.rad = {
  sin = math.sin,
  cos = math.cos,
  tan = math.tan,
}
-- Degrees mode.
M.deg = {
  sin = function(x) return math.sin(math.rad(x)) end,
  cos = function(x) return math.cos(math.rad(x)) end,
  tan = function(x) return math.tan(math.rad(x)) end
}

--8<----------------------------------------------------------------------------
if false then
--8<----------------------------------------------------------------------------
return M
--8<----------------------------------------------------------------------------
end
package.loaded['trig'] = M
--8<----------------------------------------------------------------------------

-- Program code.
local trig = require("trig").deg
trig.sin(30) -- results in 0.5
trig = require("trig").rad
trig.sin(math.pi / 6) -- also results in 0.5

--8<----------------------------------------------------------------------------
print(require('trig').deg.sin(30))
print(require('trig').rad.sin(math.pi / 6))
--8<----------------------------------------------------------------------------
