<शैली गुरु>
/*
 * Copyright (c) 2006 - 2009 Mellanox Technology Inc.  All rights reserved.
 * Copyright (C) 2009 - 2010 Bart Van Assche <bvanassche@acm.org>.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#अगर_अघोषित IB_SRPT_H
#घोषणा IB_SRPT_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_sa.h>
#समावेश <rdma/ib_cm.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/rw.h>

#समावेश <scsi/srp.h>

#समावेश "ib_dm_mad.h"

/*
 * The prefix the ServiceName field must start with in the device management
 * ServiceEntries attribute pair. See also the SRP specअगरication.
 */
#घोषणा SRP_SERVICE_NAME_PREFIX		"SRP.T10:"

काष्ठा srpt_nexus;

क्रमागत अणु
	/*
	 * SRP IOControllerProfile attributes क्रम SRP target ports that have
	 * not been defined in <scsi/srp.h>. Source: section B.7, table B.7
	 * in the SRP specअगरication.
	 */
	SRP_PROTOCOL = 0x0108,
	SRP_PROTOCOL_VERSION = 0x0001,
	SRP_IO_SUBCLASS = 0x609e,
	SRP_SEND_TO_IOC = 0x01,
	SRP_SEND_FROM_IOC = 0x02,
	SRP_RDMA_READ_FROM_IOC = 0x08,
	SRP_RDMA_WRITE_FROM_IOC = 0x20,

	/*
	 * srp_login_cmd.req_flags biपंचांगasks. See also table 9 in the SRP
	 * specअगरication.
	 */
	SRP_MTCH_ACTION = 0x03, /* MULTI-CHANNEL ACTION */
	SRP_LOSOLNT = 0x10, /* logout solicited notअगरication */
	SRP_CRSOLNT = 0x20, /* credit request solicited notअगरication */
	SRP_AESOLNT = 0x40, /* asynchronous event solicited notअगरication */

	/*
	 * srp_cmd.sol_nt / srp_tsk_mgmt.sol_not biपंचांगasks. See also tables
	 * 18 and 20 in the SRP specअगरication.
	 */
	SRP_SCSOLNT = 0x02, /* SCSOLNT = successful solicited notअगरication */
	SRP_UCSOLNT = 0x04, /* UCSOLNT = unsuccessful solicited notअगरication */

	/*
	 * srp_rsp.sol_not / srp_t_logout.sol_not biपंचांगasks. See also tables
	 * 16 and 22 in the SRP specअगरication.
	 */
	SRP_SOLNT = 0x01, /* SOLNT = solicited notअगरication */

	/* See also table 24 in the SRP specअगरication. */
	SRP_TSK_MGMT_SUCCESS = 0x00,
	SRP_TSK_MGMT_FUNC_NOT_SUPP = 0x04,
	SRP_TSK_MGMT_FAILED = 0x05,

	/* See also table 21 in the SRP specअगरication. */
	SRP_CMD_SIMPLE_Q = 0x0,
	SRP_CMD_HEAD_OF_Q = 0x1,
	SRP_CMD_ORDERED_Q = 0x2,
	SRP_CMD_ACA = 0x4,

	SRPT_DEF_SG_TABLESIZE = 128,

	MIN_SRPT_SQ_SIZE = 16,
	DEF_SRPT_SQ_SIZE = 4096,
	MAX_SRPT_RQ_SIZE = 128,
	MIN_SRPT_SRQ_SIZE = 4,
	DEFAULT_SRPT_SRQ_SIZE = 4095,
	MAX_SRPT_SRQ_SIZE = 65535,
	MAX_SRPT_RDMA_SIZE = 1U << 24,
	MAX_SRPT_RSP_SIZE = 1024,

	SRP_MAX_ADD_CDB_LEN = 16,
	SRP_MAX_IMM_DATA_OFFSET = 80,
	SRP_MAX_IMM_DATA = 8 * 1024,
	MIN_MAX_REQ_SIZE = 996,
	DEFAULT_MAX_REQ_SIZE_1 = माप(काष्ठा srp_cmd)/*48*/ +
				 SRP_MAX_ADD_CDB_LEN +
				 माप(काष्ठा srp_indirect_buf)/*20*/ +
				 128 * माप(काष्ठा srp_direct_buf)/*16*/,
	DEFAULT_MAX_REQ_SIZE_2 = SRP_MAX_IMM_DATA_OFFSET +
				 माप(काष्ठा srp_imm_buf) + SRP_MAX_IMM_DATA,
	DEFAULT_MAX_REQ_SIZE = DEFAULT_MAX_REQ_SIZE_1 > DEFAULT_MAX_REQ_SIZE_2 ?
			       DEFAULT_MAX_REQ_SIZE_1 : DEFAULT_MAX_REQ_SIZE_2,

	MIN_MAX_RSP_SIZE = माप(काष्ठा srp_rsp)/*36*/ + 4,
	DEFAULT_MAX_RSP_SIZE = 256, /* leaves 220 bytes क्रम sense data */

	DEFAULT_MAX_RDMA_SIZE = 65536,
पूर्ण;

/**
 * क्रमागत srpt_command_state - SCSI command state managed by SRPT
 * @SRPT_STATE_NEW:           New command arrived and is being processed.
 * @SRPT_STATE_NEED_DATA:     Processing a ग_लिखो or bidir command and रुकोing
 *                            क्रम data arrival.
 * @SRPT_STATE_DATA_IN:       Data क्रम the ग_लिखो or bidir command arrived and is
 *                            being processed.
 * @SRPT_STATE_CMD_RSP_SENT:  SRP_RSP क्रम SRP_CMD has been sent.
 * @SRPT_STATE_MGMT:          Processing a SCSI task management command.
 * @SRPT_STATE_MGMT_RSP_SENT: SRP_RSP क्रम SRP_TSK_MGMT has been sent.
 * @SRPT_STATE_DONE:          Command processing finished successfully, command
 *                            processing has been पातed or command processing
 *                            failed.
 */
क्रमागत srpt_command_state अणु
	SRPT_STATE_NEW		 = 0,
	SRPT_STATE_NEED_DATA	 = 1,
	SRPT_STATE_DATA_IN	 = 2,
	SRPT_STATE_CMD_RSP_SENT	 = 3,
	SRPT_STATE_MGMT		 = 4,
	SRPT_STATE_MGMT_RSP_SENT = 5,
	SRPT_STATE_DONE		 = 6,
पूर्ण;

/**
 * काष्ठा srpt_ioctx - shared SRPT I/O context inक्रमmation
 * @cqe:   Completion queue element.
 * @buf:   Poपूर्णांकer to the buffer.
 * @dma:   DMA address of the buffer.
 * @offset: Offset of the first byte in @buf and @dma that is actually used.
 * @index: Index of the I/O context in its ioctx_ring array.
 */
काष्ठा srpt_ioctx अणु
	काष्ठा ib_cqe		cqe;
	व्योम			*buf;
	dma_addr_t		dma;
	uपूर्णांक32_t		offset;
	uपूर्णांक32_t		index;
पूर्ण;

/**
 * काष्ठा srpt_recv_ioctx - SRPT receive I/O context
 * @ioctx:     See above.
 * @रुको_list: Node क्रम insertion in srpt_rdma_ch.cmd_रुको_list.
 * @byte_len:  Number of bytes in @ioctx.buf.
 */
काष्ठा srpt_recv_ioctx अणु
	काष्ठा srpt_ioctx	ioctx;
	काष्ठा list_head	रुको_list;
	पूर्णांक			byte_len;
पूर्ण;

काष्ठा srpt_rw_ctx अणु
	काष्ठा rdma_rw_ctx	rw;
	काष्ठा scatterlist	*sg;
	अचिन्हित पूर्णांक		nents;
पूर्ण;

/**
 * काष्ठा srpt_send_ioctx - SRPT send I/O context
 * @ioctx:       See above.
 * @ch:          Channel poपूर्णांकer.
 * @recv_ioctx:  Receive I/O context associated with this send I/O context.
 *		 Only used क्रम processing immediate data.
 * @s_rw_ctx:    @rw_ctxs poपूर्णांकs here अगर only a single rw_ctx is needed.
 * @rw_ctxs:     RDMA पढ़ो/ग_लिखो contexts.
 * @imm_sg:      Scatterlist क्रम immediate data.
 * @rdma_cqe:    RDMA completion queue element.
 * @state:       I/O context state.
 * @cmd:         Target core command data काष्ठाure.
 * @sense_data:  SCSI sense data.
 * @n_rdma:      Number of work requests needed to transfer this ioctx.
 * @n_rw_ctx:    Size of rw_ctxs array.
 * @queue_status_only: Send a SCSI status back to the initiator but no data.
 * @sense_data:  Sense data to be sent to the initiator.
 */
काष्ठा srpt_send_ioctx अणु
	काष्ठा srpt_ioctx	ioctx;
	काष्ठा srpt_rdma_ch	*ch;
	काष्ठा srpt_recv_ioctx	*recv_ioctx;

	काष्ठा srpt_rw_ctx	s_rw_ctx;
	काष्ठा srpt_rw_ctx	*rw_ctxs;

	काष्ठा scatterlist	imm_sg;

	काष्ठा ib_cqe		rdma_cqe;
	क्रमागत srpt_command_state	state;
	काष्ठा se_cmd		cmd;
	u8			n_rdma;
	u8			n_rw_ctx;
	bool			queue_status_only;
	u8			sense_data[TRANSPORT_SENSE_BUFFER];
पूर्ण;

/**
 * क्रमागत rdma_ch_state - SRP channel state
 * @CH_CONNECTING:    QP is in RTR state; रुकोing क्रम RTU.
 * @CH_LIVE:	      QP is in RTS state.
 * @CH_DISCONNECTING: DREQ has been sent and रुकोing क्रम DREP or DREQ has
 *                    been received.
 * @CH_DRAINING:      DREP has been received or रुकोing क्रम DREP समयd out
 *                    and last work request has been queued.
 * @CH_DISCONNECTED:  Last completion has been received.
 */
क्रमागत rdma_ch_state अणु
	CH_CONNECTING,
	CH_LIVE,
	CH_DISCONNECTING,
	CH_DRAINING,
	CH_DISCONNECTED,
पूर्ण;

/**
 * काष्ठा srpt_rdma_ch - RDMA channel
 * @nexus:         I_T nexus this channel is associated with.
 * @qp:            IB queue pair used क्रम communicating over this channel.
 * @ib_cm:	   See below.
 * @ib_cm.cm_id:   IB CM ID associated with the channel.
 * @rdma_cm:	   See below.
 * @rdma_cm.cm_id: RDMA CM ID associated with the channel.
 * @cq:            IB completion queue क्रम this channel.
 * @cq_size:	   Number of CQEs in @cq.
 * @zw_cqe:	   Zero-length ग_लिखो CQE.
 * @rcu:           RCU head.
 * @kref:	   kref क्रम this channel.
 * @बंदd:	   Completion object that will be संकेतed as soon as a new
 *		   channel object with the same identity can be created.
 * @rq_size:       IB receive queue size.
 * @max_rsp_size:  Maximum size of an RSP response message in bytes.
 * @sq_wr_avail:   number of work requests available in the send queue.
 * @sport:         poपूर्णांकer to the inक्रमmation of the HCA port used by this
 *                 channel.
 * @max_ti_iu_len: maximum target-to-initiator inक्रमmation unit length.
 * @req_lim:       request limit: maximum number of requests that may be sent
 *                 by the initiator without having received a response.
 * @req_lim_delta: Number of credits not yet sent back to the initiator.
 * @imm_data_offset: Offset from start of SRP_CMD क्रम immediate data.
 * @spinlock:      Protects मुक्त_list and state.
 * @state:         channel state. See also क्रमागत rdma_ch_state.
 * @using_rdma_cm: Whether the RDMA/CM or IB/CM is used क्रम this channel.
 * @processing_रुको_list: Whether or not cmd_रुको_list is being processed.
 * @rsp_buf_cache: kmem_cache क्रम @ioctx_ring.
 * @ioctx_ring:    Send ring.
 * @req_buf_cache: kmem_cache क्रम @ioctx_recv_ring.
 * @ioctx_recv_ring: Receive I/O context ring.
 * @list:          Node in srpt_nexus.ch_list.
 * @cmd_रुको_list: List of SCSI commands that arrived beक्रमe the RTU event. This
 *                 list contains काष्ठा srpt_ioctx elements and is रक्षित
 *                 against concurrent modअगरication by the cm_id spinlock.
 * @pkey:          P_Key of the IB partition क्रम this SRP channel.
 * @sess:          Session inक्रमmation associated with this SRP channel.
 * @sess_name:     Session name.
 * @release_work:  Allows scheduling of srpt_release_channel().
 */
काष्ठा srpt_rdma_ch अणु
	काष्ठा srpt_nexus	*nexus;
	काष्ठा ib_qp		*qp;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा ib_cm_id		*cm_id;
		पूर्ण ib_cm;
		काष्ठा अणु
			काष्ठा rdma_cm_id	*cm_id;
		पूर्ण rdma_cm;
	पूर्ण;
	काष्ठा ib_cq		*cq;
	u32			cq_size;
	काष्ठा ib_cqe		zw_cqe;
	काष्ठा rcu_head		rcu;
	काष्ठा kref		kref;
	काष्ठा completion	*बंदd;
	पूर्णांक			rq_size;
	u32			max_rsp_size;
	atomic_t		sq_wr_avail;
	काष्ठा srpt_port	*sport;
	पूर्णांक			max_ti_iu_len;
	atomic_t		req_lim;
	atomic_t		req_lim_delta;
	u16			imm_data_offset;
	spinlock_t		spinlock;
	क्रमागत rdma_ch_state	state;
	काष्ठा kmem_cache	*rsp_buf_cache;
	काष्ठा srpt_send_ioctx	**ioctx_ring;
	काष्ठा kmem_cache	*req_buf_cache;
	काष्ठा srpt_recv_ioctx	**ioctx_recv_ring;
	काष्ठा list_head	list;
	काष्ठा list_head	cmd_रुको_list;
	uपूर्णांक16_t		pkey;
	bool			using_rdma_cm;
	bool			processing_रुको_list;
	काष्ठा se_session	*sess;
	u8			sess_name[40];
	काष्ठा work_काष्ठा	release_work;
पूर्ण;

/**
 * काष्ठा srpt_nexus - I_T nexus
 * @rcu:       RCU head क्रम this data काष्ठाure.
 * @entry:     srpt_port.nexus_list list node.
 * @ch_list:   काष्ठा srpt_rdma_ch list. Protected by srpt_port.mutex.
 * @i_port_id: 128-bit initiator port identअगरier copied from SRP_LOGIN_REQ.
 * @t_port_id: 128-bit target port identअगरier copied from SRP_LOGIN_REQ.
 */
काष्ठा srpt_nexus अणु
	काष्ठा rcu_head		rcu;
	काष्ठा list_head	entry;
	काष्ठा list_head	ch_list;
	u8			i_port_id[16];
	u8			t_port_id[16];
पूर्ण;

/**
 * काष्ठा srpt_port_attrib - attributes क्रम SRPT port
 * @srp_max_rdma_size: Maximum size of SRP RDMA transfers क्रम new connections.
 * @srp_max_rsp_size: Maximum size of SRP response messages in bytes.
 * @srp_sq_size: Shared receive queue (SRQ) size.
 * @use_srq: Whether or not to use SRQ.
 */
काष्ठा srpt_port_attrib अणु
	u32			srp_max_rdma_size;
	u32			srp_max_rsp_size;
	u32			srp_sq_size;
	bool			use_srq;
पूर्ण;

/**
 * काष्ठा srpt_tpg - inक्रमmation about a single "target portal group"
 * @entry:	Entry in @sport_id->tpg_list.
 * @sport_id:	Port name this TPG is associated with.
 * @tpg:	LIO TPG data काष्ठाure.
 *
 * Zero or more target portal groups are associated with each port name
 * (srpt_port_id). With each TPG an ACL list is associated.
 */
काष्ठा srpt_tpg अणु
	काष्ठा list_head	entry;
	काष्ठा srpt_port_id	*sport_id;
	काष्ठा se_portal_group	tpg;
पूर्ण;

/**
 * काष्ठा srpt_port_id - inक्रमmation about an RDMA port name
 * @mutex:	Protects @tpg_list changes.
 * @tpg_list:	TPGs associated with the RDMA port name.
 * @wwn:	WWN associated with the RDMA port name.
 * @name:	ASCII representation of the port name.
 *
 * Multiple sysfs directories can be associated with a single RDMA port. This
 * data काष्ठाure represents a single (port, name) pair.
 */
काष्ठा srpt_port_id अणु
	काष्ठा mutex		mutex;
	काष्ठा list_head	tpg_list;
	काष्ठा se_wwn		wwn;
	अक्षर			name[64];
पूर्ण;

/**
 * काष्ठा srpt_port - inक्रमmation associated by SRPT with a single IB port
 * @sdev:      backpoपूर्णांकer to the HCA inक्रमmation.
 * @mad_agent: per-port management datagram processing inक्रमmation.
 * @enabled:   Whether or not this target port is enabled.
 * @port:      one-based port number.
 * @sm_lid:    cached value of the port's sm_lid.
 * @lid:       cached value of the port's lid.
 * @gid:       cached value of the port's gid.
 * @work:      work काष्ठाure क्रम refreshing the aक्रमementioned cached values.
 * @port_guid_id: target port GUID
 * @port_gid_id: target port GID
 * @port_attrib:   Port attributes that can be accessed through configfs.
 * @refcount:	   Number of objects associated with this port.
 * @मुक्तd_channels: Completion that will be संकेतed once @refcount becomes 0.
 * @mutex:	   Protects nexus_list.
 * @nexus_list:	   Nexus list. See also srpt_nexus.entry.
 */
काष्ठा srpt_port अणु
	काष्ठा srpt_device	*sdev;
	काष्ठा ib_mad_agent	*mad_agent;
	bool			enabled;
	u8			port;
	u32			sm_lid;
	u32			lid;
	जोड़ ib_gid		gid;
	काष्ठा work_काष्ठा	work;
	काष्ठा srpt_port_id	port_guid_id;
	काष्ठा srpt_port_id	port_gid_id;
	काष्ठा srpt_port_attrib port_attrib;
	atomic_t		refcount;
	काष्ठा completion	*मुक्तd_channels;
	काष्ठा mutex		mutex;
	काष्ठा list_head	nexus_list;
पूर्ण;

/**
 * काष्ठा srpt_device - inक्रमmation associated by SRPT with a single HCA
 * @device:        Backpoपूर्णांकer to the काष्ठा ib_device managed by the IB core.
 * @pd:            IB protection करोमुख्य.
 * @lkey:          L_Key (local key) with ग_लिखो access to all local memory.
 * @srq:           Per-HCA SRQ (shared receive queue).
 * @cm_id:         Connection identअगरier.
 * @srq_size:      SRQ size.
 * @sdev_mutex:	   Serializes use_srq changes.
 * @use_srq:       Whether or not to use SRQ.
 * @req_buf_cache: kmem_cache क्रम @ioctx_ring buffers.
 * @ioctx_ring:    Per-HCA SRQ.
 * @event_handler: Per-HCA asynchronous IB event handler.
 * @list:          Node in srpt_dev_list.
 * @port:          Inक्रमmation about the ports owned by this HCA.
 */
काष्ठा srpt_device अणु
	काष्ठा ib_device	*device;
	काष्ठा ib_pd		*pd;
	u32			lkey;
	काष्ठा ib_srq		*srq;
	काष्ठा ib_cm_id		*cm_id;
	पूर्णांक			srq_size;
	काष्ठा mutex		sdev_mutex;
	bool			use_srq;
	काष्ठा kmem_cache	*req_buf_cache;
	काष्ठा srpt_recv_ioctx	**ioctx_ring;
	काष्ठा ib_event_handler	event_handler;
	काष्ठा list_head	list;
	काष्ठा srpt_port        port[];
पूर्ण;

#पूर्ण_अगर				/* IB_SRPT_H */
