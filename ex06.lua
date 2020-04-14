-- Example 6. Processing a file
local filenames = { --[[ list of filenames... ]] }
--8<----------------------------------------------------------------------------
filenames = {'/usr/share/dict/words'}
--8<----------------------------------------------------------------------------
for i = 1, #filenames do
  local f <close> = io.open(filenames[i])
  if f then
    --8<------------------------------------------------------------------------
    local n = select(2, f:read('a'):gsub('\n', '\n'))
    print(n .. ' words')
    --8<------------------------------------------------------------------------
    --[[ process file... ]]
  end
end
