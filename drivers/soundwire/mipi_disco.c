<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
// Copyright(c) 2015-17 Intel Corporation.

/*
 * MIPI Discovery And Configuration (DisCo) Specअगरication क्रम SoundWire
 * specअगरies properties to be implemented क्रम SoundWire Masters and Slaves.
 * The DisCo spec करोesn't mandate these properties. However, SDW bus cannot
 * work without knowing these values.
 *
 * The helper functions पढ़ो the Master and Slave properties. Implementers
 * of Master or Slave drivers can use any of the below three mechanisms:
 *    a) Use these APIs here as .पढ़ो_prop() callback क्रम Master and Slave
 *    b) Implement own methods and set those as .पढ़ो_prop(), but invoke
 *    APIs in this file क्रम generic पढ़ो and override the values with
 *    platक्रमm specअगरic data
 *    c) Implement ones own methods which करो not use anything provided
 *    here
 */

#समावेश <linux/device.h>
#समावेश <linux/property.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश "bus.h"

/**
 * sdw_master_पढ़ो_prop() - Read Master properties
 * @bus: SDW bus instance
 */
पूर्णांक sdw_master_पढ़ो_prop(काष्ठा sdw_bus *bus)
अणु
	काष्ठा sdw_master_prop *prop = &bus->prop;
	काष्ठा fwnode_handle *link;
	अक्षर name[32];
	पूर्णांक nval, i;

	device_property_पढ़ो_u32(bus->dev,
				 "mipi-sdw-sw-interface-revision",
				 &prop->revision);

	/* Find master handle */
	snम_लिखो(name, माप(name),
		 "mipi-sdw-link-%d-subproperties", bus->link_id);

	link = device_get_named_child_node(bus->dev, name);
	अगर (!link) अणु
		dev_err(bus->dev, "Master node %s not found\n", name);
		वापस -EIO;
	पूर्ण

	अगर (fwnode_property_पढ़ो_bool(link,
				      "mipi-sdw-clock-stop-mode0-supported"))
		prop->clk_stop_modes |= BIT(SDW_CLK_STOP_MODE0);

	अगर (fwnode_property_पढ़ो_bool(link,
				      "mipi-sdw-clock-stop-mode1-supported"))
		prop->clk_stop_modes |= BIT(SDW_CLK_STOP_MODE1);

	fwnode_property_पढ़ो_u32(link,
				 "mipi-sdw-max-clock-frequency",
				 &prop->max_clk_freq);

	nval = fwnode_property_count_u32(link, "mipi-sdw-clock-frequencies-supported");
	अगर (nval > 0) अणु
		prop->num_clk_freq = nval;
		prop->clk_freq = devm_kसुस्मृति(bus->dev, prop->num_clk_freq,
					      माप(*prop->clk_freq),
					      GFP_KERNEL);
		अगर (!prop->clk_freq)
			वापस -ENOMEM;

		fwnode_property_पढ़ो_u32_array(link,
				"mipi-sdw-clock-frequencies-supported",
				prop->clk_freq, prop->num_clk_freq);
	पूर्ण

	/*
	 * Check the frequencies supported. If FW करोesn't provide max
	 * freq, then populate here by checking values.
	 */
	अगर (!prop->max_clk_freq && prop->clk_freq) अणु
		prop->max_clk_freq = prop->clk_freq[0];
		क्रम (i = 1; i < prop->num_clk_freq; i++) अणु
			अगर (prop->clk_freq[i] > prop->max_clk_freq)
				prop->max_clk_freq = prop->clk_freq[i];
		पूर्ण
	पूर्ण

	nval = fwnode_property_count_u32(link, "mipi-sdw-supported-clock-gears");
	अगर (nval > 0) अणु
		prop->num_clk_gears = nval;
		prop->clk_gears = devm_kसुस्मृति(bus->dev, prop->num_clk_gears,
					       माप(*prop->clk_gears),
					       GFP_KERNEL);
		अगर (!prop->clk_gears)
			वापस -ENOMEM;

		fwnode_property_पढ़ो_u32_array(link,
					       "mipi-sdw-supported-clock-gears",
					       prop->clk_gears,
					       prop->num_clk_gears);
	पूर्ण

	fwnode_property_पढ़ो_u32(link, "mipi-sdw-default-frame-rate",
				 &prop->शेष_frame_rate);

	fwnode_property_पढ़ो_u32(link, "mipi-sdw-default-frame-row-size",
				 &prop->शेष_row);

	fwnode_property_पढ़ो_u32(link, "mipi-sdw-default-frame-col-size",
				 &prop->शेष_col);

	prop->dynamic_frame =  fwnode_property_पढ़ो_bool(link,
			"mipi-sdw-dynamic-frame-shape");

	fwnode_property_पढ़ो_u32(link, "mipi-sdw-command-error-threshold",
				 &prop->err_threshold);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_master_पढ़ो_prop);

अटल पूर्णांक sdw_slave_पढ़ो_dp0(काष्ठा sdw_slave *slave,
			      काष्ठा fwnode_handle *port,
			      काष्ठा sdw_dp0_prop *dp0)
अणु
	पूर्णांक nval;

	fwnode_property_पढ़ो_u32(port, "mipi-sdw-port-max-wordlength",
				 &dp0->max_word);

	fwnode_property_पढ़ो_u32(port, "mipi-sdw-port-min-wordlength",
				 &dp0->min_word);

	nval = fwnode_property_count_u32(port, "mipi-sdw-port-wordlength-configs");
	अगर (nval > 0) अणु

		dp0->num_words = nval;
		dp0->words = devm_kसुस्मृति(&slave->dev,
					  dp0->num_words, माप(*dp0->words),
					  GFP_KERNEL);
		अगर (!dp0->words)
			वापस -ENOMEM;

		fwnode_property_पढ़ो_u32_array(port,
				"mipi-sdw-port-wordlength-configs",
				dp0->words, dp0->num_words);
	पूर्ण

	dp0->BRA_flow_controlled = fwnode_property_पढ़ो_bool(port,
				"mipi-sdw-bra-flow-controlled");

	dp0->simple_ch_prep_sm = fwnode_property_पढ़ो_bool(port,
				"mipi-sdw-simplified-channel-prepare-sm");

	dp0->imp_def_पूर्णांकerrupts = fwnode_property_पढ़ो_bool(port,
				"mipi-sdw-imp-def-dp0-interrupts-supported");

	वापस 0;
पूर्ण

अटल पूर्णांक sdw_slave_पढ़ो_dpn(काष्ठा sdw_slave *slave,
			      काष्ठा sdw_dpn_prop *dpn, पूर्णांक count, पूर्णांक ports,
			      अक्षर *type)
अणु
	काष्ठा fwnode_handle *node;
	u32 bit, i = 0;
	पूर्णांक nval;
	अचिन्हित दीर्घ addr;
	अक्षर name[40];

	addr = ports;
	/* valid ports are 1 to 14 so apply mask */
	addr &= GENMASK(14, 1);

	क्रम_each_set_bit(bit, &addr, 32) अणु
		snम_लिखो(name, माप(name),
			 "mipi-sdw-dp-%d-%s-subproperties", bit, type);

		dpn[i].num = bit;

		node = device_get_named_child_node(&slave->dev, name);
		अगर (!node) अणु
			dev_err(&slave->dev, "%s dpN not found\n", name);
			वापस -EIO;
		पूर्ण

		fwnode_property_पढ़ो_u32(node, "mipi-sdw-port-max-wordlength",
					 &dpn[i].max_word);
		fwnode_property_पढ़ो_u32(node, "mipi-sdw-port-min-wordlength",
					 &dpn[i].min_word);

		nval = fwnode_property_count_u32(node, "mipi-sdw-port-wordlength-configs");
		अगर (nval > 0) अणु
			dpn[i].num_words = nval;
			dpn[i].words = devm_kसुस्मृति(&slave->dev,
						    dpn[i].num_words,
						    माप(*dpn[i].words),
						    GFP_KERNEL);
			अगर (!dpn[i].words)
				वापस -ENOMEM;

			fwnode_property_पढ़ो_u32_array(node,
					"mipi-sdw-port-wordlength-configs",
					dpn[i].words, dpn[i].num_words);
		पूर्ण

		fwnode_property_पढ़ो_u32(node, "mipi-sdw-data-port-type",
					 &dpn[i].type);

		fwnode_property_पढ़ो_u32(node,
					 "mipi-sdw-max-grouping-supported",
					 &dpn[i].max_grouping);

		dpn[i].simple_ch_prep_sm = fwnode_property_पढ़ो_bool(node,
				"mipi-sdw-simplified-channelprepare-sm");

		fwnode_property_पढ़ो_u32(node,
					 "mipi-sdw-port-channelprepare-timeout",
					 &dpn[i].ch_prep_समयout);

		fwnode_property_पढ़ो_u32(node,
				"mipi-sdw-imp-def-dpn-interrupts-supported",
				&dpn[i].imp_def_पूर्णांकerrupts);

		fwnode_property_पढ़ो_u32(node, "mipi-sdw-min-channel-number",
					 &dpn[i].min_ch);

		fwnode_property_पढ़ो_u32(node, "mipi-sdw-max-channel-number",
					 &dpn[i].max_ch);

		nval = fwnode_property_count_u32(node, "mipi-sdw-channel-number-list");
		अगर (nval > 0) अणु
			dpn[i].num_channels = nval;
			dpn[i].channels = devm_kसुस्मृति(&slave->dev,
						       dpn[i].num_channels,
						       माप(*dpn[i].channels),
						 GFP_KERNEL);
			अगर (!dpn[i].channels)
				वापस -ENOMEM;

			fwnode_property_पढ़ो_u32_array(node,
					"mipi-sdw-channel-number-list",
					dpn[i].channels, dpn[i].num_channels);
		पूर्ण

		nval = fwnode_property_count_u32(node, "mipi-sdw-channel-combination-list");
		अगर (nval > 0) अणु
			dpn[i].num_ch_combinations = nval;
			dpn[i].ch_combinations = devm_kसुस्मृति(&slave->dev,
					dpn[i].num_ch_combinations,
					माप(*dpn[i].ch_combinations),
					GFP_KERNEL);
			अगर (!dpn[i].ch_combinations)
				वापस -ENOMEM;

			fwnode_property_पढ़ो_u32_array(node,
					"mipi-sdw-channel-combination-list",
					dpn[i].ch_combinations,
					dpn[i].num_ch_combinations);
		पूर्ण

		fwnode_property_पढ़ो_u32(node,
				"mipi-sdw-modes-supported", &dpn[i].modes);

		fwnode_property_पढ़ो_u32(node, "mipi-sdw-max-async-buffer",
					 &dpn[i].max_async_buffer);

		dpn[i].block_pack_mode = fwnode_property_पढ़ो_bool(node,
				"mipi-sdw-block-packing-mode");

		fwnode_property_पढ़ो_u32(node, "mipi-sdw-port-encoding-type",
					 &dpn[i].port_encoding);

		/* TODO: Read audio mode */

		i++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sdw_slave_पढ़ो_prop() - Read Slave properties
 * @slave: SDW Slave
 */
पूर्णांक sdw_slave_पढ़ो_prop(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_prop *prop = &slave->prop;
	काष्ठा device *dev = &slave->dev;
	काष्ठा fwnode_handle *port;
	पूर्णांक nval;

	device_property_पढ़ो_u32(dev, "mipi-sdw-sw-interface-revision",
				 &prop->mipi_revision);

	prop->wake_capable = device_property_पढ़ो_bool(dev,
				"mipi-sdw-wake-up-unavailable");
	prop->wake_capable = !prop->wake_capable;

	prop->test_mode_capable = device_property_पढ़ो_bool(dev,
				"mipi-sdw-test-mode-supported");

	prop->clk_stop_mode1 = false;
	अगर (device_property_पढ़ो_bool(dev,
				"mipi-sdw-clock-stop-mode1-supported"))
		prop->clk_stop_mode1 = true;

	prop->simple_clk_stop_capable = device_property_पढ़ो_bool(dev,
			"mipi-sdw-simplified-clockstopprepare-sm-supported");

	device_property_पढ़ो_u32(dev, "mipi-sdw-clockstopprepare-timeout",
				 &prop->clk_stop_समयout);

	device_property_पढ़ो_u32(dev, "mipi-sdw-slave-channelprepare-timeout",
				 &prop->ch_prep_समयout);

	device_property_पढ़ो_u32(dev,
			"mipi-sdw-clockstopprepare-hard-reset-behavior",
			&prop->reset_behave);

	prop->high_PHY_capable = device_property_पढ़ो_bool(dev,
			"mipi-sdw-highPHY-capable");

	prop->paging_support = device_property_पढ़ो_bool(dev,
			"mipi-sdw-paging-support");

	prop->bank_delay_support = device_property_पढ़ो_bool(dev,
			"mipi-sdw-bank-delay-support");

	device_property_पढ़ो_u32(dev,
			"mipi-sdw-port15-read-behavior", &prop->p15_behave);

	device_property_पढ़ो_u32(dev, "mipi-sdw-master-count",
				 &prop->master_count);

	device_property_पढ़ो_u32(dev, "mipi-sdw-source-port-list",
				 &prop->source_ports);

	device_property_पढ़ो_u32(dev, "mipi-sdw-sink-port-list",
				 &prop->sink_ports);

	/* Read dp0 properties */
	port = device_get_named_child_node(dev, "mipi-sdw-dp-0-subproperties");
	अगर (!port) अणु
		dev_dbg(dev, "DP0 node not found!!\n");
	पूर्ण अन्यथा अणु
		prop->dp0_prop = devm_kzalloc(&slave->dev,
					      माप(*prop->dp0_prop),
					      GFP_KERNEL);
		अगर (!prop->dp0_prop)
			वापस -ENOMEM;

		sdw_slave_पढ़ो_dp0(slave, port, prop->dp0_prop);
	पूर्ण

	/*
	 * Based on each DPn port, get source and sink dpn properties.
	 * Also, some ports can operate as both source or sink.
	 */

	/* Allocate memory क्रम set bits in port lists */
	nval = hweight32(prop->source_ports);
	prop->src_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
					  माप(*prop->src_dpn_prop),
					  GFP_KERNEL);
	अगर (!prop->src_dpn_prop)
		वापस -ENOMEM;

	/* Read dpn properties क्रम source port(s) */
	sdw_slave_पढ़ो_dpn(slave, prop->src_dpn_prop, nval,
			   prop->source_ports, "source");

	nval = hweight32(prop->sink_ports);
	prop->sink_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
					   माप(*prop->sink_dpn_prop),
					   GFP_KERNEL);
	अगर (!prop->sink_dpn_prop)
		वापस -ENOMEM;

	/* Read dpn properties क्रम sink port(s) */
	sdw_slave_पढ़ो_dpn(slave, prop->sink_dpn_prop, nval,
			   prop->sink_ports, "sink");

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_slave_पढ़ो_prop);
