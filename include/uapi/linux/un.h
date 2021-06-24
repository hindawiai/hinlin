<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_UN_H
#घोषणा _LINUX_UN_H

#समावेश <linux/socket.h>

#घोषणा UNIX_PATH_MAX	108

काष्ठा sockaddr_un अणु
	__kernel_sa_family_t sun_family; /* AF_UNIX */
	अक्षर sun_path[UNIX_PATH_MAX];	/* pathname */
पूर्ण;

#घोषणा SIOCUNIXखाता (SIOCPROTOPRIVATE + 0) /* खोलो a socket file with O_PATH */

#पूर्ण_अगर /* _LINUX_UN_H */
