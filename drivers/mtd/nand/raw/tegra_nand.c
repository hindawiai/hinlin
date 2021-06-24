<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Stefan Agner <stefan@agner.ch>
 * Copyright (C) 2014-2015 Lucas Stach <dev@lynxeye.de>
 * Copyright (C) 2012 Avionic Design GmbH
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#घोषणा COMMAND					0x00
#घोषणा   COMMAND_GO				BIT(31)
#घोषणा   COMMAND_CLE				BIT(30)
#घोषणा   COMMAND_ALE				BIT(29)
#घोषणा   COMMAND_PIO				BIT(28)
#घोषणा   COMMAND_TX				BIT(27)
#घोषणा   COMMAND_RX				BIT(26)
#घोषणा   COMMAND_SEC_CMD			BIT(25)
#घोषणा   COMMAND_AFT_DAT			BIT(24)
#घोषणा   COMMAND_TRANS_SIZE(size)		((((size) - 1) & 0xf) << 20)
#घोषणा   COMMAND_A_VALID			BIT(19)
#घोषणा   COMMAND_B_VALID			BIT(18)
#घोषणा   COMMAND_RD_STATUS_CHK			BIT(17)
#घोषणा   COMMAND_RBSY_CHK			BIT(16)
#घोषणा   COMMAND_CE(x)				BIT(8 + ((x) & 0x7))
#घोषणा   COMMAND_CLE_SIZE(size)		((((size) - 1) & 0x3) << 4)
#घोषणा   COMMAND_ALE_SIZE(size)		((((size) - 1) & 0xf) << 0)

#घोषणा STATUS					0x04

#घोषणा ISR					0x08
#घोषणा   ISR_CORRFAIL_ERR			BIT(24)
#घोषणा   ISR_UND				BIT(7)
#घोषणा   ISR_OVR				BIT(6)
#घोषणा   ISR_CMD_DONE				BIT(5)
#घोषणा   ISR_ECC_ERR				BIT(4)

#घोषणा IER					0x0c
#घोषणा   IER_ERR_TRIG_VAL(x)			(((x) & 0xf) << 16)
#घोषणा   IER_UND				BIT(7)
#घोषणा   IER_OVR				BIT(6)
#घोषणा   IER_CMD_DONE				BIT(5)
#घोषणा   IER_ECC_ERR				BIT(4)
#घोषणा   IER_GIE				BIT(0)

#घोषणा CONFIG					0x10
#घोषणा   CONFIG_HW_ECC				BIT(31)
#घोषणा   CONFIG_ECC_SEL			BIT(30)
#घोषणा   CONFIG_ERR_COR			BIT(29)
#घोषणा   CONFIG_PIPE_EN			BIT(28)
#घोषणा   CONFIG_TVAL_4				(0 << 24)
#घोषणा   CONFIG_TVAL_6				(1 << 24)
#घोषणा   CONFIG_TVAL_8				(2 << 24)
#घोषणा   CONFIG_SKIP_SPARE			BIT(23)
#घोषणा   CONFIG_BUS_WIDTH_16			BIT(21)
#घोषणा   CONFIG_COM_BSY			BIT(20)
#घोषणा   CONFIG_PS_256				(0 << 16)
#घोषणा   CONFIG_PS_512				(1 << 16)
#घोषणा   CONFIG_PS_1024			(2 << 16)
#घोषणा   CONFIG_PS_2048			(3 << 16)
#घोषणा   CONFIG_PS_4096			(4 << 16)
#घोषणा   CONFIG_SKIP_SPARE_SIZE_4		(0 << 14)
#घोषणा   CONFIG_SKIP_SPARE_SIZE_8		(1 << 14)
#घोषणा   CONFIG_SKIP_SPARE_SIZE_12		(2 << 14)
#घोषणा   CONFIG_SKIP_SPARE_SIZE_16		(3 << 14)
#घोषणा   CONFIG_TAG_BYTE_SIZE(x)			((x) & 0xff)

#घोषणा TIMING_1				0x14
#घोषणा   TIMING_TRP_RESP(x)			(((x) & 0xf) << 28)
#घोषणा   TIMING_TWB(x)				(((x) & 0xf) << 24)
#घोषणा   TIMING_TCR_TAR_TRR(x)			(((x) & 0xf) << 20)
#घोषणा   TIMING_TWHR(x)			(((x) & 0xf) << 16)
#घोषणा   TIMING_TCS(x)				(((x) & 0x3) << 14)
#घोषणा   TIMING_TWH(x)				(((x) & 0x3) << 12)
#घोषणा   TIMING_TWP(x)				(((x) & 0xf) <<  8)
#घोषणा   TIMING_TRH(x)				(((x) & 0x3) <<  4)
#घोषणा   TIMING_TRP(x)				(((x) & 0xf) <<  0)

#घोषणा RESP					0x18

#घोषणा TIMING_2				0x1c
#घोषणा   TIMING_TADL(x)			((x) & 0xf)

#घोषणा CMD_REG1				0x20
#घोषणा CMD_REG2				0x24
#घोषणा ADDR_REG1				0x28
#घोषणा ADDR_REG2				0x2c

#घोषणा DMA_MST_CTRL				0x30
#घोषणा   DMA_MST_CTRL_GO			BIT(31)
#घोषणा   DMA_MST_CTRL_IN			(0 << 30)
#घोषणा   DMA_MST_CTRL_OUT			BIT(30)
#घोषणा   DMA_MST_CTRL_PERF_EN			BIT(29)
#घोषणा   DMA_MST_CTRL_IE_DONE			BIT(28)
#घोषणा   DMA_MST_CTRL_REUSE			BIT(27)
#घोषणा   DMA_MST_CTRL_BURST_1			(2 << 24)
#घोषणा   DMA_MST_CTRL_BURST_4			(3 << 24)
#घोषणा   DMA_MST_CTRL_BURST_8			(4 << 24)
#घोषणा   DMA_MST_CTRL_BURST_16			(5 << 24)
#घोषणा   DMA_MST_CTRL_IS_DONE			BIT(20)
#घोषणा   DMA_MST_CTRL_EN_A			BIT(2)
#घोषणा   DMA_MST_CTRL_EN_B			BIT(1)

#घोषणा DMA_CFG_A				0x34
#घोषणा DMA_CFG_B				0x38

#घोषणा FIFO_CTRL				0x3c
#घोषणा   FIFO_CTRL_CLR_ALL			BIT(3)

#घोषणा DATA_PTR				0x40
#घोषणा TAG_PTR					0x44
#घोषणा ECC_PTR					0x48

#घोषणा DEC_STATUS				0x4c
#घोषणा   DEC_STATUS_A_ECC_FAIL			BIT(1)
#घोषणा   DEC_STATUS_ERR_COUNT_MASK		0x00ff0000
#घोषणा   DEC_STATUS_ERR_COUNT_SHIFT		16

#घोषणा HWSTATUS_CMD				0x50
#घोषणा HWSTATUS_MASK				0x54
#घोषणा   HWSTATUS_RDSTATUS_MASK(x)		(((x) & 0xff) << 24)
#घोषणा   HWSTATUS_RDSTATUS_VALUE(x)		(((x) & 0xff) << 16)
#घोषणा   HWSTATUS_RBSY_MASK(x)			(((x) & 0xff) << 8)
#घोषणा   HWSTATUS_RBSY_VALUE(x)		(((x) & 0xff) << 0)

#घोषणा BCH_CONFIG				0xcc
#घोषणा   BCH_ENABLE				BIT(0)
#घोषणा   BCH_TVAL_4				(0 << 4)
#घोषणा   BCH_TVAL_8				(1 << 4)
#घोषणा   BCH_TVAL_14				(2 << 4)
#घोषणा   BCH_TVAL_16				(3 << 4)

#घोषणा DEC_STAT_RESULT				0xd0
#घोषणा DEC_STAT_BUF				0xd4
#घोषणा   DEC_STAT_BUF_FAIL_SEC_FLAG_MASK	0xff000000
#घोषणा   DEC_STAT_BUF_FAIL_SEC_FLAG_SHIFT	24
#घोषणा   DEC_STAT_BUF_CORR_SEC_FLAG_MASK	0x00ff0000
#घोषणा   DEC_STAT_BUF_CORR_SEC_FLAG_SHIFT	16
#घोषणा   DEC_STAT_BUF_MAX_CORR_CNT_MASK	0x00001f00
#घोषणा   DEC_STAT_BUF_MAX_CORR_CNT_SHIFT	8

#घोषणा OFFSET(val, off)	((val) < (off) ? 0 : (val) - (off))

#घोषणा SKIP_SPARE_BYTES	4
#घोषणा BITS_PER_STEP_RS	18
#घोषणा BITS_PER_STEP_BCH	13

#घोषणा INT_MASK		(IER_UND | IER_OVR | IER_CMD_DONE | IER_GIE)
#घोषणा HWSTATUS_CMD_DEFAULT	न_अंकD_STATUS_READY
#घोषणा HWSTATUS_MASK_DEFAULT	(HWSTATUS_RDSTATUS_MASK(1) | \
				HWSTATUS_RDSTATUS_VALUE(0) | \
				HWSTATUS_RBSY_MASK(न_अंकD_STATUS_READY) | \
				HWSTATUS_RBSY_VALUE(न_अंकD_STATUS_READY))

काष्ठा tegra_nand_controller अणु
	काष्ठा nand_controller controller;
	काष्ठा device *dev;
	व्योम __iomem *regs;
	पूर्णांक irq;
	काष्ठा clk *clk;
	काष्ठा completion command_complete;
	काष्ठा completion dma_complete;
	bool last_पढ़ो_error;
	पूर्णांक cur_cs;
	काष्ठा nand_chip *chip;
पूर्ण;

काष्ठा tegra_nand_chip अणु
	काष्ठा nand_chip chip;
	काष्ठा gpio_desc *wp_gpio;
	काष्ठा mtd_oob_region ecc;
	u32 config;
	u32 config_ecc;
	u32 bch_config;
	पूर्णांक cs[1];
पूर्ण;

अटल अंतरभूत काष्ठा tegra_nand_controller *
			to_tegra_ctrl(काष्ठा nand_controller *hw_ctrl)
अणु
	वापस container_of(hw_ctrl, काष्ठा tegra_nand_controller, controller);
पूर्ण

अटल अंतरभूत काष्ठा tegra_nand_chip *to_tegra_chip(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा tegra_nand_chip, chip);
पूर्ण

अटल पूर्णांक tegra_nand_ooblayout_rs_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				       काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	पूर्णांक bytes_per_step = DIV_ROUND_UP(BITS_PER_STEP_RS * chip->ecc.strength,
					  BITS_PER_BYTE);

	अगर (section > 0)
		वापस -दुस्फल;

	oobregion->offset = SKIP_SPARE_BYTES;
	oobregion->length = round_up(bytes_per_step * chip->ecc.steps, 4);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_nand_ooblayout_no_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
					काष्ठा mtd_oob_region *oobregion)
अणु
	वापस -दुस्फल;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops tegra_nand_oob_rs_ops = अणु
	.ecc = tegra_nand_ooblayout_rs_ecc,
	.मुक्त = tegra_nand_ooblayout_no_मुक्त,
पूर्ण;

अटल पूर्णांक tegra_nand_ooblayout_bch_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
					काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	पूर्णांक bytes_per_step = DIV_ROUND_UP(BITS_PER_STEP_BCH * chip->ecc.strength,
					  BITS_PER_BYTE);

	अगर (section > 0)
		वापस -दुस्फल;

	oobregion->offset = SKIP_SPARE_BYTES;
	oobregion->length = round_up(bytes_per_step * chip->ecc.steps, 4);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops tegra_nand_oob_bch_ops = अणु
	.ecc = tegra_nand_ooblayout_bch_ecc,
	.मुक्त = tegra_nand_ooblayout_no_मुक्त,
पूर्ण;

अटल irqवापस_t tegra_nand_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_nand_controller *ctrl = data;
	u32 isr, dma;

	isr = पढ़ोl_relaxed(ctrl->regs + ISR);
	dma = पढ़ोl_relaxed(ctrl->regs + DMA_MST_CTRL);
	dev_dbg(ctrl->dev, "isr %08x\n", isr);

	अगर (!isr && !(dma & DMA_MST_CTRL_IS_DONE))
		वापस IRQ_NONE;

	/*
	 * The bit name is somewhat missleading: This is also set when
	 * HW ECC was successful. The data sheet states:
	 * Correctable OR Un-correctable errors occurred in the DMA transfer...
	 */
	अगर (isr & ISR_CORRFAIL_ERR)
		ctrl->last_पढ़ो_error = true;

	अगर (isr & ISR_CMD_DONE)
		complete(&ctrl->command_complete);

	अगर (isr & ISR_UND)
		dev_err(ctrl->dev, "FIFO underrun\n");

	अगर (isr & ISR_OVR)
		dev_err(ctrl->dev, "FIFO overrun\n");

	/* handle DMA पूर्णांकerrupts */
	अगर (dma & DMA_MST_CTRL_IS_DONE) अणु
		ग_लिखोl_relaxed(dma, ctrl->regs + DMA_MST_CTRL);
		complete(&ctrl->dma_complete);
	पूर्ण

	/* clear पूर्णांकerrupts */
	ग_लिखोl_relaxed(isr, ctrl->regs + ISR);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अक्षर * स्थिर tegra_nand_reg_names[] = अणु
	"COMMAND",
	"STATUS",
	"ISR",
	"IER",
	"CONFIG",
	"TIMING",
	शून्य,
	"TIMING2",
	"CMD_REG1",
	"CMD_REG2",
	"ADDR_REG1",
	"ADDR_REG2",
	"DMA_MST_CTRL",
	"DMA_CFG_A",
	"DMA_CFG_B",
	"FIFO_CTRL",
पूर्ण;

अटल व्योम tegra_nand_dump_reg(काष्ठा tegra_nand_controller *ctrl)
अणु
	u32 reg;
	पूर्णांक i;

	dev_err(ctrl->dev, "Tegra NAND controller register dump\n");
	क्रम (i = 0; i < ARRAY_SIZE(tegra_nand_reg_names); i++) अणु
		स्थिर अक्षर *reg_name = tegra_nand_reg_names[i];

		अगर (!reg_name)
			जारी;

		reg = पढ़ोl_relaxed(ctrl->regs + (i * 4));
		dev_err(ctrl->dev, "%s: 0x%08x\n", reg_name, reg);
	पूर्ण
पूर्ण

अटल व्योम tegra_nand_controller_पात(काष्ठा tegra_nand_controller *ctrl)
अणु
	u32 isr, dma;

	disable_irq(ctrl->irq);

	/* Abort current command/DMA operation */
	ग_लिखोl_relaxed(0, ctrl->regs + DMA_MST_CTRL);
	ग_लिखोl_relaxed(0, ctrl->regs + COMMAND);

	/* clear पूर्णांकerrupts */
	isr = पढ़ोl_relaxed(ctrl->regs + ISR);
	ग_लिखोl_relaxed(isr, ctrl->regs + ISR);
	dma = पढ़ोl_relaxed(ctrl->regs + DMA_MST_CTRL);
	ग_लिखोl_relaxed(dma, ctrl->regs + DMA_MST_CTRL);

	reinit_completion(&ctrl->command_complete);
	reinit_completion(&ctrl->dma_complete);

	enable_irq(ctrl->irq);
पूर्ण

अटल पूर्णांक tegra_nand_cmd(काष्ठा nand_chip *chip,
			  स्थिर काष्ठा nand_subop *subop)
अणु
	स्थिर काष्ठा nand_op_instr *instr;
	स्थिर काष्ठा nand_op_instr *instr_data_in = शून्य;
	काष्ठा tegra_nand_controller *ctrl = to_tegra_ctrl(chip->controller);
	अचिन्हित पूर्णांक op_id, size = 0, offset = 0;
	bool first_cmd = true;
	u32 reg, cmd = 0;
	पूर्णांक ret;

	क्रम (op_id = 0; op_id < subop->ninstrs; op_id++) अणु
		अचिन्हित पूर्णांक naddrs, i;
		स्थिर u8 *addrs;
		u32 addr1 = 0, addr2 = 0;

		instr = &subop->instrs[op_id];

		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			अगर (first_cmd) अणु
				cmd |= COMMAND_CLE;
				ग_लिखोl_relaxed(instr->ctx.cmd.opcode,
					       ctrl->regs + CMD_REG1);
			पूर्ण अन्यथा अणु
				cmd |= COMMAND_SEC_CMD;
				ग_लिखोl_relaxed(instr->ctx.cmd.opcode,
					       ctrl->regs + CMD_REG2);
			पूर्ण
			first_cmd = false;
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			offset = nand_subop_get_addr_start_off(subop, op_id);
			naddrs = nand_subop_get_num_addr_cyc(subop, op_id);
			addrs = &instr->ctx.addr.addrs[offset];

			cmd |= COMMAND_ALE | COMMAND_ALE_SIZE(naddrs);
			क्रम (i = 0; i < min_t(अचिन्हित पूर्णांक, 4, naddrs); i++)
				addr1 |= *addrs++ << (BITS_PER_BYTE * i);
			naddrs -= i;
			क्रम (i = 0; i < min_t(अचिन्हित पूर्णांक, 4, naddrs); i++)
				addr2 |= *addrs++ << (BITS_PER_BYTE * i);

			ग_लिखोl_relaxed(addr1, ctrl->regs + ADDR_REG1);
			ग_लिखोl_relaxed(addr2, ctrl->regs + ADDR_REG2);
			अवरोध;

		हाल न_अंकD_OP_DATA_IN_INSTR:
			size = nand_subop_get_data_len(subop, op_id);
			offset = nand_subop_get_data_start_off(subop, op_id);

			cmd |= COMMAND_TRANS_SIZE(size) | COMMAND_PIO |
				COMMAND_RX | COMMAND_A_VALID;

			instr_data_in = instr;
			अवरोध;

		हाल न_अंकD_OP_DATA_OUT_INSTR:
			size = nand_subop_get_data_len(subop, op_id);
			offset = nand_subop_get_data_start_off(subop, op_id);

			cmd |= COMMAND_TRANS_SIZE(size) | COMMAND_PIO |
				COMMAND_TX | COMMAND_A_VALID;
			स_नकल(&reg, instr->ctx.data.buf.out + offset, size);

			ग_लिखोl_relaxed(reg, ctrl->regs + RESP);
			अवरोध;

		हाल न_अंकD_OP_WAITRDY_INSTR:
			cmd |= COMMAND_RBSY_CHK;
			अवरोध;
		पूर्ण
	पूर्ण

	cmd |= COMMAND_GO | COMMAND_CE(ctrl->cur_cs);
	ग_लिखोl_relaxed(cmd, ctrl->regs + COMMAND);
	ret = रुको_क्रम_completion_समयout(&ctrl->command_complete,
					  msecs_to_jअगरfies(500));
	अगर (!ret) अणु
		dev_err(ctrl->dev, "COMMAND timeout\n");
		tegra_nand_dump_reg(ctrl);
		tegra_nand_controller_पात(ctrl);
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (instr_data_in) अणु
		reg = पढ़ोl_relaxed(ctrl->regs + RESP);
		स_नकल(instr_data_in->ctx.data.buf.in + offset, &reg, size);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_op_parser tegra_nand_op_parser = न_अंकD_OP_PARSER(
	न_अंकD_OP_PARSER_PATTERN(tegra_nand_cmd,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, 8),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true)),
	न_अंकD_OP_PARSER_PATTERN(tegra_nand_cmd,
		न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(false, 4)),
	न_अंकD_OP_PARSER_PATTERN(tegra_nand_cmd,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, 8),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true),
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(true, 4)),
	);

अटल व्योम tegra_nand_select_target(काष्ठा nand_chip *chip,
				     अचिन्हित पूर्णांक die_nr)
अणु
	काष्ठा tegra_nand_chip *nand = to_tegra_chip(chip);
	काष्ठा tegra_nand_controller *ctrl = to_tegra_ctrl(chip->controller);

	ctrl->cur_cs = nand->cs[die_nr];
पूर्ण

अटल पूर्णांक tegra_nand_exec_op(काष्ठा nand_chip *chip,
			      स्थिर काष्ठा nand_operation *op,
			      bool check_only)
अणु
	अगर (!check_only)
		tegra_nand_select_target(chip, op->cs);

	वापस nand_op_parser_exec_op(chip, &tegra_nand_op_parser, op,
				      check_only);
पूर्ण

अटल व्योम tegra_nand_hw_ecc(काष्ठा tegra_nand_controller *ctrl,
			      काष्ठा nand_chip *chip, bool enable)
अणु
	काष्ठा tegra_nand_chip *nand = to_tegra_chip(chip);

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_BCH && enable)
		ग_लिखोl_relaxed(nand->bch_config, ctrl->regs + BCH_CONFIG);
	अन्यथा
		ग_लिखोl_relaxed(0, ctrl->regs + BCH_CONFIG);

	अगर (enable)
		ग_लिखोl_relaxed(nand->config_ecc, ctrl->regs + CONFIG);
	अन्यथा
		ग_लिखोl_relaxed(nand->config, ctrl->regs + CONFIG);
पूर्ण

अटल पूर्णांक tegra_nand_page_xfer(काष्ठा mtd_info *mtd, काष्ठा nand_chip *chip,
				व्योम *buf, व्योम *oob_buf, पूर्णांक oob_len, पूर्णांक page,
				bool पढ़ो)
अणु
	काष्ठा tegra_nand_controller *ctrl = to_tegra_ctrl(chip->controller);
	क्रमागत dma_data_direction dir = पढ़ो ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	dma_addr_t dma_addr = 0, dma_addr_oob = 0;
	u32 addr1, cmd, dma_ctrl;
	पूर्णांक ret;

	tegra_nand_select_target(chip, chip->cur_cs);

	अगर (पढ़ो) अणु
		ग_लिखोl_relaxed(न_अंकD_CMD_READ0, ctrl->regs + CMD_REG1);
		ग_लिखोl_relaxed(न_अंकD_CMD_READSTART, ctrl->regs + CMD_REG2);
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(न_अंकD_CMD_SEQIN, ctrl->regs + CMD_REG1);
		ग_लिखोl_relaxed(न_अंकD_CMD_PAGEPROG, ctrl->regs + CMD_REG2);
	पूर्ण
	cmd = COMMAND_CLE | COMMAND_SEC_CMD;

	/* Lower 16-bits are column, by शेष 0 */
	addr1 = page << 16;

	अगर (!buf)
		addr1 |= mtd->ग_लिखोsize;
	ग_लिखोl_relaxed(addr1, ctrl->regs + ADDR_REG1);

	अगर (chip->options & न_अंकD_ROW_ADDR_3) अणु
		ग_लिखोl_relaxed(page >> 16, ctrl->regs + ADDR_REG2);
		cmd |= COMMAND_ALE | COMMAND_ALE_SIZE(5);
	पूर्ण अन्यथा अणु
		cmd |= COMMAND_ALE | COMMAND_ALE_SIZE(4);
	पूर्ण

	अगर (buf) अणु
		dma_addr = dma_map_single(ctrl->dev, buf, mtd->ग_लिखोsize, dir);
		ret = dma_mapping_error(ctrl->dev, dma_addr);
		अगर (ret) अणु
			dev_err(ctrl->dev, "dma mapping error\n");
			वापस -EINVAL;
		पूर्ण

		ग_लिखोl_relaxed(mtd->ग_लिखोsize - 1, ctrl->regs + DMA_CFG_A);
		ग_लिखोl_relaxed(dma_addr, ctrl->regs + DATA_PTR);
	पूर्ण

	अगर (oob_buf) अणु
		dma_addr_oob = dma_map_single(ctrl->dev, oob_buf, mtd->oobsize,
					      dir);
		ret = dma_mapping_error(ctrl->dev, dma_addr_oob);
		अगर (ret) अणु
			dev_err(ctrl->dev, "dma mapping error\n");
			ret = -EINVAL;
			जाओ err_unmap_dma_page;
		पूर्ण

		ग_लिखोl_relaxed(oob_len - 1, ctrl->regs + DMA_CFG_B);
		ग_लिखोl_relaxed(dma_addr_oob, ctrl->regs + TAG_PTR);
	पूर्ण

	dma_ctrl = DMA_MST_CTRL_GO | DMA_MST_CTRL_PERF_EN |
		   DMA_MST_CTRL_IE_DONE | DMA_MST_CTRL_IS_DONE |
		   DMA_MST_CTRL_BURST_16;

	अगर (buf)
		dma_ctrl |= DMA_MST_CTRL_EN_A;
	अगर (oob_buf)
		dma_ctrl |= DMA_MST_CTRL_EN_B;

	अगर (पढ़ो)
		dma_ctrl |= DMA_MST_CTRL_IN | DMA_MST_CTRL_REUSE;
	अन्यथा
		dma_ctrl |= DMA_MST_CTRL_OUT;

	ग_लिखोl_relaxed(dma_ctrl, ctrl->regs + DMA_MST_CTRL);

	cmd |= COMMAND_GO | COMMAND_RBSY_CHK | COMMAND_TRANS_SIZE(9) |
	       COMMAND_CE(ctrl->cur_cs);

	अगर (buf)
		cmd |= COMMAND_A_VALID;
	अगर (oob_buf)
		cmd |= COMMAND_B_VALID;

	अगर (पढ़ो)
		cmd |= COMMAND_RX;
	अन्यथा
		cmd |= COMMAND_TX | COMMAND_AFT_DAT;

	ग_लिखोl_relaxed(cmd, ctrl->regs + COMMAND);

	ret = रुको_क्रम_completion_समयout(&ctrl->command_complete,
					  msecs_to_jअगरfies(500));
	अगर (!ret) अणु
		dev_err(ctrl->dev, "COMMAND timeout\n");
		tegra_nand_dump_reg(ctrl);
		tegra_nand_controller_पात(ctrl);
		ret = -ETIMEDOUT;
		जाओ err_unmap_dma;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&ctrl->dma_complete,
					  msecs_to_jअगरfies(500));
	अगर (!ret) अणु
		dev_err(ctrl->dev, "DMA timeout\n");
		tegra_nand_dump_reg(ctrl);
		tegra_nand_controller_पात(ctrl);
		ret = -ETIMEDOUT;
		जाओ err_unmap_dma;
	पूर्ण
	ret = 0;

err_unmap_dma:
	अगर (oob_buf)
		dma_unmap_single(ctrl->dev, dma_addr_oob, mtd->oobsize, dir);
err_unmap_dma_page:
	अगर (buf)
		dma_unmap_single(ctrl->dev, dma_addr, mtd->ग_लिखोsize, dir);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_nand_पढ़ो_page_raw(काष्ठा nand_chip *chip, u8 *buf,
				    पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	व्योम *oob_buf = oob_required ? chip->oob_poi : शून्य;

	वापस tegra_nand_page_xfer(mtd, chip, buf, oob_buf,
				    mtd->oobsize, page, true);
पूर्ण

अटल पूर्णांक tegra_nand_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				     पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	व्योम *oob_buf = oob_required ? chip->oob_poi : शून्य;

	वापस tegra_nand_page_xfer(mtd, chip, (व्योम *)buf, oob_buf,
				     mtd->oobsize, page, false);
पूर्ण

अटल पूर्णांक tegra_nand_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	वापस tegra_nand_page_xfer(mtd, chip, शून्य, chip->oob_poi,
				    mtd->oobsize, page, true);
पूर्ण

अटल पूर्णांक tegra_nand_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	वापस tegra_nand_page_xfer(mtd, chip, शून्य, chip->oob_poi,
				    mtd->oobsize, page, false);
पूर्ण

अटल पूर्णांक tegra_nand_पढ़ो_page_hwecc(काष्ठा nand_chip *chip, u8 *buf,
				      पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा tegra_nand_controller *ctrl = to_tegra_ctrl(chip->controller);
	काष्ठा tegra_nand_chip *nand = to_tegra_chip(chip);
	व्योम *oob_buf = oob_required ? chip->oob_poi : शून्य;
	u32 dec_stat, max_corr_cnt;
	अचिन्हित दीर्घ fail_sec_flag;
	पूर्णांक ret;

	tegra_nand_hw_ecc(ctrl, chip, true);
	ret = tegra_nand_page_xfer(mtd, chip, buf, oob_buf, 0, page, true);
	tegra_nand_hw_ecc(ctrl, chip, false);
	अगर (ret)
		वापस ret;

	/* No correctable or un-correctable errors, page must have 0 bitflips */
	अगर (!ctrl->last_पढ़ो_error)
		वापस 0;

	/*
	 * Correctable or un-correctable errors occurred. Use DEC_STAT_BUF
	 * which contains inक्रमmation क्रम all ECC selections.
	 *
	 * Note that since we करो not use Command Queues DEC_RESULT करोes not
	 * state the number of pages we can पढ़ो from the DEC_STAT_BUF. But
	 * since CORRFAIL_ERR did occur during page पढ़ो we करो have a valid
	 * result in DEC_STAT_BUF.
	 */
	ctrl->last_पढ़ो_error = false;
	dec_stat = पढ़ोl_relaxed(ctrl->regs + DEC_STAT_BUF);

	fail_sec_flag = (dec_stat & DEC_STAT_BUF_FAIL_SEC_FLAG_MASK) >>
			DEC_STAT_BUF_FAIL_SEC_FLAG_SHIFT;

	max_corr_cnt = (dec_stat & DEC_STAT_BUF_MAX_CORR_CNT_MASK) >>
		       DEC_STAT_BUF_MAX_CORR_CNT_SHIFT;

	अगर (fail_sec_flag) अणु
		पूर्णांक bit, max_bitflips = 0;

		/*
		 * Since we करो not support subpage ग_लिखोs, a complete page
		 * is either written or not. We can take a लघुcut here by
		 * checking wheather any of the sector has been successful
		 * पढ़ो. If at least one sectors has been पढ़ो successfully,
		 * the page must have been a written previously. It cannot
		 * be an erased page.
		 *
		 * E.g. controller might वापस fail_sec_flag with 0x4, which
		 * would mean only the third sector failed to correct. The
		 * page must have been written and the third sector is really
		 * not correctable anymore.
		 */
		अगर (fail_sec_flag ^ GENMASK(chip->ecc.steps - 1, 0)) अणु
			mtd->ecc_stats.failed += hweight8(fail_sec_flag);
			वापस max_corr_cnt;
		पूर्ण

		/*
		 * All sectors failed to correct, but the ECC isn't smart
		 * enough to figure out अगर a page is really just erased.
		 * Read OOB data and check whether data/OOB is completely
		 * erased or अगर error correction just failed क्रम all sub-
		 * pages.
		 */
		ret = tegra_nand_पढ़ो_oob(chip, page);
		अगर (ret < 0)
			वापस ret;

		क्रम_each_set_bit(bit, &fail_sec_flag, chip->ecc.steps) अणु
			u8 *data = buf + (chip->ecc.size * bit);
			u8 *oob = chip->oob_poi + nand->ecc.offset +
				  (chip->ecc.bytes * bit);

			ret = nand_check_erased_ecc_chunk(data, chip->ecc.size,
							  oob, chip->ecc.bytes,
							  शून्य, 0,
							  chip->ecc.strength);
			अगर (ret < 0) अणु
				mtd->ecc_stats.failed++;
			पूर्ण अन्यथा अणु
				mtd->ecc_stats.corrected += ret;
				max_bitflips = max(ret, max_bitflips);
			पूर्ण
		पूर्ण

		वापस max_t(अचिन्हित पूर्णांक, max_corr_cnt, max_bitflips);
	पूर्ण अन्यथा अणु
		पूर्णांक corr_sec_flag;

		corr_sec_flag = (dec_stat & DEC_STAT_BUF_CORR_SEC_FLAG_MASK) >>
				DEC_STAT_BUF_CORR_SEC_FLAG_SHIFT;

		/*
		 * The value वापसed in the रेजिस्टर is the maximum of
		 * bitflips encountered in any of the ECC regions. As there is
		 * no way to get the number of bitflips in a specअगरic regions
		 * we are not able to deliver correct stats but instead
		 * overestimate the number of corrected bitflips by assuming
		 * that all regions where errors have been corrected
		 * encountered the maximum number of bitflips.
		 */
		mtd->ecc_stats.corrected += max_corr_cnt * hweight8(corr_sec_flag);

		वापस max_corr_cnt;
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_nand_ग_लिखो_page_hwecc(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				       पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा tegra_nand_controller *ctrl = to_tegra_ctrl(chip->controller);
	व्योम *oob_buf = oob_required ? chip->oob_poi : शून्य;
	पूर्णांक ret;

	tegra_nand_hw_ecc(ctrl, chip, true);
	ret = tegra_nand_page_xfer(mtd, chip, (व्योम *)buf, oob_buf,
				   0, page, false);
	tegra_nand_hw_ecc(ctrl, chip, false);

	वापस ret;
पूर्ण

अटल व्योम tegra_nand_setup_timing(काष्ठा tegra_nand_controller *ctrl,
				    स्थिर काष्ठा nand_sdr_timings *timings)
अणु
	/*
	 * The period (and all other timings in this function) is in ps,
	 * so need to take care here to aव्योम पूर्णांकeger overflows.
	 */
	अचिन्हित पूर्णांक rate = clk_get_rate(ctrl->clk) / 1000000;
	अचिन्हित पूर्णांक period = DIV_ROUND_UP(1000000, rate);
	u32 val, reg = 0;

	val = DIV_ROUND_UP(max3(timings->tAR_min, timings->tRR_min,
				timings->tRC_min), period);
	reg |= TIMING_TCR_TAR_TRR(OFFSET(val, 3));

	val = DIV_ROUND_UP(max(max(timings->tCS_min, timings->tCH_min),
			       max(timings->tALS_min, timings->tALH_min)),
			   period);
	reg |= TIMING_TCS(OFFSET(val, 2));

	val = DIV_ROUND_UP(max(timings->tRP_min, timings->tREA_max) + 6000,
			   period);
	reg |= TIMING_TRP(OFFSET(val, 1)) | TIMING_TRP_RESP(OFFSET(val, 1));

	reg |= TIMING_TWB(OFFSET(DIV_ROUND_UP(timings->tWB_max, period), 1));
	reg |= TIMING_TWHR(OFFSET(DIV_ROUND_UP(timings->tWHR_min, period), 1));
	reg |= TIMING_TWH(OFFSET(DIV_ROUND_UP(timings->tWH_min, period), 1));
	reg |= TIMING_TWP(OFFSET(DIV_ROUND_UP(timings->tWP_min, period), 1));
	reg |= TIMING_TRH(OFFSET(DIV_ROUND_UP(timings->tREH_min, period), 1));

	ग_लिखोl_relaxed(reg, ctrl->regs + TIMING_1);

	val = DIV_ROUND_UP(timings->tADL_min, period);
	reg = TIMING_TADL(OFFSET(val, 3));

	ग_लिखोl_relaxed(reg, ctrl->regs + TIMING_2);
पूर्ण

अटल पूर्णांक tegra_nand_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक csline,
				      स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा tegra_nand_controller *ctrl = to_tegra_ctrl(chip->controller);
	स्थिर काष्ठा nand_sdr_timings *timings;

	timings = nand_get_sdr_timings(conf);
	अगर (IS_ERR(timings))
		वापस PTR_ERR(timings);

	अगर (csline == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	tegra_nand_setup_timing(ctrl, timings);

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक rs_strength_bootable[] = अणु 4 पूर्ण;
अटल स्थिर पूर्णांक rs_strength[] = अणु 4, 6, 8 पूर्ण;
अटल स्थिर पूर्णांक bch_strength_bootable[] = अणु 8, 16 पूर्ण;
अटल स्थिर पूर्णांक bch_strength[] = अणु 4, 8, 14, 16 पूर्ण;

अटल पूर्णांक tegra_nand_get_strength(काष्ठा nand_chip *chip, स्थिर पूर्णांक *strength,
				   पूर्णांक strength_len, पूर्णांक bits_per_step,
				   पूर्णांक oobsize)
अणु
	काष्ठा nand_device *base = mtd_to_nanddev(nand_to_mtd(chip));
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(base);
	bool maximize = base->ecc.user_conf.flags & न_अंकD_ECC_MAXIMIZE_STRENGTH;
	पूर्णांक i;

	/*
	 * Loop through available strengths. Backwards in हाल we try to
	 * maximize the BCH strength.
	 */
	क्रम (i = 0; i < strength_len; i++) अणु
		पूर्णांक strength_sel, bytes_per_step, bytes_per_page;

		अगर (maximize) अणु
			strength_sel = strength[strength_len - i - 1];
		पूर्ण अन्यथा अणु
			strength_sel = strength[i];

			अगर (strength_sel < requirements->strength)
				जारी;
		पूर्ण

		bytes_per_step = DIV_ROUND_UP(bits_per_step * strength_sel,
					      BITS_PER_BYTE);
		bytes_per_page = round_up(bytes_per_step * chip->ecc.steps, 4);

		/* Check whether strength fits OOB */
		अगर (bytes_per_page < (oobsize - SKIP_SPARE_BYTES))
			वापस strength_sel;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tegra_nand_select_strength(काष्ठा nand_chip *chip, पूर्णांक oobsize)
अणु
	स्थिर पूर्णांक *strength;
	पूर्णांक strength_len, bits_per_step;

	चयन (chip->ecc.algo) अणु
	हाल न_अंकD_ECC_ALGO_RS:
		bits_per_step = BITS_PER_STEP_RS;
		अगर (chip->options & न_अंकD_IS_BOOT_MEDIUM) अणु
			strength = rs_strength_bootable;
			strength_len = ARRAY_SIZE(rs_strength_bootable);
		पूर्ण अन्यथा अणु
			strength = rs_strength;
			strength_len = ARRAY_SIZE(rs_strength);
		पूर्ण
		अवरोध;
	हाल न_अंकD_ECC_ALGO_BCH:
		bits_per_step = BITS_PER_STEP_BCH;
		अगर (chip->options & न_अंकD_IS_BOOT_MEDIUM) अणु
			strength = bch_strength_bootable;
			strength_len = ARRAY_SIZE(bch_strength_bootable);
		पूर्ण अन्यथा अणु
			strength = bch_strength;
			strength_len = ARRAY_SIZE(bch_strength);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस tegra_nand_get_strength(chip, strength, strength_len,
				       bits_per_step, oobsize);
पूर्ण

अटल पूर्णांक tegra_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा tegra_nand_controller *ctrl = to_tegra_ctrl(chip->controller);
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(&chip->base);
	काष्ठा tegra_nand_chip *nand = to_tegra_chip(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक bits_per_step;
	पूर्णांक ret;

	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH)
		chip->bbt_options |= न_अंकD_BBT_NO_OOB;

	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
	chip->ecc.size = 512;
	chip->ecc.steps = mtd->ग_लिखोsize / chip->ecc.size;
	अगर (requirements->step_size != 512) अणु
		dev_err(ctrl->dev, "Unsupported step size %d\n",
			requirements->step_size);
		वापस -EINVAL;
	पूर्ण

	chip->ecc.पढ़ो_page = tegra_nand_पढ़ो_page_hwecc;
	chip->ecc.ग_लिखो_page = tegra_nand_ग_लिखो_page_hwecc;
	chip->ecc.पढ़ो_page_raw = tegra_nand_पढ़ो_page_raw;
	chip->ecc.ग_लिखो_page_raw = tegra_nand_ग_लिखो_page_raw;
	chip->ecc.पढ़ो_oob = tegra_nand_पढ़ो_oob;
	chip->ecc.ग_लिखो_oob = tegra_nand_ग_लिखो_oob;

	अगर (chip->options & न_अंकD_BUSWIDTH_16)
		nand->config |= CONFIG_BUS_WIDTH_16;

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_UNKNOWN) अणु
		अगर (mtd->ग_लिखोsize < 2048)
			chip->ecc.algo = न_अंकD_ECC_ALGO_RS;
		अन्यथा
			chip->ecc.algo = न_अंकD_ECC_ALGO_BCH;
	पूर्ण

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_BCH && mtd->ग_लिखोsize < 2048) अणु
		dev_err(ctrl->dev, "BCH supports 2K or 4K page size only\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!chip->ecc.strength) अणु
		ret = tegra_nand_select_strength(chip, mtd->oobsize);
		अगर (ret < 0) अणु
			dev_err(ctrl->dev,
				"No valid strength found, minimum %d\n",
				requirements->strength);
			वापस ret;
		पूर्ण

		chip->ecc.strength = ret;
	पूर्ण

	nand->config_ecc = CONFIG_PIPE_EN | CONFIG_SKIP_SPARE |
			   CONFIG_SKIP_SPARE_SIZE_4;

	चयन (chip->ecc.algo) अणु
	हाल न_अंकD_ECC_ALGO_RS:
		bits_per_step = BITS_PER_STEP_RS * chip->ecc.strength;
		mtd_set_ooblayout(mtd, &tegra_nand_oob_rs_ops);
		nand->config_ecc |= CONFIG_HW_ECC | CONFIG_ECC_SEL |
				    CONFIG_ERR_COR;
		चयन (chip->ecc.strength) अणु
		हाल 4:
			nand->config_ecc |= CONFIG_TVAL_4;
			अवरोध;
		हाल 6:
			nand->config_ecc |= CONFIG_TVAL_6;
			अवरोध;
		हाल 8:
			nand->config_ecc |= CONFIG_TVAL_8;
			अवरोध;
		शेष:
			dev_err(ctrl->dev, "ECC strength %d not supported\n",
				chip->ecc.strength);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल न_अंकD_ECC_ALGO_BCH:
		bits_per_step = BITS_PER_STEP_BCH * chip->ecc.strength;
		mtd_set_ooblayout(mtd, &tegra_nand_oob_bch_ops);
		nand->bch_config = BCH_ENABLE;
		चयन (chip->ecc.strength) अणु
		हाल 4:
			nand->bch_config |= BCH_TVAL_4;
			अवरोध;
		हाल 8:
			nand->bch_config |= BCH_TVAL_8;
			अवरोध;
		हाल 14:
			nand->bch_config |= BCH_TVAL_14;
			अवरोध;
		हाल 16:
			nand->bch_config |= BCH_TVAL_16;
			अवरोध;
		शेष:
			dev_err(ctrl->dev, "ECC strength %d not supported\n",
				chip->ecc.strength);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(ctrl->dev, "ECC algorithm not supported\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(ctrl->dev, "Using %s with strength %d per 512 byte step\n",
		 chip->ecc.algo == न_अंकD_ECC_ALGO_BCH ? "BCH" : "RS",
		 chip->ecc.strength);

	chip->ecc.bytes = DIV_ROUND_UP(bits_per_step, BITS_PER_BYTE);

	चयन (mtd->ग_लिखोsize) अणु
	हाल 256:
		nand->config |= CONFIG_PS_256;
		अवरोध;
	हाल 512:
		nand->config |= CONFIG_PS_512;
		अवरोध;
	हाल 1024:
		nand->config |= CONFIG_PS_1024;
		अवरोध;
	हाल 2048:
		nand->config |= CONFIG_PS_2048;
		अवरोध;
	हाल 4096:
		nand->config |= CONFIG_PS_4096;
		अवरोध;
	शेष:
		dev_err(ctrl->dev, "Unsupported writesize %d\n",
			mtd->ग_लिखोsize);
		वापस -ENODEV;
	पूर्ण

	/* Store complete configuration क्रम HW ECC in config_ecc */
	nand->config_ecc |= nand->config;

	/* Non-HW ECC पढ़ो/ग_लिखोs complete OOB */
	nand->config |= CONFIG_TAG_BYTE_SIZE(mtd->oobsize - 1);
	ग_लिखोl_relaxed(nand->config, ctrl->regs + CONFIG);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops tegra_nand_controller_ops = अणु
	.attach_chip = &tegra_nand_attach_chip,
	.exec_op = tegra_nand_exec_op,
	.setup_पूर्णांकerface = tegra_nand_setup_पूर्णांकerface,
पूर्ण;

अटल पूर्णांक tegra_nand_chips_init(काष्ठा device *dev,
				 काष्ठा tegra_nand_controller *ctrl)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *np_nand;
	पूर्णांक nsels, nchips = of_get_child_count(np);
	काष्ठा tegra_nand_chip *nand;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;
	u32 cs;

	अगर (nchips != 1) अणु
		dev_err(dev, "Currently only one NAND chip supported\n");
		वापस -EINVAL;
	पूर्ण

	np_nand = of_get_next_child(np, शून्य);

	nsels = of_property_count_elems_of_size(np_nand, "reg", माप(u32));
	अगर (nsels != 1) अणु
		dev_err(dev, "Missing/invalid reg property\n");
		वापस -EINVAL;
	पूर्ण

	/* Retrieve CS id, currently only single die न_अंकD supported */
	ret = of_property_पढ़ो_u32(np_nand, "reg", &cs);
	अगर (ret) अणु
		dev_err(dev, "could not retrieve reg property: %d\n", ret);
		वापस ret;
	पूर्ण

	nand = devm_kzalloc(dev, माप(*nand), GFP_KERNEL);
	अगर (!nand)
		वापस -ENOMEM;

	nand->cs[0] = cs;

	nand->wp_gpio = devm_gpiod_get_optional(dev, "wp", GPIOD_OUT_LOW);

	अगर (IS_ERR(nand->wp_gpio)) अणु
		ret = PTR_ERR(nand->wp_gpio);
		dev_err(dev, "Failed to request WP GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	chip = &nand->chip;
	chip->controller = &ctrl->controller;

	mtd = nand_to_mtd(chip);

	mtd->dev.parent = dev;
	mtd->owner = THIS_MODULE;

	nand_set_flash_node(chip, np_nand);

	अगर (!mtd->name)
		mtd->name = "tegra_nand";

	chip->options = न_अंकD_NO_SUBPAGE_WRITE | न_अंकD_USES_DMA;

	ret = nand_scan(chip, 1);
	अगर (ret)
		वापस ret;

	mtd_ooblayout_ecc(mtd, 0, &nand->ecc);

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "Failed to register mtd device: %d\n", ret);
		nand_cleanup(chip);
		वापस ret;
	पूर्ण

	ctrl->chip = chip;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा reset_control *rst;
	काष्ठा tegra_nand_controller *ctrl;
	काष्ठा resource *res;
	पूर्णांक err = 0;

	ctrl = devm_kzalloc(&pdev->dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	ctrl->dev = &pdev->dev;
	nand_controller_init(&ctrl->controller);
	ctrl->controller.ops = &tegra_nand_controller_ops;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ctrl->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ctrl->regs))
		वापस PTR_ERR(ctrl->regs);

	rst = devm_reset_control_get(&pdev->dev, "nand");
	अगर (IS_ERR(rst))
		वापस PTR_ERR(rst);

	ctrl->clk = devm_clk_get(&pdev->dev, "nand");
	अगर (IS_ERR(ctrl->clk))
		वापस PTR_ERR(ctrl->clk);

	err = clk_prepare_enable(ctrl->clk);
	अगर (err)
		वापस err;

	err = reset_control_reset(rst);
	अगर (err) अणु
		dev_err(ctrl->dev, "Failed to reset HW: %d\n", err);
		जाओ err_disable_clk;
	पूर्ण

	ग_लिखोl_relaxed(HWSTATUS_CMD_DEFAULT, ctrl->regs + HWSTATUS_CMD);
	ग_लिखोl_relaxed(HWSTATUS_MASK_DEFAULT, ctrl->regs + HWSTATUS_MASK);
	ग_लिखोl_relaxed(INT_MASK, ctrl->regs + IER);

	init_completion(&ctrl->command_complete);
	init_completion(&ctrl->dma_complete);

	ctrl->irq = platक्रमm_get_irq(pdev, 0);
	err = devm_request_irq(&pdev->dev, ctrl->irq, tegra_nand_irq, 0,
			       dev_name(&pdev->dev), ctrl);
	अगर (err) अणु
		dev_err(ctrl->dev, "Failed to get IRQ: %d\n", err);
		जाओ err_disable_clk;
	पूर्ण

	ग_लिखोl_relaxed(DMA_MST_CTRL_IS_DONE, ctrl->regs + DMA_MST_CTRL);

	err = tegra_nand_chips_init(ctrl->dev, ctrl);
	अगर (err)
		जाओ err_disable_clk;

	platक्रमm_set_drvdata(pdev, ctrl);

	वापस 0;

err_disable_clk:
	clk_disable_unprepare(ctrl->clk);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_nand_controller *ctrl = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = ctrl->chip;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(mtd);
	अगर (ret)
		वापस ret;

	nand_cleanup(chip);

	clk_disable_unprepare(ctrl->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_nand_of_match[] = अणु
	अणु .compatible = "nvidia,tegra20-nand" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_nand_of_match);

अटल काष्ठा platक्रमm_driver tegra_nand_driver = अणु
	.driver = अणु
		.name = "tegra-nand",
		.of_match_table = tegra_nand_of_match,
	पूर्ण,
	.probe = tegra_nand_probe,
	.हटाओ = tegra_nand_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_nand_driver);

MODULE_DESCRIPTION("NVIDIA Tegra NAND driver");
MODULE_AUTHOR("Thierry Reding <thierry.reding@nvidia.com>");
MODULE_AUTHOR("Lucas Stach <dev@lynxeye.de>");
MODULE_AUTHOR("Stefan Agner <stefan@agner.ch>");
MODULE_LICENSE("GPL v2");
