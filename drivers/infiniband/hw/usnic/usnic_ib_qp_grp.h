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

#अगर_अघोषित USNIC_IB_QP_GRP_H_
#घोषणा USNIC_IB_QP_GRP_H_

#समावेश <linux/debugfs.h>
#समावेश <rdma/ib_verbs.h>

#समावेश "usnic_ib.h"
#समावेश "usnic_abi.h"
#समावेश "usnic_fwd.h"
#समावेश "usnic_vnic.h"

/*
 * The qp group काष्ठा represents all the hw resources needed to present a ib_qp
 */
काष्ठा usnic_ib_qp_grp अणु
	काष्ठा ib_qp				ibqp;
	क्रमागत ib_qp_state			state;
	पूर्णांक					grp_id;

	काष्ठा usnic_fwd_dev			*ufdev;
	काष्ठा usnic_ib_ucontext		*ctx;
	काष्ठा list_head			flows_lst;

	काष्ठा usnic_vnic_res_chunk		**res_chunk_list;

	pid_t					owner_pid;
	काष्ठा usnic_ib_vf			*vf;
	काष्ठा list_head			link;

	spinlock_t				lock;

	काष्ठा kobject				kobj;
पूर्ण;

काष्ठा usnic_ib_qp_grp_flow अणु
	काष्ठा usnic_fwd_flow		*flow;
	क्रमागत usnic_transport_type	trans_type;
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक16_t	port_num;
		पूर्ण usnic_roce;
		काष्ठा अणु
			काष्ठा socket	*sock;
		पूर्ण udp;
	पूर्ण;
	काष्ठा usnic_ib_qp_grp		*qp_grp;
	काष्ठा list_head		link;

	/* Debug FS */
	काष्ठा dentry			*dbgfs_dentry;
	अक्षर				dentry_name[32];
पूर्ण;

बाह्य स्थिर काष्ठा usnic_vnic_res_spec min_transport_spec[USNIC_TRANSPORT_MAX];

स्थिर अक्षर *usnic_ib_qp_grp_state_to_string(क्रमागत ib_qp_state state);
पूर्णांक usnic_ib_qp_grp_dump_hdr(अक्षर *buf, पूर्णांक buf_sz);
पूर्णांक usnic_ib_qp_grp_dump_rows(व्योम *obj, अक्षर *buf, पूर्णांक buf_sz);
काष्ठा usnic_ib_qp_grp *
usnic_ib_qp_grp_create(काष्ठा usnic_fwd_dev *ufdev, काष्ठा usnic_ib_vf *vf,
			काष्ठा usnic_ib_pd *pd,
			काष्ठा usnic_vnic_res_spec *res_spec,
			काष्ठा usnic_transport_spec *trans_spec);
व्योम usnic_ib_qp_grp_destroy(काष्ठा usnic_ib_qp_grp *qp_grp);
पूर्णांक usnic_ib_qp_grp_modअगरy(काष्ठा usnic_ib_qp_grp *qp_grp,
				क्रमागत ib_qp_state new_state,
				व्योम *data);
काष्ठा usnic_vnic_res_chunk
*usnic_ib_qp_grp_get_chunk(काष्ठा usnic_ib_qp_grp *qp_grp,
				क्रमागत usnic_vnic_res_type type);
अटल अंतरभूत
काष्ठा usnic_ib_qp_grp *to_uqp_grp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा usnic_ib_qp_grp, ibqp);
पूर्ण
#पूर्ण_अगर /* USNIC_IB_QP_GRP_H_ */
