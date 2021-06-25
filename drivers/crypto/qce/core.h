<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2014, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _CORE_H_
#घोषणा _CORE_H_

#समावेश "dma.h"

/**
 * काष्ठा qce_device - crypto engine device काष्ठाure
 * @queue: crypto request queue
 * @lock: the lock protects queue and req
 * @करोne_tasklet: करोne tasklet object
 * @req: current active request
 * @result: result of current transक्रमm
 * @base: भव IO base
 * @dev: poपूर्णांकer to device काष्ठाure
 * @core: core device घड़ी
 * @अगरace: पूर्णांकerface घड़ी
 * @bus: bus घड़ी
 * @dma: poपूर्णांकer to dma data
 * @burst_size: the crypto burst size
 * @pipe_pair_id: which pipe pair id the device using
 * @async_req_enqueue: invoked by every algorithm to enqueue a request
 * @async_req_करोne: invoked by every algorithm to finish its request
 */
काष्ठा qce_device अणु
	काष्ठा crypto_queue queue;
	spinlock_t lock;
	काष्ठा tasklet_काष्ठा करोne_tasklet;
	काष्ठा crypto_async_request *req;
	पूर्णांक result;
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा clk *core, *अगरace, *bus;
	काष्ठा qce_dma_data dma;
	पूर्णांक burst_size;
	अचिन्हित पूर्णांक pipe_pair_id;
	पूर्णांक (*async_req_enqueue)(काष्ठा qce_device *qce,
				 काष्ठा crypto_async_request *req);
	व्योम (*async_req_करोne)(काष्ठा qce_device *qce, पूर्णांक ret);
पूर्ण;

/**
 * काष्ठा qce_algo_ops - algorithm operations per crypto type
 * @type: should be CRYPTO_ALG_TYPE_XXX
 * @रेजिस्टर_algs: invoked by core to रेजिस्टर the algorithms
 * @unरेजिस्टर_algs: invoked by core to unरेजिस्टर the algorithms
 * @async_req_handle: invoked by core to handle enqueued request
 */
काष्ठा qce_algo_ops अणु
	u32 type;
	पूर्णांक (*रेजिस्टर_algs)(काष्ठा qce_device *qce);
	व्योम (*unरेजिस्टर_algs)(काष्ठा qce_device *qce);
	पूर्णांक (*async_req_handle)(काष्ठा crypto_async_request *async_req);
पूर्ण;

#पूर्ण_अगर /* _CORE_H_ */
