<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_KUP_H_
#घोषणा _ASM_POWERPC_KUP_H_

#घोषणा KUAP_READ	1
#घोषणा KUAP_WRITE	2
#घोषणा KUAP_READ_WRITE	(KUAP_READ | KUAP_WRITE)
/*
 * For prevent_user_access() only.
 * Use the current saved situation instead of the to/from/size params.
 * Used on book3s/32
 */
#घोषणा KUAP_CURRENT_READ	4
#घोषणा KUAP_CURRENT_WRITE	8
#घोषणा KUAP_CURRENT		(KUAP_CURRENT_READ | KUAP_CURRENT_WRITE)

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#समावेश <यंत्र/book3s/64/kup.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_8xx
#समावेश <यंत्र/nohash/32/kup-8xx.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_32
#समावेश <यंत्र/book3s/32/kup.h>
#पूर्ण_अगर

#अगर_घोषित __ASSEMBLY__
#अगर_अघोषित CONFIG_PPC_KUAP
.macro kuap_check_amr	gpr1, gpr2
.endm

#पूर्ण_अगर

#अन्यथा /* !__ASSEMBLY__ */

बाह्य bool disable_kuep;
बाह्य bool disable_kuap;

#समावेश <linux/pgtable.h>

#अगर_घोषित CONFIG_PPC_KUEP
व्योम setup_kuep(bool disabled);
#अन्यथा
अटल अंतरभूत व्योम setup_kuep(bool disabled) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_KUEP */

#अगर defined(CONFIG_PPC_KUEP) && defined(CONFIG_PPC_BOOK3S_32)
व्योम kuep_lock(व्योम);
व्योम kuep_unlock(व्योम);
#अन्यथा
अटल अंतरभूत व्योम kuep_lock(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kuep_unlock(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_KUAP
व्योम setup_kuap(bool disabled);
#अन्यथा
अटल अंतरभूत व्योम setup_kuap(bool disabled) अणु पूर्ण

अटल अंतरभूत bool
bad_kuap_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address, bool is_ग_लिखो)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम kuap_निश्चित_locked(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kuap_save_and_lock(काष्ठा pt_regs *regs) अणु पूर्ण
अटल अंतरभूत व्योम kuap_user_restore(काष्ठा pt_regs *regs) अणु पूर्ण
अटल अंतरभूत व्योम kuap_kernel_restore(काष्ठा pt_regs *regs, अचिन्हित दीर्घ amr) अणु पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kuap_get_and_निश्चित_locked(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * book3s/64/kup-radix.h defines these functions क्रम the !KUAP हाल to flush
 * the L1D cache after user accesses. Only include the empty stubs क्रम other
 * platक्रमms.
 */
#अगर_अघोषित CONFIG_PPC_BOOK3S_64
अटल अंतरभूत व्योम allow_user_access(व्योम __user *to, स्थिर व्योम __user *from,
				     अचिन्हित दीर्घ size, अचिन्हित दीर्घ dir) अणु पूर्ण
अटल अंतरभूत व्योम prevent_user_access(व्योम __user *to, स्थिर व्योम __user *from,
				       अचिन्हित दीर्घ size, अचिन्हित दीर्घ dir) अणु पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ prevent_user_access_वापस(व्योम) अणु वापस 0UL; पूर्ण
अटल अंतरभूत व्योम restore_user_access(अचिन्हित दीर्घ flags) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */
#पूर्ण_अगर /* CONFIG_PPC_KUAP */

अटल __always_अंतरभूत व्योम setup_kup(व्योम)
अणु
	setup_kuep(disable_kuep);
	setup_kuap(disable_kuap);
पूर्ण

अटल अंतरभूत व्योम allow_पढ़ो_from_user(स्थिर व्योम __user *from, अचिन्हित दीर्घ size)
अणु
	barrier_nospec();
	allow_user_access(शून्य, from, size, KUAP_READ);
पूर्ण

अटल अंतरभूत व्योम allow_ग_लिखो_to_user(व्योम __user *to, अचिन्हित दीर्घ size)
अणु
	allow_user_access(to, शून्य, size, KUAP_WRITE);
पूर्ण

अटल अंतरभूत व्योम allow_पढ़ो_ग_लिखो_user(व्योम __user *to, स्थिर व्योम __user *from,
					 अचिन्हित दीर्घ size)
अणु
	barrier_nospec();
	allow_user_access(to, from, size, KUAP_READ_WRITE);
पूर्ण

अटल अंतरभूत व्योम prevent_पढ़ो_from_user(स्थिर व्योम __user *from, अचिन्हित दीर्घ size)
अणु
	prevent_user_access(शून्य, from, size, KUAP_READ);
पूर्ण

अटल अंतरभूत व्योम prevent_ग_लिखो_to_user(व्योम __user *to, अचिन्हित दीर्घ size)
अणु
	prevent_user_access(to, शून्य, size, KUAP_WRITE);
पूर्ण

अटल अंतरभूत व्योम prevent_पढ़ो_ग_लिखो_user(व्योम __user *to, स्थिर व्योम __user *from,
					   अचिन्हित दीर्घ size)
अणु
	prevent_user_access(to, from, size, KUAP_READ_WRITE);
पूर्ण

अटल अंतरभूत व्योम prevent_current_access_user(व्योम)
अणु
	prevent_user_access(शून्य, शून्य, ~0UL, KUAP_CURRENT);
पूर्ण

अटल अंतरभूत व्योम prevent_current_पढ़ो_from_user(व्योम)
अणु
	prevent_user_access(शून्य, शून्य, ~0UL, KUAP_CURRENT_READ);
पूर्ण

अटल अंतरभूत व्योम prevent_current_ग_लिखो_to_user(व्योम)
अणु
	prevent_user_access(शून्य, शून्य, ~0UL, KUAP_CURRENT_WRITE);
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_KUAP_H_ */
