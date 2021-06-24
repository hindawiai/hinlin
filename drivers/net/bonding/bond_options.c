<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/bond/bond_options.c - bonding options
 * Copyright (c) 2013 Jiri Pirko <jiri@resnulli.us>
 * Copyright (c) 2013 Scott Feldman <sfeldma@cumulusnetworks.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/inet.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/bonding.h>

अटल पूर्णांक bond_option_active_slave_set(काष्ठा bonding *bond,
					स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_miimon_set(काष्ठा bonding *bond,
				  स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_updelay_set(काष्ठा bonding *bond,
				   स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_करोwndelay_set(काष्ठा bonding *bond,
				     स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_peer_notअगर_delay_set(काष्ठा bonding *bond,
					    स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_use_carrier_set(काष्ठा bonding *bond,
				       स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_arp_पूर्णांकerval_set(काष्ठा bonding *bond,
					स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_arp_ip_target_add(काष्ठा bonding *bond, __be32 target);
अटल पूर्णांक bond_option_arp_ip_target_rem(काष्ठा bonding *bond, __be32 target);
अटल पूर्णांक bond_option_arp_ip_tarमाला_लो_set(काष्ठा bonding *bond,
					  स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_arp_validate_set(काष्ठा bonding *bond,
					स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_arp_all_tarमाला_लो_set(काष्ठा bonding *bond,
					   स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_primary_set(काष्ठा bonding *bond,
				   स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_primary_reselect_set(काष्ठा bonding *bond,
					    स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_fail_over_mac_set(काष्ठा bonding *bond,
					 स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_xmit_hash_policy_set(काष्ठा bonding *bond,
					    स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_resend_igmp_set(काष्ठा bonding *bond,
				       स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_num_peer_notअगर_set(काष्ठा bonding *bond,
					  स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_all_slaves_active_set(काष्ठा bonding *bond,
					     स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_min_links_set(काष्ठा bonding *bond,
				     स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_lp_पूर्णांकerval_set(काष्ठा bonding *bond,
				       स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_pps_set(काष्ठा bonding *bond,
			       स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_lacp_rate_set(काष्ठा bonding *bond,
				     स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_ad_select_set(काष्ठा bonding *bond,
				     स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_queue_id_set(काष्ठा bonding *bond,
				    स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_mode_set(काष्ठा bonding *bond,
				स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_slaves_set(काष्ठा bonding *bond,
				  स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_tlb_dynamic_lb_set(काष्ठा bonding *bond,
				  स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_ad_actor_sys_prio_set(काष्ठा bonding *bond,
					     स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_ad_actor_प्रणाली_set(काष्ठा bonding *bond,
					   स्थिर काष्ठा bond_opt_value *newval);
अटल पूर्णांक bond_option_ad_user_port_key_set(काष्ठा bonding *bond,
					    स्थिर काष्ठा bond_opt_value *newval);


अटल स्थिर काष्ठा bond_opt_value bond_mode_tbl[] = अणु
	अणु "balance-rr",    BOND_MODE_ROUNDROBIN,   BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "active-backup", BOND_MODE_ACTIVEBACKUP, 0पूर्ण,
	अणु "balance-xor",   BOND_MODE_XOR,          0पूर्ण,
	अणु "broadcast",     BOND_MODE_BROADCAST,    0पूर्ण,
	अणु "802.3ad",       BOND_MODE_8023AD,       0पूर्ण,
	अणु "balance-tlb",   BOND_MODE_TLB,          0पूर्ण,
	अणु "balance-alb",   BOND_MODE_ALB,          0पूर्ण,
	अणु शून्य,            -1,                     0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_pps_tbl[] = अणु
	अणु "default", 1,         BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "maxval",  अच_लघु_उच्च, BOND_VALFLAG_MAXपूर्ण,
	अणु शून्य,      -1,        0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_xmit_hashtype_tbl[] = अणु
	अणु "layer2",      BOND_XMIT_POLICY_LAYER2,      BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "layer3+4",    BOND_XMIT_POLICY_LAYER34,     0पूर्ण,
	अणु "layer2+3",    BOND_XMIT_POLICY_LAYER23,     0पूर्ण,
	अणु "encap2+3",    BOND_XMIT_POLICY_ENCAP23,     0पूर्ण,
	अणु "encap3+4",    BOND_XMIT_POLICY_ENCAP34,     0पूर्ण,
	अणु "vlan+srcmac", BOND_XMIT_POLICY_VLAN_SRCMAC, 0पूर्ण,
	अणु शून्य,          -1,                           0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_arp_validate_tbl[] = अणु
	अणु "none",		BOND_ARP_VALIDATE_NONE,		BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "active",		BOND_ARP_VALIDATE_ACTIVE,	0पूर्ण,
	अणु "backup",		BOND_ARP_VALIDATE_BACKUP,	0पूर्ण,
	अणु "all",		BOND_ARP_VALIDATE_ALL,		0पूर्ण,
	अणु "filter",		BOND_ARP_FILTER,		0पूर्ण,
	अणु "filter_active",	BOND_ARP_FILTER_ACTIVE,		0पूर्ण,
	अणु "filter_backup",	BOND_ARP_FILTER_BACKUP,		0पूर्ण,
	अणु शून्य,			-1,				0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_arp_all_tarमाला_लो_tbl[] = अणु
	अणु "any", BOND_ARP_TARGETS_ANY, BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "all", BOND_ARP_TARGETS_ALL, 0पूर्ण,
	अणु शून्य,  -1,                   0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_fail_over_mac_tbl[] = अणु
	अणु "none",   BOND_FOM_NONE,   BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "active", BOND_FOM_ACTIVE, 0पूर्ण,
	अणु "follow", BOND_FOM_FOLLOW, 0पूर्ण,
	अणु शून्य,     -1,              0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_पूर्णांकmax_tbl[] = अणु
	अणु "off",     0,       BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "maxval",  पूर्णांक_उच्च, BOND_VALFLAG_MAXपूर्ण,
	अणु शून्य,      -1,      0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_lacp_rate_tbl[] = अणु
	अणु "slow", AD_LACP_SLOW, 0पूर्ण,
	अणु "fast", AD_LACP_FAST, 0पूर्ण,
	अणु शून्य,   -1,           0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_ad_select_tbl[] = अणु
	अणु "stable",    BOND_AD_STABLE,    BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "bandwidth", BOND_AD_BANDWIDTH, 0पूर्ण,
	अणु "count",     BOND_AD_COUNT,     0पूर्ण,
	अणु शून्य,        -1,                0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_num_peer_notअगर_tbl[] = अणु
	अणु "off",     0,   0पूर्ण,
	अणु "maxval",  255, BOND_VALFLAG_MAXपूर्ण,
	अणु "default", 1,   BOND_VALFLAG_DEFAULTपूर्ण,
	अणु शून्य,      -1,  0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_primary_reselect_tbl[] = अणु
	अणु "always",  BOND_PRI_RESELECT_ALWAYS,  BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "better",  BOND_PRI_RESELECT_BETTER,  0पूर्ण,
	अणु "failure", BOND_PRI_RESELECT_FAILURE, 0पूर्ण,
	अणु शून्य,      -1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_use_carrier_tbl[] = अणु
	अणु "off", 0,  0पूर्ण,
	अणु "on",  1,  BOND_VALFLAG_DEFAULTपूर्ण,
	अणु शून्य,  -1, 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_all_slaves_active_tbl[] = अणु
	अणु "off", 0,  BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "on",  1,  0पूर्ण,
	अणु शून्य,  -1, 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_resend_igmp_tbl[] = अणु
	अणु "off",     0,   0पूर्ण,
	अणु "maxval",  255, BOND_VALFLAG_MAXपूर्ण,
	अणु "default", 1,   BOND_VALFLAG_DEFAULTपूर्ण,
	अणु शून्य,      -1,  0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_lp_पूर्णांकerval_tbl[] = अणु
	अणु "minval",  1,       BOND_VALFLAG_MIN | BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "maxval",  पूर्णांक_उच्च, BOND_VALFLAG_MAXपूर्ण,
	अणु शून्य,      -1,      0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_tlb_dynamic_lb_tbl[] = अणु
	अणु "off", 0,  0पूर्ण,
	अणु "on",  1,  BOND_VALFLAG_DEFAULTपूर्ण,
	अणु शून्य,  -1, 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_ad_actor_sys_prio_tbl[] = अणु
	अणु "minval",  1,     BOND_VALFLAG_MINपूर्ण,
	अणु "maxval",  65535, BOND_VALFLAG_MAX | BOND_VALFLAG_DEFAULTपूर्ण,
	अणु शून्य,      -1,    0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_opt_value bond_ad_user_port_key_tbl[] = अणु
	अणु "minval",  0,     BOND_VALFLAG_MIN | BOND_VALFLAG_DEFAULTपूर्ण,
	अणु "maxval",  1023,  BOND_VALFLAG_MAXपूर्ण,
	अणु शून्य,      -1,    0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bond_option bond_opts[BOND_OPT_LAST] = अणु
	[BOND_OPT_MODE] = अणु
		.id = BOND_OPT_MODE,
		.name = "mode",
		.desc = "bond device mode",
		.flags = BOND_OPTFLAG_NOSLAVES | BOND_OPTFLAG_IFDOWN,
		.values = bond_mode_tbl,
		.set = bond_option_mode_set
	पूर्ण,
	[BOND_OPT_PACKETS_PER_SLAVE] = अणु
		.id = BOND_OPT_PACKETS_PER_SLAVE,
		.name = "packets_per_slave",
		.desc = "Packets to send per slave in RR mode",
		.unsuppmodes = BOND_MODE_ALL_EX(BIT(BOND_MODE_ROUNDROBIN)),
		.values = bond_pps_tbl,
		.set = bond_option_pps_set
	पूर्ण,
	[BOND_OPT_XMIT_HASH] = अणु
		.id = BOND_OPT_XMIT_HASH,
		.name = "xmit_hash_policy",
		.desc = "balance-xor, 802.3ad, and tlb hashing method",
		.values = bond_xmit_hashtype_tbl,
		.set = bond_option_xmit_hash_policy_set
	पूर्ण,
	[BOND_OPT_ARP_VALIDATE] = अणु
		.id = BOND_OPT_ARP_VALIDATE,
		.name = "arp_validate",
		.desc = "validate src/dst of ARP probes",
		.unsuppmodes = BIT(BOND_MODE_8023AD) | BIT(BOND_MODE_TLB) |
			       BIT(BOND_MODE_ALB),
		.values = bond_arp_validate_tbl,
		.set = bond_option_arp_validate_set
	पूर्ण,
	[BOND_OPT_ARP_ALL_TARGETS] = अणु
		.id = BOND_OPT_ARP_ALL_TARGETS,
		.name = "arp_all_targets",
		.desc = "fail on any/all arp targets timeout",
		.values = bond_arp_all_tarमाला_लो_tbl,
		.set = bond_option_arp_all_tarमाला_लो_set
	पूर्ण,
	[BOND_OPT_FAIL_OVER_MAC] = अणु
		.id = BOND_OPT_FAIL_OVER_MAC,
		.name = "fail_over_mac",
		.desc = "For active-backup, do not set all slaves to the same MAC",
		.flags = BOND_OPTFLAG_NOSLAVES,
		.values = bond_fail_over_mac_tbl,
		.set = bond_option_fail_over_mac_set
	पूर्ण,
	[BOND_OPT_ARP_INTERVAL] = अणु
		.id = BOND_OPT_ARP_INTERVAL,
		.name = "arp_interval",
		.desc = "arp interval in milliseconds",
		.unsuppmodes = BIT(BOND_MODE_8023AD) | BIT(BOND_MODE_TLB) |
			       BIT(BOND_MODE_ALB),
		.values = bond_पूर्णांकmax_tbl,
		.set = bond_option_arp_पूर्णांकerval_set
	पूर्ण,
	[BOND_OPT_ARP_TARGETS] = अणु
		.id = BOND_OPT_ARP_TARGETS,
		.name = "arp_ip_target",
		.desc = "arp targets in n.n.n.n form",
		.flags = BOND_OPTFLAG_RAWVAL,
		.set = bond_option_arp_ip_tarमाला_लो_set
	पूर्ण,
	[BOND_OPT_DOWNDELAY] = अणु
		.id = BOND_OPT_DOWNDELAY,
		.name = "downdelay",
		.desc = "Delay before considering link down, in milliseconds",
		.values = bond_पूर्णांकmax_tbl,
		.set = bond_option_करोwndelay_set
	पूर्ण,
	[BOND_OPT_UPDELAY] = अणु
		.id = BOND_OPT_UPDELAY,
		.name = "updelay",
		.desc = "Delay before considering link up, in milliseconds",
		.values = bond_पूर्णांकmax_tbl,
		.set = bond_option_updelay_set
	पूर्ण,
	[BOND_OPT_LACP_RATE] = अणु
		.id = BOND_OPT_LACP_RATE,
		.name = "lacp_rate",
		.desc = "LACPDU tx rate to request from 802.3ad partner",
		.flags = BOND_OPTFLAG_IFDOWN,
		.unsuppmodes = BOND_MODE_ALL_EX(BIT(BOND_MODE_8023AD)),
		.values = bond_lacp_rate_tbl,
		.set = bond_option_lacp_rate_set
	पूर्ण,
	[BOND_OPT_MINLINKS] = अणु
		.id = BOND_OPT_MINLINKS,
		.name = "min_links",
		.desc = "Minimum number of available links before turning on carrier",
		.values = bond_पूर्णांकmax_tbl,
		.set = bond_option_min_links_set
	पूर्ण,
	[BOND_OPT_AD_SELECT] = अणु
		.id = BOND_OPT_AD_SELECT,
		.name = "ad_select",
		.desc = "803.ad aggregation selection logic",
		.flags = BOND_OPTFLAG_IFDOWN,
		.values = bond_ad_select_tbl,
		.set = bond_option_ad_select_set
	पूर्ण,
	[BOND_OPT_NUM_PEER_NOTIF] = अणु
		.id = BOND_OPT_NUM_PEER_NOTIF,
		.name = "num_unsol_na",
		.desc = "Number of peer notifications to send on failover event",
		.values = bond_num_peer_notअगर_tbl,
		.set = bond_option_num_peer_notअगर_set
	पूर्ण,
	[BOND_OPT_MIIMON] = अणु
		.id = BOND_OPT_MIIMON,
		.name = "miimon",
		.desc = "Link check interval in milliseconds",
		.values = bond_पूर्णांकmax_tbl,
		.set = bond_option_miimon_set
	पूर्ण,
	[BOND_OPT_PRIMARY] = अणु
		.id = BOND_OPT_PRIMARY,
		.name = "primary",
		.desc = "Primary network device to use",
		.flags = BOND_OPTFLAG_RAWVAL,
		.unsuppmodes = BOND_MODE_ALL_EX(BIT(BOND_MODE_ACTIVEBACKUP) |
						BIT(BOND_MODE_TLB) |
						BIT(BOND_MODE_ALB)),
		.set = bond_option_primary_set
	पूर्ण,
	[BOND_OPT_PRIMARY_RESELECT] = अणु
		.id = BOND_OPT_PRIMARY_RESELECT,
		.name = "primary_reselect",
		.desc = "Reselect primary slave once it comes up",
		.values = bond_primary_reselect_tbl,
		.set = bond_option_primary_reselect_set
	पूर्ण,
	[BOND_OPT_USE_CARRIER] = अणु
		.id = BOND_OPT_USE_CARRIER,
		.name = "use_carrier",
		.desc = "Use netif_carrier_ok (vs MII ioctls) in miimon",
		.values = bond_use_carrier_tbl,
		.set = bond_option_use_carrier_set
	पूर्ण,
	[BOND_OPT_ACTIVE_SLAVE] = अणु
		.id = BOND_OPT_ACTIVE_SLAVE,
		.name = "active_slave",
		.desc = "Currently active slave",
		.flags = BOND_OPTFLAG_RAWVAL,
		.unsuppmodes = BOND_MODE_ALL_EX(BIT(BOND_MODE_ACTIVEBACKUP) |
						BIT(BOND_MODE_TLB) |
						BIT(BOND_MODE_ALB)),
		.set = bond_option_active_slave_set
	पूर्ण,
	[BOND_OPT_QUEUE_ID] = अणु
		.id = BOND_OPT_QUEUE_ID,
		.name = "queue_id",
		.desc = "Set queue id of a slave",
		.flags = BOND_OPTFLAG_RAWVAL,
		.set = bond_option_queue_id_set
	पूर्ण,
	[BOND_OPT_ALL_SLAVES_ACTIVE] = अणु
		.id = BOND_OPT_ALL_SLAVES_ACTIVE,
		.name = "all_slaves_active",
		.desc = "Keep all frames received on an interface by setting active flag for all slaves",
		.values = bond_all_slaves_active_tbl,
		.set = bond_option_all_slaves_active_set
	पूर्ण,
	[BOND_OPT_RESEND_IGMP] = अणु
		.id = BOND_OPT_RESEND_IGMP,
		.name = "resend_igmp",
		.desc = "Number of IGMP membership reports to send on link failure",
		.values = bond_resend_igmp_tbl,
		.set = bond_option_resend_igmp_set
	पूर्ण,
	[BOND_OPT_LP_INTERVAL] = अणु
		.id = BOND_OPT_LP_INTERVAL,
		.name = "lp_interval",
		.desc = "The number of seconds between instances where the bonding driver sends learning packets to each slave's peer switch",
		.values = bond_lp_पूर्णांकerval_tbl,
		.set = bond_option_lp_पूर्णांकerval_set
	पूर्ण,
	[BOND_OPT_SLAVES] = अणु
		.id = BOND_OPT_SLAVES,
		.name = "slaves",
		.desc = "Slave membership management",
		.flags = BOND_OPTFLAG_RAWVAL,
		.set = bond_option_slaves_set
	पूर्ण,
	[BOND_OPT_TLB_DYNAMIC_LB] = अणु
		.id = BOND_OPT_TLB_DYNAMIC_LB,
		.name = "tlb_dynamic_lb",
		.desc = "Enable dynamic flow shuffling",
		.unsuppmodes = BOND_MODE_ALL_EX(BIT(BOND_MODE_TLB) | BIT(BOND_MODE_ALB)),
		.values = bond_tlb_dynamic_lb_tbl,
		.flags = BOND_OPTFLAG_IFDOWN,
		.set = bond_option_tlb_dynamic_lb_set,
	पूर्ण,
	[BOND_OPT_AD_ACTOR_SYS_PRIO] = अणु
		.id = BOND_OPT_AD_ACTOR_SYS_PRIO,
		.name = "ad_actor_sys_prio",
		.unsuppmodes = BOND_MODE_ALL_EX(BIT(BOND_MODE_8023AD)),
		.values = bond_ad_actor_sys_prio_tbl,
		.set = bond_option_ad_actor_sys_prio_set,
	पूर्ण,
	[BOND_OPT_AD_ACTOR_SYSTEM] = अणु
		.id = BOND_OPT_AD_ACTOR_SYSTEM,
		.name = "ad_actor_system",
		.unsuppmodes = BOND_MODE_ALL_EX(BIT(BOND_MODE_8023AD)),
		.flags = BOND_OPTFLAG_RAWVAL,
		.set = bond_option_ad_actor_प्रणाली_set,
	पूर्ण,
	[BOND_OPT_AD_USER_PORT_KEY] = अणु
		.id = BOND_OPT_AD_USER_PORT_KEY,
		.name = "ad_user_port_key",
		.unsuppmodes = BOND_MODE_ALL_EX(BIT(BOND_MODE_8023AD)),
		.flags = BOND_OPTFLAG_IFDOWN,
		.values = bond_ad_user_port_key_tbl,
		.set = bond_option_ad_user_port_key_set,
	पूर्ण,
	[BOND_OPT_NUM_PEER_NOTIF_ALIAS] = अणु
		.id = BOND_OPT_NUM_PEER_NOTIF_ALIAS,
		.name = "num_grat_arp",
		.desc = "Number of peer notifications to send on failover event",
		.values = bond_num_peer_notअगर_tbl,
		.set = bond_option_num_peer_notअगर_set
	पूर्ण,
	[BOND_OPT_PEER_NOTIF_DELAY] = अणु
		.id = BOND_OPT_PEER_NOTIF_DELAY,
		.name = "peer_notif_delay",
		.desc = "Delay between each peer notification on failover event, in milliseconds",
		.values = bond_पूर्णांकmax_tbl,
		.set = bond_option_peer_notअगर_delay_set
	पूर्ण
पूर्ण;

/* Searches क्रम an option by name */
स्थिर काष्ठा bond_option *bond_opt_get_by_name(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा bond_option *opt;
	पूर्णांक option;

	क्रम (option = 0; option < BOND_OPT_LAST; option++) अणु
		opt = bond_opt_get(option);
		अगर (opt && !म_भेद(opt->name, name))
			वापस opt;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Searches क्रम a value in opt's values[] table */
स्थिर काष्ठा bond_opt_value *bond_opt_get_val(अचिन्हित पूर्णांक option, u64 val)
अणु
	स्थिर काष्ठा bond_option *opt;
	पूर्णांक i;

	opt = bond_opt_get(option);
	अगर (WARN_ON(!opt))
		वापस शून्य;
	क्रम (i = 0; opt->values && opt->values[i].string; i++)
		अगर (opt->values[i].value == val)
			वापस &opt->values[i];

	वापस शून्य;
पूर्ण

/* Searches क्रम a value in opt's values[] table which matches the flagmask */
अटल स्थिर काष्ठा bond_opt_value *bond_opt_get_flags(स्थिर काष्ठा bond_option *opt,
						       u32 flagmask)
अणु
	पूर्णांक i;

	क्रम (i = 0; opt->values && opt->values[i].string; i++)
		अगर (opt->values[i].flags & flagmask)
			वापस &opt->values[i];

	वापस शून्य;
पूर्ण

/* If maxval is missing then there's no range to check. In हाल minval is
 * missing then it's considered to be 0.
 */
अटल bool bond_opt_check_range(स्थिर काष्ठा bond_option *opt, u64 val)
अणु
	स्थिर काष्ठा bond_opt_value *minval, *maxval;

	minval = bond_opt_get_flags(opt, BOND_VALFLAG_MIN);
	maxval = bond_opt_get_flags(opt, BOND_VALFLAG_MAX);
	अगर (!maxval || (minval && val < minval->value) || val > maxval->value)
		वापस false;

	वापस true;
पूर्ण

/**
 * bond_opt_parse - parse option value
 * @opt: the option to parse against
 * @val: value to parse
 *
 * This function tries to extract the value from @val and check अगर it's
 * a possible match क्रम the option and वापसs शून्य अगर a match isn't found,
 * or the काष्ठा_opt_value that matched. It also strips the new line from
 * @val->string अगर it's present.
 */
स्थिर काष्ठा bond_opt_value *bond_opt_parse(स्थिर काष्ठा bond_option *opt,
					    काष्ठा bond_opt_value *val)
अणु
	अक्षर *p, valstr[BOND_OPT_MAX_NAMELEN + 1] = अणु 0, पूर्ण;
	स्थिर काष्ठा bond_opt_value *tbl;
	स्थिर काष्ठा bond_opt_value *ret = शून्य;
	bool checkval;
	पूर्णांक i, rv;

	/* No parsing अगर the option wants a raw val */
	अगर (opt->flags & BOND_OPTFLAG_RAWVAL)
		वापस val;

	tbl = opt->values;
	अगर (!tbl)
		जाओ out;

	/* ULदीर्घ_उच्च is used to bypass string processing */
	checkval = val->value != ULदीर्घ_उच्च;
	अगर (!checkval) अणु
		अगर (!val->string)
			जाओ out;
		p = म_अक्षर(val->string, '\n');
		अगर (p)
			*p = '\0';
		क्रम (p = val->string; *p; p++)
			अगर (!(है_अंक(*p) || है_खाली(*p)))
				अवरोध;
		/* The following code extracts the string to match or the value
		 * and sets checkval appropriately
		 */
		अगर (*p) अणु
			rv = माला_पूछो(val->string, "%32s", valstr);
		पूर्ण अन्यथा अणु
			rv = माला_पूछो(val->string, "%llu", &val->value);
			checkval = true;
		पूर्ण
		अगर (!rv)
			जाओ out;
	पूर्ण

	क्रम (i = 0; tbl[i].string; i++) अणु
		/* Check क्रम exact match */
		अगर (checkval) अणु
			अगर (val->value == tbl[i].value)
				ret = &tbl[i];
		पूर्ण अन्यथा अणु
			अगर (!म_भेद(valstr, "default") &&
			    (tbl[i].flags & BOND_VALFLAG_DEFAULT))
				ret = &tbl[i];

			अगर (!म_भेद(valstr, tbl[i].string))
				ret = &tbl[i];
		पूर्ण
		/* Found an exact match */
		अगर (ret)
			जाओ out;
	पूर्ण
	/* Possible range match */
	अगर (checkval && bond_opt_check_range(opt, val->value))
		ret = val;
out:
	वापस ret;
पूर्ण

/* Check opt's dependencies against bond mode and currently set options */
अटल पूर्णांक bond_opt_check_deps(काष्ठा bonding *bond,
			       स्थिर काष्ठा bond_option *opt)
अणु
	काष्ठा bond_params *params = &bond->params;

	अगर (test_bit(params->mode, &opt->unsuppmodes))
		वापस -EACCES;
	अगर ((opt->flags & BOND_OPTFLAG_NOSLAVES) && bond_has_slaves(bond))
		वापस -ENOTEMPTY;
	अगर ((opt->flags & BOND_OPTFLAG_IFDOWN) && (bond->dev->flags & IFF_UP))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम bond_opt_dep_prपूर्णांक(काष्ठा bonding *bond,
			       स्थिर काष्ठा bond_option *opt)
अणु
	स्थिर काष्ठा bond_opt_value *modeval;
	काष्ठा bond_params *params;

	params = &bond->params;
	modeval = bond_opt_get_val(BOND_OPT_MODE, params->mode);
	अगर (test_bit(params->mode, &opt->unsuppmodes))
		netdev_err(bond->dev, "option %s: mode dependency failed, not supported in mode %s(%llu)\n",
			   opt->name, modeval->string, modeval->value);
पूर्ण

अटल व्योम bond_opt_error_पूर्णांकerpret(काष्ठा bonding *bond,
				     स्थिर काष्ठा bond_option *opt,
				     पूर्णांक error, स्थिर काष्ठा bond_opt_value *val)
अणु
	स्थिर काष्ठा bond_opt_value *minval, *maxval;
	अक्षर *p;

	चयन (error) अणु
	हाल -EINVAL:
		अगर (val) अणु
			अगर (val->string) अणु
				/* someबार RAWVAL opts may have new lines */
				p = म_अक्षर(val->string, '\n');
				अगर (p)
					*p = '\0';
				netdev_err(bond->dev, "option %s: invalid value (%s)\n",
					   opt->name, val->string);
			पूर्ण अन्यथा अणु
				netdev_err(bond->dev, "option %s: invalid value (%llu)\n",
					   opt->name, val->value);
			पूर्ण
		पूर्ण
		minval = bond_opt_get_flags(opt, BOND_VALFLAG_MIN);
		maxval = bond_opt_get_flags(opt, BOND_VALFLAG_MAX);
		अगर (!maxval)
			अवरोध;
		netdev_err(bond->dev, "option %s: allowed values %llu - %llu\n",
			   opt->name, minval ? minval->value : 0, maxval->value);
		अवरोध;
	हाल -EACCES:
		bond_opt_dep_prपूर्णांक(bond, opt);
		अवरोध;
	हाल -ENOTEMPTY:
		netdev_err(bond->dev, "option %s: unable to set because the bond device has slaves\n",
			   opt->name);
		अवरोध;
	हाल -EBUSY:
		netdev_err(bond->dev, "option %s: unable to set because the bond device is up\n",
			   opt->name);
		अवरोध;
	हाल -ENODEV:
		अगर (val && val->string) अणु
			p = म_अक्षर(val->string, '\n');
			अगर (p)
				*p = '\0';
			netdev_err(bond->dev, "option %s: interface %s does not exist!\n",
				   opt->name, val->string);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * __bond_opt_set - set a bonding option
 * @bond: target bond device
 * @option: option to set
 * @val: value to set it to
 *
 * This function is used to change the bond's option value, it can be
 * used क्रम both enabling/changing an option and क्रम disabling it. RTNL lock
 * must be obtained beक्रमe calling this function.
 */
पूर्णांक __bond_opt_set(काष्ठा bonding *bond,
		   अचिन्हित पूर्णांक option, काष्ठा bond_opt_value *val)
अणु
	स्थिर काष्ठा bond_opt_value *retval = शून्य;
	स्थिर काष्ठा bond_option *opt;
	पूर्णांक ret = -ENOENT;

	ASSERT_RTNL();

	opt = bond_opt_get(option);
	अगर (WARN_ON(!val) || WARN_ON(!opt))
		जाओ out;
	ret = bond_opt_check_deps(bond, opt);
	अगर (ret)
		जाओ out;
	retval = bond_opt_parse(opt, val);
	अगर (!retval) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = opt->set(bond, retval);
out:
	अगर (ret)
		bond_opt_error_पूर्णांकerpret(bond, opt, ret, val);

	वापस ret;
पूर्ण
/**
 * __bond_opt_set_notअगरy - set a bonding option
 * @bond: target bond device
 * @option: option to set
 * @val: value to set it to
 *
 * This function is used to change the bond's option value and trigger
 * a notअगरication to user sapce. It can be used क्रम both enabling/changing
 * an option and क्रम disabling it. RTNL lock must be obtained beक्रमe calling
 * this function.
 */
पूर्णांक __bond_opt_set_notअगरy(काष्ठा bonding *bond,
			  अचिन्हित पूर्णांक option, काष्ठा bond_opt_value *val)
अणु
	पूर्णांक ret = -ENOENT;

	ASSERT_RTNL();

	ret = __bond_opt_set(bond, option, val);

	अगर (!ret && (bond->dev->reg_state == NETREG_REGISTERED))
		call_netdevice_notअगरiers(NETDEV_CHANGEINFODATA, bond->dev);

	वापस ret;
पूर्ण

/**
 * bond_opt_tryset_rtnl - try to acquire rtnl and call __bond_opt_set
 * @bond: target bond device
 * @option: option to set
 * @buf: value to set it to
 *
 * This function tries to acquire RTNL without blocking and अगर successful
 * calls __bond_opt_set. It is मुख्यly used क्रम sysfs option manipulation.
 */
पूर्णांक bond_opt_tryset_rtnl(काष्ठा bonding *bond, अचिन्हित पूर्णांक option, अक्षर *buf)
अणु
	काष्ठा bond_opt_value optval;
	पूर्णांक ret;

	अगर (!rtnl_trylock())
		वापस restart_syscall();
	bond_opt_initstr(&optval, buf);
	ret = __bond_opt_set_notअगरy(bond, option, &optval);
	rtnl_unlock();

	वापस ret;
पूर्ण

/**
 * bond_opt_get - get a poपूर्णांकer to an option
 * @option: option क्रम which to वापस a poपूर्णांकer
 *
 * This function checks अगर option is valid and अगर so वापसs a poपूर्णांकer
 * to its entry in the bond_opts[] option array.
 */
स्थिर काष्ठा bond_option *bond_opt_get(अचिन्हित पूर्णांक option)
अणु
	अगर (!BOND_OPT_VALID(option))
		वापस शून्य;

	वापस &bond_opts[option];
पूर्ण

अटल bool bond_set_xfrm_features(काष्ठा bonding *bond)
अणु
	अगर (!IS_ENABLED(CONFIG_XFRM_OFFLOAD))
		वापस false;

	अगर (BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP)
		bond->dev->wanted_features |= BOND_XFRM_FEATURES;
	अन्यथा
		bond->dev->wanted_features &= ~BOND_XFRM_FEATURES;

	वापस true;
पूर्ण

अटल bool bond_set_tls_features(काष्ठा bonding *bond)
अणु
	अगर (!IS_ENABLED(CONFIG_TLS_DEVICE))
		वापस false;

	अगर (bond_sk_check(bond))
		bond->dev->wanted_features |= BOND_TLS_FEATURES;
	अन्यथा
		bond->dev->wanted_features &= ~BOND_TLS_FEATURES;

	वापस true;
पूर्ण

अटल पूर्णांक bond_option_mode_set(काष्ठा bonding *bond,
				स्थिर काष्ठा bond_opt_value *newval)
अणु
	अगर (!bond_mode_uses_arp(newval->value)) अणु
		अगर (bond->params.arp_पूर्णांकerval) अणु
			netdev_dbg(bond->dev, "%s mode is incompatible with arp monitoring, start mii monitoring\n",
				   newval->string);
			/* disable arp monitoring */
			bond->params.arp_पूर्णांकerval = 0;
		पूर्ण

		अगर (!bond->params.miimon) अणु
			/* set miimon to शेष value */
			bond->params.miimon = BOND_DEFAULT_MIIMON;
			netdev_dbg(bond->dev, "Setting MII monitoring interval to %d\n",
				   bond->params.miimon);
		पूर्ण
	पूर्ण

	अगर (newval->value == BOND_MODE_ALB)
		bond->params.tlb_dynamic_lb = 1;

	/* करोn't cache arp_validate between modes */
	bond->params.arp_validate = BOND_ARP_VALIDATE_NONE;
	bond->params.mode = newval->value;

	अगर (bond->dev->reg_state == NETREG_REGISTERED) अणु
		bool update = false;

		update |= bond_set_xfrm_features(bond);
		update |= bond_set_tls_features(bond);

		अगर (update)
			netdev_update_features(bond->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_active_slave_set(काष्ठा bonding *bond,
					स्थिर काष्ठा bond_opt_value *newval)
अणु
	अक्षर अगरname[IFNAMSIZ] = अणु 0, पूर्ण;
	काष्ठा net_device *slave_dev;
	पूर्णांक ret = 0;

	माला_पूछो(newval->string, "%15s", अगरname); /* IFNAMSIZ */
	अगर (!म_माप(अगरname) || newval->string[0] == '\n') अणु
		slave_dev = शून्य;
	पूर्ण अन्यथा अणु
		slave_dev = __dev_get_by_name(dev_net(bond->dev), अगरname);
		अगर (!slave_dev)
			वापस -ENODEV;
	पूर्ण

	अगर (slave_dev) अणु
		अगर (!netअगर_is_bond_slave(slave_dev)) अणु
			slave_err(bond->dev, slave_dev, "Device is not bonding slave\n");
			वापस -EINVAL;
		पूर्ण

		अगर (bond->dev != netdev_master_upper_dev_get(slave_dev)) अणु
			slave_err(bond->dev, slave_dev, "Device is not our slave\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	block_netpoll_tx();
	/* check to see अगर we are clearing active */
	अगर (!slave_dev) अणु
		netdev_dbg(bond->dev, "Clearing current active slave\n");
		RCU_INIT_POINTER(bond->curr_active_slave, शून्य);
		bond_select_active_slave(bond);
	पूर्ण अन्यथा अणु
		काष्ठा slave *old_active = rtnl_dereference(bond->curr_active_slave);
		काष्ठा slave *new_active = bond_slave_get_rtnl(slave_dev);

		BUG_ON(!new_active);

		अगर (new_active == old_active) अणु
			/* करो nothing */
			slave_dbg(bond->dev, new_active->dev, "is already the current active slave\n");
		पूर्ण अन्यथा अणु
			अगर (old_active && (new_active->link == BOND_LINK_UP) &&
			    bond_slave_is_up(new_active)) अणु
				slave_dbg(bond->dev, new_active->dev, "Setting as active slave\n");
				bond_change_active_slave(bond, new_active);
			पूर्ण अन्यथा अणु
				slave_err(bond->dev, new_active->dev, "Could not set as active slave; either %s is down or the link is down\n",
					  new_active->dev->name);
				ret = -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	unblock_netpoll_tx();

	वापस ret;
पूर्ण

/* There are two tricky bits here.  First, अगर MII monitoring is activated, then
 * we must disable ARP monitoring.  Second, अगर the समयr isn't running, we must
 * start it.
 */
अटल पूर्णांक bond_option_miimon_set(काष्ठा bonding *bond,
				  स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting MII monitoring interval to %llu\n",
		   newval->value);
	bond->params.miimon = newval->value;
	अगर (bond->params.updelay)
		netdev_dbg(bond->dev, "Note: Updating updelay (to %d) since it is a multiple of the miimon value\n",
			   bond->params.updelay * bond->params.miimon);
	अगर (bond->params.करोwndelay)
		netdev_dbg(bond->dev, "Note: Updating downdelay (to %d) since it is a multiple of the miimon value\n",
			   bond->params.करोwndelay * bond->params.miimon);
	अगर (bond->params.peer_notअगर_delay)
		netdev_dbg(bond->dev, "Note: Updating peer_notif_delay (to %d) since it is a multiple of the miimon value\n",
			   bond->params.peer_notअगर_delay * bond->params.miimon);
	अगर (newval->value && bond->params.arp_पूर्णांकerval) अणु
		netdev_dbg(bond->dev, "MII monitoring cannot be used with ARP monitoring - disabling ARP monitoring...\n");
		bond->params.arp_पूर्णांकerval = 0;
		अगर (bond->params.arp_validate)
			bond->params.arp_validate = BOND_ARP_VALIDATE_NONE;
	पूर्ण
	अगर (bond->dev->flags & IFF_UP) अणु
		/* If the पूर्णांकerface is up, we may need to fire off
		 * the MII समयr. If the पूर्णांकerface is करोwn, the
		 * समयr will get fired off when the खोलो function
		 * is called.
		 */
		अगर (!newval->value) अणु
			cancel_delayed_work_sync(&bond->mii_work);
		पूर्ण अन्यथा अणु
			cancel_delayed_work_sync(&bond->arp_work);
			queue_delayed_work(bond->wq, &bond->mii_work, 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Set up, करोwn and peer notअगरication delays. These must be multiples
 * of the MII monitoring value, and are stored पूर्णांकernally as the
 * multiplier. Thus, we must translate to MS क्रम the real world.
 */
अटल पूर्णांक _bond_option_delay_set(काष्ठा bonding *bond,
				  स्थिर काष्ठा bond_opt_value *newval,
				  स्थिर अक्षर *name,
				  पूर्णांक *target)
अणु
	पूर्णांक value = newval->value;

	अगर (!bond->params.miimon) अणु
		netdev_err(bond->dev, "Unable to set %s as MII monitoring is disabled\n",
			   name);
		वापस -EPERM;
	पूर्ण
	अगर ((value % bond->params.miimon) != 0) अणु
		netdev_warn(bond->dev,
			    "%s (%d) is not a multiple of miimon (%d), value rounded to %d ms\n",
			    name,
			    value, bond->params.miimon,
			    (value / bond->params.miimon) *
			    bond->params.miimon);
	पूर्ण
	*target = value / bond->params.miimon;
	netdev_dbg(bond->dev, "Setting %s to %d\n",
		   name,
		   *target * bond->params.miimon);

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_updelay_set(काष्ठा bonding *bond,
				   स्थिर काष्ठा bond_opt_value *newval)
अणु
	वापस _bond_option_delay_set(bond, newval, "up delay",
				      &bond->params.updelay);
पूर्ण

अटल पूर्णांक bond_option_करोwndelay_set(काष्ठा bonding *bond,
				     स्थिर काष्ठा bond_opt_value *newval)
अणु
	वापस _bond_option_delay_set(bond, newval, "down delay",
				      &bond->params.करोwndelay);
पूर्ण

अटल पूर्णांक bond_option_peer_notअगर_delay_set(काष्ठा bonding *bond,
					    स्थिर काष्ठा bond_opt_value *newval)
अणु
	पूर्णांक ret = _bond_option_delay_set(bond, newval,
					 "peer notification delay",
					 &bond->params.peer_notअगर_delay);
	वापस ret;
पूर्ण

अटल पूर्णांक bond_option_use_carrier_set(काष्ठा bonding *bond,
				       स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting use_carrier to %llu\n",
		   newval->value);
	bond->params.use_carrier = newval->value;

	वापस 0;
पूर्ण

/* There are two tricky bits here.  First, अगर ARP monitoring is activated, then
 * we must disable MII monitoring.  Second, अगर the ARP समयr isn't running,
 * we must start it.
 */
अटल पूर्णांक bond_option_arp_पूर्णांकerval_set(काष्ठा bonding *bond,
					स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting ARP monitoring interval to %llu\n",
		   newval->value);
	bond->params.arp_पूर्णांकerval = newval->value;
	अगर (newval->value) अणु
		अगर (bond->params.miimon) अणु
			netdev_dbg(bond->dev, "ARP monitoring cannot be used with MII monitoring. Disabling MII monitoring\n");
			bond->params.miimon = 0;
		पूर्ण
		अगर (!bond->params.arp_tarमाला_लो[0])
			netdev_dbg(bond->dev, "ARP monitoring has been set up, but no ARP targets have been specified\n");
	पूर्ण
	अगर (bond->dev->flags & IFF_UP) अणु
		/* If the पूर्णांकerface is up, we may need to fire off
		 * the ARP समयr.  If the पूर्णांकerface is करोwn, the
		 * समयr will get fired off when the खोलो function
		 * is called.
		 */
		अगर (!newval->value) अणु
			अगर (bond->params.arp_validate)
				bond->recv_probe = शून्य;
			cancel_delayed_work_sync(&bond->arp_work);
		पूर्ण अन्यथा अणु
			/* arp_validate can be set only in active-backup mode */
			bond->recv_probe = bond_arp_rcv;
			cancel_delayed_work_sync(&bond->mii_work);
			queue_delayed_work(bond->wq, &bond->arp_work, 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम _bond_options_arp_ip_target_set(काष्ठा bonding *bond, पूर्णांक slot,
					    __be32 target,
					    अचिन्हित दीर्घ last_rx)
अणु
	__be32 *tarमाला_लो = bond->params.arp_tarमाला_लो;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	अगर (slot >= 0 && slot < BOND_MAX_ARP_TARGETS) अणु
		bond_क्रम_each_slave(bond, slave, iter)
			slave->target_last_arp_rx[slot] = last_rx;
		tarमाला_लो[slot] = target;
	पूर्ण
पूर्ण

अटल पूर्णांक _bond_option_arp_ip_target_add(काष्ठा bonding *bond, __be32 target)
अणु
	__be32 *tarमाला_लो = bond->params.arp_tarमाला_लो;
	पूर्णांक ind;

	अगर (!bond_is_ip_target_ok(target)) अणु
		netdev_err(bond->dev, "invalid ARP target %pI4 specified for addition\n",
			   &target);
		वापस -EINVAL;
	पूर्ण

	अगर (bond_get_tarमाला_लो_ip(tarमाला_लो, target) != -1) अणु /* dup */
		netdev_err(bond->dev, "ARP target %pI4 is already present\n",
			   &target);
		वापस -EINVAL;
	पूर्ण

	ind = bond_get_tarमाला_लो_ip(tarमाला_लो, 0); /* first मुक्त slot */
	अगर (ind == -1) अणु
		netdev_err(bond->dev, "ARP target table is full!\n");
		वापस -EINVAL;
	पूर्ण

	netdev_dbg(bond->dev, "Adding ARP target %pI4\n", &target);

	_bond_options_arp_ip_target_set(bond, ind, target, jअगरfies);

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_arp_ip_target_add(काष्ठा bonding *bond, __be32 target)
अणु
	वापस _bond_option_arp_ip_target_add(bond, target);
पूर्ण

अटल पूर्णांक bond_option_arp_ip_target_rem(काष्ठा bonding *bond, __be32 target)
अणु
	__be32 *tarमाला_लो = bond->params.arp_tarमाला_लो;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	अचिन्हित दीर्घ *tarमाला_लो_rx;
	पूर्णांक ind, i;

	अगर (!bond_is_ip_target_ok(target)) अणु
		netdev_err(bond->dev, "invalid ARP target %pI4 specified for removal\n",
			   &target);
		वापस -EINVAL;
	पूर्ण

	ind = bond_get_tarमाला_लो_ip(tarमाला_लो, target);
	अगर (ind == -1) अणु
		netdev_err(bond->dev, "unable to remove nonexistent ARP target %pI4\n",
			   &target);
		वापस -EINVAL;
	पूर्ण

	अगर (ind == 0 && !tarमाला_लो[1] && bond->params.arp_पूर्णांकerval)
		netdev_warn(bond->dev, "Removing last arp target with arp_interval on\n");

	netdev_dbg(bond->dev, "Removing ARP target %pI4\n", &target);

	bond_क्रम_each_slave(bond, slave, iter) अणु
		tarमाला_लो_rx = slave->target_last_arp_rx;
		क्रम (i = ind; (i < BOND_MAX_ARP_TARGETS-1) && tarमाला_लो[i+1]; i++)
			tarमाला_लो_rx[i] = tarमाला_लो_rx[i+1];
		tarमाला_लो_rx[i] = 0;
	पूर्ण
	क्रम (i = ind; (i < BOND_MAX_ARP_TARGETS-1) && tarमाला_लो[i+1]; i++)
		tarमाला_लो[i] = tarमाला_लो[i+1];
	tarमाला_लो[i] = 0;

	वापस 0;
पूर्ण

व्योम bond_option_arp_ip_tarमाला_लो_clear(काष्ठा bonding *bond)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BOND_MAX_ARP_TARGETS; i++)
		_bond_options_arp_ip_target_set(bond, i, 0, 0);
पूर्ण

अटल पूर्णांक bond_option_arp_ip_tarमाला_लो_set(काष्ठा bonding *bond,
					  स्थिर काष्ठा bond_opt_value *newval)
अणु
	पूर्णांक ret = -EPERM;
	__be32 target;

	अगर (newval->string) अणु
		अगर (!in4_pton(newval->string+1, -1, (u8 *)&target, -1, शून्य)) अणु
			netdev_err(bond->dev, "invalid ARP target %pI4 specified\n",
				   &target);
			वापस ret;
		पूर्ण
		अगर (newval->string[0] == '+')
			ret = bond_option_arp_ip_target_add(bond, target);
		अन्यथा अगर (newval->string[0] == '-')
			ret = bond_option_arp_ip_target_rem(bond, target);
		अन्यथा
			netdev_err(bond->dev, "no command found in arp_ip_targets file - use +<addr> or -<addr>\n");
	पूर्ण अन्यथा अणु
		target = newval->value;
		ret = bond_option_arp_ip_target_add(bond, target);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bond_option_arp_validate_set(काष्ठा bonding *bond,
					स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting arp_validate to %s (%llu)\n",
		   newval->string, newval->value);
	bond->params.arp_validate = newval->value;

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_arp_all_tarमाला_लो_set(काष्ठा bonding *bond,
					   स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting arp_all_targets to %s (%llu)\n",
		   newval->string, newval->value);
	bond->params.arp_all_tarमाला_लो = newval->value;

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_primary_set(काष्ठा bonding *bond,
				   स्थिर काष्ठा bond_opt_value *newval)
अणु
	अक्षर *p, *primary = newval->string;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	block_netpoll_tx();

	p = म_अक्षर(primary, '\n');
	अगर (p)
		*p = '\0';
	/* check to see अगर we are clearing primary */
	अगर (!म_माप(primary)) अणु
		netdev_dbg(bond->dev, "Setting primary slave to None\n");
		RCU_INIT_POINTER(bond->primary_slave, शून्य);
		स_रखो(bond->params.primary, 0, माप(bond->params.primary));
		bond_select_active_slave(bond);
		जाओ out;
	पूर्ण

	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (म_भेदन(slave->dev->name, primary, IFNAMSIZ) == 0) अणु
			slave_dbg(bond->dev, slave->dev, "Setting as primary slave\n");
			rcu_assign_poपूर्णांकer(bond->primary_slave, slave);
			म_नकल(bond->params.primary, slave->dev->name);
			bond->क्रमce_primary = true;
			bond_select_active_slave(bond);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (rtnl_dereference(bond->primary_slave)) अणु
		netdev_dbg(bond->dev, "Setting primary slave to None\n");
		RCU_INIT_POINTER(bond->primary_slave, शून्य);
		bond_select_active_slave(bond);
	पूर्ण
	म_नकलन(bond->params.primary, primary, IFNAMSIZ);
	bond->params.primary[IFNAMSIZ - 1] = 0;

	netdev_dbg(bond->dev, "Recording %s as primary, but it has not been enslaved yet\n",
		   primary);

out:
	unblock_netpoll_tx();

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_primary_reselect_set(काष्ठा bonding *bond,
					    स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting primary_reselect to %s (%llu)\n",
		   newval->string, newval->value);
	bond->params.primary_reselect = newval->value;

	block_netpoll_tx();
	bond_select_active_slave(bond);
	unblock_netpoll_tx();

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_fail_over_mac_set(काष्ठा bonding *bond,
					 स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting fail_over_mac to %s (%llu)\n",
		   newval->string, newval->value);
	bond->params.fail_over_mac = newval->value;

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_xmit_hash_policy_set(काष्ठा bonding *bond,
					    स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting xmit hash policy to %s (%llu)\n",
		   newval->string, newval->value);
	bond->params.xmit_policy = newval->value;

	अगर (bond->dev->reg_state == NETREG_REGISTERED)
		अगर (bond_set_tls_features(bond))
			netdev_update_features(bond->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_resend_igmp_set(काष्ठा bonding *bond,
				       स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting resend_igmp to %llu\n",
		   newval->value);
	bond->params.resend_igmp = newval->value;

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_num_peer_notअगर_set(काष्ठा bonding *bond,
				   स्थिर काष्ठा bond_opt_value *newval)
अणु
	bond->params.num_peer_notअगर = newval->value;

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_all_slaves_active_set(काष्ठा bonding *bond,
					     स्थिर काष्ठा bond_opt_value *newval)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	अगर (newval->value == bond->params.all_slaves_active)
		वापस 0;
	bond->params.all_slaves_active = newval->value;
	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (!bond_is_active_slave(slave)) अणु
			अगर (newval->value)
				slave->inactive = 0;
			अन्यथा
				slave->inactive = 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_min_links_set(काष्ठा bonding *bond,
				     स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting min links value to %llu\n",
		   newval->value);
	bond->params.min_links = newval->value;
	bond_set_carrier(bond);

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_lp_पूर्णांकerval_set(काष्ठा bonding *bond,
				       स्थिर काष्ठा bond_opt_value *newval)
अणु
	bond->params.lp_पूर्णांकerval = newval->value;

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_pps_set(काष्ठा bonding *bond,
			       स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting packets per slave to %llu\n",
		   newval->value);
	bond->params.packets_per_slave = newval->value;
	अगर (newval->value > 0) अणु
		bond->params.reciprocal_packets_per_slave =
			reciprocal_value(newval->value);
	पूर्ण अन्यथा अणु
		/* reciprocal_packets_per_slave is unused अगर
		 * packets_per_slave is 0 or 1, just initialize it
		 */
		bond->params.reciprocal_packets_per_slave =
			(काष्ठा reciprocal_value) अणु 0 पूर्ण;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_lacp_rate_set(काष्ठा bonding *bond,
				     स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting LACP rate to %s (%llu)\n",
		   newval->string, newval->value);
	bond->params.lacp_fast = newval->value;
	bond_3ad_update_lacp_rate(bond);

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_ad_select_set(काष्ठा bonding *bond,
				     स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting ad_select to %s (%llu)\n",
		   newval->string, newval->value);
	bond->params.ad_select = newval->value;

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_queue_id_set(काष्ठा bonding *bond,
				    स्थिर काष्ठा bond_opt_value *newval)
अणु
	काष्ठा slave *slave, *update_slave;
	काष्ठा net_device *sdev;
	काष्ठा list_head *iter;
	अक्षर *delim;
	पूर्णांक ret = 0;
	u16 qid;

	/* delim will poपूर्णांक to queue id अगर successful */
	delim = म_अक्षर(newval->string, ':');
	अगर (!delim)
		जाओ err_no_cmd;

	/* Terminate string that poपूर्णांकs to device name and bump it
	 * up one, so we can पढ़ो the queue id there.
	 */
	*delim = '\0';
	अगर (माला_पूछो(++delim, "%hd\n", &qid) != 1)
		जाओ err_no_cmd;

	/* Check buffer length, valid अगरname and queue id */
	अगर (!dev_valid_name(newval->string) ||
	    qid > bond->dev->real_num_tx_queues)
		जाओ err_no_cmd;

	/* Get the poपूर्णांकer to that पूर्णांकerface अगर it exists */
	sdev = __dev_get_by_name(dev_net(bond->dev), newval->string);
	अगर (!sdev)
		जाओ err_no_cmd;

	/* Search क्रम thes slave and check क्रम duplicate qids */
	update_slave = शून्य;
	bond_क्रम_each_slave(bond, slave, iter) अणु
		अगर (sdev == slave->dev)
			/* We करोn't need to check the matching
			 * slave क्रम dups, since we're overwriting it
			 */
			update_slave = slave;
		अन्यथा अगर (qid && qid == slave->queue_id) अणु
			जाओ err_no_cmd;
		पूर्ण
	पूर्ण

	अगर (!update_slave)
		जाओ err_no_cmd;

	/* Actually set the qids क्रम the slave */
	update_slave->queue_id = qid;

out:
	वापस ret;

err_no_cmd:
	netdev_dbg(bond->dev, "invalid input for queue_id set\n");
	ret = -EPERM;
	जाओ out;

पूर्ण

अटल पूर्णांक bond_option_slaves_set(काष्ठा bonding *bond,
				  स्थिर काष्ठा bond_opt_value *newval)
अणु
	अक्षर command[IFNAMSIZ + 1] = अणु 0, पूर्ण;
	काष्ठा net_device *dev;
	अक्षर *अगरname;
	पूर्णांक ret;

	माला_पूछो(newval->string, "%16s", command); /* IFNAMSIZ*/
	अगरname = command + 1;
	अगर ((म_माप(command) <= 1) ||
	    (command[0] != '+' && command[0] != '-') ||
	    !dev_valid_name(अगरname))
		जाओ err_no_cmd;

	dev = __dev_get_by_name(dev_net(bond->dev), अगरname);
	अगर (!dev) अणु
		netdev_dbg(bond->dev, "interface %s does not exist!\n",
			   अगरname);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (command[0]) अणु
	हाल '+':
		slave_dbg(bond->dev, dev, "Enslaving interface\n");
		ret = bond_enslave(bond->dev, dev, शून्य);
		अवरोध;

	हाल '-':
		slave_dbg(bond->dev, dev, "Releasing interface\n");
		ret = bond_release(bond->dev, dev);
		अवरोध;

	शेष:
		/* should not run here. */
		जाओ err_no_cmd;
	पूर्ण

out:
	वापस ret;

err_no_cmd:
	netdev_err(bond->dev, "no command found in slaves file - use +ifname or -ifname\n");
	ret = -EPERM;
	जाओ out;
पूर्ण

अटल पूर्णांक bond_option_tlb_dynamic_lb_set(काष्ठा bonding *bond,
					  स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting dynamic-lb to %s (%llu)\n",
		   newval->string, newval->value);
	bond->params.tlb_dynamic_lb = newval->value;

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_ad_actor_sys_prio_set(काष्ठा bonding *bond,
					     स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting ad_actor_sys_prio to %llu\n",
		   newval->value);

	bond->params.ad_actor_sys_prio = newval->value;
	bond_3ad_update_ad_actor_settings(bond);

	वापस 0;
पूर्ण

अटल पूर्णांक bond_option_ad_actor_प्रणाली_set(काष्ठा bonding *bond,
					   स्थिर काष्ठा bond_opt_value *newval)
अणु
	u8 macaddr[ETH_ALEN];
	u8 *mac;

	अगर (newval->string) अणु
		अगर (!mac_pton(newval->string, macaddr))
			जाओ err;
		mac = macaddr;
	पूर्ण अन्यथा अणु
		mac = (u8 *)&newval->value;
	पूर्ण

	अगर (!is_valid_ether_addr(mac))
		जाओ err;

	netdev_dbg(bond->dev, "Setting ad_actor_system to %pM\n", mac);
	ether_addr_copy(bond->params.ad_actor_प्रणाली, mac);
	bond_3ad_update_ad_actor_settings(bond);

	वापस 0;

err:
	netdev_err(bond->dev, "Invalid ad_actor_system MAC address.\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bond_option_ad_user_port_key_set(काष्ठा bonding *bond,
					    स्थिर काष्ठा bond_opt_value *newval)
अणु
	netdev_dbg(bond->dev, "Setting ad_user_port_key to %llu\n",
		   newval->value);

	bond->params.ad_user_port_key = newval->value;
	वापस 0;
पूर्ण
