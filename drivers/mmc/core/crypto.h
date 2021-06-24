<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MMC crypto engine (अंतरभूत encryption) support
 *
 * Copyright 2020 Google LLC
 */

#अगर_अघोषित _MMC_CORE_CRYPTO_H
#घोषणा _MMC_CORE_CRYPTO_H

काष्ठा mmc_host;
काष्ठा mmc_queue_req;
काष्ठा request_queue;

#अगर_घोषित CONFIG_MMC_CRYPTO

व्योम mmc_crypto_set_initial_state(काष्ठा mmc_host *host);

व्योम mmc_crypto_setup_queue(काष्ठा request_queue *q, काष्ठा mmc_host *host);

व्योम mmc_crypto_prepare_req(काष्ठा mmc_queue_req *mqrq);

#अन्यथा /* CONFIG_MMC_CRYPTO */

अटल अंतरभूत व्योम mmc_crypto_set_initial_state(काष्ठा mmc_host *host)
अणु
पूर्ण

अटल अंतरभूत व्योम mmc_crypto_setup_queue(काष्ठा request_queue *q,
					  काष्ठा mmc_host *host)
अणु
पूर्ण

अटल अंतरभूत व्योम mmc_crypto_prepare_req(काष्ठा mmc_queue_req *mqrq)
अणु
पूर्ण

#पूर्ण_अगर /* !CONFIG_MMC_CRYPTO */

#पूर्ण_अगर /* _MMC_CORE_CRYPTO_H */
