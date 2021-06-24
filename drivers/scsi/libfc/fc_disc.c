<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2007 - 2008 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

/*
 * Target Discovery
 *
 * This block discovers all FC-4 remote ports, including FCP initiators. It
 * also handles RSCN events and re-discovery अगर necessary.
 */

/*
 * DISC LOCKING
 *
 * The disc mutex is can be locked when acquiring rport locks, but may not
 * be held when acquiring the lport lock. Refer to fc_lport.c क्रम more
 * details.
 */

#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/rculist.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/fc/fc_gs.h>

#समावेश <scsi/libfc.h>

#समावेश "fc_libfc.h"

#घोषणा FC_DISC_RETRY_LIMIT	3	/* max retries */
#घोषणा FC_DISC_RETRY_DELAY	500UL	/* (msecs) delay */

अटल व्योम fc_disc_gpn_ft_req(काष्ठा fc_disc *);
अटल व्योम fc_disc_gpn_ft_resp(काष्ठा fc_seq *, काष्ठा fc_frame *, व्योम *);
अटल व्योम fc_disc_करोne(काष्ठा fc_disc *, क्रमागत fc_disc_event);
अटल व्योम fc_disc_समयout(काष्ठा work_काष्ठा *);
अटल पूर्णांक fc_disc_single(काष्ठा fc_lport *, काष्ठा fc_disc_port *);
अटल व्योम fc_disc_restart(काष्ठा fc_disc *);

/**
 * fc_disc_stop_rports() - Delete all the remote ports associated with the lport
 * @disc: The discovery job to stop remote ports on
 */
अटल व्योम fc_disc_stop_rports(काष्ठा fc_disc *disc)
अणु
	काष्ठा fc_rport_priv *rdata;

	lockdep_निश्चित_held(&disc->disc_mutex);

	list_क्रम_each_entry(rdata, &disc->rports, peers) अणु
		अगर (kref_get_unless_zero(&rdata->kref)) अणु
			fc_rport_logoff(rdata);
			kref_put(&rdata->kref, fc_rport_destroy);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * fc_disc_recv_rscn_req() - Handle Registered State Change Notअगरication (RSCN)
 * @disc:  The discovery object to which the RSCN applies
 * @fp:	   The RSCN frame
 */
अटल व्योम fc_disc_recv_rscn_req(काष्ठा fc_disc *disc, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_els_rscn *rp;
	काष्ठा fc_els_rscn_page *pp;
	काष्ठा fc_seq_els_data rjt_data;
	अचिन्हित पूर्णांक len;
	पूर्णांक redisc = 0;
	क्रमागत fc_els_rscn_ev_qual ev_qual;
	क्रमागत fc_els_rscn_addr_fmt fmt;
	LIST_HEAD(disc_ports);
	काष्ठा fc_disc_port *dp, *next;

	lockdep_निश्चित_held(&disc->disc_mutex);

	lport = fc_disc_lport(disc);

	FC_DISC_DBG(disc, "Received an RSCN event\n");

	/* make sure the frame contains an RSCN message */
	rp = fc_frame_payload_get(fp, माप(*rp));
	अगर (!rp)
		जाओ reject;
	/* make sure the page length is as expected (4 bytes) */
	अगर (rp->rscn_page_len != माप(*pp))
		जाओ reject;
	/* get the RSCN payload length */
	len = ntohs(rp->rscn_plen);
	अगर (len < माप(*rp))
		जाओ reject;
	/* make sure the frame contains the expected payload */
	rp = fc_frame_payload_get(fp, len);
	अगर (!rp)
		जाओ reject;
	/* payload must be a multiple of the RSCN page size */
	len -= माप(*rp);
	अगर (len % माप(*pp))
		जाओ reject;

	क्रम (pp = (व्योम *)(rp + 1); len > 0; len -= माप(*pp), pp++) अणु
		ev_qual = pp->rscn_page_flags >> ELS_RSCN_EV_QUAL_BIT;
		ev_qual &= ELS_RSCN_EV_QUAL_MASK;
		fmt = pp->rscn_page_flags >> ELS_RSCN_ADDR_FMT_BIT;
		fmt &= ELS_RSCN_ADDR_FMT_MASK;
		/*
		 * अगर we get an address क्रमmat other than port
		 * (area, करोमुख्य, fabric), then करो a full discovery
		 */
		चयन (fmt) अणु
		हाल ELS_ADDR_FMT_PORT:
			FC_DISC_DBG(disc, "Port address format for port "
				    "(%6.6x)\n", ntoh24(pp->rscn_fid));
			dp = kzalloc(माप(*dp), GFP_KERNEL);
			अगर (!dp) अणु
				redisc = 1;
				अवरोध;
			पूर्ण
			dp->lp = lport;
			dp->port_id = ntoh24(pp->rscn_fid);
			list_add_tail(&dp->peers, &disc_ports);
			अवरोध;
		हाल ELS_ADDR_FMT_AREA:
		हाल ELS_ADDR_FMT_DOM:
		हाल ELS_ADDR_FMT_FAB:
		शेष:
			FC_DISC_DBG(disc, "Address format is (%d)\n", fmt);
			redisc = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	fc_seq_els_rsp_send(fp, ELS_LS_ACC, शून्य);

	/*
	 * If not करोing a complete rediscovery, करो GPN_ID on
	 * the inभागidual ports mentioned in the list.
	 * If any of these get an error, करो a full rediscovery.
	 * In any हाल, go through the list and मुक्त the entries.
	 */
	list_क्रम_each_entry_safe(dp, next, &disc_ports, peers) अणु
		list_del(&dp->peers);
		अगर (!redisc)
			redisc = fc_disc_single(lport, dp);
		kमुक्त(dp);
	पूर्ण
	अगर (redisc) अणु
		FC_DISC_DBG(disc, "RSCN received: rediscovering\n");
		fc_disc_restart(disc);
	पूर्ण अन्यथा अणु
		FC_DISC_DBG(disc, "RSCN received: not rediscovering. "
			    "redisc %d state %d in_prog %d\n",
			    redisc, lport->state, disc->pending);
	पूर्ण
	fc_frame_मुक्त(fp);
	वापस;
reject:
	FC_DISC_DBG(disc, "Received a bad RSCN frame\n");
	rjt_data.reason = ELS_RJT_LOGIC;
	rjt_data.explan = ELS_EXPL_NONE;
	fc_seq_els_rsp_send(fp, ELS_LS_RJT, &rjt_data);
	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_disc_recv_req() - Handle incoming requests
 * @lport: The local port receiving the request
 * @fp:	   The request frame
 *
 * Locking Note: This function is called from the EM and will lock
 *		 the disc_mutex beक्रमe calling the handler क्रम the
 *		 request.
 */
अटल व्योम fc_disc_recv_req(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	u8 op;
	काष्ठा fc_disc *disc = &lport->disc;

	op = fc_frame_payload_op(fp);
	चयन (op) अणु
	हाल ELS_RSCN:
		mutex_lock(&disc->disc_mutex);
		fc_disc_recv_rscn_req(disc, fp);
		mutex_unlock(&disc->disc_mutex);
		अवरोध;
	शेष:
		FC_DISC_DBG(disc, "Received an unsupported request, "
			    "the opcode is (%x)\n", op);
		fc_frame_मुक्त(fp);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * fc_disc_restart() - Restart discovery
 * @disc: The discovery object to be restarted
 */
अटल व्योम fc_disc_restart(काष्ठा fc_disc *disc)
अणु
	lockdep_निश्चित_held(&disc->disc_mutex);

	अगर (!disc->disc_callback)
		वापस;

	FC_DISC_DBG(disc, "Restarting discovery\n");

	disc->requested = 1;
	अगर (disc->pending)
		वापस;

	/*
	 * Advance disc_id.  This is an arbitrary non-zero number that will
	 * match the value in the fc_rport_priv after discovery क्रम all
	 * freshly-discovered remote ports.  Aव्योम wrapping to zero.
	 */
	disc->disc_id = (disc->disc_id + 2) | 1;
	disc->retry_count = 0;
	fc_disc_gpn_ft_req(disc);
पूर्ण

/**
 * fc_disc_start() - Start discovery on a local port
 * @lport:	   The local port to have discovery started on
 * @disc_callback: Callback function to be called when discovery is complete
 */
अटल व्योम fc_disc_start(व्योम (*disc_callback)(काष्ठा fc_lport *,
						क्रमागत fc_disc_event),
			  काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_disc *disc = &lport->disc;

	/*
	 * At this poपूर्णांक we may have a new disc job or an existing
	 * one. Either way, let's lock when we make changes to it
	 * and send the GPN_FT request.
	 */
	mutex_lock(&disc->disc_mutex);
	disc->disc_callback = disc_callback;
	fc_disc_restart(disc);
	mutex_unlock(&disc->disc_mutex);
पूर्ण

/**
 * fc_disc_करोne() - Discovery has been completed
 * @disc:  The discovery context
 * @event: The discovery completion status
 */
अटल व्योम fc_disc_करोne(काष्ठा fc_disc *disc, क्रमागत fc_disc_event event)
अणु
	काष्ठा fc_lport *lport = fc_disc_lport(disc);
	काष्ठा fc_rport_priv *rdata;

	lockdep_निश्चित_held(&disc->disc_mutex);
	FC_DISC_DBG(disc, "Discovery complete\n");

	disc->pending = 0;
	अगर (disc->requested) अणु
		fc_disc_restart(disc);
		वापस;
	पूर्ण

	/*
	 * Go through all remote ports.	 If they were found in the latest
	 * discovery, reverअगरy or log them in.	Otherwise, log them out.
	 * Skip ports which were never discovered.  These are the dNS port
	 * and ports which were created by PLOGI.
	 *
	 * We करोn't need to use the _rcu variant here as the rport list
	 * is रक्षित by the disc mutex which is alपढ़ोy held on entry.
	 */
	list_क्रम_each_entry(rdata, &disc->rports, peers) अणु
		अगर (!kref_get_unless_zero(&rdata->kref))
			जारी;
		अगर (rdata->disc_id) अणु
			अगर (rdata->disc_id == disc->disc_id)
				fc_rport_login(rdata);
			अन्यथा
				fc_rport_logoff(rdata);
		पूर्ण
		kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण
	mutex_unlock(&disc->disc_mutex);
	disc->disc_callback(lport, event);
	mutex_lock(&disc->disc_mutex);
पूर्ण

/**
 * fc_disc_error() - Handle error on dNS request
 * @disc: The discovery context
 * @fp:	  The error code encoded as a frame poपूर्णांकer
 */
अटल व्योम fc_disc_error(काष्ठा fc_disc *disc, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_lport *lport = fc_disc_lport(disc);
	अचिन्हित दीर्घ delay = 0;

	FC_DISC_DBG(disc, "Error %d, retries %d/%d\n",
		    PTR_ERR_OR_ZERO(fp), disc->retry_count,
		    FC_DISC_RETRY_LIMIT);

	अगर (!fp || PTR_ERR(fp) == -FC_EX_TIMEOUT) अणु
		/*
		 * Memory allocation failure, or the exchange समयd out,
		 * retry after delay.
		 */
		अगर (disc->retry_count < FC_DISC_RETRY_LIMIT) अणु
			/* go ahead and retry */
			अगर (!fp)
				delay = msecs_to_jअगरfies(FC_DISC_RETRY_DELAY);
			अन्यथा अणु
				delay = msecs_to_jअगरfies(lport->e_d_tov);

				/* समयout faster first समय */
				अगर (!disc->retry_count)
					delay /= 4;
			पूर्ण
			disc->retry_count++;
			schedule_delayed_work(&disc->disc_work, delay);
		पूर्ण अन्यथा
			fc_disc_करोne(disc, DISC_EV_FAILED);
	पूर्ण अन्यथा अगर (PTR_ERR(fp) == -FC_EX_CLOSED) अणु
		/*
		 * अगर discovery fails due to lport reset, clear
		 * pending flag so that subsequent discovery can
		 * जारी
		 */
		disc->pending = 0;
	पूर्ण
पूर्ण

/**
 * fc_disc_gpn_ft_req() - Send Get Port Names by FC-4 type (GPN_FT) request
 * @disc: The discovery context
 */
अटल व्योम fc_disc_gpn_ft_req(काष्ठा fc_disc *disc)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_lport *lport = fc_disc_lport(disc);

	lockdep_निश्चित_held(&disc->disc_mutex);

	WARN_ON(!fc_lport_test_पढ़ोy(lport));

	disc->pending = 1;
	disc->requested = 0;

	disc->buf_len = 0;
	disc->seq_count = 0;
	fp = fc_frame_alloc(lport,
			    माप(काष्ठा fc_ct_hdr) +
			    माप(काष्ठा fc_ns_gid_ft));
	अगर (!fp)
		जाओ err;

	अगर (lport->tt.elsct_send(lport, 0, fp,
				 FC_NS_GPN_FT,
				 fc_disc_gpn_ft_resp,
				 disc, 3 * lport->r_a_tov))
		वापस;
err:
	fc_disc_error(disc, शून्य);
पूर्ण

/**
 * fc_disc_gpn_ft_parse() - Parse the body of the dNS GPN_FT response.
 * @disc:  The discovery context
 * @buf:   The GPN_FT response buffer
 * @len:   The size of response buffer
 *
 * Goes through the list of IDs and names resulting from a request.
 */
अटल पूर्णांक fc_disc_gpn_ft_parse(काष्ठा fc_disc *disc, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_gpn_ft_resp *np;
	अक्षर *bp;
	माप_प्रकार plen;
	माप_प्रकार tlen;
	पूर्णांक error = 0;
	काष्ठा fc_rport_identअगरiers ids;
	काष्ठा fc_rport_priv *rdata;

	lport = fc_disc_lport(disc);
	disc->seq_count++;

	/*
	 * Handle partial name record left over from previous call.
	 */
	bp = buf;
	plen = len;
	np = (काष्ठा fc_gpn_ft_resp *)bp;
	tlen = disc->buf_len;
	disc->buf_len = 0;
	अगर (tlen) अणु
		WARN_ON(tlen >= माप(*np));
		plen = माप(*np) - tlen;
		WARN_ON(plen <= 0);
		WARN_ON(plen >= माप(*np));
		अगर (plen > len)
			plen = len;
		np = &disc->partial_buf;
		स_नकल((अक्षर *)np + tlen, bp, plen);

		/*
		 * Set bp so that the loop below will advance it to the
		 * first valid full name element.
		 */
		bp -= tlen;
		len += tlen;
		plen += tlen;
		disc->buf_len = (अचिन्हित अक्षर) plen;
		अगर (plen == माप(*np))
			disc->buf_len = 0;
	पूर्ण

	/*
	 * Handle full name records, including the one filled from above.
	 * Normally, np == bp and plen == len, but from the partial हाल above,
	 * bp, len describe the overall buffer, and np, plen describe the
	 * partial buffer, which अगर would usually be full now.
	 * After the first समय through the loop, things वापस to "normal".
	 */
	जबतक (plen >= माप(*np)) अणु
		ids.port_id = ntoh24(np->fp_fid);
		ids.port_name = ntohll(np->fp_wwpn);

		अगर (ids.port_id != lport->port_id &&
		    ids.port_name != lport->wwpn) अणु
			rdata = fc_rport_create(lport, ids.port_id);
			अगर (rdata) अणु
				rdata->ids.port_name = ids.port_name;
				rdata->disc_id = disc->disc_id;
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_WARNING "libfc: Failed to allocate "
				       "memory for the newly discovered port "
				       "(%6.6x)\n", ids.port_id);
				error = -ENOMEM;
			पूर्ण
		पूर्ण

		अगर (np->fp_flags & FC_NS_FID_LAST) अणु
			fc_disc_करोne(disc, DISC_EV_SUCCESS);
			len = 0;
			अवरोध;
		पूर्ण
		len -= माप(*np);
		bp += माप(*np);
		np = (काष्ठा fc_gpn_ft_resp *)bp;
		plen = len;
	पूर्ण

	/*
	 * Save any partial record at the end of the buffer क्रम next समय.
	 */
	अगर (error == 0 && len > 0 && len < माप(*np)) अणु
		अगर (np != &disc->partial_buf) अणु
			FC_DISC_DBG(disc, "Partial buffer remains "
				    "for discovery\n");
			स_नकल(&disc->partial_buf, np, len);
		पूर्ण
		disc->buf_len = (अचिन्हित अक्षर) len;
	पूर्ण
	वापस error;
पूर्ण

/**
 * fc_disc_समयout() - Handler क्रम discovery समयouts
 * @work: Structure holding discovery context that needs to retry discovery
 */
अटल व्योम fc_disc_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_disc *disc = container_of(work,
					    काष्ठा fc_disc,
					    disc_work.work);
	mutex_lock(&disc->disc_mutex);
	fc_disc_gpn_ft_req(disc);
	mutex_unlock(&disc->disc_mutex);
पूर्ण

/**
 * fc_disc_gpn_ft_resp() - Handle a response frame from Get Port Names (GPN_FT)
 * @sp:	    The sequence that the GPN_FT response was received on
 * @fp:	    The GPN_FT response frame
 * @disc_arg: The discovery context
 *
 * Locking Note: This function is called without disc mutex held, and
 *		 should करो all its processing with the mutex held
 */
अटल व्योम fc_disc_gpn_ft_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
				व्योम *disc_arg)
अणु
	काष्ठा fc_disc *disc = disc_arg;
	काष्ठा fc_ct_hdr *cp;
	काष्ठा fc_frame_header *fh;
	क्रमागत fc_disc_event event = DISC_EV_NONE;
	अचिन्हित पूर्णांक seq_cnt;
	अचिन्हित पूर्णांक len;
	पूर्णांक error = 0;

	mutex_lock(&disc->disc_mutex);
	FC_DISC_DBG(disc, "Received a GPN_FT response\n");

	अगर (IS_ERR(fp)) अणु
		fc_disc_error(disc, fp);
		mutex_unlock(&disc->disc_mutex);
		वापस;
	पूर्ण

	WARN_ON(!fc_frame_is_linear(fp));	/* buffer must be contiguous */
	fh = fc_frame_header_get(fp);
	len = fr_len(fp) - माप(*fh);
	seq_cnt = ntohs(fh->fh_seq_cnt);
	अगर (fr_sof(fp) == FC_SOF_I3 && seq_cnt == 0 && disc->seq_count == 0) अणु
		cp = fc_frame_payload_get(fp, माप(*cp));
		अगर (!cp) अणु
			FC_DISC_DBG(disc, "GPN_FT response too short, len %d\n",
				    fr_len(fp));
			event = DISC_EV_FAILED;
		पूर्ण अन्यथा अगर (ntohs(cp->ct_cmd) == FC_FS_ACC) अणु

			/* Accepted, parse the response. */
			len -= माप(*cp);
			error = fc_disc_gpn_ft_parse(disc, cp + 1, len);
		पूर्ण अन्यथा अगर (ntohs(cp->ct_cmd) == FC_FS_RJT) अणु
			FC_DISC_DBG(disc, "GPN_FT rejected reason %x exp %x "
				    "(check zoning)\n", cp->ct_reason,
				    cp->ct_explan);
			event = DISC_EV_FAILED;
			अगर (cp->ct_reason == FC_FS_RJT_UNABL &&
			    cp->ct_explan == FC_FS_EXP_FTNR)
				event = DISC_EV_SUCCESS;
		पूर्ण अन्यथा अणु
			FC_DISC_DBG(disc, "GPN_FT unexpected response code "
				    "%x\n", ntohs(cp->ct_cmd));
			event = DISC_EV_FAILED;
		पूर्ण
	पूर्ण अन्यथा अगर (fr_sof(fp) == FC_SOF_N3 && seq_cnt == disc->seq_count) अणु
		error = fc_disc_gpn_ft_parse(disc, fh + 1, len);
	पूर्ण अन्यथा अणु
		FC_DISC_DBG(disc, "GPN_FT unexpected frame - out of sequence? "
			    "seq_cnt %x expected %x sof %x eof %x\n",
			    seq_cnt, disc->seq_count, fr_sof(fp), fr_eof(fp));
		event = DISC_EV_FAILED;
	पूर्ण
	अगर (error)
		fc_disc_error(disc, ERR_PTR(error));
	अन्यथा अगर (event != DISC_EV_NONE)
		fc_disc_करोne(disc, event);
	fc_frame_मुक्त(fp);
	mutex_unlock(&disc->disc_mutex);
पूर्ण

/**
 * fc_disc_gpn_id_resp() - Handle a response frame from Get Port Names (GPN_ID)
 * @sp:	       The sequence the GPN_ID is on
 * @fp:	       The response frame
 * @rdata_arg: The remote port that sent the GPN_ID response
 *
 * Locking Note: This function is called without disc mutex held.
 */
अटल व्योम fc_disc_gpn_id_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
				व्योम *rdata_arg)
अणु
	काष्ठा fc_rport_priv *rdata = rdata_arg;
	काष्ठा fc_rport_priv *new_rdata;
	काष्ठा fc_lport *lport;
	काष्ठा fc_disc *disc;
	काष्ठा fc_ct_hdr *cp;
	काष्ठा fc_ns_gid_pn *pn;
	u64 port_name;

	lport = rdata->local_port;
	disc = &lport->disc;

	अगर (PTR_ERR(fp) == -FC_EX_CLOSED)
		जाओ out;
	अगर (IS_ERR(fp)) अणु
		mutex_lock(&disc->disc_mutex);
		fc_disc_restart(disc);
		mutex_unlock(&disc->disc_mutex);
		जाओ out;
	पूर्ण

	cp = fc_frame_payload_get(fp, माप(*cp));
	अगर (!cp)
		जाओ redisc;
	अगर (ntohs(cp->ct_cmd) == FC_FS_ACC) अणु
		अगर (fr_len(fp) < माप(काष्ठा fc_frame_header) +
		    माप(*cp) + माप(*pn))
			जाओ redisc;
		pn = (काष्ठा fc_ns_gid_pn *)(cp + 1);
		port_name = get_unaligned_be64(&pn->fn_wwpn);
		mutex_lock(&rdata->rp_mutex);
		अगर (rdata->ids.port_name == -1)
			rdata->ids.port_name = port_name;
		अन्यथा अगर (rdata->ids.port_name != port_name) अणु
			FC_DISC_DBG(disc, "GPN_ID accepted.  WWPN changed. "
				    "Port-id %6.6x wwpn %16.16llx\n",
				    rdata->ids.port_id, port_name);
			mutex_unlock(&rdata->rp_mutex);
			fc_rport_logoff(rdata);
			mutex_lock(&lport->disc.disc_mutex);
			new_rdata = fc_rport_create(lport, rdata->ids.port_id);
			mutex_unlock(&lport->disc.disc_mutex);
			अगर (new_rdata) अणु
				new_rdata->disc_id = disc->disc_id;
				fc_rport_login(new_rdata);
			पूर्ण
			जाओ मुक्त_fp;
		पूर्ण
		rdata->disc_id = disc->disc_id;
		mutex_unlock(&rdata->rp_mutex);
		fc_rport_login(rdata);
	पूर्ण अन्यथा अगर (ntohs(cp->ct_cmd) == FC_FS_RJT) अणु
		FC_DISC_DBG(disc, "GPN_ID rejected reason %x exp %x\n",
			    cp->ct_reason, cp->ct_explan);
		fc_rport_logoff(rdata);
	पूर्ण अन्यथा अणु
		FC_DISC_DBG(disc, "GPN_ID unexpected response code %x\n",
			    ntohs(cp->ct_cmd));
redisc:
		mutex_lock(&disc->disc_mutex);
		fc_disc_restart(disc);
		mutex_unlock(&disc->disc_mutex);
	पूर्ण
मुक्त_fp:
	fc_frame_मुक्त(fp);
out:
	kref_put(&rdata->kref, fc_rport_destroy);
पूर्ण

/**
 * fc_disc_gpn_id_req() - Send Get Port Names by ID (GPN_ID) request
 * @lport: The local port to initiate discovery on
 * @rdata: remote port निजी data
 *
 * On failure, an error code is वापसed.
 */
अटल पूर्णांक fc_disc_gpn_id_req(काष्ठा fc_lport *lport,
			      काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा fc_frame *fp;

	lockdep_निश्चित_held(&lport->disc.disc_mutex);
	fp = fc_frame_alloc(lport, माप(काष्ठा fc_ct_hdr) +
			    माप(काष्ठा fc_ns_fid));
	अगर (!fp)
		वापस -ENOMEM;
	अगर (!lport->tt.elsct_send(lport, rdata->ids.port_id, fp, FC_NS_GPN_ID,
				  fc_disc_gpn_id_resp, rdata,
				  3 * lport->r_a_tov))
		वापस -ENOMEM;
	kref_get(&rdata->kref);
	वापस 0;
पूर्ण

/**
 * fc_disc_single() - Discover the directory inक्रमmation क्रम a single target
 * @lport: The local port the remote port is associated with
 * @dp:	   The port to rediscover
 */
अटल पूर्णांक fc_disc_single(काष्ठा fc_lport *lport, काष्ठा fc_disc_port *dp)
अणु
	काष्ठा fc_rport_priv *rdata;

	lockdep_निश्चित_held(&lport->disc.disc_mutex);

	rdata = fc_rport_create(lport, dp->port_id);
	अगर (!rdata)
		वापस -ENOMEM;
	rdata->disc_id = 0;
	वापस fc_disc_gpn_id_req(lport, rdata);
पूर्ण

/**
 * fc_disc_stop() - Stop discovery क्रम a given lport
 * @lport: The local port that discovery should stop on
 */
अटल व्योम fc_disc_stop(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_disc *disc = &lport->disc;

	अगर (disc->pending)
		cancel_delayed_work_sync(&disc->disc_work);
	mutex_lock(&disc->disc_mutex);
	fc_disc_stop_rports(disc);
	mutex_unlock(&disc->disc_mutex);
पूर्ण

/**
 * fc_disc_stop_final() - Stop discovery क्रम a given lport
 * @lport: The lport that discovery should stop on
 *
 * This function will block until discovery has been
 * completely stopped and all rports have been deleted.
 */
अटल व्योम fc_disc_stop_final(काष्ठा fc_lport *lport)
अणु
	fc_disc_stop(lport);
	fc_rport_flush_queue();
पूर्ण

/**
 * fc_disc_config() - Configure the discovery layer क्रम a local port
 * @lport: The local port that needs the discovery layer to be configured
 * @priv: Private data काष्ठाre क्रम users of the discovery layer
 */
व्योम fc_disc_config(काष्ठा fc_lport *lport, व्योम *priv)
अणु
	काष्ठा fc_disc *disc;

	अगर (!lport->tt.disc_start)
		lport->tt.disc_start = fc_disc_start;

	अगर (!lport->tt.disc_stop)
		lport->tt.disc_stop = fc_disc_stop;

	अगर (!lport->tt.disc_stop_final)
		lport->tt.disc_stop_final = fc_disc_stop_final;

	अगर (!lport->tt.disc_recv_req)
		lport->tt.disc_recv_req = fc_disc_recv_req;

	disc = &lport->disc;

	disc->priv = priv;
पूर्ण
EXPORT_SYMBOL(fc_disc_config);

/**
 * fc_disc_init() - Initialize the discovery layer क्रम a local port
 * @lport: The local port that needs the discovery layer to be initialized
 */
व्योम fc_disc_init(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_disc *disc = &lport->disc;

	INIT_DELAYED_WORK(&disc->disc_work, fc_disc_समयout);
	mutex_init(&disc->disc_mutex);
	INIT_LIST_HEAD(&disc->rports);
पूर्ण
EXPORT_SYMBOL(fc_disc_init);
