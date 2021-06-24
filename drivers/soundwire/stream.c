<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
// Copyright(c) 2015-18 Intel Corporation.

/*
 *  stream.c - SoundWire Bus stream operations.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <sound/soc.h>
#समावेश "bus.h"

/*
 * Array of supported rows and columns as per MIPI SoundWire Specअगरication 1.1
 *
 * The rows are arranged as per the array index value programmed
 * in रेजिस्टर. The index 15 has dummy value 0 in order to fill hole.
 */
पूर्णांक sdw_rows[SDW_FRAME_ROWS] = अणु48, 50, 60, 64, 75, 80, 125, 147,
			96, 100, 120, 128, 150, 160, 250, 0,
			192, 200, 240, 256, 72, 144, 90, 180पूर्ण;
EXPORT_SYMBOL(sdw_rows);

पूर्णांक sdw_cols[SDW_FRAME_COLS] = अणु2, 4, 6, 8, 10, 12, 14, 16पूर्ण;
EXPORT_SYMBOL(sdw_cols);

पूर्णांक sdw_find_col_index(पूर्णांक col)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SDW_FRAME_COLS; i++) अणु
		अगर (sdw_cols[i] == col)
			वापस i;
	पूर्ण

	pr_warn("Requested column not found, selecting lowest column no: 2\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_find_col_index);

पूर्णांक sdw_find_row_index(पूर्णांक row)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SDW_FRAME_ROWS; i++) अणु
		अगर (sdw_rows[i] == row)
			वापस i;
	पूर्ण

	pr_warn("Requested row not found, selecting lowest row no: 48\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_find_row_index);

अटल पूर्णांक _sdw_program_slave_port_params(काष्ठा sdw_bus *bus,
					  काष्ठा sdw_slave *slave,
					  काष्ठा sdw_transport_params *t_params,
					  क्रमागत sdw_dpn_type type)
अणु
	u32 addr1, addr2, addr3, addr4;
	पूर्णांक ret;
	u16 wbuf;

	अगर (bus->params.next_bank) अणु
		addr1 = SDW_DPN_OFFSETCTRL2_B1(t_params->port_num);
		addr2 = SDW_DPN_BLOCKCTRL3_B1(t_params->port_num);
		addr3 = SDW_DPN_SAMPLECTRL2_B1(t_params->port_num);
		addr4 = SDW_DPN_HCTRL_B1(t_params->port_num);
	पूर्ण अन्यथा अणु
		addr1 = SDW_DPN_OFFSETCTRL2_B0(t_params->port_num);
		addr2 = SDW_DPN_BLOCKCTRL3_B0(t_params->port_num);
		addr3 = SDW_DPN_SAMPLECTRL2_B0(t_params->port_num);
		addr4 = SDW_DPN_HCTRL_B0(t_params->port_num);
	पूर्ण

	/* Program DPN_OffsetCtrl2 रेजिस्टरs */
	ret = sdw_ग_लिखो(slave, addr1, t_params->offset2);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "DPN_OffsetCtrl2 register write failed\n");
		वापस ret;
	पूर्ण

	/* Program DPN_BlockCtrl3 रेजिस्टर */
	ret = sdw_ग_लिखो(slave, addr2, t_params->blk_pkg_mode);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "DPN_BlockCtrl3 register write failed\n");
		वापस ret;
	पूर्ण

	/*
	 * Data ports are FULL, SIMPLE and REDUCED. This function handles
	 * FULL and REDUCED only and beyond this poपूर्णांक only FULL is
	 * handled, so bail out अगर we are not FULL data port type
	 */
	अगर (type != SDW_DPN_FULL)
		वापस ret;

	/* Program DPN_SampleCtrl2 रेजिस्टर */
	wbuf = FIELD_GET(SDW_DPN_SAMPLECTRL_HIGH, t_params->sample_पूर्णांकerval - 1);

	ret = sdw_ग_लिखो(slave, addr3, wbuf);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "DPN_SampleCtrl2 register write failed\n");
		वापस ret;
	पूर्ण

	/* Program DPN_HCtrl रेजिस्टर */
	wbuf = FIELD_PREP(SDW_DPN_HCTRL_HSTART, t_params->hstart);
	wbuf |= FIELD_PREP(SDW_DPN_HCTRL_HSTOP, t_params->hstop);

	ret = sdw_ग_लिखो(slave, addr4, wbuf);
	अगर (ret < 0)
		dev_err(bus->dev, "DPN_HCtrl register write failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_program_slave_port_params(काष्ठा sdw_bus *bus,
					 काष्ठा sdw_slave_runसमय *s_rt,
					 काष्ठा sdw_port_runसमय *p_rt)
अणु
	काष्ठा sdw_transport_params *t_params = &p_rt->transport_params;
	काष्ठा sdw_port_params *p_params = &p_rt->port_params;
	काष्ठा sdw_slave_prop *slave_prop = &s_rt->slave->prop;
	u32 addr1, addr2, addr3, addr4, addr5, addr6;
	काष्ठा sdw_dpn_prop *dpn_prop;
	पूर्णांक ret;
	u8 wbuf;

	dpn_prop = sdw_get_slave_dpn_prop(s_rt->slave,
					  s_rt->direction,
					  t_params->port_num);
	अगर (!dpn_prop)
		वापस -EINVAL;

	addr1 = SDW_DPN_PORTCTRL(t_params->port_num);
	addr2 = SDW_DPN_BLOCKCTRL1(t_params->port_num);

	अगर (bus->params.next_bank) अणु
		addr3 = SDW_DPN_SAMPLECTRL1_B1(t_params->port_num);
		addr4 = SDW_DPN_OFFSETCTRL1_B1(t_params->port_num);
		addr5 = SDW_DPN_BLOCKCTRL2_B1(t_params->port_num);
		addr6 = SDW_DPN_LANECTRL_B1(t_params->port_num);

	पूर्ण अन्यथा अणु
		addr3 = SDW_DPN_SAMPLECTRL1_B0(t_params->port_num);
		addr4 = SDW_DPN_OFFSETCTRL1_B0(t_params->port_num);
		addr5 = SDW_DPN_BLOCKCTRL2_B0(t_params->port_num);
		addr6 = SDW_DPN_LANECTRL_B0(t_params->port_num);
	पूर्ण

	/* Program DPN_PortCtrl रेजिस्टर */
	wbuf = FIELD_PREP(SDW_DPN_PORTCTRL_DATAMODE, p_params->data_mode);
	wbuf |= FIELD_PREP(SDW_DPN_PORTCTRL_FLOWMODE, p_params->flow_mode);

	ret = sdw_update(s_rt->slave, addr1, 0xF, wbuf);
	अगर (ret < 0) अणु
		dev_err(&s_rt->slave->dev,
			"DPN_PortCtrl register write failed for port %d\n",
			t_params->port_num);
		वापस ret;
	पूर्ण

	अगर (!dpn_prop->पढ़ो_only_wordlength) अणु
		/* Program DPN_BlockCtrl1 रेजिस्टर */
		ret = sdw_ग_लिखो(s_rt->slave, addr2, (p_params->bps - 1));
		अगर (ret < 0) अणु
			dev_err(&s_rt->slave->dev,
				"DPN_BlockCtrl1 register write failed for port %d\n",
				t_params->port_num);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Program DPN_SampleCtrl1 रेजिस्टर */
	wbuf = (t_params->sample_पूर्णांकerval - 1) & SDW_DPN_SAMPLECTRL_LOW;
	ret = sdw_ग_लिखो(s_rt->slave, addr3, wbuf);
	अगर (ret < 0) अणु
		dev_err(&s_rt->slave->dev,
			"DPN_SampleCtrl1 register write failed for port %d\n",
			t_params->port_num);
		वापस ret;
	पूर्ण

	/* Program DPN_OffsetCtrl1 रेजिस्टरs */
	ret = sdw_ग_लिखो(s_rt->slave, addr4, t_params->offset1);
	अगर (ret < 0) अणु
		dev_err(&s_rt->slave->dev,
			"DPN_OffsetCtrl1 register write failed for port %d\n",
			t_params->port_num);
		वापस ret;
	पूर्ण

	/* Program DPN_BlockCtrl2 रेजिस्टर*/
	अगर (t_params->blk_grp_ctrl_valid) अणु
		ret = sdw_ग_लिखो(s_rt->slave, addr5, t_params->blk_grp_ctrl);
		अगर (ret < 0) अणु
			dev_err(&s_rt->slave->dev,
				"DPN_BlockCtrl2 reg write failed for port %d\n",
				t_params->port_num);
			वापस ret;
		पूर्ण
	पूर्ण

	/* program DPN_LaneCtrl रेजिस्टर */
	अगर (slave_prop->lane_control_support) अणु
		ret = sdw_ग_लिखो(s_rt->slave, addr6, t_params->lane_ctrl);
		अगर (ret < 0) अणु
			dev_err(&s_rt->slave->dev,
				"DPN_LaneCtrl register write failed for port %d\n",
				t_params->port_num);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (dpn_prop->type != SDW_DPN_SIMPLE) अणु
		ret = _sdw_program_slave_port_params(bus, s_rt->slave,
						     t_params, dpn_prop->type);
		अगर (ret < 0)
			dev_err(&s_rt->slave->dev,
				"Transport reg write failed for port: %d\n",
				t_params->port_num);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_program_master_port_params(काष्ठा sdw_bus *bus,
					  काष्ठा sdw_port_runसमय *p_rt)
अणु
	पूर्णांक ret;

	/*
	 * we need to set transport and port parameters क्रम the port.
	 * Transport parameters refers to the sample पूर्णांकerval, offsets and
	 * hstart/stop etc of the data. Port parameters refers to word
	 * length, flow mode etc of the port
	 */
	ret = bus->port_ops->dpn_set_port_transport_params(bus,
					&p_rt->transport_params,
					bus->params.next_bank);
	अगर (ret < 0)
		वापस ret;

	वापस bus->port_ops->dpn_set_port_params(bus,
						  &p_rt->port_params,
						  bus->params.next_bank);
पूर्ण

/**
 * sdw_program_port_params() - Programs transport parameters of Master(s)
 * and Slave(s)
 *
 * @m_rt: Master stream runसमय
 */
अटल पूर्णांक sdw_program_port_params(काष्ठा sdw_master_runसमय *m_rt)
अणु
	काष्ठा sdw_slave_runसमय *s_rt;
	काष्ठा sdw_bus *bus = m_rt->bus;
	काष्ठा sdw_port_runसमय *p_rt;
	पूर्णांक ret = 0;

	/* Program transport & port parameters क्रम Slave(s) */
	list_क्रम_each_entry(s_rt, &m_rt->slave_rt_list, m_rt_node) अणु
		list_क्रम_each_entry(p_rt, &s_rt->port_list, port_node) अणु
			ret = sdw_program_slave_port_params(bus, s_rt, p_rt);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Program transport & port parameters क्रम Master(s) */
	list_क्रम_each_entry(p_rt, &m_rt->port_list, port_node) अणु
		ret = sdw_program_master_port_params(bus, p_rt);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sdw_enable_disable_slave_ports: Enable/disable slave data port
 *
 * @bus: bus instance
 * @s_rt: slave runसमय
 * @p_rt: port runसमय
 * @en: enable or disable operation
 *
 * This function only sets the enable/disable bits in the relevant bank, the
 * actual enable/disable is करोne with a bank चयन
 */
अटल पूर्णांक sdw_enable_disable_slave_ports(काष्ठा sdw_bus *bus,
					  काष्ठा sdw_slave_runसमय *s_rt,
					  काष्ठा sdw_port_runसमय *p_rt,
					  bool en)
अणु
	काष्ठा sdw_transport_params *t_params = &p_rt->transport_params;
	u32 addr;
	पूर्णांक ret;

	अगर (bus->params.next_bank)
		addr = SDW_DPN_CHANNELEN_B1(p_rt->num);
	अन्यथा
		addr = SDW_DPN_CHANNELEN_B0(p_rt->num);

	/*
	 * Since bus करोesn't support sharing a port across two streams,
	 * it is safe to reset this रेजिस्टर
	 */
	अगर (en)
		ret = sdw_ग_लिखो(s_rt->slave, addr, p_rt->ch_mask);
	अन्यथा
		ret = sdw_ग_लिखो(s_rt->slave, addr, 0x0);

	अगर (ret < 0)
		dev_err(&s_rt->slave->dev,
			"Slave chn_en reg write failed:%d port:%d\n",
			ret, t_params->port_num);

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_enable_disable_master_ports(काष्ठा sdw_master_runसमय *m_rt,
					   काष्ठा sdw_port_runसमय *p_rt,
					   bool en)
अणु
	काष्ठा sdw_transport_params *t_params = &p_rt->transport_params;
	काष्ठा sdw_bus *bus = m_rt->bus;
	काष्ठा sdw_enable_ch enable_ch;
	पूर्णांक ret;

	enable_ch.port_num = p_rt->num;
	enable_ch.ch_mask = p_rt->ch_mask;
	enable_ch.enable = en;

	/* Perक्रमm Master port channel(s) enable/disable */
	अगर (bus->port_ops->dpn_port_enable_ch) अणु
		ret = bus->port_ops->dpn_port_enable_ch(bus,
							&enable_ch,
							bus->params.next_bank);
		अगर (ret < 0) अणु
			dev_err(bus->dev,
				"Master chn_en write failed:%d port:%d\n",
				ret, t_params->port_num);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(bus->dev,
			"dpn_port_enable_ch not supported, %s failed\n",
			en ? "enable" : "disable");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sdw_enable_disable_ports() - Enable/disable port(s) क्रम Master and
 * Slave(s)
 *
 * @m_rt: Master stream runसमय
 * @en: mode (enable/disable)
 */
अटल पूर्णांक sdw_enable_disable_ports(काष्ठा sdw_master_runसमय *m_rt, bool en)
अणु
	काष्ठा sdw_port_runसमय *s_port, *m_port;
	काष्ठा sdw_slave_runसमय *s_rt;
	पूर्णांक ret = 0;

	/* Enable/Disable Slave port(s) */
	list_क्रम_each_entry(s_rt, &m_rt->slave_rt_list, m_rt_node) अणु
		list_क्रम_each_entry(s_port, &s_rt->port_list, port_node) अणु
			ret = sdw_enable_disable_slave_ports(m_rt->bus, s_rt,
							     s_port, en);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Enable/Disable Master port(s) */
	list_क्रम_each_entry(m_port, &m_rt->port_list, port_node) अणु
		ret = sdw_enable_disable_master_ports(m_rt, m_port, en);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdw_करो_port_prep(काष्ठा sdw_slave_runसमय *s_rt,
			    काष्ठा sdw_prepare_ch prep_ch,
			    क्रमागत sdw_port_prep_ops cmd)
अणु
	स्थिर काष्ठा sdw_slave_ops *ops = s_rt->slave->ops;
	पूर्णांक ret;

	अगर (ops->port_prep) अणु
		ret = ops->port_prep(s_rt->slave, &prep_ch, cmd);
		अगर (ret < 0) अणु
			dev_err(&s_rt->slave->dev,
				"Slave Port Prep cmd %d failed: %d\n",
				cmd, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdw_prep_deprep_slave_ports(काष्ठा sdw_bus *bus,
				       काष्ठा sdw_slave_runसमय *s_rt,
				       काष्ठा sdw_port_runसमय *p_rt,
				       bool prep)
अणु
	काष्ठा completion *port_पढ़ोy;
	काष्ठा sdw_dpn_prop *dpn_prop;
	काष्ठा sdw_prepare_ch prep_ch;
	अचिन्हित पूर्णांक समय_left;
	bool पूर्णांकr = false;
	पूर्णांक ret = 0, val;
	u32 addr;

	prep_ch.num = p_rt->num;
	prep_ch.ch_mask = p_rt->ch_mask;

	dpn_prop = sdw_get_slave_dpn_prop(s_rt->slave,
					  s_rt->direction,
					  prep_ch.num);
	अगर (!dpn_prop) अणु
		dev_err(bus->dev,
			"Slave Port:%d properties not found\n", prep_ch.num);
		वापस -EINVAL;
	पूर्ण

	prep_ch.prepare = prep;

	prep_ch.bank = bus->params.next_bank;

	अगर (dpn_prop->imp_def_पूर्णांकerrupts || !dpn_prop->simple_ch_prep_sm ||
	    bus->params.s_data_mode != SDW_PORT_DATA_MODE_NORMAL)
		पूर्णांकr = true;

	/*
	 * Enable पूर्णांकerrupt beक्रमe Port prepare.
	 * For Port de-prepare, it is assumed that port
	 * was prepared earlier
	 */
	अगर (prep && पूर्णांकr) अणु
		ret = sdw_configure_dpn_पूर्णांकr(s_rt->slave, p_rt->num, prep,
					     dpn_prop->imp_def_पूर्णांकerrupts);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Inक्रमm slave about the impending port prepare */
	sdw_करो_port_prep(s_rt, prep_ch, SDW_OPS_PORT_PRE_PREP);

	/* Prepare Slave port implementing CP_SM */
	अगर (!dpn_prop->simple_ch_prep_sm) अणु
		addr = SDW_DPN_PREPARECTRL(p_rt->num);

		अगर (prep)
			ret = sdw_ग_लिखो(s_rt->slave, addr, p_rt->ch_mask);
		अन्यथा
			ret = sdw_ग_लिखो(s_rt->slave, addr, 0x0);

		अगर (ret < 0) अणु
			dev_err(&s_rt->slave->dev,
				"Slave prep_ctrl reg write failed\n");
			वापस ret;
		पूर्ण

		/* Wait क्रम completion on port पढ़ोy */
		port_पढ़ोy = &s_rt->slave->port_पढ़ोy[prep_ch.num];
		समय_left = रुको_क्रम_completion_समयout(port_पढ़ोy,
				msecs_to_jअगरfies(dpn_prop->ch_prep_समयout));

		val = sdw_पढ़ो(s_rt->slave, SDW_DPN_PREPARESTATUS(p_rt->num));
		val &= p_rt->ch_mask;
		अगर (!समय_left || val) अणु
			dev_err(&s_rt->slave->dev,
				"Chn prep failed for port:%d\n", prep_ch.num);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	/* Inक्रमm slaves about ports prepared */
	sdw_करो_port_prep(s_rt, prep_ch, SDW_OPS_PORT_POST_PREP);

	/* Disable पूर्णांकerrupt after Port de-prepare */
	अगर (!prep && पूर्णांकr)
		ret = sdw_configure_dpn_पूर्णांकr(s_rt->slave, p_rt->num, prep,
					     dpn_prop->imp_def_पूर्णांकerrupts);

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_prep_deprep_master_ports(काष्ठा sdw_master_runसमय *m_rt,
					काष्ठा sdw_port_runसमय *p_rt,
					bool prep)
अणु
	काष्ठा sdw_transport_params *t_params = &p_rt->transport_params;
	काष्ठा sdw_bus *bus = m_rt->bus;
	स्थिर काष्ठा sdw_master_port_ops *ops = bus->port_ops;
	काष्ठा sdw_prepare_ch prep_ch;
	पूर्णांक ret = 0;

	prep_ch.num = p_rt->num;
	prep_ch.ch_mask = p_rt->ch_mask;
	prep_ch.prepare = prep; /* Prepare/De-prepare */
	prep_ch.bank = bus->params.next_bank;

	/* Pre-prepare/Pre-deprepare port(s) */
	अगर (ops->dpn_port_prep) अणु
		ret = ops->dpn_port_prep(bus, &prep_ch);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Port prepare failed for port:%d\n",
				t_params->port_num);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sdw_prep_deprep_ports() - Prepare/De-prepare port(s) क्रम Master(s) and
 * Slave(s)
 *
 * @m_rt: Master runसमय handle
 * @prep: Prepare or De-prepare
 */
अटल पूर्णांक sdw_prep_deprep_ports(काष्ठा sdw_master_runसमय *m_rt, bool prep)
अणु
	काष्ठा sdw_slave_runसमय *s_rt;
	काष्ठा sdw_port_runसमय *p_rt;
	पूर्णांक ret = 0;

	/* Prepare/De-prepare Slave port(s) */
	list_क्रम_each_entry(s_rt, &m_rt->slave_rt_list, m_rt_node) अणु
		list_क्रम_each_entry(p_rt, &s_rt->port_list, port_node) अणु
			ret = sdw_prep_deprep_slave_ports(m_rt->bus, s_rt,
							  p_rt, prep);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Prepare/De-prepare Master port(s) */
	list_क्रम_each_entry(p_rt, &m_rt->port_list, port_node) अणु
		ret = sdw_prep_deprep_master_ports(m_rt, p_rt, prep);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sdw_notअगरy_config() - Notअगरy bus configuration
 *
 * @m_rt: Master runसमय handle
 *
 * This function notअगरies the Master(s) and Slave(s) of the
 * new bus configuration.
 */
अटल पूर्णांक sdw_notअगरy_config(काष्ठा sdw_master_runसमय *m_rt)
अणु
	काष्ठा sdw_slave_runसमय *s_rt;
	काष्ठा sdw_bus *bus = m_rt->bus;
	काष्ठा sdw_slave *slave;
	पूर्णांक ret = 0;

	अगर (bus->ops->set_bus_conf) अणु
		ret = bus->ops->set_bus_conf(bus, &bus->params);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	list_क्रम_each_entry(s_rt, &m_rt->slave_rt_list, m_rt_node) अणु
		slave = s_rt->slave;

		अगर (slave->ops->bus_config) अणु
			ret = slave->ops->bus_config(slave, &bus->params);
			अगर (ret < 0) अणु
				dev_err(bus->dev, "Notify Slave: %d failed\n",
					slave->dev_num);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sdw_program_params() - Program transport and port parameters क्रम Master(s)
 * and Slave(s)
 *
 * @bus: SDW bus instance
 * @prepare: true अगर sdw_program_params() is called by _prepare.
 */
अटल पूर्णांक sdw_program_params(काष्ठा sdw_bus *bus, bool prepare)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(m_rt, &bus->m_rt_list, bus_node) अणु

		/*
		 * this loop walks through all master runबार क्रम a
		 * bus, but the ports can only be configured जबतक
		 * explicitly preparing a stream or handling an
		 * alपढ़ोy-prepared stream otherwise.
		 */
		अगर (!prepare &&
		    m_rt->stream->state == SDW_STREAM_CONFIGURED)
			जारी;

		ret = sdw_program_port_params(m_rt);
		अगर (ret < 0) अणु
			dev_err(bus->dev,
				"Program transport params failed: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = sdw_notअगरy_config(m_rt);
		अगर (ret < 0) अणु
			dev_err(bus->dev,
				"Notify bus config failed: %d\n", ret);
			वापस ret;
		पूर्ण

		/* Enable port(s) on alternate bank क्रम all active streams */
		अगर (m_rt->stream->state != SDW_STREAM_ENABLED)
			जारी;

		ret = sdw_enable_disable_ports(m_rt, true);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Enable channel failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_bank_चयन(काष्ठा sdw_bus *bus, पूर्णांक m_rt_count)
अणु
	पूर्णांक col_index, row_index;
	bool multi_link;
	काष्ठा sdw_msg *wr_msg;
	u8 *wbuf;
	पूर्णांक ret;
	u16 addr;

	wr_msg = kzalloc(माप(*wr_msg), GFP_KERNEL);
	अगर (!wr_msg)
		वापस -ENOMEM;

	bus->defer_msg.msg = wr_msg;

	wbuf = kzalloc(माप(*wbuf), GFP_KERNEL);
	अगर (!wbuf) अणु
		ret = -ENOMEM;
		जाओ error_1;
	पूर्ण

	/* Get row and column index to program रेजिस्टर */
	col_index = sdw_find_col_index(bus->params.col);
	row_index = sdw_find_row_index(bus->params.row);
	wbuf[0] = col_index | (row_index << 3);

	अगर (bus->params.next_bank)
		addr = SDW_SCP_FRAMECTRL_B1;
	अन्यथा
		addr = SDW_SCP_FRAMECTRL_B0;

	sdw_fill_msg(wr_msg, शून्य, addr, 1, SDW_BROADCAST_DEV_NUM,
		     SDW_MSG_FLAG_WRITE, wbuf);
	wr_msg->ssp_sync = true;

	/*
	 * Set the multi_link flag only when both the hardware supports
	 * and hardware-based sync is required
	 */
	multi_link = bus->multi_link && (m_rt_count >= bus->hw_sync_min_links);

	अगर (multi_link)
		ret = sdw_transfer_defer(bus, wr_msg, &bus->defer_msg);
	अन्यथा
		ret = sdw_transfer(bus, wr_msg);

	अगर (ret < 0) अणु
		dev_err(bus->dev, "Slave frame_ctrl reg write failed\n");
		जाओ error;
	पूर्ण

	अगर (!multi_link) अणु
		kमुक्त(wr_msg);
		kमुक्त(wbuf);
		bus->defer_msg.msg = शून्य;
		bus->params.curr_bank = !bus->params.curr_bank;
		bus->params.next_bank = !bus->params.next_bank;
	पूर्ण

	वापस 0;

error:
	kमुक्त(wbuf);
error_1:
	kमुक्त(wr_msg);
	bus->defer_msg.msg = शून्य;
	वापस ret;
पूर्ण

/**
 * sdw_ml_sync_bank_चयन: Multilink रेजिस्टर bank चयन
 *
 * @bus: SDW bus instance
 *
 * Caller function should मुक्त the buffers on error
 */
अटल पूर्णांक sdw_ml_sync_bank_चयन(काष्ठा sdw_bus *bus)
अणु
	अचिन्हित दीर्घ समय_left;

	अगर (!bus->multi_link)
		वापस 0;

	/* Wait क्रम completion of transfer */
	समय_left = रुको_क्रम_completion_समयout(&bus->defer_msg.complete,
						bus->bank_चयन_समयout);

	अगर (!समय_left) अणु
		dev_err(bus->dev, "Controller Timed out on bank switch\n");
		वापस -ETIMEDOUT;
	पूर्ण

	bus->params.curr_bank = !bus->params.curr_bank;
	bus->params.next_bank = !bus->params.next_bank;

	अगर (bus->defer_msg.msg) अणु
		kमुक्त(bus->defer_msg.msg->buf);
		kमुक्त(bus->defer_msg.msg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_bank_चयन(काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	स्थिर काष्ठा sdw_master_ops *ops;
	काष्ठा sdw_bus *bus;
	bool multi_link = false;
	पूर्णांक m_rt_count;
	पूर्णांक ret = 0;

	m_rt_count = stream->m_rt_count;

	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		bus = m_rt->bus;
		ops = bus->ops;

		अगर (bus->multi_link && m_rt_count >= bus->hw_sync_min_links) अणु
			multi_link = true;
			mutex_lock(&bus->msg_lock);
		पूर्ण

		/* Pre-bank चयन */
		अगर (ops->pre_bank_चयन) अणु
			ret = ops->pre_bank_चयन(bus);
			अगर (ret < 0) अणु
				dev_err(bus->dev,
					"Pre bank switch op failed: %d\n", ret);
				जाओ msg_unlock;
			पूर्ण
		पूर्ण

		/*
		 * Perक्रमm Bank चयन operation.
		 * For multi link हालs, the actual bank चयन is
		 * synchronized across all Masters and happens later as a
		 * part of post_bank_चयन ops.
		 */
		ret = sdw_bank_चयन(bus, m_rt_count);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Bank switch failed: %d\n", ret);
			जाओ error;
		पूर्ण
	पूर्ण

	/*
	 * For multi link हालs, it is expected that the bank चयन is
	 * triggered by the post_bank_चयन क्रम the first Master in the list
	 * and क्रम the other Masters the post_bank_चयन() should वापस करोing
	 * nothing.
	 */
	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		bus = m_rt->bus;
		ops = bus->ops;

		/* Post-bank चयन */
		अगर (ops->post_bank_चयन) अणु
			ret = ops->post_bank_चयन(bus);
			अगर (ret < 0) अणु
				dev_err(bus->dev,
					"Post bank switch op failed: %d\n",
					ret);
				जाओ error;
			पूर्ण
		पूर्ण अन्यथा अगर (multi_link) अणु
			dev_err(bus->dev,
				"Post bank switch ops not implemented\n");
			जाओ error;
		पूर्ण

		/* Set the bank चयन समयout to शेष, अगर not set */
		अगर (!bus->bank_चयन_समयout)
			bus->bank_चयन_समयout = DEFAULT_BANK_SWITCH_TIMEOUT;

		/* Check अगर bank चयन was successful */
		ret = sdw_ml_sync_bank_चयन(bus);
		अगर (ret < 0) अणु
			dev_err(bus->dev,
				"multi link bank switch failed: %d\n", ret);
			जाओ error;
		पूर्ण

		अगर (multi_link)
			mutex_unlock(&bus->msg_lock);
	पूर्ण

	वापस ret;

error:
	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		bus = m_rt->bus;
		अगर (bus->defer_msg.msg) अणु
			kमुक्त(bus->defer_msg.msg->buf);
			kमुक्त(bus->defer_msg.msg);
		पूर्ण
	पूर्ण

msg_unlock:

	अगर (multi_link) अणु
		list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
			bus = m_rt->bus;
			अगर (mutex_is_locked(&bus->msg_lock))
				mutex_unlock(&bus->msg_lock);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sdw_release_stream() - Free the asचिन्हित stream runसमय
 *
 * @stream: SoundWire stream runसमय
 *
 * sdw_release_stream should be called only once per stream
 */
व्योम sdw_release_stream(काष्ठा sdw_stream_runसमय *stream)
अणु
	kमुक्त(stream);
पूर्ण
EXPORT_SYMBOL(sdw_release_stream);

/**
 * sdw_alloc_stream() - Allocate and वापस stream runसमय
 *
 * @stream_name: SoundWire stream name
 *
 * Allocates a SoundWire stream runसमय instance.
 * sdw_alloc_stream should be called only once per stream. Typically
 * invoked from ALSA/ASoC machine/platक्रमm driver.
 */
काष्ठा sdw_stream_runसमय *sdw_alloc_stream(स्थिर अक्षर *stream_name)
अणु
	काष्ठा sdw_stream_runसमय *stream;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream)
		वापस शून्य;

	stream->name = stream_name;
	INIT_LIST_HEAD(&stream->master_list);
	stream->state = SDW_STREAM_ALLOCATED;
	stream->m_rt_count = 0;

	वापस stream;
पूर्ण
EXPORT_SYMBOL(sdw_alloc_stream);

अटल काष्ठा sdw_master_runसमय
*sdw_find_master_rt(काष्ठा sdw_bus *bus,
		    काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt;

	/* Retrieve Bus handle अगर alपढ़ोy available */
	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		अगर (m_rt->bus == bus)
			वापस m_rt;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * sdw_alloc_master_rt() - Allocates and initialize Master runसमय handle
 *
 * @bus: SDW bus instance
 * @stream_config: Stream configuration
 * @stream: Stream runसमय handle.
 *
 * This function is to be called with bus_lock held.
 */
अटल काष्ठा sdw_master_runसमय
*sdw_alloc_master_rt(काष्ठा sdw_bus *bus,
		     काष्ठा sdw_stream_config *stream_config,
		     काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt;

	/*
	 * check अगर Master is alपढ़ोy allocated (as a result of Slave adding
	 * it first), अगर so skip allocation and go to configure
	 */
	m_rt = sdw_find_master_rt(bus, stream);
	अगर (m_rt)
		जाओ stream_config;

	m_rt = kzalloc(माप(*m_rt), GFP_KERNEL);
	अगर (!m_rt)
		वापस शून्य;

	/* Initialization of Master runसमय handle */
	INIT_LIST_HEAD(&m_rt->port_list);
	INIT_LIST_HEAD(&m_rt->slave_rt_list);
	list_add_tail(&m_rt->stream_node, &stream->master_list);

	list_add_tail(&m_rt->bus_node, &bus->m_rt_list);

stream_config:
	m_rt->ch_count = stream_config->ch_count;
	m_rt->bus = bus;
	m_rt->stream = stream;
	m_rt->direction = stream_config->direction;

	वापस m_rt;
पूर्ण

/**
 * sdw_alloc_slave_rt() - Allocate and initialize Slave runसमय handle.
 *
 * @slave: Slave handle
 * @stream_config: Stream configuration
 * @stream: Stream runसमय handle
 *
 * This function is to be called with bus_lock held.
 */
अटल काष्ठा sdw_slave_runसमय
*sdw_alloc_slave_rt(काष्ठा sdw_slave *slave,
		    काष्ठा sdw_stream_config *stream_config,
		    काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_slave_runसमय *s_rt;

	s_rt = kzalloc(माप(*s_rt), GFP_KERNEL);
	अगर (!s_rt)
		वापस शून्य;

	INIT_LIST_HEAD(&s_rt->port_list);
	s_rt->ch_count = stream_config->ch_count;
	s_rt->direction = stream_config->direction;
	s_rt->slave = slave;

	वापस s_rt;
पूर्ण

अटल व्योम sdw_master_port_release(काष्ठा sdw_bus *bus,
				    काष्ठा sdw_master_runसमय *m_rt)
अणु
	काष्ठा sdw_port_runसमय *p_rt, *_p_rt;

	list_क्रम_each_entry_safe(p_rt, _p_rt, &m_rt->port_list, port_node) अणु
		list_del(&p_rt->port_node);
		kमुक्त(p_rt);
	पूर्ण
पूर्ण

अटल व्योम sdw_slave_port_release(काष्ठा sdw_bus *bus,
				   काष्ठा sdw_slave *slave,
				   काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_port_runसमय *p_rt, *_p_rt;
	काष्ठा sdw_master_runसमय *m_rt;
	काष्ठा sdw_slave_runसमय *s_rt;

	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		list_क्रम_each_entry(s_rt, &m_rt->slave_rt_list, m_rt_node) अणु
			अगर (s_rt->slave != slave)
				जारी;

			list_क्रम_each_entry_safe(p_rt, _p_rt,
						 &s_rt->port_list, port_node) अणु
				list_del(&p_rt->port_node);
				kमुक्त(p_rt);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * sdw_release_slave_stream() - Free Slave(s) runसमय handle
 *
 * @slave: Slave handle.
 * @stream: Stream runसमय handle.
 *
 * This function is to be called with bus_lock held.
 */
अटल व्योम sdw_release_slave_stream(काष्ठा sdw_slave *slave,
				     काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_slave_runसमय *s_rt, *_s_rt;
	काष्ठा sdw_master_runसमय *m_rt;

	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		/* Retrieve Slave runसमय handle */
		list_क्रम_each_entry_safe(s_rt, _s_rt,
					 &m_rt->slave_rt_list, m_rt_node) अणु
			अगर (s_rt->slave == slave) अणु
				list_del(&s_rt->m_rt_node);
				kमुक्त(s_rt);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * sdw_release_master_stream() - Free Master runसमय handle
 *
 * @m_rt: Master runसमय node
 * @stream: Stream runसमय handle.
 *
 * This function is to be called with bus_lock held
 * It मुक्तs the Master runसमय handle and associated Slave(s) runसमय
 * handle. If this is called first then sdw_release_slave_stream() will have
 * no effect as Slave(s) runसमय handle would alपढ़ोy be मुक्तd up.
 */
अटल व्योम sdw_release_master_stream(काष्ठा sdw_master_runसमय *m_rt,
				      काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_slave_runसमय *s_rt, *_s_rt;

	list_क्रम_each_entry_safe(s_rt, _s_rt, &m_rt->slave_rt_list, m_rt_node) अणु
		sdw_slave_port_release(s_rt->slave->bus, s_rt->slave, stream);
		sdw_release_slave_stream(s_rt->slave, stream);
	पूर्ण

	list_del(&m_rt->stream_node);
	list_del(&m_rt->bus_node);
	kमुक्त(m_rt);
पूर्ण

/**
 * sdw_stream_हटाओ_master() - Remove master from sdw_stream
 *
 * @bus: SDW Bus instance
 * @stream: SoundWire stream
 *
 * This हटाओs and मुक्तs port_rt and master_rt from a stream
 */
पूर्णांक sdw_stream_हटाओ_master(काष्ठा sdw_bus *bus,
			     काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt, *_m_rt;

	mutex_lock(&bus->bus_lock);

	list_क्रम_each_entry_safe(m_rt, _m_rt,
				 &stream->master_list, stream_node) अणु
		अगर (m_rt->bus != bus)
			जारी;

		sdw_master_port_release(bus, m_rt);
		sdw_release_master_stream(m_rt, stream);
		stream->m_rt_count--;
	पूर्ण

	अगर (list_empty(&stream->master_list))
		stream->state = SDW_STREAM_RELEASED;

	mutex_unlock(&bus->bus_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_stream_हटाओ_master);

/**
 * sdw_stream_हटाओ_slave() - Remove slave from sdw_stream
 *
 * @slave: SDW Slave instance
 * @stream: SoundWire stream
 *
 * This हटाओs and मुक्तs port_rt and slave_rt from a stream
 */
पूर्णांक sdw_stream_हटाओ_slave(काष्ठा sdw_slave *slave,
			    काष्ठा sdw_stream_runसमय *stream)
अणु
	mutex_lock(&slave->bus->bus_lock);

	sdw_slave_port_release(slave->bus, slave, stream);
	sdw_release_slave_stream(slave, stream);

	mutex_unlock(&slave->bus->bus_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_stream_हटाओ_slave);

/**
 * sdw_config_stream() - Configure the allocated stream
 *
 * @dev: SDW device
 * @stream: SoundWire stream
 * @stream_config: Stream configuration क्रम audio stream
 * @is_slave: is API called from Slave or Master
 *
 * This function is to be called with bus_lock held.
 */
अटल पूर्णांक sdw_config_stream(काष्ठा device *dev,
			     काष्ठा sdw_stream_runसमय *stream,
			     काष्ठा sdw_stream_config *stream_config,
			     bool is_slave)
अणु
	/*
	 * Update the stream rate, channel and bps based on data
	 * source. For more than one data source (multilink),
	 * match the rate, bps, stream type and increment number of channels.
	 *
	 * If rate/bps is zero, it means the values are not set, so skip
	 * comparison and allow the value to be set and stored in stream
	 */
	अगर (stream->params.rate &&
	    stream->params.rate != stream_config->frame_rate) अणु
		dev_err(dev, "rate not matching, stream:%s\n", stream->name);
		वापस -EINVAL;
	पूर्ण

	अगर (stream->params.bps &&
	    stream->params.bps != stream_config->bps) अणु
		dev_err(dev, "bps not matching, stream:%s\n", stream->name);
		वापस -EINVAL;
	पूर्ण

	stream->type = stream_config->type;
	stream->params.rate = stream_config->frame_rate;
	stream->params.bps = stream_config->bps;

	/* TODO: Update this check during Device-device support */
	अगर (is_slave)
		stream->params.ch_count += stream_config->ch_count;

	वापस 0;
पूर्ण

अटल पूर्णांक sdw_is_valid_port_range(काष्ठा device *dev,
				   काष्ठा sdw_port_runसमय *p_rt)
अणु
	अगर (!SDW_VALID_PORT_RANGE(p_rt->num)) अणु
		dev_err(dev,
			"SoundWire: Invalid port number :%d\n", p_rt->num);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sdw_port_runसमय
*sdw_port_alloc(काष्ठा device *dev,
		काष्ठा sdw_port_config *port_config,
		पूर्णांक port_index)
अणु
	काष्ठा sdw_port_runसमय *p_rt;

	p_rt = kzalloc(माप(*p_rt), GFP_KERNEL);
	अगर (!p_rt)
		वापस शून्य;

	p_rt->ch_mask = port_config[port_index].ch_mask;
	p_rt->num = port_config[port_index].num;

	वापस p_rt;
पूर्ण

अटल पूर्णांक sdw_master_port_config(काष्ठा sdw_bus *bus,
				  काष्ठा sdw_master_runसमय *m_rt,
				  काष्ठा sdw_port_config *port_config,
				  अचिन्हित पूर्णांक num_ports)
अणु
	काष्ठा sdw_port_runसमय *p_rt;
	पूर्णांक i;

	/* Iterate क्रम number of ports to perक्रमm initialization */
	क्रम (i = 0; i < num_ports; i++) अणु
		p_rt = sdw_port_alloc(bus->dev, port_config, i);
		अगर (!p_rt)
			वापस -ENOMEM;

		/*
		 * TODO: Check port capabilities क्रम requested
		 * configuration (audio mode support)
		 */

		list_add_tail(&p_rt->port_node, &m_rt->port_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdw_slave_port_config(काष्ठा sdw_slave *slave,
				 काष्ठा sdw_slave_runसमय *s_rt,
				 काष्ठा sdw_port_config *port_config,
				 अचिन्हित पूर्णांक num_config)
अणु
	काष्ठा sdw_port_runसमय *p_rt;
	पूर्णांक i, ret;

	/* Iterate क्रम number of ports to perक्रमm initialization */
	क्रम (i = 0; i < num_config; i++) अणु
		p_rt = sdw_port_alloc(&slave->dev, port_config, i);
		अगर (!p_rt)
			वापस -ENOMEM;

		/*
		 * TODO: Check valid port range as defined by DisCo/
		 * slave
		 */
		ret = sdw_is_valid_port_range(&slave->dev, p_rt);
		अगर (ret < 0) अणु
			kमुक्त(p_rt);
			वापस ret;
		पूर्ण

		/*
		 * TODO: Check port capabilities क्रम requested
		 * configuration (audio mode support)
		 */

		list_add_tail(&p_rt->port_node, &s_rt->port_list);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sdw_stream_add_master() - Allocate and add master runसमय to a stream
 *
 * @bus: SDW Bus instance
 * @stream_config: Stream configuration क्रम audio stream
 * @port_config: Port configuration क्रम audio stream
 * @num_ports: Number of ports
 * @stream: SoundWire stream
 */
पूर्णांक sdw_stream_add_master(काष्ठा sdw_bus *bus,
			  काष्ठा sdw_stream_config *stream_config,
			  काष्ठा sdw_port_config *port_config,
			  अचिन्हित पूर्णांक num_ports,
			  काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	पूर्णांक ret;

	mutex_lock(&bus->bus_lock);

	/*
	 * For multi link streams, add the second master only अगर
	 * the bus supports it.
	 * Check अगर bus->multi_link is set
	 */
	अगर (!bus->multi_link && stream->m_rt_count > 0) अणु
		dev_err(bus->dev,
			"Multilink not supported, link %d\n", bus->link_id);
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	m_rt = sdw_alloc_master_rt(bus, stream_config, stream);
	अगर (!m_rt) अणु
		dev_err(bus->dev,
			"Master runtime config failed for stream:%s\n",
			stream->name);
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	ret = sdw_config_stream(bus->dev, stream, stream_config, false);
	अगर (ret)
		जाओ stream_error;

	ret = sdw_master_port_config(bus, m_rt, port_config, num_ports);
	अगर (ret)
		जाओ stream_error;

	stream->m_rt_count++;

	जाओ unlock;

stream_error:
	sdw_release_master_stream(m_rt, stream);
unlock:
	mutex_unlock(&bus->bus_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_stream_add_master);

/**
 * sdw_stream_add_slave() - Allocate and add master/slave runसमय to a stream
 *
 * @slave: SDW Slave instance
 * @stream_config: Stream configuration क्रम audio stream
 * @stream: SoundWire stream
 * @port_config: Port configuration क्रम audio stream
 * @num_ports: Number of ports
 *
 * It is expected that Slave is added beक्रमe adding Master
 * to the Stream.
 *
 */
पूर्णांक sdw_stream_add_slave(काष्ठा sdw_slave *slave,
			 काष्ठा sdw_stream_config *stream_config,
			 काष्ठा sdw_port_config *port_config,
			 अचिन्हित पूर्णांक num_ports,
			 काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_slave_runसमय *s_rt;
	काष्ठा sdw_master_runसमय *m_rt;
	पूर्णांक ret;

	mutex_lock(&slave->bus->bus_lock);

	/*
	 * If this API is invoked by Slave first then m_rt is not valid.
	 * So, allocate m_rt and add Slave to it.
	 */
	m_rt = sdw_alloc_master_rt(slave->bus, stream_config, stream);
	अगर (!m_rt) अणु
		dev_err(&slave->dev,
			"alloc master runtime failed for stream:%s\n",
			stream->name);
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	s_rt = sdw_alloc_slave_rt(slave, stream_config, stream);
	अगर (!s_rt) अणु
		dev_err(&slave->dev,
			"Slave runtime config failed for stream:%s\n",
			stream->name);
		ret = -ENOMEM;
		जाओ stream_error;
	पूर्ण

	ret = sdw_config_stream(&slave->dev, stream, stream_config, true);
	अगर (ret) अणु
		/*
		 * sdw_release_master_stream will release s_rt in slave_rt_list in
		 * stream_error हाल, but s_rt is only added to slave_rt_list
		 * when sdw_config_stream is successful, so मुक्त s_rt explicitly
		 * when sdw_config_stream is failed.
		 */
		kमुक्त(s_rt);
		जाओ stream_error;
	पूर्ण

	list_add_tail(&s_rt->m_rt_node, &m_rt->slave_rt_list);

	ret = sdw_slave_port_config(slave, s_rt, port_config, num_ports);
	अगर (ret)
		जाओ stream_error;

	/*
	 * Change stream state to CONFIGURED on first Slave add.
	 * Bus is not aware of number of Slave(s) in a stream at this
	 * poपूर्णांक so cannot depend on all Slave(s) to be added in order to
	 * change stream state to CONFIGURED.
	 */
	stream->state = SDW_STREAM_CONFIGURED;
	जाओ error;

stream_error:
	/*
	 * we hit error so cleanup the stream, release all Slave(s) and
	 * Master runसमय
	 */
	sdw_release_master_stream(m_rt, stream);
error:
	mutex_unlock(&slave->bus->bus_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_stream_add_slave);

/**
 * sdw_get_slave_dpn_prop() - Get Slave port capabilities
 *
 * @slave: Slave handle
 * @direction: Data direction.
 * @port_num: Port number
 */
काष्ठा sdw_dpn_prop *sdw_get_slave_dpn_prop(काष्ठा sdw_slave *slave,
					    क्रमागत sdw_data_direction direction,
					    अचिन्हित पूर्णांक port_num)
अणु
	काष्ठा sdw_dpn_prop *dpn_prop;
	u8 num_ports;
	पूर्णांक i;

	अगर (direction == SDW_DATA_सूची_TX) अणु
		num_ports = hweight32(slave->prop.source_ports);
		dpn_prop = slave->prop.src_dpn_prop;
	पूर्ण अन्यथा अणु
		num_ports = hweight32(slave->prop.sink_ports);
		dpn_prop = slave->prop.sink_dpn_prop;
	पूर्ण

	क्रम (i = 0; i < num_ports; i++) अणु
		अगर (dpn_prop[i].num == port_num)
			वापस &dpn_prop[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * sdw_acquire_bus_lock: Acquire bus lock क्रम all Master runसमय(s)
 *
 * @stream: SoundWire stream
 *
 * Acquire bus_lock क्रम each of the master runसमय(m_rt) part of this
 * stream to reconfigure the bus.
 * NOTE: This function is called from SoundWire stream ops and is
 * expected that a global lock is held beक्रमe acquiring bus_lock.
 */
अटल व्योम sdw_acquire_bus_lock(काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	काष्ठा sdw_bus *bus;

	/* Iterate क्रम all Master(s) in Master list */
	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		bus = m_rt->bus;

		mutex_lock(&bus->bus_lock);
	पूर्ण
पूर्ण

/**
 * sdw_release_bus_lock: Release bus lock क्रम all Master runसमय(s)
 *
 * @stream: SoundWire stream
 *
 * Release the previously held bus_lock after reconfiguring the bus.
 * NOTE: This function is called from SoundWire stream ops and is
 * expected that a global lock is held beक्रमe releasing bus_lock.
 */
अटल व्योम sdw_release_bus_lock(काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	काष्ठा sdw_bus *bus;

	/* Iterate क्रम all Master(s) in Master list */
	list_क्रम_each_entry_reverse(m_rt, &stream->master_list, stream_node) अणु
		bus = m_rt->bus;
		mutex_unlock(&bus->bus_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक _sdw_prepare_stream(काष्ठा sdw_stream_runसमय *stream,
			       bool update_params)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	काष्ठा sdw_bus *bus = शून्य;
	काष्ठा sdw_master_prop *prop;
	काष्ठा sdw_bus_params params;
	पूर्णांक ret;

	/* Prepare  Master(s) and Slave(s) port(s) associated with stream */
	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		bus = m_rt->bus;
		prop = &bus->prop;
		स_नकल(&params, &bus->params, माप(params));

		/* TODO: Support Asynchronous mode */
		अगर ((prop->max_clk_freq % stream->params.rate) != 0) अणु
			dev_err(bus->dev, "Async mode not supported\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!update_params)
			जाओ program_params;

		/* Increment cumulative bus bandwidth */
		/* TODO: Update this during Device-Device support */
		bus->params.bandwidth += m_rt->stream->params.rate *
			m_rt->ch_count * m_rt->stream->params.bps;

		/* Compute params */
		अगर (bus->compute_params) अणु
			ret = bus->compute_params(bus);
			अगर (ret < 0) अणु
				dev_err(bus->dev, "Compute params failed: %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण

program_params:
		/* Program params */
		ret = sdw_program_params(bus, true);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Program params failed: %d\n", ret);
			जाओ restore_params;
		पूर्ण
	पूर्ण

	अगर (!bus) अणु
		pr_err("Configuration error in %s\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ret = करो_bank_चयन(stream);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "Bank switch failed: %d\n", ret);
		जाओ restore_params;
	पूर्ण

	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		bus = m_rt->bus;

		/* Prepare port(s) on the new घड़ी configuration */
		ret = sdw_prep_deprep_ports(m_rt, true);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Prepare port(s) failed ret = %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	stream->state = SDW_STREAM_PREPARED;

	वापस ret;

restore_params:
	स_नकल(&bus->params, &params, माप(params));
	वापस ret;
पूर्ण

/**
 * sdw_prepare_stream() - Prepare SoundWire stream
 *
 * @stream: Soundwire stream
 *
 * Documentation/driver-api/soundwire/stream.rst explains this API in detail
 */
पूर्णांक sdw_prepare_stream(काष्ठा sdw_stream_runसमय *stream)
अणु
	bool update_params = true;
	पूर्णांक ret;

	अगर (!stream) अणु
		pr_err("SoundWire: Handle not found for stream\n");
		वापस -EINVAL;
	पूर्ण

	sdw_acquire_bus_lock(stream);

	अगर (stream->state == SDW_STREAM_PREPARED) अणु
		ret = 0;
		जाओ state_err;
	पूर्ण

	अगर (stream->state != SDW_STREAM_CONFIGURED &&
	    stream->state != SDW_STREAM_DEPREPARED &&
	    stream->state != SDW_STREAM_DISABLED) अणु
		pr_err("%s: %s: inconsistent state state %d\n",
		       __func__, stream->name, stream->state);
		ret = -EINVAL;
		जाओ state_err;
	पूर्ण

	/*
	 * when the stream is DISABLED, this means sdw_prepare_stream()
	 * is called as a result of an underflow or a resume operation.
	 * In this हाल, the bus parameters shall not be recomputed, but
	 * still need to be re-applied
	 */
	अगर (stream->state == SDW_STREAM_DISABLED)
		update_params = false;

	ret = _sdw_prepare_stream(stream, update_params);

state_err:
	sdw_release_bus_lock(stream);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_prepare_stream);

अटल पूर्णांक _sdw_enable_stream(काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	काष्ठा sdw_bus *bus = शून्य;
	पूर्णांक ret;

	/* Enable Master(s) and Slave(s) port(s) associated with stream */
	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		bus = m_rt->bus;

		/* Program params */
		ret = sdw_program_params(bus, false);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Program params failed: %d\n", ret);
			वापस ret;
		पूर्ण

		/* Enable port(s) */
		ret = sdw_enable_disable_ports(m_rt, true);
		अगर (ret < 0) अणु
			dev_err(bus->dev,
				"Enable port(s) failed ret: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!bus) अणु
		pr_err("Configuration error in %s\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ret = करो_bank_चयन(stream);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "Bank switch failed: %d\n", ret);
		वापस ret;
	पूर्ण

	stream->state = SDW_STREAM_ENABLED;
	वापस 0;
पूर्ण

/**
 * sdw_enable_stream() - Enable SoundWire stream
 *
 * @stream: Soundwire stream
 *
 * Documentation/driver-api/soundwire/stream.rst explains this API in detail
 */
पूर्णांक sdw_enable_stream(काष्ठा sdw_stream_runसमय *stream)
अणु
	पूर्णांक ret;

	अगर (!stream) अणु
		pr_err("SoundWire: Handle not found for stream\n");
		वापस -EINVAL;
	पूर्ण

	sdw_acquire_bus_lock(stream);

	अगर (stream->state != SDW_STREAM_PREPARED &&
	    stream->state != SDW_STREAM_DISABLED) अणु
		pr_err("%s: %s: inconsistent state state %d\n",
		       __func__, stream->name, stream->state);
		ret = -EINVAL;
		जाओ state_err;
	पूर्ण

	ret = _sdw_enable_stream(stream);

state_err:
	sdw_release_bus_lock(stream);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_enable_stream);

अटल पूर्णांक _sdw_disable_stream(काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	पूर्णांक ret;

	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		काष्ठा sdw_bus *bus = m_rt->bus;

		/* Disable port(s) */
		ret = sdw_enable_disable_ports(m_rt, false);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Disable port(s) failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	stream->state = SDW_STREAM_DISABLED;

	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		काष्ठा sdw_bus *bus = m_rt->bus;

		/* Program params */
		ret = sdw_program_params(bus, false);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Program params failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = करो_bank_चयन(stream);
	अगर (ret < 0) अणु
		pr_err("Bank switch failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* make sure alternate bank (previous current) is also disabled */
	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		काष्ठा sdw_bus *bus = m_rt->bus;

		/* Disable port(s) */
		ret = sdw_enable_disable_ports(m_rt, false);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Disable port(s) failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sdw_disable_stream() - Disable SoundWire stream
 *
 * @stream: Soundwire stream
 *
 * Documentation/driver-api/soundwire/stream.rst explains this API in detail
 */
पूर्णांक sdw_disable_stream(काष्ठा sdw_stream_runसमय *stream)
अणु
	पूर्णांक ret;

	अगर (!stream) अणु
		pr_err("SoundWire: Handle not found for stream\n");
		वापस -EINVAL;
	पूर्ण

	sdw_acquire_bus_lock(stream);

	अगर (stream->state != SDW_STREAM_ENABLED) अणु
		pr_err("%s: %s: inconsistent state state %d\n",
		       __func__, stream->name, stream->state);
		ret = -EINVAL;
		जाओ state_err;
	पूर्ण

	ret = _sdw_disable_stream(stream);

state_err:
	sdw_release_bus_lock(stream);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_disable_stream);

अटल पूर्णांक _sdw_deprepare_stream(काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	काष्ठा sdw_bus *bus;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		bus = m_rt->bus;
		/* De-prepare port(s) */
		ret = sdw_prep_deprep_ports(m_rt, false);
		अगर (ret < 0) अणु
			dev_err(bus->dev,
				"De-prepare port(s) failed: %d\n", ret);
			वापस ret;
		पूर्ण

		/* TODO: Update this during Device-Device support */
		bus->params.bandwidth -= m_rt->stream->params.rate *
			m_rt->ch_count * m_rt->stream->params.bps;

		/* Compute params */
		अगर (bus->compute_params) अणु
			ret = bus->compute_params(bus);
			अगर (ret < 0) अणु
				dev_err(bus->dev, "Compute params failed: %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण

		/* Program params */
		ret = sdw_program_params(bus, false);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Program params failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	stream->state = SDW_STREAM_DEPREPARED;
	वापस करो_bank_चयन(stream);
पूर्ण

/**
 * sdw_deprepare_stream() - Deprepare SoundWire stream
 *
 * @stream: Soundwire stream
 *
 * Documentation/driver-api/soundwire/stream.rst explains this API in detail
 */
पूर्णांक sdw_deprepare_stream(काष्ठा sdw_stream_runसमय *stream)
अणु
	पूर्णांक ret;

	अगर (!stream) अणु
		pr_err("SoundWire: Handle not found for stream\n");
		वापस -EINVAL;
	पूर्ण

	sdw_acquire_bus_lock(stream);

	अगर (stream->state != SDW_STREAM_PREPARED &&
	    stream->state != SDW_STREAM_DISABLED) अणु
		pr_err("%s: %s: inconsistent state state %d\n",
		       __func__, stream->name, stream->state);
		ret = -EINVAL;
		जाओ state_err;
	पूर्ण

	ret = _sdw_deprepare_stream(stream);

state_err:
	sdw_release_bus_lock(stream);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_deprepare_stream);

अटल पूर्णांक set_stream(काष्ठा snd_pcm_substream *substream,
		      काष्ठा sdw_stream_runसमय *sdw_stream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_dai *dai;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* Set stream poपूर्णांकer on all DAIs */
	क्रम_each_rtd_dais(rtd, i, dai) अणु
		ret = snd_soc_dai_set_sdw_stream(dai, sdw_stream, substream->stream);
		अगर (ret < 0) अणु
			dev_err(rtd->dev, "failed to set stream pointer on dai %s\n", dai->name);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sdw_startup_stream() - Startup SoundWire stream
 *
 * @sdw_substream: Soundwire stream
 *
 * Documentation/driver-api/soundwire/stream.rst explains this API in detail
 */
पूर्णांक sdw_startup_stream(व्योम *sdw_substream)
अणु
	काष्ठा snd_pcm_substream *substream = sdw_substream;
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा sdw_stream_runसमय *sdw_stream;
	अक्षर *name;
	पूर्णांक ret;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		name = kaप्र_लिखो(GFP_KERNEL, "%s-Playback", substream->name);
	अन्यथा
		name = kaप्र_लिखो(GFP_KERNEL, "%s-Capture", substream->name);

	अगर (!name)
		वापस -ENOMEM;

	sdw_stream = sdw_alloc_stream(name);
	अगर (!sdw_stream) अणु
		dev_err(rtd->dev, "alloc stream failed for substream DAI %s\n", substream->name);
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	ret = set_stream(substream, sdw_stream);
	अगर (ret < 0)
		जाओ release_stream;
	वापस 0;

release_stream:
	sdw_release_stream(sdw_stream);
	set_stream(substream, शून्य);
error:
	kमुक्त(name);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_startup_stream);

/**
 * sdw_shutकरोwn_stream() - Shutकरोwn SoundWire stream
 *
 * @sdw_substream: Soundwire stream
 *
 * Documentation/driver-api/soundwire/stream.rst explains this API in detail
 */
व्योम sdw_shutकरोwn_stream(व्योम *sdw_substream)
अणु
	काष्ठा snd_pcm_substream *substream = sdw_substream;
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा sdw_stream_runसमय *sdw_stream;
	काष्ठा snd_soc_dai *dai;

	/* Find stream from first CPU DAI */
	dai = asoc_rtd_to_cpu(rtd, 0);

	sdw_stream = snd_soc_dai_get_sdw_stream(dai, substream->stream);

	अगर (IS_ERR(sdw_stream)) अणु
		dev_err(rtd->dev, "no stream found for DAI %s\n", dai->name);
		वापस;
	पूर्ण

	/* release memory */
	kमुक्त(sdw_stream->name);
	sdw_release_stream(sdw_stream);

	/* clear DAI data */
	set_stream(substream, शून्य);
पूर्ण
EXPORT_SYMBOL(sdw_shutकरोwn_stream);
