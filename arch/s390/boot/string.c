<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#अघोषित CONFIG_KASAN
#अघोषित CONFIG_KASAN_GENERIC
#समावेश "../lib/string.c"

पूर्णांक म_भेदन(स्थिर अक्षर *cs, स्थिर अक्षर *ct, माप_प्रकार count)
अणु
	अचिन्हित अक्षर c1, c2;

	जबतक (count) अणु
		c1 = *cs++;
		c2 = *ct++;
		अगर (c1 != c2)
			वापस c1 < c2 ? -1 : 1;
		अगर (!c1)
			अवरोध;
		count--;
	पूर्ण
	वापस 0;
पूर्ण

अक्षर *skip_spaces(स्थिर अक्षर *str)
अणु
	जबतक (है_खाली(*str))
		++str;
	वापस (अक्षर *)str;
पूर्ण

अक्षर *strim(अक्षर *s)
अणु
	माप_प्रकार size;
	अक्षर *end;

	size = म_माप(s);
	अगर (!size)
		वापस s;

	end = s + size - 1;
	जबतक (end >= s && है_खाली(*end))
		end--;
	*(end + 1) = '\0';

	वापस skip_spaces(s);
पूर्ण

/* Works only क्रम digits and letters, but small and fast */
#घोषणा TOLOWER(x) ((x) | 0x20)

अटल अचिन्हित पूर्णांक simple_guess_base(स्थिर अक्षर *cp)
अणु
	अगर (cp[0] == '0') अणु
		अगर (TOLOWER(cp[1]) == 'x' && है_षष्ठादशक(cp[2]))
			वापस 16;
		अन्यथा
			वापस 8;
	पूर्ण अन्यथा अणु
		वापस 10;
	पूर्ण
पूर्ण

/**
 * simple_म_से_अदीर्घl - convert a string to an अचिन्हित दीर्घ दीर्घ
 * @cp: The start of the string
 * @endp: A poपूर्णांकer to the end of the parsed string will be placed here
 * @base: The number base to use
 */

अचिन्हित दीर्घ दीर्घ simple_म_से_अदीर्घl(स्थिर अक्षर *cp, अक्षर **endp,
				   अचिन्हित पूर्णांक base)
अणु
	अचिन्हित दीर्घ दीर्घ result = 0;

	अगर (!base)
		base = simple_guess_base(cp);

	अगर (base == 16 && cp[0] == '0' && TOLOWER(cp[1]) == 'x')
		cp += 2;

	जबतक (है_षष्ठादशक(*cp)) अणु
		अचिन्हित पूर्णांक value;

		value = है_अंक(*cp) ? *cp - '0' : TOLOWER(*cp) - 'a' + 10;
		अगर (value >= base)
			अवरोध;
		result = result * base + value;
		cp++;
	पूर्ण
	अगर (endp)
		*endp = (अक्षर *)cp;

	वापस result;
पूर्ण

दीर्घ simple_म_से_दीर्घ(स्थिर अक्षर *cp, अक्षर **endp, अचिन्हित पूर्णांक base)
अणु
	अगर (*cp == '-')
		वापस -simple_म_से_अदीर्घl(cp + 1, endp, base);

	वापस simple_म_से_अदीर्घl(cp, endp, base);
पूर्ण

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
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण
