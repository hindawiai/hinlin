<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/host1x.h>
#समावेश <linux/lcm.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश <soc/tegra/pmc.h>

#समावेश "vi.h"
#समावेश "video.h"

#घोषणा MAX_CID_CONTROLS		1

अटल स्थिर काष्ठा tegra_video_क्रमmat tegra_शेष_क्रमmat = अणु
	.img_dt = TEGRA_IMAGE_DT_RAW10,
	.bit_width = 10,
	.code = MEDIA_BUS_FMT_SRGGB10_1X10,
	.bpp = 2,
	.img_fmt = TEGRA_IMAGE_FORMAT_DEF,
	.fourcc = V4L2_PIX_FMT_SRGGB10,
पूर्ण;

अटल अंतरभूत काष्ठा tegra_vi *
host1x_client_to_vi(काष्ठा host1x_client *client)
अणु
	वापस container_of(client, काष्ठा tegra_vi, client);
पूर्ण

अटल अंतरभूत काष्ठा tegra_channel_buffer *
to_tegra_channel_buffer(काष्ठा vb2_v4l2_buffer *vb)
अणु
	वापस container_of(vb, काष्ठा tegra_channel_buffer, buf);
पूर्ण

अटल अंतरभूत काष्ठा tegra_vi_graph_entity *
to_tegra_vi_graph_entity(काष्ठा v4l2_async_subdev *asd)
अणु
	वापस container_of(asd, काष्ठा tegra_vi_graph_entity, asd);
पूर्ण

अटल पूर्णांक tegra_get_क्रमmat_idx_by_code(काष्ठा tegra_vi *vi,
					अचिन्हित पूर्णांक code,
					अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = offset; i < vi->soc->nक्रमmats; ++i) अणु
		अगर (vi->soc->video_क्रमmats[i].code == code)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल u32 tegra_get_क्रमmat_fourcc_by_idx(काष्ठा tegra_vi *vi,
					  अचिन्हित पूर्णांक index)
अणु
	अगर (index >= vi->soc->nक्रमmats)
		वापस -EINVAL;

	वापस vi->soc->video_क्रमmats[index].fourcc;
पूर्ण

अटल स्थिर काष्ठा tegra_video_क्रमmat *
tegra_get_क्रमmat_by_fourcc(काष्ठा tegra_vi *vi, u32 fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < vi->soc->nक्रमmats; ++i) अणु
		अगर (vi->soc->video_क्रमmats[i].fourcc == fourcc)
			वापस &vi->soc->video_क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * videobuf2 queue operations
 */
अटल पूर्णांक tegra_channel_queue_setup(काष्ठा vb2_queue *vq,
				     अचिन्हित पूर्णांक *nbuffers,
				     अचिन्हित पूर्णांक *nplanes,
				     अचिन्हित पूर्णांक sizes[],
				     काष्ठा device *alloc_devs[])
अणु
	काष्ठा tegra_vi_channel *chan = vb2_get_drv_priv(vq);

	अगर (*nplanes)
		वापस sizes[0] < chan->क्रमmat.sizeimage ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = chan->क्रमmat.sizeimage;
	alloc_devs[0] = chan->vi->dev;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा tegra_vi_channel *chan = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा tegra_channel_buffer *buf = to_tegra_channel_buffer(vbuf);
	अचिन्हित दीर्घ size = chan->क्रमmat.sizeimage;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		v4l2_err(chan->video.v4l2_dev,
			 "buffer too small (%lu < %lu)\n",
			 vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);
	buf->chan = chan;
	buf->addr = vb2_dma_contig_plane_dma_addr(vb, 0);

	वापस 0;
पूर्ण

अटल व्योम tegra_channel_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा tegra_vi_channel *chan = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा tegra_channel_buffer *buf = to_tegra_channel_buffer(vbuf);

	/* put buffer पूर्णांकo the capture queue */
	spin_lock(&chan->start_lock);
	list_add_tail(&buf->queue, &chan->capture);
	spin_unlock(&chan->start_lock);

	/* रुको up kthपढ़ो क्रम capture */
	wake_up_पूर्णांकerruptible(&chan->start_रुको);
पूर्ण

काष्ठा v4l2_subdev *
tegra_channel_get_remote_csi_subdev(काष्ठा tegra_vi_channel *chan)
अणु
	काष्ठा media_pad *pad;

	pad = media_entity_remote_pad(&chan->pad);
	अगर (!pad)
		वापस शून्य;

	वापस media_entity_to_v4l2_subdev(pad->entity);
पूर्ण

काष्ठा v4l2_subdev *
tegra_channel_get_remote_source_subdev(काष्ठा tegra_vi_channel *chan)
अणु
	काष्ठा media_pad *pad;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा media_entity *entity;

	subdev = tegra_channel_get_remote_csi_subdev(chan);
	अगर (!subdev)
		वापस शून्य;

	pad = &subdev->entity.pads[0];
	जबतक (!(pad->flags & MEDIA_PAD_FL_SOURCE)) अणु
		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;
		entity = pad->entity;
		pad = &entity->pads[0];
		subdev = media_entity_to_v4l2_subdev(entity);
	पूर्ण

	वापस subdev;
पूर्ण

अटल पूर्णांक tegra_channel_enable_stream(काष्ठा tegra_vi_channel *chan)
अणु
	काष्ठा v4l2_subdev *csi_subdev, *src_subdev;
	काष्ठा tegra_csi_channel *csi_chan;
	पूर्णांक ret, err;

	/*
	 * Tegra CSI receiver can detect the first LP to HS transition.
	 * So, start the CSI stream-on prior to sensor stream-on and
	 * vice-versa क्रम stream-off.
	 */
	csi_subdev = tegra_channel_get_remote_csi_subdev(chan);
	ret = v4l2_subdev_call(csi_subdev, video, s_stream, true);
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		वापस ret;

	अगर (IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		वापस 0;

	csi_chan = v4l2_get_subdevdata(csi_subdev);
	/*
	 * TRM has incorrectly करोcumented to रुको क्रम करोne status from
	 * calibration logic after CSI पूर्णांकerface घातer on.
	 * As per the design, calibration results are latched and applied
	 * to the pads only when the link is in LP11 state which will happen
	 * during the sensor stream-on.
	 * CSI subdev stream-on triggers start of MIPI pads calibration.
	 * Wait क्रम calibration to finish here after sensor subdev stream-on.
	 */
	src_subdev = tegra_channel_get_remote_source_subdev(chan);
	ret = v4l2_subdev_call(src_subdev, video, s_stream, true);
	err = tegra_mipi_finish_calibration(csi_chan->mipi);

	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		जाओ err_disable_csi_stream;

	अगर (err < 0)
		dev_warn(csi_chan->csi->dev,
			 "MIPI calibration failed: %d\n", err);

	वापस 0;

err_disable_csi_stream:
	v4l2_subdev_call(csi_subdev, video, s_stream, false);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_channel_disable_stream(काष्ठा tegra_vi_channel *chan)
अणु
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक ret;

	/*
	 * Stream-off subdevices in reverse order to stream-on.
	 * Remote source subdev in TPG mode is same as CSI subdev.
	 */
	subdev = tegra_channel_get_remote_source_subdev(chan);
	ret = v4l2_subdev_call(subdev, video, s_stream, false);
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		वापस ret;

	अगर (IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		वापस 0;

	subdev = tegra_channel_get_remote_csi_subdev(chan);
	ret = v4l2_subdev_call(subdev, video, s_stream, false);
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक tegra_channel_set_stream(काष्ठा tegra_vi_channel *chan, bool on)
अणु
	पूर्णांक ret;

	अगर (on)
		ret = tegra_channel_enable_stream(chan);
	अन्यथा
		ret = tegra_channel_disable_stream(chan);

	वापस ret;
पूर्ण

व्योम tegra_channel_release_buffers(काष्ठा tegra_vi_channel *chan,
				   क्रमागत vb2_buffer_state state)
अणु
	काष्ठा tegra_channel_buffer *buf, *nbuf;

	spin_lock(&chan->start_lock);
	list_क्रम_each_entry_safe(buf, nbuf, &chan->capture, queue) अणु
		vb2_buffer_करोne(&buf->buf.vb2_buf, state);
		list_del(&buf->queue);
	पूर्ण
	spin_unlock(&chan->start_lock);

	spin_lock(&chan->करोne_lock);
	list_क्रम_each_entry_safe(buf, nbuf, &chan->करोne, queue) अणु
		vb2_buffer_करोne(&buf->buf.vb2_buf, state);
		list_del(&buf->queue);
	पूर्ण
	spin_unlock(&chan->करोne_lock);
पूर्ण

अटल पूर्णांक tegra_channel_start_streaming(काष्ठा vb2_queue *vq, u32 count)
अणु
	काष्ठा tegra_vi_channel *chan = vb2_get_drv_priv(vq);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(chan->vi->dev);
	अगर (ret < 0) अणु
		dev_err(chan->vi->dev, "failed to get runtime PM: %d\n", ret);
		pm_runसमय_put_noidle(chan->vi->dev);
		वापस ret;
	पूर्ण

	ret = chan->vi->ops->vi_start_streaming(vq, count);
	अगर (ret < 0)
		pm_runसमय_put(chan->vi->dev);

	वापस ret;
पूर्ण

अटल व्योम tegra_channel_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा tegra_vi_channel *chan = vb2_get_drv_priv(vq);

	chan->vi->ops->vi_stop_streaming(vq);
	pm_runसमय_put(chan->vi->dev);
पूर्ण

अटल स्थिर काष्ठा vb2_ops tegra_channel_queue_qops = अणु
	.queue_setup = tegra_channel_queue_setup,
	.buf_prepare = tegra_channel_buffer_prepare,
	.buf_queue = tegra_channel_buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = tegra_channel_start_streaming,
	.stop_streaming = tegra_channel_stop_streaming,
पूर्ण;

/*
 * V4L2 ioctl operations
 */
अटल पूर्णांक tegra_channel_querycap(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_capability *cap)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);

	strscpy(cap->driver, "tegra-video", माप(cap->driver));
	strscpy(cap->card, chan->video.name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(chan->vi->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_g_parm(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	वापस v4l2_g_parm_cap(&chan->video, subdev, a);
पूर्ण

अटल पूर्णांक tegra_channel_s_parm(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	वापस v4l2_s_parm_cap(&chan->video, subdev, a);
पूर्ण

अटल पूर्णांक tegra_channel_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
					 काष्ठा v4l2_frmsizeक्रमागत *sizes)
अणु
	पूर्णांक ret;
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;
	स्थिर काष्ठा tegra_video_क्रमmat *fmtinfo;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणु
		.index = sizes->index,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	fmtinfo = tegra_get_क्रमmat_by_fourcc(chan->vi, sizes->pixel_क्रमmat);
	अगर (!fmtinfo)
		वापस -EINVAL;

	fse.code = fmtinfo->code;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	ret = v4l2_subdev_call(subdev, pad, क्रमागत_frame_size, शून्य, &fse);
	अगर (ret)
		वापस ret;

	sizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	sizes->discrete.width = fse.max_width;
	sizes->discrete.height = fse.max_height;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
					     काष्ठा v4l2_frmivalक्रमागत *ivals)
अणु
	पूर्णांक ret;
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;
	स्थिर काष्ठा tegra_video_क्रमmat *fmtinfo;
	काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत fie = अणु
		.index = ivals->index,
		.width = ivals->width,
		.height = ivals->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	fmtinfo = tegra_get_क्रमmat_by_fourcc(chan->vi, ivals->pixel_क्रमmat);
	अगर (!fmtinfo)
		वापस -EINVAL;

	fie.code = fmtinfo->code;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	ret = v4l2_subdev_call(subdev, pad, क्रमागत_frame_पूर्णांकerval, शून्य, &fie);
	अगर (ret)
		वापस ret;

	ivals->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	ivals->discrete.numerator = fie.पूर्णांकerval.numerator;
	ivals->discrete.denominator = fie.पूर्णांकerval.denominator;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_क्रमागत_क्रमmat(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	अचिन्हित पूर्णांक index = 0, i;
	अचिन्हित दीर्घ *fmts_biपंचांगap = chan->tpg_fmts_biपंचांगap;

	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		fmts_biपंचांगap = chan->fmts_biपंचांगap;

	अगर (f->index >= biपंचांगap_weight(fmts_biपंचांगap, MAX_FORMAT_NUM))
		वापस -EINVAL;

	क्रम (i = 0; i < f->index + 1; i++, index++)
		index = find_next_bit(fmts_biपंचांगap, MAX_FORMAT_NUM, index);

	f->pixelक्रमmat = tegra_get_क्रमmat_fourcc_by_idx(chan->vi, index - 1);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_get_क्रमmat(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);

	क्रमmat->fmt.pix = chan->क्रमmat;

	वापस 0;
पूर्ण

अटल व्योम tegra_channel_fmt_align(काष्ठा tegra_vi_channel *chan,
				    काष्ठा v4l2_pix_क्रमmat *pix,
				    अचिन्हित पूर्णांक bpp)
अणु
	अचिन्हित पूर्णांक min_bpl;
	अचिन्हित पूर्णांक max_bpl;
	अचिन्हित पूर्णांक bpl;

	/*
	 * The transfer alignment requirements are expressed in bytes.
	 * Clamp the requested width and height to the limits.
	 */
	pix->width = clamp(pix->width, TEGRA_MIN_WIDTH, TEGRA_MAX_WIDTH);
	pix->height = clamp(pix->height, TEGRA_MIN_HEIGHT, TEGRA_MAX_HEIGHT);

	/* Clamp the requested bytes per line value. If the maximum bytes per
	 * line value is zero, the module करोesn't support user configurable
	 * line sizes. Override the requested value with the minimum in that
	 * हाल.
	 */
	min_bpl = pix->width * bpp;
	max_bpl = roundकरोwn(TEGRA_MAX_WIDTH, SURFACE_ALIGN_BYTES);
	bpl = roundup(pix->bytesperline, SURFACE_ALIGN_BYTES);

	pix->bytesperline = clamp(bpl, min_bpl, max_bpl);
	pix->sizeimage = pix->bytesperline * pix->height;
	अगर (pix->pixelक्रमmat == V4L2_PIX_FMT_NV16)
		pix->sizeimage *= 2;
पूर्ण

अटल पूर्णांक __tegra_channel_try_क्रमmat(काष्ठा tegra_vi_channel *chan,
				      काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	स्थिर काष्ठा tegra_video_क्रमmat *fmtinfo;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_subdev_pad_config *pad_cfg;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;
	काष्ठा v4l2_subdev_selection sdsel = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = V4L2_SEL_TGT_CROP_BOUNDS,
	पूर्ण;
	पूर्णांक ret;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!subdev)
		वापस -ENODEV;

	pad_cfg = v4l2_subdev_alloc_pad_config(subdev);
	अगर (!pad_cfg)
		वापस -ENOMEM;
	/*
	 * Retrieve the क्रमmat inक्रमmation and अगर requested क्रमmat isn't
	 * supported, keep the current क्रमmat.
	 */
	fmtinfo = tegra_get_क्रमmat_by_fourcc(chan->vi, pix->pixelक्रमmat);
	अगर (!fmtinfo) अणु
		pix->pixelक्रमmat = chan->क्रमmat.pixelक्रमmat;
		pix->colorspace = chan->क्रमmat.colorspace;
		fmtinfo = tegra_get_क्रमmat_by_fourcc(chan->vi,
						     pix->pixelक्रमmat);
	पूर्ण

	pix->field = V4L2_FIELD_NONE;
	fmt.which = V4L2_SUBDEV_FORMAT_TRY;
	fmt.pad = 0;
	v4l2_fill_mbus_क्रमmat(&fmt.क्रमmat, pix, fmtinfo->code);

	/*
	 * Attempt to obtain the क्रमmat size from subdev.
	 * If not available, try to get crop boundary from subdev.
	 */
	fse.code = fmtinfo->code;
	ret = v4l2_subdev_call(subdev, pad, क्रमागत_frame_size, pad_cfg, &fse);
	अगर (ret) अणु
		अगर (!v4l2_subdev_has_op(subdev, pad, get_selection)) अणु
			pad_cfg->try_crop.width = 0;
			pad_cfg->try_crop.height = 0;
		पूर्ण अन्यथा अणु
			ret = v4l2_subdev_call(subdev, pad, get_selection,
					       शून्य, &sdsel);
			अगर (ret)
				वापस -EINVAL;

			pad_cfg->try_crop.width = sdsel.r.width;
			pad_cfg->try_crop.height = sdsel.r.height;
		पूर्ण
	पूर्ण अन्यथा अणु
		pad_cfg->try_crop.width = fse.max_width;
		pad_cfg->try_crop.height = fse.max_height;
	पूर्ण

	ret = v4l2_subdev_call(subdev, pad, set_fmt, pad_cfg, &fmt);
	अगर (ret < 0)
		वापस ret;

	v4l2_fill_pix_क्रमmat(pix, &fmt.क्रमmat);
	tegra_channel_fmt_align(chan, pix, fmtinfo->bpp);

	v4l2_subdev_मुक्त_pad_config(pad_cfg);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_try_क्रमmat(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);

	वापस __tegra_channel_try_क्रमmat(chan, &क्रमmat->fmt.pix);
पूर्ण

अटल व्योम tegra_channel_update_gangports(काष्ठा tegra_vi_channel *chan)
अणु
	अगर (chan->क्रमmat.width <= 1920)
		chan->numgangports = 1;
	अन्यथा
		chan->numgangports = chan->totalports;
पूर्ण

अटल पूर्णांक tegra_channel_set_क्रमmat(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	स्थिर काष्ठा tegra_video_क्रमmat *fmtinfo;
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा v4l2_pix_क्रमmat *pix = &क्रमmat->fmt.pix;
	पूर्णांक ret;

	अगर (vb2_is_busy(&chan->queue))
		वापस -EBUSY;

	/* get supported क्रमmat by try_fmt */
	ret = __tegra_channel_try_क्रमmat(chan, pix);
	अगर (ret)
		वापस ret;

	fmtinfo = tegra_get_क्रमmat_by_fourcc(chan->vi, pix->pixelक्रमmat);

	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	fmt.pad = 0;
	v4l2_fill_mbus_क्रमmat(&fmt.क्रमmat, pix, fmtinfo->code);
	subdev = tegra_channel_get_remote_source_subdev(chan);
	ret = v4l2_subdev_call(subdev, pad, set_fmt, शून्य, &fmt);
	अगर (ret < 0)
		वापस ret;

	v4l2_fill_pix_क्रमmat(pix, &fmt.क्रमmat);
	tegra_channel_fmt_align(chan, pix, fmtinfo->bpp);

	chan->क्रमmat = *pix;
	chan->fmtinfo = fmtinfo;
	tegra_channel_update_gangports(chan);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_set_subdev_active_fmt(काष्ठा tegra_vi_channel *chan)
अणु
	पूर्णांक ret, index;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	/*
	 * Initialize channel क्रमmat to the sub-device active क्रमmat अगर there
	 * is corresponding match in the Tegra supported video क्रमmats.
	 */
	subdev = tegra_channel_get_remote_source_subdev(chan);
	ret = v4l2_subdev_call(subdev, pad, get_fmt, शून्य, &fmt);
	अगर (ret)
		वापस ret;

	index = tegra_get_क्रमmat_idx_by_code(chan->vi, fmt.क्रमmat.code, 0);
	अगर (index < 0)
		वापस -EINVAL;

	chan->fmtinfo = &chan->vi->soc->video_क्रमmats[index];
	v4l2_fill_pix_क्रमmat(&chan->क्रमmat, &fmt.क्रमmat);
	chan->क्रमmat.pixelक्रमmat = chan->fmtinfo->fourcc;
	chan->क्रमmat.bytesperline = chan->क्रमmat.width * chan->fmtinfo->bpp;
	chan->क्रमmat.sizeimage = chan->क्रमmat.bytesperline *
				 chan->क्रमmat.height;
	tegra_channel_fmt_align(chan, &chan->क्रमmat, chan->fmtinfo->bpp);
	tegra_channel_update_gangports(chan);

	वापस 0;
पूर्ण

अटल पूर्णांक
tegra_channel_subscribe_event(काष्ठा v4l2_fh *fh,
			      स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_event_subscribe(fh, sub, 4, शून्य);
	पूर्ण

	वापस v4l2_ctrl_subscribe_event(fh, sub);
पूर्ण

अटल पूर्णांक tegra_channel_g_selection(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_selection *sel)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	काष्ठा v4l2_subdev_selection sdsel = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = sel->target,
	पूर्ण;
	पूर्णांक ret;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!v4l2_subdev_has_op(subdev, pad, get_selection))
		वापस -ENOTTY;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	/*
	 * Try the get selection operation and fallback to get क्रमmat अगर not
	 * implemented.
	 */
	ret = v4l2_subdev_call(subdev, pad, get_selection, शून्य, &sdsel);
	अगर (!ret)
		sel->r = sdsel.r;
	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	ret = v4l2_subdev_call(subdev, pad, get_fmt, शून्य, &fmt);
	अगर (ret < 0)
		वापस ret;

	sel->r.left = 0;
	sel->r.top = 0;
	sel->r.width = fmt.क्रमmat.width;
	sel->r.height = fmt.क्रमmat.height;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_s_selection(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_selection *sel)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक ret;
	काष्ठा v4l2_subdev_selection sdsel = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = sel->target,
		.flags = sel->flags,
		.r = sel->r,
	पूर्ण;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!v4l2_subdev_has_op(subdev, pad, set_selection))
		वापस -ENOTTY;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (vb2_is_busy(&chan->queue))
		वापस -EBUSY;

	ret = v4l2_subdev_call(subdev, pad, set_selection, शून्य, &sdsel);
	अगर (!ret) अणु
		sel->r = sdsel.r;
		/*
		 * Subdev active क्रमmat resolution may have changed during
		 * set selection operation. So, update channel क्रमmat to
		 * the sub-device active क्रमmat.
		 */
		वापस tegra_channel_set_subdev_active_fmt(chan);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_channel_g_edid(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_edid *edid)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!v4l2_subdev_has_op(subdev, pad, get_edid))
		वापस -ENOTTY;

	वापस v4l2_subdev_call(subdev, pad, get_edid, edid);
पूर्ण

अटल पूर्णांक tegra_channel_s_edid(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_edid *edid)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!v4l2_subdev_has_op(subdev, pad, set_edid))
		वापस -ENOTTY;

	वापस v4l2_subdev_call(subdev, pad, set_edid, edid);
पूर्ण

अटल पूर्णांक tegra_channel_g_dv_timings(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!v4l2_subdev_has_op(subdev, video, g_dv_timings))
		वापस -ENOTTY;

	वापस v4l2_device_call_until_err(chan->video.v4l2_dev, 0,
					  video, g_dv_timings, timings);
पूर्ण

अटल पूर्णांक tegra_channel_s_dv_timings(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;
	काष्ठा v4l2_bt_timings *bt = &timings->bt;
	काष्ठा v4l2_dv_timings curr_timings;
	पूर्णांक ret;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!v4l2_subdev_has_op(subdev, video, s_dv_timings))
		वापस -ENOTTY;

	ret = tegra_channel_g_dv_timings(file, fh, &curr_timings);
	अगर (ret)
		वापस ret;

	अगर (v4l2_match_dv_timings(timings, &curr_timings, 0, false))
		वापस 0;

	अगर (vb2_is_busy(&chan->queue))
		वापस -EBUSY;

	ret = v4l2_device_call_until_err(chan->video.v4l2_dev, 0,
					 video, s_dv_timings, timings);
	अगर (ret)
		वापस ret;

	chan->क्रमmat.width = bt->width;
	chan->क्रमmat.height = bt->height;
	chan->क्रमmat.bytesperline = bt->width * chan->fmtinfo->bpp;
	chan->क्रमmat.sizeimage = chan->क्रमmat.bytesperline * bt->height;
	tegra_channel_fmt_align(chan, &chan->क्रमmat, chan->fmtinfo->bpp);
	tegra_channel_update_gangports(chan);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_query_dv_timings(काष्ठा file *file, व्योम *fh,
					  काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!v4l2_subdev_has_op(subdev, video, query_dv_timings))
		वापस -ENOTTY;

	वापस v4l2_device_call_until_err(chan->video.v4l2_dev, 0,
					  video, query_dv_timings, timings);
पूर्ण

अटल पूर्णांक tegra_channel_क्रमागत_dv_timings(काष्ठा file *file, व्योम *fh,
					 काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!v4l2_subdev_has_op(subdev, pad, क्रमागत_dv_timings))
		वापस -ENOTTY;

	वापस v4l2_subdev_call(subdev, pad, क्रमागत_dv_timings, timings);
पूर्ण

अटल पूर्णांक tegra_channel_dv_timings_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_dv_timings_cap *cap)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!v4l2_subdev_has_op(subdev, pad, dv_timings_cap))
		वापस -ENOTTY;

	वापस v4l2_subdev_call(subdev, pad, dv_timings_cap, cap);
पूर्ण

अटल पूर्णांक tegra_channel_log_status(काष्ठा file *file, व्योम *fh)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);

	v4l2_device_call_all(chan->video.v4l2_dev, 0, core, log_status);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_क्रमागत_input(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_input *inp)
अणु
	काष्ठा tegra_vi_channel *chan = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;

	अगर (inp->index)
		वापस -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	subdev = tegra_channel_get_remote_source_subdev(chan);
	strscpy(inp->name, subdev->name, माप(inp->name));
	अगर (v4l2_subdev_has_op(subdev, pad, dv_timings_cap))
		inp->capabilities = V4L2_IN_CAP_DV_TIMINGS;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_g_input(काष्ठा file *file, व्योम *priv,
				 अचिन्हित पूर्णांक *i)
अणु
	*i = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_channel_s_input(काष्ठा file *file, व्योम *priv,
				 अचिन्हित पूर्णांक input)
अणु
	अगर (input > 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops tegra_channel_ioctl_ops = अणु
	.vidioc_querycap		= tegra_channel_querycap,
	.vidioc_g_parm			= tegra_channel_g_parm,
	.vidioc_s_parm			= tegra_channel_s_parm,
	.vidioc_क्रमागत_framesizes		= tegra_channel_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	= tegra_channel_क्रमागत_frameपूर्णांकervals,
	.vidioc_क्रमागत_fmt_vid_cap	= tegra_channel_क्रमागत_क्रमmat,
	.vidioc_g_fmt_vid_cap		= tegra_channel_get_क्रमmat,
	.vidioc_s_fmt_vid_cap		= tegra_channel_set_क्रमmat,
	.vidioc_try_fmt_vid_cap		= tegra_channel_try_क्रमmat,
	.vidioc_क्रमागत_input		= tegra_channel_क्रमागत_input,
	.vidioc_g_input			= tegra_channel_g_input,
	.vidioc_s_input			= tegra_channel_s_input,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
	.vidioc_subscribe_event		= tegra_channel_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
	.vidioc_g_selection		= tegra_channel_g_selection,
	.vidioc_s_selection		= tegra_channel_s_selection,
	.vidioc_g_edid			= tegra_channel_g_edid,
	.vidioc_s_edid			= tegra_channel_s_edid,
	.vidioc_g_dv_timings		= tegra_channel_g_dv_timings,
	.vidioc_s_dv_timings		= tegra_channel_s_dv_timings,
	.vidioc_query_dv_timings	= tegra_channel_query_dv_timings,
	.vidioc_क्रमागत_dv_timings		= tegra_channel_क्रमागत_dv_timings,
	.vidioc_dv_timings_cap		= tegra_channel_dv_timings_cap,
	.vidioc_log_status		= tegra_channel_log_status,
पूर्ण;

/*
 * V4L2 file operations
 */
अटल स्थिर काष्ठा v4l2_file_operations tegra_channel_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= video_ioctl2,
	.खोलो		= v4l2_fh_खोलो,
	.release	= vb2_fop_release,
	.पढ़ो		= vb2_fop_पढ़ो,
	.poll		= vb2_fop_poll,
	.mmap		= vb2_fop_mmap,
पूर्ण;

/*
 * V4L2 control operations
 */
अटल पूर्णांक vi_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा tegra_vi_channel *chan = container_of(ctrl->handler,
						     काष्ठा tegra_vi_channel,
						     ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_TEST_PATTERN:
		/* pattern change takes effect on next stream */
		chan->pg_mode = ctrl->val + 1;
		अवरोध;
	हाल V4L2_CID_TEGRA_SYNCPT_TIMEOUT_RETRY:
		chan->syncpt_समयout_retry = ctrl->val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vi_ctrl_ops = अणु
	.s_ctrl	= vi_s_ctrl,
पूर्ण;

#अगर IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG)
अटल स्थिर अक्षर *स्थिर vi_pattern_strings[] = अणु
	"Black/White Direct Mode",
	"Color Patch Mode",
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा v4l2_ctrl_config syncpt_समयout_ctrl = अणु
	.ops = &vi_ctrl_ops,
	.id = V4L2_CID_TEGRA_SYNCPT_TIMEOUT_RETRY,
	.name = "Syncpt timeout retry",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 1,
	.max = 10000,
	.step = 1,
	.def = 5,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक tegra_channel_setup_ctrl_handler(काष्ठा tegra_vi_channel *chan)
अणु
	पूर्णांक ret;

#अगर IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG)
	/* add test pattern control handler to v4l2 device */
	v4l2_ctrl_new_std_menu_items(&chan->ctrl_handler, &vi_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(vi_pattern_strings) - 1,
				     0, 0, vi_pattern_strings);
	अगर (chan->ctrl_handler.error) अणु
		dev_err(chan->vi->dev, "failed to add TPG ctrl handler: %d\n",
			chan->ctrl_handler.error);
		v4l2_ctrl_handler_मुक्त(&chan->ctrl_handler);
		वापस chan->ctrl_handler.error;
	पूर्ण
#अन्यथा
	काष्ठा v4l2_subdev *subdev;

	/* custom control */
	v4l2_ctrl_new_custom(&chan->ctrl_handler, &syncpt_समयout_ctrl, शून्य);
	अगर (chan->ctrl_handler.error) अणु
		dev_err(chan->vi->dev, "failed to add %s ctrl handler: %d\n",
			syncpt_समयout_ctrl.name,
			chan->ctrl_handler.error);
		v4l2_ctrl_handler_मुक्त(&chan->ctrl_handler);
		वापस chan->ctrl_handler.error;
	पूर्ण

	subdev = tegra_channel_get_remote_source_subdev(chan);
	अगर (!subdev)
		वापस -ENODEV;

	ret = v4l2_ctrl_add_handler(&chan->ctrl_handler, subdev->ctrl_handler,
				    शून्य, true);
	अगर (ret < 0) अणु
		dev_err(chan->vi->dev,
			"failed to add subdev %s ctrl handler: %d\n",
			subdev->name, ret);
		v4l2_ctrl_handler_मुक्त(&chan->ctrl_handler);
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	/* setup the controls */
	ret = v4l2_ctrl_handler_setup(&chan->ctrl_handler);
	अगर (ret < 0) अणु
		dev_err(chan->vi->dev,
			"failed to setup v4l2 ctrl handler: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* VI only support 2 क्रमmats in TPG mode */
अटल व्योम vi_tpg_fmts_biपंचांगap_init(काष्ठा tegra_vi_channel *chan)
अणु
	पूर्णांक index;

	biपंचांगap_zero(chan->tpg_fmts_biपंचांगap, MAX_FORMAT_NUM);

	index = tegra_get_क्रमmat_idx_by_code(chan->vi,
					     MEDIA_BUS_FMT_SRGGB10_1X10, 0);
	biपंचांगap_set(chan->tpg_fmts_biपंचांगap, index, 1);

	index = tegra_get_क्रमmat_idx_by_code(chan->vi,
					     MEDIA_BUS_FMT_RGB888_1X32_PADHI,
					     0);
	biपंचांगap_set(chan->tpg_fmts_biपंचांगap, index, 1);
पूर्ण

अटल पूर्णांक vi_fmts_biपंचांगap_init(काष्ठा tegra_vi_channel *chan)
अणु
	पूर्णांक index, ret, match_code = 0;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा v4l2_subdev_mbus_code_क्रमागत code = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	biपंचांगap_zero(chan->fmts_biपंचांगap, MAX_FORMAT_NUM);

	/*
	 * Set the biपंचांगap bits based on all the matched क्रमmats between the
	 * available media bus क्रमmats of sub-device and the pre-defined Tegra
	 * supported video क्रमmats.
	 */
	subdev = tegra_channel_get_remote_source_subdev(chan);
	जबतक (1) अणु
		ret = v4l2_subdev_call(subdev, pad, क्रमागत_mbus_code,
				       शून्य, &code);
		अगर (ret < 0)
			अवरोध;

		index = tegra_get_क्रमmat_idx_by_code(chan->vi, code.code, 0);
		जबतक (index >= 0) अणु
			biपंचांगap_set(chan->fmts_biपंचांगap, index, 1);
			अगर (!match_code)
				match_code = code.code;
			/* look क्रम other क्रमmats with same mbus code */
			index = tegra_get_क्रमmat_idx_by_code(chan->vi,
							     code.code,
							     index + 1);
		पूर्ण

		code.index++;
	पूर्ण

	/*
	 * Set the biपंचांगap bit corresponding to शेष tegra video क्रमmat अगर
	 * there are no matched क्रमmats.
	 */
	अगर (!match_code) अणु
		match_code = tegra_शेष_क्रमmat.code;
		index = tegra_get_क्रमmat_idx_by_code(chan->vi, match_code, 0);
		अगर (WARN_ON(index < 0))
			वापस -EINVAL;

		biपंचांगap_set(chan->fmts_biपंचांगap, index, 1);
	पूर्ण

	/* initialize channel क्रमmat to the sub-device active क्रमmat */
	tegra_channel_set_subdev_active_fmt(chan);

	वापस 0;
पूर्ण

अटल व्योम tegra_channel_host1x_syncpts_मुक्त(काष्ठा tegra_vi_channel *chan)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chan->numgangports; i++) अणु
		host1x_syncpt_put(chan->mw_ack_sp[i]);
		host1x_syncpt_put(chan->frame_start_sp[i]);
	पूर्ण
पूर्ण

अटल व्योम tegra_channel_cleanup(काष्ठा tegra_vi_channel *chan)
अणु
	v4l2_ctrl_handler_मुक्त(&chan->ctrl_handler);
	media_entity_cleanup(&chan->video.entity);
	tegra_channel_host1x_syncpts_मुक्त(chan);
	mutex_destroy(&chan->video_lock);
पूर्ण

व्योम tegra_channels_cleanup(काष्ठा tegra_vi *vi)
अणु
	काष्ठा tegra_vi_channel *chan, *पंचांगp;

	अगर (!vi)
		वापस;

	list_क्रम_each_entry_safe(chan, पंचांगp, &vi->vi_chans, list) अणु
		tegra_channel_cleanup(chan);
		list_del(&chan->list);
		kमुक्त(chan);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_channel_host1x_syncpt_init(काष्ठा tegra_vi_channel *chan)
अणु
	काष्ठा tegra_vi *vi = chan->vi;
	अचिन्हित दीर्घ flags = HOST1X_SYNCPT_CLIENT_MANAGED;
	काष्ठा host1x_syncpt *fs_sp;
	काष्ठा host1x_syncpt *mw_sp;
	पूर्णांक ret, i;

	क्रम (i = 0; i < chan->numgangports; i++) अणु
		fs_sp = host1x_syncpt_request(&vi->client, flags);
		अगर (!fs_sp) अणु
			dev_err(vi->dev, "failed to request frame start syncpoint\n");
			ret = -ENOMEM;
			जाओ मुक्त_syncpts;
		पूर्ण

		mw_sp = host1x_syncpt_request(&vi->client, flags);
		अगर (!mw_sp) अणु
			dev_err(vi->dev, "failed to request memory ack syncpoint\n");
			host1x_syncpt_put(fs_sp);
			ret = -ENOMEM;
			जाओ मुक्त_syncpts;
		पूर्ण

		chan->frame_start_sp[i] = fs_sp;
		chan->mw_ack_sp[i] = mw_sp;
		spin_lock_init(&chan->sp_incr_lock[i]);
	पूर्ण

	वापस 0;

मुक्त_syncpts:
	tegra_channel_host1x_syncpts_मुक्त(chan);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_channel_init(काष्ठा tegra_vi_channel *chan)
अणु
	काष्ठा tegra_vi *vi = chan->vi;
	काष्ठा tegra_video_device *vid = dev_get_drvdata(vi->client.host);
	पूर्णांक ret;

	mutex_init(&chan->video_lock);
	INIT_LIST_HEAD(&chan->capture);
	INIT_LIST_HEAD(&chan->करोne);
	spin_lock_init(&chan->start_lock);
	spin_lock_init(&chan->करोne_lock);
	init_रुकोqueue_head(&chan->start_रुको);
	init_रुकोqueue_head(&chan->करोne_रुको);

	/* initialize the video क्रमmat */
	chan->fmtinfo = &tegra_शेष_क्रमmat;
	chan->क्रमmat.pixelक्रमmat = chan->fmtinfo->fourcc;
	chan->क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;
	chan->क्रमmat.field = V4L2_FIELD_NONE;
	chan->क्रमmat.width = TEGRA_DEF_WIDTH;
	chan->क्रमmat.height = TEGRA_DEF_HEIGHT;
	chan->क्रमmat.bytesperline = TEGRA_DEF_WIDTH * chan->fmtinfo->bpp;
	chan->क्रमmat.sizeimage = chan->क्रमmat.bytesperline * TEGRA_DEF_HEIGHT;
	tegra_channel_fmt_align(chan, &chan->क्रमmat, chan->fmtinfo->bpp);

	ret = tegra_channel_host1x_syncpt_init(chan);
	अगर (ret)
		वापस ret;

	/* initialize the media entity */
	chan->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&chan->video.entity, 1, &chan->pad);
	अगर (ret < 0) अणु
		dev_err(vi->dev,
			"failed to initialize media entity: %d\n", ret);
		जाओ मुक्त_syncpts;
	पूर्ण

	ret = v4l2_ctrl_handler_init(&chan->ctrl_handler, MAX_CID_CONTROLS);
	अगर (chan->ctrl_handler.error) अणु
		dev_err(vi->dev,
			"failed to initialize v4l2 ctrl handler: %d\n", ret);
		जाओ cleanup_media;
	पूर्ण

	/* initialize the video_device */
	chan->video.fops = &tegra_channel_fops;
	chan->video.v4l2_dev = &vid->v4l2_dev;
	chan->video.release = video_device_release_empty;
	chan->video.queue = &chan->queue;
	snम_लिखो(chan->video.name, माप(chan->video.name), "%s-%s-%u",
		 dev_name(vi->dev), "output", chan->portnos[0]);
	chan->video.vfl_type = VFL_TYPE_VIDEO;
	chan->video.vfl_dir = VFL_सूची_RX;
	chan->video.ioctl_ops = &tegra_channel_ioctl_ops;
	chan->video.ctrl_handler = &chan->ctrl_handler;
	chan->video.lock = &chan->video_lock;
	chan->video.device_caps = V4L2_CAP_VIDEO_CAPTURE |
				  V4L2_CAP_STREAMING |
				  V4L2_CAP_READWRITE;
	video_set_drvdata(&chan->video, chan);

	chan->queue.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	chan->queue.io_modes = VB2_MMAP | VB2_DMABUF | VB2_READ;
	chan->queue.lock = &chan->video_lock;
	chan->queue.drv_priv = chan;
	chan->queue.buf_काष्ठा_size = माप(काष्ठा tegra_channel_buffer);
	chan->queue.ops = &tegra_channel_queue_qops;
	chan->queue.mem_ops = &vb2_dma_contig_memops;
	chan->queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	chan->queue.min_buffers_needed = 2;
	chan->queue.dev = vi->dev;
	ret = vb2_queue_init(&chan->queue);
	अगर (ret < 0) अणु
		dev_err(vi->dev, "failed to initialize vb2 queue: %d\n", ret);
		जाओ मुक्त_v4l2_ctrl_hdl;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		v4l2_async_notअगरier_init(&chan->notअगरier);

	वापस 0;

मुक्त_v4l2_ctrl_hdl:
	v4l2_ctrl_handler_मुक्त(&chan->ctrl_handler);
cleanup_media:
	media_entity_cleanup(&chan->video.entity);
मुक्त_syncpts:
	tegra_channel_host1x_syncpts_मुक्त(chan);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_vi_channel_alloc(काष्ठा tegra_vi *vi, अचिन्हित पूर्णांक port_num,
				  काष्ठा device_node *node, अचिन्हित पूर्णांक lanes)
अणु
	काष्ठा tegra_vi_channel *chan;
	अचिन्हित पूर्णांक i;

	/*
	 * Do not use devm_kzalloc as memory is मुक्तd immediately
	 * when device instance is unbound but application might still
	 * be holding the device node खोलो. Channel memory allocated
	 * with kzalloc is मुक्तd during video device release callback.
	 */
	chan = kzalloc(माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस -ENOMEM;

	chan->vi = vi;
	chan->portnos[0] = port_num;
	/*
	 * For data lanes more than maximum csi lanes per brick, multiple of
	 * x4 ports are used simultaneously क्रम capture.
	 */
	अगर (lanes <= CSI_LANES_PER_BRICK)
		chan->totalports = 1;
	अन्यथा
		chan->totalports = lanes / CSI_LANES_PER_BRICK;
	chan->numgangports = chan->totalports;

	क्रम (i = 1; i < chan->totalports; i++)
		chan->portnos[i] = chan->portnos[0] + i * CSI_PORTS_PER_BRICK;

	chan->of_node = node;
	list_add_tail(&chan->list, &vi->vi_chans);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_vi_tpg_channels_alloc(काष्ठा tegra_vi *vi)
अणु
	अचिन्हित पूर्णांक port_num;
	अचिन्हित पूर्णांक nchannels = vi->soc->vi_max_channels;
	पूर्णांक ret;

	क्रम (port_num = 0; port_num < nchannels; port_num++) अणु
		ret = tegra_vi_channel_alloc(vi, port_num,
					     vi->dev->of_node, 2);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_vi_channels_alloc(काष्ठा tegra_vi *vi)
अणु
	काष्ठा device_node *node = vi->dev->of_node;
	काष्ठा device_node *ep = शून्य;
	काष्ठा device_node *ports;
	काष्ठा device_node *port;
	अचिन्हित पूर्णांक port_num;
	काष्ठा device_node *parent;
	काष्ठा v4l2_fwnode_endpoपूर्णांक v4l2_ep = अणु .bus_type = 0 पूर्ण;
	अचिन्हित पूर्णांक lanes;
	पूर्णांक ret = 0;

	ports = of_get_child_by_name(node, "ports");
	अगर (!ports)
		वापस -ENODEV;

	क्रम_each_child_of_node(ports, port) अणु
		अगर (!of_node_name_eq(port, "port"))
			जारी;

		ret = of_property_पढ़ो_u32(port, "reg", &port_num);
		अगर (ret < 0)
			जारी;

		अगर (port_num > vi->soc->vi_max_channels) अणु
			dev_err(vi->dev, "invalid port num %d for %pOF\n",
				port_num, port);
			ret = -EINVAL;
			of_node_put(port);
			जाओ cleanup;
		पूर्ण

		ep = of_get_child_by_name(port, "endpoint");
		अगर (!ep)
			जारी;

		parent = of_graph_get_remote_port_parent(ep);
		of_node_put(ep);
		अगर (!parent)
			जारी;

		ep = of_graph_get_endpoपूर्णांक_by_regs(parent, 0, 0);
		of_node_put(parent);
		ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep),
						 &v4l2_ep);
		of_node_put(ep);
		अगर (ret)
			जारी;

		lanes = v4l2_ep.bus.mipi_csi2.num_data_lanes;
		ret = tegra_vi_channel_alloc(vi, port_num, port, lanes);
		अगर (ret < 0) अणु
			of_node_put(port);
			जाओ cleanup;
		पूर्ण
	पूर्ण

cleanup:
	of_node_put(ports);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_vi_channels_init(काष्ठा tegra_vi *vi)
अणु
	काष्ठा tegra_vi_channel *chan;
	पूर्णांक ret;

	list_क्रम_each_entry(chan, &vi->vi_chans, list) अणु
		ret = tegra_channel_init(chan);
		अगर (ret < 0) अणु
			dev_err(vi->dev,
				"failed to initialize channel-%d: %d\n",
				chan->portnos[0], ret);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	वापस 0;

cleanup:
	list_क्रम_each_entry_जारी_reverse(chan, &vi->vi_chans, list)
		tegra_channel_cleanup(chan);

	वापस ret;
पूर्ण

व्योम tegra_v4l2_nodes_cleanup_tpg(काष्ठा tegra_video_device *vid)
अणु
	काष्ठा tegra_vi *vi = vid->vi;
	काष्ठा tegra_csi *csi = vid->csi;
	काष्ठा tegra_csi_channel *csi_chan;
	काष्ठा tegra_vi_channel *chan;

	list_क्रम_each_entry(chan, &vi->vi_chans, list)
		vb2_video_unरेजिस्टर_device(&chan->video);

	list_क्रम_each_entry(csi_chan, &csi->csi_chans, list)
		v4l2_device_unरेजिस्टर_subdev(&csi_chan->subdev);
पूर्ण

पूर्णांक tegra_v4l2_nodes_setup_tpg(काष्ठा tegra_video_device *vid)
अणु
	काष्ठा tegra_vi *vi = vid->vi;
	काष्ठा tegra_csi *csi = vid->csi;
	काष्ठा tegra_vi_channel *vi_chan;
	काष्ठा tegra_csi_channel *csi_chan;
	u32 link_flags = MEDIA_LNK_FL_ENABLED;
	पूर्णांक ret;

	अगर (!vi || !csi)
		वापस -ENODEV;

	csi_chan = list_first_entry(&csi->csi_chans,
				    काष्ठा tegra_csi_channel, list);

	list_क्रम_each_entry(vi_chan, &vi->vi_chans, list) अणु
		काष्ठा media_entity *source = &csi_chan->subdev.entity;
		काष्ठा media_entity *sink = &vi_chan->video.entity;
		काष्ठा media_pad *source_pad = csi_chan->pads;
		काष्ठा media_pad *sink_pad = &vi_chan->pad;

		ret = v4l2_device_रेजिस्टर_subdev(&vid->v4l2_dev,
						  &csi_chan->subdev);
		अगर (ret) अणु
			dev_err(vi->dev,
				"failed to register subdev: %d\n", ret);
			जाओ cleanup;
		पूर्ण

		ret = video_रेजिस्टर_device(&vi_chan->video,
					    VFL_TYPE_VIDEO, -1);
		अगर (ret < 0) अणु
			dev_err(vi->dev,
				"failed to register video device: %d\n", ret);
			जाओ cleanup;
		पूर्ण

		dev_dbg(vi->dev, "creating %s:%u -> %s:%u link\n",
			source->name, source_pad->index,
			sink->name, sink_pad->index);

		ret = media_create_pad_link(source, source_pad->index,
					    sink, sink_pad->index,
					    link_flags);
		अगर (ret < 0) अणु
			dev_err(vi->dev,
				"failed to create %s:%u -> %s:%u link: %d\n",
				source->name, source_pad->index,
				sink->name, sink_pad->index, ret);
			जाओ cleanup;
		पूर्ण

		ret = tegra_channel_setup_ctrl_handler(vi_chan);
		अगर (ret < 0)
			जाओ cleanup;

		v4l2_set_subdev_hostdata(&csi_chan->subdev, vi_chan);
		vi_tpg_fmts_biपंचांगap_init(vi_chan);
		csi_chan = list_next_entry(csi_chan, list);
	पूर्ण

	वापस 0;

cleanup:
	tegra_v4l2_nodes_cleanup_tpg(vid);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused vi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_vi *vi = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_enable(vi->vdd);
	अगर (ret) अणु
		dev_err(dev, "failed to enable VDD supply: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_set_rate(vi->clk, vi->soc->vi_max_clk_hz);
	अगर (ret) अणु
		dev_err(dev, "failed to set vi clock rate: %d\n", ret);
		जाओ disable_vdd;
	पूर्ण

	ret = clk_prepare_enable(vi->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable vi clock: %d\n", ret);
		जाओ disable_vdd;
	पूर्ण

	वापस 0;

disable_vdd:
	regulator_disable(vi->vdd);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused vi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_vi *vi = dev_get_drvdata(dev);

	clk_disable_unprepare(vi->clk);

	regulator_disable(vi->vdd);

	वापस 0;
पूर्ण

/*
 * Graph Management
 */
अटल काष्ठा tegra_vi_graph_entity *
tegra_vi_graph_find_entity(काष्ठा tegra_vi_channel *chan,
			   स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा tegra_vi_graph_entity *entity;
	काष्ठा v4l2_async_subdev *asd;

	list_क्रम_each_entry(asd, &chan->notअगरier.asd_list, asd_list) अणु
		entity = to_tegra_vi_graph_entity(asd);
		अगर (entity->asd.match.fwnode == fwnode)
			वापस entity;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक tegra_vi_graph_build(काष्ठा tegra_vi_channel *chan,
				काष्ठा tegra_vi_graph_entity *entity)
अणु
	काष्ठा tegra_vi *vi = chan->vi;
	काष्ठा tegra_vi_graph_entity *ent;
	काष्ठा fwnode_handle *ep = शून्य;
	काष्ठा v4l2_fwnode_link link;
	काष्ठा media_entity *local = entity->entity;
	काष्ठा media_entity *remote;
	काष्ठा media_pad *local_pad;
	काष्ठा media_pad *remote_pad;
	u32 link_flags = MEDIA_LNK_FL_ENABLED;
	पूर्णांक ret = 0;

	dev_dbg(vi->dev, "creating links for entity %s\n", local->name);

	जबतक (1) अणु
		ep = fwnode_graph_get_next_endpoपूर्णांक(entity->asd.match.fwnode,
						    ep);
		अगर (!ep)
			अवरोध;

		ret = v4l2_fwnode_parse_link(ep, &link);
		अगर (ret < 0) अणु
			dev_err(vi->dev, "failed to parse link for %pOF: %d\n",
				to_of_node(ep), ret);
			जारी;
		पूर्ण

		अगर (link.local_port >= local->num_pads) अणु
			dev_err(vi->dev, "invalid port number %u on %pOF\n",
				link.local_port, to_of_node(link.local_node));
			v4l2_fwnode_put_link(&link);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		local_pad = &local->pads[link.local_port];
		/* Remote node is vi node. So use channel video entity and pad
		 * as remote/sink.
		 */
		अगर (link.remote_node == of_fwnode_handle(vi->dev->of_node)) अणु
			remote = &chan->video.entity;
			remote_pad = &chan->pad;
			जाओ create_link;
		पूर्ण

		/*
		 * Skip sink ports, they will be processed from the other end
		 * of the link.
		 */
		अगर (local_pad->flags & MEDIA_PAD_FL_SINK) अणु
			dev_dbg(vi->dev, "skipping sink port %pOF:%u\n",
				to_of_node(link.local_node), link.local_port);
			v4l2_fwnode_put_link(&link);
			जारी;
		पूर्ण

		/* find the remote entity from notअगरier list */
		ent = tegra_vi_graph_find_entity(chan, link.remote_node);
		अगर (!ent) अणु
			dev_err(vi->dev, "no entity found for %pOF\n",
				to_of_node(link.remote_node));
			v4l2_fwnode_put_link(&link);
			ret = -ENODEV;
			अवरोध;
		पूर्ण

		remote = ent->entity;
		अगर (link.remote_port >= remote->num_pads) अणु
			dev_err(vi->dev, "invalid port number %u on %pOF\n",
				link.remote_port,
				to_of_node(link.remote_node));
			v4l2_fwnode_put_link(&link);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		remote_pad = &remote->pads[link.remote_port];

create_link:
		dev_dbg(vi->dev, "creating %s:%u -> %s:%u link\n",
			local->name, local_pad->index,
			remote->name, remote_pad->index);

		ret = media_create_pad_link(local, local_pad->index,
					    remote, remote_pad->index,
					    link_flags);
		v4l2_fwnode_put_link(&link);
		अगर (ret < 0) अणु
			dev_err(vi->dev,
				"failed to create %s:%u -> %s:%u link: %d\n",
				local->name, local_pad->index,
				remote->name, remote_pad->index, ret);
			अवरोध;
		पूर्ण
	पूर्ण

	fwnode_handle_put(ep);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_vi_graph_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा tegra_vi_graph_entity *entity;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा tegra_vi_channel *chan;
	काष्ठा tegra_vi *vi;
	पूर्णांक ret;

	chan = container_of(notअगरier, काष्ठा tegra_vi_channel, notअगरier);
	vi = chan->vi;

	dev_dbg(vi->dev, "notify complete, all subdevs registered\n");

	/*
	 * Video device node should be created at the end of all the device
	 * related initialization/setup.
	 * Current video_रेजिस्टर_device() करोes both initialize and रेजिस्टर
	 * video device in same API.
	 *
	 * TODO: Update v4l2-dev driver to split initialize and रेजिस्टर पूर्णांकo
	 * separate APIs and then update Tegra video driver to करो video device
	 * initialize followed by all video device related setup and then
	 * रेजिस्टर the video device.
	 */
	ret = video_रेजिस्टर_device(&chan->video, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		dev_err(vi->dev,
			"failed to register video device: %d\n", ret);
		जाओ unरेजिस्टर_video;
	पूर्ण

	/* create links between the entities */
	list_क्रम_each_entry(asd, &chan->notअगरier.asd_list, asd_list) अणु
		entity = to_tegra_vi_graph_entity(asd);
		ret = tegra_vi_graph_build(chan, entity);
		अगर (ret < 0)
			जाओ unरेजिस्टर_video;
	पूर्ण

	ret = tegra_channel_setup_ctrl_handler(chan);
	अगर (ret < 0) अणु
		dev_err(vi->dev,
			"failed to setup channel controls: %d\n", ret);
		जाओ unरेजिस्टर_video;
	पूर्ण

	ret = vi_fmts_biपंचांगap_init(chan);
	अगर (ret < 0) अणु
		dev_err(vi->dev,
			"failed to initialize formats bitmap: %d\n", ret);
		जाओ unरेजिस्टर_video;
	पूर्ण

	subdev = tegra_channel_get_remote_csi_subdev(chan);
	अगर (!subdev) अणु
		ret = -ENODEV;
		dev_err(vi->dev,
			"failed to get remote csi subdev: %d\n", ret);
		जाओ unरेजिस्टर_video;
	पूर्ण

	v4l2_set_subdev_hostdata(subdev, chan);

	subdev = tegra_channel_get_remote_source_subdev(chan);
	v4l2_set_subdev_hostdata(subdev, chan);

	वापस 0;

unरेजिस्टर_video:
	vb2_video_unरेजिस्टर_device(&chan->video);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_vi_graph_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				       काष्ठा v4l2_subdev *subdev,
				       काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा tegra_vi_graph_entity *entity;
	काष्ठा tegra_vi *vi;
	काष्ठा tegra_vi_channel *chan;

	chan = container_of(notअगरier, काष्ठा tegra_vi_channel, notअगरier);
	vi = chan->vi;

	/*
	 * Locate the entity corresponding to the bound subdev and store the
	 * subdev poपूर्णांकer.
	 */
	entity = tegra_vi_graph_find_entity(chan, subdev->fwnode);
	अगर (!entity) अणु
		dev_err(vi->dev, "no entity for subdev %s\n", subdev->name);
		वापस -EINVAL;
	पूर्ण

	अगर (entity->subdev) अणु
		dev_err(vi->dev, "duplicate subdev for node %pOF\n",
			to_of_node(entity->asd.match.fwnode));
		वापस -EINVAL;
	पूर्ण

	dev_dbg(vi->dev, "subdev %s bound\n", subdev->name);
	entity->entity = &subdev->entity;
	entity->subdev = subdev;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations tegra_vi_async_ops = अणु
	.bound = tegra_vi_graph_notअगरy_bound,
	.complete = tegra_vi_graph_notअगरy_complete,
पूर्ण;

अटल पूर्णांक tegra_vi_graph_parse_one(काष्ठा tegra_vi_channel *chan,
				    काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा tegra_vi *vi = chan->vi;
	काष्ठा fwnode_handle *ep = शून्य;
	काष्ठा fwnode_handle *remote = शून्य;
	काष्ठा tegra_vi_graph_entity *tvge;
	काष्ठा device_node *node = शून्य;
	पूर्णांक ret;

	dev_dbg(vi->dev, "parsing node %pOF\n", to_of_node(fwnode));

	/* parse all the remote entities and put them पूर्णांकo the list */
	क्रम_each_endpoपूर्णांक_of_node(to_of_node(fwnode), node) अणु
		ep = of_fwnode_handle(node);
		remote = fwnode_graph_get_remote_port_parent(ep);
		अगर (!remote) अणु
			dev_err(vi->dev,
				"remote device at %pOF not found\n", node);
			ret = -EINVAL;
			जाओ cleanup;
		पूर्ण

		/* skip entities that are alपढ़ोy processed */
		अगर (remote == dev_fwnode(vi->dev) ||
		    tegra_vi_graph_find_entity(chan, remote)) अणु
			fwnode_handle_put(remote);
			जारी;
		पूर्ण

		tvge = v4l2_async_notअगरier_add_fwnode_subdev(&chan->notअगरier,
				remote, काष्ठा tegra_vi_graph_entity);
		अगर (IS_ERR(tvge)) अणु
			ret = PTR_ERR(tvge);
			dev_err(vi->dev,
				"failed to add subdev to notifier: %d\n", ret);
			fwnode_handle_put(remote);
			जाओ cleanup;
		पूर्ण

		ret = tegra_vi_graph_parse_one(chan, remote);
		अगर (ret < 0) अणु
			fwnode_handle_put(remote);
			जाओ cleanup;
		पूर्ण

		fwnode_handle_put(remote);
	पूर्ण

	वापस 0;

cleanup:
	dev_err(vi->dev, "failed parsing the graph: %d\n", ret);
	v4l2_async_notअगरier_cleanup(&chan->notअगरier);
	of_node_put(node);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_vi_graph_init(काष्ठा tegra_vi *vi)
अणु
	काष्ठा tegra_video_device *vid = dev_get_drvdata(vi->client.host);
	काष्ठा tegra_vi_channel *chan;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(vi->dev);
	पूर्णांक ret;
	काष्ठा fwnode_handle *remote = शून्य;

	/*
	 * Walk the links to parse the full graph. Each channel will have
	 * one endpoपूर्णांक of the composite node. Start by parsing the
	 * composite node and parse the remote entities in turn.
	 * Each channel will रेजिस्टर v4l2 async notअगरier to make the graph
	 * independent between the channels so we can the current channel
	 * in हाल of something wrong during graph parsing and जारी with
	 * next channels.
	 */
	list_क्रम_each_entry(chan, &vi->vi_chans, list) अणु
		remote = fwnode_graph_get_remote_node(fwnode, chan->portnos[0],
						      0);
		अगर (!remote)
			जारी;

		ret = tegra_vi_graph_parse_one(chan, remote);
		fwnode_handle_put(remote);
		अगर (ret < 0 || list_empty(&chan->notअगरier.asd_list))
			जारी;

		chan->notअगरier.ops = &tegra_vi_async_ops;
		ret = v4l2_async_notअगरier_रेजिस्टर(&vid->v4l2_dev,
						   &chan->notअगरier);
		अगर (ret < 0) अणु
			dev_err(vi->dev,
				"failed to register channel %d notifier: %d\n",
				chan->portnos[0], ret);
			v4l2_async_notअगरier_cleanup(&chan->notअगरier);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_vi_graph_cleanup(काष्ठा tegra_vi *vi)
अणु
	काष्ठा tegra_vi_channel *chan;

	list_क्रम_each_entry(chan, &vi->vi_chans, list) अणु
		vb2_video_unरेजिस्टर_device(&chan->video);
		v4l2_async_notअगरier_unरेजिस्टर(&chan->notअगरier);
		v4l2_async_notअगरier_cleanup(&chan->notअगरier);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_vi_init(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_video_device *vid = dev_get_drvdata(client->host);
	काष्ठा tegra_vi *vi = host1x_client_to_vi(client);
	काष्ठा tegra_vi_channel *chan, *पंचांगp;
	पूर्णांक ret;

	vid->media_dev.hw_revision = vi->soc->hw_revision;
	snम_लिखो(vid->media_dev.bus_info, माप(vid->media_dev.bus_info),
		 "platform:%s", dev_name(vi->dev));

	INIT_LIST_HEAD(&vi->vi_chans);

	अगर (IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		ret = tegra_vi_tpg_channels_alloc(vi);
	अन्यथा
		ret = tegra_vi_channels_alloc(vi);
	अगर (ret < 0) अणु
		dev_err(vi->dev,
			"failed to allocate vi channels: %d\n", ret);
		जाओ मुक्त_chans;
	पूर्ण

	ret = tegra_vi_channels_init(vi);
	अगर (ret < 0)
		जाओ मुक्त_chans;

	vid->vi = vi;

	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG)) अणु
		ret = tegra_vi_graph_init(vi);
		अगर (ret < 0)
			जाओ cleanup_chans;
	पूर्ण

	वापस 0;

cleanup_chans:
	list_क्रम_each_entry(chan, &vi->vi_chans, list)
		tegra_channel_cleanup(chan);
मुक्त_chans:
	list_क्रम_each_entry_safe(chan, पंचांगp, &vi->vi_chans, list) अणु
		list_del(&chan->list);
		kमुक्त(chan);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_vi_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_vi *vi = host1x_client_to_vi(client);

	/*
	 * Do not cleanup the channels here as application might still be
	 * holding video device nodes. Channels cleanup will happen during
	 * v4l2_device release callback which माला_लो called after all video
	 * device nodes are released.
	 */

	अगर (!IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		tegra_vi_graph_cleanup(vi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा host1x_client_ops vi_client_ops = अणु
	.init = tegra_vi_init,
	.निकास = tegra_vi_निकास,
पूर्ण;

अटल पूर्णांक tegra_vi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_vi *vi;
	पूर्णांक ret;

	vi = devm_kzalloc(&pdev->dev, माप(*vi), GFP_KERNEL);
	अगर (!vi)
		वापस -ENOMEM;

	vi->iomem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(vi->iomem))
		वापस PTR_ERR(vi->iomem);

	vi->soc = of_device_get_match_data(&pdev->dev);

	vi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(vi->clk)) अणु
		ret = PTR_ERR(vi->clk);
		dev_err(&pdev->dev, "failed to get vi clock: %d\n", ret);
		वापस ret;
	पूर्ण

	vi->vdd = devm_regulator_get(&pdev->dev, "avdd-dsi-csi");
	अगर (IS_ERR(vi->vdd)) अणु
		ret = PTR_ERR(vi->vdd);
		dev_err(&pdev->dev, "failed to get VDD supply: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!pdev->dev.pm_करोमुख्य) अणु
		ret = -ENOENT;
		dev_warn(&pdev->dev, "PM domain is not attached: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_of_platक्रमm_populate(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"failed to populate vi child device: %d\n", ret);
		वापस ret;
	पूर्ण

	vi->dev = &pdev->dev;
	vi->ops = vi->soc->ops;
	platक्रमm_set_drvdata(pdev, vi);
	pm_runसमय_enable(&pdev->dev);

	/* initialize host1x पूर्णांकerface */
	INIT_LIST_HEAD(&vi->client.list);
	vi->client.ops = &vi_client_ops;
	vi->client.dev = &pdev->dev;

	ret = host1x_client_रेजिस्टर(&vi->client);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"failed to register host1x client: %d\n", ret);
		जाओ rpm_disable;
	पूर्ण

	वापस 0;

rpm_disable:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_vi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_vi *vi = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = host1x_client_unरेजिस्टर(&vi->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev,
			"failed to unregister host1x client: %d\n", err);
		वापस err;
	पूर्ण

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_vi_of_id_table[] = अणु
#अगर defined(CONFIG_ARCH_TEGRA_210_SOC)
	अणु .compatible = "nvidia,tegra210-vi", .data = &tegra210_vi_soc पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_vi_of_id_table);

अटल स्थिर काष्ठा dev_pm_ops tegra_vi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(vi_runसमय_suspend, vi_runसमय_resume, शून्य)
पूर्ण;

काष्ठा platक्रमm_driver tegra_vi_driver = अणु
	.driver = अणु
		.name = "tegra-vi",
		.of_match_table = tegra_vi_of_id_table,
		.pm = &tegra_vi_pm_ops,
	पूर्ण,
	.probe = tegra_vi_probe,
	.हटाओ = tegra_vi_हटाओ,
पूर्ण;
