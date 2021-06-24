<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Convert पूर्णांकeger string representation to an पूर्णांकeger.
 * If an पूर्णांकeger करोesn't fit पूर्णांकo specअगरied type, -E is वापसed.
 *
 * Integer starts with optional sign.
 * kstrtou*() functions करो not accept sign "-".
 *
 * Radix 0 means स्वतःdetection: leading "0x" implies radix 16,
 * leading "0" implies radix 8, otherwise radix is 10.
 * Autodetection hपूर्णांकs work after optional sign, but not beक्रमe.
 *
 * If -E is वापसed, result is not touched.
 */
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश "kstrtox.h"

स्थिर अक्षर *_parse_पूर्णांकeger_fixup_radix(स्थिर अक्षर *s, अचिन्हित पूर्णांक *base)
अणु
	अगर (*base == 0) अणु
		अगर (s[0] == '0') अणु
			अगर (_छोटे(s[1]) == 'x' && है_षष्ठादशक(s[2]))
				*base = 16;
			अन्यथा
				*base = 8;
		पूर्ण अन्यथा
			*base = 10;
	पूर्ण
	अगर (*base == 16 && s[0] == '0' && _tolower(s[1]) == 'x')
		s += 2;
	वापस s;
पूर्ण

/*
 * Convert non-negative पूर्णांकeger string representation in explicitly given radix
 * to an पूर्णांकeger.
 * Return number of अक्षरacters consumed maybe or-ed with overflow bit.
 * If overflow occurs, result पूर्णांकeger (incorrect) is still वापसed.
 *
 * Don't you dare use this function.
 */
अचिन्हित पूर्णांक _parse_पूर्णांकeger(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ दीर्घ *p)
अणु
	अचिन्हित दीर्घ दीर्घ res;
	अचिन्हित पूर्णांक rv;

	res = 0;
	rv = 0;
	जबतक (1) अणु
		अचिन्हित पूर्णांक c = *s;
		अचिन्हित पूर्णांक lc = c | 0x20; /* करोn't छोटे() this line */
		अचिन्हित पूर्णांक val;

		अगर ('0' <= c && c <= '9')
			val = c - '0';
		अन्यथा अगर ('a' <= lc && lc <= 'f')
			val = lc - 'a' + 10;
		अन्यथा
			अवरोध;

		अगर (val >= base)
			अवरोध;
		/*
		 * Check क्रम overflow only अगर we are within range of
		 * it in the max base we support (16)
		 */
		अगर (unlikely(res & (~0ull << 60))) अणु
			अगर (res > भाग_u64(ULदीर्घ_उच्च - val, base))
				rv |= KSTRTOX_OVERFLOW;
		पूर्ण
		res = res * base + val;
		rv++;
		s++;
	पूर्ण
	*p = res;
	वापस rv;
पूर्ण

अटल पूर्णांक _kम_से_अदीर्घl(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ दीर्घ *res)
अणु
	अचिन्हित दीर्घ दीर्घ _res;
	अचिन्हित पूर्णांक rv;

	s = _parse_पूर्णांकeger_fixup_radix(s, &base);
	rv = _parse_पूर्णांकeger(s, base, &_res);
	अगर (rv & KSTRTOX_OVERFLOW)
		वापस -दुस्फल;
	अगर (rv == 0)
		वापस -EINVAL;
	s += rv;
	अगर (*s == '\n')
		s++;
	अगर (*s)
		वापस -EINVAL;
	*res = _res;
	वापस 0;
पूर्ण

/**
 * kम_से_अदीर्घl - convert a string to an अचिन्हित दीर्घ दीर्घ
 * @s: The start of the string. The string must be null-terminated, and may also
 *  include a single newline beक्रमe its terminating null. The first अक्षरacter
 *  may also be a plus sign, but not a minus sign.
 * @base: The number base to use. The maximum supported base is 16. If base is
 *  given as 0, then the base of the string is स्वतःmatically detected with the
 *  conventional semantics - If it begins with 0x the number will be parsed as a
 *  hexadecimal (हाल insensitive), अगर it otherwise begins with 0, it will be
 *  parsed as an octal number. Otherwise it will be parsed as a decimal.
 * @res: Where to ग_लिखो the result of the conversion on success.
 *
 * Returns 0 on success, -दुस्फल on overflow and -EINVAL on parsing error.
 * Preferred over simple_म_से_अदीर्घl(). Return code must be checked.
 */
पूर्णांक kम_से_अदीर्घl(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ दीर्घ *res)
अणु
	अगर (s[0] == '+')
		s++;
	वापस _kम_से_अदीर्घl(s, base, res);
पूर्ण
EXPORT_SYMBOL(kम_से_अदीर्घl);

/**
 * kम_से_दीर्घl - convert a string to a दीर्घ दीर्घ
 * @s: The start of the string. The string must be null-terminated, and may also
 *  include a single newline beक्रमe its terminating null. The first अक्षरacter
 *  may also be a plus sign or a minus sign.
 * @base: The number base to use. The maximum supported base is 16. If base is
 *  given as 0, then the base of the string is स्वतःmatically detected with the
 *  conventional semantics - If it begins with 0x the number will be parsed as a
 *  hexadecimal (हाल insensitive), अगर it otherwise begins with 0, it will be
 *  parsed as an octal number. Otherwise it will be parsed as a decimal.
 * @res: Where to ग_लिखो the result of the conversion on success.
 *
 * Returns 0 on success, -दुस्फल on overflow and -EINVAL on parsing error.
 * Preferred over simple_म_से_दीर्घl(). Return code must be checked.
 */
पूर्णांक kम_से_दीर्घl(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, दीर्घ दीर्घ *res)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	पूर्णांक rv;

	अगर (s[0] == '-') अणु
		rv = _kम_से_अदीर्घl(s + 1, base, &पंचांगp);
		अगर (rv < 0)
			वापस rv;
		अगर ((दीर्घ दीर्घ)-पंचांगp > 0)
			वापस -दुस्फल;
		*res = -पंचांगp;
	पूर्ण अन्यथा अणु
		rv = kम_से_अदीर्घl(s, base, &पंचांगp);
		अगर (rv < 0)
			वापस rv;
		अगर ((दीर्घ दीर्घ)पंचांगp < 0)
			वापस -दुस्फल;
		*res = पंचांगp;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kम_से_दीर्घl);

/* Internal, करो not use. */
पूर्णांक _kम_से_अदीर्घ(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ *res)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	पूर्णांक rv;

	rv = kम_से_अदीर्घl(s, base, &पंचांगp);
	अगर (rv < 0)
		वापस rv;
	अगर (पंचांगp != (अचिन्हित दीर्घ)पंचांगp)
		वापस -दुस्फल;
	*res = पंचांगp;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(_kम_से_अदीर्घ);

/* Internal, करो not use. */
पूर्णांक _kम_से_दीर्घ(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, दीर्घ *res)
अणु
	दीर्घ दीर्घ पंचांगp;
	पूर्णांक rv;

	rv = kम_से_दीर्घl(s, base, &पंचांगp);
	अगर (rv < 0)
		वापस rv;
	अगर (पंचांगp != (दीर्घ)पंचांगp)
		वापस -दुस्फल;
	*res = पंचांगp;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(_kम_से_दीर्घ);

/**
 * kstrtouपूर्णांक - convert a string to an अचिन्हित पूर्णांक
 * @s: The start of the string. The string must be null-terminated, and may also
 *  include a single newline beक्रमe its terminating null. The first अक्षरacter
 *  may also be a plus sign, but not a minus sign.
 * @base: The number base to use. The maximum supported base is 16. If base is
 *  given as 0, then the base of the string is स्वतःmatically detected with the
 *  conventional semantics - If it begins with 0x the number will be parsed as a
 *  hexadecimal (हाल insensitive), अगर it otherwise begins with 0, it will be
 *  parsed as an octal number. Otherwise it will be parsed as a decimal.
 * @res: Where to ग_लिखो the result of the conversion on success.
 *
 * Returns 0 on success, -दुस्फल on overflow and -EINVAL on parsing error.
 * Preferred over simple_म_से_अदीर्घ(). Return code must be checked.
 */
पूर्णांक kstrtouपूर्णांक(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक *res)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	पूर्णांक rv;

	rv = kम_से_अदीर्घl(s, base, &पंचांगp);
	अगर (rv < 0)
		वापस rv;
	अगर (पंचांगp != (अचिन्हित पूर्णांक)पंचांगp)
		वापस -दुस्फल;
	*res = पंचांगp;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kstrtouपूर्णांक);

/**
 * kstrtoपूर्णांक - convert a string to an पूर्णांक
 * @s: The start of the string. The string must be null-terminated, and may also
 *  include a single newline beक्रमe its terminating null. The first अक्षरacter
 *  may also be a plus sign or a minus sign.
 * @base: The number base to use. The maximum supported base is 16. If base is
 *  given as 0, then the base of the string is स्वतःmatically detected with the
 *  conventional semantics - If it begins with 0x the number will be parsed as a
 *  hexadecimal (हाल insensitive), अगर it otherwise begins with 0, it will be
 *  parsed as an octal number. Otherwise it will be parsed as a decimal.
 * @res: Where to ग_लिखो the result of the conversion on success.
 *
 * Returns 0 on success, -दुस्फल on overflow and -EINVAL on parsing error.
 * Preferred over simple_म_से_दीर्घ(). Return code must be checked.
 */
पूर्णांक kstrtoपूर्णांक(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, पूर्णांक *res)
अणु
	दीर्घ दीर्घ पंचांगp;
	पूर्णांक rv;

	rv = kम_से_दीर्घl(s, base, &पंचांगp);
	अगर (rv < 0)
		वापस rv;
	अगर (पंचांगp != (पूर्णांक)पंचांगp)
		वापस -दुस्फल;
	*res = पंचांगp;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kstrtoपूर्णांक);

पूर्णांक kstrtou16(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, u16 *res)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	पूर्णांक rv;

	rv = kम_से_अदीर्घl(s, base, &पंचांगp);
	अगर (rv < 0)
		वापस rv;
	अगर (पंचांगp != (u16)पंचांगp)
		वापस -दुस्फल;
	*res = पंचांगp;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kstrtou16);

पूर्णांक kstrtos16(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, s16 *res)
अणु
	दीर्घ दीर्घ पंचांगp;
	पूर्णांक rv;

	rv = kम_से_दीर्घl(s, base, &पंचांगp);
	अगर (rv < 0)
		वापस rv;
	अगर (पंचांगp != (s16)पंचांगp)
		वापस -दुस्फल;
	*res = पंचांगp;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kstrtos16);

पूर्णांक kstrtou8(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, u8 *res)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	पूर्णांक rv;

	rv = kम_से_अदीर्घl(s, base, &पंचांगp);
	अगर (rv < 0)
		वापस rv;
	अगर (पंचांगp != (u8)पंचांगp)
		वापस -दुस्फल;
	*res = पंचांगp;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kstrtou8);

पूर्णांक kstrtos8(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, s8 *res)
अणु
	दीर्घ दीर्घ पंचांगp;
	पूर्णांक rv;

	rv = kम_से_दीर्घl(s, base, &पंचांगp);
	अगर (rv < 0)
		वापस rv;
	अगर (पंचांगp != (s8)पंचांगp)
		वापस -दुस्फल;
	*res = पंचांगp;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kstrtos8);

/**
 * kstrtobool - convert common user inमाला_दो पूर्णांकo boolean values
 * @s: input string
 * @res: result
 *
 * This routine वापसs 0 अगरf the first अक्षरacter is one of 'Yy1Nn0', or
 * [oO][NnFf] क्रम "on" and "off". Otherwise it will वापस -EINVAL.  Value
 * poपूर्णांकed to by res is updated upon finding a match.
 */
पूर्णांक kstrtobool(स्थिर अक्षर *s, bool *res)
अणु
	अगर (!s)
		वापस -EINVAL;

	चयन (s[0]) अणु
	हाल 'y':
	हाल 'Y':
	हाल '1':
		*res = true;
		वापस 0;
	हाल 'n':
	हाल 'N':
	हाल '0':
		*res = false;
		वापस 0;
	हाल 'o':
	हाल 'O':
		चयन (s[1]) अणु
		हाल 'n':
		हाल 'N':
			*res = true;
			वापस 0;
		हाल 'f':
		हाल 'F':
			*res = false;
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(kstrtobool);

/*
 * Since "base" would be a nonsense argument, this खोलो-codes the
 * _from_user helper instead of using the helper macro below.
 */
पूर्णांक kstrtobool_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, bool *res)
अणु
	/* Longest string needed to dअगरferentiate, newline, terminator */
	अक्षर buf[4];

	count = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, s, count))
		वापस -EFAULT;
	buf[count] = '\0';
	वापस kstrtobool(buf, res);
पूर्ण
EXPORT_SYMBOL(kstrtobool_from_user);

#घोषणा kstrto_from_user(f, g, type)					\
पूर्णांक f(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, type *res)	\
अणु									\
	/* sign, base 2 representation, newline, terminator */		\
	अक्षर buf[1 + माप(type) * 8 + 1 + 1];				\
									\
	count = min(count, माप(buf) - 1);				\
	अगर (copy_from_user(buf, s, count))				\
		वापस -EFAULT;						\
	buf[count] = '\0';						\
	वापस g(buf, base, res);					\
पूर्ण									\
EXPORT_SYMBOL(f)

kstrto_from_user(kम_से_अदीर्घl_from_user,	kम_से_अदीर्घl,	अचिन्हित दीर्घ दीर्घ);
kstrto_from_user(kम_से_दीर्घl_from_user,	kम_से_दीर्घl,	दीर्घ दीर्घ);
kstrto_from_user(kम_से_अदीर्घ_from_user,	kम_से_अदीर्घ,	अचिन्हित दीर्घ);
kstrto_from_user(kम_से_दीर्घ_from_user,	kम_से_दीर्घ,	दीर्घ);
kstrto_from_user(kstrtouपूर्णांक_from_user,	kstrtouपूर्णांक,	अचिन्हित पूर्णांक);
kstrto_from_user(kstrtoपूर्णांक_from_user,	kstrtoपूर्णांक,	पूर्णांक);
kstrto_from_user(kstrtou16_from_user,	kstrtou16,	u16);
kstrto_from_user(kstrtos16_from_user,	kstrtos16,	s16);
kstrto_from_user(kstrtou8_from_user,	kstrtou8,	u8);
kstrto_from_user(kstrtos8_from_user,	kstrtos8,	s8);
