<शैली गुरु>
/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "core.h"
#समावेश "cfg80211.h"
#समावेश "debug.h"

अटल व्योम ath6kl_recovery_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath6kl *ar = container_of(work, काष्ठा ath6kl,
					 fw_recovery.recovery_work);

	ar->state = ATH6KL_STATE_RECOVERY;

	del_समयr_sync(&ar->fw_recovery.hb_समयr);

	ath6kl_init_hw_restart(ar);

	ar->state = ATH6KL_STATE_ON;
	clear_bit(WMI_CTRL_EP_FULL, &ar->flag);

	ar->fw_recovery.err_reason = 0;

	अगर (ar->fw_recovery.hb_poll)
		mod_समयr(&ar->fw_recovery.hb_समयr, jअगरfies +
			  msecs_to_jअगरfies(ar->fw_recovery.hb_poll));
पूर्ण

व्योम ath6kl_recovery_err_notअगरy(काष्ठा ath6kl *ar, क्रमागत ath6kl_fw_err reason)
अणु
	अगर (!ar->fw_recovery.enable)
		वापस;

	ath6kl_dbg(ATH6KL_DBG_RECOVERY, "Fw error detected, reason:%d\n",
		   reason);

	set_bit(reason, &ar->fw_recovery.err_reason);

	अगर (!test_bit(RECOVERY_CLEANUP, &ar->flag) &&
	    ar->state != ATH6KL_STATE_RECOVERY)
		queue_work(ar->ath6kl_wq, &ar->fw_recovery.recovery_work);
पूर्ण

व्योम ath6kl_recovery_hb_event(काष्ठा ath6kl *ar, u32 cookie)
अणु
	अगर (cookie == ar->fw_recovery.seq_num)
		ar->fw_recovery.hb_pending = false;
पूर्ण

अटल व्योम ath6kl_recovery_hb_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ath6kl *ar = from_समयr(ar, t, fw_recovery.hb_समयr);
	पूर्णांक err;

	अगर (test_bit(RECOVERY_CLEANUP, &ar->flag) ||
	    (ar->state == ATH6KL_STATE_RECOVERY))
		वापस;

	अगर (ar->fw_recovery.hb_pending)
		ar->fw_recovery.hb_misscnt++;
	अन्यथा
		ar->fw_recovery.hb_misscnt = 0;

	अगर (ar->fw_recovery.hb_misscnt > ATH6KL_HB_RESP_MISS_THRES) अणु
		ar->fw_recovery.hb_misscnt = 0;
		ar->fw_recovery.seq_num = 0;
		ar->fw_recovery.hb_pending = false;
		ath6kl_recovery_err_notअगरy(ar, ATH6KL_FW_HB_RESP_FAILURE);
		वापस;
	पूर्ण

	ar->fw_recovery.seq_num++;
	ar->fw_recovery.hb_pending = true;

	err = ath6kl_wmi_get_challenge_resp_cmd(ar->wmi,
						ar->fw_recovery.seq_num, 0);
	अगर (err)
		ath6kl_warn("Failed to send hb challenge request, err:%d\n",
			    err);

	mod_समयr(&ar->fw_recovery.hb_समयr, jअगरfies +
		  msecs_to_jअगरfies(ar->fw_recovery.hb_poll));
पूर्ण

व्योम ath6kl_recovery_init(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_fw_recovery *recovery = &ar->fw_recovery;

	clear_bit(RECOVERY_CLEANUP, &ar->flag);
	INIT_WORK(&recovery->recovery_work, ath6kl_recovery_work);
	recovery->seq_num = 0;
	recovery->hb_misscnt = 0;
	ar->fw_recovery.hb_pending = false;
	समयr_setup(&ar->fw_recovery.hb_समयr, ath6kl_recovery_hb_समयr,
		    TIMER_DEFERRABLE);

	अगर (ar->fw_recovery.hb_poll)
		mod_समयr(&ar->fw_recovery.hb_समयr, jअगरfies +
			  msecs_to_jअगरfies(ar->fw_recovery.hb_poll));
पूर्ण

व्योम ath6kl_recovery_cleanup(काष्ठा ath6kl *ar)
अणु
	अगर (!ar->fw_recovery.enable)
		वापस;

	set_bit(RECOVERY_CLEANUP, &ar->flag);

	del_समयr_sync(&ar->fw_recovery.hb_समयr);
	cancel_work_sync(&ar->fw_recovery.recovery_work);
पूर्ण

व्योम ath6kl_recovery_suspend(काष्ठा ath6kl *ar)
अणु
	अगर (!ar->fw_recovery.enable)
		वापस;

	ath6kl_recovery_cleanup(ar);

	अगर (!ar->fw_recovery.err_reason)
		वापस;

	/* Process pending fw error detection */
	ar->fw_recovery.err_reason = 0;
	WARN_ON(ar->state != ATH6KL_STATE_ON);
	ar->state = ATH6KL_STATE_RECOVERY;
	ath6kl_init_hw_restart(ar);
	ar->state = ATH6KL_STATE_ON;
पूर्ण

व्योम ath6kl_recovery_resume(काष्ठा ath6kl *ar)
अणु
	अगर (!ar->fw_recovery.enable)
		वापस;

	clear_bit(RECOVERY_CLEANUP, &ar->flag);

	अगर (!ar->fw_recovery.hb_poll)
		वापस;

	ar->fw_recovery.hb_pending = false;
	ar->fw_recovery.seq_num = 0;
	ar->fw_recovery.hb_misscnt = 0;
	mod_समयr(&ar->fw_recovery.hb_समयr,
		  jअगरfies + msecs_to_jअगरfies(ar->fw_recovery.hb_poll));
पूर्ण
