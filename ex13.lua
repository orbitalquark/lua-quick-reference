-- Example 13. Simple URL parser
function urlparse(url)
  -- Decode escapes like "%5C" -> "\".
  url = url:gsub("%%(%x%x)", function(c)
    return string.char(tonumber(c, 16))
  end)
  -- Parse out URL parts.
  local patt = "^([^:]+)://([^/]+)(.*)$"
  local scheme, host_part, rest = url:match(patt)
  local host, port = host_part:match("^([^:]+):?(%d*)")
  local path, query = rest:match("^([^?]*)%??(.*)$")
  local parts = {}
  for part in query:gmatch("[^&]+") do
    local k, v = part:match("^([^=]+)=(.*)$")
    parts[k] = v
  end
  -- Return parsed parts in a table.
  return {
    scheme = scheme,
    host = host, port = tonumber(port) or 80,
    path = path, query = parts
  }
end
urlparse("http://www.example.com/path?key=value")
-- results in:
-- {scheme = "http", host = "www.example.com",
--  port = 80, path = "/path", query = {key = "value"}}

--8<----------------------------------------------------------------------------
for k, v in pairs(urlparse("http://www.example.com/path?key=value")) do
  if type(v) ~= 'table' then
    print(k, v)
  else
    print(k)
    for k2, v2 in pairs(v) do print('', k2, v2) end
  end
end
--8<----------------------------------------------------------------------------
