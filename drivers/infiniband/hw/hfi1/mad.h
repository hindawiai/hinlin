<शैली गुरु>
/*
 * Copyright(c) 2015 - 2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#अगर_अघोषित _HFI1_MAD_H
#घोषणा _HFI1_MAD_H

#समावेश <rdma/ib_pma.h>
#समावेश <rdma/opa_smi.h>
#समावेश <rdma/opa_port_info.h>
#समावेश "opa_compat.h"

/*
 * OPA Traps
 */
#घोषणा OPA_TRAP_GID_NOW_IN_SERVICE             cpu_to_be16(64)
#घोषणा OPA_TRAP_GID_OUT_OF_SERVICE             cpu_to_be16(65)
#घोषणा OPA_TRAP_ADD_MULTICAST_GROUP            cpu_to_be16(66)
#घोषणा OPA_TRAL_DEL_MULTICAST_GROUP            cpu_to_be16(67)
#घोषणा OPA_TRAP_UNPATH                         cpu_to_be16(68)
#घोषणा OPA_TRAP_REPATH                         cpu_to_be16(69)
#घोषणा OPA_TRAP_PORT_CHANGE_STATE              cpu_to_be16(128)
#घोषणा OPA_TRAP_LINK_INTEGRITY                 cpu_to_be16(129)
#घोषणा OPA_TRAP_EXCESSIVE_BUFFER_OVERRUN       cpu_to_be16(130)
#घोषणा OPA_TRAP_FLOW_WATCHDOG                  cpu_to_be16(131)
#घोषणा OPA_TRAP_CHANGE_CAPABILITY              cpu_to_be16(144)
#घोषणा OPA_TRAP_CHANGE_SYSGUID                 cpu_to_be16(145)
#घोषणा OPA_TRAP_BAD_M_KEY                      cpu_to_be16(256)
#घोषणा OPA_TRAP_BAD_P_KEY                      cpu_to_be16(257)
#घोषणा OPA_TRAP_BAD_Q_KEY                      cpu_to_be16(258)
#घोषणा OPA_TRAP_SWITCH_BAD_PKEY                cpu_to_be16(259)
#घोषणा OPA_SMA_TRAP_DATA_LINK_WIDTH            cpu_to_be16(2048)

/*
 * Generic trap/notice other local changes flags (trap 144).
 */
#घोषणा	OPA_NOTICE_TRAP_LWDE_CHG        0x08 /* Link Width Downgrade Enable
					      * changed
					      */
#घोषणा OPA_NOTICE_TRAP_LSE_CHG         0x04 /* Link Speed Enable changed */
#घोषणा OPA_NOTICE_TRAP_LWE_CHG         0x02 /* Link Width Enable changed */
#घोषणा OPA_NOTICE_TRAP_NODE_DESC_CHG   0x01

काष्ठा opa_mad_notice_attr अणु
	u8 generic_type;
	u8 prod_type_msb;
	__be16 prod_type_lsb;
	__be16 trap_num;
	__be16 toggle_count;
	__be32 issuer_lid;
	__be32 reserved1;
	जोड़ ib_gid issuer_gid;

	जोड़ अणु
		काष्ठा अणु
			u8	details[64];
		पूर्ण raw_data;

		काष्ठा अणु
			जोड़ ib_gid	gid;
		पूर्ण __packed ntc_64_65_66_67;

		काष्ठा अणु
			__be32	lid;
		पूर्ण __packed ntc_128;

		काष्ठा अणु
			__be32	lid;		/* where violation happened */
			u8	port_num;	/* where violation happened */
		पूर्ण __packed ntc_129_130_131;

		काष्ठा अणु
			__be32	lid;		/* LID where change occurred */
			__be32	new_cap_mask;	/* new capability mask */
			__be16	reserved2;
			__be16	cap_mask3;
			__be16	change_flags;	/* low 4 bits only */
		पूर्ण __packed ntc_144;

		काष्ठा अणु
			__be64	new_sys_guid;
			__be32	lid;		/* lid where sys guid changed */
		पूर्ण __packed ntc_145;

		काष्ठा अणु
			__be32	lid;
			__be32	dr_slid;
			u8	method;
			u8	dr_trunc_hop;
			__be16	attr_id;
			__be32	attr_mod;
			__be64	mkey;
			u8	dr_rtn_path[30];
		पूर्ण __packed ntc_256;

		काष्ठा अणु
			__be32		lid1;
			__be32		lid2;
			__be32		key;
			u8		sl;	/* SL: high 5 bits */
			u8		reserved3[3];
			जोड़ ib_gid	gid1;
			जोड़ ib_gid	gid2;
			__be32		qp1;	/* high 8 bits reserved */
			__be32		qp2;	/* high 8 bits reserved */
		पूर्ण __packed ntc_257_258;

		काष्ठा अणु
			__be16		flags;	/* low 8 bits reserved */
			__be16		pkey;
			__be32		lid1;
			__be32		lid2;
			u8		sl;	/* SL: high 5 bits */
			u8		reserved4[3];
			जोड़ ib_gid	gid1;
			जोड़ ib_gid	gid2;
			__be32		qp1;	/* high 8 bits reserved */
			__be32		qp2;	/* high 8 bits reserved */
		पूर्ण __packed ntc_259;

		काष्ठा अणु
			__be32	lid;
		पूर्ण __packed ntc_2048;

	पूर्ण;
	u8	class_data[];
पूर्ण;

#घोषणा IB_VLARB_LOWPRI_0_31    1
#घोषणा IB_VLARB_LOWPRI_32_63   2
#घोषणा IB_VLARB_HIGHPRI_0_31   3
#घोषणा IB_VLARB_HIGHPRI_32_63  4

#घोषणा OPA_MAX_PREEMPT_CAP         32
#घोषणा OPA_VLARB_LOW_ELEMENTS       0
#घोषणा OPA_VLARB_HIGH_ELEMENTS      1
#घोषणा OPA_VLARB_PREEMPT_ELEMENTS   2
#घोषणा OPA_VLARB_PREEMPT_MATRIX     3

#घोषणा IB_PMA_PORT_COUNTERS_CONG       cpu_to_be16(0xFF00)
#घोषणा LINK_SPEED_25G		1
#घोषणा LINK_SPEED_12_5G	2
#घोषणा LINK_WIDTH_DEFAULT	4
#घोषणा DECIMAL_FACTORING	1000
/*
 * The शेष link width is multiplied by 1000
 * to get accurate value after भागision.
 */
#घोषणा FACTOR_LINK_WIDTH	(LINK_WIDTH_DEFAULT * DECIMAL_FACTORING)

काष्ठा ib_pma_portcounters_cong अणु
	u8 reserved;
	u8 reserved1;
	__be16 port_check_rate;
	__be16 symbol_error_counter;
	u8 link_error_recovery_counter;
	u8 link_करोwned_counter;
	__be16 port_rcv_errors;
	__be16 port_rcv_remphys_errors;
	__be16 port_rcv_चयन_relay_errors;
	__be16 port_xmit_discards;
	u8 port_xmit_स्थिरraपूर्णांक_errors;
	u8 port_rcv_स्थिरraपूर्णांक_errors;
	u8 reserved2;
	u8 link_overrun_errors; /* LocalLink: 7:4, BufferOverrun: 3:0 */
	__be16 reserved3;
	__be16 vl15_dropped;
	__be64 port_xmit_data;
	__be64 port_rcv_data;
	__be64 port_xmit_packets;
	__be64 port_rcv_packets;
	__be64 port_xmit_रुको;
	__be64 port_adr_events;
पूर्ण __packed;

#घोषणा IB_SMP_UNSUP_VERSION    cpu_to_be16(0x0004)
#घोषणा IB_SMP_UNSUP_METHOD     cpu_to_be16(0x0008)
#घोषणा IB_SMP_UNSUP_METH_ATTR  cpu_to_be16(0x000C)
#घोषणा IB_SMP_INVALID_FIELD    cpu_to_be16(0x001C)

#घोषणा OPA_MAX_PREEMPT_CAP         32
#घोषणा OPA_VLARB_LOW_ELEMENTS       0
#घोषणा OPA_VLARB_HIGH_ELEMENTS      1
#घोषणा OPA_VLARB_PREEMPT_ELEMENTS   2
#घोषणा OPA_VLARB_PREEMPT_MATRIX     3

#घोषणा HFI1_XMIT_RATE_UNSUPPORTED               0x0
#घोषणा HFI1_XMIT_RATE_PICO                      0x7
/* number of 4nsec cycles equaling 2secs */
#घोषणा HFI1_CONG_TIMER_PSINTERVAL               0x1DCD64EC

#घोषणा IB_CC_SVCTYPE_RC 0x0
#घोषणा IB_CC_SVCTYPE_UC 0x1
#घोषणा IB_CC_SVCTYPE_RD 0x2
#घोषणा IB_CC_SVCTYPE_UD 0x3

/*
 * There should be an equivalent IB #घोषणा क्रम the following, but
 * I cannot find it.
 */
#घोषणा OPA_CC_LOG_TYPE_HFI	2

काष्ठा opa_hfi1_cong_log_event_पूर्णांकernal अणु
	u32 lqpn;
	u32 rqpn;
	u8 sl;
	u8 svc_type;
	u32 rlid;
	u64 बारtamp; /* wider than 32 bits to detect 32 bit rollover */
पूर्ण;

काष्ठा opa_hfi1_cong_log_event अणु
	u8 local_qp_cn_entry[3];
	u8 remote_qp_number_cn_entry[3];
	u8 sl_svc_type_cn_entry; /* 5 bits SL, 3 bits svc type */
	u8 reserved;
	__be32 remote_lid_cn_entry;
	__be32 बारtamp_cn_entry;
पूर्ण __packed;

#घोषणा OPA_CONG_LOG_ELEMS	96

काष्ठा opa_hfi1_cong_log अणु
	u8 log_type;
	u8 congestion_flags;
	__be16 threshold_event_counter;
	__be32 current_समय_stamp;
	u8 threshold_cong_event_map[OPA_MAX_SLS / 8];
	काष्ठा opa_hfi1_cong_log_event events[OPA_CONG_LOG_ELEMS];
पूर्ण __packed;

#घोषणा IB_CC_TABLE_CAP_DEFAULT 31

/* Port control flags */
#घोषणा IB_CC_CCS_PC_SL_BASED 0x01

काष्ठा opa_congestion_setting_entry अणु
	u8 ccti_increase;
	u8 reserved;
	__be16 ccti_समयr;
	u8 trigger_threshold;
	u8 ccti_min; /* min CCTI क्रम cc table */
पूर्ण __packed;

काष्ठा opa_congestion_setting_entry_shaकरोw अणु
	u8 ccti_increase;
	u8 reserved;
	u16 ccti_समयr;
	u8 trigger_threshold;
	u8 ccti_min; /* min CCTI क्रम cc table */
पूर्ण __packed;

काष्ठा opa_congestion_setting_attr अणु
	__be32 control_map;
	__be16 port_control;
	काष्ठा opa_congestion_setting_entry entries[OPA_MAX_SLS];
पूर्ण __packed;

काष्ठा opa_congestion_setting_attr_shaकरोw अणु
	u32 control_map;
	u16 port_control;
	काष्ठा opa_congestion_setting_entry_shaकरोw entries[OPA_MAX_SLS];
पूर्ण __packed;

#घोषणा IB_CC_TABLE_ENTRY_INCREASE_DEFAULT 1
#घोषणा IB_CC_TABLE_ENTRY_TIMER_DEFAULT 1

/* 64 Congestion Control table entries in a single MAD */
#घोषणा IB_CCT_ENTRIES 64
#घोषणा IB_CCT_MIN_ENTRIES (IB_CCT_ENTRIES * 2)

काष्ठा ib_cc_table_entry अणु
	__be16 entry; /* shअगरt:2, multiplier:14 */
पूर्ण;

काष्ठा ib_cc_table_entry_shaकरोw अणु
	u16 entry; /* shअगरt:2, multiplier:14 */
पूर्ण;

काष्ठा ib_cc_table_attr अणु
	__be16 ccti_limit; /* max CCTI क्रम cc table */
	काष्ठा ib_cc_table_entry ccti_entries[IB_CCT_ENTRIES];
पूर्ण __packed;

काष्ठा ib_cc_table_attr_shaकरोw अणु
	u16 ccti_limit; /* max CCTI क्रम cc table */
	काष्ठा ib_cc_table_entry_shaकरोw ccti_entries[IB_CCT_ENTRIES];
पूर्ण __packed;

#घोषणा CC_TABLE_SHADOW_MAX \
	(IB_CC_TABLE_CAP_DEFAULT * IB_CCT_ENTRIES)

काष्ठा cc_table_shaकरोw अणु
	u16 ccti_limit; /* max CCTI क्रम cc table */
	काष्ठा ib_cc_table_entry_shaकरोw entries[CC_TABLE_SHADOW_MAX];
पूर्ण __packed;

/*
 * काष्ठा cc_state combines the (active) per-port congestion control
 * table, and the (active) per-SL congestion settings. cc_state data
 * may need to be पढ़ो in code paths that we want to be fast, so it
 * is an RCU रक्षित काष्ठाure.
 */
काष्ठा cc_state अणु
	काष्ठा rcu_head rcu;
	काष्ठा cc_table_shaकरोw cct;
	काष्ठा opa_congestion_setting_attr_shaकरोw cong_setting;
पूर्ण;

/*
 * OPA BufferControl MAD
 */

/* attribute modअगरier macros */
#घोषणा OPA_AM_NPORT_SHIFT	24
#घोषणा OPA_AM_NPORT_MASK	0xff
#घोषणा OPA_AM_NPORT_SMASK	(OPA_AM_NPORT_MASK << OPA_AM_NPORT_SHIFT)
#घोषणा OPA_AM_NPORT(am)	(((am) >> OPA_AM_NPORT_SHIFT) & \
					OPA_AM_NPORT_MASK)

#घोषणा OPA_AM_NBLK_SHIFT	24
#घोषणा OPA_AM_NBLK_MASK	0xff
#घोषणा OPA_AM_NBLK_SMASK	(OPA_AM_NBLK_MASK << OPA_AM_NBLK_SHIFT)
#घोषणा OPA_AM_NBLK(am)		(((am) >> OPA_AM_NBLK_SHIFT) & \
					OPA_AM_NBLK_MASK)

#घोषणा OPA_AM_START_BLK_SHIFT	0
#घोषणा OPA_AM_START_BLK_MASK	0xff
#घोषणा OPA_AM_START_BLK_SMASK	(OPA_AM_START_BLK_MASK << \
					OPA_AM_START_BLK_SHIFT)
#घोषणा OPA_AM_START_BLK(am)	(((am) >> OPA_AM_START_BLK_SHIFT) & \
					OPA_AM_START_BLK_MASK)

#घोषणा OPA_AM_PORTNUM_SHIFT	0
#घोषणा OPA_AM_PORTNUM_MASK	0xff
#घोषणा OPA_AM_PORTNUM_SMASK	(OPA_AM_PORTNUM_MASK << OPA_AM_PORTNUM_SHIFT)
#घोषणा OPA_AM_PORTNUM(am)	(((am) >> OPA_AM_PORTNUM_SHIFT) & \
					OPA_AM_PORTNUM_MASK)

#घोषणा OPA_AM_ASYNC_SHIFT	12
#घोषणा OPA_AM_ASYNC_MASK	0x1
#घोषणा OPA_AM_ASYNC_SMASK	(OPA_AM_ASYNC_MASK << OPA_AM_ASYNC_SHIFT)
#घोषणा OPA_AM_ASYNC(am)	(((am) >> OPA_AM_ASYNC_SHIFT) & \
					OPA_AM_ASYNC_MASK)

#घोषणा OPA_AM_START_SM_CFG_SHIFT	9
#घोषणा OPA_AM_START_SM_CFG_MASK	0x1
#घोषणा OPA_AM_START_SM_CFG_SMASK	(OPA_AM_START_SM_CFG_MASK << \
						OPA_AM_START_SM_CFG_SHIFT)
#घोषणा OPA_AM_START_SM_CFG(am)		(((am) >> OPA_AM_START_SM_CFG_SHIFT) \
						& OPA_AM_START_SM_CFG_MASK)

#घोषणा OPA_AM_CI_ADDR_SHIFT	19
#घोषणा OPA_AM_CI_ADDR_MASK	0xfff
#घोषणा OPA_AM_CI_ADDR_SMASK	(OPA_AM_CI_ADDR_MASK << OPA_CI_ADDR_SHIFT)
#घोषणा OPA_AM_CI_ADDR(am)	(((am) >> OPA_AM_CI_ADDR_SHIFT) & \
					OPA_AM_CI_ADDR_MASK)

#घोषणा OPA_AM_CI_LEN_SHIFT	13
#घोषणा OPA_AM_CI_LEN_MASK	0x3f
#घोषणा OPA_AM_CI_LEN_SMASK	(OPA_AM_CI_LEN_MASK << OPA_CI_LEN_SHIFT)
#घोषणा OPA_AM_CI_LEN(am)	(((am) >> OPA_AM_CI_LEN_SHIFT) & \
					OPA_AM_CI_LEN_MASK)

/* error info macros */
#घोषणा OPA_EI_STATUS_SMASK	0x80
#घोषणा OPA_EI_CODE_SMASK	0x0f

काष्ठा vl_limit अणु
	__be16 dedicated;
	__be16 shared;
पूर्ण;

काष्ठा buffer_control अणु
	__be16 reserved;
	__be16 overall_shared_limit;
	काष्ठा vl_limit vl[OPA_MAX_VLS];
पूर्ण;

काष्ठा sc2vlnt अणु
	u8 vlnt[32]; /* 5 bit VL, 3 bits reserved */
पूर्ण;

/*
 * The PortSamplesControl.CounterMasks field is an array of 3 bit fields
 * which specअगरy the N'th counter's capabilities. See ch. 16.1.3.2.
 * We support 5 counters which only count the mandatory quantities.
 */
#घोषणा COUNTER_MASK(q, n) (q << ((9 - n) * 3))
#घोषणा COUNTER_MASK0_9 \
	cpu_to_be32(COUNTER_MASK(1, 0) | \
		    COUNTER_MASK(1, 1) | \
		    COUNTER_MASK(1, 2) | \
		    COUNTER_MASK(1, 3) | \
		    COUNTER_MASK(1, 4))

व्योम hfi1_event_pkey_change(काष्ठा hfi1_devdata *dd, u32 port);
व्योम hfi1_handle_trap_समयr(काष्ठा समयr_list *t);
u16 tx_link_width(u16 link_width);
u64 get_xmit_रुको_counters(काष्ठा hfi1_pportdata *ppd, u16 link_width,
			   u16 link_speed, पूर्णांक vl);
/**
 * get_link_speed - determine whether 12.5G or 25G speed
 * @link_speed: the speed of active link
 * @वापस: Return 2 अगर link speed identअगरied as 12.5G
 * or वापस 1 अगर link speed is 25G.
 *
 * The function indirectly calculate required link speed
 * value क्रम convert_xmit_counter function. If the link
 * speed is 25G, the function वापस as 1 as it is required
 * by xmit counter conversion क्रमmula :-( 25G / link_speed).
 * This conversion will provide value 1 अगर current
 * link speed is 25G or 2 अगर 12.5G.This is करोne to aव्योम
 * 12.5 भग्न number conversion.
 */
अटल अंतरभूत u16 get_link_speed(u16 link_speed)
अणु
	वापस (link_speed == 1) ?
		 LINK_SPEED_12_5G : LINK_SPEED_25G;
पूर्ण

/**
 * convert_xmit_counter - calculate flit बार क्रम given xmit counter
 * value
 * @xmit_रुको_val: current xmit counter value
 * @link_width: width of active link
 * @link_speed: speed of active link
 * @वापस: वापस xmit counter value in flit बार.
 */
अटल अंतरभूत u64 convert_xmit_counter(u64 xmit_रुको_val, u16 link_width,
				       u16 link_speed)
अणु
	वापस (xmit_रुको_val * 2 * (FACTOR_LINK_WIDTH / link_width)
		 * link_speed) / DECIMAL_FACTORING;
पूर्ण
#पूर्ण_अगर				/* _HFI1_MAD_H */
