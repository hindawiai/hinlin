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

#घोषणा VDSO_HAS_CLOCK_GETRES		1

अटल __always_अंतरभूत
पूर्णांक समय_लोofday_fallback(काष्ठा __kernel_old_समयval *_tv,
			  काष्ठा समयzone *_tz)
अणु
	रेजिस्टर काष्ठा समयzone *tz यंत्र("x1") = _tz;
	रेजिस्टर काष्ठा __kernel_old_समयval *tv यंत्र("x0") = _tv;
	रेजिस्टर दीर्घ ret यंत्र ("x0");
	रेजिस्टर दीर्घ nr यंत्र("x8") = __NR_समय_लोofday;

	यंत्र अस्थिर(
	"       svc #0\n"
	: "=r" (ret)
	: "r" (tv), "r" (tz), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
दीर्घ घड़ी_समय_लो_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	रेजिस्टर काष्ठा __kernel_बारpec *ts यंत्र("x1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("x0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र ("x0");
	रेजिस्टर दीर्घ nr यंत्र("x8") = __NR_घड़ी_समय_लो;

	यंत्र अस्थिर(
	"       svc #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
पूर्णांक घड़ी_getres_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	रेजिस्टर काष्ठा __kernel_बारpec *ts यंत्र("x1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("x0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र ("x0");
	रेजिस्टर दीर्घ nr यंत्र("x8") = __NR_घड़ी_getres;

	यंत्र अस्थिर(
	"       svc #0\n"
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
	अगर (घड़ी_mode == VDSO_CLOCKMODE_NONE)
		वापस 0;

	/*
	 * This isb() is required to prevent that the counter value
	 * is speculated.
	 */
	isb();
	यंत्र अस्थिर("mrs %0, cntvct_el0" : "=r" (res) :: "memory");
	arch_counter_enक्रमce_ordering(res);

	वापस res;
पूर्ण

अटल __always_अंतरभूत
स्थिर काष्ठा vdso_data *__arch_get_vdso_data(व्योम)
अणु
	वापस _vdso_data;
पूर्ण

#अगर_घोषित CONFIG_TIME_NS
अटल __always_अंतरभूत
स्थिर काष्ठा vdso_data *__arch_get_समयns_vdso_data(स्थिर काष्ठा vdso_data *vd)
अणु
	वापस _समयns_data;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_GETTIMखातापूर्णDAY_H */
