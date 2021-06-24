<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Analog Devices ADF7242 Low-Power IEEE 802.15.4 Transceiver
 *
 * Copyright 2009-2017 Analog Devices Inc.
 *
 * https://www.analog.com/ADF7242
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/firmware.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/of.h>
#समावेश <linux/irq.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/bitops.h>
#समावेश <linux/ieee802154.h>
#समावेश <net/mac802154.h>
#समावेश <net/cfg802154.h>

#घोषणा FIRMWARE "adf7242_firmware.bin"
#घोषणा MAX_POLL_LOOPS 200

/* All Registers */

#घोषणा REG_EXT_CTRL	0x100	/* RW External LNA/PA and पूर्णांकernal PA control */
#घोषणा REG_TX_FSK_TEST 0x101	/* RW TX FSK test mode configuration */
#घोषणा REG_CCA1	0x105	/* RW RSSI threshold क्रम CCA */
#घोषणा REG_CCA2	0x106	/* RW CCA mode configuration */
#घोषणा REG_BUFFERCFG	0x107	/* RW RX_BUFFER overग_लिखो control */
#घोषणा REG_PKT_CFG	0x108	/* RW FCS evaluation configuration */
#घोषणा REG_DELAYCFG0	0x109	/* RW RC_RX command to SFD or sync word delay */
#घोषणा REG_DELAYCFG1	0x10A	/* RW RC_TX command to TX state */
#घोषणा REG_DELAYCFG2	0x10B	/* RW Mac delay extension */
#घोषणा REG_SYNC_WORD0	0x10C	/* RW sync word bits [7:0] of [23:0]  */
#घोषणा REG_SYNC_WORD1	0x10D	/* RW sync word bits [15:8] of [23:0]  */
#घोषणा REG_SYNC_WORD2	0x10E	/* RW sync word bits [23:16] of [23:0]	*/
#घोषणा REG_SYNC_CONFIG	0x10F	/* RW sync word configuration */
#घोषणा REG_RC_CFG	0x13E	/* RW RX / TX packet configuration */
#घोषणा REG_RC_VAR44	0x13F	/* RW RESERVED */
#घोषणा REG_CH_FREQ0	0x300	/* RW Channel Frequency Settings - Low */
#घोषणा REG_CH_FREQ1	0x301	/* RW Channel Frequency Settings - Middle */
#घोषणा REG_CH_FREQ2	0x302	/* RW Channel Frequency Settings - High */
#घोषणा REG_TX_FD	0x304	/* RW TX Frequency Deviation Register */
#घोषणा REG_DM_CFG0	0x305	/* RW RX Discriminator BW Register */
#घोषणा REG_TX_M	0x306	/* RW TX Mode Register */
#घोषणा REG_RX_M	0x307	/* RW RX Mode Register */
#घोषणा REG_RRB		0x30C	/* R RSSI Readback Register */
#घोषणा REG_LRB		0x30D	/* R Link Quality Readback Register */
#घोषणा REG_DR0		0x30E	/* RW bits [15:8] of [15:0] data rate setting */
#घोषणा REG_DR1		0x30F	/* RW bits [7:0] of [15:0] data rate setting */
#घोषणा REG_PRAMPG	0x313	/* RW RESERVED */
#घोषणा REG_TXPB	0x314	/* RW TX Packet Storage Base Address */
#घोषणा REG_RXPB	0x315	/* RW RX Packet Storage Base Address */
#घोषणा REG_TMR_CFG0	0x316	/* RW Wake up Timer Conf Register - High */
#घोषणा REG_TMR_CFG1	0x317	/* RW Wake up Timer Conf Register - Low */
#घोषणा REG_TMR_RLD0	0x318	/* RW Wake up Timer Value Register - High */
#घोषणा REG_TMR_RLD1	0x319	/* RW Wake up Timer Value Register - Low  */
#घोषणा REG_TMR_CTRL	0x31A	/* RW Wake up Timer Timeout flag */
#घोषणा REG_PD_AUX	0x31E	/* RW Batपंचांगon enable */
#घोषणा REG_GP_CFG	0x32C	/* RW GPIO Configuration */
#घोषणा REG_GP_OUT	0x32D	/* RW GPIO Configuration */
#घोषणा REG_GP_IN	0x32E	/* R GPIO Configuration */
#घोषणा REG_SYNT	0x335	/* RW bandwidth calibration समयrs */
#घोषणा REG_CAL_CFG	0x33D	/* RW Calibration Settings */
#घोषणा REG_PA_BIAS	0x36E	/* RW PA BIAS */
#घोषणा REG_SYNT_CAL	0x371	/* RW Oscillator and Doubler Configuration */
#घोषणा REG_IIRF_CFG	0x389	/* RW BB Filter Decimation Rate */
#घोषणा REG_CDR_CFG	0x38A	/* RW CDR kVCO */
#घोषणा REG_DM_CFG1	0x38B	/* RW Postdemodulator Filter */
#घोषणा REG_AGCSTAT	0x38E	/* R RXBB Ref Osc Calibration Engine Readback */
#घोषणा REG_RXCAL0	0x395	/* RW RX BB filter tuning, LSB */
#घोषणा REG_RXCAL1	0x396	/* RW RX BB filter tuning, MSB */
#घोषणा REG_RXFE_CFG	0x39B	/* RW RXBB Ref Osc & RXFE Calibration */
#घोषणा REG_PA_RR	0x3A7	/* RW Set PA ramp rate */
#घोषणा REG_PA_CFG	0x3A8	/* RW PA enable */
#घोषणा REG_EXTPA_CFG	0x3A9	/* RW External PA BIAS DAC */
#घोषणा REG_EXTPA_MSC	0x3AA	/* RW PA Bias Mode */
#घोषणा REG_ADC_RBK	0x3AE	/* R Readback temp */
#घोषणा REG_AGC_CFG1	0x3B2	/* RW GC Parameters */
#घोषणा REG_AGC_MAX	0x3B4	/* RW Slew rate	 */
#घोषणा REG_AGC_CFG2	0x3B6	/* RW RSSI Parameters */
#घोषणा REG_AGC_CFG3	0x3B7	/* RW RSSI Parameters */
#घोषणा REG_AGC_CFG4	0x3B8	/* RW RSSI Parameters */
#घोषणा REG_AGC_CFG5	0x3B9	/* RW RSSI & NDEC Parameters */
#घोषणा REG_AGC_CFG6	0x3BA	/* RW NDEC Parameters */
#घोषणा REG_OCL_CFG1	0x3C4	/* RW OCL System Parameters */
#घोषणा REG_IRQ1_EN0	0x3C7	/* RW Interrupt Mask set bits क्रम IRQ1 */
#घोषणा REG_IRQ1_EN1	0x3C8	/* RW Interrupt Mask set bits क्रम IRQ1 */
#घोषणा REG_IRQ2_EN0	0x3C9	/* RW Interrupt Mask set bits क्रम IRQ2 */
#घोषणा REG_IRQ2_EN1	0x3CA	/* RW Interrupt Mask set bits क्रम IRQ2 */
#घोषणा REG_IRQ1_SRC0	0x3CB	/* RW Interrupt Source bits क्रम IRQ */
#घोषणा REG_IRQ1_SRC1	0x3CC	/* RW Interrupt Source bits क्रम IRQ */
#घोषणा REG_OCL_BW0	0x3D2	/* RW OCL System Parameters */
#घोषणा REG_OCL_BW1	0x3D3	/* RW OCL System Parameters */
#घोषणा REG_OCL_BW2	0x3D4	/* RW OCL System Parameters */
#घोषणा REG_OCL_BW3	0x3D5	/* RW OCL System Parameters */
#घोषणा REG_OCL_BW4	0x3D6	/* RW OCL System Parameters */
#घोषणा REG_OCL_BWS	0x3D7	/* RW OCL System Parameters */
#घोषणा REG_OCL_CFG13	0x3E0	/* RW OCL System Parameters */
#घोषणा REG_GP_DRV	0x3E3	/* RW I/O pads Configuration and bg trim */
#घोषणा REG_BM_CFG	0x3E6	/* RW Batt. Monitor Threshold Voltage setting */
#घोषणा REG_SFD_15_4	0x3F4	/* RW Option to set non standard SFD */
#घोषणा REG_AFC_CFG	0x3F7	/* RW AFC mode and polarity */
#घोषणा REG_AFC_KI_KP	0x3F8	/* RW AFC ki and kp */
#घोषणा REG_AFC_RANGE	0x3F9	/* RW AFC range */
#घोषणा REG_AFC_READ	0x3FA	/* RW Readback frequency error */

/* REG_EXTPA_MSC */
#घोषणा PA_PWR(x)		(((x) & 0xF) << 4)
#घोषणा EXTPA_BIAS_SRC		BIT(3)
#घोषणा EXTPA_BIAS_MODE(x)	(((x) & 0x7) << 0)

/* REG_PA_CFG */
#घोषणा PA_BRIDGE_DBIAS(x)	(((x) & 0x1F) << 0)
#घोषणा PA_DBIAS_HIGH_POWER	21
#घोषणा PA_DBIAS_LOW_POWER	13

/* REG_PA_BIAS */
#घोषणा PA_BIAS_CTRL(x)		(((x) & 0x1F) << 1)
#घोषणा REG_PA_BIAS_DFL		BIT(0)
#घोषणा PA_BIAS_HIGH_POWER	63
#घोषणा PA_BIAS_LOW_POWER	55

#घोषणा REG_PAN_ID0		0x112
#घोषणा REG_PAN_ID1		0x113
#घोषणा REG_SHORT_ADDR_0	0x114
#घोषणा REG_SHORT_ADDR_1	0x115
#घोषणा REG_IEEE_ADDR_0		0x116
#घोषणा REG_IEEE_ADDR_1		0x117
#घोषणा REG_IEEE_ADDR_2		0x118
#घोषणा REG_IEEE_ADDR_3		0x119
#घोषणा REG_IEEE_ADDR_4		0x11A
#घोषणा REG_IEEE_ADDR_5		0x11B
#घोषणा REG_IEEE_ADDR_6		0x11C
#घोषणा REG_IEEE_ADDR_7		0x11D
#घोषणा REG_FFILT_CFG		0x11E
#घोषणा REG_AUTO_CFG		0x11F
#घोषणा REG_AUTO_TX1		0x120
#घोषणा REG_AUTO_TX2		0x121
#घोषणा REG_AUTO_STATUS		0x122

/* REG_FFILT_CFG */
#घोषणा ACCEPT_BEACON_FRAMES   BIT(0)
#घोषणा ACCEPT_DATA_FRAMES     BIT(1)
#घोषणा ACCEPT_ACK_FRAMES      BIT(2)
#घोषणा ACCEPT_MACCMD_FRAMES   BIT(3)
#घोषणा ACCEPT_RESERVED_FRAMES BIT(4)
#घोषणा ACCEPT_ALL_ADDRESS     BIT(5)

/* REG_AUTO_CFG */
#घोषणा AUTO_ACK_FRAMEPEND     BIT(0)
#घोषणा IS_PANCOORD	       BIT(1)
#घोषणा RX_AUTO_ACK_EN	       BIT(3)
#घोषणा CSMA_CA_RX_TURNAROUND  BIT(4)

/* REG_AUTO_TX1 */
#घोषणा MAX_FRAME_RETRIES(x)   ((x) & 0xF)
#घोषणा MAX_CCA_RETRIES(x)     (((x) & 0x7) << 4)

/* REG_AUTO_TX2 */
#घोषणा CSMA_MAX_BE(x)	       ((x) & 0xF)
#घोषणा CSMA_MIN_BE(x)	       (((x) & 0xF) << 4)

#घोषणा CMD_SPI_NOP		0xFF /* No operation. Use क्रम dummy ग_लिखोs */
#घोषणा CMD_SPI_PKT_WR		0x10 /* Write telegram to the Packet RAM
				      * starting from the TX packet base address
				      * poपूर्णांकer tx_packet_base
				      */
#घोषणा CMD_SPI_PKT_RD		0x30 /* Read telegram from the Packet RAM
				      * starting from RX packet base address
				      * poपूर्णांकer rxpb.rx_packet_base
				      */
#घोषणा CMD_SPI_MEM_WR(x)	(0x18 + (x >> 8)) /* Write data to MCR or
						   * Packet RAM sequentially
						   */
#घोषणा CMD_SPI_MEM_RD(x)	(0x38 + (x >> 8)) /* Read data from MCR or
						   * Packet RAM sequentially
						   */
#घोषणा CMD_SPI_MEMR_WR(x)	(0x08 + (x >> 8)) /* Write data to MCR or Packet
						   * RAM as अक्रमom block
						   */
#घोषणा CMD_SPI_MEMR_RD(x)	(0x28 + (x >> 8)) /* Read data from MCR or
						   * Packet RAM अक्रमom block
						   */
#घोषणा CMD_SPI_PRAM_WR		0x1E /* Write data sequentially to current
				      * PRAM page selected
				      */
#घोषणा CMD_SPI_PRAM_RD		0x3E /* Read data sequentially from current
				      * PRAM page selected
				      */
#घोषणा CMD_RC_SLEEP		0xB1 /* Invoke transition of radio controller
				      * पूर्णांकo SLEEP state
				      */
#घोषणा CMD_RC_IDLE		0xB2 /* Invoke transition of radio controller
				      * पूर्णांकo IDLE state
				      */
#घोषणा CMD_RC_PHY_RDY		0xB3 /* Invoke transition of radio controller
				      * पूर्णांकo PHY_RDY state
				      */
#घोषणा CMD_RC_RX		0xB4 /* Invoke transition of radio controller
				      * पूर्णांकo RX state
				      */
#घोषणा CMD_RC_TX		0xB5 /* Invoke transition of radio controller
				      * पूर्णांकo TX state
				      */
#घोषणा CMD_RC_MEAS		0xB6 /* Invoke transition of radio controller
				      * पूर्णांकo MEAS state
				      */
#घोषणा CMD_RC_CCA		0xB7 /* Invoke Clear channel assessment */
#घोषणा CMD_RC_CSMACA		0xC1 /* initiates CSMA-CA channel access
				      * sequence and frame transmission
				      */
#घोषणा CMD_RC_PC_RESET		0xC7 /* Program counter reset */
#घोषणा CMD_RC_RESET		0xC8 /* Resets the ADF7242 and माला_दो it in
				      * the sleep state
				      */
#घोषणा CMD_RC_PC_RESET_NO_WAIT (CMD_RC_PC_RESET | BIT(31))

/* STATUS */

#घोषणा STAT_SPI_READY		BIT(7)
#घोषणा STAT_IRQ_STATUS		BIT(6)
#घोषणा STAT_RC_READY		BIT(5)
#घोषणा STAT_CCA_RESULT		BIT(4)
#घोषणा RC_STATUS_IDLE		1
#घोषणा RC_STATUS_MEAS		2
#घोषणा RC_STATUS_PHY_RDY	3
#घोषणा RC_STATUS_RX		4
#घोषणा RC_STATUS_TX		5
#घोषणा RC_STATUS_MASK		0xF

/* AUTO_STATUS */

#घोषणा SUCCESS			0
#घोषणा SUCCESS_DATPEND		1
#घोषणा FAILURE_CSMACA		2
#घोषणा FAILURE_NOACK		3
#घोषणा AUTO_STATUS_MASK	0x3

#घोषणा PRAM_PAGESIZE		256

/* IRQ1 */

#घोषणा IRQ_CCA_COMPLETE	BIT(0)
#घोषणा IRQ_SFD_RX		BIT(1)
#घोषणा IRQ_SFD_TX		BIT(2)
#घोषणा IRQ_RX_PKT_RCVD		BIT(3)
#घोषणा IRQ_TX_PKT_SENT		BIT(4)
#घोषणा IRQ_FRAME_VALID		BIT(5)
#घोषणा IRQ_ADDRESS_VALID	BIT(6)
#घोषणा IRQ_CSMA_CA		BIT(7)

#घोषणा AUTO_TX_TURNAROUND	BIT(3)
#घोषणा ADDON_EN		BIT(4)

#घोषणा FLAG_XMIT		0
#घोषणा FLAG_START		1

#घोषणा ADF7242_REPORT_CSMA_CA_STAT 0 /* framework करोesn't handle yet */

काष्ठा adf7242_local अणु
	काष्ठा spi_device *spi;
	काष्ठा completion tx_complete;
	काष्ठा ieee802154_hw *hw;
	काष्ठा mutex bmux; /* protect SPI messages */
	काष्ठा spi_message stat_msg;
	काष्ठा spi_transfer stat_xfer;
	काष्ठा dentry *debugfs_root;
	काष्ठा delayed_work work;
	काष्ठा workqueue_काष्ठा *wqueue;
	अचिन्हित दीर्घ flags;
	पूर्णांक tx_stat;
	bool promiscuous;
	s8 rssi;
	u8 max_frame_retries;
	u8 max_cca_retries;
	u8 max_be;
	u8 min_be;

	/* DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */

	u8 buf[3] ____cacheline_aligned;
	u8 buf_reg_tx[3];
	u8 buf_पढ़ो_tx[4];
	u8 buf_पढ़ो_rx[4];
	u8 buf_stat_rx;
	u8 buf_stat_tx;
	u8 buf_cmd;
पूर्ण;

अटल पूर्णांक adf7242_soft_reset(काष्ठा adf7242_local *lp, पूर्णांक line);

अटल पूर्णांक adf7242_status(काष्ठा adf7242_local *lp, u8 *stat)
अणु
	पूर्णांक status;

	mutex_lock(&lp->bmux);
	status = spi_sync(lp->spi, &lp->stat_msg);
	*stat = lp->buf_stat_rx;
	mutex_unlock(&lp->bmux);

	वापस status;
पूर्ण

अटल पूर्णांक adf7242_रुको_status(काष्ठा adf7242_local *lp, अचिन्हित पूर्णांक status,
			       अचिन्हित पूर्णांक mask, पूर्णांक line)
अणु
	पूर्णांक cnt = 0, ret = 0;
	u8 stat;

	करो अणु
		adf7242_status(lp, &stat);
		cnt++;
	पूर्ण जबतक (((stat & mask) != status) && (cnt < MAX_POLL_LOOPS));

	अगर (cnt >= MAX_POLL_LOOPS) अणु
		ret = -ETIMEDOUT;

		अगर (!(stat & STAT_RC_READY)) अणु
			adf7242_soft_reset(lp, line);
			adf7242_status(lp, &stat);

			अगर ((stat & mask) == status)
				ret = 0;
		पूर्ण

		अगर (ret < 0)
			dev_warn(&lp->spi->dev,
				 "%s:line %d Timeout status 0x%x (%d)\n",
				 __func__, line, stat, cnt);
	पूर्ण

	dev_vdbg(&lp->spi->dev, "%s : loops=%d line %d\n", __func__, cnt, line);

	वापस ret;
पूर्ण

अटल पूर्णांक adf7242_रुको_rc_पढ़ोy(काष्ठा adf7242_local *lp, पूर्णांक line)
अणु
	वापस adf7242_रुको_status(lp, STAT_RC_READY | STAT_SPI_READY,
				   STAT_RC_READY | STAT_SPI_READY, line);
पूर्ण

अटल पूर्णांक adf7242_रुको_spi_पढ़ोy(काष्ठा adf7242_local *lp, पूर्णांक line)
अणु
	वापस adf7242_रुको_status(lp, STAT_SPI_READY,
				   STAT_SPI_READY, line);
पूर्ण

अटल पूर्णांक adf7242_ग_लिखो_fbuf(काष्ठा adf7242_local *lp, u8 *data, u8 len)
अणु
	u8 *buf = lp->buf;
	पूर्णांक status;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer_head = अणु
		.len = 2,
		.tx_buf = buf,

	पूर्ण;
	काष्ठा spi_transfer xfer_buf = अणु
		.len = len,
		.tx_buf = data,
	पूर्ण;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer_head, &msg);
	spi_message_add_tail(&xfer_buf, &msg);

	adf7242_रुको_spi_पढ़ोy(lp, __LINE__);

	mutex_lock(&lp->bmux);
	buf[0] = CMD_SPI_PKT_WR;
	buf[1] = len + 2;

	status = spi_sync(lp->spi, &msg);
	mutex_unlock(&lp->bmux);

	वापस status;
पूर्ण

अटल पूर्णांक adf7242_पढ़ो_fbuf(काष्ठा adf7242_local *lp,
			     u8 *data, माप_प्रकार len, bool packet_पढ़ो)
अणु
	u8 *buf = lp->buf;
	पूर्णांक status;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer_head = अणु
		.len = 3,
		.tx_buf = buf,
		.rx_buf = buf,
	पूर्ण;
	काष्ठा spi_transfer xfer_buf = अणु
		.len = len,
		.rx_buf = data,
	पूर्ण;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer_head, &msg);
	spi_message_add_tail(&xfer_buf, &msg);

	adf7242_रुको_spi_पढ़ोy(lp, __LINE__);

	mutex_lock(&lp->bmux);
	अगर (packet_पढ़ो) अणु
		buf[0] = CMD_SPI_PKT_RD;
		buf[1] = CMD_SPI_NOP;
		buf[2] = 0;	/* PHR */
	पूर्ण अन्यथा अणु
		buf[0] = CMD_SPI_PRAM_RD;
		buf[1] = 0;
		buf[2] = CMD_SPI_NOP;
	पूर्ण

	status = spi_sync(lp->spi, &msg);

	mutex_unlock(&lp->bmux);

	वापस status;
पूर्ण

अटल पूर्णांक adf7242_पढ़ो_reg(काष्ठा adf7242_local *lp, u16 addr, u8 *data)
अणु
	पूर्णांक status;
	काष्ठा spi_message msg;

	काष्ठा spi_transfer xfer = अणु
		.len = 4,
		.tx_buf = lp->buf_पढ़ो_tx,
		.rx_buf = lp->buf_पढ़ो_rx,
	पूर्ण;

	adf7242_रुको_spi_पढ़ोy(lp, __LINE__);

	mutex_lock(&lp->bmux);
	lp->buf_पढ़ो_tx[0] = CMD_SPI_MEM_RD(addr);
	lp->buf_पढ़ो_tx[1] = addr;
	lp->buf_पढ़ो_tx[2] = CMD_SPI_NOP;
	lp->buf_पढ़ो_tx[3] = CMD_SPI_NOP;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	status = spi_sync(lp->spi, &msg);
	अगर (msg.status)
		status = msg.status;

	अगर (!status)
		*data = lp->buf_पढ़ो_rx[3];

	mutex_unlock(&lp->bmux);

	dev_vdbg(&lp->spi->dev, "%s : REG 0x%X, VAL 0x%X\n", __func__,
		 addr, *data);

	वापस status;
पूर्ण

अटल पूर्णांक adf7242_ग_लिखो_reg(काष्ठा adf7242_local *lp, u16 addr, u8 data)
अणु
	पूर्णांक status;

	adf7242_रुको_spi_पढ़ोy(lp, __LINE__);

	mutex_lock(&lp->bmux);
	lp->buf_reg_tx[0] = CMD_SPI_MEM_WR(addr);
	lp->buf_reg_tx[1] = addr;
	lp->buf_reg_tx[2] = data;
	status = spi_ग_लिखो(lp->spi, lp->buf_reg_tx, 3);
	mutex_unlock(&lp->bmux);

	dev_vdbg(&lp->spi->dev, "%s : REG 0x%X, VAL 0x%X\n",
		 __func__, addr, data);

	वापस status;
पूर्ण

अटल पूर्णांक adf7242_cmd(काष्ठा adf7242_local *lp, अचिन्हित पूर्णांक cmd)
अणु
	पूर्णांक status;

	dev_vdbg(&lp->spi->dev, "%s : CMD=0x%X\n", __func__, cmd);

	अगर (cmd != CMD_RC_PC_RESET_NO_WAIT)
		adf7242_रुको_rc_पढ़ोy(lp, __LINE__);

	mutex_lock(&lp->bmux);
	lp->buf_cmd = cmd;
	status = spi_ग_लिखो(lp->spi, &lp->buf_cmd, 1);
	mutex_unlock(&lp->bmux);

	वापस status;
पूर्ण

अटल पूर्णांक adf7242_upload_firmware(काष्ठा adf7242_local *lp, u8 *data, u16 len)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer_buf = अणु पूर्ण;
	पूर्णांक status, i, page = 0;
	u8 *buf = lp->buf;

	काष्ठा spi_transfer xfer_head = अणु
		.len = 2,
		.tx_buf = buf,
	पूर्ण;

	buf[0] = CMD_SPI_PRAM_WR;
	buf[1] = 0;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer_head, &msg);
	spi_message_add_tail(&xfer_buf, &msg);

	क्रम (i = len; i >= 0; i -= PRAM_PAGESIZE) अणु
		adf7242_ग_लिखो_reg(lp, REG_PRAMPG, page);

		xfer_buf.len = (i >= PRAM_PAGESIZE) ? PRAM_PAGESIZE : i;
		xfer_buf.tx_buf = &data[page * PRAM_PAGESIZE];

		mutex_lock(&lp->bmux);
		status = spi_sync(lp->spi, &msg);
		mutex_unlock(&lp->bmux);
		page++;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक adf7242_verअगरy_firmware(काष्ठा adf7242_local *lp,
				   स्थिर u8 *data, माप_प्रकार len)
अणु
#अगर_घोषित DEBUG
	पूर्णांक i, j;
	अचिन्हित पूर्णांक page;
	u8 *buf = kदो_स्मृति(PRAM_PAGESIZE, GFP_KERNEL);

	अगर (!buf)
		वापस -ENOMEM;

	क्रम (page = 0, i = len; i >= 0; i -= PRAM_PAGESIZE, page++) अणु
		माप_प्रकार nb = (i >= PRAM_PAGESIZE) ? PRAM_PAGESIZE : i;

		adf7242_ग_लिखो_reg(lp, REG_PRAMPG, page);
		adf7242_पढ़ो_fbuf(lp, buf, nb, false);

		क्रम (j = 0; j < nb; j++) अणु
			अगर (buf[j] != data[page * PRAM_PAGESIZE + j]) अणु
				kमुक्त(buf);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण
	kमुक्त(buf);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम adf7242_clear_irqstat(काष्ठा adf7242_local *lp)
अणु
	adf7242_ग_लिखो_reg(lp, REG_IRQ1_SRC1, IRQ_CCA_COMPLETE | IRQ_SFD_RX |
			  IRQ_SFD_TX | IRQ_RX_PKT_RCVD | IRQ_TX_PKT_SENT |
			  IRQ_FRAME_VALID | IRQ_ADDRESS_VALID | IRQ_CSMA_CA);
पूर्ण

अटल पूर्णांक adf7242_cmd_rx(काष्ठा adf7242_local *lp)
अणु
	/* Wait until the ACK is sent */
	adf7242_रुको_status(lp, RC_STATUS_PHY_RDY, RC_STATUS_MASK, __LINE__);
	adf7242_clear_irqstat(lp);
	mod_delayed_work(lp->wqueue, &lp->work, msecs_to_jअगरfies(400));

	वापस adf7242_cmd(lp, CMD_RC_RX);
पूर्ण

अटल व्योम adf7242_rx_cal_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adf7242_local *lp =
	container_of(work, काष्ठा adf7242_local, work.work);

	/* Reissuing RC_RX every 400ms - to adjust क्रम offset
	 * drअगरt in receiver (datasheet page 61, OCL section)
	 */

	अगर (!test_bit(FLAG_XMIT, &lp->flags)) अणु
		adf7242_cmd(lp, CMD_RC_PHY_RDY);
		adf7242_cmd_rx(lp);
	पूर्ण
पूर्ण

अटल पूर्णांक adf7242_set_txघातer(काष्ठा ieee802154_hw *hw, पूर्णांक mbm)
अणु
	काष्ठा adf7242_local *lp = hw->priv;
	u8 pwr, bias_ctrl, dbias, पंचांगp;
	पूर्णांक db = mbm / 100;

	dev_vdbg(&lp->spi->dev, "%s : Power %d dB\n", __func__, db);

	अगर (db > 5 || db < -26)
		वापस -EINVAL;

	db = DIV_ROUND_CLOSEST(db + 29, 2);

	अगर (db > 15) अणु
		dbias = PA_DBIAS_HIGH_POWER;
		bias_ctrl = PA_BIAS_HIGH_POWER;
	पूर्ण अन्यथा अणु
		dbias = PA_DBIAS_LOW_POWER;
		bias_ctrl = PA_BIAS_LOW_POWER;
	पूर्ण

	pwr = clamp_t(u8, db, 3, 15);

	adf7242_पढ़ो_reg(lp, REG_PA_CFG, &पंचांगp);
	पंचांगp &= ~PA_BRIDGE_DBIAS(~0);
	पंचांगp |= PA_BRIDGE_DBIAS(dbias);
	adf7242_ग_लिखो_reg(lp, REG_PA_CFG, पंचांगp);

	adf7242_पढ़ो_reg(lp, REG_PA_BIAS, &पंचांगp);
	पंचांगp &= ~PA_BIAS_CTRL(~0);
	पंचांगp |= PA_BIAS_CTRL(bias_ctrl);
	adf7242_ग_लिखो_reg(lp, REG_PA_BIAS, पंचांगp);

	adf7242_पढ़ो_reg(lp, REG_EXTPA_MSC, &पंचांगp);
	पंचांगp &= ~PA_PWR(~0);
	पंचांगp |= PA_PWR(pwr);

	वापस adf7242_ग_लिखो_reg(lp, REG_EXTPA_MSC, पंचांगp);
पूर्ण

अटल पूर्णांक adf7242_set_csma_params(काष्ठा ieee802154_hw *hw, u8 min_be,
				   u8 max_be, u8 retries)
अणु
	काष्ठा adf7242_local *lp = hw->priv;
	पूर्णांक ret;

	dev_vdbg(&lp->spi->dev, "%s : min_be=%d max_be=%d retries=%d\n",
		 __func__, min_be, max_be, retries);

	अगर (min_be > max_be || max_be > 8 || retries > 5)
		वापस -EINVAL;

	ret = adf7242_ग_लिखो_reg(lp, REG_AUTO_TX1,
				MAX_FRAME_RETRIES(lp->max_frame_retries) |
				MAX_CCA_RETRIES(retries));
	अगर (ret)
		वापस ret;

	lp->max_cca_retries = retries;
	lp->max_be = max_be;
	lp->min_be = min_be;

	वापस adf7242_ग_लिखो_reg(lp, REG_AUTO_TX2, CSMA_MAX_BE(max_be) |
			CSMA_MIN_BE(min_be));
पूर्ण

अटल पूर्णांक adf7242_set_frame_retries(काष्ठा ieee802154_hw *hw, s8 retries)
अणु
	काष्ठा adf7242_local *lp = hw->priv;
	पूर्णांक ret = 0;

	dev_vdbg(&lp->spi->dev, "%s : Retries = %d\n", __func__, retries);

	अगर (retries < -1 || retries > 15)
		वापस -EINVAL;

	अगर (retries >= 0)
		ret = adf7242_ग_लिखो_reg(lp, REG_AUTO_TX1,
					MAX_FRAME_RETRIES(retries) |
					MAX_CCA_RETRIES(lp->max_cca_retries));

	lp->max_frame_retries = retries;

	वापस ret;
पूर्ण

अटल पूर्णांक adf7242_ed(काष्ठा ieee802154_hw *hw, u8 *level)
अणु
	काष्ठा adf7242_local *lp = hw->priv;

	*level = lp->rssi;

	dev_vdbg(&lp->spi->dev, "%s :Exit level=%d\n",
		 __func__, *level);

	वापस 0;
पूर्ण

अटल पूर्णांक adf7242_start(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा adf7242_local *lp = hw->priv;

	adf7242_cmd(lp, CMD_RC_PHY_RDY);
	adf7242_clear_irqstat(lp);
	enable_irq(lp->spi->irq);
	set_bit(FLAG_START, &lp->flags);

	वापस adf7242_cmd_rx(lp);
पूर्ण

अटल व्योम adf7242_stop(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा adf7242_local *lp = hw->priv;

	disable_irq(lp->spi->irq);
	cancel_delayed_work_sync(&lp->work);
	adf7242_cmd(lp, CMD_RC_IDLE);
	clear_bit(FLAG_START, &lp->flags);
	adf7242_clear_irqstat(lp);
पूर्ण

अटल पूर्णांक adf7242_channel(काष्ठा ieee802154_hw *hw, u8 page, u8 channel)
अणु
	काष्ठा adf7242_local *lp = hw->priv;
	अचिन्हित दीर्घ freq;

	dev_dbg(&lp->spi->dev, "%s :Channel=%d\n", __func__, channel);

	might_sleep();

	WARN_ON(page != 0);
	WARN_ON(channel < 11);
	WARN_ON(channel > 26);

	freq = (2405 + 5 * (channel - 11)) * 100;
	adf7242_cmd(lp, CMD_RC_PHY_RDY);

	adf7242_ग_लिखो_reg(lp, REG_CH_FREQ0, freq);
	adf7242_ग_लिखो_reg(lp, REG_CH_FREQ1, freq >> 8);
	adf7242_ग_लिखो_reg(lp, REG_CH_FREQ2, freq >> 16);

	अगर (test_bit(FLAG_START, &lp->flags))
		वापस adf7242_cmd_rx(lp);
	अन्यथा
		वापस adf7242_cmd(lp, CMD_RC_PHY_RDY);
पूर्ण

अटल पूर्णांक adf7242_set_hw_addr_filt(काष्ठा ieee802154_hw *hw,
				    काष्ठा ieee802154_hw_addr_filt *filt,
				    अचिन्हित दीर्घ changed)
अणु
	काष्ठा adf7242_local *lp = hw->priv;
	u8 reg;

	dev_dbg(&lp->spi->dev, "%s :Changed=0x%lX\n", __func__, changed);

	might_sleep();

	अगर (changed & IEEE802154_AFILT_IEEEADDR_CHANGED) अणु
		u8 addr[8], i;

		स_नकल(addr, &filt->ieee_addr, 8);

		क्रम (i = 0; i < 8; i++)
			adf7242_ग_लिखो_reg(lp, REG_IEEE_ADDR_0 + i, addr[i]);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_SADDR_CHANGED) अणु
		u16 saddr = le16_to_cpu(filt->लघु_addr);

		adf7242_ग_लिखो_reg(lp, REG_SHORT_ADDR_0, saddr);
		adf7242_ग_लिखो_reg(lp, REG_SHORT_ADDR_1, saddr >> 8);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANID_CHANGED) अणु
		u16 pan_id = le16_to_cpu(filt->pan_id);

		adf7242_ग_लिखो_reg(lp, REG_PAN_ID0, pan_id);
		adf7242_ग_लिखो_reg(lp, REG_PAN_ID1, pan_id >> 8);
	पूर्ण

	अगर (changed & IEEE802154_AFILT_PANC_CHANGED) अणु
		adf7242_पढ़ो_reg(lp, REG_AUTO_CFG, &reg);
		अगर (filt->pan_coord)
			reg |= IS_PANCOORD;
		अन्यथा
			reg &= ~IS_PANCOORD;
		adf7242_ग_लिखो_reg(lp, REG_AUTO_CFG, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adf7242_set_promiscuous_mode(काष्ठा ieee802154_hw *hw, bool on)
अणु
	काष्ठा adf7242_local *lp = hw->priv;

	dev_dbg(&lp->spi->dev, "%s : mode %d\n", __func__, on);

	lp->promiscuous = on;

	अगर (on) अणु
		adf7242_ग_लिखो_reg(lp, REG_AUTO_CFG, 0);
		वापस adf7242_ग_लिखो_reg(lp, REG_FFILT_CFG,
				  ACCEPT_BEACON_FRAMES |
				  ACCEPT_DATA_FRAMES |
				  ACCEPT_MACCMD_FRAMES |
				  ACCEPT_ALL_ADDRESS |
				  ACCEPT_ACK_FRAMES |
				  ACCEPT_RESERVED_FRAMES);
	पूर्ण अन्यथा अणु
		adf7242_ग_लिखो_reg(lp, REG_FFILT_CFG,
				  ACCEPT_BEACON_FRAMES |
				  ACCEPT_DATA_FRAMES |
				  ACCEPT_MACCMD_FRAMES |
				  ACCEPT_RESERVED_FRAMES);

		वापस adf7242_ग_लिखो_reg(lp, REG_AUTO_CFG, RX_AUTO_ACK_EN);
	पूर्ण
पूर्ण

अटल पूर्णांक adf7242_set_cca_ed_level(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा adf7242_local *lp = hw->priv;
	s8 level = clamp_t(s8, mbm / 100, S8_MIN, S8_MAX);

	dev_dbg(&lp->spi->dev, "%s : level %d\n", __func__, level);

	वापस adf7242_ग_लिखो_reg(lp, REG_CCA1, level);
पूर्ण

अटल पूर्णांक adf7242_xmit(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा adf7242_local *lp = hw->priv;
	पूर्णांक ret;

	/* ensure existing instances of the IRQ handler have completed */
	disable_irq(lp->spi->irq);
	set_bit(FLAG_XMIT, &lp->flags);
	cancel_delayed_work_sync(&lp->work);
	reinit_completion(&lp->tx_complete);
	adf7242_cmd(lp, CMD_RC_PHY_RDY);
	adf7242_clear_irqstat(lp);

	ret = adf7242_ग_लिखो_fbuf(lp, skb->data, skb->len);
	अगर (ret)
		जाओ err;

	ret = adf7242_cmd(lp, CMD_RC_CSMACA);
	अगर (ret)
		जाओ err;
	enable_irq(lp->spi->irq);

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&lp->tx_complete,
							HZ / 10);
	अगर (ret < 0)
		जाओ err;
	अगर (ret == 0) अणु
		dev_dbg(&lp->spi->dev, "Timeout waiting for TX interrupt\n");
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	अगर (lp->tx_stat != SUCCESS) अणु
		dev_dbg(&lp->spi->dev,
			"Error xmit: Retry count exceeded Status=0x%x\n",
			lp->tx_stat);
		ret = -ECOMM;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

err:
	clear_bit(FLAG_XMIT, &lp->flags);
	adf7242_cmd_rx(lp);

	वापस ret;
पूर्ण

अटल पूर्णांक adf7242_rx(काष्ठा adf7242_local *lp)
अणु
	काष्ठा sk_buff *skb;
	माप_प्रकार len;
	पूर्णांक ret;
	u8 lqi, len_u8, *data;

	ret = adf7242_पढ़ो_reg(lp, 0, &len_u8);
	अगर (ret)
		वापस ret;

	len = len_u8;

	अगर (!ieee802154_is_valid_psdu_len(len)) अणु
		dev_dbg(&lp->spi->dev,
			"corrupted frame received len %d\n", (पूर्णांक)len);
		len = IEEE802154_MTU;
	पूर्ण

	skb = dev_alloc_skb(len);
	अगर (!skb) अणु
		adf7242_cmd_rx(lp);
		वापस -ENOMEM;
	पूर्ण

	data = skb_put(skb, len);
	ret = adf7242_पढ़ो_fbuf(lp, data, len, true);
	अगर (ret < 0) अणु
		kमुक्त_skb(skb);
		adf7242_cmd_rx(lp);
		वापस ret;
	पूर्ण

	lqi = data[len - 2];
	lp->rssi = data[len - 1];

	ret = adf7242_cmd_rx(lp);

	skb_trim(skb, len - 2);	/* Don't put RSSI/LQI or CRC पूर्णांकo the frame */

	ieee802154_rx_irqsafe(lp->hw, skb, lqi);

	dev_dbg(&lp->spi->dev, "%s: ret=%d len=%d lqi=%d rssi=%d\n",
		__func__, ret, (पूर्णांक)len, (पूर्णांक)lqi, lp->rssi);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ieee802154_ops adf7242_ops = अणु
	.owner = THIS_MODULE,
	.xmit_sync = adf7242_xmit,
	.ed = adf7242_ed,
	.set_channel = adf7242_channel,
	.set_hw_addr_filt = adf7242_set_hw_addr_filt,
	.start = adf7242_start,
	.stop = adf7242_stop,
	.set_csma_params = adf7242_set_csma_params,
	.set_frame_retries = adf7242_set_frame_retries,
	.set_txघातer = adf7242_set_txघातer,
	.set_promiscuous_mode = adf7242_set_promiscuous_mode,
	.set_cca_ed_level = adf7242_set_cca_ed_level,
पूर्ण;

अटल व्योम adf7242_debug(काष्ठा adf7242_local *lp, u8 irq1)
अणु
#अगर_घोषित DEBUG
	u8 stat;

	adf7242_status(lp, &stat);

	dev_dbg(&lp->spi->dev, "%s IRQ1 = %X:\n%s%s%s%s%s%s%s%s\n",
		__func__, irq1,
		irq1 & IRQ_CCA_COMPLETE ? "IRQ_CCA_COMPLETE\n" : "",
		irq1 & IRQ_SFD_RX ? "IRQ_SFD_RX\n" : "",
		irq1 & IRQ_SFD_TX ? "IRQ_SFD_TX\n" : "",
		irq1 & IRQ_RX_PKT_RCVD ? "IRQ_RX_PKT_RCVD\n" : "",
		irq1 & IRQ_TX_PKT_SENT ? "IRQ_TX_PKT_SENT\n" : "",
		irq1 & IRQ_CSMA_CA ? "IRQ_CSMA_CA\n" : "",
		irq1 & IRQ_FRAME_VALID ? "IRQ_FRAME_VALID\n" : "",
		irq1 & IRQ_ADDRESS_VALID ? "IRQ_ADDRESS_VALID\n" : "");

	dev_dbg(&lp->spi->dev, "%s STATUS = %X:\n%s\n%s\n%s\n%s\n%s%s%s%s%s\n",
		__func__, stat,
		stat & STAT_SPI_READY ? "SPI_READY" : "SPI_BUSY",
		stat & STAT_IRQ_STATUS ? "IRQ_PENDING" : "IRQ_CLEAR",
		stat & STAT_RC_READY ? "RC_READY" : "RC_BUSY",
		stat & STAT_CCA_RESULT ? "CHAN_IDLE" : "CHAN_BUSY",
		(stat & 0xf) == RC_STATUS_IDLE ? "RC_STATUS_IDLE" : "",
		(stat & 0xf) == RC_STATUS_MEAS ? "RC_STATUS_MEAS" : "",
		(stat & 0xf) == RC_STATUS_PHY_RDY ? "RC_STATUS_PHY_RDY" : "",
		(stat & 0xf) == RC_STATUS_RX ? "RC_STATUS_RX" : "",
		(stat & 0xf) == RC_STATUS_TX ? "RC_STATUS_TX" : "");
#पूर्ण_अगर
पूर्ण

अटल irqवापस_t adf7242_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा adf7242_local *lp = data;
	अचिन्हित पूर्णांक xmit;
	u8 irq1;

	mod_delayed_work(lp->wqueue, &lp->work, msecs_to_jअगरfies(400));
	adf7242_पढ़ो_reg(lp, REG_IRQ1_SRC1, &irq1);

	अगर (!(irq1 & (IRQ_RX_PKT_RCVD | IRQ_CSMA_CA)))
		dev_err(&lp->spi->dev, "%s :ERROR IRQ1 = 0x%X\n",
			__func__, irq1);

	adf7242_debug(lp, irq1);

	xmit = test_bit(FLAG_XMIT, &lp->flags);

	अगर (xmit && (irq1 & IRQ_CSMA_CA)) अणु
		adf7242_रुको_status(lp, RC_STATUS_PHY_RDY,
				    RC_STATUS_MASK, __LINE__);

		अगर (ADF7242_REPORT_CSMA_CA_STAT) अणु
			u8 astat;

			adf7242_पढ़ो_reg(lp, REG_AUTO_STATUS, &astat);
			astat &= AUTO_STATUS_MASK;

			dev_dbg(&lp->spi->dev, "AUTO_STATUS = %X:\n%s%s%s%s\n",
				astat,
				astat == SUCCESS ? "SUCCESS" : "",
				astat ==
				SUCCESS_DATPEND ? "SUCCESS_DATPEND" : "",
				astat == FAILURE_CSMACA ? "FAILURE_CSMACA" : "",
				astat == FAILURE_NOACK ? "FAILURE_NOACK" : "");

			/* save CSMA-CA completion status */
			lp->tx_stat = astat;
		पूर्ण अन्यथा अणु
			lp->tx_stat = SUCCESS;
		पूर्ण
		complete(&lp->tx_complete);
		adf7242_clear_irqstat(lp);
	पूर्ण अन्यथा अगर (!xmit && (irq1 & IRQ_RX_PKT_RCVD) &&
		   (irq1 & IRQ_FRAME_VALID)) अणु
		adf7242_rx(lp);
	पूर्ण अन्यथा अगर (!xmit && test_bit(FLAG_START, &lp->flags)) अणु
		/* Invalid packet received - drop it and restart */
		dev_dbg(&lp->spi->dev, "%s:%d : ERROR IRQ1 = 0x%X\n",
			__func__, __LINE__, irq1);
		adf7242_cmd(lp, CMD_RC_PHY_RDY);
		adf7242_cmd_rx(lp);
	पूर्ण अन्यथा अणु
		/* This can only be xmit without IRQ, likely a RX packet.
		 * we get an TX IRQ लघुly - करो nothing or let the xmit
		 * समयout handle this
		 */

		dev_dbg(&lp->spi->dev, "%s:%d : ERROR IRQ1 = 0x%X, xmit %d\n",
			__func__, __LINE__, irq1, xmit);
		adf7242_रुको_status(lp, RC_STATUS_PHY_RDY,
				    RC_STATUS_MASK, __LINE__);
		complete(&lp->tx_complete);
		adf7242_clear_irqstat(lp);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adf7242_soft_reset(काष्ठा adf7242_local *lp, पूर्णांक line)
अणु
	dev_warn(&lp->spi->dev, "%s (line %d)\n", __func__, line);

	अगर (test_bit(FLAG_START, &lp->flags))
		disable_irq_nosync(lp->spi->irq);

	adf7242_cmd(lp, CMD_RC_PC_RESET_NO_WAIT);
	usleep_range(200, 250);
	adf7242_ग_लिखो_reg(lp, REG_PKT_CFG, ADDON_EN | BIT(2));
	adf7242_cmd(lp, CMD_RC_PHY_RDY);
	adf7242_set_promiscuous_mode(lp->hw, lp->promiscuous);
	adf7242_set_csma_params(lp->hw, lp->min_be, lp->max_be,
				lp->max_cca_retries);
	adf7242_clear_irqstat(lp);

	अगर (test_bit(FLAG_START, &lp->flags)) अणु
		enable_irq(lp->spi->irq);
		वापस adf7242_cmd(lp, CMD_RC_RX);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adf7242_hw_init(काष्ठा adf7242_local *lp)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw;

	adf7242_cmd(lp, CMD_RC_RESET);
	adf7242_cmd(lp, CMD_RC_IDLE);

	/* get ADF7242 adकरोn firmware
	 * build this driver as module
	 * and place under /lib/firmware/adf7242_firmware.bin
	 * or compile firmware पूर्णांकo the kernel.
	 */
	ret = request_firmware(&fw, FIRMWARE, &lp->spi->dev);
	अगर (ret) अणु
		dev_err(&lp->spi->dev,
			"request_firmware() failed with %d\n", ret);
		वापस ret;
	पूर्ण

	ret = adf7242_upload_firmware(lp, (u8 *)fw->data, fw->size);
	अगर (ret) अणु
		dev_err(&lp->spi->dev,
			"upload firmware failed with %d\n", ret);
		release_firmware(fw);
		वापस ret;
	पूर्ण

	ret = adf7242_verअगरy_firmware(lp, (u8 *)fw->data, fw->size);
	अगर (ret) अणु
		dev_err(&lp->spi->dev,
			"verify firmware failed with %d\n", ret);
		release_firmware(fw);
		वापस ret;
	पूर्ण

	adf7242_cmd(lp, CMD_RC_PC_RESET);

	release_firmware(fw);

	adf7242_ग_लिखो_reg(lp, REG_FFILT_CFG,
			  ACCEPT_BEACON_FRAMES |
			  ACCEPT_DATA_FRAMES |
			  ACCEPT_MACCMD_FRAMES |
			  ACCEPT_RESERVED_FRAMES);

	adf7242_ग_लिखो_reg(lp, REG_AUTO_CFG, RX_AUTO_ACK_EN);

	adf7242_ग_लिखो_reg(lp, REG_PKT_CFG, ADDON_EN | BIT(2));

	adf7242_ग_लिखो_reg(lp, REG_EXTPA_MSC, 0xF1);
	adf7242_ग_लिखो_reg(lp, REG_RXFE_CFG, 0x1D);

	adf7242_ग_लिखो_reg(lp, REG_IRQ1_EN0, 0);
	adf7242_ग_लिखो_reg(lp, REG_IRQ1_EN1, IRQ_RX_PKT_RCVD | IRQ_CSMA_CA);

	adf7242_clear_irqstat(lp);
	adf7242_ग_लिखो_reg(lp, REG_IRQ1_SRC0, 0xFF);

	adf7242_cmd(lp, CMD_RC_IDLE);

	वापस 0;
पूर्ण

अटल पूर्णांक adf7242_stats_show(काष्ठा seq_file *file, व्योम *offset)
अणु
	काष्ठा adf7242_local *lp = spi_get_drvdata(file->निजी);
	u8 stat, irq1;

	adf7242_status(lp, &stat);
	adf7242_पढ़ो_reg(lp, REG_IRQ1_SRC1, &irq1);

	seq_म_लिखो(file, "IRQ1 = %X:\n%s%s%s%s%s%s%s%s\n", irq1,
		   irq1 & IRQ_CCA_COMPLETE ? "IRQ_CCA_COMPLETE\n" : "",
		   irq1 & IRQ_SFD_RX ? "IRQ_SFD_RX\n" : "",
		   irq1 & IRQ_SFD_TX ? "IRQ_SFD_TX\n" : "",
		   irq1 & IRQ_RX_PKT_RCVD ? "IRQ_RX_PKT_RCVD\n" : "",
		   irq1 & IRQ_TX_PKT_SENT ? "IRQ_TX_PKT_SENT\n" : "",
		   irq1 & IRQ_CSMA_CA ? "IRQ_CSMA_CA\n" : "",
		   irq1 & IRQ_FRAME_VALID ? "IRQ_FRAME_VALID\n" : "",
		   irq1 & IRQ_ADDRESS_VALID ? "IRQ_ADDRESS_VALID\n" : "");

	seq_म_लिखो(file, "STATUS = %X:\n%s\n%s\n%s\n%s\n%s%s%s%s%s\n", stat,
		   stat & STAT_SPI_READY ? "SPI_READY" : "SPI_BUSY",
		   stat & STAT_IRQ_STATUS ? "IRQ_PENDING" : "IRQ_CLEAR",
		   stat & STAT_RC_READY ? "RC_READY" : "RC_BUSY",
		   stat & STAT_CCA_RESULT ? "CHAN_IDLE" : "CHAN_BUSY",
		   (stat & 0xf) == RC_STATUS_IDLE ? "RC_STATUS_IDLE" : "",
		   (stat & 0xf) == RC_STATUS_MEAS ? "RC_STATUS_MEAS" : "",
		   (stat & 0xf) == RC_STATUS_PHY_RDY ? "RC_STATUS_PHY_RDY" : "",
		   (stat & 0xf) == RC_STATUS_RX ? "RC_STATUS_RX" : "",
		   (stat & 0xf) == RC_STATUS_TX ? "RC_STATUS_TX" : "");

	seq_म_लिखो(file, "RSSI = %d\n", lp->rssi);

	वापस 0;
पूर्ण

अटल व्योम adf7242_debugfs_init(काष्ठा adf7242_local *lp)
अणु
	अक्षर debugfs_dir_name[DNAME_INLINE_LEN + 1] = "adf7242-";

	म_जोड़न(debugfs_dir_name, dev_name(&lp->spi->dev), DNAME_INLINE_LEN);

	lp->debugfs_root = debugfs_create_dir(debugfs_dir_name, शून्य);

	debugfs_create_devm_seqfile(&lp->spi->dev, "status", lp->debugfs_root,
				    adf7242_stats_show);
पूर्ण

अटल स्थिर s32 adf7242_घातers[] = अणु
	500, 400, 300, 200, 100, 0, -100, -200, -300, -400, -500, -600, -700,
	-800, -900, -1000, -1100, -1200, -1300, -1400, -1500, -1600, -1700,
	-1800, -1900, -2000, -2100, -2200, -2300, -2400, -2500, -2600,
पूर्ण;

अटल स्थिर s32 adf7242_ed_levels[] = अणु
	-9000, -8900, -8800, -8700, -8600, -8500, -8400, -8300, -8200, -8100,
	-8000, -7900, -7800, -7700, -7600, -7500, -7400, -7300, -7200, -7100,
	-7000, -6900, -6800, -6700, -6600, -6500, -6400, -6300, -6200, -6100,
	-6000, -5900, -5800, -5700, -5600, -5500, -5400, -5300, -5200, -5100,
	-5000, -4900, -4800, -4700, -4600, -4500, -4400, -4300, -4200, -4100,
	-4000, -3900, -3800, -3700, -3600, -3500, -3400, -3200, -3100, -3000
पूर्ण;

अटल पूर्णांक adf7242_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ieee802154_hw *hw;
	काष्ठा adf7242_local *lp;
	पूर्णांक ret, irq_type;

	अगर (!spi->irq) अणु
		dev_err(&spi->dev, "no IRQ specified\n");
		वापस -EINVAL;
	पूर्ण

	hw = ieee802154_alloc_hw(माप(*lp), &adf7242_ops);
	अगर (!hw)
		वापस -ENOMEM;

	lp = hw->priv;
	lp->hw = hw;
	lp->spi = spi;

	hw->priv = lp;
	hw->parent = &spi->dev;
	hw->extra_tx_headroom = 0;

	/* We support only 2.4 Ghz */
	hw->phy->supported.channels[0] = 0x7FFF800;

	hw->flags = IEEE802154_HW_OMIT_CKSUM |
		    IEEE802154_HW_CSMA_PARAMS |
		    IEEE802154_HW_FRAME_RETRIES | IEEE802154_HW_AFILT |
		    IEEE802154_HW_PROMISCUOUS;

	hw->phy->flags = WPAN_PHY_FLAG_TXPOWER |
			 WPAN_PHY_FLAG_CCA_ED_LEVEL |
			 WPAN_PHY_FLAG_CCA_MODE;

	hw->phy->supported.cca_modes = BIT(NL802154_CCA_ENERGY);

	hw->phy->supported.cca_ed_levels = adf7242_ed_levels;
	hw->phy->supported.cca_ed_levels_size = ARRAY_SIZE(adf7242_ed_levels);

	hw->phy->cca.mode = NL802154_CCA_ENERGY;

	hw->phy->supported.tx_घातers = adf7242_घातers;
	hw->phy->supported.tx_घातers_size = ARRAY_SIZE(adf7242_घातers);

	hw->phy->supported.min_minbe = 0;
	hw->phy->supported.max_minbe = 8;

	hw->phy->supported.min_maxbe = 3;
	hw->phy->supported.max_maxbe = 8;

	hw->phy->supported.min_frame_retries = 0;
	hw->phy->supported.max_frame_retries = 15;

	hw->phy->supported.min_csma_backoffs = 0;
	hw->phy->supported.max_csma_backoffs = 5;

	ieee802154_अक्रमom_extended_addr(&hw->phy->perm_extended_addr);

	mutex_init(&lp->bmux);
	init_completion(&lp->tx_complete);

	/* Setup Status Message */
	lp->stat_xfer.len = 1;
	lp->stat_xfer.tx_buf = &lp->buf_stat_tx;
	lp->stat_xfer.rx_buf = &lp->buf_stat_rx;
	lp->buf_stat_tx = CMD_SPI_NOP;

	spi_message_init(&lp->stat_msg);
	spi_message_add_tail(&lp->stat_xfer, &lp->stat_msg);

	spi_set_drvdata(spi, lp);
	INIT_DELAYED_WORK(&lp->work, adf7242_rx_cal_work);
	lp->wqueue = alloc_ordered_workqueue(dev_name(&spi->dev),
					     WQ_MEM_RECLAIM);
	अगर (unlikely(!lp->wqueue)) अणु
		ret = -ENOMEM;
		जाओ err_alloc_wq;
	पूर्ण

	ret = adf7242_hw_init(lp);
	अगर (ret)
		जाओ err_hw_init;

	irq_type = irq_get_trigger_type(spi->irq);
	अगर (!irq_type)
		irq_type = IRQF_TRIGGER_HIGH;

	ret = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq, शून्य, adf7242_isr,
					irq_type | IRQF_ONESHOT,
					dev_name(&spi->dev), lp);
	अगर (ret)
		जाओ err_hw_init;

	disable_irq(spi->irq);

	ret = ieee802154_रेजिस्टर_hw(lp->hw);
	अगर (ret)
		जाओ err_hw_init;

	dev_set_drvdata(&spi->dev, lp);

	adf7242_debugfs_init(lp);

	dev_info(&spi->dev, "mac802154 IRQ-%d registered\n", spi->irq);

	वापस ret;

err_hw_init:
	destroy_workqueue(lp->wqueue);
err_alloc_wq:
	mutex_destroy(&lp->bmux);
	ieee802154_मुक्त_hw(lp->hw);

	वापस ret;
पूर्ण

अटल पूर्णांक adf7242_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा adf7242_local *lp = spi_get_drvdata(spi);

	debugfs_हटाओ_recursive(lp->debugfs_root);

	cancel_delayed_work_sync(&lp->work);
	destroy_workqueue(lp->wqueue);

	ieee802154_unरेजिस्टर_hw(lp->hw);
	mutex_destroy(&lp->bmux);
	ieee802154_मुक्त_hw(lp->hw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id adf7242_of_match[] = अणु
	अणु .compatible = "adi,adf7242", पूर्ण,
	अणु .compatible = "adi,adf7241", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adf7242_of_match);

अटल स्थिर काष्ठा spi_device_id adf7242_device_id[] = अणु
	अणु .name = "adf7242", पूर्ण,
	अणु .name = "adf7241", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, adf7242_device_id);

अटल काष्ठा spi_driver adf7242_driver = अणु
	.id_table = adf7242_device_id,
	.driver = अणु
		   .of_match_table = of_match_ptr(adf7242_of_match),
		   .name = "adf7242",
		   .owner = THIS_MODULE,
		   पूर्ण,
	.probe = adf7242_probe,
	.हटाओ = adf7242_हटाओ,
पूर्ण;

module_spi_driver(adf7242_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("ADF7242 IEEE802.15.4 Transceiver Driver");
MODULE_LICENSE("GPL");
