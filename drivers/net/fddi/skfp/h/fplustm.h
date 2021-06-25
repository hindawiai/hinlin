<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

/*
 *	AMD Fplus in tag mode data काष्ठाs
 *	defs क्रम fplusपंचांग.c
 */

#अगर_अघोषित	_FPLUS_
#घोषणा _FPLUS_

#अगर_अघोषित	HW_PTR
#घोषणा	HW_PTR	व्योम __iomem *
#पूर्ण_अगर

/*
 * fplus error statistic काष्ठाure
 */
काष्ठा err_st अणु
	u_दीर्घ err_valid ;		/* memory status valid */
	u_दीर्घ err_पात ;		/* memory status receive पात */
	u_दीर्घ err_e_indicator ;	/* error indicator */
	u_दीर्घ err_crc ;		/* error detected (CRC or length) */
	u_दीर्घ err_llc_frame ;		/* LLC frame */
	u_दीर्घ err_mac_frame ;		/* MAC frame */
	u_दीर्घ err_smt_frame ;		/* SMT frame */
	u_दीर्घ err_imp_frame ;		/* implementer frame */
	u_दीर्घ err_no_buf ;		/* no buffer available */
	u_दीर्घ err_too_दीर्घ ;		/* दीर्घer than max. buffer */
	u_दीर्घ err_bec_stat ;		/* beacon state entered */
	u_दीर्घ err_clm_stat ;		/* claim state entered */
	u_दीर्घ err_sअगरg_det ;		/* लघु पूर्णांकerframe gap detect */
	u_दीर्घ err_phinv ;		/* PHY invalid */
	u_दीर्घ err_tkiss ;		/* token issued */
	u_दीर्घ err_tkerr ;		/* token error */
पूर्ण ;

/*
 *	Transmit Descriptor काष्ठा
 */
काष्ठा s_smt_fp_txd अणु
	__le32 txd_tbctrl ;		/* transmit buffer control */
	__le32 txd_txdscr ;		/* transmit frame status word */
	__le32 txd_tbadr ;		/* physical tx buffer address */
	__le32 txd_ntdadr ;		/* physical poपूर्णांकer to the next TxD */
#अगर_घोषित	ENA_64BIT_SUP
	__le32 txd_tbadr_hi ;		/* physical tx buffer addr (high dword)*/
#पूर्ण_अगर
	अक्षर far *txd_virt ;		/* भव poपूर्णांकer to the data frag */
					/* virt poपूर्णांकer to the next TxD */
	काष्ठा s_smt_fp_txd अस्थिर far *txd_next ;
	काष्ठा s_txd_os txd_os ;	/* OS - specअगरic काष्ठा */
पूर्ण ;

/*
 *	Receive Descriptor काष्ठा
 */
काष्ठा s_smt_fp_rxd अणु
	__le32 rxd_rbctrl ;		/* receive buffer control */
	__le32 rxd_rfsw ;		/* receive frame status word */
	__le32 rxd_rbadr ;		/* physical rx buffer address */
	__le32 rxd_nrdadr ;		/* physical poपूर्णांकer to the next RxD */
#अगर_घोषित	ENA_64BIT_SUP
	__le32 rxd_rbadr_hi ;		/* physical tx buffer addr (high dword)*/
#पूर्ण_अगर
	अक्षर far *rxd_virt ;		/* भव poपूर्णांकer to the data frag */
					/* virt poपूर्णांकer to the next RxD */
	काष्ठा s_smt_fp_rxd अस्थिर far *rxd_next ;
	काष्ठा s_rxd_os rxd_os ;	/* OS - specअगरic काष्ठा */
पूर्ण ;

/*
 *	Descriptor Union Definition
 */
जोड़ s_fp_descr अणु
	काष्ठा	s_smt_fp_txd t ;		/* poपूर्णांकer to the TxD */
	काष्ठा	s_smt_fp_rxd r ;		/* poपूर्णांकer to the RxD */
पूर्ण ;

/*
 *	TxD Ring Control काष्ठा
 */
काष्ठा s_smt_tx_queue अणु
	काष्ठा s_smt_fp_txd अस्थिर *tx_curr_put ; /* next मुक्त TxD */
	काष्ठा s_smt_fp_txd अस्थिर *tx_prev_put ; /* shaकरोw put poपूर्णांकer */
	काष्ठा s_smt_fp_txd अस्थिर *tx_curr_get ; /* next TxD to release*/
	u_लघु tx_मुक्त ;			/* count of मुक्त TxD's */
	u_लघु tx_used ;			/* count of used TxD's */
	HW_PTR tx_bmu_ctl ;			/* BMU addr क्रम tx start */
	HW_PTR tx_bmu_dsc ;			/* BMU addr क्रम curr dsc. */
पूर्ण ;

/*
 *	RxD Ring Control काष्ठा
 */
काष्ठा s_smt_rx_queue अणु
	काष्ठा s_smt_fp_rxd अस्थिर *rx_curr_put ; /* next RxD to queue पूर्णांकo */
	काष्ठा s_smt_fp_rxd अस्थिर *rx_prev_put ; /* shaकरोw put poपूर्णांकer */
	काष्ठा s_smt_fp_rxd अस्थिर *rx_curr_get ; /* next RxD to fill */
	u_लघु rx_मुक्त ;			/* count of मुक्त RxD's */
	u_लघु rx_used ;			/* count of used RxD's */
	HW_PTR rx_bmu_ctl ;			/* BMU addr क्रम rx start */
	HW_PTR rx_bmu_dsc ;			/* BMU addr क्रम curr dsc. */
पूर्ण ;

#घोषणा VOID_FRAME_OFF		0x00
#घोषणा CLAIM_FRAME_OFF		0x08
#घोषणा BEACON_FRAME_OFF	0x10
#घोषणा DBEACON_FRAME_OFF	0x18
#घोषणा RX_FIFO_OFF		0x21		/* to get a prime number क्रम */
						/* the RX_FIFO_SPACE */

#घोषणा RBC_MEM_SIZE		0x8000
#घोषणा SEND_ASYNC_AS_SYNC	0x1
#घोषणा	SYNC_TRAFFIC_ON		0x2

/* big FIFO memory */
#घोषणा	RX_FIFO_SPACE		0x4000 - RX_FIFO_OFF
#घोषणा	TX_FIFO_SPACE		0x4000

#घोषणा	TX_SMALL_FIFO		0x0900
#घोषणा	TX_MEDIUM_FIFO		TX_FIFO_SPACE / 2	
#घोषणा	TX_LARGE_FIFO		TX_FIFO_SPACE - TX_SMALL_FIFO	

#घोषणा	RX_SMALL_FIFO		0x0900
#घोषणा	RX_LARGE_FIFO		RX_FIFO_SPACE - RX_SMALL_FIFO	

काष्ठा s_smt_fअगरo_conf अणु
	u_लघु	rbc_ram_start ;		/* FIFO start address */
	u_लघु	rbc_ram_end ;		/* FIFO size */
	u_लघु	rx1_fअगरo_start ;	/* rx queue start address */
	u_लघु	rx1_fअगरo_size ;		/* rx queue size */
	u_लघु	rx2_fअगरo_start ;	/* rx queue start address */
	u_लघु	rx2_fअगरo_size ;		/* rx queue size */
	u_लघु	tx_s_start ;		/* sync queue start address */
	u_लघु	tx_s_size ;		/* sync queue size */
	u_लघु	tx_a0_start ;		/* async queue A0 start address */
	u_लघु	tx_a0_size ;		/* async queue A0 size */
	u_लघु	fअगरo_config_mode ;	/* FIFO configuration mode */
पूर्ण ;

#घोषणा FM_ADDRX	(FM_ADDET|FM_EXGPA0|FM_EXGPA1)

काष्ठा s_smt_fp अणु
	u_लघु	mdr2init ;		/* mode रेजिस्टर 2 init value */
	u_लघु	mdr3init ;		/* mode रेजिस्टर 3 init value */
	u_लघु frselreg_init ;		/* frame selection रेजिस्टर init val */
	u_लघु	rx_mode ;		/* address mode broad/multi/promisc */
	u_लघु	nsa_mode ;
	u_लघु rx_prom ;
	u_लघु	exgpa ;

	काष्ठा err_st err_stats ;	/* error statistics */

	/*
	 * MAC buffers
	 */
	काष्ठा fddi_mac_sf अणु		/* special frame build buffer */
		u_अक्षर			mac_fc ;
		काष्ठा fddi_addr	mac_dest ;
		काष्ठा fddi_addr	mac_source ;
		u_अक्षर			mac_info[0x20] ;
	पूर्ण mac_sfb ;


	/*
	 * queues
	 */
#घोषणा QUEUE_S			0
#घोषणा QUEUE_A0		1
#घोषणा QUEUE_R1		0
#घोषणा QUEUE_R2		1
#घोषणा USED_QUEUES		2

	/*
	 * queue poपूर्णांकers; poपूर्णांकs to the queue dependent variables
	 */
	काष्ठा s_smt_tx_queue *tx[USED_QUEUES] ;
	काष्ठा s_smt_rx_queue *rx[USED_QUEUES] ;

	/*
	 * queue dependent variables
	 */
	काष्ठा s_smt_tx_queue tx_q[USED_QUEUES] ;
	काष्ठा s_smt_rx_queue rx_q[USED_QUEUES] ;

	/*
	 * FIFO configuration काष्ठा
	 */
	काष्ठा	s_smt_fअगरo_conf	fअगरo ;

	/* last क्रमmac status */
	u_लघु	 s2u ;
	u_लघु	 s2l ;

	/* calculated FORMAC+ reg.addr. */
	HW_PTR	fm_st1u ;
	HW_PTR	fm_st1l ;
	HW_PTR	fm_st2u ;
	HW_PTR	fm_st2l ;
	HW_PTR	fm_st3u ;
	HW_PTR	fm_st3l ;


	/*
	 * multicast table
	 */
#घोषणा FPMAX_MULTICAST 32 
#घोषणा	SMT_MAX_MULTI	4
	काष्ठा अणु
		काष्ठा s_fpmc अणु
			काष्ठा fddi_addr	a ;	/* mc address */
			u_अक्षर			n ;	/* usage counter */
			u_अक्षर			perm ;	/* flag: permanent */
		पूर्ण table[FPMAX_MULTICAST] ;
	पूर्ण mc ;
	काष्ठा fddi_addr	group_addr ;
	u_दीर्घ	func_addr ;		/* functional address */
	पूर्णांक	smt_slots_used ;	/* count of table entries क्रम the SMT */
	पूर्णांक	os_slots_used ;		/* count of table entries */ 
					/* used by the os-specअगरic module */
पूर्ण ;

/*
 * modes क्रम mac_set_rx_mode()
 */
#घोषणा RX_ENABLE_ALLMULTI	1	/* enable all multicasts */
#घोषणा RX_DISABLE_ALLMULTI	2	/* disable "enable all multicasts" */
#घोषणा RX_ENABLE_PROMISC	3	/* enable promiscuous */
#घोषणा RX_DISABLE_PROMISC	4	/* disable promiscuous */
#घोषणा RX_ENABLE_NSA		5	/* enable reception of NSA frames */
#घोषणा RX_DISABLE_NSA		6	/* disable reception of NSA frames */


/*
 * support क्रम byte reversal in AIX
 * (descriptors and poपूर्णांकers must be byte reversed in memory
 *  CPU is big endian; M-Channel is little endian)
 */
#अगर_घोषित	AIX
#घोषणा MDR_REV
#घोषणा	AIX_REVERSE(x)		((((x)<<24L)&0xff000000L)	+	\
				 (((x)<< 8L)&0x00ff0000L)	+	\
				 (((x)>> 8L)&0x0000ff00L)	+	\
				 (((x)>>24L)&0x000000ffL))
#अन्यथा
#अगर_अघोषित AIX_REVERSE
#घोषणा	AIX_REVERSE(x)	(x)
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित	MDR_REV	
#घोषणा	MDR_REVERSE(x)		((((x)<<24L)&0xff000000L)	+	\
				 (((x)<< 8L)&0x00ff0000L)	+	\
				 (((x)>> 8L)&0x0000ff00L)	+	\
				 (((x)>>24L)&0x000000ffL))
#अन्यथा
#अगर_अघोषित MDR_REVERSE
#घोषणा	MDR_REVERSE(x)	(x)
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर
