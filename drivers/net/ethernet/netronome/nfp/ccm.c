<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2016-2019 Netronome Systems, Inc. */

#समावेश <linux/bitops.h>

#समावेश "ccm.h"
#समावेश "nfp_app.h"
#समावेश "nfp_net.h"

#घोषणा ccm_warn(app, msg...)	nn_dp_warn(&(app)->ctrl->dp, msg)

#घोषणा NFP_CCM_TAG_ALLOC_SPAN	(U16_MAX / 4)

अटल bool nfp_ccm_all_tags_busy(काष्ठा nfp_ccm *ccm)
अणु
	u16 used_tags;

	used_tags = ccm->tag_alloc_next - ccm->tag_alloc_last;

	वापस used_tags > NFP_CCM_TAG_ALLOC_SPAN;
पूर्ण

अटल पूर्णांक nfp_ccm_alloc_tag(काष्ठा nfp_ccm *ccm)
अणु
	/* CCM is क्रम FW communication which is request-reply.  To make sure
	 * we करोn't reuse the message ID too early after समयout - limit the
	 * number of requests in flight.
	 */
	अगर (unlikely(nfp_ccm_all_tags_busy(ccm))) अणु
		ccm_warn(ccm->app, "all FW request contexts busy!\n");
		वापस -EAGAIN;
	पूर्ण

	WARN_ON(__test_and_set_bit(ccm->tag_alloc_next, ccm->tag_allocator));
	वापस ccm->tag_alloc_next++;
पूर्ण

अटल व्योम nfp_ccm_मुक्त_tag(काष्ठा nfp_ccm *ccm, u16 tag)
अणु
	WARN_ON(!__test_and_clear_bit(tag, ccm->tag_allocator));

	जबतक (!test_bit(ccm->tag_alloc_last, ccm->tag_allocator) &&
	       ccm->tag_alloc_last != ccm->tag_alloc_next)
		ccm->tag_alloc_last++;
पूर्ण

अटल काष्ठा sk_buff *__nfp_ccm_reply(काष्ठा nfp_ccm *ccm, u16 tag)
अणु
	अचिन्हित पूर्णांक msg_tag;
	काष्ठा sk_buff *skb;

	skb_queue_walk(&ccm->replies, skb) अणु
		msg_tag = nfp_ccm_get_tag(skb);
		अगर (msg_tag == tag) अणु
			nfp_ccm_मुक्त_tag(ccm, tag);
			__skb_unlink(skb, &ccm->replies);
			वापस skb;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *
nfp_ccm_reply(काष्ठा nfp_ccm *ccm, काष्ठा nfp_app *app, u16 tag)
अणु
	काष्ठा sk_buff *skb;

	nfp_ctrl_lock(app->ctrl);
	skb = __nfp_ccm_reply(ccm, tag);
	nfp_ctrl_unlock(app->ctrl);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
nfp_ccm_reply_drop_tag(काष्ठा nfp_ccm *ccm, काष्ठा nfp_app *app, u16 tag)
अणु
	काष्ठा sk_buff *skb;

	nfp_ctrl_lock(app->ctrl);
	skb = __nfp_ccm_reply(ccm, tag);
	अगर (!skb)
		nfp_ccm_मुक्त_tag(ccm, tag);
	nfp_ctrl_unlock(app->ctrl);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
nfp_ccm_रुको_reply(काष्ठा nfp_ccm *ccm, काष्ठा nfp_app *app,
		   क्रमागत nfp_ccm_type type, पूर्णांक tag)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i, err;

	क्रम (i = 0; i < 50; i++) अणु
		udelay(4);
		skb = nfp_ccm_reply(ccm, app, tag);
		अगर (skb)
			वापस skb;
	पूर्ण

	err = रुको_event_पूर्णांकerruptible_समयout(ccm->wq,
					       skb = nfp_ccm_reply(ccm, app,
								   tag),
					       msecs_to_jअगरfies(5000));
	/* We didn't get a response - try last समय and atomically drop
	 * the tag even अगर no response is matched.
	 */
	अगर (!skb)
		skb = nfp_ccm_reply_drop_tag(ccm, app, tag);
	अगर (err < 0) अणु
		ccm_warn(app, "%s waiting for response to 0x%02x: %d\n",
			 err == ERESTARTSYS ? "interrupted" : "error",
			 type, err);
		वापस ERR_PTR(err);
	पूर्ण
	अगर (!skb) अणु
		ccm_warn(app, "timeout waiting for response to 0x%02x\n", type);
		वापस ERR_PTR(-ETIMEDOUT);
	पूर्ण

	वापस skb;
पूर्ण

काष्ठा sk_buff *
nfp_ccm_communicate(काष्ठा nfp_ccm *ccm, काष्ठा sk_buff *skb,
		    क्रमागत nfp_ccm_type type, अचिन्हित पूर्णांक reply_size)
अणु
	काष्ठा nfp_app *app = ccm->app;
	काष्ठा nfp_ccm_hdr *hdr;
	पूर्णांक reply_type, tag;

	nfp_ctrl_lock(app->ctrl);
	tag = nfp_ccm_alloc_tag(ccm);
	अगर (tag < 0) अणु
		nfp_ctrl_unlock(app->ctrl);
		dev_kमुक्त_skb_any(skb);
		वापस ERR_PTR(tag);
	पूर्ण

	hdr = (व्योम *)skb->data;
	hdr->ver = NFP_CCM_ABI_VERSION;
	hdr->type = type;
	hdr->tag = cpu_to_be16(tag);

	__nfp_app_ctrl_tx(app, skb);

	nfp_ctrl_unlock(app->ctrl);

	skb = nfp_ccm_रुको_reply(ccm, app, type, tag);
	अगर (IS_ERR(skb))
		वापस skb;

	reply_type = nfp_ccm_get_type(skb);
	अगर (reply_type != __NFP_CCM_REPLY(type)) अणु
		ccm_warn(app, "cmsg drop - wrong type 0x%02x != 0x%02lx!\n",
			 reply_type, __NFP_CCM_REPLY(type));
		जाओ err_मुक्त;
	पूर्ण
	/* 0 reply_size means caller will करो the validation */
	अगर (reply_size && skb->len != reply_size) अणु
		ccm_warn(app, "cmsg drop - type 0x%02x wrong size %d != %d!\n",
			 type, skb->len, reply_size);
		जाओ err_मुक्त;
	पूर्ण

	वापस skb;
err_मुक्त:
	dev_kमुक्त_skb_any(skb);
	वापस ERR_PTR(-EIO);
पूर्ण

व्योम nfp_ccm_rx(काष्ठा nfp_ccm *ccm, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_app *app = ccm->app;
	अचिन्हित पूर्णांक tag;

	अगर (unlikely(skb->len < माप(काष्ठा nfp_ccm_hdr))) अणु
		ccm_warn(app, "cmsg drop - too short %d!\n", skb->len);
		जाओ err_मुक्त;
	पूर्ण

	nfp_ctrl_lock(app->ctrl);

	tag = nfp_ccm_get_tag(skb);
	अगर (unlikely(!test_bit(tag, ccm->tag_allocator))) अणु
		ccm_warn(app, "cmsg drop - no one is waiting for tag %u!\n",
			 tag);
		जाओ err_unlock;
	पूर्ण

	__skb_queue_tail(&ccm->replies, skb);
	wake_up_पूर्णांकerruptible_all(&ccm->wq);

	nfp_ctrl_unlock(app->ctrl);
	वापस;

err_unlock:
	nfp_ctrl_unlock(app->ctrl);
err_मुक्त:
	dev_kमुक्त_skb_any(skb);
पूर्ण

पूर्णांक nfp_ccm_init(काष्ठा nfp_ccm *ccm, काष्ठा nfp_app *app)
अणु
	ccm->app = app;
	skb_queue_head_init(&ccm->replies);
	init_रुकोqueue_head(&ccm->wq);
	वापस 0;
पूर्ण

व्योम nfp_ccm_clean(काष्ठा nfp_ccm *ccm)
अणु
	WARN_ON(!skb_queue_empty(&ccm->replies));
पूर्ण
