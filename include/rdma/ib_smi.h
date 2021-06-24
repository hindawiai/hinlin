<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2004 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2004 Infinicon Corporation.  All rights reserved.
 * Copyright (c) 2004 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004 Voltaire Corporation.  All rights reserved.
 */

#अगर_अघोषित IB_SMI_H
#घोषणा IB_SMI_H

#समावेश <rdma/ib_mad.h>

#घोषणा IB_SMP_DATA_SIZE			64
#घोषणा IB_SMP_MAX_PATH_HOPS			64

काष्ठा ib_smp अणु
	u8	base_version;
	u8	mgmt_class;
	u8	class_version;
	u8	method;
	__be16	status;
	u8	hop_ptr;
	u8	hop_cnt;
	__be64	tid;
	__be16	attr_id;
	__be16	resv;
	__be32	attr_mod;
	__be64	mkey;
	__be16	dr_slid;
	__be16	dr_dlid;
	u8	reserved[28];
	u8	data[IB_SMP_DATA_SIZE];
	u8	initial_path[IB_SMP_MAX_PATH_HOPS];
	u8	वापस_path[IB_SMP_MAX_PATH_HOPS];
पूर्ण __packed;

#घोषणा IB_SMP_सूचीECTION			cpu_to_be16(0x8000)

/* Subnet management attributes */
#घोषणा IB_SMP_ATTR_NOTICE			cpu_to_be16(0x0002)
#घोषणा IB_SMP_ATTR_NODE_DESC			cpu_to_be16(0x0010)
#घोषणा IB_SMP_ATTR_NODE_INFO			cpu_to_be16(0x0011)
#घोषणा IB_SMP_ATTR_SWITCH_INFO			cpu_to_be16(0x0012)
#घोषणा IB_SMP_ATTR_GUID_INFO			cpu_to_be16(0x0014)
#घोषणा IB_SMP_ATTR_PORT_INFO			cpu_to_be16(0x0015)
#घोषणा IB_SMP_ATTR_PKEY_TABLE			cpu_to_be16(0x0016)
#घोषणा IB_SMP_ATTR_SL_TO_VL_TABLE		cpu_to_be16(0x0017)
#घोषणा IB_SMP_ATTR_VL_ARB_TABLE		cpu_to_be16(0x0018)
#घोषणा IB_SMP_ATTR_LINEAR_FORWARD_TABLE	cpu_to_be16(0x0019)
#घोषणा IB_SMP_ATTR_RANDOM_FORWARD_TABLE	cpu_to_be16(0x001A)
#घोषणा IB_SMP_ATTR_MCAST_FORWARD_TABLE		cpu_to_be16(0x001B)
#घोषणा IB_SMP_ATTR_SM_INFO			cpu_to_be16(0x0020)
#घोषणा IB_SMP_ATTR_VENDOR_DIAG			cpu_to_be16(0x0030)
#घोषणा IB_SMP_ATTR_LED_INFO			cpu_to_be16(0x0031)
#घोषणा IB_SMP_ATTR_VENDOR_MASK			cpu_to_be16(0xFF00)

काष्ठा ib_port_info अणु
	__be64 mkey;
	__be64 gid_prefix;
	__be16 lid;
	__be16 sm_lid;
	__be32 cap_mask;
	__be16 diag_code;
	__be16 mkey_lease_period;
	u8 local_port_num;
	u8 link_width_enabled;
	u8 link_width_supported;
	u8 link_width_active;
	u8 linkspeed_portstate;			/* 4 bits, 4 bits */
	u8 portphysstate_linkकरोwn;		/* 4 bits, 4 bits */
	u8 mkeyprot_resv_lmc;			/* 2 bits, 3, 3 */
	u8 linkspeedactive_enabled;		/* 4 bits, 4 bits */
	u8 neighbormtu_mastersmsl;		/* 4 bits, 4 bits */
	u8 vlcap_inittype;			/* 4 bits, 4 bits */
	u8 vl_high_limit;
	u8 vl_arb_high_cap;
	u8 vl_arb_low_cap;
	u8 inittypereply_mtucap;		/* 4 bits, 4 bits */
	u8 vlstallcnt_hoqlअगरe;			/* 3 bits, 5 bits */
	u8 operationalvl_pei_peo_fpi_fpo;	/* 4 bits, 1, 1, 1, 1 */
	__be16 mkey_violations;
	__be16 pkey_violations;
	__be16 qkey_violations;
	u8 guid_cap;
	u8 clientrereg_resv_subnetto;		/* 1 bit, 2 bits, 5 */
	u8 resv_respसमयvalue;			/* 3 bits, 5 bits */
	u8 localphyerrors_overrunerrors;	/* 4 bits, 4 bits */
	__be16 max_credit_hपूर्णांक;
	u8 resv;
	u8 link_roundtrip_latency[3];
पूर्ण;

काष्ठा ib_node_info अणु
	u8 base_version;
	u8 class_version;
	u8 node_type;
	u8 num_ports;
	__be64 sys_guid;
	__be64 node_guid;
	__be64 port_guid;
	__be16 partition_cap;
	__be16 device_id;
	__be32 revision;
	u8 local_port_num;
	u8 venकरोr_id[3];
पूर्ण __packed;

काष्ठा ib_vl_weight_elem अणु
	u8      vl;     /* IB: VL is low 4 bits, upper 4 bits reserved */
                        /* OPA: VL is low 5 bits, upper 3 bits reserved */
	u8      weight;
पूर्ण;

अटल अंतरभूत u8
ib_get_smp_direction(काष्ठा ib_smp *smp)
अणु
	वापस ((smp->status & IB_SMP_सूचीECTION) == IB_SMP_सूचीECTION);
पूर्ण

/*
 * SM Trap/Notice numbers
 */
#घोषणा IB_NOTICE_TRAP_LLI_THRESH	cpu_to_be16(129)
#घोषणा IB_NOTICE_TRAP_EBO_THRESH	cpu_to_be16(130)
#घोषणा IB_NOTICE_TRAP_FLOW_UPDATE	cpu_to_be16(131)
#घोषणा IB_NOTICE_TRAP_CAP_MASK_CHG	cpu_to_be16(144)
#घोषणा IB_NOTICE_TRAP_SYS_GUID_CHG	cpu_to_be16(145)
#घोषणा IB_NOTICE_TRAP_BAD_MKEY		cpu_to_be16(256)
#घोषणा IB_NOTICE_TRAP_BAD_PKEY		cpu_to_be16(257)
#घोषणा IB_NOTICE_TRAP_BAD_QKEY		cpu_to_be16(258)

/*
 * Other local changes flags (trap 144).
 */
#घोषणा IB_NOTICE_TRAP_LSE_CHG		0x04	/* Link Speed Enable changed */
#घोषणा IB_NOTICE_TRAP_LWE_CHG		0x02	/* Link Width Enable changed */
#घोषणा IB_NOTICE_TRAP_NODE_DESC_CHG	0x01

/*
 * M_Key volation flags in dr_trunc_hop (trap 256).
 */
#घोषणा IB_NOTICE_TRAP_DR_NOTICE	0x80
#घोषणा IB_NOTICE_TRAP_DR_TRUNC		0x40


#पूर्ण_अगर /* IB_SMI_H */
