<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_ALIGNMENT_H
#घोषणा __ASM_SH_ALIGNMENT_H

#समावेश <linux/types.h>

बाह्य व्योम inc_unaligned_byte_access(व्योम);
बाह्य व्योम inc_unaligned_word_access(व्योम);
बाह्य व्योम inc_unaligned_dword_access(व्योम);
बाह्य व्योम inc_unaligned_multi_access(व्योम);
बाह्य व्योम inc_unaligned_user_access(व्योम);
बाह्य व्योम inc_unaligned_kernel_access(व्योम);

#घोषणा UM_WARN		(1 << 0)
#घोषणा UM_FIXUP	(1 << 1)
#घोषणा UM_SIGNAL	(1 << 2)

बाह्य अचिन्हित पूर्णांक unaligned_user_action(व्योम);

बाह्य व्योम unaligned_fixups_notअगरy(काष्ठा task_काष्ठा *, insn_माप_प्रकार, काष्ठा pt_regs *);

#पूर्ण_अगर /* __ASM_SH_ALIGNMENT_H */
