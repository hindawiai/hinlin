<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_VSOCKMON_H
#घोषणा _UAPI_VSOCKMON_H

#समावेश <linux/virtio_vsock.h>

/*
 * vsockmon is the AF_VSOCK packet capture device.  Packets captured have the
 * following layout:
 *
 *   +-----------------------------------+
 *   |           vsockmon header         |
 *   |      (काष्ठा af_vsockmon_hdr)     |
 *   +-----------------------------------+
 *   |          transport header         |
 *   | (af_vsockmon_hdr->len bytes दीर्घ) |
 *   +-----------------------------------+
 *   |              payload              |
 *   |       (until end of packet)       |
 *   +-----------------------------------+
 *
 * The vsockmon header is a transport-independent description of the packet.
 * It duplicates some of the inक्रमmation from the transport header so that
 * no transport-specअगरic knowledge is necessary to process packets.
 *
 * The transport header is useful क्रम low-level transport-specअगरic packet
 * analysis.  Transport type is given in af_vsockmon_hdr->transport and
 * transport header length is given in af_vsockmon_hdr->len.
 *
 * If af_vsockmon_hdr->op is AF_VSOCK_OP_PAYLOAD then the payload follows the
 * transport header.  Other ops करो not have a payload.
 */

काष्ठा af_vsockmon_hdr अणु
	__le64 src_cid;
	__le64 dst_cid;
	__le32 src_port;
	__le32 dst_port;
	__le16 op;			/* क्रमागत af_vsockmon_op */
	__le16 transport;		/* क्रमागत af_vsockmon_transport */
	__le16 len;			/* Transport header length */
	__u8 reserved[2];
पूर्ण;

क्रमागत af_vsockmon_op अणु
	AF_VSOCK_OP_UNKNOWN = 0,
	AF_VSOCK_OP_CONNECT = 1,
	AF_VSOCK_OP_DISCONNECT = 2,
	AF_VSOCK_OP_CONTROL = 3,
	AF_VSOCK_OP_PAYLOAD = 4,
पूर्ण;

क्रमागत af_vsockmon_transport अणु
	AF_VSOCK_TRANSPORT_UNKNOWN = 0,
	AF_VSOCK_TRANSPORT_NO_INFO = 1,	/* No transport inक्रमmation */

	/* Transport header type: काष्ठा virtio_vsock_hdr */
	AF_VSOCK_TRANSPORT_VIRTIO = 2,
पूर्ण;

#पूर्ण_अगर
