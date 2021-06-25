<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ALPHA_FPU_H
#घोषणा __ASM_ALPHA_FPU_H

#समावेश <यंत्र/special_insns.h>
#समावेश <uapi/यंत्र/fpu.h>

/* The following two functions करोn't need trapb/excb inकाष्ठाions
   around the mf_fpcr/mt_fpcr inकाष्ठाions because (a) the kernel
   never generates arithmetic faults and (b) call_pal inकाष्ठाions
   are implied trap barriers.  */

अटल अंतरभूत अचिन्हित दीर्घ
rdfpcr(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp, ret;

#अगर defined(CONFIG_ALPHA_EV6) || defined(CONFIG_ALPHA_EV67)
	__यंत्र__ __अस्थिर__ (
		"ftoit $f0,%0\n\t"
		"mf_fpcr $f0\n\t"
		"ftoit $f0,%1\n\t"
		"itoft %0,$f0"
		: "=r"(पंचांगp), "=r"(ret));
#अन्यथा
	__यंत्र__ __अस्थिर__ (
		"stt $f0,%0\n\t"
		"mf_fpcr $f0\n\t"
		"stt $f0,%1\n\t"
		"ldt $f0,%0"
		: "=m"(पंचांगp), "=m"(ret));
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
wrfpcr(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ पंचांगp;

#अगर defined(CONFIG_ALPHA_EV6) || defined(CONFIG_ALPHA_EV67)
	__यंत्र__ __अस्थिर__ (
		"ftoit $f0,%0\n\t"
		"itoft %1,$f0\n\t"
		"mt_fpcr $f0\n\t"
		"itoft %0,$f0"
		: "=&r"(पंचांगp) : "r"(val));
#अन्यथा
	__यंत्र__ __अस्थिर__ (
		"stt $f0,%0\n\t"
		"ldt $f0,%1\n\t"
		"mt_fpcr $f0\n\t"
		"ldt $f0,%0"
		: "=m"(पंचांगp) : "m"(val));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
swcr_update_status(अचिन्हित दीर्घ swcr, अचिन्हित दीर्घ fpcr)
अणु
	/* EV6 implements most of the bits in hardware.  Collect
	   the acrued exception bits from the real fpcr.  */
	अगर (implver() == IMPLVER_EV6) अणु
		swcr &= ~IEEE_STATUS_MASK;
		swcr |= (fpcr >> 35) & IEEE_STATUS_MASK;
	पूर्ण
	वापस swcr;
पूर्ण

बाह्य अचिन्हित दीर्घ alpha_पढ़ो_fp_reg (अचिन्हित दीर्घ reg);
बाह्य व्योम alpha_ग_लिखो_fp_reg (अचिन्हित दीर्घ reg, अचिन्हित दीर्घ val);
बाह्य अचिन्हित दीर्घ alpha_पढ़ो_fp_reg_s (अचिन्हित दीर्घ reg);
बाह्य व्योम alpha_ग_लिखो_fp_reg_s (अचिन्हित दीर्घ reg, अचिन्हित दीर्घ val);

#पूर्ण_अगर /* __ASM_ALPHA_FPU_H */
