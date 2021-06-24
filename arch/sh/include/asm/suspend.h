<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SH_SUSPEND_H
#घोषणा _ASM_SH_SUSPEND_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/notअगरier.h>

#समावेश <यंत्र/ptrace.h>

काष्ठा swsusp_arch_regs अणु
	काष्ठा pt_regs user_regs;
	अचिन्हित दीर्घ bank1_regs[8];
पूर्ण;

व्योम sh_mobile_call_standby(अचिन्हित दीर्घ mode);

#अगर_घोषित CONFIG_CPU_IDLE
पूर्णांक sh_mobile_setup_cpuidle(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक sh_mobile_setup_cpuidle(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* notअगरier chains क्रम pre/post sleep hooks */
बाह्य काष्ठा atomic_notअगरier_head sh_mobile_pre_sleep_notअगरier_list;
बाह्य काष्ठा atomic_notअगरier_head sh_mobile_post_sleep_notअगरier_list;

/* priority levels क्रम notअगरiers */
#घोषणा SH_MOBILE_SLEEP_BOARD	0
#घोषणा SH_MOBILE_SLEEP_CPU	1
#घोषणा SH_MOBILE_PRE(x)	(x)
#घोषणा SH_MOBILE_POST(x)	(-(x))

/* board code registration function क्रम self-refresh assembly snippets */
व्योम sh_mobile_रेजिस्टर_self_refresh(अचिन्हित दीर्घ flags,
				     व्योम *pre_start, व्योम *pre_end,
				     व्योम *post_start, व्योम *post_end);

/* रेजिस्टर काष्ठाure क्रम address/data inक्रमmation */
काष्ठा sh_sleep_regs अणु
	अचिन्हित दीर्घ stbcr;
	अचिन्हित दीर्घ bar;

	/* MMU */
	अचिन्हित दीर्घ pteh;
	अचिन्हित दीर्घ ptel;
	अचिन्हित दीर्घ ttb;
	अचिन्हित दीर्घ tea;
	अचिन्हित दीर्घ mmucr;
	अचिन्हित दीर्घ ptea;
	अचिन्हित दीर्घ pascr;
	अचिन्हित दीर्घ irmcr;

	/* Cache */
	अचिन्हित दीर्घ ccr;
	अचिन्हित दीर्घ ramcr;
पूर्ण;

/* data area क्रम low-level sleep code */
काष्ठा sh_sleep_data अणु
	/* current sleep mode (SUSP_SH_...) */
	अचिन्हित दीर्घ mode;

	/* addresses of board specअगरic self-refresh snippets */
	अचिन्हित दीर्घ sf_pre;
	अचिन्हित दीर्घ sf_post;

	/* address of resume code */
	अचिन्हित दीर्घ resume;

	/* रेजिस्टर state saved and restored by the assembly code */
	अचिन्हित दीर्घ vbr;
	अचिन्हित दीर्घ spc;
	अचिन्हित दीर्घ sr;
	अचिन्हित दीर्घ sp;

	/* काष्ठाure क्रम keeping रेजिस्टर addresses */
	काष्ठा sh_sleep_regs addr;

	/* काष्ठाure क्रम saving/restoring रेजिस्टर state */
	काष्ठा sh_sleep_regs data;
पूर्ण;

/* a biपंचांगap of supported sleep modes (SUSP_SH..) */
बाह्य अचिन्हित दीर्घ sh_mobile_sleep_supported;

#पूर्ण_अगर

/* flags passed to assembly suspend code */
#घोषणा SUSP_SH_SLEEP		(1 << 0) /* Regular sleep mode */
#घोषणा SUSP_SH_STANDBY		(1 << 1) /* SH-Mobile Software standby mode */
#घोषणा SUSP_SH_RSTANDBY	(1 << 2) /* SH-Mobile R-standby mode */
#घोषणा SUSP_SH_USTANDBY	(1 << 3) /* SH-Mobile U-standby mode */
#घोषणा SUSP_SH_SF		(1 << 4) /* Enable self-refresh */
#घोषणा SUSP_SH_MMU		(1 << 5) /* Save/restore MMU and cache */
#घोषणा SUSP_SH_REGS		(1 << 6) /* Save/restore रेजिस्टरs */

#पूर्ण_अगर /* _ASM_SH_SUSPEND_H */
