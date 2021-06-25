<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_KUP_8XX_H_
#घोषणा _ASM_POWERPC_KUP_8XX_H_

#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/mmu.h>

#अगर_घोषित CONFIG_PPC_KUAP

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/reg.h>

अटल अंतरभूत व्योम kuap_save_and_lock(काष्ठा pt_regs *regs)
अणु
	regs->kuap = mfspr(SPRN_MD_AP);
	mtspr(SPRN_MD_AP, MD_APG_KUAP);
पूर्ण

अटल अंतरभूत व्योम kuap_user_restore(काष्ठा pt_regs *regs)
अणु
पूर्ण

अटल अंतरभूत व्योम kuap_kernel_restore(काष्ठा pt_regs *regs, अचिन्हित दीर्घ kuap)
अणु
	mtspr(SPRN_MD_AP, regs->kuap);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kuap_get_and_निश्चित_locked(व्योम)
अणु
	अचिन्हित दीर्घ kuap = mfspr(SPRN_MD_AP);

	अगर (IS_ENABLED(CONFIG_PPC_KUAP_DEBUG))
		WARN_ON_ONCE(kuap >> 16 != MD_APG_KUAP >> 16);

	वापस kuap;
पूर्ण

अटल अंतरभूत व्योम kuap_निश्चित_locked(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_PPC_KUAP_DEBUG))
		kuap_get_and_निश्चित_locked();
पूर्ण

अटल अंतरभूत व्योम allow_user_access(व्योम __user *to, स्थिर व्योम __user *from,
				     अचिन्हित दीर्घ size, अचिन्हित दीर्घ dir)
अणु
	mtspr(SPRN_MD_AP, MD_APG_INIT);
पूर्ण

अटल अंतरभूत व्योम prevent_user_access(व्योम __user *to, स्थिर व्योम __user *from,
				       अचिन्हित दीर्घ size, अचिन्हित दीर्घ dir)
अणु
	mtspr(SPRN_MD_AP, MD_APG_KUAP);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ prevent_user_access_वापस(व्योम)
अणु
	अचिन्हित दीर्घ flags = mfspr(SPRN_MD_AP);

	mtspr(SPRN_MD_AP, MD_APG_KUAP);

	वापस flags;
पूर्ण

अटल अंतरभूत व्योम restore_user_access(अचिन्हित दीर्घ flags)
अणु
	mtspr(SPRN_MD_AP, flags);
पूर्ण

अटल अंतरभूत bool
bad_kuap_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address, bool is_ग_लिखो)
अणु
	वापस !((regs->kuap ^ MD_APG_KUAP) & 0xff000000);
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* CONFIG_PPC_KUAP */

#पूर्ण_अगर /* _ASM_POWERPC_KUP_8XX_H_ */
