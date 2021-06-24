<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt Time Management Unit (TMU) support
 *
 * Copyright (C) 2019, Intel Corporation
 * Authors: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 *	    Rajmohan Mani <rajmohan.mani@पूर्णांकel.com>
 */

#समावेश <linux/delay.h>

#समावेश "tb.h"

अटल स्थिर अक्षर *tb_चयन_पंचांगu_mode_name(स्थिर काष्ठा tb_चयन *sw)
अणु
	bool root_चयन = !tb_route(sw);

	चयन (sw->पंचांगu.rate) अणु
	हाल TB_SWITCH_TMU_RATE_OFF:
		वापस "off";

	हाल TB_SWITCH_TMU_RATE_HIFI:
		/* Root चयन करोes not have upstream directionality */
		अगर (root_चयन)
			वापस "HiFi";
		अगर (sw->पंचांगu.unidirectional)
			वापस "uni-directional, HiFi";
		वापस "bi-directional, HiFi";

	हाल TB_SWITCH_TMU_RATE_NORMAL:
		अगर (root_चयन)
			वापस "normal";
		वापस "uni-directional, normal";

	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल bool tb_चयन_पंचांगu_ucap_supported(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक ret;
	u32 val;

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH,
			 sw->पंचांगu.cap + TMU_RTR_CS_0, 1);
	अगर (ret)
		वापस false;

	वापस !!(val & TMU_RTR_CS_0_UCAP);
पूर्ण

अटल पूर्णांक tb_चयन_पंचांगu_rate_पढ़ो(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक ret;
	u32 val;

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH,
			 sw->पंचांगu.cap + TMU_RTR_CS_3, 1);
	अगर (ret)
		वापस ret;

	val >>= TMU_RTR_CS_3_TS_PACKET_INTERVAL_SHIFT;
	वापस val;
पूर्ण

अटल पूर्णांक tb_चयन_पंचांगu_rate_ग_लिखो(काष्ठा tb_चयन *sw, पूर्णांक rate)
अणु
	पूर्णांक ret;
	u32 val;

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH,
			 sw->पंचांगu.cap + TMU_RTR_CS_3, 1);
	अगर (ret)
		वापस ret;

	val &= ~TMU_RTR_CS_3_TS_PACKET_INTERVAL_MASK;
	val |= rate << TMU_RTR_CS_3_TS_PACKET_INTERVAL_SHIFT;

	वापस tb_sw_ग_लिखो(sw, &val, TB_CFG_SWITCH,
			   sw->पंचांगu.cap + TMU_RTR_CS_3, 1);
पूर्ण

अटल पूर्णांक tb_port_पंचांगu_ग_लिखो(काष्ठा tb_port *port, u8 offset, u32 mask,
			     u32 value)
अणु
	u32 data;
	पूर्णांक ret;

	ret = tb_port_पढ़ो(port, &data, TB_CFG_PORT, port->cap_पंचांगu + offset, 1);
	अगर (ret)
		वापस ret;

	data &= ~mask;
	data |= value;

	वापस tb_port_ग_लिखो(port, &data, TB_CFG_PORT,
			     port->cap_पंचांगu + offset, 1);
पूर्ण

अटल पूर्णांक tb_port_पंचांगu_set_unidirectional(काष्ठा tb_port *port,
					  bool unidirectional)
अणु
	u32 val;

	अगर (!port->sw->पंचांगu.has_ucap)
		वापस 0;

	val = unidirectional ? TMU_ADP_CS_3_UDM : 0;
	वापस tb_port_पंचांगu_ग_लिखो(port, TMU_ADP_CS_3, TMU_ADP_CS_3_UDM, val);
पूर्ण

अटल अंतरभूत पूर्णांक tb_port_पंचांगu_unidirectional_disable(काष्ठा tb_port *port)
अणु
	वापस tb_port_पंचांगu_set_unidirectional(port, false);
पूर्ण

अटल bool tb_port_पंचांगu_is_unidirectional(काष्ठा tb_port *port)
अणु
	पूर्णांक ret;
	u32 val;

	ret = tb_port_पढ़ो(port, &val, TB_CFG_PORT,
			   port->cap_पंचांगu + TMU_ADP_CS_3, 1);
	अगर (ret)
		वापस false;

	वापस val & TMU_ADP_CS_3_UDM;
पूर्ण

अटल पूर्णांक tb_चयन_पंचांगu_set_समय_disruption(काष्ठा tb_चयन *sw, bool set)
अणु
	पूर्णांक ret;
	u32 val;

	ret = tb_sw_पढ़ो(sw, &val, TB_CFG_SWITCH,
			 sw->पंचांगu.cap + TMU_RTR_CS_0, 1);
	अगर (ret)
		वापस ret;

	अगर (set)
		val |= TMU_RTR_CS_0_TD;
	अन्यथा
		val &= ~TMU_RTR_CS_0_TD;

	वापस tb_sw_ग_लिखो(sw, &val, TB_CFG_SWITCH,
			   sw->पंचांगu.cap + TMU_RTR_CS_0, 1);
पूर्ण

/**
 * tb_चयन_पंचांगu_init() - Initialize चयन TMU काष्ठाures
 * @sw: Switch to initialized
 *
 * This function must be called beक्रमe other TMU related functions to
 * makes the पूर्णांकernal काष्ठाures are filled in correctly. Does not
 * change any hardware configuration.
 */
पूर्णांक tb_चयन_पंचांगu_init(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;
	पूर्णांक ret;

	अगर (tb_चयन_is_icm(sw))
		वापस 0;

	ret = tb_चयन_find_cap(sw, TB_SWITCH_CAP_TMU);
	अगर (ret > 0)
		sw->पंचांगu.cap = ret;

	tb_चयन_क्रम_each_port(sw, port) अणु
		पूर्णांक cap;

		cap = tb_port_find_cap(port, TB_PORT_CAP_TIME1);
		अगर (cap > 0)
			port->cap_पंचांगu = cap;
	पूर्ण

	ret = tb_चयन_पंचांगu_rate_पढ़ो(sw);
	अगर (ret < 0)
		वापस ret;

	sw->पंचांगu.rate = ret;

	sw->पंचांगu.has_ucap = tb_चयन_पंचांगu_ucap_supported(sw);
	अगर (sw->पंचांगu.has_ucap) अणु
		tb_sw_dbg(sw, "TMU: supports uni-directional mode\n");

		अगर (tb_route(sw)) अणु
			काष्ठा tb_port *up = tb_upstream_port(sw);

			sw->पंचांगu.unidirectional =
				tb_port_पंचांगu_is_unidirectional(up);
		पूर्ण
	पूर्ण अन्यथा अणु
		sw->पंचांगu.unidirectional = false;
	पूर्ण

	tb_sw_dbg(sw, "TMU: current mode: %s\n", tb_चयन_पंचांगu_mode_name(sw));
	वापस 0;
पूर्ण

/**
 * tb_चयन_पंचांगu_post_समय() - Update चयन local समय
 * @sw: Switch whose समय to update
 *
 * Updates चयन local समय using समय posting procedure.
 */
पूर्णांक tb_चयन_पंचांगu_post_समय(काष्ठा tb_चयन *sw)
अणु
	अचिन्हित पूर्णांक  post_local_समय_offset, post_समय_offset;
	काष्ठा tb_चयन *root_चयन = sw->tb->root_चयन;
	u64 hi, mid, lo, local_समय, post_समय;
	पूर्णांक i, ret, retries = 100;
	u32 gm_local_समय[3];

	अगर (!tb_route(sw))
		वापस 0;

	अगर (!tb_चयन_is_usb4(sw))
		वापस 0;

	/* Need to be able to पढ़ो the gअक्रम master समय */
	अगर (!root_चयन->पंचांगu.cap)
		वापस 0;

	ret = tb_sw_पढ़ो(root_चयन, gm_local_समय, TB_CFG_SWITCH,
			 root_चयन->पंचांगu.cap + TMU_RTR_CS_1,
			 ARRAY_SIZE(gm_local_समय));
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(gm_local_समय); i++)
		tb_sw_dbg(root_चयन, "local_time[%d]=0x%08x\n", i,
			  gm_local_समय[i]);

	/* Convert to nanoseconds (drop fractional part) */
	hi = gm_local_समय[2] & TMU_RTR_CS_3_LOCAL_TIME_NS_MASK;
	mid = gm_local_समय[1];
	lo = (gm_local_समय[0] & TMU_RTR_CS_1_LOCAL_TIME_NS_MASK) >>
		TMU_RTR_CS_1_LOCAL_TIME_NS_SHIFT;
	local_समय = hi << 48 | mid << 16 | lo;

	/* Tell the चयन that समय sync is disrupted क्रम a जबतक */
	ret = tb_चयन_पंचांगu_set_समय_disruption(sw, true);
	अगर (ret)
		वापस ret;

	post_local_समय_offset = sw->पंचांगu.cap + TMU_RTR_CS_22;
	post_समय_offset = sw->पंचांगu.cap + TMU_RTR_CS_24;

	/*
	 * Write the Gअक्रमmaster समय to the Post Local Time रेजिस्टरs
	 * of the new चयन.
	 */
	ret = tb_sw_ग_लिखो(sw, &local_समय, TB_CFG_SWITCH,
			  post_local_समय_offset, 2);
	अगर (ret)
		जाओ out;

	/*
	 * Have the new चयन update its local समय (by writing 1 to
	 * the post_समय रेजिस्टरs) and रुको क्रम the completion of the
	 * same (post_समय रेजिस्टर becomes 0). This means the समय has
	 * been converged properly.
	 */
	post_समय = 1;

	ret = tb_sw_ग_लिखो(sw, &post_समय, TB_CFG_SWITCH, post_समय_offset, 2);
	अगर (ret)
		जाओ out;

	करो अणु
		usleep_range(5, 10);
		ret = tb_sw_पढ़ो(sw, &post_समय, TB_CFG_SWITCH,
				 post_समय_offset, 2);
		अगर (ret)
			जाओ out;
	पूर्ण जबतक (--retries && post_समय);

	अगर (!retries) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	tb_sw_dbg(sw, "TMU: updated local time to %#llx\n", local_समय);

out:
	tb_चयन_पंचांगu_set_समय_disruption(sw, false);
	वापस ret;
पूर्ण

/**
 * tb_चयन_पंचांगu_disable() - Disable TMU of a चयन
 * @sw: Switch whose TMU to disable
 *
 * Turns off TMU of @sw अगर it is enabled. If not enabled करोes nothing.
 */
पूर्णांक tb_चयन_पंचांगu_disable(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक ret;

	अगर (!tb_चयन_is_usb4(sw))
		वापस 0;

	/* Alपढ़ोy disabled? */
	अगर (sw->पंचांगu.rate == TB_SWITCH_TMU_RATE_OFF)
		वापस 0;

	अगर (sw->पंचांगu.unidirectional) अणु
		काष्ठा tb_चयन *parent = tb_चयन_parent(sw);
		काष्ठा tb_port *up, *करोwn;

		up = tb_upstream_port(sw);
		करोwn = tb_port_at(tb_route(sw), parent);

		/* The चयन may be unplugged so ignore any errors */
		tb_port_पंचांगu_unidirectional_disable(up);
		ret = tb_port_पंचांगu_unidirectional_disable(करोwn);
		अगर (ret)
			वापस ret;
	पूर्ण

	tb_चयन_पंचांगu_rate_ग_लिखो(sw, TB_SWITCH_TMU_RATE_OFF);

	sw->पंचांगu.unidirectional = false;
	sw->पंचांगu.rate = TB_SWITCH_TMU_RATE_OFF;

	tb_sw_dbg(sw, "TMU: disabled\n");
	वापस 0;
पूर्ण

/**
 * tb_चयन_पंचांगu_enable() - Enable TMU on a चयन
 * @sw: Switch whose TMU to enable
 *
 * Enables TMU of a चयन to be in bi-directional, HiFi mode. In this mode
 * all tunneling should work.
 */
पूर्णांक tb_चयन_पंचांगu_enable(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक ret;

	अगर (!tb_चयन_is_usb4(sw))
		वापस 0;

	अगर (tb_चयन_पंचांगu_is_enabled(sw))
		वापस 0;

	ret = tb_चयन_पंचांगu_set_समय_disruption(sw, true);
	अगर (ret)
		वापस ret;

	/* Change mode to bi-directional */
	अगर (tb_route(sw) && sw->पंचांगu.unidirectional) अणु
		काष्ठा tb_चयन *parent = tb_चयन_parent(sw);
		काष्ठा tb_port *up, *करोwn;

		up = tb_upstream_port(sw);
		करोwn = tb_port_at(tb_route(sw), parent);

		ret = tb_port_पंचांगu_unidirectional_disable(करोwn);
		अगर (ret)
			वापस ret;

		ret = tb_चयन_पंचांगu_rate_ग_लिखो(sw, TB_SWITCH_TMU_RATE_HIFI);
		अगर (ret)
			वापस ret;

		ret = tb_port_पंचांगu_unidirectional_disable(up);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = tb_चयन_पंचांगu_rate_ग_लिखो(sw, TB_SWITCH_TMU_RATE_HIFI);
		अगर (ret)
			वापस ret;
	पूर्ण

	sw->पंचांगu.unidirectional = false;
	sw->पंचांगu.rate = TB_SWITCH_TMU_RATE_HIFI;
	tb_sw_dbg(sw, "TMU: mode set to: %s\n", tb_चयन_पंचांगu_mode_name(sw));

	वापस tb_चयन_पंचांगu_set_समय_disruption(sw, false);
पूर्ण
