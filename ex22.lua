-- Example 21. Compute a date 90 days in the future
local time = os.date("*t") -- e.g. 01 May 2017
time.day = time.day + 90
local future = os.time(time)
os.date("%d %b %Y", future) -- e.g. 30 Jul 2017

--8<----------------------------------------------------------------------------
print(os.date("%d %b %Y", future))
--8<----------------------------------------------------------------------------
