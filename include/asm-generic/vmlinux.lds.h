<शैली गुरु>
/*
 * Helper macros to support writing architecture specअगरic
 * linker scripts.
 *
 * A minimal linker scripts has following content:
 * [This is a sample, architectures may have special requiriements]
 *
 * OUTPUT_FORMAT(...)
 * OUTPUT_ARCH(...)
 * ENTRY(...)
 * SECTIONS
 * अणु
 *	. = START;
 *	__init_begin = .;
 *	HEAD_TEXT_SECTION
 *	INIT_TEXT_SECTION(PAGE_SIZE)
 *	INIT_DATA_SECTION(...)
 *	PERCPU_SECTION(CACHELINE_SIZE)
 *	__init_end = .;
 *
 *	_stext = .;
 *	TEXT_SECTION = 0
 *	_etext = .;
 *
 *      _sdata = .;
 *	RO_DATA(PAGE_SIZE)
 *	RW_DATA(...)
 *	_edata = .;
 *
 *	EXCEPTION_TABLE(...)
 *
 *	BSS_SECTION(0, 0, 0)
 *	_end = .;
 *
 *	STABS_DEBUG
 *	DWARF_DEBUG
 *	ELF_DETAILS
 *
 *	DISCARDS		// must be the last
 * पूर्ण
 *
 * [__init_begin, __init_end] is the init section that may be मुक्तd after init
 * 	// __init_begin and __init_end should be page aligned, so that we can
 *	// मुक्त the whole .init memory
 * [_stext, _etext] is the text section
 * [_sdata, _edata] is the data section
 *
 * Some of the included output section have their own set of स्थिरants.
 * Examples are: [__initramfs_start, __initramfs_end] क्रम initramfs and
 *               [__nosave_begin, __nosave_end] क्रम the nosave data
 */

#अगर_अघोषित LOAD_OFFSET
#घोषणा LOAD_OFFSET 0
#पूर्ण_अगर

/*
 * Only some architectures want to have the .notes segment visible in
 * a separate PT_NOTE ELF Program Header. When this happens, it needs
 * to be visible in both the kernel text's PT_LOAD and the PT_NOTE
 * Program Headers. In this हाल, though, the PT_LOAD needs to be made
 * the शेष again so that all the following sections करोn't also end
 * up in the PT_NOTE Program Header.
 */
#अगर_घोषित EMITS_PT_NOTE
#घोषणा NOTES_HEADERS		:text :note
#घोषणा NOTES_HEADERS_RESTORE	__restore_ph : अणु *(.__restore_ph) पूर्ण :text
#अन्यथा
#घोषणा NOTES_HEADERS
#घोषणा NOTES_HEADERS_RESTORE
#पूर्ण_अगर

/*
 * Some architectures have non-executable पढ़ो-only exception tables.
 * They can be added to the RO_DATA segment by specअगरying their desired
 * alignment.
 */
#अगर_घोषित RO_EXCEPTION_TABLE_ALIGN
#घोषणा RO_EXCEPTION_TABLE	EXCEPTION_TABLE(RO_EXCEPTION_TABLE_ALIGN)
#अन्यथा
#घोषणा RO_EXCEPTION_TABLE
#पूर्ण_अगर

/* Align . to a 8 byte boundary equals to maximum function alignment. */
#घोषणा ALIGN_FUNCTION()  . = ALIGN(8)

/*
 * LD_DEAD_CODE_DATA_ELIMINATION option enables -fdata-sections, which
 * generates .data.identअगरier sections, which need to be pulled in with
 * .data. We करोn't want to pull in .data..other sections, which Linux
 * has defined. Same क्रम text and bss.
 *
 * With LTO_CLANG, the linker also splits sections by शेष, so we need
 * these macros to combine the sections during the final link.
 *
 * RODATA_MAIN is not used because existing code alपढ़ोy defines .rodata.x
 * sections to be brought in with rodata.
 */
#अगर defined(CONFIG_LD_DEAD_CODE_DATA_ELIMINATION) || defined(CONFIG_LTO_CLANG)
#घोषणा TEXT_MAIN .text .text.[0-9a-zA-Z_]*
#घोषणा DATA_MAIN .data .data.[0-9a-zA-Z_]* .data..L* .data..compoundliteral* .data.$__unnamed_* .data.$L*
#घोषणा SDATA_MAIN .sdata .sdata.[0-9a-zA-Z_]*
#घोषणा RODATA_MAIN .rodata .rodata.[0-9a-zA-Z_]* .rodata..L*
#घोषणा BSS_MAIN .bss .bss.[0-9a-zA-Z_]* .bss..compoundliteral*
#घोषणा SBSS_MAIN .sbss .sbss.[0-9a-zA-Z_]*
#अन्यथा
#घोषणा TEXT_MAIN .text
#घोषणा DATA_MAIN .data
#घोषणा SDATA_MAIN .sdata
#घोषणा RODATA_MAIN .rodata
#घोषणा BSS_MAIN .bss
#घोषणा SBSS_MAIN .sbss
#पूर्ण_अगर

/*
 * GCC 4.5 and later have a 32 bytes section alignment क्रम काष्ठाures.
 * Except GCC 4.9, that feels the need to align on 64 bytes.
 */
#अगर __GNUC__ == 4 && __GNUC_MINOR__ == 9
#घोषणा STRUCT_ALIGNMENT 64
#अन्यथा
#घोषणा STRUCT_ALIGNMENT 32
#पूर्ण_अगर
#घोषणा STRUCT_ALIGN() . = ALIGN(STRUCT_ALIGNMENT)

/*
 * The order of the sched class addresses are important, as they are
 * used to determine the order of the priority of each sched class in
 * relation to each other.
 */
#घोषणा SCHED_DATA				\
	STRUCT_ALIGN();				\
	__begin_sched_classes = .;		\
	*(__idle_sched_class)			\
	*(__fair_sched_class)			\
	*(__rt_sched_class)			\
	*(__dl_sched_class)			\
	*(__stop_sched_class)			\
	__end_sched_classes = .;

/* The actual configuration determine अगर the init/निकास sections
 * are handled as text/data or they can be discarded (which
 * often happens at runसमय)
 */
#अगर_घोषित CONFIG_HOTPLUG_CPU
#घोषणा CPU_KEEP(sec)    *(.cpu##sec)
#घोषणा CPU_DISCARD(sec)
#अन्यथा
#घोषणा CPU_KEEP(sec)
#घोषणा CPU_DISCARD(sec) *(.cpu##sec)
#पूर्ण_अगर

#अगर defined(CONFIG_MEMORY_HOTPLUG)
#घोषणा MEM_KEEP(sec)    *(.mem##sec)
#घोषणा MEM_DISCARD(sec)
#अन्यथा
#घोषणा MEM_KEEP(sec)
#घोषणा MEM_DISCARD(sec) *(.mem##sec)
#पूर्ण_अगर

#अगर_घोषित CONFIG_FTRACE_MCOUNT_RECORD
/*
 * The ftrace call sites are logged to a section whose name depends on the
 * compiler option used. A given kernel image will only use one, AKA
 * FTRACE_CALLSITE_SECTION. We capture all of them here to aव्योम header
 * dependencies क्रम FTRACE_CALLSITE_SECTION's definition.
 *
 * Need to also make ftrace_stub_graph poपूर्णांक to ftrace_stub
 * so that the same stub location may have dअगरferent protocols
 * and not mess up with C verअगरiers.
 */
#घोषणा MCOUNT_REC()	. = ALIGN(8);				\
			__start_mcount_loc = .;			\
			KEEP(*(__mcount_loc))			\
			KEEP(*(__patchable_function_entries))	\
			__stop_mcount_loc = .;			\
			ftrace_stub_graph = ftrace_stub;
#अन्यथा
# अगरdef CONFIG_FUNCTION_TRACER
#  define MCOUNT_REC()	ftrace_stub_graph = ftrace_stub;
# अन्यथा
#  define MCOUNT_REC()
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACE_BRANCH_PROFILING
#घोषणा LIKELY_PROखाता()	__start_annotated_branch_profile = .;	\
				KEEP(*(_ftrace_annotated_branch))	\
				__stop_annotated_branch_profile = .;
#अन्यथा
#घोषणा LIKELY_PROखाता()
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROखाता_ALL_BRANCHES
#घोषणा BRANCH_PROखाता()	__start_branch_profile = .;		\
				KEEP(*(_ftrace_branch))			\
				__stop_branch_profile = .;
#अन्यथा
#घोषणा BRANCH_PROखाता()
#पूर्ण_अगर

#अगर_घोषित CONFIG_KPROBES
#घोषणा KPROBE_BLACKLIST()	. = ALIGN(8);				      \
				__start_kprobe_blacklist = .;		      \
				KEEP(*(_kprobe_blacklist))		      \
				__stop_kprobe_blacklist = .;
#अन्यथा
#घोषणा KPROBE_BLACKLIST()
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_ERROR_INJECTION
#घोषणा ERROR_INJECT_WHITELIST()	STRUCT_ALIGN();			      \
			__start_error_injection_whitelist = .;		      \
			KEEP(*(_error_injection_whitelist))		      \
			__stop_error_injection_whitelist = .;
#अन्यथा
#घोषणा ERROR_INJECT_WHITELIST()
#पूर्ण_अगर

#अगर_घोषित CONFIG_EVENT_TRACING
#घोषणा FTRACE_EVENTS()	. = ALIGN(8);					\
			__start_ftrace_events = .;			\
			KEEP(*(_ftrace_events))				\
			__stop_ftrace_events = .;			\
			__start_ftrace_eval_maps = .;			\
			KEEP(*(_ftrace_eval_map))			\
			__stop_ftrace_eval_maps = .;
#अन्यथा
#घोषणा FTRACE_EVENTS()
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACING
#घोषणा TRACE_PRINTKS()	 __start___trace_bprपूर्णांकk_fmt = .;      \
			 KEEP(*(__trace_prपूर्णांकk_fmt)) /* Trace_prपूर्णांकk fmt' poपूर्णांकer */ \
			 __stop___trace_bprपूर्णांकk_fmt = .;
#घोषणा TRACEPOINT_STR() __start___tracepoपूर्णांक_str = .;	\
			 KEEP(*(__tracepoपूर्णांक_str)) /* Trace_prपूर्णांकk fmt' poपूर्णांकer */ \
			 __stop___tracepoपूर्णांक_str = .;
#अन्यथा
#घोषणा TRACE_PRINTKS()
#घोषणा TRACEPOINT_STR()
#पूर्ण_अगर

#अगर_घोषित CONFIG_FTRACE_SYSCALLS
#घोषणा TRACE_SYSCALLS() . = ALIGN(8);					\
			 __start_syscalls_metadata = .;			\
			 KEEP(*(__syscalls_metadata))			\
			 __stop_syscalls_metadata = .;
#अन्यथा
#घोषणा TRACE_SYSCALLS()
#पूर्ण_अगर

#अगर_घोषित CONFIG_BPF_EVENTS
#घोषणा BPF_RAW_TP() STRUCT_ALIGN();					\
			 __start__bpf_raw_tp = .;			\
			 KEEP(*(__bpf_raw_tp_map))			\
			 __stop__bpf_raw_tp = .;
#अन्यथा
#घोषणा BPF_RAW_TP()
#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_EARLYCON
#घोषणा EARLYCON_TABLE() . = ALIGN(8);				\
			 __earlycon_table = .;			\
			 KEEP(*(__earlycon_table))		\
			 __earlycon_table_end = .;
#अन्यथा
#घोषणा EARLYCON_TABLE()
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY
#घोषणा LSM_TABLE()	. = ALIGN(8);					\
			__start_lsm_info = .;				\
			KEEP(*(.lsm_info.init))				\
			__end_lsm_info = .;
#घोषणा EARLY_LSM_TABLE()	. = ALIGN(8);				\
			__start_early_lsm_info = .;			\
			KEEP(*(.early_lsm_info.init))			\
			__end_early_lsm_info = .;
#अन्यथा
#घोषणा LSM_TABLE()
#घोषणा EARLY_LSM_TABLE()
#पूर्ण_अगर

#घोषणा ___OF_TABLE(cfg, name)	_OF_TABLE_##cfg(name)
#घोषणा __OF_TABLE(cfg, name)	___OF_TABLE(cfg, name)
#घोषणा OF_TABLE(cfg, name)	__OF_TABLE(IS_ENABLED(cfg), name)
#घोषणा _OF_TABLE_0(name)
#घोषणा _OF_TABLE_1(name)						\
	. = ALIGN(8);							\
	__##name##_of_table = .;					\
	KEEP(*(__##name##_of_table))					\
	KEEP(*(__##name##_of_table_end))

#घोषणा TIMER_OF_TABLES()	OF_TABLE(CONFIG_TIMER_OF, समयr)
#घोषणा IRQCHIP_OF_MATCH_TABLE() OF_TABLE(CONFIG_IRQCHIP, irqchip)
#घोषणा CLK_OF_TABLES()		OF_TABLE(CONFIG_COMMON_CLK, clk)
#घोषणा RESERVEDMEM_OF_TABLES()	OF_TABLE(CONFIG_OF_RESERVED_MEM, reservedmem)
#घोषणा CPU_METHOD_OF_TABLES()	OF_TABLE(CONFIG_SMP, cpu_method)
#घोषणा CPUIDLE_METHOD_OF_TABLES() OF_TABLE(CONFIG_CPU_IDLE, cpuidle_method)

#अगर_घोषित CONFIG_ACPI
#घोषणा ACPI_PROBE_TABLE(name)						\
	. = ALIGN(8);							\
	__##name##_acpi_probe_table = .;				\
	KEEP(*(__##name##_acpi_probe_table))				\
	__##name##_acpi_probe_table_end = .;
#अन्यथा
#घोषणा ACPI_PROBE_TABLE(name)
#पूर्ण_अगर

#अगर_घोषित CONFIG_THERMAL
#घोषणा THERMAL_TABLE(name)						\
	. = ALIGN(8);							\
	__##name##_thermal_table = .;					\
	KEEP(*(__##name##_thermal_table))				\
	__##name##_thermal_table_end = .;
#अन्यथा
#घोषणा THERMAL_TABLE(name)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DTPM
#घोषणा DTPM_TABLE()							\
	. = ALIGN(8);							\
	__dtpm_table = .;						\
	KEEP(*(__dtpm_table))						\
	__dtpm_table_end = .;
#अन्यथा
#घोषणा DTPM_TABLE()
#पूर्ण_अगर

#घोषणा KERNEL_DTB()							\
	STRUCT_ALIGN();							\
	__dtb_start = .;						\
	KEEP(*(.dtb.init.rodata))					\
	__dtb_end = .;

/*
 * .data section
 */
#घोषणा DATA_DATA							\
	*(.xiptext)							\
	*(DATA_MAIN)							\
	*(.ref.data)							\
	*(.data..shared_aligned) /* percpu related */			\
	MEM_KEEP(init.data*)						\
	MEM_KEEP(निकास.data*)						\
	*(.data.unlikely)						\
	__start_once = .;						\
	*(.data.once)							\
	__end_once = .;							\
	STRUCT_ALIGN();							\
	*(__tracepoपूर्णांकs)						\
	/* implement dynamic prपूर्णांकk debug */				\
	. = ALIGN(8);							\
	__start___dyndbg = .;						\
	KEEP(*(__dyndbg))						\
	__stop___dyndbg = .;						\
	LIKELY_PROखाता()		       				\
	BRANCH_PROखाता()						\
	TRACE_PRINTKS()							\
	BPF_RAW_TP()							\
	TRACEPOINT_STR()

/*
 * Data section helpers
 */
#घोषणा NOSAVE_DATA							\
	. = ALIGN(PAGE_SIZE);						\
	__nosave_begin = .;						\
	*(.data..nosave)						\
	. = ALIGN(PAGE_SIZE);						\
	__nosave_end = .;

#घोषणा PAGE_ALIGNED_DATA(page_align)					\
	. = ALIGN(page_align);						\
	*(.data..page_aligned)						\
	. = ALIGN(page_align);

#घोषणा READ_MOSTLY_DATA(align)						\
	. = ALIGN(align);						\
	*(.data..पढ़ो_mostly)						\
	. = ALIGN(align);

#घोषणा CACHELINE_ALIGNED_DATA(align)					\
	. = ALIGN(align);						\
	*(.data..cacheline_aligned)

#घोषणा INIT_TASK_DATA(align)						\
	. = ALIGN(align);						\
	__start_init_task = .;						\
	init_thपढ़ो_जोड़ = .;						\
	init_stack = .;							\
	KEEP(*(.data..init_task))					\
	KEEP(*(.data..init_thपढ़ो_info))				\
	. = __start_init_task + THREAD_SIZE;				\
	__end_init_task = .;

#घोषणा JUMP_TABLE_DATA							\
	. = ALIGN(8);							\
	__start___jump_table = .;					\
	KEEP(*(__jump_table))						\
	__stop___jump_table = .;

#घोषणा STATIC_CALL_DATA						\
	. = ALIGN(8);							\
	__start_अटल_call_sites = .;					\
	KEEP(*(.अटल_call_sites))					\
	__stop_अटल_call_sites = .;					\
	__start_अटल_call_tramp_key = .;				\
	KEEP(*(.अटल_call_tramp_key))					\
	__stop_अटल_call_tramp_key = .;

/*
 * Allow architectures to handle ro_after_init data on their
 * own by defining an empty RO_AFTER_INIT_DATA.
 */
#अगर_अघोषित RO_AFTER_INIT_DATA
#घोषणा RO_AFTER_INIT_DATA						\
	. = ALIGN(8);							\
	__start_ro_after_init = .;					\
	*(.data..ro_after_init)						\
	JUMP_TABLE_DATA							\
	STATIC_CALL_DATA						\
	__end_ro_after_init = .;
#पूर्ण_अगर

/*
 * Read only Data
 */
#घोषणा RO_DATA(align)							\
	. = ALIGN((align));						\
	.rodata           : AT(ADDR(.rodata) - LOAD_OFFSET) अणु		\
		__start_rodata = .;					\
		*(.rodata) *(.rodata.*)					\
		SCHED_DATA						\
		RO_AFTER_INIT_DATA	/* Read only after init */	\
		. = ALIGN(8);						\
		__start___tracepoपूर्णांकs_ptrs = .;				\
		KEEP(*(__tracepoपूर्णांकs_ptrs)) /* Tracepoपूर्णांकs: poपूर्णांकer array */ \
		__stop___tracepoपूर्णांकs_ptrs = .;				\
		*(__tracepoपूर्णांकs_strings)/* Tracepoपूर्णांकs: strings */	\
	पूर्ण								\
									\
	.rodata1          : AT(ADDR(.rodata1) - LOAD_OFFSET) अणु		\
		*(.rodata1)						\
	पूर्ण								\
									\
	/* PCI quirks */						\
	.pci_fixup        : AT(ADDR(.pci_fixup) - LOAD_OFFSET) अणु	\
		__start_pci_fixups_early = .;				\
		KEEP(*(.pci_fixup_early))				\
		__end_pci_fixups_early = .;				\
		__start_pci_fixups_header = .;				\
		KEEP(*(.pci_fixup_header))				\
		__end_pci_fixups_header = .;				\
		__start_pci_fixups_final = .;				\
		KEEP(*(.pci_fixup_final))				\
		__end_pci_fixups_final = .;				\
		__start_pci_fixups_enable = .;				\
		KEEP(*(.pci_fixup_enable))				\
		__end_pci_fixups_enable = .;				\
		__start_pci_fixups_resume = .;				\
		KEEP(*(.pci_fixup_resume))				\
		__end_pci_fixups_resume = .;				\
		__start_pci_fixups_resume_early = .;			\
		KEEP(*(.pci_fixup_resume_early))			\
		__end_pci_fixups_resume_early = .;			\
		__start_pci_fixups_suspend = .;				\
		KEEP(*(.pci_fixup_suspend))				\
		__end_pci_fixups_suspend = .;				\
		__start_pci_fixups_suspend_late = .;			\
		KEEP(*(.pci_fixup_suspend_late))			\
		__end_pci_fixups_suspend_late = .;			\
	पूर्ण								\
									\
	/* Built-in firmware blobs */					\
	.builtin_fw : AT(ADDR(.builtin_fw) - LOAD_OFFSET) ALIGN(8) अणु	\
		__start_builtin_fw = .;					\
		KEEP(*(.builtin_fw))					\
		__end_builtin_fw = .;					\
	पूर्ण								\
									\
	TRACEDATA							\
									\
	/* Kernel symbol table: Normal symbols */			\
	__ksymtab         : AT(ADDR(__ksymtab) - LOAD_OFFSET) अणु		\
		__start___ksymtab = .;					\
		KEEP(*(SORT(___ksymtab+*)))				\
		__stop___ksymtab = .;					\
	पूर्ण								\
									\
	/* Kernel symbol table: GPL-only symbols */			\
	__ksymtab_gpl     : AT(ADDR(__ksymtab_gpl) - LOAD_OFFSET) अणु	\
		__start___ksymtab_gpl = .;				\
		KEEP(*(SORT(___ksymtab_gpl+*)))				\
		__stop___ksymtab_gpl = .;				\
	पूर्ण								\
									\
	/* Kernel symbol table: Normal symbols */			\
	__kcrctab         : AT(ADDR(__kcrctab) - LOAD_OFFSET) अणु		\
		__start___kcrctab = .;					\
		KEEP(*(SORT(___kcrctab+*)))				\
		__stop___kcrctab = .;					\
	पूर्ण								\
									\
	/* Kernel symbol table: GPL-only symbols */			\
	__kcrctab_gpl     : AT(ADDR(__kcrctab_gpl) - LOAD_OFFSET) अणु	\
		__start___kcrctab_gpl = .;				\
		KEEP(*(SORT(___kcrctab_gpl+*)))				\
		__stop___kcrctab_gpl = .;				\
	पूर्ण								\
									\
	/* Kernel symbol table: strings */				\
        __ksymtab_strings : AT(ADDR(__ksymtab_strings) - LOAD_OFFSET) अणु	\
		*(__ksymtab_strings)					\
	पूर्ण								\
									\
	/* __*init sections */						\
	__init_rodata : AT(ADDR(__init_rodata) - LOAD_OFFSET) अणु		\
		*(.ref.rodata)						\
		MEM_KEEP(init.rodata)					\
		MEM_KEEP(निकास.rodata)					\
	पूर्ण								\
									\
	/* Built-in module parameters. */				\
	__param : AT(ADDR(__param) - LOAD_OFFSET) अणु			\
		__start___param = .;					\
		KEEP(*(__param))					\
		__stop___param = .;					\
	पूर्ण								\
									\
	/* Built-in module versions. */					\
	__modver : AT(ADDR(__modver) - LOAD_OFFSET) अणु			\
		__start___modver = .;					\
		KEEP(*(__modver))					\
		__stop___modver = .;					\
	पूर्ण								\
									\
	RO_EXCEPTION_TABLE						\
	NOTES								\
	BTF								\
									\
	. = ALIGN((align));						\
	__end_rodata = .;


/*
 * .text..L.cfi.jumptable.* contain Control-Flow Integrity (CFI)
 * jump table entries.
 */
#अगर_घोषित CONFIG_CFI_CLANG
#घोषणा TEXT_CFI_JT							\
		. = ALIGN(PMD_SIZE);					\
		__cfi_jt_start = .;					\
		*(.text..L.cfi.jumptable .text..L.cfi.jumptable.*)	\
		. = ALIGN(PMD_SIZE);					\
		__cfi_jt_end = .;
#अन्यथा
#घोषणा TEXT_CFI_JT
#पूर्ण_अगर

/*
 * Non-instrumentable text section
 */
#घोषणा NOINSTR_TEXT							\
		ALIGN_FUNCTION();					\
		__noinstr_text_start = .;				\
		*(.noinstr.text)					\
		__noinstr_text_end = .;

/*
 * .text section. Map to function alignment to aव्योम address changes
 * during second ld run in second ld pass when generating System.map
 *
 * TEXT_MAIN here will match .text.fixup and .text.unlikely अगर dead
 * code elimination is enabled, so these sections should be converted
 * to use ".." first.
 */
#घोषणा TEXT_TEXT							\
		ALIGN_FUNCTION();					\
		*(.text.hot .text.hot.*)				\
		*(TEXT_MAIN .text.fixup)				\
		*(.text.unlikely .text.unlikely.*)			\
		*(.text.unknown .text.unknown.*)			\
		NOINSTR_TEXT						\
		*(.text..refcount)					\
		*(.ref.text)						\
		TEXT_CFI_JT						\
	MEM_KEEP(init.text*)						\
	MEM_KEEP(निकास.text*)						\


/* sched.text is aling to function alignment to secure we have same
 * address even at second ld pass when generating System.map */
#घोषणा SCHED_TEXT							\
		ALIGN_FUNCTION();					\
		__sched_text_start = .;					\
		*(.sched.text)						\
		__sched_text_end = .;

/* spinlock.text is aling to function alignment to secure we have same
 * address even at second ld pass when generating System.map */
#घोषणा LOCK_TEXT							\
		ALIGN_FUNCTION();					\
		__lock_text_start = .;					\
		*(.spinlock.text)					\
		__lock_text_end = .;

#घोषणा CPUIDLE_TEXT							\
		ALIGN_FUNCTION();					\
		__cpuidle_text_start = .;				\
		*(.cpuidle.text)					\
		__cpuidle_text_end = .;

#घोषणा KPROBES_TEXT							\
		ALIGN_FUNCTION();					\
		__kprobes_text_start = .;				\
		*(.kprobes.text)					\
		__kprobes_text_end = .;

#घोषणा ENTRY_TEXT							\
		ALIGN_FUNCTION();					\
		__entry_text_start = .;					\
		*(.entry.text)						\
		__entry_text_end = .;

#घोषणा IRQENTRY_TEXT							\
		ALIGN_FUNCTION();					\
		__irqentry_text_start = .;				\
		*(.irqentry.text)					\
		__irqentry_text_end = .;

#घोषणा SOFTIRQENTRY_TEXT						\
		ALIGN_FUNCTION();					\
		__softirqentry_text_start = .;				\
		*(.softirqentry.text)					\
		__softirqentry_text_end = .;

#घोषणा STATIC_CALL_TEXT						\
		ALIGN_FUNCTION();					\
		__अटल_call_text_start = .;				\
		*(.अटल_call.text)					\
		__अटल_call_text_end = .;

/* Section used क्रम early init (in .S files) */
#घोषणा HEAD_TEXT  KEEP(*(.head.text))

#घोषणा HEAD_TEXT_SECTION							\
	.head.text : AT(ADDR(.head.text) - LOAD_OFFSET) अणु		\
		HEAD_TEXT						\
	पूर्ण

/*
 * Exception table
 */
#घोषणा EXCEPTION_TABLE(align)						\
	. = ALIGN(align);						\
	__ex_table : AT(ADDR(__ex_table) - LOAD_OFFSET) अणु		\
		__start___ex_table = .;					\
		KEEP(*(__ex_table))					\
		__stop___ex_table = .;					\
	पूर्ण

/*
 * .BTF
 */
#अगर_घोषित CONFIG_DEBUG_INFO_BTF
#घोषणा BTF								\
	.BTF : AT(ADDR(.BTF) - LOAD_OFFSET) अणु				\
		__start_BTF = .;					\
		KEEP(*(.BTF))						\
		__stop_BTF = .;						\
	पूर्ण								\
	. = ALIGN(4);							\
	.BTF_ids : AT(ADDR(.BTF_ids) - LOAD_OFFSET) अणु			\
		*(.BTF_ids)						\
	पूर्ण
#अन्यथा
#घोषणा BTF
#पूर्ण_अगर

/*
 * Init task
 */
#घोषणा INIT_TASK_DATA_SECTION(align)					\
	. = ALIGN(align);						\
	.data..init_task :  AT(ADDR(.data..init_task) - LOAD_OFFSET) अणु	\
		INIT_TASK_DATA(align)					\
	पूर्ण

#अगर_घोषित CONFIG_CONSTRUCTORS
#घोषणा KERNEL_CTORS()	. = ALIGN(8);			   \
			__ctors_start = .;		   \
			KEEP(*(SORT(.ctors.*)))		   \
			KEEP(*(.ctors))			   \
			KEEP(*(SORT(.init_array.*)))	   \
			KEEP(*(.init_array))		   \
			__ctors_end = .;
#अन्यथा
#घोषणा KERNEL_CTORS()
#पूर्ण_अगर

/* init and निकास section handling */
#घोषणा INIT_DATA							\
	KEEP(*(SORT(___kentry+*)))					\
	*(.init.data init.data.*)					\
	MEM_DISCARD(init.data*)						\
	KERNEL_CTORS()							\
	MCOUNT_REC()							\
	*(.init.rodata .init.rodata.*)					\
	FTRACE_EVENTS()							\
	TRACE_SYSCALLS()						\
	KPROBE_BLACKLIST()						\
	ERROR_INJECT_WHITELIST()					\
	MEM_DISCARD(init.rodata)					\
	CLK_OF_TABLES()							\
	RESERVEDMEM_OF_TABLES()						\
	TIMER_OF_TABLES()						\
	CPU_METHOD_OF_TABLES()						\
	CPUIDLE_METHOD_OF_TABLES()					\
	KERNEL_DTB()							\
	IRQCHIP_OF_MATCH_TABLE()					\
	ACPI_PROBE_TABLE(irqchip)					\
	ACPI_PROBE_TABLE(समयr)						\
	THERMAL_TABLE(governor)						\
	DTPM_TABLE()							\
	EARLYCON_TABLE()						\
	LSM_TABLE()							\
	EARLY_LSM_TABLE()						\
	KUNIT_TABLE()

#घोषणा INIT_TEXT							\
	*(.init.text .init.text.*)					\
	*(.text.startup)						\
	MEM_DISCARD(init.text*)

#घोषणा EXIT_DATA							\
	*(.निकास.data .निकास.data.*)					\
	*(.fini_array .fini_array.*)					\
	*(.dtors .dtors.*)						\
	MEM_DISCARD(निकास.data*)						\
	MEM_DISCARD(निकास.rodata*)

#घोषणा EXIT_TEXT							\
	*(.निकास.text)							\
	*(.text.निकास)							\
	MEM_DISCARD(निकास.text)

#घोषणा EXIT_CALL							\
	*(.निकासcall.निकास)

/*
 * bss (Block Started by Symbol) - uninitialized data
 * zeroed during startup
 */
#घोषणा SBSS(sbss_align)						\
	. = ALIGN(sbss_align);						\
	.sbss : AT(ADDR(.sbss) - LOAD_OFFSET) अणु				\
		*(.dynsbss)						\
		*(SBSS_MAIN)						\
		*(.scommon)						\
	पूर्ण

/*
 * Allow archectures to redefine BSS_FIRST_SECTIONS to add extra
 * sections to the front of bss.
 */
#अगर_अघोषित BSS_FIRST_SECTIONS
#घोषणा BSS_FIRST_SECTIONS
#पूर्ण_अगर

#घोषणा BSS(bss_align)							\
	. = ALIGN(bss_align);						\
	.bss : AT(ADDR(.bss) - LOAD_OFFSET) अणु				\
		BSS_FIRST_SECTIONS					\
		. = ALIGN(PAGE_SIZE);					\
		*(.bss..page_aligned)					\
		. = ALIGN(PAGE_SIZE);					\
		*(.dynbss)						\
		*(BSS_MAIN)						\
		*(COMMON)						\
	पूर्ण

/*
 * DWARF debug sections.
 * Symbols in the DWARF debugging sections are relative to
 * the beginning of the section so we begin them at 0.
 */
#घोषणा DWARF_DEBUG							\
		/* DWARF 1 */						\
		.debug          0 : अणु *(.debug) पूर्ण			\
		.line           0 : अणु *(.line) पूर्ण			\
		/* GNU DWARF 1 extensions */				\
		.debug_srcinfo  0 : अणु *(.debug_srcinfo) पूर्ण		\
		.debug_sfnames  0 : अणु *(.debug_sfnames) पूर्ण		\
		/* DWARF 1.1 and DWARF 2 */				\
		.debug_aranges  0 : अणु *(.debug_aranges) पूर्ण		\
		.debug_pubnames 0 : अणु *(.debug_pubnames) पूर्ण		\
		/* DWARF 2 */						\
		.debug_info     0 : अणु *(.debug_info			\
				.gnu.linkonce.wi.*) पूर्ण			\
		.debug_abbrev   0 : अणु *(.debug_abbrev) पूर्ण		\
		.debug_line     0 : अणु *(.debug_line) पूर्ण			\
		.debug_frame    0 : अणु *(.debug_frame) पूर्ण			\
		.debug_str      0 : अणु *(.debug_str) पूर्ण			\
		.debug_loc      0 : अणु *(.debug_loc) पूर्ण			\
		.debug_macinfo  0 : अणु *(.debug_macinfo) पूर्ण		\
		.debug_pubtypes 0 : अणु *(.debug_pubtypes) पूर्ण		\
		/* DWARF 3 */						\
		.debug_ranges	0 : अणु *(.debug_ranges) पूर्ण		\
		/* SGI/MIPS DWARF 2 extensions */			\
		.debug_weaknames 0 : अणु *(.debug_weaknames) पूर्ण		\
		.debug_funcnames 0 : अणु *(.debug_funcnames) पूर्ण		\
		.debug_typenames 0 : अणु *(.debug_typenames) पूर्ण		\
		.debug_varnames  0 : अणु *(.debug_varnames) पूर्ण		\
		/* GNU DWARF 2 extensions */				\
		.debug_gnu_pubnames 0 : अणु *(.debug_gnu_pubnames) पूर्ण	\
		.debug_gnu_pubtypes 0 : अणु *(.debug_gnu_pubtypes) पूर्ण	\
		/* DWARF 4 */						\
		.debug_types	0 : अणु *(.debug_types) पूर्ण			\
		/* DWARF 5 */						\
		.debug_addr	0 : अणु *(.debug_addr) पूर्ण			\
		.debug_line_str	0 : अणु *(.debug_line_str) पूर्ण		\
		.debug_loclists	0 : अणु *(.debug_loclists) पूर्ण		\
		.debug_macro	0 : अणु *(.debug_macro) पूर्ण			\
		.debug_names	0 : अणु *(.debug_names) पूर्ण			\
		.debug_rnglists	0 : अणु *(.debug_rnglists) पूर्ण		\
		.debug_str_offsets	0 : अणु *(.debug_str_offsets) पूर्ण

/* Stअसल debugging sections. */
#घोषणा STABS_DEBUG							\
		.stab 0 : अणु *(.stab) पूर्ण					\
		.stअसलtr 0 : अणु *(.stअसलtr) पूर्ण				\
		.stab.excl 0 : अणु *(.stab.excl) पूर्ण			\
		.stab.exclstr 0 : अणु *(.stab.exclstr) पूर्ण			\
		.stab.index 0 : अणु *(.stab.index) पूर्ण			\
		.stab.indexstr 0 : अणु *(.stab.indexstr) पूर्ण

/* Required sections not related to debugging. */
#घोषणा ELF_DETAILS							\
		.comment 0 : अणु *(.comment) पूर्ण				\
		.symtab 0 : अणु *(.symtab) पूर्ण				\
		.strtab 0 : अणु *(.strtab) पूर्ण				\
		.shstrtab 0 : अणु *(.shstrtab) पूर्ण

#अगर_घोषित CONFIG_GENERIC_BUG
#घोषणा BUG_TABLE							\
	. = ALIGN(8);							\
	__bug_table : AT(ADDR(__bug_table) - LOAD_OFFSET) अणु		\
		__start___bug_table = .;				\
		KEEP(*(__bug_table))					\
		__stop___bug_table = .;					\
	पूर्ण
#अन्यथा
#घोषणा BUG_TABLE
#पूर्ण_अगर

#अगर_घोषित CONFIG_UNWINDER_ORC
#घोषणा ORC_UNWIND_TABLE						\
	. = ALIGN(4);							\
	.orc_unwind_ip : AT(ADDR(.orc_unwind_ip) - LOAD_OFFSET) अणु	\
		__start_orc_unwind_ip = .;				\
		KEEP(*(.orc_unwind_ip))					\
		__stop_orc_unwind_ip = .;				\
	पूर्ण								\
	. = ALIGN(2);							\
	.orc_unwind : AT(ADDR(.orc_unwind) - LOAD_OFFSET) अणु		\
		__start_orc_unwind = .;					\
		KEEP(*(.orc_unwind))					\
		__stop_orc_unwind = .;					\
	पूर्ण								\
	. = ALIGN(4);							\
	.orc_lookup : AT(ADDR(.orc_lookup) - LOAD_OFFSET) अणु		\
		orc_lookup = .;						\
		. += (((SIZखातापूर्ण(.text) + LOOKUP_BLOCK_SIZE - 1) /	\
			LOOKUP_BLOCK_SIZE) + 1) * 4;			\
		orc_lookup_end = .;					\
	पूर्ण
#अन्यथा
#घोषणा ORC_UNWIND_TABLE
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_TRACE
#घोषणा TRACEDATA							\
	. = ALIGN(4);							\
	.tracedata : AT(ADDR(.tracedata) - LOAD_OFFSET) अणु		\
		__tracedata_start = .;					\
		KEEP(*(.tracedata))					\
		__tracedata_end = .;					\
	पूर्ण
#अन्यथा
#घोषणा TRACEDATA
#पूर्ण_अगर

#घोषणा NOTES								\
	.notes : AT(ADDR(.notes) - LOAD_OFFSET) अणु			\
		__start_notes = .;					\
		KEEP(*(.note.*))					\
		__stop_notes = .;					\
	पूर्ण NOTES_HEADERS							\
	NOTES_HEADERS_RESTORE

#घोषणा INIT_SETUP(initsetup_align)					\
		. = ALIGN(initsetup_align);				\
		__setup_start = .;					\
		KEEP(*(.init.setup))					\
		__setup_end = .;

#घोषणा INIT_CALLS_LEVEL(level)						\
		__initcall##level##_start = .;				\
		KEEP(*(.initcall##level##.init))			\
		KEEP(*(.initcall##level##s.init))			\

#घोषणा INIT_CALLS							\
		__initcall_start = .;					\
		KEEP(*(.initcallearly.init))				\
		INIT_CALLS_LEVEL(0)					\
		INIT_CALLS_LEVEL(1)					\
		INIT_CALLS_LEVEL(2)					\
		INIT_CALLS_LEVEL(3)					\
		INIT_CALLS_LEVEL(4)					\
		INIT_CALLS_LEVEL(5)					\
		INIT_CALLS_LEVEL(rootfs)				\
		INIT_CALLS_LEVEL(6)					\
		INIT_CALLS_LEVEL(7)					\
		__initcall_end = .;

#घोषणा CON_INITCALL							\
		__con_initcall_start = .;				\
		KEEP(*(.con_initcall.init))				\
		__con_initcall_end = .;

/* Alignment must be consistent with (kunit_suite *) in include/kunit/test.h */
#घोषणा KUNIT_TABLE()							\
		. = ALIGN(8);						\
		__kunit_suites_start = .;				\
		KEEP(*(.kunit_test_suites))				\
		__kunit_suites_end = .;

#अगर_घोषित CONFIG_BLK_DEV_INITRD
#घोषणा INIT_RAM_FS							\
	. = ALIGN(4);							\
	__initramfs_start = .;						\
	KEEP(*(.init.ramfs))						\
	. = ALIGN(8);							\
	KEEP(*(.init.ramfs.info))
#अन्यथा
#घोषणा INIT_RAM_FS
#पूर्ण_अगर

/*
 * Memory encryption operates on a page basis. Since we need to clear
 * the memory encryption mask क्रम this section, it needs to be aligned
 * on a page boundary and be a page-size multiple in length.
 *
 * Note: We use a separate section so that only this section माला_लो
 * decrypted to aव्योम exposing more than we wish.
 */
#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
#घोषणा PERCPU_DECRYPTED_SECTION					\
	. = ALIGN(PAGE_SIZE);						\
	*(.data..decrypted)						\
	*(.data..percpu..decrypted)					\
	. = ALIGN(PAGE_SIZE);
#अन्यथा
#घोषणा PERCPU_DECRYPTED_SECTION
#पूर्ण_अगर


/*
 * Default discarded sections.
 *
 * Some archs want to discard निकास text/data at runसमय rather than
 * link समय due to cross-section references such as alt inकाष्ठाions,
 * bug table, eh_frame, etc.  DISCARDS must be the last of output
 * section definitions so that such archs put those in earlier section
 * definitions.
 */
#अगर_घोषित RUNTIME_DISCARD_EXIT
#घोषणा EXIT_DISCARDS
#अन्यथा
#घोषणा EXIT_DISCARDS							\
	EXIT_TEXT							\
	EXIT_DATA
#पूर्ण_अगर

/*
 * Clang's -fprofile-arcs, -fsanitize=kernel-address, and
 * -fsanitize=thपढ़ो produce unwanted sections (.eh_frame
 * and .init_array.*), but CONFIG_CONSTRUCTORS wants to
 * keep any .init_array.* sections.
 * https://bugs.llvm.org/show_bug.cgi?id=46478
 */
#अगर defined(CONFIG_GCOV_KERNEL) || defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KCSAN) || \
	defined(CONFIG_CFI_CLANG)
# अगरdef CONFIG_CONSTRUCTORS
#  define SANITIZER_DISCARDS						\
	*(.eh_frame)
# अन्यथा
#  define SANITIZER_DISCARDS						\
	*(.init_array) *(.init_array.*)					\
	*(.eh_frame)
# endअगर
#अन्यथा
# define SANITIZER_DISCARDS
#पूर्ण_अगर

#घोषणा COMMON_DISCARDS							\
	SANITIZER_DISCARDS						\
	*(.discard)							\
	*(.discard.*)							\
	*(.modinfo)							\
	/* ld.bfd warns about .gnu.version* even when not emitted */	\
	*(.gnu.version*)						\

#घोषणा DISCARDS							\
	/DISCARD/ : अणु							\
	EXIT_DISCARDS							\
	EXIT_CALL							\
	COMMON_DISCARDS							\
	पूर्ण

/**
 * PERCPU_INPUT - the percpu input sections
 * @cacheline: cacheline size
 *
 * The core percpu section names and core symbols which करो not rely
 * directly upon load addresses.
 *
 * @cacheline is used to align subsections to aव्योम false cacheline
 * sharing between subsections क्रम dअगरferent purposes.
 */
#घोषणा PERCPU_INPUT(cacheline)						\
	__per_cpu_start = .;						\
	*(.data..percpu..first)						\
	. = ALIGN(PAGE_SIZE);						\
	*(.data..percpu..page_aligned)					\
	. = ALIGN(cacheline);						\
	*(.data..percpu..पढ़ो_mostly)					\
	. = ALIGN(cacheline);						\
	*(.data..percpu)						\
	*(.data..percpu..shared_aligned)				\
	PERCPU_DECRYPTED_SECTION					\
	__per_cpu_end = .;

/**
 * PERCPU_VADDR - define output section क्रम percpu area
 * @cacheline: cacheline size
 * @vaddr: explicit base address (optional)
 * @phdr: destination PHDR (optional)
 *
 * Macro which expands to output section क्रम percpu area.
 *
 * @cacheline is used to align subsections to aव्योम false cacheline
 * sharing between subsections क्रम dअगरferent purposes.
 *
 * If @vaddr is not blank, it specअगरies explicit base address and all
 * percpu symbols will be offset from the given address.  If blank,
 * @vaddr always equals @laddr + LOAD_OFFSET.
 *
 * @phdr defines the output PHDR to use अगर not blank.  Be warned that
 * output PHDR is sticky.  If @phdr is specअगरied, the next output
 * section in the linker script will go there too.  @phdr should have
 * a leading colon.
 *
 * Note that this macros defines __per_cpu_load as an असलolute symbol.
 * If there is no need to put the percpu section at a predetermined
 * address, use PERCPU_SECTION.
 */
#घोषणा PERCPU_VADDR(cacheline, vaddr, phdr)				\
	__per_cpu_load = .;						\
	.data..percpu vaddr : AT(__per_cpu_load - LOAD_OFFSET) अणु	\
		PERCPU_INPUT(cacheline)					\
	पूर्ण phdr								\
	. = __per_cpu_load + SIZखातापूर्ण(.data..percpu);

/**
 * PERCPU_SECTION - define output section क्रम percpu area, simple version
 * @cacheline: cacheline size
 *
 * Align to PAGE_SIZE and outमाला_दो output section क्रम percpu area.  This
 * macro करोesn't manipulate @vaddr or @phdr and __per_cpu_load and
 * __per_cpu_start will be identical.
 *
 * This macro is equivalent to ALIGN(PAGE_SIZE); PERCPU_VADDR(@cacheline,,)
 * except that __per_cpu_load is defined as a relative symbol against
 * .data..percpu which is required क्रम relocatable x86_32 configuration.
 */
#घोषणा PERCPU_SECTION(cacheline)					\
	. = ALIGN(PAGE_SIZE);						\
	.data..percpu	: AT(ADDR(.data..percpu) - LOAD_OFFSET) अणु	\
		__per_cpu_load = .;					\
		PERCPU_INPUT(cacheline)					\
	पूर्ण


/*
 * Definition of the high level *_SECTION macros
 * They will fit only a subset of the architectures
 */


/*
 * Writeable data.
 * All sections are combined in a single .data section.
 * The sections following CONSTRUCTORS are arranged so their
 * typical alignment matches.
 * A cacheline is typical/always less than a PAGE_SIZE so
 * the sections that has this restriction (or similar)
 * is located beक्रमe the ones requiring PAGE_SIZE alignment.
 * NOSAVE_DATA starts and ends with a PAGE_SIZE alignment which
 * matches the requirement of PAGE_ALIGNED_DATA.
 *
 * use 0 as page_align अगर page_aligned data is not used */
#घोषणा RW_DATA(cacheline, pagealigned, inittask)			\
	. = ALIGN(PAGE_SIZE);						\
	.data : AT(ADDR(.data) - LOAD_OFFSET) अणु				\
		INIT_TASK_DATA(inittask)				\
		NOSAVE_DATA						\
		PAGE_ALIGNED_DATA(pagealigned)				\
		CACHELINE_ALIGNED_DATA(cacheline)			\
		READ_MOSTLY_DATA(cacheline)				\
		DATA_DATA						\
		CONSTRUCTORS						\
	पूर्ण								\
	BUG_TABLE							\

#घोषणा INIT_TEXT_SECTION(inittext_align)				\
	. = ALIGN(inittext_align);					\
	.init.text : AT(ADDR(.init.text) - LOAD_OFFSET) अणु		\
		_sinittext = .;						\
		INIT_TEXT						\
		_einittext = .;						\
	पूर्ण

#घोषणा INIT_DATA_SECTION(initsetup_align)				\
	.init.data : AT(ADDR(.init.data) - LOAD_OFFSET) अणु		\
		INIT_DATA						\
		INIT_SETUP(initsetup_align)				\
		INIT_CALLS						\
		CON_INITCALL						\
		INIT_RAM_FS						\
	पूर्ण

#घोषणा BSS_SECTION(sbss_align, bss_align, stop_align)			\
	. = ALIGN(sbss_align);						\
	__bss_start = .;						\
	SBSS(sbss_align)						\
	BSS(bss_align)							\
	. = ALIGN(stop_align);						\
	__bss_stop = .;
