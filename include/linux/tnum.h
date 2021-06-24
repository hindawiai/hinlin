<शैली गुरु>
/* tnum: tracked (or tristate) numbers
 *
 * A tnum tracks knowledge about the bits of a value.  Each bit can be either
 * known (0 or 1), or unknown (x).  Arithmetic operations on tnums will
 * propagate the unknown bits such that the tnum result represents all the
 * possible results क्रम possible values of the opeअक्रमs.
 */

#अगर_अघोषित _LINUX_TNUM_H
#घोषणा _LINUX_TNUM_H

#समावेश <linux/types.h>

काष्ठा tnum अणु
	u64 value;
	u64 mask;
पूर्ण;

/* Conकाष्ठाors */
/* Represent a known स्थिरant as a tnum. */
काष्ठा tnum tnum_स्थिर(u64 value);
/* A completely unknown value */
बाह्य स्थिर काष्ठा tnum tnum_unknown;
/* A value that's unknown except that @min <= value <= @max */
काष्ठा tnum tnum_range(u64 min, u64 max);

/* Arithmetic and logical ops */
/* Shअगरt a tnum left (by a fixed shअगरt) */
काष्ठा tnum tnum_lshअगरt(काष्ठा tnum a, u8 shअगरt);
/* Shअगरt (rsh) a tnum right (by a fixed shअगरt) */
काष्ठा tnum tnum_rshअगरt(काष्ठा tnum a, u8 shअगरt);
/* Shअगरt (arsh) a tnum right (by a fixed min_shअगरt) */
काष्ठा tnum tnum_arshअगरt(काष्ठा tnum a, u8 min_shअगरt, u8 insn_bitness);
/* Add two tnums, वापस @a + @b */
काष्ठा tnum tnum_add(काष्ठा tnum a, काष्ठा tnum b);
/* Subtract two tnums, वापस @a - @b */
काष्ठा tnum tnum_sub(काष्ठा tnum a, काष्ठा tnum b);
/* Bitwise-AND, वापस @a & @b */
काष्ठा tnum tnum_and(काष्ठा tnum a, काष्ठा tnum b);
/* Bitwise-OR, वापस @a | @b */
काष्ठा tnum tnum_or(काष्ठा tnum a, काष्ठा tnum b);
/* Bitwise-XOR, वापस @a ^ @b */
काष्ठा tnum tnum_xor(काष्ठा tnum a, काष्ठा tnum b);
/* Multiply two tnums, वापस @a * @b */
काष्ठा tnum tnum_mul(काष्ठा tnum a, काष्ठा tnum b);

/* Return a tnum representing numbers satisfying both @a and @b */
काष्ठा tnum tnum_पूर्णांकersect(काष्ठा tnum a, काष्ठा tnum b);

/* Return @a with all but the lowest @size bytes cleared */
काष्ठा tnum tnum_cast(काष्ठा tnum a, u8 size);

/* Returns true अगर @a is a known स्थिरant */
अटल अंतरभूत bool tnum_is_स्थिर(काष्ठा tnum a)
अणु
	वापस !a.mask;
पूर्ण

/* Returns true अगर @a == tnum_स्थिर(@b) */
अटल अंतरभूत bool tnum_equals_स्थिर(काष्ठा tnum a, u64 b)
अणु
	वापस tnum_is_स्थिर(a) && a.value == b;
पूर्ण

/* Returns true अगर @a is completely unknown */
अटल अंतरभूत bool tnum_is_unknown(काष्ठा tnum a)
अणु
	वापस !~a.mask;
पूर्ण

/* Returns true अगर @a is known to be a multiple of @size.
 * @size must be a घातer of two.
 */
bool tnum_is_aligned(काष्ठा tnum a, u64 size);

/* Returns true अगर @b represents a subset of @a. */
bool tnum_in(काष्ठा tnum a, काष्ठा tnum b);

/* Formatting functions.  These have snम_लिखो-like semantics: they will ग_लिखो
 * up to @size bytes (including the terminating NUL byte), and वापस the number
 * of bytes (excluding the terminating NUL) which would have been written had
 * sufficient space been available.  (Thus tnum_sbin always वापसs 64.)
 */
/* Format a tnum as a pair of hex numbers (value; mask) */
पूर्णांक tnum_strn(अक्षर *str, माप_प्रकार size, काष्ठा tnum a);
/* Format a tnum as tristate binary expansion */
पूर्णांक tnum_sbin(अक्षर *str, माप_प्रकार size, काष्ठा tnum a);

/* Returns the 32-bit subreg */
काष्ठा tnum tnum_subreg(काष्ठा tnum a);
/* Returns the tnum with the lower 32-bit subreg cleared */
काष्ठा tnum tnum_clear_subreg(काष्ठा tnum a);
/* Returns the tnum with the lower 32-bit subreg set to value */
काष्ठा tnum tnum_स्थिर_subreg(काष्ठा tnum a, u32 value);
/* Returns true अगर 32-bit subreg @a is a known स्थिरant*/
अटल अंतरभूत bool tnum_subreg_is_स्थिर(काष्ठा tnum a)
अणु
	वापस !(tnum_subreg(a)).mask;
पूर्ण

#पूर्ण_अगर /* _LINUX_TNUM_H */
