<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
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
*******************************************************************************/

#अगर_अघोषित I40IW_PUDA_H
#घोषणा I40IW_PUDA_H

#घोषणा I40IW_IEQ_MPA_FRAMING 6

काष्ठा i40iw_sc_dev;
काष्ठा i40iw_sc_qp;
काष्ठा i40iw_sc_cq;

क्रमागत puda_resource_type अणु
	I40IW_PUDA_RSRC_TYPE_ILQ = 1,
	I40IW_PUDA_RSRC_TYPE_IEQ
पूर्ण;

क्रमागत puda_rsrc_complete अणु
	PUDA_CQ_CREATED = 1,
	PUDA_QP_CREATED,
	PUDA_TX_COMPLETE,
	PUDA_RX_COMPLETE,
	PUDA_HASH_CRC_COMPLETE
पूर्ण;

काष्ठा i40iw_puda_completion_info अणु
	काष्ठा i40iw_qp_uk *qp;
	u8 q_type;
	u8 vlan_valid;
	u8 l3proto;
	u8 l4proto;
	u16 payload_len;
	u32 compl_error;	/* No_err=0, अन्यथा major and minor err code */
	u32 qp_id;
	u32 wqe_idx;
पूर्ण;

काष्ठा i40iw_puda_send_info अणु
	u64 paddr;		/* Physical address */
	u32 len;
	u8 tcplen;
	u8 maclen;
	bool ipv4;
	bool करोloopback;
	व्योम *scratch;
पूर्ण;

काष्ठा i40iw_puda_buf अणु
	काष्ठा list_head list;	/* MUST be first entry */
	काष्ठा i40iw_dma_mem mem;	/* DMA memory क्रम the buffer */
	काष्ठा i40iw_puda_buf *next;	/* क्रम alloclist in rsrc काष्ठा */
	काष्ठा i40iw_virt_mem buf_mem;	/* Buffer memory क्रम this buffer */
	व्योम *scratch;
	u8 *iph;
	u8 *tcph;
	u8 *data;
	u16 datalen;
	u16 vlan_id;
	u8 tcphlen;		/* tcp length in bytes */
	u8 maclen;		/* mac length in bytes */
	u32 totallen;		/* machlen+iphlen+tcphlen+datalen */
	atomic_t refcount;
	u8 hdrlen;
	bool ipv4;
	u32 seqnum;
पूर्ण;

काष्ठा i40iw_puda_rsrc_info अणु
	क्रमागत puda_resource_type type;	/* ILQ or IEQ */
	u32 count;
	u16 pd_id;
	u32 cq_id;
	u32 qp_id;
	u32 sq_size;
	u32 rq_size;
	u16 buf_size;
	u16 mss;
	u32 tx_buf_cnt;		/* total bufs allocated will be rq_size + tx_buf_cnt */
	व्योम (*receive)(काष्ठा i40iw_sc_vsi *, काष्ठा i40iw_puda_buf *);
	व्योम (*xmit_complete)(काष्ठा i40iw_sc_vsi *, व्योम *);
पूर्ण;

काष्ठा i40iw_puda_rsrc अणु
	काष्ठा i40iw_sc_cq cq;
	काष्ठा i40iw_sc_qp qp;
	काष्ठा i40iw_sc_pd sc_pd;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_sc_vsi *vsi;
	काष्ठा i40iw_dma_mem cqmem;
	काष्ठा i40iw_dma_mem qpmem;
	काष्ठा i40iw_virt_mem ilq_mem;
	क्रमागत puda_rsrc_complete completion;
	क्रमागत puda_resource_type type;
	u16 buf_size;		/*buffer must be max datalen + tcpip hdr + mac */
	u16 mss;
	u32 cq_id;
	u32 qp_id;
	u32 sq_size;
	u32 rq_size;
	u32 cq_size;
	काष्ठा i40iw_sq_uk_wr_trk_info *sq_wrtrk_array;
	u64 *rq_wrid_array;
	u32 compl_rxwqe_idx;
	u32 rx_wqe_idx;
	u32 rxq_invalid_cnt;
	u32 tx_wqe_avail_cnt;
	bool check_crc;
	काष्ठा shash_desc *hash_desc;
	काष्ठा list_head txpend;
	काष्ठा list_head bufpool;	/* मुक्त buffers pool list क्रम recv and xmit */
	u32 alloc_buf_count;
	u32 avail_buf_count;		/* snapshot of currently available buffers */
	spinlock_t bufpool_lock;
	काष्ठा i40iw_puda_buf *alloclist;
	व्योम (*receive)(काष्ठा i40iw_sc_vsi *, काष्ठा i40iw_puda_buf *);
	व्योम (*xmit_complete)(काष्ठा i40iw_sc_vsi *, व्योम *);
	/* puda stats */
	u64 stats_buf_alloc_fail;
	u64 stats_pkt_rcvd;
	u64 stats_pkt_sent;
	u64 stats_rcvd_pkt_err;
	u64 stats_sent_pkt_q;
	u64 stats_bad_qp_id;
पूर्ण;

काष्ठा i40iw_puda_buf *i40iw_puda_get_bufpool(काष्ठा i40iw_puda_rsrc *rsrc);
व्योम i40iw_puda_ret_bufpool(काष्ठा i40iw_puda_rsrc *rsrc,
			    काष्ठा i40iw_puda_buf *buf);
व्योम i40iw_puda_send_buf(काष्ठा i40iw_puda_rsrc *rsrc,
			 काष्ठा i40iw_puda_buf *buf);
क्रमागत i40iw_status_code i40iw_puda_send(काष्ठा i40iw_sc_qp *qp,
				       काष्ठा i40iw_puda_send_info *info);
क्रमागत i40iw_status_code i40iw_puda_create_rsrc(काष्ठा i40iw_sc_vsi *vsi,
					      काष्ठा i40iw_puda_rsrc_info *info);
व्योम i40iw_puda_dele_resources(काष्ठा i40iw_sc_vsi *vsi,
			       क्रमागत puda_resource_type type,
			       bool reset);
क्रमागत i40iw_status_code i40iw_puda_poll_completion(काष्ठा i40iw_sc_dev *dev,
						  काष्ठा i40iw_sc_cq *cq, u32 *compl_err);

काष्ठा i40iw_sc_qp *i40iw_ieq_get_qp(काष्ठा i40iw_sc_dev *dev,
				     काष्ठा i40iw_puda_buf *buf);
क्रमागत i40iw_status_code i40iw_puda_get_tcpip_info(काष्ठा i40iw_puda_completion_info *info,
						 काष्ठा i40iw_puda_buf *buf);
क्रमागत i40iw_status_code i40iw_ieq_check_mpacrc(काष्ठा shash_desc *desc,
					      व्योम *addr, u32 length, u32 value);
क्रमागत i40iw_status_code i40iw_init_hash_desc(काष्ठा shash_desc **desc);
व्योम i40iw_ieq_mpa_crc_ae(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_qp *qp);
व्योम i40iw_मुक्त_hash_desc(काष्ठा shash_desc *desc);
व्योम i40iw_ieq_update_tcpip_info(काष्ठा i40iw_puda_buf *buf, u16 length,
				 u32 seqnum);
क्रमागत i40iw_status_code i40iw_cqp_qp_create_cmd(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_qp *qp);
क्रमागत i40iw_status_code i40iw_cqp_cq_create_cmd(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_cq *cq);
व्योम i40iw_cqp_qp_destroy_cmd(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_qp *qp);
व्योम i40iw_cqp_cq_destroy_cmd(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_cq *cq);
व्योम i40iw_ieq_cleanup_qp(काष्ठा i40iw_puda_rsrc *ieq, काष्ठा i40iw_sc_qp *qp);
#पूर्ण_अगर
