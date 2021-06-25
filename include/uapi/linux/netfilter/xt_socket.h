<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_SOCKET_H
#घोषणा _XT_SOCKET_H

#समावेश <linux/types.h>

क्रमागत अणु
	XT_SOCKET_TRANSPARENT = 1 << 0,
	XT_SOCKET_NOWILDCARD = 1 << 1,
	XT_SOCKET_RESTORESKMARK = 1 << 2,
पूर्ण;

काष्ठा xt_socket_mtinfo1 अणु
	__u8 flags;
पूर्ण;
#घोषणा XT_SOCKET_FLAGS_V1 XT_SOCKET_TRANSPARENT

काष्ठा xt_socket_mtinfo2 अणु
	__u8 flags;
पूर्ण;
#घोषणा XT_SOCKET_FLAGS_V2 (XT_SOCKET_TRANSPARENT | XT_SOCKET_NOWILDCARD)

काष्ठा xt_socket_mtinfo3 अणु
	__u8 flags;
पूर्ण;
#घोषणा XT_SOCKET_FLAGS_V3 (XT_SOCKET_TRANSPARENT \
			   | XT_SOCKET_NOWILDCARD \
			   | XT_SOCKET_RESTORESKMARK)

#पूर्ण_अगर /* _XT_SOCKET_H */
