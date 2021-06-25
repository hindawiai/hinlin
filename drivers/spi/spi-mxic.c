<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 Macronix International Co., Ltd.
//
// Authors:
//	Mason Yang <masonccyang@mxic.com.tw>
//	zhengxunli <zhengxunli@mxic.com.tw>
//	Boris Brezillon <boris.brezillon@bootlin.com>
//

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>

#घोषणा HC_CFG			0x0
#घोषणा HC_CFG_IF_CFG(x)	((x) << 27)
#घोषणा HC_CFG_DUAL_SLAVE	BIT(31)
#घोषणा HC_CFG_INDIVIDUAL	BIT(30)
#घोषणा HC_CFG_NIO(x)		(((x) / 4) << 27)
#घोषणा HC_CFG_TYPE(s, t)	((t) << (23 + ((s) * 2)))
#घोषणा HC_CFG_TYPE_SPI_NOR	0
#घोषणा HC_CFG_TYPE_SPI_न_अंकD	1
#घोषणा HC_CFG_TYPE_SPI_RAM	2
#घोषणा HC_CFG_TYPE_RAW_न_अंकD	3
#घोषणा HC_CFG_SLV_ACT(x)	((x) << 21)
#घोषणा HC_CFG_CLK_PH_EN	BIT(20)
#घोषणा HC_CFG_CLK_POL_INV	BIT(19)
#घोषणा HC_CFG_BIG_ENDIAN	BIT(18)
#घोषणा HC_CFG_DATA_PASS	BIT(17)
#घोषणा HC_CFG_IDLE_SIO_LVL(x)	((x) << 16)
#घोषणा HC_CFG_MAN_START_EN	BIT(3)
#घोषणा HC_CFG_MAN_START	BIT(2)
#घोषणा HC_CFG_MAN_CS_EN	BIT(1)
#घोषणा HC_CFG_MAN_CS_ASSERT	BIT(0)

#घोषणा INT_STS			0x4
#घोषणा INT_STS_EN		0x8
#घोषणा INT_SIG_EN		0xc
#घोषणा INT_STS_ALL		GENMASK(31, 0)
#घोषणा INT_RDY_PIN		BIT(26)
#घोषणा INT_RDY_SR		BIT(25)
#घोषणा INT_LNR_SUSP		BIT(24)
#घोषणा INT_ECC_ERR		BIT(17)
#घोषणा INT_CRC_ERR		BIT(16)
#घोषणा INT_LWR_DIS		BIT(12)
#घोषणा INT_LRD_DIS		BIT(11)
#घोषणा INT_SDMA_INT		BIT(10)
#घोषणा INT_DMA_FINISH		BIT(9)
#घोषणा INT_RX_NOT_FULL		BIT(3)
#घोषणा INT_RX_NOT_EMPTY	BIT(2)
#घोषणा INT_TX_NOT_FULL		BIT(1)
#घोषणा INT_TX_EMPTY		BIT(0)

#घोषणा HC_EN			0x10
#घोषणा HC_EN_BIT		BIT(0)

#घोषणा TXD(x)			(0x14 + ((x) * 4))
#घोषणा RXD			0x24

#घोषणा SS_CTRL(s)		(0x30 + ((s) * 4))
#घोषणा LRD_CFG			0x44
#घोषणा LWR_CFG			0x80
#घोषणा RWW_CFG			0x70
#घोषणा OP_READ			BIT(23)
#घोषणा OP_DUMMY_CYC(x)		((x) << 17)
#घोषणा OP_ADDR_BYTES(x)	((x) << 14)
#घोषणा OP_CMD_BYTES(x)		(((x) - 1) << 13)
#घोषणा OP_OCTA_CRC_EN		BIT(12)
#घोषणा OP_DQS_EN		BIT(11)
#घोषणा OP_ENHC_EN		BIT(10)
#घोषणा OP_PREAMBLE_EN		BIT(9)
#घोषणा OP_DATA_DDR		BIT(8)
#घोषणा OP_DATA_BUSW(x)		((x) << 6)
#घोषणा OP_ADDR_DDR		BIT(5)
#घोषणा OP_ADDR_BUSW(x)		((x) << 3)
#घोषणा OP_CMD_DDR		BIT(2)
#घोषणा OP_CMD_BUSW(x)		(x)
#घोषणा OP_BUSW_1		0
#घोषणा OP_BUSW_2		1
#घोषणा OP_BUSW_4		2
#घोषणा OP_BUSW_8		3

#घोषणा OCTA_CRC		0x38
#घोषणा OCTA_CRC_IN_EN(s)	BIT(3 + ((s) * 16))
#घोषणा OCTA_CRC_CHUNK(s, x)	((fls((x) / 32)) << (1 + ((s) * 16)))
#घोषणा OCTA_CRC_OUT_EN(s)	BIT(0 + ((s) * 16))

#घोषणा ONFI_DIN_CNT(s)		(0x3c + (s))

#घोषणा LRD_CTRL		0x48
#घोषणा RWW_CTRL		0x74
#घोषणा LWR_CTRL		0x84
#घोषणा LMODE_EN		BIT(31)
#घोषणा LMODE_SLV_ACT(x)	((x) << 21)
#घोषणा LMODE_CMD1(x)		((x) << 8)
#घोषणा LMODE_CMD0(x)		(x)

#घोषणा LRD_ADDR		0x4c
#घोषणा LWR_ADDR		0x88
#घोषणा LRD_RANGE		0x50
#घोषणा LWR_RANGE		0x8c

#घोषणा AXI_SLV_ADDR		0x54

#घोषणा DMAC_RD_CFG		0x58
#घोषणा DMAC_WR_CFG		0x94
#घोषणा DMAC_CFG_PERIPH_EN	BIT(31)
#घोषणा DMAC_CFG_ALLFLUSH_EN	BIT(30)
#घोषणा DMAC_CFG_LASTFLUSH_EN	BIT(29)
#घोषणा DMAC_CFG_QE(x)		(((x) + 1) << 16)
#घोषणा DMAC_CFG_BURST_LEN(x)	(((x) + 1) << 12)
#घोषणा DMAC_CFG_BURST_SZ(x)	((x) << 8)
#घोषणा DMAC_CFG_सूची_READ	BIT(1)
#घोषणा DMAC_CFG_START		BIT(0)

#घोषणा DMAC_RD_CNT		0x5c
#घोषणा DMAC_WR_CNT		0x98

#घोषणा SDMA_ADDR		0x60

#घोषणा DMAM_CFG		0x64
#घोषणा DMAM_CFG_START		BIT(31)
#घोषणा DMAM_CFG_CONT		BIT(30)
#घोषणा DMAM_CFG_SDMA_GAP(x)	(fls((x) / 8192) << 2)
#घोषणा DMAM_CFG_सूची_READ	BIT(1)
#घोषणा DMAM_CFG_EN		BIT(0)

#घोषणा DMAM_CNT		0x68

#घोषणा LNR_TIMER_TH		0x6c

#घोषणा RDM_CFG0		0x78
#घोषणा RDM_CFG0_POLY(x)	(x)

#घोषणा RDM_CFG1		0x7c
#घोषणा RDM_CFG1_RDM_EN		BIT(31)
#घोषणा RDM_CFG1_SEED(x)	(x)

#घोषणा LWR_SUSP_CTRL		0x90
#घोषणा LWR_SUSP_CTRL_EN	BIT(31)

#घोषणा DMAS_CTRL		0x9c
#घोषणा DMAS_CTRL_EN		BIT(31)
#घोषणा DMAS_CTRL_सूची_READ	BIT(30)

#घोषणा DATA_STROB		0xa0
#घोषणा DATA_STROB_EDO_EN	BIT(2)
#घोषणा DATA_STROB_INV_POL	BIT(1)
#घोषणा DATA_STROB_DELAY_2CYC	BIT(0)

#घोषणा IDLY_CODE(x)		(0xa4 + ((x) * 4))
#घोषणा IDLY_CODE_VAL(x, v)	((v) << (((x) % 4) * 8))

#घोषणा GPIO			0xc4
#घोषणा GPIO_PT(x)		BIT(3 + ((x) * 16))
#घोषणा GPIO_RESET(x)		BIT(2 + ((x) * 16))
#घोषणा GPIO_HOLDB(x)		BIT(1 + ((x) * 16))
#घोषणा GPIO_WPB(x)		BIT((x) * 16)

#घोषणा HC_VER			0xd0

#घोषणा HW_TEST(x)		(0xe0 + ((x) * 4))

काष्ठा mxic_spi अणु
	काष्ठा clk *ps_clk;
	काष्ठा clk *send_clk;
	काष्ठा clk *send_dly_clk;
	व्योम __iomem *regs;
	u32 cur_speed_hz;
पूर्ण;

अटल पूर्णांक mxic_spi_clk_enable(काष्ठा mxic_spi *mxic)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(mxic->send_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(mxic->send_dly_clk);
	अगर (ret)
		जाओ err_send_dly_clk;

	वापस ret;

err_send_dly_clk:
	clk_disable_unprepare(mxic->send_clk);

	वापस ret;
पूर्ण

अटल व्योम mxic_spi_clk_disable(काष्ठा mxic_spi *mxic)
अणु
	clk_disable_unprepare(mxic->send_clk);
	clk_disable_unprepare(mxic->send_dly_clk);
पूर्ण

अटल व्योम mxic_spi_set_input_delay_dqs(काष्ठा mxic_spi *mxic, u8 idly_code)
अणु
	ग_लिखोl(IDLY_CODE_VAL(0, idly_code) |
	       IDLY_CODE_VAL(1, idly_code) |
	       IDLY_CODE_VAL(2, idly_code) |
	       IDLY_CODE_VAL(3, idly_code),
	       mxic->regs + IDLY_CODE(0));
	ग_लिखोl(IDLY_CODE_VAL(4, idly_code) |
	       IDLY_CODE_VAL(5, idly_code) |
	       IDLY_CODE_VAL(6, idly_code) |
	       IDLY_CODE_VAL(7, idly_code),
	       mxic->regs + IDLY_CODE(1));
पूर्ण

अटल पूर्णांक mxic_spi_clk_setup(काष्ठा mxic_spi *mxic, अचिन्हित दीर्घ freq)
अणु
	पूर्णांक ret;

	ret = clk_set_rate(mxic->send_clk, freq);
	अगर (ret)
		वापस ret;

	ret = clk_set_rate(mxic->send_dly_clk, freq);
	अगर (ret)
		वापस ret;

	/*
	 * A स्थिरant delay range from 0x0 ~ 0x1F क्रम input delay,
	 * the unit is 78 ps, the max input delay is 2.418 ns.
	 */
	mxic_spi_set_input_delay_dqs(mxic, 0xf);

	/*
	 * Phase degree = 360 * freq * output-delay
	 * where output-delay is a स्थिरant value 1 ns in FPGA.
	 *
	 * Get Phase degree = 360 * freq * 1 ns
	 *                  = 360 * freq * 1 sec / 1000000000
	 *                  = 9 * freq / 25000000
	 */
	ret = clk_set_phase(mxic->send_dly_clk, 9 * freq / 25000000);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mxic_spi_set_freq(काष्ठा mxic_spi *mxic, अचिन्हित दीर्घ freq)
अणु
	पूर्णांक ret;

	अगर (mxic->cur_speed_hz == freq)
		वापस 0;

	mxic_spi_clk_disable(mxic);
	ret = mxic_spi_clk_setup(mxic, freq);
	अगर (ret)
		वापस ret;

	ret = mxic_spi_clk_enable(mxic);
	अगर (ret)
		वापस ret;

	mxic->cur_speed_hz = freq;

	वापस 0;
पूर्ण

अटल व्योम mxic_spi_hw_init(काष्ठा mxic_spi *mxic)
अणु
	ग_लिखोl(0, mxic->regs + DATA_STROB);
	ग_लिखोl(INT_STS_ALL, mxic->regs + INT_STS_EN);
	ग_लिखोl(0, mxic->regs + HC_EN);
	ग_लिखोl(0, mxic->regs + LRD_CFG);
	ग_लिखोl(0, mxic->regs + LRD_CTRL);
	ग_लिखोl(HC_CFG_NIO(1) | HC_CFG_TYPE(0, HC_CFG_TYPE_SPI_NOR) |
	       HC_CFG_SLV_ACT(0) | HC_CFG_MAN_CS_EN | HC_CFG_IDLE_SIO_LVL(1),
	       mxic->regs + HC_CFG);
पूर्ण

अटल पूर्णांक mxic_spi_data_xfer(काष्ठा mxic_spi *mxic, स्थिर व्योम *txbuf,
			      व्योम *rxbuf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक pos = 0;

	जबतक (pos < len) अणु
		अचिन्हित पूर्णांक nbytes = len - pos;
		u32 data = 0xffffffff;
		u32 sts;
		पूर्णांक ret;

		अगर (nbytes > 4)
			nbytes = 4;

		अगर (txbuf)
			स_नकल(&data, txbuf + pos, nbytes);

		ret = पढ़ोl_poll_समयout(mxic->regs + INT_STS, sts,
					 sts & INT_TX_EMPTY, 0, USEC_PER_SEC);
		अगर (ret)
			वापस ret;

		ग_लिखोl(data, mxic->regs + TXD(nbytes % 4));

		अगर (rxbuf) अणु
			ret = पढ़ोl_poll_समयout(mxic->regs + INT_STS, sts,
						 sts & INT_TX_EMPTY, 0,
						 USEC_PER_SEC);
			अगर (ret)
				वापस ret;

			ret = पढ़ोl_poll_समयout(mxic->regs + INT_STS, sts,
						 sts & INT_RX_NOT_EMPTY, 0,
						 USEC_PER_SEC);
			अगर (ret)
				वापस ret;

			data = पढ़ोl(mxic->regs + RXD);
			data >>= (8 * (4 - nbytes));
			स_नकल(rxbuf + pos, &data, nbytes);
			WARN_ON(पढ़ोl(mxic->regs + INT_STS) & INT_RX_NOT_EMPTY);
		पूर्ण अन्यथा अणु
			पढ़ोl(mxic->regs + RXD);
		पूर्ण
		WARN_ON(पढ़ोl(mxic->regs + INT_STS) & INT_RX_NOT_EMPTY);

		pos += nbytes;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool mxic_spi_mem_supports_op(काष्ठा spi_mem *mem,
				     स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (op->data.buswidth > 4 || op->addr.buswidth > 4 ||
	    op->dummy.buswidth > 4 || op->cmd.buswidth > 4)
		वापस false;

	अगर (op->data.nbytes && op->dummy.nbytes &&
	    op->data.buswidth != op->dummy.buswidth)
		वापस false;

	अगर (op->addr.nbytes > 7)
		वापस false;

	वापस spi_mem_शेष_supports_op(mem, op);
पूर्ण

अटल पूर्णांक mxic_spi_mem_exec_op(काष्ठा spi_mem *mem,
				स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा mxic_spi *mxic = spi_master_get_devdata(mem->spi->master);
	पूर्णांक nio = 1, i, ret;
	u32 ss_ctrl;
	u8 addr[8];
	u8 opcode = op->cmd.opcode;

	ret = mxic_spi_set_freq(mxic, mem->spi->max_speed_hz);
	अगर (ret)
		वापस ret;

	अगर (mem->spi->mode & (SPI_TX_QUAD | SPI_RX_QUAD))
		nio = 4;
	अन्यथा अगर (mem->spi->mode & (SPI_TX_DUAL | SPI_RX_DUAL))
		nio = 2;

	ग_लिखोl(HC_CFG_NIO(nio) |
	       HC_CFG_TYPE(mem->spi->chip_select, HC_CFG_TYPE_SPI_NOR) |
	       HC_CFG_SLV_ACT(mem->spi->chip_select) | HC_CFG_IDLE_SIO_LVL(1) |
	       HC_CFG_MAN_CS_EN,
	       mxic->regs + HC_CFG);
	ग_लिखोl(HC_EN_BIT, mxic->regs + HC_EN);

	ss_ctrl = OP_CMD_BYTES(1) | OP_CMD_BUSW(fls(op->cmd.buswidth) - 1);

	अगर (op->addr.nbytes)
		ss_ctrl |= OP_ADDR_BYTES(op->addr.nbytes) |
			   OP_ADDR_BUSW(fls(op->addr.buswidth) - 1);

	अगर (op->dummy.nbytes)
		ss_ctrl |= OP_DUMMY_CYC(op->dummy.nbytes);

	अगर (op->data.nbytes) अणु
		ss_ctrl |= OP_DATA_BUSW(fls(op->data.buswidth) - 1);
		अगर (op->data.dir == SPI_MEM_DATA_IN)
			ss_ctrl |= OP_READ;
	पूर्ण

	ग_लिखोl(ss_ctrl, mxic->regs + SS_CTRL(mem->spi->chip_select));

	ग_लिखोl(पढ़ोl(mxic->regs + HC_CFG) | HC_CFG_MAN_CS_ASSERT,
	       mxic->regs + HC_CFG);

	ret = mxic_spi_data_xfer(mxic, &opcode, शून्य, 1);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < op->addr.nbytes; i++)
		addr[i] = op->addr.val >> (8 * (op->addr.nbytes - i - 1));

	ret = mxic_spi_data_xfer(mxic, addr, शून्य, op->addr.nbytes);
	अगर (ret)
		जाओ out;

	ret = mxic_spi_data_xfer(mxic, शून्य, शून्य, op->dummy.nbytes);
	अगर (ret)
		जाओ out;

	ret = mxic_spi_data_xfer(mxic,
				 op->data.dir == SPI_MEM_DATA_OUT ?
				 op->data.buf.out : शून्य,
				 op->data.dir == SPI_MEM_DATA_IN ?
				 op->data.buf.in : शून्य,
				 op->data.nbytes);

out:
	ग_लिखोl(पढ़ोl(mxic->regs + HC_CFG) & ~HC_CFG_MAN_CS_ASSERT,
	       mxic->regs + HC_CFG);
	ग_लिखोl(0, mxic->regs + HC_EN);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops mxic_spi_mem_ops = अणु
	.supports_op = mxic_spi_mem_supports_op,
	.exec_op = mxic_spi_mem_exec_op,
पूर्ण;

अटल व्योम mxic_spi_set_cs(काष्ठा spi_device *spi, bool lvl)
अणु
	काष्ठा mxic_spi *mxic = spi_master_get_devdata(spi->master);

	अगर (!lvl) अणु
		ग_लिखोl(पढ़ोl(mxic->regs + HC_CFG) | HC_CFG_MAN_CS_EN,
		       mxic->regs + HC_CFG);
		ग_लिखोl(HC_EN_BIT, mxic->regs + HC_EN);
		ग_लिखोl(पढ़ोl(mxic->regs + HC_CFG) | HC_CFG_MAN_CS_ASSERT,
		       mxic->regs + HC_CFG);
	पूर्ण अन्यथा अणु
		ग_लिखोl(पढ़ोl(mxic->regs + HC_CFG) & ~HC_CFG_MAN_CS_ASSERT,
		       mxic->regs + HC_CFG);
		ग_लिखोl(0, mxic->regs + HC_EN);
	पूर्ण
पूर्ण

अटल पूर्णांक mxic_spi_transfer_one(काष्ठा spi_master *master,
				 काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *t)
अणु
	काष्ठा mxic_spi *mxic = spi_master_get_devdata(master);
	अचिन्हित पूर्णांक busw = OP_BUSW_1;
	पूर्णांक ret;

	अगर (t->rx_buf && t->tx_buf) अणु
		अगर (((spi->mode & SPI_TX_QUAD) &&
		     !(spi->mode & SPI_RX_QUAD)) ||
		    ((spi->mode & SPI_TX_DUAL) &&
		     !(spi->mode & SPI_RX_DUAL)))
			वापस -ENOTSUPP;
	पूर्ण

	ret = mxic_spi_set_freq(mxic, t->speed_hz);
	अगर (ret)
		वापस ret;

	अगर (t->tx_buf) अणु
		अगर (spi->mode & SPI_TX_QUAD)
			busw = OP_BUSW_4;
		अन्यथा अगर (spi->mode & SPI_TX_DUAL)
			busw = OP_BUSW_2;
	पूर्ण अन्यथा अगर (t->rx_buf) अणु
		अगर (spi->mode & SPI_RX_QUAD)
			busw = OP_BUSW_4;
		अन्यथा अगर (spi->mode & SPI_RX_DUAL)
			busw = OP_BUSW_2;
	पूर्ण

	ग_लिखोl(OP_CMD_BYTES(1) | OP_CMD_BUSW(busw) |
	       OP_DATA_BUSW(busw) | (t->rx_buf ? OP_READ : 0),
	       mxic->regs + SS_CTRL(0));

	ret = mxic_spi_data_xfer(mxic, t->tx_buf, t->rx_buf, t->len);
	अगर (ret)
		वापस ret;

	spi_finalize_current_transfer(master);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mxic_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mxic_spi *mxic = spi_master_get_devdata(master);

	mxic_spi_clk_disable(mxic);
	clk_disable_unprepare(mxic->ps_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mxic_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mxic_spi *mxic = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(mxic->ps_clk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable ps_clock.\n");
		वापस ret;
	पूर्ण

	वापस mxic_spi_clk_enable(mxic);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mxic_spi_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mxic_spi_runसमय_suspend,
			   mxic_spi_runसमय_resume, शून्य)
पूर्ण;

अटल पूर्णांक mxic_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा resource *res;
	काष्ठा mxic_spi *mxic;
	पूर्णांक ret;

	master = devm_spi_alloc_master(&pdev->dev, माप(काष्ठा mxic_spi));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);

	mxic = spi_master_get_devdata(master);

	master->dev.of_node = pdev->dev.of_node;

	mxic->ps_clk = devm_clk_get(&pdev->dev, "ps_clk");
	अगर (IS_ERR(mxic->ps_clk))
		वापस PTR_ERR(mxic->ps_clk);

	mxic->send_clk = devm_clk_get(&pdev->dev, "send_clk");
	अगर (IS_ERR(mxic->send_clk))
		वापस PTR_ERR(mxic->send_clk);

	mxic->send_dly_clk = devm_clk_get(&pdev->dev, "send_dly_clk");
	अगर (IS_ERR(mxic->send_dly_clk))
		वापस PTR_ERR(mxic->send_dly_clk);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "regs");
	mxic->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mxic->regs))
		वापस PTR_ERR(mxic->regs);

	pm_runसमय_enable(&pdev->dev);
	master->स्वतः_runसमय_pm = true;

	master->num_chipselect = 1;
	master->mem_ops = &mxic_spi_mem_ops;

	master->set_cs = mxic_spi_set_cs;
	master->transfer_one = mxic_spi_transfer_one;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->mode_bits = SPI_CPOL | SPI_CPHA |
			SPI_RX_DUAL | SPI_TX_DUAL |
			SPI_RX_QUAD | SPI_TX_QUAD;

	mxic_spi_hw_init(mxic);

	ret = spi_रेजिस्टर_master(master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "spi_register_master failed\n");
		pm_runसमय_disable(&pdev->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mxic_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	spi_unरेजिस्टर_master(master);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxic_spi_of_ids[] = अणु
	अणु .compatible = "mxicy,mx25f0a-spi", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxic_spi_of_ids);

अटल काष्ठा platक्रमm_driver mxic_spi_driver = अणु
	.probe = mxic_spi_probe,
	.हटाओ = mxic_spi_हटाओ,
	.driver = अणु
		.name = "mxic-spi",
		.of_match_table = mxic_spi_of_ids,
		.pm = &mxic_spi_dev_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mxic_spi_driver);

MODULE_AUTHOR("Mason Yang <masonccyang@mxic.com.tw>");
MODULE_DESCRIPTION("MX25F0A SPI controller driver");
MODULE_LICENSE("GPL v2");
