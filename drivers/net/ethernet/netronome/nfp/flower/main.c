<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/etherdevice.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/pci.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/devlink.h>
#समावेश <net/dst_metadata.h>

#समावेश "main.h"
#समावेश "../nfpcore/nfp_cpp.h"
#समावेश "../nfpcore/nfp_nffw.h"
#समावेश "../nfpcore/nfp_nsp.h"
#समावेश "../nfp_app.h"
#समावेश "../nfp_main.h"
#समावेश "../nfp_net.h"
#समावेश "../nfp_net_repr.h"
#समावेश "../nfp_port.h"
#समावेश "./cmsg.h"

#घोषणा NFP_FLOWER_ALLOWED_VER 0x0001000000010000UL

#घोषणा NFP_MIN_INT_PORT_ID	1
#घोषणा NFP_MAX_INT_PORT_ID	256

अटल स्थिर अक्षर *nfp_flower_extra_cap(काष्ठा nfp_app *app, काष्ठा nfp_net *nn)
अणु
	वापस "FLOWER";
पूर्ण

अटल क्रमागत devlink_eचयन_mode eचयन_mode_get(काष्ठा nfp_app *app)
अणु
	वापस DEVLINK_ESWITCH_MODE_SWITCHDEV;
पूर्ण

अटल पूर्णांक
nfp_flower_lookup_पूर्णांकernal_port_id(काष्ठा nfp_flower_priv *priv,
				   काष्ठा net_device *netdev)
अणु
	काष्ठा net_device *entry;
	पूर्णांक i, id = 0;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&priv->पूर्णांकernal_ports.port_ids, entry, i)
		अगर (entry == netdev) अणु
			id = i;
			अवरोध;
		पूर्ण
	rcu_पढ़ो_unlock();

	वापस id;
पूर्ण

अटल पूर्णांक
nfp_flower_get_पूर्णांकernal_port_id(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	पूर्णांक id;

	id = nfp_flower_lookup_पूर्णांकernal_port_id(priv, netdev);
	अगर (id > 0)
		वापस id;

	idr_preload(GFP_ATOMIC);
	spin_lock_bh(&priv->पूर्णांकernal_ports.lock);
	id = idr_alloc(&priv->पूर्णांकernal_ports.port_ids, netdev,
		       NFP_MIN_INT_PORT_ID, NFP_MAX_INT_PORT_ID, GFP_ATOMIC);
	spin_unlock_bh(&priv->पूर्णांकernal_ports.lock);
	idr_preload_end();

	वापस id;
पूर्ण

u32 nfp_flower_get_port_id_from_netdev(काष्ठा nfp_app *app,
				       काष्ठा net_device *netdev)
अणु
	पूर्णांक ext_port;

	अगर (nfp_netdev_is_nfp_repr(netdev)) अणु
		वापस nfp_repr_get_port_id(netdev);
	पूर्ण अन्यथा अगर (nfp_flower_पूर्णांकernal_port_can_offload(app, netdev)) अणु
		ext_port = nfp_flower_get_पूर्णांकernal_port_id(app, netdev);
		अगर (ext_port < 0)
			वापस 0;

		वापस nfp_flower_पूर्णांकernal_port_get_port_id(ext_port);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा net_device *
nfp_flower_get_netdev_from_पूर्णांकernal_port_id(काष्ठा nfp_app *app, पूर्णांक port_id)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा net_device *netdev;

	rcu_पढ़ो_lock();
	netdev = idr_find(&priv->पूर्णांकernal_ports.port_ids, port_id);
	rcu_पढ़ो_unlock();

	वापस netdev;
पूर्ण

अटल व्योम
nfp_flower_मुक्त_पूर्णांकernal_port_id(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	पूर्णांक id;

	id = nfp_flower_lookup_पूर्णांकernal_port_id(priv, netdev);
	अगर (!id)
		वापस;

	spin_lock_bh(&priv->पूर्णांकernal_ports.lock);
	idr_हटाओ(&priv->पूर्णांकernal_ports.port_ids, id);
	spin_unlock_bh(&priv->पूर्णांकernal_ports.lock);
पूर्ण

अटल पूर्णांक
nfp_flower_पूर्णांकernal_port_event_handler(काष्ठा nfp_app *app,
				       काष्ठा net_device *netdev,
				       अचिन्हित दीर्घ event)
अणु
	अगर (event == NETDEV_UNREGISTER &&
	    nfp_flower_पूर्णांकernal_port_can_offload(app, netdev))
		nfp_flower_मुक्त_पूर्णांकernal_port_id(app, netdev);

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम nfp_flower_पूर्णांकernal_port_init(काष्ठा nfp_flower_priv *priv)
अणु
	spin_lock_init(&priv->पूर्णांकernal_ports.lock);
	idr_init(&priv->पूर्णांकernal_ports.port_ids);
पूर्ण

अटल व्योम nfp_flower_पूर्णांकernal_port_cleanup(काष्ठा nfp_flower_priv *priv)
अणु
	idr_destroy(&priv->पूर्णांकernal_ports.port_ids);
पूर्ण

अटल काष्ठा nfp_flower_non_repr_priv *
nfp_flower_non_repr_priv_lookup(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_flower_non_repr_priv *entry;

	ASSERT_RTNL();

	list_क्रम_each_entry(entry, &priv->non_repr_priv, list)
		अगर (entry->netdev == netdev)
			वापस entry;

	वापस शून्य;
पूर्ण

व्योम
__nfp_flower_non_repr_priv_get(काष्ठा nfp_flower_non_repr_priv *non_repr_priv)
अणु
	non_repr_priv->ref_count++;
पूर्ण

काष्ठा nfp_flower_non_repr_priv *
nfp_flower_non_repr_priv_get(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_flower_non_repr_priv *entry;

	entry = nfp_flower_non_repr_priv_lookup(app, netdev);
	अगर (entry)
		जाओ inc_ref;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस शून्य;

	entry->netdev = netdev;
	list_add(&entry->list, &priv->non_repr_priv);

inc_ref:
	__nfp_flower_non_repr_priv_get(entry);
	वापस entry;
पूर्ण

व्योम
__nfp_flower_non_repr_priv_put(काष्ठा nfp_flower_non_repr_priv *non_repr_priv)
अणु
	अगर (--non_repr_priv->ref_count)
		वापस;

	list_del(&non_repr_priv->list);
	kमुक्त(non_repr_priv);
पूर्ण

व्योम
nfp_flower_non_repr_priv_put(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_flower_non_repr_priv *entry;

	entry = nfp_flower_non_repr_priv_lookup(app, netdev);
	अगर (!entry)
		वापस;

	__nfp_flower_non_repr_priv_put(entry);
पूर्ण

अटल क्रमागत nfp_repr_type
nfp_flower_repr_get_type_and_port(काष्ठा nfp_app *app, u32 port_id, u8 *port)
अणु
	चयन (FIELD_GET(NFP_FLOWER_CMSG_PORT_TYPE, port_id)) अणु
	हाल NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT:
		*port = FIELD_GET(NFP_FLOWER_CMSG_PORT_PHYS_PORT_NUM,
				  port_id);
		वापस NFP_REPR_TYPE_PHYS_PORT;

	हाल NFP_FLOWER_CMSG_PORT_TYPE_PCIE_PORT:
		*port = FIELD_GET(NFP_FLOWER_CMSG_PORT_VNIC, port_id);
		अगर (FIELD_GET(NFP_FLOWER_CMSG_PORT_VNIC_TYPE, port_id) ==
		    NFP_FLOWER_CMSG_PORT_VNIC_TYPE_PF)
			वापस NFP_REPR_TYPE_PF;
		अन्यथा
			वापस NFP_REPR_TYPE_VF;
	पूर्ण

	वापस __NFP_REPR_TYPE_MAX;
पूर्ण

अटल काष्ठा net_device *
nfp_flower_dev_get(काष्ठा nfp_app *app, u32 port_id, bool *redir_egress)
अणु
	क्रमागत nfp_repr_type repr_type;
	काष्ठा nfp_reprs *reprs;
	u8 port = 0;

	/* Check अगर the port is पूर्णांकernal. */
	अगर (FIELD_GET(NFP_FLOWER_CMSG_PORT_TYPE, port_id) ==
	    NFP_FLOWER_CMSG_PORT_TYPE_OTHER_PORT) अणु
		अगर (redir_egress)
			*redir_egress = true;
		port = FIELD_GET(NFP_FLOWER_CMSG_PORT_PHYS_PORT_NUM, port_id);
		वापस nfp_flower_get_netdev_from_पूर्णांकernal_port_id(app, port);
	पूर्ण

	repr_type = nfp_flower_repr_get_type_and_port(app, port_id, &port);
	अगर (repr_type > NFP_REPR_TYPE_MAX)
		वापस शून्य;

	reprs = rcu_dereference(app->reprs[repr_type]);
	अगर (!reprs)
		वापस शून्य;

	अगर (port >= reprs->num_reprs)
		वापस शून्य;

	वापस rcu_dereference(reprs->reprs[port]);
पूर्ण

अटल पूर्णांक
nfp_flower_reprs_reअगरy(काष्ठा nfp_app *app, क्रमागत nfp_repr_type type,
		       bool exists)
अणु
	काष्ठा nfp_reprs *reprs;
	पूर्णांक i, err, count = 0;

	reprs = rcu_dereference_रक्षित(app->reprs[type],
					  lockdep_is_held(&app->pf->lock));
	अगर (!reprs)
		वापस 0;

	क्रम (i = 0; i < reprs->num_reprs; i++) अणु
		काष्ठा net_device *netdev;

		netdev = nfp_repr_get_locked(app, reprs, i);
		अगर (netdev) अणु
			काष्ठा nfp_repr *repr = netdev_priv(netdev);

			err = nfp_flower_cmsg_portreअगरy(repr, exists);
			अगर (err)
				वापस err;
			count++;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक
nfp_flower_रुको_repr_reअगरy(काष्ठा nfp_app *app, atomic_t *replies, पूर्णांक tot_repl)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	अगर (!tot_repl)
		वापस 0;

	lockdep_निश्चित_held(&app->pf->lock);
	अगर (!रुको_event_समयout(priv->reअगरy_रुको_queue,
				atomic_पढ़ो(replies) >= tot_repl,
				NFP_FL_REPLY_TIMEOUT)) अणु
		nfp_warn(app->cpp, "Not all reprs responded to reify\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_flower_repr_netdev_खोलो(काष्ठा nfp_app *app, काष्ठा nfp_repr *repr)
अणु
	पूर्णांक err;

	err = nfp_flower_cmsg_porपंचांगod(repr, true, repr->netdev->mtu, false);
	अगर (err)
		वापस err;

	netअगर_tx_wake_all_queues(repr->netdev);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_flower_repr_netdev_stop(काष्ठा nfp_app *app, काष्ठा nfp_repr *repr)
अणु
	netअगर_tx_disable(repr->netdev);

	वापस nfp_flower_cmsg_porपंचांगod(repr, false, repr->netdev->mtu, false);
पूर्ण

अटल व्योम
nfp_flower_repr_netdev_clean(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);

	kमुक्त(repr->app_priv);
पूर्ण

अटल व्योम
nfp_flower_repr_netdev_preclean(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	काष्ठा nfp_flower_priv *priv = app->priv;
	atomic_t *replies = &priv->reअगरy_replies;
	पूर्णांक err;

	atomic_set(replies, 0);
	err = nfp_flower_cmsg_portreअगरy(repr, false);
	अगर (err) अणु
		nfp_warn(app->cpp, "Failed to notify firmware about repr destruction\n");
		वापस;
	पूर्ण

	nfp_flower_रुको_repr_reअगरy(app, replies, 1);
पूर्ण

अटल व्योम nfp_flower_sriov_disable(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	अगर (!priv->nn)
		वापस;

	nfp_reprs_clean_and_मुक्त_by_type(app, NFP_REPR_TYPE_VF);
पूर्ण

अटल पूर्णांक
nfp_flower_spawn_vnic_reprs(काष्ठा nfp_app *app,
			    क्रमागत nfp_flower_cmsg_port_vnic_type vnic_type,
			    क्रमागत nfp_repr_type repr_type, अचिन्हित पूर्णांक cnt)
अणु
	u8 nfp_pcie = nfp_cppcore_pcie_unit(app->pf->cpp);
	काष्ठा nfp_flower_priv *priv = app->priv;
	atomic_t *replies = &priv->reअगरy_replies;
	काष्ठा nfp_flower_repr_priv *repr_priv;
	क्रमागत nfp_port_type port_type;
	काष्ठा nfp_repr *nfp_repr;
	काष्ठा nfp_reprs *reprs;
	पूर्णांक i, err, reअगरy_cnt;
	स्थिर u8 queue = 0;

	port_type = repr_type == NFP_REPR_TYPE_PF ? NFP_PORT_PF_PORT :
						    NFP_PORT_VF_PORT;

	reprs = nfp_reprs_alloc(cnt);
	अगर (!reprs)
		वापस -ENOMEM;

	क्रम (i = 0; i < cnt; i++) अणु
		काष्ठा net_device *repr;
		काष्ठा nfp_port *port;
		u32 port_id;

		repr = nfp_repr_alloc(app);
		अगर (!repr) अणु
			err = -ENOMEM;
			जाओ err_reprs_clean;
		पूर्ण

		repr_priv = kzalloc(माप(*repr_priv), GFP_KERNEL);
		अगर (!repr_priv) अणु
			err = -ENOMEM;
			nfp_repr_मुक्त(repr);
			जाओ err_reprs_clean;
		पूर्ण

		nfp_repr = netdev_priv(repr);
		nfp_repr->app_priv = repr_priv;
		repr_priv->nfp_repr = nfp_repr;

		/* For now we only support 1 PF */
		WARN_ON(repr_type == NFP_REPR_TYPE_PF && i);

		port = nfp_port_alloc(app, port_type, repr);
		अगर (IS_ERR(port)) अणु
			err = PTR_ERR(port);
			kमुक्त(repr_priv);
			nfp_repr_मुक्त(repr);
			जाओ err_reprs_clean;
		पूर्ण
		अगर (repr_type == NFP_REPR_TYPE_PF) अणु
			port->pf_id = i;
			port->vnic = priv->nn->dp.ctrl_bar;
		पूर्ण अन्यथा अणु
			port->pf_id = 0;
			port->vf_id = i;
			port->vnic =
				app->pf->vf_cfg_mem + i * NFP_NET_CFG_BAR_SZ;
		पूर्ण

		eth_hw_addr_अक्रमom(repr);

		port_id = nfp_flower_cmsg_pcie_port(nfp_pcie, vnic_type,
						    i, queue);
		err = nfp_repr_init(app, repr,
				    port_id, port, priv->nn->dp.netdev);
		अगर (err) अणु
			kमुक्त(repr_priv);
			nfp_port_मुक्त(port);
			nfp_repr_मुक्त(repr);
			जाओ err_reprs_clean;
		पूर्ण

		RCU_INIT_POINTER(reprs->reprs[i], repr);
		nfp_info(app->cpp, "%s%d Representor(%s) created\n",
			 repr_type == NFP_REPR_TYPE_PF ? "PF" : "VF", i,
			 repr->name);
	पूर्ण

	nfp_app_reprs_set(app, repr_type, reprs);

	atomic_set(replies, 0);
	reअगरy_cnt = nfp_flower_reprs_reअगरy(app, repr_type, true);
	अगर (reअगरy_cnt < 0) अणु
		err = reअगरy_cnt;
		nfp_warn(app->cpp, "Failed to notify firmware about repr creation\n");
		जाओ err_reprs_हटाओ;
	पूर्ण

	err = nfp_flower_रुको_repr_reअगरy(app, replies, reअगरy_cnt);
	अगर (err)
		जाओ err_reprs_हटाओ;

	वापस 0;
err_reprs_हटाओ:
	reprs = nfp_app_reprs_set(app, repr_type, शून्य);
err_reprs_clean:
	nfp_reprs_clean_and_मुक्त(app, reprs);
	वापस err;
पूर्ण

अटल पूर्णांक nfp_flower_sriov_enable(काष्ठा nfp_app *app, पूर्णांक num_vfs)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	अगर (!priv->nn)
		वापस 0;

	वापस nfp_flower_spawn_vnic_reprs(app,
					   NFP_FLOWER_CMSG_PORT_VNIC_TYPE_VF,
					   NFP_REPR_TYPE_VF, num_vfs);
पूर्ण

अटल पूर्णांक
nfp_flower_spawn_phy_reprs(काष्ठा nfp_app *app, काष्ठा nfp_flower_priv *priv)
अणु
	काष्ठा nfp_eth_table *eth_tbl = app->pf->eth_tbl;
	atomic_t *replies = &priv->reअगरy_replies;
	काष्ठा nfp_flower_repr_priv *repr_priv;
	काष्ठा nfp_repr *nfp_repr;
	काष्ठा sk_buff *ctrl_skb;
	काष्ठा nfp_reprs *reprs;
	पूर्णांक err, reअगरy_cnt;
	अचिन्हित पूर्णांक i;

	ctrl_skb = nfp_flower_cmsg_mac_repr_start(app, eth_tbl->count);
	अगर (!ctrl_skb)
		वापस -ENOMEM;

	reprs = nfp_reprs_alloc(eth_tbl->max_index + 1);
	अगर (!reprs) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_ctrl_skb;
	पूर्ण

	क्रम (i = 0; i < eth_tbl->count; i++) अणु
		अचिन्हित पूर्णांक phys_port = eth_tbl->ports[i].index;
		काष्ठा net_device *repr;
		काष्ठा nfp_port *port;
		u32 cmsg_port_id;

		repr = nfp_repr_alloc(app);
		अगर (!repr) अणु
			err = -ENOMEM;
			जाओ err_reprs_clean;
		पूर्ण

		repr_priv = kzalloc(माप(*repr_priv), GFP_KERNEL);
		अगर (!repr_priv) अणु
			err = -ENOMEM;
			nfp_repr_मुक्त(repr);
			जाओ err_reprs_clean;
		पूर्ण

		nfp_repr = netdev_priv(repr);
		nfp_repr->app_priv = repr_priv;
		repr_priv->nfp_repr = nfp_repr;

		port = nfp_port_alloc(app, NFP_PORT_PHYS_PORT, repr);
		अगर (IS_ERR(port)) अणु
			err = PTR_ERR(port);
			kमुक्त(repr_priv);
			nfp_repr_मुक्त(repr);
			जाओ err_reprs_clean;
		पूर्ण
		err = nfp_port_init_phy_port(app->pf, app, port, i);
		अगर (err) अणु
			kमुक्त(repr_priv);
			nfp_port_मुक्त(port);
			nfp_repr_मुक्त(repr);
			जाओ err_reprs_clean;
		पूर्ण

		SET_NETDEV_DEV(repr, &priv->nn->pdev->dev);
		nfp_net_get_mac_addr(app->pf, repr, port);

		cmsg_port_id = nfp_flower_cmsg_phys_port(phys_port);
		err = nfp_repr_init(app, repr,
				    cmsg_port_id, port, priv->nn->dp.netdev);
		अगर (err) अणु
			kमुक्त(repr_priv);
			nfp_port_मुक्त(port);
			nfp_repr_मुक्त(repr);
			जाओ err_reprs_clean;
		पूर्ण

		nfp_flower_cmsg_mac_repr_add(ctrl_skb, i,
					     eth_tbl->ports[i].nbi,
					     eth_tbl->ports[i].base,
					     phys_port);

		RCU_INIT_POINTER(reprs->reprs[phys_port], repr);
		nfp_info(app->cpp, "Phys Port %d Representor(%s) created\n",
			 phys_port, repr->name);
	पूर्ण

	nfp_app_reprs_set(app, NFP_REPR_TYPE_PHYS_PORT, reprs);

	/* The REIFY/MAC_REPR control messages should be sent after the MAC
	 * representors are रेजिस्टरed using nfp_app_reprs_set().  This is
	 * because the firmware may respond with control messages क्रम the
	 * MAC representors, f.e. to provide the driver with inक्रमmation
	 * about their state, and without registration the driver will drop
	 * any such messages.
	 */
	atomic_set(replies, 0);
	reअगरy_cnt = nfp_flower_reprs_reअगरy(app, NFP_REPR_TYPE_PHYS_PORT, true);
	अगर (reअगरy_cnt < 0) अणु
		err = reअगरy_cnt;
		nfp_warn(app->cpp, "Failed to notify firmware about repr creation\n");
		जाओ err_reprs_हटाओ;
	पूर्ण

	err = nfp_flower_रुको_repr_reअगरy(app, replies, reअगरy_cnt);
	अगर (err)
		जाओ err_reprs_हटाओ;

	nfp_ctrl_tx(app->ctrl, ctrl_skb);

	वापस 0;
err_reprs_हटाओ:
	reprs = nfp_app_reprs_set(app, NFP_REPR_TYPE_PHYS_PORT, शून्य);
err_reprs_clean:
	nfp_reprs_clean_and_मुक्त(app, reprs);
err_मुक्त_ctrl_skb:
	kमुक्त_skb(ctrl_skb);
	वापस err;
पूर्ण

अटल पूर्णांक nfp_flower_vnic_alloc(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
				 अचिन्हित पूर्णांक id)
अणु
	अगर (id > 0) अणु
		nfp_warn(app->cpp, "FlowerNIC doesn't support more than one data vNIC\n");
		जाओ err_invalid_port;
	पूर्ण

	eth_hw_addr_अक्रमom(nn->dp.netdev);
	netअगर_keep_dst(nn->dp.netdev);
	nn->vnic_no_name = true;

	वापस 0;

err_invalid_port:
	nn->port = nfp_port_alloc(app, NFP_PORT_INVALID, nn->dp.netdev);
	वापस PTR_ERR_OR_ZERO(nn->port);
पूर्ण

अटल व्योम nfp_flower_vnic_clean(काष्ठा nfp_app *app, काष्ठा nfp_net *nn)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	अगर (app->pf->num_vfs)
		nfp_reprs_clean_and_मुक्त_by_type(app, NFP_REPR_TYPE_VF);
	nfp_reprs_clean_and_मुक्त_by_type(app, NFP_REPR_TYPE_PF);
	nfp_reprs_clean_and_मुक्त_by_type(app, NFP_REPR_TYPE_PHYS_PORT);

	priv->nn = शून्य;
पूर्ण

अटल पूर्णांक nfp_flower_vnic_init(काष्ठा nfp_app *app, काष्ठा nfp_net *nn)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	पूर्णांक err;

	priv->nn = nn;

	err = nfp_flower_spawn_phy_reprs(app, app->priv);
	अगर (err)
		जाओ err_clear_nn;

	err = nfp_flower_spawn_vnic_reprs(app,
					  NFP_FLOWER_CMSG_PORT_VNIC_TYPE_PF,
					  NFP_REPR_TYPE_PF, 1);
	अगर (err)
		जाओ err_destroy_reprs_phy;

	अगर (app->pf->num_vfs) अणु
		err = nfp_flower_spawn_vnic_reprs(app,
						  NFP_FLOWER_CMSG_PORT_VNIC_TYPE_VF,
						  NFP_REPR_TYPE_VF,
						  app->pf->num_vfs);
		अगर (err)
			जाओ err_destroy_reprs_pf;
	पूर्ण

	वापस 0;

err_destroy_reprs_pf:
	nfp_reprs_clean_and_मुक्त_by_type(app, NFP_REPR_TYPE_PF);
err_destroy_reprs_phy:
	nfp_reprs_clean_and_मुक्त_by_type(app, NFP_REPR_TYPE_PHYS_PORT);
err_clear_nn:
	priv->nn = शून्य;
	वापस err;
पूर्ण

अटल व्योम nfp_flower_रुको_host_bit(काष्ठा nfp_app *app)
अणु
	अचिन्हित दीर्घ err_at;
	u64 feat;
	पूर्णांक err;

	/* Wait क्रम HOST_ACK flag bit to propagate */
	err_at = jअगरfies + msecs_to_jअगरfies(100);
	करो अणु
		feat = nfp_rtsym_पढ़ो_le(app->pf->rtbl,
					 "_abi_flower_combined_features_global",
					 &err);
		अगर (समय_is_beक्रमe_eq_jअगरfies(err_at)) अणु
			nfp_warn(app->cpp,
				 "HOST_ACK bit not propagated in FW.\n");
			अवरोध;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण जबतक (!err && !(feat & NFP_FL_FEATS_HOST_ACK));

	अगर (err)
		nfp_warn(app->cpp,
			 "Could not read global features entry from FW\n");
पूर्ण

अटल पूर्णांक nfp_flower_sync_feature_bits(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_flower_priv *app_priv = app->priv;
	पूर्णांक err;

	/* Tell the firmware of the host supported features. */
	err = nfp_rtsym_ग_लिखो_le(app->pf->rtbl, "_abi_flower_host_mask",
				 app_priv->flower_ext_feats |
				 NFP_FL_FEATS_HOST_ACK);
	अगर (!err)
		nfp_flower_रुको_host_bit(app);
	अन्यथा अगर (err != -ENOENT)
		वापस err;

	/* Tell the firmware that the driver supports lag. */
	err = nfp_rtsym_ग_लिखो_le(app->pf->rtbl,
				 "_abi_flower_balance_sync_enable", 1);
	अगर (!err) अणु
		app_priv->flower_en_feats |= NFP_FL_ENABLE_LAG;
		nfp_flower_lag_init(&app_priv->nfp_lag);
	पूर्ण अन्यथा अगर (err == -ENOENT) अणु
		nfp_warn(app->cpp, "LAG not supported by FW.\n");
	पूर्ण अन्यथा अणु
		वापस err;
	पूर्ण

	अगर (app_priv->flower_ext_feats & NFP_FL_FEATS_FLOW_MOD) अणु
		/* Tell the firmware that the driver supports flow merging. */
		err = nfp_rtsym_ग_लिखो_le(app->pf->rtbl,
					 "_abi_flower_merge_hint_enable", 1);
		अगर (!err) अणु
			app_priv->flower_en_feats |= NFP_FL_ENABLE_FLOW_MERGE;
			nfp_flower_पूर्णांकernal_port_init(app_priv);
		पूर्ण अन्यथा अगर (err == -ENOENT) अणु
			nfp_warn(app->cpp,
				 "Flow merge not supported by FW.\n");
		पूर्ण अन्यथा अणु
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		nfp_warn(app->cpp, "Flow mod/merge not supported by FW.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_flower_init(काष्ठा nfp_app *app)
अणु
	u64 version, features, ctx_count, num_mems;
	स्थिर काष्ठा nfp_pf *pf = app->pf;
	काष्ठा nfp_flower_priv *app_priv;
	पूर्णांक err;

	अगर (!pf->eth_tbl) अणु
		nfp_warn(app->cpp, "FlowerNIC requires eth table\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pf->mac_stats_bar) अणु
		nfp_warn(app->cpp, "FlowerNIC requires mac_stats BAR\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pf->vf_cfg_bar) अणु
		nfp_warn(app->cpp, "FlowerNIC requires vf_cfg BAR\n");
		वापस -EINVAL;
	पूर्ण

	version = nfp_rtsym_पढ़ो_le(app->pf->rtbl, "hw_flower_version", &err);
	अगर (err) अणु
		nfp_warn(app->cpp, "FlowerNIC requires hw_flower_version memory symbol\n");
		वापस err;
	पूर्ण

	num_mems = nfp_rtsym_पढ़ो_le(app->pf->rtbl, "CONFIG_FC_HOST_CTX_SPLIT",
				     &err);
	अगर (err) अणु
		nfp_warn(app->cpp,
			 "FlowerNIC: unsupported host context memory: %d\n",
			 err);
		err = 0;
		num_mems = 1;
	पूर्ण

	अगर (!FIELD_FIT(NFP_FL_STAT_ID_MU_NUM, num_mems) || !num_mems) अणु
		nfp_warn(app->cpp,
			 "FlowerNIC: invalid host context memory: %llu\n",
			 num_mems);
		वापस -EINVAL;
	पूर्ण

	ctx_count = nfp_rtsym_पढ़ो_le(app->pf->rtbl, "CONFIG_FC_HOST_CTX_COUNT",
				      &err);
	अगर (err) अणु
		nfp_warn(app->cpp,
			 "FlowerNIC: unsupported host context count: %d\n",
			 err);
		err = 0;
		ctx_count = BIT(17);
	पूर्ण

	/* We need to ensure hardware has enough flower capabilities. */
	अगर (version != NFP_FLOWER_ALLOWED_VER) अणु
		nfp_warn(app->cpp, "FlowerNIC: unsupported firmware version\n");
		वापस -EINVAL;
	पूर्ण

	app_priv = vzalloc(माप(काष्ठा nfp_flower_priv));
	अगर (!app_priv)
		वापस -ENOMEM;

	app_priv->total_mem_units = num_mems;
	app_priv->active_mem_unit = 0;
	app_priv->stats_ring_size = roundup_घात_of_two(ctx_count);
	app->priv = app_priv;
	app_priv->app = app;
	skb_queue_head_init(&app_priv->cmsg_skbs_high);
	skb_queue_head_init(&app_priv->cmsg_skbs_low);
	INIT_WORK(&app_priv->cmsg_work, nfp_flower_cmsg_process_rx);
	init_रुकोqueue_head(&app_priv->reअगरy_रुको_queue);

	init_रुकोqueue_head(&app_priv->mtu_conf.रुको_q);
	spin_lock_init(&app_priv->mtu_conf.lock);

	err = nfp_flower_metadata_init(app, ctx_count, num_mems);
	अगर (err)
		जाओ err_मुक्त_app_priv;

	/* Extract the extra features supported by the firmware. */
	features = nfp_rtsym_पढ़ो_le(app->pf->rtbl,
				     "_abi_flower_extra_features", &err);
	अगर (err)
		app_priv->flower_ext_feats = 0;
	अन्यथा
		app_priv->flower_ext_feats = features & NFP_FL_FEATS_HOST;

	err = nfp_flower_sync_feature_bits(app);
	अगर (err)
		जाओ err_cleanup;

	err = flow_indr_dev_रेजिस्टर(nfp_flower_indr_setup_tc_cb, app);
	अगर (err)
		जाओ err_cleanup;

	अगर (app_priv->flower_ext_feats & NFP_FL_FEATS_VF_RLIM)
		nfp_flower_qos_init(app);

	INIT_LIST_HEAD(&app_priv->indr_block_cb_priv);
	INIT_LIST_HEAD(&app_priv->non_repr_priv);
	app_priv->pre_tun_rule_cnt = 0;

	वापस 0;

err_cleanup:
	अगर (app_priv->flower_en_feats & NFP_FL_ENABLE_LAG)
		nfp_flower_lag_cleanup(&app_priv->nfp_lag);
	nfp_flower_metadata_cleanup(app);
err_मुक्त_app_priv:
	vमुक्त(app->priv);
	वापस err;
पूर्ण

अटल व्योम nfp_flower_clean(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_flower_priv *app_priv = app->priv;

	skb_queue_purge(&app_priv->cmsg_skbs_high);
	skb_queue_purge(&app_priv->cmsg_skbs_low);
	flush_work(&app_priv->cmsg_work);

	अगर (app_priv->flower_ext_feats & NFP_FL_FEATS_VF_RLIM)
		nfp_flower_qos_cleanup(app);

	अगर (app_priv->flower_en_feats & NFP_FL_ENABLE_LAG)
		nfp_flower_lag_cleanup(&app_priv->nfp_lag);

	अगर (app_priv->flower_en_feats & NFP_FL_ENABLE_FLOW_MERGE)
		nfp_flower_पूर्णांकernal_port_cleanup(app_priv);

	nfp_flower_metadata_cleanup(app);
	vमुक्त(app->priv);
	app->priv = शून्य;
पूर्ण

अटल bool nfp_flower_check_ack(काष्ठा nfp_flower_priv *app_priv)
अणु
	bool ret;

	spin_lock_bh(&app_priv->mtu_conf.lock);
	ret = app_priv->mtu_conf.ack;
	spin_unlock_bh(&app_priv->mtu_conf.lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
nfp_flower_repr_change_mtu(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			   पूर्णांक new_mtu)
अणु
	काष्ठा nfp_flower_priv *app_priv = app->priv;
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	पूर्णांक err;

	/* Only need to config FW क्रम physical port MTU change. */
	अगर (repr->port->type != NFP_PORT_PHYS_PORT)
		वापस 0;

	अगर (!(app_priv->flower_ext_feats & NFP_FL_NBI_MTU_SETTING)) अणु
		nfp_err(app->cpp, "Physical port MTU setting not supported\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&app_priv->mtu_conf.lock);
	app_priv->mtu_conf.ack = false;
	app_priv->mtu_conf.requested_val = new_mtu;
	app_priv->mtu_conf.portnum = repr->dst->u.port_info.port_id;
	spin_unlock_bh(&app_priv->mtu_conf.lock);

	err = nfp_flower_cmsg_porपंचांगod(repr, netअगर_carrier_ok(netdev), new_mtu,
				      true);
	अगर (err) अणु
		spin_lock_bh(&app_priv->mtu_conf.lock);
		app_priv->mtu_conf.requested_val = 0;
		spin_unlock_bh(&app_priv->mtu_conf.lock);
		वापस err;
	पूर्ण

	/* Wait क्रम fw to ack the change. */
	अगर (!रुको_event_समयout(app_priv->mtu_conf.रुको_q,
				nfp_flower_check_ack(app_priv),
				NFP_FL_REPLY_TIMEOUT)) अणु
		spin_lock_bh(&app_priv->mtu_conf.lock);
		app_priv->mtu_conf.requested_val = 0;
		spin_unlock_bh(&app_priv->mtu_conf.lock);
		nfp_warn(app->cpp, "MTU change not verified with fw\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_flower_start(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_flower_priv *app_priv = app->priv;
	पूर्णांक err;

	अगर (app_priv->flower_en_feats & NFP_FL_ENABLE_LAG) अणु
		err = nfp_flower_lag_reset(&app_priv->nfp_lag);
		अगर (err)
			वापस err;
	पूर्ण

	वापस nfp_tunnel_config_start(app);
पूर्ण

अटल व्योम nfp_flower_stop(काष्ठा nfp_app *app)
अणु
	nfp_tunnel_config_stop(app);

	flow_indr_dev_unरेजिस्टर(nfp_flower_indr_setup_tc_cb, app,
				 nfp_flower_setup_indr_tc_release);
पूर्ण

अटल पूर्णांक
nfp_flower_netdev_event(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा nfp_flower_priv *app_priv = app->priv;
	पूर्णांक ret;

	अगर (app_priv->flower_en_feats & NFP_FL_ENABLE_LAG) अणु
		ret = nfp_flower_lag_netdev_event(app_priv, netdev, event, ptr);
		अगर (ret & NOTIFY_STOP_MASK)
			वापस ret;
	पूर्ण

	ret = nfp_flower_पूर्णांकernal_port_event_handler(app, netdev, event);
	अगर (ret & NOTIFY_STOP_MASK)
		वापस ret;

	वापस nfp_tunnel_mac_event_handler(app, netdev, event, ptr);
पूर्ण

स्थिर काष्ठा nfp_app_type app_flower = अणु
	.id		= NFP_APP_FLOWER_NIC,
	.name		= "flower",

	.ctrl_cap_mask	= ~0U,
	.ctrl_has_meta	= true,

	.extra_cap	= nfp_flower_extra_cap,

	.init		= nfp_flower_init,
	.clean		= nfp_flower_clean,

	.repr_change_mtu  = nfp_flower_repr_change_mtu,

	.vnic_alloc	= nfp_flower_vnic_alloc,
	.vnic_init	= nfp_flower_vnic_init,
	.vnic_clean	= nfp_flower_vnic_clean,

	.repr_preclean	= nfp_flower_repr_netdev_preclean,
	.repr_clean	= nfp_flower_repr_netdev_clean,

	.repr_खोलो	= nfp_flower_repr_netdev_खोलो,
	.repr_stop	= nfp_flower_repr_netdev_stop,

	.start		= nfp_flower_start,
	.stop		= nfp_flower_stop,

	.netdev_event	= nfp_flower_netdev_event,

	.ctrl_msg_rx	= nfp_flower_cmsg_rx,

	.sriov_enable	= nfp_flower_sriov_enable,
	.sriov_disable	= nfp_flower_sriov_disable,

	.eचयन_mode_get  = eचयन_mode_get,
	.dev_get	= nfp_flower_dev_get,

	.setup_tc	= nfp_flower_setup_tc,
पूर्ण;
