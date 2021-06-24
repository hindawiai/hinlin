<शैली गुरु>
/*
 * Copyright (c) 2007 Cisco Systems, Inc.  All rights reserved.
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

#अगर_अघोषित MLX4_CQ_H
#घोषणा MLX4_CQ_H

#समावेश <linux/types.h>
#समावेश <uapi/linux/अगर_ether.h>

#समावेश <linux/mlx4/device.h>
#समावेश <linux/mlx4/करोorbell.h>

काष्ठा mlx4_cqe अणु
	__be32			vlan_my_qpn;
	__be32			immed_rss_invalid;
	__be32			g_mlpath_rqpn;
	__be16			sl_vid;
	जोड़ अणु
		काष्ठा अणु
			__be16	rlid;
			__be16  status;
			u8      ipv6_ext_mask;
			u8      badfcs_enc;
		पूर्ण;
		u8  smac[ETH_ALEN];
	पूर्ण;
	__be32			byte_cnt;
	__be16			wqe_index;
	__be16			checksum;
	u8			reserved[3];
	u8			owner_sr_opcode;
पूर्ण;

काष्ठा mlx4_err_cqe अणु
	__be32			my_qpn;
	u32			reserved1[5];
	__be16			wqe_index;
	u8			venकरोr_err_syndrome;
	u8			syndrome;
	u8			reserved2[3];
	u8			owner_sr_opcode;
पूर्ण;

काष्ठा mlx4_ts_cqe अणु
	__be32			vlan_my_qpn;
	__be32			immed_rss_invalid;
	__be32			g_mlpath_rqpn;
	__be32			बारtamp_hi;
	__be16			status;
	u8			ipv6_ext_mask;
	u8			badfcs_enc;
	__be32			byte_cnt;
	__be16			wqe_index;
	__be16			checksum;
	u8			reserved;
	__be16			बारtamp_lo;
	u8			owner_sr_opcode;
पूर्ण __packed;

क्रमागत अणु
	MLX4_CQE_L2_TUNNEL_IPOK		= 1 << 31,
	MLX4_CQE_CVLAN_PRESENT_MASK	= 1 << 29,
	MLX4_CQE_SVLAN_PRESENT_MASK	= 1 << 30,
	MLX4_CQE_L2_TUNNEL		= 1 << 27,
	MLX4_CQE_L2_TUNNEL_CSUM		= 1 << 26,
	MLX4_CQE_L2_TUNNEL_IPV4		= 1 << 25,

	MLX4_CQE_QPN_MASK		= 0xffffff,
	MLX4_CQE_VID_MASK		= 0xfff,
पूर्ण;

क्रमागत अणु
	MLX4_CQE_OWNER_MASK	= 0x80,
	MLX4_CQE_IS_SEND_MASK	= 0x40,
	MLX4_CQE_OPCODE_MASK	= 0x1f
पूर्ण;

क्रमागत अणु
	MLX4_CQE_SYNDROME_LOCAL_LENGTH_ERR		= 0x01,
	MLX4_CQE_SYNDROME_LOCAL_QP_OP_ERR		= 0x02,
	MLX4_CQE_SYNDROME_LOCAL_PROT_ERR		= 0x04,
	MLX4_CQE_SYNDROME_WR_FLUSH_ERR			= 0x05,
	MLX4_CQE_SYNDROME_MW_BIND_ERR			= 0x06,
	MLX4_CQE_SYNDROME_BAD_RESP_ERR			= 0x10,
	MLX4_CQE_SYNDROME_LOCAL_ACCESS_ERR		= 0x11,
	MLX4_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR		= 0x12,
	MLX4_CQE_SYNDROME_REMOTE_ACCESS_ERR		= 0x13,
	MLX4_CQE_SYNDROME_REMOTE_OP_ERR			= 0x14,
	MLX4_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR	= 0x15,
	MLX4_CQE_SYNDROME_RNR_RETRY_EXC_ERR		= 0x16,
	MLX4_CQE_SYNDROME_REMOTE_ABORTED_ERR		= 0x22,
पूर्ण;

क्रमागत अणु
	MLX4_CQE_STATUS_IPV4		= 1 << 6,
	MLX4_CQE_STATUS_IPV4F		= 1 << 7,
	MLX4_CQE_STATUS_IPV6		= 1 << 8,
	MLX4_CQE_STATUS_IPV4OPT		= 1 << 9,
	MLX4_CQE_STATUS_TCP		= 1 << 10,
	MLX4_CQE_STATUS_UDP		= 1 << 11,
	MLX4_CQE_STATUS_IPOK		= 1 << 12,
पूर्ण;

/* L4_CSUM is logically part of status, but has to checked against badfcs_enc */
क्रमागत अणु
	MLX4_CQE_STATUS_L4_CSUM		= 1 << 2,
पूर्ण;

क्रमागत अणु
	MLX4_CQE_LLC                     = 1,
	MLX4_CQE_SNAP                    = 1 << 1,
	MLX4_CQE_BAD_FCS                 = 1 << 4,
पूर्ण;

#घोषणा MLX4_MAX_CQ_PERIOD (BIT(16) - 1)
#घोषणा MLX4_MAX_CQ_COUNT (BIT(16) - 1)

अटल अंतरभूत व्योम mlx4_cq_arm(काष्ठा mlx4_cq *cq, u32 cmd,
			       व्योम __iomem *uar_page,
			       spinlock_t *करोorbell_lock)
अणु
	__be32 करोorbell[2];
	u32 sn;
	u32 ci;

	sn = cq->arm_sn & 3;
	ci = cq->cons_index & 0xffffff;

	*cq->arm_db = cpu_to_be32(sn << 28 | cmd | ci);

	/*
	 * Make sure that the करोorbell record in host memory is
	 * written beक्रमe ringing the करोorbell via PCI MMIO.
	 */
	wmb();

	करोorbell[0] = cpu_to_be32(sn << 28 | cmd | cq->cqn);
	करोorbell[1] = cpu_to_be32(ci);

	mlx4_ग_लिखो64(करोorbell, uar_page + MLX4_CQ_DOORBELL, करोorbell_lock);
पूर्ण

अटल अंतरभूत व्योम mlx4_cq_set_ci(काष्ठा mlx4_cq *cq)
अणु
	*cq->set_ci_db = cpu_to_be32(cq->cons_index & 0xffffff);
पूर्ण

क्रमागत अणु
	MLX4_CQ_DB_REQ_NOT_SOL		= 1 << 24,
	MLX4_CQ_DB_REQ_NOT		= 2 << 24
पूर्ण;

पूर्णांक mlx4_cq_modअगरy(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cq *cq,
		   u16 count, u16 period);
पूर्णांक mlx4_cq_resize(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cq *cq,
		   पूर्णांक entries, काष्ठा mlx4_mtt *mtt);

#पूर्ण_अगर /* MLX4_CQ_H */
