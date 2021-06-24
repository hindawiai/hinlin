<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Broadcom
 */

/*
 * Broadcom PDC Mailbox Driver
 * The PDC provides a ring based programming पूर्णांकerface to one or more hardware
 * offload engines. For example, the PDC driver works with both SPU-M and SPU2
 * cryptographic offload hardware. In some chips the PDC is referred to as MDE,
 * and in others the FA2/FA+ hardware is used with this PDC driver.
 *
 * The PDC driver रेजिस्टरs with the Linux mailbox framework as a mailbox
 * controller, once क्रम each PDC instance. Ring 0 क्रम each PDC is रेजिस्टरed as
 * a mailbox channel. The PDC driver uses पूर्णांकerrupts to determine when data
 * transfers to and from an offload engine are complete. The PDC driver uses
 * thपढ़ोed IRQs so that response messages are handled outside of पूर्णांकerrupt
 * context.
 *
 * The PDC driver allows multiple messages to be pending in the descriptor
 * rings. The tx_msg_start descriptor index indicates where the last message
 * starts. The txin_numd value at this index indicates how many descriptor
 * indexes make up the message. Similar state is kept on the receive side. When
 * an rx पूर्णांकerrupt indicates a response is पढ़ोy, the PDC driver processes numd
 * descriptors from the tx and rx ring, thus processing one response at a समय.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/mailbox/brcm-message.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>

#घोषणा PDC_SUCCESS  0

#घोषणा RING_ENTRY_SIZE   माप(काष्ठा dma64dd)

/* # entries in PDC dma ring */
#घोषणा PDC_RING_ENTRIES  512
/*
 * Minimum number of ring descriptor entries that must be मुक्त to tell mailbox
 * framework that it can submit another request
 */
#घोषणा PDC_RING_SPACE_MIN  15

#घोषणा PDC_RING_SIZE    (PDC_RING_ENTRIES * RING_ENTRY_SIZE)
/* Rings are 8k aligned */
#घोषणा RING_ALIGN_ORDER  13
#घोषणा RING_ALIGN        BIT(RING_ALIGN_ORDER)

#घोषणा RX_BUF_ALIGN_ORDER  5
#घोषणा RX_BUF_ALIGN	    BIT(RX_BUF_ALIGN_ORDER)

/* descriptor bumping macros */
#घोषणा XXD(x, max_mask)              ((x) & (max_mask))
#घोषणा TXD(x, max_mask)              XXD((x), (max_mask))
#घोषणा RXD(x, max_mask)              XXD((x), (max_mask))
#घोषणा NEXTTXD(i, max_mask)          TXD((i) + 1, (max_mask))
#घोषणा PREVTXD(i, max_mask)          TXD((i) - 1, (max_mask))
#घोषणा NEXTRXD(i, max_mask)          RXD((i) + 1, (max_mask))
#घोषणा PREVRXD(i, max_mask)          RXD((i) - 1, (max_mask))
#घोषणा NTXDACTIVE(h, t, max_mask)    TXD((t) - (h), (max_mask))
#घोषणा NRXDACTIVE(h, t, max_mask)    RXD((t) - (h), (max_mask))

/* Length of BCM header at start of SPU msg, in bytes */
#घोषणा BCM_HDR_LEN  8

/*
 * PDC driver reserves ringset 0 on each SPU क्रम its own use. The driver करोes
 * not currently support use of multiple ringsets on a single PDC engine.
 */
#घोषणा PDC_RINGSET  0

/*
 * Interrupt mask and status definitions. Enable पूर्णांकerrupts क्रम tx and rx on
 * ring 0
 */
#घोषणा PDC_RCVINT_0         (16 + PDC_RINGSET)
#घोषणा PDC_RCVINTEN_0       BIT(PDC_RCVINT_0)
#घोषणा PDC_INTMASK	     (PDC_RCVINTEN_0)
#घोषणा PDC_LAZY_FRAMECOUNT  1
#घोषणा PDC_LAZY_TIMEOUT     10000
#घोषणा PDC_LAZY_INT  (PDC_LAZY_TIMEOUT | (PDC_LAZY_FRAMECOUNT << 24))
#घोषणा PDC_INTMASK_OFFSET   0x24
#घोषणा PDC_INTSTATUS_OFFSET 0x20
#घोषणा PDC_RCVLAZY0_OFFSET  (0x30 + 4 * PDC_RINGSET)
#घोषणा FA_RCVLAZY0_OFFSET   0x100

/*
 * For SPU2, configure MDE_CKSUM_CONTROL to ग_लिखो 17 bytes of metadata
 * beक्रमe frame
 */
#घोषणा PDC_SPU2_RESP_HDR_LEN  17
#घोषणा PDC_CKSUM_CTRL         BIT(27)
#घोषणा PDC_CKSUM_CTRL_OFFSET  0x400

#घोषणा PDC_SPUM_RESP_HDR_LEN  32

/*
 * Sets the following bits क्रम ग_लिखो to transmit control reg:
 * 11    - PtyChkDisable - parity check is disabled
 * 20:18 - BurstLen = 3 -> 2^7 = 128 byte data पढ़ोs from memory
 */
#घोषणा PDC_TX_CTL		0x000C0800

/* Bit in tx control reg to enable tx channel */
#घोषणा PDC_TX_ENABLE		0x1

/*
 * Sets the following bits क्रम ग_लिखो to receive control reg:
 * 7:1   - RcvOffset - size in bytes of status region at start of rx frame buf
 * 9     - SepRxHdrDescEn - place start of new frames only in descriptors
 *                          that have StartOfFrame set
 * 10    - OflowContinue - on rx FIFO overflow, clear rx fअगरo, discard all
 *                         reमुख्यing bytes in current frame, report error
 *                         in rx frame status क्रम current frame
 * 11    - PtyChkDisable - parity check is disabled
 * 20:18 - BurstLen = 3 -> 2^7 = 128 byte data पढ़ोs from memory
 */
#घोषणा PDC_RX_CTL		0x000C0E00

/* Bit in rx control reg to enable rx channel */
#घोषणा PDC_RX_ENABLE		0x1

#घोषणा CRYPTO_D64_RS0_CD_MASK   ((PDC_RING_ENTRIES * RING_ENTRY_SIZE) - 1)

/* descriptor flags */
#घोषणा D64_CTRL1_EOT   BIT(28)	/* end of descriptor table */
#घोषणा D64_CTRL1_IOC   BIT(29)	/* पूर्णांकerrupt on complete */
#घोषणा D64_CTRL1_खातापूर्ण   BIT(30)	/* end of frame */
#घोषणा D64_CTRL1_SOF   BIT(31)	/* start of frame */

#घोषणा RX_STATUS_OVERFLOW       0x00800000
#घोषणा RX_STATUS_LEN            0x0000FFFF

#घोषणा PDC_TXREGS_OFFSET  0x200
#घोषणा PDC_RXREGS_OFFSET  0x220

/* Maximum size buffer the DMA engine can handle */
#घोषणा PDC_DMA_BUF_MAX 16384

क्रमागत pdc_hw अणु
	FA_HW,		/* FA2/FA+ hardware (i.e. Northstar Plus) */
	PDC_HW		/* PDC/MDE hardware (i.e. Northstar 2, Pegasus) */
पूर्ण;

काष्ठा pdc_dma_map अणु
	व्योम *ctx;          /* opaque context associated with frame */
पूर्ण;

/* dma descriptor */
काष्ठा dma64dd अणु
	u32 ctrl1;      /* misc control bits */
	u32 ctrl2;      /* buffer count and address extension */
	u32 addrlow;    /* memory address of the date buffer, bits 31:0 */
	u32 addrhigh;   /* memory address of the date buffer, bits 63:32 */
पूर्ण;

/* dma रेजिस्टरs per channel(xmt or rcv) */
काष्ठा dma64_regs अणु
	u32  control;   /* enable, et al */
	u32  ptr;       /* last descriptor posted to chip */
	u32  addrlow;   /* descriptor ring base address low 32-bits */
	u32  addrhigh;  /* descriptor ring base address bits 63:32 */
	u32  status0;   /* last rx descriptor written by hw */
	u32  status1;   /* driver करोes not use */
पूर्ण;

/* cpp contortions to concatenate w/arg prescan */
#अगर_अघोषित PAD
#घोषणा _PADLINE(line)  pad ## line
#घोषणा _XSTR(line)     _PADLINE(line)
#घोषणा PAD             _XSTR(__LINE__)
#पूर्ण_अगर  /* PAD */

/* dma रेजिस्टरs. matches hw layout. */
काष्ठा dma64 अणु
	काष्ठा dma64_regs dmaxmt;  /* dma tx */
	u32          PAD[2];
	काष्ठा dma64_regs dmarcv;  /* dma rx */
	u32          PAD[2];
पूर्ण;

/* PDC रेजिस्टरs */
काष्ठा pdc_regs अणु
	u32  devcontrol;             /* 0x000 */
	u32  devstatus;              /* 0x004 */
	u32  PAD;
	u32  biststatus;             /* 0x00c */
	u32  PAD[4];
	u32  पूर्णांकstatus;              /* 0x020 */
	u32  पूर्णांकmask;                /* 0x024 */
	u32  gpसमयr;                /* 0x028 */

	u32  PAD;
	u32  पूर्णांकrcvlazy_0;           /* 0x030 (Only in PDC, not FA2) */
	u32  पूर्णांकrcvlazy_1;           /* 0x034 (Only in PDC, not FA2) */
	u32  पूर्णांकrcvlazy_2;           /* 0x038 (Only in PDC, not FA2) */
	u32  पूर्णांकrcvlazy_3;           /* 0x03c (Only in PDC, not FA2) */

	u32  PAD[48];
	u32  fa_पूर्णांकrecvlazy;         /* 0x100 (Only in FA2, not PDC) */
	u32  flowctlthresh;          /* 0x104 */
	u32  wrrthresh;              /* 0x108 */
	u32  gmac_idle_cnt_thresh;   /* 0x10c */

	u32  PAD[4];
	u32  अगरioaccessaddr;         /* 0x120 */
	u32  अगरioaccessbyte;         /* 0x124 */
	u32  अगरioaccessdata;         /* 0x128 */

	u32  PAD[21];
	u32  phyaccess;              /* 0x180 */
	u32  PAD;
	u32  phycontrol;             /* 0x188 */
	u32  txqctl;                 /* 0x18c */
	u32  rxqctl;                 /* 0x190 */
	u32  gpioselect;             /* 0x194 */
	u32  gpio_output_en;         /* 0x198 */
	u32  PAD;                    /* 0x19c */
	u32  txq_rxq_mem_ctl;        /* 0x1a0 */
	u32  memory_ecc_status;      /* 0x1a4 */
	u32  serdes_ctl;             /* 0x1a8 */
	u32  serdes_status0;         /* 0x1ac */
	u32  serdes_status1;         /* 0x1b0 */
	u32  PAD[11];                /* 0x1b4-1dc */
	u32  clk_ctl_st;             /* 0x1e0 */
	u32  hw_war;                 /* 0x1e4 (Only in PDC, not FA2) */
	u32  pwrctl;                 /* 0x1e8 */
	u32  PAD[5];

#घोषणा PDC_NUM_DMA_RINGS   4
	काष्ठा dma64 dmaregs[PDC_NUM_DMA_RINGS];  /* 0x0200 - 0x2fc */

	/* more रेजिस्टरs follow, but we करोn't use them */
पूर्ण;

/* काष्ठाure क्रम allocating/मुक्तing DMA rings */
काष्ठा pdc_ring_alloc अणु
	dma_addr_t  dmabase; /* DMA address of start of ring */
	व्योम	   *vbase;   /* base kernel भव address of ring */
	u32	    size;    /* ring allocation size in bytes */
पूर्ण;

/*
 * context associated with a receive descriptor.
 * @rxp_ctx: opaque context associated with frame that starts at each
 *           rx ring index.
 * @dst_sg:  Scatterlist used to क्रमm reply frames beginning at a given ring
 *           index. Retained in order to unmap each sg after reply is processed.
 * @rxin_numd: Number of rx descriptors associated with the message that starts
 *             at a descriptor index. Not set क्रम every index. For example,
 *             अगर descriptor index i poपूर्णांकs to a scatterlist with 4 entries,
 *             then the next three descriptor indexes करोn't have a value set.
 * @resp_hdr: Virtual address of buffer used to catch DMA rx status
 * @resp_hdr_daddr: physical address of DMA rx status buffer
 */
काष्ठा pdc_rx_ctx अणु
	व्योम *rxp_ctx;
	काष्ठा scatterlist *dst_sg;
	u32  rxin_numd;
	व्योम *resp_hdr;
	dma_addr_t resp_hdr_daddr;
पूर्ण;

/* PDC state काष्ठाure */
काष्ठा pdc_state अणु
	/* Index of the PDC whose state is in this काष्ठाure instance */
	u8 pdc_idx;

	/* Platक्रमm device क्रम this PDC instance */
	काष्ठा platक्रमm_device *pdev;

	/*
	 * Each PDC instance has a mailbox controller. PDC receives request
	 * messages through mailboxes, and sends response messages through the
	 * mailbox framework.
	 */
	काष्ठा mbox_controller mbc;

	अचिन्हित पूर्णांक pdc_irq;

	/* tasklet क्रम deferred processing after DMA rx पूर्णांकerrupt */
	काष्ठा tasklet_काष्ठा rx_tasklet;

	/* Number of bytes of receive status prior to each rx frame */
	u32 rx_status_len;
	/* Whether a BCM header is prepended to each frame */
	bool use_bcm_hdr;
	/* Sum of length of BCM header and rx status header */
	u32 pdc_resp_hdr_len;

	/* The base भव address of DMA hw रेजिस्टरs */
	व्योम __iomem *pdc_reg_vbase;

	/* Pool क्रम allocation of DMA rings */
	काष्ठा dma_pool *ring_pool;

	/* Pool क्रम allocation of metadata buffers क्रम response messages */
	काष्ठा dma_pool *rx_buf_pool;

	/*
	 * The base भव address of DMA tx/rx descriptor rings. Corresponding
	 * DMA address and size of ring allocation.
	 */
	काष्ठा pdc_ring_alloc tx_ring_alloc;
	काष्ठा pdc_ring_alloc rx_ring_alloc;

	काष्ठा pdc_regs *regs;    /* start of PDC रेजिस्टरs */

	काष्ठा dma64_regs *txregs_64; /* dma tx engine रेजिस्टरs */
	काष्ठा dma64_regs *rxregs_64; /* dma rx engine रेजिस्टरs */

	/*
	 * Arrays of PDC_RING_ENTRIES descriptors
	 * To use multiple ringsets, this needs to be extended
	 */
	काष्ठा dma64dd   *txd_64;  /* tx descriptor ring */
	काष्ठा dma64dd   *rxd_64;  /* rx descriptor ring */

	/* descriptor ring sizes */
	u32      ntxd;       /* # tx descriptors */
	u32      nrxd;       /* # rx descriptors */
	u32      nrxpost;    /* # rx buffers to keep posted */
	u32      ntxpost;    /* max number of tx buffers that can be posted */

	/*
	 * Index of next tx descriptor to reclaim. That is, the descriptor
	 * index of the oldest tx buffer क्रम which the host has yet to process
	 * the corresponding response.
	 */
	u32  txin;

	/*
	 * Index of the first receive descriptor क्रम the sequence of
	 * message fragments currently under स्थिरruction. Used to build up
	 * the rxin_numd count क्रम a message. Updated to rxout when the host
	 * starts a new sequence of rx buffers क्रम a new message.
	 */
	u32  tx_msg_start;

	/* Index of next tx descriptor to post. */
	u32  txout;

	/*
	 * Number of tx descriptors associated with the message that starts
	 * at this tx descriptor index.
	 */
	u32      txin_numd[PDC_RING_ENTRIES];

	/*
	 * Index of next rx descriptor to reclaim. This is the index of
	 * the next descriptor whose data has yet to be processed by the host.
	 */
	u32  rxin;

	/*
	 * Index of the first receive descriptor क्रम the sequence of
	 * message fragments currently under स्थिरruction. Used to build up
	 * the rxin_numd count क्रम a message. Updated to rxout when the host
	 * starts a new sequence of rx buffers क्रम a new message.
	 */
	u32  rx_msg_start;

	/*
	 * Saved value of current hardware rx descriptor index.
	 * The last rx buffer written by the hw is the index previous to
	 * this one.
	 */
	u32  last_rx_curr;

	/* Index of next rx descriptor to post. */
	u32  rxout;

	काष्ठा pdc_rx_ctx rx_ctx[PDC_RING_ENTRIES];

	/*
	 * Scatterlists used to क्रमm request and reply frames beginning at a
	 * given ring index. Retained in order to unmap each sg after reply
	 * is processed
	 */
	काष्ठा scatterlist *src_sg[PDC_RING_ENTRIES];

	/* counters */
	u32  pdc_requests;     /* number of request messages submitted */
	u32  pdc_replies;      /* number of reply messages received */
	u32  last_tx_not_करोne; /* too few tx descriptors to indicate करोne */
	u32  tx_ring_full;     /* unable to accept msg because tx ring full */
	u32  rx_ring_full;     /* unable to accept msg because rx ring full */
	u32  txnobuf;          /* unable to create tx descriptor */
	u32  rxnobuf;          /* unable to create rx descriptor */
	u32  rx_oflow;         /* count of rx overflows */

	/* hardware type - FA2 or PDC/MDE */
	क्रमागत pdc_hw hw_type;
पूर्ण;

/* Global variables */

काष्ठा pdc_globals अणु
	/* Actual number of SPUs in hardware, as reported by device tree */
	u32 num_spu;
पूर्ण;

अटल काष्ठा pdc_globals pdcg;

/* top level debug FS directory क्रम PDC driver */
अटल काष्ठा dentry *debugfs_dir;

अटल sमाप_प्रकार pdc_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा pdc_state *pdcs;
	अक्षर *buf;
	sमाप_प्रकार ret, out_offset, out_count;

	out_count = 512;

	buf = kदो_स्मृति(out_count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pdcs = filp->निजी_data;
	out_offset = 0;
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "SPU %u stats:\n", pdcs->pdc_idx);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "PDC requests....................%u\n",
			       pdcs->pdc_requests);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "PDC responses...................%u\n",
			       pdcs->pdc_replies);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Tx not done.....................%u\n",
			       pdcs->last_tx_not_करोne);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Tx ring full....................%u\n",
			       pdcs->tx_ring_full);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Rx ring full....................%u\n",
			       pdcs->rx_ring_full);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Tx desc write fail. Ring full...%u\n",
			       pdcs->txnobuf);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Rx desc write fail. Ring full...%u\n",
			       pdcs->rxnobuf);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Receive overflow................%u\n",
			       pdcs->rx_oflow);
	out_offset += scnम_लिखो(buf + out_offset, out_count - out_offset,
			       "Num frags in rx ring............%u\n",
			       NRXDACTIVE(pdcs->rxin, pdcs->last_rx_curr,
					  pdcs->nrxpost));

	अगर (out_offset > out_count)
		out_offset = out_count;

	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, buf, out_offset);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations pdc_debugfs_stats = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = pdc_debugfs_पढ़ो,
पूर्ण;

/**
 * pdc_setup_debugfs() - Create the debug FS directories. If the top-level
 * directory has not yet been created, create it now. Create a stats file in
 * this directory क्रम a SPU.
 * @pdcs: PDC state काष्ठाure
 */
अटल व्योम pdc_setup_debugfs(काष्ठा pdc_state *pdcs)
अणु
	अक्षर spu_stats_name[16];

	अगर (!debugfs_initialized())
		वापस;

	snम_लिखो(spu_stats_name, 16, "pdc%d_stats", pdcs->pdc_idx);
	अगर (!debugfs_dir)
		debugfs_dir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	/* S_IRUSR == 0400 */
	debugfs_create_file(spu_stats_name, 0400, debugfs_dir, pdcs,
			    &pdc_debugfs_stats);
पूर्ण

अटल व्योम pdc_मुक्त_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(debugfs_dir);
	debugfs_dir = शून्य;
पूर्ण

/**
 * pdc_build_rxd() - Build DMA descriptor to receive SPU result.
 * @pdcs:      PDC state क्रम SPU that will generate result
 * @dma_addr:  DMA address of buffer that descriptor is being built क्रम
 * @buf_len:   Length of the receive buffer, in bytes
 * @flags:     Flags to be stored in descriptor
 */
अटल अंतरभूत व्योम
pdc_build_rxd(काष्ठा pdc_state *pdcs, dma_addr_t dma_addr,
	      u32 buf_len, u32 flags)
अणु
	काष्ठा device *dev = &pdcs->pdev->dev;
	काष्ठा dma64dd *rxd = &pdcs->rxd_64[pdcs->rxout];

	dev_dbg(dev,
		"Writing rx descriptor for PDC %u at index %u with length %u. flags %#x\n",
		pdcs->pdc_idx, pdcs->rxout, buf_len, flags);

	rxd->addrlow = cpu_to_le32(lower_32_bits(dma_addr));
	rxd->addrhigh = cpu_to_le32(upper_32_bits(dma_addr));
	rxd->ctrl1 = cpu_to_le32(flags);
	rxd->ctrl2 = cpu_to_le32(buf_len);

	/* bump ring index and वापस */
	pdcs->rxout = NEXTRXD(pdcs->rxout, pdcs->nrxpost);
पूर्ण

/**
 * pdc_build_txd() - Build a DMA descriptor to transmit a SPU request to
 * hardware.
 * @pdcs:        PDC state क्रम the SPU that will process this request
 * @dma_addr:    DMA address of packet to be transmitted
 * @buf_len:     Length of tx buffer, in bytes
 * @flags:       Flags to be stored in descriptor
 */
अटल अंतरभूत व्योम
pdc_build_txd(काष्ठा pdc_state *pdcs, dma_addr_t dma_addr, u32 buf_len,
	      u32 flags)
अणु
	काष्ठा device *dev = &pdcs->pdev->dev;
	काष्ठा dma64dd *txd = &pdcs->txd_64[pdcs->txout];

	dev_dbg(dev,
		"Writing tx descriptor for PDC %u at index %u with length %u, flags %#x\n",
		pdcs->pdc_idx, pdcs->txout, buf_len, flags);

	txd->addrlow = cpu_to_le32(lower_32_bits(dma_addr));
	txd->addrhigh = cpu_to_le32(upper_32_bits(dma_addr));
	txd->ctrl1 = cpu_to_le32(flags);
	txd->ctrl2 = cpu_to_le32(buf_len);

	/* bump ring index and वापस */
	pdcs->txout = NEXTTXD(pdcs->txout, pdcs->ntxpost);
पूर्ण

/**
 * pdc_receive_one() - Receive a response message from a given SPU.
 * @pdcs:    PDC state क्रम the SPU to receive from
 *
 * When the वापस code indicates success, the response message is available in
 * the receive buffers provided prior to submission of the request.
 *
 * Return:  PDC_SUCCESS अगर one or more receive descriptors was processed
 *          -EAGAIN indicates that no response message is available
 *          -EIO an error occurred
 */
अटल पूर्णांक
pdc_receive_one(काष्ठा pdc_state *pdcs)
अणु
	काष्ठा device *dev = &pdcs->pdev->dev;
	काष्ठा mbox_controller *mbc;
	काष्ठा mbox_chan *chan;
	काष्ठा brcm_message mssg;
	u32 len, rx_status;
	u32 num_frags;
	u8 *resp_hdr;    /* भव addr of start of resp message DMA header */
	u32 frags_rdy;   /* number of fragments पढ़ोy to पढ़ो */
	u32 rx_idx;      /* ring index of start of receive frame */
	dma_addr_t resp_hdr_daddr;
	काष्ठा pdc_rx_ctx *rx_ctx;

	mbc = &pdcs->mbc;
	chan = &mbc->chans[0];
	mssg.type = BRCM_MESSAGE_SPU;

	/*
	 * वापस अगर a complete response message is not yet पढ़ोy.
	 * rxin_numd[rxin] is the number of fragments in the next msg
	 * to पढ़ो.
	 */
	frags_rdy = NRXDACTIVE(pdcs->rxin, pdcs->last_rx_curr, pdcs->nrxpost);
	अगर ((frags_rdy == 0) ||
	    (frags_rdy < pdcs->rx_ctx[pdcs->rxin].rxin_numd))
		/* No response पढ़ोy */
		वापस -EAGAIN;

	num_frags = pdcs->txin_numd[pdcs->txin];
	WARN_ON(num_frags == 0);

	dma_unmap_sg(dev, pdcs->src_sg[pdcs->txin],
		     sg_nents(pdcs->src_sg[pdcs->txin]), DMA_TO_DEVICE);

	pdcs->txin = (pdcs->txin + num_frags) & pdcs->ntxpost;

	dev_dbg(dev, "PDC %u reclaimed %d tx descriptors",
		pdcs->pdc_idx, num_frags);

	rx_idx = pdcs->rxin;
	rx_ctx = &pdcs->rx_ctx[rx_idx];
	num_frags = rx_ctx->rxin_numd;
	/* Return opaque context with result */
	mssg.ctx = rx_ctx->rxp_ctx;
	rx_ctx->rxp_ctx = शून्य;
	resp_hdr = rx_ctx->resp_hdr;
	resp_hdr_daddr = rx_ctx->resp_hdr_daddr;
	dma_unmap_sg(dev, rx_ctx->dst_sg, sg_nents(rx_ctx->dst_sg),
		     DMA_FROM_DEVICE);

	pdcs->rxin = (pdcs->rxin + num_frags) & pdcs->nrxpost;

	dev_dbg(dev, "PDC %u reclaimed %d rx descriptors",
		pdcs->pdc_idx, num_frags);

	dev_dbg(dev,
		"PDC %u txin %u, txout %u, rxin %u, rxout %u, last_rx_curr %u\n",
		pdcs->pdc_idx, pdcs->txin, pdcs->txout, pdcs->rxin,
		pdcs->rxout, pdcs->last_rx_curr);

	अगर (pdcs->pdc_resp_hdr_len == PDC_SPUM_RESP_HDR_LEN) अणु
		/*
		 * For SPU-M, get length of response msg and rx overflow status.
		 */
		rx_status = *((u32 *)resp_hdr);
		len = rx_status & RX_STATUS_LEN;
		dev_dbg(dev,
			"SPU response length %u bytes", len);
		अगर (unlikely(((rx_status & RX_STATUS_OVERFLOW) || (!len)))) अणु
			अगर (rx_status & RX_STATUS_OVERFLOW) अणु
				dev_err_ratelimited(dev,
						    "crypto receive overflow");
				pdcs->rx_oflow++;
			पूर्ण अन्यथा अणु
				dev_info_ratelimited(dev, "crypto rx len = 0");
			पूर्ण
			वापस -EIO;
		पूर्ण
	पूर्ण

	dma_pool_मुक्त(pdcs->rx_buf_pool, resp_hdr, resp_hdr_daddr);

	mbox_chan_received_data(chan, &mssg);

	pdcs->pdc_replies++;
	वापस PDC_SUCCESS;
पूर्ण

/**
 * pdc_receive() - Process as many responses as are available in the rx ring.
 * @pdcs:  PDC state
 *
 * Called within the hard IRQ.
 * Return:
 */
अटल पूर्णांक
pdc_receive(काष्ठा pdc_state *pdcs)
अणु
	पूर्णांक rx_status;

	/* पढ़ो last_rx_curr from रेजिस्टर once */
	pdcs->last_rx_curr =
	    (ioपढ़ो32((स्थिर व्योम __iomem *)&pdcs->rxregs_64->status0) &
	     CRYPTO_D64_RS0_CD_MASK) / RING_ENTRY_SIZE;

	करो अणु
		/* Could be many frames पढ़ोy */
		rx_status = pdc_receive_one(pdcs);
	पूर्ण जबतक (rx_status == PDC_SUCCESS);

	वापस 0;
पूर्ण

/**
 * pdc_tx_list_sg_add() - Add the buffers in a scatterlist to the transmit
 * descriptors क्रम a given SPU. The scatterlist buffers contain the data क्रम a
 * SPU request message.
 * @spu_idx:   The index of the SPU to submit the request to, [0, max_spu)
 * @sg:        Scatterlist whose buffers contain part of the SPU request
 *
 * If a scatterlist buffer is larger than PDC_DMA_BUF_MAX, multiple descriptors
 * are written क्रम that buffer, each <= PDC_DMA_BUF_MAX byte in length.
 *
 * Return: PDC_SUCCESS अगर successful
 *         < 0 otherwise
 */
अटल पूर्णांक pdc_tx_list_sg_add(काष्ठा pdc_state *pdcs, काष्ठा scatterlist *sg)
अणु
	u32 flags = 0;
	u32 eot;
	u32 tx_avail;

	/*
	 * Num descriptors needed. Conservatively assume we need a descriptor
	 * क्रम every entry in sg.
	 */
	u32 num_desc;
	u32 desc_w = 0;	/* Number of tx descriptors written */
	u32 bufcnt;	/* Number of bytes of buffer poपूर्णांकed to by descriptor */
	dma_addr_t databufptr;	/* DMA address to put in descriptor */

	num_desc = (u32)sg_nents(sg);

	/* check whether enough tx descriptors are available */
	tx_avail = pdcs->ntxpost - NTXDACTIVE(pdcs->txin, pdcs->txout,
					      pdcs->ntxpost);
	अगर (unlikely(num_desc > tx_avail)) अणु
		pdcs->txnobuf++;
		वापस -ENOSPC;
	पूर्ण

	/* build tx descriptors */
	अगर (pdcs->tx_msg_start == pdcs->txout) अणु
		/* Start of frame */
		pdcs->txin_numd[pdcs->tx_msg_start] = 0;
		pdcs->src_sg[pdcs->txout] = sg;
		flags = D64_CTRL1_SOF;
	पूर्ण

	जबतक (sg) अणु
		अगर (unlikely(pdcs->txout == (pdcs->ntxd - 1)))
			eot = D64_CTRL1_EOT;
		अन्यथा
			eot = 0;

		/*
		 * If sg buffer larger than PDC limit, split across
		 * multiple descriptors
		 */
		bufcnt = sg_dma_len(sg);
		databufptr = sg_dma_address(sg);
		जबतक (bufcnt > PDC_DMA_BUF_MAX) अणु
			pdc_build_txd(pdcs, databufptr, PDC_DMA_BUF_MAX,
				      flags | eot);
			desc_w++;
			bufcnt -= PDC_DMA_BUF_MAX;
			databufptr += PDC_DMA_BUF_MAX;
			अगर (unlikely(pdcs->txout == (pdcs->ntxd - 1)))
				eot = D64_CTRL1_EOT;
			अन्यथा
				eot = 0;
		पूर्ण
		sg = sg_next(sg);
		अगर (!sg)
			/* Writing last descriptor क्रम frame */
			flags |= (D64_CTRL1_खातापूर्ण | D64_CTRL1_IOC);
		pdc_build_txd(pdcs, databufptr, bufcnt, flags | eot);
		desc_w++;
		/* Clear start of frame after first descriptor */
		flags &= ~D64_CTRL1_SOF;
	पूर्ण
	pdcs->txin_numd[pdcs->tx_msg_start] += desc_w;

	वापस PDC_SUCCESS;
पूर्ण

/**
 * pdc_tx_list_final() - Initiate DMA transfer of last frame written to tx
 * ring.
 * @pdcs:  PDC state क्रम SPU to process the request
 *
 * Sets the index of the last descriptor written in both the rx and tx ring.
 *
 * Return: PDC_SUCCESS
 */
अटल पूर्णांक pdc_tx_list_final(काष्ठा pdc_state *pdcs)
अणु
	/*
	 * ग_लिखो barrier to ensure all रेजिस्टर ग_लिखोs are complete
	 * beक्रमe chip starts to process new request
	 */
	wmb();
	ioग_लिखो32(pdcs->rxout << 4, &pdcs->rxregs_64->ptr);
	ioग_लिखो32(pdcs->txout << 4, &pdcs->txregs_64->ptr);
	pdcs->pdc_requests++;

	वापस PDC_SUCCESS;
पूर्ण

/**
 * pdc_rx_list_init() - Start a new receive descriptor list क्रम a given PDC.
 * @pdcs:   PDC state क्रम SPU handling request
 * @dst_sg: scatterlist providing rx buffers क्रम response to be वापसed to
 *	    mailbox client
 * @ctx:    Opaque context क्रम this request
 *
 * Posts a single receive descriptor to hold the metadata that precedes a
 * response. For example, with SPU-M, the metadata is a 32-byte DMA header and
 * an 8-byte BCM header. Moves the msg_start descriptor indexes क्रम both tx and
 * rx to indicate the start of a new message.
 *
 * Return:  PDC_SUCCESS अगर successful
 *          < 0 अगर an error (e.g., rx ring is full)
 */
अटल पूर्णांक pdc_rx_list_init(काष्ठा pdc_state *pdcs, काष्ठा scatterlist *dst_sg,
			    व्योम *ctx)
अणु
	u32 flags = 0;
	u32 rx_avail;
	u32 rx_pkt_cnt = 1;	/* Adding a single rx buffer */
	dma_addr_t daddr;
	व्योम *vaddr;
	काष्ठा pdc_rx_ctx *rx_ctx;

	rx_avail = pdcs->nrxpost - NRXDACTIVE(pdcs->rxin, pdcs->rxout,
					      pdcs->nrxpost);
	अगर (unlikely(rx_pkt_cnt > rx_avail)) अणु
		pdcs->rxnobuf++;
		वापस -ENOSPC;
	पूर्ण

	/* allocate a buffer क्रम the dma rx status */
	vaddr = dma_pool_zalloc(pdcs->rx_buf_pool, GFP_ATOMIC, &daddr);
	अगर (unlikely(!vaddr))
		वापस -ENOMEM;

	/*
	 * Update msg_start indexes क्रम both tx and rx to indicate the start
	 * of a new sequence of descriptor indexes that contain the fragments
	 * of the same message.
	 */
	pdcs->rx_msg_start = pdcs->rxout;
	pdcs->tx_msg_start = pdcs->txout;

	/* This is always the first descriptor in the receive sequence */
	flags = D64_CTRL1_SOF;
	pdcs->rx_ctx[pdcs->rx_msg_start].rxin_numd = 1;

	अगर (unlikely(pdcs->rxout == (pdcs->nrxd - 1)))
		flags |= D64_CTRL1_EOT;

	rx_ctx = &pdcs->rx_ctx[pdcs->rxout];
	rx_ctx->rxp_ctx = ctx;
	rx_ctx->dst_sg = dst_sg;
	rx_ctx->resp_hdr = vaddr;
	rx_ctx->resp_hdr_daddr = daddr;
	pdc_build_rxd(pdcs, daddr, pdcs->pdc_resp_hdr_len, flags);
	वापस PDC_SUCCESS;
पूर्ण

/**
 * pdc_rx_list_sg_add() - Add the buffers in a scatterlist to the receive
 * descriptors क्रम a given SPU. The caller must have alपढ़ोy DMA mapped the
 * scatterlist.
 * @spu_idx:    Indicates which SPU the buffers are क्रम
 * @sg:         Scatterlist whose buffers are added to the receive ring
 *
 * If a receive buffer in the scatterlist is larger than PDC_DMA_BUF_MAX,
 * multiple receive descriptors are written, each with a buffer <=
 * PDC_DMA_BUF_MAX.
 *
 * Return: PDC_SUCCESS अगर successful
 *         < 0 otherwise (e.g., receive ring is full)
 */
अटल पूर्णांक pdc_rx_list_sg_add(काष्ठा pdc_state *pdcs, काष्ठा scatterlist *sg)
अणु
	u32 flags = 0;
	u32 rx_avail;

	/*
	 * Num descriptors needed. Conservatively assume we need a descriptor
	 * क्रम every entry from our starting poपूर्णांक in the scatterlist.
	 */
	u32 num_desc;
	u32 desc_w = 0;	/* Number of tx descriptors written */
	u32 bufcnt;	/* Number of bytes of buffer poपूर्णांकed to by descriptor */
	dma_addr_t databufptr;	/* DMA address to put in descriptor */

	num_desc = (u32)sg_nents(sg);

	rx_avail = pdcs->nrxpost - NRXDACTIVE(pdcs->rxin, pdcs->rxout,
					      pdcs->nrxpost);
	अगर (unlikely(num_desc > rx_avail)) अणु
		pdcs->rxnobuf++;
		वापस -ENOSPC;
	पूर्ण

	जबतक (sg) अणु
		अगर (unlikely(pdcs->rxout == (pdcs->nrxd - 1)))
			flags = D64_CTRL1_EOT;
		अन्यथा
			flags = 0;

		/*
		 * If sg buffer larger than PDC limit, split across
		 * multiple descriptors
		 */
		bufcnt = sg_dma_len(sg);
		databufptr = sg_dma_address(sg);
		जबतक (bufcnt > PDC_DMA_BUF_MAX) अणु
			pdc_build_rxd(pdcs, databufptr, PDC_DMA_BUF_MAX, flags);
			desc_w++;
			bufcnt -= PDC_DMA_BUF_MAX;
			databufptr += PDC_DMA_BUF_MAX;
			अगर (unlikely(pdcs->rxout == (pdcs->nrxd - 1)))
				flags = D64_CTRL1_EOT;
			अन्यथा
				flags = 0;
		पूर्ण
		pdc_build_rxd(pdcs, databufptr, bufcnt, flags);
		desc_w++;
		sg = sg_next(sg);
	पूर्ण
	pdcs->rx_ctx[pdcs->rx_msg_start].rxin_numd += desc_w;

	वापस PDC_SUCCESS;
पूर्ण

/**
 * pdc_irq_handler() - Interrupt handler called in पूर्णांकerrupt context.
 * @irq:      Interrupt number that has fired
 * @data:     device काष्ठा क्रम DMA engine that generated the पूर्णांकerrupt
 *
 * We have to clear the device पूर्णांकerrupt status flags here. So cache the
 * status क्रम later use in the thपढ़ो function. Other than that, just वापस
 * WAKE_THREAD to invoke the thपढ़ो function.
 *
 * Return: IRQ_WAKE_THREAD अगर पूर्णांकerrupt is ours
 *         IRQ_NONE otherwise
 */
अटल irqवापस_t pdc_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा device *dev = (काष्ठा device *)data;
	काष्ठा pdc_state *pdcs = dev_get_drvdata(dev);
	u32 पूर्णांकstatus = ioपढ़ो32(pdcs->pdc_reg_vbase + PDC_INTSTATUS_OFFSET);

	अगर (unlikely(पूर्णांकstatus == 0))
		वापस IRQ_NONE;

	/* Disable पूर्णांकerrupts until soft handler runs */
	ioग_लिखो32(0, pdcs->pdc_reg_vbase + PDC_INTMASK_OFFSET);

	/* Clear पूर्णांकerrupt flags in device */
	ioग_लिखो32(पूर्णांकstatus, pdcs->pdc_reg_vbase + PDC_INTSTATUS_OFFSET);

	/* Wakeup IRQ thपढ़ो */
	tasklet_schedule(&pdcs->rx_tasklet);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * pdc_tasklet_cb() - Tasklet callback that runs the deferred processing after
 * a DMA receive पूर्णांकerrupt. Reenables the receive पूर्णांकerrupt.
 * @data: PDC state काष्ठाure
 */
अटल व्योम pdc_tasklet_cb(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा pdc_state *pdcs = from_tasklet(pdcs, t, rx_tasklet);

	pdc_receive(pdcs);

	/* reenable पूर्णांकerrupts */
	ioग_लिखो32(PDC_INTMASK, pdcs->pdc_reg_vbase + PDC_INTMASK_OFFSET);
पूर्ण

/**
 * pdc_ring_init() - Allocate DMA rings and initialize स्थिरant fields of
 * descriptors in one ringset.
 * @pdcs:    PDC instance state
 * @ringset: index of ringset being used
 *
 * Return: PDC_SUCCESS अगर ring initialized
 *         < 0 otherwise
 */
अटल पूर्णांक pdc_ring_init(काष्ठा pdc_state *pdcs, पूर्णांक ringset)
अणु
	पूर्णांक i;
	पूर्णांक err = PDC_SUCCESS;
	काष्ठा dma64 *dma_reg;
	काष्ठा device *dev = &pdcs->pdev->dev;
	काष्ठा pdc_ring_alloc tx;
	काष्ठा pdc_ring_alloc rx;

	/* Allocate tx ring */
	tx.vbase = dma_pool_zalloc(pdcs->ring_pool, GFP_KERNEL, &tx.dmabase);
	अगर (unlikely(!tx.vbase)) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Allocate rx ring */
	rx.vbase = dma_pool_zalloc(pdcs->ring_pool, GFP_KERNEL, &rx.dmabase);
	अगर (unlikely(!rx.vbase)) अणु
		err = -ENOMEM;
		जाओ fail_dealloc;
	पूर्ण

	dev_dbg(dev, " - base DMA addr of tx ring      %pad", &tx.dmabase);
	dev_dbg(dev, " - base virtual addr of tx ring  %p", tx.vbase);
	dev_dbg(dev, " - base DMA addr of rx ring      %pad", &rx.dmabase);
	dev_dbg(dev, " - base virtual addr of rx ring  %p", rx.vbase);

	स_नकल(&pdcs->tx_ring_alloc, &tx, माप(tx));
	स_नकल(&pdcs->rx_ring_alloc, &rx, माप(rx));

	pdcs->rxin = 0;
	pdcs->rx_msg_start = 0;
	pdcs->last_rx_curr = 0;
	pdcs->rxout = 0;
	pdcs->txin = 0;
	pdcs->tx_msg_start = 0;
	pdcs->txout = 0;

	/* Set descriptor array base addresses */
	pdcs->txd_64 = (काष्ठा dma64dd *)pdcs->tx_ring_alloc.vbase;
	pdcs->rxd_64 = (काष्ठा dma64dd *)pdcs->rx_ring_alloc.vbase;

	/* Tell device the base DMA address of each ring */
	dma_reg = &pdcs->regs->dmaregs[ringset];

	/* But first disable DMA and set curptr to 0 क्रम both TX & RX */
	ioग_लिखो32(PDC_TX_CTL, &dma_reg->dmaxmt.control);
	ioग_लिखो32((PDC_RX_CTL + (pdcs->rx_status_len << 1)),
		  &dma_reg->dmarcv.control);
	ioग_लिखो32(0, &dma_reg->dmaxmt.ptr);
	ioग_लिखो32(0, &dma_reg->dmarcv.ptr);

	/* Set base DMA addresses */
	ioग_लिखो32(lower_32_bits(pdcs->tx_ring_alloc.dmabase),
		  &dma_reg->dmaxmt.addrlow);
	ioग_लिखो32(upper_32_bits(pdcs->tx_ring_alloc.dmabase),
		  &dma_reg->dmaxmt.addrhigh);

	ioग_लिखो32(lower_32_bits(pdcs->rx_ring_alloc.dmabase),
		  &dma_reg->dmarcv.addrlow);
	ioग_लिखो32(upper_32_bits(pdcs->rx_ring_alloc.dmabase),
		  &dma_reg->dmarcv.addrhigh);

	/* Re-enable DMA */
	ioग_लिखो32(PDC_TX_CTL | PDC_TX_ENABLE, &dma_reg->dmaxmt.control);
	ioग_लिखो32((PDC_RX_CTL | PDC_RX_ENABLE | (pdcs->rx_status_len << 1)),
		  &dma_reg->dmarcv.control);

	/* Initialize descriptors */
	क्रम (i = 0; i < PDC_RING_ENTRIES; i++) अणु
		/* Every tx descriptor can be used क्रम start of frame. */
		अगर (i != pdcs->ntxpost) अणु
			ioग_लिखो32(D64_CTRL1_SOF | D64_CTRL1_खातापूर्ण,
				  &pdcs->txd_64[i].ctrl1);
		पूर्ण अन्यथा अणु
			/* Last descriptor in ringset. Set End of Table. */
			ioग_लिखो32(D64_CTRL1_SOF | D64_CTRL1_खातापूर्ण |
				  D64_CTRL1_EOT, &pdcs->txd_64[i].ctrl1);
		पूर्ण

		/* Every rx descriptor can be used क्रम start of frame */
		अगर (i != pdcs->nrxpost) अणु
			ioग_लिखो32(D64_CTRL1_SOF,
				  &pdcs->rxd_64[i].ctrl1);
		पूर्ण अन्यथा अणु
			/* Last descriptor in ringset. Set End of Table. */
			ioग_लिखो32(D64_CTRL1_SOF | D64_CTRL1_EOT,
				  &pdcs->rxd_64[i].ctrl1);
		पूर्ण
	पूर्ण
	वापस PDC_SUCCESS;

fail_dealloc:
	dma_pool_मुक्त(pdcs->ring_pool, tx.vbase, tx.dmabase);
करोne:
	वापस err;
पूर्ण

अटल व्योम pdc_ring_मुक्त(काष्ठा pdc_state *pdcs)
अणु
	अगर (pdcs->tx_ring_alloc.vbase) अणु
		dma_pool_मुक्त(pdcs->ring_pool, pdcs->tx_ring_alloc.vbase,
			      pdcs->tx_ring_alloc.dmabase);
		pdcs->tx_ring_alloc.vbase = शून्य;
	पूर्ण

	अगर (pdcs->rx_ring_alloc.vbase) अणु
		dma_pool_मुक्त(pdcs->ring_pool, pdcs->rx_ring_alloc.vbase,
			      pdcs->rx_ring_alloc.dmabase);
		pdcs->rx_ring_alloc.vbase = शून्य;
	पूर्ण
पूर्ण

/**
 * pdc_desc_count() - Count the number of DMA descriptors that will be required
 * क्रम a given scatterlist. Account क्रम the max length of a DMA buffer.
 * @sg:    Scatterlist to be DMA'd
 * Return: Number of descriptors required
 */
अटल u32 pdc_desc_count(काष्ठा scatterlist *sg)
अणु
	u32 cnt = 0;

	जबतक (sg) अणु
		cnt += ((sg->length / PDC_DMA_BUF_MAX) + 1);
		sg = sg_next(sg);
	पूर्ण
	वापस cnt;
पूर्ण

/**
 * pdc_rings_full() - Check whether the tx ring has room क्रम tx_cnt descriptors
 * and the rx ring has room क्रम rx_cnt descriptors.
 * @pdcs:  PDC state
 * @tx_cnt: The number of descriptors required in the tx ring
 * @rx_cnt: The number of descriptors required i the rx ring
 *
 * Return: true अगर one of the rings करोes not have enough space
 *         false अगर sufficient space is available in both rings
 */
अटल bool pdc_rings_full(काष्ठा pdc_state *pdcs, पूर्णांक tx_cnt, पूर्णांक rx_cnt)
अणु
	u32 rx_avail;
	u32 tx_avail;
	bool full = false;

	/* Check अगर the tx and rx rings are likely to have enough space */
	rx_avail = pdcs->nrxpost - NRXDACTIVE(pdcs->rxin, pdcs->rxout,
					      pdcs->nrxpost);
	अगर (unlikely(rx_cnt > rx_avail)) अणु
		pdcs->rx_ring_full++;
		full = true;
	पूर्ण

	अगर (likely(!full)) अणु
		tx_avail = pdcs->ntxpost - NTXDACTIVE(pdcs->txin, pdcs->txout,
						      pdcs->ntxpost);
		अगर (unlikely(tx_cnt > tx_avail)) अणु
			pdcs->tx_ring_full++;
			full = true;
		पूर्ण
	पूर्ण
	वापस full;
पूर्ण

/**
 * pdc_last_tx_करोne() - If both the tx and rx rings have at least
 * PDC_RING_SPACE_MIN descriptors available, then indicate that the mailbox
 * framework can submit another message.
 * @chan:  mailbox channel to check
 * Return: true अगर PDC can accept another message on this channel
 */
अटल bool pdc_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	काष्ठा pdc_state *pdcs = chan->con_priv;
	bool ret;

	अगर (unlikely(pdc_rings_full(pdcs, PDC_RING_SPACE_MIN,
				    PDC_RING_SPACE_MIN))) अणु
		pdcs->last_tx_not_करोne++;
		ret = false;
	पूर्ण अन्यथा अणु
		ret = true;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * pdc_send_data() - mailbox send_data function
 * @chan:	The mailbox channel on which the data is sent. The channel
 *              corresponds to a DMA ringset.
 * @data:	The mailbox message to be sent. The message must be a
 *              brcm_message काष्ठाure.
 *
 * This function is रेजिस्टरed as the send_data function क्रम the mailbox
 * controller. From the destination scatterlist in the mailbox message, it
 * creates a sequence of receive descriptors in the rx ring. From the source
 * scatterlist, it creates a sequence of transmit descriptors in the tx ring.
 * After creating the descriptors, it ग_लिखोs the rx ptr and tx ptr रेजिस्टरs to
 * initiate the DMA transfer.
 *
 * This function करोes the DMA map and unmap of the src and dst scatterlists in
 * the mailbox message.
 *
 * Return: 0 अगर successful
 *	   -ENOTSUPP अगर the mailbox message is a type this driver करोes not
 *			support
 *         < 0 अगर an error
 */
अटल पूर्णांक pdc_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा pdc_state *pdcs = chan->con_priv;
	काष्ठा device *dev = &pdcs->pdev->dev;
	काष्ठा brcm_message *mssg = data;
	पूर्णांक err = PDC_SUCCESS;
	पूर्णांक src_nent;
	पूर्णांक dst_nent;
	पूर्णांक nent;
	u32 tx_desc_req;
	u32 rx_desc_req;

	अगर (unlikely(mssg->type != BRCM_MESSAGE_SPU))
		वापस -ENOTSUPP;

	src_nent = sg_nents(mssg->spu.src);
	अगर (likely(src_nent)) अणु
		nent = dma_map_sg(dev, mssg->spu.src, src_nent, DMA_TO_DEVICE);
		अगर (unlikely(nent == 0))
			वापस -EIO;
	पूर्ण

	dst_nent = sg_nents(mssg->spu.dst);
	अगर (likely(dst_nent)) अणु
		nent = dma_map_sg(dev, mssg->spu.dst, dst_nent,
				  DMA_FROM_DEVICE);
		अगर (unlikely(nent == 0)) अणु
			dma_unmap_sg(dev, mssg->spu.src, src_nent,
				     DMA_TO_DEVICE);
			वापस -EIO;
		पूर्ण
	पूर्ण

	/*
	 * Check अगर the tx and rx rings have enough space. Do this prior to
	 * writing any tx or rx descriptors. Need to ensure that we करो not ग_लिखो
	 * a partial set of descriptors, or ग_लिखो just rx descriptors but
	 * corresponding tx descriptors करोn't fit. Note that we want this check
	 * and the entire sequence of descriptor to happen without another
	 * thपढ़ो getting in. The channel spin lock in the mailbox framework
	 * ensures this.
	 */
	tx_desc_req = pdc_desc_count(mssg->spu.src);
	rx_desc_req = pdc_desc_count(mssg->spu.dst);
	अगर (unlikely(pdc_rings_full(pdcs, tx_desc_req, rx_desc_req + 1)))
		वापस -ENOSPC;

	/* Create rx descriptors to SPU catch response */
	err = pdc_rx_list_init(pdcs, mssg->spu.dst, mssg->ctx);
	err |= pdc_rx_list_sg_add(pdcs, mssg->spu.dst);

	/* Create tx descriptors to submit SPU request */
	err |= pdc_tx_list_sg_add(pdcs, mssg->spu.src);
	err |= pdc_tx_list_final(pdcs);	/* initiate transfer */

	अगर (unlikely(err))
		dev_err(&pdcs->pdev->dev,
			"%s failed with error %d", __func__, err);

	वापस err;
पूर्ण

अटल पूर्णांक pdc_startup(काष्ठा mbox_chan *chan)
अणु
	वापस pdc_ring_init(chan->con_priv, PDC_RINGSET);
पूर्ण

अटल व्योम pdc_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा pdc_state *pdcs = chan->con_priv;

	अगर (!pdcs)
		वापस;

	dev_dbg(&pdcs->pdev->dev,
		"Shutdown mailbox channel for PDC %u", pdcs->pdc_idx);
	pdc_ring_मुक्त(pdcs);
पूर्ण

/**
 * pdc_hw_init() - Use the given initialization parameters to initialize the
 * state क्रम one of the PDCs.
 * @pdcs:  state of the PDC
 */
अटल
व्योम pdc_hw_init(काष्ठा pdc_state *pdcs)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device *dev;
	काष्ठा dma64 *dma_reg;
	पूर्णांक ringset = PDC_RINGSET;

	pdev = pdcs->pdev;
	dev = &pdev->dev;

	dev_dbg(dev, "PDC %u initial values:", pdcs->pdc_idx);
	dev_dbg(dev, "state structure:                   %p",
		pdcs);
	dev_dbg(dev, " - base virtual addr of hw regs    %p",
		pdcs->pdc_reg_vbase);

	/* initialize data काष्ठाures */
	pdcs->regs = (काष्ठा pdc_regs *)pdcs->pdc_reg_vbase;
	pdcs->txregs_64 = (काष्ठा dma64_regs *)
	    (((u8 *)pdcs->pdc_reg_vbase) +
		     PDC_TXREGS_OFFSET + (माप(काष्ठा dma64) * ringset));
	pdcs->rxregs_64 = (काष्ठा dma64_regs *)
	    (((u8 *)pdcs->pdc_reg_vbase) +
		     PDC_RXREGS_OFFSET + (माप(काष्ठा dma64) * ringset));

	pdcs->ntxd = PDC_RING_ENTRIES;
	pdcs->nrxd = PDC_RING_ENTRIES;
	pdcs->ntxpost = PDC_RING_ENTRIES - 1;
	pdcs->nrxpost = PDC_RING_ENTRIES - 1;
	ioग_लिखो32(0, &pdcs->regs->पूर्णांकmask);

	dma_reg = &pdcs->regs->dmaregs[ringset];

	/* Configure DMA but will enable later in pdc_ring_init() */
	ioग_लिखो32(PDC_TX_CTL, &dma_reg->dmaxmt.control);

	ioग_लिखो32(PDC_RX_CTL + (pdcs->rx_status_len << 1),
		  &dma_reg->dmarcv.control);

	/* Reset current index poपूर्णांकers after making sure DMA is disabled */
	ioग_लिखो32(0, &dma_reg->dmaxmt.ptr);
	ioग_लिखो32(0, &dma_reg->dmarcv.ptr);

	अगर (pdcs->pdc_resp_hdr_len == PDC_SPU2_RESP_HDR_LEN)
		ioग_लिखो32(PDC_CKSUM_CTRL,
			  pdcs->pdc_reg_vbase + PDC_CKSUM_CTRL_OFFSET);
पूर्ण

/**
 * pdc_hw_disable() - Disable the tx and rx control in the hw.
 * @pdcs: PDC state काष्ठाure
 *
 */
अटल व्योम pdc_hw_disable(काष्ठा pdc_state *pdcs)
अणु
	काष्ठा dma64 *dma_reg;

	dma_reg = &pdcs->regs->dmaregs[PDC_RINGSET];
	ioग_लिखो32(PDC_TX_CTL, &dma_reg->dmaxmt.control);
	ioग_लिखो32(PDC_RX_CTL + (pdcs->rx_status_len << 1),
		  &dma_reg->dmarcv.control);
पूर्ण

/**
 * pdc_rx_buf_pool_create() - Pool of receive buffers used to catch the metadata
 * header वापसed with each response message.
 * @pdcs: PDC state काष्ठाure
 *
 * The metadata is not वापसed to the mailbox client. So the PDC driver
 * manages these buffers.
 *
 * Return: PDC_SUCCESS
 *         -ENOMEM अगर pool creation fails
 */
अटल पूर्णांक pdc_rx_buf_pool_create(काष्ठा pdc_state *pdcs)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device *dev;

	pdev = pdcs->pdev;
	dev = &pdev->dev;

	pdcs->pdc_resp_hdr_len = pdcs->rx_status_len;
	अगर (pdcs->use_bcm_hdr)
		pdcs->pdc_resp_hdr_len += BCM_HDR_LEN;

	pdcs->rx_buf_pool = dma_pool_create("pdc rx bufs", dev,
					    pdcs->pdc_resp_hdr_len,
					    RX_BUF_ALIGN, 0);
	अगर (!pdcs->rx_buf_pool)
		वापस -ENOMEM;

	वापस PDC_SUCCESS;
पूर्ण

/**
 * pdc_पूर्णांकerrupts_init() - Initialize the पूर्णांकerrupt configuration क्रम a PDC and
 * specअगरy a thपढ़ोed IRQ handler क्रम deferred handling of पूर्णांकerrupts outside of
 * पूर्णांकerrupt context.
 * @pdcs:   PDC state
 *
 * Set the पूर्णांकerrupt mask क्रम transmit and receive करोne.
 * Set the lazy पूर्णांकerrupt frame count to generate an पूर्णांकerrupt क्रम just one pkt.
 *
 * Return:  PDC_SUCCESS
 *          <0 अगर thपढ़ोed irq request fails
 */
अटल पूर्णांक pdc_पूर्णांकerrupts_init(काष्ठा pdc_state *pdcs)
अणु
	काष्ठा platक्रमm_device *pdev = pdcs->pdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *dn = pdev->dev.of_node;
	पूर्णांक err;

	/* पूर्णांकerrupt configuration */
	ioग_लिखो32(PDC_INTMASK, pdcs->pdc_reg_vbase + PDC_INTMASK_OFFSET);

	अगर (pdcs->hw_type == FA_HW)
		ioग_लिखो32(PDC_LAZY_INT, pdcs->pdc_reg_vbase +
			  FA_RCVLAZY0_OFFSET);
	अन्यथा
		ioग_लिखो32(PDC_LAZY_INT, pdcs->pdc_reg_vbase +
			  PDC_RCVLAZY0_OFFSET);

	/* पढ़ो irq from device tree */
	pdcs->pdc_irq = irq_of_parse_and_map(dn, 0);
	dev_dbg(dev, "pdc device %s irq %u for pdcs %p",
		dev_name(dev), pdcs->pdc_irq, pdcs);

	err = devm_request_irq(dev, pdcs->pdc_irq, pdc_irq_handler, 0,
			       dev_name(dev), dev);
	अगर (err) अणु
		dev_err(dev, "IRQ %u request failed with err %d\n",
			pdcs->pdc_irq, err);
		वापस err;
	पूर्ण
	वापस PDC_SUCCESS;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops pdc_mbox_chan_ops = अणु
	.send_data = pdc_send_data,
	.last_tx_करोne = pdc_last_tx_करोne,
	.startup = pdc_startup,
	.shutकरोwn = pdc_shutकरोwn
पूर्ण;

/**
 * pdc_mb_init() - Initialize the mailbox controller.
 * @pdcs:  PDC state
 *
 * Each PDC is a mailbox controller. Each ringset is a mailbox channel. Kernel
 * driver only uses one ringset and thus one mb channel. PDC uses the transmit
 * complete पूर्णांकerrupt to determine when a mailbox message has successfully been
 * transmitted.
 *
 * Return: 0 on success
 *         < 0 अगर there is an allocation or registration failure
 */
अटल पूर्णांक pdc_mb_init(काष्ठा pdc_state *pdcs)
अणु
	काष्ठा device *dev = &pdcs->pdev->dev;
	काष्ठा mbox_controller *mbc;
	पूर्णांक chan_index;
	पूर्णांक err;

	mbc = &pdcs->mbc;
	mbc->dev = dev;
	mbc->ops = &pdc_mbox_chan_ops;
	mbc->num_chans = 1;
	mbc->chans = devm_kसुस्मृति(dev, mbc->num_chans, माप(*mbc->chans),
				  GFP_KERNEL);
	अगर (!mbc->chans)
		वापस -ENOMEM;

	mbc->txकरोne_irq = false;
	mbc->txकरोne_poll = true;
	mbc->txpoll_period = 1;
	क्रम (chan_index = 0; chan_index < mbc->num_chans; chan_index++)
		mbc->chans[chan_index].con_priv = pdcs;

	/* Register mailbox controller */
	err = devm_mbox_controller_रेजिस्टर(dev, mbc);
	अगर (err) अणु
		dev_crit(dev,
			 "Failed to register PDC mailbox controller. Error %d.",
			 err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* Device tree API */
अटल स्थिर पूर्णांक pdc_hw = PDC_HW;
अटल स्थिर पूर्णांक fa_hw = FA_HW;

अटल स्थिर काष्ठा of_device_id pdc_mbox_of_match[] = अणु
	अणु.compatible = "brcm,iproc-pdc-mbox", .data = &pdc_hwपूर्ण,
	अणु.compatible = "brcm,iproc-fa2-mbox", .data = &fa_hwपूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pdc_mbox_of_match);

/**
 * pdc_dt_पढ़ो() - Read application-specअगरic data from device tree.
 * @pdev:  Platक्रमm device
 * @pdcs:  PDC state
 *
 * Reads the number of bytes of receive status that precede each received frame.
 * Reads whether transmit and received frames should be preceded by an 8-byte
 * BCM header.
 *
 * Return: 0 अगर successful
 *         -ENODEV अगर device not available
 */
अटल पूर्णांक pdc_dt_पढ़ो(काष्ठा platक्रमm_device *pdev, काष्ठा pdc_state *pdcs)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *dn = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	स्थिर पूर्णांक *hw_type;
	पूर्णांक err;

	err = of_property_पढ़ो_u32(dn, "brcm,rx-status-len",
				   &pdcs->rx_status_len);
	अगर (err < 0)
		dev_err(dev,
			"%s failed to get DMA receive status length from device tree",
			__func__);

	pdcs->use_bcm_hdr = of_property_पढ़ो_bool(dn, "brcm,use-bcm-hdr");

	pdcs->hw_type = PDC_HW;

	match = of_match_device(of_match_ptr(pdc_mbox_of_match), dev);
	अगर (match != शून्य) अणु
		hw_type = match->data;
		pdcs->hw_type = *hw_type;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pdc_probe() - Probe function क्रम PDC driver.
 * @pdev:   PDC platक्रमm device
 *
 * Reserve and map रेजिस्टर regions defined in device tree.
 * Allocate and initialize tx and rx DMA rings.
 * Initialize a mailbox controller क्रम each PDC.
 *
 * Return: 0 अगर successful
 *         < 0 अगर an error
 */
अटल पूर्णांक pdc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err = 0;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *pdc_regs;
	काष्ठा pdc_state *pdcs;

	/* PDC state क्रम one SPU */
	pdcs = devm_kzalloc(dev, माप(*pdcs), GFP_KERNEL);
	अगर (!pdcs) अणु
		err = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	pdcs->pdev = pdev;
	platक्रमm_set_drvdata(pdev, pdcs);
	pdcs->pdc_idx = pdcg.num_spu;
	pdcg.num_spu++;

	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(39));
	अगर (err) अणु
		dev_warn(dev, "PDC device cannot perform DMA. Error %d.", err);
		जाओ cleanup;
	पूर्ण

	/* Create DMA pool क्रम tx ring */
	pdcs->ring_pool = dma_pool_create("pdc rings", dev, PDC_RING_SIZE,
					  RING_ALIGN, 0);
	अगर (!pdcs->ring_pool) अणु
		err = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	err = pdc_dt_पढ़ो(pdev, pdcs);
	अगर (err)
		जाओ cleanup_ring_pool;

	pdc_regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!pdc_regs) अणु
		err = -ENODEV;
		जाओ cleanup_ring_pool;
	पूर्ण
	dev_dbg(dev, "PDC register region res.start = %pa, res.end = %pa",
		&pdc_regs->start, &pdc_regs->end);

	pdcs->pdc_reg_vbase = devm_ioremap_resource(&pdev->dev, pdc_regs);
	अगर (IS_ERR(pdcs->pdc_reg_vbase)) अणु
		err = PTR_ERR(pdcs->pdc_reg_vbase);
		dev_err(&pdev->dev, "Failed to map registers: %d\n", err);
		जाओ cleanup_ring_pool;
	पूर्ण

	/* create rx buffer pool after dt पढ़ो to know how big buffers are */
	err = pdc_rx_buf_pool_create(pdcs);
	अगर (err)
		जाओ cleanup_ring_pool;

	pdc_hw_init(pdcs);

	/* Init tasklet क्रम deferred DMA rx processing */
	tasklet_setup(&pdcs->rx_tasklet, pdc_tasklet_cb);

	err = pdc_पूर्णांकerrupts_init(pdcs);
	अगर (err)
		जाओ cleanup_buf_pool;

	/* Initialize mailbox controller */
	err = pdc_mb_init(pdcs);
	अगर (err)
		जाओ cleanup_buf_pool;

	pdc_setup_debugfs(pdcs);

	dev_dbg(dev, "pdc_probe() successful");
	वापस PDC_SUCCESS;

cleanup_buf_pool:
	tasklet_समाप्त(&pdcs->rx_tasklet);
	dma_pool_destroy(pdcs->rx_buf_pool);

cleanup_ring_pool:
	dma_pool_destroy(pdcs->ring_pool);

cleanup:
	वापस err;
पूर्ण

अटल पूर्णांक pdc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pdc_state *pdcs = platक्रमm_get_drvdata(pdev);

	pdc_मुक्त_debugfs();

	tasklet_समाप्त(&pdcs->rx_tasklet);

	pdc_hw_disable(pdcs);

	dma_pool_destroy(pdcs->rx_buf_pool);
	dma_pool_destroy(pdcs->ring_pool);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pdc_mbox_driver = अणु
	.probe = pdc_probe,
	.हटाओ = pdc_हटाओ,
	.driver = अणु
		   .name = "brcm-iproc-pdc-mbox",
		   .of_match_table = of_match_ptr(pdc_mbox_of_match),
		   पूर्ण,
पूर्ण;
module_platक्रमm_driver(pdc_mbox_driver);

MODULE_AUTHOR("Rob Rice <rob.rice@broadcom.com>");
MODULE_DESCRIPTION("Broadcom PDC mailbox driver");
MODULE_LICENSE("GPL v2");
