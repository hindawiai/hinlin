<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2018-2021, Intel Corporation. */

/* Link Aggregation code */

#समावेश "ice.h"
#समावेश "ice_lag.h"

/**
 * ice_lag_nop_handler - no-op Rx handler to disable LAG
 * @pskb: poपूर्णांकer to skb poपूर्णांकer
 */
rx_handler_result_t ice_lag_nop_handler(काष्ठा sk_buff __always_unused **pskb)
अणु
	वापस RX_HANDLER_PASS;
पूर्ण

/**
 * ice_lag_set_primary - set PF LAG state as Primary
 * @lag: LAG info काष्ठा
 */
अटल व्योम ice_lag_set_primary(काष्ठा ice_lag *lag)
अणु
	काष्ठा ice_pf *pf = lag->pf;

	अगर (!pf)
		वापस;

	अगर (lag->role != ICE_LAG_UNSET && lag->role != ICE_LAG_BACKUP) अणु
		dev_warn(ice_pf_to_dev(pf), "%s: Attempt to be Primary, but incompatible state.\n",
			 netdev_name(lag->netdev));
		वापस;
	पूर्ण

	lag->role = ICE_LAG_PRIMARY;
पूर्ण

/**
 * ice_lag_set_backup - set PF LAG state to Backup
 * @lag: LAG info काष्ठा
 */
अटल व्योम ice_lag_set_backup(काष्ठा ice_lag *lag)
अणु
	काष्ठा ice_pf *pf = lag->pf;

	अगर (!pf)
		वापस;

	अगर (lag->role != ICE_LAG_UNSET && lag->role != ICE_LAG_PRIMARY) अणु
		dev_dbg(ice_pf_to_dev(pf), "%s: Attempt to be Backup, but incompatible state\n",
			netdev_name(lag->netdev));
		वापस;
	पूर्ण

	lag->role = ICE_LAG_BACKUP;
पूर्ण

/**
 * ice_display_lag_info - prपूर्णांक LAG info
 * @lag: LAG info काष्ठा
 */
अटल व्योम ice_display_lag_info(काष्ठा ice_lag *lag)
अणु
	स्थिर अक्षर *name, *peer, *upper, *role, *bonded, *master;
	काष्ठा device *dev = &lag->pf->pdev->dev;

	name = lag->netdev ? netdev_name(lag->netdev) : "unset";
	peer = lag->peer_netdev ? netdev_name(lag->peer_netdev) : "unset";
	upper = lag->upper_netdev ? netdev_name(lag->upper_netdev) : "unset";
	master = lag->master ? "TRUE" : "FALSE";
	bonded = lag->bonded ? "BONDED" : "UNBONDED";

	चयन (lag->role) अणु
	हाल ICE_LAG_NONE:
		role = "NONE";
		अवरोध;
	हाल ICE_LAG_PRIMARY:
		role = "PRIMARY";
		अवरोध;
	हाल ICE_LAG_BACKUP:
		role = "BACKUP";
		अवरोध;
	हाल ICE_LAG_UNSET:
		role = "UNSET";
		अवरोध;
	शेष:
		role = "ERROR";
	पूर्ण

	dev_dbg(dev, "%s %s, peer:%s, upper:%s, role:%s, master:%s\n", name,
		bonded, peer, upper, role, master);
पूर्ण

/**
 * ice_lag_info_event - handle NETDEV_BONDING_INFO event
 * @lag: LAG info काष्ठा
 * @ptr: opaque data poपूर्णांकer
 *
 * ptr is to be cast to (netdev_notअगरier_bonding_info *)
 */
अटल व्योम ice_lag_info_event(काष्ठा ice_lag *lag, व्योम *ptr)
अणु
	काष्ठा net_device *event_netdev, *netdev_पंचांगp;
	काष्ठा netdev_notअगरier_bonding_info *info;
	काष्ठा netdev_bonding_info *bonding_info;
	स्थिर अक्षर *lag_netdev_name;

	event_netdev = netdev_notअगरier_info_to_dev(ptr);
	info = ptr;
	lag_netdev_name = netdev_name(lag->netdev);
	bonding_info = &info->bonding_info;

	अगर (event_netdev != lag->netdev || !lag->bonded || !lag->upper_netdev)
		वापस;

	अगर (bonding_info->master.bond_mode != BOND_MODE_ACTIVEBACKUP) अणु
		netdev_dbg(lag->netdev, "Bonding event recv, but mode not active/backup\n");
		जाओ lag_out;
	पूर्ण

	अगर (म_भेद(bonding_info->slave.slave_name, lag_netdev_name)) अणु
		netdev_dbg(lag->netdev, "Bonding event recv, but slave info not for us\n");
		जाओ lag_out;
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम_each_netdev_in_bond_rcu(lag->upper_netdev, netdev_पंचांगp) अणु
		अगर (!netअगर_is_ice(netdev_पंचांगp))
			जारी;

		अगर (netdev_पंचांगp && netdev_पंचांगp != lag->netdev &&
		    lag->peer_netdev != netdev_पंचांगp) अणु
			dev_hold(netdev_पंचांगp);
			lag->peer_netdev = netdev_पंचांगp;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (bonding_info->slave.state)
		ice_lag_set_backup(lag);
	अन्यथा
		ice_lag_set_primary(lag);

lag_out:
	ice_display_lag_info(lag);
पूर्ण

/**
 * ice_lag_link - handle LAG link event
 * @lag: LAG info काष्ठा
 * @info: info from the netdev notअगरier
 */
अटल व्योम
ice_lag_link(काष्ठा ice_lag *lag, काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा net_device *netdev_पंचांगp, *upper = info->upper_dev;
	काष्ठा ice_pf *pf = lag->pf;
	पूर्णांक peers = 0;

	अगर (lag->bonded)
		dev_warn(ice_pf_to_dev(pf), "%s Already part of a bond\n",
			 netdev_name(lag->netdev));

	rcu_पढ़ो_lock();
	क्रम_each_netdev_in_bond_rcu(upper, netdev_पंचांगp)
		peers++;
	rcu_पढ़ो_unlock();

	अगर (lag->upper_netdev != upper) अणु
		dev_hold(upper);
		lag->upper_netdev = upper;
	पूर्ण

	ice_clear_sriov_cap(pf);

	lag->bonded = true;
	lag->role = ICE_LAG_UNSET;

	/* अगर this is the first element in an LAG mark as master */
	lag->master = !!(peers == 1);
पूर्ण

/**
 * ice_lag_unlink - handle unlink event
 * @lag: LAG info काष्ठा
 * @info: info from netdev notअगरication
 */
अटल व्योम
ice_lag_unlink(काष्ठा ice_lag *lag,
	       काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा net_device *netdev_पंचांगp, *upper = info->upper_dev;
	काष्ठा ice_pf *pf = lag->pf;
	bool found = false;

	अगर (!lag->bonded) अणु
		netdev_dbg(lag->netdev, "bonding unlink event on non-LAG netdev\n");
		वापस;
	पूर्ण

	/* determine अगर we are in the new LAG config or not */
	rcu_पढ़ो_lock();
	क्रम_each_netdev_in_bond_rcu(upper, netdev_पंचांगp) अणु
		अगर (netdev_पंचांगp == lag->netdev) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (found)
		वापस;

	अगर (lag->upper_netdev) अणु
		dev_put(lag->upper_netdev);
		lag->upper_netdev = शून्य;
	पूर्ण

	अगर (lag->peer_netdev) अणु
		dev_put(lag->peer_netdev);
		lag->peer_netdev = शून्य;
	पूर्ण

	ice_set_sriov_cap(pf);
	lag->bonded = false;
	lag->role = ICE_LAG_NONE;
पूर्ण

/**
 * ice_lag_changeupper_event - handle LAG changeupper event
 * @lag: LAG info काष्ठा
 * @ptr: opaque poपूर्णांकer data
 *
 * ptr is to be cast पूर्णांकo netdev_notअगरier_changeupper_info
 */
अटल व्योम ice_lag_changeupper_event(काष्ठा ice_lag *lag, व्योम *ptr)
अणु
	काष्ठा netdev_notअगरier_changeupper_info *info;
	काष्ठा net_device *netdev;

	info = ptr;
	netdev = netdev_notअगरier_info_to_dev(ptr);

	/* not क्रम this netdev */
	अगर (netdev != lag->netdev)
		वापस;

	अगर (!info->upper_dev) अणु
		netdev_dbg(netdev, "changeupper rcvd, but no upper defined\n");
		वापस;
	पूर्ण

	netdev_dbg(netdev, "bonding %s\n", info->linking ? "LINK" : "UNLINK");

	अगर (!netअगर_is_lag_master(info->upper_dev)) अणु
		netdev_dbg(netdev, "changeupper rcvd, but not master. bail\n");
		वापस;
	पूर्ण

	अगर (info->linking)
		ice_lag_link(lag, info);
	अन्यथा
		ice_lag_unlink(lag, info);

	ice_display_lag_info(lag);
पूर्ण

/**
 * ice_lag_changelower_event - handle LAG changelower event
 * @lag: LAG info काष्ठा
 * @ptr: opaque data poपूर्णांकer
 *
 * ptr to be cast to netdev_notअगरier_changelowerstate_info
 */
अटल व्योम ice_lag_changelower_event(काष्ठा ice_lag *lag, व्योम *ptr)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);

	अगर (netdev != lag->netdev)
		वापस;

	netdev_dbg(netdev, "bonding info\n");

	अगर (!netअगर_is_lag_port(netdev))
		netdev_dbg(netdev, "CHANGELOWER rcvd, but netdev not in LAG. Bail\n");
पूर्ण

/**
 * ice_lag_event_handler - handle LAG events from netdev
 * @notअगर_blk: notअगरier block रेजिस्टरed by this netdev
 * @event: event type
 * @ptr: opaque data containing notअगरier event
 */
अटल पूर्णांक
ice_lag_event_handler(काष्ठा notअगरier_block *notअगर_blk, अचिन्हित दीर्घ event,
		      व्योम *ptr)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा ice_lag *lag;

	lag = container_of(notअगर_blk, काष्ठा ice_lag, notअगर_block);

	अगर (!lag->netdev)
		वापस NOTIFY_DONE;

	/* Check that the netdev is in the working namespace */
	अगर (!net_eq(dev_net(netdev), &init_net))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER:
		ice_lag_changeupper_event(lag, ptr);
		अवरोध;
	हाल NETDEV_CHANGELOWERSTATE:
		ice_lag_changelower_event(lag, ptr);
		अवरोध;
	हाल NETDEV_BONDING_INFO:
		ice_lag_info_event(lag, ptr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/**
 * ice_रेजिस्टर_lag_handler - रेजिस्टर LAG handler on netdev
 * @lag: LAG काष्ठा
 */
अटल पूर्णांक ice_रेजिस्टर_lag_handler(काष्ठा ice_lag *lag)
अणु
	काष्ठा device *dev = ice_pf_to_dev(lag->pf);
	काष्ठा notअगरier_block *notअगर_blk;

	notअगर_blk = &lag->notअगर_block;

	अगर (!notअगर_blk->notअगरier_call) अणु
		notअगर_blk->notअगरier_call = ice_lag_event_handler;
		अगर (रेजिस्टर_netdevice_notअगरier(notअगर_blk)) अणु
			notअगर_blk->notअगरier_call = शून्य;
			dev_err(dev, "FAIL register LAG event handler!\n");
			वापस -EINVAL;
		पूर्ण
		dev_dbg(dev, "LAG event handler registered\n");
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_unरेजिस्टर_lag_handler - unरेजिस्टर LAG handler on netdev
 * @lag: LAG काष्ठा
 */
अटल व्योम ice_unरेजिस्टर_lag_handler(काष्ठा ice_lag *lag)
अणु
	काष्ठा device *dev = ice_pf_to_dev(lag->pf);
	काष्ठा notअगरier_block *notअगर_blk;

	notअगर_blk = &lag->notअगर_block;
	अगर (notअगर_blk->notअगरier_call) अणु
		unरेजिस्टर_netdevice_notअगरier(notअगर_blk);
		dev_dbg(dev, "LAG event handler unregistered\n");
	पूर्ण
पूर्ण

/**
 * ice_init_lag - initialize support क्रम LAG
 * @pf: PF काष्ठा
 *
 * Alloc memory क्रम LAG काष्ठाs and initialize the elements.
 * Memory will be मुक्तd in ice_deinit_lag
 */
पूर्णांक ice_init_lag(काष्ठा ice_pf *pf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_lag *lag;
	काष्ठा ice_vsi *vsi;
	पूर्णांक err;

	pf->lag = kzalloc(माप(*lag), GFP_KERNEL);
	अगर (!pf->lag)
		वापस -ENOMEM;
	lag = pf->lag;

	vsi = ice_get_मुख्य_vsi(pf);
	अगर (!vsi) अणु
		dev_err(dev, "couldn't get main vsi, link aggregation init fail\n");
		err = -EIO;
		जाओ lag_error;
	पूर्ण

	lag->pf = pf;
	lag->netdev = vsi->netdev;
	lag->role = ICE_LAG_NONE;
	lag->bonded = false;
	lag->peer_netdev = शून्य;
	lag->upper_netdev = शून्य;
	lag->notअगर_block.notअगरier_call = शून्य;

	err = ice_रेजिस्टर_lag_handler(lag);
	अगर (err) अणु
		dev_warn(dev, "INIT LAG: Failed to register event handler\n");
		जाओ lag_error;
	पूर्ण

	ice_display_lag_info(lag);

	dev_dbg(dev, "INIT LAG complete\n");
	वापस 0;

lag_error:
	kमुक्त(lag);
	pf->lag = शून्य;
	वापस err;
पूर्ण

/**
 * ice_deinit_lag - Clean up LAG
 * @pf: PF काष्ठा
 *
 * Clean up kernel LAG info and मुक्त memory
 * This function is meant to only be called on driver हटाओ/shutकरोwn
 */
व्योम ice_deinit_lag(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_lag *lag;

	lag = pf->lag;

	अगर (!lag)
		वापस;

	अगर (lag->pf)
		ice_unरेजिस्टर_lag_handler(lag);

	अगर (lag->upper_netdev)
		dev_put(lag->upper_netdev);

	अगर (lag->peer_netdev)
		dev_put(lag->peer_netdev);

	kमुक्त(lag);

	pf->lag = शून्य;
पूर्ण
