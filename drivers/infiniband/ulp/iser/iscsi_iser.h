<शैली गुरु>
/*
 * iSER transport क्रम the Open iSCSI Initiator & iSER transport पूर्णांकernals
 *
 * Copyright (C) 2004 Dmitry Yusupov
 * Copyright (C) 2004 Alex Aizman
 * Copyright (C) 2005 Mike Christie
 * based on code मुख्यtained by खोलो-iscsi@googlegroups.com
 *
 * Copyright (c) 2004, 2005, 2006 Voltaire, Inc. All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
 * Copyright (c) 2013-2014 Mellanox Technologies. All rights reserved.
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
 *	- Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *	- Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#अगर_अघोषित __ISCSI_ISER_H__
#घोषणा __ISCSI_ISER_H__

#समावेश <linux/types.h>
#समावेश <linux/net.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <scsi/libiscsi.h>
#समावेश <scsi/scsi_transport_iscsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/iser.h>

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mempool.h>
#समावेश <linux/uपन.स>

#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>

#घोषणा DRV_NAME	"iser"
#घोषणा PFX		DRV_NAME ": "
#घोषणा DRV_VER		"1.6"

#घोषणा iser_dbg(fmt, arg...)				 \
	करो अणु						 \
		अगर (unlikely(iser_debug_level > 2))	 \
			prपूर्णांकk(KERN_DEBUG PFX "%s: " fmt,\
				__func__ , ## arg);	 \
	पूर्ण जबतक (0)

#घोषणा iser_warn(fmt, arg...)				\
	करो अणु						\
		अगर (unlikely(iser_debug_level > 0))	\
			pr_warn(PFX "%s: " fmt,		\
				__func__ , ## arg);	\
	पूर्ण जबतक (0)

#घोषणा iser_info(fmt, arg...)				\
	करो अणु						\
		अगर (unlikely(iser_debug_level > 1))	\
			pr_info(PFX "%s: " fmt,		\
				__func__ , ## arg);	\
	पूर्ण जबतक (0)

#घोषणा iser_err(fmt, arg...) \
	pr_err(PFX "%s: " fmt, __func__ , ## arg)

/* Default support is 512KB I/O size */
#घोषणा ISER_DEF_MAX_SECTORS		1024
#घोषणा ISCSI_ISER_DEF_SG_TABLESIZE                                            \
	((ISER_DEF_MAX_SECTORS * SECTOR_SIZE) >> ilog2(SZ_4K))
/* Maximum support is 16MB I/O size */
#घोषणा ISCSI_ISER_MAX_SG_TABLESIZE ((32768 * SECTOR_SIZE) >> ilog2(SZ_4K))

#घोषणा ISER_DEF_XMIT_CMDS_DEFAULT		512
#अगर ISCSI_DEF_XMIT_CMDS_MAX > ISER_DEF_XMIT_CMDS_DEFAULT
	#घोषणा ISER_DEF_XMIT_CMDS_MAX		ISCSI_DEF_XMIT_CMDS_MAX
#अन्यथा
	#घोषणा ISER_DEF_XMIT_CMDS_MAX		ISER_DEF_XMIT_CMDS_DEFAULT
#पूर्ण_अगर
#घोषणा ISER_DEF_CMD_PER_LUN		ISER_DEF_XMIT_CMDS_MAX

/* QP settings */
/* Maximal bounds on received asynchronous PDUs */
#घोषणा ISER_MAX_RX_MISC_PDUS		4 /* NOOP_IN(2) , ASYNC_EVENT(2)   */

#घोषणा ISER_MAX_TX_MISC_PDUS		6 /* NOOP_OUT(2), TEXT(1),         *
					   * SCSI_TMFUNC(2), LOGOUT(1) */

#घोषणा ISER_QP_MAX_RECV_DTOS		(ISER_DEF_XMIT_CMDS_MAX)

#घोषणा ISER_MIN_POSTED_RX		(ISER_DEF_XMIT_CMDS_MAX >> 2)

/* the max TX (send) WR supported by the iSER QP is defined by                 *
 * max_send_wr = T * (1 + D) + C ; D is how many inflight dataouts we expect   *
 * to have at max क्रम SCSI command. The tx posting & completion handling code  *
 * supports -EAGAIN scheme where tx is suspended till the QP has room क्रम more *
 * send WR. D=8 comes from 64K/8K                                              */

#घोषणा ISER_INFLIGHT_DATAOUTS		8

#घोषणा ISER_QP_MAX_REQ_DTOS		(ISER_DEF_XMIT_CMDS_MAX *    \
					(1 + ISER_INFLIGHT_DATAOUTS) + \
					ISER_MAX_TX_MISC_PDUS        + \
					ISER_MAX_RX_MISC_PDUS)

/* Max registration work requests per command */
#घोषणा ISER_MAX_REG_WR_PER_CMD		5

/* For Signature we करोn't support DATAOUTs so no need to make room क्रम them */
#घोषणा ISER_QP_SIG_MAX_REQ_DTOS	(ISER_DEF_XMIT_CMDS_MAX	*       \
					(1 + ISER_MAX_REG_WR_PER_CMD) + \
					ISER_MAX_TX_MISC_PDUS         + \
					ISER_MAX_RX_MISC_PDUS)

#घोषणा ISER_GET_MAX_XMIT_CMDS(send_wr) ((send_wr			\
					 - ISER_MAX_TX_MISC_PDUS	\
					 - ISER_MAX_RX_MISC_PDUS) /	\
					 (1 + ISER_INFLIGHT_DATAOUTS))

#घोषणा ISER_SIGNAL_CMD_COUNT 32

/* Constant PDU lengths calculations */
#घोषणा ISER_HEADERS_LEN	(माप(काष्ठा iser_ctrl) + माप(काष्ठा iscsi_hdr))

#घोषणा ISER_RECV_DATA_SEG_LEN	128
#घोषणा ISER_RX_PAYLOAD_SIZE	(ISER_HEADERS_LEN + ISER_RECV_DATA_SEG_LEN)
#घोषणा ISER_RX_LOGIN_SIZE	(ISER_HEADERS_LEN + ISCSI_DEF_MAX_RECV_SEG_LEN)

/* Length of an object name string */
#घोषणा ISER_OBJECT_NAME_SIZE		    64

क्रमागत iser_conn_state अणु
	ISER_CONN_INIT,		   /* descriptor allocd, no conn          */
	ISER_CONN_PENDING,	   /* in the process of being established */
	ISER_CONN_UP,		   /* up and running                      */
	ISER_CONN_TERMINATING,	   /* in the process of being terminated  */
	ISER_CONN_DOWN,		   /* shut करोwn                           */
	ISER_CONN_STATES_NUM
पूर्ण;

क्रमागत iser_task_status अणु
	ISER_TASK_STATUS_INIT = 0,
	ISER_TASK_STATUS_STARTED,
	ISER_TASK_STATUS_COMPLETED
पूर्ण;

क्रमागत iser_data_dir अणु
	ISER_सूची_IN = 0,	   /* to initiator */
	ISER_सूची_OUT,		   /* from initiator */
	ISER_सूचीS_NUM
पूर्ण;

/**
 * काष्ठा iser_data_buf - iSER data buffer
 *
 * @sg:           poपूर्णांकer to the sg list
 * @size:         num entries of this sg
 * @data_len:     total beffer byte len
 * @dma_nents:    वापसed by dma_map_sg
 */
काष्ठा iser_data_buf अणु
	काष्ठा scatterlist *sg;
	पूर्णांक                size;
	अचिन्हित दीर्घ      data_len;
	पूर्णांक                dma_nents;
पूर्ण;

/* fwd declarations */
काष्ठा iser_device;
काष्ठा iscsi_iser_task;
काष्ठा iscsi_endpoपूर्णांक;
काष्ठा iser_reg_resources;

/**
 * काष्ठा iser_mem_reg - iSER memory registration info
 *
 * @sge:          memory region sg element
 * @rkey:         memory region remote key
 * @mem_h:        poपूर्णांकer to registration context (FMR/Fastreg)
 */
काष्ठा iser_mem_reg अणु
	काष्ठा ib_sge	 sge;
	u32		 rkey;
	व्योम		*mem_h;
पूर्ण;

क्रमागत iser_desc_type अणु
	ISCSI_TX_CONTROL ,
	ISCSI_TX_SCSI_COMMAND,
	ISCSI_TX_DATAOUT
पूर्ण;

/**
 * काष्ठा iser_tx_desc - iSER TX descriptor
 *
 * @iser_header:   iser header
 * @iscsi_header:  iscsi header
 * @type:          command/control/dataout
 * @dma_addr:      header buffer dma_address
 * @tx_sg:         sg[0] poपूर्णांकs to iser/iscsi headers
 *                 sg[1] optionally poपूर्णांकs to either of immediate data
 *                 unsolicited data-out or control
 * @num_sge:       number sges used on this TX task
 * @cqe:           completion handler
 * @mapped:        Is the task header mapped
 * @reg_wr:        registration WR
 * @send_wr:       send WR
 * @inv_wr:        invalidate WR
 */
काष्ठा iser_tx_desc अणु
	काष्ठा iser_ctrl             iser_header;
	काष्ठा iscsi_hdr             iscsi_header;
	क्रमागत   iser_desc_type        type;
	u64		             dma_addr;
	काष्ठा ib_sge		     tx_sg[2];
	पूर्णांक                          num_sge;
	काष्ठा ib_cqe		     cqe;
	bool			     mapped;
	काष्ठा ib_reg_wr	     reg_wr;
	काष्ठा ib_send_wr	     send_wr;
	काष्ठा ib_send_wr	     inv_wr;
पूर्ण;

#घोषणा ISER_RX_PAD_SIZE	(256 - (ISER_RX_PAYLOAD_SIZE + \
				 माप(u64) + माप(काष्ठा ib_sge) + \
				 माप(काष्ठा ib_cqe)))
/**
 * काष्ठा iser_rx_desc - iSER RX descriptor
 *
 * @iser_header:   iser header
 * @iscsi_header:  iscsi header
 * @data:          received data segment
 * @dma_addr:      receive buffer dma address
 * @rx_sg:         ib_sge of receive buffer
 * @cqe:           completion handler
 * @pad:           क्रम sense data TODO: Modअगरy to maximum sense length supported
 */
काष्ठा iser_rx_desc अणु
	काष्ठा iser_ctrl             iser_header;
	काष्ठा iscsi_hdr             iscsi_header;
	अक्षर		             data[ISER_RECV_DATA_SEG_LEN];
	u64		             dma_addr;
	काष्ठा ib_sge		     rx_sg;
	काष्ठा ib_cqe		     cqe;
	अक्षर		             pad[ISER_RX_PAD_SIZE];
पूर्ण __packed;

/**
 * काष्ठा iser_login_desc - iSER login descriptor
 *
 * @req:           poपूर्णांकer to login request buffer
 * @rsp:           poपूर्णांकer to login response buffer
 * @req_dma:       DMA address of login request buffer
 * @rsp_dma:       DMA address of login response buffer
 * @sge:           IB sge क्रम login post recv
 * @cqe:           completion handler
 */
काष्ठा iser_login_desc अणु
	व्योम                         *req;
	व्योम                         *rsp;
	u64                          req_dma;
	u64                          rsp_dma;
	काष्ठा ib_sge                sge;
	काष्ठा ib_cqe		     cqe;
पूर्ण __packed;

काष्ठा iser_conn;
काष्ठा ib_conn;

/**
 * काष्ठा iser_device - iSER device handle
 *
 * @ib_device:     RDMA device
 * @pd:            Protection Doमुख्य क्रम this device
 * @mr:            Global DMA memory region
 * @event_handler: IB events handle routine
 * @ig_list:	   entry in devices list
 * @refcount:      Reference counter, करोminated by खोलो iser connections
 */
काष्ठा iser_device अणु
	काष्ठा ib_device             *ib_device;
	काष्ठा ib_pd	             *pd;
	काष्ठा ib_event_handler      event_handler;
	काष्ठा list_head             ig_list;
	पूर्णांक                          refcount;
पूर्ण;

/**
 * काष्ठा iser_reg_resources - Fast registration resources
 *
 * @mr:         memory region
 * @sig_mr:     signature memory region
 * @mr_valid:   is mr valid indicator
 */
काष्ठा iser_reg_resources अणु
	काष्ठा ib_mr                     *mr;
	काष्ठा ib_mr                     *sig_mr;
	u8				  mr_valid:1;
पूर्ण;

/**
 * काष्ठा iser_fr_desc - Fast registration descriptor
 *
 * @list:           entry in connection fastreg pool
 * @rsc:            data buffer registration resources
 * @sig_रक्षित:  is region रक्षित indicator
 * @all_list:       first and last list members
 */
काष्ठा iser_fr_desc अणु
	काष्ठा list_head		  list;
	काष्ठा iser_reg_resources	  rsc;
	bool				  sig_रक्षित;
	काष्ठा list_head                  all_list;
पूर्ण;

/**
 * काष्ठा iser_fr_pool - connection fast registration pool
 *
 * @list:                list of fastreg descriptors
 * @lock:                protects fastreg pool
 * @size:                size of the pool
 * @all_list:            first and last list members
 */
काष्ठा iser_fr_pool अणु
	काष्ठा list_head        list;
	spinlock_t              lock;
	पूर्णांक                     size;
	काष्ठा list_head        all_list;
पूर्ण;

/**
 * काष्ठा ib_conn - Infiniband related objects
 *
 * @cma_id:              rdma_cm connection maneger handle
 * @qp:                  Connection Queue-pair
 * @cq:                  Connection completion queue
 * @cq_size:             The number of max outstanding completions
 * @post_recv_buf_count: post receive counter
 * @sig_count:           send work request संकेत count
 * @rx_wr:               receive work request क्रम batch posts
 * @device:              reference to iser device
 * @fr_pool:             connection fast registration poool
 * @pi_support:          Indicate device T10-PI support
 * @reg_cqe:             completion handler
 */
काष्ठा ib_conn अणु
	काष्ठा rdma_cm_id           *cma_id;
	काष्ठा ib_qp	            *qp;
	काष्ठा ib_cq		    *cq;
	u32			    cq_size;
	पूर्णांक                          post_recv_buf_count;
	u8                           sig_count;
	काष्ठा ib_recv_wr	     rx_wr[ISER_MIN_POSTED_RX];
	काष्ठा iser_device          *device;
	काष्ठा iser_fr_pool          fr_pool;
	bool			     pi_support;
	काष्ठा ib_cqe		     reg_cqe;
पूर्ण;

/**
 * काष्ठा iser_conn - iSER connection context
 *
 * @ib_conn:          connection RDMA resources
 * @iscsi_conn:       link to matching iscsi connection
 * @ep:               transport handle
 * @state:            connection logical state
 * @qp_max_recv_dtos: maximum number of data outs, corresponds
 *                    to max number of post recvs
 * @qp_max_recv_dtos_mask: (qp_max_recv_dtos - 1)
 * @min_posted_rx:    (qp_max_recv_dtos >> 2)
 * @max_cmds:         maximum cmds allowed क्रम this connection
 * @name:             connection peer portal
 * @release_work:     deffered work क्रम release job
 * @state_mutex:      protects iser onnection state
 * @stop_completion:  conn_stop completion
 * @ib_completion:    RDMA cleanup completion
 * @up_completion:    connection establishment completed
 *                    (state is ISER_CONN_UP)
 * @conn_list:        entry in ig conn list
 * @login_desc:       login descriptor
 * @rx_desc_head:     head of rx_descs cyclic buffer
 * @rx_descs:         rx buffers array (cyclic buffer)
 * @num_rx_descs:     number of rx descriptors
 * @scsi_sg_tablesize: scsi host sg_tablesize
 * @pages_per_mr:     maximum pages available क्रम registration
 * @snd_w_inv:        connection uses remote invalidation
 */
काष्ठा iser_conn अणु
	काष्ठा ib_conn		     ib_conn;
	काष्ठा iscsi_conn	     *iscsi_conn;
	काष्ठा iscsi_endpoपूर्णांक	     *ep;
	क्रमागत iser_conn_state	     state;
	अचिन्हित		     qp_max_recv_dtos;
	अचिन्हित		     qp_max_recv_dtos_mask;
	अचिन्हित		     min_posted_rx;
	u16                          max_cmds;
	अक्षर 			     name[ISER_OBJECT_NAME_SIZE];
	काष्ठा work_काष्ठा	     release_work;
	काष्ठा mutex		     state_mutex;
	काष्ठा completion	     stop_completion;
	काष्ठा completion	     ib_completion;
	काष्ठा completion	     up_completion;
	काष्ठा list_head	     conn_list;
	काष्ठा iser_login_desc       login_desc;
	अचिन्हित पूर्णांक 		     rx_desc_head;
	काष्ठा iser_rx_desc	     *rx_descs;
	u32                          num_rx_descs;
	अचिन्हित लघु               scsi_sg_tablesize;
	अचिन्हित लघु               pages_per_mr;
	bool			     snd_w_inv;
पूर्ण;

/**
 * काष्ठा iscsi_iser_task - iser task context
 *
 * @desc:     TX descriptor
 * @iser_conn:        link to iser connection
 * @status:           current task status
 * @sc:               link to scsi command
 * @command_sent:     indicate अगर command was sent
 * @dir:              iser data direction
 * @rdma_reg:         task rdma registration desc
 * @data:             iser data buffer desc
 * @prot:             iser protection buffer desc
 */
काष्ठा iscsi_iser_task अणु
	काष्ठा iser_tx_desc          desc;
	काष्ठा iser_conn	     *iser_conn;
	क्रमागत iser_task_status 	     status;
	काष्ठा scsi_cmnd	     *sc;
	पूर्णांक                          command_sent;
	पूर्णांक                          dir[ISER_सूचीS_NUM];
	काष्ठा iser_mem_reg          rdma_reg[ISER_सूचीS_NUM];
	काष्ठा iser_data_buf         data[ISER_सूचीS_NUM];
	काष्ठा iser_data_buf         prot[ISER_सूचीS_NUM];
पूर्ण;

/**
 * काष्ठा iser_global - iSER global context
 *
 * @device_list_mutex:    protects device_list
 * @device_list:          iser devices global list
 * @connlist_mutex:       protects connlist
 * @connlist:             iser connections global list
 * @desc_cache:           kmem cache क्रम tx dataout
 */
काष्ठा iser_global अणु
	काष्ठा mutex      device_list_mutex;
	काष्ठा list_head  device_list;
	काष्ठा mutex      connlist_mutex;
	काष्ठा list_head  connlist;
	काष्ठा kmem_cache *desc_cache;
पूर्ण;

बाह्य काष्ठा iser_global ig;
बाह्य पूर्णांक iser_debug_level;
बाह्य bool iser_pi_enable;
बाह्य पूर्णांक iser_pi_guard;
बाह्य अचिन्हित पूर्णांक iser_max_sectors;
बाह्य bool iser_always_reg;

पूर्णांक iser_send_control(काष्ठा iscsi_conn *conn,
		      काष्ठा iscsi_task *task);

पूर्णांक iser_send_command(काष्ठा iscsi_conn *conn,
		      काष्ठा iscsi_task *task);

पूर्णांक iser_send_data_out(काष्ठा iscsi_conn *conn,
		       काष्ठा iscsi_task *task,
		       काष्ठा iscsi_data *hdr);

व्योम iscsi_iser_recv(काष्ठा iscsi_conn *conn,
		     काष्ठा iscsi_hdr *hdr,
		     अक्षर *rx_data,
		     पूर्णांक rx_data_len);

व्योम iser_conn_init(काष्ठा iser_conn *iser_conn);

व्योम iser_conn_release(काष्ठा iser_conn *iser_conn);

पूर्णांक iser_conn_terminate(काष्ठा iser_conn *iser_conn);

व्योम iser_release_work(काष्ठा work_काष्ठा *work);

व्योम iser_err_comp(काष्ठा ib_wc *wc, स्थिर अक्षर *type);
व्योम iser_login_rsp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
व्योम iser_task_rsp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
व्योम iser_cmd_comp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
व्योम iser_ctrl_comp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
व्योम iser_dataout_comp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
व्योम iser_reg_comp(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);

व्योम iser_task_rdma_init(काष्ठा iscsi_iser_task *task);

व्योम iser_task_rdma_finalize(काष्ठा iscsi_iser_task *task);

व्योम iser_मुक्त_rx_descriptors(काष्ठा iser_conn *iser_conn);

व्योम iser_finalize_rdma_unaligned_sg(काष्ठा iscsi_iser_task *iser_task,
				     काष्ठा iser_data_buf *mem,
				     क्रमागत iser_data_dir cmd_dir);

पूर्णांक iser_reg_mem_fastreg(काष्ठा iscsi_iser_task *task,
			 क्रमागत iser_data_dir dir,
			 bool all_imm);
व्योम iser_unreg_mem_fastreg(काष्ठा iscsi_iser_task *task,
			    क्रमागत iser_data_dir dir);

पूर्णांक  iser_connect(काष्ठा iser_conn *iser_conn,
		  काष्ठा sockaddr *src_addr,
		  काष्ठा sockaddr *dst_addr,
		  पूर्णांक non_blocking);

पूर्णांक  iser_post_recvl(काष्ठा iser_conn *iser_conn);
पूर्णांक  iser_post_recvm(काष्ठा iser_conn *iser_conn, पूर्णांक count);
पूर्णांक  iser_post_send(काष्ठा ib_conn *ib_conn, काष्ठा iser_tx_desc *tx_desc,
		    bool संकेत);

पूर्णांक iser_dma_map_task_data(काष्ठा iscsi_iser_task *iser_task,
			   काष्ठा iser_data_buf *data,
			   क्रमागत iser_data_dir iser_dir,
			   क्रमागत dma_data_direction dma_dir);

व्योम iser_dma_unmap_task_data(काष्ठा iscsi_iser_task *iser_task,
			      काष्ठा iser_data_buf *data,
			      क्रमागत dma_data_direction dir);

पूर्णांक  iser_initialize_task_headers(काष्ठा iscsi_task *task,
			काष्ठा iser_tx_desc *tx_desc);
पूर्णांक iser_alloc_rx_descriptors(काष्ठा iser_conn *iser_conn,
			      काष्ठा iscsi_session *session);
पूर्णांक iser_alloc_fastreg_pool(काष्ठा ib_conn *ib_conn,
			    अचिन्हित cmds_max,
			    अचिन्हित पूर्णांक size);
व्योम iser_मुक्त_fastreg_pool(काष्ठा ib_conn *ib_conn);
u8 iser_check_task_pi_status(काष्ठा iscsi_iser_task *iser_task,
			     क्रमागत iser_data_dir cmd_dir, sector_t *sector);

अटल अंतरभूत काष्ठा iser_conn *
to_iser_conn(काष्ठा ib_conn *ib_conn)
अणु
	वापस container_of(ib_conn, काष्ठा iser_conn, ib_conn);
पूर्ण

अटल अंतरभूत काष्ठा iser_rx_desc *
iser_rx(काष्ठा ib_cqe *cqe)
अणु
	वापस container_of(cqe, काष्ठा iser_rx_desc, cqe);
पूर्ण

अटल अंतरभूत काष्ठा iser_tx_desc *
iser_tx(काष्ठा ib_cqe *cqe)
अणु
	वापस container_of(cqe, काष्ठा iser_tx_desc, cqe);
पूर्ण

अटल अंतरभूत काष्ठा iser_login_desc *
iser_login(काष्ठा ib_cqe *cqe)
अणु
	वापस container_of(cqe, काष्ठा iser_login_desc, cqe);
पूर्ण

#पूर्ण_अगर
