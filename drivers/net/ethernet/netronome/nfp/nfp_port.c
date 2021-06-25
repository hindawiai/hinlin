<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/lockdep.h>
#समावेश <linux/netdevice.h>

#समावेश "nfpcore/nfp_cpp.h"
#समावेश "nfpcore/nfp_nsp.h"
#समावेश "nfp_app.h"
#समावेश "nfp_main.h"
#समावेश "nfp_net.h"
#समावेश "nfp_port.h"

काष्ठा nfp_port *nfp_port_from_netdev(काष्ठा net_device *netdev)
अणु
	अगर (nfp_netdev_is_nfp_net(netdev)) अणु
		काष्ठा nfp_net *nn = netdev_priv(netdev);

		वापस nn->port;
	पूर्ण

	अगर (nfp_netdev_is_nfp_repr(netdev)) अणु
		काष्ठा nfp_repr *repr = netdev_priv(netdev);

		वापस repr->port;
	पूर्ण

	WARN(1, "Unknown netdev type for nfp_port\n");

	वापस शून्य;
पूर्ण

पूर्णांक nfp_port_get_port_parent_id(काष्ठा net_device *netdev,
				काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा nfp_port *port;
	स्थिर u8 *serial;

	port = nfp_port_from_netdev(netdev);
	अगर (!port)
		वापस -EOPNOTSUPP;

	ppid->id_len = nfp_cpp_serial(port->app->cpp, &serial);
	स_नकल(&ppid->id, serial, ppid->id_len);

	वापस 0;
पूर्ण

पूर्णांक nfp_port_setup_tc(काष्ठा net_device *netdev, क्रमागत tc_setup_type type,
		      व्योम *type_data)
अणु
	काष्ठा nfp_port *port;

	port = nfp_port_from_netdev(netdev);
	अगर (!port)
		वापस -EOPNOTSUPP;

	वापस nfp_app_setup_tc(port->app, netdev, type, type_data);
पूर्ण

पूर्णांक nfp_port_set_features(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	काष्ठा nfp_port *port;

	port = nfp_port_from_netdev(netdev);
	अगर (!port)
		वापस 0;

	अगर ((netdev->features & NETIF_F_HW_TC) > (features & NETIF_F_HW_TC) &&
	    port->tc_offload_cnt) अणु
		netdev_err(netdev, "Cannot disable HW TC offload while offloads active\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा nfp_port *
nfp_port_from_id(काष्ठा nfp_pf *pf, क्रमागत nfp_port_type type, अचिन्हित पूर्णांक id)
अणु
	काष्ठा nfp_port *port;

	lockdep_निश्चित_held(&pf->lock);

	अगर (type != NFP_PORT_PHYS_PORT)
		वापस शून्य;

	list_क्रम_each_entry(port, &pf->ports, port_list)
		अगर (port->eth_id == id)
			वापस port;

	वापस शून्य;
पूर्ण

काष्ठा nfp_eth_table_port *__nfp_port_get_eth_port(काष्ठा nfp_port *port)
अणु
	अगर (!port)
		वापस शून्य;
	अगर (port->type != NFP_PORT_PHYS_PORT)
		वापस शून्य;

	वापस port->eth_port;
पूर्ण

काष्ठा nfp_eth_table_port *nfp_port_get_eth_port(काष्ठा nfp_port *port)
अणु
	अगर (!__nfp_port_get_eth_port(port))
		वापस शून्य;

	अगर (test_bit(NFP_PORT_CHANGED, &port->flags))
		अगर (nfp_net_refresh_eth_port(port))
			वापस शून्य;

	वापस __nfp_port_get_eth_port(port);
पूर्ण

पूर्णांक
nfp_port_get_phys_port_name(काष्ठा net_device *netdev, अक्षर *name, माप_प्रकार len)
अणु
	काष्ठा nfp_eth_table_port *eth_port;
	काष्ठा nfp_port *port;
	पूर्णांक n;

	port = nfp_port_from_netdev(netdev);
	अगर (!port)
		वापस -EOPNOTSUPP;

	चयन (port->type) अणु
	हाल NFP_PORT_PHYS_PORT:
		eth_port = __nfp_port_get_eth_port(port);
		अगर (!eth_port)
			वापस -EOPNOTSUPP;

		अगर (!eth_port->is_split)
			n = snम_लिखो(name, len, "p%d", eth_port->label_port);
		अन्यथा
			n = snम_लिखो(name, len, "p%ds%d", eth_port->label_port,
				     eth_port->label_subport);
		अवरोध;
	हाल NFP_PORT_PF_PORT:
		अगर (!port->pf_split)
			n = snम_लिखो(name, len, "pf%d", port->pf_id);
		अन्यथा
			n = snम_लिखो(name, len, "pf%ds%d", port->pf_id,
				     port->pf_split_id);
		अवरोध;
	हाल NFP_PORT_VF_PORT:
		n = snम_लिखो(name, len, "pf%dvf%d", port->pf_id, port->vf_id);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (n >= len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * nfp_port_configure() - helper to set the पूर्णांकerface configured bit
 * @netdev:	net_device instance
 * @configed:	Desired state
 *
 * Helper to set the अगरup/अगरकरोwn state on the PHY only अगर there is a physical
 * पूर्णांकerface associated with the netdev.
 *
 * Return:
 * 0 - configuration successful (or no change);
 * -ERRNO - configuration failed.
 */
पूर्णांक nfp_port_configure(काष्ठा net_device *netdev, bool configed)
अणु
	काष्ठा nfp_eth_table_port *eth_port;
	काष्ठा nfp_port *port;
	पूर्णांक err;

	port = nfp_port_from_netdev(netdev);
	eth_port = __nfp_port_get_eth_port(port);
	अगर (!eth_port)
		वापस 0;
	अगर (port->eth_क्रमced)
		वापस 0;

	err = nfp_eth_set_configured(port->app->cpp, eth_port->index, configed);
	वापस err < 0 && err != -EOPNOTSUPP ? err : 0;
पूर्ण

पूर्णांक nfp_port_init_phy_port(काष्ठा nfp_pf *pf, काष्ठा nfp_app *app,
			   काष्ठा nfp_port *port, अचिन्हित पूर्णांक id)
अणु
	/* Check अगर vNIC has बाह्यal port associated and cfg is OK */
	अगर (!pf->eth_tbl || id >= pf->eth_tbl->count) अणु
		nfp_err(app->cpp,
			"NSP port entries don't match vNICs (no entry %d)\n",
			id);
		वापस -EINVAL;
	पूर्ण
	अगर (pf->eth_tbl->ports[id].override_changed) अणु
		nfp_warn(app->cpp,
			 "Config changed for port #%d, reboot required before port will be operational\n",
			 pf->eth_tbl->ports[id].index);
		port->type = NFP_PORT_INVALID;
		वापस 0;
	पूर्ण

	port->eth_port = &pf->eth_tbl->ports[id];
	port->eth_id = pf->eth_tbl->ports[id].index;
	अगर (pf->mac_stats_mem)
		port->eth_stats =
			pf->mac_stats_mem + port->eth_id * NFP_MAC_STATS_SIZE;

	वापस 0;
पूर्ण

काष्ठा nfp_port *
nfp_port_alloc(काष्ठा nfp_app *app, क्रमागत nfp_port_type type,
	       काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_port *port;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस ERR_PTR(-ENOMEM);

	port->netdev = netdev;
	port->type = type;
	port->app = app;

	list_add_tail(&port->port_list, &app->pf->ports);

	वापस port;
पूर्ण

व्योम nfp_port_मुक्त(काष्ठा nfp_port *port)
अणु
	अगर (!port)
		वापस;
	list_del(&port->port_list);
	kमुक्त(port);
पूर्ण
