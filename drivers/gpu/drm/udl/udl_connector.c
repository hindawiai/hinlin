<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Red Hat
 * based in parts on udlfb.c:
 * Copyright (C) 2009 Roberto De Ioris <roberto@unbit.it>
 * Copyright (C) 2009 Jaya Kumar <jayakumar.lkml@gmail.com>
 * Copyright (C) 2009 Bernie Thompson <bernie@plugable.com>
 */

#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "udl_connector.h"
#समावेश "udl_drv.h"

अटल पूर्णांक udl_get_edid_block(व्योम *data, u8 *buf, अचिन्हित पूर्णांक block,
			       माप_प्रकार len)
अणु
	पूर्णांक ret, i;
	u8 *पढ़ो_buff;
	काष्ठा udl_device *udl = data;
	काष्ठा usb_device *udev = udl_to_usb_device(udl);

	पढ़ो_buff = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!पढ़ो_buff)
		वापस -1;

	क्रम (i = 0; i < len; i++) अणु
		पूर्णांक bval = (i + block * EDID_LENGTH) << 8;
		ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				      0x02, (0x80 | (0x02 << 5)), bval,
				      0xA1, पढ़ो_buff, 2, HZ);
		अगर (ret < 1) अणु
			DRM_ERROR("Read EDID byte %d failed err %x\n", i, ret);
			kमुक्त(पढ़ो_buff);
			वापस -1;
		पूर्ण
		buf[i] = पढ़ो_buff[1];
	पूर्ण

	kमुक्त(पढ़ो_buff);
	वापस 0;
पूर्ण

अटल पूर्णांक udl_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा udl_drm_connector *udl_connector =
					container_of(connector,
					काष्ठा udl_drm_connector,
					connector);

	drm_connector_update_edid_property(connector, udl_connector->edid);
	अगर (udl_connector->edid)
		वापस drm_add_edid_modes(connector, udl_connector->edid);
	वापस 0;
पूर्ण

अटल क्रमागत drm_mode_status udl_mode_valid(काष्ठा drm_connector *connector,
			  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा udl_device *udl = to_udl(connector->dev);
	अगर (!udl->sku_pixel_limit)
		वापस 0;

	अगर (mode->vdisplay * mode->hdisplay > udl->sku_pixel_limit)
		वापस MODE_VIRTUAL_Y;

	वापस 0;
पूर्ण

अटल क्रमागत drm_connector_status
udl_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा udl_device *udl = to_udl(connector->dev);
	काष्ठा udl_drm_connector *udl_connector =
					container_of(connector,
					काष्ठा udl_drm_connector,
					connector);

	/* cleanup previous edid */
	अगर (udl_connector->edid != शून्य) अणु
		kमुक्त(udl_connector->edid);
		udl_connector->edid = शून्य;
	पूर्ण

	udl_connector->edid = drm_करो_get_edid(connector, udl_get_edid_block, udl);
	अगर (!udl_connector->edid)
		वापस connector_status_disconnected;

	वापस connector_status_connected;
पूर्ण

अटल व्योम udl_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा udl_drm_connector *udl_connector =
					container_of(connector,
					काष्ठा udl_drm_connector,
					connector);

	drm_connector_cleanup(connector);
	kमुक्त(udl_connector->edid);
	kमुक्त(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs udl_connector_helper_funcs = अणु
	.get_modes = udl_get_modes,
	.mode_valid = udl_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs udl_connector_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.detect = udl_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = udl_connector_destroy,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state   = drm_atomic_helper_connector_destroy_state,
पूर्ण;

काष्ठा drm_connector *udl_connector_init(काष्ठा drm_device *dev)
अणु
	काष्ठा udl_drm_connector *udl_connector;
	काष्ठा drm_connector *connector;

	udl_connector = kzalloc(माप(काष्ठा udl_drm_connector), GFP_KERNEL);
	अगर (!udl_connector)
		वापस ERR_PTR(-ENOMEM);

	connector = &udl_connector->connector;
	drm_connector_init(dev, connector, &udl_connector_funcs,
			   DRM_MODE_CONNECTOR_DVII);
	drm_connector_helper_add(connector, &udl_connector_helper_funcs);

	connector->polled = DRM_CONNECTOR_POLL_HPD |
		DRM_CONNECTOR_POLL_CONNECT | DRM_CONNECTOR_POLL_DISCONNECT;

	वापस connector;
पूर्ण
