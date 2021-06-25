<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MFD driver क्रम twl6040
 *
 * Authors:     Jorge Eduarकरो Candelaria <jorge.candelaria@ti.com>
 *              Misael Lopez Cruz <misael.lopez@ti.com>
 *
 * Copyright:   (C) 2011 Texas Instruments, Inc.
 */

#अगर_अघोषित __TWL6040_CODEC_H__
#घोषणा __TWL6040_CODEC_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/clk.h>

#घोषणा TWL6040_REG_ASICID		0x01
#घोषणा TWL6040_REG_ASICREV		0x02
#घोषणा TWL6040_REG_INTID		0x03
#घोषणा TWL6040_REG_INTMR		0x04
#घोषणा TWL6040_REG_NCPCTL		0x05
#घोषणा TWL6040_REG_LDOCTL		0x06
#घोषणा TWL6040_REG_HPPLLCTL		0x07
#घोषणा TWL6040_REG_LPPLLCTL		0x08
#घोषणा TWL6040_REG_LPPLLDIV		0x09
#घोषणा TWL6040_REG_AMICBCTL		0x0A
#घोषणा TWL6040_REG_DMICBCTL		0x0B
#घोषणा TWL6040_REG_MICLCTL		0x0C
#घोषणा TWL6040_REG_MICRCTL		0x0D
#घोषणा TWL6040_REG_MICGAIN		0x0E
#घोषणा TWL6040_REG_LINEGAIN		0x0F
#घोषणा TWL6040_REG_HSLCTL		0x10
#घोषणा TWL6040_REG_HSRCTL		0x11
#घोषणा TWL6040_REG_HSGAIN		0x12
#घोषणा TWL6040_REG_EARCTL		0x13
#घोषणा TWL6040_REG_HFLCTL		0x14
#घोषणा TWL6040_REG_HFLGAIN		0x15
#घोषणा TWL6040_REG_HFRCTL		0x16
#घोषणा TWL6040_REG_HFRGAIN		0x17
#घोषणा TWL6040_REG_VIBCTLL		0x18
#घोषणा TWL6040_REG_VIBDATL		0x19
#घोषणा TWL6040_REG_VIBCTLR		0x1A
#घोषणा TWL6040_REG_VIBDATR		0x1B
#घोषणा TWL6040_REG_HKCTL1		0x1C
#घोषणा TWL6040_REG_HKCTL2		0x1D
#घोषणा TWL6040_REG_GPOCTL		0x1E
#घोषणा TWL6040_REG_ALB			0x1F
#घोषणा TWL6040_REG_DLB			0x20
#घोषणा TWL6040_REG_TRIM1		0x28
#घोषणा TWL6040_REG_TRIM2		0x29
#घोषणा TWL6040_REG_TRIM3		0x2A
#घोषणा TWL6040_REG_HSOTRIM		0x2B
#घोषणा TWL6040_REG_HFOTRIM		0x2C
#घोषणा TWL6040_REG_ACCCTL		0x2D
#घोषणा TWL6040_REG_STATUS		0x2E

/* INTID (0x03) fields */

#घोषणा TWL6040_THINT			0x01
#घोषणा TWL6040_PLUGINT			0x02
#घोषणा TWL6040_UNPLUGINT		0x04
#घोषणा TWL6040_HOOKINT			0x08
#घोषणा TWL6040_HFINT			0x10
#घोषणा TWL6040_VIBINT			0x20
#घोषणा TWL6040_READYINT		0x40

/* INTMR (0x04) fields */

#घोषणा TWL6040_THMSK			0x01
#घोषणा TWL6040_PLUGMSK			0x02
#घोषणा TWL6040_HOOKMSK			0x08
#घोषणा TWL6040_HFMSK			0x10
#घोषणा TWL6040_VIBMSK			0x20
#घोषणा TWL6040_READYMSK		0x40
#घोषणा TWL6040_ALLINT_MSK		0x7B

/* NCPCTL (0x05) fields */

#घोषणा TWL6040_NCPENA			0x01
#घोषणा TWL6040_NCPOPEN			0x40

/* LDOCTL (0x06) fields */

#घोषणा TWL6040_LSLDOENA		0x01
#घोषणा TWL6040_HSLDOENA		0x04
#घोषणा TWL6040_REFENA			0x40
#घोषणा TWL6040_OSCENA			0x80

/* HPPLLCTL (0x07) fields */

#घोषणा TWL6040_HPLLENA			0x01
#घोषणा TWL6040_HPLLRST			0x02
#घोषणा TWL6040_HPLLBP			0x04
#घोषणा TWL6040_HPLLSQRENA		0x08
#घोषणा TWL6040_MCLK_12000KHZ		(0 << 5)
#घोषणा TWL6040_MCLK_19200KHZ		(1 << 5)
#घोषणा TWL6040_MCLK_26000KHZ		(2 << 5)
#घोषणा TWL6040_MCLK_38400KHZ		(3 << 5)
#घोषणा TWL6040_MCLK_MSK		0x60

/* LPPLLCTL (0x08) fields */

#घोषणा TWL6040_LPLLENA			0x01
#घोषणा TWL6040_LPLLRST			0x02
#घोषणा TWL6040_LPLLSEL			0x04
#घोषणा TWL6040_LPLLFIN			0x08
#घोषणा TWL6040_HPLLSEL			0x10

/* HSLCTL/R (0x10/0x11) fields */

#घोषणा TWL6040_HSDACENA		(1 << 0)
#घोषणा TWL6040_HSDACMODE		(1 << 1)
#घोषणा TWL6040_HSDRVENA		(1 << 2)
#घोषणा TWL6040_HSDRVMODE		(1 << 3)

/* HFLCTL/R (0x14/0x16) fields */

#घोषणा TWL6040_HFDACENA		(1 << 0)
#घोषणा TWL6040_HFPGAENA		(1 << 1)
#घोषणा TWL6040_HFDRVENA		(1 << 4)
#घोषणा TWL6040_HFSWENA			(1 << 6)

/* VIBCTLL/R (0x18/0x1A) fields */

#घोषणा TWL6040_VIBENA			(1 << 0)
#घोषणा TWL6040_VIBSEL			(1 << 1)
#घोषणा TWL6040_VIBCTRL			(1 << 2)
#घोषणा TWL6040_VIBCTRL_P		(1 << 3)
#घोषणा TWL6040_VIBCTRL_N		(1 << 4)

/* VIBDATL/R (0x19/0x1B) fields */

#घोषणा TWL6040_VIBDAT_MAX		0x64

/* GPOCTL (0x1E) fields */

#घोषणा TWL6040_GPO1			0x01
#घोषणा TWL6040_GPO2			0x02
#घोषणा TWL6040_GPO3			0x04

/* ACCCTL (0x2D) fields */

#घोषणा TWL6040_I2CSEL			0x01
#घोषणा TWL6040_RESETSPLIT		0x04
#घोषणा TWL6040_INTCLRMODE		0x08
#घोषणा TWL6040_I2CMODE(x)		((x & 0x3) << 4)

/* STATUS (0x2E) fields */

#घोषणा TWL6040_PLUGCOMP		0x02
#घोषणा TWL6040_VIBLOCDET		0x10
#घोषणा TWL6040_VIBROCDET		0x20
#घोषणा TWL6040_TSHUTDET                0x40

#घोषणा TWL6040_CELLS			4

#घोषणा TWL6040_REV_ES1_0		0x00
#घोषणा TWL6040_REV_ES1_1		0x01 /* Rev ES1.1 and ES1.2 */
#घोषणा TWL6040_REV_ES1_3		0x02
#घोषणा TWL6041_REV_ES2_0		0x10

#घोषणा TWL6040_IRQ_TH			0
#घोषणा TWL6040_IRQ_PLUG		1
#घोषणा TWL6040_IRQ_HOOK		2
#घोषणा TWL6040_IRQ_HF			3
#घोषणा TWL6040_IRQ_VIB			4
#घोषणा TWL6040_IRQ_READY		5

/* PLL selection */
#घोषणा TWL6040_SYSCLK_SEL_LPPLL	0
#घोषणा TWL6040_SYSCLK_SEL_HPPLL	1

#घोषणा TWL6040_GPO_MAX	3

/* TODO: All platक्रमm data काष्ठा can be हटाओd */
काष्ठा twl6040_codec_data अणु
	u16 hs_left_step;
	u16 hs_right_step;
	u16 hf_left_step;
	u16 hf_right_step;
पूर्ण;

काष्ठा twl6040_vibra_data अणु
	अचिन्हित पूर्णांक vibldrv_res;	/* left driver resistance */
	अचिन्हित पूर्णांक vibrdrv_res;	/* right driver resistance */
	अचिन्हित पूर्णांक viblmotor_res;	/* left motor resistance */
	अचिन्हित पूर्णांक vibrmotor_res;	/* right motor resistance */
	पूर्णांक vddvibl_uV;			/* VDDVIBL volt, set 0 क्रम fixed reg */
	पूर्णांक vddvibr_uV;			/* VDDVIBR volt, set 0 क्रम fixed reg */
पूर्ण;

काष्ठा twl6040_gpo_data अणु
	पूर्णांक gpio_base;
पूर्ण;

काष्ठा twl6040_platक्रमm_data अणु
	पूर्णांक audpwron_gpio;	/* audio घातer-on gpio */

	काष्ठा twl6040_codec_data *codec;
	काष्ठा twl6040_vibra_data *vibra;
	काष्ठा twl6040_gpo_data *gpo;
पूर्ण;

काष्ठा regmap;
काष्ठा regmap_irq_chips_data;

काष्ठा twl6040 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *irq_data;
	काष्ठा regulator_bulk_data supplies[2]; /* supplies क्रम vio, v2v1 */
	काष्ठा clk *clk32k;
	काष्ठा clk *mclk;
	काष्ठा mutex mutex;
	काष्ठा mutex irq_mutex;
	काष्ठा mfd_cell cells[TWL6040_CELLS];
	काष्ठा completion पढ़ोy;

	पूर्णांक audpwron;
	पूर्णांक घातer_count;
	पूर्णांक rev;

	/* PLL configuration */
	पूर्णांक pll;
	अचिन्हित पूर्णांक sysclk_rate;
	अचिन्हित पूर्णांक mclk_rate;

	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक irq_पढ़ोy;
	अचिन्हित पूर्णांक irq_th;
पूर्ण;

पूर्णांक twl6040_reg_पढ़ो(काष्ठा twl6040 *twl6040, अचिन्हित पूर्णांक reg);
पूर्णांक twl6040_reg_ग_लिखो(काष्ठा twl6040 *twl6040, अचिन्हित पूर्णांक reg,
		      u8 val);
पूर्णांक twl6040_set_bits(काष्ठा twl6040 *twl6040, अचिन्हित पूर्णांक reg,
		     u8 mask);
पूर्णांक twl6040_clear_bits(काष्ठा twl6040 *twl6040, अचिन्हित पूर्णांक reg,
		       u8 mask);
पूर्णांक twl6040_घातer(काष्ठा twl6040 *twl6040, पूर्णांक on);
पूर्णांक twl6040_set_pll(काष्ठा twl6040 *twl6040, पूर्णांक pll_id,
		    अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out);
पूर्णांक twl6040_get_pll(काष्ठा twl6040 *twl6040);
अचिन्हित पूर्णांक twl6040_get_sysclk(काष्ठा twl6040 *twl6040);

/* Get the combined status of the vibra control रेजिस्टर */
पूर्णांक twl6040_get_vibralr_status(काष्ठा twl6040 *twl6040);

अटल अंतरभूत पूर्णांक twl6040_get_revid(काष्ठा twl6040 *twl6040)
अणु
	वापस twl6040->rev;
पूर्ण


#पूर्ण_अगर  /* End of __TWL6040_CODEC_H__ */
