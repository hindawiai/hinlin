<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* tnum: tracked (or tristate) numbers
 *
 * A tnum tracks knowledge about the bits of a value.  Each bit can be either
 * known (0 or 1), or unknown (x).  Arithmetic operations on tnums will
 * propagate the unknown bits such that the tnum result represents all the
 * possible results क्रम possible values of the opeअक्रमs.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/tnum.h>

#घोषणा TNUM(_v, _m)	(काष्ठा tnum)अणु.value = _v, .mask = _mपूर्ण
/* A completely unknown value */
स्थिर काष्ठा tnum tnum_unknown = अणु .value = 0, .mask = -1 पूर्ण;

काष्ठा tnum tnum_स्थिर(u64 value)
अणु
	वापस TNUM(value, 0);
पूर्ण

काष्ठा tnum tnum_range(u64 min, u64 max)
अणु
	u64 chi = min ^ max, delta;
	u8 bits = fls64(chi);

	/* special हाल, needed because 1ULL << 64 is undefined */
	अगर (bits > 63)
		वापस tnum_unknown;
	/* e.g. अगर chi = 4, bits = 3, delta = (1<<3) - 1 = 7.
	 * अगर chi = 0, bits = 0, delta = (1<<0) - 1 = 0, so we वापस
	 *  स्थिरant min (since min == max).
	 */
	delta = (1ULL << bits) - 1;
	वापस TNUM(min & ~delta, delta);
पूर्ण

काष्ठा tnum tnum_lshअगरt(काष्ठा tnum a, u8 shअगरt)
अणु
	वापस TNUM(a.value << shअगरt, a.mask << shअगरt);
पूर्ण

काष्ठा tnum tnum_rshअगरt(काष्ठा tnum a, u8 shअगरt)
अणु
	वापस TNUM(a.value >> shअगरt, a.mask >> shअगरt);
पूर्ण

काष्ठा tnum tnum_arshअगरt(काष्ठा tnum a, u8 min_shअगरt, u8 insn_bitness)
अणु
	/* अगर a.value is negative, arithmetic shअगरting by minimum shअगरt
	 * will have larger negative offset compared to more shअगरting.
	 * If a.value is nonnegative, arithmetic shअगरting by minimum shअगरt
	 * will have larger positive offset compare to more shअगरting.
	 */
	अगर (insn_bitness == 32)
		वापस TNUM((u32)(((s32)a.value) >> min_shअगरt),
			    (u32)(((s32)a.mask)  >> min_shअगरt));
	अन्यथा
		वापस TNUM((s64)a.value >> min_shअगरt,
			    (s64)a.mask  >> min_shअगरt);
पूर्ण

काष्ठा tnum tnum_add(काष्ठा tnum a, काष्ठा tnum b)
अणु
	u64 sm, sv, sigma, chi, mu;

	sm = a.mask + b.mask;
	sv = a.value + b.value;
	sigma = sm + sv;
	chi = sigma ^ sv;
	mu = chi | a.mask | b.mask;
	वापस TNUM(sv & ~mu, mu);
पूर्ण

काष्ठा tnum tnum_sub(काष्ठा tnum a, काष्ठा tnum b)
अणु
	u64 dv, alpha, beta, chi, mu;

	dv = a.value - b.value;
	alpha = dv + a.mask;
	beta = dv - b.mask;
	chi = alpha ^ beta;
	mu = chi | a.mask | b.mask;
	वापस TNUM(dv & ~mu, mu);
पूर्ण

काष्ठा tnum tnum_and(काष्ठा tnum a, काष्ठा tnum b)
अणु
	u64 alpha, beta, v;

	alpha = a.value | a.mask;
	beta = b.value | b.mask;
	v = a.value & b.value;
	वापस TNUM(v, alpha & beta & ~v);
पूर्ण

काष्ठा tnum tnum_or(काष्ठा tnum a, काष्ठा tnum b)
अणु
	u64 v, mu;

	v = a.value | b.value;
	mu = a.mask | b.mask;
	वापस TNUM(v, mu & ~v);
पूर्ण

काष्ठा tnum tnum_xor(काष्ठा tnum a, काष्ठा tnum b)
अणु
	u64 v, mu;

	v = a.value ^ b.value;
	mu = a.mask | b.mask;
	वापस TNUM(v & ~mu, mu);
पूर्ण

/* half-multiply add: acc += (unknown * mask * value).
 * An पूर्णांकermediate step in the multiply algorithm.
 */
अटल काष्ठा tnum hma(काष्ठा tnum acc, u64 value, u64 mask)
अणु
	जबतक (mask) अणु
		अगर (mask & 1)
			acc = tnum_add(acc, TNUM(0, value));
		mask >>= 1;
		value <<= 1;
	पूर्ण
	वापस acc;
पूर्ण

काष्ठा tnum tnum_mul(काष्ठा tnum a, काष्ठा tnum b)
अणु
	काष्ठा tnum acc;
	u64 pi;

	pi = a.value * b.value;
	acc = hma(TNUM(pi, 0), a.mask, b.mask | b.value);
	वापस hma(acc, b.mask, a.value);
पूर्ण

/* Note that अगर a and b disagree - i.e. one has a 'known 1' where the other has
 * a 'known 0' - this will return a 'known 1' क्रम that bit.
 */
काष्ठा tnum tnum_पूर्णांकersect(काष्ठा tnum a, काष्ठा tnum b)
अणु
	u64 v, mu;

	v = a.value | b.value;
	mu = a.mask & b.mask;
	वापस TNUM(v & ~mu, mu);
पूर्ण

काष्ठा tnum tnum_cast(काष्ठा tnum a, u8 size)
अणु
	a.value &= (1ULL << (size * 8)) - 1;
	a.mask &= (1ULL << (size * 8)) - 1;
	वापस a;
पूर्ण

bool tnum_is_aligned(काष्ठा tnum a, u64 size)
अणु
	अगर (!size)
		वापस true;
	वापस !((a.value | a.mask) & (size - 1));
पूर्ण

bool tnum_in(काष्ठा tnum a, काष्ठा tnum b)
अणु
	अगर (b.mask & ~a.mask)
		वापस false;
	b.value &= ~a.mask;
	वापस a.value == b.value;
पूर्ण

पूर्णांक tnum_strn(अक्षर *str, माप_प्रकार size, काष्ठा tnum a)
अणु
	वापस snम_लिखो(str, size, "(%#llx; %#llx)", a.value, a.mask);
पूर्ण
EXPORT_SYMBOL_GPL(tnum_strn);

पूर्णांक tnum_sbin(अक्षर *str, माप_प्रकार size, काष्ठा tnum a)
अणु
	माप_प्रकार n;

	क्रम (n = 64; n; n--) अणु
		अगर (n < size) अणु
			अगर (a.mask & 1)
				str[n - 1] = 'x';
			अन्यथा अगर (a.value & 1)
				str[n - 1] = '1';
			अन्यथा
				str[n - 1] = '0';
		पूर्ण
		a.mask >>= 1;
		a.value >>= 1;
	पूर्ण
	str[min(size - 1, (माप_प्रकार)64)] = 0;
	वापस 64;
पूर्ण

काष्ठा tnum tnum_subreg(काष्ठा tnum a)
अणु
	वापस tnum_cast(a, 4);
पूर्ण

काष्ठा tnum tnum_clear_subreg(काष्ठा tnum a)
अणु
	वापस tnum_lshअगरt(tnum_rshअगरt(a, 32), 32);
पूर्ण

काष्ठा tnum tnum_स्थिर_subreg(काष्ठा tnum a, u32 value)
अणु
	वापस tnum_or(tnum_clear_subreg(a), tnum_स्थिर(value));
पूर्ण
