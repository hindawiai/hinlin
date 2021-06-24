<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TSTYPE_H_
#घोषणा _TSTYPE_H_
#समावेश "rtl819x_Qos.h"

#घोषणा TS_ADDBA_DELAY		60

#घोषणा TOTAL_TS_NUM		16
#घोषणा TCLAS_NUM		4

/*  This define the Tx/Rx directions */
क्रमागत tr_select अणु
	TX_सूची = 0,
	RX_सूची = 1,
पूर्ण;

जोड़ qos_tclas अणु
	काष्ठा type_general अणु
		u8		priority;
		u8		classअगरier_type;
		u8		mask;
	पूर्ण type_general;

	काष्ठा type0_eth अणु
		u8		priority;
		u8		classअगरier_type;
		u8		mask;
		u8		src_addr[6];
		u8		dst_addr[6];
		u16		type;
	पूर्ण type0_eth;

	काष्ठा type1_ipv4 अणु
		u8		priority;
		u8		classअगरier_type;
		u8		mask;
		u8		version;
		u8		src_ip[4];
		u8		dst_ip[4];
		u16		src_port;
		u16		dst_port;
		u8		dscp;
		u8		protocol;
		u8		reserved;
	पूर्ण type1_ipv4;

	काष्ठा type1_ipv6 अणु
		u8		priority;
		u8		classअगरier_type;
		u8		mask;
		u8		version;
		u8		src_ip[16];
		u8		dst_ip[16];
		u16		src_port;
		u16		dst_port;
		u8		flow_label[3];
	पूर्ण type1_ipv6;

	काष्ठा type2_8021q अणु
		u8		priority;
		u8		classअगरier_type;
		u8		mask;
		u16		tag_type;
	पूर्ण type2_8021q;
पूर्ण;

काष्ठा ts_common_info अणु
	काष्ठा list_head		list;
	काष्ठा समयr_list		setup_समयr;
	काष्ठा समयr_list		inact_समयr;
	u8				addr[6];
	काष्ठा tspec_body		t_spec;
	जोड़ qos_tclas			t_class[TCLAS_NUM];
	u8				t_clas_proc;
	u8				t_clas_num;
पूर्ण;

काष्ठा tx_ts_record अणु
	काष्ठा ts_common_info		ts_common_info;
	u16				tx_cur_seq;
	काष्ठा ba_record		tx_pending_ba_record;
	काष्ठा ba_record		tx_admitted_ba_record;
	u8				add_ba_req_in_progress;
	u8				add_ba_req_delayed;
	u8				using_ba;
	काष्ठा समयr_list		ts_add_ba_समयr;
	u8				num;
पूर्ण;

काष्ठा rx_ts_record अणु
	काष्ठा ts_common_info		ts_common_info;
	u16				rx_indicate_seq;
	u16				rx_समयout_indicate_seq;
	काष्ठा list_head		rx_pending_pkt_list;
	काष्ठा समयr_list		rx_pkt_pending_समयr;
	काष्ठा ba_record		rx_admitted_ba_record;
	u16				rx_last_seq_num;
	u8				rx_last_frag_num;
	u8				num;
पूर्ण;

#पूर्ण_अगर
