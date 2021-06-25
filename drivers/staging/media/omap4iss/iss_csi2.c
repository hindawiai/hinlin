<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI OMAP4 ISS V4L2 Driver - CSI PHY module
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <media/v4l2-common.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/mm.h>

#समावेश "iss.h"
#समावेश "iss_regs.h"
#समावेश "iss_csi2.h"

/*
 * csi2_अगर_enable - Enable CSI2 Receiver पूर्णांकerface.
 * @enable: enable flag
 *
 */
अटल व्योम csi2_अगर_enable(काष्ठा iss_csi2_device *csi2, u8 enable)
अणु
	काष्ठा iss_csi2_ctrl_cfg *currctrl = &csi2->ctrl;

	iss_reg_update(csi2->iss, csi2->regs1, CSI2_CTRL, CSI2_CTRL_IF_EN,
		       enable ? CSI2_CTRL_IF_EN : 0);

	currctrl->अगर_enable = enable;
पूर्ण

/*
 * csi2_recv_config - CSI2 receiver module configuration.
 * @currctrl: iss_csi2_ctrl_cfg काष्ठाure
 *
 */
अटल व्योम csi2_recv_config(काष्ठा iss_csi2_device *csi2,
			     काष्ठा iss_csi2_ctrl_cfg *currctrl)
अणु
	u32 reg = 0;

	अगर (currctrl->frame_mode)
		reg |= CSI2_CTRL_FRAME;
	अन्यथा
		reg &= ~CSI2_CTRL_FRAME;

	अगर (currctrl->vp_clk_enable)
		reg |= CSI2_CTRL_VP_CLK_EN;
	अन्यथा
		reg &= ~CSI2_CTRL_VP_CLK_EN;

	अगर (currctrl->vp_only_enable)
		reg |= CSI2_CTRL_VP_ONLY_EN;
	अन्यथा
		reg &= ~CSI2_CTRL_VP_ONLY_EN;

	reg &= ~CSI2_CTRL_VP_OUT_CTRL_MASK;
	reg |= currctrl->vp_out_ctrl << CSI2_CTRL_VP_OUT_CTRL_SHIFT;

	अगर (currctrl->ecc_enable)
		reg |= CSI2_CTRL_ECC_EN;
	अन्यथा
		reg &= ~CSI2_CTRL_ECC_EN;

	/*
	 * Set MFlag निश्चितion boundaries to:
	 * Low: 4/8 of FIFO size
	 * High: 6/8 of FIFO size
	 */
	reg &= ~(CSI2_CTRL_MFLAG_LEVH_MASK | CSI2_CTRL_MFLAG_LEVL_MASK);
	reg |= (2 << CSI2_CTRL_MFLAG_LEVH_SHIFT) |
	       (4 << CSI2_CTRL_MFLAG_LEVL_SHIFT);

	/* Generation of 16x64-bit bursts (Recommended) */
	reg |= CSI2_CTRL_BURST_SIZE_EXPAND;

	/* Do Non-Posted ग_लिखोs (Recommended) */
	reg |= CSI2_CTRL_NON_POSTED_WRITE;

	/*
	 * Enक्रमce Little endian क्रम all क्रमmats, including:
	 * YUV4:2:2 8-bit and YUV4:2:0 Legacy
	 */
	reg |= CSI2_CTRL_ENDIANNESS;

	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTRL, reg);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक csi2_input_fmts[] = अणु
	MEDIA_BUS_FMT_SGRBG10_1X10,
	MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8,
	MEDIA_BUS_FMT_SRGGB10_1X10,
	MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8,
	MEDIA_BUS_FMT_SBGGR10_1X10,
	MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8,
	MEDIA_BUS_FMT_SGBRG10_1X10,
	MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8,
	MEDIA_BUS_FMT_SBGGR8_1X8,
	MEDIA_BUS_FMT_SGBRG8_1X8,
	MEDIA_BUS_FMT_SGRBG8_1X8,
	MEDIA_BUS_FMT_SRGGB8_1X8,
	MEDIA_BUS_FMT_UYVY8_1X16,
	MEDIA_BUS_FMT_YUYV8_1X16,
पूर्ण;

/* To set the क्रमmat on the CSI2 requires a mapping function that takes
 * the following inमाला_दो:
 * - 3 dअगरferent क्रमmats (at this समय)
 * - 2 destinations (mem, vp+mem) (vp only handled separately)
 * - 2 decompression options (on, off)
 * Output should be CSI2 frame क्रमmat code
 * Array indices as follows: [क्रमmat][dest][decompr]
 * Not all combinations are valid. 0 means invalid.
 */
अटल स्थिर u16 __csi2_fmt_map[][2][2] = अणु
	/* RAW10 क्रमmats */
	अणु
		/* Output to memory */
		अणु
			/* No DPCM decompression */
			CSI2_PIX_FMT_RAW10_EXP16,
			/* DPCM decompression */
			0,
		पूर्ण,
		/* Output to both */
		अणु
			/* No DPCM decompression */
			CSI2_PIX_FMT_RAW10_EXP16_VP,
			/* DPCM decompression */
			0,
		पूर्ण,
	पूर्ण,
	/* RAW10 DPCM8 क्रमmats */
	अणु
		/* Output to memory */
		अणु
			/* No DPCM decompression */
			CSI2_USERDEF_8BIT_DATA1,
			/* DPCM decompression */
			CSI2_USERDEF_8BIT_DATA1_DPCM10,
		पूर्ण,
		/* Output to both */
		अणु
			/* No DPCM decompression */
			CSI2_PIX_FMT_RAW8_VP,
			/* DPCM decompression */
			CSI2_USERDEF_8BIT_DATA1_DPCM10_VP,
		पूर्ण,
	पूर्ण,
	/* RAW8 क्रमmats */
	अणु
		/* Output to memory */
		अणु
			/* No DPCM decompression */
			CSI2_PIX_FMT_RAW8,
			/* DPCM decompression */
			0,
		पूर्ण,
		/* Output to both */
		अणु
			/* No DPCM decompression */
			CSI2_PIX_FMT_RAW8_VP,
			/* DPCM decompression */
			0,
		पूर्ण,
	पूर्ण,
	/* YUV422 क्रमmats */
	अणु
		/* Output to memory */
		अणु
			/* No DPCM decompression */
			CSI2_PIX_FMT_YUV422_8BIT,
			/* DPCM decompression */
			0,
		पूर्ण,
		/* Output to both */
		अणु
			/* No DPCM decompression */
			CSI2_PIX_FMT_YUV422_8BIT_VP16,
			/* DPCM decompression */
			0,
		पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * csi2_ctx_map_क्रमmat - Map CSI2 sink media bus क्रमmat to CSI2 क्रमmat ID
 * @csi2: ISS CSI2 device
 *
 * Returns CSI2 physical क्रमmat id
 */
अटल u16 csi2_ctx_map_क्रमmat(काष्ठा iss_csi2_device *csi2)
अणु
	स्थिर काष्ठा v4l2_mbus_framefmt *fmt = &csi2->क्रमmats[CSI2_PAD_SINK];
	पूर्णांक fmtidx, destidx;

	चयन (fmt->code) अणु
	हाल MEDIA_BUS_FMT_SGRBG10_1X10:
	हाल MEDIA_BUS_FMT_SRGGB10_1X10:
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
	हाल MEDIA_BUS_FMT_SGBRG10_1X10:
		fmtidx = 0;
		अवरोध;
	हाल MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8:
	हाल MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8:
	हाल MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8:
	हाल MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8:
		fmtidx = 1;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
		fmtidx = 2;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
		fmtidx = 3;
		अवरोध;
	शेष:
		WARN(1, "CSI2: pixel format %08x unsupported!\n",
		     fmt->code);
		वापस 0;
	पूर्ण

	अगर (!(csi2->output & CSI2_OUTPUT_IPIPEIF) &&
	    !(csi2->output & CSI2_OUTPUT_MEMORY)) अणु
		/* Neither output enabled is a valid combination */
		वापस CSI2_PIX_FMT_OTHERS;
	पूर्ण

	/* If we need to skip frames at the beginning of the stream disable the
	 * video port to aव्योम sending the skipped frames to the IPIPEIF.
	 */
	destidx = csi2->frame_skip ? 0 : !!(csi2->output & CSI2_OUTPUT_IPIPEIF);

	वापस __csi2_fmt_map[fmtidx][destidx][csi2->dpcm_decompress];
पूर्ण

/*
 * csi2_set_outaddr - Set memory address to save output image
 * @csi2: Poपूर्णांकer to ISS CSI2a device.
 * @addr: 32-bit memory address aligned on 32 byte boundary.
 *
 * Sets the memory address where the output will be saved.
 *
 * Returns 0 अगर successful, or -EINVAL अगर the address is not in the 32 byte
 * boundary.
 */
अटल व्योम csi2_set_outaddr(काष्ठा iss_csi2_device *csi2, u32 addr)
अणु
	काष्ठा iss_csi2_ctx_cfg *ctx = &csi2->contexts[0];

	ctx->ping_addr = addr;
	ctx->pong_addr = addr;
	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTX_PING_ADDR(ctx->ctxnum),
		      ctx->ping_addr);
	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTX_PONG_ADDR(ctx->ctxnum),
		      ctx->pong_addr);
पूर्ण

/*
 * is_usr_def_mapping - Checks whether USER_DEF_MAPPING should
 *			be enabled by CSI2.
 * @क्रमmat_id: mapped क्रमmat id
 *
 */
अटल अंतरभूत पूर्णांक is_usr_def_mapping(u32 क्रमmat_id)
अणु
	वापस (क्रमmat_id & 0xf0) == 0x40 ? 1 : 0;
पूर्ण

/*
 * csi2_ctx_enable - Enable specअगरied CSI2 context
 * @ctxnum: Context number, valid between 0 and 7 values.
 * @enable: enable
 *
 */
अटल व्योम csi2_ctx_enable(काष्ठा iss_csi2_device *csi2, u8 ctxnum, u8 enable)
अणु
	काष्ठा iss_csi2_ctx_cfg *ctx = &csi2->contexts[ctxnum];
	u32 reg;

	reg = iss_reg_पढ़ो(csi2->iss, csi2->regs1, CSI2_CTX_CTRL1(ctxnum));

	अगर (enable) अणु
		अचिन्हित पूर्णांक skip = 0;

		अगर (csi2->frame_skip)
			skip = csi2->frame_skip;
		अन्यथा अगर (csi2->output & CSI2_OUTPUT_MEMORY)
			skip = 1;

		reg &= ~CSI2_CTX_CTRL1_COUNT_MASK;
		reg |= CSI2_CTX_CTRL1_COUNT_UNLOCK
		    |  (skip << CSI2_CTX_CTRL1_COUNT_SHIFT)
		    |  CSI2_CTX_CTRL1_CTX_EN;
	पूर्ण अन्यथा अणु
		reg &= ~CSI2_CTX_CTRL1_CTX_EN;
	पूर्ण

	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTX_CTRL1(ctxnum), reg);
	ctx->enabled = enable;
पूर्ण

/*
 * csi2_ctx_config - CSI2 context configuration.
 * @ctx: context configuration
 *
 */
अटल व्योम csi2_ctx_config(काष्ठा iss_csi2_device *csi2,
			    काष्ठा iss_csi2_ctx_cfg *ctx)
अणु
	u32 reg = 0;

	ctx->frame = 0;

	/* Set up CSI2_CTx_CTRL1 */
	अगर (ctx->eof_enabled)
		reg = CSI2_CTX_CTRL1_खातापूर्ण_EN;

	अगर (ctx->eol_enabled)
		reg |= CSI2_CTX_CTRL1_EOL_EN;

	अगर (ctx->checksum_enabled)
		reg |= CSI2_CTX_CTRL1_CS_EN;

	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTX_CTRL1(ctx->ctxnum), reg);

	/* Set up CSI2_CTx_CTRL2 */
	reg = ctx->भव_id << CSI2_CTX_CTRL2_VIRTUAL_ID_SHIFT;
	reg |= ctx->क्रमmat_id << CSI2_CTX_CTRL2_FORMAT_SHIFT;

	अगर (ctx->dpcm_decompress && ctx->dpcm_predictor)
		reg |= CSI2_CTX_CTRL2_DPCM_PRED;

	अगर (is_usr_def_mapping(ctx->क्रमmat_id))
		reg |= 2 << CSI2_CTX_CTRL2_USER_DEF_MAP_SHIFT;

	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTX_CTRL2(ctx->ctxnum), reg);

	/* Set up CSI2_CTx_CTRL3 */
	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTX_CTRL3(ctx->ctxnum),
		      ctx->alpha << CSI2_CTX_CTRL3_ALPHA_SHIFT);

	/* Set up CSI2_CTx_DAT_OFST */
	iss_reg_update(csi2->iss, csi2->regs1, CSI2_CTX_DAT_OFST(ctx->ctxnum),
		       CSI2_CTX_DAT_OFST_MASK, ctx->data_offset);

	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTX_PING_ADDR(ctx->ctxnum),
		      ctx->ping_addr);
	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTX_PONG_ADDR(ctx->ctxnum),
		      ctx->pong_addr);
पूर्ण

/*
 * csi2_timing_config - CSI2 timing configuration.
 * @timing: csi2_timing_cfg काष्ठाure
 */
अटल व्योम csi2_timing_config(काष्ठा iss_csi2_device *csi2,
			       काष्ठा iss_csi2_timing_cfg *timing)
अणु
	u32 reg;

	reg = iss_reg_पढ़ो(csi2->iss, csi2->regs1, CSI2_TIMING);

	अगर (timing->क्रमce_rx_mode)
		reg |= CSI2_TIMING_FORCE_RX_MODE_IO1;
	अन्यथा
		reg &= ~CSI2_TIMING_FORCE_RX_MODE_IO1;

	अगर (timing->stop_state_16x)
		reg |= CSI2_TIMING_STOP_STATE_X16_IO1;
	अन्यथा
		reg &= ~CSI2_TIMING_STOP_STATE_X16_IO1;

	अगर (timing->stop_state_4x)
		reg |= CSI2_TIMING_STOP_STATE_X4_IO1;
	अन्यथा
		reg &= ~CSI2_TIMING_STOP_STATE_X4_IO1;

	reg &= ~CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK;
	reg |= timing->stop_state_counter <<
	       CSI2_TIMING_STOP_STATE_COUNTER_IO1_SHIFT;

	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_TIMING, reg);
पूर्ण

/*
 * csi2_irq_ctx_set - Enables CSI2 Context IRQs.
 * @enable: Enable/disable CSI2 Context पूर्णांकerrupts
 */
अटल व्योम csi2_irq_ctx_set(काष्ठा iss_csi2_device *csi2, पूर्णांक enable)
अणु
	स्थिर u32 mask = CSI2_CTX_IRQ_FE | CSI2_CTX_IRQ_FS;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTX_IRQSTATUS(i),
			      mask);
		अगर (enable)
			iss_reg_set(csi2->iss, csi2->regs1,
				    CSI2_CTX_IRQENABLE(i), mask);
		अन्यथा
			iss_reg_clr(csi2->iss, csi2->regs1,
				    CSI2_CTX_IRQENABLE(i), mask);
	पूर्ण
पूर्ण

/*
 * csi2_irq_complexio1_set - Enables CSI2 ComplexIO IRQs.
 * @enable: Enable/disable CSI2 ComplexIO #1 पूर्णांकerrupts
 */
अटल व्योम csi2_irq_complexio1_set(काष्ठा iss_csi2_device *csi2, पूर्णांक enable)
अणु
	u32 reg;

	reg = CSI2_COMPLEXIO_IRQ_STATEALLULPMEXIT |
		CSI2_COMPLEXIO_IRQ_STATEALLULPMENTER |
		CSI2_COMPLEXIO_IRQ_STATEULPM5 |
		CSI2_COMPLEXIO_IRQ_ERRCONTROL5 |
		CSI2_COMPLEXIO_IRQ_ERRESC5 |
		CSI2_COMPLEXIO_IRQ_ERRSOTSYNCHS5 |
		CSI2_COMPLEXIO_IRQ_ERRSOTHS5 |
		CSI2_COMPLEXIO_IRQ_STATEULPM4 |
		CSI2_COMPLEXIO_IRQ_ERRCONTROL4 |
		CSI2_COMPLEXIO_IRQ_ERRESC4 |
		CSI2_COMPLEXIO_IRQ_ERRSOTSYNCHS4 |
		CSI2_COMPLEXIO_IRQ_ERRSOTHS4 |
		CSI2_COMPLEXIO_IRQ_STATEULPM3 |
		CSI2_COMPLEXIO_IRQ_ERRCONTROL3 |
		CSI2_COMPLEXIO_IRQ_ERRESC3 |
		CSI2_COMPLEXIO_IRQ_ERRSOTSYNCHS3 |
		CSI2_COMPLEXIO_IRQ_ERRSOTHS3 |
		CSI2_COMPLEXIO_IRQ_STATEULPM2 |
		CSI2_COMPLEXIO_IRQ_ERRCONTROL2 |
		CSI2_COMPLEXIO_IRQ_ERRESC2 |
		CSI2_COMPLEXIO_IRQ_ERRSOTSYNCHS2 |
		CSI2_COMPLEXIO_IRQ_ERRSOTHS2 |
		CSI2_COMPLEXIO_IRQ_STATEULPM1 |
		CSI2_COMPLEXIO_IRQ_ERRCONTROL1 |
		CSI2_COMPLEXIO_IRQ_ERRESC1 |
		CSI2_COMPLEXIO_IRQ_ERRSOTSYNCHS1 |
		CSI2_COMPLEXIO_IRQ_ERRSOTHS1;
	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_COMPLEXIO_IRQSTATUS, reg);
	अगर (enable)
		iss_reg_set(csi2->iss, csi2->regs1, CSI2_COMPLEXIO_IRQENABLE,
			    reg);
	अन्यथा
		iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_COMPLEXIO_IRQENABLE,
			      0);
पूर्ण

/*
 * csi2_irq_status_set - Enables CSI2 Status IRQs.
 * @enable: Enable/disable CSI2 Status पूर्णांकerrupts
 */
अटल व्योम csi2_irq_status_set(काष्ठा iss_csi2_device *csi2, पूर्णांक enable)
अणु
	u32 reg;

	reg = CSI2_IRQ_OCP_ERR |
		CSI2_IRQ_SHORT_PACKET |
		CSI2_IRQ_ECC_CORRECTION |
		CSI2_IRQ_ECC_NO_CORRECTION |
		CSI2_IRQ_COMPLEXIO_ERR |
		CSI2_IRQ_FIFO_OVF |
		CSI2_IRQ_CONTEXT0;
	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_IRQSTATUS, reg);
	अगर (enable)
		iss_reg_set(csi2->iss, csi2->regs1, CSI2_IRQENABLE, reg);
	अन्यथा
		iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_IRQENABLE, 0);
पूर्ण

/*
 * omap4iss_csi2_reset - Resets the CSI2 module.
 *
 * Must be called with the phy lock held.
 *
 * Returns 0 अगर successful, or -EBUSY अगर घातer command didn't respond.
 */
पूर्णांक omap4iss_csi2_reset(काष्ठा iss_csi2_device *csi2)
अणु
	अचिन्हित पूर्णांक समयout;

	अगर (!csi2->available)
		वापस -ENODEV;

	अगर (csi2->phy->phy_in_use)
		वापस -EBUSY;

	iss_reg_set(csi2->iss, csi2->regs1, CSI2_SYSCONFIG,
		    CSI2_SYSCONFIG_SOFT_RESET);

	समयout = iss_poll_condition_समयout(
		iss_reg_पढ़ो(csi2->iss, csi2->regs1, CSI2_SYSSTATUS) &
		CSI2_SYSSTATUS_RESET_DONE, 500, 100, 200);
	अगर (समयout) अणु
		dev_err(csi2->iss->dev, "CSI2: Soft reset timeout!\n");
		वापस -EBUSY;
	पूर्ण

	iss_reg_set(csi2->iss, csi2->regs1, CSI2_COMPLEXIO_CFG,
		    CSI2_COMPLEXIO_CFG_RESET_CTRL);

	समयout = iss_poll_condition_समयout(
		iss_reg_पढ़ो(csi2->iss, csi2->phy->phy_regs, REGISTER1) &
		REGISTER1_RESET_DONE_CTRLCLK, 10000, 100, 500);
	अगर (समयout) अणु
		dev_err(csi2->iss->dev, "CSI2: CSI2_96M_FCLK reset timeout!\n");
		वापस -EBUSY;
	पूर्ण

	iss_reg_update(csi2->iss, csi2->regs1, CSI2_SYSCONFIG,
		       CSI2_SYSCONFIG_MSTANDBY_MODE_MASK |
		       CSI2_SYSCONFIG_AUTO_IDLE,
		       CSI2_SYSCONFIG_MSTANDBY_MODE_NO);

	वापस 0;
पूर्ण

अटल पूर्णांक csi2_configure(काष्ठा iss_csi2_device *csi2)
अणु
	स्थिर काष्ठा iss_v4l2_subdevs_group *pdata;
	काष्ठा iss_csi2_timing_cfg *timing = &csi2->timing[0];
	काष्ठा v4l2_subdev *sensor;
	काष्ठा media_pad *pad;

	/*
	 * CSI2 fields that can be updated जबतक the context has
	 * been enabled or the पूर्णांकerface has been enabled are not
	 * updated dynamically currently. So we करो not allow to
	 * reconfigure अगर either has been enabled
	 */
	अगर (csi2->contexts[0].enabled || csi2->ctrl.अगर_enable)
		वापस -EBUSY;

	pad = media_entity_remote_pad(&csi2->pads[CSI2_PAD_SINK]);
	sensor = media_entity_to_v4l2_subdev(pad->entity);
	pdata = sensor->host_priv;

	csi2->frame_skip = 0;
	v4l2_subdev_call(sensor, sensor, g_skip_frames, &csi2->frame_skip);

	csi2->ctrl.vp_out_ctrl = pdata->bus.csi2.vpclk_भाग;
	csi2->ctrl.frame_mode = ISS_CSI2_FRAME_IMMEDIATE;
	csi2->ctrl.ecc_enable = pdata->bus.csi2.crc;

	timing->क्रमce_rx_mode = 1;
	timing->stop_state_16x = 1;
	timing->stop_state_4x = 1;
	timing->stop_state_counter = 0x1ff;

	/*
	 * The CSI2 receiver can't करो any क्रमmat conversion except DPCM
	 * decompression, so every set_क्रमmat call configures both pads
	 * and enables DPCM decompression as a special हाल:
	 */
	अगर (csi2->क्रमmats[CSI2_PAD_SINK].code !=
	    csi2->क्रमmats[CSI2_PAD_SOURCE].code)
		csi2->dpcm_decompress = true;
	अन्यथा
		csi2->dpcm_decompress = false;

	csi2->contexts[0].क्रमmat_id = csi2_ctx_map_क्रमmat(csi2);

	अगर (csi2->video_out.bpl_padding == 0)
		csi2->contexts[0].data_offset = 0;
	अन्यथा
		csi2->contexts[0].data_offset = csi2->video_out.bpl_value;

	/*
	 * Enable end of frame and end of line संकेतs generation क्रम
	 * context 0. These संकेतs are generated from CSI2 receiver to
	 * qualअगरy the last pixel of a frame and the last pixel of a line.
	 * Without enabling the संकेतs CSI2 receiver ग_लिखोs data to memory
	 * beyond buffer size and/or data line offset is not handled correctly.
	 */
	csi2->contexts[0].eof_enabled = 1;
	csi2->contexts[0].eol_enabled = 1;

	csi2_irq_complexio1_set(csi2, 1);
	csi2_irq_ctx_set(csi2, 1);
	csi2_irq_status_set(csi2, 1);

	/* Set configuration (timings, क्रमmat and links) */
	csi2_timing_config(csi2, timing);
	csi2_recv_config(csi2, &csi2->ctrl);
	csi2_ctx_config(csi2, &csi2->contexts[0]);

	वापस 0;
पूर्ण

/*
 * csi2_prपूर्णांक_status - Prपूर्णांकs CSI2 debug inक्रमmation.
 */
#घोषणा CSI2_PRINT_REGISTER(iss, regs, name)\
	dev_dbg(iss->dev, "###CSI2 " #name "=0x%08x\n", \
		iss_reg_पढ़ो(iss, regs, CSI2_##name))

अटल व्योम csi2_prपूर्णांक_status(काष्ठा iss_csi2_device *csi2)
अणु
	काष्ठा iss_device *iss = csi2->iss;

	अगर (!csi2->available)
		वापस;

	dev_dbg(iss->dev, "-------------CSI2 Register dump-------------\n");

	CSI2_PRINT_REGISTER(iss, csi2->regs1, SYSCONFIG);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, SYSSTATUS);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, IRQENABLE);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, IRQSTATUS);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTRL);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, DBG_H);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, COMPLEXIO_CFG);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, COMPLEXIO_IRQSTATUS);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, SHORT_PACKET);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, COMPLEXIO_IRQENABLE);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, DBG_P);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, TIMING);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_CTRL1(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_CTRL2(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_DAT_OFST(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_PING_ADDR(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_PONG_ADDR(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_IRQENABLE(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_IRQSTATUS(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_CTRL3(0));

	dev_dbg(iss->dev, "--------------------------------------------\n");
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt handling
 */

/*
 * csi2_isr_buffer - Does buffer handling at end-of-frame
 * when writing to memory.
 */
अटल व्योम csi2_isr_buffer(काष्ठा iss_csi2_device *csi2)
अणु
	काष्ठा iss_buffer *buffer;

	csi2_ctx_enable(csi2, 0, 0);

	buffer = omap4iss_video_buffer_next(&csi2->video_out);

	/*
	 * Let video queue operation restart engine अगर there is an underrun
	 * condition.
	 */
	अगर (!buffer)
		वापस;

	csi2_set_outaddr(csi2, buffer->iss_addr);
	csi2_ctx_enable(csi2, 0, 1);
पूर्ण

अटल व्योम csi2_isr_ctx(काष्ठा iss_csi2_device *csi2,
			 काष्ठा iss_csi2_ctx_cfg *ctx)
अणु
	अचिन्हित पूर्णांक n = ctx->ctxnum;
	u32 status;

	status = iss_reg_पढ़ो(csi2->iss, csi2->regs1, CSI2_CTX_IRQSTATUS(n));
	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_CTX_IRQSTATUS(n), status);

	अगर (omap4iss_module_sync_is_stopping(&csi2->रुको, &csi2->stopping))
		वापस;

	/* Propagate frame number */
	अगर (status & CSI2_CTX_IRQ_FS) अणु
		काष्ठा iss_pipeline *pipe =
				     to_iss_pipeline(&csi2->subdev.entity);
		u16 frame;
		u16 delta;

		frame = iss_reg_पढ़ो(csi2->iss, csi2->regs1,
				     CSI2_CTX_CTRL2(ctx->ctxnum))
		      >> CSI2_CTX_CTRL2_FRAME_SHIFT;

		अगर (frame == 0) अणु
			/* A zero value means that the counter isn't implemented
			 * by the source. Increment the frame number in software
			 * in that हाल.
			 */
			atomic_inc(&pipe->frame_number);
		पूर्ण अन्यथा अणु
			/* Extend the 16 bit frame number to 32 bits by
			 * computing the delta between two consecutive CSI2
			 * frame numbers and adding it to the software frame
			 * number. The hardware counter starts at 1 and wraps
			 * from 0xffff to 1 without going through 0, so subtract
			 * 1 when the counter wraps.
			 */
			delta = frame - ctx->frame;
			अगर (frame < ctx->frame)
				delta--;
			ctx->frame = frame;

			atomic_add(delta, &pipe->frame_number);
		पूर्ण
	पूर्ण

	अगर (!(status & CSI2_CTX_IRQ_FE))
		वापस;

	/* Skip पूर्णांकerrupts until we reach the frame skip count. The CSI2 will be
	 * स्वतःmatically disabled, as the frame skip count has been programmed
	 * in the CSI2_CTx_CTRL1::COUNT field, so re-enable it.
	 *
	 * It would have been nice to rely on the FRAME_NUMBER पूर्णांकerrupt instead
	 * but it turned out that the पूर्णांकerrupt is only generated when the CSI2
	 * ग_लिखोs to memory (the CSI2_CTx_CTRL1::COUNT field is decreased
	 * correctly and reaches 0 when data is क्रमwarded to the video port only
	 * but no पूर्णांकerrupt arrives). Maybe a CSI2 hardware bug.
	 */
	अगर (csi2->frame_skip) अणु
		csi2->frame_skip--;
		अगर (csi2->frame_skip == 0) अणु
			ctx->क्रमmat_id = csi2_ctx_map_क्रमmat(csi2);
			csi2_ctx_config(csi2, ctx);
			csi2_ctx_enable(csi2, n, 1);
		पूर्ण
		वापस;
	पूर्ण

	अगर (csi2->output & CSI2_OUTPUT_MEMORY)
		csi2_isr_buffer(csi2);
पूर्ण

/*
 * omap4iss_csi2_isr - CSI2 पूर्णांकerrupt handling.
 */
व्योम omap4iss_csi2_isr(काष्ठा iss_csi2_device *csi2)
अणु
	काष्ठा iss_pipeline *pipe = to_iss_pipeline(&csi2->subdev.entity);
	u32 csi2_irqstatus, cpxio1_irqstatus;
	काष्ठा iss_device *iss = csi2->iss;

	अगर (!csi2->available)
		वापस;

	csi2_irqstatus = iss_reg_पढ़ो(csi2->iss, csi2->regs1, CSI2_IRQSTATUS);
	iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_IRQSTATUS, csi2_irqstatus);

	/* Failure Cases */
	अगर (csi2_irqstatus & CSI2_IRQ_COMPLEXIO_ERR) अणु
		cpxio1_irqstatus = iss_reg_पढ़ो(csi2->iss, csi2->regs1,
						CSI2_COMPLEXIO_IRQSTATUS);
		iss_reg_ग_लिखो(csi2->iss, csi2->regs1, CSI2_COMPLEXIO_IRQSTATUS,
			      cpxio1_irqstatus);
		dev_dbg(iss->dev, "CSI2: ComplexIO Error IRQ %x\n",
			cpxio1_irqstatus);
		pipe->error = true;
	पूर्ण

	अगर (csi2_irqstatus & (CSI2_IRQ_OCP_ERR |
			      CSI2_IRQ_SHORT_PACKET |
			      CSI2_IRQ_ECC_NO_CORRECTION |
			      CSI2_IRQ_COMPLEXIO_ERR |
			      CSI2_IRQ_FIFO_OVF)) अणु
		dev_dbg(iss->dev,
			"CSI2 Err: OCP:%d SHORT:%d ECC:%d CPXIO:%d OVF:%d\n",
			csi2_irqstatus & CSI2_IRQ_OCP_ERR ? 1 : 0,
			csi2_irqstatus & CSI2_IRQ_SHORT_PACKET ? 1 : 0,
			csi2_irqstatus & CSI2_IRQ_ECC_NO_CORRECTION ? 1 : 0,
			csi2_irqstatus & CSI2_IRQ_COMPLEXIO_ERR ? 1 : 0,
			csi2_irqstatus & CSI2_IRQ_FIFO_OVF ? 1 : 0);
		pipe->error = true;
	पूर्ण

	/* Successful हालs */
	अगर (csi2_irqstatus & CSI2_IRQ_CONTEXT0)
		csi2_isr_ctx(csi2, &csi2->contexts[0]);

	अगर (csi2_irqstatus & CSI2_IRQ_ECC_CORRECTION)
		dev_dbg(iss->dev, "CSI2: ECC correction done\n");
पूर्ण

/* -----------------------------------------------------------------------------
 * ISS video operations
 */

/*
 * csi2_queue - Queues the first buffer when using memory output
 * @video: The video node
 * @buffer: buffer to queue
 */
अटल पूर्णांक csi2_queue(काष्ठा iss_video *video, काष्ठा iss_buffer *buffer)
अणु
	काष्ठा iss_csi2_device *csi2 = container_of(video,
				काष्ठा iss_csi2_device, video_out);

	csi2_set_outaddr(csi2, buffer->iss_addr);

	/*
	 * If streaming was enabled beक्रमe there was a buffer queued
	 * or underrun happened in the ISR, the hardware was not enabled
	 * and DMA queue flag ISS_VIDEO_DMAQUEUE_UNDERRUN is still set.
	 * Enable it now.
	 */
	अगर (csi2->video_out.dmaqueue_flags & ISS_VIDEO_DMAQUEUE_UNDERRUN) अणु
		/* Enable / disable context 0 and IRQs */
		csi2_अगर_enable(csi2, 1);
		csi2_ctx_enable(csi2, 0, 1);
		iss_video_dmaqueue_flags_clr(&csi2->video_out);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iss_video_operations csi2_issvideo_ops = अणु
	.queue = csi2_queue,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 */

अटल काष्ठा v4l2_mbus_framefmt *
__csi2_get_क्रमmat(काष्ठा iss_csi2_device *csi2,
		  काष्ठा v4l2_subdev_pad_config *cfg,
		  अचिन्हित पूर्णांक pad,
		  क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&csi2->subdev, cfg, pad);

	वापस &csi2->क्रमmats[pad];
पूर्ण

अटल व्योम
csi2_try_क्रमmat(काष्ठा iss_csi2_device *csi2,
		काष्ठा v4l2_subdev_pad_config *cfg,
		अचिन्हित पूर्णांक pad,
		काष्ठा v4l2_mbus_framefmt *fmt,
		क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	u32 pixelcode;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	स्थिर काष्ठा iss_क्रमmat_info *info;
	अचिन्हित पूर्णांक i;

	चयन (pad) अणु
	हाल CSI2_PAD_SINK:
		/* Clamp the width and height to valid range (1-8191). */
		क्रम (i = 0; i < ARRAY_SIZE(csi2_input_fmts); i++) अणु
			अगर (fmt->code == csi2_input_fmts[i])
				अवरोध;
		पूर्ण

		/* If not found, use SGRBG10 as शेष */
		अगर (i >= ARRAY_SIZE(csi2_input_fmts))
			fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;

		fmt->width = clamp_t(u32, fmt->width, 1, 8191);
		fmt->height = clamp_t(u32, fmt->height, 1, 8191);
		अवरोध;

	हाल CSI2_PAD_SOURCE:
		/* Source क्रमmat same as sink क्रमmat, except क्रम DPCM
		 * compression.
		 */
		pixelcode = fmt->code;
		क्रमmat = __csi2_get_क्रमmat(csi2, cfg, CSI2_PAD_SINK, which);
		स_नकल(fmt, क्रमmat, माप(*fmt));

		/*
		 * Only Allow DPCM decompression, and check that the
		 * pattern is preserved
		 */
		info = omap4iss_video_क्रमmat_info(fmt->code);
		अगर (info->uncompressed == pixelcode)
			fmt->code = pixelcode;
		अवरोध;
	पूर्ण

	/* RGB, non-पूर्णांकerlaced */
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

/*
 * csi2_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd     : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg    : V4L2 subdev pad config
 * @code   : poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csi2_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा iss_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	स्थिर काष्ठा iss_क्रमmat_info *info;

	अगर (code->pad == CSI2_PAD_SINK) अणु
		अगर (code->index >= ARRAY_SIZE(csi2_input_fmts))
			वापस -EINVAL;

		code->code = csi2_input_fmts[code->index];
	पूर्ण अन्यथा अणु
		क्रमmat = __csi2_get_क्रमmat(csi2, cfg, CSI2_PAD_SINK,
					   code->which);
		चयन (code->index) अणु
		हाल 0:
			/* Passthrough sink pad code */
			code->code = क्रमmat->code;
			अवरोध;
		हाल 1:
			/* Uncompressed code */
			info = omap4iss_video_क्रमmat_info(क्रमmat->code);
			अगर (info->uncompressed == क्रमmat->code)
				वापस -EINVAL;

			code->code = info->uncompressed;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक csi2_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा iss_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	अगर (fse->index != 0)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = 1;
	क्रमmat.height = 1;
	csi2_try_क्रमmat(csi2, cfg, fse->pad, &क्रमmat, fse->which);
	fse->min_width = क्रमmat.width;
	fse->min_height = क्रमmat.height;

	अगर (क्रमmat.code != fse->code)
		वापस -EINVAL;

	क्रमmat.code = fse->code;
	क्रमmat.width = -1;
	क्रमmat.height = -1;
	csi2_try_क्रमmat(csi2, cfg, fse->pad, &क्रमmat, fse->which);
	fse->max_width = क्रमmat.width;
	fse->max_height = क्रमmat.height;

	वापस 0;
पूर्ण

/*
 * csi2_get_क्रमmat - Handle get क्रमmat by pads subdev method
 * @sd : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad config
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csi2_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा iss_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __csi2_get_क्रमmat(csi2, cfg, fmt->pad, fmt->which);
	अगर (!क्रमmat)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;
	वापस 0;
पूर्ण

/*
 * csi2_set_क्रमmat - Handle set क्रमmat by pads subdev method
 * @sd : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad config
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csi2_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा iss_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __csi2_get_क्रमmat(csi2, cfg, fmt->pad, fmt->which);
	अगर (!क्रमmat)
		वापस -EINVAL;

	csi2_try_क्रमmat(csi2, cfg, fmt->pad, &fmt->क्रमmat, fmt->which);
	*क्रमmat = fmt->क्रमmat;

	/* Propagate the क्रमmat from sink to source */
	अगर (fmt->pad == CSI2_PAD_SINK) अणु
		क्रमmat = __csi2_get_क्रमmat(csi2, cfg, CSI2_PAD_SOURCE,
					   fmt->which);
		*क्रमmat = fmt->क्रमmat;
		csi2_try_क्रमmat(csi2, cfg, CSI2_PAD_SOURCE, क्रमmat, fmt->which);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक csi2_link_validate(काष्ठा v4l2_subdev *sd, काष्ठा media_link *link,
			      काष्ठा v4l2_subdev_क्रमmat *source_fmt,
			      काष्ठा v4l2_subdev_क्रमmat *sink_fmt)
अणु
	काष्ठा iss_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा iss_pipeline *pipe = to_iss_pipeline(&csi2->subdev.entity);
	पूर्णांक rval;

	pipe->बाह्यal = media_entity_to_v4l2_subdev(link->source->entity);
	rval = omap4iss_get_बाह्यal_info(pipe, link);
	अगर (rval < 0)
		वापस rval;

	वापस v4l2_subdev_link_validate_शेष(sd, link, source_fmt,
						 sink_fmt);
पूर्ण

/*
 * csi2_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: ISS CSI2 V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad क्रमmats with शेष values. If fh is not शून्य, try
 * क्रमmats are initialized on the file handle. Otherwise active क्रमmats are
 * initialized on the device.
 */
अटल पूर्णांक csi2_init_क्रमmats(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;

	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	क्रमmat.pad = CSI2_PAD_SINK;
	क्रमmat.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	क्रमmat.क्रमmat.width = 4096;
	क्रमmat.क्रमmat.height = 4096;
	csi2_set_क्रमmat(sd, fh ? fh->pad : शून्य, &क्रमmat);

	वापस 0;
पूर्ण

/*
 * csi2_set_stream - Enable/Disable streaming on the CSI2 module
 * @sd: ISS CSI2 V4L2 subdevice
 * @enable: ISS pipeline stream state
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल पूर्णांक csi2_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा iss_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा iss_device *iss = csi2->iss;
	काष्ठा iss_video *video_out = &csi2->video_out;
	पूर्णांक ret = 0;

	अगर (csi2->state == ISS_PIPELINE_STREAM_STOPPED) अणु
		अगर (enable == ISS_PIPELINE_STREAM_STOPPED)
			वापस 0;

		omap4iss_subclk_enable(iss, csi2->subclk);
	पूर्ण

	चयन (enable) अणु
	हाल ISS_PIPELINE_STREAM_CONTINUOUS: अणु
		ret = omap4iss_csiphy_config(iss, sd);
		अगर (ret < 0)
			वापस ret;

		अगर (omap4iss_csiphy_acquire(csi2->phy) < 0)
			वापस -ENODEV;
		csi2_configure(csi2);
		csi2_prपूर्णांक_status(csi2);

		/*
		 * When outputting to memory with no buffer available, let the
		 * buffer queue handler start the hardware. A DMA queue flag
		 * ISS_VIDEO_DMAQUEUE_QUEUED will be set as soon as there is
		 * a buffer available.
		 */
		अगर (csi2->output & CSI2_OUTPUT_MEMORY &&
		    !(video_out->dmaqueue_flags & ISS_VIDEO_DMAQUEUE_QUEUED))
			अवरोध;
		/* Enable context 0 and IRQs */
		atomic_set(&csi2->stopping, 0);
		csi2_ctx_enable(csi2, 0, 1);
		csi2_अगर_enable(csi2, 1);
		iss_video_dmaqueue_flags_clr(video_out);
		अवरोध;
	पूर्ण
	हाल ISS_PIPELINE_STREAM_STOPPED:
		अगर (csi2->state == ISS_PIPELINE_STREAM_STOPPED)
			वापस 0;
		अगर (omap4iss_module_sync_idle(&sd->entity, &csi2->रुको,
					      &csi2->stopping))
			ret = -ETIMEDOUT;
		csi2_ctx_enable(csi2, 0, 0);
		csi2_अगर_enable(csi2, 0);
		csi2_irq_ctx_set(csi2, 0);
		omap4iss_csiphy_release(csi2->phy);
		omap4iss_subclk_disable(iss, csi2->subclk);
		iss_video_dmaqueue_flags_clr(video_out);
		अवरोध;
	पूर्ण

	csi2->state = enable;
	वापस ret;
पूर्ण

/* subdev video operations */
अटल स्थिर काष्ठा v4l2_subdev_video_ops csi2_video_ops = अणु
	.s_stream = csi2_set_stream,
पूर्ण;

/* subdev pad operations */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops csi2_pad_ops = अणु
	.क्रमागत_mbus_code = csi2_क्रमागत_mbus_code,
	.क्रमागत_frame_size = csi2_क्रमागत_frame_size,
	.get_fmt = csi2_get_क्रमmat,
	.set_fmt = csi2_set_क्रमmat,
	.link_validate = csi2_link_validate,
पूर्ण;

/* subdev operations */
अटल स्थिर काष्ठा v4l2_subdev_ops csi2_ops = अणु
	.video = &csi2_video_ops,
	.pad = &csi2_pad_ops,
पूर्ण;

/* subdev पूर्णांकernal operations */
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops csi2_पूर्णांकernal_ops = अणु
	.खोलो = csi2_init_क्रमmats,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media entity operations
 */

/*
 * csi2_link_setup - Setup CSI2 connections.
 * @entity : Poपूर्णांकer to media entity काष्ठाure
 * @local  : Poपूर्णांकer to local pad array
 * @remote : Poपूर्णांकer to remote pad array
 * @flags  : Link flags
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csi2_link_setup(काष्ठा media_entity *entity,
			   स्थिर काष्ठा media_pad *local,
			   स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा iss_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा iss_csi2_ctrl_cfg *ctrl = &csi2->ctrl;
	अचिन्हित पूर्णांक index = local->index;

	/* FIXME: this is actually a hack! */
	अगर (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

	/*
	 * The ISS core करोesn't support pipelines with multiple video outमाला_दो.
	 * Revisit this when it will be implemented, and वापस -EBUSY क्रम now.
	 */

	चयन (index) अणु
	हाल CSI2_PAD_SOURCE:
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (csi2->output & ~CSI2_OUTPUT_MEMORY)
				वापस -EBUSY;
			csi2->output |= CSI2_OUTPUT_MEMORY;
		पूर्ण अन्यथा अणु
			csi2->output &= ~CSI2_OUTPUT_MEMORY;
		पूर्ण
		अवरोध;

	हाल CSI2_PAD_SOURCE | 2 << 16:
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (csi2->output & ~CSI2_OUTPUT_IPIPEIF)
				वापस -EBUSY;
			csi2->output |= CSI2_OUTPUT_IPIPEIF;
		पूर्ण अन्यथा अणु
			csi2->output &= ~CSI2_OUTPUT_IPIPEIF;
		पूर्ण
		अवरोध;

	शेष:
		/* Link from camera to CSI2 is fixed... */
		वापस -EINVAL;
	पूर्ण

	ctrl->vp_only_enable = csi2->output & CSI2_OUTPUT_MEMORY ? false : true;
	ctrl->vp_clk_enable = !!(csi2->output & CSI2_OUTPUT_IPIPEIF);

	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations csi2_media_ops = अणु
	.link_setup = csi2_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

व्योम omap4iss_csi2_unरेजिस्टर_entities(काष्ठा iss_csi2_device *csi2)
अणु
	v4l2_device_unरेजिस्टर_subdev(&csi2->subdev);
	omap4iss_video_unरेजिस्टर(&csi2->video_out);
पूर्ण

पूर्णांक omap4iss_csi2_रेजिस्टर_entities(काष्ठा iss_csi2_device *csi2,
				    काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	/* Register the subdev and video nodes. */
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &csi2->subdev);
	अगर (ret < 0)
		जाओ error;

	ret = omap4iss_video_रेजिस्टर(&csi2->video_out, vdev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	omap4iss_csi2_unरेजिस्टर_entities(csi2);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * ISS CSI2 initialisation and cleanup
 */

/*
 * csi2_init_entities - Initialize subdev and media entity.
 * @csi2: Poपूर्णांकer to csi2 काष्ठाure.
 * वापस -ENOMEM or zero on success
 */
अटल पूर्णांक csi2_init_entities(काष्ठा iss_csi2_device *csi2, स्थिर अक्षर *subname)
अणु
	काष्ठा v4l2_subdev *sd = &csi2->subdev;
	काष्ठा media_pad *pads = csi2->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;
	अक्षर name[V4L2_SUBDEV_NAME_SIZE];

	v4l2_subdev_init(sd, &csi2_ops);
	sd->पूर्णांकernal_ops = &csi2_पूर्णांकernal_ops;
	snम_लिखो(name, माप(name), "CSI2%s", subname);
	snम_लिखो(sd->name, माप(sd->name), "OMAP4 ISS %s", name);

	sd->grp_id = BIT(16);	/* group ID क्रम iss subdevs */
	v4l2_set_subdevdata(sd, csi2);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[CSI2_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	pads[CSI2_PAD_SINK].flags = MEDIA_PAD_FL_SINK;

	me->ops = &csi2_media_ops;
	ret = media_entity_pads_init(me, CSI2_PADS_NUM, pads);
	अगर (ret < 0)
		वापस ret;

	csi2_init_क्रमmats(sd, शून्य);

	/* Video device node */
	csi2->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	csi2->video_out.ops = &csi2_issvideo_ops;
	csi2->video_out.bpl_alignment = 32;
	csi2->video_out.bpl_zero_padding = 1;
	csi2->video_out.bpl_max = 0x1ffe0;
	csi2->video_out.iss = csi2->iss;
	csi2->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 3;

	ret = omap4iss_video_init(&csi2->video_out, name);
	अगर (ret < 0)
		जाओ error_video;

	वापस 0;

error_video:
	media_entity_cleanup(&csi2->subdev.entity);
	वापस ret;
पूर्ण

/*
 * omap4iss_csi2_init - Routine क्रम module driver init
 */
पूर्णांक omap4iss_csi2_init(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_csi2_device *csi2a = &iss->csi2a;
	काष्ठा iss_csi2_device *csi2b = &iss->csi2b;
	पूर्णांक ret;

	csi2a->iss = iss;
	csi2a->available = 1;
	csi2a->regs1 = OMAP4_ISS_MEM_CSI2_A_REGS1;
	csi2a->phy = &iss->csiphy1;
	csi2a->subclk = OMAP4_ISS_SUBCLK_CSI2_A;
	csi2a->state = ISS_PIPELINE_STREAM_STOPPED;
	init_रुकोqueue_head(&csi2a->रुको);

	ret = csi2_init_entities(csi2a, "a");
	अगर (ret < 0)
		वापस ret;

	csi2b->iss = iss;
	csi2b->available = 1;
	csi2b->regs1 = OMAP4_ISS_MEM_CSI2_B_REGS1;
	csi2b->phy = &iss->csiphy2;
	csi2b->subclk = OMAP4_ISS_SUBCLK_CSI2_B;
	csi2b->state = ISS_PIPELINE_STREAM_STOPPED;
	init_रुकोqueue_head(&csi2b->रुको);

	ret = csi2_init_entities(csi2b, "b");
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * omap4iss_csi2_create_links() - CSI2 pads links creation
 * @iss: Poपूर्णांकer to ISS device
 *
 * वापस negative error code or zero on success
 */
पूर्णांक omap4iss_csi2_create_links(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_csi2_device *csi2a = &iss->csi2a;
	काष्ठा iss_csi2_device *csi2b = &iss->csi2b;
	पूर्णांक ret;

	/* Connect the CSI2a subdev to the video node. */
	ret = media_create_pad_link(&csi2a->subdev.entity, CSI2_PAD_SOURCE,
				    &csi2a->video_out.video.entity, 0, 0);
	अगर (ret < 0)
		वापस ret;

	/* Connect the CSI2b subdev to the video node. */
	ret = media_create_pad_link(&csi2b->subdev.entity, CSI2_PAD_SOURCE,
				    &csi2b->video_out.video.entity, 0, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * omap4iss_csi2_cleanup - Routine क्रम module driver cleanup
 */
व्योम omap4iss_csi2_cleanup(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_csi2_device *csi2a = &iss->csi2a;
	काष्ठा iss_csi2_device *csi2b = &iss->csi2b;

	omap4iss_video_cleanup(&csi2a->video_out);
	media_entity_cleanup(&csi2a->subdev.entity);

	omap4iss_video_cleanup(&csi2b->video_out);
	media_entity_cleanup(&csi2b->subdev.entity);
पूर्ण
