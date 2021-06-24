<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * V4L2 fwnode binding parsing library
 *
 * The origins of the V4L2 fwnode library are in V4L2 OF library that
 * क्रमmerly was located in v4l2-of.c.
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
#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

अटल स्थिर काष्ठा v4l2_fwnode_bus_conv अणु
	क्रमागत v4l2_fwnode_bus_type fwnode_bus_type;
	क्रमागत v4l2_mbus_type mbus_type;
	स्थिर अक्षर *name;
पूर्ण buses[] = अणु
	अणु
		V4L2_FWNODE_BUS_TYPE_GUESS,
		V4L2_MBUS_UNKNOWN,
		"not specified",
	पूर्ण, अणु
		V4L2_FWNODE_BUS_TYPE_CSI2_CPHY,
		V4L2_MBUS_CSI2_CPHY,
		"MIPI CSI-2 C-PHY",
	पूर्ण, अणु
		V4L2_FWNODE_BUS_TYPE_CSI1,
		V4L2_MBUS_CSI1,
		"MIPI CSI-1",
	पूर्ण, अणु
		V4L2_FWNODE_BUS_TYPE_CCP2,
		V4L2_MBUS_CCP2,
		"compact camera port 2",
	पूर्ण, अणु
		V4L2_FWNODE_BUS_TYPE_CSI2_DPHY,
		V4L2_MBUS_CSI2_DPHY,
		"MIPI CSI-2 D-PHY",
	पूर्ण, अणु
		V4L2_FWNODE_BUS_TYPE_PARALLEL,
		V4L2_MBUS_PARALLEL,
		"parallel",
	पूर्ण, अणु
		V4L2_FWNODE_BUS_TYPE_BT656,
		V4L2_MBUS_BT656,
		"Bt.656",
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा v4l2_fwnode_bus_conv *
get_v4l2_fwnode_bus_conv_by_fwnode_bus(क्रमागत v4l2_fwnode_bus_type type)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(buses); i++)
		अगर (buses[i].fwnode_bus_type == type)
			वापस &buses[i];

	वापस शून्य;
पूर्ण

अटल क्रमागत v4l2_mbus_type
v4l2_fwnode_bus_type_to_mbus(क्रमागत v4l2_fwnode_bus_type type)
अणु
	स्थिर काष्ठा v4l2_fwnode_bus_conv *conv =
		get_v4l2_fwnode_bus_conv_by_fwnode_bus(type);

	वापस conv ? conv->mbus_type : V4L2_MBUS_INVALID;
पूर्ण

अटल स्थिर अक्षर *
v4l2_fwnode_bus_type_to_string(क्रमागत v4l2_fwnode_bus_type type)
अणु
	स्थिर काष्ठा v4l2_fwnode_bus_conv *conv =
		get_v4l2_fwnode_bus_conv_by_fwnode_bus(type);

	वापस conv ? conv->name : "not found";
पूर्ण

अटल स्थिर काष्ठा v4l2_fwnode_bus_conv *
get_v4l2_fwnode_bus_conv_by_mbus(क्रमागत v4l2_mbus_type type)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(buses); i++)
		अगर (buses[i].mbus_type == type)
			वापस &buses[i];

	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *
v4l2_fwnode_mbus_type_to_string(क्रमागत v4l2_mbus_type type)
अणु
	स्थिर काष्ठा v4l2_fwnode_bus_conv *conv =
		get_v4l2_fwnode_bus_conv_by_mbus(type);

	वापस conv ? conv->name : "not found";
पूर्ण

अटल पूर्णांक v4l2_fwnode_endpoपूर्णांक_parse_csi2_bus(काष्ठा fwnode_handle *fwnode,
					       काष्ठा v4l2_fwnode_endpoपूर्णांक *vep,
					       क्रमागत v4l2_mbus_type bus_type)
अणु
	काष्ठा v4l2_fwnode_bus_mipi_csi2 *bus = &vep->bus.mipi_csi2;
	bool have_clk_lane = false, have_data_lanes = false,
		have_lane_polarities = false;
	अचिन्हित पूर्णांक flags = 0, lanes_used = 0;
	u32 array[1 + V4L2_FWNODE_CSI2_MAX_DATA_LANES];
	u32 घड़ी_lane = 0;
	अचिन्हित पूर्णांक num_data_lanes = 0;
	bool use_शेष_lane_mapping = false;
	अचिन्हित पूर्णांक i;
	u32 v;
	पूर्णांक rval;

	अगर (bus_type == V4L2_MBUS_CSI2_DPHY ||
	    bus_type == V4L2_MBUS_CSI2_CPHY) अणु
		use_शेष_lane_mapping = true;

		num_data_lanes = min_t(u32, bus->num_data_lanes,
				       V4L2_FWNODE_CSI2_MAX_DATA_LANES);

		घड़ी_lane = bus->घड़ी_lane;
		अगर (घड़ी_lane)
			use_शेष_lane_mapping = false;

		क्रम (i = 0; i < num_data_lanes; i++) अणु
			array[i] = bus->data_lanes[i];
			अगर (array[i])
				use_शेष_lane_mapping = false;
		पूर्ण

		अगर (use_शेष_lane_mapping)
			pr_debug("no lane mapping given, using defaults\n");
	पूर्ण

	rval = fwnode_property_count_u32(fwnode, "data-lanes");
	अगर (rval > 0) अणु
		num_data_lanes =
			min_t(पूर्णांक, V4L2_FWNODE_CSI2_MAX_DATA_LANES, rval);

		fwnode_property_पढ़ो_u32_array(fwnode, "data-lanes", array,
					       num_data_lanes);

		have_data_lanes = true;
		अगर (use_शेष_lane_mapping) अणु
			pr_debug("data-lanes property exists; disabling default mapping\n");
			use_शेष_lane_mapping = false;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_data_lanes; i++) अणु
		अगर (lanes_used & BIT(array[i])) अणु
			अगर (have_data_lanes || !use_शेष_lane_mapping)
				pr_warn("duplicated lane %u in data-lanes, using defaults\n",
					array[i]);
			use_शेष_lane_mapping = true;
		पूर्ण
		lanes_used |= BIT(array[i]);

		अगर (have_data_lanes)
			pr_debug("lane %u position %u\n", i, array[i]);
	पूर्ण

	rval = fwnode_property_count_u32(fwnode, "lane-polarities");
	अगर (rval > 0) अणु
		अगर (rval != 1 + num_data_lanes /* घड़ी+data */) अणु
			pr_warn("invalid number of lane-polarities entries (need %u, got %u)\n",
				1 + num_data_lanes, rval);
			वापस -EINVAL;
		पूर्ण

		have_lane_polarities = true;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "clock-lanes", &v)) अणु
		घड़ी_lane = v;
		pr_debug("clock lane position %u\n", v);
		have_clk_lane = true;
	पूर्ण

	अगर (have_clk_lane && lanes_used & BIT(घड़ी_lane) &&
	    !use_शेष_lane_mapping) अणु
		pr_warn("duplicated lane %u in clock-lanes, using defaults\n",
			v);
		use_शेष_lane_mapping = true;
	पूर्ण

	अगर (fwnode_property_present(fwnode, "clock-noncontinuous")) अणु
		flags |= V4L2_MBUS_CSI2_NONCONTINUOUS_CLOCK;
		pr_debug("non-continuous clock\n");
	पूर्ण अन्यथा अणु
		flags |= V4L2_MBUS_CSI2_CONTINUOUS_CLOCK;
	पूर्ण

	अगर (bus_type == V4L2_MBUS_CSI2_DPHY ||
	    bus_type == V4L2_MBUS_CSI2_CPHY || lanes_used ||
	    have_clk_lane || (flags & ~V4L2_MBUS_CSI2_CONTINUOUS_CLOCK)) अणु
		/* Only D-PHY has a घड़ी lane. */
		अचिन्हित पूर्णांक dfl_data_lane_index =
			bus_type == V4L2_MBUS_CSI2_DPHY;

		bus->flags = flags;
		अगर (bus_type == V4L2_MBUS_UNKNOWN)
			vep->bus_type = V4L2_MBUS_CSI2_DPHY;
		bus->num_data_lanes = num_data_lanes;

		अगर (use_शेष_lane_mapping) अणु
			bus->घड़ी_lane = 0;
			क्रम (i = 0; i < num_data_lanes; i++)
				bus->data_lanes[i] = dfl_data_lane_index + i;
		पूर्ण अन्यथा अणु
			bus->घड़ी_lane = घड़ी_lane;
			क्रम (i = 0; i < num_data_lanes; i++)
				bus->data_lanes[i] = array[i];
		पूर्ण

		अगर (have_lane_polarities) अणु
			fwnode_property_पढ़ो_u32_array(fwnode,
						       "lane-polarities", array,
						       1 + num_data_lanes);

			क्रम (i = 0; i < 1 + num_data_lanes; i++) अणु
				bus->lane_polarities[i] = array[i];
				pr_debug("lane %u polarity %sinverted",
					 i, array[i] ? "" : "not ");
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_debug("no lane polarities defined, assuming not inverted\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा PARALLEL_MBUS_FLAGS (V4L2_MBUS_HSYNC_ACTIVE_HIGH |	\
			     V4L2_MBUS_HSYNC_ACTIVE_LOW |	\
			     V4L2_MBUS_VSYNC_ACTIVE_HIGH |	\
			     V4L2_MBUS_VSYNC_ACTIVE_LOW |	\
			     V4L2_MBUS_FIELD_EVEN_HIGH |	\
			     V4L2_MBUS_FIELD_EVEN_LOW)

अटल व्योम
v4l2_fwnode_endpoपूर्णांक_parse_parallel_bus(काष्ठा fwnode_handle *fwnode,
					काष्ठा v4l2_fwnode_endpoपूर्णांक *vep,
					क्रमागत v4l2_mbus_type bus_type)
अणु
	काष्ठा v4l2_fwnode_bus_parallel *bus = &vep->bus.parallel;
	अचिन्हित पूर्णांक flags = 0;
	u32 v;

	अगर (bus_type == V4L2_MBUS_PARALLEL || bus_type == V4L2_MBUS_BT656)
		flags = bus->flags;

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "hsync-active", &v)) अणु
		flags &= ~(V4L2_MBUS_HSYNC_ACTIVE_HIGH |
			   V4L2_MBUS_HSYNC_ACTIVE_LOW);
		flags |= v ? V4L2_MBUS_HSYNC_ACTIVE_HIGH :
			V4L2_MBUS_HSYNC_ACTIVE_LOW;
		pr_debug("hsync-active %s\n", v ? "high" : "low");
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "vsync-active", &v)) अणु
		flags &= ~(V4L2_MBUS_VSYNC_ACTIVE_HIGH |
			   V4L2_MBUS_VSYNC_ACTIVE_LOW);
		flags |= v ? V4L2_MBUS_VSYNC_ACTIVE_HIGH :
			V4L2_MBUS_VSYNC_ACTIVE_LOW;
		pr_debug("vsync-active %s\n", v ? "high" : "low");
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "field-even-active", &v)) अणु
		flags &= ~(V4L2_MBUS_FIELD_EVEN_HIGH |
			   V4L2_MBUS_FIELD_EVEN_LOW);
		flags |= v ? V4L2_MBUS_FIELD_EVEN_HIGH :
			V4L2_MBUS_FIELD_EVEN_LOW;
		pr_debug("field-even-active %s\n", v ? "high" : "low");
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "pclk-sample", &v)) अणु
		flags &= ~(V4L2_MBUS_PCLK_SAMPLE_RISING |
			   V4L2_MBUS_PCLK_SAMPLE_FALLING);
		flags |= v ? V4L2_MBUS_PCLK_SAMPLE_RISING :
			V4L2_MBUS_PCLK_SAMPLE_FALLING;
		pr_debug("pclk-sample %s\n", v ? "high" : "low");
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "data-active", &v)) अणु
		flags &= ~(V4L2_MBUS_DATA_ACTIVE_HIGH |
			   V4L2_MBUS_DATA_ACTIVE_LOW);
		flags |= v ? V4L2_MBUS_DATA_ACTIVE_HIGH :
			V4L2_MBUS_DATA_ACTIVE_LOW;
		pr_debug("data-active %s\n", v ? "high" : "low");
	पूर्ण

	अगर (fwnode_property_present(fwnode, "slave-mode")) अणु
		pr_debug("slave mode\n");
		flags &= ~V4L2_MBUS_MASTER;
		flags |= V4L2_MBUS_SLAVE;
	पूर्ण अन्यथा अणु
		flags &= ~V4L2_MBUS_SLAVE;
		flags |= V4L2_MBUS_MASTER;
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "bus-width", &v)) अणु
		bus->bus_width = v;
		pr_debug("bus-width %u\n", v);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "data-shift", &v)) अणु
		bus->data_shअगरt = v;
		pr_debug("data-shift %u\n", v);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "sync-on-green-active", &v)) अणु
		flags &= ~(V4L2_MBUS_VIDEO_SOG_ACTIVE_HIGH |
			   V4L2_MBUS_VIDEO_SOG_ACTIVE_LOW);
		flags |= v ? V4L2_MBUS_VIDEO_SOG_ACTIVE_HIGH :
			V4L2_MBUS_VIDEO_SOG_ACTIVE_LOW;
		pr_debug("sync-on-green-active %s\n", v ? "high" : "low");
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "data-enable-active", &v)) अणु
		flags &= ~(V4L2_MBUS_DATA_ENABLE_HIGH |
			   V4L2_MBUS_DATA_ENABLE_LOW);
		flags |= v ? V4L2_MBUS_DATA_ENABLE_HIGH :
			V4L2_MBUS_DATA_ENABLE_LOW;
		pr_debug("data-enable-active %s\n", v ? "high" : "low");
	पूर्ण

	चयन (bus_type) अणु
	शेष:
		bus->flags = flags;
		अगर (flags & PARALLEL_MBUS_FLAGS)
			vep->bus_type = V4L2_MBUS_PARALLEL;
		अन्यथा
			vep->bus_type = V4L2_MBUS_BT656;
		अवरोध;
	हाल V4L2_MBUS_PARALLEL:
		vep->bus_type = V4L2_MBUS_PARALLEL;
		bus->flags = flags;
		अवरोध;
	हाल V4L2_MBUS_BT656:
		vep->bus_type = V4L2_MBUS_BT656;
		bus->flags = flags & ~PARALLEL_MBUS_FLAGS;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
v4l2_fwnode_endpoपूर्णांक_parse_csi1_bus(काष्ठा fwnode_handle *fwnode,
				    काष्ठा v4l2_fwnode_endpoपूर्णांक *vep,
				    क्रमागत v4l2_mbus_type bus_type)
अणु
	काष्ठा v4l2_fwnode_bus_mipi_csi1 *bus = &vep->bus.mipi_csi1;
	u32 v;

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "clock-inv", &v)) अणु
		bus->घड़ी_inv = v;
		pr_debug("clock-inv %u\n", v);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "strobe", &v)) अणु
		bus->strobe = v;
		pr_debug("strobe %u\n", v);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "data-lanes", &v)) अणु
		bus->data_lane = v;
		pr_debug("data-lanes %u\n", v);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "clock-lanes", &v)) अणु
		bus->घड़ी_lane = v;
		pr_debug("clock-lanes %u\n", v);
	पूर्ण

	अगर (bus_type == V4L2_MBUS_CCP2)
		vep->bus_type = V4L2_MBUS_CCP2;
	अन्यथा
		vep->bus_type = V4L2_MBUS_CSI1;
पूर्ण

अटल पूर्णांक __v4l2_fwnode_endpoपूर्णांक_parse(काष्ठा fwnode_handle *fwnode,
					काष्ठा v4l2_fwnode_endpoपूर्णांक *vep)
अणु
	u32 bus_type = V4L2_FWNODE_BUS_TYPE_GUESS;
	क्रमागत v4l2_mbus_type mbus_type;
	पूर्णांक rval;

	pr_debug("===== begin parsing endpoint %pfw\n", fwnode);

	fwnode_property_पढ़ो_u32(fwnode, "bus-type", &bus_type);
	pr_debug("fwnode video bus type %s (%u), mbus type %s (%u)\n",
		 v4l2_fwnode_bus_type_to_string(bus_type), bus_type,
		 v4l2_fwnode_mbus_type_to_string(vep->bus_type),
		 vep->bus_type);
	mbus_type = v4l2_fwnode_bus_type_to_mbus(bus_type);
	अगर (mbus_type == V4L2_MBUS_INVALID) अणु
		pr_debug("unsupported bus type %u\n", bus_type);
		वापस -EINVAL;
	पूर्ण

	अगर (vep->bus_type != V4L2_MBUS_UNKNOWN) अणु
		अगर (mbus_type != V4L2_MBUS_UNKNOWN &&
		    vep->bus_type != mbus_type) अणु
			pr_debug("expecting bus type %s\n",
				 v4l2_fwnode_mbus_type_to_string(vep->bus_type));
			वापस -ENXIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		vep->bus_type = mbus_type;
	पूर्ण

	चयन (vep->bus_type) अणु
	हाल V4L2_MBUS_UNKNOWN:
		rval = v4l2_fwnode_endpoपूर्णांक_parse_csi2_bus(fwnode, vep,
							   V4L2_MBUS_UNKNOWN);
		अगर (rval)
			वापस rval;

		अगर (vep->bus_type == V4L2_MBUS_UNKNOWN)
			v4l2_fwnode_endpoपूर्णांक_parse_parallel_bus(fwnode, vep,
								V4L2_MBUS_UNKNOWN);

		pr_debug("assuming media bus type %s (%u)\n",
			 v4l2_fwnode_mbus_type_to_string(vep->bus_type),
			 vep->bus_type);

		अवरोध;
	हाल V4L2_MBUS_CCP2:
	हाल V4L2_MBUS_CSI1:
		v4l2_fwnode_endpoपूर्णांक_parse_csi1_bus(fwnode, vep, vep->bus_type);

		अवरोध;
	हाल V4L2_MBUS_CSI2_DPHY:
	हाल V4L2_MBUS_CSI2_CPHY:
		rval = v4l2_fwnode_endpoपूर्णांक_parse_csi2_bus(fwnode, vep,
							   vep->bus_type);
		अगर (rval)
			वापस rval;

		अवरोध;
	हाल V4L2_MBUS_PARALLEL:
	हाल V4L2_MBUS_BT656:
		v4l2_fwnode_endpoपूर्णांक_parse_parallel_bus(fwnode, vep,
							vep->bus_type);

		अवरोध;
	शेष:
		pr_warn("unsupported bus type %u\n", mbus_type);
		वापस -EINVAL;
	पूर्ण

	fwnode_graph_parse_endpoपूर्णांक(fwnode, &vep->base);

	वापस 0;
पूर्ण

पूर्णांक v4l2_fwnode_endpoपूर्णांक_parse(काष्ठा fwnode_handle *fwnode,
			       काष्ठा v4l2_fwnode_endpoपूर्णांक *vep)
अणु
	पूर्णांक ret;

	ret = __v4l2_fwnode_endpoपूर्णांक_parse(fwnode, vep);

	pr_debug("===== end parsing endpoint %pfw\n", fwnode);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fwnode_endpoपूर्णांक_parse);

व्योम v4l2_fwnode_endpoपूर्णांक_मुक्त(काष्ठा v4l2_fwnode_endpoपूर्णांक *vep)
अणु
	अगर (IS_ERR_OR_शून्य(vep))
		वापस;

	kमुक्त(vep->link_frequencies);
	vep->link_frequencies = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fwnode_endpoपूर्णांक_मुक्त);

पूर्णांक v4l2_fwnode_endpoपूर्णांक_alloc_parse(काष्ठा fwnode_handle *fwnode,
				     काष्ठा v4l2_fwnode_endpoपूर्णांक *vep)
अणु
	पूर्णांक rval;

	rval = __v4l2_fwnode_endpoपूर्णांक_parse(fwnode, vep);
	अगर (rval < 0)
		वापस rval;

	rval = fwnode_property_count_u64(fwnode, "link-frequencies");
	अगर (rval > 0) अणु
		अचिन्हित पूर्णांक i;

		vep->link_frequencies =
			kदो_स्मृति_array(rval, माप(*vep->link_frequencies),
				      GFP_KERNEL);
		अगर (!vep->link_frequencies)
			वापस -ENOMEM;

		vep->nr_of_link_frequencies = rval;

		rval = fwnode_property_पढ़ो_u64_array(fwnode,
						      "link-frequencies",
						      vep->link_frequencies,
						      vep->nr_of_link_frequencies);
		अगर (rval < 0) अणु
			v4l2_fwnode_endpoपूर्णांक_मुक्त(vep);
			वापस rval;
		पूर्ण

		क्रम (i = 0; i < vep->nr_of_link_frequencies; i++)
			pr_debug("link-frequencies %u value %llu\n", i,
				 vep->link_frequencies[i]);
	पूर्ण

	pr_debug("===== end parsing endpoint %pfw\n", fwnode);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fwnode_endpoपूर्णांक_alloc_parse);

पूर्णांक v4l2_fwnode_parse_link(काष्ठा fwnode_handle *fwnode,
			   काष्ठा v4l2_fwnode_link *link)
अणु
	काष्ठा fwnode_endpoपूर्णांक fwep;

	स_रखो(link, 0, माप(*link));

	fwnode_graph_parse_endpoपूर्णांक(fwnode, &fwep);
	link->local_id = fwep.id;
	link->local_port = fwep.port;
	link->local_node = fwnode_graph_get_port_parent(fwnode);

	fwnode = fwnode_graph_get_remote_endpoपूर्णांक(fwnode);
	अगर (!fwnode) अणु
		fwnode_handle_put(fwnode);
		वापस -ENOLINK;
	पूर्ण

	fwnode_graph_parse_endpoपूर्णांक(fwnode, &fwep);
	link->remote_id = fwep.id;
	link->remote_port = fwep.port;
	link->remote_node = fwnode_graph_get_port_parent(fwnode);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fwnode_parse_link);

व्योम v4l2_fwnode_put_link(काष्ठा v4l2_fwnode_link *link)
अणु
	fwnode_handle_put(link->local_node);
	fwnode_handle_put(link->remote_node);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fwnode_put_link);

अटल स्थिर काष्ठा v4l2_fwnode_connector_conv अणु
	क्रमागत v4l2_connector_type type;
	स्थिर अक्षर *compatible;
पूर्ण connectors[] = अणु
	अणु
		.type = V4L2_CONN_COMPOSITE,
		.compatible = "composite-video-connector",
	पूर्ण, अणु
		.type = V4L2_CONN_SVIDEO,
		.compatible = "svideo-connector",
	पूर्ण,
पूर्ण;

अटल क्रमागत v4l2_connector_type
v4l2_fwnode_string_to_connector_type(स्थिर अक्षर *con_str)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(connectors); i++)
		अगर (!म_भेद(con_str, connectors[i].compatible))
			वापस connectors[i].type;

	वापस V4L2_CONN_UNKNOWN;
पूर्ण

अटल व्योम
v4l2_fwnode_connector_parse_analog(काष्ठा fwnode_handle *fwnode,
				   काष्ठा v4l2_fwnode_connector *vc)
अणु
	u32 stds;
	पूर्णांक ret;

	ret = fwnode_property_पढ़ो_u32(fwnode, "sdtv-standards", &stds);

	/* The property is optional. */
	vc->connector.analog.sdtv_stds = ret ? V4L2_STD_ALL : stds;
पूर्ण

व्योम v4l2_fwnode_connector_मुक्त(काष्ठा v4l2_fwnode_connector *connector)
अणु
	काष्ठा v4l2_connector_link *link, *पंचांगp;

	अगर (IS_ERR_OR_शून्य(connector) || connector->type == V4L2_CONN_UNKNOWN)
		वापस;

	list_क्रम_each_entry_safe(link, पंचांगp, &connector->links, head) अणु
		v4l2_fwnode_put_link(&link->fwnode_link);
		list_del(&link->head);
		kमुक्त(link);
	पूर्ण

	kमुक्त(connector->label);
	connector->label = शून्य;
	connector->type = V4L2_CONN_UNKNOWN;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fwnode_connector_मुक्त);

अटल क्रमागत v4l2_connector_type
v4l2_fwnode_get_connector_type(काष्ठा fwnode_handle *fwnode)
अणु
	स्थिर अक्षर *type_name;
	पूर्णांक err;

	अगर (!fwnode)
		वापस V4L2_CONN_UNKNOWN;

	/* The connector-type is stored within the compatible string. */
	err = fwnode_property_पढ़ो_string(fwnode, "compatible", &type_name);
	अगर (err)
		वापस V4L2_CONN_UNKNOWN;

	वापस v4l2_fwnode_string_to_connector_type(type_name);
पूर्ण

पूर्णांक v4l2_fwnode_connector_parse(काष्ठा fwnode_handle *fwnode,
				काष्ठा v4l2_fwnode_connector *connector)
अणु
	काष्ठा fwnode_handle *connector_node;
	क्रमागत v4l2_connector_type connector_type;
	स्थिर अक्षर *label;
	पूर्णांक err;

	अगर (!fwnode)
		वापस -EINVAL;

	स_रखो(connector, 0, माप(*connector));

	INIT_LIST_HEAD(&connector->links);

	connector_node = fwnode_graph_get_port_parent(fwnode);
	connector_type = v4l2_fwnode_get_connector_type(connector_node);
	अगर (connector_type == V4L2_CONN_UNKNOWN) अणु
		fwnode_handle_put(connector_node);
		connector_node = fwnode_graph_get_remote_port_parent(fwnode);
		connector_type = v4l2_fwnode_get_connector_type(connector_node);
	पूर्ण

	अगर (connector_type == V4L2_CONN_UNKNOWN) अणु
		pr_err("Unknown connector type\n");
		err = -ENOTCONN;
		जाओ out;
	पूर्ण

	connector->type = connector_type;
	connector->name = fwnode_get_name(connector_node);
	err = fwnode_property_पढ़ो_string(connector_node, "label", &label);
	connector->label = err ? शून्य : kstrdup_स्थिर(label, GFP_KERNEL);

	/* Parse the connector specअगरic properties. */
	चयन (connector->type) अणु
	हाल V4L2_CONN_COMPOSITE:
	हाल V4L2_CONN_SVIDEO:
		v4l2_fwnode_connector_parse_analog(connector_node, connector);
		अवरोध;
	/* Aव्योम compiler warnings */
	हाल V4L2_CONN_UNKNOWN:
		अवरोध;
	पूर्ण

out:
	fwnode_handle_put(connector_node);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fwnode_connector_parse);

पूर्णांक v4l2_fwnode_connector_add_link(काष्ठा fwnode_handle *fwnode,
				   काष्ठा v4l2_fwnode_connector *connector)
अणु
	काष्ठा fwnode_handle *connector_ep;
	काष्ठा v4l2_connector_link *link;
	पूर्णांक err;

	अगर (!fwnode || !connector || connector->type == V4L2_CONN_UNKNOWN)
		वापस -EINVAL;

	connector_ep = fwnode_graph_get_remote_endpoपूर्णांक(fwnode);
	अगर (!connector_ep)
		वापस -ENOTCONN;

	link = kzalloc(माप(*link), GFP_KERNEL);
	अगर (!link) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	err = v4l2_fwnode_parse_link(connector_ep, &link->fwnode_link);
	अगर (err)
		जाओ err;

	fwnode_handle_put(connector_ep);

	list_add(&link->head, &connector->links);
	connector->nr_of_links++;

	वापस 0;

err:
	kमुक्त(link);
	fwnode_handle_put(connector_ep);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fwnode_connector_add_link);

पूर्णांक v4l2_fwnode_device_parse(काष्ठा device *dev,
			     काष्ठा v4l2_fwnode_device_properties *props)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	u32 val;
	पूर्णांक ret;

	स_रखो(props, 0, माप(*props));

	props->orientation = V4L2_FWNODE_PROPERTY_UNSET;
	ret = fwnode_property_पढ़ो_u32(fwnode, "orientation", &val);
	अगर (!ret) अणु
		चयन (val) अणु
		हाल V4L2_FWNODE_ORIENTATION_FRONT:
		हाल V4L2_FWNODE_ORIENTATION_BACK:
		हाल V4L2_FWNODE_ORIENTATION_EXTERNAL:
			अवरोध;
		शेष:
			dev_warn(dev, "Unsupported device orientation: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		props->orientation = val;
		dev_dbg(dev, "device orientation: %u\n", val);
	पूर्ण

	props->rotation = V4L2_FWNODE_PROPERTY_UNSET;
	ret = fwnode_property_पढ़ो_u32(fwnode, "rotation", &val);
	अगर (!ret) अणु
		अगर (val >= 360) अणु
			dev_warn(dev, "Unsupported device rotation: %u\n", val);
			वापस -EINVAL;
		पूर्ण

		props->rotation = val;
		dev_dbg(dev, "device rotation: %u\n", val);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fwnode_device_parse);

अटल पूर्णांक
v4l2_async_notअगरier_fwnode_parse_endpoपूर्णांक(काष्ठा device *dev,
					  काष्ठा v4l2_async_notअगरier *notअगरier,
					  काष्ठा fwnode_handle *endpoपूर्णांक,
					  अचिन्हित पूर्णांक asd_काष्ठा_size,
					  parse_endpoपूर्णांक_func parse_endpoपूर्णांक)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु .bus_type = 0 पूर्ण;
	काष्ठा v4l2_async_subdev *asd;
	पूर्णांक ret;

	asd = kzalloc(asd_काष्ठा_size, GFP_KERNEL);
	अगर (!asd)
		वापस -ENOMEM;

	asd->match_type = V4L2_ASYNC_MATCH_FWNODE;
	asd->match.fwnode =
		fwnode_graph_get_remote_port_parent(endpoपूर्णांक);
	अगर (!asd->match.fwnode) अणु
		dev_dbg(dev, "no remote endpoint found\n");
		ret = -ENOTCONN;
		जाओ out_err;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(endpoपूर्णांक, &vep);
	अगर (ret) अणु
		dev_warn(dev, "unable to parse V4L2 fwnode endpoint (%d)\n",
			 ret);
		जाओ out_err;
	पूर्ण

	ret = parse_endpoपूर्णांक ? parse_endpoपूर्णांक(dev, &vep, asd) : 0;
	अगर (ret == -ENOTCONN)
		dev_dbg(dev, "ignoring port@%u/endpoint@%u\n", vep.base.port,
			vep.base.id);
	अन्यथा अगर (ret < 0)
		dev_warn(dev,
			 "driver could not parse port@%u/endpoint@%u (%d)\n",
			 vep.base.port, vep.base.id, ret);
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&vep);
	अगर (ret < 0)
		जाओ out_err;

	ret = __v4l2_async_notअगरier_add_subdev(notअगरier, asd);
	अगर (ret < 0) अणु
		/* not an error अगर asd alपढ़ोy exists */
		अगर (ret == -EEXIST)
			ret = 0;
		जाओ out_err;
	पूर्ण

	वापस 0;

out_err:
	fwnode_handle_put(asd->match.fwnode);
	kमुक्त(asd);

	वापस ret == -ENOTCONN ? 0 : ret;
पूर्ण

अटल पूर्णांक
__v4l2_async_notअगरier_parse_fwnode_ep(काष्ठा device *dev,
				      काष्ठा v4l2_async_notअगरier *notअगरier,
				      माप_प्रकार asd_काष्ठा_size,
				      अचिन्हित पूर्णांक port,
				      bool has_port,
				      parse_endpoपूर्णांक_func parse_endpoपूर्णांक)
अणु
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक ret = 0;

	अगर (WARN_ON(asd_काष्ठा_size < माप(काष्ठा v4l2_async_subdev)))
		वापस -EINVAL;

	fwnode_graph_क्रम_each_endpoपूर्णांक(dev_fwnode(dev), fwnode) अणु
		काष्ठा fwnode_handle *dev_fwnode;
		bool is_available;

		dev_fwnode = fwnode_graph_get_port_parent(fwnode);
		is_available = fwnode_device_is_available(dev_fwnode);
		fwnode_handle_put(dev_fwnode);
		अगर (!is_available)
			जारी;

		अगर (has_port) अणु
			काष्ठा fwnode_endpoपूर्णांक ep;

			ret = fwnode_graph_parse_endpoपूर्णांक(fwnode, &ep);
			अगर (ret)
				अवरोध;

			अगर (ep.port != port)
				जारी;
		पूर्ण

		ret = v4l2_async_notअगरier_fwnode_parse_endpoपूर्णांक(dev,
								notअगरier,
								fwnode,
								asd_काष्ठा_size,
								parse_endpoपूर्णांक);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	fwnode_handle_put(fwnode);

	वापस ret;
पूर्ण

पूर्णांक
v4l2_async_notअगरier_parse_fwnode_endpoपूर्णांकs(काष्ठा device *dev,
					   काष्ठा v4l2_async_notअगरier *notअगरier,
					   माप_प्रकार asd_काष्ठा_size,
					   parse_endpoपूर्णांक_func parse_endpoपूर्णांक)
अणु
	वापस __v4l2_async_notअगरier_parse_fwnode_ep(dev, notअगरier,
						     asd_काष्ठा_size, 0,
						     false, parse_endpoपूर्णांक);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_async_notअगरier_parse_fwnode_endpoपूर्णांकs);

/*
 * v4l2_fwnode_reference_parse - parse references क्रम async sub-devices
 * @dev: the device node the properties of which are parsed क्रम references
 * @notअगरier: the async notअगरier where the async subdevs will be added
 * @prop: the name of the property
 *
 * Return: 0 on success
 *	   -ENOENT अगर no entries were found
 *	   -ENOMEM अगर memory allocation failed
 *	   -EINVAL अगर property parsing failed
 */
अटल पूर्णांक v4l2_fwnode_reference_parse(काष्ठा device *dev,
				       काष्ठा v4l2_async_notअगरier *notअगरier,
				       स्थिर अक्षर *prop)
अणु
	काष्ठा fwnode_reference_args args;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;

	क्रम (index = 0;
	     !(ret = fwnode_property_get_reference_args(dev_fwnode(dev),
							prop, शून्य, 0,
							index, &args));
	     index++)
		fwnode_handle_put(args.fwnode);

	अगर (!index)
		वापस -ENOENT;

	/*
	 * Note that right now both -ENODATA and -ENOENT may संकेत
	 * out-of-bounds access. Return the error in हालs other than that.
	 */
	अगर (ret != -ENOENT && ret != -ENODATA)
		वापस ret;

	क्रम (index = 0;
	     !fwnode_property_get_reference_args(dev_fwnode(dev), prop, शून्य,
						 0, index, &args);
	     index++) अणु
		काष्ठा v4l2_async_subdev *asd;

		asd = v4l2_async_notअगरier_add_fwnode_subdev(notअगरier,
							    args.fwnode,
							    काष्ठा v4l2_async_subdev);
		fwnode_handle_put(args.fwnode);
		अगर (IS_ERR(asd)) अणु
			/* not an error अगर asd alपढ़ोy exists */
			अगर (PTR_ERR(asd) == -EEXIST)
				जारी;

			वापस PTR_ERR(asd);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * v4l2_fwnode_reference_get_पूर्णांक_prop - parse a reference with पूर्णांकeger
 *					arguments
 * @fwnode: fwnode to पढ़ो @prop from
 * @notअगरier: notअगरier क्रम @dev
 * @prop: the name of the property
 * @index: the index of the reference to get
 * @props: the array of पूर्णांकeger property names
 * @nprops: the number of पूर्णांकeger property names in @nprops
 *
 * First find an fwnode referred to by the reference at @index in @prop.
 *
 * Then under that fwnode, @nprops बार, क्रम each property in @props,
 * iteratively follow child nodes starting from fwnode such that they have the
 * property in @props array at the index of the child node distance from the
 * root node and the value of that property matching with the पूर्णांकeger argument
 * of the reference, at the same index.
 *
 * The child fwnode reached at the end of the iteration is then वापसed to the
 * caller.
 *
 * The core reason क्रम this is that you cannot refer to just any node in ACPI.
 * So to refer to an endpoपूर्णांक (easy in DT) you need to refer to a device, then
 * provide a list of (property name, property value) tuples where each tuple
 * uniquely identअगरies a child node. The first tuple identअगरies a child directly
 * underneath the device fwnode, the next tuple identअगरies a child node
 * underneath the fwnode identअगरied by the previous tuple, etc. until you
 * reached the fwnode you need.
 *
 * THIS EXAMPLE EXISTS MERELY TO DOCUMENT THIS FUNCTION. DO NOT USE IT AS A
 * REFERENCE IN HOW ACPI TABLES SHOULD BE WRITTEN!! See करोcumentation under
 * Documentation/firmware-guide/acpi/dsd/ instead and especially graph.txt,
 * data-node-references.txt and leds.txt .
 *
 *	Scope (\_SB.PCI0.I2C2)
 *	अणु
 *		Device (CAM0)
 *		अणु
 *			Name (_DSD, Package () अणु
 *				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
 *				Package () अणु
 *					Package () अणु
 *						"compatible",
 *						Package () अणु "nokia,smia" पूर्ण
 *					पूर्ण,
 *				पूर्ण,
 *				ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
 *				Package () अणु
 *					Package () अणु "port0", "PRT0" पूर्ण,
 *				पूर्ण
 *			पूर्ण)
 *			Name (PRT0, Package() अणु
 *				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
 *				Package () अणु
 *					Package () अणु "port", 0 पूर्ण,
 *				पूर्ण,
 *				ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
 *				Package () अणु
 *					Package () अणु "endpoint0", "EP00" पूर्ण,
 *				पूर्ण
 *			पूर्ण)
 *			Name (EP00, Package() अणु
 *				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
 *				Package () अणु
 *					Package () अणु "endpoint", 0 पूर्ण,
 *					Package () अणु
 *						"remote-endpoint",
 *						Package() अणु
 *							\_SB.PCI0.ISP, 4, 0
 *						पूर्ण
 *					पूर्ण,
 *				पूर्ण
 *			पूर्ण)
 *		पूर्ण
 *	पूर्ण
 *
 *	Scope (\_SB.PCI0)
 *	अणु
 *		Device (ISP)
 *		अणु
 *			Name (_DSD, Package () अणु
 *				ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
 *				Package () अणु
 *					Package () अणु "port4", "PRT4" पूर्ण,
 *				पूर्ण
 *			पूर्ण)
 *
 *			Name (PRT4, Package() अणु
 *				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
 *				Package () अणु
 *					Package () अणु "port", 4 पूर्ण,
 *				पूर्ण,
 *				ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
 *				Package () अणु
 *					Package () अणु "endpoint0", "EP40" पूर्ण,
 *				पूर्ण
 *			पूर्ण)
 *
 *			Name (EP40, Package() अणु
 *				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
 *				Package () अणु
 *					Package () अणु "endpoint", 0 पूर्ण,
 *					Package () अणु
 *						"remote-endpoint",
 *						Package () अणु
 *							\_SB.PCI0.I2C2.CAM0,
 *							0, 0
 *						पूर्ण
 *					पूर्ण,
 *				पूर्ण
 *			पूर्ण)
 *		पूर्ण
 *	पूर्ण
 *
 * From the EP40 node under ISP device, you could parse the graph remote
 * endpoपूर्णांक using v4l2_fwnode_reference_get_पूर्णांक_prop with these arguments:
 *
 *  @fwnode: fwnode referring to EP40 under ISP.
 *  @prop: "remote-endpoint"
 *  @index: 0
 *  @props: "port", "endpoint"
 *  @nprops: 2
 *
 * And you'd get back fwnode referring to EP00 under CAM0.
 *
 * The same works the other way around: अगर you use EP00 under CAM0 as the
 * fwnode, you'll get fwnode referring to EP40 under ISP.
 *
 * The same example in DT syntax would look like this:
 *
 * cam: cam0 अणु
 *	compatible = "nokia,smia";
 *
 *	port अणु
 *		port = <0>;
 *		endpoपूर्णांक अणु
 *			endpoपूर्णांक = <0>;
 *			remote-endpoपूर्णांक = <&isp 4 0>;
 *		पूर्ण;
 *	पूर्ण;
 * पूर्ण;
 *
 * isp: isp अणु
 *	ports अणु
 *		port@4 अणु
 *			port = <4>;
 *			endpoपूर्णांक अणु
 *				endpoपूर्णांक = <0>;
 *				remote-endpoपूर्णांक = <&cam 0 0>;
 *			पूर्ण;
 *		पूर्ण;
 *	पूर्ण;
 * पूर्ण;
 *
 * Return: 0 on success
 *	   -ENOENT अगर no entries (or the property itself) were found
 *	   -EINVAL अगर property parsing otherwise failed
 *	   -ENOMEM अगर memory allocation failed
 */
अटल काष्ठा fwnode_handle *
v4l2_fwnode_reference_get_पूर्णांक_prop(काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *prop,
				   अचिन्हित पूर्णांक index,
				   स्थिर अक्षर * स्थिर *props,
				   अचिन्हित पूर्णांक nprops)
अणु
	काष्ठा fwnode_reference_args fwnode_args;
	u64 *args = fwnode_args.args;
	काष्ठा fwnode_handle *child;
	पूर्णांक ret;

	/*
	 * Obtain remote fwnode as well as the पूर्णांकeger arguments.
	 *
	 * Note that right now both -ENODATA and -ENOENT may संकेत
	 * out-of-bounds access. Return -ENOENT in that हाल.
	 */
	ret = fwnode_property_get_reference_args(fwnode, prop, शून्य, nprops,
						 index, &fwnode_args);
	अगर (ret)
		वापस ERR_PTR(ret == -ENODATA ? -ENOENT : ret);

	/*
	 * Find a node in the tree under the referred fwnode corresponding to
	 * the पूर्णांकeger arguments.
	 */
	fwnode = fwnode_args.fwnode;
	जबतक (nprops--) अणु
		u32 val;

		/* Loop over all child nodes under fwnode. */
		fwnode_क्रम_each_child_node(fwnode, child) अणु
			अगर (fwnode_property_पढ़ो_u32(child, *props, &val))
				जारी;

			/* Found property, see अगर its value matches. */
			अगर (val == *args)
				अवरोध;
		पूर्ण

		fwnode_handle_put(fwnode);

		/* No property found; वापस an error here. */
		अगर (!child) अणु
			fwnode = ERR_PTR(-ENOENT);
			अवरोध;
		पूर्ण

		props++;
		args++;
		fwnode = child;
	पूर्ण

	वापस fwnode;
पूर्ण

काष्ठा v4l2_fwnode_पूर्णांक_props अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *props;
	अचिन्हित पूर्णांक nprops;
पूर्ण;

/*
 * v4l2_fwnode_reference_parse_पूर्णांक_props - parse references क्रम async
 *					   sub-devices
 * @dev: काष्ठा device poपूर्णांकer
 * @notअगरier: notअगरier क्रम @dev
 * @prop: the name of the property
 * @props: the array of पूर्णांकeger property names
 * @nprops: the number of पूर्णांकeger properties
 *
 * Use v4l2_fwnode_reference_get_पूर्णांक_prop to find fwnodes through reference in
 * property @prop with पूर्णांकeger arguments with child nodes matching in properties
 * @props. Then, set up V4L2 async sub-devices क्रम those fwnodes in the notअगरier
 * accordingly.
 *
 * While it is technically possible to use this function on DT, it is only
 * meaningful on ACPI. On Device tree you can refer to any node in the tree but
 * on ACPI the references are limited to devices.
 *
 * Return: 0 on success
 *	   -ENOENT अगर no entries (or the property itself) were found
 *	   -EINVAL अगर property parsing otherwisefailed
 *	   -ENOMEM अगर memory allocation failed
 */
अटल पूर्णांक
v4l2_fwnode_reference_parse_पूर्णांक_props(काष्ठा device *dev,
				      काष्ठा v4l2_async_notअगरier *notअगरier,
				      स्थिर काष्ठा v4l2_fwnode_पूर्णांक_props *p)
अणु
	काष्ठा fwnode_handle *fwnode;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;
	स्थिर अक्षर *prop = p->name;
	स्थिर अक्षर * स्थिर *props = p->props;
	अचिन्हित पूर्णांक nprops = p->nprops;

	index = 0;
	करो अणु
		fwnode = v4l2_fwnode_reference_get_पूर्णांक_prop(dev_fwnode(dev),
							    prop, index,
							    props, nprops);
		अगर (IS_ERR(fwnode)) अणु
			/*
			 * Note that right now both -ENODATA and -ENOENT may
			 * संकेत out-of-bounds access. Return the error in
			 * हालs other than that.
			 */
			अगर (PTR_ERR(fwnode) != -ENOENT &&
			    PTR_ERR(fwnode) != -ENODATA)
				वापस PTR_ERR(fwnode);
			अवरोध;
		पूर्ण
		fwnode_handle_put(fwnode);
		index++;
	पूर्ण जबतक (1);

	क्रम (index = 0;
	     !IS_ERR((fwnode = v4l2_fwnode_reference_get_पूर्णांक_prop(dev_fwnode(dev),
								  prop, index,
								  props,
								  nprops)));
	     index++) अणु
		काष्ठा v4l2_async_subdev *asd;

		asd = v4l2_async_notअगरier_add_fwnode_subdev(notअगरier, fwnode,
							    काष्ठा v4l2_async_subdev);
		fwnode_handle_put(fwnode);
		अगर (IS_ERR(asd)) अणु
			ret = PTR_ERR(asd);
			/* not an error अगर asd alपढ़ोy exists */
			अगर (ret == -EEXIST)
				जारी;

			वापस PTR_ERR(asd);
		पूर्ण
	पूर्ण

	वापस !fwnode || PTR_ERR(fwnode) == -ENOENT ? 0 : PTR_ERR(fwnode);
पूर्ण

/**
 * v4l2_async_notअगरier_parse_fwnode_sensor - parse common references on
 *					     sensors क्रम async sub-devices
 * @dev: the device node the properties of which are parsed क्रम references
 * @notअगरier: the async notअगरier where the async subdevs will be added
 *
 * Parse common sensor properties क्रम remote devices related to the
 * sensor and set up async sub-devices क्रम them.
 *
 * Any notअगरier populated using this function must be released with a call to
 * v4l2_async_notअगरier_release() after it has been unरेजिस्टरed and the async
 * sub-devices are no दीर्घer in use, even in the हाल the function वापसed an
 * error.
 *
 * Return: 0 on success
 *	   -ENOMEM अगर memory allocation failed
 *	   -EINVAL अगर property parsing failed
 */
अटल पूर्णांक
v4l2_async_notअगरier_parse_fwnode_sensor(काष्ठा device *dev,
					काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	अटल स्थिर अक्षर * स्थिर led_props[] = अणु "led" पूर्ण;
	अटल स्थिर काष्ठा v4l2_fwnode_पूर्णांक_props props[] = अणु
		अणु "flash-leds", led_props, ARRAY_SIZE(led_props) पूर्ण,
		अणु "lens-focus", शून्य, 0 पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(props); i++) अणु
		पूर्णांक ret;

		अगर (props[i].props && is_acpi_node(dev_fwnode(dev)))
			ret = v4l2_fwnode_reference_parse_पूर्णांक_props(dev,
								    notअगरier,
								    &props[i]);
		अन्यथा
			ret = v4l2_fwnode_reference_parse(dev, notअगरier,
							  props[i].name);
		अगर (ret && ret != -ENOENT) अणु
			dev_warn(dev, "parsing property \"%s\" failed (%d)\n",
				 props[i].name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक v4l2_async_रेजिस्टर_subdev_sensor(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा v4l2_async_notअगरier *notअगरier;
	पूर्णांक ret;

	अगर (WARN_ON(!sd->dev))
		वापस -ENODEV;

	notअगरier = kzalloc(माप(*notअगरier), GFP_KERNEL);
	अगर (!notअगरier)
		वापस -ENOMEM;

	v4l2_async_notअगरier_init(notअगरier);

	ret = v4l2_async_notअगरier_parse_fwnode_sensor(sd->dev, notअगरier);
	अगर (ret < 0)
		जाओ out_cleanup;

	ret = v4l2_async_subdev_notअगरier_रेजिस्टर(sd, notअगरier);
	अगर (ret < 0)
		जाओ out_cleanup;

	ret = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (ret < 0)
		जाओ out_unरेजिस्टर;

	sd->subdev_notअगरier = notअगरier;

	वापस 0;

out_unरेजिस्टर:
	v4l2_async_notअगरier_unरेजिस्टर(notअगरier);

out_cleanup:
	v4l2_async_notअगरier_cleanup(notअगरier);
	kमुक्त(notअगरier);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_async_रेजिस्टर_subdev_sensor);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sakari Ailus <sakari.ailus@linux.intel.com>");
MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
