<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_VSYSCALL_H
#घोषणा _ASM_X86_VSYSCALL_H

#समावेश <linux/seqlock.h>
#समावेश <uapi/यंत्र/vsyscall.h>

#अगर_घोषित CONFIG_X86_VSYSCALL_EMULATION
बाह्य व्योम map_vsyscall(व्योम);
बाह्य व्योम set_vsyscall_pgtable_user_bits(pgd_t *root);

/*
 * Called on inकाष्ठाion fetch fault in vsyscall page.
 * Returns true अगर handled.
 */
बाह्य bool emulate_vsyscall(अचिन्हित दीर्घ error_code,
			     काष्ठा pt_regs *regs, अचिन्हित दीर्घ address);
#अन्यथा
अटल अंतरभूत व्योम map_vsyscall(व्योम) अणुपूर्ण
अटल अंतरभूत bool emulate_vsyscall(अचिन्हित दीर्घ error_code,
				    काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_VSYSCALL_H */
