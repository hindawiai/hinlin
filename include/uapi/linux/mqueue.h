<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/* Copyright (C) 2003 Krzysztof Benedyczak & Michal Wronski

   This program is मुक्त software; you can redistribute it and/or
   modअगरy it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   It is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License क्रम more details.

   You should have received a copy of the GNU Lesser General Public
   License aदीर्घ with this software; अगर not, ग_लिखो to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#अगर_अघोषित _LINUX_MQUEUE_H
#घोषणा _LINUX_MQUEUE_H

#समावेश <linux/types.h>

#घोषणा MQ_PRIO_MAX 	32768
/* per-uid limit of kernel memory used by mqueue, in bytes */
#घोषणा MQ_BYTES_MAX	819200

काष्ठा mq_attr अणु
	__kernel_दीर्घ_t	mq_flags;	/* message queue flags			*/
	__kernel_दीर्घ_t	mq_maxmsg;	/* maximum number of messages		*/
	__kernel_दीर्घ_t	mq_msgsize;	/* maximum message size			*/
	__kernel_दीर्घ_t	mq_curmsgs;	/* number of messages currently queued	*/
	__kernel_दीर्घ_t	__reserved[4];	/* ignored क्रम input, zeroed क्रम output */
पूर्ण;

/*
 * SIGEV_THREAD implementation:
 * SIGEV_THREAD must be implemented in user space. If SIGEV_THREAD is passed
 * to mq_notअगरy, then
 * - sigev_signo must be the file descriptor of an AF_NETLINK socket. It's not
 *   necessary that the socket is bound.
 * - sigev_value.sival_ptr must poपूर्णांक to a cookie that is NOTIFY_COOKIE_LEN
 *   bytes दीर्घ.
 * If the notअगरication is triggered, then the cookie is sent to the netlink
 * socket. The last byte of the cookie is replaced with the NOTIFY_?? codes:
 * NOTIFY_WOKENUP अगर the notअगरication got triggered, NOTIFY_REMOVED अगर it was
 * हटाओd, either due to a बंद() on the message queue fd or due to a
 * mq_notअगरy() that हटाओd the notअगरication.
 */
#घोषणा NOTIFY_NONE	0
#घोषणा NOTIFY_WOKENUP	1
#घोषणा NOTIFY_REMOVED	2

#घोषणा NOTIFY_COOKIE_LEN	32

#पूर्ण_अगर
