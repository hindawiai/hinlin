<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2008-2013 Solarflare Communications Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/atomic.h>
#समावेश "net_driver.h"
#समावेश "nic.h"
#समावेश "io.h"
#समावेश "farch_regs.h"
#समावेश "mcdi_pcol.h"

/**************************************************************************
 *
 * Management-Controller-to-Driver Interface
 *
 **************************************************************************
 */

#घोषणा MCDI_RPC_TIMEOUT       (10 * HZ)

/* A reboot/निश्चितion causes the MCDI status word to be set after the
 * command word is set or a REBOOT event is sent. If we notice a reboot
 * via these mechanisms then रुको 250ms क्रम the status word to be set.
 */
#घोषणा MCDI_STATUS_DELAY_US		100
#घोषणा MCDI_STATUS_DELAY_COUNT		2500
#घोषणा MCDI_STATUS_SLEEP_MS						\
	(MCDI_STATUS_DELAY_US * MCDI_STATUS_DELAY_COUNT / 1000)

#घोषणा SEQ_MASK							\
	EFX_MASK32(EFX_WIDTH(MCDI_HEADER_SEQ))

काष्ठा efx_mcdi_async_param अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक cmd;
	माप_प्रकार inlen;
	माप_प्रकार outlen;
	bool quiet;
	efx_mcdi_async_completer *complete;
	अचिन्हित दीर्घ cookie;
	/* followed by request/response buffer */
पूर्ण;

अटल व्योम efx_mcdi_समयout_async(काष्ठा समयr_list *t);
अटल पूर्णांक efx_mcdi_drv_attach(काष्ठा efx_nic *efx, bool driver_operating,
			       bool *was_attached_out);
अटल bool efx_mcdi_poll_once(काष्ठा efx_nic *efx);
अटल व्योम efx_mcdi_abanकरोn(काष्ठा efx_nic *efx);

#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
अटल bool mcdi_logging_शेष;
module_param(mcdi_logging_शेष, bool, 0644);
MODULE_PARM_DESC(mcdi_logging_शेष,
		 "Enable MCDI logging on newly-probed functions");
#पूर्ण_अगर

पूर्णांक efx_mcdi_init(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi;
	bool alपढ़ोy_attached;
	पूर्णांक rc = -ENOMEM;

	efx->mcdi = kzalloc(माप(*efx->mcdi), GFP_KERNEL);
	अगर (!efx->mcdi)
		जाओ fail;

	mcdi = efx_mcdi(efx);
	mcdi->efx = efx;
#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
	/* consuming code assumes buffer is page-sized */
	mcdi->logging_buffer = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!mcdi->logging_buffer)
		जाओ fail1;
	mcdi->logging_enabled = mcdi_logging_शेष;
#पूर्ण_अगर
	init_रुकोqueue_head(&mcdi->wq);
	init_रुकोqueue_head(&mcdi->proxy_rx_wq);
	spin_lock_init(&mcdi->अगरace_lock);
	mcdi->state = MCDI_STATE_QUIESCENT;
	mcdi->mode = MCDI_MODE_POLL;
	spin_lock_init(&mcdi->async_lock);
	INIT_LIST_HEAD(&mcdi->async_list);
	समयr_setup(&mcdi->async_समयr, efx_mcdi_समयout_async, 0);

	(व्योम) efx_mcdi_poll_reboot(efx);
	mcdi->new_epoch = true;

	/* Recover from a failed निश्चितion beक्रमe probing */
	rc = efx_mcdi_handle_निश्चितion(efx);
	अगर (rc)
		जाओ fail2;

	/* Let the MC (and BMC, अगर this is a LOM) know that the driver
	 * is loaded. We should करो this beक्रमe we reset the NIC.
	 */
	rc = efx_mcdi_drv_attach(efx, true, &alपढ़ोy_attached);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Unable to register driver with MCPU\n");
		जाओ fail2;
	पूर्ण
	अगर (alपढ़ोy_attached)
		/* Not a fatal error */
		netअगर_err(efx, probe, efx->net_dev,
			  "Host already registered with MCPU\n");

	अगर (efx->mcdi->fn_flags &
	    (1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_PRIMARY))
		efx->primary = efx;

	वापस 0;
fail2:
#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
	मुक्त_page((अचिन्हित दीर्घ)mcdi->logging_buffer);
fail1:
#पूर्ण_अगर
	kमुक्त(efx->mcdi);
	efx->mcdi = शून्य;
fail:
	वापस rc;
पूर्ण

व्योम efx_mcdi_detach(काष्ठा efx_nic *efx)
अणु
	अगर (!efx->mcdi)
		वापस;

	BUG_ON(efx->mcdi->अगरace.state != MCDI_STATE_QUIESCENT);

	/* Relinquish the device (back to the BMC, अगर this is a LOM) */
	efx_mcdi_drv_attach(efx, false, शून्य);
पूर्ण

व्योम efx_mcdi_fini(काष्ठा efx_nic *efx)
अणु
	अगर (!efx->mcdi)
		वापस;

#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
	मुक्त_page((अचिन्हित दीर्घ)efx->mcdi->अगरace.logging_buffer);
#पूर्ण_अगर

	kमुक्त(efx->mcdi);
पूर्ण

अटल व्योम efx_mcdi_send_request(काष्ठा efx_nic *efx, अचिन्हित cmd,
				  स्थिर efx_dword_t *inbuf, माप_प्रकार inlen)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);
#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
	अक्षर *buf = mcdi->logging_buffer; /* page-sized */
#पूर्ण_अगर
	efx_dword_t hdr[2];
	माप_प्रकार hdr_len;
	u32 xflags, seqno;

	BUG_ON(mcdi->state == MCDI_STATE_QUIESCENT);

	/* Serialise with efx_mcdi_ev_cpl() and efx_mcdi_ev_death() */
	spin_lock_bh(&mcdi->अगरace_lock);
	++mcdi->seqno;
	spin_unlock_bh(&mcdi->अगरace_lock);

	seqno = mcdi->seqno & SEQ_MASK;
	xflags = 0;
	अगर (mcdi->mode == MCDI_MODE_EVENTS)
		xflags |= MCDI_HEADER_XFLAGS_EVREQ;

	अगर (efx->type->mcdi_max_ver == 1) अणु
		/* MCDI v1 */
		EFX_POPULATE_DWORD_7(hdr[0],
				     MCDI_HEADER_RESPONSE, 0,
				     MCDI_HEADER_RESYNC, 1,
				     MCDI_HEADER_CODE, cmd,
				     MCDI_HEADER_DATALEN, inlen,
				     MCDI_HEADER_SEQ, seqno,
				     MCDI_HEADER_XFLAGS, xflags,
				     MCDI_HEADER_NOT_EPOCH, !mcdi->new_epoch);
		hdr_len = 4;
	पूर्ण अन्यथा अणु
		/* MCDI v2 */
		BUG_ON(inlen > MCDI_CTL_SDU_LEN_MAX_V2);
		EFX_POPULATE_DWORD_7(hdr[0],
				     MCDI_HEADER_RESPONSE, 0,
				     MCDI_HEADER_RESYNC, 1,
				     MCDI_HEADER_CODE, MC_CMD_V2_EXTN,
				     MCDI_HEADER_DATALEN, 0,
				     MCDI_HEADER_SEQ, seqno,
				     MCDI_HEADER_XFLAGS, xflags,
				     MCDI_HEADER_NOT_EPOCH, !mcdi->new_epoch);
		EFX_POPULATE_DWORD_2(hdr[1],
				     MC_CMD_V2_EXTN_IN_EXTENDED_CMD, cmd,
				     MC_CMD_V2_EXTN_IN_ACTUAL_LEN, inlen);
		hdr_len = 8;
	पूर्ण

#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
	अगर (mcdi->logging_enabled && !WARN_ON_ONCE(!buf)) अणु
		पूर्णांक bytes = 0;
		पूर्णांक i;
		/* Lengths should always be a whole number of dwords, so scream
		 * अगर they're not.
		 */
		WARN_ON_ONCE(hdr_len % 4);
		WARN_ON_ONCE(inlen % 4);

		/* We own the logging buffer, as only one MCDI can be in
		 * progress on a NIC at any one समय.  So no need क्रम locking.
		 */
		क्रम (i = 0; i < hdr_len / 4 && bytes < PAGE_SIZE; i++)
			bytes += scnम_लिखो(buf + bytes, PAGE_SIZE - bytes,
					   " %08x",
					   le32_to_cpu(hdr[i].u32[0]));

		क्रम (i = 0; i < inlen / 4 && bytes < PAGE_SIZE; i++)
			bytes += scnम_लिखो(buf + bytes, PAGE_SIZE - bytes,
					   " %08x",
					   le32_to_cpu(inbuf[i].u32[0]));

		netअगर_info(efx, hw, efx->net_dev, "MCDI RPC REQ:%s\n", buf);
	पूर्ण
#पूर्ण_अगर

	efx->type->mcdi_request(efx, hdr, hdr_len, inbuf, inlen);

	mcdi->new_epoch = false;
पूर्ण

अटल पूर्णांक efx_mcdi_त्रुटि_सं(अचिन्हित पूर्णांक mcdi_err)
अणु
	चयन (mcdi_err) अणु
	हाल 0:
		वापस 0;
#घोषणा TRANSLATE_ERROR(name)					\
	हाल MC_CMD_ERR_ ## name:				\
		वापस -name;
	TRANSLATE_ERROR(EPERM);
	TRANSLATE_ERROR(ENOENT);
	TRANSLATE_ERROR(EINTR);
	TRANSLATE_ERROR(EAGAIN);
	TRANSLATE_ERROR(EACCES);
	TRANSLATE_ERROR(EBUSY);
	TRANSLATE_ERROR(EINVAL);
	TRANSLATE_ERROR(EDEADLK);
	TRANSLATE_ERROR(ENOSYS);
	TRANSLATE_ERROR(ETIME);
	TRANSLATE_ERROR(EALREADY);
	TRANSLATE_ERROR(ENOSPC);
#अघोषित TRANSLATE_ERROR
	हाल MC_CMD_ERR_ENOTSUP:
		वापस -EOPNOTSUPP;
	हाल MC_CMD_ERR_ALLOC_FAIL:
		वापस -ENOBUFS;
	हाल MC_CMD_ERR_MAC_EXIST:
		वापस -EADDRINUSE;
	शेष:
		वापस -EPROTO;
	पूर्ण
पूर्ण

अटल व्योम efx_mcdi_पढ़ो_response_header(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);
	अचिन्हित पूर्णांक respseq, respcmd, error;
#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
	अक्षर *buf = mcdi->logging_buffer; /* page-sized */
#पूर्ण_अगर
	efx_dword_t hdr;

	efx->type->mcdi_पढ़ो_response(efx, &hdr, 0, 4);
	respseq = EFX_DWORD_FIELD(hdr, MCDI_HEADER_SEQ);
	respcmd = EFX_DWORD_FIELD(hdr, MCDI_HEADER_CODE);
	error = EFX_DWORD_FIELD(hdr, MCDI_HEADER_ERROR);

	अगर (respcmd != MC_CMD_V2_EXTN) अणु
		mcdi->resp_hdr_len = 4;
		mcdi->resp_data_len = EFX_DWORD_FIELD(hdr, MCDI_HEADER_DATALEN);
	पूर्ण अन्यथा अणु
		efx->type->mcdi_पढ़ो_response(efx, &hdr, 4, 4);
		mcdi->resp_hdr_len = 8;
		mcdi->resp_data_len =
			EFX_DWORD_FIELD(hdr, MC_CMD_V2_EXTN_IN_ACTUAL_LEN);
	पूर्ण

#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
	अगर (mcdi->logging_enabled && !WARN_ON_ONCE(!buf)) अणु
		माप_प्रकार hdr_len, data_len;
		पूर्णांक bytes = 0;
		पूर्णांक i;

		WARN_ON_ONCE(mcdi->resp_hdr_len % 4);
		hdr_len = mcdi->resp_hdr_len / 4;
		/* MCDI_DECLARE_BUF ensures that underlying buffer is padded
		 * to dword size, and the MCDI buffer is always dword size
		 */
		data_len = DIV_ROUND_UP(mcdi->resp_data_len, 4);

		/* We own the logging buffer, as only one MCDI can be in
		 * progress on a NIC at any one समय.  So no need क्रम locking.
		 */
		क्रम (i = 0; i < hdr_len && bytes < PAGE_SIZE; i++) अणु
			efx->type->mcdi_पढ़ो_response(efx, &hdr, (i * 4), 4);
			bytes += scnम_लिखो(buf + bytes, PAGE_SIZE - bytes,
					   " %08x", le32_to_cpu(hdr.u32[0]));
		पूर्ण

		क्रम (i = 0; i < data_len && bytes < PAGE_SIZE; i++) अणु
			efx->type->mcdi_पढ़ो_response(efx, &hdr,
					mcdi->resp_hdr_len + (i * 4), 4);
			bytes += scnम_लिखो(buf + bytes, PAGE_SIZE - bytes,
					   " %08x", le32_to_cpu(hdr.u32[0]));
		पूर्ण

		netअगर_info(efx, hw, efx->net_dev, "MCDI RPC RESP:%s\n", buf);
	पूर्ण
#पूर्ण_अगर

	mcdi->resprc_raw = 0;
	अगर (error && mcdi->resp_data_len == 0) अणु
		netअगर_err(efx, hw, efx->net_dev, "MC rebooted\n");
		mcdi->resprc = -EIO;
	पूर्ण अन्यथा अगर ((respseq ^ mcdi->seqno) & SEQ_MASK) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "MC response mismatch tx seq 0x%x rx seq 0x%x\n",
			  respseq, mcdi->seqno);
		mcdi->resprc = -EIO;
	पूर्ण अन्यथा अगर (error) अणु
		efx->type->mcdi_पढ़ो_response(efx, &hdr, mcdi->resp_hdr_len, 4);
		mcdi->resprc_raw = EFX_DWORD_FIELD(hdr, EFX_DWORD_0);
		mcdi->resprc = efx_mcdi_त्रुटि_सं(mcdi->resprc_raw);
	पूर्ण अन्यथा अणु
		mcdi->resprc = 0;
	पूर्ण
पूर्ण

अटल bool efx_mcdi_poll_once(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);

	rmb();
	अगर (!efx->type->mcdi_poll_response(efx))
		वापस false;

	spin_lock_bh(&mcdi->अगरace_lock);
	efx_mcdi_पढ़ो_response_header(efx);
	spin_unlock_bh(&mcdi->अगरace_lock);

	वापस true;
पूर्ण

अटल पूर्णांक efx_mcdi_poll(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);
	अचिन्हित दीर्घ समय, finish;
	अचिन्हित पूर्णांक spins;
	पूर्णांक rc;

	/* Check क्रम a reboot atomically with respect to efx_mcdi_copyout() */
	rc = efx_mcdi_poll_reboot(efx);
	अगर (rc) अणु
		spin_lock_bh(&mcdi->अगरace_lock);
		mcdi->resprc = rc;
		mcdi->resp_hdr_len = 0;
		mcdi->resp_data_len = 0;
		spin_unlock_bh(&mcdi->अगरace_lock);
		वापस 0;
	पूर्ण

	/* Poll क्रम completion. Poll quickly (once a us) क्रम the 1st jअगरfy,
	 * because generally mcdi responses are fast. After that, back off
	 * and poll once a jअगरfy (approximately)
	 */
	spins = USER_TICK_USEC;
	finish = jअगरfies + MCDI_RPC_TIMEOUT;

	जबतक (1) अणु
		अगर (spins != 0) अणु
			--spins;
			udelay(1);
		पूर्ण अन्यथा अणु
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण

		समय = jअगरfies;

		अगर (efx_mcdi_poll_once(efx))
			अवरोध;

		अगर (समय_after(समय, finish))
			वापस -ETIMEDOUT;
	पूर्ण

	/* Return rc=0 like रुको_event_समयout() */
	वापस 0;
पूर्ण

/* Test and clear MC-rebooted flag क्रम this port/function; reset
 * software state as necessary.
 */
पूर्णांक efx_mcdi_poll_reboot(काष्ठा efx_nic *efx)
अणु
	अगर (!efx->mcdi)
		वापस 0;

	वापस efx->type->mcdi_poll_reboot(efx);
पूर्ण

अटल bool efx_mcdi_acquire_async(काष्ठा efx_mcdi_अगरace *mcdi)
अणु
	वापस cmpxchg(&mcdi->state,
		       MCDI_STATE_QUIESCENT, MCDI_STATE_RUNNING_ASYNC) ==
		MCDI_STATE_QUIESCENT;
पूर्ण

अटल व्योम efx_mcdi_acquire_sync(काष्ठा efx_mcdi_अगरace *mcdi)
अणु
	/* Wait until the पूर्णांकerface becomes QUIESCENT and we win the race
	 * to mark it RUNNING_SYNC.
	 */
	रुको_event(mcdi->wq,
		   cmpxchg(&mcdi->state,
			   MCDI_STATE_QUIESCENT, MCDI_STATE_RUNNING_SYNC) ==
		   MCDI_STATE_QUIESCENT);
पूर्ण

अटल पूर्णांक efx_mcdi_aरुको_completion(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);

	अगर (रुको_event_समयout(mcdi->wq, mcdi->state == MCDI_STATE_COMPLETED,
			       MCDI_RPC_TIMEOUT) == 0)
		वापस -ETIMEDOUT;

	/* Check अगर efx_mcdi_set_mode() चयनed us back to polled completions.
	 * In which हाल, poll क्रम completions directly. If efx_mcdi_ev_cpl()
	 * completed the request first, then we'll just end up completing the
	 * request again, which is safe.
	 *
	 * We need an smp_rmb() to synchronise with efx_mcdi_mode_poll(), which
	 * रुको_event_समयout() implicitly provides.
	 */
	अगर (mcdi->mode == MCDI_MODE_POLL)
		वापस efx_mcdi_poll(efx);

	वापस 0;
पूर्ण

/* If the पूर्णांकerface is RUNNING_SYNC, चयन to COMPLETED and wake the
 * requester.  Return whether this was करोne.  Does not take any locks.
 */
अटल bool efx_mcdi_complete_sync(काष्ठा efx_mcdi_अगरace *mcdi)
अणु
	अगर (cmpxchg(&mcdi->state,
		    MCDI_STATE_RUNNING_SYNC, MCDI_STATE_COMPLETED) ==
	    MCDI_STATE_RUNNING_SYNC) अणु
		wake_up(&mcdi->wq);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम efx_mcdi_release(काष्ठा efx_mcdi_अगरace *mcdi)
अणु
	अगर (mcdi->mode == MCDI_MODE_EVENTS) अणु
		काष्ठा efx_mcdi_async_param *async;
		काष्ठा efx_nic *efx = mcdi->efx;

		/* Process the asynchronous request queue */
		spin_lock_bh(&mcdi->async_lock);
		async = list_first_entry_or_null(
			&mcdi->async_list, काष्ठा efx_mcdi_async_param, list);
		अगर (async) अणु
			mcdi->state = MCDI_STATE_RUNNING_ASYNC;
			efx_mcdi_send_request(efx, async->cmd,
					      (स्थिर efx_dword_t *)(async + 1),
					      async->inlen);
			mod_समयr(&mcdi->async_समयr,
				  jअगरfies + MCDI_RPC_TIMEOUT);
		पूर्ण
		spin_unlock_bh(&mcdi->async_lock);

		अगर (async)
			वापस;
	पूर्ण

	mcdi->state = MCDI_STATE_QUIESCENT;
	wake_up(&mcdi->wq);
पूर्ण

/* If the पूर्णांकerface is RUNNING_ASYNC, चयन to COMPLETED, call the
 * asynchronous completion function, and release the पूर्णांकerface.
 * Return whether this was करोne.  Must be called in bh-disabled
 * context.  Will take अगरace_lock and async_lock.
 */
अटल bool efx_mcdi_complete_async(काष्ठा efx_mcdi_अगरace *mcdi, bool समयout)
अणु
	काष्ठा efx_nic *efx = mcdi->efx;
	काष्ठा efx_mcdi_async_param *async;
	माप_प्रकार hdr_len, data_len, err_len;
	efx_dword_t *outbuf;
	MCDI_DECLARE_BUF_ERR(errbuf);
	पूर्णांक rc;

	अगर (cmpxchg(&mcdi->state,
		    MCDI_STATE_RUNNING_ASYNC, MCDI_STATE_COMPLETED) !=
	    MCDI_STATE_RUNNING_ASYNC)
		वापस false;

	spin_lock(&mcdi->अगरace_lock);
	अगर (समयout) अणु
		/* Ensure that अगर the completion event arrives later,
		 * the seqno check in efx_mcdi_ev_cpl() will fail
		 */
		++mcdi->seqno;
		++mcdi->credits;
		rc = -ETIMEDOUT;
		hdr_len = 0;
		data_len = 0;
	पूर्ण अन्यथा अणु
		rc = mcdi->resprc;
		hdr_len = mcdi->resp_hdr_len;
		data_len = mcdi->resp_data_len;
	पूर्ण
	spin_unlock(&mcdi->अगरace_lock);

	/* Stop the समयr.  In हाल the समयr function is running, we
	 * must रुको क्रम it to वापस so that there is no possibility
	 * of it पातing the next request.
	 */
	अगर (!समयout)
		del_समयr_sync(&mcdi->async_समयr);

	spin_lock(&mcdi->async_lock);
	async = list_first_entry(&mcdi->async_list,
				 काष्ठा efx_mcdi_async_param, list);
	list_del(&async->list);
	spin_unlock(&mcdi->async_lock);

	outbuf = (efx_dword_t *)(async + 1);
	efx->type->mcdi_पढ़ो_response(efx, outbuf, hdr_len,
				      min(async->outlen, data_len));
	अगर (!समयout && rc && !async->quiet) अणु
		err_len = min(माप(errbuf), data_len);
		efx->type->mcdi_पढ़ो_response(efx, errbuf, hdr_len,
					      माप(errbuf));
		efx_mcdi_display_error(efx, async->cmd, async->inlen, errbuf,
				       err_len, rc);
	पूर्ण

	अगर (async->complete)
		async->complete(efx, async->cookie, rc, outbuf,
				min(async->outlen, data_len));
	kमुक्त(async);

	efx_mcdi_release(mcdi);

	वापस true;
पूर्ण

अटल व्योम efx_mcdi_ev_cpl(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक seqno,
			    अचिन्हित पूर्णांक datalen, अचिन्हित पूर्णांक mcdi_err)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);
	bool wake = false;

	spin_lock(&mcdi->अगरace_lock);

	अगर ((seqno ^ mcdi->seqno) & SEQ_MASK) अणु
		अगर (mcdi->credits)
			/* The request has been cancelled */
			--mcdi->credits;
		अन्यथा
			netअगर_err(efx, hw, efx->net_dev,
				  "MC response mismatch tx seq 0x%x rx "
				  "seq 0x%x\n", seqno, mcdi->seqno);
	पूर्ण अन्यथा अणु
		अगर (efx->type->mcdi_max_ver >= 2) अणु
			/* MCDI v2 responses करोn't fit in an event */
			efx_mcdi_पढ़ो_response_header(efx);
		पूर्ण अन्यथा अणु
			mcdi->resprc = efx_mcdi_त्रुटि_सं(mcdi_err);
			mcdi->resp_hdr_len = 4;
			mcdi->resp_data_len = datalen;
		पूर्ण

		wake = true;
	पूर्ण

	spin_unlock(&mcdi->अगरace_lock);

	अगर (wake) अणु
		अगर (!efx_mcdi_complete_async(mcdi, false))
			(व्योम) efx_mcdi_complete_sync(mcdi);

		/* If the पूर्णांकerface isn't RUNNING_ASYNC or
		 * RUNNING_SYNC then we've received a duplicate
		 * completion after we've alपढ़ोy transitioned back to
		 * QUIESCENT. [A subsequent invocation would increment
		 * seqno, so would have failed the seqno check].
		 */
	पूर्ण
पूर्ण

अटल व्योम efx_mcdi_समयout_async(काष्ठा समयr_list *t)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = from_समयr(mcdi, t, async_समयr);

	efx_mcdi_complete_async(mcdi, true);
पूर्ण

अटल पूर्णांक
efx_mcdi_check_supported(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक cmd, माप_प्रकार inlen)
अणु
	अगर (efx->type->mcdi_max_ver < 0 ||
	     (efx->type->mcdi_max_ver < 2 &&
	      cmd > MC_CMD_CMD_SPACE_ESCAPE_7))
		वापस -EINVAL;

	अगर (inlen > MCDI_CTL_SDU_LEN_MAX_V2 ||
	    (efx->type->mcdi_max_ver < 2 &&
	     inlen > MCDI_CTL_SDU_LEN_MAX_V1))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल bool efx_mcdi_get_proxy_handle(काष्ठा efx_nic *efx,
				      माप_प्रकार hdr_len, माप_प्रकार data_len,
				      u32 *proxy_handle)
अणु
	MCDI_DECLARE_BUF_ERR(testbuf);
	स्थिर माप_प्रकार buflen = माप(testbuf);

	अगर (!proxy_handle || data_len < buflen)
		वापस false;

	efx->type->mcdi_पढ़ो_response(efx, testbuf, hdr_len, buflen);
	अगर (MCDI_DWORD(testbuf, ERR_CODE) == MC_CMD_ERR_PROXY_PENDING) अणु
		*proxy_handle = MCDI_DWORD(testbuf, ERR_PROXY_PENDING_HANDLE);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक _efx_mcdi_rpc_finish(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक cmd,
				माप_प्रकार inlen,
				efx_dword_t *outbuf, माप_प्रकार outlen,
				माप_प्रकार *outlen_actual, bool quiet,
				u32 *proxy_handle, पूर्णांक *raw_rc)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);
	MCDI_DECLARE_BUF_ERR(errbuf);
	पूर्णांक rc;

	अगर (mcdi->mode == MCDI_MODE_POLL)
		rc = efx_mcdi_poll(efx);
	अन्यथा
		rc = efx_mcdi_aरुको_completion(efx);

	अगर (rc != 0) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "MC command 0x%x inlen %d mode %d timed out\n",
			  cmd, (पूर्णांक)inlen, mcdi->mode);

		अगर (mcdi->mode == MCDI_MODE_EVENTS && efx_mcdi_poll_once(efx)) अणु
			netअगर_err(efx, hw, efx->net_dev,
				  "MCDI request was completed without an event\n");
			rc = 0;
		पूर्ण

		efx_mcdi_abanकरोn(efx);

		/* Close the race with efx_mcdi_ev_cpl() executing just too late
		 * and completing a request we've just cancelled, by ensuring
		 * that the seqno check therein fails.
		 */
		spin_lock_bh(&mcdi->अगरace_lock);
		++mcdi->seqno;
		++mcdi->credits;
		spin_unlock_bh(&mcdi->अगरace_lock);
	पूर्ण

	अगर (proxy_handle)
		*proxy_handle = 0;

	अगर (rc != 0) अणु
		अगर (outlen_actual)
			*outlen_actual = 0;
	पूर्ण अन्यथा अणु
		माप_प्रकार hdr_len, data_len, err_len;

		/* At the very least we need a memory barrier here to ensure
		 * we pick up changes from efx_mcdi_ev_cpl(). Protect against
		 * a spurious efx_mcdi_ev_cpl() running concurrently by
		 * acquiring the अगरace_lock. */
		spin_lock_bh(&mcdi->अगरace_lock);
		rc = mcdi->resprc;
		अगर (raw_rc)
			*raw_rc = mcdi->resprc_raw;
		hdr_len = mcdi->resp_hdr_len;
		data_len = mcdi->resp_data_len;
		err_len = min(माप(errbuf), data_len);
		spin_unlock_bh(&mcdi->अगरace_lock);

		BUG_ON(rc > 0);

		efx->type->mcdi_पढ़ो_response(efx, outbuf, hdr_len,
					      min(outlen, data_len));
		अगर (outlen_actual)
			*outlen_actual = data_len;

		efx->type->mcdi_पढ़ो_response(efx, errbuf, hdr_len, err_len);

		अगर (cmd == MC_CMD_REBOOT && rc == -EIO) अणु
			/* Don't reset अगर MC_CMD_REBOOT वापसs EIO */
		पूर्ण अन्यथा अगर (rc == -EIO || rc == -EINTR) अणु
			netअगर_err(efx, hw, efx->net_dev, "MC reboot detected\n");
			netअगर_dbg(efx, hw, efx->net_dev, "MC rebooted during command %d rc %d\n",
				  cmd, -rc);
			अगर (efx->type->mcdi_reboot_detected)
				efx->type->mcdi_reboot_detected(efx);
			efx_schedule_reset(efx, RESET_TYPE_MC_FAILURE);
		पूर्ण अन्यथा अगर (proxy_handle && (rc == -EPROTO) &&
			   efx_mcdi_get_proxy_handle(efx, hdr_len, data_len,
						     proxy_handle)) अणु
			mcdi->proxy_rx_status = 0;
			mcdi->proxy_rx_handle = 0;
			mcdi->state = MCDI_STATE_PROXY_WAIT;
		पूर्ण अन्यथा अगर (rc && !quiet) अणु
			efx_mcdi_display_error(efx, cmd, inlen, errbuf, err_len,
					       rc);
		पूर्ण

		अगर (rc == -EIO || rc == -EINTR) अणु
			msleep(MCDI_STATUS_SLEEP_MS);
			efx_mcdi_poll_reboot(efx);
			mcdi->new_epoch = true;
		पूर्ण
	पूर्ण

	अगर (!proxy_handle || !*proxy_handle)
		efx_mcdi_release(mcdi);
	वापस rc;
पूर्ण

अटल व्योम efx_mcdi_proxy_पात(काष्ठा efx_mcdi_अगरace *mcdi)
अणु
	अगर (mcdi->state == MCDI_STATE_PROXY_WAIT) अणु
		/* Interrupt the proxy रुको. */
		mcdi->proxy_rx_status = -EINTR;
		wake_up(&mcdi->proxy_rx_wq);
	पूर्ण
पूर्ण

अटल व्योम efx_mcdi_ev_proxy_response(काष्ठा efx_nic *efx,
				       u32 handle, पूर्णांक status)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);

	WARN_ON(mcdi->state != MCDI_STATE_PROXY_WAIT);

	mcdi->proxy_rx_status = efx_mcdi_त्रुटि_सं(status);
	/* Ensure the status is written beक्रमe we update the handle, since the
	 * latter is used to check अगर we've finished.
	 */
	wmb();
	mcdi->proxy_rx_handle = handle;
	wake_up(&mcdi->proxy_rx_wq);
पूर्ण

अटल पूर्णांक efx_mcdi_proxy_रुको(काष्ठा efx_nic *efx, u32 handle, bool quiet)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);
	पूर्णांक rc;

	/* Wait क्रम a proxy event, or समयout. */
	rc = रुको_event_समयout(mcdi->proxy_rx_wq,
				mcdi->proxy_rx_handle != 0 ||
				mcdi->proxy_rx_status == -EINTR,
				MCDI_RPC_TIMEOUT);

	अगर (rc <= 0) अणु
		netअगर_dbg(efx, hw, efx->net_dev,
			  "MCDI proxy timeout %d\n", handle);
		वापस -ETIMEDOUT;
	पूर्ण अन्यथा अगर (mcdi->proxy_rx_handle != handle) अणु
		netअगर_warn(efx, hw, efx->net_dev,
			   "MCDI proxy unexpected handle %d (expected %d)\n",
			   mcdi->proxy_rx_handle, handle);
		वापस -EINVAL;
	पूर्ण

	वापस mcdi->proxy_rx_status;
पूर्ण

अटल पूर्णांक _efx_mcdi_rpc(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक cmd,
			 स्थिर efx_dword_t *inbuf, माप_प्रकार inlen,
			 efx_dword_t *outbuf, माप_प्रकार outlen,
			 माप_प्रकार *outlen_actual, bool quiet, पूर्णांक *raw_rc)
अणु
	u32 proxy_handle = 0; /* Zero is an invalid proxy handle. */
	पूर्णांक rc;

	अगर (inbuf && inlen && (inbuf == outbuf)) अणु
		/* The input buffer can't be aliased with the output. */
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	rc = efx_mcdi_rpc_start(efx, cmd, inbuf, inlen);
	अगर (rc)
		वापस rc;

	rc = _efx_mcdi_rpc_finish(efx, cmd, inlen, outbuf, outlen,
				  outlen_actual, quiet, &proxy_handle, raw_rc);

	अगर (proxy_handle) अणु
		/* Handle proxy authorisation. This allows approval of MCDI
		 * operations to be delegated to the admin function, allowing
		 * fine control over (eg) multicast subscriptions.
		 */
		काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);

		netअगर_dbg(efx, hw, efx->net_dev,
			  "MCDI waiting for proxy auth %d\n",
			  proxy_handle);
		rc = efx_mcdi_proxy_रुको(efx, proxy_handle, quiet);

		अगर (rc == 0) अणु
			netअगर_dbg(efx, hw, efx->net_dev,
				  "MCDI proxy retry %d\n", proxy_handle);

			/* We now retry the original request. */
			mcdi->state = MCDI_STATE_RUNNING_SYNC;
			efx_mcdi_send_request(efx, cmd, inbuf, inlen);

			rc = _efx_mcdi_rpc_finish(efx, cmd, inlen,
						  outbuf, outlen, outlen_actual,
						  quiet, शून्य, raw_rc);
		पूर्ण अन्यथा अणु
			netअगर_cond_dbg(efx, hw, efx->net_dev, rc == -EPERM, err,
				       "MC command 0x%x failed after proxy auth rc=%d\n",
				       cmd, rc);

			अगर (rc == -EINTR || rc == -EIO)
				efx_schedule_reset(efx, RESET_TYPE_MC_FAILURE);
			efx_mcdi_release(mcdi);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक _efx_mcdi_rpc_evb_retry(काष्ठा efx_nic *efx, अचिन्हित cmd,
				   स्थिर efx_dword_t *inbuf, माप_प्रकार inlen,
				   efx_dword_t *outbuf, माप_प्रकार outlen,
				   माप_प्रकार *outlen_actual, bool quiet)
अणु
	पूर्णांक raw_rc = 0;
	पूर्णांक rc;

	rc = _efx_mcdi_rpc(efx, cmd, inbuf, inlen,
			   outbuf, outlen, outlen_actual, true, &raw_rc);

	अगर ((rc == -EPROTO) && (raw_rc == MC_CMD_ERR_NO_EVB_PORT) &&
	    efx->type->is_vf) अणु
		/* If the EVB port isn't available within a VF this may
		 * mean the PF is still bringing the चयन up. We should
		 * retry our request लघुly.
		 */
		अचिन्हित दीर्घ पात_समय = jअगरfies + MCDI_RPC_TIMEOUT;
		अचिन्हित पूर्णांक delay_us = 10000;

		netअगर_dbg(efx, hw, efx->net_dev,
			  "%s: NO_EVB_PORT; will retry request\n",
			  __func__);

		करो अणु
			usleep_range(delay_us, delay_us + 10000);
			rc = _efx_mcdi_rpc(efx, cmd, inbuf, inlen,
					   outbuf, outlen, outlen_actual,
					   true, &raw_rc);
			अगर (delay_us < 100000)
				delay_us <<= 1;
		पूर्ण जबतक ((rc == -EPROTO) &&
			 (raw_rc == MC_CMD_ERR_NO_EVB_PORT) &&
			 समय_beक्रमe(jअगरfies, पात_समय));
	पूर्ण

	अगर (rc && !quiet && !(cmd == MC_CMD_REBOOT && rc == -EIO))
		efx_mcdi_display_error(efx, cmd, inlen,
				       outbuf, outlen, rc);

	वापस rc;
पूर्ण

/**
 * efx_mcdi_rpc - Issue an MCDI command and रुको क्रम completion
 * @efx: NIC through which to issue the command
 * @cmd: Command type number
 * @inbuf: Command parameters
 * @inlen: Length of command parameters, in bytes.  Must be a multiple
 *	of 4 and no greater than %MCDI_CTL_SDU_LEN_MAX_V1.
 * @outbuf: Response buffer.  May be %शून्य अगर @outlen is 0.
 * @outlen: Length of response buffer, in bytes.  If the actual
 *	response is दीर्घer than @outlen & ~3, it will be truncated
 *	to that length.
 * @outlen_actual: Poपूर्णांकer through which to वापस the actual response
 *	length.  May be %शून्य अगर this is not needed.
 *
 * This function may sleep and thereक्रमe must be called in an appropriate
 * context.
 *
 * Return: A negative error code, or zero अगर successful.  The error
 *	code may come from the MCDI response or may indicate a failure
 *	to communicate with the MC.  In the क्रमmer हाल, the response
 *	will still be copied to @outbuf and *@outlen_actual will be
 *	set accordingly.  In the latter हाल, *@outlen_actual will be
 *	set to zero.
 */
पूर्णांक efx_mcdi_rpc(काष्ठा efx_nic *efx, अचिन्हित cmd,
		 स्थिर efx_dword_t *inbuf, माप_प्रकार inlen,
		 efx_dword_t *outbuf, माप_प्रकार outlen,
		 माप_प्रकार *outlen_actual)
अणु
	वापस _efx_mcdi_rpc_evb_retry(efx, cmd, inbuf, inlen, outbuf, outlen,
				       outlen_actual, false);
पूर्ण

/* Normally, on receiving an error code in the MCDI response,
 * efx_mcdi_rpc will log an error message containing (among other
 * things) the raw error code, by means of efx_mcdi_display_error.
 * This _quiet version suppresses that; अगर the caller wishes to log
 * the error conditionally on the वापस code, it should call this
 * function and is then responsible क्रम calling efx_mcdi_display_error
 * as needed.
 */
पूर्णांक efx_mcdi_rpc_quiet(काष्ठा efx_nic *efx, अचिन्हित cmd,
		       स्थिर efx_dword_t *inbuf, माप_प्रकार inlen,
		       efx_dword_t *outbuf, माप_प्रकार outlen,
		       माप_प्रकार *outlen_actual)
अणु
	वापस _efx_mcdi_rpc_evb_retry(efx, cmd, inbuf, inlen, outbuf, outlen,
				       outlen_actual, true);
पूर्ण

पूर्णांक efx_mcdi_rpc_start(काष्ठा efx_nic *efx, अचिन्हित cmd,
		       स्थिर efx_dword_t *inbuf, माप_प्रकार inlen)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);
	पूर्णांक rc;

	rc = efx_mcdi_check_supported(efx, cmd, inlen);
	अगर (rc)
		वापस rc;

	अगर (efx->mc_bist_क्रम_other_fn)
		वापस -ENETDOWN;

	अगर (mcdi->mode == MCDI_MODE_FAIL)
		वापस -ENETDOWN;

	efx_mcdi_acquire_sync(mcdi);
	efx_mcdi_send_request(efx, cmd, inbuf, inlen);
	वापस 0;
पूर्ण

अटल पूर्णांक _efx_mcdi_rpc_async(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक cmd,
			       स्थिर efx_dword_t *inbuf, माप_प्रकार inlen,
			       माप_प्रकार outlen,
			       efx_mcdi_async_completer *complete,
			       अचिन्हित दीर्घ cookie, bool quiet)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);
	काष्ठा efx_mcdi_async_param *async;
	पूर्णांक rc;

	rc = efx_mcdi_check_supported(efx, cmd, inlen);
	अगर (rc)
		वापस rc;

	अगर (efx->mc_bist_क्रम_other_fn)
		वापस -ENETDOWN;

	async = kदो_स्मृति(माप(*async) + ALIGN(max(inlen, outlen), 4),
			GFP_ATOMIC);
	अगर (!async)
		वापस -ENOMEM;

	async->cmd = cmd;
	async->inlen = inlen;
	async->outlen = outlen;
	async->quiet = quiet;
	async->complete = complete;
	async->cookie = cookie;
	स_नकल(async + 1, inbuf, inlen);

	spin_lock_bh(&mcdi->async_lock);

	अगर (mcdi->mode == MCDI_MODE_EVENTS) अणु
		list_add_tail(&async->list, &mcdi->async_list);

		/* If this is at the front of the queue, try to start it
		 * immediately
		 */
		अगर (mcdi->async_list.next == &async->list &&
		    efx_mcdi_acquire_async(mcdi)) अणु
			efx_mcdi_send_request(efx, cmd, inbuf, inlen);
			mod_समयr(&mcdi->async_समयr,
				  jअगरfies + MCDI_RPC_TIMEOUT);
		पूर्ण
	पूर्ण अन्यथा अणु
		kमुक्त(async);
		rc = -ENETDOWN;
	पूर्ण

	spin_unlock_bh(&mcdi->async_lock);

	वापस rc;
पूर्ण

/**
 * efx_mcdi_rpc_async - Schedule an MCDI command to run asynchronously
 * @efx: NIC through which to issue the command
 * @cmd: Command type number
 * @inbuf: Command parameters
 * @inlen: Length of command parameters, in bytes
 * @outlen: Length to allocate क्रम response buffer, in bytes
 * @complete: Function to be called on completion or cancellation.
 * @cookie: Arbitrary value to be passed to @complete.
 *
 * This function करोes not sleep and thereक्रमe may be called in atomic
 * context.  It will fail अगर event queues are disabled or अगर MCDI
 * event completions have been disabled due to an error.
 *
 * If it succeeds, the @complete function will be called exactly once
 * in atomic context, when one of the following occurs:
 * (a) the completion event is received (in NAPI context)
 * (b) event queues are disabled (in the process that disables them)
 * (c) the request बार-out (in समयr context)
 */
पूर्णांक
efx_mcdi_rpc_async(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक cmd,
		   स्थिर efx_dword_t *inbuf, माप_प्रकार inlen, माप_प्रकार outlen,
		   efx_mcdi_async_completer *complete, अचिन्हित दीर्घ cookie)
अणु
	वापस _efx_mcdi_rpc_async(efx, cmd, inbuf, inlen, outlen, complete,
				   cookie, false);
पूर्ण

पूर्णांक efx_mcdi_rpc_async_quiet(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक cmd,
			     स्थिर efx_dword_t *inbuf, माप_प्रकार inlen,
			     माप_प्रकार outlen, efx_mcdi_async_completer *complete,
			     अचिन्हित दीर्घ cookie)
अणु
	वापस _efx_mcdi_rpc_async(efx, cmd, inbuf, inlen, outlen, complete,
				   cookie, true);
पूर्ण

पूर्णांक efx_mcdi_rpc_finish(काष्ठा efx_nic *efx, अचिन्हित cmd, माप_प्रकार inlen,
			efx_dword_t *outbuf, माप_प्रकार outlen,
			माप_प्रकार *outlen_actual)
अणु
	वापस _efx_mcdi_rpc_finish(efx, cmd, inlen, outbuf, outlen,
				    outlen_actual, false, शून्य, शून्य);
पूर्ण

पूर्णांक efx_mcdi_rpc_finish_quiet(काष्ठा efx_nic *efx, अचिन्हित cmd, माप_प्रकार inlen,
			      efx_dword_t *outbuf, माप_प्रकार outlen,
			      माप_प्रकार *outlen_actual)
अणु
	वापस _efx_mcdi_rpc_finish(efx, cmd, inlen, outbuf, outlen,
				    outlen_actual, true, शून्य, शून्य);
पूर्ण

व्योम efx_mcdi_display_error(काष्ठा efx_nic *efx, अचिन्हित cmd,
			    माप_प्रकार inlen, efx_dword_t *outbuf,
			    माप_प्रकार outlen, पूर्णांक rc)
अणु
	पूर्णांक code = 0, err_arg = 0;

	अगर (outlen >= MC_CMD_ERR_CODE_OFST + 4)
		code = MCDI_DWORD(outbuf, ERR_CODE);
	अगर (outlen >= MC_CMD_ERR_ARG_OFST + 4)
		err_arg = MCDI_DWORD(outbuf, ERR_ARG);
	netअगर_cond_dbg(efx, hw, efx->net_dev, rc == -EPERM, err,
		       "MC command 0x%x inlen %zu failed rc=%d (raw=%d) arg=%d\n",
		       cmd, inlen, rc, code, err_arg);
पूर्ण

/* Switch to polled MCDI completions.  This can be called in various
 * error conditions with various locks held, so it must be lockless.
 * Caller is responsible क्रम flushing asynchronous requests later.
 */
व्योम efx_mcdi_mode_poll(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi;

	अगर (!efx->mcdi)
		वापस;

	mcdi = efx_mcdi(efx);
	/* If alपढ़ोy in polling mode, nothing to करो.
	 * If in fail-fast state, करोn't चयन to polled completion.
	 * FLR recovery will करो that later.
	 */
	अगर (mcdi->mode == MCDI_MODE_POLL || mcdi->mode == MCDI_MODE_FAIL)
		वापस;

	/* We can चयन from event completion to polled completion, because
	 * mcdi requests are always completed in shared memory. We करो this by
	 * चयनing the mode to POLL'd then completing the request.
	 * efx_mcdi_aरुको_completion() will then call efx_mcdi_poll().
	 *
	 * We need an smp_wmb() to synchronise with efx_mcdi_aरुको_completion(),
	 * which efx_mcdi_complete_sync() provides क्रम us.
	 */
	mcdi->mode = MCDI_MODE_POLL;

	efx_mcdi_complete_sync(mcdi);
पूर्ण

/* Flush any running or queued asynchronous requests, after event processing
 * is stopped
 */
व्योम efx_mcdi_flush_async(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_async_param *async, *next;
	काष्ठा efx_mcdi_अगरace *mcdi;

	अगर (!efx->mcdi)
		वापस;

	mcdi = efx_mcdi(efx);

	/* We must be in poll or fail mode so no more requests can be queued */
	BUG_ON(mcdi->mode == MCDI_MODE_EVENTS);

	del_समयr_sync(&mcdi->async_समयr);

	/* If a request is still running, make sure we give the MC
	 * समय to complete it so that the response won't overग_लिखो our
	 * next request.
	 */
	अगर (mcdi->state == MCDI_STATE_RUNNING_ASYNC) अणु
		efx_mcdi_poll(efx);
		mcdi->state = MCDI_STATE_QUIESCENT;
	पूर्ण

	/* Nothing अन्यथा will access the async list now, so it is safe
	 * to walk it without holding async_lock.  If we hold it जबतक
	 * calling a completer then lockdep may warn that we have
	 * acquired locks in the wrong order.
	 */
	list_क्रम_each_entry_safe(async, next, &mcdi->async_list, list) अणु
		अगर (async->complete)
			async->complete(efx, async->cookie, -ENETDOWN, शून्य, 0);
		list_del(&async->list);
		kमुक्त(async);
	पूर्ण
पूर्ण

व्योम efx_mcdi_mode_event(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi;

	अगर (!efx->mcdi)
		वापस;

	mcdi = efx_mcdi(efx);
	/* If alपढ़ोy in event completion mode, nothing to करो.
	 * If in fail-fast state, करोn't चयन to event completion.  FLR
	 * recovery will करो that later.
	 */
	अगर (mcdi->mode == MCDI_MODE_EVENTS || mcdi->mode == MCDI_MODE_FAIL)
		वापस;

	/* We can't चयन from polled to event completion in the middle of a
	 * request, because the completion method is specअगरied in the request.
	 * So acquire the पूर्णांकerface to serialise the requestors. We करोn't need
	 * to acquire the अगरace_lock to change the mode here, but we करो need a
	 * ग_लिखो memory barrier ensure that efx_mcdi_rpc() sees it, which
	 * efx_mcdi_acquire() provides.
	 */
	efx_mcdi_acquire_sync(mcdi);
	mcdi->mode = MCDI_MODE_EVENTS;
	efx_mcdi_release(mcdi);
पूर्ण

अटल व्योम efx_mcdi_ev_death(काष्ठा efx_nic *efx, पूर्णांक rc)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);

	/* If there is an outstanding MCDI request, it has been terminated
	 * either by a BADASSERT or REBOOT event. If the mcdi पूर्णांकerface is
	 * in polled mode, then करो nothing because the MC reboot handler will
	 * set the header correctly. However, अगर the mcdi पूर्णांकerface is रुकोing
	 * क्रम a CMDDONE event it won't receive it [and since all MCDI events
	 * are sent to the same queue, we can't be racing with
	 * efx_mcdi_ev_cpl()]
	 *
	 * If there is an outstanding asynchronous request, we can't
	 * complete it now (efx_mcdi_complete() would deadlock).  The
	 * reset process will take care of this.
	 *
	 * There's a race here with efx_mcdi_send_request(), because
	 * we might receive a REBOOT event *beक्रमe* the request has
	 * been copied out. In polled mode (during startup) this is
	 * irrelevant, because efx_mcdi_complete_sync() is ignored. In
	 * event mode, this condition is just an edge-हाल of
	 * receiving a REBOOT event after posting the MCDI
	 * request. Did the mc reboot beक्रमe or after the copyout? The
	 * best we can करो always is just वापस failure.
	 *
	 * If there is an outstanding proxy response expected it is not going
	 * to arrive. We should thus पात it.
	 */
	spin_lock(&mcdi->अगरace_lock);
	efx_mcdi_proxy_पात(mcdi);

	अगर (efx_mcdi_complete_sync(mcdi)) अणु
		अगर (mcdi->mode == MCDI_MODE_EVENTS) अणु
			mcdi->resprc = rc;
			mcdi->resp_hdr_len = 0;
			mcdi->resp_data_len = 0;
			++mcdi->credits;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक count;

		/* Consume the status word since efx_mcdi_rpc_finish() won't */
		क्रम (count = 0; count < MCDI_STATUS_DELAY_COUNT; ++count) अणु
			rc = efx_mcdi_poll_reboot(efx);
			अगर (rc)
				अवरोध;
			udelay(MCDI_STATUS_DELAY_US);
		पूर्ण

		/* On EF10, a CODE_MC_REBOOT event can be received without the
		 * reboot detection in efx_mcdi_poll_reboot() being triggered.
		 * If zero was वापसed from the final call to
		 * efx_mcdi_poll_reboot(), the MC reboot wasn't noticed but the
		 * MC has definitely rebooted so prepare क्रम the reset.
		 */
		अगर (!rc && efx->type->mcdi_reboot_detected)
			efx->type->mcdi_reboot_detected(efx);

		mcdi->new_epoch = true;

		/* Nobody was रुकोing क्रम an MCDI request, so trigger a reset */
		efx_schedule_reset(efx, RESET_TYPE_MC_FAILURE);
	पूर्ण

	spin_unlock(&mcdi->अगरace_lock);
पूर्ण

/* The MC is going करोwn in to BIST mode. set the BIST flag to block
 * new MCDI, cancel any outstanding MCDI and and schedule a BIST-type reset
 * (which करोesn't actually execute a reset, it रुकोs क्रम the controlling
 * function to reset it).
 */
अटल व्योम efx_mcdi_ev_bist(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);

	spin_lock(&mcdi->अगरace_lock);
	efx->mc_bist_क्रम_other_fn = true;
	efx_mcdi_proxy_पात(mcdi);

	अगर (efx_mcdi_complete_sync(mcdi)) अणु
		अगर (mcdi->mode == MCDI_MODE_EVENTS) अणु
			mcdi->resprc = -EIO;
			mcdi->resp_hdr_len = 0;
			mcdi->resp_data_len = 0;
			++mcdi->credits;
		पूर्ण
	पूर्ण
	mcdi->new_epoch = true;
	efx_schedule_reset(efx, RESET_TYPE_MC_BIST);
	spin_unlock(&mcdi->अगरace_lock);
पूर्ण

/* MCDI समयouts seen, so make all MCDI calls fail-fast and issue an FLR to try
 * to recover.
 */
अटल व्योम efx_mcdi_abanकरोn(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);

	अगर (xchg(&mcdi->mode, MCDI_MODE_FAIL) == MCDI_MODE_FAIL)
		वापस; /* it had alपढ़ोy been करोne */
	netअगर_dbg(efx, hw, efx->net_dev, "MCDI is timing out; trying to recover\n");
	efx_schedule_reset(efx, RESET_TYPE_MCDI_TIMEOUT);
पूर्ण

अटल व्योम efx_handle_drain_event(काष्ठा efx_nic *efx)
अणु
	अगर (atomic_dec_and_test(&efx->active_queues))
		wake_up(&efx->flush_wq);

	WARN_ON(atomic_पढ़ो(&efx->active_queues) < 0);
पूर्ण

/* Called from efx_farch_ev_process and efx_ef10_ev_process क्रम MCDI events */
व्योम efx_mcdi_process_event(काष्ठा efx_channel *channel,
			    efx_qword_t *event)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	पूर्णांक code = EFX_QWORD_FIELD(*event, MCDI_EVENT_CODE);
	u32 data = EFX_QWORD_FIELD(*event, MCDI_EVENT_DATA);

	चयन (code) अणु
	हाल MCDI_EVENT_CODE_BADSSERT:
		netअगर_err(efx, hw, efx->net_dev,
			  "MC watchdog or assertion failure at 0x%x\n", data);
		efx_mcdi_ev_death(efx, -EINTR);
		अवरोध;

	हाल MCDI_EVENT_CODE_PMNOTICE:
		netअगर_info(efx, wol, efx->net_dev, "MCDI PM event.\n");
		अवरोध;

	हाल MCDI_EVENT_CODE_CMDDONE:
		efx_mcdi_ev_cpl(efx,
				MCDI_EVENT_FIELD(*event, CMDDONE_SEQ),
				MCDI_EVENT_FIELD(*event, CMDDONE_DATALEN),
				MCDI_EVENT_FIELD(*event, CMDDONE_ERRNO));
		अवरोध;

	हाल MCDI_EVENT_CODE_LINKCHANGE:
		efx_mcdi_process_link_change(efx, event);
		अवरोध;
	हाल MCDI_EVENT_CODE_SENSOREVT:
		efx_sensor_event(efx, event);
		अवरोध;
	हाल MCDI_EVENT_CODE_SCHEDERR:
		netअगर_dbg(efx, hw, efx->net_dev,
			  "MC Scheduler alert (0x%x)\n", data);
		अवरोध;
	हाल MCDI_EVENT_CODE_REBOOT:
	हाल MCDI_EVENT_CODE_MC_REBOOT:
		netअगर_info(efx, hw, efx->net_dev, "MC Reboot\n");
		efx_mcdi_ev_death(efx, -EIO);
		अवरोध;
	हाल MCDI_EVENT_CODE_MC_BIST:
		netअगर_info(efx, hw, efx->net_dev, "MC entered BIST mode\n");
		efx_mcdi_ev_bist(efx);
		अवरोध;
	हाल MCDI_EVENT_CODE_MAC_STATS_DMA:
		/* MAC stats are gather lazily.  We can ignore this. */
		अवरोध;
	हाल MCDI_EVENT_CODE_FLR:
		अगर (efx->type->sriov_flr)
			efx->type->sriov_flr(efx,
					     MCDI_EVENT_FIELD(*event, FLR_VF));
		अवरोध;
	हाल MCDI_EVENT_CODE_PTP_RX:
	हाल MCDI_EVENT_CODE_PTP_FAULT:
	हाल MCDI_EVENT_CODE_PTP_PPS:
		efx_ptp_event(efx, event);
		अवरोध;
	हाल MCDI_EVENT_CODE_PTP_TIME:
		efx_समय_sync_event(channel, event);
		अवरोध;
	हाल MCDI_EVENT_CODE_TX_FLUSH:
	हाल MCDI_EVENT_CODE_RX_FLUSH:
		/* Two flush events will be sent: one to the same event
		 * queue as completions, and one to event queue 0.
		 * In the latter हाल the अणुRX,TXपूर्ण_FLUSH_TO_DRIVER
		 * flag will be set, and we should ignore the event
		 * because we want to रुको क्रम all completions.
		 */
		BUILD_BUG_ON(MCDI_EVENT_TX_FLUSH_TO_DRIVER_LBN !=
			     MCDI_EVENT_RX_FLUSH_TO_DRIVER_LBN);
		अगर (!MCDI_EVENT_FIELD(*event, TX_FLUSH_TO_DRIVER))
			efx_handle_drain_event(efx);
		अवरोध;
	हाल MCDI_EVENT_CODE_TX_ERR:
	हाल MCDI_EVENT_CODE_RX_ERR:
		netअगर_err(efx, hw, efx->net_dev,
			  "%s DMA error (event: "EFX_QWORD_FMT")\n",
			  code == MCDI_EVENT_CODE_TX_ERR ? "TX" : "RX",
			  EFX_QWORD_VAL(*event));
		efx_schedule_reset(efx, RESET_TYPE_DMA_ERROR);
		अवरोध;
	हाल MCDI_EVENT_CODE_PROXY_RESPONSE:
		efx_mcdi_ev_proxy_response(efx,
				MCDI_EVENT_FIELD(*event, PROXY_RESPONSE_HANDLE),
				MCDI_EVENT_FIELD(*event, PROXY_RESPONSE_RC));
		अवरोध;
	शेष:
		netअगर_err(efx, hw, efx->net_dev,
			  "Unknown MCDI event " EFX_QWORD_FMT "\n",
			  EFX_QWORD_VAL(*event));
	पूर्ण
पूर्ण

/**************************************************************************
 *
 * Specअगरic request functions
 *
 **************************************************************************
 */

व्योम efx_mcdi_prपूर्णांक_fwver(काष्ठा efx_nic *efx, अक्षर *buf, माप_प्रकार len)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_VERSION_OUT_LEN);
	माप_प्रकार outlength;
	स्थिर __le16 *ver_words;
	माप_प्रकार offset;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_GET_VERSION_IN_LEN != 0);
	rc = efx_mcdi_rpc(efx, MC_CMD_GET_VERSION, शून्य, 0,
			  outbuf, माप(outbuf), &outlength);
	अगर (rc)
		जाओ fail;
	अगर (outlength < MC_CMD_GET_VERSION_OUT_LEN) अणु
		rc = -EIO;
		जाओ fail;
	पूर्ण

	ver_words = (__le16 *)MCDI_PTR(outbuf, GET_VERSION_OUT_VERSION);
	offset = scnम_लिखो(buf, len, "%u.%u.%u.%u",
			   le16_to_cpu(ver_words[0]),
			   le16_to_cpu(ver_words[1]),
			   le16_to_cpu(ver_words[2]),
			   le16_to_cpu(ver_words[3]));

	अगर (efx->type->prपूर्णांक_additional_fwver)
		offset += efx->type->prपूर्णांक_additional_fwver(efx, buf + offset,
							    len - offset);

	/* It's theoretically possible क्रम the string to exceed 31
	 * अक्षरacters, though in practice the first three version
	 * components are लघु enough that this करोesn't happen.
	 */
	अगर (WARN_ON(offset >= len))
		buf[0] = 0;

	वापस;

fail:
	netअगर_err(efx, probe, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
	buf[0] = 0;
पूर्ण

अटल पूर्णांक efx_mcdi_drv_attach(काष्ठा efx_nic *efx, bool driver_operating,
			       bool *was_attached)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_DRV_ATTACH_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_DRV_ATTACH_EXT_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, DRV_ATTACH_IN_NEW_STATE,
		       driver_operating ? 1 : 0);
	MCDI_SET_DWORD(inbuf, DRV_ATTACH_IN_UPDATE, 1);
	MCDI_SET_DWORD(inbuf, DRV_ATTACH_IN_FIRMWARE_ID, MC_CMD_FW_LOW_LATENCY);

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_DRV_ATTACH, inbuf, माप(inbuf),
				outbuf, माप(outbuf), &outlen);
	/* If we're not the primary PF, trying to ATTACH with a FIRMWARE_ID
	 * specअगरied will fail with EPERM, and we have to tell the MC we करोn't
	 * care what firmware we get.
	 */
	अगर (rc == -EPERM) अणु
		netअगर_dbg(efx, probe, efx->net_dev,
			  "efx_mcdi_drv_attach with fw-variant setting failed EPERM, trying without it\n");
		MCDI_SET_DWORD(inbuf, DRV_ATTACH_IN_FIRMWARE_ID,
			       MC_CMD_FW_DONT_CARE);
		rc = efx_mcdi_rpc_quiet(efx, MC_CMD_DRV_ATTACH, inbuf,
					माप(inbuf), outbuf, माप(outbuf),
					&outlen);
	पूर्ण
	अगर (rc) अणु
		efx_mcdi_display_error(efx, MC_CMD_DRV_ATTACH, माप(inbuf),
				       outbuf, outlen, rc);
		जाओ fail;
	पूर्ण
	अगर (outlen < MC_CMD_DRV_ATTACH_OUT_LEN) अणु
		rc = -EIO;
		जाओ fail;
	पूर्ण

	अगर (driver_operating) अणु
		अगर (outlen >= MC_CMD_DRV_ATTACH_EXT_OUT_LEN) अणु
			efx->mcdi->fn_flags =
				MCDI_DWORD(outbuf,
					   DRV_ATTACH_EXT_OUT_FUNC_FLAGS);
		पूर्ण अन्यथा अणु
			/* Synthesise flags क्रम Siena */
			efx->mcdi->fn_flags =
				1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_LINKCTRL |
				1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_TRUSTED |
				(efx_port_num(efx) == 0) <<
				MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_PRIMARY;
		पूर्ण
	पूर्ण

	/* We currently assume we have control of the बाह्यal link
	 * and are completely trusted by firmware.  Abort probing
	 * अगर that's not true क्रम this function.
	 */

	अगर (was_attached != शून्य)
		*was_attached = MCDI_DWORD(outbuf, DRV_ATTACH_OUT_OLD_STATE);
	वापस 0;

fail:
	netअगर_err(efx, probe, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_get_board_cfg(काष्ठा efx_nic *efx, u8 *mac_address,
			   u16 *fw_subtype_list, u32 *capabilities)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_BOARD_CFG_OUT_LENMAX);
	माप_प्रकार outlen, i;
	पूर्णांक port_num = efx_port_num(efx);
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_GET_BOARD_CFG_IN_LEN != 0);
	/* we need __aligned(2) क्रम ether_addr_copy */
	BUILD_BUG_ON(MC_CMD_GET_BOARD_CFG_OUT_MAC_ADDR_BASE_PORT0_OFST & 1);
	BUILD_BUG_ON(MC_CMD_GET_BOARD_CFG_OUT_MAC_ADDR_BASE_PORT1_OFST & 1);

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_BOARD_CFG, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		जाओ fail;

	अगर (outlen < MC_CMD_GET_BOARD_CFG_OUT_LENMIN) अणु
		rc = -EIO;
		जाओ fail;
	पूर्ण

	अगर (mac_address)
		ether_addr_copy(mac_address,
				port_num ?
				MCDI_PTR(outbuf, GET_BOARD_CFG_OUT_MAC_ADDR_BASE_PORT1) :
				MCDI_PTR(outbuf, GET_BOARD_CFG_OUT_MAC_ADDR_BASE_PORT0));
	अगर (fw_subtype_list) अणु
		क्रम (i = 0;
		     i < MCDI_VAR_ARRAY_LEN(outlen,
					    GET_BOARD_CFG_OUT_FW_SUBTYPE_LIST);
		     i++)
			fw_subtype_list[i] = MCDI_ARRAY_WORD(
				outbuf, GET_BOARD_CFG_OUT_FW_SUBTYPE_LIST, i);
		क्रम (; i < MC_CMD_GET_BOARD_CFG_OUT_FW_SUBTYPE_LIST_MAXNUM; i++)
			fw_subtype_list[i] = 0;
	पूर्ण
	अगर (capabilities) अणु
		अगर (port_num)
			*capabilities = MCDI_DWORD(outbuf,
					GET_BOARD_CFG_OUT_CAPABILITIES_PORT1);
		अन्यथा
			*capabilities = MCDI_DWORD(outbuf,
					GET_BOARD_CFG_OUT_CAPABILITIES_PORT0);
	पूर्ण

	वापस 0;

fail:
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d len=%d\n",
		  __func__, rc, (पूर्णांक)outlen);

	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_log_ctrl(काष्ठा efx_nic *efx, bool evq, bool uart, u32 dest_evq)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_LOG_CTRL_IN_LEN);
	u32 dest = 0;
	पूर्णांक rc;

	अगर (uart)
		dest |= MC_CMD_LOG_CTRL_IN_LOG_DEST_UART;
	अगर (evq)
		dest |= MC_CMD_LOG_CTRL_IN_LOG_DEST_EVQ;

	MCDI_SET_DWORD(inbuf, LOG_CTRL_IN_LOG_DEST, dest);
	MCDI_SET_DWORD(inbuf, LOG_CTRL_IN_LOG_DEST_EVQ, dest_evq);

	BUILD_BUG_ON(MC_CMD_LOG_CTRL_OUT_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_LOG_CTRL, inbuf, माप(inbuf),
			  शून्य, 0, शून्य);
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_nvram_types(काष्ठा efx_nic *efx, u32 *nvram_types_out)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_NVRAM_TYPES_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_NVRAM_TYPES_IN_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_TYPES, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		जाओ fail;
	अगर (outlen < MC_CMD_NVRAM_TYPES_OUT_LEN) अणु
		rc = -EIO;
		जाओ fail;
	पूर्ण

	*nvram_types_out = MCDI_DWORD(outbuf, NVRAM_TYPES_OUT_TYPES);
	वापस 0;

fail:
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n",
		  __func__, rc);
	वापस rc;
पूर्ण

/* This function finds types using the new NVRAM_PARTITIONS mcdi. */
अटल पूर्णांक efx_new_mcdi_nvram_types(काष्ठा efx_nic *efx, u32 *number,
				    u32 *nvram_types)
अणु
	efx_dword_t *outbuf = kzalloc(MC_CMD_NVRAM_PARTITIONS_OUT_LENMAX_MCDI2,
				      GFP_KERNEL);
	माप_प्रकार outlen;
	पूर्णांक rc;

	अगर (!outbuf)
		वापस -ENOMEM;

	BUILD_BUG_ON(MC_CMD_NVRAM_PARTITIONS_IN_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_PARTITIONS, शून्य, 0,
			  outbuf, MC_CMD_NVRAM_PARTITIONS_OUT_LENMAX_MCDI2, &outlen);
	अगर (rc)
		जाओ fail;

	*number = MCDI_DWORD(outbuf, NVRAM_PARTITIONS_OUT_NUM_PARTITIONS);

	स_नकल(nvram_types, MCDI_PTR(outbuf, NVRAM_PARTITIONS_OUT_TYPE_ID),
	       *number * माप(u32));

fail:
	kमुक्त(outbuf);
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_nvram_info(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक type,
			माप_प्रकार *size_out, माप_प्रकार *erase_size_out,
			bool *रक्षित_out)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_NVRAM_INFO_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_NVRAM_INFO_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, NVRAM_INFO_IN_TYPE, type);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_INFO, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		जाओ fail;
	अगर (outlen < MC_CMD_NVRAM_INFO_OUT_LEN) अणु
		rc = -EIO;
		जाओ fail;
	पूर्ण

	*size_out = MCDI_DWORD(outbuf, NVRAM_INFO_OUT_SIZE);
	*erase_size_out = MCDI_DWORD(outbuf, NVRAM_INFO_OUT_ERASESIZE);
	*रक्षित_out = !!(MCDI_DWORD(outbuf, NVRAM_INFO_OUT_FLAGS) &
				(1 << MC_CMD_NVRAM_INFO_OUT_PROTECTED_LBN));
	वापस 0;

fail:
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_mcdi_nvram_test(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक type)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_NVRAM_TEST_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_NVRAM_TEST_OUT_LEN);
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, NVRAM_TEST_IN_TYPE, type);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_TEST, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), शून्य);
	अगर (rc)
		वापस rc;

	चयन (MCDI_DWORD(outbuf, NVRAM_TEST_OUT_RESULT)) अणु
	हाल MC_CMD_NVRAM_TEST_PASS:
	हाल MC_CMD_NVRAM_TEST_NOTSUPP:
		वापस 0;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

/* This function tests nvram partitions using the new mcdi partition lookup scheme */
पूर्णांक efx_new_mcdi_nvram_test_all(काष्ठा efx_nic *efx)
अणु
	u32 *nvram_types = kzalloc(MC_CMD_NVRAM_PARTITIONS_OUT_LENMAX_MCDI2,
				   GFP_KERNEL);
	अचिन्हित पूर्णांक number;
	पूर्णांक rc, i;

	अगर (!nvram_types)
		वापस -ENOMEM;

	rc = efx_new_mcdi_nvram_types(efx, &number, nvram_types);
	अगर (rc)
		जाओ fail;

	/* Require at least one check */
	rc = -EAGAIN;

	क्रम (i = 0; i < number; i++) अणु
		अगर (nvram_types[i] == NVRAM_PARTITION_TYPE_PARTITION_MAP ||
		    nvram_types[i] == NVRAM_PARTITION_TYPE_DYNAMIC_CONFIG)
			जारी;

		rc = efx_mcdi_nvram_test(efx, nvram_types[i]);
		अगर (rc)
			जाओ fail;
	पूर्ण

fail:
	kमुक्त(nvram_types);
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_nvram_test_all(काष्ठा efx_nic *efx)
अणु
	u32 nvram_types;
	अचिन्हित पूर्णांक type;
	पूर्णांक rc;

	rc = efx_mcdi_nvram_types(efx, &nvram_types);
	अगर (rc)
		जाओ fail1;

	type = 0;
	जबतक (nvram_types != 0) अणु
		अगर (nvram_types & 1) अणु
			rc = efx_mcdi_nvram_test(efx, type);
			अगर (rc)
				जाओ fail2;
		पूर्ण
		type++;
		nvram_types >>= 1;
	पूर्ण

	वापस 0;

fail2:
	netअगर_err(efx, hw, efx->net_dev, "%s: failed type=%u\n",
		  __func__, type);
fail1:
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/* Returns 1 अगर an निश्चितion was पढ़ो, 0 अगर no निश्चितion had fired,
 * negative on error.
 */
अटल पूर्णांक efx_mcdi_पढ़ो_निश्चितion(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_GET_ASSERTS_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_ASSERTS_OUT_LEN);
	अचिन्हित पूर्णांक flags, index;
	स्थिर अक्षर *reason;
	माप_प्रकार outlen;
	पूर्णांक retry;
	पूर्णांक rc;

	/* Attempt to पढ़ो any stored निश्चितion state beक्रमe we reboot
	 * the mcfw out of the निश्चितion handler. Retry twice, once
	 * because a boot-समय निश्चितion might cause this command to fail
	 * with EINTR. And once again because GET_ASSERTS can race with
	 * MC_CMD_REBOOT running on the other port. */
	retry = 2;
	करो अणु
		MCDI_SET_DWORD(inbuf, GET_ASSERTS_IN_CLEAR, 1);
		rc = efx_mcdi_rpc_quiet(efx, MC_CMD_GET_ASSERTS,
					inbuf, MC_CMD_GET_ASSERTS_IN_LEN,
					outbuf, माप(outbuf), &outlen);
		अगर (rc == -EPERM)
			वापस 0;
	पूर्ण जबतक ((rc == -EINTR || rc == -EIO) && retry-- > 0);

	अगर (rc) अणु
		efx_mcdi_display_error(efx, MC_CMD_GET_ASSERTS,
				       MC_CMD_GET_ASSERTS_IN_LEN, outbuf,
				       outlen, rc);
		वापस rc;
	पूर्ण
	अगर (outlen < MC_CMD_GET_ASSERTS_OUT_LEN)
		वापस -EIO;

	/* Prपूर्णांक out any recorded निश्चितion state */
	flags = MCDI_DWORD(outbuf, GET_ASSERTS_OUT_GLOBAL_FLAGS);
	अगर (flags == MC_CMD_GET_ASSERTS_FLAGS_NO_FAILS)
		वापस 0;

	reason = (flags == MC_CMD_GET_ASSERTS_FLAGS_SYS_FAIL)
		? "system-level assertion"
		: (flags == MC_CMD_GET_ASSERTS_FLAGS_THR_FAIL)
		? "thread-level assertion"
		: (flags == MC_CMD_GET_ASSERTS_FLAGS_WDOG_FIRED)
		? "watchdog reset"
		: "unknown assertion";
	netअगर_err(efx, hw, efx->net_dev,
		  "MCPU %s at PC = 0x%.8x in thread 0x%.8x\n", reason,
		  MCDI_DWORD(outbuf, GET_ASSERTS_OUT_SAVED_PC_OFFS),
		  MCDI_DWORD(outbuf, GET_ASSERTS_OUT_THREAD_OFFS));

	/* Prपूर्णांक out the रेजिस्टरs */
	क्रम (index = 0;
	     index < MC_CMD_GET_ASSERTS_OUT_GP_REGS_OFFS_NUM;
	     index++)
		netअगर_err(efx, hw, efx->net_dev, "R%.2d (?): 0x%.8x\n",
			  1 + index,
			  MCDI_ARRAY_DWORD(outbuf, GET_ASSERTS_OUT_GP_REGS_OFFS,
					   index));

	वापस 1;
पूर्ण

अटल पूर्णांक efx_mcdi_निकास_निश्चितion(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_REBOOT_IN_LEN);
	पूर्णांक rc;

	/* If the MC is running debug firmware, it might now be
	 * रुकोing क्रम a debugger to attach, but we just want it to
	 * reboot.  We set a flag that makes the command a no-op अगर it
	 * has alपढ़ोy करोne so.
	 * The MCDI will thus वापस either 0 or -EIO.
	 */
	BUILD_BUG_ON(MC_CMD_REBOOT_OUT_LEN != 0);
	MCDI_SET_DWORD(inbuf, REBOOT_IN_FLAGS,
		       MC_CMD_REBOOT_FLAGS_AFTER_ASSERTION);
	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_REBOOT, inbuf, MC_CMD_REBOOT_IN_LEN,
				शून्य, 0, शून्य);
	अगर (rc == -EIO)
		rc = 0;
	अगर (rc)
		efx_mcdi_display_error(efx, MC_CMD_REBOOT, MC_CMD_REBOOT_IN_LEN,
				       शून्य, 0, rc);
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_handle_निश्चितion(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	rc = efx_mcdi_पढ़ो_निश्चितion(efx);
	अगर (rc <= 0)
		वापस rc;

	वापस efx_mcdi_निकास_निश्चितion(efx);
पूर्ण

पूर्णांक efx_mcdi_set_id_led(काष्ठा efx_nic *efx, क्रमागत efx_led_mode mode)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_SET_ID_LED_IN_LEN);

	BUILD_BUG_ON(EFX_LED_OFF != MC_CMD_LED_OFF);
	BUILD_BUG_ON(EFX_LED_ON != MC_CMD_LED_ON);
	BUILD_BUG_ON(EFX_LED_DEFAULT != MC_CMD_LED_DEFAULT);

	BUILD_BUG_ON(MC_CMD_SET_ID_LED_OUT_LEN != 0);

	MCDI_SET_DWORD(inbuf, SET_ID_LED_IN_STATE, mode);

	वापस efx_mcdi_rpc(efx, MC_CMD_SET_ID_LED, inbuf, माप(inbuf), शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक efx_mcdi_reset_func(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_ENTITY_RESET_IN_LEN);
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_ENTITY_RESET_OUT_LEN != 0);
	MCDI_POPULATE_DWORD_1(inbuf, ENTITY_RESET_IN_FLAG,
			      ENTITY_RESET_IN_FUNCTION_RESOURCE_RESET, 1);
	rc = efx_mcdi_rpc(efx, MC_CMD_ENTITY_RESET, inbuf, माप(inbuf),
			  शून्य, 0, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_mcdi_reset_mc(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_REBOOT_IN_LEN);
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_REBOOT_OUT_LEN != 0);
	MCDI_SET_DWORD(inbuf, REBOOT_IN_FLAGS, 0);
	rc = efx_mcdi_rpc(efx, MC_CMD_REBOOT, inbuf, माप(inbuf),
			  शून्य, 0, शून्य);
	/* White is black, and up is करोwn */
	अगर (rc == -EIO)
		वापस 0;
	अगर (rc == 0)
		rc = -EIO;
	वापस rc;
पूर्ण

क्रमागत reset_type efx_mcdi_map_reset_reason(क्रमागत reset_type reason)
अणु
	वापस RESET_TYPE_RECOVER_OR_ALL;
पूर्ण

पूर्णांक efx_mcdi_reset(काष्ठा efx_nic *efx, क्रमागत reset_type method)
अणु
	पूर्णांक rc;

	/* If MCDI is करोwn, we can't handle_निश्चितion */
	अगर (method == RESET_TYPE_MCDI_TIMEOUT) अणु
		rc = pci_reset_function(efx->pci_dev);
		अगर (rc)
			वापस rc;
		/* Re-enable polled MCDI completion */
		अगर (efx->mcdi) अणु
			काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);
			mcdi->mode = MCDI_MODE_POLL;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Recover from a failed निश्चितion pre-reset */
	rc = efx_mcdi_handle_निश्चितion(efx);
	अगर (rc)
		वापस rc;

	अगर (method == RESET_TYPE_DATAPATH)
		वापस 0;
	अन्यथा अगर (method == RESET_TYPE_WORLD)
		वापस efx_mcdi_reset_mc(efx);
	अन्यथा
		वापस efx_mcdi_reset_func(efx);
पूर्ण

अटल पूर्णांक efx_mcdi_wol_filter_set(काष्ठा efx_nic *efx, u32 type,
				   स्थिर u8 *mac, पूर्णांक *id_out)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_WOL_FILTER_SET_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_WOL_FILTER_SET_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, WOL_FILTER_SET_IN_WOL_TYPE, type);
	MCDI_SET_DWORD(inbuf, WOL_FILTER_SET_IN_FILTER_MODE,
		       MC_CMD_FILTER_MODE_SIMPLE);
	ether_addr_copy(MCDI_PTR(inbuf, WOL_FILTER_SET_IN_MAGIC_MAC), mac);

	rc = efx_mcdi_rpc(efx, MC_CMD_WOL_FILTER_SET, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		जाओ fail;

	अगर (outlen < MC_CMD_WOL_FILTER_SET_OUT_LEN) अणु
		rc = -EIO;
		जाओ fail;
	पूर्ण

	*id_out = (पूर्णांक)MCDI_DWORD(outbuf, WOL_FILTER_SET_OUT_FILTER_ID);

	वापस 0;

fail:
	*id_out = -1;
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
	वापस rc;

पूर्ण


पूर्णांक
efx_mcdi_wol_filter_set_magic(काष्ठा efx_nic *efx,  स्थिर u8 *mac, पूर्णांक *id_out)
अणु
	वापस efx_mcdi_wol_filter_set(efx, MC_CMD_WOL_TYPE_MAGIC, mac, id_out);
पूर्ण


पूर्णांक efx_mcdi_wol_filter_get_magic(काष्ठा efx_nic *efx, पूर्णांक *id_out)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_WOL_FILTER_GET_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	rc = efx_mcdi_rpc(efx, MC_CMD_WOL_FILTER_GET, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		जाओ fail;

	अगर (outlen < MC_CMD_WOL_FILTER_GET_OUT_LEN) अणु
		rc = -EIO;
		जाओ fail;
	पूर्ण

	*id_out = (पूर्णांक)MCDI_DWORD(outbuf, WOL_FILTER_GET_OUT_FILTER_ID);

	वापस 0;

fail:
	*id_out = -1;
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण


पूर्णांक efx_mcdi_wol_filter_हटाओ(काष्ठा efx_nic *efx, पूर्णांक id)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_WOL_FILTER_REMOVE_IN_LEN);
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, WOL_FILTER_REMOVE_IN_FILTER_ID, (u32)id);

	rc = efx_mcdi_rpc(efx, MC_CMD_WOL_FILTER_REMOVE, inbuf, माप(inbuf),
			  शून्य, 0, शून्य);
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_flush_rxqs(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;
	काष्ठा efx_rx_queue *rx_queue;
	MCDI_DECLARE_BUF(inbuf,
			 MC_CMD_FLUSH_RX_QUEUES_IN_LEN(EFX_MAX_CHANNELS));
	पूर्णांक rc, count;

	BUILD_BUG_ON(EFX_MAX_CHANNELS >
		     MC_CMD_FLUSH_RX_QUEUES_IN_QID_OFST_MAXNUM);

	count = 0;
	efx_क्रम_each_channel(channel, efx) अणु
		efx_क्रम_each_channel_rx_queue(rx_queue, channel) अणु
			अगर (rx_queue->flush_pending) अणु
				rx_queue->flush_pending = false;
				atomic_dec(&efx->rxq_flush_pending);
				MCDI_SET_ARRAY_DWORD(
					inbuf, FLUSH_RX_QUEUES_IN_QID_OFST,
					count, efx_rx_queue_index(rx_queue));
				count++;
			पूर्ण
		पूर्ण
	पूर्ण

	rc = efx_mcdi_rpc(efx, MC_CMD_FLUSH_RX_QUEUES, inbuf,
			  MC_CMD_FLUSH_RX_QUEUES_IN_LEN(count), शून्य, 0, शून्य);
	WARN_ON(rc < 0);

	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_wol_filter_reset(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	rc = efx_mcdi_rpc(efx, MC_CMD_WOL_FILTER_RESET, शून्य, 0, शून्य, 0, शून्य);
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_set_workaround(काष्ठा efx_nic *efx, u32 type, bool enabled,
			    अचिन्हित पूर्णांक *flags)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_WORKAROUND_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_WORKAROUND_EXT_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_WORKAROUND_OUT_LEN != 0);
	MCDI_SET_DWORD(inbuf, WORKAROUND_IN_TYPE, type);
	MCDI_SET_DWORD(inbuf, WORKAROUND_IN_ENABLED, enabled);
	rc = efx_mcdi_rpc(efx, MC_CMD_WORKAROUND, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;

	अगर (!flags)
		वापस 0;

	अगर (outlen >= MC_CMD_WORKAROUND_EXT_OUT_LEN)
		*flags = MCDI_DWORD(outbuf, WORKAROUND_EXT_OUT_FLAGS);
	अन्यथा
		*flags = 0;

	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_get_workarounds(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक *impl_out,
			     अचिन्हित पूर्णांक *enabled_out)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_WORKAROUNDS_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_WORKAROUNDS, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		जाओ fail;

	अगर (outlen < MC_CMD_GET_WORKAROUNDS_OUT_LEN) अणु
		rc = -EIO;
		जाओ fail;
	पूर्ण

	अगर (impl_out)
		*impl_out = MCDI_DWORD(outbuf, GET_WORKAROUNDS_OUT_IMPLEMENTED);

	अगर (enabled_out)
		*enabled_out = MCDI_DWORD(outbuf, GET_WORKAROUNDS_OUT_ENABLED);

	वापस 0;

fail:
	/* Older firmware lacks GET_WORKAROUNDS and this isn't especially
	 * terrअगरying.  The call site will have to deal with it though.
	 */
	netअगर_cond_dbg(efx, hw, efx->net_dev, rc == -ENOSYS, err,
		       "%s: failed rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_SFC_MTD

#घोषणा EFX_MCDI_NVRAM_LEN_MAX 128

अटल पूर्णांक efx_mcdi_nvram_update_start(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक type)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_NVRAM_UPDATE_START_V2_IN_LEN);
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, NVRAM_UPDATE_START_IN_TYPE, type);
	MCDI_POPULATE_DWORD_1(inbuf, NVRAM_UPDATE_START_V2_IN_FLAGS,
			      NVRAM_UPDATE_START_V2_IN_FLAG_REPORT_VERIFY_RESULT,
			      1);

	BUILD_BUG_ON(MC_CMD_NVRAM_UPDATE_START_OUT_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_UPDATE_START, inbuf, माप(inbuf),
			  शून्य, 0, शून्य);

	वापस rc;
पूर्ण

अटल पूर्णांक efx_mcdi_nvram_पढ़ो(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक type,
			       loff_t offset, u8 *buffer, माप_प्रकार length)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_NVRAM_READ_IN_V2_LEN);
	MCDI_DECLARE_BUF(outbuf,
			 MC_CMD_NVRAM_READ_OUT_LEN(EFX_MCDI_NVRAM_LEN_MAX));
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, NVRAM_READ_IN_TYPE, type);
	MCDI_SET_DWORD(inbuf, NVRAM_READ_IN_OFFSET, offset);
	MCDI_SET_DWORD(inbuf, NVRAM_READ_IN_LENGTH, length);
	MCDI_SET_DWORD(inbuf, NVRAM_READ_IN_V2_MODE,
		       MC_CMD_NVRAM_READ_IN_V2_DEFAULT);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_READ, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;

	स_नकल(buffer, MCDI_PTR(outbuf, NVRAM_READ_OUT_READ_BUFFER), length);
	वापस 0;
पूर्ण

अटल पूर्णांक efx_mcdi_nvram_ग_लिखो(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक type,
				loff_t offset, स्थिर u8 *buffer, माप_प्रकार length)
अणु
	MCDI_DECLARE_BUF(inbuf,
			 MC_CMD_NVRAM_WRITE_IN_LEN(EFX_MCDI_NVRAM_LEN_MAX));
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, NVRAM_WRITE_IN_TYPE, type);
	MCDI_SET_DWORD(inbuf, NVRAM_WRITE_IN_OFFSET, offset);
	MCDI_SET_DWORD(inbuf, NVRAM_WRITE_IN_LENGTH, length);
	स_नकल(MCDI_PTR(inbuf, NVRAM_WRITE_IN_WRITE_BUFFER), buffer, length);

	BUILD_BUG_ON(MC_CMD_NVRAM_WRITE_OUT_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_WRITE, inbuf,
			  ALIGN(MC_CMD_NVRAM_WRITE_IN_LEN(length), 4),
			  शून्य, 0, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_mcdi_nvram_erase(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक type,
				loff_t offset, माप_प्रकार length)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_NVRAM_ERASE_IN_LEN);
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, NVRAM_ERASE_IN_TYPE, type);
	MCDI_SET_DWORD(inbuf, NVRAM_ERASE_IN_OFFSET, offset);
	MCDI_SET_DWORD(inbuf, NVRAM_ERASE_IN_LENGTH, length);

	BUILD_BUG_ON(MC_CMD_NVRAM_ERASE_OUT_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_ERASE, inbuf, माप(inbuf),
			  शून्य, 0, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_mcdi_nvram_update_finish(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक type)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_NVRAM_UPDATE_FINISH_V2_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_NVRAM_UPDATE_FINISH_V2_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc, rc2;

	MCDI_SET_DWORD(inbuf, NVRAM_UPDATE_FINISH_IN_TYPE, type);
	/* Always set this flag. Old firmware ignores it */
	MCDI_POPULATE_DWORD_1(inbuf, NVRAM_UPDATE_FINISH_V2_IN_FLAGS,
			      NVRAM_UPDATE_FINISH_V2_IN_FLAG_REPORT_VERIFY_RESULT,
			      1);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_UPDATE_FINISH, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (!rc && outlen >= MC_CMD_NVRAM_UPDATE_FINISH_V2_OUT_LEN) अणु
		rc2 = MCDI_DWORD(outbuf, NVRAM_UPDATE_FINISH_V2_OUT_RESULT_CODE);
		अगर (rc2 != MC_CMD_NVRAM_VERIFY_RC_SUCCESS)
			netअगर_err(efx, drv, efx->net_dev,
				  "NVRAM update failed verification with code 0x%x\n",
				  rc2);
		चयन (rc2) अणु
		हाल MC_CMD_NVRAM_VERIFY_RC_SUCCESS:
			अवरोध;
		हाल MC_CMD_NVRAM_VERIFY_RC_CMS_CHECK_FAILED:
		हाल MC_CMD_NVRAM_VERIFY_RC_MESSAGE_DIGEST_CHECK_FAILED:
		हाल MC_CMD_NVRAM_VERIFY_RC_SIGNATURE_CHECK_FAILED:
		हाल MC_CMD_NVRAM_VERIFY_RC_TRUSTED_APPROVERS_CHECK_FAILED:
		हाल MC_CMD_NVRAM_VERIFY_RC_SIGNATURE_CHAIN_CHECK_FAILED:
			rc = -EIO;
			अवरोध;
		हाल MC_CMD_NVRAM_VERIFY_RC_INVALID_CMS_FORMAT:
		हाल MC_CMD_NVRAM_VERIFY_RC_BAD_MESSAGE_DIGEST:
			rc = -EINVAL;
			अवरोध;
		हाल MC_CMD_NVRAM_VERIFY_RC_NO_VALID_SIGNATURES:
		हाल MC_CMD_NVRAM_VERIFY_RC_NO_TRUSTED_APPROVERS:
		हाल MC_CMD_NVRAM_VERIFY_RC_NO_SIGNATURE_MATCH:
			rc = -EPERM;
			अवरोध;
		शेष:
			netअगर_err(efx, drv, efx->net_dev,
				  "Unknown response to NVRAM_UPDATE_FINISH\n");
			rc = -EIO;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_mtd_पढ़ो(काष्ठा mtd_info *mtd, loff_t start,
		      माप_प्रकार len, माप_प्रकार *retlen, u8 *buffer)
अणु
	काष्ठा efx_mcdi_mtd_partition *part = to_efx_mcdi_mtd_partition(mtd);
	काष्ठा efx_nic *efx = mtd->priv;
	loff_t offset = start;
	loff_t end = min_t(loff_t, start + len, mtd->size);
	माप_प्रकार chunk;
	पूर्णांक rc = 0;

	जबतक (offset < end) अणु
		chunk = min_t(माप_प्रकार, end - offset, EFX_MCDI_NVRAM_LEN_MAX);
		rc = efx_mcdi_nvram_पढ़ो(efx, part->nvram_type, offset,
					 buffer, chunk);
		अगर (rc)
			जाओ out;
		offset += chunk;
		buffer += chunk;
	पूर्ण
out:
	*retlen = offset - start;
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_mtd_erase(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len)
अणु
	काष्ठा efx_mcdi_mtd_partition *part = to_efx_mcdi_mtd_partition(mtd);
	काष्ठा efx_nic *efx = mtd->priv;
	loff_t offset = start & ~((loff_t)(mtd->erasesize - 1));
	loff_t end = min_t(loff_t, start + len, mtd->size);
	माप_प्रकार chunk = part->common.mtd.erasesize;
	पूर्णांक rc = 0;

	अगर (!part->updating) अणु
		rc = efx_mcdi_nvram_update_start(efx, part->nvram_type);
		अगर (rc)
			जाओ out;
		part->updating = true;
	पूर्ण

	/* The MCDI पूर्णांकerface can in fact करो multiple erase blocks at once;
	 * but erasing may be slow, so we make multiple calls here to aव्योम
	 * tripping the MCDI RPC समयout. */
	जबतक (offset < end) अणु
		rc = efx_mcdi_nvram_erase(efx, part->nvram_type, offset,
					  chunk);
		अगर (rc)
			जाओ out;
		offset += chunk;
	पूर्ण
out:
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_mtd_ग_लिखो(काष्ठा mtd_info *mtd, loff_t start,
		       माप_प्रकार len, माप_प्रकार *retlen, स्थिर u8 *buffer)
अणु
	काष्ठा efx_mcdi_mtd_partition *part = to_efx_mcdi_mtd_partition(mtd);
	काष्ठा efx_nic *efx = mtd->priv;
	loff_t offset = start;
	loff_t end = min_t(loff_t, start + len, mtd->size);
	माप_प्रकार chunk;
	पूर्णांक rc = 0;

	अगर (!part->updating) अणु
		rc = efx_mcdi_nvram_update_start(efx, part->nvram_type);
		अगर (rc)
			जाओ out;
		part->updating = true;
	पूर्ण

	जबतक (offset < end) अणु
		chunk = min_t(माप_प्रकार, end - offset, EFX_MCDI_NVRAM_LEN_MAX);
		rc = efx_mcdi_nvram_ग_लिखो(efx, part->nvram_type, offset,
					  buffer, chunk);
		अगर (rc)
			जाओ out;
		offset += chunk;
		buffer += chunk;
	पूर्ण
out:
	*retlen = offset - start;
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_mtd_sync(काष्ठा mtd_info *mtd)
अणु
	काष्ठा efx_mcdi_mtd_partition *part = to_efx_mcdi_mtd_partition(mtd);
	काष्ठा efx_nic *efx = mtd->priv;
	पूर्णांक rc = 0;

	अगर (part->updating) अणु
		part->updating = false;
		rc = efx_mcdi_nvram_update_finish(efx, part->nvram_type);
	पूर्ण

	वापस rc;
पूर्ण

व्योम efx_mcdi_mtd_नाम(काष्ठा efx_mtd_partition *part)
अणु
	काष्ठा efx_mcdi_mtd_partition *mcdi_part =
		container_of(part, काष्ठा efx_mcdi_mtd_partition, common);
	काष्ठा efx_nic *efx = part->mtd.priv;

	snम_लिखो(part->name, माप(part->name), "%s %s:%02x",
		 efx->name, part->type_name, mcdi_part->fw_subtype);
पूर्ण

#पूर्ण_अगर /* CONFIG_SFC_MTD */
