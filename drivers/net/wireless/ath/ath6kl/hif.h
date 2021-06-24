<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित HIF_H
#घोषणा HIF_H

#समावेश "common.h"
#समावेश "core.h"

#समावेश <linux/scatterlist.h>

#घोषणा BUS_REQUEST_MAX_NUM                64
#घोषणा HIF_MBOX_BLOCK_SIZE                128
#घोषणा HIF_MBOX0_BLOCK_SIZE               1

#घोषणा HIF_DMA_BUFFER_SIZE (32 * 1024)
#घोषणा CMD53_FIXED_ADDRESS 1
#घोषणा CMD53_INCR_ADDRESS  2

#घोषणा MAX_SCATTER_REQUESTS             4
#घोषणा MAX_SCATTER_ENTRIES_PER_REQ      16
#घोषणा MAX_SCATTER_REQ_TRANSFER_SIZE    (32 * 1024)

/* Mailbox address in SDIO address space */
#घोषणा HIF_MBOX_BASE_ADDR                 0x800
#घोषणा HIF_MBOX_WIDTH                     0x800

#घोषणा HIF_MBOX_END_ADDR  (HTC_MAILBOX_NUM_MAX * HIF_MBOX_WIDTH - 1)

/* version 1 of the chip has only a 12K extended mbox range */
#घोषणा HIF_MBOX0_EXT_BASE_ADDR  0x4000
#घोषणा HIF_MBOX0_EXT_WIDTH      (12*1024)

/* GMBOX addresses */
#घोषणा HIF_GMBOX_BASE_ADDR                0x7000
#घोषणा HIF_GMBOX_WIDTH                    0x4000

/* पूर्णांकerrupt mode रेजिस्टर */
#घोषणा CCCR_SDIO_IRQ_MODE_REG         0xF0

/* mode to enable special 4-bit पूर्णांकerrupt निश्चितion without घड़ी */
#घोषणा SDIO_IRQ_MODE_ASYNC_4BIT_IRQ   (1 << 0)

/* HTC runs over mailbox 0 */
#घोषणा HTC_MAILBOX	0

#घोषणा ATH6KL_TARGET_DEBUG_INTR_MASK     0x01

/* FIXME: are these duplicates with MAX_SCATTER_ values in hअगर.h? */
#घोषणा ATH6KL_SCATTER_ENTRIES_PER_REQ            16
#घोषणा ATH6KL_MAX_TRANSFER_SIZE_PER_SCATTER      (16 * 1024)
#घोषणा ATH6KL_SCATTER_REQS                       4

#घोषणा ATH6KL_HIF_COMMUNICATION_TIMEOUT	1000

काष्ठा bus_request अणु
	काष्ठा list_head list;

	/* request data */
	u32 address;

	u8 *buffer;
	u32 length;
	u32 request;
	काष्ठा htc_packet *packet;
	पूर्णांक status;

	/* this is a scatter request */
	काष्ठा hअगर_scatter_req *scat_req;
पूर्ण;

/* direction of transfer (पढ़ो/ग_लिखो) */
#घोषणा HIF_READ                    0x00000001
#घोषणा HIF_WRITE                   0x00000002
#घोषणा HIF_सूची_MASK                (HIF_READ | HIF_WRITE)

/*
 *     emode - This indicates the whether the command is to be executed in a
 *             blocking or non-blocking fashion (HIF_SYNCHRONOUS/
 *             HIF_ASYNCHRONOUS). The पढ़ो/ग_लिखो data paths in HTC have been
 *             implemented using the asynchronous mode allowing the the bus
 *             driver to indicate the completion of operation through the
 *             रेजिस्टरed callback routine. The requirement primarily comes
 *             from the contexts these operations get called from (a driver's
 *             transmit context or the ISR context in हाल of receive).
 *             Support क्रम both of these modes is essential.
 */
#घोषणा HIF_SYNCHRONOUS             0x00000010
#घोषणा HIF_ASYNCHRONOUS            0x00000020
#घोषणा HIF_EMODE_MASK              (HIF_SYNCHRONOUS | HIF_ASYNCHRONOUS)

/*
 *     dmode - An पूर्णांकerface may support dअगरferent kinds of commands based on
 *             the tradeoff between the amount of data it can carry and the
 *             setup समय. Byte and Block modes are supported (HIF_BYTE_BASIS/
 *             HIF_BLOCK_BASIS). In हाल of latter, the data is rounded off
 *             to the nearest block size by padding. The size of the block is
 *             configurable at compile समय using the HIF_BLOCK_SIZE and is
 *             negotiated with the target during initialization after the
 *             ATH6KL पूर्णांकerrupts are enabled.
 */
#घोषणा HIF_BYTE_BASIS              0x00000040
#घोषणा HIF_BLOCK_BASIS             0x00000080
#घोषणा HIF_DMODE_MASK              (HIF_BYTE_BASIS | HIF_BLOCK_BASIS)

/*
 *     amode - This indicates अगर the address has to be incremented on ATH6KL
 *             after every पढ़ो/ग_लिखो operation (HIF?FIXED_ADDRESS/
 *             HIF_INCREMENTAL_ADDRESS).
 */
#घोषणा HIF_FIXED_ADDRESS           0x00000100
#घोषणा HIF_INCREMENTAL_ADDRESS     0x00000200
#घोषणा HIF_AMODE_MASK		  (HIF_FIXED_ADDRESS | HIF_INCREMENTAL_ADDRESS)

#घोषणा HIF_WR_ASYNC_BYTE_INC					\
	(HIF_WRITE | HIF_ASYNCHRONOUS |				\
	 HIF_BYTE_BASIS | HIF_INCREMENTAL_ADDRESS)

#घोषणा HIF_WR_ASYNC_BLOCK_INC					\
	(HIF_WRITE | HIF_ASYNCHRONOUS |				\
	 HIF_BLOCK_BASIS | HIF_INCREMENTAL_ADDRESS)

#घोषणा HIF_WR_SYNC_BYTE_FIX					\
	(HIF_WRITE | HIF_SYNCHRONOUS |				\
	 HIF_BYTE_BASIS | HIF_FIXED_ADDRESS)

#घोषणा HIF_WR_SYNC_BYTE_INC					\
	(HIF_WRITE | HIF_SYNCHRONOUS |				\
	 HIF_BYTE_BASIS | HIF_INCREMENTAL_ADDRESS)

#घोषणा HIF_WR_SYNC_BLOCK_INC					\
	(HIF_WRITE | HIF_SYNCHRONOUS |				\
	 HIF_BLOCK_BASIS | HIF_INCREMENTAL_ADDRESS)

#घोषणा HIF_RD_SYNC_BYTE_INC						\
	(HIF_READ | HIF_SYNCHRONOUS |					\
	 HIF_BYTE_BASIS | HIF_INCREMENTAL_ADDRESS)

#घोषणा HIF_RD_SYNC_BYTE_FIX						\
	(HIF_READ | HIF_SYNCHRONOUS |					\
	 HIF_BYTE_BASIS | HIF_FIXED_ADDRESS)

#घोषणा HIF_RD_ASYNC_BLOCK_FIX						\
	(HIF_READ | HIF_ASYNCHRONOUS |					\
	 HIF_BLOCK_BASIS | HIF_FIXED_ADDRESS)

#घोषणा HIF_RD_SYNC_BLOCK_FIX						\
	(HIF_READ | HIF_SYNCHRONOUS |					\
	 HIF_BLOCK_BASIS | HIF_FIXED_ADDRESS)

काष्ठा hअगर_scatter_item अणु
	u8 *buf;
	पूर्णांक len;
	काष्ठा htc_packet *packet;
पूर्ण;

काष्ठा hअगर_scatter_req अणु
	काष्ठा list_head list;
	/* address क्रम the पढ़ो/ग_लिखो operation */
	u32 addr;

	/* request flags */
	u32 req;

	/* total length of entire transfer */
	u32 len;

	bool virt_scat;

	व्योम (*complete) (काष्ठा htc_target *, काष्ठा hअगर_scatter_req *);
	पूर्णांक status;
	पूर्णांक scat_entries;

	काष्ठा bus_request *busrequest;
	काष्ठा scatterlist *sgentries;

	/* bounce buffer क्रम upper layers to copy to/from */
	u8 *virt_dma_buf;

	u32 scat_q_depth;

	काष्ठा hअगर_scatter_item scat_list[];
पूर्ण;

काष्ठा ath6kl_irq_proc_रेजिस्टरs अणु
	u8 host_पूर्णांक_status;
	u8 cpu_पूर्णांक_status;
	u8 error_पूर्णांक_status;
	u8 counter_पूर्णांक_status;
	u8 mbox_frame;
	u8 rx_lkahd_valid;
	u8 host_पूर्णांक_status2;
	u8 gmbox_rx_avail;
	__le32 rx_lkahd[2];
	__le32 rx_gmbox_lkahd_alias[2];
पूर्ण __packed;

काष्ठा ath6kl_irq_enable_reg अणु
	u8 पूर्णांक_status_en;
	u8 cpu_पूर्णांक_status_en;
	u8 err_पूर्णांक_status_en;
	u8 cntr_पूर्णांक_status_en;
पूर्ण __packed;

काष्ठा ath6kl_device अणु
	/* protects irq_proc_reg and irq_en_reg below */
	spinlock_t lock;
	काष्ठा ath6kl_irq_proc_रेजिस्टरs irq_proc_reg;
	काष्ठा ath6kl_irq_enable_reg irq_en_reg;
	काष्ठा htc_target *htc_cnxt;
	काष्ठा ath6kl *ar;
पूर्ण;

काष्ठा ath6kl_hअगर_ops अणु
	पूर्णांक (*पढ़ो_ग_लिखो_sync)(काष्ठा ath6kl *ar, u32 addr, u8 *buf,
			       u32 len, u32 request);
	पूर्णांक (*ग_लिखो_async)(काष्ठा ath6kl *ar, u32 address, u8 *buffer,
			   u32 length, u32 request, काष्ठा htc_packet *packet);

	व्योम (*irq_enable)(काष्ठा ath6kl *ar);
	व्योम (*irq_disable)(काष्ठा ath6kl *ar);

	काष्ठा hअगर_scatter_req *(*scatter_req_get)(काष्ठा ath6kl *ar);
	व्योम (*scatter_req_add)(काष्ठा ath6kl *ar,
				काष्ठा hअगर_scatter_req *s_req);
	पूर्णांक (*enable_scatter)(काष्ठा ath6kl *ar);
	पूर्णांक (*scat_req_rw) (काष्ठा ath6kl *ar,
			    काष्ठा hअगर_scatter_req *scat_req);
	व्योम (*cleanup_scatter)(काष्ठा ath6kl *ar);
	पूर्णांक (*suspend)(काष्ठा ath6kl *ar, काष्ठा cfg80211_wowlan *wow);
	पूर्णांक (*resume)(काष्ठा ath6kl *ar);
	पूर्णांक (*diag_पढ़ो32)(काष्ठा ath6kl *ar, u32 address, u32 *value);
	पूर्णांक (*diag_ग_लिखो32)(काष्ठा ath6kl *ar, u32 address, __le32 value);
	पूर्णांक (*bmi_पढ़ो)(काष्ठा ath6kl *ar, u8 *buf, u32 len);
	पूर्णांक (*bmi_ग_लिखो)(काष्ठा ath6kl *ar, u8 *buf, u32 len);
	पूर्णांक (*घातer_on)(काष्ठा ath6kl *ar);
	पूर्णांक (*घातer_off)(काष्ठा ath6kl *ar);
	व्योम (*stop)(काष्ठा ath6kl *ar);
	पूर्णांक (*pipe_send)(काष्ठा ath6kl *ar, u8 pipe, काष्ठा sk_buff *hdr_buf,
			 काष्ठा sk_buff *buf);
	व्योम (*pipe_get_शेष)(काष्ठा ath6kl *ar, u8 *pipe_ul, u8 *pipe_dl);
	पूर्णांक (*pipe_map_service)(काष्ठा ath6kl *ar, u16 service_id, u8 *pipe_ul,
				u8 *pipe_dl);
	u16 (*pipe_get_मुक्त_queue_number)(काष्ठा ath6kl *ar, u8 pipe);
पूर्ण;

पूर्णांक ath6kl_hअगर_setup(काष्ठा ath6kl_device *dev);
पूर्णांक ath6kl_hअगर_unmask_पूर्णांकrs(काष्ठा ath6kl_device *dev);
पूर्णांक ath6kl_hअगर_mask_पूर्णांकrs(काष्ठा ath6kl_device *dev);
पूर्णांक ath6kl_hअगर_poll_mboxmsg_rx(काष्ठा ath6kl_device *dev,
			       u32 *lk_ahd, पूर्णांक समयout);
पूर्णांक ath6kl_hअगर_rx_control(काष्ठा ath6kl_device *dev, bool enable_rx);
पूर्णांक ath6kl_hअगर_disable_पूर्णांकrs(काष्ठा ath6kl_device *dev);

पूर्णांक ath6kl_hअगर_rw_comp_handler(व्योम *context, पूर्णांक status);
पूर्णांक ath6kl_hअगर_पूर्णांकr_bh_handler(काष्ठा ath6kl *ar);

/* Scatter Function and Definitions */
पूर्णांक ath6kl_hअगर_submit_scat_req(काष्ठा ath6kl_device *dev,
			       काष्ठा hअगर_scatter_req *scat_req, bool पढ़ो);

#पूर्ण_अगर
