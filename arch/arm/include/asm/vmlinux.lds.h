<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <यंत्र-generic/vmlinux.lds.h>

#अगर_घोषित CONFIG_HOTPLUG_CPU
#घोषणा ARM_CPU_DISCARD(x)
#घोषणा ARM_CPU_KEEP(x)		x
#अन्यथा
#घोषणा ARM_CPU_DISCARD(x)	x
#घोषणा ARM_CPU_KEEP(x)
#पूर्ण_अगर

#अगर (defined(CONFIG_SMP_ON_UP) && !defined(CONFIG_DEBUG_SPINLOCK)) || \
	defined(CONFIG_GENERIC_BUG) || defined(CONFIG_JUMP_LABEL)
#घोषणा ARM_EXIT_KEEP(x)	x
#घोषणा ARM_EXIT_DISCARD(x)
#अन्यथा
#घोषणा ARM_EXIT_KEEP(x)
#घोषणा ARM_EXIT_DISCARD(x)	x
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
#घोषणा ARM_MMU_KEEP(x)		x
#घोषणा ARM_MMU_DISCARD(x)
#अन्यथा
#घोषणा ARM_MMU_KEEP(x)
#घोषणा ARM_MMU_DISCARD(x)	x
#पूर्ण_अगर

#घोषणा PROC_INFO							\
		. = ALIGN(4);						\
		__proc_info_begin = .;					\
		*(.proc.info.init)					\
		__proc_info_end = .;

#घोषणा IDMAP_TEXT							\
		ALIGN_FUNCTION();					\
		__idmap_text_start = .;					\
		*(.idmap.text)						\
		__idmap_text_end = .;					\

#घोषणा ARM_DISCARD							\
		*(.ARM.exidx.निकास.text)					\
		*(.ARM.extab.निकास.text)					\
		*(.ARM.exidx.text.निकास)					\
		*(.ARM.extab.text.निकास)					\
		ARM_CPU_DISCARD(*(.ARM.exidx.cpuनिकास.text))		\
		ARM_CPU_DISCARD(*(.ARM.extab.cpuनिकास.text))		\
		ARM_EXIT_DISCARD(EXIT_TEXT)				\
		ARM_EXIT_DISCARD(EXIT_DATA)				\
		EXIT_CALL						\
		ARM_MMU_DISCARD(*(.text.fixup))				\
		ARM_MMU_DISCARD(*(__ex_table))				\
		COMMON_DISCARDS

/*
 * Sections that should stay zero sized, which is safer to explicitly
 * check instead of blindly discarding.
 */
#घोषणा ARM_ASSERTS							\
	.plt : अणु							\
		*(.iplt) *(.rel.iplt) *(.iplt) *(.igot.plt)		\
	पूर्ण								\
	ASSERT(SIZखातापूर्ण(.plt) == 0,					\
	       "Unexpected run-time procedure linkages detected!")

#घोषणा ARM_DETAILS							\
		ELF_DETAILS						\
		.ARM.attributes 0 : अणु *(.ARM.attributes) पूर्ण

#घोषणा ARM_STUBS_TEXT							\
		*(.gnu.warning)						\
		*(.glue_7)						\
		*(.glue_7t)						\
		*(.vfp11_veneer)                                        \
		*(.v4_bx)

#घोषणा ARM_TEXT							\
		IDMAP_TEXT						\
		__entry_text_start = .;					\
		*(.entry.text)						\
		__entry_text_end = .;					\
		IRQENTRY_TEXT						\
		SOFTIRQENTRY_TEXT					\
		TEXT_TEXT						\
		SCHED_TEXT						\
		CPUIDLE_TEXT						\
		LOCK_TEXT						\
		KPROBES_TEXT						\
		ARM_STUBS_TEXT						\
		. = ALIGN(4);						\
		*(.got)			/* Global offset table */	\
		ARM_CPU_KEEP(PROC_INFO)

/* Stack unwinding tables */
#घोषणा ARM_UNWIND_SECTIONS						\
	. = ALIGN(8);							\
	.ARM.unwind_idx : अणु						\
		__start_unwind_idx = .;					\
		*(.ARM.exidx*)						\
		__stop_unwind_idx = .;					\
	पूर्ण								\
	.ARM.unwind_tab : अणु						\
		__start_unwind_tab = .;					\
		*(.ARM.extab*)						\
		__stop_unwind_tab = .;					\
	पूर्ण

/*
 * The vectors and stubs are relocatable code, and the
 * only thing that matters is their relative offsets
 */
#घोषणा ARM_VECTORS							\
	__vectors_start = .;						\
	.vectors 0xffff0000 : AT(__vectors_start) अणु			\
		*(.vectors)						\
	पूर्ण								\
	. = __vectors_start + SIZखातापूर्ण(.vectors);				\
	__vectors_end = .;						\
									\
	__stubs_start = .;						\
	.stubs ADDR(.vectors) + 0x1000 : AT(__stubs_start) अणु		\
		*(.stubs)						\
	पूर्ण								\
	. = __stubs_start + SIZखातापूर्ण(.stubs);				\
	__stubs_end = .;						\
									\
	PROVIDE(vector_fiq_offset = vector_fiq - ADDR(.vectors));

#घोषणा ARM_TCM								\
	__itcm_start = ALIGN(4);					\
	.text_itcm ITCM_OFFSET : AT(__itcm_start - LOAD_OFFSET) अणु	\
		__sitcm_text = .;					\
		*(.tcm.text)						\
		*(.tcm.rodata)						\
		. = ALIGN(4);						\
		__eitcm_text = .;					\
	पूर्ण								\
	. = __itcm_start + SIZखातापूर्ण(.text_itcm);				\
									\
	__dtcm_start = .;						\
	.data_dtcm DTCM_OFFSET : AT(__dtcm_start - LOAD_OFFSET) अणु	\
		__sdtcm_data = .;					\
		*(.tcm.data)						\
		. = ALIGN(4);						\
		__edtcm_data = .;					\
	पूर्ण								\
	. = __dtcm_start + SIZखातापूर्ण(.data_dtcm);
