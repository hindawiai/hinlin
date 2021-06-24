<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ispcsi2.c
 *
 * TI OMAP3 ISP - CSI2 module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */
#समावेश <linux/delay.h>
#समावेश <media/v4l2-common.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/mm.h>

#समावेश "isp.h"
#समावेश "ispreg.h"
#समावेश "ispcsi2.h"

/*
 * csi2_अगर_enable - Enable CSI2 Receiver पूर्णांकerface.
 * @enable: enable flag
 *
 */
अटल व्योम csi2_अगर_enable(काष्ठा isp_device *isp,
			   काष्ठा isp_csi2_device *csi2, u8 enable)
अणु
	काष्ठा isp_csi2_ctrl_cfg *currctrl = &csi2->ctrl;

	isp_reg_clr_set(isp, csi2->regs1, ISPCSI2_CTRL, ISPCSI2_CTRL_IF_EN,
			enable ? ISPCSI2_CTRL_IF_EN : 0);

	currctrl->अगर_enable = enable;
पूर्ण

/*
 * csi2_recv_config - CSI2 receiver module configuration.
 * @currctrl: isp_csi2_ctrl_cfg काष्ठाure
 *
 */
अटल व्योम csi2_recv_config(काष्ठा isp_device *isp,
			     काष्ठा isp_csi2_device *csi2,
			     काष्ठा isp_csi2_ctrl_cfg *currctrl)
अणु
	u32 reg;

	reg = isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_CTRL);

	अगर (currctrl->frame_mode)
		reg |= ISPCSI2_CTRL_FRAME;
	अन्यथा
		reg &= ~ISPCSI2_CTRL_FRAME;

	अगर (currctrl->vp_clk_enable)
		reg |= ISPCSI2_CTRL_VP_CLK_EN;
	अन्यथा
		reg &= ~ISPCSI2_CTRL_VP_CLK_EN;

	अगर (currctrl->vp_only_enable)
		reg |= ISPCSI2_CTRL_VP_ONLY_EN;
	अन्यथा
		reg &= ~ISPCSI2_CTRL_VP_ONLY_EN;

	reg &= ~ISPCSI2_CTRL_VP_OUT_CTRL_MASK;
	reg |= currctrl->vp_out_ctrl << ISPCSI2_CTRL_VP_OUT_CTRL_SHIFT;

	अगर (currctrl->ecc_enable)
		reg |= ISPCSI2_CTRL_ECC_EN;
	अन्यथा
		reg &= ~ISPCSI2_CTRL_ECC_EN;

	isp_reg_ग_लिखोl(isp, reg, csi2->regs1, ISPCSI2_CTRL);
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
	MEDIA_BUS_FMT_YUYV8_2X8,
पूर्ण;

/* To set the क्रमmat on the CSI2 requires a mapping function that takes
 * the following inमाला_दो:
 * - 3 dअगरferent क्रमmats (at this समय)
 * - 2 destinations (mem, vp+mem) (vp only handled separately)
 * - 2 decompression options (on, off)
 * - 2 isp revisions (certain क्रमmat must be handled dअगरferently on OMAP3630)
 * Output should be CSI2 frame क्रमmat code
 * Array indices as follows: [क्रमmat][dest][decompr][is_3630]
 * Not all combinations are valid. 0 means invalid.
 */
अटल स्थिर u16 __csi2_fmt_map[3][2][2][2] = अणु
	/* RAW10 क्रमmats */
	अणु
		/* Output to memory */
		अणु
			/* No DPCM decompression */
			अणु CSI2_PIX_FMT_RAW10_EXP16, CSI2_PIX_FMT_RAW10_EXP16 पूर्ण,
			/* DPCM decompression */
			अणु 0, 0 पूर्ण,
		पूर्ण,
		/* Output to both */
		अणु
			/* No DPCM decompression */
			अणु CSI2_PIX_FMT_RAW10_EXP16_VP,
			  CSI2_PIX_FMT_RAW10_EXP16_VP पूर्ण,
			/* DPCM decompression */
			अणु 0, 0 पूर्ण,
		पूर्ण,
	पूर्ण,
	/* RAW10 DPCM8 क्रमmats */
	अणु
		/* Output to memory */
		अणु
			/* No DPCM decompression */
			अणु CSI2_PIX_FMT_RAW8, CSI2_USERDEF_8BIT_DATA1 पूर्ण,
			/* DPCM decompression */
			अणु CSI2_PIX_FMT_RAW8_DPCM10_EXP16,
			  CSI2_USERDEF_8BIT_DATA1_DPCM10 पूर्ण,
		पूर्ण,
		/* Output to both */
		अणु
			/* No DPCM decompression */
			अणु CSI2_PIX_FMT_RAW8_VP,
			  CSI2_PIX_FMT_RAW8_VP पूर्ण,
			/* DPCM decompression */
			अणु CSI2_PIX_FMT_RAW8_DPCM10_VP,
			  CSI2_USERDEF_8BIT_DATA1_DPCM10_VP पूर्ण,
		पूर्ण,
	पूर्ण,
	/* YUYV8 2X8 क्रमmats */
	अणु
		/* Output to memory */
		अणु
			/* No DPCM decompression */
			अणु CSI2_PIX_FMT_YUV422_8BIT,
			  CSI2_PIX_FMT_YUV422_8BIT पूर्ण,
			/* DPCM decompression */
			अणु 0, 0 पूर्ण,
		पूर्ण,
		/* Output to both */
		अणु
			/* No DPCM decompression */
			अणु CSI2_PIX_FMT_YUV422_8BIT_VP,
			  CSI2_PIX_FMT_YUV422_8BIT_VP पूर्ण,
			/* DPCM decompression */
			अणु 0, 0 पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * csi2_ctx_map_क्रमmat - Map CSI2 sink media bus क्रमmat to CSI2 क्रमmat ID
 * @csi2: ISP CSI2 device
 *
 * Returns CSI2 physical क्रमmat id
 */
अटल u16 csi2_ctx_map_क्रमmat(काष्ठा isp_csi2_device *csi2)
अणु
	स्थिर काष्ठा v4l2_mbus_framefmt *fmt = &csi2->क्रमmats[CSI2_PAD_SINK];
	पूर्णांक fmtidx, destidx, is_3630;

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
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
		fmtidx = 2;
		अवरोध;
	शेष:
		WARN(1, KERN_ERR "CSI2: pixel format %08x unsupported!\n",
		     fmt->code);
		वापस 0;
	पूर्ण

	अगर (!(csi2->output & CSI2_OUTPUT_CCDC) &&
	    !(csi2->output & CSI2_OUTPUT_MEMORY)) अणु
		/* Neither output enabled is a valid combination */
		वापस CSI2_PIX_FMT_OTHERS;
	पूर्ण

	/* If we need to skip frames at the beginning of the stream disable the
	 * video port to aव्योम sending the skipped frames to the CCDC.
	 */
	destidx = csi2->frame_skip ? 0 : !!(csi2->output & CSI2_OUTPUT_CCDC);
	is_3630 = csi2->isp->revision == ISP_REVISION_15_0;

	वापस __csi2_fmt_map[fmtidx][destidx][csi2->dpcm_decompress][is_3630];
पूर्ण

/*
 * csi2_set_outaddr - Set memory address to save output image
 * @csi2: Poपूर्णांकer to ISP CSI2a device.
 * @addr: ISP MMU Mapped 32-bit memory address aligned on 32 byte boundary.
 *
 * Sets the memory address where the output will be saved.
 *
 * Returns 0 अगर successful, or -EINVAL अगर the address is not in the 32 byte
 * boundary.
 */
अटल व्योम csi2_set_outaddr(काष्ठा isp_csi2_device *csi2, u32 addr)
अणु
	काष्ठा isp_device *isp = csi2->isp;
	काष्ठा isp_csi2_ctx_cfg *ctx = &csi2->contexts[0];

	ctx->ping_addr = addr;
	ctx->pong_addr = addr;
	isp_reg_ग_लिखोl(isp, ctx->ping_addr,
		       csi2->regs1, ISPCSI2_CTX_DAT_PING_ADDR(ctx->ctxnum));
	isp_reg_ग_लिखोl(isp, ctx->pong_addr,
		       csi2->regs1, ISPCSI2_CTX_DAT_PONG_ADDR(ctx->ctxnum));
पूर्ण

/*
 * is_usr_def_mapping - Checks whether USER_DEF_MAPPING should
 *			be enabled by CSI2.
 * @क्रमmat_id: mapped क्रमmat id
 *
 */
अटल अंतरभूत पूर्णांक is_usr_def_mapping(u32 क्रमmat_id)
अणु
	वापस (क्रमmat_id & 0x40) ? 1 : 0;
पूर्ण

/*
 * csi2_ctx_enable - Enable specअगरied CSI2 context
 * @ctxnum: Context number, valid between 0 and 7 values.
 * @enable: enable
 *
 */
अटल व्योम csi2_ctx_enable(काष्ठा isp_device *isp,
			    काष्ठा isp_csi2_device *csi2, u8 ctxnum, u8 enable)
अणु
	काष्ठा isp_csi2_ctx_cfg *ctx = &csi2->contexts[ctxnum];
	अचिन्हित पूर्णांक skip = 0;
	u32 reg;

	reg = isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_CTX_CTRL1(ctxnum));

	अगर (enable) अणु
		अगर (csi2->frame_skip)
			skip = csi2->frame_skip;
		अन्यथा अगर (csi2->output & CSI2_OUTPUT_MEMORY)
			skip = 1;

		reg &= ~ISPCSI2_CTX_CTRL1_COUNT_MASK;
		reg |= ISPCSI2_CTX_CTRL1_COUNT_UNLOCK
		    |  (skip << ISPCSI2_CTX_CTRL1_COUNT_SHIFT)
		    |  ISPCSI2_CTX_CTRL1_CTX_EN;
	पूर्ण अन्यथा अणु
		reg &= ~ISPCSI2_CTX_CTRL1_CTX_EN;
	पूर्ण

	isp_reg_ग_लिखोl(isp, reg, csi2->regs1, ISPCSI2_CTX_CTRL1(ctxnum));
	ctx->enabled = enable;
पूर्ण

/*
 * csi2_ctx_config - CSI2 context configuration.
 * @ctx: context configuration
 *
 */
अटल व्योम csi2_ctx_config(काष्ठा isp_device *isp,
			    काष्ठा isp_csi2_device *csi2,
			    काष्ठा isp_csi2_ctx_cfg *ctx)
अणु
	u32 reg;

	/* Set up CSI2_CTx_CTRL1 */
	reg = isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_CTX_CTRL1(ctx->ctxnum));

	अगर (ctx->eof_enabled)
		reg |= ISPCSI2_CTX_CTRL1_खातापूर्ण_EN;
	अन्यथा
		reg &= ~ISPCSI2_CTX_CTRL1_खातापूर्ण_EN;

	अगर (ctx->eol_enabled)
		reg |= ISPCSI2_CTX_CTRL1_EOL_EN;
	अन्यथा
		reg &= ~ISPCSI2_CTX_CTRL1_EOL_EN;

	अगर (ctx->checksum_enabled)
		reg |= ISPCSI2_CTX_CTRL1_CS_EN;
	अन्यथा
		reg &= ~ISPCSI2_CTX_CTRL1_CS_EN;

	isp_reg_ग_लिखोl(isp, reg, csi2->regs1, ISPCSI2_CTX_CTRL1(ctx->ctxnum));

	/* Set up CSI2_CTx_CTRL2 */
	reg = isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_CTX_CTRL2(ctx->ctxnum));

	reg &= ~(ISPCSI2_CTX_CTRL2_VIRTUAL_ID_MASK);
	reg |= ctx->भव_id << ISPCSI2_CTX_CTRL2_VIRTUAL_ID_SHIFT;

	reg &= ~(ISPCSI2_CTX_CTRL2_FORMAT_MASK);
	reg |= ctx->क्रमmat_id << ISPCSI2_CTX_CTRL2_FORMAT_SHIFT;

	अगर (ctx->dpcm_decompress) अणु
		अगर (ctx->dpcm_predictor)
			reg |= ISPCSI2_CTX_CTRL2_DPCM_PRED;
		अन्यथा
			reg &= ~ISPCSI2_CTX_CTRL2_DPCM_PRED;
	पूर्ण

	अगर (is_usr_def_mapping(ctx->क्रमmat_id)) अणु
		reg &= ~ISPCSI2_CTX_CTRL2_USER_DEF_MAP_MASK;
		reg |= 2 << ISPCSI2_CTX_CTRL2_USER_DEF_MAP_SHIFT;
	पूर्ण

	isp_reg_ग_लिखोl(isp, reg, csi2->regs1, ISPCSI2_CTX_CTRL2(ctx->ctxnum));

	/* Set up CSI2_CTx_CTRL3 */
	reg = isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_CTX_CTRL3(ctx->ctxnum));
	reg &= ~(ISPCSI2_CTX_CTRL3_ALPHA_MASK);
	reg |= (ctx->alpha << ISPCSI2_CTX_CTRL3_ALPHA_SHIFT);

	isp_reg_ग_लिखोl(isp, reg, csi2->regs1, ISPCSI2_CTX_CTRL3(ctx->ctxnum));

	/* Set up CSI2_CTx_DAT_OFST */
	reg = isp_reg_पढ़ोl(isp, csi2->regs1,
			    ISPCSI2_CTX_DAT_OFST(ctx->ctxnum));
	reg &= ~ISPCSI2_CTX_DAT_OFST_OFST_MASK;
	reg |= ctx->data_offset << ISPCSI2_CTX_DAT_OFST_OFST_SHIFT;
	isp_reg_ग_लिखोl(isp, reg, csi2->regs1,
		       ISPCSI2_CTX_DAT_OFST(ctx->ctxnum));

	isp_reg_ग_लिखोl(isp, ctx->ping_addr,
		       csi2->regs1, ISPCSI2_CTX_DAT_PING_ADDR(ctx->ctxnum));

	isp_reg_ग_लिखोl(isp, ctx->pong_addr,
		       csi2->regs1, ISPCSI2_CTX_DAT_PONG_ADDR(ctx->ctxnum));
पूर्ण

/*
 * csi2_timing_config - CSI2 timing configuration.
 * @timing: csi2_timing_cfg काष्ठाure
 */
अटल व्योम csi2_timing_config(काष्ठा isp_device *isp,
			       काष्ठा isp_csi2_device *csi2,
			       काष्ठा isp_csi2_timing_cfg *timing)
अणु
	u32 reg;

	reg = isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_TIMING);

	अगर (timing->क्रमce_rx_mode)
		reg |= ISPCSI2_TIMING_FORCE_RX_MODE_IO(timing->ionum);
	अन्यथा
		reg &= ~ISPCSI2_TIMING_FORCE_RX_MODE_IO(timing->ionum);

	अगर (timing->stop_state_16x)
		reg |= ISPCSI2_TIMING_STOP_STATE_X16_IO(timing->ionum);
	अन्यथा
		reg &= ~ISPCSI2_TIMING_STOP_STATE_X16_IO(timing->ionum);

	अगर (timing->stop_state_4x)
		reg |= ISPCSI2_TIMING_STOP_STATE_X4_IO(timing->ionum);
	अन्यथा
		reg &= ~ISPCSI2_TIMING_STOP_STATE_X4_IO(timing->ionum);

	reg &= ~ISPCSI2_TIMING_STOP_STATE_COUNTER_IO_MASK(timing->ionum);
	reg |= timing->stop_state_counter <<
	       ISPCSI2_TIMING_STOP_STATE_COUNTER_IO_SHIFT(timing->ionum);

	isp_reg_ग_लिखोl(isp, reg, csi2->regs1, ISPCSI2_TIMING);
पूर्ण

/*
 * csi2_irq_ctx_set - Enables CSI2 Context IRQs.
 * @enable: Enable/disable CSI2 Context पूर्णांकerrupts
 */
अटल व्योम csi2_irq_ctx_set(काष्ठा isp_device *isp,
			     काष्ठा isp_csi2_device *csi2, पूर्णांक enable)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		isp_reg_ग_लिखोl(isp, ISPCSI2_CTX_IRQSTATUS_FE_IRQ, csi2->regs1,
			       ISPCSI2_CTX_IRQSTATUS(i));
		अगर (enable)
			isp_reg_set(isp, csi2->regs1, ISPCSI2_CTX_IRQENABLE(i),
				    ISPCSI2_CTX_IRQSTATUS_FE_IRQ);
		अन्यथा
			isp_reg_clr(isp, csi2->regs1, ISPCSI2_CTX_IRQENABLE(i),
				    ISPCSI2_CTX_IRQSTATUS_FE_IRQ);
	पूर्ण
पूर्ण

/*
 * csi2_irq_complexio1_set - Enables CSI2 ComplexIO IRQs.
 * @enable: Enable/disable CSI2 ComplexIO #1 पूर्णांकerrupts
 */
अटल व्योम csi2_irq_complexio1_set(काष्ठा isp_device *isp,
				    काष्ठा isp_csi2_device *csi2, पूर्णांक enable)
अणु
	u32 reg;
	reg = ISPCSI2_PHY_IRQENABLE_STATEALLULPMEXIT |
		ISPCSI2_PHY_IRQENABLE_STATEALLULPMENTER |
		ISPCSI2_PHY_IRQENABLE_STATEULPM5 |
		ISPCSI2_PHY_IRQENABLE_ERRCONTROL5 |
		ISPCSI2_PHY_IRQENABLE_ERRESC5 |
		ISPCSI2_PHY_IRQENABLE_ERRSOTSYNCHS5 |
		ISPCSI2_PHY_IRQENABLE_ERRSOTHS5 |
		ISPCSI2_PHY_IRQENABLE_STATEULPM4 |
		ISPCSI2_PHY_IRQENABLE_ERRCONTROL4 |
		ISPCSI2_PHY_IRQENABLE_ERRESC4 |
		ISPCSI2_PHY_IRQENABLE_ERRSOTSYNCHS4 |
		ISPCSI2_PHY_IRQENABLE_ERRSOTHS4 |
		ISPCSI2_PHY_IRQENABLE_STATEULPM3 |
		ISPCSI2_PHY_IRQENABLE_ERRCONTROL3 |
		ISPCSI2_PHY_IRQENABLE_ERRESC3 |
		ISPCSI2_PHY_IRQENABLE_ERRSOTSYNCHS3 |
		ISPCSI2_PHY_IRQENABLE_ERRSOTHS3 |
		ISPCSI2_PHY_IRQENABLE_STATEULPM2 |
		ISPCSI2_PHY_IRQENABLE_ERRCONTROL2 |
		ISPCSI2_PHY_IRQENABLE_ERRESC2 |
		ISPCSI2_PHY_IRQENABLE_ERRSOTSYNCHS2 |
		ISPCSI2_PHY_IRQENABLE_ERRSOTHS2 |
		ISPCSI2_PHY_IRQENABLE_STATEULPM1 |
		ISPCSI2_PHY_IRQENABLE_ERRCONTROL1 |
		ISPCSI2_PHY_IRQENABLE_ERRESC1 |
		ISPCSI2_PHY_IRQENABLE_ERRSOTSYNCHS1 |
		ISPCSI2_PHY_IRQENABLE_ERRSOTHS1;
	isp_reg_ग_लिखोl(isp, reg, csi2->regs1, ISPCSI2_PHY_IRQSTATUS);
	अगर (enable)
		reg |= isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_PHY_IRQENABLE);
	अन्यथा
		reg = 0;
	isp_reg_ग_लिखोl(isp, reg, csi2->regs1, ISPCSI2_PHY_IRQENABLE);
पूर्ण

/*
 * csi2_irq_status_set - Enables CSI2 Status IRQs.
 * @enable: Enable/disable CSI2 Status पूर्णांकerrupts
 */
अटल व्योम csi2_irq_status_set(काष्ठा isp_device *isp,
				काष्ठा isp_csi2_device *csi2, पूर्णांक enable)
अणु
	u32 reg;
	reg = ISPCSI2_IRQSTATUS_OCP_ERR_IRQ |
		ISPCSI2_IRQSTATUS_SHORT_PACKET_IRQ |
		ISPCSI2_IRQSTATUS_ECC_CORRECTION_IRQ |
		ISPCSI2_IRQSTATUS_ECC_NO_CORRECTION_IRQ |
		ISPCSI2_IRQSTATUS_COMPLEXIO2_ERR_IRQ |
		ISPCSI2_IRQSTATUS_COMPLEXIO1_ERR_IRQ |
		ISPCSI2_IRQSTATUS_FIFO_OVF_IRQ |
		ISPCSI2_IRQSTATUS_CONTEXT(0);
	isp_reg_ग_लिखोl(isp, reg, csi2->regs1, ISPCSI2_IRQSTATUS);
	अगर (enable)
		reg |= isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_IRQENABLE);
	अन्यथा
		reg = 0;

	isp_reg_ग_लिखोl(isp, reg, csi2->regs1, ISPCSI2_IRQENABLE);
पूर्ण

/*
 * omap3isp_csi2_reset - Resets the CSI2 module.
 *
 * Must be called with the phy lock held.
 *
 * Returns 0 अगर successful, or -EBUSY अगर घातer command didn't respond.
 */
पूर्णांक omap3isp_csi2_reset(काष्ठा isp_csi2_device *csi2)
अणु
	काष्ठा isp_device *isp = csi2->isp;
	u8 soft_reset_retries = 0;
	u32 reg;
	पूर्णांक i;

	अगर (!csi2->available)
		वापस -ENODEV;

	अगर (csi2->phy->entity)
		वापस -EBUSY;

	isp_reg_set(isp, csi2->regs1, ISPCSI2_SYSCONFIG,
		    ISPCSI2_SYSCONFIG_SOFT_RESET);

	करो अणु
		reg = isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_SYSSTATUS) &
				    ISPCSI2_SYSSTATUS_RESET_DONE;
		अगर (reg == ISPCSI2_SYSSTATUS_RESET_DONE)
			अवरोध;
		soft_reset_retries++;
		अगर (soft_reset_retries < 5)
			udelay(100);
	पूर्ण जबतक (soft_reset_retries < 5);

	अगर (soft_reset_retries == 5) अणु
		dev_err(isp->dev, "CSI2: Soft reset try count exceeded!\n");
		वापस -EBUSY;
	पूर्ण

	अगर (isp->revision == ISP_REVISION_15_0)
		isp_reg_set(isp, csi2->regs1, ISPCSI2_PHY_CFG,
			    ISPCSI2_PHY_CFG_RESET_CTRL);

	i = 100;
	करो अणु
		reg = isp_reg_पढ़ोl(isp, csi2->phy->phy_regs, ISPCSIPHY_REG1)
		    & ISPCSIPHY_REG1_RESET_DONE_CTRLCLK;
		अगर (reg == ISPCSIPHY_REG1_RESET_DONE_CTRLCLK)
			अवरोध;
		udelay(100);
	पूर्ण जबतक (--i > 0);

	अगर (i == 0) अणु
		dev_err(isp->dev,
			"CSI2: Reset for CSI2_96M_FCLK domain Failed!\n");
		वापस -EBUSY;
	पूर्ण

	अगर (isp->स्वतःidle)
		isp_reg_clr_set(isp, csi2->regs1, ISPCSI2_SYSCONFIG,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_MASK |
				ISPCSI2_SYSCONFIG_AUTO_IDLE,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_SMART |
				((isp->revision == ISP_REVISION_15_0) ?
				 ISPCSI2_SYSCONFIG_AUTO_IDLE : 0));
	अन्यथा
		isp_reg_clr_set(isp, csi2->regs1, ISPCSI2_SYSCONFIG,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_MASK |
				ISPCSI2_SYSCONFIG_AUTO_IDLE,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_NO);

	वापस 0;
पूर्ण

अटल पूर्णांक csi2_configure(काष्ठा isp_csi2_device *csi2)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&csi2->subdev.entity);
	स्थिर काष्ठा isp_bus_cfg *buscfg;
	काष्ठा isp_device *isp = csi2->isp;
	काष्ठा isp_csi2_timing_cfg *timing = &csi2->timing[0];
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
	buscfg = v4l2_subdev_to_bus_cfg(pipe->बाह्यal);

	csi2->frame_skip = 0;
	v4l2_subdev_call(sensor, sensor, g_skip_frames, &csi2->frame_skip);

	csi2->ctrl.vp_out_ctrl =
		clamp_t(अचिन्हित पूर्णांक, pipe->l3_ick / pipe->बाह्यal_rate - 1,
			1, 3);
	dev_dbg(isp->dev, "%s: l3_ick %lu, external_rate %u, vp_out_ctrl %u\n",
		__func__, pipe->l3_ick,  pipe->बाह्यal_rate,
		csi2->ctrl.vp_out_ctrl);
	csi2->ctrl.frame_mode = ISP_CSI2_FRAME_IMMEDIATE;
	csi2->ctrl.ecc_enable = buscfg->bus.csi2.crc;

	timing->ionum = 1;
	timing->क्रमce_rx_mode = 1;
	timing->stop_state_16x = 1;
	timing->stop_state_4x = 1;
	timing->stop_state_counter = 0x1FF;

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

	csi2_irq_complexio1_set(isp, csi2, 1);
	csi2_irq_ctx_set(isp, csi2, 1);
	csi2_irq_status_set(isp, csi2, 1);

	/* Set configuration (timings, क्रमmat and links) */
	csi2_timing_config(isp, csi2, timing);
	csi2_recv_config(isp, csi2, &csi2->ctrl);
	csi2_ctx_config(isp, csi2, &csi2->contexts[0]);

	वापस 0;
पूर्ण

/*
 * csi2_prपूर्णांक_status - Prपूर्णांकs CSI2 debug inक्रमmation.
 */
#घोषणा CSI2_PRINT_REGISTER(isp, regs, name)\
	dev_dbg(isp->dev, "###CSI2 " #name "=0x%08x\n", \
		isp_reg_पढ़ोl(isp, regs, ISPCSI2_##name))

अटल व्योम csi2_prपूर्णांक_status(काष्ठा isp_csi2_device *csi2)
अणु
	काष्ठा isp_device *isp = csi2->isp;

	अगर (!csi2->available)
		वापस;

	dev_dbg(isp->dev, "-------------CSI2 Register dump-------------\n");

	CSI2_PRINT_REGISTER(isp, csi2->regs1, SYSCONFIG);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, SYSSTATUS);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, IRQENABLE);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, IRQSTATUS);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, CTRL);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, DBG_H);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, GNQ);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, PHY_CFG);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, PHY_IRQSTATUS);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, SHORT_PACKET);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, PHY_IRQENABLE);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, DBG_P);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, TIMING);
	CSI2_PRINT_REGISTER(isp, csi2->regs1, CTX_CTRL1(0));
	CSI2_PRINT_REGISTER(isp, csi2->regs1, CTX_CTRL2(0));
	CSI2_PRINT_REGISTER(isp, csi2->regs1, CTX_DAT_OFST(0));
	CSI2_PRINT_REGISTER(isp, csi2->regs1, CTX_DAT_PING_ADDR(0));
	CSI2_PRINT_REGISTER(isp, csi2->regs1, CTX_DAT_PONG_ADDR(0));
	CSI2_PRINT_REGISTER(isp, csi2->regs1, CTX_IRQENABLE(0));
	CSI2_PRINT_REGISTER(isp, csi2->regs1, CTX_IRQSTATUS(0));
	CSI2_PRINT_REGISTER(isp, csi2->regs1, CTX_CTRL3(0));

	dev_dbg(isp->dev, "--------------------------------------------\n");
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt handling
 */

/*
 * csi2_isr_buffer - Does buffer handling at end-of-frame
 * when writing to memory.
 */
अटल व्योम csi2_isr_buffer(काष्ठा isp_csi2_device *csi2)
अणु
	काष्ठा isp_device *isp = csi2->isp;
	काष्ठा isp_buffer *buffer;

	csi2_ctx_enable(isp, csi2, 0, 0);

	buffer = omap3isp_video_buffer_next(&csi2->video_out);

	/*
	 * Let video queue operation restart engine अगर there is an underrun
	 * condition.
	 */
	अगर (buffer == शून्य)
		वापस;

	csi2_set_outaddr(csi2, buffer->dma);
	csi2_ctx_enable(isp, csi2, 0, 1);
पूर्ण

अटल व्योम csi2_isr_ctx(काष्ठा isp_csi2_device *csi2,
			 काष्ठा isp_csi2_ctx_cfg *ctx)
अणु
	काष्ठा isp_device *isp = csi2->isp;
	अचिन्हित पूर्णांक n = ctx->ctxnum;
	u32 status;

	status = isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_CTX_IRQSTATUS(n));
	isp_reg_ग_लिखोl(isp, status, csi2->regs1, ISPCSI2_CTX_IRQSTATUS(n));

	अगर (!(status & ISPCSI2_CTX_IRQSTATUS_FE_IRQ))
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
			csi2_ctx_config(isp, csi2, ctx);
			csi2_ctx_enable(isp, csi2, n, 1);
		पूर्ण
		वापस;
	पूर्ण

	अगर (csi2->output & CSI2_OUTPUT_MEMORY)
		csi2_isr_buffer(csi2);
पूर्ण

/*
 * omap3isp_csi2_isr - CSI2 पूर्णांकerrupt handling.
 */
व्योम omap3isp_csi2_isr(काष्ठा isp_csi2_device *csi2)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&csi2->subdev.entity);
	u32 csi2_irqstatus, cpxio1_irqstatus;
	काष्ठा isp_device *isp = csi2->isp;

	अगर (!csi2->available)
		वापस;

	csi2_irqstatus = isp_reg_पढ़ोl(isp, csi2->regs1, ISPCSI2_IRQSTATUS);
	isp_reg_ग_लिखोl(isp, csi2_irqstatus, csi2->regs1, ISPCSI2_IRQSTATUS);

	/* Failure Cases */
	अगर (csi2_irqstatus & ISPCSI2_IRQSTATUS_COMPLEXIO1_ERR_IRQ) अणु
		cpxio1_irqstatus = isp_reg_पढ़ोl(isp, csi2->regs1,
						 ISPCSI2_PHY_IRQSTATUS);
		isp_reg_ग_लिखोl(isp, cpxio1_irqstatus,
			       csi2->regs1, ISPCSI2_PHY_IRQSTATUS);
		dev_dbg(isp->dev, "CSI2: ComplexIO Error IRQ %x\n",
			cpxio1_irqstatus);
		pipe->error = true;
	पूर्ण

	अगर (csi2_irqstatus & (ISPCSI2_IRQSTATUS_OCP_ERR_IRQ |
			      ISPCSI2_IRQSTATUS_SHORT_PACKET_IRQ |
			      ISPCSI2_IRQSTATUS_ECC_NO_CORRECTION_IRQ |
			      ISPCSI2_IRQSTATUS_COMPLEXIO2_ERR_IRQ |
			      ISPCSI2_IRQSTATUS_FIFO_OVF_IRQ)) अणु
		dev_dbg(isp->dev,
			"CSI2 Err: OCP:%d, Short_pack:%d, ECC:%d, CPXIO2:%d, FIFO_OVF:%d,\n",
			(csi2_irqstatus &
			 ISPCSI2_IRQSTATUS_OCP_ERR_IRQ) ? 1 : 0,
			(csi2_irqstatus &
			 ISPCSI2_IRQSTATUS_SHORT_PACKET_IRQ) ? 1 : 0,
			(csi2_irqstatus &
			 ISPCSI2_IRQSTATUS_ECC_NO_CORRECTION_IRQ) ? 1 : 0,
			(csi2_irqstatus &
			 ISPCSI2_IRQSTATUS_COMPLEXIO2_ERR_IRQ) ? 1 : 0,
			(csi2_irqstatus &
			 ISPCSI2_IRQSTATUS_FIFO_OVF_IRQ) ? 1 : 0);
		pipe->error = true;
	पूर्ण

	अगर (omap3isp_module_sync_is_stopping(&csi2->रुको, &csi2->stopping))
		वापस;

	/* Successful हालs */
	अगर (csi2_irqstatus & ISPCSI2_IRQSTATUS_CONTEXT(0))
		csi2_isr_ctx(csi2, &csi2->contexts[0]);

	अगर (csi2_irqstatus & ISPCSI2_IRQSTATUS_ECC_CORRECTION_IRQ)
		dev_dbg(isp->dev, "CSI2: ECC correction done\n");
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP video operations
 */

/*
 * csi2_queue - Queues the first buffer when using memory output
 * @video: The video node
 * @buffer: buffer to queue
 */
अटल पूर्णांक csi2_queue(काष्ठा isp_video *video, काष्ठा isp_buffer *buffer)
अणु
	काष्ठा isp_device *isp = video->isp;
	काष्ठा isp_csi2_device *csi2 = &isp->isp_csi2a;

	csi2_set_outaddr(csi2, buffer->dma);

	/*
	 * If streaming was enabled beक्रमe there was a buffer queued
	 * or underrun happened in the ISR, the hardware was not enabled
	 * and DMA queue flag ISP_VIDEO_DMAQUEUE_UNDERRUN is still set.
	 * Enable it now.
	 */
	अगर (csi2->video_out.dmaqueue_flags & ISP_VIDEO_DMAQUEUE_UNDERRUN) अणु
		/* Enable / disable context 0 and IRQs */
		csi2_अगर_enable(isp, csi2, 1);
		csi2_ctx_enable(isp, csi2, 0, 1);
		isp_video_dmaqueue_flags_clr(&csi2->video_out);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा isp_video_operations csi2_ispvideo_ops = अणु
	.queue = csi2_queue,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 */

अटल काष्ठा v4l2_mbus_framefmt *
__csi2_get_क्रमmat(काष्ठा isp_csi2_device *csi2, काष्ठा v4l2_subdev_pad_config *cfg,
		  अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&csi2->subdev, cfg, pad);
	अन्यथा
		वापस &csi2->क्रमmats[pad];
पूर्ण

अटल व्योम
csi2_try_क्रमmat(काष्ठा isp_csi2_device *csi2, काष्ठा v4l2_subdev_pad_config *cfg,
		अचिन्हित पूर्णांक pad, काष्ठा v4l2_mbus_framefmt *fmt,
		क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	u32 pixelcode;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	स्थिर काष्ठा isp_क्रमmat_info *info;
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
		info = omap3isp_video_क्रमmat_info(fmt->code);
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
 * @cfg: V4L2 subdev pad configuration
 * @code   : poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csi2_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा isp_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	स्थिर काष्ठा isp_क्रमmat_info *info;

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
			info = omap3isp_video_क्रमmat_info(क्रमmat->code);
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
	काष्ठा isp_csi2_device *csi2 = v4l2_get_subdevdata(sd);
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
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csi2_get_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा isp_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __csi2_get_क्रमmat(csi2, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;
	वापस 0;
पूर्ण

/*
 * csi2_set_क्रमmat - Handle set क्रमmat by pads subdev method
 * @sd : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @cfg: V4L2 subdev pad configuration
 * @fmt: poपूर्णांकer to v4l2 subdev क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
 */
अटल पूर्णांक csi2_set_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा isp_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __csi2_get_क्रमmat(csi2, cfg, fmt->pad, fmt->which);
	अगर (क्रमmat == शून्य)
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

/*
 * csi2_init_क्रमmats - Initialize क्रमmats on all pads
 * @sd: ISP CSI2 V4L2 subdevice
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
 * @sd: ISP CSI2 V4L2 subdevice
 * @enable: ISP pipeline stream state
 *
 * Return 0 on success or a negative error code otherwise.
 */
अटल पूर्णांक csi2_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा isp_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा isp_device *isp = csi2->isp;
	काष्ठा isp_video *video_out = &csi2->video_out;

	चयन (enable) अणु
	हाल ISP_PIPELINE_STREAM_CONTINUOUS:
		अगर (omap3isp_csiphy_acquire(csi2->phy, &sd->entity) < 0)
			वापस -ENODEV;
		अगर (csi2->output & CSI2_OUTPUT_MEMORY)
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_CSI2A_WRITE);
		csi2_configure(csi2);
		csi2_prपूर्णांक_status(csi2);

		/*
		 * When outputting to memory with no buffer available, let the
		 * buffer queue handler start the hardware. A DMA queue flag
		 * ISP_VIDEO_DMAQUEUE_QUEUED will be set as soon as there is
		 * a buffer available.
		 */
		अगर (csi2->output & CSI2_OUTPUT_MEMORY &&
		    !(video_out->dmaqueue_flags & ISP_VIDEO_DMAQUEUE_QUEUED))
			अवरोध;
		/* Enable context 0 and IRQs */
		atomic_set(&csi2->stopping, 0);
		csi2_ctx_enable(isp, csi2, 0, 1);
		csi2_अगर_enable(isp, csi2, 1);
		isp_video_dmaqueue_flags_clr(video_out);
		अवरोध;

	हाल ISP_PIPELINE_STREAM_STOPPED:
		अगर (csi2->state == ISP_PIPELINE_STREAM_STOPPED)
			वापस 0;
		अगर (omap3isp_module_sync_idle(&sd->entity, &csi2->रुको,
					      &csi2->stopping))
			dev_dbg(isp->dev, "%s: module stop timeout.\n",
				sd->name);
		csi2_ctx_enable(isp, csi2, 0, 0);
		csi2_अगर_enable(isp, csi2, 0);
		csi2_irq_ctx_set(isp, csi2, 0);
		omap3isp_csiphy_release(csi2->phy);
		isp_video_dmaqueue_flags_clr(video_out);
		omap3isp_sbl_disable(isp, OMAP3_ISP_SBL_CSI2A_WRITE);
		अवरोध;
	पूर्ण

	csi2->state = enable;
	वापस 0;
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
	काष्ठा isp_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा isp_csi2_ctrl_cfg *ctrl = &csi2->ctrl;
	अचिन्हित पूर्णांक index = local->index;

	/*
	 * The ISP core करोesn't support pipelines with multiple video outमाला_दो.
	 * Revisit this when it will be implemented, and वापस -EBUSY क्रम now.
	 */

	/* FIXME: this is actually a hack! */
	अगर (is_media_entity_v4l2_subdev(remote->entity))
		index |= 2 << 16;

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
			अगर (csi2->output & ~CSI2_OUTPUT_CCDC)
				वापस -EBUSY;
			csi2->output |= CSI2_OUTPUT_CCDC;
		पूर्ण अन्यथा अणु
			csi2->output &= ~CSI2_OUTPUT_CCDC;
		पूर्ण
		अवरोध;

	शेष:
		/* Link from camera to CSI2 is fixed... */
		वापस -EINVAL;
	पूर्ण

	ctrl->vp_only_enable =
		(csi2->output & CSI2_OUTPUT_MEMORY) ? false : true;
	ctrl->vp_clk_enable = !!(csi2->output & CSI2_OUTPUT_CCDC);

	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations csi2_media_ops = अणु
	.link_setup = csi2_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

व्योम omap3isp_csi2_unरेजिस्टर_entities(काष्ठा isp_csi2_device *csi2)
अणु
	v4l2_device_unरेजिस्टर_subdev(&csi2->subdev);
	omap3isp_video_unरेजिस्टर(&csi2->video_out);
पूर्ण

पूर्णांक omap3isp_csi2_रेजिस्टर_entities(काष्ठा isp_csi2_device *csi2,
				    काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	/* Register the subdev and video nodes. */
	csi2->subdev.dev = vdev->mdev->dev;
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &csi2->subdev);
	अगर (ret < 0)
		जाओ error;

	ret = omap3isp_video_रेजिस्टर(&csi2->video_out, vdev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	omap3isp_csi2_unरेजिस्टर_entities(csi2);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * ISP CSI2 initialisation and cleanup
 */

/*
 * csi2_init_entities - Initialize subdev and media entity.
 * @csi2: Poपूर्णांकer to csi2 काष्ठाure.
 * वापस -ENOMEM or zero on success
 */
अटल पूर्णांक csi2_init_entities(काष्ठा isp_csi2_device *csi2)
अणु
	काष्ठा v4l2_subdev *sd = &csi2->subdev;
	काष्ठा media_pad *pads = csi2->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	v4l2_subdev_init(sd, &csi2_ops);
	sd->पूर्णांकernal_ops = &csi2_पूर्णांकernal_ops;
	strscpy(sd->name, "OMAP3 ISP CSI2a", माप(sd->name));

	sd->grp_id = 1 << 16;	/* group ID क्रम isp subdevs */
	v4l2_set_subdevdata(sd, csi2);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[CSI2_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	pads[CSI2_PAD_SINK].flags = MEDIA_PAD_FL_SINK
				    | MEDIA_PAD_FL_MUST_CONNECT;

	me->ops = &csi2_media_ops;
	ret = media_entity_pads_init(me, CSI2_PADS_NUM, pads);
	अगर (ret < 0)
		वापस ret;

	csi2_init_क्रमmats(sd, शून्य);

	/* Video device node */
	csi2->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	csi2->video_out.ops = &csi2_ispvideo_ops;
	csi2->video_out.bpl_alignment = 32;
	csi2->video_out.bpl_zero_padding = 1;
	csi2->video_out.bpl_max = 0x1ffe0;
	csi2->video_out.isp = csi2->isp;
	csi2->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 3;

	ret = omap3isp_video_init(&csi2->video_out, "CSI2a");
	अगर (ret < 0)
		जाओ error_video;

	वापस 0;

error_video:
	media_entity_cleanup(&csi2->subdev.entity);
	वापस ret;
पूर्ण

/*
 * omap3isp_csi2_init - Routine क्रम module driver init
 */
पूर्णांक omap3isp_csi2_init(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_csi2_device *csi2a = &isp->isp_csi2a;
	काष्ठा isp_csi2_device *csi2c = &isp->isp_csi2c;
	पूर्णांक ret;

	csi2a->isp = isp;
	csi2a->available = 1;
	csi2a->regs1 = OMAP3_ISP_IOMEM_CSI2A_REGS1;
	csi2a->regs2 = OMAP3_ISP_IOMEM_CSI2A_REGS2;
	csi2a->phy = &isp->isp_csiphy2;
	csi2a->state = ISP_PIPELINE_STREAM_STOPPED;
	init_रुकोqueue_head(&csi2a->रुको);

	ret = csi2_init_entities(csi2a);
	अगर (ret < 0)
		वापस ret;

	अगर (isp->revision == ISP_REVISION_15_0) अणु
		csi2c->isp = isp;
		csi2c->available = 1;
		csi2c->regs1 = OMAP3_ISP_IOMEM_CSI2C_REGS1;
		csi2c->regs2 = OMAP3_ISP_IOMEM_CSI2C_REGS2;
		csi2c->phy = &isp->isp_csiphy1;
		csi2c->state = ISP_PIPELINE_STREAM_STOPPED;
		init_रुकोqueue_head(&csi2c->रुको);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * omap3isp_csi2_cleanup - Routine क्रम module driver cleanup
 */
व्योम omap3isp_csi2_cleanup(काष्ठा isp_device *isp)
अणु
	काष्ठा isp_csi2_device *csi2a = &isp->isp_csi2a;

	omap3isp_video_cleanup(&csi2a->video_out);
	media_entity_cleanup(&csi2a->subdev.entity);
पूर्ण
