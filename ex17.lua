-- Example 16. Emulate string.gsub() without captures
-- Returns a thread that, for each instance of a
-- pattern found, yields that match to main thread and
-- substitutes it with the replacement received.
local function gsub(str, patt, init)
  init = init or 1
  return coroutine.create(function()
    local buffer = {} -- for building resultant string
    local s, e = str:find(patt, init)
    while s do
      -- Add substring up to match to result buffer.
      buffer[#buffer + 1] = str:sub(init, s - 1)
      -- Yield match, receive replacement, and add to
      -- result buffer.
      local match = str:sub(s, e)
      local replacement = coroutine.yield(match)
      buffer[#buffer + 1] = replacement
      -- Continue the search.
      init = e + 1
      s, e = str:find(patt, init)
    end
    -- Build and return the final replacement string.
    return table.concat(buffer)
  end)
end
-- Replaces all instances of a pattern in a string by
-- creating a thread that searches within that string
-- and, for each match yielded, produces a suitable
-- replacement.
local function threaded_gsub(str, patt, repl)
  local thread = gsub(str, patt)
  local ok, match = coroutine.resume(thread)
  while coroutine.status(thread) == "suspended" do
    local replacement = --[[ produce from match ]]
    --8<------------------------------------------------------------------------
    match:upper()
    --8<------------------------------------------------------------------------
    ok, match = coroutine.resume(thread, replacement)
  end
  return match -- final resultant string
end

--8<----------------------------------------------------------------------------
print(threaded_gsub('foo', '.'))
--8<----------------------------------------------------------------------------
