<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
 */
#अगर_अघोषित _FC_FIP_H_
#घोषणा _FC_FIP_H_

#समावेश <scsi/fc/fc_ns.h>

/*
 * This version is based on:
 * http://www.t11.org/ftp/t11/pub/fc/bb-5/08-543v1.pdf
 * and T11 FC-BB-6 13-091v5.pdf (December 2013 VN2VN proposal)
 */

#घोषणा FIP_DEF_PRI	128	/* शेष selection priority */
#घोषणा FIP_DEF_FC_MAP	0x0efc00 /* शेष FCoE MAP (MAC OUI) value */
#घोषणा FIP_DEF_FKA	8000	/* शेष FCF keep-alive/advert period (mS) */
#घोषणा FIP_VN_KA_PERIOD 90000	/* required VN_port keep-alive period (mS) */
#घोषणा FIP_FCF_FUZZ	100	/* अक्रमom समय added by FCF (mS) */

/*
 * VN2VN proposed-standard values.
 */
#घोषणा FIP_VN_FC_MAP	0x0efd00 /* MAC OUI क्रम VN2VN use */
#घोषणा FIP_VN_PROBE_WAIT 100	/* पूर्णांकerval between VN2VN probes (ms) */
#घोषणा FIP_VN_ANN_WAIT 400	/* पूर्णांकerval between VN2VN announcements (ms) */
#घोषणा FIP_VN_RLIM_INT 10000	/* पूर्णांकerval between probes when rate limited */
#घोषणा FIP_VN_RLIM_COUNT 10	/* number of probes beक्रमe rate limiting */
#घोषणा FIP_VN_BEACON_INT 8000	/* पूर्णांकerval between VN2VN beacons */
#घोषणा FIP_VN_BEACON_FUZZ 100	/* अक्रमom समय to add to beacon period (ms) */

/*
 * Multicast MAC addresses.  T11-aकरोpted.
 */
#घोषणा FIP_ALL_FCOE_MACS	((__u8[6]) अणु 1, 0x10, 0x18, 1, 0, 0 पूर्ण)
#घोषणा FIP_ALL_ENODE_MACS	((__u8[6]) अणु 1, 0x10, 0x18, 1, 0, 1 पूर्ण)
#घोषणा FIP_ALL_FCF_MACS	((__u8[6]) अणु 1, 0x10, 0x18, 1, 0, 2 पूर्ण)
#घोषणा FIP_ALL_VN2VN_MACS	((__u8[6]) अणु 1, 0x10, 0x18, 1, 0, 4 पूर्ण)
#घोषणा FIP_ALL_P2P_MACS	((__u8[6]) अणु 1, 0x10, 0x18, 1, 0, 5 पूर्ण)

#घोषणा FIP_VER		1		/* version क्रम fip_header */

काष्ठा fip_header अणु
	__u8	fip_ver;		/* upper 4 bits are the version */
	__u8	fip_resv1;		/* reserved */
	__be16	fip_op;			/* operation code */
	__u8	fip_resv2;		/* reserved */
	__u8	fip_subcode;		/* lower 4 bits are sub-code */
	__be16	fip_dl_len;		/* length of descriptors in words */
	__be16	fip_flags;		/* header flags */
पूर्ण __attribute__((packed));

#घोषणा FIP_VER_SHIFT	4
#घोषणा FIP_VER_ENCAPS(v) ((v) << FIP_VER_SHIFT)
#घोषणा FIP_VER_DECAPS(v) ((v) >> FIP_VER_SHIFT)
#घोषणा FIP_BPW		4		/* bytes per word क्रम lengths */

/*
 * fip_op.
 */
क्रमागत fip_opcode अणु
	FIP_OP_DISC =	1,		/* discovery, advertisement, etc. */
	FIP_OP_LS =	2,		/* Link Service request or reply */
	FIP_OP_CTRL =	3,		/* Keep Alive / Link Reset */
	FIP_OP_VLAN =	4,		/* VLAN discovery */
	FIP_OP_VN2VN =	5,		/* VN2VN operation */
	FIP_OP_VENDOR_MIN = 0xfff8,	/* min venकरोr-specअगरic opcode */
	FIP_OP_VENDOR_MAX = 0xfffe,	/* max venकरोr-specअगरic opcode */
पूर्ण;

/*
 * Subcodes क्रम FIP_OP_DISC.
 */
क्रमागत fip_disc_subcode अणु
	FIP_SC_SOL =	1,		/* solicitation */
	FIP_SC_ADV =	2,		/* advertisement */
पूर्ण;

/*
 * Subcodes क्रम FIP_OP_LS.
 */
क्रमागत fip_trans_subcode अणु
	FIP_SC_REQ =	1,		/* request */
	FIP_SC_REP =	2,		/* reply */
पूर्ण;

/*
 * Subcodes क्रम FIP_OP_RESET.
 */
क्रमागत fip_reset_subcode अणु
	FIP_SC_KEEP_ALIVE = 1,		/* keep-alive from VN_Port */
	FIP_SC_CLR_VLINK = 2,		/* clear भव link from VF_Port */
पूर्ण;

/*
 * Subcodes क्रम FIP_OP_VLAN.
 */
क्रमागत fip_vlan_subcode अणु
	FIP_SC_VL_REQ =	1,		/* vlan request */
	FIP_SC_VL_NOTE = 2,		/* vlan notअगरication */
	FIP_SC_VL_VN2VN_NOTE = 3,	/* VN2VN vlan notअगरication */
पूर्ण;

/*
 * Subcodes क्रम FIP_OP_VN2VN.
 */
क्रमागत fip_vn2vn_subcode अणु
	FIP_SC_VN_PROBE_REQ = 1,	/* probe request */
	FIP_SC_VN_PROBE_REP = 2,	/* probe reply */
	FIP_SC_VN_CLAIM_NOTIFY = 3,	/* claim notअगरication */
	FIP_SC_VN_CLAIM_REP = 4,	/* claim response */
	FIP_SC_VN_BEACON = 5,		/* beacon */
पूर्ण;

/*
 * flags in header fip_flags.
 */
क्रमागत fip_flag अणु
	FIP_FL_FPMA =	0x8000,		/* supports FPMA fabric-provided MACs */
	FIP_FL_SPMA =	0x4000,		/* supports SPMA server-provided MACs */
	FIP_FL_FCF =	0x0020,		/* originated from a controlling FCF */
	FIP_FL_FDF =	0x0010,		/* originated from an FDF */
	FIP_FL_REC_OR_P2P = 0x0008,	/* configured addr or poपूर्णांक-to-poपूर्णांक */
	FIP_FL_AVAIL =	0x0004,		/* available क्रम FLOGI/ELP */
	FIP_FL_SOL =	0x0002,		/* this is a solicited message */
	FIP_FL_FPORT =	0x0001,		/* sent from an F port */
पूर्ण;

/*
 * Common descriptor header क्रमmat.
 */
काष्ठा fip_desc अणु
	__u8	fip_dtype;		/* type - see below */
	__u8	fip_dlen;		/* length - in 32-bit words */
पूर्ण;

क्रमागत fip_desc_type अणु
	FIP_DT_PRI =	1,		/* priority क्रम क्रमwarder selection */
	FIP_DT_MAC =	2,		/* MAC address */
	FIP_DT_MAP_OUI = 3,		/* FC-MAP OUI */
	FIP_DT_NAME =	4,		/* चयन name or node name */
	FIP_DT_FAB =	5,		/* fabric descriptor */
	FIP_DT_FCOE_SIZE = 6,		/* max FCoE frame size */
	FIP_DT_FLOGI =	7,		/* FLOGI request or response */
	FIP_DT_FDISC =	8,		/* FDISC request or response */
	FIP_DT_LOGO =	9,		/* LOGO request or response */
	FIP_DT_ELP =	10,		/* ELP request or response */
	FIP_DT_VN_ID =	11,		/* VN_Node Identअगरier */
	FIP_DT_FKA =	12,		/* advertisement keep-alive period */
	FIP_DT_VENDOR =	13,		/* venकरोr ID */
	FIP_DT_VLAN =	14,		/* vlan number */
	FIP_DT_FC4F =	15,		/* FC-4 features */
	FIP_DT_LIMIT,			/* max defined desc_type + 1 */
	FIP_DT_NON_CRITICAL = 128,	/* First non-critical descriptor */
	FIP_DT_CLR_VLINKS = 128,	/* Clear भव links reason code */
	FIP_DT_VENDOR_BASE = 241,	/* first venकरोr-specअगरic desc_type */
पूर्ण;

/*
 * FIP_DT_PRI - priority descriptor.
 */
काष्ठा fip_pri_desc अणु
	काष्ठा fip_desc fd_desc;
	__u8		fd_resvd;
	__u8		fd_pri;		/* FCF priority:  higher is better */
पूर्ण __attribute__((packed));

/*
 * FIP_DT_MAC - MAC address descriptor.
 */
काष्ठा fip_mac_desc अणु
	काष्ठा fip_desc fd_desc;
	__u8		fd_mac[ETH_ALEN];
पूर्ण __attribute__((packed));

/*
 * FIP_DT_MAP - descriptor.
 */
काष्ठा fip_map_desc अणु
	काष्ठा fip_desc fd_desc;
	__u8		fd_resvd[3];
	__u8		fd_map[3];
पूर्ण __attribute__((packed));

/*
 * FIP_DT_NAME descriptor.
 */
काष्ठा fip_wwn_desc अणु
	काष्ठा fip_desc fd_desc;
	__u8		fd_resvd[2];
	__be64		fd_wwn;		/* 64-bit WWN, unaligned */
पूर्ण __attribute__((packed));

/*
 * FIP_DT_FAB descriptor.
 */
काष्ठा fip_fab_desc अणु
	काष्ठा fip_desc fd_desc;
	__be16		fd_vfid;	/* भव fabric ID */
	__u8		fd_resvd;
	__u8		fd_map[3];	/* FC-MAP value */
	__be64		fd_wwn;		/* fabric name, unaligned */
पूर्ण __attribute__((packed));

/*
 * FIP_DT_FCOE_SIZE descriptor.
 */
काष्ठा fip_size_desc अणु
	काष्ठा fip_desc fd_desc;
	__be16		fd_size;
पूर्ण __attribute__((packed));

/*
 * Descriptor that encapsulates an ELS or ILS frame.
 * The encapsulated frame immediately follows this header, without
 * SOF, खातापूर्ण, or CRC.
 */
काष्ठा fip_encaps अणु
	काष्ठा fip_desc fd_desc;
	__u8		fd_resvd[2];
पूर्ण __attribute__((packed));

/*
 * FIP_DT_VN_ID - VN_Node Identअगरier descriptor.
 */
काष्ठा fip_vn_desc अणु
	काष्ठा fip_desc fd_desc;
	__u8		fd_mac[ETH_ALEN];
	__u8		fd_resvd;
	__u8		fd_fc_id[3];
	__be64		fd_wwpn;	/* port name, unaligned */
पूर्ण __attribute__((packed));

/*
 * FIP_DT_FKA - Advertisement keep-alive period.
 */
काष्ठा fip_fka_desc अणु
	काष्ठा fip_desc fd_desc;
	__u8		fd_resvd;
	__u8		fd_flags;	/* bit0 is fka disable flag */
	__be32		fd_fka_period;	/* adv./keep-alive period in mS */
पूर्ण __attribute__((packed));

/*
 * flags क्रम fip_fka_desc.fd_flags
 */
क्रमागत fip_fka_flags अणु
	FIP_FKA_ADV_D =	0x01,		/* no need क्रम FKA from ENode */
पूर्ण;

/* FIP_DT_FKA flags */

/*
 * FIP_DT_VLAN descriptor
 */
काष्ठा fip_vlan_desc अणु
	काष्ठा fip_desc fd_desc;
	__be16		fd_vlan; /* Note: highest 4 bytes are unused */
पूर्ण __attribute__((packed));

/*
 * FIP_DT_FC4F - FC-4 features.
 */
काष्ठा fip_fc4_feat अणु
	काष्ठा fip_desc fd_desc;
	__u8		fd_resvd[2];
	काष्ठा fc_ns_fts fd_fts;
	काष्ठा fc_ns_ff	fd_ff;
पूर्ण __attribute__((packed));

/*
 * FIP_DT_VENDOR descriptor.
 */
काष्ठा fip_venकरोr_desc अणु
	काष्ठा fip_desc fd_desc;
	__u8		fd_resvd[2];
	__u8		fd_venकरोr_id[8];
पूर्ण __attribute__((packed));

#पूर्ण_अगर /* _FC_FIP_H_ */
