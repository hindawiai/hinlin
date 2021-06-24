<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PVCLOCK_H
#घोषणा _ASM_X86_PVCLOCK_H

#समावेश <यंत्र/घड़ीsource.h>
#समावेश <यंत्र/pvघड़ी-abi.h>

/* some helper functions क्रम xen and kvm pv घड़ी sources */
u64 pvघड़ी_घड़ीsource_पढ़ो(काष्ठा pvघड़ी_vcpu_समय_info *src);
u8 pvघड़ी_पढ़ो_flags(काष्ठा pvघड़ी_vcpu_समय_info *src);
व्योम pvघड़ी_set_flags(u8 flags);
अचिन्हित दीर्घ pvघड़ी_प्रकारsc_khz(काष्ठा pvघड़ी_vcpu_समय_info *src);
व्योम pvघड़ी_पढ़ो_wallघड़ी(काष्ठा pvघड़ी_wall_घड़ी *wall,
			    काष्ठा pvघड़ी_vcpu_समय_info *vcpu,
			    काष्ठा बारpec64 *ts);
व्योम pvघड़ी_resume(व्योम);

व्योम pvघड़ी_प्रकारouch_watchकरोgs(व्योम);

अटल __always_अंतरभूत
अचिन्हित pvघड़ी_पढ़ो_begin(स्थिर काष्ठा pvघड़ी_vcpu_समय_info *src)
अणु
	अचिन्हित version = src->version & ~1;
	/* Make sure that the version is पढ़ो beक्रमe the data. */
	virt_rmb();
	वापस version;
पूर्ण

अटल __always_अंतरभूत
bool pvघड़ी_पढ़ो_retry(स्थिर काष्ठा pvघड़ी_vcpu_समय_info *src,
			अचिन्हित version)
अणु
	/* Make sure that the version is re-पढ़ो after the data. */
	virt_rmb();
	वापस unlikely(version != src->version);
पूर्ण

/*
 * Scale a 64-bit delta by scaling and multiplying by a 32-bit fraction,
 * yielding a 64-bit result.
 */
अटल अंतरभूत u64 pvघड़ी_scale_delta(u64 delta, u32 mul_frac, पूर्णांक shअगरt)
अणु
	u64 product;
#अगर_घोषित __i386__
	u32 पंचांगp1, पंचांगp2;
#अन्यथा
	uदीर्घ पंचांगp;
#पूर्ण_अगर

	अगर (shअगरt < 0)
		delta >>= -shअगरt;
	अन्यथा
		delta <<= shअगरt;

#अगर_घोषित __i386__
	__यंत्र__ (
		"mul  %5       ; "
		"mov  %4,%%eax ; "
		"mov  %%edx,%4 ; "
		"mul  %5       ; "
		"xor  %5,%5    ; "
		"add  %4,%%eax ; "
		"adc  %5,%%edx ; "
		: "=A" (product), "=r" (पंचांगp1), "=r" (पंचांगp2)
		: "a" ((u32)delta), "1" ((u32)(delta >> 32)), "2" (mul_frac) );
#या_अगर defined(__x86_64__)
	__यंत्र__ (
		"mulq %[mul_frac] ; shrd $32, %[hi], %[lo]"
		: [lo]"=a"(product),
		  [hi]"=d"(पंचांगp)
		: "0"(delta),
		  [mul_frac]"rm"((u64)mul_frac));
#अन्यथा
#त्रुटि implement me!
#पूर्ण_अगर

	वापस product;
पूर्ण

अटल __always_अंतरभूत
u64 __pvघड़ी_पढ़ो_cycles(स्थिर काष्ठा pvघड़ी_vcpu_समय_info *src, u64 tsc)
अणु
	u64 delta = tsc - src->tsc_बारtamp;
	u64 offset = pvघड़ी_scale_delta(delta, src->tsc_to_प्रणाली_mul,
					     src->tsc_shअगरt);
	वापस src->प्रणाली_समय + offset;
पूर्ण

काष्ठा pvघड़ी_vsyscall_समय_info अणु
	काष्ठा pvघड़ी_vcpu_समय_info pvti;
पूर्ण __attribute__((__aligned__(SMP_CACHE_BYTES)));

#घोषणा PVTI_SIZE माप(काष्ठा pvघड़ी_vsyscall_समय_info)

#अगर_घोषित CONFIG_PARAVIRT_CLOCK
व्योम pvघड़ी_set_pvti_cpu0_va(काष्ठा pvघड़ी_vsyscall_समय_info *pvti);
काष्ठा pvघड़ी_vsyscall_समय_info *pvघड़ी_get_pvti_cpu0_va(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा pvघड़ी_vsyscall_समय_info *pvघड़ी_get_pvti_cpu0_va(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_PVCLOCK_H */
