-- Example 10. Handle string encoding errors

--8<----------------------------------------------------------------------------
filename = '/home/mitchell/code/textadept/init.lua'
iconv = function() error('conversion failed') end
--iconv = function() return 'utf-8' end
--8<----------------------------------------------------------------------------

local encodings = {
  "UTF-8", "UTF-16", "UTF-32", "ASCII", "ISO-8859-1"
}
local f = io.open(filename, "r")
local text = f:read("*a")
f:close()
for i = 1, #encodings do
  -- Attempt to convert file contents to UTF-8.
  local ok, conv = pcall(iconv, text, encodings[i])
  if ok then
    text = conv
    goto encoding_detected
  end
end
error("Could not detect file encoding.")
::encoding_detected::
--[[ process UTF-8-encoded text ]]
