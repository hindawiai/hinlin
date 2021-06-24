<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Macronix International Co., Ltd.
 *
 * Author:
 *	Mason Yang <masonccyang@mxic.com.tw>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "internals.h"

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

#घोषणा MXIC_NFC_MAX_CLK_HZ	50000000
#घोषणा IRQ_TIMEOUT		1000

काष्ठा mxic_nand_ctlr अणु
	काष्ठा clk *ps_clk;
	काष्ठा clk *send_clk;
	काष्ठा clk *send_dly_clk;
	काष्ठा completion complete;
	व्योम __iomem *regs;
	काष्ठा nand_controller controller;
	काष्ठा device *dev;
	काष्ठा nand_chip chip;
पूर्ण;

अटल पूर्णांक mxic_nfc_clk_enable(काष्ठा mxic_nand_ctlr *nfc)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(nfc->ps_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(nfc->send_clk);
	अगर (ret)
		जाओ err_ps_clk;

	ret = clk_prepare_enable(nfc->send_dly_clk);
	अगर (ret)
		जाओ err_send_dly_clk;

	वापस ret;

err_send_dly_clk:
	clk_disable_unprepare(nfc->send_clk);
err_ps_clk:
	clk_disable_unprepare(nfc->ps_clk);

	वापस ret;
पूर्ण

अटल व्योम mxic_nfc_clk_disable(काष्ठा mxic_nand_ctlr *nfc)
अणु
	clk_disable_unprepare(nfc->send_clk);
	clk_disable_unprepare(nfc->send_dly_clk);
	clk_disable_unprepare(nfc->ps_clk);
पूर्ण

अटल व्योम mxic_nfc_set_input_delay(काष्ठा mxic_nand_ctlr *nfc, u8 idly_code)
अणु
	ग_लिखोl(IDLY_CODE_VAL(0, idly_code) |
	       IDLY_CODE_VAL(1, idly_code) |
	       IDLY_CODE_VAL(2, idly_code) |
	       IDLY_CODE_VAL(3, idly_code),
	       nfc->regs + IDLY_CODE(0));
	ग_लिखोl(IDLY_CODE_VAL(4, idly_code) |
	       IDLY_CODE_VAL(5, idly_code) |
	       IDLY_CODE_VAL(6, idly_code) |
	       IDLY_CODE_VAL(7, idly_code),
	       nfc->regs + IDLY_CODE(1));
पूर्ण

अटल पूर्णांक mxic_nfc_clk_setup(काष्ठा mxic_nand_ctlr *nfc, अचिन्हित दीर्घ freq)
अणु
	पूर्णांक ret;

	ret = clk_set_rate(nfc->send_clk, freq);
	अगर (ret)
		वापस ret;

	ret = clk_set_rate(nfc->send_dly_clk, freq);
	अगर (ret)
		वापस ret;

	/*
	 * A स्थिरant delay range from 0x0 ~ 0x1F क्रम input delay,
	 * the unit is 78 ps, the max input delay is 2.418 ns.
	 */
	mxic_nfc_set_input_delay(nfc, 0xf);

	/*
	 * Phase degree = 360 * freq * output-delay
	 * where output-delay is a स्थिरant value 1 ns in FPGA.
	 *
	 * Get Phase degree = 360 * freq * 1 ns
	 *                  = 360 * freq * 1 sec / 1000000000
	 *                  = 9 * freq / 25000000
	 */
	ret = clk_set_phase(nfc->send_dly_clk, 9 * freq / 25000000);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mxic_nfc_set_freq(काष्ठा mxic_nand_ctlr *nfc, अचिन्हित दीर्घ freq)
अणु
	पूर्णांक ret;

	अगर (freq > MXIC_NFC_MAX_CLK_HZ)
		freq = MXIC_NFC_MAX_CLK_HZ;

	mxic_nfc_clk_disable(nfc);
	ret = mxic_nfc_clk_setup(nfc, freq);
	अगर (ret)
		वापस ret;

	ret = mxic_nfc_clk_enable(nfc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल irqवापस_t mxic_nfc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mxic_nand_ctlr *nfc = dev_id;
	u32 sts;

	sts = पढ़ोl(nfc->regs + INT_STS);
	अगर (sts & INT_RDY_PIN)
		complete(&nfc->complete);
	अन्यथा
		वापस IRQ_NONE;

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mxic_nfc_hw_init(काष्ठा mxic_nand_ctlr *nfc)
अणु
	ग_लिखोl(HC_CFG_NIO(8) | HC_CFG_TYPE(1, HC_CFG_TYPE_RAW_न_अंकD) |
	       HC_CFG_SLV_ACT(0) | HC_CFG_MAN_CS_EN |
	       HC_CFG_IDLE_SIO_LVL(1), nfc->regs + HC_CFG);
	ग_लिखोl(INT_STS_ALL, nfc->regs + INT_STS_EN);
	ग_लिखोl(INT_RDY_PIN, nfc->regs + INT_SIG_EN);
	ग_लिखोl(0x0, nfc->regs + ONFI_DIN_CNT(0));
	ग_लिखोl(0, nfc->regs + LRD_CFG);
	ग_लिखोl(0, nfc->regs + LRD_CTRL);
	ग_लिखोl(0x0, nfc->regs + HC_EN);
पूर्ण

अटल व्योम mxic_nfc_cs_enable(काष्ठा mxic_nand_ctlr *nfc)
अणु
	ग_लिखोl(पढ़ोl(nfc->regs + HC_CFG) | HC_CFG_MAN_CS_EN,
	       nfc->regs + HC_CFG);
	ग_लिखोl(HC_CFG_MAN_CS_ASSERT | पढ़ोl(nfc->regs + HC_CFG),
	       nfc->regs + HC_CFG);
पूर्ण

अटल व्योम mxic_nfc_cs_disable(काष्ठा mxic_nand_ctlr *nfc)
अणु
	ग_लिखोl(~HC_CFG_MAN_CS_ASSERT & पढ़ोl(nfc->regs + HC_CFG),
	       nfc->regs + HC_CFG);
पूर्ण

अटल पूर्णांक  mxic_nfc_रुको_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा mxic_nand_ctlr *nfc = nand_get_controller_data(chip);
	पूर्णांक ret;

	ret = रुको_क्रम_completion_समयout(&nfc->complete,
					  msecs_to_jअगरfies(IRQ_TIMEOUT));
	अगर (!ret) अणु
		dev_err(nfc->dev, "nand device timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxic_nfc_data_xfer(काष्ठा mxic_nand_ctlr *nfc, स्थिर व्योम *txbuf,
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

		ret = पढ़ोl_poll_समयout(nfc->regs + INT_STS, sts,
					 sts & INT_TX_EMPTY, 0, USEC_PER_SEC);
		अगर (ret)
			वापस ret;

		ग_लिखोl(data, nfc->regs + TXD(nbytes % 4));

		ret = पढ़ोl_poll_समयout(nfc->regs + INT_STS, sts,
					 sts & INT_TX_EMPTY, 0, USEC_PER_SEC);
		अगर (ret)
			वापस ret;

		ret = पढ़ोl_poll_समयout(nfc->regs + INT_STS, sts,
					 sts & INT_RX_NOT_EMPTY, 0,
					 USEC_PER_SEC);
		अगर (ret)
			वापस ret;

		data = पढ़ोl(nfc->regs + RXD);
		अगर (rxbuf) अणु
			data >>= (8 * (4 - nbytes));
			स_नकल(rxbuf + pos, &data, nbytes);
		पूर्ण
		अगर (पढ़ोl(nfc->regs + INT_STS) & INT_RX_NOT_EMPTY)
			dev_warn(nfc->dev, "RX FIFO not empty\n");

		pos += nbytes;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxic_nfc_exec_op(काष्ठा nand_chip *chip,
			    स्थिर काष्ठा nand_operation *op, bool check_only)
अणु
	काष्ठा mxic_nand_ctlr *nfc = nand_get_controller_data(chip);
	स्थिर काष्ठा nand_op_instr *instr = शून्य;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक op_id;

	अगर (check_only)
		वापस 0;

	mxic_nfc_cs_enable(nfc);
	init_completion(&nfc->complete);
	क्रम (op_id = 0; op_id < op->ninstrs; op_id++) अणु
		instr = &op->instrs[op_id];

		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			ग_लिखोl(0, nfc->regs + HC_EN);
			ग_लिखोl(HC_EN_BIT, nfc->regs + HC_EN);
			ग_लिखोl(OP_CMD_BUSW(OP_BUSW_8) |  OP_DUMMY_CYC(0x3F) |
			       OP_CMD_BYTES(0), nfc->regs + SS_CTRL(0));

			ret = mxic_nfc_data_xfer(nfc,
						 &instr->ctx.cmd.opcode,
						 शून्य, 1);
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			ग_लिखोl(OP_ADDR_BUSW(OP_BUSW_8) | OP_DUMMY_CYC(0x3F) |
			       OP_ADDR_BYTES(instr->ctx.addr.naddrs),
			       nfc->regs + SS_CTRL(0));
			ret = mxic_nfc_data_xfer(nfc,
						 instr->ctx.addr.addrs, शून्य,
						 instr->ctx.addr.naddrs);
			अवरोध;

		हाल न_अंकD_OP_DATA_IN_INSTR:
			ग_लिखोl(0x0, nfc->regs + ONFI_DIN_CNT(0));
			ग_लिखोl(OP_DATA_BUSW(OP_BUSW_8) | OP_DUMMY_CYC(0x3F) |
			       OP_READ, nfc->regs + SS_CTRL(0));
			ret = mxic_nfc_data_xfer(nfc, शून्य,
						 instr->ctx.data.buf.in,
						 instr->ctx.data.len);
			अवरोध;

		हाल न_अंकD_OP_DATA_OUT_INSTR:
			ग_लिखोl(instr->ctx.data.len,
			       nfc->regs + ONFI_DIN_CNT(0));
			ग_लिखोl(OP_DATA_BUSW(OP_BUSW_8) | OP_DUMMY_CYC(0x3F),
			       nfc->regs + SS_CTRL(0));
			ret = mxic_nfc_data_xfer(nfc,
						 instr->ctx.data.buf.out, शून्य,
						 instr->ctx.data.len);
			अवरोध;

		हाल न_अंकD_OP_WAITRDY_INSTR:
			ret = mxic_nfc_रुको_पढ़ोy(chip);
			अवरोध;
		पूर्ण
	पूर्ण
	mxic_nfc_cs_disable(nfc);

	वापस ret;
पूर्ण

अटल पूर्णांक mxic_nfc_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक chipnr,
				    स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा mxic_nand_ctlr *nfc = nand_get_controller_data(chip);
	स्थिर काष्ठा nand_sdr_timings *sdr;
	अचिन्हित दीर्घ freq;
	पूर्णांक ret;

	sdr = nand_get_sdr_timings(conf);
	अगर (IS_ERR(sdr))
		वापस PTR_ERR(sdr);

	अगर (chipnr == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	freq = NSEC_PER_SEC / (sdr->tRC_min / 1000);

	ret =  mxic_nfc_set_freq(nfc, freq);
	अगर (ret)
		dev_err(nfc->dev, "set freq:%ld failed\n", freq);

	अगर (sdr->tRC_min < 30000)
		ग_लिखोl(DATA_STROB_EDO_EN, nfc->regs + DATA_STROB);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops mxic_nand_controller_ops = अणु
	.exec_op = mxic_nfc_exec_op,
	.setup_पूर्णांकerface = mxic_nfc_setup_पूर्णांकerface,
पूर्ण;

अटल पूर्णांक mxic_nfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *nand_np, *np = pdev->dev.of_node;
	काष्ठा mtd_info *mtd;
	काष्ठा mxic_nand_ctlr *nfc;
	काष्ठा nand_chip *nand_chip;
	पूर्णांक err;
	पूर्णांक irq;

	nfc = devm_kzalloc(&pdev->dev, माप(काष्ठा mxic_nand_ctlr),
			   GFP_KERNEL);
	अगर (!nfc)
		वापस -ENOMEM;

	nfc->ps_clk = devm_clk_get(&pdev->dev, "ps");
	अगर (IS_ERR(nfc->ps_clk))
		वापस PTR_ERR(nfc->ps_clk);

	nfc->send_clk = devm_clk_get(&pdev->dev, "send");
	अगर (IS_ERR(nfc->send_clk))
		वापस PTR_ERR(nfc->send_clk);

	nfc->send_dly_clk = devm_clk_get(&pdev->dev, "send_dly");
	अगर (IS_ERR(nfc->send_dly_clk))
		वापस PTR_ERR(nfc->send_dly_clk);

	nfc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(nfc->regs))
		वापस PTR_ERR(nfc->regs);

	nand_chip = &nfc->chip;
	mtd = nand_to_mtd(nand_chip);
	mtd->dev.parent = &pdev->dev;

	क्रम_each_child_of_node(np, nand_np)
		nand_set_flash_node(nand_chip, nand_np);

	nand_chip->priv = nfc;
	nfc->dev = &pdev->dev;
	nfc->controller.ops = &mxic_nand_controller_ops;
	nand_controller_init(&nfc->controller);
	nand_chip->controller = &nfc->controller;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	mxic_nfc_hw_init(nfc);

	err = devm_request_irq(&pdev->dev, irq, mxic_nfc_isr,
			       0, "mxic-nfc", nfc);
	अगर (err)
		जाओ fail;

	err = nand_scan(nand_chip, 1);
	अगर (err)
		जाओ fail;

	err = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (err)
		जाओ fail;

	platक्रमm_set_drvdata(pdev, nfc);
	वापस 0;

fail:
	mxic_nfc_clk_disable(nfc);
	वापस err;
पूर्ण

अटल पूर्णांक mxic_nfc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxic_nand_ctlr *nfc = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &nfc->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	mxic_nfc_clk_disable(nfc);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxic_nfc_of_ids[] = अणु
	अणु .compatible = "mxic,multi-itfc-v009-nand-controller", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mxic_nfc_of_ids);

अटल काष्ठा platक्रमm_driver mxic_nfc_driver = अणु
	.probe = mxic_nfc_probe,
	.हटाओ = mxic_nfc_हटाओ,
	.driver = अणु
		.name = "mxic-nfc",
		.of_match_table = mxic_nfc_of_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mxic_nfc_driver);

MODULE_AUTHOR("Mason Yang <masonccyang@mxic.com.tw>");
MODULE_DESCRIPTION("Macronix raw NAND controller driver");
MODULE_LICENSE("GPL v2");
