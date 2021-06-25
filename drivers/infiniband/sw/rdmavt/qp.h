<शैली गुरु>
#अगर_अघोषित DEF_RVTQP_H
#घोषणा DEF_RVTQP_H

/*
 * Copyright(c) 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <rdma/rdmavt_qp.h>

पूर्णांक rvt_driver_qp_init(काष्ठा rvt_dev_info *rdi);
व्योम rvt_qp_निकास(काष्ठा rvt_dev_info *rdi);
काष्ठा ib_qp *rvt_create_qp(काष्ठा ib_pd *ibpd,
			    काष्ठा ib_qp_init_attr *init_attr,
			    काष्ठा ib_udata *udata);
पूर्णांक rvt_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		  पूर्णांक attr_mask, काष्ठा ib_udata *udata);
पूर्णांक rvt_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata);
पूर्णांक rvt_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		 पूर्णांक attr_mask, काष्ठा ib_qp_init_attr *init_attr);
पूर्णांक rvt_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		  स्थिर काष्ठा ib_recv_wr **bad_wr);
पूर्णांक rvt_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		  स्थिर काष्ठा ib_send_wr **bad_wr);
पूर्णांक rvt_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr);
पूर्णांक rvt_wss_init(काष्ठा rvt_dev_info *rdi);
व्योम rvt_wss_निकास(काष्ठा rvt_dev_info *rdi);
पूर्णांक rvt_alloc_rq(काष्ठा rvt_rq *rq, u32 size, पूर्णांक node,
		 काष्ठा ib_udata *udata);
#पूर्ण_अगर          /* DEF_RVTQP_H */
