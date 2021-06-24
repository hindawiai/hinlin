<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      uvc_entity.c  --  USB Video Class driver
 *
 *      Copyright (C) 2005-2011
 *          Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-common.h>

#समावेश "uvcvideo.h"

अटल पूर्णांक uvc_mc_create_links(काष्ठा uvc_video_chain *chain,
				    काष्ठा uvc_entity *entity)
अणु
	स्थिर u32 flags = MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE;
	काष्ठा media_entity *sink;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	sink = (UVC_ENTITY_TYPE(entity) == UVC_TT_STREAMING)
	     ? (entity->vdev ? &entity->vdev->entity : शून्य)
	     : &entity->subdev.entity;
	अगर (sink == शून्य)
		वापस 0;

	क्रम (i = 0; i < entity->num_pads; ++i) अणु
		काष्ठा media_entity *source;
		काष्ठा uvc_entity *remote;
		u8 remote_pad;

		अगर (!(entity->pads[i].flags & MEDIA_PAD_FL_SINK))
			जारी;

		remote = uvc_entity_by_id(chain->dev, entity->baSourceID[i]);
		अगर (remote == शून्य)
			वापस -EINVAL;

		source = (UVC_ENTITY_TYPE(remote) == UVC_TT_STREAMING)
		       ? (remote->vdev ? &remote->vdev->entity : शून्य)
		       : &remote->subdev.entity;
		अगर (source == शून्य)
			जारी;

		remote_pad = remote->num_pads - 1;
		ret = media_create_pad_link(source, remote_pad,
					       sink, i, flags);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_ops uvc_subdev_ops = अणु
पूर्ण;

व्योम uvc_mc_cleanup_entity(काष्ठा uvc_entity *entity)
अणु
	अगर (UVC_ENTITY_TYPE(entity) != UVC_TT_STREAMING)
		media_entity_cleanup(&entity->subdev.entity);
	अन्यथा अगर (entity->vdev != शून्य)
		media_entity_cleanup(&entity->vdev->entity);
पूर्ण

अटल पूर्णांक uvc_mc_init_entity(काष्ठा uvc_video_chain *chain,
			      काष्ठा uvc_entity *entity)
अणु
	पूर्णांक ret;

	अगर (UVC_ENTITY_TYPE(entity) != UVC_TT_STREAMING) अणु
		u32 function;

		v4l2_subdev_init(&entity->subdev, &uvc_subdev_ops);
		strscpy(entity->subdev.name, entity->name,
			माप(entity->subdev.name));

		चयन (UVC_ENTITY_TYPE(entity)) अणु
		हाल UVC_VC_SELECTOR_UNIT:
			function = MEDIA_ENT_F_VID_MUX;
			अवरोध;
		हाल UVC_VC_PROCESSING_UNIT:
		हाल UVC_VC_EXTENSION_UNIT:
			/* For lack of a better option. */
			function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
			अवरोध;
		हाल UVC_COMPOSITE_CONNECTOR:
		हाल UVC_COMPONENT_CONNECTOR:
			function = MEDIA_ENT_F_CONN_COMPOSITE;
			अवरोध;
		हाल UVC_SVIDEO_CONNECTOR:
			function = MEDIA_ENT_F_CONN_SVIDEO;
			अवरोध;
		हाल UVC_ITT_CAMERA:
			function = MEDIA_ENT_F_CAM_SENSOR;
			अवरोध;
		हाल UVC_TT_VENDOR_SPECIFIC:
		हाल UVC_ITT_VENDOR_SPECIFIC:
		हाल UVC_ITT_MEDIA_TRANSPORT_INPUT:
		हाल UVC_OTT_VENDOR_SPECIFIC:
		हाल UVC_OTT_DISPLAY:
		हाल UVC_OTT_MEDIA_TRANSPORT_OUTPUT:
		हाल UVC_EXTERNAL_VENDOR_SPECIFIC:
		हाल UVC_EXT_GPIO_UNIT:
		शेष:
			function = MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN;
			अवरोध;
		पूर्ण

		entity->subdev.entity.function = function;

		ret = media_entity_pads_init(&entity->subdev.entity,
					entity->num_pads, entity->pads);

		अगर (ret < 0)
			वापस ret;

		ret = v4l2_device_रेजिस्टर_subdev(&chain->dev->vdev,
						  &entity->subdev);
	पूर्ण अन्यथा अगर (entity->vdev != शून्य) अणु
		ret = media_entity_pads_init(&entity->vdev->entity,
					entity->num_pads, entity->pads);
		अगर (entity->flags & UVC_ENTITY_FLAG_DEFAULT)
			entity->vdev->entity.flags |= MEDIA_ENT_FL_DEFAULT;
	पूर्ण अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

पूर्णांक uvc_mc_रेजिस्टर_entities(काष्ठा uvc_video_chain *chain)
अणु
	काष्ठा uvc_entity *entity;
	पूर्णांक ret;

	list_क्रम_each_entry(entity, &chain->entities, chain) अणु
		ret = uvc_mc_init_entity(chain, entity);
		अगर (ret < 0) अणु
			dev_info(&chain->dev->udev->dev,
				 "Failed to initialize entity for entity %u\n",
				 entity->id);
			वापस ret;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(entity, &chain->entities, chain) अणु
		ret = uvc_mc_create_links(chain, entity);
		अगर (ret < 0) अणु
			dev_info(&chain->dev->udev->dev,
				 "Failed to create links for entity %u\n",
				 entity->id);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
