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
#अगर_अघोषित LINUX_QEDR_CM_H_
#घोषणा LINUX_QEDR_CM_H_

#घोषणा QEDR_GSI_MAX_RECV_WR	(4096)
#घोषणा QEDR_GSI_MAX_SEND_WR	(4096)

#घोषणा QEDR_GSI_MAX_RECV_SGE	(1)	/* LL2 FW limitation */

#घोषणा QEDR_ROCE_V2_UDP_SPORT	(0000)

अटल अंतरभूत u32 qedr_get_ipv4_from_gid(स्थिर u8 *gid)
अणु
	वापस *(u32 *)(व्योम *)&gid[12];
पूर्ण

/* RDMA CM */
पूर्णांक qedr_gsi_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc);
पूर्णांक qedr_gsi_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		       स्थिर काष्ठा ib_recv_wr **bad_wr);
पूर्णांक qedr_gsi_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		       स्थिर काष्ठा ib_send_wr **bad_wr);
काष्ठा ib_qp *qedr_create_gsi_qp(काष्ठा qedr_dev *dev,
				 काष्ठा ib_qp_init_attr *attrs,
				 काष्ठा qedr_qp *qp);
व्योम qedr_store_gsi_qp_cq(काष्ठा qedr_dev *dev,
			  काष्ठा qedr_qp *qp, काष्ठा ib_qp_init_attr *attrs);
पूर्णांक qedr_destroy_gsi_qp(काष्ठा qedr_dev *dev);
व्योम qedr_inc_sw_gsi_cons(काष्ठा qedr_qp_hwq_info *info);
#पूर्ण_अगर
