<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 2013
 *    Author(s): Ralf Hoppe (rhoppe@de.ibm.com)
 */

#अगर_अघोषित _SCLP_DIAG_H
#घोषणा _SCLP_DIAG_H

#समावेश <linux/types.h>

/* वापस codes क्रम Diagnostic Test FTP Service, as indicated in member
 * sclp_diag_ftp::ldflg
 */
#घोषणा SCLP_DIAG_FTP_OK	0x80U /* success */
#घोषणा SCLP_DIAG_FTP_LDFAIL	0x01U /* load failed */
#घोषणा SCLP_DIAG_FTP_LDNPERM	0x02U /* not allowed */
#घोषणा SCLP_DIAG_FTP_LDRUNS	0x03U /* LD runs */
#घोषणा SCLP_DIAG_FTP_LDNRUNS	0x04U /* LD करोes not run */

#घोषणा SCLP_DIAG_FTP_XPCX	0x80 /* PCX communication code */
#घोषणा SCLP_DIAG_FTP_ROUTE	4 /* routing code क्रम new FTP service */

/*
 * length of Diagnostic Test FTP Service event buffer
 */
#घोषणा SCLP_DIAG_FTP_EVBUF_LEN				\
	(दुरत्व(काष्ठा sclp_diag_evbuf, mdd) +	\
	 माप(काष्ठा sclp_diag_ftp))

/**
 * काष्ठा sclp_diag_ftp - Diagnostic Test FTP Service model-dependent data
 * @pcx: code क्रम PCX communication (should be 0x80)
 * @ldflg: load flag (see defines above)
 * @cmd: FTP command
 * @pgsize: page size (0 = 4kB, 1 = large page size)
 * @srcflg: source flag
 * @spare: reserved (zeroes)
 * @offset: file offset
 * @fsize: file size
 * @length: buffer size resp. bytes transferred
 * @failaddr: failing address
 * @bufaddr: buffer address, भव
 * @asce: region or segment table designation
 * @fident: file name (ASCII, zero-terminated)
 */
काष्ठा sclp_diag_ftp अणु
	u8 pcx;
	u8 ldflg;
	u8 cmd;
	u8 pgsize;
	u8 srcflg;
	u8 spare;
	u64 offset;
	u64 fsize;
	u64 length;
	u64 failaddr;
	u64 bufaddr;
	u64 asce;

	u8 fident[256];
पूर्ण __packed;

/**
 * काष्ठा sclp_diag_evbuf - Diagnostic Test (ET7) Event Buffer
 * @hdr: event buffer header
 * @route: diagnostic route
 * @mdd: model-dependent data (@route dependent)
 */
काष्ठा sclp_diag_evbuf अणु
	काष्ठा evbuf_header hdr;
	u16 route;

	जोड़ अणु
		काष्ठा sclp_diag_ftp ftp;
	पूर्ण mdd;
पूर्ण __packed;

/**
 * काष्ठा sclp_diag_sccb - Diagnostic Test (ET7) SCCB
 * @hdr: SCCB header
 * @evbuf: event buffer
 */
काष्ठा sclp_diag_sccb अणु

	काष्ठा sccb_header hdr;
	काष्ठा sclp_diag_evbuf evbuf;
पूर्ण __packed;

#पूर्ण_अगर /* _SCLP_DIAG_H */
