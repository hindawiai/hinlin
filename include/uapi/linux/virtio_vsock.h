<शैली गुरु>
/*
 * This header, excluding the #अगर_घोषित __KERNEL__ part, is BSD licensed so
 * anyone can use the definitions to implement compatible drivers/servers:
 *
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Copyright (C) Red Hat, Inc., 2013-2015
 * Copyright (C) Asias He <asias@redhat.com>, 2013
 * Copyright (C) Stefan Hajnoczi <stefanha@redhat.com>, 2015
 */

#अगर_अघोषित _UAPI_LINUX_VIRTIO_VSOCK_H
#घोषणा _UAPI_LINUX_VIRTIO_VSOCK_H

#समावेश <linux/types.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>

काष्ठा virtio_vsock_config अणु
	__le64 guest_cid;
पूर्ण __attribute__((packed));

क्रमागत virtio_vsock_event_id अणु
	VIRTIO_VSOCK_EVENT_TRANSPORT_RESET = 0,
पूर्ण;

काष्ठा virtio_vsock_event अणु
	__le32 id;
पूर्ण __attribute__((packed));

काष्ठा virtio_vsock_hdr अणु
	__le64	src_cid;
	__le64	dst_cid;
	__le32	src_port;
	__le32	dst_port;
	__le32	len;
	__le16	type;		/* क्रमागत virtio_vsock_type */
	__le16	op;		/* क्रमागत virtio_vsock_op */
	__le32	flags;
	__le32	buf_alloc;
	__le32	fwd_cnt;
पूर्ण __attribute__((packed));

क्रमागत virtio_vsock_type अणु
	VIRTIO_VSOCK_TYPE_STREAM = 1,
पूर्ण;

क्रमागत virtio_vsock_op अणु
	VIRTIO_VSOCK_OP_INVALID = 0,

	/* Connect operations */
	VIRTIO_VSOCK_OP_REQUEST = 1,
	VIRTIO_VSOCK_OP_RESPONSE = 2,
	VIRTIO_VSOCK_OP_RST = 3,
	VIRTIO_VSOCK_OP_SHUTDOWN = 4,

	/* To send payload */
	VIRTIO_VSOCK_OP_RW = 5,

	/* Tell the peer our credit info */
	VIRTIO_VSOCK_OP_CREDIT_UPDATE = 6,
	/* Request the peer to send the credit info to us */
	VIRTIO_VSOCK_OP_CREDIT_REQUEST = 7,
पूर्ण;

/* VIRTIO_VSOCK_OP_SHUTDOWN flags values */
क्रमागत virtio_vsock_shutकरोwn अणु
	VIRTIO_VSOCK_SHUTDOWN_RCV = 1,
	VIRTIO_VSOCK_SHUTDOWN_SEND = 2,
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_VIRTIO_VSOCK_H */
