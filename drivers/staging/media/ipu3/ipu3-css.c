<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Intel Corporation

#समावेश <linux/device.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/slab.h>

#समावेश "ipu3-css.h"
#समावेश "ipu3-css-fw.h"
#समावेश "ipu3-css-params.h"
#समावेश "ipu3-dmamap.h"
#समावेश "ipu3-tables.h"

/* IRQ configuration */
#घोषणा IMGU_IRQCTRL_IRQ_MASK	(IMGU_IRQCTRL_IRQ_SP1 | \
				 IMGU_IRQCTRL_IRQ_SP2 | \
				 IMGU_IRQCTRL_IRQ_SW_PIN(0) | \
				 IMGU_IRQCTRL_IRQ_SW_PIN(1))

#घोषणा IPU3_CSS_FORMAT_BPP_DEN	50	/* Denominator */

/* Some sane limits क्रम resolutions */
#घोषणा IPU3_CSS_MIN_RES	32
#घोषणा IPU3_CSS_MAX_H		3136
#घोषणा IPU3_CSS_MAX_W		4224

/* minimal envelope size(GDC in - out) should be 4 */
#घोषणा MIN_ENVELOPE            4

/*
 * pre-allocated buffer size क्रम CSS ABI, auxiliary frames
 * after BDS and beक्रमe GDC. Those values should be tuned
 * to big enough to aव्योम buffer re-allocation when
 * streaming to lower streaming latency.
 */
#घोषणा CSS_ABI_SIZE    136
#घोषणा CSS_BDS_SIZE    (4480 * 3200 * 3)
#घोषणा CSS_GDC_SIZE    (4224 * 3200 * 12 / 8)

#घोषणा IPU3_CSS_QUEUE_TO_FLAGS(q)	(1 << (q))
#घोषणा IPU3_CSS_FORMAT_FL_IN		\
			IPU3_CSS_QUEUE_TO_FLAGS(IPU3_CSS_QUEUE_IN)
#घोषणा IPU3_CSS_FORMAT_FL_OUT		\
			IPU3_CSS_QUEUE_TO_FLAGS(IPU3_CSS_QUEUE_OUT)
#घोषणा IPU3_CSS_FORMAT_FL_VF		\
			IPU3_CSS_QUEUE_TO_FLAGS(IPU3_CSS_QUEUE_VF)

/* Formats supported by IPU3 Camera Sub System */
अटल स्थिर काष्ठा imgu_css_क्रमmat imgu_css_क्रमmats[] = अणु
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_NV12,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.frame_क्रमmat = IMGU_ABI_FRAME_FORMAT_NV12,
		.osys_क्रमmat = IMGU_ABI_OSYS_FORMAT_NV12,
		.osys_tiling = IMGU_ABI_OSYS_TILING_NONE,
		.bytesperpixel_num = 1 * IPU3_CSS_FORMAT_BPP_DEN,
		.chroma_decim = 4,
		.width_align = IPU3_UAPI_ISP_VEC_ELEMS,
		.flags = IPU3_CSS_FORMAT_FL_OUT | IPU3_CSS_FORMAT_FL_VF,
	पूर्ण, अणु
		/* Each 32 bytes contains 25 10-bit pixels */
		.pixelक्रमmat = V4L2_PIX_FMT_IPU3_SBGGR10,
		.colorspace = V4L2_COLORSPACE_RAW,
		.frame_क्रमmat = IMGU_ABI_FRAME_FORMAT_RAW_PACKED,
		.bayer_order = IMGU_ABI_BAYER_ORDER_BGGR,
		.bit_depth = 10,
		.bytesperpixel_num = 64,
		.width_align = 2 * IPU3_UAPI_ISP_VEC_ELEMS,
		.flags = IPU3_CSS_FORMAT_FL_IN,
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_IPU3_SGBRG10,
		.colorspace = V4L2_COLORSPACE_RAW,
		.frame_क्रमmat = IMGU_ABI_FRAME_FORMAT_RAW_PACKED,
		.bayer_order = IMGU_ABI_BAYER_ORDER_GBRG,
		.bit_depth = 10,
		.bytesperpixel_num = 64,
		.width_align = 2 * IPU3_UAPI_ISP_VEC_ELEMS,
		.flags = IPU3_CSS_FORMAT_FL_IN,
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_IPU3_SGRBG10,
		.colorspace = V4L2_COLORSPACE_RAW,
		.frame_क्रमmat = IMGU_ABI_FRAME_FORMAT_RAW_PACKED,
		.bayer_order = IMGU_ABI_BAYER_ORDER_GRBG,
		.bit_depth = 10,
		.bytesperpixel_num = 64,
		.width_align = 2 * IPU3_UAPI_ISP_VEC_ELEMS,
		.flags = IPU3_CSS_FORMAT_FL_IN,
	पूर्ण, अणु
		.pixelक्रमmat = V4L2_PIX_FMT_IPU3_SRGGB10,
		.colorspace = V4L2_COLORSPACE_RAW,
		.frame_क्रमmat = IMGU_ABI_FRAME_FORMAT_RAW_PACKED,
		.bayer_order = IMGU_ABI_BAYER_ORDER_RGGB,
		.bit_depth = 10,
		.bytesperpixel_num = 64,
		.width_align = 2 * IPU3_UAPI_ISP_VEC_ELEMS,
		.flags = IPU3_CSS_FORMAT_FL_IN,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	क्रमागत imgu_abi_queue_id qid;
	माप_प्रकार ptr_ofs;
पूर्ण imgu_css_queues[IPU3_CSS_QUEUES] = अणु
	[IPU3_CSS_QUEUE_IN] = अणु
		IMGU_ABI_QUEUE_C_ID,
		दुरत्व(काष्ठा imgu_abi_buffer, payload.frame.frame_data)
	पूर्ण,
	[IPU3_CSS_QUEUE_OUT] = अणु
		IMGU_ABI_QUEUE_D_ID,
		दुरत्व(काष्ठा imgu_abi_buffer, payload.frame.frame_data)
	पूर्ण,
	[IPU3_CSS_QUEUE_VF] = अणु
		IMGU_ABI_QUEUE_E_ID,
		दुरत्व(काष्ठा imgu_abi_buffer, payload.frame.frame_data)
	पूर्ण,
	[IPU3_CSS_QUEUE_STAT_3A] = अणु
		IMGU_ABI_QUEUE_F_ID,
		दुरत्व(काष्ठा imgu_abi_buffer, payload.s3a.data_ptr)
	पूर्ण,
पूर्ण;

/* Initialize queue based on given क्रमmat, adjust क्रमmat as needed */
अटल पूर्णांक imgu_css_queue_init(काष्ठा imgu_css_queue *queue,
			       काष्ठा v4l2_pix_क्रमmat_mplane *fmt, u32 flags)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *स्थिर f = &queue->fmt.mpix;
	अचिन्हित पूर्णांक i;
	u32 sizeimage;

	INIT_LIST_HEAD(&queue->bufs);

	queue->css_fmt = शून्य;	/* Disable */
	अगर (!fmt)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(imgu_css_क्रमmats); i++) अणु
		अगर (!(imgu_css_क्रमmats[i].flags & flags))
			जारी;
		queue->css_fmt = &imgu_css_क्रमmats[i];
		अगर (imgu_css_क्रमmats[i].pixelक्रमmat == fmt->pixelक्रमmat)
			अवरोध;
	पूर्ण
	अगर (!queue->css_fmt)
		वापस -EINVAL;	/* Could not find any suitable क्रमmat */

	queue->fmt.mpix = *fmt;

	f->width = ALIGN(clamp_t(u32, f->width,
				 IPU3_CSS_MIN_RES, IPU3_CSS_MAX_W), 2);
	f->height = ALIGN(clamp_t(u32, f->height,
				  IPU3_CSS_MIN_RES, IPU3_CSS_MAX_H), 2);
	queue->width_pad = ALIGN(f->width, queue->css_fmt->width_align);
	अगर (queue->css_fmt->frame_क्रमmat != IMGU_ABI_FRAME_FORMAT_RAW_PACKED)
		f->plane_fmt[0].bytesperline = DIV_ROUND_UP(queue->width_pad *
					queue->css_fmt->bytesperpixel_num,
					IPU3_CSS_FORMAT_BPP_DEN);
	अन्यथा
		/* For packed raw, alignment क्रम bpl is by 50 to the width */
		f->plane_fmt[0].bytesperline =
				DIV_ROUND_UP(f->width,
					     IPU3_CSS_FORMAT_BPP_DEN) *
					     queue->css_fmt->bytesperpixel_num;

	sizeimage = f->height * f->plane_fmt[0].bytesperline;
	अगर (queue->css_fmt->chroma_decim)
		sizeimage += 2 * sizeimage / queue->css_fmt->chroma_decim;

	f->plane_fmt[0].sizeimage = sizeimage;
	f->field = V4L2_FIELD_NONE;
	f->num_planes = 1;
	f->colorspace = queue->css_fmt->colorspace;
	f->flags = 0;
	f->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	f->quantization = V4L2_QUANTIZATION_DEFAULT;
	f->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	स_रखो(f->reserved, 0, माप(f->reserved));

	वापस 0;
पूर्ण

अटल bool imgu_css_queue_enabled(काष्ठा imgu_css_queue *q)
अणु
	वापस q->css_fmt;
पूर्ण

/******************* css hw *******************/

/* In the style of ग_लिखोsl() defined in include/यंत्र-generic/पन.स */
अटल अंतरभूत व्योम ग_लिखोs(स्थिर व्योम *mem, sमाप_प्रकार count, व्योम __iomem *addr)
अणु
	अगर (count >= 4) अणु
		स्थिर u32 *buf = mem;

		count /= 4;
		करो अणु
			ग_लिखोl(*buf++, addr);
			addr += 4;
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण

/* Wait until रेजिस्टर `reg', masked with `mask', becomes `cmp' */
अटल पूर्णांक imgu_hw_रुको(व्योम __iomem *base, पूर्णांक reg, u32 mask, u32 cmp)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout(base + reg, val, (val & mask) == cmp,
				  1000, 100 * 1000);
पूर्ण

/* Initialize the IPU3 CSS hardware and associated h/w blocks */

पूर्णांक imgu_css_set_घातerup(काष्ठा device *dev, व्योम __iomem *base,
			 अचिन्हित पूर्णांक freq)
अणु
	u32 pm_ctrl, state, val;

	dev_dbg(dev, "%s with freq %u\n", __func__, freq);
	/* Clear the CSS busy संकेत */
	पढ़ोl(base + IMGU_REG_GP_BUSY);
	ग_लिखोl(0, base + IMGU_REG_GP_BUSY);

	/* Wait क्रम idle संकेत */
	अगर (imgu_hw_रुको(base, IMGU_REG_STATE, IMGU_STATE_IDLE_STS,
			 IMGU_STATE_IDLE_STS)) अणु
		dev_err(dev, "failed to set CSS idle\n");
		जाओ fail;
	पूर्ण

	/* Reset the css */
	ग_लिखोl(पढ़ोl(base + IMGU_REG_PM_CTRL) | IMGU_PM_CTRL_FORCE_RESET,
	       base + IMGU_REG_PM_CTRL);

	usleep_range(200, 300);

	/** Prepare CSS */

	pm_ctrl = पढ़ोl(base + IMGU_REG_PM_CTRL);
	state = पढ़ोl(base + IMGU_REG_STATE);

	dev_dbg(dev, "CSS pm_ctrl 0x%x state 0x%x (power %s)\n",
		pm_ctrl, state, state & IMGU_STATE_POWER_DOWN ? "down" : "up");

	/* Power up CSS using wrapper */
	अगर (state & IMGU_STATE_POWER_DOWN) अणु
		ग_लिखोl(IMGU_PM_CTRL_RACE_TO_HALT | IMGU_PM_CTRL_START,
		       base + IMGU_REG_PM_CTRL);
		अगर (imgu_hw_रुको(base, IMGU_REG_PM_CTRL,
				 IMGU_PM_CTRL_START, 0)) अणु
			dev_err(dev, "failed to power up CSS\n");
			जाओ fail;
		पूर्ण
		usleep_range(2000, 3000);
	पूर्ण अन्यथा अणु
		ग_लिखोl(IMGU_PM_CTRL_RACE_TO_HALT, base + IMGU_REG_PM_CTRL);
	पूर्ण

	/* Set the busy bit */
	ग_लिखोl(पढ़ोl(base + IMGU_REG_GP_BUSY) | 1, base + IMGU_REG_GP_BUSY);

	/* Set CSS घड़ी frequency */
	pm_ctrl = पढ़ोl(base + IMGU_REG_PM_CTRL);
	val = pm_ctrl & ~(IMGU_PM_CTRL_CSS_PWRDN | IMGU_PM_CTRL_RST_AT_खातापूर्ण);
	ग_लिखोl(val, base + IMGU_REG_PM_CTRL);
	ग_लिखोl(0, base + IMGU_REG_GP_BUSY);
	अगर (imgu_hw_रुको(base, IMGU_REG_STATE,
			 IMGU_STATE_PWRDNM_FSM_MASK, 0)) अणु
		dev_err(dev, "failed to pwrdn CSS\n");
		जाओ fail;
	पूर्ण
	val = (freq / IMGU_SYSTEM_REQ_FREQ_DIVIDER) & IMGU_SYSTEM_REQ_FREQ_MASK;
	ग_लिखोl(val, base + IMGU_REG_SYSTEM_REQ);
	ग_लिखोl(1, base + IMGU_REG_GP_BUSY);
	ग_लिखोl(पढ़ोl(base + IMGU_REG_PM_CTRL) | IMGU_PM_CTRL_FORCE_HALT,
	       base + IMGU_REG_PM_CTRL);
	अगर (imgu_hw_रुको(base, IMGU_REG_STATE, IMGU_STATE_HALT_STS,
			 IMGU_STATE_HALT_STS)) अणु
		dev_err(dev, "failed to halt CSS\n");
		जाओ fail;
	पूर्ण

	ग_लिखोl(पढ़ोl(base + IMGU_REG_PM_CTRL) | IMGU_PM_CTRL_START,
	       base + IMGU_REG_PM_CTRL);
	अगर (imgu_hw_रुको(base, IMGU_REG_PM_CTRL, IMGU_PM_CTRL_START, 0)) अणु
		dev_err(dev, "failed to start CSS\n");
		जाओ fail;
	पूर्ण
	ग_लिखोl(पढ़ोl(base + IMGU_REG_PM_CTRL) | IMGU_PM_CTRL_FORCE_UNHALT,
	       base + IMGU_REG_PM_CTRL);

	val = पढ़ोl(base + IMGU_REG_PM_CTRL);	/* get pm_ctrl */
	val &= ~(IMGU_PM_CTRL_CSS_PWRDN | IMGU_PM_CTRL_RST_AT_खातापूर्ण);
	val |= pm_ctrl & (IMGU_PM_CTRL_CSS_PWRDN | IMGU_PM_CTRL_RST_AT_खातापूर्ण);
	ग_लिखोl(val, base + IMGU_REG_PM_CTRL);

	वापस 0;

fail:
	imgu_css_set_घातerकरोwn(dev, base);
	वापस -EIO;
पूर्ण

व्योम imgu_css_set_घातerकरोwn(काष्ठा device *dev, व्योम __iomem *base)
अणु
	dev_dbg(dev, "%s\n", __func__);
	/* रुको क्रम cio idle संकेत */
	अगर (imgu_hw_रुको(base, IMGU_REG_CIO_GATE_BURST_STATE,
			 IMGU_CIO_GATE_BURST_MASK, 0))
		dev_warn(dev, "wait cio gate idle timeout");

	/* रुको क्रम css idle संकेत */
	अगर (imgu_hw_रुको(base, IMGU_REG_STATE, IMGU_STATE_IDLE_STS,
			 IMGU_STATE_IDLE_STS))
		dev_warn(dev, "wait css idle timeout\n");

	/* करो halt-halted handshake with css */
	ग_लिखोl(1, base + IMGU_REG_GP_HALT);
	अगर (imgu_hw_रुको(base, IMGU_REG_STATE, IMGU_STATE_HALT_STS,
			 IMGU_STATE_HALT_STS))
		dev_warn(dev, "failed to halt css");

	/* de-निश्चित the busy bit */
	ग_लिखोl(0, base + IMGU_REG_GP_BUSY);
पूर्ण

अटल व्योम imgu_css_hw_enable_irq(काष्ठा imgu_css *css)
अणु
	व्योम __iomem *स्थिर base = css->base;
	u32 val, i;

	/* Set up पूर्णांकerrupts */

	/*
	 * Enable IRQ on the SP which संकेतs that SP goes to idle
	 * (aka पढ़ोy state) and set trigger to pulse
	 */
	val = पढ़ोl(base + IMGU_REG_SP_CTRL(0)) | IMGU_CTRL_IRQ_READY;
	ग_लिखोl(val, base + IMGU_REG_SP_CTRL(0));
	ग_लिखोl(val | IMGU_CTRL_IRQ_CLEAR, base + IMGU_REG_SP_CTRL(0));

	/* Enable IRQs from the IMGU wrapper */
	ग_लिखोl(IMGU_REG_INT_CSS_IRQ, base + IMGU_REG_INT_ENABLE);
	/* Clear */
	ग_लिखोl(IMGU_REG_INT_CSS_IRQ, base + IMGU_REG_INT_STATUS);

	/* Enable IRQs from मुख्य IRQ controller */
	ग_लिखोl(~0, base + IMGU_REG_IRQCTRL_EDGE_NOT_PULSE(IMGU_IRQCTRL_MAIN));
	ग_लिखोl(0, base + IMGU_REG_IRQCTRL_MASK(IMGU_IRQCTRL_MAIN));
	ग_लिखोl(IMGU_IRQCTRL_IRQ_MASK,
	       base + IMGU_REG_IRQCTRL_EDGE(IMGU_IRQCTRL_MAIN));
	ग_लिखोl(IMGU_IRQCTRL_IRQ_MASK,
	       base + IMGU_REG_IRQCTRL_ENABLE(IMGU_IRQCTRL_MAIN));
	ग_लिखोl(IMGU_IRQCTRL_IRQ_MASK,
	       base + IMGU_REG_IRQCTRL_CLEAR(IMGU_IRQCTRL_MAIN));
	ग_लिखोl(IMGU_IRQCTRL_IRQ_MASK,
	       base + IMGU_REG_IRQCTRL_MASK(IMGU_IRQCTRL_MAIN));
	/* Wait क्रम ग_लिखो complete */
	पढ़ोl(base + IMGU_REG_IRQCTRL_ENABLE(IMGU_IRQCTRL_MAIN));

	/* Enable IRQs from SP0 and SP1 controllers */
	क्रम (i = IMGU_IRQCTRL_SP0; i <= IMGU_IRQCTRL_SP1; i++) अणु
		ग_लिखोl(~0, base + IMGU_REG_IRQCTRL_EDGE_NOT_PULSE(i));
		ग_लिखोl(0, base + IMGU_REG_IRQCTRL_MASK(i));
		ग_लिखोl(IMGU_IRQCTRL_IRQ_MASK, base + IMGU_REG_IRQCTRL_EDGE(i));
		ग_लिखोl(IMGU_IRQCTRL_IRQ_MASK,
		       base + IMGU_REG_IRQCTRL_ENABLE(i));
		ग_लिखोl(IMGU_IRQCTRL_IRQ_MASK, base + IMGU_REG_IRQCTRL_CLEAR(i));
		ग_लिखोl(IMGU_IRQCTRL_IRQ_MASK, base + IMGU_REG_IRQCTRL_MASK(i));
		/* Wait क्रम ग_लिखो complete */
		पढ़ोl(base + IMGU_REG_IRQCTRL_ENABLE(i));
	पूर्ण
पूर्ण

अटल पूर्णांक imgu_css_hw_init(काष्ठा imgu_css *css)
अणु
	/* For checking that streaming monitor statuses are valid */
	अटल स्थिर काष्ठा अणु
		u32 reg;
		u32 mask;
		स्थिर अक्षर *name;
	पूर्ण stream_monitors[] = अणु
		अणु
			IMGU_REG_GP_SP1_STRMON_STAT,
			IMGU_GP_STRMON_STAT_ISP_PORT_SP12ISP,
			"ISP0 to SP0"
		पूर्ण, अणु
			IMGU_REG_GP_ISP_STRMON_STAT,
			IMGU_GP_STRMON_STAT_SP1_PORT_ISP2SP1,
			"SP0 to ISP0"
		पूर्ण, अणु
			IMGU_REG_GP_MOD_STRMON_STAT,
			IMGU_GP_STRMON_STAT_MOD_PORT_ISP2DMA,
			"ISP0 to DMA0"
		पूर्ण, अणु
			IMGU_REG_GP_ISP_STRMON_STAT,
			IMGU_GP_STRMON_STAT_ISP_PORT_DMA2ISP,
			"DMA0 to ISP0"
		पूर्ण, अणु
			IMGU_REG_GP_MOD_STRMON_STAT,
			IMGU_GP_STRMON_STAT_MOD_PORT_CELLS2GDC,
			"ISP0 to GDC0"
		पूर्ण, अणु
			IMGU_REG_GP_MOD_STRMON_STAT,
			IMGU_GP_STRMON_STAT_MOD_PORT_GDC2CELLS,
			"GDC0 to ISP0"
		पूर्ण, अणु
			IMGU_REG_GP_MOD_STRMON_STAT,
			IMGU_GP_STRMON_STAT_MOD_PORT_SP12DMA,
			"SP0 to DMA0"
		पूर्ण, अणु
			IMGU_REG_GP_SP1_STRMON_STAT,
			IMGU_GP_STRMON_STAT_SP1_PORT_DMA2SP1,
			"DMA0 to SP0"
		पूर्ण, अणु
			IMGU_REG_GP_MOD_STRMON_STAT,
			IMGU_GP_STRMON_STAT_MOD_PORT_CELLS2GDC,
			"SP0 to GDC0"
		पूर्ण, अणु
			IMGU_REG_GP_MOD_STRMON_STAT,
			IMGU_GP_STRMON_STAT_MOD_PORT_GDC2CELLS,
			"GDC0 to SP0"
		पूर्ण,
	पूर्ण;

	काष्ठा device *dev = css->dev;
	व्योम __iomem *स्थिर base = css->base;
	u32 val, i;

	/* Set inकाष्ठाion cache address and inv bit क्रम ISP, SP, and SP1 */
	क्रम (i = 0; i < IMGU_NUM_SP; i++) अणु
		काष्ठा imgu_fw_info *bi =
					&css->fwp->binary_header[css->fw_sp[i]];

		ग_लिखोl(css->binary[css->fw_sp[i]].daddr,
		       base + IMGU_REG_SP_ICACHE_ADDR(bi->type));
		ग_लिखोl(पढ़ोl(base + IMGU_REG_SP_CTRL(bi->type)) |
		       IMGU_CTRL_ICACHE_INV,
		       base + IMGU_REG_SP_CTRL(bi->type));
	पूर्ण
	ग_लिखोl(css->binary[css->fw_bl].daddr, base + IMGU_REG_ISP_ICACHE_ADDR);
	ग_लिखोl(पढ़ोl(base + IMGU_REG_ISP_CTRL) | IMGU_CTRL_ICACHE_INV,
	       base + IMGU_REG_ISP_CTRL);

	/* Check that IMGU hardware is पढ़ोy */

	अगर (!(पढ़ोl(base + IMGU_REG_SP_CTRL(0)) & IMGU_CTRL_IDLE)) अणु
		dev_err(dev, "SP is not idle\n");
		वापस -EIO;
	पूर्ण
	अगर (!(पढ़ोl(base + IMGU_REG_ISP_CTRL) & IMGU_CTRL_IDLE)) अणु
		dev_err(dev, "ISP is not idle\n");
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(stream_monitors); i++) अणु
		val = पढ़ोl(base + stream_monitors[i].reg);
		अगर (val & stream_monitors[i].mask) अणु
			dev_err(dev, "error: Stream monitor %s is valid\n",
				stream_monitors[i].name);
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* Initialize GDC with शेष values */

	क्रम (i = 0; i < ARRAY_SIZE(imgu_css_gdc_lut[0]); i++) अणु
		u32 val0 = imgu_css_gdc_lut[0][i] & IMGU_GDC_LUT_MASK;
		u32 val1 = imgu_css_gdc_lut[1][i] & IMGU_GDC_LUT_MASK;
		u32 val2 = imgu_css_gdc_lut[2][i] & IMGU_GDC_LUT_MASK;
		u32 val3 = imgu_css_gdc_lut[3][i] & IMGU_GDC_LUT_MASK;

		ग_लिखोl(val0 | (val1 << 16),
		       base + IMGU_REG_GDC_LUT_BASE + i * 8);
		ग_लिखोl(val2 | (val3 << 16),
		       base + IMGU_REG_GDC_LUT_BASE + i * 8 + 4);
	पूर्ण

	वापस 0;
पूर्ण

/* Boot the given IPU3 CSS SP */
अटल पूर्णांक imgu_css_hw_start_sp(काष्ठा imgu_css *css, पूर्णांक sp)
अणु
	व्योम __iomem *स्थिर base = css->base;
	काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[css->fw_sp[sp]];
	काष्ठा imgu_abi_sp_init_dmem_cfg dmem_cfg = अणु
		.ddr_data_addr = css->binary[css->fw_sp[sp]].daddr
			+ bi->blob.data_source,
		.dmem_data_addr = bi->blob.data_target,
		.dmem_bss_addr = bi->blob.bss_target,
		.data_size = bi->blob.data_size,
		.bss_size = bi->blob.bss_size,
		.sp_id = sp,
	पूर्ण;

	ग_लिखोs(&dmem_cfg, माप(dmem_cfg), base +
	       IMGU_REG_SP_DMEM_BASE(sp) + bi->info.sp.init_dmem_data);

	ग_लिखोl(bi->info.sp.sp_entry, base + IMGU_REG_SP_START_ADDR(sp));

	ग_लिखोl(पढ़ोl(base + IMGU_REG_SP_CTRL(sp))
		| IMGU_CTRL_START | IMGU_CTRL_RUN, base + IMGU_REG_SP_CTRL(sp));

	अगर (imgu_hw_रुको(css->base, IMGU_REG_SP_DMEM_BASE(sp)
			 + bi->info.sp.sw_state,
			 ~0, IMGU_ABI_SP_SWSTATE_INITIALIZED))
		वापस -EIO;

	वापस 0;
पूर्ण

/* Start the IPU3 CSS ImgU (Imaging Unit) and all the SPs */
अटल पूर्णांक imgu_css_hw_start(काष्ठा imgu_css *css)
अणु
	अटल स्थिर u32 event_mask =
		((1 << IMGU_ABI_EVTTYPE_OUT_FRAME_DONE) |
		(1 << IMGU_ABI_EVTTYPE_2ND_OUT_FRAME_DONE) |
		(1 << IMGU_ABI_EVTTYPE_VF_OUT_FRAME_DONE) |
		(1 << IMGU_ABI_EVTTYPE_2ND_VF_OUT_FRAME_DONE) |
		(1 << IMGU_ABI_EVTTYPE_3A_STATS_DONE) |
		(1 << IMGU_ABI_EVTTYPE_DIS_STATS_DONE) |
		(1 << IMGU_ABI_EVTTYPE_PIPELINE_DONE) |
		(1 << IMGU_ABI_EVTTYPE_FRAME_TAGGED) |
		(1 << IMGU_ABI_EVTTYPE_INPUT_FRAME_DONE) |
		(1 << IMGU_ABI_EVTTYPE_METADATA_DONE) |
		(1 << IMGU_ABI_EVTTYPE_ACC_STAGE_COMPLETE))
		<< IMGU_ABI_SP_COMM_EVENT_IRQ_MASK_OR_SHIFT;

	व्योम __iomem *स्थिर base = css->base;
	काष्ठा imgu_fw_info *bi, *bl = &css->fwp->binary_header[css->fw_bl];
	अचिन्हित पूर्णांक i;

	ग_लिखोl(IMGU_TLB_INVALIDATE, base + IMGU_REG_TLB_INVALIDATE);

	/* Start bootloader */

	ग_लिखोl(IMGU_ABI_BL_SWSTATE_BUSY,
	       base + IMGU_REG_ISP_DMEM_BASE + bl->info.bl.sw_state);
	ग_लिखोl(IMGU_NUM_SP,
	       base + IMGU_REG_ISP_DMEM_BASE + bl->info.bl.num_dma_cmds);

	क्रम (i = 0; i < IMGU_NUM_SP; i++) अणु
		पूर्णांक j = IMGU_NUM_SP - i - 1;	/* load sp1 first, then sp0 */
		काष्ठा imgu_fw_info *sp =
					&css->fwp->binary_header[css->fw_sp[j]];
		काष्ठा imgu_abi_bl_dma_cmd_entry dma_cmd = अणु
			.src_addr = css->binary[css->fw_sp[j]].daddr
				+ sp->blob.text_source,
			.size = sp->blob.text_size,
			.dst_type = IMGU_ABI_BL_DMACMD_TYPE_SP_PMEM,
			.dst_addr = IMGU_SP_PMEM_BASE(j),
		पूर्ण;

		ग_लिखोs(&dma_cmd, माप(dma_cmd),
		       base + IMGU_REG_ISP_DMEM_BASE + i * माप(dma_cmd) +
		       bl->info.bl.dma_cmd_list);
	पूर्ण

	ग_लिखोl(bl->info.bl.bl_entry, base + IMGU_REG_ISP_START_ADDR);

	ग_लिखोl(पढ़ोl(base + IMGU_REG_ISP_CTRL)
		| IMGU_CTRL_START | IMGU_CTRL_RUN, base + IMGU_REG_ISP_CTRL);
	अगर (imgu_hw_रुको(css->base, IMGU_REG_ISP_DMEM_BASE
			 + bl->info.bl.sw_state, ~0,
			 IMGU_ABI_BL_SWSTATE_OK)) अणु
		dev_err(css->dev, "failed to start bootloader\n");
		वापस -EIO;
	पूर्ण

	/* Start ISP */

	स_रखो(css->xmem_sp_group_ptrs.vaddr, 0,
	       माप(काष्ठा imgu_abi_sp_group));

	bi = &css->fwp->binary_header[css->fw_sp[0]];

	ग_लिखोl(css->xmem_sp_group_ptrs.daddr,
	       base + IMGU_REG_SP_DMEM_BASE(0) + bi->info.sp.per_frame_data);

	ग_लिखोl(IMGU_ABI_SP_SWSTATE_TERMINATED,
	       base + IMGU_REG_SP_DMEM_BASE(0) + bi->info.sp.sw_state);
	ग_लिखोl(1, base + IMGU_REG_SP_DMEM_BASE(0) + bi->info.sp.invalidate_tlb);

	अगर (imgu_css_hw_start_sp(css, 0))
		वापस -EIO;

	ग_लिखोl(0, base + IMGU_REG_SP_DMEM_BASE(0) + bi->info.sp.isp_started);
	ग_लिखोl(0, base + IMGU_REG_SP_DMEM_BASE(0) +
		bi->info.sp.host_sp_queues_initialized);
	ग_लिखोl(0, base + IMGU_REG_SP_DMEM_BASE(0) + bi->info.sp.sleep_mode);
	ग_लिखोl(0, base + IMGU_REG_SP_DMEM_BASE(0) + bi->info.sp.invalidate_tlb);
	ग_लिखोl(IMGU_ABI_SP_COMM_COMMAND_READY, base + IMGU_REG_SP_DMEM_BASE(0)
		+ bi->info.sp.host_sp_com + IMGU_ABI_SP_COMM_COMMAND);

	/* Enable all events क्रम all queues */

	क्रम (i = 0; i < IPU3_CSS_PIPE_ID_NUM; i++)
		ग_लिखोl(event_mask, base + IMGU_REG_SP_DMEM_BASE(0)
			+ bi->info.sp.host_sp_com
			+ IMGU_ABI_SP_COMM_EVENT_IRQ_MASK(i));
	ग_लिखोl(1, base + IMGU_REG_SP_DMEM_BASE(0) +
		bi->info.sp.host_sp_queues_initialized);

	/* Start SP1 */

	bi = &css->fwp->binary_header[css->fw_sp[1]];

	ग_लिखोl(IMGU_ABI_SP_SWSTATE_TERMINATED,
	       base + IMGU_REG_SP_DMEM_BASE(1) + bi->info.sp.sw_state);

	अगर (imgu_css_hw_start_sp(css, 1))
		वापस -EIO;

	ग_लिखोl(IMGU_ABI_SP_COMM_COMMAND_READY, base + IMGU_REG_SP_DMEM_BASE(1)
		+ bi->info.sp.host_sp_com + IMGU_ABI_SP_COMM_COMMAND);

	वापस 0;
पूर्ण

अटल व्योम imgu_css_hw_stop(काष्ठा imgu_css *css)
अणु
	व्योम __iomem *स्थिर base = css->base;
	काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[css->fw_sp[0]];

	/* Stop fw */
	ग_लिखोl(IMGU_ABI_SP_COMM_COMMAND_TERMINATE,
	       base + IMGU_REG_SP_DMEM_BASE(0) +
	       bi->info.sp.host_sp_com + IMGU_ABI_SP_COMM_COMMAND);
	अगर (imgu_hw_रुको(css->base, IMGU_REG_SP_CTRL(0),
			 IMGU_CTRL_IDLE, IMGU_CTRL_IDLE))
		dev_err(css->dev, "wait sp0 idle timeout.\n");
	अगर (पढ़ोl(base + IMGU_REG_SP_DMEM_BASE(0) + bi->info.sp.sw_state) !=
		  IMGU_ABI_SP_SWSTATE_TERMINATED)
		dev_err(css->dev, "sp0 is not terminated.\n");
	अगर (imgu_hw_रुको(css->base, IMGU_REG_ISP_CTRL,
			 IMGU_CTRL_IDLE, IMGU_CTRL_IDLE))
		dev_err(css->dev, "wait isp idle timeout\n");
पूर्ण

अटल व्योम imgu_css_hw_cleanup(काष्ठा imgu_css *css)
अणु
	व्योम __iomem *स्थिर base = css->base;

	/** Reset CSS **/

	/* Clear the CSS busy संकेत */
	पढ़ोl(base + IMGU_REG_GP_BUSY);
	ग_लिखोl(0, base + IMGU_REG_GP_BUSY);

	/* Wait क्रम idle संकेत */
	अगर (imgu_hw_रुको(css->base, IMGU_REG_STATE, IMGU_STATE_IDLE_STS,
			 IMGU_STATE_IDLE_STS))
		dev_err(css->dev, "failed to shut down hw cleanly\n");

	/* Reset the css */
	ग_लिखोl(पढ़ोl(base + IMGU_REG_PM_CTRL) | IMGU_PM_CTRL_FORCE_RESET,
	       base + IMGU_REG_PM_CTRL);

	usleep_range(200, 300);
पूर्ण

अटल व्योम imgu_css_pipeline_cleanup(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा imgu_device *imgu = dev_get_drvdata(css->dev);
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	अचिन्हित पूर्णांक i;

	imgu_css_pool_cleanup(imgu, &css_pipe->pool.parameter_set_info);
	imgu_css_pool_cleanup(imgu, &css_pipe->pool.acc);
	imgu_css_pool_cleanup(imgu, &css_pipe->pool.gdc);
	imgu_css_pool_cleanup(imgu, &css_pipe->pool.obgrid);

	क्रम (i = 0; i < IMGU_ABI_NUM_MEMORIES; i++)
		imgu_css_pool_cleanup(imgu, &css_pipe->pool.binary_params_p[i]);
पूर्ण

/*
 * This function initializes various stages of the
 * IPU3 CSS ISP pipeline
 */
अटल पूर्णांक imgu_css_pipeline_init(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe)
अणु
	अटल स्थिर पूर्णांक BYPC = 2;	/* Bytes per component */
	अटल स्थिर काष्ठा imgu_abi_buffer_sp buffer_sp_init = अणु
		.buf_src = अणु.queue_id = IMGU_ABI_QUEUE_EVENT_IDपूर्ण,
		.buf_type = IMGU_ABI_BUFFER_TYPE_INVALID,
	पूर्ण;

	काष्ठा imgu_abi_isp_iterator_config *cfg_iter;
	काष्ठा imgu_abi_isp_ref_config *cfg_ref;
	काष्ठा imgu_abi_isp_dvs_config *cfg_dvs;
	काष्ठा imgu_abi_isp_tnr3_config *cfg_tnr;
	काष्ठा imgu_abi_isp_ref_dmem_state *cfg_ref_state;
	काष्ठा imgu_abi_isp_tnr3_dmem_state *cfg_tnr_state;

	स्थिर पूर्णांक stage = 0;
	अचिन्हित पूर्णांक i, j;

	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	काष्ठा imgu_css_queue *css_queue_in =
			&css_pipe->queue[IPU3_CSS_QUEUE_IN];
	काष्ठा imgu_css_queue *css_queue_out =
			&css_pipe->queue[IPU3_CSS_QUEUE_OUT];
	काष्ठा imgu_css_queue *css_queue_vf =
			&css_pipe->queue[IPU3_CSS_QUEUE_VF];
	स्थिर काष्ठा imgu_fw_info *bi =
			&css->fwp->binary_header[css_pipe->bindex];
	स्थिर अचिन्हित पूर्णांक stripes = bi->info.isp.sp.iterator.num_stripes;

	काष्ठा imgu_fw_config_memory_offsets *cofs = (व्योम *)css->fwp +
		bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_CONFIG];
	काष्ठा imgu_fw_state_memory_offsets *sofs = (व्योम *)css->fwp +
		bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_STATE];

	काष्ठा imgu_abi_isp_stage *isp_stage;
	काष्ठा imgu_abi_sp_stage *sp_stage;
	काष्ठा imgu_abi_sp_group *sp_group;
	काष्ठा imgu_abi_frames_sp *frames_sp;
	काष्ठा imgu_abi_frame_sp *frame_sp;
	काष्ठा imgu_abi_frame_sp_info *frame_sp_info;

	स्थिर अचिन्हित पूर्णांक bds_width_pad =
				ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].width,
				      2 * IPU3_UAPI_ISP_VEC_ELEMS);

	स्थिर क्रमागत imgu_abi_memories m0 = IMGU_ABI_MEM_ISP_DMEM0;
	क्रमागत imgu_abi_param_class cfg = IMGU_ABI_PARAM_CLASS_CONFIG;
	व्योम *vaddr = css_pipe->binary_params_cs[cfg - 1][m0].vaddr;

	काष्ठा imgu_device *imgu = dev_get_drvdata(css->dev);

	dev_dbg(css->dev, "%s for pipe %d", __func__, pipe);

	/* Configure iterator */

	cfg_iter = imgu_css_fw_pipeline_params(css, pipe, cfg, m0,
					       &cofs->dmem.iterator,
					       माप(*cfg_iter), vaddr);
	अगर (!cfg_iter)
		जाओ bad_firmware;

	frame_sp_info = &cfg_iter->input_info;
	frame_sp_info->res.width	= css_queue_in->fmt.mpix.width;
	frame_sp_info->res.height	= css_queue_in->fmt.mpix.height;
	frame_sp_info->padded_width	= css_queue_in->width_pad;
	frame_sp_info->क्रमmat		= css_queue_in->css_fmt->frame_क्रमmat;
	frame_sp_info->raw_bit_depth	= css_queue_in->css_fmt->bit_depth;
	frame_sp_info->raw_bayer_order	= css_queue_in->css_fmt->bayer_order;
	frame_sp_info->raw_type		= IMGU_ABI_RAW_TYPE_BAYER;

	frame_sp_info = &cfg_iter->पूर्णांकernal_info;
	frame_sp_info->res.width = css_pipe->rect[IPU3_CSS_RECT_BDS].width;
	frame_sp_info->res.height = css_pipe->rect[IPU3_CSS_RECT_BDS].height;
	frame_sp_info->padded_width	= bds_width_pad;
	frame_sp_info->क्रमmat		= css_queue_out->css_fmt->frame_क्रमmat;
	frame_sp_info->raw_bit_depth	= css_queue_out->css_fmt->bit_depth;
	frame_sp_info->raw_bayer_order	= css_queue_out->css_fmt->bayer_order;
	frame_sp_info->raw_type		= IMGU_ABI_RAW_TYPE_BAYER;

	frame_sp_info = &cfg_iter->output_info;
	frame_sp_info->res.width	= css_queue_out->fmt.mpix.width;
	frame_sp_info->res.height	= css_queue_out->fmt.mpix.height;
	frame_sp_info->padded_width	= css_queue_out->width_pad;
	frame_sp_info->क्रमmat		= css_queue_out->css_fmt->frame_क्रमmat;
	frame_sp_info->raw_bit_depth	= css_queue_out->css_fmt->bit_depth;
	frame_sp_info->raw_bayer_order	= css_queue_out->css_fmt->bayer_order;
	frame_sp_info->raw_type		= IMGU_ABI_RAW_TYPE_BAYER;

	frame_sp_info = &cfg_iter->vf_info;
	frame_sp_info->res.width	= css_queue_vf->fmt.mpix.width;
	frame_sp_info->res.height	= css_queue_vf->fmt.mpix.height;
	frame_sp_info->padded_width	= css_queue_vf->width_pad;
	frame_sp_info->क्रमmat		= css_queue_vf->css_fmt->frame_क्रमmat;
	frame_sp_info->raw_bit_depth	= css_queue_vf->css_fmt->bit_depth;
	frame_sp_info->raw_bayer_order	= css_queue_vf->css_fmt->bayer_order;
	frame_sp_info->raw_type		= IMGU_ABI_RAW_TYPE_BAYER;

	cfg_iter->dvs_envelope.width =
				css_pipe->rect[IPU3_CSS_RECT_ENVELOPE].width;
	cfg_iter->dvs_envelope.height =
				css_pipe->rect[IPU3_CSS_RECT_ENVELOPE].height;

	/* Configure reference (delay) frames */

	cfg_ref = imgu_css_fw_pipeline_params(css, pipe, cfg, m0,
					      &cofs->dmem.ref,
					      माप(*cfg_ref), vaddr);
	अगर (!cfg_ref)
		जाओ bad_firmware;

	cfg_ref->port_b.crop = 0;
	cfg_ref->port_b.elems = IMGU_ABI_ISP_DDR_WORD_BYTES / BYPC;
	cfg_ref->port_b.width =
		css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].width;
	cfg_ref->port_b.stride =
		css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].bytesperline;
	cfg_ref->width_a_over_b =
				IPU3_UAPI_ISP_VEC_ELEMS / cfg_ref->port_b.elems;
	cfg_ref->dvs_frame_delay = IPU3_CSS_AUX_FRAMES - 1;
	क्रम (i = 0; i < IPU3_CSS_AUX_FRAMES; i++) अणु
		cfg_ref->ref_frame_addr_y[i] =
			css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].mem[i].daddr;
		cfg_ref->ref_frame_addr_c[i] =
			css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].mem[i].daddr +
			css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].bytesperline *
			css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].height;
	पूर्ण
	क्रम (; i < IMGU_ABI_FRAMES_REF; i++) अणु
		cfg_ref->ref_frame_addr_y[i] = 0;
		cfg_ref->ref_frame_addr_c[i] = 0;
	पूर्ण

	/* Configure DVS (digital video stabilization) */

	cfg_dvs = imgu_css_fw_pipeline_params(css, pipe, cfg, m0,
					      &cofs->dmem.dvs, माप(*cfg_dvs),
					      vaddr);
	अगर (!cfg_dvs)
		जाओ bad_firmware;

	cfg_dvs->num_horizontal_blocks =
			ALIGN(DIV_ROUND_UP(css_pipe->rect[IPU3_CSS_RECT_GDC].width,
					   IMGU_DVS_BLOCK_W), 2);
	cfg_dvs->num_vertical_blocks =
			DIV_ROUND_UP(css_pipe->rect[IPU3_CSS_RECT_GDC].height,
				     IMGU_DVS_BLOCK_H);

	/* Configure TNR (temporal noise reduction) */

	अगर (css_pipe->pipe_id == IPU3_CSS_PIPE_ID_VIDEO) अणु
		cfg_tnr = imgu_css_fw_pipeline_params(css, pipe, cfg, m0,
						      &cofs->dmem.tnr3,
						      माप(*cfg_tnr),
						      vaddr);
		अगर (!cfg_tnr)
			जाओ bad_firmware;

		cfg_tnr->port_b.crop = 0;
		cfg_tnr->port_b.elems = IMGU_ABI_ISP_DDR_WORD_BYTES;
		cfg_tnr->port_b.width =
			css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].width;
		cfg_tnr->port_b.stride =
			css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].bytesperline;
		cfg_tnr->width_a_over_b =
			IPU3_UAPI_ISP_VEC_ELEMS / cfg_tnr->port_b.elems;
		cfg_tnr->frame_height =
			css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].height;
		cfg_tnr->delay_frame = IPU3_CSS_AUX_FRAMES - 1;
		क्रम (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
			cfg_tnr->frame_addr[i] =
				css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR]
					.mem[i].daddr;
		क्रम (; i < IMGU_ABI_FRAMES_TNR; i++)
			cfg_tnr->frame_addr[i] = 0;
	पूर्ण

	/* Configure ref dmem state parameters */

	cfg = IMGU_ABI_PARAM_CLASS_STATE;
	vaddr = css_pipe->binary_params_cs[cfg - 1][m0].vaddr;

	cfg_ref_state = imgu_css_fw_pipeline_params(css, pipe, cfg, m0,
						    &sofs->dmem.ref,
						    माप(*cfg_ref_state),
						    vaddr);
	अगर (!cfg_ref_state)
		जाओ bad_firmware;

	cfg_ref_state->ref_in_buf_idx = 0;
	cfg_ref_state->ref_out_buf_idx = 1;

	/* Configure tnr dmem state parameters */
	अगर (css_pipe->pipe_id == IPU3_CSS_PIPE_ID_VIDEO) अणु
		cfg_tnr_state =
			imgu_css_fw_pipeline_params(css, pipe, cfg, m0,
						    &sofs->dmem.tnr3,
						    माप(*cfg_tnr_state),
						    vaddr);
		अगर (!cfg_tnr_state)
			जाओ bad_firmware;

		cfg_tnr_state->in_bufidx = 0;
		cfg_tnr_state->out_bufidx = 1;
		cfg_tnr_state->bypass_filter = 0;
		cfg_tnr_state->total_frame_counter = 0;
		क्रम (i = 0; i < IMGU_ABI_BUF_SETS_TNR; i++)
			cfg_tnr_state->buffer_frame_counter[i] = 0;
	पूर्ण

	/* Configure ISP stage */

	isp_stage = css_pipe->xmem_isp_stage_ptrs[pipe][stage].vaddr;
	स_रखो(isp_stage, 0, माप(*isp_stage));
	isp_stage->blob_info = bi->blob;
	isp_stage->binary_info = bi->info.isp.sp;
	strscpy(isp_stage->binary_name,
		(अक्षर *)css->fwp + bi->blob.prog_name_offset,
		माप(isp_stage->binary_name));
	isp_stage->mem_initializers = bi->info.isp.sp.mem_initializers;
	क्रम (i = IMGU_ABI_PARAM_CLASS_CONFIG; i < IMGU_ABI_PARAM_CLASS_NUM; i++)
		क्रम (j = 0; j < IMGU_ABI_NUM_MEMORIES; j++)
			isp_stage->mem_initializers.params[i][j].address =
					css_pipe->binary_params_cs[i - 1][j].daddr;

	/* Configure SP stage */

	sp_stage = css_pipe->xmem_sp_stage_ptrs[pipe][stage].vaddr;
	स_रखो(sp_stage, 0, माप(*sp_stage));

	frames_sp = &sp_stage->frames;
	frames_sp->in.buf_attr = buffer_sp_init;
	क्रम (i = 0; i < IMGU_ABI_BINARY_MAX_OUTPUT_PORTS; i++)
		frames_sp->out[i].buf_attr = buffer_sp_init;
	frames_sp->out_vf.buf_attr = buffer_sp_init;
	frames_sp->s3a_buf = buffer_sp_init;
	frames_sp->dvs_buf = buffer_sp_init;

	sp_stage->stage_type = IMGU_ABI_STAGE_TYPE_ISP;
	sp_stage->num = stage;
	sp_stage->isp_online = 0;
	sp_stage->isp_copy_vf = 0;
	sp_stage->isp_copy_output = 0;

	sp_stage->enable.vf_output = css_pipe->vf_output_en;

	frames_sp->effective_in_res.width =
				css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].width;
	frames_sp->effective_in_res.height =
				css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].height;

	frame_sp = &frames_sp->in;
	frame_sp->info.res.width	= css_queue_in->fmt.mpix.width;
	frame_sp->info.res.height	= css_queue_in->fmt.mpix.height;
	frame_sp->info.padded_width	= css_queue_in->width_pad;
	frame_sp->info.क्रमmat		= css_queue_in->css_fmt->frame_क्रमmat;
	frame_sp->info.raw_bit_depth	= css_queue_in->css_fmt->bit_depth;
	frame_sp->info.raw_bayer_order	= css_queue_in->css_fmt->bayer_order;
	frame_sp->info.raw_type		= IMGU_ABI_RAW_TYPE_BAYER;
	frame_sp->buf_attr.buf_src.queue_id = IMGU_ABI_QUEUE_C_ID;
	frame_sp->buf_attr.buf_type	= IMGU_ABI_BUFFER_TYPE_INPUT_FRAME;

	frame_sp = &frames_sp->out[0];
	frame_sp->info.res.width	= css_queue_out->fmt.mpix.width;
	frame_sp->info.res.height	= css_queue_out->fmt.mpix.height;
	frame_sp->info.padded_width	= css_queue_out->width_pad;
	frame_sp->info.क्रमmat		= css_queue_out->css_fmt->frame_क्रमmat;
	frame_sp->info.raw_bit_depth	= css_queue_out->css_fmt->bit_depth;
	frame_sp->info.raw_bayer_order	= css_queue_out->css_fmt->bayer_order;
	frame_sp->info.raw_type		= IMGU_ABI_RAW_TYPE_BAYER;
	frame_sp->planes.nv.uv.offset	= css_queue_out->width_pad *
					  css_queue_out->fmt.mpix.height;
	frame_sp->buf_attr.buf_src.queue_id = IMGU_ABI_QUEUE_D_ID;
	frame_sp->buf_attr.buf_type	= IMGU_ABI_BUFFER_TYPE_OUTPUT_FRAME;

	frame_sp = &frames_sp->out[1];
	frame_sp->buf_attr.buf_src.queue_id = IMGU_ABI_QUEUE_EVENT_ID;

	frame_sp_info = &frames_sp->पूर्णांकernal_frame_info;
	frame_sp_info->res.width = css_pipe->rect[IPU3_CSS_RECT_BDS].width;
	frame_sp_info->res.height = css_pipe->rect[IPU3_CSS_RECT_BDS].height;
	frame_sp_info->padded_width	= bds_width_pad;
	frame_sp_info->क्रमmat		= css_queue_out->css_fmt->frame_क्रमmat;
	frame_sp_info->raw_bit_depth	= css_queue_out->css_fmt->bit_depth;
	frame_sp_info->raw_bayer_order	= css_queue_out->css_fmt->bayer_order;
	frame_sp_info->raw_type		= IMGU_ABI_RAW_TYPE_BAYER;

	frame_sp = &frames_sp->out_vf;
	frame_sp->info.res.width	= css_queue_vf->fmt.mpix.width;
	frame_sp->info.res.height	= css_queue_vf->fmt.mpix.height;
	frame_sp->info.padded_width	= css_queue_vf->width_pad;
	frame_sp->info.क्रमmat		= css_queue_vf->css_fmt->frame_क्रमmat;
	frame_sp->info.raw_bit_depth	= css_queue_vf->css_fmt->bit_depth;
	frame_sp->info.raw_bayer_order	= css_queue_vf->css_fmt->bayer_order;
	frame_sp->info.raw_type		= IMGU_ABI_RAW_TYPE_BAYER;
	frame_sp->planes.yuv.u.offset	= css_queue_vf->width_pad *
					  css_queue_vf->fmt.mpix.height;
	frame_sp->planes.yuv.v.offset	= css_queue_vf->width_pad *
					  css_queue_vf->fmt.mpix.height * 5 / 4;
	frame_sp->buf_attr.buf_src.queue_id = IMGU_ABI_QUEUE_E_ID;
	frame_sp->buf_attr.buf_type	= IMGU_ABI_BUFFER_TYPE_VF_OUTPUT_FRAME;

	frames_sp->s3a_buf.buf_src.queue_id = IMGU_ABI_QUEUE_F_ID;
	frames_sp->s3a_buf.buf_type	= IMGU_ABI_BUFFER_TYPE_3A_STATISTICS;

	frames_sp->dvs_buf.buf_src.queue_id = IMGU_ABI_QUEUE_G_ID;
	frames_sp->dvs_buf.buf_type	= IMGU_ABI_BUFFER_TYPE_DIS_STATISTICS;

	sp_stage->dvs_envelope.width =
				css_pipe->rect[IPU3_CSS_RECT_ENVELOPE].width;
	sp_stage->dvs_envelope.height =
				css_pipe->rect[IPU3_CSS_RECT_ENVELOPE].height;

	sp_stage->isp_pipe_version =
				bi->info.isp.sp.pipeline.isp_pipe_version;
	sp_stage->isp_deci_log_factor =
			clamp(max(fls(css_pipe->rect[IPU3_CSS_RECT_BDS].width /
				      IMGU_MAX_BQ_GRID_WIDTH),
				  fls(css_pipe->rect[IPU3_CSS_RECT_BDS].height /
				      IMGU_MAX_BQ_GRID_HEIGHT)) - 1, 3, 5);
	sp_stage->isp_vf_करोwnscale_bits = 0;
	sp_stage->अगर_config_index = 255;
	sp_stage->sp_enable_xnr = 0;
	sp_stage->num_stripes = stripes;
	sp_stage->enable.s3a = 1;
	sp_stage->enable.dvs_stats = 0;

	sp_stage->xmem_bin_addr = css->binary[css_pipe->bindex].daddr;
	sp_stage->xmem_map_addr = css_pipe->sp_ddr_ptrs.daddr;
	sp_stage->isp_stage_addr =
		css_pipe->xmem_isp_stage_ptrs[pipe][stage].daddr;

	/* Configure SP group */

	sp_group = css->xmem_sp_group_ptrs.vaddr;
	स_रखो(&sp_group->pipe[pipe], 0, माप(काष्ठा imgu_abi_sp_pipeline));

	sp_group->pipe[pipe].num_stages = 1;
	sp_group->pipe[pipe].pipe_id = css_pipe->pipe_id;
	sp_group->pipe[pipe].thपढ़ो_id = pipe;
	sp_group->pipe[pipe].pipe_num = pipe;
	sp_group->pipe[pipe].num_execs = -1;
	sp_group->pipe[pipe].pipe_qos_config = -1;
	sp_group->pipe[pipe].required_bds_factor = 0;
	sp_group->pipe[pipe].dvs_frame_delay = IPU3_CSS_AUX_FRAMES - 1;
	sp_group->pipe[pipe].inout_port_config =
					IMGU_ABI_PORT_CONFIG_TYPE_INPUT_HOST |
					IMGU_ABI_PORT_CONFIG_TYPE_OUTPUT_HOST;
	sp_group->pipe[pipe].scaler_pp_lut = 0;
	sp_group->pipe[pipe].shading.पूर्णांकernal_frame_origin_x_bqs_on_sctbl = 0;
	sp_group->pipe[pipe].shading.पूर्णांकernal_frame_origin_y_bqs_on_sctbl = 0;
	sp_group->pipe[pipe].sp_stage_addr[stage] =
			css_pipe->xmem_sp_stage_ptrs[pipe][stage].daddr;
	sp_group->pipe[pipe].pipe_config =
			bi->info.isp.sp.enable.params ? (1 << pipe) : 0;
	sp_group->pipe[pipe].pipe_config |= IMGU_ABI_PIPE_CONFIG_ACQUIRE_ISP;

	/* Initialize parameter pools */

	अगर (imgu_css_pool_init(imgu, &css_pipe->pool.parameter_set_info,
			       माप(काष्ठा imgu_abi_parameter_set_info)) ||
	    imgu_css_pool_init(imgu, &css_pipe->pool.acc,
			       माप(काष्ठा imgu_abi_acc_param)) ||
	    imgu_css_pool_init(imgu, &css_pipe->pool.gdc,
			       माप(काष्ठा imgu_abi_gdc_warp_param) *
			       3 * cfg_dvs->num_horizontal_blocks / 2 *
			       cfg_dvs->num_vertical_blocks) ||
	    imgu_css_pool_init(imgu, &css_pipe->pool.obgrid,
			       imgu_css_fw_obgrid_size(
			       &css->fwp->binary_header[css_pipe->bindex])))
		जाओ out_of_memory;

	क्रम (i = 0; i < IMGU_ABI_NUM_MEMORIES; i++)
		अगर (imgu_css_pool_init(imgu,
				       &css_pipe->pool.binary_params_p[i],
				       bi->info.isp.sp.mem_initializers.params
				       [IMGU_ABI_PARAM_CLASS_PARAM][i].size))
			जाओ out_of_memory;

	वापस 0;

bad_firmware:
	imgu_css_pipeline_cleanup(css, pipe);
	वापस -EPROTO;

out_of_memory:
	imgu_css_pipeline_cleanup(css, pipe);
	वापस -ENOMEM;
पूर्ण

अटल u8 imgu_css_queue_pos(काष्ठा imgu_css *css, पूर्णांक queue, पूर्णांक thपढ़ो)
अणु
	अटल स्थिर अचिन्हित पूर्णांक sp;
	व्योम __iomem *स्थिर base = css->base;
	काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[css->fw_sp[sp]];
	काष्ठा imgu_abi_queues __iomem *q = base + IMGU_REG_SP_DMEM_BASE(sp) +
						bi->info.sp.host_sp_queue;

	वापस queue >= 0 ? पढ़ोb(&q->host2sp_bufq_info[thपढ़ो][queue].end) :
			    पढ़ोb(&q->host2sp_evtq_info.end);
पूर्ण

/* Sent data to sp using given buffer queue, or अगर queue < 0, event queue. */
अटल पूर्णांक imgu_css_queue_data(काष्ठा imgu_css *css,
			       पूर्णांक queue, पूर्णांक thपढ़ो, u32 data)
अणु
	अटल स्थिर अचिन्हित पूर्णांक sp;
	व्योम __iomem *स्थिर base = css->base;
	काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[css->fw_sp[sp]];
	काष्ठा imgu_abi_queues __iomem *q = base + IMGU_REG_SP_DMEM_BASE(sp) +
						bi->info.sp.host_sp_queue;
	u8 size, start, end, end2;

	अगर (queue >= 0) अणु
		size = पढ़ोb(&q->host2sp_bufq_info[thपढ़ो][queue].size);
		start = पढ़ोb(&q->host2sp_bufq_info[thपढ़ो][queue].start);
		end = पढ़ोb(&q->host2sp_bufq_info[thपढ़ो][queue].end);
	पूर्ण अन्यथा अणु
		size = पढ़ोb(&q->host2sp_evtq_info.size);
		start = पढ़ोb(&q->host2sp_evtq_info.start);
		end = पढ़ोb(&q->host2sp_evtq_info.end);
	पूर्ण

	अगर (size == 0)
		वापस -EIO;

	end2 = (end + 1) % size;
	अगर (end2 == start)
		वापस -EBUSY;	/* Queue full */

	अगर (queue >= 0) अणु
		ग_लिखोl(data, &q->host2sp_bufq[thपढ़ो][queue][end]);
		ग_लिखोb(end2, &q->host2sp_bufq_info[thपढ़ो][queue].end);
	पूर्ण अन्यथा अणु
		ग_लिखोl(data, &q->host2sp_evtq[end]);
		ग_लिखोb(end2, &q->host2sp_evtq_info.end);
	पूर्ण

	वापस 0;
पूर्ण

/* Receive data using given buffer queue, or अगर queue < 0, event queue. */
अटल पूर्णांक imgu_css_dequeue_data(काष्ठा imgu_css *css, पूर्णांक queue, u32 *data)
अणु
	अटल स्थिर अचिन्हित पूर्णांक sp;
	व्योम __iomem *स्थिर base = css->base;
	काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[css->fw_sp[sp]];
	काष्ठा imgu_abi_queues __iomem *q = base + IMGU_REG_SP_DMEM_BASE(sp) +
						bi->info.sp.host_sp_queue;
	u8 size, start, end, start2;

	अगर (queue >= 0) अणु
		size = पढ़ोb(&q->sp2host_bufq_info[queue].size);
		start = पढ़ोb(&q->sp2host_bufq_info[queue].start);
		end = पढ़ोb(&q->sp2host_bufq_info[queue].end);
	पूर्ण अन्यथा अणु
		size = पढ़ोb(&q->sp2host_evtq_info.size);
		start = पढ़ोb(&q->sp2host_evtq_info.start);
		end = पढ़ोb(&q->sp2host_evtq_info.end);
	पूर्ण

	अगर (size == 0)
		वापस -EIO;

	अगर (end == start)
		वापस -EBUSY;	/* Queue empty */

	start2 = (start + 1) % size;

	अगर (queue >= 0) अणु
		*data = पढ़ोl(&q->sp2host_bufq[queue][start]);
		ग_लिखोb(start2, &q->sp2host_bufq_info[queue].start);
	पूर्ण अन्यथा अणु
		पूर्णांक r;

		*data = पढ़ोl(&q->sp2host_evtq[start]);
		ग_लिखोb(start2, &q->sp2host_evtq_info.start);

		/* Acknowledge events dequeued from event queue */
		r = imgu_css_queue_data(css, queue, 0,
					IMGU_ABI_EVENT_EVENT_DEQUEUED);
		अगर (r < 0)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/* Free binary-specअगरic resources */
अटल व्योम imgu_css_binary_cleanup(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा imgu_device *imgu = dev_get_drvdata(css->dev);
	अचिन्हित पूर्णांक i, j;

	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

	क्रम (j = 0; j < IMGU_ABI_PARAM_CLASS_NUM - 1; j++)
		क्रम (i = 0; i < IMGU_ABI_NUM_MEMORIES; i++)
			imgu_dmamap_मुक्त(imgu,
					 &css_pipe->binary_params_cs[j][i]);

	j = IPU3_CSS_AUX_FRAME_REF;
	क्रम (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
		imgu_dmamap_मुक्त(imgu,
				 &css_pipe->aux_frames[j].mem[i]);

	j = IPU3_CSS_AUX_FRAME_TNR;
	क्रम (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
		imgu_dmamap_मुक्त(imgu,
				 &css_pipe->aux_frames[j].mem[i]);
पूर्ण

अटल पूर्णांक imgu_css_binary_pपुनः_स्मृतिate(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा imgu_device *imgu = dev_get_drvdata(css->dev);
	अचिन्हित पूर्णांक i, j;

	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

	क्रम (j = IMGU_ABI_PARAM_CLASS_CONFIG;
	     j < IMGU_ABI_PARAM_CLASS_NUM; j++)
		क्रम (i = 0; i < IMGU_ABI_NUM_MEMORIES; i++)
			अगर (!imgu_dmamap_alloc(imgu,
					       &css_pipe->binary_params_cs[j - 1][i],
					       CSS_ABI_SIZE))
				जाओ out_of_memory;

	क्रम (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
		अगर (!imgu_dmamap_alloc(imgu,
				       &css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].
				       mem[i], CSS_BDS_SIZE))
			जाओ out_of_memory;

	क्रम (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
		अगर (!imgu_dmamap_alloc(imgu,
				       &css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].
				       mem[i], CSS_GDC_SIZE))
			जाओ out_of_memory;

	वापस 0;

out_of_memory:
	imgu_css_binary_cleanup(css, pipe);
	वापस -ENOMEM;
पूर्ण

/* allocate binary-specअगरic resources */
अटल पूर्णांक imgu_css_binary_setup(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[css_pipe->bindex];
	काष्ठा imgu_device *imgu = dev_get_drvdata(css->dev);
	पूर्णांक i, j, size;
	अटल स्थिर पूर्णांक BYPC = 2;	/* Bytes per component */
	अचिन्हित पूर्णांक w, h;

	/* Allocate parameter memory blocks क्रम this binary */

	क्रम (j = IMGU_ABI_PARAM_CLASS_CONFIG; j < IMGU_ABI_PARAM_CLASS_NUM; j++)
		क्रम (i = 0; i < IMGU_ABI_NUM_MEMORIES; i++) अणु
			अगर (imgu_css_dma_buffer_resize(
			    imgu,
			    &css_pipe->binary_params_cs[j - 1][i],
			    bi->info.isp.sp.mem_initializers.params[j][i].size))
				जाओ out_of_memory;
		पूर्ण

	/* Allocate पूर्णांकernal frame buffers */

	/* Reference frames क्रम DVS, FRAME_FORMAT_YUV420_16 */
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].bytesperpixel = BYPC;
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].width =
					css_pipe->rect[IPU3_CSS_RECT_BDS].width;
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].height =
				ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].height,
				      IMGU_DVS_BLOCK_H) + 2 * IMGU_GDC_BUF_Y;
	h = css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].height;
	w = ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].width,
		  2 * IPU3_UAPI_ISP_VEC_ELEMS) + 2 * IMGU_GDC_BUF_X;
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].bytesperline =
		css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].bytesperpixel * w;
	size = w * h * BYPC + (w / 2) * (h / 2) * BYPC * 2;
	क्रम (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
		अगर (imgu_css_dma_buffer_resize(
			imgu,
			&css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].mem[i],
			size))
			जाओ out_of_memory;

	/* TNR frames क्रम temporal noise reduction, FRAME_FORMAT_YUV_LINE */
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].bytesperpixel = 1;
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].width =
			roundup(css_pipe->rect[IPU3_CSS_RECT_GDC].width,
				bi->info.isp.sp.block.block_width *
				IPU3_UAPI_ISP_VEC_ELEMS);
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].height =
			roundup(css_pipe->rect[IPU3_CSS_RECT_GDC].height,
				bi->info.isp.sp.block.output_block_height);

	w = css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].width;
	css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].bytesperline = w;
	h = css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].height;
	size = w * ALIGN(h * 3 / 2 + 3, 2);	/* +3 क्रम vf_pp prefetch */
	क्रम (i = 0; i < IPU3_CSS_AUX_FRAMES; i++)
		अगर (imgu_css_dma_buffer_resize(
			imgu,
			&css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_TNR].mem[i],
			size))
			जाओ out_of_memory;

	वापस 0;

out_of_memory:
	imgu_css_binary_cleanup(css, pipe);
	वापस -ENOMEM;
पूर्ण

पूर्णांक imgu_css_start_streaming(काष्ठा imgu_css *css)
अणु
	u32 data;
	पूर्णांक r, pipe;

	अगर (css->streaming)
		वापस -EPROTO;

	क्रम_each_set_bit(pipe, css->enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		r = imgu_css_binary_setup(css, pipe);
		अगर (r < 0)
			वापस r;
	पूर्ण

	r = imgu_css_hw_init(css);
	अगर (r < 0)
		वापस r;

	r = imgu_css_hw_start(css);
	अगर (r < 0)
		जाओ fail;

	क्रम_each_set_bit(pipe, css->enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		r = imgu_css_pipeline_init(css, pipe);
		अगर (r < 0)
			जाओ fail;
	पूर्ण

	css->streaming = true;

	imgu_css_hw_enable_irq(css);

	/* Initialize parameters to शेष */
	क्रम_each_set_bit(pipe, css->enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		r = imgu_css_set_parameters(css, pipe, शून्य);
		अगर (r < 0)
			जाओ fail;
	पूर्ण

	जबतक (!(r = imgu_css_dequeue_data(css, IMGU_ABI_QUEUE_A_ID, &data)))
		;
	अगर (r != -EBUSY)
		जाओ fail;

	जबतक (!(r = imgu_css_dequeue_data(css, IMGU_ABI_QUEUE_B_ID, &data)))
		;
	अगर (r != -EBUSY)
		जाओ fail;

	क्रम_each_set_bit(pipe, css->enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		r = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe,
					IMGU_ABI_EVENT_START_STREAM |
					pipe << 16);
		अगर (r < 0)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	css->streaming = false;
	imgu_css_hw_cleanup(css);
	क्रम_each_set_bit(pipe, css->enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		imgu_css_pipeline_cleanup(css, pipe);
		imgu_css_binary_cleanup(css, pipe);
	पूर्ण

	वापस r;
पूर्ण

व्योम imgu_css_stop_streaming(काष्ठा imgu_css *css)
अणु
	काष्ठा imgu_css_buffer *b, *b0;
	पूर्णांक q, r, pipe;

	क्रम_each_set_bit(pipe, css->enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		r = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe,
					IMGU_ABI_EVENT_STOP_STREAM);
		अगर (r < 0)
			dev_warn(css->dev, "failed on stop stream event\n");
	पूर्ण

	अगर (!css->streaming)
		वापस;

	imgu_css_hw_stop(css);

	imgu_css_hw_cleanup(css);

	क्रम_each_set_bit(pipe, css->enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

		imgu_css_pipeline_cleanup(css, pipe);

		spin_lock(&css_pipe->qlock);
		क्रम (q = 0; q < IPU3_CSS_QUEUES; q++)
			list_क्रम_each_entry_safe(b, b0,
						 &css_pipe->queue[q].bufs,
						 list) अणु
				b->state = IPU3_CSS_BUFFER_FAILED;
				list_del(&b->list);
			पूर्ण
		spin_unlock(&css_pipe->qlock);
	पूर्ण

	css->streaming = false;
पूर्ण

bool imgu_css_pipe_queue_empty(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe)
अणु
	पूर्णांक q;
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

	spin_lock(&css_pipe->qlock);
	क्रम (q = 0; q < IPU3_CSS_QUEUES; q++)
		अगर (!list_empty(&css_pipe->queue[q].bufs))
			अवरोध;
	spin_unlock(&css_pipe->qlock);
	वापस (q == IPU3_CSS_QUEUES);
पूर्ण

bool imgu_css_queue_empty(काष्ठा imgu_css *css)
अणु
	अचिन्हित पूर्णांक pipe;
	bool ret = false;

	क्रम (pipe = 0; pipe < IMGU_MAX_PIPE_NUM; pipe++)
		ret &= imgu_css_pipe_queue_empty(css, pipe);

	वापस ret;
पूर्ण

bool imgu_css_is_streaming(काष्ठा imgu_css *css)
अणु
	वापस css->streaming;
पूर्ण

अटल पूर्णांक imgu_css_map_init(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा imgu_device *imgu = dev_get_drvdata(css->dev);
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	अचिन्हित पूर्णांक p, q, i;

	/* Allocate and map common काष्ठाures with imgu hardware */
	क्रम (p = 0; p < IPU3_CSS_PIPE_ID_NUM; p++)
		क्रम (i = 0; i < IMGU_ABI_MAX_STAGES; i++) अणु
			अगर (!imgu_dmamap_alloc(imgu,
					       &css_pipe->
					       xmem_sp_stage_ptrs[p][i],
					       माप(काष्ठा imgu_abi_sp_stage)))
				वापस -ENOMEM;
			अगर (!imgu_dmamap_alloc(imgu,
					       &css_pipe->
					       xmem_isp_stage_ptrs[p][i],
					       माप(काष्ठा imgu_abi_isp_stage)))
				वापस -ENOMEM;
		पूर्ण

	अगर (!imgu_dmamap_alloc(imgu, &css_pipe->sp_ddr_ptrs,
			       ALIGN(माप(काष्ठा imgu_abi_ddr_address_map),
				     IMGU_ABI_ISP_DDR_WORD_BYTES)))
		वापस -ENOMEM;

	क्रम (q = 0; q < IPU3_CSS_QUEUES; q++) अणु
		अचिन्हित पूर्णांक abi_buf_num = ARRAY_SIZE(css_pipe->abi_buffers[q]);

		क्रम (i = 0; i < abi_buf_num; i++)
			अगर (!imgu_dmamap_alloc(imgu,
					       &css_pipe->abi_buffers[q][i],
					       माप(काष्ठा imgu_abi_buffer)))
				वापस -ENOMEM;
	पूर्ण

	अगर (imgu_css_binary_pपुनः_स्मृतिate(css, pipe)) अणु
		imgu_css_binary_cleanup(css, pipe);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imgu_css_pipe_cleanup(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा imgu_device *imgu = dev_get_drvdata(css->dev);
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	अचिन्हित पूर्णांक p, q, i, abi_buf_num;

	imgu_css_binary_cleanup(css, pipe);

	क्रम (q = 0; q < IPU3_CSS_QUEUES; q++) अणु
		abi_buf_num = ARRAY_SIZE(css_pipe->abi_buffers[q]);
		क्रम (i = 0; i < abi_buf_num; i++)
			imgu_dmamap_मुक्त(imgu, &css_pipe->abi_buffers[q][i]);
	पूर्ण

	क्रम (p = 0; p < IPU3_CSS_PIPE_ID_NUM; p++)
		क्रम (i = 0; i < IMGU_ABI_MAX_STAGES; i++) अणु
			imgu_dmamap_मुक्त(imgu,
					 &css_pipe->xmem_sp_stage_ptrs[p][i]);
			imgu_dmamap_मुक्त(imgu,
					 &css_pipe->xmem_isp_stage_ptrs[p][i]);
		पूर्ण

	imgu_dmamap_मुक्त(imgu, &css_pipe->sp_ddr_ptrs);
पूर्ण

व्योम imgu_css_cleanup(काष्ठा imgu_css *css)
अणु
	काष्ठा imgu_device *imgu = dev_get_drvdata(css->dev);
	अचिन्हित पूर्णांक pipe;

	imgu_css_stop_streaming(css);
	क्रम (pipe = 0; pipe < IMGU_MAX_PIPE_NUM; pipe++)
		imgu_css_pipe_cleanup(css, pipe);
	imgu_dmamap_मुक्त(imgu, &css->xmem_sp_group_ptrs);
	imgu_css_fw_cleanup(css);
पूर्ण

पूर्णांक imgu_css_init(काष्ठा device *dev, काष्ठा imgu_css *css,
		  व्योम __iomem *base, पूर्णांक length)
अणु
	काष्ठा imgu_device *imgu = dev_get_drvdata(dev);
	पूर्णांक r, q, pipe;

	/* Initialize मुख्य data काष्ठाure */
	css->dev = dev;
	css->base = base;
	css->iomem_length = length;

	क्रम (pipe = 0; pipe < IMGU_MAX_PIPE_NUM; pipe++) अणु
		काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

		css_pipe->vf_output_en = false;
		spin_lock_init(&css_pipe->qlock);
		css_pipe->bindex = IPU3_CSS_DEFAULT_BINARY;
		css_pipe->pipe_id = IPU3_CSS_PIPE_ID_VIDEO;
		क्रम (q = 0; q < IPU3_CSS_QUEUES; q++) अणु
			r = imgu_css_queue_init(&css_pipe->queue[q], शून्य, 0);
			अगर (r)
				वापस r;
		पूर्ण
		r = imgu_css_map_init(css, pipe);
		अगर (r) अणु
			imgu_css_cleanup(css);
			वापस r;
		पूर्ण
	पूर्ण
	अगर (!imgu_dmamap_alloc(imgu, &css->xmem_sp_group_ptrs,
			       माप(काष्ठा imgu_abi_sp_group)))
		वापस -ENOMEM;

	r = imgu_css_fw_init(css);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल u32 imgu_css_adjust(u32 res, u32 align)
अणु
	u32 val = max_t(u32, IPU3_CSS_MIN_RES, res);

	वापस DIV_ROUND_CLOSEST(val, align) * align;
पूर्ण

/* Select a binary matching the required resolutions and क्रमmats */
अटल पूर्णांक imgu_css_find_binary(काष्ठा imgu_css *css,
				अचिन्हित पूर्णांक pipe,
				काष्ठा imgu_css_queue queue[IPU3_CSS_QUEUES],
				काष्ठा v4l2_rect rects[IPU3_CSS_RECTS])
अणु
	स्थिर पूर्णांक binary_nr = css->fwp->file_header.binary_nr;
	अचिन्हित पूर्णांक binary_mode =
		(css->pipes[pipe].pipe_id == IPU3_CSS_PIPE_ID_CAPTURE) ?
		IA_CSS_BINARY_MODE_PRIMARY : IA_CSS_BINARY_MODE_VIDEO;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *in =
					&queue[IPU3_CSS_QUEUE_IN].fmt.mpix;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *out =
					&queue[IPU3_CSS_QUEUE_OUT].fmt.mpix;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *vf =
					&queue[IPU3_CSS_QUEUE_VF].fmt.mpix;
	u32 stripe_w = 0, stripe_h = 0;
	स्थिर अक्षर *name;
	पूर्णांक i, j;

	अगर (!imgu_css_queue_enabled(&queue[IPU3_CSS_QUEUE_IN]))
		वापस -EINVAL;

	/* Find out the strip size boundary */
	क्रम (i = 0; i < binary_nr; i++) अणु
		काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[i];

		u32 max_width = bi->info.isp.sp.output.max_width;
		u32 max_height = bi->info.isp.sp.output.max_height;

		अगर (bi->info.isp.sp.iterator.num_stripes <= 1) अणु
			stripe_w = stripe_w ?
				min(stripe_w, max_width) : max_width;
			stripe_h = stripe_h ?
				min(stripe_h, max_height) : max_height;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < binary_nr; i++) अणु
		काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[i];
		क्रमागत imgu_abi_frame_क्रमmat q_fmt;

		name = (व्योम *)css->fwp + bi->blob.prog_name_offset;

		/* Check that binary supports memory-to-memory processing */
		अगर (bi->info.isp.sp.input.source !=
		    IMGU_ABI_BINARY_INPUT_SOURCE_MEMORY)
			जारी;

		/* Check that binary supports raw10 input */
		अगर (!bi->info.isp.sp.enable.input_feeder &&
		    !bi->info.isp.sp.enable.input_raw)
			जारी;

		/* Check binary mode */
		अगर (bi->info.isp.sp.pipeline.mode != binary_mode)
			जारी;

		/* Since input is RGGB bayer, need to process colors */
		अगर (bi->info.isp.sp.enable.luma_only)
			जारी;

		अगर (in->width < bi->info.isp.sp.input.min_width ||
		    in->width > bi->info.isp.sp.input.max_width ||
		    in->height < bi->info.isp.sp.input.min_height ||
		    in->height > bi->info.isp.sp.input.max_height)
			जारी;

		अगर (imgu_css_queue_enabled(&queue[IPU3_CSS_QUEUE_OUT])) अणु
			अगर (bi->info.isp.num_output_pins <= 0)
				जारी;

			q_fmt = queue[IPU3_CSS_QUEUE_OUT].css_fmt->frame_क्रमmat;
			क्रम (j = 0; j < bi->info.isp.num_output_क्रमmats; j++)
				अगर (bi->info.isp.output_क्रमmats[j] == q_fmt)
					अवरोध;
			अगर (j >= bi->info.isp.num_output_क्रमmats)
				जारी;

			अगर (out->width < bi->info.isp.sp.output.min_width ||
			    out->width > bi->info.isp.sp.output.max_width ||
			    out->height < bi->info.isp.sp.output.min_height ||
			    out->height > bi->info.isp.sp.output.max_height)
				जारी;

			अगर (out->width > bi->info.isp.sp.पूर्णांकernal.max_width ||
			    out->height > bi->info.isp.sp.पूर्णांकernal.max_height)
				जारी;
		पूर्ण

		अगर (imgu_css_queue_enabled(&queue[IPU3_CSS_QUEUE_VF])) अणु
			अगर (bi->info.isp.num_output_pins <= 1)
				जारी;

			q_fmt = queue[IPU3_CSS_QUEUE_VF].css_fmt->frame_क्रमmat;
			क्रम (j = 0; j < bi->info.isp.num_output_क्रमmats; j++)
				अगर (bi->info.isp.output_क्रमmats[j] == q_fmt)
					अवरोध;
			अगर (j >= bi->info.isp.num_output_क्रमmats)
				जारी;

			अगर (vf->width < bi->info.isp.sp.output.min_width ||
			    vf->width > bi->info.isp.sp.output.max_width ||
			    vf->height < bi->info.isp.sp.output.min_height ||
			    vf->height > bi->info.isp.sp.output.max_height)
				जारी;
		पूर्ण

		/* All checks passed, select the binary */
		dev_dbg(css->dev, "using binary %s id = %u\n", name,
			bi->info.isp.sp.id);
		वापस i;
	पूर्ण

	/* Can not find suitable binary क्रम these parameters */
	वापस -EINVAL;
पूर्ण

/*
 * Check that there is a binary matching requirements. Parameters may be
 * शून्य indicating disabled input/output. Return negative अगर given
 * parameters can not be supported or on error, zero or positive indicating
 * found binary number. May modअगरy the given parameters अगर not exact match
 * is found.
 */
पूर्णांक imgu_css_fmt_try(काष्ठा imgu_css *css,
		     काष्ठा v4l2_pix_क्रमmat_mplane *fmts[IPU3_CSS_QUEUES],
		     काष्ठा v4l2_rect *rects[IPU3_CSS_RECTS],
		     अचिन्हित पूर्णांक pipe)
अणु
	अटल स्थिर u32 EFF_ALIGN_W = 2;
	अटल स्थिर u32 BDS_ALIGN_W = 4;
	अटल स्थिर u32 OUT_ALIGN_W = 8;
	अटल स्थिर u32 OUT_ALIGN_H = 4;
	अटल स्थिर u32 VF_ALIGN_W  = 2;
	अटल स्थिर अक्षर *qnames[IPU3_CSS_QUEUES] = अणु
		[IPU3_CSS_QUEUE_IN] = "in",
		[IPU3_CSS_QUEUE_PARAMS]    = "params",
		[IPU3_CSS_QUEUE_OUT] = "out",
		[IPU3_CSS_QUEUE_VF] = "vf",
		[IPU3_CSS_QUEUE_STAT_3A]   = "3a",
	पूर्ण;
	अटल स्थिर अक्षर *rnames[IPU3_CSS_RECTS] = अणु
		[IPU3_CSS_RECT_EFFECTIVE] = "effective resolution",
		[IPU3_CSS_RECT_BDS]       = "bayer-domain scaled resolution",
		[IPU3_CSS_RECT_ENVELOPE]  = "DVS envelope size",
		[IPU3_CSS_RECT_GDC]  = "GDC output res",
	पूर्ण;
	काष्ठा v4l2_rect r[IPU3_CSS_RECTS] = अणु पूर्ण;
	काष्ठा v4l2_rect *स्थिर eff = &r[IPU3_CSS_RECT_EFFECTIVE];
	काष्ठा v4l2_rect *स्थिर bds = &r[IPU3_CSS_RECT_BDS];
	काष्ठा v4l2_rect *स्थिर env = &r[IPU3_CSS_RECT_ENVELOPE];
	काष्ठा v4l2_rect *स्थिर gdc = &r[IPU3_CSS_RECT_GDC];
	काष्ठा imgu_css_queue *q;
	काष्ठा v4l2_pix_क्रमmat_mplane *in, *out, *vf;
	पूर्णांक i, s, ret;

	q = kसुस्मृति(IPU3_CSS_QUEUES, माप(काष्ठा imgu_css_queue), GFP_KERNEL);
	अगर (!q)
		वापस -ENOMEM;

	in  = &q[IPU3_CSS_QUEUE_IN].fmt.mpix;
	out = &q[IPU3_CSS_QUEUE_OUT].fmt.mpix;
	vf  = &q[IPU3_CSS_QUEUE_VF].fmt.mpix;

	/* Adjust all क्रमmats, get statistics buffer sizes and क्रमmats */
	क्रम (i = 0; i < IPU3_CSS_QUEUES; i++) अणु
		अगर (fmts[i])
			dev_dbg(css->dev, "%s %s: (%i,%i) fmt 0x%x\n", __func__,
				qnames[i], fmts[i]->width, fmts[i]->height,
				fmts[i]->pixelक्रमmat);
		अन्यथा
			dev_dbg(css->dev, "%s %s: (not set)\n", __func__,
				qnames[i]);
		अगर (imgu_css_queue_init(&q[i], fmts[i],
					IPU3_CSS_QUEUE_TO_FLAGS(i))) अणु
			dev_notice(css->dev, "can not initialize queue %s\n",
				   qnames[i]);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < IPU3_CSS_RECTS; i++) अणु
		अगर (rects[i]) अणु
			dev_dbg(css->dev, "%s %s: (%i,%i)\n", __func__,
				rnames[i], rects[i]->width, rects[i]->height);
			r[i].width  = rects[i]->width;
			r[i].height = rects[i]->height;
		पूर्ण अन्यथा अणु
			dev_dbg(css->dev, "%s %s: (not set)\n", __func__,
				rnames[i]);
		पूर्ण
		/* For now, क्रमce known good resolutions */
		r[i].left = 0;
		r[i].top  = 0;
	पूर्ण

	/* Always require one input and vf only अगर out is also enabled */
	अगर (!imgu_css_queue_enabled(&q[IPU3_CSS_QUEUE_IN]) ||
	    !imgu_css_queue_enabled(&q[IPU3_CSS_QUEUE_OUT])) अणु
		dev_warn(css->dev, "required queues are disabled\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!imgu_css_queue_enabled(&q[IPU3_CSS_QUEUE_OUT])) अणु
		out->width = in->width;
		out->height = in->height;
	पूर्ण
	अगर (eff->width <= 0 || eff->height <= 0) अणु
		eff->width = in->width;
		eff->height = in->height;
	पूर्ण
	अगर (bds->width <= 0 || bds->height <= 0) अणु
		bds->width = out->width;
		bds->height = out->height;
	पूर्ण
	अगर (gdc->width <= 0 || gdc->height <= 0) अणु
		gdc->width = out->width;
		gdc->height = out->height;
	पूर्ण

	in->width   = imgu_css_adjust(in->width, 1);
	in->height  = imgu_css_adjust(in->height, 1);
	eff->width  = imgu_css_adjust(eff->width, EFF_ALIGN_W);
	eff->height = imgu_css_adjust(eff->height, 1);
	bds->width  = imgu_css_adjust(bds->width, BDS_ALIGN_W);
	bds->height = imgu_css_adjust(bds->height, 1);
	gdc->width  = imgu_css_adjust(gdc->width, OUT_ALIGN_W);
	gdc->height = imgu_css_adjust(gdc->height, OUT_ALIGN_H);
	out->width  = imgu_css_adjust(out->width, OUT_ALIGN_W);
	out->height = imgu_css_adjust(out->height, OUT_ALIGN_H);
	vf->width   = imgu_css_adjust(vf->width, VF_ALIGN_W);
	vf->height  = imgu_css_adjust(vf->height, 1);

	s = (bds->width - gdc->width) / 2;
	env->width = s < MIN_ENVELOPE ? MIN_ENVELOPE : s;
	s = (bds->height - gdc->height) / 2;
	env->height = s < MIN_ENVELOPE ? MIN_ENVELOPE : s;

	ret = imgu_css_find_binary(css, pipe, q, r);
	अगर (ret < 0) अणु
		dev_err(css->dev, "failed to find suitable binary\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	css->pipes[pipe].bindex = ret;

	dev_dbg(css->dev, "Binary index %d for pipe %d found.",
		css->pipes[pipe].bindex, pipe);

	/* Final adjusपंचांगent and set back the queried क्रमmats */
	क्रम (i = 0; i < IPU3_CSS_QUEUES; i++) अणु
		अगर (fmts[i]) अणु
			अगर (imgu_css_queue_init(&q[i], &q[i].fmt.mpix,
						IPU3_CSS_QUEUE_TO_FLAGS(i))) अणु
				dev_err(css->dev,
					"final resolution adjustment failed\n");
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			*fmts[i] = q[i].fmt.mpix;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < IPU3_CSS_RECTS; i++)
		अगर (rects[i])
			*rects[i] = r[i];

	dev_dbg(css->dev,
		"in(%u,%u) if(%u,%u) ds(%u,%u) gdc(%u,%u) out(%u,%u) vf(%u,%u)",
		 in->width, in->height, eff->width, eff->height,
		 bds->width, bds->height, gdc->width, gdc->height,
		 out->width, out->height, vf->width, vf->height);

	ret = 0;
out:
	kमुक्त(q);
	वापस ret;
पूर्ण

पूर्णांक imgu_css_fmt_set(काष्ठा imgu_css *css,
		     काष्ठा v4l2_pix_क्रमmat_mplane *fmts[IPU3_CSS_QUEUES],
		     काष्ठा v4l2_rect *rects[IPU3_CSS_RECTS],
		     अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा v4l2_rect rect_data[IPU3_CSS_RECTS];
	काष्ठा v4l2_rect *all_rects[IPU3_CSS_RECTS];
	पूर्णांक i, r;
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

	क्रम (i = 0; i < IPU3_CSS_RECTS; i++) अणु
		अगर (rects[i])
			rect_data[i] = *rects[i];
		अन्यथा
			स_रखो(&rect_data[i], 0, माप(rect_data[i]));
		all_rects[i] = &rect_data[i];
	पूर्ण
	r = imgu_css_fmt_try(css, fmts, all_rects, pipe);
	अगर (r < 0)
		वापस r;

	क्रम (i = 0; i < IPU3_CSS_QUEUES; i++)
		अगर (imgu_css_queue_init(&css_pipe->queue[i], fmts[i],
					IPU3_CSS_QUEUE_TO_FLAGS(i)))
			वापस -EINVAL;
	क्रम (i = 0; i < IPU3_CSS_RECTS; i++) अणु
		css_pipe->rect[i] = rect_data[i];
		अगर (rects[i])
			*rects[i] = rect_data[i];
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक imgu_css_meta_fmt_set(काष्ठा v4l2_meta_क्रमmat *fmt)
अणु
	चयन (fmt->dataक्रमmat) अणु
	हाल V4L2_META_FMT_IPU3_PARAMS:
		fmt->buffersize = माप(काष्ठा ipu3_uapi_params);

		/*
		 * Sanity check क्रम the parameter काष्ठा size. This must
		 * not change!
		 */
		BUILD_BUG_ON(माप(काष्ठा ipu3_uapi_params) != 39328);

		अवरोध;
	हाल V4L2_META_FMT_IPU3_STAT_3A:
		fmt->buffersize = माप(काष्ठा ipu3_uapi_stats_3a);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Queue given buffer to CSS. imgu_css_buf_prepare() must have been first
 * called क्रम the buffer. May be called from पूर्णांकerrupt context.
 * Returns 0 on success, -EBUSY अगर the buffer queue is full, or some other
 * code on error conditions.
 */
पूर्णांक imgu_css_buf_queue(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
		       काष्ठा imgu_css_buffer *b)
अणु
	काष्ठा imgu_abi_buffer *abi_buf;
	काष्ठा imgu_addr_t *buf_addr;
	u32 data;
	पूर्णांक r;
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

	अगर (!css->streaming)
		वापस -EPROTO;	/* CSS or buffer in wrong state */

	अगर (b->queue >= IPU3_CSS_QUEUES || !imgu_css_queues[b->queue].qid)
		वापस -EINVAL;

	b->queue_pos = imgu_css_queue_pos(css, imgu_css_queues[b->queue].qid,
					  pipe);

	अगर (b->queue_pos >= ARRAY_SIZE(css->pipes[pipe].abi_buffers[b->queue]))
		वापस -EIO;
	abi_buf = css->pipes[pipe].abi_buffers[b->queue][b->queue_pos].vaddr;

	/* Fill काष्ठा abi_buffer क्रम firmware */
	स_रखो(abi_buf, 0, माप(*abi_buf));

	buf_addr = (व्योम *)abi_buf + imgu_css_queues[b->queue].ptr_ofs;
	*(imgu_addr_t *)buf_addr = b->daddr;

	अगर (b->queue == IPU3_CSS_QUEUE_STAT_3A)
		abi_buf->payload.s3a.data.dmem.s3a_tbl = b->daddr;

	अगर (b->queue == IPU3_CSS_QUEUE_OUT)
		abi_buf->payload.frame.padded_width =
				css_pipe->queue[IPU3_CSS_QUEUE_OUT].width_pad;

	अगर (b->queue == IPU3_CSS_QUEUE_VF)
		abi_buf->payload.frame.padded_width =
					css_pipe->queue[IPU3_CSS_QUEUE_VF].width_pad;

	spin_lock(&css_pipe->qlock);
	list_add_tail(&b->list, &css_pipe->queue[b->queue].bufs);
	spin_unlock(&css_pipe->qlock);
	b->state = IPU3_CSS_BUFFER_QUEUED;

	data = css->pipes[pipe].abi_buffers[b->queue][b->queue_pos].daddr;
	r = imgu_css_queue_data(css, imgu_css_queues[b->queue].qid,
				pipe, data);
	अगर (r < 0)
		जाओ queueing_failed;

	data = IMGU_ABI_EVENT_BUFFER_ENQUEUED(pipe,
					      imgu_css_queues[b->queue].qid);
	r = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe, data);
	अगर (r < 0)
		जाओ queueing_failed;

	dev_dbg(css->dev, "queued buffer %p to css queue %i in pipe %d\n",
		b, b->queue, pipe);

	वापस 0;

queueing_failed:
	b->state = (r == -EBUSY || r == -EAGAIN) ?
		IPU3_CSS_BUFFER_NEW : IPU3_CSS_BUFFER_FAILED;
	list_del(&b->list);

	वापस r;
पूर्ण

/*
 * Get next पढ़ोy CSS buffer. Returns -EAGAIN in which हाल the function
 * should be called again, or -EBUSY which means that there are no more
 * buffers available. May be called from पूर्णांकerrupt context.
 */
काष्ठा imgu_css_buffer *imgu_css_buf_dequeue(काष्ठा imgu_css *css)
अणु
	अटल स्थिर अचिन्हित अक्षर evtype_to_queue[] = अणु
		[IMGU_ABI_EVTTYPE_INPUT_FRAME_DONE] = IPU3_CSS_QUEUE_IN,
		[IMGU_ABI_EVTTYPE_OUT_FRAME_DONE] = IPU3_CSS_QUEUE_OUT,
		[IMGU_ABI_EVTTYPE_VF_OUT_FRAME_DONE] = IPU3_CSS_QUEUE_VF,
		[IMGU_ABI_EVTTYPE_3A_STATS_DONE] = IPU3_CSS_QUEUE_STAT_3A,
	पूर्ण;
	काष्ठा imgu_css_buffer *b = ERR_PTR(-EAGAIN);
	u32 event, daddr;
	पूर्णांक evtype, pipe, pipeid, queue, qid, r;
	काष्ठा imgu_css_pipe *css_pipe;

	अगर (!css->streaming)
		वापस ERR_PTR(-EPROTO);

	r = imgu_css_dequeue_data(css, IMGU_ABI_QUEUE_EVENT_ID, &event);
	अगर (r < 0)
		वापस ERR_PTR(r);

	evtype = (event & IMGU_ABI_EVTTYPE_EVENT_MASK) >>
		  IMGU_ABI_EVTTYPE_EVENT_SHIFT;

	चयन (evtype) अणु
	हाल IMGU_ABI_EVTTYPE_OUT_FRAME_DONE:
	हाल IMGU_ABI_EVTTYPE_VF_OUT_FRAME_DONE:
	हाल IMGU_ABI_EVTTYPE_3A_STATS_DONE:
	हाल IMGU_ABI_EVTTYPE_INPUT_FRAME_DONE:
		pipe = (event & IMGU_ABI_EVTTYPE_PIPE_MASK) >>
			IMGU_ABI_EVTTYPE_PIPE_SHIFT;
		pipeid = (event & IMGU_ABI_EVTTYPE_PIPEID_MASK) >>
			IMGU_ABI_EVTTYPE_PIPEID_SHIFT;
		queue = evtype_to_queue[evtype];
		qid = imgu_css_queues[queue].qid;

		अगर (pipe >= IMGU_MAX_PIPE_NUM) अणु
			dev_err(css->dev, "Invalid pipe: %i\n", pipe);
			वापस ERR_PTR(-EIO);
		पूर्ण

		अगर (qid >= IMGU_ABI_QUEUE_NUM) अणु
			dev_err(css->dev, "Invalid qid: %i\n", qid);
			वापस ERR_PTR(-EIO);
		पूर्ण
		css_pipe = &css->pipes[pipe];
		dev_dbg(css->dev,
			"event: buffer done 0x%x queue %i pipe %i pipeid %i\n",
			event, queue, pipe, pipeid);

		r = imgu_css_dequeue_data(css, qid, &daddr);
		अगर (r < 0) अणु
			dev_err(css->dev, "failed to dequeue buffer\n");
			/* Force real error, not -EBUSY */
			वापस ERR_PTR(-EIO);
		पूर्ण

		r = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe,
					IMGU_ABI_EVENT_BUFFER_DEQUEUED(qid));
		अगर (r < 0) अणु
			dev_err(css->dev, "failed to queue event\n");
			वापस ERR_PTR(-EIO);
		पूर्ण

		spin_lock(&css_pipe->qlock);
		अगर (list_empty(&css_pipe->queue[queue].bufs)) अणु
			spin_unlock(&css_pipe->qlock);
			dev_err(css->dev, "event on empty queue\n");
			वापस ERR_PTR(-EIO);
		पूर्ण
		b = list_first_entry(&css_pipe->queue[queue].bufs,
				     काष्ठा imgu_css_buffer, list);
		अगर (queue != b->queue ||
		    daddr != css_pipe->abi_buffers
			[b->queue][b->queue_pos].daddr) अणु
			spin_unlock(&css_pipe->qlock);
			dev_err(css->dev, "dequeued bad buffer 0x%x\n", daddr);
			वापस ERR_PTR(-EIO);
		पूर्ण

		dev_dbg(css->dev, "buffer 0x%8x done from pipe %d\n", daddr, pipe);
		b->pipe = pipe;
		b->state = IPU3_CSS_BUFFER_DONE;
		list_del(&b->list);
		spin_unlock(&css_pipe->qlock);
		अवरोध;
	हाल IMGU_ABI_EVTTYPE_PIPELINE_DONE:
		pipe = (event & IMGU_ABI_EVTTYPE_PIPE_MASK) >>
			IMGU_ABI_EVTTYPE_PIPE_SHIFT;
		अगर (pipe >= IMGU_MAX_PIPE_NUM) अणु
			dev_err(css->dev, "Invalid pipe: %i\n", pipe);
			वापस ERR_PTR(-EIO);
		पूर्ण

		css_pipe = &css->pipes[pipe];
		dev_dbg(css->dev, "event: pipeline done 0x%8x for pipe %d\n",
			event, pipe);
		अवरोध;
	हाल IMGU_ABI_EVTTYPE_TIMER:
		r = imgu_css_dequeue_data(css, IMGU_ABI_QUEUE_EVENT_ID, &event);
		अगर (r < 0)
			वापस ERR_PTR(r);

		अगर ((event & IMGU_ABI_EVTTYPE_EVENT_MASK) >>
		    IMGU_ABI_EVTTYPE_EVENT_SHIFT == IMGU_ABI_EVTTYPE_TIMER)
			dev_dbg(css->dev, "event: timer\n");
		अन्यथा
			dev_warn(css->dev, "half of timer event missing\n");
		अवरोध;
	हाल IMGU_ABI_EVTTYPE_FW_WARNING:
		dev_warn(css->dev, "event: firmware warning 0x%x\n", event);
		अवरोध;
	हाल IMGU_ABI_EVTTYPE_FW_ASSERT:
		dev_err(css->dev,
			"event: firmware assert 0x%x module_id %i line_no %i\n",
			event,
			(event & IMGU_ABI_EVTTYPE_MODULEID_MASK) >>
			IMGU_ABI_EVTTYPE_MODULEID_SHIFT,
			swab16((event & IMGU_ABI_EVTTYPE_LINENO_MASK) >>
			       IMGU_ABI_EVTTYPE_LINENO_SHIFT));
		अवरोध;
	शेष:
		dev_warn(css->dev, "received unknown event 0x%x\n", event);
	पूर्ण

	वापस b;
पूर्ण

/*
 * Get a new set of parameters from pool and initialize them based on
 * the parameters params, gdc, and obgrid. Any of these may be शून्य,
 * in which हाल the previously set parameters are used.
 * If parameters haven't been set previously, initialize from scratch.
 *
 * Return index to css->parameter_set_info which has the newly created
 * parameters or negative value on error.
 */
पूर्णांक imgu_css_set_parameters(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
			    काष्ठा ipu3_uapi_params *set_params)
अणु
	अटल स्थिर अचिन्हित पूर्णांक queue_id = IMGU_ABI_QUEUE_A_ID;
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	स्थिर पूर्णांक stage = 0;
	स्थिर काष्ठा imgu_fw_info *bi;
	पूर्णांक obgrid_size;
	अचिन्हित पूर्णांक stripes, i;
	काष्ठा ipu3_uapi_flags *use = set_params ? &set_params->use : शून्य;

	/* Destination buffers which are filled here */
	काष्ठा imgu_abi_parameter_set_info *param_set;
	काष्ठा imgu_abi_acc_param *acc = शून्य;
	काष्ठा imgu_abi_gdc_warp_param *gdc = शून्य;
	काष्ठा ipu3_uapi_obgrid_param *obgrid = शून्य;
	स्थिर काष्ठा imgu_css_map *map;
	व्योम *vmem0 = शून्य;
	व्योम *dmem0 = शून्य;

	क्रमागत imgu_abi_memories m;
	पूर्णांक r = -EBUSY;

	अगर (!css->streaming)
		वापस -EPROTO;

	dev_dbg(css->dev, "%s for pipe %d", __func__, pipe);

	bi = &css->fwp->binary_header[css_pipe->bindex];
	obgrid_size = imgu_css_fw_obgrid_size(bi);
	stripes = bi->info.isp.sp.iterator.num_stripes ? : 1;

	imgu_css_pool_get(&css_pipe->pool.parameter_set_info);
	param_set = imgu_css_pool_last(&css_pipe->pool.parameter_set_info,
				       0)->vaddr;

	/* Get a new acc only अगर new parameters given, or none yet */
	map = imgu_css_pool_last(&css_pipe->pool.acc, 0);
	अगर (set_params || !map->vaddr) अणु
		imgu_css_pool_get(&css_pipe->pool.acc);
		map = imgu_css_pool_last(&css_pipe->pool.acc, 0);
		acc = map->vaddr;
	पूर्ण

	/* Get new VMEM0 only अगर needed, or none yet */
	m = IMGU_ABI_MEM_ISP_VMEM0;
	map = imgu_css_pool_last(&css_pipe->pool.binary_params_p[m], 0);
	अगर (!map->vaddr || (set_params && (set_params->use.lin_vmem_params ||
					   set_params->use.tnr3_vmem_params ||
					   set_params->use.xnr3_vmem_params))) अणु
		imgu_css_pool_get(&css_pipe->pool.binary_params_p[m]);
		map = imgu_css_pool_last(&css_pipe->pool.binary_params_p[m], 0);
		vmem0 = map->vaddr;
	पूर्ण

	/* Get new DMEM0 only अगर needed, or none yet */
	m = IMGU_ABI_MEM_ISP_DMEM0;
	map = imgu_css_pool_last(&css_pipe->pool.binary_params_p[m], 0);
	अगर (!map->vaddr || (set_params && (set_params->use.tnr3_dmem_params ||
					   set_params->use.xnr3_dmem_params))) अणु
		imgu_css_pool_get(&css_pipe->pool.binary_params_p[m]);
		map = imgu_css_pool_last(&css_pipe->pool.binary_params_p[m], 0);
		dmem0 = map->vaddr;
	पूर्ण

	/* Configure acc parameter cluster */
	अगर (acc) अणु
		/* get acc_old */
		map = imgu_css_pool_last(&css_pipe->pool.acc, 1);
		/* user acc */
		r = imgu_css_cfg_acc(css, pipe, use, acc, map->vaddr,
			set_params ? &set_params->acc_param : शून्य);
		अगर (r < 0)
			जाओ fail;
	पूर्ण

	/* Configure late binding parameters */
	अगर (vmem0) अणु
		m = IMGU_ABI_MEM_ISP_VMEM0;
		map = imgu_css_pool_last(&css_pipe->pool.binary_params_p[m], 1);
		r = imgu_css_cfg_vmem0(css, pipe, use, vmem0,
				       map->vaddr, set_params);
		अगर (r < 0)
			जाओ fail;
	पूर्ण

	अगर (dmem0) अणु
		m = IMGU_ABI_MEM_ISP_DMEM0;
		map = imgu_css_pool_last(&css_pipe->pool.binary_params_p[m], 1);
		r = imgu_css_cfg_dmem0(css, pipe, use, dmem0,
				       map->vaddr, set_params);
		अगर (r < 0)
			जाओ fail;
	पूर्ण

	/* Get a new gdc only अगर a new gdc is given, or none yet */
	अगर (bi->info.isp.sp.enable.dvs_6axis) अणु
		अचिन्हित पूर्णांक a = IPU3_CSS_AUX_FRAME_REF;
		अचिन्हित पूर्णांक g = IPU3_CSS_RECT_GDC;
		अचिन्हित पूर्णांक e = IPU3_CSS_RECT_ENVELOPE;

		map = imgu_css_pool_last(&css_pipe->pool.gdc, 0);
		अगर (!map->vaddr) अणु
			imgu_css_pool_get(&css_pipe->pool.gdc);
			map = imgu_css_pool_last(&css_pipe->pool.gdc, 0);
			gdc = map->vaddr;
			imgu_css_cfg_gdc_table(map->vaddr,
				css_pipe->aux_frames[a].bytesperline /
				css_pipe->aux_frames[a].bytesperpixel,
				css_pipe->aux_frames[a].height,
				css_pipe->rect[g].width,
				css_pipe->rect[g].height,
				css_pipe->rect[e].width,
				css_pipe->rect[e].height);
		पूर्ण
	पूर्ण

	/* Get a new obgrid only अगर a new obgrid is given, or none yet */
	map = imgu_css_pool_last(&css_pipe->pool.obgrid, 0);
	अगर (!map->vaddr || (set_params && set_params->use.obgrid_param)) अणु
		imgu_css_pool_get(&css_pipe->pool.obgrid);
		map = imgu_css_pool_last(&css_pipe->pool.obgrid, 0);
		obgrid = map->vaddr;

		/* Configure optical black level grid (obgrid) */
		अगर (set_params && set_params->use.obgrid_param)
			क्रम (i = 0; i < obgrid_size / माप(*obgrid); i++)
				obgrid[i] = set_params->obgrid_param;
		अन्यथा
			स_रखो(obgrid, 0, obgrid_size);
	पूर्ण

	/* Configure parameter set info, queued to `queue_id' */

	स_रखो(param_set, 0, माप(*param_set));
	map = imgu_css_pool_last(&css_pipe->pool.acc, 0);
	param_set->mem_map.acc_cluster_params_क्रम_sp = map->daddr;

	map = imgu_css_pool_last(&css_pipe->pool.gdc, 0);
	param_set->mem_map.dvs_6axis_params_y = map->daddr;

	क्रम (i = 0; i < stripes; i++) अणु
		map = imgu_css_pool_last(&css_pipe->pool.obgrid, 0);
		param_set->mem_map.obgrid_tbl[i] =
			map->daddr + (obgrid_size / stripes) * i;
	पूर्ण

	क्रम (m = 0; m < IMGU_ABI_NUM_MEMORIES; m++) अणु
		map = imgu_css_pool_last(&css_pipe->pool.binary_params_p[m], 0);
		param_set->mem_map.isp_mem_param[stage][m] = map->daddr;
	पूर्ण

	/* Then queue the new parameter buffer */
	map = imgu_css_pool_last(&css_pipe->pool.parameter_set_info, 0);
	r = imgu_css_queue_data(css, queue_id, pipe, map->daddr);
	अगर (r < 0)
		जाओ fail;

	r = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe,
				IMGU_ABI_EVENT_BUFFER_ENQUEUED(pipe,
							       queue_id));
	अगर (r < 0)
		जाओ fail_no_put;

	/* Finally dequeue all old parameter buffers */

	करो अणु
		u32 daddr;

		r = imgu_css_dequeue_data(css, queue_id, &daddr);
		अगर (r == -EBUSY)
			अवरोध;
		अगर (r)
			जाओ fail_no_put;
		r = imgu_css_queue_data(css, IMGU_ABI_QUEUE_EVENT_ID, pipe,
					IMGU_ABI_EVENT_BUFFER_DEQUEUED
					(queue_id));
		अगर (r < 0) अणु
			dev_err(css->dev, "failed to queue parameter event\n");
			जाओ fail_no_put;
		पूर्ण
	पूर्ण जबतक (1);

	वापस 0;

fail:
	/*
	 * A failure, most likely the parameter queue was full.
	 * Return error but जारी streaming. User can try submitting new
	 * parameters again later.
	 */

	imgu_css_pool_put(&css_pipe->pool.parameter_set_info);
	अगर (acc)
		imgu_css_pool_put(&css_pipe->pool.acc);
	अगर (gdc)
		imgu_css_pool_put(&css_pipe->pool.gdc);
	अगर (obgrid)
		imgu_css_pool_put(&css_pipe->pool.obgrid);
	अगर (vmem0)
		imgu_css_pool_put(
			&css_pipe->pool.binary_params_p
			[IMGU_ABI_MEM_ISP_VMEM0]);
	अगर (dmem0)
		imgu_css_pool_put(
			&css_pipe->pool.binary_params_p
			[IMGU_ABI_MEM_ISP_DMEM0]);

fail_no_put:
	वापस r;
पूर्ण

पूर्णांक imgu_css_irq_ack(काष्ठा imgu_css *css)
अणु
	अटल स्थिर पूर्णांक NUM_SWIRQS = 3;
	काष्ठा imgu_fw_info *bi = &css->fwp->binary_header[css->fw_sp[0]];
	व्योम __iomem *स्थिर base = css->base;
	u32 irq_status[IMGU_IRQCTRL_NUM];
	पूर्णांक i;

	u32 imgu_status = पढ़ोl(base + IMGU_REG_INT_STATUS);

	ग_लिखोl(imgu_status, base + IMGU_REG_INT_STATUS);
	क्रम (i = 0; i < IMGU_IRQCTRL_NUM; i++)
		irq_status[i] = पढ़ोl(base + IMGU_REG_IRQCTRL_STATUS(i));

	क्रम (i = 0; i < NUM_SWIRQS; i++) अणु
		अगर (irq_status[IMGU_IRQCTRL_SP0] & IMGU_IRQCTRL_IRQ_SW_PIN(i)) अणु
			/* SP SW पूर्णांकerrupt */
			u32 cnt = पढ़ोl(base + IMGU_REG_SP_DMEM_BASE(0) +
					bi->info.sp.output);
			u32 val = पढ़ोl(base + IMGU_REG_SP_DMEM_BASE(0) +
					bi->info.sp.output + 4 + 4 * i);

			dev_dbg(css->dev, "%s: swirq %i cnt %i val 0x%x\n",
				__func__, i, cnt, val);
		पूर्ण
	पूर्ण

	क्रम (i = IMGU_IRQCTRL_NUM - 1; i >= 0; i--)
		अगर (irq_status[i]) अणु
			ग_लिखोl(irq_status[i], base + IMGU_REG_IRQCTRL_CLEAR(i));
			/* Wait क्रम ग_लिखो to complete */
			पढ़ोl(base + IMGU_REG_IRQCTRL_ENABLE(i));
		पूर्ण

	dev_dbg(css->dev, "%s: imgu 0x%x main 0x%x sp0 0x%x sp1 0x%x\n",
		__func__, imgu_status, irq_status[IMGU_IRQCTRL_MAIN],
		irq_status[IMGU_IRQCTRL_SP0], irq_status[IMGU_IRQCTRL_SP1]);

	अगर (!imgu_status && !irq_status[IMGU_IRQCTRL_MAIN])
		वापस -ENOMSG;

	वापस 0;
पूर्ण
