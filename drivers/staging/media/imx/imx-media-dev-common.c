<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * V4L2 Media Controller Driver क्रम Freescale common i.MX5/6/7 SOC
 *
 * Copyright (c) 2019 Linaro Ltd
 * Copyright (c) 2016 Mentor Graphics Inc.
 */

#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>
#समावेश "imx-media.h"

अटल अंतरभूत काष्ठा imx_media_dev *notअगरier2dev(काष्ठा v4l2_async_notअगरier *n)
अणु
	वापस container_of(n, काष्ठा imx_media_dev, notअगरier);
पूर्ण

/* async subdev bound notअगरier */
अटल पूर्णांक imx_media_subdev_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				  काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा imx_media_dev *imxmd = notअगरier2dev(notअगरier);

	dev_dbg(imxmd->md.dev, "subdev %s bound\n", sd->name);

	वापस 0;
पूर्ण

/*
 * Create the missing media links from the CSI-2 receiver.
 * Called after all async subdevs have bound.
 */
अटल व्योम imx_media_create_csi2_links(काष्ठा imx_media_dev *imxmd)
अणु
	काष्ठा v4l2_subdev *sd, *csi2 = शून्य;

	list_क्रम_each_entry(sd, &imxmd->v4l2_dev.subdevs, list) अणु
		अगर (sd->grp_id == IMX_MEDIA_GRP_ID_CSI2) अणु
			csi2 = sd;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!csi2)
		वापस;

	list_क्रम_each_entry(sd, &imxmd->v4l2_dev.subdevs, list) अणु
		/* skip अगर not a CSI or a CSI mux */
		अगर (!(sd->grp_id & IMX_MEDIA_GRP_ID_IPU_CSI) &&
		    !(sd->grp_id & IMX_MEDIA_GRP_ID_CSI) &&
		    !(sd->grp_id & IMX_MEDIA_GRP_ID_CSI_MUX))
			जारी;

		v4l2_create_fwnode_links(csi2, sd);
	पूर्ण
पूर्ण

/*
 * adds given video device to given imx-media source pad vdev list.
 * Continues upstream from the pad entity's sink pads.
 */
अटल पूर्णांक imx_media_add_vdev_to_pad(काष्ठा imx_media_dev *imxmd,
				     काष्ठा imx_media_video_dev *vdev,
				     काष्ठा media_pad *srcpad)
अणु
	काष्ठा media_entity *entity = srcpad->entity;
	काष्ठा imx_media_pad_vdev *pad_vdev;
	काष्ठा list_head *pad_vdev_list;
	काष्ठा media_link *link;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक i, ret;

	/* skip this entity अगर not a v4l2_subdev */
	अगर (!is_media_entity_v4l2_subdev(entity))
		वापस 0;

	sd = media_entity_to_v4l2_subdev(entity);

	pad_vdev_list = to_pad_vdev_list(sd, srcpad->index);
	अगर (!pad_vdev_list) अणु
		v4l2_warn(&imxmd->v4l2_dev, "%s:%u has no vdev list!\n",
			  entity->name, srcpad->index);
		/*
		 * shouldn't happen, but no reason to fail driver load,
		 * just skip this entity.
		 */
		वापस 0;
	पूर्ण

	/* just वापस अगर we've been here beक्रमe */
	list_क्रम_each_entry(pad_vdev, pad_vdev_list, list) अणु
		अगर (pad_vdev->vdev == vdev)
			वापस 0;
	पूर्ण

	dev_dbg(imxmd->md.dev, "adding %s to pad %s:%u\n",
		vdev->vfd->entity.name, entity->name, srcpad->index);

	pad_vdev = devm_kzalloc(imxmd->md.dev, माप(*pad_vdev), GFP_KERNEL);
	अगर (!pad_vdev)
		वापस -ENOMEM;

	/* attach this vdev to this pad */
	pad_vdev->vdev = vdev;
	list_add_tail(&pad_vdev->list, pad_vdev_list);

	/* move upstream from this entity's sink pads */
	क्रम (i = 0; i < entity->num_pads; i++) अणु
		काष्ठा media_pad *pad = &entity->pads[i];

		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			जारी;

		list_क्रम_each_entry(link, &entity->links, list) अणु
			अगर (link->sink != pad)
				जारी;
			ret = imx_media_add_vdev_to_pad(imxmd, vdev,
							link->source);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * For every subdevice, allocate an array of list_head's, one list_head
 * क्रम each pad, to hold the list of video devices reachable from that
 * pad.
 */
अटल पूर्णांक imx_media_alloc_pad_vdev_lists(काष्ठा imx_media_dev *imxmd)
अणु
	काष्ठा list_head *vdev_lists;
	काष्ठा media_entity *entity;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक i;

	list_क्रम_each_entry(sd, &imxmd->v4l2_dev.subdevs, list) अणु
		entity = &sd->entity;
		vdev_lists = devm_kसुस्मृति(imxmd->md.dev,
					  entity->num_pads, माप(*vdev_lists),
					  GFP_KERNEL);
		अगर (!vdev_lists)
			वापस -ENOMEM;

		/* attach to the subdev's host निजी poपूर्णांकer */
		sd->host_priv = vdev_lists;

		क्रम (i = 0; i < entity->num_pads; i++)
			INIT_LIST_HEAD(to_pad_vdev_list(sd, i));
	पूर्ण

	वापस 0;
पूर्ण

/* क्रमm the vdev lists in all imx-media source pads */
अटल पूर्णांक imx_media_create_pad_vdev_lists(काष्ठा imx_media_dev *imxmd)
अणु
	काष्ठा imx_media_video_dev *vdev;
	काष्ठा media_link *link;
	पूर्णांक ret;

	ret = imx_media_alloc_pad_vdev_lists(imxmd);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(vdev, &imxmd->vdev_list, list) अणु
		link = list_first_entry(&vdev->vfd->entity.links,
					काष्ठा media_link, list);
		ret = imx_media_add_vdev_to_pad(imxmd, vdev, link->source);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* async subdev complete notअगरier */
पूर्णांक imx_media_probe_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा imx_media_dev *imxmd = notअगरier2dev(notअगरier);
	पूर्णांक ret;

	mutex_lock(&imxmd->mutex);

	imx_media_create_csi2_links(imxmd);

	ret = imx_media_create_pad_vdev_lists(imxmd);
	अगर (ret)
		जाओ unlock;

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&imxmd->v4l2_dev);
unlock:
	mutex_unlock(&imxmd->mutex);
	अगर (ret)
		वापस ret;

	वापस media_device_रेजिस्टर(&imxmd->md);
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_probe_complete);

/*
 * adds controls to a video device from an entity subdevice.
 * Continues upstream from the entity's sink pads.
 */
अटल पूर्णांक imx_media_inherit_controls(काष्ठा imx_media_dev *imxmd,
				      काष्ठा video_device *vfd,
				      काष्ठा media_entity *entity)
अणु
	पूर्णांक i, ret = 0;

	अगर (is_media_entity_v4l2_subdev(entity)) अणु
		काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);

		dev_dbg(imxmd->md.dev,
			"adding controls to %s from %s\n",
			vfd->entity.name, sd->entity.name);

		ret = v4l2_ctrl_add_handler(vfd->ctrl_handler,
					    sd->ctrl_handler,
					    शून्य, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* move upstream */
	क्रम (i = 0; i < entity->num_pads; i++) अणु
		काष्ठा media_pad *pad, *spad = &entity->pads[i];

		अगर (!(spad->flags & MEDIA_PAD_FL_SINK))
			जारी;

		pad = media_entity_remote_pad(spad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			जारी;

		ret = imx_media_inherit_controls(imxmd, vfd, pad->entity);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक imx_media_link_notअगरy(काष्ठा media_link *link, u32 flags,
				 अचिन्हित पूर्णांक notअगरication)
अणु
	काष्ठा imx_media_dev *imxmd = container_of(link->graph_obj.mdev,
						   काष्ठा imx_media_dev, md);
	काष्ठा media_entity *source = link->source->entity;
	काष्ठा imx_media_pad_vdev *pad_vdev;
	काष्ठा list_head *pad_vdev_list;
	काष्ठा video_device *vfd;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक pad_idx, ret;

	ret = v4l2_pipeline_link_notअगरy(link, flags, notअगरication);
	अगर (ret)
		वापस ret;

	/* करोn't bother अगर source is not a subdev */
	अगर (!is_media_entity_v4l2_subdev(source))
		वापस 0;

	sd = media_entity_to_v4l2_subdev(source);
	pad_idx = link->source->index;

	pad_vdev_list = to_pad_vdev_list(sd, pad_idx);
	अगर (!pad_vdev_list) अणु
		/* nothing to करो अगर source sd has no pad vdev list */
		वापस 0;
	पूर्ण

	/*
	 * Beक्रमe disabling a link, reset controls क्रम all video
	 * devices reachable from this link.
	 *
	 * After enabling a link, refresh controls क्रम all video
	 * devices reachable from this link.
	 */
	अगर (notअगरication == MEDIA_DEV_NOTIFY_PRE_LINK_CH &&
	    !(flags & MEDIA_LNK_FL_ENABLED)) अणु
		list_क्रम_each_entry(pad_vdev, pad_vdev_list, list) अणु
			vfd = pad_vdev->vdev->vfd;
			अगर (!vfd->ctrl_handler)
				जारी;
			dev_dbg(imxmd->md.dev,
				"reset controls for %s\n",
				vfd->entity.name);
			v4l2_ctrl_handler_मुक्त(vfd->ctrl_handler);
			v4l2_ctrl_handler_init(vfd->ctrl_handler, 0);
		पूर्ण
	पूर्ण अन्यथा अगर (notअगरication == MEDIA_DEV_NOTIFY_POST_LINK_CH &&
		   (link->flags & MEDIA_LNK_FL_ENABLED)) अणु
		list_क्रम_each_entry(pad_vdev, pad_vdev_list, list) अणु
			vfd = pad_vdev->vdev->vfd;
			अगर (!vfd->ctrl_handler)
				जारी;
			dev_dbg(imxmd->md.dev,
				"refresh controls for %s\n",
				vfd->entity.name);
			ret = imx_media_inherit_controls(imxmd, vfd,
							 &vfd->entity);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम imx_media_notअगरy(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक notअगरication,
			     व्योम *arg)
अणु
	काष्ठा media_entity *entity = &sd->entity;
	पूर्णांक i;

	अगर (notअगरication != V4L2_DEVICE_NOTIFY_EVENT)
		वापस;

	क्रम (i = 0; i < entity->num_pads; i++) अणु
		काष्ठा media_pad *pad = &entity->pads[i];
		काष्ठा imx_media_pad_vdev *pad_vdev;
		काष्ठा list_head *pad_vdev_list;

		pad_vdev_list = to_pad_vdev_list(sd, pad->index);
		अगर (!pad_vdev_list)
			जारी;
		list_क्रम_each_entry(pad_vdev, pad_vdev_list, list)
			v4l2_event_queue(pad_vdev->vdev->vfd, arg);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations imx_media_notअगरier_ops = अणु
	.bound = imx_media_subdev_bound,
	.complete = imx_media_probe_complete,
पूर्ण;

अटल स्थिर काष्ठा media_device_ops imx_media_md_ops = अणु
	.link_notअगरy = imx_media_link_notअगरy,
पूर्ण;

काष्ठा imx_media_dev *imx_media_dev_init(काष्ठा device *dev,
					 स्थिर काष्ठा media_device_ops *ops)
अणु
	काष्ठा imx_media_dev *imxmd;
	पूर्णांक ret;

	imxmd = devm_kzalloc(dev, माप(*imxmd), GFP_KERNEL);
	अगर (!imxmd)
		वापस ERR_PTR(-ENOMEM);

	dev_set_drvdata(dev, imxmd);

	strscpy(imxmd->md.model, "imx-media", माप(imxmd->md.model));
	imxmd->md.ops = ops ? ops : &imx_media_md_ops;
	imxmd->md.dev = dev;

	mutex_init(&imxmd->mutex);

	imxmd->v4l2_dev.mdev = &imxmd->md;
	imxmd->v4l2_dev.notअगरy = imx_media_notअगरy;
	strscpy(imxmd->v4l2_dev.name, "imx-media",
		माप(imxmd->v4l2_dev.name));

	media_device_init(&imxmd->md);

	ret = v4l2_device_रेजिस्टर(dev, &imxmd->v4l2_dev);
	अगर (ret < 0) अणु
		v4l2_err(&imxmd->v4l2_dev,
			 "Failed to register v4l2_device: %d\n", ret);
		जाओ cleanup;
	पूर्ण

	INIT_LIST_HEAD(&imxmd->vdev_list);

	v4l2_async_notअगरier_init(&imxmd->notअगरier);

	वापस imxmd;

cleanup:
	media_device_cleanup(&imxmd->md);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_dev_init);

पूर्णांक imx_media_dev_notअगरier_रेजिस्टर(काष्ठा imx_media_dev *imxmd,
			    स्थिर काष्ठा v4l2_async_notअगरier_operations *ops)
अणु
	पूर्णांक ret;

	/* no subdevs? just bail */
	अगर (list_empty(&imxmd->notअगरier.asd_list)) अणु
		v4l2_err(&imxmd->v4l2_dev, "no subdevs\n");
		वापस -ENODEV;
	पूर्ण

	/* prepare the async subdev notअगरier and रेजिस्टर it */
	imxmd->notअगरier.ops = ops ? ops : &imx_media_notअगरier_ops;
	ret = v4l2_async_notअगरier_रेजिस्टर(&imxmd->v4l2_dev,
					   &imxmd->notअगरier);
	अगर (ret) अणु
		v4l2_err(&imxmd->v4l2_dev,
			 "v4l2_async_notifier_register failed with %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_dev_notअगरier_रेजिस्टर);
