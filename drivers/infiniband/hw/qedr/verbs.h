<शैली गुरु>
/* QLogic qedr NIC Driver
 * Copyright (c) 2015-2016  QLogic Corporation
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
 *        disclaimer in the करोcumentation and /or other materials
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
 */
#अगर_अघोषित __QEDR_VERBS_H__
#घोषणा __QEDR_VERBS_H__

पूर्णांक qedr_query_device(काष्ठा ib_device *ibdev,
		      काष्ठा ib_device_attr *attr, काष्ठा ib_udata *udata);
पूर्णांक qedr_query_port(काष्ठा ib_device *ibdev, u32 port,
		    काष्ठा ib_port_attr *props);

पूर्णांक qedr_iw_query_gid(काष्ठा ib_device *ibdev, u32 port,
		      पूर्णांक index, जोड़ ib_gid *gid);

पूर्णांक qedr_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index, u16 *pkey);

पूर्णांक qedr_alloc_ucontext(काष्ठा ib_ucontext *uctx, काष्ठा ib_udata *udata);
व्योम qedr_dealloc_ucontext(काष्ठा ib_ucontext *uctx);

पूर्णांक qedr_mmap(काष्ठा ib_ucontext *ucontext, काष्ठा vm_area_काष्ठा *vma);
व्योम qedr_mmap_मुक्त(काष्ठा rdma_user_mmap_entry *rdma_entry);
पूर्णांक qedr_alloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
पूर्णांक qedr_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
पूर्णांक qedr_alloc_xrcd(काष्ठा ib_xrcd *ibxrcd, काष्ठा ib_udata *udata);
पूर्णांक qedr_dealloc_xrcd(काष्ठा ib_xrcd *ibxrcd, काष्ठा ib_udata *udata);
पूर्णांक qedr_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		   काष्ठा ib_udata *udata);
पूर्णांक qedr_resize_cq(काष्ठा ib_cq *, पूर्णांक cqe, काष्ठा ib_udata *);
पूर्णांक qedr_destroy_cq(काष्ठा ib_cq *ibcq, काष्ठा ib_udata *udata);
पूर्णांक qedr_arm_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags flags);
काष्ठा ib_qp *qedr_create_qp(काष्ठा ib_pd *, काष्ठा ib_qp_init_attr *attrs,
			     काष्ठा ib_udata *);
पूर्णांक qedr_modअगरy_qp(काष्ठा ib_qp *, काष्ठा ib_qp_attr *attr,
		   पूर्णांक attr_mask, काष्ठा ib_udata *udata);
पूर्णांक qedr_query_qp(काष्ठा ib_qp *, काष्ठा ib_qp_attr *qp_attr,
		  पूर्णांक qp_attr_mask, काष्ठा ib_qp_init_attr *);
पूर्णांक qedr_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata);

पूर्णांक qedr_create_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_init_attr *attr,
		    काष्ठा ib_udata *udata);
पूर्णांक qedr_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		    क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata);
पूर्णांक qedr_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr);
पूर्णांक qedr_destroy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_udata *udata);
पूर्णांक qedr_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
		       स्थिर काष्ठा ib_recv_wr **bad_recv_wr);
पूर्णांक qedr_create_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_init_attr *init_attr,
		   काष्ठा ib_udata *udata);
पूर्णांक qedr_destroy_ah(काष्ठा ib_ah *ibah, u32 flags);

पूर्णांक qedr_dereg_mr(काष्ठा ib_mr *ib_mr, काष्ठा ib_udata *udata);
काष्ठा ib_mr *qedr_get_dma_mr(काष्ठा ib_pd *, पूर्णांक acc);

काष्ठा ib_mr *qedr_reg_user_mr(काष्ठा ib_pd *, u64 start, u64 length,
			       u64 virt, पूर्णांक acc, काष्ठा ib_udata *);

पूर्णांक qedr_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg,
		   पूर्णांक sg_nents, अचिन्हित पूर्णांक *sg_offset);

काष्ठा ib_mr *qedr_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			    u32 max_num_sg);
पूर्णांक qedr_poll_cq(काष्ठा ib_cq *, पूर्णांक num_entries, काष्ठा ib_wc *wc);
पूर्णांक qedr_post_send(काष्ठा ib_qp *, स्थिर काष्ठा ib_send_wr *,
		   स्थिर काष्ठा ib_send_wr **bad_wr);
पूर्णांक qedr_post_recv(काष्ठा ib_qp *, स्थिर काष्ठा ib_recv_wr *,
		   स्थिर काष्ठा ib_recv_wr **bad_wr);
पूर्णांक qedr_process_mad(काष्ठा ib_device *ibdev, पूर्णांक process_mad_flags,
		     u32 port_num, स्थिर काष्ठा ib_wc *in_wc,
		     स्थिर काष्ठा ib_grh *in_grh, स्थिर काष्ठा ib_mad *in_mad,
		     काष्ठा ib_mad *out_mad, माप_प्रकार *out_mad_size,
		     u16 *out_mad_pkey_index);

पूर्णांक qedr_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			काष्ठा ib_port_immutable *immutable);
#पूर्ण_अगर
