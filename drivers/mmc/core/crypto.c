<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MMC crypto engine (अंतरभूत encryption) support
 *
 * Copyright 2020 Google LLC
 */

#समावेश <linux/blk-crypto.h>
#समावेश <linux/mmc/host.h>

#समावेश "core.h"
#समावेश "crypto.h"
#समावेश "queue.h"

व्योम mmc_crypto_set_initial_state(काष्ठा mmc_host *host)
अणु
	/* Reset might clear all keys, so reprogram all the keys. */
	अगर (host->caps2 & MMC_CAP2_CRYPTO)
		blk_ksm_reprogram_all_keys(&host->ksm);
पूर्ण

व्योम mmc_crypto_setup_queue(काष्ठा request_queue *q, काष्ठा mmc_host *host)
अणु
	अगर (host->caps2 & MMC_CAP2_CRYPTO)
		blk_ksm_रेजिस्टर(&host->ksm, q);
पूर्ण
EXPORT_SYMBOL_GPL(mmc_crypto_setup_queue);

व्योम mmc_crypto_prepare_req(काष्ठा mmc_queue_req *mqrq)
अणु
	काष्ठा request *req = mmc_queue_req_to_req(mqrq);
	काष्ठा mmc_request *mrq = &mqrq->brq.mrq;

	अगर (!req->crypt_keyslot)
		वापस;

	mrq->crypto_enabled = true;
	mrq->crypto_key_slot = blk_ksm_get_slot_idx(req->crypt_keyslot);

	/*
	 * For now we assume that all MMC drivers set max_dun_bytes_supported=4,
	 * which is the limit क्रम CQHCI crypto.  So all DUNs should be 32-bit.
	 */
	WARN_ON_ONCE(req->crypt_ctx->bc_dun[0] > U32_MAX);

	mrq->data_unit_num = req->crypt_ctx->bc_dun[0];
पूर्ण
EXPORT_SYMBOL_GPL(mmc_crypto_prepare_req);
