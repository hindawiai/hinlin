<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Rockchip ISP1 Driver - Stats subdevice
 *
 * Copyright (C) 2017 Rockchip Electronics Co., Ltd.
 */

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>	/* क्रम ISP statistics */

#समावेश "rkisp1-common.h"

#घोषणा RKISP1_STATS_DEV_NAME	RKISP1_DRIVER_NAME "_stats"

#घोषणा RKISP1_ISP_STATS_REQ_BUFS_MIN 2
#घोषणा RKISP1_ISP_STATS_REQ_BUFS_MAX 8

अटल पूर्णांक rkisp1_stats_क्रमागत_fmt_meta_cap(काष्ठा file *file, व्योम *priv,
					  काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा video_device *video = video_devdata(file);
	काष्ठा rkisp1_stats *stats = video_get_drvdata(video);

	अगर (f->index > 0 || f->type != video->queue->type)
		वापस -EINVAL;

	f->pixelक्रमmat = stats->vdev_fmt.fmt.meta.dataक्रमmat;
	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_stats_g_fmt_meta_cap(काष्ठा file *file, व्योम *priv,
				       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा video_device *video = video_devdata(file);
	काष्ठा rkisp1_stats *stats = video_get_drvdata(video);
	काष्ठा v4l2_meta_क्रमmat *meta = &f->fmt.meta;

	अगर (f->type != video->queue->type)
		वापस -EINVAL;

	स_रखो(meta, 0, माप(*meta));
	meta->dataक्रमmat = stats->vdev_fmt.fmt.meta.dataक्रमmat;
	meta->buffersize = stats->vdev_fmt.fmt.meta.buffersize;

	वापस 0;
पूर्ण

अटल पूर्णांक rkisp1_stats_querycap(काष्ठा file *file,
				 व्योम *priv, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	strscpy(cap->driver, RKISP1_DRIVER_NAME, माप(cap->driver));
	strscpy(cap->card, vdev->name, माप(cap->card));
	strscpy(cap->bus_info, RKISP1_BUS_INFO, माप(cap->bus_info));

	वापस 0;
पूर्ण

/* ISP video device IOCTLs */
अटल स्थिर काष्ठा v4l2_ioctl_ops rkisp1_stats_ioctl = अणु
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_expbuf = vb2_ioctl_expbuf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
	.vidioc_क्रमागत_fmt_meta_cap = rkisp1_stats_क्रमागत_fmt_meta_cap,
	.vidioc_g_fmt_meta_cap = rkisp1_stats_g_fmt_meta_cap,
	.vidioc_s_fmt_meta_cap = rkisp1_stats_g_fmt_meta_cap,
	.vidioc_try_fmt_meta_cap = rkisp1_stats_g_fmt_meta_cap,
	.vidioc_querycap = rkisp1_stats_querycap,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations rkisp1_stats_fops = अणु
	.mmap = vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
	.poll = vb2_fop_poll,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release
पूर्ण;

अटल पूर्णांक rkisp1_stats_vb2_queue_setup(काष्ठा vb2_queue *vq,
					अचिन्हित पूर्णांक *num_buffers,
					अचिन्हित पूर्णांक *num_planes,
					अचिन्हित पूर्णांक sizes[],
					काष्ठा device *alloc_devs[])
अणु
	*num_planes = 1;

	*num_buffers = clamp_t(u32, *num_buffers, RKISP1_ISP_STATS_REQ_BUFS_MIN,
			       RKISP1_ISP_STATS_REQ_BUFS_MAX);

	sizes[0] = माप(काष्ठा rkisp1_stat_buffer);

	वापस 0;
पूर्ण

अटल व्योम rkisp1_stats_vb2_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा rkisp1_buffer *stats_buf =
		container_of(vbuf, काष्ठा rkisp1_buffer, vb);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा rkisp1_stats *stats_dev = vq->drv_priv;

	stats_buf->vaddr = vb2_plane_vaddr(vb, 0);

	spin_lock_irq(&stats_dev->lock);
	list_add_tail(&stats_buf->queue, &stats_dev->stat);
	spin_unlock_irq(&stats_dev->lock);
पूर्ण

अटल पूर्णांक rkisp1_stats_vb2_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	अगर (vb2_plane_size(vb, 0) < माप(काष्ठा rkisp1_stat_buffer))
		वापस -EINVAL;

	vb2_set_plane_payload(vb, 0, माप(काष्ठा rkisp1_stat_buffer));

	वापस 0;
पूर्ण

अटल व्योम rkisp1_stats_vb2_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा rkisp1_stats *stats = vq->drv_priv;
	काष्ठा rkisp1_buffer *buf;
	अचिन्हित पूर्णांक i;

	spin_lock_irq(&stats->lock);
	क्रम (i = 0; i < RKISP1_ISP_STATS_REQ_BUFS_MAX; i++) अणु
		अगर (list_empty(&stats->stat))
			अवरोध;
		buf = list_first_entry(&stats->stat,
				       काष्ठा rkisp1_buffer, queue);
		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irq(&stats->lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops rkisp1_stats_vb2_ops = अणु
	.queue_setup = rkisp1_stats_vb2_queue_setup,
	.buf_queue = rkisp1_stats_vb2_buf_queue,
	.buf_prepare = rkisp1_stats_vb2_buf_prepare,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.stop_streaming = rkisp1_stats_vb2_stop_streaming,
पूर्ण;

अटल पूर्णांक
rkisp1_stats_init_vb2_queue(काष्ठा vb2_queue *q, काष्ठा rkisp1_stats *stats)
अणु
	काष्ठा rkisp1_vdev_node *node;

	node = container_of(q, काष्ठा rkisp1_vdev_node, buf_queue);

	q->type = V4L2_BUF_TYPE_META_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->drv_priv = stats;
	q->ops = &rkisp1_stats_vb2_ops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;
	q->buf_काष्ठा_size = माप(काष्ठा rkisp1_buffer);
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &node->vlock;

	वापस vb2_queue_init(q);
पूर्ण

अटल व्योम rkisp1_stats_get_awb_meas(काष्ठा rkisp1_stats *stats,
				      काष्ठा rkisp1_stat_buffer *pbuf)
अणु
	/* Protect against concurrent access from ISR? */
	काष्ठा rkisp1_device *rkisp1 = stats->rkisp1;
	u32 reg_val;

	pbuf->meas_type |= RKISP1_CIF_ISP_STAT_AWB;
	reg_val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_AWB_WHITE_CNT);
	pbuf->params.awb.awb_mean[0].cnt =
				RKISP1_CIF_ISP_AWB_GET_PIXEL_CNT(reg_val);
	reg_val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_AWB_MEAN);

	pbuf->params.awb.awb_mean[0].mean_cr_or_r =
				RKISP1_CIF_ISP_AWB_GET_MEAN_CR_R(reg_val);
	pbuf->params.awb.awb_mean[0].mean_cb_or_b =
				RKISP1_CIF_ISP_AWB_GET_MEAN_CB_B(reg_val);
	pbuf->params.awb.awb_mean[0].mean_y_or_g =
				RKISP1_CIF_ISP_AWB_GET_MEAN_Y_G(reg_val);
पूर्ण

अटल व्योम rkisp1_stats_get_aec_meas(काष्ठा rkisp1_stats *stats,
				      काष्ठा rkisp1_stat_buffer *pbuf)
अणु
	काष्ठा rkisp1_device *rkisp1 = stats->rkisp1;
	अचिन्हित पूर्णांक i;

	pbuf->meas_type |= RKISP1_CIF_ISP_STAT_AUTOEXP;
	क्रम (i = 0; i < RKISP1_CIF_ISP_AE_MEAN_MAX_V10; i++)
		pbuf->params.ae.exp_mean[i] =
			(u8)rkisp1_पढ़ो(rkisp1,
					RKISP1_CIF_ISP_EXP_MEAN_00 + i * 4);
पूर्ण

अटल व्योम rkisp1_stats_get_afc_meas(काष्ठा rkisp1_stats *stats,
				      काष्ठा rkisp1_stat_buffer *pbuf)
अणु
	काष्ठा rkisp1_device *rkisp1 = stats->rkisp1;
	काष्ठा rkisp1_cअगर_isp_af_stat *af;

	pbuf->meas_type |= RKISP1_CIF_ISP_STAT_AFM;

	af = &pbuf->params.af;
	af->winकरोw[0].sum = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_AFM_SUM_A);
	af->winकरोw[0].lum = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_AFM_LUM_A);
	af->winकरोw[1].sum = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_AFM_SUM_B);
	af->winकरोw[1].lum = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_AFM_LUM_B);
	af->winकरोw[2].sum = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_AFM_SUM_C);
	af->winकरोw[2].lum = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_AFM_LUM_C);
पूर्ण

अटल व्योम rkisp1_stats_get_hst_meas(काष्ठा rkisp1_stats *stats,
				      काष्ठा rkisp1_stat_buffer *pbuf)
अणु
	काष्ठा rkisp1_device *rkisp1 = stats->rkisp1;
	अचिन्हित पूर्णांक i;

	pbuf->meas_type |= RKISP1_CIF_ISP_STAT_HIST;
	क्रम (i = 0; i < RKISP1_CIF_ISP_HIST_BIN_N_MAX_V10; i++) अणु
		u32 reg_val = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_HIST_BIN_0 + i * 4);

		pbuf->params.hist.hist_bins[i] = RKISP1_CIF_ISP_HIST_GET_BIN(reg_val);
	पूर्ण
पूर्ण

अटल व्योम rkisp1_stats_get_bls_meas(काष्ठा rkisp1_stats *stats,
				      काष्ठा rkisp1_stat_buffer *pbuf)
अणु
	काष्ठा rkisp1_device *rkisp1 = stats->rkisp1;
	स्थिर काष्ठा rkisp1_isp_mbus_info *in_fmt = rkisp1->isp.sink_fmt;
	काष्ठा rkisp1_cअगर_isp_bls_meas_val *bls_val;

	bls_val = &pbuf->params.ae.bls_val;
	अगर (in_fmt->bayer_pat == RKISP1_RAW_BGGR) अणु
		bls_val->meas_b =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_A_MEASURED);
		bls_val->meas_gb =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_B_MEASURED);
		bls_val->meas_gr =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_C_MEASURED);
		bls_val->meas_r =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_D_MEASURED);
	पूर्ण अन्यथा अगर (in_fmt->bayer_pat == RKISP1_RAW_GBRG) अणु
		bls_val->meas_gb =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_A_MEASURED);
		bls_val->meas_b =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_B_MEASURED);
		bls_val->meas_r =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_C_MEASURED);
		bls_val->meas_gr =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_D_MEASURED);
	पूर्ण अन्यथा अगर (in_fmt->bayer_pat == RKISP1_RAW_GRBG) अणु
		bls_val->meas_gr =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_A_MEASURED);
		bls_val->meas_r =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_B_MEASURED);
		bls_val->meas_b =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_C_MEASURED);
		bls_val->meas_gb =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_D_MEASURED);
	पूर्ण अन्यथा अगर (in_fmt->bayer_pat == RKISP1_RAW_RGGB) अणु
		bls_val->meas_r =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_A_MEASURED);
		bls_val->meas_gr =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_B_MEASURED);
		bls_val->meas_gb =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_C_MEASURED);
		bls_val->meas_b =
			rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_BLS_D_MEASURED);
	पूर्ण
पूर्ण

अटल व्योम
rkisp1_stats_send_measurement(काष्ठा rkisp1_stats *stats, u32 isp_ris)
अणु
	काष्ठा rkisp1_stat_buffer *cur_stat_buf;
	काष्ठा rkisp1_buffer *cur_buf = शून्य;
	अचिन्हित पूर्णांक frame_sequence = stats->rkisp1->isp.frame_sequence;
	u64 बारtamp = kसमय_get_ns();

	/* get one empty buffer */
	अगर (!list_empty(&stats->stat)) अणु
		cur_buf = list_first_entry(&stats->stat,
					   काष्ठा rkisp1_buffer, queue);
		list_del(&cur_buf->queue);
	पूर्ण

	अगर (!cur_buf)
		वापस;

	cur_stat_buf =
		(काष्ठा rkisp1_stat_buffer *)(cur_buf->vaddr);

	अगर (isp_ris & RKISP1_CIF_ISP_AWB_DONE)
		rkisp1_stats_get_awb_meas(stats, cur_stat_buf);

	अगर (isp_ris & RKISP1_CIF_ISP_AFM_FIN)
		rkisp1_stats_get_afc_meas(stats, cur_stat_buf);

	अगर (isp_ris & RKISP1_CIF_ISP_EXP_END) अणु
		rkisp1_stats_get_aec_meas(stats, cur_stat_buf);
		rkisp1_stats_get_bls_meas(stats, cur_stat_buf);
	पूर्ण

	अगर (isp_ris & RKISP1_CIF_ISP_HIST_MEASURE_RDY)
		rkisp1_stats_get_hst_meas(stats, cur_stat_buf);

	vb2_set_plane_payload(&cur_buf->vb.vb2_buf, 0,
			      माप(काष्ठा rkisp1_stat_buffer));
	cur_buf->vb.sequence = frame_sequence;
	cur_buf->vb.vb2_buf.बारtamp = बारtamp;
	vb2_buffer_करोne(&cur_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण

व्योम rkisp1_stats_isr(काष्ठा rkisp1_stats *stats, u32 isp_ris)
अणु
	काष्ठा rkisp1_device *rkisp1 = stats->rkisp1;
	अचिन्हित पूर्णांक isp_mis_पंचांगp = 0;

	spin_lock(&stats->lock);

	rkisp1_ग_लिखो(rkisp1, RKISP1_STATS_MEAS_MASK, RKISP1_CIF_ISP_ICR);

	isp_mis_पंचांगp = rkisp1_पढ़ो(rkisp1, RKISP1_CIF_ISP_MIS);
	अगर (isp_mis_पंचांगp & RKISP1_STATS_MEAS_MASK)
		rkisp1->debug.stats_error++;

	अगर (isp_ris & RKISP1_STATS_MEAS_MASK)
		rkisp1_stats_send_measurement(stats, isp_ris);

	spin_unlock(&stats->lock);
पूर्ण

अटल व्योम rkisp1_init_stats(काष्ठा rkisp1_stats *stats)
अणु
	stats->vdev_fmt.fmt.meta.dataक्रमmat =
		V4L2_META_FMT_RK_ISP1_STAT_3A;
	stats->vdev_fmt.fmt.meta.buffersize =
		माप(काष्ठा rkisp1_stat_buffer);
पूर्ण

पूर्णांक rkisp1_stats_रेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_stats *stats = &rkisp1->stats;
	काष्ठा rkisp1_vdev_node *node = &stats->vnode;
	काष्ठा video_device *vdev = &node->vdev;
	पूर्णांक ret;

	stats->rkisp1 = rkisp1;
	mutex_init(&node->vlock);
	INIT_LIST_HEAD(&stats->stat);
	spin_lock_init(&stats->lock);

	strscpy(vdev->name, RKISP1_STATS_DEV_NAME, माप(vdev->name));

	video_set_drvdata(vdev, stats);
	vdev->ioctl_ops = &rkisp1_stats_ioctl;
	vdev->fops = &rkisp1_stats_fops;
	vdev->release = video_device_release_empty;
	vdev->lock = &node->vlock;
	vdev->v4l2_dev = &rkisp1->v4l2_dev;
	vdev->queue = &node->buf_queue;
	vdev->device_caps = V4L2_CAP_META_CAPTURE | V4L2_CAP_STREAMING;
	vdev->vfl_dir =  VFL_सूची_RX;
	rkisp1_stats_init_vb2_queue(vdev->queue, stats);
	rkisp1_init_stats(stats);
	video_set_drvdata(vdev, stats);

	node->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vdev->entity, 1, &node->pad);
	अगर (ret)
		जाओ err_mutex_destroy;

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(&vdev->dev,
			"failed to register %s, ret=%d\n", vdev->name, ret);
		जाओ err_cleanup_media_entity;
	पूर्ण

	वापस 0;

err_cleanup_media_entity:
	media_entity_cleanup(&vdev->entity);
err_mutex_destroy:
	mutex_destroy(&node->vlock);
	वापस ret;
पूर्ण

व्योम rkisp1_stats_unरेजिस्टर(काष्ठा rkisp1_device *rkisp1)
अणु
	काष्ठा rkisp1_stats *stats = &rkisp1->stats;
	काष्ठा rkisp1_vdev_node *node = &stats->vnode;
	काष्ठा video_device *vdev = &node->vdev;

	vb2_video_unरेजिस्टर_device(vdev);
	media_entity_cleanup(&vdev->entity);
	mutex_destroy(&node->vlock);
पूर्ण
