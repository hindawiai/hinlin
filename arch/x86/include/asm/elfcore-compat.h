<शैली गुरु>
#अगर_अघोषित _ASM_X86_ELFCORE_COMPAT_H
#घोषणा _ASM_X86_ELFCORE_COMPAT_H

#समावेश <यंत्र/user32.h>

/*
 * On amd64 we have two 32bit ABIs - i386 and x32.  The latter
 * has bigger रेजिस्टरs, so we use it क्रम compat_elf_regset_t.
 * The क्रमmer uses i386_elf_prstatus and PRSTATUS_SIZE/SET_PR_FPVALID
 * are used to choose the size and location of ->pr_fpvalid of
 * the layout actually used.
 */
प्रकार काष्ठा user_regs_काष्ठा compat_elf_gregset_t;

काष्ठा i386_elf_prstatus
अणु
	काष्ठा compat_elf_prstatus_common	common;
	काष्ठा user_regs_काष्ठा32		pr_reg;
	compat_पूर्णांक_t			pr_fpvalid;
पूर्ण;

#घोषणा PRSTATUS_SIZE \
	(user_64bit_mode(task_pt_regs(current)) \
		? माप(काष्ठा compat_elf_prstatus) \
		: माप(काष्ठा i386_elf_prstatus))
#घोषणा SET_PR_FPVALID(S) \
	(*(user_64bit_mode(task_pt_regs(current)) \
		? &(S)->pr_fpvalid 	\
		: &((काष्ठा i386_elf_prstatus *)(S))->pr_fpvalid) = 1)

#पूर्ण_अगर
