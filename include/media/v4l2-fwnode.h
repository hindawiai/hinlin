<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * V4L2 fwnode binding parsing library
 *
 * Copyright (c) 2016 Intel Corporation.
 * Author: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 *
 * Copyright (C) 2012 - 2013 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 *
 * Copyright (C) 2012 Renesas Electronics Corp.
 * Author: Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */
#अगर_अघोषित _V4L2_FWNODE_H
#घोषणा _V4L2_FWNODE_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fwnode.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>

#समावेश <media/v4l2-mediabus.h>

काष्ठा fwnode_handle;
काष्ठा v4l2_async_notअगरier;
काष्ठा v4l2_async_subdev;

#घोषणा V4L2_FWNODE_CSI2_MAX_DATA_LANES	8

/**
 * काष्ठा v4l2_fwnode_bus_mipi_csi2 - MIPI CSI-2 bus data काष्ठाure
 * @flags: media bus (V4L2_MBUS_*) flags
 * @data_lanes: an array of physical data lane indexes
 * @घड़ी_lane: physical lane index of the घड़ी lane
 * @num_data_lanes: number of data lanes
 * @lane_polarities: polarity of the lanes. The order is the same of
 *		   the physical lanes.
 */
काष्ठा v4l2_fwnode_bus_mipi_csi2 अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित अक्षर data_lanes[V4L2_FWNODE_CSI2_MAX_DATA_LANES];
	अचिन्हित अक्षर घड़ी_lane;
	अचिन्हित अक्षर num_data_lanes;
	bool lane_polarities[1 + V4L2_FWNODE_CSI2_MAX_DATA_LANES];
पूर्ण;

/**
 * काष्ठा v4l2_fwnode_bus_parallel - parallel data bus data काष्ठाure
 * @flags: media bus (V4L2_MBUS_*) flags
 * @bus_width: bus width in bits
 * @data_shअगरt: data shअगरt in bits
 */
काष्ठा v4l2_fwnode_bus_parallel अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित अक्षर bus_width;
	अचिन्हित अक्षर data_shअगरt;
पूर्ण;

/**
 * काष्ठा v4l2_fwnode_bus_mipi_csi1 - CSI-1/CCP2 data bus काष्ठाure
 * @घड़ी_inv: polarity of घड़ी/strobe संकेत
 *	       false - not inverted, true - inverted
 * @strobe: false - data/घड़ी, true - data/strobe
 * @lane_polarity: the polarities of the घड़ी (index 0) and data lanes
 *		   index (1)
 * @data_lane: the number of the data lane
 * @घड़ी_lane: the number of the घड़ी lane
 */
काष्ठा v4l2_fwnode_bus_mipi_csi1 अणु
	अचिन्हित अक्षर घड़ी_inv:1;
	अचिन्हित अक्षर strobe:1;
	bool lane_polarity[2];
	अचिन्हित अक्षर data_lane;
	अचिन्हित अक्षर घड़ी_lane;
पूर्ण;

/**
 * काष्ठा v4l2_fwnode_endpoपूर्णांक - the endpoपूर्णांक data काष्ठाure
 * @base: fwnode endpoपूर्णांक of the v4l2_fwnode
 * @bus_type: bus type
 * @bus: bus configuration data काष्ठाure
 * @bus.parallel: embedded &काष्ठा v4l2_fwnode_bus_parallel.
 *		  Used अगर the bus is parallel.
 * @bus.mipi_csi1: embedded &काष्ठा v4l2_fwnode_bus_mipi_csi1.
 *		   Used अगर the bus is MIPI Alliance's Camera Serial
 *		   Interface version 1 (MIPI CSI1) or Standard
 *		   Mobile Imaging Architecture's Compact Camera Port 2
 *		   (SMIA CCP2).
 * @bus.mipi_csi2: embedded &काष्ठा v4l2_fwnode_bus_mipi_csi2.
 *		   Used अगर the bus is MIPI Alliance's Camera Serial
 *		   Interface version 2 (MIPI CSI2).
 * @link_frequencies: array of supported link frequencies
 * @nr_of_link_frequencies: number of elements in link_frequenccies array
 */
काष्ठा v4l2_fwnode_endpoपूर्णांक अणु
	काष्ठा fwnode_endpoपूर्णांक base;
	/*
	 * Fields below this line will be zeroed by
	 * v4l2_fwnode_endpoपूर्णांक_parse()
	 */
	क्रमागत v4l2_mbus_type bus_type;
	काष्ठा अणु
		काष्ठा v4l2_fwnode_bus_parallel parallel;
		काष्ठा v4l2_fwnode_bus_mipi_csi1 mipi_csi1;
		काष्ठा v4l2_fwnode_bus_mipi_csi2 mipi_csi2;
	पूर्ण bus;
	u64 *link_frequencies;
	अचिन्हित पूर्णांक nr_of_link_frequencies;
पूर्ण;

/**
 * V4L2_FWNODE_PROPERTY_UNSET - identअगरy a non initialized property
 *
 * All properties in &काष्ठा v4l2_fwnode_device_properties are initialized
 * to this value.
 */
#घोषणा V4L2_FWNODE_PROPERTY_UNSET   (-1U)

/**
 * क्रमागत v4l2_fwnode_orientation - possible device orientation
 * @V4L2_FWNODE_ORIENTATION_FRONT: device installed on the front side
 * @V4L2_FWNODE_ORIENTATION_BACK: device installed on the back side
 * @V4L2_FWNODE_ORIENTATION_EXTERNAL: device बाह्यally located
 */
क्रमागत v4l2_fwnode_orientation अणु
	V4L2_FWNODE_ORIENTATION_FRONT,
	V4L2_FWNODE_ORIENTATION_BACK,
	V4L2_FWNODE_ORIENTATION_EXTERNAL
पूर्ण;

/**
 * काष्ठा v4l2_fwnode_device_properties - fwnode device properties
 * @orientation: device orientation. See &क्रमागत v4l2_fwnode_orientation
 * @rotation: device rotation
 */
काष्ठा v4l2_fwnode_device_properties अणु
	क्रमागत v4l2_fwnode_orientation orientation;
	अचिन्हित पूर्णांक rotation;
पूर्ण;

/**
 * काष्ठा v4l2_fwnode_link - a link between two endpoपूर्णांकs
 * @local_node: poपूर्णांकer to device_node of this endpoपूर्णांक
 * @local_port: identअगरier of the port this endpoपूर्णांक beदीर्घs to
 * @local_id: identअगरier of the id this endpoपूर्णांक beदीर्घs to
 * @remote_node: poपूर्णांकer to device_node of the remote endpoपूर्णांक
 * @remote_port: identअगरier of the port the remote endpoपूर्णांक beदीर्घs to
 * @remote_id: identअगरier of the id the remote endpoपूर्णांक beदीर्घs to
 */
काष्ठा v4l2_fwnode_link अणु
	काष्ठा fwnode_handle *local_node;
	अचिन्हित पूर्णांक local_port;
	अचिन्हित पूर्णांक local_id;
	काष्ठा fwnode_handle *remote_node;
	अचिन्हित पूर्णांक remote_port;
	अचिन्हित पूर्णांक remote_id;
पूर्ण;

/**
 * क्रमागत v4l2_connector_type - connector type
 * @V4L2_CONN_UNKNOWN:   unknown connector type, no V4L2 connector configuration
 * @V4L2_CONN_COMPOSITE: analog composite connector
 * @V4L2_CONN_SVIDEO:    analog svideo connector
 */
क्रमागत v4l2_connector_type अणु
	V4L2_CONN_UNKNOWN,
	V4L2_CONN_COMPOSITE,
	V4L2_CONN_SVIDEO,
पूर्ण;

/**
 * काष्ठा v4l2_connector_link - connector link data काष्ठाure
 * @head: काष्ठाure to be used to add the link to the
 *        &काष्ठा v4l2_fwnode_connector
 * @fwnode_link: &काष्ठा v4l2_fwnode_link link between the connector and the
 *               device the connector beदीर्घs to.
 */
काष्ठा v4l2_connector_link अणु
	काष्ठा list_head head;
	काष्ठा v4l2_fwnode_link fwnode_link;
पूर्ण;

/**
 * काष्ठा v4l2_fwnode_connector_analog - analog connector data काष्ठाure
 * @sdtv_stds: sdtv standards this connector supports, set to V4L2_STD_ALL
 *             अगर no restrictions are specअगरied.
 */
काष्ठा v4l2_fwnode_connector_analog अणु
	v4l2_std_id sdtv_stds;
पूर्ण;

/**
 * काष्ठा v4l2_fwnode_connector - the connector data काष्ठाure
 * @name: the connector device name
 * @label: optional connector label
 * @type: connector type
 * @links: list of all connector &काष्ठा v4l2_connector_link links
 * @nr_of_links: total number of links
 * @connector: connector configuration
 * @connector.analog: analog connector configuration
 *                    &काष्ठा v4l2_fwnode_connector_analog
 */
काष्ठा v4l2_fwnode_connector अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *label;
	क्रमागत v4l2_connector_type type;
	काष्ठा list_head links;
	अचिन्हित पूर्णांक nr_of_links;

	जोड़ अणु
		काष्ठा v4l2_fwnode_connector_analog analog;
		/* future connectors */
	पूर्ण connector;
पूर्ण;

/**
 * क्रमागत v4l2_fwnode_bus_type - Video bus types defined by firmware properties
 * @V4L2_FWNODE_BUS_TYPE_GUESS: Default value अगर no bus-type fwnode property
 * @V4L2_FWNODE_BUS_TYPE_CSI2_CPHY: MIPI CSI-2 bus, C-PHY physical layer
 * @V4L2_FWNODE_BUS_TYPE_CSI1: MIPI CSI-1 bus
 * @V4L2_FWNODE_BUS_TYPE_CCP2: SMIA Compact Camera Port 2 bus
 * @V4L2_FWNODE_BUS_TYPE_CSI2_DPHY: MIPI CSI-2 bus, D-PHY physical layer
 * @V4L2_FWNODE_BUS_TYPE_PARALLEL: Camera Parallel Interface bus
 * @V4L2_FWNODE_BUS_TYPE_BT656: BT.656 video क्रमmat bus-type
 * @NR_OF_V4L2_FWNODE_BUS_TYPE: Number of bus-types
 */
क्रमागत v4l2_fwnode_bus_type अणु
	V4L2_FWNODE_BUS_TYPE_GUESS = 0,
	V4L2_FWNODE_BUS_TYPE_CSI2_CPHY,
	V4L2_FWNODE_BUS_TYPE_CSI1,
	V4L2_FWNODE_BUS_TYPE_CCP2,
	V4L2_FWNODE_BUS_TYPE_CSI2_DPHY,
	V4L2_FWNODE_BUS_TYPE_PARALLEL,
	V4L2_FWNODE_BUS_TYPE_BT656,
	NR_OF_V4L2_FWNODE_BUS_TYPE
पूर्ण;

/**
 * v4l2_fwnode_endpoपूर्णांक_parse() - parse all fwnode node properties
 * @fwnode: poपूर्णांकer to the endpoपूर्णांक's fwnode handle
 * @vep: poपूर्णांकer to the V4L2 fwnode data काष्ठाure
 *
 * This function parses the V4L2 fwnode endpoपूर्णांक specअगरic parameters from the
 * firmware. There are two ways to use this function, either by letting it
 * obtain the type of the bus (by setting the @vep.bus_type field to
 * V4L2_MBUS_UNKNOWN) or specअगरying the bus type explicitly to one of the &क्रमागत
 * v4l2_mbus_type types.
 *
 * When @vep.bus_type is V4L2_MBUS_UNKNOWN, the function will use the "bus-type"
 * property to determine the type when it is available. The caller is
 * responsible क्रम validating the contents of @vep.bus_type field after the call
 * वापसs.
 *
 * As a deprecated functionality to support older DT bindings without "bus-type"
 * property क्रम devices that support multiple types, अगर the "bus-type" property
 * करोes not exist, the function will attempt to guess the type based on the
 * endpoपूर्णांक properties available. NEVER RELY ON GUESSING THE BUS TYPE IN NEW
 * DRIVERS OR BINDINGS.
 *
 * It is also possible to set @vep.bus_type corresponding to an actual bus. In
 * this हाल the function will only attempt to parse properties related to this
 * bus, and it will वापस an error अगर the value of the "bus-type" property
 * corresponds to a dअगरferent bus.
 *
 * The caller is required to initialise all fields of @vep, either with
 * explicitly values, or by zeroing them.
 *
 * The function करोes not change the V4L2 fwnode endpoपूर्णांक state अगर it fails.
 *
 * NOTE: This function करोes not parse "link-frequencies" property as its size is
 * not known in advance. Please use v4l2_fwnode_endpoपूर्णांक_alloc_parse() अगर you
 * need properties of variable size.
 *
 * Return: %0 on success or a negative error code on failure:
 *	   %-ENOMEM on memory allocation failure
 *	   %-EINVAL on parsing failure
 *	   %-ENXIO on mismatching bus types
 */
पूर्णांक v4l2_fwnode_endpoपूर्णांक_parse(काष्ठा fwnode_handle *fwnode,
			       काष्ठा v4l2_fwnode_endpoपूर्णांक *vep);

/**
 * v4l2_fwnode_endpoपूर्णांक_मुक्त() - मुक्त the V4L2 fwnode acquired by
 * v4l2_fwnode_endpoपूर्णांक_alloc_parse()
 * @vep: the V4L2 fwnode the resources of which are to be released
 *
 * It is safe to call this function with शून्य argument or on a V4L2 fwnode the
 * parsing of which failed.
 */
व्योम v4l2_fwnode_endpoपूर्णांक_मुक्त(काष्ठा v4l2_fwnode_endpoपूर्णांक *vep);

/**
 * v4l2_fwnode_endpoपूर्णांक_alloc_parse() - parse all fwnode node properties
 * @fwnode: poपूर्णांकer to the endpoपूर्णांक's fwnode handle
 * @vep: poपूर्णांकer to the V4L2 fwnode data काष्ठाure
 *
 * This function parses the V4L2 fwnode endpoपूर्णांक specअगरic parameters from the
 * firmware. There are two ways to use this function, either by letting it
 * obtain the type of the bus (by setting the @vep.bus_type field to
 * V4L2_MBUS_UNKNOWN) or specअगरying the bus type explicitly to one of the &क्रमागत
 * v4l2_mbus_type types.
 *
 * When @vep.bus_type is V4L2_MBUS_UNKNOWN, the function will use the "bus-type"
 * property to determine the type when it is available. The caller is
 * responsible क्रम validating the contents of @vep.bus_type field after the call
 * वापसs.
 *
 * As a deprecated functionality to support older DT bindings without "bus-type"
 * property क्रम devices that support multiple types, अगर the "bus-type" property
 * करोes not exist, the function will attempt to guess the type based on the
 * endpoपूर्णांक properties available. NEVER RELY ON GUESSING THE BUS TYPE IN NEW
 * DRIVERS OR BINDINGS.
 *
 * It is also possible to set @vep.bus_type corresponding to an actual bus. In
 * this हाल the function will only attempt to parse properties related to this
 * bus, and it will वापस an error अगर the value of the "bus-type" property
 * corresponds to a dअगरferent bus.
 *
 * The caller is required to initialise all fields of @vep, either with
 * explicitly values, or by zeroing them.
 *
 * The function करोes not change the V4L2 fwnode endpoपूर्णांक state अगर it fails.
 *
 * v4l2_fwnode_endpoपूर्णांक_alloc_parse() has two important dअगरferences to
 * v4l2_fwnode_endpoपूर्णांक_parse():
 *
 * 1. It also parses variable size data.
 *
 * 2. The memory it has allocated to store the variable size data must be मुक्तd
 *    using v4l2_fwnode_endpoपूर्णांक_मुक्त() when no दीर्घer needed.
 *
 * Return: %0 on success or a negative error code on failure:
 *	   %-ENOMEM on memory allocation failure
 *	   %-EINVAL on parsing failure
 *	   %-ENXIO on mismatching bus types
 */
पूर्णांक v4l2_fwnode_endpoपूर्णांक_alloc_parse(काष्ठा fwnode_handle *fwnode,
				     काष्ठा v4l2_fwnode_endpoपूर्णांक *vep);

/**
 * v4l2_fwnode_parse_link() - parse a link between two endpoपूर्णांकs
 * @fwnode: poपूर्णांकer to the endpoपूर्णांक's fwnode at the local end of the link
 * @link: poपूर्णांकer to the V4L2 fwnode link data काष्ठाure
 *
 * Fill the link काष्ठाure with the local and remote nodes and port numbers.
 * The local_node and remote_node fields are set to poपूर्णांक to the local and
 * remote port's parent nodes respectively (the port parent node being the
 * parent node of the port node अगर that node isn't a 'ports' node, or the
 * gअक्रम-parent node of the port node otherwise).
 *
 * A reference is taken to both the local and remote nodes, the caller must use
 * v4l2_fwnode_put_link() to drop the references when करोne with the
 * link.
 *
 * Return: 0 on success, or -ENOLINK अगर the remote endpoपूर्णांक fwnode can't be
 * found.
 */
पूर्णांक v4l2_fwnode_parse_link(काष्ठा fwnode_handle *fwnode,
			   काष्ठा v4l2_fwnode_link *link);

/**
 * v4l2_fwnode_put_link() - drop references to nodes in a link
 * @link: poपूर्णांकer to the V4L2 fwnode link data काष्ठाure
 *
 * Drop references to the local and remote nodes in the link. This function
 * must be called on every link parsed with v4l2_fwnode_parse_link().
 */
व्योम v4l2_fwnode_put_link(काष्ठा v4l2_fwnode_link *link);

/**
 * v4l2_fwnode_connector_मुक्त() - मुक्त the V4L2 connector acquired memory
 * @connector: the V4L2 connector resources of which are to be released
 *
 * Free all allocated memory and put all links acquired by
 * v4l2_fwnode_connector_parse() and v4l2_fwnode_connector_add_link().
 *
 * It is safe to call this function with शून्य argument or on a V4L2 connector
 * the parsing of which failed.
 */
व्योम v4l2_fwnode_connector_मुक्त(काष्ठा v4l2_fwnode_connector *connector);

/**
 * v4l2_fwnode_connector_parse() - initialize the 'struct v4l2_fwnode_connector'
 * @fwnode: poपूर्णांकer to the subdev endpoपूर्णांक's fwnode handle where the connector
 *	    is connected to or to the connector endpoपूर्णांक fwnode handle.
 * @connector: poपूर्णांकer to the V4L2 fwnode connector data काष्ठाure
 *
 * Fill the &काष्ठा v4l2_fwnode_connector with the connector type, label and
 * all &क्रमागत v4l2_connector_type specअगरic connector data. The label is optional
 * so it is set to %शून्य अगर no one was found. The function initialize the links
 * to zero. Adding links to the connector is करोne by calling
 * v4l2_fwnode_connector_add_link().
 *
 * The memory allocated क्रम the label must be मुक्तd when no दीर्घer needed.
 * Freeing the memory is करोne by v4l2_fwnode_connector_मुक्त().
 *
 * Return:
 * * %0 on success or a negative error code on failure:
 * * %-EINVAL अगर @fwnode is invalid
 * * %-ENOTCONN अगर connector type is unknown or connector device can't be found
 */
पूर्णांक v4l2_fwnode_connector_parse(काष्ठा fwnode_handle *fwnode,
				काष्ठा v4l2_fwnode_connector *connector);

/**
 * v4l2_fwnode_connector_add_link - add a link between a connector node and
 *				    a v4l2-subdev node.
 * @fwnode: poपूर्णांकer to the subdev endpoपूर्णांक's fwnode handle where the connector
 *          is connected to
 * @connector: poपूर्णांकer to the V4L2 fwnode connector data काष्ठाure
 *
 * Add a new &काष्ठा v4l2_connector_link link to the
 * &काष्ठा v4l2_fwnode_connector connector links list. The link local_node
 * poपूर्णांकs to the connector node, the remote_node to the host v4l2 (sub)dev.
 *
 * The taken references to remote_node and local_node must be dropped and the
 * allocated memory must be मुक्तd when no दीर्घer needed. Both is करोne by calling
 * v4l2_fwnode_connector_मुक्त().
 *
 * Return:
 * * %0 on success or a negative error code on failure:
 * * %-EINVAL अगर @fwnode or @connector is invalid or @connector type is unknown
 * * %-ENOMEM on link memory allocation failure
 * * %-ENOTCONN अगर remote connector device can't be found
 * * %-ENOLINK अगर link parsing between v4l2 (sub)dev and connector fails
 */
पूर्णांक v4l2_fwnode_connector_add_link(काष्ठा fwnode_handle *fwnode,
				   काष्ठा v4l2_fwnode_connector *connector);

/**
 * v4l2_fwnode_device_parse() - parse fwnode device properties
 * @dev: poपूर्णांकer to &काष्ठा device
 * @props: poपूर्णांकer to &काष्ठा v4l2_fwnode_device_properties where to store the
 *	   parsed properties values
 *
 * This function parses and validates the V4L2 fwnode device properties from the
 * firmware पूर्णांकerface, and fills the @काष्ठा v4l2_fwnode_device_properties
 * provided by the caller.
 *
 * Return:
 *	% 0 on success
 *	%-EINVAL अगर a parsed property value is not valid
 */
पूर्णांक v4l2_fwnode_device_parse(काष्ठा device *dev,
			     काष्ठा v4l2_fwnode_device_properties *props);

/**
 * प्रकार parse_endpoपूर्णांक_func - Driver's callback function to be called on
 *	each V4L2 fwnode endpoपूर्णांक.
 *
 * @dev: poपूर्णांकer to &काष्ठा device
 * @vep: poपूर्णांकer to &काष्ठा v4l2_fwnode_endpoपूर्णांक
 * @asd: poपूर्णांकer to &काष्ठा v4l2_async_subdev
 *
 * Return:
 * * %0 on success
 * * %-ENOTCONN अगर the endpoपूर्णांक is to be skipped but this
 *   should not be considered as an error
 * * %-EINVAL अगर the endpoपूर्णांक configuration is invalid
 */
प्रकार पूर्णांक (*parse_endpoपूर्णांक_func)(काष्ठा device *dev,
				  काष्ठा v4l2_fwnode_endpoपूर्णांक *vep,
				  काष्ठा v4l2_async_subdev *asd);

/**
 * v4l2_async_notअगरier_parse_fwnode_endpoपूर्णांकs - Parse V4L2 fwnode endpoपूर्णांकs in a
 *						device node
 * @dev: the device the endpoपूर्णांकs of which are to be parsed
 * @notअगरier: notअगरier क्रम @dev
 * @asd_काष्ठा_size: size of the driver's async sub-device काष्ठा, including
 *		     माप(काष्ठा v4l2_async_subdev). The &काष्ठा
 *		     v4l2_async_subdev shall be the first member of
 *		     the driver's async sub-device काष्ठा, i.e. both
 *		     begin at the same memory address.
 * @parse_endpoपूर्णांक: Driver's callback function called on each V4L2 fwnode
 *		    endpoपूर्णांक. Optional.
 *
 * DEPRECATED! This function is deprecated. Don't use it in new drivers.
 * Instead see an example in cio2_parse_firmware() function in
 * drivers/media/pci/पूर्णांकel/ipu3/ipu3-cio2.c .
 *
 * Parse the fwnode endpoपूर्णांकs of the @dev device and populate the async sub-
 * devices list in the notअगरier. The @parse_endpoपूर्णांक callback function is
 * called क्रम each endpoपूर्णांक with the corresponding async sub-device poपूर्णांकer to
 * let the caller initialize the driver-specअगरic part of the async sub-device
 * काष्ठाure.
 *
 * The notअगरier memory shall be zeroed beक्रमe this function is called on the
 * notअगरier.
 *
 * This function may not be called on a रेजिस्टरed notअगरier and may be called on
 * a notअगरier only once.
 *
 * The &काष्ठा v4l2_fwnode_endpoपूर्णांक passed to the callback function
 * @parse_endpoपूर्णांक is released once the function is finished. If there is a need
 * to retain that configuration, the user needs to allocate memory क्रम it.
 *
 * Any notअगरier populated using this function must be released with a call to
 * v4l2_async_notअगरier_cleanup() after it has been unरेजिस्टरed and the async
 * sub-devices are no दीर्घer in use, even अगर the function वापसed an error.
 *
 * Return: %0 on success, including when no async sub-devices are found
 *	   %-ENOMEM अगर memory allocation failed
 *	   %-EINVAL अगर graph or endpoपूर्णांक parsing failed
 *	   Other error codes as वापसed by @parse_endpoपूर्णांक
 */
पूर्णांक
v4l2_async_notअगरier_parse_fwnode_endpoपूर्णांकs(काष्ठा device *dev,
					   काष्ठा v4l2_async_notअगरier *notअगरier,
					   माप_प्रकार asd_काष्ठा_size,
					   parse_endpoपूर्णांक_func parse_endpoपूर्णांक);

/* Helper macros to access the connector links. */

/** v4l2_connector_last_link - Helper macro to get the first
 *                             &काष्ठा v4l2_fwnode_connector link
 * @v4l2c: &काष्ठा v4l2_fwnode_connector owning the connector links
 *
 * This marco वापसs the first added &काष्ठा v4l2_connector_link connector
 * link or @शून्य अगर the connector has no links.
 */
#घोषणा v4l2_connector_first_link(v4l2c)				       \
	list_first_entry_or_null(&(v4l2c)->links,			       \
				 काष्ठा v4l2_connector_link, head)

/** v4l2_connector_last_link - Helper macro to get the last
 *                             &काष्ठा v4l2_fwnode_connector link
 * @v4l2c: &काष्ठा v4l2_fwnode_connector owning the connector links
 *
 * This marco वापसs the last &काष्ठा v4l2_connector_link added connector link.
 */
#घोषणा v4l2_connector_last_link(v4l2c)					       \
	list_last_entry(&(v4l2c)->links, काष्ठा v4l2_connector_link, head)

#पूर्ण_अगर /* _V4L2_FWNODE_H */
