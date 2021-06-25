<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ISHTP client logic
 *
 * Copyright (c) 2003-2016, Intel Corporation.
 */

#अगर_अघोषित _ISHTP_CLIENT_H_
#घोषणा _ISHTP_CLIENT_H_

#समावेश <linux/types.h>
#समावेश "ishtp-dev.h"

/* Tx and Rx ring size */
#घोषणा	CL_DEF_RX_RING_SIZE	2
#घोषणा	CL_DEF_TX_RING_SIZE	2
#घोषणा	CL_MAX_RX_RING_SIZE	32
#घोषणा	CL_MAX_TX_RING_SIZE	32

#घोषणा DMA_SLOT_SIZE		4096
/* Number of IPC fragments after which it's worth sending via DMA */
#घोषणा	DMA_WORTH_THRESHOLD	3

/* DMA/IPC Tx paths. Other the शेष means enक्रमcement */
#घोषणा	CL_TX_PATH_DEFAULT	0
#घोषणा	CL_TX_PATH_IPC		1
#घोषणा	CL_TX_PATH_DMA		2

/* Client Tx buffer list entry */
काष्ठा ishtp_cl_tx_ring अणु
	काष्ठा list_head	list;
	काष्ठा ishtp_msg_data	send_buf;
पूर्ण;

/* ISHTP client instance */
काष्ठा ishtp_cl अणु
	काष्ठा list_head	link;
	काष्ठा ishtp_device	*dev;
	क्रमागत cl_state		state;
	पूर्णांक			status;

	/* Link to ISHTP bus device */
	काष्ठा ishtp_cl_device	*device;

	/* ID of client connected */
	uपूर्णांक8_t	host_client_id;
	uपूर्णांक8_t	fw_client_id;
	uपूर्णांक8_t	ishtp_flow_ctrl_creds;
	uपूर्णांक8_t	out_flow_ctrl_creds;

	/* dma */
	पूर्णांक	last_tx_path;
	/* 0: ack wasn't received,1:ack was received */
	पूर्णांक	last_dma_acked;
	अचिन्हित अक्षर	*last_dma_addr;
	/* 0: ack wasn't received,1:ack was received */
	पूर्णांक	last_ipc_acked;

	/* Rx ring buffer pool */
	अचिन्हित पूर्णांक	rx_ring_size;
	काष्ठा ishtp_cl_rb	मुक्त_rb_list;
	spinlock_t	मुक्त_list_spinlock;
	/* Rx in-process list */
	काष्ठा ishtp_cl_rb	in_process_list;
	spinlock_t	in_process_spinlock;

	/* Client Tx buffers list */
	अचिन्हित पूर्णांक	tx_ring_size;
	काष्ठा ishtp_cl_tx_ring	tx_list, tx_मुक्त_list;
	पूर्णांक		tx_ring_मुक्त_size;
	spinlock_t	tx_list_spinlock;
	spinlock_t	tx_मुक्त_list_spinlock;
	माप_प्रकार	tx_offs;	/* Offset in buffer at head of 'tx_list' */

	/**
	 * अगर we get a FC, and the list is not empty, we must know whether we
	 * are at the middle of sending.
	 * अगर so -need to increase FC counter, otherwise, need to start sending
	 * the first msg in list
	 * (!)This is क्रम counting-FC implementation only. Within single-FC the
	 * other party may NOT send FC until it receives complete message
	 */
	पूर्णांक	sending;

	/* Send FC spinlock */
	spinlock_t	fc_spinlock;

	/* रुको queue क्रम connect and disconnect response from FW */
	रुको_queue_head_t	रुको_ctrl_res;

	/* Error stats */
	अचिन्हित पूर्णांक	err_send_msg;
	अचिन्हित पूर्णांक	err_send_fc;

	/* Send/recv stats */
	अचिन्हित पूर्णांक	send_msg_cnt_ipc;
	अचिन्हित पूर्णांक	send_msg_cnt_dma;
	अचिन्हित पूर्णांक	recv_msg_cnt_ipc;
	अचिन्हित पूर्णांक	recv_msg_cnt_dma;
	अचिन्हित पूर्णांक	recv_msg_num_frags;
	अचिन्हित पूर्णांक	ishtp_flow_ctrl_cnt;
	अचिन्हित पूर्णांक	out_flow_ctrl_cnt;

	/* Rx msg ... out FC timing */
	kसमय_प्रकार ts_rx;
	kसमय_प्रकार ts_out_fc;
	kसमय_प्रकार ts_max_fc_delay;
	व्योम *client_data;
पूर्ण;

/* Client connection managenment पूर्णांकernal functions */
पूर्णांक ishtp_can_client_connect(काष्ठा ishtp_device *ishtp_dev, guid_t *uuid);
पूर्णांक ishtp_fw_cl_by_id(काष्ठा ishtp_device *dev, uपूर्णांक8_t client_id);
व्योम ishtp_cl_send_msg(काष्ठा ishtp_device *dev, काष्ठा ishtp_cl *cl);
व्योम recv_ishtp_cl_msg(काष्ठा ishtp_device *dev,
		       काष्ठा ishtp_msg_hdr *ishtp_hdr);
पूर्णांक ishtp_cl_पढ़ो_start(काष्ठा ishtp_cl *cl);

/* Ring Buffer I/F */
पूर्णांक ishtp_cl_alloc_rx_ring(काष्ठा ishtp_cl *cl);
पूर्णांक ishtp_cl_alloc_tx_ring(काष्ठा ishtp_cl *cl);
व्योम ishtp_cl_मुक्त_rx_ring(काष्ठा ishtp_cl *cl);
व्योम ishtp_cl_मुक्त_tx_ring(काष्ठा ishtp_cl *cl);
पूर्णांक ishtp_cl_get_tx_मुक्त_buffer_size(काष्ठा ishtp_cl *cl);
पूर्णांक ishtp_cl_get_tx_मुक्त_rings(काष्ठा ishtp_cl *cl);

/* DMA I/F functions */
व्योम recv_ishtp_cl_msg_dma(काष्ठा ishtp_device *dev, व्योम *msg,
			   काष्ठा dma_xfer_hbm *hbm);
व्योम ishtp_cl_alloc_dma_buf(काष्ठा ishtp_device *dev);
व्योम ishtp_cl_मुक्त_dma_buf(काष्ठा ishtp_device *dev);
व्योम *ishtp_cl_get_dma_send_buf(काष्ठा ishtp_device *dev,
				uपूर्णांक32_t size);
व्योम ishtp_cl_release_dma_acked_mem(काष्ठा ishtp_device *dev,
				    व्योम *msg_addr,
				    uपूर्णांक8_t size);

/* Request blocks alloc/मुक्त I/F */
काष्ठा ishtp_cl_rb *ishtp_io_rb_init(काष्ठा ishtp_cl *cl);
व्योम ishtp_io_rb_मुक्त(काष्ठा ishtp_cl_rb *priv_rb);
पूर्णांक ishtp_io_rb_alloc_buf(काष्ठा ishtp_cl_rb *rb, माप_प्रकार length);

/**
 * ishtp_cl_cmp_id - tells अगर file निजी data have same id
 * वापसs true  - अगर ids are the same and not शून्य
 */
अटल अंतरभूत bool ishtp_cl_cmp_id(स्थिर काष्ठा ishtp_cl *cl1,
				   स्थिर काष्ठा ishtp_cl *cl2)
अणु
	वापस cl1 && cl2 &&
		(cl1->host_client_id == cl2->host_client_id) &&
		(cl1->fw_client_id == cl2->fw_client_id);
पूर्ण

#पूर्ण_अगर /* _ISHTP_CLIENT_H_ */
