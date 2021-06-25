<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * Media Controller ancillary functions
 *
 * Copyright (c) 2016 Mauro Carvalho Chehab <mchehab@kernel.org>
 * Copyright (C) 2016 Shuah Khan <shuahkh@osg.samsung.com>
 * Copyright (C) 2006-2010 Nokia Corporation
 * Copyright (c) 2016 Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/usb.h>
#समावेश <media/media-device.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-core.h>

पूर्णांक v4l2_mc_create_media_graph(काष्ठा media_device *mdev)

अणु
	काष्ठा media_entity *entity;
	काष्ठा media_entity *अगर_vid = शून्य, *अगर_aud = शून्य;
	काष्ठा media_entity *tuner = शून्य, *decoder = शून्य;
	काष्ठा media_entity *io_v4l = शून्य, *io_vbi = शून्य, *io_swradio = शून्य;
	bool is_webcam = false;
	u32 flags;
	पूर्णांक ret, pad_sink, pad_source;

	अगर (!mdev)
		वापस 0;

	media_device_क्रम_each_entity(entity, mdev) अणु
		चयन (entity->function) अणु
		हाल MEDIA_ENT_F_IF_VID_DECODER:
			अगर_vid = entity;
			अवरोध;
		हाल MEDIA_ENT_F_IF_AUD_DECODER:
			अगर_aud = entity;
			अवरोध;
		हाल MEDIA_ENT_F_TUNER:
			tuner = entity;
			अवरोध;
		हाल MEDIA_ENT_F_ATV_DECODER:
			decoder = entity;
			अवरोध;
		हाल MEDIA_ENT_F_IO_V4L:
			io_v4l = entity;
			अवरोध;
		हाल MEDIA_ENT_F_IO_VBI:
			io_vbi = entity;
			अवरोध;
		हाल MEDIA_ENT_F_IO_SWRADIO:
			io_swradio = entity;
			अवरोध;
		हाल MEDIA_ENT_F_CAM_SENSOR:
			is_webcam = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* It should have at least one I/O entity */
	अगर (!io_v4l && !io_vbi && !io_swradio) अणु
		dev_warn(mdev->dev, "Didn't find any I/O entity\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Here, webcams are modelled on a very simple way: the sensor is
	 * connected directly to the I/O entity. All dirty details, like
	 * scaler and crop HW are hidden. While such mapping is not enough
	 * क्रम mc-centric hardware, it is enough क्रम v4l2 पूर्णांकerface centric
	 * PC-consumer's hardware.
	 */
	अगर (is_webcam) अणु
		अगर (!io_v4l) अणु
			dev_warn(mdev->dev, "Didn't find a MEDIA_ENT_F_IO_V4L\n");
			वापस -EINVAL;
		पूर्ण

		media_device_क्रम_each_entity(entity, mdev) अणु
			अगर (entity->function != MEDIA_ENT_F_CAM_SENSOR)
				जारी;
			ret = media_create_pad_link(entity, 0,
						    io_v4l, 0,
						    MEDIA_LNK_FL_ENABLED);
			अगर (ret) अणु
				dev_warn(mdev->dev, "Failed to create a sensor link\n");
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (!decoder)
			वापस 0;
	पूर्ण

	/* The device isn't a webcam. So, it should have a decoder */
	अगर (!decoder) अणु
		dev_warn(mdev->dev, "Decoder not found\n");
		वापस -EINVAL;
	पूर्ण

	/* Link the tuner and IF video output pads */
	अगर (tuner) अणु
		अगर (अगर_vid) अणु
			pad_source = media_get_pad_index(tuner, false,
							 PAD_SIGNAL_ANALOG);
			pad_sink = media_get_pad_index(अगर_vid, true,
						       PAD_SIGNAL_ANALOG);
			अगर (pad_source < 0 || pad_sink < 0) अणु
				dev_warn(mdev->dev, "Couldn't get tuner and/or PLL pad(s): (%d, %d)\n",
					 pad_source, pad_sink);
				वापस -EINVAL;
			पूर्ण
			ret = media_create_pad_link(tuner, pad_source,
						    अगर_vid, pad_sink,
						    MEDIA_LNK_FL_ENABLED);
			अगर (ret) अणु
				dev_warn(mdev->dev, "Couldn't create tuner->PLL link)\n");
				वापस ret;
			पूर्ण

			pad_source = media_get_pad_index(अगर_vid, false,
							 PAD_SIGNAL_ANALOG);
			pad_sink = media_get_pad_index(decoder, true,
						       PAD_SIGNAL_ANALOG);
			अगर (pad_source < 0 || pad_sink < 0) अणु
				dev_warn(mdev->dev, "get decoder and/or PLL pad(s): (%d, %d)\n",
					 pad_source, pad_sink);
				वापस -EINVAL;
			पूर्ण
			ret = media_create_pad_link(अगर_vid, pad_source,
						    decoder, pad_sink,
						    MEDIA_LNK_FL_ENABLED);
			अगर (ret) अणु
				dev_warn(mdev->dev, "couldn't link PLL to decoder\n");
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			pad_source = media_get_pad_index(tuner, false,
							 PAD_SIGNAL_ANALOG);
			pad_sink = media_get_pad_index(decoder, true,
						       PAD_SIGNAL_ANALOG);
			अगर (pad_source < 0 || pad_sink < 0) अणु
				dev_warn(mdev->dev, "couldn't get tuner and/or decoder pad(s): (%d, %d)\n",
					 pad_source, pad_sink);
				वापस -EINVAL;
			पूर्ण
			ret = media_create_pad_link(tuner, pad_source,
						    decoder, pad_sink,
						    MEDIA_LNK_FL_ENABLED);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (अगर_aud) अणु
			pad_source = media_get_pad_index(tuner, false,
							 PAD_SIGNAL_AUDIO);
			pad_sink = media_get_pad_index(अगर_aud, true,
						       PAD_SIGNAL_AUDIO);
			अगर (pad_source < 0 || pad_sink < 0) अणु
				dev_warn(mdev->dev, "couldn't get tuner and/or decoder pad(s) for audio: (%d, %d)\n",
					 pad_source, pad_sink);
				वापस -EINVAL;
			पूर्ण
			ret = media_create_pad_link(tuner, pad_source,
						    अगर_aud, pad_sink,
						    MEDIA_LNK_FL_ENABLED);
			अगर (ret) अणु
				dev_warn(mdev->dev, "couldn't link tuner->audio PLL\n");
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर_aud = tuner;
		पूर्ण

	पूर्ण

	/* Create demod to V4L, VBI and SDR radio links */
	अगर (io_v4l) अणु
		pad_source = media_get_pad_index(decoder, false, PAD_SIGNAL_DV);
		अगर (pad_source < 0) अणु
			dev_warn(mdev->dev, "couldn't get decoder output pad for V4L I/O\n");
			वापस -EINVAL;
		पूर्ण
		ret = media_create_pad_link(decoder, pad_source,
					    io_v4l, 0,
					    MEDIA_LNK_FL_ENABLED);
		अगर (ret) अणु
			dev_warn(mdev->dev, "couldn't link decoder output to V4L I/O\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (io_swradio) अणु
		pad_source = media_get_pad_index(decoder, false, PAD_SIGNAL_DV);
		अगर (pad_source < 0) अणु
			dev_warn(mdev->dev, "couldn't get decoder output pad for SDR\n");
			वापस -EINVAL;
		पूर्ण
		ret = media_create_pad_link(decoder, pad_source,
					    io_swradio, 0,
					    MEDIA_LNK_FL_ENABLED);
		अगर (ret) अणु
			dev_warn(mdev->dev, "couldn't link decoder output to SDR\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (io_vbi) अणु
		pad_source = media_get_pad_index(decoder, false, PAD_SIGNAL_DV);
		अगर (pad_source < 0) अणु
			dev_warn(mdev->dev, "couldn't get decoder output pad for VBI\n");
			वापस -EINVAL;
		पूर्ण
		ret = media_create_pad_link(decoder, pad_source,
					    io_vbi, 0,
					    MEDIA_LNK_FL_ENABLED);
		अगर (ret) अणु
			dev_warn(mdev->dev, "couldn't link decoder output to VBI\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Create links क्रम the media connectors */
	flags = MEDIA_LNK_FL_ENABLED;
	media_device_क्रम_each_entity(entity, mdev) अणु
		चयन (entity->function) अणु
		हाल MEDIA_ENT_F_CONN_RF:
			अगर (!tuner)
				जारी;
			pad_sink = media_get_pad_index(tuner, true,
						       PAD_SIGNAL_ANALOG);
			अगर (pad_sink < 0) अणु
				dev_warn(mdev->dev, "couldn't get tuner analog pad sink\n");
				वापस -EINVAL;
			पूर्ण
			ret = media_create_pad_link(entity, 0, tuner,
						    pad_sink,
						    flags);
			अवरोध;
		हाल MEDIA_ENT_F_CONN_SVIDEO:
		हाल MEDIA_ENT_F_CONN_COMPOSITE:
			pad_sink = media_get_pad_index(decoder, true,
						       PAD_SIGNAL_ANALOG);
			अगर (pad_sink < 0) अणु
				dev_warn(mdev->dev, "couldn't get decoder analog pad sink\n");
				वापस -EINVAL;
			पूर्ण
			ret = media_create_pad_link(entity, 0, decoder,
						    pad_sink,
						    flags);
			अवरोध;
		शेष:
			जारी;
		पूर्ण
		अगर (ret)
			वापस ret;

		flags = 0;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_mc_create_media_graph);

पूर्णांक v4l_enable_media_source(काष्ठा video_device *vdev)
अणु
	काष्ठा media_device *mdev = vdev->entity.graph_obj.mdev;
	पूर्णांक ret = 0, err;

	अगर (!mdev)
		वापस 0;

	mutex_lock(&mdev->graph_mutex);
	अगर (!mdev->enable_source)
		जाओ end;
	err = mdev->enable_source(&vdev->entity, &vdev->pipe);
	अगर (err)
		ret = -EBUSY;
end:
	mutex_unlock(&mdev->graph_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l_enable_media_source);

व्योम v4l_disable_media_source(काष्ठा video_device *vdev)
अणु
	काष्ठा media_device *mdev = vdev->entity.graph_obj.mdev;

	अगर (mdev) अणु
		mutex_lock(&mdev->graph_mutex);
		अगर (mdev->disable_source)
			mdev->disable_source(&vdev->entity);
		mutex_unlock(&mdev->graph_mutex);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(v4l_disable_media_source);

पूर्णांक v4l_vb2q_enable_media_source(काष्ठा vb2_queue *q)
अणु
	काष्ठा v4l2_fh *fh = q->owner;

	अगर (fh && fh->vdev)
		वापस v4l_enable_media_source(fh->vdev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l_vb2q_enable_media_source);

पूर्णांक v4l2_create_fwnode_links_to_pad(काष्ठा v4l2_subdev *src_sd,
				    काष्ठा media_pad *sink, u32 flags)
अणु
	काष्ठा fwnode_handle *endpoपूर्णांक;
	काष्ठा v4l2_subdev *sink_sd;

	अगर (!(sink->flags & MEDIA_PAD_FL_SINK) ||
	    !is_media_entity_v4l2_subdev(sink->entity))
		वापस -EINVAL;

	sink_sd = media_entity_to_v4l2_subdev(sink->entity);

	fwnode_graph_क्रम_each_endpoपूर्णांक(dev_fwnode(src_sd->dev), endpoपूर्णांक) अणु
		काष्ठा fwnode_handle *remote_ep;
		पूर्णांक src_idx, sink_idx, ret;
		काष्ठा media_pad *src;

		src_idx = media_entity_get_fwnode_pad(&src_sd->entity,
						      endpoपूर्णांक,
						      MEDIA_PAD_FL_SOURCE);
		अगर (src_idx < 0)
			जारी;

		remote_ep = fwnode_graph_get_remote_endpoपूर्णांक(endpoपूर्णांक);
		अगर (!remote_ep)
			जारी;

		/*
		 * ask the sink to verअगरy it owns the remote endpoपूर्णांक,
		 * and translate to a sink pad.
		 */
		sink_idx = media_entity_get_fwnode_pad(&sink_sd->entity,
						       remote_ep,
						       MEDIA_PAD_FL_SINK);
		fwnode_handle_put(remote_ep);

		अगर (sink_idx < 0 || sink_idx != sink->index)
			जारी;

		/*
		 * the source endpoपूर्णांक corresponds to one of its source pads,
		 * the source endpoपूर्णांक connects to an endpoपूर्णांक at the sink
		 * entity, and the sink endpoपूर्णांक corresponds to the sink
		 * pad requested, so we have found an endpoपूर्णांक connection
		 * that works, create the media link क्रम it.
		 */

		src = &src_sd->entity.pads[src_idx];

		/* skip अगर link alपढ़ोy exists */
		अगर (media_entity_find_link(src, sink))
			जारी;

		dev_dbg(sink_sd->dev, "creating link %s:%d -> %s:%d\n",
			src_sd->entity.name, src_idx,
			sink_sd->entity.name, sink_idx);

		ret = media_create_pad_link(&src_sd->entity, src_idx,
					    &sink_sd->entity, sink_idx, flags);
		अगर (ret) अणु
			dev_err(sink_sd->dev,
				"link %s:%d -> %s:%d failed with %d\n",
				src_sd->entity.name, src_idx,
				sink_sd->entity.name, sink_idx, ret);

			fwnode_handle_put(endpoपूर्णांक);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_create_fwnode_links_to_pad);

पूर्णांक v4l2_create_fwnode_links(काष्ठा v4l2_subdev *src_sd,
			     काष्ठा v4l2_subdev *sink_sd)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sink_sd->entity.num_pads; i++) अणु
		काष्ठा media_pad *pad = &sink_sd->entity.pads[i];
		पूर्णांक ret;

		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			जारी;

		ret = v4l2_create_fwnode_links_to_pad(src_sd, pad, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_create_fwnode_links);

/* -----------------------------------------------------------------------------
 * Pipeline घातer management
 *
 * Entities must be घातered up when part of a pipeline that contains at least
 * one खोलो video device node.
 *
 * To achieve this use the entity use_count field to track the number of users.
 * For entities corresponding to video device nodes the use_count field stores
 * the users count of the node. For entities corresponding to subdevs the
 * use_count field stores the total number of users of all video device nodes
 * in the pipeline.
 *
 * The v4l2_pipeline_pm_अणुget, putपूर्ण() functions must be called in the खोलो() and
 * बंद() handlers of video device nodes. It increments or decrements the use
 * count of all subdev entities in the pipeline.
 *
 * To react to link management on घातered pipelines, the link setup notअगरication
 * callback updates the use count of all entities in the source and sink sides
 * of the link.
 */

/*
 * pipeline_pm_use_count - Count the number of users of a pipeline
 * @entity: The entity
 *
 * Return the total number of users of all video device nodes in the pipeline.
 */
अटल पूर्णांक pipeline_pm_use_count(काष्ठा media_entity *entity,
	काष्ठा media_graph *graph)
अणु
	पूर्णांक use = 0;

	media_graph_walk_start(graph, entity);

	जबतक ((entity = media_graph_walk_next(graph))) अणु
		अगर (is_media_entity_v4l2_video_device(entity))
			use += entity->use_count;
	पूर्ण

	वापस use;
पूर्ण

/*
 * pipeline_pm_घातer_one - Apply घातer change to an entity
 * @entity: The entity
 * @change: Use count change
 *
 * Change the entity use count by @change. If the entity is a subdev update its
 * घातer state by calling the core::s_घातer operation when the use count goes
 * from 0 to != 0 or from != 0 to 0.
 *
 * Return 0 on success or a negative error code on failure.
 */
अटल पूर्णांक pipeline_pm_घातer_one(काष्ठा media_entity *entity, पूर्णांक change)
अणु
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक ret;

	subdev = is_media_entity_v4l2_subdev(entity)
	       ? media_entity_to_v4l2_subdev(entity) : शून्य;

	अगर (entity->use_count == 0 && change > 0 && subdev != शून्य) अणु
		ret = v4l2_subdev_call(subdev, core, s_घातer, 1);
		अगर (ret < 0 && ret != -ENOIOCTLCMD)
			वापस ret;
	पूर्ण

	entity->use_count += change;
	WARN_ON(entity->use_count < 0);

	अगर (entity->use_count == 0 && change < 0 && subdev != शून्य)
		v4l2_subdev_call(subdev, core, s_घातer, 0);

	वापस 0;
पूर्ण

/*
 * pipeline_pm_घातer - Apply घातer change to all entities in a pipeline
 * @entity: The entity
 * @change: Use count change
 *
 * Walk the pipeline to update the use count and the घातer state of all non-node
 * entities.
 *
 * Return 0 on success or a negative error code on failure.
 */
अटल पूर्णांक pipeline_pm_घातer(काष्ठा media_entity *entity, पूर्णांक change,
	काष्ठा media_graph *graph)
अणु
	काष्ठा media_entity *first = entity;
	पूर्णांक ret = 0;

	अगर (!change)
		वापस 0;

	media_graph_walk_start(graph, entity);

	जबतक (!ret && (entity = media_graph_walk_next(graph)))
		अगर (is_media_entity_v4l2_subdev(entity))
			ret = pipeline_pm_घातer_one(entity, change);

	अगर (!ret)
		वापस ret;

	media_graph_walk_start(graph, first);

	जबतक ((first = media_graph_walk_next(graph))
	       && first != entity)
		अगर (is_media_entity_v4l2_subdev(first))
			pipeline_pm_घातer_one(first, -change);

	वापस ret;
पूर्ण

अटल पूर्णांक v4l2_pipeline_pm_use(काष्ठा media_entity *entity, अचिन्हित पूर्णांक use)
अणु
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	पूर्णांक change = use ? 1 : -1;
	पूर्णांक ret;

	mutex_lock(&mdev->graph_mutex);

	/* Apply use count to node. */
	entity->use_count += change;
	WARN_ON(entity->use_count < 0);

	/* Apply घातer change to connected non-nodes. */
	ret = pipeline_pm_घातer(entity, change, &mdev->pm_count_walk);
	अगर (ret < 0)
		entity->use_count -= change;

	mutex_unlock(&mdev->graph_mutex);

	वापस ret;
पूर्ण

पूर्णांक v4l2_pipeline_pm_get(काष्ठा media_entity *entity)
अणु
	वापस v4l2_pipeline_pm_use(entity, 1);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_pipeline_pm_get);

व्योम v4l2_pipeline_pm_put(काष्ठा media_entity *entity)
अणु
	/* Powering off entities shouldn't fail. */
	WARN_ON(v4l2_pipeline_pm_use(entity, 0));
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_pipeline_pm_put);

पूर्णांक v4l2_pipeline_link_notअगरy(काष्ठा media_link *link, u32 flags,
			      अचिन्हित पूर्णांक notअगरication)
अणु
	काष्ठा media_graph *graph = &link->graph_obj.mdev->pm_count_walk;
	काष्ठा media_entity *source = link->source->entity;
	काष्ठा media_entity *sink = link->sink->entity;
	पूर्णांक source_use;
	पूर्णांक sink_use;
	पूर्णांक ret = 0;

	source_use = pipeline_pm_use_count(source, graph);
	sink_use = pipeline_pm_use_count(sink, graph);

	अगर (notअगरication == MEDIA_DEV_NOTIFY_POST_LINK_CH &&
	    !(flags & MEDIA_LNK_FL_ENABLED)) अणु
		/* Powering off entities is assumed to never fail. */
		pipeline_pm_घातer(source, -sink_use, graph);
		pipeline_pm_घातer(sink, -source_use, graph);
		वापस 0;
	पूर्ण

	अगर (notअगरication == MEDIA_DEV_NOTIFY_PRE_LINK_CH &&
		(flags & MEDIA_LNK_FL_ENABLED)) अणु

		ret = pipeline_pm_घातer(source, sink_use, graph);
		अगर (ret < 0)
			वापस ret;

		ret = pipeline_pm_घातer(sink, source_use, graph);
		अगर (ret < 0)
			pipeline_pm_घातer(source, -sink_use, graph);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_pipeline_link_notअगरy);
