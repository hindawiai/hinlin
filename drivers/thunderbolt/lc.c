<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt link controller support
 *
 * Copyright (C) 2019, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश "tb.h"

/**
 * tb_lc_पढ़ो_uuid() - Read चयन UUID from link controller common रेजिस्टर
 * @sw: Switch whose UUID is पढ़ो
 * @uuid: UUID is placed here
 */
पूर्णांक tb_lc_पढ़ो_uuid(काष्ठा tb_चयन *sw, u32 *uuid)
अणु
	अगर (!sw->cap_lc)
		वापस -EINVAL;
	वापस tb_sw_पढ़ो(sw, uuid, TB_CFG_SWITCH, sw->cap_lc + TB_LC_FUSE, 4);
पूर्ण

अटल पूर्णांक पढ़ो_lc_desc(काष्ठा tb_चयन *sw, u32 *desc)
अणु
	अगर (!sw->cap_lc)
		वापस -EINVAL;
	वापस tb_sw_पढ़ो(sw, desc, TB_CFG_SWITCH, sw->cap_lc + TB_LC_DESC, 1);
पूर्ण

अटल पूर्णांक find_port_lc_cap(काष्ठा tb_port *port)
अणु
	काष्ठा tb_चयन *sw = port->sw;
	पूर्णांक start, phys, ret, size;
	u32 desc;

	ret = पढ़ो_lc_desc(sw, &desc);
	अगर (ret)
		वापस ret;

	/* Start of port LC रेजिस्टरs */
	start = (desc & TB_LC_DESC_SIZE_MASK) >> TB_LC_DESC_SIZE_SHIFT;
	size = (desc & TB_LC_DESC_PORT_SIZE_MASK) >> TB_LC_DESC_PORT_SIZE_SHIFT;
	phys = tb_phy_port_from_link(port->port);

	वापस sw->cap_lc + start + phys * size;
पूर्ण

अटल पूर्णांक tb_lc_set_port_configured(काष्ठा tb_port *port, bool configured)
अणु
	bool upstream = tb_is_upstream_port(port);
	काष्ठा tb_चयन *sw = port->sw;
	u32 ctrl, lane;
	पूर्णांक cap, ret;

	अगर (sw->generation < 2)
		वापस 0;

	cap = find_port_lc_cap(port);
	अगर (cap < 0)
		वापस cap;

	ret = tb_sw_पढ़ो(sw, &ctrl, TB_CFG_SWITCH, cap + TB_LC_SX_CTRL, 1);
	अगर (ret)
		वापस ret;

	/* Resolve correct lane */
	अगर (port->port % 2)
		lane = TB_LC_SX_CTRL_L1C;
	अन्यथा
		lane = TB_LC_SX_CTRL_L2C;

	अगर (configured) अणु
		ctrl |= lane;
		अगर (upstream)
			ctrl |= TB_LC_SX_CTRL_UPSTREAM;
	पूर्ण अन्यथा अणु
		ctrl &= ~lane;
		अगर (upstream)
			ctrl &= ~TB_LC_SX_CTRL_UPSTREAM;
	पूर्ण

	वापस tb_sw_ग_लिखो(sw, &ctrl, TB_CFG_SWITCH, cap + TB_LC_SX_CTRL, 1);
पूर्ण

/**
 * tb_lc_configure_port() - Let LC know about configured port
 * @port: Port that is set as configured
 *
 * Sets the port configured क्रम घातer management purposes.
 */
पूर्णांक tb_lc_configure_port(काष्ठा tb_port *port)
अणु
	वापस tb_lc_set_port_configured(port, true);
पूर्ण

/**
 * tb_lc_unconfigure_port() - Let LC know about unconfigured port
 * @port: Port that is set as configured
 *
 * Sets the port unconfigured क्रम घातer management purposes.
 */
व्योम tb_lc_unconfigure_port(काष्ठा tb_port *port)
अणु
	tb_lc_set_port_configured(port, false);
पूर्ण

अटल पूर्णांक tb_lc_set_xकरोमुख्य_configured(काष्ठा tb_port *port, bool configure)
अणु
	काष्ठा tb_चयन *sw = port->sw;
	u32 ctrl, lane;
	पूर्णांक cap, ret;

	अगर (sw->generation < 2)
		वापस 0;

	cap = find_port_lc_cap(port);
	अगर (cap < 0)
		वापस cap;

	ret = tb_sw_पढ़ो(sw, &ctrl, TB_CFG_SWITCH, cap + TB_LC_SX_CTRL, 1);
	अगर (ret)
		वापस ret;

	/* Resolve correct lane */
	अगर (port->port % 2)
		lane = TB_LC_SX_CTRL_L1D;
	अन्यथा
		lane = TB_LC_SX_CTRL_L2D;

	अगर (configure)
		ctrl |= lane;
	अन्यथा
		ctrl &= ~lane;

	वापस tb_sw_ग_लिखो(sw, &ctrl, TB_CFG_SWITCH, cap + TB_LC_SX_CTRL, 1);
पूर्ण

/**
 * tb_lc_configure_xकरोमुख्य() - Inक्रमm LC that the link is XDoमुख्य
 * @port: Switch करोwnstream port connected to another host
 *
 * Sets the lane configured क्रम XDoमुख्य accordingly so that the LC knows
 * about this. Returns %0 in success and negative त्रुटि_सं in failure.
 */
पूर्णांक tb_lc_configure_xकरोमुख्य(काष्ठा tb_port *port)
अणु
	वापस tb_lc_set_xकरोमुख्य_configured(port, true);
पूर्ण

/**
 * tb_lc_unconfigure_xकरोमुख्य() - Unconfigure XDoमुख्य from port
 * @port: Switch करोwnstream port that was connected to another host
 *
 * Unsets the lane XDoमुख्य configuration.
 */
व्योम tb_lc_unconfigure_xकरोमुख्य(काष्ठा tb_port *port)
अणु
	tb_lc_set_xकरोमुख्य_configured(port, false);
पूर्ण

/**
 * tb_lc_start_lane_initialization() - Start lane initialization
 * @port: Device router lane 0 adapter
 *
 * Starts lane initialization क्रम @port after the router resumed from
 * sleep. Should be called क्रम those करोwnstream lane adapters that were
 * not connected (tb_lc_configure_port() was not called) beक्रमe sleep.
 *
 * Returns %0 in success and negative त्रुटि_सं in हाल of failure.
 */
पूर्णांक tb_lc_start_lane_initialization(काष्ठा tb_port *port)
अणु
	काष्ठा tb_चयन *sw = port->sw;
	पूर्णांक ret, cap;
	u32 ctrl;

	अगर (!tb_route(sw))
		वापस 0;

	अगर (sw->generation < 2)
		वापस 0;

	cap = find_port_lc_cap(port);
	अगर (cap < 0)
		वापस cap;

	ret = tb_sw_पढ़ो(sw, &ctrl, TB_CFG_SWITCH, cap + TB_LC_SX_CTRL, 1);
	अगर (ret)
		वापस ret;

	ctrl |= TB_LC_SX_CTRL_SLI;

	वापस tb_sw_ग_लिखो(sw, &ctrl, TB_CFG_SWITCH, cap + TB_LC_SX_CTRL, 1);
पूर्ण

अटल पूर्णांक tb_lc_set_wake_one(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक offset,
			      अचिन्हित पूर्णांक flags)
अणु
	u32 ctrl;
	पूर्णांक ret;

	/*
	 * Enable wake on PCIe and USB4 (wake coming from another
	 * router).
	 */
	ret = tb_sw_पढ़ो(sw, &ctrl, TB_CFG_SWITCH,
			 offset + TB_LC_SX_CTRL, 1);
	अगर (ret)
		वापस ret;

	ctrl &= ~(TB_LC_SX_CTRL_WOC | TB_LC_SX_CTRL_WOD | TB_LC_SX_CTRL_WOP |
		  TB_LC_SX_CTRL_WOU4);

	अगर (flags & TB_WAKE_ON_CONNECT)
		ctrl |= TB_LC_SX_CTRL_WOC | TB_LC_SX_CTRL_WOD;
	अगर (flags & TB_WAKE_ON_USB4)
		ctrl |= TB_LC_SX_CTRL_WOU4;
	अगर (flags & TB_WAKE_ON_PCIE)
		ctrl |= TB_LC_SX_CTRL_WOP;

	वापस tb_sw_ग_लिखो(sw, &ctrl, TB_CFG_SWITCH, offset + TB_LC_SX_CTRL, 1);
पूर्ण

/**
 * tb_lc_set_wake() - Enable/disable wake
 * @sw: Switch whose wakes to configure
 * @flags: Wakeup flags (%0 to disable)
 *
 * For each LC sets wake bits accordingly.
 */
पूर्णांक tb_lc_set_wake(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक start, size, nlc, ret, i;
	u32 desc;

	अगर (sw->generation < 2)
		वापस 0;

	अगर (!tb_route(sw))
		वापस 0;

	ret = पढ़ो_lc_desc(sw, &desc);
	अगर (ret)
		वापस ret;

	/* Figure out number of link controllers */
	nlc = desc & TB_LC_DESC_NLC_MASK;
	start = (desc & TB_LC_DESC_SIZE_MASK) >> TB_LC_DESC_SIZE_SHIFT;
	size = (desc & TB_LC_DESC_PORT_SIZE_MASK) >> TB_LC_DESC_PORT_SIZE_SHIFT;

	/* For each link controller set sleep bit */
	क्रम (i = 0; i < nlc; i++) अणु
		अचिन्हित पूर्णांक offset = sw->cap_lc + start + i * size;

		ret = tb_lc_set_wake_one(sw, offset, flags);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tb_lc_set_sleep() - Inक्रमm LC that the चयन is going to sleep
 * @sw: Switch to set sleep
 *
 * Let the चयन link controllers know that the चयन is going to
 * sleep.
 */
पूर्णांक tb_lc_set_sleep(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक start, size, nlc, ret, i;
	u32 desc;

	अगर (sw->generation < 2)
		वापस 0;

	ret = पढ़ो_lc_desc(sw, &desc);
	अगर (ret)
		वापस ret;

	/* Figure out number of link controllers */
	nlc = desc & TB_LC_DESC_NLC_MASK;
	start = (desc & TB_LC_DESC_SIZE_MASK) >> TB_LC_DESC_SIZE_SHIFT;
	size = (desc & TB_LC_DESC_PORT_SIZE_MASK) >> TB_LC_DESC_PORT_SIZE_SHIFT;

	/* For each link controller set sleep bit */
	क्रम (i = 0; i < nlc; i++) अणु
		अचिन्हित पूर्णांक offset = sw->cap_lc + start + i * size;
		u32 ctrl;

		ret = tb_sw_पढ़ो(sw, &ctrl, TB_CFG_SWITCH,
				 offset + TB_LC_SX_CTRL, 1);
		अगर (ret)
			वापस ret;

		ctrl |= TB_LC_SX_CTRL_SLP;
		ret = tb_sw_ग_लिखो(sw, &ctrl, TB_CFG_SWITCH,
				  offset + TB_LC_SX_CTRL, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tb_lc_lane_bonding_possible() - Is lane bonding possible towards चयन
 * @sw: Switch to check
 *
 * Checks whether conditions क्रम lane bonding from parent to @sw are
 * possible.
 */
bool tb_lc_lane_bonding_possible(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *up;
	पूर्णांक cap, ret;
	u32 val;

	अगर (sw->generation < 2)
		वापस false;

	up = tb_upstream_port(sw);
	cap = find_port_lc_cap(up);
	अगर (cap < 0)
		वापस false;

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH, cap + TB_LC_PORT_ATTR, 1);
	अगर (ret)
		वापस false;

	वापस !!(val & TB_LC_PORT_ATTR_BE);
पूर्ण

अटल पूर्णांक tb_lc_dp_sink_from_port(स्थिर काष्ठा tb_चयन *sw,
				   काष्ठा tb_port *in)
अणु
	काष्ठा tb_port *port;

	/* The first DP IN port is sink 0 and second is sink 1 */
	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (tb_port_is_dpin(port))
			वापस in != port;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tb_lc_dp_sink_available(काष्ठा tb_चयन *sw, पूर्णांक sink)
अणु
	u32 val, alloc;
	पूर्णांक ret;

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH,
			 sw->cap_lc + TB_LC_SNK_ALLOCATION, 1);
	अगर (ret)
		वापस ret;

	/*
	 * Sink is available क्रम CM/SW to use अगर the allocation valie is
	 * either 0 or 1.
	 */
	अगर (!sink) अणु
		alloc = val & TB_LC_SNK_ALLOCATION_SNK0_MASK;
		अगर (!alloc || alloc == TB_LC_SNK_ALLOCATION_SNK0_CM)
			वापस 0;
	पूर्ण अन्यथा अणु
		alloc = (val & TB_LC_SNK_ALLOCATION_SNK1_MASK) >>
			TB_LC_SNK_ALLOCATION_SNK1_SHIFT;
		अगर (!alloc || alloc == TB_LC_SNK_ALLOCATION_SNK1_CM)
			वापस 0;
	पूर्ण

	वापस -EBUSY;
पूर्ण

/**
 * tb_lc_dp_sink_query() - Is DP sink available क्रम DP IN port
 * @sw: Switch whose DP sink is queried
 * @in: DP IN port to check
 *
 * Queries through LC SNK_ALLOCATION रेजिस्टरs whether DP sink is available
 * क्रम the given DP IN port or not.
 */
bool tb_lc_dp_sink_query(काष्ठा tb_चयन *sw, काष्ठा tb_port *in)
अणु
	पूर्णांक sink;

	/*
	 * For older generations sink is always available as there is no
	 * allocation mechanism.
	 */
	अगर (sw->generation < 3)
		वापस true;

	sink = tb_lc_dp_sink_from_port(sw, in);
	अगर (sink < 0)
		वापस false;

	वापस !tb_lc_dp_sink_available(sw, sink);
पूर्ण

/**
 * tb_lc_dp_sink_alloc() - Allocate DP sink
 * @sw: Switch whose DP sink is allocated
 * @in: DP IN port the DP sink is allocated क्रम
 *
 * Allocate DP sink क्रम @in via LC SNK_ALLOCATION रेजिस्टरs. If the
 * resource is available and allocation is successful वापसs %0. In all
 * other हालs returs negative त्रुटि_सं. In particular %-EBUSY is वापसed अगर
 * the resource was not available.
 */
पूर्णांक tb_lc_dp_sink_alloc(काष्ठा tb_चयन *sw, काष्ठा tb_port *in)
अणु
	पूर्णांक ret, sink;
	u32 val;

	अगर (sw->generation < 3)
		वापस 0;

	sink = tb_lc_dp_sink_from_port(sw, in);
	अगर (sink < 0)
		वापस sink;

	ret = tb_lc_dp_sink_available(sw, sink);
	अगर (ret)
		वापस ret;

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH,
			 sw->cap_lc + TB_LC_SNK_ALLOCATION, 1);
	अगर (ret)
		वापस ret;

	अगर (!sink) अणु
		val &= ~TB_LC_SNK_ALLOCATION_SNK0_MASK;
		val |= TB_LC_SNK_ALLOCATION_SNK0_CM;
	पूर्ण अन्यथा अणु
		val &= ~TB_LC_SNK_ALLOCATION_SNK1_MASK;
		val |= TB_LC_SNK_ALLOCATION_SNK1_CM <<
			TB_LC_SNK_ALLOCATION_SNK1_SHIFT;
	पूर्ण

	ret = tb_sw_ग_लिखो(sw, &val, TB_CFG_SWITCH,
			  sw->cap_lc + TB_LC_SNK_ALLOCATION, 1);

	अगर (ret)
		वापस ret;

	tb_port_dbg(in, "sink %d allocated\n", sink);
	वापस 0;
पूर्ण

/**
 * tb_lc_dp_sink_dealloc() - De-allocate DP sink
 * @sw: Switch whose DP sink is de-allocated
 * @in: DP IN port whose DP sink is de-allocated
 *
 * De-allocate DP sink from @in using LC SNK_ALLOCATION रेजिस्टरs.
 */
पूर्णांक tb_lc_dp_sink_dealloc(काष्ठा tb_चयन *sw, काष्ठा tb_port *in)
अणु
	पूर्णांक ret, sink;
	u32 val;

	अगर (sw->generation < 3)
		वापस 0;

	sink = tb_lc_dp_sink_from_port(sw, in);
	अगर (sink < 0)
		वापस sink;

	/* Needs to be owned by CM/SW */
	ret = tb_lc_dp_sink_available(sw, sink);
	अगर (ret)
		वापस ret;

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH,
			 sw->cap_lc + TB_LC_SNK_ALLOCATION, 1);
	अगर (ret)
		वापस ret;

	अगर (!sink)
		val &= ~TB_LC_SNK_ALLOCATION_SNK0_MASK;
	अन्यथा
		val &= ~TB_LC_SNK_ALLOCATION_SNK1_MASK;

	ret = tb_sw_ग_लिखो(sw, &val, TB_CFG_SWITCH,
			  sw->cap_lc + TB_LC_SNK_ALLOCATION, 1);
	अगर (ret)
		वापस ret;

	tb_port_dbg(in, "sink %d de-allocated\n", sink);
	वापस 0;
पूर्ण

/**
 * tb_lc_क्रमce_घातer() - Forces LC to be घातered on
 * @sw: Thunderbolt चयन
 *
 * This is useful to let authentication cycle pass even without
 * a Thunderbolt link present.
 */
पूर्णांक tb_lc_क्रमce_घातer(काष्ठा tb_चयन *sw)
अणु
	u32 in = 0xffff;

	वापस tb_sw_ग_लिखो(sw, &in, TB_CFG_SWITCH, TB_LC_POWER, 1);
पूर्ण
