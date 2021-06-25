<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_POLL_H
#घोषणा __ASM_GENERIC_POLL_H

/* These are specअगरied by iBCS2 */
#घोषणा POLLIN		0x0001
#घोषणा POLLPRI		0x0002
#घोषणा POLLOUT		0x0004
#घोषणा POLLERR		0x0008
#घोषणा POLLHUP		0x0010
#घोषणा POLLNVAL	0x0020

/* The rest seem to be more-or-less nonstandard. Check them! */
#घोषणा POLLRDNORM	0x0040
#घोषणा POLLRDBAND	0x0080
#अगर_अघोषित POLLWRNORM
#घोषणा POLLWRNORM	0x0100
#पूर्ण_अगर
#अगर_अघोषित POLLWRBAND
#घोषणा POLLWRBAND	0x0200
#पूर्ण_अगर
#अगर_अघोषित POLLMSG
#घोषणा POLLMSG		0x0400
#पूर्ण_अगर
#अगर_अघोषित POLLREMOVE
#घोषणा POLLREMOVE	0x1000
#पूर्ण_अगर
#अगर_अघोषित POLLRDHUP
#घोषणा POLLRDHUP       0x2000
#पूर्ण_अगर

#घोषणा POLLFREE	(__क्रमce __poll_t)0x4000	/* currently only क्रम epoll */

#घोषणा POLL_BUSY_LOOP	(__क्रमce __poll_t)0x8000

काष्ठा pollfd अणु
	पूर्णांक fd;
	लघु events;
	लघु revents;
पूर्ण;

#पूर्ण_अगर	/* __ASM_GENERIC_POLL_H */
