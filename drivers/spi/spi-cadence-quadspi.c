<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Driver क्रम Cadence QSPI Controller
//
// Copyright Altera Corporation (C) 2012-2014. All rights reserved.
// Copyright Intel Corporation (C) 2019-2020. All rights reserved.
// Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/sched.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>
#समावेश <linux/समयr.h>

#घोषणा CQSPI_NAME			"cadence-qspi"
#घोषणा CQSPI_MAX_CHIPSELECT		16

/* Quirks */
#घोषणा CQSPI_NEEDS_WR_DELAY		BIT(0)
#घोषणा CQSPI_DISABLE_DAC_MODE		BIT(1)

/* Capabilities */
#घोषणा CQSPI_SUPPORTS_OCTAL		BIT(0)

काष्ठा cqspi_st;

काष्ठा cqspi_flash_pdata अणु
	काष्ठा cqspi_st	*cqspi;
	u32		clk_rate;
	u32		पढ़ो_delay;
	u32		tshsl_ns;
	u32		tsd2d_ns;
	u32		tchsh_ns;
	u32		tslch_ns;
	u8		inst_width;
	u8		addr_width;
	u8		data_width;
	bool		dtr;
	u8		cs;
पूर्ण;

काष्ठा cqspi_st अणु
	काष्ठा platक्रमm_device	*pdev;

	काष्ठा clk		*clk;
	अचिन्हित पूर्णांक		sclk;

	व्योम __iomem		*iobase;
	व्योम __iomem		*ahb_base;
	resource_माप_प्रकार		ahb_size;
	काष्ठा completion	transfer_complete;

	काष्ठा dma_chan		*rx_chan;
	काष्ठा completion	rx_dma_complete;
	dma_addr_t		mmap_phys_base;

	पूर्णांक			current_cs;
	अचिन्हित दीर्घ		master_ref_clk_hz;
	bool			is_decoded_cs;
	u32			fअगरo_depth;
	u32			fअगरo_width;
	u32			num_chipselect;
	bool			rclk_en;
	u32			trigger_address;
	u32			wr_delay;
	bool			use_direct_mode;
	काष्ठा cqspi_flash_pdata f_pdata[CQSPI_MAX_CHIPSELECT];
पूर्ण;

काष्ठा cqspi_driver_platdata अणु
	u32 hwcaps_mask;
	u8 quirks;
पूर्ण;

/* Operation समयout value */
#घोषणा CQSPI_TIMEOUT_MS			500
#घोषणा CQSPI_READ_TIMEOUT_MS			10

/* Inकाष्ठाion type */
#घोषणा CQSPI_INST_TYPE_SINGLE			0
#घोषणा CQSPI_INST_TYPE_DUAL			1
#घोषणा CQSPI_INST_TYPE_QUAD			2
#घोषणा CQSPI_INST_TYPE_OCTAL			3

#घोषणा CQSPI_DUMMY_CLKS_PER_BYTE		8
#घोषणा CQSPI_DUMMY_BYTES_MAX			4
#घोषणा CQSPI_DUMMY_CLKS_MAX			31

#घोषणा CQSPI_STIG_DATA_LEN_MAX			8

/* Register map */
#घोषणा CQSPI_REG_CONFIG			0x00
#घोषणा CQSPI_REG_CONFIG_ENABLE_MASK		BIT(0)
#घोषणा CQSPI_REG_CONFIG_ENB_सूची_ACC_CTRL	BIT(7)
#घोषणा CQSPI_REG_CONFIG_DECODE_MASK		BIT(9)
#घोषणा CQSPI_REG_CONFIG_CHIPSELECT_LSB		10
#घोषणा CQSPI_REG_CONFIG_DMA_MASK		BIT(15)
#घोषणा CQSPI_REG_CONFIG_BAUD_LSB		19
#घोषणा CQSPI_REG_CONFIG_DTR_PROTO		BIT(24)
#घोषणा CQSPI_REG_CONFIG_DUAL_OPCODE		BIT(30)
#घोषणा CQSPI_REG_CONFIG_IDLE_LSB		31
#घोषणा CQSPI_REG_CONFIG_CHIPSELECT_MASK	0xF
#घोषणा CQSPI_REG_CONFIG_BAUD_MASK		0xF

#घोषणा CQSPI_REG_RD_INSTR			0x04
#घोषणा CQSPI_REG_RD_INSTR_OPCODE_LSB		0
#घोषणा CQSPI_REG_RD_INSTR_TYPE_INSTR_LSB	8
#घोषणा CQSPI_REG_RD_INSTR_TYPE_ADDR_LSB	12
#घोषणा CQSPI_REG_RD_INSTR_TYPE_DATA_LSB	16
#घोषणा CQSPI_REG_RD_INSTR_MODE_EN_LSB		20
#घोषणा CQSPI_REG_RD_INSTR_DUMMY_LSB		24
#घोषणा CQSPI_REG_RD_INSTR_TYPE_INSTR_MASK	0x3
#घोषणा CQSPI_REG_RD_INSTR_TYPE_ADDR_MASK	0x3
#घोषणा CQSPI_REG_RD_INSTR_TYPE_DATA_MASK	0x3
#घोषणा CQSPI_REG_RD_INSTR_DUMMY_MASK		0x1F

#घोषणा CQSPI_REG_WR_INSTR			0x08
#घोषणा CQSPI_REG_WR_INSTR_OPCODE_LSB		0
#घोषणा CQSPI_REG_WR_INSTR_TYPE_ADDR_LSB	12
#घोषणा CQSPI_REG_WR_INSTR_TYPE_DATA_LSB	16

#घोषणा CQSPI_REG_DELAY				0x0C
#घोषणा CQSPI_REG_DELAY_TSLCH_LSB		0
#घोषणा CQSPI_REG_DELAY_TCHSH_LSB		8
#घोषणा CQSPI_REG_DELAY_TSD2D_LSB		16
#घोषणा CQSPI_REG_DELAY_TSHSL_LSB		24
#घोषणा CQSPI_REG_DELAY_TSLCH_MASK		0xFF
#घोषणा CQSPI_REG_DELAY_TCHSH_MASK		0xFF
#घोषणा CQSPI_REG_DELAY_TSD2D_MASK		0xFF
#घोषणा CQSPI_REG_DELAY_TSHSL_MASK		0xFF

#घोषणा CQSPI_REG_READCAPTURE			0x10
#घोषणा CQSPI_REG_READCAPTURE_BYPASS_LSB	0
#घोषणा CQSPI_REG_READCAPTURE_DELAY_LSB		1
#घोषणा CQSPI_REG_READCAPTURE_DELAY_MASK	0xF

#घोषणा CQSPI_REG_SIZE				0x14
#घोषणा CQSPI_REG_SIZE_ADDRESS_LSB		0
#घोषणा CQSPI_REG_SIZE_PAGE_LSB			4
#घोषणा CQSPI_REG_SIZE_BLOCK_LSB		16
#घोषणा CQSPI_REG_SIZE_ADDRESS_MASK		0xF
#घोषणा CQSPI_REG_SIZE_PAGE_MASK		0xFFF
#घोषणा CQSPI_REG_SIZE_BLOCK_MASK		0x3F

#घोषणा CQSPI_REG_SRAMPARTITION			0x18
#घोषणा CQSPI_REG_INसूचीECTTRIGGER		0x1C

#घोषणा CQSPI_REG_DMA				0x20
#घोषणा CQSPI_REG_DMA_SINGLE_LSB		0
#घोषणा CQSPI_REG_DMA_BURST_LSB			8
#घोषणा CQSPI_REG_DMA_SINGLE_MASK		0xFF
#घोषणा CQSPI_REG_DMA_BURST_MASK		0xFF

#घोषणा CQSPI_REG_REMAP				0x24
#घोषणा CQSPI_REG_MODE_BIT			0x28

#घोषणा CQSPI_REG_SDRAMLEVEL			0x2C
#घोषणा CQSPI_REG_SDRAMLEVEL_RD_LSB		0
#घोषणा CQSPI_REG_SDRAMLEVEL_WR_LSB		16
#घोषणा CQSPI_REG_SDRAMLEVEL_RD_MASK		0xFFFF
#घोषणा CQSPI_REG_SDRAMLEVEL_WR_MASK		0xFFFF

#घोषणा CQSPI_REG_WR_COMPLETION_CTRL		0x38
#घोषणा CQSPI_REG_WR_DISABLE_AUTO_POLL		BIT(14)

#घोषणा CQSPI_REG_IRQSTATUS			0x40
#घोषणा CQSPI_REG_IRQMASK			0x44

#घोषणा CQSPI_REG_INसूचीECTRD			0x60
#घोषणा CQSPI_REG_INसूचीECTRD_START_MASK		BIT(0)
#घोषणा CQSPI_REG_INसूचीECTRD_CANCEL_MASK	BIT(1)
#घोषणा CQSPI_REG_INसूचीECTRD_DONE_MASK		BIT(5)

#घोषणा CQSPI_REG_INसूचीECTRDWATERMARK		0x64
#घोषणा CQSPI_REG_INसूचीECTRDSTARTADDR		0x68
#घोषणा CQSPI_REG_INसूचीECTRDBYTES		0x6C

#घोषणा CQSPI_REG_CMDCTRL			0x90
#घोषणा CQSPI_REG_CMDCTRL_EXECUTE_MASK		BIT(0)
#घोषणा CQSPI_REG_CMDCTRL_INPROGRESS_MASK	BIT(1)
#घोषणा CQSPI_REG_CMDCTRL_DUMMY_LSB		7
#घोषणा CQSPI_REG_CMDCTRL_WR_BYTES_LSB		12
#घोषणा CQSPI_REG_CMDCTRL_WR_EN_LSB		15
#घोषणा CQSPI_REG_CMDCTRL_ADD_BYTES_LSB		16
#घोषणा CQSPI_REG_CMDCTRL_ADDR_EN_LSB		19
#घोषणा CQSPI_REG_CMDCTRL_RD_BYTES_LSB		20
#घोषणा CQSPI_REG_CMDCTRL_RD_EN_LSB		23
#घोषणा CQSPI_REG_CMDCTRL_OPCODE_LSB		24
#घोषणा CQSPI_REG_CMDCTRL_WR_BYTES_MASK		0x7
#घोषणा CQSPI_REG_CMDCTRL_ADD_BYTES_MASK	0x3
#घोषणा CQSPI_REG_CMDCTRL_RD_BYTES_MASK		0x7
#घोषणा CQSPI_REG_CMDCTRL_DUMMY_MASK		0x1F

#घोषणा CQSPI_REG_INसूचीECTWR			0x70
#घोषणा CQSPI_REG_INसूचीECTWR_START_MASK		BIT(0)
#घोषणा CQSPI_REG_INसूचीECTWR_CANCEL_MASK	BIT(1)
#घोषणा CQSPI_REG_INसूचीECTWR_DONE_MASK		BIT(5)

#घोषणा CQSPI_REG_INसूचीECTWRWATERMARK		0x74
#घोषणा CQSPI_REG_INसूचीECTWRSTARTADDR		0x78
#घोषणा CQSPI_REG_INसूचीECTWRBYTES		0x7C

#घोषणा CQSPI_REG_CMDADDRESS			0x94
#घोषणा CQSPI_REG_CMDREADDATALOWER		0xA0
#घोषणा CQSPI_REG_CMDREADDATAUPPER		0xA4
#घोषणा CQSPI_REG_CMDWRITEDATALOWER		0xA8
#घोषणा CQSPI_REG_CMDWRITEDATAUPPER		0xAC

#घोषणा CQSPI_REG_POLLING_STATUS		0xB0
#घोषणा CQSPI_REG_POLLING_STATUS_DUMMY_LSB	16

#घोषणा CQSPI_REG_OP_EXT_LOWER			0xE0
#घोषणा CQSPI_REG_OP_EXT_READ_LSB		24
#घोषणा CQSPI_REG_OP_EXT_WRITE_LSB		16
#घोषणा CQSPI_REG_OP_EXT_STIG_LSB		0

/* Interrupt status bits */
#घोषणा CQSPI_REG_IRQ_MODE_ERR			BIT(0)
#घोषणा CQSPI_REG_IRQ_UNDERFLOW			BIT(1)
#घोषणा CQSPI_REG_IRQ_IND_COMP			BIT(2)
#घोषणा CQSPI_REG_IRQ_IND_RD_REJECT		BIT(3)
#घोषणा CQSPI_REG_IRQ_WR_PROTECTED_ERR		BIT(4)
#घोषणा CQSPI_REG_IRQ_ILLEGAL_AHB_ERR		BIT(5)
#घोषणा CQSPI_REG_IRQ_WATERMARK			BIT(6)
#घोषणा CQSPI_REG_IRQ_IND_SRAM_FULL		BIT(12)

#घोषणा CQSPI_IRQ_MASK_RD		(CQSPI_REG_IRQ_WATERMARK	| \
					 CQSPI_REG_IRQ_IND_SRAM_FULL	| \
					 CQSPI_REG_IRQ_IND_COMP)

#घोषणा CQSPI_IRQ_MASK_WR		(CQSPI_REG_IRQ_IND_COMP		| \
					 CQSPI_REG_IRQ_WATERMARK	| \
					 CQSPI_REG_IRQ_UNDERFLOW)

#घोषणा CQSPI_IRQ_STATUS_MASK		0x1FFFF

अटल पूर्णांक cqspi_रुको_क्रम_bit(व्योम __iomem *reg, स्थिर u32 mask, bool clr)
अणु
	u32 val;

	वापस पढ़ोl_relaxed_poll_समयout(reg, val,
					  (((clr ? ~val : val) & mask) == mask),
					  10, CQSPI_TIMEOUT_MS * 1000);
पूर्ण

अटल bool cqspi_is_idle(काष्ठा cqspi_st *cqspi)
अणु
	u32 reg = पढ़ोl(cqspi->iobase + CQSPI_REG_CONFIG);

	वापस reg & (1UL << CQSPI_REG_CONFIG_IDLE_LSB);
पूर्ण

अटल u32 cqspi_get_rd_sram_level(काष्ठा cqspi_st *cqspi)
अणु
	u32 reg = पढ़ोl(cqspi->iobase + CQSPI_REG_SDRAMLEVEL);

	reg >>= CQSPI_REG_SDRAMLEVEL_RD_LSB;
	वापस reg & CQSPI_REG_SDRAMLEVEL_RD_MASK;
पूर्ण

अटल irqवापस_t cqspi_irq_handler(पूर्णांक this_irq, व्योम *dev)
अणु
	काष्ठा cqspi_st *cqspi = dev;
	अचिन्हित पूर्णांक irq_status;

	/* Read पूर्णांकerrupt status */
	irq_status = पढ़ोl(cqspi->iobase + CQSPI_REG_IRQSTATUS);

	/* Clear पूर्णांकerrupt */
	ग_लिखोl(irq_status, cqspi->iobase + CQSPI_REG_IRQSTATUS);

	irq_status &= CQSPI_IRQ_MASK_RD | CQSPI_IRQ_MASK_WR;

	अगर (irq_status)
		complete(&cqspi->transfer_complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक cqspi_calc_rdreg(काष्ठा cqspi_flash_pdata *f_pdata)
अणु
	u32 rdreg = 0;

	rdreg |= f_pdata->inst_width << CQSPI_REG_RD_INSTR_TYPE_INSTR_LSB;
	rdreg |= f_pdata->addr_width << CQSPI_REG_RD_INSTR_TYPE_ADDR_LSB;
	rdreg |= f_pdata->data_width << CQSPI_REG_RD_INSTR_TYPE_DATA_LSB;

	वापस rdreg;
पूर्ण

अटल अचिन्हित पूर्णांक cqspi_calc_dummy(स्थिर काष्ठा spi_mem_op *op, bool dtr)
अणु
	अचिन्हित पूर्णांक dummy_clk;

	dummy_clk = op->dummy.nbytes * (8 / op->dummy.buswidth);
	अगर (dtr)
		dummy_clk /= 2;

	वापस dummy_clk;
पूर्ण

अटल पूर्णांक cqspi_set_protocol(काष्ठा cqspi_flash_pdata *f_pdata,
			      स्थिर काष्ठा spi_mem_op *op)
अणु
	f_pdata->inst_width = CQSPI_INST_TYPE_SINGLE;
	f_pdata->addr_width = CQSPI_INST_TYPE_SINGLE;
	f_pdata->data_width = CQSPI_INST_TYPE_SINGLE;
	f_pdata->dtr = op->data.dtr && op->cmd.dtr && op->addr.dtr;

	चयन (op->data.buswidth) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		f_pdata->data_width = CQSPI_INST_TYPE_SINGLE;
		अवरोध;
	हाल 2:
		f_pdata->data_width = CQSPI_INST_TYPE_DUAL;
		अवरोध;
	हाल 4:
		f_pdata->data_width = CQSPI_INST_TYPE_QUAD;
		अवरोध;
	हाल 8:
		f_pdata->data_width = CQSPI_INST_TYPE_OCTAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Right now we only support 8-8-8 DTR mode. */
	अगर (f_pdata->dtr) अणु
		चयन (op->cmd.buswidth) अणु
		हाल 0:
			अवरोध;
		हाल 8:
			f_pdata->inst_width = CQSPI_INST_TYPE_OCTAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		चयन (op->addr.buswidth) अणु
		हाल 0:
			अवरोध;
		हाल 8:
			f_pdata->addr_width = CQSPI_INST_TYPE_OCTAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		चयन (op->data.buswidth) अणु
		हाल 0:
			अवरोध;
		हाल 8:
			f_pdata->data_width = CQSPI_INST_TYPE_OCTAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cqspi_रुको_idle(काष्ठा cqspi_st *cqspi)
अणु
	स्थिर अचिन्हित पूर्णांक poll_idle_retry = 3;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(CQSPI_TIMEOUT_MS);
	जबतक (1) अणु
		/*
		 * Read few बार in succession to ensure the controller
		 * is indeed idle, that is, the bit करोes not transition
		 * low again.
		 */
		अगर (cqspi_is_idle(cqspi))
			count++;
		अन्यथा
			count = 0;

		अगर (count >= poll_idle_retry)
			वापस 0;

		अगर (समय_after(jअगरfies, समयout)) अणु
			/* Timeout, in busy mode. */
			dev_err(&cqspi->pdev->dev,
				"QSPI is still busy after %dms timeout.\n",
				CQSPI_TIMEOUT_MS);
			वापस -ETIMEDOUT;
		पूर्ण

		cpu_relax();
	पूर्ण
पूर्ण

अटल पूर्णांक cqspi_exec_flash_cmd(काष्ठा cqspi_st *cqspi, अचिन्हित पूर्णांक reg)
अणु
	व्योम __iomem *reg_base = cqspi->iobase;
	पूर्णांक ret;

	/* Write the CMDCTRL without start execution. */
	ग_लिखोl(reg, reg_base + CQSPI_REG_CMDCTRL);
	/* Start execute */
	reg |= CQSPI_REG_CMDCTRL_EXECUTE_MASK;
	ग_लिखोl(reg, reg_base + CQSPI_REG_CMDCTRL);

	/* Polling क्रम completion. */
	ret = cqspi_रुको_क्रम_bit(reg_base + CQSPI_REG_CMDCTRL,
				 CQSPI_REG_CMDCTRL_INPROGRESS_MASK, 1);
	अगर (ret) अणु
		dev_err(&cqspi->pdev->dev,
			"Flash command execution timed out.\n");
		वापस ret;
	पूर्ण

	/* Polling QSPI idle status. */
	वापस cqspi_रुको_idle(cqspi);
पूर्ण

अटल पूर्णांक cqspi_setup_opcode_ext(काष्ठा cqspi_flash_pdata *f_pdata,
				  स्थिर काष्ठा spi_mem_op *op,
				  अचिन्हित पूर्णांक shअगरt)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	व्योम __iomem *reg_base = cqspi->iobase;
	अचिन्हित पूर्णांक reg;
	u8 ext;

	अगर (op->cmd.nbytes != 2)
		वापस -EINVAL;

	/* Opcode extension is the LSB. */
	ext = op->cmd.opcode & 0xff;

	reg = पढ़ोl(reg_base + CQSPI_REG_OP_EXT_LOWER);
	reg &= ~(0xff << shअगरt);
	reg |= ext << shअगरt;
	ग_लिखोl(reg, reg_base + CQSPI_REG_OP_EXT_LOWER);

	वापस 0;
पूर्ण

अटल पूर्णांक cqspi_enable_dtr(काष्ठा cqspi_flash_pdata *f_pdata,
			    स्थिर काष्ठा spi_mem_op *op, अचिन्हित पूर्णांक shअगरt,
			    bool enable)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	व्योम __iomem *reg_base = cqspi->iobase;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	reg = पढ़ोl(reg_base + CQSPI_REG_CONFIG);

	/*
	 * We enable dual byte opcode here. The callers have to set up the
	 * extension opcode based on which type of operation it is.
	 */
	अगर (enable) अणु
		reg |= CQSPI_REG_CONFIG_DTR_PROTO;
		reg |= CQSPI_REG_CONFIG_DUAL_OPCODE;

		/* Set up command opcode extension. */
		ret = cqspi_setup_opcode_ext(f_pdata, op, shअगरt);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		reg &= ~CQSPI_REG_CONFIG_DTR_PROTO;
		reg &= ~CQSPI_REG_CONFIG_DUAL_OPCODE;
	पूर्ण

	ग_लिखोl(reg, reg_base + CQSPI_REG_CONFIG);

	वापस cqspi_रुको_idle(cqspi);
पूर्ण

अटल पूर्णांक cqspi_command_पढ़ो(काष्ठा cqspi_flash_pdata *f_pdata,
			      स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	व्योम __iomem *reg_base = cqspi->iobase;
	u8 *rxbuf = op->data.buf.in;
	u8 opcode;
	माप_प्रकार n_rx = op->data.nbytes;
	अचिन्हित पूर्णांक rdreg;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक dummy_clk;
	माप_प्रकार पढ़ो_len;
	पूर्णांक status;

	status = cqspi_set_protocol(f_pdata, op);
	अगर (status)
		वापस status;

	status = cqspi_enable_dtr(f_pdata, op, CQSPI_REG_OP_EXT_STIG_LSB,
				  f_pdata->dtr);
	अगर (status)
		वापस status;

	अगर (!n_rx || n_rx > CQSPI_STIG_DATA_LEN_MAX || !rxbuf) अणु
		dev_err(&cqspi->pdev->dev,
			"Invalid input argument, len %zu rxbuf 0x%p\n",
			n_rx, rxbuf);
		वापस -EINVAL;
	पूर्ण

	अगर (f_pdata->dtr)
		opcode = op->cmd.opcode >> 8;
	अन्यथा
		opcode = op->cmd.opcode;

	reg = opcode << CQSPI_REG_CMDCTRL_OPCODE_LSB;

	rdreg = cqspi_calc_rdreg(f_pdata);
	ग_लिखोl(rdreg, reg_base + CQSPI_REG_RD_INSTR);

	dummy_clk = cqspi_calc_dummy(op, f_pdata->dtr);
	अगर (dummy_clk > CQSPI_DUMMY_CLKS_MAX)
		वापस -EOPNOTSUPP;

	अगर (dummy_clk)
		reg |= (dummy_clk & CQSPI_REG_CMDCTRL_DUMMY_MASK)
		     << CQSPI_REG_CMDCTRL_DUMMY_LSB;

	reg |= (0x1 << CQSPI_REG_CMDCTRL_RD_EN_LSB);

	/* 0 means 1 byte. */
	reg |= (((n_rx - 1) & CQSPI_REG_CMDCTRL_RD_BYTES_MASK)
		<< CQSPI_REG_CMDCTRL_RD_BYTES_LSB);
	status = cqspi_exec_flash_cmd(cqspi, reg);
	अगर (status)
		वापस status;

	reg = पढ़ोl(reg_base + CQSPI_REG_CMDREADDATALOWER);

	/* Put the पढ़ो value पूर्णांकo rx_buf */
	पढ़ो_len = (n_rx > 4) ? 4 : n_rx;
	स_नकल(rxbuf, &reg, पढ़ो_len);
	rxbuf += पढ़ो_len;

	अगर (n_rx > 4) अणु
		reg = पढ़ोl(reg_base + CQSPI_REG_CMDREADDATAUPPER);

		पढ़ो_len = n_rx - पढ़ो_len;
		स_नकल(rxbuf, &reg, पढ़ो_len);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cqspi_command_ग_लिखो(काष्ठा cqspi_flash_pdata *f_pdata,
			       स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	व्योम __iomem *reg_base = cqspi->iobase;
	u8 opcode;
	स्थिर u8 *txbuf = op->data.buf.out;
	माप_प्रकार n_tx = op->data.nbytes;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक data;
	माप_प्रकार ग_लिखो_len;
	पूर्णांक ret;

	ret = cqspi_set_protocol(f_pdata, op);
	अगर (ret)
		वापस ret;

	ret = cqspi_enable_dtr(f_pdata, op, CQSPI_REG_OP_EXT_STIG_LSB,
			       f_pdata->dtr);
	अगर (ret)
		वापस ret;

	अगर (n_tx > CQSPI_STIG_DATA_LEN_MAX || (n_tx && !txbuf)) अणु
		dev_err(&cqspi->pdev->dev,
			"Invalid input argument, cmdlen %zu txbuf 0x%p\n",
			n_tx, txbuf);
		वापस -EINVAL;
	पूर्ण

	reg = cqspi_calc_rdreg(f_pdata);
	ग_लिखोl(reg, reg_base + CQSPI_REG_RD_INSTR);

	अगर (f_pdata->dtr)
		opcode = op->cmd.opcode >> 8;
	अन्यथा
		opcode = op->cmd.opcode;

	reg = opcode << CQSPI_REG_CMDCTRL_OPCODE_LSB;

	अगर (op->addr.nbytes) अणु
		reg |= (0x1 << CQSPI_REG_CMDCTRL_ADDR_EN_LSB);
		reg |= ((op->addr.nbytes - 1) &
			CQSPI_REG_CMDCTRL_ADD_BYTES_MASK)
			<< CQSPI_REG_CMDCTRL_ADD_BYTES_LSB;

		ग_लिखोl(op->addr.val, reg_base + CQSPI_REG_CMDADDRESS);
	पूर्ण

	अगर (n_tx) अणु
		reg |= (0x1 << CQSPI_REG_CMDCTRL_WR_EN_LSB);
		reg |= ((n_tx - 1) & CQSPI_REG_CMDCTRL_WR_BYTES_MASK)
			<< CQSPI_REG_CMDCTRL_WR_BYTES_LSB;
		data = 0;
		ग_लिखो_len = (n_tx > 4) ? 4 : n_tx;
		स_नकल(&data, txbuf, ग_लिखो_len);
		txbuf += ग_लिखो_len;
		ग_लिखोl(data, reg_base + CQSPI_REG_CMDWRITEDATALOWER);

		अगर (n_tx > 4) अणु
			data = 0;
			ग_लिखो_len = n_tx - 4;
			स_नकल(&data, txbuf, ग_लिखो_len);
			ग_लिखोl(data, reg_base + CQSPI_REG_CMDWRITEDATAUPPER);
		पूर्ण
	पूर्ण

	वापस cqspi_exec_flash_cmd(cqspi, reg);
पूर्ण

अटल पूर्णांक cqspi_पढ़ो_setup(काष्ठा cqspi_flash_pdata *f_pdata,
			    स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	व्योम __iomem *reg_base = cqspi->iobase;
	अचिन्हित पूर्णांक dummy_clk = 0;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	u8 opcode;

	ret = cqspi_enable_dtr(f_pdata, op, CQSPI_REG_OP_EXT_READ_LSB,
			       f_pdata->dtr);
	अगर (ret)
		वापस ret;

	अगर (f_pdata->dtr)
		opcode = op->cmd.opcode >> 8;
	अन्यथा
		opcode = op->cmd.opcode;

	reg = opcode << CQSPI_REG_RD_INSTR_OPCODE_LSB;
	reg |= cqspi_calc_rdreg(f_pdata);

	/* Setup dummy घड़ी cycles */
	dummy_clk = cqspi_calc_dummy(op, f_pdata->dtr);

	अगर (dummy_clk > CQSPI_DUMMY_CLKS_MAX)
		वापस -EOPNOTSUPP;

	अगर (dummy_clk)
		reg |= (dummy_clk & CQSPI_REG_RD_INSTR_DUMMY_MASK)
		       << CQSPI_REG_RD_INSTR_DUMMY_LSB;

	ग_लिखोl(reg, reg_base + CQSPI_REG_RD_INSTR);

	/* Set address width */
	reg = पढ़ोl(reg_base + CQSPI_REG_SIZE);
	reg &= ~CQSPI_REG_SIZE_ADDRESS_MASK;
	reg |= (op->addr.nbytes - 1);
	ग_लिखोl(reg, reg_base + CQSPI_REG_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक cqspi_indirect_पढ़ो_execute(काष्ठा cqspi_flash_pdata *f_pdata,
				       u8 *rxbuf, loff_t from_addr,
				       स्थिर माप_प्रकार n_rx)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	काष्ठा device *dev = &cqspi->pdev->dev;
	व्योम __iomem *reg_base = cqspi->iobase;
	व्योम __iomem *ahb_base = cqspi->ahb_base;
	अचिन्हित पूर्णांक reमुख्यing = n_rx;
	अचिन्हित पूर्णांक mod_bytes = n_rx % 4;
	अचिन्हित पूर्णांक bytes_to_पढ़ो = 0;
	u8 *rxbuf_end = rxbuf + n_rx;
	पूर्णांक ret = 0;

	ग_लिखोl(from_addr, reg_base + CQSPI_REG_INसूचीECTRDSTARTADDR);
	ग_लिखोl(reमुख्यing, reg_base + CQSPI_REG_INसूचीECTRDBYTES);

	/* Clear all पूर्णांकerrupts. */
	ग_लिखोl(CQSPI_IRQ_STATUS_MASK, reg_base + CQSPI_REG_IRQSTATUS);

	ग_लिखोl(CQSPI_IRQ_MASK_RD, reg_base + CQSPI_REG_IRQMASK);

	reinit_completion(&cqspi->transfer_complete);
	ग_लिखोl(CQSPI_REG_INसूचीECTRD_START_MASK,
	       reg_base + CQSPI_REG_INसूचीECTRD);

	जबतक (reमुख्यing > 0) अणु
		अगर (!रुको_क्रम_completion_समयout(&cqspi->transfer_complete,
						 msecs_to_jअगरfies(CQSPI_READ_TIMEOUT_MS)))
			ret = -ETIMEDOUT;

		bytes_to_पढ़ो = cqspi_get_rd_sram_level(cqspi);

		अगर (ret && bytes_to_पढ़ो == 0) अणु
			dev_err(dev, "Indirect read timeout, no bytes\n");
			जाओ failrd;
		पूर्ण

		जबतक (bytes_to_पढ़ो != 0) अणु
			अचिन्हित पूर्णांक word_reमुख्य = round_करोwn(reमुख्यing, 4);

			bytes_to_पढ़ो *= cqspi->fअगरo_width;
			bytes_to_पढ़ो = bytes_to_पढ़ो > reमुख्यing ?
					reमुख्यing : bytes_to_पढ़ो;
			bytes_to_पढ़ो = round_करोwn(bytes_to_पढ़ो, 4);
			/* Read 4 byte word chunks then single bytes */
			अगर (bytes_to_पढ़ो) अणु
				ioपढ़ो32_rep(ahb_base, rxbuf,
					     (bytes_to_पढ़ो / 4));
			पूर्ण अन्यथा अगर (!word_reमुख्य && mod_bytes) अणु
				अचिन्हित पूर्णांक temp = ioपढ़ो32(ahb_base);

				bytes_to_पढ़ो = mod_bytes;
				स_नकल(rxbuf, &temp, min((अचिन्हित पूर्णांक)
							 (rxbuf_end - rxbuf),
							 bytes_to_पढ़ो));
			पूर्ण
			rxbuf += bytes_to_पढ़ो;
			reमुख्यing -= bytes_to_पढ़ो;
			bytes_to_पढ़ो = cqspi_get_rd_sram_level(cqspi);
		पूर्ण

		अगर (reमुख्यing > 0)
			reinit_completion(&cqspi->transfer_complete);
	पूर्ण

	/* Check indirect करोne status */
	ret = cqspi_रुको_क्रम_bit(reg_base + CQSPI_REG_INसूचीECTRD,
				 CQSPI_REG_INसूचीECTRD_DONE_MASK, 0);
	अगर (ret) अणु
		dev_err(dev, "Indirect read completion error (%i)\n", ret);
		जाओ failrd;
	पूर्ण

	/* Disable पूर्णांकerrupt */
	ग_लिखोl(0, reg_base + CQSPI_REG_IRQMASK);

	/* Clear indirect completion status */
	ग_लिखोl(CQSPI_REG_INसूचीECTRD_DONE_MASK, reg_base + CQSPI_REG_INसूचीECTRD);

	वापस 0;

failrd:
	/* Disable पूर्णांकerrupt */
	ग_लिखोl(0, reg_base + CQSPI_REG_IRQMASK);

	/* Cancel the indirect पढ़ो */
	ग_लिखोl(CQSPI_REG_INसूचीECTWR_CANCEL_MASK,
	       reg_base + CQSPI_REG_INसूचीECTRD);
	वापस ret;
पूर्ण

अटल पूर्णांक cqspi_ग_लिखो_setup(काष्ठा cqspi_flash_pdata *f_pdata,
			     स्थिर काष्ठा spi_mem_op *op)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	व्योम __iomem *reg_base = cqspi->iobase;
	u8 opcode;

	ret = cqspi_enable_dtr(f_pdata, op, CQSPI_REG_OP_EXT_WRITE_LSB,
			       f_pdata->dtr);
	अगर (ret)
		वापस ret;

	अगर (f_pdata->dtr)
		opcode = op->cmd.opcode >> 8;
	अन्यथा
		opcode = op->cmd.opcode;

	/* Set opcode. */
	reg = opcode << CQSPI_REG_WR_INSTR_OPCODE_LSB;
	reg |= f_pdata->data_width << CQSPI_REG_WR_INSTR_TYPE_DATA_LSB;
	reg |= f_pdata->addr_width << CQSPI_REG_WR_INSTR_TYPE_ADDR_LSB;
	ग_लिखोl(reg, reg_base + CQSPI_REG_WR_INSTR);
	reg = cqspi_calc_rdreg(f_pdata);
	ग_लिखोl(reg, reg_base + CQSPI_REG_RD_INSTR);

	अगर (f_pdata->dtr) अणु
		/*
		 * Some flashes like the cypress Semper flash expect a 4-byte
		 * dummy address with the Read SR command in DTR mode, but this
		 * controller करोes not support sending address with the Read SR
		 * command. So, disable ग_लिखो completion polling on the
		 * controller's side. spi-nor will take care of polling the
		 * status रेजिस्टर.
		 */
		reg = पढ़ोl(reg_base + CQSPI_REG_WR_COMPLETION_CTRL);
		reg |= CQSPI_REG_WR_DISABLE_AUTO_POLL;
		ग_लिखोl(reg, reg_base + CQSPI_REG_WR_COMPLETION_CTRL);
	पूर्ण

	reg = पढ़ोl(reg_base + CQSPI_REG_SIZE);
	reg &= ~CQSPI_REG_SIZE_ADDRESS_MASK;
	reg |= (op->addr.nbytes - 1);
	ग_लिखोl(reg, reg_base + CQSPI_REG_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक cqspi_indirect_ग_लिखो_execute(काष्ठा cqspi_flash_pdata *f_pdata,
					loff_t to_addr, स्थिर u8 *txbuf,
					स्थिर माप_प्रकार n_tx)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	काष्ठा device *dev = &cqspi->pdev->dev;
	व्योम __iomem *reg_base = cqspi->iobase;
	अचिन्हित पूर्णांक reमुख्यing = n_tx;
	अचिन्हित पूर्णांक ग_लिखो_bytes;
	पूर्णांक ret;

	ग_लिखोl(to_addr, reg_base + CQSPI_REG_INसूचीECTWRSTARTADDR);
	ग_लिखोl(reमुख्यing, reg_base + CQSPI_REG_INसूचीECTWRBYTES);

	/* Clear all पूर्णांकerrupts. */
	ग_लिखोl(CQSPI_IRQ_STATUS_MASK, reg_base + CQSPI_REG_IRQSTATUS);

	ग_लिखोl(CQSPI_IRQ_MASK_WR, reg_base + CQSPI_REG_IRQMASK);

	reinit_completion(&cqspi->transfer_complete);
	ग_लिखोl(CQSPI_REG_INसूचीECTWR_START_MASK,
	       reg_base + CQSPI_REG_INसूचीECTWR);
	/*
	 * As per 66AK2G02 TRM SPRUHY8F section 11.15.5.3 Indirect Access
	 * Controller programming sequence, couple of cycles of
	 * QSPI_REF_CLK delay is required क्रम the above bit to
	 * be पूर्णांकernally synchronized by the QSPI module. Provide 5
	 * cycles of delay.
	 */
	अगर (cqspi->wr_delay)
		ndelay(cqspi->wr_delay);

	जबतक (reमुख्यing > 0) अणु
		माप_प्रकार ग_लिखो_words, mod_bytes;

		ग_लिखो_bytes = reमुख्यing;
		ग_लिखो_words = ग_लिखो_bytes / 4;
		mod_bytes = ग_लिखो_bytes % 4;
		/* Write 4 bytes at a समय then single bytes. */
		अगर (ग_लिखो_words) अणु
			ioग_लिखो32_rep(cqspi->ahb_base, txbuf, ग_लिखो_words);
			txbuf += (ग_लिखो_words * 4);
		पूर्ण
		अगर (mod_bytes) अणु
			अचिन्हित पूर्णांक temp = 0xFFFFFFFF;

			स_नकल(&temp, txbuf, mod_bytes);
			ioग_लिखो32(temp, cqspi->ahb_base);
			txbuf += mod_bytes;
		पूर्ण

		अगर (!रुको_क्रम_completion_समयout(&cqspi->transfer_complete,
						 msecs_to_jअगरfies(CQSPI_TIMEOUT_MS))) अणु
			dev_err(dev, "Indirect write timeout\n");
			ret = -ETIMEDOUT;
			जाओ failwr;
		पूर्ण

		reमुख्यing -= ग_लिखो_bytes;

		अगर (reमुख्यing > 0)
			reinit_completion(&cqspi->transfer_complete);
	पूर्ण

	/* Check indirect करोne status */
	ret = cqspi_रुको_क्रम_bit(reg_base + CQSPI_REG_INसूचीECTWR,
				 CQSPI_REG_INसूचीECTWR_DONE_MASK, 0);
	अगर (ret) अणु
		dev_err(dev, "Indirect write completion error (%i)\n", ret);
		जाओ failwr;
	पूर्ण

	/* Disable पूर्णांकerrupt. */
	ग_लिखोl(0, reg_base + CQSPI_REG_IRQMASK);

	/* Clear indirect completion status */
	ग_लिखोl(CQSPI_REG_INसूचीECTWR_DONE_MASK, reg_base + CQSPI_REG_INसूचीECTWR);

	cqspi_रुको_idle(cqspi);

	वापस 0;

failwr:
	/* Disable पूर्णांकerrupt. */
	ग_लिखोl(0, reg_base + CQSPI_REG_IRQMASK);

	/* Cancel the indirect ग_लिखो */
	ग_लिखोl(CQSPI_REG_INसूचीECTWR_CANCEL_MASK,
	       reg_base + CQSPI_REG_INसूचीECTWR);
	वापस ret;
पूर्ण

अटल व्योम cqspi_chipselect(काष्ठा cqspi_flash_pdata *f_pdata)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	व्योम __iomem *reg_base = cqspi->iobase;
	अचिन्हित पूर्णांक chip_select = f_pdata->cs;
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(reg_base + CQSPI_REG_CONFIG);
	अगर (cqspi->is_decoded_cs) अणु
		reg |= CQSPI_REG_CONFIG_DECODE_MASK;
	पूर्ण अन्यथा अणु
		reg &= ~CQSPI_REG_CONFIG_DECODE_MASK;

		/* Convert CS अगर without decoder.
		 * CS0 to 4b'1110
		 * CS1 to 4b'1101
		 * CS2 to 4b'1011
		 * CS3 to 4b'0111
		 */
		chip_select = 0xF & ~(1 << chip_select);
	पूर्ण

	reg &= ~(CQSPI_REG_CONFIG_CHIPSELECT_MASK
		 << CQSPI_REG_CONFIG_CHIPSELECT_LSB);
	reg |= (chip_select & CQSPI_REG_CONFIG_CHIPSELECT_MASK)
	    << CQSPI_REG_CONFIG_CHIPSELECT_LSB;
	ग_लिखोl(reg, reg_base + CQSPI_REG_CONFIG);
पूर्ण

अटल अचिन्हित पूर्णांक calculate_ticks_क्रम_ns(स्थिर अचिन्हित पूर्णांक ref_clk_hz,
					   स्थिर अचिन्हित पूर्णांक ns_val)
अणु
	अचिन्हित पूर्णांक ticks;

	ticks = ref_clk_hz / 1000;	/* kHz */
	ticks = DIV_ROUND_UP(ticks * ns_val, 1000000);

	वापस ticks;
पूर्ण

अटल व्योम cqspi_delay(काष्ठा cqspi_flash_pdata *f_pdata)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	व्योम __iomem *iobase = cqspi->iobase;
	स्थिर अचिन्हित पूर्णांक ref_clk_hz = cqspi->master_ref_clk_hz;
	अचिन्हित पूर्णांक tshsl, tchsh, tslch, tsd2d;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक tsclk;

	/* calculate the number of ref ticks क्रम one sclk tick */
	tsclk = DIV_ROUND_UP(ref_clk_hz, cqspi->sclk);

	tshsl = calculate_ticks_क्रम_ns(ref_clk_hz, f_pdata->tshsl_ns);
	/* this particular value must be at least one sclk */
	अगर (tshsl < tsclk)
		tshsl = tsclk;

	tchsh = calculate_ticks_क्रम_ns(ref_clk_hz, f_pdata->tchsh_ns);
	tslch = calculate_ticks_क्रम_ns(ref_clk_hz, f_pdata->tslch_ns);
	tsd2d = calculate_ticks_क्रम_ns(ref_clk_hz, f_pdata->tsd2d_ns);

	reg = (tshsl & CQSPI_REG_DELAY_TSHSL_MASK)
	       << CQSPI_REG_DELAY_TSHSL_LSB;
	reg |= (tchsh & CQSPI_REG_DELAY_TCHSH_MASK)
		<< CQSPI_REG_DELAY_TCHSH_LSB;
	reg |= (tslch & CQSPI_REG_DELAY_TSLCH_MASK)
		<< CQSPI_REG_DELAY_TSLCH_LSB;
	reg |= (tsd2d & CQSPI_REG_DELAY_TSD2D_MASK)
		<< CQSPI_REG_DELAY_TSD2D_LSB;
	ग_लिखोl(reg, iobase + CQSPI_REG_DELAY);
पूर्ण

अटल व्योम cqspi_config_baudrate_भाग(काष्ठा cqspi_st *cqspi)
अणु
	स्थिर अचिन्हित पूर्णांक ref_clk_hz = cqspi->master_ref_clk_hz;
	व्योम __iomem *reg_base = cqspi->iobase;
	u32 reg, भाग;

	/* Recalculate the baudrate भागisor based on QSPI specअगरication. */
	भाग = DIV_ROUND_UP(ref_clk_hz, 2 * cqspi->sclk) - 1;

	reg = पढ़ोl(reg_base + CQSPI_REG_CONFIG);
	reg &= ~(CQSPI_REG_CONFIG_BAUD_MASK << CQSPI_REG_CONFIG_BAUD_LSB);
	reg |= (भाग & CQSPI_REG_CONFIG_BAUD_MASK) << CQSPI_REG_CONFIG_BAUD_LSB;
	ग_लिखोl(reg, reg_base + CQSPI_REG_CONFIG);
पूर्ण

अटल व्योम cqspi_पढ़ोdata_capture(काष्ठा cqspi_st *cqspi,
				   स्थिर bool bypass,
				   स्थिर अचिन्हित पूर्णांक delay)
अणु
	व्योम __iomem *reg_base = cqspi->iobase;
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(reg_base + CQSPI_REG_READCAPTURE);

	अगर (bypass)
		reg |= (1 << CQSPI_REG_READCAPTURE_BYPASS_LSB);
	अन्यथा
		reg &= ~(1 << CQSPI_REG_READCAPTURE_BYPASS_LSB);

	reg &= ~(CQSPI_REG_READCAPTURE_DELAY_MASK
		 << CQSPI_REG_READCAPTURE_DELAY_LSB);

	reg |= (delay & CQSPI_REG_READCAPTURE_DELAY_MASK)
		<< CQSPI_REG_READCAPTURE_DELAY_LSB;

	ग_लिखोl(reg, reg_base + CQSPI_REG_READCAPTURE);
पूर्ण

अटल व्योम cqspi_controller_enable(काष्ठा cqspi_st *cqspi, bool enable)
अणु
	व्योम __iomem *reg_base = cqspi->iobase;
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(reg_base + CQSPI_REG_CONFIG);

	अगर (enable)
		reg |= CQSPI_REG_CONFIG_ENABLE_MASK;
	अन्यथा
		reg &= ~CQSPI_REG_CONFIG_ENABLE_MASK;

	ग_लिखोl(reg, reg_base + CQSPI_REG_CONFIG);
पूर्ण

अटल व्योम cqspi_configure(काष्ठा cqspi_flash_pdata *f_pdata,
			    अचिन्हित दीर्घ sclk)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	पूर्णांक चयन_cs = (cqspi->current_cs != f_pdata->cs);
	पूर्णांक चयन_ck = (cqspi->sclk != sclk);

	अगर (चयन_cs || चयन_ck)
		cqspi_controller_enable(cqspi, 0);

	/* Switch chip select. */
	अगर (चयन_cs) अणु
		cqspi->current_cs = f_pdata->cs;
		cqspi_chipselect(f_pdata);
	पूर्ण

	/* Setup baudrate भागisor and delays */
	अगर (चयन_ck) अणु
		cqspi->sclk = sclk;
		cqspi_config_baudrate_भाग(cqspi);
		cqspi_delay(f_pdata);
		cqspi_पढ़ोdata_capture(cqspi, !cqspi->rclk_en,
				       f_pdata->पढ़ो_delay);
	पूर्ण

	अगर (चयन_cs || चयन_ck)
		cqspi_controller_enable(cqspi, 1);
पूर्ण

अटल sमाप_प्रकार cqspi_ग_लिखो(काष्ठा cqspi_flash_pdata *f_pdata,
			   स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	loff_t to = op->addr.val;
	माप_प्रकार len = op->data.nbytes;
	स्थिर u_अक्षर *buf = op->data.buf.out;
	पूर्णांक ret;

	ret = cqspi_set_protocol(f_pdata, op);
	अगर (ret)
		वापस ret;

	ret = cqspi_ग_लिखो_setup(f_pdata, op);
	अगर (ret)
		वापस ret;

	/*
	 * Some flashes like the Cypress Semper flash expect a dummy 4-byte
	 * address (all 0s) with the पढ़ो status रेजिस्टर command in DTR mode.
	 * But this controller करोes not support sending dummy address bytes to
	 * the flash when it is polling the ग_लिखो completion रेजिस्टर in DTR
	 * mode. So, we can not use direct mode when in DTR mode क्रम writing
	 * data.
	 */
	अगर (!f_pdata->dtr && cqspi->use_direct_mode &&
	    ((to + len) <= cqspi->ahb_size)) अणु
		स_नकल_toio(cqspi->ahb_base + to, buf, len);
		वापस cqspi_रुको_idle(cqspi);
	पूर्ण

	वापस cqspi_indirect_ग_लिखो_execute(f_pdata, to, buf, len);
पूर्ण

अटल व्योम cqspi_rx_dma_callback(व्योम *param)
अणु
	काष्ठा cqspi_st *cqspi = param;

	complete(&cqspi->rx_dma_complete);
पूर्ण

अटल पूर्णांक cqspi_direct_पढ़ो_execute(काष्ठा cqspi_flash_pdata *f_pdata,
				     u_अक्षर *buf, loff_t from, माप_प्रकार len)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	काष्ठा device *dev = &cqspi->pdev->dev;
	क्रमागत dma_ctrl_flags flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	dma_addr_t dma_src = (dma_addr_t)cqspi->mmap_phys_base + from;
	पूर्णांक ret = 0;
	काष्ठा dma_async_tx_descriptor *tx;
	dma_cookie_t cookie;
	dma_addr_t dma_dst;
	काष्ठा device *ddev;

	अगर (!cqspi->rx_chan || !virt_addr_valid(buf)) अणु
		स_नकल_fromio(buf, cqspi->ahb_base + from, len);
		वापस 0;
	पूर्ण

	ddev = cqspi->rx_chan->device->dev;
	dma_dst = dma_map_single(ddev, buf, len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ddev, dma_dst)) अणु
		dev_err(dev, "dma mapping failed\n");
		वापस -ENOMEM;
	पूर्ण
	tx = dmaengine_prep_dma_स_नकल(cqspi->rx_chan, dma_dst, dma_src,
				       len, flags);
	अगर (!tx) अणु
		dev_err(dev, "device_prep_dma_memcpy error\n");
		ret = -EIO;
		जाओ err_unmap;
	पूर्ण

	tx->callback = cqspi_rx_dma_callback;
	tx->callback_param = cqspi;
	cookie = tx->tx_submit(tx);
	reinit_completion(&cqspi->rx_dma_complete);

	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dev_err(dev, "dma_submit_error %d\n", cookie);
		ret = -EIO;
		जाओ err_unmap;
	पूर्ण

	dma_async_issue_pending(cqspi->rx_chan);
	अगर (!रुको_क्रम_completion_समयout(&cqspi->rx_dma_complete,
					 msecs_to_jअगरfies(max_t(माप_प्रकार, len, 500)))) अणु
		dmaengine_terminate_sync(cqspi->rx_chan);
		dev_err(dev, "DMA wait_for_completion_timeout\n");
		ret = -ETIMEDOUT;
		जाओ err_unmap;
	पूर्ण

err_unmap:
	dma_unmap_single(ddev, dma_dst, len, DMA_FROM_DEVICE);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार cqspi_पढ़ो(काष्ठा cqspi_flash_pdata *f_pdata,
			  स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा cqspi_st *cqspi = f_pdata->cqspi;
	loff_t from = op->addr.val;
	माप_प्रकार len = op->data.nbytes;
	u_अक्षर *buf = op->data.buf.in;
	पूर्णांक ret;

	ret = cqspi_set_protocol(f_pdata, op);
	अगर (ret)
		वापस ret;

	ret = cqspi_पढ़ो_setup(f_pdata, op);
	अगर (ret)
		वापस ret;

	अगर (cqspi->use_direct_mode && ((from + len) <= cqspi->ahb_size))
		वापस cqspi_direct_पढ़ो_execute(f_pdata, buf, from, len);

	वापस cqspi_indirect_पढ़ो_execute(f_pdata, buf, from, len);
पूर्ण

अटल पूर्णांक cqspi_mem_process(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा cqspi_st *cqspi = spi_master_get_devdata(mem->spi->master);
	काष्ठा cqspi_flash_pdata *f_pdata;

	f_pdata = &cqspi->f_pdata[mem->spi->chip_select];
	cqspi_configure(f_pdata, mem->spi->max_speed_hz);

	अगर (op->data.dir == SPI_MEM_DATA_IN && op->data.buf.in) अणु
		अगर (!op->addr.nbytes)
			वापस cqspi_command_पढ़ो(f_pdata, op);

		वापस cqspi_पढ़ो(f_pdata, op);
	पूर्ण

	अगर (!op->addr.nbytes || !op->data.buf.out)
		वापस cqspi_command_ग_लिखो(f_pdata, op);

	वापस cqspi_ग_लिखो(f_pdata, op);
पूर्ण

अटल पूर्णांक cqspi_exec_mem_op(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	पूर्णांक ret;

	ret = cqspi_mem_process(mem, op);
	अगर (ret)
		dev_err(&mem->spi->dev, "operation failed with %d\n", ret);

	वापस ret;
पूर्ण

अटल bool cqspi_supports_mem_op(काष्ठा spi_mem *mem,
				  स्थिर काष्ठा spi_mem_op *op)
अणु
	bool all_true, all_false;

	all_true = op->cmd.dtr && op->addr.dtr && op->dummy.dtr &&
		   op->data.dtr;
	all_false = !op->cmd.dtr && !op->addr.dtr && !op->dummy.dtr &&
		    !op->data.dtr;

	/* Mixed DTR modes not supported. */
	अगर (!(all_true || all_false))
		वापस false;

	अगर (all_true)
		वापस spi_mem_dtr_supports_op(mem, op);
	अन्यथा
		वापस spi_mem_शेष_supports_op(mem, op);
पूर्ण

अटल पूर्णांक cqspi_of_get_flash_pdata(काष्ठा platक्रमm_device *pdev,
				    काष्ठा cqspi_flash_pdata *f_pdata,
				    काष्ठा device_node *np)
अणु
	अगर (of_property_पढ़ो_u32(np, "cdns,read-delay", &f_pdata->पढ़ो_delay)) अणु
		dev_err(&pdev->dev, "couldn't determine read-delay\n");
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cdns,tshsl-ns", &f_pdata->tshsl_ns)) अणु
		dev_err(&pdev->dev, "couldn't determine tshsl-ns\n");
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cdns,tsd2d-ns", &f_pdata->tsd2d_ns)) अणु
		dev_err(&pdev->dev, "couldn't determine tsd2d-ns\n");
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cdns,tchsh-ns", &f_pdata->tchsh_ns)) अणु
		dev_err(&pdev->dev, "couldn't determine tchsh-ns\n");
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cdns,tslch-ns", &f_pdata->tslch_ns)) अणु
		dev_err(&pdev->dev, "couldn't determine tslch-ns\n");
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "spi-max-frequency", &f_pdata->clk_rate)) अणु
		dev_err(&pdev->dev, "couldn't determine spi-max-frequency\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cqspi_of_get_pdata(काष्ठा cqspi_st *cqspi)
अणु
	काष्ठा device *dev = &cqspi->pdev->dev;
	काष्ठा device_node *np = dev->of_node;

	cqspi->is_decoded_cs = of_property_पढ़ो_bool(np, "cdns,is-decoded-cs");

	अगर (of_property_पढ़ो_u32(np, "cdns,fifo-depth", &cqspi->fअगरo_depth)) अणु
		dev_err(dev, "couldn't determine fifo-depth\n");
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cdns,fifo-width", &cqspi->fअगरo_width)) अणु
		dev_err(dev, "couldn't determine fifo-width\n");
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cdns,trigger-address",
				 &cqspi->trigger_address)) अणु
		dev_err(dev, "couldn't determine trigger-address\n");
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "num-cs", &cqspi->num_chipselect))
		cqspi->num_chipselect = CQSPI_MAX_CHIPSELECT;

	cqspi->rclk_en = of_property_पढ़ो_bool(np, "cdns,rclk-en");

	वापस 0;
पूर्ण

अटल व्योम cqspi_controller_init(काष्ठा cqspi_st *cqspi)
अणु
	u32 reg;

	cqspi_controller_enable(cqspi, 0);

	/* Configure the remap address रेजिस्टर, no remap */
	ग_लिखोl(0, cqspi->iobase + CQSPI_REG_REMAP);

	/* Disable all पूर्णांकerrupts. */
	ग_लिखोl(0, cqspi->iobase + CQSPI_REG_IRQMASK);

	/* Configure the SRAM split to 1:1 . */
	ग_लिखोl(cqspi->fअगरo_depth / 2, cqspi->iobase + CQSPI_REG_SRAMPARTITION);

	/* Load indirect trigger address. */
	ग_लिखोl(cqspi->trigger_address,
	       cqspi->iobase + CQSPI_REG_INसूचीECTTRIGGER);

	/* Program पढ़ो watermark -- 1/2 of the FIFO. */
	ग_लिखोl(cqspi->fअगरo_depth * cqspi->fअगरo_width / 2,
	       cqspi->iobase + CQSPI_REG_INसूचीECTRDWATERMARK);
	/* Program ग_लिखो watermark -- 1/8 of the FIFO. */
	ग_लिखोl(cqspi->fअगरo_depth * cqspi->fअगरo_width / 8,
	       cqspi->iobase + CQSPI_REG_INसूचीECTWRWATERMARK);

	/* Disable direct access controller */
	अगर (!cqspi->use_direct_mode) अणु
		reg = पढ़ोl(cqspi->iobase + CQSPI_REG_CONFIG);
		reg &= ~CQSPI_REG_CONFIG_ENB_सूची_ACC_CTRL;
		ग_लिखोl(reg, cqspi->iobase + CQSPI_REG_CONFIG);
	पूर्ण

	cqspi_controller_enable(cqspi, 1);
पूर्ण

अटल पूर्णांक cqspi_request_mmap_dma(काष्ठा cqspi_st *cqspi)
अणु
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	cqspi->rx_chan = dma_request_chan_by_mask(&mask);
	अगर (IS_ERR(cqspi->rx_chan)) अणु
		पूर्णांक ret = PTR_ERR(cqspi->rx_chan);
		cqspi->rx_chan = शून्य;
		वापस dev_err_probe(&cqspi->pdev->dev, ret, "No Rx DMA available\n");
	पूर्ण
	init_completion(&cqspi->rx_dma_complete);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *cqspi_get_name(काष्ठा spi_mem *mem)
अणु
	काष्ठा cqspi_st *cqspi = spi_master_get_devdata(mem->spi->master);
	काष्ठा device *dev = &cqspi->pdev->dev;

	वापस devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s.%d", dev_name(dev), mem->spi->chip_select);
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops cqspi_mem_ops = अणु
	.exec_op = cqspi_exec_mem_op,
	.get_name = cqspi_get_name,
	.supports_op = cqspi_supports_mem_op,
पूर्ण;

अटल पूर्णांक cqspi_setup_flash(काष्ठा cqspi_st *cqspi)
अणु
	काष्ठा platक्रमm_device *pdev = cqspi->pdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा cqspi_flash_pdata *f_pdata;
	अचिन्हित पूर्णांक cs;
	पूर्णांक ret;

	/* Get flash device data */
	क्रम_each_available_child_of_node(dev->of_node, np) अणु
		ret = of_property_पढ़ो_u32(np, "reg", &cs);
		अगर (ret) अणु
			dev_err(dev, "Couldn't determine chip select.\n");
			of_node_put(np);
			वापस ret;
		पूर्ण

		अगर (cs >= CQSPI_MAX_CHIPSELECT) अणु
			dev_err(dev, "Chip select %d out of range.\n", cs);
			of_node_put(np);
			वापस -EINVAL;
		पूर्ण

		f_pdata = &cqspi->f_pdata[cs];
		f_pdata->cqspi = cqspi;
		f_pdata->cs = cs;

		ret = cqspi_of_get_flash_pdata(pdev, f_pdata, np);
		अगर (ret) अणु
			of_node_put(np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cqspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा cqspi_driver_platdata *ddata;
	काष्ठा reset_control *rstc, *rstc_ocp;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spi_master *master;
	काष्ठा resource *res_ahb;
	काष्ठा cqspi_st *cqspi;
	काष्ठा resource *res;
	पूर्णांक ret;
	पूर्णांक irq;

	master = spi_alloc_master(&pdev->dev, माप(*cqspi));
	अगर (!master) अणु
		dev_err(&pdev->dev, "spi_alloc_master failed\n");
		वापस -ENOMEM;
	पूर्ण
	master->mode_bits = SPI_RX_QUAD | SPI_RX_DUAL;
	master->mem_ops = &cqspi_mem_ops;
	master->dev.of_node = pdev->dev.of_node;

	cqspi = spi_master_get_devdata(master);

	cqspi->pdev = pdev;
	platक्रमm_set_drvdata(pdev, cqspi);

	/* Obtain configuration from OF. */
	ret = cqspi_of_get_pdata(cqspi);
	अगर (ret) अणु
		dev_err(dev, "Cannot get mandatory OF data.\n");
		ret = -ENODEV;
		जाओ probe_master_put;
	पूर्ण

	/* Obtain QSPI घड़ी. */
	cqspi->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(cqspi->clk)) अणु
		dev_err(dev, "Cannot claim QSPI clock.\n");
		ret = PTR_ERR(cqspi->clk);
		जाओ probe_master_put;
	पूर्ण

	/* Obtain and remap controller address. */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	cqspi->iobase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(cqspi->iobase)) अणु
		dev_err(dev, "Cannot remap controller address.\n");
		ret = PTR_ERR(cqspi->iobase);
		जाओ probe_master_put;
	पूर्ण

	/* Obtain and remap AHB address. */
	res_ahb = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	cqspi->ahb_base = devm_ioremap_resource(dev, res_ahb);
	अगर (IS_ERR(cqspi->ahb_base)) अणु
		dev_err(dev, "Cannot remap AHB address.\n");
		ret = PTR_ERR(cqspi->ahb_base);
		जाओ probe_master_put;
	पूर्ण
	cqspi->mmap_phys_base = (dma_addr_t)res_ahb->start;
	cqspi->ahb_size = resource_size(res_ahb);

	init_completion(&cqspi->transfer_complete);

	/* Obtain IRQ line. */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = -ENXIO;
		जाओ probe_master_put;
	पूर्ण

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		जाओ probe_master_put;
	पूर्ण

	ret = clk_prepare_enable(cqspi->clk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable QSPI clock.\n");
		जाओ probe_clk_failed;
	पूर्ण

	/* Obtain QSPI reset control */
	rstc = devm_reset_control_get_optional_exclusive(dev, "qspi");
	अगर (IS_ERR(rstc)) अणु
		ret = PTR_ERR(rstc);
		dev_err(dev, "Cannot get QSPI reset.\n");
		जाओ probe_reset_failed;
	पूर्ण

	rstc_ocp = devm_reset_control_get_optional_exclusive(dev, "qspi-ocp");
	अगर (IS_ERR(rstc_ocp)) अणु
		ret = PTR_ERR(rstc_ocp);
		dev_err(dev, "Cannot get QSPI OCP reset.\n");
		जाओ probe_reset_failed;
	पूर्ण

	reset_control_निश्चित(rstc);
	reset_control_deनिश्चित(rstc);

	reset_control_निश्चित(rstc_ocp);
	reset_control_deनिश्चित(rstc_ocp);

	cqspi->master_ref_clk_hz = clk_get_rate(cqspi->clk);
	master->max_speed_hz = cqspi->master_ref_clk_hz;
	ddata  = of_device_get_match_data(dev);
	अगर (ddata) अणु
		अगर (ddata->quirks & CQSPI_NEEDS_WR_DELAY)
			cqspi->wr_delay = 50 * DIV_ROUND_UP(NSEC_PER_SEC,
						cqspi->master_ref_clk_hz);
		अगर (ddata->hwcaps_mask & CQSPI_SUPPORTS_OCTAL)
			master->mode_bits |= SPI_RX_OCTAL | SPI_TX_OCTAL;
		अगर (!(ddata->quirks & CQSPI_DISABLE_DAC_MODE))
			cqspi->use_direct_mode = true;
	पूर्ण

	ret = devm_request_irq(dev, irq, cqspi_irq_handler, 0,
			       pdev->name, cqspi);
	अगर (ret) अणु
		dev_err(dev, "Cannot request IRQ.\n");
		जाओ probe_reset_failed;
	पूर्ण

	cqspi_रुको_idle(cqspi);
	cqspi_controller_init(cqspi);
	cqspi->current_cs = -1;
	cqspi->sclk = 0;

	master->num_chipselect = cqspi->num_chipselect;

	ret = cqspi_setup_flash(cqspi);
	अगर (ret) अणु
		dev_err(dev, "failed to setup flash parameters %d\n", ret);
		जाओ probe_setup_failed;
	पूर्ण

	अगर (cqspi->use_direct_mode) अणु
		ret = cqspi_request_mmap_dma(cqspi);
		अगर (ret == -EPROBE_DEFER)
			जाओ probe_setup_failed;
	पूर्ण

	ret = devm_spi_रेजिस्टर_master(dev, master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register SPI ctlr %d\n", ret);
		जाओ probe_setup_failed;
	पूर्ण

	वापस 0;
probe_setup_failed:
	cqspi_controller_enable(cqspi, 0);
probe_reset_failed:
	clk_disable_unprepare(cqspi->clk);
probe_clk_failed:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
probe_master_put:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक cqspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cqspi_st *cqspi = platक्रमm_get_drvdata(pdev);

	cqspi_controller_enable(cqspi, 0);

	अगर (cqspi->rx_chan)
		dma_release_channel(cqspi->rx_chan);

	clk_disable_unprepare(cqspi->clk);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cqspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा cqspi_st *cqspi = dev_get_drvdata(dev);

	cqspi_controller_enable(cqspi, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cqspi_resume(काष्ठा device *dev)
अणु
	काष्ठा cqspi_st *cqspi = dev_get_drvdata(dev);

	cqspi_controller_enable(cqspi, 1);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cqspi__dev_pm_ops = अणु
	.suspend = cqspi_suspend,
	.resume = cqspi_resume,
पूर्ण;

#घोषणा CQSPI_DEV_PM_OPS	(&cqspi__dev_pm_ops)
#अन्यथा
#घोषणा CQSPI_DEV_PM_OPS	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा cqspi_driver_platdata cdns_qspi = अणु
	.quirks = CQSPI_DISABLE_DAC_MODE,
पूर्ण;

अटल स्थिर काष्ठा cqspi_driver_platdata k2g_qspi = अणु
	.quirks = CQSPI_NEEDS_WR_DELAY,
पूर्ण;

अटल स्थिर काष्ठा cqspi_driver_platdata am654_ospi = अणु
	.hwcaps_mask = CQSPI_SUPPORTS_OCTAL,
	.quirks = CQSPI_NEEDS_WR_DELAY,
पूर्ण;

अटल स्थिर काष्ठा cqspi_driver_platdata पूर्णांकel_lgm_qspi = अणु
	.quirks = CQSPI_DISABLE_DAC_MODE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cqspi_dt_ids[] = अणु
	अणु
		.compatible = "cdns,qspi-nor",
		.data = &cdns_qspi,
	पूर्ण,
	अणु
		.compatible = "ti,k2g-qspi",
		.data = &k2g_qspi,
	पूर्ण,
	अणु
		.compatible = "ti,am654-ospi",
		.data = &am654_ospi,
	पूर्ण,
	अणु
		.compatible = "intel,lgm-qspi",
		.data = &पूर्णांकel_lgm_qspi,
	पूर्ण,
	अणु /* end of table */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, cqspi_dt_ids);

अटल काष्ठा platक्रमm_driver cqspi_platक्रमm_driver = अणु
	.probe = cqspi_probe,
	.हटाओ = cqspi_हटाओ,
	.driver = अणु
		.name = CQSPI_NAME,
		.pm = CQSPI_DEV_PM_OPS,
		.of_match_table = cqspi_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cqspi_platक्रमm_driver);

MODULE_DESCRIPTION("Cadence QSPI Controller Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" CQSPI_NAME);
MODULE_AUTHOR("Ley Foon Tan <lftan@altera.com>");
MODULE_AUTHOR("Graham Moore <grmoore@opensource.altera.com>");
MODULE_AUTHOR("Vadivel Murugan R <vadivel.muruganx.ramuthevar@intel.com>");
MODULE_AUTHOR("Vignesh Raghavendra <vigneshr@ti.com>");
MODULE_AUTHOR("Pratyush Yadav <p.yadav@ti.com>");
