<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */

#समावेश <linux/bitfield.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>

#समावेश "../nfpcore/nfp.h"
#समावेश "../nfpcore/nfp_cpp.h"
#समावेश "../nfpcore/nfp_nsp.h"
#समावेश "../nfp_app.h"
#समावेश "../nfp_main.h"
#समावेश "../nfp_net.h"
#समावेश "../nfp_net_repr.h"
#समावेश "../nfp_port.h"
#समावेश "main.h"

अटल u32 nfp_abm_portid(क्रमागत nfp_repr_type rtype, अचिन्हित पूर्णांक id)
अणु
	वापस FIELD_PREP(NFP_ABM_PORTID_TYPE, rtype) |
	       FIELD_PREP(NFP_ABM_PORTID_ID, id);
पूर्ण

अटल पूर्णांक
nfp_abm_setup_tc(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
		 क्रमागत tc_setup_type type, व्योम *type_data)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	काष्ठा nfp_port *port;

	port = nfp_port_from_netdev(netdev);
	अगर (!port || port->type != NFP_PORT_PF_PORT)
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_ROOT_QDISC:
		वापस nfp_abm_setup_root(netdev, repr->app_priv, type_data);
	हाल TC_SETUP_QDISC_MQ:
		वापस nfp_abm_setup_tc_mq(netdev, repr->app_priv, type_data);
	हाल TC_SETUP_QDISC_RED:
		वापस nfp_abm_setup_tc_red(netdev, repr->app_priv, type_data);
	हाल TC_SETUP_QDISC_GRED:
		वापस nfp_abm_setup_tc_gred(netdev, repr->app_priv, type_data);
	हाल TC_SETUP_BLOCK:
		वापस nfp_abm_setup_cls_block(netdev, repr, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल काष्ठा net_device *
nfp_abm_repr_get(काष्ठा nfp_app *app, u32 port_id, bool *redir_egress)
अणु
	क्रमागत nfp_repr_type rtype;
	काष्ठा nfp_reprs *reprs;
	u8 port;

	rtype = FIELD_GET(NFP_ABM_PORTID_TYPE, port_id);
	port = FIELD_GET(NFP_ABM_PORTID_ID, port_id);

	reprs = rcu_dereference(app->reprs[rtype]);
	अगर (!reprs)
		वापस शून्य;

	अगर (port >= reprs->num_reprs)
		वापस शून्य;

	वापस rcu_dereference(reprs->reprs[port]);
पूर्ण

अटल पूर्णांक
nfp_abm_spawn_repr(काष्ठा nfp_app *app, काष्ठा nfp_abm_link *alink,
		   क्रमागत nfp_port_type ptype)
अणु
	काष्ठा net_device *netdev;
	क्रमागत nfp_repr_type rtype;
	काष्ठा nfp_reprs *reprs;
	काष्ठा nfp_repr *repr;
	काष्ठा nfp_port *port;
	अचिन्हित पूर्णांक txqs;
	पूर्णांक err;

	अगर (ptype == NFP_PORT_PHYS_PORT) अणु
		rtype = NFP_REPR_TYPE_PHYS_PORT;
		txqs = 1;
	पूर्ण अन्यथा अणु
		rtype = NFP_REPR_TYPE_PF;
		txqs = alink->vnic->max_rx_rings;
	पूर्ण

	netdev = nfp_repr_alloc_mqs(app, txqs, 1);
	अगर (!netdev)
		वापस -ENOMEM;
	repr = netdev_priv(netdev);
	repr->app_priv = alink;

	port = nfp_port_alloc(app, ptype, netdev);
	अगर (IS_ERR(port)) अणु
		err = PTR_ERR(port);
		जाओ err_मुक्त_repr;
	पूर्ण

	अगर (ptype == NFP_PORT_PHYS_PORT) अणु
		port->eth_क्रमced = true;
		err = nfp_port_init_phy_port(app->pf, app, port, alink->id);
		अगर (err)
			जाओ err_मुक्त_port;
	पूर्ण अन्यथा अणु
		port->pf_id = alink->abm->pf_id;
		port->pf_split = app->pf->max_data_vnics > 1;
		port->pf_split_id = alink->id;
		port->vnic = alink->vnic->dp.ctrl_bar;
	पूर्ण

	SET_NETDEV_DEV(netdev, &alink->vnic->pdev->dev);
	eth_hw_addr_अक्रमom(netdev);

	err = nfp_repr_init(app, netdev, nfp_abm_portid(rtype, alink->id),
			    port, alink->vnic->dp.netdev);
	अगर (err)
		जाओ err_मुक्त_port;

	reprs = nfp_reprs_get_locked(app, rtype);
	WARN(nfp_repr_get_locked(app, reprs, alink->id), "duplicate repr");
	rtnl_lock();
	rcu_assign_poपूर्णांकer(reprs->reprs[alink->id], netdev);
	rtnl_unlock();

	nfp_info(app->cpp, "%s Port %d Representor(%s) created\n",
		 ptype == NFP_PORT_PF_PORT ? "PCIe" : "Phys",
		 alink->id, netdev->name);

	वापस 0;

err_मुक्त_port:
	nfp_port_मुक्त(port);
err_मुक्त_repr:
	nfp_repr_मुक्त(netdev);
	वापस err;
पूर्ण

अटल व्योम
nfp_abm_समाप्त_repr(काष्ठा nfp_app *app, काष्ठा nfp_abm_link *alink,
		  क्रमागत nfp_repr_type rtype)
अणु
	काष्ठा net_device *netdev;
	काष्ठा nfp_reprs *reprs;

	reprs = nfp_reprs_get_locked(app, rtype);
	netdev = nfp_repr_get_locked(app, reprs, alink->id);
	अगर (!netdev)
		वापस;
	rtnl_lock();
	rcu_assign_poपूर्णांकer(reprs->reprs[alink->id], शून्य);
	rtnl_unlock();
	synchronize_rcu();
	/* Cast to make sure nfp_repr_clean_and_मुक्त() takes a nfp_repr */
	nfp_repr_clean_and_मुक्त((काष्ठा nfp_repr *)netdev_priv(netdev));
पूर्ण

अटल व्योम
nfp_abm_समाप्त_reprs(काष्ठा nfp_abm *abm, काष्ठा nfp_abm_link *alink)
अणु
	nfp_abm_समाप्त_repr(abm->app, alink, NFP_REPR_TYPE_PF);
	nfp_abm_समाप्त_repr(abm->app, alink, NFP_REPR_TYPE_PHYS_PORT);
पूर्ण

अटल व्योम nfp_abm_समाप्त_reprs_all(काष्ठा nfp_abm *abm)
अणु
	काष्ठा nfp_pf *pf = abm->app->pf;
	काष्ठा nfp_net *nn;

	list_क्रम_each_entry(nn, &pf->vnics, vnic_list)
		nfp_abm_समाप्त_reprs(abm, (काष्ठा nfp_abm_link *)nn->app_priv);
पूर्ण

अटल क्रमागत devlink_eचयन_mode nfp_abm_eचयन_mode_get(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_abm *abm = app->priv;

	वापस abm->eचयन_mode;
पूर्ण

अटल पूर्णांक nfp_abm_eचयन_set_legacy(काष्ठा nfp_abm *abm)
अणु
	nfp_abm_समाप्त_reprs_all(abm);
	nfp_abm_ctrl_qm_disable(abm);

	abm->eचयन_mode = DEVLINK_ESWITCH_MODE_LEGACY;
	वापस 0;
पूर्ण

अटल व्योम nfp_abm_eचयन_clean_up(काष्ठा nfp_abm *abm)
अणु
	अगर (abm->eचयन_mode != DEVLINK_ESWITCH_MODE_LEGACY)
		WARN_ON(nfp_abm_eचयन_set_legacy(abm));
पूर्ण

अटल पूर्णांक nfp_abm_eचयन_set_चयनdev(काष्ठा nfp_abm *abm)
अणु
	काष्ठा nfp_app *app = abm->app;
	काष्ठा nfp_pf *pf = app->pf;
	काष्ठा nfp_net *nn;
	पूर्णांक err;

	अगर (!abm->red_support)
		वापस -EOPNOTSUPP;

	err = nfp_abm_ctrl_qm_enable(abm);
	अगर (err)
		वापस err;

	list_क्रम_each_entry(nn, &pf->vnics, vnic_list) अणु
		काष्ठा nfp_abm_link *alink = nn->app_priv;

		err = nfp_abm_spawn_repr(app, alink, NFP_PORT_PHYS_PORT);
		अगर (err)
			जाओ err_समाप्त_all_reprs;

		err = nfp_abm_spawn_repr(app, alink, NFP_PORT_PF_PORT);
		अगर (err)
			जाओ err_समाप्त_all_reprs;
	पूर्ण

	abm->eचयन_mode = DEVLINK_ESWITCH_MODE_SWITCHDEV;
	वापस 0;

err_समाप्त_all_reprs:
	nfp_abm_समाप्त_reprs_all(abm);
	nfp_abm_ctrl_qm_disable(abm);
	वापस err;
पूर्ण

अटल पूर्णांक nfp_abm_eचयन_mode_set(काष्ठा nfp_app *app, u16 mode)
अणु
	काष्ठा nfp_abm *abm = app->priv;

	अगर (abm->eचयन_mode == mode)
		वापस 0;

	चयन (mode) अणु
	हाल DEVLINK_ESWITCH_MODE_LEGACY:
		वापस nfp_abm_eचयन_set_legacy(abm);
	हाल DEVLINK_ESWITCH_MODE_SWITCHDEV:
		वापस nfp_abm_eचयन_set_चयनdev(abm);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम
nfp_abm_vnic_set_mac(काष्ठा nfp_pf *pf, काष्ठा nfp_abm *abm, काष्ठा nfp_net *nn,
		     अचिन्हित पूर्णांक id)
अणु
	काष्ठा nfp_eth_table_port *eth_port = &pf->eth_tbl->ports[id];
	u8 mac_addr[ETH_ALEN];
	काष्ठा nfp_nsp *nsp;
	अक्षर hwinfo[32];
	पूर्णांक err;

	अगर (id > pf->eth_tbl->count) अणु
		nfp_warn(pf->cpp, "No entry for persistent MAC address\n");
		eth_hw_addr_अक्रमom(nn->dp.netdev);
		वापस;
	पूर्ण

	snम_लिखो(hwinfo, माप(hwinfo), "eth%u.mac.pf%u",
		 eth_port->eth_index, abm->pf_id);

	nsp = nfp_nsp_खोलो(pf->cpp);
	अगर (IS_ERR(nsp)) अणु
		nfp_warn(pf->cpp, "Failed to access the NSP for persistent MAC address: %ld\n",
			 PTR_ERR(nsp));
		eth_hw_addr_अक्रमom(nn->dp.netdev);
		वापस;
	पूर्ण

	अगर (!nfp_nsp_has_hwinfo_lookup(nsp)) अणु
		nfp_warn(pf->cpp, "NSP doesn't support PF MAC generation\n");
		eth_hw_addr_अक्रमom(nn->dp.netdev);
		nfp_nsp_बंद(nsp);
		वापस;
	पूर्ण

	err = nfp_nsp_hwinfo_lookup(nsp, hwinfo, माप(hwinfo));
	nfp_nsp_बंद(nsp);
	अगर (err) अणु
		nfp_warn(pf->cpp, "Reading persistent MAC address failed: %d\n",
			 err);
		eth_hw_addr_अक्रमom(nn->dp.netdev);
		वापस;
	पूर्ण

	अगर (माला_पूछो(hwinfo, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
		   &mac_addr[0], &mac_addr[1], &mac_addr[2],
		   &mac_addr[3], &mac_addr[4], &mac_addr[5]) != 6) अणु
		nfp_warn(pf->cpp, "Can't parse persistent MAC address (%s)\n",
			 hwinfo);
		eth_hw_addr_अक्रमom(nn->dp.netdev);
		वापस;
	पूर्ण

	ether_addr_copy(nn->dp.netdev->dev_addr, mac_addr);
	ether_addr_copy(nn->dp.netdev->perm_addr, mac_addr);
पूर्ण

अटल पूर्णांक
nfp_abm_vnic_alloc(काष्ठा nfp_app *app, काष्ठा nfp_net *nn, अचिन्हित पूर्णांक id)
अणु
	काष्ठा nfp_eth_table_port *eth_port = &app->pf->eth_tbl->ports[id];
	काष्ठा nfp_abm *abm = app->priv;
	काष्ठा nfp_abm_link *alink;
	पूर्णांक err;

	alink = kzalloc(माप(*alink), GFP_KERNEL);
	अगर (!alink)
		वापस -ENOMEM;
	nn->app_priv = alink;
	alink->abm = abm;
	alink->vnic = nn;
	alink->id = id;
	alink->total_queues = alink->vnic->max_rx_rings;

	INIT_LIST_HEAD(&alink->dscp_map);

	err = nfp_abm_ctrl_पढ़ो_params(alink);
	अगर (err)
		जाओ err_मुक्त_alink;

	alink->prio_map = kzalloc(abm->prio_map_len, GFP_KERNEL);
	अगर (!alink->prio_map) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_alink;
	पूर्ण

	/* This is a multi-host app, make sure MAC/PHY is up, but करोn't
	 * make the MAC/PHY state follow the state of any of the ports.
	 */
	err = nfp_eth_set_configured(app->cpp, eth_port->index, true);
	अगर (err < 0)
		जाओ err_मुक्त_priomap;

	netअगर_keep_dst(nn->dp.netdev);

	nfp_abm_vnic_set_mac(app->pf, abm, nn, id);
	INIT_RADIX_TREE(&alink->qdiscs, GFP_KERNEL);

	वापस 0;

err_मुक्त_priomap:
	kमुक्त(alink->prio_map);
err_मुक्त_alink:
	kमुक्त(alink);
	वापस err;
पूर्ण

अटल व्योम nfp_abm_vnic_मुक्त(काष्ठा nfp_app *app, काष्ठा nfp_net *nn)
अणु
	काष्ठा nfp_abm_link *alink = nn->app_priv;

	nfp_abm_समाप्त_reprs(alink->abm, alink);
	WARN(!radix_tree_empty(&alink->qdiscs), "left over qdiscs\n");
	kमुक्त(alink->prio_map);
	kमुक्त(alink);
पूर्ण

अटल पूर्णांक nfp_abm_vnic_init(काष्ठा nfp_app *app, काष्ठा nfp_net *nn)
अणु
	काष्ठा nfp_abm_link *alink = nn->app_priv;

	अगर (nfp_abm_has_prio(alink->abm))
		वापस nfp_abm_ctrl_prio_map_update(alink, alink->prio_map);
	वापस 0;
पूर्ण

अटल u64 *
nfp_abm_port_get_stats(काष्ठा nfp_app *app, काष्ठा nfp_port *port, u64 *data)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(port->netdev);
	काष्ठा nfp_abm_link *alink;
	अचिन्हित पूर्णांक i;

	अगर (port->type != NFP_PORT_PF_PORT)
		वापस data;
	alink = repr->app_priv;
	क्रम (i = 0; i < alink->vnic->dp.num_r_vecs; i++) अणु
		*data++ = nfp_abm_ctrl_stat_non_sto(alink, i);
		*data++ = nfp_abm_ctrl_stat_sto(alink, i);
	पूर्ण
	वापस data;
पूर्ण

अटल पूर्णांक
nfp_abm_port_get_stats_count(काष्ठा nfp_app *app, काष्ठा nfp_port *port)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(port->netdev);
	काष्ठा nfp_abm_link *alink;

	अगर (port->type != NFP_PORT_PF_PORT)
		वापस 0;
	alink = repr->app_priv;
	वापस alink->vnic->dp.num_r_vecs * 2;
पूर्ण

अटल u8 *
nfp_abm_port_get_stats_strings(काष्ठा nfp_app *app, काष्ठा nfp_port *port,
			       u8 *data)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(port->netdev);
	काष्ठा nfp_abm_link *alink;
	अचिन्हित पूर्णांक i;

	अगर (port->type != NFP_PORT_PF_PORT)
		वापस data;
	alink = repr->app_priv;
	क्रम (i = 0; i < alink->vnic->dp.num_r_vecs; i++) अणु
		ethtool_प्र_लिखो(&data, "q%u_no_wait", i);
		ethtool_प्र_लिखो(&data, "q%u_delayed", i);
	पूर्ण
	वापस data;
पूर्ण

अटल पूर्णांक nfp_abm_fw_init_reset(काष्ठा nfp_abm *abm)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!abm->red_support)
		वापस 0;

	क्रम (i = 0; i < abm->num_bands * NFP_NET_MAX_RX_RINGS; i++) अणु
		__nfp_abm_ctrl_set_q_lvl(abm, i, NFP_ABM_LVL_अनन्त);
		__nfp_abm_ctrl_set_q_act(abm, i, NFP_ABM_ACT_DROP);
	पूर्ण

	वापस nfp_abm_ctrl_qm_disable(abm);
पूर्ण

अटल पूर्णांक nfp_abm_init(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_pf *pf = app->pf;
	काष्ठा nfp_reprs *reprs;
	काष्ठा nfp_abm *abm;
	पूर्णांक err;

	अगर (!pf->eth_tbl) अणु
		nfp_err(pf->cpp, "ABM NIC requires ETH table\n");
		वापस -EINVAL;
	पूर्ण
	अगर (pf->max_data_vnics != pf->eth_tbl->count) अणु
		nfp_err(pf->cpp, "ETH entries don't match vNICs (%d vs %d)\n",
			pf->max_data_vnics, pf->eth_tbl->count);
		वापस -EINVAL;
	पूर्ण
	अगर (!pf->mac_stats_bar) अणु
		nfp_warn(app->cpp, "ABM NIC requires mac_stats symbol\n");
		वापस -EINVAL;
	पूर्ण

	abm = kzalloc(माप(*abm), GFP_KERNEL);
	अगर (!abm)
		वापस -ENOMEM;
	app->priv = abm;
	abm->app = app;

	err = nfp_abm_ctrl_find_addrs(abm);
	अगर (err)
		जाओ err_मुक्त_abm;

	err = -ENOMEM;
	abm->num_thresholds = array_size(abm->num_bands, NFP_NET_MAX_RX_RINGS);
	abm->threshold_undef = biपंचांगap_zalloc(abm->num_thresholds, GFP_KERNEL);
	अगर (!abm->threshold_undef)
		जाओ err_मुक्त_abm;

	abm->thresholds = kvसुस्मृति(abm->num_thresholds,
				   माप(*abm->thresholds), GFP_KERNEL);
	अगर (!abm->thresholds)
		जाओ err_मुक्त_thresh_umap;

	abm->actions = kvसुस्मृति(abm->num_thresholds, माप(*abm->actions),
				GFP_KERNEL);
	अगर (!abm->actions)
		जाओ err_मुक्त_thresh;

	/* We start in legacy mode, make sure advanced queuing is disabled */
	err = nfp_abm_fw_init_reset(abm);
	अगर (err)
		जाओ err_मुक्त_act;

	err = -ENOMEM;
	reprs = nfp_reprs_alloc(pf->max_data_vnics);
	अगर (!reprs)
		जाओ err_मुक्त_act;
	RCU_INIT_POINTER(app->reprs[NFP_REPR_TYPE_PHYS_PORT], reprs);

	reprs = nfp_reprs_alloc(pf->max_data_vnics);
	अगर (!reprs)
		जाओ err_मुक्त_phys;
	RCU_INIT_POINTER(app->reprs[NFP_REPR_TYPE_PF], reprs);

	वापस 0;

err_मुक्त_phys:
	nfp_reprs_clean_and_मुक्त_by_type(app, NFP_REPR_TYPE_PHYS_PORT);
err_मुक्त_act:
	kvमुक्त(abm->actions);
err_मुक्त_thresh:
	kvमुक्त(abm->thresholds);
err_मुक्त_thresh_umap:
	biपंचांगap_मुक्त(abm->threshold_undef);
err_मुक्त_abm:
	kमुक्त(abm);
	app->priv = शून्य;
	वापस err;
पूर्ण

अटल व्योम nfp_abm_clean(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_abm *abm = app->priv;

	nfp_abm_eचयन_clean_up(abm);
	nfp_reprs_clean_and_मुक्त_by_type(app, NFP_REPR_TYPE_PF);
	nfp_reprs_clean_and_मुक्त_by_type(app, NFP_REPR_TYPE_PHYS_PORT);
	biपंचांगap_मुक्त(abm->threshold_undef);
	kvमुक्त(abm->actions);
	kvमुक्त(abm->thresholds);
	kमुक्त(abm);
	app->priv = शून्य;
पूर्ण

स्थिर काष्ठा nfp_app_type app_abm = अणु
	.id		= NFP_APP_ACTIVE_BUFFER_MGMT_NIC,
	.name		= "abm",

	.init		= nfp_abm_init,
	.clean		= nfp_abm_clean,

	.vnic_alloc	= nfp_abm_vnic_alloc,
	.vnic_मुक्त	= nfp_abm_vnic_मुक्त,
	.vnic_init	= nfp_abm_vnic_init,

	.port_get_stats		= nfp_abm_port_get_stats,
	.port_get_stats_count	= nfp_abm_port_get_stats_count,
	.port_get_stats_strings	= nfp_abm_port_get_stats_strings,

	.setup_tc	= nfp_abm_setup_tc,

	.eचयन_mode_get	= nfp_abm_eचयन_mode_get,
	.eचयन_mode_set	= nfp_abm_eचयन_mode_set,

	.dev_get	= nfp_abm_repr_get,
पूर्ण;
