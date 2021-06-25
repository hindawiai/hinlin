<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 ARM Limited
 */
#अगर_अघोषित __ASM_VDSO_GETTIMखातापूर्णDAY_H
#घोषणा __ASM_VDSO_GETTIMखातापूर्णDAY_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/vdso/cp15.h>
#समावेश <uapi/linux/समय.स>

#घोषणा VDSO_HAS_CLOCK_GETRES		1

बाह्य काष्ठा vdso_data *__get_datapage(व्योम);

अटल __always_अंतरभूत पूर्णांक समय_लोofday_fallback(
				काष्ठा __kernel_old_समयval *_tv,
				काष्ठा समयzone *_tz)
अणु
	रेजिस्टर काष्ठा समयzone *tz यंत्र("r1") = _tz;
	रेजिस्टर काष्ठा __kernel_old_समयval *tv यंत्र("r0") = _tv;
	रेजिस्टर दीर्घ ret यंत्र ("r0");
	रेजिस्टर दीर्घ nr यंत्र("r7") = __NR_समय_लोofday;

	यंत्र अस्थिर(
	"	swi #0\n"
	: "=r" (ret)
	: "r" (tv), "r" (tz), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत दीर्घ घड़ी_समय_लो_fallback(
					घड़ीid_t _clkid,
					काष्ठा __kernel_बारpec *_ts)
अणु
	रेजिस्टर काष्ठा __kernel_बारpec *ts यंत्र("r1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("r0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र ("r0");
	रेजिस्टर दीर्घ nr यंत्र("r7") = __NR_घड़ी_समय_लो64;

	यंत्र अस्थिर(
	"	swi #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत दीर्घ घड़ी_समय_लो32_fallback(
					घड़ीid_t _clkid,
					काष्ठा old_बारpec32 *_ts)
अणु
	रेजिस्टर काष्ठा old_बारpec32 *ts यंत्र("r1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("r0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र ("r0");
	रेजिस्टर दीर्घ nr यंत्र("r7") = __NR_घड़ी_समय_लो;

	यंत्र अस्थिर(
	"	swi #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत पूर्णांक घड़ी_getres_fallback(
					घड़ीid_t _clkid,
					काष्ठा __kernel_बारpec *_ts)
अणु
	रेजिस्टर काष्ठा __kernel_बारpec *ts यंत्र("r1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("r0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र ("r0");
	रेजिस्टर दीर्घ nr यंत्र("r7") = __NR_घड़ी_getres_समय64;

	यंत्र अस्थिर(
	"       swi #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत पूर्णांक घड़ी_getres32_fallback(
					घड़ीid_t _clkid,
					काष्ठा old_बारpec32 *_ts)
अणु
	रेजिस्टर काष्ठा old_बारpec32 *ts यंत्र("r1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("r0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र ("r0");
	रेजिस्टर दीर्घ nr यंत्र("r7") = __NR_घड़ी_getres;

	यंत्र अस्थिर(
	"       swi #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल अंतरभूत bool arm_vdso_hres_capable(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM_ARCH_TIMER);
पूर्ण
#घोषणा __arch_vdso_hres_capable arm_vdso_hres_capable

अटल __always_अंतरभूत u64 __arch_get_hw_counter(पूर्णांक घड़ी_mode,
						 स्थिर काष्ठा vdso_data *vd)
अणु
#अगर_घोषित CONFIG_ARM_ARCH_TIMER
	u64 cycle_now;

	/*
	 * Core checks क्रम mode alपढ़ोy, so this raced against a concurrent
	 * update. Return something. Core will करो another round and then
	 * see the mode change and fallback to the syscall.
	 */
	अगर (घड़ी_mode == VDSO_CLOCKMODE_NONE)
		वापस 0;

	isb();
	cycle_now = पढ़ो_sysreg(CNTVCT);

	वापस cycle_now;
#अन्यथा
	/* Make GCC happy. This is compiled out anyway */
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल __always_अंतरभूत स्थिर काष्ठा vdso_data *__arch_get_vdso_data(व्योम)
अणु
	वापस __get_datapage();
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_GETTIMखातापूर्णDAY_H */
