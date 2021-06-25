<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  i2c Support क्रम Aपंचांगel's AT91 Two-Wire Interface (TWI)
 *
 *  Copyright (C) 2011 Weinmann Medical GmbH
 *  Author: Nikolaus Voss <n.voss@weinmann.de>
 *
 *  Evolved from original work by:
 *  Copyright (C) 2004 Rick Bronson
 *  Converted to 2.6 by Andrew Victor <andrew@sanpeople.com>
 *
 *  Borrowed heavily from original work by:
 *  Copyright (C) 2000 Philip Edelbrock <phil@stimpy.netroedge.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा AT91_I2C_TIMEOUT	msecs_to_jअगरfies(100)	/* transfer समयout */
#घोषणा AT91_I2C_DMA_THRESHOLD	8			/* enable DMA अगर transfer size is bigger than this threshold */
#घोषणा AUTOSUSPEND_TIMEOUT		2000
#घोषणा AT91_I2C_MAX_ALT_CMD_DATA_SIZE	256

/* AT91 TWI रेजिस्टर definitions */
#घोषणा	AT91_TWI_CR		0x0000	/* Control Register */
#घोषणा	AT91_TWI_START		BIT(0)	/* Send a Start Condition */
#घोषणा	AT91_TWI_STOP		BIT(1)	/* Send a Stop Condition */
#घोषणा	AT91_TWI_MSEN		BIT(2)	/* Master Transfer Enable */
#घोषणा	AT91_TWI_MSDIS		BIT(3)	/* Master Transfer Disable */
#घोषणा	AT91_TWI_SVEN		BIT(4)	/* Slave Transfer Enable */
#घोषणा	AT91_TWI_SVDIS		BIT(5)	/* Slave Transfer Disable */
#घोषणा	AT91_TWI_QUICK		BIT(6)	/* SMBus quick command */
#घोषणा	AT91_TWI_SWRST		BIT(7)	/* Software Reset */
#घोषणा	AT91_TWI_CLEAR		BIT(15) /* Bus clear command */
#घोषणा	AT91_TWI_ACMEN		BIT(16) /* Alternative Command Mode Enable */
#घोषणा	AT91_TWI_ACMDIS		BIT(17) /* Alternative Command Mode Disable */
#घोषणा	AT91_TWI_THRCLR		BIT(24) /* Transmit Holding Register Clear */
#घोषणा	AT91_TWI_RHRCLR		BIT(25) /* Receive Holding Register Clear */
#घोषणा	AT91_TWI_LOCKCLR	BIT(26) /* Lock Clear */
#घोषणा	AT91_TWI_FIFOEN		BIT(28) /* FIFO Enable */
#घोषणा	AT91_TWI_FIFODIS	BIT(29) /* FIFO Disable */

#घोषणा	AT91_TWI_MMR		0x0004	/* Master Mode Register */
#घोषणा	AT91_TWI_IADRSZ_1	0x0100	/* Internal Device Address Size */
#घोषणा	AT91_TWI_MREAD		BIT(12)	/* Master Read Direction */

#घोषणा	AT91_TWI_SMR		0x0008	/* Slave Mode Register */
#घोषणा	AT91_TWI_SMR_SADR_MAX	0x007f
#घोषणा	AT91_TWI_SMR_SADR(x)	(((x) & AT91_TWI_SMR_SADR_MAX) << 16)

#घोषणा	AT91_TWI_IADR		0x000c	/* Internal Address Register */

#घोषणा	AT91_TWI_CWGR		0x0010	/* Clock Waveक्रमm Generator Reg */
#घोषणा	AT91_TWI_CWGR_HOLD_MAX	0x1f
#घोषणा	AT91_TWI_CWGR_HOLD(x)	(((x) & AT91_TWI_CWGR_HOLD_MAX) << 24)

#घोषणा	AT91_TWI_SR		0x0020	/* Status Register */
#घोषणा	AT91_TWI_TXCOMP		BIT(0)	/* Transmission Complete */
#घोषणा	AT91_TWI_RXRDY		BIT(1)	/* Receive Holding Register Ready */
#घोषणा	AT91_TWI_TXRDY		BIT(2)	/* Transmit Holding Register Ready */
#घोषणा	AT91_TWI_SVREAD		BIT(3)	/* Slave Read */
#घोषणा	AT91_TWI_SVACC		BIT(4)	/* Slave Access */
#घोषणा	AT91_TWI_OVRE		BIT(6)	/* Overrun Error */
#घोषणा	AT91_TWI_UNRE		BIT(7)	/* Underrun Error */
#घोषणा	AT91_TWI_NACK		BIT(8)	/* Not Acknowledged */
#घोषणा	AT91_TWI_EOSACC		BIT(11)	/* End Of Slave Access */
#घोषणा	AT91_TWI_LOCK		BIT(23) /* TWI Lock due to Frame Errors */
#घोषणा	AT91_TWI_SCL		BIT(24) /* TWI SCL status */
#घोषणा	AT91_TWI_SDA		BIT(25) /* TWI SDA status */

#घोषणा	AT91_TWI_INT_MASK \
	(AT91_TWI_TXCOMP | AT91_TWI_RXRDY | AT91_TWI_TXRDY | AT91_TWI_NACK \
	| AT91_TWI_SVACC | AT91_TWI_EOSACC)

#घोषणा	AT91_TWI_IER		0x0024	/* Interrupt Enable Register */
#घोषणा	AT91_TWI_IDR		0x0028	/* Interrupt Disable Register */
#घोषणा	AT91_TWI_IMR		0x002c	/* Interrupt Mask Register */
#घोषणा	AT91_TWI_RHR		0x0030	/* Receive Holding Register */
#घोषणा	AT91_TWI_THR		0x0034	/* Transmit Holding Register */

#घोषणा	AT91_TWI_ACR		0x0040	/* Alternative Command Register */
#घोषणा	AT91_TWI_ACR_DATAL_MASK	GENMASK(15, 0)
#घोषणा	AT91_TWI_ACR_DATAL(len)	((len) & AT91_TWI_ACR_DATAL_MASK)
#घोषणा	AT91_TWI_ACR_सूची	BIT(8)

#घोषणा AT91_TWI_FILTR		0x0044
#घोषणा AT91_TWI_FILTR_FILT	BIT(0)
#घोषणा AT91_TWI_FILTR_PADFEN	BIT(1)
#घोषणा AT91_TWI_FILTR_THRES(v)		((v) << 8)
#घोषणा AT91_TWI_FILTR_THRES_MAX	7
#घोषणा AT91_TWI_FILTR_THRES_MASK	GENMASK(10, 8)

#घोषणा	AT91_TWI_FMR		0x0050	/* FIFO Mode Register */
#घोषणा	AT91_TWI_FMR_TXRDYM(mode)	(((mode) & 0x3) << 0)
#घोषणा	AT91_TWI_FMR_TXRDYM_MASK	(0x3 << 0)
#घोषणा	AT91_TWI_FMR_RXRDYM(mode)	(((mode) & 0x3) << 4)
#घोषणा	AT91_TWI_FMR_RXRDYM_MASK	(0x3 << 4)
#घोषणा	AT91_TWI_ONE_DATA	0x0
#घोषणा	AT91_TWI_TWO_DATA	0x1
#घोषणा	AT91_TWI_FOUR_DATA	0x2

#घोषणा	AT91_TWI_FLR		0x0054	/* FIFO Level Register */

#घोषणा	AT91_TWI_FSR		0x0060	/* FIFO Status Register */
#घोषणा	AT91_TWI_FIER		0x0064	/* FIFO Interrupt Enable Register */
#घोषणा	AT91_TWI_FIDR		0x0068	/* FIFO Interrupt Disable Register */
#घोषणा	AT91_TWI_FIMR		0x006c	/* FIFO Interrupt Mask Register */

#घोषणा	AT91_TWI_VER		0x00fc	/* Version Register */

काष्ठा at91_twi_pdata अणु
	अचिन्हित clk_max_भाग;
	अचिन्हित clk_offset;
	bool has_unre_flag;
	bool has_alt_cmd;
	bool has_hold_field;
	bool has_dig_filtr;
	bool has_adv_dig_filtr;
	bool has_ana_filtr;
	bool has_clear_cmd;
पूर्ण;

काष्ठा at91_twi_dma अणु
	काष्ठा dma_chan *chan_rx;
	काष्ठा dma_chan *chan_tx;
	काष्ठा scatterlist sg[2];
	काष्ठा dma_async_tx_descriptor *data_desc;
	क्रमागत dma_data_direction direction;
	bool buf_mapped;
	bool xfer_in_progress;
पूर्ण;

काष्ठा at91_twi_dev अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा completion cmd_complete;
	काष्ठा clk *clk;
	u8 *buf;
	माप_प्रकार buf_len;
	काष्ठा i2c_msg *msg;
	पूर्णांक irq;
	अचिन्हित imr;
	अचिन्हित transfer_status;
	काष्ठा i2c_adapter adapter;
	अचिन्हित twi_cwgr_reg;
	काष्ठा at91_twi_pdata *pdata;
	bool use_dma;
	bool use_alt_cmd;
	bool recv_len_पात;
	u32 fअगरo_size;
	काष्ठा at91_twi_dma dma;
	bool slave_detected;
	काष्ठा i2c_bus_recovery_info rinfo;
#अगर_घोषित CONFIG_I2C_AT91_SLAVE_EXPERIMENTAL
	अचिन्हित smr;
	काष्ठा i2c_client *slave;
#पूर्ण_अगर
	bool enable_dig_filt;
	bool enable_ana_filt;
	u32 filter_width;
पूर्ण;

अचिन्हित at91_twi_पढ़ो(काष्ठा at91_twi_dev *dev, अचिन्हित reg);
व्योम at91_twi_ग_लिखो(काष्ठा at91_twi_dev *dev, अचिन्हित reg, अचिन्हित val);
व्योम at91_disable_twi_पूर्णांकerrupts(काष्ठा at91_twi_dev *dev);
व्योम at91_twi_irq_save(काष्ठा at91_twi_dev *dev);
व्योम at91_twi_irq_restore(काष्ठा at91_twi_dev *dev);
व्योम at91_init_twi_bus(काष्ठा at91_twi_dev *dev);

व्योम at91_init_twi_bus_master(काष्ठा at91_twi_dev *dev);
पूर्णांक at91_twi_probe_master(काष्ठा platक्रमm_device *pdev, u32 phy_addr,
			  काष्ठा at91_twi_dev *dev);

#अगर_घोषित CONFIG_I2C_AT91_SLAVE_EXPERIMENTAL
व्योम at91_init_twi_bus_slave(काष्ठा at91_twi_dev *dev);
पूर्णांक at91_twi_probe_slave(काष्ठा platक्रमm_device *pdev, u32 phy_addr,
			 काष्ठा at91_twi_dev *dev);

#अन्यथा
अटल अंतरभूत व्योम at91_init_twi_bus_slave(काष्ठा at91_twi_dev *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक at91_twi_probe_slave(काष्ठा platक्रमm_device *pdev,
				       u32 phy_addr, काष्ठा at91_twi_dev *dev)
अणु
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर
