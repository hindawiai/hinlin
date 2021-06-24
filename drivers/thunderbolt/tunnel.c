<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt driver - Tunneling support
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2019, Intel Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>

#समावेश "tunnel.h"
#समावेश "tb.h"

/* PCIe adapters use always HopID of 8 क्रम both directions */
#घोषणा TB_PCI_HOPID			8

#घोषणा TB_PCI_PATH_DOWN		0
#घोषणा TB_PCI_PATH_UP			1

/* USB3 adapters use always HopID of 8 क्रम both directions */
#घोषणा TB_USB3_HOPID			8

#घोषणा TB_USB3_PATH_DOWN		0
#घोषणा TB_USB3_PATH_UP			1

/* DP adapters use HopID 8 क्रम AUX and 9 क्रम Video */
#घोषणा TB_DP_AUX_TX_HOPID		8
#घोषणा TB_DP_AUX_RX_HOPID		8
#घोषणा TB_DP_VIDEO_HOPID		9

#घोषणा TB_DP_VIDEO_PATH_OUT		0
#घोषणा TB_DP_AUX_PATH_OUT		1
#घोषणा TB_DP_AUX_PATH_IN		2

अटल स्थिर अक्षर * स्थिर tb_tunnel_names[] = अणु "PCI", "DP", "DMA", "USB3" पूर्ण;

#घोषणा __TB_TUNNEL_PRINT(level, tunnel, fmt, arg...)                   \
	करो अणु                                                            \
		काष्ठा tb_tunnel *__tunnel = (tunnel);                  \
		level(__tunnel->tb, "%llx:%x <-> %llx:%x (%s): " fmt,   \
		      tb_route(__tunnel->src_port->sw),                 \
		      __tunnel->src_port->port,                         \
		      tb_route(__tunnel->dst_port->sw),                 \
		      __tunnel->dst_port->port,                         \
		      tb_tunnel_names[__tunnel->type],			\
		      ## arg);                                          \
	पूर्ण जबतक (0)

#घोषणा tb_tunnel_WARN(tunnel, fmt, arg...) \
	__TB_TUNNEL_PRINT(tb_WARN, tunnel, fmt, ##arg)
#घोषणा tb_tunnel_warn(tunnel, fmt, arg...) \
	__TB_TUNNEL_PRINT(tb_warn, tunnel, fmt, ##arg)
#घोषणा tb_tunnel_info(tunnel, fmt, arg...) \
	__TB_TUNNEL_PRINT(tb_info, tunnel, fmt, ##arg)
#घोषणा tb_tunnel_dbg(tunnel, fmt, arg...) \
	__TB_TUNNEL_PRINT(tb_dbg, tunnel, fmt, ##arg)

अटल काष्ठा tb_tunnel *tb_tunnel_alloc(काष्ठा tb *tb, माप_प्रकार npaths,
					 क्रमागत tb_tunnel_type type)
अणु
	काष्ठा tb_tunnel *tunnel;

	tunnel = kzalloc(माप(*tunnel), GFP_KERNEL);
	अगर (!tunnel)
		वापस शून्य;

	tunnel->paths = kसुस्मृति(npaths, माप(tunnel->paths[0]), GFP_KERNEL);
	अगर (!tunnel->paths) अणु
		tb_tunnel_मुक्त(tunnel);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&tunnel->list);
	tunnel->tb = tb;
	tunnel->npaths = npaths;
	tunnel->type = type;

	वापस tunnel;
पूर्ण

अटल पूर्णांक tb_pci_activate(काष्ठा tb_tunnel *tunnel, bool activate)
अणु
	पूर्णांक res;

	res = tb_pci_port_enable(tunnel->src_port, activate);
	अगर (res)
		वापस res;

	अगर (tb_port_is_pcie_up(tunnel->dst_port))
		वापस tb_pci_port_enable(tunnel->dst_port, activate);

	वापस 0;
पूर्ण

अटल पूर्णांक tb_initial_credits(स्थिर काष्ठा tb_चयन *sw)
अणु
	/* If the path is complete sw is not शून्य */
	अगर (sw) अणु
		/* More credits क्रम faster link */
		चयन (sw->link_speed * sw->link_width) अणु
		हाल 40:
			वापस 32;
		हाल 20:
			वापस 24;
		पूर्ण
	पूर्ण

	वापस 16;
पूर्ण

अटल व्योम tb_pci_init_path(काष्ठा tb_path *path)
अणु
	path->egress_fc_enable = TB_PATH_SOURCE | TB_PATH_INTERNAL;
	path->egress_shared_buffer = TB_PATH_NONE;
	path->ingress_fc_enable = TB_PATH_ALL;
	path->ingress_shared_buffer = TB_PATH_NONE;
	path->priority = 3;
	path->weight = 1;
	path->drop_packages = 0;
	path->nfc_credits = 0;
	path->hops[0].initial_credits = 7;
	अगर (path->path_length > 1)
		path->hops[1].initial_credits =
			tb_initial_credits(path->hops[1].in_port->sw);
पूर्ण

/**
 * tb_tunnel_discover_pci() - Discover existing PCIe tunnels
 * @tb: Poपूर्णांकer to the करोमुख्य काष्ठाure
 * @करोwn: PCIe करोwnstream adapter
 *
 * If @करोwn adapter is active, follows the tunnel to the PCIe upstream
 * adapter and back. Returns the discovered tunnel or %शून्य अगर there was
 * no tunnel.
 */
काष्ठा tb_tunnel *tb_tunnel_discover_pci(काष्ठा tb *tb, काष्ठा tb_port *करोwn)
अणु
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_path *path;

	अगर (!tb_pci_port_is_enabled(करोwn))
		वापस शून्य;

	tunnel = tb_tunnel_alloc(tb, 2, TB_TUNNEL_PCI);
	अगर (!tunnel)
		वापस शून्य;

	tunnel->activate = tb_pci_activate;
	tunnel->src_port = करोwn;

	/*
	 * Discover both paths even अगर they are not complete. We will
	 * clean them up by calling tb_tunnel_deactivate() below in that
	 * हाल.
	 */
	path = tb_path_discover(करोwn, TB_PCI_HOPID, शून्य, -1,
				&tunnel->dst_port, "PCIe Up");
	अगर (!path) अणु
		/* Just disable the करोwnstream port */
		tb_pci_port_enable(करोwn, false);
		जाओ err_मुक्त;
	पूर्ण
	tunnel->paths[TB_PCI_PATH_UP] = path;
	tb_pci_init_path(tunnel->paths[TB_PCI_PATH_UP]);

	path = tb_path_discover(tunnel->dst_port, -1, करोwn, TB_PCI_HOPID, शून्य,
				"PCIe Down");
	अगर (!path)
		जाओ err_deactivate;
	tunnel->paths[TB_PCI_PATH_DOWN] = path;
	tb_pci_init_path(tunnel->paths[TB_PCI_PATH_DOWN]);

	/* Validate that the tunnel is complete */
	अगर (!tb_port_is_pcie_up(tunnel->dst_port)) अणु
		tb_port_warn(tunnel->dst_port,
			     "path does not end on a PCIe adapter, cleaning up\n");
		जाओ err_deactivate;
	पूर्ण

	अगर (करोwn != tunnel->src_port) अणु
		tb_tunnel_warn(tunnel, "path is not complete, cleaning up\n");
		जाओ err_deactivate;
	पूर्ण

	अगर (!tb_pci_port_is_enabled(tunnel->dst_port)) अणु
		tb_tunnel_warn(tunnel,
			       "tunnel is not fully activated, cleaning up\n");
		जाओ err_deactivate;
	पूर्ण

	tb_tunnel_dbg(tunnel, "discovered\n");
	वापस tunnel;

err_deactivate:
	tb_tunnel_deactivate(tunnel);
err_मुक्त:
	tb_tunnel_मुक्त(tunnel);

	वापस शून्य;
पूर्ण

/**
 * tb_tunnel_alloc_pci() - allocate a pci tunnel
 * @tb: Poपूर्णांकer to the करोमुख्य काष्ठाure
 * @up: PCIe upstream adapter port
 * @करोwn: PCIe करोwnstream adapter port
 *
 * Allocate a PCI tunnel. The ports must be of type TB_TYPE_PCIE_UP and
 * TB_TYPE_PCIE_DOWN.
 *
 * Return: Returns a tb_tunnel on success or शून्य on failure.
 */
काष्ठा tb_tunnel *tb_tunnel_alloc_pci(काष्ठा tb *tb, काष्ठा tb_port *up,
				      काष्ठा tb_port *करोwn)
अणु
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_path *path;

	tunnel = tb_tunnel_alloc(tb, 2, TB_TUNNEL_PCI);
	अगर (!tunnel)
		वापस शून्य;

	tunnel->activate = tb_pci_activate;
	tunnel->src_port = करोwn;
	tunnel->dst_port = up;

	path = tb_path_alloc(tb, करोwn, TB_PCI_HOPID, up, TB_PCI_HOPID, 0,
			     "PCIe Down");
	अगर (!path) अणु
		tb_tunnel_मुक्त(tunnel);
		वापस शून्य;
	पूर्ण
	tb_pci_init_path(path);
	tunnel->paths[TB_PCI_PATH_DOWN] = path;

	path = tb_path_alloc(tb, up, TB_PCI_HOPID, करोwn, TB_PCI_HOPID, 0,
			     "PCIe Up");
	अगर (!path) अणु
		tb_tunnel_मुक्त(tunnel);
		वापस शून्य;
	पूर्ण
	tb_pci_init_path(path);
	tunnel->paths[TB_PCI_PATH_UP] = path;

	वापस tunnel;
पूर्ण

अटल bool tb_dp_is_usb4(स्थिर काष्ठा tb_चयन *sw)
अणु
	/* Titan Ridge DP adapters need the same treaपंचांगent as USB4 */
	वापस tb_चयन_is_usb4(sw) || tb_चयन_is_titan_ridge(sw);
पूर्ण

अटल पूर्णांक tb_dp_cm_handshake(काष्ठा tb_port *in, काष्ठा tb_port *out)
अणु
	पूर्णांक समयout = 10;
	u32 val;
	पूर्णांक ret;

	/* Both ends need to support this */
	अगर (!tb_dp_is_usb4(in->sw) || !tb_dp_is_usb4(out->sw))
		वापस 0;

	ret = tb_port_पढ़ो(out, &val, TB_CFG_PORT,
			   out->cap_adap + DP_STATUS_CTRL, 1);
	अगर (ret)
		वापस ret;

	val |= DP_STATUS_CTRL_UF | DP_STATUS_CTRL_CMHS;

	ret = tb_port_ग_लिखो(out, &val, TB_CFG_PORT,
			    out->cap_adap + DP_STATUS_CTRL, 1);
	अगर (ret)
		वापस ret;

	करो अणु
		ret = tb_port_पढ़ो(out, &val, TB_CFG_PORT,
				   out->cap_adap + DP_STATUS_CTRL, 1);
		अगर (ret)
			वापस ret;
		अगर (!(val & DP_STATUS_CTRL_CMHS))
			वापस 0;
		usleep_range(10, 100);
	पूर्ण जबतक (समयout--);

	वापस -ETIMEDOUT;
पूर्ण

अटल अंतरभूत u32 tb_dp_cap_get_rate(u32 val)
अणु
	u32 rate = (val & DP_COMMON_CAP_RATE_MASK) >> DP_COMMON_CAP_RATE_SHIFT;

	चयन (rate) अणु
	हाल DP_COMMON_CAP_RATE_RBR:
		वापस 1620;
	हाल DP_COMMON_CAP_RATE_HBR:
		वापस 2700;
	हाल DP_COMMON_CAP_RATE_HBR2:
		वापस 5400;
	हाल DP_COMMON_CAP_RATE_HBR3:
		वापस 8100;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 tb_dp_cap_set_rate(u32 val, u32 rate)
अणु
	val &= ~DP_COMMON_CAP_RATE_MASK;
	चयन (rate) अणु
	शेष:
		WARN(1, "invalid rate %u passed, defaulting to 1620 MB/s\n", rate);
		fallthrough;
	हाल 1620:
		val |= DP_COMMON_CAP_RATE_RBR << DP_COMMON_CAP_RATE_SHIFT;
		अवरोध;
	हाल 2700:
		val |= DP_COMMON_CAP_RATE_HBR << DP_COMMON_CAP_RATE_SHIFT;
		अवरोध;
	हाल 5400:
		val |= DP_COMMON_CAP_RATE_HBR2 << DP_COMMON_CAP_RATE_SHIFT;
		अवरोध;
	हाल 8100:
		val |= DP_COMMON_CAP_RATE_HBR3 << DP_COMMON_CAP_RATE_SHIFT;
		अवरोध;
	पूर्ण
	वापस val;
पूर्ण

अटल अंतरभूत u32 tb_dp_cap_get_lanes(u32 val)
अणु
	u32 lanes = (val & DP_COMMON_CAP_LANES_MASK) >> DP_COMMON_CAP_LANES_SHIFT;

	चयन (lanes) अणु
	हाल DP_COMMON_CAP_1_LANE:
		वापस 1;
	हाल DP_COMMON_CAP_2_LANES:
		वापस 2;
	हाल DP_COMMON_CAP_4_LANES:
		वापस 4;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 tb_dp_cap_set_lanes(u32 val, u32 lanes)
अणु
	val &= ~DP_COMMON_CAP_LANES_MASK;
	चयन (lanes) अणु
	शेष:
		WARN(1, "invalid number of lanes %u passed, defaulting to 1\n",
		     lanes);
		fallthrough;
	हाल 1:
		val |= DP_COMMON_CAP_1_LANE << DP_COMMON_CAP_LANES_SHIFT;
		अवरोध;
	हाल 2:
		val |= DP_COMMON_CAP_2_LANES << DP_COMMON_CAP_LANES_SHIFT;
		अवरोध;
	हाल 4:
		val |= DP_COMMON_CAP_4_LANES << DP_COMMON_CAP_LANES_SHIFT;
		अवरोध;
	पूर्ण
	वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक tb_dp_bandwidth(अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक lanes)
अणु
	/* Tunneling हटाओs the DP 8b/10b encoding */
	वापस rate * lanes * 8 / 10;
पूर्ण

अटल पूर्णांक tb_dp_reduce_bandwidth(पूर्णांक max_bw, u32 in_rate, u32 in_lanes,
				  u32 out_rate, u32 out_lanes, u32 *new_rate,
				  u32 *new_lanes)
अणु
	अटल स्थिर u32 dp_bw[][2] = अणु
		/* Mb/s, lanes */
		अणु 8100, 4 पूर्ण, /* 25920 Mb/s */
		अणु 5400, 4 पूर्ण, /* 17280 Mb/s */
		अणु 8100, 2 पूर्ण, /* 12960 Mb/s */
		अणु 2700, 4 पूर्ण, /* 8640 Mb/s */
		अणु 5400, 2 पूर्ण, /* 8640 Mb/s */
		अणु 8100, 1 पूर्ण, /* 6480 Mb/s */
		अणु 1620, 4 पूर्ण, /* 5184 Mb/s */
		अणु 5400, 1 पूर्ण, /* 4320 Mb/s */
		अणु 2700, 2 पूर्ण, /* 4320 Mb/s */
		अणु 1620, 2 पूर्ण, /* 2592 Mb/s */
		अणु 2700, 1 पूर्ण, /* 2160 Mb/s */
		अणु 1620, 1 पूर्ण, /* 1296 Mb/s */
	पूर्ण;
	अचिन्हित पूर्णांक i;

	/*
	 * Find a combination that can fit पूर्णांकo max_bw and करोes not
	 * exceed the maximum rate and lanes supported by the DP OUT and
	 * DP IN adapters.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(dp_bw); i++) अणु
		अगर (dp_bw[i][0] > out_rate || dp_bw[i][1] > out_lanes)
			जारी;

		अगर (dp_bw[i][0] > in_rate || dp_bw[i][1] > in_lanes)
			जारी;

		अगर (tb_dp_bandwidth(dp_bw[i][0], dp_bw[i][1]) <= max_bw) अणु
			*new_rate = dp_bw[i][0];
			*new_lanes = dp_bw[i][1];
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOSR;
पूर्ण

अटल पूर्णांक tb_dp_xchg_caps(काष्ठा tb_tunnel *tunnel)
अणु
	u32 out_dp_cap, out_rate, out_lanes, in_dp_cap, in_rate, in_lanes, bw;
	काष्ठा tb_port *out = tunnel->dst_port;
	काष्ठा tb_port *in = tunnel->src_port;
	पूर्णांक ret, max_bw;

	/*
	 * Copy DP_LOCAL_CAP रेजिस्टर to DP_REMOTE_CAP रेजिस्टर क्रम
	 * newer generation hardware.
	 */
	अगर (in->sw->generation < 2 || out->sw->generation < 2)
		वापस 0;

	/*
	 * Perक्रमm connection manager handshake between IN and OUT ports
	 * beक्रमe capabilities exchange can take place.
	 */
	ret = tb_dp_cm_handshake(in, out);
	अगर (ret)
		वापस ret;

	/* Read both DP_LOCAL_CAP रेजिस्टरs */
	ret = tb_port_पढ़ो(in, &in_dp_cap, TB_CFG_PORT,
			   in->cap_adap + DP_LOCAL_CAP, 1);
	अगर (ret)
		वापस ret;

	ret = tb_port_पढ़ो(out, &out_dp_cap, TB_CFG_PORT,
			   out->cap_adap + DP_LOCAL_CAP, 1);
	अगर (ret)
		वापस ret;

	/* Write IN local caps to OUT remote caps */
	ret = tb_port_ग_लिखो(out, &in_dp_cap, TB_CFG_PORT,
			    out->cap_adap + DP_REMOTE_CAP, 1);
	अगर (ret)
		वापस ret;

	in_rate = tb_dp_cap_get_rate(in_dp_cap);
	in_lanes = tb_dp_cap_get_lanes(in_dp_cap);
	tb_port_dbg(in, "maximum supported bandwidth %u Mb/s x%u = %u Mb/s\n",
		    in_rate, in_lanes, tb_dp_bandwidth(in_rate, in_lanes));

	/*
	 * If the tunnel bandwidth is limited (max_bw is set) then see
	 * अगर we need to reduce bandwidth to fit there.
	 */
	out_rate = tb_dp_cap_get_rate(out_dp_cap);
	out_lanes = tb_dp_cap_get_lanes(out_dp_cap);
	bw = tb_dp_bandwidth(out_rate, out_lanes);
	tb_port_dbg(out, "maximum supported bandwidth %u Mb/s x%u = %u Mb/s\n",
		    out_rate, out_lanes, bw);

	अगर (in->sw->config.depth < out->sw->config.depth)
		max_bw = tunnel->max_करोwn;
	अन्यथा
		max_bw = tunnel->max_up;

	अगर (max_bw && bw > max_bw) अणु
		u32 new_rate, new_lanes, new_bw;

		ret = tb_dp_reduce_bandwidth(max_bw, in_rate, in_lanes,
					     out_rate, out_lanes, &new_rate,
					     &new_lanes);
		अगर (ret) अणु
			tb_port_info(out, "not enough bandwidth for DP tunnel\n");
			वापस ret;
		पूर्ण

		new_bw = tb_dp_bandwidth(new_rate, new_lanes);
		tb_port_dbg(out, "bandwidth reduced to %u Mb/s x%u = %u Mb/s\n",
			    new_rate, new_lanes, new_bw);

		/*
		 * Set new rate and number of lanes beक्रमe writing it to
		 * the IN port remote caps.
		 */
		out_dp_cap = tb_dp_cap_set_rate(out_dp_cap, new_rate);
		out_dp_cap = tb_dp_cap_set_lanes(out_dp_cap, new_lanes);
	पूर्ण

	वापस tb_port_ग_लिखो(in, &out_dp_cap, TB_CFG_PORT,
			     in->cap_adap + DP_REMOTE_CAP, 1);
पूर्ण

अटल पूर्णांक tb_dp_activate(काष्ठा tb_tunnel *tunnel, bool active)
अणु
	पूर्णांक ret;

	अगर (active) अणु
		काष्ठा tb_path **paths;
		पूर्णांक last;

		paths = tunnel->paths;
		last = paths[TB_DP_VIDEO_PATH_OUT]->path_length - 1;

		tb_dp_port_set_hops(tunnel->src_port,
			paths[TB_DP_VIDEO_PATH_OUT]->hops[0].in_hop_index,
			paths[TB_DP_AUX_PATH_OUT]->hops[0].in_hop_index,
			paths[TB_DP_AUX_PATH_IN]->hops[last].next_hop_index);

		tb_dp_port_set_hops(tunnel->dst_port,
			paths[TB_DP_VIDEO_PATH_OUT]->hops[last].next_hop_index,
			paths[TB_DP_AUX_PATH_IN]->hops[0].in_hop_index,
			paths[TB_DP_AUX_PATH_OUT]->hops[last].next_hop_index);
	पूर्ण अन्यथा अणु
		tb_dp_port_hpd_clear(tunnel->src_port);
		tb_dp_port_set_hops(tunnel->src_port, 0, 0, 0);
		अगर (tb_port_is_dpout(tunnel->dst_port))
			tb_dp_port_set_hops(tunnel->dst_port, 0, 0, 0);
	पूर्ण

	ret = tb_dp_port_enable(tunnel->src_port, active);
	अगर (ret)
		वापस ret;

	अगर (tb_port_is_dpout(tunnel->dst_port))
		वापस tb_dp_port_enable(tunnel->dst_port, active);

	वापस 0;
पूर्ण

अटल पूर्णांक tb_dp_consumed_bandwidth(काष्ठा tb_tunnel *tunnel, पूर्णांक *consumed_up,
				    पूर्णांक *consumed_करोwn)
अणु
	काष्ठा tb_port *in = tunnel->src_port;
	स्थिर काष्ठा tb_चयन *sw = in->sw;
	u32 val, rate = 0, lanes = 0;
	पूर्णांक ret;

	अगर (tb_dp_is_usb4(sw)) अणु
		पूर्णांक समयout = 20;

		/*
		 * Wait क्रम DPRX करोne. Normally it should be alपढ़ोy set
		 * क्रम active tunnel.
		 */
		करो अणु
			ret = tb_port_पढ़ो(in, &val, TB_CFG_PORT,
					   in->cap_adap + DP_COMMON_CAP, 1);
			अगर (ret)
				वापस ret;

			अगर (val & DP_COMMON_CAP_DPRX_DONE) अणु
				rate = tb_dp_cap_get_rate(val);
				lanes = tb_dp_cap_get_lanes(val);
				अवरोध;
			पूर्ण
			msleep(250);
		पूर्ण जबतक (समयout--);

		अगर (!समयout)
			वापस -ETIMEDOUT;
	पूर्ण अन्यथा अगर (sw->generation >= 2) अणु
		/*
		 * Read from the copied remote cap so that we take पूर्णांकo
		 * account अगर capabilities were reduced during exchange.
		 */
		ret = tb_port_पढ़ो(in, &val, TB_CFG_PORT,
				   in->cap_adap + DP_REMOTE_CAP, 1);
		अगर (ret)
			वापस ret;

		rate = tb_dp_cap_get_rate(val);
		lanes = tb_dp_cap_get_lanes(val);
	पूर्ण अन्यथा अणु
		/* No bandwidth management क्रम legacy devices  */
		*consumed_up = 0;
		*consumed_करोwn = 0;
		वापस 0;
	पूर्ण

	अगर (in->sw->config.depth < tunnel->dst_port->sw->config.depth) अणु
		*consumed_up = 0;
		*consumed_करोwn = tb_dp_bandwidth(rate, lanes);
	पूर्ण अन्यथा अणु
		*consumed_up = tb_dp_bandwidth(rate, lanes);
		*consumed_करोwn = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tb_dp_init_aux_path(काष्ठा tb_path *path)
अणु
	पूर्णांक i;

	path->egress_fc_enable = TB_PATH_SOURCE | TB_PATH_INTERNAL;
	path->egress_shared_buffer = TB_PATH_NONE;
	path->ingress_fc_enable = TB_PATH_ALL;
	path->ingress_shared_buffer = TB_PATH_NONE;
	path->priority = 2;
	path->weight = 1;

	क्रम (i = 0; i < path->path_length; i++)
		path->hops[i].initial_credits = 1;
पूर्ण

अटल व्योम tb_dp_init_video_path(काष्ठा tb_path *path, bool discover)
अणु
	u32 nfc_credits = path->hops[0].in_port->config.nfc_credits;

	path->egress_fc_enable = TB_PATH_NONE;
	path->egress_shared_buffer = TB_PATH_NONE;
	path->ingress_fc_enable = TB_PATH_NONE;
	path->ingress_shared_buffer = TB_PATH_NONE;
	path->priority = 1;
	path->weight = 1;

	अगर (discover) अणु
		path->nfc_credits = nfc_credits & ADP_CS_4_NFC_BUFFERS_MASK;
	पूर्ण अन्यथा अणु
		u32 max_credits;

		max_credits = (nfc_credits & ADP_CS_4_TOTAL_BUFFERS_MASK) >>
			ADP_CS_4_TOTAL_BUFFERS_SHIFT;
		/* Leave some credits क्रम AUX path */
		path->nfc_credits = min(max_credits - 2, 12U);
	पूर्ण
पूर्ण

/**
 * tb_tunnel_discover_dp() - Discover existing Display Port tunnels
 * @tb: Poपूर्णांकer to the करोमुख्य काष्ठाure
 * @in: DP in adapter
 *
 * If @in adapter is active, follows the tunnel to the DP out adapter
 * and back. Returns the discovered tunnel or %शून्य अगर there was no
 * tunnel.
 *
 * Return: DP tunnel or %शून्य अगर no tunnel found.
 */
काष्ठा tb_tunnel *tb_tunnel_discover_dp(काष्ठा tb *tb, काष्ठा tb_port *in)
अणु
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_port *port;
	काष्ठा tb_path *path;

	अगर (!tb_dp_port_is_enabled(in))
		वापस शून्य;

	tunnel = tb_tunnel_alloc(tb, 3, TB_TUNNEL_DP);
	अगर (!tunnel)
		वापस शून्य;

	tunnel->init = tb_dp_xchg_caps;
	tunnel->activate = tb_dp_activate;
	tunnel->consumed_bandwidth = tb_dp_consumed_bandwidth;
	tunnel->src_port = in;

	path = tb_path_discover(in, TB_DP_VIDEO_HOPID, शून्य, -1,
				&tunnel->dst_port, "Video");
	अगर (!path) अणु
		/* Just disable the DP IN port */
		tb_dp_port_enable(in, false);
		जाओ err_मुक्त;
	पूर्ण
	tunnel->paths[TB_DP_VIDEO_PATH_OUT] = path;
	tb_dp_init_video_path(tunnel->paths[TB_DP_VIDEO_PATH_OUT], true);

	path = tb_path_discover(in, TB_DP_AUX_TX_HOPID, शून्य, -1, शून्य, "AUX TX");
	अगर (!path)
		जाओ err_deactivate;
	tunnel->paths[TB_DP_AUX_PATH_OUT] = path;
	tb_dp_init_aux_path(tunnel->paths[TB_DP_AUX_PATH_OUT]);

	path = tb_path_discover(tunnel->dst_port, -1, in, TB_DP_AUX_RX_HOPID,
				&port, "AUX RX");
	अगर (!path)
		जाओ err_deactivate;
	tunnel->paths[TB_DP_AUX_PATH_IN] = path;
	tb_dp_init_aux_path(tunnel->paths[TB_DP_AUX_PATH_IN]);

	/* Validate that the tunnel is complete */
	अगर (!tb_port_is_dpout(tunnel->dst_port)) अणु
		tb_port_warn(in, "path does not end on a DP adapter, cleaning up\n");
		जाओ err_deactivate;
	पूर्ण

	अगर (!tb_dp_port_is_enabled(tunnel->dst_port))
		जाओ err_deactivate;

	अगर (!tb_dp_port_hpd_is_active(tunnel->dst_port))
		जाओ err_deactivate;

	अगर (port != tunnel->src_port) अणु
		tb_tunnel_warn(tunnel, "path is not complete, cleaning up\n");
		जाओ err_deactivate;
	पूर्ण

	tb_tunnel_dbg(tunnel, "discovered\n");
	वापस tunnel;

err_deactivate:
	tb_tunnel_deactivate(tunnel);
err_मुक्त:
	tb_tunnel_मुक्त(tunnel);

	वापस शून्य;
पूर्ण

/**
 * tb_tunnel_alloc_dp() - allocate a Display Port tunnel
 * @tb: Poपूर्णांकer to the करोमुख्य काष्ठाure
 * @in: DP in adapter port
 * @out: DP out adapter port
 * @max_up: Maximum available upstream bandwidth क्रम the DP tunnel (%0
 *	    अगर not limited)
 * @max_करोwn: Maximum available करोwnstream bandwidth क्रम the DP tunnel
 *	      (%0 अगर not limited)
 *
 * Allocates a tunnel between @in and @out that is capable of tunneling
 * Display Port traffic.
 *
 * Return: Returns a tb_tunnel on success or शून्य on failure.
 */
काष्ठा tb_tunnel *tb_tunnel_alloc_dp(काष्ठा tb *tb, काष्ठा tb_port *in,
				     काष्ठा tb_port *out, पूर्णांक max_up,
				     पूर्णांक max_करोwn)
अणु
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_path **paths;
	काष्ठा tb_path *path;

	अगर (WARN_ON(!in->cap_adap || !out->cap_adap))
		वापस शून्य;

	tunnel = tb_tunnel_alloc(tb, 3, TB_TUNNEL_DP);
	अगर (!tunnel)
		वापस शून्य;

	tunnel->init = tb_dp_xchg_caps;
	tunnel->activate = tb_dp_activate;
	tunnel->consumed_bandwidth = tb_dp_consumed_bandwidth;
	tunnel->src_port = in;
	tunnel->dst_port = out;
	tunnel->max_up = max_up;
	tunnel->max_करोwn = max_करोwn;

	paths = tunnel->paths;

	path = tb_path_alloc(tb, in, TB_DP_VIDEO_HOPID, out, TB_DP_VIDEO_HOPID,
			     1, "Video");
	अगर (!path)
		जाओ err_मुक्त;
	tb_dp_init_video_path(path, false);
	paths[TB_DP_VIDEO_PATH_OUT] = path;

	path = tb_path_alloc(tb, in, TB_DP_AUX_TX_HOPID, out,
			     TB_DP_AUX_TX_HOPID, 1, "AUX TX");
	अगर (!path)
		जाओ err_मुक्त;
	tb_dp_init_aux_path(path);
	paths[TB_DP_AUX_PATH_OUT] = path;

	path = tb_path_alloc(tb, out, TB_DP_AUX_RX_HOPID, in,
			     TB_DP_AUX_RX_HOPID, 1, "AUX RX");
	अगर (!path)
		जाओ err_मुक्त;
	tb_dp_init_aux_path(path);
	paths[TB_DP_AUX_PATH_IN] = path;

	वापस tunnel;

err_मुक्त:
	tb_tunnel_मुक्त(tunnel);
	वापस शून्य;
पूर्ण

अटल u32 tb_dma_credits(काष्ठा tb_port *nhi)
अणु
	u32 max_credits;

	max_credits = (nhi->config.nfc_credits & ADP_CS_4_TOTAL_BUFFERS_MASK) >>
		ADP_CS_4_TOTAL_BUFFERS_SHIFT;
	वापस min(max_credits, 13U);
पूर्ण

अटल व्योम tb_dma_init_path(काष्ठा tb_path *path, अचिन्हित पूर्णांक efc, u32 credits)
अणु
	पूर्णांक i;

	path->egress_fc_enable = efc;
	path->ingress_fc_enable = TB_PATH_ALL;
	path->egress_shared_buffer = TB_PATH_NONE;
	path->ingress_shared_buffer = TB_PATH_NONE;
	path->priority = 5;
	path->weight = 1;
	path->clear_fc = true;

	क्रम (i = 0; i < path->path_length; i++)
		path->hops[i].initial_credits = credits;
पूर्ण

/**
 * tb_tunnel_alloc_dma() - allocate a DMA tunnel
 * @tb: Poपूर्णांकer to the करोमुख्य काष्ठाure
 * @nhi: Host controller port
 * @dst: Destination null port which the other करोमुख्य is connected to
 * @transmit_path: HopID used क्रम transmitting packets
 * @transmit_ring: NHI ring number used to send packets towards the
 *		   other करोमुख्य. Set to %-1 अगर TX path is not needed.
 * @receive_path: HopID used क्रम receiving packets
 * @receive_ring: NHI ring number used to receive packets from the
 *		  other करोमुख्य. Set to %-1 अगर RX path is not needed.
 *
 * Return: Returns a tb_tunnel on success or शून्य on failure.
 */
काष्ठा tb_tunnel *tb_tunnel_alloc_dma(काष्ठा tb *tb, काष्ठा tb_port *nhi,
				      काष्ठा tb_port *dst, पूर्णांक transmit_path,
				      पूर्णांक transmit_ring, पूर्णांक receive_path,
				      पूर्णांक receive_ring)
अणु
	काष्ठा tb_tunnel *tunnel;
	माप_प्रकार npaths = 0, i = 0;
	काष्ठा tb_path *path;
	u32 credits;

	अगर (receive_ring > 0)
		npaths++;
	अगर (transmit_ring > 0)
		npaths++;

	अगर (WARN_ON(!npaths))
		वापस शून्य;

	tunnel = tb_tunnel_alloc(tb, npaths, TB_TUNNEL_DMA);
	अगर (!tunnel)
		वापस शून्य;

	tunnel->src_port = nhi;
	tunnel->dst_port = dst;

	credits = tb_dma_credits(nhi);

	अगर (receive_ring > 0) अणु
		path = tb_path_alloc(tb, dst, receive_path, nhi, receive_ring, 0,
				     "DMA RX");
		अगर (!path) अणु
			tb_tunnel_मुक्त(tunnel);
			वापस शून्य;
		पूर्ण
		tb_dma_init_path(path, TB_PATH_SOURCE | TB_PATH_INTERNAL, credits);
		tunnel->paths[i++] = path;
	पूर्ण

	अगर (transmit_ring > 0) अणु
		path = tb_path_alloc(tb, nhi, transmit_ring, dst, transmit_path, 0,
				     "DMA TX");
		अगर (!path) अणु
			tb_tunnel_मुक्त(tunnel);
			वापस शून्य;
		पूर्ण
		tb_dma_init_path(path, TB_PATH_ALL, credits);
		tunnel->paths[i++] = path;
	पूर्ण

	वापस tunnel;
पूर्ण

/**
 * tb_tunnel_match_dma() - Match DMA tunnel
 * @tunnel: Tunnel to match
 * @transmit_path: HopID used क्रम transmitting packets. Pass %-1 to ignore.
 * @transmit_ring: NHI ring number used to send packets towards the
 *		   other करोमुख्य. Pass %-1 to ignore.
 * @receive_path: HopID used क्रम receiving packets. Pass %-1 to ignore.
 * @receive_ring: NHI ring number used to receive packets from the
 *		  other करोमुख्य. Pass %-1 to ignore.
 *
 * This function can be used to match specअगरic DMA tunnel, अगर there are
 * multiple DMA tunnels going through the same XDoमुख्य connection.
 * Returns true अगर there is match and false otherwise.
 */
bool tb_tunnel_match_dma(स्थिर काष्ठा tb_tunnel *tunnel, पूर्णांक transmit_path,
			 पूर्णांक transmit_ring, पूर्णांक receive_path, पूर्णांक receive_ring)
अणु
	स्थिर काष्ठा tb_path *tx_path = शून्य, *rx_path = शून्य;
	पूर्णांक i;

	अगर (!receive_ring || !transmit_ring)
		वापस false;

	क्रम (i = 0; i < tunnel->npaths; i++) अणु
		स्थिर काष्ठा tb_path *path = tunnel->paths[i];

		अगर (!path)
			जारी;

		अगर (tb_port_is_nhi(path->hops[0].in_port))
			tx_path = path;
		अन्यथा अगर (tb_port_is_nhi(path->hops[path->path_length - 1].out_port))
			rx_path = path;
	पूर्ण

	अगर (transmit_ring > 0 || transmit_path > 0) अणु
		अगर (!tx_path)
			वापस false;
		अगर (transmit_ring > 0 &&
		    (tx_path->hops[0].in_hop_index != transmit_ring))
			वापस false;
		अगर (transmit_path > 0 &&
		    (tx_path->hops[tx_path->path_length - 1].next_hop_index != transmit_path))
			वापस false;
	पूर्ण

	अगर (receive_ring > 0 || receive_path > 0) अणु
		अगर (!rx_path)
			वापस false;
		अगर (receive_path > 0 &&
		    (rx_path->hops[0].in_hop_index != receive_path))
			वापस false;
		अगर (receive_ring > 0 &&
		    (rx_path->hops[rx_path->path_length - 1].next_hop_index != receive_ring))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक tb_usb3_max_link_rate(काष्ठा tb_port *up, काष्ठा tb_port *करोwn)
अणु
	पूर्णांक ret, up_max_rate, करोwn_max_rate;

	ret = usb4_usb3_port_max_link_rate(up);
	अगर (ret < 0)
		वापस ret;
	up_max_rate = ret;

	ret = usb4_usb3_port_max_link_rate(करोwn);
	अगर (ret < 0)
		वापस ret;
	करोwn_max_rate = ret;

	वापस min(up_max_rate, करोwn_max_rate);
पूर्ण

अटल पूर्णांक tb_usb3_init(काष्ठा tb_tunnel *tunnel)
अणु
	tb_tunnel_dbg(tunnel, "allocating initial bandwidth %d/%d Mb/s\n",
		      tunnel->allocated_up, tunnel->allocated_करोwn);

	वापस usb4_usb3_port_allocate_bandwidth(tunnel->src_port,
						 &tunnel->allocated_up,
						 &tunnel->allocated_करोwn);
पूर्ण

अटल पूर्णांक tb_usb3_activate(काष्ठा tb_tunnel *tunnel, bool activate)
अणु
	पूर्णांक res;

	res = tb_usb3_port_enable(tunnel->src_port, activate);
	अगर (res)
		वापस res;

	अगर (tb_port_is_usb3_up(tunnel->dst_port))
		वापस tb_usb3_port_enable(tunnel->dst_port, activate);

	वापस 0;
पूर्ण

अटल पूर्णांक tb_usb3_consumed_bandwidth(काष्ठा tb_tunnel *tunnel,
		पूर्णांक *consumed_up, पूर्णांक *consumed_करोwn)
अणु
	पूर्णांक pcie_enabled = tb_acpi_may_tunnel_pcie();

	/*
	 * PCIe tunneling, अगर enabled, affects the USB3 bandwidth so
	 * take that it पूर्णांकo account here.
	 */
	*consumed_up = tunnel->allocated_up * (3 + pcie_enabled) / 3;
	*consumed_करोwn = tunnel->allocated_करोwn * (3 + pcie_enabled) / 3;
	वापस 0;
पूर्ण

अटल पूर्णांक tb_usb3_release_unused_bandwidth(काष्ठा tb_tunnel *tunnel)
अणु
	पूर्णांक ret;

	ret = usb4_usb3_port_release_bandwidth(tunnel->src_port,
					       &tunnel->allocated_up,
					       &tunnel->allocated_करोwn);
	अगर (ret)
		वापस ret;

	tb_tunnel_dbg(tunnel, "decreased bandwidth allocation to %d/%d Mb/s\n",
		      tunnel->allocated_up, tunnel->allocated_करोwn);
	वापस 0;
पूर्ण

अटल व्योम tb_usb3_reclaim_available_bandwidth(काष्ठा tb_tunnel *tunnel,
						पूर्णांक *available_up,
						पूर्णांक *available_करोwn)
अणु
	पूर्णांक ret, max_rate, allocate_up, allocate_करोwn;

	ret = usb4_usb3_port_actual_link_rate(tunnel->src_port);
	अगर (ret < 0) अणु
		tb_tunnel_warn(tunnel, "failed to read actual link rate\n");
		वापस;
	पूर्ण अन्यथा अगर (!ret) अणु
		/* Use maximum link rate अगर the link valid is not set */
		ret = usb4_usb3_port_max_link_rate(tunnel->src_port);
		अगर (ret < 0) अणु
			tb_tunnel_warn(tunnel, "failed to read maximum link rate\n");
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * 90% of the max rate can be allocated क्रम isochronous
	 * transfers.
	 */
	max_rate = ret * 90 / 100;

	/* No need to reclaim अगर alपढ़ोy at maximum */
	अगर (tunnel->allocated_up >= max_rate &&
	    tunnel->allocated_करोwn >= max_rate)
		वापस;

	/* Don't go lower than what is alपढ़ोy allocated */
	allocate_up = min(max_rate, *available_up);
	अगर (allocate_up < tunnel->allocated_up)
		allocate_up = tunnel->allocated_up;

	allocate_करोwn = min(max_rate, *available_करोwn);
	अगर (allocate_करोwn < tunnel->allocated_करोwn)
		allocate_करोwn = tunnel->allocated_करोwn;

	/* If no changes no need to करो more */
	अगर (allocate_up == tunnel->allocated_up &&
	    allocate_करोwn == tunnel->allocated_करोwn)
		वापस;

	ret = usb4_usb3_port_allocate_bandwidth(tunnel->src_port, &allocate_up,
						&allocate_करोwn);
	अगर (ret) अणु
		tb_tunnel_info(tunnel, "failed to allocate bandwidth\n");
		वापस;
	पूर्ण

	tunnel->allocated_up = allocate_up;
	*available_up -= tunnel->allocated_up;

	tunnel->allocated_करोwn = allocate_करोwn;
	*available_करोwn -= tunnel->allocated_करोwn;

	tb_tunnel_dbg(tunnel, "increased bandwidth allocation to %d/%d Mb/s\n",
		      tunnel->allocated_up, tunnel->allocated_करोwn);
पूर्ण

अटल व्योम tb_usb3_init_path(काष्ठा tb_path *path)
अणु
	path->egress_fc_enable = TB_PATH_SOURCE | TB_PATH_INTERNAL;
	path->egress_shared_buffer = TB_PATH_NONE;
	path->ingress_fc_enable = TB_PATH_ALL;
	path->ingress_shared_buffer = TB_PATH_NONE;
	path->priority = 3;
	path->weight = 3;
	path->drop_packages = 0;
	path->nfc_credits = 0;
	path->hops[0].initial_credits = 7;
	अगर (path->path_length > 1)
		path->hops[1].initial_credits =
			tb_initial_credits(path->hops[1].in_port->sw);
पूर्ण

/**
 * tb_tunnel_discover_usb3() - Discover existing USB3 tunnels
 * @tb: Poपूर्णांकer to the करोमुख्य काष्ठाure
 * @करोwn: USB3 करोwnstream adapter
 *
 * If @करोwn adapter is active, follows the tunnel to the USB3 upstream
 * adapter and back. Returns the discovered tunnel or %शून्य अगर there was
 * no tunnel.
 */
काष्ठा tb_tunnel *tb_tunnel_discover_usb3(काष्ठा tb *tb, काष्ठा tb_port *करोwn)
अणु
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_path *path;

	अगर (!tb_usb3_port_is_enabled(करोwn))
		वापस शून्य;

	tunnel = tb_tunnel_alloc(tb, 2, TB_TUNNEL_USB3);
	अगर (!tunnel)
		वापस शून्य;

	tunnel->activate = tb_usb3_activate;
	tunnel->src_port = करोwn;

	/*
	 * Discover both paths even अगर they are not complete. We will
	 * clean them up by calling tb_tunnel_deactivate() below in that
	 * हाल.
	 */
	path = tb_path_discover(करोwn, TB_USB3_HOPID, शून्य, -1,
				&tunnel->dst_port, "USB3 Down");
	अगर (!path) अणु
		/* Just disable the करोwnstream port */
		tb_usb3_port_enable(करोwn, false);
		जाओ err_मुक्त;
	पूर्ण
	tunnel->paths[TB_USB3_PATH_DOWN] = path;
	tb_usb3_init_path(tunnel->paths[TB_USB3_PATH_DOWN]);

	path = tb_path_discover(tunnel->dst_port, -1, करोwn, TB_USB3_HOPID, शून्य,
				"USB3 Up");
	अगर (!path)
		जाओ err_deactivate;
	tunnel->paths[TB_USB3_PATH_UP] = path;
	tb_usb3_init_path(tunnel->paths[TB_USB3_PATH_UP]);

	/* Validate that the tunnel is complete */
	अगर (!tb_port_is_usb3_up(tunnel->dst_port)) अणु
		tb_port_warn(tunnel->dst_port,
			     "path does not end on an USB3 adapter, cleaning up\n");
		जाओ err_deactivate;
	पूर्ण

	अगर (करोwn != tunnel->src_port) अणु
		tb_tunnel_warn(tunnel, "path is not complete, cleaning up\n");
		जाओ err_deactivate;
	पूर्ण

	अगर (!tb_usb3_port_is_enabled(tunnel->dst_port)) अणु
		tb_tunnel_warn(tunnel,
			       "tunnel is not fully activated, cleaning up\n");
		जाओ err_deactivate;
	पूर्ण

	अगर (!tb_route(करोwn->sw)) अणु
		पूर्णांक ret;

		/*
		 * Read the initial bandwidth allocation क्रम the first
		 * hop tunnel.
		 */
		ret = usb4_usb3_port_allocated_bandwidth(करोwn,
			&tunnel->allocated_up, &tunnel->allocated_करोwn);
		अगर (ret)
			जाओ err_deactivate;

		tb_tunnel_dbg(tunnel, "currently allocated bandwidth %d/%d Mb/s\n",
			      tunnel->allocated_up, tunnel->allocated_करोwn);

		tunnel->init = tb_usb3_init;
		tunnel->consumed_bandwidth = tb_usb3_consumed_bandwidth;
		tunnel->release_unused_bandwidth =
			tb_usb3_release_unused_bandwidth;
		tunnel->reclaim_available_bandwidth =
			tb_usb3_reclaim_available_bandwidth;
	पूर्ण

	tb_tunnel_dbg(tunnel, "discovered\n");
	वापस tunnel;

err_deactivate:
	tb_tunnel_deactivate(tunnel);
err_मुक्त:
	tb_tunnel_मुक्त(tunnel);

	वापस शून्य;
पूर्ण

/**
 * tb_tunnel_alloc_usb3() - allocate a USB3 tunnel
 * @tb: Poपूर्णांकer to the करोमुख्य काष्ठाure
 * @up: USB3 upstream adapter port
 * @करोwn: USB3 करोwnstream adapter port
 * @max_up: Maximum available upstream bandwidth क्रम the USB3 tunnel (%0
 *	    अगर not limited).
 * @max_करोwn: Maximum available करोwnstream bandwidth क्रम the USB3 tunnel
 *	      (%0 अगर not limited).
 *
 * Allocate an USB3 tunnel. The ports must be of type @TB_TYPE_USB3_UP and
 * @TB_TYPE_USB3_DOWN.
 *
 * Return: Returns a tb_tunnel on success or %शून्य on failure.
 */
काष्ठा tb_tunnel *tb_tunnel_alloc_usb3(काष्ठा tb *tb, काष्ठा tb_port *up,
				       काष्ठा tb_port *करोwn, पूर्णांक max_up,
				       पूर्णांक max_करोwn)
अणु
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_path *path;
	पूर्णांक max_rate = 0;

	/*
	 * Check that we have enough bandwidth available क्रम the new
	 * USB3 tunnel.
	 */
	अगर (max_up > 0 || max_करोwn > 0) अणु
		max_rate = tb_usb3_max_link_rate(करोwn, up);
		अगर (max_rate < 0)
			वापस शून्य;

		/* Only 90% can be allocated क्रम USB3 isochronous transfers */
		max_rate = max_rate * 90 / 100;
		tb_port_dbg(up, "required bandwidth for USB3 tunnel %d Mb/s\n",
			    max_rate);

		अगर (max_rate > max_up || max_rate > max_करोwn) अणु
			tb_port_warn(up, "not enough bandwidth for USB3 tunnel\n");
			वापस शून्य;
		पूर्ण
	पूर्ण

	tunnel = tb_tunnel_alloc(tb, 2, TB_TUNNEL_USB3);
	अगर (!tunnel)
		वापस शून्य;

	tunnel->activate = tb_usb3_activate;
	tunnel->src_port = करोwn;
	tunnel->dst_port = up;
	tunnel->max_up = max_up;
	tunnel->max_करोwn = max_करोwn;

	path = tb_path_alloc(tb, करोwn, TB_USB3_HOPID, up, TB_USB3_HOPID, 0,
			     "USB3 Down");
	अगर (!path) अणु
		tb_tunnel_मुक्त(tunnel);
		वापस शून्य;
	पूर्ण
	tb_usb3_init_path(path);
	tunnel->paths[TB_USB3_PATH_DOWN] = path;

	path = tb_path_alloc(tb, up, TB_USB3_HOPID, करोwn, TB_USB3_HOPID, 0,
			     "USB3 Up");
	अगर (!path) अणु
		tb_tunnel_मुक्त(tunnel);
		वापस शून्य;
	पूर्ण
	tb_usb3_init_path(path);
	tunnel->paths[TB_USB3_PATH_UP] = path;

	अगर (!tb_route(करोwn->sw)) अणु
		tunnel->allocated_up = max_rate;
		tunnel->allocated_करोwn = max_rate;

		tunnel->init = tb_usb3_init;
		tunnel->consumed_bandwidth = tb_usb3_consumed_bandwidth;
		tunnel->release_unused_bandwidth =
			tb_usb3_release_unused_bandwidth;
		tunnel->reclaim_available_bandwidth =
			tb_usb3_reclaim_available_bandwidth;
	पूर्ण

	वापस tunnel;
पूर्ण

/**
 * tb_tunnel_मुक्त() - मुक्त a tunnel
 * @tunnel: Tunnel to be मुक्तd
 *
 * Frees a tunnel. The tunnel करोes not need to be deactivated.
 */
व्योम tb_tunnel_मुक्त(काष्ठा tb_tunnel *tunnel)
अणु
	पूर्णांक i;

	अगर (!tunnel)
		वापस;

	क्रम (i = 0; i < tunnel->npaths; i++) अणु
		अगर (tunnel->paths[i])
			tb_path_मुक्त(tunnel->paths[i]);
	पूर्ण

	kमुक्त(tunnel->paths);
	kमुक्त(tunnel);
पूर्ण

/**
 * tb_tunnel_is_invalid - check whether an activated path is still valid
 * @tunnel: Tunnel to check
 */
bool tb_tunnel_is_invalid(काष्ठा tb_tunnel *tunnel)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tunnel->npaths; i++) अणु
		WARN_ON(!tunnel->paths[i]->activated);
		अगर (tb_path_is_invalid(tunnel->paths[i]))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * tb_tunnel_restart() - activate a tunnel after a hardware reset
 * @tunnel: Tunnel to restart
 *
 * Return: 0 on success and negative त्रुटि_सं in हाल अगर failure
 */
पूर्णांक tb_tunnel_restart(काष्ठा tb_tunnel *tunnel)
अणु
	पूर्णांक res, i;

	tb_tunnel_dbg(tunnel, "activating\n");

	/*
	 * Make sure all paths are properly disabled beक्रमe enabling
	 * them again.
	 */
	क्रम (i = 0; i < tunnel->npaths; i++) अणु
		अगर (tunnel->paths[i]->activated) अणु
			tb_path_deactivate(tunnel->paths[i]);
			tunnel->paths[i]->activated = false;
		पूर्ण
	पूर्ण

	अगर (tunnel->init) अणु
		res = tunnel->init(tunnel);
		अगर (res)
			वापस res;
	पूर्ण

	क्रम (i = 0; i < tunnel->npaths; i++) अणु
		res = tb_path_activate(tunnel->paths[i]);
		अगर (res)
			जाओ err;
	पूर्ण

	अगर (tunnel->activate) अणु
		res = tunnel->activate(tunnel, true);
		अगर (res)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	tb_tunnel_warn(tunnel, "activation failed\n");
	tb_tunnel_deactivate(tunnel);
	वापस res;
पूर्ण

/**
 * tb_tunnel_activate() - activate a tunnel
 * @tunnel: Tunnel to activate
 *
 * Return: Returns 0 on success or an error code on failure.
 */
पूर्णांक tb_tunnel_activate(काष्ठा tb_tunnel *tunnel)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tunnel->npaths; i++) अणु
		अगर (tunnel->paths[i]->activated) अणु
			tb_tunnel_WARN(tunnel,
				       "trying to activate an already activated tunnel\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस tb_tunnel_restart(tunnel);
पूर्ण

/**
 * tb_tunnel_deactivate() - deactivate a tunnel
 * @tunnel: Tunnel to deactivate
 */
व्योम tb_tunnel_deactivate(काष्ठा tb_tunnel *tunnel)
अणु
	पूर्णांक i;

	tb_tunnel_dbg(tunnel, "deactivating\n");

	अगर (tunnel->activate)
		tunnel->activate(tunnel, false);

	क्रम (i = 0; i < tunnel->npaths; i++) अणु
		अगर (tunnel->paths[i] && tunnel->paths[i]->activated)
			tb_path_deactivate(tunnel->paths[i]);
	पूर्ण
पूर्ण

/**
 * tb_tunnel_port_on_path() - Does the tunnel go through port
 * @tunnel: Tunnel to check
 * @port: Port to check
 *
 * Returns true अगर @tunnel goes through @port (direction करोes not matter),
 * false otherwise.
 */
bool tb_tunnel_port_on_path(स्थिर काष्ठा tb_tunnel *tunnel,
			    स्थिर काष्ठा tb_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tunnel->npaths; i++) अणु
		अगर (!tunnel->paths[i])
			जारी;

		अगर (tb_path_port_on_path(tunnel->paths[i], port))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool tb_tunnel_is_active(स्थिर काष्ठा tb_tunnel *tunnel)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tunnel->npaths; i++) अणु
		अगर (!tunnel->paths[i])
			वापस false;
		अगर (!tunnel->paths[i]->activated)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * tb_tunnel_consumed_bandwidth() - Return bandwidth consumed by the tunnel
 * @tunnel: Tunnel to check
 * @consumed_up: Consumed bandwidth in Mb/s from @dst_port to @src_port.
 *		 Can be %शून्य.
 * @consumed_करोwn: Consumed bandwidth in Mb/s from @src_port to @dst_port.
 *		   Can be %शून्य.
 *
 * Stores the amount of isochronous bandwidth @tunnel consumes in
 * @consumed_up and @consumed_करोwn. In हाल of success वापसs %0,
 * negative त्रुटि_सं otherwise.
 */
पूर्णांक tb_tunnel_consumed_bandwidth(काष्ठा tb_tunnel *tunnel, पूर्णांक *consumed_up,
				 पूर्णांक *consumed_करोwn)
अणु
	पूर्णांक up_bw = 0, करोwn_bw = 0;

	अगर (!tb_tunnel_is_active(tunnel))
		जाओ out;

	अगर (tunnel->consumed_bandwidth) अणु
		पूर्णांक ret;

		ret = tunnel->consumed_bandwidth(tunnel, &up_bw, &करोwn_bw);
		अगर (ret)
			वापस ret;

		tb_tunnel_dbg(tunnel, "consumed bandwidth %d/%d Mb/s\n", up_bw,
			      करोwn_bw);
	पूर्ण

out:
	अगर (consumed_up)
		*consumed_up = up_bw;
	अगर (consumed_करोwn)
		*consumed_करोwn = करोwn_bw;

	वापस 0;
पूर्ण

/**
 * tb_tunnel_release_unused_bandwidth() - Release unused bandwidth
 * @tunnel: Tunnel whose unused bandwidth to release
 *
 * If tunnel supports dynamic bandwidth management (USB3 tunnels at the
 * moment) this function makes it to release all the unused bandwidth.
 *
 * Returns %0 in हाल of success and negative त्रुटि_सं otherwise.
 */
पूर्णांक tb_tunnel_release_unused_bandwidth(काष्ठा tb_tunnel *tunnel)
अणु
	अगर (!tb_tunnel_is_active(tunnel))
		वापस 0;

	अगर (tunnel->release_unused_bandwidth) अणु
		पूर्णांक ret;

		ret = tunnel->release_unused_bandwidth(tunnel);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tb_tunnel_reclaim_available_bandwidth() - Reclaim available bandwidth
 * @tunnel: Tunnel reclaiming available bandwidth
 * @available_up: Available upstream bandwidth (in Mb/s)
 * @available_करोwn: Available करोwnstream bandwidth (in Mb/s)
 *
 * Reclaims bandwidth from @available_up and @available_करोwn and updates
 * the variables accordingly (e.g decreases both according to what was
 * reclaimed by the tunnel). If nothing was reclaimed the values are
 * kept as is.
 */
व्योम tb_tunnel_reclaim_available_bandwidth(काष्ठा tb_tunnel *tunnel,
					   पूर्णांक *available_up,
					   पूर्णांक *available_करोwn)
अणु
	अगर (!tb_tunnel_is_active(tunnel))
		वापस;

	अगर (tunnel->reclaim_available_bandwidth)
		tunnel->reclaim_available_bandwidth(tunnel, available_up,
						    available_करोwn);
पूर्ण
