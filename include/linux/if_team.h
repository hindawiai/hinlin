<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/अगर_team.h - Network team device driver header
 * Copyright (c) 2011 Jiri Pirko <jpirko@redhat.com>
 */
#अगर_अघोषित _LINUX_IF_TEAM_H_
#घोषणा _LINUX_IF_TEAM_H_

#समावेश <linux/netpoll.h>
#समावेश <net/sch_generic.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/अगर_team.h>

काष्ठा team_pcpu_stats अणु
	u64			rx_packets;
	u64			rx_bytes;
	u64			rx_multicast;
	u64			tx_packets;
	u64			tx_bytes;
	काष्ठा u64_stats_sync	syncp;
	u32			rx_dropped;
	u32			tx_dropped;
	u32			rx_nohandler;
पूर्ण;

काष्ठा team;

काष्ठा team_port अणु
	काष्ठा net_device *dev;
	काष्ठा hlist_node hlist; /* node in enabled ports hash list */
	काष्ठा list_head list; /* node in ordinary list */
	काष्ठा team *team;
	पूर्णांक index; /* index of enabled port. If disabled, it's set to -1 */

	bool linkup; /* either state.linkup or user.linkup */

	काष्ठा अणु
		bool linkup;
		u32 speed;
		u8 duplex;
	पूर्ण state;

	/* Values set by userspace */
	काष्ठा अणु
		bool linkup;
		bool linkup_enabled;
	पूर्ण user;

	/* Custom gennetlink पूर्णांकerface related flags */
	bool changed;
	bool हटाओd;

	/*
	 * A place क्रम storing original values of the device beक्रमe it
	 * become a port.
	 */
	काष्ठा अणु
		अचिन्हित अक्षर dev_addr[MAX_ADDR_LEN];
		अचिन्हित पूर्णांक mtu;
	पूर्ण orig;

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	काष्ठा netpoll *np;
#पूर्ण_अगर

	s32 priority; /* lower number ~ higher priority */
	u16 queue_id;
	काष्ठा list_head qom_list; /* node in queue override mapping list */
	काष्ठा rcu_head	rcu;
	दीर्घ mode_priv[];
पूर्ण;

अटल अंतरभूत काष्ठा team_port *team_port_get_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_dereference(dev->rx_handler_data);
पूर्ण

अटल अंतरभूत bool team_port_enabled(काष्ठा team_port *port)
अणु
	वापस port->index != -1;
पूर्ण

अटल अंतरभूत bool team_port_txable(काष्ठा team_port *port)
अणु
	वापस port->linkup && team_port_enabled(port);
पूर्ण

अटल अंतरभूत bool team_port_dev_txable(स्थिर काष्ठा net_device *port_dev)
अणु
	काष्ठा team_port *port;
	bool txable;

	rcu_पढ़ो_lock();
	port = team_port_get_rcu(port_dev);
	txable = port ? team_port_txable(port) : false;
	rcu_पढ़ो_unlock();

	वापस txable;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल अंतरभूत व्योम team_netpoll_send_skb(काष्ठा team_port *port,
					 काष्ठा sk_buff *skb)
अणु
	netpoll_send_skb(port->np, skb);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम team_netpoll_send_skb(काष्ठा team_port *port,
					 काष्ठा sk_buff *skb)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा team_mode_ops अणु
	पूर्णांक (*init)(काष्ठा team *team);
	व्योम (*निकास)(काष्ठा team *team);
	rx_handler_result_t (*receive)(काष्ठा team *team,
				       काष्ठा team_port *port,
				       काष्ठा sk_buff *skb);
	bool (*transmit)(काष्ठा team *team, काष्ठा sk_buff *skb);
	पूर्णांक (*port_enter)(काष्ठा team *team, काष्ठा team_port *port);
	व्योम (*port_leave)(काष्ठा team *team, काष्ठा team_port *port);
	व्योम (*port_change_dev_addr)(काष्ठा team *team, काष्ठा team_port *port);
	व्योम (*port_enabled)(काष्ठा team *team, काष्ठा team_port *port);
	व्योम (*port_disabled)(काष्ठा team *team, काष्ठा team_port *port);
पूर्ण;

बाह्य पूर्णांक team_modeop_port_enter(काष्ठा team *team, काष्ठा team_port *port);
बाह्य व्योम team_modeop_port_change_dev_addr(काष्ठा team *team,
					     काष्ठा team_port *port);

क्रमागत team_option_type अणु
	TEAM_OPTION_TYPE_U32,
	TEAM_OPTION_TYPE_STRING,
	TEAM_OPTION_TYPE_BINARY,
	TEAM_OPTION_TYPE_BOOL,
	TEAM_OPTION_TYPE_S32,
पूर्ण;

काष्ठा team_option_inst_info अणु
	u32 array_index;
	काष्ठा team_port *port; /* != शून्य अगर per-port */
पूर्ण;

काष्ठा team_gsetter_ctx अणु
	जोड़ अणु
		u32 u32_val;
		स्थिर अक्षर *str_val;
		काष्ठा अणु
			स्थिर व्योम *ptr;
			u32 len;
		पूर्ण bin_val;
		bool bool_val;
		s32 s32_val;
	पूर्ण data;
	काष्ठा team_option_inst_info *info;
पूर्ण;

काष्ठा team_option अणु
	काष्ठा list_head list;
	स्थिर अक्षर *name;
	bool per_port;
	अचिन्हित पूर्णांक array_size; /* != 0 means the option is array */
	क्रमागत team_option_type type;
	पूर्णांक (*init)(काष्ठा team *team, काष्ठा team_option_inst_info *info);
	पूर्णांक (*getter)(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx);
	पूर्णांक (*setter)(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx);
पूर्ण;

बाह्य व्योम team_option_inst_set_change(काष्ठा team_option_inst_info *opt_inst_info);
बाह्य व्योम team_options_change_check(काष्ठा team *team);

काष्ठा team_mode अणु
	स्थिर अक्षर *kind;
	काष्ठा module *owner;
	माप_प्रकार priv_size;
	माप_प्रकार port_priv_size;
	स्थिर काष्ठा team_mode_ops *ops;
	क्रमागत netdev_lag_tx_type lag_tx_type;
पूर्ण;

#घोषणा TEAM_PORT_HASHBITS 4
#घोषणा TEAM_PORT_HASHENTRIES (1 << TEAM_PORT_HASHBITS)

#घोषणा TEAM_MODE_PRIV_LONGS 4
#घोषणा TEAM_MODE_PRIV_SIZE (माप(दीर्घ) * TEAM_MODE_PRIV_LONGS)

काष्ठा team अणु
	काष्ठा net_device *dev; /* associated netdevice */
	काष्ठा team_pcpu_stats __percpu *pcpu_stats;

	काष्ठा mutex lock; /* used क्रम overall locking, e.g. port lists ग_लिखो */

	/*
	 * List of enabled ports and their count
	 */
	पूर्णांक en_port_count;
	काष्ठा hlist_head en_port_hlist[TEAM_PORT_HASHENTRIES];

	काष्ठा list_head port_list; /* list of all ports */

	काष्ठा list_head option_list;
	काष्ठा list_head option_inst_list; /* list of option instances */

	स्थिर काष्ठा team_mode *mode;
	काष्ठा team_mode_ops ops;
	bool user_carrier_enabled;
	bool queue_override_enabled;
	काष्ठा list_head *qom_lists; /* array of queue override mapping lists */
	bool port_mtu_change_allowed;
	काष्ठा अणु
		अचिन्हित पूर्णांक count;
		अचिन्हित पूर्णांक पूर्णांकerval; /* in ms */
		atomic_t count_pending;
		काष्ठा delayed_work dw;
	पूर्ण notअगरy_peers;
	काष्ठा अणु
		अचिन्हित पूर्णांक count;
		अचिन्हित पूर्णांक पूर्णांकerval; /* in ms */
		atomic_t count_pending;
		काष्ठा delayed_work dw;
	पूर्ण mcast_rejoin;
	काष्ठा lock_class_key team_lock_key;
	दीर्घ mode_priv[TEAM_MODE_PRIV_LONGS];
पूर्ण;

अटल अंतरभूत पूर्णांक team_dev_queue_xmit(काष्ठा team *team, काष्ठा team_port *port,
				      काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(skb->queue_mapping) !=
		     माप(qdisc_skb_cb(skb)->slave_dev_queue_mapping));
	skb_set_queue_mapping(skb, qdisc_skb_cb(skb)->slave_dev_queue_mapping);

	skb->dev = port->dev;
	अगर (unlikely(netpoll_tx_running(team->dev))) अणु
		team_netpoll_send_skb(port, skb);
		वापस 0;
	पूर्ण
	वापस dev_queue_xmit(skb);
पूर्ण

अटल अंतरभूत काष्ठा hlist_head *team_port_index_hash(काष्ठा team *team,
						      पूर्णांक port_index)
अणु
	वापस &team->en_port_hlist[port_index & (TEAM_PORT_HASHENTRIES - 1)];
पूर्ण

अटल अंतरभूत काष्ठा team_port *team_get_port_by_index(काष्ठा team *team,
						       पूर्णांक port_index)
अणु
	काष्ठा team_port *port;
	काष्ठा hlist_head *head = team_port_index_hash(team, port_index);

	hlist_क्रम_each_entry(port, head, hlist)
		अगर (port->index == port_index)
			वापस port;
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक team_num_to_port_index(काष्ठा team *team, अचिन्हित पूर्णांक num)
अणु
	पूर्णांक en_port_count = READ_ONCE(team->en_port_count);

	अगर (unlikely(!en_port_count))
		वापस 0;
	वापस num % en_port_count;
पूर्ण

अटल अंतरभूत काष्ठा team_port *team_get_port_by_index_rcu(काष्ठा team *team,
							   पूर्णांक port_index)
अणु
	काष्ठा team_port *port;
	काष्ठा hlist_head *head = team_port_index_hash(team, port_index);

	hlist_क्रम_each_entry_rcu(port, head, hlist)
		अगर (port->index == port_index)
			वापस port;
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा team_port *
team_get_first_port_txable_rcu(काष्ठा team *team, काष्ठा team_port *port)
अणु
	काष्ठा team_port *cur;

	अगर (likely(team_port_txable(port)))
		वापस port;
	cur = port;
	list_क्रम_each_entry_जारी_rcu(cur, &team->port_list, list)
		अगर (team_port_txable(cur))
			वापस cur;
	list_क्रम_each_entry_rcu(cur, &team->port_list, list) अणु
		अगर (cur == port)
			अवरोध;
		अगर (team_port_txable(cur))
			वापस cur;
	पूर्ण
	वापस शून्य;
पूर्ण

बाह्य पूर्णांक team_options_रेजिस्टर(काष्ठा team *team,
				 स्थिर काष्ठा team_option *option,
				 माप_प्रकार option_count);
बाह्य व्योम team_options_unरेजिस्टर(काष्ठा team *team,
				    स्थिर काष्ठा team_option *option,
				    माप_प्रकार option_count);
बाह्य पूर्णांक team_mode_रेजिस्टर(स्थिर काष्ठा team_mode *mode);
बाह्य व्योम team_mode_unरेजिस्टर(स्थिर काष्ठा team_mode *mode);

#घोषणा TEAM_DEFAULT_NUM_TX_QUEUES 16
#घोषणा TEAM_DEFAULT_NUM_RX_QUEUES 16

#घोषणा MODULE_ALIAS_TEAM_MODE(kind) MODULE_ALIAS("team-mode-" kind)

#पूर्ण_अगर /* _LINUX_IF_TEAM_H_ */
