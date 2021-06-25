<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_ALPHA_SOCKIOS_H
#घोषणा _ASM_ALPHA_SOCKIOS_H

/* Socket-level I/O control calls. */

#घोषणा FIOGETOWN	_IOR('f', 123, पूर्णांक)
#घोषणा FIOSETOWN 	_IOW('f', 124, पूर्णांक)

#घोषणा SIOCATMARK	_IOR('s', 7, पूर्णांक)
#घोषणा SIOCSPGRP	_IOW('s', 8, pid_t)
#घोषणा SIOCGPGRP	_IOR('s', 9, pid_t)

#घोषणा SIOCGSTAMP_OLD	0x8906		/* Get stamp (समयval) */
#घोषणा SIOCGSTAMPNS_OLD 0x8907		/* Get stamp (बारpec) */

#पूर्ण_अगर /* _ASM_ALPHA_SOCKIOS_H */
