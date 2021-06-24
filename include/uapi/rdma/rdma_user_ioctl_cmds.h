<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies inc.  All rights reserved.
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

#अगर_अघोषित RDMA_USER_IOCTL_CMDS_H
#घोषणा RDMA_USER_IOCTL_CMDS_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/* Documentation/userspace-api/ioctl/ioctl-number.rst */
#घोषणा RDMA_IOCTL_MAGIC	0x1b
#घोषणा RDMA_VERBS_IOCTL \
	_IOWR(RDMA_IOCTL_MAGIC, 1, काष्ठा ib_uverbs_ioctl_hdr)

क्रमागत अणु
	/* User input */
	UVERBS_ATTR_F_MANDATORY = 1U << 0,
	/*
	 * Valid output bit should be ignored and considered set in
	 * mandatory fields. This bit is kernel output.
	 */
	UVERBS_ATTR_F_VALID_OUTPUT = 1U << 1,
पूर्ण;

काष्ठा ib_uverbs_attr अणु
	__u16 attr_id;		/* command specअगरic type attribute */
	__u16 len;		/* only क्रम poपूर्णांकers and IDRs array */
	__u16 flags;		/* combination of UVERBS_ATTR_F_XXXX */
	जोड़ अणु
		काष्ठा अणु
			__u8 elem_id;
			__u8 reserved;
		पूर्ण क्रमागत_data;
		__u16 reserved;
	पूर्ण attr_data;
	जोड़ अणु
		/*
		 * ptr to command, अंतरभूत data, idr/fd or
		 * ptr to __u32 array of IDRs
		 */
		__aligned_u64 data;
		/* Used by FD_IN and FD_OUT */
		__s64 data_s64;
	पूर्ण;
पूर्ण;

काष्ठा ib_uverbs_ioctl_hdr अणु
	__u16 length;
	__u16 object_id;
	__u16 method_id;
	__u16 num_attrs;
	__aligned_u64 reserved1;
	__u32 driver_id;
	__u32 reserved2;
	काष्ठा ib_uverbs_attr  attrs[0];
पूर्ण;

#पूर्ण_अगर
