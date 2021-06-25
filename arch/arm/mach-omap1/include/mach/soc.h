<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OMAP cpu type detection
 *
 * Copyright (C) 2004, 2008 Nokia Corporation
 *
 * Copyright (C) 2009-11 Texas Instruments.
 *
 * Written by Tony Lindgren <tony.lindgren@nokia.com>
 *
 * Added OMAP4/5 specअगरic defines - Santosh Shilimkar<santosh.shilimkar@ti.com>
 */

#अगर_अघोषित __ASM_ARCH_OMAP_CPU_H
#घोषणा __ASM_ARCH_OMAP_CPU_H

#समावेश <यंत्र/irq.h>
#समावेश <mach/hardware.h>
#समावेश <mach/irqs.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bitops.h>

/*
 * Test अगर multicore OMAP support is needed
 */
#अघोषित MULTI_OMAP1
#अघोषित OMAP_NAME

#अगर_घोषित CONFIG_ARCH_OMAP730
# अगरdef OMAP_NAME
#  undef  MULTI_OMAP1
#  define MULTI_OMAP1
# अन्यथा
#  define OMAP_NAME omap730
# endअगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP850
# अगरdef OMAP_NAME
#  undef  MULTI_OMAP1
#  define MULTI_OMAP1
# अन्यथा
#  define OMAP_NAME omap850
# endअगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP15XX
# अगरdef OMAP_NAME
#  undef  MULTI_OMAP1
#  define MULTI_OMAP1
# अन्यथा
#  define OMAP_NAME omap1510
# endअगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP16XX
# अगरdef OMAP_NAME
#  undef  MULTI_OMAP1
#  define MULTI_OMAP1
# अन्यथा
#  define OMAP_NAME omap16xx
# endअगर
#पूर्ण_अगर

/*
 * omap_rev bits:
 * CPU id bits	(0730, 1510, 1710, 2422...)	[31:16]
 * CPU revision	(See _REV_ defined in cpu.h)	[15:08]
 * CPU class bits (15xx, 16xx, 24xx, 34xx...)	[07:00]
 */
अचिन्हित पूर्णांक omap_rev(व्योम);

/*
 * Get the CPU revision क्रम OMAP devices
 */
#घोषणा GET_OMAP_REVISION()	((omap_rev() >> 8) & 0xff)

/*
 * Macros to group OMAP पूर्णांकo cpu classes.
 * These can be used in most places.
 * cpu_is_omap7xx():	True क्रम OMAP730, OMAP850
 * cpu_is_omap15xx():	True क्रम OMAP1510, OMAP5910 and OMAP310
 * cpu_is_omap16xx():	True क्रम OMAP1610, OMAP5912 and OMAP1710
 */
#घोषणा GET_OMAP_CLASS	(omap_rev() & 0xff)

#घोषणा IS_OMAP_CLASS(class, id)			\
अटल अंतरभूत पूर्णांक is_omap ##class (व्योम)		\
अणु							\
	वापस (GET_OMAP_CLASS == (id)) ? 1 : 0;	\
पूर्ण

#घोषणा GET_OMAP_SUBCLASS	((omap_rev() >> 20) & 0x0fff)

#घोषणा IS_OMAP_SUBCLASS(subclass, id)			\
अटल अंतरभूत पूर्णांक is_omap ##subclass (व्योम)		\
अणु							\
	वापस (GET_OMAP_SUBCLASS == (id)) ? 1 : 0;	\
पूर्ण

IS_OMAP_CLASS(7xx, 0x07)
IS_OMAP_CLASS(15xx, 0x15)
IS_OMAP_CLASS(16xx, 0x16)

#घोषणा cpu_is_omap7xx()		0
#घोषणा cpu_is_omap15xx()		0
#घोषणा cpu_is_omap16xx()		0

#अगर defined(MULTI_OMAP1)
# अगर defined(CONFIG_ARCH_OMAP730)
#  undef  cpu_is_omap7xx
#  define cpu_is_omap7xx()		is_omap7xx()
# endअगर
# अगर defined(CONFIG_ARCH_OMAP850)
#  undef  cpu_is_omap7xx
#  define cpu_is_omap7xx()		is_omap7xx()
# endअगर
# अगर defined(CONFIG_ARCH_OMAP15XX)
#  undef  cpu_is_omap15xx
#  define cpu_is_omap15xx()		is_omap15xx()
# endअगर
# अगर defined(CONFIG_ARCH_OMAP16XX)
#  undef  cpu_is_omap16xx
#  define cpu_is_omap16xx()		is_omap16xx()
# endअगर
#अन्यथा
# अगर defined(CONFIG_ARCH_OMAP730)
#  undef  cpu_is_omap7xx
#  define cpu_is_omap7xx()		1
# endअगर
# अगर defined(CONFIG_ARCH_OMAP850)
#  undef  cpu_is_omap7xx
#  define cpu_is_omap7xx()		1
# endअगर
# अगर defined(CONFIG_ARCH_OMAP15XX)
#  undef  cpu_is_omap15xx
#  define cpu_is_omap15xx()		1
# endअगर
# अगर defined(CONFIG_ARCH_OMAP16XX)
#  undef  cpu_is_omap16xx
#  define cpu_is_omap16xx()		1
# endअगर
#पूर्ण_अगर

/*
 * Macros to detect inभागidual cpu types.
 * These are only rarely needed.
 * cpu_is_omap310():	True क्रम OMAP310
 * cpu_is_omap1510():	True क्रम OMAP1510
 * cpu_is_omap1610():	True क्रम OMAP1610
 * cpu_is_omap1611():	True क्रम OMAP1611
 * cpu_is_omap5912():	True क्रम OMAP5912
 * cpu_is_omap1621():	True क्रम OMAP1621
 * cpu_is_omap1710():	True क्रम OMAP1710
 */
#घोषणा GET_OMAP_TYPE	((omap_rev() >> 16) & 0xffff)

#घोषणा IS_OMAP_TYPE(type, id)				\
अटल अंतरभूत पूर्णांक is_omap ##type (व्योम)			\
अणु							\
	वापस (GET_OMAP_TYPE == (id)) ? 1 : 0;		\
पूर्ण

IS_OMAP_TYPE(310, 0x0310)
IS_OMAP_TYPE(1510, 0x1510)
IS_OMAP_TYPE(1610, 0x1610)
IS_OMAP_TYPE(1611, 0x1611)
IS_OMAP_TYPE(5912, 0x1611)
IS_OMAP_TYPE(1621, 0x1621)
IS_OMAP_TYPE(1710, 0x1710)

#घोषणा cpu_is_omap310()		0
#घोषणा cpu_is_omap1510()		0
#घोषणा cpu_is_omap1610()		0
#घोषणा cpu_is_omap5912()		0
#घोषणा cpu_is_omap1611()		0
#घोषणा cpu_is_omap1621()		0
#घोषणा cpu_is_omap1710()		0

/* These are needed to compile common code */
#अगर_घोषित CONFIG_ARCH_OMAP1
#घोषणा cpu_is_omap242x()		0
#घोषणा cpu_is_omap2430()		0
#घोषणा cpu_is_omap243x()		0
#घोषणा cpu_is_omap24xx()		0
#घोषणा cpu_is_omap34xx()		0
#घोषणा cpu_is_omap44xx()		0
#घोषणा soc_is_omap54xx()		0
#घोषणा soc_is_dra7xx()			0
#घोषणा soc_is_am33xx()			0
#घोषणा cpu_class_is_omap1()		1
#घोषणा cpu_class_is_omap2()		0
#पूर्ण_अगर

/*
 * Whether we have MULTI_OMAP1 or not, we still need to distinguish
 * between 310 vs. 1510 and 1611B/5912 vs. 1710.
 */

#अगर defined(CONFIG_ARCH_OMAP15XX)
# undef  cpu_is_omap310
# undef  cpu_is_omap1510
# define cpu_is_omap310()		is_omap310()
# define cpu_is_omap1510()		is_omap1510()
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_OMAP16XX)
# undef  cpu_is_omap1610
# undef  cpu_is_omap1611
# undef  cpu_is_omap5912
# undef  cpu_is_omap1621
# undef  cpu_is_omap1710
# define cpu_is_omap1610()		is_omap1610()
# define cpu_is_omap1611()		is_omap1611()
# define cpu_is_omap5912()		is_omap5912()
# define cpu_is_omap1621()		is_omap1621()
# define cpu_is_omap1710()		is_omap1710()
#पूर्ण_अगर

#पूर्ण_अगर	/* __ASSEMBLY__ */
#पूर्ण_अगर
