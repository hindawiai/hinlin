<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2018-2020 Broadcom.
 */

#अगर_अघोषित BCM_VK_MSG_H
#घोषणा BCM_VK_MSG_H

#समावेश <uapi/linux/misc/bcm_vk.h>
#समावेश "bcm_vk_sg.h"

/* Single message queue control काष्ठाure */
काष्ठा bcm_vk_msgq अणु
	u16 type;	/* queue type */
	u16 num;	/* queue number */
	u32 start;	/* offset in BAR1 where the queue memory starts */

	u32 rd_idx; /* पढ़ो idx */
	u32 wr_idx; /* ग_लिखो idx */

	u32 size;	/*
			 * size, which is in number of 16byte blocks,
			 * to align with the message data काष्ठाure.
			 */
	u32 nxt;	/*
			 * nxt offset to the next msg queue काष्ठा.
			 * This is to provide flexibity क्रम alignment purposes.
			 */

/* Least signअगरicant 16 bits in below field hold करोorbell रेजिस्टर offset */
#घोषणा DB_SHIFT 16

	u32 db_offset; /* queue करोorbell रेजिस्टर offset in BAR0 */

	u32 rsvd;
पूर्ण;

/*
 * Structure to record अटल info from the msgq sync.  We keep local copy
 * क्रम some of these variables क्रम both perक्रमmance + checking purpose.
 */
काष्ठा bcm_vk_sync_qinfo अणु
	व्योम __iomem *q_start;
	u32 q_size;
	u32 q_mask;
	u32 q_low;
	u32 q_db_offset;
पूर्ण;

#घोषणा VK_MSGQ_MAX_NR 4 /* Maximum number of message queues */

/*
 * message block - basic unit in the message where a message's size is always
 *		   N x माप(basic_block)
 */
काष्ठा vk_msg_blk अणु
	u8 function_id;
#घोषणा VK_FID_TRANS_BUF	5
#घोषणा VK_FID_SHUTDOWN		8
#घोषणा VK_FID_INIT		9
	u8 size; /* size of the message in number of vk_msg_blk's */
	u16 trans_id; /* transport id, queue & msg_id */
	u32 context_id;
#घोषणा VK_NEW_CTX		0
	u32 cmd;
#घोषणा VK_CMD_PLANES_MASK	0x000f /* number of planes to up/करोwnload */
#घोषणा VK_CMD_UPLOAD		0x0400 /* memory transfer to vk */
#घोषणा VK_CMD_DOWNLOAD		0x0500 /* memory transfer from vk */
#घोषणा VK_CMD_MASK		0x0f00 /* command mask */
	u32 arg;
पूर्ण;

/* vk_msg_blk is 16 bytes fixed */
#घोषणा VK_MSGQ_BLK_SIZE   (माप(काष्ठा vk_msg_blk))
/* shअगरt क्रम fast भागision of basic msg blk size */
#घोषणा VK_MSGQ_BLK_SZ_SHIFT 4

/* use msg_id 0 क्रम any simplex host2vk communication */
#घोषणा VK_SIMPLEX_MSG_ID 0

/* context per session खोलोing of sysfs */
काष्ठा bcm_vk_ctx अणु
	काष्ठा list_head node; /* use क्रम linkage in Hash Table */
	अचिन्हित पूर्णांक idx;
	bool in_use;
	pid_t pid;
	u32 hash_idx;
	u32 q_num; /* queue number used by the stream */
	काष्ठा miscdevice *miscdev;
	atomic_t pend_cnt; /* number of items pending to be पढ़ो from host */
	atomic_t dma_cnt; /* any dma transaction outstanding */
	रुको_queue_head_t rd_wq;
पूर्ण;

/* pid hash table entry */
काष्ठा bcm_vk_ht_entry अणु
	काष्ठा list_head head;
पूर्ण;

#घोषणा VK_DMA_MAX_ADDRS 4 /* Max 4 DMA Addresses */
/* काष्ठाure क्रम house keeping a single work entry */
काष्ठा bcm_vk_wkent अणु
	काष्ठा list_head node; /* क्रम linking purpose */
	काष्ठा bcm_vk_ctx *ctx;

	/* Store up to 4 dma poपूर्णांकers */
	काष्ठा bcm_vk_dma dma[VK_DMA_MAX_ADDRS];

	u32 to_h_blks; /* response */
	काष्ठा vk_msg_blk *to_h_msg;

	/*
	 * put the to_v_msg at the end so that we could simply append to_v msg
	 * to the end of the allocated block
	 */
	u32 usr_msg_id;
	u32 to_v_blks;
	u32 seq_num;
	काष्ठा vk_msg_blk to_v_msg[0];
पूर्ण;

/* queue stats counters */
काष्ठा bcm_vk_qs_cnts अणु
	u32 cnt; /* general counter, used to limit output */
	u32 acc_sum;
	u32 max_occ; /* max during a sampling period */
	u32 max_असल; /* the असल max since reset */
पूर्ण;

/* control channel काष्ठाure क्रम either to_v or to_h communication */
काष्ठा bcm_vk_msg_chan अणु
	u32 q_nr;
	/* Mutex to access msgq */
	काष्ठा mutex msgq_mutex;
	/* poपूर्णांकing to BAR locations */
	काष्ठा bcm_vk_msgq __iomem *msgq[VK_MSGQ_MAX_NR];
	/* Spinlock to access pending queue */
	spinlock_t pendq_lock;
	/* क्रम temporary storing pending items, one क्रम each queue */
	काष्ठा list_head pendq[VK_MSGQ_MAX_NR];
	/* अटल queue info from the sync */
	काष्ठा bcm_vk_sync_qinfo sync_qinfo[VK_MSGQ_MAX_NR];
पूर्ण;

/* totol number of message q allowed by the driver */
#घोषणा VK_MSGQ_PER_CHAN_MAX	3
#घोषणा VK_MSGQ_NUM_DEFAULT	(VK_MSGQ_PER_CHAN_MAX - 1)

/* total number of supported ctx, 32 ctx each क्रम 5 components */
#घोषणा VK_CMPT_CTX_MAX		(32 * 5)

/* hash table defines to store the खोलोed FDs */
#घोषणा VK_PID_HT_SHIFT_BIT	7 /* 128 */
#घोषणा VK_PID_HT_SZ		BIT(VK_PID_HT_SHIFT_BIT)

/* The following are offsets of DDR info provided by the vk card */
#घोषणा VK_BAR0_SEG_SIZE	(4 * SZ_1K) /* segment size क्रम BAR0 */

/* shutकरोwn types supported */
#घोषणा VK_SHUTDOWN_PID		1
#घोषणा VK_SHUTDOWN_GRACEFUL	2

#पूर्ण_अगर
