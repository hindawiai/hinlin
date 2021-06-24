<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित __CSIO_HW_H__
#घोषणा __CSIO_HW_H__

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/compiler.h>
#समावेश <linux/cdev.h>
#समावेश <linux/list.h>
#समावेश <linux/mempool.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock_types.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport_fc.h>

#समावेश "t4_hw.h"
#समावेश "csio_hw_chip.h"
#समावेश "csio_wr.h"
#समावेश "csio_mb.h"
#समावेश "csio_scsi.h"
#समावेश "csio_defs.h"
#समावेश "t4_regs.h"
#समावेश "t4_msg.h"

/*
 * An error value used by host. Should not clash with FW defined वापस values.
 */
#घोषणा	FW_HOSTERROR			255

#घोषणा CSIO_HW_NAME		"Chelsio FCoE Adapter"
#घोषणा CSIO_MAX_PFN		8
#घोषणा CSIO_MAX_PPORTS		4

#घोषणा CSIO_MAX_LUN		0xFFFF
#घोषणा CSIO_MAX_QUEUE		2048
#घोषणा CSIO_MAX_CMD_PER_LUN	32
#घोषणा CSIO_MAX_DDP_BUF_SIZE	(1024 * 1024)
#घोषणा CSIO_MAX_SECTOR_SIZE	128
#घोषणा CSIO_MIN_T6_FW		0x01102D00  /* FW 1.16.45.0 */

/* Interrupts */
#घोषणा CSIO_EXTRA_MSI_IQS	2	/* Extra iqs क्रम INTX/MSI mode
					 * (Forward पूर्णांकr iq + fw iq) */
#घोषणा CSIO_EXTRA_VECS		2	/* non-data + FW evt */
#घोषणा CSIO_MAX_SCSI_CPU	128
#घोषणा CSIO_MAX_SCSI_QSETS	(CSIO_MAX_SCSI_CPU * CSIO_MAX_PPORTS)
#घोषणा CSIO_MAX_MSIX_VECS	(CSIO_MAX_SCSI_QSETS + CSIO_EXTRA_VECS)

/* Queues */
क्रमागत अणु
	CSIO_INTR_WRSIZE = 128,
	CSIO_INTR_IQSIZE = ((CSIO_MAX_MSIX_VECS + 1) * CSIO_INTR_WRSIZE),
	CSIO_FWEVT_WRSIZE = 128,
	CSIO_FWEVT_IQLEN = 128,
	CSIO_FWEVT_FLBUFS = 64,
	CSIO_FWEVT_IQSIZE = (CSIO_FWEVT_WRSIZE * CSIO_FWEVT_IQLEN),
	CSIO_HW_NIQ = 1,
	CSIO_HW_NFLQ = 1,
	CSIO_HW_NEQ = 1,
	CSIO_HW_NINTXQ = 1,
पूर्ण;

काष्ठा csio_msix_entries अणु
	व्योम		*dev_id;	/* Priv object associated w/ this msix*/
	अक्षर		desc[24];	/* Description of this vector */
पूर्ण;

काष्ठा csio_scsi_qset अणु
	पूर्णांक		iq_idx;		/* Ingress index */
	पूर्णांक		eq_idx;		/* Egress index */
	uपूर्णांक32_t	पूर्णांकr_idx;	/* MSIX Vector index */
पूर्ण;

काष्ठा csio_scsi_cpu_info अणु
	पूर्णांक16_t	max_cpus;
पूर्ण;

बाह्य पूर्णांक csio_dbg_level;
बाह्य अचिन्हित पूर्णांक csio_port_mask;
बाह्य पूर्णांक csio_msi;

#घोषणा CSIO_VENDOR_ID				0x1425
#घोषणा CSIO_ASIC_DEVID_PROTO_MASK		0xFF00
#घोषणा CSIO_ASIC_DEVID_TYPE_MASK		0x00FF

#घोषणा CSIO_GLBL_INTR_MASK	(CIM_F | MPS_F | PL_F | PCIE_F | MC_F | \
				 EDC0_F | EDC1_F | LE_F | TP_F | MA_F | \
				 PM_TX_F | PM_RX_F | ULP_RX_F | \
				 CPL_SWITCH_F | SGE_F | ULP_TX_F | SF_F)

/*
 * Hard parameters used to initialize the card in the असलence of a
 * configuration file.
 */
क्रमागत अणु
	/* General */
	CSIO_SGE_DBFIFO_INT_THRESH	= 10,

	CSIO_SGE_RX_DMA_OFFSET		= 2,

	CSIO_SGE_FLBUF_SIZE1		= 65536,
	CSIO_SGE_FLBUF_SIZE2		= 1536,
	CSIO_SGE_FLBUF_SIZE3		= 9024,
	CSIO_SGE_FLBUF_SIZE4		= 9216,
	CSIO_SGE_FLBUF_SIZE5		= 2048,
	CSIO_SGE_FLBUF_SIZE6		= 128,
	CSIO_SGE_FLBUF_SIZE7		= 8192,
	CSIO_SGE_FLBUF_SIZE8		= 16384,

	CSIO_SGE_TIMER_VAL_0		= 5,
	CSIO_SGE_TIMER_VAL_1		= 10,
	CSIO_SGE_TIMER_VAL_2		= 20,
	CSIO_SGE_TIMER_VAL_3		= 50,
	CSIO_SGE_TIMER_VAL_4		= 100,
	CSIO_SGE_TIMER_VAL_5		= 200,

	CSIO_SGE_INT_CNT_VAL_0		= 1,
	CSIO_SGE_INT_CNT_VAL_1		= 4,
	CSIO_SGE_INT_CNT_VAL_2		= 8,
	CSIO_SGE_INT_CNT_VAL_3		= 16,
पूर्ण;

/* Slowpath events */
क्रमागत csio_evt अणु
	CSIO_EVT_FW  = 0,	/* FW event */
	CSIO_EVT_MBX,		/* MBX event */
	CSIO_EVT_SCN,		/* State change notअगरication */
	CSIO_EVT_DEV_LOSS,	/* Device loss event */
	CSIO_EVT_MAX,		/* Max supported event */
पूर्ण;

#घोषणा CSIO_EVT_MSG_SIZE	512
#घोषणा CSIO_EVTQ_SIZE		512

/* Event msg  */
काष्ठा csio_evt_msg अणु
	काष्ठा list_head	list;	/* evt queue*/
	क्रमागत csio_evt		type;
	uपूर्णांक8_t			data[CSIO_EVT_MSG_SIZE];
पूर्ण;

क्रमागत अणु
	SERNUM_LEN     = 16,    /* Serial # length */
	EC_LEN         = 16,    /* E/C length */
	ID_LEN         = 16,    /* ID length */
पूर्ण;

क्रमागत अणु
	SF_SIZE = SF_SEC_SIZE * 16,   /* serial flash size */
पूर्ण;

/* serial flash and firmware स्थिरants */
क्रमागत अणु
	SF_ATTEMPTS = 10,             /* max retries क्रम SF operations */

	/* flash command opcodes */
	SF_PROG_PAGE    = 2,          /* program page */
	SF_WR_DISABLE   = 4,          /* disable ग_लिखोs */
	SF_RD_STATUS    = 5,          /* पढ़ो status रेजिस्टर */
	SF_WR_ENABLE    = 6,          /* enable ग_लिखोs */
	SF_RD_DATA_FAST = 0xb,        /* पढ़ो flash */
	SF_RD_ID	= 0x9f,	      /* पढ़ो ID */
	SF_ERASE_SECTOR = 0xd8,       /* erase sector */
पूर्ण;

/* Management module */
क्रमागत अणु
	CSIO_MGMT_EQ_WRSIZE = 512,
	CSIO_MGMT_IQ_WRSIZE = 128,
	CSIO_MGMT_EQLEN = 64,
	CSIO_MGMT_IQLEN = 64,
पूर्ण;

#घोषणा CSIO_MGMT_EQSIZE	(CSIO_MGMT_EQLEN * CSIO_MGMT_EQ_WRSIZE)
#घोषणा CSIO_MGMT_IQSIZE	(CSIO_MGMT_IQLEN * CSIO_MGMT_IQ_WRSIZE)

/* mgmt module stats */
काष्ठा csio_mgmपंचांग_stats अणु
	uपूर्णांक32_t	n_पात_req;		/* Total पात request */
	uपूर्णांक32_t	n_पात_rsp;		/* Total पात response */
	uपूर्णांक32_t	n_बंद_req;		/* Total बंद request */
	uपूर्णांक32_t	n_बंद_rsp;		/* Total बंद response */
	uपूर्णांक32_t	n_err;			/* Total Errors */
	uपूर्णांक32_t	n_drop;			/* Total request dropped */
	uपूर्णांक32_t	n_active;		/* Count of active_q */
	uपूर्णांक32_t	n_cbfn;			/* Count of cbfn_q */
पूर्ण;

/* MGMT module */
काष्ठा csio_mgmपंचांग अणु
	काष्ठा	csio_hw		*hw;		/* Poपूर्णांकer to HW moduel */
	पूर्णांक			eq_idx;		/* Egress queue index */
	पूर्णांक			iq_idx;		/* Ingress queue index */
	पूर्णांक			msi_vec;	/* MSI vector */
	काष्ठा list_head	active_q;	/* Outstanding ELS/CT */
	काष्ठा list_head	पात_q;	/* Outstanding पात req */
	काष्ठा list_head	cbfn_q;		/* Completion queue */
	काष्ठा list_head	mgmt_req_मुक्तlist; /* Free poll of reqs */
						/* ELSCT request मुक्तlist*/
	काष्ठा समयr_list	mgmt_समयr;	/* MGMT समयr */
	काष्ठा csio_mgmपंचांग_stats stats;		/* ELS/CT stats */
पूर्ण;

काष्ठा csio_adap_desc अणु
	अक्षर model_no[16];
	अक्षर description[32];
पूर्ण;

काष्ठा pci_params अणु
	uपूर्णांक16_t   venकरोr_id;
	uपूर्णांक16_t   device_id;
	पूर्णांक        vpd_cap_addr;
	uपूर्णांक16_t   speed;
	uपूर्णांक8_t    width;
पूर्ण;

/* User configurable hw parameters */
काष्ठा csio_hw_params अणु
	uपूर्णांक32_t		sf_size;		/* serial flash
							 * size in bytes
							 */
	uपूर्णांक32_t		sf_nsec;		/* # of flash sectors */
	काष्ठा pci_params	pci;
	uपूर्णांक32_t		log_level;		/* Module-level क्रम
							 * debug log.
							 */
पूर्ण;

काष्ठा csio_vpd अणु
	uपूर्णांक32_t cclk;
	uपूर्णांक8_t ec[EC_LEN + 1];
	uपूर्णांक8_t sn[SERNUM_LEN + 1];
	uपूर्णांक8_t id[ID_LEN + 1];
पूर्ण;

/* Firmware Port Capabilities types. */

प्रकार u16 fw_port_cap16_t;    /* 16-bit Port Capabilities पूर्णांकegral value */
प्रकार u32 fw_port_cap32_t;    /* 32-bit Port Capabilities पूर्णांकegral value */

क्रमागत fw_caps अणु
	FW_CAPS_UNKNOWN = 0,    /* 0'ed out initial state */
	FW_CAPS16       = 1,    /* old Firmware: 16-bit Port Capabilities */
	FW_CAPS32       = 2,    /* new Firmware: 32-bit Port Capabilities */
पूर्ण;

क्रमागत cc_छोड़ो अणु
	PAUSE_RX      = 1 << 0,
	PAUSE_TX      = 1 << 1,
	PAUSE_AUTONEG = 1 << 2
पूर्ण;

क्रमागत cc_fec अणु
	FEC_AUTO	= 1 << 0,  /* IEEE 802.3 "automatic" */
	FEC_RS		= 1 << 1,  /* Reed-Solomon */
	FEC_BASER_RS	= 1 << 2   /* BaseR/Reed-Solomon */
पूर्ण;

काष्ठा link_config अणु
	fw_port_cap32_t pcaps;		/* link capabilities */
	fw_port_cap32_t def_acaps;	/* शेष advertised capabilities */
	fw_port_cap32_t acaps;		/* advertised capabilities */
	fw_port_cap32_t lpacaps;	/* peer advertised capabilities */

	fw_port_cap32_t speed_caps;	/* speed(s) user has requested */
	अचिन्हित पूर्णांक   speed;		/* actual link speed (Mb/s) */

	क्रमागत cc_छोड़ो  requested_fc;	/* flow control user has requested */
	क्रमागत cc_छोड़ो  fc;		/* actual link flow control */

	क्रमागत cc_fec    requested_fec;	/* Forward Error Correction: */
	क्रमागत cc_fec    fec;		/* requested and actual in use */

	अचिन्हित अक्षर  स्वतःneg;		/* स्वतःnegotiating? */

	अचिन्हित अक्षर  link_ok;		/* link up? */
	अचिन्हित अक्षर  link_करोwn_rc;	/* link करोwn reason */
पूर्ण;

#घोषणा FW_LEN16(fw_काष्ठा) FW_CMD_LEN16_V(माप(fw_काष्ठा) / 16)

#घोषणा ADVERT_MASK (FW_PORT_CAP32_SPEED_V(FW_PORT_CAP32_SPEED_M) | \
		     FW_PORT_CAP32_ANEG)

/* Enable or disable स्वतःnegotiation. */
#घोषणा AUTONEG_DISABLE	0x00
#घोषणा AUTONEG_ENABLE	0x01

काष्ठा csio_pport अणु
	uपूर्णांक16_t	pcap;
	uपूर्णांक16_t	acap;
	uपूर्णांक8_t		portid;
	uपूर्णांक8_t		link_status;
	uपूर्णांक16_t	link_speed;
	uपूर्णांक8_t		mac[6];
	uपूर्णांक8_t		mod_type;
	uपूर्णांक8_t		rsvd1;
	uपूर्णांक8_t		rsvd2;
	uपूर्णांक8_t		rsvd3;
	काष्ठा link_config link_cfg;
पूर्ण;

/* fcoe resource inक्रमmation */
काष्ठा csio_fcoe_res_info अणु
	uपूर्णांक16_t	e_d_tov;
	uपूर्णांक16_t	r_a_tov_seq;
	uपूर्णांक16_t	r_a_tov_els;
	uपूर्णांक16_t	r_r_tov;
	uपूर्णांक32_t	max_xchgs;
	uपूर्णांक32_t	max_ssns;
	uपूर्णांक32_t	used_xchgs;
	uपूर्णांक32_t	used_ssns;
	uपूर्णांक32_t	max_fcfs;
	uपूर्णांक32_t	max_vnps;
	uपूर्णांक32_t	used_fcfs;
	uपूर्णांक32_t	used_vnps;
पूर्ण;

/* HW State machine Events */
क्रमागत csio_hw_ev अणु
	CSIO_HWE_CFG = (uपूर्णांक32_t)1, /* Starts off the State machine */
	CSIO_HWE_INIT,	         /* Config करोne, start Init      */
	CSIO_HWE_INIT_DONE,      /* Init Mailboxes sent, HW पढ़ोy */
	CSIO_HWE_FATAL,		 /* Fatal error during initialization */
	CSIO_HWE_PCIERR_DETECTED,/* PCI error recovery detetced */
	CSIO_HWE_PCIERR_SLOT_RESET, /* Slot reset after PCI recoviery */
	CSIO_HWE_PCIERR_RESUME,  /* Resume after PCI error recovery */
	CSIO_HWE_QUIESCED,	 /* HBA quiesced */
	CSIO_HWE_HBA_RESET,      /* HBA reset requested */
	CSIO_HWE_HBA_RESET_DONE, /* HBA reset completed */
	CSIO_HWE_FW_DLOAD,       /* FW करोwnload requested */
	CSIO_HWE_PCI_REMOVE,     /* PCI de-instantiation */
	CSIO_HWE_SUSPEND,        /* HW suspend क्रम Online(hot) replacement */
	CSIO_HWE_RESUME,         /* HW resume क्रम Online(hot) replacement */
	CSIO_HWE_MAX,		 /* Max HW event */
पूर्ण;

/* hw stats */
काष्ठा csio_hw_stats अणु
	uपूर्णांक32_t	n_evt_activeq;	/* Number of event in active Q */
	uपूर्णांक32_t	n_evt_मुक्तq;	/* Number of event in मुक्त Q */
	uपूर्णांक32_t	n_evt_drop;	/* Number of event droped */
	uपूर्णांक32_t	n_evt_unexp;	/* Number of unexpected events */
	uपूर्णांक32_t	n_pcich_offline;/* Number of pci channel offline */
	uपूर्णांक32_t	n_lnlkup_miss;  /* Number of lnode lookup miss */
	uपूर्णांक32_t	n_cpl_fw6_msg;	/* Number of cpl fw6 message*/
	uपूर्णांक32_t	n_cpl_fw6_pld;	/* Number of cpl fw6 payload*/
	uपूर्णांक32_t	n_cpl_unexp;	/* Number of unexpected cpl */
	uपूर्णांक32_t	n_mbपूर्णांक_unexp;	/* Number of unexpected mbox */
					/* पूर्णांकerrupt */
	uपूर्णांक32_t	n_plपूर्णांक_unexp;	/* Number of unexpected PL */
					/* पूर्णांकerrupt */
	uपूर्णांक32_t	n_plपूर्णांक_cnt;	/* Number of PL पूर्णांकerrupt */
	uपूर्णांक32_t	n_पूर्णांक_stray;	/* Number of stray पूर्णांकerrupt */
	uपूर्णांक32_t	n_err;		/* Number of hw errors */
	uपूर्णांक32_t	n_err_fatal;	/* Number of fatal errors */
	uपूर्णांक32_t	n_err_nomem;	/* Number of memory alloc failure */
	uपूर्णांक32_t	n_err_io;	/* Number of IO failure */
	क्रमागत csio_hw_ev	n_evt_sm[CSIO_HWE_MAX];	/* Number of sm events */
	uपूर्णांक64_t	n_reset_start;  /* Start समय after the reset */
	uपूर्णांक32_t	rsvd1;
पूर्ण;

/* Defines क्रम hw->flags */
#घोषणा CSIO_HWF_MASTER			0x00000001	/* This is the Master
							 * function क्रम the
							 * card.
							 */
#घोषणा	CSIO_HWF_HW_INTR_ENABLED	0x00000002	/* Are HW Interrupt
							 * enable bit set?
							 */
#घोषणा	CSIO_HWF_FWEVT_PENDING		0x00000004	/* FW events pending */
#घोषणा	CSIO_HWF_Q_MEM_ALLOCED		0x00000008	/* Queues have been
							 * allocated memory.
							 */
#घोषणा	CSIO_HWF_Q_FW_ALLOCED		0x00000010	/* Queues have been
							 * allocated in FW.
							 */
#घोषणा CSIO_HWF_VPD_VALID		0x00000020	/* Valid VPD copied */
#घोषणा CSIO_HWF_DEVID_CACHED		0X00000040	/* PCI venकरोr & device
							 * id cached */
#घोषणा	CSIO_HWF_FWEVT_STOP		0x00000080	/* Stop processing
							 * FW events
							 */
#घोषणा CSIO_HWF_USING_SOFT_PARAMS	0x00000100      /* Using FW config
							 * params
							 */
#घोषणा	CSIO_HWF_HOST_INTR_ENABLED	0x00000200	/* Are host पूर्णांकerrupts
							 * enabled?
							 */
#घोषणा CSIO_HWF_ROOT_NO_RELAXED_ORDERING 0x00000400	/* Is PCIe relaxed
							 * ordering enabled
							 */

#घोषणा csio_is_hw_पूर्णांकr_enabled(__hw)	\
				((__hw)->flags & CSIO_HWF_HW_INTR_ENABLED)
#घोषणा csio_is_host_पूर्णांकr_enabled(__hw)	\
				((__hw)->flags & CSIO_HWF_HOST_INTR_ENABLED)
#घोषणा csio_is_hw_master(__hw)		((__hw)->flags & CSIO_HWF_MASTER)
#घोषणा csio_is_valid_vpd(__hw)		((__hw)->flags & CSIO_HWF_VPD_VALID)
#घोषणा csio_is_dev_id_cached(__hw)	((__hw)->flags & CSIO_HWF_DEVID_CACHED)
#घोषणा csio_valid_vpd_copied(__hw)	((__hw)->flags |= CSIO_HWF_VPD_VALID)
#घोषणा csio_dev_id_cached(__hw)	((__hw)->flags |= CSIO_HWF_DEVID_CACHED)

/* Defines क्रम पूर्णांकr_mode */
क्रमागत csio_पूर्णांकr_mode अणु
	CSIO_IM_NONE = 0,
	CSIO_IM_INTX = 1,
	CSIO_IM_MSI  = 2,
	CSIO_IM_MSIX = 3,
पूर्ण;

/* Master HW काष्ठाure: One per function */
काष्ठा csio_hw अणु
	काष्ठा csio_sm		sm;			/* State machine: should
							 * be the 1st member.
							 */
	spinlock_t		lock;			/* Lock क्रम hw */

	काष्ठा csio_scsim	scsim;			/* SCSI module*/
	काष्ठा csio_wrm		wrm;			/* Work request module*/
	काष्ठा pci_dev		*pdev;			/* PCI device */

	व्योम __iomem		*regstart;		/* Virtual address of
							 * रेजिस्टर map
							 */
	/* SCSI queue sets */
	uपूर्णांक32_t		num_sqsets;		/* Number of SCSI
							 * queue sets */
	uपूर्णांक32_t		num_scsi_msix_cpus;	/* Number of CPUs that
							 * will be used
							 * क्रम ingress
							 * processing.
							 */

	काष्ठा csio_scsi_qset	sqset[CSIO_MAX_PPORTS][CSIO_MAX_SCSI_CPU];
	काष्ठा csio_scsi_cpu_info scsi_cpu_info[CSIO_MAX_PPORTS];

	uपूर्णांक32_t		evtflag;		/* Event flag  */
	uपूर्णांक32_t		flags;			/* HW flags */

	काष्ठा csio_mgmपंचांग	mgmपंचांग;			/* management module */
	काष्ठा csio_mbm		mbm;			/* Mailbox module */

	/* Lnodes */
	uपूर्णांक32_t		num_lns;		/* Number of lnodes */
	काष्ठा csio_lnode	*rln;			/* Root lnode */
	काष्ठा list_head	sln_head;		/* Sibling node list
							 * list
							 */
	पूर्णांक			पूर्णांकr_iq_idx;		/* Forward पूर्णांकerrupt
							 * queue.
							 */
	पूर्णांक			fwevt_iq_idx;		/* FW evt queue */
	काष्ठा work_काष्ठा	evtq_work;		/* Worker thपढ़ो क्रम
							 * HW events.
							 */
	काष्ठा list_head	evt_मुक्त_q;		/* मुक्तlist of evt
							 * elements
							 */
	काष्ठा list_head	evt_active_q;		/* active evt queue*/

	/* board related info */
	अक्षर			name[32];
	अक्षर			hw_ver[16];
	अक्षर			model_desc[32];
	अक्षर			drv_version[32];
	अक्षर			fwrev_str[32];
	uपूर्णांक32_t		optrom_ver;
	uपूर्णांक32_t		fwrev;
	uपूर्णांक32_t		tp_vers;
	अक्षर			chip_ver;
	uपूर्णांक16_t		chip_id;		/* Tells T4/T5 chip */
	क्रमागत csio_dev_state	fw_state;
	काष्ठा csio_vpd		vpd;

	uपूर्णांक8_t			pfn;			/* Physical Function
							 * number
							 */
	uपूर्णांक32_t		port_vec;		/* Port vector */
	uपूर्णांक8_t			num_pports;		/* Number of physical
							 * ports.
							 */
	uपूर्णांक8_t			rst_retries;		/* Reset retries */
	uपूर्णांक8_t			cur_evt;		/* current s/m evt */
	uपूर्णांक8_t			prev_evt;		/* Previous s/m evt */
	uपूर्णांक32_t		dev_num;		/* device number */
	काष्ठा csio_pport	pport[CSIO_MAX_PPORTS];	/* Ports (XGMACs) */
	काष्ठा csio_hw_params	params;			/* Hw parameters */

	काष्ठा dma_pool		*scsi_dma_pool;		/* DMA pool क्रम SCSI */
	mempool_t		*mb_mempool;		/* Mailbox memory pool*/
	mempool_t		*rnode_mempool;		/* rnode memory pool */

	/* Interrupt */
	क्रमागत csio_पूर्णांकr_mode	पूर्णांकr_mode;		/* INTx, MSI, MSIX */
	uपूर्णांक32_t		fwevt_पूर्णांकr_idx;		/* FW evt MSIX/पूर्णांकerrupt
							 * index
							 */
	uपूर्णांक32_t		nondata_पूर्णांकr_idx;	/* nondata MSIX/पूर्णांकr
							 * idx
							 */

	uपूर्णांक8_t			cfg_neq;		/* FW configured no of
							 * egress queues
							 */
	uपूर्णांक8_t			cfg_niq;		/* FW configured no of
							 * iq queues.
							 */

	काष्ठा csio_fcoe_res_info  fres_info;		/* Fcoe resource info */
	काष्ठा csio_hw_chip_ops	*chip_ops;		/* T4/T5 Chip specअगरic
							 * Operations
							 */

	/* MSIX vectors */
	काष्ठा csio_msix_entries msix_entries[CSIO_MAX_MSIX_VECS];

	काष्ठा dentry		*debugfs_root;		/* Debug FS */
	काष्ठा csio_hw_stats	stats;			/* Hw statistics */
पूर्ण;

/* Register access macros */
#घोषणा csio_reg(_b, _r)		((_b) + (_r))

#घोषणा	csio_rd_reg8(_h, _r)		पढ़ोb(csio_reg((_h)->regstart, (_r)))
#घोषणा	csio_rd_reg16(_h, _r)		पढ़ोw(csio_reg((_h)->regstart, (_r)))
#घोषणा	csio_rd_reg32(_h, _r)		पढ़ोl(csio_reg((_h)->regstart, (_r)))
#घोषणा	csio_rd_reg64(_h, _r)		पढ़ोq(csio_reg((_h)->regstart, (_r)))

#घोषणा	csio_wr_reg8(_h, _v, _r)	ग_लिखोb((_v), \
						csio_reg((_h)->regstart, (_r)))
#घोषणा	csio_wr_reg16(_h, _v, _r)	ग_लिखोw((_v), \
						csio_reg((_h)->regstart, (_r)))
#घोषणा	csio_wr_reg32(_h, _v, _r)	ग_लिखोl((_v), \
						csio_reg((_h)->regstart, (_r)))
#घोषणा	csio_wr_reg64(_h, _v, _r)	ग_लिखोq((_v), \
						csio_reg((_h)->regstart, (_r)))

व्योम csio_set_reg_field(काष्ठा csio_hw *, uपूर्णांक32_t, uपूर्णांक32_t, uपूर्णांक32_t);

/* Core घड़ीs <==> uSecs */
अटल अंतरभूत uपूर्णांक32_t
csio_core_ticks_to_us(काष्ठा csio_hw *hw, uपूर्णांक32_t ticks)
अणु
	/* add Core Clock / 2 to round ticks to nearest uS */
	वापस (ticks * 1000 + hw->vpd.cclk/2) / hw->vpd.cclk;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
csio_us_to_core_ticks(काष्ठा csio_hw *hw, uपूर्णांक32_t us)
अणु
	वापस (us * hw->vpd.cclk) / 1000;
पूर्ण

/* Easy access macros */
#घोषणा csio_hw_to_wrm(hw)		((काष्ठा csio_wrm *)(&(hw)->wrm))
#घोषणा csio_hw_to_mbm(hw)		((काष्ठा csio_mbm *)(&(hw)->mbm))
#घोषणा csio_hw_to_scsim(hw)		((काष्ठा csio_scsim *)(&(hw)->scsim))
#घोषणा csio_hw_to_mgmपंचांग(hw)		((काष्ठा csio_mgmपंचांग *)(&(hw)->mgmपंचांग))

#घोषणा CSIO_PCI_BUS(hw)		((hw)->pdev->bus->number)
#घोषणा CSIO_PCI_DEV(hw)		(PCI_SLOT((hw)->pdev->devfn))
#घोषणा CSIO_PCI_FUNC(hw)		(PCI_FUNC((hw)->pdev->devfn))

#घोषणा csio_set_fwevt_पूर्णांकr_idx(_h, _i)		((_h)->fwevt_पूर्णांकr_idx = (_i))
#घोषणा csio_get_fwevt_पूर्णांकr_idx(_h)		((_h)->fwevt_पूर्णांकr_idx)
#घोषणा csio_set_nondata_पूर्णांकr_idx(_h, _i)	((_h)->nondata_पूर्णांकr_idx = (_i))
#घोषणा csio_get_nondata_पूर्णांकr_idx(_h)		((_h)->nondata_पूर्णांकr_idx)

/* Prपूर्णांकing/logging */
#घोषणा CSIO_DEVID(__dev)		((__dev)->dev_num)
#घोषणा CSIO_DEVID_LO(__dev)		(CSIO_DEVID((__dev)) & 0xFFFF)
#घोषणा CSIO_DEVID_HI(__dev)		((CSIO_DEVID((__dev)) >> 16) & 0xFFFF)

#घोषणा csio_info(__hw, __fmt, ...)					\
			dev_info(&(__hw)->pdev->dev, __fmt, ##__VA_ARGS__)

#घोषणा csio_fatal(__hw, __fmt, ...)					\
			dev_crit(&(__hw)->pdev->dev, __fmt, ##__VA_ARGS__)

#घोषणा csio_err(__hw, __fmt, ...)					\
			dev_err(&(__hw)->pdev->dev, __fmt, ##__VA_ARGS__)

#घोषणा csio_warn(__hw, __fmt, ...)					\
			dev_warn(&(__hw)->pdev->dev, __fmt, ##__VA_ARGS__)

#अगर_घोषित __CSIO_DEBUG__
#घोषणा csio_dbg(__hw, __fmt, ...)					\
			csio_info((__hw), __fmt, ##__VA_ARGS__);
#अन्यथा
#घोषणा csio_dbg(__hw, __fmt, ...)
#पूर्ण_अगर

पूर्णांक csio_hw_रुको_op_करोne_val(काष्ठा csio_hw *, पूर्णांक, uपूर्णांक32_t, पूर्णांक,
			     पूर्णांक, पूर्णांक, uपूर्णांक32_t *);
व्योम csio_hw_tp_wr_bits_indirect(काष्ठा csio_hw *, अचिन्हित पूर्णांक,
				 अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
पूर्णांक csio_mgmt_req_lookup(काष्ठा csio_mgmपंचांग *, काष्ठा csio_ioreq *);
व्योम csio_hw_पूर्णांकr_disable(काष्ठा csio_hw *);
पूर्णांक csio_hw_slow_पूर्णांकr_handler(काष्ठा csio_hw *);
पूर्णांक csio_handle_पूर्णांकr_status(काष्ठा csio_hw *, अचिन्हित पूर्णांक,
			    स्थिर काष्ठा पूर्णांकr_info *);

fw_port_cap32_t fwcap_to_fwspeed(fw_port_cap32_t acaps);
fw_port_cap32_t fwcaps16_to_caps32(fw_port_cap16_t caps16);
fw_port_cap16_t fwcaps32_to_caps16(fw_port_cap32_t caps32);
fw_port_cap32_t lstatus_to_fwcap(u32 lstatus);

पूर्णांक csio_hw_start(काष्ठा csio_hw *);
पूर्णांक csio_hw_stop(काष्ठा csio_hw *);
पूर्णांक csio_hw_reset(काष्ठा csio_hw *);
पूर्णांक csio_is_hw_पढ़ोy(काष्ठा csio_hw *);
पूर्णांक csio_is_hw_removing(काष्ठा csio_hw *);

पूर्णांक csio_fwevtq_handler(काष्ठा csio_hw *);
व्योम csio_evtq_worker(काष्ठा work_काष्ठा *);
पूर्णांक csio_enqueue_evt(काष्ठा csio_hw *, क्रमागत csio_evt, व्योम *, uपूर्णांक16_t);
व्योम csio_evtq_flush(काष्ठा csio_hw *hw);

पूर्णांक csio_request_irqs(काष्ठा csio_hw *);
व्योम csio_पूर्णांकr_enable(काष्ठा csio_hw *);
व्योम csio_पूर्णांकr_disable(काष्ठा csio_hw *, bool);
व्योम csio_hw_fatal_err(काष्ठा csio_hw *);

काष्ठा csio_lnode *csio_lnode_alloc(काष्ठा csio_hw *);
पूर्णांक csio_config_queues(काष्ठा csio_hw *);

पूर्णांक csio_hw_init(काष्ठा csio_hw *);
व्योम csio_hw_निकास(काष्ठा csio_hw *);
#पूर्ण_अगर /* अगरndef __CSIO_HW_H__ */
