<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hantro VPU codec driver
 *
 * Copyright (C) 2018 Collabora, Ltd.
 * Copyright 2018 Google LLC.
 *	Tomasz Figa <tfiga@chromium.org>
 *
 * Based on s5p-mfc driver by Samsung Electronics Co., Ltd.
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/workqueue.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "hantro_v4l2.h"
#समावेश "hantro.h"
#समावेश "hantro_hw.h"

#घोषणा DRIVER_NAME "hantro-vpu"

पूर्णांक hantro_debug;
module_param_named(debug, hantro_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
		 "Debug level - higher value produces more verbose messages");

व्योम *hantro_get_ctrl(काष्ठा hantro_ctx *ctx, u32 id)
अणु
	काष्ठा v4l2_ctrl *ctrl;

	ctrl = v4l2_ctrl_find(&ctx->ctrl_handler, id);
	वापस ctrl ? ctrl->p_cur.p : शून्य;
पूर्ण

dma_addr_t hantro_get_ref(काष्ठा hantro_ctx *ctx, u64 ts)
अणु
	काष्ठा vb2_queue *q = v4l2_m2m_get_dst_vq(ctx->fh.m2m_ctx);
	काष्ठा vb2_buffer *buf;
	पूर्णांक index;

	index = vb2_find_बारtamp(q, ts, 0);
	अगर (index < 0)
		वापस 0;
	buf = vb2_get_buffer(q, index);
	वापस hantro_get_dec_buf_addr(ctx, buf);
पूर्ण

अटल व्योम hantro_job_finish(काष्ठा hantro_dev *vpu,
			      काष्ठा hantro_ctx *ctx,
			      क्रमागत vb2_buffer_state result)
अणु
	काष्ठा vb2_v4l2_buffer *src, *dst;

	pm_runसमय_mark_last_busy(vpu->dev);
	pm_runसमय_put_स्वतःsuspend(vpu->dev);
	clk_bulk_disable(vpu->variant->num_घड़ीs, vpu->घड़ीs);

	src = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	अगर (WARN_ON(!src))
		वापस;
	अगर (WARN_ON(!dst))
		वापस;

	src->sequence = ctx->sequence_out++;
	dst->sequence = ctx->sequence_cap++;

	v4l2_m2m_buf_करोne_and_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx,
					 result);
पूर्ण

व्योम hantro_irq_करोne(काष्ठा hantro_dev *vpu,
		     क्रमागत vb2_buffer_state result)
अणु
	काष्ठा hantro_ctx *ctx =
		v4l2_m2m_get_curr_priv(vpu->m2m_dev);

	/*
	 * If cancel_delayed_work वापसs false
	 * the समयout expired. The watchकरोg is running,
	 * and will take care of finishing the job.
	 */
	अगर (cancel_delayed_work(&vpu->watchकरोg_work)) अणु
		अगर (result == VB2_BUF_STATE_DONE && ctx->codec_ops->करोne)
			ctx->codec_ops->करोne(ctx);
		hantro_job_finish(vpu, ctx, result);
	पूर्ण
पूर्ण

व्योम hantro_watchकरोg(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hantro_dev *vpu;
	काष्ठा hantro_ctx *ctx;

	vpu = container_of(to_delayed_work(work),
			   काष्ठा hantro_dev, watchकरोg_work);
	ctx = v4l2_m2m_get_curr_priv(vpu->m2m_dev);
	अगर (ctx) अणु
		vpu_err("frame processing timed out!\n");
		ctx->codec_ops->reset(ctx);
		hantro_job_finish(vpu, ctx, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

व्योम hantro_start_prepare_run(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा vb2_v4l2_buffer *src_buf;

	src_buf = hantro_get_src_buf(ctx);
	v4l2_ctrl_request_setup(src_buf->vb2_buf.req_obj.req,
				&ctx->ctrl_handler);

	अगर (!ctx->is_encoder) अणु
		अगर (hantro_needs_postproc(ctx, ctx->vpu_dst_fmt))
			hantro_postproc_enable(ctx);
		अन्यथा
			hantro_postproc_disable(ctx);
	पूर्ण
पूर्ण

व्योम hantro_end_prepare_run(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा vb2_v4l2_buffer *src_buf;

	src_buf = hantro_get_src_buf(ctx);
	v4l2_ctrl_request_complete(src_buf->vb2_buf.req_obj.req,
				   &ctx->ctrl_handler);

	/* Kick the watchकरोg. */
	schedule_delayed_work(&ctx->dev->watchकरोg_work,
			      msecs_to_jअगरfies(2000));
पूर्ण

अटल व्योम device_run(व्योम *priv)
अणु
	काष्ठा hantro_ctx *ctx = priv;
	काष्ठा vb2_v4l2_buffer *src, *dst;
	पूर्णांक ret;

	src = hantro_get_src_buf(ctx);
	dst = hantro_get_dst_buf(ctx);

	ret = clk_bulk_enable(ctx->dev->variant->num_घड़ीs, ctx->dev->घड़ीs);
	अगर (ret)
		जाओ err_cancel_job;
	ret = pm_runसमय_get_sync(ctx->dev->dev);
	अगर (ret < 0)
		जाओ err_cancel_job;

	v4l2_m2m_buf_copy_metadata(src, dst, true);

	ctx->codec_ops->run(ctx);
	वापस;

err_cancel_job:
	hantro_job_finish(ctx->dev, ctx, VB2_BUF_STATE_ERROR);
पूर्ण

अटल काष्ठा v4l2_m2m_ops vpu_m2m_ops = अणु
	.device_run = device_run,
पूर्ण;

अटल पूर्णांक
queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq, काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा hantro_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->ops = &hantro_queue_ops;
	src_vq->mem_ops = &vb2_dma_contig_memops;

	/*
	 * Driver करोes mostly sequential access, so sacrअगरice TLB efficiency
	 * क्रम faster allocation. Also, no CPU access on the source queue,
	 * so no kernel mapping needed.
	 */
	src_vq->dma_attrs = DMA_ATTR_ALLOC_SINGLE_PAGES |
			    DMA_ATTR_NO_KERNEL_MAPPING;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->dev->vpu_mutex;
	src_vq->dev = ctx->dev->v4l2_dev.dev;
	src_vq->supports_requests = true;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	/*
	 * When encoding, the CAPTURE queue करोesn't need dma memory,
	 * as the CPU needs to create the JPEG frames, from the
	 * hardware-produced JPEG payload.
	 *
	 * For the DMA destination buffer, we use a bounce buffer.
	 */
	अगर (ctx->is_encoder) अणु
		dst_vq->mem_ops = &vb2_vदो_स्मृति_memops;
	पूर्ण अन्यथा अणु
		dst_vq->bidirectional = true;
		dst_vq->mem_ops = &vb2_dma_contig_memops;
		dst_vq->dma_attrs = DMA_ATTR_ALLOC_SINGLE_PAGES |
				    DMA_ATTR_NO_KERNEL_MAPPING;
	पूर्ण

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->ops = &hantro_queue_ops;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->dev->vpu_mutex;
	dst_vq->dev = ctx->dev->v4l2_dev.dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक hantro_try_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	अगर (ctrl->id == V4L2_CID_STATELESS_H264_SPS) अणु
		स्थिर काष्ठा v4l2_ctrl_h264_sps *sps = ctrl->p_new.p_h264_sps;

		अगर (sps->chroma_क्रमmat_idc > 1)
			/* Only 4:0:0 and 4:2:0 are supported */
			वापस -EINVAL;
		अगर (sps->bit_depth_luma_minus8 != sps->bit_depth_chroma_minus8)
			/* Luma and chroma bit depth mismatch */
			वापस -EINVAL;
		अगर (sps->bit_depth_luma_minus8 != 0)
			/* Only 8-bit is supported */
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hantro_jpeg_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा hantro_ctx *ctx;

	ctx = container_of(ctrl->handler,
			   काष्ठा hantro_ctx, ctrl_handler);

	vpu_debug(1, "s_ctrl: id = %d, val = %d\n", ctrl->id, ctrl->val);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		ctx->jpeg_quality = ctrl->val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops hantro_ctrl_ops = अणु
	.try_ctrl = hantro_try_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops hantro_jpeg_ctrl_ops = अणु
	.s_ctrl = hantro_jpeg_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा hantro_ctrl controls[] = अणु
	अणु
		.codec = HANTRO_JPEG_ENCODER,
		.cfg = अणु
			.id = V4L2_CID_JPEG_COMPRESSION_QUALITY,
			.min = 5,
			.max = 100,
			.step = 1,
			.def = 50,
			.ops = &hantro_jpeg_ctrl_ops,
		पूर्ण,
	पूर्ण, अणु
		.codec = HANTRO_MPEG2_DECODER,
		.cfg = अणु
			.id = V4L2_CID_MPEG_VIDEO_MPEG2_SLICE_PARAMS,
		पूर्ण,
	पूर्ण, अणु
		.codec = HANTRO_MPEG2_DECODER,
		.cfg = अणु
			.id = V4L2_CID_MPEG_VIDEO_MPEG2_QUANTIZATION,
		पूर्ण,
	पूर्ण, अणु
		.codec = HANTRO_VP8_DECODER,
		.cfg = अणु
			.id = V4L2_CID_STATELESS_VP8_FRAME,
		पूर्ण,
	पूर्ण, अणु
		.codec = HANTRO_H264_DECODER,
		.cfg = अणु
			.id = V4L2_CID_STATELESS_H264_DECODE_PARAMS,
		पूर्ण,
	पूर्ण, अणु
		.codec = HANTRO_H264_DECODER,
		.cfg = अणु
			.id = V4L2_CID_STATELESS_H264_SPS,
			.ops = &hantro_ctrl_ops,
		पूर्ण,
	पूर्ण, अणु
		.codec = HANTRO_H264_DECODER,
		.cfg = अणु
			.id = V4L2_CID_STATELESS_H264_PPS,
		पूर्ण,
	पूर्ण, अणु
		.codec = HANTRO_H264_DECODER,
		.cfg = अणु
			.id = V4L2_CID_STATELESS_H264_SCALING_MATRIX,
		पूर्ण,
	पूर्ण, अणु
		.codec = HANTRO_H264_DECODER,
		.cfg = अणु
			.id = V4L2_CID_STATELESS_H264_DECODE_MODE,
			.min = V4L2_STATELESS_H264_DECODE_MODE_FRAME_BASED,
			.def = V4L2_STATELESS_H264_DECODE_MODE_FRAME_BASED,
			.max = V4L2_STATELESS_H264_DECODE_MODE_FRAME_BASED,
		पूर्ण,
	पूर्ण, अणु
		.codec = HANTRO_H264_DECODER,
		.cfg = अणु
			.id = V4L2_CID_STATELESS_H264_START_CODE,
			.min = V4L2_STATELESS_H264_START_CODE_ANNEX_B,
			.def = V4L2_STATELESS_H264_START_CODE_ANNEX_B,
			.max = V4L2_STATELESS_H264_START_CODE_ANNEX_B,
		पूर्ण,
	पूर्ण, अणु
		.codec = HANTRO_H264_DECODER,
		.cfg = अणु
			.id = V4L2_CID_MPEG_VIDEO_H264_PROखाता,
			.min = V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE,
			.max = V4L2_MPEG_VIDEO_H264_PROखाता_HIGH,
			.menu_skip_mask =
			BIT(V4L2_MPEG_VIDEO_H264_PROखाता_EXTENDED),
			.def = V4L2_MPEG_VIDEO_H264_PROखाता_MAIN,
		पूर्ण
	पूर्ण, अणु
	पूर्ण,
पूर्ण;

अटल पूर्णांक hantro_ctrls_setup(काष्ठा hantro_dev *vpu,
			      काष्ठा hantro_ctx *ctx,
			      पूर्णांक allowed_codecs)
अणु
	पूर्णांक i, num_ctrls = ARRAY_SIZE(controls);

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, num_ctrls);

	क्रम (i = 0; i < num_ctrls; i++) अणु
		अगर (!(allowed_codecs & controls[i].codec))
			जारी;

		v4l2_ctrl_new_custom(&ctx->ctrl_handler,
				     &controls[i].cfg, शून्य);
		अगर (ctx->ctrl_handler.error) अणु
			vpu_err("Adding control (%d) failed %d\n",
				controls[i].cfg.id,
				ctx->ctrl_handler.error);
			v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
			वापस ctx->ctrl_handler.error;
		पूर्ण
	पूर्ण
	वापस v4l2_ctrl_handler_setup(&ctx->ctrl_handler);
पूर्ण

/*
 * V4L2 file operations.
 */

अटल पूर्णांक hantro_खोलो(काष्ठा file *filp)
अणु
	काष्ठा hantro_dev *vpu = video_drvdata(filp);
	काष्ठा video_device *vdev = video_devdata(filp);
	काष्ठा hantro_func *func = hantro_vdev_to_func(vdev);
	काष्ठा hantro_ctx *ctx;
	पूर्णांक allowed_codecs, ret;

	/*
	 * We करो not need any extra locking here, because we operate only
	 * on local data here, except पढ़ोing few fields from dev, which
	 * करो not change through device's lअगरeसमय (which is guaranteed by
	 * reference on module from खोलो()) and V4L2 पूर्णांकernal objects (such
	 * as vdev and ctx->fh), which have proper locking करोne in respective
	 * helper functions used here.
	 */

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = vpu;
	अगर (func->id == MEDIA_ENT_F_PROC_VIDEO_ENCODER) अणु
		allowed_codecs = vpu->variant->codec & HANTRO_ENCODERS;
		ctx->is_encoder = true;
	पूर्ण अन्यथा अगर (func->id == MEDIA_ENT_F_PROC_VIDEO_DECODER) अणु
		allowed_codecs = vpu->variant->codec & HANTRO_DECODERS;
		ctx->is_encoder = false;
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
		जाओ err_ctx_मुक्त;
	पूर्ण

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(vpu->m2m_dev, ctx, queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ err_ctx_मुक्त;
	पूर्ण

	v4l2_fh_init(&ctx->fh, vdev);
	filp->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	hantro_reset_fmts(ctx);

	ret = hantro_ctrls_setup(vpu, ctx, allowed_codecs);
	अगर (ret) अणु
		vpu_err("Failed to set up controls\n");
		जाओ err_fh_मुक्त;
	पूर्ण
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;

	वापस 0;

err_fh_मुक्त:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
err_ctx_मुक्त:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक hantro_release(काष्ठा file *filp)
अणु
	काष्ठा hantro_ctx *ctx =
		container_of(filp->निजी_data, काष्ठा hantro_ctx, fh);

	/*
	 * No need क्रम extra locking because this was the last reference
	 * to this file.
	 */
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	kमुक्त(ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations hantro_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = hantro_खोलो,
	.release = hantro_release,
	.poll = v4l2_m2m_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap = v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_hantro_match[] = अणु
#अगर_घोषित CONFIG_VIDEO_HANTRO_ROCKCHIP
	अणु .compatible = "rockchip,rk3399-vpu", .data = &rk3399_vpu_variant, पूर्ण,
	अणु .compatible = "rockchip,rk3328-vpu", .data = &rk3328_vpu_variant, पूर्ण,
	अणु .compatible = "rockchip,rk3288-vpu", .data = &rk3288_vpu_variant, पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_VIDEO_HANTRO_IMX8M
	अणु .compatible = "nxp,imx8mq-vpu", .data = &imx8mq_vpu_variant, पूर्ण,
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_hantro_match);

अटल पूर्णांक hantro_रेजिस्टर_entity(काष्ठा media_device *mdev,
				  काष्ठा media_entity *entity,
				  स्थिर अक्षर *entity_name,
				  काष्ठा media_pad *pads, पूर्णांक num_pads,
				  पूर्णांक function, काष्ठा video_device *vdev)
अणु
	अक्षर *name;
	पूर्णांक ret;

	entity->obj_type = MEDIA_ENTITY_TYPE_BASE;
	अगर (function == MEDIA_ENT_F_IO_V4L) अणु
		entity->info.dev.major = VIDEO_MAJOR;
		entity->info.dev.minor = vdev->minor;
	पूर्ण

	name = devm_kaप्र_लिखो(mdev->dev, GFP_KERNEL, "%s-%s", vdev->name,
			      entity_name);
	अगर (!name)
		वापस -ENOMEM;

	entity->name = name;
	entity->function = function;

	ret = media_entity_pads_init(entity, num_pads, pads);
	अगर (ret)
		वापस ret;

	ret = media_device_रेजिस्टर_entity(mdev, entity);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक hantro_attach_func(काष्ठा hantro_dev *vpu,
			      काष्ठा hantro_func *func)
अणु
	काष्ठा media_device *mdev = &vpu->mdev;
	काष्ठा media_link *link;
	पूर्णांक ret;

	/* Create the three encoder entities with their pads */
	func->source_pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = hantro_रेजिस्टर_entity(mdev, &func->vdev.entity, "source",
				     &func->source_pad, 1, MEDIA_ENT_F_IO_V4L,
				     &func->vdev);
	अगर (ret)
		वापस ret;

	func->proc_pads[0].flags = MEDIA_PAD_FL_SINK;
	func->proc_pads[1].flags = MEDIA_PAD_FL_SOURCE;
	ret = hantro_रेजिस्टर_entity(mdev, &func->proc, "proc",
				     func->proc_pads, 2, func->id,
				     &func->vdev);
	अगर (ret)
		जाओ err_rel_entity0;

	func->sink_pad.flags = MEDIA_PAD_FL_SINK;
	ret = hantro_रेजिस्टर_entity(mdev, &func->sink, "sink",
				     &func->sink_pad, 1, MEDIA_ENT_F_IO_V4L,
				     &func->vdev);
	अगर (ret)
		जाओ err_rel_entity1;

	/* Connect the three entities */
	ret = media_create_pad_link(&func->vdev.entity, 0, &func->proc, 0,
				    MEDIA_LNK_FL_IMMUTABLE |
				    MEDIA_LNK_FL_ENABLED);
	अगर (ret)
		जाओ err_rel_entity2;

	ret = media_create_pad_link(&func->proc, 1, &func->sink, 0,
				    MEDIA_LNK_FL_IMMUTABLE |
				    MEDIA_LNK_FL_ENABLED);
	अगर (ret)
		जाओ err_rm_links0;

	/* Create video पूर्णांकerface */
	func->पूर्णांकf_devnode = media_devnode_create(mdev, MEDIA_INTF_T_V4L_VIDEO,
						  0, VIDEO_MAJOR,
						  func->vdev.minor);
	अगर (!func->पूर्णांकf_devnode) अणु
		ret = -ENOMEM;
		जाओ err_rm_links1;
	पूर्ण

	/* Connect the two DMA engines to the पूर्णांकerface */
	link = media_create_पूर्णांकf_link(&func->vdev.entity,
				      &func->पूर्णांकf_devnode->पूर्णांकf,
				      MEDIA_LNK_FL_IMMUTABLE |
				      MEDIA_LNK_FL_ENABLED);
	अगर (!link) अणु
		ret = -ENOMEM;
		जाओ err_rm_devnode;
	पूर्ण

	link = media_create_पूर्णांकf_link(&func->sink, &func->पूर्णांकf_devnode->पूर्णांकf,
				      MEDIA_LNK_FL_IMMUTABLE |
				      MEDIA_LNK_FL_ENABLED);
	अगर (!link) अणु
		ret = -ENOMEM;
		जाओ err_rm_devnode;
	पूर्ण
	वापस 0;

err_rm_devnode:
	media_devnode_हटाओ(func->पूर्णांकf_devnode);

err_rm_links1:
	media_entity_हटाओ_links(&func->sink);

err_rm_links0:
	media_entity_हटाओ_links(&func->proc);
	media_entity_हटाओ_links(&func->vdev.entity);

err_rel_entity2:
	media_device_unरेजिस्टर_entity(&func->sink);

err_rel_entity1:
	media_device_unरेजिस्टर_entity(&func->proc);

err_rel_entity0:
	media_device_unरेजिस्टर_entity(&func->vdev.entity);
	वापस ret;
पूर्ण

अटल व्योम hantro_detach_func(काष्ठा hantro_func *func)
अणु
	media_devnode_हटाओ(func->पूर्णांकf_devnode);
	media_entity_हटाओ_links(&func->sink);
	media_entity_हटाओ_links(&func->proc);
	media_entity_हटाओ_links(&func->vdev.entity);
	media_device_unरेजिस्टर_entity(&func->sink);
	media_device_unरेजिस्टर_entity(&func->proc);
	media_device_unरेजिस्टर_entity(&func->vdev.entity);
पूर्ण

अटल पूर्णांक hantro_add_func(काष्ठा hantro_dev *vpu, अचिन्हित पूर्णांक funcid)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा hantro_func *func;
	काष्ठा video_device *vfd;
	पूर्णांक ret;

	match = of_match_node(of_hantro_match, vpu->dev->of_node);
	func = devm_kzalloc(vpu->dev, माप(*func), GFP_KERNEL);
	अगर (!func) अणु
		v4l2_err(&vpu->v4l2_dev, "Failed to allocate video device\n");
		वापस -ENOMEM;
	पूर्ण

	func->id = funcid;

	vfd = &func->vdev;
	vfd->fops = &hantro_fops;
	vfd->release = video_device_release_empty;
	vfd->lock = &vpu->vpu_mutex;
	vfd->v4l2_dev = &vpu->v4l2_dev;
	vfd->vfl_dir = VFL_सूची_M2M;
	vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M_MPLANE;
	vfd->ioctl_ops = &hantro_ioctl_ops;
	snम_लिखो(vfd->name, माप(vfd->name), "%s-%s", match->compatible,
		 funcid == MEDIA_ENT_F_PROC_VIDEO_ENCODER ? "enc" : "dec");

	अगर (funcid == MEDIA_ENT_F_PROC_VIDEO_ENCODER)
		vpu->encoder = func;
	अन्यथा
		vpu->decoder = func;

	video_set_drvdata(vfd, vpu);

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(&vpu->v4l2_dev, "Failed to register video device\n");
		वापस ret;
	पूर्ण

	ret = hantro_attach_func(vpu, func);
	अगर (ret) अणु
		v4l2_err(&vpu->v4l2_dev,
			 "Failed to attach functionality to the media device\n");
		जाओ err_unreg_dev;
	पूर्ण

	v4l2_info(&vpu->v4l2_dev, "registered %s as /dev/video%d\n", vfd->name,
		  vfd->num);

	वापस 0;

err_unreg_dev:
	video_unरेजिस्टर_device(vfd);
	वापस ret;
पूर्ण

अटल पूर्णांक hantro_add_enc_func(काष्ठा hantro_dev *vpu)
अणु
	अगर (!vpu->variant->enc_fmts)
		वापस 0;

	वापस hantro_add_func(vpu, MEDIA_ENT_F_PROC_VIDEO_ENCODER);
पूर्ण

अटल पूर्णांक hantro_add_dec_func(काष्ठा hantro_dev *vpu)
अणु
	अगर (!vpu->variant->dec_fmts)
		वापस 0;

	वापस hantro_add_func(vpu, MEDIA_ENT_F_PROC_VIDEO_DECODER);
पूर्ण

अटल व्योम hantro_हटाओ_func(काष्ठा hantro_dev *vpu,
			       अचिन्हित पूर्णांक funcid)
अणु
	काष्ठा hantro_func *func;

	अगर (funcid == MEDIA_ENT_F_PROC_VIDEO_ENCODER)
		func = vpu->encoder;
	अन्यथा
		func = vpu->decoder;

	अगर (!func)
		वापस;

	hantro_detach_func(func);
	video_unरेजिस्टर_device(&func->vdev);
पूर्ण

अटल व्योम hantro_हटाओ_enc_func(काष्ठा hantro_dev *vpu)
अणु
	hantro_हटाओ_func(vpu, MEDIA_ENT_F_PROC_VIDEO_ENCODER);
पूर्ण

अटल व्योम hantro_हटाओ_dec_func(काष्ठा hantro_dev *vpu)
अणु
	hantro_हटाओ_func(vpu, MEDIA_ENT_F_PROC_VIDEO_DECODER);
पूर्ण

अटल स्थिर काष्ठा media_device_ops hantro_m2m_media_ops = अणु
	.req_validate = vb2_request_validate,
	.req_queue = v4l2_m2m_request_queue,
पूर्ण;

अटल पूर्णांक hantro_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा hantro_dev *vpu;
	काष्ठा resource *res;
	पूर्णांक num_bases;
	पूर्णांक i, ret;

	vpu = devm_kzalloc(&pdev->dev, माप(*vpu), GFP_KERNEL);
	अगर (!vpu)
		वापस -ENOMEM;

	vpu->dev = &pdev->dev;
	vpu->pdev = pdev;
	mutex_init(&vpu->vpu_mutex);
	spin_lock_init(&vpu->irqlock);

	match = of_match_node(of_hantro_match, pdev->dev.of_node);
	vpu->variant = match->data;

	INIT_DELAYED_WORK(&vpu->watchकरोg_work, hantro_watchकरोg);

	vpu->घड़ीs = devm_kसुस्मृति(&pdev->dev, vpu->variant->num_घड़ीs,
				   माप(*vpu->घड़ीs), GFP_KERNEL);
	अगर (!vpu->घड़ीs)
		वापस -ENOMEM;

	क्रम (i = 0; i < vpu->variant->num_घड़ीs; i++)
		vpu->घड़ीs[i].id = vpu->variant->clk_names[i];
	ret = devm_clk_bulk_get(&pdev->dev, vpu->variant->num_घड़ीs,
				vpu->घड़ीs);
	अगर (ret)
		वापस ret;

	num_bases = vpu->variant->num_regs ?: 1;
	vpu->reg_bases = devm_kसुस्मृति(&pdev->dev, num_bases,
				      माप(*vpu->reg_bases), GFP_KERNEL);
	अगर (!vpu->reg_bases)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_bases; i++) अणु
		res = vpu->variant->reg_names ?
		      platक्रमm_get_resource_byname(vpu->pdev, IORESOURCE_MEM,
						   vpu->variant->reg_names[i]) :
		      platक्रमm_get_resource(vpu->pdev, IORESOURCE_MEM, 0);
		vpu->reg_bases[i] = devm_ioremap_resource(vpu->dev, res);
		अगर (IS_ERR(vpu->reg_bases[i]))
			वापस PTR_ERR(vpu->reg_bases[i]);
	पूर्ण
	vpu->enc_base = vpu->reg_bases[0] + vpu->variant->enc_offset;
	vpu->dec_base = vpu->reg_bases[0] + vpu->variant->dec_offset;

	ret = dma_set_coherent_mask(vpu->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(vpu->dev, "Could not set DMA coherent mask.\n");
		वापस ret;
	पूर्ण
	vb2_dma_contig_set_max_seg_size(&pdev->dev, DMA_BIT_MASK(32));

	क्रम (i = 0; i < vpu->variant->num_irqs; i++) अणु
		स्थिर अक्षर *irq_name = vpu->variant->irqs[i].name;
		पूर्णांक irq;

		अगर (!vpu->variant->irqs[i].handler)
			जारी;

		irq = platक्रमm_get_irq_byname(vpu->pdev, irq_name);
		अगर (irq <= 0)
			वापस -ENXIO;

		ret = devm_request_irq(vpu->dev, irq,
				       vpu->variant->irqs[i].handler, 0,
				       dev_name(vpu->dev), vpu);
		अगर (ret) अणु
			dev_err(vpu->dev, "Could not request %s IRQ.\n",
				irq_name);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = vpu->variant->init(vpu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to init VPU hardware\n");
		वापस ret;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(vpu->dev, 100);
	pm_runसमय_use_स्वतःsuspend(vpu->dev);
	pm_runसमय_enable(vpu->dev);

	ret = clk_bulk_prepare(vpu->variant->num_घड़ीs, vpu->घड़ीs);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to prepare clocks\n");
		वापस ret;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &vpu->v4l2_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register v4l2 device\n");
		जाओ err_clk_unprepare;
	पूर्ण
	platक्रमm_set_drvdata(pdev, vpu);

	vpu->m2m_dev = v4l2_m2m_init(&vpu_m2m_ops);
	अगर (IS_ERR(vpu->m2m_dev)) अणु
		v4l2_err(&vpu->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(vpu->m2m_dev);
		जाओ err_v4l2_unreg;
	पूर्ण

	vpu->mdev.dev = vpu->dev;
	strscpy(vpu->mdev.model, DRIVER_NAME, माप(vpu->mdev.model));
	strscpy(vpu->mdev.bus_info, "platform: " DRIVER_NAME,
		माप(vpu->mdev.model));
	media_device_init(&vpu->mdev);
	vpu->mdev.ops = &hantro_m2m_media_ops;
	vpu->v4l2_dev.mdev = &vpu->mdev;

	ret = hantro_add_enc_func(vpu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register encoder\n");
		जाओ err_m2m_rel;
	पूर्ण

	ret = hantro_add_dec_func(vpu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register decoder\n");
		जाओ err_rm_enc_func;
	पूर्ण

	ret = media_device_रेजिस्टर(&vpu->mdev);
	अगर (ret) अणु
		v4l2_err(&vpu->v4l2_dev, "Failed to register mem2mem media device\n");
		जाओ err_rm_dec_func;
	पूर्ण

	वापस 0;

err_rm_dec_func:
	hantro_हटाओ_dec_func(vpu);
err_rm_enc_func:
	hantro_हटाओ_enc_func(vpu);
err_m2m_rel:
	media_device_cleanup(&vpu->mdev);
	v4l2_m2m_release(vpu->m2m_dev);
err_v4l2_unreg:
	v4l2_device_unरेजिस्टर(&vpu->v4l2_dev);
err_clk_unprepare:
	clk_bulk_unprepare(vpu->variant->num_घड़ीs, vpu->घड़ीs);
	pm_runसमय_करोnt_use_स्वतःsuspend(vpu->dev);
	pm_runसमय_disable(vpu->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक hantro_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hantro_dev *vpu = platक्रमm_get_drvdata(pdev);

	v4l2_info(&vpu->v4l2_dev, "Removing %s\n", pdev->name);

	media_device_unरेजिस्टर(&vpu->mdev);
	hantro_हटाओ_dec_func(vpu);
	hantro_हटाओ_enc_func(vpu);
	media_device_cleanup(&vpu->mdev);
	v4l2_m2m_release(vpu->m2m_dev);
	v4l2_device_unरेजिस्टर(&vpu->v4l2_dev);
	clk_bulk_unprepare(vpu->variant->num_घड़ीs, vpu->घड़ीs);
	pm_runसमय_करोnt_use_स्वतःsuspend(vpu->dev);
	pm_runसमय_disable(vpu->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक hantro_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा hantro_dev *vpu = dev_get_drvdata(dev);

	अगर (vpu->variant->runसमय_resume)
		वापस vpu->variant->runसमय_resume(vpu);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops hantro_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(शून्य, hantro_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver hantro_driver = अणु
	.probe = hantro_probe,
	.हटाओ = hantro_हटाओ,
	.driver = अणु
		   .name = DRIVER_NAME,
		   .of_match_table = of_match_ptr(of_hantro_match),
		   .pm = &hantro_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(hantro_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Alpha Lin <Alpha.Lin@Rock-Chips.com>");
MODULE_AUTHOR("Tomasz Figa <tfiga@chromium.org>");
MODULE_AUTHOR("Ezequiel Garcia <ezequiel@collabora.com>");
MODULE_DESCRIPTION("Hantro VPU codec driver");
