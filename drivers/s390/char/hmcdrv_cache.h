<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    SE/HMC Drive (Read) Cache Functions
 *
 *    Copyright IBM Corp. 2013
 *    Author(s): Ralf Hoppe (rhoppe@de.ibm.com)
 */

#अगर_अघोषित __HMCDRV_CACHE_H__
#घोषणा __HMCDRV_CACHE_H__

#समावेश <linux/mmzone.h>
#समावेश "hmcdrv_ftp.h"

#घोषणा HMCDRV_CACHE_SIZE_DFLT	(MAX_ORDER_NR_PAGES * PAGE_SIZE / 2UL)

प्रकार sमाप_प्रकार (*hmcdrv_cache_ftpfunc)(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp,
					माप_प्रकार *fsize);

sमाप_प्रकार hmcdrv_cache_cmd(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp,
			 hmcdrv_cache_ftpfunc func);
पूर्णांक hmcdrv_cache_startup(माप_प्रकार cachesize);
व्योम hmcdrv_cache_shutकरोwn(व्योम);

#पूर्ण_अगर	 /* __HMCDRV_CACHE_H__ */
