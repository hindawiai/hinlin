<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2016 Mellanox Technologies, LTD. All rights reserved.
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
 */

#अगर_अघोषित RDMA_USER_IOCTL_H
#घोषणा RDMA_USER_IOCTL_H

#समावेश <rdma/ib_user_mad.h>
#समावेश <rdma/hfi/hfi1_ioctl.h>
#समावेश <rdma/rdma_user_ioctl_cmds.h>

/* Legacy name, क्रम user space application which alपढ़ोy use it */
#घोषणा IB_IOCTL_MAGIC		RDMA_IOCTL_MAGIC

/*
 * General blocks assignments
 * It is बंदd on purpose - करो not expose it to user space
 * #घोषणा MAD_CMD_BASE		0x00
 * #घोषणा HFI1_CMD_BAS		0xE0
 */

/* MAD specअगरic section */
#घोषणा IB_USER_MAD_REGISTER_AGENT	_IOWR(RDMA_IOCTL_MAGIC, 0x01, काष्ठा ib_user_mad_reg_req)
#घोषणा IB_USER_MAD_UNREGISTER_AGENT	_IOW(RDMA_IOCTL_MAGIC,  0x02, __u32)
#घोषणा IB_USER_MAD_ENABLE_PKEY		_IO(RDMA_IOCTL_MAGIC,   0x03)
#घोषणा IB_USER_MAD_REGISTER_AGENT2	_IOWR(RDMA_IOCTL_MAGIC, 0x04, काष्ठा ib_user_mad_reg_req2)

/* HFI specअगरic section */
/* allocate HFI and context */
#घोषणा HFI1_IOCTL_ASSIGN_CTXT		_IOWR(RDMA_IOCTL_MAGIC, 0xE1, काष्ठा hfi1_user_info)
/* find out what resources we got */
#घोषणा HFI1_IOCTL_CTXT_INFO		_IOW(RDMA_IOCTL_MAGIC,  0xE2, काष्ठा hfi1_ctxt_info)
/* set up userspace */
#घोषणा HFI1_IOCTL_USER_INFO		_IOW(RDMA_IOCTL_MAGIC,  0xE3, काष्ठा hfi1_base_info)
/* update expected TID entries */
#घोषणा HFI1_IOCTL_TID_UPDATE		_IOWR(RDMA_IOCTL_MAGIC, 0xE4, काष्ठा hfi1_tid_info)
/* मुक्त expected TID entries */
#घोषणा HFI1_IOCTL_TID_FREE		_IOWR(RDMA_IOCTL_MAGIC, 0xE5, काष्ठा hfi1_tid_info)
/* क्रमce an update of PIO credit */
#घोषणा HFI1_IOCTL_CREDIT_UPD		_IO(RDMA_IOCTL_MAGIC,   0xE6)
/* control receipt of packets */
#घोषणा HFI1_IOCTL_RECV_CTRL		_IOW(RDMA_IOCTL_MAGIC,  0xE8, पूर्णांक)
/* set the kind of polling we want */
#घोषणा HFI1_IOCTL_POLL_TYPE		_IOW(RDMA_IOCTL_MAGIC,  0xE9, पूर्णांक)
/* ack & clear user status bits */
#घोषणा HFI1_IOCTL_ACK_EVENT		_IOW(RDMA_IOCTL_MAGIC,  0xEA, अचिन्हित दीर्घ)
/* set context's pkey */
#घोषणा HFI1_IOCTL_SET_PKEY		_IOW(RDMA_IOCTL_MAGIC,  0xEB, __u16)
/* reset context's HW send context */
#घोषणा HFI1_IOCTL_CTXT_RESET		_IO(RDMA_IOCTL_MAGIC,   0xEC)
/* पढ़ो TID cache invalidations */
#घोषणा HFI1_IOCTL_TID_INVAL_READ	_IOWR(RDMA_IOCTL_MAGIC, 0xED, काष्ठा hfi1_tid_info)
/* get the version of the user cdev */
#घोषणा HFI1_IOCTL_GET_VERS		_IOR(RDMA_IOCTL_MAGIC,  0xEE, पूर्णांक)

#पूर्ण_अगर /* RDMA_USER_IOCTL_H */
