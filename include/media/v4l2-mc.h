<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * v4l2-mc.h - Media Controller V4L2 types and prototypes
 *
 * Copyright (C) 2016 Mauro Carvalho Chehab <mchehab@kernel.org>
 * Copyright (C) 2006-2010 Nokia Corporation
 * Copyright (c) 2016 Intel Corporation.
 */

#अगर_अघोषित _V4L2_MC_H
#घोषणा _V4L2_MC_H

#समावेश <media/media-device.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <linux/types.h>

/* We करोn't need to include pci.h or usb.h here */
काष्ठा pci_dev;
काष्ठा usb_device;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
/**
 * v4l2_mc_create_media_graph() - create Media Controller links at the graph.
 *
 * @mdev:	poपूर्णांकer to the &media_device काष्ठा.
 *
 * Add links between the entities commonly found on PC customer's hardware at
 * the V4L2 side: camera sensors, audio and video PLL-IF decoders, tuners,
 * analog TV decoder and I/O entities (video, VBI and Software Defined Radio).
 *
 * .. note::
 *
 *    Webcams are modelled on a very simple way: the sensor is
 *    connected directly to the I/O entity. All dirty details, like
 *    scaler and crop HW are hidden. While such mapping is enough क्रम v4l2
 *    पूर्णांकerface centric PC-consumer's hardware, V4L2 subdev centric camera
 *    hardware should not use this routine, as it will not build the right graph.
 */
पूर्णांक v4l2_mc_create_media_graph(काष्ठा media_device *mdev);

/**
 * v4l_enable_media_source() -	Hold media source क्रम exclusive use
 *				अगर मुक्त
 *
 * @vdev:	poपूर्णांकer to काष्ठा video_device
 *
 * This पूर्णांकerface calls enable_source handler to determine अगर
 * media source is मुक्त क्रम use. The enable_source handler is
 * responsible क्रम checking is the media source is मुक्त and
 * start a pipeline between the media source and the media
 * entity associated with the video device. This पूर्णांकerface
 * should be called from v4l2-core and dvb-core पूर्णांकerfaces
 * that change the source configuration.
 *
 * Return: वापसs zero on success or a negative error code.
 */
पूर्णांक v4l_enable_media_source(काष्ठा video_device *vdev);

/**
 * v4l_disable_media_source() -	Release media source
 *
 * @vdev:	poपूर्णांकer to काष्ठा video_device
 *
 * This पूर्णांकerface calls disable_source handler to release
 * the media source. The disable_source handler stops the
 * active media pipeline between the media source and the
 * media entity associated with the video device.
 *
 * Return: वापसs zero on success or a negative error code.
 */
व्योम v4l_disable_media_source(काष्ठा video_device *vdev);

/*
 * v4l_vb2q_enable_media_tuner -  Hold media source क्रम exclusive use
 *				  अगर मुक्त.
 * @q - poपूर्णांकer to काष्ठा vb2_queue
 *
 * Wrapper क्रम v4l_enable_media_source(). This function should
 * be called from v4l2-core to enable the media source with
 * poपूर्णांकer to काष्ठा vb2_queue as the input argument. Some
 * v4l2-core पूर्णांकerfaces करोn't have access to video device and
 * this पूर्णांकerface finds the काष्ठा video_device क्रम the q and
 * calls v4l_enable_media_source().
 */
पूर्णांक v4l_vb2q_enable_media_source(काष्ठा vb2_queue *q);

/**
 * v4l2_create_fwnode_links_to_pad - Create fwnode-based links from a
 *                                   source subdev to a sink subdev pad.
 *
 * @src_sd: poपूर्णांकer to a source subdev
 * @sink:  poपूर्णांकer to a subdev sink pad
 * @flags: the link flags
 *
 * This function searches क्रम fwnode endpoपूर्णांक connections from a source
 * subdevice to a single sink pad, and अगर suitable connections are found,
 * translates them पूर्णांकo media links to that pad. The function can be
 * called by the sink subdevice, in its v4l2-async notअगरier subdev bound
 * callback, to create links from a bound source subdevice.
 *
 * The @flags argument specअगरies the link flags. The caller shall ensure that
 * the flags are valid regardless of the number of links that may be created.
 * For instance, setting the MEDIA_LNK_FL_ENABLED flag will cause all created
 * links to be enabled, which isn't valid अगर more than one link is created.
 *
 * .. note::
 *
 *    Any sink subdevice that calls this function must implement the
 *    .get_fwnode_pad media operation in order to verअगरy endpoपूर्णांकs passed
 *    to the sink are owned by the sink.
 *
 * Return 0 on success or a negative error code on failure.
 */
पूर्णांक v4l2_create_fwnode_links_to_pad(काष्ठा v4l2_subdev *src_sd,
				    काष्ठा media_pad *sink, u32 flags);

/**
 * v4l2_create_fwnode_links - Create fwnode-based links from a source
 *                            subdev to a sink subdev.
 *
 * @src_sd: poपूर्णांकer to a source subdevice
 * @sink_sd: poपूर्णांकer to a sink subdevice
 *
 * This function searches क्रम any and all fwnode endpoपूर्णांक connections
 * between source and sink subdevices, and translates them पूर्णांकo media
 * links. The function can be called by the sink subdevice, in its
 * v4l2-async notअगरier subdev bound callback, to create all links from
 * a bound source subdevice.
 *
 * .. note::
 *
 *    Any sink subdevice that calls this function must implement the
 *    .get_fwnode_pad media operation in order to verअगरy endpoपूर्णांकs passed
 *    to the sink are owned by the sink.
 *
 * Return 0 on success or a negative error code on failure.
 */
पूर्णांक v4l2_create_fwnode_links(काष्ठा v4l2_subdev *src_sd,
			     काष्ठा v4l2_subdev *sink_sd);

/**
 * v4l2_pipeline_pm_get - Increase the use count of a pipeline
 * @entity: The root entity of a pipeline
 *
 * Update the use count of all entities in the pipeline and घातer entities on.
 *
 * This function is पूर्णांकended to be called in video node खोलो. It uses
 * काष्ठा media_entity.use_count to track the घातer status. The use
 * of this function should be paired with v4l2_pipeline_link_notअगरy().
 *
 * Return 0 on success or a negative error code on failure.
 */
पूर्णांक v4l2_pipeline_pm_get(काष्ठा media_entity *entity);

/**
 * v4l2_pipeline_pm_put - Decrease the use count of a pipeline
 * @entity: The root entity of a pipeline
 *
 * Update the use count of all entities in the pipeline and घातer entities off.
 *
 * This function is पूर्णांकended to be called in video node release. It uses
 * काष्ठा media_entity.use_count to track the घातer status. The use
 * of this function should be paired with v4l2_pipeline_link_notअगरy().
 */
व्योम v4l2_pipeline_pm_put(काष्ठा media_entity *entity);


/**
 * v4l2_pipeline_link_notअगरy - Link management notअगरication callback
 * @link: The link
 * @flags: New link flags that will be applied
 * @notअगरication: The link's state change notअगरication type (MEDIA_DEV_NOTIFY_*)
 *
 * React to link management on घातered pipelines by updating the use count of
 * all entities in the source and sink sides of the link. Entities are घातered
 * on or off accordingly. The use of this function should be paired
 * with v4l2_pipeline_pm_अणुget,putपूर्ण().
 *
 * Return 0 on success or a negative error code on failure. Powering entities
 * off is assumed to never fail. This function will not fail क्रम disconnection
 * events.
 */
पूर्णांक v4l2_pipeline_link_notअगरy(काष्ठा media_link *link, u32 flags,
			      अचिन्हित पूर्णांक notअगरication);

#अन्यथा /* CONFIG_MEDIA_CONTROLLER */

अटल अंतरभूत पूर्णांक v4l2_mc_create_media_graph(काष्ठा media_device *mdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक v4l_enable_media_source(काष्ठा video_device *vdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम v4l_disable_media_source(काष्ठा video_device *vdev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक v4l_vb2q_enable_media_source(काष्ठा vb2_queue *q)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक v4l2_pipeline_pm_get(काष्ठा media_entity *entity)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम v4l2_pipeline_pm_put(काष्ठा media_entity *entity)
अणुपूर्ण

अटल अंतरभूत पूर्णांक v4l2_pipeline_link_notअगरy(काष्ठा media_link *link, u32 flags,
					    अचिन्हित पूर्णांक notअगरication)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER */
#पूर्ण_अगर /* _V4L2_MC_H */
