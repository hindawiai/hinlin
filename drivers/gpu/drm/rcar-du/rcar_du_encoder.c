<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rcar_du_encoder.c  --  R-Car Display Unit Encoder
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/export.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_panel.h>

#समावेश "rcar_du_drv.h"
#समावेश "rcar_du_encoder.h"
#समावेश "rcar_du_kms.h"
#समावेश "rcar_lvds.h"

/* -----------------------------------------------------------------------------
 * Encoder
 */

अटल अचिन्हित पूर्णांक rcar_du_encoder_count_ports(काष्ठा device_node *node)
अणु
	काष्ठा device_node *ports;
	काष्ठा device_node *port;
	अचिन्हित पूर्णांक num_ports = 0;

	ports = of_get_child_by_name(node, "ports");
	अगर (!ports)
		ports = of_node_get(node);

	क्रम_each_child_of_node(ports, port) अणु
		अगर (of_node_name_eq(port, "port"))
			num_ports++;
	पूर्ण

	of_node_put(ports);

	वापस num_ports;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs rcar_du_encoder_funcs = अणु
पूर्ण;

पूर्णांक rcar_du_encoder_init(काष्ठा rcar_du_device *rcdu,
			 क्रमागत rcar_du_output output,
			 काष्ठा device_node *enc_node)
अणु
	काष्ठा rcar_du_encoder *renc;
	काष्ठा drm_bridge *bridge;

	/*
	 * Locate the DRM bridge from the DT node. For the DPAD outमाला_दो, अगर the
	 * DT node has a single port, assume that it describes a panel and
	 * create a panel bridge.
	 */
	अगर ((output == RCAR_DU_OUTPUT_DPAD0 ||
	     output == RCAR_DU_OUTPUT_DPAD1) &&
	    rcar_du_encoder_count_ports(enc_node) == 1) अणु
		काष्ठा drm_panel *panel = of_drm_find_panel(enc_node);

		अगर (IS_ERR(panel))
			वापस PTR_ERR(panel);

		bridge = devm_drm_panel_bridge_add_typed(rcdu->dev, panel,
							 DRM_MODE_CONNECTOR_DPI);
		अगर (IS_ERR(bridge))
			वापस PTR_ERR(bridge);
	पूर्ण अन्यथा अणु
		bridge = of_drm_find_bridge(enc_node);
		अगर (!bridge)
			वापस -EPROBE_DEFER;

		अगर (output == RCAR_DU_OUTPUT_LVDS0 ||
		    output == RCAR_DU_OUTPUT_LVDS1)
			rcdu->lvds[output - RCAR_DU_OUTPUT_LVDS0] = bridge;
	पूर्ण

	/*
	 * Create and initialize the encoder. On Gen3 skip the LVDS1 output अगर
	 * the LVDS1 encoder is used as a companion क्रम LVDS0 in dual-link
	 * mode.
	 */
	अगर (rcdu->info->gen >= 3 && output == RCAR_DU_OUTPUT_LVDS1) अणु
		अगर (rcar_lvds_dual_link(bridge))
			वापस -ENOLINK;
	पूर्ण

	dev_dbg(rcdu->dev, "initializing encoder %pOF for output %u\n",
		enc_node, output);

	renc = drmm_encoder_alloc(&rcdu->ddev, काष्ठा rcar_du_encoder, base,
				  &rcar_du_encoder_funcs, DRM_MODE_ENCODER_NONE,
				  शून्य);
	अगर (!renc)
		वापस -ENOMEM;

	renc->output = output;

	/*
	 * Attach the bridge to the encoder. The bridge will create the
	 * connector.
	 */
	वापस drm_bridge_attach(&renc->base, bridge, शून्य, 0);
पूर्ण
