<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */

/*******************************************************************************
 * Communicates with the करोngle by using dcmd codes.
 * For certain dcmd codes, the करोngle पूर्णांकerprets string data from the host.
 ******************************************************************************/

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>

#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>

#समावेश "core.h"
#समावेश "debug.h"
#समावेश "proto.h"
#समावेश "msgbuf.h"
#समावेश "commonring.h"
#समावेश "flowring.h"
#समावेश "bus.h"
#समावेश "tracepoint.h"


#घोषणा MSGBUF_IOCTL_RESP_TIMEOUT		msecs_to_jअगरfies(2000)

#घोषणा MSGBUF_TYPE_GEN_STATUS			0x1
#घोषणा MSGBUF_TYPE_RING_STATUS			0x2
#घोषणा MSGBUF_TYPE_FLOW_RING_CREATE		0x3
#घोषणा MSGBUF_TYPE_FLOW_RING_CREATE_CMPLT	0x4
#घोषणा MSGBUF_TYPE_FLOW_RING_DELETE		0x5
#घोषणा MSGBUF_TYPE_FLOW_RING_DELETE_CMPLT	0x6
#घोषणा MSGBUF_TYPE_FLOW_RING_FLUSH		0x7
#घोषणा MSGBUF_TYPE_FLOW_RING_FLUSH_CMPLT	0x8
#घोषणा MSGBUF_TYPE_IOCTLPTR_REQ		0x9
#घोषणा MSGBUF_TYPE_IOCTLPTR_REQ_ACK		0xA
#घोषणा MSGBUF_TYPE_IOCTLRESP_BUF_POST		0xB
#घोषणा MSGBUF_TYPE_IOCTL_CMPLT			0xC
#घोषणा MSGBUF_TYPE_EVENT_BUF_POST		0xD
#घोषणा MSGBUF_TYPE_WL_EVENT			0xE
#घोषणा MSGBUF_TYPE_TX_POST			0xF
#घोषणा MSGBUF_TYPE_TX_STATUS			0x10
#घोषणा MSGBUF_TYPE_RXBUF_POST			0x11
#घोषणा MSGBUF_TYPE_RX_CMPLT			0x12
#घोषणा MSGBUF_TYPE_LPBK_DMAXFER		0x13
#घोषणा MSGBUF_TYPE_LPBK_DMAXFER_CMPLT		0x14

#घोषणा NR_TX_PKTIDS				2048
#घोषणा NR_RX_PKTIDS				1024

#घोषणा BRCMF_IOCTL_REQ_PKTID			0xFFFE

#घोषणा BRCMF_MSGBUF_MAX_PKT_SIZE		2048
#घोषणा BRCMF_MSGBUF_MAX_CTL_PKT_SIZE           8192
#घोषणा BRCMF_MSGBUF_RXBUFPOST_THRESHOLD	32
#घोषणा BRCMF_MSGBUF_MAX_IOCTLRESPBUF_POST	8
#घोषणा BRCMF_MSGBUF_MAX_EVENTBUF_POST		8

#घोषणा BRCMF_MSGBUF_PKT_FLAGS_FRAME_802_3	0x01
#घोषणा BRCMF_MSGBUF_PKT_FLAGS_FRAME_802_11	0x02
#घोषणा BRCMF_MSGBUF_PKT_FLAGS_FRAME_MASK	0x07
#घोषणा BRCMF_MSGBUF_PKT_FLAGS_PRIO_SHIFT	5

#घोषणा BRCMF_MSGBUF_TX_FLUSH_CNT1		32
#घोषणा BRCMF_MSGBUF_TX_FLUSH_CNT2		96

#घोषणा BRCMF_MSGBUF_DELAY_TXWORKER_THRS	96
#घोषणा BRCMF_MSGBUF_TRICKLE_TXWORKER_THRS	32
#घोषणा BRCMF_MSGBUF_UPDATE_RX_PTR_THRS		48


काष्ठा msgbuf_common_hdr अणु
	u8				msgtype;
	u8				अगरidx;
	u8				flags;
	u8				rsvd0;
	__le32				request_id;
पूर्ण;

काष्ठा msgbuf_ioctl_req_hdr अणु
	काष्ठा msgbuf_common_hdr	msg;
	__le32				cmd;
	__le16				trans_id;
	__le16				input_buf_len;
	__le16				output_buf_len;
	__le16				rsvd0[3];
	काष्ठा msgbuf_buf_addr		req_buf_addr;
	__le32				rsvd1[2];
पूर्ण;

काष्ठा msgbuf_tx_msghdr अणु
	काष्ठा msgbuf_common_hdr	msg;
	u8				txhdr[ETH_HLEN];
	u8				flags;
	u8				seg_cnt;
	काष्ठा msgbuf_buf_addr		metadata_buf_addr;
	काष्ठा msgbuf_buf_addr		data_buf_addr;
	__le16				metadata_buf_len;
	__le16				data_len;
	__le32				rsvd0;
पूर्ण;

काष्ठा msgbuf_rx_bufpost अणु
	काष्ठा msgbuf_common_hdr	msg;
	__le16				metadata_buf_len;
	__le16				data_buf_len;
	__le32				rsvd0;
	काष्ठा msgbuf_buf_addr		metadata_buf_addr;
	काष्ठा msgbuf_buf_addr		data_buf_addr;
पूर्ण;

काष्ठा msgbuf_rx_ioctl_resp_or_event अणु
	काष्ठा msgbuf_common_hdr	msg;
	__le16				host_buf_len;
	__le16				rsvd0[3];
	काष्ठा msgbuf_buf_addr		host_buf_addr;
	__le32				rsvd1[4];
पूर्ण;

काष्ठा msgbuf_completion_hdr अणु
	__le16				status;
	__le16				flow_ring_id;
पूर्ण;

/* Data काष्ठा क्रम the MSGBUF_TYPE_GEN_STATUS */
काष्ठा msgbuf_gen_status अणु
	काष्ठा msgbuf_common_hdr	msg;
	काष्ठा msgbuf_completion_hdr	compl_hdr;
	__le16				ग_लिखो_idx;
	__le32				rsvd0[3];
पूर्ण;

/* Data काष्ठा क्रम the MSGBUF_TYPE_RING_STATUS */
काष्ठा msgbuf_ring_status अणु
	काष्ठा msgbuf_common_hdr	msg;
	काष्ठा msgbuf_completion_hdr	compl_hdr;
	__le16				ग_लिखो_idx;
	__le16				rsvd0[5];
पूर्ण;

काष्ठा msgbuf_rx_event अणु
	काष्ठा msgbuf_common_hdr	msg;
	काष्ठा msgbuf_completion_hdr	compl_hdr;
	__le16				event_data_len;
	__le16				seqnum;
	__le16				rsvd0[4];
पूर्ण;

काष्ठा msgbuf_ioctl_resp_hdr अणु
	काष्ठा msgbuf_common_hdr	msg;
	काष्ठा msgbuf_completion_hdr	compl_hdr;
	__le16				resp_len;
	__le16				trans_id;
	__le32				cmd;
	__le32				rsvd0;
पूर्ण;

काष्ठा msgbuf_tx_status अणु
	काष्ठा msgbuf_common_hdr	msg;
	काष्ठा msgbuf_completion_hdr	compl_hdr;
	__le16				metadata_len;
	__le16				tx_status;
पूर्ण;

काष्ठा msgbuf_rx_complete अणु
	काष्ठा msgbuf_common_hdr	msg;
	काष्ठा msgbuf_completion_hdr	compl_hdr;
	__le16				metadata_len;
	__le16				data_len;
	__le16				data_offset;
	__le16				flags;
	__le32				rx_status_0;
	__le32				rx_status_1;
	__le32				rsvd0;
पूर्ण;

काष्ठा msgbuf_tx_flowring_create_req अणु
	काष्ठा msgbuf_common_hdr	msg;
	u8				da[ETH_ALEN];
	u8				sa[ETH_ALEN];
	u8				tid;
	u8				अगर_flags;
	__le16				flow_ring_id;
	u8				tc;
	u8				priority;
	__le16				पूर्णांक_vector;
	__le16				max_items;
	__le16				len_item;
	काष्ठा msgbuf_buf_addr		flow_ring_addr;
पूर्ण;

काष्ठा msgbuf_tx_flowring_delete_req अणु
	काष्ठा msgbuf_common_hdr	msg;
	__le16				flow_ring_id;
	__le16				reason;
	__le32				rsvd0[7];
पूर्ण;

काष्ठा msgbuf_flowring_create_resp अणु
	काष्ठा msgbuf_common_hdr	msg;
	काष्ठा msgbuf_completion_hdr	compl_hdr;
	__le32				rsvd0[3];
पूर्ण;

काष्ठा msgbuf_flowring_delete_resp अणु
	काष्ठा msgbuf_common_hdr	msg;
	काष्ठा msgbuf_completion_hdr	compl_hdr;
	__le32				rsvd0[3];
पूर्ण;

काष्ठा msgbuf_flowring_flush_resp अणु
	काष्ठा msgbuf_common_hdr	msg;
	काष्ठा msgbuf_completion_hdr	compl_hdr;
	__le32				rsvd0[3];
पूर्ण;

काष्ठा brcmf_msgbuf_work_item अणु
	काष्ठा list_head queue;
	u32 flowid;
	पूर्णांक अगरidx;
	u8 sa[ETH_ALEN];
	u8 da[ETH_ALEN];
पूर्ण;

काष्ठा brcmf_msgbuf अणु
	काष्ठा brcmf_pub *drvr;

	काष्ठा brcmf_commonring **commonrings;
	काष्ठा brcmf_commonring **flowrings;
	dma_addr_t *flowring_dma_handle;

	u16 max_flowrings;
	u16 max_submissionrings;
	u16 max_completionrings;

	u16 rx_dataoffset;
	u32 max_rxbufpost;
	u16 rx_metadata_offset;
	u32 rxbufpost;

	u32 max_ioctlrespbuf;
	u32 cur_ioctlrespbuf;
	u32 max_eventbuf;
	u32 cur_eventbuf;

	व्योम *ioctbuf;
	dma_addr_t ioctbuf_handle;
	u32 ioctbuf_phys_hi;
	u32 ioctbuf_phys_lo;
	पूर्णांक ioctl_resp_status;
	u32 ioctl_resp_ret_len;
	u32 ioctl_resp_pktid;

	u16 data_seq_no;
	u16 ioctl_seq_no;
	u32 reqid;
	रुको_queue_head_t ioctl_resp_रुको;
	bool ctl_completed;

	काष्ठा brcmf_msgbuf_pktids *tx_pktids;
	काष्ठा brcmf_msgbuf_pktids *rx_pktids;
	काष्ठा brcmf_flowring *flow;

	काष्ठा workqueue_काष्ठा *txflow_wq;
	काष्ठा work_काष्ठा txflow_work;
	अचिन्हित दीर्घ *flow_map;
	अचिन्हित दीर्घ *txstatus_करोne_map;

	काष्ठा work_काष्ठा flowring_work;
	spinlock_t flowring_work_lock;
	काष्ठा list_head work_queue;
पूर्ण;

काष्ठा brcmf_msgbuf_pktid अणु
	atomic_t  allocated;
	u16 data_offset;
	काष्ठा sk_buff *skb;
	dma_addr_t physaddr;
पूर्ण;

काष्ठा brcmf_msgbuf_pktids अणु
	u32 array_size;
	u32 last_allocated_idx;
	क्रमागत dma_data_direction direction;
	काष्ठा brcmf_msgbuf_pktid *array;
पूर्ण;

अटल व्योम brcmf_msgbuf_rxbuf_ioctlresp_post(काष्ठा brcmf_msgbuf *msgbuf);


अटल काष्ठा brcmf_msgbuf_pktids *
brcmf_msgbuf_init_pktids(u32 nr_array_entries,
			 क्रमागत dma_data_direction direction)
अणु
	काष्ठा brcmf_msgbuf_pktid *array;
	काष्ठा brcmf_msgbuf_pktids *pktids;

	array = kसुस्मृति(nr_array_entries, माप(*array), GFP_KERNEL);
	अगर (!array)
		वापस शून्य;

	pktids = kzalloc(माप(*pktids), GFP_KERNEL);
	अगर (!pktids) अणु
		kमुक्त(array);
		वापस शून्य;
	पूर्ण
	pktids->array = array;
	pktids->array_size = nr_array_entries;

	वापस pktids;
पूर्ण


अटल पूर्णांक
brcmf_msgbuf_alloc_pktid(काष्ठा device *dev,
			 काष्ठा brcmf_msgbuf_pktids *pktids,
			 काष्ठा sk_buff *skb, u16 data_offset,
			 dma_addr_t *physaddr, u32 *idx)
अणु
	काष्ठा brcmf_msgbuf_pktid *array;
	u32 count;

	array = pktids->array;

	*physaddr = dma_map_single(dev, skb->data + data_offset,
				   skb->len - data_offset, pktids->direction);

	अगर (dma_mapping_error(dev, *physaddr)) अणु
		brcmf_err("dma_map_single failed !!\n");
		वापस -ENOMEM;
	पूर्ण

	*idx = pktids->last_allocated_idx;

	count = 0;
	करो अणु
		(*idx)++;
		अगर (*idx == pktids->array_size)
			*idx = 0;
		अगर (array[*idx].allocated.counter == 0)
			अगर (atomic_cmpxchg(&array[*idx].allocated, 0, 1) == 0)
				अवरोध;
		count++;
	पूर्ण जबतक (count < pktids->array_size);

	अगर (count == pktids->array_size)
		वापस -ENOMEM;

	array[*idx].data_offset = data_offset;
	array[*idx].physaddr = *physaddr;
	array[*idx].skb = skb;

	pktids->last_allocated_idx = *idx;

	वापस 0;
पूर्ण


अटल काष्ठा sk_buff *
brcmf_msgbuf_get_pktid(काष्ठा device *dev, काष्ठा brcmf_msgbuf_pktids *pktids,
		       u32 idx)
अणु
	काष्ठा brcmf_msgbuf_pktid *pktid;
	काष्ठा sk_buff *skb;

	अगर (idx >= pktids->array_size) अणु
		brcmf_err("Invalid packet id %d (max %d)\n", idx,
			  pktids->array_size);
		वापस शून्य;
	पूर्ण
	अगर (pktids->array[idx].allocated.counter) अणु
		pktid = &pktids->array[idx];
		dma_unmap_single(dev, pktid->physaddr,
				 pktid->skb->len - pktid->data_offset,
				 pktids->direction);
		skb = pktid->skb;
		pktid->allocated.counter = 0;
		वापस skb;
	पूर्ण अन्यथा अणु
		brcmf_err("Invalid packet id %d (not in use)\n", idx);
	पूर्ण

	वापस शून्य;
पूर्ण


अटल व्योम
brcmf_msgbuf_release_array(काष्ठा device *dev,
			   काष्ठा brcmf_msgbuf_pktids *pktids)
अणु
	काष्ठा brcmf_msgbuf_pktid *array;
	काष्ठा brcmf_msgbuf_pktid *pktid;
	u32 count;

	array = pktids->array;
	count = 0;
	करो अणु
		अगर (array[count].allocated.counter) अणु
			pktid = &array[count];
			dma_unmap_single(dev, pktid->physaddr,
					 pktid->skb->len - pktid->data_offset,
					 pktids->direction);
			brcmu_pkt_buf_मुक्त_skb(pktid->skb);
		पूर्ण
		count++;
	पूर्ण जबतक (count < pktids->array_size);

	kमुक्त(array);
	kमुक्त(pktids);
पूर्ण


अटल व्योम brcmf_msgbuf_release_pktids(काष्ठा brcmf_msgbuf *msgbuf)
अणु
	अगर (msgbuf->rx_pktids)
		brcmf_msgbuf_release_array(msgbuf->drvr->bus_अगर->dev,
					   msgbuf->rx_pktids);
	अगर (msgbuf->tx_pktids)
		brcmf_msgbuf_release_array(msgbuf->drvr->bus_अगर->dev,
					   msgbuf->tx_pktids);
पूर्ण


अटल पूर्णांक brcmf_msgbuf_tx_ioctl(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
				 uपूर्णांक cmd, व्योम *buf, uपूर्णांक len)
अणु
	काष्ठा brcmf_msgbuf *msgbuf = (काष्ठा brcmf_msgbuf *)drvr->proto->pd;
	काष्ठा brcmf_commonring *commonring;
	काष्ठा msgbuf_ioctl_req_hdr *request;
	u16 buf_len;
	व्योम *ret_ptr;
	पूर्णांक err;

	commonring = msgbuf->commonrings[BRCMF_H2D_MSGRING_CONTROL_SUBMIT];
	brcmf_commonring_lock(commonring);
	ret_ptr = brcmf_commonring_reserve_क्रम_ग_लिखो(commonring);
	अगर (!ret_ptr) अणु
		bphy_err(drvr, "Failed to reserve space in commonring\n");
		brcmf_commonring_unlock(commonring);
		वापस -ENOMEM;
	पूर्ण

	msgbuf->reqid++;

	request = (काष्ठा msgbuf_ioctl_req_hdr *)ret_ptr;
	request->msg.msgtype = MSGBUF_TYPE_IOCTLPTR_REQ;
	request->msg.अगरidx = (u8)अगरidx;
	request->msg.flags = 0;
	request->msg.request_id = cpu_to_le32(BRCMF_IOCTL_REQ_PKTID);
	request->cmd = cpu_to_le32(cmd);
	request->output_buf_len = cpu_to_le16(len);
	request->trans_id = cpu_to_le16(msgbuf->reqid);

	buf_len = min_t(u16, len, BRCMF_TX_IOCTL_MAX_MSG_SIZE);
	request->input_buf_len = cpu_to_le16(buf_len);
	request->req_buf_addr.high_addr = cpu_to_le32(msgbuf->ioctbuf_phys_hi);
	request->req_buf_addr.low_addr = cpu_to_le32(msgbuf->ioctbuf_phys_lo);
	अगर (buf)
		स_नकल(msgbuf->ioctbuf, buf, buf_len);
	अन्यथा
		स_रखो(msgbuf->ioctbuf, 0, buf_len);

	err = brcmf_commonring_ग_लिखो_complete(commonring);
	brcmf_commonring_unlock(commonring);

	वापस err;
पूर्ण


अटल पूर्णांक brcmf_msgbuf_ioctl_resp_रुको(काष्ठा brcmf_msgbuf *msgbuf)
अणु
	वापस रुको_event_समयout(msgbuf->ioctl_resp_रुको,
				  msgbuf->ctl_completed,
				  MSGBUF_IOCTL_RESP_TIMEOUT);
पूर्ण


अटल व्योम brcmf_msgbuf_ioctl_resp_wake(काष्ठा brcmf_msgbuf *msgbuf)
अणु
	msgbuf->ctl_completed = true;
	wake_up(&msgbuf->ioctl_resp_रुको);
पूर्ण


अटल पूर्णांक brcmf_msgbuf_query_dcmd(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
				   uपूर्णांक cmd, व्योम *buf, uपूर्णांक len, पूर्णांक *fwerr)
अणु
	काष्ठा brcmf_msgbuf *msgbuf = (काष्ठा brcmf_msgbuf *)drvr->proto->pd;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक समयout;
	पूर्णांक err;

	brcmf_dbg(MSGBUF, "ifidx=%d, cmd=%d, len=%d\n", अगरidx, cmd, len);
	*fwerr = 0;
	msgbuf->ctl_completed = false;
	err = brcmf_msgbuf_tx_ioctl(drvr, अगरidx, cmd, buf, len);
	अगर (err)
		वापस err;

	समयout = brcmf_msgbuf_ioctl_resp_रुको(msgbuf);
	अगर (!समयout) अणु
		bphy_err(drvr, "Timeout on response for query command\n");
		वापस -EIO;
	पूर्ण

	skb = brcmf_msgbuf_get_pktid(msgbuf->drvr->bus_अगर->dev,
				     msgbuf->rx_pktids,
				     msgbuf->ioctl_resp_pktid);
	अगर (msgbuf->ioctl_resp_ret_len != 0) अणु
		अगर (!skb)
			वापस -EBADF;

		स_नकल(buf, skb->data, (len < msgbuf->ioctl_resp_ret_len) ?
				       len : msgbuf->ioctl_resp_ret_len);
	पूर्ण
	brcmu_pkt_buf_मुक्त_skb(skb);

	*fwerr = msgbuf->ioctl_resp_status;
	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_msgbuf_set_dcmd(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
				 uपूर्णांक cmd, व्योम *buf, uपूर्णांक len, पूर्णांक *fwerr)
अणु
	वापस brcmf_msgbuf_query_dcmd(drvr, अगरidx, cmd, buf, len, fwerr);
पूर्ण


अटल पूर्णांक brcmf_msgbuf_hdrpull(काष्ठा brcmf_pub *drvr, bool करो_fws,
				काष्ठा sk_buff *skb, काष्ठा brcmf_अगर **अगरp)
अणु
	वापस -ENODEV;
पूर्ण

अटल व्योम brcmf_msgbuf_rxreorder(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *skb,
				   bool inirq)
अणु
पूर्ण

अटल व्योम
brcmf_msgbuf_हटाओ_flowring(काष्ठा brcmf_msgbuf *msgbuf, u16 flowid)
अणु
	u32 dma_sz;
	व्योम *dma_buf;

	brcmf_dbg(MSGBUF, "Removing flowring %d\n", flowid);

	dma_sz = BRCMF_H2D_TXFLOWRING_MAX_ITEM * BRCMF_H2D_TXFLOWRING_ITEMSIZE;
	dma_buf = msgbuf->flowrings[flowid]->buf_addr;
	dma_मुक्त_coherent(msgbuf->drvr->bus_अगर->dev, dma_sz, dma_buf,
			  msgbuf->flowring_dma_handle[flowid]);

	brcmf_flowring_delete(msgbuf->flow, flowid);
पूर्ण


अटल काष्ठा brcmf_msgbuf_work_item *
brcmf_msgbuf_dequeue_work(काष्ठा brcmf_msgbuf *msgbuf)
अणु
	काष्ठा brcmf_msgbuf_work_item *work = शून्य;
	uदीर्घ flags;

	spin_lock_irqsave(&msgbuf->flowring_work_lock, flags);
	अगर (!list_empty(&msgbuf->work_queue)) अणु
		work = list_first_entry(&msgbuf->work_queue,
					काष्ठा brcmf_msgbuf_work_item, queue);
		list_del(&work->queue);
	पूर्ण
	spin_unlock_irqrestore(&msgbuf->flowring_work_lock, flags);

	वापस work;
पूर्ण


अटल u32
brcmf_msgbuf_flowring_create_worker(काष्ठा brcmf_msgbuf *msgbuf,
				    काष्ठा brcmf_msgbuf_work_item *work)
अणु
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	काष्ठा msgbuf_tx_flowring_create_req *create;
	काष्ठा brcmf_commonring *commonring;
	व्योम *ret_ptr;
	u32 flowid;
	व्योम *dma_buf;
	u32 dma_sz;
	u64 address;
	पूर्णांक err;

	flowid = work->flowid;
	dma_sz = BRCMF_H2D_TXFLOWRING_MAX_ITEM * BRCMF_H2D_TXFLOWRING_ITEMSIZE;
	dma_buf = dma_alloc_coherent(msgbuf->drvr->bus_अगर->dev, dma_sz,
				     &msgbuf->flowring_dma_handle[flowid],
				     GFP_KERNEL);
	अगर (!dma_buf) अणु
		bphy_err(drvr, "dma_alloc_coherent failed\n");
		brcmf_flowring_delete(msgbuf->flow, flowid);
		वापस BRCMF_FLOWRING_INVALID_ID;
	पूर्ण

	brcmf_commonring_config(msgbuf->flowrings[flowid],
				BRCMF_H2D_TXFLOWRING_MAX_ITEM,
				BRCMF_H2D_TXFLOWRING_ITEMSIZE, dma_buf);

	commonring = msgbuf->commonrings[BRCMF_H2D_MSGRING_CONTROL_SUBMIT];
	brcmf_commonring_lock(commonring);
	ret_ptr = brcmf_commonring_reserve_क्रम_ग_लिखो(commonring);
	अगर (!ret_ptr) अणु
		bphy_err(drvr, "Failed to reserve space in commonring\n");
		brcmf_commonring_unlock(commonring);
		brcmf_msgbuf_हटाओ_flowring(msgbuf, flowid);
		वापस BRCMF_FLOWRING_INVALID_ID;
	पूर्ण

	create = (काष्ठा msgbuf_tx_flowring_create_req *)ret_ptr;
	create->msg.msgtype = MSGBUF_TYPE_FLOW_RING_CREATE;
	create->msg.अगरidx = work->अगरidx;
	create->msg.request_id = 0;
	create->tid = brcmf_flowring_tid(msgbuf->flow, flowid);
	create->flow_ring_id = cpu_to_le16(flowid +
					   BRCMF_H2D_MSGRING_FLOWRING_IDSTART);
	स_नकल(create->sa, work->sa, ETH_ALEN);
	स_नकल(create->da, work->da, ETH_ALEN);
	address = (u64)msgbuf->flowring_dma_handle[flowid];
	create->flow_ring_addr.high_addr = cpu_to_le32(address >> 32);
	create->flow_ring_addr.low_addr = cpu_to_le32(address & 0xffffffff);
	create->max_items = cpu_to_le16(BRCMF_H2D_TXFLOWRING_MAX_ITEM);
	create->len_item = cpu_to_le16(BRCMF_H2D_TXFLOWRING_ITEMSIZE);

	brcmf_dbg(MSGBUF, "Send Flow Create Req flow ID %d for peer %pM prio %d ifindex %d\n",
		  flowid, work->da, create->tid, work->अगरidx);

	err = brcmf_commonring_ग_लिखो_complete(commonring);
	brcmf_commonring_unlock(commonring);
	अगर (err) अणु
		bphy_err(drvr, "Failed to write commonring\n");
		brcmf_msgbuf_हटाओ_flowring(msgbuf, flowid);
		वापस BRCMF_FLOWRING_INVALID_ID;
	पूर्ण

	वापस flowid;
पूर्ण


अटल व्योम brcmf_msgbuf_flowring_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा brcmf_msgbuf *msgbuf;
	काष्ठा brcmf_msgbuf_work_item *create;

	msgbuf = container_of(work, काष्ठा brcmf_msgbuf, flowring_work);

	जबतक ((create = brcmf_msgbuf_dequeue_work(msgbuf))) अणु
		brcmf_msgbuf_flowring_create_worker(msgbuf, create);
		kमुक्त(create);
	पूर्ण
पूर्ण


अटल u32 brcmf_msgbuf_flowring_create(काष्ठा brcmf_msgbuf *msgbuf, पूर्णांक अगरidx,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_msgbuf_work_item *create;
	काष्ठा ethhdr *eh = (काष्ठा ethhdr *)(skb->data);
	u32 flowid;
	uदीर्घ flags;

	create = kzalloc(माप(*create), GFP_ATOMIC);
	अगर (create == शून्य)
		वापस BRCMF_FLOWRING_INVALID_ID;

	flowid = brcmf_flowring_create(msgbuf->flow, eh->h_dest,
				       skb->priority, अगरidx);
	अगर (flowid == BRCMF_FLOWRING_INVALID_ID) अणु
		kमुक्त(create);
		वापस flowid;
	पूर्ण

	create->flowid = flowid;
	create->अगरidx = अगरidx;
	स_नकल(create->sa, eh->h_source, ETH_ALEN);
	स_नकल(create->da, eh->h_dest, ETH_ALEN);

	spin_lock_irqsave(&msgbuf->flowring_work_lock, flags);
	list_add_tail(&create->queue, &msgbuf->work_queue);
	spin_unlock_irqrestore(&msgbuf->flowring_work_lock, flags);
	schedule_work(&msgbuf->flowring_work);

	वापस flowid;
पूर्ण


अटल व्योम brcmf_msgbuf_txflow(काष्ठा brcmf_msgbuf *msgbuf, u16 flowid)
अणु
	काष्ठा brcmf_flowring *flow = msgbuf->flow;
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	काष्ठा brcmf_commonring *commonring;
	व्योम *ret_ptr;
	u32 count;
	काष्ठा sk_buff *skb;
	dma_addr_t physaddr;
	u32 pktid;
	काष्ठा msgbuf_tx_msghdr *tx_msghdr;
	u64 address;

	commonring = msgbuf->flowrings[flowid];
	अगर (!brcmf_commonring_ग_लिखो_available(commonring))
		वापस;

	brcmf_commonring_lock(commonring);

	count = BRCMF_MSGBUF_TX_FLUSH_CNT2 - BRCMF_MSGBUF_TX_FLUSH_CNT1;
	जबतक (brcmf_flowring_qlen(flow, flowid)) अणु
		skb = brcmf_flowring_dequeue(flow, flowid);
		अगर (skb == शून्य) अणु
			bphy_err(drvr, "No SKB, but qlen %d\n",
				 brcmf_flowring_qlen(flow, flowid));
			अवरोध;
		पूर्ण
		skb_orphan(skb);
		अगर (brcmf_msgbuf_alloc_pktid(msgbuf->drvr->bus_अगर->dev,
					     msgbuf->tx_pktids, skb, ETH_HLEN,
					     &physaddr, &pktid)) अणु
			brcmf_flowring_reinsert(flow, flowid, skb);
			bphy_err(drvr, "No PKTID available !!\n");
			अवरोध;
		पूर्ण
		ret_ptr = brcmf_commonring_reserve_क्रम_ग_लिखो(commonring);
		अगर (!ret_ptr) अणु
			brcmf_msgbuf_get_pktid(msgbuf->drvr->bus_अगर->dev,
					       msgbuf->tx_pktids, pktid);
			brcmf_flowring_reinsert(flow, flowid, skb);
			अवरोध;
		पूर्ण
		count++;

		tx_msghdr = (काष्ठा msgbuf_tx_msghdr *)ret_ptr;

		tx_msghdr->msg.msgtype = MSGBUF_TYPE_TX_POST;
		tx_msghdr->msg.request_id = cpu_to_le32(pktid + 1);
		tx_msghdr->msg.अगरidx = brcmf_flowring_अगरidx_get(flow, flowid);
		tx_msghdr->flags = BRCMF_MSGBUF_PKT_FLAGS_FRAME_802_3;
		tx_msghdr->flags |= (skb->priority & 0x07) <<
				    BRCMF_MSGBUF_PKT_FLAGS_PRIO_SHIFT;
		tx_msghdr->seg_cnt = 1;
		स_नकल(tx_msghdr->txhdr, skb->data, ETH_HLEN);
		tx_msghdr->data_len = cpu_to_le16(skb->len - ETH_HLEN);
		address = (u64)physaddr;
		tx_msghdr->data_buf_addr.high_addr = cpu_to_le32(address >> 32);
		tx_msghdr->data_buf_addr.low_addr =
			cpu_to_le32(address & 0xffffffff);
		tx_msghdr->metadata_buf_len = 0;
		tx_msghdr->metadata_buf_addr.high_addr = 0;
		tx_msghdr->metadata_buf_addr.low_addr = 0;
		atomic_inc(&commonring->outstanding_tx);
		अगर (count >= BRCMF_MSGBUF_TX_FLUSH_CNT2) अणु
			brcmf_commonring_ग_लिखो_complete(commonring);
			count = 0;
		पूर्ण
	पूर्ण
	अगर (count)
		brcmf_commonring_ग_लिखो_complete(commonring);
	brcmf_commonring_unlock(commonring);
पूर्ण


अटल व्योम brcmf_msgbuf_txflow_worker(काष्ठा work_काष्ठा *worker)
अणु
	काष्ठा brcmf_msgbuf *msgbuf;
	u32 flowid;

	msgbuf = container_of(worker, काष्ठा brcmf_msgbuf, txflow_work);
	क्रम_each_set_bit(flowid, msgbuf->flow_map, msgbuf->max_flowrings) अणु
		clear_bit(flowid, msgbuf->flow_map);
		brcmf_msgbuf_txflow(msgbuf, flowid);
	पूर्ण
पूर्ण


अटल पूर्णांक brcmf_msgbuf_schedule_txdata(काष्ठा brcmf_msgbuf *msgbuf, u32 flowid,
					bool क्रमce)
अणु
	काष्ठा brcmf_commonring *commonring;

	set_bit(flowid, msgbuf->flow_map);
	commonring = msgbuf->flowrings[flowid];
	अगर ((क्रमce) || (atomic_पढ़ो(&commonring->outstanding_tx) <
			BRCMF_MSGBUF_DELAY_TXWORKER_THRS))
		queue_work(msgbuf->txflow_wq, &msgbuf->txflow_work);

	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_msgbuf_tx_queue_data(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_msgbuf *msgbuf = (काष्ठा brcmf_msgbuf *)drvr->proto->pd;
	काष्ठा brcmf_flowring *flow = msgbuf->flow;
	काष्ठा ethhdr *eh = (काष्ठा ethhdr *)(skb->data);
	u32 flowid;
	u32 queue_count;
	bool क्रमce;

	flowid = brcmf_flowring_lookup(flow, eh->h_dest, skb->priority, अगरidx);
	अगर (flowid == BRCMF_FLOWRING_INVALID_ID) अणु
		flowid = brcmf_msgbuf_flowring_create(msgbuf, अगरidx, skb);
		अगर (flowid == BRCMF_FLOWRING_INVALID_ID)
			वापस -ENOMEM;
	पूर्ण
	queue_count = brcmf_flowring_enqueue(flow, flowid, skb);
	क्रमce = ((queue_count % BRCMF_MSGBUF_TRICKLE_TXWORKER_THRS) == 0);
	brcmf_msgbuf_schedule_txdata(msgbuf, flowid, क्रमce);

	वापस 0;
पूर्ण


अटल व्योम
brcmf_msgbuf_configure_addr_mode(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
				 क्रमागत proto_addr_mode addr_mode)
अणु
	काष्ठा brcmf_msgbuf *msgbuf = (काष्ठा brcmf_msgbuf *)drvr->proto->pd;

	brcmf_flowring_configure_addr_mode(msgbuf->flow, अगरidx, addr_mode);
पूर्ण


अटल व्योम
brcmf_msgbuf_delete_peer(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, u8 peer[ETH_ALEN])
अणु
	काष्ठा brcmf_msgbuf *msgbuf = (काष्ठा brcmf_msgbuf *)drvr->proto->pd;

	brcmf_flowring_delete_peer(msgbuf->flow, अगरidx, peer);
पूर्ण


अटल व्योम
brcmf_msgbuf_add_tdls_peer(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, u8 peer[ETH_ALEN])
अणु
	काष्ठा brcmf_msgbuf *msgbuf = (काष्ठा brcmf_msgbuf *)drvr->proto->pd;

	brcmf_flowring_add_tdls_peer(msgbuf->flow, अगरidx, peer);
पूर्ण


अटल व्योम
brcmf_msgbuf_process_ioctl_complete(काष्ठा brcmf_msgbuf *msgbuf, व्योम *buf)
अणु
	काष्ठा msgbuf_ioctl_resp_hdr *ioctl_resp;

	ioctl_resp = (काष्ठा msgbuf_ioctl_resp_hdr *)buf;

	msgbuf->ioctl_resp_status =
			(s16)le16_to_cpu(ioctl_resp->compl_hdr.status);
	msgbuf->ioctl_resp_ret_len = le16_to_cpu(ioctl_resp->resp_len);
	msgbuf->ioctl_resp_pktid = le32_to_cpu(ioctl_resp->msg.request_id);

	brcmf_msgbuf_ioctl_resp_wake(msgbuf);

	अगर (msgbuf->cur_ioctlrespbuf)
		msgbuf->cur_ioctlrespbuf--;
	brcmf_msgbuf_rxbuf_ioctlresp_post(msgbuf);
पूर्ण


अटल व्योम
brcmf_msgbuf_process_txstatus(काष्ठा brcmf_msgbuf *msgbuf, व्योम *buf)
अणु
	काष्ठा brcmf_commonring *commonring;
	काष्ठा msgbuf_tx_status *tx_status;
	u32 idx;
	काष्ठा sk_buff *skb;
	u16 flowid;

	tx_status = (काष्ठा msgbuf_tx_status *)buf;
	idx = le32_to_cpu(tx_status->msg.request_id) - 1;
	flowid = le16_to_cpu(tx_status->compl_hdr.flow_ring_id);
	flowid -= BRCMF_H2D_MSGRING_FLOWRING_IDSTART;
	skb = brcmf_msgbuf_get_pktid(msgbuf->drvr->bus_अगर->dev,
				     msgbuf->tx_pktids, idx);
	अगर (!skb)
		वापस;

	set_bit(flowid, msgbuf->txstatus_करोne_map);
	commonring = msgbuf->flowrings[flowid];
	atomic_dec(&commonring->outstanding_tx);

	brcmf_txfinalize(brcmf_get_अगरp(msgbuf->drvr, tx_status->msg.अगरidx),
			 skb, true);
पूर्ण


अटल u32 brcmf_msgbuf_rxbuf_data_post(काष्ठा brcmf_msgbuf *msgbuf, u32 count)
अणु
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	काष्ठा brcmf_commonring *commonring;
	व्योम *ret_ptr;
	काष्ठा sk_buff *skb;
	u16 alloced;
	u32 pktlen;
	dma_addr_t physaddr;
	काष्ठा msgbuf_rx_bufpost *rx_bufpost;
	u64 address;
	u32 pktid;
	u32 i;

	commonring = msgbuf->commonrings[BRCMF_H2D_MSGRING_RXPOST_SUBMIT];
	ret_ptr = brcmf_commonring_reserve_क्रम_ग_लिखो_multiple(commonring,
							      count,
							      &alloced);
	अगर (!ret_ptr) अणु
		brcmf_dbg(MSGBUF, "Failed to reserve space in commonring\n");
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < alloced; i++) अणु
		rx_bufpost = (काष्ठा msgbuf_rx_bufpost *)ret_ptr;
		स_रखो(rx_bufpost, 0, माप(*rx_bufpost));

		skb = brcmu_pkt_buf_get_skb(BRCMF_MSGBUF_MAX_PKT_SIZE);

		अगर (skb == शून्य) अणु
			bphy_err(drvr, "Failed to alloc SKB\n");
			brcmf_commonring_ग_लिखो_cancel(commonring, alloced - i);
			अवरोध;
		पूर्ण

		pktlen = skb->len;
		अगर (brcmf_msgbuf_alloc_pktid(msgbuf->drvr->bus_अगर->dev,
					     msgbuf->rx_pktids, skb, 0,
					     &physaddr, &pktid)) अणु
			dev_kमुक्त_skb_any(skb);
			bphy_err(drvr, "No PKTID available !!\n");
			brcmf_commonring_ग_लिखो_cancel(commonring, alloced - i);
			अवरोध;
		पूर्ण

		अगर (msgbuf->rx_metadata_offset) अणु
			address = (u64)physaddr;
			rx_bufpost->metadata_buf_len =
				cpu_to_le16(msgbuf->rx_metadata_offset);
			rx_bufpost->metadata_buf_addr.high_addr =
				cpu_to_le32(address >> 32);
			rx_bufpost->metadata_buf_addr.low_addr =
				cpu_to_le32(address & 0xffffffff);

			skb_pull(skb, msgbuf->rx_metadata_offset);
			pktlen = skb->len;
			physaddr += msgbuf->rx_metadata_offset;
		पूर्ण
		rx_bufpost->msg.msgtype = MSGBUF_TYPE_RXBUF_POST;
		rx_bufpost->msg.request_id = cpu_to_le32(pktid);

		address = (u64)physaddr;
		rx_bufpost->data_buf_len = cpu_to_le16((u16)pktlen);
		rx_bufpost->data_buf_addr.high_addr =
			cpu_to_le32(address >> 32);
		rx_bufpost->data_buf_addr.low_addr =
			cpu_to_le32(address & 0xffffffff);

		ret_ptr += brcmf_commonring_len_item(commonring);
	पूर्ण

	अगर (i)
		brcmf_commonring_ग_लिखो_complete(commonring);

	वापस i;
पूर्ण


अटल व्योम
brcmf_msgbuf_rxbuf_data_fill(काष्ठा brcmf_msgbuf *msgbuf)
अणु
	u32 fillbufs;
	u32 retcount;

	fillbufs = msgbuf->max_rxbufpost - msgbuf->rxbufpost;

	जबतक (fillbufs) अणु
		retcount = brcmf_msgbuf_rxbuf_data_post(msgbuf, fillbufs);
		अगर (!retcount)
			अवरोध;
		msgbuf->rxbufpost += retcount;
		fillbufs -= retcount;
	पूर्ण
पूर्ण


अटल व्योम
brcmf_msgbuf_update_rxbufpost_count(काष्ठा brcmf_msgbuf *msgbuf, u16 rxcnt)
अणु
	msgbuf->rxbufpost -= rxcnt;
	अगर (msgbuf->rxbufpost <= (msgbuf->max_rxbufpost -
				  BRCMF_MSGBUF_RXBUFPOST_THRESHOLD))
		brcmf_msgbuf_rxbuf_data_fill(msgbuf);
पूर्ण


अटल u32
brcmf_msgbuf_rxbuf_ctrl_post(काष्ठा brcmf_msgbuf *msgbuf, bool event_buf,
			     u32 count)
अणु
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	काष्ठा brcmf_commonring *commonring;
	व्योम *ret_ptr;
	काष्ठा sk_buff *skb;
	u16 alloced;
	u32 pktlen;
	dma_addr_t physaddr;
	काष्ठा msgbuf_rx_ioctl_resp_or_event *rx_bufpost;
	u64 address;
	u32 pktid;
	u32 i;

	commonring = msgbuf->commonrings[BRCMF_H2D_MSGRING_CONTROL_SUBMIT];
	brcmf_commonring_lock(commonring);
	ret_ptr = brcmf_commonring_reserve_क्रम_ग_लिखो_multiple(commonring,
							      count,
							      &alloced);
	अगर (!ret_ptr) अणु
		bphy_err(drvr, "Failed to reserve space in commonring\n");
		brcmf_commonring_unlock(commonring);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < alloced; i++) अणु
		rx_bufpost = (काष्ठा msgbuf_rx_ioctl_resp_or_event *)ret_ptr;
		स_रखो(rx_bufpost, 0, माप(*rx_bufpost));

		skb = brcmu_pkt_buf_get_skb(BRCMF_MSGBUF_MAX_CTL_PKT_SIZE);

		अगर (skb == शून्य) अणु
			bphy_err(drvr, "Failed to alloc SKB\n");
			brcmf_commonring_ग_लिखो_cancel(commonring, alloced - i);
			अवरोध;
		पूर्ण

		pktlen = skb->len;
		अगर (brcmf_msgbuf_alloc_pktid(msgbuf->drvr->bus_अगर->dev,
					     msgbuf->rx_pktids, skb, 0,
					     &physaddr, &pktid)) अणु
			dev_kमुक्त_skb_any(skb);
			bphy_err(drvr, "No PKTID available !!\n");
			brcmf_commonring_ग_लिखो_cancel(commonring, alloced - i);
			अवरोध;
		पूर्ण
		अगर (event_buf)
			rx_bufpost->msg.msgtype = MSGBUF_TYPE_EVENT_BUF_POST;
		अन्यथा
			rx_bufpost->msg.msgtype =
				MSGBUF_TYPE_IOCTLRESP_BUF_POST;
		rx_bufpost->msg.request_id = cpu_to_le32(pktid);

		address = (u64)physaddr;
		rx_bufpost->host_buf_len = cpu_to_le16((u16)pktlen);
		rx_bufpost->host_buf_addr.high_addr =
			cpu_to_le32(address >> 32);
		rx_bufpost->host_buf_addr.low_addr =
			cpu_to_le32(address & 0xffffffff);

		ret_ptr += brcmf_commonring_len_item(commonring);
	पूर्ण

	अगर (i)
		brcmf_commonring_ग_लिखो_complete(commonring);

	brcmf_commonring_unlock(commonring);

	वापस i;
पूर्ण


अटल व्योम brcmf_msgbuf_rxbuf_ioctlresp_post(काष्ठा brcmf_msgbuf *msgbuf)
अणु
	u32 count;

	count = msgbuf->max_ioctlrespbuf - msgbuf->cur_ioctlrespbuf;
	count = brcmf_msgbuf_rxbuf_ctrl_post(msgbuf, false, count);
	msgbuf->cur_ioctlrespbuf += count;
पूर्ण


अटल व्योम brcmf_msgbuf_rxbuf_event_post(काष्ठा brcmf_msgbuf *msgbuf)
अणु
	u32 count;

	count = msgbuf->max_eventbuf - msgbuf->cur_eventbuf;
	count = brcmf_msgbuf_rxbuf_ctrl_post(msgbuf, true, count);
	msgbuf->cur_eventbuf += count;
पूर्ण


अटल व्योम brcmf_msgbuf_process_event(काष्ठा brcmf_msgbuf *msgbuf, व्योम *buf)
अणु
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	काष्ठा msgbuf_rx_event *event;
	u32 idx;
	u16 buflen;
	काष्ठा sk_buff *skb;
	काष्ठा brcmf_अगर *अगरp;

	event = (काष्ठा msgbuf_rx_event *)buf;
	idx = le32_to_cpu(event->msg.request_id);
	buflen = le16_to_cpu(event->event_data_len);

	अगर (msgbuf->cur_eventbuf)
		msgbuf->cur_eventbuf--;
	brcmf_msgbuf_rxbuf_event_post(msgbuf);

	skb = brcmf_msgbuf_get_pktid(msgbuf->drvr->bus_अगर->dev,
				     msgbuf->rx_pktids, idx);
	अगर (!skb)
		वापस;

	अगर (msgbuf->rx_dataoffset)
		skb_pull(skb, msgbuf->rx_dataoffset);

	skb_trim(skb, buflen);

	अगरp = brcmf_get_अगरp(msgbuf->drvr, event->msg.अगरidx);
	अगर (!अगरp || !अगरp->ndev) अणु
		bphy_err(drvr, "Received pkt for invalid ifidx %d\n",
			 event->msg.अगरidx);
		जाओ निकास;
	पूर्ण

	skb->protocol = eth_type_trans(skb, अगरp->ndev);

	brcmf_fweh_process_skb(अगरp->drvr, skb, 0, GFP_KERNEL);

निकास:
	brcmu_pkt_buf_मुक्त_skb(skb);
पूर्ण


अटल व्योम
brcmf_msgbuf_process_rx_complete(काष्ठा brcmf_msgbuf *msgbuf, व्योम *buf)
अणु
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	काष्ठा msgbuf_rx_complete *rx_complete;
	काष्ठा sk_buff *skb;
	u16 data_offset;
	u16 buflen;
	u16 flags;
	u32 idx;
	काष्ठा brcmf_अगर *अगरp;

	brcmf_msgbuf_update_rxbufpost_count(msgbuf, 1);

	rx_complete = (काष्ठा msgbuf_rx_complete *)buf;
	data_offset = le16_to_cpu(rx_complete->data_offset);
	buflen = le16_to_cpu(rx_complete->data_len);
	idx = le32_to_cpu(rx_complete->msg.request_id);
	flags = le16_to_cpu(rx_complete->flags);

	skb = brcmf_msgbuf_get_pktid(msgbuf->drvr->bus_अगर->dev,
				     msgbuf->rx_pktids, idx);
	अगर (!skb)
		वापस;

	अगर (data_offset)
		skb_pull(skb, data_offset);
	अन्यथा अगर (msgbuf->rx_dataoffset)
		skb_pull(skb, msgbuf->rx_dataoffset);

	skb_trim(skb, buflen);

	अगर ((flags & BRCMF_MSGBUF_PKT_FLAGS_FRAME_MASK) ==
	    BRCMF_MSGBUF_PKT_FLAGS_FRAME_802_11) अणु
		अगरp = msgbuf->drvr->mon_अगर;

		अगर (!अगरp) अणु
			bphy_err(drvr, "Received unexpected monitor pkt\n");
			brcmu_pkt_buf_मुक्त_skb(skb);
			वापस;
		पूर्ण

		brcmf_netअगर_mon_rx(अगरp, skb);
		वापस;
	पूर्ण

	अगरp = brcmf_get_अगरp(msgbuf->drvr, rx_complete->msg.अगरidx);
	अगर (!अगरp || !अगरp->ndev) अणु
		bphy_err(drvr, "Received pkt for invalid ifidx %d\n",
			 rx_complete->msg.अगरidx);
		brcmu_pkt_buf_मुक्त_skb(skb);
		वापस;
	पूर्ण

	skb->protocol = eth_type_trans(skb, अगरp->ndev);
	brcmf_netअगर_rx(अगरp, skb, false);
पूर्ण

अटल व्योम brcmf_msgbuf_process_gen_status(काष्ठा brcmf_msgbuf *msgbuf,
					    व्योम *buf)
अणु
	काष्ठा msgbuf_gen_status *gen_status = buf;
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	पूर्णांक err;

	err = le16_to_cpu(gen_status->compl_hdr.status);
	अगर (err)
		bphy_err(drvr, "Firmware reported general error: %d\n", err);
पूर्ण

अटल व्योम brcmf_msgbuf_process_ring_status(काष्ठा brcmf_msgbuf *msgbuf,
					     व्योम *buf)
अणु
	काष्ठा msgbuf_ring_status *ring_status = buf;
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	पूर्णांक err;

	err = le16_to_cpu(ring_status->compl_hdr.status);
	अगर (err) अणु
		पूर्णांक ring = le16_to_cpu(ring_status->compl_hdr.flow_ring_id);

		bphy_err(drvr, "Firmware reported ring %d error: %d\n", ring,
			 err);
	पूर्ण
पूर्ण

अटल व्योम
brcmf_msgbuf_process_flow_ring_create_response(काष्ठा brcmf_msgbuf *msgbuf,
					       व्योम *buf)
अणु
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	काष्ठा msgbuf_flowring_create_resp *flowring_create_resp;
	u16 status;
	u16 flowid;

	flowring_create_resp = (काष्ठा msgbuf_flowring_create_resp *)buf;

	flowid = le16_to_cpu(flowring_create_resp->compl_hdr.flow_ring_id);
	flowid -= BRCMF_H2D_MSGRING_FLOWRING_IDSTART;
	status =  le16_to_cpu(flowring_create_resp->compl_hdr.status);

	अगर (status) अणु
		bphy_err(drvr, "Flowring creation failed, code %d\n", status);
		brcmf_msgbuf_हटाओ_flowring(msgbuf, flowid);
		वापस;
	पूर्ण
	brcmf_dbg(MSGBUF, "Flowring %d Create response status %d\n", flowid,
		  status);

	brcmf_flowring_खोलो(msgbuf->flow, flowid);

	brcmf_msgbuf_schedule_txdata(msgbuf, flowid, true);
पूर्ण


अटल व्योम
brcmf_msgbuf_process_flow_ring_delete_response(काष्ठा brcmf_msgbuf *msgbuf,
					       व्योम *buf)
अणु
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	काष्ठा msgbuf_flowring_delete_resp *flowring_delete_resp;
	u16 status;
	u16 flowid;

	flowring_delete_resp = (काष्ठा msgbuf_flowring_delete_resp *)buf;

	flowid = le16_to_cpu(flowring_delete_resp->compl_hdr.flow_ring_id);
	flowid -= BRCMF_H2D_MSGRING_FLOWRING_IDSTART;
	status =  le16_to_cpu(flowring_delete_resp->compl_hdr.status);

	अगर (status) अणु
		bphy_err(drvr, "Flowring deletion failed, code %d\n", status);
		brcmf_flowring_delete(msgbuf->flow, flowid);
		वापस;
	पूर्ण
	brcmf_dbg(MSGBUF, "Flowring %d Delete response status %d\n", flowid,
		  status);

	brcmf_msgbuf_हटाओ_flowring(msgbuf, flowid);
पूर्ण


अटल व्योम brcmf_msgbuf_process_msgtype(काष्ठा brcmf_msgbuf *msgbuf, व्योम *buf)
अणु
	काष्ठा brcmf_pub *drvr = msgbuf->drvr;
	काष्ठा msgbuf_common_hdr *msg;

	msg = (काष्ठा msgbuf_common_hdr *)buf;
	चयन (msg->msgtype) अणु
	हाल MSGBUF_TYPE_GEN_STATUS:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_GEN_STATUS\n");
		brcmf_msgbuf_process_gen_status(msgbuf, buf);
		अवरोध;
	हाल MSGBUF_TYPE_RING_STATUS:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_RING_STATUS\n");
		brcmf_msgbuf_process_ring_status(msgbuf, buf);
		अवरोध;
	हाल MSGBUF_TYPE_FLOW_RING_CREATE_CMPLT:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_FLOW_RING_CREATE_CMPLT\n");
		brcmf_msgbuf_process_flow_ring_create_response(msgbuf, buf);
		अवरोध;
	हाल MSGBUF_TYPE_FLOW_RING_DELETE_CMPLT:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_FLOW_RING_DELETE_CMPLT\n");
		brcmf_msgbuf_process_flow_ring_delete_response(msgbuf, buf);
		अवरोध;
	हाल MSGBUF_TYPE_IOCTLPTR_REQ_ACK:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_IOCTLPTR_REQ_ACK\n");
		अवरोध;
	हाल MSGBUF_TYPE_IOCTL_CMPLT:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_IOCTL_CMPLT\n");
		brcmf_msgbuf_process_ioctl_complete(msgbuf, buf);
		अवरोध;
	हाल MSGBUF_TYPE_WL_EVENT:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_WL_EVENT\n");
		brcmf_msgbuf_process_event(msgbuf, buf);
		अवरोध;
	हाल MSGBUF_TYPE_TX_STATUS:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_TX_STATUS\n");
		brcmf_msgbuf_process_txstatus(msgbuf, buf);
		अवरोध;
	हाल MSGBUF_TYPE_RX_CMPLT:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_RX_CMPLT\n");
		brcmf_msgbuf_process_rx_complete(msgbuf, buf);
		अवरोध;
	शेष:
		bphy_err(drvr, "Unsupported msgtype %d\n", msg->msgtype);
		अवरोध;
	पूर्ण
पूर्ण


अटल व्योम brcmf_msgbuf_process_rx(काष्ठा brcmf_msgbuf *msgbuf,
				    काष्ठा brcmf_commonring *commonring)
अणु
	व्योम *buf;
	u16 count;
	u16 processed;

again:
	buf = brcmf_commonring_get_पढ़ो_ptr(commonring, &count);
	अगर (buf == शून्य)
		वापस;

	processed = 0;
	जबतक (count) अणु
		brcmf_msgbuf_process_msgtype(msgbuf,
					     buf + msgbuf->rx_dataoffset);
		buf += brcmf_commonring_len_item(commonring);
		processed++;
		अगर (processed == BRCMF_MSGBUF_UPDATE_RX_PTR_THRS) अणु
			brcmf_commonring_पढ़ो_complete(commonring, processed);
			processed = 0;
		पूर्ण
		count--;
	पूर्ण
	अगर (processed)
		brcmf_commonring_पढ़ो_complete(commonring, processed);

	अगर (commonring->r_ptr == 0)
		जाओ again;
पूर्ण


पूर्णांक brcmf_proto_msgbuf_rx_trigger(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;
	काष्ठा brcmf_msgbuf *msgbuf = (काष्ठा brcmf_msgbuf *)drvr->proto->pd;
	काष्ठा brcmf_commonring *commonring;
	व्योम *buf;
	u32 flowid;
	पूर्णांक qlen;

	buf = msgbuf->commonrings[BRCMF_D2H_MSGRING_RX_COMPLETE];
	brcmf_msgbuf_process_rx(msgbuf, buf);
	buf = msgbuf->commonrings[BRCMF_D2H_MSGRING_TX_COMPLETE];
	brcmf_msgbuf_process_rx(msgbuf, buf);
	buf = msgbuf->commonrings[BRCMF_D2H_MSGRING_CONTROL_COMPLETE];
	brcmf_msgbuf_process_rx(msgbuf, buf);

	क्रम_each_set_bit(flowid, msgbuf->txstatus_करोne_map,
			 msgbuf->max_flowrings) अणु
		clear_bit(flowid, msgbuf->txstatus_करोne_map);
		commonring = msgbuf->flowrings[flowid];
		qlen = brcmf_flowring_qlen(msgbuf->flow, flowid);
		अगर ((qlen > BRCMF_MSGBUF_TRICKLE_TXWORKER_THRS) ||
		    ((qlen) && (atomic_पढ़ो(&commonring->outstanding_tx) <
				BRCMF_MSGBUF_TRICKLE_TXWORKER_THRS)))
			brcmf_msgbuf_schedule_txdata(msgbuf, flowid, true);
	पूर्ण

	वापस 0;
पूर्ण


व्योम brcmf_msgbuf_delete_flowring(काष्ठा brcmf_pub *drvr, u16 flowid)
अणु
	काष्ठा brcmf_msgbuf *msgbuf = (काष्ठा brcmf_msgbuf *)drvr->proto->pd;
	काष्ठा msgbuf_tx_flowring_delete_req *delete;
	काष्ठा brcmf_commonring *commonring;
	व्योम *ret_ptr;
	u8 अगरidx;
	पूर्णांक err;

	/* no need to submit अगर firmware can not be reached */
	अगर (drvr->bus_अगर->state != BRCMF_BUS_UP) अणु
		brcmf_dbg(MSGBUF, "bus down, flowring will be removed\n");
		brcmf_msgbuf_हटाओ_flowring(msgbuf, flowid);
		वापस;
	पूर्ण

	commonring = msgbuf->commonrings[BRCMF_H2D_MSGRING_CONTROL_SUBMIT];
	brcmf_commonring_lock(commonring);
	ret_ptr = brcmf_commonring_reserve_क्रम_ग_लिखो(commonring);
	अगर (!ret_ptr) अणु
		bphy_err(drvr, "FW unaware, flowring will be removed !!\n");
		brcmf_commonring_unlock(commonring);
		brcmf_msgbuf_हटाओ_flowring(msgbuf, flowid);
		वापस;
	पूर्ण

	delete = (काष्ठा msgbuf_tx_flowring_delete_req *)ret_ptr;

	अगरidx = brcmf_flowring_अगरidx_get(msgbuf->flow, flowid);

	delete->msg.msgtype = MSGBUF_TYPE_FLOW_RING_DELETE;
	delete->msg.अगरidx = अगरidx;
	delete->msg.request_id = 0;

	delete->flow_ring_id = cpu_to_le16(flowid +
					   BRCMF_H2D_MSGRING_FLOWRING_IDSTART);
	delete->reason = 0;

	brcmf_dbg(MSGBUF, "Send Flow Delete Req flow ID %d, ifindex %d\n",
		  flowid, अगरidx);

	err = brcmf_commonring_ग_लिखो_complete(commonring);
	brcmf_commonring_unlock(commonring);
	अगर (err) अणु
		bphy_err(drvr, "Failed to submit RING_DELETE, flowring will be removed\n");
		brcmf_msgbuf_हटाओ_flowring(msgbuf, flowid);
	पूर्ण
पूर्ण

#अगर_घोषित DEBUG
अटल पूर्णांक brcmf_msgbuf_stats_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(seq->निजी);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;
	काष्ठा brcmf_msgbuf *msgbuf = (काष्ठा brcmf_msgbuf *)drvr->proto->pd;
	काष्ठा brcmf_commonring *commonring;
	u16 i;
	काष्ठा brcmf_flowring_ring *ring;
	काष्ठा brcmf_flowring_hash *hash;

	commonring = msgbuf->commonrings[BRCMF_H2D_MSGRING_CONTROL_SUBMIT];
	seq_म_लिखो(seq, "h2d_ctl_submit: rp %4u, wp %4u, depth %4u\n",
		   commonring->r_ptr, commonring->w_ptr, commonring->depth);
	commonring = msgbuf->commonrings[BRCMF_H2D_MSGRING_RXPOST_SUBMIT];
	seq_म_लिखो(seq, "h2d_rx_submit:  rp %4u, wp %4u, depth %4u\n",
		   commonring->r_ptr, commonring->w_ptr, commonring->depth);
	commonring = msgbuf->commonrings[BRCMF_D2H_MSGRING_CONTROL_COMPLETE];
	seq_म_लिखो(seq, "d2h_ctl_cmplt:  rp %4u, wp %4u, depth %4u\n",
		   commonring->r_ptr, commonring->w_ptr, commonring->depth);
	commonring = msgbuf->commonrings[BRCMF_D2H_MSGRING_TX_COMPLETE];
	seq_म_लिखो(seq, "d2h_tx_cmplt:   rp %4u, wp %4u, depth %4u\n",
		   commonring->r_ptr, commonring->w_ptr, commonring->depth);
	commonring = msgbuf->commonrings[BRCMF_D2H_MSGRING_RX_COMPLETE];
	seq_म_लिखो(seq, "d2h_rx_cmplt:   rp %4u, wp %4u, depth %4u\n",
		   commonring->r_ptr, commonring->w_ptr, commonring->depth);

	seq_म_लिखो(seq, "\nh2d_flowrings: depth %u\n",
		   BRCMF_H2D_TXFLOWRING_MAX_ITEM);
	seq_माला_दो(seq, "Active flowrings:\n");
	क्रम (i = 0; i < msgbuf->flow->nrofrings; i++) अणु
		अगर (!msgbuf->flow->rings[i])
			जारी;
		ring = msgbuf->flow->rings[i];
		अगर (ring->status != RING_OPEN)
			जारी;
		commonring = msgbuf->flowrings[i];
		hash = &msgbuf->flow->hash[ring->hash_id];
		seq_म_लिखो(seq, "id %3u: rp %4u, wp %4u, qlen %4u, blocked %u\n"
				"        ifidx %u, fifo %u, da %pM\n",
				i, commonring->r_ptr, commonring->w_ptr,
				skb_queue_len(&ring->skblist), ring->blocked,
				hash->अगरidx, hash->fअगरo, hash->mac);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक brcmf_msgbuf_stats_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम brcmf_msgbuf_debugfs_create(काष्ठा brcmf_pub *drvr)
अणु
	brcmf_debugfs_add_entry(drvr, "msgbuf_stats", brcmf_msgbuf_stats_पढ़ो);
पूर्ण

पूर्णांक brcmf_proto_msgbuf_attach(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_bus_msgbuf *अगर_msgbuf;
	काष्ठा brcmf_msgbuf *msgbuf;
	u64 address;
	u32 count;

	अगर_msgbuf = drvr->bus_अगर->msgbuf;

	अगर (अगर_msgbuf->max_flowrings >= BRCMF_FLOWRING_HASHSIZE) अणु
		bphy_err(drvr, "driver not configured for this many flowrings %d\n",
			 अगर_msgbuf->max_flowrings);
		अगर_msgbuf->max_flowrings = BRCMF_FLOWRING_HASHSIZE - 1;
	पूर्ण

	msgbuf = kzalloc(माप(*msgbuf), GFP_KERNEL);
	अगर (!msgbuf)
		जाओ fail;

	msgbuf->txflow_wq = create_singlethपढ़ो_workqueue("msgbuf_txflow");
	अगर (msgbuf->txflow_wq == शून्य) अणु
		bphy_err(drvr, "workqueue creation failed\n");
		जाओ fail;
	पूर्ण
	INIT_WORK(&msgbuf->txflow_work, brcmf_msgbuf_txflow_worker);
	count = BITS_TO_LONGS(अगर_msgbuf->max_flowrings);
	count = count * माप(अचिन्हित दीर्घ);
	msgbuf->flow_map = kzalloc(count, GFP_KERNEL);
	अगर (!msgbuf->flow_map)
		जाओ fail;

	msgbuf->txstatus_करोne_map = kzalloc(count, GFP_KERNEL);
	अगर (!msgbuf->txstatus_करोne_map)
		जाओ fail;

	msgbuf->drvr = drvr;
	msgbuf->ioctbuf = dma_alloc_coherent(drvr->bus_अगर->dev,
					     BRCMF_TX_IOCTL_MAX_MSG_SIZE,
					     &msgbuf->ioctbuf_handle,
					     GFP_KERNEL);
	अगर (!msgbuf->ioctbuf)
		जाओ fail;
	address = (u64)msgbuf->ioctbuf_handle;
	msgbuf->ioctbuf_phys_hi = address >> 32;
	msgbuf->ioctbuf_phys_lo = address & 0xffffffff;

	drvr->proto->hdrpull = brcmf_msgbuf_hdrpull;
	drvr->proto->query_dcmd = brcmf_msgbuf_query_dcmd;
	drvr->proto->set_dcmd = brcmf_msgbuf_set_dcmd;
	drvr->proto->tx_queue_data = brcmf_msgbuf_tx_queue_data;
	drvr->proto->configure_addr_mode = brcmf_msgbuf_configure_addr_mode;
	drvr->proto->delete_peer = brcmf_msgbuf_delete_peer;
	drvr->proto->add_tdls_peer = brcmf_msgbuf_add_tdls_peer;
	drvr->proto->rxreorder = brcmf_msgbuf_rxreorder;
	drvr->proto->debugfs_create = brcmf_msgbuf_debugfs_create;
	drvr->proto->pd = msgbuf;

	init_रुकोqueue_head(&msgbuf->ioctl_resp_रुको);

	msgbuf->commonrings =
		(काष्ठा brcmf_commonring **)अगर_msgbuf->commonrings;
	msgbuf->flowrings = (काष्ठा brcmf_commonring **)अगर_msgbuf->flowrings;
	msgbuf->max_flowrings = अगर_msgbuf->max_flowrings;
	msgbuf->flowring_dma_handle =
		kसुस्मृति(msgbuf->max_flowrings,
			माप(*msgbuf->flowring_dma_handle), GFP_KERNEL);
	अगर (!msgbuf->flowring_dma_handle)
		जाओ fail;

	msgbuf->rx_dataoffset = अगर_msgbuf->rx_dataoffset;
	msgbuf->max_rxbufpost = अगर_msgbuf->max_rxbufpost;

	msgbuf->max_ioctlrespbuf = BRCMF_MSGBUF_MAX_IOCTLRESPBUF_POST;
	msgbuf->max_eventbuf = BRCMF_MSGBUF_MAX_EVENTBUF_POST;

	msgbuf->tx_pktids = brcmf_msgbuf_init_pktids(NR_TX_PKTIDS,
						     DMA_TO_DEVICE);
	अगर (!msgbuf->tx_pktids)
		जाओ fail;
	msgbuf->rx_pktids = brcmf_msgbuf_init_pktids(NR_RX_PKTIDS,
						     DMA_FROM_DEVICE);
	अगर (!msgbuf->rx_pktids)
		जाओ fail;

	msgbuf->flow = brcmf_flowring_attach(drvr->bus_अगर->dev,
					     अगर_msgbuf->max_flowrings);
	अगर (!msgbuf->flow)
		जाओ fail;


	brcmf_dbg(MSGBUF, "Feeding buffers, rx data %d, rx event %d, rx ioctl resp %d\n",
		  msgbuf->max_rxbufpost, msgbuf->max_eventbuf,
		  msgbuf->max_ioctlrespbuf);
	count = 0;
	करो अणु
		brcmf_msgbuf_rxbuf_data_fill(msgbuf);
		अगर (msgbuf->max_rxbufpost != msgbuf->rxbufpost)
			msleep(10);
		अन्यथा
			अवरोध;
		count++;
	पूर्ण जबतक (count < 10);
	brcmf_msgbuf_rxbuf_event_post(msgbuf);
	brcmf_msgbuf_rxbuf_ioctlresp_post(msgbuf);

	INIT_WORK(&msgbuf->flowring_work, brcmf_msgbuf_flowring_worker);
	spin_lock_init(&msgbuf->flowring_work_lock);
	INIT_LIST_HEAD(&msgbuf->work_queue);

	वापस 0;

fail:
	अगर (msgbuf) अणु
		kमुक्त(msgbuf->flow_map);
		kमुक्त(msgbuf->txstatus_करोne_map);
		brcmf_msgbuf_release_pktids(msgbuf);
		kमुक्त(msgbuf->flowring_dma_handle);
		अगर (msgbuf->ioctbuf)
			dma_मुक्त_coherent(drvr->bus_अगर->dev,
					  BRCMF_TX_IOCTL_MAX_MSG_SIZE,
					  msgbuf->ioctbuf,
					  msgbuf->ioctbuf_handle);
		अगर (msgbuf->txflow_wq)
			destroy_workqueue(msgbuf->txflow_wq);
		kमुक्त(msgbuf);
	पूर्ण
	वापस -ENOMEM;
पूर्ण


व्योम brcmf_proto_msgbuf_detach(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_msgbuf *msgbuf;
	काष्ठा brcmf_msgbuf_work_item *work;

	brcmf_dbg(TRACE, "Enter\n");
	अगर (drvr->proto->pd) अणु
		msgbuf = (काष्ठा brcmf_msgbuf *)drvr->proto->pd;
		cancel_work_sync(&msgbuf->flowring_work);
		जबतक (!list_empty(&msgbuf->work_queue)) अणु
			work = list_first_entry(&msgbuf->work_queue,
						काष्ठा brcmf_msgbuf_work_item,
						queue);
			list_del(&work->queue);
			kमुक्त(work);
		पूर्ण
		kमुक्त(msgbuf->flow_map);
		kमुक्त(msgbuf->txstatus_करोne_map);
		अगर (msgbuf->txflow_wq)
			destroy_workqueue(msgbuf->txflow_wq);

		brcmf_flowring_detach(msgbuf->flow);
		dma_मुक्त_coherent(drvr->bus_अगर->dev,
				  BRCMF_TX_IOCTL_MAX_MSG_SIZE,
				  msgbuf->ioctbuf, msgbuf->ioctbuf_handle);
		brcmf_msgbuf_release_pktids(msgbuf);
		kमुक्त(msgbuf->flowring_dma_handle);
		kमुक्त(msgbuf);
		drvr->proto->pd = शून्य;
	पूर्ण
पूर्ण
