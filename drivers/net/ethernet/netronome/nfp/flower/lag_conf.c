<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */

#समावेश "main.h"

/* LAG group config flags. */
#घोषणा NFP_FL_LAG_LAST			BIT(1)
#घोषणा NFP_FL_LAG_FIRST		BIT(2)
#घोषणा NFP_FL_LAG_DATA			BIT(3)
#घोषणा NFP_FL_LAG_XON			BIT(4)
#घोषणा NFP_FL_LAG_SYNC			BIT(5)
#घोषणा NFP_FL_LAG_SWITCH		BIT(6)
#घोषणा NFP_FL_LAG_RESET		BIT(7)

/* LAG port state flags. */
#घोषणा NFP_PORT_LAG_LINK_UP		BIT(0)
#घोषणा NFP_PORT_LAG_TX_ENABLED		BIT(1)
#घोषणा NFP_PORT_LAG_CHANGED		BIT(2)

क्रमागत nfp_fl_lag_batch अणु
	NFP_FL_LAG_BATCH_FIRST,
	NFP_FL_LAG_BATCH_MEMBER,
	NFP_FL_LAG_BATCH_FINISHED
पूर्ण;

/**
 * काष्ठा nfp_flower_cmsg_lag_config - control message payload क्रम LAG config
 * @ctrl_flags:	Configuration flags
 * @reserved:	Reserved क्रम future use
 * @ttl:	Time to live of packet - host always sets to 0xff
 * @pkt_number:	Config message packet number - increment क्रम each message
 * @batch_ver:	Batch version of messages - increment क्रम each batch of messages
 * @group_id:	Group ID applicable
 * @group_inst:	Group instance number - increment when group is reused
 * @members:	Array of 32-bit words listing all active group members
 */
काष्ठा nfp_flower_cmsg_lag_config अणु
	u8 ctrl_flags;
	u8 reserved[2];
	u8 ttl;
	__be32 pkt_number;
	__be32 batch_ver;
	__be32 group_id;
	__be32 group_inst;
	__be32 members[];
पूर्ण;

/**
 * काष्ठा nfp_fl_lag_group - list entry क्रम each LAG group
 * @group_id:		Asचिन्हित group ID क्रम host/kernel sync
 * @group_inst:		Group instance in हाल of ID reuse
 * @list:		List entry
 * @master_ndev:	Group master Netdev
 * @dirty:		Marked अगर the group needs synced to HW
 * @offloaded:		Marked अगर the group is currently offloaded to NIC
 * @to_हटाओ:		Marked अगर the group should be हटाओd from NIC
 * @to_destroy:		Marked अगर the group should be हटाओd from driver
 * @slave_cnt:		Number of slaves in group
 */
काष्ठा nfp_fl_lag_group अणु
	अचिन्हित पूर्णांक group_id;
	u8 group_inst;
	काष्ठा list_head list;
	काष्ठा net_device *master_ndev;
	bool dirty;
	bool offloaded;
	bool to_हटाओ;
	bool to_destroy;
	अचिन्हित पूर्णांक slave_cnt;
पूर्ण;

#घोषणा NFP_FL_LAG_PKT_NUMBER_MASK	GENMASK(30, 0)
#घोषणा NFP_FL_LAG_VERSION_MASK		GENMASK(22, 0)
#घोषणा NFP_FL_LAG_HOST_TTL		0xff

/* Use this ID with zero members to ack a batch config */
#घोषणा NFP_FL_LAG_SYNC_ID		0
#घोषणा NFP_FL_LAG_GROUP_MIN		1 /* ID 0 reserved */
#घोषणा NFP_FL_LAG_GROUP_MAX		32 /* IDs 1 to 31 are valid */

/* रुको क्रम more config */
#घोषणा NFP_FL_LAG_DELAY		(msecs_to_jअगरfies(2))

#घोषणा NFP_FL_LAG_RETRANS_LIMIT	100 /* max retrans cmsgs to store */

अटल अचिन्हित पूर्णांक nfp_fl_get_next_pkt_number(काष्ठा nfp_fl_lag *lag)
अणु
	lag->pkt_num++;
	lag->pkt_num &= NFP_FL_LAG_PKT_NUMBER_MASK;

	वापस lag->pkt_num;
पूर्ण

अटल व्योम nfp_fl_increment_version(काष्ठा nfp_fl_lag *lag)
अणु
	/* LSB is not considered by firmware so add 2 क्रम each increment. */
	lag->batch_ver += 2;
	lag->batch_ver &= NFP_FL_LAG_VERSION_MASK;

	/* Zero is reserved by firmware. */
	अगर (!lag->batch_ver)
		lag->batch_ver += 2;
पूर्ण

अटल काष्ठा nfp_fl_lag_group *
nfp_fl_lag_group_create(काष्ठा nfp_fl_lag *lag, काष्ठा net_device *master)
अणु
	काष्ठा nfp_fl_lag_group *group;
	काष्ठा nfp_flower_priv *priv;
	पूर्णांक id;

	priv = container_of(lag, काष्ठा nfp_flower_priv, nfp_lag);

	id = ida_simple_get(&lag->ida_handle, NFP_FL_LAG_GROUP_MIN,
			    NFP_FL_LAG_GROUP_MAX, GFP_KERNEL);
	अगर (id < 0) अणु
		nfp_flower_cmsg_warn(priv->app,
				     "No more bonding groups available\n");
		वापस ERR_PTR(id);
	पूर्ण

	group = kदो_स्मृति(माप(*group), GFP_KERNEL);
	अगर (!group) अणु
		ida_simple_हटाओ(&lag->ida_handle, id);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	group->group_id = id;
	group->master_ndev = master;
	group->dirty = true;
	group->offloaded = false;
	group->to_हटाओ = false;
	group->to_destroy = false;
	group->slave_cnt = 0;
	group->group_inst = ++lag->global_inst;
	list_add_tail(&group->list, &lag->group_list);

	वापस group;
पूर्ण

अटल काष्ठा nfp_fl_lag_group *
nfp_fl_lag_find_group_क्रम_master_with_lag(काष्ठा nfp_fl_lag *lag,
					  काष्ठा net_device *master)
अणु
	काष्ठा nfp_fl_lag_group *entry;

	अगर (!master)
		वापस शून्य;

	list_क्रम_each_entry(entry, &lag->group_list, list)
		अगर (entry->master_ndev == master)
			वापस entry;

	वापस शून्य;
पूर्ण

पूर्णांक nfp_flower_lag_populate_pre_action(काष्ठा nfp_app *app,
				       काष्ठा net_device *master,
				       काष्ठा nfp_fl_pre_lag *pre_act,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_fl_lag_group *group = शून्य;
	__be32 temp_vers;

	mutex_lock(&priv->nfp_lag.lock);
	group = nfp_fl_lag_find_group_क्रम_master_with_lag(&priv->nfp_lag,
							  master);
	अगर (!group) अणु
		mutex_unlock(&priv->nfp_lag.lock);
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: group does not exist for LAG action");
		वापस -ENOENT;
	पूर्ण

	pre_act->group_id = cpu_to_be16(group->group_id);
	temp_vers = cpu_to_be32(priv->nfp_lag.batch_ver <<
				NFP_FL_PRE_LAG_VER_OFF);
	स_नकल(pre_act->lag_version, &temp_vers, 3);
	pre_act->instance = group->group_inst;
	mutex_unlock(&priv->nfp_lag.lock);

	वापस 0;
पूर्ण

पूर्णांक nfp_flower_lag_get_output_id(काष्ठा nfp_app *app, काष्ठा net_device *master)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_fl_lag_group *group = शून्य;
	पूर्णांक group_id = -ENOENT;

	mutex_lock(&priv->nfp_lag.lock);
	group = nfp_fl_lag_find_group_क्रम_master_with_lag(&priv->nfp_lag,
							  master);
	अगर (group)
		group_id = group->group_id;
	mutex_unlock(&priv->nfp_lag.lock);

	वापस group_id;
पूर्ण

अटल पूर्णांक
nfp_fl_lag_config_group(काष्ठा nfp_fl_lag *lag, काष्ठा nfp_fl_lag_group *group,
			काष्ठा net_device **active_members,
			अचिन्हित पूर्णांक member_cnt, क्रमागत nfp_fl_lag_batch *batch)
अणु
	काष्ठा nfp_flower_cmsg_lag_config *cmsg_payload;
	काष्ठा nfp_flower_priv *priv;
	अचिन्हित दीर्घ पूर्णांक flags;
	अचिन्हित पूर्णांक size, i;
	काष्ठा sk_buff *skb;

	priv = container_of(lag, काष्ठा nfp_flower_priv, nfp_lag);
	size = माप(*cmsg_payload) + माप(__be32) * member_cnt;
	skb = nfp_flower_cmsg_alloc(priv->app, size,
				    NFP_FLOWER_CMSG_TYPE_LAG_CONFIG,
				    GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	cmsg_payload = nfp_flower_cmsg_get_data(skb);
	flags = 0;

	/* Increment batch version क्रम each new batch of config messages. */
	अगर (*batch == NFP_FL_LAG_BATCH_FIRST) अणु
		flags |= NFP_FL_LAG_FIRST;
		nfp_fl_increment_version(lag);
		*batch = NFP_FL_LAG_BATCH_MEMBER;
	पूर्ण

	/* If it is a reset msg then it is also the end of the batch. */
	अगर (lag->rst_cfg) अणु
		flags |= NFP_FL_LAG_RESET;
		*batch = NFP_FL_LAG_BATCH_FINISHED;
	पूर्ण

	/* To संकेत the end of a batch, both the चयन and last flags are set
	 * and the the reserved SYNC group ID is used.
	 */
	अगर (*batch == NFP_FL_LAG_BATCH_FINISHED) अणु
		flags |= NFP_FL_LAG_SWITCH | NFP_FL_LAG_LAST;
		lag->rst_cfg = false;
		cmsg_payload->group_id = cpu_to_be32(NFP_FL_LAG_SYNC_ID);
		cmsg_payload->group_inst = 0;
	पूर्ण अन्यथा अणु
		cmsg_payload->group_id = cpu_to_be32(group->group_id);
		cmsg_payload->group_inst = cpu_to_be32(group->group_inst);
	पूर्ण

	cmsg_payload->reserved[0] = 0;
	cmsg_payload->reserved[1] = 0;
	cmsg_payload->ttl = NFP_FL_LAG_HOST_TTL;
	cmsg_payload->ctrl_flags = flags;
	cmsg_payload->batch_ver = cpu_to_be32(lag->batch_ver);
	cmsg_payload->pkt_number = cpu_to_be32(nfp_fl_get_next_pkt_number(lag));

	क्रम (i = 0; i < member_cnt; i++)
		cmsg_payload->members[i] =
			cpu_to_be32(nfp_repr_get_port_id(active_members[i]));

	nfp_ctrl_tx(priv->app->ctrl, skb);
	वापस 0;
पूर्ण

अटल व्योम nfp_fl_lag_करो_work(काष्ठा work_काष्ठा *work)
अणु
	क्रमागत nfp_fl_lag_batch batch = NFP_FL_LAG_BATCH_FIRST;
	काष्ठा nfp_fl_lag_group *entry, *storage;
	काष्ठा delayed_work *delayed_work;
	काष्ठा nfp_flower_priv *priv;
	काष्ठा nfp_fl_lag *lag;
	पूर्णांक err;

	delayed_work = to_delayed_work(work);
	lag = container_of(delayed_work, काष्ठा nfp_fl_lag, work);
	priv = container_of(lag, काष्ठा nfp_flower_priv, nfp_lag);

	mutex_lock(&lag->lock);
	list_क्रम_each_entry_safe(entry, storage, &lag->group_list, list) अणु
		काष्ठा net_device *iter_netdev, **acti_netdevs;
		काष्ठा nfp_flower_repr_priv *repr_priv;
		पूर्णांक active_count = 0, slaves = 0;
		काष्ठा nfp_repr *repr;
		अचिन्हित दीर्घ *flags;

		अगर (entry->to_हटाओ) अणु
			/* Active count of 0 deletes group on hw. */
			err = nfp_fl_lag_config_group(lag, entry, शून्य, 0,
						      &batch);
			अगर (!err) अणु
				entry->to_हटाओ = false;
				entry->offloaded = false;
			पूर्ण अन्यथा अणु
				nfp_flower_cmsg_warn(priv->app,
						     "group delete failed\n");
				schedule_delayed_work(&lag->work,
						      NFP_FL_LAG_DELAY);
				जारी;
			पूर्ण

			अगर (entry->to_destroy) अणु
				ida_simple_हटाओ(&lag->ida_handle,
						  entry->group_id);
				list_del(&entry->list);
				kमुक्त(entry);
			पूर्ण
			जारी;
		पूर्ण

		acti_netdevs = kदो_स्मृति_array(entry->slave_cnt,
					     माप(*acti_netdevs), GFP_KERNEL);

		/* Include sanity check in the loop. It may be that a bond has
		 * changed between processing the last notअगरication and the
		 * work queue triggering. If the number of slaves has changed
		 * or it now contains netdevs that cannot be offloaded, ignore
		 * the group until pending notअगरications are processed.
		 */
		rcu_पढ़ो_lock();
		क्रम_each_netdev_in_bond_rcu(entry->master_ndev, iter_netdev) अणु
			अगर (!nfp_netdev_is_nfp_repr(iter_netdev)) अणु
				slaves = 0;
				अवरोध;
			पूर्ण

			repr = netdev_priv(iter_netdev);

			अगर (repr->app != priv->app) अणु
				slaves = 0;
				अवरोध;
			पूर्ण

			slaves++;
			अगर (slaves > entry->slave_cnt)
				अवरोध;

			/* Check the ports क्रम state changes. */
			repr_priv = repr->app_priv;
			flags = &repr_priv->lag_port_flags;

			अगर (*flags & NFP_PORT_LAG_CHANGED) अणु
				*flags &= ~NFP_PORT_LAG_CHANGED;
				entry->dirty = true;
			पूर्ण

			अगर ((*flags & NFP_PORT_LAG_TX_ENABLED) &&
			    (*flags & NFP_PORT_LAG_LINK_UP))
				acti_netdevs[active_count++] = iter_netdev;
		पूर्ण
		rcu_पढ़ो_unlock();

		अगर (slaves != entry->slave_cnt || !entry->dirty) अणु
			kमुक्त(acti_netdevs);
			जारी;
		पूर्ण

		err = nfp_fl_lag_config_group(lag, entry, acti_netdevs,
					      active_count, &batch);
		अगर (!err) अणु
			entry->offloaded = true;
			entry->dirty = false;
		पूर्ण अन्यथा अणु
			nfp_flower_cmsg_warn(priv->app,
					     "group offload failed\n");
			schedule_delayed_work(&lag->work, NFP_FL_LAG_DELAY);
		पूर्ण

		kमुक्त(acti_netdevs);
	पूर्ण

	/* End the config batch अगर at least one packet has been batched. */
	अगर (batch == NFP_FL_LAG_BATCH_MEMBER) अणु
		batch = NFP_FL_LAG_BATCH_FINISHED;
		err = nfp_fl_lag_config_group(lag, शून्य, शून्य, 0, &batch);
		अगर (err)
			nfp_flower_cmsg_warn(priv->app,
					     "group batch end cmsg failed\n");
	पूर्ण

	mutex_unlock(&lag->lock);
पूर्ण

अटल पूर्णांक
nfp_fl_lag_put_unprocessed(काष्ठा nfp_fl_lag *lag, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_flower_cmsg_lag_config *cmsg_payload;

	cmsg_payload = nfp_flower_cmsg_get_data(skb);
	अगर (be32_to_cpu(cmsg_payload->group_id) >= NFP_FL_LAG_GROUP_MAX)
		वापस -EINVAL;

	/* Drop cmsg retrans अगर storage limit is exceeded to prevent
	 * overloading. If the fw notices that expected messages have not been
	 * received in a given समय block, it will request a full resync.
	 */
	अगर (skb_queue_len(&lag->retrans_skbs) >= NFP_FL_LAG_RETRANS_LIMIT)
		वापस -ENOSPC;

	__skb_queue_tail(&lag->retrans_skbs, skb);

	वापस 0;
पूर्ण

अटल व्योम nfp_fl_send_unprocessed(काष्ठा nfp_fl_lag *lag)
अणु
	काष्ठा nfp_flower_priv *priv;
	काष्ठा sk_buff *skb;

	priv = container_of(lag, काष्ठा nfp_flower_priv, nfp_lag);

	जबतक ((skb = __skb_dequeue(&lag->retrans_skbs)))
		nfp_ctrl_tx(priv->app->ctrl, skb);
पूर्ण

bool nfp_flower_lag_unprocessed_msg(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_flower_cmsg_lag_config *cmsg_payload;
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_fl_lag_group *group_entry;
	अचिन्हित दीर्घ पूर्णांक flags;
	bool store_skb = false;
	पूर्णांक err;

	cmsg_payload = nfp_flower_cmsg_get_data(skb);
	flags = cmsg_payload->ctrl_flags;

	/* Note the पूर्णांकentional fall through below. If DATA and XON are both
	 * set, the message will stored and sent again with the rest of the
	 * unprocessed messages list.
	 */

	/* Store */
	अगर (flags & NFP_FL_LAG_DATA)
		अगर (!nfp_fl_lag_put_unprocessed(&priv->nfp_lag, skb))
			store_skb = true;

	/* Send stored */
	अगर (flags & NFP_FL_LAG_XON)
		nfp_fl_send_unprocessed(&priv->nfp_lag);

	/* Resend all */
	अगर (flags & NFP_FL_LAG_SYNC) अणु
		/* To resend all config:
		 * 1) Clear all unprocessed messages
		 * 2) Mark all groups dirty
		 * 3) Reset NFP group config
		 * 4) Schedule a LAG config update
		 */

		__skb_queue_purge(&priv->nfp_lag.retrans_skbs);

		mutex_lock(&priv->nfp_lag.lock);
		list_क्रम_each_entry(group_entry, &priv->nfp_lag.group_list,
				    list)
			group_entry->dirty = true;

		err = nfp_flower_lag_reset(&priv->nfp_lag);
		अगर (err)
			nfp_flower_cmsg_warn(priv->app,
					     "mem err in group reset msg\n");
		mutex_unlock(&priv->nfp_lag.lock);

		schedule_delayed_work(&priv->nfp_lag.work, 0);
	पूर्ण

	वापस store_skb;
पूर्ण

अटल व्योम
nfp_fl_lag_schedule_group_हटाओ(काष्ठा nfp_fl_lag *lag,
				 काष्ठा nfp_fl_lag_group *group)
अणु
	group->to_हटाओ = true;

	schedule_delayed_work(&lag->work, NFP_FL_LAG_DELAY);
पूर्ण

अटल व्योम
nfp_fl_lag_schedule_group_delete(काष्ठा nfp_fl_lag *lag,
				 काष्ठा net_device *master)
अणु
	काष्ठा nfp_fl_lag_group *group;
	काष्ठा nfp_flower_priv *priv;

	priv = container_of(lag, काष्ठा nfp_flower_priv, nfp_lag);

	अगर (!netअगर_is_bond_master(master))
		वापस;

	mutex_lock(&lag->lock);
	group = nfp_fl_lag_find_group_क्रम_master_with_lag(lag, master);
	अगर (!group) अणु
		mutex_unlock(&lag->lock);
		nfp_warn(priv->app->cpp, "untracked bond got unregistered %s\n",
			 netdev_name(master));
		वापस;
	पूर्ण

	group->to_हटाओ = true;
	group->to_destroy = true;
	mutex_unlock(&lag->lock);

	schedule_delayed_work(&lag->work, NFP_FL_LAG_DELAY);
पूर्ण

अटल पूर्णांक
nfp_fl_lag_changeupper_event(काष्ठा nfp_fl_lag *lag,
			     काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा net_device *upper = info->upper_dev, *iter_netdev;
	काष्ठा netdev_lag_upper_info *lag_upper_info;
	काष्ठा nfp_fl_lag_group *group;
	काष्ठा nfp_flower_priv *priv;
	अचिन्हित पूर्णांक slave_count = 0;
	bool can_offload = true;
	काष्ठा nfp_repr *repr;

	अगर (!netअगर_is_lag_master(upper))
		वापस 0;

	priv = container_of(lag, काष्ठा nfp_flower_priv, nfp_lag);

	rcu_पढ़ो_lock();
	क्रम_each_netdev_in_bond_rcu(upper, iter_netdev) अणु
		अगर (!nfp_netdev_is_nfp_repr(iter_netdev)) अणु
			can_offload = false;
			अवरोध;
		पूर्ण
		repr = netdev_priv(iter_netdev);

		/* Ensure all ports are created by the same app/on same card. */
		अगर (repr->app != priv->app) अणु
			can_offload = false;
			अवरोध;
		पूर्ण

		slave_count++;
	पूर्ण
	rcu_पढ़ो_unlock();

	lag_upper_info = info->upper_info;

	/* Firmware supports active/backup and L3/L4 hash bonds. */
	अगर (lag_upper_info &&
	    lag_upper_info->tx_type != NETDEV_LAG_TX_TYPE_ACTIVEBACKUP &&
	    (lag_upper_info->tx_type != NETDEV_LAG_TX_TYPE_HASH ||
	     (lag_upper_info->hash_type != NETDEV_LAG_HASH_L34 &&
	      lag_upper_info->hash_type != NETDEV_LAG_HASH_E34 &&
	      lag_upper_info->hash_type != NETDEV_LAG_HASH_UNKNOWN))) अणु
		can_offload = false;
		nfp_flower_cmsg_warn(priv->app,
				     "Unable to offload tx_type %u hash %u\n",
				     lag_upper_info->tx_type,
				     lag_upper_info->hash_type);
	पूर्ण

	mutex_lock(&lag->lock);
	group = nfp_fl_lag_find_group_क्रम_master_with_lag(lag, upper);

	अगर (slave_count == 0 || !can_offload) अणु
		/* Cannot offload the group - हटाओ अगर previously offloaded. */
		अगर (group && group->offloaded)
			nfp_fl_lag_schedule_group_हटाओ(lag, group);

		mutex_unlock(&lag->lock);
		वापस 0;
	पूर्ण

	अगर (!group) अणु
		group = nfp_fl_lag_group_create(lag, upper);
		अगर (IS_ERR(group)) अणु
			mutex_unlock(&lag->lock);
			वापस PTR_ERR(group);
		पूर्ण
	पूर्ण

	group->dirty = true;
	group->slave_cnt = slave_count;

	/* Group may have been on queue क्रम removal but is now offfloable. */
	group->to_हटाओ = false;
	mutex_unlock(&lag->lock);

	schedule_delayed_work(&lag->work, NFP_FL_LAG_DELAY);
	वापस 0;
पूर्ण

अटल व्योम
nfp_fl_lag_changels_event(काष्ठा nfp_fl_lag *lag, काष्ठा net_device *netdev,
			  काष्ठा netdev_notअगरier_changelowerstate_info *info)
अणु
	काष्ठा netdev_lag_lower_state_info *lag_lower_info;
	काष्ठा nfp_flower_repr_priv *repr_priv;
	काष्ठा nfp_flower_priv *priv;
	काष्ठा nfp_repr *repr;
	अचिन्हित दीर्घ *flags;

	अगर (!netअगर_is_lag_port(netdev) || !nfp_netdev_is_nfp_repr(netdev))
		वापस;

	lag_lower_info = info->lower_state_info;
	अगर (!lag_lower_info)
		वापस;

	priv = container_of(lag, काष्ठा nfp_flower_priv, nfp_lag);
	repr = netdev_priv(netdev);

	/* Verअगरy that the repr is associated with this app. */
	अगर (repr->app != priv->app)
		वापस;

	repr_priv = repr->app_priv;
	flags = &repr_priv->lag_port_flags;

	mutex_lock(&lag->lock);
	अगर (lag_lower_info->link_up)
		*flags |= NFP_PORT_LAG_LINK_UP;
	अन्यथा
		*flags &= ~NFP_PORT_LAG_LINK_UP;

	अगर (lag_lower_info->tx_enabled)
		*flags |= NFP_PORT_LAG_TX_ENABLED;
	अन्यथा
		*flags &= ~NFP_PORT_LAG_TX_ENABLED;

	*flags |= NFP_PORT_LAG_CHANGED;
	mutex_unlock(&lag->lock);

	schedule_delayed_work(&lag->work, NFP_FL_LAG_DELAY);
पूर्ण

पूर्णांक nfp_flower_lag_netdev_event(काष्ठा nfp_flower_priv *priv,
				काष्ठा net_device *netdev,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा nfp_fl_lag *lag = &priv->nfp_lag;
	पूर्णांक err;

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER:
		err = nfp_fl_lag_changeupper_event(lag, ptr);
		अगर (err)
			वापस NOTIFY_BAD;
		वापस NOTIFY_OK;
	हाल NETDEV_CHANGELOWERSTATE:
		nfp_fl_lag_changels_event(lag, netdev, ptr);
		वापस NOTIFY_OK;
	हाल NETDEV_UNREGISTER:
		nfp_fl_lag_schedule_group_delete(lag, netdev);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

पूर्णांक nfp_flower_lag_reset(काष्ठा nfp_fl_lag *lag)
अणु
	क्रमागत nfp_fl_lag_batch batch = NFP_FL_LAG_BATCH_FIRST;

	lag->rst_cfg = true;
	वापस nfp_fl_lag_config_group(lag, शून्य, शून्य, 0, &batch);
पूर्ण

व्योम nfp_flower_lag_init(काष्ठा nfp_fl_lag *lag)
अणु
	INIT_DELAYED_WORK(&lag->work, nfp_fl_lag_करो_work);
	INIT_LIST_HEAD(&lag->group_list);
	mutex_init(&lag->lock);
	ida_init(&lag->ida_handle);

	__skb_queue_head_init(&lag->retrans_skbs);

	/* 0 is a reserved batch version so increment to first valid value. */
	nfp_fl_increment_version(lag);
पूर्ण

व्योम nfp_flower_lag_cleanup(काष्ठा nfp_fl_lag *lag)
अणु
	काष्ठा nfp_fl_lag_group *entry, *storage;

	cancel_delayed_work_sync(&lag->work);

	__skb_queue_purge(&lag->retrans_skbs);

	/* Remove all groups. */
	mutex_lock(&lag->lock);
	list_क्रम_each_entry_safe(entry, storage, &lag->group_list, list) अणु
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
	mutex_unlock(&lag->lock);
	mutex_destroy(&lag->lock);
	ida_destroy(&lag->ida_handle);
पूर्ण
