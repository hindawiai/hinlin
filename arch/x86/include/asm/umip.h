<शैली गुरु>
#अगर_अघोषित _ASM_X86_UMIP_H
#घोषणा _ASM_X86_UMIP_H

#समावेश <linux/types.h>
#समावेश <यंत्र/ptrace.h>

#अगर_घोषित CONFIG_X86_UMIP
bool fixup_umip_exception(काष्ठा pt_regs *regs);
#अन्यथा
अटल अंतरभूत bool fixup_umip_exception(काष्ठा pt_regs *regs) अणु वापस false; पूर्ण
#पूर्ण_अगर  /* CONFIG_X86_UMIP */
#पूर्ण_अगर  /* _ASM_X86_UMIP_H */
