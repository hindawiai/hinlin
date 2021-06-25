<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_EFI_H
#घोषणा _ASM_X86_EFI_H

#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/processor-flags.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pgtable.h>

बाह्य अचिन्हित दीर्घ efi_fw_venकरोr, efi_config_table;
बाह्य अचिन्हित दीर्घ efi_mixed_mode_stack_pa;

/*
 * We map the EFI regions needed क्रम runसमय services non-contiguously,
 * with preserved alignment on भव addresses starting from -4G करोwn
 * क्रम a total max space of 64G. This way, we provide क्रम stable runसमय
 * services addresses across kernels so that a kexec'd kernel can still
 * use them.
 *
 * This is the मुख्य reason why we're करोing stable VA mappings क्रम RT
 * services.
 */

#घोषणा EFI32_LOADER_SIGNATURE	"EL32"
#घोषणा EFI64_LOADER_SIGNATURE	"EL64"

#घोषणा ARCH_EFI_IRQ_FLAGS_MASK	X86_EFLAGS_IF

/*
 * The EFI services are called through variadic functions in many हालs. These
 * functions are implemented in assembler and support only a fixed number of
 * arguments. The macros below allows us to check at build समय that we करोn't
 * try to call them with too many arguments.
 *
 * __efi_nargs() will वापस the number of arguments अगर it is 7 or less, and
 * cause a BUILD_BUG otherwise. The limitations of the C preprocessor make it
 * impossible to calculate the exact number of arguments beyond some
 * pre-defined limit. The maximum number of arguments currently supported by
 * any of the thunks is 7, so this is good enough क्रम now and can be extended
 * in the obvious way अगर we ever need more.
 */

#घोषणा __efi_nargs(...) __efi_nargs_(__VA_ARGS__)
#घोषणा __efi_nargs_(...) __efi_nargs__(0, ##__VA_ARGS__,	\
	__efi_arg_sentinel(7), __efi_arg_sentinel(6),		\
	__efi_arg_sentinel(5), __efi_arg_sentinel(4),		\
	__efi_arg_sentinel(3), __efi_arg_sentinel(2),		\
	__efi_arg_sentinel(1), __efi_arg_sentinel(0))
#घोषणा __efi_nargs__(_0, _1, _2, _3, _4, _5, _6, _7, n, ...)	\
	__take_second_arg(n,					\
		(अणु BUILD_BUG_ON_MSG(1, "__efi_nargs limit exceeded"); 8; पूर्ण))
#घोषणा __efi_arg_sentinel(n) , n

/*
 * __efi_nargs_check(f, n, ...) will cause a BUILD_BUG अगर the ellipsis
 * represents more than n arguments.
 */

#घोषणा __efi_nargs_check(f, n, ...)					\
	__efi_nargs_check_(f, __efi_nargs(__VA_ARGS__), n)
#घोषणा __efi_nargs_check_(f, p, n) __efi_nargs_check__(f, p, n)
#घोषणा __efi_nargs_check__(f, p, n) (अणु					\
	BUILD_BUG_ON_MSG(						\
		(p) > (n),						\
		#f " called with too many arguments (" #p ">" #n ")");	\
पूर्ण)

अटल अंतरभूत व्योम efi_fpu_begin(व्योम)
अणु
	/*
	 * The UEFI calling convention (UEFI spec 2.3.2 and 2.3.4) requires
	 * that FCW and MXCSR (64-bit) must be initialized prior to calling
	 * UEFI code.  (Oddly the spec करोes not require that the FPU stack
	 * be empty.)
	 */
	kernel_fpu_begin_mask(KFPU_387 | KFPU_MXCSR);
पूर्ण

अटल अंतरभूत व्योम efi_fpu_end(व्योम)
अणु
	kernel_fpu_end();
पूर्ण

#अगर_घोषित CONFIG_X86_32
#घोषणा arch_efi_call_virt_setup()					\
(अणु									\
	efi_fpu_begin();						\
	firmware_restrict_branch_speculation_start();			\
पूर्ण)

#घोषणा arch_efi_call_virt_tearकरोwn()					\
(अणु									\
	firmware_restrict_branch_speculation_end();			\
	efi_fpu_end();							\
पूर्ण)

#घोषणा arch_efi_call_virt(p, f, args...)	p->f(args)

#अन्यथा /* !CONFIG_X86_32 */

#घोषणा EFI_LOADER_SIGNATURE	"EL64"

बाह्य यंत्रlinkage u64 __efi_call(व्योम *fp, ...);

#घोषणा efi_call(...) (अणु						\
	__efi_nargs_check(efi_call, 7, __VA_ARGS__);			\
	__efi_call(__VA_ARGS__);					\
पूर्ण)

#घोषणा arch_efi_call_virt_setup()					\
(अणु									\
	efi_sync_low_kernel_mappings();					\
	efi_fpu_begin();						\
	firmware_restrict_branch_speculation_start();			\
	efi_enter_mm();							\
पूर्ण)

#घोषणा arch_efi_call_virt(p, f, args...)				\
	efi_call((व्योम *)p->f, args)					\

#घोषणा arch_efi_call_virt_tearकरोwn()					\
(अणु									\
	efi_leave_mm();							\
	firmware_restrict_branch_speculation_end();			\
	efi_fpu_end();							\
पूर्ण)

#अगर_घोषित CONFIG_KASAN
/*
 * CONFIG_KASAN may redefine स_रखो to __स_रखो.  __स_रखो function is present
 * only in kernel binary.  Since the EFI stub linked पूर्णांकo a separate binary it
 * करोesn't have __स_रखो().  So we should use standard स_रखो from
 * arch/x86/boot/compressed/string.c.  The same applies to स_नकल and स_हटाओ.
 */
#अघोषित स_नकल
#अघोषित स_रखो
#अघोषित स_हटाओ
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_X86_32 */

बाह्य पूर्णांक __init efi_memblock_x86_reserve_range(व्योम);
बाह्य व्योम __init efi_prपूर्णांक_memmap(व्योम);
बाह्य व्योम __init efi_map_region(efi_memory_desc_t *md);
बाह्य व्योम __init efi_map_region_fixed(efi_memory_desc_t *md);
बाह्य व्योम efi_sync_low_kernel_mappings(व्योम);
बाह्य पूर्णांक __init efi_alloc_page_tables(व्योम);
बाह्य पूर्णांक __init efi_setup_page_tables(अचिन्हित दीर्घ pa_memmap, अचिन्हित num_pages);
बाह्य व्योम __init efi_runसमय_update_mappings(व्योम);
बाह्य व्योम __init efi_dump_pagetable(व्योम);
बाह्य व्योम __init efi_apply_memmap_quirks(व्योम);
बाह्य पूर्णांक __init efi_reuse_config(u64 tables, पूर्णांक nr_tables);
बाह्य व्योम efi_delete_dummy_variable(व्योम);
बाह्य व्योम efi_crash_gracefully_on_page_fault(अचिन्हित दीर्घ phys_addr);
बाह्य व्योम efi_मुक्त_boot_services(व्योम);

व्योम efi_enter_mm(व्योम);
व्योम efi_leave_mm(व्योम);

/* kexec बाह्यal ABI */
काष्ठा efi_setup_data अणु
	u64 fw_venकरोr;
	u64 __unused;
	u64 tables;
	u64 smbios;
	u64 reserved[8];
पूर्ण;

बाह्य u64 efi_setup;

#अगर_घोषित CONFIG_EFI
बाह्य efi_status_t __efi64_thunk(u32, ...);

#घोषणा efi64_thunk(...) (अणु						\
	__efi_nargs_check(efi64_thunk, 6, __VA_ARGS__);			\
	__efi64_thunk(__VA_ARGS__);					\
पूर्ण)

अटल अंतरभूत bool efi_is_mixed(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_EFI_MIXED))
		वापस false;
	वापस IS_ENABLED(CONFIG_X86_64) && !efi_enabled(EFI_64BIT);
पूर्ण

अटल अंतरभूत bool efi_runसमय_supported(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_X86_64) == efi_enabled(EFI_64BIT))
		वापस true;

	वापस IS_ENABLED(CONFIG_EFI_MIXED);
पूर्ण

बाह्य व्योम parse_efi_setup(u64 phys_addr, u32 data_len);

बाह्य व्योम efअगरb_setup_from_dmi(काष्ठा screen_info *si, स्थिर अक्षर *opt);

बाह्य व्योम efi_thunk_runसमय_setup(व्योम);
efi_status_t efi_set_भव_address_map(अचिन्हित दीर्घ memory_map_size,
					 अचिन्हित दीर्घ descriptor_size,
					 u32 descriptor_version,
					 efi_memory_desc_t *भव_map,
					 अचिन्हित दीर्घ systab_phys);

/* arch specअगरic definitions used by the stub code */

#अगर_घोषित CONFIG_EFI_MIXED

#घोषणा ARCH_HAS_EFISTUB_WRAPPERS

अटल अंतरभूत bool efi_is_64bit(व्योम)
अणु
	बाह्य स्थिर bool efi_is64;

	वापस efi_is64;
पूर्ण

अटल अंतरभूत bool efi_is_native(व्योम)
अणु
	वापस efi_is_64bit();
पूर्ण

#घोषणा efi_mixed_mode_cast(attr)					\
	__builtin_choose_expr(						\
		__builtin_types_compatible_p(u32, __typeof__(attr)),	\
			(अचिन्हित दीर्घ)(attr), (attr))

#घोषणा efi_table_attr(inst, attr)					\
	(efi_is_native()						\
		? inst->attr						\
		: (__typeof__(inst->attr))				\
			efi_mixed_mode_cast(inst->mixed_mode.attr))

/*
 * The following macros allow translating arguments अगर necessary from native to
 * mixed mode. The use हाल क्रम this is to initialize the upper 32 bits of
 * output parameters, and where the 32-bit method requires a 64-bit argument,
 * which must be split up पूर्णांकo two arguments to be thunked properly.
 *
 * As examples, the AllocatePool boot service वापसs the address of the
 * allocation, but it will not set the high 32 bits of the address. To ensure
 * that the full 64-bit address is initialized, we zero-init the address beक्रमe
 * calling the thunk.
 *
 * The FreePages boot service takes a 64-bit physical address even in 32-bit
 * mode. For the thunk to work correctly, a native 64-bit call of
 * 	मुक्त_pages(addr, size)
 * must be translated to
 * 	efi64_thunk(मुक्त_pages, addr & U32_MAX, addr >> 32, size)
 * so that the two 32-bit halves of addr get pushed onto the stack separately.
 */

अटल अंतरभूत व्योम *efi64_zero_upper(व्योम *p)
अणु
	((u32 *)p)[1] = 0;
	वापस p;
पूर्ण

अटल अंतरभूत u32 efi64_convert_status(efi_status_t status)
अणु
	वापस (u32)(status | (u64)status >> 32);
पूर्ण

#घोषणा __efi64_argmap_मुक्त_pages(addr, size)				\
	((addr), 0, (size))

#घोषणा __efi64_argmap_get_memory_map(mm_size, mm, key, size, ver)	\
	((mm_size), (mm), efi64_zero_upper(key), efi64_zero_upper(size), (ver))

#घोषणा __efi64_argmap_allocate_pool(type, size, buffer)		\
	((type), (size), efi64_zero_upper(buffer))

#घोषणा __efi64_argmap_create_event(type, tpl, f, c, event)		\
	((type), (tpl), (f), (c), efi64_zero_upper(event))

#घोषणा __efi64_argmap_set_समयr(event, type, समय)			\
	((event), (type), lower_32_bits(समय), upper_32_bits(समय))

#घोषणा __efi64_argmap_रुको_क्रम_event(num, event, index)		\
	((num), (event), efi64_zero_upper(index))

#घोषणा __efi64_argmap_handle_protocol(handle, protocol, पूर्णांकerface)	\
	((handle), (protocol), efi64_zero_upper(पूर्णांकerface))

#घोषणा __efi64_argmap_locate_protocol(protocol, reg, पूर्णांकerface)	\
	((protocol), (reg), efi64_zero_upper(पूर्णांकerface))

#घोषणा __efi64_argmap_locate_device_path(protocol, path, handle)	\
	((protocol), (path), efi64_zero_upper(handle))

#घोषणा __efi64_argmap_निकास(handle, status, size, data)			\
	((handle), efi64_convert_status(status), (size), (data))

/* PCI I/O */
#घोषणा __efi64_argmap_get_location(protocol, seg, bus, dev, func)	\
	((protocol), efi64_zero_upper(seg), efi64_zero_upper(bus),	\
	 efi64_zero_upper(dev), efi64_zero_upper(func))

/* LoadFile */
#घोषणा __efi64_argmap_load_file(protocol, path, policy, bufsize, buf)	\
	((protocol), (path), (policy), efi64_zero_upper(bufsize), (buf))

/* Graphics Output Protocol */
#घोषणा __efi64_argmap_query_mode(gop, mode, size, info)		\
	((gop), (mode), efi64_zero_upper(size), efi64_zero_upper(info))

/*
 * The macros below handle the plumbing क्रम the argument mapping. To add a
 * mapping क्रम a specअगरic EFI method, simply define a macro
 * __efi64_argmap_<method name>, following the examples above.
 */

#घोषणा __efi64_thunk_map(inst, func, ...)				\
	efi64_thunk(inst->mixed_mode.func,				\
		__efi64_argmap(__efi64_argmap_ ## func(__VA_ARGS__),	\
			       (__VA_ARGS__)))

#घोषणा __efi64_argmap(mapped, args)					\
	__PASTE(__efi64_argmap__, __efi_nargs(__efi_eat mapped))(mapped, args)
#घोषणा __efi64_argmap__0(mapped, args) __efi_eval mapped
#घोषणा __efi64_argmap__1(mapped, args) __efi_eval args

#घोषणा __efi_eat(...)
#घोषणा __efi_eval(...) __VA_ARGS__

/* The three macros below handle dispatching via the thunk अगर needed */

#घोषणा efi_call_proto(inst, func, ...)					\
	(efi_is_native()						\
		? inst->func(inst, ##__VA_ARGS__)			\
		: __efi64_thunk_map(inst, func, inst, ##__VA_ARGS__))

#घोषणा efi_bs_call(func, ...)						\
	(efi_is_native()						\
		? efi_प्रणाली_table->bootसमय->func(__VA_ARGS__)		\
		: __efi64_thunk_map(efi_table_attr(efi_प्रणाली_table,	\
						   bootसमय),		\
				    func, __VA_ARGS__))

#घोषणा efi_rt_call(func, ...)						\
	(efi_is_native()						\
		? efi_प्रणाली_table->runसमय->func(__VA_ARGS__)		\
		: __efi64_thunk_map(efi_table_attr(efi_प्रणाली_table,	\
						   runसमय),		\
				    func, __VA_ARGS__))

#अन्यथा /* CONFIG_EFI_MIXED */

अटल अंतरभूत bool efi_is_64bit(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_X86_64);
पूर्ण

#पूर्ण_अगर /* CONFIG_EFI_MIXED */

बाह्य bool efi_reboot_required(व्योम);
बाह्य bool efi_is_table_address(अचिन्हित दीर्घ phys_addr);

बाह्य व्योम efi_find_mirror(व्योम);
बाह्य व्योम efi_reserve_boot_services(व्योम);
#अन्यथा
अटल अंतरभूत व्योम parse_efi_setup(u64 phys_addr, u32 data_len) अणुपूर्ण
अटल अंतरभूत bool efi_reboot_required(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत  bool efi_is_table_address(अचिन्हित दीर्घ phys_addr)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम efi_find_mirror(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम efi_reserve_boot_services(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_EFI */

#अगर_घोषित CONFIG_EFI_FAKE_MEMMAP
बाह्य व्योम __init efi_fake_memmap_early(व्योम);
#अन्यथा
अटल अंतरभूत व्योम efi_fake_memmap_early(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा arch_ima_efi_boot_mode	\
	(अणु बाह्य काष्ठा boot_params boot_params; boot_params.secure_boot; पूर्ण)

#पूर्ण_अगर /* _ASM_X86_EFI_H */
