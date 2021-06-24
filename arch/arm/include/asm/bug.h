<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASMARM_BUG_H
#घोषणा _ASMARM_BUG_H

#समावेश <linux/linkage.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/opcodes.h>

/*
 * Use a suitable undefined inकाष्ठाion to use क्रम ARM/Thumb2 bug handling.
 * We need to be careful not to conflict with those used by other modules and
 * the रेजिस्टर_undef_hook() प्रणाली.
 */
#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा BUG_INSTR_VALUE 0xde02
#घोषणा BUG_INSTR(__value) __inst_thumb16(__value)
#अन्यथा
#घोषणा BUG_INSTR_VALUE 0xe7f001f2
#घोषणा BUG_INSTR(__value) __inst_arm(__value)
#पूर्ण_अगर


#घोषणा BUG() _BUG(__खाता__, __LINE__, BUG_INSTR_VALUE)
#घोषणा _BUG(file, line, value) __BUG(file, line, value)

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE

/*
 * The extra indirection is to ensure that the __खाता__ string comes through
 * OK. Many version of gcc करो not support the यंत्र %c parameter which would be
 * preferable to this unpleasantness. We use mergeable string sections to
 * aव्योम multiple copies of the string appearing in the kernel image.
 */

#घोषणा __BUG(__file, __line, __value)				\
करो अणु								\
	यंत्र अस्थिर("1:\t" BUG_INSTR(__value) "\n"  \
		".pushsection .rodata.str, \"aMS\", %progbits, 1\n" \
		"2:\t.asciz " #__file "\n" 			\
		".popsection\n" 				\
		".pushsection __bug_table,\"aw\"\n"		\
		".align 2\n"					\
		"3:\t.word 1b, 2b\n"				\
		"\t.hword " #__line ", 0\n"			\
		".popsection");					\
	unreachable();						\
पूर्ण जबतक (0)

#अन्यथा

#घोषणा __BUG(__file, __line, __value)				\
करो अणु								\
	यंत्र अस्थिर(BUG_INSTR(__value) "\n");			\
	unreachable();						\
पूर्ण जबतक (0)
#पूर्ण_अगर  /* CONFIG_DEBUG_BUGVERBOSE */

#घोषणा HAVE_ARCH_BUG

#समावेश <यंत्र-generic/bug.h>

काष्ठा pt_regs;
व्योम die(स्थिर अक्षर *msg, काष्ठा pt_regs *regs, पूर्णांक err);

व्योम arm_notअगरy_die(स्थिर अक्षर *str, काष्ठा pt_regs *regs,
		पूर्णांक signo, पूर्णांक si_code, व्योम __user *addr,
		अचिन्हित दीर्घ err, अचिन्हित दीर्घ trap);

#अगर_घोषित CONFIG_ARM_LPAE
#घोषणा FAULT_CODE_ALIGNMENT	33
#घोषणा FAULT_CODE_DEBUG	34
#अन्यथा
#घोषणा FAULT_CODE_ALIGNMENT	1
#घोषणा FAULT_CODE_DEBUG	2
#पूर्ण_अगर

व्योम hook_fault_code(पूर्णांक nr, पूर्णांक (*fn)(अचिन्हित दीर्घ, अचिन्हित पूर्णांक,
				       काष्ठा pt_regs *),
		     पूर्णांक sig, पूर्णांक code, स्थिर अक्षर *name);

व्योम hook_अगरault_code(पूर्णांक nr, पूर्णांक (*fn)(अचिन्हित दीर्घ, अचिन्हित पूर्णांक,
				       काष्ठा pt_regs *),
		     पूर्णांक sig, पूर्णांक code, स्थिर अक्षर *name);

बाह्य यंत्रlinkage व्योम c_backtrace(अचिन्हित दीर्घ fp, पूर्णांक pmode,
				   स्थिर अक्षर *loglvl);

काष्ठा mm_काष्ठा;
व्योम show_pte(स्थिर अक्षर *lvl, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
बाह्य व्योम __show_regs(काष्ठा pt_regs *);
बाह्य व्योम __show_regs_alloc_मुक्त(काष्ठा pt_regs *regs);

#पूर्ण_अगर
