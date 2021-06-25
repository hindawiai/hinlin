<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * OMAP Smartreflex Defines and Routines
 *
 * Author: Thara Gopinath	<thara@ti.com>
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Thara Gopinath <thara@ti.com>
 *
 * Copyright (C) 2008 Nokia Corporation
 * Kalle Jokiniemi
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Lesly A M <x0080970@ti.com>
 */

#अगर_अघोषित __POWER_SMARTREFLEX_H
#घोषणा __POWER_SMARTREFLEX_H

#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_data/voltage-omap.h>

/*
 * Dअगरferent Smartreflex IPs version. The v1 is the 65nm version used in
 * OMAP3430. The v2 is the update क्रम the 45nm version of the IP
 * used in OMAP3630 and OMAP4430
 */
#घोषणा SR_TYPE_V1	1
#घोषणा SR_TYPE_V2	2

/* SMART REFLEX REG ADDRESS OFFSET */
#घोषणा SRCONFIG		0x00
#घोषणा SRSTATUS		0x04
#घोषणा SENVAL			0x08
#घोषणा SENMIN			0x0C
#घोषणा SENMAX			0x10
#घोषणा SENAVG			0x14
#घोषणा AVGWEIGHT		0x18
#घोषणा NVALUERECIPROCAL	0x1c
#घोषणा SENERROR_V1		0x20
#घोषणा ERRCONFIG_V1		0x24
#घोषणा IRQ_EOI			0x20
#घोषणा IRQSTATUS_RAW		0x24
#घोषणा IRQSTATUS		0x28
#घोषणा IRQENABLE_SET		0x2C
#घोषणा IRQENABLE_CLR		0x30
#घोषणा SENERROR_V2		0x34
#घोषणा ERRCONFIG_V2		0x38

/* Bit/Shअगरt Positions */

/* SRCONFIG */
#घोषणा SRCONFIG_ACCUMDATA_SHIFT	22
#घोषणा SRCONFIG_SRCLKLENGTH_SHIFT	12
#घोषणा SRCONFIG_SENNENABLE_V1_SHIFT	5
#घोषणा SRCONFIG_SENPENABLE_V1_SHIFT	3
#घोषणा SRCONFIG_SENNENABLE_V2_SHIFT	1
#घोषणा SRCONFIG_SENPENABLE_V2_SHIFT	0
#घोषणा SRCONFIG_CLKCTRL_SHIFT		0

#घोषणा SRCONFIG_ACCUMDATA_MASK		(0x3ff << 22)

#घोषणा SRCONFIG_SRENABLE		BIT(11)
#घोषणा SRCONFIG_SENENABLE		BIT(10)
#घोषणा SRCONFIG_ERRGEN_EN		BIT(9)
#घोषणा SRCONFIG_MINMAXAVG_EN		BIT(8)
#घोषणा SRCONFIG_DELAYCTRL		BIT(2)

/* AVGWEIGHT */
#घोषणा AVGWEIGHT_SENPAVGWEIGHT_SHIFT	2
#घोषणा AVGWEIGHT_SENNAVGWEIGHT_SHIFT	0

/* NVALUERECIPROCAL */
#घोषणा NVALUERECIPROCAL_SENPGAIN_SHIFT	20
#घोषणा NVALUERECIPROCAL_SENNGAIN_SHIFT	16
#घोषणा NVALUERECIPROCAL_RNSENP_SHIFT	8
#घोषणा NVALUERECIPROCAL_RNSENN_SHIFT	0

/* ERRCONFIG */
#घोषणा ERRCONFIG_ERRWEIGHT_SHIFT	16
#घोषणा ERRCONFIG_ERRMAXLIMIT_SHIFT	8
#घोषणा ERRCONFIG_ERRMINLIMIT_SHIFT	0

#घोषणा SR_ERRWEIGHT_MASK		(0x07 << 16)
#घोषणा SR_ERRMAXLIMIT_MASK		(0xff << 8)
#घोषणा SR_ERRMINLIMIT_MASK		(0xff << 0)

#घोषणा ERRCONFIG_VPBOUNDINTEN_V1	BIT(31)
#घोषणा ERRCONFIG_VPBOUNDINTST_V1	BIT(30)
#घोषणा	ERRCONFIG_MCUACCUMINTEN		BIT(29)
#घोषणा ERRCONFIG_MCUACCUMINTST		BIT(28)
#घोषणा	ERRCONFIG_MCUVALIDINTEN		BIT(27)
#घोषणा ERRCONFIG_MCUVALIDINTST		BIT(26)
#घोषणा ERRCONFIG_MCUBOUNDINTEN		BIT(25)
#घोषणा	ERRCONFIG_MCUBOUNDINTST		BIT(24)
#घोषणा	ERRCONFIG_MCUDISACKINTEN	BIT(23)
#घोषणा ERRCONFIG_VPBOUNDINTST_V2	BIT(23)
#घोषणा ERRCONFIG_MCUDISACKINTST	BIT(22)
#घोषणा ERRCONFIG_VPBOUNDINTEN_V2	BIT(22)

#घोषणा ERRCONFIG_STATUS_V1_MASK	(ERRCONFIG_VPBOUNDINTST_V1 | \
					ERRCONFIG_MCUACCUMINTST | \
					ERRCONFIG_MCUVALIDINTST | \
					ERRCONFIG_MCUBOUNDINTST | \
					ERRCONFIG_MCUDISACKINTST)
/* IRQSTATUS */
#घोषणा IRQSTATUS_MCUACCUMINT		BIT(3)
#घोषणा IRQSTATUS_MCVALIDINT		BIT(2)
#घोषणा IRQSTATUS_MCBOUNDSINT		BIT(1)
#घोषणा IRQSTATUS_MCUDISABLEACKINT	BIT(0)

/* IRQENABLE_SET and IRQENABLE_CLEAR */
#घोषणा IRQENABLE_MCUACCUMINT		BIT(3)
#घोषणा IRQENABLE_MCUVALIDINT		BIT(2)
#घोषणा IRQENABLE_MCUBOUNDSINT		BIT(1)
#घोषणा IRQENABLE_MCUDISABLEACKINT	BIT(0)

/* Common Bit values */

#घोषणा SRCLKLENGTH_12MHZ_SYSCLK	0x3c
#घोषणा SRCLKLENGTH_13MHZ_SYSCLK	0x41
#घोषणा SRCLKLENGTH_19MHZ_SYSCLK	0x60
#घोषणा SRCLKLENGTH_26MHZ_SYSCLK	0x82
#घोषणा SRCLKLENGTH_38MHZ_SYSCLK	0xC0

/*
 * 3430 specअगरic values. Maybe these should be passed from board file or
 * pmic काष्ठाures.
 */
#घोषणा OMAP3430_SR_ACCUMDATA		0x1f4

#घोषणा OMAP3430_SR1_SENPAVGWEIGHT	0x03
#घोषणा OMAP3430_SR1_SENNAVGWEIGHT	0x03

#घोषणा OMAP3430_SR2_SENPAVGWEIGHT	0x01
#घोषणा OMAP3430_SR2_SENNAVGWEIGHT	0x01

#घोषणा OMAP3430_SR_ERRWEIGHT		0x04
#घोषणा OMAP3430_SR_ERRMAXLIMIT		0x02

क्रमागत sr_instance अणु
	OMAP_SR_MPU,			/* shared with iva on omap3 */
	OMAP_SR_CORE,
	OMAP_SR_IVA,
	OMAP_SR_NR,
पूर्ण;

काष्ठा omap_sr अणु
	अक्षर				*name;
	काष्ठा list_head		node;
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा omap_sr_nvalue_table	*nvalue_table;
	काष्ठा voltageकरोमुख्य		*voltdm;
	काष्ठा dentry			*dbg_dir;
	अचिन्हित पूर्णांक			irq;
	पूर्णांक				srid;
	पूर्णांक				ip_type;
	पूर्णांक				nvalue_count;
	bool				स्वतःcomp_active;
	u32				clk_length;
	u32				err_weight;
	u32				err_minlimit;
	u32				err_maxlimit;
	u32				accum_data;
	u32				senn_avgweight;
	u32				senp_avgweight;
	u32				senp_mod;
	u32				senn_mod;
	व्योम __iomem			*base;
पूर्ण;

/**
 * test_cond_समयout - busy-loop, testing a condition
 * @cond: condition to test until it evaluates to true
 * @समयout: maximum number of microseconds in the समयout
 * @index: loop index (पूर्णांकeger)
 *
 * Loop रुकोing क्रम @cond to become true or until at least @समयout
 * microseconds have passed.  To use, define some पूर्णांकeger @index in the
 * calling code.  After running, अगर @index == @समयout, then the loop has
 * समयd out.
 *
 * Copied from omap_test_समयout */
#घोषणा sr_test_cond_समयout(cond, समयout, index)		\
(अणु								\
	क्रम (index = 0; index < समयout; index++) अणु		\
		अगर (cond)					\
			अवरोध;					\
		udelay(1);					\
	पूर्ण							\
पूर्ण)

/**
 * काष्ठा omap_sr_pmic_data - Strucutre to be populated by pmic code to pass
 *				pmic specअगरic info to smartreflex driver
 *
 * @sr_pmic_init:	API to initialize smartreflex on the PMIC side.
 */
काष्ठा omap_sr_pmic_data अणु
	व्योम (*sr_pmic_init) (व्योम);
पूर्ण;

/**
 * काष्ठा omap_smartreflex_dev_attr - Smartreflex Device attribute.
 *
 * @sensor_voltdm_name:       Name of voltकरोमुख्य of SR instance
 */
काष्ठा omap_smartreflex_dev_attr अणु
	स्थिर अक्षर      *sensor_voltdm_name;
पूर्ण;

/*
 * The smart reflex driver supports CLASS1 CLASS2 and CLASS3 SR.
 * The smartreflex class driver should pass the class type.
 * Should be used to populate the class_type field of the
 * omap_smartreflex_class_data काष्ठाure.
 */
#घोषणा SR_CLASS1	0x1
#घोषणा SR_CLASS2	0x2
#घोषणा SR_CLASS3	0x3

/**
 * काष्ठा omap_sr_class_data - Smartreflex class driver info
 *
 * @enable:		API to enable a particular class smaartreflex.
 * @disable:		API to disable a particular class smartreflex.
 * @configure:		API to configure a particular class smartreflex.
 * @notअगरy:		API to notअगरy the class driver about an event in SR.
 *			Not needed क्रम class3.
 * @notअगरy_flags:	specअगरy the events to be notअगरied to the class driver
 * @class_type:		specअगरy which smartreflex class.
 *			Can be used by the SR driver to take any class
 *			based decisions.
 */
काष्ठा omap_sr_class_data अणु
	पूर्णांक (*enable)(काष्ठा omap_sr *sr);
	पूर्णांक (*disable)(काष्ठा omap_sr *sr, पूर्णांक is_volt_reset);
	पूर्णांक (*configure)(काष्ठा omap_sr *sr);
	पूर्णांक (*notअगरy)(काष्ठा omap_sr *sr, u32 status);
	u8 notअगरy_flags;
	u8 class_type;
पूर्ण;

/**
 * काष्ठा omap_sr_nvalue_table	- Smartreflex n-target value info
 *
 * @efuse_offs:	  The offset of the efuse where n-target values are stored.
 * @nvalue:	  The n-target value.
 * @errminlimit:  The value of the ERRMINLIMIT bitfield क्रम this n-target
 * @volt_nominal: microvolts DC that the VDD is initially programmed to
 */
काष्ठा omap_sr_nvalue_table अणु
	u32 efuse_offs;
	u32 nvalue;
	u32 errminlimit;
	अचिन्हित दीर्घ volt_nominal;
पूर्ण;

/**
 * काष्ठा omap_sr_data - Smartreflex platक्रमm data.
 *
 * @name:		instance name
 * @ip_type:		Smartreflex IP type.
 * @senp_mod:		SENPENABLE value of the sr CONFIG रेजिस्टर
 * @senn_mod:		SENNENABLE value क्रम sr CONFIG रेजिस्टर
 * @err_weight		ERRWEIGHT value of the sr ERRCONFIG रेजिस्टर
 * @err_maxlimit	ERRMAXLIMIT value of the sr ERRCONFIG रेजिस्टर
 * @accum_data		ACCUMDATA value of the sr CONFIG रेजिस्टर
 * @senn_avgweight	SENNAVGWEIGHT value of the sr AVGWEIGHT रेजिस्टर
 * @senp_avgweight	SENPAVGWEIGHT value of the sr AVGWEIGHT रेजिस्टर
 * @nvalue_count:	Number of distinct nvalues in the nvalue table
 * @enable_on_init:	whether this sr module needs to enabled at
 *			boot up or not.
 * @nvalue_table:	table containing the  efuse offsets and nvalues
 *			corresponding to them.
 * @voltdm:		Poपूर्णांकer to the voltage करोमुख्य associated with the SR
 */
काष्ठा omap_sr_data अणु
	स्थिर अक्षर			*name;
	पूर्णांक				ip_type;
	u32				senp_mod;
	u32				senn_mod;
	u32				err_weight;
	u32				err_maxlimit;
	u32				accum_data;
	u32				senn_avgweight;
	u32				senp_avgweight;
	पूर्णांक				nvalue_count;
	bool				enable_on_init;
	काष्ठा omap_sr_nvalue_table	*nvalue_table;
	काष्ठा voltageकरोमुख्य		*voltdm;
पूर्ण;


बाह्य काष्ठा omap_sr_data omap_sr_pdata[OMAP_SR_NR];

#अगर_घोषित CONFIG_POWER_AVS_OMAP

/* Smartreflex module enable/disable पूर्णांकerface */
व्योम omap_sr_enable(काष्ठा voltageकरोमुख्य *voltdm);
व्योम omap_sr_disable(काष्ठा voltageकरोमुख्य *voltdm);
व्योम omap_sr_disable_reset_volt(काष्ठा voltageकरोमुख्य *voltdm);

/* Smartreflex driver hooks to be called from Smartreflex class driver */
पूर्णांक sr_enable(काष्ठा omap_sr *sr, अचिन्हित दीर्घ volt);
व्योम sr_disable(काष्ठा omap_sr *sr);
पूर्णांक sr_configure_errgen(काष्ठा omap_sr *sr);
पूर्णांक sr_disable_errgen(काष्ठा omap_sr *sr);
पूर्णांक sr_configure_minmax(काष्ठा omap_sr *sr);

/* API to रेजिस्टर the smartreflex class driver with the smartreflex driver */
पूर्णांक sr_रेजिस्टर_class(काष्ठा omap_sr_class_data *class_data);
#अन्यथा
अटल अंतरभूत व्योम omap_sr_enable(काष्ठा voltageकरोमुख्य *voltdm) अणुपूर्ण
अटल अंतरभूत व्योम omap_sr_disable(काष्ठा voltageकरोमुख्य *voltdm) अणुपूर्ण
अटल अंतरभूत व्योम omap_sr_disable_reset_volt(
		काष्ठा voltageकरोमुख्य *voltdm) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
