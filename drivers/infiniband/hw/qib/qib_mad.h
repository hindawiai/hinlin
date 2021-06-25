<शैली गुरु>
/*
 * Copyright (c) 2012 Intel Corporation.  All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2005, 2006 PathScale, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#अगर_अघोषित _QIB_MAD_H
#घोषणा _QIB_MAD_H

#समावेश <rdma/ib_pma.h>

#घोषणा IB_SMP_UNSUP_VERSION \
cpu_to_be16(IB_MGMT_MAD_STATUS_BAD_VERSION)

#घोषणा IB_SMP_UNSUP_METHOD \
cpu_to_be16(IB_MGMT_MAD_STATUS_UNSUPPORTED_METHOD)

#घोषणा IB_SMP_UNSUP_METH_ATTR \
cpu_to_be16(IB_MGMT_MAD_STATUS_UNSUPPORTED_METHOD_ATTRIB)

#घोषणा IB_SMP_INVALID_FIELD \
cpu_to_be16(IB_MGMT_MAD_STATUS_INVALID_ATTRIB_VALUE)

#घोषणा IB_VLARB_LOWPRI_0_31    1
#घोषणा IB_VLARB_LOWPRI_32_63   2
#घोषणा IB_VLARB_HIGHPRI_0_31   3
#घोषणा IB_VLARB_HIGHPRI_32_63  4

#घोषणा IB_PMA_PORT_COUNTERS_CONG       cpu_to_be16(0xFF00)

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

#घोषणा IB_PMA_CONG_HW_CONTROL_TIMER            0x00
#घोषणा IB_PMA_CONG_HW_CONTROL_SAMPLE           0x01

#घोषणा QIB_XMIT_RATE_UNSUPPORTED               0x0
#घोषणा QIB_XMIT_RATE_PICO                      0x7
/* number of 4nsec cycles equaling 2secs */
#घोषणा QIB_CONG_TIMER_PSINTERVAL               0x1DCD64EC

#घोषणा IB_PMA_SEL_CONG_ALL                     0x01
#घोषणा IB_PMA_SEL_CONG_PORT_DATA               0x02
#घोषणा IB_PMA_SEL_CONG_XMIT                    0x04
#घोषणा IB_PMA_SEL_CONG_ROUTING                 0x08

/*
 * Congestion control class attributes
 */
#घोषणा IB_CC_ATTR_CLASSPORTINFO			cpu_to_be16(0x0001)
#घोषणा IB_CC_ATTR_NOTICE				cpu_to_be16(0x0002)
#घोषणा IB_CC_ATTR_CONGESTION_INFO			cpu_to_be16(0x0011)
#घोषणा IB_CC_ATTR_CONGESTION_KEY_INFO			cpu_to_be16(0x0012)
#घोषणा IB_CC_ATTR_CONGESTION_LOG			cpu_to_be16(0x0013)
#घोषणा IB_CC_ATTR_SWITCH_CONGESTION_SETTING		cpu_to_be16(0x0014)
#घोषणा IB_CC_ATTR_SWITCH_PORT_CONGESTION_SETTING	cpu_to_be16(0x0015)
#घोषणा IB_CC_ATTR_CA_CONGESTION_SETTING		cpu_to_be16(0x0016)
#घोषणा IB_CC_ATTR_CONGESTION_CONTROL_TABLE		cpu_to_be16(0x0017)
#घोषणा IB_CC_ATTR_TIME_STAMP				cpu_to_be16(0x0018)

/* generalizations क्रम threshold values */
#घोषणा IB_CC_THRESHOLD_NONE 0x0
#घोषणा IB_CC_THRESHOLD_MIN  0x1
#घोषणा IB_CC_THRESHOLD_MAX  0xf

/* CCA MAD header स्थिरants */
#घोषणा IB_CC_MAD_LOGDATA_LEN 32
#घोषणा IB_CC_MAD_MGMTDATA_LEN 192

काष्ठा ib_cc_mad अणु
	u8	base_version;
	u8	mgmt_class;
	u8	class_version;
	u8	method;
	__be16	status;
	__be16	class_specअगरic;
	__be64	tid;
	__be16	attr_id;
	__be16	resv;
	__be32	attr_mod;
	__be64 cckey;

	/* For CongestionLog attribute only */
	u8 log_data[IB_CC_MAD_LOGDATA_LEN];

	u8 mgmt_data[IB_CC_MAD_MGMTDATA_LEN];
पूर्ण __packed;

/*
 * Congestion Control class portinfo capability mask bits
 */
#घोषणा IB_CC_CPI_CM_TRAP_GEN		cpu_to_be16(1 << 0)
#घोषणा IB_CC_CPI_CM_GET_SET_NOTICE	cpu_to_be16(1 << 1)
#घोषणा IB_CC_CPI_CM_CAP2		cpu_to_be16(1 << 2)
#घोषणा IB_CC_CPI_CM_ENHANCEDPORT0_CC	cpu_to_be16(1 << 8)

काष्ठा ib_cc_classportinfo_attr अणु
	u8 base_version;
	u8 class_version;
	__be16 cap_mask;
	u8 reserved[3];
	u8 resp_समय_value;     /* only lower 5 bits */
	जोड़ ib_gid redirect_gid;
	__be32 redirect_tc_sl_fl;       /* 8, 4, 20 bits respectively */
	__be16 redirect_lid;
	__be16 redirect_pkey;
	__be32 redirect_qp;     /* only lower 24 bits */
	__be32 redirect_qkey;
	जोड़ ib_gid trap_gid;
	__be32 trap_tc_sl_fl;   /* 8, 4, 20 bits respectively */
	__be16 trap_lid;
	__be16 trap_pkey;
	__be32 trap_hl_qp;      /* 8, 24 bits respectively */
	__be32 trap_qkey;
पूर्ण __packed;

/* Congestion control traps */
#घोषणा IB_CC_TRAP_KEY_VIOLATION 0x0000

काष्ठा ib_cc_trap_key_violation_attr अणु
	__be16 source_lid;
	u8 method;
	u8 reserved1;
	__be16 attrib_id;
	__be32 attrib_mod;
	__be32 qp;
	__be64 cckey;
	u8 sgid[16];
	u8 padding[24];
पूर्ण __packed;

/* Congestion info flags */
#घोषणा IB_CC_CI_FLAGS_CREDIT_STARVATION 0x1
#घोषणा IB_CC_TABLE_CAP_DEFAULT 31

काष्ठा ib_cc_info_attr अणु
	__be16 congestion_info;
	u8  control_table_cap; /* Multiple of 64 entry unit CCTs */
पूर्ण __packed;

काष्ठा ib_cc_key_info_attr अणु
	__be64 cckey;
	u8  protect;
	__be16 lease_period;
	__be16 violations;
पूर्ण __packed;

#घोषणा IB_CC_CL_CA_LOGEVENTS_LEN 208

काष्ठा ib_cc_log_attr अणु
	u8 log_type;
	u8 congestion_flags;
	__be16 threshold_event_counter;
	__be16 threshold_congestion_event_map;
	__be16 current_समय_stamp;
	u8 log_events[IB_CC_CL_CA_LOGEVENTS_LEN];
पूर्ण __packed;

#घोषणा IB_CC_CLEC_SERVICETYPE_RC 0x0
#घोषणा IB_CC_CLEC_SERVICETYPE_UC 0x1
#घोषणा IB_CC_CLEC_SERVICETYPE_RD 0x2
#घोषणा IB_CC_CLEC_SERVICETYPE_UD 0x3

काष्ठा ib_cc_log_event अणु
	u8 local_qp_cn_entry;
	u8 remote_qp_number_cn_entry[3];
	u8  sl_cn_entry:4;
	u8  service_type_cn_entry:4;
	__be32 remote_lid_cn_entry;
	__be32 बारtamp_cn_entry;
पूर्ण __packed;

/* Sixteen congestion entries */
#घोषणा IB_CC_CCS_ENTRIES 16

/* Port control flags */
#घोषणा IB_CC_CCS_PC_SL_BASED 0x01

काष्ठा ib_cc_congestion_entry अणु
	u8 ccti_increase;
	__be16 ccti_समयr;
	u8 trigger_threshold;
	u8 ccti_min; /* min CCTI क्रम cc table */
पूर्ण __packed;

काष्ठा ib_cc_congestion_entry_shaकरोw अणु
	u8 ccti_increase;
	u16 ccti_समयr;
	u8 trigger_threshold;
	u8 ccti_min; /* min CCTI क्रम cc table */
पूर्ण __packed;

काष्ठा ib_cc_congestion_setting_attr अणु
	__be16 port_control;
	__be16 control_map;
	काष्ठा ib_cc_congestion_entry entries[IB_CC_CCS_ENTRIES];
पूर्ण __packed;

काष्ठा ib_cc_congestion_setting_attr_shaकरोw अणु
	u16 port_control;
	u16 control_map;
	काष्ठा ib_cc_congestion_entry_shaकरोw entries[IB_CC_CCS_ENTRIES];
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
	u16 ccti_last_entry;
	काष्ठा ib_cc_table_entry_shaकरोw entries[CC_TABLE_SHADOW_MAX];
पूर्ण __packed;

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

#पूर्ण_अगर				/* _QIB_MAD_H */
