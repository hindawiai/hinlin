<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <linux/device.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश <xen/पूर्णांकerface/io/displअगर.h>
#समावेश <xen/xenbus.h>

#समावेश "xen_drm_front.h"
#समावेश "xen_drm_front_cfg.h"

अटल पूर्णांक cfg_connector(काष्ठा xen_drm_front_info *front_info,
			 काष्ठा xen_drm_front_cfg_connector *connector,
			 स्थिर अक्षर *path, पूर्णांक index)
अणु
	अक्षर *connector_path;

	connector_path = devm_kaप्र_लिखो(&front_info->xb_dev->dev,
					GFP_KERNEL, "%s/%d", path, index);
	अगर (!connector_path)
		वापस -ENOMEM;

	अगर (xenbus_म_पूछो(XBT_NIL, connector_path, XENDISPL_FIELD_RESOLUTION,
			 "%d" XENDISPL_RESOLUTION_SEPARATOR "%d",
			 &connector->width, &connector->height) < 0) अणु
		/* either no entry configured or wrong resolution set */
		connector->width = 0;
		connector->height = 0;
		वापस -EINVAL;
	पूर्ण

	connector->xenstore_path = connector_path;

	DRM_INFO("Connector %s: resolution %dx%d\n",
		 connector_path, connector->width, connector->height);
	वापस 0;
पूर्ण

पूर्णांक xen_drm_front_cfg_card(काष्ठा xen_drm_front_info *front_info,
			   काष्ठा xen_drm_front_cfg *cfg)
अणु
	काष्ठा xenbus_device *xb_dev = front_info->xb_dev;
	पूर्णांक ret, i;

	अगर (xenbus_पढ़ो_अचिन्हित(front_info->xb_dev->nodename,
				 XENDISPL_FIELD_BE_ALLOC, 0)) अणु
		DRM_INFO("Backend can provide display buffers\n");
		cfg->be_alloc = true;
	पूर्ण

	cfg->num_connectors = 0;
	क्रम (i = 0; i < ARRAY_SIZE(cfg->connectors); i++) अणु
		ret = cfg_connector(front_info, &cfg->connectors[i],
				    xb_dev->nodename, i);
		अगर (ret < 0)
			अवरोध;
		cfg->num_connectors++;
	पूर्ण

	अगर (!cfg->num_connectors) अणु
		DRM_ERROR("No connector(s) configured at %s\n",
			  xb_dev->nodename);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

