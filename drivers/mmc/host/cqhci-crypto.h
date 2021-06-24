<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * CQHCI crypto engine (अंतरभूत encryption) support
 *
 * Copyright 2020 Google LLC
 */

#अगर_अघोषित LINUX_MMC_CQHCI_CRYPTO_H
#घोषणा LINUX_MMC_CQHCI_CRYPTO_H

#समावेश <linux/mmc/host.h>

#समावेश "cqhci.h"

#अगर_घोषित CONFIG_MMC_CRYPTO

पूर्णांक cqhci_crypto_init(काष्ठा cqhci_host *host);

/*
 * Returns the crypto bits that should be set in bits 64-127 of the
 * task descriptor.
 */
अटल अंतरभूत u64 cqhci_crypto_prep_task_desc(काष्ठा mmc_request *mrq)
अणु
	अगर (!mrq->crypto_enabled)
		वापस 0;

	वापस CQHCI_CRYPTO_ENABLE_BIT |
	       CQHCI_CRYPTO_KEYSLOT(mrq->crypto_key_slot) |
	       mrq->data_unit_num;
पूर्ण

#अन्यथा /* CONFIG_MMC_CRYPTO */

अटल अंतरभूत पूर्णांक cqhci_crypto_init(काष्ठा cqhci_host *host)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u64 cqhci_crypto_prep_task_desc(काष्ठा mmc_request *mrq)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_MMC_CRYPTO */

#पूर्ण_अगर /* LINUX_MMC_CQHCI_CRYPTO_H */
