<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2015 - 2020 Intel Corporation */
#अगर_अघोषित ADF_PF2VF_MSG_H
#घोषणा ADF_PF2VF_MSG_H

/*
 * PF<->VF Messaging
 * The PF has an array of 32-bit PF2VF रेजिस्टरs, one क्रम each VF.  The
 * PF can access all these रेजिस्टरs; each VF can access only the one
 * रेजिस्टर associated with that particular VF.
 *
 * The रेजिस्टर functionally is split पूर्णांकo two parts:
 * The bottom half is क्रम PF->VF messages. In particular when the first
 * bit of this रेजिस्टर (bit 0) माला_लो set an पूर्णांकerrupt will be triggered
 * in the respective VF.
 * The top half is क्रम VF->PF messages. In particular when the first bit
 * of this half of रेजिस्टर (bit 16) माला_लो set an पूर्णांकerrupt will be triggered
 * in the PF.
 *
 * The reमुख्यing bits within this रेजिस्टर are available to encode messages.
 * and implement a collision control mechanism to prevent concurrent use of
 * the PF2VF रेजिस्टर by both the PF and VF.
 *
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16
 *  _______________________________________________
 * |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 * +-----------------------------------------------+
 *  \___________________________/ \_________/ ^   ^
 *                ^                    ^      |   |
 *                |                    |      |   VF2PF Int
 *                |                    |      Message Origin
 *                |                    Message Type
 *                Message-specअगरic Data/Reserved
 *
 *  15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
 *  _______________________________________________
 * |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 * +-----------------------------------------------+
 *  \___________________________/ \_________/ ^   ^
 *                ^                    ^      |   |
 *                |                    |      |   PF2VF Int
 *                |                    |      Message Origin
 *                |                    Message Type
 *                Message-specअगरic Data/Reserved
 *
 * Message Origin (Should always be 1)
 * A legacy out-of-tree QAT driver allowed क्रम a set of messages not supported
 * by this driver; these had a Msg Origin of 0 and are ignored by this driver.
 *
 * When a PF or VF attempts to send a message in the lower or upper 16 bits,
 * respectively, the other 16 bits are written to first with a defined
 * IN_USE_BY pattern as part of a collision control scheme (see adf_iov_puपंचांगsg).
 */

#घोषणा ADF_PFVF_COMPATIBILITY_VERSION		0x1	/* PF<->VF compat */

/* PF->VF messages */
#घोषणा ADF_PF2VF_INT				BIT(0)
#घोषणा ADF_PF2VF_MSGORIGIN_SYSTEM		BIT(1)
#घोषणा ADF_PF2VF_MSGTYPE_MASK			0x0000003C
#घोषणा ADF_PF2VF_MSGTYPE_SHIFT			2
#घोषणा ADF_PF2VF_MSGTYPE_RESTARTING		0x01
#घोषणा ADF_PF2VF_MSGTYPE_VERSION_RESP		0x02
#घोषणा ADF_PF2VF_IN_USE_BY_PF			0x6AC20000
#घोषणा ADF_PF2VF_IN_USE_BY_PF_MASK		0xFFFE0000

/* PF->VF Version Response */
#घोषणा ADF_PF2VF_VERSION_RESP_VERS_MASK	0x00003FC0
#घोषणा ADF_PF2VF_VERSION_RESP_VERS_SHIFT	6
#घोषणा ADF_PF2VF_VERSION_RESP_RESULT_MASK	0x0000C000
#घोषणा ADF_PF2VF_VERSION_RESP_RESULT_SHIFT	14
#घोषणा ADF_PF2VF_MINORVERSION_SHIFT		6
#घोषणा ADF_PF2VF_MAJORVERSION_SHIFT		10
#घोषणा ADF_PF2VF_VF_COMPATIBLE			1
#घोषणा ADF_PF2VF_VF_INCOMPATIBLE		2
#घोषणा ADF_PF2VF_VF_COMPAT_UNKNOWN		3

/* VF->PF messages */
#घोषणा ADF_VF2PF_IN_USE_BY_VF			0x00006AC2
#घोषणा ADF_VF2PF_IN_USE_BY_VF_MASK		0x0000FFFE
#घोषणा ADF_VF2PF_INT				BIT(16)
#घोषणा ADF_VF2PF_MSGORIGIN_SYSTEM		BIT(17)
#घोषणा ADF_VF2PF_MSGTYPE_MASK			0x003C0000
#घोषणा ADF_VF2PF_MSGTYPE_SHIFT			18
#घोषणा ADF_VF2PF_MSGTYPE_INIT			0x3
#घोषणा ADF_VF2PF_MSGTYPE_SHUTDOWN		0x4
#घोषणा ADF_VF2PF_MSGTYPE_VERSION_REQ		0x5
#घोषणा ADF_VF2PF_MSGTYPE_COMPAT_VER_REQ	0x6

/* VF->PF Compatible Version Request */
#घोषणा ADF_VF2PF_COMPAT_VER_REQ_SHIFT		22

/* Collision detection */
#घोषणा ADF_IOV_MSG_COLLISION_DETECT_DELAY	10
#घोषणा ADF_IOV_MSG_ACK_DELAY			2
#घोषणा ADF_IOV_MSG_ACK_MAX_RETRY		100
#घोषणा ADF_IOV_MSG_RETRY_DELAY			5
#घोषणा ADF_IOV_MSG_MAX_RETRIES			3
#घोषणा ADF_IOV_MSG_RESP_TIMEOUT	(ADF_IOV_MSG_ACK_DELAY * \
					 ADF_IOV_MSG_ACK_MAX_RETRY + \
					 ADF_IOV_MSG_COLLISION_DETECT_DELAY)
#पूर्ण_अगर /* ADF_IOV_MSG_H */
