<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt driver - capabilities lookup
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2018, Intel Corporation
 */

#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश "tb.h"

#घोषणा CAP_OFFSET_MAX		0xff
#घोषणा VSE_CAP_OFFSET_MAX	0xffff
#घोषणा TMU_ACCESS_EN		BIT(20)

अटल पूर्णांक tb_port_enable_पंचांगu(काष्ठा tb_port *port, bool enable)
अणु
	काष्ठा tb_चयन *sw = port->sw;
	u32 value, offset;
	पूर्णांक ret;

	/*
	 * Legacy devices need to have TMU access enabled beक्रमe port
	 * space can be fully accessed.
	 */
	अगर (tb_चयन_is_light_ridge(sw))
		offset = 0x26;
	अन्यथा अगर (tb_चयन_is_eagle_ridge(sw))
		offset = 0x2a;
	अन्यथा
		वापस 0;

	ret = tb_sw_पढ़ो(sw, &value, TB_CFG_SWITCH, offset, 1);
	अगर (ret)
		वापस ret;

	अगर (enable)
		value |= TMU_ACCESS_EN;
	अन्यथा
		value &= ~TMU_ACCESS_EN;

	वापस tb_sw_ग_लिखो(sw, &value, TB_CFG_SWITCH, offset, 1);
पूर्ण

अटल व्योम tb_port_dummy_पढ़ो(काष्ठा tb_port *port)
अणु
	/*
	 * When पढ़ोing from next capability poपूर्णांकer location in port
	 * config space the पढ़ो data is not cleared on LR. To aव्योम
	 * पढ़ोing stale data on next पढ़ो perक्रमm one dummy पढ़ो after
	 * port capabilities are walked.
	 */
	अगर (tb_चयन_is_light_ridge(port->sw)) अणु
		u32 dummy;

		tb_port_पढ़ो(port, &dummy, TB_CFG_PORT, 0, 1);
	पूर्ण
पूर्ण

/**
 * tb_port_next_cap() - Return next capability in the linked list
 * @port: Port to find the capability क्रम
 * @offset: Previous capability offset (%0 क्रम start)
 *
 * Returns dword offset of the next capability in port config space
 * capability list and वापसs it. Passing %0 वापसs the first entry in
 * the capability list. If no next capability is found वापसs %0. In हाल
 * of failure वापसs negative त्रुटि_सं.
 */
पूर्णांक tb_port_next_cap(काष्ठा tb_port *port, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tb_cap_any header;
	पूर्णांक ret;

	अगर (!offset)
		वापस port->config.first_cap_offset;

	ret = tb_port_पढ़ो(port, &header, TB_CFG_PORT, offset, 1);
	अगर (ret)
		वापस ret;

	वापस header.basic.next;
पूर्ण

अटल पूर्णांक __tb_port_find_cap(काष्ठा tb_port *port, क्रमागत tb_port_cap cap)
अणु
	पूर्णांक offset = 0;

	करो अणु
		काष्ठा tb_cap_any header;
		पूर्णांक ret;

		offset = tb_port_next_cap(port, offset);
		अगर (offset < 0)
			वापस offset;

		ret = tb_port_पढ़ो(port, &header, TB_CFG_PORT, offset, 1);
		अगर (ret)
			वापस ret;

		अगर (header.basic.cap == cap)
			वापस offset;
	पूर्ण जबतक (offset > 0);

	वापस -ENOENT;
पूर्ण

/**
 * tb_port_find_cap() - Find port capability
 * @port: Port to find the capability क्रम
 * @cap: Capability to look
 *
 * Returns offset to start of capability or %-ENOENT अगर no such
 * capability was found. Negative त्रुटि_सं is वापसed अगर there was an
 * error.
 */
पूर्णांक tb_port_find_cap(काष्ठा tb_port *port, क्रमागत tb_port_cap cap)
अणु
	पूर्णांक ret;

	ret = tb_port_enable_पंचांगu(port, true);
	अगर (ret)
		वापस ret;

	ret = __tb_port_find_cap(port, cap);

	tb_port_dummy_पढ़ो(port);
	tb_port_enable_पंचांगu(port, false);

	वापस ret;
पूर्ण

/**
 * tb_चयन_next_cap() - Return next capability in the linked list
 * @sw: Switch to find the capability क्रम
 * @offset: Previous capability offset (%0 क्रम start)
 *
 * Finds dword offset of the next capability in router config space
 * capability list and वापसs it. Passing %0 वापसs the first entry in
 * the capability list. If no next capability is found वापसs %0. In हाल
 * of failure वापसs negative त्रुटि_सं.
 */
पूर्णांक tb_चयन_next_cap(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tb_cap_any header;
	पूर्णांक ret;

	अगर (!offset)
		वापस sw->config.first_cap_offset;

	ret = tb_sw_पढ़ो(sw, &header, TB_CFG_SWITCH, offset, 2);
	अगर (ret)
		वापस ret;

	चयन (header.basic.cap) अणु
	हाल TB_SWITCH_CAP_TMU:
		ret = header.basic.next;
		अवरोध;

	हाल TB_SWITCH_CAP_VSE:
		अगर (!header.extended_लघु.length)
			ret = header.extended_दीर्घ.next;
		अन्यथा
			ret = header.extended_लघु.next;
		अवरोध;

	शेष:
		tb_sw_dbg(sw, "unknown capability %#x at %#x\n",
			  header.basic.cap, offset);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret >= VSE_CAP_OFFSET_MAX ? 0 : ret;
पूर्ण

/**
 * tb_चयन_find_cap() - Find चयन capability
 * @sw: Switch to find the capability क्रम
 * @cap: Capability to look
 *
 * Returns offset to start of capability or %-ENOENT अगर no such
 * capability was found. Negative त्रुटि_सं is वापसed अगर there was an
 * error.
 */
पूर्णांक tb_चयन_find_cap(काष्ठा tb_चयन *sw, क्रमागत tb_चयन_cap cap)
अणु
	पूर्णांक offset = 0;

	करो अणु
		काष्ठा tb_cap_any header;
		पूर्णांक ret;

		offset = tb_चयन_next_cap(sw, offset);
		अगर (offset < 0)
			वापस offset;

		ret = tb_sw_पढ़ो(sw, &header, TB_CFG_SWITCH, offset, 1);
		अगर (ret)
			वापस ret;

		अगर (header.basic.cap == cap)
			वापस offset;
	पूर्ण जबतक (offset);

	वापस -ENOENT;
पूर्ण

/**
 * tb_चयन_find_vse_cap() - Find चयन venकरोr specअगरic capability
 * @sw: Switch to find the capability क्रम
 * @vsec: Venकरोr specअगरic capability to look
 *
 * Functions क्रमागतerates venकरोr specअगरic capabilities (VSEC) of a चयन
 * and वापसs offset when capability matching @vsec is found. If no
 * such capability is found वापसs %-ENOENT. In हाल of error वापसs
 * negative त्रुटि_सं.
 */
पूर्णांक tb_चयन_find_vse_cap(काष्ठा tb_चयन *sw, क्रमागत tb_चयन_vse_cap vsec)
अणु
	पूर्णांक offset = 0;

	करो अणु
		काष्ठा tb_cap_any header;
		पूर्णांक ret;

		offset = tb_चयन_next_cap(sw, offset);
		अगर (offset < 0)
			वापस offset;

		ret = tb_sw_पढ़ो(sw, &header, TB_CFG_SWITCH, offset, 1);
		अगर (ret)
			वापस ret;

		अगर (header.extended_लघु.cap == TB_SWITCH_CAP_VSE &&
		    header.extended_लघु.vsec_id == vsec)
			वापस offset;
	पूर्ण जबतक (offset);

	वापस -ENOENT;
पूर्ण
