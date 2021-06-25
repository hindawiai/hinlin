<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCACHE_JOURNAL_H
#घोषणा _BCACHE_JOURNAL_H

/*
 * THE JOURNAL:
 *
 * The journal is treated as a circular buffer of buckets - a journal entry
 * never spans two buckets. This means (not implemented yet) we can resize the
 * journal at runसमय, and will be needed क्रम bcache on raw flash support.
 *
 * Journal entries contain a list of keys, ordered by the समय they were
 * inserted; thus journal replay just has to reinsert the keys.
 *
 * We also keep some things in the journal header that are logically part of the
 * superblock - all the things that are frequently updated. This is क्रम future
 * bcache on raw flash support; the superblock (which will become another
 * journal) can't be moved or wear leveled, so it contains just enough
 * inक्रमmation to find the मुख्य journal, and the superblock only has to be
 * rewritten when we want to move/wear level the मुख्य journal.
 *
 * Currently, we करोn't journal BTREE_REPLACE operations - this will hopefully be
 * fixed eventually. This isn't a bug - BTREE_REPLACE is used क्रम insertions
 * from cache misses, which करोn't have to be journaled, and क्रम ग_लिखोback and
 * moving gc we work around it by flushing the btree to disk beक्रमe updating the
 * gc inक्रमmation. But it is a potential issue with incremental garbage
 * collection, and it's fragile.
 *
 * OPEN JOURNAL ENTRIES:
 *
 * Each journal entry contains, in the header, the sequence number of the last
 * journal entry still खोलो - i.e. that has keys that haven't been flushed to
 * disk in the btree.
 *
 * We track this by मुख्यtaining a refcount क्रम every खोलो journal entry, in a
 * fअगरo; each entry in the fअगरo corresponds to a particular journal
 * entry/sequence number. When the refcount at the tail of the fअगरo goes to
 * zero, we pop it off - thus, the size of the fअगरo tells us the number of खोलो
 * journal entries
 *
 * We take a refcount on a journal entry when we add some keys to a journal
 * entry that we're going to insert (held by काष्ठा btree_op), and then when we
 * insert those keys पूर्णांकo the btree the btree ग_लिखो we're setting up takes a
 * copy of that refcount (held by काष्ठा btree_ग_लिखो). That refcount is dropped
 * when the btree ग_लिखो completes.
 *
 * A काष्ठा btree_ग_लिखो can only hold a refcount on a single journal entry, but
 * might contain keys क्रम many journal entries - we handle this by making sure
 * it always has a refcount on the _oldest_ journal entry of all the journal
 * entries it has keys क्रम.
 *
 * JOURNAL RECLAIM:
 *
 * As mentioned previously, our fअगरo of refcounts tells us the number of खोलो
 * journal entries; from that and the current journal sequence number we compute
 * last_seq - the oldest journal entry we still need. We ग_लिखो last_seq in each
 * journal entry, and we also have to keep track of where it exists on disk so
 * we करोn't overग_लिखो it when we loop around the journal.
 *
 * To करो that we track, क्रम each journal bucket, the sequence number of the
 * newest journal entry it contains - अगर we करोn't need that journal entry we
 * करोn't need anything in that bucket anymore. From that we track the last
 * journal bucket we still need; all this is tracked in काष्ठा journal_device
 * and updated by journal_reclaim().
 *
 * JOURNAL FILLING UP:
 *
 * There are two ways the journal could fill up; either we could run out of
 * space to ग_लिखो to, or we could have too many खोलो journal entries and run out
 * of room in the fअगरo of refcounts. Since those refcounts are decremented
 * without any locking we can't safely resize that fअगरo, so we handle it the
 * same way.
 *
 * If the journal fills up, we start flushing dirty btree nodes until we can
 * allocate space क्रम a journal ग_लिखो again - preferentially flushing btree
 * nodes that are pinning the oldest journal entries first.
 */

/*
 * Only used क्रम holding the journal entries we पढ़ो in btree_journal_पढ़ो()
 * during cache_registration
 */
काष्ठा journal_replay अणु
	काष्ठा list_head	list;
	atomic_t		*pin;
	काष्ठा jset		j;
पूर्ण;

/*
 * We put two of these in काष्ठा journal; we used them क्रम ग_लिखोs to the
 * journal that are being staged or in flight.
 */
काष्ठा journal_ग_लिखो अणु
	काष्ठा jset		*data;
#घोषणा JSET_BITS		3

	काष्ठा cache_set	*c;
	काष्ठा closure_रुकोlist	रुको;
	bool			dirty;
	bool			need_ग_लिखो;
पूर्ण;

/* Embedded in काष्ठा cache_set */
काष्ठा journal अणु
	spinlock_t		lock;
	spinlock_t		flush_ग_लिखो_lock;
	bool			btree_flushing;
	/* used when रुकोing because the journal was full */
	काष्ठा closure_रुकोlist	रुको;
	काष्ठा closure		io;
	पूर्णांक			io_in_flight;
	काष्ठा delayed_work	work;

	/* Number of blocks मुक्त in the bucket(s) we're currently writing to */
	अचिन्हित पूर्णांक		blocks_मुक्त;
	uपूर्णांक64_t		seq;
	DECLARE_FIFO(atomic_t, pin);

	BKEY_PADDED(key);

	काष्ठा journal_ग_लिखो	w[2], *cur;
पूर्ण;

/*
 * Embedded in काष्ठा cache. First three fields refer to the array of journal
 * buckets, in cache_sb.
 */
काष्ठा journal_device अणु
	/*
	 * For each journal bucket, contains the max sequence number of the
	 * journal ग_लिखोs it contains - so we know when a bucket can be reused.
	 */
	uपूर्णांक64_t		seq[SB_JOURNAL_BUCKETS];

	/* Journal bucket we're currently writing to */
	अचिन्हित पूर्णांक		cur_idx;

	/* Last journal bucket that still contains an खोलो journal entry */
	अचिन्हित पूर्णांक		last_idx;

	/* Next journal bucket to be discarded */
	अचिन्हित पूर्णांक		discard_idx;

#घोषणा DISCARD_READY		0
#घोषणा DISCARD_IN_FLIGHT	1
#घोषणा DISCARD_DONE		2
	/* 1 - discard in flight, -1 - discard completed */
	atomic_t		discard_in_flight;

	काष्ठा work_काष्ठा	discard_work;
	काष्ठा bio		discard_bio;
	काष्ठा bio_vec		discard_bv;

	/* Bio क्रम journal पढ़ोs/ग_लिखोs to this device */
	काष्ठा bio		bio;
	काष्ठा bio_vec		bv[8];
पूर्ण;

#घोषणा BTREE_FLUSH_NR	8

#घोषणा journal_pin_cmp(c, l, r)				\
	(fअगरo_idx(&(c)->journal.pin, (l)) > fअगरo_idx(&(c)->journal.pin, (r)))

#घोषणा JOURNAL_PIN	20000

#घोषणा journal_full(j)						\
	(!(j)->blocks_मुक्त || fअगरo_मुक्त(&(j)->pin) <= 1)

काष्ठा closure;
काष्ठा cache_set;
काष्ठा btree_op;
काष्ठा keylist;

atomic_t *bch_journal(काष्ठा cache_set *c,
		      काष्ठा keylist *keys,
		      काष्ठा closure *parent);
व्योम bch_journal_next(काष्ठा journal *j);
व्योम bch_journal_mark(काष्ठा cache_set *c, काष्ठा list_head *list);
व्योम bch_journal_meta(काष्ठा cache_set *c, काष्ठा closure *cl);
पूर्णांक bch_journal_पढ़ो(काष्ठा cache_set *c, काष्ठा list_head *list);
पूर्णांक bch_journal_replay(काष्ठा cache_set *c, काष्ठा list_head *list);

व्योम bch_journal_मुक्त(काष्ठा cache_set *c);
पूर्णांक bch_journal_alloc(काष्ठा cache_set *c);

#पूर्ण_अगर /* _BCACHE_JOURNAL_H */
