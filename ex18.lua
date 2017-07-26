-- Example 18. Echo lines matching a Lua pattern

--8<----------------------------------------------------------------------------
local lines = {
  'foo\n',
  '2017/01/01\n',
  'bar\n',
  '2017/02/01\n',
  'baz\n'
}
local i = 0
io.read = function()
  i = i + 1
  return lines[i]
end
--8<----------------------------------------------------------------------------

local date_patt = "%d+/%d+/%d+"
local line = io.read("*L")
while line do
  if line:find(date_patt) then
    io.write(line)
  end
  line = io.read("*L")
end
-- Note: for line in io.lines(io.stdin, "*L") do … end
-- is also valid.
