<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/component.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/of_graph.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>

/**
 * DOC: overview
 *
 * A set of helper functions to aid DRM drivers in parsing standard DT
 * properties.
 */

अटल व्योम drm_release_of(काष्ठा device *dev, व्योम *data)
अणु
	of_node_put(data);
पूर्ण

/**
 * drm_of_crtc_port_mask - find the mask of a रेजिस्टरed CRTC by port OF node
 * @dev: DRM device
 * @port: port OF node
 *
 * Given a port OF node, वापस the possible mask of the corresponding
 * CRTC within a device's list of CRTCs.  Returns zero अगर not found.
 */
uपूर्णांक32_t drm_of_crtc_port_mask(काष्ठा drm_device *dev,
			    काष्ठा device_node *port)
अणु
	अचिन्हित पूर्णांक index = 0;
	काष्ठा drm_crtc *पंचांगp;

	drm_क्रम_each_crtc(पंचांगp, dev) अणु
		अगर (पंचांगp->port == port)
			वापस 1 << index;

		index++;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_of_crtc_port_mask);

/**
 * drm_of_find_possible_crtcs - find the possible CRTCs क्रम an encoder port
 * @dev: DRM device
 * @port: encoder port to scan क्रम endpoपूर्णांकs
 *
 * Scan all endpoपूर्णांकs attached to a port, locate their attached CRTCs,
 * and generate the DRM mask of CRTCs which may be attached to this
 * encoder.
 *
 * See Documentation/devicetree/bindings/graph.txt क्रम the bindings.
 */
uपूर्णांक32_t drm_of_find_possible_crtcs(काष्ठा drm_device *dev,
				    काष्ठा device_node *port)
अणु
	काष्ठा device_node *remote_port, *ep;
	uपूर्णांक32_t possible_crtcs = 0;

	क्रम_each_endpoपूर्णांक_of_node(port, ep) अणु
		remote_port = of_graph_get_remote_port(ep);
		अगर (!remote_port) अणु
			of_node_put(ep);
			वापस 0;
		पूर्ण

		possible_crtcs |= drm_of_crtc_port_mask(dev, remote_port);

		of_node_put(remote_port);
	पूर्ण

	वापस possible_crtcs;
पूर्ण
EXPORT_SYMBOL(drm_of_find_possible_crtcs);

/**
 * drm_of_component_match_add - Add a component helper OF node match rule
 * @master: master device
 * @matchptr: component match poपूर्णांकer
 * @compare: compare function used क्रम matching component
 * @node: of_node
 */
व्योम drm_of_component_match_add(काष्ठा device *master,
				काष्ठा component_match **matchptr,
				पूर्णांक (*compare)(काष्ठा device *, व्योम *),
				काष्ठा device_node *node)
अणु
	of_node_get(node);
	component_match_add_release(master, matchptr, drm_release_of,
				    compare, node);
पूर्ण
EXPORT_SYMBOL_GPL(drm_of_component_match_add);

/**
 * drm_of_component_probe - Generic probe function क्रम a component based master
 * @dev: master device containing the OF node
 * @compare_of: compare function used क्रम matching components
 * @m_ops: component master ops to be used
 *
 * Parse the platक्रमm device OF node and bind all the components associated
 * with the master. Interface ports are added beक्रमe the encoders in order to
 * satisfy their .bind requirements
 * See Documentation/devicetree/bindings/graph.txt क्रम the bindings.
 *
 * Returns zero अगर successful, or one of the standard error codes अगर it fails.
 */
पूर्णांक drm_of_component_probe(काष्ठा device *dev,
			   पूर्णांक (*compare_of)(काष्ठा device *, व्योम *),
			   स्थिर काष्ठा component_master_ops *m_ops)
अणु
	काष्ठा device_node *ep, *port, *remote;
	काष्ठा component_match *match = शून्य;
	पूर्णांक i;

	अगर (!dev->of_node)
		वापस -EINVAL;

	/*
	 * Bind the crtc's ports first, so that drm_of_find_possible_crtcs()
	 * called from encoder's .bind callbacks works as expected
	 */
	क्रम (i = 0; ; i++) अणु
		port = of_parse_phandle(dev->of_node, "ports", i);
		अगर (!port)
			अवरोध;

		अगर (of_device_is_available(port->parent))
			drm_of_component_match_add(dev, &match, compare_of,
						   port);

		of_node_put(port);
	पूर्ण

	अगर (i == 0) अणु
		dev_err(dev, "missing 'ports' property\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!match) अणु
		dev_err(dev, "no available port\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * For bound crtcs, bind the encoders attached to their remote endpoपूर्णांक
	 */
	क्रम (i = 0; ; i++) अणु
		port = of_parse_phandle(dev->of_node, "ports", i);
		अगर (!port)
			अवरोध;

		अगर (!of_device_is_available(port->parent)) अणु
			of_node_put(port);
			जारी;
		पूर्ण

		क्रम_each_child_of_node(port, ep) अणु
			remote = of_graph_get_remote_port_parent(ep);
			अगर (!remote || !of_device_is_available(remote)) अणु
				of_node_put(remote);
				जारी;
			पूर्ण अन्यथा अगर (!of_device_is_available(remote->parent)) अणु
				dev_warn(dev, "parent device of %pOF is not available\n",
					 remote);
				of_node_put(remote);
				जारी;
			पूर्ण

			drm_of_component_match_add(dev, &match, compare_of,
						   remote);
			of_node_put(remote);
		पूर्ण
		of_node_put(port);
	पूर्ण

	वापस component_master_add_with_match(dev, m_ops, match);
पूर्ण
EXPORT_SYMBOL(drm_of_component_probe);

/*
 * drm_of_encoder_active_endpoपूर्णांक - वापस the active encoder endpoपूर्णांक
 * @node: device tree node containing encoder input ports
 * @encoder: drm_encoder
 *
 * Given an encoder device node and a drm_encoder with a connected crtc,
 * parse the encoder endpoपूर्णांक connecting to the crtc port.
 */
पूर्णांक drm_of_encoder_active_endpoपूर्णांक(काष्ठा device_node *node,
				   काष्ठा drm_encoder *encoder,
				   काष्ठा of_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा device_node *ep;
	काष्ठा drm_crtc *crtc = encoder->crtc;
	काष्ठा device_node *port;
	पूर्णांक ret;

	अगर (!node || !crtc)
		वापस -EINVAL;

	क्रम_each_endpoपूर्णांक_of_node(node, ep) अणु
		port = of_graph_get_remote_port(ep);
		of_node_put(port);
		अगर (port == crtc->port) अणु
			ret = of_graph_parse_endpoपूर्णांक(ep, endpoपूर्णांक);
			of_node_put(ep);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(drm_of_encoder_active_endpoपूर्णांक);

/**
 * drm_of_find_panel_or_bridge - वापस connected panel or bridge device
 * @np: device tree node containing encoder output ports
 * @port: port in the device tree node
 * @endpoपूर्णांक: endpoपूर्णांक in the device tree node
 * @panel: poपूर्णांकer to hold वापसed drm_panel
 * @bridge: poपूर्णांकer to hold वापसed drm_bridge
 *
 * Given a DT node's port and endpoपूर्णांक number, find the connected node and
 * वापस either the associated काष्ठा drm_panel or drm_bridge device. Either
 * @panel or @bridge must not be शून्य.
 *
 * Returns zero अगर successful, or one of the standard error codes अगर it fails.
 */
पूर्णांक drm_of_find_panel_or_bridge(स्थिर काष्ठा device_node *np,
				पूर्णांक port, पूर्णांक endpoपूर्णांक,
				काष्ठा drm_panel **panel,
				काष्ठा drm_bridge **bridge)
अणु
	पूर्णांक ret = -EPROBE_DEFER;
	काष्ठा device_node *remote;

	अगर (!panel && !bridge)
		वापस -EINVAL;
	अगर (panel)
		*panel = शून्य;

	/*
	 * of_graph_get_remote_node() produces a noisy error message अगर port
	 * node isn't found and the असलence of the port is a legit हाल here,
	 * so at first we silently check whether graph presents in the
	 * device-tree node.
	 */
	अगर (!of_graph_is_present(np))
		वापस -ENODEV;

	remote = of_graph_get_remote_node(np, port, endpoपूर्णांक);
	अगर (!remote)
		वापस -ENODEV;

	अगर (panel) अणु
		*panel = of_drm_find_panel(remote);
		अगर (!IS_ERR(*panel))
			ret = 0;
		अन्यथा
			*panel = शून्य;
	पूर्ण

	/* No panel found yet, check क्रम a bridge next. */
	अगर (bridge) अणु
		अगर (ret) अणु
			*bridge = of_drm_find_bridge(remote);
			अगर (*bridge)
				ret = 0;
		पूर्ण अन्यथा अणु
			*bridge = शून्य;
		पूर्ण

	पूर्ण

	of_node_put(remote);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(drm_of_find_panel_or_bridge);

क्रमागत drm_of_lvds_pixels अणु
	DRM_OF_LVDS_EVEN = BIT(0),
	DRM_OF_LVDS_ODD = BIT(1),
पूर्ण;

अटल पूर्णांक drm_of_lvds_get_port_pixels_type(काष्ठा device_node *port_node)
अणु
	bool even_pixels =
		of_property_पढ़ो_bool(port_node, "dual-lvds-even-pixels");
	bool odd_pixels =
		of_property_पढ़ो_bool(port_node, "dual-lvds-odd-pixels");

	वापस (even_pixels ? DRM_OF_LVDS_EVEN : 0) |
	       (odd_pixels ? DRM_OF_LVDS_ODD : 0);
पूर्ण

अटल पूर्णांक drm_of_lvds_get_remote_pixels_type(
			स्थिर काष्ठा device_node *port_node)
अणु
	काष्ठा device_node *endpoपूर्णांक = शून्य;
	पूर्णांक pixels_type = -EPIPE;

	क्रम_each_child_of_node(port_node, endpoपूर्णांक) अणु
		काष्ठा device_node *remote_port;
		पूर्णांक current_pt;

		अगर (!of_node_name_eq(endpoपूर्णांक, "endpoint"))
			जारी;

		remote_port = of_graph_get_remote_port(endpoपूर्णांक);
		अगर (!remote_port) अणु
			of_node_put(remote_port);
			वापस -EPIPE;
		पूर्ण

		current_pt = drm_of_lvds_get_port_pixels_type(remote_port);
		of_node_put(remote_port);
		अगर (pixels_type < 0)
			pixels_type = current_pt;

		/*
		 * Sanity check, ensure that all remote endpoपूर्णांकs have the same
		 * pixel type. We may lअगरt this restriction later अगर we need to
		 * support multiple sinks with dअगरferent dual-link
		 * configurations by passing the endpoपूर्णांकs explicitly to
		 * drm_of_lvds_get_dual_link_pixel_order().
		 */
		अगर (!current_pt || pixels_type != current_pt)
			वापस -EINVAL;
	पूर्ण

	वापस pixels_type;
पूर्ण

/**
 * drm_of_lvds_get_dual_link_pixel_order - Get LVDS dual-link pixel order
 * @port1: First DT port node of the Dual-link LVDS source
 * @port2: Second DT port node of the Dual-link LVDS source
 *
 * An LVDS dual-link connection is made of two links, with even pixels
 * transitting on one link, and odd pixels on the other link. This function
 * वापसs, क्रम two ports of an LVDS dual-link source, which port shall transmit
 * the even and odd pixels, based on the requirements of the connected sink.
 *
 * The pixel order is determined from the dual-lvds-even-pixels and
 * dual-lvds-odd-pixels properties in the sink's DT port nodes. If those
 * properties are not present, or अगर their usage is not valid, this function
 * वापसs -EINVAL.
 *
 * If either port is not connected, this function वापसs -EPIPE.
 *
 * @port1 and @port2 are typically DT sibling nodes, but may have dअगरferent
 * parents when, क्रम instance, two separate LVDS encoders carry the even and odd
 * pixels.
 *
 * Return:
 * * DRM_LVDS_DUAL_LINK_EVEN_ODD_PIXELS - @port1 carries even pixels and @port2
 *   carries odd pixels
 * * DRM_LVDS_DUAL_LINK_ODD_EVEN_PIXELS - @port1 carries odd pixels and @port2
 *   carries even pixels
 * * -EINVAL - @port1 and @port2 are not connected to a dual-link LVDS sink, or
 *   the sink configuration is invalid
 * * -EPIPE - when @port1 or @port2 are not connected
 */
पूर्णांक drm_of_lvds_get_dual_link_pixel_order(स्थिर काष्ठा device_node *port1,
					  स्थिर काष्ठा device_node *port2)
अणु
	पूर्णांक remote_p1_pt, remote_p2_pt;

	अगर (!port1 || !port2)
		वापस -EINVAL;

	remote_p1_pt = drm_of_lvds_get_remote_pixels_type(port1);
	अगर (remote_p1_pt < 0)
		वापस remote_p1_pt;

	remote_p2_pt = drm_of_lvds_get_remote_pixels_type(port2);
	अगर (remote_p2_pt < 0)
		वापस remote_p2_pt;

	/*
	 * A valid dual-lVDS bus is found when one remote port is marked with
	 * "dual-lvds-even-pixels", and the other remote port is marked with
	 * "dual-lvds-odd-pixels", bail out अगर the markers are not right.
	 */
	अगर (remote_p1_pt + remote_p2_pt != DRM_OF_LVDS_EVEN + DRM_OF_LVDS_ODD)
		वापस -EINVAL;

	वापस remote_p1_pt == DRM_OF_LVDS_EVEN ?
		DRM_LVDS_DUAL_LINK_EVEN_ODD_PIXELS :
		DRM_LVDS_DUAL_LINK_ODD_EVEN_PIXELS;
पूर्ण
EXPORT_SYMBOL_GPL(drm_of_lvds_get_dual_link_pixel_order);
