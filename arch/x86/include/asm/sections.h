<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SECTIONS_H
#घोषणा _ASM_X86_SECTIONS_H

#घोषणा arch_is_kernel_iniपंचांगem_मुक्तd arch_is_kernel_iniपंचांगem_मुक्तd

#समावेश <यंत्र-generic/sections.h>
#समावेश <यंत्र/extable.h>

बाह्य अक्षर __brk_base[], __brk_limit[];
बाह्य अक्षर __end_rodata_aligned[];

#अगर defined(CONFIG_X86_64)
बाह्य अक्षर __end_rodata_hpage_align[];
#पूर्ण_अगर

बाह्य अक्षर __end_of_kernel_reserve[];

बाह्य अचिन्हित दीर्घ _brk_start, _brk_end;

अटल अंतरभूत bool arch_is_kernel_iniपंचांगem_मुक्तd(अचिन्हित दीर्घ addr)
अणु
	/*
	 * If _brk_start has not been cleared, brk allocation is incomplete,
	 * and we can not make assumptions about its use.
	 */
	अगर (_brk_start)
		वापस 0;

	/*
	 * After brk allocation is complete, space between _brk_end and _end
	 * is available क्रम allocation.
	 */
	वापस addr >= _brk_end && addr < (अचिन्हित दीर्घ)&_end;
पूर्ण

#पूर्ण_अगर	/* _ASM_X86_SECTIONS_H */
