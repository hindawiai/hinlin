<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TIME_H
#घोषणा _LINUX_TIME_H

# include <linux/cache.h>
# include <linux/math64.h>
# include <linux/समय64.h>

बाह्य काष्ठा समयzone sys_tz;

पूर्णांक get_बारpec64(काष्ठा बारpec64 *ts,
		स्थिर काष्ठा __kernel_बारpec __user *uts);
पूर्णांक put_बारpec64(स्थिर काष्ठा बारpec64 *ts,
		काष्ठा __kernel_बारpec __user *uts);
पूर्णांक get_iसमयrspec64(काष्ठा iसमयrspec64 *it,
			स्थिर काष्ठा __kernel_iसमयrspec __user *uit);
पूर्णांक put_iसमयrspec64(स्थिर काष्ठा iसमयrspec64 *it,
			काष्ठा __kernel_iसमयrspec __user *uit);

बाह्य समय64_t स_गढ़ो64(स्थिर अचिन्हित पूर्णांक year, स्थिर अचिन्हित पूर्णांक mon,
			स्थिर अचिन्हित पूर्णांक day, स्थिर अचिन्हित पूर्णांक hour,
			स्थिर अचिन्हित पूर्णांक min, स्थिर अचिन्हित पूर्णांक sec);

#अगर_घोषित CONFIG_POSIX_TIMERS
बाह्य व्योम clear_iसमयr(व्योम);
#अन्यथा
अटल अंतरभूत व्योम clear_iसमयr(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य दीर्घ करो_uबार(पूर्णांक dfd, स्थिर अक्षर __user *filename, काष्ठा बारpec64 *बार, पूर्णांक flags);

/*
 * Similar to the काष्ठा पंचांग in userspace <समय.स>, but it needs to be here so
 * that the kernel source is self contained.
 */
काष्ठा पंचांग अणु
	/*
	 * the number of seconds after the minute, normally in the range
	 * 0 to 59, but can be up to 60 to allow क्रम leap seconds
	 */
	पूर्णांक पंचांग_sec;
	/* the number of minutes after the hour, in the range 0 to 59*/
	पूर्णांक पंचांग_min;
	/* the number of hours past midnight, in the range 0 to 23 */
	पूर्णांक पंचांग_hour;
	/* the day of the month, in the range 1 to 31 */
	पूर्णांक पंचांग_mday;
	/* the number of months since January, in the range 0 to 11 */
	पूर्णांक पंचांग_mon;
	/* the number of years since 1900 */
	दीर्घ पंचांग_year;
	/* the number of days since Sunday, in the range 0 to 6 */
	पूर्णांक पंचांग_wday;
	/* the number of days since January 1, in the range 0 to 365 */
	पूर्णांक पंचांग_yday;
पूर्ण;

व्योम समय64_to_पंचांग(समय64_t totalsecs, पूर्णांक offset, काष्ठा पंचांग *result);

# include <linux/समय32.h>

अटल अंतरभूत bool iसमयrspec64_valid(स्थिर काष्ठा iसमयrspec64 *its)
अणु
	अगर (!बारpec64_valid(&(its->it_पूर्णांकerval)) ||
		!बारpec64_valid(&(its->it_value)))
		वापस false;

	वापस true;
पूर्ण

/**
 * समय_after32 - compare two 32-bit relative बार
 * @a:	the समय which may be after @b
 * @b:	the समय which may be beक्रमe @a
 *
 * समय_after32(a, b) वापसs true अगर the समय @a is after समय @b.
 * समय_beक्रमe32(b, a) वापसs true अगर the समय @b is beक्रमe समय @a.
 *
 * Similar to समय_after(), compare two 32-bit बारtamps क्रम relative
 * बार.  This is useful क्रम comparing 32-bit seconds values that can't
 * be converted to 64-bit values (e.g. due to disk क्रमmat or wire protocol
 * issues) when it is known that the बार are less than 68 years apart.
 */
#घोषणा समय_after32(a, b)	((s32)((u32)(b) - (u32)(a)) < 0)
#घोषणा समय_beक्रमe32(b, a)	समय_after32(a, b)

/**
 * समय_between32 - check अगर a 32-bit बारtamp is within a given समय range
 * @t:	the समय which may be within [l,h]
 * @l:	the lower bound of the range
 * @h:	the higher bound of the range
 *
 * समय_beक्रमe32(t, l, h) वापसs true अगर @l <= @t <= @h. All opeअक्रमs are
 * treated as 32-bit पूर्णांकegers.
 *
 * Equivalent to !(समय_beक्रमe32(@t, @l) || समय_after32(@t, @h)).
 */
#घोषणा समय_between32(t, l, h) ((u32)(h) - (u32)(l) >= (u32)(t) - (u32)(l))

# include <vdso/समय.स>

#पूर्ण_अगर
