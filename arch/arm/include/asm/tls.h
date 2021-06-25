<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASMARM_TLS_H
#घोषणा __ASMARM_TLS_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/thपढ़ो_info.h>

#अगर_घोषित __ASSEMBLY__
#समावेश <यंत्र/यंत्र-offsets.h>
	.macro चयन_tls_none, base, tp, tpuser, पंचांगp1, पंचांगp2
	.endm

	.macro चयन_tls_v6k, base, tp, tpuser, पंचांगp1, पंचांगp2
	mrc	p15, 0, \टmp2, c13, c0, 2	@ get the user r/w रेजिस्टर
	mcr	p15, 0, \टp, c13, c0, 3		@ set TLS रेजिस्टर
	mcr	p15, 0, \टpuser, c13, c0, 2	@ and the user r/w रेजिस्टर
	str	\टmp2, [\मase, #TI_TP_VALUE + 4] @ save it
	.endm

	.macro चयन_tls_v6, base, tp, tpuser, पंचांगp1, पंचांगp2
	ldr	\टmp1, =elf_hwcap
	ldr	\टmp1, [\टmp1, #0]
	mov	\टmp2, #0xffff0fff
	tst	\टmp1, #HWCAP_TLS		@ hardware TLS available?
	streq	\टp, [\टmp2, #-15]		@ set TLS value at 0xffff0ff0
	mrcne	p15, 0, \टmp2, c13, c0, 2	@ get the user r/w रेजिस्टर
	mcrne	p15, 0, \टp, c13, c0, 3		@ yes, set TLS रेजिस्टर
	mcrne	p15, 0, \टpuser, c13, c0, 2	@ set user r/w रेजिस्टर
	strne	\टmp2, [\मase, #TI_TP_VALUE + 4] @ save it
	.endm

	.macro चयन_tls_software, base, tp, tpuser, पंचांगp1, पंचांगp2
	mov	\टmp1, #0xffff0fff
	str	\टp, [\टmp1, #-15]		@ set TLS value at 0xffff0ff0
	.endm
#पूर्ण_अगर

#अगर_घोषित CONFIG_TLS_REG_EMUL
#घोषणा tls_emu		1
#घोषणा has_tls_reg		1
#घोषणा चयन_tls	चयन_tls_none
#या_अगर defined(CONFIG_CPU_V6)
#घोषणा tls_emu		0
#घोषणा has_tls_reg		(elf_hwcap & HWCAP_TLS)
#घोषणा चयन_tls	चयन_tls_v6
#या_अगर defined(CONFIG_CPU_32v6K)
#घोषणा tls_emu		0
#घोषणा has_tls_reg		1
#घोषणा चयन_tls	चयन_tls_v6k
#अन्यथा
#घोषणा tls_emu		0
#घोषणा has_tls_reg		0
#घोषणा चयन_tls	चयन_tls_software
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत व्योम set_tls(अचिन्हित दीर्घ val)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो;

	thपढ़ो = current_thपढ़ो_info();

	thपढ़ो->tp_value[0] = val;

	/*
	 * This code runs with preemption enabled and thereक्रमe must
	 * be reentrant with respect to चयन_tls.
	 *
	 * We need to ensure ordering between the shaकरोw state and the
	 * hardware state, so that we करोn't corrupt the hardware state
	 * with a stale shaकरोw state during context चयन.
	 *
	 * If we're preempted here, चयन_tls will load TPIDRURO from
	 * thपढ़ो_info upon resuming execution and the following mcr
	 * is merely redundant.
	 */
	barrier();

	अगर (!tls_emu) अणु
		अगर (has_tls_reg) अणु
			यंत्र("mcr p15, 0, %0, c13, c0, 3"
			    : : "r" (val));
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_KUSER_HELPERS
			/*
			 * User space must never try to access this
			 * directly.  Expect your app to अवरोध
			 * eventually अगर you करो so.  The user helper
			 * at 0xffff0fe0 must be used instead.  (see
			 * entry-armv.S क्रम details)
			 */
			*((अचिन्हित पूर्णांक *)0xffff0ff0) = val;
#पूर्ण_अगर
		पूर्ण

	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_tpuser(व्योम)
अणु
	अचिन्हित दीर्घ reg = 0;

	अगर (has_tls_reg && !tls_emu)
		__यंत्र__("mrc p15, 0, %0, c13, c0, 2" : "=r" (reg));

	वापस reg;
पूर्ण

अटल अंतरभूत व्योम set_tpuser(अचिन्हित दीर्घ val)
अणु
	/* Since TPIDRURW is fully context-चयनed (unlike TPIDRURO),
	 * we need not update thपढ़ो_info.
	 */
	अगर (has_tls_reg && !tls_emu) अणु
		यंत्र("mcr p15, 0, %0, c13, c0, 2"
		    : : "r" (val));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम flush_tls(व्योम)
अणु
	set_tls(0);
	set_tpuser(0);
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर	/* __ASMARM_TLS_H */
