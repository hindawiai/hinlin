<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Handle async block request by crypto hardware engine.
 *
 * Copyright (C) 2016 Linaro, Inc.
 *
 * Author: Baolin Wang <baolin.wang@linaro.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <crypto/engine.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश "internal.h"

#घोषणा CRYPTO_ENGINE_MAX_QLEN 10

/**
 * crypto_finalize_request - finalize one request अगर the request is करोne
 * @engine: the hardware engine
 * @req: the request need to be finalized
 * @err: error number
 */
अटल व्योम crypto_finalize_request(काष्ठा crypto_engine *engine,
				    काष्ठा crypto_async_request *req, पूर्णांक err)
अणु
	अचिन्हित दीर्घ flags;
	bool finalize_req = false;
	पूर्णांक ret;
	काष्ठा crypto_engine_ctx *enginectx;

	/*
	 * If hardware cannot enqueue more requests
	 * and retry mechanism is not supported
	 * make sure we are completing the current request
	 */
	अगर (!engine->retry_support) अणु
		spin_lock_irqsave(&engine->queue_lock, flags);
		अगर (engine->cur_req == req) अणु
			finalize_req = true;
			engine->cur_req = शून्य;
		पूर्ण
		spin_unlock_irqrestore(&engine->queue_lock, flags);
	पूर्ण

	अगर (finalize_req || engine->retry_support) अणु
		enginectx = crypto_tfm_ctx(req->tfm);
		अगर (enginectx->op.prepare_request &&
		    enginectx->op.unprepare_request) अणु
			ret = enginectx->op.unprepare_request(engine, req);
			अगर (ret)
				dev_err(engine->dev, "failed to unprepare request\n");
		पूर्ण
	पूर्ण
	req->complete(req, err);

	kthपढ़ो_queue_work(engine->kworker, &engine->pump_requests);
पूर्ण

/**
 * crypto_pump_requests - dequeue one request from engine queue to process
 * @engine: the hardware engine
 * @in_kthपढ़ो: true अगर we are in the context of the request pump thपढ़ो
 *
 * This function checks अगर there is any request in the engine queue that
 * needs processing and अगर so call out to the driver to initialize hardware
 * and handle each request.
 */
अटल व्योम crypto_pump_requests(काष्ठा crypto_engine *engine,
				 bool in_kthपढ़ो)
अणु
	काष्ठा crypto_async_request *async_req, *backlog;
	अचिन्हित दीर्घ flags;
	bool was_busy = false;
	पूर्णांक ret;
	काष्ठा crypto_engine_ctx *enginectx;

	spin_lock_irqsave(&engine->queue_lock, flags);

	/* Make sure we are not alपढ़ोy running a request */
	अगर (!engine->retry_support && engine->cur_req)
		जाओ out;

	/* If another context is idling then defer */
	अगर (engine->idling) अणु
		kthपढ़ो_queue_work(engine->kworker, &engine->pump_requests);
		जाओ out;
	पूर्ण

	/* Check अगर the engine queue is idle */
	अगर (!crypto_queue_len(&engine->queue) || !engine->running) अणु
		अगर (!engine->busy)
			जाओ out;

		/* Only करो tearकरोwn in the thपढ़ो */
		अगर (!in_kthपढ़ो) अणु
			kthपढ़ो_queue_work(engine->kworker,
					   &engine->pump_requests);
			जाओ out;
		पूर्ण

		engine->busy = false;
		engine->idling = true;
		spin_unlock_irqrestore(&engine->queue_lock, flags);

		अगर (engine->unprepare_crypt_hardware &&
		    engine->unprepare_crypt_hardware(engine))
			dev_err(engine->dev, "failed to unprepare crypt hardware\n");

		spin_lock_irqsave(&engine->queue_lock, flags);
		engine->idling = false;
		जाओ out;
	पूर्ण

start_request:
	/* Get the fist request from the engine queue to handle */
	backlog = crypto_get_backlog(&engine->queue);
	async_req = crypto_dequeue_request(&engine->queue);
	अगर (!async_req)
		जाओ out;

	/*
	 * If hardware करोesn't support the retry mechanism,
	 * keep track of the request we are processing now.
	 * We'll need it on completion (crypto_finalize_request).
	 */
	अगर (!engine->retry_support)
		engine->cur_req = async_req;

	अगर (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	अगर (engine->busy)
		was_busy = true;
	अन्यथा
		engine->busy = true;

	spin_unlock_irqrestore(&engine->queue_lock, flags);

	/* Until here we get the request need to be encrypted successfully */
	अगर (!was_busy && engine->prepare_crypt_hardware) अणु
		ret = engine->prepare_crypt_hardware(engine);
		अगर (ret) अणु
			dev_err(engine->dev, "failed to prepare crypt hardware\n");
			जाओ req_err_2;
		पूर्ण
	पूर्ण

	enginectx = crypto_tfm_ctx(async_req->tfm);

	अगर (enginectx->op.prepare_request) अणु
		ret = enginectx->op.prepare_request(engine, async_req);
		अगर (ret) अणु
			dev_err(engine->dev, "failed to prepare request: %d\n",
				ret);
			जाओ req_err_2;
		पूर्ण
	पूर्ण
	अगर (!enginectx->op.करो_one_request) अणु
		dev_err(engine->dev, "failed to do request\n");
		ret = -EINVAL;
		जाओ req_err_1;
	पूर्ण

	ret = enginectx->op.करो_one_request(engine, async_req);

	/* Request unsuccessfully executed by hardware */
	अगर (ret < 0) अणु
		/*
		 * If hardware queue is full (-ENOSPC), requeue request
		 * regardless of backlog flag.
		 * Otherwise, unprepare and complete the request.
		 */
		अगर (!engine->retry_support ||
		    (ret != -ENOSPC)) अणु
			dev_err(engine->dev,
				"Failed to do one request from queue: %d\n",
				ret);
			जाओ req_err_1;
		पूर्ण
		/*
		 * If retry mechanism is supported,
		 * unprepare current request and
		 * enqueue it back पूर्णांकo crypto-engine queue.
		 */
		अगर (enginectx->op.unprepare_request) अणु
			ret = enginectx->op.unprepare_request(engine,
							      async_req);
			अगर (ret)
				dev_err(engine->dev,
					"failed to unprepare request\n");
		पूर्ण
		spin_lock_irqsave(&engine->queue_lock, flags);
		/*
		 * If hardware was unable to execute request, enqueue it
		 * back in front of crypto-engine queue, to keep the order
		 * of requests.
		 */
		crypto_enqueue_request_head(&engine->queue, async_req);

		kthपढ़ो_queue_work(engine->kworker, &engine->pump_requests);
		जाओ out;
	पूर्ण

	जाओ retry;

req_err_1:
	अगर (enginectx->op.unprepare_request) अणु
		ret = enginectx->op.unprepare_request(engine, async_req);
		अगर (ret)
			dev_err(engine->dev, "failed to unprepare request\n");
	पूर्ण

req_err_2:
	async_req->complete(async_req, ret);

retry:
	/* If retry mechanism is supported, send new requests to engine */
	अगर (engine->retry_support) अणु
		spin_lock_irqsave(&engine->queue_lock, flags);
		जाओ start_request;
	पूर्ण
	वापस;

out:
	spin_unlock_irqrestore(&engine->queue_lock, flags);

	/*
	 * Batch requests is possible only अगर
	 * hardware can enqueue multiple requests
	 */
	अगर (engine->करो_batch_requests) अणु
		ret = engine->करो_batch_requests(engine);
		अगर (ret)
			dev_err(engine->dev, "failed to do batch requests: %d\n",
				ret);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम crypto_pump_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा crypto_engine *engine =
		container_of(work, काष्ठा crypto_engine, pump_requests);

	crypto_pump_requests(engine, true);
पूर्ण

/**
 * crypto_transfer_request - transfer the new request पूर्णांकo the engine queue
 * @engine: the hardware engine
 * @req: the request need to be listed पूर्णांकo the engine queue
 */
अटल पूर्णांक crypto_transfer_request(काष्ठा crypto_engine *engine,
				   काष्ठा crypto_async_request *req,
				   bool need_pump)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&engine->queue_lock, flags);

	अगर (!engine->running) अणु
		spin_unlock_irqrestore(&engine->queue_lock, flags);
		वापस -ESHUTDOWN;
	पूर्ण

	ret = crypto_enqueue_request(&engine->queue, req);

	अगर (!engine->busy && need_pump)
		kthपढ़ो_queue_work(engine->kworker, &engine->pump_requests);

	spin_unlock_irqrestore(&engine->queue_lock, flags);
	वापस ret;
पूर्ण

/**
 * crypto_transfer_request_to_engine - transfer one request to list
 * पूर्णांकo the engine queue
 * @engine: the hardware engine
 * @req: the request need to be listed पूर्णांकo the engine queue
 */
अटल पूर्णांक crypto_transfer_request_to_engine(काष्ठा crypto_engine *engine,
					     काष्ठा crypto_async_request *req)
अणु
	वापस crypto_transfer_request(engine, req, true);
पूर्ण

/**
 * crypto_transfer_aead_request_to_engine - transfer one aead_request
 * to list पूर्णांकo the engine queue
 * @engine: the hardware engine
 * @req: the request need to be listed पूर्णांकo the engine queue
 */
पूर्णांक crypto_transfer_aead_request_to_engine(काष्ठा crypto_engine *engine,
					   काष्ठा aead_request *req)
अणु
	वापस crypto_transfer_request_to_engine(engine, &req->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_transfer_aead_request_to_engine);

/**
 * crypto_transfer_akcipher_request_to_engine - transfer one akcipher_request
 * to list पूर्णांकo the engine queue
 * @engine: the hardware engine
 * @req: the request need to be listed पूर्णांकo the engine queue
 */
पूर्णांक crypto_transfer_akcipher_request_to_engine(काष्ठा crypto_engine *engine,
					       काष्ठा akcipher_request *req)
अणु
	वापस crypto_transfer_request_to_engine(engine, &req->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_transfer_akcipher_request_to_engine);

/**
 * crypto_transfer_hash_request_to_engine - transfer one ahash_request
 * to list पूर्णांकo the engine queue
 * @engine: the hardware engine
 * @req: the request need to be listed पूर्णांकo the engine queue
 */
पूर्णांक crypto_transfer_hash_request_to_engine(काष्ठा crypto_engine *engine,
					   काष्ठा ahash_request *req)
अणु
	वापस crypto_transfer_request_to_engine(engine, &req->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_transfer_hash_request_to_engine);

/**
 * crypto_transfer_skcipher_request_to_engine - transfer one skcipher_request
 * to list पूर्णांकo the engine queue
 * @engine: the hardware engine
 * @req: the request need to be listed पूर्णांकo the engine queue
 */
पूर्णांक crypto_transfer_skcipher_request_to_engine(काष्ठा crypto_engine *engine,
					       काष्ठा skcipher_request *req)
अणु
	वापस crypto_transfer_request_to_engine(engine, &req->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_transfer_skcipher_request_to_engine);

/**
 * crypto_finalize_aead_request - finalize one aead_request अगर
 * the request is करोne
 * @engine: the hardware engine
 * @req: the request need to be finalized
 * @err: error number
 */
व्योम crypto_finalize_aead_request(काष्ठा crypto_engine *engine,
				  काष्ठा aead_request *req, पूर्णांक err)
अणु
	वापस crypto_finalize_request(engine, &req->base, err);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_finalize_aead_request);

/**
 * crypto_finalize_akcipher_request - finalize one akcipher_request अगर
 * the request is करोne
 * @engine: the hardware engine
 * @req: the request need to be finalized
 * @err: error number
 */
व्योम crypto_finalize_akcipher_request(काष्ठा crypto_engine *engine,
				      काष्ठा akcipher_request *req, पूर्णांक err)
अणु
	वापस crypto_finalize_request(engine, &req->base, err);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_finalize_akcipher_request);

/**
 * crypto_finalize_hash_request - finalize one ahash_request अगर
 * the request is करोne
 * @engine: the hardware engine
 * @req: the request need to be finalized
 * @err: error number
 */
व्योम crypto_finalize_hash_request(काष्ठा crypto_engine *engine,
				  काष्ठा ahash_request *req, पूर्णांक err)
अणु
	वापस crypto_finalize_request(engine, &req->base, err);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_finalize_hash_request);

/**
 * crypto_finalize_skcipher_request - finalize one skcipher_request अगर
 * the request is करोne
 * @engine: the hardware engine
 * @req: the request need to be finalized
 * @err: error number
 */
व्योम crypto_finalize_skcipher_request(काष्ठा crypto_engine *engine,
				      काष्ठा skcipher_request *req, पूर्णांक err)
अणु
	वापस crypto_finalize_request(engine, &req->base, err);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_finalize_skcipher_request);

/**
 * crypto_engine_start - start the hardware engine
 * @engine: the hardware engine need to be started
 *
 * Return 0 on success, अन्यथा on fail.
 */
पूर्णांक crypto_engine_start(काष्ठा crypto_engine *engine)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&engine->queue_lock, flags);

	अगर (engine->running || engine->busy) अणु
		spin_unlock_irqrestore(&engine->queue_lock, flags);
		वापस -EBUSY;
	पूर्ण

	engine->running = true;
	spin_unlock_irqrestore(&engine->queue_lock, flags);

	kthपढ़ो_queue_work(engine->kworker, &engine->pump_requests);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_engine_start);

/**
 * crypto_engine_stop - stop the hardware engine
 * @engine: the hardware engine need to be stopped
 *
 * Return 0 on success, अन्यथा on fail.
 */
पूर्णांक crypto_engine_stop(काष्ठा crypto_engine *engine)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक limit = 500;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&engine->queue_lock, flags);

	/*
	 * If the engine queue is not empty or the engine is on busy state,
	 * we need to रुको क्रम a जबतक to pump the requests of engine queue.
	 */
	जबतक ((crypto_queue_len(&engine->queue) || engine->busy) && limit--) अणु
		spin_unlock_irqrestore(&engine->queue_lock, flags);
		msleep(20);
		spin_lock_irqsave(&engine->queue_lock, flags);
	पूर्ण

	अगर (crypto_queue_len(&engine->queue) || engine->busy)
		ret = -EBUSY;
	अन्यथा
		engine->running = false;

	spin_unlock_irqrestore(&engine->queue_lock, flags);

	अगर (ret)
		dev_warn(engine->dev, "could not stop engine\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_engine_stop);

/**
 * crypto_engine_alloc_init_and_set - allocate crypto hardware engine काष्ठाure
 * and initialize it by setting the maximum number of entries in the software
 * crypto-engine queue.
 * @dev: the device attached with one hardware engine
 * @retry_support: whether hardware has support क्रम retry mechanism
 * @cbk_करो_batch: poपूर्णांकer to a callback function to be invoked when executing
 *                a batch of requests.
 *                This has the क्रमm:
 *                callback(काष्ठा crypto_engine *engine)
 *                where:
 *                @engine: the crypto engine काष्ठाure.
 * @rt: whether this queue is set to run as a realसमय task
 * @qlen: maximum size of the crypto-engine queue
 *
 * This must be called from context that can sleep.
 * Return: the crypto engine काष्ठाure on success, अन्यथा शून्य.
 */
काष्ठा crypto_engine *crypto_engine_alloc_init_and_set(काष्ठा device *dev,
						       bool retry_support,
						       पूर्णांक (*cbk_करो_batch)(काष्ठा crypto_engine *engine),
						       bool rt, पूर्णांक qlen)
अणु
	काष्ठा crypto_engine *engine;

	अगर (!dev)
		वापस शून्य;

	engine = devm_kzalloc(dev, माप(*engine), GFP_KERNEL);
	अगर (!engine)
		वापस शून्य;

	engine->dev = dev;
	engine->rt = rt;
	engine->running = false;
	engine->busy = false;
	engine->idling = false;
	engine->retry_support = retry_support;
	engine->priv_data = dev;
	/*
	 * Batch requests is possible only अगर
	 * hardware has support क्रम retry mechanism.
	 */
	engine->करो_batch_requests = retry_support ? cbk_करो_batch : शून्य;

	snम_लिखो(engine->name, माप(engine->name),
		 "%s-engine", dev_name(dev));

	crypto_init_queue(&engine->queue, qlen);
	spin_lock_init(&engine->queue_lock);

	engine->kworker = kthपढ़ो_create_worker(0, "%s", engine->name);
	अगर (IS_ERR(engine->kworker)) अणु
		dev_err(dev, "failed to create crypto request pump task\n");
		वापस शून्य;
	पूर्ण
	kthपढ़ो_init_work(&engine->pump_requests, crypto_pump_work);

	अगर (engine->rt) अणु
		dev_info(dev, "will run requests pump with realtime priority\n");
		sched_set_fअगरo(engine->kworker->task);
	पूर्ण

	वापस engine;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_engine_alloc_init_and_set);

/**
 * crypto_engine_alloc_init - allocate crypto hardware engine काष्ठाure and
 * initialize it.
 * @dev: the device attached with one hardware engine
 * @rt: whether this queue is set to run as a realसमय task
 *
 * This must be called from context that can sleep.
 * Return: the crypto engine काष्ठाure on success, अन्यथा शून्य.
 */
काष्ठा crypto_engine *crypto_engine_alloc_init(काष्ठा device *dev, bool rt)
अणु
	वापस crypto_engine_alloc_init_and_set(dev, false, शून्य, rt,
						CRYPTO_ENGINE_MAX_QLEN);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_engine_alloc_init);

/**
 * crypto_engine_निकास - मुक्त the resources of hardware engine when निकास
 * @engine: the hardware engine need to be मुक्तd
 *
 * Return 0 क्रम success.
 */
पूर्णांक crypto_engine_निकास(काष्ठा crypto_engine *engine)
अणु
	पूर्णांक ret;

	ret = crypto_engine_stop(engine);
	अगर (ret)
		वापस ret;

	kthपढ़ो_destroy_worker(engine->kworker);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_engine_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Crypto hardware engine framework");
