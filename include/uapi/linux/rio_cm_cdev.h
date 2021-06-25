<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * Copyright (c) 2015, Integrated Device Technology Inc.
 * Copyright (c) 2015, Prodrive Technologies
 * Copyright (c) 2015, RapidIO Trade Association
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License(GPL) Version 2, or the BSD-3 Clause license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary क्रमm must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the करोcumentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to enकरोrse or promote products derived from this software without
 * specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _RIO_CM_CDEV_H_
#घोषणा _RIO_CM_CDEV_H_

#समावेश <linux/types.h>

काष्ठा rio_cm_channel अणु
	__u16 id;
	__u16 remote_channel;
	__u16 remote_destid;
	__u8 mport_id;
पूर्ण;

काष्ठा rio_cm_msg अणु
	__u16 ch_num;
	__u16 size;
	__u32 rxto;	/* receive समयout in mSec. 0 = blocking */
	__u64 msg;
पूर्ण;

काष्ठा rio_cm_accept अणु
	__u16 ch_num;
	__u16 pad0;
	__u32 रुको_to;	/* accept समयout in mSec. 0 = blocking */
पूर्ण;

/* RapidIO Channelized Messaging Driver IOCTLs */
#घोषणा RIO_CM_IOC_MAGIC	'c'

#घोषणा RIO_CM_EP_GET_LIST_SIZE	_IOWR(RIO_CM_IOC_MAGIC, 1, __u32)
#घोषणा RIO_CM_EP_GET_LIST	_IOWR(RIO_CM_IOC_MAGIC, 2, __u32)
#घोषणा RIO_CM_CHAN_CREATE	_IOWR(RIO_CM_IOC_MAGIC, 3, __u16)
#घोषणा RIO_CM_CHAN_CLOSE	_IOW(RIO_CM_IOC_MAGIC, 4, __u16)
#घोषणा RIO_CM_CHAN_BIND	_IOW(RIO_CM_IOC_MAGIC, 5, काष्ठा rio_cm_channel)
#घोषणा RIO_CM_CHAN_LISTEN	_IOW(RIO_CM_IOC_MAGIC, 6, __u16)
#घोषणा RIO_CM_CHAN_ACCEPT	_IOWR(RIO_CM_IOC_MAGIC, 7, काष्ठा rio_cm_accept)
#घोषणा RIO_CM_CHAN_CONNECT	_IOW(RIO_CM_IOC_MAGIC, 8, काष्ठा rio_cm_channel)
#घोषणा RIO_CM_CHAN_SEND	_IOW(RIO_CM_IOC_MAGIC, 9, काष्ठा rio_cm_msg)
#घोषणा RIO_CM_CHAN_RECEIVE	_IOWR(RIO_CM_IOC_MAGIC, 10, काष्ठा rio_cm_msg)
#घोषणा RIO_CM_MPORT_GET_LIST	_IOWR(RIO_CM_IOC_MAGIC, 11, __u32)

#पूर्ण_अगर /* _RIO_CM_CDEV_H_ */
