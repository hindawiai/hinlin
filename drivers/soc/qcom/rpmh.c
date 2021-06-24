<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

#समावेश <soc/qcom/rpmh.h>

#समावेश "rpmh-internal.h"

#घोषणा RPMH_TIMEOUT_MS			msecs_to_jअगरfies(10000)

#घोषणा DEFINE_RPMH_MSG_ONSTACK(device, s, q, name)	\
	काष्ठा rpmh_request name = अणु			\
		.msg = अणु				\
			.state = s,			\
			.cmds = name.cmd,		\
			.num_cmds = 0,			\
			.रुको_क्रम_compl = true,		\
		पूर्ण,					\
		.cmd = अणु अणु 0 पूर्ण पूर्ण,			\
		.completion = q,			\
		.dev = device,				\
		.needs_मुक्त = false,				\
	पूर्ण

#घोषणा ctrlr_to_drv(ctrlr) container_of(ctrlr, काष्ठा rsc_drv, client)

/**
 * काष्ठा cache_req: the request object क्रम caching
 *
 * @addr: the address of the resource
 * @sleep_val: the sleep vote
 * @wake_val: the wake vote
 * @list: linked list obj
 */
काष्ठा cache_req अणु
	u32 addr;
	u32 sleep_val;
	u32 wake_val;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा batch_cache_req - An entry in our batch catch
 *
 * @list: linked list obj
 * @count: number of messages
 * @rpm_msgs: the messages
 */

काष्ठा batch_cache_req अणु
	काष्ठा list_head list;
	पूर्णांक count;
	काष्ठा rpmh_request rpm_msgs[];
पूर्ण;

अटल काष्ठा rpmh_ctrlr *get_rpmh_ctrlr(स्थिर काष्ठा device *dev)
अणु
	काष्ठा rsc_drv *drv = dev_get_drvdata(dev->parent);

	वापस &drv->client;
पूर्ण

व्योम rpmh_tx_करोne(स्थिर काष्ठा tcs_request *msg, पूर्णांक r)
अणु
	काष्ठा rpmh_request *rpm_msg = container_of(msg, काष्ठा rpmh_request,
						    msg);
	काष्ठा completion *compl = rpm_msg->completion;
	bool मुक्त = rpm_msg->needs_मुक्त;

	rpm_msg->err = r;

	अगर (r)
		dev_err(rpm_msg->dev, "RPMH TX fail in msg addr=%#x, err=%d\n",
			rpm_msg->msg.cmds[0].addr, r);

	अगर (!compl)
		जाओ निकास;

	/* Signal the blocking thपढ़ो we are करोne */
	complete(compl);

निकास:
	अगर (मुक्त)
		kमुक्त(rpm_msg);
पूर्ण

अटल काष्ठा cache_req *__find_req(काष्ठा rpmh_ctrlr *ctrlr, u32 addr)
अणु
	काष्ठा cache_req *p, *req = शून्य;

	list_क्रम_each_entry(p, &ctrlr->cache, list) अणु
		अगर (p->addr == addr) अणु
			req = p;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस req;
पूर्ण

अटल काष्ठा cache_req *cache_rpm_request(काष्ठा rpmh_ctrlr *ctrlr,
					   क्रमागत rpmh_state state,
					   काष्ठा tcs_cmd *cmd)
अणु
	काष्ठा cache_req *req;
	अचिन्हित दीर्घ flags;
	u32 old_sleep_val, old_wake_val;

	spin_lock_irqsave(&ctrlr->cache_lock, flags);
	req = __find_req(ctrlr, cmd->addr);
	अगर (req)
		जाओ existing;

	req = kzalloc(माप(*req), GFP_ATOMIC);
	अगर (!req) अणु
		req = ERR_PTR(-ENOMEM);
		जाओ unlock;
	पूर्ण

	req->addr = cmd->addr;
	req->sleep_val = req->wake_val = अच_पूर्णांक_उच्च;
	list_add_tail(&req->list, &ctrlr->cache);

existing:
	old_sleep_val = req->sleep_val;
	old_wake_val = req->wake_val;

	चयन (state) अणु
	हाल RPMH_ACTIVE_ONLY_STATE:
	हाल RPMH_WAKE_ONLY_STATE:
		req->wake_val = cmd->data;
		अवरोध;
	हाल RPMH_SLEEP_STATE:
		req->sleep_val = cmd->data;
		अवरोध;
	पूर्ण

	ctrlr->dirty |= (req->sleep_val != old_sleep_val ||
			 req->wake_val != old_wake_val) &&
			 req->sleep_val != अच_पूर्णांक_उच्च &&
			 req->wake_val != अच_पूर्णांक_उच्च;

unlock:
	spin_unlock_irqrestore(&ctrlr->cache_lock, flags);

	वापस req;
पूर्ण

/**
 * __rpmh_ग_लिखो: Cache and send the RPMH request
 *
 * @dev: The device making the request
 * @state: Active/Sleep request type
 * @rpm_msg: The data that needs to be sent (cmds).
 *
 * Cache the RPMH request and send अगर the state is ACTIVE_ONLY.
 * SLEEP/WAKE_ONLY requests are not sent to the controller at
 * this समय. Use rpmh_flush() to send them to the controller.
 */
अटल पूर्णांक __rpmh_ग_लिखो(स्थिर काष्ठा device *dev, क्रमागत rpmh_state state,
			काष्ठा rpmh_request *rpm_msg)
अणु
	काष्ठा rpmh_ctrlr *ctrlr = get_rpmh_ctrlr(dev);
	पूर्णांक ret = -EINVAL;
	काष्ठा cache_req *req;
	पूर्णांक i;

	/* Cache the request in our store and link the payload */
	क्रम (i = 0; i < rpm_msg->msg.num_cmds; i++) अणु
		req = cache_rpm_request(ctrlr, state, &rpm_msg->msg.cmds[i]);
		अगर (IS_ERR(req))
			वापस PTR_ERR(req);
	पूर्ण

	अगर (state == RPMH_ACTIVE_ONLY_STATE) अणु
		WARN_ON(irqs_disabled());
		ret = rpmh_rsc_send_data(ctrlr_to_drv(ctrlr), &rpm_msg->msg);
	पूर्ण अन्यथा अणु
		/* Clean up our call by spoofing tx_करोne */
		ret = 0;
		rpmh_tx_करोne(&rpm_msg->msg, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __fill_rpmh_msg(काष्ठा rpmh_request *req, क्रमागत rpmh_state state,
		स्थिर काष्ठा tcs_cmd *cmd, u32 n)
अणु
	अगर (!cmd || !n || n > MAX_RPMH_PAYLOAD)
		वापस -EINVAL;

	स_नकल(req->cmd, cmd, n * माप(*cmd));

	req->msg.state = state;
	req->msg.cmds = req->cmd;
	req->msg.num_cmds = n;

	वापस 0;
पूर्ण

/**
 * rpmh_ग_लिखो_async: Write a set of RPMH commands
 *
 * @dev: The device making the request
 * @state: Active/sleep set
 * @cmd: The payload data
 * @n: The number of elements in payload
 *
 * Write a set of RPMH commands, the order of commands is मुख्यtained
 * and will be sent as a single shot.
 */
पूर्णांक rpmh_ग_लिखो_async(स्थिर काष्ठा device *dev, क्रमागत rpmh_state state,
		     स्थिर काष्ठा tcs_cmd *cmd, u32 n)
अणु
	काष्ठा rpmh_request *rpm_msg;
	पूर्णांक ret;

	rpm_msg = kzalloc(माप(*rpm_msg), GFP_ATOMIC);
	अगर (!rpm_msg)
		वापस -ENOMEM;
	rpm_msg->needs_मुक्त = true;

	ret = __fill_rpmh_msg(rpm_msg, state, cmd, n);
	अगर (ret) अणु
		kमुक्त(rpm_msg);
		वापस ret;
	पूर्ण

	वापस __rpmh_ग_लिखो(dev, state, rpm_msg);
पूर्ण
EXPORT_SYMBOL(rpmh_ग_लिखो_async);

/**
 * rpmh_ग_लिखो: Write a set of RPMH commands and block until response
 *
 * @dev: The device making the request
 * @state: Active/sleep set
 * @cmd: The payload data
 * @n: The number of elements in @cmd
 *
 * May sleep. Do not call from atomic contexts.
 */
पूर्णांक rpmh_ग_लिखो(स्थिर काष्ठा device *dev, क्रमागत rpmh_state state,
	       स्थिर काष्ठा tcs_cmd *cmd, u32 n)
अणु
	DECLARE_COMPLETION_ONSTACK(compl);
	DEFINE_RPMH_MSG_ONSTACK(dev, state, &compl, rpm_msg);
	पूर्णांक ret;

	ret = __fill_rpmh_msg(&rpm_msg, state, cmd, n);
	अगर (ret)
		वापस ret;

	ret = __rpmh_ग_लिखो(dev, state, &rpm_msg);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_completion_समयout(&compl, RPMH_TIMEOUT_MS);
	WARN_ON(!ret);
	वापस (ret > 0) ? 0 : -ETIMEDOUT;
पूर्ण
EXPORT_SYMBOL(rpmh_ग_लिखो);

अटल व्योम cache_batch(काष्ठा rpmh_ctrlr *ctrlr, काष्ठा batch_cache_req *req)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctrlr->cache_lock, flags);
	list_add_tail(&req->list, &ctrlr->batch_cache);
	ctrlr->dirty = true;
	spin_unlock_irqrestore(&ctrlr->cache_lock, flags);
पूर्ण

अटल पूर्णांक flush_batch(काष्ठा rpmh_ctrlr *ctrlr)
अणु
	काष्ठा batch_cache_req *req;
	स्थिर काष्ठा rpmh_request *rpm_msg;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* Send Sleep/Wake requests to the controller, expect no response */
	list_क्रम_each_entry(req, &ctrlr->batch_cache, list) अणु
		क्रम (i = 0; i < req->count; i++) अणु
			rpm_msg = req->rpm_msgs + i;
			ret = rpmh_rsc_ग_लिखो_ctrl_data(ctrlr_to_drv(ctrlr),
						       &rpm_msg->msg);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * rpmh_ग_लिखो_batch: Write multiple sets of RPMH commands and रुको क्रम the
 * batch to finish.
 *
 * @dev: the device making the request
 * @state: Active/sleep set
 * @cmd: The payload data
 * @n: The array of count of elements in each batch, 0 terminated.
 *
 * Write a request to the RSC controller without caching. If the request
 * state is ACTIVE, then the requests are treated as completion request
 * and sent to the controller immediately. The function रुकोs until all the
 * commands are complete. If the request was to SLEEP or WAKE_ONLY, then the
 * request is sent as fire-n-क्रमget and no ack is expected.
 *
 * May sleep. Do not call from atomic contexts क्रम ACTIVE_ONLY requests.
 */
पूर्णांक rpmh_ग_लिखो_batch(स्थिर काष्ठा device *dev, क्रमागत rpmh_state state,
		     स्थिर काष्ठा tcs_cmd *cmd, u32 *n)
अणु
	काष्ठा batch_cache_req *req;
	काष्ठा rpmh_request *rpm_msgs;
	काष्ठा completion *compls;
	काष्ठा rpmh_ctrlr *ctrlr = get_rpmh_ctrlr(dev);
	अचिन्हित दीर्घ समय_left;
	पूर्णांक count = 0;
	पूर्णांक ret, i;
	व्योम *ptr;

	अगर (!cmd || !n)
		वापस -EINVAL;

	जबतक (n[count] > 0)
		count++;
	अगर (!count)
		वापस -EINVAL;

	ptr = kzalloc(माप(*req) +
		      count * (माप(req->rpm_msgs[0]) + माप(*compls)),
		      GFP_ATOMIC);
	अगर (!ptr)
		वापस -ENOMEM;

	req = ptr;
	compls = ptr + माप(*req) + count * माप(*rpm_msgs);

	req->count = count;
	rpm_msgs = req->rpm_msgs;

	क्रम (i = 0; i < count; i++) अणु
		__fill_rpmh_msg(rpm_msgs + i, state, cmd, n[i]);
		cmd += n[i];
	पूर्ण

	अगर (state != RPMH_ACTIVE_ONLY_STATE) अणु
		cache_batch(ctrlr, req);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा completion *compl = &compls[i];

		init_completion(compl);
		rpm_msgs[i].completion = compl;
		ret = rpmh_rsc_send_data(ctrlr_to_drv(ctrlr), &rpm_msgs[i].msg);
		अगर (ret) अणु
			pr_err("Error(%d) sending RPMH message addr=%#x\n",
			       ret, rpm_msgs[i].msg.cmds[0].addr);
			अवरोध;
		पूर्ण
	पूर्ण

	समय_left = RPMH_TIMEOUT_MS;
	जबतक (i--) अणु
		समय_left = रुको_क्रम_completion_समयout(&compls[i], समय_left);
		अगर (!समय_left) अणु
			/*
			 * Better hope they never finish because they'll संकेत
			 * the completion that we're going to मुक्त once
			 * we've वापसed from this function.
			 */
			WARN_ON(1);
			ret = -ETIMEDOUT;
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	kमुक्त(ptr);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(rpmh_ग_लिखो_batch);

अटल पूर्णांक is_req_valid(काष्ठा cache_req *req)
अणु
	वापस (req->sleep_val != अच_पूर्णांक_उच्च &&
		req->wake_val != अच_पूर्णांक_उच्च &&
		req->sleep_val != req->wake_val);
पूर्ण

अटल पूर्णांक send_single(काष्ठा rpmh_ctrlr *ctrlr, क्रमागत rpmh_state state,
		       u32 addr, u32 data)
अणु
	DEFINE_RPMH_MSG_ONSTACK(शून्य, state, शून्य, rpm_msg);

	/* Wake sets are always complete and sleep sets are not */
	rpm_msg.msg.रुको_क्रम_compl = (state == RPMH_WAKE_ONLY_STATE);
	rpm_msg.cmd[0].addr = addr;
	rpm_msg.cmd[0].data = data;
	rpm_msg.msg.num_cmds = 1;

	वापस rpmh_rsc_ग_लिखो_ctrl_data(ctrlr_to_drv(ctrlr), &rpm_msg.msg);
पूर्ण

/**
 * rpmh_flush() - Flushes the buffered sleep and wake sets to TCSes
 *
 * @ctrlr: Controller making request to flush cached data
 *
 * Return:
 * * 0          - Success
 * * Error code - Otherwise
 */
पूर्णांक rpmh_flush(काष्ठा rpmh_ctrlr *ctrlr)
अणु
	काष्ठा cache_req *p;
	पूर्णांक ret = 0;

	lockdep_निश्चित_irqs_disabled();

	/*
	 * Currently rpmh_flush() is only called when we think we're running
	 * on the last processor.  If the lock is busy it means another
	 * processor is up and it's better to पात than spin.
	 */
	अगर (!spin_trylock(&ctrlr->cache_lock))
		वापस -EBUSY;

	अगर (!ctrlr->dirty) अणु
		pr_debug("Skipping flush, TCS has latest data.\n");
		जाओ निकास;
	पूर्ण

	/* Invalidate the TCSes first to aव्योम stale data */
	rpmh_rsc_invalidate(ctrlr_to_drv(ctrlr));

	/* First flush the cached batch requests */
	ret = flush_batch(ctrlr);
	अगर (ret)
		जाओ निकास;

	list_क्रम_each_entry(p, &ctrlr->cache, list) अणु
		अगर (!is_req_valid(p)) अणु
			pr_debug("%s: skipping RPMH req: a:%#x s:%#x w:%#x",
				 __func__, p->addr, p->sleep_val, p->wake_val);
			जारी;
		पूर्ण
		ret = send_single(ctrlr, RPMH_SLEEP_STATE, p->addr,
				  p->sleep_val);
		अगर (ret)
			जाओ निकास;
		ret = send_single(ctrlr, RPMH_WAKE_ONLY_STATE, p->addr,
				  p->wake_val);
		अगर (ret)
			जाओ निकास;
	पूर्ण

	ctrlr->dirty = false;

निकास:
	spin_unlock(&ctrlr->cache_lock);
	वापस ret;
पूर्ण

/**
 * rpmh_invalidate: Invalidate sleep and wake sets in batch_cache
 *
 * @dev: The device making the request
 *
 * Invalidate the sleep and wake values in batch_cache.
 */
व्योम rpmh_invalidate(स्थिर काष्ठा device *dev)
अणु
	काष्ठा rpmh_ctrlr *ctrlr = get_rpmh_ctrlr(dev);
	काष्ठा batch_cache_req *req, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctrlr->cache_lock, flags);
	list_क्रम_each_entry_safe(req, पंचांगp, &ctrlr->batch_cache, list)
		kमुक्त(req);
	INIT_LIST_HEAD(&ctrlr->batch_cache);
	ctrlr->dirty = true;
	spin_unlock_irqrestore(&ctrlr->cache_lock, flags);
पूर्ण
EXPORT_SYMBOL(rpmh_invalidate);
