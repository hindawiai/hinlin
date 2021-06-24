<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
/*!  \पile  octeon_iq.h
 *   \मrief Host Driver: Implementation of Octeon input queues. "Input" is
 *   with respect to the Octeon device on the NIC. From this driver's
 *   poपूर्णांक of view they are egress queues.
 */

#अगर_अघोषित __OCTEON_IQ_H__
#घोषणा  __OCTEON_IQ_H__

#घोषणा IQ_STATUS_RUNNING   1

#घोषणा IQ_SEND_OK          0
#घोषणा IQ_SEND_STOP        1
#घोषणा IQ_SEND_FAILED     -1

/*-------------------------  INSTRUCTION QUEUE --------------------------*/

/* \cond */

#घोषणा REQTYPE_NONE                 0
#घोषणा REQTYPE_NORESP_NET           1
#घोषणा REQTYPE_NORESP_NET_SG        2
#घोषणा REQTYPE_RESP_NET             3
#घोषणा REQTYPE_RESP_NET_SG          4
#घोषणा REQTYPE_SOFT_COMMAND         5
#घोषणा REQTYPE_LAST                 5

काष्ठा octeon_request_list अणु
	u32 reqtype;
	व्योम *buf;
पूर्ण;

/* \endcond */

/** Input Queue statistics. Each input queue has four stats fields. */
काष्ठा oct_iq_stats अणु
	u64 instr_posted; /**< Inकाष्ठाions posted to this queue. */
	u64 instr_processed; /**< Inकाष्ठाions processed in this queue. */
	u64 instr_dropped; /**< Inकाष्ठाions that could not be processed */
	u64 bytes_sent;  /**< Bytes sent through this queue. */
	u64 sgentry_sent;/**< Gather entries sent through this queue. */
	u64 tx_करोne;/**< Num of packets sent to network. */
	u64 tx_iq_busy;/**< Numof बार this iq was found to be full. */
	u64 tx_dropped;/**< Numof pkts dropped dueto xmitpath errors. */
	u64 tx_tot_bytes;/**< Total count of bytes sento to network. */
	u64 tx_gso;  /* count of tso */
	u64 tx_vxlan; /* tunnel */
	u64 tx_dmamap_fail; /* Number of बार dma mapping failed */
	u64 tx_restart; /* Number of बार this queue restarted */
पूर्ण;

#घोषणा OCT_IQ_STATS_SIZE   (माप(काष्ठा oct_iq_stats))

/** The inकाष्ठाion (input) queue.
 *  The input queue is used to post raw (inकाष्ठाion) mode data or packet
 *  data to Octeon device from the host. Each input queue (upto 4) क्रम
 *  a Octeon device has one such काष्ठाure to represent it.
 */
काष्ठा octeon_instr_queue अणु
	काष्ठा octeon_device *oct_dev;

	/** A spinlock to protect access to the input ring.  */
	spinlock_t lock;

	/** A spinlock to protect जबतक posting on the ring.  */
	spinlock_t post_lock;

	/** This flag indicates अगर the queue can be used क्रम soft commands.
	 *  If this flag is set, post_lock must be acquired beक्रमe posting
	 *  a command to the queue.
	 *  If this flag is clear, post_lock is invalid क्रम the queue.
	 *  All control commands (soft commands) will go through only Queue 0
	 *  (control and data queue). So only queue-0 needs post_lock,
	 *  other queues are only data queues and करोes not need post_lock
	 */
	bool allow_soft_cmds;

	u32 pkt_in_करोne;

	u32 pkts_processed;

	/** A spinlock to protect access to the input ring.*/
	spinlock_t iq_flush_running_lock;

	/** Flag that indicates अगर the queue uses 64 byte commands. */
	u32 iqcmd_64B:1;

	/** Queue info. */
	जोड़ oct_txpciq txpciq;

	u32 rsvd:17;

	/* Controls whether extra flushing of IQ is करोne on Tx */
	u32 करो_स्वतः_flush:1;

	u32 status:8;

	/** Maximum no. of inकाष्ठाions in this queue. */
	u32 max_count;

	/** Index in input ring where the driver should ग_लिखो the next packet */
	u32 host_ग_लिखो_index;

	/** Index in input ring where Octeon is expected to पढ़ो the next
	 * packet.
	 */
	u32 octeon_पढ़ो_index;

	/** This index aids in finding the winकरोw in the queue where Octeon
	 *  has पढ़ो the commands.
	 */
	u32 flush_index;

	/** This field keeps track of the inकाष्ठाions pending in this queue. */
	atomic_t instr_pending;

	u32 reset_instr_cnt;

	/** Poपूर्णांकer to the Virtual Base addr of the input ring. */
	u8 *base_addr;

	काष्ठा octeon_request_list *request_list;

	/** Octeon करोorbell रेजिस्टर क्रम the ring. */
	व्योम __iomem *करोorbell_reg;

	/** Octeon inकाष्ठाion count रेजिस्टर क्रम this ring. */
	व्योम __iomem *inst_cnt_reg;

	/** Number of inकाष्ठाions pending to be posted to Octeon. */
	u32 fill_cnt;

	/** The max. number of inकाष्ठाions that can be held pending by the
	 * driver.
	 */
	u32 fill_threshold;

	/** The last समय that the करोorbell was rung. */
	u64 last_db_समय;

	/** The करोorbell समयout. If the करोorbell was not rung क्रम this समय and
	 * fill_cnt is non-zero, ring the करोorbell again.
	 */
	u32 db_समयout;

	/** Statistics क्रम this input queue. */
	काष्ठा oct_iq_stats stats;

	/** DMA mapped base address of the input descriptor ring. */
	dma_addr_t base_addr_dma;

	/** Application context */
	व्योम *app_ctx;

	/* network stack queue index */
	पूर्णांक q_index;

	/*os अगरidx associated with this queue */
	पूर्णांक अगरidx;

पूर्ण;

/*----------------------  INSTRUCTION FORMAT ----------------------------*/

/** 32-byte inकाष्ठाion क्रमmat.
 *  Format of inकाष्ठाion क्रम a 32-byte mode input queue.
 */
काष्ठा octeon_instr_32B अणु
	/** Poपूर्णांकer where the input data is available. */
	u64 dptr;

	/** Inकाष्ठाion Header.  */
	u64 ih;

	/** Poपूर्णांकer where the response क्रम a RAW mode packet will be written
	 * by Octeon.
	 */
	u64 rptr;

	/** Input Request Header. Additional info about the input. */
	u64 irh;

पूर्ण;

#घोषणा OCT_32B_INSTR_SIZE     (माप(काष्ठा octeon_instr_32B))

/** 64-byte inकाष्ठाion क्रमmat.
 *  Format of inकाष्ठाion क्रम a 64-byte mode input queue.
 */
काष्ठा octeon_instr2_64B अणु
	/** Poपूर्णांकer where the input data is available. */
	u64 dptr;

	/** Inकाष्ठाion Header. */
	u64 ih2;

	/** Input Request Header. */
	u64 irh;

	/** opcode/subcode specअगरic parameters */
	u64 ossp[2];

	/** Return Data Parameters */
	u64 rdp;

	/** Poपूर्णांकer where the response क्रम a RAW mode packet will be written
	 * by Octeon.
	 */
	u64 rptr;

	u64 reserved;
पूर्ण;

काष्ठा octeon_instr3_64B अणु
	/** Poपूर्णांकer where the input data is available. */
	u64 dptr;

	/** Inकाष्ठाion Header. */
	u64 ih3;

	/** Inकाष्ठाion Header. */
	u64 pki_ih3;

	/** Input Request Header. */
	u64 irh;

	/** opcode/subcode specअगरic parameters */
	u64 ossp[2];

	/** Return Data Parameters */
	u64 rdp;

	/** Poपूर्णांकer where the response क्रम a RAW mode packet will be written
	 * by Octeon.
	 */
	u64 rptr;

पूर्ण;

जोड़ octeon_instr_64B अणु
	काष्ठा octeon_instr2_64B cmd2;
	काष्ठा octeon_instr3_64B cmd3;
पूर्ण;

#घोषणा OCT_64B_INSTR_SIZE     (माप(जोड़ octeon_instr_64B))

/** The size of each buffer in soft command buffer pool
 */
#घोषणा  SOFT_COMMAND_BUFFER_SIZE	2048

काष्ठा octeon_soft_command अणु
	/** Soft command buffer info. */
	काष्ठा list_head node;
	u64 dma_addr;
	u32 size;

	/** Command and वापस status */
	जोड़ octeon_instr_64B cmd;

#घोषणा COMPLETION_WORD_INIT    0xffffffffffffffffULL
	u64 *status_word;

	/** Data buffer info */
	व्योम *virtdptr;
	u64 dmadptr;
	u32 datasize;

	/** Return buffer info */
	व्योम *virtrptr;
	u64 dmarptr;
	u32 rdatasize;

	/** Context buffer info */
	व्योम *ctxptr;
	u32  ctxsize;

	/** Time out and callback */
	माप_प्रकार expiry_समय;
	u32 iq_no;
	व्योम (*callback)(काष्ठा octeon_device *, u32, व्योम *);
	व्योम *callback_arg;

	पूर्णांक caller_is_करोne;
	u32 sc_status;
	काष्ठा completion complete;
पूर्ण;

/* max समयout (in milli sec) क्रम soft request */
#घोषणा LIO_SC_MAX_TMO_MS       60000

/** Maximum number of buffers to allocate पूर्णांकo soft command buffer pool
 */
#घोषणा  MAX_SOFT_COMMAND_BUFFERS	256

/** Head of a soft command buffer pool.
 */
काष्ठा octeon_sc_buffer_pool अणु
	/** List काष्ठाure to add delete pending entries to */
	काष्ठा list_head head;

	/** A lock क्रम this response list */
	spinlock_t lock;

	atomic_t alloc_buf_count;
पूर्ण;

#घोषणा INCR_INSTRQUEUE_PKT_COUNT(octeon_dev_ptr, iq_no, field, count)  \
		(((octeon_dev_ptr)->instr_queue[iq_no]->stats.field) += count)

पूर्णांक octeon_setup_sc_buffer_pool(काष्ठा octeon_device *oct);
पूर्णांक octeon_मुक्त_sc_करोne_list(काष्ठा octeon_device *oct);
पूर्णांक octeon_मुक्त_sc_zombie_list(काष्ठा octeon_device *oct);
पूर्णांक octeon_मुक्त_sc_buffer_pool(काष्ठा octeon_device *oct);
काष्ठा octeon_soft_command *
	octeon_alloc_soft_command(काष्ठा octeon_device *oct,
				  u32 datasize, u32 rdatasize,
				  u32 ctxsize);
व्योम octeon_मुक्त_soft_command(काष्ठा octeon_device *oct,
			      काष्ठा octeon_soft_command *sc);

/**
 *  octeon_init_instr_queue()
 *  @param octeon_dev      - poपूर्णांकer to the octeon device काष्ठाure.
 *  @param txpciq          - queue to be initialized (0 <= q_no <= 3).
 *
 *  Called at driver init समय क्रम each input queue. iq_conf has the
 *  configuration parameters क्रम the queue.
 *
 *  @वापस  Success: 0   Failure: 1
 */
पूर्णांक octeon_init_instr_queue(काष्ठा octeon_device *octeon_dev,
			    जोड़ oct_txpciq txpciq,
			    u32 num_descs);

/**
 *  octeon_delete_instr_queue()
 *  @param octeon_dev      - poपूर्णांकer to the octeon device काष्ठाure.
 *  @param iq_no           - queue to be deleted (0 <= q_no <= 3).
 *
 *  Called at driver unload समय क्रम each input queue. Deletes all
 *  allocated resources क्रम the input queue.
 *
 *  @वापस  Success: 0   Failure: 1
 */
पूर्णांक octeon_delete_instr_queue(काष्ठा octeon_device *octeon_dev, u32 iq_no);

पूर्णांक lio_रुको_क्रम_instr_fetch(काष्ठा octeon_device *oct);

व्योम
octeon_ring_करोorbell_locked(काष्ठा octeon_device *oct, u32 iq_no);

पूर्णांक
octeon_रेजिस्टर_reqtype_मुक्त_fn(काष्ठा octeon_device *oct, पूर्णांक reqtype,
				व्योम (*fn)(व्योम *));

पूर्णांक
lio_process_iq_request_list(काष्ठा octeon_device *oct,
			    काष्ठा octeon_instr_queue *iq, u32 napi_budget);

पूर्णांक octeon_send_command(काष्ठा octeon_device *oct, u32 iq_no,
			u32 क्रमce_db, व्योम *cmd, व्योम *buf,
			u32 datasize, u32 reqtype);

व्योम octeon_dump_soft_command(काष्ठा octeon_device *oct,
			      काष्ठा octeon_soft_command *sc);

व्योम octeon_prepare_soft_command(काष्ठा octeon_device *oct,
				 काष्ठा octeon_soft_command *sc,
				 u8 opcode, u8 subcode,
				 u32 irh_ossp, u64 ossp0,
				 u64 ossp1);

पूर्णांक octeon_send_soft_command(काष्ठा octeon_device *oct,
			     काष्ठा octeon_soft_command *sc);

पूर्णांक octeon_setup_iq(काष्ठा octeon_device *oct, पूर्णांक अगरidx,
		    पूर्णांक q_index, जोड़ oct_txpciq iq_no, u32 num_descs,
		    व्योम *app_ctx);
पूर्णांक
octeon_flush_iq(काष्ठा octeon_device *oct, काष्ठा octeon_instr_queue *iq,
		u32 napi_budget);
#पूर्ण_अगर				/* __OCTEON_IQ_H__ */
