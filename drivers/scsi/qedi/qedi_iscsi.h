<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#अगर_अघोषित _QEDI_ISCSI_H_
#घोषणा _QEDI_ISCSI_H_

#समावेश <linux/socket.h>
#समावेश <linux/completion.h>
#समावेश "qedi.h"

#घोषणा ISCSI_MAX_SESS_PER_HBA	4096

#घोषणा DEF_KA_TIMEOUT		7200000
#घोषणा DEF_KA_INTERVAL		10000
#घोषणा DEF_KA_MAX_PROBE_COUNT	10
#घोषणा DEF_TOS			0
#घोषणा DEF_TTL			0xfe
#घोषणा DEF_SND_SEQ_SCALE	0
#घोषणा DEF_RCV_BUF		0xffff
#घोषणा DEF_SND_BUF		0xffff
#घोषणा DEF_SEED		0
#घोषणा DEF_MAX_RT_TIME		8000
#घोषणा DEF_MAX_DA_COUNT        2
#घोषणा DEF_SWS_TIMER		1000
#घोषणा DEF_MAX_CWND		2
#घोषणा DEF_PATH_MTU		1500
#घोषणा DEF_MSS			1460
#घोषणा DEF_LL2_MTU		1560
#घोषणा JUMBO_MTU		9000

#घोषणा MIN_MTU         576 /* rfc 793 */
#घोषणा IPV4_HDR_LEN    20
#घोषणा IPV6_HDR_LEN    40
#घोषणा TCP_HDR_LEN     20
#घोषणा TCP_OPTION_LEN  12
#घोषणा VLAN_LEN         4

क्रमागत अणु
	EP_STATE_IDLE                   = 0x0,
	EP_STATE_ACQRCONN_START         = 0x1,
	EP_STATE_ACQRCONN_COMPL         = 0x2,
	EP_STATE_OFLDCONN_START         = 0x4,
	EP_STATE_OFLDCONN_COMPL         = 0x8,
	EP_STATE_DISCONN_START          = 0x10,
	EP_STATE_DISCONN_COMPL          = 0x20,
	EP_STATE_CLEANUP_START          = 0x40,
	EP_STATE_CLEANUP_CMPL           = 0x80,
	EP_STATE_TCP_FIN_RCVD           = 0x100,
	EP_STATE_TCP_RST_RCVD           = 0x200,
	EP_STATE_LOGOUT_SENT            = 0x400,
	EP_STATE_LOGOUT_RESP_RCVD       = 0x800,
	EP_STATE_CLEANUP_FAILED         = 0x1000,
	EP_STATE_OFLDCONN_FAILED        = 0x2000,
	EP_STATE_CONNECT_FAILED         = 0x4000,
	EP_STATE_DISCONN_TIMEDOUT       = 0x8000,
	EP_STATE_OFLDCONN_NONE          = 0x10000,
पूर्ण;

काष्ठा qedi_conn;

काष्ठा qedi_endpoपूर्णांक अणु
	काष्ठा qedi_ctx *qedi;
	u32 dst_addr[4];
	u32 src_addr[4];
	u16 src_port;
	u16 dst_port;
	u16 vlan_id;
	u16 pmtu;
	u8 src_mac[ETH_ALEN];
	u8 dst_mac[ETH_ALEN];
	u8 ip_type;
	पूर्णांक state;
	रुको_queue_head_t ofld_रुको;
	रुको_queue_head_t tcp_ofld_रुको;
	u32 iscsi_cid;
	/* identअगरier of the connection from qed */
	u32 handle;
	u32 fw_cid;
	व्योम __iomem *p_करोorbell;

	/* Send queue management */
	काष्ठा iscsi_wqe *sq;
	dma_addr_t sq_dma;

	u16 sq_prod_idx;
	u16 fw_sq_prod_idx;
	u16 sq_con_idx;
	u32 sq_mem_size;

	व्योम *sq_pbl;
	dma_addr_t sq_pbl_dma;
	u32 sq_pbl_size;
	काष्ठा qedi_conn *conn;
	काष्ठा work_काष्ठा offload_work;
पूर्ण;

#घोषणा QEDI_SQ_WQES_MIN	16

काष्ठा qedi_io_bdt अणु
	काष्ठा scsi_sge *sge_tbl;
	dma_addr_t sge_tbl_dma;
	u16 sge_valid;
पूर्ण;

/**
 * काष्ठा generic_pdu_resc - login pdu resource काष्ठाure
 *
 * @req_buf:            driver buffer used to stage payload associated with
 *                      the login request
 * @req_dma_addr:       dma address क्रम iscsi login request payload buffer
 * @req_buf_size:       actual login request payload length
 * @req_wr_ptr:         poपूर्णांकer पूर्णांकo login request buffer when next data is
 *                      to be written
 * @resp_hdr:           iscsi header where iscsi login response header is to
 *                      be recreated
 * @resp_buf:           buffer to stage login response payload
 * @resp_dma_addr:      login response payload buffer dma address
 * @resp_buf_size:      login response paylod length
 * @resp_wr_ptr:        poपूर्णांकer पूर्णांकo login response buffer when next data is
 *                      to be written
 * @req_bd_tbl:         iscsi login request payload BD table
 * @req_bd_dma:         login request BD table dma address
 * @resp_bd_tbl:        iscsi login response payload BD table
 * @resp_bd_dma:        login request BD table dma address
 *
 * following काष्ठाure defines buffer info क्रम generic pdus such as iSCSI Login,
 *      Logout and NOP
 */
काष्ठा generic_pdu_resc अणु
	अक्षर *req_buf;
	dma_addr_t req_dma_addr;
	u32 req_buf_size;
	अक्षर *req_wr_ptr;
	काष्ठा iscsi_hdr resp_hdr;
	अक्षर *resp_buf;
	dma_addr_t resp_dma_addr;
	u32 resp_buf_size;
	अक्षर *resp_wr_ptr;
	अक्षर *req_bd_tbl;
	dma_addr_t req_bd_dma;
	अक्षर *resp_bd_tbl;
	dma_addr_t resp_bd_dma;
पूर्ण;

काष्ठा qedi_conn अणु
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा qedi_ctx *qedi;
	काष्ठा qedi_endpoपूर्णांक *ep;
	काष्ठा iscsi_endpoपूर्णांक *iscsi_ep;
	काष्ठा list_head active_cmd_list;
	spinlock_t list_lock;		/* पूर्णांकernal conn lock */
	u32 active_cmd_count;
	u32 cmd_cleanup_req;
	u32 cmd_cleanup_cmpl;

	u32 iscsi_conn_id;
	पूर्णांक itt;
	पूर्णांक abrt_conn;
#घोषणा QEDI_CID_RESERVED	0x5AFF
	u32 fw_cid;
	/*
	 * Buffer क्रम login negotiation process
	 */
	काष्ठा generic_pdu_resc gen_pdu;

	काष्ठा list_head पंचांगf_work_list;
	रुको_queue_head_t रुको_queue;
	spinlock_t पंचांगf_work_lock;	/* पंचांगf work lock */
	अचिन्हित दीर्घ flags;
#घोषणा QEDI_CONN_FW_CLEANUP	1
पूर्ण;

काष्ठा qedi_cmd अणु
	काष्ठा list_head io_cmd;
	bool io_cmd_in_list;
	काष्ठा iscsi_hdr hdr;
	काष्ठा qedi_conn *conn;
	काष्ठा scsi_cmnd *scsi_cmd;
	काष्ठा scatterlist *sg;
	काष्ठा qedi_io_bdt io_tbl;
	काष्ठा e4_iscsi_task_context request;
	अचिन्हित अक्षर *sense_buffer;
	dma_addr_t sense_buffer_dma;
	u16 task_id;

	/* field populated क्रम पंचांगf work queue */
	काष्ठा iscsi_task *task;
	काष्ठा work_काष्ठा पंचांगf_work;
	पूर्णांक state;
#घोषणा CLEANUP_WAIT	1
#घोषणा CLEANUP_RECV	2
#घोषणा CLEANUP_WAIT_FAILED	3
#घोषणा CLEANUP_NOT_REQUIRED	4
#घोषणा LUN_RESET_RESPONSE_RECEIVED	5
#घोषणा RESPONSE_RECEIVED	6

	पूर्णांक type;
#घोषणा TYPEIO		1
#घोषणा TYPERESET	2

	काष्ठा qedi_work_map *list_पंचांगf_work;
	/* slowpath management */
	bool use_slowpath;

	काष्ठा iscsi_पंचांग_rsp *पंचांगf_resp_buf;
	काष्ठा qedi_work cqe_work;
पूर्ण;

काष्ठा qedi_work_map अणु
	काष्ठा list_head list;
	काष्ठा qedi_cmd *qedi_cmd;
	पूर्णांक rtid;

	पूर्णांक state;
#घोषणा QEDI_WORK_QUEUED	1
#घोषणा QEDI_WORK_SCHEDULED	2
#घोषणा QEDI_WORK_EXIT		3

	काष्ठा work_काष्ठा *ptr_पंचांगf_work;
पूर्ण;

काष्ठा qedi_boot_target अणु
	अक्षर ip_addr[64];
	अक्षर iscsi_name[255];
	u32 ipv6_en;
पूर्ण;

#घोषणा qedi_set_itt(task_id, itt) ((u32)(((task_id) & 0xffff) | ((itt) << 16)))
#घोषणा qedi_get_itt(cqe) (cqe.iscsi_hdr.cmd.itt >> 16)

#घोषणा QEDI_OFLD_WAIT_STATE(q) ((q)->state == EP_STATE_OFLDCONN_FAILED || \
				(q)->state == EP_STATE_OFLDCONN_COMPL)

#पूर्ण_अगर /* _QEDI_ISCSI_H_ */
