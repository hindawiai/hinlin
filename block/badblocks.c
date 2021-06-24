<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Bad block management
 *
 * - Heavily based on MD badblocks code from Neil Brown
 *
 * Copyright (c) 2015, Intel Corporation.
 */

#समावेश <linux/badblocks.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>

/**
 * badblocks_check() - check a given range क्रम bad sectors
 * @bb:		the badblocks काष्ठाure that holds all badblock inक्रमmation
 * @s:		sector (start) at which to check क्रम badblocks
 * @sectors:	number of sectors to check क्रम badblocks
 * @first_bad:	poपूर्णांकer to store location of the first badblock
 * @bad_sectors: poपूर्णांकer to store number of badblocks after @first_bad
 *
 * We can record which blocks on each device are 'bad' and so just
 * fail those blocks, or that stripe, rather than the whole device.
 * Entries in the bad-block table are 64bits wide.  This comprises:
 * Length of bad-range, in sectors: 0-511 क्रम lengths 1-512
 * Start of bad-range, sector offset, 54 bits (allows 8 exbibytes)
 *  A 'shift' can be set so that larger blocks are tracked and
 *  consequently larger devices can be covered.
 * 'Acknowledged' flag - 1 bit. - the most signअगरicant bit.
 *
 * Locking of the bad-block table uses a seqlock so badblocks_check
 * might need to retry अगर it is very unlucky.
 * We will someबार want to check क्रम bad blocks in a bi_end_io function,
 * so we use the ग_लिखो_seqlock_irq variant.
 *
 * When looking क्रम a bad block we specअगरy a range and want to
 * know अगर any block in the range is bad.  So we binary-search
 * to the last range that starts at-or-beक्रमe the given endpoपूर्णांक,
 * (or "before the sector after the target range")
 * then see अगर it ends after the given start.
 *
 * Return:
 *  0: there are no known bad blocks in the range
 *  1: there are known bad block which are all acknowledged
 * -1: there are bad blocks which have not yet been acknowledged in metadata.
 * plus the start/length of the first bad section we overlap.
 */
पूर्णांक badblocks_check(काष्ठा badblocks *bb, sector_t s, पूर्णांक sectors,
			sector_t *first_bad, पूर्णांक *bad_sectors)
अणु
	पूर्णांक hi;
	पूर्णांक lo;
	u64 *p = bb->page;
	पूर्णांक rv;
	sector_t target = s + sectors;
	अचिन्हित seq;

	अगर (bb->shअगरt > 0) अणु
		/* round the start करोwn, and the end up */
		s >>= bb->shअगरt;
		target += (1<<bb->shअगरt) - 1;
		target >>= bb->shअगरt;
		sectors = target - s;
	पूर्ण
	/* 'target' is now the first block after the bad range */

retry:
	seq = पढ़ो_seqbegin(&bb->lock);
	lo = 0;
	rv = 0;
	hi = bb->count;

	/* Binary search between lo and hi क्रम 'target'
	 * i.e. क्रम the last range that starts beक्रमe 'target'
	 */
	/* INVARIANT: ranges beक्रमe 'lo' and at-or-after 'hi'
	 * are known not to be the last range beक्रमe target.
	 * VARIANT: hi-lo is the number of possible
	 * ranges, and decreases until it reaches 1
	 */
	जबतक (hi - lo > 1) अणु
		पूर्णांक mid = (lo + hi) / 2;
		sector_t a = BB_OFFSET(p[mid]);

		अगर (a < target)
			/* This could still be the one, earlier ranges
			 * could not.
			 */
			lo = mid;
		अन्यथा
			/* This and later ranges are definitely out. */
			hi = mid;
	पूर्ण
	/* 'lo' might be the last that started before target, but 'hi' isn't */
	अगर (hi > lo) अणु
		/* need to check all range that end after 's' to see अगर
		 * any are unacknowledged.
		 */
		जबतक (lo >= 0 &&
		       BB_OFFSET(p[lo]) + BB_LEN(p[lo]) > s) अणु
			अगर (BB_OFFSET(p[lo]) < target) अणु
				/* starts beक्रमe the end, and finishes after
				 * the start, so they must overlap
				 */
				अगर (rv != -1 && BB_ACK(p[lo]))
					rv = 1;
				अन्यथा
					rv = -1;
				*first_bad = BB_OFFSET(p[lo]);
				*bad_sectors = BB_LEN(p[lo]);
			पूर्ण
			lo--;
		पूर्ण
	पूर्ण

	अगर (पढ़ो_seqretry(&bb->lock, seq))
		जाओ retry;

	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(badblocks_check);

अटल व्योम badblocks_update_acked(काष्ठा badblocks *bb)
अणु
	u64 *p = bb->page;
	पूर्णांक i;
	bool unacked = false;

	अगर (!bb->unacked_exist)
		वापस;

	क्रम (i = 0; i < bb->count ; i++) अणु
		अगर (!BB_ACK(p[i])) अणु
			unacked = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!unacked)
		bb->unacked_exist = 0;
पूर्ण

/**
 * badblocks_set() - Add a range of bad blocks to the table.
 * @bb:		the badblocks काष्ठाure that holds all badblock inक्रमmation
 * @s:		first sector to mark as bad
 * @sectors:	number of sectors to mark as bad
 * @acknowledged: weather to mark the bad sectors as acknowledged
 *
 * This might extend the table, or might contract it अगर two adjacent ranges
 * can be merged. We binary-search to find the 'insertion' poपूर्णांक, then
 * decide how best to handle it.
 *
 * Return:
 *  0: success
 *  1: failed to set badblocks (out of space)
 */
पूर्णांक badblocks_set(काष्ठा badblocks *bb, sector_t s, पूर्णांक sectors,
			पूर्णांक acknowledged)
अणु
	u64 *p;
	पूर्णांक lo, hi;
	पूर्णांक rv = 0;
	अचिन्हित दीर्घ flags;

	अगर (bb->shअगरt < 0)
		/* badblocks are disabled */
		वापस 1;

	अगर (bb->shअगरt) अणु
		/* round the start करोwn, and the end up */
		sector_t next = s + sectors;

		s >>= bb->shअगरt;
		next += (1<<bb->shअगरt) - 1;
		next >>= bb->shअगरt;
		sectors = next - s;
	पूर्ण

	ग_लिखो_seqlock_irqsave(&bb->lock, flags);

	p = bb->page;
	lo = 0;
	hi = bb->count;
	/* Find the last range that starts at-or-beक्रमe 's' */
	जबतक (hi - lo > 1) अणु
		पूर्णांक mid = (lo + hi) / 2;
		sector_t a = BB_OFFSET(p[mid]);

		अगर (a <= s)
			lo = mid;
		अन्यथा
			hi = mid;
	पूर्ण
	अगर (hi > lo && BB_OFFSET(p[lo]) > s)
		hi = lo;

	अगर (hi > lo) अणु
		/* we found a range that might merge with the start
		 * of our new range
		 */
		sector_t a = BB_OFFSET(p[lo]);
		sector_t e = a + BB_LEN(p[lo]);
		पूर्णांक ack = BB_ACK(p[lo]);

		अगर (e >= s) अणु
			/* Yes, we can merge with a previous range */
			अगर (s == a && s + sectors >= e)
				/* new range covers old */
				ack = acknowledged;
			अन्यथा
				ack = ack && acknowledged;

			अगर (e < s + sectors)
				e = s + sectors;
			अगर (e - a <= BB_MAX_LEN) अणु
				p[lo] = BB_MAKE(a, e-a, ack);
				s = e;
			पूर्ण अन्यथा अणु
				/* करोes not all fit in one range,
				 * make p[lo] maximal
				 */
				अगर (BB_LEN(p[lo]) != BB_MAX_LEN)
					p[lo] = BB_MAKE(a, BB_MAX_LEN, ack);
				s = a + BB_MAX_LEN;
			पूर्ण
			sectors = e - s;
		पूर्ण
	पूर्ण
	अगर (sectors && hi < bb->count) अणु
		/* 'hi' points to the first range that starts after 's'.
		 * Maybe we can merge with the start of that range
		 */
		sector_t a = BB_OFFSET(p[hi]);
		sector_t e = a + BB_LEN(p[hi]);
		पूर्णांक ack = BB_ACK(p[hi]);

		अगर (a <= s + sectors) अणु
			/* merging is possible */
			अगर (e <= s + sectors) अणु
				/* full overlap */
				e = s + sectors;
				ack = acknowledged;
			पूर्ण अन्यथा
				ack = ack && acknowledged;

			a = s;
			अगर (e - a <= BB_MAX_LEN) अणु
				p[hi] = BB_MAKE(a, e-a, ack);
				s = e;
			पूर्ण अन्यथा अणु
				p[hi] = BB_MAKE(a, BB_MAX_LEN, ack);
				s = a + BB_MAX_LEN;
			पूर्ण
			sectors = e - s;
			lo = hi;
			hi++;
		पूर्ण
	पूर्ण
	अगर (sectors == 0 && hi < bb->count) अणु
		/* we might be able to combine lo and hi */
		/* Note: 's' is at the end of 'lo' */
		sector_t a = BB_OFFSET(p[hi]);
		पूर्णांक lolen = BB_LEN(p[lo]);
		पूर्णांक hilen = BB_LEN(p[hi]);
		पूर्णांक newlen = lolen + hilen - (s - a);

		अगर (s >= a && newlen < BB_MAX_LEN) अणु
			/* yes, we can combine them */
			पूर्णांक ack = BB_ACK(p[lo]) && BB_ACK(p[hi]);

			p[lo] = BB_MAKE(BB_OFFSET(p[lo]), newlen, ack);
			स_हटाओ(p + hi, p + hi + 1,
				(bb->count - hi - 1) * 8);
			bb->count--;
		पूर्ण
	पूर्ण
	जबतक (sectors) अणु
		/* didn't merge (it all).
		 * Need to add a range just beक्रमe 'hi'
		 */
		अगर (bb->count >= MAX_BADBLOCKS) अणु
			/* No room क्रम more */
			rv = 1;
			अवरोध;
		पूर्ण अन्यथा अणु
			पूर्णांक this_sectors = sectors;

			स_हटाओ(p + hi + 1, p + hi,
				(bb->count - hi) * 8);
			bb->count++;

			अगर (this_sectors > BB_MAX_LEN)
				this_sectors = BB_MAX_LEN;
			p[hi] = BB_MAKE(s, this_sectors, acknowledged);
			sectors -= this_sectors;
			s += this_sectors;
		पूर्ण
	पूर्ण

	bb->changed = 1;
	अगर (!acknowledged)
		bb->unacked_exist = 1;
	अन्यथा
		badblocks_update_acked(bb);
	ग_लिखो_sequnlock_irqrestore(&bb->lock, flags);

	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(badblocks_set);

/**
 * badblocks_clear() - Remove a range of bad blocks to the table.
 * @bb:		the badblocks काष्ठाure that holds all badblock inक्रमmation
 * @s:		first sector to mark as bad
 * @sectors:	number of sectors to mark as bad
 *
 * This may involve extending the table अगर we spilt a region,
 * but it must not fail.  So अगर the table becomes full, we just
 * drop the हटाओ request.
 *
 * Return:
 *  0: success
 *  1: failed to clear badblocks
 */
पूर्णांक badblocks_clear(काष्ठा badblocks *bb, sector_t s, पूर्णांक sectors)
अणु
	u64 *p;
	पूर्णांक lo, hi;
	sector_t target = s + sectors;
	पूर्णांक rv = 0;

	अगर (bb->shअगरt > 0) अणु
		/* When clearing we round the start up and the end करोwn.
		 * This should not matter as the shअगरt should align with
		 * the block size and no rounding should ever be needed.
		 * However it is better the think a block is bad when it
		 * isn't than to think a block is not bad when it is.
		 */
		s += (1<<bb->shअगरt) - 1;
		s >>= bb->shअगरt;
		target >>= bb->shअगरt;
		sectors = target - s;
	पूर्ण

	ग_लिखो_seqlock_irq(&bb->lock);

	p = bb->page;
	lo = 0;
	hi = bb->count;
	/* Find the last range that starts beक्रमe 'target' */
	जबतक (hi - lo > 1) अणु
		पूर्णांक mid = (lo + hi) / 2;
		sector_t a = BB_OFFSET(p[mid]);

		अगर (a < target)
			lo = mid;
		अन्यथा
			hi = mid;
	पूर्ण
	अगर (hi > lo) अणु
		/* p[lo] is the last range that could overlap the
		 * current range.  Earlier ranges could also overlap,
		 * but only this one can overlap the end of the range.
		 */
		अगर ((BB_OFFSET(p[lo]) + BB_LEN(p[lo]) > target) &&
		    (BB_OFFSET(p[lo]) < target)) अणु
			/* Partial overlap, leave the tail of this range */
			पूर्णांक ack = BB_ACK(p[lo]);
			sector_t a = BB_OFFSET(p[lo]);
			sector_t end = a + BB_LEN(p[lo]);

			अगर (a < s) अणु
				/* we need to split this range */
				अगर (bb->count >= MAX_BADBLOCKS) अणु
					rv = -ENOSPC;
					जाओ out;
				पूर्ण
				स_हटाओ(p+lo+1, p+lo, (bb->count - lo) * 8);
				bb->count++;
				p[lo] = BB_MAKE(a, s-a, ack);
				lo++;
			पूर्ण
			p[lo] = BB_MAKE(target, end - target, ack);
			/* there is no दीर्घer an overlap */
			hi = lo;
			lo--;
		पूर्ण
		जबतक (lo >= 0 &&
		       (BB_OFFSET(p[lo]) + BB_LEN(p[lo]) > s) &&
		       (BB_OFFSET(p[lo]) < target)) अणु
			/* This range करोes overlap */
			अगर (BB_OFFSET(p[lo]) < s) अणु
				/* Keep the early parts of this range. */
				पूर्णांक ack = BB_ACK(p[lo]);
				sector_t start = BB_OFFSET(p[lo]);

				p[lo] = BB_MAKE(start, s - start, ack);
				/* now low करोesn't overlap, so.. */
				अवरोध;
			पूर्ण
			lo--;
		पूर्ण
		/* 'lo' is strictly before, 'hi' is strictly after,
		 * anything between needs to be discarded
		 */
		अगर (hi - lo > 1) अणु
			स_हटाओ(p+lo+1, p+hi, (bb->count - hi) * 8);
			bb->count -= (hi - lo - 1);
		पूर्ण
	पूर्ण

	badblocks_update_acked(bb);
	bb->changed = 1;
out:
	ग_लिखो_sequnlock_irq(&bb->lock);
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(badblocks_clear);

/**
 * ack_all_badblocks() - Acknowledge all bad blocks in a list.
 * @bb:		the badblocks काष्ठाure that holds all badblock inक्रमmation
 *
 * This only succeeds अगर ->changed is clear.  It is used by
 * in-kernel metadata updates
 */
व्योम ack_all_badblocks(काष्ठा badblocks *bb)
अणु
	अगर (bb->page == शून्य || bb->changed)
		/* no poपूर्णांक even trying */
		वापस;
	ग_लिखो_seqlock_irq(&bb->lock);

	अगर (bb->changed == 0 && bb->unacked_exist) अणु
		u64 *p = bb->page;
		पूर्णांक i;

		क्रम (i = 0; i < bb->count ; i++) अणु
			अगर (!BB_ACK(p[i])) अणु
				sector_t start = BB_OFFSET(p[i]);
				पूर्णांक len = BB_LEN(p[i]);

				p[i] = BB_MAKE(start, len, 1);
			पूर्ण
		पूर्ण
		bb->unacked_exist = 0;
	पूर्ण
	ग_लिखो_sequnlock_irq(&bb->lock);
पूर्ण
EXPORT_SYMBOL_GPL(ack_all_badblocks);

/**
 * badblocks_show() - sysfs access to bad-blocks list
 * @bb:		the badblocks काष्ठाure that holds all badblock inक्रमmation
 * @page:	buffer received from sysfs
 * @unack:	weather to show unacknowledged badblocks
 *
 * Return:
 *  Length of वापसed data
 */
sमाप_प्रकार badblocks_show(काष्ठा badblocks *bb, अक्षर *page, पूर्णांक unack)
अणु
	माप_प्रकार len;
	पूर्णांक i;
	u64 *p = bb->page;
	अचिन्हित seq;

	अगर (bb->shअगरt < 0)
		वापस 0;

retry:
	seq = पढ़ो_seqbegin(&bb->lock);

	len = 0;
	i = 0;

	जबतक (len < PAGE_SIZE && i < bb->count) अणु
		sector_t s = BB_OFFSET(p[i]);
		अचिन्हित पूर्णांक length = BB_LEN(p[i]);
		पूर्णांक ack = BB_ACK(p[i]);

		i++;

		अगर (unack && ack)
			जारी;

		len += snम_लिखो(page+len, PAGE_SIZE-len, "%llu %u\n",
				(अचिन्हित दीर्घ दीर्घ)s << bb->shअगरt,
				length << bb->shअगरt);
	पूर्ण
	अगर (unack && len == 0)
		bb->unacked_exist = 0;

	अगर (पढ़ो_seqretry(&bb->lock, seq))
		जाओ retry;

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(badblocks_show);

/**
 * badblocks_store() - sysfs access to bad-blocks list
 * @bb:		the badblocks काष्ठाure that holds all badblock inक्रमmation
 * @page:	buffer received from sysfs
 * @len:	length of data received from sysfs
 * @unack:	weather to show unacknowledged badblocks
 *
 * Return:
 *  Length of the buffer processed or -ve error.
 */
sमाप_प्रकार badblocks_store(काष्ठा badblocks *bb, स्थिर अक्षर *page, माप_प्रकार len,
			पूर्णांक unack)
अणु
	अचिन्हित दीर्घ दीर्घ sector;
	पूर्णांक length;
	अक्षर newline;

	चयन (माला_पूछो(page, "%llu %d%c", &sector, &length, &newline)) अणु
	हाल 3:
		अगर (newline != '\n')
			वापस -EINVAL;
		fallthrough;
	हाल 2:
		अगर (length <= 0)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (badblocks_set(bb, sector, length, !unack))
		वापस -ENOSPC;
	अन्यथा
		वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(badblocks_store);

अटल पूर्णांक __badblocks_init(काष्ठा device *dev, काष्ठा badblocks *bb,
		पूर्णांक enable)
अणु
	bb->dev = dev;
	bb->count = 0;
	अगर (enable)
		bb->shअगरt = 0;
	अन्यथा
		bb->shअगरt = -1;
	अगर (dev)
		bb->page = devm_kzalloc(dev, PAGE_SIZE, GFP_KERNEL);
	अन्यथा
		bb->page = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!bb->page) अणु
		bb->shअगरt = -1;
		वापस -ENOMEM;
	पूर्ण
	seqlock_init(&bb->lock);

	वापस 0;
पूर्ण

/**
 * badblocks_init() - initialize the badblocks काष्ठाure
 * @bb:		the badblocks काष्ठाure that holds all badblock inक्रमmation
 * @enable:	weather to enable badblocks accounting
 *
 * Return:
 *  0: success
 *  -ve त्रुटि_सं: on error
 */
पूर्णांक badblocks_init(काष्ठा badblocks *bb, पूर्णांक enable)
अणु
	वापस __badblocks_init(शून्य, bb, enable);
पूर्ण
EXPORT_SYMBOL_GPL(badblocks_init);

पूर्णांक devm_init_badblocks(काष्ठा device *dev, काष्ठा badblocks *bb)
अणु
	अगर (!bb)
		वापस -EINVAL;
	वापस __badblocks_init(dev, bb, 1);
पूर्ण
EXPORT_SYMBOL_GPL(devm_init_badblocks);

/**
 * badblocks_निकास() - मुक्त the badblocks काष्ठाure
 * @bb:		the badblocks काष्ठाure that holds all badblock inक्रमmation
 */
व्योम badblocks_निकास(काष्ठा badblocks *bb)
अणु
	अगर (!bb)
		वापस;
	अगर (bb->dev)
		devm_kमुक्त(bb->dev, bb->page);
	अन्यथा
		kमुक्त(bb->page);
	bb->page = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(badblocks_निकास);
