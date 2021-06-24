<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Google LLC
 */

/**
 * DOC: The Keyslot Manager
 *
 * Many devices with अंतरभूत encryption support have a limited number of "slots"
 * पूर्णांकo which encryption contexts may be programmed, and requests can be tagged
 * with a slot number to specअगरy the key to use क्रम en/decryption.
 *
 * As the number of slots is limited, and programming keys is expensive on
 * many अंतरभूत encryption hardware, we करोn't want to program the same key पूर्णांकo
 * multiple slots - अगर multiple requests are using the same key, we want to
 * program just one slot with that key and use that slot क्रम all requests.
 *
 * The keyslot manager manages these keyslots appropriately, and also acts as
 * an असलtraction between the अंतरभूत encryption hardware and the upper layers.
 *
 * Lower layer devices will set up a keyslot manager in their request queue
 * and tell it how to perक्रमm device specअगरic operations like programming/
 * evicting keys from keyslots.
 *
 * Upper layers will call blk_ksm_get_slot_क्रम_key() to program a
 * key पूर्णांकo some slot in the अंतरभूत encryption hardware.
 */

#घोषणा pr_fmt(fmt) "blk-crypto: " fmt

#समावेश <linux/keyslot-manager.h>
#समावेश <linux/device.h>
#समावेश <linux/atomic.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/blkdev.h>

काष्ठा blk_ksm_keyslot अणु
	atomic_t slot_refs;
	काष्ठा list_head idle_slot_node;
	काष्ठा hlist_node hash_node;
	स्थिर काष्ठा blk_crypto_key *key;
	काष्ठा blk_keyslot_manager *ksm;
पूर्ण;

अटल अंतरभूत व्योम blk_ksm_hw_enter(काष्ठा blk_keyslot_manager *ksm)
अणु
	/*
	 * Calling पूर्णांकo the driver requires ksm->lock held and the device
	 * resumed.  But we must resume the device first, since that can acquire
	 * and release ksm->lock via blk_ksm_reprogram_all_keys().
	 */
	अगर (ksm->dev)
		pm_runसमय_get_sync(ksm->dev);
	करोwn_ग_लिखो(&ksm->lock);
पूर्ण

अटल अंतरभूत व्योम blk_ksm_hw_निकास(काष्ठा blk_keyslot_manager *ksm)
अणु
	up_ग_लिखो(&ksm->lock);
	अगर (ksm->dev)
		pm_runसमय_put_sync(ksm->dev);
पूर्ण

अटल अंतरभूत bool blk_ksm_is_passthrough(काष्ठा blk_keyslot_manager *ksm)
अणु
	वापस ksm->num_slots == 0;
पूर्ण

/**
 * blk_ksm_init() - Initialize a keyslot manager
 * @ksm: The keyslot_manager to initialize.
 * @num_slots: The number of key slots to manage.
 *
 * Allocate memory क्रम keyslots and initialize a keyslot manager. Called by
 * e.g. storage drivers to set up a keyslot manager in their request_queue.
 *
 * Return: 0 on success, or अन्यथा a negative error code.
 */
पूर्णांक blk_ksm_init(काष्ठा blk_keyslot_manager *ksm, अचिन्हित पूर्णांक num_slots)
अणु
	अचिन्हित पूर्णांक slot;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक slot_hashtable_size;

	स_रखो(ksm, 0, माप(*ksm));

	अगर (num_slots == 0)
		वापस -EINVAL;

	ksm->slots = kvसुस्मृति(num_slots, माप(ksm->slots[0]), GFP_KERNEL);
	अगर (!ksm->slots)
		वापस -ENOMEM;

	ksm->num_slots = num_slots;

	init_rwsem(&ksm->lock);

	init_रुकोqueue_head(&ksm->idle_slots_रुको_queue);
	INIT_LIST_HEAD(&ksm->idle_slots);

	क्रम (slot = 0; slot < num_slots; slot++) अणु
		ksm->slots[slot].ksm = ksm;
		list_add_tail(&ksm->slots[slot].idle_slot_node,
			      &ksm->idle_slots);
	पूर्ण

	spin_lock_init(&ksm->idle_slots_lock);

	slot_hashtable_size = roundup_घात_of_two(num_slots);
	/*
	 * hash_ptr() assumes bits != 0, so ensure the hash table has at least 2
	 * buckets.  This only makes a dअगरference when there is only 1 keyslot.
	 */
	अगर (slot_hashtable_size < 2)
		slot_hashtable_size = 2;

	ksm->log_slot_ht_size = ilog2(slot_hashtable_size);
	ksm->slot_hashtable = kvदो_स्मृति_array(slot_hashtable_size,
					     माप(ksm->slot_hashtable[0]),
					     GFP_KERNEL);
	अगर (!ksm->slot_hashtable)
		जाओ err_destroy_ksm;
	क्रम (i = 0; i < slot_hashtable_size; i++)
		INIT_HLIST_HEAD(&ksm->slot_hashtable[i]);

	वापस 0;

err_destroy_ksm:
	blk_ksm_destroy(ksm);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(blk_ksm_init);

अटल व्योम blk_ksm_destroy_callback(व्योम *ksm)
अणु
	blk_ksm_destroy(ksm);
पूर्ण

/**
 * devm_blk_ksm_init() - Resource-managed blk_ksm_init()
 * @dev: The device which owns the blk_keyslot_manager.
 * @ksm: The blk_keyslot_manager to initialize.
 * @num_slots: The number of key slots to manage.
 *
 * Like blk_ksm_init(), but causes blk_ksm_destroy() to be called स्वतःmatically
 * on driver detach.
 *
 * Return: 0 on success, or अन्यथा a negative error code.
 */
पूर्णांक devm_blk_ksm_init(काष्ठा device *dev, काष्ठा blk_keyslot_manager *ksm,
		      अचिन्हित पूर्णांक num_slots)
अणु
	पूर्णांक err = blk_ksm_init(ksm, num_slots);

	अगर (err)
		वापस err;

	वापस devm_add_action_or_reset(dev, blk_ksm_destroy_callback, ksm);
पूर्ण
EXPORT_SYMBOL_GPL(devm_blk_ksm_init);

अटल अंतरभूत काष्ठा hlist_head *
blk_ksm_hash_bucket_क्रम_key(काष्ठा blk_keyslot_manager *ksm,
			    स्थिर काष्ठा blk_crypto_key *key)
अणु
	वापस &ksm->slot_hashtable[hash_ptr(key, ksm->log_slot_ht_size)];
पूर्ण

अटल व्योम blk_ksm_हटाओ_slot_from_lru_list(काष्ठा blk_ksm_keyslot *slot)
अणु
	काष्ठा blk_keyslot_manager *ksm = slot->ksm;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ksm->idle_slots_lock, flags);
	list_del(&slot->idle_slot_node);
	spin_unlock_irqrestore(&ksm->idle_slots_lock, flags);
पूर्ण

अटल काष्ठा blk_ksm_keyslot *blk_ksm_find_keyslot(
					काष्ठा blk_keyslot_manager *ksm,
					स्थिर काष्ठा blk_crypto_key *key)
अणु
	स्थिर काष्ठा hlist_head *head = blk_ksm_hash_bucket_क्रम_key(ksm, key);
	काष्ठा blk_ksm_keyslot *slotp;

	hlist_क्रम_each_entry(slotp, head, hash_node) अणु
		अगर (slotp->key == key)
			वापस slotp;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा blk_ksm_keyslot *blk_ksm_find_and_grab_keyslot(
					काष्ठा blk_keyslot_manager *ksm,
					स्थिर काष्ठा blk_crypto_key *key)
अणु
	काष्ठा blk_ksm_keyslot *slot;

	slot = blk_ksm_find_keyslot(ksm, key);
	अगर (!slot)
		वापस शून्य;
	अगर (atomic_inc_वापस(&slot->slot_refs) == 1) अणु
		/* Took first reference to this slot; हटाओ it from LRU list */
		blk_ksm_हटाओ_slot_from_lru_list(slot);
	पूर्ण
	वापस slot;
पूर्ण

अचिन्हित पूर्णांक blk_ksm_get_slot_idx(काष्ठा blk_ksm_keyslot *slot)
अणु
	वापस slot - slot->ksm->slots;
पूर्ण
EXPORT_SYMBOL_GPL(blk_ksm_get_slot_idx);

/**
 * blk_ksm_get_slot_क्रम_key() - Program a key पूर्णांकo a keyslot.
 * @ksm: The keyslot manager to program the key पूर्णांकo.
 * @key: Poपूर्णांकer to the key object to program, including the raw key, crypto
 *	 mode, and data unit size.
 * @slot_ptr: A poपूर्णांकer to वापस the poपूर्णांकer of the allocated keyslot.
 *
 * Get a keyslot that's been programmed with the specअगरied key.  If one alपढ़ोy
 * exists, वापस it with incremented refcount.  Otherwise, रुको क्रम a keyslot
 * to become idle and program it.
 *
 * Context: Process context. Takes and releases ksm->lock.
 * Return: BLK_STS_OK on success (and keyslot is set to the poपूर्णांकer of the
 *	   allocated keyslot), or some other blk_status_t otherwise (and
 *	   keyslot is set to शून्य).
 */
blk_status_t blk_ksm_get_slot_क्रम_key(काष्ठा blk_keyslot_manager *ksm,
				      स्थिर काष्ठा blk_crypto_key *key,
				      काष्ठा blk_ksm_keyslot **slot_ptr)
अणु
	काष्ठा blk_ksm_keyslot *slot;
	पूर्णांक slot_idx;
	पूर्णांक err;

	*slot_ptr = शून्य;

	अगर (blk_ksm_is_passthrough(ksm))
		वापस BLK_STS_OK;

	करोwn_पढ़ो(&ksm->lock);
	slot = blk_ksm_find_and_grab_keyslot(ksm, key);
	up_पढ़ो(&ksm->lock);
	अगर (slot)
		जाओ success;

	क्रम (;;) अणु
		blk_ksm_hw_enter(ksm);
		slot = blk_ksm_find_and_grab_keyslot(ksm, key);
		अगर (slot) अणु
			blk_ksm_hw_निकास(ksm);
			जाओ success;
		पूर्ण

		/*
		 * If we're here, that means there wasn't a slot that was
		 * alपढ़ोy programmed with the key. So try to program it.
		 */
		अगर (!list_empty(&ksm->idle_slots))
			अवरोध;

		blk_ksm_hw_निकास(ksm);
		रुको_event(ksm->idle_slots_रुको_queue,
			   !list_empty(&ksm->idle_slots));
	पूर्ण

	slot = list_first_entry(&ksm->idle_slots, काष्ठा blk_ksm_keyslot,
				idle_slot_node);
	slot_idx = blk_ksm_get_slot_idx(slot);

	err = ksm->ksm_ll_ops.keyslot_program(ksm, key, slot_idx);
	अगर (err) अणु
		wake_up(&ksm->idle_slots_रुको_queue);
		blk_ksm_hw_निकास(ksm);
		वापस त्रुटि_सं_to_blk_status(err);
	पूर्ण

	/* Move this slot to the hash list क्रम the new key. */
	अगर (slot->key)
		hlist_del(&slot->hash_node);
	slot->key = key;
	hlist_add_head(&slot->hash_node, blk_ksm_hash_bucket_क्रम_key(ksm, key));

	atomic_set(&slot->slot_refs, 1);

	blk_ksm_हटाओ_slot_from_lru_list(slot);

	blk_ksm_hw_निकास(ksm);
success:
	*slot_ptr = slot;
	वापस BLK_STS_OK;
पूर्ण

/**
 * blk_ksm_put_slot() - Release a reference to a slot
 * @slot: The keyslot to release the reference of.
 *
 * Context: Any context.
 */
व्योम blk_ksm_put_slot(काष्ठा blk_ksm_keyslot *slot)
अणु
	काष्ठा blk_keyslot_manager *ksm;
	अचिन्हित दीर्घ flags;

	अगर (!slot)
		वापस;

	ksm = slot->ksm;

	अगर (atomic_dec_and_lock_irqsave(&slot->slot_refs,
					&ksm->idle_slots_lock, flags)) अणु
		list_add_tail(&slot->idle_slot_node, &ksm->idle_slots);
		spin_unlock_irqrestore(&ksm->idle_slots_lock, flags);
		wake_up(&ksm->idle_slots_रुको_queue);
	पूर्ण
पूर्ण

/**
 * blk_ksm_crypto_cfg_supported() - Find out अगर a crypto configuration is
 *				    supported by a ksm.
 * @ksm: The keyslot manager to check
 * @cfg: The crypto configuration to check क्रम.
 *
 * Checks क्रम crypto_mode/data unit size/dun bytes support.
 *
 * Return: Whether or not this ksm supports the specअगरied crypto config.
 */
bool blk_ksm_crypto_cfg_supported(काष्ठा blk_keyslot_manager *ksm,
				  स्थिर काष्ठा blk_crypto_config *cfg)
अणु
	अगर (!ksm)
		वापस false;
	अगर (!(ksm->crypto_modes_supported[cfg->crypto_mode] &
	      cfg->data_unit_size))
		वापस false;
	अगर (ksm->max_dun_bytes_supported < cfg->dun_bytes)
		वापस false;
	वापस true;
पूर्ण

/**
 * blk_ksm_evict_key() - Evict a key from the lower layer device.
 * @ksm: The keyslot manager to evict from
 * @key: The key to evict
 *
 * Find the keyslot that the specअगरied key was programmed पूर्णांकo, and evict that
 * slot from the lower layer device. The slot must not be in use by any
 * in-flight IO when this function is called.
 *
 * Context: Process context. Takes and releases ksm->lock.
 * Return: 0 on success or अगर there's no keyslot with the specअगरied key, -EBUSY
 *	   अगर the keyslot is still in use, or another -त्रुटि_सं value on other
 *	   error.
 */
पूर्णांक blk_ksm_evict_key(काष्ठा blk_keyslot_manager *ksm,
		      स्थिर काष्ठा blk_crypto_key *key)
अणु
	काष्ठा blk_ksm_keyslot *slot;
	पूर्णांक err = 0;

	अगर (blk_ksm_is_passthrough(ksm)) अणु
		अगर (ksm->ksm_ll_ops.keyslot_evict) अणु
			blk_ksm_hw_enter(ksm);
			err = ksm->ksm_ll_ops.keyslot_evict(ksm, key, -1);
			blk_ksm_hw_निकास(ksm);
			वापस err;
		पूर्ण
		वापस 0;
	पूर्ण

	blk_ksm_hw_enter(ksm);
	slot = blk_ksm_find_keyslot(ksm, key);
	अगर (!slot)
		जाओ out_unlock;

	अगर (WARN_ON_ONCE(atomic_पढ़ो(&slot->slot_refs) != 0)) अणु
		err = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	err = ksm->ksm_ll_ops.keyslot_evict(ksm, key,
					    blk_ksm_get_slot_idx(slot));
	अगर (err)
		जाओ out_unlock;

	hlist_del(&slot->hash_node);
	slot->key = शून्य;
	err = 0;
out_unlock:
	blk_ksm_hw_निकास(ksm);
	वापस err;
पूर्ण

/**
 * blk_ksm_reprogram_all_keys() - Re-program all keyslots.
 * @ksm: The keyslot manager
 *
 * Re-program all keyslots that are supposed to have a key programmed.  This is
 * पूर्णांकended only क्रम use by drivers क्रम hardware that loses its keys on reset.
 *
 * Context: Process context. Takes and releases ksm->lock.
 */
व्योम blk_ksm_reprogram_all_keys(काष्ठा blk_keyslot_manager *ksm)
अणु
	अचिन्हित पूर्णांक slot;

	अगर (blk_ksm_is_passthrough(ksm))
		वापस;

	/* This is क्रम device initialization, so करोn't resume the device */
	करोwn_ग_लिखो(&ksm->lock);
	क्रम (slot = 0; slot < ksm->num_slots; slot++) अणु
		स्थिर काष्ठा blk_crypto_key *key = ksm->slots[slot].key;
		पूर्णांक err;

		अगर (!key)
			जारी;

		err = ksm->ksm_ll_ops.keyslot_program(ksm, key, slot);
		WARN_ON(err);
	पूर्ण
	up_ग_लिखो(&ksm->lock);
पूर्ण
EXPORT_SYMBOL_GPL(blk_ksm_reprogram_all_keys);

व्योम blk_ksm_destroy(काष्ठा blk_keyslot_manager *ksm)
अणु
	अगर (!ksm)
		वापस;
	kvमुक्त(ksm->slot_hashtable);
	kvमुक्त_sensitive(ksm->slots, माप(ksm->slots[0]) * ksm->num_slots);
	memzero_explicit(ksm, माप(*ksm));
पूर्ण
EXPORT_SYMBOL_GPL(blk_ksm_destroy);

bool blk_ksm_रेजिस्टर(काष्ठा blk_keyslot_manager *ksm, काष्ठा request_queue *q)
अणु
	अगर (blk_पूर्णांकegrity_queue_supports_पूर्णांकegrity(q)) अणु
		pr_warn("Integrity and hardware inline encryption are not supported together. Disabling hardware inline encryption.\n");
		वापस false;
	पूर्ण
	q->ksm = ksm;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(blk_ksm_रेजिस्टर);

व्योम blk_ksm_unरेजिस्टर(काष्ठा request_queue *q)
अणु
	q->ksm = शून्य;
पूर्ण

/**
 * blk_ksm_पूर्णांकersect_modes() - restrict supported modes by child device
 * @parent: The keyslot manager क्रम parent device
 * @child: The keyslot manager क्रम child device, or शून्य
 *
 * Clear any crypto mode support bits in @parent that aren't set in @child.
 * If @child is शून्य, then all parent bits are cleared.
 *
 * Only use this when setting up the keyslot manager क्रम a layered device,
 * beक्रमe it's been exposed yet.
 */
व्योम blk_ksm_पूर्णांकersect_modes(काष्ठा blk_keyslot_manager *parent,
			     स्थिर काष्ठा blk_keyslot_manager *child)
अणु
	अगर (child) अणु
		अचिन्हित पूर्णांक i;

		parent->max_dun_bytes_supported =
			min(parent->max_dun_bytes_supported,
			    child->max_dun_bytes_supported);
		क्रम (i = 0; i < ARRAY_SIZE(child->crypto_modes_supported);
		     i++) अणु
			parent->crypto_modes_supported[i] &=
				child->crypto_modes_supported[i];
		पूर्ण
	पूर्ण अन्यथा अणु
		parent->max_dun_bytes_supported = 0;
		स_रखो(parent->crypto_modes_supported, 0,
		       माप(parent->crypto_modes_supported));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(blk_ksm_पूर्णांकersect_modes);

/**
 * blk_ksm_is_superset() - Check अगर a KSM supports a superset of crypto modes
 *			   and DUN bytes that another KSM supports. Here,
 *			   "superset" refers to the mathematical meaning of the
 *			   word - i.e. अगर two KSMs have the *same* capabilities,
 *			   they *are* considered supersets of each other.
 * @ksm_superset: The KSM that we want to verअगरy is a superset
 * @ksm_subset: The KSM that we want to verअगरy is a subset
 *
 * Return: True अगर @ksm_superset supports a superset of the crypto modes and DUN
 *	   bytes that @ksm_subset supports.
 */
bool blk_ksm_is_superset(काष्ठा blk_keyslot_manager *ksm_superset,
			 काष्ठा blk_keyslot_manager *ksm_subset)
अणु
	पूर्णांक i;

	अगर (!ksm_subset)
		वापस true;

	अगर (!ksm_superset)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(ksm_superset->crypto_modes_supported); i++) अणु
		अगर (ksm_subset->crypto_modes_supported[i] &
		    (~ksm_superset->crypto_modes_supported[i])) अणु
			वापस false;
		पूर्ण
	पूर्ण

	अगर (ksm_subset->max_dun_bytes_supported >
	    ksm_superset->max_dun_bytes_supported) अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(blk_ksm_is_superset);

/**
 * blk_ksm_update_capabilities() - Update the restrictions of a KSM to those of
 *				   another KSM
 * @target_ksm: The KSM whose restrictions to update.
 * @reference_ksm: The KSM to whose restrictions this function will update
 *		   @target_ksm's restrictions to.
 *
 * Blk-crypto requires that crypto capabilities that were
 * advertised when a bio was created जारी to be supported by the
 * device until that bio is ended. This is turn means that a device cannot
 * shrink its advertised crypto capabilities without any explicit
 * synchronization with upper layers. So अगर there's no such explicit
 * synchronization, @reference_ksm must support all the crypto capabilities that
 * @target_ksm करोes
 * (i.e. we need blk_ksm_is_superset(@reference_ksm, @target_ksm) == true).
 *
 * Note also that as दीर्घ as the crypto capabilities are being expanded, the
 * order of updates becoming visible is not important because it's alright
 * क्रम blk-crypto to see stale values - they only cause blk-crypto to
 * believe that a crypto capability isn't supported when it actually is (which
 * might result in blk-crypto-fallback being used अगर available, or the bio being
 * failed).
 */
व्योम blk_ksm_update_capabilities(काष्ठा blk_keyslot_manager *target_ksm,
				 काष्ठा blk_keyslot_manager *reference_ksm)
अणु
	स_नकल(target_ksm->crypto_modes_supported,
	       reference_ksm->crypto_modes_supported,
	       माप(target_ksm->crypto_modes_supported));

	target_ksm->max_dun_bytes_supported =
				reference_ksm->max_dun_bytes_supported;
पूर्ण
EXPORT_SYMBOL_GPL(blk_ksm_update_capabilities);

/**
 * blk_ksm_init_passthrough() - Init a passthrough keyslot manager
 * @ksm: The keyslot manager to init
 *
 * Initialize a passthrough keyslot manager.
 * Called by e.g. storage drivers to set up a keyslot manager in their
 * request_queue, when the storage driver wants to manage its keys by itself.
 * This is useful क्रम अंतरभूत encryption hardware that करोesn't have the concept
 * of keyslots, and क्रम layered devices.
 */
व्योम blk_ksm_init_passthrough(काष्ठा blk_keyslot_manager *ksm)
अणु
	स_रखो(ksm, 0, माप(*ksm));
	init_rwsem(&ksm->lock);
पूर्ण
EXPORT_SYMBOL_GPL(blk_ksm_init_passthrough);
