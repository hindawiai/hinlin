<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Derived from IRIX <sys/SN/SN0/hubपन.स>, Revision 1.80.
 *
 * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.
 * Copyright (C) 1999 by Ralf Baechle
 */
#अगर_अघोषित _ASM_SGI_SN_SN0_HUBIO_H
#घोषणा _ASM_SGI_SN_SN0_HUBIO_H

/*
 * Hub I/O पूर्णांकerface रेजिस्टरs
 *
 * All रेजिस्टरs in this file are subject to change until Hub chip tapeout.
 * In general, the दीर्घer software name should be used when available.
 */

/*
 * Slightly मित्रlier names क्रम some common रेजिस्टरs.
 * The hardware definitions follow.
 */
#घोषणा IIO_WIDGET		IIO_WID	     /* Widget identअगरication */
#घोषणा IIO_WIDGET_STAT		IIO_WSTAT    /* Widget status रेजिस्टर */
#घोषणा IIO_WIDGET_CTRL		IIO_WCR	     /* Widget control रेजिस्टर */
#घोषणा IIO_WIDGET_TOUT		IIO_WRTO     /* Widget request समयout */
#घोषणा IIO_WIDGET_FLUSH	IIO_WTFR     /* Widget target flush */
#घोषणा IIO_PROTECT		IIO_ILAPR    /* IO पूर्णांकerface protection */
#घोषणा IIO_PROTECT_OVRRD	IIO_ILAPO    /* IO protect override */
#घोषणा IIO_OUTWIDGET_ACCESS	IIO_IOWA     /* Outbound widget access */
#घोषणा IIO_INWIDGET_ACCESS	IIO_IIWA     /* Inbound widget access */
#घोषणा IIO_INDEV_ERR_MASK	IIO_IIDEM    /* Inbound device error mask */
#घोषणा IIO_LLP_CSR		IIO_ILCSR    /* LLP control and status */
#घोषणा IIO_LLP_LOG		IIO_ILLR     /* LLP log */
#घोषणा IIO_XTALKCC_TOUT	IIO_IXCC     /* Xtalk credit count समयout*/
#घोषणा IIO_XTALKTT_TOUT	IIO_IXTT     /* Xtalk tail समयout */
#घोषणा IIO_IO_ERR_CLR		IIO_IECLR    /* IO error clear */
#घोषणा IIO_BTE_CRB_CNT		IIO_IBCN     /* IO BTE CRB count */

#घोषणा IIO_LLP_CSR_IS_UP		0x00002000
#घोषणा IIO_LLP_CSR_LLP_STAT_MASK	0x00003000
#घोषणा IIO_LLP_CSR_LLP_STAT_SHFT	12

/* key to IIO_PROTECT_OVRRD */
#घोषणा IIO_PROTECT_OVRRD_KEY	0x53474972756c6573ull	/* "SGIrules" */

/* BTE रेजिस्टर names */
#घोषणा IIO_BTE_STAT_0		IIO_IBLS_0   /* Also BTE length/status 0 */
#घोषणा IIO_BTE_SRC_0		IIO_IBSA_0   /* Also BTE source address	 0 */
#घोषणा IIO_BTE_DEST_0		IIO_IBDA_0   /* Also BTE dest. address 0 */
#घोषणा IIO_BTE_CTRL_0		IIO_IBCT_0   /* Also BTE control/terminate 0 */
#घोषणा IIO_BTE_NOTIFY_0	IIO_IBNA_0   /* Also BTE notअगरication 0 */
#घोषणा IIO_BTE_INT_0		IIO_IBIA_0   /* Also BTE पूर्णांकerrupt 0 */
#घोषणा IIO_BTE_OFF_0		0	     /* Base offset from BTE 0 regs. */
#घोषणा IIO_BTE_OFF_1	IIO_IBLS_1 - IIO_IBLS_0 /* Offset from base to BTE 1 */

/* BTE रेजिस्टर offsets from base */
#घोषणा BTखातापूर्णF_STAT		0
#घोषणा BTखातापूर्णF_SRC		(IIO_BTE_SRC_0 - IIO_BTE_STAT_0)
#घोषणा BTखातापूर्णF_DEST		(IIO_BTE_DEST_0 - IIO_BTE_STAT_0)
#घोषणा BTखातापूर्णF_CTRL		(IIO_BTE_CTRL_0 - IIO_BTE_STAT_0)
#घोषणा BTखातापूर्णF_NOTIFY		(IIO_BTE_NOTIFY_0 - IIO_BTE_STAT_0)
#घोषणा BTखातापूर्णF_INT		(IIO_BTE_INT_0 - IIO_BTE_STAT_0)


/*
 * The following definitions use the names defined in the IO पूर्णांकerface
 * करोcument क्रम ease of reference.  When possible, software should
 * generally use the दीर्घer but clearer names defined above.
 */

#घोषणा IIO_BASE	0x400000
#घोषणा IIO_BASE_BTE0	0x410000
#घोषणा IIO_BASE_BTE1	0x420000
#घोषणा IIO_BASE_PERF	0x430000
#घोषणा IIO_PERF_CNT	0x430008

#घोषणा IO_PERF_SETS	32

#घोषणा IIO_WID		0x400000	/* Widget identअगरication */
#घोषणा IIO_WSTAT	0x400008	/* Widget status */
#घोषणा IIO_WCR		0x400020	/* Widget control */

#घोषणा IIO_WSTAT_ECRAZY	(1ULL << 32)	/* Hub gone crazy */
#घोषणा IIO_WSTAT_TXRETRY	(1ULL << 9)	/* Hub Tx Retry समयout */
#घोषणा IIO_WSTAT_TXRETRY_MASK	(0x7F)
#घोषणा IIO_WSTAT_TXRETRY_SHFT	(16)
#घोषणा IIO_WSTAT_TXRETRY_CNT(w)	(((w) >> IIO_WSTAT_TXRETRY_SHFT) & \
					  IIO_WSTAT_TXRETRY_MASK)

#घोषणा IIO_ILAPR	0x400100	/* Local Access Protection */
#घोषणा IIO_ILAPO	0x400108	/* Protection override */
#घोषणा IIO_IOWA	0x400110	/* outbound widget access */
#घोषणा IIO_IIWA	0x400118	/* inbound widget access */
#घोषणा IIO_IIDEM	0x400120	/* Inbound Device Error Mask */
#घोषणा IIO_ILCSR	0x400128	/* LLP control and status */
#घोषणा IIO_ILLR	0x400130	/* LLP Log */
#घोषणा IIO_IIDSR	0x400138	/* Interrupt destination */

#घोषणा IIO_IIBUSERR	0x1400208	/* Reads here cause a bus error. */

/* IO Interrupt Destination Register */
#घोषणा IIO_IIDSR_SENT_SHIFT	28
#घोषणा IIO_IIDSR_SENT_MASK	0x10000000
#घोषणा IIO_IIDSR_ENB_SHIFT	24
#घोषणा IIO_IIDSR_ENB_MASK	0x01000000
#घोषणा IIO_IIDSR_NODE_SHIFT	8
#घोषणा IIO_IIDSR_NODE_MASK	0x0000ff00
#घोषणा IIO_IIDSR_LVL_SHIFT	0
#घोषणा IIO_IIDSR_LVL_MASK	0x0000003f


/* GFX Flow Control Node/Widget Register */
#घोषणा IIO_IGFX_0	0x400140	/* gfx node/widget रेजिस्टर 0 */
#घोषणा IIO_IGFX_1	0x400148	/* gfx node/widget रेजिस्टर 1 */
#घोषणा IIO_IGFX_W_NUM_BITS	4	/* size of widget num field */
#घोषणा IIO_IGFX_W_NUM_MASK	((1<<IIO_IGFX_W_NUM_BITS)-1)
#घोषणा IIO_IGFX_W_NUM_SHIFT	0
#घोषणा IIO_IGFX_N_NUM_BITS	9	/* size of node num field */
#घोषणा IIO_IGFX_N_NUM_MASK	((1<<IIO_IGFX_N_NUM_BITS)-1)
#घोषणा IIO_IGFX_N_NUM_SHIFT	4
#घोषणा IIO_IGFX_P_NUM_BITS	1	/* size of processor num field */
#घोषणा IIO_IGFX_P_NUM_MASK	((1<<IIO_IGFX_P_NUM_BITS)-1)
#घोषणा IIO_IGFX_P_NUM_SHIFT	16
#घोषणा IIO_IGFX_VLD_BITS	1	/* size of valid field */
#घोषणा IIO_IGFX_VLD_MASK	((1<<IIO_IGFX_VLD_BITS)-1)
#घोषणा IIO_IGFX_VLD_SHIFT	20
#घोषणा IIO_IGFX_INIT(widget, node, cpu, valid)				(\
	(((widget) & IIO_IGFX_W_NUM_MASK) << IIO_IGFX_W_NUM_SHIFT) |	 \
	(((node)   & IIO_IGFX_N_NUM_MASK) << IIO_IGFX_N_NUM_SHIFT) |	 \
	(((cpu)	   & IIO_IGFX_P_NUM_MASK) << IIO_IGFX_P_NUM_SHIFT) |	 \
	(((valid)  & IIO_IGFX_VLD_MASK)	  << IIO_IGFX_VLD_SHIFT)	 )

/* Scratch रेजिस्टरs (not all bits available) */
#घोषणा IIO_SCRATCH_REG0	0x400150
#घोषणा IIO_SCRATCH_REG1	0x400158
#घोषणा IIO_SCRATCH_MASK	0x0000000f00f11fff

#घोषणा IIO_SCRATCH_BIT0_0	0x0000000800000000
#घोषणा IIO_SCRATCH_BIT0_1	0x0000000400000000
#घोषणा IIO_SCRATCH_BIT0_2	0x0000000200000000
#घोषणा IIO_SCRATCH_BIT0_3	0x0000000100000000
#घोषणा IIO_SCRATCH_BIT0_4	0x0000000000800000
#घोषणा IIO_SCRATCH_BIT0_5	0x0000000000400000
#घोषणा IIO_SCRATCH_BIT0_6	0x0000000000200000
#घोषणा IIO_SCRATCH_BIT0_7	0x0000000000100000
#घोषणा IIO_SCRATCH_BIT0_8	0x0000000000010000
#घोषणा IIO_SCRATCH_BIT0_9	0x0000000000001000
#घोषणा IIO_SCRATCH_BIT0_R	0x0000000000000fff

/* IO Translation Table Entries */
#घोषणा IIO_NUM_ITTES	7		/* ITTEs numbered 0..6 */
					/* Hw manuals number them 1..7! */

/*
 * As a permanent workaround क्रम a bug in the PI side of the hub, we've
 * redefined big winकरोw 7 as small winकरोw 0.
 */
#घोषणा HUB_NUM_BIG_WINDOW	IIO_NUM_ITTES - 1

/*
 * Use the top big winकरोw as a surrogate क्रम the first small winकरोw
 */
#घोषणा SWIN0_BIGWIN		HUB_NUM_BIG_WINDOW

#घोषणा ILCSR_WARM_RESET	0x100
/*
 * The IO LLP control status रेजिस्टर and widget control रेजिस्टर
 */
#अगर_अघोषित __ASSEMBLY__

प्रकार जोड़ hubii_wid_u अणु
	u64	wid_reg_value;
	काष्ठा अणु
		u64	wid_rsvd:	32,	/* unused */
			wid_rev_num:	 4,	/* revision number */
			wid_part_num:	16,	/* the widget type: hub=c101 */
			wid_mfg_num:	11,	/* Manufacturer id (IBM) */
			wid_rsvd1:	 1;	/* Reserved */
	पूर्ण wid_fields_s;
पूर्ण hubii_wid_t;


प्रकार जोड़ hubii_wcr_u अणु
	u64	wcr_reg_value;
	काष्ठा अणु
		u64	wcr_rsvd:	41,	/* unused */
			wcr_e_thresh:	 5,	/* elasticity threshold */
			wcr_dir_con:	 1,	/* widget direct connect */
			wcr_f_bad_pkt:	 1,	/* Force bad llp pkt enable */
			wcr_xbar_crd:	 3,	/* LLP crossbar credit */
			wcr_rsvd1:	 8,	/* Reserved */
			wcr_tag_mode:	 1,	/* Tag mode */
			wcr_widget_id:	 4;	/* LLP crossbar credit */
	पूर्ण wcr_fields_s;
पूर्ण hubii_wcr_t;

#घोषणा iwcr_dir_con	wcr_fields_s.wcr_dir_con

प्रकार जोड़ hubii_wstat_u अणु
	u64	 reg_value;
	काष्ठा अणु
		u64	rsvd1:		31,
			crazy:		 1,	/* Crazy bit		*/
			rsvd2:		 8,
			llp_tx_cnt:	 8,	/* LLP Xmit retry counter */
			rsvd3:		 6,
			tx_max_rtry:	 1,	/* LLP Retry Timeout Signal */
			rsvd4:		 2,
			xt_tail_to:	 1,	/* Xtalk Tail Timeout	*/
			xt_crd_to:	 1,	/* Xtalk Credit Timeout */
			pending:	 4;	/* Pending Requests	*/
	पूर्ण wstat_fields_s;
पूर्ण hubii_wstat_t;


प्रकार जोड़ hubii_ilcsr_u अणु
	u64	icsr_reg_value;
	काष्ठा अणु
		u64	icsr_rsvd:	22,	/* unused */
			icsr_max_burst: 10,	/* max burst */
			icsr_rsvd4:	 6,	/* reserved */
			icsr_max_retry: 10,	/* max retry */
			icsr_rsvd3:	 2,	/* reserved */
			icsr_lnk_stat:	 2,	/* link status */
			icsr_bm8:	 1,	/* Bit mode 8 */
			icsr_llp_en:	 1,	/* LLP enable bit */
			icsr_rsvd2:	 1,	/* reserver */
			icsr_wrm_reset:	 1,	/* Warm reset bit */
			icsr_rsvd1:	 2,	/* Data पढ़ोy offset */
			icsr_null_to:	 6;	/* Null समयout	  */

	पूर्ण icsr_fields_s;
पूर्ण hubii_ilcsr_t;


प्रकार जोड़ hubii_iowa_u अणु
	u64	iowa_reg_value;
	काष्ठा अणु
		u64	iowa_rsvd:	48,	/* unused */
			iowa_wxoac:	 8,	/* xtalk widget access bits */
			iowa_rsvd1:	 7,	/* xtalk widget access bits */
			iowa_w0oac:	 1;	/* xtalk widget access bits */
	पूर्ण iowa_fields_s;
पूर्ण hubii_iowa_t;

प्रकार जोड़ hubii_iiwa_u अणु
	u64	iiwa_reg_value;
	काष्ठा अणु
		u64	iiwa_rsvd:	48,	/* unused */
			iiwa_wxiac:	 8,	/* hub wid access bits */
			iiwa_rsvd1:	 7,	/* reserved */
			iiwa_w0iac:	 1;	/* hub wid0 access */
	पूर्ण iiwa_fields_s;
पूर्ण hubii_iiwa_t;

प्रकार जोड़	hubii_illr_u अणु
	u64	illr_reg_value;
	काष्ठा अणु
		u64	illr_rsvd:	32,	/* unused */
			illr_cb_cnt:	16,	/* checkbit error count */
			illr_sn_cnt:	16;	/* sequence number count */
	पूर्ण illr_fields_s;
पूर्ण hubii_illr_t;

/* The काष्ठाures below are defined to extract and modअगरy the ii
perक्रमmance रेजिस्टरs */

/* io_perf_sel allows the caller to specअगरy what tests will be
   perक्रमmed */
प्रकार जोड़ io_perf_sel अणु
	u64 perf_sel_reg;
	काष्ठा अणु
		u64	perf_rsvd  : 48,
			perf_icct  :  8,
			perf_ippr1 :  4,
			perf_ippr0 :  4;
	पूर्ण perf_sel_bits;
पूर्ण io_perf_sel_t;

/* io_perf_cnt is to extract the count from the hub रेजिस्टरs. Due to
   hardware problems there is only one counter, not two. */

प्रकार जोड़ io_perf_cnt अणु
	u64	perf_cnt;
	काष्ठा अणु
		u64	perf_rsvd1 : 32,
			perf_rsvd2 : 12,
			perf_cnt   : 20;
	पूर्ण perf_cnt_bits;
पूर्ण io_perf_cnt_t;

#पूर्ण_अगर /* !__ASSEMBLY__ */


#घोषणा LNK_STAT_WORKING	0x2

#घोषणा IIO_LLP_CB_MAX	0xffff
#घोषणा IIO_LLP_SN_MAX	0xffff

/* IO PRB Entries */
#घोषणा IIO_NUM_IPRBS	(9)
#घोषणा IIO_IOPRB_0	0x400198	/* PRB entry 0 */
#घोषणा IIO_IOPRB_8	0x4001a0	/* PRB entry 8 */
#घोषणा IIO_IOPRB_9	0x4001a8	/* PRB entry 9 */
#घोषणा IIO_IOPRB_A	0x4001b0	/* PRB entry a */
#घोषणा IIO_IOPRB_B	0x4001b8	/* PRB entry b */
#घोषणा IIO_IOPRB_C	0x4001c0	/* PRB entry c */
#घोषणा IIO_IOPRB_D	0x4001c8	/* PRB entry d */
#घोषणा IIO_IOPRB_E	0x4001d0	/* PRB entry e */
#घोषणा IIO_IOPRB_F	0x4001d8	/* PRB entry f */


#घोषणा IIO_IXCC	0x4001e0	/* Crosstalk credit count समयout */
#घोषणा IIO_IXTCC	IIO_IXCC
#घोषणा IIO_IMEM	0x4001e8	/* Miscellaneous Enable Mask */
#घोषणा IIO_IXTT	0x4001f0	/* Crosstalk tail समयout */
#घोषणा IIO_IECLR	0x4001f8	/* IO error clear */
#घोषणा IIO_IBCN	0x400200	/* IO BTE CRB count */

/*
 * IIO_IMEM Register fields.
 */
#घोषणा IIO_IMEM_W0ESD	0x1		/* Widget 0 shut करोwn due to error */
#घोषणा IIO_IMEM_B0ESD	(1 << 4)	/* BTE 0 shut करोwn due to error */
#घोषणा IIO_IMEM_B1ESD	(1 << 8)	/* BTE 1 Shut करोwn due to error */

/* PIO Read address Table Entries */
#घोषणा IIO_IPCA	0x400300	/* PRB Counter adjust */
#घोषणा IIO_NUM_PRTES	8		/* Total number of PRB table entries */
#घोषणा IIO_PRTE_0	0x400308	/* PIO Read address table entry 0 */
#घोषणा IIO_PRTE(_x)	(IIO_PRTE_0 + (8 * (_x)))
#घोषणा IIO_WIDPRTE(x)	IIO_PRTE(((x) - 8)) /* widget ID to its PRTE num */
#घोषणा IIO_IPDR	0x400388	/* PIO table entry deallocation */
#घोषणा IIO_ICDR	0x400390	/* CRB Entry Deallocation */
#घोषणा IIO_IFDR	0x400398	/* IOQ FIFO Depth */
#घोषणा IIO_IIAP	0x4003a0	/* IIQ Arbitration Parameters */
#घोषणा IIO_IMMR	IIO_IIAP
#घोषणा IIO_ICMR	0x4003a8	/* CRB Management Register */
#घोषणा IIO_ICCR	0x4003b0	/* CRB Control Register */
#घोषणा IIO_ICTO	0x4003b8	/* CRB Time Out Register */
#घोषणा IIO_ICTP	0x4003c0	/* CRB Time Out Prescalar */


/*
 * ICMR रेजिस्टर fields
 */
#घोषणा IIO_ICMR_PC_VLD_SHFT	36
#घोषणा IIO_ICMR_PC_VLD_MASK	(0x7fffUL << IIO_ICMR_PC_VLD_SHFT)

#घोषणा IIO_ICMR_CRB_VLD_SHFT	20
#घोषणा IIO_ICMR_CRB_VLD_MASK	(0x7fffUL << IIO_ICMR_CRB_VLD_SHFT)

#घोषणा IIO_ICMR_FC_CNT_SHFT	16
#घोषणा IIO_ICMR_FC_CNT_MASK	(0xf << IIO_ICMR_FC_CNT_SHFT)

#घोषणा IIO_ICMR_C_CNT_SHFT	4
#घोषणा IIO_ICMR_C_CNT_MASK	(0xf << IIO_ICMR_C_CNT_SHFT)

#घोषणा IIO_ICMR_P_CNT_SHFT	0
#घोषणा IIO_ICMR_P_CNT_MASK	(0xf << IIO_ICMR_P_CNT_SHFT)

#घोषणा IIO_ICMR_PRECISE	(1UL << 52)
#घोषणा IIO_ICMR_CLR_RPPD	(1UL << 13)
#घोषणा IIO_ICMR_CLR_RQPD	(1UL << 12)

/*
 * IIO PIO Deallocation रेजिस्टर field masks : (IIO_IPDR)
 */
#घोषणा IIO_IPDR_PND	(1 << 4)

/*
 * IIO CRB deallocation रेजिस्टर field masks: (IIO_ICDR)
 */
#घोषणा IIO_ICDR_PND	(1 << 4)

/*
 * IIO CRB control रेजिस्टर Fields: IIO_ICCR
 */
#घोषणा IIO_ICCR_PENDING	(0x10000)
#घोषणा IIO_ICCR_CMD_MASK	(0xFF)
#घोषणा IIO_ICCR_CMD_SHFT	(7)
#घोषणा IIO_ICCR_CMD_NOP	(0x0)	/* No Op */
#घोषणा IIO_ICCR_CMD_WAKE	(0x100) /* Reactivate CRB entry and process */
#घोषणा IIO_ICCR_CMD_TIMEOUT	(0x200) /* Make CRB समयout & mark invalid */
#घोषणा IIO_ICCR_CMD_EJECT	(0x400) /* Contents of entry written to memory
					 * via a WB
					 */
#घोषणा IIO_ICCR_CMD_FLUSH	(0x800)

/*
 * CRB manipulation macros
 *	The CRB macros are slightly complicated, since there are up to
 *	four रेजिस्टरs associated with each CRB entry.
 */
#घोषणा IIO_NUM_CRBS		15	/* Number of CRBs */
#घोषणा IIO_NUM_NORMAL_CRBS	12	/* Number of regular CRB entries */
#घोषणा IIO_NUM_PC_CRBS		4	/* Number of partial cache CRBs */
#घोषणा IIO_ICRB_OFFSET		8
#घोषणा IIO_ICRB_0		0x400400
/* XXX - This is now tuneable:
	#घोषणा IIO_FIRST_PC_ENTRY 12
 */

#घोषणा IIO_ICRB_A(_x)	(IIO_ICRB_0 + (4 * IIO_ICRB_OFFSET * (_x)))
#घोषणा IIO_ICRB_B(_x)	(IIO_ICRB_A(_x) + 1*IIO_ICRB_OFFSET)
#घोषणा IIO_ICRB_C(_x)	(IIO_ICRB_A(_x) + 2*IIO_ICRB_OFFSET)
#घोषणा IIO_ICRB_D(_x)	(IIO_ICRB_A(_x) + 3*IIO_ICRB_OFFSET)

/* XXX - IBUE रेजिस्टर coming क्रम Hub 2 */

/*
 *
 * CRB Register description.
 *
 * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING
 * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING
 * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING
 * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING
 * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING
 *
 * Many of the fields in CRB are status bits used by hardware
 * क्रम implementation of the protocol. It's very dangerous to
 * mess around with the CRB रेजिस्टरs.
 *
 * It's OK to पढ़ो the CRB रेजिस्टरs and try to make sense out of the
 * fields in CRB.
 *
 * Updating CRB requires all activities in Hub IIO to be quiesced.
 * otherwise, a ग_लिखो to CRB could corrupt other CRB entries.
 * CRBs are here only as a back करोor peek to hub IIO's status.
 * Quiescing implies  no dmas no PIOs
 * either directly from the cpu or from sn0net.
 * this is not something that can be करोne easily. So, AVOID updating
 * CRBs.
 */

/*
 * Fields in CRB Register A
 */
#अगर_अघोषित __ASSEMBLY__
प्रकार जोड़ icrba_u अणु
	u64	reg_value;
	काष्ठा अणु
		u64	resvd:	6,
			stall_bte0: 1,	/* Stall BTE 0 */
			stall_bte1: 1,	/* Stall BTE 1 */
			error:	1,	/* CRB has an error	*/
			ecode:	3,	/* Error Code		*/
			lnetuce: 1,	/* SN0net Uncorrectable error */
			mark:	1,	/* CRB Has been marked	*/
			xerr:	1,	/* Error bit set in xtalk header */
			sidn:	4,	/* SIDN field from xtalk	*/
			tnum:	5,	/* TNUM field in xtalk		*/
			addr:	38,	/* Address of request	*/
			valid:	1,	/* Valid status		*/
			iow:	1;	/* IO Write operation	*/
	पूर्ण icrba_fields_s;
पूर्ण icrba_t;

/* This is an alternate प्रकार क्रम the HUB1 CRB A in order to allow
   runसमय selection of the क्रमmat based on the REV_ID field of the
   NI_STATUS_REV_ID रेजिस्टर. */
प्रकार जोड़ h1_icrba_u अणु
	u64	reg_value;

	काष्ठा अणु
		u64	resvd:	6,
			unused: 1,	/* Unused but RW!!	*/
			error:	1,	/* CRB has an error	*/
			ecode:	4,	/* Error Code		*/
			lnetuce: 1,	/* SN0net Uncorrectable error */
			mark:	1,	/* CRB Has been marked	*/
			xerr:	1,	/* Error bit set in xtalk header */
			sidn:	4,	/* SIDN field from xtalk	*/
			tnum:	5,	/* TNUM field in xtalk		*/
			addr:	38,	/* Address of request	*/
			valid:	1,	/* Valid status		*/
			iow:	1;	/* IO Write operation	*/
	पूर्ण h1_icrba_fields_s;
पूर्ण h1_icrba_t;

/* XXX - Is this still right?  Check the spec. */
#घोषणा ICRBN_A_CERR_SHFT	54
#घोषणा ICRBN_A_ERR_MASK	0x3ff

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा IIO_ICRB_ADDR_SHFT	2	/* Shअगरt to get proper address */

/*
 * values क्रम "ecode" field
 */
#घोषणा IIO_ICRB_ECODE_DERR	0	/* Directory error due to IIO access */
#घोषणा IIO_ICRB_ECODE_PERR	1	/* Poison error on IO access */
#घोषणा IIO_ICRB_ECODE_WERR	2	/* Write error by IIO access
					 * e.g. WINV to a Read only line.
					 */
#घोषणा IIO_ICRB_ECODE_AERR	3	/* Access error caused by IIO access */
#घोषणा IIO_ICRB_ECODE_PWERR	4	/* Error on partial ग_लिखो	*/
#घोषणा IIO_ICRB_ECODE_PRERR	5	/* Error on partial पढ़ो	*/
#घोषणा IIO_ICRB_ECODE_TOUT	6	/* CRB समयout beक्रमe deallocating */
#घोषणा IIO_ICRB_ECODE_XTERR	7	/* Incoming xtalk pkt had error bit */



/*
 * Fields in CRB Register B
 */
#अगर_अघोषित __ASSEMBLY__
प्रकार जोड़ icrbb_u अणु
	u64	reg_value;
	काष्ठा अणु
	    u64 rsvd1:	5,
		btक्रमागत: 1,	/* BTE to which entry beदीर्घs to */
		cohtrans: 1,	/* Coherent transaction */
		xtsize: 2,	/* Xtalk operation size
				 * 0: Double Word
				 * 1: 32 Bytes.
				 * 2: 128 Bytes,
				 * 3: Reserved.
				 */
		srcnode: 9,	/* Source Node ID		*/
		srcinit: 2,	/* Source Initiator:
				 * See below क्रम field values.
				 */
		useold: 1,	/* Use OLD command क्रम processing */
		imsgtype: 2,	/* Incoming message type
				 * see below क्रम field values
				 */
		imsg:	8,	/* Incoming message	*/
		initator: 3,	/* Initiator of original request
				 * See below क्रम field values.
				 */
		reqtype: 5,	/* Identअगरies type of request
				 * See below क्रम field values.
				 */
		rsvd2:	7,
		ackcnt: 11,	/* Invalidate ack count */
		resp:	1,	/* data response  given to processor */
		ack:	1,	/* indicates data ack received	*/
		hold:	1,	/* entry is gathering inval acks */
		wb_pend:1,	/* रुकोing क्रम ग_लिखोback to complete */
		पूर्णांकvn:	1,	/* Intervention */
		stall_ib: 1,	/* Stall Ibuf (from crosstalk) */
		stall_पूर्णांकr: 1;	/* Stall पूर्णांकernal पूर्णांकerrupts */
	पूर्ण icrbb_field_s;
पूर्ण icrbb_t;

/* This is an alternate प्रकार क्रम the HUB1 CRB B in order to allow
   runसमय selection of the क्रमmat based on the REV_ID field of the
   NI_STATUS_REV_ID रेजिस्टर. */
प्रकार जोड़ h1_icrbb_u अणु
	u64	reg_value;
	काष्ठा अणु
		u64	rsvd1:	5,
			btक्रमागत: 1,	/* BTE to which entry beदीर्घs to */
			cohtrans: 1,	/* Coherent transaction */
			xtsize: 2,	/* Xtalk operation size
					 * 0: Double Word
					 * 1: 32 Bytes.
					 * 2: 128 Bytes,
					 * 3: Reserved.
					 */
			srcnode: 9,	/* Source Node ID		*/
			srcinit: 2,	/* Source Initiator:
					 * See below क्रम field values.
					 */
			useold: 1,	/* Use OLD command क्रम processing */
			imsgtype: 2,	/* Incoming message type
					 * see below क्रम field values
					 */
			imsg:	8,	/* Incoming message	*/
			initator: 3,	/* Initiator of original request
					 * See below क्रम field values.
					 */
			rsvd2:	1,
			pcache: 1,	/* entry beदीर्घs to partial cache */
			reqtype: 5,	/* Identअगरies type of request
					 * See below क्रम field values.
					 */
			stl_ib: 1,	/* stall Ibus coming from xtalk */
			stl_पूर्णांकr: 1,	/* Stall पूर्णांकernal पूर्णांकerrupts */
			stl_bte0: 1,	/* Stall BTE 0	*/
			stl_bte1: 1,	/* Stall BTE 1	*/
			पूर्णांकrvn: 1,	/* Req was target of पूर्णांकervention */
			ackcnt: 11,	/* Invalidate ack count */
			resp:	1,	/* data response  given to processor */
			ack:	1,	/* indicates data ack received	*/
			hold:	1,	/* entry is gathering inval acks */
			wb_pend:1,	/* रुकोing क्रम ग_लिखोback to complete */
			sleep:	1,	/* xtalk req sleeping till IO-sync */
			pnd_reply: 1,	/* replies not issed due to IOQ full */
			pnd_req: 1;	/* reqs not issued due to IOQ full */
	पूर्ण h1_icrbb_field_s;
पूर्ण h1_icrbb_t;


#घोषणा b_imsgtype	icrbb_field_s.imsgtype
#घोषणा b_btक्रमागत	icrbb_field_s.btक्रमागत
#घोषणा b_cohtrans	icrbb_field_s.cohtrans
#घोषणा b_xtsize	icrbb_field_s.xtsize
#घोषणा b_srcnode	icrbb_field_s.srcnode
#घोषणा b_srcinit	icrbb_field_s.srcinit
#घोषणा b_imsgtype	icrbb_field_s.imsgtype
#घोषणा b_imsg		icrbb_field_s.imsg
#घोषणा b_initiator	icrbb_field_s.initiator

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * values क्रम field xtsize
 */
#घोषणा IIO_ICRB_XTSIZE_DW	0	/* Xtalk operation size is 8 bytes  */
#घोषणा IIO_ICRB_XTSIZE_32	1	/* Xtalk operation size is 32 bytes */
#घोषणा IIO_ICRB_XTSIZE_128	2	/* Xtalk operation size is 128 bytes */

/*
 * values क्रम field srcinit
 */
#घोषणा IIO_ICRB_PROC0		0	/* Source of request is Proc 0 */
#घोषणा IIO_ICRB_PROC1		1	/* Source of request is Proc 1 */
#घोषणा IIO_ICRB_GB_REQ		2	/* Source is Guaranteed BW request */
#घोषणा IIO_ICRB_IO_REQ		3	/* Source is Normal IO request	*/

/*
 * Values क्रम field imsgtype
 */
#घोषणा IIO_ICRB_IMSGT_XTALK	0	/* Incoming Message from Xtalk */
#घोषणा IIO_ICRB_IMSGT_BTE	1	/* Incoming message from BTE	*/
#घोषणा IIO_ICRB_IMSGT_SN0NET	2	/* Incoming message from SN0 net */
#घोषणा IIO_ICRB_IMSGT_CRB	3	/* Incoming message from CRB ???  */

/*
 * values क्रम field initiator.
 */
#घोषणा IIO_ICRB_INIT_XTALK	0	/* Message originated in xtalk	*/
#घोषणा IIO_ICRB_INIT_BTE0	0x1	/* Message originated in BTE 0	*/
#घोषणा IIO_ICRB_INIT_SN0NET	0x2	/* Message originated in SN0net */
#घोषणा IIO_ICRB_INIT_CRB	0x3	/* Message originated in CRB ?	*/
#घोषणा IIO_ICRB_INIT_BTE1	0x5	/* MEssage originated in BTE 1	*/

/*
 * Values क्रम field reqtype.
 */
/* XXX - Need to fix this क्रम Hub 2 */
#घोषणा IIO_ICRB_REQ_DWRD	0	/* Request type द्विगुन word	*/
#घोषणा IIO_ICRB_REQ_QCLRD	1	/* Request is Qrtr Caceh line Rd */
#घोषणा IIO_ICRB_REQ_BLKRD	2	/* Request is block पढ़ो	*/
#घोषणा IIO_ICRB_REQ_RSHU	6	/* Request is BTE block पढ़ो	*/
#घोषणा IIO_ICRB_REQ_REXU	7	/* request is BTE Excl Read	*/
#घोषणा IIO_ICRB_REQ_RDEX	8	/* Request is Read Exclusive	*/
#घोषणा IIO_ICRB_REQ_WINC	9	/* Request is Write Invalidate	*/
#घोषणा IIO_ICRB_REQ_BWINV	10	/* Request is BTE Winv		*/
#घोषणा IIO_ICRB_REQ_PIORD	11	/* Request is PIO पढ़ो		*/
#घोषणा IIO_ICRB_REQ_PIOWR	12	/* Request is PIO Write		*/
#घोषणा IIO_ICRB_REQ_PRDM	13	/* Request is Fetch&Op		*/
#घोषणा IIO_ICRB_REQ_PWRM	14	/* Request is Store &Op		*/
#घोषणा IIO_ICRB_REQ_PTPWR	15	/* Request is Peer to peer	*/
#घोषणा IIO_ICRB_REQ_WB		16	/* Request is Write back	*/
#घोषणा IIO_ICRB_REQ_DEX	17	/* Retained DEX Cache line	*/

/*
 * Fields in CRB Register C
 */

#अगर_अघोषित __ASSEMBLY__

प्रकार जोड़ icrbc_s अणु
	u64	reg_value;
	काष्ठा अणु
		u64	rsvd:	6,
			sleep:	1,
			pricnt: 4,	/* Priority count sent with Read req */
			pripsc: 4,	/* Priority Pre scalar	*/
			bteop:	1,	/* BTE Operation	*/
			push_be: 34,	/* Push address Byte enable
					 * Holds push addr, अगर CRB is क्रम BTE
					 * If CRB beदीर्घs to Partial cache,
					 * this contains byte enables bits
					 * ([47:46] = 0)
					 */
			suppl:	11,	/* Supplemental field	*/
			barrop: 1,	/* Barrier Op bit set in xtalk req */
			करोresp: 1,	/* Xtalk req needs a response	*/
			gbr:	1;	/* GBR bit set in xtalk packet	*/
	पूर्ण icrbc_field_s;
पूर्ण icrbc_t;

#घोषणा c_pricnt	icrbc_field_s.pricnt
#घोषणा c_pripsc	icrbc_field_s.pripsc
#घोषणा c_bteop		icrbc_field_s.bteop
#घोषणा c_bteaddr	icrbc_field_s.push_be	/* push_be field has 2 names */
#घोषणा c_benable	icrbc_field_s.push_be	/* push_be field has 2 names */
#घोषणा c_suppl		icrbc_field_s.suppl
#घोषणा c_barrop	icrbc_field_s.barrop
#घोषणा c_करोresp	icrbc_field_s.करोresp
#घोषणा c_gbr	icrbc_field_s.gbr
#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * Fields in CRB Register D
 */

#अगर_अघोषित __ASSEMBLY__
प्रकार जोड़ icrbd_s अणु
	u64	reg_value;
	काष्ठा अणु
	    u64 rsvd:	38,
		toutvld: 1,	/* Timeout in progress क्रम this CRB */
		ctxtvld: 1,	/* Context field below is valid */
		rsvd2:	1,
		context: 15,	/* Bit vector:
				 * Has a bit set क्रम each CRB entry
				 * which needs to be deallocated
				 * beक्रमe this CRB entry is processed.
				 * Set only क्रम barrier operations.
				 */
		समयout: 8;	/* Timeout Upper 8 bits */
	पूर्ण icrbd_field_s;
पूर्ण icrbd_t;

#घोषणा icrbd_toutvld	icrbd_field_s.toutvld
#घोषणा icrbd_ctxtvld	icrbd_field_s.ctxtvld
#घोषणा icrbd_context	icrbd_field_s.context


प्रकार जोड़ hubii_अगरdr_u अणु
	u64	hi_अगरdr_value;
	काष्ठा अणु
		u64	अगरdr_rsvd:	49,
			अगरdr_maxrp:	 7,
			अगरdr_rsvd1:	 1,
			अगरdr_maxrq:	 7;
	पूर्ण hi_अगरdr_fields;
पूर्ण hubii_अगरdr_t;

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * Hardware deचिन्हित names क्रम the BTE control रेजिस्टरs.
 */
#घोषणा IIO_IBLS_0	0x410000	/* BTE length/status 0 */
#घोषणा IIO_IBSA_0	0x410008	/* BTE source address 0 */
#घोषणा IIO_IBDA_0	0x410010	/* BTE destination address 0 */
#घोषणा IIO_IBCT_0	0x410018	/* BTE control/terminate 0 */
#घोषणा IIO_IBNA_0	0x410020	/* BTE notअगरication address 0 */
#घोषणा IIO_IBNR_0	IIO_IBNA_0
#घोषणा IIO_IBIA_0	0x410028	/* BTE पूर्णांकerrupt address 0 */

#घोषणा IIO_IBLS_1	0x420000	/* BTE length/status 1 */
#घोषणा IIO_IBSA_1	0x420008	/* BTE source address 1 */
#घोषणा IIO_IBDA_1	0x420010	/* BTE destination address 1 */
#घोषणा IIO_IBCT_1	0x420018	/* BTE control/terminate 1 */
#घोषणा IIO_IBNA_1	0x420020	/* BTE notअगरication address 1 */
#घोषणा IIO_IBNR_1	IIO_IBNA_1
#घोषणा IIO_IBIA_1	0x420028	/* BTE पूर्णांकerrupt address 1 */

/*
 * More miscellaneous रेजिस्टरs
 */
#घोषणा IIO_IPCR	0x430000	/* Perक्रमmance Control */
#घोषणा IIO_IPPR	0x430008	/* Perक्रमmance Profiling */

/*
 * IO Error Clear रेजिस्टर bit field definitions
 */
#घोषणा IECLR_BTE1		(1 << 18)  /* clear bte error 1 ??? */
#घोषणा IECLR_BTE0		(1 << 17)  /* clear bte error 0 ??? */
#घोषणा IECLR_CRAZY		(1 << 16)  /* clear crazy bit in wstat reg */
#घोषणा IECLR_PRB_F		(1 << 15)  /* clear err bit in PRB_F reg */
#घोषणा IECLR_PRB_E		(1 << 14)  /* clear err bit in PRB_E reg */
#घोषणा IECLR_PRB_D		(1 << 13)  /* clear err bit in PRB_D reg */
#घोषणा IECLR_PRB_C		(1 << 12)  /* clear err bit in PRB_C reg */
#घोषणा IECLR_PRB_B		(1 << 11)  /* clear err bit in PRB_B reg */
#घोषणा IECLR_PRB_A		(1 << 10)  /* clear err bit in PRB_A reg */
#घोषणा IECLR_PRB_9		(1 << 9)   /* clear err bit in PRB_9 reg */
#घोषणा IECLR_PRB_8		(1 << 8)   /* clear err bit in PRB_8 reg */
#घोषणा IECLR_PRB_0		(1 << 0)   /* clear err bit in PRB_0 reg */

/*
 * IO PIO Read Table Entry क्रमmat
 */

#अगर_अघोषित __ASSEMBLY__

प्रकार जोड़ iprte_a अणु
	u64	entry;
	काष्ठा अणु
	    u64 rsvd1	  : 7,	/* Reserved field		*/
		valid	  : 1,	/* Maps to a समयout entry	*/
		rsvd2	  : 1,
		srcnode	  : 9,	/* Node which did this PIO	*/
		initiator : 2,	/* If T5A or T5B or IO		*/
		rsvd3	  : 3,
		addr	  : 38, /* Physical address of PIO	*/
		rsvd4	  : 3;
	पूर्ण iprte_fields;
पूर्ण iprte_a_t;

#घोषणा iprte_valid	iprte_fields.valid
#घोषणा iprte_समयout	iprte_fields.समयout
#घोषणा iprte_srcnode	iprte_fields.srcnode
#घोषणा iprte_init	iprte_fields.initiator
#घोषणा iprte_addr	iprte_fields.addr

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा IPRTE_ADDRSHFT	3

/*
 * Hub IIO PRB Register क्रमmat.
 */

#अगर_अघोषित __ASSEMBLY__
/*
 * Note: Fields bnakctr, anakctr, xtalkctrmode, ovflow fields are
 * "Status" fields, and should only be used in हाल of clean up after errors.
 */

प्रकार जोड़ iprb_u अणु
	u64	reg_value;
	काष्ठा अणु
	    u64 rsvd1:	15,
		error:	1,	/* Widget rcvd wr resp pkt w/ error */
		ovflow: 5,	/* Overflow count. perf measurement */
		fire_and_क्रमget: 1, /* Launch Write without response */
		mode:	2,	/* Widget operation Mode	*/
		rsvd2:	2,
		bnakctr: 14,
		rsvd3:	2,
		anakctr: 14,
		xtalkctr: 8;
	पूर्ण iprb_fields_s;
पूर्ण iprb_t;

#घोषणा iprb_regval	reg_value

#घोषणा iprb_error	iprb_fields_s.error
#घोषणा iprb_ovflow	iprb_fields_s.ovflow
#घोषणा iprb_ff		iprb_fields_s.fire_and_क्रमget
#घोषणा iprb_mode	iprb_fields_s.mode
#घोषणा iprb_bnakctr	iprb_fields_s.bnakctr
#घोषणा iprb_anakctr	iprb_fields_s.anakctr
#घोषणा iprb_xtalkctr	iprb_fields_s.xtalkctr

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * values क्रम mode field in iprb_t.
 * For details of the meanings of NAK and Accept, refer the PIO flow
 * करोcument
 */
#घोषणा IPRB_MODE_NORMAL	(0)
#घोषणा IPRB_MODE_COLLECT_A	(1)	/* PRB in collect A mode */
#घोषणा IPRB_MODE_SERVICE_A	(2)	/* NAK B and Accept A */
#घोषणा IPRB_MODE_SERVICE_B	(3)	/* NAK A and Accept B */

/*
 * IO CRB entry C_A to E_A : Partial (cache) CRBS
 */
#अगर_अघोषित __ASSEMBLY__
प्रकार जोड़ icrbp_a अणु
	u64   ip_reg;	    /* the entire रेजिस्टर value	*/
	काष्ठा अणु
	     u64 error: 1,  /*	  63, error occurred		*/
		ln_uce: 1,  /*	  62: uncorrectable memory	*/
		ln_ae:	1,  /*	  61: protection violation	*/
		ln_werr:1,  /*	  60: ग_लिखो access error	*/
		ln_aerr:1,  /*	  59: sn0net: Address error	*/
		ln_perr:1,  /*	  58: sn0net: poison error	*/
		समयout:1,  /*	  57: CRB समयd out		*/
		l_bdpkt:1,  /*	  56: truncated pkt on sn0net	*/
		c_bdpkt:1,  /*	  55: truncated pkt on xtalk	*/
		c_err:	1,  /*	  54: incoming xtalk req, err set*/
		rsvd1: 12,  /* 53-42: reserved			*/
		valid:	1,  /*	  41: Valid status		*/
		sidn:	4,  /* 40-37: SIDN field of xtalk rqst	*/
		tnum:	5,  /* 36-32: TNUM of xtalk request	*/
		bo:	1,  /*	  31: barrier op set in xtalk rqst*/
		resprqd:1,  /*	  30: xtalk rqst requires response*/
		gbr:	1,  /*	  29: gbr bit set in xtalk rqst */
		size:	2,  /* 28-27: size of xtalk request	*/
		excl:	4,  /* 26-23: exclusive bit(s)		*/
		stall:	3,  /* 22-20: stall (xtalk, bte 0/1)	*/
		पूर्णांकvn:	1,  /*	  19: rqst target of पूर्णांकervention*/
		resp:	1,  /*	  18: Data response given to t5 */
		ack:	1,  /*	  17: Data ack received.	*/
		hold:	1,  /*	  16: crb gathering invalidate acks*/
		wb:	1,  /*	  15: ग_लिखोback pending.	*/
		ack_cnt:11, /* 14-04: counter of invalidate acks*/
		tscaler:4;  /* 03-00: Timeout prescaler		*/
	पूर्ण ip_fmt;
पूर्ण icrbp_a_t;

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * A couple of defines to go with the above काष्ठाure.
 */
#घोषणा ICRBP_A_CERR_SHFT	54
#घोषणा ICRBP_A_ERR_MASK	0x3ff

#अगर_अघोषित __ASSEMBLY__
प्रकार जोड़ hubii_idsr अणु
	u64 iin_reg;
	काष्ठा अणु
		u64 rsvd1 : 35,
		    isent : 1,
		    rsvd2 : 3,
		    ienable: 1,
		    rsvd  : 7,
		    node  : 9,
		    rsvd4 : 1,
		    level : 7;
	पूर्ण iin_fmt;
पूर्ण hubii_idsr_t;
#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * IO BTE Length/Status (IIO_IBLS) रेजिस्टर bit field definitions
 */
#घोषणा IBLS_BUSY		(0x1 << 20)
#घोषणा IBLS_ERROR_SHFT		16
#घोषणा IBLS_ERROR		(0x1 << IBLS_ERROR_SHFT)
#घोषणा IBLS_LENGTH_MASK	0xffff

/*
 * IO BTE Control/Terminate रेजिस्टर (IBCT) रेजिस्टर bit field definitions
 */
#घोषणा IBCT_POISON		(0x1 << 8)
#घोषणा IBCT_NOTIFY		(0x1 << 4)
#घोषणा IBCT_ZFIL_MODE		(0x1 << 0)

/*
 * IO BTE Interrupt Address Register (IBIA) रेजिस्टर bit field definitions
 */
#घोषणा IBIA_LEVEL_SHFT		16
#घोषणा IBIA_LEVEL_MASK		(0x7f << IBIA_LEVEL_SHFT)
#घोषणा IBIA_NODE_ID_SHFT	0
#घोषणा IBIA_NODE_ID_MASK	(0x1ff)

/*
 * Miscellaneous hub स्थिरants
 */

/* Number of widमाला_लो supported by hub */
#घोषणा HUB_NUM_WIDGET		9
#घोषणा HUB_WIDGET_ID_MIN	0x8
#घोषणा HUB_WIDGET_ID_MAX	0xf

#घोषणा HUB_WIDGET_PART_NUM	0xc101
#घोषणा MAX_HUBS_PER_XBOW	2

/*
 * Get a hub's widget id from widget control रेजिस्टर
 */
#घोषणा IIO_WCR_WID_GET(nasid)	(REMOTE_HUB_L(nasid, III_WCR) & 0xf)
#घोषणा IIO_WST_ERROR_MASK	(UINT64_CAST 1 << 32) /* Widget status error */

/*
 * Number of credits Hub widget has जबतक sending req/response to
 * xbow.
 * Value of 3 is required by Xbow 1.1
 * We may be able to increase this to 4 with Xbow 1.2.
 */
#घोषणा	      HUBII_XBOW_CREDIT	      3
#घोषणा	      HUBII_XBOW_REV2_CREDIT  4

#पूर्ण_अगर /* _ASM_SGI_SN_SN0_HUBIO_H */
