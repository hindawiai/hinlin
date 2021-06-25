<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    DIAGNOSE X'2C4' inकाष्ठाion based SE/HMC FTP Services, useable on z/VM
 *
 *    Notice that all functions exported here are not reentrant.
 *    So usage should be exclusive, ensured by the caller (e.g. using a
 *    mutex).
 *
 *    Copyright IBM Corp. 2013
 *    Author(s): Ralf Hoppe (rhoppe@de.ibm.com)
 */

#अगर_अघोषित __DIAG_FTP_H__
#घोषणा __DIAG_FTP_H__

#समावेश "hmcdrv_ftp.h"

पूर्णांक diag_ftp_startup(व्योम);
व्योम diag_ftp_shutकरोwn(व्योम);
sमाप_प्रकार diag_ftp_cmd(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp, माप_प्रकार *fsize);

#पूर्ण_अगर	 /* __DIAG_FTP_H__ */
