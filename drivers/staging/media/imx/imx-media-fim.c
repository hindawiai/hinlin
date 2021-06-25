<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Frame Interval Monitor.
 *
 * Copyright (c) 2016 Mentor Graphics Inc.
 */
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/imx.h>
#समावेश "imx-media.h"

क्रमागत अणु
	FIM_CL_ENABLE = 0,
	FIM_CL_NUM,
	FIM_CL_TOLERANCE_MIN,
	FIM_CL_TOLERANCE_MAX,
	FIM_CL_NUM_SKIP,
	FIM_NUM_CONTROLS,
पूर्ण;

क्रमागत अणु
	FIM_CL_ICAP_EDGE = 0,
	FIM_CL_ICAP_CHANNEL,
	FIM_NUM_ICAP_CONTROLS,
पूर्ण;

#घोषणा FIM_CL_ENABLE_DEF          0 /* FIM disabled by शेष */
#घोषणा FIM_CL_NUM_DEF             8 /* average 8 frames */
#घोषणा FIM_CL_NUM_SKIP_DEF        2 /* skip 2 frames after restart */
#घोषणा FIM_CL_TOLERANCE_MIN_DEF  50 /* usec */
#घोषणा FIM_CL_TOLERANCE_MAX_DEF   0 /* no max tolerance (unbounded) */

काष्ठा imx_media_fim अणु
	/* the owning subdev of this fim instance */
	काष्ठा v4l2_subdev *sd;

	/* FIM's control handler */
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	/* control clusters */
	काष्ठा v4l2_ctrl  *ctrl[FIM_NUM_CONTROLS];
	काष्ठा v4l2_ctrl  *icap_ctrl[FIM_NUM_ICAP_CONTROLS];

	spinlock_t        lock; /* protect control values */

	/* current control values */
	bool              enabled;
	पूर्णांक               num_avg;
	पूर्णांक               num_skip;
	अचिन्हित दीर्घ     tolerance_min; /* usec */
	अचिन्हित दीर्घ     tolerance_max; /* usec */
	/* input capture method of measuring FI */
	पूर्णांक               icap_channel;
	पूर्णांक               icap_flags;

	पूर्णांक               counter;
	kसमय_प्रकार		  last_ts;
	अचिन्हित दीर्घ     sum;       /* usec */
	अचिन्हित दीर्घ     nominal;   /* usec */

	काष्ठा completion icap_first_event;
	bool              stream_on;
पूर्ण;

#घोषणा icap_enabled(fim) ((fim)->icap_flags != IRQ_TYPE_NONE)

अटल व्योम update_fim_nominal(काष्ठा imx_media_fim *fim,
			       स्थिर काष्ठा v4l2_fract *fi)
अणु
	अगर (fi->denominator == 0) अणु
		dev_dbg(fim->sd->dev, "no frame interval, FIM disabled\n");
		fim->enabled = false;
		वापस;
	पूर्ण

	fim->nominal = DIV_ROUND_CLOSEST_ULL(1000000ULL * (u64)fi->numerator,
					     fi->denominator);

	dev_dbg(fim->sd->dev, "FI=%lu usec\n", fim->nominal);
पूर्ण

अटल व्योम reset_fim(काष्ठा imx_media_fim *fim, bool curval)
अणु
	काष्ठा v4l2_ctrl *icap_chan = fim->icap_ctrl[FIM_CL_ICAP_CHANNEL];
	काष्ठा v4l2_ctrl *icap_edge = fim->icap_ctrl[FIM_CL_ICAP_EDGE];
	काष्ठा v4l2_ctrl *en = fim->ctrl[FIM_CL_ENABLE];
	काष्ठा v4l2_ctrl *num = fim->ctrl[FIM_CL_NUM];
	काष्ठा v4l2_ctrl *skip = fim->ctrl[FIM_CL_NUM_SKIP];
	काष्ठा v4l2_ctrl *tol_min = fim->ctrl[FIM_CL_TOLERANCE_MIN];
	काष्ठा v4l2_ctrl *tol_max = fim->ctrl[FIM_CL_TOLERANCE_MAX];

	अगर (curval) अणु
		fim->enabled = en->cur.val;
		fim->icap_flags = icap_edge->cur.val;
		fim->icap_channel = icap_chan->cur.val;
		fim->num_avg = num->cur.val;
		fim->num_skip = skip->cur.val;
		fim->tolerance_min = tol_min->cur.val;
		fim->tolerance_max = tol_max->cur.val;
	पूर्ण अन्यथा अणु
		fim->enabled = en->val;
		fim->icap_flags = icap_edge->val;
		fim->icap_channel = icap_chan->val;
		fim->num_avg = num->val;
		fim->num_skip = skip->val;
		fim->tolerance_min = tol_min->val;
		fim->tolerance_max = tol_max->val;
	पूर्ण

	/* disable tolerance range अगर max <= min */
	अगर (fim->tolerance_max <= fim->tolerance_min)
		fim->tolerance_max = 0;

	/* num_skip must be >= 1 अगर input capture not used */
	अगर (!icap_enabled(fim))
		fim->num_skip = max_t(पूर्णांक, fim->num_skip, 1);

	fim->counter = -fim->num_skip;
	fim->sum = 0;
पूर्ण

अटल व्योम send_fim_event(काष्ठा imx_media_fim *fim, अचिन्हित दीर्घ error)
अणु
	अटल स्थिर काष्ठा v4l2_event ev = अणु
		.type = V4L2_EVENT_IMX_FRAME_INTERVAL_ERROR,
	पूर्ण;

	v4l2_subdev_notअगरy_event(fim->sd, &ev);
पूर्ण

/*
 * Monitor an averaged frame पूर्णांकerval. If the average deviates too much
 * from the nominal frame rate, send the frame पूर्णांकerval error event. The
 * frame पूर्णांकervals are averaged in order to quiet noise from
 * (presumably अक्रमom) पूर्णांकerrupt latency.
 */
अटल व्योम frame_पूर्णांकerval_monitor(काष्ठा imx_media_fim *fim,
				   kसमय_प्रकार बारtamp)
अणु
	दीर्घ दीर्घ पूर्णांकerval, error;
	अचिन्हित दीर्घ error_avg;
	bool send_event = false;

	अगर (!fim->enabled || ++fim->counter <= 0)
		जाओ out_update_ts;

	/* max error is less than l00तगs, so use 32-bit भागision or fail */
	पूर्णांकerval = kसमय_प्रकारo_ns(kसमय_sub(बारtamp, fim->last_ts));
	error = असल(पूर्णांकerval - NSEC_PER_USEC * (u64)fim->nominal);
	अगर (error > U32_MAX)
		error = U32_MAX;
	अन्यथा
		error = असल((u32)error / NSEC_PER_USEC);

	अगर (fim->tolerance_max && error >= fim->tolerance_max) अणु
		dev_dbg(fim->sd->dev,
			"FIM: %llu ignored, out of tolerance bounds\n",
			error);
		fim->counter--;
		जाओ out_update_ts;
	पूर्ण

	fim->sum += error;

	अगर (fim->counter == fim->num_avg) अणु
		error_avg = DIV_ROUND_CLOSEST(fim->sum, fim->num_avg);

		अगर (error_avg > fim->tolerance_min)
			send_event = true;

		dev_dbg(fim->sd->dev, "FIM: error: %lu usec%s\n",
			error_avg, send_event ? " (!!!)" : "");

		fim->counter = 0;
		fim->sum = 0;
	पूर्ण

out_update_ts:
	fim->last_ts = बारtamp;
	अगर (send_event)
		send_fim_event(fim, error_avg);
पूर्ण

#अगर_घोषित CONFIG_IMX_GPT_ICAP
/*
 * Input Capture method of measuring frame पूर्णांकervals. Not subject
 * to पूर्णांकerrupt latency.
 */
अटल व्योम fim_input_capture_handler(पूर्णांक channel, व्योम *dev_id,
				      kसमय_प्रकार बारtamp)
अणु
	काष्ठा imx_media_fim *fim = dev_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fim->lock, flags);

	frame_पूर्णांकerval_monitor(fim, बारtamp);

	अगर (!completion_करोne(&fim->icap_first_event))
		complete(&fim->icap_first_event);

	spin_unlock_irqrestore(&fim->lock, flags);
पूर्ण

अटल पूर्णांक fim_request_input_capture(काष्ठा imx_media_fim *fim)
अणु
	init_completion(&fim->icap_first_event);

	वापस mxc_request_input_capture(fim->icap_channel,
					 fim_input_capture_handler,
					 fim->icap_flags, fim);
पूर्ण

अटल व्योम fim_मुक्त_input_capture(काष्ठा imx_media_fim *fim)
अणु
	mxc_मुक्त_input_capture(fim->icap_channel, fim);
पूर्ण

#अन्यथा /* CONFIG_IMX_GPT_ICAP */

अटल पूर्णांक fim_request_input_capture(काष्ठा imx_media_fim *fim)
अणु
	वापस 0;
पूर्ण

अटल व्योम fim_मुक्त_input_capture(काष्ठा imx_media_fim *fim)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_IMX_GPT_ICAP */

/*
 * In हाल we are monitoring the first frame पूर्णांकerval after streamon
 * (when fim->num_skip = 0), we need a valid fim->last_ts beक्रमe we
 * can begin. This only applies to the input capture method. It is not
 * possible to accurately measure the first FI after streamon using the
 * खातापूर्ण method, so fim->num_skip minimum is set to 1 in that हाल, so this
 * function is a noop when the खातापूर्ण method is used.
 */
अटल व्योम fim_acquire_first_ts(काष्ठा imx_media_fim *fim)
अणु
	अचिन्हित दीर्घ ret;

	अगर (!fim->enabled || fim->num_skip > 0)
		वापस;

	ret = रुको_क्रम_completion_समयout(
		&fim->icap_first_event,
		msecs_to_jअगरfies(IMX_MEDIA_खातापूर्ण_TIMEOUT));
	अगर (ret == 0)
		v4l2_warn(fim->sd, "wait first icap event timeout\n");
पूर्ण

/* FIM Controls */
अटल पूर्णांक fim_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा imx_media_fim *fim = container_of(ctrl->handler,
						 काष्ठा imx_media_fim,
						 ctrl_handler);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&fim->lock, flags);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_IMX_FIM_ENABLE:
		अवरोध;
	हाल V4L2_CID_IMX_FIM_ICAP_EDGE:
		अगर (fim->stream_on)
			ret = -EBUSY;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (!ret)
		reset_fim(fim, false);

	spin_unlock_irqrestore(&fim->lock, flags);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops fim_ctrl_ops = अणु
	.s_ctrl = fim_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config fim_ctrl[] = अणु
	[FIM_CL_ENABLE] = अणु
		.ops = &fim_ctrl_ops,
		.id = V4L2_CID_IMX_FIM_ENABLE,
		.name = "FIM Enable",
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.def = FIM_CL_ENABLE_DEF,
		.min = 0,
		.max = 1,
		.step = 1,
	पूर्ण,
	[FIM_CL_NUM] = अणु
		.ops = &fim_ctrl_ops,
		.id = V4L2_CID_IMX_FIM_NUM,
		.name = "FIM Num Average",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.def = FIM_CL_NUM_DEF,
		.min =  1, /* no averaging */
		.max = 64, /* average 64 frames */
		.step = 1,
	पूर्ण,
	[FIM_CL_TOLERANCE_MIN] = अणु
		.ops = &fim_ctrl_ops,
		.id = V4L2_CID_IMX_FIM_TOLERANCE_MIN,
		.name = "FIM Tolerance Min",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.def = FIM_CL_TOLERANCE_MIN_DEF,
		.min =    2,
		.max =  200,
		.step =   1,
	पूर्ण,
	[FIM_CL_TOLERANCE_MAX] = अणु
		.ops = &fim_ctrl_ops,
		.id = V4L2_CID_IMX_FIM_TOLERANCE_MAX,
		.name = "FIM Tolerance Max",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.def = FIM_CL_TOLERANCE_MAX_DEF,
		.min =    0,
		.max =  500,
		.step =   1,
	पूर्ण,
	[FIM_CL_NUM_SKIP] = अणु
		.ops = &fim_ctrl_ops,
		.id = V4L2_CID_IMX_FIM_NUM_SKIP,
		.name = "FIM Num Skip",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.def = FIM_CL_NUM_SKIP_DEF,
		.min =   0, /* skip no frames */
		.max = 256, /* skip 256 frames */
		.step =  1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config fim_icap_ctrl[] = अणु
	[FIM_CL_ICAP_EDGE] = अणु
		.ops = &fim_ctrl_ops,
		.id = V4L2_CID_IMX_FIM_ICAP_EDGE,
		.name = "FIM Input Capture Edge",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.def =  IRQ_TYPE_NONE, /* input capture disabled by शेष */
		.min =  IRQ_TYPE_NONE,
		.max =  IRQ_TYPE_EDGE_BOTH,
		.step = 1,
	पूर्ण,
	[FIM_CL_ICAP_CHANNEL] = अणु
		.ops = &fim_ctrl_ops,
		.id = V4L2_CID_IMX_FIM_ICAP_CHANNEL,
		.name = "FIM Input Capture Channel",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.def =  0,
		.min =  0,
		.max =  1,
		.step = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक init_fim_controls(काष्ठा imx_media_fim *fim)
अणु
	काष्ठा v4l2_ctrl_handler *hdlr = &fim->ctrl_handler;
	पूर्णांक i, ret;

	v4l2_ctrl_handler_init(hdlr, FIM_NUM_CONTROLS + FIM_NUM_ICAP_CONTROLS);

	क्रम (i = 0; i < FIM_NUM_CONTROLS; i++)
		fim->ctrl[i] = v4l2_ctrl_new_custom(hdlr,
						    &fim_ctrl[i],
						    शून्य);
	क्रम (i = 0; i < FIM_NUM_ICAP_CONTROLS; i++)
		fim->icap_ctrl[i] = v4l2_ctrl_new_custom(hdlr,
							 &fim_icap_ctrl[i],
							 शून्य);
	अगर (hdlr->error) अणु
		ret = hdlr->error;
		जाओ err_मुक्त;
	पूर्ण

	v4l2_ctrl_cluster(FIM_NUM_CONTROLS, fim->ctrl);
	v4l2_ctrl_cluster(FIM_NUM_ICAP_CONTROLS, fim->icap_ctrl);

	वापस 0;
err_मुक्त:
	v4l2_ctrl_handler_मुक्त(hdlr);
	वापस ret;
पूर्ण

/*
 * Monitor frame पूर्णांकervals via खातापूर्ण पूर्णांकerrupt. This method is
 * subject to uncertaपूर्णांकy errors पूर्णांकroduced by पूर्णांकerrupt latency.
 *
 * This is a noop अगर the Input Capture method is being used, since
 * the frame_पूर्णांकerval_monitor() is called by the input capture event
 * callback handler in that हाल.
 */
व्योम imx_media_fim_eof_monitor(काष्ठा imx_media_fim *fim, kसमय_प्रकार बारtamp)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fim->lock, flags);

	अगर (!icap_enabled(fim))
		frame_पूर्णांकerval_monitor(fim, बारtamp);

	spin_unlock_irqrestore(&fim->lock, flags);
पूर्ण

/* Called by the subdev in its s_stream callback */
पूर्णांक imx_media_fim_set_stream(काष्ठा imx_media_fim *fim,
			     स्थिर काष्ठा v4l2_fract *fi,
			     bool on)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	v4l2_ctrl_lock(fim->ctrl[FIM_CL_ENABLE]);

	अगर (fim->stream_on == on)
		जाओ out;

	अगर (on) अणु
		spin_lock_irqsave(&fim->lock, flags);
		reset_fim(fim, true);
		update_fim_nominal(fim, fi);
		spin_unlock_irqrestore(&fim->lock, flags);

		अगर (icap_enabled(fim)) अणु
			ret = fim_request_input_capture(fim);
			अगर (ret)
				जाओ out;
			fim_acquire_first_ts(fim);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (icap_enabled(fim))
			fim_मुक्त_input_capture(fim);
	पूर्ण

	fim->stream_on = on;
out:
	v4l2_ctrl_unlock(fim->ctrl[FIM_CL_ENABLE]);
	वापस ret;
पूर्ण

पूर्णांक imx_media_fim_add_controls(काष्ठा imx_media_fim *fim)
अणु
	/* add the FIM controls to the calling subdev ctrl handler */
	वापस v4l2_ctrl_add_handler(fim->sd->ctrl_handler,
				     &fim->ctrl_handler, शून्य, false);
पूर्ण

/* Called by the subdev in its subdev रेजिस्टरed callback */
काष्ठा imx_media_fim *imx_media_fim_init(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा imx_media_fim *fim;
	पूर्णांक ret;

	fim = devm_kzalloc(sd->dev, माप(*fim), GFP_KERNEL);
	अगर (!fim)
		वापस ERR_PTR(-ENOMEM);

	fim->sd = sd;

	spin_lock_init(&fim->lock);

	ret = init_fim_controls(fim);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस fim;
पूर्ण

व्योम imx_media_fim_मुक्त(काष्ठा imx_media_fim *fim)
अणु
	v4l2_ctrl_handler_मुक्त(&fim->ctrl_handler);
पूर्ण
