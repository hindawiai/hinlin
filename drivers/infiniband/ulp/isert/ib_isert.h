<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/rw.h>
#समावेश <scsi/iser.h>


#घोषणा DRV_NAME	"isert"
#घोषणा PFX		DRV_NAME ": "

#घोषणा isert_dbg(fmt, arg...)				 \
	करो अणु						 \
		अगर (unlikely(isert_debug_level > 2))	 \
			prपूर्णांकk(KERN_DEBUG PFX "%s: " fmt,\
				__func__ , ## arg);	 \
	पूर्ण जबतक (0)

#घोषणा isert_warn(fmt, arg...)				\
	करो अणु						\
		अगर (unlikely(isert_debug_level > 0))	\
			pr_warn(PFX "%s: " fmt,         \
				__func__ , ## arg);	\
	पूर्ण जबतक (0)

#घोषणा isert_info(fmt, arg...)				\
	करो अणु						\
		अगर (unlikely(isert_debug_level > 1))	\
			pr_info(PFX "%s: " fmt,         \
				__func__ , ## arg);	\
	पूर्ण जबतक (0)

#घोषणा isert_err(fmt, arg...) \
	pr_err(PFX "%s: " fmt, __func__ , ## arg)

/* Constant PDU lengths calculations */
#घोषणा ISER_HEADERS_LEN	(माप(काष्ठा iser_ctrl) + \
				 माप(काष्ठा iscsi_hdr))
#घोषणा ISER_RX_PAYLOAD_SIZE	(ISER_HEADERS_LEN + ISCSI_DEF_MAX_RECV_SEG_LEN)

/* QP settings */
/* Maximal bounds on received asynchronous PDUs */
#घोषणा ISERT_MAX_TX_MISC_PDUS	4 /* NOOP_IN(2) , ASYNC_EVENT(2)   */

#घोषणा ISERT_MAX_RX_MISC_PDUS	6 /*
				   * NOOP_OUT(2), TEXT(1),
				   * SCSI_TMFUNC(2), LOGOUT(1)
				   */

#घोषणा ISCSI_DEF_XMIT_CMDS_MAX 128 /* from libiscsi.h, must be घातer of 2 */

#घोषणा ISERT_QP_MAX_RECV_DTOS	(ISCSI_DEF_XMIT_CMDS_MAX)

#घोषणा ISERT_MIN_POSTED_RX	(ISCSI_DEF_XMIT_CMDS_MAX >> 2)

#घोषणा ISERT_QP_MAX_REQ_DTOS	(ISCSI_DEF_XMIT_CMDS_MAX +    \
				ISERT_MAX_TX_MISC_PDUS	+ \
				ISERT_MAX_RX_MISC_PDUS)

/*
 * RX size is शेष of 8k plus headers, but data needs to align to
 * 512 boundary, so use 1024 to have the extra space क्रम alignment.
 */
#घोषणा ISER_RX_SIZE		(ISCSI_DEF_MAX_RECV_SEG_LEN + 1024)

/* Default I/O size is 1MB */
#घोषणा ISCSI_ISER_DEF_SG_TABLESIZE 256

/* Minimum I/O size is 512KB */
#घोषणा ISCSI_ISER_MIN_SG_TABLESIZE 128

/* Maximum support is 16MB I/O size */
#घोषणा ISCSI_ISER_MAX_SG_TABLESIZE	4096

क्रमागत isert_desc_type अणु
	ISCSI_TX_CONTROL,
	ISCSI_TX_DATAIN
पूर्ण;

क्रमागत iser_conn_state अणु
	ISER_CONN_INIT,
	ISER_CONN_UP,
	ISER_CONN_BOUND,
	ISER_CONN_FULL_FEATURE,
	ISER_CONN_TERMINATING,
	ISER_CONN_DOWN,
पूर्ण;

काष्ठा iser_rx_desc अणु
	अक्षर		buf[ISER_RX_SIZE];
	u64		dma_addr;
	काष्ठा ib_sge	rx_sg;
	काष्ठा ib_cqe	rx_cqe;
	bool		in_use;
पूर्ण;

अटल अंतरभूत काष्ठा iser_rx_desc *cqe_to_rx_desc(काष्ठा ib_cqe *cqe)
अणु
	वापस container_of(cqe, काष्ठा iser_rx_desc, rx_cqe);
पूर्ण

अटल व्योम *isert_get_iser_hdr(काष्ठा iser_rx_desc *desc)
अणु
	वापस PTR_ALIGN(desc->buf + ISER_HEADERS_LEN, 512) - ISER_HEADERS_LEN;
पूर्ण

अटल माप_प्रकार isert_get_hdr_offset(काष्ठा iser_rx_desc *desc)
अणु
	वापस isert_get_iser_hdr(desc) - (व्योम *)desc->buf;
पूर्ण

अटल व्योम *isert_get_iscsi_hdr(काष्ठा iser_rx_desc *desc)
अणु
	वापस isert_get_iser_hdr(desc) + माप(काष्ठा iser_ctrl);
पूर्ण

अटल व्योम *isert_get_data(काष्ठा iser_rx_desc *desc)
अणु
	व्योम *data = isert_get_iser_hdr(desc) + ISER_HEADERS_LEN;

	WARN_ON((uपूर्णांकptr_t)data & 511);
	वापस data;
पूर्ण

काष्ठा iser_tx_desc अणु
	काष्ठा iser_ctrl iser_header;
	काष्ठा iscsi_hdr iscsi_header;
	क्रमागत isert_desc_type type;
	u64		dma_addr;
	काष्ठा ib_sge	tx_sg[2];
	काष्ठा ib_cqe	tx_cqe;
	पूर्णांक		num_sge;
	काष्ठा ib_send_wr send_wr;
पूर्ण __packed;

अटल अंतरभूत काष्ठा iser_tx_desc *cqe_to_tx_desc(काष्ठा ib_cqe *cqe)
अणु
	वापस container_of(cqe, काष्ठा iser_tx_desc, tx_cqe);
पूर्ण

काष्ठा isert_cmd अणु
	uपूर्णांक32_t		पढ़ो_stag;
	uपूर्णांक32_t		ग_लिखो_stag;
	uपूर्णांक64_t		पढ़ो_va;
	uपूर्णांक64_t		ग_लिखो_va;
	uपूर्णांक32_t		inv_rkey;
	u64			pdu_buf_dma;
	u32			pdu_buf_len;
	काष्ठा isert_conn	*conn;
	काष्ठा iscsi_cmd	*iscsi_cmd;
	काष्ठा iser_tx_desc	tx_desc;
	काष्ठा iser_rx_desc	*rx_desc;
	काष्ठा rdma_rw_ctx	rw;
	काष्ठा work_काष्ठा	comp_work;
	काष्ठा scatterlist	sg;
	bool			ctx_init_करोne;
पूर्ण;

अटल अंतरभूत काष्ठा isert_cmd *tx_desc_to_cmd(काष्ठा iser_tx_desc *desc)
अणु
	वापस container_of(desc, काष्ठा isert_cmd, tx_desc);
पूर्ण

काष्ठा isert_device;

काष्ठा isert_conn अणु
	क्रमागत iser_conn_state	state;
	u32			responder_resources;
	u32			initiator_depth;
	bool			pi_support;
	काष्ठा iser_rx_desc	*login_desc;
	अक्षर			*login_rsp_buf;
	पूर्णांक			login_req_len;
	u64			login_rsp_dma;
	काष्ठा iser_rx_desc	*rx_descs;
	काष्ठा ib_recv_wr	rx_wr[ISERT_QP_MAX_RECV_DTOS];
	काष्ठा iscsi_conn	*conn;
	काष्ठा list_head	node;
	काष्ठा completion	login_comp;
	काष्ठा completion	login_req_comp;
	काष्ठा iser_tx_desc	login_tx_desc;
	काष्ठा rdma_cm_id	*cm_id;
	काष्ठा ib_qp		*qp;
	काष्ठा ib_cq		*cq;
	u32			cq_size;
	काष्ठा isert_device	*device;
	काष्ठा mutex		mutex;
	काष्ठा kref		kref;
	काष्ठा work_काष्ठा	release_work;
	bool                    logout_posted;
	bool                    snd_w_inv;
	रुको_queue_head_t	rem_रुको;
	bool			dev_हटाओd;
पूर्ण;

काष्ठा isert_device अणु
	bool			pi_capable;
	पूर्णांक			refcount;
	काष्ठा ib_device	*ib_device;
	काष्ठा ib_pd		*pd;
	काष्ठा isert_comp	*comps;
	पूर्णांक                     comps_used;
	काष्ठा list_head	dev_node;
पूर्ण;

काष्ठा isert_np अणु
	काष्ठा iscsi_np         *np;
	काष्ठा semaphore	sem;
	काष्ठा rdma_cm_id	*cm_id;
	काष्ठा mutex		mutex;
	काष्ठा list_head	accepted;
	काष्ठा list_head	pending;
पूर्ण;
