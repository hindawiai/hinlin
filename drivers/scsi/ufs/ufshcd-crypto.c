<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Google LLC
 */

#समावेश "ufshcd.h"
#समावेश "ufshcd-crypto.h"

/* Blk-crypto modes supported by UFS crypto */
अटल स्थिर काष्ठा ufs_crypto_alg_entry अणु
	क्रमागत ufs_crypto_alg ufs_alg;
	क्रमागत ufs_crypto_key_size ufs_key_size;
पूर्ण ufs_crypto_algs[BLK_ENCRYPTION_MODE_MAX] = अणु
	[BLK_ENCRYPTION_MODE_AES_256_XTS] = अणु
		.ufs_alg = UFS_CRYPTO_ALG_AES_XTS,
		.ufs_key_size = UFS_CRYPTO_KEY_SIZE_256,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ufshcd_program_key(काष्ठा ufs_hba *hba,
			      स्थिर जोड़ ufs_crypto_cfg_entry *cfg, पूर्णांक slot)
अणु
	पूर्णांक i;
	u32 slot_offset = hba->crypto_cfg_रेजिस्टर + slot * माप(*cfg);
	पूर्णांक err = 0;

	ufshcd_hold(hba, false);

	अगर (hba->vops && hba->vops->program_key) अणु
		err = hba->vops->program_key(hba, cfg, slot);
		जाओ out;
	पूर्ण

	/* Ensure that CFGE is cleared beक्रमe programming the key */
	ufshcd_ग_लिखोl(hba, 0, slot_offset + 16 * माप(cfg->reg_val[0]));
	क्रम (i = 0; i < 16; i++) अणु
		ufshcd_ग_लिखोl(hba, le32_to_cpu(cfg->reg_val[i]),
			      slot_offset + i * माप(cfg->reg_val[0]));
	पूर्ण
	/* Write dword 17 */
	ufshcd_ग_लिखोl(hba, le32_to_cpu(cfg->reg_val[17]),
		      slot_offset + 17 * माप(cfg->reg_val[0]));
	/* Dword 16 must be written last */
	ufshcd_ग_लिखोl(hba, le32_to_cpu(cfg->reg_val[16]),
		      slot_offset + 16 * माप(cfg->reg_val[0]));
out:
	ufshcd_release(hba);
	वापस err;
पूर्ण

अटल पूर्णांक ufshcd_crypto_keyslot_program(काष्ठा blk_keyslot_manager *ksm,
					 स्थिर काष्ठा blk_crypto_key *key,
					 अचिन्हित पूर्णांक slot)
अणु
	काष्ठा ufs_hba *hba = container_of(ksm, काष्ठा ufs_hba, ksm);
	स्थिर जोड़ ufs_crypto_cap_entry *ccap_array = hba->crypto_cap_array;
	स्थिर काष्ठा ufs_crypto_alg_entry *alg =
			&ufs_crypto_algs[key->crypto_cfg.crypto_mode];
	u8 data_unit_mask = key->crypto_cfg.data_unit_size / 512;
	पूर्णांक i;
	पूर्णांक cap_idx = -1;
	जोड़ ufs_crypto_cfg_entry cfg = अणुपूर्ण;
	पूर्णांक err;

	BUILD_BUG_ON(UFS_CRYPTO_KEY_SIZE_INVALID != 0);
	क्रम (i = 0; i < hba->crypto_capabilities.num_crypto_cap; i++) अणु
		अगर (ccap_array[i].algorithm_id == alg->ufs_alg &&
		    ccap_array[i].key_size == alg->ufs_key_size &&
		    (ccap_array[i].sdus_mask & data_unit_mask)) अणु
			cap_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(cap_idx < 0))
		वापस -EOPNOTSUPP;

	cfg.data_unit_size = data_unit_mask;
	cfg.crypto_cap_idx = cap_idx;
	cfg.config_enable = UFS_CRYPTO_CONFIGURATION_ENABLE;

	अगर (ccap_array[cap_idx].algorithm_id == UFS_CRYPTO_ALG_AES_XTS) अणु
		/* In XTS mode, the blk_crypto_key's size is alपढ़ोy द्विगुनd */
		स_नकल(cfg.crypto_key, key->raw, key->size/2);
		स_नकल(cfg.crypto_key + UFS_CRYPTO_KEY_MAX_SIZE/2,
		       key->raw + key->size/2, key->size/2);
	पूर्ण अन्यथा अणु
		स_नकल(cfg.crypto_key, key->raw, key->size);
	पूर्ण

	err = ufshcd_program_key(hba, &cfg, slot);

	memzero_explicit(&cfg, माप(cfg));
	वापस err;
पूर्ण

अटल पूर्णांक ufshcd_clear_keyslot(काष्ठा ufs_hba *hba, पूर्णांक slot)
अणु
	/*
	 * Clear the crypto cfg on the device. Clearing CFGE
	 * might not be sufficient, so just clear the entire cfg.
	 */
	जोड़ ufs_crypto_cfg_entry cfg = अणुपूर्ण;

	वापस ufshcd_program_key(hba, &cfg, slot);
पूर्ण

अटल पूर्णांक ufshcd_crypto_keyslot_evict(काष्ठा blk_keyslot_manager *ksm,
				       स्थिर काष्ठा blk_crypto_key *key,
				       अचिन्हित पूर्णांक slot)
अणु
	काष्ठा ufs_hba *hba = container_of(ksm, काष्ठा ufs_hba, ksm);

	वापस ufshcd_clear_keyslot(hba, slot);
पूर्ण

bool ufshcd_crypto_enable(काष्ठा ufs_hba *hba)
अणु
	अगर (!(hba->caps & UFSHCD_CAP_CRYPTO))
		वापस false;

	/* Reset might clear all keys, so reprogram all the keys. */
	blk_ksm_reprogram_all_keys(&hba->ksm);
	वापस true;
पूर्ण

अटल स्थिर काष्ठा blk_ksm_ll_ops ufshcd_ksm_ops = अणु
	.keyslot_program	= ufshcd_crypto_keyslot_program,
	.keyslot_evict		= ufshcd_crypto_keyslot_evict,
पूर्ण;

अटल क्रमागत blk_crypto_mode_num
ufshcd_find_blk_crypto_mode(जोड़ ufs_crypto_cap_entry cap)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ufs_crypto_algs); i++) अणु
		BUILD_BUG_ON(UFS_CRYPTO_KEY_SIZE_INVALID != 0);
		अगर (ufs_crypto_algs[i].ufs_alg == cap.algorithm_id &&
		    ufs_crypto_algs[i].ufs_key_size == cap.key_size) अणु
			वापस i;
		पूर्ण
	पूर्ण
	वापस BLK_ENCRYPTION_MODE_INVALID;
पूर्ण

/**
 * ufshcd_hba_init_crypto_capabilities - Read crypto capabilities, init crypto
 *					 fields in hba
 * @hba: Per adapter instance
 *
 * Return: 0 अगर crypto was initialized or is not supported, अन्यथा a -त्रुटि_सं value.
 */
पूर्णांक ufshcd_hba_init_crypto_capabilities(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक cap_idx;
	पूर्णांक err = 0;
	क्रमागत blk_crypto_mode_num blk_mode_num;

	/*
	 * Don't use crypto if either the hardware doesn't advertise the
	 * standard crypto capability bit *or* अगर the venकरोr specअगरic driver
	 * hasn't advertised that crypto is supported.
	 */
	अगर (!(hba->capabilities & MASK_CRYPTO_SUPPORT) ||
	    !(hba->caps & UFSHCD_CAP_CRYPTO))
		जाओ out;

	hba->crypto_capabilities.reg_val =
			cpu_to_le32(ufshcd_पढ़ोl(hba, REG_UFS_CCAP));
	hba->crypto_cfg_रेजिस्टर =
		(u32)hba->crypto_capabilities.config_array_ptr * 0x100;
	hba->crypto_cap_array =
		devm_kसुस्मृति(hba->dev, hba->crypto_capabilities.num_crypto_cap,
			     माप(hba->crypto_cap_array[0]), GFP_KERNEL);
	अगर (!hba->crypto_cap_array) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* The actual number of configurations supported is (CFGC+1) */
	err = devm_blk_ksm_init(hba->dev, &hba->ksm,
				hba->crypto_capabilities.config_count + 1);
	अगर (err)
		जाओ out;

	hba->ksm.ksm_ll_ops = ufshcd_ksm_ops;
	/* UFS only supports 8 bytes क्रम any DUN */
	hba->ksm.max_dun_bytes_supported = 8;
	hba->ksm.dev = hba->dev;

	/*
	 * Cache all the UFS crypto capabilities and advertise the supported
	 * crypto modes and data unit sizes to the block layer.
	 */
	क्रम (cap_idx = 0; cap_idx < hba->crypto_capabilities.num_crypto_cap;
	     cap_idx++) अणु
		hba->crypto_cap_array[cap_idx].reg_val =
			cpu_to_le32(ufshcd_पढ़ोl(hba,
						 REG_UFS_CRYPTOCAP +
						 cap_idx * माप(__le32)));
		blk_mode_num = ufshcd_find_blk_crypto_mode(
						hba->crypto_cap_array[cap_idx]);
		अगर (blk_mode_num != BLK_ENCRYPTION_MODE_INVALID)
			hba->ksm.crypto_modes_supported[blk_mode_num] |=
				hba->crypto_cap_array[cap_idx].sdus_mask * 512;
	पूर्ण

	वापस 0;

out:
	/* Indicate that init failed by clearing UFSHCD_CAP_CRYPTO */
	hba->caps &= ~UFSHCD_CAP_CRYPTO;
	वापस err;
पूर्ण

/**
 * ufshcd_init_crypto - Initialize crypto hardware
 * @hba: Per adapter instance
 */
व्योम ufshcd_init_crypto(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक slot;

	अगर (!(hba->caps & UFSHCD_CAP_CRYPTO))
		वापस;

	/* Clear all keyslots - the number of keyslots is (CFGC + 1) */
	क्रम (slot = 0; slot < hba->crypto_capabilities.config_count + 1; slot++)
		ufshcd_clear_keyslot(hba, slot);
पूर्ण

व्योम ufshcd_crypto_setup_rq_keyslot_manager(काष्ठा ufs_hba *hba,
					    काष्ठा request_queue *q)
अणु
	अगर (hba->caps & UFSHCD_CAP_CRYPTO)
		blk_ksm_रेजिस्टर(&hba->ksm, q);
पूर्ण
