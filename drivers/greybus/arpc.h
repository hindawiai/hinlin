<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Copyright(c) 2016 Google Inc. All rights reserved.
 * Copyright(c) 2016 Linaro Ltd. All rights reserved.
 */

#अगर_अघोषित __ARPC_H
#घोषणा __ARPC_H

/* APBridgeA RPC (ARPC) */

क्रमागत arpc_result अणु
	ARPC_SUCCESS		= 0x00,
	ARPC_NO_MEMORY		= 0x01,
	ARPC_INVALID		= 0x02,
	ARPC_TIMEOUT		= 0x03,
	ARPC_UNKNOWN_ERROR	= 0xff,
पूर्ण;

काष्ठा arpc_request_message अणु
	__le16	id;		/* RPC unique id */
	__le16	size;		/* Size in bytes of header + payload */
	__u8	type;		/* RPC type */
	__u8	data[];	/* ARPC data */
पूर्ण __packed;

काष्ठा arpc_response_message अणु
	__le16	id;		/* RPC unique id */
	__u8	result;		/* Result of RPC */
पूर्ण __packed;

/* ARPC requests */
#घोषणा ARPC_TYPE_CPORT_CONNECTED		0x01
#घोषणा ARPC_TYPE_CPORT_QUIESCE			0x02
#घोषणा ARPC_TYPE_CPORT_CLEAR			0x03
#घोषणा ARPC_TYPE_CPORT_FLUSH			0x04
#घोषणा ARPC_TYPE_CPORT_SHUTDOWN		0x05

काष्ठा arpc_cport_connected_req अणु
	__le16 cport_id;
पूर्ण __packed;

काष्ठा arpc_cport_quiesce_req अणु
	__le16 cport_id;
	__le16 peer_space;
	__le16 समयout;
पूर्ण __packed;

काष्ठा arpc_cport_clear_req अणु
	__le16 cport_id;
पूर्ण __packed;

काष्ठा arpc_cport_flush_req अणु
	__le16 cport_id;
पूर्ण __packed;

काष्ठा arpc_cport_shutकरोwn_req अणु
	__le16 cport_id;
	__le16 समयout;
	__u8 phase;
पूर्ण __packed;

#पूर्ण_अगर	/* __ARPC_H */
