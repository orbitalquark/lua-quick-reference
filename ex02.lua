-- Example 2. Emulating "continue" with goto
local function open_files(filenames)
  for i = 1, #filenames do
    local text
    local f = io.open(filenames[i])
    if f then
      text = f:read("*a")
      if not text then goto continue end -- cannot read
      --8<----------------------------------------------------------------------
      print('opened', filenames[i])
      --8<----------------------------------------------------------------------
    end
    --[[ process text ]]
    ::continue::
  end
end

--8<----------------------------------------------------------------------------
open_files{'/etc/shadow','/etc/fstab'}
--8<----------------------------------------------------------------------------
