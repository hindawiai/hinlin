<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Traphandler
 * Copyright (C) 2014 Free Electrons
 * Copyright (C) 2014 Aपंचांगel
 *
 * Author: Jean-Jacques Hiblot <jjhiblot@traphandler.com>
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <linux/of_graph.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "atmel_hlcdc_dc.h"

काष्ठा aपंचांगel_hlcdc_rgb_output अणु
	काष्ठा drm_encoder encoder;
	पूर्णांक bus_fmt;
पूर्ण;

अटल काष्ठा aपंचांगel_hlcdc_rgb_output *
aपंचांगel_hlcdc_encoder_to_rgb_output(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा aपंचांगel_hlcdc_rgb_output, encoder);
पूर्ण

पूर्णांक aपंचांगel_hlcdc_encoder_get_bus_fmt(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा aपंचांगel_hlcdc_rgb_output *output;

	output = aपंचांगel_hlcdc_encoder_to_rgb_output(encoder);

	वापस output->bus_fmt;
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_of_bus_fmt(स्थिर काष्ठा device_node *ep)
अणु
	u32 bus_width;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(ep, "bus-width", &bus_width);
	अगर (ret == -EINVAL)
		वापस 0;
	अगर (ret)
		वापस ret;

	चयन (bus_width) अणु
	हाल 12:
		वापस MEDIA_BUS_FMT_RGB444_1X12;
	हाल 16:
		वापस MEDIA_BUS_FMT_RGB565_1X16;
	हाल 18:
		वापस MEDIA_BUS_FMT_RGB666_1X18;
	हाल 24:
		वापस MEDIA_BUS_FMT_RGB888_1X24;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_attach_endpoपूर्णांक(काष्ठा drm_device *dev, पूर्णांक endpoपूर्णांक)
अणु
	काष्ठा aपंचांगel_hlcdc_rgb_output *output;
	काष्ठा device_node *ep;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	पूर्णांक ret;

	ep = of_graph_get_endpoपूर्णांक_by_regs(dev->dev->of_node, 0, endpoपूर्णांक);
	अगर (!ep)
		वापस -ENODEV;

	ret = drm_of_find_panel_or_bridge(dev->dev->of_node, 0, endpoपूर्णांक,
					  &panel, &bridge);
	अगर (ret) अणु
		of_node_put(ep);
		वापस ret;
	पूर्ण

	output = devm_kzalloc(dev->dev, माप(*output), GFP_KERNEL);
	अगर (!output) अणु
		of_node_put(ep);
		वापस -ENOMEM;
	पूर्ण

	output->bus_fmt = aपंचांगel_hlcdc_of_bus_fmt(ep);
	of_node_put(ep);
	अगर (output->bus_fmt < 0) अणु
		dev_err(dev->dev, "endpoint %d: invalid bus width\n", endpoपूर्णांक);
		वापस -EINVAL;
	पूर्ण

	ret = drm_simple_encoder_init(dev, &output->encoder,
				      DRM_MODE_ENCODER_NONE);
	अगर (ret)
		वापस ret;

	output->encoder.possible_crtcs = 0x1;

	अगर (panel) अणु
		bridge = drm_panel_bridge_add_typed(panel,
						    DRM_MODE_CONNECTOR_Unknown);
		अगर (IS_ERR(bridge))
			वापस PTR_ERR(bridge);
	पूर्ण

	अगर (bridge) अणु
		ret = drm_bridge_attach(&output->encoder, bridge, शून्य, 0);
		अगर (!ret)
			वापस 0;

		अगर (panel)
			drm_panel_bridge_हटाओ(bridge);
	पूर्ण

	drm_encoder_cleanup(&output->encoder);

	वापस ret;
पूर्ण

पूर्णांक aपंचांगel_hlcdc_create_outमाला_दो(काष्ठा drm_device *dev)
अणु
	पूर्णांक endpoपूर्णांक, ret = 0;
	पूर्णांक attached = 0;

	/*
	 * Always scan the first few endpoपूर्णांकs even अगर we get -ENODEV,
	 * but keep going after that as दीर्घ as we keep getting hits.
	 */
	क्रम (endpoपूर्णांक = 0; !ret || endpoपूर्णांक < 4; endpoपूर्णांक++) अणु
		ret = aपंचांगel_hlcdc_attach_endpoपूर्णांक(dev, endpoपूर्णांक);
		अगर (ret == -ENODEV)
			जारी;
		अगर (ret)
			अवरोध;
		attached++;
	पूर्ण

	/* At least one device was successfully attached.*/
	अगर (ret == -ENODEV && attached)
		वापस 0;

	वापस ret;
पूर्ण
