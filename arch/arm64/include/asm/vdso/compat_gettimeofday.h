<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 ARM Limited
 */
#अगर_अघोषित __ASM_VDSO_GETTIMखातापूर्णDAY_H
#घोषणा __ASM_VDSO_GETTIMखातापूर्णDAY_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/त्रुटिसं.स>

#समावेश <यंत्र/vdso/compat_barrier.h>

#घोषणा VDSO_HAS_CLOCK_GETRES		1

#घोषणा BUILD_VDSO32			1

अटल __always_अंतरभूत
पूर्णांक समय_लोofday_fallback(काष्ठा __kernel_old_समयval *_tv,
			  काष्ठा समयzone *_tz)
अणु
	रेजिस्टर काष्ठा समयzone *tz यंत्र("r1") = _tz;
	रेजिस्टर काष्ठा __kernel_old_समयval *tv यंत्र("r0") = _tv;
	रेजिस्टर दीर्घ ret यंत्र ("r0");
	रेजिस्टर दीर्घ nr यंत्र("r7") = __NR_compat_समय_लोofday;

	यंत्र अस्थिर(
	"	swi #0\n"
	: "=r" (ret)
	: "r" (tv), "r" (tz), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
दीर्घ घड़ी_समय_लो_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	रेजिस्टर काष्ठा __kernel_बारpec *ts यंत्र("r1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("r0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र ("r0");
	रेजिस्टर दीर्घ nr यंत्र("r7") = __NR_compat_घड़ी_समय_लो64;

	यंत्र अस्थिर(
	"	swi #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
दीर्घ घड़ी_समय_लो32_fallback(घड़ीid_t _clkid, काष्ठा old_बारpec32 *_ts)
अणु
	रेजिस्टर काष्ठा old_बारpec32 *ts यंत्र("r1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("r0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र ("r0");
	रेजिस्टर दीर्घ nr यंत्र("r7") = __NR_compat_घड़ी_समय_लो;

	यंत्र अस्थिर(
	"	swi #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
पूर्णांक घड़ी_getres_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	रेजिस्टर काष्ठा __kernel_बारpec *ts यंत्र("r1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("r0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र ("r0");
	रेजिस्टर दीर्घ nr यंत्र("r7") = __NR_compat_घड़ी_getres_समय64;

	यंत्र अस्थिर(
	"       swi #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
पूर्णांक घड़ी_getres32_fallback(घड़ीid_t _clkid, काष्ठा old_बारpec32 *_ts)
अणु
	रेजिस्टर काष्ठा old_बारpec32 *ts यंत्र("r1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("r0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र ("r0");
	रेजिस्टर दीर्घ nr यंत्र("r7") = __NR_compat_घड़ी_getres;

	यंत्र अस्थिर(
	"       swi #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत u64 __arch_get_hw_counter(s32 घड़ी_mode,
						 स्थिर काष्ठा vdso_data *vd)
अणु
	u64 res;

	/*
	 * Core checks क्रम mode alपढ़ोy, so this raced against a concurrent
	 * update. Return something. Core will करो another round and then
	 * see the mode change and fallback to the syscall.
	 */
	अगर (घड़ी_mode != VDSO_CLOCKMODE_ARCHTIMER)
		वापस 0;

	/*
	 * This isb() is required to prevent that the counter value
	 * is speculated.
	 */
	isb();
	यंत्र अस्थिर("mrrc p15, 1, %Q0, %R0, c14" : "=r" (res));
	/*
	 * This isb() is required to prevent that the seq lock is
	 * speculated.
	 */
	isb();

	वापस res;
पूर्ण

अटल __always_अंतरभूत स्थिर काष्ठा vdso_data *__arch_get_vdso_data(व्योम)
अणु
	स्थिर काष्ठा vdso_data *ret;

	/*
	 * This simply माला_दो &_vdso_data पूर्णांकo ret. The reason why we करोn't use
	 * `ret = _vdso_data` is that the compiler tends to optimise this in a
	 * very suboptimal way: instead of keeping &_vdso_data in a रेजिस्टर,
	 * it goes through a relocation almost every समय _vdso_data must be
	 * accessed (even in subfunctions). This is both समय and space
	 * consuming: each relocation uses a word in the code section, and it
	 * has to be loaded at runसमय.
	 *
	 * This trick hides the assignment from the compiler. Since it cannot
	 * track where the poपूर्णांकer comes from, it will only use one relocation
	 * where __arch_get_vdso_data() is called, and then keep the result in
	 * a रेजिस्टर.
	 */
	यंत्र अस्थिर("mov %0, %1" : "=r"(ret) : "r"(_vdso_data));

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_TIME_NS
अटल __always_अंतरभूत
स्थिर काष्ठा vdso_data *__arch_get_समयns_vdso_data(स्थिर काष्ठा vdso_data *vd)
अणु
	स्थिर काष्ठा vdso_data *ret;

	/* See __arch_get_vdso_data(). */
	यंत्र अस्थिर("mov %0, %1" : "=r"(ret) : "r"(_समयns_data));

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool vdso_घड़ीsource_ok(स्थिर काष्ठा vdso_data *vd)
अणु
	वापस vd->घड़ी_mode == VDSO_CLOCKMODE_ARCHTIMER;
पूर्ण
#घोषणा vdso_घड़ीsource_ok	vdso_घड़ीsource_ok

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_GETTIMखातापूर्णDAY_H */
