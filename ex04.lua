-- Example 4. Function that accepts variable arguments
function handle_event(event_name, ...)
  local f = event_handlers[event_name]
  if f then
    -- Forward all event parameters to the event
    -- handler function.
    return f(...)
  end
end

--8<----------------------------------------------------------------------------
event_handlers = {
  foo = function(...) print('handling foo', ...) end
}
handle_event('foo', 1, 2, 3)
--8<----------------------------------------------------------------------------
