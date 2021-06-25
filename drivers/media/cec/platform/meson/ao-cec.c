<शैली गुरु>
/*
 * Driver क्रम Amlogic Meson AO CEC Controller
 *
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved
 * Copyright (C) 2017 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 * SPDX-License-Identअगरier: GPL-2.0+
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reset.h>
#समावेश <media/cec.h>
#समावेश <media/cec-notअगरier.h>

/* CEC Registers */

/*
 * [2:1] cntl_clk
 *  - 0 = Disable clk (Power-off mode)
 *  - 1 = Enable gated घड़ी (Normal mode)
 *  - 2 = Enable मुक्त-run clk (Debug mode)
 */
#घोषणा CEC_GEN_CNTL_REG		0x00

#घोषणा CEC_GEN_CNTL_RESET		BIT(0)
#घोषणा CEC_GEN_CNTL_CLK_DISABLE	0
#घोषणा CEC_GEN_CNTL_CLK_ENABLE		1
#घोषणा CEC_GEN_CNTL_CLK_ENABLE_DBG	2
#घोषणा CEC_GEN_CNTL_CLK_CTRL_MASK	GENMASK(2, 1)

/*
 * [7:0] cec_reg_addr
 * [15:8] cec_reg_wrdata
 * [16] cec_reg_wr
 *  - 0 = Read
 *  - 1 = Write
 * [23] bus मुक्त
 * [31:24] cec_reg_rddata
 */
#घोषणा CEC_RW_REG			0x04

#घोषणा CEC_RW_ADDR			GENMASK(7, 0)
#घोषणा CEC_RW_WR_DATA			GENMASK(15, 8)
#घोषणा CEC_RW_WRITE_EN			BIT(16)
#घोषणा CEC_RW_BUS_BUSY			BIT(23)
#घोषणा CEC_RW_RD_DATA			GENMASK(31, 24)

/*
 * [1] tx पूर्णांकr
 * [2] rx पूर्णांकr
 */
#घोषणा CEC_INTR_MASKN_REG		0x08
#घोषणा CEC_INTR_CLR_REG		0x0c
#घोषणा CEC_INTR_STAT_REG		0x10

#घोषणा CEC_INTR_TX			BIT(1)
#घोषणा CEC_INTR_RX			BIT(2)

/* CEC Commands */

#घोषणा CEC_TX_MSG_0_HEADER		0x00
#घोषणा CEC_TX_MSG_1_OPCODE		0x01
#घोषणा CEC_TX_MSG_2_OP1		0x02
#घोषणा CEC_TX_MSG_3_OP2		0x03
#घोषणा CEC_TX_MSG_4_OP3		0x04
#घोषणा CEC_TX_MSG_5_OP4		0x05
#घोषणा CEC_TX_MSG_6_OP5		0x06
#घोषणा CEC_TX_MSG_7_OP6		0x07
#घोषणा CEC_TX_MSG_8_OP7		0x08
#घोषणा CEC_TX_MSG_9_OP8		0x09
#घोषणा CEC_TX_MSG_A_OP9		0x0A
#घोषणा CEC_TX_MSG_B_OP10		0x0B
#घोषणा CEC_TX_MSG_C_OP11		0x0C
#घोषणा CEC_TX_MSG_D_OP12		0x0D
#घोषणा CEC_TX_MSG_E_OP13		0x0E
#घोषणा CEC_TX_MSG_F_OP14		0x0F
#घोषणा CEC_TX_MSG_LENGTH		0x10
#घोषणा CEC_TX_MSG_CMD			0x11
#घोषणा CEC_TX_WRITE_BUF		0x12
#घोषणा CEC_TX_CLEAR_BUF		0x13
#घोषणा CEC_RX_MSG_CMD			0x14
#घोषणा CEC_RX_CLEAR_BUF		0x15
#घोषणा CEC_LOGICAL_ADDR0		0x16
#घोषणा CEC_LOGICAL_ADDR1		0x17
#घोषणा CEC_LOGICAL_ADDR2		0x18
#घोषणा CEC_LOGICAL_ADDR3		0x19
#घोषणा CEC_LOGICAL_ADDR4		0x1A
#घोषणा CEC_CLOCK_DIV_H			0x1B
#घोषणा CEC_CLOCK_DIV_L			0x1C
#घोषणा CEC_QUIESCENT_25MS_BIT7_0	0x20
#घोषणा CEC_QUIESCENT_25MS_BIT11_8	0x21
#घोषणा CEC_STARTBITMINL2H_3MS5_BIT7_0	0x22
#घोषणा CEC_STARTBITMINL2H_3MS5_BIT8	0x23
#घोषणा CEC_STARTBITMAXL2H_3MS9_BIT7_0	0x24
#घोषणा CEC_STARTBITMAXL2H_3MS9_BIT8	0x25
#घोषणा CEC_STARTBITMINH_0MS6_BIT7_0	0x26
#घोषणा CEC_STARTBITMINH_0MS6_BIT8	0x27
#घोषणा CEC_STARTBITMAXH_1MS0_BIT7_0	0x28
#घोषणा CEC_STARTBITMAXH_1MS0_BIT8	0x29
#घोषणा CEC_STARTBITMINTOT_4MS3_BIT7_0	0x2A
#घोषणा CEC_STARTBITMINTOT_4MS3_BIT9_8	0x2B
#घोषणा CEC_STARTBITMAXTOT_4MS7_BIT7_0	0x2C
#घोषणा CEC_STARTBITMAXTOT_4MS7_BIT9_8	0x2D
#घोषणा CEC_LOGIC1MINL2H_0MS4_BIT7_0	0x2E
#घोषणा CEC_LOGIC1MINL2H_0MS4_BIT8	0x2F
#घोषणा CEC_LOGIC1MAXL2H_0MS8_BIT7_0	0x30
#घोषणा CEC_LOGIC1MAXL2H_0MS8_BIT8	0x31
#घोषणा CEC_LOGIC0MINL2H_1MS3_BIT7_0	0x32
#घोषणा CEC_LOGIC0MINL2H_1MS3_BIT8	0x33
#घोषणा CEC_LOGIC0MAXL2H_1MS7_BIT7_0	0x34
#घोषणा CEC_LOGIC0MAXL2H_1MS7_BIT8	0x35
#घोषणा CEC_LOGICMINTOTAL_2MS05_BIT7_0	0x36
#घोषणा CEC_LOGICMINTOTAL_2MS05_BIT9_8	0x37
#घोषणा CEC_LOGICMAXHIGH_2MS8_BIT7_0	0x38
#घोषणा CEC_LOGICMAXHIGH_2MS8_BIT8	0x39
#घोषणा CEC_LOGICERRLOW_3MS4_BIT7_0	0x3A
#घोषणा CEC_LOGICERRLOW_3MS4_BIT8	0x3B
#घोषणा CEC_NOMSMPPOINT_1MS05		0x3C
#घोषणा CEC_DELCNTR_LOGICERR		0x3E
#घोषणा CEC_TXTIME_17MS_BIT7_0		0x40
#घोषणा CEC_TXTIME_17MS_BIT10_8		0x41
#घोषणा CEC_TXTIME_2BIT_BIT7_0		0x42
#घोषणा CEC_TXTIME_2BIT_BIT10_8		0x43
#घोषणा CEC_TXTIME_4BIT_BIT7_0		0x44
#घोषणा CEC_TXTIME_4BIT_BIT10_8		0x45
#घोषणा CEC_STARTBITNOML2H_3MS7_BIT7_0	0x46
#घोषणा CEC_STARTBITNOML2H_3MS7_BIT8	0x47
#घोषणा CEC_STARTBITNOMH_0MS8_BIT7_0	0x48
#घोषणा CEC_STARTBITNOMH_0MS8_BIT8	0x49
#घोषणा CEC_LOGIC1NOML2H_0MS6_BIT7_0	0x4A
#घोषणा CEC_LOGIC1NOML2H_0MS6_BIT8	0x4B
#घोषणा CEC_LOGIC0NOML2H_1MS5_BIT7_0	0x4C
#घोषणा CEC_LOGIC0NOML2H_1MS5_BIT8	0x4D
#घोषणा CEC_LOGIC1NOMH_1MS8_BIT7_0	0x4E
#घोषणा CEC_LOGIC1NOMH_1MS8_BIT8	0x4F
#घोषणा CEC_LOGIC0NOMH_0MS9_BIT7_0	0x50
#घोषणा CEC_LOGIC0NOMH_0MS9_BIT8	0x51
#घोषणा CEC_LOGICERRLOW_3MS6_BIT7_0	0x52
#घोषणा CEC_LOGICERRLOW_3MS6_BIT8	0x53
#घोषणा CEC_CHKCONTENTION_0MS1		0x54
#घोषणा CEC_PREPARENXTBIT_0MS05_BIT7_0	0x56
#घोषणा CEC_PREPARENXTBIT_0MS05_BIT8	0x57
#घोषणा CEC_NOMSMPACKPOINT_0MS45	0x58
#घोषणा CEC_ACK0NOML2H_1MS5_BIT7_0	0x5A
#घोषणा CEC_ACK0NOML2H_1MS5_BIT8	0x5B
#घोषणा CEC_BUGFIX_DISABLE_0		0x60
#घोषणा CEC_BUGFIX_DISABLE_1		0x61
#घोषणा CEC_RX_MSG_0_HEADER		0x80
#घोषणा CEC_RX_MSG_1_OPCODE		0x81
#घोषणा CEC_RX_MSG_2_OP1		0x82
#घोषणा CEC_RX_MSG_3_OP2		0x83
#घोषणा CEC_RX_MSG_4_OP3		0x84
#घोषणा CEC_RX_MSG_5_OP4		0x85
#घोषणा CEC_RX_MSG_6_OP5		0x86
#घोषणा CEC_RX_MSG_7_OP6		0x87
#घोषणा CEC_RX_MSG_8_OP7		0x88
#घोषणा CEC_RX_MSG_9_OP8		0x89
#घोषणा CEC_RX_MSG_A_OP9		0x8A
#घोषणा CEC_RX_MSG_B_OP10		0x8B
#घोषणा CEC_RX_MSG_C_OP11		0x8C
#घोषणा CEC_RX_MSG_D_OP12		0x8D
#घोषणा CEC_RX_MSG_E_OP13		0x8E
#घोषणा CEC_RX_MSG_F_OP14		0x8F
#घोषणा CEC_RX_MSG_LENGTH		0x90
#घोषणा CEC_RX_MSG_STATUS		0x91
#घोषणा CEC_RX_NUM_MSG			0x92
#घोषणा CEC_TX_MSG_STATUS		0x93
#घोषणा CEC_TX_NUM_MSG			0x94


/* CEC_TX_MSG_CMD definition */
#घोषणा TX_NO_OP	0  /* No transaction */
#घोषणा TX_REQ_CURRENT	1  /* Transmit earliest message in buffer */
#घोषणा TX_ABORT	2  /* Abort transmitting earliest message */
#घोषणा TX_REQ_NEXT	3  /* Overग_लिखो earliest msg, transmit next */

/* tx_msg_status definition */
#घोषणा TX_IDLE		0  /* No transaction */
#घोषणा TX_BUSY		1  /* Transmitter is busy */
#घोषणा TX_DONE		2  /* Message successfully transmitted */
#घोषणा TX_ERROR	3  /* Message transmitted with error */

/* rx_msg_cmd */
#घोषणा RX_NO_OP	0  /* No transaction */
#घोषणा RX_ACK_CURRENT	1  /* Read earliest message in buffer */
#घोषणा RX_DISABLE	2  /* Disable receiving latest message */
#घोषणा RX_ACK_NEXT	3  /* Clear earliest msg, पढ़ो next */

/* rx_msg_status */
#घोषणा RX_IDLE		0  /* No transaction */
#घोषणा RX_BUSY		1  /* Receiver is busy */
#घोषणा RX_DONE		2  /* Message has been received successfully */
#घोषणा RX_ERROR	3  /* Message has been received with error */

/* RX_CLEAR_BUF options */
#घोषणा CLEAR_START	1
#घोषणा CLEAR_STOP	0

/* CEC_LOGICAL_ADDRx options */
#घोषणा LOGICAL_ADDR_MASK	0xf
#घोषणा LOGICAL_ADDR_VALID	BIT(4)
#घोषणा LOGICAL_ADDR_DISABLE	0

#घोषणा CEC_CLK_RATE		32768

काष्ठा meson_ao_cec_device अणु
	काष्ठा platक्रमm_device		*pdev;
	व्योम __iomem			*base;
	काष्ठा clk			*core;
	spinlock_t			cec_reg_lock;
	काष्ठा cec_notअगरier		*notअगरy;
	काष्ठा cec_adapter		*adap;
	काष्ठा cec_msg			rx_msg;
पूर्ण;

#घोषणा ग_लिखोl_bits_relaxed(mask, val, addr) \
	ग_लिखोl_relaxed((पढ़ोl_relaxed(addr) & ~(mask)) | (val), addr)

अटल अंतरभूत पूर्णांक meson_ao_cec_रुको_busy(काष्ठा meson_ao_cec_device *ao_cec)
अणु
	kसमय_प्रकार समयout = kसमय_add_us(kसमय_get(), 5000);

	जबतक (पढ़ोl_relaxed(ao_cec->base + CEC_RW_REG) & CEC_RW_BUS_BUSY) अणु
		अगर (kसमय_compare(kसमय_get(), समयout) > 0)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम meson_ao_cec_पढ़ो(काष्ठा meson_ao_cec_device *ao_cec,
			     अचिन्हित दीर्घ address, u8 *data,
			     पूर्णांक *res)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg = FIELD_PREP(CEC_RW_ADDR, address);
	पूर्णांक ret = 0;

	अगर (res && *res)
		वापस;

	spin_lock_irqsave(&ao_cec->cec_reg_lock, flags);

	ret = meson_ao_cec_रुको_busy(ao_cec);
	अगर (ret)
		जाओ पढ़ो_out;

	ग_लिखोl_relaxed(reg, ao_cec->base + CEC_RW_REG);

	ret = meson_ao_cec_रुको_busy(ao_cec);
	अगर (ret)
		जाओ पढ़ो_out;

	*data = FIELD_GET(CEC_RW_RD_DATA,
			  पढ़ोl_relaxed(ao_cec->base + CEC_RW_REG));

पढ़ो_out:
	spin_unlock_irqrestore(&ao_cec->cec_reg_lock, flags);

	अगर (res)
		*res = ret;
पूर्ण

अटल व्योम meson_ao_cec_ग_लिखो(काष्ठा meson_ao_cec_device *ao_cec,
			       अचिन्हित दीर्घ address, u8 data,
			       पूर्णांक *res)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg = FIELD_PREP(CEC_RW_ADDR, address) |
		  FIELD_PREP(CEC_RW_WR_DATA, data) |
		  CEC_RW_WRITE_EN;
	पूर्णांक ret = 0;

	अगर (res && *res)
		वापस;

	spin_lock_irqsave(&ao_cec->cec_reg_lock, flags);

	ret = meson_ao_cec_रुको_busy(ao_cec);
	अगर (ret)
		जाओ ग_लिखो_out;

	ग_लिखोl_relaxed(reg, ao_cec->base + CEC_RW_REG);

ग_लिखो_out:
	spin_unlock_irqrestore(&ao_cec->cec_reg_lock, flags);

	अगर (res)
		*res = ret;
पूर्ण

अटल अंतरभूत व्योम meson_ao_cec_irq_setup(काष्ठा meson_ao_cec_device *ao_cec,
				      bool enable)
अणु
	u32 cfg = CEC_INTR_TX | CEC_INTR_RX;

	ग_लिखोl_bits_relaxed(cfg, enable ? cfg : 0,
			    ao_cec->base + CEC_INTR_MASKN_REG);
पूर्ण

अटल अंतरभूत पूर्णांक meson_ao_cec_clear(काष्ठा meson_ao_cec_device *ao_cec)
अणु
	पूर्णांक ret = 0;

	meson_ao_cec_ग_लिखो(ao_cec, CEC_RX_MSG_CMD, RX_DISABLE, &ret);
	meson_ao_cec_ग_लिखो(ao_cec, CEC_TX_MSG_CMD, TX_ABORT, &ret);
	meson_ao_cec_ग_लिखो(ao_cec, CEC_RX_CLEAR_BUF, 1, &ret);
	meson_ao_cec_ग_लिखो(ao_cec, CEC_TX_CLEAR_BUF, 1, &ret);
	अगर (ret)
		वापस ret;

	udelay(100);

	meson_ao_cec_ग_लिखो(ao_cec, CEC_RX_CLEAR_BUF, 0, &ret);
	meson_ao_cec_ग_लिखो(ao_cec, CEC_TX_CLEAR_BUF, 0, &ret);
	अगर (ret)
		वापस ret;

	udelay(100);

	meson_ao_cec_ग_लिखो(ao_cec, CEC_RX_MSG_CMD, RX_NO_OP, &ret);
	meson_ao_cec_ग_लिखो(ao_cec, CEC_TX_MSG_CMD, TX_NO_OP, &ret);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_ao_cec_arbit_bit_समय_set(काष्ठा meson_ao_cec_device *ao_cec,
					   अचिन्हित पूर्णांक bit_set,
					   अचिन्हित पूर्णांक समय_set)
अणु
	पूर्णांक ret = 0;

	चयन (bit_set) अणु
	हाल CEC_SIGNAL_FREE_TIME_RETRY:
		meson_ao_cec_ग_लिखो(ao_cec, CEC_TXTIME_4BIT_BIT7_0,
				   समय_set & 0xff, &ret);
		meson_ao_cec_ग_लिखो(ao_cec, CEC_TXTIME_4BIT_BIT10_8,
				   (समय_set >> 8) & 0x7, &ret);
		अवरोध;

	हाल CEC_SIGNAL_FREE_TIME_NEW_INITIATOR:
		meson_ao_cec_ग_लिखो(ao_cec, CEC_TXTIME_2BIT_BIT7_0,
				   समय_set & 0xff, &ret);
		meson_ao_cec_ग_लिखो(ao_cec, CEC_TXTIME_2BIT_BIT10_8,
				   (समय_set >> 8) & 0x7, &ret);
		अवरोध;

	हाल CEC_SIGNAL_FREE_TIME_NEXT_XFER:
		meson_ao_cec_ग_लिखो(ao_cec, CEC_TXTIME_17MS_BIT7_0,
				   समय_set & 0xff, &ret);
		meson_ao_cec_ग_लिखो(ao_cec, CEC_TXTIME_17MS_BIT10_8,
				   (समय_set >> 8) & 0x7, &ret);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t meson_ao_cec_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा meson_ao_cec_device *ao_cec = data;
	u32 stat = पढ़ोl_relaxed(ao_cec->base + CEC_INTR_STAT_REG);

	अगर (stat)
		वापस IRQ_WAKE_THREAD;

	वापस IRQ_NONE;
पूर्ण

अटल व्योम meson_ao_cec_irq_tx(काष्ठा meson_ao_cec_device *ao_cec)
अणु
	अचिन्हित दीर्घ tx_status = 0;
	u8 stat;
	पूर्णांक ret = 0;

	meson_ao_cec_पढ़ो(ao_cec, CEC_TX_MSG_STATUS, &stat, &ret);
	अगर (ret)
		जाओ tx_reg_err;

	चयन (stat) अणु
	हाल TX_DONE:
		tx_status = CEC_TX_STATUS_OK;
		अवरोध;

	हाल TX_BUSY:
		tx_status = CEC_TX_STATUS_ARB_LOST;
		अवरोध;

	हाल TX_IDLE:
		tx_status = CEC_TX_STATUS_LOW_DRIVE;
		अवरोध;

	हाल TX_ERROR:
	शेष:
		tx_status = CEC_TX_STATUS_NACK;
		अवरोध;
	पूर्ण

	/* Clear Interruption */
	ग_लिखोl_relaxed(CEC_INTR_TX, ao_cec->base + CEC_INTR_CLR_REG);

	/* Stop TX */
	meson_ao_cec_ग_लिखो(ao_cec, CEC_TX_MSG_CMD, TX_NO_OP, &ret);
	अगर (ret)
		जाओ tx_reg_err;

	cec_transmit_attempt_करोne(ao_cec->adap, tx_status);
	वापस;

tx_reg_err:
	cec_transmit_attempt_करोne(ao_cec->adap, CEC_TX_STATUS_ERROR);
पूर्ण

अटल व्योम meson_ao_cec_irq_rx(काष्ठा meson_ao_cec_device *ao_cec)
अणु
	पूर्णांक i, ret = 0;
	u8 reg;

	meson_ao_cec_पढ़ो(ao_cec, CEC_RX_MSG_STATUS, &reg, &ret);
	अगर (reg != RX_DONE)
		जाओ rx_out;

	meson_ao_cec_पढ़ो(ao_cec, CEC_RX_NUM_MSG, &reg, &ret);
	अगर (reg != 1)
		जाओ rx_out;

	meson_ao_cec_पढ़ो(ao_cec, CEC_RX_MSG_LENGTH, &reg, &ret);

	ao_cec->rx_msg.len = reg + 1;
	अगर (ao_cec->rx_msg.len > CEC_MAX_MSG_SIZE)
		ao_cec->rx_msg.len = CEC_MAX_MSG_SIZE;

	क्रम (i = 0; i < ao_cec->rx_msg.len; i++) अणु
		u8 byte;

		meson_ao_cec_पढ़ो(ao_cec, CEC_RX_MSG_0_HEADER + i, &byte, &ret);

		ao_cec->rx_msg.msg[i] = byte;
	पूर्ण

	अगर (ret)
		जाओ rx_out;

	cec_received_msg(ao_cec->adap, &ao_cec->rx_msg);

rx_out:
	/* Clear Interruption */
	ग_लिखोl_relaxed(CEC_INTR_RX, ao_cec->base + CEC_INTR_CLR_REG);

	/* Ack RX message */
	meson_ao_cec_ग_लिखो(ao_cec, CEC_RX_MSG_CMD, RX_ACK_CURRENT, &ret);
	meson_ao_cec_ग_लिखो(ao_cec, CEC_RX_MSG_CMD, RX_NO_OP, &ret);

	/* Clear RX buffer */
	meson_ao_cec_ग_लिखो(ao_cec, CEC_RX_CLEAR_BUF, CLEAR_START, &ret);
	meson_ao_cec_ग_लिखो(ao_cec, CEC_RX_CLEAR_BUF, CLEAR_STOP, &ret);
पूर्ण

अटल irqवापस_t meson_ao_cec_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा meson_ao_cec_device *ao_cec = data;
	u32 stat = पढ़ोl_relaxed(ao_cec->base + CEC_INTR_STAT_REG);

	अगर (stat & CEC_INTR_TX)
		meson_ao_cec_irq_tx(ao_cec);

	meson_ao_cec_irq_rx(ao_cec);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक meson_ao_cec_set_log_addr(काष्ठा cec_adapter *adap, u8 logical_addr)
अणु
	काष्ठा meson_ao_cec_device *ao_cec = adap->priv;
	पूर्णांक ret = 0;

	meson_ao_cec_ग_लिखो(ao_cec, CEC_LOGICAL_ADDR0,
			   LOGICAL_ADDR_DISABLE, &ret);
	अगर (ret)
		वापस ret;

	ret = meson_ao_cec_clear(ao_cec);
	अगर (ret)
		वापस ret;

	अगर (logical_addr == CEC_LOG_ADDR_INVALID)
		वापस 0;

	meson_ao_cec_ग_लिखो(ao_cec, CEC_LOGICAL_ADDR0,
			   logical_addr & LOGICAL_ADDR_MASK, &ret);
	अगर (ret)
		वापस ret;

	udelay(100);

	meson_ao_cec_ग_लिखो(ao_cec, CEC_LOGICAL_ADDR0,
			   (logical_addr & LOGICAL_ADDR_MASK) |
			   LOGICAL_ADDR_VALID, &ret);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_ao_cec_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				 u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा meson_ao_cec_device *ao_cec = adap->priv;
	पूर्णांक i, ret = 0;
	u8 reg;

	meson_ao_cec_पढ़ो(ao_cec, CEC_TX_MSG_STATUS, &reg, &ret);
	अगर (ret)
		वापस ret;

	अगर (reg == TX_BUSY) अणु
		dev_dbg(&ao_cec->pdev->dev, "%s: busy TX: aborting\n",
			__func__);
		meson_ao_cec_ग_लिखो(ao_cec, CEC_TX_MSG_CMD, TX_ABORT, &ret);
	पूर्ण

	क्रम (i = 0; i < msg->len; i++) अणु
		meson_ao_cec_ग_लिखो(ao_cec, CEC_TX_MSG_0_HEADER + i,
				   msg->msg[i], &ret);
	पूर्ण

	meson_ao_cec_ग_लिखो(ao_cec, CEC_TX_MSG_LENGTH, msg->len - 1, &ret);
	meson_ao_cec_ग_लिखो(ao_cec, CEC_TX_MSG_CMD, TX_REQ_CURRENT, &ret);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_ao_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा meson_ao_cec_device *ao_cec = adap->priv;
	पूर्णांक ret;

	meson_ao_cec_irq_setup(ao_cec, false);

	ग_लिखोl_bits_relaxed(CEC_GEN_CNTL_RESET, CEC_GEN_CNTL_RESET,
			    ao_cec->base + CEC_GEN_CNTL_REG);

	अगर (!enable)
		वापस 0;

	/* Enable gated घड़ी (Normal mode). */
	ग_लिखोl_bits_relaxed(CEC_GEN_CNTL_CLK_CTRL_MASK,
			    FIELD_PREP(CEC_GEN_CNTL_CLK_CTRL_MASK,
				       CEC_GEN_CNTL_CLK_ENABLE),
			    ao_cec->base + CEC_GEN_CNTL_REG);

	udelay(100);

	/* Release Reset */
	ग_लिखोl_bits_relaxed(CEC_GEN_CNTL_RESET, 0,
			    ao_cec->base + CEC_GEN_CNTL_REG);

	/* Clear buffers */
	ret = meson_ao_cec_clear(ao_cec);
	अगर (ret)
		वापस ret;

	/* CEC arbitration 3/5/7 bit समय set. */
	ret = meson_ao_cec_arbit_bit_समय_set(ao_cec,
					CEC_SIGNAL_FREE_TIME_RETRY,
					0x118);
	अगर (ret)
		वापस ret;
	ret = meson_ao_cec_arbit_bit_समय_set(ao_cec,
					CEC_SIGNAL_FREE_TIME_NEW_INITIATOR,
					0x000);
	अगर (ret)
		वापस ret;
	ret = meson_ao_cec_arbit_bit_समय_set(ao_cec,
					CEC_SIGNAL_FREE_TIME_NEXT_XFER,
					0x2aa);
	अगर (ret)
		वापस ret;

	meson_ao_cec_irq_setup(ao_cec, true);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops meson_ao_cec_ops = अणु
	.adap_enable = meson_ao_cec_adap_enable,
	.adap_log_addr = meson_ao_cec_set_log_addr,
	.adap_transmit = meson_ao_cec_transmit,
पूर्ण;

अटल पूर्णांक meson_ao_cec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_ao_cec_device *ao_cec;
	काष्ठा device *hdmi_dev;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	hdmi_dev = cec_notअगरier_parse_hdmi_phandle(&pdev->dev);

	अगर (IS_ERR(hdmi_dev))
		वापस PTR_ERR(hdmi_dev);

	ao_cec = devm_kzalloc(&pdev->dev, माप(*ao_cec), GFP_KERNEL);
	अगर (!ao_cec)
		वापस -ENOMEM;

	spin_lock_init(&ao_cec->cec_reg_lock);

	ao_cec->adap = cec_allocate_adapter(&meson_ao_cec_ops, ao_cec,
					    "meson_ao_cec",
					    CEC_CAP_DEFAULTS |
					    CEC_CAP_CONNECTOR_INFO,
					    1); /* Use 1 क्रम now */
	अगर (IS_ERR(ao_cec->adap))
		वापस PTR_ERR(ao_cec->adap);

	ao_cec->adap->owner = THIS_MODULE;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ao_cec->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ao_cec->base)) अणु
		ret = PTR_ERR(ao_cec->base);
		जाओ out_probe_adapter;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					meson_ao_cec_irq,
					meson_ao_cec_irq_thपढ़ो,
					0, शून्य, ao_cec);
	अगर (ret) अणु
		dev_err(&pdev->dev, "irq request failed\n");
		जाओ out_probe_adapter;
	पूर्ण

	ao_cec->core = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(ao_cec->core)) अणु
		dev_err(&pdev->dev, "core clock request failed\n");
		ret = PTR_ERR(ao_cec->core);
		जाओ out_probe_adapter;
	पूर्ण

	ret = clk_prepare_enable(ao_cec->core);
	अगर (ret) अणु
		dev_err(&pdev->dev, "core clock enable failed\n");
		जाओ out_probe_adapter;
	पूर्ण

	ret = clk_set_rate(ao_cec->core, CEC_CLK_RATE);
	अगर (ret) अणु
		dev_err(&pdev->dev, "core clock set rate failed\n");
		जाओ out_probe_clk;
	पूर्ण

	device_reset_optional(&pdev->dev);

	ao_cec->pdev = pdev;
	platक्रमm_set_drvdata(pdev, ao_cec);

	ao_cec->notअगरy = cec_notअगरier_cec_adap_रेजिस्टर(hdmi_dev, शून्य,
							ao_cec->adap);
	अगर (!ao_cec->notअगरy) अणु
		ret = -ENOMEM;
		जाओ out_probe_clk;
	पूर्ण

	ret = cec_रेजिस्टर_adapter(ao_cec->adap, &pdev->dev);
	अगर (ret < 0)
		जाओ out_probe_notअगरy;

	/* Setup Hardware */
	ग_लिखोl_relaxed(CEC_GEN_CNTL_RESET,
		       ao_cec->base + CEC_GEN_CNTL_REG);

	वापस 0;

out_probe_notअगरy:
	cec_notअगरier_cec_adap_unरेजिस्टर(ao_cec->notअगरy, ao_cec->adap);

out_probe_clk:
	clk_disable_unprepare(ao_cec->core);

out_probe_adapter:
	cec_delete_adapter(ao_cec->adap);

	dev_err(&pdev->dev, "CEC controller registration failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक meson_ao_cec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_ao_cec_device *ao_cec = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(ao_cec->core);

	cec_notअगरier_cec_adap_unरेजिस्टर(ao_cec->notअगरy, ao_cec->adap);
	cec_unरेजिस्टर_adapter(ao_cec->adap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_ao_cec_of_match[] = अणु
	अणु .compatible = "amlogic,meson-gx-ao-cec", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_ao_cec_of_match);

अटल काष्ठा platक्रमm_driver meson_ao_cec_driver = अणु
	.probe   = meson_ao_cec_probe,
	.हटाओ  = meson_ao_cec_हटाओ,
	.driver  = अणु
		.name = "meson-ao-cec",
		.of_match_table = of_match_ptr(meson_ao_cec_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_ao_cec_driver);

MODULE_DESCRIPTION("Meson AO CEC Controller driver");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("GPL");
