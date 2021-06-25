<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/******************************************************************************
 *
 * aपंचांग_nicstar.h
 *
 * Driver-specअगरic declarations क्रम use by NICSTAR driver specअगरic utils.
 *
 * Author: Rui Prior
 *
 * (C) INESC 1998
 *
 ******************************************************************************/


#अगर_अघोषित LINUX_ATM_NICSTAR_H
#घोषणा LINUX_ATM_NICSTAR_H

/* Note: non-kernel programs including this file must also include
 * sys/types.h क्रम काष्ठा समयval
 */

#समावेश <linux/aपंचांगapi.h>
#समावेश <linux/aपंचांगioc.h>

#घोषणा NS_GETPSTAT	_IOWR('a',ATMIOC_SARPRV+1,काष्ठा aपंचांगअगर_sioc)
						/* get pool statistics */
#घोषणा NS_SETBUFLEV	_IOW('a',ATMIOC_SARPRV+2,काष्ठा aपंचांगअगर_sioc)
						/* set buffer level markers */
#घोषणा NS_ADJBUFLEV	_IO('a',ATMIOC_SARPRV+3)
						/* adjust buffer level */

प्रकार काष्ठा buf_nr
अणु
   अचिन्हित min;
   अचिन्हित init;
   अचिन्हित max;
पूर्णbuf_nr;


प्रकार काष्ठा pool_levels
अणु
   पूर्णांक buftype;
   पूर्णांक count;		/* (At least क्रम now) only used in NS_GETPSTAT */
   buf_nr level;
पूर्ण pool_levels;

/* type must be one of the following: */
#घोषणा NS_BUFTYPE_SMALL 1
#घोषणा NS_BUFTYPE_LARGE 2
#घोषणा NS_BUFTYPE_HUGE 3
#घोषणा NS_BUFTYPE_IOVEC 4


#पूर्ण_अगर /* LINUX_ATM_NICSTAR_H */
