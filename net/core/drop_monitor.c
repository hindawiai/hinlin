<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Monitoring code क्रम network dropped packet alerts
 *
 * Copyright (C) 2009 Neil Horman <nhorman@tuxdriver.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/inet.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/netlink.h>
#समावेश <linux/net_dropmon.h>
#समावेश <linux/percpu.h>
#समावेश <linux/समयr.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <net/genetlink.h>
#समावेश <net/netevent.h>
#समावेश <net/flow_offload.h>
#समावेश <net/devlink.h>

#समावेश <trace/events/skb.h>
#समावेश <trace/events/napi.h>
#समावेश <trace/events/devlink.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा TRACE_ON 1
#घोषणा TRACE_OFF 0

/*
 * Globals, our netlink socket poपूर्णांकer
 * and the work handle that will send up
 * netlink alerts
 */
अटल पूर्णांक trace_state = TRACE_OFF;
अटल bool monitor_hw;

/* net_dm_mutex
 *
 * An overall lock guarding every operation coming from userspace.
 * It also guards the global 'hw_stats_list' list.
 */
अटल DEFINE_MUTEX(net_dm_mutex);

काष्ठा net_dm_stats अणु
	u64 dropped;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

#घोषणा NET_DM_MAX_HW_TRAP_NAME_LEN 40

काष्ठा net_dm_hw_entry अणु
	अक्षर trap_name[NET_DM_MAX_HW_TRAP_NAME_LEN];
	u32 count;
पूर्ण;

काष्ठा net_dm_hw_entries अणु
	u32 num_entries;
	काष्ठा net_dm_hw_entry entries[];
पूर्ण;

काष्ठा per_cpu_dm_data अणु
	spinlock_t		lock;	/* Protects 'skb', 'hw_entries' and
					 * 'send_timer'
					 */
	जोड़ अणु
		काष्ठा sk_buff			*skb;
		काष्ठा net_dm_hw_entries	*hw_entries;
	पूर्ण;
	काष्ठा sk_buff_head	drop_queue;
	काष्ठा work_काष्ठा	dm_alert_work;
	काष्ठा समयr_list	send_समयr;
	काष्ठा net_dm_stats	stats;
पूर्ण;

काष्ठा dm_hw_stat_delta अणु
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ last_rx;
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
	अचिन्हित दीर्घ last_drop_val;
पूर्ण;

अटल काष्ठा genl_family net_drop_monitor_family;

अटल DEFINE_PER_CPU(काष्ठा per_cpu_dm_data, dm_cpu_data);
अटल DEFINE_PER_CPU(काष्ठा per_cpu_dm_data, dm_hw_cpu_data);

अटल पूर्णांक dm_hit_limit = 64;
अटल पूर्णांक dm_delay = 1;
अटल अचिन्हित दीर्घ dm_hw_check_delta = 2*HZ;
अटल LIST_HEAD(hw_stats_list);

अटल क्रमागत net_dm_alert_mode net_dm_alert_mode = NET_DM_ALERT_MODE_SUMMARY;
अटल u32 net_dm_trunc_len;
अटल u32 net_dm_queue_len = 1000;

काष्ठा net_dm_alert_ops अणु
	व्योम (*kमुक्त_skb_probe)(व्योम *ignore, काष्ठा sk_buff *skb,
				व्योम *location);
	व्योम (*napi_poll_probe)(व्योम *ignore, काष्ठा napi_काष्ठा *napi,
				पूर्णांक work, पूर्णांक budget);
	व्योम (*work_item_func)(काष्ठा work_काष्ठा *work);
	व्योम (*hw_work_item_func)(काष्ठा work_काष्ठा *work);
	व्योम (*hw_trap_probe)(व्योम *ignore, स्थिर काष्ठा devlink *devlink,
			      काष्ठा sk_buff *skb,
			      स्थिर काष्ठा devlink_trap_metadata *metadata);
पूर्ण;

काष्ठा net_dm_skb_cb अणु
	जोड़ अणु
		काष्ठा devlink_trap_metadata *hw_metadata;
		व्योम *pc;
	पूर्ण;
पूर्ण;

#घोषणा NET_DM_SKB_CB(__skb) ((काष्ठा net_dm_skb_cb *)&((__skb)->cb[0]))

अटल काष्ठा sk_buff *reset_per_cpu_data(काष्ठा per_cpu_dm_data *data)
अणु
	माप_प्रकार al;
	काष्ठा net_dm_alert_msg *msg;
	काष्ठा nlattr *nla;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	व्योम *msg_header;

	al = माप(काष्ठा net_dm_alert_msg);
	al += dm_hit_limit * माप(काष्ठा net_dm_drop_poपूर्णांक);
	al += माप(काष्ठा nlattr);

	skb = genlmsg_new(al, GFP_KERNEL);

	अगर (!skb)
		जाओ err;

	msg_header = genlmsg_put(skb, 0, 0, &net_drop_monitor_family,
				 0, NET_DM_CMD_ALERT);
	अगर (!msg_header) अणु
		nlmsg_मुक्त(skb);
		skb = शून्य;
		जाओ err;
	पूर्ण
	nla = nla_reserve(skb, NLA_UNSPEC,
			  माप(काष्ठा net_dm_alert_msg));
	अगर (!nla) अणु
		nlmsg_मुक्त(skb);
		skb = शून्य;
		जाओ err;
	पूर्ण
	msg = nla_data(nla);
	स_रखो(msg, 0, al);
	जाओ out;

err:
	mod_समयr(&data->send_समयr, jअगरfies + HZ / 10);
out:
	spin_lock_irqsave(&data->lock, flags);
	swap(data->skb, skb);
	spin_unlock_irqrestore(&data->lock, flags);

	अगर (skb) अणु
		काष्ठा nlmsghdr *nlh = (काष्ठा nlmsghdr *)skb->data;
		काष्ठा genlmsghdr *gnlh = (काष्ठा genlmsghdr *)nlmsg_data(nlh);

		genlmsg_end(skb, genlmsg_data(gnlh));
	पूर्ण

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा genl_multicast_group dropmon_mcgrps[] = अणु
	अणु .name = "events", पूर्ण,
पूर्ण;

अटल व्योम send_dm_alert(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा per_cpu_dm_data *data;

	data = container_of(work, काष्ठा per_cpu_dm_data, dm_alert_work);

	skb = reset_per_cpu_data(data);

	अगर (skb)
		genlmsg_multicast(&net_drop_monitor_family, skb, 0,
				  0, GFP_KERNEL);
पूर्ण

/*
 * This is the समयr function to delay the sending of an alert
 * in the event that more drops will arrive during the
 * hysteresis period.
 */
अटल व्योम sched_send_work(काष्ठा समयr_list *t)
अणु
	काष्ठा per_cpu_dm_data *data = from_समयr(data, t, send_समयr);

	schedule_work(&data->dm_alert_work);
पूर्ण

अटल व्योम trace_drop_common(काष्ठा sk_buff *skb, व्योम *location)
अणु
	काष्ठा net_dm_alert_msg *msg;
	काष्ठा net_dm_drop_poपूर्णांक *poपूर्णांक;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlattr *nla;
	पूर्णांक i;
	काष्ठा sk_buff *dskb;
	काष्ठा per_cpu_dm_data *data;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	data = this_cpu_ptr(&dm_cpu_data);
	spin_lock(&data->lock);
	dskb = data->skb;

	अगर (!dskb)
		जाओ out;

	nlh = (काष्ठा nlmsghdr *)dskb->data;
	nla = genlmsg_data(nlmsg_data(nlh));
	msg = nla_data(nla);
	poपूर्णांक = msg->poपूर्णांकs;
	क्रम (i = 0; i < msg->entries; i++) अणु
		अगर (!स_भेद(&location, &poपूर्णांक->pc, माप(व्योम *))) अणु
			poपूर्णांक->count++;
			जाओ out;
		पूर्ण
		poपूर्णांक++;
	पूर्ण
	अगर (msg->entries == dm_hit_limit)
		जाओ out;
	/*
	 * We need to create a new entry
	 */
	__nla_reserve_nohdr(dskb, माप(काष्ठा net_dm_drop_poपूर्णांक));
	nla->nla_len += NLA_ALIGN(माप(काष्ठा net_dm_drop_poपूर्णांक));
	स_नकल(poपूर्णांक->pc, &location, माप(व्योम *));
	poपूर्णांक->count = 1;
	msg->entries++;

	अगर (!समयr_pending(&data->send_समयr)) अणु
		data->send_समयr.expires = jअगरfies + dm_delay * HZ;
		add_समयr(&data->send_समयr);
	पूर्ण

out:
	spin_unlock_irqrestore(&data->lock, flags);
पूर्ण

अटल व्योम trace_kमुक्त_skb_hit(व्योम *ignore, काष्ठा sk_buff *skb, व्योम *location)
अणु
	trace_drop_common(skb, location);
पूर्ण

अटल व्योम trace_napi_poll_hit(व्योम *ignore, काष्ठा napi_काष्ठा *napi,
				पूर्णांक work, पूर्णांक budget)
अणु
	काष्ठा dm_hw_stat_delta *new_stat;

	/*
	 * Don't check napi काष्ठाures with no associated device
	 */
	अगर (!napi->dev)
		वापस;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(new_stat, &hw_stats_list, list) अणु
		/*
		 * only add a note to our monitor buffer अगर:
		 * 1) this is the dev we received on
		 * 2) its after the last_rx delta
		 * 3) our rx_dropped count has gone up
		 */
		अगर ((new_stat->dev == napi->dev)  &&
		    (समय_after(jअगरfies, new_stat->last_rx + dm_hw_check_delta)) &&
		    (napi->dev->stats.rx_dropped != new_stat->last_drop_val)) अणु
			trace_drop_common(शून्य, शून्य);
			new_stat->last_drop_val = napi->dev->stats.rx_dropped;
			new_stat->last_rx = jअगरfies;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल काष्ठा net_dm_hw_entries *
net_dm_hw_reset_per_cpu_data(काष्ठा per_cpu_dm_data *hw_data)
अणु
	काष्ठा net_dm_hw_entries *hw_entries;
	अचिन्हित दीर्घ flags;

	hw_entries = kzalloc(काष्ठा_size(hw_entries, entries, dm_hit_limit),
			     GFP_KERNEL);
	अगर (!hw_entries) अणु
		/* If the memory allocation failed, we try to perक्रमm another
		 * allocation in 1/10 second. Otherwise, the probe function
		 * will स्थिरantly bail out.
		 */
		mod_समयr(&hw_data->send_समयr, jअगरfies + HZ / 10);
	पूर्ण

	spin_lock_irqsave(&hw_data->lock, flags);
	swap(hw_data->hw_entries, hw_entries);
	spin_unlock_irqrestore(&hw_data->lock, flags);

	वापस hw_entries;
पूर्ण

अटल पूर्णांक net_dm_hw_entry_put(काष्ठा sk_buff *msg,
			       स्थिर काष्ठा net_dm_hw_entry *hw_entry)
अणु
	काष्ठा nlattr *attr;

	attr = nla_nest_start(msg, NET_DM_ATTR_HW_ENTRY);
	अगर (!attr)
		वापस -EMSGSIZE;

	अगर (nla_put_string(msg, NET_DM_ATTR_HW_TRAP_NAME, hw_entry->trap_name))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NET_DM_ATTR_HW_TRAP_COUNT, hw_entry->count))
		जाओ nla_put_failure;

	nla_nest_end(msg, attr);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक net_dm_hw_entries_put(काष्ठा sk_buff *msg,
				 स्थिर काष्ठा net_dm_hw_entries *hw_entries)
अणु
	काष्ठा nlattr *attr;
	पूर्णांक i;

	attr = nla_nest_start(msg, NET_DM_ATTR_HW_ENTRIES);
	अगर (!attr)
		वापस -EMSGSIZE;

	क्रम (i = 0; i < hw_entries->num_entries; i++) अणु
		पूर्णांक rc;

		rc = net_dm_hw_entry_put(msg, &hw_entries->entries[i]);
		अगर (rc)
			जाओ nla_put_failure;
	पूर्ण

	nla_nest_end(msg, attr);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
net_dm_hw_summary_report_fill(काष्ठा sk_buff *msg,
			      स्थिर काष्ठा net_dm_hw_entries *hw_entries)
अणु
	काष्ठा net_dm_alert_msg anc_hdr = अणु 0 पूर्ण;
	व्योम *hdr;
	पूर्णांक rc;

	hdr = genlmsg_put(msg, 0, 0, &net_drop_monitor_family, 0,
			  NET_DM_CMD_ALERT);
	अगर (!hdr)
		वापस -EMSGSIZE;

	/* We need to put the ancillary header in order not to अवरोध user
	 * space.
	 */
	अगर (nla_put(msg, NLA_UNSPEC, माप(anc_hdr), &anc_hdr))
		जाओ nla_put_failure;

	rc = net_dm_hw_entries_put(msg, hw_entries);
	अगर (rc)
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम net_dm_hw_summary_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा net_dm_hw_entries *hw_entries;
	काष्ठा per_cpu_dm_data *hw_data;
	काष्ठा sk_buff *msg;
	पूर्णांक rc;

	hw_data = container_of(work, काष्ठा per_cpu_dm_data, dm_alert_work);

	hw_entries = net_dm_hw_reset_per_cpu_data(hw_data);
	अगर (!hw_entries)
		वापस;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		जाओ out;

	rc = net_dm_hw_summary_report_fill(msg, hw_entries);
	अगर (rc) अणु
		nlmsg_मुक्त(msg);
		जाओ out;
	पूर्ण

	genlmsg_multicast(&net_drop_monitor_family, msg, 0, 0, GFP_KERNEL);

out:
	kमुक्त(hw_entries);
पूर्ण

अटल व्योम
net_dm_hw_trap_summary_probe(व्योम *ignore, स्थिर काष्ठा devlink *devlink,
			     काष्ठा sk_buff *skb,
			     स्थिर काष्ठा devlink_trap_metadata *metadata)
अणु
	काष्ठा net_dm_hw_entries *hw_entries;
	काष्ठा net_dm_hw_entry *hw_entry;
	काष्ठा per_cpu_dm_data *hw_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (metadata->trap_type == DEVLINK_TRAP_TYPE_CONTROL)
		वापस;

	hw_data = this_cpu_ptr(&dm_hw_cpu_data);
	spin_lock_irqsave(&hw_data->lock, flags);
	hw_entries = hw_data->hw_entries;

	अगर (!hw_entries)
		जाओ out;

	क्रम (i = 0; i < hw_entries->num_entries; i++) अणु
		hw_entry = &hw_entries->entries[i];
		अगर (!म_भेदन(hw_entry->trap_name, metadata->trap_name,
			     NET_DM_MAX_HW_TRAP_NAME_LEN - 1)) अणु
			hw_entry->count++;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (WARN_ON_ONCE(hw_entries->num_entries == dm_hit_limit))
		जाओ out;

	hw_entry = &hw_entries->entries[hw_entries->num_entries];
	strlcpy(hw_entry->trap_name, metadata->trap_name,
		NET_DM_MAX_HW_TRAP_NAME_LEN - 1);
	hw_entry->count = 1;
	hw_entries->num_entries++;

	अगर (!समयr_pending(&hw_data->send_समयr)) अणु
		hw_data->send_समयr.expires = jअगरfies + dm_delay * HZ;
		add_समयr(&hw_data->send_समयr);
	पूर्ण

out:
	spin_unlock_irqrestore(&hw_data->lock, flags);
पूर्ण

अटल स्थिर काष्ठा net_dm_alert_ops net_dm_alert_summary_ops = अणु
	.kमुक्त_skb_probe	= trace_kमुक्त_skb_hit,
	.napi_poll_probe	= trace_napi_poll_hit,
	.work_item_func		= send_dm_alert,
	.hw_work_item_func	= net_dm_hw_summary_work,
	.hw_trap_probe		= net_dm_hw_trap_summary_probe,
पूर्ण;

अटल व्योम net_dm_packet_trace_kमुक्त_skb_hit(व्योम *ignore,
					      काष्ठा sk_buff *skb,
					      व्योम *location)
अणु
	kसमय_प्रकार tstamp = kसमय_get_real();
	काष्ठा per_cpu_dm_data *data;
	काष्ठा sk_buff *nskb;
	अचिन्हित दीर्घ flags;

	अगर (!skb_mac_header_was_set(skb))
		वापस;

	nskb = skb_clone(skb, GFP_ATOMIC);
	अगर (!nskb)
		वापस;

	NET_DM_SKB_CB(nskb)->pc = location;
	/* Override the बारtamp because we care about the समय when the
	 * packet was dropped.
	 */
	nskb->tstamp = tstamp;

	data = this_cpu_ptr(&dm_cpu_data);

	spin_lock_irqsave(&data->drop_queue.lock, flags);
	अगर (skb_queue_len(&data->drop_queue) < net_dm_queue_len)
		__skb_queue_tail(&data->drop_queue, nskb);
	अन्यथा
		जाओ unlock_मुक्त;
	spin_unlock_irqrestore(&data->drop_queue.lock, flags);

	schedule_work(&data->dm_alert_work);

	वापस;

unlock_मुक्त:
	spin_unlock_irqrestore(&data->drop_queue.lock, flags);
	u64_stats_update_begin(&data->stats.syncp);
	data->stats.dropped++;
	u64_stats_update_end(&data->stats.syncp);
	consume_skb(nskb);
पूर्ण

अटल व्योम net_dm_packet_trace_napi_poll_hit(व्योम *ignore,
					      काष्ठा napi_काष्ठा *napi,
					      पूर्णांक work, पूर्णांक budget)
अणु
पूर्ण

अटल माप_प्रकार net_dm_in_port_size(व्योम)
अणु
	       /* NET_DM_ATTR_IN_PORT nest */
	वापस nla_total_size(0) +
	       /* NET_DM_ATTR_PORT_NETDEV_IFINDEX */
	       nla_total_size(माप(u32)) +
	       /* NET_DM_ATTR_PORT_NETDEV_NAME */
	       nla_total_size(IFNAMSIZ + 1);
पूर्ण

#घोषणा NET_DM_MAX_SYMBOL_LEN 40

अटल माप_प्रकार net_dm_packet_report_size(माप_प्रकार payload_len)
अणु
	माप_प्रकार size;

	size = nlmsg_msg_size(GENL_HDRLEN + net_drop_monitor_family.hdrsize);

	वापस NLMSG_ALIGN(size) +
	       /* NET_DM_ATTR_ORIGIN */
	       nla_total_size(माप(u16)) +
	       /* NET_DM_ATTR_PC */
	       nla_total_size(माप(u64)) +
	       /* NET_DM_ATTR_SYMBOL */
	       nla_total_size(NET_DM_MAX_SYMBOL_LEN + 1) +
	       /* NET_DM_ATTR_IN_PORT */
	       net_dm_in_port_size() +
	       /* NET_DM_ATTR_TIMESTAMP */
	       nla_total_size(माप(u64)) +
	       /* NET_DM_ATTR_ORIG_LEN */
	       nla_total_size(माप(u32)) +
	       /* NET_DM_ATTR_PROTO */
	       nla_total_size(माप(u16)) +
	       /* NET_DM_ATTR_PAYLOAD */
	       nla_total_size(payload_len);
पूर्ण

अटल पूर्णांक net_dm_packet_report_in_port_put(काष्ठा sk_buff *msg, पूर्णांक अगरindex,
					    स्थिर अक्षर *name)
अणु
	काष्ठा nlattr *attr;

	attr = nla_nest_start(msg, NET_DM_ATTR_IN_PORT);
	अगर (!attr)
		वापस -EMSGSIZE;

	अगर (अगरindex &&
	    nla_put_u32(msg, NET_DM_ATTR_PORT_NETDEV_IFINDEX, अगरindex))
		जाओ nla_put_failure;

	अगर (name && nla_put_string(msg, NET_DM_ATTR_PORT_NETDEV_NAME, name))
		जाओ nla_put_failure;

	nla_nest_end(msg, attr);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक net_dm_packet_report_fill(काष्ठा sk_buff *msg, काष्ठा sk_buff *skb,
				     माप_प्रकार payload_len)
अणु
	u64 pc = (u64)(uपूर्णांकptr_t) NET_DM_SKB_CB(skb)->pc;
	अक्षर buf[NET_DM_MAX_SYMBOL_LEN];
	काष्ठा nlattr *attr;
	व्योम *hdr;
	पूर्णांक rc;

	hdr = genlmsg_put(msg, 0, 0, &net_drop_monitor_family, 0,
			  NET_DM_CMD_PACKET_ALERT);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (nla_put_u16(msg, NET_DM_ATTR_ORIGIN, NET_DM_ORIGIN_SW))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(msg, NET_DM_ATTR_PC, pc, NET_DM_ATTR_PAD))
		जाओ nla_put_failure;

	snम_लिखो(buf, माप(buf), "%pS", NET_DM_SKB_CB(skb)->pc);
	अगर (nla_put_string(msg, NET_DM_ATTR_SYMBOL, buf))
		जाओ nla_put_failure;

	rc = net_dm_packet_report_in_port_put(msg, skb->skb_iअगर, शून्य);
	अगर (rc)
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(msg, NET_DM_ATTR_TIMESTAMP,
			      kसमय_प्रकारo_ns(skb->tstamp), NET_DM_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NET_DM_ATTR_ORIG_LEN, skb->len))
		जाओ nla_put_failure;

	अगर (!payload_len)
		जाओ out;

	अगर (nla_put_u16(msg, NET_DM_ATTR_PROTO, be16_to_cpu(skb->protocol)))
		जाओ nla_put_failure;

	attr = skb_put(msg, nla_total_size(payload_len));
	attr->nla_type = NET_DM_ATTR_PAYLOAD;
	attr->nla_len = nla_attr_size(payload_len);
	अगर (skb_copy_bits(skb, 0, nla_data(attr), payload_len))
		जाओ nla_put_failure;

out:
	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

#घोषणा NET_DM_MAX_PACKET_SIZE (0xffff - NLA_HDRLEN - NLA_ALIGNTO)

अटल व्योम net_dm_packet_report(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *msg;
	माप_प्रकार payload_len;
	पूर्णांक rc;

	/* Make sure we start copying the packet from the MAC header */
	अगर (skb->data > skb_mac_header(skb))
		skb_push(skb, skb->data - skb_mac_header(skb));
	अन्यथा
		skb_pull(skb, skb_mac_header(skb) - skb->data);

	/* Ensure packet fits inside a single netlink attribute */
	payload_len = min_t(माप_प्रकार, skb->len, NET_DM_MAX_PACKET_SIZE);
	अगर (net_dm_trunc_len)
		payload_len = min_t(माप_प्रकार, net_dm_trunc_len, payload_len);

	msg = nlmsg_new(net_dm_packet_report_size(payload_len), GFP_KERNEL);
	अगर (!msg)
		जाओ out;

	rc = net_dm_packet_report_fill(msg, skb, payload_len);
	अगर (rc) अणु
		nlmsg_मुक्त(msg);
		जाओ out;
	पूर्ण

	genlmsg_multicast(&net_drop_monitor_family, msg, 0, 0, GFP_KERNEL);

out:
	consume_skb(skb);
पूर्ण

अटल व्योम net_dm_packet_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा per_cpu_dm_data *data;
	काष्ठा sk_buff_head list;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	data = container_of(work, काष्ठा per_cpu_dm_data, dm_alert_work);

	__skb_queue_head_init(&list);

	spin_lock_irqsave(&data->drop_queue.lock, flags);
	skb_queue_splice_tail_init(&data->drop_queue, &list);
	spin_unlock_irqrestore(&data->drop_queue.lock, flags);

	जबतक ((skb = __skb_dequeue(&list)))
		net_dm_packet_report(skb);
पूर्ण

अटल माप_प्रकार
net_dm_flow_action_cookie_size(स्थिर काष्ठा devlink_trap_metadata *hw_metadata)
अणु
	वापस hw_metadata->fa_cookie ?
	       nla_total_size(hw_metadata->fa_cookie->cookie_len) : 0;
पूर्ण

अटल माप_प्रकार
net_dm_hw_packet_report_size(माप_प्रकार payload_len,
			     स्थिर काष्ठा devlink_trap_metadata *hw_metadata)
अणु
	माप_प्रकार size;

	size = nlmsg_msg_size(GENL_HDRLEN + net_drop_monitor_family.hdrsize);

	वापस NLMSG_ALIGN(size) +
	       /* NET_DM_ATTR_ORIGIN */
	       nla_total_size(माप(u16)) +
	       /* NET_DM_ATTR_HW_TRAP_GROUP_NAME */
	       nla_total_size(म_माप(hw_metadata->trap_group_name) + 1) +
	       /* NET_DM_ATTR_HW_TRAP_NAME */
	       nla_total_size(म_माप(hw_metadata->trap_name) + 1) +
	       /* NET_DM_ATTR_IN_PORT */
	       net_dm_in_port_size() +
	       /* NET_DM_ATTR_FLOW_ACTION_COOKIE */
	       net_dm_flow_action_cookie_size(hw_metadata) +
	       /* NET_DM_ATTR_TIMESTAMP */
	       nla_total_size(माप(u64)) +
	       /* NET_DM_ATTR_ORIG_LEN */
	       nla_total_size(माप(u32)) +
	       /* NET_DM_ATTR_PROTO */
	       nla_total_size(माप(u16)) +
	       /* NET_DM_ATTR_PAYLOAD */
	       nla_total_size(payload_len);
पूर्ण

अटल पूर्णांक net_dm_hw_packet_report_fill(काष्ठा sk_buff *msg,
					काष्ठा sk_buff *skb, माप_प्रकार payload_len)
अणु
	काष्ठा devlink_trap_metadata *hw_metadata;
	काष्ठा nlattr *attr;
	व्योम *hdr;

	hw_metadata = NET_DM_SKB_CB(skb)->hw_metadata;

	hdr = genlmsg_put(msg, 0, 0, &net_drop_monitor_family, 0,
			  NET_DM_CMD_PACKET_ALERT);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (nla_put_u16(msg, NET_DM_ATTR_ORIGIN, NET_DM_ORIGIN_HW))
		जाओ nla_put_failure;

	अगर (nla_put_string(msg, NET_DM_ATTR_HW_TRAP_GROUP_NAME,
			   hw_metadata->trap_group_name))
		जाओ nla_put_failure;

	अगर (nla_put_string(msg, NET_DM_ATTR_HW_TRAP_NAME,
			   hw_metadata->trap_name))
		जाओ nla_put_failure;

	अगर (hw_metadata->input_dev) अणु
		काष्ठा net_device *dev = hw_metadata->input_dev;
		पूर्णांक rc;

		rc = net_dm_packet_report_in_port_put(msg, dev->अगरindex,
						      dev->name);
		अगर (rc)
			जाओ nla_put_failure;
	पूर्ण

	अगर (hw_metadata->fa_cookie &&
	    nla_put(msg, NET_DM_ATTR_FLOW_ACTION_COOKIE,
		    hw_metadata->fa_cookie->cookie_len,
		    hw_metadata->fa_cookie->cookie))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(msg, NET_DM_ATTR_TIMESTAMP,
			      kसमय_प्रकारo_ns(skb->tstamp), NET_DM_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NET_DM_ATTR_ORIG_LEN, skb->len))
		जाओ nla_put_failure;

	अगर (!payload_len)
		जाओ out;

	अगर (nla_put_u16(msg, NET_DM_ATTR_PROTO, be16_to_cpu(skb->protocol)))
		जाओ nla_put_failure;

	attr = skb_put(msg, nla_total_size(payload_len));
	attr->nla_type = NET_DM_ATTR_PAYLOAD;
	attr->nla_len = nla_attr_size(payload_len);
	अगर (skb_copy_bits(skb, 0, nla_data(attr), payload_len))
		जाओ nla_put_failure;

out:
	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा devlink_trap_metadata *
net_dm_hw_metadata_copy(स्थिर काष्ठा devlink_trap_metadata *metadata)
अणु
	स्थिर काष्ठा flow_action_cookie *fa_cookie;
	काष्ठा devlink_trap_metadata *hw_metadata;
	स्थिर अक्षर *trap_group_name;
	स्थिर अक्षर *trap_name;

	hw_metadata = kzalloc(माप(*hw_metadata), GFP_ATOMIC);
	अगर (!hw_metadata)
		वापस शून्य;

	trap_group_name = kstrdup(metadata->trap_group_name, GFP_ATOMIC);
	अगर (!trap_group_name)
		जाओ मुक्त_hw_metadata;
	hw_metadata->trap_group_name = trap_group_name;

	trap_name = kstrdup(metadata->trap_name, GFP_ATOMIC);
	अगर (!trap_name)
		जाओ मुक्त_trap_group;
	hw_metadata->trap_name = trap_name;

	अगर (metadata->fa_cookie) अणु
		माप_प्रकार cookie_size = माप(*fa_cookie) +
				     metadata->fa_cookie->cookie_len;

		fa_cookie = kmemdup(metadata->fa_cookie, cookie_size,
				    GFP_ATOMIC);
		अगर (!fa_cookie)
			जाओ मुक्त_trap_name;
		hw_metadata->fa_cookie = fa_cookie;
	पूर्ण

	hw_metadata->input_dev = metadata->input_dev;
	अगर (hw_metadata->input_dev)
		dev_hold(hw_metadata->input_dev);

	वापस hw_metadata;

मुक्त_trap_name:
	kमुक्त(trap_name);
मुक्त_trap_group:
	kमुक्त(trap_group_name);
मुक्त_hw_metadata:
	kमुक्त(hw_metadata);
	वापस शून्य;
पूर्ण

अटल व्योम
net_dm_hw_metadata_मुक्त(स्थिर काष्ठा devlink_trap_metadata *hw_metadata)
अणु
	अगर (hw_metadata->input_dev)
		dev_put(hw_metadata->input_dev);
	kमुक्त(hw_metadata->fa_cookie);
	kमुक्त(hw_metadata->trap_name);
	kमुक्त(hw_metadata->trap_group_name);
	kमुक्त(hw_metadata);
पूर्ण

अटल व्योम net_dm_hw_packet_report(काष्ठा sk_buff *skb)
अणु
	काष्ठा devlink_trap_metadata *hw_metadata;
	काष्ठा sk_buff *msg;
	माप_प्रकार payload_len;
	पूर्णांक rc;

	अगर (skb->data > skb_mac_header(skb))
		skb_push(skb, skb->data - skb_mac_header(skb));
	अन्यथा
		skb_pull(skb, skb_mac_header(skb) - skb->data);

	payload_len = min_t(माप_प्रकार, skb->len, NET_DM_MAX_PACKET_SIZE);
	अगर (net_dm_trunc_len)
		payload_len = min_t(माप_प्रकार, net_dm_trunc_len, payload_len);

	hw_metadata = NET_DM_SKB_CB(skb)->hw_metadata;
	msg = nlmsg_new(net_dm_hw_packet_report_size(payload_len, hw_metadata),
			GFP_KERNEL);
	अगर (!msg)
		जाओ out;

	rc = net_dm_hw_packet_report_fill(msg, skb, payload_len);
	अगर (rc) अणु
		nlmsg_मुक्त(msg);
		जाओ out;
	पूर्ण

	genlmsg_multicast(&net_drop_monitor_family, msg, 0, 0, GFP_KERNEL);

out:
	net_dm_hw_metadata_मुक्त(NET_DM_SKB_CB(skb)->hw_metadata);
	consume_skb(skb);
पूर्ण

अटल व्योम net_dm_hw_packet_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा per_cpu_dm_data *hw_data;
	काष्ठा sk_buff_head list;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	hw_data = container_of(work, काष्ठा per_cpu_dm_data, dm_alert_work);

	__skb_queue_head_init(&list);

	spin_lock_irqsave(&hw_data->drop_queue.lock, flags);
	skb_queue_splice_tail_init(&hw_data->drop_queue, &list);
	spin_unlock_irqrestore(&hw_data->drop_queue.lock, flags);

	जबतक ((skb = __skb_dequeue(&list)))
		net_dm_hw_packet_report(skb);
पूर्ण

अटल व्योम
net_dm_hw_trap_packet_probe(व्योम *ignore, स्थिर काष्ठा devlink *devlink,
			    काष्ठा sk_buff *skb,
			    स्थिर काष्ठा devlink_trap_metadata *metadata)
अणु
	काष्ठा devlink_trap_metadata *n_hw_metadata;
	kसमय_प्रकार tstamp = kसमय_get_real();
	काष्ठा per_cpu_dm_data *hw_data;
	काष्ठा sk_buff *nskb;
	अचिन्हित दीर्घ flags;

	अगर (metadata->trap_type == DEVLINK_TRAP_TYPE_CONTROL)
		वापस;

	अगर (!skb_mac_header_was_set(skb))
		वापस;

	nskb = skb_clone(skb, GFP_ATOMIC);
	अगर (!nskb)
		वापस;

	n_hw_metadata = net_dm_hw_metadata_copy(metadata);
	अगर (!n_hw_metadata)
		जाओ मुक्त;

	NET_DM_SKB_CB(nskb)->hw_metadata = n_hw_metadata;
	nskb->tstamp = tstamp;

	hw_data = this_cpu_ptr(&dm_hw_cpu_data);

	spin_lock_irqsave(&hw_data->drop_queue.lock, flags);
	अगर (skb_queue_len(&hw_data->drop_queue) < net_dm_queue_len)
		__skb_queue_tail(&hw_data->drop_queue, nskb);
	अन्यथा
		जाओ unlock_मुक्त;
	spin_unlock_irqrestore(&hw_data->drop_queue.lock, flags);

	schedule_work(&hw_data->dm_alert_work);

	वापस;

unlock_मुक्त:
	spin_unlock_irqrestore(&hw_data->drop_queue.lock, flags);
	u64_stats_update_begin(&hw_data->stats.syncp);
	hw_data->stats.dropped++;
	u64_stats_update_end(&hw_data->stats.syncp);
	net_dm_hw_metadata_मुक्त(n_hw_metadata);
मुक्त:
	consume_skb(nskb);
पूर्ण

अटल स्थिर काष्ठा net_dm_alert_ops net_dm_alert_packet_ops = अणु
	.kमुक्त_skb_probe	= net_dm_packet_trace_kमुक्त_skb_hit,
	.napi_poll_probe	= net_dm_packet_trace_napi_poll_hit,
	.work_item_func		= net_dm_packet_work,
	.hw_work_item_func	= net_dm_hw_packet_work,
	.hw_trap_probe		= net_dm_hw_trap_packet_probe,
पूर्ण;

अटल स्थिर काष्ठा net_dm_alert_ops *net_dm_alert_ops_arr[] = अणु
	[NET_DM_ALERT_MODE_SUMMARY]	= &net_dm_alert_summary_ops,
	[NET_DM_ALERT_MODE_PACKET]	= &net_dm_alert_packet_ops,
पूर्ण;

#अगर IS_ENABLED(CONFIG_NET_DEVLINK)
अटल पूर्णांक net_dm_hw_probe_रेजिस्टर(स्थिर काष्ठा net_dm_alert_ops *ops)
अणु
	वापस रेजिस्टर_trace_devlink_trap_report(ops->hw_trap_probe, शून्य);
पूर्ण

अटल व्योम net_dm_hw_probe_unरेजिस्टर(स्थिर काष्ठा net_dm_alert_ops *ops)
अणु
	unरेजिस्टर_trace_devlink_trap_report(ops->hw_trap_probe, शून्य);
	tracepoपूर्णांक_synchronize_unरेजिस्टर();
पूर्ण
#अन्यथा
अटल पूर्णांक net_dm_hw_probe_रेजिस्टर(स्थिर काष्ठा net_dm_alert_ops *ops)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम net_dm_hw_probe_unरेजिस्टर(स्थिर काष्ठा net_dm_alert_ops *ops)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक net_dm_hw_monitor_start(काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा net_dm_alert_ops *ops;
	पूर्णांक cpu, rc;

	अगर (monitor_hw) अणु
		NL_SET_ERR_MSG_MOD(extack, "Hardware monitoring already enabled");
		वापस -EAGAIN;
	पूर्ण

	ops = net_dm_alert_ops_arr[net_dm_alert_mode];

	अगर (!try_module_get(THIS_MODULE)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to take reference on module");
		वापस -ENODEV;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा per_cpu_dm_data *hw_data = &per_cpu(dm_hw_cpu_data, cpu);
		काष्ठा net_dm_hw_entries *hw_entries;

		INIT_WORK(&hw_data->dm_alert_work, ops->hw_work_item_func);
		समयr_setup(&hw_data->send_समयr, sched_send_work, 0);
		hw_entries = net_dm_hw_reset_per_cpu_data(hw_data);
		kमुक्त(hw_entries);
	पूर्ण

	rc = net_dm_hw_probe_रेजिस्टर(ops);
	अगर (rc) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to connect probe to devlink_trap_probe() tracepoint");
		जाओ err_module_put;
	पूर्ण

	monitor_hw = true;

	वापस 0;

err_module_put:
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा per_cpu_dm_data *hw_data = &per_cpu(dm_hw_cpu_data, cpu);
		काष्ठा sk_buff *skb;

		del_समयr_sync(&hw_data->send_समयr);
		cancel_work_sync(&hw_data->dm_alert_work);
		जबतक ((skb = __skb_dequeue(&hw_data->drop_queue))) अणु
			काष्ठा devlink_trap_metadata *hw_metadata;

			hw_metadata = NET_DM_SKB_CB(skb)->hw_metadata;
			net_dm_hw_metadata_मुक्त(hw_metadata);
			consume_skb(skb);
		पूर्ण
	पूर्ण
	module_put(THIS_MODULE);
	वापस rc;
पूर्ण

अटल व्योम net_dm_hw_monitor_stop(काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा net_dm_alert_ops *ops;
	पूर्णांक cpu;

	अगर (!monitor_hw) अणु
		NL_SET_ERR_MSG_MOD(extack, "Hardware monitoring already disabled");
		वापस;
	पूर्ण

	ops = net_dm_alert_ops_arr[net_dm_alert_mode];

	monitor_hw = false;

	net_dm_hw_probe_unरेजिस्टर(ops);

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा per_cpu_dm_data *hw_data = &per_cpu(dm_hw_cpu_data, cpu);
		काष्ठा sk_buff *skb;

		del_समयr_sync(&hw_data->send_समयr);
		cancel_work_sync(&hw_data->dm_alert_work);
		जबतक ((skb = __skb_dequeue(&hw_data->drop_queue))) अणु
			काष्ठा devlink_trap_metadata *hw_metadata;

			hw_metadata = NET_DM_SKB_CB(skb)->hw_metadata;
			net_dm_hw_metadata_मुक्त(hw_metadata);
			consume_skb(skb);
		पूर्ण
	पूर्ण

	module_put(THIS_MODULE);
पूर्ण

अटल पूर्णांक net_dm_trace_on_set(काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा net_dm_alert_ops *ops;
	पूर्णांक cpu, rc;

	ops = net_dm_alert_ops_arr[net_dm_alert_mode];

	अगर (!try_module_get(THIS_MODULE)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to take reference on module");
		वापस -ENODEV;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा per_cpu_dm_data *data = &per_cpu(dm_cpu_data, cpu);
		काष्ठा sk_buff *skb;

		INIT_WORK(&data->dm_alert_work, ops->work_item_func);
		समयr_setup(&data->send_समयr, sched_send_work, 0);
		/* Allocate a new per-CPU skb क्रम the summary alert message and
		 * मुक्त the old one which might contain stale data from
		 * previous tracing.
		 */
		skb = reset_per_cpu_data(data);
		consume_skb(skb);
	पूर्ण

	rc = रेजिस्टर_trace_kमुक्त_skb(ops->kमुक्त_skb_probe, शून्य);
	अगर (rc) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to connect probe to kfree_skb() tracepoint");
		जाओ err_module_put;
	पूर्ण

	rc = रेजिस्टर_trace_napi_poll(ops->napi_poll_probe, शून्य);
	अगर (rc) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to connect probe to napi_poll() tracepoint");
		जाओ err_unरेजिस्टर_trace;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_trace:
	unरेजिस्टर_trace_kमुक्त_skb(ops->kमुक्त_skb_probe, शून्य);
err_module_put:
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा per_cpu_dm_data *data = &per_cpu(dm_cpu_data, cpu);
		काष्ठा sk_buff *skb;

		del_समयr_sync(&data->send_समयr);
		cancel_work_sync(&data->dm_alert_work);
		जबतक ((skb = __skb_dequeue(&data->drop_queue)))
			consume_skb(skb);
	पूर्ण
	module_put(THIS_MODULE);
	वापस rc;
पूर्ण

अटल व्योम net_dm_trace_off_set(व्योम)
अणु
	काष्ठा dm_hw_stat_delta *new_stat, *temp;
	स्थिर काष्ठा net_dm_alert_ops *ops;
	पूर्णांक cpu;

	ops = net_dm_alert_ops_arr[net_dm_alert_mode];

	unरेजिस्टर_trace_napi_poll(ops->napi_poll_probe, शून्य);
	unरेजिस्टर_trace_kमुक्त_skb(ops->kमुक्त_skb_probe, शून्य);

	tracepoपूर्णांक_synchronize_unरेजिस्टर();

	/* Make sure we करो not send notअगरications to user space after request
	 * to stop tracing वापसs.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा per_cpu_dm_data *data = &per_cpu(dm_cpu_data, cpu);
		काष्ठा sk_buff *skb;

		del_समयr_sync(&data->send_समयr);
		cancel_work_sync(&data->dm_alert_work);
		जबतक ((skb = __skb_dequeue(&data->drop_queue)))
			consume_skb(skb);
	पूर्ण

	list_क्रम_each_entry_safe(new_stat, temp, &hw_stats_list, list) अणु
		अगर (new_stat->dev == शून्य) अणु
			list_del_rcu(&new_stat->list);
			kमुक्त_rcu(new_stat, rcu);
		पूर्ण
	पूर्ण

	module_put(THIS_MODULE);
पूर्ण

अटल पूर्णांक set_all_monitor_traces(पूर्णांक state, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक rc = 0;

	अगर (state == trace_state) अणु
		NL_SET_ERR_MSG_MOD(extack, "Trace state already set to requested state");
		वापस -EAGAIN;
	पूर्ण

	चयन (state) अणु
	हाल TRACE_ON:
		rc = net_dm_trace_on_set(extack);
		अवरोध;
	हाल TRACE_OFF:
		net_dm_trace_off_set();
		अवरोध;
	शेष:
		rc = 1;
		अवरोध;
	पूर्ण

	अगर (!rc)
		trace_state = state;
	अन्यथा
		rc = -EINPROGRESS;

	वापस rc;
पूर्ण

अटल bool net_dm_is_monitoring(व्योम)
अणु
	वापस trace_state == TRACE_ON || monitor_hw;
पूर्ण

अटल पूर्णांक net_dm_alert_mode_get_from_info(काष्ठा genl_info *info,
					   क्रमागत net_dm_alert_mode *p_alert_mode)
अणु
	u8 val;

	val = nla_get_u8(info->attrs[NET_DM_ATTR_ALERT_MODE]);

	चयन (val) अणु
	हाल NET_DM_ALERT_MODE_SUMMARY:
	हाल NET_DM_ALERT_MODE_PACKET:
		*p_alert_mode = val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक net_dm_alert_mode_set(काष्ठा genl_info *info)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	क्रमागत net_dm_alert_mode alert_mode;
	पूर्णांक rc;

	अगर (!info->attrs[NET_DM_ATTR_ALERT_MODE])
		वापस 0;

	rc = net_dm_alert_mode_get_from_info(info, &alert_mode);
	अगर (rc) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid alert mode");
		वापस -EINVAL;
	पूर्ण

	net_dm_alert_mode = alert_mode;

	वापस 0;
पूर्ण

अटल व्योम net_dm_trunc_len_set(काष्ठा genl_info *info)
अणु
	अगर (!info->attrs[NET_DM_ATTR_TRUNC_LEN])
		वापस;

	net_dm_trunc_len = nla_get_u32(info->attrs[NET_DM_ATTR_TRUNC_LEN]);
पूर्ण

अटल व्योम net_dm_queue_len_set(काष्ठा genl_info *info)
अणु
	अगर (!info->attrs[NET_DM_ATTR_QUEUE_LEN])
		वापस;

	net_dm_queue_len = nla_get_u32(info->attrs[NET_DM_ATTR_QUEUE_LEN]);
पूर्ण

अटल पूर्णांक net_dm_cmd_config(काष्ठा sk_buff *skb,
			काष्ठा genl_info *info)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	पूर्णांक rc;

	अगर (net_dm_is_monitoring()) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot configure drop monitor during monitoring");
		वापस -EBUSY;
	पूर्ण

	rc = net_dm_alert_mode_set(info);
	अगर (rc)
		वापस rc;

	net_dm_trunc_len_set(info);

	net_dm_queue_len_set(info);

	वापस 0;
पूर्ण

अटल पूर्णांक net_dm_monitor_start(bool set_sw, bool set_hw,
				काष्ठा netlink_ext_ack *extack)
अणु
	bool sw_set = false;
	पूर्णांक rc;

	अगर (set_sw) अणु
		rc = set_all_monitor_traces(TRACE_ON, extack);
		अगर (rc)
			वापस rc;
		sw_set = true;
	पूर्ण

	अगर (set_hw) अणु
		rc = net_dm_hw_monitor_start(extack);
		अगर (rc)
			जाओ err_monitor_hw;
	पूर्ण

	वापस 0;

err_monitor_hw:
	अगर (sw_set)
		set_all_monitor_traces(TRACE_OFF, extack);
	वापस rc;
पूर्ण

अटल व्योम net_dm_monitor_stop(bool set_sw, bool set_hw,
				काष्ठा netlink_ext_ack *extack)
अणु
	अगर (set_hw)
		net_dm_hw_monitor_stop(extack);
	अगर (set_sw)
		set_all_monitor_traces(TRACE_OFF, extack);
पूर्ण

अटल पूर्णांक net_dm_cmd_trace(काष्ठा sk_buff *skb,
			काष्ठा genl_info *info)
अणु
	bool set_sw = !!info->attrs[NET_DM_ATTR_SW_DROPS];
	bool set_hw = !!info->attrs[NET_DM_ATTR_HW_DROPS];
	काष्ठा netlink_ext_ack *extack = info->extack;

	/* To मुख्यtain backward compatibility, we start / stop monitoring of
	 * software drops अगर no flag is specअगरied.
	 */
	अगर (!set_sw && !set_hw)
		set_sw = true;

	चयन (info->genlhdr->cmd) अणु
	हाल NET_DM_CMD_START:
		वापस net_dm_monitor_start(set_sw, set_hw, extack);
	हाल NET_DM_CMD_STOP:
		net_dm_monitor_stop(set_sw, set_hw, extack);
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक net_dm_config_fill(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			  &net_drop_monitor_family, 0, NET_DM_CMD_CONFIG_NEW);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (nla_put_u8(msg, NET_DM_ATTR_ALERT_MODE, net_dm_alert_mode))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NET_DM_ATTR_TRUNC_LEN, net_dm_trunc_len))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NET_DM_ATTR_QUEUE_LEN, net_dm_queue_len))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक net_dm_cmd_config_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक rc;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	rc = net_dm_config_fill(msg, info);
	अगर (rc)
		जाओ मुक्त_msg;

	वापस genlmsg_reply(msg, info);

मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस rc;
पूर्ण

अटल व्योम net_dm_stats_पढ़ो(काष्ठा net_dm_stats *stats)
अणु
	पूर्णांक cpu;

	स_रखो(stats, 0, माप(*stats));
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा per_cpu_dm_data *data = &per_cpu(dm_cpu_data, cpu);
		काष्ठा net_dm_stats *cpu_stats = &data->stats;
		अचिन्हित पूर्णांक start;
		u64 dropped;

		करो अणु
			start = u64_stats_fetch_begin_irq(&cpu_stats->syncp);
			dropped = cpu_stats->dropped;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&cpu_stats->syncp, start));

		stats->dropped += dropped;
	पूर्ण
पूर्ण

अटल पूर्णांक net_dm_stats_put(काष्ठा sk_buff *msg)
अणु
	काष्ठा net_dm_stats stats;
	काष्ठा nlattr *attr;

	net_dm_stats_पढ़ो(&stats);

	attr = nla_nest_start(msg, NET_DM_ATTR_STATS);
	अगर (!attr)
		वापस -EMSGSIZE;

	अगर (nla_put_u64_64bit(msg, NET_DM_ATTR_STATS_DROPPED,
			      stats.dropped, NET_DM_ATTR_PAD))
		जाओ nla_put_failure;

	nla_nest_end(msg, attr);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, attr);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम net_dm_hw_stats_पढ़ो(काष्ठा net_dm_stats *stats)
अणु
	पूर्णांक cpu;

	स_रखो(stats, 0, माप(*stats));
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा per_cpu_dm_data *hw_data = &per_cpu(dm_hw_cpu_data, cpu);
		काष्ठा net_dm_stats *cpu_stats = &hw_data->stats;
		अचिन्हित पूर्णांक start;
		u64 dropped;

		करो अणु
			start = u64_stats_fetch_begin_irq(&cpu_stats->syncp);
			dropped = cpu_stats->dropped;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&cpu_stats->syncp, start));

		stats->dropped += dropped;
	पूर्ण
पूर्ण

अटल पूर्णांक net_dm_hw_stats_put(काष्ठा sk_buff *msg)
अणु
	काष्ठा net_dm_stats stats;
	काष्ठा nlattr *attr;

	net_dm_hw_stats_पढ़ो(&stats);

	attr = nla_nest_start(msg, NET_DM_ATTR_HW_STATS);
	अगर (!attr)
		वापस -EMSGSIZE;

	अगर (nla_put_u64_64bit(msg, NET_DM_ATTR_STATS_DROPPED,
			      stats.dropped, NET_DM_ATTR_PAD))
		जाओ nla_put_failure;

	nla_nest_end(msg, attr);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक net_dm_stats_fill(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	व्योम *hdr;
	पूर्णांक rc;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			  &net_drop_monitor_family, 0, NET_DM_CMD_STATS_NEW);
	अगर (!hdr)
		वापस -EMSGSIZE;

	rc = net_dm_stats_put(msg);
	अगर (rc)
		जाओ nla_put_failure;

	rc = net_dm_hw_stats_put(msg);
	अगर (rc)
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक net_dm_cmd_stats_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक rc;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	rc = net_dm_stats_fill(msg, info);
	अगर (rc)
		जाओ मुक्त_msg;

	वापस genlmsg_reply(msg, info);

मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस rc;
पूर्ण

अटल पूर्णांक dropmon_net_event(काष्ठा notअगरier_block *ev_block,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा dm_hw_stat_delta *new_stat = शून्य;
	काष्ठा dm_hw_stat_delta *पंचांगp;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		new_stat = kzalloc(माप(काष्ठा dm_hw_stat_delta), GFP_KERNEL);

		अगर (!new_stat)
			जाओ out;

		new_stat->dev = dev;
		new_stat->last_rx = jअगरfies;
		mutex_lock(&net_dm_mutex);
		list_add_rcu(&new_stat->list, &hw_stats_list);
		mutex_unlock(&net_dm_mutex);
		अवरोध;
	हाल NETDEV_UNREGISTER:
		mutex_lock(&net_dm_mutex);
		list_क्रम_each_entry_safe(new_stat, पंचांगp, &hw_stats_list, list) अणु
			अगर (new_stat->dev == dev) अणु
				new_stat->dev = शून्य;
				अगर (trace_state == TRACE_OFF) अणु
					list_del_rcu(&new_stat->list);
					kमुक्त_rcu(new_stat, rcu);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		mutex_unlock(&net_dm_mutex);
		अवरोध;
	पूर्ण
out:
	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा nla_policy net_dm_nl_policy[NET_DM_ATTR_MAX + 1] = अणु
	[NET_DM_ATTR_UNSPEC] = अणु .strict_start_type = NET_DM_ATTR_UNSPEC + 1 पूर्ण,
	[NET_DM_ATTR_ALERT_MODE] = अणु .type = NLA_U8 पूर्ण,
	[NET_DM_ATTR_TRUNC_LEN] = अणु .type = NLA_U32 पूर्ण,
	[NET_DM_ATTR_QUEUE_LEN] = अणु .type = NLA_U32 पूर्ण,
	[NET_DM_ATTR_SW_DROPS]	= अणु. type = NLA_FLAG पूर्ण,
	[NET_DM_ATTR_HW_DROPS]	= अणु. type = NLA_FLAG पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_small_ops dropmon_ops[] = अणु
	अणु
		.cmd = NET_DM_CMD_CONFIG,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = net_dm_cmd_config,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = NET_DM_CMD_START,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = net_dm_cmd_trace,
	पूर्ण,
	अणु
		.cmd = NET_DM_CMD_STOP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = net_dm_cmd_trace,
	पूर्ण,
	अणु
		.cmd = NET_DM_CMD_CONFIG_GET,
		.करोit = net_dm_cmd_config_get,
	पूर्ण,
	अणु
		.cmd = NET_DM_CMD_STATS_GET,
		.करोit = net_dm_cmd_stats_get,
	पूर्ण,
पूर्ण;

अटल पूर्णांक net_dm_nl_pre_करोit(स्थिर काष्ठा genl_ops *ops,
			      काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	mutex_lock(&net_dm_mutex);

	वापस 0;
पूर्ण

अटल व्योम net_dm_nl_post_करोit(स्थिर काष्ठा genl_ops *ops,
				काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	mutex_unlock(&net_dm_mutex);
पूर्ण

अटल काष्ठा genl_family net_drop_monitor_family __ro_after_init = अणु
	.hdrsize        = 0,
	.name           = "NET_DM",
	.version        = 2,
	.maxattr	= NET_DM_ATTR_MAX,
	.policy		= net_dm_nl_policy,
	.pre_करोit	= net_dm_nl_pre_करोit,
	.post_करोit	= net_dm_nl_post_करोit,
	.module		= THIS_MODULE,
	.small_ops	= dropmon_ops,
	.n_small_ops	= ARRAY_SIZE(dropmon_ops),
	.mcgrps		= dropmon_mcgrps,
	.n_mcgrps	= ARRAY_SIZE(dropmon_mcgrps),
पूर्ण;

अटल काष्ठा notअगरier_block dropmon_net_notअगरier = अणु
	.notअगरier_call = dropmon_net_event
पूर्ण;

अटल व्योम __net_dm_cpu_data_init(काष्ठा per_cpu_dm_data *data)
अणु
	spin_lock_init(&data->lock);
	skb_queue_head_init(&data->drop_queue);
	u64_stats_init(&data->stats.syncp);
पूर्ण

अटल व्योम __net_dm_cpu_data_fini(काष्ठा per_cpu_dm_data *data)
अणु
	WARN_ON(!skb_queue_empty(&data->drop_queue));
पूर्ण

अटल व्योम net_dm_cpu_data_init(पूर्णांक cpu)
अणु
	काष्ठा per_cpu_dm_data *data;

	data = &per_cpu(dm_cpu_data, cpu);
	__net_dm_cpu_data_init(data);
पूर्ण

अटल व्योम net_dm_cpu_data_fini(पूर्णांक cpu)
अणु
	काष्ठा per_cpu_dm_data *data;

	data = &per_cpu(dm_cpu_data, cpu);
	/* At this poपूर्णांक, we should have exclusive access
	 * to this काष्ठा and can मुक्त the skb inside it.
	 */
	consume_skb(data->skb);
	__net_dm_cpu_data_fini(data);
पूर्ण

अटल व्योम net_dm_hw_cpu_data_init(पूर्णांक cpu)
अणु
	काष्ठा per_cpu_dm_data *hw_data;

	hw_data = &per_cpu(dm_hw_cpu_data, cpu);
	__net_dm_cpu_data_init(hw_data);
पूर्ण

अटल व्योम net_dm_hw_cpu_data_fini(पूर्णांक cpu)
अणु
	काष्ठा per_cpu_dm_data *hw_data;

	hw_data = &per_cpu(dm_hw_cpu_data, cpu);
	kमुक्त(hw_data->hw_entries);
	__net_dm_cpu_data_fini(hw_data);
पूर्ण

अटल पूर्णांक __init init_net_drop_monitor(व्योम)
अणु
	पूर्णांक cpu, rc;

	pr_info("Initializing network drop monitor service\n");

	अगर (माप(व्योम *) > 8) अणु
		pr_err("Unable to store program counters on this arch, Drop monitor failed\n");
		वापस -ENOSPC;
	पूर्ण

	rc = genl_रेजिस्टर_family(&net_drop_monitor_family);
	अगर (rc) अणु
		pr_err("Could not create drop monitor netlink family\n");
		वापस rc;
	पूर्ण
	WARN_ON(net_drop_monitor_family.mcgrp_offset != NET_DM_GRP_ALERT);

	rc = रेजिस्टर_netdevice_notअगरier(&dropmon_net_notअगरier);
	अगर (rc < 0) अणु
		pr_crit("Failed to register netdevice notifier\n");
		जाओ out_unreg;
	पूर्ण

	rc = 0;

	क्रम_each_possible_cpu(cpu) अणु
		net_dm_cpu_data_init(cpu);
		net_dm_hw_cpu_data_init(cpu);
	पूर्ण

	जाओ out;

out_unreg:
	genl_unरेजिस्टर_family(&net_drop_monitor_family);
out:
	वापस rc;
पूर्ण

अटल व्योम निकास_net_drop_monitor(व्योम)
अणु
	पूर्णांक cpu;

	BUG_ON(unरेजिस्टर_netdevice_notअगरier(&dropmon_net_notअगरier));

	/*
	 * Because of the module_get/put we करो in the trace state change path
	 * we are guaranteed not to have any current users when we get here
	 */

	क्रम_each_possible_cpu(cpu) अणु
		net_dm_hw_cpu_data_fini(cpu);
		net_dm_cpu_data_fini(cpu);
	पूर्ण

	BUG_ON(genl_unरेजिस्टर_family(&net_drop_monitor_family));
पूर्ण

module_init(init_net_drop_monitor);
module_निकास(निकास_net_drop_monitor);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Neil Horman <nhorman@tuxdriver.com>");
MODULE_ALIAS_GENL_FAMILY("NET_DM");
MODULE_DESCRIPTION("Monitoring code for network dropped packet alerts");
