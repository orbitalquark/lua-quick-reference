-- Example 21. Fetch the contents of a directory

--8<----------------------------------------------------------------------------
local dir = '/home/mitchell/code/textadept/'
--8<----------------------------------------------------------------------------

local filenames = {} -- or "dir /B "
local p <close> = io.popen("ls -1 " .. dir)
for filename in p:lines() do
  filenames[#filenames + 1] = filename
end

--8<----------------------------------------------------------------------------
for i = 1, #filenames do
  print(filenames[i])
end
--8<----------------------------------------------------------------------------
