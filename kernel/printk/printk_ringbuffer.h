<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _KERNEL_PRINTK_RINGBUFFER_H
#घोषणा _KERNEL_PRINTK_RINGBUFFER_H

#समावेश <linux/atomic.h>
#समावेश <linux/dev_prपूर्णांकk.h>

/*
 * Meta inक्रमmation about each stored message.
 *
 * All fields are set by the prपूर्णांकk code except क्रम @seq, which is
 * set by the ringbuffer code.
 */
काष्ठा prपूर्णांकk_info अणु
	u64	seq;		/* sequence number */
	u64	ts_nsec;	/* बारtamp in nanoseconds */
	u16	text_len;	/* length of text message */
	u8	facility;	/* syslog facility */
	u8	flags:5;	/* पूर्णांकernal record flags */
	u8	level:3;	/* syslog level */
	u32	caller_id;	/* thपढ़ो id or processor id */

	काष्ठा dev_prपूर्णांकk_info	dev_info;
पूर्ण;

/*
 * A काष्ठाure providing the buffers, used by ग_लिखोrs and पढ़ोers.
 *
 * Writers:
 * Using prb_rec_init_wr(), a ग_लिखोr sets @text_buf_size beक्रमe calling
 * prb_reserve(). On success, prb_reserve() sets @info and @text_buf to
 * buffers reserved क्रम that ग_लिखोr.
 *
 * Readers:
 * Using prb_rec_init_rd(), a पढ़ोer sets all fields beक्रमe calling
 * prb_पढ़ो_valid(). Note that the पढ़ोer provides the @info and @text_buf,
 * buffers. On success, the काष्ठा poपूर्णांकed to by @info will be filled and
 * the अक्षर array poपूर्णांकed to by @text_buf will be filled with text data.
 */
काष्ठा prपूर्णांकk_record अणु
	काष्ठा prपूर्णांकk_info	*info;
	अक्षर			*text_buf;
	अचिन्हित पूर्णांक		text_buf_size;
पूर्ण;

/* Specअगरies the logical position and span of a data block. */
काष्ठा prb_data_blk_lpos अणु
	अचिन्हित दीर्घ	begin;
	अचिन्हित दीर्घ	next;
पूर्ण;

/*
 * A descriptor: the complete meta-data क्रम a record.
 *
 * @state_var: A bitwise combination of descriptor ID and descriptor state.
 */
काष्ठा prb_desc अणु
	atomic_दीर्घ_t			state_var;
	काष्ठा prb_data_blk_lpos	text_blk_lpos;
पूर्ण;

/* A ringbuffer of "ID + data" elements. */
काष्ठा prb_data_ring अणु
	अचिन्हित पूर्णांक	size_bits;
	अक्षर		*data;
	atomic_दीर्घ_t	head_lpos;
	atomic_दीर्घ_t	tail_lpos;
पूर्ण;

/* A ringbuffer of "struct prb_desc" elements. */
काष्ठा prb_desc_ring अणु
	अचिन्हित पूर्णांक		count_bits;
	काष्ठा prb_desc		*descs;
	काष्ठा prपूर्णांकk_info	*infos;
	atomic_दीर्घ_t		head_id;
	atomic_दीर्घ_t		tail_id;
पूर्ण;

/*
 * The high level काष्ठाure representing the prपूर्णांकk ringbuffer.
 *
 * @fail: Count of failed prb_reserve() calls where not even a data-less
 *        record was created.
 */
काष्ठा prपूर्णांकk_ringbuffer अणु
	काष्ठा prb_desc_ring	desc_ring;
	काष्ठा prb_data_ring	text_data_ring;
	atomic_दीर्घ_t		fail;
पूर्ण;

/*
 * Used by ग_लिखोrs as a reserve/commit handle.
 *
 * @rb:         Ringbuffer where the entry is reserved.
 * @irqflags:   Saved irq flags to restore on entry commit.
 * @id:         ID of the reserved descriptor.
 * @text_space: Total occupied buffer space in the text data ring, including
 *              ID, alignment padding, and wrapping data blocks.
 *
 * This काष्ठाure is an opaque handle क्रम ग_लिखोrs. Its contents are only
 * to be used by the ringbuffer implementation.
 */
काष्ठा prb_reserved_entry अणु
	काष्ठा prपूर्णांकk_ringbuffer	*rb;
	अचिन्हित दीर्घ			irqflags;
	अचिन्हित दीर्घ			id;
	अचिन्हित पूर्णांक			text_space;
पूर्ण;

/* The possible responses of a descriptor state-query. */
क्रमागत desc_state अणु
	desc_miss	=  -1,	/* ID mismatch (pseuकरो state) */
	desc_reserved	= 0x0,	/* reserved, in use by ग_लिखोr */
	desc_committed	= 0x1,	/* committed by ग_लिखोr, could get reखोलोed */
	desc_finalized	= 0x2,	/* committed, no further modअगरication allowed */
	desc_reusable	= 0x3,	/* मुक्त, not yet used by any ग_लिखोr */
पूर्ण;

#घोषणा _DATA_SIZE(sz_bits)	(1UL << (sz_bits))
#घोषणा _DESCS_COUNT(ct_bits)	(1U << (ct_bits))
#घोषणा DESC_SV_BITS		(माप(अचिन्हित दीर्घ) * 8)
#घोषणा DESC_FLAGS_SHIFT	(DESC_SV_BITS - 2)
#घोषणा DESC_FLAGS_MASK		(3UL << DESC_FLAGS_SHIFT)
#घोषणा DESC_STATE(sv)		(3UL & (sv >> DESC_FLAGS_SHIFT))
#घोषणा DESC_SV(id, state)	(((अचिन्हित दीर्घ)state << DESC_FLAGS_SHIFT) | id)
#घोषणा DESC_ID_MASK		(~DESC_FLAGS_MASK)
#घोषणा DESC_ID(sv)		((sv) & DESC_ID_MASK)
#घोषणा FAILED_LPOS		0x1
#घोषणा NO_LPOS			0x3

#घोषणा FAILED_BLK_LPOS	\
अणु				\
	.begin	= FAILED_LPOS,	\
	.next	= FAILED_LPOS,	\
पूर्ण

/*
 * Descriptor Bootstrap
 *
 * The descriptor array is minimally initialized to allow immediate usage
 * by पढ़ोers and ग_लिखोrs. The requirements that the descriptor array
 * initialization must satisfy:
 *
 *   Req1
 *     The tail must poपूर्णांक to an existing (committed or reusable) descriptor.
 *     This is required by the implementation of prb_first_seq().
 *
 *   Req2
 *     Readers must see that the ringbuffer is initially empty.
 *
 *   Req3
 *     The first record reserved by a ग_लिखोr is asचिन्हित sequence number 0.
 *
 * To satisfy Req1, the tail initially poपूर्णांकs to a descriptor that is
 * minimally initialized (having no data block, i.e. data-less with the
 * data block's lpos @begin and @next values set to FAILED_LPOS).
 *
 * To satisfy Req2, the initial tail descriptor is initialized to the
 * reusable state. Readers recognize reusable descriptors as existing
 * records, but skip over them.
 *
 * To satisfy Req3, the last descriptor in the array is used as the initial
 * head (and tail) descriptor. This allows the first record reserved by a
 * ग_लिखोr (head + 1) to be the first descriptor in the array. (Only the first
 * descriptor in the array could have a valid sequence number of 0.)
 *
 * The first समय a descriptor is reserved, it is asचिन्हित a sequence number
 * with the value of the array index. A "first time reserved" descriptor can
 * be recognized because it has a sequence number of 0 but करोes not have an
 * index of 0. (Only the first descriptor in the array could have a valid
 * sequence number of 0.) After the first reservation, all future reservations
 * (recycling) simply involve incrementing the sequence number by the array
 * count.
 *
 *   Hack #1
 *     Only the first descriptor in the array is allowed to have the sequence
 *     number 0. In this हाल it is not possible to recognize अगर it is being
 *     reserved the first समय (set to index value) or has been reserved
 *     previously (increment by the array count). This is handled by _always_
 *     incrementing the sequence number by the array count when reserving the
 *     first descriptor in the array. In order to satisfy Req3, the sequence
 *     number of the first descriptor in the array is initialized to minus
 *     the array count. Then, upon the first reservation, it is incremented
 *     to 0, thus satisfying Req3.
 *
 *   Hack #2
 *     prb_first_seq() can be called at any समय by पढ़ोers to retrieve the
 *     sequence number of the tail descriptor. However, due to Req2 and Req3,
 *     initially there are no records to report the sequence number of
 *     (sequence numbers are u64 and there is nothing less than 0). To handle
 *     this, the sequence number of the initial tail descriptor is initialized
 *     to 0. Technically this is incorrect, because there is no record with
 *     sequence number 0 (yet) and the tail descriptor is not the first
 *     descriptor in the array. But it allows prb_पढ़ो_valid() to correctly
 *     report the existence of a record क्रम _any_ given sequence number at all
 *     बार. Bootstrapping is complete when the tail is pushed the first
 *     समय, thus finally poपूर्णांकing to the first descriptor reserved by a
 *     ग_लिखोr, which has the asचिन्हित sequence number 0.
 */

/*
 * Initiating Logical Value Overflows
 *
 * Both logical position (lpos) and ID values can be mapped to array indexes
 * but may experience overflows during the lअगरeसमय of the प्रणाली. To ensure
 * that prपूर्णांकk_ringbuffer can handle the overflows क्रम these types, initial
 * values are chosen that map to the correct initial array indexes, but will
 * result in overflows soon.
 *
 *   BLK0_LPOS
 *     The initial @head_lpos and @tail_lpos क्रम data rings. It is at index
 *     0 and the lpos value is such that it will overflow on the first wrap.
 *
 *   DESC0_ID
 *     The initial @head_id and @tail_id क्रम the desc ring. It is at the last
 *     index of the descriptor array (see Req3 above) and the ID value is such
 *     that it will overflow on the second wrap.
 */
#घोषणा BLK0_LPOS(sz_bits)	(-(_DATA_SIZE(sz_bits)))
#घोषणा DESC0_ID(ct_bits)	DESC_ID(-(_DESCS_COUNT(ct_bits) + 1))
#घोषणा DESC0_SV(ct_bits)	DESC_SV(DESC0_ID(ct_bits), desc_reusable)

/*
 * Define a ringbuffer with an बाह्यal text data buffer. The same as
 * DEFINE_PRINTKRB() but requires specअगरying an बाह्यal buffer क्रम the
 * text data.
 *
 * Note: The specअगरied बाह्यal buffer must be of the size:
 *       2 ^ (descbits + avgtextbits)
 */
#घोषणा _DEFINE_PRINTKRB(name, descbits, avgtextbits, text_buf)			\
अटल काष्ठा prb_desc _##name##_descs[_DESCS_COUNT(descbits)] = अणु				\
	/* the initial head and tail */								\
	[_DESCS_COUNT(descbits) - 1] = अणु							\
		/* reusable */									\
		.state_var	= ATOMIC_INIT(DESC0_SV(descbits)),				\
		/* no associated data block */							\
		.text_blk_lpos	= FAILED_BLK_LPOS,						\
	पूर्ण,											\
पूर्ण;												\
अटल काष्ठा prपूर्णांकk_info _##name##_infos[_DESCS_COUNT(descbits)] = अणु				\
	/* this will be the first record reserved by a ग_लिखोr */				\
	[0] = अणु											\
		/* will be incremented to 0 on the first reservation */				\
		.seq = -(u64)_DESCS_COUNT(descbits),						\
	पूर्ण,											\
	/* the initial head and tail */								\
	[_DESCS_COUNT(descbits) - 1] = अणु							\
		/* reports the first seq value during the bootstrap phase */			\
		.seq = 0,									\
	पूर्ण,											\
पूर्ण;												\
अटल काष्ठा prपूर्णांकk_ringbuffer name = अणु							\
	.desc_ring = अणु										\
		.count_bits	= descbits,							\
		.descs		= &_##name##_descs[0],						\
		.infos		= &_##name##_infos[0],						\
		.head_id	= ATOMIC_INIT(DESC0_ID(descbits)),				\
		.tail_id	= ATOMIC_INIT(DESC0_ID(descbits)),				\
	पूर्ण,											\
	.text_data_ring = अणु									\
		.size_bits	= (avgtextbits) + (descbits),					\
		.data		= text_buf,							\
		.head_lpos	= ATOMIC_LONG_INIT(BLK0_LPOS((avgtextbits) + (descbits))),	\
		.tail_lpos	= ATOMIC_LONG_INIT(BLK0_LPOS((avgtextbits) + (descbits))),	\
	पूर्ण,											\
	.fail			= ATOMIC_LONG_INIT(0),						\
पूर्ण

/**
 * DEFINE_PRINTKRB() - Define a ringbuffer.
 *
 * @name:        The name of the ringbuffer variable.
 * @descbits:    The number of descriptors as a घातer-of-2 value.
 * @avgtextbits: The average text data size per record as a घातer-of-2 value.
 *
 * This is a macro क्रम defining a ringbuffer and all पूर्णांकernal काष्ठाures
 * such that it is पढ़ोy क्रम immediate use. See _DEFINE_PRINTKRB() क्रम a
 * variant where the text data buffer can be specअगरied बाह्यally.
 */
#घोषणा DEFINE_PRINTKRB(name, descbits, avgtextbits)				\
अटल अक्षर _##name##_text[1U << ((avgtextbits) + (descbits))]			\
			__aligned(__alignof__(अचिन्हित दीर्घ));			\
_DEFINE_PRINTKRB(name, descbits, avgtextbits, &_##name##_text[0])

/* Writer Interface */

/**
 * prb_rec_init_wr() - Initialize a buffer क्रम writing records.
 *
 * @r:             The record to initialize.
 * @text_buf_size: The needed text buffer size.
 */
अटल अंतरभूत व्योम prb_rec_init_wr(काष्ठा prपूर्णांकk_record *r,
				   अचिन्हित पूर्णांक text_buf_size)
अणु
	r->info = शून्य;
	r->text_buf = शून्य;
	r->text_buf_size = text_buf_size;
पूर्ण

bool prb_reserve(काष्ठा prb_reserved_entry *e, काष्ठा prपूर्णांकk_ringbuffer *rb,
		 काष्ठा prपूर्णांकk_record *r);
bool prb_reserve_in_last(काष्ठा prb_reserved_entry *e, काष्ठा prपूर्णांकk_ringbuffer *rb,
			 काष्ठा prपूर्णांकk_record *r, u32 caller_id, अचिन्हित पूर्णांक max_size);
व्योम prb_commit(काष्ठा prb_reserved_entry *e);
व्योम prb_final_commit(काष्ठा prb_reserved_entry *e);

व्योम prb_init(काष्ठा prपूर्णांकk_ringbuffer *rb,
	      अक्षर *text_buf, अचिन्हित पूर्णांक text_buf_size,
	      काष्ठा prb_desc *descs, अचिन्हित पूर्णांक descs_count_bits,
	      काष्ठा prपूर्णांकk_info *infos);
अचिन्हित पूर्णांक prb_record_text_space(काष्ठा prb_reserved_entry *e);

/* Reader Interface */

/**
 * prb_rec_init_rd() - Initialize a buffer क्रम पढ़ोing records.
 *
 * @r:             The record to initialize.
 * @info:          A buffer to store record meta-data.
 * @text_buf:      A buffer to store text data.
 * @text_buf_size: The size of @text_buf.
 *
 * Initialize all the fields that a पढ़ोer is पूर्णांकerested in. All arguments
 * (except @r) are optional. Only record data क्रम arguments that are
 * non-शून्य or non-zero will be पढ़ो.
 */
अटल अंतरभूत व्योम prb_rec_init_rd(काष्ठा prपूर्णांकk_record *r,
				   काष्ठा prपूर्णांकk_info *info,
				   अक्षर *text_buf, अचिन्हित पूर्णांक text_buf_size)
अणु
	r->info = info;
	r->text_buf = text_buf;
	r->text_buf_size = text_buf_size;
पूर्ण

/**
 * prb_क्रम_each_record() - Iterate over the records of a ringbuffer.
 *
 * @from: The sequence number to begin with.
 * @rb:   The ringbuffer to iterate over.
 * @s:    A u64 to store the sequence number on each iteration.
 * @r:    A prपूर्णांकk_record to store the record on each iteration.
 *
 * This is a macro क्रम conveniently iterating over a ringbuffer.
 * Note that @s may not be the sequence number of the record on each
 * iteration. For the sequence number, @r->info->seq should be checked.
 *
 * Context: Any context.
 */
#घोषणा prb_क्रम_each_record(from, rb, s, r) \
क्रम ((s) = from; prb_पढ़ो_valid(rb, s, r); (s) = (r)->info->seq + 1)

/**
 * prb_क्रम_each_info() - Iterate over the meta data of a ringbuffer.
 *
 * @from: The sequence number to begin with.
 * @rb:   The ringbuffer to iterate over.
 * @s:    A u64 to store the sequence number on each iteration.
 * @i:    A prपूर्णांकk_info to store the record meta data on each iteration.
 * @lc:   An अचिन्हित पूर्णांक to store the text line count of each record.
 *
 * This is a macro क्रम conveniently iterating over a ringbuffer.
 * Note that @s may not be the sequence number of the record on each
 * iteration. For the sequence number, @r->info->seq should be checked.
 *
 * Context: Any context.
 */
#घोषणा prb_क्रम_each_info(from, rb, s, i, lc) \
क्रम ((s) = from; prb_पढ़ो_valid_info(rb, s, i, lc); (s) = (i)->seq + 1)

bool prb_पढ़ो_valid(काष्ठा prपूर्णांकk_ringbuffer *rb, u64 seq,
		    काष्ठा prपूर्णांकk_record *r);
bool prb_पढ़ो_valid_info(काष्ठा prपूर्णांकk_ringbuffer *rb, u64 seq,
			 काष्ठा prपूर्णांकk_info *info, अचिन्हित पूर्णांक *line_count);

u64 prb_first_valid_seq(काष्ठा prपूर्णांकk_ringbuffer *rb);
u64 prb_next_seq(काष्ठा prपूर्णांकk_ringbuffer *rb);

#पूर्ण_अगर /* _KERNEL_PRINTK_RINGBUFFER_H */
