<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_SH_SOCKIOS_H
#घोषणा __ASM_SH_SOCKIOS_H

#समावेश <linux/समय_प्रकारypes.h>

/* Socket-level I/O control calls. */
#घोषणा FIOGETOWN	_IOR('f', 123, पूर्णांक)
#घोषणा FIOSETOWN 	_IOW('f', 124, पूर्णांक)

#घोषणा SIOCATMARK	_IOR('s', 7, पूर्णांक)
#घोषणा SIOCSPGRP	_IOW('s', 8, pid_t)
#घोषणा SIOCGPGRP	_IOR('s', 9, pid_t)

#घोषणा SIOCGSTAMP_OLD	_IOR('s', 100, काष्ठा __kernel_old_समयval) /* Get stamp (समयval) */
#घोषणा SIOCGSTAMPNS_OLD _IOR('s', 101, काष्ठा __kernel_old_बारpec) /* Get stamp (बारpec) */

#पूर्ण_अगर /* __ASM_SH_SOCKIOS_H */
