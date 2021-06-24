<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_HEAD_64_H
#घोषणा _ASM_POWERPC_HEAD_64_H

#समावेश <यंत्र/cache.h>

#अगर_घोषित __ASSEMBLY__
/*
 * We can't करो CPP stringअगरication and concatination directly पूर्णांकo the section
 * name क्रम some reason, so these macros can करो it क्रम us.
 */
.macro define_ftsec name
	.section ".head.text.\name\()","ax",@progbits
.endm
.macro define_data_ftsec name
	.section ".head.data.\name\()","a",@progbits
.endm
.macro use_ftsec name
	.section ".head.text.\name\()"
.endm

/*
 * Fixed (location) sections are used by खोलोing fixed sections and emitting
 * fixed section entries पूर्णांकo them beक्रमe closing them. Multiple fixed sections
 * can be खोलो at any समय.
 *
 * Each fixed section created in a .S file must have corresponding linkage
 * directives including location, added to  arch/घातerpc/kernel/vmlinux.lds.S
 *
 * For each fixed section, code is generated पूर्णांकo it in the order which it
 * appears in the source.  Fixed section entries can be placed at a fixed
 * location within the section using _LOCATION postअगरx variants. These must
 * be ordered according to their relative placements within the section.
 *
 * OPEN_FIXED_SECTION(section_name, start_address, end_address)
 * FIXED_SECTION_ENTRY_BEGIN(section_name, label1)
 *
 * USE_FIXED_SECTION(section_name)
 * label3:
 *     li  r10,128
 *     mv  r11,r10

 * FIXED_SECTION_ENTRY_BEGIN_LOCATION(section_name, label2, start_address, size)
 * FIXED_SECTION_ENTRY_END_LOCATION(section_name, label2, start_address, size)
 * CLOSE_FIXED_SECTION(section_name)
 *
 * ZERO_FIXED_SECTION can be used to emit zeroed data.
 *
 * Troubleshooting:
 * - If the build dies with "Error: attempt to move .org backwards" at
 *   CLOSE_FIXED_SECTION() or अन्यथाwhere, there may be something
 *   unexpected being added there. Remove the '. = x_len' line, rebuild, and
 *   check what is pushing the section करोwn.
 * - If the build dies in linking, check arch/घातerpc/tools/head_check.sh
 *   comments.
 * - If the kernel crashes or hangs in very early boot, it could be linker
 *   stubs at the start of the मुख्य text.
 */

#घोषणा OPEN_FIXED_SECTION(sname, start, end)			\
	sname##_start = (start);				\
	sname##_end = (end);					\
	sname##_len = (end) - (start);				\
	define_ftsec sname;					\
	. = 0x0;						\
start_##sname:

/*
 * .linker_stub_catch section is used to catch linker stubs from being
 * inserted in our .text section, above the start_text label (which अवरोधs
 * the ABS_ADDR calculation). See kernel/vmlinux.lds.S and tools/head_check.sh
 * क्रम more details. We would prefer to just keep a cacheline (0x80), but
 * 0x100 seems to be how the linker aligns branch stub groups.
 */
#अगर_घोषित CONFIG_LD_HEAD_STUB_CATCH
#घोषणा OPEN_TEXT_SECTION(start)				\
	.section ".linker_stub_catch","ax",@progbits;		\
linker_stub_catch:						\
	. = 0x4;						\
	text_start = (start) + 0x100;				\
	.section ".text","ax",@progbits;			\
	.balign 0x100;						\
start_text:
#अन्यथा
#घोषणा OPEN_TEXT_SECTION(start)				\
	text_start = (start);					\
	.section ".text","ax",@progbits;			\
	. = 0x0;						\
start_text:
#पूर्ण_अगर

#घोषणा ZERO_FIXED_SECTION(sname, start, end)			\
	sname##_start = (start);				\
	sname##_end = (end);					\
	sname##_len = (end) - (start);				\
	define_data_ftsec sname;				\
	. = 0x0;						\
	. = sname##_len;

#घोषणा USE_FIXED_SECTION(sname)				\
	fs_label = start_##sname;				\
	fs_start = sname##_start;				\
	use_ftsec sname;

#घोषणा USE_TEXT_SECTION()					\
	fs_label = start_text;					\
	fs_start = text_start;					\
	.text

#घोषणा CLOSE_FIXED_SECTION(sname)				\
	USE_FIXED_SECTION(sname);				\
	. = sname##_len;					\
end_##sname:


#घोषणा __FIXED_SECTION_ENTRY_BEGIN(sname, name, __align)	\
	USE_FIXED_SECTION(sname);				\
	.balign __align;					\
	.global name;						\
name:

#घोषणा FIXED_SECTION_ENTRY_BEGIN(sname, name)			\
	__FIXED_SECTION_ENTRY_BEGIN(sname, name, IFETCH_ALIGN_BYTES)

#घोषणा FIXED_SECTION_ENTRY_BEGIN_LOCATION(sname, name, start, size) \
	USE_FIXED_SECTION(sname);				\
	name##_start = (start);					\
	.अगर ((start) % (size) != 0);				\
	.error "Fixed section exception vector misalignment";	\
	.endअगर;							\
	.अगर ((size) != 0x20) && ((size) != 0x80) && ((size) != 0x100) && ((size) != 0x1000); \
	.error "Fixed section exception vector bad size";	\
	.endअगर;							\
	.अगर (start) < sname##_start;				\
	.error "Fixed section underflow";			\
	.पात;							\
	.endअगर;							\
	. = (start) - sname##_start;				\
	.global name;						\
name:

#घोषणा FIXED_SECTION_ENTRY_END_LOCATION(sname, name, start, size) \
	.अगर (start) + (size) > sname##_end;			\
	.error "Fixed section overflow";			\
	.पात;							\
	.endअगर;							\
	.अगर (. - name > (start) + (size) - name##_start);	\
	.error "Fixed entry overflow";				\
	.पात;							\
	.endअगर;							\
	. = ((start) + (size) - sname##_start);			\


/*
 * These macros are used to change symbols in other fixed sections to be
 * असलolute or related to our current fixed section.
 *
 * - DEFINE_FIXED_SYMBOL / FIXED_SYMBOL_ABS_ADDR is used to find the
 *   असलolute address of a symbol within a fixed section, from any section.
 *
 * - ABS_ADDR is used to find the असलolute address of any symbol, from within
 *   a fixed section.
 */
#घोषणा DEFINE_FIXED_SYMBOL(label)				\
	label##_असलolute = (label - fs_label + fs_start)

#घोषणा FIXED_SYMBOL_ABS_ADDR(label)				\
	(label##_असलolute)

#घोषणा ABS_ADDR(label) (label - fs_label + fs_start)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर	/* _ASM_POWERPC_HEAD_64_H */
