<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
// Copyright(c) 2015-2020 Intel Corporation.

/*
 * Bandwidth management algorithm based on 2^n gears
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश "bus.h"

#घोषणा SDW_STRM_RATE_GROUPING		1

काष्ठा sdw_group_params अणु
	अचिन्हित पूर्णांक rate;
	पूर्णांक full_bw;
	पूर्णांक payload_bw;
	पूर्णांक hwidth;
पूर्ण;

काष्ठा sdw_group अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक max_size;
	अचिन्हित पूर्णांक *rates;
पूर्ण;

काष्ठा sdw_transport_data अणु
	पूर्णांक hstart;
	पूर्णांक hstop;
	पूर्णांक block_offset;
	पूर्णांक sub_block_offset;
पूर्ण;

अटल व्योम sdw_compute_slave_ports(काष्ठा sdw_master_runसमय *m_rt,
				    काष्ठा sdw_transport_data *t_data)
अणु
	काष्ठा sdw_slave_runसमय *s_rt = शून्य;
	काष्ठा sdw_port_runसमय *p_rt;
	पूर्णांक port_bo, sample_पूर्णांक;
	अचिन्हित पूर्णांक rate, bps, ch = 0;
	अचिन्हित पूर्णांक slave_total_ch;
	काष्ठा sdw_bus_params *b_params = &m_rt->bus->params;

	port_bo = t_data->block_offset;

	list_क्रम_each_entry(s_rt, &m_rt->slave_rt_list, m_rt_node) अणु
		rate = m_rt->stream->params.rate;
		bps = m_rt->stream->params.bps;
		sample_पूर्णांक = (m_rt->bus->params.curr_dr_freq / rate);
		slave_total_ch = 0;

		list_क्रम_each_entry(p_rt, &s_rt->port_list, port_node) अणु
			ch = sdw_ch_mask_to_ch(p_rt->ch_mask);

			sdw_fill_xport_params(&p_rt->transport_params,
					      p_rt->num, false,
					      SDW_BLK_GRP_CNT_1,
					      sample_पूर्णांक, port_bo, port_bo >> 8,
					      t_data->hstart,
					      t_data->hstop,
					      SDW_BLK_PKG_PER_PORT, 0x0);

			sdw_fill_port_params(&p_rt->port_params,
					     p_rt->num, bps,
					     SDW_PORT_FLOW_MODE_ISOCH,
					     b_params->s_data_mode);

			port_bo += bps * ch;
			slave_total_ch += ch;
		पूर्ण

		अगर (m_rt->direction == SDW_DATA_सूची_TX &&
		    m_rt->ch_count == slave_total_ch) अणु
			/*
			 * Slave devices were configured to access all channels
			 * of the stream, which indicates that they operate in
			 * 'mirror mode'. Make sure we reset the port offset क्रम
			 * the next device in the list
			 */
			port_bo = t_data->block_offset;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sdw_compute_master_ports(काष्ठा sdw_master_runसमय *m_rt,
				     काष्ठा sdw_group_params *params,
				     पूर्णांक port_bo, पूर्णांक hstop)
अणु
	काष्ठा sdw_transport_data t_data = अणु0पूर्ण;
	काष्ठा sdw_port_runसमय *p_rt;
	काष्ठा sdw_bus *bus = m_rt->bus;
	काष्ठा sdw_bus_params *b_params = &bus->params;
	पूर्णांक sample_पूर्णांक, hstart = 0;
	अचिन्हित पूर्णांक rate, bps, ch;

	rate = m_rt->stream->params.rate;
	bps = m_rt->stream->params.bps;
	ch = m_rt->ch_count;
	sample_पूर्णांक = (bus->params.curr_dr_freq / rate);

	अगर (rate != params->rate)
		वापस;

	t_data.hstop = hstop;
	hstart = hstop - params->hwidth + 1;
	t_data.hstart = hstart;

	list_क्रम_each_entry(p_rt, &m_rt->port_list, port_node) अणु

		sdw_fill_xport_params(&p_rt->transport_params, p_rt->num,
				      false, SDW_BLK_GRP_CNT_1, sample_पूर्णांक,
				      port_bo, port_bo >> 8, hstart, hstop,
				      SDW_BLK_PKG_PER_PORT, 0x0);

		sdw_fill_port_params(&p_rt->port_params,
				     p_rt->num, bps,
				     SDW_PORT_FLOW_MODE_ISOCH,
				     b_params->m_data_mode);

		/* Check क्रम first entry */
		अगर (!(p_rt == list_first_entry(&m_rt->port_list,
					       काष्ठा sdw_port_runसमय,
					       port_node))) अणु
			port_bo += bps * ch;
			जारी;
		पूर्ण

		t_data.hstart = hstart;
		t_data.hstop = hstop;
		t_data.block_offset = port_bo;
		t_data.sub_block_offset = 0;
		port_bo += bps * ch;
	पूर्ण

	sdw_compute_slave_ports(m_rt, &t_data);
पूर्ण

अटल व्योम _sdw_compute_port_params(काष्ठा sdw_bus *bus,
				     काष्ठा sdw_group_params *params, पूर्णांक count)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	पूर्णांक hstop = bus->params.col - 1;
	पूर्णांक block_offset, port_bo, i;

	/* Run loop क्रम all groups to compute transport parameters */
	क्रम (i = 0; i < count; i++) अणु
		port_bo = 1;
		block_offset = 1;

		list_क्रम_each_entry(m_rt, &bus->m_rt_list, bus_node) अणु
			sdw_compute_master_ports(m_rt, &params[i],
						 port_bo, hstop);

			block_offset += m_rt->ch_count *
					m_rt->stream->params.bps;
			port_bo = block_offset;
		पूर्ण

		hstop = hstop - params[i].hwidth;
	पूर्ण
पूर्ण

अटल पूर्णांक sdw_compute_group_params(काष्ठा sdw_bus *bus,
				    काष्ठा sdw_group_params *params,
				    पूर्णांक *rates, पूर्णांक count)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	पूर्णांक sel_col = bus->params.col;
	अचिन्हित पूर्णांक rate, bps, ch;
	पूर्णांक i, column_needed = 0;

	/* Calculate bandwidth per group */
	क्रम (i = 0; i < count; i++) अणु
		params[i].rate = rates[i];
		params[i].full_bw = bus->params.curr_dr_freq / params[i].rate;
	पूर्ण

	list_क्रम_each_entry(m_rt, &bus->m_rt_list, bus_node) अणु
		rate = m_rt->stream->params.rate;
		bps = m_rt->stream->params.bps;
		ch = m_rt->ch_count;

		क्रम (i = 0; i < count; i++) अणु
			अगर (rate == params[i].rate)
				params[i].payload_bw += bps * ch;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		params[i].hwidth = (sel_col *
			params[i].payload_bw + params[i].full_bw - 1) /
			params[i].full_bw;

		column_needed += params[i].hwidth;
	पूर्ण

	अगर (column_needed > sel_col - 1)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sdw_add_element_group_count(काष्ठा sdw_group *group,
				       अचिन्हित पूर्णांक rate)
अणु
	पूर्णांक num = group->count;
	पूर्णांक i;

	क्रम (i = 0; i <= num; i++) अणु
		अगर (rate == group->rates[i])
			अवरोध;

		अगर (i != num)
			जारी;

		अगर (group->count >= group->max_size) अणु
			अचिन्हित पूर्णांक *rates;

			group->max_size += 1;
			rates = kपुनः_स्मृति(group->rates,
					 (माप(पूर्णांक) * group->max_size),
					 GFP_KERNEL);
			अगर (!rates)
				वापस -ENOMEM;
			group->rates = rates;
		पूर्ण

		group->rates[group->count++] = rate;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdw_get_group_count(काष्ठा sdw_bus *bus,
			       काष्ठा sdw_group *group)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	अचिन्हित पूर्णांक rate;
	पूर्णांक ret = 0;

	group->count = 0;
	group->max_size = SDW_STRM_RATE_GROUPING;
	group->rates = kसुस्मृति(group->max_size, माप(पूर्णांक), GFP_KERNEL);
	अगर (!group->rates)
		वापस -ENOMEM;

	list_क्रम_each_entry(m_rt, &bus->m_rt_list, bus_node) अणु
		rate = m_rt->stream->params.rate;
		अगर (m_rt == list_first_entry(&bus->m_rt_list,
					     काष्ठा sdw_master_runसमय,
					     bus_node)) अणु
			group->rates[group->count++] = rate;

		पूर्ण अन्यथा अणु
			ret = sdw_add_element_group_count(group, rate);
			अगर (ret < 0) अणु
				kमुक्त(group->rates);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sdw_compute_port_params: Compute transport and port parameters
 *
 * @bus: SDW Bus instance
 */
अटल पूर्णांक sdw_compute_port_params(काष्ठा sdw_bus *bus)
अणु
	काष्ठा sdw_group_params *params = शून्य;
	काष्ठा sdw_group group;
	पूर्णांक ret;

	ret = sdw_get_group_count(bus, &group);
	अगर (ret < 0)
		वापस ret;

	अगर (group.count == 0)
		जाओ out;

	params = kसुस्मृति(group.count, माप(*params), GFP_KERNEL);
	अगर (!params) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Compute transport parameters क्रम grouped streams */
	ret = sdw_compute_group_params(bus, params,
				       &group.rates[0], group.count);
	अगर (ret < 0)
		जाओ मुक्त_params;

	_sdw_compute_port_params(bus, params, group.count);

मुक्त_params:
	kमुक्त(params);
out:
	kमुक्त(group.rates);

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_select_row_col(काष्ठा sdw_bus *bus, पूर्णांक clk_freq)
अणु
	काष्ठा sdw_master_prop *prop = &bus->prop;
	पूर्णांक frame_पूर्णांक, frame_freq;
	पूर्णांक r, c;

	क्रम (c = 0; c < SDW_FRAME_COLS; c++) अणु
		क्रम (r = 0; r < SDW_FRAME_ROWS; r++) अणु
			अगर (sdw_rows[r] != prop->शेष_row ||
			    sdw_cols[c] != prop->शेष_col)
				जारी;

			frame_पूर्णांक = sdw_rows[r] * sdw_cols[c];
			frame_freq = clk_freq / frame_पूर्णांक;

			अगर ((clk_freq - (frame_freq * SDW_FRAME_CTRL_BITS)) <
			    bus->params.bandwidth)
				जारी;

			bus->params.row = sdw_rows[r];
			bus->params.col = sdw_cols[c];
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * sdw_compute_bus_params: Compute bus parameters
 *
 * @bus: SDW Bus instance
 */
अटल पूर्णांक sdw_compute_bus_params(काष्ठा sdw_bus *bus)
अणु
	अचिन्हित पूर्णांक max_dr_freq, curr_dr_freq = 0;
	काष्ठा sdw_master_prop *mstr_prop = &bus->prop;
	पूर्णांक i, clk_values, ret;
	bool is_gear = false;
	u32 *clk_buf;

	अगर (mstr_prop->num_clk_gears) अणु
		clk_values = mstr_prop->num_clk_gears;
		clk_buf = mstr_prop->clk_gears;
		is_gear = true;
	पूर्ण अन्यथा अगर (mstr_prop->num_clk_freq) अणु
		clk_values = mstr_prop->num_clk_freq;
		clk_buf = mstr_prop->clk_freq;
	पूर्ण अन्यथा अणु
		clk_values = 1;
		clk_buf = शून्य;
	पूर्ण

	max_dr_freq = mstr_prop->max_clk_freq * SDW_DOUBLE_RATE_FACTOR;

	क्रम (i = 0; i < clk_values; i++) अणु
		अगर (!clk_buf)
			curr_dr_freq = max_dr_freq;
		अन्यथा
			curr_dr_freq = (is_gear) ?
				(max_dr_freq >>  clk_buf[i]) :
				clk_buf[i] * SDW_DOUBLE_RATE_FACTOR;

		अगर (curr_dr_freq <= bus->params.bandwidth)
			जारी;

		अवरोध;

		/*
		 * TODO: Check all the Slave(s) port(s) audio modes and find
		 * whether given घड़ी rate is supported with glitchless
		 * transition.
		 */
	पूर्ण

	अगर (i == clk_values)
		वापस -EINVAL;

	ret = sdw_select_row_col(bus, curr_dr_freq);
	अगर (ret < 0)
		वापस -EINVAL;

	bus->params.curr_dr_freq = curr_dr_freq;
	वापस 0;
पूर्ण

/**
 * sdw_compute_params: Compute bus, transport and port parameters
 *
 * @bus: SDW Bus instance
 */
पूर्णांक sdw_compute_params(काष्ठा sdw_bus *bus)
अणु
	पूर्णांक ret;

	/* Computes घड़ी frequency, frame shape and frame frequency */
	ret = sdw_compute_bus_params(bus);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "Compute bus params failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Compute transport and port params */
	ret = sdw_compute_port_params(bus);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "Compute transport params failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_compute_params);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("SoundWire Generic Bandwidth Allocation");
