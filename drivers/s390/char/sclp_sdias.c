<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SCLP "store data in absolute storage"
 *
 * Copyright IBM Corp. 2003, 2013
 * Author(s): Michael Holzheu
 */

#घोषणा KMSG_COMPONENT "sclp_sdias"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/completion.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/ipl.h>

#समावेश "sclp_sdias.h"
#समावेश "sclp.h"
#समावेश "sclp_rw.h"

#घोषणा TRACE(x...) debug_प्र_लिखो_event(sdias_dbf, 1, x)

#घोषणा SDIAS_RETRIES 300

अटल काष्ठा debug_info *sdias_dbf;

अटल काष्ठा sclp_रेजिस्टर sclp_sdias_रेजिस्टर = अणु
	.send_mask = EVTYP_SDIAS_MASK,
पूर्ण;

अटल काष्ठा sdias_sccb *sclp_sdias_sccb;
अटल काष्ठा sdias_evbuf sdias_evbuf;

अटल DECLARE_COMPLETION(evbuf_accepted);
अटल DECLARE_COMPLETION(evbuf_करोne);
अटल DEFINE_MUTEX(sdias_mutex);

/*
 * Called by SCLP base when पढ़ो event data has been completed (async mode only)
 */
अटल व्योम sclp_sdias_receiver_fn(काष्ठा evbuf_header *evbuf)
अणु
	स_नकल(&sdias_evbuf, evbuf,
	       min_t(अचिन्हित दीर्घ, माप(sdias_evbuf), evbuf->length));
	complete(&evbuf_करोne);
	TRACE("sclp_sdias_receiver_fn done\n");
पूर्ण

/*
 * Called by SCLP base when sdias event has been accepted
 */
अटल व्योम sdias_callback(काष्ठा sclp_req *request, व्योम *data)
अणु
	complete(&evbuf_accepted);
	TRACE("callback done\n");
पूर्ण

अटल पूर्णांक sdias_sclp_send(काष्ठा sclp_req *req)
अणु
	काष्ठा sdias_sccb *sccb = sclp_sdias_sccb;
	पूर्णांक retries;
	पूर्णांक rc;

	क्रम (retries = SDIAS_RETRIES; retries; retries--) अणु
		TRACE("add request\n");
		rc = sclp_add_request(req);
		अगर (rc) अणु
			/* not initiated, रुको some समय and retry */
			set_current_state(TASK_INTERRUPTIBLE);
			TRACE("add request failed: rc = %i\n",rc);
			schedule_समयout(msecs_to_jअगरfies(500));
			जारी;
		पूर्ण
		/* initiated, रुको क्रम completion of service call */
		रुको_क्रम_completion(&evbuf_accepted);
		अगर (req->status == SCLP_REQ_FAILED) अणु
			TRACE("sclp request failed\n");
			जारी;
		पूर्ण
		/* अगर not accepted, retry */
		अगर (!(sccb->evbuf.hdr.flags & 0x80)) अणु
			TRACE("sclp request failed: flags=%x\n",
			      sccb->evbuf.hdr.flags);
			जारी;
		पूर्ण
		/*
		 * क्रम the sync पूर्णांकerface the response is in the initial sccb
		 */
		अगर (!sclp_sdias_रेजिस्टर.receiver_fn) अणु
			स_नकल(&sdias_evbuf, &sccb->evbuf, माप(sdias_evbuf));
			TRACE("sync request done\n");
			वापस 0;
		पूर्ण
		/* otherwise we रुको क्रम completion */
		रुको_क्रम_completion(&evbuf_करोne);
		TRACE("request done\n");
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

/*
 * Get number of blocks (4K) available in the HSA
 */
पूर्णांक sclp_sdias_blk_count(व्योम)
अणु
	काष्ठा sdias_sccb *sccb = sclp_sdias_sccb;
	काष्ठा sclp_req request;
	पूर्णांक rc;

	mutex_lock(&sdias_mutex);

	स_रखो(sccb, 0, माप(*sccb));
	स_रखो(&request, 0, माप(request));

	sccb->hdr.length = माप(*sccb);
	sccb->evbuf.hdr.length = माप(काष्ठा sdias_evbuf);
	sccb->evbuf.hdr.type = EVTYP_SDIAS;
	sccb->evbuf.event_qual = SDIAS_EQ_SIZE;
	sccb->evbuf.data_id = SDIAS_DI_FCP_DUMP;
	sccb->evbuf.event_id = 4712;
	sccb->evbuf.dbs = 1;

	request.sccb = sccb;
	request.command = SCLP_CMDW_WRITE_EVENT_DATA;
	request.status = SCLP_REQ_FILLED;
	request.callback = sdias_callback;

	rc = sdias_sclp_send(&request);
	अगर (rc) अणु
		pr_err("sclp_send failed for get_nr_blocks\n");
		जाओ out;
	पूर्ण
	अगर (sccb->hdr.response_code != 0x0020) अणु
		TRACE("send failed: %x\n", sccb->hdr.response_code);
		rc = -EIO;
		जाओ out;
	पूर्ण

	चयन (sdias_evbuf.event_status) अणु
		हाल 0:
			rc = sdias_evbuf.blk_cnt;
			अवरोध;
		शेष:
			pr_err("SCLP error: %x\n", sdias_evbuf.event_status);
			rc = -EIO;
			जाओ out;
	पूर्ण
	TRACE("%i blocks\n", rc);
out:
	mutex_unlock(&sdias_mutex);
	वापस rc;
पूर्ण

/*
 * Copy from HSA to असलolute storage (not reentrant):
 *
 * @dest     : Address of buffer where data should be copied
 * @start_blk: Start Block (beginning with 1)
 * @nr_blks  : Number of 4K blocks to copy
 *
 * Return Value: 0 : Requested 'number' of blocks of data copied
 *		 <0: ERROR - negative event status
 */
पूर्णांक sclp_sdias_copy(व्योम *dest, पूर्णांक start_blk, पूर्णांक nr_blks)
अणु
	काष्ठा sdias_sccb *sccb = sclp_sdias_sccb;
	काष्ठा sclp_req request;
	पूर्णांक rc;

	mutex_lock(&sdias_mutex);

	स_रखो(sccb, 0, माप(*sccb));
	स_रखो(&request, 0, माप(request));

	sccb->hdr.length = माप(*sccb);
	sccb->evbuf.hdr.length = माप(काष्ठा sdias_evbuf);
	sccb->evbuf.hdr.type = EVTYP_SDIAS;
	sccb->evbuf.hdr.flags = 0;
	sccb->evbuf.event_qual = SDIAS_EQ_STORE_DATA;
	sccb->evbuf.data_id = SDIAS_DI_FCP_DUMP;
	sccb->evbuf.event_id = 4712;
	sccb->evbuf.asa_size = SDIAS_ASA_SIZE_64;
	sccb->evbuf.event_status = 0;
	sccb->evbuf.blk_cnt = nr_blks;
	sccb->evbuf.asa = (अचिन्हित दीर्घ)dest;
	sccb->evbuf.fbn = start_blk;
	sccb->evbuf.lbn = 0;
	sccb->evbuf.dbs = 1;

	request.sccb	 = sccb;
	request.command  = SCLP_CMDW_WRITE_EVENT_DATA;
	request.status	 = SCLP_REQ_FILLED;
	request.callback = sdias_callback;

	rc = sdias_sclp_send(&request);
	अगर (rc) अणु
		pr_err("sclp_send failed: %x\n", rc);
		जाओ out;
	पूर्ण
	अगर (sccb->hdr.response_code != 0x0020) अणु
		TRACE("copy failed: %x\n", sccb->hdr.response_code);
		rc = -EIO;
		जाओ out;
	पूर्ण

	चयन (sdias_evbuf.event_status) अणु
	हाल SDIAS_EVSTATE_ALL_STORED:
		TRACE("all stored\n");
		अवरोध;
	हाल SDIAS_EVSTATE_PART_STORED:
		TRACE("part stored: %i\n", sdias_evbuf.blk_cnt);
		अवरोध;
	हाल SDIAS_EVSTATE_NO_DATA:
		TRACE("no data\n");
		fallthrough;
	शेष:
		pr_err("Error from SCLP while copying hsa. Event status = %x\n",
		       sdias_evbuf.event_status);
		rc = -EIO;
	पूर्ण
out:
	mutex_unlock(&sdias_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक __init sclp_sdias_रेजिस्टर_check(व्योम)
अणु
	पूर्णांक rc;

	rc = sclp_रेजिस्टर(&sclp_sdias_रेजिस्टर);
	अगर (rc)
		वापस rc;
	अगर (sclp_sdias_blk_count() == 0) अणु
		sclp_unरेजिस्टर(&sclp_sdias_रेजिस्टर);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init sclp_sdias_init_sync(व्योम)
अणु
	TRACE("Try synchronous mode\n");
	sclp_sdias_रेजिस्टर.receive_mask = 0;
	sclp_sdias_रेजिस्टर.receiver_fn = शून्य;
	वापस sclp_sdias_रेजिस्टर_check();
पूर्ण

अटल पूर्णांक __init sclp_sdias_init_async(व्योम)
अणु
	TRACE("Try asynchronous mode\n");
	sclp_sdias_रेजिस्टर.receive_mask = EVTYP_SDIAS_MASK;
	sclp_sdias_रेजिस्टर.receiver_fn = sclp_sdias_receiver_fn;
	वापस sclp_sdias_रेजिस्टर_check();
पूर्ण

पूर्णांक __init sclp_sdias_init(व्योम)
अणु
	अगर (!is_ipl_type_dump())
		वापस 0;
	sclp_sdias_sccb = (व्योम *) __get_मुक्त_page(GFP_KERNEL | GFP_DMA);
	BUG_ON(!sclp_sdias_sccb);
	sdias_dbf = debug_रेजिस्टर("dump_sdias", 4, 1, 4 * माप(दीर्घ));
	debug_रेजिस्टर_view(sdias_dbf, &debug_प्र_लिखो_view);
	debug_set_level(sdias_dbf, 6);
	अगर (sclp_sdias_init_sync() == 0)
		जाओ out;
	अगर (sclp_sdias_init_async() == 0)
		जाओ out;
	TRACE("init failed\n");
	मुक्त_page((अचिन्हित दीर्घ) sclp_sdias_sccb);
	वापस -ENODEV;
out:
	TRACE("init done\n");
	वापस 0;
पूर्ण
