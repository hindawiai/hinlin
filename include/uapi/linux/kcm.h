<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Kernel Connection Multiplexor
 *
 * Copyright (c) 2016 Tom Herbert <tom@herbertland.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * User API to clone KCM sockets and attach transport socket to a KCM
 * multiplexor.
 */

#अगर_अघोषित KCM_KERNEL_H
#घोषणा KCM_KERNEL_H

काष्ठा kcm_attach अणु
	पूर्णांक fd;
	पूर्णांक bpf_fd;
पूर्ण;

काष्ठा kcm_unattach अणु
	पूर्णांक fd;
पूर्ण;

काष्ठा kcm_clone अणु
	पूर्णांक fd;
पूर्ण;

#घोषणा SIOCKCMATTACH	(SIOCPROTOPRIVATE + 0)
#घोषणा SIOCKCMUNATTACH	(SIOCPROTOPRIVATE + 1)
#घोषणा SIOCKCMCLONE	(SIOCPROTOPRIVATE + 2)

#घोषणा KCMPROTO_CONNECTED	0

/* Socket options */
#घोषणा KCM_RECV_DISABLE	1

#पूर्ण_अगर

