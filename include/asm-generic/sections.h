<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_SECTIONS_H_
#घोषणा _ASM_GENERIC_SECTIONS_H_

/* References to section boundaries */

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

/*
 * Usage guidelines:
 * _text, _data: architecture specअगरic, करोn't use them in arch-independent code
 * [_stext, _etext]: contains .text.* sections, may also contain .rodata.*
 *                   and/or .init.* sections
 * [_sdata, _edata]: contains .data.* sections, may also contain .rodata.*
 *                   and/or .init.* sections.
 * [__start_rodata, __end_rodata]: contains .rodata.* sections
 * [__start_ro_after_init, __end_ro_after_init]:
 *		     contains .data..ro_after_init section
 * [__init_begin, __init_end]: contains .init.* sections, but .init.text.*
 *                   may be out of this range on some architectures.
 * [_sinittext, _einittext]: contains .init.text.* sections
 * [__bss_start, __bss_stop]: contains BSS sections
 *
 * Following global variables are optional and may be unavailable on some
 * architectures and/or kernel configurations.
 *	_text, _data
 *	__kprobes_text_start, __kprobes_text_end
 *	__entry_text_start, __entry_text_end
 *	__ctors_start, __ctors_end
 *	__irqentry_text_start, __irqentry_text_end
 *	__softirqentry_text_start, __softirqentry_text_end
 *	__start_opd, __end_opd
 */
बाह्य अक्षर _text[], _stext[], _etext[];
बाह्य अक्षर _data[], _sdata[], _edata[];
बाह्य अक्षर __bss_start[], __bss_stop[];
बाह्य अक्षर __init_begin[], __init_end[];
बाह्य अक्षर _sinittext[], _einittext[];
बाह्य अक्षर __start_ro_after_init[], __end_ro_after_init[];
बाह्य अक्षर _end[];
बाह्य अक्षर __per_cpu_load[], __per_cpu_start[], __per_cpu_end[];
बाह्य अक्षर __kprobes_text_start[], __kprobes_text_end[];
बाह्य अक्षर __entry_text_start[], __entry_text_end[];
बाह्य अक्षर __start_rodata[], __end_rodata[];
बाह्य अक्षर __irqentry_text_start[], __irqentry_text_end[];
बाह्य अक्षर __softirqentry_text_start[], __softirqentry_text_end[];
बाह्य अक्षर __start_once[], __end_once[];

/* Start and end of .ctors section - used क्रम स्थिरructor calls. */
बाह्य अक्षर __ctors_start[], __ctors_end[];

/* Start and end of .opd section - used क्रम function descriptors. */
बाह्य अक्षर __start_opd[], __end_opd[];

/* Start and end of instrumentation रक्षित text section */
बाह्य अक्षर __noinstr_text_start[], __noinstr_text_end[];

बाह्य __visible स्थिर व्योम __nosave_begin, __nosave_end;

/* Function descriptor handling (अगर any).  Override in यंत्र/sections.h */
#अगर_अघोषित dereference_function_descriptor
#घोषणा dereference_function_descriptor(p) ((व्योम *)(p))
#घोषणा dereference_kernel_function_descriptor(p) ((व्योम *)(p))
#पूर्ण_अगर

/* अक्रमom extra sections (अगर any).  Override
 * in यंत्र/sections.h */
#अगर_अघोषित arch_is_kernel_text
अटल अंतरभूत पूर्णांक arch_is_kernel_text(अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_is_kernel_data
अटल अंतरभूत पूर्णांक arch_is_kernel_data(अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Check अगर an address is part of मुक्तd iniपंचांगem. This is needed on architectures
 * with virt == phys kernel mapping, क्रम code that wants to check अगर an address
 * is part of a अटल object within [_stext, _end]. After iniपंचांगem is मुक्तd,
 * memory can be allocated from it, and such allocations would then have
 * addresses within the range [_stext, _end].
 */
#अगर_अघोषित arch_is_kernel_iniपंचांगem_मुक्तd
अटल अंतरभूत पूर्णांक arch_is_kernel_iniपंचांगem_मुक्तd(अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * memory_contains - checks अगर an object is contained within a memory region
 * @begin: भव address of the beginning of the memory region
 * @end: भव address of the end of the memory region
 * @virt: भव address of the memory object
 * @size: size of the memory object
 *
 * Returns: true अगर the object specअगरied by @virt and @size is entirely
 * contained within the memory region defined by @begin and @end, false
 * otherwise.
 */
अटल अंतरभूत bool memory_contains(व्योम *begin, व्योम *end, व्योम *virt,
				   माप_प्रकार size)
अणु
	वापस virt >= begin && virt + size <= end;
पूर्ण

/**
 * memory_पूर्णांकersects - checks अगर the region occupied by an object पूर्णांकersects
 *                     with another memory region
 * @begin: भव address of the beginning of the memory regien
 * @end: भव address of the end of the memory region
 * @virt: भव address of the memory object
 * @size: size of the memory object
 *
 * Returns: true अगर an object's memory region, specअगरied by @virt and @size,
 * पूर्णांकersects with the region specअगरied by @begin and @end, false otherwise.
 */
अटल अंतरभूत bool memory_पूर्णांकersects(व्योम *begin, व्योम *end, व्योम *virt,
				     माप_प्रकार size)
अणु
	व्योम *vend = virt + size;

	वापस (virt >= begin && virt < end) || (vend >= begin && vend < end);
पूर्ण

/**
 * init_section_contains - checks अगर an object is contained within the init
 *                         section
 * @virt: भव address of the memory object
 * @size: size of the memory object
 *
 * Returns: true अगर the object specअगरied by @virt and @size is entirely
 * contained within the init section, false otherwise.
 */
अटल अंतरभूत bool init_section_contains(व्योम *virt, माप_प्रकार size)
अणु
	वापस memory_contains(__init_begin, __init_end, virt, size);
पूर्ण

/**
 * init_section_पूर्णांकersects - checks अगर the region occupied by an object
 *                           पूर्णांकersects with the init section
 * @virt: भव address of the memory object
 * @size: size of the memory object
 *
 * Returns: true अगर an object's memory region, specअगरied by @virt and @size,
 * पूर्णांकersects with the init section, false otherwise.
 */
अटल अंतरभूत bool init_section_पूर्णांकersects(व्योम *virt, माप_प्रकार size)
अणु
	वापस memory_पूर्णांकersects(__init_begin, __init_end, virt, size);
पूर्ण

/**
 * is_kernel_rodata - checks अगर the poपूर्णांकer address is located in the
 *                    .rodata section
 *
 * @addr: address to check
 *
 * Returns: true अगर the address is located in .rodata, false otherwise.
 */
अटल अंतरभूत bool is_kernel_rodata(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= (अचिन्हित दीर्घ)__start_rodata &&
	       addr < (अचिन्हित दीर्घ)__end_rodata;
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_SECTIONS_H_ */
