<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx Video IP Composite Device
 *
 * Copyright (C) 2013-2015 Ideas on Board
 * Copyright (C) 2013-2015 Xilinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xilinx.com>
 *           Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>

#समावेश "xilinx-dma.h"
#समावेश "xilinx-vipp.h"

#घोषणा XVIPP_DMA_S2MM				0
#घोषणा XVIPP_DMA_MM2S				1

/**
 * काष्ठा xvip_graph_entity - Entity in the video graph
 * @asd: subdev asynchronous registration inक्रमmation
 * @entity: media entity, from the corresponding V4L2 subdev
 * @subdev: V4L2 subdev
 */
काष्ठा xvip_graph_entity अणु
	काष्ठा v4l2_async_subdev asd; /* must be first */
	काष्ठा media_entity *entity;
	काष्ठा v4l2_subdev *subdev;
पूर्ण;

अटल अंतरभूत काष्ठा xvip_graph_entity *
to_xvip_entity(काष्ठा v4l2_async_subdev *asd)
अणु
	वापस container_of(asd, काष्ठा xvip_graph_entity, asd);
पूर्ण

/* -----------------------------------------------------------------------------
 * Graph Management
 */

अटल काष्ठा xvip_graph_entity *
xvip_graph_find_entity(काष्ठा xvip_composite_device *xdev,
		       स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा xvip_graph_entity *entity;
	काष्ठा v4l2_async_subdev *asd;

	list_क्रम_each_entry(asd, &xdev->notअगरier.asd_list, asd_list) अणु
		entity = to_xvip_entity(asd);
		अगर (entity->asd.match.fwnode == fwnode)
			वापस entity;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक xvip_graph_build_one(काष्ठा xvip_composite_device *xdev,
				काष्ठा xvip_graph_entity *entity)
अणु
	u32 link_flags = MEDIA_LNK_FL_ENABLED;
	काष्ठा media_entity *local = entity->entity;
	काष्ठा media_entity *remote;
	काष्ठा media_pad *local_pad;
	काष्ठा media_pad *remote_pad;
	काष्ठा xvip_graph_entity *ent;
	काष्ठा v4l2_fwnode_link link;
	काष्ठा fwnode_handle *ep = शून्य;
	पूर्णांक ret = 0;

	dev_dbg(xdev->dev, "creating links for entity %s\n", local->name);

	जबतक (1) अणु
		/* Get the next endpoपूर्णांक and parse its link. */
		ep = fwnode_graph_get_next_endpoपूर्णांक(entity->asd.match.fwnode,
						    ep);
		अगर (ep == शून्य)
			अवरोध;

		dev_dbg(xdev->dev, "processing endpoint %p\n", ep);

		ret = v4l2_fwnode_parse_link(ep, &link);
		अगर (ret < 0) अणु
			dev_err(xdev->dev, "failed to parse link for %p\n",
				ep);
			जारी;
		पूर्ण

		/* Skip sink ports, they will be processed from the other end of
		 * the link.
		 */
		अगर (link.local_port >= local->num_pads) अणु
			dev_err(xdev->dev, "invalid port number %u for %p\n",
				link.local_port, link.local_node);
			v4l2_fwnode_put_link(&link);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		local_pad = &local->pads[link.local_port];

		अगर (local_pad->flags & MEDIA_PAD_FL_SINK) अणु
			dev_dbg(xdev->dev, "skipping sink port %p:%u\n",
				link.local_node, link.local_port);
			v4l2_fwnode_put_link(&link);
			जारी;
		पूर्ण

		/* Skip DMA engines, they will be processed separately. */
		अगर (link.remote_node == of_fwnode_handle(xdev->dev->of_node)) अणु
			dev_dbg(xdev->dev, "skipping DMA port %p:%u\n",
				link.local_node, link.local_port);
			v4l2_fwnode_put_link(&link);
			जारी;
		पूर्ण

		/* Find the remote entity. */
		ent = xvip_graph_find_entity(xdev, link.remote_node);
		अगर (ent == शून्य) अणु
			dev_err(xdev->dev, "no entity found for %p\n",
				link.remote_node);
			v4l2_fwnode_put_link(&link);
			ret = -ENODEV;
			अवरोध;
		पूर्ण

		remote = ent->entity;

		अगर (link.remote_port >= remote->num_pads) अणु
			dev_err(xdev->dev, "invalid port number %u on %p\n",
				link.remote_port, link.remote_node);
			v4l2_fwnode_put_link(&link);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		remote_pad = &remote->pads[link.remote_port];

		v4l2_fwnode_put_link(&link);

		/* Create the media link. */
		dev_dbg(xdev->dev, "creating %s:%u -> %s:%u link\n",
			local->name, local_pad->index,
			remote->name, remote_pad->index);

		ret = media_create_pad_link(local, local_pad->index,
					       remote, remote_pad->index,
					       link_flags);
		अगर (ret < 0) अणु
			dev_err(xdev->dev,
				"failed to create %s:%u -> %s:%u link\n",
				local->name, local_pad->index,
				remote->name, remote_pad->index);
			अवरोध;
		पूर्ण
	पूर्ण

	fwnode_handle_put(ep);
	वापस ret;
पूर्ण

अटल काष्ठा xvip_dma *
xvip_graph_find_dma(काष्ठा xvip_composite_device *xdev, अचिन्हित पूर्णांक port)
अणु
	काष्ठा xvip_dma *dma;

	list_क्रम_each_entry(dma, &xdev->dmas, list) अणु
		अगर (dma->port == port)
			वापस dma;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक xvip_graph_build_dma(काष्ठा xvip_composite_device *xdev)
अणु
	u32 link_flags = MEDIA_LNK_FL_ENABLED;
	काष्ठा device_node *node = xdev->dev->of_node;
	काष्ठा media_entity *source;
	काष्ठा media_entity *sink;
	काष्ठा media_pad *source_pad;
	काष्ठा media_pad *sink_pad;
	काष्ठा xvip_graph_entity *ent;
	काष्ठा v4l2_fwnode_link link;
	काष्ठा device_node *ep = शून्य;
	काष्ठा xvip_dma *dma;
	पूर्णांक ret = 0;

	dev_dbg(xdev->dev, "creating links for DMA engines\n");

	जबतक (1) अणु
		/* Get the next endpoपूर्णांक and parse its link. */
		ep = of_graph_get_next_endpoपूर्णांक(node, ep);
		अगर (ep == शून्य)
			अवरोध;

		dev_dbg(xdev->dev, "processing endpoint %pOF\n", ep);

		ret = v4l2_fwnode_parse_link(of_fwnode_handle(ep), &link);
		अगर (ret < 0) अणु
			dev_err(xdev->dev, "failed to parse link for %pOF\n",
				ep);
			जारी;
		पूर्ण

		/* Find the DMA engine. */
		dma = xvip_graph_find_dma(xdev, link.local_port);
		अगर (dma == शून्य) अणु
			dev_err(xdev->dev, "no DMA engine found for port %u\n",
				link.local_port);
			v4l2_fwnode_put_link(&link);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		dev_dbg(xdev->dev, "creating link for DMA engine %s\n",
			dma->video.name);

		/* Find the remote entity. */
		ent = xvip_graph_find_entity(xdev, link.remote_node);
		अगर (ent == शून्य) अणु
			dev_err(xdev->dev, "no entity found for %pOF\n",
				to_of_node(link.remote_node));
			v4l2_fwnode_put_link(&link);
			ret = -ENODEV;
			अवरोध;
		पूर्ण

		अगर (link.remote_port >= ent->entity->num_pads) अणु
			dev_err(xdev->dev, "invalid port number %u on %pOF\n",
				link.remote_port,
				to_of_node(link.remote_node));
			v4l2_fwnode_put_link(&link);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (dma->pad.flags & MEDIA_PAD_FL_SOURCE) अणु
			source = &dma->video.entity;
			source_pad = &dma->pad;
			sink = ent->entity;
			sink_pad = &sink->pads[link.remote_port];
		पूर्ण अन्यथा अणु
			source = ent->entity;
			source_pad = &source->pads[link.remote_port];
			sink = &dma->video.entity;
			sink_pad = &dma->pad;
		पूर्ण

		v4l2_fwnode_put_link(&link);

		/* Create the media link. */
		dev_dbg(xdev->dev, "creating %s:%u -> %s:%u link\n",
			source->name, source_pad->index,
			sink->name, sink_pad->index);

		ret = media_create_pad_link(source, source_pad->index,
					       sink, sink_pad->index,
					       link_flags);
		अगर (ret < 0) अणु
			dev_err(xdev->dev,
				"failed to create %s:%u -> %s:%u link\n",
				source->name, source_pad->index,
				sink->name, sink_pad->index);
			अवरोध;
		पूर्ण
	पूर्ण

	of_node_put(ep);
	वापस ret;
पूर्ण

अटल पूर्णांक xvip_graph_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा xvip_composite_device *xdev =
		container_of(notअगरier, काष्ठा xvip_composite_device, notअगरier);
	काष्ठा xvip_graph_entity *entity;
	काष्ठा v4l2_async_subdev *asd;
	पूर्णांक ret;

	dev_dbg(xdev->dev, "notify complete, all subdevs registered\n");

	/* Create links क्रम every entity. */
	list_क्रम_each_entry(asd, &xdev->notअगरier.asd_list, asd_list) अणु
		entity = to_xvip_entity(asd);
		ret = xvip_graph_build_one(xdev, entity);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Create links क्रम DMA channels. */
	ret = xvip_graph_build_dma(xdev);
	अगर (ret < 0)
		वापस ret;

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&xdev->v4l2_dev);
	अगर (ret < 0)
		dev_err(xdev->dev, "failed to register subdev nodes\n");

	वापस media_device_रेजिस्टर(&xdev->media_dev);
पूर्ण

अटल पूर्णांक xvip_graph_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				   काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_async_subdev *unused)
अणु
	काष्ठा xvip_composite_device *xdev =
		container_of(notअगरier, काष्ठा xvip_composite_device, notअगरier);
	काष्ठा xvip_graph_entity *entity;
	काष्ठा v4l2_async_subdev *asd;

	/* Locate the entity corresponding to the bound subdev and store the
	 * subdev poपूर्णांकer.
	 */
	list_क्रम_each_entry(asd, &xdev->notअगरier.asd_list, asd_list) अणु
		entity = to_xvip_entity(asd);

		अगर (entity->asd.match.fwnode != subdev->fwnode)
			जारी;

		अगर (entity->subdev) अणु
			dev_err(xdev->dev, "duplicate subdev for node %p\n",
				entity->asd.match.fwnode);
			वापस -EINVAL;
		पूर्ण

		dev_dbg(xdev->dev, "subdev %s bound\n", subdev->name);
		entity->entity = &subdev->entity;
		entity->subdev = subdev;
		वापस 0;
	पूर्ण

	dev_err(xdev->dev, "no entity for subdev %s\n", subdev->name);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations xvip_graph_notअगरy_ops = अणु
	.bound = xvip_graph_notअगरy_bound,
	.complete = xvip_graph_notअगरy_complete,
पूर्ण;

अटल पूर्णांक xvip_graph_parse_one(काष्ठा xvip_composite_device *xdev,
				काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *remote;
	काष्ठा fwnode_handle *ep = शून्य;
	पूर्णांक ret = 0;

	dev_dbg(xdev->dev, "parsing node %p\n", fwnode);

	जबतक (1) अणु
		काष्ठा xvip_graph_entity *xge;

		ep = fwnode_graph_get_next_endpoपूर्णांक(fwnode, ep);
		अगर (ep == शून्य)
			अवरोध;

		dev_dbg(xdev->dev, "handling endpoint %p\n", ep);

		remote = fwnode_graph_get_remote_port_parent(ep);
		अगर (remote == शून्य) अणु
			ret = -EINVAL;
			जाओ err_notअगरier_cleanup;
		पूर्ण

		fwnode_handle_put(ep);

		/* Skip entities that we have alपढ़ोy processed. */
		अगर (remote == of_fwnode_handle(xdev->dev->of_node) ||
		    xvip_graph_find_entity(xdev, remote)) अणु
			fwnode_handle_put(remote);
			जारी;
		पूर्ण

		xge = v4l2_async_notअगरier_add_fwnode_subdev(
			&xdev->notअगरier, remote,
			काष्ठा xvip_graph_entity);
		fwnode_handle_put(remote);
		अगर (IS_ERR(xge)) अणु
			ret = PTR_ERR(xge);
			जाओ err_notअगरier_cleanup;
		पूर्ण
	पूर्ण

	वापस 0;

err_notअगरier_cleanup:
	v4l2_async_notअगरier_cleanup(&xdev->notअगरier);
	fwnode_handle_put(ep);
	वापस ret;
पूर्ण

अटल पूर्णांक xvip_graph_parse(काष्ठा xvip_composite_device *xdev)
अणु
	काष्ठा xvip_graph_entity *entity;
	काष्ठा v4l2_async_subdev *asd;
	पूर्णांक ret;

	/*
	 * Walk the links to parse the full graph. Start by parsing the
	 * composite node and then parse entities in turn. The list_क्रम_each
	 * loop will handle entities added at the end of the list जबतक walking
	 * the links.
	 */
	ret = xvip_graph_parse_one(xdev, of_fwnode_handle(xdev->dev->of_node));
	अगर (ret < 0)
		वापस 0;

	list_क्रम_each_entry(asd, &xdev->notअगरier.asd_list, asd_list) अणु
		entity = to_xvip_entity(asd);
		ret = xvip_graph_parse_one(xdev, entity->asd.match.fwnode);
		अगर (ret < 0) अणु
			v4l2_async_notअगरier_cleanup(&xdev->notअगरier);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक xvip_graph_dma_init_one(काष्ठा xvip_composite_device *xdev,
				   काष्ठा device_node *node)
अणु
	काष्ठा xvip_dma *dma;
	क्रमागत v4l2_buf_type type;
	स्थिर अक्षर *direction;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;

	ret = of_property_पढ़ो_string(node, "direction", &direction);
	अगर (ret < 0)
		वापस ret;

	अगर (म_भेद(direction, "input") == 0)
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	अन्यथा अगर (म_भेद(direction, "output") == 0)
		type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	अन्यथा
		वापस -EINVAL;

	of_property_पढ़ो_u32(node, "reg", &index);

	dma = devm_kzalloc(xdev->dev, माप(*dma), GFP_KERNEL);
	अगर (dma == शून्य)
		वापस -ENOMEM;

	ret = xvip_dma_init(xdev, dma, type, index);
	अगर (ret < 0) अणु
		dev_err(xdev->dev, "%pOF initialization failed\n", node);
		वापस ret;
	पूर्ण

	list_add_tail(&dma->list, &xdev->dmas);

	xdev->v4l2_caps |= type == V4L2_BUF_TYPE_VIDEO_CAPTURE
			 ? V4L2_CAP_VIDEO_CAPTURE : V4L2_CAP_VIDEO_OUTPUT;

	वापस 0;
पूर्ण

अटल पूर्णांक xvip_graph_dma_init(काष्ठा xvip_composite_device *xdev)
अणु
	काष्ठा device_node *ports;
	काष्ठा device_node *port;
	पूर्णांक ret;

	ports = of_get_child_by_name(xdev->dev->of_node, "ports");
	अगर (ports == शून्य) अणु
		dev_err(xdev->dev, "ports node not present\n");
		वापस -EINVAL;
	पूर्ण

	क्रम_each_child_of_node(ports, port) अणु
		ret = xvip_graph_dma_init_one(xdev, port);
		अगर (ret < 0) अणु
			of_node_put(port);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xvip_graph_cleanup(काष्ठा xvip_composite_device *xdev)
अणु
	काष्ठा xvip_dma *dmap;
	काष्ठा xvip_dma *dma;

	v4l2_async_notअगरier_unरेजिस्टर(&xdev->notअगरier);
	v4l2_async_notअगरier_cleanup(&xdev->notअगरier);

	list_क्रम_each_entry_safe(dma, dmap, &xdev->dmas, list) अणु
		xvip_dma_cleanup(dma);
		list_del(&dma->list);
	पूर्ण
पूर्ण

अटल पूर्णांक xvip_graph_init(काष्ठा xvip_composite_device *xdev)
अणु
	पूर्णांक ret;

	/* Init the DMA channels. */
	ret = xvip_graph_dma_init(xdev);
	अगर (ret < 0) अणु
		dev_err(xdev->dev, "DMA initialization failed\n");
		जाओ करोne;
	पूर्ण

	/* Parse the graph to extract a list of subdevice DT nodes. */
	ret = xvip_graph_parse(xdev);
	अगर (ret < 0) अणु
		dev_err(xdev->dev, "graph parsing failed\n");
		जाओ करोne;
	पूर्ण

	अगर (list_empty(&xdev->notअगरier.asd_list)) अणु
		dev_err(xdev->dev, "no subdev found in graph\n");
		ret = -ENOENT;
		जाओ करोne;
	पूर्ण

	/* Register the subdevices notअगरier. */
	xdev->notअगरier.ops = &xvip_graph_notअगरy_ops;

	ret = v4l2_async_notअगरier_रेजिस्टर(&xdev->v4l2_dev, &xdev->notअगरier);
	अगर (ret < 0) अणु
		dev_err(xdev->dev, "notifier registration failed\n");
		जाओ करोne;
	पूर्ण

	ret = 0;

करोne:
	अगर (ret < 0)
		xvip_graph_cleanup(xdev);

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Media Controller and V4L2
 */

अटल व्योम xvip_composite_v4l2_cleanup(काष्ठा xvip_composite_device *xdev)
अणु
	v4l2_device_unरेजिस्टर(&xdev->v4l2_dev);
	media_device_unरेजिस्टर(&xdev->media_dev);
	media_device_cleanup(&xdev->media_dev);
पूर्ण

अटल पूर्णांक xvip_composite_v4l2_init(काष्ठा xvip_composite_device *xdev)
अणु
	पूर्णांक ret;

	xdev->media_dev.dev = xdev->dev;
	strscpy(xdev->media_dev.model, "Xilinx Video Composite Device",
		माप(xdev->media_dev.model));
	xdev->media_dev.hw_revision = 0;

	media_device_init(&xdev->media_dev);

	xdev->v4l2_dev.mdev = &xdev->media_dev;
	ret = v4l2_device_रेजिस्टर(xdev->dev, &xdev->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(xdev->dev, "V4L2 device registration failed (%d)\n",
			ret);
		media_device_cleanup(&xdev->media_dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Platक्रमm Device Driver
 */

अटल पूर्णांक xvip_composite_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xvip_composite_device *xdev;
	पूर्णांक ret;

	xdev = devm_kzalloc(&pdev->dev, माप(*xdev), GFP_KERNEL);
	अगर (!xdev)
		वापस -ENOMEM;

	xdev->dev = &pdev->dev;
	INIT_LIST_HEAD(&xdev->dmas);
	v4l2_async_notअगरier_init(&xdev->notअगरier);

	ret = xvip_composite_v4l2_init(xdev);
	अगर (ret < 0)
		वापस ret;

	ret = xvip_graph_init(xdev);
	अगर (ret < 0)
		जाओ error;

	platक्रमm_set_drvdata(pdev, xdev);

	dev_info(xdev->dev, "device registered\n");

	वापस 0;

error:
	xvip_composite_v4l2_cleanup(xdev);
	वापस ret;
पूर्ण

अटल पूर्णांक xvip_composite_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xvip_composite_device *xdev = platक्रमm_get_drvdata(pdev);

	xvip_graph_cleanup(xdev);
	xvip_composite_v4l2_cleanup(xdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xvip_composite_of_id_table[] = अणु
	अणु .compatible = "xlnx,video" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xvip_composite_of_id_table);

अटल काष्ठा platक्रमm_driver xvip_composite_driver = अणु
	.driver = अणु
		.name = "xilinx-video",
		.of_match_table = xvip_composite_of_id_table,
	पूर्ण,
	.probe = xvip_composite_probe,
	.हटाओ = xvip_composite_हटाओ,
पूर्ण;

module_platक्रमm_driver(xvip_composite_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Xilinx Video IP Composite Driver");
MODULE_LICENSE("GPL v2");
