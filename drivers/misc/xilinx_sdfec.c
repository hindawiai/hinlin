<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx SDFEC
 *
 * Copyright (C) 2019 Xilinx, Inc.
 *
 * Description:
 * This driver is developed क्रम SDFEC16 (Soft Decision FEC 16nm)
 * IP. It exposes a अक्षर device which supports file operations
 * like  खोलो(), बंद() and ioctl().
 */

#समावेश <linux/miscdevice.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/compat.h>
#समावेश <linux/highस्मृति.स>

#समावेश <uapi/misc/xilinx_sdfec.h>

#घोषणा DEV_NAME_LEN 12

अटल DEFINE_IDA(dev_nrs);

/* Xilinx SDFEC Register Map */
/* CODE_WRI_PROTECT Register */
#घोषणा XSDFEC_CODE_WR_PROTECT_ADDR (0x4)

/* ACTIVE Register */
#घोषणा XSDFEC_ACTIVE_ADDR (0x8)
#घोषणा XSDFEC_IS_ACTIVITY_SET (0x1)

/* AXIS_WIDTH Register */
#घोषणा XSDFEC_AXIS_WIDTH_ADDR (0xC)
#घोषणा XSDFEC_AXIS_DOUT_WORDS_LSB (5)
#घोषणा XSDFEC_AXIS_DOUT_WIDTH_LSB (3)
#घोषणा XSDFEC_AXIS_DIN_WORDS_LSB (2)
#घोषणा XSDFEC_AXIS_DIN_WIDTH_LSB (0)

/* AXIS_ENABLE Register */
#घोषणा XSDFEC_AXIS_ENABLE_ADDR (0x10)
#घोषणा XSDFEC_AXIS_OUT_ENABLE_MASK (0x38)
#घोषणा XSDFEC_AXIS_IN_ENABLE_MASK (0x7)
#घोषणा XSDFEC_AXIS_ENABLE_MASK                                                \
	(XSDFEC_AXIS_OUT_ENABLE_MASK | XSDFEC_AXIS_IN_ENABLE_MASK)

/* FEC_CODE Register */
#घोषणा XSDFEC_FEC_CODE_ADDR (0x14)

/* ORDER Register Map */
#घोषणा XSDFEC_ORDER_ADDR (0x18)

/* Interrupt Status Register */
#घोषणा XSDFEC_ISR_ADDR (0x1C)
/* Interrupt Status Register Bit Mask */
#घोषणा XSDFEC_ISR_MASK (0x3F)

/* Write Only - Interrupt Enable Register */
#घोषणा XSDFEC_IER_ADDR (0x20)
/* Write Only - Interrupt Disable Register */
#घोषणा XSDFEC_IDR_ADDR (0x24)
/* Read Only - Interrupt Mask Register */
#घोषणा XSDFEC_IMR_ADDR (0x28)

/* ECC Interrupt Status Register */
#घोषणा XSDFEC_ECC_ISR_ADDR (0x2C)
/* Single Bit Errors */
#घोषणा XSDFEC_ECC_ISR_SBE_MASK (0x7FF)
/* PL Initialize Single Bit Errors */
#घोषणा XSDFEC_PL_INIT_ECC_ISR_SBE_MASK (0x3C00000)
/* Multi Bit Errors */
#घोषणा XSDFEC_ECC_ISR_MBE_MASK (0x3FF800)
/* PL Initialize Multi Bit Errors */
#घोषणा XSDFEC_PL_INIT_ECC_ISR_MBE_MASK (0x3C000000)
/* Multi Bit Error to Event Shअगरt */
#घोषणा XSDFEC_ECC_ISR_MBE_TO_EVENT_SHIFT (11)
/* PL Initialize Multi Bit Error to Event Shअगरt */
#घोषणा XSDFEC_PL_INIT_ECC_ISR_MBE_TO_EVENT_SHIFT (4)
/* ECC Interrupt Status Bit Mask */
#घोषणा XSDFEC_ECC_ISR_MASK (XSDFEC_ECC_ISR_SBE_MASK | XSDFEC_ECC_ISR_MBE_MASK)
/* ECC Interrupt Status PL Initialize Bit Mask */
#घोषणा XSDFEC_PL_INIT_ECC_ISR_MASK                                            \
	(XSDFEC_PL_INIT_ECC_ISR_SBE_MASK | XSDFEC_PL_INIT_ECC_ISR_MBE_MASK)
/* ECC Interrupt Status All Bit Mask */
#घोषणा XSDFEC_ALL_ECC_ISR_MASK                                                \
	(XSDFEC_ECC_ISR_MASK | XSDFEC_PL_INIT_ECC_ISR_MASK)
/* ECC Interrupt Status Single Bit Errors Mask */
#घोषणा XSDFEC_ALL_ECC_ISR_SBE_MASK                                            \
	(XSDFEC_ECC_ISR_SBE_MASK | XSDFEC_PL_INIT_ECC_ISR_SBE_MASK)
/* ECC Interrupt Status Multi Bit Errors Mask */
#घोषणा XSDFEC_ALL_ECC_ISR_MBE_MASK                                            \
	(XSDFEC_ECC_ISR_MBE_MASK | XSDFEC_PL_INIT_ECC_ISR_MBE_MASK)

/* Write Only - ECC Interrupt Enable Register */
#घोषणा XSDFEC_ECC_IER_ADDR (0x30)
/* Write Only - ECC Interrupt Disable Register */
#घोषणा XSDFEC_ECC_IDR_ADDR (0x34)
/* Read Only - ECC Interrupt Mask Register */
#घोषणा XSDFEC_ECC_IMR_ADDR (0x38)

/* BYPASS Register */
#घोषणा XSDFEC_BYPASS_ADDR (0x3C)

/* Turbo Code Register */
#घोषणा XSDFEC_TURBO_ADDR (0x100)
#घोषणा XSDFEC_TURBO_SCALE_MASK (0xFFF)
#घोषणा XSDFEC_TURBO_SCALE_BIT_POS (8)
#घोषणा XSDFEC_TURBO_SCALE_MAX (15)

/* REG0 Register */
#घोषणा XSDFEC_LDPC_CODE_REG0_ADDR_BASE (0x2000)
#घोषणा XSDFEC_LDPC_CODE_REG0_ADDR_HIGH (0x27F0)
#घोषणा XSDFEC_REG0_N_MIN (4)
#घोषणा XSDFEC_REG0_N_MAX (32768)
#घोषणा XSDFEC_REG0_N_MUL_P (256)
#घोषणा XSDFEC_REG0_N_LSB (0)
#घोषणा XSDFEC_REG0_K_MIN (2)
#घोषणा XSDFEC_REG0_K_MAX (32766)
#घोषणा XSDFEC_REG0_K_MUL_P (256)
#घोषणा XSDFEC_REG0_K_LSB (16)

/* REG1 Register */
#घोषणा XSDFEC_LDPC_CODE_REG1_ADDR_BASE (0x2004)
#घोषणा XSDFEC_LDPC_CODE_REG1_ADDR_HIGH (0x27f4)
#घोषणा XSDFEC_REG1_PSIZE_MIN (2)
#घोषणा XSDFEC_REG1_PSIZE_MAX (512)
#घोषणा XSDFEC_REG1_NO_PACKING_MASK (0x400)
#घोषणा XSDFEC_REG1_NO_PACKING_LSB (10)
#घोषणा XSDFEC_REG1_NM_MASK (0xFF800)
#घोषणा XSDFEC_REG1_NM_LSB (11)
#घोषणा XSDFEC_REG1_BYPASS_MASK (0x100000)

/* REG2 Register */
#घोषणा XSDFEC_LDPC_CODE_REG2_ADDR_BASE (0x2008)
#घोषणा XSDFEC_LDPC_CODE_REG2_ADDR_HIGH (0x27f8)
#घोषणा XSDFEC_REG2_NLAYERS_MIN (1)
#घोषणा XSDFEC_REG2_NLAYERS_MAX (256)
#घोषणा XSDFEC_REG2_NNMQC_MASK (0xFFE00)
#घोषणा XSDFEC_REG2_NMQC_LSB (9)
#घोषणा XSDFEC_REG2_NORM_TYPE_MASK (0x100000)
#घोषणा XSDFEC_REG2_NORM_TYPE_LSB (20)
#घोषणा XSDFEC_REG2_SPECIAL_QC_MASK (0x200000)
#घोषणा XSDFEC_REG2_SPEICAL_QC_LSB (21)
#घोषणा XSDFEC_REG2_NO_FINAL_PARITY_MASK (0x400000)
#घोषणा XSDFEC_REG2_NO_FINAL_PARITY_LSB (22)
#घोषणा XSDFEC_REG2_MAX_SCHEDULE_MASK (0x1800000)
#घोषणा XSDFEC_REG2_MAX_SCHEDULE_LSB (23)

/* REG3 Register */
#घोषणा XSDFEC_LDPC_CODE_REG3_ADDR_BASE (0x200C)
#घोषणा XSDFEC_LDPC_CODE_REG3_ADDR_HIGH (0x27FC)
#घोषणा XSDFEC_REG3_LA_OFF_LSB (8)
#घोषणा XSDFEC_REG3_QC_OFF_LSB (16)

#घोषणा XSDFEC_LDPC_REG_JUMP (0x10)
#घोषणा XSDFEC_REG_WIDTH_JUMP (4)

/* The maximum number of pinned pages */
#घोषणा MAX_NUM_PAGES ((XSDFEC_QC_TABLE_DEPTH / PAGE_SIZE) + 1)

/**
 * काष्ठा xsdfec_clks - For managing SD-FEC घड़ीs
 * @core_clk: Main processing घड़ी क्रम core
 * @axi_clk: AXI4-Lite memory-mapped घड़ी
 * @din_words_clk: DIN Words AXI4-Stream Slave घड़ी
 * @din_clk: DIN AXI4-Stream Slave घड़ी
 * @करोut_clk: DOUT Words AXI4-Stream Slave घड़ी
 * @करोut_words_clk: DOUT AXI4-Stream Slave घड़ी
 * @ctrl_clk: Control AXI4-Stream Slave घड़ी
 * @status_clk: Status AXI4-Stream Slave घड़ी
 */
काष्ठा xsdfec_clks अणु
	काष्ठा clk *core_clk;
	काष्ठा clk *axi_clk;
	काष्ठा clk *din_words_clk;
	काष्ठा clk *din_clk;
	काष्ठा clk *करोut_clk;
	काष्ठा clk *करोut_words_clk;
	काष्ठा clk *ctrl_clk;
	काष्ठा clk *status_clk;
पूर्ण;

/**
 * काष्ठा xsdfec_dev - Driver data क्रम SDFEC
 * @miscdev: Misc device handle
 * @clks: Clocks managed by the SDFEC driver
 * @रुकोq: Driver रुको queue
 * @config: Configuration of the SDFEC device
 * @dev_name: Device name
 * @flags: spinlock flags
 * @regs: device physical base address
 * @dev: poपूर्णांकer to device काष्ठा
 * @state: State of the SDFEC device
 * @error_data_lock: Error counter and states spinlock
 * @dev_id: Device ID
 * @isr_err_count: Count of ISR errors
 * @cecc_count: Count of Correctable ECC errors (SBE)
 * @uecc_count: Count of Uncorrectable ECC errors (MBE)
 * @irq: IRQ number
 * @state_updated: indicates State updated by पूर्णांकerrupt handler
 * @stats_updated: indicates Stats updated by पूर्णांकerrupt handler
 * @पूर्णांकr_enabled: indicates IRQ enabled
 *
 * This काष्ठाure contains necessary state क्रम SDFEC driver to operate
 */
काष्ठा xsdfec_dev अणु
	काष्ठा miscdevice miscdev;
	काष्ठा xsdfec_clks clks;
	रुको_queue_head_t रुकोq;
	काष्ठा xsdfec_config config;
	अक्षर dev_name[DEV_NAME_LEN];
	अचिन्हित दीर्घ flags;
	व्योम __iomem *regs;
	काष्ठा device *dev;
	क्रमागत xsdfec_state state;
	/* Spinlock to protect state_updated and stats_updated */
	spinlock_t error_data_lock;
	पूर्णांक dev_id;
	u32 isr_err_count;
	u32 cecc_count;
	u32 uecc_count;
	पूर्णांक irq;
	bool state_updated;
	bool stats_updated;
	bool पूर्णांकr_enabled;
पूर्ण;

अटल अंतरभूत व्योम xsdfec_regग_लिखो(काष्ठा xsdfec_dev *xsdfec, u32 addr,
				   u32 value)
अणु
	dev_dbg(xsdfec->dev, "Writing 0x%x to offset 0x%x", value, addr);
	ioग_लिखो32(value, xsdfec->regs + addr);
पूर्ण

अटल अंतरभूत u32 xsdfec_regपढ़ो(काष्ठा xsdfec_dev *xsdfec, u32 addr)
अणु
	u32 rval;

	rval = ioपढ़ो32(xsdfec->regs + addr);
	dev_dbg(xsdfec->dev, "Read value = 0x%x from offset 0x%x", rval, addr);
	वापस rval;
पूर्ण

अटल व्योम update_bool_config_from_reg(काष्ठा xsdfec_dev *xsdfec,
					u32 reg_offset, u32 bit_num,
					अक्षर *config_value)
अणु
	u32 reg_val;
	u32 bit_mask = 1 << bit_num;

	reg_val = xsdfec_regपढ़ो(xsdfec, reg_offset);
	*config_value = (reg_val & bit_mask) > 0;
पूर्ण

अटल व्योम update_config_from_hw(काष्ठा xsdfec_dev *xsdfec)
अणु
	u32 reg_value;
	bool sdfec_started;

	/* Update the Order */
	reg_value = xsdfec_regपढ़ो(xsdfec, XSDFEC_ORDER_ADDR);
	xsdfec->config.order = reg_value;

	update_bool_config_from_reg(xsdfec, XSDFEC_BYPASS_ADDR,
				    0, /* Bit Number, maybe change to mask */
				    &xsdfec->config.bypass);

	update_bool_config_from_reg(xsdfec, XSDFEC_CODE_WR_PROTECT_ADDR,
				    0, /* Bit Number */
				    &xsdfec->config.code_wr_protect);

	reg_value = xsdfec_regपढ़ो(xsdfec, XSDFEC_IMR_ADDR);
	xsdfec->config.irq.enable_isr = (reg_value & XSDFEC_ISR_MASK) > 0;

	reg_value = xsdfec_regपढ़ो(xsdfec, XSDFEC_ECC_IMR_ADDR);
	xsdfec->config.irq.enable_ecc_isr =
		(reg_value & XSDFEC_ECC_ISR_MASK) > 0;

	reg_value = xsdfec_regपढ़ो(xsdfec, XSDFEC_AXIS_ENABLE_ADDR);
	sdfec_started = (reg_value & XSDFEC_AXIS_IN_ENABLE_MASK) > 0;
	अगर (sdfec_started)
		xsdfec->state = XSDFEC_STARTED;
	अन्यथा
		xsdfec->state = XSDFEC_STOPPED;
पूर्ण

अटल पूर्णांक xsdfec_get_status(काष्ठा xsdfec_dev *xsdfec, व्योम __user *arg)
अणु
	काष्ठा xsdfec_status status;
	पूर्णांक err;

	स_रखो(&status, 0, माप(status));
	spin_lock_irqsave(&xsdfec->error_data_lock, xsdfec->flags);
	status.state = xsdfec->state;
	xsdfec->state_updated = false;
	spin_unlock_irqrestore(&xsdfec->error_data_lock, xsdfec->flags);
	status.activity = (xsdfec_regपढ़ो(xsdfec, XSDFEC_ACTIVE_ADDR) &
			   XSDFEC_IS_ACTIVITY_SET);

	err = copy_to_user(arg, &status, माप(status));
	अगर (err)
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक xsdfec_get_config(काष्ठा xsdfec_dev *xsdfec, व्योम __user *arg)
अणु
	पूर्णांक err;

	err = copy_to_user(arg, &xsdfec->config, माप(xsdfec->config));
	अगर (err)
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक xsdfec_isr_enable(काष्ठा xsdfec_dev *xsdfec, bool enable)
अणु
	u32 mask_पढ़ो;

	अगर (enable) अणु
		/* Enable */
		xsdfec_regग_लिखो(xsdfec, XSDFEC_IER_ADDR, XSDFEC_ISR_MASK);
		mask_पढ़ो = xsdfec_regपढ़ो(xsdfec, XSDFEC_IMR_ADDR);
		अगर (mask_पढ़ो & XSDFEC_ISR_MASK) अणु
			dev_dbg(xsdfec->dev,
				"SDFEC enabling irq with IER failed");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Disable */
		xsdfec_regग_लिखो(xsdfec, XSDFEC_IDR_ADDR, XSDFEC_ISR_MASK);
		mask_पढ़ो = xsdfec_regपढ़ो(xsdfec, XSDFEC_IMR_ADDR);
		अगर ((mask_पढ़ो & XSDFEC_ISR_MASK) != XSDFEC_ISR_MASK) अणु
			dev_dbg(xsdfec->dev,
				"SDFEC disabling irq with IDR failed");
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_ecc_isr_enable(काष्ठा xsdfec_dev *xsdfec, bool enable)
अणु
	u32 mask_पढ़ो;

	अगर (enable) अणु
		/* Enable */
		xsdfec_regग_लिखो(xsdfec, XSDFEC_ECC_IER_ADDR,
				XSDFEC_ALL_ECC_ISR_MASK);
		mask_पढ़ो = xsdfec_regपढ़ो(xsdfec, XSDFEC_ECC_IMR_ADDR);
		अगर (mask_पढ़ो & XSDFEC_ALL_ECC_ISR_MASK) अणु
			dev_dbg(xsdfec->dev,
				"SDFEC enabling ECC irq with ECC IER failed");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Disable */
		xsdfec_regग_लिखो(xsdfec, XSDFEC_ECC_IDR_ADDR,
				XSDFEC_ALL_ECC_ISR_MASK);
		mask_पढ़ो = xsdfec_regपढ़ो(xsdfec, XSDFEC_ECC_IMR_ADDR);
		अगर (!(((mask_पढ़ो & XSDFEC_ALL_ECC_ISR_MASK) ==
		       XSDFEC_ECC_ISR_MASK) ||
		      ((mask_पढ़ो & XSDFEC_ALL_ECC_ISR_MASK) ==
		       XSDFEC_PL_INIT_ECC_ISR_MASK))) अणु
			dev_dbg(xsdfec->dev,
				"SDFEC disable ECC irq with ECC IDR failed");
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_set_irq(काष्ठा xsdfec_dev *xsdfec, व्योम __user *arg)
अणु
	काष्ठा xsdfec_irq irq;
	पूर्णांक err;
	पूर्णांक isr_err;
	पूर्णांक ecc_err;

	err = copy_from_user(&irq, arg, माप(irq));
	अगर (err)
		वापस -EFAULT;

	/* Setup tlast related IRQ */
	isr_err = xsdfec_isr_enable(xsdfec, irq.enable_isr);
	अगर (!isr_err)
		xsdfec->config.irq.enable_isr = irq.enable_isr;

	/* Setup ECC related IRQ */
	ecc_err = xsdfec_ecc_isr_enable(xsdfec, irq.enable_ecc_isr);
	अगर (!ecc_err)
		xsdfec->config.irq.enable_ecc_isr = irq.enable_ecc_isr;

	अगर (isr_err < 0 || ecc_err < 0)
		err = -EIO;

	वापस err;
पूर्ण

अटल पूर्णांक xsdfec_set_turbo(काष्ठा xsdfec_dev *xsdfec, व्योम __user *arg)
अणु
	काष्ठा xsdfec_turbo turbo;
	पूर्णांक err;
	u32 turbo_ग_लिखो;

	err = copy_from_user(&turbo, arg, माप(turbo));
	अगर (err)
		वापस -EFAULT;

	अगर (turbo.alg >= XSDFEC_TURBO_ALG_MAX)
		वापस -EINVAL;

	अगर (turbo.scale > XSDFEC_TURBO_SCALE_MAX)
		वापस -EINVAL;

	/* Check to see what device tree says about the FEC codes */
	अगर (xsdfec->config.code == XSDFEC_LDPC_CODE)
		वापस -EIO;

	turbo_ग_लिखो = ((turbo.scale & XSDFEC_TURBO_SCALE_MASK)
		       << XSDFEC_TURBO_SCALE_BIT_POS) |
		      turbo.alg;
	xsdfec_regग_लिखो(xsdfec, XSDFEC_TURBO_ADDR, turbo_ग_लिखो);
	वापस err;
पूर्ण

अटल पूर्णांक xsdfec_get_turbo(काष्ठा xsdfec_dev *xsdfec, व्योम __user *arg)
अणु
	u32 reg_value;
	काष्ठा xsdfec_turbo turbo_params;
	पूर्णांक err;

	अगर (xsdfec->config.code == XSDFEC_LDPC_CODE)
		वापस -EIO;

	स_रखो(&turbo_params, 0, माप(turbo_params));
	reg_value = xsdfec_regपढ़ो(xsdfec, XSDFEC_TURBO_ADDR);

	turbo_params.scale = (reg_value & XSDFEC_TURBO_SCALE_MASK) >>
			     XSDFEC_TURBO_SCALE_BIT_POS;
	turbo_params.alg = reg_value & 0x1;

	err = copy_to_user(arg, &turbo_params, माप(turbo_params));
	अगर (err)
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक xsdfec_reg0_ग_लिखो(काष्ठा xsdfec_dev *xsdfec, u32 n, u32 k, u32 psize,
			     u32 offset)
अणु
	u32 wdata;

	अगर (n < XSDFEC_REG0_N_MIN || n > XSDFEC_REG0_N_MAX || psize == 0 ||
	    (n > XSDFEC_REG0_N_MUL_P * psize) || n <= k || ((n % psize) != 0)) अणु
		dev_dbg(xsdfec->dev, "N value is not in range");
		वापस -EINVAL;
	पूर्ण
	n <<= XSDFEC_REG0_N_LSB;

	अगर (k < XSDFEC_REG0_K_MIN || k > XSDFEC_REG0_K_MAX ||
	    (k > XSDFEC_REG0_K_MUL_P * psize) || ((k % psize) != 0)) अणु
		dev_dbg(xsdfec->dev, "K value is not in range");
		वापस -EINVAL;
	पूर्ण
	k = k << XSDFEC_REG0_K_LSB;
	wdata = k | n;

	अगर (XSDFEC_LDPC_CODE_REG0_ADDR_BASE + (offset * XSDFEC_LDPC_REG_JUMP) >
	    XSDFEC_LDPC_CODE_REG0_ADDR_HIGH) अणु
		dev_dbg(xsdfec->dev, "Writing outside of LDPC reg0 space 0x%x",
			XSDFEC_LDPC_CODE_REG0_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP));
		वापस -EINVAL;
	पूर्ण
	xsdfec_regग_लिखो(xsdfec,
			XSDFEC_LDPC_CODE_REG0_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP),
			wdata);
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_reg1_ग_लिखो(काष्ठा xsdfec_dev *xsdfec, u32 psize,
			     u32 no_packing, u32 nm, u32 offset)
अणु
	u32 wdata;

	अगर (psize < XSDFEC_REG1_PSIZE_MIN || psize > XSDFEC_REG1_PSIZE_MAX) अणु
		dev_dbg(xsdfec->dev, "Psize is not in range");
		वापस -EINVAL;
	पूर्ण

	अगर (no_packing != 0 && no_packing != 1)
		dev_dbg(xsdfec->dev, "No-packing bit register invalid");
	no_packing = ((no_packing << XSDFEC_REG1_NO_PACKING_LSB) &
		      XSDFEC_REG1_NO_PACKING_MASK);

	अगर (nm & ~(XSDFEC_REG1_NM_MASK >> XSDFEC_REG1_NM_LSB))
		dev_dbg(xsdfec->dev, "NM is beyond 10 bits");
	nm = (nm << XSDFEC_REG1_NM_LSB) & XSDFEC_REG1_NM_MASK;

	wdata = nm | no_packing | psize;
	अगर (XSDFEC_LDPC_CODE_REG1_ADDR_BASE + (offset * XSDFEC_LDPC_REG_JUMP) >
	    XSDFEC_LDPC_CODE_REG1_ADDR_HIGH) अणु
		dev_dbg(xsdfec->dev, "Writing outside of LDPC reg1 space 0x%x",
			XSDFEC_LDPC_CODE_REG1_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP));
		वापस -EINVAL;
	पूर्ण
	xsdfec_regग_लिखो(xsdfec,
			XSDFEC_LDPC_CODE_REG1_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP),
			wdata);
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_reg2_ग_लिखो(काष्ठा xsdfec_dev *xsdfec, u32 nlayers, u32 nmqc,
			     u32 norm_type, u32 special_qc, u32 no_final_parity,
			     u32 max_schedule, u32 offset)
अणु
	u32 wdata;

	अगर (nlayers < XSDFEC_REG2_NLAYERS_MIN ||
	    nlayers > XSDFEC_REG2_NLAYERS_MAX) अणु
		dev_dbg(xsdfec->dev, "Nlayers is not in range");
		वापस -EINVAL;
	पूर्ण

	अगर (nmqc & ~(XSDFEC_REG2_NNMQC_MASK >> XSDFEC_REG2_NMQC_LSB))
		dev_dbg(xsdfec->dev, "NMQC exceeds 11 bits");
	nmqc = (nmqc << XSDFEC_REG2_NMQC_LSB) & XSDFEC_REG2_NNMQC_MASK;

	अगर (norm_type > 1)
		dev_dbg(xsdfec->dev, "Norm type is invalid");
	norm_type = ((norm_type << XSDFEC_REG2_NORM_TYPE_LSB) &
		     XSDFEC_REG2_NORM_TYPE_MASK);
	अगर (special_qc > 1)
		dev_dbg(xsdfec->dev, "Special QC in invalid");
	special_qc = ((special_qc << XSDFEC_REG2_SPEICAL_QC_LSB) &
		      XSDFEC_REG2_SPECIAL_QC_MASK);

	अगर (no_final_parity > 1)
		dev_dbg(xsdfec->dev, "No final parity check invalid");
	no_final_parity =
		((no_final_parity << XSDFEC_REG2_NO_FINAL_PARITY_LSB) &
		 XSDFEC_REG2_NO_FINAL_PARITY_MASK);
	अगर (max_schedule &
	    ~(XSDFEC_REG2_MAX_SCHEDULE_MASK >> XSDFEC_REG2_MAX_SCHEDULE_LSB))
		dev_dbg(xsdfec->dev, "Max Schedule exceeds 2 bits");
	max_schedule = ((max_schedule << XSDFEC_REG2_MAX_SCHEDULE_LSB) &
			XSDFEC_REG2_MAX_SCHEDULE_MASK);

	wdata = (max_schedule | no_final_parity | special_qc | norm_type |
		 nmqc | nlayers);

	अगर (XSDFEC_LDPC_CODE_REG2_ADDR_BASE + (offset * XSDFEC_LDPC_REG_JUMP) >
	    XSDFEC_LDPC_CODE_REG2_ADDR_HIGH) अणु
		dev_dbg(xsdfec->dev, "Writing outside of LDPC reg2 space 0x%x",
			XSDFEC_LDPC_CODE_REG2_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP));
		वापस -EINVAL;
	पूर्ण
	xsdfec_regग_लिखो(xsdfec,
			XSDFEC_LDPC_CODE_REG2_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP),
			wdata);
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_reg3_ग_लिखो(काष्ठा xsdfec_dev *xsdfec, u8 sc_off, u8 la_off,
			     u16 qc_off, u32 offset)
अणु
	u32 wdata;

	wdata = ((qc_off << XSDFEC_REG3_QC_OFF_LSB) |
		 (la_off << XSDFEC_REG3_LA_OFF_LSB) | sc_off);
	अगर (XSDFEC_LDPC_CODE_REG3_ADDR_BASE + (offset * XSDFEC_LDPC_REG_JUMP) >
	    XSDFEC_LDPC_CODE_REG3_ADDR_HIGH) अणु
		dev_dbg(xsdfec->dev, "Writing outside of LDPC reg3 space 0x%x",
			XSDFEC_LDPC_CODE_REG3_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP));
		वापस -EINVAL;
	पूर्ण
	xsdfec_regग_लिखो(xsdfec,
			XSDFEC_LDPC_CODE_REG3_ADDR_BASE +
				(offset * XSDFEC_LDPC_REG_JUMP),
			wdata);
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_table_ग_लिखो(काष्ठा xsdfec_dev *xsdfec, u32 offset,
			      u32 *src_ptr, u32 len, स्थिर u32 base_addr,
			      स्थिर u32 depth)
अणु
	u32 reg = 0;
	पूर्णांक res, i, nr_pages;
	u32 n;
	u32 *addr = शून्य;
	काष्ठा page *pages[MAX_NUM_PAGES];

	/*
	 * Writes that go beyond the length of
	 * Shared Scale(SC) table should fail
	 */
	अगर (offset > depth / XSDFEC_REG_WIDTH_JUMP ||
	    len > depth / XSDFEC_REG_WIDTH_JUMP ||
	    offset + len > depth / XSDFEC_REG_WIDTH_JUMP) अणु
		dev_dbg(xsdfec->dev, "Write exceeds SC table length");
		वापस -EINVAL;
	पूर्ण

	n = (len * XSDFEC_REG_WIDTH_JUMP) / PAGE_SIZE;
	अगर ((len * XSDFEC_REG_WIDTH_JUMP) % PAGE_SIZE)
		n += 1;

	अगर (WARN_ON_ONCE(n > पूर्णांक_उच्च))
		वापस -EINVAL;

	nr_pages = n;

	res = pin_user_pages_fast((अचिन्हित दीर्घ)src_ptr, nr_pages, 0, pages);
	अगर (res < nr_pages) अणु
		अगर (res > 0)
			unpin_user_pages(pages, res);

		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < nr_pages; i++) अणु
		addr = kmap(pages[i]);
		करो अणु
			xsdfec_regग_लिखो(xsdfec,
					base_addr + ((offset + reg) *
						     XSDFEC_REG_WIDTH_JUMP),
					addr[reg]);
			reg++;
		पूर्ण जबतक ((reg < len) &&
			 ((reg * XSDFEC_REG_WIDTH_JUMP) % PAGE_SIZE));
		unpin_user_page(pages[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_add_ldpc(काष्ठा xsdfec_dev *xsdfec, व्योम __user *arg)
अणु
	काष्ठा xsdfec_ldpc_params *ldpc;
	पूर्णांक ret, n;

	ldpc = memdup_user(arg, माप(*ldpc));
	अगर (IS_ERR(ldpc))
		वापस PTR_ERR(ldpc);

	अगर (xsdfec->config.code == XSDFEC_TURBO_CODE) अणु
		ret = -EIO;
		जाओ err_out;
	पूर्ण

	/* Verअगरy Device has not started */
	अगर (xsdfec->state == XSDFEC_STARTED) अणु
		ret = -EIO;
		जाओ err_out;
	पूर्ण

	अगर (xsdfec->config.code_wr_protect) अणु
		ret = -EIO;
		जाओ err_out;
	पूर्ण

	/* Write Reg 0 */
	ret = xsdfec_reg0_ग_लिखो(xsdfec, ldpc->n, ldpc->k, ldpc->psize,
				ldpc->code_id);
	अगर (ret)
		जाओ err_out;

	/* Write Reg 1 */
	ret = xsdfec_reg1_ग_लिखो(xsdfec, ldpc->psize, ldpc->no_packing, ldpc->nm,
				ldpc->code_id);
	अगर (ret)
		जाओ err_out;

	/* Write Reg 2 */
	ret = xsdfec_reg2_ग_लिखो(xsdfec, ldpc->nlayers, ldpc->nmqc,
				ldpc->norm_type, ldpc->special_qc,
				ldpc->no_final_parity, ldpc->max_schedule,
				ldpc->code_id);
	अगर (ret)
		जाओ err_out;

	/* Write Reg 3 */
	ret = xsdfec_reg3_ग_लिखो(xsdfec, ldpc->sc_off, ldpc->la_off,
				ldpc->qc_off, ldpc->code_id);
	अगर (ret)
		जाओ err_out;

	/* Write Shared Codes */
	n = ldpc->nlayers / 4;
	अगर (ldpc->nlayers % 4)
		n++;

	ret = xsdfec_table_ग_लिखो(xsdfec, ldpc->sc_off, ldpc->sc_table, n,
				 XSDFEC_LDPC_SC_TABLE_ADDR_BASE,
				 XSDFEC_SC_TABLE_DEPTH);
	अगर (ret < 0)
		जाओ err_out;

	ret = xsdfec_table_ग_लिखो(xsdfec, 4 * ldpc->la_off, ldpc->la_table,
				 ldpc->nlayers, XSDFEC_LDPC_LA_TABLE_ADDR_BASE,
				 XSDFEC_LA_TABLE_DEPTH);
	अगर (ret < 0)
		जाओ err_out;

	ret = xsdfec_table_ग_लिखो(xsdfec, 4 * ldpc->qc_off, ldpc->qc_table,
				 ldpc->nqc, XSDFEC_LDPC_QC_TABLE_ADDR_BASE,
				 XSDFEC_QC_TABLE_DEPTH);
err_out:
	kमुक्त(ldpc);
	वापस ret;
पूर्ण

अटल पूर्णांक xsdfec_set_order(काष्ठा xsdfec_dev *xsdfec, व्योम __user *arg)
अणु
	bool order_invalid;
	क्रमागत xsdfec_order order;
	पूर्णांक err;

	err = get_user(order, (क्रमागत xsdfec_order __user *)arg);
	अगर (err)
		वापस -EFAULT;

	order_invalid = (order != XSDFEC_MAINTAIN_ORDER) &&
			(order != XSDFEC_OUT_OF_ORDER);
	अगर (order_invalid)
		वापस -EINVAL;

	/* Verअगरy Device has not started */
	अगर (xsdfec->state == XSDFEC_STARTED)
		वापस -EIO;

	xsdfec_regग_लिखो(xsdfec, XSDFEC_ORDER_ADDR, order);

	xsdfec->config.order = order;

	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_set_bypass(काष्ठा xsdfec_dev *xsdfec, bool __user *arg)
अणु
	bool bypass;
	पूर्णांक err;

	err = get_user(bypass, arg);
	अगर (err)
		वापस -EFAULT;

	/* Verअगरy Device has not started */
	अगर (xsdfec->state == XSDFEC_STARTED)
		वापस -EIO;

	अगर (bypass)
		xsdfec_regग_लिखो(xsdfec, XSDFEC_BYPASS_ADDR, 1);
	अन्यथा
		xsdfec_regग_लिखो(xsdfec, XSDFEC_BYPASS_ADDR, 0);

	xsdfec->config.bypass = bypass;

	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_is_active(काष्ठा xsdfec_dev *xsdfec, bool __user *arg)
अणु
	u32 reg_value;
	bool is_active;
	पूर्णांक err;

	reg_value = xsdfec_regपढ़ो(xsdfec, XSDFEC_ACTIVE_ADDR);
	/* using a द्विगुन ! चालक instead of casting */
	is_active = !!(reg_value & XSDFEC_IS_ACTIVITY_SET);
	err = put_user(is_active, arg);
	अगर (err)
		वापस -EFAULT;

	वापस err;
पूर्ण

अटल u32
xsdfec_translate_axis_width_cfg_val(क्रमागत xsdfec_axis_width axis_width_cfg)
अणु
	u32 axis_width_field = 0;

	चयन (axis_width_cfg) अणु
	हाल XSDFEC_1x128b:
		axis_width_field = 0;
		अवरोध;
	हाल XSDFEC_2x128b:
		axis_width_field = 1;
		अवरोध;
	हाल XSDFEC_4x128b:
		axis_width_field = 2;
		अवरोध;
	पूर्ण

	वापस axis_width_field;
पूर्ण

अटल u32 xsdfec_translate_axis_words_cfg_val(क्रमागत xsdfec_axis_word_include
	axis_word_inc_cfg)
अणु
	u32 axis_words_field = 0;

	अगर (axis_word_inc_cfg == XSDFEC_FIXED_VALUE ||
	    axis_word_inc_cfg == XSDFEC_IN_BLOCK)
		axis_words_field = 0;
	अन्यथा अगर (axis_word_inc_cfg == XSDFEC_PER_AXI_TRANSACTION)
		axis_words_field = 1;

	वापस axis_words_field;
पूर्ण

अटल पूर्णांक xsdfec_cfg_axi_streams(काष्ठा xsdfec_dev *xsdfec)
अणु
	u32 reg_value;
	u32 करोut_words_field;
	u32 करोut_width_field;
	u32 din_words_field;
	u32 din_width_field;
	काष्ठा xsdfec_config *config = &xsdfec->config;

	/* translate config info to रेजिस्टर values */
	करोut_words_field =
		xsdfec_translate_axis_words_cfg_val(config->करोut_word_include);
	करोut_width_field =
		xsdfec_translate_axis_width_cfg_val(config->करोut_width);
	din_words_field =
		xsdfec_translate_axis_words_cfg_val(config->din_word_include);
	din_width_field =
		xsdfec_translate_axis_width_cfg_val(config->din_width);

	reg_value = करोut_words_field << XSDFEC_AXIS_DOUT_WORDS_LSB;
	reg_value |= करोut_width_field << XSDFEC_AXIS_DOUT_WIDTH_LSB;
	reg_value |= din_words_field << XSDFEC_AXIS_DIN_WORDS_LSB;
	reg_value |= din_width_field << XSDFEC_AXIS_DIN_WIDTH_LSB;

	xsdfec_regग_लिखो(xsdfec, XSDFEC_AXIS_WIDTH_ADDR, reg_value);

	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_dev_खोलो(काष्ठा inode *iptr, काष्ठा file *fptr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_dev_release(काष्ठा inode *iptr, काष्ठा file *fptr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_start(काष्ठा xsdfec_dev *xsdfec)
अणु
	u32 regपढ़ो;

	regपढ़ो = xsdfec_regपढ़ो(xsdfec, XSDFEC_FEC_CODE_ADDR);
	regपढ़ो &= 0x1;
	अगर (regपढ़ो != xsdfec->config.code) अणु
		dev_dbg(xsdfec->dev,
			"%s SDFEC HW code does not match driver code, reg %d, code %d",
			__func__, regपढ़ो, xsdfec->config.code);
		वापस -EINVAL;
	पूर्ण

	/* Set AXIS enable */
	xsdfec_regग_लिखो(xsdfec, XSDFEC_AXIS_ENABLE_ADDR,
			XSDFEC_AXIS_ENABLE_MASK);
	/* Done */
	xsdfec->state = XSDFEC_STARTED;
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_stop(काष्ठा xsdfec_dev *xsdfec)
अणु
	u32 regपढ़ो;

	अगर (xsdfec->state != XSDFEC_STARTED)
		dev_dbg(xsdfec->dev, "Device not started correctly");
	/* Disable AXIS_ENABLE Input पूर्णांकerfaces only */
	regपढ़ो = xsdfec_regपढ़ो(xsdfec, XSDFEC_AXIS_ENABLE_ADDR);
	regपढ़ो &= (~XSDFEC_AXIS_IN_ENABLE_MASK);
	xsdfec_regग_लिखो(xsdfec, XSDFEC_AXIS_ENABLE_ADDR, regपढ़ो);
	/* Stop */
	xsdfec->state = XSDFEC_STOPPED;
	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_clear_stats(काष्ठा xsdfec_dev *xsdfec)
अणु
	spin_lock_irqsave(&xsdfec->error_data_lock, xsdfec->flags);
	xsdfec->isr_err_count = 0;
	xsdfec->uecc_count = 0;
	xsdfec->cecc_count = 0;
	spin_unlock_irqrestore(&xsdfec->error_data_lock, xsdfec->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक xsdfec_get_stats(काष्ठा xsdfec_dev *xsdfec, व्योम __user *arg)
अणु
	पूर्णांक err;
	काष्ठा xsdfec_stats user_stats;

	spin_lock_irqsave(&xsdfec->error_data_lock, xsdfec->flags);
	user_stats.isr_err_count = xsdfec->isr_err_count;
	user_stats.cecc_count = xsdfec->cecc_count;
	user_stats.uecc_count = xsdfec->uecc_count;
	xsdfec->stats_updated = false;
	spin_unlock_irqrestore(&xsdfec->error_data_lock, xsdfec->flags);

	err = copy_to_user(arg, &user_stats, माप(user_stats));
	अगर (err)
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक xsdfec_set_शेष_config(काष्ठा xsdfec_dev *xsdfec)
अणु
	/* Ensure रेजिस्टरs are aligned with core configuration */
	xsdfec_regग_लिखो(xsdfec, XSDFEC_FEC_CODE_ADDR, xsdfec->config.code);
	xsdfec_cfg_axi_streams(xsdfec);
	update_config_from_hw(xsdfec);

	वापस 0;
पूर्ण

अटल दीर्घ xsdfec_dev_ioctl(काष्ठा file *fptr, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ data)
अणु
	काष्ठा xsdfec_dev *xsdfec;
	व्योम __user *arg = (व्योम __user *)data;
	पूर्णांक rval;

	xsdfec = container_of(fptr->निजी_data, काष्ठा xsdfec_dev, miscdev);

	/* In failed state allow only reset and get status IOCTLs */
	अगर (xsdfec->state == XSDFEC_NEEDS_RESET &&
	    (cmd != XSDFEC_SET_DEFAULT_CONFIG && cmd != XSDFEC_GET_STATUS &&
	     cmd != XSDFEC_GET_STATS && cmd != XSDFEC_CLEAR_STATS)) अणु
		वापस -EPERM;
	पूर्ण

	चयन (cmd) अणु
	हाल XSDFEC_START_DEV:
		rval = xsdfec_start(xsdfec);
		अवरोध;
	हाल XSDFEC_STOP_DEV:
		rval = xsdfec_stop(xsdfec);
		अवरोध;
	हाल XSDFEC_CLEAR_STATS:
		rval = xsdfec_clear_stats(xsdfec);
		अवरोध;
	हाल XSDFEC_GET_STATS:
		rval = xsdfec_get_stats(xsdfec, arg);
		अवरोध;
	हाल XSDFEC_GET_STATUS:
		rval = xsdfec_get_status(xsdfec, arg);
		अवरोध;
	हाल XSDFEC_GET_CONFIG:
		rval = xsdfec_get_config(xsdfec, arg);
		अवरोध;
	हाल XSDFEC_SET_DEFAULT_CONFIG:
		rval = xsdfec_set_शेष_config(xsdfec);
		अवरोध;
	हाल XSDFEC_SET_IRQ:
		rval = xsdfec_set_irq(xsdfec, arg);
		अवरोध;
	हाल XSDFEC_SET_TURBO:
		rval = xsdfec_set_turbo(xsdfec, arg);
		अवरोध;
	हाल XSDFEC_GET_TURBO:
		rval = xsdfec_get_turbo(xsdfec, arg);
		अवरोध;
	हाल XSDFEC_ADD_LDPC_CODE_PARAMS:
		rval = xsdfec_add_ldpc(xsdfec, arg);
		अवरोध;
	हाल XSDFEC_SET_ORDER:
		rval = xsdfec_set_order(xsdfec, arg);
		अवरोध;
	हाल XSDFEC_SET_BYPASS:
		rval = xsdfec_set_bypass(xsdfec, arg);
		अवरोध;
	हाल XSDFEC_IS_ACTIVE:
		rval = xsdfec_is_active(xsdfec, (bool __user *)arg);
		अवरोध;
	शेष:
		rval = -ENOTTY;
		अवरोध;
	पूर्ण
	वापस rval;
पूर्ण

अटल __poll_t xsdfec_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t mask = 0;
	काष्ठा xsdfec_dev *xsdfec;

	xsdfec = container_of(file->निजी_data, काष्ठा xsdfec_dev, miscdev);

	अगर (!xsdfec)
		वापस EPOLLNVAL | EPOLLHUP;

	poll_रुको(file, &xsdfec->रुकोq, रुको);

	/* XSDFEC ISR detected an error */
	spin_lock_irqsave(&xsdfec->error_data_lock, xsdfec->flags);
	अगर (xsdfec->state_updated)
		mask |= EPOLLIN | EPOLLPRI;

	अगर (xsdfec->stats_updated)
		mask |= EPOLLIN | EPOLLRDNORM;
	spin_unlock_irqrestore(&xsdfec->error_data_lock, xsdfec->flags);

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations xsdfec_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = xsdfec_dev_खोलो,
	.release = xsdfec_dev_release,
	.unlocked_ioctl = xsdfec_dev_ioctl,
	.poll = xsdfec_poll,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

अटल पूर्णांक xsdfec_parse_of(काष्ठा xsdfec_dev *xsdfec)
अणु
	काष्ठा device *dev = xsdfec->dev;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक rval;
	स्थिर अक्षर *fec_code;
	u32 din_width;
	u32 din_word_include;
	u32 करोut_width;
	u32 करोut_word_include;

	rval = of_property_पढ़ो_string(node, "xlnx,sdfec-code", &fec_code);
	अगर (rval < 0)
		वापस rval;

	अगर (!strहालcmp(fec_code, "ldpc"))
		xsdfec->config.code = XSDFEC_LDPC_CODE;
	अन्यथा अगर (!strहालcmp(fec_code, "turbo"))
		xsdfec->config.code = XSDFEC_TURBO_CODE;
	अन्यथा
		वापस -EINVAL;

	rval = of_property_पढ़ो_u32(node, "xlnx,sdfec-din-words",
				    &din_word_include);
	अगर (rval < 0)
		वापस rval;

	अगर (din_word_include < XSDFEC_AXIS_WORDS_INCLUDE_MAX)
		xsdfec->config.din_word_include = din_word_include;
	अन्यथा
		वापस -EINVAL;

	rval = of_property_पढ़ो_u32(node, "xlnx,sdfec-din-width", &din_width);
	अगर (rval < 0)
		वापस rval;

	चयन (din_width) अणु
	/* Fall through and set क्रम valid values */
	हाल XSDFEC_1x128b:
	हाल XSDFEC_2x128b:
	हाल XSDFEC_4x128b:
		xsdfec->config.din_width = din_width;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rval = of_property_पढ़ो_u32(node, "xlnx,sdfec-dout-words",
				    &करोut_word_include);
	अगर (rval < 0)
		वापस rval;

	अगर (करोut_word_include < XSDFEC_AXIS_WORDS_INCLUDE_MAX)
		xsdfec->config.करोut_word_include = करोut_word_include;
	अन्यथा
		वापस -EINVAL;

	rval = of_property_पढ़ो_u32(node, "xlnx,sdfec-dout-width", &करोut_width);
	अगर (rval < 0)
		वापस rval;

	चयन (करोut_width) अणु
	/* Fall through and set क्रम valid values */
	हाल XSDFEC_1x128b:
	हाल XSDFEC_2x128b:
	हाल XSDFEC_4x128b:
		xsdfec->config.करोut_width = करोut_width;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Write LDPC to CODE Register */
	xsdfec_regग_लिखो(xsdfec, XSDFEC_FEC_CODE_ADDR, xsdfec->config.code);

	xsdfec_cfg_axi_streams(xsdfec);

	वापस 0;
पूर्ण

अटल irqवापस_t xsdfec_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xsdfec_dev *xsdfec = dev_id;
	irqवापस_t ret = IRQ_HANDLED;
	u32 ecc_err;
	u32 isr_err;
	u32 uecc_count;
	u32 cecc_count;
	u32 isr_err_count;
	u32 aecc_count;
	u32 पंचांगp;

	WARN_ON(xsdfec->irq != irq);

	/* Mask Interrupts */
	xsdfec_isr_enable(xsdfec, false);
	xsdfec_ecc_isr_enable(xsdfec, false);
	/* Read ISR */
	ecc_err = xsdfec_regपढ़ो(xsdfec, XSDFEC_ECC_ISR_ADDR);
	isr_err = xsdfec_regपढ़ो(xsdfec, XSDFEC_ISR_ADDR);
	/* Clear the पूर्णांकerrupts */
	xsdfec_regग_लिखो(xsdfec, XSDFEC_ECC_ISR_ADDR, ecc_err);
	xsdfec_regग_लिखो(xsdfec, XSDFEC_ISR_ADDR, isr_err);

	पंचांगp = ecc_err & XSDFEC_ALL_ECC_ISR_MBE_MASK;
	/* Count uncorrectable 2-bit errors */
	uecc_count = hweight32(पंचांगp);
	/* Count all ECC errors */
	aecc_count = hweight32(ecc_err);
	/* Number of correctable 1-bit ECC error */
	cecc_count = aecc_count - 2 * uecc_count;
	/* Count ISR errors */
	isr_err_count = hweight32(isr_err);
	dev_dbg(xsdfec->dev, "tmp=%x, uecc=%x, aecc=%x, cecc=%x, isr=%x", पंचांगp,
		uecc_count, aecc_count, cecc_count, isr_err_count);
	dev_dbg(xsdfec->dev, "uecc=%x, cecc=%x, isr=%x", xsdfec->uecc_count,
		xsdfec->cecc_count, xsdfec->isr_err_count);

	spin_lock_irqsave(&xsdfec->error_data_lock, xsdfec->flags);
	/* Add new errors to a 2-bits counter */
	अगर (uecc_count)
		xsdfec->uecc_count += uecc_count;
	/* Add new errors to a 1-bits counter */
	अगर (cecc_count)
		xsdfec->cecc_count += cecc_count;
	/* Add new errors to a ISR counter */
	अगर (isr_err_count)
		xsdfec->isr_err_count += isr_err_count;

	/* Update state/stats flag */
	अगर (uecc_count) अणु
		अगर (ecc_err & XSDFEC_ECC_ISR_MBE_MASK)
			xsdfec->state = XSDFEC_NEEDS_RESET;
		अन्यथा अगर (ecc_err & XSDFEC_PL_INIT_ECC_ISR_MBE_MASK)
			xsdfec->state = XSDFEC_PL_RECONFIGURE;
		xsdfec->stats_updated = true;
		xsdfec->state_updated = true;
	पूर्ण

	अगर (cecc_count)
		xsdfec->stats_updated = true;

	अगर (isr_err_count) अणु
		xsdfec->state = XSDFEC_NEEDS_RESET;
		xsdfec->stats_updated = true;
		xsdfec->state_updated = true;
	पूर्ण

	spin_unlock_irqrestore(&xsdfec->error_data_lock, xsdfec->flags);
	dev_dbg(xsdfec->dev, "state=%x, stats=%x", xsdfec->state_updated,
		xsdfec->stats_updated);

	/* Enable another polling */
	अगर (xsdfec->state_updated || xsdfec->stats_updated)
		wake_up_पूर्णांकerruptible(&xsdfec->रुकोq);
	अन्यथा
		ret = IRQ_NONE;

	/* Unmask Interrupts */
	xsdfec_isr_enable(xsdfec, true);
	xsdfec_ecc_isr_enable(xsdfec, true);

	वापस ret;
पूर्ण

अटल पूर्णांक xsdfec_clk_init(काष्ठा platक्रमm_device *pdev,
			   काष्ठा xsdfec_clks *clks)
अणु
	पूर्णांक err;

	clks->core_clk = devm_clk_get(&pdev->dev, "core_clk");
	अगर (IS_ERR(clks->core_clk)) अणु
		dev_err(&pdev->dev, "failed to get core_clk");
		वापस PTR_ERR(clks->core_clk);
	पूर्ण

	clks->axi_clk = devm_clk_get(&pdev->dev, "s_axi_aclk");
	अगर (IS_ERR(clks->axi_clk)) अणु
		dev_err(&pdev->dev, "failed to get axi_clk");
		वापस PTR_ERR(clks->axi_clk);
	पूर्ण

	clks->din_words_clk = devm_clk_get(&pdev->dev, "s_axis_din_words_aclk");
	अगर (IS_ERR(clks->din_words_clk)) अणु
		अगर (PTR_ERR(clks->din_words_clk) != -ENOENT) अणु
			err = PTR_ERR(clks->din_words_clk);
			वापस err;
		पूर्ण
		clks->din_words_clk = शून्य;
	पूर्ण

	clks->din_clk = devm_clk_get(&pdev->dev, "s_axis_din_aclk");
	अगर (IS_ERR(clks->din_clk)) अणु
		अगर (PTR_ERR(clks->din_clk) != -ENOENT) अणु
			err = PTR_ERR(clks->din_clk);
			वापस err;
		पूर्ण
		clks->din_clk = शून्य;
	पूर्ण

	clks->करोut_clk = devm_clk_get(&pdev->dev, "m_axis_dout_aclk");
	अगर (IS_ERR(clks->करोut_clk)) अणु
		अगर (PTR_ERR(clks->करोut_clk) != -ENOENT) अणु
			err = PTR_ERR(clks->करोut_clk);
			वापस err;
		पूर्ण
		clks->करोut_clk = शून्य;
	पूर्ण

	clks->करोut_words_clk =
		devm_clk_get(&pdev->dev, "s_axis_dout_words_aclk");
	अगर (IS_ERR(clks->करोut_words_clk)) अणु
		अगर (PTR_ERR(clks->करोut_words_clk) != -ENOENT) अणु
			err = PTR_ERR(clks->करोut_words_clk);
			वापस err;
		पूर्ण
		clks->करोut_words_clk = शून्य;
	पूर्ण

	clks->ctrl_clk = devm_clk_get(&pdev->dev, "s_axis_ctrl_aclk");
	अगर (IS_ERR(clks->ctrl_clk)) अणु
		अगर (PTR_ERR(clks->ctrl_clk) != -ENOENT) अणु
			err = PTR_ERR(clks->ctrl_clk);
			वापस err;
		पूर्ण
		clks->ctrl_clk = शून्य;
	पूर्ण

	clks->status_clk = devm_clk_get(&pdev->dev, "m_axis_status_aclk");
	अगर (IS_ERR(clks->status_clk)) अणु
		अगर (PTR_ERR(clks->status_clk) != -ENOENT) अणु
			err = PTR_ERR(clks->status_clk);
			वापस err;
		पूर्ण
		clks->status_clk = शून्य;
	पूर्ण

	err = clk_prepare_enable(clks->core_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable core_clk (%d)", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(clks->axi_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable axi_clk (%d)", err);
		जाओ err_disable_core_clk;
	पूर्ण

	err = clk_prepare_enable(clks->din_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable din_clk (%d)", err);
		जाओ err_disable_axi_clk;
	पूर्ण

	err = clk_prepare_enable(clks->din_words_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable din_words_clk (%d)", err);
		जाओ err_disable_din_clk;
	पूर्ण

	err = clk_prepare_enable(clks->करोut_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable dout_clk (%d)", err);
		जाओ err_disable_din_words_clk;
	पूर्ण

	err = clk_prepare_enable(clks->करोut_words_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable dout_words_clk (%d)",
			err);
		जाओ err_disable_करोut_clk;
	पूर्ण

	err = clk_prepare_enable(clks->ctrl_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable ctrl_clk (%d)", err);
		जाओ err_disable_करोut_words_clk;
	पूर्ण

	err = clk_prepare_enable(clks->status_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable status_clk (%d)\n", err);
		जाओ err_disable_ctrl_clk;
	पूर्ण

	वापस err;

err_disable_ctrl_clk:
	clk_disable_unprepare(clks->ctrl_clk);
err_disable_करोut_words_clk:
	clk_disable_unprepare(clks->करोut_words_clk);
err_disable_करोut_clk:
	clk_disable_unprepare(clks->करोut_clk);
err_disable_din_words_clk:
	clk_disable_unprepare(clks->din_words_clk);
err_disable_din_clk:
	clk_disable_unprepare(clks->din_clk);
err_disable_axi_clk:
	clk_disable_unprepare(clks->axi_clk);
err_disable_core_clk:
	clk_disable_unprepare(clks->core_clk);

	वापस err;
पूर्ण

अटल व्योम xsdfec_disable_all_clks(काष्ठा xsdfec_clks *clks)
अणु
	clk_disable_unprepare(clks->status_clk);
	clk_disable_unprepare(clks->ctrl_clk);
	clk_disable_unprepare(clks->करोut_words_clk);
	clk_disable_unprepare(clks->करोut_clk);
	clk_disable_unprepare(clks->din_words_clk);
	clk_disable_unprepare(clks->din_clk);
	clk_disable_unprepare(clks->core_clk);
	clk_disable_unprepare(clks->axi_clk);
पूर्ण

अटल पूर्णांक xsdfec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xsdfec_dev *xsdfec;
	काष्ठा device *dev;
	काष्ठा resource *res;
	पूर्णांक err;
	bool irq_enabled = true;

	xsdfec = devm_kzalloc(&pdev->dev, माप(*xsdfec), GFP_KERNEL);
	अगर (!xsdfec)
		वापस -ENOMEM;

	xsdfec->dev = &pdev->dev;
	spin_lock_init(&xsdfec->error_data_lock);

	err = xsdfec_clk_init(pdev, &xsdfec->clks);
	अगर (err)
		वापस err;

	dev = xsdfec->dev;
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	xsdfec->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(xsdfec->regs)) अणु
		err = PTR_ERR(xsdfec->regs);
		जाओ err_xsdfec_dev;
	पूर्ण

	xsdfec->irq = platक्रमm_get_irq(pdev, 0);
	अगर (xsdfec->irq < 0) अणु
		dev_dbg(dev, "platform_get_irq failed");
		irq_enabled = false;
	पूर्ण

	err = xsdfec_parse_of(xsdfec);
	अगर (err < 0)
		जाओ err_xsdfec_dev;

	update_config_from_hw(xsdfec);

	/* Save driver निजी data */
	platक्रमm_set_drvdata(pdev, xsdfec);

	अगर (irq_enabled) अणु
		init_रुकोqueue_head(&xsdfec->रुकोq);
		/* Register IRQ thपढ़ो */
		err = devm_request_thपढ़ोed_irq(dev, xsdfec->irq, शून्य,
						xsdfec_irq_thपढ़ो, IRQF_ONESHOT,
						"xilinx-sdfec16", xsdfec);
		अगर (err < 0) अणु
			dev_err(dev, "unable to request IRQ%d", xsdfec->irq);
			जाओ err_xsdfec_dev;
		पूर्ण
	पूर्ण

	err = ida_alloc(&dev_nrs, GFP_KERNEL);
	अगर (err < 0)
		जाओ err_xsdfec_dev;
	xsdfec->dev_id = err;

	snम_लिखो(xsdfec->dev_name, DEV_NAME_LEN, "xsdfec%d", xsdfec->dev_id);
	xsdfec->miscdev.minor = MISC_DYNAMIC_MINOR;
	xsdfec->miscdev.name = xsdfec->dev_name;
	xsdfec->miscdev.fops = &xsdfec_fops;
	xsdfec->miscdev.parent = dev;
	err = misc_रेजिस्टर(&xsdfec->miscdev);
	अगर (err) अणु
		dev_err(dev, "error:%d. Unable to register device", err);
		जाओ err_xsdfec_ida;
	पूर्ण
	वापस 0;

err_xsdfec_ida:
	ida_मुक्त(&dev_nrs, xsdfec->dev_id);
err_xsdfec_dev:
	xsdfec_disable_all_clks(&xsdfec->clks);
	वापस err;
पूर्ण

अटल पूर्णांक xsdfec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xsdfec_dev *xsdfec;

	xsdfec = platक्रमm_get_drvdata(pdev);
	misc_deरेजिस्टर(&xsdfec->miscdev);
	ida_मुक्त(&dev_nrs, xsdfec->dev_id);
	xsdfec_disable_all_clks(&xsdfec->clks);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xsdfec_of_match[] = अणु
	अणु
		.compatible = "xlnx,sd-fec-1.1",
	पूर्ण,
	अणु /* end of table */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xsdfec_of_match);

अटल काष्ठा platक्रमm_driver xsdfec_driver = अणु
	.driver = अणु
		.name = "xilinx-sdfec",
		.of_match_table = xsdfec_of_match,
	पूर्ण,
	.probe = xsdfec_probe,
	.हटाओ =  xsdfec_हटाओ,
पूर्ण;

module_platक्रमm_driver(xsdfec_driver);

MODULE_AUTHOR("Xilinx, Inc");
MODULE_DESCRIPTION("Xilinx SD-FEC16 Driver");
MODULE_LICENSE("GPL");
