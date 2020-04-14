-- Example 19. Obtain a file's size before processing it

--8<----------------------------------------------------------------------------
local filename = '/home/mitchell/code/textadept/init.lua'
--8<----------------------------------------------------------------------------

local f = io.open(filename, "r")
local size = f:seek("end")
f:seek("set") -- restore position to beginning of file

--8<----------------------------------------------------------------------------
print(size)
--8<----------------------------------------------------------------------------
