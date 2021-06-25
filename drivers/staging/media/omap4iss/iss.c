<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI OMAP4 ISS V4L2 Driver
 *
 * Copyright (C) 2012, Texas Instruments
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "iss.h"
#समावेश "iss_regs.h"

#घोषणा ISS_PRINT_REGISTER(iss, name)\
	dev_dbg(iss->dev, "###ISS " #name "=0x%08x\n", \
		iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_TOP, ISS_##name))

अटल व्योम iss_prपूर्णांक_status(काष्ठा iss_device *iss)
अणु
	dev_dbg(iss->dev, "-------------ISS HL Register dump-------------\n");

	ISS_PRINT_REGISTER(iss, HL_REVISION);
	ISS_PRINT_REGISTER(iss, HL_SYSCONFIG);
	ISS_PRINT_REGISTER(iss, HL_IRQSTATUS(5));
	ISS_PRINT_REGISTER(iss, HL_IRQENABLE_SET(5));
	ISS_PRINT_REGISTER(iss, HL_IRQENABLE_CLR(5));
	ISS_PRINT_REGISTER(iss, CTRL);
	ISS_PRINT_REGISTER(iss, CLKCTRL);
	ISS_PRINT_REGISTER(iss, CLKSTAT);

	dev_dbg(iss->dev, "-----------------------------------------------\n");
पूर्ण

/*
 * omap4iss_flush - Post pending L3 bus ग_लिखोs by करोing a रेजिस्टर पढ़ोback
 * @iss: OMAP4 ISS device
 *
 * In order to क्रमce posting of pending ग_लिखोs, we need to ग_लिखो and
 * पढ़ोback the same रेजिस्टर, in this हाल the revision रेजिस्टर.
 *
 * See this link क्रम reference:
 *   https://www.mail-archive.com/linux-omap@vger.kernel.org/msg08149.hपंचांगl
 */
अटल व्योम omap4iss_flush(काष्ठा iss_device *iss)
अणु
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_TOP, ISS_HL_REVISION, 0);
	iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_TOP, ISS_HL_REVISION);
पूर्ण

/*
 * iss_isp_enable_पूर्णांकerrupts - Enable ISS ISP पूर्णांकerrupts.
 * @iss: OMAP4 ISS device
 */
अटल व्योम omap4iss_isp_enable_पूर्णांकerrupts(काष्ठा iss_device *iss)
अणु
	अटल स्थिर u32 isp_irq = ISP5_IRQ_OCP_ERR |
				   ISP5_IRQ_RSZ_FIFO_IN_BLK_ERR |
				   ISP5_IRQ_RSZ_FIFO_OVF |
				   ISP5_IRQ_RSZ_INT_DMA |
				   ISP5_IRQ_ISIF_INT(0);

	/* Enable ISP पूर्णांकerrupts */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_IRQSTATUS(0), isp_irq);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_IRQENABLE_SET(0),
		      isp_irq);
पूर्ण

/*
 * iss_isp_disable_पूर्णांकerrupts - Disable ISS पूर्णांकerrupts.
 * @iss: OMAP4 ISS device
 */
अटल व्योम omap4iss_isp_disable_पूर्णांकerrupts(काष्ठा iss_device *iss)
अणु
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_IRQENABLE_CLR(0), ~0);
पूर्ण

/*
 * iss_enable_पूर्णांकerrupts - Enable ISS पूर्णांकerrupts.
 * @iss: OMAP4 ISS device
 */
अटल व्योम iss_enable_पूर्णांकerrupts(काष्ठा iss_device *iss)
अणु
	अटल स्थिर u32 hl_irq = ISS_HL_IRQ_CSIA | ISS_HL_IRQ_CSIB
				| ISS_HL_IRQ_ISP(0);

	/* Enable HL पूर्णांकerrupts */
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_TOP, ISS_HL_IRQSTATUS(5), hl_irq);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_TOP, ISS_HL_IRQENABLE_SET(5), hl_irq);

	अगर (iss->regs[OMAP4_ISS_MEM_ISP_SYS1])
		omap4iss_isp_enable_पूर्णांकerrupts(iss);
पूर्ण

/*
 * iss_disable_पूर्णांकerrupts - Disable ISS पूर्णांकerrupts.
 * @iss: OMAP4 ISS device
 */
अटल व्योम iss_disable_पूर्णांकerrupts(काष्ठा iss_device *iss)
अणु
	अगर (iss->regs[OMAP4_ISS_MEM_ISP_SYS1])
		omap4iss_isp_disable_पूर्णांकerrupts(iss);

	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_TOP, ISS_HL_IRQENABLE_CLR(5), ~0);
पूर्ण

पूर्णांक omap4iss_get_बाह्यal_info(काष्ठा iss_pipeline *pipe,
			       काष्ठा media_link *link)
अणु
	काष्ठा iss_device *iss =
		container_of(pipe, काष्ठा iss_video, pipe)->iss;
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक ret;

	अगर (!pipe->बाह्यal)
		वापस 0;

	अगर (pipe->बाह्यal_rate)
		वापस 0;

	स_रखो(&fmt, 0, माप(fmt));

	fmt.pad = link->source->index;
	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(media_entity_to_v4l2_subdev(link->sink->entity),
			       pad, get_fmt, शून्य, &fmt);
	अगर (ret < 0)
		वापस -EPIPE;

	pipe->बाह्यal_bpp = omap4iss_video_क्रमmat_info(fmt.क्रमmat.code)->bpp;

	ctrl = v4l2_ctrl_find(pipe->बाह्यal->ctrl_handler,
			      V4L2_CID_PIXEL_RATE);
	अगर (!ctrl) अणु
		dev_warn(iss->dev, "no pixel rate control in subdev %s\n",
			 pipe->बाह्यal->name);
		वापस -EPIPE;
	पूर्ण

	pipe->बाह्यal_rate = v4l2_ctrl_g_ctrl_पूर्णांक64(ctrl);

	वापस 0;
पूर्ण

/*
 * Configure the bridge. Valid inमाला_दो are
 *
 * IPIPEIF_INPUT_CSI2A: CSI2a receiver
 * IPIPEIF_INPUT_CSI2B: CSI2b receiver
 *
 * The bridge and lane shअगरter are configured according to the selected input
 * and the ISP platक्रमm data.
 */
व्योम omap4iss_configure_bridge(काष्ठा iss_device *iss,
			       क्रमागत ipipeअगर_input_entity input)
अणु
	u32 issctrl_val;
	u32 isp5ctrl_val;

	issctrl_val = iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_TOP, ISS_CTRL);
	issctrl_val &= ~ISS_CTRL_INPUT_SEL_MASK;
	issctrl_val &= ~ISS_CTRL_CLK_DIV_MASK;

	isp5ctrl_val = iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_CTRL);

	चयन (input) अणु
	हाल IPIPEIF_INPUT_CSI2A:
		issctrl_val |= ISS_CTRL_INPUT_SEL_CSI2A;
		अवरोध;

	हाल IPIPEIF_INPUT_CSI2B:
		issctrl_val |= ISS_CTRL_INPUT_SEL_CSI2B;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	issctrl_val |= ISS_CTRL_SYNC_DETECT_VS_RAISING;

	isp5ctrl_val |= ISP5_CTRL_VD_PULSE_EXT | ISP5_CTRL_PSYNC_CLK_SEL |
			ISP5_CTRL_SYNC_ENABLE;

	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_TOP, ISS_CTRL, issctrl_val);
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_CTRL, isp5ctrl_val);
पूर्ण

#अगर_घोषित ISS_ISR_DEBUG
अटल व्योम iss_isr_dbg(काष्ठा iss_device *iss, u32 irqstatus)
अणु
	अटल स्थिर अक्षर * स्थिर name[] = अणु
		"ISP_0",
		"ISP_1",
		"ISP_2",
		"ISP_3",
		"CSIA",
		"CSIB",
		"CCP2_0",
		"CCP2_1",
		"CCP2_2",
		"CCP2_3",
		"CBUFF",
		"BTE",
		"SIMCOP_0",
		"SIMCOP_1",
		"SIMCOP_2",
		"SIMCOP_3",
		"CCP2_8",
		"HS_VS",
		"18",
		"19",
		"20",
		"21",
		"22",
		"23",
		"24",
		"25",
		"26",
		"27",
		"28",
		"29",
		"30",
		"31",
	पूर्ण;
	अचिन्हित पूर्णांक i;

	dev_dbg(iss->dev, "ISS IRQ: ");

	क्रम (i = 0; i < ARRAY_SIZE(name); i++) अणु
		अगर ((1 << i) & irqstatus)
			pr_cont("%s ", name[i]);
	पूर्ण
	pr_cont("\n");
पूर्ण

अटल व्योम iss_isp_isr_dbg(काष्ठा iss_device *iss, u32 irqstatus)
अणु
	अटल स्थिर अक्षर * स्थिर name[] = अणु
		"ISIF_0",
		"ISIF_1",
		"ISIF_2",
		"ISIF_3",
		"IPIPEREQ",
		"IPIPELAST_PIX",
		"IPIPEDMA",
		"IPIPEBSC",
		"IPIPEHST",
		"IPIPEIF",
		"AEW",
		"AF",
		"H3A",
		"RSZ_REG",
		"RSZ_LAST_PIX",
		"RSZ_DMA",
		"RSZ_CYC_RZA",
		"RSZ_CYC_RZB",
		"RSZ_FIFO_OVF",
		"RSZ_FIFO_IN_BLK_ERR",
		"20",
		"21",
		"RSZ_EOF0",
		"RSZ_EOF1",
		"H3A_EOF",
		"IPIPE_EOF",
		"26",
		"IPIPE_DPC_INI",
		"IPIPE_DPC_RNEW0",
		"IPIPE_DPC_RNEW1",
		"30",
		"OCP_ERR",
	पूर्ण;
	अचिन्हित पूर्णांक i;

	dev_dbg(iss->dev, "ISP IRQ: ");

	क्रम (i = 0; i < ARRAY_SIZE(name); i++) अणु
		अगर ((1 << i) & irqstatus)
			pr_cont("%s ", name[i]);
	पूर्ण
	pr_cont("\n");
पूर्ण
#पूर्ण_अगर

/*
 * iss_isr - Interrupt Service Routine क्रम ISS module.
 * @irq: Not used currently.
 * @_iss: Poपूर्णांकer to the OMAP4 ISS device
 *
 * Handles the corresponding callback अगर plugged in.
 *
 * Returns IRQ_HANDLED when IRQ was correctly handled, or IRQ_NONE when the
 * IRQ wasn't handled.
 */
अटल irqवापस_t iss_isr(पूर्णांक irq, व्योम *_iss)
अणु
	अटल स्थिर u32 ipipeअगर_events = ISP5_IRQ_IPIPEIF_IRQ |
					  ISP5_IRQ_ISIF_INT(0);
	अटल स्थिर u32 resizer_events = ISP5_IRQ_RSZ_FIFO_IN_BLK_ERR |
					  ISP5_IRQ_RSZ_FIFO_OVF |
					  ISP5_IRQ_RSZ_INT_DMA;
	काष्ठा iss_device *iss = _iss;
	u32 irqstatus;

	irqstatus = iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_TOP, ISS_HL_IRQSTATUS(5));
	iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_TOP, ISS_HL_IRQSTATUS(5), irqstatus);

	अगर (irqstatus & ISS_HL_IRQ_CSIA)
		omap4iss_csi2_isr(&iss->csi2a);

	अगर (irqstatus & ISS_HL_IRQ_CSIB)
		omap4iss_csi2_isr(&iss->csi2b);

	अगर (irqstatus & ISS_HL_IRQ_ISP(0)) अणु
		u32 isp_irqstatus = iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_SYS1,
						 ISP5_IRQSTATUS(0));
		iss_reg_ग_लिखो(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_IRQSTATUS(0),
			      isp_irqstatus);

		अगर (isp_irqstatus & ISP5_IRQ_OCP_ERR)
			dev_dbg(iss->dev, "ISP5 OCP Error!\n");

		अगर (isp_irqstatus & ipipeअगर_events) अणु
			omap4iss_ipipeअगर_isr(&iss->ipipeअगर,
					     isp_irqstatus & ipipeअगर_events);
		पूर्ण

		अगर (isp_irqstatus & resizer_events)
			omap4iss_resizer_isr(&iss->resizer,
					     isp_irqstatus & resizer_events);

#अगर_घोषित ISS_ISR_DEBUG
		iss_isp_isr_dbg(iss, isp_irqstatus);
#पूर्ण_अगर
	पूर्ण

	omap4iss_flush(iss);

#अगर_घोषित ISS_ISR_DEBUG
	iss_isr_dbg(iss, irqstatus);
#पूर्ण_अगर

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा media_device_ops iss_media_ops = अणु
	.link_notअगरy = v4l2_pipeline_link_notअगरy,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Pipeline stream management
 */

/*
 * iss_pipeline_disable - Disable streaming on a pipeline
 * @pipe: ISS pipeline
 * @until: entity at which to stop pipeline walk
 *
 * Walk the entities chain starting at the pipeline output video node and stop
 * all modules in the chain. Wait synchronously क्रम the modules to be stopped अगर
 * necessary.
 *
 * If the until argument isn't शून्य, stop the pipeline walk when reaching the
 * until entity. This is used to disable a partially started pipeline due to a
 * subdev start error.
 */
अटल पूर्णांक iss_pipeline_disable(काष्ठा iss_pipeline *pipe,
				काष्ठा media_entity *until)
अणु
	काष्ठा iss_device *iss = pipe->output->iss;
	काष्ठा media_entity *entity;
	काष्ठा media_pad *pad;
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक failure = 0;
	पूर्णांक ret;

	entity = &pipe->output->video.entity;
	जबतक (1) अणु
		pad = &entity->pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;

		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		entity = pad->entity;
		अगर (entity == until)
			अवरोध;

		subdev = media_entity_to_v4l2_subdev(entity);
		ret = v4l2_subdev_call(subdev, video, s_stream, 0);
		अगर (ret < 0) अणु
			dev_warn(iss->dev, "%s: module stop timeout.\n",
				 subdev->name);
			/* If the entity failed to stopped, assume it has
			 * crashed. Mark it as such, the ISS will be reset when
			 * applications will release it.
			 */
			media_entity_क्रमागत_set(&iss->crashed, &subdev->entity);
			failure = -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस failure;
पूर्ण

/*
 * iss_pipeline_enable - Enable streaming on a pipeline
 * @pipe: ISS pipeline
 * @mode: Stream mode (single shot or continuous)
 *
 * Walk the entities chain starting at the pipeline output video node and start
 * all modules in the chain in the given mode.
 *
 * Return 0 अगर successful, or the वापस value of the failed video::s_stream
 * operation otherwise.
 */
अटल पूर्णांक iss_pipeline_enable(काष्ठा iss_pipeline *pipe,
			       क्रमागत iss_pipeline_stream_state mode)
अणु
	काष्ठा iss_device *iss = pipe->output->iss;
	काष्ठा media_entity *entity;
	काष्ठा media_pad *pad;
	काष्ठा v4l2_subdev *subdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* If one of the entities in the pipeline has crashed it will not work
	 * properly. Refuse to start streaming in that हाल. This check must be
	 * perक्रमmed beक्रमe the loop below to aव्योम starting entities अगर the
	 * pipeline won't start anyway (those entities would then likely fail to
	 * stop, making the problem worse).
	 */
	अगर (media_entity_क्रमागत_पूर्णांकersects(&pipe->ent_क्रमागत, &iss->crashed))
		वापस -EIO;

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~(ISS_PIPELINE_IDLE_INPUT | ISS_PIPELINE_IDLE_OUTPUT);
	spin_unlock_irqrestore(&pipe->lock, flags);

	pipe->करो_propagation = false;

	mutex_lock(&iss->media_dev.graph_mutex);

	entity = &pipe->output->video.entity;
	जबतक (1) अणु
		pad = &entity->pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;

		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		entity = pad->entity;
		subdev = media_entity_to_v4l2_subdev(entity);

		ret = v4l2_subdev_call(subdev, video, s_stream, mode);
		अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
			iss_pipeline_disable(pipe, entity);
			mutex_unlock(&iss->media_dev.graph_mutex);
			वापस ret;
		पूर्ण

		अगर (subdev == &iss->csi2a.subdev ||
		    subdev == &iss->csi2b.subdev)
			pipe->करो_propagation = true;
	पूर्ण

	mutex_unlock(&iss->media_dev.graph_mutex);
	iss_prपूर्णांक_status(pipe->output->iss);

	वापस 0;
पूर्ण

/*
 * omap4iss_pipeline_set_stream - Enable/disable streaming on a pipeline
 * @pipe: ISS pipeline
 * @state: Stream state (stopped, single shot or continuous)
 *
 * Set the pipeline to the given stream state. Pipelines can be started in
 * single-shot or continuous mode.
 *
 * Return 0 अगर successful, or the वापस value of the failed video::s_stream
 * operation otherwise. The pipeline state is not updated when the operation
 * fails, except when stopping the pipeline.
 */
पूर्णांक omap4iss_pipeline_set_stream(काष्ठा iss_pipeline *pipe,
				 क्रमागत iss_pipeline_stream_state state)
अणु
	पूर्णांक ret;

	अगर (state == ISS_PIPELINE_STREAM_STOPPED)
		ret = iss_pipeline_disable(pipe, शून्य);
	अन्यथा
		ret = iss_pipeline_enable(pipe, state);

	अगर (ret == 0 || state == ISS_PIPELINE_STREAM_STOPPED)
		pipe->stream_state = state;

	वापस ret;
पूर्ण

/*
 * omap4iss_pipeline_cancel_stream - Cancel stream on a pipeline
 * @pipe: ISS pipeline
 *
 * Cancelling a stream mark all buffers on all video nodes in the pipeline as
 * erroneous and makes sure no new buffer can be queued. This function is called
 * when a fatal error that prevents any further operation on the pipeline
 * occurs.
 */
व्योम omap4iss_pipeline_cancel_stream(काष्ठा iss_pipeline *pipe)
अणु
	अगर (pipe->input)
		omap4iss_video_cancel_stream(pipe->input);
	अगर (pipe->output)
		omap4iss_video_cancel_stream(pipe->output);
पूर्ण

/*
 * iss_pipeline_is_last - Verअगरy अगर entity has an enabled link to the output
 *			  video node
 * @me: ISS module's media entity
 *
 * Returns 1 अगर the entity has an enabled link to the output video node or 0
 * otherwise. It's true only जबतक pipeline can have no more than one output
 * node.
 */
अटल पूर्णांक iss_pipeline_is_last(काष्ठा media_entity *me)
अणु
	काष्ठा iss_pipeline *pipe;
	काष्ठा media_pad *pad;

	अगर (!me->pipe)
		वापस 0;
	pipe = to_iss_pipeline(me);
	अगर (pipe->stream_state == ISS_PIPELINE_STREAM_STOPPED)
		वापस 0;
	pad = media_entity_remote_pad(&pipe->output->pad);
	वापस pad->entity == me;
पूर्ण

अटल पूर्णांक iss_reset(काष्ठा iss_device *iss)
अणु
	अचिन्हित पूर्णांक समयout;

	iss_reg_set(iss, OMAP4_ISS_MEM_TOP, ISS_HL_SYSCONFIG,
		    ISS_HL_SYSCONFIG_SOFTRESET);

	समयout = iss_poll_condition_समयout(
		!(iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_TOP, ISS_HL_SYSCONFIG) &
		ISS_HL_SYSCONFIG_SOFTRESET), 1000, 10, 100);
	अगर (समयout) अणु
		dev_err(iss->dev, "ISS reset timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	media_entity_क्रमागत_zero(&iss->crashed);

	वापस 0;
पूर्ण

अटल पूर्णांक iss_isp_reset(काष्ठा iss_device *iss)
अणु
	अचिन्हित पूर्णांक समयout;

	/* Fist, ensure that the ISP is IDLE (no transactions happening) */
	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_SYSCONFIG,
		       ISP5_SYSCONFIG_STANDBYMODE_MASK,
		       ISP5_SYSCONFIG_STANDBYMODE_SMART);

	iss_reg_set(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_CTRL, ISP5_CTRL_MSTANDBY);

	समयout = iss_poll_condition_समयout(
		iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_CTRL) &
		ISP5_CTRL_MSTANDBY_WAIT, 1000000, 1000, 1500);
	अगर (समयout) अणु
		dev_err(iss->dev, "ISP5 standby timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* Now finally, करो the reset */
	iss_reg_set(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_SYSCONFIG,
		    ISP5_SYSCONFIG_SOFTRESET);

	समयout = iss_poll_condition_समयout(
		!(iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_SYSCONFIG) &
		ISP5_SYSCONFIG_SOFTRESET), 1000000, 1000, 1500);
	अगर (समयout) अणु
		dev_err(iss->dev, "ISP5 reset timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * iss_module_sync_idle - Helper to sync module with its idle state
 * @me: ISS submodule's media entity
 * @रुको: ISS submodule's रुको queue क्रम streamoff/पूर्णांकerrupt synchronization
 * @stopping: flag which tells module wants to stop
 *
 * This function checks अगर ISS submodule needs to रुको क्रम next पूर्णांकerrupt. If
 * yes, makes the caller to sleep जबतक रुकोing क्रम such event.
 */
पूर्णांक omap4iss_module_sync_idle(काष्ठा media_entity *me, रुको_queue_head_t *रुको,
			      atomic_t *stopping)
अणु
	काष्ठा iss_pipeline *pipe = to_iss_pipeline(me);
	काष्ठा iss_video *video = pipe->output;
	अचिन्हित दीर्घ flags;

	अगर (pipe->stream_state == ISS_PIPELINE_STREAM_STOPPED ||
	    (pipe->stream_state == ISS_PIPELINE_STREAM_SINGLESHOT &&
	     !iss_pipeline_पढ़ोy(pipe)))
		वापस 0;

	/*
	 * atomic_set() करोesn't include memory barrier on ARM platक्रमm क्रम SMP
	 * scenario. We'll call it here to aव्योम race conditions.
	 */
	atomic_set(stopping, 1);
	smp_wmb();

	/*
	 * If module is the last one, it's writing to memory. In this हाल,
	 * it's necessary to check अगर the module is alपढ़ोy छोड़ोd due to
	 * DMA queue underrun or अगर it has to रुको क्रम next पूर्णांकerrupt to be
	 * idle.
	 * If it isn't the last one, the function won't sleep but *stopping
	 * will still be set to warn next submodule caller's पूर्णांकerrupt the
	 * module wants to be idle.
	 */
	अगर (!iss_pipeline_is_last(me))
		वापस 0;

	spin_lock_irqsave(&video->qlock, flags);
	अगर (video->dmaqueue_flags & ISS_VIDEO_DMAQUEUE_UNDERRUN) अणु
		spin_unlock_irqrestore(&video->qlock, flags);
		atomic_set(stopping, 0);
		smp_wmb();
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&video->qlock, flags);
	अगर (!रुको_event_समयout(*रुको, !atomic_पढ़ो(stopping),
				msecs_to_jअगरfies(1000))) अणु
		atomic_set(stopping, 0);
		smp_wmb();
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * omap4iss_module_sync_is_stopped - Helper to verअगरy अगर module was stopping
 * @रुको: ISS submodule's रुको queue क्रम streamoff/पूर्णांकerrupt synchronization
 * @stopping: flag which tells module wants to stop
 *
 * This function checks अगर ISS submodule was stopping. In हाल of yes, it
 * notices the caller by setting stopping to 0 and waking up the रुको queue.
 * Returns 1 अगर it was stopping or 0 otherwise.
 */
पूर्णांक omap4iss_module_sync_is_stopping(रुको_queue_head_t *रुको,
				     atomic_t *stopping)
अणु
	अगर (atomic_cmpxchg(stopping, 1, 0)) अणु
		wake_up(रुको);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------
 * Clock management
 */

#घोषणा ISS_CLKCTRL_MASK	(ISS_CLKCTRL_CSI2_A |\
				 ISS_CLKCTRL_CSI2_B |\
				 ISS_CLKCTRL_ISP)

अटल पूर्णांक __iss_subclk_update(काष्ठा iss_device *iss)
अणु
	u32 clk = 0;
	पूर्णांक ret = 0, समयout = 1000;

	अगर (iss->subclk_resources & OMAP4_ISS_SUBCLK_CSI2_A)
		clk |= ISS_CLKCTRL_CSI2_A;

	अगर (iss->subclk_resources & OMAP4_ISS_SUBCLK_CSI2_B)
		clk |= ISS_CLKCTRL_CSI2_B;

	अगर (iss->subclk_resources & OMAP4_ISS_SUBCLK_ISP)
		clk |= ISS_CLKCTRL_ISP;

	iss_reg_update(iss, OMAP4_ISS_MEM_TOP, ISS_CLKCTRL,
		       ISS_CLKCTRL_MASK, clk);

	/* Wait क्रम HW निश्चितion */
	जबतक (--समयout > 0) अणु
		udelay(1);
		अगर ((iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_TOP, ISS_CLKSTAT) &
		    ISS_CLKCTRL_MASK) == clk)
			अवरोध;
	पूर्ण

	अगर (!समयout)
		ret = -EBUSY;

	वापस ret;
पूर्ण

पूर्णांक omap4iss_subclk_enable(काष्ठा iss_device *iss,
			   क्रमागत iss_subclk_resource res)
अणु
	iss->subclk_resources |= res;

	वापस __iss_subclk_update(iss);
पूर्ण

पूर्णांक omap4iss_subclk_disable(काष्ठा iss_device *iss,
			    क्रमागत iss_subclk_resource res)
अणु
	iss->subclk_resources &= ~res;

	वापस __iss_subclk_update(iss);
पूर्ण

#घोषणा ISS_ISP5_CLKCTRL_MASK	(ISP5_CTRL_BL_CLK_ENABLE |\
				 ISP5_CTRL_ISIF_CLK_ENABLE |\
				 ISP5_CTRL_H3A_CLK_ENABLE |\
				 ISP5_CTRL_RSZ_CLK_ENABLE |\
				 ISP5_CTRL_IPIPE_CLK_ENABLE |\
				 ISP5_CTRL_IPIPEIF_CLK_ENABLE)

अटल व्योम __iss_isp_subclk_update(काष्ठा iss_device *iss)
अणु
	u32 clk = 0;

	अगर (iss->isp_subclk_resources & OMAP4_ISS_ISP_SUBCLK_ISIF)
		clk |= ISP5_CTRL_ISIF_CLK_ENABLE;

	अगर (iss->isp_subclk_resources & OMAP4_ISS_ISP_SUBCLK_H3A)
		clk |= ISP5_CTRL_H3A_CLK_ENABLE;

	अगर (iss->isp_subclk_resources & OMAP4_ISS_ISP_SUBCLK_RSZ)
		clk |= ISP5_CTRL_RSZ_CLK_ENABLE;

	अगर (iss->isp_subclk_resources & OMAP4_ISS_ISP_SUBCLK_IPIPE)
		clk |= ISP5_CTRL_IPIPE_CLK_ENABLE;

	अगर (iss->isp_subclk_resources & OMAP4_ISS_ISP_SUBCLK_IPIPEIF)
		clk |= ISP5_CTRL_IPIPEIF_CLK_ENABLE;

	अगर (clk)
		clk |= ISP5_CTRL_BL_CLK_ENABLE;

	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_CTRL,
		       ISS_ISP5_CLKCTRL_MASK, clk);
पूर्ण

व्योम omap4iss_isp_subclk_enable(काष्ठा iss_device *iss,
				क्रमागत iss_isp_subclk_resource res)
अणु
	iss->isp_subclk_resources |= res;

	__iss_isp_subclk_update(iss);
पूर्ण

व्योम omap4iss_isp_subclk_disable(काष्ठा iss_device *iss,
				 क्रमागत iss_isp_subclk_resource res)
अणु
	iss->isp_subclk_resources &= ~res;

	__iss_isp_subclk_update(iss);
पूर्ण

/*
 * iss_enable_घड़ीs - Enable ISS घड़ीs
 * @iss: OMAP4 ISS device
 *
 * Return 0 अगर successful, or clk_enable वापस value अगर any of tthem fails.
 */
अटल पूर्णांक iss_enable_घड़ीs(काष्ठा iss_device *iss)
अणु
	पूर्णांक ret;

	ret = clk_enable(iss->iss_fck);
	अगर (ret) अणु
		dev_err(iss->dev, "clk_enable iss_fck failed\n");
		वापस ret;
	पूर्ण

	ret = clk_enable(iss->iss_ctrlclk);
	अगर (ret) अणु
		dev_err(iss->dev, "clk_enable iss_ctrlclk failed\n");
		clk_disable(iss->iss_fck);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * iss_disable_घड़ीs - Disable ISS घड़ीs
 * @iss: OMAP4 ISS device
 */
अटल व्योम iss_disable_घड़ीs(काष्ठा iss_device *iss)
अणु
	clk_disable(iss->iss_ctrlclk);
	clk_disable(iss->iss_fck);
पूर्ण

अटल पूर्णांक iss_get_घड़ीs(काष्ठा iss_device *iss)
अणु
	iss->iss_fck = devm_clk_get(iss->dev, "iss_fck");
	अगर (IS_ERR(iss->iss_fck)) अणु
		dev_err(iss->dev, "Unable to get iss_fck clock info\n");
		वापस PTR_ERR(iss->iss_fck);
	पूर्ण

	iss->iss_ctrlclk = devm_clk_get(iss->dev, "iss_ctrlclk");
	अगर (IS_ERR(iss->iss_ctrlclk)) अणु
		dev_err(iss->dev, "Unable to get iss_ctrlclk clock info\n");
		वापस PTR_ERR(iss->iss_ctrlclk);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * omap4iss_get - Acquire the ISS resource.
 *
 * Initializes the घड़ीs क्रम the first acquire.
 *
 * Increment the reference count on the ISS. If the first reference is taken,
 * enable घड़ीs and घातer-up all submodules.
 *
 * Return a poपूर्णांकer to the ISS device काष्ठाure, or शून्य अगर an error occurred.
 */
काष्ठा iss_device *omap4iss_get(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_device *__iss = iss;

	अगर (!iss)
		वापस शून्य;

	mutex_lock(&iss->iss_mutex);
	अगर (iss->ref_count > 0)
		जाओ out;

	अगर (iss_enable_घड़ीs(iss) < 0) अणु
		__iss = शून्य;
		जाओ out;
	पूर्ण

	iss_enable_पूर्णांकerrupts(iss);

out:
	अगर (__iss)
		iss->ref_count++;
	mutex_unlock(&iss->iss_mutex);

	वापस __iss;
पूर्ण

/*
 * omap4iss_put - Release the ISS
 *
 * Decrement the reference count on the ISS. If the last reference is released,
 * घातer-करोwn all submodules, disable घड़ीs and मुक्त temporary buffers.
 */
व्योम omap4iss_put(काष्ठा iss_device *iss)
अणु
	अगर (!iss)
		वापस;

	mutex_lock(&iss->iss_mutex);
	WARN_ON(iss->ref_count == 0);
	अगर (--iss->ref_count == 0) अणु
		iss_disable_पूर्णांकerrupts(iss);
		/* Reset the ISS अगर an entity has failed to stop. This is the
		 * only way to recover from such conditions, although it would
		 * be worth investigating whether resetting the ISP only can't
		 * fix the problem in some हालs.
		 */
		अगर (!media_entity_क्रमागत_empty(&iss->crashed))
			iss_reset(iss);
		iss_disable_घड़ीs(iss);
	पूर्ण
	mutex_unlock(&iss->iss_mutex);
पूर्ण

अटल पूर्णांक iss_map_mem_resource(काष्ठा platक्रमm_device *pdev,
				काष्ठा iss_device *iss,
				क्रमागत iss_mem_resources res)
अणु
	iss->regs[res] = devm_platक्रमm_ioremap_resource(pdev, res);

	वापस PTR_ERR_OR_ZERO(iss->regs[res]);
पूर्ण

अटल व्योम iss_unरेजिस्टर_entities(काष्ठा iss_device *iss)
अणु
	omap4iss_resizer_unरेजिस्टर_entities(&iss->resizer);
	omap4iss_ipipe_unरेजिस्टर_entities(&iss->ipipe);
	omap4iss_ipipeअगर_unरेजिस्टर_entities(&iss->ipipeअगर);
	omap4iss_csi2_unरेजिस्टर_entities(&iss->csi2a);
	omap4iss_csi2_unरेजिस्टर_entities(&iss->csi2b);

	v4l2_device_unरेजिस्टर(&iss->v4l2_dev);
	media_device_unरेजिस्टर(&iss->media_dev);
पूर्ण

/*
 * iss_रेजिस्टर_subdev_group - Register a group of subdevices
 * @iss: OMAP4 ISS device
 * @board_info: I2C subdevs board inक्रमmation array
 *
 * Register all I2C subdevices in the board_info array. The array must be
 * terminated by a शून्य entry, and the first entry must be the sensor.
 *
 * Return a poपूर्णांकer to the sensor media entity अगर it has been successfully
 * रेजिस्टरed, or शून्य otherwise.
 */
अटल काष्ठा v4l2_subdev *
iss_रेजिस्टर_subdev_group(काष्ठा iss_device *iss,
			  काष्ठा iss_subdev_i2c_board_info *board_info)
अणु
	काष्ठा v4l2_subdev *sensor = शून्य;
	अचिन्हित पूर्णांक first;

	अगर (!board_info->board_info)
		वापस शून्य;

	क्रम (first = 1; board_info->board_info; ++board_info, first = 0) अणु
		काष्ठा v4l2_subdev *subdev;
		काष्ठा i2c_adapter *adapter;

		adapter = i2c_get_adapter(board_info->i2c_adapter_id);
		अगर (!adapter) अणु
			dev_err(iss->dev,
				"%s: Unable to get I2C adapter %d for device %s\n",
				__func__, board_info->i2c_adapter_id,
				board_info->board_info->type);
			जारी;
		पूर्ण

		subdev = v4l2_i2c_new_subdev_board(&iss->v4l2_dev, adapter,
						   board_info->board_info, शून्य);
		अगर (!subdev) अणु
			dev_err(iss->dev, "Unable to register subdev %s\n",
				board_info->board_info->type);
			जारी;
		पूर्ण

		अगर (first)
			sensor = subdev;
	पूर्ण

	वापस sensor;
पूर्ण

अटल पूर्णांक iss_रेजिस्टर_entities(काष्ठा iss_device *iss)
अणु
	काष्ठा iss_platक्रमm_data *pdata = iss->pdata;
	काष्ठा iss_v4l2_subdevs_group *subdevs;
	पूर्णांक ret;

	iss->media_dev.dev = iss->dev;
	strscpy(iss->media_dev.model, "TI OMAP4 ISS",
		माप(iss->media_dev.model));
	iss->media_dev.hw_revision = iss->revision;
	iss->media_dev.ops = &iss_media_ops;
	ret = media_device_रेजिस्टर(&iss->media_dev);
	अगर (ret < 0) अणु
		dev_err(iss->dev, "Media device registration failed (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	iss->v4l2_dev.mdev = &iss->media_dev;
	ret = v4l2_device_रेजिस्टर(iss->dev, &iss->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(iss->dev, "V4L2 device registration failed (%d)\n",
			ret);
		जाओ करोne;
	पूर्ण

	/* Register पूर्णांकernal entities */
	ret = omap4iss_csi2_रेजिस्टर_entities(&iss->csi2a, &iss->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap4iss_csi2_रेजिस्टर_entities(&iss->csi2b, &iss->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap4iss_ipipeअगर_रेजिस्टर_entities(&iss->ipipeअगर, &iss->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap4iss_ipipe_रेजिस्टर_entities(&iss->ipipe, &iss->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = omap4iss_resizer_रेजिस्टर_entities(&iss->resizer, &iss->v4l2_dev);
	अगर (ret < 0)
		जाओ करोne;

	/* Register बाह्यal entities */
	क्रम (subdevs = pdata->subdevs; subdevs && subdevs->subdevs; ++subdevs) अणु
		काष्ठा v4l2_subdev *sensor;
		काष्ठा media_entity *input;
		अचिन्हित पूर्णांक flags;
		अचिन्हित पूर्णांक pad;

		sensor = iss_रेजिस्टर_subdev_group(iss, subdevs->subdevs);
		अगर (!sensor)
			जारी;

		sensor->host_priv = subdevs;

		/* Connect the sensor to the correct पूर्णांकerface module.
		 * CSI2a receiver through CSIPHY1, or
		 * CSI2b receiver through CSIPHY2
		 */
		चयन (subdevs->पूर्णांकerface) अणु
		हाल ISS_INTERFACE_CSI2A_PHY1:
			input = &iss->csi2a.subdev.entity;
			pad = CSI2_PAD_SINK;
			flags = MEDIA_LNK_FL_IMMUTABLE
			      | MEDIA_LNK_FL_ENABLED;
			अवरोध;

		हाल ISS_INTERFACE_CSI2B_PHY2:
			input = &iss->csi2b.subdev.entity;
			pad = CSI2_PAD_SINK;
			flags = MEDIA_LNK_FL_IMMUTABLE
			      | MEDIA_LNK_FL_ENABLED;
			अवरोध;

		शेष:
			dev_err(iss->dev, "invalid interface type %u\n",
				subdevs->पूर्णांकerface);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		ret = media_create_pad_link(&sensor->entity, 0, input, pad,
					    flags);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&iss->v4l2_dev);

करोne:
	अगर (ret < 0)
		iss_unरेजिस्टर_entities(iss);

	वापस ret;
पूर्ण

/*
 * iss_create_links() - Pads links creation क्रम the subdevices
 * @iss : Poपूर्णांकer to ISS device
 *
 * वापस negative error code or zero on success
 */
अटल पूर्णांक iss_create_links(काष्ठा iss_device *iss)
अणु
	पूर्णांक ret;

	ret = omap4iss_csi2_create_links(iss);
	अगर (ret < 0) अणु
		dev_err(iss->dev, "CSI2 pads links creation failed\n");
		वापस ret;
	पूर्ण

	ret = omap4iss_ipipeअगर_create_links(iss);
	अगर (ret < 0) अणु
		dev_err(iss->dev, "ISP IPIPEIF pads links creation failed\n");
		वापस ret;
	पूर्ण

	ret = omap4iss_resizer_create_links(iss);
	अगर (ret < 0) अणु
		dev_err(iss->dev, "ISP RESIZER pads links creation failed\n");
		वापस ret;
	पूर्ण

	/* Connect the submodules. */
	ret = media_create_pad_link(
			&iss->csi2a.subdev.entity, CSI2_PAD_SOURCE,
			&iss->ipipeअगर.subdev.entity, IPIPEIF_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&iss->csi2b.subdev.entity, CSI2_PAD_SOURCE,
			&iss->ipipeअगर.subdev.entity, IPIPEIF_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&iss->ipipeअगर.subdev.entity, IPIPEIF_PAD_SOURCE_VP,
			&iss->resizer.subdev.entity, RESIZER_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&iss->ipipeअगर.subdev.entity, IPIPEIF_PAD_SOURCE_VP,
			&iss->ipipe.subdev.entity, IPIPE_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = media_create_pad_link(
			&iss->ipipe.subdev.entity, IPIPE_PAD_SOURCE_VP,
			&iss->resizer.subdev.entity, RESIZER_PAD_SINK, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण;

अटल व्योम iss_cleanup_modules(काष्ठा iss_device *iss)
अणु
	omap4iss_csi2_cleanup(iss);
	omap4iss_ipipeअगर_cleanup(iss);
	omap4iss_ipipe_cleanup(iss);
	omap4iss_resizer_cleanup(iss);
पूर्ण

अटल पूर्णांक iss_initialize_modules(काष्ठा iss_device *iss)
अणु
	पूर्णांक ret;

	ret = omap4iss_csiphy_init(iss);
	अगर (ret < 0) अणु
		dev_err(iss->dev, "CSI PHY initialization failed\n");
		जाओ error_csiphy;
	पूर्ण

	ret = omap4iss_csi2_init(iss);
	अगर (ret < 0) अणु
		dev_err(iss->dev, "CSI2 initialization failed\n");
		जाओ error_csi2;
	पूर्ण

	ret = omap4iss_ipipeअगर_init(iss);
	अगर (ret < 0) अणु
		dev_err(iss->dev, "ISP IPIPEIF initialization failed\n");
		जाओ error_ipipeअगर;
	पूर्ण

	ret = omap4iss_ipipe_init(iss);
	अगर (ret < 0) अणु
		dev_err(iss->dev, "ISP IPIPE initialization failed\n");
		जाओ error_ipipe;
	पूर्ण

	ret = omap4iss_resizer_init(iss);
	अगर (ret < 0) अणु
		dev_err(iss->dev, "ISP RESIZER initialization failed\n");
		जाओ error_resizer;
	पूर्ण

	वापस 0;

error_resizer:
	omap4iss_ipipe_cleanup(iss);
error_ipipe:
	omap4iss_ipipeअगर_cleanup(iss);
error_ipipeअगर:
	omap4iss_csi2_cleanup(iss);
error_csi2:
error_csiphy:
	वापस ret;
पूर्ण

अटल पूर्णांक iss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iss_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा iss_device *iss;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!pdata)
		वापस -EINVAL;

	iss = devm_kzalloc(&pdev->dev, माप(*iss), GFP_KERNEL);
	अगर (!iss)
		वापस -ENOMEM;

	mutex_init(&iss->iss_mutex);

	iss->dev = &pdev->dev;
	iss->pdata = pdata;

	iss->raw_dmamask = DMA_BIT_MASK(32);
	iss->dev->dma_mask = &iss->raw_dmamask;
	iss->dev->coherent_dma_mask = DMA_BIT_MASK(32);

	platक्रमm_set_drvdata(pdev, iss);

	/*
	 * TODO: When implementing DT support चयन to syscon regmap lookup by
	 * phandle.
	 */
	iss->syscon = syscon_regmap_lookup_by_compatible("syscon");
	अगर (IS_ERR(iss->syscon)) अणु
		ret = PTR_ERR(iss->syscon);
		जाओ error;
	पूर्ण

	/* Clocks */
	ret = iss_map_mem_resource(pdev, iss, OMAP4_ISS_MEM_TOP);
	अगर (ret < 0)
		जाओ error;

	ret = iss_get_घड़ीs(iss);
	अगर (ret < 0)
		जाओ error;

	अगर (!omap4iss_get(iss)) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	ret = iss_reset(iss);
	अगर (ret < 0)
		जाओ error_iss;

	iss->revision = iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_TOP, ISS_HL_REVISION);
	dev_info(iss->dev, "Revision %08x found\n", iss->revision);

	क्रम (i = 1; i < OMAP4_ISS_MEM_LAST; i++) अणु
		ret = iss_map_mem_resource(pdev, iss, i);
		अगर (ret)
			जाओ error_iss;
	पूर्ण

	/* Configure BTE BW_LIMITER field to max recommended value (1 GB) */
	iss_reg_update(iss, OMAP4_ISS_MEM_BTE, BTE_CTRL,
		       BTE_CTRL_BW_LIMITER_MASK,
		       18 << BTE_CTRL_BW_LIMITER_SHIFT);

	/* Perक्रमm ISP reset */
	ret = omap4iss_subclk_enable(iss, OMAP4_ISS_SUBCLK_ISP);
	अगर (ret < 0)
		जाओ error_iss;

	ret = iss_isp_reset(iss);
	अगर (ret < 0)
		जाओ error_iss;

	dev_info(iss->dev, "ISP Revision %08x found\n",
		 iss_reg_पढ़ो(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_REVISION));

	/* Interrupt */
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret <= 0) अणु
		ret = -ENODEV;
		जाओ error_iss;
	पूर्ण
	iss->irq_num = ret;

	अगर (devm_request_irq(iss->dev, iss->irq_num, iss_isr, IRQF_SHARED,
			     "OMAP4 ISS", iss)) अणु
		dev_err(iss->dev, "Unable to request IRQ\n");
		ret = -EINVAL;
		जाओ error_iss;
	पूर्ण

	/* Entities */
	ret = iss_initialize_modules(iss);
	अगर (ret < 0)
		जाओ error_iss;

	ret = iss_रेजिस्टर_entities(iss);
	अगर (ret < 0)
		जाओ error_modules;

	ret = media_entity_क्रमागत_init(&iss->crashed, &iss->media_dev);
	अगर (ret)
		जाओ error_entities;

	ret = iss_create_links(iss);
	अगर (ret < 0)
		जाओ error_entities;

	omap4iss_put(iss);

	वापस 0;

error_entities:
	iss_unरेजिस्टर_entities(iss);
	media_entity_क्रमागत_cleanup(&iss->crashed);
error_modules:
	iss_cleanup_modules(iss);
error_iss:
	omap4iss_put(iss);
error:
	mutex_destroy(&iss->iss_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक iss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iss_device *iss = platक्रमm_get_drvdata(pdev);

	iss_unरेजिस्टर_entities(iss);
	media_entity_क्रमागत_cleanup(&iss->crashed);
	iss_cleanup_modules(iss);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id omap4iss_id_table[] = अणु
	अणु "omap4iss", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, omap4iss_id_table);

अटल काष्ठा platक्रमm_driver iss_driver = अणु
	.probe		= iss_probe,
	.हटाओ		= iss_हटाओ,
	.id_table	= omap4iss_id_table,
	.driver = अणु
		.name	= "omap4iss",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(iss_driver);

MODULE_DESCRIPTION("TI OMAP4 ISS driver");
MODULE_AUTHOR("Sergio Aguirre <sergio.a.aguirre@gmail.com>");
MODULE_LICENSE("GPL");
