<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/proc_fs.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/export.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/bonding.h>

#समावेश "bonding_priv.h"

अटल व्योम *bond_info_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा bonding *bond = PDE_DATA(file_inode(seq->file));
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	loff_t off = 0;

	rcu_पढ़ो_lock();

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	bond_क्रम_each_slave_rcu(bond, slave, iter)
		अगर (++off == *pos)
			वापस slave;

	वापस शून्य;
पूर्ण

अटल व्योम *bond_info_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा bonding *bond = PDE_DATA(file_inode(seq->file));
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	bool found = false;

	++*pos;
	अगर (v == SEQ_START_TOKEN)
		वापस bond_first_slave_rcu(bond);

	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (found)
			वापस slave;
		अगर (slave == v)
			found = true;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम bond_info_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम bond_info_show_master(काष्ठा seq_file *seq)
अणु
	काष्ठा bonding *bond = PDE_DATA(file_inode(seq->file));
	स्थिर काष्ठा bond_opt_value *optval;
	काष्ठा slave *curr, *primary;
	पूर्णांक i;

	curr = rcu_dereference(bond->curr_active_slave);

	seq_म_लिखो(seq, "Bonding Mode: %s",
		   bond_mode_name(BOND_MODE(bond)));

	अगर (BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP &&
	    bond->params.fail_over_mac) अणु
		optval = bond_opt_get_val(BOND_OPT_FAIL_OVER_MAC,
					  bond->params.fail_over_mac);
		seq_म_लिखो(seq, " (fail_over_mac %s)", optval->string);
	पूर्ण

	seq_म_लिखो(seq, "\n");

	अगर (bond_mode_uses_xmit_hash(bond)) अणु
		optval = bond_opt_get_val(BOND_OPT_XMIT_HASH,
					  bond->params.xmit_policy);
		seq_म_लिखो(seq, "Transmit Hash Policy: %s (%d)\n",
			   optval->string, bond->params.xmit_policy);
	पूर्ण

	अगर (bond_uses_primary(bond)) अणु
		primary = rcu_dereference(bond->primary_slave);
		seq_म_लिखो(seq, "Primary Slave: %s",
			   primary ? primary->dev->name : "None");
		अगर (primary) अणु
			optval = bond_opt_get_val(BOND_OPT_PRIMARY_RESELECT,
						  bond->params.primary_reselect);
			seq_म_लिखो(seq, " (primary_reselect %s)",
				   optval->string);
		पूर्ण

		seq_म_लिखो(seq, "\nCurrently Active Slave: %s\n",
			   (curr) ? curr->dev->name : "None");
	पूर्ण

	seq_म_लिखो(seq, "MII Status: %s\n", netअगर_carrier_ok(bond->dev) ?
		   "up" : "down");
	seq_म_लिखो(seq, "MII Polling Interval (ms): %d\n", bond->params.miimon);
	seq_म_लिखो(seq, "Up Delay (ms): %d\n",
		   bond->params.updelay * bond->params.miimon);
	seq_म_लिखो(seq, "Down Delay (ms): %d\n",
		   bond->params.करोwndelay * bond->params.miimon);
	seq_म_लिखो(seq, "Peer Notification Delay (ms): %d\n",
		   bond->params.peer_notअगर_delay * bond->params.miimon);


	/* ARP inक्रमmation */
	अगर (bond->params.arp_पूर्णांकerval > 0) अणु
		पूर्णांक prपूर्णांकed = 0;
		seq_म_लिखो(seq, "ARP Polling Interval (ms): %d\n",
				bond->params.arp_पूर्णांकerval);

		seq_म_लिखो(seq, "ARP IP target/s (n.n.n.n form):");

		क्रम (i = 0; (i < BOND_MAX_ARP_TARGETS); i++) अणु
			अगर (!bond->params.arp_tarमाला_लो[i])
				अवरोध;
			अगर (prपूर्णांकed)
				seq_म_लिखो(seq, ",");
			seq_म_लिखो(seq, " %pI4", &bond->params.arp_tarमाला_लो[i]);
			prपूर्णांकed = 1;
		पूर्ण
		seq_म_लिखो(seq, "\n");
	पूर्ण

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
		काष्ठा ad_info ad_info;

		seq_माला_दो(seq, "\n802.3ad info\n");
		seq_म_लिखो(seq, "LACP rate: %s\n",
			   (bond->params.lacp_fast) ? "fast" : "slow");
		seq_म_लिखो(seq, "Min links: %d\n", bond->params.min_links);
		optval = bond_opt_get_val(BOND_OPT_AD_SELECT,
					  bond->params.ad_select);
		seq_म_लिखो(seq, "Aggregator selection policy (ad_select): %s\n",
			   optval->string);
		अगर (capable(CAP_NET_ADMIN)) अणु
			seq_म_लिखो(seq, "System priority: %d\n",
				   BOND_AD_INFO(bond).प्रणाली.sys_priority);
			seq_म_लिखो(seq, "System MAC address: %pM\n",
				   &BOND_AD_INFO(bond).प्रणाली.sys_mac_addr);

			अगर (__bond_3ad_get_active_agg_info(bond, &ad_info)) अणु
				seq_म_लिखो(seq,
					   "bond %s has no active aggregator\n",
					   bond->dev->name);
			पूर्ण अन्यथा अणु
				seq_म_लिखो(seq, "Active Aggregator Info:\n");

				seq_म_लिखो(seq, "\tAggregator ID: %d\n",
					   ad_info.aggregator_id);
				seq_म_लिखो(seq, "\tNumber of ports: %d\n",
					   ad_info.ports);
				seq_म_लिखो(seq, "\tActor Key: %d\n",
					   ad_info.actor_key);
				seq_म_लिखो(seq, "\tPartner Key: %d\n",
					   ad_info.partner_key);
				seq_म_लिखो(seq, "\tPartner Mac Address: %pM\n",
					   ad_info.partner_प्रणाली);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bond_info_show_slave(काष्ठा seq_file *seq,
				 स्थिर काष्ठा slave *slave)
अणु
	काष्ठा bonding *bond = PDE_DATA(file_inode(seq->file));

	seq_म_लिखो(seq, "\nSlave Interface: %s\n", slave->dev->name);
	seq_म_लिखो(seq, "MII Status: %s\n", bond_slave_link_status(slave->link));
	अगर (slave->speed == SPEED_UNKNOWN)
		seq_म_लिखो(seq, "Speed: %s\n", "Unknown");
	अन्यथा
		seq_म_लिखो(seq, "Speed: %d Mbps\n", slave->speed);

	अगर (slave->duplex == DUPLEX_UNKNOWN)
		seq_म_लिखो(seq, "Duplex: %s\n", "Unknown");
	अन्यथा
		seq_म_लिखो(seq, "Duplex: %s\n", slave->duplex ? "full" : "half");

	seq_म_लिखो(seq, "Link Failure Count: %u\n",
		   slave->link_failure_count);

	seq_म_लिखो(seq, "Permanent HW addr: %*phC\n",
		   slave->dev->addr_len, slave->perm_hwaddr);
	seq_म_लिखो(seq, "Slave queue ID: %d\n", slave->queue_id);

	अगर (BOND_MODE(bond) == BOND_MODE_8023AD) अणु
		स्थिर काष्ठा port *port = &SLAVE_AD_INFO(slave)->port;
		स्थिर काष्ठा aggregator *agg = port->aggregator;

		अगर (agg) अणु
			seq_म_लिखो(seq, "Aggregator ID: %d\n",
				   agg->aggregator_identअगरier);
			seq_म_लिखो(seq, "Actor Churn State: %s\n",
				   bond_3ad_churn_desc(port->sm_churn_actor_state));
			seq_म_लिखो(seq, "Partner Churn State: %s\n",
				   bond_3ad_churn_desc(port->sm_churn_partner_state));
			seq_म_लिखो(seq, "Actor Churned Count: %d\n",
				   port->churn_actor_count);
			seq_म_लिखो(seq, "Partner Churned Count: %d\n",
				   port->churn_partner_count);

			अगर (capable(CAP_NET_ADMIN)) अणु
				seq_माला_दो(seq, "details actor lacp pdu:\n");
				seq_म_लिखो(seq, "    system priority: %d\n",
					   port->actor_प्रणाली_priority);
				seq_म_लिखो(seq, "    system mac address: %pM\n",
					   &port->actor_प्रणाली);
				seq_म_लिखो(seq, "    port key: %d\n",
					   port->actor_oper_port_key);
				seq_म_लिखो(seq, "    port priority: %d\n",
					   port->actor_port_priority);
				seq_म_लिखो(seq, "    port number: %d\n",
					   port->actor_port_number);
				seq_म_लिखो(seq, "    port state: %d\n",
					   port->actor_oper_port_state);

				seq_माला_दो(seq, "details partner lacp pdu:\n");
				seq_म_लिखो(seq, "    system priority: %d\n",
					   port->partner_oper.प्रणाली_priority);
				seq_म_लिखो(seq, "    system mac address: %pM\n",
					   &port->partner_oper.प्रणाली);
				seq_म_लिखो(seq, "    oper key: %d\n",
					   port->partner_oper.key);
				seq_म_लिखो(seq, "    port priority: %d\n",
					   port->partner_oper.port_priority);
				seq_म_लिखो(seq, "    port number: %d\n",
					   port->partner_oper.port_number);
				seq_म_लिखो(seq, "    port state: %d\n",
					   port->partner_oper.port_state);
			पूर्ण
		पूर्ण अन्यथा अणु
			seq_माला_दो(seq, "Aggregator ID: N/A\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bond_info_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq, "%s\n", bond_version);
		bond_info_show_master(seq);
	पूर्ण अन्यथा
		bond_info_show_slave(seq, v);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations bond_info_seq_ops = अणु
	.start = bond_info_seq_start,
	.next  = bond_info_seq_next,
	.stop  = bond_info_seq_stop,
	.show  = bond_info_seq_show,
पूर्ण;

व्योम bond_create_proc_entry(काष्ठा bonding *bond)
अणु
	काष्ठा net_device *bond_dev = bond->dev;
	काष्ठा bond_net *bn = net_generic(dev_net(bond_dev), bond_net_id);

	अगर (bn->proc_dir) अणु
		bond->proc_entry = proc_create_seq_data(bond_dev->name, 0444,
				bn->proc_dir, &bond_info_seq_ops, bond);
		अगर (bond->proc_entry == शून्य)
			netdev_warn(bond_dev, "Cannot create /proc/net/%s/%s\n",
				    DRV_NAME, bond_dev->name);
		अन्यथा
			स_नकल(bond->proc_file_name, bond_dev->name, IFNAMSIZ);
	पूर्ण
पूर्ण

व्योम bond_हटाओ_proc_entry(काष्ठा bonding *bond)
अणु
	काष्ठा net_device *bond_dev = bond->dev;
	काष्ठा bond_net *bn = net_generic(dev_net(bond_dev), bond_net_id);

	अगर (bn->proc_dir && bond->proc_entry) अणु
		हटाओ_proc_entry(bond->proc_file_name, bn->proc_dir);
		स_रखो(bond->proc_file_name, 0, IFNAMSIZ);
		bond->proc_entry = शून्य;
	पूर्ण
पूर्ण

/* Create the bonding directory under /proc/net, अगर करोesn't exist yet.
 * Caller must hold rtnl_lock.
 */
व्योम __net_init bond_create_proc_dir(काष्ठा bond_net *bn)
अणु
	अगर (!bn->proc_dir) अणु
		bn->proc_dir = proc_सूची_गढ़ो(DRV_NAME, bn->net->proc_net);
		अगर (!bn->proc_dir)
			pr_warn("Warning: Cannot create /proc/net/%s\n",
				DRV_NAME);
	पूर्ण
पूर्ण

/* Destroy the bonding directory under /proc/net, अगर empty.
 * Caller must hold rtnl_lock.
 */
व्योम __net_निकास bond_destroy_proc_dir(काष्ठा bond_net *bn)
अणु
	अगर (bn->proc_dir) अणु
		हटाओ_proc_entry(DRV_NAME, bn->net->proc_net);
		bn->proc_dir = शून्य;
	पूर्ण
पूर्ण
