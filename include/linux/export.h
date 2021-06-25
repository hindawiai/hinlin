<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _LINUX_EXPORT_H
#घोषणा _LINUX_EXPORT_H

/*
 * Export symbols from the kernel to modules.  Forked from module.h
 * to reduce the amount of poपूर्णांकless cruft we feed to gcc when only
 * exporting a simple symbol or two.
 *
 * Try not to add #समावेशs here.  It slows compilation and makes kernel
 * hackers place grumpy comments in header files.
 */

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित MODULE
बाह्य काष्ठा module __this_module;
#घोषणा THIS_MODULE (&__this_module)
#अन्यथा
#घोषणा THIS_MODULE ((काष्ठा module *)0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MODVERSIONS
/* Mark the CRC weak since genksyms apparently decides not to
 * generate a checksums क्रम some symbols */
#अगर defined(CONFIG_MODULE_REL_CRCS)
#घोषणा __CRC_SYMBOL(sym, sec)						\
	यंत्र("	.section \"___kcrctab" sec "+" #sym "\", \"a\"	\n"	\
	    "	.weak	__crc_" #sym "				\n"	\
	    "	.long	__crc_" #sym " - .			\n"	\
	    "	.previous					\n")
#अन्यथा
#घोषणा __CRC_SYMBOL(sym, sec)						\
	यंत्र("	.section \"___kcrctab" sec "+" #sym "\", \"a\"	\n"	\
	    "	.weak	__crc_" #sym "				\n"	\
	    "	.long	__crc_" #sym "				\n"	\
	    "	.previous					\n")
#पूर्ण_अगर
#अन्यथा
#घोषणा __CRC_SYMBOL(sym, sec)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
#समावेश <linux/compiler.h>
/*
 * Emit the ksymtab entry as a pair of relative references: this reduces
 * the size by half on 64-bit architectures, and eliminates the need क्रम
 * असलolute relocations that require runसमय processing on relocatable
 * kernels.
 */
#घोषणा __KSYMTAB_ENTRY(sym, sec)					\
	__ADDRESSABLE(sym)						\
	यंत्र("	.section \"___ksymtab" sec "+" #sym "\", \"a\"	\n"	\
	    "	.balign	4					\n"	\
	    "__ksymtab_" #sym ":				\n"	\
	    "	.long	" #sym "- .				\n"	\
	    "	.long	__kstrtab_" #sym "- .			\n"	\
	    "	.long	__kstrtabns_" #sym "- .			\n"	\
	    "	.previous					\n")

काष्ठा kernel_symbol अणु
	पूर्णांक value_offset;
	पूर्णांक name_offset;
	पूर्णांक namespace_offset;
पूर्ण;
#अन्यथा
#घोषणा __KSYMTAB_ENTRY(sym, sec)					\
	अटल स्थिर काष्ठा kernel_symbol __ksymtab_##sym		\
	__attribute__((section("___ksymtab" sec "+" #sym), used))	\
	__aligned(माप(व्योम *))					\
	= अणु (अचिन्हित दीर्घ)&sym, __kstrtab_##sym, __kstrtabns_##sym पूर्ण

काष्ठा kernel_symbol अणु
	अचिन्हित दीर्घ value;
	स्थिर अक्षर *name;
	स्थिर अक्षर *namespace;
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित __GENKSYMS__

#घोषणा ___EXPORT_SYMBOL(sym, sec, ns)	__GENKSYMS_EXPORT_SYMBOL(sym)

#अन्यथा

/*
 * For every exported symbol, करो the following:
 *
 * - If applicable, place a CRC entry in the __kcrctab section.
 * - Put the name of the symbol and namespace (empty string "" क्रम none) in
 *   __ksymtab_strings.
 * - Place a काष्ठा kernel_symbol entry in the __ksymtab section.
 *
 * note on .section use: we specअगरy progbits since usage of the "M" (SHF_MERGE)
 * section flag requires it. Use '%progbits' instead of '@progbits' since the
 * क्रमmer apparently works on all arches according to the binutils source.
 */
#घोषणा ___EXPORT_SYMBOL(sym, sec, ns)						\
	बाह्य typeof(sym) sym;							\
	बाह्य स्थिर अक्षर __kstrtab_##sym[];					\
	बाह्य स्थिर अक्षर __kstrtabns_##sym[];					\
	__CRC_SYMBOL(sym, sec);							\
	यंत्र("	.section \"__ksymtab_strings\",\"aMS\",%progbits,1	\n"	\
	    "__kstrtab_" #sym ":					\n"	\
	    "	.asciz 	\"" #sym "\"					\n"	\
	    "__kstrtabns_" #sym ":					\n"	\
	    "	.asciz 	\"" ns "\"					\n"	\
	    "	.previous						\n");	\
	__KSYMTAB_ENTRY(sym, sec)

#पूर्ण_अगर

#अगर !defined(CONFIG_MODULES) || defined(__DISABLE_EXPORTS)

/*
 * Allow symbol exports to be disabled completely so that C code may
 * be reused in other execution contexts such as the UEFI stub or the
 * decompressor.
 */
#घोषणा __EXPORT_SYMBOL(sym, sec, ns)

#या_अगर defined(CONFIG_TRIM_UNUSED_KSYMS)

#समावेश <generated/स्वतःksyms.h>

/*
 * For fine grained build dependencies, we want to tell the build प्रणाली
 * about each possible exported symbol even अगर they're not actually exported.
 * We use a symbol pattern __ksym_marker_<symbol> that the build प्रणाली filters
 * from the $(NM) output (see scripts/gen_ksymdeps.sh). These symbols are
 * discarded in the final link stage.
 */
#घोषणा __ksym_marker(sym)	\
	अटल पूर्णांक __ksym_marker_##sym[0] __section(".discard.ksym") __used

#घोषणा __EXPORT_SYMBOL(sym, sec, ns)					\
	__ksym_marker(sym);						\
	__cond_export_sym(sym, sec, ns, __is_defined(__KSYM_##sym))
#घोषणा __cond_export_sym(sym, sec, ns, conf)				\
	___cond_export_sym(sym, sec, ns, conf)
#घोषणा ___cond_export_sym(sym, sec, ns, enabled)			\
	__cond_export_sym_##enabled(sym, sec, ns)
#घोषणा __cond_export_sym_1(sym, sec, ns) ___EXPORT_SYMBOL(sym, sec, ns)
#घोषणा __cond_export_sym_0(sym, sec, ns) /* nothing */

#अन्यथा

#घोषणा __EXPORT_SYMBOL(sym, sec, ns)	___EXPORT_SYMBOL(sym, sec, ns)

#पूर्ण_अगर /* CONFIG_MODULES */

#अगर_घोषित DEFAULT_SYMBOL_NAMESPACE
#समावेश <linux/stringअगरy.h>
#घोषणा _EXPORT_SYMBOL(sym, sec)	__EXPORT_SYMBOL(sym, sec, __stringअगरy(DEFAULT_SYMBOL_NAMESPACE))
#अन्यथा
#घोषणा _EXPORT_SYMBOL(sym, sec)	__EXPORT_SYMBOL(sym, sec, "")
#पूर्ण_अगर

#घोषणा EXPORT_SYMBOL(sym)		_EXPORT_SYMBOL(sym, "")
#घोषणा EXPORT_SYMBOL_GPL(sym)		_EXPORT_SYMBOL(sym, "_gpl")
#घोषणा EXPORT_SYMBOL_NS(sym, ns)	__EXPORT_SYMBOL(sym, "", #ns)
#घोषणा EXPORT_SYMBOL_NS_GPL(sym, ns)	__EXPORT_SYMBOL(sym, "_gpl", #ns)

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _LINUX_EXPORT_H */
