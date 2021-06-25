<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ldt.h
 *
 * Definitions of काष्ठाures used with the modअगरy_ldt प्रणाली call.
 */
#अगर_अघोषित _ASM_X86_LDT_H
#घोषणा _ASM_X86_LDT_H

/* Maximum number of LDT entries supported. */
#घोषणा LDT_ENTRIES	8192
/* The size of each LDT entry. */
#घोषणा LDT_ENTRY_SIZE	8

#अगर_अघोषित __ASSEMBLY__
/*
 * Note on 64bit base and limit is ignored and you cannot set DS/ES/CS
 * not to the शेष values अगर you still want to करो syscalls. This
 * call is more क्रम 32bit mode thereक्रमe.
 */
काष्ठा user_desc अणु
	अचिन्हित पूर्णांक  entry_number;
	अचिन्हित पूर्णांक  base_addr;
	अचिन्हित पूर्णांक  limit;
	अचिन्हित पूर्णांक  seg_32bit:1;
	अचिन्हित पूर्णांक  contents:2;
	अचिन्हित पूर्णांक  पढ़ो_exec_only:1;
	अचिन्हित पूर्णांक  limit_in_pages:1;
	अचिन्हित पूर्णांक  seg_not_present:1;
	अचिन्हित पूर्णांक  useable:1;
#अगर_घोषित __x86_64__
	/*
	 * Because this bit is not present in 32-bit user code, user
	 * programs can pass uninitialized values here.  Thereक्रमe, in
	 * any context in which a user_desc comes from a 32-bit program,
	 * the kernel must act as though lm == 0, regardless of the
	 * actual value.
	 */
	अचिन्हित पूर्णांक  lm:1;
#पूर्ण_अगर
पूर्ण;

#घोषणा MODIFY_LDT_CONTENTS_DATA	0
#घोषणा MODIFY_LDT_CONTENTS_STACK	1
#घोषणा MODIFY_LDT_CONTENTS_CODE	2

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_LDT_H */
