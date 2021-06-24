<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV OPAL asynchronous completion पूर्णांकerfaces
 *
 * Copyright 2013-2017 IBM Corp.
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/gfp.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/opal.h>

क्रमागत opal_async_token_state अणु
	ASYNC_TOKEN_UNALLOCATED = 0,
	ASYNC_TOKEN_ALLOCATED,
	ASYNC_TOKEN_DISPATCHED,
	ASYNC_TOKEN_ABANDONED,
	ASYNC_TOKEN_COMPLETED
पूर्ण;

काष्ठा opal_async_token अणु
	क्रमागत opal_async_token_state state;
	काष्ठा opal_msg response;
पूर्ण;

अटल DECLARE_WAIT_QUEUE_HEAD(opal_async_रुको);
अटल DEFINE_SPINLOCK(opal_async_comp_lock);
अटल काष्ठा semaphore opal_async_sem;
अटल अचिन्हित पूर्णांक opal_max_async_tokens;
अटल काष्ठा opal_async_token *opal_async_tokens;

अटल पूर्णांक __opal_async_get_token(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, token = -EBUSY;

	spin_lock_irqsave(&opal_async_comp_lock, flags);

	क्रम (i = 0; i < opal_max_async_tokens; i++) अणु
		अगर (opal_async_tokens[i].state == ASYNC_TOKEN_UNALLOCATED) अणु
			opal_async_tokens[i].state = ASYNC_TOKEN_ALLOCATED;
			token = i;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&opal_async_comp_lock, flags);
	वापस token;
पूर्ण

/*
 * Note: If the वापसed token is used in an opal call and opal वापसs
 * OPAL_ASYNC_COMPLETION you MUST call one of opal_async_रुको_response() or
 * opal_async_रुको_response_पूर्णांकerruptible() at least once beक्रमe calling another
 * opal_async_* function
 */
पूर्णांक opal_async_get_token_पूर्णांकerruptible(व्योम)
अणु
	पूर्णांक token;

	/* Wait until a token is available */
	अगर (करोwn_पूर्णांकerruptible(&opal_async_sem))
		वापस -ERESTARTSYS;

	token = __opal_async_get_token();
	अगर (token < 0)
		up(&opal_async_sem);

	वापस token;
पूर्ण
EXPORT_SYMBOL_GPL(opal_async_get_token_पूर्णांकerruptible);

अटल पूर्णांक __opal_async_release_token(पूर्णांक token)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (token < 0 || token >= opal_max_async_tokens) अणु
		pr_err("%s: Passed token is out of range, token %d\n",
				__func__, token);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&opal_async_comp_lock, flags);
	चयन (opal_async_tokens[token].state) अणु
	हाल ASYNC_TOKEN_COMPLETED:
	हाल ASYNC_TOKEN_ALLOCATED:
		opal_async_tokens[token].state = ASYNC_TOKEN_UNALLOCATED;
		rc = 0;
		अवरोध;
	/*
	 * DISPATCHED and ABANDONED tokens must रुको क्रम OPAL to respond.
	 * Mark a DISPATCHED token as ABANDONED so that the response handling
	 * code knows no one cares and that it can मुक्त it then.
	 */
	हाल ASYNC_TOKEN_DISPATCHED:
		opal_async_tokens[token].state = ASYNC_TOKEN_ABANDONED;
		fallthrough;
	शेष:
		rc = 1;
	पूर्ण
	spin_unlock_irqrestore(&opal_async_comp_lock, flags);

	वापस rc;
पूर्ण

पूर्णांक opal_async_release_token(पूर्णांक token)
अणु
	पूर्णांक ret;

	ret = __opal_async_release_token(token);
	अगर (!ret)
		up(&opal_async_sem);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(opal_async_release_token);

पूर्णांक opal_async_रुको_response(uपूर्णांक64_t token, काष्ठा opal_msg *msg)
अणु
	अगर (token >= opal_max_async_tokens) अणु
		pr_err("%s: Invalid token passed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!msg) अणु
		pr_err("%s: Invalid message pointer passed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * There is no need to mark the token as dispatched, रुको_event()
	 * will block until the token completes.
	 *
	 * Wakeup the poller beक्रमe we रुको क्रम events to speed things
	 * up on platक्रमms or simulators where the पूर्णांकerrupts aren't
	 * functional.
	 */
	opal_wake_poller();
	रुको_event(opal_async_रुको, opal_async_tokens[token].state
			== ASYNC_TOKEN_COMPLETED);
	स_नकल(msg, &opal_async_tokens[token].response, माप(*msg));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(opal_async_रुको_response);

पूर्णांक opal_async_रुको_response_पूर्णांकerruptible(uपूर्णांक64_t token, काष्ठा opal_msg *msg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (token >= opal_max_async_tokens) अणु
		pr_err("%s: Invalid token passed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!msg) अणु
		pr_err("%s: Invalid message pointer passed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The first समय this माला_लो called we mark the token as DISPATCHED
	 * so that अगर रुको_event_पूर्णांकerruptible() वापसs not zero and the
	 * caller मुक्तs the token, we know not to actually मुक्त the token
	 * until the response comes.
	 *
	 * Only change अगर the token is ALLOCATED - it may have been
	 * completed even beक्रमe the caller माला_लो around to calling this
	 * the first समय.
	 *
	 * There is also a dirty great comment at the token allocation
	 * function that अगर the opal call वापसs OPAL_ASYNC_COMPLETION to
	 * the caller then the caller *must* call this or the not
	 * पूर्णांकerruptible version beक्रमe करोing anything अन्यथा with the
	 * token.
	 */
	अगर (opal_async_tokens[token].state == ASYNC_TOKEN_ALLOCATED) अणु
		spin_lock_irqsave(&opal_async_comp_lock, flags);
		अगर (opal_async_tokens[token].state == ASYNC_TOKEN_ALLOCATED)
			opal_async_tokens[token].state = ASYNC_TOKEN_DISPATCHED;
		spin_unlock_irqrestore(&opal_async_comp_lock, flags);
	पूर्ण

	/*
	 * Wakeup the poller beक्रमe we रुको क्रम events to speed things
	 * up on platक्रमms or simulators where the पूर्णांकerrupts aren't
	 * functional.
	 */
	opal_wake_poller();
	ret = रुको_event_पूर्णांकerruptible(opal_async_रुको,
			opal_async_tokens[token].state ==
			ASYNC_TOKEN_COMPLETED);
	अगर (!ret)
		स_नकल(msg, &opal_async_tokens[token].response, माप(*msg));

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(opal_async_रुको_response_पूर्णांकerruptible);

/* Called from पूर्णांकerrupt context */
अटल पूर्णांक opal_async_comp_event(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ msg_type, व्योम *msg)
अणु
	काष्ठा opal_msg *comp_msg = msg;
	क्रमागत opal_async_token_state state;
	अचिन्हित दीर्घ flags;
	uपूर्णांक64_t token;

	अगर (msg_type != OPAL_MSG_ASYNC_COMP)
		वापस 0;

	token = be64_to_cpu(comp_msg->params[0]);
	spin_lock_irqsave(&opal_async_comp_lock, flags);
	state = opal_async_tokens[token].state;
	opal_async_tokens[token].state = ASYNC_TOKEN_COMPLETED;
	spin_unlock_irqrestore(&opal_async_comp_lock, flags);

	अगर (state == ASYNC_TOKEN_ABANDONED) अणु
		/* Free the token, no one अन्यथा will */
		opal_async_release_token(token);
		वापस 0;
	पूर्ण
	स_नकल(&opal_async_tokens[token].response, comp_msg, माप(*comp_msg));
	wake_up(&opal_async_रुको);

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block opal_async_comp_nb = अणु
		.notअगरier_call	= opal_async_comp_event,
		.next		= शून्य,
		.priority	= 0,
पूर्ण;

पूर्णांक __init opal_async_comp_init(व्योम)
अणु
	काष्ठा device_node *opal_node;
	स्थिर __be32 *async;
	पूर्णांक err;

	opal_node = of_find_node_by_path("/ibm,opal");
	अगर (!opal_node) अणु
		pr_err("%s: Opal node not found\n", __func__);
		err = -ENOENT;
		जाओ out;
	पूर्ण

	async = of_get_property(opal_node, "opal-msg-async-num", शून्य);
	अगर (!async) अणु
		pr_err("%s: %pOF has no opal-msg-async-num\n",
				__func__, opal_node);
		err = -ENOENT;
		जाओ out_opal_node;
	पूर्ण

	opal_max_async_tokens = be32_to_cpup(async);
	opal_async_tokens = kसुस्मृति(opal_max_async_tokens,
			माप(*opal_async_tokens), GFP_KERNEL);
	अगर (!opal_async_tokens) अणु
		err = -ENOMEM;
		जाओ out_opal_node;
	पूर्ण

	err = opal_message_notअगरier_रेजिस्टर(OPAL_MSG_ASYNC_COMP,
			&opal_async_comp_nb);
	अगर (err) अणु
		pr_err("%s: Can't register OPAL event notifier (%d)\n",
				__func__, err);
		kमुक्त(opal_async_tokens);
		जाओ out_opal_node;
	पूर्ण

	sema_init(&opal_async_sem, opal_max_async_tokens);

out_opal_node:
	of_node_put(opal_node);
out:
	वापस err;
पूर्ण
