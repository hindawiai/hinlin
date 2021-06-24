<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ WITH Linux-syscall-note */
/*
 * Bond several ethernet पूर्णांकerfaces पूर्णांकo a Cisco, running 'Etherchannel'.
 *
 *
 * Portions are (c) Copyright 1995 Simon "Guru Aleph-Null" Janes
 * NCM: Network and Communications Management, Inc.
 *
 * BUT, I'm the one who modअगरied it क्रम ethernet, so:
 * (c) Copyright 1999, Thomas Davis, tadavis@lbl.gov
 *
 *	This software may be used and distributed according to the terms
 *	of the GNU Public License, incorporated herein by reference.
 *
 * 2003/03/18 - Amir Noam <amir.noam at पूर्णांकel करोt com>
 *	- Added support क्रम getting slave's speed and duplex via ethtool.
 *	  Needed क्रम 802.3ad and other future modes.
 *
 * 2003/03/18 - Tsippy Mendelson <tsippy.mendelson at पूर्णांकel करोt com> and
 *		Shmulik Hen <shmulik.hen at पूर्णांकel करोt com>
 *	- Enable support of modes that need to use the unique mac address of
 *	  each slave.
 *
 * 2003/03/18 - Tsippy Mendelson <tsippy.mendelson at पूर्णांकel करोt com> and
 *		Amir Noam <amir.noam at पूर्णांकel करोt com>
 *	- Moved driver's निजी data types to bonding.h
 *
 * 2003/03/18 - Amir Noam <amir.noam at पूर्णांकel करोt com>,
 *		Tsippy Mendelson <tsippy.mendelson at पूर्णांकel करोt com> and
 *		Shmulik Hen <shmulik.hen at पूर्णांकel करोt com>
 *	- Added support क्रम IEEE 802.3ad Dynamic link aggregation mode.
 *
 * 2003/05/01 - Amir Noam <amir.noam at पूर्णांकel करोt com>
 *	- Added ABI version control to restore compatibility between
 *	  new/old अगरenslave and new/old bonding.
 *
 * 2003/12/01 - Shmulik Hen <shmulik.hen at पूर्णांकel करोt com>
 *	- Code cleanup and style changes
 *
 * 2005/05/05 - Jason Gabler <jygabler at lbl करोt gov>
 *      - added definitions क्रम various XOR hashing policies
 */

#अगर_अघोषित _LINUX_IF_BONDING_H
#घोषणा _LINUX_IF_BONDING_H

#समावेश <linux/अगर.h>
#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

/* userland - kernel ABI version (2003/05/08) */
#घोषणा BOND_ABI_VERSION 2

/*
 * We can हटाओ these ioctl definitions in 2.5.  People should use the
 * SIOC*** versions of them instead
 */
#घोषणा BOND_ENSLAVE_OLD		(SIOCDEVPRIVATE)
#घोषणा BOND_RELEASE_OLD		(SIOCDEVPRIVATE + 1)
#घोषणा BOND_SETHWADDR_OLD		(SIOCDEVPRIVATE + 2)
#घोषणा BOND_SLAVE_INFO_QUERY_OLD	(SIOCDEVPRIVATE + 11)
#घोषणा BOND_INFO_QUERY_OLD		(SIOCDEVPRIVATE + 12)
#घोषणा BOND_CHANGE_ACTIVE_OLD		(SIOCDEVPRIVATE + 13)

#घोषणा BOND_CHECK_MII_STATUS	(SIOCGMIIPHY)

#घोषणा BOND_MODE_ROUNDROBIN	0
#घोषणा BOND_MODE_ACTIVEBACKUP	1
#घोषणा BOND_MODE_XOR		2
#घोषणा BOND_MODE_BROADCAST	3
#घोषणा BOND_MODE_8023AD        4
#घोषणा BOND_MODE_TLB           5
#घोषणा BOND_MODE_ALB		6 /* TLB + RLB (receive load balancing) */

/* each slave's link has 4 states */
#घोषणा BOND_LINK_UP    0           /* link is up and running */
#घोषणा BOND_LINK_FAIL  1           /* link has just gone करोwn */
#घोषणा BOND_LINK_DOWN  2           /* link has been करोwn क्रम too दीर्घ समय */
#घोषणा BOND_LINK_BACK  3           /* link is going back */

/* each slave has several states */
#घोषणा BOND_STATE_ACTIVE       0   /* link is active */
#घोषणा BOND_STATE_BACKUP       1   /* link is backup */

#घोषणा BOND_DEFAULT_MAX_BONDS  1   /* Default maximum number of devices to support */

#घोषणा BOND_DEFAULT_TX_QUEUES 16   /* Default number of tx queues per device */

#घोषणा BOND_DEFAULT_RESEND_IGMP	1 /* Default number of IGMP membership reports */

/* hashing types */
#घोषणा BOND_XMIT_POLICY_LAYER2		0 /* layer 2 (MAC only), शेष */
#घोषणा BOND_XMIT_POLICY_LAYER34	1 /* layer 3+4 (IP ^ (TCP || UDP)) */
#घोषणा BOND_XMIT_POLICY_LAYER23	2 /* layer 2+3 (IP ^ MAC) */
#घोषणा BOND_XMIT_POLICY_ENCAP23	3 /* encapsulated layer 2+3 */
#घोषणा BOND_XMIT_POLICY_ENCAP34	4 /* encapsulated layer 3+4 */
#घोषणा BOND_XMIT_POLICY_VLAN_SRCMAC	5 /* vlan + source MAC */

/* 802.3ad port state definitions (43.4.2.2 in the 802.3ad standard) */
#घोषणा LACP_STATE_LACP_ACTIVITY   0x1
#घोषणा LACP_STATE_LACP_TIMEOUT    0x2
#घोषणा LACP_STATE_AGGREGATION     0x4
#घोषणा LACP_STATE_SYNCHRONIZATION 0x8
#घोषणा LACP_STATE_COLLECTING      0x10
#घोषणा LACP_STATE_DISTRIBUTING    0x20
#घोषणा LACP_STATE_DEFAULTED       0x40
#घोषणा LACP_STATE_EXPIRED         0x80

प्रकार काष्ठा अगरbond अणु
	__s32 bond_mode;
	__s32 num_slaves;
	__s32 miimon;
पूर्ण अगरbond;

प्रकार काष्ठा अगरslave अणु
	__s32 slave_id; /* Used as an IN param to the BOND_SLAVE_INFO_QUERY ioctl */
	अक्षर slave_name[IFNAMSIZ];
	__s8 link;
	__s8 state;
	__u32  link_failure_count;
पूर्ण अगरslave;

काष्ठा ad_info अणु
	__u16 aggregator_id;
	__u16 ports;
	__u16 actor_key;
	__u16 partner_key;
	__u8 partner_प्रणाली[ETH_ALEN];
पूर्ण;

/* Embedded inside LINK_XSTATS_TYPE_BOND */
क्रमागत अणु
	BOND_XSTATS_UNSPEC,
	BOND_XSTATS_3AD,
	__BOND_XSTATS_MAX
पूर्ण;
#घोषणा BOND_XSTATS_MAX (__BOND_XSTATS_MAX - 1)

/* Embedded inside BOND_XSTATS_3AD */
क्रमागत अणु
	BOND_3AD_STAT_LACPDU_RX,
	BOND_3AD_STAT_LACPDU_TX,
	BOND_3AD_STAT_LACPDU_UNKNOWN_RX,
	BOND_3AD_STAT_LACPDU_ILLEGAL_RX,
	BOND_3AD_STAT_MARKER_RX,
	BOND_3AD_STAT_MARKER_TX,
	BOND_3AD_STAT_MARKER_RESP_RX,
	BOND_3AD_STAT_MARKER_RESP_TX,
	BOND_3AD_STAT_MARKER_UNKNOWN_RX,
	BOND_3AD_STAT_PAD,
	__BOND_3AD_STAT_MAX
पूर्ण;
#घोषणा BOND_3AD_STAT_MAX (__BOND_3AD_STAT_MAX - 1)

#पूर्ण_अगर /* _LINUX_IF_BONDING_H */
