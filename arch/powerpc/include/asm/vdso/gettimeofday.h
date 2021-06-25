<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_VDSO_GETTIMखातापूर्णDAY_H
#घोषणा _ASM_POWERPC_VDSO_GETTIMखातापूर्णDAY_H

#समावेश <यंत्र/page.h>

#अगर_घोषित __ASSEMBLY__

#समावेश <यंत्र/ppc_यंत्र.h>

/*
 * The macros sets two stack frames, one क्रम the caller and one क्रम the callee
 * because there are no requirement क्रम the caller to set a stack frame when
 * calling VDSO so it may have omitted to set one, especially on PPC64
 */

.macro cvdso_call funct
  .cfi_startproc
	PPC_STLU	r1, -PPC_MIN_STKFRM(r1)
	mflr		r0
  .cfi_रेजिस्टर lr, r0
	PPC_STLU	r1, -PPC_MIN_STKFRM(r1)
	PPC_STL		r0, PPC_MIN_STKFRM + PPC_LR_STKOFF(r1)
#अगर_घोषित __घातerpc64__
	PPC_STL		r2, PPC_MIN_STKFRM + STK_GOT(r1)
#पूर्ण_अगर
	get_datapage	r5
	addi		r5, r5, VDSO_DATA_OFFSET
	bl		DOTSYM(\पunct)
	PPC_LL		r0, PPC_MIN_STKFRM + PPC_LR_STKOFF(r1)
#अगर_घोषित __घातerpc64__
	PPC_LL		r2, PPC_MIN_STKFRM + STK_GOT(r1)
#पूर्ण_अगर
	cmpwi		r3, 0
	mtlr		r0
  .cfi_restore lr
	addi		r1, r1, 2 * PPC_MIN_STKFRM
	crclr		so
	beqlr+
	crset		so
	neg		r3, r3
	blr
  .cfi_endproc
.endm

.macro cvdso_call_समय funct
  .cfi_startproc
	PPC_STLU	r1, -PPC_MIN_STKFRM(r1)
	mflr		r0
  .cfi_रेजिस्टर lr, r0
	PPC_STLU	r1, -PPC_MIN_STKFRM(r1)
	PPC_STL		r0, PPC_MIN_STKFRM + PPC_LR_STKOFF(r1)
#अगर_घोषित __घातerpc64__
	PPC_STL		r2, PPC_MIN_STKFRM + STK_GOT(r1)
#पूर्ण_अगर
	get_datapage	r4
	addi		r4, r4, VDSO_DATA_OFFSET
	bl		DOTSYM(\पunct)
	PPC_LL		r0, PPC_MIN_STKFRM + PPC_LR_STKOFF(r1)
#अगर_घोषित __घातerpc64__
	PPC_LL		r2, PPC_MIN_STKFRM + STK_GOT(r1)
#पूर्ण_अगर
	crclr		so
	mtlr		r0
  .cfi_restore lr
	addi		r1, r1, 2 * PPC_MIN_STKFRM
	blr
  .cfi_endproc
.endm

#अन्यथा

#समावेश <यंत्र/vdso/समयbase.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/unistd.h>
#समावेश <uapi/linux/समय.स>

#घोषणा VDSO_HAS_CLOCK_GETRES		1

#घोषणा VDSO_HAS_TIME			1

अटल __always_अंतरभूत पूर्णांक करो_syscall_2(स्थिर अचिन्हित दीर्घ _r0, स्थिर अचिन्हित दीर्घ _r3,
					स्थिर अचिन्हित दीर्घ _r4)
अणु
	रेजिस्टर दीर्घ r0 यंत्र("r0") = _r0;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("r3") = _r3;
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("r4") = _r4;
	रेजिस्टर पूर्णांक ret यंत्र ("r3");

	यंत्र अस्थिर(
		"       sc\n"
		"	bns+	1f\n"
		"	neg	%0, %0\n"
		"1:\n"
	: "=r" (ret), "+r" (r4), "+r" (r0)
	: "r" (r3)
	: "memory", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "cr0", "ctr");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
पूर्णांक समय_लोofday_fallback(काष्ठा __kernel_old_समयval *_tv, काष्ठा समयzone *_tz)
अणु
	वापस करो_syscall_2(__NR_समय_लोofday, (अचिन्हित दीर्घ)_tv, (अचिन्हित दीर्घ)_tz);
पूर्ण

#अगर_घोषित __घातerpc64__

अटल __always_अंतरभूत
पूर्णांक घड़ी_समय_लो_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	वापस करो_syscall_2(__NR_घड़ी_समय_लो, _clkid, (अचिन्हित दीर्घ)_ts);
पूर्ण

अटल __always_अंतरभूत
पूर्णांक घड़ी_getres_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	वापस करो_syscall_2(__NR_घड़ी_getres, _clkid, (अचिन्हित दीर्घ)_ts);
पूर्ण

#अन्यथा

#घोषणा BUILD_VDSO32		1

अटल __always_अंतरभूत
पूर्णांक घड़ी_समय_लो_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	वापस करो_syscall_2(__NR_घड़ी_समय_लो64, _clkid, (अचिन्हित दीर्घ)_ts);
पूर्ण

अटल __always_अंतरभूत
पूर्णांक घड़ी_getres_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	वापस करो_syscall_2(__NR_घड़ी_getres_समय64, _clkid, (अचिन्हित दीर्घ)_ts);
पूर्ण

अटल __always_अंतरभूत
पूर्णांक घड़ी_समय_लो32_fallback(घड़ीid_t _clkid, काष्ठा old_बारpec32 *_ts)
अणु
	वापस करो_syscall_2(__NR_घड़ी_समय_लो, _clkid, (अचिन्हित दीर्घ)_ts);
पूर्ण

अटल __always_अंतरभूत
पूर्णांक घड़ी_getres32_fallback(घड़ीid_t _clkid, काष्ठा old_बारpec32 *_ts)
अणु
	वापस करो_syscall_2(__NR_घड़ी_getres, _clkid, (अचिन्हित दीर्घ)_ts);
पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत u64 __arch_get_hw_counter(s32 घड़ी_mode,
						 स्थिर काष्ठा vdso_data *vd)
अणु
	वापस get_tb();
पूर्ण

स्थिर काष्ठा vdso_data *__arch_get_vdso_data(व्योम);

#अगर_घोषित CONFIG_TIME_NS
अटल __always_अंतरभूत
स्थिर काष्ठा vdso_data *__arch_get_समयns_vdso_data(स्थिर काष्ठा vdso_data *vd)
अणु
	वापस (व्योम *)vd + PAGE_SIZE;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool vdso_घड़ीsource_ok(स्थिर काष्ठा vdso_data *vd)
अणु
	वापस true;
पूर्ण
#घोषणा vdso_घड़ीsource_ok vdso_घड़ीsource_ok

/*
 * घातerpc specअगरic delta calculation.
 *
 * This variant हटाओs the masking of the subtraction because the
 * घड़ीsource mask of all VDSO capable घड़ीsources on घातerpc is U64_MAX
 * which would result in a poपूर्णांकless operation. The compiler cannot
 * optimize it away as the mask comes from the vdso data and is not compile
 * समय स्थिरant.
 */
अटल __always_अंतरभूत u64 vdso_calc_delta(u64 cycles, u64 last, u64 mask, u32 mult)
अणु
	वापस (cycles - last) * mult;
पूर्ण
#घोषणा vdso_calc_delta vdso_calc_delta

#अगर_अघोषित __घातerpc64__
अटल __always_अंतरभूत u64 vdso_shअगरt_ns(u64 ns, अचिन्हित दीर्घ shअगरt)
अणु
	u32 hi = ns >> 32;
	u32 lo = ns;

	lo >>= shअगरt;
	lo |= hi << (32 - shअगरt);
	hi >>= shअगरt;

	अगर (likely(hi == 0))
		वापस lo;

	वापस ((u64)hi << 32) | lo;
पूर्ण
#घोषणा vdso_shअगरt_ns vdso_shअगरt_ns
#पूर्ण_अगर

#अगर_घोषित __घातerpc64__
पूर्णांक __c_kernel_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts,
			     स्थिर काष्ठा vdso_data *vd);
पूर्णांक __c_kernel_घड़ी_getres(घड़ीid_t घड़ी_id, काष्ठा __kernel_बारpec *res,
			    स्थिर काष्ठा vdso_data *vd);
#अन्यथा
पूर्णांक __c_kernel_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा old_बारpec32 *ts,
			     स्थिर काष्ठा vdso_data *vd);
पूर्णांक __c_kernel_घड़ी_समय_लो64(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts,
			       स्थिर काष्ठा vdso_data *vd);
पूर्णांक __c_kernel_घड़ी_getres(घड़ीid_t घड़ी_id, काष्ठा old_बारpec32 *res,
			    स्थिर काष्ठा vdso_data *vd);
#पूर्ण_अगर
पूर्णांक __c_kernel_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz,
			    स्थिर काष्ठा vdso_data *vd);
__kernel_old_समय_प्रकार __c_kernel_समय(__kernel_old_समय_प्रकार *समय,
				    स्थिर काष्ठा vdso_data *vd);
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_VDSO_GETTIMखातापूर्णDAY_H */
