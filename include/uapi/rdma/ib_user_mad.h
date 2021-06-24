<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Voltaire, Inc. All rights reserved.
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

#अगर_अघोषित IB_USER_MAD_H
#घोषणा IB_USER_MAD_H

#समावेश <linux/types.h>
#समावेश <rdma/rdma_user_ioctl.h>

/*
 * Increment this value अगर any changes that अवरोध userspace ABI
 * compatibility are made.
 */
#घोषणा IB_USER_MAD_ABI_VERSION	5

/*
 * Make sure that all काष्ठाs defined in this file reमुख्य laid out so
 * that they pack the same way on 32-bit and 64-bit architectures (to
 * aव्योम incompatibility between 32-bit userspace and 64-bit kernels).
 */

/**
 * ib_user_mad_hdr_old - Old version of MAD packet header without pkey_index
 * @id - ID of agent MAD received with/to be sent with
 * @status - 0 on successful receive, ETIMEDOUT अगर no response
 *   received (transaction ID in data[] will be set to TID of original
 *   request) (ignored on send)
 * @समयout_ms - Milliseconds to रुको क्रम response (unset on receive)
 * @retries - Number of स्वतःmatic retries to attempt
 * @qpn - Remote QP number received from/to be sent to
 * @qkey - Remote Q_Key to be sent with (unset on receive)
 * @lid - Remote lid received from/to be sent to
 * @sl - Service level received with/to be sent with
 * @path_bits - Local path bits received with/to be sent with
 * @grh_present - If set, GRH was received/should be sent
 * @gid_index - Local GID index to send with (unset on receive)
 * @hop_limit - Hop limit in GRH
 * @traffic_class - Traffic class in GRH
 * @gid - Remote GID in GRH
 * @flow_label - Flow label in GRH
 */
काष्ठा ib_user_mad_hdr_old अणु
	__u32	id;
	__u32	status;
	__u32	समयout_ms;
	__u32	retries;
	__u32	length;
	__be32	qpn;
	__be32  qkey;
	__be16	lid;
	__u8	sl;
	__u8	path_bits;
	__u8	grh_present;
	__u8	gid_index;
	__u8	hop_limit;
	__u8	traffic_class;
	__u8	gid[16];
	__be32	flow_label;
पूर्ण;

/**
 * ib_user_mad_hdr - MAD packet header
 *   This layout allows specअगरying/receiving the P_Key index.  To use
 *   this capability, an application must call the
 *   IB_USER_MAD_ENABLE_PKEY ioctl on the user MAD file handle beक्रमe
 *   any other actions with the file handle.
 * @id - ID of agent MAD received with/to be sent with
 * @status - 0 on successful receive, ETIMEDOUT अगर no response
 *   received (transaction ID in data[] will be set to TID of original
 *   request) (ignored on send)
 * @समयout_ms - Milliseconds to रुको क्रम response (unset on receive)
 * @retries - Number of स्वतःmatic retries to attempt
 * @qpn - Remote QP number received from/to be sent to
 * @qkey - Remote Q_Key to be sent with (unset on receive)
 * @lid - Remote lid received from/to be sent to
 * @sl - Service level received with/to be sent with
 * @path_bits - Local path bits received with/to be sent with
 * @grh_present - If set, GRH was received/should be sent
 * @gid_index - Local GID index to send with (unset on receive)
 * @hop_limit - Hop limit in GRH
 * @traffic_class - Traffic class in GRH
 * @gid - Remote GID in GRH
 * @flow_label - Flow label in GRH
 * @pkey_index - P_Key index
 */
काष्ठा ib_user_mad_hdr अणु
	__u32	id;
	__u32	status;
	__u32	समयout_ms;
	__u32	retries;
	__u32	length;
	__be32	qpn;
	__be32  qkey;
	__be16	lid;
	__u8	sl;
	__u8	path_bits;
	__u8	grh_present;
	__u8	gid_index;
	__u8	hop_limit;
	__u8	traffic_class;
	__u8	gid[16];
	__be32	flow_label;
	__u16	pkey_index;
	__u8	reserved[6];
पूर्ण;

/**
 * ib_user_mad - MAD packet
 * @hdr - MAD packet header
 * @data - Contents of MAD
 *
 */
काष्ठा ib_user_mad अणु
	काष्ठा ib_user_mad_hdr hdr;
	__aligned_u64	data[0];
पूर्ण;

/*
 * Earlier versions of this पूर्णांकerface definition declared the
 * method_mask[] member as an array of __u32 but treated it as a
 * biपंचांगap made up of दीर्घs in the kernel.  This ambiguity meant that
 * 32-bit big-endian applications that can run on both 32-bit and
 * 64-bit kernels had no consistent ABI to rely on, and 64-bit
 * big-endian applications that treated method_mask as being made up
 * of 32-bit words would have their biपंचांगap misपूर्णांकerpreted.
 *
 * To clear up this confusion, we change the declaration of
 * method_mask[] to use अचिन्हित दीर्घ and handle the conversion from
 * 32-bit userspace to 64-bit kernel क्रम big-endian प्रणालीs in the
 * compat_ioctl method.  Unक्रमtunately, to keep the काष्ठाure layout
 * the same, we need the method_mask[] array to be aligned only to 4
 * bytes even when दीर्घ is 64 bits, which क्रमces us पूर्णांकo this ugly
 * प्रकार.
 */
प्रकार अचिन्हित दीर्घ __attribute__((aligned(4))) packed_uदीर्घ;
#घोषणा IB_USER_MAD_LONGS_PER_METHOD_MASK (128 / (8 * माप (दीर्घ)))

/**
 * ib_user_mad_reg_req - MAD registration request
 * @id - Set by the kernel; used to identअगरy agent in future requests.
 * @qpn - Queue pair number; must be 0 or 1.
 * @method_mask - The caller will receive unsolicited MADs क्रम any method
 *   where @method_mask = 1.
 * @mgmt_class - Indicates which management class of MADs should be receive
 *   by the caller.  This field is only required अगर the user wishes to
 *   receive unsolicited MADs, otherwise it should be 0.
 * @mgmt_class_version - Indicates which version of MADs क्रम the given
 *   management class to receive.
 * @oui: Indicates IEEE OUI when mgmt_class is a venकरोr class
 *   in the range from 0x30 to 0x4f. Otherwise not used.
 * @rmpp_version: If set, indicates the RMPP version used.
 *
 */
काष्ठा ib_user_mad_reg_req अणु
	__u32	id;
	packed_uदीर्घ method_mask[IB_USER_MAD_LONGS_PER_METHOD_MASK];
	__u8	qpn;
	__u8	mgmt_class;
	__u8	mgmt_class_version;
	__u8    oui[3];
	__u8	rmpp_version;
पूर्ण;

/**
 * ib_user_mad_reg_req2 - MAD registration request
 *
 * @id                 - Set by the _kernel_; used by userspace to identअगरy the
 *                       रेजिस्टरed agent in future requests.
 * @qpn                - Queue pair number; must be 0 or 1.
 * @mgmt_class         - Indicates which management class of MADs should be
 *                       receive by the caller.  This field is only required अगर
 *                       the user wishes to receive unsolicited MADs, otherwise
 *                       it should be 0.
 * @mgmt_class_version - Indicates which version of MADs क्रम the given
 *                       management class to receive.
 * @res                - Ignored.
 * @flags              - additional registration flags; Must be in the set of
 *                       flags defined in IB_USER_MAD_REG_FLAGS_CAP
 * @method_mask        - The caller wishes to receive unsolicited MADs क्रम the
 *                       methods whose bit(s) is(are) set.
 * @oui                - Indicates IEEE OUI to use when mgmt_class is a venकरोr
 *                       class in the range from 0x30 to 0x4f. Otherwise not
 *                       used.
 * @rmpp_version       - If set, indicates the RMPP version to use.
 */
क्रमागत अणु
	IB_USER_MAD_USER_RMPP = (1 << 0),
पूर्ण;
#घोषणा IB_USER_MAD_REG_FLAGS_CAP (IB_USER_MAD_USER_RMPP)
काष्ठा ib_user_mad_reg_req2 अणु
	__u32	id;
	__u32	qpn;
	__u8	mgmt_class;
	__u8	mgmt_class_version;
	__u16   res;
	__u32   flags;
	__aligned_u64 method_mask[2];
	__u32   oui;
	__u8	rmpp_version;
	__u8	reserved[3];
पूर्ण;

#पूर्ण_अगर /* IB_USER_MAD_H */
