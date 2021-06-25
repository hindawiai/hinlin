<शैली गुरु>
#अगर_अघोषित _ASM_MIPS_ELFCORE_COMPAT_H
#घोषणा _ASM_MIPS_ELFCORE_COMPAT_H

/*
 * On mips we have two 32bit ABIs - o32 and n32.  The latter
 * has bigger रेजिस्टरs, so we use it क्रम compat_elf_regset_t.
 * The क्रमmer uses o32_elf_prstatus and PRSTATUS_SIZE/SET_PR_FPVALID
 * are used to choose the size and location of ->pr_fpvalid of
 * the layout actually used.
 */
प्रकार elf_gregset_t compat_elf_gregset_t;

काष्ठा o32_elf_prstatus
अणु
	काष्ठा compat_elf_prstatus_common	common;
	अचिन्हित पूर्णांक 			pr_reg[ELF_NGREG];
	compat_पूर्णांक_t			pr_fpvalid;
पूर्ण;

#घोषणा PRSTATUS_SIZE \
	(!test_thपढ़ो_flag(TIF_32BIT_REGS) \
		? माप(काष्ठा compat_elf_prstatus) \
		: माप(काष्ठा o32_elf_prstatus))
#घोषणा SET_PR_FPVALID(S) \
	(*(!test_thपढ़ो_flag(TIF_32BIT_REGS) \
		? &(S)->pr_fpvalid 	\
		: &((काष्ठा o32_elf_prstatus *)(S))->pr_fpvalid) = 1)

#पूर्ण_अगर
