<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Crypto engine API
 *
 * Copyright (c) 2016 Baolin Wang <baolin.wang@linaro.org>
 */
#अगर_अघोषित _CRYPTO_ENGINE_H
#घोषणा _CRYPTO_ENGINE_H

#समावेश <linux/crypto.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>

#घोषणा ENGINE_NAME_LEN	30
/*
 * काष्ठा crypto_engine - crypto hardware engine
 * @name: the engine name
 * @idling: the engine is entering idle state
 * @busy: request pump is busy
 * @running: the engine is on working
 * @retry_support: indication that the hardware allows re-execution
 * of a failed backlog request
 * crypto-engine, in head position to keep order
 * @list: link with the global crypto engine list
 * @queue_lock: spinlock to syncronise access to request queue
 * @queue: the crypto queue of the engine
 * @rt: whether this queue is set to run as a realसमय task
 * @prepare_crypt_hardware: a request will soon arrive from the queue
 * so the subप्रणाली requests the driver to prepare the hardware
 * by issuing this call
 * @unprepare_crypt_hardware: there are currently no more requests on the
 * queue so the subप्रणाली notअगरies the driver that it may relax the
 * hardware by issuing this call
 * @करो_batch_requests: execute a batch of requests. Depends on multiple
 * requests support.
 * @kworker: kthपढ़ो worker काष्ठा क्रम request pump
 * @pump_requests: work काष्ठा क्रम scheduling work to the request pump
 * @priv_data: the engine निजी data
 * @cur_req: the current request which is on processing
 */
काष्ठा crypto_engine अणु
	अक्षर			name[ENGINE_NAME_LEN];
	bool			idling;
	bool			busy;
	bool			running;

	bool			retry_support;

	काष्ठा list_head	list;
	spinlock_t		queue_lock;
	काष्ठा crypto_queue	queue;
	काष्ठा device		*dev;

	bool			rt;

	पूर्णांक (*prepare_crypt_hardware)(काष्ठा crypto_engine *engine);
	पूर्णांक (*unprepare_crypt_hardware)(काष्ठा crypto_engine *engine);
	पूर्णांक (*करो_batch_requests)(काष्ठा crypto_engine *engine);


	काष्ठा kthपढ़ो_worker           *kworker;
	काष्ठा kthपढ़ो_work             pump_requests;

	व्योम				*priv_data;
	काष्ठा crypto_async_request	*cur_req;
पूर्ण;

/*
 * काष्ठा crypto_engine_op - crypto hardware engine operations
 * @prepare__request: करो some prepare अगर need beक्रमe handle the current request
 * @unprepare_request: unकरो any work करोne by prepare_request()
 * @करो_one_request: करो encryption क्रम current request
 */
काष्ठा crypto_engine_op अणु
	पूर्णांक (*prepare_request)(काष्ठा crypto_engine *engine,
			       व्योम *areq);
	पूर्णांक (*unprepare_request)(काष्ठा crypto_engine *engine,
				 व्योम *areq);
	पूर्णांक (*करो_one_request)(काष्ठा crypto_engine *engine,
			      व्योम *areq);
पूर्ण;

काष्ठा crypto_engine_ctx अणु
	काष्ठा crypto_engine_op op;
पूर्ण;

पूर्णांक crypto_transfer_aead_request_to_engine(काष्ठा crypto_engine *engine,
					   काष्ठा aead_request *req);
पूर्णांक crypto_transfer_akcipher_request_to_engine(काष्ठा crypto_engine *engine,
					       काष्ठा akcipher_request *req);
पूर्णांक crypto_transfer_hash_request_to_engine(काष्ठा crypto_engine *engine,
					       काष्ठा ahash_request *req);
पूर्णांक crypto_transfer_skcipher_request_to_engine(काष्ठा crypto_engine *engine,
					       काष्ठा skcipher_request *req);
व्योम crypto_finalize_aead_request(काष्ठा crypto_engine *engine,
				  काष्ठा aead_request *req, पूर्णांक err);
व्योम crypto_finalize_akcipher_request(काष्ठा crypto_engine *engine,
				      काष्ठा akcipher_request *req, पूर्णांक err);
व्योम crypto_finalize_hash_request(काष्ठा crypto_engine *engine,
				  काष्ठा ahash_request *req, पूर्णांक err);
व्योम crypto_finalize_skcipher_request(काष्ठा crypto_engine *engine,
				      काष्ठा skcipher_request *req, पूर्णांक err);
पूर्णांक crypto_engine_start(काष्ठा crypto_engine *engine);
पूर्णांक crypto_engine_stop(काष्ठा crypto_engine *engine);
काष्ठा crypto_engine *crypto_engine_alloc_init(काष्ठा device *dev, bool rt);
काष्ठा crypto_engine *crypto_engine_alloc_init_and_set(काष्ठा device *dev,
						       bool retry_support,
						       पूर्णांक (*cbk_करो_batch)(काष्ठा crypto_engine *engine),
						       bool rt, पूर्णांक qlen);
पूर्णांक crypto_engine_निकास(काष्ठा crypto_engine *engine);

#पूर्ण_अगर /* _CRYPTO_ENGINE_H */
