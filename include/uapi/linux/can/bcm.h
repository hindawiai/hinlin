<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0-only WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * linux/can/bcm.h
 *
 * Definitions क्रम CAN Broadcast Manager (BCM)
 *
 * Author: Oliver Hartkopp <oliver.hartkopp@volkswagen.de>
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

#अगर_अघोषित _UAPI_CAN_BCM_H
#घोषणा _UAPI_CAN_BCM_H

#समावेश <linux/types.h>
#समावेश <linux/can.h>

काष्ठा bcm_समयval अणु
	दीर्घ tv_sec;
	दीर्घ tv_usec;
पूर्ण;

/**
 * काष्ठा bcm_msg_head - head of messages to/from the broadcast manager
 * @opcode:    opcode, see क्रमागत below.
 * @flags:     special flags, see below.
 * @count:     number of frames to send beक्रमe changing पूर्णांकerval.
 * @ival1:     पूर्णांकerval क्रम the first @count frames.
 * @ival2:     पूर्णांकerval क्रम the following frames.
 * @can_id:    CAN ID of frames to be sent or received.
 * @nframes:   number of frames appended to the message head.
 * @frames:    array of CAN frames.
 */
काष्ठा bcm_msg_head अणु
	__u32 opcode;
	__u32 flags;
	__u32 count;
	काष्ठा bcm_समयval ival1, ival2;
	canid_t can_id;
	__u32 nframes;
	काष्ठा can_frame frames[0];
पूर्ण;

क्रमागत अणु
	TX_SETUP = 1,	/* create (cyclic) transmission task */
	TX_DELETE,	/* हटाओ (cyclic) transmission task */
	TX_READ,	/* पढ़ो properties of (cyclic) transmission task */
	TX_SEND,	/* send one CAN frame */
	RX_SETUP,	/* create RX content filter subscription */
	RX_DELETE,	/* हटाओ RX content filter subscription */
	RX_READ,	/* पढ़ो properties of RX content filter subscription */
	TX_STATUS,	/* reply to TX_READ request */
	TX_EXPIRED,	/* notअगरication on perक्रमmed transmissions (count=0) */
	RX_STATUS,	/* reply to RX_READ request */
	RX_TIMEOUT,	/* cyclic message is असलent */
	RX_CHANGED	/* updated CAN frame (detected content change) */
पूर्ण;

#घोषणा SETTIMER            0x0001
#घोषणा STARTTIMER          0x0002
#घोषणा TX_COUNTEVT         0x0004
#घोषणा TX_ANNOUNCE         0x0008
#घोषणा TX_CP_CAN_ID        0x0010
#घोषणा RX_FILTER_ID        0x0020
#घोषणा RX_CHECK_DLC        0x0040
#घोषणा RX_NO_AUTOTIMER     0x0080
#घोषणा RX_ANNOUNCE_RESUME  0x0100
#घोषणा TX_RESET_MULTI_IDX  0x0200
#घोषणा RX_RTR_FRAME        0x0400
#घोषणा CAN_FD_FRAME        0x0800

#पूर्ण_अगर /* !_UAPI_CAN_BCM_H */
