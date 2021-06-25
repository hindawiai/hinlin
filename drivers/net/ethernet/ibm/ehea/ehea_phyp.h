<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/net/ethernet/ibm/ehea/ehea_phyp.h
 *
 *  eHEA ethernet device driver क्रम IBM eServer System p
 *
 *  (C) Copyright IBM Corp. 2006
 *
 *  Authors:
 *       Christoph Raisch <raisch@de.ibm.com>
 *       Jan-Bernd Themann <themann@de.ibm.com>
 *       Thomas Klein <tklein@de.ibm.com>
 */

#अगर_अघोषित __EHEA_PHYP_H__
#घोषणा __EHEA_PHYP_H__

#समावेश <linux/delay.h>
#समावेश <यंत्र/hvcall.h>
#समावेश "ehea.h"
#समावेश "ehea_hw.h"

/* Some abbreviations used here:
 *
 * hcp_*  - काष्ठाures, variables and functions releated to Hypervisor Calls
 */

/* Number of pages which can be रेजिस्टरed at once by H_REGISTER_HEA_RPAGES */
#घोषणा EHEA_MAX_RPAGE 512

/* Notअगरication Event Queue (NEQ) Entry bit masks */
#घोषणा NEQE_EVENT_CODE		EHEA_BMASK_IBM(2, 7)
#घोषणा NEQE_PORTNUM  		EHEA_BMASK_IBM(32, 47)
#घोषणा NEQE_PORT_UP		EHEA_BMASK_IBM(16, 16)
#घोषणा NEQE_EXTSWITCH_PORT_UP	EHEA_BMASK_IBM(17, 17)
#घोषणा NEQE_EXTSWITCH_PRIMARY	EHEA_BMASK_IBM(18, 18)
#घोषणा NEQE_PLID		EHEA_BMASK_IBM(16, 47)

/* Notअगरication Event Codes */
#घोषणा EHEA_EC_PORTSTATE_CHG	0x30
#घोषणा EHEA_EC_ADAPTER_MALFUNC	0x32
#घोषणा EHEA_EC_PORT_MALFUNC	0x33

/* Notअगरication Event Log Register (NELR) bit masks */
#घोषणा NELR_PORT_MALFUNC	EHEA_BMASK_IBM(61, 61)
#घोषणा NELR_ADAPTER_MALFUNC	EHEA_BMASK_IBM(62, 62)
#घोषणा NELR_PORTSTATE_CHG	EHEA_BMASK_IBM(63, 63)

अटल अंतरभूत व्योम hcp_epas_ctor(काष्ठा h_epas *epas, u64 paddr_kernel,
				 u64 paddr_user)
अणु
	/* To support 64k pages we must round to 64k page boundary */
	epas->kernel.addr = ioremap((paddr_kernel & PAGE_MASK), PAGE_SIZE) +
			    (paddr_kernel & ~PAGE_MASK);
	epas->user.addr = paddr_user;
पूर्ण

अटल अंतरभूत व्योम hcp_epas_dtor(काष्ठा h_epas *epas)
अणु
	अगर (epas->kernel.addr)
		iounmap((व्योम __iomem *)((u64)epas->kernel.addr & PAGE_MASK));

	epas->user.addr = 0;
	epas->kernel.addr = 0;
पूर्ण

काष्ठा hcp_modअगरy_qp_cb0 अणु
	u64 qp_ctl_reg;		/* 00 */
	u32 max_swqe;		/* 02 */
	u32 max_rwqe;		/* 03 */
	u32 port_nb;		/* 04 */
	u32 reserved0;		/* 05 */
	u64 qp_aer;		/* 06 */
	u64 qp_tenure;		/* 08 */
पूर्ण;

/* Hcall Query/Modअगरy Queue Pair Control Block 0 Selection Mask Bits */
#घोषणा H_QPCB0_ALL             EHEA_BMASK_IBM(0, 5)
#घोषणा H_QPCB0_QP_CTL_REG      EHEA_BMASK_IBM(0, 0)
#घोषणा H_QPCB0_MAX_SWQE        EHEA_BMASK_IBM(1, 1)
#घोषणा H_QPCB0_MAX_RWQE        EHEA_BMASK_IBM(2, 2)
#घोषणा H_QPCB0_PORT_NB         EHEA_BMASK_IBM(3, 3)
#घोषणा H_QPCB0_QP_AER          EHEA_BMASK_IBM(4, 4)
#घोषणा H_QPCB0_QP_TENURE       EHEA_BMASK_IBM(5, 5)

/* Queue Pair Control Register Status Bits */
#घोषणा H_QP_CR_ENABLED		    0x8000000000000000ULL /* QP enabled */
							  /* QP States: */
#घोषणा H_QP_CR_STATE_RESET	    0x0000010000000000ULL /*  Reset */
#घोषणा H_QP_CR_STATE_INITIALIZED   0x0000020000000000ULL /*  Initialized */
#घोषणा H_QP_CR_STATE_RDY2RCV	    0x0000030000000000ULL /*  Ready to recv */
#घोषणा H_QP_CR_STATE_RDY2SND	    0x0000050000000000ULL /*  Ready to send */
#घोषणा H_QP_CR_STATE_ERROR	    0x0000800000000000ULL /*  Error */
#घोषणा H_QP_CR_RES_STATE 	    0x0000007F00000000ULL /* Resultant state */

काष्ठा hcp_modअगरy_qp_cb1 अणु
	u32 qpn;		/* 00 */
	u32 qp_asyn_ev_eq_nb;	/* 01 */
	u64 sq_cq_handle;	/* 02 */
	u64 rq_cq_handle;	/* 04 */
	/* sgel = scatter gather element */
	u32 sgel_nb_sq;		/* 06 */
	u32 sgel_nb_rq1;	/* 07 */
	u32 sgel_nb_rq2;	/* 08 */
	u32 sgel_nb_rq3;	/* 09 */
पूर्ण;

/* Hcall Query/Modअगरy Queue Pair Control Block 1 Selection Mask Bits */
#घोषणा H_QPCB1_ALL             EHEA_BMASK_IBM(0, 7)
#घोषणा H_QPCB1_QPN             EHEA_BMASK_IBM(0, 0)
#घोषणा H_QPCB1_ASYN_EV_EQ_NB   EHEA_BMASK_IBM(1, 1)
#घोषणा H_QPCB1_SQ_CQ_HANDLE    EHEA_BMASK_IBM(2, 2)
#घोषणा H_QPCB1_RQ_CQ_HANDLE    EHEA_BMASK_IBM(3, 3)
#घोषणा H_QPCB1_SGEL_NB_SQ      EHEA_BMASK_IBM(4, 4)
#घोषणा H_QPCB1_SGEL_NB_RQ1     EHEA_BMASK_IBM(5, 5)
#घोषणा H_QPCB1_SGEL_NB_RQ2     EHEA_BMASK_IBM(6, 6)
#घोषणा H_QPCB1_SGEL_NB_RQ3     EHEA_BMASK_IBM(7, 7)

काष्ठा hcp_query_ehea अणु
	u32 cur_num_qps;		/* 00 */
	u32 cur_num_cqs;		/* 01 */
	u32 cur_num_eqs;		/* 02 */
	u32 cur_num_mrs;		/* 03 */
	u32 auth_level;			/* 04 */
	u32 max_num_qps;		/* 05 */
	u32 max_num_cqs;		/* 06 */
	u32 max_num_eqs;		/* 07 */
	u32 max_num_mrs;		/* 08 */
	u32 reserved0;			/* 09 */
	u32 पूर्णांक_घड़ी_freq;		/* 10 */
	u32 max_num_pds;		/* 11 */
	u32 max_num_addr_handles;	/* 12 */
	u32 max_num_cqes;		/* 13 */
	u32 max_num_wqes;		/* 14 */
	u32 max_num_sgel_rq1wqe;	/* 15 */
	u32 max_num_sgel_rq2wqe;	/* 16 */
	u32 max_num_sgel_rq3wqe;	/* 17 */
	u32 mr_page_size;		/* 18 */
	u32 reserved1;			/* 19 */
	u64 max_mr_size;		/* 20 */
	u64 reserved2;			/* 22 */
	u32 num_ports;			/* 24 */
	u32 reserved3;			/* 25 */
	u32 reserved4;			/* 26 */
	u32 reserved5;			/* 27 */
	u64 max_mc_mac;			/* 28 */
	u64 ehea_cap;			/* 30 */
	u32 max_isn_per_eq;		/* 32 */
	u32 max_num_neq;		/* 33 */
	u64 max_num_vlan_ids;		/* 34 */
	u32 max_num_port_group;		/* 36 */
	u32 max_num_phys_port;		/* 37 */

पूर्ण;

/* Hcall Query/Modअगरy Port Control Block defines */
#घोषणा H_PORT_CB0	 0
#घोषणा H_PORT_CB1	 1
#घोषणा H_PORT_CB2	 2
#घोषणा H_PORT_CB3	 3
#घोषणा H_PORT_CB4	 4
#घोषणा H_PORT_CB5	 5
#घोषणा H_PORT_CB6	 6
#घोषणा H_PORT_CB7	 7

काष्ठा hcp_ehea_port_cb0 अणु
	u64 port_mac_addr;
	u64 port_rc;
	u64 reserved0;
	u32 port_op_state;
	u32 port_speed;
	u32 ext_swport_op_state;
	u32 neg_tpf_prpf;
	u32 num_शेष_qps;
	u32 reserved1;
	u64 शेष_qpn_arr[16];
पूर्ण;

/* Hcall Query/Modअगरy Port Control Block 0 Selection Mask Bits */
#घोषणा H_PORT_CB0_ALL		EHEA_BMASK_IBM(0, 7)    /* Set all bits */
#घोषणा H_PORT_CB0_MAC		EHEA_BMASK_IBM(0, 0)    /* MAC address */
#घोषणा H_PORT_CB0_PRC		EHEA_BMASK_IBM(1, 1)    /* Port Recv Control */
#घोषणा H_PORT_CB0_DEFQPNARRAY	EHEA_BMASK_IBM(7, 7)    /* Default QPN Array */

/*  Hcall Query Port: Returned port speed values */
#घोषणा H_SPEED_10M_H	1	/*  10 Mbps, Half Duplex */
#घोषणा H_SPEED_10M_F	2	/*  10 Mbps, Full Duplex */
#घोषणा H_SPEED_100M_H	3	/* 100 Mbps, Half Duplex */
#घोषणा H_SPEED_100M_F	4	/* 100 Mbps, Full Duplex */
#घोषणा H_SPEED_1G_F	6	/*   1 Gbps, Full Duplex */
#घोषणा H_SPEED_10G_F	8	/*  10 Gbps, Full Duplex */

/* Port Receive Control Status Bits */
#घोषणा PXLY_RC_VALID           EHEA_BMASK_IBM(49, 49)
#घोषणा PXLY_RC_VLAN_XTRACT     EHEA_BMASK_IBM(50, 50)
#घोषणा PXLY_RC_TCP_6_TUPLE     EHEA_BMASK_IBM(51, 51)
#घोषणा PXLY_RC_UDP_6_TUPLE     EHEA_BMASK_IBM(52, 52)
#घोषणा PXLY_RC_TCP_3_TUPLE     EHEA_BMASK_IBM(53, 53)
#घोषणा PXLY_RC_TCP_2_TUPLE     EHEA_BMASK_IBM(54, 54)
#घोषणा PXLY_RC_LLC_SNAP        EHEA_BMASK_IBM(55, 55)
#घोषणा PXLY_RC_JUMBO_FRAME     EHEA_BMASK_IBM(56, 56)
#घोषणा PXLY_RC_FRAG_IP_PKT     EHEA_BMASK_IBM(57, 57)
#घोषणा PXLY_RC_TCP_UDP_CHKSUM  EHEA_BMASK_IBM(58, 58)
#घोषणा PXLY_RC_IP_CHKSUM       EHEA_BMASK_IBM(59, 59)
#घोषणा PXLY_RC_MAC_FILTER      EHEA_BMASK_IBM(60, 60)
#घोषणा PXLY_RC_UNTAG_FILTER    EHEA_BMASK_IBM(61, 61)
#घोषणा PXLY_RC_VLAN_TAG_FILTER EHEA_BMASK_IBM(62, 63)

#घोषणा PXLY_RC_VLAN_FILTER     2
#घोषणा PXLY_RC_VLAN_PERM       0


#घोषणा H_PORT_CB1_ALL          0x8000000000000000ULL

काष्ठा hcp_ehea_port_cb1 अणु
	u64 vlan_filter[64];
पूर्ण;

#घोषणा H_PORT_CB2_ALL          0xFFE0000000000000ULL

काष्ठा hcp_ehea_port_cb2 अणु
	u64 rxo;
	u64 rxucp;
	u64 rxufd;
	u64 rxuerr;
	u64 rxftl;
	u64 rxmcp;
	u64 rxbcp;
	u64 txo;
	u64 txucp;
	u64 txmcp;
	u64 txbcp;
पूर्ण;

काष्ठा hcp_ehea_port_cb3 अणु
	u64 vlan_bc_filter[64];
	u64 vlan_mc_filter[64];
	u64 vlan_un_filter[64];
	u64 port_mac_hash_array[64];
पूर्ण;

#घोषणा H_PORT_CB4_ALL          0xF000000000000000ULL
#घोषणा H_PORT_CB4_JUMBO        0x1000000000000000ULL
#घोषणा H_PORT_CB4_SPEED        0x8000000000000000ULL

काष्ठा hcp_ehea_port_cb4 अणु
	u32 port_speed;
	u32 छोड़ो_frame;
	u32 ens_port_op_state;
	u32 jumbo_frame;
	u32 ens_port_wrap;
पूर्ण;

/* Hcall Query/Modअगरy Port Control Block 5 Selection Mask Bits */
#घोषणा H_PORT_CB5_RCU		0x0001000000000000ULL
#घोषणा PXS_RCU			EHEA_BMASK_IBM(61, 63)

काष्ठा hcp_ehea_port_cb5 अणु
	u64 prc;	        /* 00 */
	u64 uaa;		/* 01 */
	u64 macvc;		/* 02 */
	u64 xpcsc;		/* 03 */
	u64 xpcsp;		/* 04 */
	u64 pcsid;		/* 05 */
	u64 xpcsst;		/* 06 */
	u64 pthlb;		/* 07 */
	u64 pthrb;		/* 08 */
	u64 pqu;		/* 09 */
	u64 pqd;		/* 10 */
	u64 prt;		/* 11 */
	u64 wsth;		/* 12 */
	u64 rcb;		/* 13 */
	u64 rcm;		/* 14 */
	u64 rcu;		/* 15 */
	u64 macc;		/* 16 */
	u64 pc;			/* 17 */
	u64 pst;		/* 18 */
	u64 ducqpn;		/* 19 */
	u64 mcqpn;		/* 20 */
	u64 mma;		/* 21 */
	u64 pmc0h;		/* 22 */
	u64 pmc0l;		/* 23 */
	u64 lbc;		/* 24 */
पूर्ण;

#घोषणा H_PORT_CB6_ALL  0xFFFFFE7FFFFF8000ULL

काष्ठा hcp_ehea_port_cb6 अणु
	u64 rxo;		/* 00 */
	u64 rx64;		/* 01 */
	u64 rx65;		/* 02 */
	u64 rx128;		/* 03 */
	u64 rx256;		/* 04 */
	u64 rx512;		/* 05 */
	u64 rx1024;		/* 06 */
	u64 rxbfcs;		/* 07 */
	u64 rxime;		/* 08 */
	u64 rxrle;		/* 09 */
	u64 rxorle;		/* 10 */
	u64 rxftl;		/* 11 */
	u64 rxjab;		/* 12 */
	u64 rxse;		/* 13 */
	u64 rxce;		/* 14 */
	u64 rxrf;		/* 15 */
	u64 rxfrag;		/* 16 */
	u64 rxuoc;		/* 17 */
	u64 rxcpf;		/* 18 */
	u64 rxsb;		/* 19 */
	u64 rxfd;		/* 20 */
	u64 rxoerr;		/* 21 */
	u64 rxaln;		/* 22 */
	u64 ducqpn;		/* 23 */
	u64 reserved0;		/* 24 */
	u64 rxmcp;		/* 25 */
	u64 rxbcp;		/* 26 */
	u64 txmcp;		/* 27 */
	u64 txbcp;		/* 28 */
	u64 txo;		/* 29 */
	u64 tx64;		/* 30 */
	u64 tx65;		/* 31 */
	u64 tx128;		/* 32 */
	u64 tx256;		/* 33 */
	u64 tx512;		/* 34 */
	u64 tx1024;		/* 35 */
	u64 txbfcs;		/* 36 */
	u64 txcpf;		/* 37 */
	u64 txlf;		/* 38 */
	u64 txrf;		/* 39 */
	u64 txime;		/* 40 */
	u64 txsc;		/* 41 */
	u64 txmc;		/* 42 */
	u64 txsqe;		/* 43 */
	u64 txdef;		/* 44 */
	u64 txlcol;		/* 45 */
	u64 txexcol;		/* 46 */
	u64 txcse;		/* 47 */
	u64 txbor;		/* 48 */
पूर्ण;

#घोषणा H_PORT_CB7_DUCQPN 0x8000000000000000ULL

काष्ठा hcp_ehea_port_cb7 अणु
	u64 def_uc_qpn;
पूर्ण;

u64 ehea_h_query_ehea_qp(स्थिर u64 adapter_handle,
			 स्थिर u8 qp_category,
			 स्थिर u64 qp_handle, स्थिर u64 sel_mask,
			 व्योम *cb_addr);

u64 ehea_h_modअगरy_ehea_qp(स्थिर u64 adapter_handle,
			  स्थिर u8 cat,
			  स्थिर u64 qp_handle,
			  स्थिर u64 sel_mask,
			  व्योम *cb_addr,
			  u64 *inv_attr_id,
			  u64 *proc_mask, u16 *out_swr, u16 *out_rwr);

u64 ehea_h_alloc_resource_eq(स्थिर u64 adapter_handle,
			     काष्ठा ehea_eq_attr *eq_attr, u64 *eq_handle);

u64 ehea_h_alloc_resource_cq(स्थिर u64 adapter_handle,
			     काष्ठा ehea_cq_attr *cq_attr,
			     u64 *cq_handle, काष्ठा h_epas *epas);

u64 ehea_h_alloc_resource_qp(स्थिर u64 adapter_handle,
			     काष्ठा ehea_qp_init_attr *init_attr,
			     स्थिर u32 pd,
			     u64 *qp_handle, काष्ठा h_epas *h_epas);

#घोषणा H_REG_RPAGE_PAGE_SIZE          EHEA_BMASK_IBM(48, 55)
#घोषणा H_REG_RPAGE_QT                 EHEA_BMASK_IBM(62, 63)

u64 ehea_h_रेजिस्टर_rpage(स्थिर u64 adapter_handle,
			  स्थिर u8 pagesize,
			  स्थिर u8 queue_type,
			  स्थिर u64 resource_handle,
			  स्थिर u64 log_pageaddr, u64 count);

#घोषणा H_DISABLE_GET_EHEA_WQE_P  1
#घोषणा H_DISABLE_GET_SQ_WQE_P    2
#घोषणा H_DISABLE_GET_RQC         3

u64 ehea_h_disable_and_get_hea(स्थिर u64 adapter_handle, स्थिर u64 qp_handle);

#घोषणा FORCE_FREE 1
#घोषणा NORMAL_FREE 0

u64 ehea_h_मुक्त_resource(स्थिर u64 adapter_handle, स्थिर u64 res_handle,
			 u64 क्रमce_bit);

u64 ehea_h_alloc_resource_mr(स्थिर u64 adapter_handle, स्थिर u64 vaddr,
			     स्थिर u64 length, स्थिर u32 access_ctrl,
			     स्थिर u32 pd, u64 *mr_handle, u32 *lkey);

u64 ehea_h_रेजिस्टर_rpage_mr(स्थिर u64 adapter_handle, स्थिर u64 mr_handle,
			     स्थिर u8 pagesize, स्थिर u8 queue_type,
			     स्थिर u64 log_pageaddr, स्थिर u64 count);

u64 ehea_h_रेजिस्टर_smr(स्थिर u64 adapter_handle, स्थिर u64 orig_mr_handle,
			स्थिर u64 vaddr_in, स्थिर u32 access_ctrl, स्थिर u32 pd,
			काष्ठा ehea_mr *mr);

u64 ehea_h_query_ehea(स्थिर u64 adapter_handle, व्योम *cb_addr);

/* output param R5 */
#घोषणा H_MEHEAPORT_CAT		EHEA_BMASK_IBM(40, 47)
#घोषणा H_MEHEAPORT_PN		EHEA_BMASK_IBM(48, 63)

u64 ehea_h_query_ehea_port(स्थिर u64 adapter_handle, स्थिर u16 port_num,
			   स्थिर u8 cb_cat, स्थिर u64 select_mask,
			   व्योम *cb_addr);

u64 ehea_h_modअगरy_ehea_port(स्थिर u64 adapter_handle, स्थिर u16 port_num,
			    स्थिर u8 cb_cat, स्थिर u64 select_mask,
			    व्योम *cb_addr);

#घोषणा H_REGBCMC_PN            EHEA_BMASK_IBM(48, 63)
#घोषणा H_REGBCMC_REGTYPE       EHEA_BMASK_IBM(60, 63)
#घोषणा H_REGBCMC_MACADDR       EHEA_BMASK_IBM(16, 63)
#घोषणा H_REGBCMC_VLANID        EHEA_BMASK_IBM(52, 63)

u64 ehea_h_reg_dereg_bcmc(स्थिर u64 adapter_handle, स्थिर u16 port_num,
			  स्थिर u8 reg_type, स्थिर u64 mc_mac_addr,
			  स्थिर u16 vlan_id, स्थिर u32 hcall_id);

u64 ehea_h_reset_events(स्थिर u64 adapter_handle, स्थिर u64 neq_handle,
			स्थिर u64 event_mask);

u64 ehea_h_error_data(स्थिर u64 adapter_handle, स्थिर u64 ressource_handle,
		      व्योम *rblock);

#पूर्ण_अगर	/* __EHEA_PHYP_H__ */
