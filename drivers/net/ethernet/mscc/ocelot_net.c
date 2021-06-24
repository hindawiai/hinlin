<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Microsemi Ocelot Switch driver
 *
 * This contains glue logic between the चयनdev driver operations and the
 * mscc_ocelot_चयन_lib.
 *
 * Copyright (c) 2017, 2019 Microsemi Corporation
 * Copyright 2020-2021 NXP Semiconductors
 */

#समावेश <linux/अगर_bridge.h>
#समावेश <net/pkt_cls.h>
#समावेश "ocelot.h"
#समावेश "ocelot_vcap.h"

अटल काष्ठा ocelot *devlink_port_to_ocelot(काष्ठा devlink_port *dlp)
अणु
	वापस devlink_priv(dlp->devlink);
पूर्ण

अटल पूर्णांक devlink_port_to_port(काष्ठा devlink_port *dlp)
अणु
	काष्ठा ocelot *ocelot = devlink_port_to_ocelot(dlp);

	वापस dlp - ocelot->devlink_ports;
पूर्ण

अटल पूर्णांक ocelot_devlink_sb_pool_get(काष्ठा devlink *dl,
				      अचिन्हित पूर्णांक sb_index, u16 pool_index,
				      काष्ठा devlink_sb_pool_info *pool_info)
अणु
	काष्ठा ocelot *ocelot = devlink_priv(dl);

	वापस ocelot_sb_pool_get(ocelot, sb_index, pool_index, pool_info);
पूर्ण

अटल पूर्णांक ocelot_devlink_sb_pool_set(काष्ठा devlink *dl, अचिन्हित पूर्णांक sb_index,
				      u16 pool_index, u32 size,
				      क्रमागत devlink_sb_threshold_type threshold_type,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot *ocelot = devlink_priv(dl);

	वापस ocelot_sb_pool_set(ocelot, sb_index, pool_index, size,
				  threshold_type, extack);
पूर्ण

अटल पूर्णांक ocelot_devlink_sb_port_pool_get(काष्ठा devlink_port *dlp,
					   अचिन्हित पूर्णांक sb_index, u16 pool_index,
					   u32 *p_threshold)
अणु
	काष्ठा ocelot *ocelot = devlink_port_to_ocelot(dlp);
	पूर्णांक port = devlink_port_to_port(dlp);

	वापस ocelot_sb_port_pool_get(ocelot, port, sb_index, pool_index,
				       p_threshold);
पूर्ण

अटल पूर्णांक ocelot_devlink_sb_port_pool_set(काष्ठा devlink_port *dlp,
					   अचिन्हित पूर्णांक sb_index, u16 pool_index,
					   u32 threshold,
					   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot *ocelot = devlink_port_to_ocelot(dlp);
	पूर्णांक port = devlink_port_to_port(dlp);

	वापस ocelot_sb_port_pool_set(ocelot, port, sb_index, pool_index,
				       threshold, extack);
पूर्ण

अटल पूर्णांक
ocelot_devlink_sb_tc_pool_bind_get(काष्ठा devlink_port *dlp,
				   अचिन्हित पूर्णांक sb_index, u16 tc_index,
				   क्रमागत devlink_sb_pool_type pool_type,
				   u16 *p_pool_index, u32 *p_threshold)
अणु
	काष्ठा ocelot *ocelot = devlink_port_to_ocelot(dlp);
	पूर्णांक port = devlink_port_to_port(dlp);

	वापस ocelot_sb_tc_pool_bind_get(ocelot, port, sb_index, tc_index,
					  pool_type, p_pool_index,
					  p_threshold);
पूर्ण

अटल पूर्णांक
ocelot_devlink_sb_tc_pool_bind_set(काष्ठा devlink_port *dlp,
				   अचिन्हित पूर्णांक sb_index, u16 tc_index,
				   क्रमागत devlink_sb_pool_type pool_type,
				   u16 pool_index, u32 threshold,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot *ocelot = devlink_port_to_ocelot(dlp);
	पूर्णांक port = devlink_port_to_port(dlp);

	वापस ocelot_sb_tc_pool_bind_set(ocelot, port, sb_index, tc_index,
					  pool_type, pool_index, threshold,
					  extack);
पूर्ण

अटल पूर्णांक ocelot_devlink_sb_occ_snapshot(काष्ठा devlink *dl,
					  अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा ocelot *ocelot = devlink_priv(dl);

	वापस ocelot_sb_occ_snapshot(ocelot, sb_index);
पूर्ण

अटल पूर्णांक ocelot_devlink_sb_occ_max_clear(काष्ठा devlink *dl,
					   अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा ocelot *ocelot = devlink_priv(dl);

	वापस ocelot_sb_occ_max_clear(ocelot, sb_index);
पूर्ण

अटल पूर्णांक ocelot_devlink_sb_occ_port_pool_get(काष्ठा devlink_port *dlp,
					       अचिन्हित पूर्णांक sb_index,
					       u16 pool_index, u32 *p_cur,
					       u32 *p_max)
अणु
	काष्ठा ocelot *ocelot = devlink_port_to_ocelot(dlp);
	पूर्णांक port = devlink_port_to_port(dlp);

	वापस ocelot_sb_occ_port_pool_get(ocelot, port, sb_index, pool_index,
					   p_cur, p_max);
पूर्ण

अटल पूर्णांक
ocelot_devlink_sb_occ_tc_port_bind_get(काष्ठा devlink_port *dlp,
				       अचिन्हित पूर्णांक sb_index, u16 tc_index,
				       क्रमागत devlink_sb_pool_type pool_type,
				       u32 *p_cur, u32 *p_max)
अणु
	काष्ठा ocelot *ocelot = devlink_port_to_ocelot(dlp);
	पूर्णांक port = devlink_port_to_port(dlp);

	वापस ocelot_sb_occ_tc_port_bind_get(ocelot, port, sb_index,
					      tc_index, pool_type,
					      p_cur, p_max);
पूर्ण

स्थिर काष्ठा devlink_ops ocelot_devlink_ops = अणु
	.sb_pool_get			= ocelot_devlink_sb_pool_get,
	.sb_pool_set			= ocelot_devlink_sb_pool_set,
	.sb_port_pool_get		= ocelot_devlink_sb_port_pool_get,
	.sb_port_pool_set		= ocelot_devlink_sb_port_pool_set,
	.sb_tc_pool_bind_get		= ocelot_devlink_sb_tc_pool_bind_get,
	.sb_tc_pool_bind_set		= ocelot_devlink_sb_tc_pool_bind_set,
	.sb_occ_snapshot		= ocelot_devlink_sb_occ_snapshot,
	.sb_occ_max_clear		= ocelot_devlink_sb_occ_max_clear,
	.sb_occ_port_pool_get		= ocelot_devlink_sb_occ_port_pool_get,
	.sb_occ_tc_port_bind_get	= ocelot_devlink_sb_occ_tc_port_bind_get,
पूर्ण;

पूर्णांक ocelot_port_devlink_init(काष्ठा ocelot *ocelot, पूर्णांक port,
			     क्रमागत devlink_port_flavour flavour)
अणु
	काष्ठा devlink_port *dlp = &ocelot->devlink_ports[port];
	पूर्णांक id_len = माप(ocelot->base_mac);
	काष्ठा devlink *dl = ocelot->devlink;
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;

	स_नकल(attrs.चयन_id.id, &ocelot->base_mac, id_len);
	attrs.चयन_id.id_len = id_len;
	attrs.phys.port_number = port;
	attrs.flavour = flavour;

	devlink_port_attrs_set(dlp, &attrs);

	वापस devlink_port_रेजिस्टर(dl, dlp, port);
पूर्ण

व्योम ocelot_port_devlink_tearकरोwn(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	काष्ठा devlink_port *dlp = &ocelot->devlink_ports[port];

	devlink_port_unरेजिस्टर(dlp);
पूर्ण

अटल काष्ठा devlink_port *ocelot_get_devlink_port(काष्ठा net_device *dev)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	वापस &ocelot->devlink_ports[port];
पूर्ण

पूर्णांक ocelot_setup_tc_cls_flower(काष्ठा ocelot_port_निजी *priv,
			       काष्ठा flow_cls_offload *f,
			       bool ingress)
अणु
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	अगर (!ingress)
		वापस -EOPNOTSUPP;

	चयन (f->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस ocelot_cls_flower_replace(ocelot, port, f, ingress);
	हाल FLOW_CLS_DESTROY:
		वापस ocelot_cls_flower_destroy(ocelot, port, f, ingress);
	हाल FLOW_CLS_STATS:
		वापस ocelot_cls_flower_stats(ocelot, port, f, ingress);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ocelot_setup_tc_cls_matchall(काष्ठा ocelot_port_निजी *priv,
					काष्ठा tc_cls_matchall_offload *f,
					bool ingress)
अणु
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	काष्ठा ocelot_policer pol = अणु 0 पूर्ण;
	काष्ठा flow_action_entry *action;
	पूर्णांक port = priv->chip_port;
	पूर्णांक err;

	अगर (!ingress) अणु
		NL_SET_ERR_MSG_MOD(extack, "Only ingress is supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (f->command) अणु
	हाल TC_CLSMATCHALL_REPLACE:
		अगर (!flow_offload_has_one_action(&f->rule->action)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Only one action is supported");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (priv->tc.block_shared) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Rate limit is not supported on shared blocks");
			वापस -EOPNOTSUPP;
		पूर्ण

		action = &f->rule->action.entries[0];

		अगर (action->id != FLOW_ACTION_POLICE) अणु
			NL_SET_ERR_MSG_MOD(extack, "Unsupported action");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (priv->tc.police_id && priv->tc.police_id != f->cookie) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Only one policer per port is supported");
			वापस -EEXIST;
		पूर्ण

		अगर (action->police.rate_pkt_ps) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "QoS offload not support packets per second");
			वापस -EOPNOTSUPP;
		पूर्ण

		pol.rate = (u32)भाग_u64(action->police.rate_bytes_ps, 1000) * 8;
		pol.burst = action->police.burst;

		err = ocelot_port_policer_add(ocelot, port, &pol);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Could not add policer");
			वापस err;
		पूर्ण

		priv->tc.police_id = f->cookie;
		priv->tc.offload_cnt++;
		वापस 0;
	हाल TC_CLSMATCHALL_DESTROY:
		अगर (priv->tc.police_id != f->cookie)
			वापस -ENOENT;

		err = ocelot_port_policer_del(ocelot, port);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Could not delete policer");
			वापस err;
		पूर्ण
		priv->tc.police_id = 0;
		priv->tc.offload_cnt--;
		वापस 0;
	हाल TC_CLSMATCHALL_STATS:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ocelot_setup_tc_block_cb(क्रमागत tc_setup_type type,
				    व्योम *type_data,
				    व्योम *cb_priv, bool ingress)
अणु
	काष्ठा ocelot_port_निजी *priv = cb_priv;

	अगर (!tc_cls_can_offload_and_chain0(priv->dev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSMATCHALL:
		वापस ocelot_setup_tc_cls_matchall(priv, type_data, ingress);
	हाल TC_SETUP_CLSFLOWER:
		वापस ocelot_setup_tc_cls_flower(priv, type_data, ingress);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ocelot_setup_tc_block_cb_ig(क्रमागत tc_setup_type type,
				       व्योम *type_data,
				       व्योम *cb_priv)
अणु
	वापस ocelot_setup_tc_block_cb(type, type_data,
					cb_priv, true);
पूर्ण

अटल पूर्णांक ocelot_setup_tc_block_cb_eg(क्रमागत tc_setup_type type,
				       व्योम *type_data,
				       व्योम *cb_priv)
अणु
	वापस ocelot_setup_tc_block_cb(type, type_data,
					cb_priv, false);
पूर्ण

अटल LIST_HEAD(ocelot_block_cb_list);

अटल पूर्णांक ocelot_setup_tc_block(काष्ठा ocelot_port_निजी *priv,
				 काष्ठा flow_block_offload *f)
अणु
	काष्ठा flow_block_cb *block_cb;
	flow_setup_cb_t *cb;

	अगर (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS) अणु
		cb = ocelot_setup_tc_block_cb_ig;
		priv->tc.block_shared = f->block_shared;
	पूर्ण अन्यथा अगर (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS) अणु
		cb = ocelot_setup_tc_block_cb_eg;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	f->driver_block_list = &ocelot_block_cb_list;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		अगर (flow_block_cb_is_busy(cb, priv, &ocelot_block_cb_list))
			वापस -EBUSY;

		block_cb = flow_block_cb_alloc(cb, priv, priv, शून्य);
		अगर (IS_ERR(block_cb))
			वापस PTR_ERR(block_cb);

		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, f->driver_block_list);
		वापस 0;
	हाल FLOW_BLOCK_UNBIND:
		block_cb = flow_block_cb_lookup(f->block, cb, priv);
		अगर (!block_cb)
			वापस -ENOENT;

		flow_block_cb_हटाओ(block_cb, f);
		list_del(&block_cb->driver_list);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ocelot_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			   व्योम *type_data)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस ocelot_setup_tc_block(priv, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ocelot_port_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	ocelot_adjust_link(ocelot, port, dev->phydev);
पूर्ण

अटल पूर्णांक ocelot_vlan_vid_prepare(काष्ठा net_device *dev, u16 vid, bool pvid,
				   bool untagged)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;

	वापस ocelot_vlan_prepare(ocelot, port, vid, pvid, untagged);
पूर्ण

अटल पूर्णांक ocelot_vlan_vid_add(काष्ठा net_device *dev, u16 vid, bool pvid,
			       bool untagged)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;
	पूर्णांक ret;

	ret = ocelot_vlan_add(ocelot, port, vid, pvid, untagged);
	अगर (ret)
		वापस ret;

	/* Add the port MAC address to with the right VLAN inक्रमmation */
	ocelot_mact_learn(ocelot, PGID_CPU, dev->dev_addr, vid,
			  ENTRYTYPE_LOCKED);

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_vlan_vid_del(काष्ठा net_device *dev, u16 vid)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;
	पूर्णांक ret;

	/* 8021q हटाओs VID 0 on module unload क्रम all पूर्णांकerfaces
	 * with VLAN filtering feature. We need to keep it to receive
	 * untagged traffic.
	 */
	अगर (vid == 0)
		वापस 0;

	ret = ocelot_vlan_del(ocelot, port, vid);
	अगर (ret)
		वापस ret;

	/* Del the port MAC address to with the right VLAN inक्रमmation */
	ocelot_mact_क्रमget(ocelot, dev->dev_addr, vid);

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_port_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;
	पूर्णांक err;

	अगर (priv->serdes) अणु
		err = phy_set_mode_ext(priv->serdes, PHY_MODE_ETHERNET,
				       ocelot_port->phy_mode);
		अगर (err) अणु
			netdev_err(dev, "Could not set mode of SerDes\n");
			वापस err;
		पूर्ण
	पूर्ण

	err = phy_connect_direct(dev, priv->phy, &ocelot_port_adjust_link,
				 ocelot_port->phy_mode);
	अगर (err) अणु
		netdev_err(dev, "Could not attach to PHY\n");
		वापस err;
	पूर्ण

	dev->phydev = priv->phy;

	phy_attached_info(priv->phy);
	phy_start(priv->phy);

	ocelot_port_enable(ocelot, port, priv->phy);

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_port_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	phy_disconnect(priv->phy);

	dev->phydev = शून्य;

	ocelot_port_disable(ocelot, port);

	वापस 0;
पूर्ण

अटल netdev_tx_t ocelot_port_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;
	u32 rew_op = 0;

	अगर (!ocelot_can_inject(ocelot, 0))
		वापस NETDEV_TX_BUSY;

	/* Check अगर बारtamping is needed */
	अगर (ocelot->ptp && (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) अणु
		काष्ठा sk_buff *clone = शून्य;

		अगर (ocelot_port_txtstamp_request(ocelot, port, skb, &clone)) अणु
			kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण

		अगर (clone)
			OCELOT_SKB_CB(skb)->clone = clone;

		rew_op = ocelot_ptp_rew_op(skb);
	पूर्ण

	ocelot_port_inject_frame(ocelot, port, 0, rew_op, skb);

	kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

क्रमागत ocelot_action_type अणु
	OCELOT_MACT_LEARN,
	OCELOT_MACT_FORGET,
पूर्ण;

काष्ठा ocelot_mact_work_ctx अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ocelot *ocelot;
	क्रमागत ocelot_action_type type;
	जोड़ अणु
		/* OCELOT_MACT_LEARN */
		काष्ठा अणु
			अचिन्हित अक्षर addr[ETH_ALEN];
			u16 vid;
			क्रमागत macaccess_entry_type entry_type;
			पूर्णांक pgid;
		पूर्ण learn;
		/* OCELOT_MACT_FORGET */
		काष्ठा अणु
			अचिन्हित अक्षर addr[ETH_ALEN];
			u16 vid;
		पूर्ण क्रमget;
	पूर्ण;
पूर्ण;

#घोषणा ocelot_work_to_ctx(x) \
	container_of((x), काष्ठा ocelot_mact_work_ctx, work)

अटल व्योम ocelot_mact_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ocelot_mact_work_ctx *w = ocelot_work_to_ctx(work);
	काष्ठा ocelot *ocelot = w->ocelot;

	चयन (w->type) अणु
	हाल OCELOT_MACT_LEARN:
		ocelot_mact_learn(ocelot, w->learn.pgid, w->learn.addr,
				  w->learn.vid, w->learn.entry_type);
		अवरोध;
	हाल OCELOT_MACT_FORGET:
		ocelot_mact_क्रमget(ocelot, w->क्रमget.addr, w->क्रमget.vid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kमुक्त(w);
पूर्ण

अटल पूर्णांक ocelot_enqueue_mact_action(काष्ठा ocelot *ocelot,
				      स्थिर काष्ठा ocelot_mact_work_ctx *ctx)
अणु
	काष्ठा ocelot_mact_work_ctx *w = kmemdup(ctx, माप(*w), GFP_ATOMIC);

	अगर (!w)
		वापस -ENOMEM;

	w->ocelot = ocelot;
	INIT_WORK(&w->work, ocelot_mact_work);
	queue_work(ocelot->owq, &w->work);

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_mc_unsync(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	काष्ठा ocelot_mact_work_ctx w;

	ether_addr_copy(w.क्रमget.addr, addr);
	w.क्रमget.vid = ocelot_port->pvid_vlan.vid;
	w.type = OCELOT_MACT_FORGET;

	वापस ocelot_enqueue_mact_action(ocelot, &w);
पूर्ण

अटल पूर्णांक ocelot_mc_sync(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	काष्ठा ocelot_mact_work_ctx w;

	ether_addr_copy(w.learn.addr, addr);
	w.learn.vid = ocelot_port->pvid_vlan.vid;
	w.learn.pgid = PGID_CPU;
	w.learn.entry_type = ENTRYTYPE_LOCKED;
	w.type = OCELOT_MACT_LEARN;

	वापस ocelot_enqueue_mact_action(ocelot, &w);
पूर्ण

अटल व्योम ocelot_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	u32 val;
	पूर्णांक i;

	/* This करोesn't handle promiscuous mode because the bridge core is
	 * setting IFF_PROMISC on all slave पूर्णांकerfaces and all frames would be
	 * क्रमwarded to the CPU port.
	 */
	val = GENMASK(ocelot->num_phys_ports - 1, 0);
	क्रम_each_nonreserved_multicast_dest_pgid(ocelot, i)
		ocelot_ग_लिखो_rix(ocelot, val, ANA_PGID_PGID, i);

	__dev_mc_sync(dev, ocelot_mc_sync, ocelot_mc_unsync);
पूर्ण

अटल पूर्णांक ocelot_port_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	स्थिर काष्ठा sockaddr *addr = p;

	/* Learn the new net device MAC address in the mac table. */
	ocelot_mact_learn(ocelot, PGID_CPU, addr->sa_data,
			  ocelot_port->pvid_vlan.vid, ENTRYTYPE_LOCKED);
	/* Then क्रमget the previous one. */
	ocelot_mact_क्रमget(ocelot, dev->dev_addr, ocelot_port->pvid_vlan.vid);

	ether_addr_copy(dev->dev_addr, addr->sa_data);
	वापस 0;
पूर्ण

अटल व्योम ocelot_get_stats64(काष्ठा net_device *dev,
			       काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	/* Configure the port to पढ़ो the stats from */
	ocelot_ग_लिखो(ocelot, SYS_STAT_CFG_STAT_VIEW(port),
		     SYS_STAT_CFG);

	/* Get Rx stats */
	stats->rx_bytes = ocelot_पढ़ो(ocelot, SYS_COUNT_RX_OCTETS);
	stats->rx_packets = ocelot_पढ़ो(ocelot, SYS_COUNT_RX_SHORTS) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_RX_FRAGMENTS) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_RX_JABBERS) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_RX_LONGS) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_RX_64) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_RX_65_127) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_RX_128_255) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_RX_256_1023) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_RX_1024_1526) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_RX_1527_MAX);
	stats->multicast = ocelot_पढ़ो(ocelot, SYS_COUNT_RX_MULTICAST);
	stats->rx_dropped = dev->stats.rx_dropped;

	/* Get Tx stats */
	stats->tx_bytes = ocelot_पढ़ो(ocelot, SYS_COUNT_TX_OCTETS);
	stats->tx_packets = ocelot_पढ़ो(ocelot, SYS_COUNT_TX_64) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_TX_65_127) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_TX_128_511) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_TX_512_1023) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_TX_1024_1526) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_TX_1527_MAX);
	stats->tx_dropped = ocelot_पढ़ो(ocelot, SYS_COUNT_TX_DROPS) +
			    ocelot_पढ़ो(ocelot, SYS_COUNT_TX_AGING);
	stats->collisions = ocelot_पढ़ो(ocelot, SYS_COUNT_TX_COLLISION);
पूर्ण

अटल पूर्णांक ocelot_port_fdb_add(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			       काष्ठा net_device *dev,
			       स्थिर अचिन्हित अक्षर *addr,
			       u16 vid, u16 flags,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	वापस ocelot_fdb_add(ocelot, port, addr, vid);
पूर्ण

अटल पूर्णांक ocelot_port_fdb_del(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			       काष्ठा net_device *dev,
			       स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	वापस ocelot_fdb_del(ocelot, port, addr, vid);
पूर्ण

अटल पूर्णांक ocelot_port_fdb_dump(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb,
				काष्ठा net_device *dev,
				काष्ठा net_device *filter_dev, पूर्णांक *idx)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	काष्ठा ocelot_dump_ctx dump = अणु
		.dev = dev,
		.skb = skb,
		.cb = cb,
		.idx = *idx,
	पूर्ण;
	पूर्णांक port = priv->chip_port;
	पूर्णांक ret;

	ret = ocelot_fdb_dump(ocelot, port, ocelot_port_fdb_करो_dump, &dump);

	*idx = dump.idx;

	वापस ret;
पूर्ण

अटल पूर्णांक ocelot_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto,
				  u16 vid)
अणु
	वापस ocelot_vlan_vid_add(dev, vid, false, false);
पूर्ण

अटल पूर्णांक ocelot_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto,
				   u16 vid)
अणु
	वापस ocelot_vlan_vid_del(dev, vid);
पूर्ण

अटल व्योम ocelot_vlan_mode(काष्ठा ocelot *ocelot, पूर्णांक port,
			     netdev_features_t features)
अणु
	u32 val;

	/* Filtering */
	val = ocelot_पढ़ो(ocelot, ANA_VLANMASK);
	अगर (features & NETIF_F_HW_VLAN_CTAG_FILTER)
		val |= BIT(port);
	अन्यथा
		val &= ~BIT(port);
	ocelot_ग_लिखो(ocelot, val, ANA_VLANMASK);
पूर्ण

अटल पूर्णांक ocelot_set_features(काष्ठा net_device *dev,
			       netdev_features_t features)
अणु
	netdev_features_t changed = dev->features ^ features;
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	अगर ((dev->features & NETIF_F_HW_TC) > (features & NETIF_F_HW_TC) &&
	    priv->tc.offload_cnt) अणु
		netdev_err(dev,
			   "Cannot disable HW TC offload while offloads active\n");
		वापस -EBUSY;
	पूर्ण

	अगर (changed & NETIF_F_HW_VLAN_CTAG_FILTER)
		ocelot_vlan_mode(ocelot, port, features);

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	/* If the attached PHY device isn't capable of बारtamping operations,
	 * use our own (when possible).
	 */
	अगर (!phy_has_hwtstamp(dev->phydev) && ocelot->ptp) अणु
		चयन (cmd) अणु
		हाल SIOCSHWTSTAMP:
			वापस ocelot_hwstamp_set(ocelot, port, अगरr);
		हाल SIOCGHWTSTAMP:
			वापस ocelot_hwstamp_get(ocelot, port, अगरr);
		पूर्ण
	पूर्ण

	वापस phy_mii_ioctl(dev->phydev, अगरr, cmd);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ocelot_port_netdev_ops = अणु
	.nकरो_खोलो			= ocelot_port_खोलो,
	.nकरो_stop			= ocelot_port_stop,
	.nकरो_start_xmit			= ocelot_port_xmit,
	.nकरो_set_rx_mode		= ocelot_set_rx_mode,
	.nकरो_set_mac_address		= ocelot_port_set_mac_address,
	.nकरो_get_stats64		= ocelot_get_stats64,
	.nकरो_fdb_add			= ocelot_port_fdb_add,
	.nकरो_fdb_del			= ocelot_port_fdb_del,
	.nकरो_fdb_dump			= ocelot_port_fdb_dump,
	.nकरो_vlan_rx_add_vid		= ocelot_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid		= ocelot_vlan_rx_समाप्त_vid,
	.nकरो_set_features		= ocelot_set_features,
	.nकरो_setup_tc			= ocelot_setup_tc,
	.nकरो_करो_ioctl			= ocelot_ioctl,
	.nकरो_get_devlink_port		= ocelot_get_devlink_port,
पूर्ण;

काष्ठा net_device *ocelot_port_to_netdev(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	काष्ठा ocelot_port_निजी *priv;

	अगर (!ocelot_port)
		वापस शून्य;

	priv = container_of(ocelot_port, काष्ठा ocelot_port_निजी, port);

	वापस priv->dev;
पूर्ण

/* Checks अगर the net_device instance given to us originates from our driver */
अटल bool ocelot_netdevice_dev_check(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->netdev_ops == &ocelot_port_netdev_ops;
पूर्ण

पूर्णांक ocelot_netdev_to_port(काष्ठा net_device *dev)
अणु
	काष्ठा ocelot_port_निजी *priv;

	अगर (!dev || !ocelot_netdevice_dev_check(dev))
		वापस -EINVAL;

	priv = netdev_priv(dev);

	वापस priv->chip_port;
पूर्ण

अटल व्योम ocelot_port_get_strings(काष्ठा net_device *netdev, u32 sset,
				    u8 *data)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(netdev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	ocelot_get_strings(ocelot, port, sset, data);
पूर्ण

अटल व्योम ocelot_port_get_ethtool_stats(काष्ठा net_device *dev,
					  काष्ठा ethtool_stats *stats,
					  u64 *data)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	ocelot_get_ethtool_stats(ocelot, port, data);
पूर्ण

अटल पूर्णांक ocelot_port_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	वापस ocelot_get_sset_count(ocelot, port, sset);
पूर्ण

अटल पूर्णांक ocelot_port_get_ts_info(काष्ठा net_device *dev,
				   काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;

	अगर (!ocelot->ptp)
		वापस ethtool_op_get_ts_info(dev, info);

	वापस ocelot_get_ts_info(ocelot, port, info);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ocelot_ethtool_ops = अणु
	.get_strings		= ocelot_port_get_strings,
	.get_ethtool_stats	= ocelot_port_get_ethtool_stats,
	.get_sset_count		= ocelot_port_get_sset_count,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
	.get_ts_info		= ocelot_port_get_ts_info,
पूर्ण;

अटल व्योम ocelot_port_attr_stp_state_set(काष्ठा ocelot *ocelot, पूर्णांक port,
					   u8 state)
अणु
	ocelot_bridge_stp_state_set(ocelot, port, state);
पूर्ण

अटल व्योम ocelot_port_attr_ageing_set(काष्ठा ocelot *ocelot, पूर्णांक port,
					अचिन्हित दीर्घ ageing_घड़ी_प्रकार)
अणु
	अचिन्हित दीर्घ ageing_jअगरfies = घड़ी_प्रकार_to_jअगरfies(ageing_घड़ी_प्रकार);
	u32 ageing_समय = jअगरfies_to_msecs(ageing_jअगरfies);

	ocelot_set_ageing_समय(ocelot, ageing_समय);
पूर्ण

अटल व्योम ocelot_port_attr_mc_set(काष्ठा ocelot *ocelot, पूर्णांक port, bool mc)
अणु
	u32 cpu_fwd_mcast = ANA_PORT_CPU_FWD_CFG_CPU_IGMP_REसूची_ENA |
			    ANA_PORT_CPU_FWD_CFG_CPU_MLD_REसूची_ENA |
			    ANA_PORT_CPU_FWD_CFG_CPU_IPMC_CTRL_COPY_ENA;
	u32 val = 0;

	अगर (mc)
		val = cpu_fwd_mcast;

	ocelot_rmw_gix(ocelot, val, cpu_fwd_mcast,
		       ANA_PORT_CPU_FWD_CFG, port);
पूर्ण

अटल पूर्णांक ocelot_port_attr_set(काष्ठा net_device *dev,
				स्थिर काष्ठा चयनdev_attr *attr,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot *ocelot = priv->port.ocelot;
	पूर्णांक port = priv->chip_port;
	पूर्णांक err = 0;

	चयन (attr->id) अणु
	हाल SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		ocelot_port_attr_stp_state_set(ocelot, port, attr->u.stp_state);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME:
		ocelot_port_attr_ageing_set(ocelot, port, attr->u.ageing_समय);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		ocelot_port_vlan_filtering(ocelot, port, attr->u.vlan_filtering);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_MC_DISABLED:
		ocelot_port_attr_mc_set(ocelot, port, !attr->u.mc_disabled);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		err = ocelot_port_pre_bridge_flags(ocelot, port,
						   attr->u.brport_flags);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		ocelot_port_bridge_flags(ocelot, port, attr->u.brport_flags);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ocelot_port_obj_add_vlan(काष्ठा net_device *dev,
				    स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	पूर्णांक ret;

	ret = ocelot_vlan_vid_prepare(dev, vlan->vid, pvid, untagged);
	अगर (ret)
		वापस ret;

	वापस ocelot_vlan_vid_add(dev, vlan->vid, pvid, untagged);
पूर्ण

अटल पूर्णांक ocelot_port_obj_add_mdb(काष्ठा net_device *dev,
				   स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;

	वापस ocelot_port_mdb_add(ocelot, port, mdb);
पूर्ण

अटल पूर्णांक ocelot_port_obj_del_mdb(काष्ठा net_device *dev,
				   स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;

	वापस ocelot_port_mdb_del(ocelot, port, mdb);
पूर्ण

अटल पूर्णांक ocelot_port_obj_mrp_add(काष्ठा net_device *dev,
				   स्थिर काष्ठा चयनdev_obj_mrp *mrp)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;

	वापस ocelot_mrp_add(ocelot, port, mrp);
पूर्ण

अटल पूर्णांक ocelot_port_obj_mrp_del(काष्ठा net_device *dev,
				   स्थिर काष्ठा चयनdev_obj_mrp *mrp)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;

	वापस ocelot_mrp_del(ocelot, port, mrp);
पूर्ण

अटल पूर्णांक
ocelot_port_obj_mrp_add_ring_role(काष्ठा net_device *dev,
				  स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;

	वापस ocelot_mrp_add_ring_role(ocelot, port, mrp);
पूर्ण

अटल पूर्णांक
ocelot_port_obj_mrp_del_ring_role(काष्ठा net_device *dev,
				  स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;

	वापस ocelot_mrp_del_ring_role(ocelot, port, mrp);
पूर्ण

अटल पूर्णांक ocelot_port_obj_add(काष्ठा net_device *dev,
			       स्थिर काष्ठा चयनdev_obj *obj,
			       काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक ret = 0;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		ret = ocelot_port_obj_add_vlan(dev,
					       SWITCHDEV_OBJ_PORT_VLAN(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
		ret = ocelot_port_obj_add_mdb(dev, SWITCHDEV_OBJ_PORT_MDB(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_MRP:
		ret = ocelot_port_obj_mrp_add(dev, SWITCHDEV_OBJ_MRP(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_RING_ROLE_MRP:
		ret = ocelot_port_obj_mrp_add_ring_role(dev,
							SWITCHDEV_OBJ_RING_ROLE_MRP(obj));
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ocelot_port_obj_del(काष्ठा net_device *dev,
			       स्थिर काष्ठा चयनdev_obj *obj)
अणु
	पूर्णांक ret = 0;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		ret = ocelot_vlan_vid_del(dev,
					  SWITCHDEV_OBJ_PORT_VLAN(obj)->vid);
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
		ret = ocelot_port_obj_del_mdb(dev, SWITCHDEV_OBJ_PORT_MDB(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_MRP:
		ret = ocelot_port_obj_mrp_del(dev, SWITCHDEV_OBJ_MRP(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_RING_ROLE_MRP:
		ret = ocelot_port_obj_mrp_del_ring_role(dev,
							SWITCHDEV_OBJ_RING_ROLE_MRP(obj));
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ocelot_inherit_brport_flags(काष्ठा ocelot *ocelot, पूर्णांक port,
					काष्ठा net_device *brport_dev)
अणु
	काष्ठा चयनdev_brport_flags flags = अणु0पूर्ण;
	पूर्णांक flag;

	flags.mask = BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD | BR_BCAST_FLOOD;

	क्रम_each_set_bit(flag, &flags.mask, 32)
		अगर (br_port_flag_is_set(brport_dev, BIT(flag)))
			flags.val |= BIT(flag);

	ocelot_port_bridge_flags(ocelot, port, flags);
पूर्ण

अटल व्योम ocelot_clear_brport_flags(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	काष्ठा चयनdev_brport_flags flags;

	flags.mask = BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD | BR_BCAST_FLOOD;
	flags.val = flags.mask & ~BR_LEARNING;

	ocelot_port_bridge_flags(ocelot, port, flags);
पूर्ण

अटल पूर्णांक ocelot_चयनdev_sync(काष्ठा ocelot *ocelot, पूर्णांक port,
				 काष्ठा net_device *brport_dev,
				 काष्ठा net_device *bridge_dev,
				 काष्ठा netlink_ext_ack *extack)
अणु
	घड़ी_प्रकार ageing_समय;
	u8 stp_state;
	पूर्णांक err;

	ocelot_inherit_brport_flags(ocelot, port, brport_dev);

	stp_state = br_port_get_stp_state(brport_dev);
	ocelot_bridge_stp_state_set(ocelot, port, stp_state);

	err = ocelot_port_vlan_filtering(ocelot, port,
					 br_vlan_enabled(bridge_dev));
	अगर (err)
		वापस err;

	ageing_समय = br_get_ageing_समय(bridge_dev);
	ocelot_port_attr_ageing_set(ocelot, port, ageing_समय);

	err = br_mdb_replay(bridge_dev, brport_dev,
			    &ocelot_चयनdev_blocking_nb, extack);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	err = br_fdb_replay(bridge_dev, brport_dev, &ocelot_चयनdev_nb);
	अगर (err)
		वापस err;

	err = br_vlan_replay(bridge_dev, brport_dev,
			     &ocelot_चयनdev_blocking_nb, extack);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_चयनdev_unsync(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	पूर्णांक err;

	err = ocelot_port_vlan_filtering(ocelot, port, false);
	अगर (err)
		वापस err;

	ocelot_clear_brport_flags(ocelot, port);

	ocelot_bridge_stp_state_set(ocelot, port, BR_STATE_FORWARDING);

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_netdevice_bridge_join(काष्ठा net_device *dev,
					काष्ठा net_device *brport_dev,
					काष्ठा net_device *bridge,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;
	पूर्णांक err;

	ocelot_port_bridge_join(ocelot, port, bridge);

	err = ocelot_चयनdev_sync(ocelot, port, brport_dev, bridge, extack);
	अगर (err)
		जाओ err_चयनdev_sync;

	वापस 0;

err_चयनdev_sync:
	ocelot_port_bridge_leave(ocelot, port, bridge);
	वापस err;
पूर्ण

अटल पूर्णांक ocelot_netdevice_bridge_leave(काष्ठा net_device *dev,
					 काष्ठा net_device *brport_dev,
					 काष्ठा net_device *bridge)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;
	पूर्णांक err;

	err = ocelot_चयनdev_unsync(ocelot, port);
	अगर (err)
		वापस err;

	ocelot_port_bridge_leave(ocelot, port, bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_netdevice_lag_join(काष्ठा net_device *dev,
				     काष्ठा net_device *bond,
				     काष्ठा netdev_lag_upper_info *info,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	काष्ठा net_device *bridge_dev;
	पूर्णांक port = priv->chip_port;
	पूर्णांक err;

	err = ocelot_port_lag_join(ocelot, port, bond, info);
	अगर (err == -EOPNOTSUPP) अणु
		NL_SET_ERR_MSG_MOD(extack, "Offloading not supported");
		वापस 0;
	पूर्ण

	bridge_dev = netdev_master_upper_dev_get(bond);
	अगर (!bridge_dev || !netअगर_is_bridge_master(bridge_dev))
		वापस 0;

	err = ocelot_netdevice_bridge_join(dev, bond, bridge_dev, extack);
	अगर (err)
		जाओ err_bridge_join;

	वापस 0;

err_bridge_join:
	ocelot_port_lag_leave(ocelot, port, bond);
	वापस err;
पूर्ण

अटल पूर्णांक ocelot_netdevice_lag_leave(काष्ठा net_device *dev,
				      काष्ठा net_device *bond)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	काष्ठा net_device *bridge_dev;
	पूर्णांक port = priv->chip_port;

	ocelot_port_lag_leave(ocelot, port, bond);

	bridge_dev = netdev_master_upper_dev_get(bond);
	अगर (!bridge_dev || !netअगर_is_bridge_master(bridge_dev))
		वापस 0;

	वापस ocelot_netdevice_bridge_leave(dev, bond, bridge_dev);
पूर्ण

अटल पूर्णांक ocelot_netdevice_changeupper(काष्ठा net_device *dev,
					काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा netlink_ext_ack *extack;
	पूर्णांक err = 0;

	extack = netdev_notअगरier_info_to_extack(&info->info);

	अगर (netअगर_is_bridge_master(info->upper_dev)) अणु
		अगर (info->linking)
			err = ocelot_netdevice_bridge_join(dev, dev,
							   info->upper_dev,
							   extack);
		अन्यथा
			err = ocelot_netdevice_bridge_leave(dev, dev,
							    info->upper_dev);
	पूर्ण
	अगर (netअगर_is_lag_master(info->upper_dev)) अणु
		अगर (info->linking)
			err = ocelot_netdevice_lag_join(dev, info->upper_dev,
							info->upper_info, extack);
		अन्यथा
			ocelot_netdevice_lag_leave(dev, info->upper_dev);
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

/* Treat CHANGEUPPER events on an offloaded LAG as inभागidual CHANGEUPPER
 * events क्रम the lower physical ports of the LAG.
 * If the LAG upper isn't offloaded, ignore its CHANGEUPPER events.
 * In हाल the LAG joined a bridge, notअगरy that we are offloading it and can करो
 * क्रमwarding in hardware towards it.
 */
अटल पूर्णांक
ocelot_netdevice_lag_changeupper(काष्ठा net_device *dev,
				 काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा net_device *lower;
	काष्ठा list_head *iter;
	पूर्णांक err = NOTIFY_DONE;

	netdev_क्रम_each_lower_dev(dev, lower, iter) अणु
		काष्ठा ocelot_port_निजी *priv = netdev_priv(lower);
		काष्ठा ocelot_port *ocelot_port = &priv->port;

		अगर (ocelot_port->bond != dev)
			वापस NOTIFY_OK;

		err = ocelot_netdevice_changeupper(lower, info);
		अगर (err)
			वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक
ocelot_netdevice_changelowerstate(काष्ठा net_device *dev,
				  काष्ठा netdev_lag_lower_state_info *info)
अणु
	काष्ठा ocelot_port_निजी *priv = netdev_priv(dev);
	bool is_active = info->link_up && info->tx_enabled;
	काष्ठा ocelot_port *ocelot_port = &priv->port;
	काष्ठा ocelot *ocelot = ocelot_port->ocelot;
	पूर्णांक port = priv->chip_port;

	अगर (!ocelot_port->bond)
		वापस NOTIFY_DONE;

	अगर (ocelot_port->lag_tx_active == is_active)
		वापस NOTIFY_DONE;

	ocelot_port_lag_change(ocelot, port, is_active);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक ocelot_netdevice_event(काष्ठा notअगरier_block *unused,
				  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER: अणु
		काष्ठा netdev_notअगरier_changeupper_info *info = ptr;

		अगर (ocelot_netdevice_dev_check(dev))
			वापस ocelot_netdevice_changeupper(dev, info);

		अगर (netअगर_is_lag_master(dev))
			वापस ocelot_netdevice_lag_changeupper(dev, info);

		अवरोध;
	पूर्ण
	हाल NETDEV_CHANGELOWERSTATE: अणु
		काष्ठा netdev_notअगरier_changelowerstate_info *info = ptr;

		अगर (!ocelot_netdevice_dev_check(dev))
			अवरोध;

		वापस ocelot_netdevice_changelowerstate(dev,
							 info->lower_state_info);
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

काष्ठा notअगरier_block ocelot_netdevice_nb __पढ़ो_mostly = अणु
	.notअगरier_call = ocelot_netdevice_event,
पूर्ण;

अटल पूर्णांक ocelot_चयनdev_event(काष्ठा notअगरier_block *unused,
				  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	पूर्णांक err;

	चयन (event) अणु
	हाल SWITCHDEV_PORT_ATTR_SET:
		err = चयनdev_handle_port_attr_set(dev, ptr,
						     ocelot_netdevice_dev_check,
						     ocelot_port_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

काष्ठा notअगरier_block ocelot_चयनdev_nb __पढ़ो_mostly = अणु
	.notअगरier_call = ocelot_चयनdev_event,
पूर्ण;

अटल पूर्णांक ocelot_चयनdev_blocking_event(काष्ठा notअगरier_block *unused,
					   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	पूर्णांक err;

	चयन (event) अणु
		/* Blocking events. */
	हाल SWITCHDEV_PORT_OBJ_ADD:
		err = चयनdev_handle_port_obj_add(dev, ptr,
						    ocelot_netdevice_dev_check,
						    ocelot_port_obj_add);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_PORT_OBJ_DEL:
		err = चयनdev_handle_port_obj_del(dev, ptr,
						    ocelot_netdevice_dev_check,
						    ocelot_port_obj_del);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_PORT_ATTR_SET:
		err = चयनdev_handle_port_attr_set(dev, ptr,
						     ocelot_netdevice_dev_check,
						     ocelot_port_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

काष्ठा notअगरier_block ocelot_चयनdev_blocking_nb __पढ़ो_mostly = अणु
	.notअगरier_call = ocelot_चयनdev_blocking_event,
पूर्ण;

पूर्णांक ocelot_probe_port(काष्ठा ocelot *ocelot, पूर्णांक port, काष्ठा regmap *target,
		      काष्ठा phy_device *phy)
अणु
	काष्ठा ocelot_port_निजी *priv;
	काष्ठा ocelot_port *ocelot_port;
	काष्ठा net_device *dev;
	पूर्णांक err;

	dev = alloc_etherdev(माप(काष्ठा ocelot_port_निजी));
	अगर (!dev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(dev, ocelot->dev);
	priv = netdev_priv(dev);
	priv->dev = dev;
	priv->phy = phy;
	priv->chip_port = port;
	ocelot_port = &priv->port;
	ocelot_port->ocelot = ocelot;
	ocelot_port->target = target;
	ocelot->ports[port] = ocelot_port;

	dev->netdev_ops = &ocelot_port_netdev_ops;
	dev->ethtool_ops = &ocelot_ethtool_ops;

	dev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_RXFCS |
		NETIF_F_HW_TC;
	dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_HW_TC;

	स_नकल(dev->dev_addr, ocelot->base_mac, ETH_ALEN);
	dev->dev_addr[ETH_ALEN - 1] += port;
	ocelot_mact_learn(ocelot, PGID_CPU, dev->dev_addr,
			  ocelot_port->pvid_vlan.vid, ENTRYTYPE_LOCKED);

	ocelot_init_port(ocelot, port);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(ocelot->dev, "register_netdev failed\n");
		मुक्त_netdev(dev);
		ocelot->ports[port] = शून्य;
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ocelot_release_port(काष्ठा ocelot_port *ocelot_port)
अणु
	काष्ठा ocelot_port_निजी *priv = container_of(ocelot_port,
						काष्ठा ocelot_port_निजी,
						port);

	unरेजिस्टर_netdev(priv->dev);
	मुक्त_netdev(priv->dev);
पूर्ण
