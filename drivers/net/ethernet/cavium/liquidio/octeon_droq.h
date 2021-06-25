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
/*!  \पile  octeon_droq.h
 *   \मrief Implementation of Octeon Output queues. "Output" is with
 *   respect to the Octeon device on the NIC. From this driver's poपूर्णांक of
 *   view they are ingress queues.
 */

#अगर_अघोषित __OCTEON_DROQ_H__
#घोषणा __OCTEON_DROQ_H__

/* Default number of packets that will be processed in one iteration. */
#घोषणा MAX_PACKET_BUDGET 0xFFFFFFFF

/** Octeon descriptor क्रमmat.
 *  The descriptor ring is made of descriptors which have 2 64-bit values:
 *  -# Physical (bus) address of the data buffer.
 *  -# Physical (bus) address of a octeon_droq_info काष्ठाure.
 *  The Octeon device DMA's incoming packets and its inक्रमmation at the address
 *  given by these descriptor fields.
 */
काष्ठा octeon_droq_desc अणु
	/** The buffer poपूर्णांकer */
	u64 buffer_ptr;

	/** The Info poपूर्णांकer */
	u64 info_ptr;
पूर्ण;

#घोषणा OCT_DROQ_DESC_SIZE    (माप(काष्ठा octeon_droq_desc))

/** Inक्रमmation about packet DMA'ed by Octeon.
 *  The क्रमmat of the inक्रमmation available at Info Poपूर्णांकer after Octeon
 *  has posted a packet. Not all descriptors have valid inक्रमmation. Only
 *  the Info field of the first descriptor क्रम a packet has inक्रमmation
 *  about the packet.
 */
काष्ठा octeon_droq_info अणु
	/** The Length of the packet. */
	u64 length;

	/** The Output Receive Header. */
	जोड़ octeon_rh rh;
पूर्ण;

#घोषणा OCT_DROQ_INFO_SIZE   (माप(काष्ठा octeon_droq_info))

काष्ठा octeon_skb_page_info अणु
	/* DMA address क्रम the page */
	dma_addr_t dma;

	/* Page क्रम the rx dma  **/
	काष्ठा page *page;

	/** which offset पूर्णांकo page */
	अचिन्हित पूर्णांक page_offset;
पूर्ण;

/** Poपूर्णांकer to data buffer.
 *  Driver keeps a poपूर्णांकer to the data buffer that it made available to
 *  the Octeon device. Since the descriptor ring keeps physical (bus)
 *  addresses, this field is required क्रम the driver to keep track of
 *  the भव address poपूर्णांकers.
 */
काष्ठा octeon_recv_buffer अणु
	/** Packet buffer, including metadata. */
	व्योम *buffer;

	/** Data in the packet buffer.  */
	u8 *data;

	/** pg_info **/
	काष्ठा octeon_skb_page_info pg_info;
पूर्ण;

#घोषणा OCT_DROQ_RECVBUF_SIZE    (माप(काष्ठा octeon_recv_buffer))

/** Output Queue statistics. Each output queue has four stats fields. */
काष्ठा oct_droq_stats अणु
	/** Number of packets received in this queue. */
	u64 pkts_received;

	/** Bytes received by this queue. */
	u64 bytes_received;

	/** Packets dropped due to no dispatch function. */
	u64 dropped_nodispatch;

	/** Packets dropped due to no memory available. */
	u64 dropped_nomem;

	/** Packets dropped due to large number of pkts to process. */
	u64 dropped_toomany;

	/** Number of packets  sent to stack from this queue. */
	u64 rx_pkts_received;

	/** Number of Bytes sent to stack from this queue. */
	u64 rx_bytes_received;

	/** Num of Packets dropped due to receive path failures. */
	u64 rx_dropped;

	u64 rx_vxlan;

	/** Num of failures of recv_buffer_alloc() */
	u64 rx_alloc_failure;

पूर्ण;

/* The maximum number of buffers that can be dispatched from the
 * output/dma queue. Set to 64 assuming 1K buffers in DROQ and the fact that
 * max packet size from DROQ is 64K.
 */
#घोषणा    MAX_RECV_BUFS    64

/** Receive Packet क्रमmat used when dispatching output queue packets
 *  with non-raw opcodes.
 *  The received packet will be sent to the upper layers using this
 *  काष्ठाure which is passed as a parameter to the dispatch function
 */
काष्ठा octeon_recv_pkt अणु
	/**  Number of buffers in this received packet */
	u16 buffer_count;

	/** Id of the device that is sending the packet up */
	u16 octeon_id;

	/** Length of data in the packet buffer */
	u32 length;

	/** The receive header */
	जोड़ octeon_rh rh;

	/** Poपूर्णांकer to the OS-specअगरic packet buffer */
	व्योम *buffer_ptr[MAX_RECV_BUFS];

	/** Size of the buffers poपूर्णांकed to by ptr's in buffer_ptr */
	u32 buffer_size[MAX_RECV_BUFS];
पूर्ण;

#घोषणा OCT_RECV_PKT_SIZE    (माप(काष्ठा octeon_recv_pkt))

/** The first parameter of a dispatch function.
 *  For a raw mode opcode, the driver dispatches with the device
 *  poपूर्णांकer in this काष्ठाure.
 *  For non-raw mode opcode, the driver dispatches the recv_pkt
 *  created to contain the buffers with data received from Octeon.
 *  ---------------------
 *  |     *recv_pkt ----|---
 *  |-------------------|   |
 *  | 0 or more bytes   |   |
 *  | reserved by driver|   |
 *  |-------------------|<-/
 *  | octeon_recv_pkt   |
 *  |                   |
 *  |___________________|
 */
काष्ठा octeon_recv_info अणु
	व्योम *rsvd;
	काष्ठा octeon_recv_pkt *recv_pkt;
पूर्ण;

#घोषणा  OCT_RECV_INFO_SIZE    (माप(काष्ठा octeon_recv_info))

/** Allocate a recv_info काष्ठाure. The recv_pkt poपूर्णांकer in the recv_info
 *  काष्ठाure is filled in beक्रमe this call वापसs.
 *  @param extra_bytes - extra bytes to be allocated at the end of the recv info
 *                       काष्ठाure.
 *  @वापस - poपूर्णांकer to a newly allocated recv_info काष्ठाure.
 */
अटल अंतरभूत काष्ठा octeon_recv_info *octeon_alloc_recv_info(पूर्णांक extra_bytes)
अणु
	काष्ठा octeon_recv_info *recv_info;
	u8 *buf;

	buf = kदो_स्मृति(OCT_RECV_PKT_SIZE + OCT_RECV_INFO_SIZE +
		      extra_bytes, GFP_ATOMIC);
	अगर (!buf)
		वापस शून्य;

	recv_info = (काष्ठा octeon_recv_info *)buf;
	recv_info->recv_pkt =
		(काष्ठा octeon_recv_pkt *)(buf + OCT_RECV_INFO_SIZE);
	recv_info->rsvd = शून्य;
	अगर (extra_bytes)
		recv_info->rsvd = buf + OCT_RECV_INFO_SIZE + OCT_RECV_PKT_SIZE;

	वापस recv_info;
पूर्ण

/** Free a recv_info काष्ठाure.
 *  @param recv_info - Poपूर्णांकer to receive_info to be मुक्तd
 */
अटल अंतरभूत व्योम octeon_मुक्त_recv_info(काष्ठा octeon_recv_info *recv_info)
अणु
	kमुक्त(recv_info);
पूर्ण

प्रकार पूर्णांक (*octeon_dispatch_fn_t)(काष्ठा octeon_recv_info *, व्योम *);

/** Used by NIC module to रेजिस्टर packet handler and to get device
 * inक्रमmation क्रम each octeon device.
 */
काष्ठा octeon_droq_ops अणु
	/** This रेजिस्टरed function will be called by the driver with
	 *  the octeon id, poपूर्णांकer to buffer from droq and length of
	 *  data in the buffer. The receive header gives the port
	 *  number to the caller.  Function poपूर्णांकer is set by caller.
	 */
	व्योम (*fptr)(u32, व्योम *, u32, जोड़ octeon_rh *, व्योम *, व्योम *);
	व्योम *farg;

	/* This function will be called by the driver क्रम all NAPI related
	 * events. The first param is the octeon id. The second param is the
	 * output queue number. The third is the NAPI event that occurred.
	 */
	व्योम (*napi_fn)(व्योम *);

	u32 poll_mode;

	/** Flag indicating अगर the DROQ handler should drop packets that
	 *  it cannot handle in one iteration. Set by caller.
	 */
	u32 drop_on_max;
पूर्ण;

/** The Descriptor Ring Output Queue काष्ठाure.
 *  This काष्ठाure has all the inक्रमmation required to implement a
 *  Octeon DROQ.
 */
काष्ठा octeon_droq अणु
	u32 q_no;

	u32 pkt_count;

	काष्ठा octeon_droq_ops ops;

	काष्ठा octeon_device *oct_dev;

	/** The 8B aligned descriptor ring starts at this address. */
	काष्ठा octeon_droq_desc *desc_ring;

	/** Index in the ring where the driver should पढ़ो the next packet */
	u32 पढ़ो_idx;

	/** Index in the ring where Octeon will ग_लिखो the next packet */
	u32 ग_लिखो_idx;

	/** Index in the ring where the driver will refill the descriptor's
	 * buffer
	 */
	u32 refill_idx;

	/** Packets pending to be processed */
	atomic_t pkts_pending;

	/** Number of  descriptors in this ring. */
	u32 max_count;

	/** The number of descriptors pending refill. */
	u32 refill_count;

	u32 pkts_per_पूर्णांकr;
	u32 refill_threshold;

	/** The max number of descriptors in DROQ without a buffer.
	 * This field is used to keep track of empty space threshold. If the
	 * refill_count reaches this value, the DROQ cannot accept a max-sized
	 * (64K) packet.
	 */
	u32 max_empty_descs;

	/** The receive buffer list. This list has the भव addresses of the
	 * buffers.
	 */
	काष्ठा octeon_recv_buffer *recv_buf_list;

	/** The size of each buffer poपूर्णांकed by the buffer poपूर्णांकer. */
	u32 buffer_size;

	/** Poपूर्णांकer to the mapped packet credit रेजिस्टर.
	 * Host ग_लिखोs number of info/buffer ptrs available to this रेजिस्टर
	 */
	व्योम  __iomem *pkts_credit_reg;

	/** Poपूर्णांकer to the mapped packet sent रेजिस्टर.
	 * Octeon ग_लिखोs the number of packets DMA'ed to host memory
	 * in this रेजिस्टर.
	 */
	व्योम __iomem *pkts_sent_reg;

	काष्ठा list_head dispatch_list;

	/** Statistics क्रम this DROQ. */
	काष्ठा oct_droq_stats stats;

	/** DMA mapped address of the DROQ descriptor ring. */
	माप_प्रकार desc_ring_dma;

	/** application context */
	व्योम *app_ctx;

	काष्ठा napi_काष्ठा napi;

	u32 cpu_id;

	call_single_data_t csd;
पूर्ण;

#घोषणा OCT_DROQ_SIZE   (माप(काष्ठा octeon_droq))

/**
 *  Allocates space क्रम the descriptor ring क्रम the droq and sets the
 *   base addr, num desc etc in Octeon रेजिस्टरs.
 *
 * @param  oct_dev    - poपूर्णांकer to the octeon device काष्ठाure
 * @param  q_no       - droq no. ranges from 0 - 3.
 * @param app_ctx     - poपूर्णांकer to application context
 * @वापस Success: 0    Failure: 1
 */
पूर्णांक octeon_init_droq(काष्ठा octeon_device *oct_dev,
		     u32 q_no,
		     u32 num_descs,
		     u32 desc_size,
		     व्योम *app_ctx);

/**
 *  Frees the space क्रम descriptor ring क्रम the droq.
 *
 *  @param oct_dev - poपूर्णांकer to the octeon device काष्ठाure
 *  @param q_no    - droq no. ranges from 0 - 3.
 *  @वापस:    Success: 0    Failure: 1
 */
पूर्णांक octeon_delete_droq(काष्ठा octeon_device *oct_dev, u32 q_no);

/** Register a change in droq operations. The ops field has a poपूर्णांकer to a
 * function which will called by the DROQ handler क्रम all packets arriving
 * on output queues given by q_no irrespective of the type of packet.
 * The ops field also has a flag which अगर set tells the DROQ handler to
 * drop packets अगर it receives more than what it can process in one
 * invocation of the handler.
 * @param oct       - octeon device
 * @param q_no      - octeon output queue number (0 <= q_no <= MAX_OCTEON_DROQ-1
 * @param ops       - the droq_ops settings क्रम this queue
 * @वापस          - 0 on success, -ENODEV or -EINVAL on error.
 */
पूर्णांक
octeon_रेजिस्टर_droq_ops(काष्ठा octeon_device *oct,
			 u32 q_no,
			 काष्ठा octeon_droq_ops *ops);

/** Resets the function poपूर्णांकer and flag settings made by
 * octeon_रेजिस्टर_droq_ops(). After this routine is called, the DROQ handler
 * will lookup dispatch function क्रम each arriving packet on the output queue
 * given by q_no.
 * @param oct       - octeon device
 * @param q_no      - octeon output queue number (0 <= q_no <= MAX_OCTEON_DROQ-1
 * @वापस          - 0 on success, -ENODEV or -EINVAL on error.
 */
पूर्णांक octeon_unरेजिस्टर_droq_ops(काष्ठा octeon_device *oct, u32 q_no);

/**   Register a dispatch function क्रम a opcode/subcode. The driver will call
 *    this dispatch function when it receives a packet with the given
 *    opcode/subcode in its output queues aदीर्घ with the user specअगरied
 *    argument.
 *    @param  oct        - the octeon device to रेजिस्टर with.
 *    @param  opcode     - the opcode क्रम which the dispatch will be रेजिस्टरed.
 *    @param  subcode    - the subcode क्रम which the dispatch will be रेजिस्टरed
 *    @param  fn         - the dispatch function.
 *    @param  fn_arg     - user specअगरied that will be passed aदीर्घ with the
 *                         dispatch function by the driver.
 *    @वापस Success: 0; Failure: 1
 */
पूर्णांक octeon_रेजिस्टर_dispatch_fn(काष्ठा octeon_device *oct,
				u16 opcode,
				u16 subcode,
				octeon_dispatch_fn_t fn, व्योम *fn_arg);

व्योम *octeon_get_dispatch_arg(काष्ठा octeon_device *oct,
			      u16 opcode, u16 subcode);

व्योम octeon_droq_prपूर्णांक_stats(व्योम);

u32 octeon_droq_check_hw_क्रम_pkts(काष्ठा octeon_droq *droq);

पूर्णांक octeon_create_droq(काष्ठा octeon_device *oct, u32 q_no,
		       u32 num_descs, u32 desc_size, व्योम *app_ctx);

पूर्णांक octeon_droq_process_packets(काष्ठा octeon_device *oct,
				काष्ठा octeon_droq *droq,
				u32 budget);

पूर्णांक octeon_droq_process_poll_pkts(काष्ठा octeon_device *oct,
				  काष्ठा octeon_droq *droq, u32 budget);

पूर्णांक octeon_enable_irq(काष्ठा octeon_device *oct, u32 q_no);

पूर्णांक octeon_retry_droq_refill(काष्ठा octeon_droq *droq);

#पूर्ण_अगर	/*__OCTEON_DROQ_H__ */
