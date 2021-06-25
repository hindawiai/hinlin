<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_KPROBES_H
#घोषणा _ASM_GENERIC_KPROBES_H

#अगर defined(__KERNEL__) && !defined(__ASSEMBLY__)
#अगर_घोषित CONFIG_KPROBES
/*
 * Blacklist ganerating macro. Specअगरy functions which is not probed
 * by using this macro.
 */
# define __NOKPROBE_SYMBOL(fname)				\
अटल अचिन्हित दीर्घ __used					\
	__section("_kprobe_blacklist")				\
	_kbl_addr_##fname = (अचिन्हित दीर्घ)fname;
# define NOKPROBE_SYMBOL(fname)	__NOKPROBE_SYMBOL(fname)
/* Use this to क्रमbid a kprobes attach on very low level functions */
# define __kprobes	__section(".kprobes.text")
# define nokprobe_अंतरभूत	__always_अंतरभूत
#अन्यथा
# define NOKPROBE_SYMBOL(fname)
# define __kprobes
# define nokprobe_अंतरभूत	अंतरभूत
#पूर्ण_अगर
#पूर्ण_अगर /* defined(__KERNEL__) && !defined(__ASSEMBLY__) */

#पूर्ण_अगर /* _ASM_GENERIC_KPROBES_H */
