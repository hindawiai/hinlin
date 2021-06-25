<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

/* \पile cc_request_mgr.h
 * Request Manager
 */

#अगर_अघोषित __REQUEST_MGR_H__
#घोषणा __REQUEST_MGR_H__

#समावेश "cc_hw_queue_defs.h"

पूर्णांक cc_req_mgr_init(काष्ठा cc_drvdata *drvdata);

/**
 * cc_send_request() - Enqueue caller request to crypto hardware.
 *
 * @drvdata: Associated device driver context
 * @cc_req: The request to enqueue
 * @desc: The crypto sequence
 * @len: The crypto sequence length
 * @req: Asynchronous crypto request
 *
 * Return:
 * Returns -EINPROGRESS or error
 */
पूर्णांक cc_send_request(काष्ठा cc_drvdata *drvdata, काष्ठा cc_crypto_req *cc_req,
		    काष्ठा cc_hw_desc *desc, अचिन्हित पूर्णांक len,
		    काष्ठा crypto_async_request *req);

पूर्णांक cc_send_sync_request(काष्ठा cc_drvdata *drvdata,
			 काष्ठा cc_crypto_req *cc_req, काष्ठा cc_hw_desc *desc,
			 अचिन्हित पूर्णांक len);

पूर्णांक send_request_init(काष्ठा cc_drvdata *drvdata, काष्ठा cc_hw_desc *desc,
		      अचिन्हित पूर्णांक len);

व्योम complete_request(काष्ठा cc_drvdata *drvdata);

व्योम cc_req_mgr_fini(काष्ठा cc_drvdata *drvdata);

#पूर्ण_अगर /*__REQUEST_MGR_H__*/
