<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Facebook Inc.

#समावेश <linux/ethtool_netlink.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/vxlan.h>

क्रमागत udp_tunnel_nic_table_entry_flags अणु
	UDP_TUNNEL_NIC_ENTRY_ADD	= BIT(0),
	UDP_TUNNEL_NIC_ENTRY_DEL	= BIT(1),
	UDP_TUNNEL_NIC_ENTRY_OP_FAIL	= BIT(2),
	UDP_TUNNEL_NIC_ENTRY_FROZEN	= BIT(3),
पूर्ण;

काष्ठा udp_tunnel_nic_table_entry अणु
	__be16 port;
	u8 type;
	u8 flags;
	u16 use_cnt;
#घोषणा UDP_TUNNEL_NIC_USE_CNT_MAX	U16_MAX
	u8 hw_priv;
पूर्ण;

/**
 * काष्ठा udp_tunnel_nic - UDP tunnel port offload state
 * @work:	async work क्रम talking to hardware from process context
 * @dev:	netdev poपूर्णांकer
 * @need_sync:	at least one port start changed
 * @need_replay: space was मुक्तd, we need a replay of all ports
 * @work_pending: @work is currently scheduled
 * @n_tables:	number of tables under @entries
 * @missed:	biपंचांगap of tables which overflown
 * @entries:	table of tables of ports currently offloaded
 */
काष्ठा udp_tunnel_nic अणु
	काष्ठा work_काष्ठा work;

	काष्ठा net_device *dev;

	u8 need_sync:1;
	u8 need_replay:1;
	u8 work_pending:1;

	अचिन्हित पूर्णांक n_tables;
	अचिन्हित दीर्घ missed;
	काष्ठा udp_tunnel_nic_table_entry **entries;
पूर्ण;

/* We ensure all work काष्ठाs are करोne using driver state, but not the code.
 * We need a workqueue we can flush beक्रमe module माला_लो हटाओd.
 */
अटल काष्ठा workqueue_काष्ठा *udp_tunnel_nic_workqueue;

अटल स्थिर अक्षर *udp_tunnel_nic_tunnel_type_name(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल UDP_TUNNEL_TYPE_VXLAN:
		वापस "vxlan";
	हाल UDP_TUNNEL_TYPE_GENEVE:
		वापस "geneve";
	हाल UDP_TUNNEL_TYPE_VXLAN_GPE:
		वापस "vxlan-gpe";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल bool
udp_tunnel_nic_entry_is_मुक्त(काष्ठा udp_tunnel_nic_table_entry *entry)
अणु
	वापस entry->use_cnt == 0 && !entry->flags;
पूर्ण

अटल bool
udp_tunnel_nic_entry_is_present(काष्ठा udp_tunnel_nic_table_entry *entry)
अणु
	वापस entry->use_cnt && !(entry->flags & ~UDP_TUNNEL_NIC_ENTRY_FROZEN);
पूर्ण

अटल bool
udp_tunnel_nic_entry_is_frozen(काष्ठा udp_tunnel_nic_table_entry *entry)
अणु
	वापस entry->flags & UDP_TUNNEL_NIC_ENTRY_FROZEN;
पूर्ण

अटल व्योम
udp_tunnel_nic_entry_मुक्तze_used(काष्ठा udp_tunnel_nic_table_entry *entry)
अणु
	अगर (!udp_tunnel_nic_entry_is_मुक्त(entry))
		entry->flags |= UDP_TUNNEL_NIC_ENTRY_FROZEN;
पूर्ण

अटल व्योम
udp_tunnel_nic_entry_unमुक्तze(काष्ठा udp_tunnel_nic_table_entry *entry)
अणु
	entry->flags &= ~UDP_TUNNEL_NIC_ENTRY_FROZEN;
पूर्ण

अटल bool
udp_tunnel_nic_entry_is_queued(काष्ठा udp_tunnel_nic_table_entry *entry)
अणु
	वापस entry->flags & (UDP_TUNNEL_NIC_ENTRY_ADD |
			       UDP_TUNNEL_NIC_ENTRY_DEL);
पूर्ण

अटल व्योम
udp_tunnel_nic_entry_queue(काष्ठा udp_tunnel_nic *utn,
			   काष्ठा udp_tunnel_nic_table_entry *entry,
			   अचिन्हित पूर्णांक flag)
अणु
	entry->flags |= flag;
	utn->need_sync = 1;
पूर्ण

अटल व्योम
udp_tunnel_nic_ti_from_entry(काष्ठा udp_tunnel_nic_table_entry *entry,
			     काष्ठा udp_tunnel_info *ti)
अणु
	स_रखो(ti, 0, माप(*ti));
	ti->port = entry->port;
	ti->type = entry->type;
	ti->hw_priv = entry->hw_priv;
पूर्ण

अटल bool
udp_tunnel_nic_is_empty(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < utn->n_tables; i++)
		क्रम (j = 0; j < info->tables[i].n_entries; j++)
			अगर (!udp_tunnel_nic_entry_is_मुक्त(&utn->entries[i][j]))
				वापस false;
	वापस true;
पूर्ण

अटल bool
udp_tunnel_nic_should_replay(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn)
अणु
	स्थिर काष्ठा udp_tunnel_nic_table_info *table;
	अचिन्हित पूर्णांक i, j;

	अगर (!utn->missed)
		वापस false;

	क्रम (i = 0; i < utn->n_tables; i++) अणु
		table = &dev->udp_tunnel_nic_info->tables[i];
		अगर (!test_bit(i, &utn->missed))
			जारी;

		क्रम (j = 0; j < table->n_entries; j++)
			अगर (udp_tunnel_nic_entry_is_मुक्त(&utn->entries[i][j]))
				वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम
__udp_tunnel_nic_get_port(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			  अचिन्हित पूर्णांक idx, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा udp_tunnel_nic_table_entry *entry;
	काष्ठा udp_tunnel_nic *utn;

	utn = dev->udp_tunnel_nic;
	entry = &utn->entries[table][idx];

	अगर (entry->use_cnt)
		udp_tunnel_nic_ti_from_entry(entry, ti);
पूर्ण

अटल व्योम
__udp_tunnel_nic_set_port_priv(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			       अचिन्हित पूर्णांक idx, u8 priv)
अणु
	dev->udp_tunnel_nic->entries[table][idx].hw_priv = priv;
पूर्ण

अटल व्योम
udp_tunnel_nic_entry_update_करोne(काष्ठा udp_tunnel_nic_table_entry *entry,
				 पूर्णांक err)
अणु
	bool करोdgy = entry->flags & UDP_TUNNEL_NIC_ENTRY_OP_FAIL;

	WARN_ON_ONCE(entry->flags & UDP_TUNNEL_NIC_ENTRY_ADD &&
		     entry->flags & UDP_TUNNEL_NIC_ENTRY_DEL);

	अगर (entry->flags & UDP_TUNNEL_NIC_ENTRY_ADD &&
	    (!err || (err == -EEXIST && करोdgy)))
		entry->flags &= ~UDP_TUNNEL_NIC_ENTRY_ADD;

	अगर (entry->flags & UDP_TUNNEL_NIC_ENTRY_DEL &&
	    (!err || (err == -ENOENT && करोdgy)))
		entry->flags &= ~UDP_TUNNEL_NIC_ENTRY_DEL;

	अगर (!err)
		entry->flags &= ~UDP_TUNNEL_NIC_ENTRY_OP_FAIL;
	अन्यथा
		entry->flags |= UDP_TUNNEL_NIC_ENTRY_OP_FAIL;
पूर्ण

अटल व्योम
udp_tunnel_nic_device_sync_one(काष्ठा net_device *dev,
			       काष्ठा udp_tunnel_nic *utn,
			       अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा udp_tunnel_nic_table_entry *entry;
	काष्ठा udp_tunnel_info ti;
	पूर्णांक err;

	entry = &utn->entries[table][idx];
	अगर (!udp_tunnel_nic_entry_is_queued(entry))
		वापस;

	udp_tunnel_nic_ti_from_entry(entry, &ti);
	अगर (entry->flags & UDP_TUNNEL_NIC_ENTRY_ADD)
		err = dev->udp_tunnel_nic_info->set_port(dev, table, idx, &ti);
	अन्यथा
		err = dev->udp_tunnel_nic_info->unset_port(dev, table, idx,
							   &ti);
	udp_tunnel_nic_entry_update_करोne(entry, err);

	अगर (err)
		netdev_warn(dev,
			    "UDP tunnel port sync failed port %d type %s: %d\n",
			    be16_to_cpu(entry->port),
			    udp_tunnel_nic_tunnel_type_name(entry->type),
			    err);
पूर्ण

अटल व्योम
udp_tunnel_nic_device_sync_by_port(काष्ठा net_device *dev,
				   काष्ठा udp_tunnel_nic *utn)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < utn->n_tables; i++)
		क्रम (j = 0; j < info->tables[i].n_entries; j++)
			udp_tunnel_nic_device_sync_one(dev, utn, i, j);
पूर्ण

अटल व्योम
udp_tunnel_nic_device_sync_by_table(काष्ठा net_device *dev,
				    काष्ठा udp_tunnel_nic *utn)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक err;

	क्रम (i = 0; i < utn->n_tables; i++) अणु
		/* Find something that needs sync in this table */
		क्रम (j = 0; j < info->tables[i].n_entries; j++)
			अगर (udp_tunnel_nic_entry_is_queued(&utn->entries[i][j]))
				अवरोध;
		अगर (j == info->tables[i].n_entries)
			जारी;

		err = info->sync_table(dev, i);
		अगर (err)
			netdev_warn(dev, "UDP tunnel port sync failed for table %d: %d\n",
				    i, err);

		क्रम (j = 0; j < info->tables[i].n_entries; j++) अणु
			काष्ठा udp_tunnel_nic_table_entry *entry;

			entry = &utn->entries[i][j];
			अगर (udp_tunnel_nic_entry_is_queued(entry))
				udp_tunnel_nic_entry_update_करोne(entry, err);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
__udp_tunnel_nic_device_sync(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn)
अणु
	अगर (!utn->need_sync)
		वापस;

	अगर (dev->udp_tunnel_nic_info->sync_table)
		udp_tunnel_nic_device_sync_by_table(dev, utn);
	अन्यथा
		udp_tunnel_nic_device_sync_by_port(dev, utn);

	utn->need_sync = 0;
	/* Can't replay directly here, in case we come from the tunnel driver's
	 * notअगरication - trying to replay may deadlock inside tunnel driver.
	 */
	utn->need_replay = udp_tunnel_nic_should_replay(dev, utn);
पूर्ण

अटल व्योम
udp_tunnel_nic_device_sync(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	bool may_sleep;

	अगर (!utn->need_sync)
		वापस;

	/* Drivers which sleep in the callback need to update from
	 * the workqueue, अगर we come from the tunnel driver's notअगरication.
	 */
	may_sleep = info->flags & UDP_TUNNEL_NIC_INFO_MAY_SLEEP;
	अगर (!may_sleep)
		__udp_tunnel_nic_device_sync(dev, utn);
	अगर (may_sleep || utn->need_replay) अणु
		queue_work(udp_tunnel_nic_workqueue, &utn->work);
		utn->work_pending = 1;
	पूर्ण
पूर्ण

अटल bool
udp_tunnel_nic_table_is_capable(स्थिर काष्ठा udp_tunnel_nic_table_info *table,
				काष्ठा udp_tunnel_info *ti)
अणु
	वापस table->tunnel_types & ti->type;
पूर्ण

अटल bool
udp_tunnel_nic_is_capable(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn,
			  काष्ठा udp_tunnel_info *ti)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	अचिन्हित पूर्णांक i;

	/* Special हाल IPv4-only NICs */
	अगर (info->flags & UDP_TUNNEL_NIC_INFO_IPV4_ONLY &&
	    ti->sa_family != AF_INET)
		वापस false;

	क्रम (i = 0; i < utn->n_tables; i++)
		अगर (udp_tunnel_nic_table_is_capable(&info->tables[i], ti))
			वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक
udp_tunnel_nic_has_collision(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn,
			     काष्ठा udp_tunnel_info *ti)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	काष्ठा udp_tunnel_nic_table_entry *entry;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < utn->n_tables; i++)
		क्रम (j = 0; j < info->tables[i].n_entries; j++) अणु
			entry =	&utn->entries[i][j];

			अगर (!udp_tunnel_nic_entry_is_मुक्त(entry) &&
			    entry->port == ti->port &&
			    entry->type != ti->type) अणु
				__set_bit(i, &utn->missed);
				वापस true;
			पूर्ण
		पूर्ण
	वापस false;
पूर्ण

अटल व्योम
udp_tunnel_nic_entry_adj(काष्ठा udp_tunnel_nic *utn,
			 अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक idx, पूर्णांक use_cnt_adj)
अणु
	काष्ठा udp_tunnel_nic_table_entry *entry =  &utn->entries[table][idx];
	bool करोdgy = entry->flags & UDP_TUNNEL_NIC_ENTRY_OP_FAIL;
	अचिन्हित पूर्णांक from, to;

	WARN_ON(entry->use_cnt + (u32)use_cnt_adj > U16_MAX);

	/* If not going from used to unused or vice versa - all करोne.
	 * For करोdgy entries make sure we try to sync again (queue the entry).
	 */
	entry->use_cnt += use_cnt_adj;
	अगर (!करोdgy && !entry->use_cnt == !(entry->use_cnt - use_cnt_adj))
		वापस;

	/* Cancel the op beक्रमe it was sent to the device, अगर possible,
	 * otherwise we'd need to take special care to issue commands
	 * in the same order the ports arrived.
	 */
	अगर (use_cnt_adj < 0) अणु
		from = UDP_TUNNEL_NIC_ENTRY_ADD;
		to = UDP_TUNNEL_NIC_ENTRY_DEL;
	पूर्ण अन्यथा अणु
		from = UDP_TUNNEL_NIC_ENTRY_DEL;
		to = UDP_TUNNEL_NIC_ENTRY_ADD;
	पूर्ण

	अगर (entry->flags & from) अणु
		entry->flags &= ~from;
		अगर (!करोdgy)
			वापस;
	पूर्ण

	udp_tunnel_nic_entry_queue(utn, entry, to);
पूर्ण

अटल bool
udp_tunnel_nic_entry_try_adj(काष्ठा udp_tunnel_nic *utn,
			     अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक idx,
			     काष्ठा udp_tunnel_info *ti, पूर्णांक use_cnt_adj)
अणु
	काष्ठा udp_tunnel_nic_table_entry *entry =  &utn->entries[table][idx];

	अगर (udp_tunnel_nic_entry_is_मुक्त(entry) ||
	    entry->port != ti->port ||
	    entry->type != ti->type)
		वापस false;

	अगर (udp_tunnel_nic_entry_is_frozen(entry))
		वापस true;

	udp_tunnel_nic_entry_adj(utn, table, idx, use_cnt_adj);
	वापस true;
पूर्ण

/* Try to find existing matching entry and adjust its use count, instead of
 * adding a new one. Returns true अगर entry was found. In हाल of delete the
 * entry may have gotten हटाओd in the process, in which हाल it will be
 * queued क्रम removal.
 */
अटल bool
udp_tunnel_nic_try_existing(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn,
			    काष्ठा udp_tunnel_info *ti, पूर्णांक use_cnt_adj)
अणु
	स्थिर काष्ठा udp_tunnel_nic_table_info *table;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < utn->n_tables; i++) अणु
		table = &dev->udp_tunnel_nic_info->tables[i];
		अगर (!udp_tunnel_nic_table_is_capable(table, ti))
			जारी;

		क्रम (j = 0; j < table->n_entries; j++)
			अगर (udp_tunnel_nic_entry_try_adj(utn, i, j, ti,
							 use_cnt_adj))
				वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool
udp_tunnel_nic_add_existing(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn,
			    काष्ठा udp_tunnel_info *ti)
अणु
	वापस udp_tunnel_nic_try_existing(dev, utn, ti, +1);
पूर्ण

अटल bool
udp_tunnel_nic_del_existing(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn,
			    काष्ठा udp_tunnel_info *ti)
अणु
	वापस udp_tunnel_nic_try_existing(dev, utn, ti, -1);
पूर्ण

अटल bool
udp_tunnel_nic_add_new(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn,
		       काष्ठा udp_tunnel_info *ti)
अणु
	स्थिर काष्ठा udp_tunnel_nic_table_info *table;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < utn->n_tables; i++) अणु
		table = &dev->udp_tunnel_nic_info->tables[i];
		अगर (!udp_tunnel_nic_table_is_capable(table, ti))
			जारी;

		क्रम (j = 0; j < table->n_entries; j++) अणु
			काष्ठा udp_tunnel_nic_table_entry *entry;

			entry = &utn->entries[i][j];
			अगर (!udp_tunnel_nic_entry_is_मुक्त(entry))
				जारी;

			entry->port = ti->port;
			entry->type = ti->type;
			entry->use_cnt = 1;
			udp_tunnel_nic_entry_queue(utn, entry,
						   UDP_TUNNEL_NIC_ENTRY_ADD);
			वापस true;
		पूर्ण

		/* The dअगरferent table may still fit this port in, but there
		 * are no devices currently which have multiple tables accepting
		 * the same tunnel type, and false positives are okay.
		 */
		__set_bit(i, &utn->missed);
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम
__udp_tunnel_nic_add_port(काष्ठा net_device *dev, काष्ठा udp_tunnel_info *ti)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	काष्ठा udp_tunnel_nic *utn;

	utn = dev->udp_tunnel_nic;
	अगर (!utn)
		वापस;
	अगर (!netअगर_running(dev) && info->flags & UDP_TUNNEL_NIC_INFO_OPEN_ONLY)
		वापस;
	अगर (info->flags & UDP_TUNNEL_NIC_INFO_STATIC_IANA_VXLAN &&
	    ti->port == htons(IANA_VXLAN_UDP_PORT)) अणु
		अगर (ti->type != UDP_TUNNEL_TYPE_VXLAN)
			netdev_warn(dev, "device assumes port 4789 will be used by vxlan tunnels\n");
		वापस;
	पूर्ण

	अगर (!udp_tunnel_nic_is_capable(dev, utn, ti))
		वापस;

	/* It may happen that a tunnel of one type is हटाओd and dअगरferent
	 * tunnel type tries to reuse its port beक्रमe the device was inक्रमmed.
	 * Rely on utn->missed to re-add this port later.
	 */
	अगर (udp_tunnel_nic_has_collision(dev, utn, ti))
		वापस;

	अगर (!udp_tunnel_nic_add_existing(dev, utn, ti))
		udp_tunnel_nic_add_new(dev, utn, ti);

	udp_tunnel_nic_device_sync(dev, utn);
पूर्ण

अटल व्योम
__udp_tunnel_nic_del_port(काष्ठा net_device *dev, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा udp_tunnel_nic *utn;

	utn = dev->udp_tunnel_nic;
	अगर (!utn)
		वापस;

	अगर (!udp_tunnel_nic_is_capable(dev, utn, ti))
		वापस;

	udp_tunnel_nic_del_existing(dev, utn, ti);

	udp_tunnel_nic_device_sync(dev, utn);
पूर्ण

अटल व्योम __udp_tunnel_nic_reset_ntf(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	काष्ठा udp_tunnel_nic *utn;
	अचिन्हित पूर्णांक i, j;

	ASSERT_RTNL();

	utn = dev->udp_tunnel_nic;
	अगर (!utn)
		वापस;

	utn->need_sync = false;
	क्रम (i = 0; i < utn->n_tables; i++)
		क्रम (j = 0; j < info->tables[i].n_entries; j++) अणु
			काष्ठा udp_tunnel_nic_table_entry *entry;

			entry = &utn->entries[i][j];

			entry->flags &= ~(UDP_TUNNEL_NIC_ENTRY_DEL |
					  UDP_TUNNEL_NIC_ENTRY_OP_FAIL);
			/* We करोn't release rtnl across ops */
			WARN_ON(entry->flags & UDP_TUNNEL_NIC_ENTRY_FROZEN);
			अगर (!entry->use_cnt)
				जारी;

			udp_tunnel_nic_entry_queue(utn, entry,
						   UDP_TUNNEL_NIC_ENTRY_ADD);
		पूर्ण

	__udp_tunnel_nic_device_sync(dev, utn);
पूर्ण

अटल माप_प्रकार
__udp_tunnel_nic_dump_size(काष्ठा net_device *dev, अचिन्हित पूर्णांक table)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	काष्ठा udp_tunnel_nic *utn;
	अचिन्हित पूर्णांक j;
	माप_प्रकार size;

	utn = dev->udp_tunnel_nic;
	अगर (!utn)
		वापस 0;

	size = 0;
	क्रम (j = 0; j < info->tables[table].n_entries; j++) अणु
		अगर (!udp_tunnel_nic_entry_is_present(&utn->entries[table][j]))
			जारी;

		size += nla_total_size(0) +		 /* _TABLE_ENTRY */
			nla_total_size(माप(__be16)) + /* _ENTRY_PORT */
			nla_total_size(माप(u32));	 /* _ENTRY_TYPE */
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक
__udp_tunnel_nic_dump_ग_लिखो(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			    काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	काष्ठा udp_tunnel_nic *utn;
	काष्ठा nlattr *nest;
	अचिन्हित पूर्णांक j;

	utn = dev->udp_tunnel_nic;
	अगर (!utn)
		वापस 0;

	क्रम (j = 0; j < info->tables[table].n_entries; j++) अणु
		अगर (!udp_tunnel_nic_entry_is_present(&utn->entries[table][j]))
			जारी;

		nest = nla_nest_start(skb, ETHTOOL_A_TUNNEL_UDP_TABLE_ENTRY);

		अगर (nla_put_be16(skb, ETHTOOL_A_TUNNEL_UDP_ENTRY_PORT,
				 utn->entries[table][j].port) ||
		    nla_put_u32(skb, ETHTOOL_A_TUNNEL_UDP_ENTRY_TYPE,
				ilog2(utn->entries[table][j].type)))
			जाओ err_cancel;

		nla_nest_end(skb, nest);
	पूर्ण

	वापस 0;

err_cancel:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_ops __udp_tunnel_nic_ops = अणु
	.get_port	= __udp_tunnel_nic_get_port,
	.set_port_priv	= __udp_tunnel_nic_set_port_priv,
	.add_port	= __udp_tunnel_nic_add_port,
	.del_port	= __udp_tunnel_nic_del_port,
	.reset_ntf	= __udp_tunnel_nic_reset_ntf,
	.dump_size	= __udp_tunnel_nic_dump_size,
	.dump_ग_लिखो	= __udp_tunnel_nic_dump_ग_लिखो,
पूर्ण;

अटल व्योम
udp_tunnel_nic_flush(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < utn->n_tables; i++)
		क्रम (j = 0; j < info->tables[i].n_entries; j++) अणु
			पूर्णांक adj_cnt = -utn->entries[i][j].use_cnt;

			अगर (adj_cnt)
				udp_tunnel_nic_entry_adj(utn, i, j, adj_cnt);
		पूर्ण

	__udp_tunnel_nic_device_sync(dev, utn);

	क्रम (i = 0; i < utn->n_tables; i++)
		स_रखो(utn->entries[i], 0, array_size(info->tables[i].n_entries,
						      माप(**utn->entries)));
	WARN_ON(utn->need_sync);
	utn->need_replay = 0;
पूर्ण

अटल व्योम
udp_tunnel_nic_replay(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	काष्ठा udp_tunnel_nic_shared_node *node;
	अचिन्हित पूर्णांक i, j;

	/* Freeze all the ports we are alपढ़ोy tracking so that the replay
	 * करोes not द्विगुन up the refcount.
	 */
	क्रम (i = 0; i < utn->n_tables; i++)
		क्रम (j = 0; j < info->tables[i].n_entries; j++)
			udp_tunnel_nic_entry_मुक्तze_used(&utn->entries[i][j]);
	utn->missed = 0;
	utn->need_replay = 0;

	अगर (!info->shared) अणु
		udp_tunnel_get_rx_info(dev);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(node, &info->shared->devices, list)
			udp_tunnel_get_rx_info(node->dev);
	पूर्ण

	क्रम (i = 0; i < utn->n_tables; i++)
		क्रम (j = 0; j < info->tables[i].n_entries; j++)
			udp_tunnel_nic_entry_unमुक्तze(&utn->entries[i][j]);
पूर्ण

अटल व्योम udp_tunnel_nic_device_sync_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा udp_tunnel_nic *utn =
		container_of(work, काष्ठा udp_tunnel_nic, work);

	rtnl_lock();
	utn->work_pending = 0;
	__udp_tunnel_nic_device_sync(utn->dev, utn);

	अगर (utn->need_replay)
		udp_tunnel_nic_replay(utn->dev, utn);
	rtnl_unlock();
पूर्ण

अटल काष्ठा udp_tunnel_nic *
udp_tunnel_nic_alloc(स्थिर काष्ठा udp_tunnel_nic_info *info,
		     अचिन्हित पूर्णांक n_tables)
अणु
	काष्ठा udp_tunnel_nic *utn;
	अचिन्हित पूर्णांक i;

	utn = kzalloc(माप(*utn), GFP_KERNEL);
	अगर (!utn)
		वापस शून्य;
	utn->n_tables = n_tables;
	INIT_WORK(&utn->work, udp_tunnel_nic_device_sync_work);

	utn->entries = kदो_स्मृति_array(n_tables, माप(व्योम *), GFP_KERNEL);
	अगर (!utn->entries)
		जाओ err_मुक्त_utn;

	क्रम (i = 0; i < n_tables; i++) अणु
		utn->entries[i] = kसुस्मृति(info->tables[i].n_entries,
					  माप(*utn->entries[i]), GFP_KERNEL);
		अगर (!utn->entries[i])
			जाओ err_मुक्त_prev_entries;
	पूर्ण

	वापस utn;

err_मुक्त_prev_entries:
	जबतक (i--)
		kमुक्त(utn->entries[i]);
	kमुक्त(utn->entries);
err_मुक्त_utn:
	kमुक्त(utn);
	वापस शून्य;
पूर्ण

अटल व्योम udp_tunnel_nic_मुक्त(काष्ठा udp_tunnel_nic *utn)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < utn->n_tables; i++)
		kमुक्त(utn->entries[i]);
	kमुक्त(utn->entries);
	kमुक्त(utn);
पूर्ण

अटल पूर्णांक udp_tunnel_nic_रेजिस्टर(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;
	काष्ठा udp_tunnel_nic_shared_node *node = शून्य;
	काष्ठा udp_tunnel_nic *utn;
	अचिन्हित पूर्णांक n_tables, i;

	BUILD_BUG_ON(माप(utn->missed) * BITS_PER_BYTE <
		     UDP_TUNNEL_NIC_MAX_TABLES);
	/* Expect use count of at most 2 (IPv4, IPv6) per device */
	BUILD_BUG_ON(UDP_TUNNEL_NIC_USE_CNT_MAX <
		     UDP_TUNNEL_NIC_MAX_SHARING_DEVICES * 2);

	/* Check that the driver info is sane */
	अगर (WARN_ON(!info->set_port != !info->unset_port) ||
	    WARN_ON(!info->set_port == !info->sync_table) ||
	    WARN_ON(!info->tables[0].n_entries))
		वापस -EINVAL;

	अगर (WARN_ON(info->shared &&
		    info->flags & UDP_TUNNEL_NIC_INFO_OPEN_ONLY))
		वापस -EINVAL;

	n_tables = 1;
	क्रम (i = 1; i < UDP_TUNNEL_NIC_MAX_TABLES; i++) अणु
		अगर (!info->tables[i].n_entries)
			जारी;

		n_tables++;
		अगर (WARN_ON(!info->tables[i - 1].n_entries))
			वापस -EINVAL;
	पूर्ण

	/* Create UDP tunnel state काष्ठाures */
	अगर (info->shared) अणु
		node = kzalloc(माप(*node), GFP_KERNEL);
		अगर (!node)
			वापस -ENOMEM;

		node->dev = dev;
	पूर्ण

	अगर (info->shared && info->shared->udp_tunnel_nic_info) अणु
		utn = info->shared->udp_tunnel_nic_info;
	पूर्ण अन्यथा अणु
		utn = udp_tunnel_nic_alloc(info, n_tables);
		अगर (!utn) अणु
			kमुक्त(node);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (info->shared) अणु
		अगर (!info->shared->udp_tunnel_nic_info) अणु
			INIT_LIST_HEAD(&info->shared->devices);
			info->shared->udp_tunnel_nic_info = utn;
		पूर्ण

		list_add_tail(&node->list, &info->shared->devices);
	पूर्ण

	utn->dev = dev;
	dev_hold(dev);
	dev->udp_tunnel_nic = utn;

	अगर (!(info->flags & UDP_TUNNEL_NIC_INFO_OPEN_ONLY))
		udp_tunnel_get_rx_info(dev);

	वापस 0;
पूर्ण

अटल व्योम
udp_tunnel_nic_unरेजिस्टर(काष्ठा net_device *dev, काष्ठा udp_tunnel_nic *utn)
अणु
	स्थिर काष्ठा udp_tunnel_nic_info *info = dev->udp_tunnel_nic_info;

	/* For a shared table हटाओ this dev from the list of sharing devices
	 * and अगर there are other devices just detach.
	 */
	अगर (info->shared) अणु
		काष्ठा udp_tunnel_nic_shared_node *node, *first;

		list_क्रम_each_entry(node, &info->shared->devices, list)
			अगर (node->dev == dev)
				अवरोध;
		अगर (node->dev != dev)
			वापस;

		list_del(&node->list);
		kमुक्त(node);

		first = list_first_entry_or_null(&info->shared->devices,
						 typeof(*first), list);
		अगर (first) अणु
			udp_tunnel_drop_rx_info(dev);
			utn->dev = first->dev;
			जाओ release_dev;
		पूर्ण

		info->shared->udp_tunnel_nic_info = शून्य;
	पूर्ण

	/* Flush beक्रमe we check work, so we करोn't waste समय adding entries
	 * from the work which we will boot immediately.
	 */
	udp_tunnel_nic_flush(dev, utn);

	/* Wait क्रम the work to be करोne using the state, netdev core will
	 * retry unरेजिस्टर until we give up our reference on this device.
	 */
	अगर (utn->work_pending)
		वापस;

	udp_tunnel_nic_मुक्त(utn);
release_dev:
	dev->udp_tunnel_nic = शून्य;
	dev_put(dev);
पूर्ण

अटल पूर्णांक
udp_tunnel_nic_netdevice_event(काष्ठा notअगरier_block *unused,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	स्थिर काष्ठा udp_tunnel_nic_info *info;
	काष्ठा udp_tunnel_nic *utn;

	info = dev->udp_tunnel_nic_info;
	अगर (!info)
		वापस NOTIFY_DONE;

	अगर (event == NETDEV_REGISTER) अणु
		पूर्णांक err;

		err = udp_tunnel_nic_रेजिस्टर(dev);
		अगर (err)
			netdev_WARN(dev, "failed to register for UDP tunnel offloads: %d", err);
		वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण
	/* All other events will need the udp_tunnel_nic state */
	utn = dev->udp_tunnel_nic;
	अगर (!utn)
		वापस NOTIFY_DONE;

	अगर (event == NETDEV_UNREGISTER) अणु
		udp_tunnel_nic_unरेजिस्टर(dev, utn);
		वापस NOTIFY_OK;
	पूर्ण

	/* All other events only matter अगर NIC has to be programmed खोलो */
	अगर (!(info->flags & UDP_TUNNEL_NIC_INFO_OPEN_ONLY))
		वापस NOTIFY_DONE;

	अगर (event == NETDEV_UP) अणु
		WARN_ON(!udp_tunnel_nic_is_empty(dev, utn));
		udp_tunnel_get_rx_info(dev);
		वापस NOTIFY_OK;
	पूर्ण
	अगर (event == NETDEV_GOING_DOWN) अणु
		udp_tunnel_nic_flush(dev, utn);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block udp_tunnel_nic_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = udp_tunnel_nic_netdevice_event,
पूर्ण;

अटल पूर्णांक __init udp_tunnel_nic_init_module(व्योम)
अणु
	पूर्णांक err;

	udp_tunnel_nic_workqueue = alloc_workqueue("udp_tunnel_nic", 0, 0);
	अगर (!udp_tunnel_nic_workqueue)
		वापस -ENOMEM;

	rtnl_lock();
	udp_tunnel_nic_ops = &__udp_tunnel_nic_ops;
	rtnl_unlock();

	err = रेजिस्टर_netdevice_notअगरier(&udp_tunnel_nic_notअगरier_block);
	अगर (err)
		जाओ err_unset_ops;

	वापस 0;

err_unset_ops:
	rtnl_lock();
	udp_tunnel_nic_ops = शून्य;
	rtnl_unlock();
	destroy_workqueue(udp_tunnel_nic_workqueue);
	वापस err;
पूर्ण
late_initcall(udp_tunnel_nic_init_module);

अटल व्योम __निकास udp_tunnel_nic_cleanup_module(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&udp_tunnel_nic_notअगरier_block);

	rtnl_lock();
	udp_tunnel_nic_ops = शून्य;
	rtnl_unlock();

	destroy_workqueue(udp_tunnel_nic_workqueue);
पूर्ण
module_निकास(udp_tunnel_nic_cleanup_module);

MODULE_LICENSE("GPL");
