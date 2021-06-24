<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * Intel MIC Platक्रमm Software Stack (MPSS)
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2014 Intel Corporation.
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
 * Copyright(c) 2014 Intel Corporation.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the करोcumentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of Intel Corporation nor the names of its
 *   contributors may be used to enकरोrse or promote products derived
 *   from this software without specअगरic prior written permission.
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
 * Intel SCIF driver.
 *
 */
/*
 * -----------------------------------------
 * SCIF IOCTL पूर्णांकerface inक्रमmation
 * -----------------------------------------
 */
#अगर_अघोषित SCIF_IOCTL_H
#घोषणा SCIF_IOCTL_H

#समावेश <linux/types.h>

/**
 * काष्ठा scअगर_port_id - SCIF port inक्रमmation
 * @node:	node on which port resides
 * @port:	local port number
 */
काष्ठा scअगर_port_id अणु
	__u16 node;
	__u16 port;
पूर्ण;

/**
 * काष्ठा scअगरioctl_connect - used क्रम SCIF_CONNECT IOCTL
 * @self:	used to पढ़ो back the asचिन्हित port_id
 * @peer:	destination node and port to connect to
 */
काष्ठा scअगरioctl_connect अणु
	काष्ठा scअगर_port_id	self;
	काष्ठा scअगर_port_id	peer;
पूर्ण;

/**
 * काष्ठा scअगरioctl_accept - used क्रम SCIF_ACCEPTREQ IOCTL
 * @flags:	flags
 * @peer:	global id of peer endpoपूर्णांक
 * @endpt:	new connected endpoपूर्णांक descriptor
 */
काष्ठा scअगरioctl_accept अणु
	__s32			flags;
	काष्ठा scअगर_port_id	peer;
	__u64			endpt;
पूर्ण;

/**
 * काष्ठा scअगरioctl_msg - used क्रम SCIF_SEND/SCIF_RECV IOCTL
 * @msg:	message buffer address
 * @len:	message length
 * @flags:	flags
 * @out_len:	number of bytes sent/received
 */
काष्ठा scअगरioctl_msg अणु
	__u64	msg;
	__s32	len;
	__s32	flags;
	__s32	out_len;
पूर्ण;

/**
 * काष्ठा scअगरioctl_reg - used क्रम SCIF_REG IOCTL
 * @addr:	starting भव address
 * @len:	length of range
 * @offset:	offset of winकरोw
 * @prot:	पढ़ो/ग_लिखो protection
 * @flags:	flags
 * @out_offset:	offset वापसed
 */
काष्ठा scअगरioctl_reg अणु
	__u64		addr;
	__u64		len;
	__s64		offset;
	__s32		prot;
	__s32		flags;
	__s64		out_offset;
पूर्ण;

/**
 * काष्ठा scअगरioctl_unreg - used क्रम SCIF_UNREG IOCTL
 * @offset:	start of range to unरेजिस्टर
 * @len:	length of range to unरेजिस्टर
 */
काष्ठा scअगरioctl_unreg अणु
	__s64		offset;
	__u64		len;
पूर्ण;

/**
 * काष्ठा scअगरioctl_copy - used क्रम SCIF DMA copy IOCTLs
 *
 * @loffset:	offset in local रेजिस्टरed address space to/from
 *		which to copy
 * @len:	length of range to copy
 * @roffset:	offset in remote रेजिस्टरed address space to/from
 *		which to copy
 * @addr:	user भव address to/from which to copy
 * @flags:	flags
 *
 * This काष्ठाure is used क्रम SCIF_READFROM, SCIF_WRITETO, SCIF_VREADFROM
 * and SCIF_VREADFROM IOCTL's.
 */
काष्ठा scअगरioctl_copy अणु
	__s64		loffset;
	__u64		len;
	__s64		roffset;
	__u64		addr;
	__s32		flags;
पूर्ण;

/**
 * काष्ठा scअगरioctl_fence_mark  - used क्रम SCIF_FENCE_MARK IOCTL
 * @flags:	flags
 * @mark:	fence handle which is a poपूर्णांकer to a __s32
 */
काष्ठा scअगरioctl_fence_mark अणु
	__s32	flags;
	__u64	mark;
पूर्ण;

/**
 * काष्ठा scअगरioctl_fence_संकेत - used क्रम SCIF_FENCE_SIGNAL IOCTL
 * @loff:	local offset
 * @lval:	value to ग_लिखो to loffset
 * @roff:	remote offset
 * @rval:	value to ग_लिखो to roffset
 * @flags:	flags
 */
काष्ठा scअगरioctl_fence_संकेत अणु
	__s64		loff;
	__u64		lval;
	__s64		roff;
	__u64		rval;
	__s32		flags;
पूर्ण;

/**
 * काष्ठा scअगरioctl_node_ids - used क्रम SCIF_GET_NODEIDS IOCTL
 * @nodes:	poपूर्णांकer to an array of node_ids
 * @self:	ID of the current node
 * @len:	length of array
 */
काष्ठा scअगरioctl_node_ids अणु
	__u64	nodes;
	__u64	self;
	__s32	len;
पूर्ण;

#घोषणा SCIF_BIND		_IOWR('s', 1, __u64)
#घोषणा SCIF_LISTEN		_IOW('s', 2, __s32)
#घोषणा SCIF_CONNECT		_IOWR('s', 3, काष्ठा scअगरioctl_connect)
#घोषणा SCIF_ACCEPTREQ		_IOWR('s', 4, काष्ठा scअगरioctl_accept)
#घोषणा SCIF_ACCEPTREG		_IOWR('s', 5, __u64)
#घोषणा SCIF_SEND		_IOWR('s', 6, काष्ठा scअगरioctl_msg)
#घोषणा SCIF_RECV		_IOWR('s', 7, काष्ठा scअगरioctl_msg)
#घोषणा SCIF_REG		_IOWR('s', 8, काष्ठा scअगरioctl_reg)
#घोषणा SCIF_UNREG		_IOWR('s', 9, काष्ठा scअगरioctl_unreg)
#घोषणा SCIF_READFROM		_IOWR('s', 10, काष्ठा scअगरioctl_copy)
#घोषणा SCIF_WRITETO		_IOWR('s', 11, काष्ठा scअगरioctl_copy)
#घोषणा SCIF_VREADFROM		_IOWR('s', 12, काष्ठा scअगरioctl_copy)
#घोषणा SCIF_VWRITETO		_IOWR('s', 13, काष्ठा scअगरioctl_copy)
#घोषणा SCIF_GET_NODEIDS	_IOWR('s', 14, काष्ठा scअगरioctl_node_ids)
#घोषणा SCIF_FENCE_MARK		_IOWR('s', 15, काष्ठा scअगरioctl_fence_mark)
#घोषणा SCIF_FENCE_WAIT		_IOWR('s', 16, __s32)
#घोषणा SCIF_FENCE_SIGNAL	_IOWR('s', 17, काष्ठा scअगरioctl_fence_संकेत)

#पूर्ण_अगर /* SCIF_IOCTL_H */
