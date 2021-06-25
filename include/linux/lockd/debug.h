<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/lockd/debug.h
 *
 * Debugging stuff.
 *
 * Copyright (C) 1996 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित LINUX_LOCKD_DEBUG_H
#घोषणा LINUX_LOCKD_DEBUG_H

#समावेश <linux/sunrpc/debug.h>

/*
 * Enable lockd debugging.
 * Requires RPC_DEBUG.
 */
#अघोषित अगरdebug
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define अगरdebug(flag)		अगर (unlikely(nlm_debug & NLMDBG_##flag))
#अन्यथा
# define अगरdebug(flag)		अगर (0)
#पूर्ण_अगर

/*
 * Debug flags
 */
#घोषणा NLMDBG_SVC		0x0001
#घोषणा NLMDBG_CLIENT		0x0002
#घोषणा NLMDBG_CLNTLOCK		0x0004
#घोषणा NLMDBG_SVCLOCK		0x0008
#घोषणा NLMDBG_MONITOR		0x0010
#घोषणा NLMDBG_CLNTSUBS		0x0020
#घोषणा NLMDBG_SVCSUBS		0x0040
#घोषणा NLMDBG_HOSTCACHE	0x0080
#घोषणा NLMDBG_XDR		0x0100
#घोषणा NLMDBG_ALL		0x7fff

#पूर्ण_अगर /* LINUX_LOCKD_DEBUG_H */
