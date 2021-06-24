<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) "prime numbers: " fmt

#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/prime_numbers.h>
#समावेश <linux/slab.h>

#घोषणा biपंचांगap_size(nbits) (BITS_TO_LONGS(nbits) * माप(अचिन्हित दीर्घ))

काष्ठा primes अणु
	काष्ठा rcu_head rcu;
	अचिन्हित दीर्घ last, sz;
	अचिन्हित दीर्घ primes[];
पूर्ण;

#अगर BITS_PER_LONG == 64
अटल स्थिर काष्ठा primes small_primes = अणु
	.last = 61,
	.sz = 64,
	.primes = अणु
		BIT(2) |
		BIT(3) |
		BIT(5) |
		BIT(7) |
		BIT(11) |
		BIT(13) |
		BIT(17) |
		BIT(19) |
		BIT(23) |
		BIT(29) |
		BIT(31) |
		BIT(37) |
		BIT(41) |
		BIT(43) |
		BIT(47) |
		BIT(53) |
		BIT(59) |
		BIT(61)
	पूर्ण
पूर्ण;
#या_अगर BITS_PER_LONG == 32
अटल स्थिर काष्ठा primes small_primes = अणु
	.last = 31,
	.sz = 32,
	.primes = अणु
		BIT(2) |
		BIT(3) |
		BIT(5) |
		BIT(7) |
		BIT(11) |
		BIT(13) |
		BIT(17) |
		BIT(19) |
		BIT(23) |
		BIT(29) |
		BIT(31)
	पूर्ण
पूर्ण;
#अन्यथा
#त्रुटि "unhandled BITS_PER_LONG"
#पूर्ण_अगर

अटल DEFINE_MUTEX(lock);
अटल स्थिर काष्ठा primes __rcu *primes = RCU_INITIALIZER(&small_primes);

अटल अचिन्हित दीर्घ selftest_max;

अटल bool slow_is_prime_number(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ y = पूर्णांक_वर्ग_मूल(x);

	जबतक (y > 1) अणु
		अगर ((x % y) == 0)
			अवरोध;
		y--;
	पूर्ण

	वापस y == 1;
पूर्ण

अटल अचिन्हित दीर्घ slow_next_prime_number(अचिन्हित दीर्घ x)
अणु
	जबतक (x < अच_दीर्घ_उच्च && !slow_is_prime_number(++x))
		;

	वापस x;
पूर्ण

अटल अचिन्हित दीर्घ clear_multiples(अचिन्हित दीर्घ x,
				     अचिन्हित दीर्घ *p,
				     अचिन्हित दीर्घ start,
				     अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ m;

	m = 2 * x;
	अगर (m < start)
		m = roundup(start, x);

	जबतक (m < end) अणु
		__clear_bit(m, p);
		m += x;
	पूर्ण

	वापस x;
पूर्ण

अटल bool expand_to_next_prime(अचिन्हित दीर्घ x)
अणु
	स्थिर काष्ठा primes *p;
	काष्ठा primes *new;
	अचिन्हित दीर्घ sz, y;

	/* Betअक्रम's Postulate (or Chebyshev's theorem) states that अगर n > 3,
	 * there is always at least one prime p between n and 2n - 2.
	 * Equivalently, अगर n > 1, then there is always at least one prime p
	 * such that n < p < 2n.
	 *
	 * http://mathworld.wolfram.com/Bertअक्रमsPostulate.hपंचांगl
	 * https://en.wikipedia.org/wiki/Bertअक्रम's_postulate
	 */
	sz = 2 * x;
	अगर (sz < x)
		वापस false;

	sz = round_up(sz, BITS_PER_LONG);
	new = kदो_स्मृति(माप(*new) + biपंचांगap_size(sz),
		      GFP_KERNEL | __GFP_NOWARN);
	अगर (!new)
		वापस false;

	mutex_lock(&lock);
	p = rcu_dereference_रक्षित(primes, lockdep_is_held(&lock));
	अगर (x < p->last) अणु
		kमुक्त(new);
		जाओ unlock;
	पूर्ण

	/* Where memory permits, track the primes using the
	 * Sieve of Eratosthenes. The sieve is to हटाओ all multiples of known
	 * primes from the set, what reमुख्यs in the set is thereक्रमe prime.
	 */
	biपंचांगap_fill(new->primes, sz);
	biपंचांगap_copy(new->primes, p->primes, p->sz);
	क्रम (y = 2UL; y < sz; y = find_next_bit(new->primes, sz, y + 1))
		new->last = clear_multiples(y, new->primes, p->sz, sz);
	new->sz = sz;

	BUG_ON(new->last <= x);

	rcu_assign_poपूर्णांकer(primes, new);
	अगर (p != &small_primes)
		kमुक्त_rcu((काष्ठा primes *)p, rcu);

unlock:
	mutex_unlock(&lock);
	वापस true;
पूर्ण

अटल व्योम मुक्त_primes(व्योम)
अणु
	स्थिर काष्ठा primes *p;

	mutex_lock(&lock);
	p = rcu_dereference_रक्षित(primes, lockdep_is_held(&lock));
	अगर (p != &small_primes) अणु
		rcu_assign_poपूर्णांकer(primes, &small_primes);
		kमुक्त_rcu((काष्ठा primes *)p, rcu);
	पूर्ण
	mutex_unlock(&lock);
पूर्ण

/**
 * next_prime_number - वापस the next prime number
 * @x: the starting poपूर्णांक क्रम searching to test
 *
 * A prime number is an पूर्णांकeger greater than 1 that is only भागisible by
 * itself and 1.  The set of prime numbers is computed using the Sieve of
 * Eratoshenes (on finding a prime, all multiples of that prime are हटाओd
 * from the set) enabling a fast lookup of the next prime number larger than
 * @x. If the sieve fails (memory limitation), the search falls back to using
 * slow trial-भागison, up to the value of अच_दीर्घ_उच्च (which is reported as the
 * final prime as a sentinel).
 *
 * Returns: the next prime number larger than @x
 */
अचिन्हित दीर्घ next_prime_number(अचिन्हित दीर्घ x)
अणु
	स्थिर काष्ठा primes *p;

	rcu_पढ़ो_lock();
	p = rcu_dereference(primes);
	जबतक (x >= p->last) अणु
		rcu_पढ़ो_unlock();

		अगर (!expand_to_next_prime(x))
			वापस slow_next_prime_number(x);

		rcu_पढ़ो_lock();
		p = rcu_dereference(primes);
	पूर्ण
	x = find_next_bit(p->primes, p->last, x + 1);
	rcu_पढ़ो_unlock();

	वापस x;
पूर्ण
EXPORT_SYMBOL(next_prime_number);

/**
 * is_prime_number - test whether the given number is prime
 * @x: the number to test
 *
 * A prime number is an पूर्णांकeger greater than 1 that is only भागisible by
 * itself and 1. Internally a cache of prime numbers is kept (to speed up
 * searching क्रम sequential primes, see next_prime_number()), but अगर the number
 * falls outside of that cache, its primality is tested using trial-भागison.
 *
 * Returns: true अगर @x is prime, false क्रम composite numbers.
 */
bool is_prime_number(अचिन्हित दीर्घ x)
अणु
	स्थिर काष्ठा primes *p;
	bool result;

	rcu_पढ़ो_lock();
	p = rcu_dereference(primes);
	जबतक (x >= p->sz) अणु
		rcu_पढ़ो_unlock();

		अगर (!expand_to_next_prime(x))
			वापस slow_is_prime_number(x);

		rcu_पढ़ो_lock();
		p = rcu_dereference(primes);
	पूर्ण
	result = test_bit(x, p->primes);
	rcu_पढ़ो_unlock();

	वापस result;
पूर्ण
EXPORT_SYMBOL(is_prime_number);

अटल व्योम dump_primes(व्योम)
अणु
	स्थिर काष्ठा primes *p;
	अक्षर *buf;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);

	rcu_पढ़ो_lock();
	p = rcu_dereference(primes);

	अगर (buf)
		biपंचांगap_prपूर्णांक_to_pagebuf(true, buf, p->primes, p->sz);
	pr_info("primes.{last=%lu, .sz=%lu, .primes[]=...x%lx} = %s\n",
		p->last, p->sz, p->primes[BITS_TO_LONGS(p->sz) - 1], buf);

	rcu_पढ़ो_unlock();

	kमुक्त(buf);
पूर्ण

अटल पूर्णांक selftest(अचिन्हित दीर्घ max)
अणु
	अचिन्हित दीर्घ x, last;

	अगर (!max)
		वापस 0;

	क्रम (last = 0, x = 2; x < max; x++) अणु
		bool slow = slow_is_prime_number(x);
		bool fast = is_prime_number(x);

		अगर (slow != fast) अणु
			pr_err("inconsistent result for is-prime(%lu): slow=%s, fast=%s!\n",
			       x, slow ? "yes" : "no", fast ? "yes" : "no");
			जाओ err;
		पूर्ण

		अगर (!slow)
			जारी;

		अगर (next_prime_number(last) != x) अणु
			pr_err("incorrect result for next-prime(%lu): expected %lu, got %lu\n",
			       last, x, next_prime_number(last));
			जाओ err;
		पूर्ण
		last = x;
	पूर्ण

	pr_info("%s(%lu) passed, last prime was %lu\n", __func__, x, last);
	वापस 0;

err:
	dump_primes();
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __init primes_init(व्योम)
अणु
	वापस selftest(selftest_max);
पूर्ण

अटल व्योम __निकास primes_निकास(व्योम)
अणु
	मुक्त_primes();
पूर्ण

module_init(primes_init);
module_निकास(primes_निकास);

module_param_named(selftest, selftest_max, uदीर्घ, 0400);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL");
