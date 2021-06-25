<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TI OMAP I2C master mode driver
 *
 * Copyright (C) 2003 MontaVista Software, Inc.
 * Copyright (C) 2005 Nokia Corporation
 * Copyright (C) 2004 - 2007 Texas Instruments.
 *
 * Originally written by MontaVista Software, Inc.
 * Additional contributions by:
 *	Tony Lindgren <tony@atomide.com>
 *	Imre Deak <imre.deak@nokia.com>
 *	Juha Yrjथघlथअ <juha.yrjola@solidboot.com>
 *	Syed Khasim <x0khasim@ti.com>
 *	Nishant Menon <nm@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/i2c-omap.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pinctrl/consumer.h>

/* I2C controller revisions */
#घोषणा OMAP_I2C_OMAP1_REV_2		0x20

/* I2C controller revisions present on specअगरic hardware */
#घोषणा OMAP_I2C_REV_ON_2430		0x00000036
#घोषणा OMAP_I2C_REV_ON_3430_3530	0x0000003C
#घोषणा OMAP_I2C_REV_ON_3630		0x00000040
#घोषणा OMAP_I2C_REV_ON_4430_PLUS	0x50400002

/* समयout रुकोing क्रम the controller to respond */
#घोषणा OMAP_I2C_TIMEOUT (msecs_to_jअगरfies(1000))

/* समयout क्रम pm runसमय स्वतःsuspend */
#घोषणा OMAP_I2C_PM_TIMEOUT		1000	/* ms */

/* समयout क्रम making decision on bus मुक्त status */
#घोषणा OMAP_I2C_BUS_FREE_TIMEOUT (msecs_to_jअगरfies(10))

/* For OMAP3 I2C_IV has changed to I2C_WE (wakeup enable) */
क्रमागत अणु
	OMAP_I2C_REV_REG = 0,
	OMAP_I2C_IE_REG,
	OMAP_I2C_STAT_REG,
	OMAP_I2C_IV_REG,
	OMAP_I2C_WE_REG,
	OMAP_I2C_SYSS_REG,
	OMAP_I2C_BUF_REG,
	OMAP_I2C_CNT_REG,
	OMAP_I2C_DATA_REG,
	OMAP_I2C_SYSC_REG,
	OMAP_I2C_CON_REG,
	OMAP_I2C_OA_REG,
	OMAP_I2C_SA_REG,
	OMAP_I2C_PSC_REG,
	OMAP_I2C_SCLL_REG,
	OMAP_I2C_SCLH_REG,
	OMAP_I2C_SYSTEST_REG,
	OMAP_I2C_BUFSTAT_REG,
	/* only on OMAP4430 */
	OMAP_I2C_IP_V2_REVNB_LO,
	OMAP_I2C_IP_V2_REVNB_HI,
	OMAP_I2C_IP_V2_IRQSTATUS_RAW,
	OMAP_I2C_IP_V2_IRQENABLE_SET,
	OMAP_I2C_IP_V2_IRQENABLE_CLR,
पूर्ण;

/* I2C Interrupt Enable Register (OMAP_I2C_IE): */
#घोषणा OMAP_I2C_IE_XDR		(1 << 14)	/* TX Buffer drain पूर्णांक enable */
#घोषणा OMAP_I2C_IE_RDR		(1 << 13)	/* RX Buffer drain पूर्णांक enable */
#घोषणा OMAP_I2C_IE_XRDY	(1 << 4)	/* TX data पढ़ोy पूर्णांक enable */
#घोषणा OMAP_I2C_IE_RRDY	(1 << 3)	/* RX data पढ़ोy पूर्णांक enable */
#घोषणा OMAP_I2C_IE_ARDY	(1 << 2)	/* Access पढ़ोy पूर्णांक enable */
#घोषणा OMAP_I2C_IE_NACK	(1 << 1)	/* No ack पूर्णांकerrupt enable */
#घोषणा OMAP_I2C_IE_AL		(1 << 0)	/* Arbitration lost पूर्णांक ena */

/* I2C Status Register (OMAP_I2C_STAT): */
#घोषणा OMAP_I2C_STAT_XDR	(1 << 14)	/* TX Buffer draining */
#घोषणा OMAP_I2C_STAT_RDR	(1 << 13)	/* RX Buffer draining */
#घोषणा OMAP_I2C_STAT_BB	(1 << 12)	/* Bus busy */
#घोषणा OMAP_I2C_STAT_ROVR	(1 << 11)	/* Receive overrun */
#घोषणा OMAP_I2C_STAT_XUDF	(1 << 10)	/* Transmit underflow */
#घोषणा OMAP_I2C_STAT_AAS	(1 << 9)	/* Address as slave */
#घोषणा OMAP_I2C_STAT_BF	(1 << 8)	/* Bus Free */
#घोषणा OMAP_I2C_STAT_XRDY	(1 << 4)	/* Transmit data पढ़ोy */
#घोषणा OMAP_I2C_STAT_RRDY	(1 << 3)	/* Receive data पढ़ोy */
#घोषणा OMAP_I2C_STAT_ARDY	(1 << 2)	/* Register access पढ़ोy */
#घोषणा OMAP_I2C_STAT_NACK	(1 << 1)	/* No ack पूर्णांकerrupt enable */
#घोषणा OMAP_I2C_STAT_AL	(1 << 0)	/* Arbitration lost पूर्णांक ena */

/* I2C WE wakeup enable रेजिस्टर */
#घोषणा OMAP_I2C_WE_XDR_WE	(1 << 14)	/* TX drain wakup */
#घोषणा OMAP_I2C_WE_RDR_WE	(1 << 13)	/* RX drain wakeup */
#घोषणा OMAP_I2C_WE_AAS_WE	(1 << 9)	/* Address as slave wakeup*/
#घोषणा OMAP_I2C_WE_BF_WE	(1 << 8)	/* Bus मुक्त wakeup */
#घोषणा OMAP_I2C_WE_STC_WE	(1 << 6)	/* Start condition wakeup */
#घोषणा OMAP_I2C_WE_GC_WE	(1 << 5)	/* General call wakeup */
#घोषणा OMAP_I2C_WE_DRDY_WE	(1 << 3)	/* TX/RX data पढ़ोy wakeup */
#घोषणा OMAP_I2C_WE_ARDY_WE	(1 << 2)	/* Reg access पढ़ोy wakeup */
#घोषणा OMAP_I2C_WE_NACK_WE	(1 << 1)	/* No acknowledgment wakeup */
#घोषणा OMAP_I2C_WE_AL_WE	(1 << 0)	/* Arbitration lost wakeup */

#घोषणा OMAP_I2C_WE_ALL		(OMAP_I2C_WE_XDR_WE | OMAP_I2C_WE_RDR_WE | \
				OMAP_I2C_WE_AAS_WE | OMAP_I2C_WE_BF_WE | \
				OMAP_I2C_WE_STC_WE | OMAP_I2C_WE_GC_WE | \
				OMAP_I2C_WE_DRDY_WE | OMAP_I2C_WE_ARDY_WE | \
				OMAP_I2C_WE_NACK_WE | OMAP_I2C_WE_AL_WE)

/* I2C Buffer Configuration Register (OMAP_I2C_BUF): */
#घोषणा OMAP_I2C_BUF_RDMA_EN	(1 << 15)	/* RX DMA channel enable */
#घोषणा OMAP_I2C_BUF_RXFIF_CLR	(1 << 14)	/* RX FIFO Clear */
#घोषणा OMAP_I2C_BUF_XDMA_EN	(1 << 7)	/* TX DMA channel enable */
#घोषणा OMAP_I2C_BUF_TXFIF_CLR	(1 << 6)	/* TX FIFO Clear */

/* I2C Configuration Register (OMAP_I2C_CON): */
#घोषणा OMAP_I2C_CON_EN		(1 << 15)	/* I2C module enable */
#घोषणा OMAP_I2C_CON_BE		(1 << 14)	/* Big endian mode */
#घोषणा OMAP_I2C_CON_OPMODE_HS	(1 << 12)	/* High Speed support */
#घोषणा OMAP_I2C_CON_STB	(1 << 11)	/* Start byte mode (master) */
#घोषणा OMAP_I2C_CON_MST	(1 << 10)	/* Master/slave mode */
#घोषणा OMAP_I2C_CON_TRX	(1 << 9)	/* TX/RX mode (master only) */
#घोषणा OMAP_I2C_CON_XA		(1 << 8)	/* Expand address */
#घोषणा OMAP_I2C_CON_RM		(1 << 2)	/* Repeat mode (master only) */
#घोषणा OMAP_I2C_CON_STP	(1 << 1)	/* Stop cond (master only) */
#घोषणा OMAP_I2C_CON_STT	(1 << 0)	/* Start condition (master) */

/* I2C SCL समय value when Master */
#घोषणा OMAP_I2C_SCLL_HSSCLL	8
#घोषणा OMAP_I2C_SCLH_HSSCLH	8

/* I2C System Test Register (OMAP_I2C_SYSTEST): */
#घोषणा OMAP_I2C_SYSTEST_ST_EN		(1 << 15)	/* System test enable */
#घोषणा OMAP_I2C_SYSTEST_FREE		(1 << 14)	/* Free running mode */
#घोषणा OMAP_I2C_SYSTEST_TMODE_MASK	(3 << 12)	/* Test mode select */
#घोषणा OMAP_I2C_SYSTEST_TMODE_SHIFT	(12)		/* Test mode select */
/* Functional mode */
#घोषणा OMAP_I2C_SYSTEST_SCL_I_FUNC	(1 << 8)	/* SCL line input value */
#घोषणा OMAP_I2C_SYSTEST_SCL_O_FUNC	(1 << 7)	/* SCL line output value */
#घोषणा OMAP_I2C_SYSTEST_SDA_I_FUNC	(1 << 6)	/* SDA line input value */
#घोषणा OMAP_I2C_SYSTEST_SDA_O_FUNC	(1 << 5)	/* SDA line output value */
/* SDA/SCL IO mode */
#घोषणा OMAP_I2C_SYSTEST_SCL_I		(1 << 3)	/* SCL line sense in */
#घोषणा OMAP_I2C_SYSTEST_SCL_O		(1 << 2)	/* SCL line drive out */
#घोषणा OMAP_I2C_SYSTEST_SDA_I		(1 << 1)	/* SDA line sense in */
#घोषणा OMAP_I2C_SYSTEST_SDA_O		(1 << 0)	/* SDA line drive out */

/* OCP_SYSSTATUS bit definitions */
#घोषणा SYSS_RESETDONE_MASK		(1 << 0)

/* OCP_SYSCONFIG bit definitions */
#घोषणा SYSC_CLOCKACTIVITY_MASK		(0x3 << 8)
#घोषणा SYSC_SIDLEMODE_MASK		(0x3 << 3)
#घोषणा SYSC_ENAWAKEUP_MASK		(1 << 2)
#घोषणा SYSC_SOFTRESET_MASK		(1 << 1)
#घोषणा SYSC_AUTOIDLE_MASK		(1 << 0)

#घोषणा SYSC_IDLEMODE_SMART		0x2
#घोषणा SYSC_CLOCKACTIVITY_FCLK		0x2

/* Errata definitions */
#घोषणा I2C_OMAP_ERRATA_I207		(1 << 0)
#घोषणा I2C_OMAP_ERRATA_I462		(1 << 1)

#घोषणा OMAP_I2C_IP_V2_INTERRUPTS_MASK	0x6FFF

काष्ठा omap_i2c_dev अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;		/* भव */
	पूर्णांक			irq;
	पूर्णांक			reg_shअगरt;      /* bit shअगरt क्रम I2C रेजिस्टर addresses */
	काष्ठा completion	cmd_complete;
	काष्ठा resource		*ioarea;
	u32			latency;	/* maximum mpu wkup latency */
	व्योम			(*set_mpu_wkup_lat)(काष्ठा device *dev,
						    दीर्घ latency);
	u32			speed;		/* Speed of bus in kHz */
	u32			flags;
	u16			scheme;
	u16			cmd_err;
	u8			*buf;
	u8			*regs;
	माप_प्रकार			buf_len;
	काष्ठा i2c_adapter	adapter;
	u8			threshold;
	u8			fअगरo_size;	/* use as flag and value
						 * fअगरo_size==0 implies no fअगरo
						 * अगर set, should be trsh+1
						 */
	u32			rev;
	अचिन्हित		b_hw:1;		/* bad h/w fixes */
	अचिन्हित		bb_valid:1;	/* true when BB-bit reflects
						 * the I2C bus state
						 */
	अचिन्हित		receiver:1;	/* true when we're in receiver mode */
	u16			iestate;	/* Saved पूर्णांकerrupt रेजिस्टर */
	u16			pscstate;
	u16			scllstate;
	u16			sclhstate;
	u16			syscstate;
	u16			westate;
	u16			errata;
पूर्ण;

अटल स्थिर u8 reg_map_ip_v1[] = अणु
	[OMAP_I2C_REV_REG] = 0x00,
	[OMAP_I2C_IE_REG] = 0x01,
	[OMAP_I2C_STAT_REG] = 0x02,
	[OMAP_I2C_IV_REG] = 0x03,
	[OMAP_I2C_WE_REG] = 0x03,
	[OMAP_I2C_SYSS_REG] = 0x04,
	[OMAP_I2C_BUF_REG] = 0x05,
	[OMAP_I2C_CNT_REG] = 0x06,
	[OMAP_I2C_DATA_REG] = 0x07,
	[OMAP_I2C_SYSC_REG] = 0x08,
	[OMAP_I2C_CON_REG] = 0x09,
	[OMAP_I2C_OA_REG] = 0x0a,
	[OMAP_I2C_SA_REG] = 0x0b,
	[OMAP_I2C_PSC_REG] = 0x0c,
	[OMAP_I2C_SCLL_REG] = 0x0d,
	[OMAP_I2C_SCLH_REG] = 0x0e,
	[OMAP_I2C_SYSTEST_REG] = 0x0f,
	[OMAP_I2C_BUFSTAT_REG] = 0x10,
पूर्ण;

अटल स्थिर u8 reg_map_ip_v2[] = अणु
	[OMAP_I2C_REV_REG] = 0x04,
	[OMAP_I2C_IE_REG] = 0x2c,
	[OMAP_I2C_STAT_REG] = 0x28,
	[OMAP_I2C_IV_REG] = 0x34,
	[OMAP_I2C_WE_REG] = 0x34,
	[OMAP_I2C_SYSS_REG] = 0x90,
	[OMAP_I2C_BUF_REG] = 0x94,
	[OMAP_I2C_CNT_REG] = 0x98,
	[OMAP_I2C_DATA_REG] = 0x9c,
	[OMAP_I2C_SYSC_REG] = 0x10,
	[OMAP_I2C_CON_REG] = 0xa4,
	[OMAP_I2C_OA_REG] = 0xa8,
	[OMAP_I2C_SA_REG] = 0xac,
	[OMAP_I2C_PSC_REG] = 0xb0,
	[OMAP_I2C_SCLL_REG] = 0xb4,
	[OMAP_I2C_SCLH_REG] = 0xb8,
	[OMAP_I2C_SYSTEST_REG] = 0xbC,
	[OMAP_I2C_BUFSTAT_REG] = 0xc0,
	[OMAP_I2C_IP_V2_REVNB_LO] = 0x00,
	[OMAP_I2C_IP_V2_REVNB_HI] = 0x04,
	[OMAP_I2C_IP_V2_IRQSTATUS_RAW] = 0x24,
	[OMAP_I2C_IP_V2_IRQENABLE_SET] = 0x2c,
	[OMAP_I2C_IP_V2_IRQENABLE_CLR] = 0x30,
पूर्ण;

अटल पूर्णांक omap_i2c_xfer_data(काष्ठा omap_i2c_dev *omap);

अटल अंतरभूत व्योम omap_i2c_ग_लिखो_reg(काष्ठा omap_i2c_dev *omap,
				      पूर्णांक reg, u16 val)
अणु
	ग_लिखोw_relaxed(val, omap->base +
			(omap->regs[reg] << omap->reg_shअगरt));
पूर्ण

अटल अंतरभूत u16 omap_i2c_पढ़ो_reg(काष्ठा omap_i2c_dev *omap, पूर्णांक reg)
अणु
	वापस पढ़ोw_relaxed(omap->base +
				(omap->regs[reg] << omap->reg_shअगरt));
पूर्ण

अटल व्योम __omap_i2c_init(काष्ठा omap_i2c_dev *omap)
अणु

	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CON_REG, 0);

	/* Setup घड़ी prescaler to obtain approx 12MHz I2C module घड़ी: */
	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_PSC_REG, omap->pscstate);

	/* SCL low and high समय values */
	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_SCLL_REG, omap->scllstate);
	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_SCLH_REG, omap->sclhstate);
	अगर (omap->rev >= OMAP_I2C_REV_ON_3430_3530)
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_WE_REG, omap->westate);

	/* Take the I2C module out of reset: */
	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CON_REG, OMAP_I2C_CON_EN);

	/*
	 * NOTE: right after setting CON_EN, STAT_BB could be 0 जबतक the
	 * bus is busy. It will be changed to 1 on the next IP FCLK घड़ी.
	 * udelay(1) will be enough to fix that.
	 */

	/*
	 * Don't ग_लिखो to this रेजिस्टर अगर the IE state is 0 as it can
	 * cause deadlock.
	 */
	अगर (omap->iestate)
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_IE_REG, omap->iestate);
पूर्ण

अटल पूर्णांक omap_i2c_reset(काष्ठा omap_i2c_dev *omap)
अणु
	अचिन्हित दीर्घ समयout;
	u16 sysc;

	अगर (omap->rev >= OMAP_I2C_OMAP1_REV_2) अणु
		sysc = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_SYSC_REG);

		/* Disable I2C controller beक्रमe soft reset */
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CON_REG,
			omap_i2c_पढ़ो_reg(omap, OMAP_I2C_CON_REG) &
				~(OMAP_I2C_CON_EN));

		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_SYSC_REG, SYSC_SOFTRESET_MASK);
		/* For some reason we need to set the EN bit beक्रमe the
		 * reset करोne bit माला_लो set. */
		समयout = jअगरfies + OMAP_I2C_TIMEOUT;
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CON_REG, OMAP_I2C_CON_EN);
		जबतक (!(omap_i2c_पढ़ो_reg(omap, OMAP_I2C_SYSS_REG) &
			 SYSS_RESETDONE_MASK)) अणु
			अगर (समय_after(jअगरfies, समयout)) अणु
				dev_warn(omap->dev, "timeout waiting "
						"for controller reset\n");
				वापस -ETIMEDOUT;
			पूर्ण
			msleep(1);
		पूर्ण

		/* SYSC रेजिस्टर is cleared by the reset; reग_लिखो it */
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_SYSC_REG, sysc);

		अगर (omap->rev > OMAP_I2C_REV_ON_3430_3530) अणु
			/* Schedule I2C-bus monitoring on the next transfer */
			omap->bb_valid = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_i2c_init(काष्ठा omap_i2c_dev *omap)
अणु
	u16 psc = 0, scll = 0, sclh = 0;
	u16 fsscll = 0, fssclh = 0, hsscll = 0, hssclh = 0;
	अचिन्हित दीर्घ fclk_rate = 12000000;
	अचिन्हित दीर्घ पूर्णांकernal_clk = 0;
	काष्ठा clk *fclk;
	पूर्णांक error;

	अगर (omap->rev >= OMAP_I2C_REV_ON_3430_3530) अणु
		/*
		 * Enabling all wakup sources to stop I2C मुक्तzing on
		 * WFI inकाष्ठाion.
		 * REVISIT: Some wkup sources might not be needed.
		 */
		omap->westate = OMAP_I2C_WE_ALL;
	पूर्ण

	अगर (omap->flags & OMAP_I2C_FLAG_ALWAYS_ARMXOR_CLK) अणु
		/*
		 * The I2C functional घड़ी is the armxor_ck, so there's
		 * no need to get "armxor_ck" separately.  Now, अगर OMAP2420
		 * always वापसs 12MHz क्रम the functional घड़ी, we can
		 * करो this bit unconditionally.
		 */
		fclk = clk_get(omap->dev, "fck");
		अगर (IS_ERR(fclk)) अणु
			error = PTR_ERR(fclk);
			dev_err(omap->dev, "could not get fck: %i\n", error);

			वापस error;
		पूर्ण

		fclk_rate = clk_get_rate(fclk);
		clk_put(fclk);

		/* TRM क्रम 5912 says the I2C घड़ी must be prescaled to be
		 * between 7 - 12 MHz. The XOR input घड़ी is typically
		 * 12, 13 or 19.2 MHz. So we should have code that produces:
		 *
		 * XOR MHz	Divider		Prescaler
		 * 12		1		0
		 * 13		2		1
		 * 19.2		2		1
		 */
		अगर (fclk_rate > 12000000)
			psc = fclk_rate / 12000000;
	पूर्ण

	अगर (!(omap->flags & OMAP_I2C_FLAG_SIMPLE_CLOCK)) अणु

		/*
		 * HSI2C controller पूर्णांकernal clk rate should be 19.2 Mhz क्रम
		 * HS and क्रम all modes on 2430. On 34xx we can use lower rate
		 * to get दीर्घer filter period क्रम better noise suppression.
		 * The filter is iclk (fclk क्रम HS) period.
		 */
		अगर (omap->speed > 400 ||
			       omap->flags & OMAP_I2C_FLAG_FORCE_19200_INT_CLK)
			पूर्णांकernal_clk = 19200;
		अन्यथा अगर (omap->speed > 100)
			पूर्णांकernal_clk = 9600;
		अन्यथा
			पूर्णांकernal_clk = 4000;
		fclk = clk_get(omap->dev, "fck");
		अगर (IS_ERR(fclk)) अणु
			error = PTR_ERR(fclk);
			dev_err(omap->dev, "could not get fck: %i\n", error);

			वापस error;
		पूर्ण
		fclk_rate = clk_get_rate(fclk) / 1000;
		clk_put(fclk);

		/* Compute prescaler भागisor */
		psc = fclk_rate / पूर्णांकernal_clk;
		psc = psc - 1;

		/* If configured क्रम High Speed */
		अगर (omap->speed > 400) अणु
			अचिन्हित दीर्घ scl;

			/* For first phase of HS mode */
			scl = पूर्णांकernal_clk / 400;
			fsscll = scl - (scl / 3) - 7;
			fssclh = (scl / 3) - 5;

			/* For second phase of HS mode */
			scl = fclk_rate / omap->speed;
			hsscll = scl - (scl / 3) - 7;
			hssclh = (scl / 3) - 5;
		पूर्ण अन्यथा अगर (omap->speed > 100) अणु
			अचिन्हित दीर्घ scl;

			/* Fast mode */
			scl = पूर्णांकernal_clk / omap->speed;
			fsscll = scl - (scl / 3) - 7;
			fssclh = (scl / 3) - 5;
		पूर्ण अन्यथा अणु
			/* Standard mode */
			fsscll = पूर्णांकernal_clk / (omap->speed * 2) - 7;
			fssclh = पूर्णांकernal_clk / (omap->speed * 2) - 5;
		पूर्ण
		scll = (hsscll << OMAP_I2C_SCLL_HSSCLL) | fsscll;
		sclh = (hssclh << OMAP_I2C_SCLH_HSSCLH) | fssclh;
	पूर्ण अन्यथा अणु
		/* Program desired operating rate */
		fclk_rate /= (psc + 1) * 1000;
		अगर (psc > 2)
			psc = 2;
		scll = fclk_rate / (omap->speed * 2) - 7 + psc;
		sclh = fclk_rate / (omap->speed * 2) - 7 + psc;
	पूर्ण

	omap->iestate = (OMAP_I2C_IE_XRDY | OMAP_I2C_IE_RRDY |
			OMAP_I2C_IE_ARDY | OMAP_I2C_IE_NACK |
			OMAP_I2C_IE_AL)  | ((omap->fअगरo_size) ?
				(OMAP_I2C_IE_RDR | OMAP_I2C_IE_XDR) : 0);

	omap->pscstate = psc;
	omap->scllstate = scll;
	omap->sclhstate = sclh;

	अगर (omap->rev <= OMAP_I2C_REV_ON_3430_3530) अणु
		/* Not implemented */
		omap->bb_valid = 1;
	पूर्ण

	__omap_i2c_init(omap);

	वापस 0;
पूर्ण

/*
 * Try bus recovery, but only अगर SDA is actually low.
 */
अटल पूर्णांक omap_i2c_recover_bus(काष्ठा omap_i2c_dev *omap)
अणु
	u16 systest;

	systest = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_SYSTEST_REG);
	अगर ((systest & OMAP_I2C_SYSTEST_SCL_I_FUNC) &&
	    (systest & OMAP_I2C_SYSTEST_SDA_I_FUNC))
		वापस 0; /* bus seems to alपढ़ोy be fine */
	अगर (!(systest & OMAP_I2C_SYSTEST_SCL_I_FUNC))
		वापस -EBUSY; /* recovery would not fix SCL */
	वापस i2c_recover_bus(&omap->adapter);
पूर्ण

/*
 * Waiting on Bus Busy
 */
अटल पूर्णांक omap_i2c_रुको_क्रम_bb(काष्ठा omap_i2c_dev *omap)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + OMAP_I2C_TIMEOUT;
	जबतक (omap_i2c_पढ़ो_reg(omap, OMAP_I2C_STAT_REG) & OMAP_I2C_STAT_BB) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस omap_i2c_recover_bus(omap);
		msleep(1);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Wait जबतक BB-bit करोesn't reflect the I2C bus state
 *
 * In a multimaster environment, after IP software reset, BB-bit value करोesn't
 * correspond to the current bus state. It may happen what BB-bit will be 0,
 * जबतक the bus is busy due to another I2C master activity.
 * Here are BB-bit values after reset:
 *     SDA   SCL   BB   NOTES
 *       0     0    0   1, 2
 *       1     0    0   1, 2
 *       0     1    1
 *       1     1    0   3
 * Later, अगर IP detect SDA=0 and SCL=1 (ACK) or SDA 1->0 जबतक SCL=1 (START)
 * combinations on the bus, it set BB-bit to 1.
 * If IP detect SDA 0->1 जबतक SCL=1 (STOP) combination on the bus,
 * it set BB-bit to 0 and BF to 1.
 * BB and BF bits correctly tracks the bus state जबतक IP is suspended
 * BB bit became valid on the next FCLK घड़ी after CON_EN bit set
 *
 * NOTES:
 * 1. Any transfer started when BB=0 and bus is busy wouldn't be
 *    completed by IP and results in controller समयout.
 * 2. Any transfer started when BB=0 and SCL=0 results in IP
 *    starting to drive SDA low. In that हाल IP corrupt data
 *    on the bus.
 * 3. Any transfer started in the middle of another master's transfer
 *    results in unpredictable results and data corruption
 */
अटल पूर्णांक omap_i2c_रुको_क्रम_bb_valid(काष्ठा omap_i2c_dev *omap)
अणु
	अचिन्हित दीर्घ bus_मुक्त_समयout = 0;
	अचिन्हित दीर्घ समयout;
	पूर्णांक bus_मुक्त = 0;
	u16 stat, systest;

	अगर (omap->bb_valid)
		वापस 0;

	समयout = jअगरfies + OMAP_I2C_TIMEOUT;
	जबतक (1) अणु
		stat = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_STAT_REG);
		/*
		 * We will see BB or BF event in a हाल IP had detected any
		 * activity on the I2C bus. Now IP correctly tracks the bus
		 * state. BB-bit value is valid.
		 */
		अगर (stat & (OMAP_I2C_STAT_BB | OMAP_I2C_STAT_BF))
			अवरोध;

		/*
		 * Otherwise, we must look संकेतs on the bus to make
		 * the right decision.
		 */
		systest = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_SYSTEST_REG);
		अगर ((systest & OMAP_I2C_SYSTEST_SCL_I_FUNC) &&
		    (systest & OMAP_I2C_SYSTEST_SDA_I_FUNC)) अणु
			अगर (!bus_मुक्त) अणु
				bus_मुक्त_समयout = jअगरfies +
					OMAP_I2C_BUS_FREE_TIMEOUT;
				bus_मुक्त = 1;
			पूर्ण

			/*
			 * SDA and SCL lines was high क्रम 10 ms without bus
			 * activity detected. The bus is मुक्त. Consider
			 * BB-bit value is valid.
			 */
			अगर (समय_after(jअगरfies, bus_मुक्त_समयout))
				अवरोध;
		पूर्ण अन्यथा अणु
			bus_मुक्त = 0;
		पूर्ण

		अगर (समय_after(jअगरfies, समयout)) अणु
			/*
			 * SDA or SCL were low क्रम the entire समयout without
			 * any activity detected. Most likely, a slave is
			 * locking up the bus with no master driving the घड़ी.
			 */
			dev_warn(omap->dev, "timeout waiting for bus ready\n");
			वापस omap_i2c_recover_bus(omap);
		पूर्ण

		msleep(1);
	पूर्ण

	omap->bb_valid = 1;
	वापस 0;
पूर्ण

अटल व्योम omap_i2c_resize_fअगरo(काष्ठा omap_i2c_dev *omap, u8 size, bool is_rx)
अणु
	u16		buf;

	अगर (omap->flags & OMAP_I2C_FLAG_NO_FIFO)
		वापस;

	/*
	 * Set up notअगरication threshold based on message size. We're करोing
	 * this to try and aव्योम draining feature as much as possible. Whenever
	 * we have big messages to transfer (bigger than our total fअगरo size)
	 * then we might use draining feature to transfer the reमुख्यing bytes.
	 */

	omap->threshold = clamp(size, (u8) 1, omap->fअगरo_size);

	buf = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_BUF_REG);

	अगर (is_rx) अणु
		/* Clear RX Threshold */
		buf &= ~(0x3f << 8);
		buf |= ((omap->threshold - 1) << 8) | OMAP_I2C_BUF_RXFIF_CLR;
	पूर्ण अन्यथा अणु
		/* Clear TX Threshold */
		buf &= ~0x3f;
		buf |= (omap->threshold - 1) | OMAP_I2C_BUF_TXFIF_CLR;
	पूर्ण

	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_BUF_REG, buf);

	अगर (omap->rev < OMAP_I2C_REV_ON_3630)
		omap->b_hw = 1; /* Enable hardware fixes */

	/* calculate wakeup latency स्थिरraपूर्णांक क्रम MPU */
	अगर (omap->set_mpu_wkup_lat != शून्य)
		omap->latency = (1000000 * omap->threshold) /
			(1000 * omap->speed / 8);
पूर्ण

अटल व्योम omap_i2c_रुको(काष्ठा omap_i2c_dev *omap)
अणु
	u16 stat;
	u16 mask = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_IE_REG);
	पूर्णांक count = 0;

	करो अणु
		stat = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_STAT_REG);
		count++;
	पूर्ण जबतक (!(stat & mask) && count < 5);
पूर्ण

/*
 * Low level master पढ़ो/ग_लिखो transaction.
 */
अटल पूर्णांक omap_i2c_xfer_msg(काष्ठा i2c_adapter *adap,
			     काष्ठा i2c_msg *msg, पूर्णांक stop, bool polling)
अणु
	काष्ठा omap_i2c_dev *omap = i2c_get_adapdata(adap);
	अचिन्हित दीर्घ समयout;
	u16 w;
	पूर्णांक ret;

	dev_dbg(omap->dev, "addr: 0x%04x, len: %d, flags: 0x%x, stop: %d\n",
		msg->addr, msg->len, msg->flags, stop);

	omap->receiver = !!(msg->flags & I2C_M_RD);
	omap_i2c_resize_fअगरo(omap, msg->len, omap->receiver);

	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_SA_REG, msg->addr);

	/* REVISIT: Could the STB bit of I2C_CON be used with probing? */
	omap->buf = msg->buf;
	omap->buf_len = msg->len;

	/* make sure ग_लिखोs to omap->buf_len are ordered */
	barrier();

	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CNT_REG, omap->buf_len);

	/* Clear the FIFO Buffers */
	w = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_BUF_REG);
	w |= OMAP_I2C_BUF_RXFIF_CLR | OMAP_I2C_BUF_TXFIF_CLR;
	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_BUF_REG, w);

	अगर (!polling)
		reinit_completion(&omap->cmd_complete);
	omap->cmd_err = 0;

	w = OMAP_I2C_CON_EN | OMAP_I2C_CON_MST | OMAP_I2C_CON_STT;

	/* High speed configuration */
	अगर (omap->speed > 400)
		w |= OMAP_I2C_CON_OPMODE_HS;

	अगर (msg->flags & I2C_M_STOP)
		stop = 1;
	अगर (msg->flags & I2C_M_TEN)
		w |= OMAP_I2C_CON_XA;
	अगर (!(msg->flags & I2C_M_RD))
		w |= OMAP_I2C_CON_TRX;

	अगर (!omap->b_hw && stop)
		w |= OMAP_I2C_CON_STP;
	/*
	 * NOTE: STAT_BB bit could became 1 here अगर another master occupy
	 * the bus. IP successfully complete transfer when the bus will be
	 * मुक्त again (BB reset to 0).
	 */
	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CON_REG, w);

	/*
	 * Don't ग_लिखो stt and stp together on some hardware.
	 */
	अगर (omap->b_hw && stop) अणु
		अचिन्हित दीर्घ delay = jअगरfies + OMAP_I2C_TIMEOUT;
		u16 con = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_CON_REG);
		जबतक (con & OMAP_I2C_CON_STT) अणु
			con = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_CON_REG);

			/* Let the user know अगर i2c is in a bad state */
			अगर (समय_after(jअगरfies, delay)) अणु
				dev_err(omap->dev, "controller timed out "
				"waiting for start condition to finish\n");
				वापस -ETIMEDOUT;
			पूर्ण
			cpu_relax();
		पूर्ण

		w |= OMAP_I2C_CON_STP;
		w &= ~OMAP_I2C_CON_STT;
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CON_REG, w);
	पूर्ण

	/*
	 * REVISIT: We should पात the transfer on संकेतs, but the bus goes
	 * पूर्णांकo arbitration and we're currently unable to recover from it.
	 */
	अगर (!polling) अणु
		समयout = रुको_क्रम_completion_समयout(&omap->cmd_complete,
						      OMAP_I2C_TIMEOUT);
	पूर्ण अन्यथा अणु
		करो अणु
			omap_i2c_रुको(omap);
			ret = omap_i2c_xfer_data(omap);
		पूर्ण जबतक (ret == -EAGAIN);

		समयout = !ret;
	पूर्ण

	अगर (समयout == 0) अणु
		dev_err(omap->dev, "controller timed out\n");
		omap_i2c_reset(omap);
		__omap_i2c_init(omap);
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (likely(!omap->cmd_err))
		वापस 0;

	/* We have an error */
	अगर (omap->cmd_err & (OMAP_I2C_STAT_ROVR | OMAP_I2C_STAT_XUDF)) अणु
		omap_i2c_reset(omap);
		__omap_i2c_init(omap);
		वापस -EIO;
	पूर्ण

	अगर (omap->cmd_err & OMAP_I2C_STAT_AL)
		वापस -EAGAIN;

	अगर (omap->cmd_err & OMAP_I2C_STAT_NACK) अणु
		अगर (msg->flags & I2C_M_IGNORE_NAK)
			वापस 0;

		w = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_CON_REG);
		w |= OMAP_I2C_CON_STP;
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CON_REG, w);
		वापस -EREMOTEIO;
	पूर्ण
	वापस -EIO;
पूर्ण


/*
 * Prepare controller क्रम a transaction and call omap_i2c_xfer_msg
 * to करो the work during IRQ processing.
 */
अटल पूर्णांक
omap_i2c_xfer_common(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[], पूर्णांक num,
		     bool polling)
अणु
	काष्ठा omap_i2c_dev *omap = i2c_get_adapdata(adap);
	पूर्णांक i;
	पूर्णांक r;

	r = pm_runसमय_get_sync(omap->dev);
	अगर (r < 0)
		जाओ out;

	r = omap_i2c_रुको_क्रम_bb_valid(omap);
	अगर (r < 0)
		जाओ out;

	r = omap_i2c_रुको_क्रम_bb(omap);
	अगर (r < 0)
		जाओ out;

	अगर (omap->set_mpu_wkup_lat != शून्य)
		omap->set_mpu_wkup_lat(omap->dev, omap->latency);

	क्रम (i = 0; i < num; i++) अणु
		r = omap_i2c_xfer_msg(adap, &msgs[i], (i == (num - 1)),
				      polling);
		अगर (r != 0)
			अवरोध;
	पूर्ण

	अगर (r == 0)
		r = num;

	omap_i2c_रुको_क्रम_bb(omap);

	अगर (omap->set_mpu_wkup_lat != शून्य)
		omap->set_mpu_wkup_lat(omap->dev, -1);

out:
	pm_runसमय_mark_last_busy(omap->dev);
	pm_runसमय_put_स्वतःsuspend(omap->dev);
	वापस r;
पूर्ण

अटल पूर्णांक
omap_i2c_xfer_irq(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	वापस omap_i2c_xfer_common(adap, msgs, num, false);
पूर्ण

अटल पूर्णांक
omap_i2c_xfer_polling(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	वापस omap_i2c_xfer_common(adap, msgs, num, true);
पूर्ण

अटल u32
omap_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK) |
	       I2C_FUNC_PROTOCOL_MANGLING;
पूर्ण

अटल अंतरभूत व्योम
omap_i2c_complete_cmd(काष्ठा omap_i2c_dev *omap, u16 err)
अणु
	omap->cmd_err |= err;
	complete(&omap->cmd_complete);
पूर्ण

अटल अंतरभूत व्योम
omap_i2c_ack_stat(काष्ठा omap_i2c_dev *omap, u16 stat)
अणु
	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_STAT_REG, stat);
पूर्ण

अटल अंतरभूत व्योम i2c_omap_errata_i207(काष्ठा omap_i2c_dev *omap, u16 stat)
अणु
	/*
	 * I2C Errata(Errata Nos. OMAP2: 1.67, OMAP3: 1.8)
	 * Not applicable क्रम OMAP4.
	 * Under certain rare conditions, RDR could be set again
	 * when the bus is busy, then ignore the पूर्णांकerrupt and
	 * clear the पूर्णांकerrupt.
	 */
	अगर (stat & OMAP_I2C_STAT_RDR) अणु
		/* Step 1: If RDR is set, clear it */
		omap_i2c_ack_stat(omap, OMAP_I2C_STAT_RDR);

		/* Step 2: */
		अगर (!(omap_i2c_पढ़ो_reg(omap, OMAP_I2C_STAT_REG)
						& OMAP_I2C_STAT_BB)) अणु

			/* Step 3: */
			अगर (omap_i2c_पढ़ो_reg(omap, OMAP_I2C_STAT_REG)
						& OMAP_I2C_STAT_RDR) अणु
				omap_i2c_ack_stat(omap, OMAP_I2C_STAT_RDR);
				dev_dbg(omap->dev, "RDR when bus is busy.\n");
			पूर्ण

		पूर्ण
	पूर्ण
पूर्ण

/* rev1 devices are apparently only on some 15xx */
#अगर_घोषित CONFIG_ARCH_OMAP15XX

अटल irqवापस_t
omap_i2c_omap1_isr(पूर्णांक this_irq, व्योम *dev_id)
अणु
	काष्ठा omap_i2c_dev *omap = dev_id;
	u16 iv, w;

	अगर (pm_runसमय_suspended(omap->dev))
		वापस IRQ_NONE;

	iv = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_IV_REG);
	चयन (iv) अणु
	हाल 0x00:	/* None */
		अवरोध;
	हाल 0x01:	/* Arbitration lost */
		dev_err(omap->dev, "Arbitration lost\n");
		omap_i2c_complete_cmd(omap, OMAP_I2C_STAT_AL);
		अवरोध;
	हाल 0x02:	/* No acknowledgement */
		omap_i2c_complete_cmd(omap, OMAP_I2C_STAT_NACK);
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CON_REG, OMAP_I2C_CON_STP);
		अवरोध;
	हाल 0x03:	/* Register access पढ़ोy */
		omap_i2c_complete_cmd(omap, 0);
		अवरोध;
	हाल 0x04:	/* Receive data पढ़ोy */
		अगर (omap->buf_len) अणु
			w = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_DATA_REG);
			*omap->buf++ = w;
			omap->buf_len--;
			अगर (omap->buf_len) अणु
				*omap->buf++ = w >> 8;
				omap->buf_len--;
			पूर्ण
		पूर्ण अन्यथा
			dev_err(omap->dev, "RRDY IRQ while no data requested\n");
		अवरोध;
	हाल 0x05:	/* Transmit data पढ़ोy */
		अगर (omap->buf_len) अणु
			w = *omap->buf++;
			omap->buf_len--;
			अगर (omap->buf_len) अणु
				w |= *omap->buf++ << 8;
				omap->buf_len--;
			पूर्ण
			omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_DATA_REG, w);
		पूर्ण अन्यथा
			dev_err(omap->dev, "XRDY IRQ while no data to send\n");
		अवरोध;
	शेष:
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण
#अन्यथा
#घोषणा omap_i2c_omap1_isr		शून्य
#पूर्ण_अगर

/*
 * OMAP3430 Errata i462: When an XRDY/XDR is hit, रुको क्रम XUDF beक्रमe writing
 * data to DATA_REG. Otherwise some data bytes can be lost जबतक transferring
 * them from the memory to the I2C पूर्णांकerface.
 */
अटल पूर्णांक errata_omap3_i462(काष्ठा omap_i2c_dev *omap)
अणु
	अचिन्हित दीर्घ समयout = 10000;
	u16 stat;

	करो अणु
		stat = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_STAT_REG);
		अगर (stat & OMAP_I2C_STAT_XUDF)
			अवरोध;

		अगर (stat & (OMAP_I2C_STAT_NACK | OMAP_I2C_STAT_AL)) अणु
			omap_i2c_ack_stat(omap, (OMAP_I2C_STAT_XRDY |
							OMAP_I2C_STAT_XDR));
			अगर (stat & OMAP_I2C_STAT_NACK) अणु
				omap->cmd_err |= OMAP_I2C_STAT_NACK;
				omap_i2c_ack_stat(omap, OMAP_I2C_STAT_NACK);
			पूर्ण

			अगर (stat & OMAP_I2C_STAT_AL) अणु
				dev_err(omap->dev, "Arbitration lost\n");
				omap->cmd_err |= OMAP_I2C_STAT_AL;
				omap_i2c_ack_stat(omap, OMAP_I2C_STAT_AL);
			पूर्ण

			वापस -EIO;
		पूर्ण

		cpu_relax();
	पूर्ण जबतक (--समयout);

	अगर (!समयout) अणु
		dev_err(omap->dev, "timeout waiting on XUDF bit\n");
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम omap_i2c_receive_data(काष्ठा omap_i2c_dev *omap, u8 num_bytes,
		bool is_rdr)
अणु
	u16		w;

	जबतक (num_bytes--) अणु
		w = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_DATA_REG);
		*omap->buf++ = w;
		omap->buf_len--;

		/*
		 * Data reg in 2430, omap3 and
		 * omap4 is 8 bit wide
		 */
		अगर (omap->flags & OMAP_I2C_FLAG_16BIT_DATA_REG) अणु
			*omap->buf++ = w >> 8;
			omap->buf_len--;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक omap_i2c_transmit_data(काष्ठा omap_i2c_dev *omap, u8 num_bytes,
		bool is_xdr)
अणु
	u16		w;

	जबतक (num_bytes--) अणु
		w = *omap->buf++;
		omap->buf_len--;

		/*
		 * Data reg in 2430, omap3 and
		 * omap4 is 8 bit wide
		 */
		अगर (omap->flags & OMAP_I2C_FLAG_16BIT_DATA_REG) अणु
			w |= *omap->buf++ << 8;
			omap->buf_len--;
		पूर्ण

		अगर (omap->errata & I2C_OMAP_ERRATA_I462) अणु
			पूर्णांक ret;

			ret = errata_omap3_i462(omap);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_DATA_REG, w);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t
omap_i2c_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap_i2c_dev *omap = dev_id;
	irqवापस_t ret = IRQ_HANDLED;
	u16 mask;
	u16 stat;

	stat = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_STAT_REG);
	mask = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_IE_REG);

	अगर (stat & mask)
		ret = IRQ_WAKE_THREAD;

	वापस ret;
पूर्ण

अटल पूर्णांक omap_i2c_xfer_data(काष्ठा omap_i2c_dev *omap)
अणु
	u16 bits;
	u16 stat;
	पूर्णांक err = 0, count = 0;

	करो अणु
		bits = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_IE_REG);
		stat = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_STAT_REG);
		stat &= bits;

		/* If we're in receiver mode, ignore XDR/XRDY */
		अगर (omap->receiver)
			stat &= ~(OMAP_I2C_STAT_XDR | OMAP_I2C_STAT_XRDY);
		अन्यथा
			stat &= ~(OMAP_I2C_STAT_RDR | OMAP_I2C_STAT_RRDY);

		अगर (!stat) अणु
			/* my work here is करोne */
			err = -EAGAIN;
			अवरोध;
		पूर्ण

		dev_dbg(omap->dev, "IRQ (ISR = 0x%04x)\n", stat);
		अगर (count++ == 100) अणु
			dev_warn(omap->dev, "Too much work in one IRQ\n");
			अवरोध;
		पूर्ण

		अगर (stat & OMAP_I2C_STAT_NACK) अणु
			err |= OMAP_I2C_STAT_NACK;
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_NACK);
		पूर्ण

		अगर (stat & OMAP_I2C_STAT_AL) अणु
			dev_err(omap->dev, "Arbitration lost\n");
			err |= OMAP_I2C_STAT_AL;
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_AL);
		पूर्ण

		/*
		 * ProDB0017052: Clear ARDY bit twice
		 */
		अगर (stat & OMAP_I2C_STAT_ARDY)
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_ARDY);

		अगर (stat & (OMAP_I2C_STAT_ARDY | OMAP_I2C_STAT_NACK |
					OMAP_I2C_STAT_AL)) अणु
			omap_i2c_ack_stat(omap, (OMAP_I2C_STAT_RRDY |
						OMAP_I2C_STAT_RDR |
						OMAP_I2C_STAT_XRDY |
						OMAP_I2C_STAT_XDR |
						OMAP_I2C_STAT_ARDY));
			अवरोध;
		पूर्ण

		अगर (stat & OMAP_I2C_STAT_RDR) अणु
			u8 num_bytes = 1;

			अगर (omap->fअगरo_size)
				num_bytes = omap->buf_len;

			अगर (omap->errata & I2C_OMAP_ERRATA_I207) अणु
				i2c_omap_errata_i207(omap, stat);
				num_bytes = (omap_i2c_पढ़ो_reg(omap,
					OMAP_I2C_BUFSTAT_REG) >> 8) & 0x3F;
			पूर्ण

			omap_i2c_receive_data(omap, num_bytes, true);
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_RDR);
			जारी;
		पूर्ण

		अगर (stat & OMAP_I2C_STAT_RRDY) अणु
			u8 num_bytes = 1;

			अगर (omap->threshold)
				num_bytes = omap->threshold;

			omap_i2c_receive_data(omap, num_bytes, false);
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_RRDY);
			जारी;
		पूर्ण

		अगर (stat & OMAP_I2C_STAT_XDR) अणु
			u8 num_bytes = 1;
			पूर्णांक ret;

			अगर (omap->fअगरo_size)
				num_bytes = omap->buf_len;

			ret = omap_i2c_transmit_data(omap, num_bytes, true);
			अगर (ret < 0)
				अवरोध;

			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_XDR);
			जारी;
		पूर्ण

		अगर (stat & OMAP_I2C_STAT_XRDY) अणु
			u8 num_bytes = 1;
			पूर्णांक ret;

			अगर (omap->threshold)
				num_bytes = omap->threshold;

			ret = omap_i2c_transmit_data(omap, num_bytes, false);
			अगर (ret < 0)
				अवरोध;

			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_XRDY);
			जारी;
		पूर्ण

		अगर (stat & OMAP_I2C_STAT_ROVR) अणु
			dev_err(omap->dev, "Receive overrun\n");
			err |= OMAP_I2C_STAT_ROVR;
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_ROVR);
			अवरोध;
		पूर्ण

		अगर (stat & OMAP_I2C_STAT_XUDF) अणु
			dev_err(omap->dev, "Transmit underflow\n");
			err |= OMAP_I2C_STAT_XUDF;
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_XUDF);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (stat);

	वापस err;
पूर्ण

अटल irqवापस_t
omap_i2c_isr_thपढ़ो(पूर्णांक this_irq, व्योम *dev_id)
अणु
	पूर्णांक ret;
	काष्ठा omap_i2c_dev *omap = dev_id;

	ret = omap_i2c_xfer_data(omap);
	अगर (ret != -EAGAIN)
		omap_i2c_complete_cmd(omap, ret);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm omap_i2c_algo = अणु
	.master_xfer	= omap_i2c_xfer_irq,
	.master_xfer_atomic	= omap_i2c_xfer_polling,
	.functionality	= omap_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks omap_i2c_quirks = अणु
	.flags = I2C_AQ_NO_ZERO_LEN,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा omap_i2c_bus_platक्रमm_data omap2420_pdata = अणु
	.rev = OMAP_I2C_IP_VERSION_1,
	.flags = OMAP_I2C_FLAG_NO_FIFO |
			OMAP_I2C_FLAG_SIMPLE_CLOCK |
			OMAP_I2C_FLAG_16BIT_DATA_REG |
			OMAP_I2C_FLAG_BUS_SHIFT_2,
पूर्ण;

अटल काष्ठा omap_i2c_bus_platक्रमm_data omap2430_pdata = अणु
	.rev = OMAP_I2C_IP_VERSION_1,
	.flags = OMAP_I2C_FLAG_BUS_SHIFT_2 |
			OMAP_I2C_FLAG_FORCE_19200_INT_CLK,
पूर्ण;

अटल काष्ठा omap_i2c_bus_platक्रमm_data omap3_pdata = अणु
	.rev = OMAP_I2C_IP_VERSION_1,
	.flags = OMAP_I2C_FLAG_BUS_SHIFT_2,
पूर्ण;

अटल काष्ठा omap_i2c_bus_platक्रमm_data omap4_pdata = अणु
	.rev = OMAP_I2C_IP_VERSION_2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_i2c_of_match[] = अणु
	अणु
		.compatible = "ti,omap4-i2c",
		.data = &omap4_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap3-i2c",
		.data = &omap3_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap2430-i2c",
		.data = &omap2430_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap2420-i2c",
		.data = &omap2420_pdata,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_i2c_of_match);
#पूर्ण_अगर

#घोषणा OMAP_I2C_SCHEME(rev)		((rev & 0xc000) >> 14)

#घोषणा OMAP_I2C_REV_SCHEME_0_MAJOR(rev) (rev >> 4)
#घोषणा OMAP_I2C_REV_SCHEME_0_MINOR(rev) (rev & 0xf)

#घोषणा OMAP_I2C_REV_SCHEME_1_MAJOR(rev) ((rev & 0x0700) >> 7)
#घोषणा OMAP_I2C_REV_SCHEME_1_MINOR(rev) (rev & 0x1f)
#घोषणा OMAP_I2C_SCHEME_0		0
#घोषणा OMAP_I2C_SCHEME_1		1

अटल पूर्णांक omap_i2c_get_scl(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 reg;

	reg = omap_i2c_पढ़ो_reg(dev, OMAP_I2C_SYSTEST_REG);

	वापस reg & OMAP_I2C_SYSTEST_SCL_I_FUNC;
पूर्ण

अटल पूर्णांक omap_i2c_get_sda(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 reg;

	reg = omap_i2c_पढ़ो_reg(dev, OMAP_I2C_SYSTEST_REG);

	वापस reg & OMAP_I2C_SYSTEST_SDA_I_FUNC;
पूर्ण

अटल व्योम omap_i2c_set_scl(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	काष्ठा omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 reg;

	reg = omap_i2c_पढ़ो_reg(dev, OMAP_I2C_SYSTEST_REG);
	अगर (val)
		reg |= OMAP_I2C_SYSTEST_SCL_O;
	अन्यथा
		reg &= ~OMAP_I2C_SYSTEST_SCL_O;
	omap_i2c_ग_लिखो_reg(dev, OMAP_I2C_SYSTEST_REG, reg);
पूर्ण

अटल व्योम omap_i2c_prepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 reg;

	reg = omap_i2c_पढ़ो_reg(dev, OMAP_I2C_SYSTEST_REG);
	/* enable test mode */
	reg |= OMAP_I2C_SYSTEST_ST_EN;
	/* select SDA/SCL IO mode */
	reg |= 3 << OMAP_I2C_SYSTEST_TMODE_SHIFT;
	/* set SCL to high-impedance state (reset value is 0) */
	reg |= OMAP_I2C_SYSTEST_SCL_O;
	/* set SDA to high-impedance state (reset value is 0) */
	reg |= OMAP_I2C_SYSTEST_SDA_O;
	omap_i2c_ग_लिखो_reg(dev, OMAP_I2C_SYSTEST_REG, reg);
पूर्ण

अटल व्योम omap_i2c_unprepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 reg;

	reg = omap_i2c_पढ़ो_reg(dev, OMAP_I2C_SYSTEST_REG);
	/* restore reset values */
	reg &= ~OMAP_I2C_SYSTEST_ST_EN;
	reg &= ~OMAP_I2C_SYSTEST_TMODE_MASK;
	reg &= ~OMAP_I2C_SYSTEST_SCL_O;
	reg &= ~OMAP_I2C_SYSTEST_SDA_O;
	omap_i2c_ग_लिखो_reg(dev, OMAP_I2C_SYSTEST_REG, reg);
पूर्ण

अटल काष्ठा i2c_bus_recovery_info omap_i2c_bus_recovery_info = अणु
	.get_scl		= omap_i2c_get_scl,
	.get_sda		= omap_i2c_get_sda,
	.set_scl		= omap_i2c_set_scl,
	.prepare_recovery	= omap_i2c_prepare_recovery,
	.unprepare_recovery	= omap_i2c_unprepare_recovery,
	.recover_bus		= i2c_generic_scl_recovery,
पूर्ण;

अटल पूर्णांक
omap_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_i2c_dev	*omap;
	काष्ठा i2c_adapter	*adap;
	स्थिर काष्ठा omap_i2c_bus_platक्रमm_data *pdata =
		dev_get_platdata(&pdev->dev);
	काष्ठा device_node	*node = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक irq;
	पूर्णांक r;
	u32 rev;
	u16 minor, major;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	omap = devm_kzalloc(&pdev->dev, माप(काष्ठा omap_i2c_dev), GFP_KERNEL);
	अगर (!omap)
		वापस -ENOMEM;

	omap->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(omap->base))
		वापस PTR_ERR(omap->base);

	match = of_match_device(of_match_ptr(omap_i2c_of_match), &pdev->dev);
	अगर (match) अणु
		u32 freq = I2C_MAX_STANDARD_MODE_FREQ;

		pdata = match->data;
		omap->flags = pdata->flags;

		of_property_पढ़ो_u32(node, "clock-frequency", &freq);
		/* convert DT freq value in Hz पूर्णांकo kHz क्रम speed */
		omap->speed = freq / 1000;
	पूर्ण अन्यथा अगर (pdata != शून्य) अणु
		omap->speed = pdata->clkrate;
		omap->flags = pdata->flags;
		omap->set_mpu_wkup_lat = pdata->set_mpu_wkup_lat;
	पूर्ण

	omap->dev = &pdev->dev;
	omap->irq = irq;

	platक्रमm_set_drvdata(pdev, omap);
	init_completion(&omap->cmd_complete);

	omap->reg_shअगरt = (omap->flags >> OMAP_I2C_FLAG_BUS_SHIFT__SHIFT) & 3;

	pm_runसमय_enable(omap->dev);
	pm_runसमय_set_स्वतःsuspend_delay(omap->dev, OMAP_I2C_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(omap->dev);

	r = pm_runसमय_resume_and_get(omap->dev);
	अगर (r < 0)
		जाओ err_disable_pm;

	/*
	 * Read the Rev hi bit-[15:14] ie scheme this is 1 indicates ver2.
	 * On omap1/3/2 Offset 4 is IE Reg the bit [15:14] is 0 at reset.
	 * Also since the omap_i2c_पढ़ो_reg uses reg_map_ip_* a
	 * पढ़ोw_relaxed is करोne.
	 */
	rev = पढ़ोw_relaxed(omap->base + 0x04);

	omap->scheme = OMAP_I2C_SCHEME(rev);
	चयन (omap->scheme) अणु
	हाल OMAP_I2C_SCHEME_0:
		omap->regs = (u8 *)reg_map_ip_v1;
		omap->rev = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_REV_REG);
		minor = OMAP_I2C_REV_SCHEME_0_MAJOR(omap->rev);
		major = OMAP_I2C_REV_SCHEME_0_MAJOR(omap->rev);
		अवरोध;
	हाल OMAP_I2C_SCHEME_1:
	शेष:
		omap->regs = (u8 *)reg_map_ip_v2;
		rev = (rev << 16) |
			omap_i2c_पढ़ो_reg(omap, OMAP_I2C_IP_V2_REVNB_LO);
		minor = OMAP_I2C_REV_SCHEME_1_MINOR(rev);
		major = OMAP_I2C_REV_SCHEME_1_MAJOR(rev);
		omap->rev = rev;
	पूर्ण

	omap->errata = 0;

	अगर (omap->rev >= OMAP_I2C_REV_ON_2430 &&
			omap->rev < OMAP_I2C_REV_ON_4430_PLUS)
		omap->errata |= I2C_OMAP_ERRATA_I207;

	अगर (omap->rev <= OMAP_I2C_REV_ON_3430_3530)
		omap->errata |= I2C_OMAP_ERRATA_I462;

	अगर (!(omap->flags & OMAP_I2C_FLAG_NO_FIFO)) अणु
		u16 s;

		/* Set up the fअगरo size - Get total size */
		s = (omap_i2c_पढ़ो_reg(omap, OMAP_I2C_BUFSTAT_REG) >> 14) & 0x3;
		omap->fअगरo_size = 0x8 << s;

		/*
		 * Set up notअगरication threshold as half the total available
		 * size. This is to ensure that we can handle the status on पूर्णांक
		 * call back latencies.
		 */

		omap->fअगरo_size = (omap->fअगरo_size / 2);

		अगर (omap->rev < OMAP_I2C_REV_ON_3630)
			omap->b_hw = 1; /* Enable hardware fixes */

		/* calculate wakeup latency स्थिरraपूर्णांक क्रम MPU */
		अगर (omap->set_mpu_wkup_lat != शून्य)
			omap->latency = (1000000 * omap->fअगरo_size) /
				       (1000 * omap->speed / 8);
	पूर्ण

	/* reset ASAP, clearing any IRQs */
	omap_i2c_init(omap);

	अगर (omap->rev < OMAP_I2C_OMAP1_REV_2)
		r = devm_request_irq(&pdev->dev, omap->irq, omap_i2c_omap1_isr,
				IRQF_NO_SUSPEND, pdev->name, omap);
	अन्यथा
		r = devm_request_thपढ़ोed_irq(&pdev->dev, omap->irq,
				omap_i2c_isr, omap_i2c_isr_thपढ़ो,
				IRQF_NO_SUSPEND | IRQF_ONESHOT,
				pdev->name, omap);

	अगर (r) अणु
		dev_err(omap->dev, "failure requesting irq %i\n", omap->irq);
		जाओ err_unuse_घड़ीs;
	पूर्ण

	adap = &omap->adapter;
	i2c_set_adapdata(adap, omap);
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DEPRECATED;
	strlcpy(adap->name, "OMAP I2C adapter", माप(adap->name));
	adap->algo = &omap_i2c_algo;
	adap->quirks = &omap_i2c_quirks;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;
	adap->bus_recovery_info = &omap_i2c_bus_recovery_info;

	/* i2c device drivers may be active on वापस from add_adapter() */
	adap->nr = pdev->id;
	r = i2c_add_numbered_adapter(adap);
	अगर (r)
		जाओ err_unuse_घड़ीs;

	dev_info(omap->dev, "bus %d rev%d.%d at %d kHz\n", adap->nr,
		 major, minor, omap->speed);

	pm_runसमय_mark_last_busy(omap->dev);
	pm_runसमय_put_स्वतःsuspend(omap->dev);

	वापस 0;

err_unuse_घड़ीs:
	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CON_REG, 0);
	pm_runसमय_करोnt_use_स्वतःsuspend(omap->dev);
	pm_runसमय_put_sync(omap->dev);
err_disable_pm:
	pm_runसमय_disable(&pdev->dev);

	वापस r;
पूर्ण

अटल पूर्णांक omap_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_i2c_dev	*omap = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	i2c_del_adapter(&omap->adapter);
	ret = pm_runसमय_resume_and_get(&pdev->dev);
	अगर (ret < 0)
		वापस ret;

	omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_CON_REG, 0);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap_i2c_dev *omap = dev_get_drvdata(dev);

	omap->iestate = omap_i2c_पढ़ो_reg(omap, OMAP_I2C_IE_REG);

	अगर (omap->scheme == OMAP_I2C_SCHEME_0)
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_IE_REG, 0);
	अन्यथा
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_IP_V2_IRQENABLE_CLR,
				   OMAP_I2C_IP_V2_INTERRUPTS_MASK);

	अगर (omap->rev < OMAP_I2C_OMAP1_REV_2) अणु
		omap_i2c_पढ़ो_reg(omap, OMAP_I2C_IV_REG); /* Read clears */
	पूर्ण अन्यथा अणु
		omap_i2c_ग_लिखो_reg(omap, OMAP_I2C_STAT_REG, omap->iestate);

		/* Flush posted ग_लिखो */
		omap_i2c_पढ़ो_reg(omap, OMAP_I2C_STAT_REG);
	पूर्ण

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा omap_i2c_dev *omap = dev_get_drvdata(dev);

	pinctrl_pm_select_शेष_state(dev);

	अगर (!omap->regs)
		वापस 0;

	__omap_i2c_init(omap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap_i2c_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				      pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(omap_i2c_runसमय_suspend,
			   omap_i2c_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver omap_i2c_driver = अणु
	.probe		= omap_i2c_probe,
	.हटाओ		= omap_i2c_हटाओ,
	.driver		= अणु
		.name	= "omap_i2c",
		.pm	= &omap_i2c_pm_ops,
		.of_match_table = of_match_ptr(omap_i2c_of_match),
	पूर्ण,
पूर्ण;

/* I2C may be needed to bring up other drivers */
अटल पूर्णांक __init
omap_i2c_init_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_i2c_driver);
पूर्ण
subsys_initcall(omap_i2c_init_driver);

अटल व्योम __निकास omap_i2c_निकास_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_i2c_driver);
पूर्ण
module_निकास(omap_i2c_निकास_driver);

MODULE_AUTHOR("MontaVista Software, Inc. (and others)");
MODULE_DESCRIPTION("TI OMAP I2C bus adapter");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:omap_i2c");
