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
 * Added DRA7xxx specअगरic defines - Sriअक्षरan R<r.sriअक्षरan@ti.com>
 */

#समावेश "omap24xx.h"
#समावेश "omap34xx.h"
#समावेश "omap44xx.h"
#समावेश "ti81xx.h"
#समावेश "am33xx.h"
#समावेश "omap54xx.h"

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bitops.h>
#समावेश <linux/of.h>

/*
 * OMAP2+ is always defined as ARCH_MULTIPLATFORM in Kconfig
 */
#अघोषित MULTI_OMAP2
#घोषणा MULTI_OMAP2

/*
 * Omap device type i.e. EMU/HS/TST/GP/BAD
 */
#घोषणा OMAP2_DEVICE_TYPE_TEST		0
#घोषणा OMAP2_DEVICE_TYPE_EMU		1
#घोषणा OMAP2_DEVICE_TYPE_SEC		2
#घोषणा OMAP2_DEVICE_TYPE_GP		3
#घोषणा OMAP2_DEVICE_TYPE_BAD		4

पूर्णांक omap_type(व्योम);

/*
 * omap_rev bits:
 * SoC id bits	(0730, 1510, 1710, 2422...)	[31:16]
 * SoC revision	(See _REV_ defined in cpu.h)	[15:08]
 * SoC class bits (15xx, 16xx, 24xx, 34xx...)	[07:00]
 */
अचिन्हित पूर्णांक omap_rev(व्योम);

अटल अंतरभूत पूर्णांक soc_is_omap(व्योम)
अणु
	वापस omap_rev() != 0;
पूर्ण

/*
 * Get the SoC revision क्रम OMAP devices
 */
#घोषणा GET_OMAP_REVISION()	((omap_rev() >> 8) & 0xff)

/*
 * Macros to group OMAP पूर्णांकo cpu classes.
 * These can be used in most places.
 * soc_is_omap24xx():	True क्रम OMAP2420, OMAP2422, OMAP2423, OMAP2430
 * soc_is_omap242x():	True क्रम OMAP2420, OMAP2422, OMAP2423
 * soc_is_omap243x():	True क्रम OMAP2430
 * soc_is_omap343x():	True क्रम OMAP3430
 * soc_is_omap443x():	True क्रम OMAP4430
 * soc_is_omap446x():	True क्रम OMAP4460
 * soc_is_omap447x():	True क्रम OMAP4470
 * soc_is_omap543x():	True क्रम OMAP5430, OMAP5432
 */
#घोषणा GET_OMAP_CLASS	(omap_rev() & 0xff)

#घोषणा IS_OMAP_CLASS(class, id)			\
अटल अंतरभूत पूर्णांक is_omap ##class (व्योम)		\
अणु							\
	वापस (GET_OMAP_CLASS == (id)) ? 1 : 0;	\
पूर्ण

#घोषणा GET_AM_CLASS	((omap_rev() >> 24) & 0xff)

#घोषणा IS_AM_CLASS(class, id)				\
अटल अंतरभूत पूर्णांक is_am ##class (व्योम)			\
अणु							\
	वापस (GET_AM_CLASS == (id)) ? 1 : 0;		\
पूर्ण

#घोषणा GET_TI_CLASS	((omap_rev() >> 24) & 0xff)

#घोषणा IS_TI_CLASS(class, id)			\
अटल अंतरभूत पूर्णांक is_ti ##class (व्योम)		\
अणु							\
	वापस (GET_TI_CLASS == (id)) ? 1 : 0;	\
पूर्ण

#घोषणा GET_DRA_CLASS	((omap_rev() >> 24) & 0xff)

#घोषणा IS_DRA_CLASS(class, id)				\
अटल अंतरभूत पूर्णांक is_dra ##class (व्योम)			\
अणु							\
	वापस (GET_DRA_CLASS == (id)) ? 1 : 0;		\
पूर्ण

#घोषणा GET_OMAP_SUBCLASS	((omap_rev() >> 20) & 0x0fff)

#घोषणा IS_OMAP_SUBCLASS(subclass, id)			\
अटल अंतरभूत पूर्णांक is_omap ##subclass (व्योम)		\
अणु							\
	वापस (GET_OMAP_SUBCLASS == (id)) ? 1 : 0;	\
पूर्ण

#घोषणा IS_TI_SUBCLASS(subclass, id)			\
अटल अंतरभूत पूर्णांक is_ti ##subclass (व्योम)		\
अणु							\
	वापस (GET_OMAP_SUBCLASS == (id)) ? 1 : 0;	\
पूर्ण

#घोषणा IS_AM_SUBCLASS(subclass, id)			\
अटल अंतरभूत पूर्णांक is_am ##subclass (व्योम)		\
अणु							\
	वापस (GET_OMAP_SUBCLASS == (id)) ? 1 : 0;	\
पूर्ण

#घोषणा IS_DRA_SUBCLASS(subclass, id)			\
अटल अंतरभूत पूर्णांक is_dra ##subclass (व्योम)		\
अणु							\
	वापस (GET_OMAP_SUBCLASS == (id)) ? 1 : 0;	\
पूर्ण

#घोषणा GET_DRA_PACKAGE		(omap_rev() & 0xff)

#घोषणा IS_DRA_SUBCLASS_PACKAGE(subclass, package, id)			\
अटल अंतरभूत पूर्णांक is_dra ##subclass ##_ ##package (व्योम)		\
अणु									\
	वापस (is_dra ##subclass () && GET_DRA_PACKAGE == id) ? 1 : 0;	\
पूर्ण

IS_OMAP_CLASS(24xx, 0x24)
IS_OMAP_CLASS(34xx, 0x34)
IS_OMAP_CLASS(44xx, 0x44)
IS_AM_CLASS(35xx, 0x35)
IS_OMAP_CLASS(54xx, 0x54)
IS_AM_CLASS(33xx, 0x33)
IS_AM_CLASS(43xx, 0x43)

IS_TI_CLASS(81xx, 0x81)
IS_DRA_CLASS(7xx, 0x7)

IS_OMAP_SUBCLASS(242x, 0x242)
IS_OMAP_SUBCLASS(243x, 0x243)
IS_OMAP_SUBCLASS(343x, 0x343)
IS_OMAP_SUBCLASS(363x, 0x363)
IS_OMAP_SUBCLASS(443x, 0x443)
IS_OMAP_SUBCLASS(446x, 0x446)
IS_OMAP_SUBCLASS(447x, 0x447)
IS_OMAP_SUBCLASS(543x, 0x543)

IS_TI_SUBCLASS(816x, 0x816)
IS_TI_SUBCLASS(814x, 0x814)
IS_AM_SUBCLASS(335x, 0x335)
IS_AM_SUBCLASS(437x, 0x437)
IS_DRA_SUBCLASS(76x, 0x76)
IS_DRA_SUBCLASS_PACKAGE(76x, abz, 2)
IS_DRA_SUBCLASS_PACKAGE(76x, acd, 3)
IS_DRA_SUBCLASS(75x, 0x75)
IS_DRA_SUBCLASS(72x, 0x72)

#घोषणा soc_is_ti81xx()			0
#घोषणा soc_is_ti816x()			0
#घोषणा soc_is_ti814x()			0
#घोषणा soc_is_am35xx()			0
#घोषणा soc_is_am33xx()			0
#घोषणा soc_is_am335x()			0
#घोषणा soc_is_am43xx()			0
#घोषणा soc_is_am437x()			0
#घोषणा soc_is_omap44xx()		0
#घोषणा soc_is_omap443x()		0
#घोषणा soc_is_omap446x()		0
#घोषणा soc_is_omap447x()		0
#घोषणा soc_is_omap54xx()		0
#घोषणा soc_is_omap543x()		0
#घोषणा soc_is_dra7xx()			0
#घोषणा soc_is_dra76x()			0
#घोषणा soc_is_dra74x()			0
#घोषणा soc_is_dra72x()			0

#अगर defined(CONFIG_ARCH_OMAP2)
# define soc_is_omap24xx()		is_omap24xx()
#अन्यथा
# define soc_is_omap24xx()		0
#पूर्ण_अगर
#अगर defined(CONFIG_SOC_OMAP2420)
# define soc_is_omap242x()		is_omap242x()
#अन्यथा
# define soc_is_omap242x()		0
#पूर्ण_अगर
#अगर defined(CONFIG_SOC_OMAP2430)
# define soc_is_omap243x()		is_omap243x()
#अन्यथा
# define soc_is_omap243x()		0
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_OMAP3)
# define soc_is_omap34xx()		is_omap34xx()
# define soc_is_omap343x()		is_omap343x()
#अन्यथा
# define soc_is_omap34xx()		0
# define soc_is_omap343x()		0
#पूर्ण_अगर

/*
 * Macros to detect inभागidual cpu types.
 * These are only rarely needed.
 * soc_is_omap2420():	True क्रम OMAP2420
 * soc_is_omap2422():	True क्रम OMAP2422
 * soc_is_omap2423():	True क्रम OMAP2423
 * soc_is_omap2430():	True क्रम OMAP2430
 * soc_is_omap3430():	True क्रम OMAP3430
 */
#घोषणा GET_OMAP_TYPE	((omap_rev() >> 16) & 0xffff)

#घोषणा IS_OMAP_TYPE(type, id)				\
अटल अंतरभूत पूर्णांक is_omap ##type (व्योम)			\
अणु							\
	वापस (GET_OMAP_TYPE == (id)) ? 1 : 0;		\
पूर्ण

IS_OMAP_TYPE(2420, 0x2420)
IS_OMAP_TYPE(2422, 0x2422)
IS_OMAP_TYPE(2423, 0x2423)
IS_OMAP_TYPE(2430, 0x2430)
IS_OMAP_TYPE(3430, 0x3430)

#घोषणा soc_is_omap2420()		0
#घोषणा soc_is_omap2422()		0
#घोषणा soc_is_omap2423()		0
#घोषणा soc_is_omap2430()		0
#घोषणा soc_is_omap3430()		0
#घोषणा soc_is_omap3630()		0
#घोषणा soc_is_omap5430()		0

/* These are needed क्रम the common code */
#घोषणा soc_is_omap7xx()		0
#घोषणा soc_is_omap15xx()		0
#घोषणा soc_is_omap16xx()		0
#घोषणा soc_is_omap1510()		0
#घोषणा soc_is_omap1610()		0
#घोषणा soc_is_omap1611()		0
#घोषणा soc_is_omap1621()		0
#घोषणा soc_is_omap1710()		0
#घोषणा cpu_class_is_omap1()		0
#घोषणा cpu_class_is_omap2()		1

#अगर defined(CONFIG_ARCH_OMAP2)
# undef  soc_is_omap2420
# undef  soc_is_omap2422
# undef  soc_is_omap2423
# undef  soc_is_omap2430
# define soc_is_omap2420()		is_omap2420()
# define soc_is_omap2422()		is_omap2422()
# define soc_is_omap2423()		is_omap2423()
# define soc_is_omap2430()		is_omap2430()
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_OMAP3)
# undef soc_is_omap3430
# undef soc_is_ti81xx
# undef soc_is_ti816x
# undef soc_is_ti814x
# undef soc_is_am35xx
# define soc_is_omap3430()		is_omap3430()
# undef soc_is_omap3630
# define soc_is_omap3630()		is_omap363x()
# define soc_is_ti81xx()		is_ti81xx()
# define soc_is_ti816x()		is_ti816x()
# define soc_is_ti814x()		is_ti814x()
# define soc_is_am35xx()		is_am35xx()
#पूर्ण_अगर

# अगर defined(CONFIG_SOC_AM33XX)
# undef soc_is_am33xx
# undef soc_is_am335x
# define soc_is_am33xx()		is_am33xx()
# define soc_is_am335x()		is_am335x()
#पूर्ण_अगर

#अगर_घोषित	CONFIG_SOC_AM43XX
# undef soc_is_am43xx
# undef soc_is_am437x
# define soc_is_am43xx()		is_am43xx()
# define soc_is_am437x()		is_am437x()
#पूर्ण_अगर

# अगर defined(CONFIG_ARCH_OMAP4)
# undef soc_is_omap44xx
# undef soc_is_omap443x
# undef soc_is_omap446x
# undef soc_is_omap447x
# define soc_is_omap44xx()		is_omap44xx()
# define soc_is_omap443x()		is_omap443x()
# define soc_is_omap446x()		is_omap446x()
# define soc_is_omap447x()		is_omap447x()
# endअगर

# अगर defined(CONFIG_SOC_OMAP5)
# undef soc_is_omap54xx
# undef soc_is_omap543x
# define soc_is_omap54xx()		is_omap54xx()
# define soc_is_omap543x()		is_omap543x()
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_DRA7XX)
#अघोषित soc_is_dra7xx
#अघोषित soc_is_dra76x
#अघोषित soc_is_dra76x_abz
#अघोषित soc_is_dra76x_acd
#अघोषित soc_is_dra74x
#अघोषित soc_is_dra72x
#घोषणा soc_is_dra7xx()	is_dra7xx()
#घोषणा soc_is_dra76x()	is_dra76x()
#घोषणा soc_is_dra76x_abz()	is_dra76x_abz()
#घोषणा soc_is_dra76x_acd()	is_dra76x_acd()
#घोषणा soc_is_dra74x()	is_dra75x()
#घोषणा soc_is_dra72x()	is_dra72x()
#पूर्ण_अगर

/* Various silicon revisions क्रम omap2 */
#घोषणा OMAP242X_CLASS		0x24200024
#घोषणा OMAP2420_REV_ES1_0	OMAP242X_CLASS
#घोषणा OMAP2420_REV_ES2_0	(OMAP242X_CLASS | (0x1 << 8))

#घोषणा OMAP243X_CLASS		0x24300024
#घोषणा OMAP2430_REV_ES1_0	OMAP243X_CLASS

#घोषणा OMAP343X_CLASS		0x34300034
#घोषणा OMAP3430_REV_ES1_0	OMAP343X_CLASS
#घोषणा OMAP3430_REV_ES2_0	(OMAP343X_CLASS | (0x1 << 8))
#घोषणा OMAP3430_REV_ES2_1	(OMAP343X_CLASS | (0x2 << 8))
#घोषणा OMAP3430_REV_ES3_0	(OMAP343X_CLASS | (0x3 << 8))
#घोषणा OMAP3430_REV_ES3_1	(OMAP343X_CLASS | (0x4 << 8))
#घोषणा OMAP3430_REV_ES3_1_2	(OMAP343X_CLASS | (0x5 << 8))

#घोषणा OMAP363X_CLASS		0x36300034
#घोषणा OMAP3630_REV_ES1_0	OMAP363X_CLASS
#घोषणा OMAP3630_REV_ES1_1	(OMAP363X_CLASS | (0x1 << 8))
#घोषणा OMAP3630_REV_ES1_2	(OMAP363X_CLASS | (0x2 << 8))

#घोषणा TI816X_CLASS		0x81600081
#घोषणा TI8168_REV_ES1_0	TI816X_CLASS
#घोषणा TI8168_REV_ES1_1	(TI816X_CLASS | (0x1 << 8))
#घोषणा TI8168_REV_ES2_0	(TI816X_CLASS | (0x2 << 8))
#घोषणा TI8168_REV_ES2_1	(TI816X_CLASS | (0x3 << 8))

#घोषणा TI814X_CLASS		0x81400081
#घोषणा TI8148_REV_ES1_0	TI814X_CLASS
#घोषणा TI8148_REV_ES2_0	(TI814X_CLASS | (0x1 << 8))
#घोषणा TI8148_REV_ES2_1	(TI814X_CLASS | (0x2 << 8))

#घोषणा AM35XX_CLASS		0x35170034
#घोषणा AM35XX_REV_ES1_0	AM35XX_CLASS
#घोषणा AM35XX_REV_ES1_1	(AM35XX_CLASS | (0x1 << 8))

#घोषणा AM335X_CLASS		0x33500033
#घोषणा AM335X_REV_ES1_0	AM335X_CLASS
#घोषणा AM335X_REV_ES2_0	(AM335X_CLASS | (0x1 << 8))
#घोषणा AM335X_REV_ES2_1	(AM335X_CLASS | (0x2 << 8))

#घोषणा AM437X_CLASS		0x43700000
#घोषणा AM437X_REV_ES1_0	(AM437X_CLASS | (0x10 << 8))
#घोषणा AM437X_REV_ES1_1	(AM437X_CLASS | (0x11 << 8))
#घोषणा AM437X_REV_ES1_2	(AM437X_CLASS | (0x12 << 8))

#घोषणा OMAP443X_CLASS		0x44300044
#घोषणा OMAP4430_REV_ES1_0	(OMAP443X_CLASS | (0x10 << 8))
#घोषणा OMAP4430_REV_ES2_0	(OMAP443X_CLASS | (0x20 << 8))
#घोषणा OMAP4430_REV_ES2_1	(OMAP443X_CLASS | (0x21 << 8))
#घोषणा OMAP4430_REV_ES2_2	(OMAP443X_CLASS | (0x22 << 8))
#घोषणा OMAP4430_REV_ES2_3	(OMAP443X_CLASS | (0x23 << 8))

#घोषणा OMAP446X_CLASS		0x44600044
#घोषणा OMAP4460_REV_ES1_0	(OMAP446X_CLASS | (0x10 << 8))
#घोषणा OMAP4460_REV_ES1_1	(OMAP446X_CLASS | (0x11 << 8))

#घोषणा OMAP447X_CLASS		0x44700044
#घोषणा OMAP4470_REV_ES1_0	(OMAP447X_CLASS | (0x10 << 8))

#घोषणा OMAP54XX_CLASS		0x54000054
#घोषणा OMAP5430_REV_ES2_0	(OMAP54XX_CLASS | (0x30 << 16) | (0x20 << 8))
#घोषणा OMAP5432_REV_ES2_0	(OMAP54XX_CLASS | (0x32 << 16) | (0x20 << 8))

#घोषणा DRA7XX_CLASS		0x07000000
#घोषणा DRA762_REV_ES1_0	(DRA7XX_CLASS | (0x62 << 16) | (0x10 << 8))
#घोषणा DRA762_ABZ_REV_ES1_0	(DRA762_REV_ES1_0 | (2 << 0))
#घोषणा DRA762_ACD_REV_ES1_0	(DRA762_REV_ES1_0 | (3 << 0))
#घोषणा DRA752_REV_ES1_0	(DRA7XX_CLASS | (0x52 << 16) | (0x10 << 8))
#घोषणा DRA752_REV_ES1_1	(DRA7XX_CLASS | (0x52 << 16) | (0x11 << 8))
#घोषणा DRA752_REV_ES2_0	(DRA7XX_CLASS | (0x52 << 16) | (0x20 << 8))
#घोषणा DRA722_REV_ES1_0	(DRA7XX_CLASS | (0x22 << 16) | (0x10 << 8))
#घोषणा DRA722_REV_ES2_0	(DRA7XX_CLASS | (0x22 << 16) | (0x20 << 8))
#घोषणा DRA722_REV_ES2_1	(DRA7XX_CLASS | (0x22 << 16) | (0x21 << 8))

व्योम omap2xxx_check_revision(व्योम);
व्योम omap3xxx_check_revision(व्योम);
व्योम omap4xxx_check_revision(व्योम);
व्योम omap5xxx_check_revision(व्योम);
व्योम dra7xxx_check_revision(व्योम);
व्योम omap3xxx_check_features(व्योम);
व्योम ti81xx_check_features(व्योम);
व्योम am33xx_check_features(व्योम);
व्योम omap4xxx_check_features(व्योम);

/*
 * Runसमय detection of OMAP3 features
 *
 * OMAP3_HAS_IO_CHAIN_CTRL: Some later members of the OMAP3 chip
 *    family have OS-level control over the I/O chain घड़ी.  This is
 *    to aव्योम a winकरोw during which wakeups could potentially be lost
 *    during घातerकरोमुख्य transitions.  If this bit is set, it
 *    indicates that the chip करोes support OS-level control of this
 *    feature.
 */
बाह्य u32 omap_features;

#घोषणा OMAP3_HAS_L2CACHE		BIT(0)
#घोषणा OMAP3_HAS_IVA			BIT(1)
#घोषणा OMAP3_HAS_SGX			BIT(2)
#घोषणा OMAP3_HAS_NEON			BIT(3)
#घोषणा OMAP3_HAS_ISP			BIT(4)
#घोषणा OMAP3_HAS_192MHZ_CLK		BIT(5)
#घोषणा OMAP3_HAS_IO_WAKEUP		BIT(6)
#घोषणा OMAP3_HAS_SDRC			BIT(7)
#घोषणा OMAP3_HAS_IO_CHAIN_CTRL		BIT(8)
#घोषणा OMAP4_HAS_PERF_SILICON		BIT(9)


#घोषणा OMAP3_HAS_FEATURE(feat,flag)			\
अटल अंतरभूत अचिन्हित पूर्णांक omap3_has_ ##feat(व्योम)	\
अणु							\
	वापस omap_features & OMAP3_HAS_ ##flag;	\
पूर्ण							\

OMAP3_HAS_FEATURE(l2cache, L2CACHE)
OMAP3_HAS_FEATURE(sgx, SGX)
OMAP3_HAS_FEATURE(iva, IVA)
OMAP3_HAS_FEATURE(neon, NEON)
OMAP3_HAS_FEATURE(isp, ISP)
OMAP3_HAS_FEATURE(192mhz_clk, 192MHZ_CLK)
OMAP3_HAS_FEATURE(io_wakeup, IO_WAKEUP)
OMAP3_HAS_FEATURE(sdrc, SDRC)
OMAP3_HAS_FEATURE(io_chain_ctrl, IO_CHAIN_CTRL)

/*
 * Runसमय detection of OMAP4 features
 */
#घोषणा OMAP4_HAS_FEATURE(feat, flag)			\
अटल अंतरभूत अचिन्हित पूर्णांक omap4_has_ ##feat(व्योम)	\
अणु							\
	वापस omap_features & OMAP4_HAS_ ##flag;	\
पूर्ण							\

OMAP4_HAS_FEATURE(perf_silicon, PERF_SILICON)

/*
 * We need to make sure omap initcalls करोn't run when
 * multiplatक्रमm kernels are booted on other SoCs.
 */
#घोषणा omap_initcall(level, fn)		\
अटल पूर्णांक __init __used __##fn(व्योम)		\
अणु						\
	अगर (!soc_is_omap())			\
		वापस 0;			\
	वापस fn();				\
पूर्ण						\
level(__##fn);

#घोषणा omap_early_initcall(fn)		omap_initcall(early_initcall, fn)
#घोषणा omap_core_initcall(fn)		omap_initcall(core_initcall, fn)
#घोषणा omap_postcore_initcall(fn)	omap_initcall(postcore_initcall, fn)
#घोषणा omap_arch_initcall(fn)		omap_initcall(arch_initcall, fn)
#घोषणा omap_subsys_initcall(fn)	omap_initcall(subsys_initcall, fn)
#घोषणा omap_device_initcall(fn)	omap_initcall(device_initcall, fn)
#घोषणा omap_late_initcall(fn)		omap_initcall(late_initcall, fn)
#घोषणा omap_late_initcall_sync(fn)	omap_initcall(late_initcall_sync, fn)

/* Legacy defines, these can be हटाओd when users are हटाओd */
#घोषणा cpu_is_omap2420()	soc_is_omap2420()
#घोषणा cpu_is_omap2422()	soc_is_omap2422()
#घोषणा cpu_is_omap242x()	soc_is_omap242x()
#घोषणा cpu_is_omap2430()	soc_is_omap2430()
#घोषणा cpu_is_omap243x()	soc_is_omap243x()
#घोषणा cpu_is_omap24xx()	soc_is_omap24xx()
#घोषणा cpu_is_omap3430()	soc_is_omap3430()
#घोषणा cpu_is_omap343x()	soc_is_omap343x()
#घोषणा cpu_is_omap34xx()	soc_is_omap34xx()
#घोषणा cpu_is_omap3630()	soc_is_omap3630()
#घोषणा cpu_is_omap443x()	soc_is_omap443x()
#घोषणा cpu_is_omap446x()	soc_is_omap446x()
#घोषणा cpu_is_omap44xx()	soc_is_omap44xx()
#घोषणा cpu_is_ti814x()		soc_is_ti814x()
#घोषणा cpu_is_ti816x()		soc_is_ti816x()
#घोषणा cpu_is_ti81xx()		soc_is_ti81xx()

#पूर्ण_अगर	/* __ASSEMBLY__ */
