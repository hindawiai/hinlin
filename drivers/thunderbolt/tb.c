<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt driver - bus logic (NHI independent)
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2019, Intel Corporation
 */

#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "tb.h"
#समावेश "tb_regs.h"
#समावेश "tunnel.h"

#घोषणा TB_TIMEOUT	100 /* ms */

/**
 * काष्ठा tb_cm - Simple Thunderbolt connection manager
 * @tunnel_list: List of active tunnels
 * @dp_resources: List of available DP resources क्रम DP tunneling
 * @hotplug_active: tb_handle_hotplug will stop progressing plug
 *		    events and निकास अगर this is not set (it needs to
 *		    acquire the lock one more समय). Used to drain wq
 *		    after cfg has been छोड़ोd.
 * @हटाओ_work: Work used to हटाओ any unplugged routers after
 *		 runसमय resume
 */
काष्ठा tb_cm अणु
	काष्ठा list_head tunnel_list;
	काष्ठा list_head dp_resources;
	bool hotplug_active;
	काष्ठा delayed_work हटाओ_work;
पूर्ण;

अटल अंतरभूत काष्ठा tb *tcm_to_tb(काष्ठा tb_cm *tcm)
अणु
	वापस ((व्योम *)tcm - माप(काष्ठा tb));
पूर्ण

काष्ठा tb_hotplug_event अणु
	काष्ठा work_काष्ठा work;
	काष्ठा tb *tb;
	u64 route;
	u8 port;
	bool unplug;
पूर्ण;

अटल व्योम tb_handle_hotplug(काष्ठा work_काष्ठा *work);

अटल व्योम tb_queue_hotplug(काष्ठा tb *tb, u64 route, u8 port, bool unplug)
अणु
	काष्ठा tb_hotplug_event *ev;

	ev = kदो_स्मृति(माप(*ev), GFP_KERNEL);
	अगर (!ev)
		वापस;

	ev->tb = tb;
	ev->route = route;
	ev->port = port;
	ev->unplug = unplug;
	INIT_WORK(&ev->work, tb_handle_hotplug);
	queue_work(tb->wq, &ev->work);
पूर्ण

/* क्रमागतeration & hot plug handling */

अटल व्योम tb_add_dp_resources(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_cm *tcm = tb_priv(sw->tb);
	काष्ठा tb_port *port;

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (!tb_port_is_dpin(port))
			जारी;

		अगर (!tb_चयन_query_dp_resource(sw, port))
			जारी;

		list_add_tail(&port->list, &tcm->dp_resources);
		tb_port_dbg(port, "DP IN resource available\n");
	पूर्ण
पूर्ण

अटल व्योम tb_हटाओ_dp_resources(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_cm *tcm = tb_priv(sw->tb);
	काष्ठा tb_port *port, *पंचांगp;

	/* Clear children resources first */
	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (tb_port_has_remote(port))
			tb_हटाओ_dp_resources(port->remote->sw);
	पूर्ण

	list_क्रम_each_entry_safe(port, पंचांगp, &tcm->dp_resources, list) अणु
		अगर (port->sw == sw) अणु
			tb_port_dbg(port, "DP OUT resource unavailable\n");
			list_del_init(&port->list);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tb_discover_tunnels(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb *tb = sw->tb;
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_port *port;

	tb_चयन_क्रम_each_port(sw, port) अणु
		काष्ठा tb_tunnel *tunnel = शून्य;

		चयन (port->config.type) अणु
		हाल TB_TYPE_DP_HDMI_IN:
			tunnel = tb_tunnel_discover_dp(tb, port);
			अवरोध;

		हाल TB_TYPE_PCIE_DOWN:
			tunnel = tb_tunnel_discover_pci(tb, port);
			अवरोध;

		हाल TB_TYPE_USB3_DOWN:
			tunnel = tb_tunnel_discover_usb3(tb, port);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अगर (!tunnel)
			जारी;

		अगर (tb_tunnel_is_pci(tunnel)) अणु
			काष्ठा tb_चयन *parent = tunnel->dst_port->sw;

			जबतक (parent != tunnel->src_port->sw) अणु
				parent->boot = true;
				parent = tb_चयन_parent(parent);
			पूर्ण
		पूर्ण अन्यथा अगर (tb_tunnel_is_dp(tunnel)) अणु
			/* Keep the करोमुख्य from घातering करोwn */
			pm_runसमय_get_sync(&tunnel->src_port->sw->dev);
			pm_runसमय_get_sync(&tunnel->dst_port->sw->dev);
		पूर्ण

		list_add_tail(&tunnel->list, &tcm->tunnel_list);
	पूर्ण

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (tb_port_has_remote(port))
			tb_discover_tunnels(port->remote->sw);
	पूर्ण
पूर्ण

अटल पूर्णांक tb_port_configure_xकरोमुख्य(काष्ठा tb_port *port)
अणु
	/*
	 * XDoमुख्य paths currently only support single lane so we must
	 * disable the other lane according to USB4 spec.
	 */
	tb_port_disable(port->dual_link_port);

	अगर (tb_चयन_is_usb4(port->sw))
		वापस usb4_port_configure_xकरोमुख्य(port);
	वापस tb_lc_configure_xकरोमुख्य(port);
पूर्ण

अटल व्योम tb_port_unconfigure_xकरोमुख्य(काष्ठा tb_port *port)
अणु
	अगर (tb_चयन_is_usb4(port->sw))
		usb4_port_unconfigure_xकरोमुख्य(port);
	अन्यथा
		tb_lc_unconfigure_xकरोमुख्य(port);

	tb_port_enable(port->dual_link_port);
पूर्ण

अटल व्योम tb_scan_xकरोमुख्य(काष्ठा tb_port *port)
अणु
	काष्ठा tb_चयन *sw = port->sw;
	काष्ठा tb *tb = sw->tb;
	काष्ठा tb_xकरोमुख्य *xd;
	u64 route;

	अगर (!tb_is_xकरोमुख्य_enabled())
		वापस;

	route = tb_करोwnstream_route(port);
	xd = tb_xकरोमुख्य_find_by_route(tb, route);
	अगर (xd) अणु
		tb_xकरोमुख्य_put(xd);
		वापस;
	पूर्ण

	xd = tb_xकरोमुख्य_alloc(tb, &sw->dev, route, tb->root_चयन->uuid,
			      शून्य);
	अगर (xd) अणु
		tb_port_at(route, sw)->xकरोमुख्य = xd;
		tb_port_configure_xकरोमुख्य(port);
		tb_xकरोमुख्य_add(xd);
	पूर्ण
पूर्ण

अटल पूर्णांक tb_enable_पंचांगu(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक ret;

	/* If it is alपढ़ोy enabled in correct mode, करोn't touch it */
	अगर (tb_चयन_पंचांगu_is_enabled(sw))
		वापस 0;

	ret = tb_चयन_पंचांगu_disable(sw);
	अगर (ret)
		वापस ret;

	ret = tb_चयन_पंचांगu_post_समय(sw);
	अगर (ret)
		वापस ret;

	वापस tb_चयन_पंचांगu_enable(sw);
पूर्ण

/**
 * tb_find_unused_port() - वापस the first inactive port on @sw
 * @sw: Switch to find the port on
 * @type: Port type to look क्रम
 */
अटल काष्ठा tb_port *tb_find_unused_port(काष्ठा tb_चयन *sw,
					   क्रमागत tb_port_type type)
अणु
	काष्ठा tb_port *port;

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (tb_is_upstream_port(port))
			जारी;
		अगर (port->config.type != type)
			जारी;
		अगर (!port->cap_adap)
			जारी;
		अगर (tb_port_is_enabled(port))
			जारी;
		वापस port;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा tb_port *tb_find_usb3_करोwn(काष्ठा tb_चयन *sw,
					 स्थिर काष्ठा tb_port *port)
अणु
	काष्ठा tb_port *करोwn;

	करोwn = usb4_चयन_map_usb3_करोwn(sw, port);
	अगर (करोwn && !tb_usb3_port_is_enabled(करोwn))
		वापस करोwn;
	वापस शून्य;
पूर्ण

अटल काष्ठा tb_tunnel *tb_find_tunnel(काष्ठा tb *tb, क्रमागत tb_tunnel_type type,
					काष्ठा tb_port *src_port,
					काष्ठा tb_port *dst_port)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_tunnel *tunnel;

	list_क्रम_each_entry(tunnel, &tcm->tunnel_list, list) अणु
		अगर (tunnel->type == type &&
		    ((src_port && src_port == tunnel->src_port) ||
		     (dst_port && dst_port == tunnel->dst_port))) अणु
			वापस tunnel;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा tb_tunnel *tb_find_first_usb3_tunnel(काष्ठा tb *tb,
						   काष्ठा tb_port *src_port,
						   काष्ठा tb_port *dst_port)
अणु
	काष्ठा tb_port *port, *usb3_करोwn;
	काष्ठा tb_चयन *sw;

	/* Pick the router that is deepest in the topology */
	अगर (dst_port->sw->config.depth > src_port->sw->config.depth)
		sw = dst_port->sw;
	अन्यथा
		sw = src_port->sw;

	/* Can't be the host router */
	अगर (sw == tb->root_चयन)
		वापस शून्य;

	/* Find the करोwnstream USB4 port that leads to this router */
	port = tb_port_at(tb_route(sw), tb->root_चयन);
	/* Find the corresponding host router USB3 करोwnstream port */
	usb3_करोwn = usb4_चयन_map_usb3_करोwn(tb->root_चयन, port);
	अगर (!usb3_करोwn)
		वापस शून्य;

	वापस tb_find_tunnel(tb, TB_TUNNEL_USB3, usb3_करोwn, शून्य);
पूर्ण

अटल पूर्णांक tb_available_bandwidth(काष्ठा tb *tb, काष्ठा tb_port *src_port,
	काष्ठा tb_port *dst_port, पूर्णांक *available_up, पूर्णांक *available_करोwn)
अणु
	पूर्णांक usb3_consumed_up, usb3_consumed_करोwn, ret;
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_port *port;

	tb_port_dbg(dst_port, "calculating available bandwidth\n");

	tunnel = tb_find_first_usb3_tunnel(tb, src_port, dst_port);
	अगर (tunnel) अणु
		ret = tb_tunnel_consumed_bandwidth(tunnel, &usb3_consumed_up,
						   &usb3_consumed_करोwn);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		usb3_consumed_up = 0;
		usb3_consumed_करोwn = 0;
	पूर्ण

	*available_up = *available_करोwn = 40000;

	/* Find the minimum available bandwidth over all links */
	tb_क्रम_each_port_on_path(src_port, dst_port, port) अणु
		पूर्णांक link_speed, link_width, up_bw, करोwn_bw;

		अगर (!tb_port_is_null(port))
			जारी;

		अगर (tb_is_upstream_port(port)) अणु
			link_speed = port->sw->link_speed;
		पूर्ण अन्यथा अणु
			link_speed = tb_port_get_link_speed(port);
			अगर (link_speed < 0)
				वापस link_speed;
		पूर्ण

		link_width = port->bonded ? 2 : 1;

		up_bw = link_speed * link_width * 1000; /* Mb/s */
		/* Leave 10% guard band */
		up_bw -= up_bw / 10;
		करोwn_bw = up_bw;

		tb_port_dbg(port, "link total bandwidth %d Mb/s\n", up_bw);

		/*
		 * Find all DP tunnels that cross the port and reduce
		 * their consumed bandwidth from the available.
		 */
		list_क्रम_each_entry(tunnel, &tcm->tunnel_list, list) अणु
			पूर्णांक dp_consumed_up, dp_consumed_करोwn;

			अगर (!tb_tunnel_is_dp(tunnel))
				जारी;

			अगर (!tb_tunnel_port_on_path(tunnel, port))
				जारी;

			ret = tb_tunnel_consumed_bandwidth(tunnel,
							   &dp_consumed_up,
							   &dp_consumed_करोwn);
			अगर (ret)
				वापस ret;

			up_bw -= dp_consumed_up;
			करोwn_bw -= dp_consumed_करोwn;
		पूर्ण

		/*
		 * If USB3 is tunneled from the host router करोwn to the
		 * branch leading to port we need to take USB3 consumed
		 * bandwidth पूर्णांकo account regardless whether it actually
		 * crosses the port.
		 */
		up_bw -= usb3_consumed_up;
		करोwn_bw -= usb3_consumed_करोwn;

		अगर (up_bw < *available_up)
			*available_up = up_bw;
		अगर (करोwn_bw < *available_करोwn)
			*available_करोwn = करोwn_bw;
	पूर्ण

	अगर (*available_up < 0)
		*available_up = 0;
	अगर (*available_करोwn < 0)
		*available_करोwn = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक tb_release_unused_usb3_bandwidth(काष्ठा tb *tb,
					    काष्ठा tb_port *src_port,
					    काष्ठा tb_port *dst_port)
अणु
	काष्ठा tb_tunnel *tunnel;

	tunnel = tb_find_first_usb3_tunnel(tb, src_port, dst_port);
	वापस tunnel ? tb_tunnel_release_unused_bandwidth(tunnel) : 0;
पूर्ण

अटल व्योम tb_reclaim_usb3_bandwidth(काष्ठा tb *tb, काष्ठा tb_port *src_port,
				      काष्ठा tb_port *dst_port)
अणु
	पूर्णांक ret, available_up, available_करोwn;
	काष्ठा tb_tunnel *tunnel;

	tunnel = tb_find_first_usb3_tunnel(tb, src_port, dst_port);
	अगर (!tunnel)
		वापस;

	tb_dbg(tb, "reclaiming unused bandwidth for USB3\n");

	/*
	 * Calculate available bandwidth क्रम the first hop USB3 tunnel.
	 * That determines the whole USB3 bandwidth क्रम this branch.
	 */
	ret = tb_available_bandwidth(tb, tunnel->src_port, tunnel->dst_port,
				     &available_up, &available_करोwn);
	अगर (ret) अणु
		tb_warn(tb, "failed to calculate available bandwidth\n");
		वापस;
	पूर्ण

	tb_dbg(tb, "available bandwidth for USB3 %d/%d Mb/s\n",
	       available_up, available_करोwn);

	tb_tunnel_reclaim_available_bandwidth(tunnel, &available_up, &available_करोwn);
पूर्ण

अटल पूर्णांक tb_tunnel_usb3(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_चयन *parent = tb_चयन_parent(sw);
	पूर्णांक ret, available_up, available_करोwn;
	काष्ठा tb_port *up, *करोwn, *port;
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_tunnel *tunnel;

	अगर (!tb_acpi_may_tunnel_usb3()) अणु
		tb_dbg(tb, "USB3 tunneling disabled, not creating tunnel\n");
		वापस 0;
	पूर्ण

	up = tb_चयन_find_port(sw, TB_TYPE_USB3_UP);
	अगर (!up)
		वापस 0;

	अगर (!sw->link_usb4)
		वापस 0;

	/*
	 * Look up available करोwn port. Since we are chaining it should
	 * be found right above this चयन.
	 */
	port = tb_port_at(tb_route(sw), parent);
	करोwn = tb_find_usb3_करोwn(parent, port);
	अगर (!करोwn)
		वापस 0;

	अगर (tb_route(parent)) अणु
		काष्ठा tb_port *parent_up;
		/*
		 * Check first that the parent चयन has its upstream USB3
		 * port enabled. Otherwise the chain is not complete and
		 * there is no poपूर्णांक setting up a new tunnel.
		 */
		parent_up = tb_चयन_find_port(parent, TB_TYPE_USB3_UP);
		अगर (!parent_up || !tb_port_is_enabled(parent_up))
			वापस 0;

		/* Make all unused bandwidth available क्रम the new tunnel */
		ret = tb_release_unused_usb3_bandwidth(tb, करोwn, up);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = tb_available_bandwidth(tb, करोwn, up, &available_up,
				     &available_करोwn);
	अगर (ret)
		जाओ err_reclaim;

	tb_port_dbg(up, "available bandwidth for new USB3 tunnel %d/%d Mb/s\n",
		    available_up, available_करोwn);

	tunnel = tb_tunnel_alloc_usb3(tb, up, करोwn, available_up,
				      available_करोwn);
	अगर (!tunnel) अणु
		ret = -ENOMEM;
		जाओ err_reclaim;
	पूर्ण

	अगर (tb_tunnel_activate(tunnel)) अणु
		tb_port_info(up,
			     "USB3 tunnel activation failed, aborting\n");
		ret = -EIO;
		जाओ err_मुक्त;
	पूर्ण

	list_add_tail(&tunnel->list, &tcm->tunnel_list);
	अगर (tb_route(parent))
		tb_reclaim_usb3_bandwidth(tb, करोwn, up);

	वापस 0;

err_मुक्त:
	tb_tunnel_मुक्त(tunnel);
err_reclaim:
	अगर (tb_route(parent))
		tb_reclaim_usb3_bandwidth(tb, करोwn, up);

	वापस ret;
पूर्ण

अटल पूर्णांक tb_create_usb3_tunnels(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;
	पूर्णांक ret;

	अगर (!tb_acpi_may_tunnel_usb3())
		वापस 0;

	अगर (tb_route(sw)) अणु
		ret = tb_tunnel_usb3(sw->tb, sw);
		अगर (ret)
			वापस ret;
	पूर्ण

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (!tb_port_has_remote(port))
			जारी;
		ret = tb_create_usb3_tunnels(port->remote->sw);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tb_scan_port(काष्ठा tb_port *port);

/*
 * tb_scan_चयन() - scan क्रम and initialize करोwnstream चयनes
 */
अटल व्योम tb_scan_चयन(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;

	pm_runसमय_get_sync(&sw->dev);

	tb_चयन_क्रम_each_port(sw, port)
		tb_scan_port(port);

	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);
पूर्ण

/*
 * tb_scan_port() - check क्रम and initialize चयनes below port
 */
अटल व्योम tb_scan_port(काष्ठा tb_port *port)
अणु
	काष्ठा tb_cm *tcm = tb_priv(port->sw->tb);
	काष्ठा tb_port *upstream_port;
	काष्ठा tb_चयन *sw;

	अगर (tb_is_upstream_port(port))
		वापस;

	अगर (tb_port_is_dpout(port) && tb_dp_port_hpd_is_active(port) == 1 &&
	    !tb_dp_port_is_enabled(port)) अणु
		tb_port_dbg(port, "DP adapter HPD set, queuing hotplug\n");
		tb_queue_hotplug(port->sw->tb, tb_route(port->sw), port->port,
				 false);
		वापस;
	पूर्ण

	अगर (port->config.type != TB_TYPE_PORT)
		वापस;
	अगर (port->dual_link_port && port->link_nr)
		वापस; /*
			 * Downstream चयन is reachable through two ports.
			 * Only scan on the primary port (link_nr == 0).
			 */
	अगर (tb_रुको_क्रम_port(port, false) <= 0)
		वापस;
	अगर (port->remote) अणु
		tb_port_dbg(port, "port already has a remote\n");
		वापस;
	पूर्ण

	tb_reसमयr_scan(port);

	sw = tb_चयन_alloc(port->sw->tb, &port->sw->dev,
			     tb_करोwnstream_route(port));
	अगर (IS_ERR(sw)) अणु
		/*
		 * If there is an error accessing the connected चयन
		 * it may be connected to another करोमुख्य. Also we allow
		 * the other करोमुख्य to be connected to a max depth चयन.
		 */
		अगर (PTR_ERR(sw) == -EIO || PTR_ERR(sw) == -EADDRNOTAVAIL)
			tb_scan_xकरोमुख्य(port);
		वापस;
	पूर्ण

	अगर (tb_चयन_configure(sw)) अणु
		tb_चयन_put(sw);
		वापस;
	पूर्ण

	/*
	 * If there was previously another करोमुख्य connected हटाओ it
	 * first.
	 */
	अगर (port->xकरोमुख्य) अणु
		tb_xकरोमुख्य_हटाओ(port->xकरोमुख्य);
		tb_port_unconfigure_xकरोमुख्य(port);
		port->xकरोमुख्य = शून्य;
	पूर्ण

	/*
	 * Do not send uevents until we have discovered all existing
	 * tunnels and know which चयनes were authorized alपढ़ोy by
	 * the boot firmware.
	 */
	अगर (!tcm->hotplug_active)
		dev_set_uevent_suppress(&sw->dev, true);

	/*
	 * At the moment Thunderbolt 2 and beyond (devices with LC) we
	 * can support runसमय PM.
	 */
	sw->rpm = sw->generation > 1;

	अगर (tb_चयन_add(sw)) अणु
		tb_चयन_put(sw);
		वापस;
	पूर्ण

	/* Link the चयनes using both links अगर available */
	upstream_port = tb_upstream_port(sw);
	port->remote = upstream_port;
	upstream_port->remote = port;
	अगर (port->dual_link_port && upstream_port->dual_link_port) अणु
		port->dual_link_port->remote = upstream_port->dual_link_port;
		upstream_port->dual_link_port->remote = port->dual_link_port;
	पूर्ण

	/* Enable lane bonding अगर supported */
	tb_चयन_lane_bonding_enable(sw);
	/* Set the link configured */
	tb_चयन_configure_link(sw);

	अगर (tb_enable_पंचांगu(sw))
		tb_sw_warn(sw, "failed to enable TMU\n");

	/* Scan upstream reसमयrs */
	tb_reसमयr_scan(upstream_port);

	/*
	 * Create USB 3.x tunnels only when the चयन is plugged to the
	 * करोमुख्य. This is because we scan the करोमुख्य also during discovery
	 * and want to discover existing USB 3.x tunnels beक्रमe we create
	 * any new.
	 */
	अगर (tcm->hotplug_active && tb_tunnel_usb3(sw->tb, sw))
		tb_sw_warn(sw, "USB3 tunnel creation failed\n");

	tb_add_dp_resources(sw);
	tb_scan_चयन(sw);
पूर्ण

अटल व्योम tb_deactivate_and_मुक्त_tunnel(काष्ठा tb_tunnel *tunnel)
अणु
	काष्ठा tb_port *src_port, *dst_port;
	काष्ठा tb *tb;

	अगर (!tunnel)
		वापस;

	tb_tunnel_deactivate(tunnel);
	list_del(&tunnel->list);

	tb = tunnel->tb;
	src_port = tunnel->src_port;
	dst_port = tunnel->dst_port;

	चयन (tunnel->type) अणु
	हाल TB_TUNNEL_DP:
		/*
		 * In हाल of DP tunnel make sure the DP IN resource is
		 * deallocated properly.
		 */
		tb_चयन_dealloc_dp_resource(src_port->sw, src_port);
		/* Now we can allow the करोमुख्य to runसमय suspend again */
		pm_runसमय_mark_last_busy(&dst_port->sw->dev);
		pm_runसमय_put_स्वतःsuspend(&dst_port->sw->dev);
		pm_runसमय_mark_last_busy(&src_port->sw->dev);
		pm_runसमय_put_स्वतःsuspend(&src_port->sw->dev);
		fallthrough;

	हाल TB_TUNNEL_USB3:
		tb_reclaim_usb3_bandwidth(tb, src_port, dst_port);
		अवरोध;

	शेष:
		/*
		 * PCIe and DMA tunnels करो not consume guaranteed
		 * bandwidth.
		 */
		अवरोध;
	पूर्ण

	tb_tunnel_मुक्त(tunnel);
पूर्ण

/*
 * tb_मुक्त_invalid_tunnels() - destroy tunnels of devices that have gone away
 */
अटल व्योम tb_मुक्त_invalid_tunnels(काष्ठा tb *tb)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_tunnel *n;

	list_क्रम_each_entry_safe(tunnel, n, &tcm->tunnel_list, list) अणु
		अगर (tb_tunnel_is_invalid(tunnel))
			tb_deactivate_and_मुक्त_tunnel(tunnel);
	पूर्ण
पूर्ण

/*
 * tb_मुक्त_unplugged_children() - traverse hierarchy and मुक्त unplugged चयनes
 */
अटल व्योम tb_मुक्त_unplugged_children(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (!tb_port_has_remote(port))
			जारी;

		अगर (port->remote->sw->is_unplugged) अणु
			tb_reसमयr_हटाओ_all(port);
			tb_हटाओ_dp_resources(port->remote->sw);
			tb_चयन_unconfigure_link(port->remote->sw);
			tb_चयन_lane_bonding_disable(port->remote->sw);
			tb_चयन_हटाओ(port->remote->sw);
			port->remote = शून्य;
			अगर (port->dual_link_port)
				port->dual_link_port->remote = शून्य;
		पूर्ण अन्यथा अणु
			tb_मुक्त_unplugged_children(port->remote->sw);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा tb_port *tb_find_pcie_करोwn(काष्ठा tb_चयन *sw,
					 स्थिर काष्ठा tb_port *port)
अणु
	काष्ठा tb_port *करोwn = शून्य;

	/*
	 * To keep plugging devices consistently in the same PCIe
	 * hierarchy, करो mapping here क्रम चयन करोwnstream PCIe ports.
	 */
	अगर (tb_चयन_is_usb4(sw)) अणु
		करोwn = usb4_चयन_map_pcie_करोwn(sw, port);
	पूर्ण अन्यथा अगर (!tb_route(sw)) अणु
		पूर्णांक phy_port = tb_phy_port_from_link(port->port);
		पूर्णांक index;

		/*
		 * Hard-coded Thunderbolt port to PCIe करोwn port mapping
		 * per controller.
		 */
		अगर (tb_चयन_is_cactus_ridge(sw) ||
		    tb_चयन_is_alpine_ridge(sw))
			index = !phy_port ? 6 : 7;
		अन्यथा अगर (tb_चयन_is_falcon_ridge(sw))
			index = !phy_port ? 6 : 8;
		अन्यथा अगर (tb_चयन_is_titan_ridge(sw))
			index = !phy_port ? 8 : 9;
		अन्यथा
			जाओ out;

		/* Validate the hard-coding */
		अगर (WARN_ON(index > sw->config.max_port_number))
			जाओ out;

		करोwn = &sw->ports[index];
	पूर्ण

	अगर (करोwn) अणु
		अगर (WARN_ON(!tb_port_is_pcie_करोwn(करोwn)))
			जाओ out;
		अगर (tb_pci_port_is_enabled(करोwn))
			जाओ out;

		वापस करोwn;
	पूर्ण

out:
	वापस tb_find_unused_port(sw, TB_TYPE_PCIE_DOWN);
पूर्ण

अटल काष्ठा tb_port *tb_find_dp_out(काष्ठा tb *tb, काष्ठा tb_port *in)
अणु
	काष्ठा tb_port *host_port, *port;
	काष्ठा tb_cm *tcm = tb_priv(tb);

	host_port = tb_route(in->sw) ?
		tb_port_at(tb_route(in->sw), tb->root_चयन) : शून्य;

	list_क्रम_each_entry(port, &tcm->dp_resources, list) अणु
		अगर (!tb_port_is_dpout(port))
			जारी;

		अगर (tb_port_is_enabled(port)) अणु
			tb_port_dbg(port, "in use\n");
			जारी;
		पूर्ण

		tb_port_dbg(port, "DP OUT available\n");

		/*
		 * Keep the DP tunnel under the topology starting from
		 * the same host router करोwnstream port.
		 */
		अगर (host_port && tb_route(port->sw)) अणु
			काष्ठा tb_port *p;

			p = tb_port_at(tb_route(port->sw), tb->root_चयन);
			अगर (p != host_port)
				जारी;
		पूर्ण

		वापस port;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम tb_tunnel_dp(काष्ठा tb *tb)
अणु
	पूर्णांक available_up, available_करोwn, ret;
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_port *port, *in, *out;
	काष्ठा tb_tunnel *tunnel;

	अगर (!tb_acpi_may_tunnel_dp()) अणु
		tb_dbg(tb, "DP tunneling disabled, not creating tunnel\n");
		वापस;
	पूर्ण

	/*
	 * Find pair of inactive DP IN and DP OUT adapters and then
	 * establish a DP tunnel between them.
	 */
	tb_dbg(tb, "looking for DP IN <-> DP OUT pairs:\n");

	in = शून्य;
	out = शून्य;
	list_क्रम_each_entry(port, &tcm->dp_resources, list) अणु
		अगर (!tb_port_is_dpin(port))
			जारी;

		अगर (tb_port_is_enabled(port)) अणु
			tb_port_dbg(port, "in use\n");
			जारी;
		पूर्ण

		tb_port_dbg(port, "DP IN available\n");

		out = tb_find_dp_out(tb, port);
		अगर (out) अणु
			in = port;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!in) अणु
		tb_dbg(tb, "no suitable DP IN adapter available, not tunneling\n");
		वापस;
	पूर्ण
	अगर (!out) अणु
		tb_dbg(tb, "no suitable DP OUT adapter available, not tunneling\n");
		वापस;
	पूर्ण

	/*
	 * DP stream needs the करोमुख्य to be active so runसमय resume
	 * both ends of the tunnel.
	 *
	 * This should bring the routers in the middle active as well
	 * and keeps the करोमुख्य from runसमय suspending जबतक the DP
	 * tunnel is active.
	 */
	pm_runसमय_get_sync(&in->sw->dev);
	pm_runसमय_get_sync(&out->sw->dev);

	अगर (tb_चयन_alloc_dp_resource(in->sw, in)) अणु
		tb_port_dbg(in, "no resource available for DP IN, not tunneling\n");
		जाओ err_rpm_put;
	पूर्ण

	/* Make all unused USB3 bandwidth available क्रम the new DP tunnel */
	ret = tb_release_unused_usb3_bandwidth(tb, in, out);
	अगर (ret) अणु
		tb_warn(tb, "failed to release unused bandwidth\n");
		जाओ err_dealloc_dp;
	पूर्ण

	ret = tb_available_bandwidth(tb, in, out, &available_up,
				     &available_करोwn);
	अगर (ret)
		जाओ err_reclaim;

	tb_dbg(tb, "available bandwidth for new DP tunnel %u/%u Mb/s\n",
	       available_up, available_करोwn);

	tunnel = tb_tunnel_alloc_dp(tb, in, out, available_up, available_करोwn);
	अगर (!tunnel) अणु
		tb_port_dbg(out, "could not allocate DP tunnel\n");
		जाओ err_reclaim;
	पूर्ण

	अगर (tb_tunnel_activate(tunnel)) अणु
		tb_port_info(out, "DP tunnel activation failed, aborting\n");
		जाओ err_मुक्त;
	पूर्ण

	list_add_tail(&tunnel->list, &tcm->tunnel_list);
	tb_reclaim_usb3_bandwidth(tb, in, out);
	वापस;

err_मुक्त:
	tb_tunnel_मुक्त(tunnel);
err_reclaim:
	tb_reclaim_usb3_bandwidth(tb, in, out);
err_dealloc_dp:
	tb_चयन_dealloc_dp_resource(in->sw, in);
err_rpm_put:
	pm_runसमय_mark_last_busy(&out->sw->dev);
	pm_runसमय_put_स्वतःsuspend(&out->sw->dev);
	pm_runसमय_mark_last_busy(&in->sw->dev);
	pm_runसमय_put_स्वतःsuspend(&in->sw->dev);
पूर्ण

अटल व्योम tb_dp_resource_unavailable(काष्ठा tb *tb, काष्ठा tb_port *port)
अणु
	काष्ठा tb_port *in, *out;
	काष्ठा tb_tunnel *tunnel;

	अगर (tb_port_is_dpin(port)) अणु
		tb_port_dbg(port, "DP IN resource unavailable\n");
		in = port;
		out = शून्य;
	पूर्ण अन्यथा अणु
		tb_port_dbg(port, "DP OUT resource unavailable\n");
		in = शून्य;
		out = port;
	पूर्ण

	tunnel = tb_find_tunnel(tb, TB_TUNNEL_DP, in, out);
	tb_deactivate_and_मुक्त_tunnel(tunnel);
	list_del_init(&port->list);

	/*
	 * See अगर there is another DP OUT port that can be used क्रम
	 * to create another tunnel.
	 */
	tb_tunnel_dp(tb);
पूर्ण

अटल व्योम tb_dp_resource_available(काष्ठा tb *tb, काष्ठा tb_port *port)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_port *p;

	अगर (tb_port_is_enabled(port))
		वापस;

	list_क्रम_each_entry(p, &tcm->dp_resources, list) अणु
		अगर (p == port)
			वापस;
	पूर्ण

	tb_port_dbg(port, "DP %s resource available\n",
		    tb_port_is_dpin(port) ? "IN" : "OUT");
	list_add_tail(&port->list, &tcm->dp_resources);

	/* Look क्रम suitable DP IN <-> DP OUT pairs now */
	tb_tunnel_dp(tb);
पूर्ण

अटल व्योम tb_disconnect_and_release_dp(काष्ठा tb *tb)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_tunnel *tunnel, *n;

	/*
	 * Tear करोwn all DP tunnels and release their resources. They
	 * will be re-established after resume based on plug events.
	 */
	list_क्रम_each_entry_safe_reverse(tunnel, n, &tcm->tunnel_list, list) अणु
		अगर (tb_tunnel_is_dp(tunnel))
			tb_deactivate_and_मुक्त_tunnel(tunnel);
	पूर्ण

	जबतक (!list_empty(&tcm->dp_resources)) अणु
		काष्ठा tb_port *port;

		port = list_first_entry(&tcm->dp_resources,
					काष्ठा tb_port, list);
		list_del_init(&port->list);
	पूर्ण
पूर्ण

अटल पूर्णांक tb_disconnect_pci(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_port *up;

	up = tb_चयन_find_port(sw, TB_TYPE_PCIE_UP);
	अगर (WARN_ON(!up))
		वापस -ENODEV;

	tunnel = tb_find_tunnel(tb, TB_TUNNEL_PCI, शून्य, up);
	अगर (WARN_ON(!tunnel))
		वापस -ENODEV;

	tb_tunnel_deactivate(tunnel);
	list_del(&tunnel->list);
	tb_tunnel_मुक्त(tunnel);
	वापस 0;
पूर्ण

अटल पूर्णांक tb_tunnel_pci(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *up, *करोwn, *port;
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_चयन *parent_sw;
	काष्ठा tb_tunnel *tunnel;

	up = tb_चयन_find_port(sw, TB_TYPE_PCIE_UP);
	अगर (!up)
		वापस 0;

	/*
	 * Look up available करोwn port. Since we are chaining it should
	 * be found right above this चयन.
	 */
	parent_sw = tb_to_चयन(sw->dev.parent);
	port = tb_port_at(tb_route(sw), parent_sw);
	करोwn = tb_find_pcie_करोwn(parent_sw, port);
	अगर (!करोwn)
		वापस 0;

	tunnel = tb_tunnel_alloc_pci(tb, up, करोwn);
	अगर (!tunnel)
		वापस -ENOMEM;

	अगर (tb_tunnel_activate(tunnel)) अणु
		tb_port_info(up,
			     "PCIe tunnel activation failed, aborting\n");
		tb_tunnel_मुक्त(tunnel);
		वापस -EIO;
	पूर्ण

	list_add_tail(&tunnel->list, &tcm->tunnel_list);
	वापस 0;
पूर्ण

अटल पूर्णांक tb_approve_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
				    पूर्णांक transmit_path, पूर्णांक transmit_ring,
				    पूर्णांक receive_path, पूर्णांक receive_ring)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_port *nhi_port, *dst_port;
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_चयन *sw;

	sw = tb_to_चयन(xd->dev.parent);
	dst_port = tb_port_at(xd->route, sw);
	nhi_port = tb_चयन_find_port(tb->root_चयन, TB_TYPE_NHI);

	mutex_lock(&tb->lock);
	tunnel = tb_tunnel_alloc_dma(tb, nhi_port, dst_port, transmit_path,
				     transmit_ring, receive_path, receive_ring);
	अगर (!tunnel) अणु
		mutex_unlock(&tb->lock);
		वापस -ENOMEM;
	पूर्ण

	अगर (tb_tunnel_activate(tunnel)) अणु
		tb_port_info(nhi_port,
			     "DMA tunnel activation failed, aborting\n");
		tb_tunnel_मुक्त(tunnel);
		mutex_unlock(&tb->lock);
		वापस -EIO;
	पूर्ण

	list_add_tail(&tunnel->list, &tcm->tunnel_list);
	mutex_unlock(&tb->lock);
	वापस 0;
पूर्ण

अटल व्योम __tb_disconnect_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
					  पूर्णांक transmit_path, पूर्णांक transmit_ring,
					  पूर्णांक receive_path, पूर्णांक receive_ring)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_port *nhi_port, *dst_port;
	काष्ठा tb_tunnel *tunnel, *n;
	काष्ठा tb_चयन *sw;

	sw = tb_to_चयन(xd->dev.parent);
	dst_port = tb_port_at(xd->route, sw);
	nhi_port = tb_चयन_find_port(tb->root_चयन, TB_TYPE_NHI);

	list_क्रम_each_entry_safe(tunnel, n, &tcm->tunnel_list, list) अणु
		अगर (!tb_tunnel_is_dma(tunnel))
			जारी;
		अगर (tunnel->src_port != nhi_port || tunnel->dst_port != dst_port)
			जारी;

		अगर (tb_tunnel_match_dma(tunnel, transmit_path, transmit_ring,
					receive_path, receive_ring))
			tb_deactivate_and_मुक्त_tunnel(tunnel);
	पूर्ण
पूर्ण

अटल पूर्णांक tb_disconnect_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
				       पूर्णांक transmit_path, पूर्णांक transmit_ring,
				       पूर्णांक receive_path, पूर्णांक receive_ring)
अणु
	अगर (!xd->is_unplugged) अणु
		mutex_lock(&tb->lock);
		__tb_disconnect_xकरोमुख्य_paths(tb, xd, transmit_path,
					      transmit_ring, receive_path,
					      receive_ring);
		mutex_unlock(&tb->lock);
	पूर्ण
	वापस 0;
पूर्ण

/* hotplug handling */

/*
 * tb_handle_hotplug() - handle hotplug event
 *
 * Executes on tb->wq.
 */
अटल व्योम tb_handle_hotplug(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tb_hotplug_event *ev = container_of(work, typeof(*ev), work);
	काष्ठा tb *tb = ev->tb;
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_चयन *sw;
	काष्ठा tb_port *port;

	/* Bring the करोमुख्य back from sleep अगर it was suspended */
	pm_runसमय_get_sync(&tb->dev);

	mutex_lock(&tb->lock);
	अगर (!tcm->hotplug_active)
		जाओ out; /* during init, suspend or shutकरोwn */

	sw = tb_चयन_find_by_route(tb, ev->route);
	अगर (!sw) अणु
		tb_warn(tb,
			"hotplug event from non existent switch %llx:%x (unplug: %d)\n",
			ev->route, ev->port, ev->unplug);
		जाओ out;
	पूर्ण
	अगर (ev->port > sw->config.max_port_number) अणु
		tb_warn(tb,
			"hotplug event from non existent port %llx:%x (unplug: %d)\n",
			ev->route, ev->port, ev->unplug);
		जाओ put_sw;
	पूर्ण
	port = &sw->ports[ev->port];
	अगर (tb_is_upstream_port(port)) अणु
		tb_dbg(tb, "hotplug event for upstream port %llx:%x (unplug: %d)\n",
		       ev->route, ev->port, ev->unplug);
		जाओ put_sw;
	पूर्ण

	pm_runसमय_get_sync(&sw->dev);

	अगर (ev->unplug) अणु
		tb_reसमयr_हटाओ_all(port);

		अगर (tb_port_has_remote(port)) अणु
			tb_port_dbg(port, "switch unplugged\n");
			tb_sw_set_unplugged(port->remote->sw);
			tb_मुक्त_invalid_tunnels(tb);
			tb_हटाओ_dp_resources(port->remote->sw);
			tb_चयन_पंचांगu_disable(port->remote->sw);
			tb_चयन_unconfigure_link(port->remote->sw);
			tb_चयन_lane_bonding_disable(port->remote->sw);
			tb_चयन_हटाओ(port->remote->sw);
			port->remote = शून्य;
			अगर (port->dual_link_port)
				port->dual_link_port->remote = शून्य;
			/* Maybe we can create another DP tunnel */
			tb_tunnel_dp(tb);
		पूर्ण अन्यथा अगर (port->xकरोमुख्य) अणु
			काष्ठा tb_xकरोमुख्य *xd = tb_xकरोमुख्य_get(port->xकरोमुख्य);

			tb_port_dbg(port, "xdomain unplugged\n");
			/*
			 * Service drivers are unbound during
			 * tb_xकरोमुख्य_हटाओ() so setting XDoमुख्य as
			 * unplugged here prevents deadlock अगर they call
			 * tb_xकरोमुख्य_disable_paths(). We will tear करोwn
			 * all the tunnels below.
			 */
			xd->is_unplugged = true;
			tb_xकरोमुख्य_हटाओ(xd);
			port->xकरोमुख्य = शून्य;
			__tb_disconnect_xकरोमुख्य_paths(tb, xd, -1, -1, -1, -1);
			tb_xकरोमुख्य_put(xd);
			tb_port_unconfigure_xकरोमुख्य(port);
		पूर्ण अन्यथा अगर (tb_port_is_dpout(port) || tb_port_is_dpin(port)) अणु
			tb_dp_resource_unavailable(tb, port);
		पूर्ण अन्यथा अणु
			tb_port_dbg(port,
				   "got unplug event for disconnected port, ignoring\n");
		पूर्ण
	पूर्ण अन्यथा अगर (port->remote) अणु
		tb_port_dbg(port, "got plug event for connected port, ignoring\n");
	पूर्ण अन्यथा अणु
		अगर (tb_port_is_null(port)) अणु
			tb_port_dbg(port, "hotplug: scanning\n");
			tb_scan_port(port);
			अगर (!port->remote)
				tb_port_dbg(port, "hotplug: no switch found\n");
		पूर्ण अन्यथा अगर (tb_port_is_dpout(port) || tb_port_is_dpin(port)) अणु
			tb_dp_resource_available(tb, port);
		पूर्ण
	पूर्ण

	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);

put_sw:
	tb_चयन_put(sw);
out:
	mutex_unlock(&tb->lock);

	pm_runसमय_mark_last_busy(&tb->dev);
	pm_runसमय_put_स्वतःsuspend(&tb->dev);

	kमुक्त(ev);
पूर्ण

/*
 * tb_schedule_hotplug_handler() - callback function क्रम the control channel
 *
 * Delegates to tb_handle_hotplug.
 */
अटल व्योम tb_handle_event(काष्ठा tb *tb, क्रमागत tb_cfg_pkg_type type,
			    स्थिर व्योम *buf, माप_प्रकार size)
अणु
	स्थिर काष्ठा cfg_event_pkg *pkg = buf;
	u64 route;

	अगर (type != TB_CFG_PKG_EVENT) अणु
		tb_warn(tb, "unexpected event %#x, ignoring\n", type);
		वापस;
	पूर्ण

	route = tb_cfg_get_route(&pkg->header);

	अगर (tb_cfg_ack_plug(tb->ctl, route, pkg->port, pkg->unplug)) अणु
		tb_warn(tb, "could not ack plug event on %llx:%x\n", route,
			pkg->port);
	पूर्ण

	tb_queue_hotplug(tb, route, pkg->port, pkg->unplug);
पूर्ण

अटल व्योम tb_stop(काष्ठा tb *tb)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_tunnel *tunnel;
	काष्ठा tb_tunnel *n;

	cancel_delayed_work(&tcm->हटाओ_work);
	/* tunnels are only present after everything has been initialized */
	list_क्रम_each_entry_safe(tunnel, n, &tcm->tunnel_list, list) अणु
		/*
		 * DMA tunnels require the driver to be functional so we
		 * tear them करोwn. Other protocol tunnels can be left
		 * पूर्णांकact.
		 */
		अगर (tb_tunnel_is_dma(tunnel))
			tb_tunnel_deactivate(tunnel);
		tb_tunnel_मुक्त(tunnel);
	पूर्ण
	tb_चयन_हटाओ(tb->root_चयन);
	tcm->hotplug_active = false; /* संकेत tb_handle_hotplug to quit */
पूर्ण

अटल पूर्णांक tb_scan_finalize_चयन(काष्ठा device *dev, व्योम *data)
अणु
	अगर (tb_is_चयन(dev)) अणु
		काष्ठा tb_चयन *sw = tb_to_चयन(dev);

		/*
		 * If we found that the चयन was alपढ़ोy setup by the
		 * boot firmware, mark it as authorized now beक्रमe we
		 * send uevent to userspace.
		 */
		अगर (sw->boot)
			sw->authorized = 1;

		dev_set_uevent_suppress(dev, false);
		kobject_uevent(&dev->kobj, KOBJ_ADD);
		device_क्रम_each_child(dev, शून्य, tb_scan_finalize_चयन);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tb_start(काष्ठा tb *tb)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);
	पूर्णांक ret;

	tb->root_चयन = tb_चयन_alloc(tb, &tb->dev, 0);
	अगर (IS_ERR(tb->root_चयन))
		वापस PTR_ERR(tb->root_चयन);

	/*
	 * ICM firmware upgrade needs running firmware and in native
	 * mode that is not available so disable firmware upgrade of the
	 * root चयन.
	 */
	tb->root_चयन->no_nvm_upgrade = true;
	/* All USB4 routers support runसमय PM */
	tb->root_चयन->rpm = tb_चयन_is_usb4(tb->root_चयन);

	ret = tb_चयन_configure(tb->root_चयन);
	अगर (ret) अणु
		tb_चयन_put(tb->root_चयन);
		वापस ret;
	पूर्ण

	/* Announce the चयन to the world */
	ret = tb_चयन_add(tb->root_चयन);
	अगर (ret) अणु
		tb_चयन_put(tb->root_चयन);
		वापस ret;
	पूर्ण

	/* Enable TMU अगर it is off */
	tb_चयन_पंचांगu_enable(tb->root_चयन);
	/* Full scan to discover devices added beक्रमe the driver was loaded. */
	tb_scan_चयन(tb->root_चयन);
	/* Find out tunnels created by the boot firmware */
	tb_discover_tunnels(tb->root_चयन);
	/*
	 * If the boot firmware did not create USB 3.x tunnels create them
	 * now क्रम the whole topology.
	 */
	tb_create_usb3_tunnels(tb->root_चयन);
	/* Add DP IN resources क्रम the root चयन */
	tb_add_dp_resources(tb->root_चयन);
	/* Make the discovered चयनes available to the userspace */
	device_क्रम_each_child(&tb->root_चयन->dev, शून्य,
			      tb_scan_finalize_चयन);

	/* Allow tb_handle_hotplug to progress events */
	tcm->hotplug_active = true;
	वापस 0;
पूर्ण

अटल पूर्णांक tb_suspend_noirq(काष्ठा tb *tb)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);

	tb_dbg(tb, "suspending...\n");
	tb_disconnect_and_release_dp(tb);
	tb_चयन_suspend(tb->root_चयन, false);
	tcm->hotplug_active = false; /* संकेत tb_handle_hotplug to quit */
	tb_dbg(tb, "suspend finished\n");

	वापस 0;
पूर्ण

अटल व्योम tb_restore_children(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;

	/* No need to restore अगर the router is alपढ़ोy unplugged */
	अगर (sw->is_unplugged)
		वापस;

	अगर (tb_enable_पंचांगu(sw))
		tb_sw_warn(sw, "failed to restore TMU configuration\n");

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (!tb_port_has_remote(port) && !port->xकरोमुख्य)
			जारी;

		अगर (port->remote) अणु
			tb_चयन_lane_bonding_enable(port->remote->sw);
			tb_चयन_configure_link(port->remote->sw);

			tb_restore_children(port->remote->sw);
		पूर्ण अन्यथा अगर (port->xकरोमुख्य) अणु
			tb_port_configure_xकरोमुख्य(port);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tb_resume_noirq(काष्ठा tb *tb)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_tunnel *tunnel, *n;

	tb_dbg(tb, "resuming...\n");

	/* हटाओ any pci devices the firmware might have setup */
	tb_चयन_reset(tb->root_चयन);

	tb_चयन_resume(tb->root_चयन);
	tb_मुक्त_invalid_tunnels(tb);
	tb_मुक्त_unplugged_children(tb->root_चयन);
	tb_restore_children(tb->root_चयन);
	list_क्रम_each_entry_safe(tunnel, n, &tcm->tunnel_list, list)
		tb_tunnel_restart(tunnel);
	अगर (!list_empty(&tcm->tunnel_list)) अणु
		/*
		 * the pcie links need some समय to get going.
		 * 100ms works क्रम me...
		 */
		tb_dbg(tb, "tunnels restarted, sleeping for 100ms\n");
		msleep(100);
	पूर्ण
	 /* Allow tb_handle_hotplug to progress events */
	tcm->hotplug_active = true;
	tb_dbg(tb, "resume finished\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tb_मुक्त_unplugged_xकरोमुख्यs(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_port *port;
	पूर्णांक ret = 0;

	tb_चयन_क्रम_each_port(sw, port) अणु
		अगर (tb_is_upstream_port(port))
			जारी;
		अगर (port->xकरोमुख्य && port->xकरोमुख्य->is_unplugged) अणु
			tb_reसमयr_हटाओ_all(port);
			tb_xकरोमुख्य_हटाओ(port->xकरोमुख्य);
			tb_port_unconfigure_xकरोमुख्य(port);
			port->xकरोमुख्य = शून्य;
			ret++;
		पूर्ण अन्यथा अगर (port->remote) अणु
			ret += tb_मुक्त_unplugged_xकरोमुख्यs(port->remote->sw);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tb_मुक्तze_noirq(काष्ठा tb *tb)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);

	tcm->hotplug_active = false;
	वापस 0;
पूर्ण

अटल पूर्णांक tb_thaw_noirq(काष्ठा tb *tb)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);

	tcm->hotplug_active = true;
	वापस 0;
पूर्ण

अटल व्योम tb_complete(काष्ठा tb *tb)
अणु
	/*
	 * Release any unplugged XDoमुख्यs and अगर there is a हाल where
	 * another करोमुख्य is swapped in place of unplugged XDoमुख्य we
	 * need to run another rescan.
	 */
	mutex_lock(&tb->lock);
	अगर (tb_मुक्त_unplugged_xकरोमुख्यs(tb->root_चयन))
		tb_scan_चयन(tb->root_चयन);
	mutex_unlock(&tb->lock);
पूर्ण

अटल पूर्णांक tb_runसमय_suspend(काष्ठा tb *tb)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);

	mutex_lock(&tb->lock);
	tb_चयन_suspend(tb->root_चयन, true);
	tcm->hotplug_active = false;
	mutex_unlock(&tb->lock);

	वापस 0;
पूर्ण

अटल व्योम tb_हटाओ_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tb_cm *tcm = container_of(work, काष्ठा tb_cm, हटाओ_work.work);
	काष्ठा tb *tb = tcm_to_tb(tcm);

	mutex_lock(&tb->lock);
	अगर (tb->root_चयन) अणु
		tb_मुक्त_unplugged_children(tb->root_चयन);
		tb_मुक्त_unplugged_xकरोमुख्यs(tb->root_चयन);
	पूर्ण
	mutex_unlock(&tb->lock);
पूर्ण

अटल पूर्णांक tb_runसमय_resume(काष्ठा tb *tb)
अणु
	काष्ठा tb_cm *tcm = tb_priv(tb);
	काष्ठा tb_tunnel *tunnel, *n;

	mutex_lock(&tb->lock);
	tb_चयन_resume(tb->root_चयन);
	tb_मुक्त_invalid_tunnels(tb);
	tb_restore_children(tb->root_चयन);
	list_क्रम_each_entry_safe(tunnel, n, &tcm->tunnel_list, list)
		tb_tunnel_restart(tunnel);
	tcm->hotplug_active = true;
	mutex_unlock(&tb->lock);

	/*
	 * Schedule cleanup of any unplugged devices. Run this in a
	 * separate thपढ़ो to aव्योम possible deadlock अगर the device
	 * removal runसमय resumes the unplugged device.
	 */
	queue_delayed_work(tb->wq, &tcm->हटाओ_work, msecs_to_jअगरfies(50));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tb_cm_ops tb_cm_ops = अणु
	.start = tb_start,
	.stop = tb_stop,
	.suspend_noirq = tb_suspend_noirq,
	.resume_noirq = tb_resume_noirq,
	.मुक्तze_noirq = tb_मुक्तze_noirq,
	.thaw_noirq = tb_thaw_noirq,
	.complete = tb_complete,
	.runसमय_suspend = tb_runसमय_suspend,
	.runसमय_resume = tb_runसमय_resume,
	.handle_event = tb_handle_event,
	.disapprove_चयन = tb_disconnect_pci,
	.approve_चयन = tb_tunnel_pci,
	.approve_xकरोमुख्य_paths = tb_approve_xकरोमुख्य_paths,
	.disconnect_xकरोमुख्य_paths = tb_disconnect_xकरोमुख्य_paths,
पूर्ण;

काष्ठा tb *tb_probe(काष्ठा tb_nhi *nhi)
अणु
	काष्ठा tb_cm *tcm;
	काष्ठा tb *tb;

	tb = tb_करोमुख्य_alloc(nhi, TB_TIMEOUT, माप(*tcm));
	अगर (!tb)
		वापस शून्य;

	अगर (tb_acpi_may_tunnel_pcie())
		tb->security_level = TB_SECURITY_USER;
	अन्यथा
		tb->security_level = TB_SECURITY_NOPCIE;

	tb->cm_ops = &tb_cm_ops;

	tcm = tb_priv(tb);
	INIT_LIST_HEAD(&tcm->tunnel_list);
	INIT_LIST_HEAD(&tcm->dp_resources);
	INIT_DELAYED_WORK(&tcm->हटाओ_work, tb_हटाओ_work);

	tb_dbg(tb, "using software connection manager\n");

	वापस tb;
पूर्ण
