<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    SE/HMC Drive FTP Services
 *
 *    Copyright IBM Corp. 2013
 *    Author(s): Ralf Hoppe (rhoppe@de.ibm.com)
 */

#अगर_अघोषित __HMCDRV_FTP_H__
#घोषणा __HMCDRV_FTP_H__

#समावेश <linux/types.h> /* माप_प्रकार, loff_t */

/*
 * HMC drive FTP Service max. length of path (w/ EOS)
 */
#घोषणा HMCDRV_FTP_FIDENT_MAX 192

/**
 * क्रमागत hmcdrv_ftp_cmdid - HMC drive FTP commands
 * @HMCDRV_FTP_NOOP: करो nothing (only क्रम probing)
 * @HMCDRV_FTP_GET: पढ़ो a file
 * @HMCDRV_FTP_PUT: (over-) ग_लिखो a file
 * @HMCDRV_FTP_APPEND: append to a file
 * @HMCDRV_FTP_सूची: list directory दीर्घ (ls -l)
 * @HMCDRV_FTP_NLIST: list files, no directories (name list)
 * @HMCDRV_FTP_DELETE: delete a file
 * @HMCDRV_FTP_CANCEL: cancel operation (SCLP/LPAR only)
 */
क्रमागत hmcdrv_ftp_cmdid अणु
	HMCDRV_FTP_NOOP = 0,
	HMCDRV_FTP_GET = 1,
	HMCDRV_FTP_PUT = 2,
	HMCDRV_FTP_APPEND = 3,
	HMCDRV_FTP_सूची = 4,
	HMCDRV_FTP_NLIST = 5,
	HMCDRV_FTP_DELETE = 6,
	HMCDRV_FTP_CANCEL = 7
पूर्ण;

/**
 * काष्ठा hmcdrv_ftp_cmdspec - FTP command specअगरication
 * @id: FTP command ID
 * @ofs: offset in file
 * @fname: filename (ASCII), null-terminated
 * @buf: kernel-space transfer data buffer, 4k aligned
 * @len: (max) number of bytes to transfer from/to @buf
 */
काष्ठा hmcdrv_ftp_cmdspec अणु
	क्रमागत hmcdrv_ftp_cmdid id;
	loff_t ofs;
	स्थिर अक्षर *fname;
	व्योम __kernel *buf;
	माप_प्रकार len;
पूर्ण;

पूर्णांक hmcdrv_ftp_startup(व्योम);
व्योम hmcdrv_ftp_shutकरोwn(व्योम);
पूर्णांक hmcdrv_ftp_probe(व्योम);
sमाप_प्रकार hmcdrv_ftp_करो(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp);
sमाप_प्रकार hmcdrv_ftp_cmd(अक्षर __kernel *cmd, loff_t offset,
		       अक्षर __user *buf, माप_प्रकार len);

#पूर्ण_अगर	 /* __HMCDRV_FTP_H__ */
