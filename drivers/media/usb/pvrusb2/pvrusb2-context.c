<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */

#समावेश "pvrusb2-context.h"
#समावेश "pvrusb2-io.h"
#समावेश "pvrusb2-ioread.h"
#समावेश "pvrusb2-hdw.h"
#समावेश "pvrusb2-debug.h"
#समावेश <linux/रुको.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

अटल काष्ठा pvr2_context *pvr2_context_exist_first;
अटल काष्ठा pvr2_context *pvr2_context_exist_last;
अटल काष्ठा pvr2_context *pvr2_context_notअगरy_first;
अटल काष्ठा pvr2_context *pvr2_context_notअगरy_last;
अटल DEFINE_MUTEX(pvr2_context_mutex);
अटल DECLARE_WAIT_QUEUE_HEAD(pvr2_context_sync_data);
अटल DECLARE_WAIT_QUEUE_HEAD(pvr2_context_cleanup_data);
अटल पूर्णांक pvr2_context_cleanup_flag;
अटल पूर्णांक pvr2_context_cleaned_flag;
अटल काष्ठा task_काष्ठा *pvr2_context_thपढ़ो_ptr;


अटल व्योम pvr2_context_set_notअगरy(काष्ठा pvr2_context *mp, पूर्णांक fl)
अणु
	पूर्णांक संकेत_flag = 0;
	mutex_lock(&pvr2_context_mutex);
	अगर (fl) अणु
		अगर (!mp->notअगरy_flag) अणु
			संकेत_flag = (pvr2_context_notअगरy_first == शून्य);
			mp->notअगरy_prev = pvr2_context_notअगरy_last;
			mp->notअगरy_next = शून्य;
			pvr2_context_notअगरy_last = mp;
			अगर (mp->notअगरy_prev) अणु
				mp->notअगरy_prev->notअगरy_next = mp;
			पूर्ण अन्यथा अणु
				pvr2_context_notअगरy_first = mp;
			पूर्ण
			mp->notअगरy_flag = !0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mp->notअगरy_flag) अणु
			mp->notअगरy_flag = 0;
			अगर (mp->notअगरy_next) अणु
				mp->notअगरy_next->notअगरy_prev = mp->notअगरy_prev;
			पूर्ण अन्यथा अणु
				pvr2_context_notअगरy_last = mp->notअगरy_prev;
			पूर्ण
			अगर (mp->notअगरy_prev) अणु
				mp->notअगरy_prev->notअगरy_next = mp->notअगरy_next;
			पूर्ण अन्यथा अणु
				pvr2_context_notअगरy_first = mp->notअगरy_next;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&pvr2_context_mutex);
	अगर (संकेत_flag) wake_up(&pvr2_context_sync_data);
पूर्ण


अटल व्योम pvr2_context_destroy(काष्ठा pvr2_context *mp)
अणु
	pvr2_trace(PVR2_TRACE_CTXT,"pvr2_context %p (destroy)",mp);
	pvr2_hdw_destroy(mp->hdw);
	pvr2_context_set_notअगरy(mp, 0);
	mutex_lock(&pvr2_context_mutex);
	अगर (mp->exist_next) अणु
		mp->exist_next->exist_prev = mp->exist_prev;
	पूर्ण अन्यथा अणु
		pvr2_context_exist_last = mp->exist_prev;
	पूर्ण
	अगर (mp->exist_prev) अणु
		mp->exist_prev->exist_next = mp->exist_next;
	पूर्ण अन्यथा अणु
		pvr2_context_exist_first = mp->exist_next;
	पूर्ण
	अगर (!pvr2_context_exist_first) अणु
		/* Trigger wakeup on control thपढ़ो in हाल it is रुकोing
		   क्रम an निकास condition. */
		wake_up(&pvr2_context_sync_data);
	पूर्ण
	mutex_unlock(&pvr2_context_mutex);
	kमुक्त(mp);
पूर्ण


अटल व्योम pvr2_context_notअगरy(काष्ठा pvr2_context *mp)
अणु
	pvr2_context_set_notअगरy(mp,!0);
पूर्ण


अटल व्योम pvr2_context_check(काष्ठा pvr2_context *mp)
अणु
	काष्ठा pvr2_channel *ch1, *ch2;
	pvr2_trace(PVR2_TRACE_CTXT,
		   "pvr2_context %p (notify)", mp);
	अगर (!mp->initialized_flag && !mp->disconnect_flag) अणु
		mp->initialized_flag = !0;
		pvr2_trace(PVR2_TRACE_CTXT,
			   "pvr2_context %p (initialize)", mp);
		/* Finish hardware initialization */
		अगर (pvr2_hdw_initialize(mp->hdw,
					(व्योम (*)(व्योम *))pvr2_context_notअगरy,
					mp)) अणु
			mp->video_stream.stream =
				pvr2_hdw_get_video_stream(mp->hdw);
			/* Trigger पूर्णांकerface initialization.  By करोing this
			   here initialization runs in our own safe and
			   cozy thपढ़ो context. */
			अगर (mp->setup_func) mp->setup_func(mp);
		पूर्ण अन्यथा अणु
			pvr2_trace(PVR2_TRACE_CTXT,
				   "pvr2_context %p (thread skipping setup)",
				   mp);
			/* Even though initialization did not succeed,
			   we're still going to जारी anyway.  We need
			   to करो this in order to aरुको the expected
			   disconnect (which we will detect in the normal
			   course of operation). */
		पूर्ण
	पूर्ण

	क्रम (ch1 = mp->mc_first; ch1; ch1 = ch2) अणु
		ch2 = ch1->mc_next;
		अगर (ch1->check_func) ch1->check_func(ch1);
	पूर्ण

	अगर (mp->disconnect_flag && !mp->mc_first) अणु
		/* Go away... */
		pvr2_context_destroy(mp);
		वापस;
	पूर्ण
पूर्ण


अटल पूर्णांक pvr2_context_shutok(व्योम)
अणु
	वापस pvr2_context_cleanup_flag && (pvr2_context_exist_first == शून्य);
पूर्ण


अटल पूर्णांक pvr2_context_thपढ़ो_func(व्योम *foo)
अणु
	काष्ठा pvr2_context *mp;

	pvr2_trace(PVR2_TRACE_CTXT,"pvr2_context thread start");

	करो अणु
		जबतक ((mp = pvr2_context_notअगरy_first) != शून्य) अणु
			pvr2_context_set_notअगरy(mp, 0);
			pvr2_context_check(mp);
		पूर्ण
		रुको_event_पूर्णांकerruptible(
			pvr2_context_sync_data,
			((pvr2_context_notअगरy_first != शून्य) ||
			 pvr2_context_shutok()));
	पूर्ण जबतक (!pvr2_context_shutok());

	pvr2_context_cleaned_flag = !0;
	wake_up(&pvr2_context_cleanup_data);

	pvr2_trace(PVR2_TRACE_CTXT,"pvr2_context thread cleaned up");

	रुको_event_पूर्णांकerruptible(
		pvr2_context_sync_data,
		kthपढ़ो_should_stop());

	pvr2_trace(PVR2_TRACE_CTXT,"pvr2_context thread end");

	वापस 0;
पूर्ण


पूर्णांक pvr2_context_global_init(व्योम)
अणु
	pvr2_context_thपढ़ो_ptr = kthपढ़ो_run(pvr2_context_thपढ़ो_func,
					      शून्य,
					      "pvrusb2-context");
	वापस IS_ERR(pvr2_context_thपढ़ो_ptr) ? -ENOMEM : 0;
पूर्ण


व्योम pvr2_context_global_करोne(व्योम)
अणु
	pvr2_context_cleanup_flag = !0;
	wake_up(&pvr2_context_sync_data);
	रुको_event_पूर्णांकerruptible(
		pvr2_context_cleanup_data,
		pvr2_context_cleaned_flag);
	kthपढ़ो_stop(pvr2_context_thपढ़ो_ptr);
पूर्ण


काष्ठा pvr2_context *pvr2_context_create(
	काष्ठा usb_पूर्णांकerface *पूर्णांकf,
	स्थिर काष्ठा usb_device_id *devid,
	व्योम (*setup_func)(काष्ठा pvr2_context *))
अणु
	काष्ठा pvr2_context *mp = शून्य;
	mp = kzalloc(माप(*mp),GFP_KERNEL);
	अगर (!mp) जाओ करोne;
	pvr2_trace(PVR2_TRACE_CTXT,"pvr2_context %p (create)",mp);
	mp->setup_func = setup_func;
	mutex_init(&mp->mutex);
	mutex_lock(&pvr2_context_mutex);
	mp->exist_prev = pvr2_context_exist_last;
	mp->exist_next = शून्य;
	pvr2_context_exist_last = mp;
	अगर (mp->exist_prev) अणु
		mp->exist_prev->exist_next = mp;
	पूर्ण अन्यथा अणु
		pvr2_context_exist_first = mp;
	पूर्ण
	mutex_unlock(&pvr2_context_mutex);
	mp->hdw = pvr2_hdw_create(पूर्णांकf,devid);
	अगर (!mp->hdw) अणु
		pvr2_context_destroy(mp);
		mp = शून्य;
		जाओ करोne;
	पूर्ण
	pvr2_context_set_notअगरy(mp, !0);
 करोne:
	वापस mp;
पूर्ण


अटल व्योम pvr2_context_reset_input_limits(काष्ठा pvr2_context *mp)
अणु
	अचिन्हित पूर्णांक पंचांगsk,mmsk;
	काष्ठा pvr2_channel *cp;
	काष्ठा pvr2_hdw *hdw = mp->hdw;
	mmsk = pvr2_hdw_get_input_available(hdw);
	पंचांगsk = mmsk;
	क्रम (cp = mp->mc_first; cp; cp = cp->mc_next) अणु
		अगर (!cp->input_mask) जारी;
		पंचांगsk &= cp->input_mask;
	पूर्ण
	pvr2_hdw_set_input_allowed(hdw,mmsk,पंचांगsk);
	pvr2_hdw_commit_ctl(hdw);
पूर्ण


अटल व्योम pvr2_context_enter(काष्ठा pvr2_context *mp)
अणु
	mutex_lock(&mp->mutex);
पूर्ण


अटल व्योम pvr2_context_निकास(काष्ठा pvr2_context *mp)
अणु
	पूर्णांक destroy_flag = 0;
	अगर (!(mp->mc_first || !mp->disconnect_flag)) अणु
		destroy_flag = !0;
	पूर्ण
	mutex_unlock(&mp->mutex);
	अगर (destroy_flag) pvr2_context_notअगरy(mp);
पूर्ण


व्योम pvr2_context_disconnect(काष्ठा pvr2_context *mp)
अणु
	pvr2_hdw_disconnect(mp->hdw);
	mp->disconnect_flag = !0;
	pvr2_context_notअगरy(mp);
पूर्ण


व्योम pvr2_channel_init(काष्ठा pvr2_channel *cp,काष्ठा pvr2_context *mp)
अणु
	pvr2_context_enter(mp);
	cp->hdw = mp->hdw;
	cp->mc_head = mp;
	cp->mc_next = शून्य;
	cp->mc_prev = mp->mc_last;
	अगर (mp->mc_last) अणु
		mp->mc_last->mc_next = cp;
	पूर्ण अन्यथा अणु
		mp->mc_first = cp;
	पूर्ण
	mp->mc_last = cp;
	pvr2_context_निकास(mp);
पूर्ण


अटल व्योम pvr2_channel_disclaim_stream(काष्ठा pvr2_channel *cp)
अणु
	अगर (!cp->stream) वापस;
	pvr2_stream_समाप्त(cp->stream->stream);
	cp->stream->user = शून्य;
	cp->stream = शून्य;
पूर्ण


व्योम pvr2_channel_करोne(काष्ठा pvr2_channel *cp)
अणु
	काष्ठा pvr2_context *mp = cp->mc_head;
	pvr2_context_enter(mp);
	cp->input_mask = 0;
	pvr2_channel_disclaim_stream(cp);
	pvr2_context_reset_input_limits(mp);
	अगर (cp->mc_next) अणु
		cp->mc_next->mc_prev = cp->mc_prev;
	पूर्ण अन्यथा अणु
		mp->mc_last = cp->mc_prev;
	पूर्ण
	अगर (cp->mc_prev) अणु
		cp->mc_prev->mc_next = cp->mc_next;
	पूर्ण अन्यथा अणु
		mp->mc_first = cp->mc_next;
	पूर्ण
	cp->hdw = शून्य;
	pvr2_context_निकास(mp);
पूर्ण


पूर्णांक pvr2_channel_limit_inमाला_दो(काष्ठा pvr2_channel *cp,अचिन्हित पूर्णांक cmsk)
अणु
	अचिन्हित पूर्णांक पंचांगsk,mmsk;
	पूर्णांक ret = 0;
	काष्ठा pvr2_channel *p2;
	काष्ठा pvr2_hdw *hdw = cp->hdw;

	mmsk = pvr2_hdw_get_input_available(hdw);
	cmsk &= mmsk;
	अगर (cmsk == cp->input_mask) अणु
		/* No change; nothing to करो */
		वापस 0;
	पूर्ण

	pvr2_context_enter(cp->mc_head);
	करो अणु
		अगर (!cmsk) अणु
			cp->input_mask = 0;
			pvr2_context_reset_input_limits(cp->mc_head);
			अवरोध;
		पूर्ण
		पंचांगsk = mmsk;
		क्रम (p2 = cp->mc_head->mc_first; p2; p2 = p2->mc_next) अणु
			अगर (p2 == cp) जारी;
			अगर (!p2->input_mask) जारी;
			पंचांगsk &= p2->input_mask;
		पूर्ण
		अगर (!(पंचांगsk & cmsk)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण
		पंचांगsk &= cmsk;
		अगर ((ret = pvr2_hdw_set_input_allowed(hdw,mmsk,पंचांगsk)) != 0) अणु
			/* Internal failure changing allowed list; probably
			   should not happen, but react अगर it करोes. */
			अवरोध;
		पूर्ण
		cp->input_mask = cmsk;
		pvr2_hdw_commit_ctl(hdw);
	पूर्ण जबतक (0);
	pvr2_context_निकास(cp->mc_head);
	वापस ret;
पूर्ण


अचिन्हित पूर्णांक pvr2_channel_get_limited_inमाला_दो(काष्ठा pvr2_channel *cp)
अणु
	वापस cp->input_mask;
पूर्ण


पूर्णांक pvr2_channel_claim_stream(काष्ठा pvr2_channel *cp,
			      काष्ठा pvr2_context_stream *sp)
अणु
	पूर्णांक code = 0;
	pvr2_context_enter(cp->mc_head); करो अणु
		अगर (sp == cp->stream) अवरोध;
		अगर (sp && sp->user) अणु
			code = -EBUSY;
			अवरोध;
		पूर्ण
		pvr2_channel_disclaim_stream(cp);
		अगर (!sp) अवरोध;
		sp->user = cp;
		cp->stream = sp;
	पूर्ण जबतक (0);
	pvr2_context_निकास(cp->mc_head);
	वापस code;
पूर्ण


// This is the marker क्रम the real beginning of a legitimate mpeg2 stream.
अटल अक्षर stream_sync_key[] = अणु
	0x00, 0x00, 0x01, 0xba,
पूर्ण;

काष्ठा pvr2_ioपढ़ो *pvr2_channel_create_mpeg_stream(
	काष्ठा pvr2_context_stream *sp)
अणु
	काष्ठा pvr2_ioपढ़ो *cp;
	cp = pvr2_ioपढ़ो_create();
	अगर (!cp) वापस शून्य;
	pvr2_ioपढ़ो_setup(cp,sp->stream);
	pvr2_ioपढ़ो_set_sync_key(cp,stream_sync_key,माप(stream_sync_key));
	वापस cp;
पूर्ण
