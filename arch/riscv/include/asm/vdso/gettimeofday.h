<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_VDSO_GETTIMखातापूर्णDAY_H
#घोषणा __ASM_VDSO_GETTIMखातापूर्णDAY_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/csr.h>
#समावेश <uapi/linux/समय.स>

#घोषणा VDSO_HAS_CLOCK_GETRES	1

अटल __always_अंतरभूत
पूर्णांक समय_लोofday_fallback(काष्ठा __kernel_old_समयval *_tv,
			  काष्ठा समयzone *_tz)
अणु
	रेजिस्टर काष्ठा __kernel_old_समयval *tv यंत्र("a0") = _tv;
	रेजिस्टर काष्ठा समयzone *tz यंत्र("a1") = _tz;
	रेजिस्टर दीर्घ ret यंत्र("a0");
	रेजिस्टर दीर्घ nr यंत्र("a7") = __NR_समय_लोofday;

	यंत्र अस्थिर ("ecall\n"
		      : "=r" (ret)
		      : "r"(tv), "r"(tz), "r"(nr)
		      : "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
दीर्घ घड़ी_समय_लो_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	रेजिस्टर घड़ीid_t clkid यंत्र("a0") = _clkid;
	रेजिस्टर काष्ठा __kernel_बारpec *ts यंत्र("a1") = _ts;
	रेजिस्टर दीर्घ ret यंत्र("a0");
	रेजिस्टर दीर्घ nr यंत्र("a7") = __NR_घड़ी_समय_लो;

	यंत्र अस्थिर ("ecall\n"
		      : "=r" (ret)
		      : "r"(clkid), "r"(ts), "r"(nr)
		      : "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
पूर्णांक घड़ी_getres_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	रेजिस्टर घड़ीid_t clkid यंत्र("a0") = _clkid;
	रेजिस्टर काष्ठा __kernel_बारpec *ts यंत्र("a1") = _ts;
	रेजिस्टर दीर्घ ret यंत्र("a0");
	रेजिस्टर दीर्घ nr यंत्र("a7") = __NR_घड़ी_getres;

	यंत्र अस्थिर ("ecall\n"
		      : "=r" (ret)
		      : "r"(clkid), "r"(ts), "r"(nr)
		      : "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत u64 __arch_get_hw_counter(s32 घड़ी_mode,
						 स्थिर काष्ठा vdso_data *vd)
अणु
	/*
	 * The purpose of csr_पढ़ो(CSR_TIME) is to trap the प्रणाली पूर्णांकo
	 * M-mode to obtain the value of CSR_TIME. Hence, unlike other
	 * architecture, no fence inकाष्ठाions surround the csr_पढ़ो()
	 */
	वापस csr_पढ़ो(CSR_TIME);
पूर्ण

अटल __always_अंतरभूत स्थिर काष्ठा vdso_data *__arch_get_vdso_data(व्योम)
अणु
	वापस _vdso_data;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_GETTIMखातापूर्णDAY_H */
