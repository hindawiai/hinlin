<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) crypto API support
 *
 * Copyright (C) 2013,2017 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/ccp.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/akcipher.h>

#समावेश "ccp-crypto.h"

MODULE_AUTHOR("Tom Lendacky <thomas.lendacky@amd.com>");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0.0");
MODULE_DESCRIPTION("AMD Cryptographic Coprocessor crypto API support");

अटल अचिन्हित पूर्णांक aes_disable;
module_param(aes_disable, uपूर्णांक, 0444);
MODULE_PARM_DESC(aes_disable, "Disable use of AES - any non-zero value");

अटल अचिन्हित पूर्णांक sha_disable;
module_param(sha_disable, uपूर्णांक, 0444);
MODULE_PARM_DESC(sha_disable, "Disable use of SHA - any non-zero value");

अटल अचिन्हित पूर्णांक des3_disable;
module_param(des3_disable, uपूर्णांक, 0444);
MODULE_PARM_DESC(des3_disable, "Disable use of 3DES - any non-zero value");

अटल अचिन्हित पूर्णांक rsa_disable;
module_param(rsa_disable, uपूर्णांक, 0444);
MODULE_PARM_DESC(rsa_disable, "Disable use of RSA - any non-zero value");

/* List heads क्रम the supported algorithms */
अटल LIST_HEAD(hash_algs);
अटल LIST_HEAD(skcipher_algs);
अटल LIST_HEAD(aead_algs);
अटल LIST_HEAD(akcipher_algs);

/* For any tfm, requests क्रम that tfm must be वापसed on the order
 * received.  With multiple queues available, the CCP can process more
 * than one cmd at a समय.  Thereक्रमe we must मुख्यtain a cmd list to insure
 * the proper ordering of requests on a given tfm.
 */
काष्ठा ccp_crypto_queue अणु
	काष्ठा list_head cmds;
	काष्ठा list_head *backlog;
	अचिन्हित पूर्णांक cmd_count;
पूर्ण;

#घोषणा CCP_CRYPTO_MAX_QLEN	100

अटल काष्ठा ccp_crypto_queue req_queue;
अटल DEFINE_SPINLOCK(req_queue_lock);

काष्ठा ccp_crypto_cmd अणु
	काष्ठा list_head entry;

	काष्ठा ccp_cmd *cmd;

	/* Save the crypto_tfm and crypto_async_request addresses
	 * separately to aव्योम any reference to a possibly invalid
	 * crypto_async_request काष्ठाure after invoking the request
	 * callback
	 */
	काष्ठा crypto_async_request *req;
	काष्ठा crypto_tfm *tfm;

	/* Used क्रम held command processing to determine state */
	पूर्णांक ret;
पूर्ण;

काष्ठा ccp_crypto_cpu अणु
	काष्ठा work_काष्ठा work;
	काष्ठा completion completion;
	काष्ठा ccp_crypto_cmd *crypto_cmd;
	पूर्णांक err;
पूर्ण;

अटल अंतरभूत bool ccp_crypto_success(पूर्णांक err)
अणु
	अगर (err && (err != -EINPROGRESS) && (err != -EBUSY))
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा ccp_crypto_cmd *ccp_crypto_cmd_complete(
	काष्ठा ccp_crypto_cmd *crypto_cmd, काष्ठा ccp_crypto_cmd **backlog)
अणु
	काष्ठा ccp_crypto_cmd *held = शून्य, *पंचांगp;
	अचिन्हित दीर्घ flags;

	*backlog = शून्य;

	spin_lock_irqsave(&req_queue_lock, flags);

	/* Held cmds will be after the current cmd in the queue so start
	 * searching क्रम a cmd with a matching tfm क्रम submission.
	 */
	पंचांगp = crypto_cmd;
	list_क्रम_each_entry_जारी(पंचांगp, &req_queue.cmds, entry) अणु
		अगर (crypto_cmd->tfm != पंचांगp->tfm)
			जारी;
		held = पंचांगp;
		अवरोध;
	पूर्ण

	/* Process the backlog:
	 *   Because cmds can be executed from any poपूर्णांक in the cmd list
	 *   special precautions have to be taken when handling the backlog.
	 */
	अगर (req_queue.backlog != &req_queue.cmds) अणु
		/* Skip over this cmd अगर it is the next backlog cmd */
		अगर (req_queue.backlog == &crypto_cmd->entry)
			req_queue.backlog = crypto_cmd->entry.next;

		*backlog = container_of(req_queue.backlog,
					काष्ठा ccp_crypto_cmd, entry);
		req_queue.backlog = req_queue.backlog->next;

		/* Skip over this cmd अगर it is now the next backlog cmd */
		अगर (req_queue.backlog == &crypto_cmd->entry)
			req_queue.backlog = crypto_cmd->entry.next;
	पूर्ण

	/* Remove the cmd entry from the list of cmds */
	req_queue.cmd_count--;
	list_del(&crypto_cmd->entry);

	spin_unlock_irqrestore(&req_queue_lock, flags);

	वापस held;
पूर्ण

अटल व्योम ccp_crypto_complete(व्योम *data, पूर्णांक err)
अणु
	काष्ठा ccp_crypto_cmd *crypto_cmd = data;
	काष्ठा ccp_crypto_cmd *held, *next, *backlog;
	काष्ठा crypto_async_request *req = crypto_cmd->req;
	काष्ठा ccp_ctx *ctx = crypto_tfm_ctx(req->tfm);
	पूर्णांक ret;

	अगर (err == -EINPROGRESS) अणु
		/* Only propagate the -EINPROGRESS अगर necessary */
		अगर (crypto_cmd->ret == -EBUSY) अणु
			crypto_cmd->ret = -EINPROGRESS;
			req->complete(req, -EINPROGRESS);
		पूर्ण

		वापस;
	पूर्ण

	/* Operation has completed - update the queue beक्रमe invoking
	 * the completion callbacks and retrieve the next cmd (cmd with
	 * a matching tfm) that can be submitted to the CCP.
	 */
	held = ccp_crypto_cmd_complete(crypto_cmd, &backlog);
	अगर (backlog) अणु
		backlog->ret = -EINPROGRESS;
		backlog->req->complete(backlog->req, -EINPROGRESS);
	पूर्ण

	/* Transition the state from -EBUSY to -EINPROGRESS first */
	अगर (crypto_cmd->ret == -EBUSY)
		req->complete(req, -EINPROGRESS);

	/* Completion callbacks */
	ret = err;
	अगर (ctx->complete)
		ret = ctx->complete(req, ret);
	req->complete(req, ret);

	/* Submit the next cmd */
	जबतक (held) अणु
		/* Since we have alपढ़ोy queued the cmd, we must indicate that
		 * we can backlog so as not to "lose" this request.
		 */
		held->cmd->flags |= CCP_CMD_MAY_BACKLOG;
		ret = ccp_enqueue_cmd(held->cmd);
		अगर (ccp_crypto_success(ret))
			अवरोध;

		/* Error occurred, report it and get the next entry */
		ctx = crypto_tfm_ctx(held->req->tfm);
		अगर (ctx->complete)
			ret = ctx->complete(held->req, ret);
		held->req->complete(held->req, ret);

		next = ccp_crypto_cmd_complete(held, &backlog);
		अगर (backlog) अणु
			backlog->ret = -EINPROGRESS;
			backlog->req->complete(backlog->req, -EINPROGRESS);
		पूर्ण

		kमुक्त(held);
		held = next;
	पूर्ण

	kमुक्त(crypto_cmd);
पूर्ण

अटल पूर्णांक ccp_crypto_enqueue_cmd(काष्ठा ccp_crypto_cmd *crypto_cmd)
अणु
	काष्ठा ccp_crypto_cmd *active = शून्य, *पंचांगp;
	अचिन्हित दीर्घ flags;
	bool मुक्त_cmd = true;
	पूर्णांक ret;

	spin_lock_irqsave(&req_queue_lock, flags);

	/* Check अगर the cmd can/should be queued */
	अगर (req_queue.cmd_count >= CCP_CRYPTO_MAX_QLEN) अणु
		अगर (!(crypto_cmd->cmd->flags & CCP_CMD_MAY_BACKLOG)) अणु
			ret = -ENOSPC;
			जाओ e_lock;
		पूर्ण
	पूर्ण

	/* Look क्रम an entry with the same tfm.  If there is a cmd
	 * with the same tfm in the list then the current cmd cannot
	 * be submitted to the CCP yet.
	 */
	list_क्रम_each_entry(पंचांगp, &req_queue.cmds, entry) अणु
		अगर (crypto_cmd->tfm != पंचांगp->tfm)
			जारी;
		active = पंचांगp;
		अवरोध;
	पूर्ण

	ret = -EINPROGRESS;
	अगर (!active) अणु
		ret = ccp_enqueue_cmd(crypto_cmd->cmd);
		अगर (!ccp_crypto_success(ret))
			जाओ e_lock;	/* Error, करोn't queue it */
	पूर्ण

	अगर (req_queue.cmd_count >= CCP_CRYPTO_MAX_QLEN) अणु
		ret = -EBUSY;
		अगर (req_queue.backlog == &req_queue.cmds)
			req_queue.backlog = &crypto_cmd->entry;
	पूर्ण
	crypto_cmd->ret = ret;

	req_queue.cmd_count++;
	list_add_tail(&crypto_cmd->entry, &req_queue.cmds);

	मुक्त_cmd = false;

e_lock:
	spin_unlock_irqrestore(&req_queue_lock, flags);

	अगर (मुक्त_cmd)
		kमुक्त(crypto_cmd);

	वापस ret;
पूर्ण

/**
 * ccp_crypto_enqueue_request - queue an crypto async request क्रम processing
 *				by the CCP
 *
 * @req: crypto_async_request काष्ठा to be processed
 * @cmd: ccp_cmd काष्ठा to be sent to the CCP
 */
पूर्णांक ccp_crypto_enqueue_request(काष्ठा crypto_async_request *req,
			       काष्ठा ccp_cmd *cmd)
अणु
	काष्ठा ccp_crypto_cmd *crypto_cmd;
	gfp_t gfp;

	gfp = req->flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL : GFP_ATOMIC;

	crypto_cmd = kzalloc(माप(*crypto_cmd), gfp);
	अगर (!crypto_cmd)
		वापस -ENOMEM;

	/* The tfm poपूर्णांकer must be saved and not referenced from the
	 * crypto_async_request (req) poपूर्णांकer because it is used after
	 * completion callback क्रम the request and the req poपूर्णांकer
	 * might not be valid anymore.
	 */
	crypto_cmd->cmd = cmd;
	crypto_cmd->req = req;
	crypto_cmd->tfm = req->tfm;

	cmd->callback = ccp_crypto_complete;
	cmd->data = crypto_cmd;

	अगर (req->flags & CRYPTO_TFM_REQ_MAY_BACKLOG)
		cmd->flags |= CCP_CMD_MAY_BACKLOG;
	अन्यथा
		cmd->flags &= ~CCP_CMD_MAY_BACKLOG;

	वापस ccp_crypto_enqueue_cmd(crypto_cmd);
पूर्ण

काष्ठा scatterlist *ccp_crypto_sg_table_add(काष्ठा sg_table *table,
					    काष्ठा scatterlist *sg_add)
अणु
	काष्ठा scatterlist *sg, *sg_last = शून्य;

	क्रम (sg = table->sgl; sg; sg = sg_next(sg))
		अगर (!sg_page(sg))
			अवरोध;
	अगर (WARN_ON(!sg))
		वापस शून्य;

	क्रम (; sg && sg_add; sg = sg_next(sg), sg_add = sg_next(sg_add)) अणु
		sg_set_page(sg, sg_page(sg_add), sg_add->length,
			    sg_add->offset);
		sg_last = sg;
	पूर्ण
	अगर (WARN_ON(sg_add))
		वापस शून्य;

	वापस sg_last;
पूर्ण

अटल पूर्णांक ccp_रेजिस्टर_algs(व्योम)
अणु
	पूर्णांक ret;

	अगर (!aes_disable) अणु
		ret = ccp_रेजिस्टर_aes_algs(&skcipher_algs);
		अगर (ret)
			वापस ret;

		ret = ccp_रेजिस्टर_aes_cmac_algs(&hash_algs);
		अगर (ret)
			वापस ret;

		ret = ccp_रेजिस्टर_aes_xts_algs(&skcipher_algs);
		अगर (ret)
			वापस ret;

		ret = ccp_रेजिस्टर_aes_aeads(&aead_algs);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!des3_disable) अणु
		ret = ccp_रेजिस्टर_des3_algs(&skcipher_algs);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!sha_disable) अणु
		ret = ccp_रेजिस्टर_sha_algs(&hash_algs);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!rsa_disable) अणु
		ret = ccp_रेजिस्टर_rsa_algs(&akcipher_algs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ccp_unरेजिस्टर_algs(व्योम)
अणु
	काष्ठा ccp_crypto_ahash_alg *ahash_alg, *ahash_पंचांगp;
	काष्ठा ccp_crypto_skcipher_alg *ablk_alg, *ablk_पंचांगp;
	काष्ठा ccp_crypto_aead *aead_alg, *aead_पंचांगp;
	काष्ठा ccp_crypto_akcipher_alg *akc_alg, *akc_पंचांगp;

	list_क्रम_each_entry_safe(ahash_alg, ahash_पंचांगp, &hash_algs, entry) अणु
		crypto_unरेजिस्टर_ahash(&ahash_alg->alg);
		list_del(&ahash_alg->entry);
		kमुक्त(ahash_alg);
	पूर्ण

	list_क्रम_each_entry_safe(ablk_alg, ablk_पंचांगp, &skcipher_algs, entry) अणु
		crypto_unरेजिस्टर_skcipher(&ablk_alg->alg);
		list_del(&ablk_alg->entry);
		kमुक्त(ablk_alg);
	पूर्ण

	list_क्रम_each_entry_safe(aead_alg, aead_पंचांगp, &aead_algs, entry) अणु
		crypto_unरेजिस्टर_aead(&aead_alg->alg);
		list_del(&aead_alg->entry);
		kमुक्त(aead_alg);
	पूर्ण

	list_क्रम_each_entry_safe(akc_alg, akc_पंचांगp, &akcipher_algs, entry) अणु
		crypto_unरेजिस्टर_akcipher(&akc_alg->alg);
		list_del(&akc_alg->entry);
		kमुक्त(akc_alg);
	पूर्ण
पूर्ण

अटल पूर्णांक ccp_crypto_init(व्योम)
अणु
	पूर्णांक ret;

	ret = ccp_present();
	अगर (ret) अणु
		pr_err("Cannot load: there are no available CCPs\n");
		वापस ret;
	पूर्ण

	INIT_LIST_HEAD(&req_queue.cmds);
	req_queue.backlog = &req_queue.cmds;
	req_queue.cmd_count = 0;

	ret = ccp_रेजिस्टर_algs();
	अगर (ret)
		ccp_unरेजिस्टर_algs();

	वापस ret;
पूर्ण

अटल व्योम ccp_crypto_निकास(व्योम)
अणु
	ccp_unरेजिस्टर_algs();
पूर्ण

module_init(ccp_crypto_init);
module_निकास(ccp_crypto_निकास);
