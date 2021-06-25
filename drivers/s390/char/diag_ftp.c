<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    DIAGNOSE X'2C4' inकाष्ठाion based HMC FTP services, useable on z/VM
 *
 *    Copyright IBM Corp. 2013
 *    Author(s): Ralf Hoppe (rhoppe@de.ibm.com)
 *
 */

#घोषणा KMSG_COMPONENT "hmcdrv"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/irq.h>
#समावेश <linux/रुको.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र/diag.h>

#समावेश "hmcdrv_ftp.h"
#समावेश "diag_ftp.h"

/* DIAGNOSE X'2C4' वापस codes in Ry */
#घोषणा DIAG_FTP_RET_OK	0 /* HMC FTP started successfully */
#घोषणा DIAG_FTP_RET_EBUSY	4 /* HMC FTP service currently busy */
#घोषणा DIAG_FTP_RET_EIO	8 /* HMC FTP service I/O error */
/* and an artअगरicial extension */
#घोषणा DIAG_FTP_RET_EPERM	2 /* HMC FTP service privilege error */

/* FTP service status codes (after INTR at guest real location 133) */
#घोषणा DIAG_FTP_STAT_OK	0U /* request completed successfully */
#घोषणा DIAG_FTP_STAT_PGCC	4U /* program check condition */
#घोषणा DIAG_FTP_STAT_PGIOE	8U /* paging I/O error */
#घोषणा DIAG_FTP_STAT_TIMEOUT	12U /* समयout */
#घोषणा DIAG_FTP_STAT_EBASE	16U /* base of error codes from SCLP */
#घोषणा DIAG_FTP_STAT_LDFAIL	(DIAG_FTP_STAT_EBASE + 1U) /* failed */
#घोषणा DIAG_FTP_STAT_LDNPERM	(DIAG_FTP_STAT_EBASE + 2U) /* not allowed */
#घोषणा DIAG_FTP_STAT_LDRUNS	(DIAG_FTP_STAT_EBASE + 3U) /* runs */
#घोषणा DIAG_FTP_STAT_LDNRUNS	(DIAG_FTP_STAT_EBASE + 4U) /* not runs */

/**
 * काष्ठा diag_ftp_ldfpl - load file FTP parameter list (LDFPL)
 * @bufaddr: real buffer address (at 4k boundary)
 * @buflen: length of buffer
 * @offset: dir/file offset
 * @पूर्णांकparm: पूर्णांकerruption parameter (unused)
 * @transferred: bytes transferred
 * @fsize: file size, filled on GET
 * @failaddr: failing address
 * @spare: padding
 * @fident: file name - ASCII
 */
काष्ठा diag_ftp_ldfpl अणु
	u64 bufaddr;
	u64 buflen;
	u64 offset;
	u64 पूर्णांकparm;
	u64 transferred;
	u64 fsize;
	u64 failaddr;
	u64 spare;
	u8 fident[HMCDRV_FTP_FIDENT_MAX];
पूर्ण __packed;

अटल DECLARE_COMPLETION(diag_ftp_rx_complete);
अटल पूर्णांक diag_ftp_subcode;

/**
 * diag_ftp_handler() - FTP services IRQ handler
 * @extirq: बाह्यal पूर्णांकerrupt (sub-) code
 * @param32: 32-bit पूर्णांकerruption parameter from &काष्ठा diag_ftp_ldfpl
 * @param64: unused (क्रम 64-bit पूर्णांकerrupt parameters)
 */
अटल व्योम diag_ftp_handler(काष्ठा ext_code extirq,
			     अचिन्हित पूर्णांक param32,
			     अचिन्हित दीर्घ param64)
अणु
	अगर ((extirq.subcode >> 8) != 8)
		वापस; /* not a FTP services sub-code */

	inc_irq_stat(IRQEXT_FTP);
	diag_ftp_subcode = extirq.subcode & 0xffU;
	complete(&diag_ftp_rx_complete);
पूर्ण

/**
 * diag_ftp_2c4() - DIAGNOSE X'2C4' service call
 * @fpl: poपूर्णांकer to prepared LDFPL
 * @cmd: FTP command to be executed
 *
 * Perक्रमms a DIAGNOSE X'2C4' call with (input/output) FTP parameter list
 * @fpl and FTP function code @cmd. In हाल of an error the function करोes
 * nothing and वापसs an (negative) error code.
 *
 * Notes:
 * 1. This function only initiates a transfer, so the caller must रुको
 *    क्रम completion (asynchronous execution).
 * 2. The FTP parameter list @fpl must be aligned to a द्विगुन-word boundary.
 * 3. fpl->bufaddr must be a real address, 4k aligned
 */
अटल पूर्णांक diag_ftp_2c4(काष्ठा diag_ftp_ldfpl *fpl,
			क्रमागत hmcdrv_ftp_cmdid cmd)
अणु
	पूर्णांक rc;

	diag_stat_inc(DIAG_STAT_X2C4);
	यंत्र अस्थिर(
		"	diag	%[addr],%[cmd],0x2c4\n"
		"0:	j	2f\n"
		"1:	la	%[rc],%[err]\n"
		"2:\n"
		EX_TABLE(0b, 1b)
		: [rc] "=d" (rc), "+m" (*fpl)
		: [cmd] "0" (cmd), [addr] "d" (virt_to_phys(fpl)),
		  [err] "i" (DIAG_FTP_RET_EPERM)
		: "cc");

	चयन (rc) अणु
	हाल DIAG_FTP_RET_OK:
		वापस 0;
	हाल DIAG_FTP_RET_EBUSY:
		वापस -EBUSY;
	हाल DIAG_FTP_RET_EPERM:
		वापस -EPERM;
	हाल DIAG_FTP_RET_EIO:
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

/**
 * diag_ftp_cmd() - executes a DIAG X'2C4' FTP command, targeting a HMC
 * @ftp: poपूर्णांकer to FTP command specअगरication
 * @fsize: वापस of file size (or शून्य अगर undesirable)
 *
 * Attention: Notice that this function is not reentrant - so the caller
 * must ensure locking.
 *
 * Return: number of bytes पढ़ो/written or a (negative) error code
 */
sमाप_प्रकार diag_ftp_cmd(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp, माप_प्रकार *fsize)
अणु
	काष्ठा diag_ftp_ldfpl *ldfpl;
	sमाप_प्रकार len;
#अगर_घोषित DEBUG
	अचिन्हित दीर्घ start_jअगरfies;

	pr_debug("starting DIAG X'2C4' on '%s', requesting %zd bytes\n",
		 ftp->fname, ftp->len);
	start_jअगरfies = jअगरfies;
#पूर्ण_अगर
	init_completion(&diag_ftp_rx_complete);

	ldfpl = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!ldfpl) अणु
		len = -ENOMEM;
		जाओ out;
	पूर्ण

	len = strlcpy(ldfpl->fident, ftp->fname, माप(ldfpl->fident));
	अगर (len >= HMCDRV_FTP_FIDENT_MAX) अणु
		len = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	ldfpl->transferred = 0;
	ldfpl->fsize = 0;
	ldfpl->offset = ftp->ofs;
	ldfpl->buflen = ftp->len;
	ldfpl->bufaddr = virt_to_phys(ftp->buf);

	len = diag_ftp_2c4(ldfpl, ftp->id);
	अगर (len)
		जाओ out_मुक्त;

	/*
	 * There is no way to cancel the running diag X'2C4', the code
	 * needs to रुको unconditionally until the transfer is complete.
	 */
	रुको_क्रम_completion(&diag_ftp_rx_complete);

#अगर_घोषित DEBUG
	pr_debug("completed DIAG X'2C4' after %lu ms\n",
		 (jअगरfies - start_jअगरfies) * 1000 / HZ);
	pr_debug("status of DIAG X'2C4' is %u, with %lld/%lld bytes\n",
		 diag_ftp_subcode, ldfpl->transferred, ldfpl->fsize);
#पूर्ण_अगर

	चयन (diag_ftp_subcode) अणु
	हाल DIAG_FTP_STAT_OK: /* success */
		len = ldfpl->transferred;
		अगर (fsize)
			*fsize = ldfpl->fsize;
		अवरोध;
	हाल DIAG_FTP_STAT_LDNPERM:
		len = -EPERM;
		अवरोध;
	हाल DIAG_FTP_STAT_LDRUNS:
		len = -EBUSY;
		अवरोध;
	हाल DIAG_FTP_STAT_LDFAIL:
		len = -ENOENT; /* no such file or media */
		अवरोध;
	शेष:
		len = -EIO;
		अवरोध;
	पूर्ण

out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ) ldfpl);
out:
	वापस len;
पूर्ण

/**
 * diag_ftp_startup() - startup of FTP services, when running on z/VM
 *
 * Return: 0 on success, अन्यथा an (negative) error code
 */
पूर्णांक diag_ftp_startup(व्योम)
अणु
	पूर्णांक rc;

	rc = रेजिस्टर_बाह्यal_irq(EXT_IRQ_CP_SERVICE, diag_ftp_handler);
	अगर (rc)
		वापस rc;

	irq_subclass_रेजिस्टर(IRQ_SUBCLASS_SERVICE_SIGNAL);
	वापस 0;
पूर्ण

/**
 * diag_ftp_shutकरोwn() - shutकरोwn of FTP services, when running on z/VM
 */
व्योम diag_ftp_shutकरोwn(व्योम)
अणु
	irq_subclass_unरेजिस्टर(IRQ_SUBCLASS_SERVICE_SIGNAL);
	unरेजिस्टर_बाह्यal_irq(EXT_IRQ_CP_SERVICE, diag_ftp_handler);
पूर्ण
