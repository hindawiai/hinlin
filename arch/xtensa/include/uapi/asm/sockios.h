<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/sockios.h
 *
 * Socket-level I/O control calls.  Copied from MIPS.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995 by Ralf Baechle
 * Copyright (C) 2001 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_SOCKIOS_H
#घोषणा _XTENSA_SOCKIOS_H

#समावेश <यंत्र/ioctl.h>

/* Socket-level I/O control calls. */

#घोषणा FIOGETOWN	_IOR('f', 123, पूर्णांक)
#घोषणा FIOSETOWN 	_IOW('f', 124, पूर्णांक)

#घोषणा SIOCATMARK	_IOR('s', 7, पूर्णांक)
#घोषणा SIOCSPGRP	_IOW('s', 8, pid_t)
#घोषणा SIOCGPGRP	_IOR('s', 9, pid_t)

#घोषणा SIOCGSTAMP_OLD	0x8906		/* Get stamp (समयval) */
#घोषणा SIOCGSTAMPNS_OLD 0x8907		/* Get stamp (बारpec) */

#पूर्ण_अगर	/* _XTENSA_SOCKIOS_H */
