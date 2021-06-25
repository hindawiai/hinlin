<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Renesas R-Car VIN
 *
 * Copyright (C) 2016 Renesas Electronics Corp.
 * Copyright (C) 2011-2013 Renesas Solutions Corp.
 * Copyright (C) 2013 Cogent Embedded, Inc., <source@cogentembedded.com>
 * Copyright (C) 2008 Magnus Damm
 *
 * Based on the soc-camera rcar_vin driver
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-mc.h>

#समावेश "rcar-vin.h"

/*
 * The companion CSI-2 receiver driver (rcar-csi2) is known
 * and we know it has one source pad (pad 0) and four sink
 * pads (pad 1-4). So to translate a pad on the remote
 * CSI-2 receiver to/from the VIN पूर्णांकernal channel number simply
 * subtract/add one from the pad/channel number.
 */
#घोषणा rvin_group_csi_pad_to_channel(pad) ((pad) - 1)
#घोषणा rvin_group_csi_channel_to_pad(channel) ((channel) + 1)

/*
 * Not all VINs are created equal, master VINs control the
 * routing क्रम other VIN's. We can figure out which VIN is
 * master by looking at a VINs id.
 */
#घोषणा rvin_group_id_to_master(vin) ((vin) < 4 ? 0 : 4)

#घोषणा v4l2_dev_to_vin(d)	container_of(d, काष्ठा rvin_dev, v4l2_dev)

/* -----------------------------------------------------------------------------
 * Media Controller link notअगरication
 */

/* group lock should be held when calling this function. */
अटल पूर्णांक rvin_group_entity_to_csi_id(काष्ठा rvin_group *group,
				       काष्ठा media_entity *entity)
अणु
	काष्ठा v4l2_subdev *sd;
	अचिन्हित पूर्णांक i;

	sd = media_entity_to_v4l2_subdev(entity);

	क्रम (i = 0; i < RVIN_CSI_MAX; i++)
		अगर (group->csi[i].subdev == sd)
			वापस i;

	वापस -ENODEV;
पूर्ण

अटल अचिन्हित पूर्णांक rvin_group_get_mask(काष्ठा rvin_dev *vin,
					क्रमागत rvin_csi_id csi_id,
					अचिन्हित अक्षर channel)
अणु
	स्थिर काष्ठा rvin_group_route *route;
	अचिन्हित पूर्णांक mask = 0;

	क्रम (route = vin->info->routes; route->mask; route++) अणु
		अगर (route->vin == vin->id &&
		    route->csi == csi_id &&
		    route->channel == channel) अणु
			vin_dbg(vin,
				"Adding route: vin: %d csi: %d channel: %d\n",
				route->vin, route->csi, route->channel);
			mask |= route->mask;
		पूर्ण
	पूर्ण

	वापस mask;
पूर्ण

/*
 * Link setup क्रम the links between a VIN and a CSI-2 receiver is a bit
 * complex. The reason क्रम this is that the रेजिस्टर controlling routing
 * is not present in each VIN instance. There are special VINs which
 * control routing क्रम themselves and other VINs. There are not many
 * dअगरferent possible links combinations that can be enabled at the same
 * समय, thereक्रम all alपढ़ोy enabled links which are controlled by a
 * master VIN need to be taken पूर्णांकo account when making the decision
 * अगर a new link can be enabled or not.
 *
 * 1. Find out which VIN the link the user tries to enable is connected to.
 * 2. Lookup which master VIN controls the links क्रम this VIN.
 * 3. Start with a biपंचांगask with all bits set.
 * 4. For each previously enabled link from the master VIN bitwise AND its
 *    route mask (see करोcumentation क्रम mask in काष्ठा rvin_group_route)
 *    with the biपंचांगask.
 * 5. Bitwise AND the mask क्रम the link the user tries to enable to the biपंचांगask.
 * 6. If the biपंचांगask is not empty at this poपूर्णांक the new link can be enabled
 *    जबतक keeping all previous links enabled. Update the CHSEL value of the
 *    master VIN and inक्रमm the user that the link could be enabled.
 *
 * Please note that no link can be enabled अगर any VIN in the group is
 * currently खोलो.
 */
अटल पूर्णांक rvin_group_link_notअगरy(काष्ठा media_link *link, u32 flags,
				  अचिन्हित पूर्णांक notअगरication)
अणु
	काष्ठा rvin_group *group = container_of(link->graph_obj.mdev,
						काष्ठा rvin_group, mdev);
	अचिन्हित पूर्णांक master_id, channel, mask_new, i;
	अचिन्हित पूर्णांक mask = ~0;
	काष्ठा media_entity *entity;
	काष्ठा video_device *vdev;
	काष्ठा media_pad *csi_pad;
	काष्ठा rvin_dev *vin = शून्य;
	पूर्णांक csi_id, ret;

	ret = v4l2_pipeline_link_notअगरy(link, flags, notअगरication);
	अगर (ret)
		वापस ret;

	/* Only care about link enablement क्रम VIN nodes. */
	अगर (!(flags & MEDIA_LNK_FL_ENABLED) ||
	    !is_media_entity_v4l2_video_device(link->sink->entity))
		वापस 0;

	/*
	 * Don't allow link changes अगर any entity in the graph is
	 * streaming, modअगरying the CHSEL रेजिस्टर fields can disrupt
	 * running streams.
	 */
	media_device_क्रम_each_entity(entity, &group->mdev)
		अगर (entity->stream_count)
			वापस -EBUSY;

	mutex_lock(&group->lock);

	/* Find the master VIN that controls the routes. */
	vdev = media_entity_to_video_device(link->sink->entity);
	vin = container_of(vdev, काष्ठा rvin_dev, vdev);
	master_id = rvin_group_id_to_master(vin->id);

	अगर (WARN_ON(!group->vin[master_id])) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* Build a mask क्रम alपढ़ोy enabled links. */
	क्रम (i = master_id; i < master_id + 4; i++) अणु
		अगर (!group->vin[i])
			जारी;

		/* Get remote CSI-2, अगर any. */
		csi_pad = media_entity_remote_pad(
				&group->vin[i]->vdev.entity.pads[0]);
		अगर (!csi_pad)
			जारी;

		csi_id = rvin_group_entity_to_csi_id(group, csi_pad->entity);
		channel = rvin_group_csi_pad_to_channel(csi_pad->index);

		mask &= rvin_group_get_mask(group->vin[i], csi_id, channel);
	पूर्ण

	/* Add the new link to the existing mask and check अगर it works. */
	csi_id = rvin_group_entity_to_csi_id(group, link->source->entity);

	अगर (csi_id == -ENODEV) अणु
		काष्ठा v4l2_subdev *sd;

		/*
		 * Make sure the source entity subdevice is रेजिस्टरed as
		 * a parallel input of one of the enabled VINs अगर it is not
		 * one of the CSI-2 subdevices.
		 *
		 * No hardware configuration required क्रम parallel inमाला_दो,
		 * we can वापस here.
		 */
		sd = media_entity_to_v4l2_subdev(link->source->entity);
		क्रम (i = 0; i < RCAR_VIN_NUM; i++) अणु
			अगर (group->vin[i] &&
			    group->vin[i]->parallel.subdev == sd) अणु
				group->vin[i]->is_csi = false;
				ret = 0;
				जाओ out;
			पूर्ण
		पूर्ण

		vin_err(vin, "Subdevice %s not registered to any VIN\n",
			link->source->entity->name);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	channel = rvin_group_csi_pad_to_channel(link->source->index);
	mask_new = mask & rvin_group_get_mask(vin, csi_id, channel);
	vin_dbg(vin, "Try link change mask: 0x%x new: 0x%x\n", mask, mask_new);

	अगर (!mask_new) अणु
		ret = -EMLINK;
		जाओ out;
	पूर्ण

	/* New valid CHSEL found, set the new value. */
	ret = rvin_set_channel_routing(group->vin[master_id], __ffs(mask_new));
	अगर (ret)
		जाओ out;

	vin->is_csi = true;

out:
	mutex_unlock(&group->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा media_device_ops rvin_media_ops = अणु
	.link_notअगरy = rvin_group_link_notअगरy,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Gen3 CSI2 Group Allocator
 */

/* FIXME:  This should अगर we find a प्रणाली that supports more
 * than one group क्रम the whole प्रणाली be replaced with a linked
 * list of groups. And eventually all of this should be replaced
 * with a global device allocator API.
 *
 * But क्रम now this works as on all supported प्रणालीs there will
 * be only one group क्रम all instances.
 */

अटल DEFINE_MUTEX(rvin_group_lock);
अटल काष्ठा rvin_group *rvin_group_data;

अटल व्योम rvin_group_cleanup(काष्ठा rvin_group *group)
अणु
	media_device_cleanup(&group->mdev);
	mutex_destroy(&group->lock);
पूर्ण

अटल पूर्णांक rvin_group_init(काष्ठा rvin_group *group, काष्ठा rvin_dev *vin)
अणु
	काष्ठा media_device *mdev = &group->mdev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;

	mutex_init(&group->lock);

	/* Count number of VINs in the प्रणाली */
	group->count = 0;
	क्रम_each_matching_node(np, vin->dev->driver->of_match_table)
		अगर (of_device_is_available(np))
			group->count++;

	vin_dbg(vin, "found %u enabled VIN's in DT", group->count);

	mdev->dev = vin->dev;
	mdev->ops = &rvin_media_ops;

	match = of_match_node(vin->dev->driver->of_match_table,
			      vin->dev->of_node);

	strscpy(mdev->driver_name, KBUILD_MODNAME, माप(mdev->driver_name));
	strscpy(mdev->model, match->compatible, माप(mdev->model));
	snम_लिखो(mdev->bus_info, माप(mdev->bus_info), "platform:%s",
		 dev_name(mdev->dev));

	media_device_init(mdev);

	वापस 0;
पूर्ण

अटल व्योम rvin_group_release(काष्ठा kref *kref)
अणु
	काष्ठा rvin_group *group =
		container_of(kref, काष्ठा rvin_group, refcount);

	mutex_lock(&rvin_group_lock);

	rvin_group_data = शून्य;

	rvin_group_cleanup(group);

	kमुक्त(group);

	mutex_unlock(&rvin_group_lock);
पूर्ण

अटल पूर्णांक rvin_group_get(काष्ठा rvin_dev *vin)
अणु
	काष्ठा rvin_group *group;
	u32 id;
	पूर्णांक ret;

	/* Make sure VIN id is present and sane */
	ret = of_property_पढ़ो_u32(vin->dev->of_node, "renesas,id", &id);
	अगर (ret) अणु
		vin_err(vin, "%pOF: No renesas,id property found\n",
			vin->dev->of_node);
		वापस -EINVAL;
	पूर्ण

	अगर (id >= RCAR_VIN_NUM) अणु
		vin_err(vin, "%pOF: Invalid renesas,id '%u'\n",
			vin->dev->of_node, id);
		वापस -EINVAL;
	पूर्ण

	/* Join or create a VIN group */
	mutex_lock(&rvin_group_lock);
	अगर (rvin_group_data) अणु
		group = rvin_group_data;
		kref_get(&group->refcount);
	पूर्ण अन्यथा अणु
		group = kzalloc(माप(*group), GFP_KERNEL);
		अगर (!group) अणु
			ret = -ENOMEM;
			जाओ err_group;
		पूर्ण

		ret = rvin_group_init(group, vin);
		अगर (ret) अणु
			kमुक्त(group);
			vin_err(vin, "Failed to initialize group\n");
			जाओ err_group;
		पूर्ण

		kref_init(&group->refcount);

		rvin_group_data = group;
	पूर्ण
	mutex_unlock(&rvin_group_lock);

	/* Add VIN to group */
	mutex_lock(&group->lock);

	अगर (group->vin[id]) अणु
		vin_err(vin, "Duplicate renesas,id property value %u\n", id);
		mutex_unlock(&group->lock);
		kref_put(&group->refcount, rvin_group_release);
		वापस -EINVAL;
	पूर्ण

	group->vin[id] = vin;

	vin->id = id;
	vin->group = group;
	vin->v4l2_dev.mdev = &group->mdev;

	mutex_unlock(&group->lock);

	वापस 0;
err_group:
	mutex_unlock(&rvin_group_lock);
	वापस ret;
पूर्ण

अटल व्योम rvin_group_put(काष्ठा rvin_dev *vin)
अणु
	काष्ठा rvin_group *group = vin->group;

	mutex_lock(&group->lock);

	vin->group = शून्य;
	vin->v4l2_dev.mdev = शून्य;

	अगर (WARN_ON(group->vin[vin->id] != vin))
		जाओ out;

	group->vin[vin->id] = शून्य;
out:
	mutex_unlock(&group->lock);

	kref_put(&group->refcount, rvin_group_release);
पूर्ण

/* -----------------------------------------------------------------------------
 * Controls
 */

अटल पूर्णांक rvin_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा rvin_dev *vin =
		container_of(ctrl->handler, काष्ठा rvin_dev, ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ALPHA_COMPONENT:
		rvin_set_alpha(vin, ctrl->val);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops rvin_ctrl_ops = अणु
	.s_ctrl = rvin_s_ctrl,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Async notअगरier
 */

अटल पूर्णांक rvin_find_pad(काष्ठा v4l2_subdev *sd, पूर्णांक direction)
अणु
	अचिन्हित पूर्णांक pad;

	अगर (sd->entity.num_pads <= 1)
		वापस 0;

	क्रम (pad = 0; pad < sd->entity.num_pads; pad++)
		अगर (sd->entity.pads[pad].flags & direction)
			वापस pad;

	वापस -EINVAL;
पूर्ण

/* -----------------------------------------------------------------------------
 * Parallel async notअगरier
 */

/* The vin lock should be held when calling the subdevice attach and detach */
अटल पूर्णांक rvin_parallel_subdevice_attach(काष्ठा rvin_dev *vin,
					  काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा v4l2_subdev_mbus_code_क्रमागत code = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	/* Find source and sink pad of remote subdevice */
	ret = rvin_find_pad(subdev, MEDIA_PAD_FL_SOURCE);
	अगर (ret < 0)
		वापस ret;
	vin->parallel.source_pad = ret;

	ret = rvin_find_pad(subdev, MEDIA_PAD_FL_SINK);
	vin->parallel.sink_pad = ret < 0 ? 0 : ret;

	अगर (vin->info->use_mc) अणु
		vin->parallel.subdev = subdev;
		वापस 0;
	पूर्ण

	/* Find compatible subdevices mbus क्रमmat */
	vin->mbus_code = 0;
	code.index = 0;
	code.pad = vin->parallel.source_pad;
	जबतक (!vin->mbus_code &&
	       !v4l2_subdev_call(subdev, pad, क्रमागत_mbus_code, शून्य, &code)) अणु
		code.index++;
		चयन (code.code) अणु
		हाल MEDIA_BUS_FMT_YUYV8_1X16:
		हाल MEDIA_BUS_FMT_UYVY8_1X16:
		हाल MEDIA_BUS_FMT_UYVY8_2X8:
		हाल MEDIA_BUS_FMT_UYVY10_2X10:
		हाल MEDIA_BUS_FMT_RGB888_1X24:
			vin->mbus_code = code.code;
			vin_dbg(vin, "Found media bus format for %s: %d\n",
				subdev->name, vin->mbus_code);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!vin->mbus_code) अणु
		vin_err(vin, "Unsupported media bus format for %s\n",
			subdev->name);
		वापस -EINVAL;
	पूर्ण

	/* Read tvnorms */
	ret = v4l2_subdev_call(subdev, video, g_tvnorms, &vin->vdev.tvnorms);
	अगर (ret < 0 && ret != -ENOIOCTLCMD && ret != -ENODEV)
		वापस ret;

	/* Read standard */
	vin->std = V4L2_STD_UNKNOWN;
	ret = v4l2_subdev_call(subdev, video, g_std, &vin->std);
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		वापस ret;

	/* Add the controls */
	ret = v4l2_ctrl_handler_init(&vin->ctrl_handler, 16);
	अगर (ret < 0)
		वापस ret;

	v4l2_ctrl_new_std(&vin->ctrl_handler, &rvin_ctrl_ops,
			  V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 255);

	अगर (vin->ctrl_handler.error) अणु
		ret = vin->ctrl_handler.error;
		v4l2_ctrl_handler_मुक्त(&vin->ctrl_handler);
		वापस ret;
	पूर्ण

	ret = v4l2_ctrl_add_handler(&vin->ctrl_handler, subdev->ctrl_handler,
				    शून्य, true);
	अगर (ret < 0) अणु
		v4l2_ctrl_handler_मुक्त(&vin->ctrl_handler);
		वापस ret;
	पूर्ण

	vin->vdev.ctrl_handler = &vin->ctrl_handler;

	vin->parallel.subdev = subdev;

	वापस 0;
पूर्ण

अटल व्योम rvin_parallel_subdevice_detach(काष्ठा rvin_dev *vin)
अणु
	rvin_v4l2_unरेजिस्टर(vin);
	vin->parallel.subdev = शून्य;

	अगर (!vin->info->use_mc) अणु
		v4l2_ctrl_handler_मुक्त(&vin->ctrl_handler);
		vin->vdev.ctrl_handler = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक rvin_parallel_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा rvin_dev *vin = v4l2_dev_to_vin(notअगरier->v4l2_dev);
	काष्ठा media_entity *source;
	काष्ठा media_entity *sink;
	पूर्णांक ret;

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&vin->v4l2_dev);
	अगर (ret < 0) अणु
		vin_err(vin, "Failed to register subdev nodes\n");
		वापस ret;
	पूर्ण

	अगर (!video_is_रेजिस्टरed(&vin->vdev)) अणु
		ret = rvin_v4l2_रेजिस्टर(vin);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (!vin->info->use_mc)
		वापस 0;

	/* If we're running with media-controller, link the subdevs. */
	source = &vin->parallel.subdev->entity;
	sink = &vin->vdev.entity;

	ret = media_create_pad_link(source, vin->parallel.source_pad,
				    sink, vin->parallel.sink_pad, 0);
	अगर (ret)
		vin_err(vin, "Error adding link from %s to %s: %d\n",
			source->name, sink->name, ret);

	वापस ret;
पूर्ण

अटल व्योम rvin_parallel_notअगरy_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
					काष्ठा v4l2_subdev *subdev,
					काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा rvin_dev *vin = v4l2_dev_to_vin(notअगरier->v4l2_dev);

	vin_dbg(vin, "unbind parallel subdev %s\n", subdev->name);

	mutex_lock(&vin->lock);
	rvin_parallel_subdevice_detach(vin);
	mutex_unlock(&vin->lock);
पूर्ण

अटल पूर्णांक rvin_parallel_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				      काष्ठा v4l2_subdev *subdev,
				      काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा rvin_dev *vin = v4l2_dev_to_vin(notअगरier->v4l2_dev);
	पूर्णांक ret;

	mutex_lock(&vin->lock);
	ret = rvin_parallel_subdevice_attach(vin, subdev);
	mutex_unlock(&vin->lock);
	अगर (ret)
		वापस ret;

	v4l2_set_subdev_hostdata(subdev, vin);

	vin_dbg(vin, "bound subdev %s source pad: %u sink pad: %u\n",
		subdev->name, vin->parallel.source_pad,
		vin->parallel.sink_pad);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations rvin_parallel_notअगरy_ops = अणु
	.bound = rvin_parallel_notअगरy_bound,
	.unbind = rvin_parallel_notअगरy_unbind,
	.complete = rvin_parallel_notअगरy_complete,
पूर्ण;

अटल पूर्णांक rvin_parallel_parse_of(काष्ठा rvin_dev *vin)
अणु
	काष्ठा fwnode_handle *ep, *fwnode;
	काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
		.bus_type = V4L2_MBUS_UNKNOWN,
	पूर्ण;
	काष्ठा v4l2_async_subdev *asd;
	पूर्णांक ret;

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(vin->dev), 0, 0, 0);
	अगर (!ep)
		वापस 0;

	fwnode = fwnode_graph_get_remote_endpoपूर्णांक(ep);
	ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);
	fwnode_handle_put(ep);
	अगर (ret) अणु
		vin_err(vin, "Failed to parse %pOF\n", to_of_node(fwnode));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (vep.bus_type) अणु
	हाल V4L2_MBUS_PARALLEL:
	हाल V4L2_MBUS_BT656:
		vin_dbg(vin, "Found %s media bus\n",
			vep.bus_type == V4L2_MBUS_PARALLEL ?
			"PARALLEL" : "BT656");
		vin->parallel.mbus_type = vep.bus_type;
		vin->parallel.bus = vep.bus.parallel;
		अवरोध;
	शेष:
		vin_err(vin, "Unknown media bus type\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	asd = v4l2_async_notअगरier_add_fwnode_subdev(&vin->notअगरier, fwnode,
						    काष्ठा v4l2_async_subdev);
	अगर (IS_ERR(asd)) अणु
		ret = PTR_ERR(asd);
		जाओ out;
	पूर्ण

	vin->parallel.asd = asd;

	vin_dbg(vin, "Add parallel OF device %pOF\n", to_of_node(fwnode));
out:
	fwnode_handle_put(fwnode);

	वापस ret;
पूर्ण

अटल पूर्णांक rvin_parallel_init(काष्ठा rvin_dev *vin)
अणु
	पूर्णांक ret;

	v4l2_async_notअगरier_init(&vin->notअगरier);

	ret = rvin_parallel_parse_of(vin);
	अगर (ret)
		वापस ret;

	/* If using mc, it's fine not to have any input रेजिस्टरed. */
	अगर (!vin->parallel.asd)
		वापस vin->info->use_mc ? 0 : -ENODEV;

	vin_dbg(vin, "Found parallel subdevice %pOF\n",
		to_of_node(vin->parallel.asd->match.fwnode));

	vin->notअगरier.ops = &rvin_parallel_notअगरy_ops;
	ret = v4l2_async_notअगरier_रेजिस्टर(&vin->v4l2_dev, &vin->notअगरier);
	अगर (ret < 0) अणु
		vin_err(vin, "Notifier registration failed\n");
		v4l2_async_notअगरier_cleanup(&vin->notअगरier);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Group async notअगरier
 */

अटल पूर्णांक rvin_group_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा rvin_dev *vin = v4l2_dev_to_vin(notअगरier->v4l2_dev);
	स्थिर काष्ठा rvin_group_route *route;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = media_device_रेजिस्टर(&vin->group->mdev);
	अगर (ret)
		वापस ret;

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&vin->v4l2_dev);
	अगर (ret) अणु
		vin_err(vin, "Failed to register subdev nodes\n");
		वापस ret;
	पूर्ण

	/* Register all video nodes क्रम the group. */
	क्रम (i = 0; i < RCAR_VIN_NUM; i++) अणु
		अगर (vin->group->vin[i] &&
		    !video_is_रेजिस्टरed(&vin->group->vin[i]->vdev)) अणु
			ret = rvin_v4l2_रेजिस्टर(vin->group->vin[i]);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Create all media device links between VINs and CSI-2's. */
	mutex_lock(&vin->group->lock);
	क्रम (route = vin->info->routes; route->mask; route++) अणु
		काष्ठा media_pad *source_pad, *sink_pad;
		काष्ठा media_entity *source, *sink;
		अचिन्हित पूर्णांक source_idx;

		/* Check that VIN is part of the group. */
		अगर (!vin->group->vin[route->vin])
			जारी;

		/* Check that VIN' master is part of the group. */
		अगर (!vin->group->vin[rvin_group_id_to_master(route->vin)])
			जारी;

		/* Check that CSI-2 is part of the group. */
		अगर (!vin->group->csi[route->csi].subdev)
			जारी;

		source = &vin->group->csi[route->csi].subdev->entity;
		source_idx = rvin_group_csi_channel_to_pad(route->channel);
		source_pad = &source->pads[source_idx];

		sink = &vin->group->vin[route->vin]->vdev.entity;
		sink_pad = &sink->pads[0];

		/* Skip अगर link alपढ़ोy exists. */
		अगर (media_entity_find_link(source_pad, sink_pad))
			जारी;

		ret = media_create_pad_link(source, source_idx, sink, 0, 0);
		अगर (ret) अणु
			vin_err(vin, "Error adding link from %s to %s\n",
				source->name, sink->name);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&vin->group->lock);

	वापस ret;
पूर्ण

अटल व्योम rvin_group_notअगरy_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
				     काष्ठा v4l2_subdev *subdev,
				     काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा rvin_dev *vin = v4l2_dev_to_vin(notअगरier->v4l2_dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < RCAR_VIN_NUM; i++)
		अगर (vin->group->vin[i])
			rvin_v4l2_unरेजिस्टर(vin->group->vin[i]);

	mutex_lock(&vin->group->lock);

	क्रम (i = 0; i < RVIN_CSI_MAX; i++) अणु
		अगर (vin->group->csi[i].asd != asd)
			जारी;
		vin->group->csi[i].subdev = शून्य;
		vin_dbg(vin, "Unbind CSI-2 %s from slot %u\n", subdev->name, i);
		अवरोध;
	पूर्ण

	mutex_unlock(&vin->group->lock);

	media_device_unरेजिस्टर(&vin->group->mdev);
पूर्ण

अटल पूर्णांक rvin_group_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				   काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा rvin_dev *vin = v4l2_dev_to_vin(notअगरier->v4l2_dev);
	अचिन्हित पूर्णांक i;

	mutex_lock(&vin->group->lock);

	क्रम (i = 0; i < RVIN_CSI_MAX; i++) अणु
		अगर (vin->group->csi[i].asd != asd)
			जारी;
		vin->group->csi[i].subdev = subdev;
		vin_dbg(vin, "Bound CSI-2 %s to slot %u\n", subdev->name, i);
		अवरोध;
	पूर्ण

	mutex_unlock(&vin->group->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations rvin_group_notअगरy_ops = अणु
	.bound = rvin_group_notअगरy_bound,
	.unbind = rvin_group_notअगरy_unbind,
	.complete = rvin_group_notअगरy_complete,
पूर्ण;

अटल पूर्णांक rvin_mc_parse_of(काष्ठा rvin_dev *vin, अचिन्हित पूर्णांक id)
अणु
	काष्ठा fwnode_handle *ep, *fwnode;
	काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY,
	पूर्ण;
	काष्ठा v4l2_async_subdev *asd;
	पूर्णांक ret;

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(vin->dev), 1, id, 0);
	अगर (!ep)
		वापस 0;

	fwnode = fwnode_graph_get_remote_endpoपूर्णांक(ep);
	ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);
	fwnode_handle_put(ep);
	अगर (ret) अणु
		vin_err(vin, "Failed to parse %pOF\n", to_of_node(fwnode));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!of_device_is_available(to_of_node(fwnode))) अणु
		vin_dbg(vin, "OF device %pOF disabled, ignoring\n",
			to_of_node(fwnode));
		ret = -ENOTCONN;
		जाओ out;
	पूर्ण

	asd = v4l2_async_notअगरier_add_fwnode_subdev(&vin->group->notअगरier,
						    fwnode,
						    काष्ठा v4l2_async_subdev);
	अगर (IS_ERR(asd)) अणु
		ret = PTR_ERR(asd);
		जाओ out;
	पूर्ण

	vin->group->csi[vep.base.id].asd = asd;

	vin_dbg(vin, "Add group OF device %pOF to slot %u\n",
		to_of_node(fwnode), vep.base.id);
out:
	fwnode_handle_put(fwnode);

	वापस ret;
पूर्ण

अटल पूर्णांक rvin_mc_parse_of_graph(काष्ठा rvin_dev *vin)
अणु
	अचिन्हित पूर्णांक count = 0, vin_mask = 0;
	अचिन्हित पूर्णांक i, id;
	पूर्णांक ret;

	mutex_lock(&vin->group->lock);

	/* If not all VIN's are registered don't रेजिस्टर the notअगरier. */
	क्रम (i = 0; i < RCAR_VIN_NUM; i++) अणु
		अगर (vin->group->vin[i]) अणु
			count++;
			vin_mask |= BIT(i);
		पूर्ण
	पूर्ण

	अगर (vin->group->count != count) अणु
		mutex_unlock(&vin->group->lock);
		वापस 0;
	पूर्ण

	mutex_unlock(&vin->group->lock);

	v4l2_async_notअगरier_init(&vin->group->notअगरier);

	/*
	 * Have all VIN's look क्रम CSI-2 subdevices. Some subdevices will
	 * overlap but the parser function can handle it, so each subdevice
	 * will only be रेजिस्टरed once with the group notअगरier.
	 */
	क्रम (i = 0; i < RCAR_VIN_NUM; i++) अणु
		अगर (!(vin_mask & BIT(i)))
			जारी;

		क्रम (id = 0; id < RVIN_CSI_MAX; id++) अणु
			अगर (vin->group->csi[id].asd)
				जारी;

			ret = rvin_mc_parse_of(vin->group->vin[i], id);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (list_empty(&vin->group->notअगरier.asd_list))
		वापस 0;

	vin->group->notअगरier.ops = &rvin_group_notअगरy_ops;
	ret = v4l2_async_notअगरier_रेजिस्टर(&vin->v4l2_dev,
					   &vin->group->notअगरier);
	अगर (ret < 0) अणु
		vin_err(vin, "Notifier registration failed\n");
		v4l2_async_notअगरier_cleanup(&vin->group->notअगरier);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_mc_init(काष्ठा rvin_dev *vin)
अणु
	पूर्णांक ret;

	vin->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vin->vdev.entity, 1, &vin->pad);
	अगर (ret)
		वापस ret;

	ret = rvin_group_get(vin);
	अगर (ret)
		वापस ret;

	ret = rvin_mc_parse_of_graph(vin);
	अगर (ret)
		rvin_group_put(vin);

	ret = v4l2_ctrl_handler_init(&vin->ctrl_handler, 1);
	अगर (ret < 0)
		वापस ret;

	v4l2_ctrl_new_std(&vin->ctrl_handler, &rvin_ctrl_ops,
			  V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 255);

	अगर (vin->ctrl_handler.error) अणु
		ret = vin->ctrl_handler.error;
		v4l2_ctrl_handler_मुक्त(&vin->ctrl_handler);
		वापस ret;
	पूर्ण

	vin->vdev.ctrl_handler = &vin->ctrl_handler;

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Suspend / Resume
 */

अटल पूर्णांक __maybe_unused rvin_suspend(काष्ठा device *dev)
अणु
	काष्ठा rvin_dev *vin = dev_get_drvdata(dev);

	अगर (vin->state != RUNNING)
		वापस 0;

	rvin_stop_streaming(vin);

	vin->state = SUSPENDED;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rvin_resume(काष्ठा device *dev)
अणु
	काष्ठा rvin_dev *vin = dev_get_drvdata(dev);

	अगर (vin->state != SUSPENDED)
		वापस 0;

	/*
	 * Restore group master CHSEL setting.
	 *
	 * This needs to be करोne by every VIN resuming not only the master
	 * as we करोn't know अगर and in which order the master VINs will
	 * be resumed.
	 */
	अगर (vin->info->use_mc) अणु
		अचिन्हित पूर्णांक master_id = rvin_group_id_to_master(vin->id);
		काष्ठा rvin_dev *master = vin->group->vin[master_id];
		पूर्णांक ret;

		अगर (WARN_ON(!master))
			वापस -ENODEV;

		ret = rvin_set_channel_routing(master, master->chsel);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस rvin_start_streaming(vin);
पूर्ण

/* -----------------------------------------------------------------------------
 * Platक्रमm Device Driver
 */

अटल स्थिर काष्ठा rvin_info rcar_info_h1 = अणु
	.model = RCAR_H1,
	.use_mc = false,
	.max_width = 2048,
	.max_height = 2048,
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_m1 = अणु
	.model = RCAR_M1,
	.use_mc = false,
	.max_width = 2048,
	.max_height = 2048,
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_gen2 = अणु
	.model = RCAR_GEN2,
	.use_mc = false,
	.max_width = 2048,
	.max_height = 2048,
पूर्ण;

अटल स्थिर काष्ठा rvin_group_route rcar_info_r8a774e1_routes[] = अणु
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 0, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 0, .mask = BIT(1) | BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 0, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 1, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 1, .mask = BIT(1) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 1, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 1, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 2, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 2, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 2, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 2, .vin = 2, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 2, .vin = 2, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 3, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 3, .mask = BIT(1) | BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 3, .vin = 3, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 3, .vin = 3, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 4, .mask = BIT(1) | BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 5, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 5, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 6, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 6, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 2, .vin = 6, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 7, .mask = BIT(1) | BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 3, .vin = 7, .mask = BIT(4) पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_r8a774e1 = अणु
	.model = RCAR_GEN3,
	.use_mc = true,
	.max_width = 4096,
	.max_height = 4096,
	.routes = rcar_info_r8a774e1_routes,
पूर्ण;

अटल स्थिर काष्ठा rvin_group_route rcar_info_r8a7795_routes[] = अणु
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 0, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 0, .mask = BIT(1) | BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 0, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 1, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 1, .mask = BIT(1) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 1, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 1, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 2, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 2, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 2, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 2, .vin = 2, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 2, .vin = 2, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 3, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 3, .mask = BIT(1) | BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 3, .vin = 3, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 3, .vin = 3, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 0, .vin = 4, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 4, .mask = BIT(1) | BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 1, .vin = 4, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 5, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 1, .vin = 5, .mask = BIT(1) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 0, .vin = 5, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 5, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 6, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 0, .vin = 6, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 6, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 2, .vin = 6, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 2, .vin = 6, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 1, .vin = 7, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 7, .mask = BIT(1) | BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 3, .vin = 7, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 3, .vin = 7, .mask = BIT(4) पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_r8a7795 = अणु
	.model = RCAR_GEN3,
	.use_mc = true,
	.nv12 = true,
	.max_width = 4096,
	.max_height = 4096,
	.routes = rcar_info_r8a7795_routes,
पूर्ण;

अटल स्थिर काष्ठा rvin_group_route rcar_info_r8a7795es1_routes[] = अणु
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 0, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 0, .mask = BIT(1) | BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 0, .vin = 0, .mask = BIT(2) | BIT(5) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 1, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 0, .vin = 1, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 1, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 1, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 1, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 1, .vin = 1, .mask = BIT(5) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 0, .vin = 2, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 2, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 2, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 2, .vin = 2, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 2, .vin = 2, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 2, .vin = 2, .mask = BIT(5) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 3, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 3, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 1, .vin = 3, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 3, .vin = 3, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 3, .vin = 3, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 3, .vin = 3, .mask = BIT(5) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 0, .vin = 4, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 4, .mask = BIT(1) | BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 0, .vin = 4, .mask = BIT(2) | BIT(5) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 5, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 0, .vin = 5, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 0, .vin = 5, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 1, .vin = 5, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 5, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 1, .vin = 5, .mask = BIT(5) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 0, .vin = 6, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 0, .vin = 6, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 6, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 2, .vin = 6, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 2, .vin = 6, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 2, .vin = 6, .mask = BIT(5) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 1, .vin = 7, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 7, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 1, .vin = 7, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 3, .vin = 7, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 3, .vin = 7, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI21, .channel = 3, .vin = 7, .mask = BIT(5) पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_r8a7795es1 = अणु
	.model = RCAR_GEN3,
	.use_mc = true,
	.max_width = 4096,
	.max_height = 4096,
	.routes = rcar_info_r8a7795es1_routes,
पूर्ण;

अटल स्थिर काष्ठा rvin_group_route rcar_info_r8a7796_routes[] = अणु
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 0, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 0, .mask = BIT(1) | BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 1, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 1, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 1, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 1, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 2, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 2, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 2, .vin = 2, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 2, .vin = 2, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 3, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 3, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 3, .vin = 3, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 3, .vin = 3, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 4, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 4, .mask = BIT(1) | BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 5, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 5, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 5, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 5, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 6, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 6, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 2, .vin = 6, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 2, .vin = 6, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 7, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 7, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 3, .vin = 7, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 3, .vin = 7, .mask = BIT(4) पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_r8a7796 = अणु
	.model = RCAR_GEN3,
	.use_mc = true,
	.nv12 = true,
	.max_width = 4096,
	.max_height = 4096,
	.routes = rcar_info_r8a7796_routes,
पूर्ण;

अटल स्थिर काष्ठा rvin_group_route rcar_info_r8a77965_routes[] = अणु
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 0, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 0, .mask = BIT(1) | BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 0, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 1, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 1, .mask = BIT(1) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 1, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 1, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 2, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 2, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 2, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 2, .vin = 2, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 2, .vin = 2, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 3, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 3, .mask = BIT(1) | BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 3, .vin = 3, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 3, .vin = 3, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 4, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 4, .mask = BIT(1) | BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 4, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 5, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 5, .mask = BIT(1) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 5, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 5, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 6, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 6, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 0, .vin = 6, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 2, .vin = 6, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 2, .vin = 6, .mask = BIT(4) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 7, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 1, .vin = 7, .mask = BIT(1) | BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 3, .vin = 7, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI20, .channel = 3, .vin = 7, .mask = BIT(4) पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_r8a77965 = अणु
	.model = RCAR_GEN3,
	.use_mc = true,
	.nv12 = true,
	.max_width = 4096,
	.max_height = 4096,
	.routes = rcar_info_r8a77965_routes,
पूर्ण;

अटल स्थिर काष्ठा rvin_group_route rcar_info_r8a77970_routes[] = अणु
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 0, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 1, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 1, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 2, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 2, .vin = 2, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 3, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 3, .vin = 3, .mask = BIT(3) पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_r8a77970 = अणु
	.model = RCAR_GEN3,
	.use_mc = true,
	.max_width = 4096,
	.max_height = 4096,
	.routes = rcar_info_r8a77970_routes,
पूर्ण;

अटल स्थिर काष्ठा rvin_group_route rcar_info_r8a77980_routes[] = अणु
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 0, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 0, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 1, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 1, .mask = BIT(1) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 2, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 2, .vin = 2, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 3, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 3, .vin = 3, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 0, .vin = 4, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 1, .vin = 4, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 0, .vin = 5, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 1, .vin = 5, .mask = BIT(1) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 0, .vin = 6, .mask = BIT(1) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 2, .vin = 6, .mask = BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 1, .vin = 7, .mask = BIT(0) पूर्ण,
	अणु .csi = RVIN_CSI41, .channel = 3, .vin = 7, .mask = BIT(3) पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_r8a77980 = अणु
	.model = RCAR_GEN3,
	.use_mc = true,
	.nv12 = true,
	.max_width = 4096,
	.max_height = 4096,
	.routes = rcar_info_r8a77980_routes,
पूर्ण;

अटल स्थिर काष्ठा rvin_group_route rcar_info_r8a77990_routes[] = अणु
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 4, .mask = BIT(0) | BIT(3) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 0, .vin = 5, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 4, .mask = BIT(2) पूर्ण,
	अणु .csi = RVIN_CSI40, .channel = 1, .vin = 5, .mask = BIT(1) | BIT(3) पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_r8a77990 = अणु
	.model = RCAR_GEN3,
	.use_mc = true,
	.nv12 = true,
	.max_width = 4096,
	.max_height = 4096,
	.routes = rcar_info_r8a77990_routes,
पूर्ण;

अटल स्थिर काष्ठा rvin_group_route rcar_info_r8a77995_routes[] = अणु
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rvin_info rcar_info_r8a77995 = अणु
	.model = RCAR_GEN3,
	.use_mc = true,
	.nv12 = true,
	.max_width = 4096,
	.max_height = 4096,
	.routes = rcar_info_r8a77995_routes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rvin_of_id_table[] = अणु
	अणु
		.compatible = "renesas,vin-r8a774a1",
		.data = &rcar_info_r8a7796,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a774b1",
		.data = &rcar_info_r8a77965,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a774c0",
		.data = &rcar_info_r8a77990,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a774e1",
		.data = &rcar_info_r8a774e1,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a7778",
		.data = &rcar_info_m1,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a7779",
		.data = &rcar_info_h1,
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen2-vin",
		.data = &rcar_info_gen2,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a7795",
		.data = &rcar_info_r8a7795,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a7796",
		.data = &rcar_info_r8a7796,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a77965",
		.data = &rcar_info_r8a77965,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a77970",
		.data = &rcar_info_r8a77970,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a77980",
		.data = &rcar_info_r8a77980,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a77990",
		.data = &rcar_info_r8a77990,
	पूर्ण,
	अणु
		.compatible = "renesas,vin-r8a77995",
		.data = &rcar_info_r8a77995,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rvin_of_id_table);

अटल स्थिर काष्ठा soc_device_attribute r8a7795es1[] = अणु
	अणु
		.soc_id = "r8a7795", .revision = "ES1.*",
		.data = &rcar_info_r8a7795es1,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक rcar_vin_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा soc_device_attribute *attr;
	काष्ठा rvin_dev *vin;
	पूर्णांक irq, ret;

	vin = devm_kzalloc(&pdev->dev, माप(*vin), GFP_KERNEL);
	अगर (!vin)
		वापस -ENOMEM;

	vin->dev = &pdev->dev;
	vin->info = of_device_get_match_data(&pdev->dev);
	vin->alpha = 0xff;

	/*
	 * Special care is needed on r8a7795 ES1.x since it
	 * uses dअगरferent routing than r8a7795 ES2.0.
	 */
	attr = soc_device_match(r8a7795es1);
	अगर (attr)
		vin->info = attr->data;

	vin->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(vin->base))
		वापस PTR_ERR(vin->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = rvin_dma_रेजिस्टर(vin, irq);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, vin);

	अगर (vin->info->use_mc) अणु
		ret = rvin_mc_init(vin);
		अगर (ret)
			जाओ error_dma_unरेजिस्टर;
	पूर्ण

	ret = rvin_parallel_init(vin);
	अगर (ret)
		जाओ error_group_unरेजिस्टर;

	pm_suspend_ignore_children(&pdev->dev, true);
	pm_runसमय_enable(&pdev->dev);

	वापस 0;

error_group_unरेजिस्टर:
	v4l2_ctrl_handler_मुक्त(&vin->ctrl_handler);

	अगर (vin->info->use_mc) अणु
		mutex_lock(&vin->group->lock);
		अगर (&vin->v4l2_dev == vin->group->notअगरier.v4l2_dev) अणु
			v4l2_async_notअगरier_unरेजिस्टर(&vin->group->notअगरier);
			v4l2_async_notअगरier_cleanup(&vin->group->notअगरier);
		पूर्ण
		mutex_unlock(&vin->group->lock);
		rvin_group_put(vin);
	पूर्ण

error_dma_unरेजिस्टर:
	rvin_dma_unरेजिस्टर(vin);

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_vin_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rvin_dev *vin = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);

	rvin_v4l2_unरेजिस्टर(vin);

	v4l2_async_notअगरier_unरेजिस्टर(&vin->notअगरier);
	v4l2_async_notअगरier_cleanup(&vin->notअगरier);

	अगर (vin->info->use_mc) अणु
		v4l2_async_notअगरier_unरेजिस्टर(&vin->group->notअगरier);
		v4l2_async_notअगरier_cleanup(&vin->group->notअगरier);
		rvin_group_put(vin);
	पूर्ण

	v4l2_ctrl_handler_मुक्त(&vin->ctrl_handler);

	rvin_dma_unरेजिस्टर(vin);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rvin_pm_ops, rvin_suspend, rvin_resume);

अटल काष्ठा platक्रमm_driver rcar_vin_driver = अणु
	.driver = अणु
		.name = "rcar-vin",
		.pm = &rvin_pm_ops,
		.of_match_table = rvin_of_id_table,
	पूर्ण,
	.probe = rcar_vin_probe,
	.हटाओ = rcar_vin_हटाओ,
पूर्ण;

module_platक्रमm_driver(rcar_vin_driver);

MODULE_AUTHOR("Niklas Sथघderlund <niklas.soderlund@ragnatech.se>");
MODULE_DESCRIPTION("Renesas R-Car VIN camera host driver");
MODULE_LICENSE("GPL");
