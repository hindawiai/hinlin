<शैली गुरु>
#अगर_अघोषित _QIB_KERNEL_H
#घोषणा _QIB_KERNEL_H
/*
 * Copyright (c) 2012 - 2017 Intel Corporation.  All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
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

/*
 * This header file is the base header file क्रम qlogic_ib kernel code
 * qib_user.h serves a similar purpose क्रम user code.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/fs.h>
#समावेश <linux/completion.h>
#समावेश <linux/kref.h>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/xarray.h>
#समावेश <rdma/ib_hdrs.h>
#समावेश <rdma/rdma_vt.h>

#समावेश "qib_common.h"
#समावेश "qib_verbs.h"

/* only s/w major version of QLogic_IB we can handle */
#घोषणा QIB_CHIP_VERS_MAJ 2U

/* करोn't care about this except prपूर्णांकing */
#घोषणा QIB_CHIP_VERS_MIN 0U

/* The Organization Unique Identअगरier (Mfg code), and its position in GUID */
#घोषणा QIB_OUI 0x001175
#घोषणा QIB_OUI_LSB 40

/*
 * per driver stats, either not device nor port-specअगरic, or
 * summed over all of the devices and ports.
 * They are described by name via ipathfs fileप्रणाली, so layout
 * and number of elements can change without अवरोधing compatibility.
 * If members are added or deleted qib_statnames[] in qib_fs.c must
 * change to match.
 */
काष्ठा qlogic_ib_stats अणु
	__u64 sps_पूर्णांकs; /* number of पूर्णांकerrupts handled */
	__u64 sps_errपूर्णांकs; /* number of error पूर्णांकerrupts */
	__u64 sps_txerrs; /* tx-related packet errors */
	__u64 sps_rcverrs; /* non-crc rcv packet errors */
	__u64 sps_hwerrs; /* hardware errors reported (parity, etc.) */
	__u64 sps_nopiobufs; /* no pio bufs avail from kernel */
	__u64 sps_ctxts; /* number of contexts currently खोलो */
	__u64 sps_lenerrs; /* number of kernel packets where RHF != LRH len */
	__u64 sps_buffull;
	__u64 sps_hdrfull;
पूर्ण;

बाह्य काष्ठा qlogic_ib_stats qib_stats;
बाह्य स्थिर काष्ठा pci_error_handlers qib_pci_err_handler;

#घोषणा QIB_CHIP_SWVERSION QIB_CHIP_VERS_MAJ
/*
 * First-cut critierion क्रम "device is active" is
 * two thousand dwords combined Tx, Rx traffic per
 * 5-second पूर्णांकerval. SMA packets are 64 dwords,
 * and occur "a few per second", presumably each way.
 */
#घोषणा QIB_TRAFFIC_ACTIVE_THRESHOLD (2000)

/*
 * Below contains all data related to a single context (क्रमmerly called port).
 */

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा qib_opcode_stats_perctx;
#पूर्ण_अगर

काष्ठा qib_ctxtdata अणु
	व्योम **rcvegrbuf;
	dma_addr_t *rcvegrbuf_phys;
	/* rcvhdrq base, needs mmap beक्रमe useful */
	व्योम *rcvhdrq;
	/* kernel भव address where hdrqtail is updated */
	व्योम *rcvhdrtail_kvaddr;
	/*
	 * temp buffer क्रम expected send setup, allocated at खोलो, instead
	 * of each setup call
	 */
	व्योम *tid_pg_list;
	/*
	 * Shared page क्रम kernel to संकेत user processes that send buffers
	 * need disarming.  The process should call QIB_CMD_DISARM_BUFS
	 * or QIB_CMD_ACK_EVENT with IPATH_EVENT_DISARM_BUFS set.
	 */
	अचिन्हित दीर्घ *user_event_mask;
	/* when रुकोing क्रम rcv or pioavail */
	रुको_queue_head_t रुको;
	/*
	 * rcvegr bufs base, physical, must fit
	 * in 44 bits so 32 bit programs mmap64 44 bit works)
	 */
	dma_addr_t rcvegr_phys;
	/* mmap of hdrq, must fit in 44 bits */
	dma_addr_t rcvhdrq_phys;
	dma_addr_t rcvhdrqtailaddr_phys;

	/*
	 * number of खोलोs (including slave sub-contexts) on this instance
	 * (ignoring विभाजनs, dup, etc. क्रम now)
	 */
	पूर्णांक cnt;
	/*
	 * how much space to leave at start of eager TID entries क्रम
	 * protocol use, on each TID
	 */
	/* instead of calculating it */
	अचिन्हित ctxt;
	/* local node of context */
	पूर्णांक node_id;
	/* non-zero अगर ctxt is being shared. */
	u16 subctxt_cnt;
	/* non-zero अगर ctxt is being shared. */
	u16 subctxt_id;
	/* number of eager TID entries. */
	u16 rcvegrcnt;
	/* index of first eager TID entry. */
	u16 rcvegr_tid_base;
	/* number of pio bufs क्रम this ctxt (all procs, अगर shared) */
	u32 piocnt;
	/* first pio buffer क्रम this ctxt */
	u32 pio_base;
	/* chip offset of PIO buffers क्रम this ctxt */
	u32 piobufs;
	/* how many alloc_pages() chunks in rcvegrbuf_pages */
	u32 rcvegrbuf_chunks;
	/* how many egrbufs per chunk */
	u16 rcvegrbufs_perchunk;
	/* ilog2 of above */
	u16 rcvegrbufs_perchunk_shअगरt;
	/* order क्रम rcvegrbuf_pages */
	माप_प्रकार rcvegrbuf_size;
	/* rcvhdrq size (क्रम मुक्तing) */
	माप_प्रकार rcvhdrq_size;
	/* per-context flags क्रम fileops/पूर्णांकr communication */
	अचिन्हित दीर्घ flag;
	/* next expected TID to check when looking क्रम मुक्त */
	u32 tidcursor;
	/* WAIT_RCV that समयd out, no पूर्णांकerrupt */
	u32 rcvरुको_to;
	/* WAIT_PIO that समयd out, no पूर्णांकerrupt */
	u32 pioरुको_to;
	/* WAIT_RCV alपढ़ोy happened, no रुको */
	u32 rcvnoरुको;
	/* WAIT_PIO alपढ़ोy happened, no रुको */
	u32 pionoरुको;
	/* total number of polled urgent packets */
	u32 urgent;
	/* saved total number of polled urgent packets क्रम poll edge trigger */
	u32 urgent_poll;
	/* pid of process using this ctxt */
	pid_t pid;
	pid_t subpid[QLOGIC_IB_MAX_SUBCTXT];
	/* same size as task_काष्ठा .comm[], command that खोलोed context */
	अक्षर comm[16];
	/* pkeys set by this use of this ctxt */
	u16 pkeys[4];
	/* so file ops can get at unit */
	काष्ठा qib_devdata *dd;
	/* so funcs that need physical port can get it easily */
	काष्ठा qib_pportdata *ppd;
	/* A page of memory क्रम rcvhdrhead, rcvegrhead, rcvegrtail * N */
	व्योम *subctxt_uregbase;
	/* An array of pages क्रम the eager receive buffers * N */
	व्योम *subctxt_rcvegrbuf;
	/* An array of pages क्रम the eager header queue entries * N */
	व्योम *subctxt_rcvhdr_base;
	/* The version of the library which खोलोed this ctxt */
	u32 userversion;
	/* Biपंचांगask of active slaves */
	u32 active_slaves;
	/* Type of packets or conditions we want to poll क्रम */
	u16 poll_type;
	/* receive packet sequence counter */
	u8 seq_cnt;
	u8 redirect_seq_cnt;
	/* ctxt rcvhdrq head offset */
	u32 head;
	/* QPs रुकोing क्रम context processing */
	काष्ठा list_head qp_रुको_list;
#अगर_घोषित CONFIG_DEBUG_FS
	/* verbs stats per CTX */
	काष्ठा qib_opcode_stats_perctx *opstats;
#पूर्ण_अगर
पूर्ण;

काष्ठा rvt_sge_state;

काष्ठा qib_sdma_txreq अणु
	पूर्णांक                 flags;
	पूर्णांक                 sg_count;
	dma_addr_t          addr;
	व्योम              (*callback)(काष्ठा qib_sdma_txreq *, पूर्णांक);
	u16                 start_idx;  /* sdma निजी */
	u16                 next_descq_idx;  /* sdma निजी */
	काष्ठा list_head    list;       /* sdma निजी */
पूर्ण;

काष्ठा qib_sdma_desc अणु
	__le64 qw[2];
पूर्ण;

काष्ठा qib_verbs_txreq अणु
	काष्ठा qib_sdma_txreq   txreq;
	काष्ठा rvt_qp           *qp;
	काष्ठा rvt_swqe         *wqe;
	u32                     dwords;
	u16                     hdr_dwords;
	u16                     hdr_inx;
	काष्ठा qib_pio_header	*align_buf;
	काष्ठा rvt_mregion	*mr;
	काष्ठा rvt_sge_state    *ss;
पूर्ण;

#घोषणा QIB_SDMA_TXREQ_F_USELARGEBUF  0x1
#घोषणा QIB_SDMA_TXREQ_F_HEADTOHOST   0x2
#घोषणा QIB_SDMA_TXREQ_F_INTREQ       0x4
#घोषणा QIB_SDMA_TXREQ_F_FREEBUF      0x8
#घोषणा QIB_SDMA_TXREQ_F_FREEDESC     0x10

#घोषणा QIB_SDMA_TXREQ_S_OK        0
#घोषणा QIB_SDMA_TXREQ_S_SENDERROR 1
#घोषणा QIB_SDMA_TXREQ_S_ABORTED   2
#घोषणा QIB_SDMA_TXREQ_S_SHUTDOWN  3

/*
 * Get/Set IB link-level config parameters क्रम f_get/set_ib_cfg()
 * Mostly क्रम MADs that set or query link parameters, also ipath
 * config पूर्णांकerfaces
 */
#घोषणा QIB_IB_CFG_LIDLMC 0 /* LID (LS16b) and Mask (MS16b) */
#घोषणा QIB_IB_CFG_LWID_ENB 2 /* allowed Link-width */
#घोषणा QIB_IB_CFG_LWID 3 /* currently active Link-width */
#घोषणा QIB_IB_CFG_SPD_ENB 4 /* allowed Link speeds */
#घोषणा QIB_IB_CFG_SPD 5 /* current Link spd */
#घोषणा QIB_IB_CFG_RXPOL_ENB 6 /* Auto-RX-polarity enable */
#घोषणा QIB_IB_CFG_LREV_ENB 7 /* Auto-Lane-reversal enable */
#घोषणा QIB_IB_CFG_LINKLATENCY 8 /* Link Latency (IB1.2 only) */
#घोषणा QIB_IB_CFG_HRTBT 9 /* IB heartbeat off/enable/स्वतः; DDR/QDR only */
#घोषणा QIB_IB_CFG_OP_VLS 10 /* operational VLs */
#घोषणा QIB_IB_CFG_VL_HIGH_CAP 11 /* num of VL high priority weights */
#घोषणा QIB_IB_CFG_VL_LOW_CAP 12 /* num of VL low priority weights */
#घोषणा QIB_IB_CFG_OVERRUN_THRESH 13 /* IB overrun threshold */
#घोषणा QIB_IB_CFG_PHYERR_THRESH 14 /* IB PHY error threshold */
#घोषणा QIB_IB_CFG_LINKDEFAULT 15 /* IB link शेष (sleep/poll) */
#घोषणा QIB_IB_CFG_PKEYS 16 /* update partition keys */
#घोषणा QIB_IB_CFG_MTU 17 /* update MTU in IBC */
#घोषणा QIB_IB_CFG_LSTATE 18 /* update linkcmd and linkinitcmd in IBC */
#घोषणा QIB_IB_CFG_VL_HIGH_LIMIT 19
#घोषणा QIB_IB_CFG_PMA_TICKS 20 /* PMA sample tick resolution */
#घोषणा QIB_IB_CFG_PORT 21 /* चयन port we are connected to */

/*
 * क्रम CFG_LSTATE: LINKCMD in upper 16 bits, LINKINITCMD in lower 16
 * IB_LINKINITCMD_POLL and SLEEP are also used as set/get values क्रम
 * QIB_IB_CFG_LINKDEFAULT cmd
 */
#घोषणा   IB_LINKCMD_DOWN   (0 << 16)
#घोषणा   IB_LINKCMD_ARMED  (1 << 16)
#घोषणा   IB_LINKCMD_ACTIVE (2 << 16)
#घोषणा   IB_LINKINITCMD_NOP     0
#घोषणा   IB_LINKINITCMD_POLL    1
#घोषणा   IB_LINKINITCMD_SLEEP   2
#घोषणा   IB_LINKINITCMD_DISABLE 3

/*
 * valid states passed to qib_set_linkstate() user call
 */
#घोषणा QIB_IB_LINKDOWN         0
#घोषणा QIB_IB_LINKARM          1
#घोषणा QIB_IB_LINKACTIVE       2
#घोषणा QIB_IB_LINKDOWN_ONLY    3
#घोषणा QIB_IB_LINKDOWN_SLEEP   4
#घोषणा QIB_IB_LINKDOWN_DISABLE 5

/*
 * These 7 values (SDR, DDR, and QDR may be ORed क्रम स्वतः-speed
 * negotiation) are used क्रम the 3rd argument to path_f_set_ib_cfg
 * with cmd QIB_IB_CFG_SPD_ENB, by direct calls or via sysfs.  They
 * are also the the possible values क्रम qib_link_speed_enabled and active
 * The values were chosen to match values used within the IB spec.
 */
#घोषणा QIB_IB_SDR 1
#घोषणा QIB_IB_DDR 2
#घोषणा QIB_IB_QDR 4

#घोषणा QIB_DEFAULT_MTU 4096

/* max number of IB ports supported per HCA */
#घोषणा QIB_MAX_IB_PORTS 2

/*
 * Possible IB config parameters क्रम f_get/set_ib_table()
 */
#घोषणा QIB_IB_TBL_VL_HIGH_ARB 1 /* Get/set VL high priority weights */
#घोषणा QIB_IB_TBL_VL_LOW_ARB 2 /* Get/set VL low priority weights */

/*
 * Possible "operations" क्रम f_rcvctrl(ppd, op, ctxt)
 * these are bits so they can be combined, e.g.
 * QIB_RCVCTRL_INTRAVAIL_ENB | QIB_RCVCTRL_CTXT_ENB
 */
#घोषणा QIB_RCVCTRL_TAILUPD_ENB 0x01
#घोषणा QIB_RCVCTRL_TAILUPD_DIS 0x02
#घोषणा QIB_RCVCTRL_CTXT_ENB 0x04
#घोषणा QIB_RCVCTRL_CTXT_DIS 0x08
#घोषणा QIB_RCVCTRL_INTRAVAIL_ENB 0x10
#घोषणा QIB_RCVCTRL_INTRAVAIL_DIS 0x20
#घोषणा QIB_RCVCTRL_PKEY_ENB 0x40  /* Note, शेष is enabled */
#घोषणा QIB_RCVCTRL_PKEY_DIS 0x80
#घोषणा QIB_RCVCTRL_BP_ENB 0x0100
#घोषणा QIB_RCVCTRL_BP_DIS 0x0200
#घोषणा QIB_RCVCTRL_TIDFLOW_ENB 0x0400
#घोषणा QIB_RCVCTRL_TIDFLOW_DIS 0x0800

/*
 * Possible "operations" क्रम f_sendctrl(ppd, op, var)
 * these are bits so they can be combined, e.g.
 * QIB_SENDCTRL_BUFAVAIL_ENB | QIB_SENDCTRL_ENB
 * Some operations (e.g. DISARM, ABORT) are known to
 * be "one-shot", so करो not modअगरy shaकरोw.
 */
#घोषणा QIB_SENDCTRL_DISARM       (0x1000)
#घोषणा QIB_SENDCTRL_DISARM_BUF(bufn) ((bufn) | QIB_SENDCTRL_DISARM)
	/* available (0x2000) */
#घोषणा QIB_SENDCTRL_AVAIL_DIS    (0x4000)
#घोषणा QIB_SENDCTRL_AVAIL_ENB    (0x8000)
#घोषणा QIB_SENDCTRL_AVAIL_BLIP  (0x10000)
#घोषणा QIB_SENDCTRL_SEND_DIS    (0x20000)
#घोषणा QIB_SENDCTRL_SEND_ENB    (0x40000)
#घोषणा QIB_SENDCTRL_FLUSH       (0x80000)
#घोषणा QIB_SENDCTRL_CLEAR      (0x100000)
#घोषणा QIB_SENDCTRL_DISARM_ALL (0x200000)

/*
 * These are the generic indices क्रम requesting per-port
 * counter values via the f_portcntr function.  They
 * are always वापसed as 64 bit values, although most
 * are 32 bit counters.
 */
/* send-related counters */
#घोषणा QIBPORTCNTR_PKTSEND         0U
#घोषणा QIBPORTCNTR_WORDSEND        1U
#घोषणा QIBPORTCNTR_PSXMITDATA      2U
#घोषणा QIBPORTCNTR_PSXMITPKTS      3U
#घोषणा QIBPORTCNTR_PSXMITWAIT      4U
#घोषणा QIBPORTCNTR_SENDSTALL       5U
/* receive-related counters */
#घोषणा QIBPORTCNTR_PKTRCV          6U
#घोषणा QIBPORTCNTR_PSRCVDATA       7U
#घोषणा QIBPORTCNTR_PSRCVPKTS       8U
#घोषणा QIBPORTCNTR_RCVEBP          9U
#घोषणा QIBPORTCNTR_RCVOVFL         10U
#घोषणा QIBPORTCNTR_WORDRCV         11U
/* IB link related error counters */
#घोषणा QIBPORTCNTR_RXLOCALPHYERR   12U
#घोषणा QIBPORTCNTR_RXVLERR         13U
#घोषणा QIBPORTCNTR_ERRICRC         14U
#घोषणा QIBPORTCNTR_ERRVCRC         15U
#घोषणा QIBPORTCNTR_ERRLPCRC        16U
#घोषणा QIBPORTCNTR_BADFORMAT       17U
#घोषणा QIBPORTCNTR_ERR_RLEN        18U
#घोषणा QIBPORTCNTR_IBSYMBOLERR     19U
#घोषणा QIBPORTCNTR_INVALIDRLEN     20U
#घोषणा QIBPORTCNTR_UNSUPVL         21U
#घोषणा QIBPORTCNTR_EXCESSBUFOVFL   22U
#घोषणा QIBPORTCNTR_ERRLINK         23U
#घोषणा QIBPORTCNTR_IBLINKDOWN      24U
#घोषणा QIBPORTCNTR_IBLINKERRRECOV  25U
#घोषणा QIBPORTCNTR_LLI             26U
/* other error counters */
#घोषणा QIBPORTCNTR_RXDROPPKT       27U
#घोषणा QIBPORTCNTR_VL15PKTDROP     28U
#घोषणा QIBPORTCNTR_ERRPKEY         29U
#घोषणा QIBPORTCNTR_KHDROVFL        30U
/* sampling counters (these are actually control रेजिस्टरs) */
#घोषणा QIBPORTCNTR_PSINTERVAL      31U
#घोषणा QIBPORTCNTR_PSSTART         32U
#घोषणा QIBPORTCNTR_PSSTAT          33U

/* how often we check क्रम packet activity क्रम "घातer on hours (in seconds) */
#घोषणा ACTIVITY_TIMER 5

#घोषणा MAX_NAME_SIZE 64

#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
काष्ठा qib_irq_notअगरy;
#पूर्ण_अगर

काष्ठा qib_msix_entry अणु
	व्योम *arg;
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	पूर्णांक dca;
	पूर्णांक rcv;
	काष्ठा qib_irq_notअगरy *notअगरier;
#पूर्ण_अगर
	cpumask_var_t mask;
पूर्ण;

/* Below is an opaque काष्ठा. Each chip (device) can मुख्यtain
 * निजी data needed क्रम its operation, but not germane to the
 * rest of the driver.  For convenience, we define another that
 * is chip-specअगरic, per-port
 */
काष्ठा qib_chip_specअगरic;
काष्ठा qib_chipport_specअगरic;

क्रमागत qib_sdma_states अणु
	qib_sdma_state_s00_hw_करोwn,
	qib_sdma_state_s10_hw_start_up_रुको,
	qib_sdma_state_s20_idle,
	qib_sdma_state_s30_sw_clean_up_रुको,
	qib_sdma_state_s40_hw_clean_up_रुको,
	qib_sdma_state_s50_hw_halt_रुको,
	qib_sdma_state_s99_running,
पूर्ण;

क्रमागत qib_sdma_events अणु
	qib_sdma_event_e00_go_hw_करोwn,
	qib_sdma_event_e10_go_hw_start,
	qib_sdma_event_e20_hw_started,
	qib_sdma_event_e30_go_running,
	qib_sdma_event_e40_sw_cleaned,
	qib_sdma_event_e50_hw_cleaned,
	qib_sdma_event_e60_hw_halted,
	qib_sdma_event_e70_go_idle,
	qib_sdma_event_e7220_err_halted,
	qib_sdma_event_e7322_err_halted,
	qib_sdma_event_e90_समयr_tick,
पूर्ण;

काष्ठा sdma_set_state_action अणु
	अचिन्हित op_enable:1;
	अचिन्हित op_पूर्णांकenable:1;
	अचिन्हित op_halt:1;
	अचिन्हित op_drain:1;
	अचिन्हित go_s99_running_tofalse:1;
	अचिन्हित go_s99_running_totrue:1;
पूर्ण;

काष्ठा qib_sdma_state अणु
	काष्ठा kref          kref;
	काष्ठा completion    comp;
	क्रमागत qib_sdma_states current_state;
	काष्ठा sdma_set_state_action *set_state_action;
	अचिन्हित             current_op;
	अचिन्हित             go_s99_running;
	अचिन्हित             first_sendbuf;
	अचिन्हित             last_sendbuf; /* really last +1 */
	/* debugging/devel */
	क्रमागत qib_sdma_states previous_state;
	अचिन्हित             previous_op;
	क्रमागत qib_sdma_events last_event;
पूर्ण;

काष्ठा xmit_रुको अणु
	काष्ठा समयr_list समयr;
	u64 counter;
	u8 flags;
	काष्ठा cache अणु
		u64 psxmitdata;
		u64 psrcvdata;
		u64 psxmitpkts;
		u64 psrcvpkts;
		u64 psxmitरुको;
	पूर्ण counter_cache;
पूर्ण;

/*
 * The काष्ठाure below encapsulates data relevant to a physical IB Port.
 * Current chips support only one such port, but the separation
 * clarअगरies things a bit. Note that to conक्रमm to IB conventions,
 * port-numbers are one-based. The first or only port is port1.
 */
काष्ठा qib_pportdata अणु
	काष्ठा qib_ibport ibport_data;

	काष्ठा qib_devdata *dd;
	काष्ठा qib_chippport_specअगरic *cpspec; /* chip-specअगरic per-port */
	काष्ठा kobject pport_kobj;
	काष्ठा kobject pport_cc_kobj;
	काष्ठा kobject sl2vl_kobj;
	काष्ठा kobject diagc_kobj;

	/* GUID क्रम this पूर्णांकerface, in network order */
	__be64 guid;

	/* QIB_POLL, etc. link-state specअगरic flags, per port */
	u32 lflags;
	/* qib_lflags driver is रुकोing क्रम */
	u32 state_wanted;
	spinlock_t lflags_lock;

	/* ref count क्रम each pkey */
	atomic_t pkeyrefs[4];

	/*
	 * this address is mapped पढ़ोonly पूर्णांकo user processes so they can
	 * get status cheaply, whenever they want.  One qword of status per port
	 */
	u64 *statusp;

	/* SendDMA related entries */

	/* पढ़ो mostly */
	काष्ठा qib_sdma_desc *sdma_descq;
	काष्ठा workqueue_काष्ठा *qib_wq;
	काष्ठा qib_sdma_state sdma_state;
	dma_addr_t       sdma_descq_phys;
	अस्थिर __le64 *sdma_head_dma; /* DMA'ed by chip */
	dma_addr_t       sdma_head_phys;
	u16                   sdma_descq_cnt;

	/* पढ़ो/ग_लिखो using lock */
	spinlock_t            sdma_lock ____cacheline_aligned_in_smp;
	काष्ठा list_head      sdma_activelist;
	काष्ठा list_head      sdma_userpending;
	u64                   sdma_descq_added;
	u64                   sdma_descq_हटाओd;
	u16                   sdma_descq_tail;
	u16                   sdma_descq_head;
	u8                    sdma_generation;
	u8                    sdma_पूर्णांकrequest;

	काष्ठा tasklet_काष्ठा sdma_sw_clean_up_task
		____cacheline_aligned_in_smp;

	रुको_queue_head_t state_रुको; /* क्रम state_wanted */

	/* HoL blocking क्रम SMP replies */
	अचिन्हित          hol_state;
	काष्ठा समयr_list hol_समयr;

	/*
	 * Shaकरोw copies of रेजिस्टरs; size indicates पढ़ो access size.
	 * Most of them are पढ़ोonly, but some are ग_लिखो-only रेजिस्टर,
	 * where we manipulate the bits in the shaकरोw copy, and then ग_लिखो
	 * the shaकरोw copy to qlogic_ib.
	 *
	 * We deliberately make most of these 32 bits, since they have
	 * restricted range.  For any that we पढ़ो, we won't to generate 32
	 * bit accesses, since Opteron will generate 2 separate 32 bit HT
	 * transactions क्रम a 64 bit पढ़ो, and we want to aव्योम unnecessary
	 * bus transactions.
	 */

	/* This is the 64 bit group */
	/* last ibcstatus.  opaque outside chip-specअगरic code */
	u64 lastibcstat;

	/* these are the "32 bit" regs */

	/*
	 * the following two are 32-bit biपंचांगasks, but अणुtest,clear,setपूर्ण_bit
	 * all expect bit fields to be "unsigned long"
	 */
	अचिन्हित दीर्घ p_rcvctrl; /* shaकरोw per-port rcvctrl */
	अचिन्हित दीर्घ p_sendctrl; /* shaकरोw per-port sendctrl */

	u32 ibmtu; /* The MTU programmed क्रम this unit */
	/*
	 * Current max size IB packet (in bytes) including IB headers, that
	 * we can send. Changes when ibmtu changes.
	 */
	u32 ibmaxlen;
	/*
	 * ibmaxlen at init समय, limited by chip and by receive buffer
	 * size.  Not changed after init.
	 */
	u32 init_ibmaxlen;
	/* LID programmed क्रम this instance */
	u16 lid;
	/* list of pkeys programmed; 0 अगर not set */
	u16 pkeys[4];
	/* LID mask control */
	u8 lmc;
	u8 link_width_supported;
	u16 link_speed_supported;
	u8 link_width_enabled;
	u16 link_speed_enabled;
	u8 link_width_active;
	u16 link_speed_active;
	u8 vls_supported;
	u8 vls_operational;
	/* Rx Polarity inversion (compensate क्रम ~tx on partner) */
	u8 rx_pol_inv;

	u8 hw_pidx;     /* physical port index */
	u32 port;        /* IB port number and index पूर्णांकo dd->pports - 1 */

	u8 delay_mult;

	/* used to override LED behavior */
	u8 led_override;  /* Substituted क्रम normal value, अगर non-zero */
	u16 led_override_समयoff; /* delta to next समयr event */
	u8 led_override_vals[2]; /* Alternates per blink-frame */
	u8 led_override_phase; /* Just counts, LSB picks from vals[] */
	atomic_t led_override_समयr_active;
	/* Used to flash LEDs in override mode */
	काष्ठा समयr_list led_override_समयr;
	काष्ठा xmit_रुको cong_stats;
	काष्ठा समयr_list symerr_clear_समयr;

	/* Synchronize access between driver ग_लिखोs and sysfs पढ़ोs */
	spinlock_t cc_shaकरोw_lock
		____cacheline_aligned_in_smp;

	/* Shaकरोw copy of the congestion control table */
	काष्ठा cc_table_shaकरोw *ccti_entries_shaकरोw;

	/* Shaकरोw copy of the congestion control entries */
	काष्ठा ib_cc_congestion_setting_attr_shaकरोw *congestion_entries_shaकरोw;

	/* List of congestion control table entries */
	काष्ठा ib_cc_table_entry_shaकरोw *ccti_entries;

	/* 16 congestion entries with each entry corresponding to a SL */
	काष्ठा ib_cc_congestion_entry_shaकरोw *congestion_entries;

	/* Maximum number of congestion control entries that the agent expects
	 * the manager to send.
	 */
	u16 cc_supported_table_entries;

	/* Total number of congestion control table entries */
	u16 total_cct_entry;

	/* Bit map identअगरying service level */
	u16 cc_sl_control_map;

	/* maximum congestion control table index */
	u16 ccti_limit;

	/* CA's max number of 64 entry units in the congestion control table */
	u8 cc_max_table_entries;
पूर्ण;

/* Observers. Not to be taken lightly, possibly not to ship. */
/*
 * If a diag पढ़ो or ग_लिखो is to (bottom <= offset <= top),
 * the "hoook" is called, allowing, e.g. shaकरोws to be
 * updated in sync with the driver. काष्ठा diag_observer
 * is the "visible" part.
 */
काष्ठा diag_observer;

प्रकार पूर्णांक (*diag_hook) (काष्ठा qib_devdata *dd,
	स्थिर काष्ठा diag_observer *op,
	u32 offs, u64 *data, u64 mask, पूर्णांक only_32);

काष्ठा diag_observer अणु
	diag_hook hook;
	u32 bottom;
	u32 top;
पूर्ण;

बाह्य पूर्णांक qib_रेजिस्टर_observer(काष्ठा qib_devdata *dd,
	स्थिर काष्ठा diag_observer *op);

/* Only declared here, not defined. Private to diags */
काष्ठा diag_observer_list_elt;

/* device data काष्ठा now contains only "general per-device" info.
 * fields related to a physical IB port are in a qib_pportdata काष्ठा,
 * described above) जबतक fields only used by a particular chip-type are in
 * a qib_chipdata काष्ठा, whose contents are opaque to this file.
 */
काष्ठा qib_devdata अणु
	काष्ठा qib_ibdev verbs_dev;     /* must be first */
	काष्ठा list_head list;
	/* poपूर्णांकers to related काष्ठाs क्रम this device */
	/* pci access data काष्ठाure */
	काष्ठा pci_dev *pcidev;
	काष्ठा cdev *user_cdev;
	काष्ठा cdev *diag_cdev;
	काष्ठा device *user_device;
	काष्ठा device *diag_device;

	/* mem-mapped poपूर्णांकer to base of chip regs */
	u64 __iomem *kregbase;
	/* end of mem-mapped chip space excluding sendbuf and user regs */
	u64 __iomem *kregend;
	/* physical address of chip क्रम io_remap, etc. */
	resource_माप_प्रकार physaddr;
	/* qib_cfgctxts poपूर्णांकers */
	काष्ठा qib_ctxtdata **rcd; /* Receive Context Data */

	/* qib_pportdata, poपूर्णांकs to array of (physical) port-specअगरic
	 * data काष्ठाs, indexed by pidx (0..n-1)
	 */
	काष्ठा qib_pportdata *pport;
	काष्ठा qib_chip_specअगरic *cspec; /* chip-specअगरic */

	/* kvirt address of 1st 2k pio buffer */
	व्योम __iomem *pio2kbase;
	/* kvirt address of 1st 4k pio buffer */
	व्योम __iomem *pio4kbase;
	/* mem-mapped poपूर्णांकer to base of PIO buffers (अगर using WC PAT) */
	व्योम __iomem *piobase;
	/* mem-mapped poपूर्णांकer to base of user chip regs (अगर using WC PAT) */
	u64 __iomem *userbase;
	व्योम __iomem *piovl15base; /* base of VL15 buffers, अगर not WC */
	/*
	 * poपूर्णांकs to area where PIOavail रेजिस्टरs will be DMA'ed.
	 * Has to be on a page of it's own, because the page will be
	 * mapped पूर्णांकo user program space.  This copy is *ONLY* ever
	 * written by DMA, not by the driver!  Need a copy per device
	 * when we get to multiple devices
	 */
	अस्थिर __le64 *pioavailregs_dma; /* DMA'ed by chip */
	/* physical address where updates occur */
	dma_addr_t pioavailregs_phys;

	/* device-specअगरic implementations of functions needed by
	 * common code. Contrary to previous consensus, we can't
	 * really just poपूर्णांक to a device-specअगरic table, because we
	 * may need to "bend", e.g. *_f_put_tid
	 */
	/* fallback to alternate पूर्णांकerrupt type अगर possible */
	पूर्णांक (*f_पूर्णांकr_fallback)(काष्ठा qib_devdata *);
	/* hard reset chip */
	पूर्णांक (*f_reset)(काष्ठा qib_devdata *);
	व्योम (*f_quiet_serdes)(काष्ठा qib_pportdata *);
	पूर्णांक (*f_bringup_serdes)(काष्ठा qib_pportdata *);
	पूर्णांक (*f_early_init)(काष्ठा qib_devdata *);
	व्योम (*f_clear_tids)(काष्ठा qib_devdata *, काष्ठा qib_ctxtdata *);
	व्योम (*f_put_tid)(काष्ठा qib_devdata *, u64 __iomem*,
				u32, अचिन्हित दीर्घ);
	व्योम (*f_cleanup)(काष्ठा qib_devdata *);
	व्योम (*f_setextled)(काष्ठा qib_pportdata *, u32);
	/* fill out chip-specअगरic fields */
	पूर्णांक (*f_get_base_info)(काष्ठा qib_ctxtdata *, काष्ठा qib_base_info *);
	/* मुक्त irq */
	व्योम (*f_मुक्त_irq)(काष्ठा qib_devdata *);
	काष्ठा qib_message_header *(*f_get_msgheader)
					(काष्ठा qib_devdata *, __le32 *);
	व्योम (*f_config_ctxts)(काष्ठा qib_devdata *);
	पूर्णांक (*f_get_ib_cfg)(काष्ठा qib_pportdata *, पूर्णांक);
	पूर्णांक (*f_set_ib_cfg)(काष्ठा qib_pportdata *, पूर्णांक, u32);
	पूर्णांक (*f_set_ib_loopback)(काष्ठा qib_pportdata *, स्थिर अक्षर *);
	पूर्णांक (*f_get_ib_table)(काष्ठा qib_pportdata *, पूर्णांक, व्योम *);
	पूर्णांक (*f_set_ib_table)(काष्ठा qib_pportdata *, पूर्णांक, व्योम *);
	u32 (*f_iblink_state)(u64);
	u8 (*f_ibphys_portstate)(u64);
	व्योम (*f_xgxs_reset)(काष्ठा qib_pportdata *);
	/* per chip actions needed क्रम IB Link up/करोwn changes */
	पूर्णांक (*f_ib_upकरोwn)(काष्ठा qib_pportdata *, पूर्णांक, u64);
	u32 __iomem *(*f_माला_लोendbuf)(काष्ठा qib_pportdata *, u64, u32 *);
	/* Read/modअगरy/ग_लिखो of GPIO pins (potentially chip-specअगरic */
	पूर्णांक (*f_gpio_mod)(काष्ठा qib_devdata *dd, u32 out, u32 dir,
		u32 mask);
	/* Enable ग_लिखोs to config EEPROM (अगर supported) */
	पूर्णांक (*f_eeprom_wen)(काष्ठा qib_devdata *dd, पूर्णांक wen);
	/*
	 * modअगरy rcvctrl shaकरोw[s] and ग_लिखो to appropriate chip-regs.
	 * see above QIB_RCVCTRL_xxx_ENB/DIS क्रम operations.
	 * (ctxt == -1) means "all contexts", only meaningful क्रम
	 * clearing. Could हटाओ अगर chip_spec shutकरोwn properly करोne.
	 */
	व्योम (*f_rcvctrl)(काष्ठा qib_pportdata *, अचिन्हित पूर्णांक op,
		पूर्णांक ctxt);
	/* Read/modअगरy/ग_लिखो sendctrl appropriately क्रम op and port. */
	व्योम (*f_sendctrl)(काष्ठा qib_pportdata *, u32 op);
	व्योम (*f_set_पूर्णांकr_state)(काष्ठा qib_devdata *, u32);
	व्योम (*f_set_armlaunch)(काष्ठा qib_devdata *, u32);
	व्योम (*f_wantpiobuf_पूर्णांकr)(काष्ठा qib_devdata *, u32);
	पूर्णांक (*f_late_initreg)(काष्ठा qib_devdata *);
	पूर्णांक (*f_init_sdma_regs)(काष्ठा qib_pportdata *);
	u16 (*f_sdma_gethead)(काष्ठा qib_pportdata *);
	पूर्णांक (*f_sdma_busy)(काष्ठा qib_pportdata *);
	व्योम (*f_sdma_update_tail)(काष्ठा qib_pportdata *, u16);
	व्योम (*f_sdma_set_desc_cnt)(काष्ठा qib_pportdata *, अचिन्हित);
	व्योम (*f_sdma_sendctrl)(काष्ठा qib_pportdata *, अचिन्हित);
	व्योम (*f_sdma_hw_clean_up)(काष्ठा qib_pportdata *);
	व्योम (*f_sdma_hw_start_up)(काष्ठा qib_pportdata *);
	व्योम (*f_sdma_init_early)(काष्ठा qib_pportdata *);
	व्योम (*f_set_cntr_sample)(काष्ठा qib_pportdata *, u32, u32);
	व्योम (*f_update_usrhead)(काष्ठा qib_ctxtdata *, u64, u32, u32, u32);
	u32 (*f_hdrqempty)(काष्ठा qib_ctxtdata *);
	u64 (*f_portcntr)(काष्ठा qib_pportdata *, u32);
	u32 (*f_पढ़ो_cntrs)(काष्ठा qib_devdata *, loff_t, अक्षर **,
		u64 **);
	u32 (*f_पढ़ो_portcntrs)(काष्ठा qib_devdata *, loff_t, u32,
		अक्षर **, u64 **);
	u32 (*f_setpbc_control)(काष्ठा qib_pportdata *, u32, u8, u8);
	व्योम (*f_initvl15_bufs)(काष्ठा qib_devdata *);
	व्योम (*f_init_ctxt)(काष्ठा qib_ctxtdata *);
	व्योम (*f_txchk_change)(काष्ठा qib_devdata *, u32, u32, u32,
		काष्ठा qib_ctxtdata *);
	व्योम (*f_ग_लिखोscratch)(काष्ठा qib_devdata *, u32);
	पूर्णांक (*f_tempsense_rd)(काष्ठा qib_devdata *, पूर्णांक regnum);
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	पूर्णांक (*f_notअगरy_dca)(काष्ठा qib_devdata *, अचिन्हित दीर्घ event);
#पूर्ण_अगर

	अक्षर *boardname; /* human पढ़ोable board info */

	/* ढाँचा क्रम writing TIDs  */
	u64 tidढाँचा;
	/* value to ग_लिखो to मुक्त TIDs */
	u64 tidinvalid;

	/* number of रेजिस्टरs used क्रम pioavail */
	u32 pioavregs;
	/* device (not port) flags, basically device capabilities */
	u32 flags;
	/* last buffer क्रम user use */
	u32 lastctxt_piobuf;

	/* reset value */
	u64 z_पूर्णांक_counter;
	/* percpu पूर्णांकcounter */
	u64 __percpu *पूर्णांक_counter;

	/* pio bufs allocated per ctxt */
	u32 pbufsctxt;
	/* अगर reमुख्यder on bufs/ctxt, ctxts < extrabuf get 1 extra */
	u32 ctxts_extrabuf;
	/*
	 * number of ctxts configured as max; zero is set to number chip
	 * supports, less gives more pio bufs/ctxt, etc.
	 */
	u32 cfgctxts;
	/*
	 * number of ctxts available क्रम PSM खोलो
	 */
	u32 मुक्तctxts;

	/*
	 * hपूर्णांक that we should update pioavailshaकरोw beक्रमe
	 * looking क्रम a PIO buffer
	 */
	u32 upd_pio_shaकरोw;

	/* पूर्णांकernal debugging stats */
	u32 maxpkts_call;
	u32 avgpkts_call;
	u64 nopiobufs;

	/* PCI Venकरोr ID (here क्रम NodeInfo) */
	u16 venकरोrid;
	/* PCI Device ID (here क्रम NodeInfo) */
	u16 deviceid;
	/* क्रम ग_लिखो combining settings */
	पूर्णांक wc_cookie;
	अचिन्हित दीर्घ wc_base;
	अचिन्हित दीर्घ wc_len;

	/* shaकरोw copy of काष्ठा page *'s क्रम exp tid pages */
	काष्ठा page **pageshaकरोw;
	/* shaकरोw copy of dma handles क्रम exp tid pages */
	dma_addr_t *physshaकरोw;
	u64 __iomem *egrtidbase;
	spinlock_t sendctrl_lock; /* protect changes to sendctrl shaकरोw */
	/* around rcd and (user ctxts) ctxt_cnt use (पूर्णांकr vs मुक्त) */
	spinlock_t uctxt_lock; /* rcd and user context changes */
	/*
	 * per unit status, see also portdata statusp
	 * mapped पढ़ोonly पूर्णांकo user processes so they can get unit and
	 * IB link status cheaply
	 */
	u64 *devstatusp;
	अक्षर *मुक्तzemsg; /* मुक्तze msg अगर hw error put chip in मुक्तze */
	u32 मुक्तzelen; /* max length of मुक्तzemsg */
	/* समयr used to prevent stats overflow, error throttling, etc. */
	काष्ठा समयr_list stats_समयr;

	/* समयr to verअगरy पूर्णांकerrupts work, and fallback अगर possible */
	काष्ठा समयr_list पूर्णांकrchk_समयr;
	अचिन्हित दीर्घ ureg_align; /* user रेजिस्टर alignment */

	/*
	 * Protects pioavailshaकरोw, pioavailkernel, pio_need_disarm, and
	 * pio_writing.
	 */
	spinlock_t pioavail_lock;
	/*
	 * index of last buffer to optimize search क्रम next
	 */
	u32 last_pio;
	/*
	 * min kernel pio buffer to optimize search
	 */
	u32 min_kernel_pio;
	/*
	 * Shaकरोw copies of रेजिस्टरs; size indicates पढ़ो access size.
	 * Most of them are पढ़ोonly, but some are ग_लिखो-only रेजिस्टर,
	 * where we manipulate the bits in the shaकरोw copy, and then ग_लिखो
	 * the shaकरोw copy to qlogic_ib.
	 *
	 * We deliberately make most of these 32 bits, since they have
	 * restricted range.  For any that we पढ़ो, we won't to generate 32
	 * bit accesses, since Opteron will generate 2 separate 32 bit HT
	 * transactions क्रम a 64 bit पढ़ो, and we want to aव्योम unnecessary
	 * bus transactions.
	 */

	/* This is the 64 bit group */

	अचिन्हित दीर्घ pioavailshaकरोw[6];
	/* biपंचांगap of send buffers available क्रम the kernel to use with PIO. */
	अचिन्हित दीर्घ pioavailkernel[6];
	/* biपंचांगap of send buffers which need to be disarmed. */
	अचिन्हित दीर्घ pio_need_disarm[3];
	/* biपंचांगap of send buffers which are being written to. */
	अचिन्हित दीर्घ pio_writing[3];
	/* kr_revision shaकरोw */
	u64 revision;
	/* Base GUID क्रम device (from eeprom, network order) */
	__be64 base_guid;

	/*
	 * kr_sendpiobufbase value (chip offset of pio buffers), and the
	 * base of the 2KB buffer s(user processes only use 2K)
	 */
	u64 piobufbase;
	u32 pio2k_bufbase;

	/* these are the "32 bit" regs */

	/* number of GUIDs in the flash क्रम this पूर्णांकerface */
	u32 nguid;
	/*
	 * the following two are 32-bit biपंचांगasks, but अणुtest,clear,setपूर्ण_bit
	 * all expect bit fields to be "unsigned long"
	 */
	अचिन्हित दीर्घ rcvctrl; /* shaकरोw per device rcvctrl */
	अचिन्हित दीर्घ sendctrl; /* shaकरोw per device sendctrl */

	/* value we put in kr_rcvhdrcnt */
	u32 rcvhdrcnt;
	/* value we put in kr_rcvhdrsize */
	u32 rcvhdrsize;
	/* value we put in kr_rcvhdrentsize */
	u32 rcvhdrentsize;
	/* kr_ctxtcnt value */
	u32 ctxtcnt;
	/* kr_pagealign value */
	u32 palign;
	/* number of "2KB" PIO buffers */
	u32 piobcnt2k;
	/* size in bytes of "2KB" PIO buffers */
	u32 piosize2k;
	/* max usable size in dwords of a "2KB" PIO buffer beक्रमe going "4KB" */
	u32 piosize2kmax_dwords;
	/* number of "4KB" PIO buffers */
	u32 piobcnt4k;
	/* size in bytes of "4KB" PIO buffers */
	u32 piosize4k;
	/* kr_rcvegrbase value */
	u32 rcvegrbase;
	/* kr_rcvtidbase value */
	u32 rcvtidbase;
	/* kr_rcvtidcnt value */
	u32 rcvtidcnt;
	/* kr_userregbase */
	u32 uregbase;
	/* shaकरोw the control रेजिस्टर contents */
	u32 control;

	/* chip address space used by 4k pio buffers */
	u32 align4k;
	/* size of each rcvegrbuffer */
	u16 rcvegrbufsize;
	/* log2 of above */
	u16 rcvegrbufsize_shअगरt;
	/* localbus width (1, 2,4,8,16,32) from config space  */
	u32 lbus_width;
	/* localbus speed in MHz */
	u32 lbus_speed;
	पूर्णांक unit; /* unit # of this chip */

	/* start of CHIP_SPEC move to chipspec, but need code changes */
	/* low and high portions of MSI capability/vector */
	u32 msi_lo;
	/* saved after PCIe init क्रम restore after reset */
	u32 msi_hi;
	/* MSI data (vector) saved क्रम restore */
	u16 msi_data;
	/* so we can reग_लिखो it after a chip reset */
	u32 pcibar0;
	/* so we can reग_लिखो it after a chip reset */
	u32 pcibar1;
	u64 rhdrhead_पूर्णांकr_off;

	/*
	 * ASCII serial number, from flash, large enough क्रम original
	 * all digit strings, and दीर्घer QLogic serial number क्रमmat
	 */
	u8 serial[16];
	/* human पढ़ोable board version */
	u8 boardversion[96];
	u8 lbus_info[32]; /* human पढ़ोable localbus info */
	/* chip major rev, from qib_revision */
	u8 majrev;
	/* chip minor rev, from qib_revision */
	u8 minrev;

	/* Misc small पूर्णांकs */
	/* Number of physical ports available */
	u8 num_pports;
	/* Lowest context number which can be used by user processes */
	u8 first_user_ctxt;
	u8 n_krcv_queues;
	u8 qpn_mask;
	u8 skip_kctxt_mask;

	u16 rhf_offset; /* offset of RHF within receive header entry */

	/*
	 * GPIO pins क्रम twsi-connected devices, and device code क्रम eeprom
	 */
	u8 gpio_sda_num;
	u8 gpio_scl_num;
	u8 twsi_eeprom_dev;
	u8 board_atten;

	/* Support (including locks) क्रम EEPROM logging of errors and समय */
	/* control access to actual counters, समयr */
	spinlock_t eep_st_lock;
	/* control high-level access to EEPROM */
	काष्ठा mutex eep_lock;
	uपूर्णांक64_t traffic_wds;
	काष्ठा qib_diag_client *diag_client;
	spinlock_t qib_diag_trans_lock; /* protect diag observer ops */
	काष्ठा diag_observer_list_elt *diag_observer_list;

	u8 psxmitरुको_supported;
	/* cycle length of PS* counters in HW (in picoseconds) */
	u16 psxmitरुको_check_rate;
	/* high volume overflow errors defered to tasklet */
	काष्ठा tasklet_काष्ठा error_tasklet;

	पूर्णांक asचिन्हित_node_id; /* NUMA node बंदst to HCA */
पूर्ण;

/* hol_state values */
#घोषणा QIB_HOL_UP       0
#घोषणा QIB_HOL_INIT     1

#घोषणा QIB_SDMA_SENDCTRL_OP_ENABLE    (1U << 0)
#घोषणा QIB_SDMA_SENDCTRL_OP_INTENABLE (1U << 1)
#घोषणा QIB_SDMA_SENDCTRL_OP_HALT      (1U << 2)
#घोषणा QIB_SDMA_SENDCTRL_OP_CLEANUP   (1U << 3)
#घोषणा QIB_SDMA_SENDCTRL_OP_DRAIN     (1U << 4)

/* operation types क्रम f_txchk_change() */
#घोषणा TXCHK_CHG_TYPE_DIS1  3
#घोषणा TXCHK_CHG_TYPE_ENAB1 2
#घोषणा TXCHK_CHG_TYPE_KERN  1
#घोषणा TXCHK_CHG_TYPE_USER  0

#घोषणा QIB_CHASE_TIME msecs_to_jअगरfies(145)
#घोषणा QIB_CHASE_DIS_TIME msecs_to_jअगरfies(160)

/* Private data क्रम file operations */
काष्ठा qib_filedata अणु
	काष्ठा qib_ctxtdata *rcd;
	अचिन्हित subctxt;
	अचिन्हित tidcursor;
	काष्ठा qib_user_sdma_queue *pq;
	पूर्णांक rec_cpu_num; /* क्रम cpu affinity; -1 अगर none */
पूर्ण;

बाह्य काष्ठा xarray qib_dev_table;
बाह्य काष्ठा qib_devdata *qib_lookup(पूर्णांक unit);
बाह्य u32 qib_cpulist_count;
बाह्य अचिन्हित दीर्घ *qib_cpulist;
बाह्य अचिन्हित qib_cc_table_size;

पूर्णांक qib_init(काष्ठा qib_devdata *, पूर्णांक);
पूर्णांक init_chip_wc_pat(काष्ठा qib_devdata *dd, u32);
पूर्णांक qib_enable_wc(काष्ठा qib_devdata *dd);
व्योम qib_disable_wc(काष्ठा qib_devdata *dd);
पूर्णांक qib_count_units(पूर्णांक *npresentp, पूर्णांक *nupp);
पूर्णांक qib_count_active_units(व्योम);

पूर्णांक qib_cdev_init(पूर्णांक minor, स्थिर अक्षर *name,
		  स्थिर काष्ठा file_operations *fops,
		  काष्ठा cdev **cdevp, काष्ठा device **devp);
व्योम qib_cdev_cleanup(काष्ठा cdev **cdevp, काष्ठा device **devp);
पूर्णांक qib_dev_init(व्योम);
व्योम qib_dev_cleanup(व्योम);

पूर्णांक qib_diag_add(काष्ठा qib_devdata *);
व्योम qib_diag_हटाओ(काष्ठा qib_devdata *);
व्योम qib_handle_e_ibstatuschanged(काष्ठा qib_pportdata *, u64);
व्योम qib_sdma_update_tail(काष्ठा qib_pportdata *, u16); /* hold sdma_lock */

पूर्णांक qib_decode_err(काष्ठा qib_devdata *dd, अक्षर *buf, माप_प्रकार blen, u64 err);
व्योम qib_bad_पूर्णांकrstatus(काष्ठा qib_devdata *);
व्योम qib_handle_urcv(काष्ठा qib_devdata *, u64);

/* clean up any per-chip chip-specअगरic stuff */
व्योम qib_chip_cleanup(काष्ठा qib_devdata *);
/* clean up any chip type-specअगरic stuff */
व्योम qib_chip_करोne(व्योम);

/* check to see अगर we have to क्रमce ordering क्रम ग_लिखो combining */
पूर्णांक qib_unordered_wc(व्योम);
व्योम qib_pio_copy(व्योम __iomem *to, स्थिर व्योम *from, माप_प्रकार count);

व्योम qib_disarm_piobufs(काष्ठा qib_devdata *, अचिन्हित, अचिन्हित);
पूर्णांक qib_disarm_piobufs_अगरneeded(काष्ठा qib_ctxtdata *);
व्योम qib_disarm_piobufs_set(काष्ठा qib_devdata *, अचिन्हित दीर्घ *, अचिन्हित);
व्योम qib_cancel_sends(काष्ठा qib_pportdata *);

पूर्णांक qib_create_rcvhdrq(काष्ठा qib_devdata *, काष्ठा qib_ctxtdata *);
पूर्णांक qib_setup_eagerbufs(काष्ठा qib_ctxtdata *);
व्योम qib_set_ctxtcnt(काष्ठा qib_devdata *);
पूर्णांक qib_create_ctxts(काष्ठा qib_devdata *dd);
काष्ठा qib_ctxtdata *qib_create_ctxtdata(काष्ठा qib_pportdata *, u32, पूर्णांक);
पूर्णांक qib_init_pportdata(काष्ठा qib_pportdata *, काष्ठा qib_devdata *, u8, u8);
व्योम qib_मुक्त_ctxtdata(काष्ठा qib_devdata *, काष्ठा qib_ctxtdata *);

u32 qib_kreceive(काष्ठा qib_ctxtdata *, u32 *, u32 *);
पूर्णांक qib_reset_device(पूर्णांक);
पूर्णांक qib_रुको_linkstate(काष्ठा qib_pportdata *, u32, पूर्णांक);
पूर्णांक qib_set_linkstate(काष्ठा qib_pportdata *, u8);
पूर्णांक qib_set_mtu(काष्ठा qib_pportdata *, u16);
पूर्णांक qib_set_lid(काष्ठा qib_pportdata *, u32, u8);
व्योम qib_hol_करोwn(काष्ठा qib_pportdata *);
व्योम qib_hol_init(काष्ठा qib_pportdata *);
व्योम qib_hol_up(काष्ठा qib_pportdata *);
व्योम qib_hol_event(काष्ठा समयr_list *);
व्योम qib_disable_after_error(काष्ठा qib_devdata *);
पूर्णांक qib_set_uevent_bits(काष्ठा qib_pportdata *, स्थिर पूर्णांक);

/* क्रम use in प्रणाली calls, where we want to know device type, etc. */
#घोषणा ctxt_fp(fp) \
	(((काष्ठा qib_filedata *)(fp)->निजी_data)->rcd)
#घोषणा subctxt_fp(fp) \
	(((काष्ठा qib_filedata *)(fp)->निजी_data)->subctxt)
#घोषणा tidcursor_fp(fp) \
	(((काष्ठा qib_filedata *)(fp)->निजी_data)->tidcursor)
#घोषणा user_sdma_queue_fp(fp) \
	(((काष्ठा qib_filedata *)(fp)->निजी_data)->pq)

अटल अंतरभूत काष्ठा qib_devdata *dd_from_ppd(काष्ठा qib_pportdata *ppd)
अणु
	वापस ppd->dd;
पूर्ण

अटल अंतरभूत काष्ठा qib_devdata *dd_from_dev(काष्ठा qib_ibdev *dev)
अणु
	वापस container_of(dev, काष्ठा qib_devdata, verbs_dev);
पूर्ण

अटल अंतरभूत काष्ठा qib_devdata *dd_from_ibdev(काष्ठा ib_device *ibdev)
अणु
	वापस dd_from_dev(to_idev(ibdev));
पूर्ण

अटल अंतरभूत काष्ठा qib_pportdata *ppd_from_ibp(काष्ठा qib_ibport *ibp)
अणु
	वापस container_of(ibp, काष्ठा qib_pportdata, ibport_data);
पूर्ण

अटल अंतरभूत काष्ठा qib_ibport *to_iport(काष्ठा ib_device *ibdev, u32 port)
अणु
	काष्ठा qib_devdata *dd = dd_from_ibdev(ibdev);
	u32 pidx = port - 1; /* IB number port from 1, hdw from 0 */

	WARN_ON(pidx >= dd->num_pports);
	वापस &dd->pport[pidx].ibport_data;
पूर्ण

/*
 * values क्रम dd->flags (_device_ related flags) and
 */
#घोषणा QIB_HAS_LINK_LATENCY  0x1 /* supports link latency (IB 1.2) */
#घोषणा QIB_INITTED           0x2 /* chip and driver up and initted */
#घोषणा QIB_DOING_RESET       0x4  /* in the middle of करोing chip reset */
#घोषणा QIB_PRESENT           0x8  /* chip accesses can be करोne */
#घोषणा QIB_PIO_FLUSH_WC      0x10 /* Needs Write combining flush क्रम PIO */
#घोषणा QIB_HAS_THRESH_UPDATE 0x40
#घोषणा QIB_HAS_SDMA_TIMEOUT  0x80
#घोषणा QIB_USE_SPCL_TRIG     0x100 /* SpecialTrigger launch enabled */
#घोषणा QIB_NODMA_RTAIL       0x200 /* rcvhdrtail रेजिस्टर DMA enabled */
#घोषणा QIB_HAS_INTX          0x800 /* Supports INTx पूर्णांकerrupts */
#घोषणा QIB_HAS_SEND_DMA      0x1000 /* Supports Send DMA */
#घोषणा QIB_HAS_VLSUPP        0x2000 /* Supports multiple VLs; PBC dअगरferent */
#घोषणा QIB_HAS_HDRSUPP       0x4000 /* Supports header suppression */
#घोषणा QIB_BADINTR           0x8000 /* severe पूर्णांकerrupt problems */
#घोषणा QIB_DCA_ENABLED       0x10000 /* Direct Cache Access enabled */
#घोषणा QIB_HAS_QSFP          0x20000 /* device (card instance) has QSFP */
#घोषणा QIB_SHUTDOWN          0x40000 /* device is shutting करोwn */

/*
 * values क्रम ppd->lflags (_ib_port_ related flags)
 */
#घोषणा QIBL_LINKV             0x1 /* IB link state valid */
#घोषणा QIBL_LINKDOWN          0x8 /* IB link is करोwn */
#घोषणा QIBL_LINKINIT          0x10 /* IB link level is up */
#घोषणा QIBL_LINKARMED         0x20 /* IB link is ARMED */
#घोषणा QIBL_LINKACTIVE        0x40 /* IB link is ACTIVE */
/* leave a gap क्रम more IB-link state */
#घोषणा QIBL_IB_AUTONEG_INPROG 0x1000 /* non-IBTA DDR/QDR neg active */
#घोषणा QIBL_IB_AUTONEG_FAILED 0x2000 /* non-IBTA DDR/QDR neg failed */
#घोषणा QIBL_IB_LINK_DISABLED  0x4000 /* Linkकरोwn-disable क्रमced,
				       * Do not try to bring up */
#घोषणा QIBL_IB_FORCE_NOTIFY   0x8000 /* क्रमce notअगरy on next ib change */

/* IB dword length mask in PBC (lower 11 bits); same क्रम all chips */
#घोषणा QIB_PBC_LENGTH_MASK                     ((1 << 11) - 1)


/* ctxt_flag bit offsets */
		/* रुकोing क्रम a packet to arrive */
#घोषणा QIB_CTXT_WAITING_RCV   2
		/* master has not finished initializing */
#घोषणा QIB_CTXT_MASTER_UNINIT 4
		/* रुकोing क्रम an urgent packet to arrive */
#घोषणा QIB_CTXT_WAITING_URG 5

/* मुक्त up any allocated data at बंदs */
व्योम qib_मुक्त_data(काष्ठा qib_ctxtdata *dd);
व्योम qib_chg_pioavailkernel(काष्ठा qib_devdata *, अचिन्हित, अचिन्हित,
			    u32, काष्ठा qib_ctxtdata *);
काष्ठा qib_devdata *qib_init_iba7322_funcs(काष्ठा pci_dev *,
					   स्थिर काष्ठा pci_device_id *);
काष्ठा qib_devdata *qib_init_iba7220_funcs(काष्ठा pci_dev *,
					   स्थिर काष्ठा pci_device_id *);
काष्ठा qib_devdata *qib_init_iba6120_funcs(काष्ठा pci_dev *,
					   स्थिर काष्ठा pci_device_id *);
व्योम qib_मुक्त_devdata(काष्ठा qib_devdata *);
काष्ठा qib_devdata *qib_alloc_devdata(काष्ठा pci_dev *pdev, माप_प्रकार extra);

#घोषणा QIB_TWSI_NO_DEV 0xFF
/* Below qib_twsi_ functions must be called with eep_lock held */
पूर्णांक qib_twsi_reset(काष्ठा qib_devdata *dd);
पूर्णांक qib_twsi_blk_rd(काष्ठा qib_devdata *dd, पूर्णांक dev, पूर्णांक addr, व्योम *buffer,
		    पूर्णांक len);
पूर्णांक qib_twsi_blk_wr(काष्ठा qib_devdata *dd, पूर्णांक dev, पूर्णांक addr,
		    स्थिर व्योम *buffer, पूर्णांक len);
व्योम qib_get_eeprom_info(काष्ठा qib_devdata *);
व्योम qib_dump_lookup_output_queue(काष्ठा qib_devdata *);
व्योम qib_क्रमce_pio_avail_update(काष्ठा qib_devdata *);
व्योम qib_clear_symerror_on_linkup(काष्ठा समयr_list *t);

/*
 * Set LED override, only the two LSBs have "public" meaning, but
 * any non-zero value substitutes them क्रम the Link and LinkTrain
 * LED states.
 */
#घोषणा QIB_LED_PHYS 1 /* Physical (linktraining) GREEN LED */
#घोषणा QIB_LED_LOG 2  /* Logical (link) YELLOW LED */
व्योम qib_set_led_override(काष्ठा qib_pportdata *ppd, अचिन्हित पूर्णांक val);

/* send dma routines */
पूर्णांक qib_setup_sdma(काष्ठा qib_pportdata *);
व्योम qib_tearकरोwn_sdma(काष्ठा qib_pportdata *);
व्योम __qib_sdma_पूर्णांकr(काष्ठा qib_pportdata *);
व्योम qib_sdma_पूर्णांकr(काष्ठा qib_pportdata *);
व्योम qib_user_sdma_send_desc(काष्ठा qib_pportdata *dd,
			काष्ठा list_head *pktlist);
पूर्णांक qib_sdma_verbs_send(काष्ठा qib_pportdata *, काष्ठा rvt_sge_state *,
			u32, काष्ठा qib_verbs_txreq *);
/* ppd->sdma_lock should be locked beक्रमe calling this. */
पूर्णांक qib_sdma_make_progress(काष्ठा qib_pportdata *dd);

/* must be called under qib_sdma_lock */
अटल अंतरभूत u16 qib_sdma_descq_मुक्तcnt(स्थिर काष्ठा qib_pportdata *ppd)
अणु
	वापस ppd->sdma_descq_cnt -
		(ppd->sdma_descq_added - ppd->sdma_descq_हटाओd) - 1;
पूर्ण

अटल अंतरभूत पूर्णांक __qib_sdma_running(काष्ठा qib_pportdata *ppd)
अणु
	वापस ppd->sdma_state.current_state == qib_sdma_state_s99_running;
पूर्ण
पूर्णांक qib_sdma_running(काष्ठा qib_pportdata *);
व्योम dump_sdma_state(काष्ठा qib_pportdata *ppd);
व्योम __qib_sdma_process_event(काष्ठा qib_pportdata *, क्रमागत qib_sdma_events);
व्योम qib_sdma_process_event(काष्ठा qib_pportdata *, क्रमागत qib_sdma_events);

/*
 * number of words used क्रम protocol header अगर not set by qib_userinit();
 */
#घोषणा QIB_DFLT_RCVHDRSIZE 9

/*
 * We need to be able to handle an IB header of at least 24 dwords.
 * We need the rcvhdrq large enough to handle largest IB header, but
 * still have room क्रम a 2KB MTU standard IB packet.
 * Additionally, some processor/memory controller combinations
 * benefit quite strongly from having the DMA'ed data be cacheline
 * aligned and a cacheline multiple, so we set the size to 32 dwords
 * (2 64-byte primary cachelines क्रम pretty much all processors of
 * पूर्णांकerest).  The alignment hurts nothing, other than using somewhat
 * more memory.
 */
#घोषणा QIB_RCVHDR_ENTSIZE 32

पूर्णांक qib_get_user_pages(अचिन्हित दीर्घ, माप_प्रकार, काष्ठा page **);
व्योम qib_release_user_pages(काष्ठा page **, माप_प्रकार);
पूर्णांक qib_eeprom_पढ़ो(काष्ठा qib_devdata *, u8, व्योम *, पूर्णांक);
पूर्णांक qib_eeprom_ग_लिखो(काष्ठा qib_devdata *, u8, स्थिर व्योम *, पूर्णांक);
u32 __iomem *qib_माला_लोendbuf_range(काष्ठा qib_devdata *, u32 *, u32, u32);
व्योम qib_sendbuf_करोne(काष्ठा qib_devdata *, अचिन्हित);

अटल अंतरभूत व्योम qib_clear_rcvhdrtail(स्थिर काष्ठा qib_ctxtdata *rcd)
अणु
	*((u64 *) rcd->rcvhdrtail_kvaddr) = 0ULL;
पूर्ण

अटल अंतरभूत u32 qib_get_rcvhdrtail(स्थिर काष्ठा qib_ctxtdata *rcd)
अणु
	/*
	 * अस्थिर because it's a DMA target from the chip, routine is
	 * अंतरभूतd, and करोn't want रेजिस्टर caching or reordering.
	 */
	वापस (u32) le64_to_cpu(
		*((अस्थिर __le64 *)rcd->rcvhdrtail_kvaddr)); /* DMA'ed */
पूर्ण

/*
 * sysfs पूर्णांकerface.
 */

बाह्य स्थिर अक्षर ib_qib_version[];
बाह्य स्थिर काष्ठा attribute_group qib_attr_group;

पूर्णांक qib_device_create(काष्ठा qib_devdata *);
व्योम qib_device_हटाओ(काष्ठा qib_devdata *);

पूर्णांक qib_create_port_files(काष्ठा ib_device *ibdev, u32 port_num,
			  काष्ठा kobject *kobj);
व्योम qib_verbs_unरेजिस्टर_sysfs(काष्ठा qib_devdata *);
/* Hook क्रम sysfs पढ़ो of QSFP */
बाह्य पूर्णांक qib_qsfp_dump(काष्ठा qib_pportdata *ppd, अक्षर *buf, पूर्णांक len);

पूर्णांक __init qib_init_qibfs(व्योम);
पूर्णांक __निकास qib_निकास_qibfs(व्योम);

पूर्णांक qibfs_add(काष्ठा qib_devdata *);
पूर्णांक qibfs_हटाओ(काष्ठा qib_devdata *);

पूर्णांक qib_pcie_init(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
पूर्णांक qib_pcie_ddinit(काष्ठा qib_devdata *, काष्ठा pci_dev *,
		    स्थिर काष्ठा pci_device_id *);
व्योम qib_pcie_ddcleanup(काष्ठा qib_devdata *);
पूर्णांक qib_pcie_params(काष्ठा qib_devdata *dd, u32 minw, u32 *nent);
व्योम qib_मुक्त_irq(काष्ठा qib_devdata *dd);
पूर्णांक qib_reinit_पूर्णांकr(काष्ठा qib_devdata *dd);
व्योम qib_pcie_अ_लोmd(काष्ठा qib_devdata *, u16 *, u8 *, u8 *);
व्योम qib_pcie_reenable(काष्ठा qib_devdata *, u16, u8, u8);
/* पूर्णांकerrupts क्रम device */
u64 qib_पूर्णांक_counter(काष्ठा qib_devdata *);
/* पूर्णांकerrupt क्रम all devices */
u64 qib_sps_पूर्णांकs(व्योम);

/*
 * dma_addr wrappers - all 0's invalid क्रम hw
 */
पूर्णांक qib_map_page(काष्ठा pci_dev *d, काष्ठा page *p, dma_addr_t *daddr);
काष्ठा pci_dev *qib_get_pci_dev(काष्ठा rvt_dev_info *rdi);

/*
 * Flush ग_लिखो combining store buffers (अगर present) and perक्रमm a ग_लिखो
 * barrier.
 */
अटल अंतरभूत व्योम qib_flush_wc(व्योम)
अणु
#अगर defined(CONFIG_X86_64)
	यंत्र अस्थिर("sfence" : : : "memory");
#अन्यथा
	wmb(); /* no reorder around wc flush */
#पूर्ण_अगर
पूर्ण

/* global module parameter variables */
बाह्य अचिन्हित qib_ibmtu;
बाह्य uलघु qib_cfgctxts;
बाह्य uलघु qib_num_cfg_vls;
बाह्य uलघु qib_mini_init; /* If set, करो few (ideally 0) ग_लिखोs to chip */
बाह्य अचिन्हित qib_n_krcv_queues;
बाह्य अचिन्हित qib_sdma_fetch_arb;
बाह्य अचिन्हित qib_compat_ddr_negotiate;
बाह्य पूर्णांक qib_special_trigger;
बाह्य अचिन्हित qib_numa_aware;

बाह्य काष्ठा mutex qib_mutex;

/* Number of seconds beक्रमe our card status check...  */
#घोषणा STATUS_TIMEOUT 60

#घोषणा QIB_DRV_NAME            "ib_qib"
#घोषणा QIB_USER_MINOR_BASE     0
#घोषणा QIB_TRACE_MINOR         127
#घोषणा QIB_DIAGPKT_MINOR       128
#घोषणा QIB_DIAG_MINOR_BASE     129
#घोषणा QIB_NMINORS             255

#घोषणा PCI_VENDOR_ID_PATHSCALE 0x1fc1
#घोषणा PCI_VENDOR_ID_QLOGIC 0x1077
#घोषणा PCI_DEVICE_ID_QLOGIC_IB_6120 0x10
#घोषणा PCI_DEVICE_ID_QLOGIC_IB_7220 0x7220
#घोषणा PCI_DEVICE_ID_QLOGIC_IB_7322 0x7322

/*
 * qib_early_err is used (only!) to prपूर्णांक early errors beक्रमe devdata is
 * allocated, or when dd->pcidev may not be valid, and at the tail end of
 * cleanup when devdata may have been मुक्तd, etc.  qib_dev_porterr is
 * the same as qib_dev_err, but is used when the message really needs
 * the IB port# to be definitive as to what's happening..
 * All of these go to the trace log, and the trace log entry is करोne
 * first to aव्योम possible serial port delays from prपूर्णांकk.
 */
#घोषणा qib_early_err(dev, fmt, ...) \
	dev_err(dev, fmt, ##__VA_ARGS__)

#घोषणा qib_dev_err(dd, fmt, ...) \
	dev_err(&(dd)->pcidev->dev, "%s: " fmt, \
		rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), ##__VA_ARGS__)

#घोषणा qib_dev_warn(dd, fmt, ...) \
	dev_warn(&(dd)->pcidev->dev, "%s: " fmt, \
		 rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), ##__VA_ARGS__)

#घोषणा qib_dev_porterr(dd, port, fmt, ...) \
	dev_err(&(dd)->pcidev->dev, "%s: IB%u:%u " fmt, \
		rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), (dd)->unit, (port), \
		##__VA_ARGS__)

#घोषणा qib_devinfo(pcidev, fmt, ...) \
	dev_info(&(pcidev)->dev, fmt, ##__VA_ARGS__)

/*
 * this is used क्रम क्रमmatting hw error messages...
 */
काष्ठा qib_hwerror_msgs अणु
	u64 mask;
	स्थिर अक्षर *msg;
	माप_प्रकार sz;
पूर्ण;

#घोषणा QLOGIC_IB_HWE_MSG(a, b) अणु .mask = a, .msg = b पूर्ण

/* in qib_पूर्णांकr.c... */
व्योम qib_क्रमmat_hwerrors(u64 hwerrs,
			 स्थिर काष्ठा qib_hwerror_msgs *hwerrmsgs,
			 माप_प्रकार nhwerrmsgs, अक्षर *msg, माप_प्रकार lmsg);

व्योम qib_stop_send_queue(काष्ठा rvt_qp *qp);
व्योम qib_quiesce_qp(काष्ठा rvt_qp *qp);
व्योम qib_flush_qp_रुकोers(काष्ठा rvt_qp *qp);
पूर्णांक qib_mtu_to_path_mtu(u32 mtu);
u32 qib_mtu_from_qp(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp, u32 pmtu);
व्योम qib_notअगरy_error_qp(काष्ठा rvt_qp *qp);
पूर्णांक qib_get_pmtu_from_attr(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
			   काष्ठा ib_qp_attr *attr);

#पूर्ण_अगर                          /* _QIB_KERNEL_H */
