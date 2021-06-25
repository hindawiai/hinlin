<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांग_eni.h - Driver-specअगरic declarations of the ENI driver (क्रम use by
	       driver-specअगरic utilities) */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */


#अगर_अघोषित LINUX_ATM_ENI_H
#घोषणा LINUX_ATM_ENI_H

#समावेश <linux/aपंचांगioc.h>


काष्ठा eni_multipliers अणु
	पूर्णांक tx,rx;	/* values are in percent and must be > 100 */
पूर्ण;


#घोषणा ENI_MEMDUMP     _IOW('a',ATMIOC_SARPRV,काष्ठा aपंचांगअगर_sioc)
                                                /* prपूर्णांकk memory map */
#घोषणा ENI_SETMULT	_IOW('a',ATMIOC_SARPRV+7,काष्ठा aपंचांगअगर_sioc)
						/* set buffer multipliers */

#पूर्ण_अगर
