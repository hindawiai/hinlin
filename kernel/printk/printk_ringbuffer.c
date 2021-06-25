<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/kernel.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश "printk_ringbuffer.h"

/**
 * DOC: prपूर्णांकk_ringbuffer overview
 *
 * Data Structure
 * --------------
 * The prपूर्णांकk_ringbuffer is made up of 3 पूर्णांकernal ringbuffers:
 *
 *   desc_ring
 *     A ring of descriptors and their meta data (such as sequence number,
 *     बारtamp, loglevel, etc.) as well as पूर्णांकernal state inक्रमmation about
 *     the record and logical positions specअगरying where in the other
 *     ringbuffer the text strings are located.
 *
 *   text_data_ring
 *     A ring of data blocks. A data block consists of an अचिन्हित दीर्घ
 *     पूर्णांकeger (ID) that maps to a desc_ring index followed by the text
 *     string of the record.
 *
 * The पूर्णांकernal state inक्रमmation of a descriptor is the key element to allow
 * पढ़ोers and ग_लिखोrs to locklessly synchronize access to the data.
 *
 * Implementation
 * --------------
 *
 * Descriptor Ring
 * ~~~~~~~~~~~~~~~
 * The descriptor ring is an array of descriptors. A descriptor contains
 * essential meta data to track the data of a prपूर्णांकk record using
 * blk_lpos काष्ठाs poपूर्णांकing to associated text data blocks (see
 * "Data Rings" below). Each descriptor is asचिन्हित an ID that maps
 * directly to index values of the descriptor array and has a state. The ID
 * and the state are bitwise combined पूर्णांकo a single descriptor field named
 * @state_var, allowing ID and state to be synchronously and atomically
 * updated.
 *
 * Descriptors have four states:
 *
 *   reserved
 *     A ग_लिखोr is modअगरying the record.
 *
 *   committed
 *     The record and all its data are written. A ग_लिखोr can reखोलो the
 *     descriptor (transitioning it back to reserved), but in the committed
 *     state the data is consistent.
 *
 *   finalized
 *     The record and all its data are complete and available क्रम पढ़ोing. A
 *     ग_लिखोr cannot reखोलो the descriptor.
 *
 *   reusable
 *     The record exists, but its text and/or meta data may no दीर्घer be
 *     available.
 *
 * Querying the @state_var of a record requires providing the ID of the
 * descriptor to query. This can yield a possible fअगरth (pseuकरो) state:
 *
 *   miss
 *     The descriptor being queried has an unexpected ID.
 *
 * The descriptor ring has a @tail_id that contains the ID of the oldest
 * descriptor and @head_id that contains the ID of the newest descriptor.
 *
 * When a new descriptor should be created (and the ring is full), the tail
 * descriptor is invalidated by first transitioning to the reusable state and
 * then invalidating all tail data blocks up to and including the data blocks
 * associated with the tail descriptor (क्रम the text ring). Then
 * @tail_id is advanced, followed by advancing @head_id. And finally the
 * @state_var of the new descriptor is initialized to the new ID and reserved
 * state.
 *
 * The @tail_id can only be advanced अगर the new @tail_id would be in the
 * committed or reusable queried state. This makes it possible that a valid
 * sequence number of the tail is always available.
 *
 * Descriptor Finalization
 * ~~~~~~~~~~~~~~~~~~~~~~~
 * When a ग_लिखोr calls the commit function prb_commit(), record data is
 * fully stored and is consistent within the ringbuffer. However, a ग_लिखोr can
 * reखोलो that record, claiming exclusive access (as with prb_reserve()), and
 * modअगरy that record. When finished, the ग_लिखोr must again commit the record.
 *
 * In order क्रम a record to be made available to पढ़ोers (and also become
 * recyclable क्रम ग_लिखोrs), it must be finalized. A finalized record cannot be
 * reखोलोed and can never become "unfinalized". Record finalization can occur
 * in three dअगरferent scenarios:
 *
 *   1) A ग_लिखोr can simultaneously commit and finalize its record by calling
 *      prb_final_commit() instead of prb_commit().
 *
 *   2) When a new record is reserved and the previous record has been
 *      committed via prb_commit(), that previous record is स्वतःmatically
 *      finalized.
 *
 *   3) When a record is committed via prb_commit() and a newer record
 *      alपढ़ोy exists, the record being committed is स्वतःmatically finalized.
 *
 * Data Ring
 * ~~~~~~~~~
 * The text data ring is a byte array composed of data blocks. Data blocks are
 * referenced by blk_lpos काष्ठाs that poपूर्णांक to the logical position of the
 * beginning of a data block and the beginning of the next adjacent data
 * block. Logical positions are mapped directly to index values of the byte
 * array ringbuffer.
 *
 * Each data block consists of an ID followed by the ग_लिखोr data. The ID is
 * the identअगरier of a descriptor that is associated with the data block. A
 * given data block is considered valid अगर all of the following conditions
 * are met:
 *
 *   1) The descriptor associated with the data block is in the committed
 *      or finalized queried state.
 *
 *   2) The blk_lpos काष्ठा within the descriptor associated with the data
 *      block references back to the same data block.
 *
 *   3) The data block is within the head/tail logical position range.
 *
 * If the ग_लिखोr data of a data block would extend beyond the end of the
 * byte array, only the ID of the data block is stored at the logical
 * position and the full data block (ID and ग_लिखोr data) is stored at the
 * beginning of the byte array. The referencing blk_lpos will poपूर्णांक to the
 * ID beक्रमe the wrap and the next data block will be at the logical
 * position adjacent the full data block after the wrap.
 *
 * Data rings have a @tail_lpos that poपूर्णांकs to the beginning of the oldest
 * data block and a @head_lpos that poपूर्णांकs to the logical position of the
 * next (not yet existing) data block.
 *
 * When a new data block should be created (and the ring is full), tail data
 * blocks will first be invalidated by putting their associated descriptors
 * पूर्णांकo the reusable state and then pushing the @tail_lpos क्रमward beyond
 * them. Then the @head_lpos is pushed क्रमward and is associated with a new
 * descriptor. If a data block is not valid, the @tail_lpos cannot be
 * advanced beyond it.
 *
 * Info Array
 * ~~~~~~~~~~
 * The general meta data of prपूर्णांकk records are stored in prपूर्णांकk_info काष्ठाs,
 * stored in an array with the same number of elements as the descriptor ring.
 * Each info corresponds to the descriptor of the same index in the
 * descriptor ring. Info validity is confirmed by evaluating the corresponding
 * descriptor beक्रमe and after loading the info.
 *
 * Usage
 * -----
 * Here are some simple examples demonstrating ग_लिखोrs and पढ़ोers. For the
 * examples a global ringbuffer (test_rb) is available (which is not the
 * actual ringbuffer used by prपूर्णांकk)::
 *
 *	DEFINE_PRINTKRB(test_rb, 15, 5);
 *
 * This ringbuffer allows up to 32768 records (2 ^ 15) and has a size of
 * 1 MiB (2 ^ (15 + 5)) क्रम text data.
 *
 * Sample ग_लिखोr code::
 *
 *	स्थिर अक्षर *textstr = "message text";
 *	काष्ठा prb_reserved_entry e;
 *	काष्ठा prपूर्णांकk_record r;
 *
 *	// specअगरy how much to allocate
 *	prb_rec_init_wr(&r, म_माप(textstr) + 1);
 *
 *	अगर (prb_reserve(&e, &test_rb, &r)) अणु
 *		snम_लिखो(r.text_buf, r.text_buf_size, "%s", textstr);
 *
 *		r.info->text_len = म_माप(textstr);
 *		r.info->ts_nsec = local_घड़ी();
 *		r.info->caller_id = prपूर्णांकk_caller_id();
 *
 *		// commit and finalize the record
 *		prb_final_commit(&e);
 *	पूर्ण
 *
 * Note that additional ग_लिखोr functions are available to extend a record
 * after it has been committed but not yet finalized. This can be करोne as
 * दीर्घ as no new records have been reserved and the caller is the same.
 *
 * Sample ग_लिखोr code (record extending)::
 *
 *		// alternate rest of previous example
 *
 *		r.info->text_len = म_माप(textstr);
 *		r.info->ts_nsec = local_घड़ी();
 *		r.info->caller_id = prपूर्णांकk_caller_id();
 *
 *		// commit the record (but करो not finalize yet)
 *		prb_commit(&e);
 *	पूर्ण
 *
 *	...
 *
 *	// specअगरy additional 5 bytes text space to extend
 *	prb_rec_init_wr(&r, 5);
 *
 *	// try to extend, but only अगर it करोes not exceed 32 bytes
 *	अगर (prb_reserve_in_last(&e, &test_rb, &r, prपूर्णांकk_caller_id()), 32) अणु
 *		snम_लिखो(&r.text_buf[r.info->text_len],
 *			 r.text_buf_size - r.info->text_len, "hello");
 *
 *		r.info->text_len += 5;
 *
 *		// commit and finalize the record
 *		prb_final_commit(&e);
 *	पूर्ण
 *
 * Sample पढ़ोer code::
 *
 *	काष्ठा prपूर्णांकk_info info;
 *	काष्ठा prपूर्णांकk_record r;
 *	अक्षर text_buf[32];
 *	u64 seq;
 *
 *	prb_rec_init_rd(&r, &info, &text_buf[0], माप(text_buf));
 *
 *	prb_क्रम_each_record(0, &test_rb, &seq, &r) अणु
 *		अगर (info.seq != seq)
 *			pr_warn("lost %llu records\n", info.seq - seq);
 *
 *		अगर (info.text_len > r.text_buf_size) अणु
 *			pr_warn("record %llu text truncated\n", info.seq);
 *			text_buf[r.text_buf_size - 1] = 0;
 *		पूर्ण
 *
 *		pr_info("%llu: %llu: %s\n", info.seq, info.ts_nsec,
 *			&text_buf[0]);
 *	पूर्ण
 *
 * Note that additional less convenient पढ़ोer functions are available to
 * allow complex record access.
 *
 * ABA Issues
 * ~~~~~~~~~~
 * To help aव्योम ABA issues, descriptors are referenced by IDs (array index
 * values combined with tagged bits counting array wraps) and data blocks are
 * referenced by logical positions (array index values combined with tagged
 * bits counting array wraps). However, on 32-bit प्रणालीs the number of
 * tagged bits is relatively small such that an ABA incident is (at least
 * theoretically) possible. For example, अगर 4 million maximally sized (1KiB)
 * prपूर्णांकk messages were to occur in NMI context on a 32-bit प्रणाली, the
 * पूर्णांकerrupted context would not be able to recognize that the 32-bit पूर्णांकeger
 * completely wrapped and thus represents a dअगरferent data block than the one
 * the पूर्णांकerrupted context expects.
 *
 * To help combat this possibility, additional state checking is perक्रमmed
 * (such as using cmpxchg() even though set() would suffice). These extra
 * checks are commented as such and will hopefully catch any ABA issue that
 * a 32-bit प्रणाली might experience.
 *
 * Memory Barriers
 * ~~~~~~~~~~~~~~~
 * Multiple memory barriers are used. To simplअगरy proving correctness and
 * generating liपंचांगus tests, lines of code related to memory barriers
 * (loads, stores, and the associated memory barriers) are labeled::
 *
 *	LMM(function:letter)
 *
 * Comments reference the labels using only the "function:letter" part.
 *
 * The memory barrier pairs and their ordering are:
 *
 *   desc_reserve:D / desc_reserve:B
 *     push descriptor tail (id), then push descriptor head (id)
 *
 *   desc_reserve:D / data_push_tail:B
 *     push data tail (lpos), then set new descriptor reserved (state)
 *
 *   desc_reserve:D / desc_push_tail:C
 *     push descriptor tail (id), then set new descriptor reserved (state)
 *
 *   desc_reserve:D / prb_first_seq:C
 *     push descriptor tail (id), then set new descriptor reserved (state)
 *
 *   desc_reserve:F / desc_पढ़ो:D
 *     set new descriptor id and reserved (state), then allow ग_लिखोr changes
 *
 *   data_alloc:A (or data_पुनः_स्मृति:A) / desc_पढ़ो:D
 *     set old descriptor reusable (state), then modअगरy new data block area
 *
 *   data_alloc:A (or data_पुनः_स्मृति:A) / data_push_tail:B
 *     push data tail (lpos), then modअगरy new data block area
 *
 *   _prb_commit:B / desc_पढ़ो:B
 *     store ग_लिखोr changes, then set new descriptor committed (state)
 *
 *   desc_reखोलो_last:A / _prb_commit:B
 *     set descriptor reserved (state), then पढ़ो descriptor data
 *
 *   _prb_commit:B / desc_reserve:D
 *     set new descriptor committed (state), then check descriptor head (id)
 *
 *   data_push_tail:D / data_push_tail:A
 *     set descriptor reusable (state), then push data tail (lpos)
 *
 *   desc_push_tail:B / desc_reserve:D
 *     set descriptor reusable (state), then push descriptor tail (id)
 */

#घोषणा DATA_SIZE(data_ring)		_DATA_SIZE((data_ring)->size_bits)
#घोषणा DATA_SIZE_MASK(data_ring)	(DATA_SIZE(data_ring) - 1)

#घोषणा DESCS_COUNT(desc_ring)		_DESCS_COUNT((desc_ring)->count_bits)
#घोषणा DESCS_COUNT_MASK(desc_ring)	(DESCS_COUNT(desc_ring) - 1)

/* Determine the data array index from a logical position. */
#घोषणा DATA_INDEX(data_ring, lpos)	((lpos) & DATA_SIZE_MASK(data_ring))

/* Determine the desc array index from an ID or sequence number. */
#घोषणा DESC_INDEX(desc_ring, n)	((n) & DESCS_COUNT_MASK(desc_ring))

/* Determine how many बार the data array has wrapped. */
#घोषणा DATA_WRAPS(data_ring, lpos)	((lpos) >> (data_ring)->size_bits)

/* Determine अगर a logical position refers to a data-less block. */
#घोषणा LPOS_DATALESS(lpos)		((lpos) & 1UL)
#घोषणा BLK_DATALESS(blk)		(LPOS_DATALESS((blk)->begin) && \
					 LPOS_DATALESS((blk)->next))

/* Get the logical position at index 0 of the current wrap. */
#घोषणा DATA_THIS_WRAP_START_LPOS(data_ring, lpos) \
((lpos) & ~DATA_SIZE_MASK(data_ring))

/* Get the ID क्रम the same index of the previous wrap as the given ID. */
#घोषणा DESC_ID_PREV_WRAP(desc_ring, id) \
DESC_ID((id) - DESCS_COUNT(desc_ring))

/*
 * A data block: mapped directly to the beginning of the data block area
 * specअगरied as a logical position within the data ring.
 *
 * @id:   the ID of the associated descriptor
 * @data: the ग_लिखोr data
 *
 * Note that the size of a data block is only known by its associated
 * descriptor.
 */
काष्ठा prb_data_block अणु
	अचिन्हित दीर्घ	id;
	अक्षर		data[];
पूर्ण;

/*
 * Return the descriptor associated with @n. @n can be either a
 * descriptor ID or a sequence number.
 */
अटल काष्ठा prb_desc *to_desc(काष्ठा prb_desc_ring *desc_ring, u64 n)
अणु
	वापस &desc_ring->descs[DESC_INDEX(desc_ring, n)];
पूर्ण

/*
 * Return the prपूर्णांकk_info associated with @n. @n can be either a
 * descriptor ID or a sequence number.
 */
अटल काष्ठा prपूर्णांकk_info *to_info(काष्ठा prb_desc_ring *desc_ring, u64 n)
अणु
	वापस &desc_ring->infos[DESC_INDEX(desc_ring, n)];
पूर्ण

अटल काष्ठा prb_data_block *to_block(काष्ठा prb_data_ring *data_ring,
				       अचिन्हित दीर्घ begin_lpos)
अणु
	वापस (व्योम *)&data_ring->data[DATA_INDEX(data_ring, begin_lpos)];
पूर्ण

/*
 * Increase the data size to account क्रम data block meta data plus any
 * padding so that the adjacent data block is aligned on the ID size.
 */
अटल अचिन्हित पूर्णांक to_blk_size(अचिन्हित पूर्णांक size)
अणु
	काष्ठा prb_data_block *db = शून्य;

	size += माप(*db);
	size = ALIGN(size, माप(db->id));
	वापस size;
पूर्ण

/*
 * Sanity checker क्रम reserve size. The ringbuffer code assumes that a data
 * block करोes not exceed the maximum possible size that could fit within the
 * ringbuffer. This function provides that basic size check so that the
 * assumption is safe.
 */
अटल bool data_check_size(काष्ठा prb_data_ring *data_ring, अचिन्हित पूर्णांक size)
अणु
	काष्ठा prb_data_block *db = शून्य;

	अगर (size == 0)
		वापस true;

	/*
	 * Ensure the alignment padded size could possibly fit in the data
	 * array. The largest possible data block must still leave room क्रम
	 * at least the ID of the next block.
	 */
	size = to_blk_size(size);
	अगर (size > DATA_SIZE(data_ring) - माप(db->id))
		वापस false;

	वापस true;
पूर्ण

/* Query the state of a descriptor. */
अटल क्रमागत desc_state get_desc_state(अचिन्हित दीर्घ id,
				      अचिन्हित दीर्घ state_val)
अणु
	अगर (id != DESC_ID(state_val))
		वापस desc_miss;

	वापस DESC_STATE(state_val);
पूर्ण

/*
 * Get a copy of a specअगरied descriptor and वापस its queried state. If the
 * descriptor is in an inconsistent state (miss or reserved), the caller can
 * only expect the descriptor's @state_var field to be valid.
 *
 * The sequence number and caller_id can be optionally retrieved. Like all
 * non-state_var data, they are only valid अगर the descriptor is in a
 * consistent state.
 */
अटल क्रमागत desc_state desc_पढ़ो(काष्ठा prb_desc_ring *desc_ring,
				 अचिन्हित दीर्घ id, काष्ठा prb_desc *desc_out,
				 u64 *seq_out, u32 *caller_id_out)
अणु
	काष्ठा prपूर्णांकk_info *info = to_info(desc_ring, id);
	काष्ठा prb_desc *desc = to_desc(desc_ring, id);
	atomic_दीर्घ_t *state_var = &desc->state_var;
	क्रमागत desc_state d_state;
	अचिन्हित दीर्घ state_val;

	/* Check the descriptor state. */
	state_val = atomic_दीर्घ_पढ़ो(state_var); /* LMM(desc_पढ़ो:A) */
	d_state = get_desc_state(id, state_val);
	अगर (d_state == desc_miss || d_state == desc_reserved) अणु
		/*
		 * The descriptor is in an inconsistent state. Set at least
		 * @state_var so that the caller can see the details of
		 * the inconsistent state.
		 */
		जाओ out;
	पूर्ण

	/*
	 * Guarantee the state is loaded beक्रमe copying the descriptor
	 * content. This aव्योमs copying obsolete descriptor content that might
	 * not apply to the descriptor state. This pairs with _prb_commit:B.
	 *
	 * Memory barrier involvement:
	 *
	 * If desc_पढ़ो:A पढ़ोs from _prb_commit:B, then desc_पढ़ो:C पढ़ोs
	 * from _prb_commit:A.
	 *
	 * Relies on:
	 *
	 * WMB from _prb_commit:A to _prb_commit:B
	 *    matching
	 * RMB from desc_पढ़ो:A to desc_पढ़ो:C
	 */
	smp_rmb(); /* LMM(desc_पढ़ो:B) */

	/*
	 * Copy the descriptor data. The data is not valid until the
	 * state has been re-checked. A स_नकल() क्रम all of @desc
	 * cannot be used because of the atomic_t @state_var field.
	 */
	स_नकल(&desc_out->text_blk_lpos, &desc->text_blk_lpos,
	       माप(desc_out->text_blk_lpos)); /* LMM(desc_पढ़ो:C) */
	अगर (seq_out)
		*seq_out = info->seq; /* also part of desc_पढ़ो:C */
	अगर (caller_id_out)
		*caller_id_out = info->caller_id; /* also part of desc_पढ़ो:C */

	/*
	 * 1. Guarantee the descriptor content is loaded beक्रमe re-checking
	 *    the state. This aव्योमs पढ़ोing an obsolete descriptor state
	 *    that may not apply to the copied content. This pairs with
	 *    desc_reserve:F.
	 *
	 *    Memory barrier involvement:
	 *
	 *    If desc_पढ़ो:C पढ़ोs from desc_reserve:G, then desc_पढ़ो:E
	 *    पढ़ोs from desc_reserve:F.
	 *
	 *    Relies on:
	 *
	 *    WMB from desc_reserve:F to desc_reserve:G
	 *       matching
	 *    RMB from desc_पढ़ो:C to desc_पढ़ो:E
	 *
	 * 2. Guarantee the record data is loaded beक्रमe re-checking the
	 *    state. This aव्योमs पढ़ोing an obsolete descriptor state that may
	 *    not apply to the copied data. This pairs with data_alloc:A and
	 *    data_पुनः_स्मृति:A.
	 *
	 *    Memory barrier involvement:
	 *
	 *    If copy_data:A पढ़ोs from data_alloc:B, then desc_पढ़ो:E
	 *    पढ़ोs from desc_make_reusable:A.
	 *
	 *    Relies on:
	 *
	 *    MB from desc_make_reusable:A to data_alloc:B
	 *       matching
	 *    RMB from desc_पढ़ो:C to desc_पढ़ो:E
	 *
	 *    Note: desc_make_reusable:A and data_alloc:B can be dअगरferent
	 *          CPUs. However, the data_alloc:B CPU (which perक्रमms the
	 *          full memory barrier) must have previously seen
	 *          desc_make_reusable:A.
	 */
	smp_rmb(); /* LMM(desc_पढ़ो:D) */

	/*
	 * The data has been copied. Return the current descriptor state,
	 * which may have changed since the load above.
	 */
	state_val = atomic_दीर्घ_पढ़ो(state_var); /* LMM(desc_पढ़ो:E) */
	d_state = get_desc_state(id, state_val);
out:
	atomic_दीर्घ_set(&desc_out->state_var, state_val);
	वापस d_state;
पूर्ण

/*
 * Take a specअगरied descriptor out of the finalized state by attempting
 * the transition from finalized to reusable. Either this context or some
 * other context will have been successful.
 */
अटल व्योम desc_make_reusable(काष्ठा prb_desc_ring *desc_ring,
			       अचिन्हित दीर्घ id)
अणु
	अचिन्हित दीर्घ val_finalized = DESC_SV(id, desc_finalized);
	अचिन्हित दीर्घ val_reusable = DESC_SV(id, desc_reusable);
	काष्ठा prb_desc *desc = to_desc(desc_ring, id);
	atomic_दीर्घ_t *state_var = &desc->state_var;

	atomic_दीर्घ_cmpxchg_relaxed(state_var, val_finalized,
				    val_reusable); /* LMM(desc_make_reusable:A) */
पूर्ण

/*
 * Given the text data ring, put the associated descriptor of each
 * data block from @lpos_begin until @lpos_end पूर्णांकo the reusable state.
 *
 * If there is any problem making the associated descriptor reusable, either
 * the descriptor has not yet been finalized or another ग_लिखोr context has
 * alपढ़ोy pushed the tail lpos past the problematic data block. Regardless,
 * on error the caller can re-load the tail lpos to determine the situation.
 */
अटल bool data_make_reusable(काष्ठा prपूर्णांकk_ringbuffer *rb,
			       अचिन्हित दीर्घ lpos_begin,
			       अचिन्हित दीर्घ lpos_end,
			       अचिन्हित दीर्घ *lpos_out)
अणु

	काष्ठा prb_data_ring *data_ring = &rb->text_data_ring;
	काष्ठा prb_desc_ring *desc_ring = &rb->desc_ring;
	काष्ठा prb_data_block *blk;
	क्रमागत desc_state d_state;
	काष्ठा prb_desc desc;
	काष्ठा prb_data_blk_lpos *blk_lpos = &desc.text_blk_lpos;
	अचिन्हित दीर्घ id;

	/* Loop until @lpos_begin has advanced to or beyond @lpos_end. */
	जबतक ((lpos_end - lpos_begin) - 1 < DATA_SIZE(data_ring)) अणु
		blk = to_block(data_ring, lpos_begin);

		/*
		 * Load the block ID from the data block. This is a data race
		 * against a ग_लिखोr that may have newly reserved this data
		 * area. If the loaded value matches a valid descriptor ID,
		 * the blk_lpos of that descriptor will be checked to make
		 * sure it poपूर्णांकs back to this data block. If the check fails,
		 * the data area has been recycled by another ग_लिखोr.
		 */
		id = blk->id; /* LMM(data_make_reusable:A) */

		d_state = desc_पढ़ो(desc_ring, id, &desc,
				    शून्य, शून्य); /* LMM(data_make_reusable:B) */

		चयन (d_state) अणु
		हाल desc_miss:
		हाल desc_reserved:
		हाल desc_committed:
			वापस false;
		हाल desc_finalized:
			/*
			 * This data block is invalid अगर the descriptor
			 * करोes not poपूर्णांक back to it.
			 */
			अगर (blk_lpos->begin != lpos_begin)
				वापस false;
			desc_make_reusable(desc_ring, id);
			अवरोध;
		हाल desc_reusable:
			/*
			 * This data block is invalid अगर the descriptor
			 * करोes not poपूर्णांक back to it.
			 */
			अगर (blk_lpos->begin != lpos_begin)
				वापस false;
			अवरोध;
		पूर्ण

		/* Advance @lpos_begin to the next data block. */
		lpos_begin = blk_lpos->next;
	पूर्ण

	*lpos_out = lpos_begin;
	वापस true;
पूर्ण

/*
 * Advance the data ring tail to at least @lpos. This function माला_दो
 * descriptors पूर्णांकo the reusable state अगर the tail is pushed beyond
 * their associated data block.
 */
अटल bool data_push_tail(काष्ठा prपूर्णांकk_ringbuffer *rb, अचिन्हित दीर्घ lpos)
अणु
	काष्ठा prb_data_ring *data_ring = &rb->text_data_ring;
	अचिन्हित दीर्घ tail_lpos_new;
	अचिन्हित दीर्घ tail_lpos;
	अचिन्हित दीर्घ next_lpos;

	/* If @lpos is from a data-less block, there is nothing to करो. */
	अगर (LPOS_DATALESS(lpos))
		वापस true;

	/*
	 * Any descriptor states that have transitioned to reusable due to the
	 * data tail being pushed to this loaded value will be visible to this
	 * CPU. This pairs with data_push_tail:D.
	 *
	 * Memory barrier involvement:
	 *
	 * If data_push_tail:A पढ़ोs from data_push_tail:D, then this CPU can
	 * see desc_make_reusable:A.
	 *
	 * Relies on:
	 *
	 * MB from desc_make_reusable:A to data_push_tail:D
	 *    matches
	 * READFROM from data_push_tail:D to data_push_tail:A
	 *    thus
	 * READFROM from desc_make_reusable:A to this CPU
	 */
	tail_lpos = atomic_दीर्घ_पढ़ो(&data_ring->tail_lpos); /* LMM(data_push_tail:A) */

	/*
	 * Loop until the tail lpos is at or beyond @lpos. This condition
	 * may alपढ़ोy be satisfied, resulting in no full memory barrier
	 * from data_push_tail:D being perक्रमmed. However, since this CPU
	 * sees the new tail lpos, any descriptor states that transitioned to
	 * the reusable state must alपढ़ोy be visible.
	 */
	जबतक ((lpos - tail_lpos) - 1 < DATA_SIZE(data_ring)) अणु
		/*
		 * Make all descriptors reusable that are associated with
		 * data blocks beक्रमe @lpos.
		 */
		अगर (!data_make_reusable(rb, tail_lpos, lpos, &next_lpos)) अणु
			/*
			 * 1. Guarantee the block ID loaded in
			 *    data_make_reusable() is perक्रमmed beक्रमe
			 *    reloading the tail lpos. The failed
			 *    data_make_reusable() may be due to a newly
			 *    recycled data area causing the tail lpos to
			 *    have been previously pushed. This pairs with
			 *    data_alloc:A and data_पुनः_स्मृति:A.
			 *
			 *    Memory barrier involvement:
			 *
			 *    If data_make_reusable:A पढ़ोs from data_alloc:B,
			 *    then data_push_tail:C पढ़ोs from
			 *    data_push_tail:D.
			 *
			 *    Relies on:
			 *
			 *    MB from data_push_tail:D to data_alloc:B
			 *       matching
			 *    RMB from data_make_reusable:A to
			 *    data_push_tail:C
			 *
			 *    Note: data_push_tail:D and data_alloc:B can be
			 *          dअगरferent CPUs. However, the data_alloc:B
			 *          CPU (which perक्रमms the full memory
			 *          barrier) must have previously seen
			 *          data_push_tail:D.
			 *
			 * 2. Guarantee the descriptor state loaded in
			 *    data_make_reusable() is perक्रमmed beक्रमe
			 *    reloading the tail lpos. The failed
			 *    data_make_reusable() may be due to a newly
			 *    recycled descriptor causing the tail lpos to
			 *    have been previously pushed. This pairs with
			 *    desc_reserve:D.
			 *
			 *    Memory barrier involvement:
			 *
			 *    If data_make_reusable:B पढ़ोs from
			 *    desc_reserve:F, then data_push_tail:C पढ़ोs
			 *    from data_push_tail:D.
			 *
			 *    Relies on:
			 *
			 *    MB from data_push_tail:D to desc_reserve:F
			 *       matching
			 *    RMB from data_make_reusable:B to
			 *    data_push_tail:C
			 *
			 *    Note: data_push_tail:D and desc_reserve:F can
			 *          be dअगरferent CPUs. However, the
			 *          desc_reserve:F CPU (which perक्रमms the
			 *          full memory barrier) must have previously
			 *          seen data_push_tail:D.
			 */
			smp_rmb(); /* LMM(data_push_tail:B) */

			tail_lpos_new = atomic_दीर्घ_पढ़ो(&data_ring->tail_lpos
							); /* LMM(data_push_tail:C) */
			अगर (tail_lpos_new == tail_lpos)
				वापस false;

			/* Another CPU pushed the tail. Try again. */
			tail_lpos = tail_lpos_new;
			जारी;
		पूर्ण

		/*
		 * Guarantee any descriptor states that have transitioned to
		 * reusable are stored beक्रमe pushing the tail lpos. A full
		 * memory barrier is needed since other CPUs may have made
		 * the descriptor states reusable. This pairs with
		 * data_push_tail:A.
		 */
		अगर (atomic_दीर्घ_try_cmpxchg(&data_ring->tail_lpos, &tail_lpos,
					    next_lpos)) अणु /* LMM(data_push_tail:D) */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/*
 * Advance the desc ring tail. This function advances the tail by one
 * descriptor, thus invalidating the oldest descriptor. Beक्रमe advancing
 * the tail, the tail descriptor is made reusable and all data blocks up to
 * and including the descriptor's data block are invalidated (i.e. the data
 * ring tail is pushed past the data block of the descriptor being made
 * reusable).
 */
अटल bool desc_push_tail(काष्ठा prपूर्णांकk_ringbuffer *rb,
			   अचिन्हित दीर्घ tail_id)
अणु
	काष्ठा prb_desc_ring *desc_ring = &rb->desc_ring;
	क्रमागत desc_state d_state;
	काष्ठा prb_desc desc;

	d_state = desc_पढ़ो(desc_ring, tail_id, &desc, शून्य, शून्य);

	चयन (d_state) अणु
	हाल desc_miss:
		/*
		 * If the ID is exactly 1 wrap behind the expected, it is
		 * in the process of being reserved by another ग_लिखोr and
		 * must be considered reserved.
		 */
		अगर (DESC_ID(atomic_दीर्घ_पढ़ो(&desc.state_var)) ==
		    DESC_ID_PREV_WRAP(desc_ring, tail_id)) अणु
			वापस false;
		पूर्ण

		/*
		 * The ID has changed. Another ग_लिखोr must have pushed the
		 * tail and recycled the descriptor alपढ़ोy. Success is
		 * वापसed because the caller is only पूर्णांकerested in the
		 * specअगरied tail being pushed, which it was.
		 */
		वापस true;
	हाल desc_reserved:
	हाल desc_committed:
		वापस false;
	हाल desc_finalized:
		desc_make_reusable(desc_ring, tail_id);
		अवरोध;
	हाल desc_reusable:
		अवरोध;
	पूर्ण

	/*
	 * Data blocks must be invalidated beक्रमe their associated
	 * descriptor can be made available क्रम recycling. Invalidating
	 * them later is not possible because there is no way to trust
	 * data blocks once their associated descriptor is gone.
	 */

	अगर (!data_push_tail(rb, desc.text_blk_lpos.next))
		वापस false;

	/*
	 * Check the next descriptor after @tail_id beक्रमe pushing the tail
	 * to it because the tail must always be in a finalized or reusable
	 * state. The implementation of prb_first_seq() relies on this.
	 *
	 * A successful पढ़ो implies that the next descriptor is less than or
	 * equal to @head_id so there is no risk of pushing the tail past the
	 * head.
	 */
	d_state = desc_पढ़ो(desc_ring, DESC_ID(tail_id + 1), &desc,
			    शून्य, शून्य); /* LMM(desc_push_tail:A) */

	अगर (d_state == desc_finalized || d_state == desc_reusable) अणु
		/*
		 * Guarantee any descriptor states that have transitioned to
		 * reusable are stored beक्रमe pushing the tail ID. This allows
		 * verअगरying the recycled descriptor state. A full memory
		 * barrier is needed since other CPUs may have made the
		 * descriptor states reusable. This pairs with desc_reserve:D.
		 */
		atomic_दीर्घ_cmpxchg(&desc_ring->tail_id, tail_id,
				    DESC_ID(tail_id + 1)); /* LMM(desc_push_tail:B) */
	पूर्ण अन्यथा अणु
		/*
		 * Guarantee the last state load from desc_पढ़ो() is beक्रमe
		 * reloading @tail_id in order to see a new tail ID in the
		 * हाल that the descriptor has been recycled. This pairs
		 * with desc_reserve:D.
		 *
		 * Memory barrier involvement:
		 *
		 * If desc_push_tail:A पढ़ोs from desc_reserve:F, then
		 * desc_push_tail:D पढ़ोs from desc_push_tail:B.
		 *
		 * Relies on:
		 *
		 * MB from desc_push_tail:B to desc_reserve:F
		 *    matching
		 * RMB from desc_push_tail:A to desc_push_tail:D
		 *
		 * Note: desc_push_tail:B and desc_reserve:F can be dअगरferent
		 *       CPUs. However, the desc_reserve:F CPU (which perक्रमms
		 *       the full memory barrier) must have previously seen
		 *       desc_push_tail:B.
		 */
		smp_rmb(); /* LMM(desc_push_tail:C) */

		/*
		 * Re-check the tail ID. The descriptor following @tail_id is
		 * not in an allowed tail state. But अगर the tail has since
		 * been moved by another CPU, then it करोes not matter.
		 */
		अगर (atomic_दीर्घ_पढ़ो(&desc_ring->tail_id) == tail_id) /* LMM(desc_push_tail:D) */
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Reserve a new descriptor, invalidating the oldest अगर necessary. */
अटल bool desc_reserve(काष्ठा prपूर्णांकk_ringbuffer *rb, अचिन्हित दीर्घ *id_out)
अणु
	काष्ठा prb_desc_ring *desc_ring = &rb->desc_ring;
	अचिन्हित दीर्घ prev_state_val;
	अचिन्हित दीर्घ id_prev_wrap;
	काष्ठा prb_desc *desc;
	अचिन्हित दीर्घ head_id;
	अचिन्हित दीर्घ id;

	head_id = atomic_दीर्घ_पढ़ो(&desc_ring->head_id); /* LMM(desc_reserve:A) */

	करो अणु
		id = DESC_ID(head_id + 1);
		id_prev_wrap = DESC_ID_PREV_WRAP(desc_ring, id);

		/*
		 * Guarantee the head ID is पढ़ो beक्रमe पढ़ोing the tail ID.
		 * Since the tail ID is updated beक्रमe the head ID, this
		 * guarantees that @id_prev_wrap is never ahead of the tail
		 * ID. This pairs with desc_reserve:D.
		 *
		 * Memory barrier involvement:
		 *
		 * If desc_reserve:A पढ़ोs from desc_reserve:D, then
		 * desc_reserve:C पढ़ोs from desc_push_tail:B.
		 *
		 * Relies on:
		 *
		 * MB from desc_push_tail:B to desc_reserve:D
		 *    matching
		 * RMB from desc_reserve:A to desc_reserve:C
		 *
		 * Note: desc_push_tail:B and desc_reserve:D can be dअगरferent
		 *       CPUs. However, the desc_reserve:D CPU (which perक्रमms
		 *       the full memory barrier) must have previously seen
		 *       desc_push_tail:B.
		 */
		smp_rmb(); /* LMM(desc_reserve:B) */

		अगर (id_prev_wrap == atomic_दीर्घ_पढ़ो(&desc_ring->tail_id
						    )) अणु /* LMM(desc_reserve:C) */
			/*
			 * Make space क्रम the new descriptor by
			 * advancing the tail.
			 */
			अगर (!desc_push_tail(rb, id_prev_wrap))
				वापस false;
		पूर्ण

		/*
		 * 1. Guarantee the tail ID is पढ़ो beक्रमe validating the
		 *    recycled descriptor state. A पढ़ो memory barrier is
		 *    sufficient क्रम this. This pairs with desc_push_tail:B.
		 *
		 *    Memory barrier involvement:
		 *
		 *    If desc_reserve:C पढ़ोs from desc_push_tail:B, then
		 *    desc_reserve:E पढ़ोs from desc_make_reusable:A.
		 *
		 *    Relies on:
		 *
		 *    MB from desc_make_reusable:A to desc_push_tail:B
		 *       matching
		 *    RMB from desc_reserve:C to desc_reserve:E
		 *
		 *    Note: desc_make_reusable:A and desc_push_tail:B can be
		 *          dअगरferent CPUs. However, the desc_push_tail:B CPU
		 *          (which perक्रमms the full memory barrier) must have
		 *          previously seen desc_make_reusable:A.
		 *
		 * 2. Guarantee the tail ID is stored beक्रमe storing the head
		 *    ID. This pairs with desc_reserve:B.
		 *
		 * 3. Guarantee any data ring tail changes are stored beक्रमe
		 *    recycling the descriptor. Data ring tail changes can
		 *    happen via desc_push_tail()->data_push_tail(). A full
		 *    memory barrier is needed since another CPU may have
		 *    pushed the data ring tails. This pairs with
		 *    data_push_tail:B.
		 *
		 * 4. Guarantee a new tail ID is stored beक्रमe recycling the
		 *    descriptor. A full memory barrier is needed since
		 *    another CPU may have pushed the tail ID. This pairs
		 *    with desc_push_tail:C and this also pairs with
		 *    prb_first_seq:C.
		 *
		 * 5. Guarantee the head ID is stored beक्रमe trying to
		 *    finalize the previous descriptor. This pairs with
		 *    _prb_commit:B.
		 */
	पूर्ण जबतक (!atomic_दीर्घ_try_cmpxchg(&desc_ring->head_id, &head_id,
					  id)); /* LMM(desc_reserve:D) */

	desc = to_desc(desc_ring, id);

	/*
	 * If the descriptor has been recycled, verअगरy the old state val.
	 * See "ABA Issues" about why this verअगरication is perक्रमmed.
	 */
	prev_state_val = atomic_दीर्घ_पढ़ो(&desc->state_var); /* LMM(desc_reserve:E) */
	अगर (prev_state_val &&
	    get_desc_state(id_prev_wrap, prev_state_val) != desc_reusable) अणु
		WARN_ON_ONCE(1);
		वापस false;
	पूर्ण

	/*
	 * Assign the descriptor a new ID and set its state to reserved.
	 * See "ABA Issues" about why cmpxchg() instead of set() is used.
	 *
	 * Guarantee the new descriptor ID and state is stored beक्रमe making
	 * any other changes. A ग_लिखो memory barrier is sufficient क्रम this.
	 * This pairs with desc_पढ़ो:D.
	 */
	अगर (!atomic_दीर्घ_try_cmpxchg(&desc->state_var, &prev_state_val,
			DESC_SV(id, desc_reserved))) अणु /* LMM(desc_reserve:F) */
		WARN_ON_ONCE(1);
		वापस false;
	पूर्ण

	/* Now data in @desc can be modअगरied: LMM(desc_reserve:G) */

	*id_out = id;
	वापस true;
पूर्ण

/* Determine the end of a data block. */
अटल अचिन्हित दीर्घ get_next_lpos(काष्ठा prb_data_ring *data_ring,
				   अचिन्हित दीर्घ lpos, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित दीर्घ begin_lpos;
	अचिन्हित दीर्घ next_lpos;

	begin_lpos = lpos;
	next_lpos = lpos + size;

	/* First check अगर the data block करोes not wrap. */
	अगर (DATA_WRAPS(data_ring, begin_lpos) == DATA_WRAPS(data_ring, next_lpos))
		वापस next_lpos;

	/* Wrapping data blocks store their data at the beginning. */
	वापस (DATA_THIS_WRAP_START_LPOS(data_ring, next_lpos) + size);
पूर्ण

/*
 * Allocate a new data block, invalidating the oldest data block(s)
 * अगर necessary. This function also associates the data block with
 * a specअगरied descriptor.
 */
अटल अक्षर *data_alloc(काष्ठा prपूर्णांकk_ringbuffer *rb, अचिन्हित पूर्णांक size,
			काष्ठा prb_data_blk_lpos *blk_lpos, अचिन्हित दीर्घ id)
अणु
	काष्ठा prb_data_ring *data_ring = &rb->text_data_ring;
	काष्ठा prb_data_block *blk;
	अचिन्हित दीर्घ begin_lpos;
	अचिन्हित दीर्घ next_lpos;

	अगर (size == 0) अणु
		/* Specअगरy a data-less block. */
		blk_lpos->begin = NO_LPOS;
		blk_lpos->next = NO_LPOS;
		वापस शून्य;
	पूर्ण

	size = to_blk_size(size);

	begin_lpos = atomic_दीर्घ_पढ़ो(&data_ring->head_lpos);

	करो अणु
		next_lpos = get_next_lpos(data_ring, begin_lpos, size);

		अगर (!data_push_tail(rb, next_lpos - DATA_SIZE(data_ring))) अणु
			/* Failed to allocate, specअगरy a data-less block. */
			blk_lpos->begin = FAILED_LPOS;
			blk_lpos->next = FAILED_LPOS;
			वापस शून्य;
		पूर्ण

		/*
		 * 1. Guarantee any descriptor states that have transitioned
		 *    to reusable are stored beक्रमe modअगरying the newly
		 *    allocated data area. A full memory barrier is needed
		 *    since other CPUs may have made the descriptor states
		 *    reusable. See data_push_tail:A about why the reusable
		 *    states are visible. This pairs with desc_पढ़ो:D.
		 *
		 * 2. Guarantee any updated tail lpos is stored beक्रमe
		 *    modअगरying the newly allocated data area. Another CPU may
		 *    be in data_make_reusable() and is पढ़ोing a block ID
		 *    from this area. data_make_reusable() can handle पढ़ोing
		 *    a garbage block ID value, but then it must be able to
		 *    load a new tail lpos. A full memory barrier is needed
		 *    since other CPUs may have updated the tail lpos. This
		 *    pairs with data_push_tail:B.
		 */
	पूर्ण जबतक (!atomic_दीर्घ_try_cmpxchg(&data_ring->head_lpos, &begin_lpos,
					  next_lpos)); /* LMM(data_alloc:A) */

	blk = to_block(data_ring, begin_lpos);
	blk->id = id; /* LMM(data_alloc:B) */

	अगर (DATA_WRAPS(data_ring, begin_lpos) != DATA_WRAPS(data_ring, next_lpos)) अणु
		/* Wrapping data blocks store their data at the beginning. */
		blk = to_block(data_ring, 0);

		/*
		 * Store the ID on the wrapped block क्रम consistency.
		 * The prपूर्णांकk_ringbuffer करोes not actually use it.
		 */
		blk->id = id;
	पूर्ण

	blk_lpos->begin = begin_lpos;
	blk_lpos->next = next_lpos;

	वापस &blk->data[0];
पूर्ण

/*
 * Try to resize an existing data block associated with the descriptor
 * specअगरied by @id. If the resized data block should become wrapped, it
 * copies the old data to the new data block. If @size yields a data block
 * with the same or less size, the data block is left as is.
 *
 * Fail अगर this is not the last allocated data block or अगर there is not
 * enough space or it is not possible make enough space.
 *
 * Return a poपूर्णांकer to the beginning of the entire data buffer or शून्य on
 * failure.
 */
अटल अक्षर *data_पुनः_स्मृति(काष्ठा prपूर्णांकk_ringbuffer *rb, अचिन्हित पूर्णांक size,
			  काष्ठा prb_data_blk_lpos *blk_lpos, अचिन्हित दीर्घ id)
अणु
	काष्ठा prb_data_ring *data_ring = &rb->text_data_ring;
	काष्ठा prb_data_block *blk;
	अचिन्हित दीर्घ head_lpos;
	अचिन्हित दीर्घ next_lpos;
	bool wrapped;

	/* Reallocation only works अगर @blk_lpos is the newest data block. */
	head_lpos = atomic_दीर्घ_पढ़ो(&data_ring->head_lpos);
	अगर (head_lpos != blk_lpos->next)
		वापस शून्य;

	/* Keep track अगर @blk_lpos was a wrapping data block. */
	wrapped = (DATA_WRAPS(data_ring, blk_lpos->begin) != DATA_WRAPS(data_ring, blk_lpos->next));

	size = to_blk_size(size);

	next_lpos = get_next_lpos(data_ring, blk_lpos->begin, size);

	/* If the data block करोes not increase, there is nothing to करो. */
	अगर (head_lpos - next_lpos < DATA_SIZE(data_ring)) अणु
		अगर (wrapped)
			blk = to_block(data_ring, 0);
		अन्यथा
			blk = to_block(data_ring, blk_lpos->begin);
		वापस &blk->data[0];
	पूर्ण

	अगर (!data_push_tail(rb, next_lpos - DATA_SIZE(data_ring)))
		वापस शून्य;

	/* The memory barrier involvement is the same as data_alloc:A. */
	अगर (!atomic_दीर्घ_try_cmpxchg(&data_ring->head_lpos, &head_lpos,
				     next_lpos)) अणु /* LMM(data_पुनः_स्मृति:A) */
		वापस शून्य;
	पूर्ण

	blk = to_block(data_ring, blk_lpos->begin);

	अगर (DATA_WRAPS(data_ring, blk_lpos->begin) != DATA_WRAPS(data_ring, next_lpos)) अणु
		काष्ठा prb_data_block *old_blk = blk;

		/* Wrapping data blocks store their data at the beginning. */
		blk = to_block(data_ring, 0);

		/*
		 * Store the ID on the wrapped block क्रम consistency.
		 * The prपूर्णांकk_ringbuffer करोes not actually use it.
		 */
		blk->id = id;

		अगर (!wrapped) अणु
			/*
			 * Since the allocated space is now in the newly
			 * created wrapping data block, copy the content
			 * from the old data block.
			 */
			स_नकल(&blk->data[0], &old_blk->data[0],
			       (blk_lpos->next - blk_lpos->begin) - माप(blk->id));
		पूर्ण
	पूर्ण

	blk_lpos->next = next_lpos;

	वापस &blk->data[0];
पूर्ण

/* Return the number of bytes used by a data block. */
अटल अचिन्हित पूर्णांक space_used(काष्ठा prb_data_ring *data_ring,
			       काष्ठा prb_data_blk_lpos *blk_lpos)
अणु
	/* Data-less blocks take no space. */
	अगर (BLK_DATALESS(blk_lpos))
		वापस 0;

	अगर (DATA_WRAPS(data_ring, blk_lpos->begin) == DATA_WRAPS(data_ring, blk_lpos->next)) अणु
		/* Data block करोes not wrap. */
		वापस (DATA_INDEX(data_ring, blk_lpos->next) -
			DATA_INDEX(data_ring, blk_lpos->begin));
	पूर्ण

	/*
	 * For wrapping data blocks, the trailing (wasted) space is
	 * also counted.
	 */
	वापस (DATA_INDEX(data_ring, blk_lpos->next) +
		DATA_SIZE(data_ring) - DATA_INDEX(data_ring, blk_lpos->begin));
पूर्ण

/*
 * Given @blk_lpos, वापस a poपूर्णांकer to the ग_लिखोr data from the data block
 * and calculate the size of the data part. A शून्य poपूर्णांकer is वापसed अगर
 * @blk_lpos specअगरies values that could never be legal.
 *
 * This function (used by पढ़ोers) perक्रमms strict validation on the lpos
 * values to possibly detect bugs in the ग_लिखोr code. A WARN_ON_ONCE() is
 * triggered अगर an पूर्णांकernal error is detected.
 */
अटल स्थिर अक्षर *get_data(काष्ठा prb_data_ring *data_ring,
			    काष्ठा prb_data_blk_lpos *blk_lpos,
			    अचिन्हित पूर्णांक *data_size)
अणु
	काष्ठा prb_data_block *db;

	/* Data-less data block description. */
	अगर (BLK_DATALESS(blk_lpos)) अणु
		अगर (blk_lpos->begin == NO_LPOS && blk_lpos->next == NO_LPOS) अणु
			*data_size = 0;
			वापस "";
		पूर्ण
		वापस शून्य;
	पूर्ण

	/* Regular data block: @begin less than @next and in same wrap. */
	अगर (DATA_WRAPS(data_ring, blk_lpos->begin) == DATA_WRAPS(data_ring, blk_lpos->next) &&
	    blk_lpos->begin < blk_lpos->next) अणु
		db = to_block(data_ring, blk_lpos->begin);
		*data_size = blk_lpos->next - blk_lpos->begin;

	/* Wrapping data block: @begin is one wrap behind @next. */
	पूर्ण अन्यथा अगर (DATA_WRAPS(data_ring, blk_lpos->begin + DATA_SIZE(data_ring)) ==
		   DATA_WRAPS(data_ring, blk_lpos->next)) अणु
		db = to_block(data_ring, 0);
		*data_size = DATA_INDEX(data_ring, blk_lpos->next);

	/* Illegal block description. */
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(1);
		वापस शून्य;
	पूर्ण

	/* A valid data block will always be aligned to the ID size. */
	अगर (WARN_ON_ONCE(blk_lpos->begin != ALIGN(blk_lpos->begin, माप(db->id))) ||
	    WARN_ON_ONCE(blk_lpos->next != ALIGN(blk_lpos->next, माप(db->id)))) अणु
		वापस शून्य;
	पूर्ण

	/* A valid data block will always have at least an ID. */
	अगर (WARN_ON_ONCE(*data_size < माप(db->id)))
		वापस शून्य;

	/* Subtract block ID space from size to reflect data size. */
	*data_size -= माप(db->id);

	वापस &db->data[0];
पूर्ण

/*
 * Attempt to transition the newest descriptor from committed back to reserved
 * so that the record can be modअगरied by a ग_लिखोr again. This is only possible
 * अगर the descriptor is not yet finalized and the provided @caller_id matches.
 */
अटल काष्ठा prb_desc *desc_reखोलो_last(काष्ठा prb_desc_ring *desc_ring,
					 u32 caller_id, अचिन्हित दीर्घ *id_out)
अणु
	अचिन्हित दीर्घ prev_state_val;
	क्रमागत desc_state d_state;
	काष्ठा prb_desc desc;
	काष्ठा prb_desc *d;
	अचिन्हित दीर्घ id;
	u32 cid;

	id = atomic_दीर्घ_पढ़ो(&desc_ring->head_id);

	/*
	 * To reduce unnecessarily reखोलोing, first check अगर the descriptor
	 * state and caller ID are correct.
	 */
	d_state = desc_पढ़ो(desc_ring, id, &desc, शून्य, &cid);
	अगर (d_state != desc_committed || cid != caller_id)
		वापस शून्य;

	d = to_desc(desc_ring, id);

	prev_state_val = DESC_SV(id, desc_committed);

	/*
	 * Guarantee the reserved state is stored beक्रमe पढ़ोing any
	 * record data. A full memory barrier is needed because @state_var
	 * modअगरication is followed by पढ़ोing. This pairs with _prb_commit:B.
	 *
	 * Memory barrier involvement:
	 *
	 * If desc_reखोलो_last:A पढ़ोs from _prb_commit:B, then
	 * prb_reserve_in_last:A पढ़ोs from _prb_commit:A.
	 *
	 * Relies on:
	 *
	 * WMB from _prb_commit:A to _prb_commit:B
	 *    matching
	 * MB If desc_reखोलो_last:A to prb_reserve_in_last:A
	 */
	अगर (!atomic_दीर्घ_try_cmpxchg(&d->state_var, &prev_state_val,
			DESC_SV(id, desc_reserved))) अणु /* LMM(desc_reखोलो_last:A) */
		वापस शून्य;
	पूर्ण

	*id_out = id;
	वापस d;
पूर्ण

/**
 * prb_reserve_in_last() - Re-reserve and extend the space in the ringbuffer
 *                         used by the newest record.
 *
 * @e:         The entry काष्ठाure to setup.
 * @rb:        The ringbuffer to re-reserve and extend data in.
 * @r:         The record काष्ठाure to allocate buffers क्रम.
 * @caller_id: The caller ID of the caller (reserving ग_लिखोr).
 * @max_size:  Fail अगर the extended size would be greater than this.
 *
 * This is the खुला function available to ग_लिखोrs to re-reserve and extend
 * data.
 *
 * The ग_लिखोr specअगरies the text size to extend (not the new total size) by
 * setting the @text_buf_size field of @r. To ensure proper initialization
 * of @r, prb_rec_init_wr() should be used.
 *
 * This function will fail अगर @caller_id करोes not match the caller ID of the
 * newest record. In that हाल the caller must reserve new data using
 * prb_reserve().
 *
 * Context: Any context. Disables local पूर्णांकerrupts on success.
 * Return: true अगर text data could be extended, otherwise false.
 *
 * On success:
 *
 *   - @r->text_buf poपूर्णांकs to the beginning of the entire text buffer.
 *
 *   - @r->text_buf_size is set to the new total size of the buffer.
 *
 *   - @r->info is not touched so that @r->info->text_len could be used
 *     to append the text.
 *
 *   - prb_record_text_space() can be used on @e to query the new
 *     actually used space.
 *
 * Important: All @r->info fields will alपढ़ोy be set with the current values
 *            क्रम the record. I.e. @r->info->text_len will be less than
 *            @text_buf_size. Writers can use @r->info->text_len to know
 *            where concatenation begins and ग_लिखोrs should update
 *            @r->info->text_len after concatenating.
 */
bool prb_reserve_in_last(काष्ठा prb_reserved_entry *e, काष्ठा prपूर्णांकk_ringbuffer *rb,
			 काष्ठा prपूर्णांकk_record *r, u32 caller_id, अचिन्हित पूर्णांक max_size)
अणु
	काष्ठा prb_desc_ring *desc_ring = &rb->desc_ring;
	काष्ठा prपूर्णांकk_info *info;
	अचिन्हित पूर्णांक data_size;
	काष्ठा prb_desc *d;
	अचिन्हित दीर्घ id;

	local_irq_save(e->irqflags);

	/* Transition the newest descriptor back to the reserved state. */
	d = desc_reखोलो_last(desc_ring, caller_id, &id);
	अगर (!d) अणु
		local_irq_restore(e->irqflags);
		जाओ fail_reखोलो;
	पूर्ण

	/* Now the ग_लिखोr has exclusive access: LMM(prb_reserve_in_last:A) */

	info = to_info(desc_ring, id);

	/*
	 * Set the @e fields here so that prb_commit() can be used अगर
	 * anything fails from now on.
	 */
	e->rb = rb;
	e->id = id;

	/*
	 * desc_reखोलो_last() checked the caller_id, but there was no
	 * exclusive access at that poपूर्णांक. The descriptor may have
	 * changed since then.
	 */
	अगर (caller_id != info->caller_id)
		जाओ fail;

	अगर (BLK_DATALESS(&d->text_blk_lpos)) अणु
		अगर (WARN_ON_ONCE(info->text_len != 0)) अणु
			pr_warn_once("wrong text_len value (%hu, expecting 0)\n",
				     info->text_len);
			info->text_len = 0;
		पूर्ण

		अगर (!data_check_size(&rb->text_data_ring, r->text_buf_size))
			जाओ fail;

		अगर (r->text_buf_size > max_size)
			जाओ fail;

		r->text_buf = data_alloc(rb, r->text_buf_size,
					 &d->text_blk_lpos, id);
	पूर्ण अन्यथा अणु
		अगर (!get_data(&rb->text_data_ring, &d->text_blk_lpos, &data_size))
			जाओ fail;

		/*
		 * Increase the buffer size to include the original size. If
		 * the meta data (@text_len) is not sane, use the full data
		 * block size.
		 */
		अगर (WARN_ON_ONCE(info->text_len > data_size)) अणु
			pr_warn_once("wrong text_len value (%hu, expecting <=%u)\n",
				     info->text_len, data_size);
			info->text_len = data_size;
		पूर्ण
		r->text_buf_size += info->text_len;

		अगर (!data_check_size(&rb->text_data_ring, r->text_buf_size))
			जाओ fail;

		अगर (r->text_buf_size > max_size)
			जाओ fail;

		r->text_buf = data_पुनः_स्मृति(rb, r->text_buf_size,
					   &d->text_blk_lpos, id);
	पूर्ण
	अगर (r->text_buf_size && !r->text_buf)
		जाओ fail;

	r->info = info;

	e->text_space = space_used(&rb->text_data_ring, &d->text_blk_lpos);

	वापस true;
fail:
	prb_commit(e);
	/* prb_commit() re-enabled पूर्णांकerrupts. */
fail_reखोलो:
	/* Make it clear to the caller that the re-reserve failed. */
	स_रखो(r, 0, माप(*r));
	वापस false;
पूर्ण

/*
 * Attempt to finalize a specअगरied descriptor. If this fails, the descriptor
 * is either alपढ़ोy final or it will finalize itself when the ग_लिखोr commits.
 */
अटल व्योम desc_make_final(काष्ठा prb_desc_ring *desc_ring, अचिन्हित दीर्घ id)
अणु
	अचिन्हित दीर्घ prev_state_val = DESC_SV(id, desc_committed);
	काष्ठा prb_desc *d = to_desc(desc_ring, id);

	atomic_दीर्घ_cmpxchg_relaxed(&d->state_var, prev_state_val,
			DESC_SV(id, desc_finalized)); /* LMM(desc_make_final:A) */
पूर्ण

/**
 * prb_reserve() - Reserve space in the ringbuffer.
 *
 * @e:  The entry काष्ठाure to setup.
 * @rb: The ringbuffer to reserve data in.
 * @r:  The record काष्ठाure to allocate buffers क्रम.
 *
 * This is the खुला function available to ग_लिखोrs to reserve data.
 *
 * The ग_लिखोr specअगरies the text size to reserve by setting the
 * @text_buf_size field of @r. To ensure proper initialization of @r,
 * prb_rec_init_wr() should be used.
 *
 * Context: Any context. Disables local पूर्णांकerrupts on success.
 * Return: true अगर at least text data could be allocated, otherwise false.
 *
 * On success, the fields @info and @text_buf of @r will be set by this
 * function and should be filled in by the ग_लिखोr beक्रमe committing. Also
 * on success, prb_record_text_space() can be used on @e to query the actual
 * space used क्रम the text data block.
 *
 * Important: @info->text_len needs to be set correctly by the ग_लिखोr in
 *            order क्रम data to be पढ़ोable and/or extended. Its value
 *            is initialized to 0.
 */
bool prb_reserve(काष्ठा prb_reserved_entry *e, काष्ठा prपूर्णांकk_ringbuffer *rb,
		 काष्ठा prपूर्णांकk_record *r)
अणु
	काष्ठा prb_desc_ring *desc_ring = &rb->desc_ring;
	काष्ठा prपूर्णांकk_info *info;
	काष्ठा prb_desc *d;
	अचिन्हित दीर्घ id;
	u64 seq;

	अगर (!data_check_size(&rb->text_data_ring, r->text_buf_size))
		जाओ fail;

	/*
	 * Descriptors in the reserved state act as blockers to all further
	 * reservations once the desc_ring has fully wrapped. Disable
	 * पूर्णांकerrupts during the reserve/commit winकरोw in order to minimize
	 * the likelihood of this happening.
	 */
	local_irq_save(e->irqflags);

	अगर (!desc_reserve(rb, &id)) अणु
		/* Descriptor reservation failures are tracked. */
		atomic_दीर्घ_inc(&rb->fail);
		local_irq_restore(e->irqflags);
		जाओ fail;
	पूर्ण

	d = to_desc(desc_ring, id);
	info = to_info(desc_ring, id);

	/*
	 * All @info fields (except @seq) are cleared and must be filled in
	 * by the ग_लिखोr. Save @seq beक्रमe clearing because it is used to
	 * determine the new sequence number.
	 */
	seq = info->seq;
	स_रखो(info, 0, माप(*info));

	/*
	 * Set the @e fields here so that prb_commit() can be used अगर
	 * text data allocation fails.
	 */
	e->rb = rb;
	e->id = id;

	/*
	 * Initialize the sequence number अगर it has "never been set".
	 * Otherwise just increment it by a full wrap.
	 *
	 * @seq is considered "never been set" अगर it has a value of 0,
	 * _except_ क्रम @infos[0], which was specially setup by the ringbuffer
	 * initializer and thereक्रमe is always considered as set.
	 *
	 * See the "Bootstrap" comment block in prपूर्णांकk_ringbuffer.h क्रम
	 * details about how the initializer bootstraps the descriptors.
	 */
	अगर (seq == 0 && DESC_INDEX(desc_ring, id) != 0)
		info->seq = DESC_INDEX(desc_ring, id);
	अन्यथा
		info->seq = seq + DESCS_COUNT(desc_ring);

	/*
	 * New data is about to be reserved. Once that happens, previous
	 * descriptors are no दीर्घer able to be extended. Finalize the
	 * previous descriptor now so that it can be made available to
	 * पढ़ोers. (For seq==0 there is no previous descriptor.)
	 */
	अगर (info->seq > 0)
		desc_make_final(desc_ring, DESC_ID(id - 1));

	r->text_buf = data_alloc(rb, r->text_buf_size, &d->text_blk_lpos, id);
	/* If text data allocation fails, a data-less record is committed. */
	अगर (r->text_buf_size && !r->text_buf) अणु
		prb_commit(e);
		/* prb_commit() re-enabled पूर्णांकerrupts. */
		जाओ fail;
	पूर्ण

	r->info = info;

	/* Record full text space used by record. */
	e->text_space = space_used(&rb->text_data_ring, &d->text_blk_lpos);

	वापस true;
fail:
	/* Make it clear to the caller that the reserve failed. */
	स_रखो(r, 0, माप(*r));
	वापस false;
पूर्ण

/* Commit the data (possibly finalizing it) and restore पूर्णांकerrupts. */
अटल व्योम _prb_commit(काष्ठा prb_reserved_entry *e, अचिन्हित दीर्घ state_val)
अणु
	काष्ठा prb_desc_ring *desc_ring = &e->rb->desc_ring;
	काष्ठा prb_desc *d = to_desc(desc_ring, e->id);
	अचिन्हित दीर्घ prev_state_val = DESC_SV(e->id, desc_reserved);

	/* Now the ग_लिखोr has finished all writing: LMM(_prb_commit:A) */

	/*
	 * Set the descriptor as committed. See "ABA Issues" about why
	 * cmpxchg() instead of set() is used.
	 *
	 * 1  Guarantee all record data is stored beक्रमe the descriptor state
	 *    is stored as committed. A ग_लिखो memory barrier is sufficient
	 *    क्रम this. This pairs with desc_पढ़ो:B and desc_reखोलो_last:A.
	 *
	 * 2. Guarantee the descriptor state is stored as committed beक्रमe
	 *    re-checking the head ID in order to possibly finalize this
	 *    descriptor. This pairs with desc_reserve:D.
	 *
	 *    Memory barrier involvement:
	 *
	 *    If prb_commit:A पढ़ोs from desc_reserve:D, then
	 *    desc_make_final:A पढ़ोs from _prb_commit:B.
	 *
	 *    Relies on:
	 *
	 *    MB _prb_commit:B to prb_commit:A
	 *       matching
	 *    MB desc_reserve:D to desc_make_final:A
	 */
	अगर (!atomic_दीर्घ_try_cmpxchg(&d->state_var, &prev_state_val,
			DESC_SV(e->id, state_val))) अणु /* LMM(_prb_commit:B) */
		WARN_ON_ONCE(1);
	पूर्ण

	/* Restore पूर्णांकerrupts, the reserve/commit winकरोw is finished. */
	local_irq_restore(e->irqflags);
पूर्ण

/**
 * prb_commit() - Commit (previously reserved) data to the ringbuffer.
 *
 * @e: The entry containing the reserved data inक्रमmation.
 *
 * This is the खुला function available to ग_लिखोrs to commit data.
 *
 * Note that the data is not yet available to पढ़ोers until it is finalized.
 * Finalizing happens स्वतःmatically when space क्रम the next record is
 * reserved.
 *
 * See prb_final_commit() क्रम a version of this function that finalizes
 * immediately.
 *
 * Context: Any context. Enables local पूर्णांकerrupts.
 */
व्योम prb_commit(काष्ठा prb_reserved_entry *e)
अणु
	काष्ठा prb_desc_ring *desc_ring = &e->rb->desc_ring;
	अचिन्हित दीर्घ head_id;

	_prb_commit(e, desc_committed);

	/*
	 * If this descriptor is no दीर्घer the head (i.e. a new record has
	 * been allocated), extending the data क्रम this record is no दीर्घer
	 * allowed and thereक्रमe it must be finalized.
	 */
	head_id = atomic_दीर्घ_पढ़ो(&desc_ring->head_id); /* LMM(prb_commit:A) */
	अगर (head_id != e->id)
		desc_make_final(desc_ring, e->id);
पूर्ण

/**
 * prb_final_commit() - Commit and finalize (previously reserved) data to
 *                      the ringbuffer.
 *
 * @e: The entry containing the reserved data inक्रमmation.
 *
 * This is the खुला function available to ग_लिखोrs to commit+finalize data.
 *
 * By finalizing, the data is made immediately available to पढ़ोers.
 *
 * This function should only be used अगर there are no पूर्णांकentions of extending
 * this data using prb_reserve_in_last().
 *
 * Context: Any context. Enables local पूर्णांकerrupts.
 */
व्योम prb_final_commit(काष्ठा prb_reserved_entry *e)
अणु
	_prb_commit(e, desc_finalized);
पूर्ण

/*
 * Count the number of lines in provided text. All text has at least 1 line
 * (even अगर @text_size is 0). Each '\n' processed is counted as an additional
 * line.
 */
अटल अचिन्हित पूर्णांक count_lines(स्थिर अक्षर *text, अचिन्हित पूर्णांक text_size)
अणु
	अचिन्हित पूर्णांक next_size = text_size;
	अचिन्हित पूर्णांक line_count = 1;
	स्थिर अक्षर *next = text;

	जबतक (next_size) अणु
		next = स_प्रथम(next, '\n', next_size);
		अगर (!next)
			अवरोध;
		line_count++;
		next++;
		next_size = text_size - (next - text);
	पूर्ण

	वापस line_count;
पूर्ण

/*
 * Given @blk_lpos, copy an expected @len of data पूर्णांकo the provided buffer.
 * If @line_count is provided, count the number of lines in the data.
 *
 * This function (used by पढ़ोers) perक्रमms strict validation on the data
 * size to possibly detect bugs in the ग_लिखोr code. A WARN_ON_ONCE() is
 * triggered अगर an पूर्णांकernal error is detected.
 */
अटल bool copy_data(काष्ठा prb_data_ring *data_ring,
		      काष्ठा prb_data_blk_lpos *blk_lpos, u16 len, अक्षर *buf,
		      अचिन्हित पूर्णांक buf_size, अचिन्हित पूर्णांक *line_count)
अणु
	अचिन्हित पूर्णांक data_size;
	स्थिर अक्षर *data;

	/* Caller might not want any data. */
	अगर ((!buf || !buf_size) && !line_count)
		वापस true;

	data = get_data(data_ring, blk_lpos, &data_size);
	अगर (!data)
		वापस false;

	/*
	 * Actual cannot be less than expected. It can be more than expected
	 * because of the trailing alignment padding.
	 *
	 * Note that invalid @len values can occur because the caller loads
	 * the value during an allowed data race.
	 */
	अगर (data_size < (अचिन्हित पूर्णांक)len)
		वापस false;

	/* Caller पूर्णांकerested in the line count? */
	अगर (line_count)
		*line_count = count_lines(data, len);

	/* Caller पूर्णांकerested in the data content? */
	अगर (!buf || !buf_size)
		वापस true;

	data_size = min_t(u16, buf_size, len);

	स_नकल(&buf[0], data, data_size); /* LMM(copy_data:A) */
	वापस true;
पूर्ण

/*
 * This is an extended version of desc_पढ़ो(). It माला_लो a copy of a specअगरied
 * descriptor. However, it also verअगरies that the record is finalized and has
 * the sequence number @seq. On success, 0 is वापसed.
 *
 * Error वापस values:
 * -EINVAL: A finalized record with sequence number @seq करोes not exist.
 * -ENOENT: A finalized record with sequence number @seq exists, but its data
 *          is not available. This is a valid record, so पढ़ोers should
 *          जारी with the next record.
 */
अटल पूर्णांक desc_पढ़ो_finalized_seq(काष्ठा prb_desc_ring *desc_ring,
				   अचिन्हित दीर्घ id, u64 seq,
				   काष्ठा prb_desc *desc_out)
अणु
	काष्ठा prb_data_blk_lpos *blk_lpos = &desc_out->text_blk_lpos;
	क्रमागत desc_state d_state;
	u64 s;

	d_state = desc_पढ़ो(desc_ring, id, desc_out, &s, शून्य);

	/*
	 * An unexpected @id (desc_miss) or @seq mismatch means the record
	 * करोes not exist. A descriptor in the reserved or committed state
	 * means the record करोes not yet exist क्रम the पढ़ोer.
	 */
	अगर (d_state == desc_miss ||
	    d_state == desc_reserved ||
	    d_state == desc_committed ||
	    s != seq) अणु
		वापस -EINVAL;
	पूर्ण

	/*
	 * A descriptor in the reusable state may no दीर्घer have its data
	 * available; report it as existing but with lost data. Or the record
	 * may actually be a record with lost data.
	 */
	अगर (d_state == desc_reusable ||
	    (blk_lpos->begin == FAILED_LPOS && blk_lpos->next == FAILED_LPOS)) अणु
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Copy the ringbuffer data from the record with @seq to the provided
 * @r buffer. On success, 0 is वापसed.
 *
 * See desc_पढ़ो_finalized_seq() क्रम error वापस values.
 */
अटल पूर्णांक prb_पढ़ो(काष्ठा prपूर्णांकk_ringbuffer *rb, u64 seq,
		    काष्ठा prपूर्णांकk_record *r, अचिन्हित पूर्णांक *line_count)
अणु
	काष्ठा prb_desc_ring *desc_ring = &rb->desc_ring;
	काष्ठा prपूर्णांकk_info *info = to_info(desc_ring, seq);
	काष्ठा prb_desc *rdesc = to_desc(desc_ring, seq);
	atomic_दीर्घ_t *state_var = &rdesc->state_var;
	काष्ठा prb_desc desc;
	अचिन्हित दीर्घ id;
	पूर्णांक err;

	/* Extract the ID, used to specअगरy the descriptor to पढ़ो. */
	id = DESC_ID(atomic_दीर्घ_पढ़ो(state_var));

	/* Get a local copy of the correct descriptor (अगर available). */
	err = desc_पढ़ो_finalized_seq(desc_ring, id, seq, &desc);

	/*
	 * If @r is शून्य, the caller is only पूर्णांकerested in the availability
	 * of the record.
	 */
	अगर (err || !r)
		वापस err;

	/* If requested, copy meta data. */
	अगर (r->info)
		स_नकल(r->info, info, माप(*(r->info)));

	/* Copy text data. If it fails, this is a data-less record. */
	अगर (!copy_data(&rb->text_data_ring, &desc.text_blk_lpos, info->text_len,
		       r->text_buf, r->text_buf_size, line_count)) अणु
		वापस -ENOENT;
	पूर्ण

	/* Ensure the record is still finalized and has the same @seq. */
	वापस desc_पढ़ो_finalized_seq(desc_ring, id, seq, &desc);
पूर्ण

/* Get the sequence number of the tail descriptor. */
अटल u64 prb_first_seq(काष्ठा prपूर्णांकk_ringbuffer *rb)
अणु
	काष्ठा prb_desc_ring *desc_ring = &rb->desc_ring;
	क्रमागत desc_state d_state;
	काष्ठा prb_desc desc;
	अचिन्हित दीर्घ id;
	u64 seq;

	क्रम (;;) अणु
		id = atomic_दीर्घ_पढ़ो(&rb->desc_ring.tail_id); /* LMM(prb_first_seq:A) */

		d_state = desc_पढ़ो(desc_ring, id, &desc, &seq, शून्य); /* LMM(prb_first_seq:B) */

		/*
		 * This loop will not be infinite because the tail is
		 * _always_ in the finalized or reusable state.
		 */
		अगर (d_state == desc_finalized || d_state == desc_reusable)
			अवरोध;

		/*
		 * Guarantee the last state load from desc_पढ़ो() is beक्रमe
		 * reloading @tail_id in order to see a new tail in the हाल
		 * that the descriptor has been recycled. This pairs with
		 * desc_reserve:D.
		 *
		 * Memory barrier involvement:
		 *
		 * If prb_first_seq:B पढ़ोs from desc_reserve:F, then
		 * prb_first_seq:A पढ़ोs from desc_push_tail:B.
		 *
		 * Relies on:
		 *
		 * MB from desc_push_tail:B to desc_reserve:F
		 *    matching
		 * RMB prb_first_seq:B to prb_first_seq:A
		 */
		smp_rmb(); /* LMM(prb_first_seq:C) */
	पूर्ण

	वापस seq;
पूर्ण

/*
 * Non-blocking पढ़ो of a record. Updates @seq to the last finalized record
 * (which may have no data available).
 *
 * See the description of prb_पढ़ो_valid() and prb_पढ़ो_valid_info()
 * क्रम details.
 */
अटल bool _prb_पढ़ो_valid(काष्ठा prपूर्णांकk_ringbuffer *rb, u64 *seq,
			    काष्ठा prपूर्णांकk_record *r, अचिन्हित पूर्णांक *line_count)
अणु
	u64 tail_seq;
	पूर्णांक err;

	जबतक ((err = prb_पढ़ो(rb, *seq, r, line_count))) अणु
		tail_seq = prb_first_seq(rb);

		अगर (*seq < tail_seq) अणु
			/*
			 * Behind the tail. Catch up and try again. This
			 * can happen क्रम -ENOENT and -EINVAL हालs.
			 */
			*seq = tail_seq;

		पूर्ण अन्यथा अगर (err == -ENOENT) अणु
			/* Record exists, but no data available. Skip. */
			(*seq)++;

		पूर्ण अन्यथा अणु
			/* Non-existent/non-finalized record. Must stop. */
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/**
 * prb_पढ़ो_valid() - Non-blocking पढ़ो of a requested record or (अगर gone)
 *                    the next available record.
 *
 * @rb:  The ringbuffer to पढ़ो from.
 * @seq: The sequence number of the record to पढ़ो.
 * @r:   A record data buffer to store the पढ़ो record to.
 *
 * This is the खुला function available to पढ़ोers to पढ़ो a record.
 *
 * The पढ़ोer provides the @info and @text_buf buffers of @r to be
 * filled in. Any of the buffer poपूर्णांकers can be set to शून्य अगर the पढ़ोer
 * is not पूर्णांकerested in that data. To ensure proper initialization of @r,
 * prb_rec_init_rd() should be used.
 *
 * Context: Any context.
 * Return: true अगर a record was पढ़ो, otherwise false.
 *
 * On success, the पढ़ोer must check r->info.seq to see which record was
 * actually पढ़ो. This allows the पढ़ोer to detect dropped records.
 *
 * Failure means @seq refers to a not yet written record.
 */
bool prb_पढ़ो_valid(काष्ठा prपूर्णांकk_ringbuffer *rb, u64 seq,
		    काष्ठा prपूर्णांकk_record *r)
अणु
	वापस _prb_पढ़ो_valid(rb, &seq, r, शून्य);
पूर्ण

/**
 * prb_पढ़ो_valid_info() - Non-blocking पढ़ो of meta data क्रम a requested
 *                         record or (अगर gone) the next available record.
 *
 * @rb:         The ringbuffer to पढ़ो from.
 * @seq:        The sequence number of the record to पढ़ो.
 * @info:       A buffer to store the पढ़ो record meta data to.
 * @line_count: A buffer to store the number of lines in the record text.
 *
 * This is the खुला function available to पढ़ोers to पढ़ो only the
 * meta data of a record.
 *
 * The पढ़ोer provides the @info, @line_count buffers to be filled in.
 * Either of the buffer poपूर्णांकers can be set to शून्य अगर the पढ़ोer is not
 * पूर्णांकerested in that data.
 *
 * Context: Any context.
 * Return: true अगर a record's meta data was पढ़ो, otherwise false.
 *
 * On success, the पढ़ोer must check info->seq to see which record meta data
 * was actually पढ़ो. This allows the पढ़ोer to detect dropped records.
 *
 * Failure means @seq refers to a not yet written record.
 */
bool prb_पढ़ो_valid_info(काष्ठा prपूर्णांकk_ringbuffer *rb, u64 seq,
			 काष्ठा prपूर्णांकk_info *info, अचिन्हित पूर्णांक *line_count)
अणु
	काष्ठा prपूर्णांकk_record r;

	prb_rec_init_rd(&r, info, शून्य, 0);

	वापस _prb_पढ़ो_valid(rb, &seq, &r, line_count);
पूर्ण

/**
 * prb_first_valid_seq() - Get the sequence number of the oldest available
 *                         record.
 *
 * @rb: The ringbuffer to get the sequence number from.
 *
 * This is the खुला function available to पढ़ोers to see what the
 * first/oldest valid sequence number is.
 *
 * This provides पढ़ोers a starting poपूर्णांक to begin iterating the ringbuffer.
 *
 * Context: Any context.
 * Return: The sequence number of the first/oldest record or, अगर the
 *         ringbuffer is empty, 0 is वापसed.
 */
u64 prb_first_valid_seq(काष्ठा prपूर्णांकk_ringbuffer *rb)
अणु
	u64 seq = 0;

	अगर (!_prb_पढ़ो_valid(rb, &seq, शून्य, शून्य))
		वापस 0;

	वापस seq;
पूर्ण

/**
 * prb_next_seq() - Get the sequence number after the last available record.
 *
 * @rb:  The ringbuffer to get the sequence number from.
 *
 * This is the खुला function available to पढ़ोers to see what the next
 * newest sequence number available to पढ़ोers will be.
 *
 * This provides पढ़ोers a sequence number to jump to अगर all currently
 * available records should be skipped.
 *
 * Context: Any context.
 * Return: The sequence number of the next newest (not yet available) record
 *         क्रम पढ़ोers.
 */
u64 prb_next_seq(काष्ठा prपूर्णांकk_ringbuffer *rb)
अणु
	u64 seq = 0;

	/* Search क्रमward from the oldest descriptor. */
	जबतक (_prb_पढ़ो_valid(rb, &seq, शून्य, शून्य))
		seq++;

	वापस seq;
पूर्ण

/**
 * prb_init() - Initialize a ringbuffer to use provided बाह्यal buffers.
 *
 * @rb:       The ringbuffer to initialize.
 * @text_buf: The data buffer क्रम text data.
 * @textbits: The size of @text_buf as a घातer-of-2 value.
 * @descs:    The descriptor buffer क्रम ringbuffer records.
 * @descbits: The count of @descs items as a घातer-of-2 value.
 * @infos:    The prपूर्णांकk_info buffer क्रम ringbuffer records.
 *
 * This is the खुला function available to ग_लिखोrs to setup a ringbuffer
 * during runसमय using provided buffers.
 *
 * This must match the initialization of DEFINE_PRINTKRB().
 *
 * Context: Any context.
 */
व्योम prb_init(काष्ठा prपूर्णांकk_ringbuffer *rb,
	      अक्षर *text_buf, अचिन्हित पूर्णांक textbits,
	      काष्ठा prb_desc *descs, अचिन्हित पूर्णांक descbits,
	      काष्ठा prपूर्णांकk_info *infos)
अणु
	स_रखो(descs, 0, _DESCS_COUNT(descbits) * माप(descs[0]));
	स_रखो(infos, 0, _DESCS_COUNT(descbits) * माप(infos[0]));

	rb->desc_ring.count_bits = descbits;
	rb->desc_ring.descs = descs;
	rb->desc_ring.infos = infos;
	atomic_दीर्घ_set(&rb->desc_ring.head_id, DESC0_ID(descbits));
	atomic_दीर्घ_set(&rb->desc_ring.tail_id, DESC0_ID(descbits));

	rb->text_data_ring.size_bits = textbits;
	rb->text_data_ring.data = text_buf;
	atomic_दीर्घ_set(&rb->text_data_ring.head_lpos, BLK0_LPOS(textbits));
	atomic_दीर्घ_set(&rb->text_data_ring.tail_lpos, BLK0_LPOS(textbits));

	atomic_दीर्घ_set(&rb->fail, 0);

	atomic_दीर्घ_set(&(descs[_DESCS_COUNT(descbits) - 1].state_var), DESC0_SV(descbits));
	descs[_DESCS_COUNT(descbits) - 1].text_blk_lpos.begin = FAILED_LPOS;
	descs[_DESCS_COUNT(descbits) - 1].text_blk_lpos.next = FAILED_LPOS;

	infos[0].seq = -(u64)_DESCS_COUNT(descbits);
	infos[_DESCS_COUNT(descbits) - 1].seq = 0;
पूर्ण

/**
 * prb_record_text_space() - Query the full actual used ringbuffer space क्रम
 *                           the text data of a reserved entry.
 *
 * @e: The successfully reserved entry to query.
 *
 * This is the खुला function available to ग_लिखोrs to see how much actual
 * space is used in the ringbuffer to store the text data of the specअगरied
 * entry.
 *
 * This function is only valid अगर @e has been successfully reserved using
 * prb_reserve().
 *
 * Context: Any context.
 * Return: The size in bytes used by the text data of the associated record.
 */
अचिन्हित पूर्णांक prb_record_text_space(काष्ठा prb_reserved_entry *e)
अणु
	वापस e->text_space;
पूर्ण
