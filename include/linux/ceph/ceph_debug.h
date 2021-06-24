<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_DEBUG_H
#घोषणा _FS_CEPH_DEBUG_H

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/माला.स>

#अगर_घोषित CONFIG_CEPH_LIB_PRETTYDEBUG

/*
 * wrap pr_debug to include a filename:lineno prefix on each line.
 * this incurs some overhead (kernel size and execution समय) due to
 * the extra function call at each call site.
 */

# अगर defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
#  define करोut(fmt, ...)						\
	pr_debug("%.*s %12.12s:%-4d : " fmt,				\
		 8 - (पूर्णांक)माप(KBUILD_MODNAME), "    ",		\
		 kbasename(__खाता__), __LINE__, ##__VA_ARGS__)
# अन्यथा
/* faux prपूर्णांकk call just to see any compiler warnings. */
#  define करोut(fmt, ...)	करो अणु				\
		अगर (0)						\
			prपूर्णांकk(KERN_DEBUG fmt, ##__VA_ARGS__);	\
	पूर्ण जबतक (0)
# endअगर

#अन्यथा

/*
 * or, just wrap pr_debug
 */
# define करोut(fmt, ...)	pr_debug(" " fmt, ##__VA_ARGS__)

#पूर्ण_अगर

#पूर्ण_अगर
