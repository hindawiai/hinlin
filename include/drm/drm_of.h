<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DRM_OF_H__
#घोषणा __DRM_OF_H__

#समावेश <linux/of_graph.h>
#अगर IS_ENABLED(CONFIG_OF) && IS_ENABLED(CONFIG_DRM_PANEL_BRIDGE)
#समावेश <drm/drm_bridge.h>
#पूर्ण_अगर

काष्ठा component_master_ops;
काष्ठा component_match;
काष्ठा device;
काष्ठा drm_device;
काष्ठा drm_encoder;
काष्ठा drm_panel;
काष्ठा drm_bridge;
काष्ठा device_node;

/**
 * क्रमागत drm_lvds_dual_link_pixels - Pixel order of an LVDS dual-link connection
 * @DRM_LVDS_DUAL_LINK_EVEN_ODD_PIXELS: Even pixels are expected to be generated
 *    from the first port, odd pixels from the second port
 * @DRM_LVDS_DUAL_LINK_ODD_EVEN_PIXELS: Odd pixels are expected to be generated
 *    from the first port, even pixels from the second port
 */
क्रमागत drm_lvds_dual_link_pixels अणु
	DRM_LVDS_DUAL_LINK_EVEN_ODD_PIXELS = 0,
	DRM_LVDS_DUAL_LINK_ODD_EVEN_PIXELS = 1,
पूर्ण;

#अगर_घोषित CONFIG_OF
uपूर्णांक32_t drm_of_crtc_port_mask(काष्ठा drm_device *dev,
			    काष्ठा device_node *port);
uपूर्णांक32_t drm_of_find_possible_crtcs(काष्ठा drm_device *dev,
				    काष्ठा device_node *port);
व्योम drm_of_component_match_add(काष्ठा device *master,
				काष्ठा component_match **matchptr,
				पूर्णांक (*compare)(काष्ठा device *, व्योम *),
				काष्ठा device_node *node);
पूर्णांक drm_of_component_probe(काष्ठा device *dev,
			   पूर्णांक (*compare_of)(काष्ठा device *, व्योम *),
			   स्थिर काष्ठा component_master_ops *m_ops);
पूर्णांक drm_of_encoder_active_endpoपूर्णांक(काष्ठा device_node *node,
				   काष्ठा drm_encoder *encoder,
				   काष्ठा of_endpoपूर्णांक *endpoपूर्णांक);
पूर्णांक drm_of_find_panel_or_bridge(स्थिर काष्ठा device_node *np,
				पूर्णांक port, पूर्णांक endpoपूर्णांक,
				काष्ठा drm_panel **panel,
				काष्ठा drm_bridge **bridge);
पूर्णांक drm_of_lvds_get_dual_link_pixel_order(स्थिर काष्ठा device_node *port1,
					  स्थिर काष्ठा device_node *port2);
#अन्यथा
अटल अंतरभूत uपूर्णांक32_t drm_of_crtc_port_mask(काष्ठा drm_device *dev,
					  काष्ठा device_node *port)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t drm_of_find_possible_crtcs(काष्ठा drm_device *dev,
						  काष्ठा device_node *port)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
drm_of_component_match_add(काष्ठा device *master,
			   काष्ठा component_match **matchptr,
			   पूर्णांक (*compare)(काष्ठा device *, व्योम *),
			   काष्ठा device_node *node)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
drm_of_component_probe(काष्ठा device *dev,
		       पूर्णांक (*compare_of)(काष्ठा device *, व्योम *),
		       स्थिर काष्ठा component_master_ops *m_ops)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक drm_of_encoder_active_endpoपूर्णांक(काष्ठा device_node *node,
						 काष्ठा drm_encoder *encoder,
						 काष्ठा of_endpoपूर्णांक *endpoपूर्णांक)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक drm_of_find_panel_or_bridge(स्थिर काष्ठा device_node *np,
					      पूर्णांक port, पूर्णांक endpoपूर्णांक,
					      काष्ठा drm_panel **panel,
					      काष्ठा drm_bridge **bridge)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
drm_of_lvds_get_dual_link_pixel_order(स्थिर काष्ठा device_node *port1,
				      स्थिर काष्ठा device_node *port2)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/*
 * drm_of_panel_bridge_हटाओ - हटाओ panel bridge
 * @np: device tree node containing panel bridge output ports
 *
 * Remove the panel bridge of a given DT node's port and endpoपूर्णांक number
 *
 * Returns zero अगर successful, or one of the standard error codes अगर it fails.
 */
अटल अंतरभूत पूर्णांक drm_of_panel_bridge_हटाओ(स्थिर काष्ठा device_node *np,
					     पूर्णांक port, पूर्णांक endpoपूर्णांक)
अणु
#अगर IS_ENABLED(CONFIG_OF) && IS_ENABLED(CONFIG_DRM_PANEL_BRIDGE)
	काष्ठा drm_bridge *bridge;
	काष्ठा device_node *remote;

	remote = of_graph_get_remote_node(np, port, endpoपूर्णांक);
	अगर (!remote)
		वापस -ENODEV;

	bridge = of_drm_find_bridge(remote);
	drm_panel_bridge_हटाओ(bridge);

	वापस 0;
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक drm_of_encoder_active_endpoपूर्णांक_id(काष्ठा device_node *node,
						    काष्ठा drm_encoder *encoder)
अणु
	काष्ठा of_endpoपूर्णांक endpoपूर्णांक;
	पूर्णांक ret = drm_of_encoder_active_endpoपूर्णांक(node, encoder,
						 &endpoपूर्णांक);

	वापस ret ?: endpoपूर्णांक.id;
पूर्ण

अटल अंतरभूत पूर्णांक drm_of_encoder_active_port_id(काष्ठा device_node *node,
						काष्ठा drm_encoder *encoder)
अणु
	काष्ठा of_endpoपूर्णांक endpoपूर्णांक;
	पूर्णांक ret = drm_of_encoder_active_endpoपूर्णांक(node, encoder,
						 &endpoपूर्णांक);

	वापस ret ?: endpoपूर्णांक.port;
पूर्ण

#पूर्ण_अगर /* __DRM_OF_H__ */
