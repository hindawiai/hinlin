<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_video.c  --  R-Car VSP1 Video Node
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/रुको.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "vsp1.h"
#समावेश "vsp1_brx.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_entity.h"
#समावेश "vsp1_hgo.h"
#समावेश "vsp1_hgt.h"
#समावेश "vsp1_pipe.h"
#समावेश "vsp1_rwpf.h"
#समावेश "vsp1_uds.h"
#समावेश "vsp1_video.h"

#घोषणा VSP1_VIDEO_DEF_FORMAT		V4L2_PIX_FMT_YUYV
#घोषणा VSP1_VIDEO_DEF_WIDTH		1024
#घोषणा VSP1_VIDEO_DEF_HEIGHT		768

#घोषणा VSP1_VIDEO_MAX_WIDTH		8190U
#घोषणा VSP1_VIDEO_MAX_HEIGHT		8190U

/* -----------------------------------------------------------------------------
 * Helper functions
 */

अटल काष्ठा v4l2_subdev *
vsp1_video_remote_subdev(काष्ठा media_pad *local, u32 *pad)
अणु
	काष्ठा media_pad *remote;

	remote = media_entity_remote_pad(local);
	अगर (!remote || !is_media_entity_v4l2_subdev(remote->entity))
		वापस शून्य;

	अगर (pad)
		*pad = remote->index;

	वापस media_entity_to_v4l2_subdev(remote->entity);
पूर्ण

अटल पूर्णांक vsp1_video_verअगरy_क्रमmat(काष्ठा vsp1_video *video)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक ret;

	subdev = vsp1_video_remote_subdev(&video->pad, &fmt.pad);
	अगर (subdev == शून्य)
		वापस -EINVAL;

	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(subdev, pad, get_fmt, शून्य, &fmt);
	अगर (ret < 0)
		वापस ret == -ENOIOCTLCMD ? -EINVAL : ret;

	अगर (video->rwpf->fmtinfo->mbus != fmt.क्रमmat.code ||
	    video->rwpf->क्रमmat.height != fmt.क्रमmat.height ||
	    video->rwpf->क्रमmat.width != fmt.क्रमmat.width)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __vsp1_video_try_क्रमmat(काष्ठा vsp1_video *video,
				   काष्ठा v4l2_pix_क्रमmat_mplane *pix,
				   स्थिर काष्ठा vsp1_क्रमmat_info **fmtinfo)
अणु
	अटल स्थिर u32 xrgb_क्रमmats[][2] = अणु
		अणु V4L2_PIX_FMT_RGB444, V4L2_PIX_FMT_XRGB444 पूर्ण,
		अणु V4L2_PIX_FMT_RGB555, V4L2_PIX_FMT_XRGB555 पूर्ण,
		अणु V4L2_PIX_FMT_BGR32, V4L2_PIX_FMT_XBGR32 पूर्ण,
		अणु V4L2_PIX_FMT_RGB32, V4L2_PIX_FMT_XRGB32 पूर्ण,
	पूर्ण;

	स्थिर काष्ठा vsp1_क्रमmat_info *info;
	अचिन्हित पूर्णांक width = pix->width;
	अचिन्हित पूर्णांक height = pix->height;
	अचिन्हित पूर्णांक i;

	/*
	 * Backward compatibility: replace deprecated RGB क्रमmats by their XRGB
	 * equivalent. This selects the क्रमmat older userspace applications want
	 * जबतक still exposing the new क्रमmat.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(xrgb_क्रमmats); ++i) अणु
		अगर (xrgb_क्रमmats[i][0] == pix->pixelक्रमmat) अणु
			pix->pixelक्रमmat = xrgb_क्रमmats[i][1];
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Retrieve क्रमmat inक्रमmation and select the शेष क्रमmat अगर the
	 * requested क्रमmat isn't supported.
	 */
	info = vsp1_get_क्रमmat_info(video->vsp1, pix->pixelक्रमmat);
	अगर (info == शून्य)
		info = vsp1_get_क्रमmat_info(video->vsp1, VSP1_VIDEO_DEF_FORMAT);

	pix->pixelक्रमmat = info->fourcc;
	pix->colorspace = V4L2_COLORSPACE_SRGB;
	pix->field = V4L2_FIELD_NONE;

	अगर (info->fourcc == V4L2_PIX_FMT_HSV24 ||
	    info->fourcc == V4L2_PIX_FMT_HSV32)
		pix->hsv_enc = V4L2_HSV_ENC_256;

	स_रखो(pix->reserved, 0, माप(pix->reserved));

	/* Align the width and height क्रम YUV 4:2:2 and 4:2:0 क्रमmats. */
	width = round_करोwn(width, info->hsub);
	height = round_करोwn(height, info->vsub);

	/* Clamp the width and height. */
	pix->width = clamp(width, info->hsub, VSP1_VIDEO_MAX_WIDTH);
	pix->height = clamp(height, info->vsub, VSP1_VIDEO_MAX_HEIGHT);

	/*
	 * Compute and clamp the stride and image size. While not करोcumented in
	 * the datasheet, strides not aligned to a multiple of 128 bytes result
	 * in image corruption.
	 */
	क्रम (i = 0; i < min(info->planes, 2U); ++i) अणु
		अचिन्हित पूर्णांक hsub = i > 0 ? info->hsub : 1;
		अचिन्हित पूर्णांक vsub = i > 0 ? info->vsub : 1;
		अचिन्हित पूर्णांक align = 128;
		अचिन्हित पूर्णांक bpl;

		bpl = clamp_t(अचिन्हित पूर्णांक, pix->plane_fmt[i].bytesperline,
			      pix->width / hsub * info->bpp[i] / 8,
			      round_करोwn(65535U, align));

		pix->plane_fmt[i].bytesperline = round_up(bpl, align);
		pix->plane_fmt[i].sizeimage = pix->plane_fmt[i].bytesperline
					    * pix->height / vsub;
	पूर्ण

	अगर (info->planes == 3) अणु
		/* The second and third planes must have the same stride. */
		pix->plane_fmt[2].bytesperline = pix->plane_fmt[1].bytesperline;
		pix->plane_fmt[2].sizeimage = pix->plane_fmt[1].sizeimage;
	पूर्ण

	pix->num_planes = info->planes;

	अगर (fmtinfo)
		*fmtinfo = info;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * VSP1 Partition Algorithm support
 */

/**
 * vsp1_video_calculate_partition - Calculate the active partition output winकरोw
 *
 * @pipe: the pipeline
 * @partition: partition that will hold the calculated values
 * @भाग_size: pre-determined maximum partition भागision size
 * @index: partition index
 */
अटल व्योम vsp1_video_calculate_partition(काष्ठा vsp1_pipeline *pipe,
					   काष्ठा vsp1_partition *partition,
					   अचिन्हित पूर्णांक भाग_size,
					   अचिन्हित पूर्णांक index)
अणु
	स्थिर काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा vsp1_partition_winकरोw winकरोw;
	अचिन्हित पूर्णांक modulus;

	/*
	 * Partitions are computed on the size beक्रमe rotation, use the क्रमmat
	 * at the WPF sink.
	 */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&pipe->output->entity,
					    pipe->output->entity.config,
					    RWPF_PAD_SINK);

	/* A single partition simply processes the output size in full. */
	अगर (pipe->partitions <= 1) अणु
		winकरोw.left = 0;
		winकरोw.width = क्रमmat->width;

		vsp1_pipeline_propagate_partition(pipe, partition, index,
						  &winकरोw);
		वापस;
	पूर्ण

	/* Initialise the partition with sane starting conditions. */
	winकरोw.left = index * भाग_size;
	winकरोw.width = भाग_size;

	modulus = क्रमmat->width % भाग_size;

	/*
	 * We need to prevent the last partition from being smaller than the
	 * *minimum* width of the hardware capabilities.
	 *
	 * If the modulus is less than half of the partition size,
	 * the penultimate partition is reduced to half, which is added
	 * to the final partition: |1234|1234|1234|12|341|
	 * to prevent this:        |1234|1234|1234|1234|1|.
	 */
	अगर (modulus) अणु
		/*
		 * pipe->partitions is 1 based, whilst index is a 0 based index.
		 * Normalise this locally.
		 */
		अचिन्हित पूर्णांक partitions = pipe->partitions - 1;

		अगर (modulus < भाग_size / 2) अणु
			अगर (index == partitions - 1) अणु
				/* Halve the penultimate partition. */
				winकरोw.width = भाग_size / 2;
			पूर्ण अन्यथा अगर (index == partitions) अणु
				/* Increase the final partition. */
				winकरोw.width = (भाग_size / 2) + modulus;
				winकरोw.left -= भाग_size / 2;
			पूर्ण
		पूर्ण अन्यथा अगर (index == partitions) अणु
			winकरोw.width = modulus;
		पूर्ण
	पूर्ण

	vsp1_pipeline_propagate_partition(pipe, partition, index, &winकरोw);
पूर्ण

अटल पूर्णांक vsp1_video_pipeline_setup_partitions(काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_device *vsp1 = pipe->output->entity.vsp1;
	स्थिर काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा vsp1_entity *entity;
	अचिन्हित पूर्णांक भाग_size;
	अचिन्हित पूर्णांक i;

	/*
	 * Partitions are computed on the size beक्रमe rotation, use the क्रमmat
	 * at the WPF sink.
	 */
	क्रमmat = vsp1_entity_get_pad_क्रमmat(&pipe->output->entity,
					    pipe->output->entity.config,
					    RWPF_PAD_SINK);
	भाग_size = क्रमmat->width;

	/*
	 * Only Gen3 hardware requires image partitioning, Gen2 will operate
	 * with a single partition that covers the whole output.
	 */
	अगर (vsp1->info->gen == 3) अणु
		list_क्रम_each_entry(entity, &pipe->entities, list_pipe) अणु
			अचिन्हित पूर्णांक entity_max;

			अगर (!entity->ops->max_width)
				जारी;

			entity_max = entity->ops->max_width(entity, pipe);
			अगर (entity_max)
				भाग_size = min(भाग_size, entity_max);
		पूर्ण
	पूर्ण

	pipe->partitions = DIV_ROUND_UP(क्रमmat->width, भाग_size);
	pipe->part_table = kसुस्मृति(pipe->partitions, माप(*pipe->part_table),
				   GFP_KERNEL);
	अगर (!pipe->part_table)
		वापस -ENOMEM;

	क्रम (i = 0; i < pipe->partitions; ++i)
		vsp1_video_calculate_partition(pipe, &pipe->part_table[i],
					       भाग_size, i);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Pipeline Management
 */

/*
 * vsp1_video_complete_buffer - Complete the current buffer
 * @video: the video node
 *
 * This function completes the current buffer by filling its sequence number,
 * समय stamp and payload size, and hands it back to the videobuf core.
 *
 * Return the next queued buffer or शून्य अगर the queue is empty.
 */
अटल काष्ठा vsp1_vb2_buffer *
vsp1_video_complete_buffer(काष्ठा vsp1_video *video)
अणु
	काष्ठा vsp1_pipeline *pipe = video->rwpf->entity.pipe;
	काष्ठा vsp1_vb2_buffer *next = शून्य;
	काष्ठा vsp1_vb2_buffer *करोne;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&video->irqlock, flags);

	अगर (list_empty(&video->irqqueue)) अणु
		spin_unlock_irqrestore(&video->irqlock, flags);
		वापस शून्य;
	पूर्ण

	करोne = list_first_entry(&video->irqqueue,
				काष्ठा vsp1_vb2_buffer, queue);

	list_del(&करोne->queue);

	अगर (!list_empty(&video->irqqueue))
		next = list_first_entry(&video->irqqueue,
					काष्ठा vsp1_vb2_buffer, queue);

	spin_unlock_irqrestore(&video->irqlock, flags);

	करोne->buf.sequence = pipe->sequence;
	करोne->buf.vb2_buf.बारtamp = kसमय_get_ns();
	क्रम (i = 0; i < करोne->buf.vb2_buf.num_planes; ++i)
		vb2_set_plane_payload(&करोne->buf.vb2_buf, i,
				      vb2_plane_size(&करोne->buf.vb2_buf, i));
	vb2_buffer_करोne(&करोne->buf.vb2_buf, VB2_BUF_STATE_DONE);

	वापस next;
पूर्ण

अटल व्योम vsp1_video_frame_end(काष्ठा vsp1_pipeline *pipe,
				 काष्ठा vsp1_rwpf *rwpf)
अणु
	काष्ठा vsp1_video *video = rwpf->video;
	काष्ठा vsp1_vb2_buffer *buf;

	buf = vsp1_video_complete_buffer(video);
	अगर (buf == शून्य)
		वापस;

	video->rwpf->mem = buf->mem;
	pipe->buffers_पढ़ोy |= 1 << video->pipe_index;
पूर्ण

अटल व्योम vsp1_video_pipeline_run_partition(काष्ठा vsp1_pipeline *pipe,
					      काष्ठा vsp1_dl_list *dl,
					      अचिन्हित पूर्णांक partition)
अणु
	काष्ठा vsp1_dl_body *dlb = vsp1_dl_list_get_body0(dl);
	काष्ठा vsp1_entity *entity;

	pipe->partition = &pipe->part_table[partition];

	list_क्रम_each_entry(entity, &pipe->entities, list_pipe)
		vsp1_entity_configure_partition(entity, pipe, dl, dlb);
पूर्ण

अटल व्योम vsp1_video_pipeline_run(काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_device *vsp1 = pipe->output->entity.vsp1;
	काष्ठा vsp1_entity *entity;
	काष्ठा vsp1_dl_body *dlb;
	काष्ठा vsp1_dl_list *dl;
	अचिन्हित पूर्णांक partition;

	dl = vsp1_dl_list_get(pipe->output->dlm);

	/*
	 * If the VSP hardware isn't configured yet (which occurs either when
	 * processing the first frame or after a प्रणाली suspend/resume), add the
	 * cached stream configuration to the display list to perक्रमm a full
	 * initialisation.
	 */
	अगर (!pipe->configured)
		vsp1_dl_list_add_body(dl, pipe->stream_config);

	dlb = vsp1_dl_list_get_body0(dl);

	list_क्रम_each_entry(entity, &pipe->entities, list_pipe)
		vsp1_entity_configure_frame(entity, pipe, dl, dlb);

	/* Run the first partition. */
	vsp1_video_pipeline_run_partition(pipe, dl, 0);

	/* Process consecutive partitions as necessary. */
	क्रम (partition = 1; partition < pipe->partitions; ++partition) अणु
		काष्ठा vsp1_dl_list *dl_next;

		dl_next = vsp1_dl_list_get(pipe->output->dlm);

		/*
		 * An incomplete chain will still function, but output only
		 * the partitions that had a dl available. The frame end
		 * पूर्णांकerrupt will be marked on the last dl in the chain.
		 */
		अगर (!dl_next) अणु
			dev_err(vsp1->dev, "Failed to obtain a dl list. Frame will be incomplete\n");
			अवरोध;
		पूर्ण

		vsp1_video_pipeline_run_partition(pipe, dl_next, partition);
		vsp1_dl_list_add_chain(dl, dl_next);
	पूर्ण

	/* Complete, and commit the head display list. */
	vsp1_dl_list_commit(dl, 0);
	pipe->configured = true;

	vsp1_pipeline_run(pipe);
पूर्ण

अटल व्योम vsp1_video_pipeline_frame_end(काष्ठा vsp1_pipeline *pipe,
					  अचिन्हित पूर्णांक completion)
अणु
	काष्ठा vsp1_device *vsp1 = pipe->output->entity.vsp1;
	क्रमागत vsp1_pipeline_state state;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	/* M2M Pipelines should never call here with an incomplete frame. */
	WARN_ON_ONCE(!(completion & VSP1_DL_FRAME_END_COMPLETED));

	spin_lock_irqsave(&pipe->irqlock, flags);

	/* Complete buffers on all video nodes. */
	क्रम (i = 0; i < vsp1->info->rpf_count; ++i) अणु
		अगर (!pipe->inमाला_दो[i])
			जारी;

		vsp1_video_frame_end(pipe, pipe->inमाला_दो[i]);
	पूर्ण

	vsp1_video_frame_end(pipe, pipe->output);

	state = pipe->state;
	pipe->state = VSP1_PIPELINE_STOPPED;

	/*
	 * If a stop has been requested, mark the pipeline as stopped and
	 * वापस. Otherwise restart the pipeline अगर पढ़ोy.
	 */
	अगर (state == VSP1_PIPELINE_STOPPING)
		wake_up(&pipe->wq);
	अन्यथा अगर (vsp1_pipeline_पढ़ोy(pipe))
		vsp1_video_pipeline_run(pipe);

	spin_unlock_irqrestore(&pipe->irqlock, flags);
पूर्ण

अटल पूर्णांक vsp1_video_pipeline_build_branch(काष्ठा vsp1_pipeline *pipe,
					    काष्ठा vsp1_rwpf *input,
					    काष्ठा vsp1_rwpf *output)
अणु
	काष्ठा media_entity_क्रमागत ent_क्रमागत;
	काष्ठा vsp1_entity *entity;
	काष्ठा media_pad *pad;
	काष्ठा vsp1_brx *brx = शून्य;
	पूर्णांक ret;

	ret = media_entity_क्रमागत_init(&ent_क्रमागत, &input->entity.vsp1->media_dev);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The मुख्य data path करोesn't include the HGO or HGT, use
	 * vsp1_entity_remote_pad() to traverse the graph.
	 */

	pad = vsp1_entity_remote_pad(&input->entity.pads[RWPF_PAD_SOURCE]);

	जबतक (1) अणु
		अगर (pad == शून्य) अणु
			ret = -EPIPE;
			जाओ out;
		पूर्ण

		/* We've reached a video node, that shouldn't have happened. */
		अगर (!is_media_entity_v4l2_subdev(pad->entity)) अणु
			ret = -EPIPE;
			जाओ out;
		पूर्ण

		entity = to_vsp1_entity(
			media_entity_to_v4l2_subdev(pad->entity));

		/*
		 * A BRU or BRS is present in the pipeline, store its input pad
		 * number in the input RPF क्रम use when configuring the RPF.
		 */
		अगर (entity->type == VSP1_ENTITY_BRU ||
		    entity->type == VSP1_ENTITY_BRS) अणु
			/* BRU and BRS can't be chained. */
			अगर (brx) अणु
				ret = -EPIPE;
				जाओ out;
			पूर्ण

			brx = to_brx(&entity->subdev);
			brx->inमाला_दो[pad->index].rpf = input;
			input->brx_input = pad->index;
		पूर्ण

		/* We've reached the WPF, we're करोne. */
		अगर (entity->type == VSP1_ENTITY_WPF)
			अवरोध;

		/* Ensure the branch has no loop. */
		अगर (media_entity_क्रमागत_test_and_set(&ent_क्रमागत,
						   &entity->subdev.entity)) अणु
			ret = -EPIPE;
			जाओ out;
		पूर्ण

		/* UDS can't be chained. */
		अगर (entity->type == VSP1_ENTITY_UDS) अणु
			अगर (pipe->uds) अणु
				ret = -EPIPE;
				जाओ out;
			पूर्ण

			pipe->uds = entity;
			pipe->uds_input = brx ? &brx->entity : &input->entity;
		पूर्ण

		/* Follow the source link, ignoring any HGO or HGT. */
		pad = &entity->pads[entity->source_pad];
		pad = vsp1_entity_remote_pad(pad);
	पूर्ण

	/* The last entity must be the output WPF. */
	अगर (entity != &output->entity)
		ret = -EPIPE;

out:
	media_entity_क्रमागत_cleanup(&ent_क्रमागत);

	वापस ret;
पूर्ण

अटल पूर्णांक vsp1_video_pipeline_build(काष्ठा vsp1_pipeline *pipe,
				     काष्ठा vsp1_video *video)
अणु
	काष्ठा media_graph graph;
	काष्ठा media_entity *entity = &video->video.entity;
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Walk the graph to locate the entities and video nodes. */
	ret = media_graph_walk_init(&graph, mdev);
	अगर (ret)
		वापस ret;

	media_graph_walk_start(&graph, entity);

	जबतक ((entity = media_graph_walk_next(&graph))) अणु
		काष्ठा v4l2_subdev *subdev;
		काष्ठा vsp1_rwpf *rwpf;
		काष्ठा vsp1_entity *e;

		अगर (!is_media_entity_v4l2_subdev(entity))
			जारी;

		subdev = media_entity_to_v4l2_subdev(entity);
		e = to_vsp1_entity(subdev);
		list_add_tail(&e->list_pipe, &pipe->entities);
		e->pipe = pipe;

		चयन (e->type) अणु
		हाल VSP1_ENTITY_RPF:
			rwpf = to_rwpf(subdev);
			pipe->inमाला_दो[rwpf->entity.index] = rwpf;
			rwpf->video->pipe_index = ++pipe->num_inमाला_दो;
			अवरोध;

		हाल VSP1_ENTITY_WPF:
			rwpf = to_rwpf(subdev);
			pipe->output = rwpf;
			rwpf->video->pipe_index = 0;
			अवरोध;

		हाल VSP1_ENTITY_LIF:
			pipe->lअगर = e;
			अवरोध;

		हाल VSP1_ENTITY_BRU:
		हाल VSP1_ENTITY_BRS:
			pipe->brx = e;
			अवरोध;

		हाल VSP1_ENTITY_HGO:
			pipe->hgo = e;
			अवरोध;

		हाल VSP1_ENTITY_HGT:
			pipe->hgt = e;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	media_graph_walk_cleanup(&graph);

	/* We need one output and at least one input. */
	अगर (pipe->num_inमाला_दो == 0 || !pipe->output)
		वापस -EPIPE;

	/*
	 * Follow links करोwnstream क्रम each input and make sure the graph
	 * contains no loop and that all branches end at the output WPF.
	 */
	क्रम (i = 0; i < video->vsp1->info->rpf_count; ++i) अणु
		अगर (!pipe->inमाला_दो[i])
			जारी;

		ret = vsp1_video_pipeline_build_branch(pipe, pipe->inमाला_दो[i],
						       pipe->output);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsp1_video_pipeline_init(काष्ठा vsp1_pipeline *pipe,
				    काष्ठा vsp1_video *video)
अणु
	vsp1_pipeline_init(pipe);

	pipe->frame_end = vsp1_video_pipeline_frame_end;

	वापस vsp1_video_pipeline_build(pipe, video);
पूर्ण

अटल काष्ठा vsp1_pipeline *vsp1_video_pipeline_get(काष्ठा vsp1_video *video)
अणु
	काष्ठा vsp1_pipeline *pipe;
	पूर्णांक ret;

	/*
	 * Get a pipeline object क्रम the video node. If a pipeline has alपढ़ोy
	 * been allocated just increment its reference count and वापस it.
	 * Otherwise allocate a new pipeline and initialize it, it will be मुक्तd
	 * when the last reference is released.
	 */
	अगर (!video->rwpf->entity.pipe) अणु
		pipe = kzalloc(माप(*pipe), GFP_KERNEL);
		अगर (!pipe)
			वापस ERR_PTR(-ENOMEM);

		ret = vsp1_video_pipeline_init(pipe, video);
		अगर (ret < 0) अणु
			vsp1_pipeline_reset(pipe);
			kमुक्त(pipe);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण अन्यथा अणु
		pipe = video->rwpf->entity.pipe;
		kref_get(&pipe->kref);
	पूर्ण

	वापस pipe;
पूर्ण

अटल व्योम vsp1_video_pipeline_release(काष्ठा kref *kref)
अणु
	काष्ठा vsp1_pipeline *pipe = container_of(kref, typeof(*pipe), kref);

	vsp1_pipeline_reset(pipe);
	kमुक्त(pipe);
पूर्ण

अटल व्योम vsp1_video_pipeline_put(काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा media_device *mdev = &pipe->output->entity.vsp1->media_dev;

	mutex_lock(&mdev->graph_mutex);
	kref_put(&pipe->kref, vsp1_video_pipeline_release);
	mutex_unlock(&mdev->graph_mutex);
पूर्ण

/* -----------------------------------------------------------------------------
 * videobuf2 Queue Operations
 */

अटल पूर्णांक
vsp1_video_queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा vsp1_video *video = vb2_get_drv_priv(vq);
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *क्रमmat = &video->rwpf->क्रमmat;
	अचिन्हित पूर्णांक i;

	अगर (*nplanes) अणु
		अगर (*nplanes != क्रमmat->num_planes)
			वापस -EINVAL;

		क्रम (i = 0; i < *nplanes; i++)
			अगर (sizes[i] < क्रमmat->plane_fmt[i].sizeimage)
				वापस -EINVAL;
		वापस 0;
	पूर्ण

	*nplanes = क्रमmat->num_planes;

	क्रम (i = 0; i < क्रमmat->num_planes; ++i)
		sizes[i] = क्रमmat->plane_fmt[i].sizeimage;

	वापस 0;
पूर्ण

अटल पूर्णांक vsp1_video_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vsp1_video *video = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vsp1_vb2_buffer *buf = to_vsp1_vb2_buffer(vbuf);
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *क्रमmat = &video->rwpf->क्रमmat;
	अचिन्हित पूर्णांक i;

	अगर (vb->num_planes < क्रमmat->num_planes)
		वापस -EINVAL;

	क्रम (i = 0; i < vb->num_planes; ++i) अणु
		buf->mem.addr[i] = vb2_dma_contig_plane_dma_addr(vb, i);

		अगर (vb2_plane_size(vb, i) < क्रमmat->plane_fmt[i].sizeimage)
			वापस -EINVAL;
	पूर्ण

	क्रम ( ; i < 3; ++i)
		buf->mem.addr[i] = 0;

	वापस 0;
पूर्ण

अटल व्योम vsp1_video_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vsp1_video *video = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vsp1_pipeline *pipe = video->rwpf->entity.pipe;
	काष्ठा vsp1_vb2_buffer *buf = to_vsp1_vb2_buffer(vbuf);
	अचिन्हित दीर्घ flags;
	bool empty;

	spin_lock_irqsave(&video->irqlock, flags);
	empty = list_empty(&video->irqqueue);
	list_add_tail(&buf->queue, &video->irqqueue);
	spin_unlock_irqrestore(&video->irqlock, flags);

	अगर (!empty)
		वापस;

	spin_lock_irqsave(&pipe->irqlock, flags);

	video->rwpf->mem = buf->mem;
	pipe->buffers_पढ़ोy |= 1 << video->pipe_index;

	अगर (vb2_is_streaming(&video->queue) &&
	    vsp1_pipeline_पढ़ोy(pipe))
		vsp1_video_pipeline_run(pipe);

	spin_unlock_irqrestore(&pipe->irqlock, flags);
पूर्ण

अटल पूर्णांक vsp1_video_setup_pipeline(काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_entity *entity;
	पूर्णांक ret;

	/* Determine this pipelines sizes क्रम image partitioning support. */
	ret = vsp1_video_pipeline_setup_partitions(pipe);
	अगर (ret < 0)
		वापस ret;

	अगर (pipe->uds) अणु
		काष्ठा vsp1_uds *uds = to_uds(&pipe->uds->subdev);

		/*
		 * If a BRU or BRS is present in the pipeline beक्रमe the UDS,
		 * the alpha component करोesn't need to be scaled as the BRU and
		 * BRS output alpha value is fixed to 255. Otherwise we need to
		 * scale the alpha component only when available at the input
		 * RPF.
		 */
		अगर (pipe->uds_input->type == VSP1_ENTITY_BRU ||
		    pipe->uds_input->type == VSP1_ENTITY_BRS) अणु
			uds->scale_alpha = false;
		पूर्ण अन्यथा अणु
			काष्ठा vsp1_rwpf *rpf =
				to_rwpf(&pipe->uds_input->subdev);

			uds->scale_alpha = rpf->fmtinfo->alpha;
		पूर्ण
	पूर्ण

	/*
	 * Compute and cache the stream configuration पूर्णांकo a body. The cached
	 * body will be added to the display list by vsp1_video_pipeline_run()
	 * whenever the pipeline needs to be fully reconfigured.
	 */
	pipe->stream_config = vsp1_dlm_dl_body_get(pipe->output->dlm);
	अगर (!pipe->stream_config)
		वापस -ENOMEM;

	list_क्रम_each_entry(entity, &pipe->entities, list_pipe) अणु
		vsp1_entity_route_setup(entity, pipe, pipe->stream_config);
		vsp1_entity_configure_stream(entity, pipe, शून्य,
					     pipe->stream_config);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vsp1_video_release_buffers(काष्ठा vsp1_video *video)
अणु
	काष्ठा vsp1_vb2_buffer *buffer;
	अचिन्हित दीर्घ flags;

	/* Remove all buffers from the IRQ queue. */
	spin_lock_irqsave(&video->irqlock, flags);
	list_क्रम_each_entry(buffer, &video->irqqueue, queue)
		vb2_buffer_करोne(&buffer->buf.vb2_buf, VB2_BUF_STATE_ERROR);
	INIT_LIST_HEAD(&video->irqqueue);
	spin_unlock_irqrestore(&video->irqlock, flags);
पूर्ण

अटल व्योम vsp1_video_cleanup_pipeline(काष्ठा vsp1_pipeline *pipe)
अणु
	lockdep_निश्चित_held(&pipe->lock);

	/* Release any cached configuration from our output video. */
	vsp1_dl_body_put(pipe->stream_config);
	pipe->stream_config = शून्य;
	pipe->configured = false;

	/* Release our partition table allocation. */
	kमुक्त(pipe->part_table);
	pipe->part_table = शून्य;
पूर्ण

अटल पूर्णांक vsp1_video_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vsp1_video *video = vb2_get_drv_priv(vq);
	काष्ठा vsp1_pipeline *pipe = video->rwpf->entity.pipe;
	bool start_pipeline = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	mutex_lock(&pipe->lock);
	अगर (pipe->stream_count == pipe->num_inमाला_दो) अणु
		ret = vsp1_video_setup_pipeline(pipe);
		अगर (ret < 0) अणु
			vsp1_video_release_buffers(video);
			vsp1_video_cleanup_pipeline(pipe);
			mutex_unlock(&pipe->lock);
			वापस ret;
		पूर्ण

		start_pipeline = true;
	पूर्ण

	pipe->stream_count++;
	mutex_unlock(&pipe->lock);

	/*
	 * vsp1_pipeline_पढ़ोy() is not sufficient to establish that all streams
	 * are prepared and the pipeline is configured, as multiple streams
	 * can race through streamon with buffers alपढ़ोy queued; Thereक्रमe we
	 * करोn't even attempt to start the pipeline until the last stream has
	 * called through here.
	 */
	अगर (!start_pipeline)
		वापस 0;

	spin_lock_irqsave(&pipe->irqlock, flags);
	अगर (vsp1_pipeline_पढ़ोy(pipe))
		vsp1_video_pipeline_run(pipe);
	spin_unlock_irqrestore(&pipe->irqlock, flags);

	वापस 0;
पूर्ण

अटल व्योम vsp1_video_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vsp1_video *video = vb2_get_drv_priv(vq);
	काष्ठा vsp1_pipeline *pipe = video->rwpf->entity.pipe;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * Clear the buffers पढ़ोy flag to make sure the device won't be started
	 * by a QBUF on the video node on the other side of the pipeline.
	 */
	spin_lock_irqsave(&video->irqlock, flags);
	pipe->buffers_पढ़ोy &= ~(1 << video->pipe_index);
	spin_unlock_irqrestore(&video->irqlock, flags);

	mutex_lock(&pipe->lock);
	अगर (--pipe->stream_count == pipe->num_inमाला_दो) अणु
		/* Stop the pipeline. */
		ret = vsp1_pipeline_stop(pipe);
		अगर (ret == -ETIMEDOUT)
			dev_err(video->vsp1->dev, "pipeline stop timeout\n");

		vsp1_video_cleanup_pipeline(pipe);
	पूर्ण
	mutex_unlock(&pipe->lock);

	media_pipeline_stop(&video->video.entity);
	vsp1_video_release_buffers(video);
	vsp1_video_pipeline_put(pipe);
पूर्ण

अटल स्थिर काष्ठा vb2_ops vsp1_video_queue_qops = अणु
	.queue_setup = vsp1_video_queue_setup,
	.buf_prepare = vsp1_video_buffer_prepare,
	.buf_queue = vsp1_video_buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = vsp1_video_start_streaming,
	.stop_streaming = vsp1_video_stop_streaming,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 ioctls
 */

अटल पूर्णांक
vsp1_video_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा vsp1_video *video = to_vsp1_video(vfh->vdev);

	cap->capabilities = V4L2_CAP_DEVICE_CAPS | V4L2_CAP_STREAMING
			  | V4L2_CAP_VIDEO_CAPTURE_MPLANE
			  | V4L2_CAP_VIDEO_OUTPUT_MPLANE;


	strscpy(cap->driver, "vsp1", माप(cap->driver));
	strscpy(cap->card, video->video.name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(video->vsp1->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक
vsp1_video_get_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा vsp1_video *video = to_vsp1_video(vfh->vdev);

	अगर (क्रमmat->type != video->queue.type)
		वापस -EINVAL;

	mutex_lock(&video->lock);
	क्रमmat->fmt.pix_mp = video->rwpf->क्रमmat;
	mutex_unlock(&video->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
vsp1_video_try_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा vsp1_video *video = to_vsp1_video(vfh->vdev);

	अगर (क्रमmat->type != video->queue.type)
		वापस -EINVAL;

	वापस __vsp1_video_try_क्रमmat(video, &क्रमmat->fmt.pix_mp, शून्य);
पूर्ण

अटल पूर्णांक
vsp1_video_set_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा vsp1_video *video = to_vsp1_video(vfh->vdev);
	स्थिर काष्ठा vsp1_क्रमmat_info *info;
	पूर्णांक ret;

	अगर (क्रमmat->type != video->queue.type)
		वापस -EINVAL;

	ret = __vsp1_video_try_क्रमmat(video, &क्रमmat->fmt.pix_mp, &info);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&video->lock);

	अगर (vb2_is_busy(&video->queue)) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	video->rwpf->क्रमmat = क्रमmat->fmt.pix_mp;
	video->rwpf->fmtinfo = info;

करोne:
	mutex_unlock(&video->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक
vsp1_video_streamon(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा vsp1_video *video = to_vsp1_video(vfh->vdev);
	काष्ठा media_device *mdev = &video->vsp1->media_dev;
	काष्ठा vsp1_pipeline *pipe;
	पूर्णांक ret;

	अगर (video->queue.owner && video->queue.owner != file->निजी_data)
		वापस -EBUSY;

	/*
	 * Get a pipeline क्रम the video node and start streaming on it. No link
	 * touching an entity in the pipeline can be activated or deactivated
	 * once streaming is started.
	 */
	mutex_lock(&mdev->graph_mutex);

	pipe = vsp1_video_pipeline_get(video);
	अगर (IS_ERR(pipe)) अणु
		mutex_unlock(&mdev->graph_mutex);
		वापस PTR_ERR(pipe);
	पूर्ण

	ret = __media_pipeline_start(&video->video.entity, &pipe->pipe);
	अगर (ret < 0) अणु
		mutex_unlock(&mdev->graph_mutex);
		जाओ err_pipe;
	पूर्ण

	mutex_unlock(&mdev->graph_mutex);

	/*
	 * Verअगरy that the configured क्रमmat matches the output of the connected
	 * subdev.
	 */
	ret = vsp1_video_verअगरy_क्रमmat(video);
	अगर (ret < 0)
		जाओ err_stop;

	/* Start the queue. */
	ret = vb2_streamon(&video->queue, type);
	अगर (ret < 0)
		जाओ err_stop;

	वापस 0;

err_stop:
	media_pipeline_stop(&video->video.entity);
err_pipe:
	vsp1_video_pipeline_put(pipe);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops vsp1_video_ioctl_ops = अणु
	.vidioc_querycap		= vsp1_video_querycap,
	.vidioc_g_fmt_vid_cap_mplane	= vsp1_video_get_क्रमmat,
	.vidioc_s_fmt_vid_cap_mplane	= vsp1_video_set_क्रमmat,
	.vidioc_try_fmt_vid_cap_mplane	= vsp1_video_try_क्रमmat,
	.vidioc_g_fmt_vid_out_mplane	= vsp1_video_get_क्रमmat,
	.vidioc_s_fmt_vid_out_mplane	= vsp1_video_set_क्रमmat,
	.vidioc_try_fmt_vid_out_mplane	= vsp1_video_try_क्रमmat,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vsp1_video_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 File Operations
 */

अटल पूर्णांक vsp1_video_खोलो(काष्ठा file *file)
अणु
	काष्ठा vsp1_video *video = video_drvdata(file);
	काष्ठा v4l2_fh *vfh;
	पूर्णांक ret = 0;

	vfh = kzalloc(माप(*vfh), GFP_KERNEL);
	अगर (vfh == शून्य)
		वापस -ENOMEM;

	v4l2_fh_init(vfh, &video->video);
	v4l2_fh_add(vfh);

	file->निजी_data = vfh;

	ret = vsp1_device_get(video->vsp1);
	अगर (ret < 0) अणु
		v4l2_fh_del(vfh);
		v4l2_fh_निकास(vfh);
		kमुक्त(vfh);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vsp1_video_release(काष्ठा file *file)
अणु
	काष्ठा vsp1_video *video = video_drvdata(file);
	काष्ठा v4l2_fh *vfh = file->निजी_data;

	mutex_lock(&video->lock);
	अगर (video->queue.owner == vfh) अणु
		vb2_queue_release(&video->queue);
		video->queue.owner = शून्य;
	पूर्ण
	mutex_unlock(&video->lock);

	vsp1_device_put(video->vsp1);

	v4l2_fh_release(file);

	file->निजी_data = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations vsp1_video_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.खोलो = vsp1_video_खोलो,
	.release = vsp1_video_release,
	.poll = vb2_fop_poll,
	.mmap = vb2_fop_mmap,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Suspend and Resume
 */

व्योम vsp1_video_suspend(काष्ठा vsp1_device *vsp1)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/*
	 * To aव्योम increasing the प्रणाली suspend समय needlessly, loop over the
	 * pipelines twice, first to set them all to the stopping state, and
	 * then to रुको क्रम the stop to complete.
	 */
	क्रम (i = 0; i < vsp1->info->wpf_count; ++i) अणु
		काष्ठा vsp1_rwpf *wpf = vsp1->wpf[i];
		काष्ठा vsp1_pipeline *pipe;

		अगर (wpf == शून्य)
			जारी;

		pipe = wpf->entity.pipe;
		अगर (pipe == शून्य)
			जारी;

		spin_lock_irqsave(&pipe->irqlock, flags);
		अगर (pipe->state == VSP1_PIPELINE_RUNNING)
			pipe->state = VSP1_PIPELINE_STOPPING;
		spin_unlock_irqrestore(&pipe->irqlock, flags);
	पूर्ण

	क्रम (i = 0; i < vsp1->info->wpf_count; ++i) अणु
		काष्ठा vsp1_rwpf *wpf = vsp1->wpf[i];
		काष्ठा vsp1_pipeline *pipe;

		अगर (wpf == शून्य)
			जारी;

		pipe = wpf->entity.pipe;
		अगर (pipe == शून्य)
			जारी;

		ret = रुको_event_समयout(pipe->wq, vsp1_pipeline_stopped(pipe),
					 msecs_to_jअगरfies(500));
		अगर (ret == 0)
			dev_warn(vsp1->dev, "pipeline %u stop timeout\n",
				 wpf->entity.index);
	पूर्ण
पूर्ण

व्योम vsp1_video_resume(काष्ठा vsp1_device *vsp1)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	/* Resume all running pipelines. */
	क्रम (i = 0; i < vsp1->info->wpf_count; ++i) अणु
		काष्ठा vsp1_rwpf *wpf = vsp1->wpf[i];
		काष्ठा vsp1_pipeline *pipe;

		अगर (wpf == शून्य)
			जारी;

		pipe = wpf->entity.pipe;
		अगर (pipe == शून्य)
			जारी;

		/*
		 * The hardware may have been reset during a suspend and will
		 * need a full reconfiguration.
		 */
		pipe->configured = false;

		spin_lock_irqsave(&pipe->irqlock, flags);
		अगर (vsp1_pipeline_पढ़ोy(pipe))
			vsp1_video_pipeline_run(pipe);
		spin_unlock_irqrestore(&pipe->irqlock, flags);
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

काष्ठा vsp1_video *vsp1_video_create(काष्ठा vsp1_device *vsp1,
				     काष्ठा vsp1_rwpf *rwpf)
अणु
	काष्ठा vsp1_video *video;
	स्थिर अक्षर *direction;
	पूर्णांक ret;

	video = devm_kzalloc(vsp1->dev, माप(*video), GFP_KERNEL);
	अगर (!video)
		वापस ERR_PTR(-ENOMEM);

	rwpf->video = video;

	video->vsp1 = vsp1;
	video->rwpf = rwpf;

	अगर (rwpf->entity.type == VSP1_ENTITY_RPF) अणु
		direction = "input";
		video->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
		video->pad.flags = MEDIA_PAD_FL_SOURCE;
		video->video.vfl_dir = VFL_सूची_TX;
		video->video.device_caps = V4L2_CAP_VIDEO_OUTPUT_MPLANE |
					   V4L2_CAP_STREAMING;
	पूर्ण अन्यथा अणु
		direction = "output";
		video->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		video->pad.flags = MEDIA_PAD_FL_SINK;
		video->video.vfl_dir = VFL_सूची_RX;
		video->video.device_caps = V4L2_CAP_VIDEO_CAPTURE_MPLANE |
					   V4L2_CAP_STREAMING;
	पूर्ण

	mutex_init(&video->lock);
	spin_lock_init(&video->irqlock);
	INIT_LIST_HEAD(&video->irqqueue);

	/* Initialize the media entity... */
	ret = media_entity_pads_init(&video->video.entity, 1, &video->pad);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	/* ... and the क्रमmat ... */
	rwpf->क्रमmat.pixelक्रमmat = VSP1_VIDEO_DEF_FORMAT;
	rwpf->क्रमmat.width = VSP1_VIDEO_DEF_WIDTH;
	rwpf->क्रमmat.height = VSP1_VIDEO_DEF_HEIGHT;
	__vsp1_video_try_क्रमmat(video, &rwpf->क्रमmat, &rwpf->fmtinfo);

	/* ... and the video node... */
	video->video.v4l2_dev = &video->vsp1->v4l2_dev;
	video->video.fops = &vsp1_video_fops;
	snम_लिखो(video->video.name, माप(video->video.name), "%s %s",
		 rwpf->entity.subdev.name, direction);
	video->video.vfl_type = VFL_TYPE_VIDEO;
	video->video.release = video_device_release_empty;
	video->video.ioctl_ops = &vsp1_video_ioctl_ops;

	video_set_drvdata(&video->video, video);

	video->queue.type = video->type;
	video->queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	video->queue.lock = &video->lock;
	video->queue.drv_priv = video;
	video->queue.buf_काष्ठा_size = माप(काष्ठा vsp1_vb2_buffer);
	video->queue.ops = &vsp1_video_queue_qops;
	video->queue.mem_ops = &vb2_dma_contig_memops;
	video->queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	video->queue.dev = video->vsp1->bus_master;
	ret = vb2_queue_init(&video->queue);
	अगर (ret < 0) अणु
		dev_err(video->vsp1->dev, "failed to initialize vb2 queue\n");
		जाओ error;
	पूर्ण

	/* ... and रेजिस्टर the video device. */
	video->video.queue = &video->queue;
	ret = video_रेजिस्टर_device(&video->video, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		dev_err(video->vsp1->dev, "failed to register video device\n");
		जाओ error;
	पूर्ण

	वापस video;

error:
	vsp1_video_cleanup(video);
	वापस ERR_PTR(ret);
पूर्ण

व्योम vsp1_video_cleanup(काष्ठा vsp1_video *video)
अणु
	अगर (video_is_रेजिस्टरed(&video->video))
		video_unरेजिस्टर_device(&video->video);

	media_entity_cleanup(&video->video.entity);
पूर्ण
