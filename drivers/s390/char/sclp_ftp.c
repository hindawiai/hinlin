<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    SCLP Event Type (ET) 7 - Diagnostic Test FTP Services, useable on LPAR
 *
 *    Copyright IBM Corp. 2013
 *    Author(s): Ralf Hoppe (rhoppe@de.ibm.com)
 *
 */

#घोषणा KMSG_COMPONENT "hmcdrv"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/रुको.h>
#समावेश <linux/माला.स>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/ebcdic.h>

#समावेश "sclp.h"
#समावेश "sclp_diag.h"
#समावेश "sclp_ftp.h"

अटल DECLARE_COMPLETION(sclp_ftp_rx_complete);
अटल u8 sclp_ftp_ldflg;
अटल u64 sclp_ftp_fsize;
अटल u64 sclp_ftp_length;

/**
 * sclp_ftp_txcb() - Diagnostic Test FTP services SCLP command callback
 */
अटल व्योम sclp_ftp_txcb(काष्ठा sclp_req *req, व्योम *data)
अणु
	काष्ठा completion *completion = data;

#अगर_घोषित DEBUG
	pr_debug("SCLP (ET7) TX-IRQ, SCCB @ 0x%p: %*phN\n",
		 req->sccb, 24, req->sccb);
#पूर्ण_अगर
	complete(completion);
पूर्ण

/**
 * sclp_ftp_rxcb() - Diagnostic Test FTP services receiver event callback
 */
अटल व्योम sclp_ftp_rxcb(काष्ठा evbuf_header *evbuf)
अणु
	काष्ठा sclp_diag_evbuf *diag = (काष्ठा sclp_diag_evbuf *) evbuf;

	/*
	 * Check क्रम Diagnostic Test FTP Service
	 */
	अगर (evbuf->type != EVTYP_DIAG_TEST ||
	    diag->route != SCLP_DIAG_FTP_ROUTE ||
	    diag->mdd.ftp.pcx != SCLP_DIAG_FTP_XPCX ||
	    evbuf->length < SCLP_DIAG_FTP_EVBUF_LEN)
		वापस;

#अगर_घोषित DEBUG
	pr_debug("SCLP (ET7) RX-IRQ, Event @ 0x%p: %*phN\n",
		 evbuf, 24, evbuf);
#पूर्ण_अगर

	/*
	 * Because the event buffer is located in a page which is owned
	 * by the SCLP core, all data of पूर्णांकerest must be copied. The
	 * error indication is in 'sclp_ftp_ldflg'
	 */
	sclp_ftp_ldflg = diag->mdd.ftp.ldflg;
	sclp_ftp_fsize = diag->mdd.ftp.fsize;
	sclp_ftp_length = diag->mdd.ftp.length;

	complete(&sclp_ftp_rx_complete);
पूर्ण

/**
 * sclp_ftp_et7() - start a Diagnostic Test FTP Service SCLP request
 * @ftp: poपूर्णांकer to FTP descriptor
 *
 * Return: 0 on success, अन्यथा a (negative) error code
 */
अटल पूर्णांक sclp_ftp_et7(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp)
अणु
	काष्ठा completion completion;
	काष्ठा sclp_diag_sccb *sccb;
	काष्ठा sclp_req *req;
	माप_प्रकार len;
	पूर्णांक rc;

	req = kzalloc(माप(*req), GFP_KERNEL);
	sccb = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!req || !sccb) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	sccb->hdr.length = SCLP_DIAG_FTP_EVBUF_LEN +
		माप(काष्ठा sccb_header);
	sccb->evbuf.hdr.type = EVTYP_DIAG_TEST;
	sccb->evbuf.hdr.length = SCLP_DIAG_FTP_EVBUF_LEN;
	sccb->evbuf.hdr.flags = 0; /* clear processed-buffer */
	sccb->evbuf.route = SCLP_DIAG_FTP_ROUTE;
	sccb->evbuf.mdd.ftp.pcx = SCLP_DIAG_FTP_XPCX;
	sccb->evbuf.mdd.ftp.srcflg = 0;
	sccb->evbuf.mdd.ftp.pgsize = 0;
	sccb->evbuf.mdd.ftp.asce = _ASCE_REAL_SPACE;
	sccb->evbuf.mdd.ftp.ldflg = SCLP_DIAG_FTP_LDFAIL;
	sccb->evbuf.mdd.ftp.fsize = 0;
	sccb->evbuf.mdd.ftp.cmd = ftp->id;
	sccb->evbuf.mdd.ftp.offset = ftp->ofs;
	sccb->evbuf.mdd.ftp.length = ftp->len;
	sccb->evbuf.mdd.ftp.bufaddr = virt_to_phys(ftp->buf);

	len = strlcpy(sccb->evbuf.mdd.ftp.fident, ftp->fname,
		      HMCDRV_FTP_FIDENT_MAX);
	अगर (len >= HMCDRV_FTP_FIDENT_MAX) अणु
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	req->command = SCLP_CMDW_WRITE_EVENT_DATA;
	req->sccb = sccb;
	req->status = SCLP_REQ_FILLED;
	req->callback = sclp_ftp_txcb;
	req->callback_data = &completion;

	init_completion(&completion);

	rc = sclp_add_request(req);
	अगर (rc)
		जाओ out_मुक्त;

	/* Wait क्रम end of ftp sclp command. */
	रुको_क्रम_completion(&completion);

#अगर_घोषित DEBUG
	pr_debug("status of SCLP (ET7) request is 0x%04x (0x%02x)\n",
		 sccb->hdr.response_code, sccb->evbuf.hdr.flags);
#पूर्ण_अगर

	/*
	 * Check अगर sclp accepted the request. The data transfer runs
	 * asynchronously and the completion is indicated with an
	 * sclp ET7 event.
	 */
	अगर (req->status != SCLP_REQ_DONE ||
	    (sccb->evbuf.hdr.flags & 0x80) == 0 || /* processed-buffer */
	    (sccb->hdr.response_code & 0xffU) != 0x20U) अणु
		rc = -EIO;
	पूर्ण

out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ) sccb);
	kमुक्त(req);
	वापस rc;
पूर्ण

/**
 * sclp_ftp_cmd() - executes a HMC related SCLP Diagnose (ET7) FTP command
 * @ftp: poपूर्णांकer to FTP command specअगरication
 * @fsize: वापस of file size (or शून्य अगर undesirable)
 *
 * Attention: Notice that this function is not reentrant - so the caller
 * must ensure locking.
 *
 * Return: number of bytes पढ़ो/written or a (negative) error code
 */
sमाप_प्रकार sclp_ftp_cmd(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp, माप_प्रकार *fsize)
अणु
	sमाप_प्रकार len;
#अगर_घोषित DEBUG
	अचिन्हित दीर्घ start_jअगरfies;

	pr_debug("starting SCLP (ET7), cmd %d for '%s' at %lld with %zd bytes\n",
		 ftp->id, ftp->fname, (दीर्घ दीर्घ) ftp->ofs, ftp->len);
	start_jअगरfies = jअगरfies;
#पूर्ण_अगर

	init_completion(&sclp_ftp_rx_complete);

	/* Start ftp sclp command. */
	len = sclp_ftp_et7(ftp);
	अगर (len)
		जाओ out_unlock;

	/*
	 * There is no way to cancel the sclp ET7 request, the code
	 * needs to रुको unconditionally until the transfer is complete.
	 */
	रुको_क्रम_completion(&sclp_ftp_rx_complete);

#अगर_घोषित DEBUG
	pr_debug("completed SCLP (ET7) request after %lu ms (all)\n",
		 (jअगरfies - start_jअगरfies) * 1000 / HZ);
	pr_debug("return code of SCLP (ET7) FTP Service is 0x%02x, with %lld/%lld bytes\n",
		 sclp_ftp_ldflg, sclp_ftp_length, sclp_ftp_fsize);
#पूर्ण_अगर

	चयन (sclp_ftp_ldflg) अणु
	हाल SCLP_DIAG_FTP_OK:
		len = sclp_ftp_length;
		अगर (fsize)
			*fsize = sclp_ftp_fsize;
		अवरोध;
	हाल SCLP_DIAG_FTP_LDNPERM:
		len = -EPERM;
		अवरोध;
	हाल SCLP_DIAG_FTP_LDRUNS:
		len = -EBUSY;
		अवरोध;
	हाल SCLP_DIAG_FTP_LDFAIL:
		len = -ENOENT;
		अवरोध;
	शेष:
		len = -EIO;
		अवरोध;
	पूर्ण

out_unlock:
	वापस len;
पूर्ण

/*
 * ET7 event listener
 */
अटल काष्ठा sclp_रेजिस्टर sclp_ftp_event = अणु
	.send_mask = EVTYP_DIAG_TEST_MASK,    /* want tx events */
	.receive_mask = EVTYP_DIAG_TEST_MASK, /* want rx events */
	.receiver_fn = sclp_ftp_rxcb,	      /* async callback (rx) */
	.state_change_fn = शून्य,
	.pm_event_fn = शून्य,
पूर्ण;

/**
 * sclp_ftp_startup() - startup of FTP services, when running on LPAR
 */
पूर्णांक sclp_ftp_startup(व्योम)
अणु
#अगर_घोषित DEBUG
	अचिन्हित दीर्घ info;
#पूर्ण_अगर
	पूर्णांक rc;

	rc = sclp_रेजिस्टर(&sclp_ftp_event);
	अगर (rc)
		वापस rc;

#अगर_घोषित DEBUG
	info = get_zeroed_page(GFP_KERNEL);

	अगर (info != 0) अणु
		काष्ठा sysinfo_2_2_2 *info222 = (काष्ठा sysinfo_2_2_2 *)info;

		अगर (!stsi(info222, 2, 2, 2)) अणु /* get SYSIB 2.2.2 */
			info222->name[माप(info222->name) - 1] = '\0';
			EBCASC_500(info222->name, माप(info222->name) - 1);
			pr_debug("SCLP (ET7) FTP Service working on LPAR %u (%s)\n",
				 info222->lpar_number, info222->name);
		पूर्ण

		मुक्त_page(info);
	पूर्ण
#पूर्ण_अगर	/* DEBUG */
	वापस 0;
पूर्ण

/**
 * sclp_ftp_shutकरोwn() - shutकरोwn of FTP services, when running on LPAR
 */
व्योम sclp_ftp_shutकरोwn(व्योम)
अणु
	sclp_unरेजिस्टर(&sclp_ftp_event);
पूर्ण
