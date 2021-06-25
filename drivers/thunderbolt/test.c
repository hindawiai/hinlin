<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KUnit tests
 *
 * Copyright (C) 2020, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <kunit/test.h>
#समावेश <linux/idr.h>

#समावेश "tb.h"
#समावेश "tunnel.h"

अटल पूर्णांक __ida_init(काष्ठा kunit_resource *res, व्योम *context)
अणु
	काष्ठा ida *ida = context;

	ida_init(ida);
	res->data = ida;
	वापस 0;
पूर्ण

अटल व्योम __ida_destroy(काष्ठा kunit_resource *res)
अणु
	काष्ठा ida *ida = res->data;

	ida_destroy(ida);
पूर्ण

अटल व्योम kunit_ida_init(काष्ठा kunit *test, काष्ठा ida *ida)
अणु
	kunit_alloc_resource(test, __ida_init, __ida_destroy, GFP_KERNEL, ida);
पूर्ण

अटल काष्ठा tb_चयन *alloc_चयन(काष्ठा kunit *test, u64 route,
				      u8 upstream_port, u8 max_port_number)
अणु
	काष्ठा tb_चयन *sw;
	माप_प्रकार size;
	पूर्णांक i;

	sw = kunit_kzalloc(test, माप(*sw), GFP_KERNEL);
	अगर (!sw)
		वापस शून्य;

	sw->config.upstream_port_number = upstream_port;
	sw->config.depth = tb_route_length(route);
	sw->config.route_hi = upper_32_bits(route);
	sw->config.route_lo = lower_32_bits(route);
	sw->config.enabled = 0;
	sw->config.max_port_number = max_port_number;

	size = (sw->config.max_port_number + 1) * माप(*sw->ports);
	sw->ports = kunit_kzalloc(test, size, GFP_KERNEL);
	अगर (!sw->ports)
		वापस शून्य;

	क्रम (i = 0; i <= sw->config.max_port_number; i++) अणु
		sw->ports[i].sw = sw;
		sw->ports[i].port = i;
		sw->ports[i].config.port_number = i;
		अगर (i) अणु
			kunit_ida_init(test, &sw->ports[i].in_hopids);
			kunit_ida_init(test, &sw->ports[i].out_hopids);
		पूर्ण
	पूर्ण

	वापस sw;
पूर्ण

अटल काष्ठा tb_चयन *alloc_host(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *sw;

	sw = alloc_चयन(test, 0, 7, 13);
	अगर (!sw)
		वापस शून्य;

	sw->config.venकरोr_id = 0x8086;
	sw->config.device_id = 0x9a1b;

	sw->ports[0].config.type = TB_TYPE_PORT;
	sw->ports[0].config.max_in_hop_id = 7;
	sw->ports[0].config.max_out_hop_id = 7;

	sw->ports[1].config.type = TB_TYPE_PORT;
	sw->ports[1].config.max_in_hop_id = 19;
	sw->ports[1].config.max_out_hop_id = 19;
	sw->ports[1].dual_link_port = &sw->ports[2];

	sw->ports[2].config.type = TB_TYPE_PORT;
	sw->ports[2].config.max_in_hop_id = 19;
	sw->ports[2].config.max_out_hop_id = 19;
	sw->ports[2].dual_link_port = &sw->ports[1];
	sw->ports[2].link_nr = 1;

	sw->ports[3].config.type = TB_TYPE_PORT;
	sw->ports[3].config.max_in_hop_id = 19;
	sw->ports[3].config.max_out_hop_id = 19;
	sw->ports[3].dual_link_port = &sw->ports[4];

	sw->ports[4].config.type = TB_TYPE_PORT;
	sw->ports[4].config.max_in_hop_id = 19;
	sw->ports[4].config.max_out_hop_id = 19;
	sw->ports[4].dual_link_port = &sw->ports[3];
	sw->ports[4].link_nr = 1;

	sw->ports[5].config.type = TB_TYPE_DP_HDMI_IN;
	sw->ports[5].config.max_in_hop_id = 9;
	sw->ports[5].config.max_out_hop_id = 9;
	sw->ports[5].cap_adap = -1;

	sw->ports[6].config.type = TB_TYPE_DP_HDMI_IN;
	sw->ports[6].config.max_in_hop_id = 9;
	sw->ports[6].config.max_out_hop_id = 9;
	sw->ports[6].cap_adap = -1;

	sw->ports[7].config.type = TB_TYPE_NHI;
	sw->ports[7].config.max_in_hop_id = 11;
	sw->ports[7].config.max_out_hop_id = 11;
	sw->ports[7].config.nfc_credits = 0x41800000;

	sw->ports[8].config.type = TB_TYPE_PCIE_DOWN;
	sw->ports[8].config.max_in_hop_id = 8;
	sw->ports[8].config.max_out_hop_id = 8;

	sw->ports[9].config.type = TB_TYPE_PCIE_DOWN;
	sw->ports[9].config.max_in_hop_id = 8;
	sw->ports[9].config.max_out_hop_id = 8;

	sw->ports[10].disabled = true;
	sw->ports[11].disabled = true;

	sw->ports[12].config.type = TB_TYPE_USB3_DOWN;
	sw->ports[12].config.max_in_hop_id = 8;
	sw->ports[12].config.max_out_hop_id = 8;

	sw->ports[13].config.type = TB_TYPE_USB3_DOWN;
	sw->ports[13].config.max_in_hop_id = 8;
	sw->ports[13].config.max_out_hop_id = 8;

	वापस sw;
पूर्ण

अटल काष्ठा tb_चयन *alloc_dev_शेष(काष्ठा kunit *test,
					   काष्ठा tb_चयन *parent,
					   u64 route, bool bonded)
अणु
	काष्ठा tb_port *port, *upstream_port;
	काष्ठा tb_चयन *sw;

	sw = alloc_चयन(test, route, 1, 19);
	अगर (!sw)
		वापस शून्य;

	sw->config.venकरोr_id = 0x8086;
	sw->config.device_id = 0x15ef;

	sw->ports[0].config.type = TB_TYPE_PORT;
	sw->ports[0].config.max_in_hop_id = 8;
	sw->ports[0].config.max_out_hop_id = 8;

	sw->ports[1].config.type = TB_TYPE_PORT;
	sw->ports[1].config.max_in_hop_id = 19;
	sw->ports[1].config.max_out_hop_id = 19;
	sw->ports[1].dual_link_port = &sw->ports[2];

	sw->ports[2].config.type = TB_TYPE_PORT;
	sw->ports[2].config.max_in_hop_id = 19;
	sw->ports[2].config.max_out_hop_id = 19;
	sw->ports[2].dual_link_port = &sw->ports[1];
	sw->ports[2].link_nr = 1;

	sw->ports[3].config.type = TB_TYPE_PORT;
	sw->ports[3].config.max_in_hop_id = 19;
	sw->ports[3].config.max_out_hop_id = 19;
	sw->ports[3].dual_link_port = &sw->ports[4];

	sw->ports[4].config.type = TB_TYPE_PORT;
	sw->ports[4].config.max_in_hop_id = 19;
	sw->ports[4].config.max_out_hop_id = 19;
	sw->ports[4].dual_link_port = &sw->ports[3];
	sw->ports[4].link_nr = 1;

	sw->ports[5].config.type = TB_TYPE_PORT;
	sw->ports[5].config.max_in_hop_id = 19;
	sw->ports[5].config.max_out_hop_id = 19;
	sw->ports[5].dual_link_port = &sw->ports[6];

	sw->ports[6].config.type = TB_TYPE_PORT;
	sw->ports[6].config.max_in_hop_id = 19;
	sw->ports[6].config.max_out_hop_id = 19;
	sw->ports[6].dual_link_port = &sw->ports[5];
	sw->ports[6].link_nr = 1;

	sw->ports[7].config.type = TB_TYPE_PORT;
	sw->ports[7].config.max_in_hop_id = 19;
	sw->ports[7].config.max_out_hop_id = 19;
	sw->ports[7].dual_link_port = &sw->ports[8];

	sw->ports[8].config.type = TB_TYPE_PORT;
	sw->ports[8].config.max_in_hop_id = 19;
	sw->ports[8].config.max_out_hop_id = 19;
	sw->ports[8].dual_link_port = &sw->ports[7];
	sw->ports[8].link_nr = 1;

	sw->ports[9].config.type = TB_TYPE_PCIE_UP;
	sw->ports[9].config.max_in_hop_id = 8;
	sw->ports[9].config.max_out_hop_id = 8;

	sw->ports[10].config.type = TB_TYPE_PCIE_DOWN;
	sw->ports[10].config.max_in_hop_id = 8;
	sw->ports[10].config.max_out_hop_id = 8;

	sw->ports[11].config.type = TB_TYPE_PCIE_DOWN;
	sw->ports[11].config.max_in_hop_id = 8;
	sw->ports[11].config.max_out_hop_id = 8;

	sw->ports[12].config.type = TB_TYPE_PCIE_DOWN;
	sw->ports[12].config.max_in_hop_id = 8;
	sw->ports[12].config.max_out_hop_id = 8;

	sw->ports[13].config.type = TB_TYPE_DP_HDMI_OUT;
	sw->ports[13].config.max_in_hop_id = 9;
	sw->ports[13].config.max_out_hop_id = 9;
	sw->ports[13].cap_adap = -1;

	sw->ports[14].config.type = TB_TYPE_DP_HDMI_OUT;
	sw->ports[14].config.max_in_hop_id = 9;
	sw->ports[14].config.max_out_hop_id = 9;
	sw->ports[14].cap_adap = -1;

	sw->ports[15].disabled = true;

	sw->ports[16].config.type = TB_TYPE_USB3_UP;
	sw->ports[16].config.max_in_hop_id = 8;
	sw->ports[16].config.max_out_hop_id = 8;

	sw->ports[17].config.type = TB_TYPE_USB3_DOWN;
	sw->ports[17].config.max_in_hop_id = 8;
	sw->ports[17].config.max_out_hop_id = 8;

	sw->ports[18].config.type = TB_TYPE_USB3_DOWN;
	sw->ports[18].config.max_in_hop_id = 8;
	sw->ports[18].config.max_out_hop_id = 8;

	sw->ports[19].config.type = TB_TYPE_USB3_DOWN;
	sw->ports[19].config.max_in_hop_id = 8;
	sw->ports[19].config.max_out_hop_id = 8;

	अगर (!parent)
		वापस sw;

	/* Link them */
	upstream_port = tb_upstream_port(sw);
	port = tb_port_at(route, parent);
	port->remote = upstream_port;
	upstream_port->remote = port;
	अगर (port->dual_link_port && upstream_port->dual_link_port) अणु
		port->dual_link_port->remote = upstream_port->dual_link_port;
		upstream_port->dual_link_port->remote = port->dual_link_port;
	पूर्ण

	अगर (bonded) अणु
		/* Bonding is used */
		port->bonded = true;
		port->dual_link_port->bonded = true;
		upstream_port->bonded = true;
		upstream_port->dual_link_port->bonded = true;
	पूर्ण

	वापस sw;
पूर्ण

अटल काष्ठा tb_चयन *alloc_dev_with_dpin(काष्ठा kunit *test,
					     काष्ठा tb_चयन *parent,
					     u64 route, bool bonded)
अणु
	काष्ठा tb_चयन *sw;

	sw = alloc_dev_शेष(test, parent, route, bonded);
	अगर (!sw)
		वापस शून्य;

	sw->ports[13].config.type = TB_TYPE_DP_HDMI_IN;
	sw->ports[13].config.max_in_hop_id = 9;
	sw->ports[13].config.max_out_hop_id = 9;

	sw->ports[14].config.type = TB_TYPE_DP_HDMI_IN;
	sw->ports[14].config.max_in_hop_id = 9;
	sw->ports[14].config.max_out_hop_id = 9;

	वापस sw;
पूर्ण

अटल व्योम tb_test_path_basic(काष्ठा kunit *test)
अणु
	काष्ठा tb_port *src_port, *dst_port, *p;
	काष्ठा tb_चयन *host;

	host = alloc_host(test);

	src_port = &host->ports[5];
	dst_port = src_port;

	p = tb_next_port_on_path(src_port, dst_port, शून्य);
	KUNIT_EXPECT_PTR_EQ(test, p, dst_port);

	p = tb_next_port_on_path(src_port, dst_port, p);
	KUNIT_EXPECT_TRUE(test, !p);
पूर्ण

अटल व्योम tb_test_path_not_connected_walk(काष्ठा kunit *test)
अणु
	काष्ठा tb_port *src_port, *dst_port, *p;
	काष्ठा tb_चयन *host, *dev;

	host = alloc_host(test);
	/* No connection between host and dev */
	dev = alloc_dev_शेष(test, शून्य, 3, true);

	src_port = &host->ports[12];
	dst_port = &dev->ports[16];

	p = tb_next_port_on_path(src_port, dst_port, शून्य);
	KUNIT_EXPECT_PTR_EQ(test, p, src_port);

	p = tb_next_port_on_path(src_port, dst_port, p);
	KUNIT_EXPECT_PTR_EQ(test, p, &host->ports[3]);

	p = tb_next_port_on_path(src_port, dst_port, p);
	KUNIT_EXPECT_TRUE(test, !p);

	/* Other direction */

	p = tb_next_port_on_path(dst_port, src_port, शून्य);
	KUNIT_EXPECT_PTR_EQ(test, p, dst_port);

	p = tb_next_port_on_path(dst_port, src_port, p);
	KUNIT_EXPECT_PTR_EQ(test, p, &dev->ports[1]);

	p = tb_next_port_on_path(dst_port, src_port, p);
	KUNIT_EXPECT_TRUE(test, !p);
पूर्ण

काष्ठा port_expectation अणु
	u64 route;
	u8 port;
	क्रमागत tb_port_type type;
पूर्ण;

अटल व्योम tb_test_path_single_hop_walk(काष्ठा kunit *test)
अणु
	/*
	 * Walks from Host PCIe करोwnstream port to Device #1 PCIe
	 * upstream port.
	 *
	 *   [Host]
	 *   1 |
	 *   1 |
	 *  [Device]
	 */
	अटल स्थिर काष्ठा port_expectation test_data[] = अणु
		अणु .route = 0x0, .port = 8, .type = TB_TYPE_PCIE_DOWN पूर्ण,
		अणु .route = 0x0, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x1, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x1, .port = 9, .type = TB_TYPE_PCIE_UP पूर्ण,
	पूर्ण;
	काष्ठा tb_port *src_port, *dst_port, *p;
	काष्ठा tb_चयन *host, *dev;
	पूर्णांक i;

	host = alloc_host(test);
	dev = alloc_dev_शेष(test, host, 1, true);

	src_port = &host->ports[8];
	dst_port = &dev->ports[9];

	/* Walk both directions */

	i = 0;
	tb_क्रम_each_port_on_path(src_port, dst_port, p) अणु
		KUNIT_EXPECT_TRUE(test, i < ARRAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_route(p->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, p->port, test_data[i].port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)p->config.type,
				test_data[i].type);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, (पूर्णांक)ARRAY_SIZE(test_data));

	i = ARRAY_SIZE(test_data) - 1;
	tb_क्रम_each_port_on_path(dst_port, src_port, p) अणु
		KUNIT_EXPECT_TRUE(test, i < ARRAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_route(p->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, p->port, test_data[i].port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)p->config.type,
				test_data[i].type);
		i--;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, -1);
पूर्ण

अटल व्योम tb_test_path_daisy_chain_walk(काष्ठा kunit *test)
अणु
	/*
	 * Walks from Host DP IN to Device #2 DP OUT.
	 *
	 *           [Host]
	 *            1 |
	 *            1 |
	 *         [Device #1]
	 *       3 /
	 *      1 /
	 * [Device #2]
	 */
	अटल स्थिर काष्ठा port_expectation test_data[] = अणु
		अणु .route = 0x0, .port = 5, .type = TB_TYPE_DP_HDMI_IN पूर्ण,
		अणु .route = 0x0, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x1, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x1, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x301, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x301, .port = 13, .type = TB_TYPE_DP_HDMI_OUT पूर्ण,
	पूर्ण;
	काष्ठा tb_port *src_port, *dst_port, *p;
	काष्ठा tb_चयन *host, *dev1, *dev2;
	पूर्णांक i;

	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	dev2 = alloc_dev_शेष(test, dev1, 0x301, true);

	src_port = &host->ports[5];
	dst_port = &dev2->ports[13];

	/* Walk both directions */

	i = 0;
	tb_क्रम_each_port_on_path(src_port, dst_port, p) अणु
		KUNIT_EXPECT_TRUE(test, i < ARRAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_route(p->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, p->port, test_data[i].port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)p->config.type,
				test_data[i].type);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, (पूर्णांक)ARRAY_SIZE(test_data));

	i = ARRAY_SIZE(test_data) - 1;
	tb_क्रम_each_port_on_path(dst_port, src_port, p) अणु
		KUNIT_EXPECT_TRUE(test, i < ARRAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_route(p->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, p->port, test_data[i].port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)p->config.type,
				test_data[i].type);
		i--;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, -1);
पूर्ण

अटल व्योम tb_test_path_simple_tree_walk(काष्ठा kunit *test)
अणु
	/*
	 * Walks from Host DP IN to Device #3 DP OUT.
	 *
	 *           [Host]
	 *            1 |
	 *            1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #4]
	 *             | 1
	 *         [Device #3]
	 */
	अटल स्थिर काष्ठा port_expectation test_data[] = अणु
		अणु .route = 0x0, .port = 5, .type = TB_TYPE_DP_HDMI_IN पूर्ण,
		अणु .route = 0x0, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x1, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x1, .port = 5, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x501, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x501, .port = 13, .type = TB_TYPE_DP_HDMI_OUT पूर्ण,
	पूर्ण;
	काष्ठा tb_port *src_port, *dst_port, *p;
	काष्ठा tb_चयन *host, *dev1, *dev3;
	पूर्णांक i;

	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	alloc_dev_शेष(test, dev1, 0x301, true);
	dev3 = alloc_dev_शेष(test, dev1, 0x501, true);
	alloc_dev_शेष(test, dev1, 0x701, true);

	src_port = &host->ports[5];
	dst_port = &dev3->ports[13];

	/* Walk both directions */

	i = 0;
	tb_क्रम_each_port_on_path(src_port, dst_port, p) अणु
		KUNIT_EXPECT_TRUE(test, i < ARRAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_route(p->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, p->port, test_data[i].port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)p->config.type,
				test_data[i].type);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, (पूर्णांक)ARRAY_SIZE(test_data));

	i = ARRAY_SIZE(test_data) - 1;
	tb_क्रम_each_port_on_path(dst_port, src_port, p) अणु
		KUNIT_EXPECT_TRUE(test, i < ARRAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_route(p->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, p->port, test_data[i].port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)p->config.type,
				test_data[i].type);
		i--;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, -1);
पूर्ण

अटल व्योम tb_test_path_complex_tree_walk(काष्ठा kunit *test)
अणु
	/*
	 * Walks from Device #3 DP IN to Device #9 DP OUT.
	 *
	 *           [Host]
	 *            1 |
	 *            1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #5]
	 *    5 |      | 1         \ 7
	 *    1 |  [Device #4]      \ 1
	 * [Device #3]             [Device #6]
	 *                       3 /
	 *                      1 /
	 *                    [Device #7]
	 *                  3 /      | 5
	 *                 1 /       |
	 *               [Device #8] | 1
	 *                       [Device #9]
	 */
	अटल स्थिर काष्ठा port_expectation test_data[] = अणु
		अणु .route = 0x50301, .port = 13, .type = TB_TYPE_DP_HDMI_IN पूर्ण,
		अणु .route = 0x50301, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x301, .port = 5, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x301, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x1, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x1, .port = 7, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x701, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x701, .port = 7, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x70701, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x70701, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x3070701, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x3070701, .port = 5, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x503070701, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x503070701, .port = 14, .type = TB_TYPE_DP_HDMI_OUT पूर्ण,
	पूर्ण;
	काष्ठा tb_चयन *host, *dev1, *dev2, *dev3, *dev5, *dev6, *dev7, *dev9;
	काष्ठा tb_port *src_port, *dst_port, *p;
	पूर्णांक i;

	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	dev2 = alloc_dev_शेष(test, dev1, 0x301, true);
	dev3 = alloc_dev_with_dpin(test, dev2, 0x50301, true);
	alloc_dev_शेष(test, dev1, 0x501, true);
	dev5 = alloc_dev_शेष(test, dev1, 0x701, true);
	dev6 = alloc_dev_शेष(test, dev5, 0x70701, true);
	dev7 = alloc_dev_शेष(test, dev6, 0x3070701, true);
	alloc_dev_शेष(test, dev7, 0x303070701, true);
	dev9 = alloc_dev_शेष(test, dev7, 0x503070701, true);

	src_port = &dev3->ports[13];
	dst_port = &dev9->ports[14];

	/* Walk both directions */

	i = 0;
	tb_क्रम_each_port_on_path(src_port, dst_port, p) अणु
		KUNIT_EXPECT_TRUE(test, i < ARRAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_route(p->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, p->port, test_data[i].port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)p->config.type,
				test_data[i].type);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, (पूर्णांक)ARRAY_SIZE(test_data));

	i = ARRAY_SIZE(test_data) - 1;
	tb_क्रम_each_port_on_path(dst_port, src_port, p) अणु
		KUNIT_EXPECT_TRUE(test, i < ARRAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_route(p->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, p->port, test_data[i].port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)p->config.type,
				test_data[i].type);
		i--;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, -1);
पूर्ण

अटल व्योम tb_test_path_max_length_walk(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *host, *dev1, *dev2, *dev3, *dev4, *dev5, *dev6;
	काष्ठा tb_चयन *dev7, *dev8, *dev9, *dev10, *dev11, *dev12;
	काष्ठा tb_port *src_port, *dst_port, *p;
	पूर्णांक i;

	/*
	 * Walks from Device #6 DP IN to Device #12 DP OUT.
	 *
	 *          [Host]
	 *         1 /  \ 3
	 *        1 /    \ 1
	 * [Device #1]   [Device #7]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #2]   [Device #8]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #3]   [Device #9]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #4]   [Device #10]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #5]   [Device #11]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #6]   [Device #12]
	 */
	अटल स्थिर काष्ठा port_expectation test_data[] = अणु
		अणु .route = 0x30303030301, .port = 13, .type = TB_TYPE_DP_HDMI_IN पूर्ण,
		अणु .route = 0x30303030301, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x303030301, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x303030301, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x3030301, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x3030301, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x30301, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x30301, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x301, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x301, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x1, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x1, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x0, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x0, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x3, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x3, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x303, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x303, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x30303, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x30303, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x3030303, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x3030303, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x303030303, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x303030303, .port = 3, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x30303030303, .port = 1, .type = TB_TYPE_PORT पूर्ण,
		अणु .route = 0x30303030303, .port = 13, .type = TB_TYPE_DP_HDMI_OUT पूर्ण,
	पूर्ण;

	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	dev2 = alloc_dev_शेष(test, dev1, 0x301, true);
	dev3 = alloc_dev_शेष(test, dev2, 0x30301, true);
	dev4 = alloc_dev_शेष(test, dev3, 0x3030301, true);
	dev5 = alloc_dev_शेष(test, dev4, 0x303030301, true);
	dev6 = alloc_dev_with_dpin(test, dev5, 0x30303030301, true);
	dev7 = alloc_dev_शेष(test, host, 0x3, true);
	dev8 = alloc_dev_शेष(test, dev7, 0x303, true);
	dev9 = alloc_dev_शेष(test, dev8, 0x30303, true);
	dev10 = alloc_dev_शेष(test, dev9, 0x3030303, true);
	dev11 = alloc_dev_शेष(test, dev10, 0x303030303, true);
	dev12 = alloc_dev_शेष(test, dev11, 0x30303030303, true);

	src_port = &dev6->ports[13];
	dst_port = &dev12->ports[13];

	/* Walk both directions */

	i = 0;
	tb_क्रम_each_port_on_path(src_port, dst_port, p) अणु
		KUNIT_EXPECT_TRUE(test, i < ARRAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_route(p->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, p->port, test_data[i].port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)p->config.type,
				test_data[i].type);
		i++;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, (पूर्णांक)ARRAY_SIZE(test_data));

	i = ARRAY_SIZE(test_data) - 1;
	tb_क्रम_each_port_on_path(dst_port, src_port, p) अणु
		KUNIT_EXPECT_TRUE(test, i < ARRAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_route(p->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, p->port, test_data[i].port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)p->config.type,
				test_data[i].type);
		i--;
	पूर्ण

	KUNIT_EXPECT_EQ(test, i, -1);
पूर्ण

अटल व्योम tb_test_path_not_connected(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *host, *dev1, *dev2;
	काष्ठा tb_port *करोwn, *up;
	काष्ठा tb_path *path;

	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x3, false);
	/* Not connected to anything */
	dev2 = alloc_dev_शेष(test, शून्य, 0x303, false);

	करोwn = &dev1->ports[10];
	up = &dev2->ports[9];

	path = tb_path_alloc(शून्य, करोwn, 8, up, 8, 0, "PCIe Down");
	KUNIT_ASSERT_TRUE(test, path == शून्य);
	path = tb_path_alloc(शून्य, करोwn, 8, up, 8, 1, "PCIe Down");
	KUNIT_ASSERT_TRUE(test, path == शून्य);
पूर्ण

काष्ठा hop_expectation अणु
	u64 route;
	u8 in_port;
	क्रमागत tb_port_type in_type;
	u8 out_port;
	क्रमागत tb_port_type out_type;
पूर्ण;

अटल व्योम tb_test_path_not_bonded_lane0(काष्ठा kunit *test)
अणु
	/*
	 * PCIe path from host to device using lane 0.
	 *
	 *   [Host]
	 *   3 |: 4
	 *   1 |: 2
	 *  [Device]
	 */
	अटल स्थिर काष्ठा hop_expectation test_data[] = अणु
		अणु
			.route = 0x0,
			.in_port = 9,
			.in_type = TB_TYPE_PCIE_DOWN,
			.out_port = 3,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x3,
			.in_port = 1,
			.in_type = TB_TYPE_PORT,
			.out_port = 9,
			.out_type = TB_TYPE_PCIE_UP,
		पूर्ण,
	पूर्ण;
	काष्ठा tb_चयन *host, *dev;
	काष्ठा tb_port *करोwn, *up;
	काष्ठा tb_path *path;
	पूर्णांक i;

	host = alloc_host(test);
	dev = alloc_dev_शेष(test, host, 0x3, false);

	करोwn = &host->ports[9];
	up = &dev->ports[9];

	path = tb_path_alloc(शून्य, करोwn, 8, up, 8, 0, "PCIe Down");
	KUNIT_ASSERT_TRUE(test, path != शून्य);
	KUNIT_ASSERT_EQ(test, path->path_length, (पूर्णांक)ARRAY_SIZE(test_data));
	क्रम (i = 0; i < ARRAY_SIZE(test_data); i++) अणु
		स्थिर काष्ठा tb_port *in_port, *out_port;

		in_port = path->hops[i].in_port;
		out_port = path->hops[i].out_port;

		KUNIT_EXPECT_EQ(test, tb_route(in_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, in_port->port, test_data[i].in_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)in_port->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_route(out_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, out_port->port, test_data[i].out_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)out_port->config.type,
				test_data[i].out_type);
	पूर्ण
	tb_path_मुक्त(path);
पूर्ण

अटल व्योम tb_test_path_not_bonded_lane1(काष्ठा kunit *test)
अणु
	/*
	 * DP Video path from host to device using lane 1. Paths like
	 * these are only used with Thunderbolt 1 devices where lane
	 * bonding is not possible. USB4 specअगरically करोes not allow
	 * paths like this (you either use lane 0 where lane 1 is
	 * disabled or both lanes are bonded).
	 *
	 *   [Host]
	 *   1 :| 2
	 *   1 :| 2
	 *  [Device]
	 */
	अटल स्थिर काष्ठा hop_expectation test_data[] = अणु
		अणु
			.route = 0x0,
			.in_port = 5,
			.in_type = TB_TYPE_DP_HDMI_IN,
			.out_port = 2,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x1,
			.in_port = 2,
			.in_type = TB_TYPE_PORT,
			.out_port = 13,
			.out_type = TB_TYPE_DP_HDMI_OUT,
		पूर्ण,
	पूर्ण;
	काष्ठा tb_चयन *host, *dev;
	काष्ठा tb_port *in, *out;
	काष्ठा tb_path *path;
	पूर्णांक i;

	host = alloc_host(test);
	dev = alloc_dev_शेष(test, host, 0x1, false);

	in = &host->ports[5];
	out = &dev->ports[13];

	path = tb_path_alloc(शून्य, in, 9, out, 9, 1, "Video");
	KUNIT_ASSERT_TRUE(test, path != शून्य);
	KUNIT_ASSERT_EQ(test, path->path_length, (पूर्णांक)ARRAY_SIZE(test_data));
	क्रम (i = 0; i < ARRAY_SIZE(test_data); i++) अणु
		स्थिर काष्ठा tb_port *in_port, *out_port;

		in_port = path->hops[i].in_port;
		out_port = path->hops[i].out_port;

		KUNIT_EXPECT_EQ(test, tb_route(in_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, in_port->port, test_data[i].in_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)in_port->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_route(out_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, out_port->port, test_data[i].out_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)out_port->config.type,
				test_data[i].out_type);
	पूर्ण
	tb_path_मुक्त(path);
पूर्ण

अटल व्योम tb_test_path_not_bonded_lane1_chain(काष्ठा kunit *test)
अणु
	/*
	 * DP Video path from host to device 3 using lane 1.
	 *
	 *    [Host]
	 *    1 :| 2
	 *    1 :| 2
	 *  [Device #1]
	 *    7 :| 8
	 *    1 :| 2
	 *  [Device #2]
	 *    5 :| 6
	 *    1 :| 2
	 *  [Device #3]
	 */
	अटल स्थिर काष्ठा hop_expectation test_data[] = अणु
		अणु
			.route = 0x0,
			.in_port = 5,
			.in_type = TB_TYPE_DP_HDMI_IN,
			.out_port = 2,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x1,
			.in_port = 2,
			.in_type = TB_TYPE_PORT,
			.out_port = 8,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x701,
			.in_port = 2,
			.in_type = TB_TYPE_PORT,
			.out_port = 6,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x50701,
			.in_port = 2,
			.in_type = TB_TYPE_PORT,
			.out_port = 13,
			.out_type = TB_TYPE_DP_HDMI_OUT,
		पूर्ण,
	पूर्ण;
	काष्ठा tb_चयन *host, *dev1, *dev2, *dev3;
	काष्ठा tb_port *in, *out;
	काष्ठा tb_path *path;
	पूर्णांक i;

	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, false);
	dev2 = alloc_dev_शेष(test, dev1, 0x701, false);
	dev3 = alloc_dev_शेष(test, dev2, 0x50701, false);

	in = &host->ports[5];
	out = &dev3->ports[13];

	path = tb_path_alloc(शून्य, in, 9, out, 9, 1, "Video");
	KUNIT_ASSERT_TRUE(test, path != शून्य);
	KUNIT_ASSERT_EQ(test, path->path_length, (पूर्णांक)ARRAY_SIZE(test_data));
	क्रम (i = 0; i < ARRAY_SIZE(test_data); i++) अणु
		स्थिर काष्ठा tb_port *in_port, *out_port;

		in_port = path->hops[i].in_port;
		out_port = path->hops[i].out_port;

		KUNIT_EXPECT_EQ(test, tb_route(in_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, in_port->port, test_data[i].in_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)in_port->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_route(out_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, out_port->port, test_data[i].out_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)out_port->config.type,
				test_data[i].out_type);
	पूर्ण
	tb_path_मुक्त(path);
पूर्ण

अटल व्योम tb_test_path_not_bonded_lane1_chain_reverse(काष्ठा kunit *test)
अणु
	/*
	 * DP Video path from device 3 to host using lane 1.
	 *
	 *    [Host]
	 *    1 :| 2
	 *    1 :| 2
	 *  [Device #1]
	 *    7 :| 8
	 *    1 :| 2
	 *  [Device #2]
	 *    5 :| 6
	 *    1 :| 2
	 *  [Device #3]
	 */
	अटल स्थिर काष्ठा hop_expectation test_data[] = अणु
		अणु
			.route = 0x50701,
			.in_port = 13,
			.in_type = TB_TYPE_DP_HDMI_IN,
			.out_port = 2,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x701,
			.in_port = 6,
			.in_type = TB_TYPE_PORT,
			.out_port = 2,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x1,
			.in_port = 8,
			.in_type = TB_TYPE_PORT,
			.out_port = 2,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x0,
			.in_port = 2,
			.in_type = TB_TYPE_PORT,
			.out_port = 5,
			.out_type = TB_TYPE_DP_HDMI_IN,
		पूर्ण,
	पूर्ण;
	काष्ठा tb_चयन *host, *dev1, *dev2, *dev3;
	काष्ठा tb_port *in, *out;
	काष्ठा tb_path *path;
	पूर्णांक i;

	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, false);
	dev2 = alloc_dev_शेष(test, dev1, 0x701, false);
	dev3 = alloc_dev_with_dpin(test, dev2, 0x50701, false);

	in = &dev3->ports[13];
	out = &host->ports[5];

	path = tb_path_alloc(शून्य, in, 9, out, 9, 1, "Video");
	KUNIT_ASSERT_TRUE(test, path != शून्य);
	KUNIT_ASSERT_EQ(test, path->path_length, (पूर्णांक)ARRAY_SIZE(test_data));
	क्रम (i = 0; i < ARRAY_SIZE(test_data); i++) अणु
		स्थिर काष्ठा tb_port *in_port, *out_port;

		in_port = path->hops[i].in_port;
		out_port = path->hops[i].out_port;

		KUNIT_EXPECT_EQ(test, tb_route(in_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, in_port->port, test_data[i].in_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)in_port->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_route(out_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, out_port->port, test_data[i].out_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)out_port->config.type,
				test_data[i].out_type);
	पूर्ण
	tb_path_मुक्त(path);
पूर्ण

अटल व्योम tb_test_path_mixed_chain(काष्ठा kunit *test)
अणु
	/*
	 * DP Video path from host to device 4 where first and last link
	 * is bonded.
	 *
	 *    [Host]
	 *    1 |
	 *    1 |
	 *  [Device #1]
	 *    7 :| 8
	 *    1 :| 2
	 *  [Device #2]
	 *    5 :| 6
	 *    1 :| 2
	 *  [Device #3]
	 *    3 |
	 *    1 |
	 *  [Device #4]
	 */
	अटल स्थिर काष्ठा hop_expectation test_data[] = अणु
		अणु
			.route = 0x0,
			.in_port = 5,
			.in_type = TB_TYPE_DP_HDMI_IN,
			.out_port = 1,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x1,
			.in_port = 1,
			.in_type = TB_TYPE_PORT,
			.out_port = 8,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x701,
			.in_port = 2,
			.in_type = TB_TYPE_PORT,
			.out_port = 6,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x50701,
			.in_port = 2,
			.in_type = TB_TYPE_PORT,
			.out_port = 3,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x3050701,
			.in_port = 1,
			.in_type = TB_TYPE_PORT,
			.out_port = 13,
			.out_type = TB_TYPE_DP_HDMI_OUT,
		पूर्ण,
	पूर्ण;
	काष्ठा tb_चयन *host, *dev1, *dev2, *dev3, *dev4;
	काष्ठा tb_port *in, *out;
	काष्ठा tb_path *path;
	पूर्णांक i;

	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	dev2 = alloc_dev_शेष(test, dev1, 0x701, false);
	dev3 = alloc_dev_शेष(test, dev2, 0x50701, false);
	dev4 = alloc_dev_शेष(test, dev3, 0x3050701, true);

	in = &host->ports[5];
	out = &dev4->ports[13];

	path = tb_path_alloc(शून्य, in, 9, out, 9, 1, "Video");
	KUNIT_ASSERT_TRUE(test, path != शून्य);
	KUNIT_ASSERT_EQ(test, path->path_length, (पूर्णांक)ARRAY_SIZE(test_data));
	क्रम (i = 0; i < ARRAY_SIZE(test_data); i++) अणु
		स्थिर काष्ठा tb_port *in_port, *out_port;

		in_port = path->hops[i].in_port;
		out_port = path->hops[i].out_port;

		KUNIT_EXPECT_EQ(test, tb_route(in_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, in_port->port, test_data[i].in_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)in_port->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_route(out_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, out_port->port, test_data[i].out_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)out_port->config.type,
				test_data[i].out_type);
	पूर्ण
	tb_path_मुक्त(path);
पूर्ण

अटल व्योम tb_test_path_mixed_chain_reverse(काष्ठा kunit *test)
अणु
	/*
	 * DP Video path from device 4 to host where first and last link
	 * is bonded.
	 *
	 *    [Host]
	 *    1 |
	 *    1 |
	 *  [Device #1]
	 *    7 :| 8
	 *    1 :| 2
	 *  [Device #2]
	 *    5 :| 6
	 *    1 :| 2
	 *  [Device #3]
	 *    3 |
	 *    1 |
	 *  [Device #4]
	 */
	अटल स्थिर काष्ठा hop_expectation test_data[] = अणु
		अणु
			.route = 0x3050701,
			.in_port = 13,
			.in_type = TB_TYPE_DP_HDMI_OUT,
			.out_port = 1,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x50701,
			.in_port = 3,
			.in_type = TB_TYPE_PORT,
			.out_port = 2,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x701,
			.in_port = 6,
			.in_type = TB_TYPE_PORT,
			.out_port = 2,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x1,
			.in_port = 8,
			.in_type = TB_TYPE_PORT,
			.out_port = 1,
			.out_type = TB_TYPE_PORT,
		पूर्ण,
		अणु
			.route = 0x0,
			.in_port = 1,
			.in_type = TB_TYPE_PORT,
			.out_port = 5,
			.out_type = TB_TYPE_DP_HDMI_IN,
		पूर्ण,
	पूर्ण;
	काष्ठा tb_चयन *host, *dev1, *dev2, *dev3, *dev4;
	काष्ठा tb_port *in, *out;
	काष्ठा tb_path *path;
	पूर्णांक i;

	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	dev2 = alloc_dev_शेष(test, dev1, 0x701, false);
	dev3 = alloc_dev_शेष(test, dev2, 0x50701, false);
	dev4 = alloc_dev_शेष(test, dev3, 0x3050701, true);

	in = &dev4->ports[13];
	out = &host->ports[5];

	path = tb_path_alloc(शून्य, in, 9, out, 9, 1, "Video");
	KUNIT_ASSERT_TRUE(test, path != शून्य);
	KUNIT_ASSERT_EQ(test, path->path_length, (पूर्णांक)ARRAY_SIZE(test_data));
	क्रम (i = 0; i < ARRAY_SIZE(test_data); i++) अणु
		स्थिर काष्ठा tb_port *in_port, *out_port;

		in_port = path->hops[i].in_port;
		out_port = path->hops[i].out_port;

		KUNIT_EXPECT_EQ(test, tb_route(in_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, in_port->port, test_data[i].in_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)in_port->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_route(out_port->sw), test_data[i].route);
		KUNIT_EXPECT_EQ(test, out_port->port, test_data[i].out_port);
		KUNIT_EXPECT_EQ(test, (क्रमागत tb_port_type)out_port->config.type,
				test_data[i].out_type);
	पूर्ण
	tb_path_मुक्त(path);
पूर्ण

अटल व्योम tb_test_tunnel_pcie(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *host, *dev1, *dev2;
	काष्ठा tb_tunnel *tunnel1, *tunnel2;
	काष्ठा tb_port *करोwn, *up;

	/*
	 * Create PCIe tunnel between host and two devices.
	 *
	 *   [Host]
	 *    1 |
	 *    1 |
	 *  [Device #1]
	 *    5 |
	 *    1 |
	 *  [Device #2]
	 */
	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	dev2 = alloc_dev_शेष(test, dev1, 0x501, true);

	करोwn = &host->ports[8];
	up = &dev1->ports[9];
	tunnel1 = tb_tunnel_alloc_pci(शून्य, up, करोwn);
	KUNIT_ASSERT_TRUE(test, tunnel1 != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel1->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_PCI);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->src_port, करोwn);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->dst_port, up);
	KUNIT_ASSERT_EQ(test, tunnel1->npaths, (माप_प्रकार)2);
	KUNIT_ASSERT_EQ(test, tunnel1->paths[0]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->paths[0]->hops[0].in_port, करोwn);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->paths[0]->hops[1].out_port, up);
	KUNIT_ASSERT_EQ(test, tunnel1->paths[1]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->paths[1]->hops[0].in_port, up);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->paths[1]->hops[1].out_port, करोwn);

	करोwn = &dev1->ports[10];
	up = &dev2->ports[9];
	tunnel2 = tb_tunnel_alloc_pci(शून्य, up, करोwn);
	KUNIT_ASSERT_TRUE(test, tunnel2 != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel2->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_PCI);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->src_port, करोwn);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->dst_port, up);
	KUNIT_ASSERT_EQ(test, tunnel2->npaths, (माप_प्रकार)2);
	KUNIT_ASSERT_EQ(test, tunnel2->paths[0]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->paths[0]->hops[0].in_port, करोwn);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->paths[0]->hops[1].out_port, up);
	KUNIT_ASSERT_EQ(test, tunnel2->paths[1]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->paths[1]->hops[0].in_port, up);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->paths[1]->hops[1].out_port, करोwn);

	tb_tunnel_मुक्त(tunnel2);
	tb_tunnel_मुक्त(tunnel1);
पूर्ण

अटल व्योम tb_test_tunnel_dp(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *host, *dev;
	काष्ठा tb_port *in, *out;
	काष्ठा tb_tunnel *tunnel;

	/*
	 * Create DP tunnel between Host and Device
	 *
	 *   [Host]
	 *   1 |
	 *   1 |
	 *  [Device]
	 */
	host = alloc_host(test);
	dev = alloc_dev_शेष(test, host, 0x3, true);

	in = &host->ports[5];
	out = &dev->ports[13];

	tunnel = tb_tunnel_alloc_dp(शून्य, in, out, 0, 0);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_DP);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->src_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->dst_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->npaths, (माप_प्रकार)3);
	KUNIT_ASSERT_EQ(test, tunnel->paths[0]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].in_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[1].out_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->paths[1]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[0].in_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[1].out_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->paths[2]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[2]->hops[0].in_port, out);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[2]->hops[1].out_port, in);
	tb_tunnel_मुक्त(tunnel);
पूर्ण

अटल व्योम tb_test_tunnel_dp_chain(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *host, *dev1, *dev4;
	काष्ठा tb_port *in, *out;
	काष्ठा tb_tunnel *tunnel;

	/*
	 * Create DP tunnel from Host DP IN to Device #4 DP OUT.
	 *
	 *           [Host]
	 *            1 |
	 *            1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #4]
	 *             | 1
	 *         [Device #3]
	 */
	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	alloc_dev_शेष(test, dev1, 0x301, true);
	alloc_dev_शेष(test, dev1, 0x501, true);
	dev4 = alloc_dev_शेष(test, dev1, 0x701, true);

	in = &host->ports[5];
	out = &dev4->ports[14];

	tunnel = tb_tunnel_alloc_dp(शून्य, in, out, 0, 0);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_DP);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->src_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->dst_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->npaths, (माप_प्रकार)3);
	KUNIT_ASSERT_EQ(test, tunnel->paths[0]->path_length, 3);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].in_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[2].out_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->paths[1]->path_length, 3);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[0].in_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[2].out_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->paths[2]->path_length, 3);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[2]->hops[0].in_port, out);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[2]->hops[2].out_port, in);
	tb_tunnel_मुक्त(tunnel);
पूर्ण

अटल व्योम tb_test_tunnel_dp_tree(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *host, *dev1, *dev2, *dev3, *dev5;
	काष्ठा tb_port *in, *out;
	काष्ठा tb_tunnel *tunnel;

	/*
	 * Create DP tunnel from Device #2 DP IN to Device #5 DP OUT.
	 *
	 *          [Host]
	 *           3 |
	 *           1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #4]
	 *             | 1
	 *         [Device #3]
	 *             | 5
	 *             | 1
	 *         [Device #5]
	 */
	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x3, true);
	dev2 = alloc_dev_with_dpin(test, dev1, 0x303, true);
	dev3 = alloc_dev_शेष(test, dev1, 0x503, true);
	alloc_dev_शेष(test, dev1, 0x703, true);
	dev5 = alloc_dev_शेष(test, dev3, 0x50503, true);

	in = &dev2->ports[13];
	out = &dev5->ports[13];

	tunnel = tb_tunnel_alloc_dp(शून्य, in, out, 0, 0);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_DP);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->src_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->dst_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->npaths, (माप_प्रकार)3);
	KUNIT_ASSERT_EQ(test, tunnel->paths[0]->path_length, 4);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].in_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[3].out_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->paths[1]->path_length, 4);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[0].in_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[3].out_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->paths[2]->path_length, 4);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[2]->hops[0].in_port, out);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[2]->hops[3].out_port, in);
	tb_tunnel_मुक्त(tunnel);
पूर्ण

अटल व्योम tb_test_tunnel_dp_max_length(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *host, *dev1, *dev2, *dev3, *dev4, *dev5, *dev6;
	काष्ठा tb_चयन *dev7, *dev8, *dev9, *dev10, *dev11, *dev12;
	काष्ठा tb_port *in, *out;
	काष्ठा tb_tunnel *tunnel;

	/*
	 * Creates DP tunnel from Device #6 to Device #12.
	 *
	 *          [Host]
	 *         1 /  \ 3
	 *        1 /    \ 1
	 * [Device #1]   [Device #7]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #2]   [Device #8]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #3]   [Device #9]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #4]   [Device #10]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #5]   [Device #11]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #6]   [Device #12]
	 */
	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	dev2 = alloc_dev_शेष(test, dev1, 0x301, true);
	dev3 = alloc_dev_शेष(test, dev2, 0x30301, true);
	dev4 = alloc_dev_शेष(test, dev3, 0x3030301, true);
	dev5 = alloc_dev_शेष(test, dev4, 0x303030301, true);
	dev6 = alloc_dev_with_dpin(test, dev5, 0x30303030301, true);
	dev7 = alloc_dev_शेष(test, host, 0x3, true);
	dev8 = alloc_dev_शेष(test, dev7, 0x303, true);
	dev9 = alloc_dev_शेष(test, dev8, 0x30303, true);
	dev10 = alloc_dev_शेष(test, dev9, 0x3030303, true);
	dev11 = alloc_dev_शेष(test, dev10, 0x303030303, true);
	dev12 = alloc_dev_शेष(test, dev11, 0x30303030303, true);

	in = &dev6->ports[13];
	out = &dev12->ports[13];

	tunnel = tb_tunnel_alloc_dp(शून्य, in, out, 0, 0);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_DP);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->src_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->dst_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->npaths, (माप_प्रकार)3);
	KUNIT_ASSERT_EQ(test, tunnel->paths[0]->path_length, 13);
	/* First hop */
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].in_port, in);
	/* Middle */
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[6].in_port,
			    &host->ports[1]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[6].out_port,
			    &host->ports[3]);
	/* Last */
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[12].out_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->paths[1]->path_length, 13);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[0].in_port, in);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[6].in_port,
			    &host->ports[1]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[6].out_port,
			    &host->ports[3]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[12].out_port, out);
	KUNIT_ASSERT_EQ(test, tunnel->paths[2]->path_length, 13);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[2]->hops[0].in_port, out);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[2]->hops[6].in_port,
			    &host->ports[3]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[2]->hops[6].out_port,
			    &host->ports[1]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[2]->hops[12].out_port, in);
	tb_tunnel_मुक्त(tunnel);
पूर्ण

अटल व्योम tb_test_tunnel_usb3(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *host, *dev1, *dev2;
	काष्ठा tb_tunnel *tunnel1, *tunnel2;
	काष्ठा tb_port *करोwn, *up;

	/*
	 * Create USB3 tunnel between host and two devices.
	 *
	 *   [Host]
	 *    1 |
	 *    1 |
	 *  [Device #1]
	 *          \ 7
	 *           \ 1
	 *         [Device #2]
	 */
	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	dev2 = alloc_dev_शेष(test, dev1, 0x701, true);

	करोwn = &host->ports[12];
	up = &dev1->ports[16];
	tunnel1 = tb_tunnel_alloc_usb3(शून्य, up, करोwn, 0, 0);
	KUNIT_ASSERT_TRUE(test, tunnel1 != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel1->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_USB3);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->src_port, करोwn);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->dst_port, up);
	KUNIT_ASSERT_EQ(test, tunnel1->npaths, (माप_प्रकार)2);
	KUNIT_ASSERT_EQ(test, tunnel1->paths[0]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->paths[0]->hops[0].in_port, करोwn);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->paths[0]->hops[1].out_port, up);
	KUNIT_ASSERT_EQ(test, tunnel1->paths[1]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->paths[1]->hops[0].in_port, up);
	KUNIT_EXPECT_PTR_EQ(test, tunnel1->paths[1]->hops[1].out_port, करोwn);

	करोwn = &dev1->ports[17];
	up = &dev2->ports[16];
	tunnel2 = tb_tunnel_alloc_usb3(शून्य, up, करोwn, 0, 0);
	KUNIT_ASSERT_TRUE(test, tunnel2 != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel2->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_USB3);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->src_port, करोwn);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->dst_port, up);
	KUNIT_ASSERT_EQ(test, tunnel2->npaths, (माप_प्रकार)2);
	KUNIT_ASSERT_EQ(test, tunnel2->paths[0]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->paths[0]->hops[0].in_port, करोwn);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->paths[0]->hops[1].out_port, up);
	KUNIT_ASSERT_EQ(test, tunnel2->paths[1]->path_length, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->paths[1]->hops[0].in_port, up);
	KUNIT_EXPECT_PTR_EQ(test, tunnel2->paths[1]->hops[1].out_port, करोwn);

	tb_tunnel_मुक्त(tunnel2);
	tb_tunnel_मुक्त(tunnel1);
पूर्ण

अटल व्योम tb_test_tunnel_port_on_path(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *host, *dev1, *dev2, *dev3, *dev4, *dev5;
	काष्ठा tb_port *in, *out, *port;
	काष्ठा tb_tunnel *dp_tunnel;

	/*
	 *          [Host]
	 *           3 |
	 *           1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #4]
	 *             | 1
	 *         [Device #3]
	 *             | 5
	 *             | 1
	 *         [Device #5]
	 */
	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x3, true);
	dev2 = alloc_dev_with_dpin(test, dev1, 0x303, true);
	dev3 = alloc_dev_शेष(test, dev1, 0x503, true);
	dev4 = alloc_dev_शेष(test, dev1, 0x703, true);
	dev5 = alloc_dev_शेष(test, dev3, 0x50503, true);

	in = &dev2->ports[13];
	out = &dev5->ports[13];

	dp_tunnel = tb_tunnel_alloc_dp(शून्य, in, out, 0, 0);
	KUNIT_ASSERT_TRUE(test, dp_tunnel != शून्य);

	KUNIT_EXPECT_TRUE(test, tb_tunnel_port_on_path(dp_tunnel, in));
	KUNIT_EXPECT_TRUE(test, tb_tunnel_port_on_path(dp_tunnel, out));

	port = &host->ports[8];
	KUNIT_EXPECT_FALSE(test, tb_tunnel_port_on_path(dp_tunnel, port));

	port = &host->ports[3];
	KUNIT_EXPECT_FALSE(test, tb_tunnel_port_on_path(dp_tunnel, port));

	port = &dev1->ports[1];
	KUNIT_EXPECT_FALSE(test, tb_tunnel_port_on_path(dp_tunnel, port));

	port = &dev1->ports[3];
	KUNIT_EXPECT_TRUE(test, tb_tunnel_port_on_path(dp_tunnel, port));

	port = &dev1->ports[5];
	KUNIT_EXPECT_TRUE(test, tb_tunnel_port_on_path(dp_tunnel, port));

	port = &dev1->ports[7];
	KUNIT_EXPECT_FALSE(test, tb_tunnel_port_on_path(dp_tunnel, port));

	port = &dev3->ports[1];
	KUNIT_EXPECT_TRUE(test, tb_tunnel_port_on_path(dp_tunnel, port));

	port = &dev5->ports[1];
	KUNIT_EXPECT_TRUE(test, tb_tunnel_port_on_path(dp_tunnel, port));

	port = &dev4->ports[1];
	KUNIT_EXPECT_FALSE(test, tb_tunnel_port_on_path(dp_tunnel, port));

	tb_tunnel_मुक्त(dp_tunnel);
पूर्ण

अटल व्योम tb_test_tunnel_dma(काष्ठा kunit *test)
अणु
	काष्ठा tb_port *nhi, *port;
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_चयन *host;

	/*
	 * Create DMA tunnel from NHI to port 1 and back.
	 *
	 *   [Host 1]
	 *    1 ^ In HopID 1 -> Out HopID 8
	 *      |
	 *      v In HopID 8 -> Out HopID 1
	 * ............ Doमुख्य border
	 *      |
	 *   [Host 2]
	 */
	host = alloc_host(test);
	nhi = &host->ports[7];
	port = &host->ports[1];

	tunnel = tb_tunnel_alloc_dma(शून्य, nhi, port, 8, 1, 8, 1);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_DMA);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->src_port, nhi);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->dst_port, port);
	KUNIT_ASSERT_EQ(test, tunnel->npaths, (माप_प्रकार)2);
	/* RX path */
	KUNIT_ASSERT_EQ(test, tunnel->paths[0]->path_length, 1);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].in_port, port);
	KUNIT_EXPECT_EQ(test, tunnel->paths[0]->hops[0].in_hop_index, 8);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].out_port, nhi);
	KUNIT_EXPECT_EQ(test, tunnel->paths[0]->hops[0].next_hop_index, 1);
	/* TX path */
	KUNIT_ASSERT_EQ(test, tunnel->paths[1]->path_length, 1);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[0].in_port, nhi);
	KUNIT_EXPECT_EQ(test, tunnel->paths[1]->hops[0].in_hop_index, 1);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[0].out_port, port);
	KUNIT_EXPECT_EQ(test, tunnel->paths[1]->hops[0].next_hop_index, 8);

	tb_tunnel_मुक्त(tunnel);
पूर्ण

अटल व्योम tb_test_tunnel_dma_rx(काष्ठा kunit *test)
अणु
	काष्ठा tb_port *nhi, *port;
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_चयन *host;

	/*
	 * Create DMA RX tunnel from port 1 to NHI.
	 *
	 *   [Host 1]
	 *    1 ^
	 *      |
	 *      | In HopID 15 -> Out HopID 2
	 * ............ Doमुख्य border
	 *      |
	 *   [Host 2]
	 */
	host = alloc_host(test);
	nhi = &host->ports[7];
	port = &host->ports[1];

	tunnel = tb_tunnel_alloc_dma(शून्य, nhi, port, -1, -1, 15, 2);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_DMA);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->src_port, nhi);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->dst_port, port);
	KUNIT_ASSERT_EQ(test, tunnel->npaths, (माप_प्रकार)1);
	/* RX path */
	KUNIT_ASSERT_EQ(test, tunnel->paths[0]->path_length, 1);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].in_port, port);
	KUNIT_EXPECT_EQ(test, tunnel->paths[0]->hops[0].in_hop_index, 15);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].out_port, nhi);
	KUNIT_EXPECT_EQ(test, tunnel->paths[0]->hops[0].next_hop_index, 2);

	tb_tunnel_मुक्त(tunnel);
पूर्ण

अटल व्योम tb_test_tunnel_dma_tx(काष्ठा kunit *test)
अणु
	काष्ठा tb_port *nhi, *port;
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_चयन *host;

	/*
	 * Create DMA TX tunnel from NHI to port 1.
	 *
	 *   [Host 1]
	 *    1 | In HopID 2 -> Out HopID 15
	 *      |
	 *      v
	 * ............ Doमुख्य border
	 *      |
	 *   [Host 2]
	 */
	host = alloc_host(test);
	nhi = &host->ports[7];
	port = &host->ports[1];

	tunnel = tb_tunnel_alloc_dma(शून्य, nhi, port, 15, 2, -1, -1);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_DMA);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->src_port, nhi);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->dst_port, port);
	KUNIT_ASSERT_EQ(test, tunnel->npaths, (माप_प्रकार)1);
	/* TX path */
	KUNIT_ASSERT_EQ(test, tunnel->paths[0]->path_length, 1);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].in_port, nhi);
	KUNIT_EXPECT_EQ(test, tunnel->paths[0]->hops[0].in_hop_index, 2);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].out_port, port);
	KUNIT_EXPECT_EQ(test, tunnel->paths[0]->hops[0].next_hop_index, 15);

	tb_tunnel_मुक्त(tunnel);
पूर्ण

अटल व्योम tb_test_tunnel_dma_chain(काष्ठा kunit *test)
अणु
	काष्ठा tb_चयन *host, *dev1, *dev2;
	काष्ठा tb_port *nhi, *port;
	काष्ठा tb_tunnel *tunnel;

	/*
	 * Create DMA tunnel from NHI to Device #2 port 3 and back.
	 *
	 *   [Host 1]
	 *    1 ^ In HopID 1 -> Out HopID x
	 *      |
	 *    1 | In HopID x -> Out HopID 1
	 *  [Device #1]
	 *         7 \
	 *          1 \
	 *         [Device #2]
	 *           3 | In HopID x -> Out HopID 8
	 *             |
	 *             v In HopID 8 -> Out HopID x
	 * ............ Doमुख्य border
	 *             |
	 *          [Host 2]
	 */
	host = alloc_host(test);
	dev1 = alloc_dev_शेष(test, host, 0x1, true);
	dev2 = alloc_dev_शेष(test, dev1, 0x701, true);

	nhi = &host->ports[7];
	port = &dev2->ports[3];
	tunnel = tb_tunnel_alloc_dma(शून्य, nhi, port, 8, 1, 8, 1);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);
	KUNIT_EXPECT_EQ(test, tunnel->type, (क्रमागत tb_tunnel_type)TB_TUNNEL_DMA);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->src_port, nhi);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->dst_port, port);
	KUNIT_ASSERT_EQ(test, tunnel->npaths, (माप_प्रकार)2);
	/* RX path */
	KUNIT_ASSERT_EQ(test, tunnel->paths[0]->path_length, 3);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].in_port, port);
	KUNIT_EXPECT_EQ(test, tunnel->paths[0]->hops[0].in_hop_index, 8);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[0].out_port,
			    &dev2->ports[1]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[1].in_port,
			    &dev1->ports[7]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[1].out_port,
			    &dev1->ports[1]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[2].in_port,
			    &host->ports[1]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[0]->hops[2].out_port, nhi);
	KUNIT_EXPECT_EQ(test, tunnel->paths[0]->hops[2].next_hop_index, 1);
	/* TX path */
	KUNIT_ASSERT_EQ(test, tunnel->paths[1]->path_length, 3);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[0].in_port, nhi);
	KUNIT_EXPECT_EQ(test, tunnel->paths[1]->hops[0].in_hop_index, 1);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[1].in_port,
			    &dev1->ports[1]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[1].out_port,
			    &dev1->ports[7]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[2].in_port,
			    &dev2->ports[1]);
	KUNIT_EXPECT_PTR_EQ(test, tunnel->paths[1]->hops[2].out_port, port);
	KUNIT_EXPECT_EQ(test, tunnel->paths[1]->hops[2].next_hop_index, 8);

	tb_tunnel_मुक्त(tunnel);
पूर्ण

अटल व्योम tb_test_tunnel_dma_match(काष्ठा kunit *test)
अणु
	काष्ठा tb_port *nhi, *port;
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_चयन *host;

	host = alloc_host(test);
	nhi = &host->ports[7];
	port = &host->ports[1];

	tunnel = tb_tunnel_alloc_dma(शून्य, nhi, port, 15, 1, 15, 1);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);

	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, 15, 1, 15, 1));
	KUNIT_ASSERT_FALSE(test, tb_tunnel_match_dma(tunnel, 8, 1, 15, 1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, -1, 15, 1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, 15, 1, -1, -1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, 15, -1, -1, -1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, 1, -1, -1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, -1, 15, -1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, -1, -1, 1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, -1, -1, -1));
	KUNIT_ASSERT_FALSE(test, tb_tunnel_match_dma(tunnel, 8, -1, 8, -1));

	tb_tunnel_मुक्त(tunnel);

	tunnel = tb_tunnel_alloc_dma(शून्य, nhi, port, 15, 1, -1, -1);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, 15, 1, -1, -1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, 15, -1, -1, -1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, 1, -1, -1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, -1, -1, -1));
	KUNIT_ASSERT_FALSE(test, tb_tunnel_match_dma(tunnel, 15, 1, 15, 1));
	KUNIT_ASSERT_FALSE(test, tb_tunnel_match_dma(tunnel, -1, -1, 15, 1));
	KUNIT_ASSERT_FALSE(test, tb_tunnel_match_dma(tunnel, 15, 11, -1, -1));

	tb_tunnel_मुक्त(tunnel);

	tunnel = tb_tunnel_alloc_dma(शून्य, nhi, port, -1, -1, 15, 11);
	KUNIT_ASSERT_TRUE(test, tunnel != शून्य);
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, -1, 15, 11));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, -1, 15, -1));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, -1, -1, 11));
	KUNIT_ASSERT_TRUE(test, tb_tunnel_match_dma(tunnel, -1, -1, -1, -1));
	KUNIT_ASSERT_FALSE(test, tb_tunnel_match_dma(tunnel, -1, -1, 15, 1));
	KUNIT_ASSERT_FALSE(test, tb_tunnel_match_dma(tunnel, -1, -1, 10, 11));
	KUNIT_ASSERT_FALSE(test, tb_tunnel_match_dma(tunnel, 15, 11, -1, -1));

	tb_tunnel_मुक्त(tunnel);
पूर्ण

अटल स्थिर u32 root_directory[] = अणु
	0x55584401,	/* "UXD" v1 */
	0x00000018,	/* Root directory length */
	0x76656e64,	/* "vend" */
	0x6f726964,	/* "orid" */
	0x76000001,	/* "v" R 1 */
	0x00000a27,	/* Immediate value, ! Venकरोr ID */
	0x76656e64,	/* "vend" */
	0x6f726964,	/* "orid" */
	0x74000003,	/* "t" R 3 */
	0x0000001a,	/* Text leaf offset, (ै Apple Inc.ै ) */
	0x64657669,	/* "devi" */
	0x63656964,	/* "ceid" */
	0x76000001,	/* "v" R 1 */
	0x0000000a,	/* Immediate value, ! Device ID */
	0x64657669,	/* "devi" */
	0x63656964,	/* "ceid" */
	0x74000003,	/* "t" R 3 */
	0x0000001d,	/* Text leaf offset, (ै Macपूर्णांकoshै ) */
	0x64657669,	/* "devi" */
	0x63657276,	/* "cerv" */
	0x76000001,	/* "v" R 1 */
	0x80000100,	/* Immediate value, Device Revision */
	0x6e657477,	/* "netw" */
	0x6f726b00,	/* "ork" */
	0x44000014,	/* "D" R 20 */
	0x00000021,	/* Directory data offset, (Network Directory) */
	0x4170706c,	/* "Appl" */
	0x6520496e,	/* "e In" */
	0x632e0000,	/* "c." ! */
	0x4d616369,	/* "Maci" */
	0x6e746f73,	/* "ntos" */
	0x68000000,	/* "h" */
	0x00000000,	/* padding */
	0xca8961c6,	/* Directory UUID, Network Directory */
	0x9541ce1c,	/* Directory UUID, Network Directory */
	0x5949b8bd,	/* Directory UUID, Network Directory */
	0x4f5a5f2e,	/* Directory UUID, Network Directory */
	0x70727463,	/* "prtc" */
	0x69640000,	/* "id" */
	0x76000001,	/* "v" R 1 */
	0x00000001,	/* Immediate value, Network Protocol ID */
	0x70727463,	/* "prtc" */
	0x76657273,	/* "vers" */
	0x76000001,	/* "v" R 1 */
	0x00000001,	/* Immediate value, Network Protocol Version */
	0x70727463,	/* "prtc" */
	0x72657673,	/* "revs" */
	0x76000001,	/* "v" R 1 */
	0x00000001,	/* Immediate value, Network Protocol Revision */
	0x70727463,	/* "prtc" */
	0x73746e73,	/* "stns" */
	0x76000001,	/* "v" R 1 */
	0x00000000,	/* Immediate value, Network Protocol Settings */
पूर्ण;

अटल स्थिर uuid_t network_dir_uuid =
	UUID_INIT(0xc66189ca, 0x1cce, 0x4195,
		  0xbd, 0xb8, 0x49, 0x59, 0x2e, 0x5f, 0x5a, 0x4f);

अटल व्योम tb_test_property_parse(काष्ठा kunit *test)
अणु
	काष्ठा tb_property_dir *dir, *network_dir;
	काष्ठा tb_property *p;

	dir = tb_property_parse_dir(root_directory, ARRAY_SIZE(root_directory));
	KUNIT_ASSERT_TRUE(test, dir != शून्य);

	p = tb_property_find(dir, "foo", TB_PROPERTY_TYPE_TEXT);
	KUNIT_ASSERT_TRUE(test, !p);

	p = tb_property_find(dir, "vendorid", TB_PROPERTY_TYPE_TEXT);
	KUNIT_ASSERT_TRUE(test, p != शून्य);
	KUNIT_EXPECT_STREQ(test, p->value.text, "Apple Inc.");

	p = tb_property_find(dir, "vendorid", TB_PROPERTY_TYPE_VALUE);
	KUNIT_ASSERT_TRUE(test, p != शून्य);
	KUNIT_EXPECT_EQ(test, p->value.immediate, (u32)0xa27);

	p = tb_property_find(dir, "deviceid", TB_PROPERTY_TYPE_TEXT);
	KUNIT_ASSERT_TRUE(test, p != शून्य);
	KUNIT_EXPECT_STREQ(test, p->value.text, "Macintosh");

	p = tb_property_find(dir, "deviceid", TB_PROPERTY_TYPE_VALUE);
	KUNIT_ASSERT_TRUE(test, p != शून्य);
	KUNIT_EXPECT_EQ(test, p->value.immediate, (u32)0xa);

	p = tb_property_find(dir, "missing", TB_PROPERTY_TYPE_सूचीECTORY);
	KUNIT_ASSERT_TRUE(test, !p);

	p = tb_property_find(dir, "network", TB_PROPERTY_TYPE_सूचीECTORY);
	KUNIT_ASSERT_TRUE(test, p != शून्य);

	network_dir = p->value.dir;
	KUNIT_EXPECT_TRUE(test, uuid_equal(network_dir->uuid, &network_dir_uuid));

	p = tb_property_find(network_dir, "prtcid", TB_PROPERTY_TYPE_VALUE);
	KUNIT_ASSERT_TRUE(test, p != शून्य);
	KUNIT_EXPECT_EQ(test, p->value.immediate, (u32)0x1);

	p = tb_property_find(network_dir, "prtcvers", TB_PROPERTY_TYPE_VALUE);
	KUNIT_ASSERT_TRUE(test, p != शून्य);
	KUNIT_EXPECT_EQ(test, p->value.immediate, (u32)0x1);

	p = tb_property_find(network_dir, "prtcrevs", TB_PROPERTY_TYPE_VALUE);
	KUNIT_ASSERT_TRUE(test, p != शून्य);
	KUNIT_EXPECT_EQ(test, p->value.immediate, (u32)0x1);

	p = tb_property_find(network_dir, "prtcstns", TB_PROPERTY_TYPE_VALUE);
	KUNIT_ASSERT_TRUE(test, p != शून्य);
	KUNIT_EXPECT_EQ(test, p->value.immediate, (u32)0x0);

	p = tb_property_find(network_dir, "deviceid", TB_PROPERTY_TYPE_VALUE);
	KUNIT_EXPECT_TRUE(test, !p);
	p = tb_property_find(network_dir, "deviceid", TB_PROPERTY_TYPE_TEXT);
	KUNIT_EXPECT_TRUE(test, !p);

	tb_property_मुक्त_dir(dir);
पूर्ण

अटल व्योम tb_test_property_क्रमmat(काष्ठा kunit *test)
अणु
	काष्ठा tb_property_dir *dir;
	sमाप_प्रकार block_len;
	u32 *block;
	पूर्णांक ret, i;

	dir = tb_property_parse_dir(root_directory, ARRAY_SIZE(root_directory));
	KUNIT_ASSERT_TRUE(test, dir != शून्य);

	ret = tb_property_क्रमmat_dir(dir, शून्य, 0);
	KUNIT_ASSERT_EQ(test, ret, (पूर्णांक)ARRAY_SIZE(root_directory));

	block_len = ret;

	block = kunit_kzalloc(test, block_len * माप(u32), GFP_KERNEL);
	KUNIT_ASSERT_TRUE(test, block != शून्य);

	ret = tb_property_क्रमmat_dir(dir, block, block_len);
	KUNIT_EXPECT_EQ(test, ret, 0);

	क्रम (i = 0; i < ARRAY_SIZE(root_directory); i++)
		KUNIT_EXPECT_EQ(test, root_directory[i], block[i]);

	tb_property_मुक्त_dir(dir);
पूर्ण

अटल व्योम compare_dirs(काष्ठा kunit *test, काष्ठा tb_property_dir *d1,
			 काष्ठा tb_property_dir *d2)
अणु
	काष्ठा tb_property *p1, *p2, *पंचांगp;
	पूर्णांक n1, n2, i;

	अगर (d1->uuid) अणु
		KUNIT_ASSERT_TRUE(test, d2->uuid != शून्य);
		KUNIT_ASSERT_TRUE(test, uuid_equal(d1->uuid, d2->uuid));
	पूर्ण अन्यथा अणु
		KUNIT_ASSERT_TRUE(test, d2->uuid == शून्य);
	पूर्ण

	n1 = 0;
	tb_property_क्रम_each(d1, पंचांगp)
		n1++;
	KUNIT_ASSERT_NE(test, n1, 0);

	n2 = 0;
	tb_property_क्रम_each(d2, पंचांगp)
		n2++;
	KUNIT_ASSERT_NE(test, n2, 0);

	KUNIT_ASSERT_EQ(test, n1, n2);

	p1 = शून्य;
	p2 = शून्य;
	क्रम (i = 0; i < n1; i++) अणु
		p1 = tb_property_get_next(d1, p1);
		KUNIT_ASSERT_TRUE(test, p1 != शून्य);
		p2 = tb_property_get_next(d2, p2);
		KUNIT_ASSERT_TRUE(test, p2 != शून्य);

		KUNIT_ASSERT_STREQ(test, &p1->key[0], &p2->key[0]);
		KUNIT_ASSERT_EQ(test, p1->type, p2->type);
		KUNIT_ASSERT_EQ(test, p1->length, p2->length);

		चयन (p1->type) अणु
		हाल TB_PROPERTY_TYPE_सूचीECTORY:
			KUNIT_ASSERT_TRUE(test, p1->value.dir != शून्य);
			KUNIT_ASSERT_TRUE(test, p2->value.dir != शून्य);
			compare_dirs(test, p1->value.dir, p2->value.dir);
			अवरोध;

		हाल TB_PROPERTY_TYPE_DATA:
			KUNIT_ASSERT_TRUE(test, p1->value.data != शून्य);
			KUNIT_ASSERT_TRUE(test, p2->value.data != शून्य);
			KUNIT_ASSERT_TRUE(test,
				!स_भेद(p1->value.data, p2->value.data,
					p1->length * 4)
			);
			अवरोध;

		हाल TB_PROPERTY_TYPE_TEXT:
			KUNIT_ASSERT_TRUE(test, p1->value.text != शून्य);
			KUNIT_ASSERT_TRUE(test, p2->value.text != शून्य);
			KUNIT_ASSERT_STREQ(test, p1->value.text, p2->value.text);
			अवरोध;

		हाल TB_PROPERTY_TYPE_VALUE:
			KUNIT_ASSERT_EQ(test, p1->value.immediate,
					p2->value.immediate);
			अवरोध;
		शेष:
			KUNIT_FAIL(test, "unexpected property type");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tb_test_property_copy(काष्ठा kunit *test)
अणु
	काष्ठा tb_property_dir *src, *dst;
	u32 *block;
	पूर्णांक ret, i;

	src = tb_property_parse_dir(root_directory, ARRAY_SIZE(root_directory));
	KUNIT_ASSERT_TRUE(test, src != शून्य);

	dst = tb_property_copy_dir(src);
	KUNIT_ASSERT_TRUE(test, dst != शून्य);

	/* Compare the काष्ठाures */
	compare_dirs(test, src, dst);

	/* Compare the resulting property block */
	ret = tb_property_क्रमmat_dir(dst, शून्य, 0);
	KUNIT_ASSERT_EQ(test, ret, (पूर्णांक)ARRAY_SIZE(root_directory));

	block = kunit_kzalloc(test, माप(root_directory), GFP_KERNEL);
	KUNIT_ASSERT_TRUE(test, block != शून्य);

	ret = tb_property_क्रमmat_dir(dst, block, ARRAY_SIZE(root_directory));
	KUNIT_EXPECT_TRUE(test, !ret);

	क्रम (i = 0; i < ARRAY_SIZE(root_directory); i++)
		KUNIT_EXPECT_EQ(test, root_directory[i], block[i]);

	tb_property_मुक्त_dir(dst);
	tb_property_मुक्त_dir(src);
पूर्ण

अटल काष्ठा kunit_हाल tb_test_हालs[] = अणु
	KUNIT_CASE(tb_test_path_basic),
	KUNIT_CASE(tb_test_path_not_connected_walk),
	KUNIT_CASE(tb_test_path_single_hop_walk),
	KUNIT_CASE(tb_test_path_daisy_chain_walk),
	KUNIT_CASE(tb_test_path_simple_tree_walk),
	KUNIT_CASE(tb_test_path_complex_tree_walk),
	KUNIT_CASE(tb_test_path_max_length_walk),
	KUNIT_CASE(tb_test_path_not_connected),
	KUNIT_CASE(tb_test_path_not_bonded_lane0),
	KUNIT_CASE(tb_test_path_not_bonded_lane1),
	KUNIT_CASE(tb_test_path_not_bonded_lane1_chain),
	KUNIT_CASE(tb_test_path_not_bonded_lane1_chain_reverse),
	KUNIT_CASE(tb_test_path_mixed_chain),
	KUNIT_CASE(tb_test_path_mixed_chain_reverse),
	KUNIT_CASE(tb_test_tunnel_pcie),
	KUNIT_CASE(tb_test_tunnel_dp),
	KUNIT_CASE(tb_test_tunnel_dp_chain),
	KUNIT_CASE(tb_test_tunnel_dp_tree),
	KUNIT_CASE(tb_test_tunnel_dp_max_length),
	KUNIT_CASE(tb_test_tunnel_port_on_path),
	KUNIT_CASE(tb_test_tunnel_usb3),
	KUNIT_CASE(tb_test_tunnel_dma),
	KUNIT_CASE(tb_test_tunnel_dma_rx),
	KUNIT_CASE(tb_test_tunnel_dma_tx),
	KUNIT_CASE(tb_test_tunnel_dma_chain),
	KUNIT_CASE(tb_test_tunnel_dma_match),
	KUNIT_CASE(tb_test_property_parse),
	KUNIT_CASE(tb_test_property_क्रमmat),
	KUNIT_CASE(tb_test_property_copy),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा kunit_suite tb_test_suite = अणु
	.name = "thunderbolt",
	.test_हालs = tb_test_हालs,
पूर्ण;

अटल काष्ठा kunit_suite *tb_test_suites[] = अणु &tb_test_suite, शून्य पूर्ण;

पूर्णांक tb_test_init(व्योम)
अणु
	वापस __kunit_test_suites_init(tb_test_suites);
पूर्ण

व्योम tb_test_निकास(व्योम)
अणु
	वापस __kunit_test_suites_निकास(tb_test_suites);
पूर्ण
