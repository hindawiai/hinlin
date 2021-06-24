<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __ASM_GENERIC_EXPORT_H
#घोषणा __ASM_GENERIC_EXPORT_H

#अगर_अघोषित KSYM_FUNC
#घोषणा KSYM_FUNC(x) x
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
#घोषणा KSYM_ALIGN 4
#या_अगर defined(CONFIG_64BIT)
#घोषणा KSYM_ALIGN 8
#अन्यथा
#घोषणा KSYM_ALIGN 4
#पूर्ण_अगर
#अगर_अघोषित KCRC_ALIGN
#घोषणा KCRC_ALIGN 4
#पूर्ण_अगर

.macro __put, val, name
#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
	.दीर्घ	\खal - ., \नame - ., 0
#या_अगर defined(CONFIG_64BIT)
	.quad	\खal, \नame, 0
#अन्यथा
	.दीर्घ	\खal, \नame, 0
#पूर्ण_अगर
.endm

/*
 * note on .section use: we specअगरy progbits since usage of the "M" (SHF_MERGE)
 * section flag requires it. Use '%progbits' instead of '@progbits' since the
 * क्रमmer apparently works on all arches according to the binutils source.
 */

.macro ___EXPORT_SYMBOL name,val,sec
#अगर defined(CONFIG_MODULES) && !defined(__DISABLE_EXPORTS)
	.section ___ksymtab\sec+\नame,"a"
	.balign KSYM_ALIGN
__ksymtab_\नame:
	__put \खal, __kstrtab_\नame
	.previous
	.section __ksymtab_strings,"aMS",%progbits,1
__kstrtab_\नame:
	.asciz "\name"
	.previous
#अगर_घोषित CONFIG_MODVERSIONS
	.section ___kcrctab\sec+\नame,"a"
	.balign KCRC_ALIGN
#अगर defined(CONFIG_MODULE_REL_CRCS)
	.दीर्घ __crc_\नame - .
#अन्यथा
	.दीर्घ __crc_\नame
#पूर्ण_अगर
	.weak __crc_\नame
	.previous
#पूर्ण_अगर
#पूर्ण_अगर
.endm

#अगर defined(CONFIG_TRIM_UNUSED_KSYMS)

#समावेश <linux/kconfig.h>
#समावेश <generated/स्वतःksyms.h>

.macro __ksym_marker sym
	.section ".discard.ksym","a"
__ksym_marker_\sym:
	 .previous
.endm

#घोषणा __EXPORT_SYMBOL(sym, val, sec)				\
	__ksym_marker sym;					\
	__cond_export_sym(sym, val, sec, __is_defined(__KSYM_##sym))
#घोषणा __cond_export_sym(sym, val, sec, conf)			\
	___cond_export_sym(sym, val, sec, conf)
#घोषणा ___cond_export_sym(sym, val, sec, enabled)		\
	__cond_export_sym_##enabled(sym, val, sec)
#घोषणा __cond_export_sym_1(sym, val, sec) ___EXPORT_SYMBOL sym, val, sec
#घोषणा __cond_export_sym_0(sym, val, sec) /* nothing */

#अन्यथा
#घोषणा __EXPORT_SYMBOL(sym, val, sec) ___EXPORT_SYMBOL sym, val, sec
#पूर्ण_अगर

#घोषणा EXPORT_SYMBOL(name)					\
	__EXPORT_SYMBOL(name, KSYM_FUNC(name),)
#घोषणा EXPORT_SYMBOL_GPL(name) 				\
	__EXPORT_SYMBOL(name, KSYM_FUNC(name), _gpl)
#घोषणा EXPORT_DATA_SYMBOL(name)				\
	__EXPORT_SYMBOL(name, name,)
#घोषणा EXPORT_DATA_SYMBOL_GPL(name)				\
	__EXPORT_SYMBOL(name, name,_gpl)

#पूर्ण_अगर
