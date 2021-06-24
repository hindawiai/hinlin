<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_VDSO_GETTIMखातापूर्णDAY_H
#घोषणा ASM_VDSO_GETTIMखातापूर्णDAY_H

#घोषणा VDSO_HAS_TIME 1

#घोषणा VDSO_HAS_CLOCK_GETRES 1

#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/vdso.h>
#समावेश <linux/compiler.h>

#घोषणा vdso_calc_delta __arch_vdso_calc_delta
अटल __always_अंतरभूत u64 __arch_vdso_calc_delta(u64 cycles, u64 last, u64 mask, u32 mult)
अणु
	वापस (cycles - last) * mult;
पूर्ण

अटल __always_अंतरभूत स्थिर काष्ठा vdso_data *__arch_get_vdso_data(व्योम)
अणु
	वापस _vdso_data;
पूर्ण

अटल अंतरभूत u64 __arch_get_hw_counter(s32 घड़ी_mode, स्थिर काष्ठा vdso_data *vd)
अणु
	u64 adj, now;

	now = get_tod_घड़ी();
	adj = vd->arch_data.tod_steering_end - now;
	अगर (unlikely((s64) adj > 0))
		now += (vd->arch_data.tod_steering_delta < 0) ? (adj >> 15) : -(adj >> 15);
	वापस now;
पूर्ण

अटल __always_अंतरभूत
दीर्घ घड़ी_समय_लो_fallback(घड़ीid_t clkid, काष्ठा __kernel_बारpec *ts)
अणु
	रेजिस्टर अचिन्हित दीर्घ r1 __यंत्र__("r1") = __NR_घड़ी_समय_लो;
	रेजिस्टर अचिन्हित दीर्घ r2 __यंत्र__("r2") = (अचिन्हित दीर्घ)clkid;
	रेजिस्टर व्योम *r3 __यंत्र__("r3") = ts;

	यंत्र ("svc 0\n" : "+d" (r2) : "d" (r1), "d" (r3) : "cc", "memory");
	वापस r2;
पूर्ण

अटल __always_अंतरभूत
दीर्घ समय_लोofday_fallback(रेजिस्टर काष्ठा __kernel_old_समयval *tv,
			   रेजिस्टर काष्ठा समयzone *tz)
अणु
	रेजिस्टर अचिन्हित दीर्घ r1 __यंत्र__("r1") = __NR_समय_लोofday;
	रेजिस्टर अचिन्हित दीर्घ r2 __यंत्र__("r2") = (अचिन्हित दीर्घ)tv;
	रेजिस्टर व्योम *r3 __यंत्र__("r3") = tz;

	यंत्र ("svc 0\n" : "+d" (r2) : "d" (r1), "d" (r3) : "cc", "memory");
	वापस r2;
पूर्ण

अटल __always_अंतरभूत
दीर्घ घड़ी_getres_fallback(घड़ीid_t clkid, काष्ठा __kernel_बारpec *ts)
अणु
	रेजिस्टर अचिन्हित दीर्घ r1 __यंत्र__("r1") = __NR_घड़ी_getres;
	रेजिस्टर अचिन्हित दीर्घ r2 __यंत्र__("r2") = (अचिन्हित दीर्घ)clkid;
	रेजिस्टर व्योम *r3 __यंत्र__("r3") = ts;

	यंत्र ("svc 0\n" : "+d" (r2) : "d" (r1), "d" (r3) : "cc", "memory");
	वापस r2;
पूर्ण

#अगर_घोषित CONFIG_TIME_NS
अटल __always_अंतरभूत
स्थिर काष्ठा vdso_data *__arch_get_समयns_vdso_data(स्थिर काष्ठा vdso_data *vd)
अणु
	वापस _समयns_data;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
