<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Microchip MRF24J40 802.15.4 Wireless-PAN Networking controller
 *
 * Copyright (C) 2012 Alan Ott <alan@संकेत11.us>
 *                    Signal 11 Software
 */

#समावेश <linux/spi/spi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/ieee802154.h>
#समावेश <linux/irq.h>
#समावेश <net/cfg802154.h>
#समावेश <net/mac802154.h>

/* MRF24J40 Short Address Registers */
#घोषणा REG_RXMCR	0x00  /* Receive MAC control */
#घोषणा BIT_PROMI	BIT(0)
#घोषणा BIT_ERRPKT	BIT(1)
#घोषणा BIT_NOACKRSP	BIT(5)
#घोषणा BIT_PANCOORD	BIT(3)

#घोषणा REG_PANIDL	0x01  /* PAN ID (low) */
#घोषणा REG_PANIDH	0x02  /* PAN ID (high) */
#घोषणा REG_SADRL	0x03  /* Short address (low) */
#घोषणा REG_SADRH	0x04  /* Short address (high) */
#घोषणा REG_EADR0	0x05  /* Long address (low) (high is EADR7) */
#घोषणा REG_EADR1	0x06
#घोषणा REG_EADR2	0x07
#घोषणा REG_EADR3	0x08
#घोषणा REG_EADR4	0x09
#घोषणा REG_EADR5	0x0A
#घोषणा REG_EADR6	0x0B
#घोषणा REG_EADR7	0x0C
#घोषणा REG_RXFLUSH	0x0D
#घोषणा REG_ORDER	0x10
#घोषणा REG_TXMCR	0x11  /* Transmit MAC control */
#घोषणा TXMCR_MIN_BE_SHIFT		3
#घोषणा TXMCR_MIN_BE_MASK		0x18
#घोषणा TXMCR_CSMA_RETRIES_SHIFT	0
#घोषणा TXMCR_CSMA_RETRIES_MASK		0x07

#घोषणा REG_ACKTMOUT	0x12
#घोषणा REG_ESLOTG1	0x13
#घोषणा REG_SYMTICKL	0x14
#घोषणा REG_SYMTICKH	0x15
#घोषणा REG_PACON0	0x16  /* Power Amplअगरier Control */
#घोषणा REG_PACON1	0x17  /* Power Amplअगरier Control */
#घोषणा REG_PACON2	0x18  /* Power Amplअगरier Control */
#घोषणा REG_TXBCON0	0x1A
#घोषणा REG_TXNCON	0x1B  /* Transmit Normal FIFO Control */
#घोषणा BIT_TXNTRIG	BIT(0)
#घोषणा BIT_TXNSECEN	BIT(1)
#घोषणा BIT_TXNACKREQ	BIT(2)

#घोषणा REG_TXG1CON	0x1C
#घोषणा REG_TXG2CON	0x1D
#घोषणा REG_ESLOTG23	0x1E
#घोषणा REG_ESLOTG45	0x1F
#घोषणा REG_ESLOTG67	0x20
#घोषणा REG_TXPEND	0x21
#घोषणा REG_WAKECON	0x22
#घोषणा REG_FROMOFFSET	0x23
#घोषणा REG_TXSTAT	0x24  /* TX MAC Status Register */
#घोषणा REG_TXBCON1	0x25
#घोषणा REG_GATECLK	0x26
#घोषणा REG_TXTIME	0x27
#घोषणा REG_HSYMTMRL	0x28
#घोषणा REG_HSYMTMRH	0x29
#घोषणा REG_SOFTRST	0x2A  /* Soft Reset */
#घोषणा REG_SECCON0	0x2C
#घोषणा REG_SECCON1	0x2D
#घोषणा REG_TXSTBL	0x2E  /* TX Stabilization */
#घोषणा REG_RXSR	0x30
#घोषणा REG_INTSTAT	0x31  /* Interrupt Status */
#घोषणा BIT_TXNIF	BIT(0)
#घोषणा BIT_RXIF	BIT(3)
#घोषणा BIT_SECIF	BIT(4)
#घोषणा BIT_SECIGNORE	BIT(7)

#घोषणा REG_INTCON	0x32  /* Interrupt Control */
#घोषणा BIT_TXNIE	BIT(0)
#घोषणा BIT_RXIE	BIT(3)
#घोषणा BIT_SECIE	BIT(4)

#घोषणा REG_GPIO	0x33  /* GPIO */
#घोषणा REG_TRISGPIO	0x34  /* GPIO direction */
#घोषणा REG_SLPACK	0x35
#घोषणा REG_RFCTL	0x36  /* RF Control Mode Register */
#घोषणा BIT_RFRST	BIT(2)

#घोषणा REG_SECCR2	0x37
#घोषणा REG_BBREG0	0x38
#घोषणा REG_BBREG1	0x39  /* Baseband Registers */
#घोषणा BIT_RXDECINV	BIT(2)

#घोषणा REG_BBREG2	0x3A  /* */
#घोषणा BBREG2_CCA_MODE_SHIFT	6
#घोषणा BBREG2_CCA_MODE_MASK	0xc0

#घोषणा REG_BBREG3	0x3B
#घोषणा REG_BBREG4	0x3C
#घोषणा REG_BBREG6	0x3E  /* */
#घोषणा REG_CCAEDTH	0x3F  /* Energy Detection Threshold */

/* MRF24J40 Long Address Registers */
#घोषणा REG_RFCON0	0x200  /* RF Control Registers */
#घोषणा RFCON0_CH_SHIFT	4
#घोषणा RFCON0_CH_MASK	0xf0
#घोषणा RFOPT_RECOMMEND	3

#घोषणा REG_RFCON1	0x201
#घोषणा REG_RFCON2	0x202
#घोषणा REG_RFCON3	0x203

#घोषणा TXPWRL_MASK	0xc0
#घोषणा TXPWRL_SHIFT	6
#घोषणा TXPWRL_30	0x3
#घोषणा TXPWRL_20	0x2
#घोषणा TXPWRL_10	0x1
#घोषणा TXPWRL_0	0x0

#घोषणा TXPWRS_MASK	0x38
#घोषणा TXPWRS_SHIFT	3
#घोषणा TXPWRS_6_3	0x7
#घोषणा TXPWRS_4_9	0x6
#घोषणा TXPWRS_3_7	0x5
#घोषणा TXPWRS_2_8	0x4
#घोषणा TXPWRS_1_9	0x3
#घोषणा TXPWRS_1_2	0x2
#घोषणा TXPWRS_0_5	0x1
#घोषणा TXPWRS_0	0x0

#घोषणा REG_RFCON5	0x205
#घोषणा REG_RFCON6	0x206
#घोषणा REG_RFCON7	0x207
#घोषणा REG_RFCON8	0x208
#घोषणा REG_SLPCAL0	0x209
#घोषणा REG_SLPCAL1	0x20A
#घोषणा REG_SLPCAL2	0x20B
#घोषणा REG_RFSTATE	0x20F
#घोषणा REG_RSSI	0x210
#घोषणा REG_SLPCON0	0x211  /* Sleep Clock Control Registers */
#घोषणा BIT_INTEDGE	BIT(1)

#घोषणा REG_SLPCON1	0x220
#घोषणा REG_WAKETIMEL	0x222  /* Wake-up Time Match Value Low */
#घोषणा REG_WAKETIMEH	0x223  /* Wake-up Time Match Value High */
#घोषणा REG_REMCNTL	0x224
#घोषणा REG_REMCNTH	0x225
#घोषणा REG_MAINCNT0	0x226
#घोषणा REG_MAINCNT1	0x227
#घोषणा REG_MAINCNT2	0x228
#घोषणा REG_MAINCNT3	0x229
#घोषणा REG_TESTMODE	0x22F  /* Test mode */
#घोषणा REG_ASSOEAR0	0x230
#घोषणा REG_ASSOEAR1	0x231
#घोषणा REG_ASSOEAR2	0x232
#घोषणा REG_ASSOEAR3	0x233
#घोषणा REG_ASSOEAR4	0x234
#घोषणा REG_ASSOEAR5	0x235
#घोषणा REG_ASSOEAR6	0x236
#घोषणा REG_ASSOEAR7	0x237
#घोषणा REG_ASSOSAR0	0x238
#घोषणा REG_ASSOSAR1	0x239
#घोषणा REG_UNONCE0	0x240
#घोषणा REG_UNONCE1	0x241
#घोषणा REG_UNONCE2	0x242
#घोषणा REG_UNONCE3	0x243
#घोषणा REG_UNONCE4	0x244
#घोषणा REG_UNONCE5	0x245
#घोषणा REG_UNONCE6	0x246
#घोषणा REG_UNONCE7	0x247
#घोषणा REG_UNONCE8	0x248
#घोषणा REG_UNONCE9	0x249
#घोषणा REG_UNONCE10	0x24A
#घोषणा REG_UNONCE11	0x24B
#घोषणा REG_UNONCE12	0x24C
#घोषणा REG_RX_FIFO	0x300  /* Receive FIFO */

/* Device configuration: Only channels 11-26 on page 0 are supported. */
#घोषणा MRF24J40_CHAN_MIN 11
#घोषणा MRF24J40_CHAN_MAX 26
#घोषणा CHANNEL_MASK (((u32)1 << (MRF24J40_CHAN_MAX + 1)) \
		      - ((u32)1 << MRF24J40_CHAN_MIN))

#घोषणा TX_FIFO_SIZE 128 /* From datasheet */
#घोषणा RX_FIFO_SIZE 144 /* From datasheet */
#घोषणा SET_CHANNEL_DELAY_US 192 /* From datasheet */

क्रमागत mrf24j40_modules अणु MRF24J40, MRF24J40MA, MRF24J40MC पूर्ण;

/* Device Private Data */
काष्ठा mrf24j40 अणु
	काष्ठा spi_device *spi;
	काष्ठा ieee802154_hw *hw;

	काष्ठा regmap *regmap_लघु;
	काष्ठा regmap *regmap_दीर्घ;

	/* क्रम writing txfअगरo */
	काष्ठा spi_message tx_msg;
	u8 tx_hdr_buf[2];
	काष्ठा spi_transfer tx_hdr_trx;
	u8 tx_len_buf[2];
	काष्ठा spi_transfer tx_len_trx;
	काष्ठा spi_transfer tx_buf_trx;
	काष्ठा sk_buff *tx_skb;

	/* post transmit message to send frame out  */
	काष्ठा spi_message tx_post_msg;
	u8 tx_post_buf[2];
	काष्ठा spi_transfer tx_post_trx;

	/* क्रम protect/unprotect/पढ़ो length rxfअगरo */
	काष्ठा spi_message rx_msg;
	u8 rx_buf[3];
	काष्ठा spi_transfer rx_trx;

	/* receive handling */
	काष्ठा spi_message rx_buf_msg;
	u8 rx_addr_buf[2];
	काष्ठा spi_transfer rx_addr_trx;
	u8 rx_lqi_buf[2];
	काष्ठा spi_transfer rx_lqi_trx;
	u8 rx_fअगरo_buf[RX_FIFO_SIZE];
	काष्ठा spi_transfer rx_fअगरo_buf_trx;

	/* isr handling क्रम पढ़ोing पूर्णांकstat */
	काष्ठा spi_message irq_msg;
	u8 irq_buf[2];
	काष्ठा spi_transfer irq_trx;
पूर्ण;

/* regmap inक्रमmation क्रम लघु address रेजिस्टर access */
#घोषणा MRF24J40_SHORT_WRITE	0x01
#घोषणा MRF24J40_SHORT_READ	0x00
#घोषणा MRF24J40_SHORT_NUMREGS	0x3F

/* regmap inक्रमmation क्रम दीर्घ address रेजिस्टर access */
#घोषणा MRF24J40_LONG_ACCESS	0x80
#घोषणा MRF24J40_LONG_NUMREGS	0x38F

/* Read/Write SPI Commands क्रम Short and Long Address रेजिस्टरs. */
#घोषणा MRF24J40_READSHORT(reg) ((reg) << 1)
#घोषणा MRF24J40_WRITESHORT(reg) ((reg) << 1 | 1)
#घोषणा MRF24J40_READLONG(reg) (1 << 15 | (reg) << 5)
#घोषणा MRF24J40_WRITELONG(reg) (1 << 15 | (reg) << 5 | 1 << 4)

/* The datasheet indicates the theoretical maximum क्रम SCK to be 10MHz */
#घोषणा MAX_SPI_SPEED_HZ 10000000

#घोषणा prपूर्णांकdev(X) (&X->spi->dev)

अटल bool
mrf24j40_लघु_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_RXMCR:
	हाल REG_PANIDL:
	हाल REG_PANIDH:
	हाल REG_SADRL:
	हाल REG_SADRH:
	हाल REG_EADR0:
	हाल REG_EADR1:
	हाल REG_EADR2:
	हाल REG_EADR3:
	हाल REG_EADR4:
	हाल REG_EADR5:
	हाल REG_EADR6:
	हाल REG_EADR7:
	हाल REG_RXFLUSH:
	हाल REG_ORDER:
	हाल REG_TXMCR:
	हाल REG_ACKTMOUT:
	हाल REG_ESLOTG1:
	हाल REG_SYMTICKL:
	हाल REG_SYMTICKH:
	हाल REG_PACON0:
	हाल REG_PACON1:
	हाल REG_PACON2:
	हाल REG_TXBCON0:
	हाल REG_TXNCON:
	हाल REG_TXG1CON:
	हाल REG_TXG2CON:
	हाल REG_ESLOTG23:
	हाल REG_ESLOTG45:
	हाल REG_ESLOTG67:
	हाल REG_TXPEND:
	हाल REG_WAKECON:
	हाल REG_FROMOFFSET:
	हाल REG_TXBCON1:
	हाल REG_GATECLK:
	हाल REG_TXTIME:
	हाल REG_HSYMTMRL:
	हाल REG_HSYMTMRH:
	हाल REG_SOFTRST:
	हाल REG_SECCON0:
	हाल REG_SECCON1:
	हाल REG_TXSTBL:
	हाल REG_RXSR:
	हाल REG_INTCON:
	हाल REG_TRISGPIO:
	हाल REG_GPIO:
	हाल REG_RFCTL:
	हाल REG_SECCR2:
	हाल REG_SLPACK:
	हाल REG_BBREG0:
	हाल REG_BBREG1:
	हाल REG_BBREG2:
	हाल REG_BBREG3:
	हाल REG_BBREG4:
	हाल REG_BBREG6:
	हाल REG_CCAEDTH:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
mrf24j40_लघु_reg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	bool rc;

	/* all ग_लिखोable are also पढ़ोable */
	rc = mrf24j40_लघु_reg_ग_लिखोable(dev, reg);
	अगर (rc)
		वापस rc;

	/* पढ़ोonly regs */
	चयन (reg) अणु
	हाल REG_TXSTAT:
	हाल REG_INTSTAT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
mrf24j40_लघु_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* can be changed during runसमय */
	चयन (reg) अणु
	हाल REG_TXSTAT:
	हाल REG_INTSTAT:
	हाल REG_RXFLUSH:
	हाल REG_TXNCON:
	हाल REG_SOFTRST:
	हाल REG_RFCTL:
	हाल REG_TXBCON0:
	हाल REG_TXG1CON:
	हाल REG_TXG2CON:
	हाल REG_TXBCON1:
	हाल REG_SECCON0:
	हाल REG_RXSR:
	हाल REG_SLPACK:
	हाल REG_SECCR2:
	हाल REG_BBREG6:
	/* use them in spi_async and regmap so it's अस्थिर */
	हाल REG_BBREG1:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
mrf24j40_लघु_reg_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* करोn't clear irq line on पढ़ो */
	चयन (reg) अणु
	हाल REG_INTSTAT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config mrf24j40_लघु_regmap = अणु
	.name = "mrf24j40_short",
	.reg_bits = 7,
	.val_bits = 8,
	.pad_bits = 1,
	.ग_लिखो_flag_mask = MRF24J40_SHORT_WRITE,
	.पढ़ो_flag_mask = MRF24J40_SHORT_READ,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = MRF24J40_SHORT_NUMREGS,
	.ग_लिखोable_reg = mrf24j40_लघु_reg_ग_लिखोable,
	.पढ़ोable_reg = mrf24j40_लघु_reg_पढ़ोable,
	.अस्थिर_reg = mrf24j40_लघु_reg_अस्थिर,
	.precious_reg = mrf24j40_लघु_reg_precious,
पूर्ण;

अटल bool
mrf24j40_दीर्घ_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_RFCON0:
	हाल REG_RFCON1:
	हाल REG_RFCON2:
	हाल REG_RFCON3:
	हाल REG_RFCON5:
	हाल REG_RFCON6:
	हाल REG_RFCON7:
	हाल REG_RFCON8:
	हाल REG_SLPCAL2:
	हाल REG_SLPCON0:
	हाल REG_SLPCON1:
	हाल REG_WAKETIMEL:
	हाल REG_WAKETIMEH:
	हाल REG_REMCNTL:
	हाल REG_REMCNTH:
	हाल REG_MAINCNT0:
	हाल REG_MAINCNT1:
	हाल REG_MAINCNT2:
	हाल REG_MAINCNT3:
	हाल REG_TESTMODE:
	हाल REG_ASSOEAR0:
	हाल REG_ASSOEAR1:
	हाल REG_ASSOEAR2:
	हाल REG_ASSOEAR3:
	हाल REG_ASSOEAR4:
	हाल REG_ASSOEAR5:
	हाल REG_ASSOEAR6:
	हाल REG_ASSOEAR7:
	हाल REG_ASSOSAR0:
	हाल REG_ASSOSAR1:
	हाल REG_UNONCE0:
	हाल REG_UNONCE1:
	हाल REG_UNONCE2:
	हाल REG_UNONCE3:
	हाल REG_UNONCE4:
	हाल REG_UNONCE5:
	हाल REG_UNONCE6:
	हाल REG_UNONCE7:
	हाल REG_UNONCE8:
	हाल REG_UNONCE9:
	हाल REG_UNONCE10:
	हाल REG_UNONCE11:
	हाल REG_UNONCE12:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
mrf24j40_दीर्घ_reg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	bool rc;

	/* all ग_लिखोable are also पढ़ोable */
	rc = mrf24j40_दीर्घ_reg_ग_लिखोable(dev, reg);
	अगर (rc)
		वापस rc;

	/* पढ़ोonly regs */
	चयन (reg) अणु
	हाल REG_SLPCAL0:
	हाल REG_SLPCAL1:
	हाल REG_RFSTATE:
	हाल REG_RSSI:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
mrf24j40_दीर्घ_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* can be changed during runसमय */
	चयन (reg) अणु
	हाल REG_SLPCAL0:
	हाल REG_SLPCAL1:
	हाल REG_SLPCAL2:
	हाल REG_RFSTATE:
	हाल REG_RSSI:
	हाल REG_MAINCNT3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config mrf24j40_दीर्घ_regmap = अणु
	.name = "mrf24j40_long",
	.reg_bits = 11,
	.val_bits = 8,
	.pad_bits = 5,
	.ग_लिखो_flag_mask = MRF24J40_LONG_ACCESS,
	.पढ़ो_flag_mask = MRF24J40_LONG_ACCESS,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = MRF24J40_LONG_NUMREGS,
	.ग_लिखोable_reg = mrf24j40_दीर्घ_reg_ग_लिखोable,
	.पढ़ोable_reg = mrf24j40_दीर्घ_reg_पढ़ोable,
	.अस्थिर_reg = mrf24j40_दीर्घ_reg_अस्थिर,
पूर्ण;

अटल पूर्णांक mrf24j40_दीर्घ_regmap_ग_लिखो(व्योम *context, स्थिर व्योम *data,
				      माप_प्रकार count)
अणु
	काष्ठा spi_device *spi = context;
	u8 buf[3];

	अगर (count > 3)
		वापस -EINVAL;

	/* regmap supports पढ़ो/ग_लिखो mask only in frist byte
	 * दीर्घ ग_लिखो access need to set the 12th bit, so we
	 * make special handling क्रम ग_लिखो.
	 */
	स_नकल(buf, data, count);
	buf[1] |= (1 << 4);

	वापस spi_ग_लिखो(spi, buf, count);
पूर्ण

अटल पूर्णांक
mrf24j40_दीर्घ_regmap_पढ़ो(व्योम *context, स्थिर व्योम *reg, माप_प्रकार reg_size,
			  व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा spi_device *spi = context;

	वापस spi_ग_लिखो_then_पढ़ो(spi, reg, reg_size, val, val_size);
पूर्ण

अटल स्थिर काष्ठा regmap_bus mrf24j40_दीर्घ_regmap_bus = अणु
	.ग_लिखो = mrf24j40_दीर्घ_regmap_ग_लिखो,
	.पढ़ो = mrf24j40_दीर्घ_regmap_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
पूर्ण;

अटल व्योम ग_लिखो_tx_buf_complete(व्योम *context)
अणु
	काष्ठा mrf24j40 *devrec = context;
	__le16 fc = ieee802154_get_fc_from_skb(devrec->tx_skb);
	u8 val = BIT_TXNTRIG;
	पूर्णांक ret;

	अगर (ieee802154_is_secen(fc))
		val |= BIT_TXNSECEN;

	अगर (ieee802154_is_ackreq(fc))
		val |= BIT_TXNACKREQ;

	devrec->tx_post_msg.complete = शून्य;
	devrec->tx_post_buf[0] = MRF24J40_WRITESHORT(REG_TXNCON);
	devrec->tx_post_buf[1] = val;

	ret = spi_async(devrec->spi, &devrec->tx_post_msg);
	अगर (ret)
		dev_err(prपूर्णांकdev(devrec), "SPI write Failed for transmit buf\n");
पूर्ण

/* This function relies on an unकरोcumented ग_लिखो method. Once a ग_लिखो command
   and address is set, as many bytes of data as desired can be घड़ीed पूर्णांकo
   the device. The datasheet only shows setting one byte at a समय. */
अटल पूर्णांक ग_लिखो_tx_buf(काष्ठा mrf24j40 *devrec, u16 reg,
			स्थिर u8 *data, माप_प्रकार length)
अणु
	u16 cmd;
	पूर्णांक ret;

	/* Range check the length. 2 bytes are used क्रम the length fields.*/
	अगर (length > TX_FIFO_SIZE-2) अणु
		dev_err(prपूर्णांकdev(devrec), "write_tx_buf() was passed too large a buffer. Performing short write.\n");
		length = TX_FIFO_SIZE-2;
	पूर्ण

	cmd = MRF24J40_WRITELONG(reg);
	devrec->tx_hdr_buf[0] = cmd >> 8 & 0xff;
	devrec->tx_hdr_buf[1] = cmd & 0xff;
	devrec->tx_len_buf[0] = 0x0; /* Header Length. Set to 0 क्रम now. TODO */
	devrec->tx_len_buf[1] = length; /* Total length */
	devrec->tx_buf_trx.tx_buf = data;
	devrec->tx_buf_trx.len = length;

	ret = spi_async(devrec->spi, &devrec->tx_msg);
	अगर (ret)
		dev_err(prपूर्णांकdev(devrec), "SPI write Failed for TX buf\n");

	वापस ret;
पूर्ण

अटल पूर्णांक mrf24j40_tx(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा mrf24j40 *devrec = hw->priv;

	dev_dbg(prपूर्णांकdev(devrec), "tx packet of %d bytes\n", skb->len);
	devrec->tx_skb = skb;

	वापस ग_लिखो_tx_buf(devrec, 0x000, skb->data, skb->len);
पूर्ण

अटल पूर्णांक mrf24j40_ed(काष्ठा ieee802154_hw *hw, u8 *level)
अणु
	/* TODO: */
	pr_warn("mrf24j40: ed not implemented\n");
	*level = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक mrf24j40_start(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा mrf24j40 *devrec = hw->priv;

	dev_dbg(prपूर्णांकdev(devrec), "start\n");

	/* Clear TXNIE and RXIE. Enable पूर्णांकerrupts */
	वापस regmap_update_bits(devrec->regmap_लघु, REG_INTCON,
				  BIT_TXNIE | BIT_RXIE | BIT_SECIE, 0);
पूर्ण

अटल व्योम mrf24j40_stop(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा mrf24j40 *devrec = hw->priv;

	dev_dbg(prपूर्णांकdev(devrec), "stop\n");

	/* Set TXNIE and RXIE. Disable Interrupts */
	regmap_update_bits(devrec->regmap_लघु, REG_INTCON,
			   BIT_TXNIE | BIT_RXIE, BIT_TXNIE | BIT_RXIE);
पूर्ण

अटल पूर्णांक mrf24j40_set_channel(काष्ठा ieee802154_hw *hw, u8 page, u8 channel)
अणु
	काष्ठा mrf24j40 *devrec = hw->priv;
	u8 val;
	पूर्णांक ret;

	dev_dbg(prपूर्णांकdev(devrec), "Set Channel %d\n", channel);

	WARN_ON(page != 0);
	WARN_ON(channel < MRF24J40_CHAN_MIN);
	WARN_ON(channel > MRF24J40_CHAN_MAX);

	/* Set Channel TODO */
	val = (channel - 11) << RFCON0_CH_SHIFT | RFOPT_RECOMMEND;
	ret = regmap_update_bits(devrec->regmap_दीर्घ, REG_RFCON0,
				 RFCON0_CH_MASK, val);
	अगर (ret)
		वापस ret;

	/* RF Reset */
	ret = regmap_update_bits(devrec->regmap_लघु, REG_RFCTL, BIT_RFRST,
				 BIT_RFRST);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(devrec->regmap_लघु, REG_RFCTL, BIT_RFRST, 0);
	अगर (!ret)
		udelay(SET_CHANNEL_DELAY_US); /* per datasheet */

	वापस ret;
पूर्ण

अटल पूर्णांक mrf24j40_filter(काष्ठा ieee802154_hw *hw,
			   काष्ठा ieee802154_hw_addr_filt *filt,
			   अचिन्हित दीर्घ changed)
अणु
	काष्ठा mrf24j40 *devrec = hw->priv;

	dev_dbg(prपूर्णांकdev(devrec), "filter\n");

	अगर (changed & IEEE802154_AFILT_SADDR_CHANGED) अणु
		/* Short Addr */
		u8 addrh, addrl;

		addrh = le16_to_cpu(filt->लघु_addr) >> 8 & 0xff;
		addrl = le16_to_cpu(filt->लघु_addr) & 0xff;

		regmap_ग_लिखो(devrec->regmap_लघु, REG_SADRH, addrh);
		regmap_ग_लिखो(devrec->regmap_लघु, REG_SADRL, addrl);
		dev_dbg(prपूर्णांकdev(devrec),
			"Set short addr to %04hx\n", filt->लघु_addr);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_IEEEADDR_CHANGED) अणु
		/* Device Address */
		u8 i, addr[8];

		स_नकल(addr, &filt->ieee_addr, 8);
		क्रम (i = 0; i < 8; i++)
			regmap_ग_लिखो(devrec->regmap_लघु, REG_EADR0 + i,
				     addr[i]);

#अगर_घोषित DEBUG
		pr_debug("Set long addr to: ");
		क्रम (i = 0; i < 8; i++)
			pr_debug("%02hhx ", addr[7 - i]);
		pr_debug("\n");
#पूर्ण_अगर
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANID_CHANGED) अणु
		/* PAN ID */
		u8 panidl, panidh;

		panidh = le16_to_cpu(filt->pan_id) >> 8 & 0xff;
		panidl = le16_to_cpu(filt->pan_id) & 0xff;
		regmap_ग_लिखो(devrec->regmap_लघु, REG_PANIDH, panidh);
		regmap_ग_लिखो(devrec->regmap_लघु, REG_PANIDL, panidl);

		dev_dbg(prपूर्णांकdev(devrec), "Set PANID to %04hx\n", filt->pan_id);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANC_CHANGED) अणु
		/* Pan Coordinator */
		u8 val;
		पूर्णांक ret;

		अगर (filt->pan_coord)
			val = BIT_PANCOORD;
		अन्यथा
			val = 0;
		ret = regmap_update_bits(devrec->regmap_लघु, REG_RXMCR,
					 BIT_PANCOORD, val);
		अगर (ret)
			वापस ret;

		/* REG_SLOTTED is मुख्यtained as शेष (unslotted/CSMA-CA).
		 * REG_ORDER is मुख्यtained as शेष (no beacon/superframe).
		 */

		dev_dbg(prपूर्णांकdev(devrec), "Set Pan Coord to %s\n",
			filt->pan_coord ? "on" : "off");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mrf24j40_handle_rx_पढ़ो_buf_unlock(काष्ठा mrf24j40 *devrec)
अणु
	पूर्णांक ret;

	/* Turn back on reception of packets off the air. */
	devrec->rx_msg.complete = शून्य;
	devrec->rx_buf[0] = MRF24J40_WRITESHORT(REG_BBREG1);
	devrec->rx_buf[1] = 0x00; /* CLR RXDECINV */
	ret = spi_async(devrec->spi, &devrec->rx_msg);
	अगर (ret)
		dev_err(prपूर्णांकdev(devrec), "failed to unlock rx buffer\n");
पूर्ण

अटल व्योम mrf24j40_handle_rx_पढ़ो_buf_complete(व्योम *context)
अणु
	काष्ठा mrf24j40 *devrec = context;
	u8 len = devrec->rx_buf[2];
	u8 rx_local_buf[RX_FIFO_SIZE];
	काष्ठा sk_buff *skb;

	स_नकल(rx_local_buf, devrec->rx_fअगरo_buf, len);
	mrf24j40_handle_rx_पढ़ो_buf_unlock(devrec);

	skb = dev_alloc_skb(IEEE802154_MTU);
	अगर (!skb) अणु
		dev_err(prपूर्णांकdev(devrec), "failed to allocate skb\n");
		वापस;
	पूर्ण

	skb_put_data(skb, rx_local_buf, len);
	ieee802154_rx_irqsafe(devrec->hw, skb, 0);

#अगर_घोषित DEBUG
	 prपूर्णांक_hex_dump(KERN_DEBUG, "mrf24j40 rx: ", DUMP_PREFIX_OFFSET, 16, 1,
			rx_local_buf, len, 0);
	 pr_debug("mrf24j40 rx: lqi: %02hhx rssi: %02hhx\n",
		  devrec->rx_lqi_buf[0], devrec->rx_lqi_buf[1]);
#पूर्ण_अगर
पूर्ण

अटल व्योम mrf24j40_handle_rx_पढ़ो_buf(व्योम *context)
अणु
	काष्ठा mrf24j40 *devrec = context;
	u16 cmd;
	पूर्णांक ret;

	/* अगर length is invalid पढ़ो the full MTU */
	अगर (!ieee802154_is_valid_psdu_len(devrec->rx_buf[2]))
		devrec->rx_buf[2] = IEEE802154_MTU;

	cmd = MRF24J40_READLONG(REG_RX_FIFO + 1);
	devrec->rx_addr_buf[0] = cmd >> 8 & 0xff;
	devrec->rx_addr_buf[1] = cmd & 0xff;
	devrec->rx_fअगरo_buf_trx.len = devrec->rx_buf[2];
	ret = spi_async(devrec->spi, &devrec->rx_buf_msg);
	अगर (ret) अणु
		dev_err(prपूर्णांकdev(devrec), "failed to read rx buffer\n");
		mrf24j40_handle_rx_पढ़ो_buf_unlock(devrec);
	पूर्ण
पूर्ण

अटल व्योम mrf24j40_handle_rx_पढ़ो_len(व्योम *context)
अणु
	काष्ठा mrf24j40 *devrec = context;
	u16 cmd;
	पूर्णांक ret;

	/* पढ़ो the length of received frame */
	devrec->rx_msg.complete = mrf24j40_handle_rx_पढ़ो_buf;
	devrec->rx_trx.len = 3;
	cmd = MRF24J40_READLONG(REG_RX_FIFO);
	devrec->rx_buf[0] = cmd >> 8 & 0xff;
	devrec->rx_buf[1] = cmd & 0xff;

	ret = spi_async(devrec->spi, &devrec->rx_msg);
	अगर (ret) अणु
		dev_err(prपूर्णांकdev(devrec), "failed to read rx buffer length\n");
		mrf24j40_handle_rx_पढ़ो_buf_unlock(devrec);
	पूर्ण
पूर्ण

अटल पूर्णांक mrf24j40_handle_rx(काष्ठा mrf24j40 *devrec)
अणु
	/* Turn off reception of packets off the air. This prevents the
	 * device from overwriting the buffer जबतक we're पढ़ोing it.
	 */
	devrec->rx_msg.complete = mrf24j40_handle_rx_पढ़ो_len;
	devrec->rx_trx.len = 2;
	devrec->rx_buf[0] = MRF24J40_WRITESHORT(REG_BBREG1);
	devrec->rx_buf[1] = BIT_RXDECINV; /* SET RXDECINV */

	वापस spi_async(devrec->spi, &devrec->rx_msg);
पूर्ण

अटल पूर्णांक
mrf24j40_csma_params(काष्ठा ieee802154_hw *hw, u8 min_be, u8 max_be,
		     u8 retries)
अणु
	काष्ठा mrf24j40 *devrec = hw->priv;
	u8 val;

	/* min_be */
	val = min_be << TXMCR_MIN_BE_SHIFT;
	/* csma backoffs */
	val |= retries << TXMCR_CSMA_RETRIES_SHIFT;

	वापस regmap_update_bits(devrec->regmap_लघु, REG_TXMCR,
				  TXMCR_MIN_BE_MASK | TXMCR_CSMA_RETRIES_MASK,
				  val);
पूर्ण

अटल पूर्णांक mrf24j40_set_cca_mode(काष्ठा ieee802154_hw *hw,
				 स्थिर काष्ठा wpan_phy_cca *cca)
अणु
	काष्ठा mrf24j40 *devrec = hw->priv;
	u8 val;

	/* mapping 802.15.4 to driver spec */
	चयन (cca->mode) अणु
	हाल NL802154_CCA_ENERGY:
		val = 2;
		अवरोध;
	हाल NL802154_CCA_CARRIER:
		val = 1;
		अवरोध;
	हाल NL802154_CCA_ENERGY_CARRIER:
		चयन (cca->opt) अणु
		हाल NL802154_CCA_OPT_ENERGY_CARRIER_AND:
			val = 3;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(devrec->regmap_लघु, REG_BBREG2,
				  BBREG2_CCA_MODE_MASK,
				  val << BBREG2_CCA_MODE_SHIFT);
पूर्ण

/* array क्रम representing ed levels */
अटल स्थिर s32 mrf24j40_ed_levels[] = अणु
	-9000, -8900, -8800, -8700, -8600, -8500, -8400, -8300, -8200, -8100,
	-8000, -7900, -7800, -7700, -7600, -7500, -7400, -7300, -7200, -7100,
	-7000, -6900, -6800, -6700, -6600, -6500, -6400, -6300, -6200, -6100,
	-6000, -5900, -5800, -5700, -5600, -5500, -5400, -5300, -5200, -5100,
	-5000, -4900, -4800, -4700, -4600, -4500, -4400, -4300, -4200, -4100,
	-4000, -3900, -3800, -3700, -3600, -3500
पूर्ण;

/* map ed levels to रेजिस्टर value */
अटल स्थिर s32 mrf24j40_ed_levels_map[][2] = अणु
	अणु -9000, 0 पूर्ण, अणु -8900, 1 पूर्ण, अणु -8800, 2 पूर्ण, अणु -8700, 5 पूर्ण, अणु -8600, 9 पूर्ण,
	अणु -8500, 13 पूर्ण, अणु -8400, 18 पूर्ण, अणु -8300, 23 पूर्ण, अणु -8200, 27 पूर्ण,
	अणु -8100, 32 पूर्ण, अणु -8000, 37 पूर्ण, अणु -7900, 43 पूर्ण, अणु -7800, 48 पूर्ण,
	अणु -7700, 53 पूर्ण, अणु -7600, 58 पूर्ण, अणु -7500, 63 पूर्ण, अणु -7400, 68 पूर्ण,
	अणु -7300, 73 पूर्ण, अणु -7200, 78 पूर्ण, अणु -7100, 83 पूर्ण, अणु -7000, 89 पूर्ण,
	अणु -6900, 95 पूर्ण, अणु -6800, 100 पूर्ण, अणु -6700, 107 पूर्ण, अणु -6600, 111 पूर्ण,
	अणु -6500, 117 पूर्ण, अणु -6400, 121 पूर्ण, अणु -6300, 125 पूर्ण, अणु -6200, 129 पूर्ण,
	अणु -6100, 133 पूर्ण,	अणु -6000, 138 पूर्ण, अणु -5900, 143 पूर्ण, अणु -5800, 148 पूर्ण,
	अणु -5700, 153 पूर्ण, अणु -5600, 159 पूर्ण,	अणु -5500, 165 पूर्ण, अणु -5400, 170 पूर्ण,
	अणु -5300, 176 पूर्ण, अणु -5200, 183 पूर्ण, अणु -5100, 188 पूर्ण, अणु -5000, 193 पूर्ण,
	अणु -4900, 198 पूर्ण, अणु -4800, 203 पूर्ण, अणु -4700, 207 पूर्ण, अणु -4600, 212 पूर्ण,
	अणु -4500, 216 पूर्ण, अणु -4400, 221 पूर्ण, अणु -4300, 225 पूर्ण, अणु -4200, 228 पूर्ण,
	अणु -4100, 233 पूर्ण, अणु -4000, 239 पूर्ण, अणु -3900, 245 पूर्ण, अणु -3800, 250 पूर्ण,
	अणु -3700, 253 पूर्ण, अणु -3600, 254 पूर्ण, अणु -3500, 255 पूर्ण,
पूर्ण;

अटल पूर्णांक mrf24j40_set_cca_ed_level(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा mrf24j40 *devrec = hw->priv;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mrf24j40_ed_levels_map); i++) अणु
		अगर (mrf24j40_ed_levels_map[i][0] == mbm)
			वापस regmap_ग_लिखो(devrec->regmap_लघु, REG_CCAEDTH,
					    mrf24j40_ed_levels_map[i][1]);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर s32 mrf24j40ma_घातers[] = अणु
	0, -50, -120, -190, -280, -370, -490, -630, -1000, -1050, -1120, -1190,
	-1280, -1370, -1490, -1630, -2000, -2050, -2120, -2190, -2280, -2370,
	-2490, -2630, -3000, -3050, -3120, -3190, -3280, -3370, -3490, -3630,
पूर्ण;

अटल पूर्णांक mrf24j40_set_txघातer(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा mrf24j40 *devrec = hw->priv;
	s32 small_scale;
	u8 val;

	अगर (0 >= mbm && mbm > -1000) अणु
		val = TXPWRL_0 << TXPWRL_SHIFT;
		small_scale = mbm;
	पूर्ण अन्यथा अगर (-1000 >= mbm && mbm > -2000) अणु
		val = TXPWRL_10 << TXPWRL_SHIFT;
		small_scale = mbm + 1000;
	पूर्ण अन्यथा अगर (-2000 >= mbm && mbm > -3000) अणु
		val = TXPWRL_20 << TXPWRL_SHIFT;
		small_scale = mbm + 2000;
	पूर्ण अन्यथा अगर (-3000 >= mbm && mbm > -4000) अणु
		val = TXPWRL_30 << TXPWRL_SHIFT;
		small_scale = mbm + 3000;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	चयन (small_scale) अणु
	हाल 0:
		val |= (TXPWRS_0 << TXPWRS_SHIFT);
		अवरोध;
	हाल -50:
		val |= (TXPWRS_0_5 << TXPWRS_SHIFT);
		अवरोध;
	हाल -120:
		val |= (TXPWRS_1_2 << TXPWRS_SHIFT);
		अवरोध;
	हाल -190:
		val |= (TXPWRS_1_9 << TXPWRS_SHIFT);
		अवरोध;
	हाल -280:
		val |= (TXPWRS_2_8 << TXPWRS_SHIFT);
		अवरोध;
	हाल -370:
		val |= (TXPWRS_3_7 << TXPWRS_SHIFT);
		अवरोध;
	हाल -490:
		val |= (TXPWRS_4_9 << TXPWRS_SHIFT);
		अवरोध;
	हाल -630:
		val |= (TXPWRS_6_3 << TXPWRS_SHIFT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(devrec->regmap_दीर्घ, REG_RFCON3,
				  TXPWRL_MASK | TXPWRS_MASK, val);
पूर्ण

अटल पूर्णांक mrf24j40_set_promiscuous_mode(काष्ठा ieee802154_hw *hw, bool on)
अणु
	काष्ठा mrf24j40 *devrec = hw->priv;
	पूर्णांक ret;

	अगर (on) अणु
		/* set PROMI, ERRPKT and NOACKRSP */
		ret = regmap_update_bits(devrec->regmap_लघु, REG_RXMCR,
					 BIT_PROMI | BIT_ERRPKT | BIT_NOACKRSP,
					 BIT_PROMI | BIT_ERRPKT | BIT_NOACKRSP);
	पूर्ण अन्यथा अणु
		/* clear PROMI, ERRPKT and NOACKRSP */
		ret = regmap_update_bits(devrec->regmap_लघु, REG_RXMCR,
					 BIT_PROMI | BIT_ERRPKT | BIT_NOACKRSP,
					 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ieee802154_ops mrf24j40_ops = अणु
	.owner = THIS_MODULE,
	.xmit_async = mrf24j40_tx,
	.ed = mrf24j40_ed,
	.start = mrf24j40_start,
	.stop = mrf24j40_stop,
	.set_channel = mrf24j40_set_channel,
	.set_hw_addr_filt = mrf24j40_filter,
	.set_csma_params = mrf24j40_csma_params,
	.set_cca_mode = mrf24j40_set_cca_mode,
	.set_cca_ed_level = mrf24j40_set_cca_ed_level,
	.set_txघातer = mrf24j40_set_txघातer,
	.set_promiscuous_mode = mrf24j40_set_promiscuous_mode,
पूर्ण;

अटल व्योम mrf24j40_पूर्णांकstat_complete(व्योम *context)
अणु
	काष्ठा mrf24j40 *devrec = context;
	u8 पूर्णांकstat = devrec->irq_buf[1];

	enable_irq(devrec->spi->irq);

	/* Ignore Rx security decryption */
	अगर (पूर्णांकstat & BIT_SECIF)
		regmap_ग_लिखो_async(devrec->regmap_लघु, REG_SECCON0,
				   BIT_SECIGNORE);

	/* Check क्रम TX complete */
	अगर (पूर्णांकstat & BIT_TXNIF)
		ieee802154_xmit_complete(devrec->hw, devrec->tx_skb, false);

	/* Check क्रम Rx */
	अगर (पूर्णांकstat & BIT_RXIF)
		mrf24j40_handle_rx(devrec);
पूर्ण

अटल irqवापस_t mrf24j40_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mrf24j40 *devrec = data;
	पूर्णांक ret;

	disable_irq_nosync(irq);

	devrec->irq_buf[0] = MRF24J40_READSHORT(REG_INTSTAT);
	devrec->irq_buf[1] = 0;

	/* Read the पूर्णांकerrupt status */
	ret = spi_async(devrec->spi, &devrec->irq_msg);
	अगर (ret) अणु
		enable_irq(irq);
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mrf24j40_hw_init(काष्ठा mrf24j40 *devrec)
अणु
	u32 irq_type;
	पूर्णांक ret;

	/* Initialize the device.
		From datasheet section 3.2: Initialization. */
	ret = regmap_ग_लिखो(devrec->regmap_लघु, REG_SOFTRST, 0x07);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_लघु, REG_PACON2, 0x98);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_लघु, REG_TXSTBL, 0x95);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_दीर्घ, REG_RFCON0, 0x03);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_दीर्घ, REG_RFCON1, 0x01);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_दीर्घ, REG_RFCON2, 0x80);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_दीर्घ, REG_RFCON6, 0x90);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_दीर्घ, REG_RFCON7, 0x80);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_दीर्घ, REG_RFCON8, 0x10);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_दीर्घ, REG_SLPCON1, 0x21);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_लघु, REG_BBREG2, 0x80);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_लघु, REG_CCAEDTH, 0x60);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_लघु, REG_BBREG6, 0x40);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_लघु, REG_RFCTL, 0x04);
	अगर (ret)
		जाओ err_ret;

	ret = regmap_ग_लिखो(devrec->regmap_लघु, REG_RFCTL, 0x0);
	अगर (ret)
		जाओ err_ret;

	udelay(192);

	/* Set RX Mode. RXMCR<1:0>: 0x0 normal, 0x1 promisc, 0x2 error */
	ret = regmap_update_bits(devrec->regmap_लघु, REG_RXMCR, 0x03, 0x00);
	अगर (ret)
		जाओ err_ret;

	अगर (spi_get_device_id(devrec->spi)->driver_data == MRF24J40MC) अणु
		/* Enable बाह्यal amplअगरier.
		 * From MRF24J40MC datasheet section 1.3: Operation.
		 */
		regmap_update_bits(devrec->regmap_दीर्घ, REG_TESTMODE, 0x07,
				   0x07);

		/* Set GPIO3 as output. */
		regmap_update_bits(devrec->regmap_लघु, REG_TRISGPIO, 0x08,
				   0x08);

		/* Set GPIO3 HIGH to enable U5 voltage regulator */
		regmap_update_bits(devrec->regmap_लघु, REG_GPIO, 0x08, 0x08);

		/* Reduce TX pwr to meet FCC requirements.
		 * From MRF24J40MC datasheet section 3.1.1
		 */
		regmap_ग_लिखो(devrec->regmap_दीर्घ, REG_RFCON3, 0x28);
	पूर्ण

	irq_type = irq_get_trigger_type(devrec->spi->irq);
	अगर (irq_type == IRQ_TYPE_EDGE_RISING ||
	    irq_type == IRQ_TYPE_EDGE_FALLING)
		dev_warn(&devrec->spi->dev,
			 "Using edge triggered irq's are not recommended, because it can cause races and result in a non-functional driver!\n");
	चयन (irq_type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_LEVEL_HIGH:
		/* set पूर्णांकerrupt polarity to rising */
		ret = regmap_update_bits(devrec->regmap_दीर्घ, REG_SLPCON0,
					 BIT_INTEDGE, BIT_INTEDGE);
		अगर (ret)
			जाओ err_ret;
		अवरोध;
	शेष:
		/* शेष is falling edge */
		अवरोध;
	पूर्ण

	वापस 0;

err_ret:
	वापस ret;
पूर्ण

अटल व्योम
mrf24j40_setup_tx_spi_messages(काष्ठा mrf24j40 *devrec)
अणु
	spi_message_init(&devrec->tx_msg);
	devrec->tx_msg.context = devrec;
	devrec->tx_msg.complete = ग_लिखो_tx_buf_complete;
	devrec->tx_hdr_trx.len = 2;
	devrec->tx_hdr_trx.tx_buf = devrec->tx_hdr_buf;
	spi_message_add_tail(&devrec->tx_hdr_trx, &devrec->tx_msg);
	devrec->tx_len_trx.len = 2;
	devrec->tx_len_trx.tx_buf = devrec->tx_len_buf;
	spi_message_add_tail(&devrec->tx_len_trx, &devrec->tx_msg);
	spi_message_add_tail(&devrec->tx_buf_trx, &devrec->tx_msg);

	spi_message_init(&devrec->tx_post_msg);
	devrec->tx_post_msg.context = devrec;
	devrec->tx_post_trx.len = 2;
	devrec->tx_post_trx.tx_buf = devrec->tx_post_buf;
	spi_message_add_tail(&devrec->tx_post_trx, &devrec->tx_post_msg);
पूर्ण

अटल व्योम
mrf24j40_setup_rx_spi_messages(काष्ठा mrf24j40 *devrec)
अणु
	spi_message_init(&devrec->rx_msg);
	devrec->rx_msg.context = devrec;
	devrec->rx_trx.len = 2;
	devrec->rx_trx.tx_buf = devrec->rx_buf;
	devrec->rx_trx.rx_buf = devrec->rx_buf;
	spi_message_add_tail(&devrec->rx_trx, &devrec->rx_msg);

	spi_message_init(&devrec->rx_buf_msg);
	devrec->rx_buf_msg.context = devrec;
	devrec->rx_buf_msg.complete = mrf24j40_handle_rx_पढ़ो_buf_complete;
	devrec->rx_addr_trx.len = 2;
	devrec->rx_addr_trx.tx_buf = devrec->rx_addr_buf;
	spi_message_add_tail(&devrec->rx_addr_trx, &devrec->rx_buf_msg);
	devrec->rx_fअगरo_buf_trx.rx_buf = devrec->rx_fअगरo_buf;
	spi_message_add_tail(&devrec->rx_fअगरo_buf_trx, &devrec->rx_buf_msg);
	devrec->rx_lqi_trx.len = 2;
	devrec->rx_lqi_trx.rx_buf = devrec->rx_lqi_buf;
	spi_message_add_tail(&devrec->rx_lqi_trx, &devrec->rx_buf_msg);
पूर्ण

अटल व्योम
mrf24j40_setup_irq_spi_messages(काष्ठा mrf24j40 *devrec)
अणु
	spi_message_init(&devrec->irq_msg);
	devrec->irq_msg.context = devrec;
	devrec->irq_msg.complete = mrf24j40_पूर्णांकstat_complete;
	devrec->irq_trx.len = 2;
	devrec->irq_trx.tx_buf = devrec->irq_buf;
	devrec->irq_trx.rx_buf = devrec->irq_buf;
	spi_message_add_tail(&devrec->irq_trx, &devrec->irq_msg);
पूर्ण

अटल व्योम  mrf24j40_phy_setup(काष्ठा mrf24j40 *devrec)
अणु
	ieee802154_अक्रमom_extended_addr(&devrec->hw->phy->perm_extended_addr);
	devrec->hw->phy->current_channel = 11;

	/* mrf24j40 supports max_minbe 0 - 3 */
	devrec->hw->phy->supported.max_minbe = 3;
	/* datasheet करोesn't say anything about max_be, but we have min_be
	 * So we assume the max_be शेष.
	 */
	devrec->hw->phy->supported.min_maxbe = 5;
	devrec->hw->phy->supported.max_maxbe = 5;

	devrec->hw->phy->cca.mode = NL802154_CCA_CARRIER;
	devrec->hw->phy->supported.cca_modes = BIT(NL802154_CCA_ENERGY) |
					       BIT(NL802154_CCA_CARRIER) |
					       BIT(NL802154_CCA_ENERGY_CARRIER);
	devrec->hw->phy->supported.cca_opts = BIT(NL802154_CCA_OPT_ENERGY_CARRIER_AND);

	devrec->hw->phy->cca_ed_level = -6900;
	devrec->hw->phy->supported.cca_ed_levels = mrf24j40_ed_levels;
	devrec->hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(mrf24j40_ed_levels);

	चयन (spi_get_device_id(devrec->spi)->driver_data) अणु
	हाल MRF24J40:
	हाल MRF24J40MA:
		devrec->hw->phy->supported.tx_घातers = mrf24j40ma_घातers;
		devrec->hw->phy->supported.tx_घातers_size = ARRAY_SIZE(mrf24j40ma_घातers);
		devrec->hw->phy->flags |= WPAN_PHY_FLAG_TXPOWER;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mrf24j40_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret = -ENOMEM, irq_type;
	काष्ठा ieee802154_hw *hw;
	काष्ठा mrf24j40 *devrec;

	dev_info(&spi->dev, "probe(). IRQ: %d\n", spi->irq);

	/* Register with the 802154 subप्रणाली */

	hw = ieee802154_alloc_hw(माप(*devrec), &mrf24j40_ops);
	अगर (!hw)
		जाओ err_ret;

	devrec = hw->priv;
	devrec->spi = spi;
	spi_set_drvdata(spi, devrec);
	devrec->hw = hw;
	devrec->hw->parent = &spi->dev;
	devrec->hw->phy->supported.channels[0] = CHANNEL_MASK;
	devrec->hw->flags = IEEE802154_HW_TX_OMIT_CKSUM | IEEE802154_HW_AFILT |
			    IEEE802154_HW_CSMA_PARAMS |
			    IEEE802154_HW_PROMISCUOUS;

	devrec->hw->phy->flags = WPAN_PHY_FLAG_CCA_MODE |
				 WPAN_PHY_FLAG_CCA_ED_LEVEL;

	mrf24j40_setup_tx_spi_messages(devrec);
	mrf24j40_setup_rx_spi_messages(devrec);
	mrf24j40_setup_irq_spi_messages(devrec);

	devrec->regmap_लघु = devm_regmap_init_spi(spi,
						    &mrf24j40_लघु_regmap);
	अगर (IS_ERR(devrec->regmap_लघु)) अणु
		ret = PTR_ERR(devrec->regmap_लघु);
		dev_err(&spi->dev, "Failed to allocate short register map: %d\n",
			ret);
		जाओ err_रेजिस्टर_device;
	पूर्ण

	devrec->regmap_दीर्घ = devm_regmap_init(&spi->dev,
					       &mrf24j40_दीर्घ_regmap_bus,
					       spi, &mrf24j40_दीर्घ_regmap);
	अगर (IS_ERR(devrec->regmap_दीर्घ)) अणु
		ret = PTR_ERR(devrec->regmap_दीर्घ);
		dev_err(&spi->dev, "Failed to allocate long register map: %d\n",
			ret);
		जाओ err_रेजिस्टर_device;
	पूर्ण

	अगर (spi->max_speed_hz > MAX_SPI_SPEED_HZ) अणु
		dev_warn(&spi->dev, "spi clock above possible maximum: %d",
			 MAX_SPI_SPEED_HZ);
		ret = -EINVAL;
		जाओ err_रेजिस्टर_device;
	पूर्ण

	ret = mrf24j40_hw_init(devrec);
	अगर (ret)
		जाओ err_रेजिस्टर_device;

	mrf24j40_phy_setup(devrec);

	/* request IRQF_TRIGGER_LOW as fallback शेष */
	irq_type = irq_get_trigger_type(spi->irq);
	अगर (!irq_type)
		irq_type = IRQF_TRIGGER_LOW;

	ret = devm_request_irq(&spi->dev, spi->irq, mrf24j40_isr,
			       irq_type, dev_name(&spi->dev), devrec);
	अगर (ret) अणु
		dev_err(prपूर्णांकdev(devrec), "Unable to get IRQ");
		जाओ err_रेजिस्टर_device;
	पूर्ण

	dev_dbg(prपूर्णांकdev(devrec), "registered mrf24j40\n");
	ret = ieee802154_रेजिस्टर_hw(devrec->hw);
	अगर (ret)
		जाओ err_रेजिस्टर_device;

	वापस 0;

err_रेजिस्टर_device:
	ieee802154_मुक्त_hw(devrec->hw);
err_ret:
	वापस ret;
पूर्ण

अटल पूर्णांक mrf24j40_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा mrf24j40 *devrec = spi_get_drvdata(spi);

	dev_dbg(prपूर्णांकdev(devrec), "remove\n");

	ieee802154_unरेजिस्टर_hw(devrec->hw);
	ieee802154_मुक्त_hw(devrec->hw);
	/* TODO: Will ieee802154_मुक्त_device() रुको until ->xmit() is
	 * complete? */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mrf24j40_of_match[] = अणु
	अणु .compatible = "microchip,mrf24j40", .data = (व्योम *)MRF24J40 पूर्ण,
	अणु .compatible = "microchip,mrf24j40ma", .data = (व्योम *)MRF24J40MA पूर्ण,
	अणु .compatible = "microchip,mrf24j40mc", .data = (व्योम *)MRF24J40MC पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mrf24j40_of_match);

अटल स्थिर काष्ठा spi_device_id mrf24j40_ids[] = अणु
	अणु "mrf24j40", MRF24J40 पूर्ण,
	अणु "mrf24j40ma", MRF24J40MA पूर्ण,
	अणु "mrf24j40mc", MRF24J40MC पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, mrf24j40_ids);

अटल काष्ठा spi_driver mrf24j40_driver = अणु
	.driver = अणु
		.of_match_table = mrf24j40_of_match,
		.name = "mrf24j40",
	पूर्ण,
	.id_table = mrf24j40_ids,
	.probe = mrf24j40_probe,
	.हटाओ = mrf24j40_हटाओ,
पूर्ण;

module_spi_driver(mrf24j40_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alan Ott");
MODULE_DESCRIPTION("MRF24J40 SPI 802.15.4 Controller Driver");
