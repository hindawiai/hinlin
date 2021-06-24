<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम NXP MCR20A 802.15.4 Wireless-PAN Networking controller
 *
 * Copyright (C) 2018 Xue Liu <liuxueneपंचांगail@gmail.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/ieee802154.h>
#समावेश <linux/debugfs.h>

#समावेश <net/mac802154.h>
#समावेश <net/cfg802154.h>

#समावेश <linux/device.h>

#समावेश "mcr20a.h"

#घोषणा	SPI_COMMAND_BUFFER		3

#घोषणा REGISTER_READ			BIT(7)
#घोषणा REGISTER_WRITE			(0 << 7)
#घोषणा REGISTER_ACCESS			(0 << 6)
#घोषणा PACKET_BUFF_BURST_ACCESS	BIT(6)
#घोषणा PACKET_BUFF_BYTE_ACCESS		BIT(5)

#घोषणा MCR20A_WRITE_REG(x)		(x)
#घोषणा MCR20A_READ_REG(x)		(REGISTER_READ | (x))
#घोषणा MCR20A_BURST_READ_PACKET_BUF	(0xC0)
#घोषणा MCR20A_BURST_WRITE_PACKET_BUF	(0x40)

#घोषणा MCR20A_CMD_REG		0x80
#घोषणा MCR20A_CMD_REG_MASK	0x3f
#घोषणा MCR20A_CMD_WRITE	0x40
#घोषणा MCR20A_CMD_FB		0x20

/* Number of Interrupt Request Status Register */
#घोषणा MCR20A_IRQSTS_NUM 2 /* only IRQ_STS1 and IRQ_STS2 */

/* MCR20A CCA Type */
क्रमागत अणु
	MCR20A_CCA_ED,	  // energy detect - CCA bit not active,
			  // not to be used क्रम T and CCCA sequences
	MCR20A_CCA_MODE1, // energy detect - CCA bit ACTIVE
	MCR20A_CCA_MODE2, // 802.15.4 compliant संकेत detect - CCA bit ACTIVE
	MCR20A_CCA_MODE3
पूर्ण;

क्रमागत अणु
	MCR20A_XCVSEQ_IDLE	= 0x00,
	MCR20A_XCVSEQ_RX	= 0x01,
	MCR20A_XCVSEQ_TX	= 0x02,
	MCR20A_XCVSEQ_CCA	= 0x03,
	MCR20A_XCVSEQ_TR	= 0x04,
	MCR20A_XCVSEQ_CCCA	= 0x05,
पूर्ण;

/* IEEE-802.15.4 defined स्थिरants (2.4 GHz logical channels) */
#घोषणा	MCR20A_MIN_CHANNEL	(11)
#घोषणा	MCR20A_MAX_CHANNEL	(26)
#घोषणा	MCR20A_CHANNEL_SPACING	(5)

/* MCR20A CCA Threshold स्थिरans */
#घोषणा MCR20A_MIN_CCA_THRESHOLD (0x6EU)
#घोषणा MCR20A_MAX_CCA_THRESHOLD (0x00U)

/* version 0C */
#घोषणा MCR20A_OVERWRITE_VERSION (0x0C)

/* MCR20A PLL configurations */
अटल स्थिर u8  PLL_INT[16] = अणु
	/* 2405 */ 0x0B,	/* 2410 */ 0x0B,	/* 2415 */ 0x0B,
	/* 2420 */ 0x0B,	/* 2425 */ 0x0B,	/* 2430 */ 0x0B,
	/* 2435 */ 0x0C,	/* 2440 */ 0x0C,	/* 2445 */ 0x0C,
	/* 2450 */ 0x0C,	/* 2455 */ 0x0C,	/* 2460 */ 0x0C,
	/* 2465 */ 0x0D,	/* 2470 */ 0x0D,	/* 2475 */ 0x0D,
	/* 2480 */ 0x0D
पूर्ण;

अटल स्थिर u8 PLL_FRAC[16] = अणु
	/* 2405 */ 0x28,	/* 2410 */ 0x50,	/* 2415 */ 0x78,
	/* 2420 */ 0xA0,	/* 2425 */ 0xC8,	/* 2430 */ 0xF0,
	/* 2435 */ 0x18,	/* 2440 */ 0x40,	/* 2445 */ 0x68,
	/* 2450 */ 0x90,	/* 2455 */ 0xB8,	/* 2460 */ 0xE0,
	/* 2465 */ 0x08,	/* 2470 */ 0x30,	/* 2475 */ 0x58,
	/* 2480 */ 0x80
पूर्ण;

अटल स्थिर काष्ठा reg_sequence mar20a_iar_overग_लिखोs[] = अणु
	अणु IAR_MISC_PAD_CTRL,	0x02 पूर्ण,
	अणु IAR_VCO_CTRL1,	0xB3 पूर्ण,
	अणु IAR_VCO_CTRL2,	0x07 पूर्ण,
	अणु IAR_PA_TUNING,	0x71 पूर्ण,
	अणु IAR_CHF_IBUF,		0x2F पूर्ण,
	अणु IAR_CHF_QBUF,		0x2F पूर्ण,
	अणु IAR_CHF_IRIN,		0x24 पूर्ण,
	अणु IAR_CHF_QRIN,		0x24 पूर्ण,
	अणु IAR_CHF_IL,		0x24 पूर्ण,
	अणु IAR_CHF_QL,		0x24 पूर्ण,
	अणु IAR_CHF_CC1,		0x32 पूर्ण,
	अणु IAR_CHF_CCL,		0x1D पूर्ण,
	अणु IAR_CHF_CC2,		0x2D पूर्ण,
	अणु IAR_CHF_IROUT,	0x24 पूर्ण,
	अणु IAR_CHF_QROUT,	0x24 पूर्ण,
	अणु IAR_PA_CAL,		0x28 पूर्ण,
	अणु IAR_AGC_THR1,		0x55 पूर्ण,
	अणु IAR_AGC_THR2,		0x2D पूर्ण,
	अणु IAR_ATT_RSSI1,	0x5F पूर्ण,
	अणु IAR_ATT_RSSI2,	0x8F पूर्ण,
	अणु IAR_RSSI_OFFSET,	0x61 पूर्ण,
	अणु IAR_CHF_PMA_GAIN,	0x03 पूर्ण,
	अणु IAR_CCA1_THRESH,	0x50 पूर्ण,
	अणु IAR_CORR_NVAL,	0x13 पूर्ण,
	अणु IAR_ACKDELAY,		0x3D पूर्ण,
पूर्ण;

#घोषणा MCR20A_VALID_CHANNELS (0x07FFF800)
#घोषणा MCR20A_MAX_BUF		(127)

#घोषणा prपूर्णांकdev(X) (&X->spi->dev)

/* regmap inक्रमmation क्रम Direct Access Register (DAR) access */
#घोषणा MCR20A_DAR_WRITE	0x01
#घोषणा MCR20A_DAR_READ		0x00
#घोषणा MCR20A_DAR_NUMREGS	0x3F

/* regmap inक्रमmation क्रम Indirect Access Register (IAR) access */
#घोषणा MCR20A_IAR_ACCESS	0x80
#घोषणा MCR20A_IAR_NUMREGS	0xBEFF

/* Read/Write SPI Commands क्रम DAR and IAR रेजिस्टरs. */
#घोषणा MCR20A_READSHORT(reg)	((reg) << 1)
#घोषणा MCR20A_WRITESHORT(reg)	((reg) << 1 | 1)
#घोषणा MCR20A_READLONG(reg)	(1 << 15 | (reg) << 5)
#घोषणा MCR20A_WRITELONG(reg)	(1 << 15 | (reg) << 5 | 1 << 4)

/* Type definitions क्रम link configuration of instantiable layers  */
#घोषणा MCR20A_PHY_INसूचीECT_QUEUE_SIZE (12)

अटल bool
mcr20a_dar_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DAR_IRQ_STS1:
	हाल DAR_IRQ_STS2:
	हाल DAR_IRQ_STS3:
	हाल DAR_PHY_CTRL1:
	हाल DAR_PHY_CTRL2:
	हाल DAR_PHY_CTRL3:
	हाल DAR_PHY_CTRL4:
	हाल DAR_SRC_CTRL:
	हाल DAR_SRC_ADDRS_SUM_LSB:
	हाल DAR_SRC_ADDRS_SUM_MSB:
	हाल DAR_T3CMP_LSB:
	हाल DAR_T3CMP_MSB:
	हाल DAR_T3CMP_USB:
	हाल DAR_T2PRIMECMP_LSB:
	हाल DAR_T2PRIMECMP_MSB:
	हाल DAR_T1CMP_LSB:
	हाल DAR_T1CMP_MSB:
	हाल DAR_T1CMP_USB:
	हाल DAR_T2CMP_LSB:
	हाल DAR_T2CMP_MSB:
	हाल DAR_T2CMP_USB:
	हाल DAR_T4CMP_LSB:
	हाल DAR_T4CMP_MSB:
	हाल DAR_T4CMP_USB:
	हाल DAR_PLL_INT0:
	हाल DAR_PLL_FRAC0_LSB:
	हाल DAR_PLL_FRAC0_MSB:
	हाल DAR_PA_PWR:
	/* no DAR_ACM */
	हाल DAR_OVERWRITE_VER:
	हाल DAR_CLK_OUT_CTRL:
	हाल DAR_PWR_MODES:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
mcr20a_dar_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	bool rc;

	/* all ग_लिखोable are also पढ़ोable */
	rc = mcr20a_dar_ग_लिखोable(dev, reg);
	अगर (rc)
		वापस rc;

	/* पढ़ोonly regs */
	चयन (reg) अणु
	हाल DAR_RX_FRM_LEN:
	हाल DAR_CCA1_ED_FNL:
	हाल DAR_EVENT_TMR_LSB:
	हाल DAR_EVENT_TMR_MSB:
	हाल DAR_EVENT_TMR_USB:
	हाल DAR_TIMESTAMP_LSB:
	हाल DAR_TIMESTAMP_MSB:
	हाल DAR_TIMESTAMP_USB:
	हाल DAR_SEQ_STATE:
	हाल DAR_LQI_VALUE:
	हाल DAR_RSSI_CCA_CONT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
mcr20a_dar_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* can be changed during runसमय */
	चयन (reg) अणु
	हाल DAR_IRQ_STS1:
	हाल DAR_IRQ_STS2:
	हाल DAR_IRQ_STS3:
	/* use them in spi_async and regmap so it's अस्थिर */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
mcr20a_dar_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* करोn't clear irq line on पढ़ो */
	चयन (reg) अणु
	हाल DAR_IRQ_STS1:
	हाल DAR_IRQ_STS2:
	हाल DAR_IRQ_STS3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config mcr20a_dar_regmap = अणु
	.name			= "mcr20a_dar",
	.reg_bits		= 8,
	.val_bits		= 8,
	.ग_लिखो_flag_mask	= REGISTER_ACCESS | REGISTER_WRITE,
	.पढ़ो_flag_mask		= REGISTER_ACCESS | REGISTER_READ,
	.cache_type		= REGCACHE_RBTREE,
	.ग_लिखोable_reg		= mcr20a_dar_ग_लिखोable,
	.पढ़ोable_reg		= mcr20a_dar_पढ़ोable,
	.अस्थिर_reg		= mcr20a_dar_अस्थिर,
	.precious_reg		= mcr20a_dar_precious,
	.fast_io		= true,
	.can_multi_ग_लिखो	= true,
पूर्ण;

अटल bool
mcr20a_iar_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल IAR_XTAL_TRIM:
	हाल IAR_PMC_LP_TRIM:
	हाल IAR_MACPANID0_LSB:
	हाल IAR_MACPANID0_MSB:
	हाल IAR_MACSHORTADDRS0_LSB:
	हाल IAR_MACSHORTADDRS0_MSB:
	हाल IAR_MACLONGADDRS0_0:
	हाल IAR_MACLONGADDRS0_8:
	हाल IAR_MACLONGADDRS0_16:
	हाल IAR_MACLONGADDRS0_24:
	हाल IAR_MACLONGADDRS0_32:
	हाल IAR_MACLONGADDRS0_40:
	हाल IAR_MACLONGADDRS0_48:
	हाल IAR_MACLONGADDRS0_56:
	हाल IAR_RX_FRAME_FILTER:
	हाल IAR_PLL_INT1:
	हाल IAR_PLL_FRAC1_LSB:
	हाल IAR_PLL_FRAC1_MSB:
	हाल IAR_MACPANID1_LSB:
	हाल IAR_MACPANID1_MSB:
	हाल IAR_MACSHORTADDRS1_LSB:
	हाल IAR_MACSHORTADDRS1_MSB:
	हाल IAR_MACLONGADDRS1_0:
	हाल IAR_MACLONGADDRS1_8:
	हाल IAR_MACLONGADDRS1_16:
	हाल IAR_MACLONGADDRS1_24:
	हाल IAR_MACLONGADDRS1_32:
	हाल IAR_MACLONGADDRS1_40:
	हाल IAR_MACLONGADDRS1_48:
	हाल IAR_MACLONGADDRS1_56:
	हाल IAR_DUAL_PAN_CTRL:
	हाल IAR_DUAL_PAN_DWELL:
	हाल IAR_CCA1_THRESH:
	हाल IAR_CCA1_ED_OFFSET_COMP:
	हाल IAR_LQI_OFFSET_COMP:
	हाल IAR_CCA_CTRL:
	हाल IAR_CCA2_CORR_PEAKS:
	हाल IAR_CCA2_CORR_THRESH:
	हाल IAR_TMR_PRESCALE:
	हाल IAR_ANT_PAD_CTRL:
	हाल IAR_MISC_PAD_CTRL:
	हाल IAR_BSM_CTRL:
	हाल IAR_RNG:
	हाल IAR_RX_WTR_MARK:
	हाल IAR_SOFT_RESET:
	हाल IAR_TXDELAY:
	हाल IAR_ACKDELAY:
	हाल IAR_CORR_NVAL:
	हाल IAR_ANT_AGC_CTRL:
	हाल IAR_AGC_THR1:
	हाल IAR_AGC_THR2:
	हाल IAR_PA_CAL:
	हाल IAR_ATT_RSSI1:
	हाल IAR_ATT_RSSI2:
	हाल IAR_RSSI_OFFSET:
	हाल IAR_XTAL_CTRL:
	हाल IAR_CHF_PMA_GAIN:
	हाल IAR_CHF_IBUF:
	हाल IAR_CHF_QBUF:
	हाल IAR_CHF_IRIN:
	हाल IAR_CHF_QRIN:
	हाल IAR_CHF_IL:
	हाल IAR_CHF_QL:
	हाल IAR_CHF_CC1:
	हाल IAR_CHF_CCL:
	हाल IAR_CHF_CC2:
	हाल IAR_CHF_IROUT:
	हाल IAR_CHF_QROUT:
	हाल IAR_PA_TUNING:
	हाल IAR_VCO_CTRL1:
	हाल IAR_VCO_CTRL2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
mcr20a_iar_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	bool rc;

	/* all ग_लिखोable are also पढ़ोable */
	rc = mcr20a_iar_ग_लिखोable(dev, reg);
	अगर (rc)
		वापस rc;

	/* पढ़ोonly regs */
	चयन (reg) अणु
	हाल IAR_PART_ID:
	हाल IAR_DUAL_PAN_STS:
	हाल IAR_RX_BYTE_COUNT:
	हाल IAR_FILTERFAIL_CODE1:
	हाल IAR_FILTERFAIL_CODE2:
	हाल IAR_RSSI:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
mcr20a_iar_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
/* can be changed during runसमय */
	चयन (reg) अणु
	हाल IAR_DUAL_PAN_STS:
	हाल IAR_RX_BYTE_COUNT:
	हाल IAR_FILTERFAIL_CODE1:
	हाल IAR_FILTERFAIL_CODE2:
	हाल IAR_RSSI:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config mcr20a_iar_regmap = अणु
	.name			= "mcr20a_iar",
	.reg_bits		= 16,
	.val_bits		= 8,
	.ग_लिखो_flag_mask	= REGISTER_ACCESS | REGISTER_WRITE | IAR_INDEX,
	.पढ़ो_flag_mask		= REGISTER_ACCESS | REGISTER_READ  | IAR_INDEX,
	.cache_type		= REGCACHE_RBTREE,
	.ग_लिखोable_reg		= mcr20a_iar_ग_लिखोable,
	.पढ़ोable_reg		= mcr20a_iar_पढ़ोable,
	.अस्थिर_reg		= mcr20a_iar_अस्थिर,
	.fast_io		= true,
पूर्ण;

काष्ठा mcr20a_local अणु
	काष्ठा spi_device *spi;

	काष्ठा ieee802154_hw *hw;
	काष्ठा regmap *regmap_dar;
	काष्ठा regmap *regmap_iar;

	u8 *buf;

	bool is_tx;

	/* क्रम writing tx buffer */
	काष्ठा spi_message tx_buf_msg;
	u8 tx_header[1];
	/* burst buffer ग_लिखो command */
	काष्ठा spi_transfer tx_xfer_header;
	u8 tx_len[1];
	/* len of tx packet */
	काष्ठा spi_transfer tx_xfer_len;
	/* data of tx packet */
	काष्ठा spi_transfer tx_xfer_buf;
	काष्ठा sk_buff *tx_skb;

	/* क्रम पढ़ो length rxfअगरo */
	काष्ठा spi_message reg_msg;
	u8 reg_cmd[1];
	u8 reg_data[MCR20A_IRQSTS_NUM];
	काष्ठा spi_transfer reg_xfer_cmd;
	काष्ठा spi_transfer reg_xfer_data;

	/* receive handling */
	काष्ठा spi_message rx_buf_msg;
	u8 rx_header[1];
	काष्ठा spi_transfer rx_xfer_header;
	u8 rx_lqi[1];
	काष्ठा spi_transfer rx_xfer_lqi;
	u8 rx_buf[MCR20A_MAX_BUF];
	काष्ठा spi_transfer rx_xfer_buf;

	/* isr handling क्रम पढ़ोing पूर्णांकstat */
	काष्ठा spi_message irq_msg;
	u8 irq_header[1];
	u8 irq_data[MCR20A_IRQSTS_NUM];
	काष्ठा spi_transfer irq_xfer_data;
	काष्ठा spi_transfer irq_xfer_header;
पूर्ण;

अटल व्योम
mcr20a_ग_लिखो_tx_buf_complete(व्योम *context)
अणु
	काष्ठा mcr20a_local *lp = context;
	पूर्णांक ret;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	lp->reg_msg.complete = शून्य;
	lp->reg_cmd[0]	= MCR20A_WRITE_REG(DAR_PHY_CTRL1);
	lp->reg_data[0] = MCR20A_XCVSEQ_TX;
	lp->reg_xfer_data.len = 1;

	ret = spi_async(lp->spi, &lp->reg_msg);
	अगर (ret)
		dev_err(prपूर्णांकdev(lp), "failed to set SEQ TX\n");
पूर्ण

अटल पूर्णांक
mcr20a_xmit(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा mcr20a_local *lp = hw->priv;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	lp->tx_skb = skb;

	prपूर्णांक_hex_dump_debug("mcr20a tx: ", DUMP_PREFIX_OFFSET, 16, 1,
			     skb->data, skb->len, 0);

	lp->is_tx = 1;

	lp->reg_msg.complete	= शून्य;
	lp->reg_cmd[0]		= MCR20A_WRITE_REG(DAR_PHY_CTRL1);
	lp->reg_data[0]		= MCR20A_XCVSEQ_IDLE;
	lp->reg_xfer_data.len	= 1;

	वापस spi_async(lp->spi, &lp->reg_msg);
पूर्ण

अटल पूर्णांक
mcr20a_ed(काष्ठा ieee802154_hw *hw, u8 *level)
अणु
	WARN_ON(!level);
	*level = 0xbe;
	वापस 0;
पूर्ण

अटल पूर्णांक
mcr20a_set_channel(काष्ठा ieee802154_hw *hw, u8 page, u8 channel)
अणु
	काष्ठा mcr20a_local *lp = hw->priv;
	पूर्णांक ret;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	/* freqency = ((PLL_INT+64) + (PLL_FRAC/65536)) * 32 MHz */
	ret = regmap_ग_लिखो(lp->regmap_dar, DAR_PLL_INT0, PLL_INT[channel - 11]);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(lp->regmap_dar, DAR_PLL_FRAC0_LSB, 0x00);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(lp->regmap_dar, DAR_PLL_FRAC0_MSB,
			   PLL_FRAC[channel - 11]);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
mcr20a_start(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा mcr20a_local *lp = hw->priv;
	पूर्णांक ret;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	/* No slotted operation */
	dev_dbg(prपूर्णांकdev(lp), "no slotted operation\n");
	ret = regmap_update_bits(lp->regmap_dar, DAR_PHY_CTRL1,
				 DAR_PHY_CTRL1_SLOTTED, 0x0);
	अगर (ret < 0)
		वापस ret;

	/* enable irq */
	enable_irq(lp->spi->irq);

	/* Unmask SEQ पूर्णांकerrupt */
	ret = regmap_update_bits(lp->regmap_dar, DAR_PHY_CTRL2,
				 DAR_PHY_CTRL2_SEQMSK, 0x0);
	अगर (ret < 0)
		वापस ret;

	/* Start the RX sequence */
	dev_dbg(prपूर्णांकdev(lp), "start the RX sequence\n");
	ret = regmap_update_bits(lp->regmap_dar, DAR_PHY_CTRL1,
				 DAR_PHY_CTRL1_XCVSEQ_MASK, MCR20A_XCVSEQ_RX);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम
mcr20a_stop(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा mcr20a_local *lp = hw->priv;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	/* stop all running sequence */
	regmap_update_bits(lp->regmap_dar, DAR_PHY_CTRL1,
			   DAR_PHY_CTRL1_XCVSEQ_MASK, MCR20A_XCVSEQ_IDLE);

	/* disable irq */
	disable_irq(lp->spi->irq);
पूर्ण

अटल पूर्णांक
mcr20a_set_hw_addr_filt(काष्ठा ieee802154_hw *hw,
			काष्ठा ieee802154_hw_addr_filt *filt,
			अचिन्हित दीर्घ changed)
अणु
	काष्ठा mcr20a_local *lp = hw->priv;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	अगर (changed & IEEE802154_AFILT_SADDR_CHANGED) अणु
		u16 addr = le16_to_cpu(filt->लघु_addr);

		regmap_ग_लिखो(lp->regmap_iar, IAR_MACSHORTADDRS0_LSB, addr);
		regmap_ग_लिखो(lp->regmap_iar, IAR_MACSHORTADDRS0_MSB, addr >> 8);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANID_CHANGED) अणु
		u16 pan = le16_to_cpu(filt->pan_id);

		regmap_ग_लिखो(lp->regmap_iar, IAR_MACPANID0_LSB, pan);
		regmap_ग_लिखो(lp->regmap_iar, IAR_MACPANID0_MSB, pan >> 8);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_IEEEADDR_CHANGED) अणु
		u8 addr[8], i;

		स_नकल(addr, &filt->ieee_addr, 8);
		क्रम (i = 0; i < 8; i++)
			regmap_ग_लिखो(lp->regmap_iar,
				     IAR_MACLONGADDRS0_0 + i, addr[i]);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANC_CHANGED) अणु
		अगर (filt->pan_coord) अणु
			regmap_update_bits(lp->regmap_dar, DAR_PHY_CTRL4,
					   DAR_PHY_CTRL4_PANCORDNTR0, 0x10);
		पूर्ण अन्यथा अणु
			regmap_update_bits(lp->regmap_dar, DAR_PHY_CTRL4,
					   DAR_PHY_CTRL4_PANCORDNTR0, 0x00);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* -30 dBm to 10 dBm */
#घोषणा MCR20A_MAX_TX_POWERS 0x14
अटल स्थिर s32 mcr20a_घातers[MCR20A_MAX_TX_POWERS + 1] = अणु
	-3000, -2800, -2600, -2400, -2200, -2000, -1800, -1600, -1400,
	-1200, -1000, -800, -600, -400, -200, 0, 200, 400, 600, 800, 1000
पूर्ण;

अटल पूर्णांक
mcr20a_set_txघातer(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा mcr20a_local *lp = hw->priv;
	u32 i;

	dev_dbg(prपूर्णांकdev(lp), "%s(%d)\n", __func__, mbm);

	क्रम (i = 0; i < lp->hw->phy->supported.tx_घातers_size; i++) अणु
		अगर (lp->hw->phy->supported.tx_घातers[i] == mbm)
			वापस regmap_ग_लिखो(lp->regmap_dar, DAR_PA_PWR,
					    ((i + 8) & 0x1F));
	पूर्ण

	वापस -EINVAL;
पूर्ण

#घोषणा MCR20A_MAX_ED_LEVELS MCR20A_MIN_CCA_THRESHOLD
अटल s32 mcr20a_ed_levels[MCR20A_MAX_ED_LEVELS + 1];

अटल पूर्णांक
mcr20a_set_cca_mode(काष्ठा ieee802154_hw *hw,
		    स्थिर काष्ठा wpan_phy_cca *cca)
अणु
	काष्ठा mcr20a_local *lp = hw->priv;
	अचिन्हित पूर्णांक cca_mode = 0xff;
	bool cca_mode_and = false;
	पूर्णांक ret;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	/* mapping 802.15.4 to driver spec */
	चयन (cca->mode) अणु
	हाल NL802154_CCA_ENERGY:
		cca_mode = MCR20A_CCA_MODE1;
		अवरोध;
	हाल NL802154_CCA_CARRIER:
		cca_mode = MCR20A_CCA_MODE2;
		अवरोध;
	हाल NL802154_CCA_ENERGY_CARRIER:
		चयन (cca->opt) अणु
		हाल NL802154_CCA_OPT_ENERGY_CARRIER_AND:
			cca_mode = MCR20A_CCA_MODE3;
			cca_mode_and = true;
			अवरोध;
		हाल NL802154_CCA_OPT_ENERGY_CARRIER_OR:
			cca_mode = MCR20A_CCA_MODE3;
			cca_mode_and = false;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ret = regmap_update_bits(lp->regmap_dar, DAR_PHY_CTRL4,
				 DAR_PHY_CTRL4_CCATYPE_MASK,
				 cca_mode << DAR_PHY_CTRL4_CCATYPE_SHIFT);
	अगर (ret < 0)
		वापस ret;

	अगर (cca_mode == MCR20A_CCA_MODE3) अणु
		अगर (cca_mode_and) अणु
			ret = regmap_update_bits(lp->regmap_iar, IAR_CCA_CTRL,
						 IAR_CCA_CTRL_CCA3_AND_NOT_OR,
						 0x08);
		पूर्ण अन्यथा अणु
			ret = regmap_update_bits(lp->regmap_iar,
						 IAR_CCA_CTRL,
						 IAR_CCA_CTRL_CCA3_AND_NOT_OR,
						 0x00);
		पूर्ण
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
mcr20a_set_cca_ed_level(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा mcr20a_local *lp = hw->priv;
	u32 i;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	क्रम (i = 0; i < hw->phy->supported.cca_ed_levels_size; i++) अणु
		अगर (hw->phy->supported.cca_ed_levels[i] == mbm)
			वापस regmap_ग_लिखो(lp->regmap_iar, IAR_CCA1_THRESH, i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mcr20a_set_promiscuous_mode(काष्ठा ieee802154_hw *hw, स्थिर bool on)
अणु
	काष्ठा mcr20a_local *lp = hw->priv;
	पूर्णांक ret;
	u8 rx_frame_filter_reg = 0x0;

	dev_dbg(prपूर्णांकdev(lp), "%s(%d)\n", __func__, on);

	अगर (on) अणु
		/* All frame types accepted*/
		rx_frame_filter_reg &= ~(IAR_RX_FRAME_FLT_FRM_VER);
		rx_frame_filter_reg |= (IAR_RX_FRAME_FLT_ACK_FT |
				  IAR_RX_FRAME_FLT_NS_FT);

		ret = regmap_update_bits(lp->regmap_dar, DAR_PHY_CTRL4,
					 DAR_PHY_CTRL4_PROMISCUOUS,
					 DAR_PHY_CTRL4_PROMISCUOUS);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_ग_लिखो(lp->regmap_iar, IAR_RX_FRAME_FILTER,
				   rx_frame_filter_reg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = regmap_update_bits(lp->regmap_dar, DAR_PHY_CTRL4,
					 DAR_PHY_CTRL4_PROMISCUOUS, 0x0);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_ग_लिखो(lp->regmap_iar, IAR_RX_FRAME_FILTER,
				   IAR_RX_FRAME_FLT_FRM_VER |
				   IAR_RX_FRAME_FLT_BEACON_FT |
				   IAR_RX_FRAME_FLT_DATA_FT |
				   IAR_RX_FRAME_FLT_CMD_FT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee802154_ops mcr20a_hw_ops = अणु
	.owner			= THIS_MODULE,
	.xmit_async		= mcr20a_xmit,
	.ed			= mcr20a_ed,
	.set_channel		= mcr20a_set_channel,
	.start			= mcr20a_start,
	.stop			= mcr20a_stop,
	.set_hw_addr_filt	= mcr20a_set_hw_addr_filt,
	.set_txघातer		= mcr20a_set_txघातer,
	.set_cca_mode		= mcr20a_set_cca_mode,
	.set_cca_ed_level	= mcr20a_set_cca_ed_level,
	.set_promiscuous_mode	= mcr20a_set_promiscuous_mode,
पूर्ण;

अटल पूर्णांक
mcr20a_request_rx(काष्ठा mcr20a_local *lp)
अणु
	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	/* Start the RX sequence */
	regmap_update_bits_async(lp->regmap_dar, DAR_PHY_CTRL1,
				 DAR_PHY_CTRL1_XCVSEQ_MASK, MCR20A_XCVSEQ_RX);

	वापस 0;
पूर्ण

अटल व्योम
mcr20a_handle_rx_पढ़ो_buf_complete(व्योम *context)
अणु
	काष्ठा mcr20a_local *lp = context;
	u8 len = lp->reg_data[0] & DAR_RX_FRAME_LENGTH_MASK;
	काष्ठा sk_buff *skb;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	dev_dbg(prपूर्णांकdev(lp), "RX is done\n");

	अगर (!ieee802154_is_valid_psdu_len(len)) अणु
		dev_vdbg(&lp->spi->dev, "corrupted frame received\n");
		len = IEEE802154_MTU;
	पूर्ण

	len = len - 2;  /* get rid of frame check field */

	skb = dev_alloc_skb(len);
	अगर (!skb)
		वापस;

	__skb_put_data(skb, lp->rx_buf, len);
	ieee802154_rx_irqsafe(lp->hw, skb, lp->rx_lqi[0]);

	prपूर्णांक_hex_dump_debug("mcr20a rx: ", DUMP_PREFIX_OFFSET, 16, 1,
			     lp->rx_buf, len, 0);
	pr_debug("mcr20a rx: lqi: %02hhx\n", lp->rx_lqi[0]);

	/* start RX sequence */
	mcr20a_request_rx(lp);
पूर्ण

अटल व्योम
mcr20a_handle_rx_पढ़ो_len_complete(व्योम *context)
अणु
	काष्ठा mcr20a_local *lp = context;
	u8 len;
	पूर्णांक ret;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	/* get the length of received frame */
	len = lp->reg_data[0] & DAR_RX_FRAME_LENGTH_MASK;
	dev_dbg(prपूर्णांकdev(lp), "frame len : %d\n", len);

	/* prepare to पढ़ो the rx buf */
	lp->rx_buf_msg.complete = mcr20a_handle_rx_पढ़ो_buf_complete;
	lp->rx_header[0] = MCR20A_BURST_READ_PACKET_BUF;
	lp->rx_xfer_buf.len = len;

	ret = spi_async(lp->spi, &lp->rx_buf_msg);
	अगर (ret)
		dev_err(prपूर्णांकdev(lp), "failed to read rx buffer length\n");
पूर्ण

अटल पूर्णांक
mcr20a_handle_rx(काष्ठा mcr20a_local *lp)
अणु
	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);
	lp->reg_msg.complete = mcr20a_handle_rx_पढ़ो_len_complete;
	lp->reg_cmd[0] = MCR20A_READ_REG(DAR_RX_FRM_LEN);
	lp->reg_xfer_data.len	= 1;

	वापस spi_async(lp->spi, &lp->reg_msg);
पूर्ण

अटल पूर्णांक
mcr20a_handle_tx_complete(काष्ठा mcr20a_local *lp)
अणु
	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	ieee802154_xmit_complete(lp->hw, lp->tx_skb, false);

	वापस mcr20a_request_rx(lp);
पूर्ण

अटल पूर्णांक
mcr20a_handle_tx(काष्ठा mcr20a_local *lp)
अणु
	पूर्णांक ret;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	/* ग_लिखो tx buffer */
	lp->tx_header[0]	= MCR20A_BURST_WRITE_PACKET_BUF;
	/* add 2 bytes of FCS */
	lp->tx_len[0]		= lp->tx_skb->len + 2;
	lp->tx_xfer_buf.tx_buf	= lp->tx_skb->data;
	/* add 1 byte psduLength */
	lp->tx_xfer_buf.len	= lp->tx_skb->len + 1;

	ret = spi_async(lp->spi, &lp->tx_buf_msg);
	अगर (ret) अणु
		dev_err(prपूर्णांकdev(lp), "SPI write Failed for TX buf\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mcr20a_irq_clean_complete(व्योम *context)
अणु
	काष्ठा mcr20a_local *lp = context;
	u8 seq_state = lp->irq_data[DAR_IRQ_STS1] & DAR_PHY_CTRL1_XCVSEQ_MASK;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	enable_irq(lp->spi->irq);

	dev_dbg(prपूर्णांकdev(lp), "IRQ STA1 (%02x) STA2 (%02x)\n",
		lp->irq_data[DAR_IRQ_STS1], lp->irq_data[DAR_IRQ_STS2]);

	चयन (seq_state) अणु
	/* TX IRQ, RX IRQ and SEQ IRQ */
	हाल (DAR_IRQSTS1_TXIRQ | DAR_IRQSTS1_SEQIRQ):
		अगर (lp->is_tx) अणु
			lp->is_tx = 0;
			dev_dbg(prपूर्णांकdev(lp), "TX is done. No ACK\n");
			mcr20a_handle_tx_complete(lp);
		पूर्ण
		अवरोध;
	हाल (DAR_IRQSTS1_RXIRQ | DAR_IRQSTS1_SEQIRQ):
		/* rx is starting */
		dev_dbg(prपूर्णांकdev(lp), "RX is starting\n");
		mcr20a_handle_rx(lp);
		अवरोध;
	हाल (DAR_IRQSTS1_RXIRQ | DAR_IRQSTS1_TXIRQ | DAR_IRQSTS1_SEQIRQ):
		अगर (lp->is_tx) अणु
			/* tx is करोne */
			lp->is_tx = 0;
			dev_dbg(prपूर्णांकdev(lp), "TX is done. Get ACK\n");
			mcr20a_handle_tx_complete(lp);
		पूर्ण अन्यथा अणु
			/* rx is starting */
			dev_dbg(prपूर्णांकdev(lp), "RX is starting\n");
			mcr20a_handle_rx(lp);
		पूर्ण
		अवरोध;
	हाल (DAR_IRQSTS1_SEQIRQ):
		अगर (lp->is_tx) अणु
			dev_dbg(prपूर्णांकdev(lp), "TX is starting\n");
			mcr20a_handle_tx(lp);
		पूर्ण अन्यथा अणु
			dev_dbg(prपूर्णांकdev(lp), "MCR20A is stop\n");
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mcr20a_irq_status_complete(व्योम *context)
अणु
	पूर्णांक ret;
	काष्ठा mcr20a_local *lp = context;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);
	regmap_update_bits_async(lp->regmap_dar, DAR_PHY_CTRL1,
				 DAR_PHY_CTRL1_XCVSEQ_MASK, MCR20A_XCVSEQ_IDLE);

	lp->reg_msg.complete = mcr20a_irq_clean_complete;
	lp->reg_cmd[0] = MCR20A_WRITE_REG(DAR_IRQ_STS1);
	स_नकल(lp->reg_data, lp->irq_data, MCR20A_IRQSTS_NUM);
	lp->reg_xfer_data.len = MCR20A_IRQSTS_NUM;

	ret = spi_async(lp->spi, &lp->reg_msg);

	अगर (ret)
		dev_err(prपूर्णांकdev(lp), "failed to clean irq status\n");
पूर्ण

अटल irqवापस_t mcr20a_irq_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mcr20a_local *lp = data;
	पूर्णांक ret;

	disable_irq_nosync(irq);

	lp->irq_header[0] = MCR20A_READ_REG(DAR_IRQ_STS1);
	/* पढ़ो IRQSTSx */
	ret = spi_async(lp->spi, &lp->irq_msg);
	अगर (ret) अणु
		enable_irq(irq);
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mcr20a_hw_setup(काष्ठा mcr20a_local *lp)
अणु
	u8 i;
	काष्ठा ieee802154_hw *hw = lp->hw;
	काष्ठा wpan_phy *phy = lp->hw->phy;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	phy->symbol_duration = 16;
	phy->lअगरs_period = 40;
	phy->sअगरs_period = 12;

	hw->flags = IEEE802154_HW_TX_OMIT_CKSUM |
			IEEE802154_HW_AFILT |
			IEEE802154_HW_PROMISCUOUS;

	phy->flags = WPAN_PHY_FLAG_TXPOWER | WPAN_PHY_FLAG_CCA_ED_LEVEL |
			WPAN_PHY_FLAG_CCA_MODE;

	phy->supported.cca_modes = BIT(NL802154_CCA_ENERGY) |
		BIT(NL802154_CCA_CARRIER) | BIT(NL802154_CCA_ENERGY_CARRIER);
	phy->supported.cca_opts = BIT(NL802154_CCA_OPT_ENERGY_CARRIER_AND) |
		BIT(NL802154_CCA_OPT_ENERGY_CARRIER_OR);

	/* initiating cca_ed_levels */
	क्रम (i = MCR20A_MAX_CCA_THRESHOLD; i < MCR20A_MIN_CCA_THRESHOLD + 1;
	      ++i) अणु
		mcr20a_ed_levels[i] =  -i * 100;
	पूर्ण

	phy->supported.cca_ed_levels = mcr20a_ed_levels;
	phy->supported.cca_ed_levels_size = ARRAY_SIZE(mcr20a_ed_levels);

	phy->cca.mode = NL802154_CCA_ENERGY;

	phy->supported.channels[0] = MCR20A_VALID_CHANNELS;
	phy->current_page = 0;
	/* MCR20A शेष reset value */
	phy->current_channel = 20;
	phy->symbol_duration = 16;
	phy->supported.tx_घातers = mcr20a_घातers;
	phy->supported.tx_घातers_size = ARRAY_SIZE(mcr20a_घातers);
	phy->cca_ed_level = phy->supported.cca_ed_levels[75];
	phy->transmit_घातer = phy->supported.tx_घातers[0x0F];
पूर्ण

अटल व्योम
mcr20a_setup_tx_spi_messages(काष्ठा mcr20a_local *lp)
अणु
	spi_message_init(&lp->tx_buf_msg);
	lp->tx_buf_msg.context = lp;
	lp->tx_buf_msg.complete = mcr20a_ग_लिखो_tx_buf_complete;

	lp->tx_xfer_header.len = 1;
	lp->tx_xfer_header.tx_buf = lp->tx_header;

	lp->tx_xfer_len.len = 1;
	lp->tx_xfer_len.tx_buf = lp->tx_len;

	spi_message_add_tail(&lp->tx_xfer_header, &lp->tx_buf_msg);
	spi_message_add_tail(&lp->tx_xfer_len, &lp->tx_buf_msg);
	spi_message_add_tail(&lp->tx_xfer_buf, &lp->tx_buf_msg);
पूर्ण

अटल व्योम
mcr20a_setup_rx_spi_messages(काष्ठा mcr20a_local *lp)
अणु
	spi_message_init(&lp->reg_msg);
	lp->reg_msg.context = lp;

	lp->reg_xfer_cmd.len = 1;
	lp->reg_xfer_cmd.tx_buf = lp->reg_cmd;
	lp->reg_xfer_cmd.rx_buf = lp->reg_cmd;

	lp->reg_xfer_data.rx_buf = lp->reg_data;
	lp->reg_xfer_data.tx_buf = lp->reg_data;

	spi_message_add_tail(&lp->reg_xfer_cmd, &lp->reg_msg);
	spi_message_add_tail(&lp->reg_xfer_data, &lp->reg_msg);

	spi_message_init(&lp->rx_buf_msg);
	lp->rx_buf_msg.context = lp;
	lp->rx_buf_msg.complete = mcr20a_handle_rx_पढ़ो_buf_complete;
	lp->rx_xfer_header.len = 1;
	lp->rx_xfer_header.tx_buf = lp->rx_header;
	lp->rx_xfer_header.rx_buf = lp->rx_header;

	lp->rx_xfer_buf.rx_buf = lp->rx_buf;

	lp->rx_xfer_lqi.len = 1;
	lp->rx_xfer_lqi.rx_buf = lp->rx_lqi;

	spi_message_add_tail(&lp->rx_xfer_header, &lp->rx_buf_msg);
	spi_message_add_tail(&lp->rx_xfer_buf, &lp->rx_buf_msg);
	spi_message_add_tail(&lp->rx_xfer_lqi, &lp->rx_buf_msg);
पूर्ण

अटल व्योम
mcr20a_setup_irq_spi_messages(काष्ठा mcr20a_local *lp)
अणु
	spi_message_init(&lp->irq_msg);
	lp->irq_msg.context		= lp;
	lp->irq_msg.complete	= mcr20a_irq_status_complete;
	lp->irq_xfer_header.len	= 1;
	lp->irq_xfer_header.tx_buf = lp->irq_header;
	lp->irq_xfer_header.rx_buf = lp->irq_header;

	lp->irq_xfer_data.len	= MCR20A_IRQSTS_NUM;
	lp->irq_xfer_data.rx_buf = lp->irq_data;

	spi_message_add_tail(&lp->irq_xfer_header, &lp->irq_msg);
	spi_message_add_tail(&lp->irq_xfer_data, &lp->irq_msg);
पूर्ण

अटल पूर्णांक
mcr20a_phy_init(काष्ठा mcr20a_local *lp)
अणु
	u8 index;
	अचिन्हित पूर्णांक phy_reg = 0;
	पूर्णांक ret;

	dev_dbg(prपूर्णांकdev(lp), "%s\n", __func__);

	/* Disable Tristate on COCO MISO क्रम SPI पढ़ोs */
	ret = regmap_ग_लिखो(lp->regmap_iar, IAR_MISC_PAD_CTRL, 0x02);
	अगर (ret)
		जाओ err_ret;

	/* Clear all PP IRQ bits in IRQSTS1 to aव्योम unexpected पूर्णांकerrupts
	 * immediately after init
	 */
	ret = regmap_ग_लिखो(lp->regmap_dar, DAR_IRQ_STS1, 0xEF);
	अगर (ret)
		जाओ err_ret;

	/* Clear all PP IRQ bits in IRQSTS2 */
	ret = regmap_ग_लिखो(lp->regmap_dar, DAR_IRQ_STS2,
			   DAR_IRQSTS2_ASM_IRQ | DAR_IRQSTS2_PB_ERR_IRQ |
			   DAR_IRQSTS2_WAKE_IRQ);
	अगर (ret)
		जाओ err_ret;

	/* Disable all समयr पूर्णांकerrupts */
	ret = regmap_ग_लिखो(lp->regmap_dar, DAR_IRQ_STS3, 0xFF);
	अगर (ret)
		जाओ err_ret;

	/*  PHY_CTRL1 : शेष HW settings + AUTOACK enabled */
	ret = regmap_update_bits(lp->regmap_dar, DAR_PHY_CTRL1,
				 DAR_PHY_CTRL1_AUTOACK, DAR_PHY_CTRL1_AUTOACK);

	/*  PHY_CTRL2 : disable all पूर्णांकerrupts */
	ret = regmap_ग_लिखो(lp->regmap_dar, DAR_PHY_CTRL2, 0xFF);
	अगर (ret)
		जाओ err_ret;

	/* PHY_CTRL3 : disable all समयrs and reमुख्यing पूर्णांकerrupts */
	ret = regmap_ग_लिखो(lp->regmap_dar, DAR_PHY_CTRL3,
			   DAR_PHY_CTRL3_ASM_MSK | DAR_PHY_CTRL3_PB_ERR_MSK |
			   DAR_PHY_CTRL3_WAKE_MSK);
	अगर (ret)
		जाओ err_ret;

	/* SRC_CTRL : enable Acknowledge Frame Pending and
	 * Source Address Matching Enable
	 */
	ret = regmap_ग_लिखो(lp->regmap_dar, DAR_SRC_CTRL,
			   DAR_SRC_CTRL_ACK_FRM_PND |
			   (DAR_SRC_CTRL_INDEX << DAR_SRC_CTRL_INDEX_SHIFT));
	अगर (ret)
		जाओ err_ret;

	/*  RX_FRAME_FILTER */
	/*  FRM_VER[1:0] = b11. Accept FrameVersion 0 and 1 packets */
	ret = regmap_ग_लिखो(lp->regmap_iar, IAR_RX_FRAME_FILTER,
			   IAR_RX_FRAME_FLT_FRM_VER |
			   IAR_RX_FRAME_FLT_BEACON_FT |
			   IAR_RX_FRAME_FLT_DATA_FT |
			   IAR_RX_FRAME_FLT_CMD_FT);
	अगर (ret)
		जाओ err_ret;

	dev_info(prपूर्णांकdev(lp), "MCR20A DAR overwrites version: 0x%02x\n",
		 MCR20A_OVERWRITE_VERSION);

	/* Overग_लिखोs direct रेजिस्टरs  */
	ret = regmap_ग_लिखो(lp->regmap_dar, DAR_OVERWRITE_VER,
			   MCR20A_OVERWRITE_VERSION);
	अगर (ret)
		जाओ err_ret;

	/* Overग_लिखोs indirect रेजिस्टरs  */
	ret = regmap_multi_reg_ग_लिखो(lp->regmap_iar, mar20a_iar_overग_लिखोs,
				     ARRAY_SIZE(mar20a_iar_overग_लिखोs));
	अगर (ret)
		जाओ err_ret;

	/* Clear HW indirect queue */
	dev_dbg(prपूर्णांकdev(lp), "clear HW indirect queue\n");
	क्रम (index = 0; index < MCR20A_PHY_INसूचीECT_QUEUE_SIZE; index++) अणु
		phy_reg = (u8)(((index & DAR_SRC_CTRL_INDEX) <<
			       DAR_SRC_CTRL_INDEX_SHIFT)
			      | (DAR_SRC_CTRL_SRCADDR_EN)
			      | (DAR_SRC_CTRL_INDEX_DISABLE));
		ret = regmap_ग_लिखो(lp->regmap_dar, DAR_SRC_CTRL, phy_reg);
		अगर (ret)
			जाओ err_ret;
		phy_reg = 0;
	पूर्ण

	/* Assign HW Indirect hash table to PAN0 */
	ret = regmap_पढ़ो(lp->regmap_iar, IAR_DUAL_PAN_CTRL, &phy_reg);
	अगर (ret)
		जाओ err_ret;

	/* Clear current lvl */
	phy_reg &= ~IAR_DUAL_PAN_CTRL_DUAL_PAN_SAM_LVL_MSK;

	/* Set new lvl */
	phy_reg |= MCR20A_PHY_INसूचीECT_QUEUE_SIZE <<
		IAR_DUAL_PAN_CTRL_DUAL_PAN_SAM_LVL_SHIFT;
	ret = regmap_ग_लिखो(lp->regmap_iar, IAR_DUAL_PAN_CTRL, phy_reg);
	अगर (ret)
		जाओ err_ret;

	/* Set CCA threshold to -75 dBm */
	ret = regmap_ग_लिखो(lp->regmap_iar, IAR_CCA1_THRESH, 0x4B);
	अगर (ret)
		जाओ err_ret;

	/* Set prescaller to obtain 1 symbol (16us) समयbase */
	ret = regmap_ग_लिखो(lp->regmap_iar, IAR_TMR_PRESCALE, 0x05);
	अगर (ret)
		जाओ err_ret;

	/* Enable स्वतःकरोze mode. */
	ret = regmap_update_bits(lp->regmap_dar, DAR_PWR_MODES,
				 DAR_PWR_MODES_AUTODOZE,
				 DAR_PWR_MODES_AUTODOZE);
	अगर (ret)
		जाओ err_ret;

	/* Disable clk_out */
	ret = regmap_update_bits(lp->regmap_dar, DAR_CLK_OUT_CTRL,
				 DAR_CLK_OUT_CTRL_EN, 0x0);
	अगर (ret)
		जाओ err_ret;

	वापस 0;

err_ret:
	वापस ret;
पूर्ण

अटल पूर्णांक
mcr20a_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ieee802154_hw *hw;
	काष्ठा mcr20a_local *lp;
	काष्ठा gpio_desc *rst_b;
	पूर्णांक irq_type;
	पूर्णांक ret = -ENOMEM;

	dev_dbg(&spi->dev, "%s\n", __func__);

	अगर (!spi->irq) अणु
		dev_err(&spi->dev, "no IRQ specified\n");
		वापस -EINVAL;
	पूर्ण

	rst_b = devm_gpiod_get(&spi->dev, "rst_b", GPIOD_OUT_HIGH);
	अगर (IS_ERR(rst_b)) अणु
		ret = PTR_ERR(rst_b);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&spi->dev, "Failed to get 'rst_b' gpio: %d", ret);
		वापस ret;
	पूर्ण

	/* reset mcr20a */
	usleep_range(10, 20);
	gpiod_set_value_cansleep(rst_b, 1);
	usleep_range(10, 20);
	gpiod_set_value_cansleep(rst_b, 0);
	usleep_range(120, 240);

	/* allocate ieee802154_hw and निजी data */
	hw = ieee802154_alloc_hw(माप(*lp), &mcr20a_hw_ops);
	अगर (!hw) अणु
		dev_crit(&spi->dev, "ieee802154_alloc_hw failed\n");
		वापस ret;
	पूर्ण

	/* init mcr20a local data */
	lp = hw->priv;
	lp->hw = hw;
	lp->spi = spi;

	/* init ieee802154_hw */
	hw->parent = &spi->dev;
	ieee802154_अक्रमom_extended_addr(&hw->phy->perm_extended_addr);

	/* init buf */
	lp->buf = devm_kzalloc(&spi->dev, SPI_COMMAND_BUFFER, GFP_KERNEL);

	अगर (!lp->buf) अणु
		ret = -ENOMEM;
		जाओ मुक्त_dev;
	पूर्ण

	mcr20a_setup_tx_spi_messages(lp);
	mcr20a_setup_rx_spi_messages(lp);
	mcr20a_setup_irq_spi_messages(lp);

	/* setup regmap */
	lp->regmap_dar = devm_regmap_init_spi(spi, &mcr20a_dar_regmap);
	अगर (IS_ERR(lp->regmap_dar)) अणु
		ret = PTR_ERR(lp->regmap_dar);
		dev_err(&spi->dev, "Failed to allocate dar map: %d\n",
			ret);
		जाओ मुक्त_dev;
	पूर्ण

	lp->regmap_iar = devm_regmap_init_spi(spi, &mcr20a_iar_regmap);
	अगर (IS_ERR(lp->regmap_iar)) अणु
		ret = PTR_ERR(lp->regmap_iar);
		dev_err(&spi->dev, "Failed to allocate iar map: %d\n", ret);
		जाओ मुक्त_dev;
	पूर्ण

	mcr20a_hw_setup(lp);

	spi_set_drvdata(spi, lp);

	ret = mcr20a_phy_init(lp);
	अगर (ret < 0) अणु
		dev_crit(&spi->dev, "mcr20a_phy_init failed\n");
		जाओ मुक्त_dev;
	पूर्ण

	irq_type = irq_get_trigger_type(spi->irq);
	अगर (!irq_type)
		irq_type = IRQF_TRIGGER_FALLING;

	ret = devm_request_irq(&spi->dev, spi->irq, mcr20a_irq_isr,
			       irq_type, dev_name(&spi->dev), lp);
	अगर (ret) अणु
		dev_err(&spi->dev, "could not request_irq for mcr20a\n");
		ret = -ENODEV;
		जाओ मुक्त_dev;
	पूर्ण

	/* disable_irq by शेष and रुको क्रम starting hardware */
	disable_irq(spi->irq);

	ret = ieee802154_रेजिस्टर_hw(hw);
	अगर (ret) अणु
		dev_crit(&spi->dev, "ieee802154_register_hw failed\n");
		जाओ मुक्त_dev;
	पूर्ण

	वापस ret;

मुक्त_dev:
	ieee802154_मुक्त_hw(lp->hw);

	वापस ret;
पूर्ण

अटल पूर्णांक mcr20a_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा mcr20a_local *lp = spi_get_drvdata(spi);

	dev_dbg(&spi->dev, "%s\n", __func__);

	ieee802154_unरेजिस्टर_hw(lp->hw);
	ieee802154_मुक्त_hw(lp->hw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mcr20a_of_match[] = अणु
	अणु .compatible = "nxp,mcr20a", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mcr20a_of_match);

अटल स्थिर काष्ठा spi_device_id mcr20a_device_id[] = अणु
	अणु .name = "mcr20a", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, mcr20a_device_id);

अटल काष्ठा spi_driver mcr20a_driver = अणु
	.id_table = mcr20a_device_id,
	.driver = अणु
		.of_match_table = of_match_ptr(mcr20a_of_match),
		.name	= "mcr20a",
	पूर्ण,
	.probe      = mcr20a_probe,
	.हटाओ     = mcr20a_हटाओ,
पूर्ण;

module_spi_driver(mcr20a_driver);

MODULE_DESCRIPTION("MCR20A Transceiver Driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Xue Liu <liuxuenetmail@gmail>");
