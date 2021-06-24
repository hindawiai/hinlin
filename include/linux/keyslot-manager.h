<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2019 Google LLC
 */

#अगर_अघोषित __LINUX_KEYSLOT_MANAGER_H
#घोषणा __LINUX_KEYSLOT_MANAGER_H

#समावेश <linux/bपन.स>
#समावेश <linux/blk-crypto.h>

काष्ठा blk_keyslot_manager;

/**
 * काष्ठा blk_ksm_ll_ops - functions to manage keyslots in hardware
 * @keyslot_program:	Program the specअगरied key पूर्णांकo the specअगरied slot in the
 *			अंतरभूत encryption hardware.
 * @keyslot_evict:	Evict key from the specअगरied keyslot in the hardware.
 *			The key is provided so that e.g. dm layers can evict
 *			keys from the devices that they map over.
 *			Returns 0 on success, -त्रुटि_सं otherwise.
 *
 * This काष्ठाure should be provided by storage device drivers when they set up
 * a keyslot manager - this काष्ठाure holds the function ptrs that the keyslot
 * manager will use to manipulate keyslots in the hardware.
 */
काष्ठा blk_ksm_ll_ops अणु
	पूर्णांक (*keyslot_program)(काष्ठा blk_keyslot_manager *ksm,
			       स्थिर काष्ठा blk_crypto_key *key,
			       अचिन्हित पूर्णांक slot);
	पूर्णांक (*keyslot_evict)(काष्ठा blk_keyslot_manager *ksm,
			     स्थिर काष्ठा blk_crypto_key *key,
			     अचिन्हित पूर्णांक slot);
पूर्ण;

काष्ठा blk_keyslot_manager अणु
	/*
	 * The काष्ठा blk_ksm_ll_ops that this keyslot manager will use
	 * to perक्रमm operations like programming and evicting keys on the
	 * device
	 */
	काष्ठा blk_ksm_ll_ops ksm_ll_ops;

	/*
	 * The maximum number of bytes supported क्रम specअगरying the data unit
	 * number.
	 */
	अचिन्हित पूर्णांक max_dun_bytes_supported;

	/*
	 * Array of size BLK_ENCRYPTION_MODE_MAX of biपंचांगasks that represents
	 * whether a crypto mode and data unit size are supported. The i'th
	 * bit of crypto_mode_supported[crypto_mode] is set अगरf a data unit
	 * size of (1 << i) is supported. We only support data unit sizes
	 * that are घातers of 2.
	 */
	अचिन्हित पूर्णांक crypto_modes_supported[BLK_ENCRYPTION_MODE_MAX];

	/* Device क्रम runसमय घातer management (शून्य अगर none) */
	काष्ठा device *dev;

	/* Here onwards are *निजी* fields क्रम पूर्णांकernal keyslot manager use */

	अचिन्हित पूर्णांक num_slots;

	/* Protects programming and evicting keys from the device */
	काष्ठा rw_semaphore lock;

	/* List of idle slots, with least recently used slot at front */
	रुको_queue_head_t idle_slots_रुको_queue;
	काष्ठा list_head idle_slots;
	spinlock_t idle_slots_lock;

	/*
	 * Hash table which maps काष्ठा *blk_crypto_key to keyslots, so that we
	 * can find a key's keyslot in O(1) समय rather than O(num_slots).
	 * Protected by 'lock'.
	 */
	काष्ठा hlist_head *slot_hashtable;
	अचिन्हित पूर्णांक log_slot_ht_size;

	/* Per-keyslot data */
	काष्ठा blk_ksm_keyslot *slots;
पूर्ण;

पूर्णांक blk_ksm_init(काष्ठा blk_keyslot_manager *ksm, अचिन्हित पूर्णांक num_slots);

पूर्णांक devm_blk_ksm_init(काष्ठा device *dev, काष्ठा blk_keyslot_manager *ksm,
		      अचिन्हित पूर्णांक num_slots);

blk_status_t blk_ksm_get_slot_क्रम_key(काष्ठा blk_keyslot_manager *ksm,
				      स्थिर काष्ठा blk_crypto_key *key,
				      काष्ठा blk_ksm_keyslot **slot_ptr);

अचिन्हित पूर्णांक blk_ksm_get_slot_idx(काष्ठा blk_ksm_keyslot *slot);

व्योम blk_ksm_put_slot(काष्ठा blk_ksm_keyslot *slot);

bool blk_ksm_crypto_cfg_supported(काष्ठा blk_keyslot_manager *ksm,
				  स्थिर काष्ठा blk_crypto_config *cfg);

पूर्णांक blk_ksm_evict_key(काष्ठा blk_keyslot_manager *ksm,
		      स्थिर काष्ठा blk_crypto_key *key);

व्योम blk_ksm_reprogram_all_keys(काष्ठा blk_keyslot_manager *ksm);

व्योम blk_ksm_destroy(काष्ठा blk_keyslot_manager *ksm);

व्योम blk_ksm_पूर्णांकersect_modes(काष्ठा blk_keyslot_manager *parent,
			     स्थिर काष्ठा blk_keyslot_manager *child);

व्योम blk_ksm_init_passthrough(काष्ठा blk_keyslot_manager *ksm);

bool blk_ksm_is_superset(काष्ठा blk_keyslot_manager *ksm_superset,
			 काष्ठा blk_keyslot_manager *ksm_subset);

व्योम blk_ksm_update_capabilities(काष्ठा blk_keyslot_manager *target_ksm,
				 काष्ठा blk_keyslot_manager *reference_ksm);

#पूर्ण_अगर /* __LINUX_KEYSLOT_MANAGER_H */
