<शैली गुरु>
#अगर_अघोषित _HFI1_KERNEL_H
#घोषणा _HFI1_KERNEL_H
/*
 * Copyright(c) 2020 Cornelis Networks, Inc.
 * Copyright(c) 2015-2020 Intel Corporation.
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
#समावेश <linux/cdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/xarray.h>
#समावेश <rdma/ib_hdrs.h>
#समावेश <rdma/opa_addr.h>
#समावेश <linux/rhashtable.h>
#समावेश <rdma/rdma_vt.h>

#समावेश "chip_registers.h"
#समावेश "common.h"
#समावेश "opfn.h"
#समावेश "verbs.h"
#समावेश "pio.h"
#समावेश "chip.h"
#समावेश "mad.h"
#समावेश "qsfp.h"
#समावेश "platform.h"
#समावेश "affinity.h"
#समावेश "msix.h"

/* bumped 1 from s/w major version of TrueScale */
#घोषणा HFI1_CHIP_VERS_MAJ 3U

/* करोn't care about this except prपूर्णांकing */
#घोषणा HFI1_CHIP_VERS_MIN 0U

/* The Organization Unique Identअगरier (Mfg code), and its position in GUID */
#घोषणा HFI1_OUI 0x001175
#घोषणा HFI1_OUI_LSB 40

#घोषणा DROP_PACKET_OFF		0
#घोषणा DROP_PACKET_ON		1

#घोषणा NEIGHBOR_TYPE_HFI		0
#घोषणा NEIGHBOR_TYPE_SWITCH	1

#घोषणा HFI1_MAX_ACTIVE_WORKQUEUE_ENTRIES 5

बाह्य अचिन्हित दीर्घ hfi1_cap_mask;
#घोषणा HFI1_CAP_KGET_MASK(mask, cap) ((mask) & HFI1_CAP_##cap)
#घोषणा HFI1_CAP_UGET_MASK(mask, cap) \
	(((mask) >> HFI1_CAP_USER_SHIFT) & HFI1_CAP_##cap)
#घोषणा HFI1_CAP_KGET(cap) (HFI1_CAP_KGET_MASK(hfi1_cap_mask, cap))
#घोषणा HFI1_CAP_UGET(cap) (HFI1_CAP_UGET_MASK(hfi1_cap_mask, cap))
#घोषणा HFI1_CAP_IS_KSET(cap) (!!HFI1_CAP_KGET(cap))
#घोषणा HFI1_CAP_IS_USET(cap) (!!HFI1_CAP_UGET(cap))
#घोषणा HFI1_MISC_GET() ((hfi1_cap_mask >> HFI1_CAP_MISC_SHIFT) & \
			HFI1_CAP_MISC_MASK)
/* Offline Disabled Reason is 4-bits */
#घोषणा HFI1_ODR_MASK(rsn) ((rsn) & OPA_PI_MASK_OFFLINE_REASON)

/*
 * Control context is always 0 and handles the error packets.
 * It also handles the VL15 and multicast packets.
 */
#घोषणा HFI1_CTRL_CTXT    0

/*
 * Driver context will store software counters क्रम each of the events
 * associated with these status रेजिस्टरs
 */
#घोषणा NUM_CCE_ERR_STATUS_COUNTERS 41
#घोषणा NUM_RCV_ERR_STATUS_COUNTERS 64
#घोषणा NUM_MISC_ERR_STATUS_COUNTERS 13
#घोषणा NUM_SEND_PIO_ERR_STATUS_COUNTERS 36
#घोषणा NUM_SEND_DMA_ERR_STATUS_COUNTERS 4
#घोषणा NUM_SEND_EGRESS_ERR_STATUS_COUNTERS 64
#घोषणा NUM_SEND_ERR_STATUS_COUNTERS 3
#घोषणा NUM_SEND_CTXT_ERR_STATUS_COUNTERS 5
#घोषणा NUM_SEND_DMA_ENG_ERR_STATUS_COUNTERS 24

/*
 * per driver stats, either not device nor port-specअगरic, or
 * summed over all of the devices and ports.
 * They are described by name via ipathfs fileप्रणाली, so layout
 * and number of elements can change without अवरोधing compatibility.
 * If members are added or deleted hfi1_statnames[] in debugfs.c must
 * change to match.
 */
काष्ठा hfi1_ib_stats अणु
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

बाह्य काष्ठा hfi1_ib_stats hfi1_stats;
बाह्य स्थिर काष्ठा pci_error_handlers hfi1_pci_err_handler;

बाह्य पूर्णांक num_driver_cntrs;

/*
 * First-cut criterion क्रम "device is active" is
 * two thousand dwords combined Tx, Rx traffic per
 * 5-second पूर्णांकerval. SMA packets are 64 dwords,
 * and occur "a few per second", presumably each way.
 */
#घोषणा HFI1_TRAFFIC_ACTIVE_THRESHOLD (2000)

/*
 * Below contains all data related to a single context (क्रमmerly called port).
 */

काष्ठा hfi1_opcode_stats_perctx;

काष्ठा ctxt_eager_bufs अणु
	काष्ठा eager_buffer अणु
		व्योम *addr;
		dma_addr_t dma;
		sमाप_प्रकार len;
	पूर्ण *buffers;
	काष्ठा अणु
		व्योम *addr;
		dma_addr_t dma;
	पूर्ण *rcvtids;
	u32 size;                /* total size of eager buffers */
	u32 rcvtid_size;         /* size of each eager rcv tid */
	u16 count;               /* size of buffers array */
	u16 numbufs;             /* number of buffers allocated */
	u16 alloced;             /* number of rcvarray entries used */
	u16 threshold;           /* head update threshold */
पूर्ण;

काष्ठा exp_tid_set अणु
	काष्ठा list_head list;
	u32 count;
पूर्ण;

काष्ठा hfi1_ctxtdata;
प्रकार पूर्णांक (*पूर्णांकr_handler)(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक data);
प्रकार व्योम (*rhf_rcv_function_ptr)(काष्ठा hfi1_packet *packet);

काष्ठा tid_queue अणु
	काष्ठा list_head queue_head;
			/* queue head क्रम QP TID resource रुकोers */
	u32 enqueue;	/* count of tid enqueues */
	u32 dequeue;	/* count of tid dequeues */
पूर्ण;

काष्ठा hfi1_ctxtdata अणु
	/* rcvhdrq base, needs mmap beक्रमe useful */
	व्योम *rcvhdrq;
	/* kernel भव address where hdrqtail is updated */
	अस्थिर __le64 *rcvhdrtail_kvaddr;
	/* so functions that need physical port can get it easily */
	काष्ठा hfi1_pportdata *ppd;
	/* so file ops can get at unit */
	काष्ठा hfi1_devdata *dd;
	/* this receive context's asचिन्हित PIO ACK send context */
	काष्ठा send_context *sc;
	/* per context recv functions */
	स्थिर rhf_rcv_function_ptr *rhf_rcv_function_map;
	/*
	 * The पूर्णांकerrupt handler क्रम a particular receive context can vary
	 * throughout it's lअगरeसमय. This is not a lock रक्षित data member so
	 * it must be updated atomically and the prev and new value must always
	 * be valid. Worst हाल is we process an extra पूर्णांकerrupt and up to 64
	 * packets with the wrong पूर्णांकerrupt handler.
	 */
	पूर्णांकr_handler करो_पूर्णांकerrupt;
	/** fast handler after स्वतःactive */
	पूर्णांकr_handler fast_handler;
	/** slow handler */
	पूर्णांकr_handler slow_handler;
	/* napi poपूर्णांकer assiociated with netdev */
	काष्ठा napi_काष्ठा *napi;
	/* verbs rx_stats per rcd */
	काष्ठा hfi1_opcode_stats_perctx *opstats;
	/* clear पूर्णांकerrupt mask */
	u64 imask;
	/* ctxt rcvhdrq head offset */
	u32 head;
	/* number of rcvhdrq entries */
	u16 rcvhdrq_cnt;
	u8 ireg;	/* clear पूर्णांकerrupt रेजिस्टर */
	/* receive packet sequence counter */
	u8 seq_cnt;
	/* size of each of the rcvhdrq entries */
	u8 rcvhdrqentsize;
	/* offset of RHF within receive header entry */
	u8 rhf_offset;
	/* dynamic receive available पूर्णांकerrupt समयout */
	u8 rcvavail_समयout;
	/* Indicates that this is vnic context */
	bool is_vnic;
	/* vnic queue index this context is mapped to */
	u8 vnic_q_idx;
	/* Is ASPM पूर्णांकerrupt supported क्रम this context */
	bool aspm_पूर्णांकr_supported;
	/* ASPM state (enabled/disabled) क्रम this context */
	bool aspm_enabled;
	/* Is ASPM processing enabled क्रम this context (in पूर्णांकr context) */
	bool aspm_पूर्णांकr_enable;
	काष्ठा ctxt_eager_bufs egrbufs;
	/* QPs रुकोing क्रम context processing */
	काष्ठा list_head qp_रुको_list;
	/* tid allocation lists */
	काष्ठा exp_tid_set tid_group_list;
	काष्ठा exp_tid_set tid_used_list;
	काष्ठा exp_tid_set tid_full_list;

	/* Timer क्रम re-enabling ASPM अगर पूर्णांकerrupt activity quiets करोwn */
	काष्ठा समयr_list aspm_समयr;
	/* per-context configuration flags */
	अचिन्हित दीर्घ flags;
	/* array of tid_groups */
	काष्ठा tid_group  *groups;
	/* mmap of hdrq, must fit in 44 bits */
	dma_addr_t rcvhdrq_dma;
	dma_addr_t rcvhdrqtailaddr_dma;
	/* Last पूर्णांकerrupt बारtamp */
	kसमय_प्रकार aspm_ts_last_पूर्णांकr;
	/* Last बारtamp at which we scheduled a समयr क्रम this context */
	kसमय_प्रकार aspm_ts_समयr_sched;
	/* Lock to serialize between पूर्णांकr, समयr पूर्णांकr and user thपढ़ोs */
	spinlock_t aspm_lock;
	/* Reference count the base context usage */
	काष्ठा kref kref;
	/* numa node of this context */
	पूर्णांक numa_id;
	/* associated msix पूर्णांकerrupt. */
	s16 msix_पूर्णांकr;
	/* job key */
	u16 jkey;
	/* number of RcvArray groups क्रम this context. */
	u16 rcv_array_groups;
	/* index of first eager TID entry. */
	u16 eager_base;
	/* number of expected TID entries */
	u16 expected_count;
	/* index of first expected TID entry. */
	u16 expected_base;
	/* Device context index */
	u8 ctxt;

	/* PSM Specअगरic fields */
	/* lock protecting all Expected TID data */
	काष्ठा mutex exp_mutex;
	/* lock protecting all Expected TID data of kernel contexts */
	spinlock_t exp_lock;
	/* Queue क्रम QP's रुकोing क्रम HW TID flows */
	काष्ठा tid_queue flow_queue;
	/* Queue क्रम QP's रुकोing क्रम HW receive array entries */
	काष्ठा tid_queue rarr_queue;
	/* when रुकोing क्रम rcv or pioavail */
	रुको_queue_head_t रुको;
	/* uuid from PSM */
	u8 uuid[16];
	/* same size as task_काष्ठा .comm[], command that खोलोed context */
	अक्षर comm[TASK_COMM_LEN];
	/* Biपंचांगask of in use context(s) */
	DECLARE_BITMAP(in_use_ctxts, HFI1_MAX_SHARED_CTXTS);
	/* per-context event flags क्रम fileops/पूर्णांकr communication */
	अचिन्हित दीर्घ event_flags;
	/* A page of memory क्रम rcvhdrhead, rcvegrhead, rcvegrtail * N */
	व्योम *subctxt_uregbase;
	/* An array of pages क्रम the eager receive buffers * N */
	व्योम *subctxt_rcvegrbuf;
	/* An array of pages क्रम the eager header queue entries * N */
	व्योम *subctxt_rcvhdr_base;
	/* total number of polled urgent packets */
	u32 urgent;
	/* saved total number of polled urgent packets क्रम poll edge trigger */
	u32 urgent_poll;
	/* Type of packets or conditions we want to poll क्रम */
	u16 poll_type;
	/* non-zero अगर ctxt is being shared. */
	u16 subctxt_id;
	/* The version of the library which खोलोed this ctxt */
	u32 userversion;
	/*
	 * non-zero अगर ctxt can be shared, and defines the maximum number of
	 * sub-contexts क्रम this device context.
	 */
	u8 subctxt_cnt;

	/* Bit mask to track मुक्त TID RDMA HW flows */
	अचिन्हित दीर्घ flow_mask;
	काष्ठा tid_flow_state flows[RXE_NUM_TID_FLOWS];
पूर्ण;

/**
 * rcvhdrq_size - वापस total size in bytes क्रम header queue
 * @rcd: the receive context
 *
 * rcvhdrqentsize is in DWs, so we have to convert to bytes
 *
 */
अटल अंतरभूत u32 rcvhdrq_size(काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस PAGE_ALIGN(rcd->rcvhdrq_cnt *
			  rcd->rcvhdrqentsize * माप(u32));
पूर्ण

/*
 * Represents a single packet at a high level. Put commonly computed things in
 * here so we करो not have to keep करोing them over and over. The rule of thumb is
 * अगर something is used one समय to derive some value, store that something in
 * here. If it is used multiple बार, then store the result of that derivation
 * in here.
 */
काष्ठा hfi1_packet अणु
	व्योम *ebuf;
	व्योम *hdr;
	व्योम *payload;
	काष्ठा hfi1_ctxtdata *rcd;
	__le32 *rhf_addr;
	काष्ठा rvt_qp *qp;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा ib_grh *grh;
	काष्ठा opa_16b_mgmt *mgmt;
	u64 rhf;
	u32 maxcnt;
	u32 rhqoff;
	u32 dlid;
	u32 slid;
	पूर्णांक numpkt;
	u16 tlen;
	s16 etail;
	u16 pkey;
	u8 hlen;
	u8 rsize;
	u8 updegr;
	u8 etype;
	u8 extra_byte;
	u8 pad;
	u8 sc;
	u8 sl;
	u8 opcode;
	bool migrated;
पूर्ण;

/* Packet types */
#घोषणा HFI1_PKT_TYPE_9B  0
#घोषणा HFI1_PKT_TYPE_16B 1

/*
 * OPA 16B Header
 */
#घोषणा OPA_16B_L4_MASK		0xFFull
#घोषणा OPA_16B_SC_MASK		0x1F00000ull
#घोषणा OPA_16B_SC_SHIFT	20
#घोषणा OPA_16B_LID_MASK	0xFFFFFull
#घोषणा OPA_16B_DLID_MASK	0xF000ull
#घोषणा OPA_16B_DLID_SHIFT	20
#घोषणा OPA_16B_DLID_HIGH_SHIFT	12
#घोषणा OPA_16B_SLID_MASK	0xF00ull
#घोषणा OPA_16B_SLID_SHIFT	20
#घोषणा OPA_16B_SLID_HIGH_SHIFT	8
#घोषणा OPA_16B_BECN_MASK       0x80000000ull
#घोषणा OPA_16B_BECN_SHIFT      31
#घोषणा OPA_16B_FECN_MASK       0x10000000ull
#घोषणा OPA_16B_FECN_SHIFT      28
#घोषणा OPA_16B_L2_MASK		0x60000000ull
#घोषणा OPA_16B_L2_SHIFT	29
#घोषणा OPA_16B_PKEY_MASK	0xFFFF0000ull
#घोषणा OPA_16B_PKEY_SHIFT	16
#घोषणा OPA_16B_LEN_MASK	0x7FF00000ull
#घोषणा OPA_16B_LEN_SHIFT	20
#घोषणा OPA_16B_RC_MASK		0xE000000ull
#घोषणा OPA_16B_RC_SHIFT	25
#घोषणा OPA_16B_AGE_MASK	0xFF0000ull
#घोषणा OPA_16B_AGE_SHIFT	16
#घोषणा OPA_16B_ENTROPY_MASK	0xFFFFull

/*
 * OPA 16B L2/L4 Encodings
 */
#घोषणा OPA_16B_L4_9B		0x00
#घोषणा OPA_16B_L2_TYPE		0x02
#घोषणा OPA_16B_L4_FM		0x08
#घोषणा OPA_16B_L4_IB_LOCAL	0x09
#घोषणा OPA_16B_L4_IB_GLOBAL	0x0A
#घोषणा OPA_16B_L4_ETHR		OPA_VNIC_L4_ETHR

/*
 * OPA 16B Management
 */
#घोषणा OPA_16B_L4_FM_PAD	3  /* fixed 3B pad */
#घोषणा OPA_16B_L4_FM_HLEN	24 /* 16B(16) + L4_FM(8) */

अटल अंतरभूत u8 hfi1_16B_get_l4(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u8)(hdr->lrh[2] & OPA_16B_L4_MASK);
पूर्ण

अटल अंतरभूत u8 hfi1_16B_get_sc(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u8)((hdr->lrh[1] & OPA_16B_SC_MASK) >> OPA_16B_SC_SHIFT);
पूर्ण

अटल अंतरभूत u32 hfi1_16B_get_dlid(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u32)((hdr->lrh[1] & OPA_16B_LID_MASK) |
		     (((hdr->lrh[2] & OPA_16B_DLID_MASK) >>
		     OPA_16B_DLID_HIGH_SHIFT) << OPA_16B_DLID_SHIFT));
पूर्ण

अटल अंतरभूत u32 hfi1_16B_get_slid(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u32)((hdr->lrh[0] & OPA_16B_LID_MASK) |
		     (((hdr->lrh[2] & OPA_16B_SLID_MASK) >>
		     OPA_16B_SLID_HIGH_SHIFT) << OPA_16B_SLID_SHIFT));
पूर्ण

अटल अंतरभूत u8 hfi1_16B_get_becn(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u8)((hdr->lrh[0] & OPA_16B_BECN_MASK) >> OPA_16B_BECN_SHIFT);
पूर्ण

अटल अंतरभूत u8 hfi1_16B_get_fecn(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u8)((hdr->lrh[1] & OPA_16B_FECN_MASK) >> OPA_16B_FECN_SHIFT);
पूर्ण

अटल अंतरभूत u8 hfi1_16B_get_l2(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u8)((hdr->lrh[1] & OPA_16B_L2_MASK) >> OPA_16B_L2_SHIFT);
पूर्ण

अटल अंतरभूत u16 hfi1_16B_get_pkey(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u16)((hdr->lrh[2] & OPA_16B_PKEY_MASK) >> OPA_16B_PKEY_SHIFT);
पूर्ण

अटल अंतरभूत u8 hfi1_16B_get_rc(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u8)((hdr->lrh[1] & OPA_16B_RC_MASK) >> OPA_16B_RC_SHIFT);
पूर्ण

अटल अंतरभूत u8 hfi1_16B_get_age(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u8)((hdr->lrh[3] & OPA_16B_AGE_MASK) >> OPA_16B_AGE_SHIFT);
पूर्ण

अटल अंतरभूत u16 hfi1_16B_get_len(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u16)((hdr->lrh[0] & OPA_16B_LEN_MASK) >> OPA_16B_LEN_SHIFT);
पूर्ण

अटल अंतरभूत u16 hfi1_16B_get_entropy(काष्ठा hfi1_16b_header *hdr)
अणु
	वापस (u16)(hdr->lrh[3] & OPA_16B_ENTROPY_MASK);
पूर्ण

#घोषणा OPA_16B_MAKE_QW(low_dw, high_dw) (((u64)(high_dw) << 32) | (low_dw))

/*
 * BTH
 */
#घोषणा OPA_16B_BTH_PAD_MASK	7
अटल अंतरभूत u8 hfi1_16B_bth_get_pad(काष्ठा ib_other_headers *ohdr)
अणु
	वापस (u8)((be32_to_cpu(ohdr->bth[0]) >> IB_BTH_PAD_SHIFT) &
		   OPA_16B_BTH_PAD_MASK);
पूर्ण

/*
 * 16B Management
 */
#घोषणा OPA_16B_MGMT_QPN_MASK	0xFFFFFF
अटल अंतरभूत u32 hfi1_16B_get_dest_qpn(काष्ठा opa_16b_mgmt *mgmt)
अणु
	वापस be32_to_cpu(mgmt->dest_qpn) & OPA_16B_MGMT_QPN_MASK;
पूर्ण

अटल अंतरभूत u32 hfi1_16B_get_src_qpn(काष्ठा opa_16b_mgmt *mgmt)
अणु
	वापस be32_to_cpu(mgmt->src_qpn) & OPA_16B_MGMT_QPN_MASK;
पूर्ण

अटल अंतरभूत व्योम hfi1_16B_set_qpn(काष्ठा opa_16b_mgmt *mgmt,
				    u32 dest_qp, u32 src_qp)
अणु
	mgmt->dest_qpn = cpu_to_be32(dest_qp & OPA_16B_MGMT_QPN_MASK);
	mgmt->src_qpn = cpu_to_be32(src_qp & OPA_16B_MGMT_QPN_MASK);
पूर्ण

/**
 * hfi1_get_rc_ohdr - get extended header
 * @opah - the opaheader
 */
अटल अंतरभूत काष्ठा ib_other_headers *
hfi1_get_rc_ohdr(काष्ठा hfi1_opa_header *opah)
अणु
	काष्ठा ib_other_headers *ohdr;
	काष्ठा ib_header *hdr = शून्य;
	काष्ठा hfi1_16b_header *hdr_16b = शून्य;

	/* Find out where the BTH is */
	अगर (opah->hdr_type == HFI1_PKT_TYPE_9B) अणु
		hdr = &opah->ibh;
		अगर (ib_get_lnh(hdr) == HFI1_LRH_BTH)
			ohdr = &hdr->u.oth;
		अन्यथा
			ohdr = &hdr->u.l.oth;
	पूर्ण अन्यथा अणु
		u8 l4;

		hdr_16b = &opah->opah;
		l4  = hfi1_16B_get_l4(hdr_16b);
		अगर (l4 == OPA_16B_L4_IB_LOCAL)
			ohdr = &hdr_16b->u.oth;
		अन्यथा
			ohdr = &hdr_16b->u.l.oth;
	पूर्ण
	वापस ohdr;
पूर्ण

काष्ठा rvt_sge_state;

/*
 * Get/Set IB link-level config parameters क्रम f_get/set_ib_cfg()
 * Mostly क्रम MADs that set or query link parameters, also ipath
 * config पूर्णांकerfaces
 */
#घोषणा HFI1_IB_CFG_LIDLMC 0 /* LID (LS16b) and Mask (MS16b) */
#घोषणा HFI1_IB_CFG_LWID_DG_ENB 1 /* allowed Link-width करोwngrade */
#घोषणा HFI1_IB_CFG_LWID_ENB 2 /* allowed Link-width */
#घोषणा HFI1_IB_CFG_LWID 3 /* currently active Link-width */
#घोषणा HFI1_IB_CFG_SPD_ENB 4 /* allowed Link speeds */
#घोषणा HFI1_IB_CFG_SPD 5 /* current Link spd */
#घोषणा HFI1_IB_CFG_RXPOL_ENB 6 /* Auto-RX-polarity enable */
#घोषणा HFI1_IB_CFG_LREV_ENB 7 /* Auto-Lane-reversal enable */
#घोषणा HFI1_IB_CFG_LINKLATENCY 8 /* Link Latency (IB1.2 only) */
#घोषणा HFI1_IB_CFG_HRTBT 9 /* IB heartbeat off/enable/स्वतः; DDR/QDR only */
#घोषणा HFI1_IB_CFG_OP_VLS 10 /* operational VLs */
#घोषणा HFI1_IB_CFG_VL_HIGH_CAP 11 /* num of VL high priority weights */
#घोषणा HFI1_IB_CFG_VL_LOW_CAP 12 /* num of VL low priority weights */
#घोषणा HFI1_IB_CFG_OVERRUN_THRESH 13 /* IB overrun threshold */
#घोषणा HFI1_IB_CFG_PHYERR_THRESH 14 /* IB PHY error threshold */
#घोषणा HFI1_IB_CFG_LINKDEFAULT 15 /* IB link शेष (sleep/poll) */
#घोषणा HFI1_IB_CFG_PKEYS 16 /* update partition keys */
#घोषणा HFI1_IB_CFG_MTU 17 /* update MTU in IBC */
#घोषणा HFI1_IB_CFG_VL_HIGH_LIMIT 19
#घोषणा HFI1_IB_CFG_PMA_TICKS 20 /* PMA sample tick resolution */
#घोषणा HFI1_IB_CFG_PORT 21 /* चयन port we are connected to */

/*
 * HFI or Host Link States
 *
 * These describe the states the driver thinks the logical and physical
 * states are in.  Used as an argument to set_link_state().  Implemented
 * as bits क्रम easy multi-state checking.  The actual state can only be
 * one.
 */
#घोषणा __HLS_UP_INIT_BP	0
#घोषणा __HLS_UP_ARMED_BP	1
#घोषणा __HLS_UP_ACTIVE_BP	2
#घोषणा __HLS_DN_DOWNDEF_BP	3	/* link करोwn शेष */
#घोषणा __HLS_DN_POLL_BP	4
#घोषणा __HLS_DN_DISABLE_BP	5
#घोषणा __HLS_DN_OFFLINE_BP	6
#घोषणा __HLS_VERIFY_CAP_BP	7
#घोषणा __HLS_GOING_UP_BP	8
#घोषणा __HLS_GOING_OFFLINE_BP  9
#घोषणा __HLS_LINK_COOLDOWN_BP 10

#घोषणा HLS_UP_INIT	  BIT(__HLS_UP_INIT_BP)
#घोषणा HLS_UP_ARMED	  BIT(__HLS_UP_ARMED_BP)
#घोषणा HLS_UP_ACTIVE	  BIT(__HLS_UP_ACTIVE_BP)
#घोषणा HLS_DN_DOWNDEF	  BIT(__HLS_DN_DOWNDEF_BP) /* link करोwn शेष */
#घोषणा HLS_DN_POLL	  BIT(__HLS_DN_POLL_BP)
#घोषणा HLS_DN_DISABLE	  BIT(__HLS_DN_DISABLE_BP)
#घोषणा HLS_DN_OFFLINE	  BIT(__HLS_DN_OFFLINE_BP)
#घोषणा HLS_VERIFY_CAP	  BIT(__HLS_VERIFY_CAP_BP)
#घोषणा HLS_GOING_UP	  BIT(__HLS_GOING_UP_BP)
#घोषणा HLS_GOING_OFFLINE BIT(__HLS_GOING_OFFLINE_BP)
#घोषणा HLS_LINK_COOLDOWN BIT(__HLS_LINK_COOLDOWN_BP)

#घोषणा HLS_UP (HLS_UP_INIT | HLS_UP_ARMED | HLS_UP_ACTIVE)
#घोषणा HLS_DOWN ~(HLS_UP)

#घोषणा HLS_DEFAULT HLS_DN_POLL

/* use this MTU size अगर none other is given */
#घोषणा HFI1_DEFAULT_ACTIVE_MTU 10240
/* use this MTU size as the शेष maximum */
#घोषणा HFI1_DEFAULT_MAX_MTU 10240
/* शेष partition key */
#घोषणा DEFAULT_PKEY 0xffff

/*
 * Possible fabric manager config parameters क्रम fm_अणुget,setपूर्ण_table()
 */
#घोषणा FM_TBL_VL_HIGH_ARB		1 /* Get/set VL high prio weights */
#घोषणा FM_TBL_VL_LOW_ARB		2 /* Get/set VL low prio weights */
#घोषणा FM_TBL_BUFFER_CONTROL		3 /* Get/set Buffer Control */
#घोषणा FM_TBL_SC2VLNT			4 /* Get/set SC->VLnt */
#घोषणा FM_TBL_VL_PREEMPT_ELEMS		5 /* Get (no set) VL preempt elems */
#घोषणा FM_TBL_VL_PREEMPT_MATRIX	6 /* Get (no set) VL preempt matrix */

/*
 * Possible "operations" क्रम f_rcvctrl(ppd, op, ctxt)
 * these are bits so they can be combined, e.g.
 * HFI1_RCVCTRL_INTRAVAIL_ENB | HFI1_RCVCTRL_CTXT_ENB
 */
#घोषणा HFI1_RCVCTRL_TAILUPD_ENB 0x01
#घोषणा HFI1_RCVCTRL_TAILUPD_DIS 0x02
#घोषणा HFI1_RCVCTRL_CTXT_ENB 0x04
#घोषणा HFI1_RCVCTRL_CTXT_DIS 0x08
#घोषणा HFI1_RCVCTRL_INTRAVAIL_ENB 0x10
#घोषणा HFI1_RCVCTRL_INTRAVAIL_DIS 0x20
#घोषणा HFI1_RCVCTRL_PKEY_ENB 0x40  /* Note, शेष is enabled */
#घोषणा HFI1_RCVCTRL_PKEY_DIS 0x80
#घोषणा HFI1_RCVCTRL_TIDFLOW_ENB 0x0400
#घोषणा HFI1_RCVCTRL_TIDFLOW_DIS 0x0800
#घोषणा HFI1_RCVCTRL_ONE_PKT_EGR_ENB 0x1000
#घोषणा HFI1_RCVCTRL_ONE_PKT_EGR_DIS 0x2000
#घोषणा HFI1_RCVCTRL_NO_RHQ_DROP_ENB 0x4000
#घोषणा HFI1_RCVCTRL_NO_RHQ_DROP_DIS 0x8000
#घोषणा HFI1_RCVCTRL_NO_EGR_DROP_ENB 0x10000
#घोषणा HFI1_RCVCTRL_NO_EGR_DROP_DIS 0x20000
#घोषणा HFI1_RCVCTRL_URGENT_ENB 0x40000
#घोषणा HFI1_RCVCTRL_URGENT_DIS 0x80000

/* partition enक्रमcement flags */
#घोषणा HFI1_PART_ENFORCE_IN	0x1
#घोषणा HFI1_PART_ENFORCE_OUT	0x2

/* how often we check क्रम synthetic counter wrap around */
#घोषणा SYNTH_CNT_TIME 3

/* Counter flags */
#घोषणा CNTR_NORMAL		0x0 /* Normal counters, just पढ़ो रेजिस्टर */
#घोषणा CNTR_SYNTH		0x1 /* Synthetic counters, saturate at all 1s */
#घोषणा CNTR_DISABLED		0x2 /* Disable this counter */
#घोषणा CNTR_32BIT		0x4 /* Simulate 64 bits क्रम this counter */
#घोषणा CNTR_VL			0x8 /* Per VL counter */
#घोषणा CNTR_SDMA              0x10
#घोषणा CNTR_INVALID_VL		-1  /* Specअगरies invalid VL */
#घोषणा CNTR_MODE_W		0x0
#घोषणा CNTR_MODE_R		0x1

/* VLs Supported/Operational */
#घोषणा HFI1_MIN_VLS_SUPPORTED 1
#घोषणा HFI1_MAX_VLS_SUPPORTED 8

#घोषणा HFI1_GUIDS_PER_PORT  5
#घोषणा HFI1_PORT_GUID_INDEX 0

अटल अंतरभूत व्योम incr_cntr64(u64 *cntr)
अणु
	अगर (*cntr < (u64)-1LL)
		(*cntr)++;
पूर्ण

#घोषणा MAX_NAME_SIZE 64
काष्ठा hfi1_msix_entry अणु
	क्रमागत irq_type type;
	पूर्णांक irq;
	व्योम *arg;
	cpumask_t mask;
	काष्ठा irq_affinity_notअगरy notअगरy;
पूर्ण;

काष्ठा hfi1_msix_info अणु
	/* lock to synchronize in_use_msix access */
	spinlock_t msix_lock;
	DECLARE_BITMAP(in_use_msix, CCE_NUM_MSIX_VECTORS);
	काष्ठा hfi1_msix_entry *msix_entries;
	u16 max_requested;
पूर्ण;

/* per-SL CCA inक्रमmation */
काष्ठा cca_समयr अणु
	काष्ठा hrसमयr hrसमयr;
	काष्ठा hfi1_pportdata *ppd; /* पढ़ो-only */
	पूर्णांक sl; /* पढ़ो-only */
	u16 ccti; /* पढ़ो/ग_लिखो - current value of CCTI */
पूर्ण;

काष्ठा link_करोwn_reason अणु
	/*
	 * SMA-facing value.  Should be set from .latest when
	 * HLS_UP_* -> HLS_DN_* transition actually occurs.
	 */
	u8 sma;
	u8 latest;
पूर्ण;

क्रमागत अणु
	LO_PRIO_TABLE,
	HI_PRIO_TABLE,
	MAX_PRIO_TABLE
पूर्ण;

काष्ठा vl_arb_cache अणु
	/* protect vl arb cache */
	spinlock_t lock;
	काष्ठा ib_vl_weight_elem table[VL_ARB_TABLE_SIZE];
पूर्ण;

/*
 * The काष्ठाure below encapsulates data relevant to a physical IB Port.
 * Current chips support only one such port, but the separation
 * clarअगरies things a bit. Note that to conक्रमm to IB conventions,
 * port-numbers are one-based. The first or only port is port1.
 */
काष्ठा hfi1_pportdata अणु
	काष्ठा hfi1_ibport ibport_data;

	काष्ठा hfi1_devdata *dd;
	काष्ठा kobject pport_cc_kobj;
	काष्ठा kobject sc2vl_kobj;
	काष्ठा kobject sl2sc_kobj;
	काष्ठा kobject vl2mtu_kobj;

	/* PHY support */
	काष्ठा qsfp_data qsfp_info;
	/* Values क्रम SI tuning of SerDes */
	u32 port_type;
	u32 tx_preset_eq;
	u32 tx_preset_noeq;
	u32 rx_preset;
	u8  local_atten;
	u8  remote_atten;
	u8  शेष_atten;
	u8  max_घातer_class;

	/* did we पढ़ो platक्रमm config from scratch रेजिस्टरs? */
	bool config_from_scratch;

	/* GUIDs क्रम this पूर्णांकerface, in host order, guids[0] is a port guid */
	u64 guids[HFI1_GUIDS_PER_PORT];

	/* GUID क्रम peer पूर्णांकerface, in host order */
	u64 neighbor_guid;

	/* up or करोwn physical link state */
	u32 linkup;

	/*
	 * this address is mapped पढ़ो-only पूर्णांकo user processes so they can
	 * get status cheaply, whenever they want.  One qword of status per port
	 */
	u64 *statusp;

	/* SendDMA related entries */

	काष्ठा workqueue_काष्ठा *hfi1_wq;
	काष्ठा workqueue_काष्ठा *link_wq;

	/* move out of पूर्णांकerrupt context */
	काष्ठा work_काष्ठा link_vc_work;
	काष्ठा work_काष्ठा link_up_work;
	काष्ठा work_काष्ठा link_करोwn_work;
	काष्ठा work_काष्ठा sma_message_work;
	काष्ठा work_काष्ठा मुक्तze_work;
	काष्ठा work_काष्ठा link_करोwngrade_work;
	काष्ठा work_काष्ठा link_bounce_work;
	काष्ठा delayed_work start_link_work;
	/* host link state variables */
	काष्ठा mutex hls_lock;
	u32 host_link_state;

	/* these are the "32 bit" regs */

	u32 ibmtu; /* The MTU programmed क्रम this unit */
	/*
	 * Current max size IB packet (in bytes) including IB headers, that
	 * we can send. Changes when ibmtu changes.
	 */
	u32 ibmaxlen;
	u32 current_egress_rate; /* units [10^6 bits/sec] */
	/* LID programmed क्रम this instance */
	u32 lid;
	/* list of pkeys programmed; 0 अगर not set */
	u16 pkeys[MAX_PKEY_VALUES];
	u16 link_width_supported;
	u16 link_width_करोwngrade_supported;
	u16 link_speed_supported;
	u16 link_width_enabled;
	u16 link_width_करोwngrade_enabled;
	u16 link_speed_enabled;
	u16 link_width_active;
	u16 link_width_करोwngrade_tx_active;
	u16 link_width_करोwngrade_rx_active;
	u16 link_speed_active;
	u8 vls_supported;
	u8 vls_operational;
	u8 actual_vls_operational;
	/* LID mask control */
	u8 lmc;
	/* Rx Polarity inversion (compensate क्रम ~tx on partner) */
	u8 rx_pol_inv;

	u8 hw_pidx;     /* physical port index */
	u32 port;        /* IB port number and index पूर्णांकo dd->pports - 1 */
	/* type of neighbor node */
	u8 neighbor_type;
	u8 neighbor_normal;
	u8 neighbor_fm_security; /* 1 अगर firmware checking is disabled */
	u8 neighbor_port_number;
	u8 is_sm_config_started;
	u8 offline_disabled_reason;
	u8 is_active_optimize_enabled;
	u8 driver_link_पढ़ोy;	/* driver पढ़ोy क्रम active link */
	u8 link_enabled;	/* link enabled? */
	u8 linkinit_reason;
	u8 local_tx_rate;	/* rate given to 8051 firmware */
	u8 qsfp_retry_count;

	/* placeholders क्रम IB MAD packet settings */
	u8 overrun_threshold;
	u8 phy_error_threshold;
	अचिन्हित पूर्णांक is_link_करोwn_queued;

	/* Used to override LED behavior क्रम things like मुख्यtenance beaconing*/
	/*
	 * Alternates per phase of blink
	 * [0] holds LED off duration, [1] holds LED on duration
	 */
	अचिन्हित दीर्घ led_override_vals[2];
	u8 led_override_phase; /* LSB picks from vals[] */
	atomic_t led_override_समयr_active;
	/* Used to flash LEDs in override mode */
	काष्ठा समयr_list led_override_समयr;

	u32 sm_trap_qp;
	u32 sa_qp;

	/*
	 * cca_समयr_lock protects access to the per-SL cca_समयr
	 * काष्ठाures (specअगरically the ccti member).
	 */
	spinlock_t cca_समयr_lock ____cacheline_aligned_in_smp;
	काष्ठा cca_समयr cca_समयr[OPA_MAX_SLS];

	/* List of congestion control table entries */
	काष्ठा ib_cc_table_entry_shaकरोw ccti_entries[CC_TABLE_SHADOW_MAX];

	/* congestion entries, each entry corresponding to a SL */
	काष्ठा opa_congestion_setting_entry_shaकरोw
		congestion_entries[OPA_MAX_SLS];

	/*
	 * cc_state_lock protects (ग_लिखो) access to the per-port
	 * काष्ठा cc_state.
	 */
	spinlock_t cc_state_lock ____cacheline_aligned_in_smp;

	काष्ठा cc_state __rcu *cc_state;

	/* Total number of congestion control table entries */
	u16 total_cct_entry;

	/* Bit map identअगरying service level */
	u32 cc_sl_control_map;

	/* CA's max number of 64 entry units in the congestion control table */
	u8 cc_max_table_entries;

	/*
	 * begin congestion log related entries
	 * cc_log_lock protects all congestion log related data
	 */
	spinlock_t cc_log_lock ____cacheline_aligned_in_smp;
	u8 threshold_cong_event_map[OPA_MAX_SLS / 8];
	u16 threshold_event_counter;
	काष्ठा opa_hfi1_cong_log_event_पूर्णांकernal cc_events[OPA_CONG_LOG_ELEMS];
	पूर्णांक cc_log_idx; /* index क्रम logging events */
	पूर्णांक cc_mad_idx; /* index क्रम reporting events */
	/* end congestion log related entries */

	काष्ठा vl_arb_cache vl_arb_cache[MAX_PRIO_TABLE];

	/* port relative counter buffer */
	u64 *cntrs;
	/* port relative synthetic counter buffer */
	u64 *scntrs;
	/* port_xmit_discards are synthesized from dअगरferent egress errors */
	u64 port_xmit_discards;
	u64 port_xmit_discards_vl[C_VL_COUNT];
	u64 port_xmit_स्थिरraपूर्णांक_errors;
	u64 port_rcv_स्थिरraपूर्णांक_errors;
	/* count of 'link_err' पूर्णांकerrupts from DC */
	u64 link_करोwned;
	/* number of बार link retrained successfully */
	u64 link_up;
	/* number of बार a link unknown frame was reported */
	u64 unknown_frame_count;
	/* port_ltp_crc_mode is वापसed in 'portinfo' MADs */
	u16 port_ltp_crc_mode;
	/* port_crc_mode_enabled is the crc we support */
	u8 port_crc_mode_enabled;
	/* mgmt_allowed is also वापसed in 'portinfo' MADs */
	u8 mgmt_allowed;
	u8 part_enक्रमce; /* partition enक्रमcement flags */
	काष्ठा link_करोwn_reason local_link_करोwn_reason;
	काष्ठा link_करोwn_reason neigh_link_करोwn_reason;
	/* Value to be sent to link peer on LinkDown .*/
	u8 remote_link_करोwn_reason;
	/* Error events that will cause a port bounce. */
	u32 port_error_action;
	काष्ठा work_काष्ठा linkstate_active_work;
	/* Does this port need to prescan क्रम FECNs */
	bool cc_prescan;
	/*
	 * Sample sendWaitCnt & sendWaitVlCnt during link transition
	 * and counter request.
	 */
	u64 port_vl_xmit_रुको_last[C_VL_COUNT + 1];
	u16 prev_link_width;
	u64 vl_xmit_flit_cnt[C_VL_COUNT + 1];
पूर्ण;

प्रकार व्योम (*opcode_handler)(काष्ठा hfi1_packet *packet);
प्रकार व्योम (*hfi1_make_req)(काष्ठा rvt_qp *qp,
			      काष्ठा hfi1_pkt_state *ps,
			      काष्ठा rvt_swqe *wqe);
बाह्य स्थिर rhf_rcv_function_ptr normal_rhf_rcv_functions[];
बाह्य स्थिर rhf_rcv_function_ptr netdev_rhf_rcv_functions[];

/* वापस values क्रम the RHF receive functions */
#घोषणा RHF_RCV_CONTINUE  0	/* keep going */
#घोषणा RHF_RCV_DONE	  1	/* stop, this packet processed */
#घोषणा RHF_RCV_REPROCESS 2	/* stop. retain this packet */

काष्ठा rcv_array_data अणु
	u16 ngroups;
	u16 nctxt_extra;
	u8 group_size;
पूर्ण;

काष्ठा per_vl_data अणु
	u16 mtu;
	काष्ठा send_context *sc;
पूर्ण;

/* 16 to directly index */
#घोषणा PER_VL_SEND_CONTEXTS 16

काष्ठा err_info_rcvport अणु
	u8 status_and_code;
	u64 packet_flit1;
	u64 packet_flit2;
पूर्ण;

काष्ठा err_info_स्थिरraपूर्णांक अणु
	u8 status;
	u16 pkey;
	u32 slid;
पूर्ण;

काष्ठा hfi1_temp अणु
	अचिन्हित पूर्णांक curr;       /* current temperature */
	अचिन्हित पूर्णांक lo_lim;     /* low temperature limit */
	अचिन्हित पूर्णांक hi_lim;     /* high temperature limit */
	अचिन्हित पूर्णांक crit_lim;   /* critical temperature limit */
	u8 triggers;      /* temperature triggers */
पूर्ण;

काष्ठा hfi1_i2c_bus अणु
	काष्ठा hfi1_devdata *controlling_dd; /* current controlling device */
	काष्ठा i2c_adapter adapter;	/* bus details */
	काष्ठा i2c_algo_bit_data algo;	/* bus algorithm details */
	पूर्णांक num;			/* bus number, 0 or 1 */
पूर्ण;

/* common data between shared ASIC HFIs */
काष्ठा hfi1_asic_data अणु
	काष्ठा hfi1_devdata *dds[2];	/* back poपूर्णांकers */
	काष्ठा mutex asic_resource_mutex;
	काष्ठा hfi1_i2c_bus *i2c_bus0;
	काष्ठा hfi1_i2c_bus *i2c_bus1;
पूर्ण;

/* sizes क्रम both the QP and RSM map tables */
#घोषणा NUM_MAP_ENTRIES	 256
#घोषणा NUM_MAP_REGS      32

/* Virtual NIC inक्रमmation */
काष्ठा hfi1_vnic_data अणु
	काष्ठा kmem_cache *txreq_cache;
	u8 num_vports;
पूर्ण;

काष्ठा hfi1_vnic_vport_info;

/* device data काष्ठा now contains only "general per-device" info.
 * fields related to a physical IB port are in a hfi1_pportdata काष्ठा.
 */
काष्ठा sdma_engine;
काष्ठा sdma_vl_map;

#घोषणा BOARD_VERS_MAX 96 /* how दीर्घ the version string can be */
#घोषणा SERIAL_MAX 16 /* length of the serial number */

प्रकार पूर्णांक (*send_routine)(काष्ठा rvt_qp *, काष्ठा hfi1_pkt_state *, u64);
काष्ठा hfi1_netdev_rx;
काष्ठा hfi1_devdata अणु
	काष्ठा hfi1_ibdev verbs_dev;     /* must be first */
	/* poपूर्णांकers to related काष्ठाs क्रम this device */
	/* pci access data काष्ठाure */
	काष्ठा pci_dev *pcidev;
	काष्ठा cdev user_cdev;
	काष्ठा cdev diag_cdev;
	काष्ठा cdev ui_cdev;
	काष्ठा device *user_device;
	काष्ठा device *diag_device;
	काष्ठा device *ui_device;

	/* first mapping up to RcvArray */
	u8 __iomem *kregbase1;
	resource_माप_प्रकार physaddr;

	/* second uncached mapping from RcvArray to pio send buffers */
	u8 __iomem *kregbase2;
	/* क्रम detecting offset above kregbase2 address */
	u32 base2_start;

	/* Per VL data. Enough क्रम all VLs but not all elements are set/used. */
	काष्ठा per_vl_data vld[PER_VL_SEND_CONTEXTS];
	/* send context data */
	काष्ठा send_context_info *send_contexts;
	/* map hardware send contexts to software index */
	u8 *hw_to_sw;
	/* spinlock क्रम allocating and releasing send context resources */
	spinlock_t sc_lock;
	/* lock क्रम pio_map */
	spinlock_t pio_map_lock;
	/* Send Context initialization lock. */
	spinlock_t sc_init_lock;
	/* lock क्रम sdma_map */
	spinlock_t                          sde_map_lock;
	/* array of kernel send contexts */
	काष्ठा send_context **kernel_send_context;
	/* array of vl maps */
	काष्ठा pio_vl_map __rcu *pio_map;
	/* शेष flags to last descriptor */
	u64 शेष_desc1;

	/* fields common to all SDMA engines */

	अस्थिर __le64                    *sdma_heads_dma; /* DMA'ed by chip */
	dma_addr_t                          sdma_heads_phys;
	व्योम                               *sdma_pad_dma; /* DMA'ed by chip */
	dma_addr_t                          sdma_pad_phys;
	/* क्रम deallocation */
	माप_प्रकार                              sdma_heads_size;
	/* num used */
	u32                                 num_sdma;
	/* array of engines sized by num_sdma */
	काष्ठा sdma_engine                 *per_sdma;
	/* array of vl maps */
	काष्ठा sdma_vl_map __rcu           *sdma_map;
	/* SPC मुक्तze रुकोqueue and variable */
	रुको_queue_head_t		  sdma_unमुक्तze_wq;
	atomic_t			  sdma_unमुक्तze_count;

	u32 lcb_access_count;		/* count of LCB users */

	/* common data between shared ASIC HFIs in this OS */
	काष्ठा hfi1_asic_data *asic_data;

	/* mem-mapped poपूर्णांकer to base of PIO buffers */
	व्योम __iomem *piobase;
	/*
	 * ग_लिखो-combining mem-mapped poपूर्णांकer to base of RcvArray
	 * memory.
	 */
	व्योम __iomem *rcvarray_wc;
	/*
	 * credit वापस base - a per-NUMA range of DMA address that
	 * the chip will use to update the per-context मुक्त counter
	 */
	काष्ठा credit_वापस_base *cr_base;

	/* send context numbers and sizes क्रम each type */
	काष्ठा sc_config_sizes sc_sizes[SC_MAX];

	अक्षर *boardname; /* human पढ़ोable board info */

	u64 ctx0_seq_drop;

	/* reset value */
	u64 z_पूर्णांक_counter;
	u64 z_rcv_limit;
	u64 z_send_schedule;

	u64 __percpu *send_schedule;
	/* number of reserved contexts क्रम netdev usage */
	u16 num_netdev_contexts;
	/* number of receive contexts in use by the driver */
	u32 num_rcv_contexts;
	/* number of pio send contexts in use by the driver */
	u32 num_send_contexts;
	/*
	 * number of ctxts available क्रम PSM खोलो
	 */
	u32 मुक्तctxts;
	/* total number of available user/PSM contexts */
	u32 num_user_contexts;
	/* base receive पूर्णांकerrupt समयout, in CSR units */
	u32 rcv_पूर्णांकr_समयout_csr;

	spinlock_t sendctrl_lock; /* protect changes to SendCtrl */
	spinlock_t rcvctrl_lock; /* protect changes to RcvCtrl */
	spinlock_t uctxt_lock; /* protect rcd changes */
	काष्ठा mutex dc8051_lock; /* exclusive access to 8051 */
	काष्ठा workqueue_काष्ठा *update_cntr_wq;
	काष्ठा work_काष्ठा update_cntr_work;
	/* exclusive access to 8051 memory */
	spinlock_t dc8051_memlock;
	पूर्णांक dc8051_समयd_out;	/* remember अगर the 8051 समयd out */
	/*
	 * A page that will hold event notअगरication biपंचांगaps क्रम all
	 * contexts. This page will be mapped पूर्णांकo all processes.
	 */
	अचिन्हित दीर्घ *events;
	/*
	 * per unit status, see also portdata statusp
	 * mapped पढ़ो-only पूर्णांकo user processes so they can get unit and
	 * IB link status cheaply
	 */
	काष्ठा hfi1_status *status;

	/* revision रेजिस्टर shaकरोw */
	u64 revision;
	/* Base GUID क्रम device (network order) */
	u64 base_guid;

	/* both sides of the PCIe link are gen3 capable */
	u8 link_gen3_capable;
	u8 dc_shutकरोwn;
	/* localbus width (1, 2,4,8,16,32) from config space  */
	u32 lbus_width;
	/* localbus speed in MHz */
	u32 lbus_speed;
	पूर्णांक unit; /* unit # of this chip */
	पूर्णांक node; /* home node of this chip */

	/* save these PCI fields to restore after a reset */
	u32 pcibar0;
	u32 pcibar1;
	u32 pci_rom;
	u16 pci_command;
	u16 pcie_devctl;
	u16 pcie_lnkctl;
	u16 pcie_devctl2;
	u32 pci_msix0;
	u32 pci_tph2;

	/*
	 * ASCII serial number, from flash, large enough क्रम original
	 * all digit strings, and दीर्घer serial number क्रमmat
	 */
	u8 serial[SERIAL_MAX];
	/* human पढ़ोable board version */
	u8 boardversion[BOARD_VERS_MAX];
	u8 lbus_info[32]; /* human पढ़ोable localbus info */
	/* chip major rev, from CceRevision */
	u8 majrev;
	/* chip minor rev, from CceRevision */
	u8 minrev;
	/* hardware ID */
	u8 hfi1_id;
	/* implementation code */
	u8 icode;
	/* vAU of this device */
	u8 vau;
	/* vCU of this device */
	u8 vcu;
	/* link credits of this device */
	u16 link_credits;
	/* initial vl15 credits to use */
	u16 vl15_init;

	/*
	 * Cached value क्रम vl15buf, पढ़ो during verअगरy cap पूर्णांकerrupt. VL15
	 * credits are to be kept at 0 and set when handling the link-up
	 * पूर्णांकerrupt. This हटाओs the possibility of receiving VL15 MAD
	 * packets beक्रमe this HFI is पढ़ोy.
	 */
	u16 vl15buf_cached;

	/* Misc small पूर्णांकs */
	u8 n_krcv_queues;
	u8 qos_shअगरt;

	u16 irev;	/* implementation revision */
	u32 dc8051_ver; /* 8051 firmware version */

	spinlock_t hfi1_diag_trans_lock; /* protect diag observer ops */
	काष्ठा platक्रमm_config platक्रमm_config;
	काष्ठा platक्रमm_config_cache pcfg_cache;

	काष्ठा diag_client *diag_client;

	/* general पूर्णांकerrupt: mask of handled पूर्णांकerrupts */
	u64 gi_mask[CCE_NUM_INT_CSRS];

	काष्ठा rcv_array_data rcv_entries;

	/* cycle length of PS* counters in HW (in picoseconds) */
	u16 psxmitरुको_check_rate;

	/*
	 * 64 bit synthetic counters
	 */
	काष्ठा समयr_list synth_stats_समयr;

	/* MSI-X inक्रमmation */
	काष्ठा hfi1_msix_info msix_info;

	/*
	 * device counters
	 */
	अक्षर *cntrnames;
	माप_प्रकार cntrnameslen;
	माप_प्रकार ndevcntrs;
	u64 *cntrs;
	u64 *scntrs;

	/*
	 * remembered values क्रम synthetic counters
	 */
	u64 last_tx;
	u64 last_rx;

	/*
	 * per-port counters
	 */
	माप_प्रकार nportcntrs;
	अक्षर *portcntrnames;
	माप_प्रकार portcntrnameslen;

	काष्ठा err_info_rcvport err_info_rcvport;
	काष्ठा err_info_स्थिरraपूर्णांक err_info_rcv_स्थिरraपूर्णांक;
	काष्ठा err_info_स्थिरraपूर्णांक err_info_xmit_स्थिरraपूर्णांक;

	atomic_t drop_packet;
	bool करो_drop;
	u8 err_info_uncorrectable;
	u8 err_info_fmconfig;

	/*
	 * Software counters क्रम the status bits defined by the
	 * associated error status रेजिस्टरs
	 */
	u64 cce_err_status_cnt[NUM_CCE_ERR_STATUS_COUNTERS];
	u64 rcv_err_status_cnt[NUM_RCV_ERR_STATUS_COUNTERS];
	u64 misc_err_status_cnt[NUM_MISC_ERR_STATUS_COUNTERS];
	u64 send_pio_err_status_cnt[NUM_SEND_PIO_ERR_STATUS_COUNTERS];
	u64 send_dma_err_status_cnt[NUM_SEND_DMA_ERR_STATUS_COUNTERS];
	u64 send_egress_err_status_cnt[NUM_SEND_EGRESS_ERR_STATUS_COUNTERS];
	u64 send_err_status_cnt[NUM_SEND_ERR_STATUS_COUNTERS];

	/* Software counter that spans all contexts */
	u64 sw_ctxt_err_status_cnt[NUM_SEND_CTXT_ERR_STATUS_COUNTERS];
	/* Software counter that spans all DMA engines */
	u64 sw_send_dma_eng_err_status_cnt[
		NUM_SEND_DMA_ENG_ERR_STATUS_COUNTERS];
	/* Software counter that aggregates all cce_err_status errors */
	u64 sw_cce_err_status_aggregate;
	/* Software counter that aggregates all bypass packet rcv errors */
	u64 sw_rcv_bypass_packet_errors;

	/* Save the enabled LCB error bits */
	u64 lcb_err_en;
	काष्ठा cpu_mask_set *comp_vect;
	पूर्णांक *comp_vect_mappings;
	u32 comp_vect_possible_cpus;

	/*
	 * Capability to have dअगरferent send engines simply by changing a
	 * poपूर्णांकer value.
	 */
	send_routine process_pio_send ____cacheline_aligned_in_smp;
	send_routine process_dma_send;
	व्योम (*pio_अंतरभूत_send)(काष्ठा hfi1_devdata *dd, काष्ठा pio_buf *pbuf,
				u64 pbc, स्थिर व्योम *from, माप_प्रकार count);
	पूर्णांक (*process_vnic_dma_send)(काष्ठा hfi1_devdata *dd, u8 q_idx,
				     काष्ठा hfi1_vnic_vport_info *vinfo,
				     काष्ठा sk_buff *skb, u64 pbc, u8 plen);
	/* hfi1_pportdata, poपूर्णांकs to array of (physical) port-specअगरic
	 * data काष्ठाs, indexed by pidx (0..n-1)
	 */
	काष्ठा hfi1_pportdata *pport;
	/* receive context data */
	काष्ठा hfi1_ctxtdata **rcd;
	u64 __percpu *पूर्णांक_counter;
	/* verbs tx opcode stats */
	काष्ठा hfi1_opcode_stats_perctx __percpu *tx_opstats;
	/* device (not port) flags, basically device capabilities */
	u16 flags;
	/* Number of physical ports available */
	u8 num_pports;
	/* Lowest context number which can be used by user processes or VNIC */
	u8 first_dyn_alloc_ctxt;
	/* adding a new field here would make it part of this cacheline */

	/* seqlock क्रम sc2vl */
	seqlock_t sc2vl_lock ____cacheline_aligned_in_smp;
	u64 sc2vl[4];
	u64 __percpu *rcv_limit;
	/* adding a new field here would make it part of this cacheline */

	/* OUI comes from the HW. Used everywhere as 3 separate bytes. */
	u8 oui1;
	u8 oui2;
	u8 oui3;

	/* Timer and counter used to detect RcvBufOvflCnt changes */
	काष्ठा समयr_list rcverr_समयr;

	रुको_queue_head_t event_queue;

	/* receive context tail dummy address */
	__le64 *rcvhdrtail_dummy_kvaddr;
	dma_addr_t rcvhdrtail_dummy_dma;

	u32 rcv_ovfl_cnt;
	/* Serialize ASPM enable/disable between multiple verbs contexts */
	spinlock_t aspm_lock;
	/* Number of verbs contexts which have disabled ASPM */
	atomic_t aspm_disabled_cnt;
	/* Keeps track of user space clients */
	atomic_t user_refcount;
	/* Used to रुको क्रम outstanding user space clients beक्रमe dev removal */
	काष्ठा completion user_comp;

	bool eprom_available;	/* true अगर EPROM is available क्रम this device */
	bool aspm_supported;	/* Does HW support ASPM */
	bool aspm_enabled;	/* ASPM state: enabled/disabled */
	काष्ठा rhashtable *sdma_rht;

	/* vnic data */
	काष्ठा hfi1_vnic_data vnic;
	/* Lock to protect IRQ SRC रेजिस्टर access */
	spinlock_t irq_src_lock;
	पूर्णांक vnic_num_vports;
	काष्ठा hfi1_netdev_rx *netdev_rx;
	काष्ठा hfi1_affinity_node *affinity_entry;

	/* Keeps track of IPoIB RSM rule users */
	atomic_t ipoib_rsm_usr_num;
पूर्ण;

/* 8051 firmware version helper */
#घोषणा dc8051_ver(a, b, c) ((a) << 16 | (b) << 8 | (c))
#घोषणा dc8051_ver_maj(a) (((a) & 0xff0000) >> 16)
#घोषणा dc8051_ver_min(a) (((a) & 0x00ff00) >> 8)
#घोषणा dc8051_ver_patch(a) ((a) & 0x0000ff)

/* f_put_tid types */
#घोषणा PT_EXPECTED       0
#घोषणा PT_EAGER          1
#घोषणा PT_INVALID_FLUSH  2
#घोषणा PT_INVALID        3

काष्ठा tid_rb_node;
काष्ठा mmu_rb_node;
काष्ठा mmu_rb_handler;

/* Private data क्रम file operations */
काष्ठा hfi1_filedata अणु
	काष्ठा srcu_काष्ठा pq_srcu;
	काष्ठा hfi1_devdata *dd;
	काष्ठा hfi1_ctxtdata *uctxt;
	काष्ठा hfi1_user_sdma_comp_q *cq;
	/* update side lock क्रम SRCU */
	spinlock_t pq_rcu_lock;
	काष्ठा hfi1_user_sdma_pkt_q __rcu *pq;
	u16 subctxt;
	/* क्रम cpu affinity; -1 अगर none */
	पूर्णांक rec_cpu_num;
	u32 tid_n_pinned;
	bool use_mn;
	काष्ठा tid_rb_node **entry_to_rb;
	spinlock_t tid_lock; /* protect tid_[limit,used] counters */
	u32 tid_limit;
	u32 tid_used;
	u32 *invalid_tids;
	u32 invalid_tid_idx;
	/* protect invalid_tids array and invalid_tid_idx */
	spinlock_t invalid_lock;
पूर्ण;

बाह्य काष्ठा xarray hfi1_dev_table;
काष्ठा hfi1_devdata *hfi1_lookup(पूर्णांक unit);

अटल अंतरभूत अचिन्हित दीर्घ uctxt_offset(काष्ठा hfi1_ctxtdata *uctxt)
अणु
	वापस (uctxt->ctxt - uctxt->dd->first_dyn_alloc_ctxt) *
		HFI1_MAX_SHARED_CTXTS;
पूर्ण

पूर्णांक hfi1_init(काष्ठा hfi1_devdata *dd, पूर्णांक reinit);
पूर्णांक hfi1_count_active_units(व्योम);

पूर्णांक hfi1_diag_add(काष्ठा hfi1_devdata *dd);
व्योम hfi1_diag_हटाओ(काष्ठा hfi1_devdata *dd);
व्योम handle_linkup_change(काष्ठा hfi1_devdata *dd, u32 linkup);

व्योम handle_user_पूर्णांकerrupt(काष्ठा hfi1_ctxtdata *rcd);

पूर्णांक hfi1_create_rcvhdrq(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *rcd);
पूर्णांक hfi1_setup_eagerbufs(काष्ठा hfi1_ctxtdata *rcd);
पूर्णांक hfi1_create_kctxts(काष्ठा hfi1_devdata *dd);
पूर्णांक hfi1_create_ctxtdata(काष्ठा hfi1_pportdata *ppd, पूर्णांक numa,
			 काष्ठा hfi1_ctxtdata **rcd);
व्योम hfi1_मुक्त_ctxt(काष्ठा hfi1_ctxtdata *rcd);
व्योम hfi1_init_pportdata(काष्ठा pci_dev *pdev, काष्ठा hfi1_pportdata *ppd,
			 काष्ठा hfi1_devdata *dd, u8 hw_pidx, u32 port);
व्योम hfi1_मुक्त_ctxtdata(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *rcd);
पूर्णांक hfi1_rcd_put(काष्ठा hfi1_ctxtdata *rcd);
पूर्णांक hfi1_rcd_get(काष्ठा hfi1_ctxtdata *rcd);
काष्ठा hfi1_ctxtdata *hfi1_rcd_get_by_index_safe(काष्ठा hfi1_devdata *dd,
						 u16 ctxt);
काष्ठा hfi1_ctxtdata *hfi1_rcd_get_by_index(काष्ठा hfi1_devdata *dd, u16 ctxt);
पूर्णांक handle_receive_पूर्णांकerrupt(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक thपढ़ो);
पूर्णांक handle_receive_पूर्णांकerrupt_nodma_rtail(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक thपढ़ो);
पूर्णांक handle_receive_पूर्णांकerrupt_dma_rtail(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक thपढ़ो);
पूर्णांक handle_receive_पूर्णांकerrupt_napi_fp(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक budget);
पूर्णांक handle_receive_पूर्णांकerrupt_napi_sp(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक budget);
व्योम set_all_slowpath(काष्ठा hfi1_devdata *dd);

बाह्य स्थिर काष्ठा pci_device_id hfi1_pci_tbl[];
व्योम hfi1_make_ud_req_9B(काष्ठा rvt_qp *qp,
			 काष्ठा hfi1_pkt_state *ps,
			 काष्ठा rvt_swqe *wqe);

व्योम hfi1_make_ud_req_16B(काष्ठा rvt_qp *qp,
			  काष्ठा hfi1_pkt_state *ps,
			  काष्ठा rvt_swqe *wqe);

/* receive packet handler dispositions */
#घोषणा RCV_PKT_OK      0x0 /* keep going */
#घोषणा RCV_PKT_LIMIT   0x1 /* stop, hit limit, start thपढ़ो */
#घोषणा RCV_PKT_DONE    0x2 /* stop, no more packets detected */

/**
 * hfi1_rcd_head - add accessor क्रम rcd head
 * @rcd: the context
 */
अटल अंतरभूत u32 hfi1_rcd_head(काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस rcd->head;
पूर्ण

/**
 * hfi1_set_rcd_head - add accessor क्रम rcd head
 * @rcd: the context
 * @head: the new head
 */
अटल अंतरभूत व्योम hfi1_set_rcd_head(काष्ठा hfi1_ctxtdata *rcd, u32 head)
अणु
	rcd->head = head;
पूर्ण

/* calculate the current RHF address */
अटल अंतरभूत __le32 *get_rhf_addr(काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस (__le32 *)rcd->rcvhdrq + rcd->head + rcd->rhf_offset;
पूर्ण

/* वापस DMA_RTAIL configuration */
अटल अंतरभूत bool get_dma_rtail_setting(काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस !!HFI1_CAP_KGET_MASK(rcd->flags, DMA_RTAIL);
पूर्ण

/**
 * hfi1_seq_incr_wrap - wrapping increment क्रम sequence
 * @seq: the current sequence number
 *
 * Returns: the incremented seq
 */
अटल अंतरभूत u8 hfi1_seq_incr_wrap(u8 seq)
अणु
	अगर (++seq > RHF_MAX_SEQ)
		seq = 1;
	वापस seq;
पूर्ण

/**
 * hfi1_seq_cnt - वापस seq_cnt member
 * @rcd: the receive context
 *
 * Return seq_cnt member
 */
अटल अंतरभूत u8 hfi1_seq_cnt(काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस rcd->seq_cnt;
पूर्ण

/**
 * hfi1_set_seq_cnt - वापस seq_cnt member
 * @rcd: the receive context
 *
 * Return seq_cnt member
 */
अटल अंतरभूत व्योम hfi1_set_seq_cnt(काष्ठा hfi1_ctxtdata *rcd, u8 cnt)
अणु
	rcd->seq_cnt = cnt;
पूर्ण

/**
 * last_rcv_seq - is last
 * @rcd: the receive context
 * @seq: sequence
 *
 * वापस true अगर last packet
 */
अटल अंतरभूत bool last_rcv_seq(काष्ठा hfi1_ctxtdata *rcd, u32 seq)
अणु
	वापस seq != rcd->seq_cnt;
पूर्ण

/**
 * rcd_seq_incr - increment context sequence number
 * @rcd: the receive context
 * @seq: the current sequence number
 *
 * Returns: true अगर the this was the last packet
 */
अटल अंतरभूत bool hfi1_seq_incr(काष्ठा hfi1_ctxtdata *rcd, u32 seq)
अणु
	rcd->seq_cnt = hfi1_seq_incr_wrap(rcd->seq_cnt);
	वापस last_rcv_seq(rcd, seq);
पूर्ण

/**
 * get_hdrqentsize - वापस hdrq entry size
 * @rcd: the receive context
 */
अटल अंतरभूत u8 get_hdrqentsize(काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस rcd->rcvhdrqentsize;
पूर्ण

/**
 * get_hdrq_cnt - वापस hdrq count
 * @rcd: the receive context
 */
अटल अंतरभूत u16 get_hdrq_cnt(काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस rcd->rcvhdrq_cnt;
पूर्ण

/**
 * hfi1_is_slowpath - check अगर this context is slow path
 * @rcd: the receive context
 */
अटल अंतरभूत bool hfi1_is_slowpath(काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस rcd->करो_पूर्णांकerrupt == rcd->slow_handler;
पूर्ण

/**
 * hfi1_is_fastpath - check अगर this context is fast path
 * @rcd: the receive context
 */
अटल अंतरभूत bool hfi1_is_fastpath(काष्ठा hfi1_ctxtdata *rcd)
अणु
	अगर (rcd->ctxt == HFI1_CTRL_CTXT)
		वापस false;

	वापस rcd->करो_पूर्णांकerrupt == rcd->fast_handler;
पूर्ण

/**
 * hfi1_set_fast - change to the fast handler
 * @rcd: the receive context
 */
अटल अंतरभूत व्योम hfi1_set_fast(काष्ठा hfi1_ctxtdata *rcd)
अणु
	अगर (unlikely(!rcd))
		वापस;
	अगर (unlikely(!hfi1_is_fastpath(rcd)))
		rcd->करो_पूर्णांकerrupt = rcd->fast_handler;
पूर्ण

पूर्णांक hfi1_reset_device(पूर्णांक);

व्योम receive_पूर्णांकerrupt_work(काष्ठा work_काष्ठा *work);

/* extract service channel from header and rhf */
अटल अंतरभूत पूर्णांक hfi1_9B_get_sc5(काष्ठा ib_header *hdr, u64 rhf)
अणु
	वापस ib_get_sc(hdr) | ((!!(rhf_dc_info(rhf))) << 4);
पूर्ण

#घोषणा HFI1_JKEY_WIDTH       16
#घोषणा HFI1_JKEY_MASK        (BIT(16) - 1)
#घोषणा HFI1_ADMIN_JKEY_RANGE 32

/*
 * J_KEYs are split and allocated in the following groups:
 *   0 - 31    - users with administrator privileges
 *  32 - 63    - kernel protocols using KDETH packets
 *  64 - 65535 - all other users using KDETH packets
 */
अटल अंतरभूत u16 generate_jkey(kuid_t uid)
अणु
	u16 jkey = from_kuid(current_user_ns(), uid) & HFI1_JKEY_MASK;

	अगर (capable(CAP_SYS_ADMIN))
		jkey &= HFI1_ADMIN_JKEY_RANGE - 1;
	अन्यथा अगर (jkey < 64)
		jkey |= BIT(HFI1_JKEY_WIDTH - 1);

	वापस jkey;
पूर्ण

/*
 * active_egress_rate
 *
 * वापसs the active egress rate in units of [10^6 bits/sec]
 */
अटल अंतरभूत u32 active_egress_rate(काष्ठा hfi1_pportdata *ppd)
अणु
	u16 link_speed = ppd->link_speed_active;
	u16 link_width = ppd->link_width_active;
	u32 egress_rate;

	अगर (link_speed == OPA_LINK_SPEED_25G)
		egress_rate = 25000;
	अन्यथा /* assume OPA_LINK_SPEED_12_5G */
		egress_rate = 12500;

	चयन (link_width) अणु
	हाल OPA_LINK_WIDTH_4X:
		egress_rate *= 4;
		अवरोध;
	हाल OPA_LINK_WIDTH_3X:
		egress_rate *= 3;
		अवरोध;
	हाल OPA_LINK_WIDTH_2X:
		egress_rate *= 2;
		अवरोध;
	शेष:
		/* assume IB_WIDTH_1X */
		अवरोध;
	पूर्ण

	वापस egress_rate;
पूर्ण

/*
 * egress_cycles
 *
 * Returns the number of 'fabric clock cycles' to egress a packet
 * of length 'len' bytes, at 'rate' Mbit/s. Since the fabric घड़ी
 * rate is (approximately) 805 MHz, the units of the वापसed value
 * are (1/805 MHz).
 */
अटल अंतरभूत u32 egress_cycles(u32 len, u32 rate)
अणु
	u32 cycles;

	/*
	 * cycles is:
	 *
	 *          (length) [bits] / (rate) [bits/sec]
	 *  ---------------------------------------------------
	 *  fabric_घड़ी_period == 1 /(805 * 10^6) [cycles/sec]
	 */

	cycles = len * 8; /* bits */
	cycles *= 805;
	cycles /= rate;

	वापस cycles;
पूर्ण

व्योम set_link_ipg(काष्ठा hfi1_pportdata *ppd);
व्योम process_becn(काष्ठा hfi1_pportdata *ppd, u8 sl, u32 rlid, u32 lqpn,
		  u32 rqpn, u8 svc_type);
व्योम वापस_cnp(काष्ठा hfi1_ibport *ibp, काष्ठा rvt_qp *qp, u32 remote_qpn,
		u16 pkey, u32 slid, u32 dlid, u8 sc5,
		स्थिर काष्ठा ib_grh *old_grh);
व्योम वापस_cnp_16B(काष्ठा hfi1_ibport *ibp, काष्ठा rvt_qp *qp,
		    u32 remote_qpn, u16 pkey, u32 slid, u32 dlid,
		    u8 sc5, स्थिर काष्ठा ib_grh *old_grh);
प्रकार व्योम (*hfi1_handle_cnp)(काष्ठा hfi1_ibport *ibp, काष्ठा rvt_qp *qp,
				u32 remote_qpn, u16 pkey, u32 slid, u32 dlid,
				u8 sc5, स्थिर काष्ठा ib_grh *old_grh);

#घोषणा PKEY_CHECK_INVALID -1
पूर्णांक egress_pkey_check(काष्ठा hfi1_pportdata *ppd, u32 slid, u16 pkey,
		      u8 sc5, पूर्णांक8_t s_pkey_index);

#घोषणा PACKET_EGRESS_TIMEOUT 350
अटल अंतरभूत व्योम छोड़ो_क्रम_credit_वापस(काष्ठा hfi1_devdata *dd)
अणु
	/* Pause at least 1us, to ensure chip वापसs all credits */
	u32 usec = cघड़ी_प्रकारo_ns(dd, PACKET_EGRESS_TIMEOUT) / 1000;

	udelay(usec ? usec : 1);
पूर्ण

/**
 * sc_to_vlt() reverse lookup sc to vl
 * @dd - devdata
 * @sc5 - 5 bit sc
 */
अटल अंतरभूत u8 sc_to_vlt(काष्ठा hfi1_devdata *dd, u8 sc5)
अणु
	अचिन्हित seq;
	u8 rval;

	अगर (sc5 >= OPA_MAX_SCS)
		वापस (u8)(0xff);

	करो अणु
		seq = पढ़ो_seqbegin(&dd->sc2vl_lock);
		rval = *(((u8 *)dd->sc2vl) + sc5);
	पूर्ण जबतक (पढ़ो_seqretry(&dd->sc2vl_lock, seq));

	वापस rval;
पूर्ण

#घोषणा PKEY_MEMBER_MASK 0x8000
#घोषणा PKEY_LOW_15_MASK 0x7fff

/*
 * ingress_pkey_matches_entry - वापस 1 अगर the pkey matches ent (ent
 * being an entry from the ingress partition key table), वापस 0
 * otherwise. Use the matching criteria क्रम ingress partition keys
 * specअगरied in the OPAv1 spec., section 9.10.14.
 */
अटल अंतरभूत पूर्णांक ingress_pkey_matches_entry(u16 pkey, u16 ent)
अणु
	u16 mkey = pkey & PKEY_LOW_15_MASK;
	u16 ment = ent & PKEY_LOW_15_MASK;

	अगर (mkey == ment) अणु
		/*
		 * If pkey[15] is clear (limited partition member),
		 * is bit 15 in the corresponding table element
		 * clear (limited member)?
		 */
		अगर (!(pkey & PKEY_MEMBER_MASK))
			वापस !!(ent & PKEY_MEMBER_MASK);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ingress_pkey_table_search - search the entire pkey table क्रम
 * an entry which matches 'pkey'. वापस 0 अगर a match is found,
 * and 1 otherwise.
 */
अटल पूर्णांक ingress_pkey_table_search(काष्ठा hfi1_pportdata *ppd, u16 pkey)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_PKEY_VALUES; i++) अणु
		अगर (ingress_pkey_matches_entry(pkey, ppd->pkeys[i]))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * ingress_pkey_table_fail - record a failure of ingress pkey validation,
 * i.e., increment port_rcv_स्थिरraपूर्णांक_errors क्रम the port, and record
 * the 'error info' क्रम this failure.
 */
अटल व्योम ingress_pkey_table_fail(काष्ठा hfi1_pportdata *ppd, u16 pkey,
				    u32 slid)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;

	incr_cntr64(&ppd->port_rcv_स्थिरraपूर्णांक_errors);
	अगर (!(dd->err_info_rcv_स्थिरraपूर्णांक.status & OPA_EI_STATUS_SMASK)) अणु
		dd->err_info_rcv_स्थिरraपूर्णांक.status |= OPA_EI_STATUS_SMASK;
		dd->err_info_rcv_स्थिरraपूर्णांक.slid = slid;
		dd->err_info_rcv_स्थिरraपूर्णांक.pkey = pkey;
	पूर्ण
पूर्ण

/*
 * ingress_pkey_check - Return 0 अगर the ingress pkey is valid, वापस 1
 * otherwise. Use the criteria in the OPAv1 spec, section 9.10.14. idx
 * is a hपूर्णांक as to the best place in the partition key table to begin
 * searching. This function should not be called on the data path because
 * of perक्रमmance reasons. On datapath pkey check is expected to be करोne
 * by HW and rcv_pkey_check function should be called instead.
 */
अटल अंतरभूत पूर्णांक ingress_pkey_check(काष्ठा hfi1_pportdata *ppd, u16 pkey,
				     u8 sc5, u8 idx, u32 slid, bool क्रमce)
अणु
	अगर (!(क्रमce) && !(ppd->part_enक्रमce & HFI1_PART_ENFORCE_IN))
		वापस 0;

	/* If SC15, pkey[0:14] must be 0x7fff */
	अगर ((sc5 == 0xf) && ((pkey & PKEY_LOW_15_MASK) != PKEY_LOW_15_MASK))
		जाओ bad;

	/* Is the pkey = 0x0, or 0x8000? */
	अगर ((pkey & PKEY_LOW_15_MASK) == 0)
		जाओ bad;

	/* The most likely matching pkey has index 'idx' */
	अगर (ingress_pkey_matches_entry(pkey, ppd->pkeys[idx]))
		वापस 0;

	/* no match - try the whole table */
	अगर (!ingress_pkey_table_search(ppd, pkey))
		वापस 0;

bad:
	ingress_pkey_table_fail(ppd, pkey, slid);
	वापस 1;
पूर्ण

/*
 * rcv_pkey_check - Return 0 अगर the ingress pkey is valid, वापस 1
 * otherwise. It only ensures pkey is vlid क्रम QP0. This function
 * should be called on the data path instead of ingress_pkey_check
 * as on data path, pkey check is करोne by HW (except क्रम QP0).
 */
अटल अंतरभूत पूर्णांक rcv_pkey_check(काष्ठा hfi1_pportdata *ppd, u16 pkey,
				 u8 sc5, u16 slid)
अणु
	अगर (!(ppd->part_enक्रमce & HFI1_PART_ENFORCE_IN))
		वापस 0;

	/* If SC15, pkey[0:14] must be 0x7fff */
	अगर ((sc5 == 0xf) && ((pkey & PKEY_LOW_15_MASK) != PKEY_LOW_15_MASK))
		जाओ bad;

	वापस 0;
bad:
	ingress_pkey_table_fail(ppd, pkey, slid);
	वापस 1;
पूर्ण

/* MTU handling */

/* MTU क्रमागतeration, 256-4k match IB */
#घोषणा OPA_MTU_0     0
#घोषणा OPA_MTU_256   1
#घोषणा OPA_MTU_512   2
#घोषणा OPA_MTU_1024  3
#घोषणा OPA_MTU_2048  4
#घोषणा OPA_MTU_4096  5

u32 lrh_max_header_bytes(काष्ठा hfi1_devdata *dd);
पूर्णांक mtu_to_क्रमागत(u32 mtu, पूर्णांक शेष_अगर_bad);
u16 क्रमागत_to_mtu(पूर्णांक mtu);
अटल अंतरभूत पूर्णांक valid_ib_mtu(अचिन्हित पूर्णांक mtu)
अणु
	वापस mtu == 256 || mtu == 512 ||
		mtu == 1024 || mtu == 2048 ||
		mtu == 4096;
पूर्ण

अटल अंतरभूत पूर्णांक valid_opa_max_mtu(अचिन्हित पूर्णांक mtu)
अणु
	वापस mtu >= 2048 &&
		(valid_ib_mtu(mtu) || mtu == 8192 || mtu == 10240);
पूर्ण

पूर्णांक set_mtu(काष्ठा hfi1_pportdata *ppd);

पूर्णांक hfi1_set_lid(काष्ठा hfi1_pportdata *ppd, u32 lid, u8 lmc);
व्योम hfi1_disable_after_error(काष्ठा hfi1_devdata *dd);
पूर्णांक hfi1_set_uevent_bits(काष्ठा hfi1_pportdata *ppd, स्थिर पूर्णांक evtbit);
पूर्णांक hfi1_rcvbuf_validate(u32 size, u8 type, u16 *encode);

पूर्णांक fm_get_table(काष्ठा hfi1_pportdata *ppd, पूर्णांक which, व्योम *t);
पूर्णांक fm_set_table(काष्ठा hfi1_pportdata *ppd, पूर्णांक which, व्योम *t);

व्योम set_up_vau(काष्ठा hfi1_devdata *dd, u8 vau);
व्योम set_up_vl15(काष्ठा hfi1_devdata *dd, u16 vl15buf);
व्योम reset_link_credits(काष्ठा hfi1_devdata *dd);
व्योम assign_remote_cm_au_table(काष्ठा hfi1_devdata *dd, u8 vcu);

पूर्णांक set_buffer_control(काष्ठा hfi1_pportdata *ppd, काष्ठा buffer_control *bc);

अटल अंतरभूत काष्ठा hfi1_devdata *dd_from_ppd(काष्ठा hfi1_pportdata *ppd)
अणु
	वापस ppd->dd;
पूर्ण

अटल अंतरभूत काष्ठा hfi1_devdata *dd_from_dev(काष्ठा hfi1_ibdev *dev)
अणु
	वापस container_of(dev, काष्ठा hfi1_devdata, verbs_dev);
पूर्ण

अटल अंतरभूत काष्ठा hfi1_devdata *dd_from_ibdev(काष्ठा ib_device *ibdev)
अणु
	वापस dd_from_dev(to_idev(ibdev));
पूर्ण

अटल अंतरभूत काष्ठा hfi1_pportdata *ppd_from_ibp(काष्ठा hfi1_ibport *ibp)
अणु
	वापस container_of(ibp, काष्ठा hfi1_pportdata, ibport_data);
पूर्ण

अटल अंतरभूत काष्ठा hfi1_ibdev *dev_from_rdi(काष्ठा rvt_dev_info *rdi)
अणु
	वापस container_of(rdi, काष्ठा hfi1_ibdev, rdi);
पूर्ण

अटल अंतरभूत काष्ठा hfi1_ibport *to_iport(काष्ठा ib_device *ibdev, u32 port)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u32 pidx = port - 1; /* IB number port from 1, hdw from 0 */

	WARN_ON(pidx >= dd->num_pports);
	वापस &dd->pport[pidx].ibport_data;
पूर्ण

अटल अंतरभूत काष्ठा hfi1_ibport *rcd_to_iport(काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस &rcd->ppd->ibport_data;
पूर्ण

/**
 * hfi1_may_ecn - Check whether FECN or BECN processing should be करोne
 * @pkt: the packet to be evaluated
 *
 * Check whether the FECN or BECN bits in the packet's header are
 * enabled, depending on packet type.
 *
 * This function only checks क्रम FECN and BECN bits. Additional checks
 * are करोne in the slowpath (hfi1_process_ecn_slowpath()) in order to
 * ensure correct handling.
 */
अटल अंतरभूत bool hfi1_may_ecn(काष्ठा hfi1_packet *pkt)
अणु
	bool fecn, becn;

	अगर (pkt->etype == RHF_RCV_TYPE_BYPASS) अणु
		fecn = hfi1_16B_get_fecn(pkt->hdr);
		becn = hfi1_16B_get_becn(pkt->hdr);
	पूर्ण अन्यथा अणु
		fecn = ib_bth_get_fecn(pkt->ohdr);
		becn = ib_bth_get_becn(pkt->ohdr);
	पूर्ण
	वापस fecn || becn;
पूर्ण

bool hfi1_process_ecn_slowpath(काष्ठा rvt_qp *qp, काष्ठा hfi1_packet *pkt,
			       bool prescan);
अटल अंतरभूत bool process_ecn(काष्ठा rvt_qp *qp, काष्ठा hfi1_packet *pkt)
अणु
	bool करो_work;

	करो_work = hfi1_may_ecn(pkt);
	अगर (unlikely(करो_work))
		वापस hfi1_process_ecn_slowpath(qp, pkt, false);
	वापस false;
पूर्ण

/*
 * Return the indexed PKEY from the port PKEY table.
 */
अटल अंतरभूत u16 hfi1_get_pkey(काष्ठा hfi1_ibport *ibp, अचिन्हित index)
अणु
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u16 ret;

	अगर (index >= ARRAY_SIZE(ppd->pkeys))
		ret = 0;
	अन्यथा
		ret = ppd->pkeys[index];

	वापस ret;
पूर्ण

/*
 * Return the indexed GUID from the port GUIDs table.
 */
अटल अंतरभूत __be64 get_sguid(काष्ठा hfi1_ibport *ibp, अचिन्हित पूर्णांक index)
अणु
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	WARN_ON(index >= HFI1_GUIDS_PER_PORT);
	वापस cpu_to_be64(ppd->guids[index]);
पूर्ण

/*
 * Called by पढ़ोers of cc_state only, must call under rcu_पढ़ो_lock().
 */
अटल अंतरभूत काष्ठा cc_state *get_cc_state(काष्ठा hfi1_pportdata *ppd)
अणु
	वापस rcu_dereference(ppd->cc_state);
पूर्ण

/*
 * Called by ग_लिखोrs of cc_state only,  must call under cc_state_lock.
 */
अटल अंतरभूत
काष्ठा cc_state *get_cc_state_रक्षित(काष्ठा hfi1_pportdata *ppd)
अणु
	वापस rcu_dereference_रक्षित(ppd->cc_state,
					 lockdep_is_held(&ppd->cc_state_lock));
पूर्ण

/*
 * values क्रम dd->flags (_device_ related flags)
 */
#घोषणा HFI1_INITTED           0x1    /* chip and driver up and initted */
#घोषणा HFI1_PRESENT           0x2    /* chip accesses can be करोne */
#घोषणा HFI1_FROZEN            0x4    /* chip in SPC मुक्तze */
#घोषणा HFI1_HAS_SDMA_TIMEOUT  0x8
#घोषणा HFI1_HAS_SEND_DMA      0x10   /* Supports Send DMA */
#घोषणा HFI1_FORCED_FREEZE     0x80   /* driver क्रमced मुक्तze mode */
#घोषणा HFI1_SHUTDOWN          0x100  /* device is shutting करोwn */

/* IB dword length mask in PBC (lower 11 bits); same क्रम all chips */
#घोषणा HFI1_PBC_LENGTH_MASK                     ((1 << 11) - 1)

/* ctxt_flag bit offsets */
		/* base context has not finished initializing */
#घोषणा HFI1_CTXT_BASE_UNINIT 1
		/* base context initaliation failed */
#घोषणा HFI1_CTXT_BASE_FAILED 2
		/* रुकोing क्रम a packet to arrive */
#घोषणा HFI1_CTXT_WAITING_RCV 3
		/* रुकोing क्रम an urgent packet to arrive */
#घोषणा HFI1_CTXT_WAITING_URG 4

/* मुक्त up any allocated data at बंदs */
पूर्णांक hfi1_init_dd(काष्ठा hfi1_devdata *dd);
व्योम hfi1_मुक्त_devdata(काष्ठा hfi1_devdata *dd);

/* LED beaconing functions */
व्योम hfi1_start_led_override(काष्ठा hfi1_pportdata *ppd, अचिन्हित पूर्णांक समयon,
			     अचिन्हित पूर्णांक समयoff);
व्योम shutकरोwn_led_override(काष्ठा hfi1_pportdata *ppd);

#घोषणा HFI1_CREDIT_RETURN_RATE (100)

/*
 * The number of words क्रम the KDETH protocol field.  If this is
 * larger then the actual field used, then part of the payload
 * will be in the header.
 *
 * Optimally, we want this sized so that a typical हाल will
 * use full cache lines.  The typical local KDETH header would
 * be:
 *
 *	Bytes	Field
 *	  8	LRH
 *	 12	BHT
 *	 ??	KDETH
 *	  8	RHF
 *	---
 *	 28 + KDETH
 *
 * For a 64-byte cache line, KDETH would need to be 36 bytes or 9 DWORDS
 */
#घोषणा DEFAULT_RCVHDRSIZE 9

/*
 * Maximal header byte count:
 *
 *	Bytes	Field
 *	  8	LRH
 *	 40	GRH (optional)
 *	 12	BTH
 *	 ??	KDETH
 *	  8	RHF
 *	---
 *	 68 + KDETH
 *
 * We also want to मुख्यtain a cache line alignment to assist DMA'ing
 * of the header bytes.  Round up to a good size.
 */
#घोषणा DEFAULT_RCVHDR_ENTSIZE 32

bool hfi1_can_pin_pages(काष्ठा hfi1_devdata *dd, काष्ठा mm_काष्ठा *mm,
			u32 nlocked, u32 npages);
पूर्णांक hfi1_acquire_user_pages(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr,
			    माप_प्रकार npages, bool writable, काष्ठा page **pages);
व्योम hfi1_release_user_pages(काष्ठा mm_काष्ठा *mm, काष्ठा page **p,
			     माप_प्रकार npages, bool dirty);

/**
 * hfi1_rcvhdrtail_kvaddr - वापस tail kvaddr
 * @rcd - the receive context
 */
अटल अंतरभूत __le64 *hfi1_rcvhdrtail_kvaddr(स्थिर काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस (__le64 *)rcd->rcvhdrtail_kvaddr;
पूर्ण

अटल अंतरभूत व्योम clear_rcvhdrtail(स्थिर काष्ठा hfi1_ctxtdata *rcd)
अणु
	u64 *kv = (u64 *)hfi1_rcvhdrtail_kvaddr(rcd);

	अगर (kv)
		*kv = 0ULL;
पूर्ण

अटल अंतरभूत u32 get_rcvhdrtail(स्थिर काष्ठा hfi1_ctxtdata *rcd)
अणु
	/*
	 * अस्थिर because it's a DMA target from the chip, routine is
	 * अंतरभूतd, and करोn't want रेजिस्टर caching or reordering.
	 */
	वापस (u32)le64_to_cpu(*hfi1_rcvhdrtail_kvaddr(rcd));
पूर्ण

अटल अंतरभूत bool hfi1_packet_present(काष्ठा hfi1_ctxtdata *rcd)
अणु
	अगर (likely(!rcd->rcvhdrtail_kvaddr)) अणु
		u32 seq = rhf_rcv_seq(rhf_to_cpu(get_rhf_addr(rcd)));

		वापस !last_rcv_seq(rcd, seq);
	पूर्ण
	वापस hfi1_rcd_head(rcd) != get_rcvhdrtail(rcd);
पूर्ण

/*
 * sysfs पूर्णांकerface.
 */

बाह्य स्थिर अक्षर ib_hfi1_version[];
बाह्य स्थिर काष्ठा attribute_group ib_hfi1_attr_group;

पूर्णांक hfi1_device_create(काष्ठा hfi1_devdata *dd);
व्योम hfi1_device_हटाओ(काष्ठा hfi1_devdata *dd);

पूर्णांक hfi1_create_port_files(काष्ठा ib_device *ibdev, u32 port_num,
			   काष्ठा kobject *kobj);
पूर्णांक hfi1_verbs_रेजिस्टर_sysfs(काष्ठा hfi1_devdata *dd);
व्योम hfi1_verbs_unरेजिस्टर_sysfs(काष्ठा hfi1_devdata *dd);
/* Hook क्रम sysfs पढ़ो of QSFP */
पूर्णांक qsfp_dump(काष्ठा hfi1_pportdata *ppd, अक्षर *buf, पूर्णांक len);

पूर्णांक hfi1_pcie_init(काष्ठा hfi1_devdata *dd);
व्योम hfi1_pcie_cleanup(काष्ठा pci_dev *pdev);
पूर्णांक hfi1_pcie_ddinit(काष्ठा hfi1_devdata *dd, काष्ठा pci_dev *pdev);
व्योम hfi1_pcie_ddcleanup(काष्ठा hfi1_devdata *);
पूर्णांक pcie_speeds(काष्ठा hfi1_devdata *dd);
पूर्णांक restore_pci_variables(काष्ठा hfi1_devdata *dd);
पूर्णांक save_pci_variables(काष्ठा hfi1_devdata *dd);
पूर्णांक करो_pcie_gen3_transition(काष्ठा hfi1_devdata *dd);
व्योम tune_pcie_caps(काष्ठा hfi1_devdata *dd);
पूर्णांक parse_platक्रमm_config(काष्ठा hfi1_devdata *dd);
पूर्णांक get_platक्रमm_config_field(काष्ठा hfi1_devdata *dd,
			      क्रमागत platक्रमm_config_table_type_encoding
			      table_type, पूर्णांक table_index, पूर्णांक field_index,
			      u32 *data, u32 len);

काष्ठा pci_dev *get_pci_dev(काष्ठा rvt_dev_info *rdi);

/*
 * Flush ग_लिखो combining store buffers (अगर present) and perक्रमm a ग_लिखो
 * barrier.
 */
अटल अंतरभूत व्योम flush_wc(व्योम)
अणु
	यंत्र अस्थिर("sfence" : : : "memory");
पूर्ण

व्योम handle_eflags(काष्ठा hfi1_packet *packet);
व्योम seqfile_dump_rcd(काष्ठा seq_file *s, काष्ठा hfi1_ctxtdata *rcd);

/* global module parameter variables */
बाह्य अचिन्हित पूर्णांक hfi1_max_mtu;
बाह्य अचिन्हित पूर्णांक hfi1_cu;
बाह्य अचिन्हित पूर्णांक user_credit_वापस_threshold;
बाह्य पूर्णांक num_user_contexts;
बाह्य अचिन्हित दीर्घ n_krcvqs;
बाह्य uपूर्णांक krcvqs[];
बाह्य पूर्णांक krcvqsset;
बाह्य uपूर्णांक loopback;
बाह्य uपूर्णांक quick_linkup;
बाह्य uपूर्णांक rcv_पूर्णांकr_समयout;
बाह्य uपूर्णांक rcv_पूर्णांकr_count;
बाह्य uपूर्णांक rcv_पूर्णांकr_dynamic;
बाह्य uलघु link_crc_mask;

बाह्य काष्ठा mutex hfi1_mutex;

/* Number of seconds beक्रमe our card status check...  */
#घोषणा STATUS_TIMEOUT 60

#घोषणा DRIVER_NAME		"hfi1"
#घोषणा HFI1_USER_MINOR_BASE     0
#घोषणा HFI1_TRACE_MINOR         127
#घोषणा HFI1_NMINORS             255

#घोषणा PCI_VENDOR_ID_INTEL 0x8086
#घोषणा PCI_DEVICE_ID_INTEL0 0x24f0
#घोषणा PCI_DEVICE_ID_INTEL1 0x24f1

#घोषणा HFI1_PKT_USER_SC_INTEGRITY					    \
	(SEND_CTXT_CHECK_ENABLE_DISALLOW_NON_KDETH_PACKETS_SMASK	    \
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_KDETH_PACKETS_SMASK		\
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_BYPASS_SMASK		    \
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_GRH_SMASK)

#घोषणा HFI1_PKT_KERNEL_SC_INTEGRITY					    \
	(SEND_CTXT_CHECK_ENABLE_DISALLOW_KDETH_PACKETS_SMASK)

अटल अंतरभूत u64 hfi1_pkt_शेष_send_ctxt_mask(काष्ठा hfi1_devdata *dd,
						  u16 ctxt_type)
अणु
	u64 base_sc_पूर्णांकegrity;

	/* No पूर्णांकegrity checks अगर HFI1_CAP_NO_INTEGRITY is set */
	अगर (HFI1_CAP_IS_KSET(NO_INTEGRITY))
		वापस 0;

	base_sc_पूर्णांकegrity =
	SEND_CTXT_CHECK_ENABLE_DISALLOW_BYPASS_BAD_PKT_LEN_SMASK
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_PBC_STATIC_RATE_CONTROL_SMASK
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_TOO_LONG_BYPASS_PACKETS_SMASK
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_TOO_LONG_IB_PACKETS_SMASK
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_BAD_PKT_LEN_SMASK
#अगर_अघोषित CONFIG_FAULT_INJECTION
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_PBC_TEST_SMASK
#पूर्ण_अगर
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_TOO_SMALL_BYPASS_PACKETS_SMASK
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_TOO_SMALL_IB_PACKETS_SMASK
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_RAW_IPV6_SMASK
	| SEND_CTXT_CHECK_ENABLE_DISALLOW_RAW_SMASK
	| SEND_CTXT_CHECK_ENABLE_CHECK_BYPASS_VL_MAPPING_SMASK
	| SEND_CTXT_CHECK_ENABLE_CHECK_VL_MAPPING_SMASK
	| SEND_CTXT_CHECK_ENABLE_CHECK_OPCODE_SMASK
	| SEND_CTXT_CHECK_ENABLE_CHECK_SLID_SMASK
	| SEND_CTXT_CHECK_ENABLE_CHECK_VL_SMASK
	| SEND_CTXT_CHECK_ENABLE_CHECK_ENABLE_SMASK;

	अगर (ctxt_type == SC_USER)
		base_sc_पूर्णांकegrity |=
#अगर_अघोषित CONFIG_FAULT_INJECTION
			SEND_CTXT_CHECK_ENABLE_DISALLOW_PBC_TEST_SMASK |
#पूर्ण_अगर
			HFI1_PKT_USER_SC_INTEGRITY;
	अन्यथा अगर (ctxt_type != SC_KERNEL)
		base_sc_पूर्णांकegrity |= HFI1_PKT_KERNEL_SC_INTEGRITY;

	/* turn on send-side job key checks अगर !A0 */
	अगर (!is_ax(dd))
		base_sc_पूर्णांकegrity |= SEND_CTXT_CHECK_ENABLE_CHECK_JOB_KEY_SMASK;

	वापस base_sc_पूर्णांकegrity;
पूर्ण

अटल अंतरभूत u64 hfi1_pkt_base_sdma_पूर्णांकegrity(काष्ठा hfi1_devdata *dd)
अणु
	u64 base_sdma_पूर्णांकegrity;

	/* No पूर्णांकegrity checks अगर HFI1_CAP_NO_INTEGRITY is set */
	अगर (HFI1_CAP_IS_KSET(NO_INTEGRITY))
		वापस 0;

	base_sdma_पूर्णांकegrity =
	SEND_DMA_CHECK_ENABLE_DISALLOW_BYPASS_BAD_PKT_LEN_SMASK
	| SEND_DMA_CHECK_ENABLE_DISALLOW_TOO_LONG_BYPASS_PACKETS_SMASK
	| SEND_DMA_CHECK_ENABLE_DISALLOW_TOO_LONG_IB_PACKETS_SMASK
	| SEND_DMA_CHECK_ENABLE_DISALLOW_BAD_PKT_LEN_SMASK
	| SEND_DMA_CHECK_ENABLE_DISALLOW_TOO_SMALL_BYPASS_PACKETS_SMASK
	| SEND_DMA_CHECK_ENABLE_DISALLOW_TOO_SMALL_IB_PACKETS_SMASK
	| SEND_DMA_CHECK_ENABLE_DISALLOW_RAW_IPV6_SMASK
	| SEND_DMA_CHECK_ENABLE_DISALLOW_RAW_SMASK
	| SEND_DMA_CHECK_ENABLE_CHECK_BYPASS_VL_MAPPING_SMASK
	| SEND_DMA_CHECK_ENABLE_CHECK_VL_MAPPING_SMASK
	| SEND_DMA_CHECK_ENABLE_CHECK_OPCODE_SMASK
	| SEND_DMA_CHECK_ENABLE_CHECK_SLID_SMASK
	| SEND_DMA_CHECK_ENABLE_CHECK_VL_SMASK
	| SEND_DMA_CHECK_ENABLE_CHECK_ENABLE_SMASK;

	अगर (!HFI1_CAP_IS_KSET(STATIC_RATE_CTRL))
		base_sdma_पूर्णांकegrity |=
		SEND_DMA_CHECK_ENABLE_DISALLOW_PBC_STATIC_RATE_CONTROL_SMASK;

	/* turn on send-side job key checks अगर !A0 */
	अगर (!is_ax(dd))
		base_sdma_पूर्णांकegrity |=
			SEND_DMA_CHECK_ENABLE_CHECK_JOB_KEY_SMASK;

	वापस base_sdma_पूर्णांकegrity;
पूर्ण

#घोषणा dd_dev_emerg(dd, fmt, ...) \
	dev_emerg(&(dd)->pcidev->dev, "%s: " fmt, \
		  rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), ##__VA_ARGS__)

#घोषणा dd_dev_err(dd, fmt, ...) \
	dev_err(&(dd)->pcidev->dev, "%s: " fmt, \
		rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), ##__VA_ARGS__)

#घोषणा dd_dev_err_ratelimited(dd, fmt, ...) \
	dev_err_ratelimited(&(dd)->pcidev->dev, "%s: " fmt, \
			    rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), \
			    ##__VA_ARGS__)

#घोषणा dd_dev_warn(dd, fmt, ...) \
	dev_warn(&(dd)->pcidev->dev, "%s: " fmt, \
		 rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), ##__VA_ARGS__)

#घोषणा dd_dev_warn_ratelimited(dd, fmt, ...) \
	dev_warn_ratelimited(&(dd)->pcidev->dev, "%s: " fmt, \
			     rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), \
			     ##__VA_ARGS__)

#घोषणा dd_dev_info(dd, fmt, ...) \
	dev_info(&(dd)->pcidev->dev, "%s: " fmt, \
		 rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), ##__VA_ARGS__)

#घोषणा dd_dev_info_ratelimited(dd, fmt, ...) \
	dev_info_ratelimited(&(dd)->pcidev->dev, "%s: " fmt, \
			     rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), \
			     ##__VA_ARGS__)

#घोषणा dd_dev_dbg(dd, fmt, ...) \
	dev_dbg(&(dd)->pcidev->dev, "%s: " fmt, \
		rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), ##__VA_ARGS__)

#घोषणा hfi1_dev_porterr(dd, port, fmt, ...) \
	dev_err(&(dd)->pcidev->dev, "%s: port %u: " fmt, \
		rvt_get_ibdev_name(&(dd)->verbs_dev.rdi), (port), ##__VA_ARGS__)

/*
 * this is used क्रम क्रमmatting hw error messages...
 */
काष्ठा hfi1_hwerror_msgs अणु
	u64 mask;
	स्थिर अक्षर *msg;
	माप_प्रकार sz;
पूर्ण;

/* in पूर्णांकr.c... */
व्योम hfi1_क्रमmat_hwerrors(u64 hwerrs,
			  स्थिर काष्ठा hfi1_hwerror_msgs *hwerrmsgs,
			  माप_प्रकार nhwerrmsgs, अक्षर *msg, माप_प्रकार lmsg);

#घोषणा USER_OPCODE_CHECK_VAL 0xC0
#घोषणा USER_OPCODE_CHECK_MASK 0xC0
#घोषणा OPCODE_CHECK_VAL_DISABLED 0x0
#घोषणा OPCODE_CHECK_MASK_DISABLED 0x0

अटल अंतरभूत व्योम hfi1_reset_cpu_counters(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_pportdata *ppd;
	पूर्णांक i;

	dd->z_पूर्णांक_counter = get_all_cpu_total(dd->पूर्णांक_counter);
	dd->z_rcv_limit = get_all_cpu_total(dd->rcv_limit);
	dd->z_send_schedule = get_all_cpu_total(dd->send_schedule);

	ppd = (काष्ठा hfi1_pportdata *)(dd + 1);
	क्रम (i = 0; i < dd->num_pports; i++, ppd++) अणु
		ppd->ibport_data.rvp.z_rc_acks =
			get_all_cpu_total(ppd->ibport_data.rvp.rc_acks);
		ppd->ibport_data.rvp.z_rc_qacks =
			get_all_cpu_total(ppd->ibport_data.rvp.rc_qacks);
	पूर्ण
पूर्ण

/* Control LED state */
अटल अंतरभूत व्योम setextled(काष्ठा hfi1_devdata *dd, u32 on)
अणु
	अगर (on)
		ग_लिखो_csr(dd, DCC_CFG_LED_CNTRL, 0x1F);
	अन्यथा
		ग_लिखो_csr(dd, DCC_CFG_LED_CNTRL, 0x10);
पूर्ण

/* वापस the i2c resource given the target */
अटल अंतरभूत u32 i2c_target(u32 target)
अणु
	वापस target ? CR_I2C2 : CR_I2C1;
पूर्ण

/* वापस the i2c chain chip resource that this HFI uses क्रम QSFP */
अटल अंतरभूत u32 qsfp_resource(काष्ठा hfi1_devdata *dd)
अणु
	वापस i2c_target(dd->hfi1_id);
पूर्ण

/* Is this device पूर्णांकegrated or discrete? */
अटल अंतरभूत bool is_पूर्णांकegrated(काष्ठा hfi1_devdata *dd)
अणु
	वापस dd->pcidev->device == PCI_DEVICE_ID_INTEL1;
पूर्ण

/**
 * hfi1_need_drop - detect need क्रम drop
 * @dd: - the device
 *
 * In some हालs, the first packet needs to be dropped.
 *
 * Return true is the current packet needs to be dropped and false otherwise.
 */
अटल अंतरभूत bool hfi1_need_drop(काष्ठा hfi1_devdata *dd)
अणु
	अगर (unlikely(dd->करो_drop &&
		     atomic_xchg(&dd->drop_packet, DROP_PACKET_OFF) ==
		     DROP_PACKET_ON)) अणु
		dd->करो_drop = false;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक hfi1_tempsense_rd(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_temp *temp);

#घोषणा DD_DEV_ENTRY(dd)       __string(dev, dev_name(&(dd)->pcidev->dev))
#घोषणा DD_DEV_ASSIGN(dd)      __assign_str(dev, dev_name(&(dd)->pcidev->dev))

अटल अंतरभूत व्योम hfi1_update_ah_attr(काष्ठा ib_device *ibdev,
				       काष्ठा rdma_ah_attr *attr)
अणु
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_ibport *ibp;
	u32 dlid = rdma_ah_get_dlid(attr);

	/*
	 * Kernel clients may not have setup GRH inक्रमmation
	 * Set that here.
	 */
	ibp = to_iport(ibdev, rdma_ah_get_port_num(attr));
	ppd = ppd_from_ibp(ibp);
	अगर ((((dlid >= be16_to_cpu(IB_MULTICAST_LID_BASE)) ||
	      (ppd->lid >= be16_to_cpu(IB_MULTICAST_LID_BASE))) &&
	    (dlid != be32_to_cpu(OPA_LID_PERMISSIVE)) &&
	    (dlid != be16_to_cpu(IB_LID_PERMISSIVE)) &&
	    (!(rdma_ah_get_ah_flags(attr) & IB_AH_GRH))) ||
	    (rdma_ah_get_make_grd(attr))) अणु
		rdma_ah_set_ah_flags(attr, IB_AH_GRH);
		rdma_ah_set_पूर्णांकerface_id(attr, OPA_MAKE_ID(dlid));
		rdma_ah_set_subnet_prefix(attr, ibp->rvp.gid_prefix);
	पूर्ण
पूर्ण

/*
 * hfi1_check_mcast- Check अगर the given lid is
 * in the OPA multicast range.
 *
 * The LID might either reside in ah.dlid or might be
 * in the GRH of the address handle as DGID अगर extended
 * addresses are in use.
 */
अटल अंतरभूत bool hfi1_check_mcast(u32 lid)
अणु
	वापस ((lid >= opa_get_mcast_base(OPA_MCAST_NR)) &&
		(lid != be32_to_cpu(OPA_LID_PERMISSIVE)));
पूर्ण

#घोषणा opa_get_lid(lid, क्रमmat)	\
	__opa_get_lid(lid, OPA_PORT_PACKET_FORMAT_##क्रमmat)

/* Convert a lid to a specअगरic lid space */
अटल अंतरभूत u32 __opa_get_lid(u32 lid, u8 क्रमmat)
अणु
	bool is_mcast = hfi1_check_mcast(lid);

	चयन (क्रमmat) अणु
	हाल OPA_PORT_PACKET_FORMAT_8B:
	हाल OPA_PORT_PACKET_FORMAT_10B:
		अगर (is_mcast)
			वापस (lid - opa_get_mcast_base(OPA_MCAST_NR) +
				0xF0000);
		वापस lid & 0xFFFFF;
	हाल OPA_PORT_PACKET_FORMAT_16B:
		अगर (is_mcast)
			वापस (lid - opa_get_mcast_base(OPA_MCAST_NR) +
				0xF00000);
		वापस lid & 0xFFFFFF;
	हाल OPA_PORT_PACKET_FORMAT_9B:
		अगर (is_mcast)
			वापस (lid -
				opa_get_mcast_base(OPA_MCAST_NR) +
				be16_to_cpu(IB_MULTICAST_LID_BASE));
		अन्यथा
			वापस lid & 0xFFFF;
	शेष:
		वापस lid;
	पूर्ण
पूर्ण

/* Return true अगर the given lid is the OPA 16B multicast range */
अटल अंतरभूत bool hfi1_is_16B_mcast(u32 lid)
अणु
	वापस ((lid >=
		opa_get_lid(opa_get_mcast_base(OPA_MCAST_NR), 16B)) &&
		(lid != opa_get_lid(be32_to_cpu(OPA_LID_PERMISSIVE), 16B)));
पूर्ण

अटल अंतरभूत व्योम hfi1_make_opa_lid(काष्ठा rdma_ah_attr *attr)
अणु
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(attr);
	u32 dlid = rdma_ah_get_dlid(attr);

	/* Modअगरy ah_attr.dlid to be in the 32 bit LID space.
	 * This is how the address will be laid out:
	 * Assuming MCAST_NR to be 4,
	 * 32 bit permissive LID = 0xFFFFFFFF
	 * Multicast LID range = 0xFFFFFFFE to 0xF0000000
	 * Unicast LID range = 0xEFFFFFFF to 1
	 * Invalid LID = 0
	 */
	अगर (ib_is_opa_gid(&grh->dgid))
		dlid = opa_get_lid_from_gid(&grh->dgid);
	अन्यथा अगर ((dlid >= be16_to_cpu(IB_MULTICAST_LID_BASE)) &&
		 (dlid != be16_to_cpu(IB_LID_PERMISSIVE)) &&
		 (dlid != be32_to_cpu(OPA_LID_PERMISSIVE)))
		dlid = dlid - be16_to_cpu(IB_MULTICAST_LID_BASE) +
			opa_get_mcast_base(OPA_MCAST_NR);
	अन्यथा अगर (dlid == be16_to_cpu(IB_LID_PERMISSIVE))
		dlid = be32_to_cpu(OPA_LID_PERMISSIVE);

	rdma_ah_set_dlid(attr, dlid);
पूर्ण

अटल अंतरभूत u8 hfi1_get_packet_type(u32 lid)
अणु
	/* 9B अगर lid > 0xF0000000 */
	अगर (lid >= opa_get_mcast_base(OPA_MCAST_NR))
		वापस HFI1_PKT_TYPE_9B;

	/* 16B अगर lid > 0xC000 */
	अगर (lid >= opa_get_lid(opa_get_mcast_base(OPA_MCAST_NR), 9B))
		वापस HFI1_PKT_TYPE_16B;

	वापस HFI1_PKT_TYPE_9B;
पूर्ण

अटल अंतरभूत bool hfi1_get_hdr_type(u32 lid, काष्ठा rdma_ah_attr *attr)
अणु
	/*
	 * If there was an incoming 16B packet with permissive
	 * LIDs, OPA GIDs would have been programmed when those
	 * packets were received. A 16B packet will have to
	 * be sent in response to that packet. Return a 16B
	 * header type अगर that's the हाल.
	 */
	अगर (rdma_ah_get_dlid(attr) == be32_to_cpu(OPA_LID_PERMISSIVE))
		वापस (ib_is_opa_gid(&rdma_ah_पढ़ो_grh(attr)->dgid)) ?
			HFI1_PKT_TYPE_16B : HFI1_PKT_TYPE_9B;

	/*
	 * Return a 16B header type अगर either the the destination
	 * or source lid is extended.
	 */
	अगर (hfi1_get_packet_type(rdma_ah_get_dlid(attr)) == HFI1_PKT_TYPE_16B)
		वापस HFI1_PKT_TYPE_16B;

	वापस hfi1_get_packet_type(lid);
पूर्ण

अटल अंतरभूत व्योम hfi1_make_ext_grh(काष्ठा hfi1_packet *packet,
				     काष्ठा ib_grh *grh, u32 slid,
				     u32 dlid)
अणु
	काष्ठा hfi1_ibport *ibp = &packet->rcd->ppd->ibport_data;
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	अगर (!ibp)
		वापस;

	grh->hop_limit = 1;
	grh->sgid.global.subnet_prefix = ibp->rvp.gid_prefix;
	अगर (slid == opa_get_lid(be32_to_cpu(OPA_LID_PERMISSIVE), 16B))
		grh->sgid.global.पूर्णांकerface_id =
			OPA_MAKE_ID(be32_to_cpu(OPA_LID_PERMISSIVE));
	अन्यथा
		grh->sgid.global.पूर्णांकerface_id = OPA_MAKE_ID(slid);

	/*
	 * Upper layers (like mad) may compare the dgid in the
	 * wc that is obtained here with the sgid_index in
	 * the wr. Since sgid_index in wr is always 0 क्रम
	 * extended lids, set the dgid here to the शेष
	 * IB gid.
	 */
	grh->dgid.global.subnet_prefix = ibp->rvp.gid_prefix;
	grh->dgid.global.पूर्णांकerface_id =
		cpu_to_be64(ppd->guids[HFI1_PORT_GUID_INDEX]);
पूर्ण

अटल अंतरभूत पूर्णांक hfi1_get_16b_padding(u32 hdr_size, u32 payload)
अणु
	वापस -(hdr_size + payload + (SIZE_OF_CRC << 2) +
		     SIZE_OF_LT) & 0x7;
पूर्ण

अटल अंतरभूत व्योम hfi1_make_ib_hdr(काष्ठा ib_header *hdr,
				    u16 lrh0, u16 len,
				    u16 dlid, u16 slid)
अणु
	hdr->lrh[0] = cpu_to_be16(lrh0);
	hdr->lrh[1] = cpu_to_be16(dlid);
	hdr->lrh[2] = cpu_to_be16(len);
	hdr->lrh[3] = cpu_to_be16(slid);
पूर्ण

अटल अंतरभूत व्योम hfi1_make_16b_hdr(काष्ठा hfi1_16b_header *hdr,
				     u32 slid, u32 dlid,
				     u16 len, u16 pkey,
				     bool becn, bool fecn, u8 l4,
				     u8 sc)
अणु
	u32 lrh0 = 0;
	u32 lrh1 = 0x40000000;
	u32 lrh2 = 0;
	u32 lrh3 = 0;

	lrh0 = (lrh0 & ~OPA_16B_BECN_MASK) | (becn << OPA_16B_BECN_SHIFT);
	lrh0 = (lrh0 & ~OPA_16B_LEN_MASK) | (len << OPA_16B_LEN_SHIFT);
	lrh0 = (lrh0 & ~OPA_16B_LID_MASK)  | (slid & OPA_16B_LID_MASK);
	lrh1 = (lrh1 & ~OPA_16B_FECN_MASK) | (fecn << OPA_16B_FECN_SHIFT);
	lrh1 = (lrh1 & ~OPA_16B_SC_MASK) | (sc << OPA_16B_SC_SHIFT);
	lrh1 = (lrh1 & ~OPA_16B_LID_MASK) | (dlid & OPA_16B_LID_MASK);
	lrh2 = (lrh2 & ~OPA_16B_SLID_MASK) |
		((slid >> OPA_16B_SLID_SHIFT) << OPA_16B_SLID_HIGH_SHIFT);
	lrh2 = (lrh2 & ~OPA_16B_DLID_MASK) |
		((dlid >> OPA_16B_DLID_SHIFT) << OPA_16B_DLID_HIGH_SHIFT);
	lrh2 = (lrh2 & ~OPA_16B_PKEY_MASK) | ((u32)pkey << OPA_16B_PKEY_SHIFT);
	lrh2 = (lrh2 & ~OPA_16B_L4_MASK) | l4;

	hdr->lrh[0] = lrh0;
	hdr->lrh[1] = lrh1;
	hdr->lrh[2] = lrh2;
	hdr->lrh[3] = lrh3;
पूर्ण
#पूर्ण_अगर                          /* _HFI1_KERNEL_H */
