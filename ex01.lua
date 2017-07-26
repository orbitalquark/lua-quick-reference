-- Example 1. Sieve of Eratosthenes
function sieve(n)
  -- Construct initial {2..n} table.
  local is_prime = {}
  for i = 2, n do
    is_prime[i] = true
  end
  -- Strike out all existing multiples of primes.
  for i = 2, math.sqrt(n) do
    if is_prime[i] then
      for j = i^2, n, i do
        is_prime[j] = false
      end
    end
  end
  -- Construct the final primes list.
  local primes = {}
  for i = 2, n do
    if is_prime[i] then
      primes[#primes + 1] = i
    end
  end
  return primes
end

--8<----------------------------------------------------------------------------
print(table.unpack(sieve(30)))
--8<----------------------------------------------------------------------------
