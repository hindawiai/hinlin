<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0-only WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * linux/can.h
 *
 * Definitions क्रम CAN network layer (socket addr / CAN frame / CAN filter)
 *
 * Authors: Oliver Hartkopp <oliver.hartkopp@volkswagen.de>
 *          Urs Thuermann   <urs.thuermann@volkswagen.de>
 * Copyright (c) 2002-2007 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
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
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#अगर_अघोषित _UAPI_CAN_H
#घोषणा _UAPI_CAN_H

#समावेश <linux/types.h>
#समावेश <linux/socket.h>

/* controller area network (CAN) kernel definitions */

/* special address description flags क्रम the CAN_ID */
#घोषणा CAN_EFF_FLAG 0x80000000U /* EFF/SFF is set in the MSB */
#घोषणा CAN_RTR_FLAG 0x40000000U /* remote transmission request */
#घोषणा CAN_ERR_FLAG 0x20000000U /* error message frame */

/* valid bits in CAN ID क्रम frame क्रमmats */
#घोषणा CAN_SFF_MASK 0x000007FFU /* standard frame क्रमmat (SFF) */
#घोषणा CAN_EFF_MASK 0x1FFFFFFFU /* extended frame क्रमmat (EFF) */
#घोषणा CAN_ERR_MASK 0x1FFFFFFFU /* omit EFF, RTR, ERR flags */

/*
 * Controller Area Network Identअगरier काष्ठाure
 *
 * bit 0-28	: CAN identअगरier (11/29 bit)
 * bit 29	: error message frame flag (0 = data frame, 1 = error message)
 * bit 30	: remote transmission request flag (1 = rtr frame)
 * bit 31	: frame क्रमmat flag (0 = standard 11 bit, 1 = extended 29 bit)
 */
प्रकार __u32 canid_t;

#घोषणा CAN_SFF_ID_BITS		11
#घोषणा CAN_EFF_ID_BITS		29

/*
 * Controller Area Network Error Message Frame Mask काष्ठाure
 *
 * bit 0-28	: error class mask (see include/uapi/linux/can/error.h)
 * bit 29-31	: set to zero
 */
प्रकार __u32 can_err_mask_t;

/* CAN payload length and DLC definitions according to ISO 11898-1 */
#घोषणा CAN_MAX_DLC 8
#घोषणा CAN_MAX_RAW_DLC 15
#घोषणा CAN_MAX_DLEN 8

/* CAN FD payload length and DLC definitions according to ISO 11898-7 */
#घोषणा CANFD_MAX_DLC 15
#घोषणा CANFD_MAX_DLEN 64

/**
 * काष्ठा can_frame - Classical CAN frame काष्ठाure (aka CAN 2.0B)
 * @can_id:   CAN ID of the frame and CAN_*_FLAG flags, see canid_t definition
 * @len:      CAN frame payload length in byte (0 .. 8)
 * @can_dlc:  deprecated name क्रम CAN frame payload length in byte (0 .. 8)
 * @__pad:    padding
 * @__res0:   reserved / padding
 * @len8_dlc: optional DLC value (9 .. 15) at 8 byte payload length
 *            len8_dlc contains values from 9 .. 15 when the payload length is
 *            8 bytes but the DLC value (see ISO 11898-1) is greater then 8.
 *            CAN_CTRLMODE_CC_LEN8_DLC flag has to be enabled in CAN driver.
 * @data:     CAN frame payload (up to 8 byte)
 */
काष्ठा can_frame अणु
	canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
	जोड़ अणु
		/* CAN frame payload length in byte (0 .. CAN_MAX_DLEN)
		 * was previously named can_dlc so we need to carry that
		 * name क्रम legacy support
		 */
		__u8 len;
		__u8 can_dlc; /* deprecated */
	पूर्ण __attribute__((packed)); /* disable padding added in some ABIs */
	__u8 __pad; /* padding */
	__u8 __res0; /* reserved / padding */
	__u8 len8_dlc; /* optional DLC क्रम 8 byte payload length (9 .. 15) */
	__u8 data[CAN_MAX_DLEN] __attribute__((aligned(8)));
पूर्ण;

/*
 * defined bits क्रम canfd_frame.flags
 *
 * The use of काष्ठा canfd_frame implies the Extended Data Length (EDL) bit to
 * be set in the CAN frame bitstream on the wire. The EDL bit चयन turns
 * the CAN controllers bitstream processor पूर्णांकo the CAN FD mode which creates
 * two new options within the CAN FD frame specअगरication:
 *
 * Bit Rate Switch - to indicate a second bitrate is/was used क्रम the payload
 * Error State Indicator - represents the error state of the transmitting node
 *
 * As the CANFD_ESI bit is पूर्णांकernally generated by the transmitting CAN
 * controller only the CANFD_BRS bit is relevant क्रम real CAN controllers when
 * building a CAN FD frame क्रम transmission. Setting the CANFD_ESI bit can make
 * sense क्रम भव CAN पूर्णांकerfaces to test applications with echoed frames.
 */
#घोषणा CANFD_BRS 0x01 /* bit rate चयन (second bitrate क्रम payload data) */
#घोषणा CANFD_ESI 0x02 /* error state indicator of the transmitting node */

/**
 * काष्ठा canfd_frame - CAN flexible data rate frame काष्ठाure
 * @can_id: CAN ID of the frame and CAN_*_FLAG flags, see canid_t definition
 * @len:    frame payload length in byte (0 .. CANFD_MAX_DLEN)
 * @flags:  additional flags क्रम CAN FD
 * @__res0: reserved / padding
 * @__res1: reserved / padding
 * @data:   CAN FD frame payload (up to CANFD_MAX_DLEN byte)
 */
काष्ठा canfd_frame अणु
	canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
	__u8    len;     /* frame payload length in byte */
	__u8    flags;   /* additional flags क्रम CAN FD */
	__u8    __res0;  /* reserved / padding */
	__u8    __res1;  /* reserved / padding */
	__u8    data[CANFD_MAX_DLEN] __attribute__((aligned(8)));
पूर्ण;

#घोषणा CAN_MTU		(माप(काष्ठा can_frame))
#घोषणा CANFD_MTU	(माप(काष्ठा canfd_frame))

/* particular protocols of the protocol family PF_CAN */
#घोषणा CAN_RAW		1 /* RAW sockets */
#घोषणा CAN_BCM		2 /* Broadcast Manager */
#घोषणा CAN_TP16	3 /* VAG Transport Protocol v1.6 */
#घोषणा CAN_TP20	4 /* VAG Transport Protocol v2.0 */
#घोषणा CAN_MCNET	5 /* Bosch MCNet */
#घोषणा CAN_ISOTP	6 /* ISO 15765-2 Transport Protocol */
#घोषणा CAN_J1939	7 /* SAE J1939 */
#घोषणा CAN_NPROTO	8

#घोषणा SOL_CAN_BASE 100

/**
 * काष्ठा sockaddr_can - the sockaddr काष्ठाure क्रम CAN sockets
 * @can_family:  address family number AF_CAN.
 * @can_अगरindex: CAN network पूर्णांकerface index.
 * @can_addr:    protocol specअगरic address inक्रमmation
 */
काष्ठा sockaddr_can अणु
	__kernel_sa_family_t can_family;
	पूर्णांक         can_अगरindex;
	जोड़ अणु
		/* transport protocol class address inक्रमmation (e.g. ISOTP) */
		काष्ठा अणु canid_t rx_id, tx_id; पूर्ण tp;

		/* J1939 address inक्रमmation */
		काष्ठा अणु
			/* 8 byte name when using dynamic addressing */
			__u64 name;

			/* pgn:
			 * 8 bit: PS in PDU2 हाल, अन्यथा 0
			 * 8 bit: PF
			 * 1 bit: DP
			 * 1 bit: reserved
			 */
			__u32 pgn;

			/* 1 byte address */
			__u8 addr;
		पूर्ण j1939;

		/* reserved क्रम future CAN protocols address inक्रमmation */
	पूर्ण can_addr;
पूर्ण;

/**
 * काष्ठा can_filter - CAN ID based filter in can_रेजिस्टर().
 * @can_id:   relevant bits of CAN ID which are not masked out.
 * @can_mask: CAN mask (see description)
 *
 * Description:
 * A filter matches, when
 *
 *          <received_can_id> & mask == can_id & mask
 *
 * The filter can be inverted (CAN_INV_FILTER bit set in can_id) or it can
 * filter क्रम error message frames (CAN_ERR_FLAG bit set in mask).
 */
काष्ठा can_filter अणु
	canid_t can_id;
	canid_t can_mask;
पूर्ण;

#घोषणा CAN_INV_FILTER 0x20000000U /* to be set in can_filter.can_id */
#घोषणा CAN_RAW_FILTER_MAX 512 /* maximum number of can_filter set via setsockopt() */

#पूर्ण_अगर /* !_UAPI_CAN_H */
