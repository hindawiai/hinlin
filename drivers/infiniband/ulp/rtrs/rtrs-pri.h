<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RDMA Transport Layer
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */

#अगर_अघोषित RTRS_PRI_H
#घोषणा RTRS_PRI_H

#समावेश <linux/uuid.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib.h>

#समावेश "rtrs.h"

#घोषणा RTRS_PROTO_VER_MAJOR 2
#घोषणा RTRS_PROTO_VER_MINOR 0

#घोषणा RTRS_PROTO_VER_STRING __stringअगरy(RTRS_PROTO_VER_MAJOR) "." \
			       __stringअगरy(RTRS_PROTO_VER_MINOR)

क्रमागत rtrs_imm_स्थिर अणु
	MAX_IMM_TYPE_BITS = 4,
	MAX_IMM_TYPE_MASK = ((1 << MAX_IMM_TYPE_BITS) - 1),
	MAX_IMM_PAYL_BITS = 28,
	MAX_IMM_PAYL_MASK = ((1 << MAX_IMM_PAYL_BITS) - 1),
पूर्ण;

क्रमागत rtrs_imm_type अणु
	RTRS_IO_REQ_IMM       = 0, /* client to server */
	RTRS_IO_RSP_IMM       = 1, /* server to client */
	RTRS_IO_RSP_W_INV_IMM = 2, /* server to client */

	RTRS_HB_MSG_IMM = 8, /* HB: HeartBeat */
	RTRS_HB_ACK_IMM = 9,

	RTRS_LAST_IMM,
पूर्ण;

क्रमागत अणु
	SERVICE_CON_QUEUE_DEPTH = 512,

	MAX_PATHS_NUM = 128,

	/*
	 * With the size of काष्ठा rtrs_permit allocated on the client, 4K
	 * is the maximum number of rtrs_permits we can allocate. This number is
	 * also used on the client to allocate the IU क्रम the user connection
	 * to receive the RDMA addresses from the server.
	 */
	MAX_SESS_QUEUE_DEPTH = 4096,

	RTRS_HB_INTERVAL_MS = 5000,
	RTRS_HB_MISSED_MAX = 5,

	RTRS_MAGIC = 0x1BBD,
	RTRS_PROTO_VER = (RTRS_PROTO_VER_MAJOR << 8) | RTRS_PROTO_VER_MINOR,
पूर्ण;

काष्ठा rtrs_ib_dev;

काष्ठा rtrs_rdma_dev_pd_ops अणु
	काष्ठा rtrs_ib_dev *(*alloc)(व्योम);
	व्योम (*मुक्त)(काष्ठा rtrs_ib_dev *dev);
	पूर्णांक (*init)(काष्ठा rtrs_ib_dev *dev);
	व्योम (*deinit)(काष्ठा rtrs_ib_dev *dev);
पूर्ण;

काष्ठा rtrs_rdma_dev_pd अणु
	काष्ठा mutex		mutex;
	काष्ठा list_head	list;
	क्रमागत ib_pd_flags	pd_flags;
	स्थिर काष्ठा rtrs_rdma_dev_pd_ops *ops;
पूर्ण;

काष्ठा rtrs_ib_dev अणु
	काष्ठा ib_device	 *ib_dev;
	काष्ठा ib_pd		 *ib_pd;
	काष्ठा kref		 ref;
	काष्ठा list_head	 entry;
	काष्ठा rtrs_rdma_dev_pd *pool;
पूर्ण;

काष्ठा rtrs_con अणु
	काष्ठा rtrs_sess	*sess;
	काष्ठा ib_qp		*qp;
	काष्ठा ib_cq		*cq;
	काष्ठा rdma_cm_id	*cm_id;
	अचिन्हित पूर्णांक		cid;
	u16                     cq_size;
पूर्ण;

काष्ठा rtrs_sess अणु
	काष्ठा list_head	entry;
	काष्ठा sockaddr_storage dst_addr;
	काष्ठा sockaddr_storage src_addr;
	अक्षर			sessname[NAME_MAX];
	uuid_t			uuid;
	काष्ठा rtrs_con	**con;
	अचिन्हित पूर्णांक		con_num;
	अचिन्हित पूर्णांक		irq_con_num;
	अचिन्हित पूर्णांक		recon_cnt;
	काष्ठा rtrs_ib_dev	*dev;
	पूर्णांक			dev_ref;
	काष्ठा ib_cqe		*hb_cqe;
	व्योम			(*hb_err_handler)(काष्ठा rtrs_con *con);
	काष्ठा workqueue_काष्ठा *hb_wq;
	काष्ठा delayed_work	hb_dwork;
	अचिन्हित पूर्णांक		hb_पूर्णांकerval_ms;
	अचिन्हित पूर्णांक		hb_missed_cnt;
	अचिन्हित पूर्णांक		hb_missed_max;
	kसमय_प्रकार			hb_last_sent;
	kसमय_प्रकार			hb_cur_latency;
पूर्ण;

/* rtrs inक्रमmation unit */
काष्ठा rtrs_iu अणु
	काष्ठा ib_cqe           cqe;
	dma_addr_t              dma_addr;
	व्योम                    *buf;
	माप_प्रकार                  size;
	क्रमागत dma_data_direction direction;
पूर्ण;

/**
 * क्रमागत rtrs_msg_types - RTRS message types, see also rtrs/README
 * @RTRS_MSG_INFO_REQ:		Client additional info request to the server
 * @RTRS_MSG_INFO_RSP:		Server additional info response to the client
 * @RTRS_MSG_WRITE:		Client ग_लिखोs data per RDMA to server
 * @RTRS_MSG_READ:		Client requests data transfer from server
 * @RTRS_MSG_RKEY_RSP:		Server refreshed rkey क्रम rbuf
 */
क्रमागत rtrs_msg_types अणु
	RTRS_MSG_INFO_REQ,
	RTRS_MSG_INFO_RSP,
	RTRS_MSG_WRITE,
	RTRS_MSG_READ,
	RTRS_MSG_RKEY_RSP,
पूर्ण;

/**
 * क्रमागत rtrs_msg_flags - RTRS message flags.
 * @RTRS_NEED_INVAL:	Send invalidation in response.
 * @RTRS_MSG_NEW_RKEY_F: Send refreshed rkey in response.
 */
क्रमागत rtrs_msg_flags अणु
	RTRS_MSG_NEED_INVAL_F = 1 << 0,
	RTRS_MSG_NEW_RKEY_F = 1 << 1,
पूर्ण;

/**
 * काष्ठा rtrs_sg_desc - RDMA-Buffer entry description
 * @addr:	Address of RDMA destination buffer
 * @key:	Authorization rkey to ग_लिखो to the buffer
 * @len:	Size of the buffer
 */
काष्ठा rtrs_sg_desc अणु
	__le64			addr;
	__le32			key;
	__le32			len;
पूर्ण;

/**
 * काष्ठा rtrs_msg_conn_req - Client connection request to the server
 * @magic:	   RTRS magic
 * @version:	   RTRS protocol version
 * @cid:	   Current connection id
 * @cid_num:	   Number of connections per session
 * @recon_cnt:	   Reconnections counter
 * @sess_uuid:	   UUID of a session (path)
 * @paths_uuid:	   UUID of a group of sessions (paths)
 *
 * NOTE: max size 56 bytes, see man rdma_connect().
 */
काष्ठा rtrs_msg_conn_req अणु
	/* Is set to 0 by cma.c in हाल of AF_IB, करो not touch that.
	 * see https://www.spinics.net/lists/linux-rdma/msg22397.hपंचांगl
	 */
	u8		__cma_version;
	/* On sender side that should be set to 0, or cma_save_ip_info()
	 * extract garbage and will fail.
	 */
	u8		__ip_version;
	__le16		magic;
	__le16		version;
	__le16		cid;
	__le16		cid_num;
	__le16		recon_cnt;
	uuid_t		sess_uuid;
	uuid_t		paths_uuid;
	u8		first_conn : 1;
	u8		reserved_bits : 7;
	u8		reserved[11];
पूर्ण;

/**
 * काष्ठा rtrs_msg_conn_rsp - Server connection response to the client
 * @magic:	   RTRS magic
 * @version:	   RTRS protocol version
 * @त्रुटि_सं:	   If rdma_accept() then 0, अगर rdma_reject() indicates error
 * @queue_depth:   max inflight messages (queue-depth) in this session
 * @max_io_size:   max io size server supports
 * @max_hdr_size:  max msg header size server supports
 *
 * NOTE: size is 56 bytes, max possible is 136 bytes, see man rdma_accept().
 */
काष्ठा rtrs_msg_conn_rsp अणु
	__le16		magic;
	__le16		version;
	__le16		त्रुटि_सं;
	__le16		queue_depth;
	__le32		max_io_size;
	__le32		max_hdr_size;
	__le32		flags;
	u8		reserved[36];
पूर्ण;

/**
 * काष्ठा rtrs_msg_info_req
 * @type:		@RTRS_MSG_INFO_REQ
 * @sessname:		Session name chosen by client
 */
काष्ठा rtrs_msg_info_req अणु
	__le16		type;
	u8		sessname[NAME_MAX];
	u8		reserved[15];
पूर्ण;

/**
 * काष्ठा rtrs_msg_info_rsp
 * @type:		@RTRS_MSG_INFO_RSP
 * @sg_cnt:		Number of @desc entries
 * @desc:		RDMA buffers where the client can ग_लिखो to server
 */
काष्ठा rtrs_msg_info_rsp अणु
	__le16		type;
	__le16          sg_cnt;
	u8              reserved[4];
	काष्ठा rtrs_sg_desc desc[];
पूर्ण;

/**
 * काष्ठा rtrs_msg_rkey_rsp
 * @type:		@RTRS_MSG_RKEY_RSP
 * @buf_id:		RDMA buf_id of the new rkey
 * @rkey:		new remote key क्रम RDMA buffers id from server
 */
काष्ठा rtrs_msg_rkey_rsp अणु
	__le16		type;
	__le16          buf_id;
	__le32		rkey;
पूर्ण;

/**
 * काष्ठा rtrs_msg_rdma_पढ़ो - RDMA data transfer request from client
 * @type:		always @RTRS_MSG_READ
 * @usr_len:		length of user payload
 * @sg_cnt:		number of @desc entries
 * @desc:		RDMA buffers where the server can ग_लिखो the result to
 */
काष्ठा rtrs_msg_rdma_पढ़ो अणु
	__le16			type;
	__le16			usr_len;
	__le16			flags;
	__le16			sg_cnt;
	काष्ठा rtrs_sg_desc    desc[];
पूर्ण;

/**
 * काष्ठा_msg_rdma_ग_लिखो - Message transferred to server with RDMA-Write
 * @type:		always @RTRS_MSG_WRITE
 * @usr_len:		length of user payload
 */
काष्ठा rtrs_msg_rdma_ग_लिखो अणु
	__le16			type;
	__le16			usr_len;
पूर्ण;

/**
 * काष्ठा_msg_rdma_hdr - header क्रम पढ़ो or ग_लिखो request
 * @type:		@RTRS_MSG_WRITE | @RTRS_MSG_READ
 */
काष्ठा rtrs_msg_rdma_hdr अणु
	__le16			type;
पूर्ण;

/* rtrs.c */

काष्ठा rtrs_iu *rtrs_iu_alloc(u32 queue_size, माप_प्रकार size, gfp_t t,
			      काष्ठा ib_device *dev, क्रमागत dma_data_direction,
			      व्योम (*करोne)(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc));
व्योम rtrs_iu_मुक्त(काष्ठा rtrs_iu *iu, काष्ठा ib_device *dev, u32 queue_size);
पूर्णांक rtrs_iu_post_recv(काष्ठा rtrs_con *con, काष्ठा rtrs_iu *iu);
पूर्णांक rtrs_iu_post_send(काष्ठा rtrs_con *con, काष्ठा rtrs_iu *iu, माप_प्रकार size,
		      काष्ठा ib_send_wr *head);
पूर्णांक rtrs_iu_post_rdma_ग_लिखो_imm(काष्ठा rtrs_con *con, काष्ठा rtrs_iu *iu,
				काष्ठा ib_sge *sge, अचिन्हित पूर्णांक num_sge,
				u32 rkey, u64 rdma_addr, u32 imm_data,
				क्रमागत ib_send_flags flags,
				काष्ठा ib_send_wr *head);

पूर्णांक rtrs_post_recv_empty(काष्ठा rtrs_con *con, काष्ठा ib_cqe *cqe);
पूर्णांक rtrs_post_rdma_ग_लिखो_imm_empty(काष्ठा rtrs_con *con, काष्ठा ib_cqe *cqe,
				   u32 imm_data, क्रमागत ib_send_flags flags,
				   काष्ठा ib_send_wr *head);

पूर्णांक rtrs_cq_qp_create(काष्ठा rtrs_sess *rtrs_sess, काष्ठा rtrs_con *con,
		      u32 max_send_sge, पूर्णांक cq_vector, पूर्णांक cq_size,
		      u32 max_send_wr, u32 max_recv_wr,
		      क्रमागत ib_poll_context poll_ctx);
व्योम rtrs_cq_qp_destroy(काष्ठा rtrs_con *con);

व्योम rtrs_init_hb(काष्ठा rtrs_sess *sess, काष्ठा ib_cqe *cqe,
		  अचिन्हित पूर्णांक पूर्णांकerval_ms, अचिन्हित पूर्णांक missed_max,
		  व्योम (*err_handler)(काष्ठा rtrs_con *con),
		  काष्ठा workqueue_काष्ठा *wq);
व्योम rtrs_start_hb(काष्ठा rtrs_sess *sess);
व्योम rtrs_stop_hb(काष्ठा rtrs_sess *sess);
व्योम rtrs_send_hb_ack(काष्ठा rtrs_sess *sess);

व्योम rtrs_rdma_dev_pd_init(क्रमागत ib_pd_flags pd_flags,
			   काष्ठा rtrs_rdma_dev_pd *pool);
व्योम rtrs_rdma_dev_pd_deinit(काष्ठा rtrs_rdma_dev_pd *pool);

काष्ठा rtrs_ib_dev *rtrs_ib_dev_find_or_add(काष्ठा ib_device *ib_dev,
					    काष्ठा rtrs_rdma_dev_pd *pool);
पूर्णांक rtrs_ib_dev_put(काष्ठा rtrs_ib_dev *dev);

अटल अंतरभूत u32 rtrs_to_imm(u32 type, u32 payload)
अणु
	BUILD_BUG_ON(MAX_IMM_PAYL_BITS + MAX_IMM_TYPE_BITS != 32);
	BUILD_BUG_ON(RTRS_LAST_IMM > (1<<MAX_IMM_TYPE_BITS));
	वापस ((type & MAX_IMM_TYPE_MASK) << MAX_IMM_PAYL_BITS) |
		(payload & MAX_IMM_PAYL_MASK);
पूर्ण

अटल अंतरभूत व्योम rtrs_from_imm(u32 imm, u32 *type, u32 *payload)
अणु
	*payload = imm & MAX_IMM_PAYL_MASK;
	*type = imm >> MAX_IMM_PAYL_BITS;
पूर्ण

अटल अंतरभूत u32 rtrs_to_io_req_imm(u32 addr)
अणु
	वापस rtrs_to_imm(RTRS_IO_REQ_IMM, addr);
पूर्ण

अटल अंतरभूत u32 rtrs_to_io_rsp_imm(u32 msg_id, पूर्णांक त्रुटि_सं, bool w_inval)
अणु
	क्रमागत rtrs_imm_type type;
	u32 payload;

	/* 9 bits क्रम त्रुटि_सं, 19 bits क्रम msg_id */
	payload = (असल(त्रुटि_सं) & 0x1ff) << 19 | (msg_id & 0x7ffff);
	type = w_inval ? RTRS_IO_RSP_W_INV_IMM : RTRS_IO_RSP_IMM;

	वापस rtrs_to_imm(type, payload);
पूर्ण

अटल अंतरभूत व्योम rtrs_from_io_rsp_imm(u32 payload, u32 *msg_id, पूर्णांक *त्रुटि_सं)
अणु
	/* 9 bits क्रम त्रुटि_सं, 19 bits क्रम msg_id */
	*msg_id = payload & 0x7ffff;
	*त्रुटि_सं = -(पूर्णांक)((payload >> 19) & 0x1ff);
पूर्ण

#घोषणा STAT_STORE_FUNC(type, set_value, reset)				\
अटल sमाप_प्रकार set_value##_store(काष्ठा kobject *kobj,			\
			     काष्ठा kobj_attribute *attr,		\
			     स्थिर अक्षर *buf, माप_प्रकार count)		\
अणु									\
	पूर्णांक ret = -EINVAL;						\
	type *stats = container_of(kobj, type, kobj_stats);		\
									\
	अगर (sysfs_streq(buf, "1"))					\
		ret = reset(stats, true);			\
	अन्यथा अगर (sysfs_streq(buf, "0"))					\
		ret = reset(stats, false);			\
	अगर (ret)							\
		वापस ret;						\
									\
	वापस count;							\
पूर्ण

#घोषणा STAT_SHOW_FUNC(type, get_value, prपूर्णांक)				\
अटल sमाप_प्रकार get_value##_show(काष्ठा kobject *kobj,			\
			   काष्ठा kobj_attribute *attr,			\
			   अक्षर *page)					\
अणु									\
	type *stats = container_of(kobj, type, kobj_stats);		\
									\
	वापस prपूर्णांक(stats, page, PAGE_SIZE);			\
पूर्ण

#घोषणा STAT_ATTR(type, stat, prपूर्णांक, reset)				\
STAT_STORE_FUNC(type, stat, reset)					\
STAT_SHOW_FUNC(type, stat, prपूर्णांक)					\
अटल काष्ठा kobj_attribute stat##_attr = __ATTR_RW(stat)

#पूर्ण_अगर /* RTRS_PRI_H */
