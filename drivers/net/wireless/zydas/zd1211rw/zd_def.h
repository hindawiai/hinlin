<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 */

#अगर_अघोषित _ZD_DEF_H
#घोषणा _ZD_DEF_H

#समावेश <linux/kernel.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/device.h>

प्रकार u16 __nocast zd_addr_t;

#घोषणा dev_prपूर्णांकk_f(level, dev, fmt, args...) \
	dev_prपूर्णांकk(level, dev, "%s() " fmt, __func__, ##args)

#अगर_घोषित DEBUG
#  define dev_dbg_f(dev, fmt, args...) \
	  dev_prपूर्णांकk_f(KERN_DEBUG, dev, fmt, ## args)
#  define dev_dbg_f_limit(dev, fmt, args...) करो अणु \
	अगर (net_ratelimit()) \
		dev_prपूर्णांकk_f(KERN_DEBUG, dev, fmt, ## args); \
पूर्ण जबतक (0)
#  define dev_dbg_f_cond(dev, cond, fmt, args...) (अणु \
	bool __cond = !!(cond); \
	अगर (unlikely(__cond)) \
		dev_prपूर्णांकk_f(KERN_DEBUG, dev, fmt, ## args); \
पूर्ण)
#अन्यथा
#  define dev_dbg_f(dev, fmt, args...) करो अणु (व्योम)(dev); पूर्ण जबतक (0)
#  define dev_dbg_f_limit(dev, fmt, args...) करो अणु (व्योम)(dev); पूर्ण जबतक (0)
#  define dev_dbg_f_cond(dev, cond, fmt, args...) करो अणु (व्योम)(dev); पूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG */

#अगर_घोषित DEBUG
#  define ZD_ASSERT(x) \
करो अणु \
	अगर (unlikely(!(x))) अणु \
		pr_debug("%s:%d ASSERT %s VIOLATED!\n", \
			__खाता__, __LINE__, __stringअगरy(x)); \
		dump_stack(); \
	पूर्ण \
पूर्ण जबतक (0)
#अन्यथा
#  define ZD_ASSERT(x) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित DEBUG
#  define ZD_MEMCLEAR(poपूर्णांकer, size) स_रखो((poपूर्णांकer), 0xff, (size))
#अन्यथा
#  define ZD_MEMCLEAR(poपूर्णांकer, size) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* _ZD_DEF_H */
