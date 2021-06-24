<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */

#समावेश "edp.h"

काष्ठा edp_bridge अणु
	काष्ठा drm_bridge base;
	काष्ठा msm_edp *edp;
पूर्ण;
#घोषणा to_edp_bridge(x) container_of(x, काष्ठा edp_bridge, base)

व्योम edp_bridge_destroy(काष्ठा drm_bridge *bridge)
अणु
पूर्ण

अटल व्योम edp_bridge_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा edp_bridge *edp_bridge = to_edp_bridge(bridge);
	काष्ठा msm_edp *edp = edp_bridge->edp;

	DBG("");
	msm_edp_ctrl_घातer(edp->ctrl, true);
पूर्ण

अटल व्योम edp_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	DBG("");
पूर्ण

अटल व्योम edp_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	DBG("");
पूर्ण

अटल व्योम edp_bridge_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा edp_bridge *edp_bridge = to_edp_bridge(bridge);
	काष्ठा msm_edp *edp = edp_bridge->edp;

	DBG("");
	msm_edp_ctrl_घातer(edp->ctrl, false);
पूर्ण

अटल व्योम edp_bridge_mode_set(काष्ठा drm_bridge *bridge,
		स्थिर काष्ठा drm_display_mode *mode,
		स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = bridge->dev;
	काष्ठा drm_connector *connector;
	काष्ठा edp_bridge *edp_bridge = to_edp_bridge(bridge);
	काष्ठा msm_edp *edp = edp_bridge->edp;

	DBG("set mode: " DRM_MODE_FMT, DRM_MODE_ARG(mode));

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		काष्ठा drm_encoder *encoder = connector->encoder;
		काष्ठा drm_bridge *first_bridge;

		अगर (!connector->encoder)
			जारी;

		first_bridge = drm_bridge_chain_get_first_bridge(encoder);
		अगर (bridge == first_bridge) अणु
			msm_edp_ctrl_timing_cfg(edp->ctrl,
				adjusted_mode, &connector->display_info);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs edp_bridge_funcs = अणु
	.pre_enable = edp_bridge_pre_enable,
	.enable = edp_bridge_enable,
	.disable = edp_bridge_disable,
	.post_disable = edp_bridge_post_disable,
	.mode_set = edp_bridge_mode_set,
पूर्ण;

/* initialize bridge */
काष्ठा drm_bridge *msm_edp_bridge_init(काष्ठा msm_edp *edp)
अणु
	काष्ठा drm_bridge *bridge = शून्य;
	काष्ठा edp_bridge *edp_bridge;
	पूर्णांक ret;

	edp_bridge = devm_kzalloc(edp->dev->dev,
			माप(*edp_bridge), GFP_KERNEL);
	अगर (!edp_bridge) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	edp_bridge->edp = edp;

	bridge = &edp_bridge->base;
	bridge->funcs = &edp_bridge_funcs;

	ret = drm_bridge_attach(edp->encoder, bridge, शून्य, 0);
	अगर (ret)
		जाओ fail;

	वापस bridge;

fail:
	अगर (bridge)
		edp_bridge_destroy(bridge);

	वापस ERR_PTR(ret);
पूर्ण
