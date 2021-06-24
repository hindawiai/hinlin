<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Inc. All rights reserved. */

#समावेश <linux/netdevice.h>
#समावेश <linux/list.h>
#समावेश <net/lag.h>

#समावेश "mlx5_core.h"
#समावेश "eswitch.h"
#समावेश "esw/acl/ofld.h"
#समावेश "en_rep.h"

काष्ठा mlx5e_rep_bond अणु
	काष्ठा notअगरier_block nb;
	काष्ठा netdev_net_notअगरier nn;
	काष्ठा list_head metadata_list;
पूर्ण;

काष्ठा mlx5e_rep_bond_slave_entry अणु
	काष्ठा list_head list;
	काष्ठा net_device *netdev;
पूर्ण;

काष्ठा mlx5e_rep_bond_metadata अणु
	काष्ठा list_head list; /* link to global list of rep_bond_metadata */
	काष्ठा mlx5_eचयन *esw;
	 /* निजी of uplink holding rep bond metadata list */
	काष्ठा net_device *lag_dev;
	u32 metadata_reg_c_0;

	काष्ठा list_head slaves_list; /* slaves list */
	पूर्णांक slaves;
पूर्ण;

अटल काष्ठा mlx5e_rep_bond_metadata *
mlx5e_lookup_rep_bond_metadata(काष्ठा mlx5_rep_uplink_priv *uplink_priv,
			       स्थिर काष्ठा net_device *lag_dev)
अणु
	काष्ठा mlx5e_rep_bond_metadata *found = शून्य;
	काष्ठा mlx5e_rep_bond_metadata *cur;

	list_क्रम_each_entry(cur, &uplink_priv->bond->metadata_list, list) अणु
		अगर (cur->lag_dev == lag_dev) अणु
			found = cur;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल काष्ठा mlx5e_rep_bond_slave_entry *
mlx5e_lookup_rep_bond_slave_entry(काष्ठा mlx5e_rep_bond_metadata *mdata,
				  स्थिर काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_rep_bond_slave_entry *found = शून्य;
	काष्ठा mlx5e_rep_bond_slave_entry *cur;

	list_क्रम_each_entry(cur, &mdata->slaves_list, list) अणु
		अगर (cur->netdev == netdev) अणु
			found = cur;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल व्योम mlx5e_rep_bond_metadata_release(काष्ठा mlx5e_rep_bond_metadata *mdata)
अणु
	netdev_dbg(mdata->lag_dev, "destroy rep_bond_metadata(%d)\n",
		   mdata->metadata_reg_c_0);
	list_del(&mdata->list);
	mlx5_esw_match_metadata_मुक्त(mdata->esw, mdata->metadata_reg_c_0);
	WARN_ON(!list_empty(&mdata->slaves_list));
	kमुक्त(mdata);
पूर्ण

/* This must be called under rtnl_lock */
पूर्णांक mlx5e_rep_bond_enslave(काष्ठा mlx5_eचयन *esw, काष्ठा net_device *netdev,
			   काष्ठा net_device *lag_dev)
अणु
	काष्ठा mlx5e_rep_bond_slave_entry *s_entry;
	काष्ठा mlx5e_rep_bond_metadata *mdata;
	काष्ठा mlx5e_rep_priv *rpriv;
	काष्ठा mlx5e_priv *priv;
	पूर्णांक err;

	ASSERT_RTNL();

	rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
	mdata = mlx5e_lookup_rep_bond_metadata(&rpriv->uplink_priv, lag_dev);
	अगर (!mdata) अणु
		/* First netdev becomes slave, no metadata presents the lag_dev. Create one */
		mdata = kzalloc(माप(*mdata), GFP_KERNEL);
		अगर (!mdata)
			वापस -ENOMEM;

		mdata->lag_dev = lag_dev;
		mdata->esw = esw;
		INIT_LIST_HEAD(&mdata->slaves_list);
		mdata->metadata_reg_c_0 = mlx5_esw_match_metadata_alloc(esw);
		अगर (!mdata->metadata_reg_c_0) अणु
			kमुक्त(mdata);
			वापस -ENOSPC;
		पूर्ण
		list_add(&mdata->list, &rpriv->uplink_priv.bond->metadata_list);

		netdev_dbg(lag_dev, "create rep_bond_metadata(%d)\n",
			   mdata->metadata_reg_c_0);
	पूर्ण

	s_entry = kzalloc(माप(*s_entry), GFP_KERNEL);
	अगर (!s_entry) अणु
		err = -ENOMEM;
		जाओ entry_alloc_err;
	पूर्ण

	s_entry->netdev = netdev;
	priv = netdev_priv(netdev);
	rpriv = priv->ppriv;

	err = mlx5_esw_acl_ingress_vport_bond_update(esw, rpriv->rep->vport,
						     mdata->metadata_reg_c_0);
	अगर (err)
		जाओ ingress_err;

	mdata->slaves++;
	list_add_tail(&s_entry->list, &mdata->slaves_list);
	netdev_dbg(netdev, "enslave rep vport(%d) lag_dev(%s) metadata(0x%x)\n",
		   rpriv->rep->vport, lag_dev->name, mdata->metadata_reg_c_0);

	वापस 0;

ingress_err:
	kमुक्त(s_entry);
entry_alloc_err:
	अगर (!mdata->slaves)
		mlx5e_rep_bond_metadata_release(mdata);
	वापस err;
पूर्ण

/* This must be called under rtnl_lock */
व्योम mlx5e_rep_bond_unslave(काष्ठा mlx5_eचयन *esw,
			    स्थिर काष्ठा net_device *netdev,
			    स्थिर काष्ठा net_device *lag_dev)
अणु
	काष्ठा mlx5e_rep_bond_slave_entry *s_entry;
	काष्ठा mlx5e_rep_bond_metadata *mdata;
	काष्ठा mlx5e_rep_priv *rpriv;
	काष्ठा mlx5e_priv *priv;

	ASSERT_RTNL();

	rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
	mdata = mlx5e_lookup_rep_bond_metadata(&rpriv->uplink_priv, lag_dev);
	अगर (!mdata)
		वापस;

	s_entry = mlx5e_lookup_rep_bond_slave_entry(mdata, netdev);
	अगर (!s_entry)
		वापस;

	priv = netdev_priv(netdev);
	rpriv = priv->ppriv;

	/* Reset bond_metadata to zero first then reset all ingress/egress
	 * acls and rx rules of unslave representor's vport
	 */
	mlx5_esw_acl_ingress_vport_bond_update(esw, rpriv->rep->vport, 0);
	mlx5_esw_acl_egress_vport_unbond(esw, rpriv->rep->vport);
	mlx5e_rep_bond_update(priv, false);

	list_del(&s_entry->list);

	netdev_dbg(netdev, "unslave rep vport(%d) lag_dev(%s) metadata(0x%x)\n",
		   rpriv->rep->vport, lag_dev->name, mdata->metadata_reg_c_0);

	अगर (--mdata->slaves == 0)
		mlx5e_rep_bond_metadata_release(mdata);
	kमुक्त(s_entry);
पूर्ण

अटल bool mlx5e_rep_is_lag_netdev(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_rep_priv *rpriv;
	काष्ठा mlx5e_priv *priv;

	/* A given netdev is not a representor or not a slave of LAG configuration */
	अगर (!mlx5e_eचयन_rep(netdev) || !netअगर_is_lag_port(netdev))
		वापस false;

	priv = netdev_priv(netdev);
	rpriv = priv->ppriv;

	/* Egress acl क्रमward to vport is supported only non-uplink representor */
	वापस rpriv->rep->vport != MLX5_VPORT_UPLINK;
पूर्ण

अटल व्योम mlx5e_rep_changelowerstate_event(काष्ठा net_device *netdev, व्योम *ptr)
अणु
	काष्ठा netdev_notअगरier_changelowerstate_info *info;
	काष्ठा netdev_lag_lower_state_info *lag_info;
	काष्ठा mlx5e_rep_priv *rpriv;
	काष्ठा net_device *lag_dev;
	काष्ठा mlx5e_priv *priv;
	काष्ठा list_head *iter;
	काष्ठा net_device *dev;
	u16 acl_vport_num;
	u16 fwd_vport_num;
	पूर्णांक err;

	अगर (!mlx5e_rep_is_lag_netdev(netdev))
		वापस;

	info = ptr;
	lag_info = info->lower_state_info;
	/* This is not an event of a representor becoming active slave */
	अगर (!lag_info->tx_enabled)
		वापस;

	priv = netdev_priv(netdev);
	rpriv = priv->ppriv;
	fwd_vport_num = rpriv->rep->vport;
	lag_dev = netdev_master_upper_dev_get(netdev);
	अगर (!lag_dev)
		वापस;

	netdev_dbg(netdev, "lag_dev(%s)'s slave vport(%d) is txable(%d)\n",
		   lag_dev->name, fwd_vport_num, net_lag_port_dev_txable(netdev));

	/* Poपूर्णांक everyone's egress acl to the vport of the active representor */
	netdev_क्रम_each_lower_dev(lag_dev, dev, iter) अणु
		priv = netdev_priv(dev);
		rpriv = priv->ppriv;
		acl_vport_num = rpriv->rep->vport;
		अगर (acl_vport_num != fwd_vport_num) अणु
			/* Only single rx_rule क्रम unique bond_metadata should be
			 * present, delete it अगर it's saved as passive vport's
			 * rx_rule with destination as passive vport's root_ft
			 */
			mlx5e_rep_bond_update(priv, true);
			err = mlx5_esw_acl_egress_vport_bond(priv->mdev->priv.eचयन,
							     fwd_vport_num,
							     acl_vport_num);
			अगर (err)
				netdev_warn(dev,
					    "configure slave vport(%d) egress fwd, err(%d)",
					    acl_vport_num, err);
		पूर्ण
	पूर्ण

	/* Insert new rx_rule क्रम unique bond_metadata, save it as active vport's
	 * rx_rule with new destination as active vport's root_ft
	 */
	err = mlx5e_rep_bond_update(netdev_priv(netdev), false);
	अगर (err)
		netdev_warn(netdev, "configure active slave vport(%d) rx_rule, err(%d)",
			    fwd_vport_num, err);
पूर्ण

अटल व्योम mlx5e_rep_changeupper_event(काष्ठा net_device *netdev, व्योम *ptr)
अणु
	काष्ठा netdev_notअगरier_changeupper_info *info = ptr;
	काष्ठा mlx5e_rep_priv *rpriv;
	काष्ठा net_device *lag_dev;
	काष्ठा mlx5e_priv *priv;

	अगर (!mlx5e_rep_is_lag_netdev(netdev))
		वापस;

	priv = netdev_priv(netdev);
	rpriv = priv->ppriv;
	lag_dev = info->upper_dev;

	netdev_dbg(netdev, "%sslave vport(%d) lag(%s)\n",
		   info->linking ? "en" : "un", rpriv->rep->vport, lag_dev->name);

	अगर (info->linking)
		mlx5e_rep_bond_enslave(priv->mdev->priv.eचयन, netdev, lag_dev);
	अन्यथा
		mlx5e_rep_bond_unslave(priv->mdev->priv.eचयन, netdev, lag_dev);
पूर्ण

/* Bond device of representors and netdev events are used here in specअगरic way
 * to support eचयन vports bonding and to perक्रमm failover of eचयन vport
 * by modअगरying the vport's egress acl of lower dev representors. Thus this
 * also change the traditional behavior of lower dev under bond device.
 * All non-representor netdevs or representors of other venकरोrs as lower dev
 * of bond device are not supported.
 */
अटल पूर्णांक mlx5e_rep_esw_bond_netevent(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);

	चयन (event) अणु
	हाल NETDEV_CHANGELOWERSTATE:
		mlx5e_rep_changelowerstate_event(netdev, ptr);
		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		mlx5e_rep_changeupper_event(netdev, ptr);
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/* If HW support eचयन vports bonding, रेजिस्टर a specअगरic notअगरier to
 * handle it when two or more representors are bonded
 */
पूर्णांक mlx5e_rep_bond_init(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	काष्ठा mlx5_rep_uplink_priv *uplink_priv = &rpriv->uplink_priv;
	काष्ठा net_device *netdev = rpriv->netdev;
	काष्ठा mlx5e_priv *priv;
	पूर्णांक ret = 0;

	priv = netdev_priv(netdev);
	अगर (!mlx5_esw_acl_egress_fwd2vport_supported(priv->mdev->priv.eचयन))
		जाओ out;

	uplink_priv->bond = kvzalloc(माप(*uplink_priv->bond), GFP_KERNEL);
	अगर (!uplink_priv->bond) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&uplink_priv->bond->metadata_list);
	uplink_priv->bond->nb.notअगरier_call = mlx5e_rep_esw_bond_netevent;
	ret = रेजिस्टर_netdevice_notअगरier_dev_net(netdev,
						  &uplink_priv->bond->nb,
						  &uplink_priv->bond->nn);
	अगर (ret) अणु
		netdev_err(netdev, "register bonding netevent notifier, err(%d)\n", ret);
		kvमुक्त(uplink_priv->bond);
		uplink_priv->bond = शून्य;
	पूर्ण

out:
	वापस ret;
पूर्ण

व्योम mlx5e_rep_bond_cleanup(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(rpriv->netdev);

	अगर (!mlx5_esw_acl_egress_fwd2vport_supported(priv->mdev->priv.eचयन) ||
	    !rpriv->uplink_priv.bond)
		वापस;

	unरेजिस्टर_netdevice_notअगरier_dev_net(rpriv->netdev,
					      &rpriv->uplink_priv.bond->nb,
					      &rpriv->uplink_priv.bond->nn);
	kvमुक्त(rpriv->uplink_priv.bond);
पूर्ण
