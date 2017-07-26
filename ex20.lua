-- Example 20. Fetch the contents of a directory

--8<----------------------------------------------------------------------------
local dir = '/home/mitchell/code/textadept/'
--8<----------------------------------------------------------------------------

local filenames = {}
local p = io.popen("ls -1 " .. dir) -- or "dir /B "
for filename in p:lines() do
  filenames[#filenames + 1] = filename
end

--8<----------------------------------------------------------------------------
for i = 1, #filenames do
  print(filenames[i])
end
--8<----------------------------------------------------------------------------
