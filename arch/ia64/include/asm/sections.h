<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_SECTIONS_H
#घोषणा _ASM_IA64_SECTIONS_H

/*
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

#समावेश <linux/elf.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र-generic/sections.h>

बाह्य अक्षर __phys_per_cpu_start[];
#अगर_घोषित	CONFIG_SMP
बाह्य अक्षर __cpu0_per_cpu[];
#पूर्ण_अगर
बाह्य अक्षर __start___vtop_patchlist[], __end___vtop_patchlist[];
बाह्य अक्षर __start___rse_patchlist[], __end___rse_patchlist[];
बाह्य अक्षर __start___mckinley_e9_bundles[], __end___mckinley_e9_bundles[];
बाह्य अक्षर __start___phys_stack_reg_patchlist[], __end___phys_stack_reg_patchlist[];
बाह्य अक्षर __start_gate_section[];
बाह्य अक्षर __start_gate_mckinley_e9_patchlist[], __end_gate_mckinley_e9_patchlist[];
बाह्य अक्षर __start_gate_vtop_patchlist[], __end_gate_vtop_patchlist[];
बाह्य अक्षर __start_gate_fsyscall_patchlist[], __end_gate_fsyscall_patchlist[];
बाह्य अक्षर __start_gate_brl_fsys_bubble_करोwn_patchlist[], __end_gate_brl_fsys_bubble_करोwn_patchlist[];
बाह्य अक्षर __start_unwind[], __end_unwind[];
बाह्य अक्षर __start_ivt_text[], __end_ivt_text[];

#घोषणा HAVE_DEREFERENCE_FUNCTION_DESCRIPTOR 1

#अघोषित dereference_function_descriptor
अटल अंतरभूत व्योम *dereference_function_descriptor(व्योम *ptr)
अणु
	काष्ठा fdesc *desc = ptr;
	व्योम *p;

	अगर (!get_kernel_nofault(p, (व्योम *)&desc->ip))
		ptr = p;
	वापस ptr;
पूर्ण

#अघोषित dereference_kernel_function_descriptor
अटल अंतरभूत व्योम *dereference_kernel_function_descriptor(व्योम *ptr)
अणु
	अगर (ptr < (व्योम *)__start_opd || ptr >= (व्योम *)__end_opd)
		वापस ptr;
	वापस dereference_function_descriptor(ptr);
पूर्ण

#पूर्ण_अगर /* _ASM_IA64_SECTIONS_H */
