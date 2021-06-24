<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  i2c_adap_pxa.c
 *
 *  I2C adapter क्रम the PXA I2C bus access.
 *
 *  Copyright (C) 2002 Intrinsyc Software Inc.
 *  Copyright (C) 2004-2005 Deep Blue Solutions Ltd.
 *
 *  History:
 *    Apr 2002: Initial version [CS]
 *    Jun 2002: Properly separated algo/adap [FB]
 *    Jan 2003: Fixed several bugs concerning पूर्णांकerrupt handling [Kai-Uwe Bloem]
 *    Jan 2003: added limited संकेत handling [Kai-Uwe Bloem]
 *    Sep 2004: Major rework to ensure efficient bus handling [RMK]
 *    Dec 2004: Added support क्रम PXA27x and slave device probing [Liam Girdwood]
 *    Feb 2005: Rework slave mode handling [RMK]
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/slab.h>

/* I2C रेजिस्टर field definitions */
#घोषणा IBMR_SDAS	(1 << 0)
#घोषणा IBMR_SCLS	(1 << 1)

#घोषणा ICR_START	(1 << 0)	   /* start bit */
#घोषणा ICR_STOP	(1 << 1)	   /* stop bit */
#घोषणा ICR_ACKNAK	(1 << 2)	   /* send ACK(0) or NAK(1) */
#घोषणा ICR_TB		(1 << 3)	   /* transfer byte bit */
#घोषणा ICR_MA		(1 << 4)	   /* master पात */
#घोषणा ICR_SCLE	(1 << 5)	   /* master घड़ी enable */
#घोषणा ICR_IUE		(1 << 6)	   /* unit enable */
#घोषणा ICR_GCD		(1 << 7)	   /* general call disable */
#घोषणा ICR_ITEIE	(1 << 8)	   /* enable tx पूर्णांकerrupts */
#घोषणा ICR_IRFIE	(1 << 9)	   /* enable rx पूर्णांकerrupts */
#घोषणा ICR_BEIE	(1 << 10)	   /* enable bus error पूर्णांकs */
#घोषणा ICR_SSDIE	(1 << 11)	   /* slave STOP detected पूर्णांक enable */
#घोषणा ICR_ALDIE	(1 << 12)	   /* enable arbitration पूर्णांकerrupt */
#घोषणा ICR_SADIE	(1 << 13)	   /* slave address detected पूर्णांक enable */
#घोषणा ICR_UR		(1 << 14)	   /* unit reset */
#घोषणा ICR_FM		(1 << 15)	   /* fast mode */
#घोषणा ICR_HS		(1 << 16)	   /* High Speed mode */
#घोषणा ICR_A3700_FM	(1 << 16)	   /* fast mode क्रम armada-3700 */
#घोषणा ICR_A3700_HS	(1 << 17)	   /* high speed mode क्रम armada-3700 */
#घोषणा ICR_GPIOEN	(1 << 19)	   /* enable GPIO mode क्रम SCL in HS */

#घोषणा ISR_RWM		(1 << 0)	   /* पढ़ो/ग_लिखो mode */
#घोषणा ISR_ACKNAK	(1 << 1)	   /* ack/nak status */
#घोषणा ISR_UB		(1 << 2)	   /* unit busy */
#घोषणा ISR_IBB		(1 << 3)	   /* bus busy */
#घोषणा ISR_SSD		(1 << 4)	   /* slave stop detected */
#घोषणा ISR_ALD		(1 << 5)	   /* arbitration loss detected */
#घोषणा ISR_ITE		(1 << 6)	   /* tx buffer empty */
#घोषणा ISR_IRF		(1 << 7)	   /* rx buffer full */
#घोषणा ISR_GCAD	(1 << 8)	   /* general call address detected */
#घोषणा ISR_SAD		(1 << 9)	   /* slave address detected */
#घोषणा ISR_BED		(1 << 10)	   /* bus error no ACK/NAK */

#घोषणा ILCR_SLV_SHIFT		0
#घोषणा ILCR_SLV_MASK		(0x1FF << ILCR_SLV_SHIFT)
#घोषणा ILCR_FLV_SHIFT		9
#घोषणा ILCR_FLV_MASK		(0x1FF << ILCR_FLV_SHIFT)
#घोषणा ILCR_HLVL_SHIFT		18
#घोषणा ILCR_HLVL_MASK		(0x1FF << ILCR_HLVL_SHIFT)
#घोषणा ILCR_HLVH_SHIFT		27
#घोषणा ILCR_HLVH_MASK		(0x1F << ILCR_HLVH_SHIFT)

#घोषणा IWCR_CNT_SHIFT		0
#घोषणा IWCR_CNT_MASK		(0x1F << IWCR_CNT_SHIFT)
#घोषणा IWCR_HS_CNT1_SHIFT	5
#घोषणा IWCR_HS_CNT1_MASK	(0x1F << IWCR_HS_CNT1_SHIFT)
#घोषणा IWCR_HS_CNT2_SHIFT	10
#घोषणा IWCR_HS_CNT2_MASK	(0x1F << IWCR_HS_CNT2_SHIFT)

/* need a दीर्घer समयout अगर we're dealing with the fact we may well be
 * looking at a multi-master environment
 */
#घोषणा DEF_TIMEOUT             32

#घोषणा NO_SLAVE		(-ENXIO)
#घोषणा BUS_ERROR               (-EREMOTEIO)
#घोषणा XFER_NAKED              (-ECONNREFUSED)
#घोषणा I2C_RETRY               (-2000) /* an error has occurred retry transmit */

/* ICR initialize bit values
 *
 * 15 FM     0 (100 kHz operation)
 * 14 UR     0 (No unit reset)
 * 13 SADIE  0 (Disables the unit from पूर्णांकerrupting on slave addresses
 *              matching its slave address)
 * 12 ALDIE  0 (Disables the unit from पूर्णांकerrupt when it loses arbitration
 *              in master mode)
 * 11 SSDIE  0 (Disables पूर्णांकerrupts from a slave stop detected, in slave mode)
 * 10 BEIE   1 (Enable पूर्णांकerrupts from detected bus errors, no ACK sent)
 *  9 IRFIE  1 (Enable पूर्णांकerrupts from full buffer received)
 *  8 ITEIE  1 (Enables the I2C unit to पूर्णांकerrupt when transmit buffer empty)
 *  7 GCD    1 (Disables i2c unit response to general call messages as a slave)
 *  6 IUE    0 (Disable unit until we change settings)
 *  5 SCLE   1 (Enables the i2c घड़ी output क्रम master mode (drives SCL)
 *  4 MA     0 (Only send stop with the ICR stop bit)
 *  3 TB     0 (We are not transmitting a byte initially)
 *  2 ACKNAK 0 (Send an ACK after the unit receives a byte)
 *  1 STOP   0 (Do not send a STOP)
 *  0 START  0 (Do not send a START)
 */
#घोषणा I2C_ICR_INIT	(ICR_BEIE | ICR_IRFIE | ICR_ITEIE | ICR_GCD | ICR_SCLE)

/* I2C status रेजिस्टर init values
 *
 * 10 BED    1 (Clear bus error detected)
 *  9 SAD    1 (Clear slave address detected)
 *  7 IRF    1 (Clear IDBR Receive Full)
 *  6 ITE    1 (Clear IDBR Transmit Empty)
 *  5 ALD    1 (Clear Arbitration Loss Detected)
 *  4 SSD    1 (Clear Slave Stop Detected)
 */
#घोषणा I2C_ISR_INIT	0x7FF  /* status रेजिस्टर init */

काष्ठा pxa_reg_layout अणु
	u32 ibmr;
	u32 idbr;
	u32 icr;
	u32 isr;
	u32 isar;
	u32 ilcr;
	u32 iwcr;
	u32 fm;
	u32 hs;
पूर्ण;

क्रमागत pxa_i2c_types अणु
	REGS_PXA2XX,
	REGS_PXA3XX,
	REGS_CE4100,
	REGS_PXA910,
	REGS_A3700,
पूर्ण;

/* I2C रेजिस्टर layout definitions */
अटल काष्ठा pxa_reg_layout pxa_reg_layout[] = अणु
	[REGS_PXA2XX] = अणु
		.ibmr =	0x00,
		.idbr =	0x08,
		.icr =	0x10,
		.isr =	0x18,
		.isar =	0x20,
		.fm = ICR_FM,
		.hs = ICR_HS,
	पूर्ण,
	[REGS_PXA3XX] = अणु
		.ibmr =	0x00,
		.idbr =	0x04,
		.icr =	0x08,
		.isr =	0x0c,
		.isar =	0x10,
		.fm = ICR_FM,
		.hs = ICR_HS,
	पूर्ण,
	[REGS_CE4100] = अणु
		.ibmr =	0x14,
		.idbr =	0x0c,
		.icr =	0x00,
		.isr =	0x04,
		/* no isar रेजिस्टर */
		.fm = ICR_FM,
		.hs = ICR_HS,
	पूर्ण,
	[REGS_PXA910] = अणु
		.ibmr = 0x00,
		.idbr = 0x08,
		.icr =	0x10,
		.isr =	0x18,
		.isar = 0x20,
		.ilcr = 0x28,
		.iwcr = 0x30,
		.fm = ICR_FM,
		.hs = ICR_HS,
	पूर्ण,
	[REGS_A3700] = अणु
		.ibmr =	0x00,
		.idbr =	0x04,
		.icr =	0x08,
		.isr =	0x0c,
		.isar =	0x10,
		.fm = ICR_A3700_FM,
		.hs = ICR_A3700_HS,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id i2c_pxa_dt_ids[] = अणु
	अणु .compatible = "mrvl,pxa-i2c", .data = (व्योम *)REGS_PXA2XX पूर्ण,
	अणु .compatible = "mrvl,pwri2c", .data = (व्योम *)REGS_PXA3XX पूर्ण,
	अणु .compatible = "mrvl,mmp-twsi", .data = (व्योम *)REGS_PXA910 पूर्ण,
	अणु .compatible = "marvell,armada-3700-i2c", .data = (व्योम *)REGS_A3700 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_pxa_dt_ids);

अटल स्थिर काष्ठा platक्रमm_device_id i2c_pxa_id_table[] = अणु
	अणु "pxa2xx-i2c",		REGS_PXA2XX पूर्ण,
	अणु "pxa3xx-pwri2c",	REGS_PXA3XX पूर्ण,
	अणु "ce4100-i2c",		REGS_CE4100 पूर्ण,
	अणु "pxa910-i2c",		REGS_PXA910 पूर्ण,
	अणु "armada-3700-i2c",	REGS_A3700  पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, i2c_pxa_id_table);

काष्ठा pxa_i2c अणु
	spinlock_t		lock;
	रुको_queue_head_t	रुको;
	काष्ठा i2c_msg		*msg;
	अचिन्हित पूर्णांक		msg_num;
	अचिन्हित पूर्णांक		msg_idx;
	अचिन्हित पूर्णांक		msg_ptr;
	अचिन्हित पूर्णांक		slave_addr;
	अचिन्हित पूर्णांक		req_slave_addr;

	काष्ठा i2c_adapter	adap;
	काष्ठा clk		*clk;
#अगर_घोषित CONFIG_I2C_PXA_SLAVE
	काष्ठा i2c_client	*slave;
#पूर्ण_अगर

	अचिन्हित पूर्णांक		irqlogidx;
	u32			isrlog[32];
	u32			icrlog[32];

	व्योम __iomem		*reg_base;
	व्योम __iomem		*reg_ibmr;
	व्योम __iomem		*reg_idbr;
	व्योम __iomem		*reg_icr;
	व्योम __iomem		*reg_isr;
	व्योम __iomem		*reg_isar;
	व्योम __iomem		*reg_ilcr;
	व्योम __iomem		*reg_iwcr;

	अचिन्हित दीर्घ		iobase;
	अचिन्हित दीर्घ		iosize;

	पूर्णांक			irq;
	अचिन्हित पूर्णांक		use_pio :1;
	अचिन्हित पूर्णांक		fast_mode :1;
	अचिन्हित पूर्णांक		high_mode:1;
	अचिन्हित अक्षर		master_code;
	अचिन्हित दीर्घ		rate;
	bool			highmode_enter;
	u32			fm_mask;
	u32			hs_mask;

	काष्ठा i2c_bus_recovery_info recovery;
पूर्ण;

#घोषणा _IBMR(i2c)	((i2c)->reg_ibmr)
#घोषणा _IDBR(i2c)	((i2c)->reg_idbr)
#घोषणा _ICR(i2c)	((i2c)->reg_icr)
#घोषणा _ISR(i2c)	((i2c)->reg_isr)
#घोषणा _ISAR(i2c)	((i2c)->reg_isar)
#घोषणा _ILCR(i2c)	((i2c)->reg_ilcr)
#घोषणा _IWCR(i2c)	((i2c)->reg_iwcr)

/*
 * I2C Slave mode address
 */
#घोषणा I2C_PXA_SLAVE_ADDR      0x1

#अगर_घोषित DEBUG

काष्ठा bits अणु
	u32	mask;
	स्थिर अक्षर *set;
	स्थिर अक्षर *unset;
पूर्ण;
#घोषणा PXA_BIT(m, s, u)	अणु .mask = m, .set = s, .unset = u पूर्ण

अटल अंतरभूत व्योम
decode_bits(स्थिर अक्षर *prefix, स्थिर काष्ठा bits *bits, पूर्णांक num, u32 val)
अणु
	prपूर्णांकk("%s %08x:", prefix, val);
	जबतक (num--) अणु
		स्थिर अक्षर *str = val & bits->mask ? bits->set : bits->unset;
		अगर (str)
			pr_cont(" %s", str);
		bits++;
	पूर्ण
	pr_cont("\n");
पूर्ण

अटल स्थिर काष्ठा bits isr_bits[] = अणु
	PXA_BIT(ISR_RWM,	"RX",		"TX"),
	PXA_BIT(ISR_ACKNAK,	"NAK",		"ACK"),
	PXA_BIT(ISR_UB,		"Bsy",		"Rdy"),
	PXA_BIT(ISR_IBB,	"BusBsy",	"BusRdy"),
	PXA_BIT(ISR_SSD,	"SlaveStop",	शून्य),
	PXA_BIT(ISR_ALD,	"ALD",		शून्य),
	PXA_BIT(ISR_ITE,	"TxEmpty",	शून्य),
	PXA_BIT(ISR_IRF,	"RxFull",	शून्य),
	PXA_BIT(ISR_GCAD,	"GenCall",	शून्य),
	PXA_BIT(ISR_SAD,	"SlaveAddr",	शून्य),
	PXA_BIT(ISR_BED,	"BusErr",	शून्य),
पूर्ण;

अटल व्योम decode_ISR(अचिन्हित पूर्णांक val)
अणु
	decode_bits(KERN_DEBUG "ISR", isr_bits, ARRAY_SIZE(isr_bits), val);
पूर्ण

अटल स्थिर काष्ठा bits icr_bits[] = अणु
	PXA_BIT(ICR_START,  "START",	शून्य),
	PXA_BIT(ICR_STOP,   "STOP",	शून्य),
	PXA_BIT(ICR_ACKNAK, "ACKNAK",	शून्य),
	PXA_BIT(ICR_TB,     "TB",	शून्य),
	PXA_BIT(ICR_MA,     "MA",	शून्य),
	PXA_BIT(ICR_SCLE,   "SCLE",	"scle"),
	PXA_BIT(ICR_IUE,    "IUE",	"iue"),
	PXA_BIT(ICR_GCD,    "GCD",	शून्य),
	PXA_BIT(ICR_ITEIE,  "ITEIE",	शून्य),
	PXA_BIT(ICR_IRFIE,  "IRFIE",	शून्य),
	PXA_BIT(ICR_BEIE,   "BEIE",	शून्य),
	PXA_BIT(ICR_SSDIE,  "SSDIE",	शून्य),
	PXA_BIT(ICR_ALDIE,  "ALDIE",	शून्य),
	PXA_BIT(ICR_SADIE,  "SADIE",	शून्य),
	PXA_BIT(ICR_UR,     "UR",		"ur"),
पूर्ण;

#अगर_घोषित CONFIG_I2C_PXA_SLAVE
अटल व्योम decode_ICR(अचिन्हित पूर्णांक val)
अणु
	decode_bits(KERN_DEBUG "ICR", icr_bits, ARRAY_SIZE(icr_bits), val);
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक i2c_debug = DEBUG;

अटल व्योम i2c_pxa_show_state(काष्ठा pxa_i2c *i2c, पूर्णांक lno, स्थिर अक्षर *fname)
अणु
	dev_dbg(&i2c->adap.dev, "state:%s:%d: ISR=%08x, ICR=%08x, IBMR=%02x\n", fname, lno,
		पढ़ोl(_ISR(i2c)), पढ़ोl(_ICR(i2c)), पढ़ोl(_IBMR(i2c)));
पूर्ण

#घोषणा show_state(i2c) i2c_pxa_show_state(i2c, __LINE__, __func__)

अटल व्योम i2c_pxa_scream_blue_murder(काष्ठा pxa_i2c *i2c, स्थिर अक्षर *why)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा device *dev = &i2c->adap.dev;

	dev_err(dev, "slave_0x%x error: %s\n",
		i2c->req_slave_addr >> 1, why);
	dev_err(dev, "msg_num: %d msg_idx: %d msg_ptr: %d\n",
		i2c->msg_num, i2c->msg_idx, i2c->msg_ptr);
	dev_err(dev, "IBMR: %08x IDBR: %08x ICR: %08x ISR: %08x\n",
		पढ़ोl(_IBMR(i2c)), पढ़ोl(_IDBR(i2c)), पढ़ोl(_ICR(i2c)),
		पढ़ोl(_ISR(i2c)));
	dev_err(dev, "log:");
	क्रम (i = 0; i < i2c->irqlogidx; i++)
		pr_cont(" [%03x:%05x]", i2c->isrlog[i], i2c->icrlog[i]);
	pr_cont("\n");
पूर्ण

#अन्यथा /* अगरdef DEBUG */

#घोषणा i2c_debug	0

#घोषणा show_state(i2c) करो अणु पूर्ण जबतक (0)
#घोषणा decode_ISR(val) करो अणु पूर्ण जबतक (0)
#घोषणा decode_ICR(val) करो अणु पूर्ण जबतक (0)
#घोषणा i2c_pxa_scream_blue_murder(i2c, why) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* अगरdef DEBUG / अन्यथा */

अटल व्योम i2c_pxa_master_complete(काष्ठा pxa_i2c *i2c, पूर्णांक ret);

अटल अंतरभूत पूर्णांक i2c_pxa_is_slavemode(काष्ठा pxa_i2c *i2c)
अणु
	वापस !(पढ़ोl(_ICR(i2c)) & ICR_SCLE);
पूर्ण

अटल व्योम i2c_pxa_पात(काष्ठा pxa_i2c *i2c)
अणु
	पूर्णांक i = 250;

	अगर (i2c_pxa_is_slavemode(i2c)) अणु
		dev_dbg(&i2c->adap.dev, "%s: called in slave mode\n", __func__);
		वापस;
	पूर्ण

	जबतक ((i > 0) && (पढ़ोl(_IBMR(i2c)) & IBMR_SDAS) == 0) अणु
		अचिन्हित दीर्घ icr = पढ़ोl(_ICR(i2c));

		icr &= ~ICR_START;
		icr |= ICR_ACKNAK | ICR_STOP | ICR_TB;

		ग_लिखोl(icr, _ICR(i2c));

		show_state(i2c);

		mdelay(1);
		i --;
	पूर्ण

	ग_लिखोl(पढ़ोl(_ICR(i2c)) & ~(ICR_MA | ICR_START | ICR_STOP),
	       _ICR(i2c));
पूर्ण

अटल पूर्णांक i2c_pxa_रुको_bus_not_busy(काष्ठा pxa_i2c *i2c)
अणु
	पूर्णांक समयout = DEF_TIMEOUT;
	u32 isr;

	जबतक (1) अणु
		isr = पढ़ोl(_ISR(i2c));
		अगर (!(isr & (ISR_IBB | ISR_UB)))
			वापस 0;

		अगर (isr & ISR_SAD)
			समयout += 4;

		अगर (!समयout--)
			अवरोध;

		msleep(2);
		show_state(i2c);
	पूर्ण

	show_state(i2c);

	वापस I2C_RETRY;
पूर्ण

अटल पूर्णांक i2c_pxa_रुको_master(काष्ठा pxa_i2c *i2c)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ*4;

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (i2c_debug > 1)
			dev_dbg(&i2c->adap.dev, "%s: %ld: ISR=%08x, ICR=%08x, IBMR=%02x\n",
				__func__, (दीर्घ)jअगरfies, पढ़ोl(_ISR(i2c)), पढ़ोl(_ICR(i2c)), पढ़ोl(_IBMR(i2c)));

		अगर (पढ़ोl(_ISR(i2c)) & ISR_SAD) अणु
			अगर (i2c_debug > 0)
				dev_dbg(&i2c->adap.dev, "%s: Slave detected\n", __func__);
			जाओ out;
		पूर्ण

		/* रुको क्रम unit and bus being not busy, and we also करो a
		 * quick check of the i2c lines themselves to ensure they've
		 * gone high...
		 */
		अगर ((पढ़ोl(_ISR(i2c)) & (ISR_UB | ISR_IBB)) == 0 &&
		    पढ़ोl(_IBMR(i2c)) == (IBMR_SCLS | IBMR_SDAS)) अणु
			अगर (i2c_debug > 0)
				dev_dbg(&i2c->adap.dev, "%s: done\n", __func__);
			वापस 1;
		पूर्ण

		msleep(1);
	पूर्ण

	अगर (i2c_debug > 0)
		dev_dbg(&i2c->adap.dev, "%s: did not free\n", __func__);
 out:
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_pxa_set_master(काष्ठा pxa_i2c *i2c)
अणु
	अगर (i2c_debug)
		dev_dbg(&i2c->adap.dev, "setting to bus master\n");

	अगर ((पढ़ोl(_ISR(i2c)) & (ISR_UB | ISR_IBB)) != 0) अणु
		dev_dbg(&i2c->adap.dev, "%s: unit is busy\n", __func__);
		अगर (!i2c_pxa_रुको_master(i2c)) अणु
			dev_dbg(&i2c->adap.dev, "%s: error: unit busy\n", __func__);
			वापस I2C_RETRY;
		पूर्ण
	पूर्ण

	ग_लिखोl(पढ़ोl(_ICR(i2c)) | ICR_SCLE, _ICR(i2c));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_I2C_PXA_SLAVE
अटल पूर्णांक i2c_pxa_रुको_slave(काष्ठा pxa_i2c *i2c)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ*1;

	/* रुको क्रम stop */

	show_state(i2c);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (i2c_debug > 1)
			dev_dbg(&i2c->adap.dev, "%s: %ld: ISR=%08x, ICR=%08x, IBMR=%02x\n",
				__func__, (दीर्घ)jअगरfies, पढ़ोl(_ISR(i2c)), पढ़ोl(_ICR(i2c)), पढ़ोl(_IBMR(i2c)));

		अगर ((पढ़ोl(_ISR(i2c)) & (ISR_UB|ISR_IBB)) == 0 ||
		    (पढ़ोl(_ISR(i2c)) & ISR_SAD) != 0 ||
		    (पढ़ोl(_ICR(i2c)) & ICR_SCLE) == 0) अणु
			अगर (i2c_debug > 1)
				dev_dbg(&i2c->adap.dev, "%s: done\n", __func__);
			वापस 1;
		पूर्ण

		msleep(1);
	पूर्ण

	अगर (i2c_debug > 0)
		dev_dbg(&i2c->adap.dev, "%s: did not free\n", __func__);
	वापस 0;
पूर्ण

/*
 * clear the hold on the bus, and take of anything अन्यथा
 * that has been configured
 */
अटल व्योम i2c_pxa_set_slave(काष्ठा pxa_i2c *i2c, पूर्णांक errcode)
अणु
	show_state(i2c);

	अगर (errcode < 0) अणु
		udelay(100);   /* simple delay */
	पूर्ण अन्यथा अणु
		/* we need to रुको क्रम the stop condition to end */

		/* अगर we where in stop, then clear... */
		अगर (पढ़ोl(_ICR(i2c)) & ICR_STOP) अणु
			udelay(100);
			ग_लिखोl(पढ़ोl(_ICR(i2c)) & ~ICR_STOP, _ICR(i2c));
		पूर्ण

		अगर (!i2c_pxa_रुको_slave(i2c)) अणु
			dev_err(&i2c->adap.dev, "%s: wait timedout\n",
				__func__);
			वापस;
		पूर्ण
	पूर्ण

	ग_लिखोl(पढ़ोl(_ICR(i2c)) & ~(ICR_STOP|ICR_ACKNAK|ICR_MA), _ICR(i2c));
	ग_लिखोl(पढ़ोl(_ICR(i2c)) & ~ICR_SCLE, _ICR(i2c));

	अगर (i2c_debug) अणु
		dev_dbg(&i2c->adap.dev, "ICR now %08x, ISR %08x\n", पढ़ोl(_ICR(i2c)), पढ़ोl(_ISR(i2c)));
		decode_ICR(पढ़ोl(_ICR(i2c)));
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा i2c_pxa_set_slave(i2c, err)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम i2c_pxa_करो_reset(काष्ठा pxa_i2c *i2c)
अणु
	/* reset according to 9.8 */
	ग_लिखोl(ICR_UR, _ICR(i2c));
	ग_लिखोl(I2C_ISR_INIT, _ISR(i2c));
	ग_लिखोl(पढ़ोl(_ICR(i2c)) & ~ICR_UR, _ICR(i2c));

	अगर (i2c->reg_isar && IS_ENABLED(CONFIG_I2C_PXA_SLAVE))
		ग_लिखोl(i2c->slave_addr, _ISAR(i2c));

	/* set control रेजिस्टर values */
	ग_लिखोl(I2C_ICR_INIT | (i2c->fast_mode ? i2c->fm_mask : 0), _ICR(i2c));
	ग_लिखोl(पढ़ोl(_ICR(i2c)) | (i2c->high_mode ? i2c->hs_mask : 0), _ICR(i2c));

#अगर_घोषित CONFIG_I2C_PXA_SLAVE
	dev_info(&i2c->adap.dev, "Enabling slave mode\n");
	ग_लिखोl(पढ़ोl(_ICR(i2c)) | ICR_SADIE | ICR_ALDIE | ICR_SSDIE, _ICR(i2c));
#पूर्ण_अगर

	i2c_pxa_set_slave(i2c, 0);
पूर्ण

अटल व्योम i2c_pxa_enable(काष्ठा pxa_i2c *i2c)
अणु
	/* enable unit */
	ग_लिखोl(पढ़ोl(_ICR(i2c)) | ICR_IUE, _ICR(i2c));
	udelay(100);
पूर्ण

अटल व्योम i2c_pxa_reset(काष्ठा pxa_i2c *i2c)
अणु
	pr_debug("Resetting I2C Controller Unit\n");

	/* पात any transfer currently under way */
	i2c_pxa_पात(i2c);
	i2c_pxa_करो_reset(i2c);
	i2c_pxa_enable(i2c);
पूर्ण


#अगर_घोषित CONFIG_I2C_PXA_SLAVE
/*
 * PXA I2C Slave mode
 */

अटल व्योम i2c_pxa_slave_txempty(काष्ठा pxa_i2c *i2c, u32 isr)
अणु
	अगर (isr & ISR_BED) अणु
		/* what should we करो here? */
	पूर्ण अन्यथा अणु
		u8 byte = 0;

		अगर (i2c->slave != शून्य)
			i2c_slave_event(i2c->slave, I2C_SLAVE_READ_PROCESSED,
					&byte);

		ग_लिखोl(byte, _IDBR(i2c));
		ग_लिखोl(पढ़ोl(_ICR(i2c)) | ICR_TB, _ICR(i2c));   /* allow next byte */
	पूर्ण
पूर्ण

अटल व्योम i2c_pxa_slave_rxfull(काष्ठा pxa_i2c *i2c, u32 isr)
अणु
	u8 byte = पढ़ोl(_IDBR(i2c));

	अगर (i2c->slave != शून्य)
		i2c_slave_event(i2c->slave, I2C_SLAVE_WRITE_RECEIVED, &byte);

	ग_लिखोl(पढ़ोl(_ICR(i2c)) | ICR_TB, _ICR(i2c));
पूर्ण

अटल व्योम i2c_pxa_slave_start(काष्ठा pxa_i2c *i2c, u32 isr)
अणु
	पूर्णांक समयout;

	अगर (i2c_debug > 0)
		dev_dbg(&i2c->adap.dev, "SAD, mode is slave-%cx\n",
		       (isr & ISR_RWM) ? 'r' : 't');

	अगर (i2c->slave != शून्य) अणु
		अगर (isr & ISR_RWM) अणु
			u8 byte = 0;

			i2c_slave_event(i2c->slave, I2C_SLAVE_READ_REQUESTED,
					&byte);
			ग_लिखोl(byte, _IDBR(i2c));
		पूर्ण अन्यथा अणु
			i2c_slave_event(i2c->slave, I2C_SLAVE_WRITE_REQUESTED,
					शून्य);
		पूर्ण
	पूर्ण

	/*
	 * slave could पूर्णांकerrupt in the middle of us generating a
	 * start condition... अगर this happens, we'd better back off
	 * and stop holding the poor thing up
	 */
	ग_लिखोl(पढ़ोl(_ICR(i2c)) & ~(ICR_START|ICR_STOP), _ICR(i2c));
	ग_लिखोl(पढ़ोl(_ICR(i2c)) | ICR_TB, _ICR(i2c));

	समयout = 0x10000;

	जबतक (1) अणु
		अगर ((पढ़ोl(_IBMR(i2c)) & IBMR_SCLS) == IBMR_SCLS)
			अवरोध;

		समयout--;

		अगर (समयout <= 0) अणु
			dev_err(&i2c->adap.dev, "timeout waiting for SCL high\n");
			अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखोl(पढ़ोl(_ICR(i2c)) & ~ICR_SCLE, _ICR(i2c));
पूर्ण

अटल व्योम i2c_pxa_slave_stop(काष्ठा pxa_i2c *i2c)
अणु
	अगर (i2c_debug > 2)
		dev_dbg(&i2c->adap.dev, "ISR: SSD (Slave Stop)\n");

	अगर (i2c->slave != शून्य)
		i2c_slave_event(i2c->slave, I2C_SLAVE_STOP, शून्य);

	अगर (i2c_debug > 2)
		dev_dbg(&i2c->adap.dev, "ISR: SSD (Slave Stop) acked\n");

	/*
	 * If we have a master-mode message रुकोing,
	 * kick it off now that the slave has completed.
	 */
	अगर (i2c->msg)
		i2c_pxa_master_complete(i2c, I2C_RETRY);
पूर्ण

अटल पूर्णांक i2c_pxa_slave_reg(काष्ठा i2c_client *slave)
अणु
	काष्ठा pxa_i2c *i2c = slave->adapter->algo_data;

	अगर (i2c->slave)
		वापस -EBUSY;

	अगर (!i2c->reg_isar)
		वापस -EAFNOSUPPORT;

	i2c->slave = slave;
	i2c->slave_addr = slave->addr;

	ग_लिखोl(i2c->slave_addr, _ISAR(i2c));

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_pxa_slave_unreg(काष्ठा i2c_client *slave)
अणु
	काष्ठा pxa_i2c *i2c = slave->adapter->algo_data;

	WARN_ON(!i2c->slave);

	i2c->slave_addr = I2C_PXA_SLAVE_ADDR;
	ग_लिखोl(i2c->slave_addr, _ISAR(i2c));

	i2c->slave = शून्य;

	वापस 0;
पूर्ण
#अन्यथा
अटल व्योम i2c_pxa_slave_txempty(काष्ठा pxa_i2c *i2c, u32 isr)
अणु
	अगर (isr & ISR_BED) अणु
		/* what should we करो here? */
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, _IDBR(i2c));
		ग_लिखोl(पढ़ोl(_ICR(i2c)) | ICR_TB, _ICR(i2c));
	पूर्ण
पूर्ण

अटल व्योम i2c_pxa_slave_rxfull(काष्ठा pxa_i2c *i2c, u32 isr)
अणु
	ग_लिखोl(पढ़ोl(_ICR(i2c)) | ICR_TB | ICR_ACKNAK, _ICR(i2c));
पूर्ण

अटल व्योम i2c_pxa_slave_start(काष्ठा pxa_i2c *i2c, u32 isr)
अणु
	पूर्णांक समयout;

	/*
	 * slave could पूर्णांकerrupt in the middle of us generating a
	 * start condition... अगर this happens, we'd better back off
	 * and stop holding the poor thing up
	 */
	ग_लिखोl(पढ़ोl(_ICR(i2c)) & ~(ICR_START|ICR_STOP), _ICR(i2c));
	ग_लिखोl(पढ़ोl(_ICR(i2c)) | ICR_TB | ICR_ACKNAK, _ICR(i2c));

	समयout = 0x10000;

	जबतक (1) अणु
		अगर ((पढ़ोl(_IBMR(i2c)) & IBMR_SCLS) == IBMR_SCLS)
			अवरोध;

		समयout--;

		अगर (समयout <= 0) अणु
			dev_err(&i2c->adap.dev, "timeout waiting for SCL high\n");
			अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखोl(पढ़ोl(_ICR(i2c)) & ~ICR_SCLE, _ICR(i2c));
पूर्ण

अटल व्योम i2c_pxa_slave_stop(काष्ठा pxa_i2c *i2c)
अणु
	अगर (i2c->msg)
		i2c_pxa_master_complete(i2c, I2C_RETRY);
पूर्ण
#पूर्ण_अगर

/*
 * PXA I2C Master mode
 */

अटल अंतरभूत व्योम i2c_pxa_start_message(काष्ठा pxa_i2c *i2c)
अणु
	u32 icr;

	/*
	 * Step 1: target slave address पूर्णांकo IDBR
	 */
	i2c->req_slave_addr = i2c_8bit_addr_from_msg(i2c->msg);
	ग_लिखोl(i2c->req_slave_addr, _IDBR(i2c));

	/*
	 * Step 2: initiate the ग_लिखो.
	 */
	icr = पढ़ोl(_ICR(i2c)) & ~(ICR_STOP | ICR_ALDIE);
	ग_लिखोl(icr | ICR_START | ICR_TB, _ICR(i2c));
पूर्ण

अटल अंतरभूत व्योम i2c_pxa_stop_message(काष्ठा pxa_i2c *i2c)
अणु
	u32 icr;

	/* Clear the START, STOP, ACK, TB and MA flags */
	icr = पढ़ोl(_ICR(i2c));
	icr &= ~(ICR_START | ICR_STOP | ICR_ACKNAK | ICR_TB | ICR_MA);
	ग_लिखोl(icr, _ICR(i2c));
पूर्ण

/*
 * PXA I2C send master code
 * 1. Load master code to IDBR and send it.
 *    Note क्रम HS mode, set ICR [GPIOEN].
 * 2. Wait until win arbitration.
 */
अटल पूर्णांक i2c_pxa_send_mastercode(काष्ठा pxa_i2c *i2c)
अणु
	u32 icr;
	दीर्घ समयout;

	spin_lock_irq(&i2c->lock);
	i2c->highmode_enter = true;
	ग_लिखोl(i2c->master_code, _IDBR(i2c));

	icr = पढ़ोl(_ICR(i2c)) & ~(ICR_STOP | ICR_ALDIE);
	icr |= ICR_GPIOEN | ICR_START | ICR_TB | ICR_ITEIE;
	ग_लिखोl(icr, _ICR(i2c));

	spin_unlock_irq(&i2c->lock);
	समयout = रुको_event_समयout(i2c->रुको,
			i2c->highmode_enter == false, HZ * 1);

	i2c->highmode_enter = false;

	वापस (समयout == 0) ? I2C_RETRY : 0;
पूर्ण

/*
 * i2c_pxa_master_complete - complete the message and wake up.
 */
अटल व्योम i2c_pxa_master_complete(काष्ठा pxa_i2c *i2c, पूर्णांक ret)
अणु
	i2c->msg_ptr = 0;
	i2c->msg = शून्य;
	i2c->msg_idx ++;
	i2c->msg_num = 0;
	अगर (ret)
		i2c->msg_idx = ret;
	अगर (!i2c->use_pio)
		wake_up(&i2c->रुको);
पूर्ण

अटल व्योम i2c_pxa_irq_txempty(काष्ठा pxa_i2c *i2c, u32 isr)
अणु
	u32 icr = पढ़ोl(_ICR(i2c)) & ~(ICR_START|ICR_STOP|ICR_ACKNAK|ICR_TB);

 again:
	/*
	 * If ISR_ALD is set, we lost arbitration.
	 */
	अगर (isr & ISR_ALD) अणु
		/*
		 * Do we need to करो anything here?  The PXA करोcs
		 * are vague about what happens.
		 */
		i2c_pxa_scream_blue_murder(i2c, "ALD set");

		/*
		 * We ignore this error.  We seem to see spurious ALDs
		 * क्रम seemingly no reason.  If we handle them as I think
		 * they should, we end up causing an I2C error, which
		 * is painful क्रम some प्रणालीs.
		 */
		वापस; /* ignore */
	पूर्ण

	अगर ((isr & ISR_BED) &&
		(!((i2c->msg->flags & I2C_M_IGNORE_NAK) &&
			(isr & ISR_ACKNAK)))) अणु
		पूर्णांक ret = BUS_ERROR;

		/*
		 * I2C bus error - either the device NAK'd us, or
		 * something more serious happened.  If we were NAK'd
		 * on the initial address phase, we can retry.
		 */
		अगर (isr & ISR_ACKNAK) अणु
			अगर (i2c->msg_ptr == 0 && i2c->msg_idx == 0)
				ret = NO_SLAVE;
			अन्यथा
				ret = XFER_NAKED;
		पूर्ण
		i2c_pxa_master_complete(i2c, ret);
	पूर्ण अन्यथा अगर (isr & ISR_RWM) अणु
		/*
		 * Read mode.  We have just sent the address byte, and
		 * now we must initiate the transfer.
		 */
		अगर (i2c->msg_ptr == i2c->msg->len - 1 &&
		    i2c->msg_idx == i2c->msg_num - 1)
			icr |= ICR_STOP | ICR_ACKNAK;

		icr |= ICR_ALDIE | ICR_TB;
	पूर्ण अन्यथा अगर (i2c->msg_ptr < i2c->msg->len) अणु
		/*
		 * Write mode.  Write the next data byte.
		 */
		ग_लिखोl(i2c->msg->buf[i2c->msg_ptr++], _IDBR(i2c));

		icr |= ICR_ALDIE | ICR_TB;

		/*
		 * If this is the last byte of the last message or last byte
		 * of any message with I2C_M_STOP (e.g. SCCB), send a STOP.
		 */
		अगर ((i2c->msg_ptr == i2c->msg->len) &&
			((i2c->msg->flags & I2C_M_STOP) ||
			(i2c->msg_idx == i2c->msg_num - 1)))
				icr |= ICR_STOP;

	पूर्ण अन्यथा अगर (i2c->msg_idx < i2c->msg_num - 1) अणु
		/*
		 * Next segment of the message.
		 */
		i2c->msg_ptr = 0;
		i2c->msg_idx ++;
		i2c->msg++;

		/*
		 * If we aren't करोing a repeated start and address,
		 * go back and try to send the next byte.  Note that
		 * we करो not support चयनing the R/W direction here.
		 */
		अगर (i2c->msg->flags & I2C_M_NOSTART)
			जाओ again;

		/*
		 * Write the next address.
		 */
		i2c->req_slave_addr = i2c_8bit_addr_from_msg(i2c->msg);
		ग_लिखोl(i2c->req_slave_addr, _IDBR(i2c));

		/*
		 * And trigger a repeated start, and send the byte.
		 */
		icr &= ~ICR_ALDIE;
		icr |= ICR_START | ICR_TB;
	पूर्ण अन्यथा अणु
		अगर (i2c->msg->len == 0)
			icr |= ICR_MA;
		i2c_pxa_master_complete(i2c, 0);
	पूर्ण

	i2c->icrlog[i2c->irqlogidx-1] = icr;

	ग_लिखोl(icr, _ICR(i2c));
	show_state(i2c);
पूर्ण

अटल व्योम i2c_pxa_irq_rxfull(काष्ठा pxa_i2c *i2c, u32 isr)
अणु
	u32 icr = पढ़ोl(_ICR(i2c)) & ~(ICR_START|ICR_STOP|ICR_ACKNAK|ICR_TB);

	/*
	 * Read the byte.
	 */
	i2c->msg->buf[i2c->msg_ptr++] = पढ़ोl(_IDBR(i2c));

	अगर (i2c->msg_ptr < i2c->msg->len) अणु
		/*
		 * If this is the last byte of the last
		 * message, send a STOP.
		 */
		अगर (i2c->msg_ptr == i2c->msg->len - 1)
			icr |= ICR_STOP | ICR_ACKNAK;

		icr |= ICR_ALDIE | ICR_TB;
	पूर्ण अन्यथा अणु
		i2c_pxa_master_complete(i2c, 0);
	पूर्ण

	i2c->icrlog[i2c->irqlogidx-1] = icr;

	ग_लिखोl(icr, _ICR(i2c));
पूर्ण

#घोषणा VALID_INT_SOURCE	(ISR_SSD | ISR_ALD | ISR_ITE | ISR_IRF | \
				ISR_SAD | ISR_BED)
अटल irqवापस_t i2c_pxa_handler(पूर्णांक this_irq, व्योम *dev_id)
अणु
	काष्ठा pxa_i2c *i2c = dev_id;
	u32 isr = पढ़ोl(_ISR(i2c));

	अगर (!(isr & VALID_INT_SOURCE))
		वापस IRQ_NONE;

	अगर (i2c_debug > 2 && 0) अणु
		dev_dbg(&i2c->adap.dev, "%s: ISR=%08x, ICR=%08x, IBMR=%02x\n",
			__func__, isr, पढ़ोl(_ICR(i2c)), पढ़ोl(_IBMR(i2c)));
		decode_ISR(isr);
	पूर्ण

	अगर (i2c->irqlogidx < ARRAY_SIZE(i2c->isrlog))
		i2c->isrlog[i2c->irqlogidx++] = isr;

	show_state(i2c);

	/*
	 * Always clear all pending IRQs.
	 */
	ग_लिखोl(isr & VALID_INT_SOURCE, _ISR(i2c));

	अगर (isr & ISR_SAD)
		i2c_pxa_slave_start(i2c, isr);
	अगर (isr & ISR_SSD)
		i2c_pxa_slave_stop(i2c);

	अगर (i2c_pxa_is_slavemode(i2c)) अणु
		अगर (isr & ISR_ITE)
			i2c_pxa_slave_txempty(i2c, isr);
		अगर (isr & ISR_IRF)
			i2c_pxa_slave_rxfull(i2c, isr);
	पूर्ण अन्यथा अगर (i2c->msg && (!i2c->highmode_enter)) अणु
		अगर (isr & ISR_ITE)
			i2c_pxa_irq_txempty(i2c, isr);
		अगर (isr & ISR_IRF)
			i2c_pxa_irq_rxfull(i2c, isr);
	पूर्ण अन्यथा अगर ((isr & ISR_ITE) && i2c->highmode_enter) अणु
		i2c->highmode_enter = false;
		wake_up(&i2c->रुको);
	पूर्ण अन्यथा अणु
		i2c_pxa_scream_blue_murder(i2c, "spurious irq");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * We are रक्षित by the adapter bus mutex.
 */
अटल पूर्णांक i2c_pxa_करो_xfer(काष्ठा pxa_i2c *i2c, काष्ठा i2c_msg *msg, पूर्णांक num)
अणु
	दीर्घ समयout;
	पूर्णांक ret;

	/*
	 * Wait क्रम the bus to become मुक्त.
	 */
	ret = i2c_pxa_रुको_bus_not_busy(i2c);
	अगर (ret) अणु
		dev_err(&i2c->adap.dev, "i2c_pxa: timeout waiting for bus free\n");
		i2c_recover_bus(&i2c->adap);
		जाओ out;
	पूर्ण

	/*
	 * Set master mode.
	 */
	ret = i2c_pxa_set_master(i2c);
	अगर (ret) अणु
		dev_err(&i2c->adap.dev, "i2c_pxa_set_master: error %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (i2c->high_mode) अणु
		ret = i2c_pxa_send_mastercode(i2c);
		अगर (ret) अणु
			dev_err(&i2c->adap.dev, "i2c_pxa_send_mastercode timeout\n");
			जाओ out;
			पूर्ण
	पूर्ण

	spin_lock_irq(&i2c->lock);

	i2c->msg = msg;
	i2c->msg_num = num;
	i2c->msg_idx = 0;
	i2c->msg_ptr = 0;
	i2c->irqlogidx = 0;

	i2c_pxa_start_message(i2c);

	spin_unlock_irq(&i2c->lock);

	/*
	 * The rest of the processing occurs in the पूर्णांकerrupt handler.
	 */
	समयout = रुको_event_समयout(i2c->रुको, i2c->msg_num == 0, HZ * 5);
	i2c_pxa_stop_message(i2c);

	/*
	 * We place the वापस code in i2c->msg_idx.
	 */
	ret = i2c->msg_idx;

	अगर (!समयout && i2c->msg_num) अणु
		i2c_pxa_scream_blue_murder(i2c, "timeout with active message");
		i2c_recover_bus(&i2c->adap);
		ret = I2C_RETRY;
	पूर्ण

 out:
	वापस ret;
पूर्ण

अटल पूर्णांक i2c_pxa_पूर्णांकernal_xfer(काष्ठा pxa_i2c *i2c,
				 काष्ठा i2c_msg *msgs, पूर्णांक num,
				 पूर्णांक (*xfer)(काष्ठा pxa_i2c *,
					     काष्ठा i2c_msg *, पूर्णांक num))
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; ; ) अणु
		ret = xfer(i2c, msgs, num);
		अगर (ret != I2C_RETRY && ret != NO_SLAVE)
			जाओ out;
		अगर (++i >= i2c->adap.retries)
			अवरोध;

		अगर (i2c_debug)
			dev_dbg(&i2c->adap.dev, "Retrying transmission\n");
		udelay(100);
	पूर्ण
	अगर (ret != NO_SLAVE)
		i2c_pxa_scream_blue_murder(i2c, "exhausted retries");
	ret = -EREMOTEIO;
 out:
	i2c_pxa_set_slave(i2c, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक i2c_pxa_xfer(काष्ठा i2c_adapter *adap,
			काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा pxa_i2c *i2c = adap->algo_data;

	वापस i2c_pxa_पूर्णांकernal_xfer(i2c, msgs, num, i2c_pxa_करो_xfer);
पूर्ण

अटल u32 i2c_pxa_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
		I2C_FUNC_PROTOCOL_MANGLING | I2C_FUNC_NOSTART;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm i2c_pxa_algorithm = अणु
	.master_xfer	= i2c_pxa_xfer,
	.functionality	= i2c_pxa_functionality,
#अगर_घोषित CONFIG_I2C_PXA_SLAVE
	.reg_slave	= i2c_pxa_slave_reg,
	.unreg_slave	= i2c_pxa_slave_unreg,
#पूर्ण_अगर
पूर्ण;

/* Non-पूर्णांकerrupt mode support */
अटल पूर्णांक i2c_pxa_pio_set_master(काष्ठा pxa_i2c *i2c)
अणु
	/* make समयout the same as क्रम पूर्णांकerrupt based functions */
	दीर्घ समयout = 2 * DEF_TIMEOUT;

	/*
	 * Wait क्रम the bus to become मुक्त.
	 */
	जबतक (समयout-- && पढ़ोl(_ISR(i2c)) & (ISR_IBB | ISR_UB))
		udelay(1000);

	अगर (समयout < 0) अणु
		show_state(i2c);
		dev_err(&i2c->adap.dev,
			"i2c_pxa: timeout waiting for bus free (set_master)\n");
		वापस I2C_RETRY;
	पूर्ण

	/*
	 * Set master mode.
	 */
	ग_लिखोl(पढ़ोl(_ICR(i2c)) | ICR_SCLE, _ICR(i2c));

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_pxa_करो_pio_xfer(काष्ठा pxa_i2c *i2c,
			       काष्ठा i2c_msg *msg, पूर्णांक num)
अणु
	अचिन्हित दीर्घ समयout = 500000; /* 5 seconds */
	पूर्णांक ret = 0;

	ret = i2c_pxa_pio_set_master(i2c);
	अगर (ret)
		जाओ out;

	i2c->msg = msg;
	i2c->msg_num = num;
	i2c->msg_idx = 0;
	i2c->msg_ptr = 0;
	i2c->irqlogidx = 0;

	i2c_pxa_start_message(i2c);

	जबतक (i2c->msg_num > 0 && --समयout) अणु
		i2c_pxa_handler(0, i2c);
		udelay(10);
	पूर्ण

	i2c_pxa_stop_message(i2c);

	/*
	 * We place the वापस code in i2c->msg_idx.
	 */
	ret = i2c->msg_idx;

out:
	अगर (समयout == 0) अणु
		i2c_pxa_scream_blue_murder(i2c, "timeout (do_pio_xfer)");
		ret = I2C_RETRY;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_pxa_pio_xfer(काष्ठा i2c_adapter *adap,
			    काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा pxa_i2c *i2c = adap->algo_data;

	/* If the I2C controller is disabled we need to reset it
	  (probably due to a suspend/resume destroying state). We करो
	  this here as we can then aव्योम worrying about resuming the
	  controller beक्रमe its users. */
	अगर (!(पढ़ोl(_ICR(i2c)) & ICR_IUE))
		i2c_pxa_reset(i2c);

	वापस i2c_pxa_पूर्णांकernal_xfer(i2c, msgs, num, i2c_pxa_करो_pio_xfer);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm i2c_pxa_pio_algorithm = अणु
	.master_xfer	= i2c_pxa_pio_xfer,
	.functionality	= i2c_pxa_functionality,
#अगर_घोषित CONFIG_I2C_PXA_SLAVE
	.reg_slave	= i2c_pxa_slave_reg,
	.unreg_slave	= i2c_pxa_slave_unreg,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक i2c_pxa_probe_dt(काष्ठा platक्रमm_device *pdev, काष्ठा pxa_i2c *i2c,
			    क्रमागत pxa_i2c_types *i2c_types)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id =
			of_match_device(i2c_pxa_dt_ids, &pdev->dev);

	अगर (!of_id)
		वापस 1;

	/* For device tree we always use the dynamic or alias-asचिन्हित ID */
	i2c->adap.nr = -1;

	अगर (of_get_property(np, "mrvl,i2c-polling", शून्य))
		i2c->use_pio = 1;
	अगर (of_get_property(np, "mrvl,i2c-fast-mode", शून्य))
		i2c->fast_mode = 1;

	*i2c_types = (क्रमागत pxa_i2c_types)(of_id->data);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_pxa_probe_pdata(काष्ठा platक्रमm_device *pdev,
			       काष्ठा pxa_i2c *i2c,
			       क्रमागत pxa_i2c_types *i2c_types)
अणु
	काष्ठा i2c_pxa_platक्रमm_data *plat = dev_get_platdata(&pdev->dev);
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);

	*i2c_types = id->driver_data;
	अगर (plat) अणु
		i2c->use_pio = plat->use_pio;
		i2c->fast_mode = plat->fast_mode;
		i2c->high_mode = plat->high_mode;
		i2c->master_code = plat->master_code;
		अगर (!i2c->master_code)
			i2c->master_code = 0xe;
		i2c->rate = plat->rate;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम i2c_pxa_prepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा pxa_i2c *i2c = adap->algo_data;
	u32 ibmr = पढ़ोl(_IBMR(i2c));

	/*
	 * Program the GPIOs to reflect the current I2C bus state जबतक
	 * we transition to recovery; this aव्योमs glitching the bus.
	 */
	gpiod_set_value(i2c->recovery.scl_gpiod, ibmr & IBMR_SCLS);
	gpiod_set_value(i2c->recovery.sda_gpiod, ibmr & IBMR_SDAS);
पूर्ण

अटल व्योम i2c_pxa_unprepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा pxa_i2c *i2c = adap->algo_data;
	काष्ठा i2c_bus_recovery_info *bri = adap->bus_recovery_info;
	u32 isr;

	/*
	 * The bus should now be मुक्त. Clear up the I2C controller beक्रमe
	 * handing control of the bus back to aव्योम the bus changing state.
	 */
	isr = पढ़ोl(_ISR(i2c));
	अगर (isr & (ISR_UB | ISR_IBB)) अणु
		dev_dbg(&i2c->adap.dev,
			"recovery: resetting controller, ISR=0x%08x\n", isr);
		i2c_pxa_करो_reset(i2c);
	पूर्ण

	WARN_ON(pinctrl_select_state(bri->pinctrl, bri->pins_शेष));

	dev_dbg(&i2c->adap.dev, "recovery: IBMR 0x%08x ISR 0x%08x\n",
	        पढ़ोl(_IBMR(i2c)), पढ़ोl(_ISR(i2c)));

	i2c_pxa_enable(i2c);
पूर्ण

अटल पूर्णांक i2c_pxa_init_recovery(काष्ठा pxa_i2c *i2c)
अणु
	काष्ठा i2c_bus_recovery_info *bri = &i2c->recovery;
	काष्ठा device *dev = i2c->adap.dev.parent;

	/*
	 * When slave mode is enabled, we are not the only master on the bus.
	 * Bus recovery can only be perक्रमmed when we are the master, which
	 * we can't be certain of. Thereक्रमe, when slave mode is enabled, करो
	 * not configure bus recovery.
	 */
	अगर (IS_ENABLED(CONFIG_I2C_PXA_SLAVE))
		वापस 0;

	bri->pinctrl = devm_pinctrl_get(dev);
	अगर (PTR_ERR(bri->pinctrl) == -ENODEV) अणु
		bri->pinctrl = शून्य;
		वापस 0;
	पूर्ण
	अगर (IS_ERR(bri->pinctrl))
		वापस PTR_ERR(bri->pinctrl);

	bri->prepare_recovery = i2c_pxa_prepare_recovery;
	bri->unprepare_recovery = i2c_pxa_unprepare_recovery;

	i2c->adap.bus_recovery_info = bri;

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_pxa_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा i2c_pxa_platक्रमm_data *plat = dev_get_platdata(&dev->dev);
	क्रमागत pxa_i2c_types i2c_type;
	काष्ठा pxa_i2c *i2c;
	काष्ठा resource *res = शून्य;
	पूर्णांक ret, irq;

	i2c = devm_kzalloc(&dev->dev, माप(काष्ठा pxa_i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	/* Default adapter num to device id; i2c_pxa_probe_dt can override. */
	i2c->adap.nr = dev->id;
	i2c->adap.owner   = THIS_MODULE;
	i2c->adap.retries = 5;
	i2c->adap.algo_data = i2c;
	i2c->adap.dev.parent = &dev->dev;
#अगर_घोषित CONFIG_OF
	i2c->adap.dev.of_node = dev->dev.of_node;
#पूर्ण_अगर

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	i2c->reg_base = devm_ioremap_resource(&dev->dev, res);
	अगर (IS_ERR(i2c->reg_base))
		वापस PTR_ERR(i2c->reg_base);

	irq = platक्रमm_get_irq(dev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = i2c_pxa_init_recovery(i2c);
	अगर (ret)
		वापस ret;

	ret = i2c_pxa_probe_dt(dev, i2c, &i2c_type);
	अगर (ret > 0)
		ret = i2c_pxa_probe_pdata(dev, i2c, &i2c_type);
	अगर (ret < 0)
		वापस ret;

	spin_lock_init(&i2c->lock);
	init_रुकोqueue_head(&i2c->रुको);

	strlcpy(i2c->adap.name, "pxa_i2c-i2c", माप(i2c->adap.name));

	i2c->clk = devm_clk_get(&dev->dev, शून्य);
	अगर (IS_ERR(i2c->clk)) अणु
		dev_err(&dev->dev, "failed to get the clk: %ld\n", PTR_ERR(i2c->clk));
		वापस PTR_ERR(i2c->clk);
	पूर्ण

	i2c->reg_ibmr = i2c->reg_base + pxa_reg_layout[i2c_type].ibmr;
	i2c->reg_idbr = i2c->reg_base + pxa_reg_layout[i2c_type].idbr;
	i2c->reg_icr = i2c->reg_base + pxa_reg_layout[i2c_type].icr;
	i2c->reg_isr = i2c->reg_base + pxa_reg_layout[i2c_type].isr;
	i2c->fm_mask = pxa_reg_layout[i2c_type].fm;
	i2c->hs_mask = pxa_reg_layout[i2c_type].hs;

	अगर (i2c_type != REGS_CE4100)
		i2c->reg_isar = i2c->reg_base + pxa_reg_layout[i2c_type].isar;

	अगर (i2c_type == REGS_PXA910) अणु
		i2c->reg_ilcr = i2c->reg_base + pxa_reg_layout[i2c_type].ilcr;
		i2c->reg_iwcr = i2c->reg_base + pxa_reg_layout[i2c_type].iwcr;
	पूर्ण

	i2c->iobase = res->start;
	i2c->iosize = resource_size(res);

	i2c->irq = irq;

	i2c->slave_addr = I2C_PXA_SLAVE_ADDR;
	i2c->highmode_enter = false;

	अगर (plat) अणु
		i2c->adap.class = plat->class;
	पूर्ण

	अगर (i2c->high_mode) अणु
		अगर (i2c->rate) अणु
			clk_set_rate(i2c->clk, i2c->rate);
			pr_info("i2c: <%s> set rate to %ld\n",
				i2c->adap.name, clk_get_rate(i2c->clk));
		पूर्ण अन्यथा
			pr_warn("i2c: <%s> clock rate not set\n",
				i2c->adap.name);
	पूर्ण

	clk_prepare_enable(i2c->clk);

	अगर (i2c->use_pio) अणु
		i2c->adap.algo = &i2c_pxa_pio_algorithm;
	पूर्ण अन्यथा अणु
		i2c->adap.algo = &i2c_pxa_algorithm;
		ret = devm_request_irq(&dev->dev, irq, i2c_pxa_handler,
				IRQF_SHARED | IRQF_NO_SUSPEND,
				dev_name(&dev->dev), i2c);
		अगर (ret) अणु
			dev_err(&dev->dev, "failed to request irq: %d\n", ret);
			जाओ ereqirq;
		पूर्ण
	पूर्ण

	i2c_pxa_reset(i2c);

	ret = i2c_add_numbered_adapter(&i2c->adap);
	अगर (ret < 0)
		जाओ ereqirq;

	platक्रमm_set_drvdata(dev, i2c);

#अगर_घोषित CONFIG_I2C_PXA_SLAVE
	dev_info(&i2c->adap.dev, " PXA I2C adapter, slave address %d\n",
		i2c->slave_addr);
#अन्यथा
	dev_info(&i2c->adap.dev, " PXA I2C adapter\n");
#पूर्ण_अगर
	वापस 0;

ereqirq:
	clk_disable_unprepare(i2c->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक i2c_pxa_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pxa_i2c *i2c = platक्रमm_get_drvdata(dev);

	i2c_del_adapter(&i2c->adap);

	clk_disable_unprepare(i2c->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक i2c_pxa_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा pxa_i2c *i2c = dev_get_drvdata(dev);

	clk_disable(i2c->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_pxa_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा pxa_i2c *i2c = dev_get_drvdata(dev);

	clk_enable(i2c->clk);
	i2c_pxa_reset(i2c);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops i2c_pxa_dev_pm_ops = अणु
	.suspend_noirq = i2c_pxa_suspend_noirq,
	.resume_noirq = i2c_pxa_resume_noirq,
पूर्ण;

#घोषणा I2C_PXA_DEV_PM_OPS (&i2c_pxa_dev_pm_ops)
#अन्यथा
#घोषणा I2C_PXA_DEV_PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver i2c_pxa_driver = अणु
	.probe		= i2c_pxa_probe,
	.हटाओ		= i2c_pxa_हटाओ,
	.driver		= अणु
		.name	= "pxa2xx-i2c",
		.pm	= I2C_PXA_DEV_PM_OPS,
		.of_match_table = i2c_pxa_dt_ids,
	पूर्ण,
	.id_table	= i2c_pxa_id_table,
पूर्ण;

अटल पूर्णांक __init i2c_adap_pxa_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&i2c_pxa_driver);
पूर्ण

अटल व्योम __निकास i2c_adap_pxa_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&i2c_pxa_driver);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-i2c");

subsys_initcall(i2c_adap_pxa_init);
module_निकास(i2c_adap_pxa_निकास);
