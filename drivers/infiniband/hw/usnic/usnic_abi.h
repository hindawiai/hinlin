<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
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


#अगर_अघोषित USNIC_ABI_H
#घोषणा USNIC_ABI_H

/* ABI between userspace and kernel */
#घोषणा USNIC_UVERBS_ABI_VERSION	4

#घोषणा USNIC_QP_GRP_MAX_WQS		8
#घोषणा USNIC_QP_GRP_MAX_RQS		8
#घोषणा USNIC_QP_GRP_MAX_CQS		16

क्रमागत usnic_transport_type अणु
	USNIC_TRANSPORT_UNKNOWN		= 0,
	USNIC_TRANSPORT_ROCE_CUSTOM	= 1,
	USNIC_TRANSPORT_IPV4_UDP	= 2,
	USNIC_TRANSPORT_MAX		= 3,
पूर्ण;

काष्ठा usnic_transport_spec अणु
	क्रमागत usnic_transport_type	trans_type;
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक16_t	port_num;
		पूर्ण usnic_roce;
		काष्ठा अणु
			uपूर्णांक32_t	sock_fd;
		पूर्ण udp;
	पूर्ण;
पूर्ण;

काष्ठा usnic_ib_create_qp_cmd अणु
	काष्ठा usnic_transport_spec	spec;
पूर्ण;

/*TODO: Future - usnic_modअगरy_qp needs to pass in generic filters */
काष्ठा usnic_ib_create_qp_resp अणु
	u32				vfid;
	u32				qp_grp_id;
	u64				bar_bus_addr;
	u32				bar_len;
/*
 * WQ, RQ, CQ are explicity specअगरied bc exposing a generic resources पूर्णांकeface
 * expands the scope of ABI to many files.
 */
	u32				wq_cnt;
	u32				rq_cnt;
	u32				cq_cnt;
	u32				wq_idx[USNIC_QP_GRP_MAX_WQS];
	u32				rq_idx[USNIC_QP_GRP_MAX_RQS];
	u32				cq_idx[USNIC_QP_GRP_MAX_CQS];
	u32				transport;
	u32				reserved[9];
पूर्ण;

#पूर्ण_अगर /* USNIC_ABI_H */
