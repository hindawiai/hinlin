<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  include/linux/eventpoll.h ( Efficient event polling implementation )
 *  Copyright (C) 2001,...,2006	 Davide Libenzi
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Davide Libenzi <davidel@xmailserver.org>
 *
 */

#अगर_अघोषित _UAPI_LINUX_EVENTPOLL_H
#घोषणा _UAPI_LINUX_EVENTPOLL_H

/* For O_CLOEXEC */
#समावेश <linux/fcntl.h>
#समावेश <linux/types.h>

/* Flags क्रम epoll_create1.  */
#घोषणा EPOLL_CLOEXEC O_CLOEXEC

/* Valid opcodes to issue to sys_epoll_ctl() */
#घोषणा EPOLL_CTL_ADD 1
#घोषणा EPOLL_CTL_DEL 2
#घोषणा EPOLL_CTL_MOD 3

/* Epoll event masks */
#घोषणा EPOLLIN		(__क्रमce __poll_t)0x00000001
#घोषणा EPOLLPRI	(__क्रमce __poll_t)0x00000002
#घोषणा EPOLLOUT	(__क्रमce __poll_t)0x00000004
#घोषणा EPOLLERR	(__क्रमce __poll_t)0x00000008
#घोषणा EPOLLHUP	(__क्रमce __poll_t)0x00000010
#घोषणा EPOLLNVAL	(__क्रमce __poll_t)0x00000020
#घोषणा EPOLLRDNORM	(__क्रमce __poll_t)0x00000040
#घोषणा EPOLLRDBAND	(__क्रमce __poll_t)0x00000080
#घोषणा EPOLLWRNORM	(__क्रमce __poll_t)0x00000100
#घोषणा EPOLLWRBAND	(__क्रमce __poll_t)0x00000200
#घोषणा EPOLLMSG	(__क्रमce __poll_t)0x00000400
#घोषणा EPOLLRDHUP	(__क्रमce __poll_t)0x00002000

/* Set exclusive wakeup mode क्रम the target file descriptor */
#घोषणा EPOLLEXCLUSIVE	((__क्रमce __poll_t)(1U << 28))

/*
 * Request the handling of प्रणाली wakeup events so as to prevent प्रणाली suspends
 * from happening जबतक those events are being processed.
 *
 * Assuming neither EPOLLET nor EPOLLONESHOT is set, प्रणाली suspends will not be
 * re-allowed until epoll_रुको is called again after consuming the wakeup
 * event(s).
 *
 * Requires CAP_BLOCK_SUSPEND
 */
#घोषणा EPOLLWAKEUP	((__क्रमce __poll_t)(1U << 29))

/* Set the One Shot behaviour क्रम the target file descriptor */
#घोषणा EPOLLONESHOT	((__क्रमce __poll_t)(1U << 30))

/* Set the Edge Triggered behaviour क्रम the target file descriptor */
#घोषणा EPOLLET		((__क्रमce __poll_t)(1U << 31))

/* 
 * On x86-64 make the 64bit काष्ठाure have the same alignment as the
 * 32bit काष्ठाure. This makes 32bit emulation easier.
 *
 * UML/x86_64 needs the same packing as x86_64
 */
#अगर_घोषित __x86_64__
#घोषणा EPOLL_PACKED __attribute__((packed))
#अन्यथा
#घोषणा EPOLL_PACKED
#पूर्ण_अगर

काष्ठा epoll_event अणु
	__poll_t events;
	__u64 data;
पूर्ण EPOLL_PACKED;

#अगर_घोषित CONFIG_PM_SLEEP
अटल अंतरभूत व्योम ep_take_care_of_epollwakeup(काष्ठा epoll_event *epev)
अणु
	अगर ((epev->events & EPOLLWAKEUP) && !capable(CAP_BLOCK_SUSPEND))
		epev->events &= ~EPOLLWAKEUP;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ep_take_care_of_epollwakeup(काष्ठा epoll_event *epev)
अणु
	epev->events &= ~EPOLLWAKEUP;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _UAPI_LINUX_EVENTPOLL_H */
