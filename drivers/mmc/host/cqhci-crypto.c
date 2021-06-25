<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CQHCI crypto engine (अंतरभूत encryption) support
 *
 * Copyright 2020 Google LLC
 */

#समावेश <linux/blk-crypto.h>
#समावेश <linux/keyslot-manager.h>
#समावेश <linux/mmc/host.h>

#समावेश "cqhci-crypto.h"

/* Map from blk-crypto modes to CQHCI crypto algorithm IDs and key sizes */
अटल स्थिर काष्ठा cqhci_crypto_alg_entry अणु
	क्रमागत cqhci_crypto_alg alg;
	क्रमागत cqhci_crypto_key_size key_size;
पूर्ण cqhci_crypto_algs[BLK_ENCRYPTION_MODE_MAX] = अणु
	[BLK_ENCRYPTION_MODE_AES_256_XTS] = अणु
		.alg = CQHCI_CRYPTO_ALG_AES_XTS,
		.key_size = CQHCI_CRYPTO_KEY_SIZE_256,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा cqhci_host *
cqhci_host_from_ksm(काष्ठा blk_keyslot_manager *ksm)
अणु
	काष्ठा mmc_host *mmc = container_of(ksm, काष्ठा mmc_host, ksm);

	वापस mmc->cqe_निजी;
पूर्ण

अटल पूर्णांक cqhci_crypto_program_key(काष्ठा cqhci_host *cq_host,
				    स्थिर जोड़ cqhci_crypto_cfg_entry *cfg,
				    पूर्णांक slot)
अणु
	u32 slot_offset = cq_host->crypto_cfg_रेजिस्टर + slot * माप(*cfg);
	पूर्णांक i;

	अगर (cq_host->ops->program_key)
		वापस cq_host->ops->program_key(cq_host, cfg, slot);

	/* Clear CFGE */
	cqhci_ग_लिखोl(cq_host, 0, slot_offset + 16 * माप(cfg->reg_val[0]));

	/* Write the key */
	क्रम (i = 0; i < 16; i++) अणु
		cqhci_ग_लिखोl(cq_host, le32_to_cpu(cfg->reg_val[i]),
			     slot_offset + i * माप(cfg->reg_val[0]));
	पूर्ण
	/* Write dword 17 */
	cqhci_ग_लिखोl(cq_host, le32_to_cpu(cfg->reg_val[17]),
		     slot_offset + 17 * माप(cfg->reg_val[0]));
	/* Write dword 16, which includes the new value of CFGE */
	cqhci_ग_लिखोl(cq_host, le32_to_cpu(cfg->reg_val[16]),
		     slot_offset + 16 * माप(cfg->reg_val[0]));
	वापस 0;
पूर्ण

अटल पूर्णांक cqhci_crypto_keyslot_program(काष्ठा blk_keyslot_manager *ksm,
					स्थिर काष्ठा blk_crypto_key *key,
					अचिन्हित पूर्णांक slot)

अणु
	काष्ठा cqhci_host *cq_host = cqhci_host_from_ksm(ksm);
	स्थिर जोड़ cqhci_crypto_cap_entry *ccap_array =
		cq_host->crypto_cap_array;
	स्थिर काष्ठा cqhci_crypto_alg_entry *alg =
			&cqhci_crypto_algs[key->crypto_cfg.crypto_mode];
	u8 data_unit_mask = key->crypto_cfg.data_unit_size / 512;
	पूर्णांक i;
	पूर्णांक cap_idx = -1;
	जोड़ cqhci_crypto_cfg_entry cfg = अणुपूर्ण;
	पूर्णांक err;

	BUILD_BUG_ON(CQHCI_CRYPTO_KEY_SIZE_INVALID != 0);
	क्रम (i = 0; i < cq_host->crypto_capabilities.num_crypto_cap; i++) अणु
		अगर (ccap_array[i].algorithm_id == alg->alg &&
		    ccap_array[i].key_size == alg->key_size &&
		    (ccap_array[i].sdus_mask & data_unit_mask)) अणु
			cap_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (WARN_ON(cap_idx < 0))
		वापस -EOPNOTSUPP;

	cfg.data_unit_size = data_unit_mask;
	cfg.crypto_cap_idx = cap_idx;
	cfg.config_enable = CQHCI_CRYPTO_CONFIGURATION_ENABLE;

	अगर (ccap_array[cap_idx].algorithm_id == CQHCI_CRYPTO_ALG_AES_XTS) अणु
		/* In XTS mode, the blk_crypto_key's size is alपढ़ोy द्विगुनd */
		स_नकल(cfg.crypto_key, key->raw, key->size/2);
		स_नकल(cfg.crypto_key + CQHCI_CRYPTO_KEY_MAX_SIZE/2,
		       key->raw + key->size/2, key->size/2);
	पूर्ण अन्यथा अणु
		स_नकल(cfg.crypto_key, key->raw, key->size);
	पूर्ण

	err = cqhci_crypto_program_key(cq_host, &cfg, slot);

	memzero_explicit(&cfg, माप(cfg));
	वापस err;
पूर्ण

अटल पूर्णांक cqhci_crypto_clear_keyslot(काष्ठा cqhci_host *cq_host, पूर्णांक slot)
अणु
	/*
	 * Clear the crypto cfg on the device. Clearing CFGE
	 * might not be sufficient, so just clear the entire cfg.
	 */
	जोड़ cqhci_crypto_cfg_entry cfg = अणुपूर्ण;

	वापस cqhci_crypto_program_key(cq_host, &cfg, slot);
पूर्ण

अटल पूर्णांक cqhci_crypto_keyslot_evict(काष्ठा blk_keyslot_manager *ksm,
				      स्थिर काष्ठा blk_crypto_key *key,
				      अचिन्हित पूर्णांक slot)
अणु
	काष्ठा cqhci_host *cq_host = cqhci_host_from_ksm(ksm);

	वापस cqhci_crypto_clear_keyslot(cq_host, slot);
पूर्ण

/*
 * The keyslot management operations क्रम CQHCI crypto.
 *
 * Note that the block layer ensures that these are never called जबतक the host
 * controller is runसमय-suspended.  However, the CQE won't necessarily be
 * "enabled" when these are called, i.e. CQHCI_ENABLE might not be set in the
 * CQHCI_CFG रेजिस्टर.  But the hardware allows that.
 */
अटल स्थिर काष्ठा blk_ksm_ll_ops cqhci_ksm_ops = अणु
	.keyslot_program	= cqhci_crypto_keyslot_program,
	.keyslot_evict		= cqhci_crypto_keyslot_evict,
पूर्ण;

अटल क्रमागत blk_crypto_mode_num
cqhci_find_blk_crypto_mode(जोड़ cqhci_crypto_cap_entry cap)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cqhci_crypto_algs); i++) अणु
		BUILD_BUG_ON(CQHCI_CRYPTO_KEY_SIZE_INVALID != 0);
		अगर (cqhci_crypto_algs[i].alg == cap.algorithm_id &&
		    cqhci_crypto_algs[i].key_size == cap.key_size)
			वापस i;
	पूर्ण
	वापस BLK_ENCRYPTION_MODE_INVALID;
पूर्ण

/**
 * cqhci_crypto_init - initialize CQHCI crypto support
 * @cq_host: a cqhci host
 *
 * If the driver previously set MMC_CAP2_CRYPTO and the CQE declares
 * CQHCI_CAP_CS, initialize the crypto support.  This involves पढ़ोing the
 * crypto capability रेजिस्टरs, initializing the keyslot manager, clearing all
 * keyslots, and enabling 128-bit task descriptors.
 *
 * Return: 0 अगर crypto was initialized or isn't supported; whether
 *	   MMC_CAP2_CRYPTO reमुख्यs set indicates which one of those हालs it is.
 *	   Also can वापस a negative त्रुटि_सं value on unexpected error.
 */
पूर्णांक cqhci_crypto_init(काष्ठा cqhci_host *cq_host)
अणु
	काष्ठा mmc_host *mmc = cq_host->mmc;
	काष्ठा device *dev = mmc_dev(mmc);
	काष्ठा blk_keyslot_manager *ksm = &mmc->ksm;
	अचिन्हित पूर्णांक num_keyslots;
	अचिन्हित पूर्णांक cap_idx;
	क्रमागत blk_crypto_mode_num blk_mode_num;
	अचिन्हित पूर्णांक slot;
	पूर्णांक err = 0;

	अगर (!(mmc->caps2 & MMC_CAP2_CRYPTO) ||
	    !(cqhci_पढ़ोl(cq_host, CQHCI_CAP) & CQHCI_CAP_CS))
		जाओ out;

	cq_host->crypto_capabilities.reg_val =
			cpu_to_le32(cqhci_पढ़ोl(cq_host, CQHCI_CCAP));

	cq_host->crypto_cfg_रेजिस्टर =
		(u32)cq_host->crypto_capabilities.config_array_ptr * 0x100;

	cq_host->crypto_cap_array =
		devm_kसुस्मृति(dev, cq_host->crypto_capabilities.num_crypto_cap,
			     माप(cq_host->crypto_cap_array[0]), GFP_KERNEL);
	अगर (!cq_host->crypto_cap_array) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * CCAP.CFGC is off by one, so the actual number of crypto
	 * configurations (a.k.a. keyslots) is CCAP.CFGC + 1.
	 */
	num_keyslots = cq_host->crypto_capabilities.config_count + 1;

	err = devm_blk_ksm_init(dev, ksm, num_keyslots);
	अगर (err)
		जाओ out;

	ksm->ksm_ll_ops = cqhci_ksm_ops;
	ksm->dev = dev;

	/* Unक्रमtunately, CQHCI crypto only supports 32 DUN bits. */
	ksm->max_dun_bytes_supported = 4;

	/*
	 * Cache all the crypto capabilities and advertise the supported crypto
	 * modes and data unit sizes to the block layer.
	 */
	क्रम (cap_idx = 0; cap_idx < cq_host->crypto_capabilities.num_crypto_cap;
	     cap_idx++) अणु
		cq_host->crypto_cap_array[cap_idx].reg_val =
			cpu_to_le32(cqhci_पढ़ोl(cq_host,
						CQHCI_CRYPTOCAP +
						cap_idx * माप(__le32)));
		blk_mode_num = cqhci_find_blk_crypto_mode(
					cq_host->crypto_cap_array[cap_idx]);
		अगर (blk_mode_num == BLK_ENCRYPTION_MODE_INVALID)
			जारी;
		ksm->crypto_modes_supported[blk_mode_num] |=
			cq_host->crypto_cap_array[cap_idx].sdus_mask * 512;
	पूर्ण

	/* Clear all the keyslots so that we start in a known state. */
	क्रम (slot = 0; slot < num_keyslots; slot++)
		cqhci_crypto_clear_keyslot(cq_host, slot);

	/* CQHCI crypto requires the use of 128-bit task descriptors. */
	cq_host->caps |= CQHCI_TASK_DESC_SZ_128;

	वापस 0;

out:
	mmc->caps2 &= ~MMC_CAP2_CRYPTO;
	वापस err;
पूर्ण
