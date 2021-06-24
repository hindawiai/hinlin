<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   drbd_biपंचांगap.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2004-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 2004-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2004-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.

 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/माला.स>
#समावेश <linux/drbd.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>

#समावेश "drbd_int.h"


/* OPAQUE outside this file!
 * पूर्णांकerface defined in drbd_पूर्णांक.h

 * convention:
 * function name drbd_bm_... => used अन्यथाwhere, "public".
 * function name      bm_... => पूर्णांकernal to implementation, "private".
 */


/*
 * LIMITATIONS:
 * We want to support >= peta byte of backend storage, जबतक क्रम now still using
 * a granularity of one bit per 4KiB of storage.
 * 1 << 50		bytes backend storage (1 PiB)
 * 1 << (50 - 12)	bits needed
 *	38 --> we need u64 to index and count bits
 * 1 << (38 - 3)	biपंचांगap bytes needed
 *	35 --> we still need u64 to index and count bytes
 *			(that's 32 GiB of biपंचांगap क्रम 1 PiB storage)
 * 1 << (35 - 2)	32bit दीर्घs needed
 *	33 --> we'd even need u64 to index and count 32bit दीर्घ words.
 * 1 << (35 - 3)	64bit दीर्घs needed
 *	32 --> we could get away with a 32bit अचिन्हित पूर्णांक to index and count
 *	64bit दीर्घ words, but I rather stay with अचिन्हित दीर्घ क्रम now.
 *	We probably should neither count nor poपूर्णांक to bytes or दीर्घ words
 *	directly, but either by bitnumber, or by page index and offset.
 * 1 << (35 - 12)
 *	22 --> we need that much 4KiB pages of biपंचांगap.
 *	1 << (22 + 3) --> on a 64bit arch,
 *	we need 32 MiB to store the array of page poपूर्णांकers.
 *
 * Because I'm lazy, and because the resulting patch was too large, too ugly
 * and still incomplete, on 32bit we still "only" support 16 TiB (minus some),
 * (1 << 32) bits * 4k storage.
 *

 * biपंचांगap storage and IO:
 *	Biपंचांगap is stored little endian on disk, and is kept little endian in
 *	core memory. Currently we still hold the full biपंचांगap in core as दीर्घ
 *	as we are "attached" to a local disk, which at 32 GiB क्रम 1PiB storage
 *	seems excessive.
 *
 *	We plan to reduce the amount of in-core biपंचांगap pages by paging them in
 *	and out against their on-disk location as necessary, but need to make
 *	sure we करोn't cause too much meta data IO, and must not deadlock in
 *	tight memory situations. This needs some more work.
 */

/*
 * NOTE
 *  Access to the *bm_pages is रक्षित by bm_lock.
 *  It is safe to पढ़ो the other members within the lock.
 *
 *  drbd_bm_set_bits is called from bio_endio callbacks,
 *  We may be called with irq alपढ़ोy disabled,
 *  so we need spin_lock_irqsave().
 *  And we need the kmap_atomic.
 */
काष्ठा drbd_biपंचांगap अणु
	काष्ठा page **bm_pages;
	spinlock_t bm_lock;

	/* exclusively to be used by __al_ग_लिखो_transaction(),
	 * drbd_bm_mark_क्रम_ग_लिखोout() and
	 * and drbd_bm_ग_लिखो_hपूर्णांकed() -> bm_rw() called from there.
	 */
	अचिन्हित पूर्णांक n_biपंचांगap_hपूर्णांकs;
	अचिन्हित पूर्णांक al_biपंचांगap_hपूर्णांकs[AL_UPDATES_PER_TRANSACTION];

	/* see LIMITATIONS: above */

	अचिन्हित दीर्घ bm_set;       /* nr of set bits; THINK maybe atomic_t? */
	अचिन्हित दीर्घ bm_bits;
	माप_प्रकार   bm_words;
	माप_प्रकार   bm_number_of_pages;
	sector_t bm_dev_capacity;
	काष्ठा mutex bm_change; /* serializes resize operations */

	रुको_queue_head_t bm_io_रुको; /* used to serialize IO of single pages */

	क्रमागत bm_flag bm_flags;

	/* debugging aid, in हाल we are still racy somewhere */
	अक्षर          *bm_why;
	काष्ठा task_काष्ठा *bm_task;
पूर्ण;

#घोषणा bm_prपूर्णांक_lock_info(m) __bm_prपूर्णांक_lock_info(m, __func__)
अटल व्योम __bm_prपूर्णांक_lock_info(काष्ठा drbd_device *device, स्थिर अक्षर *func)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अगर (!__ratelimit(&drbd_ratelimit_state))
		वापस;
	drbd_err(device, "FIXME %s[%d] in %s, bitmap locked for '%s' by %s[%d]\n",
		 current->comm, task_pid_nr(current),
		 func, b->bm_why ?: "?",
		 b->bm_task->comm, task_pid_nr(b->bm_task));
पूर्ण

व्योम drbd_bm_lock(काष्ठा drbd_device *device, अक्षर *why, क्रमागत bm_flag flags)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	पूर्णांक trylock_failed;

	अगर (!b) अणु
		drbd_err(device, "FIXME no bitmap in drbd_bm_lock!?\n");
		वापस;
	पूर्ण

	trylock_failed = !mutex_trylock(&b->bm_change);

	अगर (trylock_failed) अणु
		drbd_warn(device, "%s[%d] going to '%s' but bitmap already locked for '%s' by %s[%d]\n",
			  current->comm, task_pid_nr(current),
			  why, b->bm_why ?: "?",
			  b->bm_task->comm, task_pid_nr(b->bm_task));
		mutex_lock(&b->bm_change);
	पूर्ण
	अगर (BM_LOCKED_MASK & b->bm_flags)
		drbd_err(device, "FIXME bitmap already locked in bm_lock\n");
	b->bm_flags |= flags & BM_LOCKED_MASK;

	b->bm_why  = why;
	b->bm_task = current;
पूर्ण

व्योम drbd_bm_unlock(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अगर (!b) अणु
		drbd_err(device, "FIXME no bitmap in drbd_bm_unlock!?\n");
		वापस;
	पूर्ण

	अगर (!(BM_LOCKED_MASK & device->biपंचांगap->bm_flags))
		drbd_err(device, "FIXME bitmap not locked in bm_unlock\n");

	b->bm_flags &= ~BM_LOCKED_MASK;
	b->bm_why  = शून्य;
	b->bm_task = शून्य;
	mutex_unlock(&b->bm_change);
पूर्ण

/* we store some "meta" info about our pages in page->निजी */
/* at a granularity of 4k storage per biपंचांगap bit:
 * one peta byte storage: 1<<50 byte, 1<<38 * 4k storage blocks
 *  1<<38 bits,
 *  1<<23 4k biपंचांगap pages.
 * Use 24 bits as page index, covers 2 peta byte storage
 * at a granularity of 4k per bit.
 * Used to report the failed page idx on io error from the endio handlers.
 */
#घोषणा BM_PAGE_IDX_MASK	((1UL<<24)-1)
/* this page is currently पढ़ो in, or written back */
#घोषणा BM_PAGE_IO_LOCK		31
/* अगर there has been an IO error क्रम this page */
#घोषणा BM_PAGE_IO_ERROR	30
/* this is to be able to पूर्णांकelligently skip disk IO,
 * set अगर bits have been set since last IO. */
#घोषणा BM_PAGE_NEED_WRITEOUT	29
/* to mark क्रम lazy ग_लिखोout once syncer cleared all clearable bits,
 * we अगर bits have been cleared since last IO. */
#घोषणा BM_PAGE_LAZY_WRITEOUT	28
/* pages marked with this "HINT" will be considered क्रम ग_लिखोout
 * on activity log transactions */
#घोषणा BM_PAGE_HINT_WRITEOUT	27

/* store_page_idx uses non-atomic assignment. It is only used directly after
 * allocating the page.  All other bm_set_page_* and bm_clear_page_* need to
 * use atomic bit manipulation, as set_out_of_sync (and thereक्रमe biपंचांगap
 * changes) may happen from various contexts, and रुको_on_bit/wake_up_bit
 * requires it all to be atomic as well. */
अटल व्योम bm_store_page_idx(काष्ठा page *page, अचिन्हित दीर्घ idx)
अणु
	BUG_ON(0 != (idx & ~BM_PAGE_IDX_MASK));
	set_page_निजी(page, idx);
पूर्ण

अटल अचिन्हित दीर्घ bm_page_to_idx(काष्ठा page *page)
अणु
	वापस page_निजी(page) & BM_PAGE_IDX_MASK;
पूर्ण

/* As is very unlikely that the same page is under IO from more than one
 * context, we can get away with a bit per page and one रुको queue per biपंचांगap.
 */
अटल व्योम bm_page_lock_io(काष्ठा drbd_device *device, पूर्णांक page_nr)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	व्योम *addr = &page_निजी(b->bm_pages[page_nr]);
	रुको_event(b->bm_io_रुको, !test_and_set_bit(BM_PAGE_IO_LOCK, addr));
पूर्ण

अटल व्योम bm_page_unlock_io(काष्ठा drbd_device *device, पूर्णांक page_nr)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	व्योम *addr = &page_निजी(b->bm_pages[page_nr]);
	clear_bit_unlock(BM_PAGE_IO_LOCK, addr);
	wake_up(&device->biपंचांगap->bm_io_रुको);
पूर्ण

/* set _beक्रमe_ submit_io, so it may be reset due to being changed
 * जबतक this page is in flight... will get submitted later again */
अटल व्योम bm_set_page_unchanged(काष्ठा page *page)
अणु
	/* use cmpxchg? */
	clear_bit(BM_PAGE_NEED_WRITEOUT, &page_निजी(page));
	clear_bit(BM_PAGE_LAZY_WRITEOUT, &page_निजी(page));
पूर्ण

अटल व्योम bm_set_page_need_ग_लिखोout(काष्ठा page *page)
अणु
	set_bit(BM_PAGE_NEED_WRITEOUT, &page_निजी(page));
पूर्ण

व्योम drbd_bm_reset_al_hपूर्णांकs(काष्ठा drbd_device *device)
अणु
	device->biपंचांगap->n_biपंचांगap_hपूर्णांकs = 0;
पूर्ण

/**
 * drbd_bm_mark_क्रम_ग_लिखोout() - mark a page with a "hint" to be considered क्रम ग_लिखोout
 * @device:	DRBD device.
 * @page_nr:	the biपंचांगap page to mark with the "hint" flag
 *
 * From within an activity log transaction, we mark a few pages with these
 * hपूर्णांकs, then call drbd_bm_ग_लिखो_hपूर्णांकed(), which will only ग_लिखो out changed
 * pages which are flagged with this mark.
 */
व्योम drbd_bm_mark_क्रम_ग_लिखोout(काष्ठा drbd_device *device, पूर्णांक page_nr)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	काष्ठा page *page;
	अगर (page_nr >= device->biपंचांगap->bm_number_of_pages) अणु
		drbd_warn(device, "BAD: page_nr: %u, number_of_pages: %u\n",
			 page_nr, (पूर्णांक)device->biपंचांगap->bm_number_of_pages);
		वापस;
	पूर्ण
	page = device->biपंचांगap->bm_pages[page_nr];
	BUG_ON(b->n_biपंचांगap_hपूर्णांकs >= ARRAY_SIZE(b->al_biपंचांगap_hपूर्णांकs));
	अगर (!test_and_set_bit(BM_PAGE_HINT_WRITEOUT, &page_निजी(page)))
		b->al_biपंचांगap_hपूर्णांकs[b->n_biपंचांगap_hपूर्णांकs++] = page_nr;
पूर्ण

अटल पूर्णांक bm_test_page_unchanged(काष्ठा page *page)
अणु
	अस्थिर स्थिर अचिन्हित दीर्घ *addr = &page_निजी(page);
	वापस (*addr & ((1UL<<BM_PAGE_NEED_WRITEOUT)|(1UL<<BM_PAGE_LAZY_WRITEOUT))) == 0;
पूर्ण

अटल व्योम bm_set_page_io_err(काष्ठा page *page)
अणु
	set_bit(BM_PAGE_IO_ERROR, &page_निजी(page));
पूर्ण

अटल व्योम bm_clear_page_io_err(काष्ठा page *page)
अणु
	clear_bit(BM_PAGE_IO_ERROR, &page_निजी(page));
पूर्ण

अटल व्योम bm_set_page_lazy_ग_लिखोout(काष्ठा page *page)
अणु
	set_bit(BM_PAGE_LAZY_WRITEOUT, &page_निजी(page));
पूर्ण

अटल पूर्णांक bm_test_page_lazy_ग_लिखोout(काष्ठा page *page)
अणु
	वापस test_bit(BM_PAGE_LAZY_WRITEOUT, &page_निजी(page));
पूर्ण

/* on a 32bit box, this would allow क्रम exactly (2<<38) bits. */
अटल अचिन्हित पूर्णांक bm_word_to_page_idx(काष्ठा drbd_biपंचांगap *b, अचिन्हित दीर्घ दीर्घ_nr)
अणु
	/* page_nr = (word*माप(दीर्घ)) >> PAGE_SHIFT; */
	अचिन्हित पूर्णांक page_nr = दीर्घ_nr >> (PAGE_SHIFT - LN2_BPL + 3);
	BUG_ON(page_nr >= b->bm_number_of_pages);
	वापस page_nr;
पूर्ण

अटल अचिन्हित पूर्णांक bm_bit_to_page_idx(काष्ठा drbd_biपंचांगap *b, u64 bitnr)
अणु
	/* page_nr = (bitnr/8) >> PAGE_SHIFT; */
	अचिन्हित पूर्णांक page_nr = bitnr >> (PAGE_SHIFT + 3);
	BUG_ON(page_nr >= b->bm_number_of_pages);
	वापस page_nr;
पूर्ण

अटल अचिन्हित दीर्घ *__bm_map_pidx(काष्ठा drbd_biपंचांगap *b, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा page *page = b->bm_pages[idx];
	वापस (अचिन्हित दीर्घ *) kmap_atomic(page);
पूर्ण

अटल अचिन्हित दीर्घ *bm_map_pidx(काष्ठा drbd_biपंचांगap *b, अचिन्हित पूर्णांक idx)
अणु
	वापस __bm_map_pidx(b, idx);
पूर्ण

अटल व्योम __bm_unmap(अचिन्हित दीर्घ *p_addr)
अणु
	kunmap_atomic(p_addr);
पूर्ण;

अटल व्योम bm_unmap(अचिन्हित दीर्घ *p_addr)
अणु
	वापस __bm_unmap(p_addr);
पूर्ण

/* दीर्घ word offset of _biपंचांगap_ sector */
#घोषणा S2W(s)	((s)<<(BM_EXT_SHIFT-BM_BLOCK_SHIFT-LN2_BPL))
/* word offset from start of biपंचांगap to word number _in_page_
 * modulo दीर्घs per page
#घोषणा MLPP(X) ((X) % (PAGE_SIZE/माप(दीर्घ))
 hm, well, Philipp thinks gcc might not optimize the % पूर्णांकo & (... - 1)
 so करो it explicitly:
 */
#घोषणा MLPP(X) ((X) & ((PAGE_SIZE/माप(दीर्घ))-1))

/* Long words per page */
#घोषणा LWPP (PAGE_SIZE/माप(दीर्घ))

/*
 * actually most functions herein should take a काष्ठा drbd_biपंचांगap*, not a
 * काष्ठा drbd_device*, but क्रम the debug macros I like to have the device around
 * to be able to report device specअगरic.
 */


अटल व्योम bm_मुक्त_pages(काष्ठा page **pages, अचिन्हित दीर्घ number)
अणु
	अचिन्हित दीर्घ i;
	अगर (!pages)
		वापस;

	क्रम (i = 0; i < number; i++) अणु
		अगर (!pages[i]) अणु
			pr_alert("bm_free_pages tried to free a NULL pointer; i=%lu n=%lu\n",
				 i, number);
			जारी;
		पूर्ण
		__मुक्त_page(pages[i]);
		pages[i] = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bm_vk_मुक्त(व्योम *ptr)
अणु
	kvमुक्त(ptr);
पूर्ण

/*
 * "have" and "want" are NUMBER OF PAGES.
 */
अटल काष्ठा page **bm_पुनः_स्मृति_pages(काष्ठा drbd_biपंचांगap *b, अचिन्हित दीर्घ want)
अणु
	काष्ठा page **old_pages = b->bm_pages;
	काष्ठा page **new_pages, *page;
	अचिन्हित पूर्णांक i, bytes;
	अचिन्हित दीर्घ have = b->bm_number_of_pages;

	BUG_ON(have == 0 && old_pages != शून्य);
	BUG_ON(have != 0 && old_pages == शून्य);

	अगर (have == want)
		वापस old_pages;

	/* Trying kदो_स्मृति first, falling back to vदो_स्मृति.
	 * GFP_NOIO, as this is called जबतक drbd IO is "suspended",
	 * and during resize or attach on diskless Primary,
	 * we must not block on IO to ourselves.
	 * Context is receiver thपढ़ो or dmsetup. */
	bytes = माप(काष्ठा page *)*want;
	new_pages = kzalloc(bytes, GFP_NOIO | __GFP_NOWARN);
	अगर (!new_pages) अणु
		new_pages = __vदो_स्मृति(bytes, GFP_NOIO | __GFP_ZERO);
		अगर (!new_pages)
			वापस शून्य;
	पूर्ण

	अगर (want >= have) अणु
		क्रम (i = 0; i < have; i++)
			new_pages[i] = old_pages[i];
		क्रम (; i < want; i++) अणु
			page = alloc_page(GFP_NOIO | __GFP_HIGHMEM);
			अगर (!page) अणु
				bm_मुक्त_pages(new_pages + have, i - have);
				bm_vk_मुक्त(new_pages);
				वापस शून्य;
			पूर्ण
			/* we want to know which page it is
			 * from the endio handlers */
			bm_store_page_idx(page, i);
			new_pages[i] = page;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < want; i++)
			new_pages[i] = old_pages[i];
		/* NOT HERE, we are outside the spinlock!
		bm_मुक्त_pages(old_pages + want, have - want);
		*/
	पूर्ण

	वापस new_pages;
पूर्ण

/*
 * allocates the drbd_biपंचांगap and stores it in device->biपंचांगap.
 */
पूर्णांक drbd_bm_init(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	WARN_ON(b != शून्य);
	b = kzalloc(माप(काष्ठा drbd_biपंचांगap), GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;
	spin_lock_init(&b->bm_lock);
	mutex_init(&b->bm_change);
	init_रुकोqueue_head(&b->bm_io_रुको);

	device->biपंचांगap = b;

	वापस 0;
पूर्ण

sector_t drbd_bm_capacity(काष्ठा drbd_device *device)
अणु
	अगर (!expect(device->biपंचांगap))
		वापस 0;
	वापस device->biपंचांगap->bm_dev_capacity;
पूर्ण

/* called on driver unload. TODO: call when a device is destroyed.
 */
व्योम drbd_bm_cleanup(काष्ठा drbd_device *device)
अणु
	अगर (!expect(device->biपंचांगap))
		वापस;
	bm_मुक्त_pages(device->biपंचांगap->bm_pages, device->biपंचांगap->bm_number_of_pages);
	bm_vk_मुक्त(device->biपंचांगap->bm_pages);
	kमुक्त(device->biपंचांगap);
	device->biपंचांगap = शून्य;
पूर्ण

/*
 * since (b->bm_bits % BITS_PER_LONG) != 0,
 * this masks out the reमुख्यing bits.
 * Returns the number of bits cleared.
 */
#अगर_अघोषित BITS_PER_PAGE
#घोषणा BITS_PER_PAGE		(1UL << (PAGE_SHIFT + 3))
#घोषणा BITS_PER_PAGE_MASK	(BITS_PER_PAGE - 1)
#अन्यथा
# अगर BITS_PER_PAGE != (1UL << (PAGE_SHIFT + 3))
#  error "ambiguous BITS_PER_PAGE"
# endअगर
#पूर्ण_अगर
#घोषणा BITS_PER_LONG_MASK	(BITS_PER_LONG - 1)
अटल पूर्णांक bm_clear_surplus(काष्ठा drbd_biपंचांगap *b)
अणु
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ *p_addr, *bm;
	पूर्णांक पंचांगp;
	पूर्णांक cleared = 0;

	/* number of bits modulo bits per page */
	पंचांगp = (b->bm_bits & BITS_PER_PAGE_MASK);
	/* mask the used bits of the word containing the last bit */
	mask = (1UL << (पंचांगp & BITS_PER_LONG_MASK)) -1;
	/* biपंचांगap is always stored little endian,
	 * on disk and in core memory alike */
	mask = cpu_to_lel(mask);

	p_addr = bm_map_pidx(b, b->bm_number_of_pages - 1);
	bm = p_addr + (पंचांगp/BITS_PER_LONG);
	अगर (mask) अणु
		/* If mask != 0, we are not exactly aligned, so bm now poपूर्णांकs
		 * to the दीर्घ containing the last bit.
		 * If mask == 0, bm alपढ़ोy poपूर्णांकs to the word immediately
		 * after the last (दीर्घ word aligned) bit. */
		cleared = hweight_दीर्घ(*bm & ~mask);
		*bm &= mask;
		bm++;
	पूर्ण

	अगर (BITS_PER_LONG == 32 && ((bm - p_addr) & 1) == 1) अणु
		/* on a 32bit arch, we may need to zero out
		 * a padding दीर्घ to align with a 64bit remote */
		cleared += hweight_दीर्घ(*bm);
		*bm = 0;
	पूर्ण
	bm_unmap(p_addr);
	वापस cleared;
पूर्ण

अटल व्योम bm_set_surplus(काष्ठा drbd_biपंचांगap *b)
अणु
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ *p_addr, *bm;
	पूर्णांक पंचांगp;

	/* number of bits modulo bits per page */
	पंचांगp = (b->bm_bits & BITS_PER_PAGE_MASK);
	/* mask the used bits of the word containing the last bit */
	mask = (1UL << (पंचांगp & BITS_PER_LONG_MASK)) -1;
	/* biपंचांगap is always stored little endian,
	 * on disk and in core memory alike */
	mask = cpu_to_lel(mask);

	p_addr = bm_map_pidx(b, b->bm_number_of_pages - 1);
	bm = p_addr + (पंचांगp/BITS_PER_LONG);
	अगर (mask) अणु
		/* If mask != 0, we are not exactly aligned, so bm now poपूर्णांकs
		 * to the दीर्घ containing the last bit.
		 * If mask == 0, bm alपढ़ोy poपूर्णांकs to the word immediately
		 * after the last (दीर्घ word aligned) bit. */
		*bm |= ~mask;
		bm++;
	पूर्ण

	अगर (BITS_PER_LONG == 32 && ((bm - p_addr) & 1) == 1) अणु
		/* on a 32bit arch, we may need to zero out
		 * a padding दीर्घ to align with a 64bit remote */
		*bm = ~0UL;
	पूर्ण
	bm_unmap(p_addr);
पूर्ण

/* you better not modअगरy the biपंचांगap जबतक this is running,
 * or its results will be stale */
अटल अचिन्हित दीर्घ bm_count_bits(काष्ठा drbd_biपंचांगap *b)
अणु
	अचिन्हित दीर्घ *p_addr;
	अचिन्हित दीर्घ bits = 0;
	अचिन्हित दीर्घ mask = (1UL << (b->bm_bits & BITS_PER_LONG_MASK)) -1;
	पूर्णांक idx, last_word;

	/* all but last page */
	क्रम (idx = 0; idx < b->bm_number_of_pages - 1; idx++) अणु
		p_addr = __bm_map_pidx(b, idx);
		bits += biपंचांगap_weight(p_addr, BITS_PER_PAGE);
		__bm_unmap(p_addr);
		cond_resched();
	पूर्ण
	/* last (or only) page */
	last_word = ((b->bm_bits - 1) & BITS_PER_PAGE_MASK) >> LN2_BPL;
	p_addr = __bm_map_pidx(b, idx);
	bits += biपंचांगap_weight(p_addr, last_word * BITS_PER_LONG);
	p_addr[last_word] &= cpu_to_lel(mask);
	bits += hweight_दीर्घ(p_addr[last_word]);
	/* 32bit arch, may have an unused padding दीर्घ */
	अगर (BITS_PER_LONG == 32 && (last_word & 1) == 0)
		p_addr[last_word+1] = 0;
	__bm_unmap(p_addr);
	वापस bits;
पूर्ण

/* offset and len in दीर्घ words.*/
अटल व्योम bm_स_रखो(काष्ठा drbd_biपंचांगap *b, माप_प्रकार offset, पूर्णांक c, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ *p_addr, *bm;
	अचिन्हित पूर्णांक idx;
	माप_प्रकार करो_now, end;

	end = offset + len;

	अगर (end > b->bm_words) अणु
		pr_alert("bm_memset end > bm_words\n");
		वापस;
	पूर्ण

	जबतक (offset < end) अणु
		करो_now = min_t(माप_प्रकार, ALIGN(offset + 1, LWPP), end) - offset;
		idx = bm_word_to_page_idx(b, offset);
		p_addr = bm_map_pidx(b, idx);
		bm = p_addr + MLPP(offset);
		अगर (bm+करो_now > p_addr + LWPP) अणु
			pr_alert("BUG BUG BUG! p_addr:%p bm:%p do_now:%d\n",
			       p_addr, bm, (पूर्णांक)करो_now);
		पूर्ण अन्यथा
			स_रखो(bm, c, करो_now * माप(दीर्घ));
		bm_unmap(p_addr);
		bm_set_page_need_ग_लिखोout(b->bm_pages[idx]);
		offset += करो_now;
	पूर्ण
पूर्ण

/* For the layout, see comment above drbd_md_set_sector_offsets(). */
अटल u64 drbd_md_on_disk_bits(काष्ठा drbd_backing_dev *ldev)
अणु
	u64 biपंचांगap_sectors;
	अगर (ldev->md.al_offset == 8)
		biपंचांगap_sectors = ldev->md.md_size_sect - ldev->md.bm_offset;
	अन्यथा
		biपंचांगap_sectors = ldev->md.al_offset - ldev->md.bm_offset;
	वापस biपंचांगap_sectors << (9 + 3);
पूर्ण

/*
 * make sure the biपंचांगap has enough room क्रम the attached storage,
 * अगर necessary, resize.
 * called whenever we may have changed the device size.
 * वापसs -ENOMEM अगर we could not allocate enough memory, 0 on success.
 * In हाल this is actually a resize, we copy the old biपंचांगap पूर्णांकo the new one.
 * Otherwise, the biपंचांगap is initialized to all bits set.
 */
पूर्णांक drbd_bm_resize(काष्ठा drbd_device *device, sector_t capacity, पूर्णांक set_new_bits)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित दीर्घ bits, words, owords, obits;
	अचिन्हित दीर्घ want, have, onpages; /* number of pages */
	काष्ठा page **npages, **opages = शून्य;
	पूर्णांक err = 0;
	bool growing;

	अगर (!expect(b))
		वापस -ENOMEM;

	drbd_bm_lock(device, "resize", BM_LOCKED_MASK);

	drbd_info(device, "drbd_bm_resize called with capacity == %llu\n",
			(अचिन्हित दीर्घ दीर्घ)capacity);

	अगर (capacity == b->bm_dev_capacity)
		जाओ out;

	अगर (capacity == 0) अणु
		spin_lock_irq(&b->bm_lock);
		opages = b->bm_pages;
		onpages = b->bm_number_of_pages;
		owords = b->bm_words;
		b->bm_pages = शून्य;
		b->bm_number_of_pages =
		b->bm_set   =
		b->bm_bits  =
		b->bm_words =
		b->bm_dev_capacity = 0;
		spin_unlock_irq(&b->bm_lock);
		bm_मुक्त_pages(opages, onpages);
		bm_vk_मुक्त(opages);
		जाओ out;
	पूर्ण
	bits  = BM_SECT_TO_BIT(ALIGN(capacity, BM_SECT_PER_BIT));

	/* अगर we would use
	   words = ALIGN(bits,BITS_PER_LONG) >> LN2_BPL;
	   a 32bit host could present the wrong number of words
	   to a 64bit host.
	*/
	words = ALIGN(bits, 64) >> LN2_BPL;

	अगर (get_ldev(device)) अणु
		u64 bits_on_disk = drbd_md_on_disk_bits(device->ldev);
		put_ldev(device);
		अगर (bits > bits_on_disk) अणु
			drbd_info(device, "bits = %lu\n", bits);
			drbd_info(device, "bits_on_disk = %llu\n", bits_on_disk);
			err = -ENOSPC;
			जाओ out;
		पूर्ण
	पूर्ण

	want = ALIGN(words*माप(दीर्घ), PAGE_SIZE) >> PAGE_SHIFT;
	have = b->bm_number_of_pages;
	अगर (want == have) अणु
		D_ASSERT(device, b->bm_pages != शून्य);
		npages = b->bm_pages;
	पूर्ण अन्यथा अणु
		अगर (drbd_insert_fault(device, DRBD_FAULT_BM_ALLOC))
			npages = शून्य;
		अन्यथा
			npages = bm_पुनः_स्मृति_pages(b, want);
	पूर्ण

	अगर (!npages) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	spin_lock_irq(&b->bm_lock);
	opages = b->bm_pages;
	owords = b->bm_words;
	obits  = b->bm_bits;

	growing = bits > obits;
	अगर (opages && growing && set_new_bits)
		bm_set_surplus(b);

	b->bm_pages = npages;
	b->bm_number_of_pages = want;
	b->bm_bits  = bits;
	b->bm_words = words;
	b->bm_dev_capacity = capacity;

	अगर (growing) अणु
		अगर (set_new_bits) अणु
			bm_स_रखो(b, owords, 0xff, words-owords);
			b->bm_set += bits - obits;
		पूर्ण अन्यथा
			bm_स_रखो(b, owords, 0x00, words-owords);

	पूर्ण

	अगर (want < have) अणु
		/* implicit: (opages != शून्य) && (opages != npages) */
		bm_मुक्त_pages(opages + want, have - want);
	पूर्ण

	(व्योम)bm_clear_surplus(b);

	spin_unlock_irq(&b->bm_lock);
	अगर (opages != npages)
		bm_vk_मुक्त(opages);
	अगर (!growing)
		b->bm_set = bm_count_bits(b);
	drbd_info(device, "resync bitmap: bits=%lu words=%lu pages=%lu\n", bits, words, want);

 out:
	drbd_bm_unlock(device);
	वापस err;
पूर्ण

/* inherently racy:
 * अगर not रक्षित by other means, वापस value may be out of date when
 * leaving this function...
 * we still need to lock it, since it is important that this वापसs
 * bm_set == 0 precisely.
 *
 * maybe bm_set should be atomic_t ?
 */
अचिन्हित दीर्घ _drbd_bm_total_weight(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित दीर्घ s;
	अचिन्हित दीर्घ flags;

	अगर (!expect(b))
		वापस 0;
	अगर (!expect(b->bm_pages))
		वापस 0;

	spin_lock_irqsave(&b->bm_lock, flags);
	s = b->bm_set;
	spin_unlock_irqrestore(&b->bm_lock, flags);

	वापस s;
पूर्ण

अचिन्हित दीर्घ drbd_bm_total_weight(काष्ठा drbd_device *device)
अणु
	अचिन्हित दीर्घ s;
	/* अगर I करोn't have a disk, I don't know about out-of-sync status */
	अगर (!get_ldev_अगर_state(device, D_NEGOTIATING))
		वापस 0;
	s = _drbd_bm_total_weight(device);
	put_ldev(device);
	वापस s;
पूर्ण

माप_प्रकार drbd_bm_words(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अगर (!expect(b))
		वापस 0;
	अगर (!expect(b->bm_pages))
		वापस 0;

	वापस b->bm_words;
पूर्ण

अचिन्हित दीर्घ drbd_bm_bits(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अगर (!expect(b))
		वापस 0;

	वापस b->bm_bits;
पूर्ण

/* merge number words from buffer पूर्णांकo the biपंचांगap starting at offset.
 * buffer[i] is expected to be little endian अचिन्हित दीर्घ.
 * biपंचांगap must be locked by drbd_bm_lock.
 * currently only used from receive_biपंचांगap.
 */
व्योम drbd_bm_merge_lel(काष्ठा drbd_device *device, माप_प्रकार offset, माप_प्रकार number,
			अचिन्हित दीर्घ *buffer)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित दीर्घ *p_addr, *bm;
	अचिन्हित दीर्घ word, bits;
	अचिन्हित पूर्णांक idx;
	माप_प्रकार end, करो_now;

	end = offset + number;

	अगर (!expect(b))
		वापस;
	अगर (!expect(b->bm_pages))
		वापस;
	अगर (number == 0)
		वापस;
	WARN_ON(offset >= b->bm_words);
	WARN_ON(end    >  b->bm_words);

	spin_lock_irq(&b->bm_lock);
	जबतक (offset < end) अणु
		करो_now = min_t(माप_प्रकार, ALIGN(offset+1, LWPP), end) - offset;
		idx = bm_word_to_page_idx(b, offset);
		p_addr = bm_map_pidx(b, idx);
		bm = p_addr + MLPP(offset);
		offset += करो_now;
		जबतक (करो_now--) अणु
			bits = hweight_दीर्घ(*bm);
			word = *bm | *buffer++;
			*bm++ = word;
			b->bm_set += hweight_दीर्घ(word) - bits;
		पूर्ण
		bm_unmap(p_addr);
		bm_set_page_need_ग_लिखोout(b->bm_pages[idx]);
	पूर्ण
	/* with 32bit <-> 64bit cross-platक्रमm connect
	 * this is only correct क्रम current usage,
	 * where we _know_ that we are 64 bit aligned,
	 * and know that this function is used in this way, too...
	 */
	अगर (end == b->bm_words)
		b->bm_set -= bm_clear_surplus(b);
	spin_unlock_irq(&b->bm_lock);
पूर्ण

/* copy number words from the biपंचांगap starting at offset पूर्णांकo the buffer.
 * buffer[i] will be little endian अचिन्हित दीर्घ.
 */
व्योम drbd_bm_get_lel(काष्ठा drbd_device *device, माप_प्रकार offset, माप_प्रकार number,
		     अचिन्हित दीर्घ *buffer)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित दीर्घ *p_addr, *bm;
	माप_प्रकार end, करो_now;

	end = offset + number;

	अगर (!expect(b))
		वापस;
	अगर (!expect(b->bm_pages))
		वापस;

	spin_lock_irq(&b->bm_lock);
	अगर ((offset >= b->bm_words) ||
	    (end    >  b->bm_words) ||
	    (number <= 0))
		drbd_err(device, "offset=%lu number=%lu bm_words=%lu\n",
			(अचिन्हित दीर्घ)	offset,
			(अचिन्हित दीर्घ)	number,
			(अचिन्हित दीर्घ) b->bm_words);
	अन्यथा अणु
		जबतक (offset < end) अणु
			करो_now = min_t(माप_प्रकार, ALIGN(offset+1, LWPP), end) - offset;
			p_addr = bm_map_pidx(b, bm_word_to_page_idx(b, offset));
			bm = p_addr + MLPP(offset);
			offset += करो_now;
			जबतक (करो_now--)
				*buffer++ = *bm++;
			bm_unmap(p_addr);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&b->bm_lock);
पूर्ण

/* set all bits in the biपंचांगap */
व्योम drbd_bm_set_all(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अगर (!expect(b))
		वापस;
	अगर (!expect(b->bm_pages))
		वापस;

	spin_lock_irq(&b->bm_lock);
	bm_स_रखो(b, 0, 0xff, b->bm_words);
	(व्योम)bm_clear_surplus(b);
	b->bm_set = b->bm_bits;
	spin_unlock_irq(&b->bm_lock);
पूर्ण

/* clear all bits in the biपंचांगap */
व्योम drbd_bm_clear_all(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अगर (!expect(b))
		वापस;
	अगर (!expect(b->bm_pages))
		वापस;

	spin_lock_irq(&b->bm_lock);
	bm_स_रखो(b, 0, 0, b->bm_words);
	b->bm_set = 0;
	spin_unlock_irq(&b->bm_lock);
पूर्ण

अटल व्योम drbd_bm_aio_ctx_destroy(काष्ठा kref *kref)
अणु
	काष्ठा drbd_bm_aio_ctx *ctx = container_of(kref, काष्ठा drbd_bm_aio_ctx, kref);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->device->resource->req_lock, flags);
	list_del(&ctx->list);
	spin_unlock_irqrestore(&ctx->device->resource->req_lock, flags);
	put_ldev(ctx->device);
	kमुक्त(ctx);
पूर्ण

/* bv_page may be a copy, or may be the original */
अटल व्योम drbd_bm_endio(काष्ठा bio *bio)
अणु
	काष्ठा drbd_bm_aio_ctx *ctx = bio->bi_निजी;
	काष्ठा drbd_device *device = ctx->device;
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित पूर्णांक idx = bm_page_to_idx(bio_first_page_all(bio));

	अगर ((ctx->flags & BM_AIO_COPY_PAGES) == 0 &&
	    !bm_test_page_unchanged(b->bm_pages[idx]))
		drbd_warn(device, "bitmap page idx %u changed during IO!\n", idx);

	अगर (bio->bi_status) अणु
		/* ctx error will hold the completed-last non-zero error code,
		 * in हाल error codes dअगरfer. */
		ctx->error = blk_status_to_त्रुटि_सं(bio->bi_status);
		bm_set_page_io_err(b->bm_pages[idx]);
		/* Not identical to on disk version of it.
		 * Is BM_PAGE_IO_ERROR enough? */
		अगर (__ratelimit(&drbd_ratelimit_state))
			drbd_err(device, "IO ERROR %d on bitmap page idx %u\n",
					bio->bi_status, idx);
	पूर्ण अन्यथा अणु
		bm_clear_page_io_err(b->bm_pages[idx]);
		dynamic_drbd_dbg(device, "bitmap page idx %u completed\n", idx);
	पूर्ण

	bm_page_unlock_io(device, idx);

	अगर (ctx->flags & BM_AIO_COPY_PAGES)
		mempool_मुक्त(bio->bi_io_vec[0].bv_page, &drbd_md_io_page_pool);

	bio_put(bio);

	अगर (atomic_dec_and_test(&ctx->in_flight)) अणु
		ctx->करोne = 1;
		wake_up(&device->misc_रुको);
		kref_put(&ctx->kref, &drbd_bm_aio_ctx_destroy);
	पूर्ण
पूर्ण

अटल व्योम bm_page_io_async(काष्ठा drbd_bm_aio_ctx *ctx, पूर्णांक page_nr) __must_hold(local)
अणु
	काष्ठा bio *bio = bio_alloc_bioset(GFP_NOIO, 1, &drbd_md_io_bio_set);
	काष्ठा drbd_device *device = ctx->device;
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	काष्ठा page *page;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक op = (ctx->flags & BM_AIO_READ) ? REQ_OP_READ : REQ_OP_WRITE;

	sector_t on_disk_sector =
		device->ldev->md.md_offset + device->ldev->md.bm_offset;
	on_disk_sector += ((sector_t)page_nr) << (PAGE_SHIFT-9);

	/* this might happen with very small
	 * flexible बाह्यal meta data device,
	 * or with PAGE_SIZE > 4k */
	len = min_t(अचिन्हित पूर्णांक, PAGE_SIZE,
		(drbd_md_last_sector(device->ldev) - on_disk_sector + 1)<<9);

	/* serialize IO on this page */
	bm_page_lock_io(device, page_nr);
	/* beक्रमe स_नकल and submit,
	 * so it can be redirtied any समय */
	bm_set_page_unchanged(b->bm_pages[page_nr]);

	अगर (ctx->flags & BM_AIO_COPY_PAGES) अणु
		page = mempool_alloc(&drbd_md_io_page_pool,
				GFP_NOIO | __GFP_HIGHMEM);
		copy_highpage(page, b->bm_pages[page_nr]);
		bm_store_page_idx(page, page_nr);
	पूर्ण अन्यथा
		page = b->bm_pages[page_nr];
	bio_set_dev(bio, device->ldev->md_bdev);
	bio->bi_iter.bi_sector = on_disk_sector;
	/* bio_add_page of a single page to an empty bio will always succeed,
	 * according to api.  Do we want to निश्चित that? */
	bio_add_page(bio, page, len, 0);
	bio->bi_निजी = ctx;
	bio->bi_end_io = drbd_bm_endio;
	bio_set_op_attrs(bio, op, 0);

	अगर (drbd_insert_fault(device, (op == REQ_OP_WRITE) ? DRBD_FAULT_MD_WR : DRBD_FAULT_MD_RD)) अणु
		bio_io_error(bio);
	पूर्ण अन्यथा अणु
		submit_bio(bio);
		/* this should not count as user activity and cause the
		 * resync to throttle -- see drbd_rs_should_slow_करोwn(). */
		atomic_add(len >> 9, &device->rs_sect_ev);
	पूर्ण
पूर्ण

/*
 * bm_rw: पढ़ो/ग_लिखो the whole biपंचांगap from/to its on disk location.
 */
अटल पूर्णांक bm_rw(काष्ठा drbd_device *device, स्थिर अचिन्हित पूर्णांक flags, अचिन्हित lazy_ग_लिखोout_upper_idx) __must_hold(local)
अणु
	काष्ठा drbd_bm_aio_ctx *ctx;
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित पूर्णांक num_pages, i, count = 0;
	अचिन्हित दीर्घ now;
	अक्षर ppb[10];
	पूर्णांक err = 0;

	/*
	 * We are रक्षित against biपंचांगap disappearing/resizing by holding an
	 * ldev reference (caller must have called get_ldev()).
	 * For पढ़ो/ग_लिखो, we are रक्षित against changes to the biपंचांगap by
	 * the biपंचांगap lock (see drbd_biपंचांगap_io).
	 * For lazy ग_लिखोout, we करोn't care क्रम ongoing changes to the biपंचांगap,
	 * as we submit copies of pages anyways.
	 */

	ctx = kदो_स्मृति(माप(काष्ठा drbd_bm_aio_ctx), GFP_NOIO);
	अगर (!ctx)
		वापस -ENOMEM;

	*ctx = (काष्ठा drbd_bm_aio_ctx) अणु
		.device = device,
		.start_jअगर = jअगरfies,
		.in_flight = ATOMIC_INIT(1),
		.करोne = 0,
		.flags = flags,
		.error = 0,
		.kref = KREF_INIT(2),
	पूर्ण;

	अगर (!get_ldev_अगर_state(device, D_ATTACHING)) अणु  /* put is in drbd_bm_aio_ctx_destroy() */
		drbd_err(device, "ASSERT FAILED: get_ldev_if_state() == 1 in bm_rw()\n");
		kमुक्त(ctx);
		वापस -ENODEV;
	पूर्ण
	/* Here D_ATTACHING is sufficient since drbd_bm_पढ़ो() is called only from
	   drbd_adm_attach(), after device->ldev was asचिन्हित. */

	अगर (0 == (ctx->flags & ~BM_AIO_READ))
		WARN_ON(!(BM_LOCKED_MASK & b->bm_flags));

	spin_lock_irq(&device->resource->req_lock);
	list_add_tail(&ctx->list, &device->pending_biपंचांगap_io);
	spin_unlock_irq(&device->resource->req_lock);

	num_pages = b->bm_number_of_pages;

	now = jअगरfies;

	/* let the layers below us try to merge these bios... */

	अगर (flags & BM_AIO_READ) अणु
		क्रम (i = 0; i < num_pages; i++) अणु
			atomic_inc(&ctx->in_flight);
			bm_page_io_async(ctx, i);
			++count;
			cond_resched();
		पूर्ण
	पूर्ण अन्यथा अगर (flags & BM_AIO_WRITE_HINTED) अणु
		/* ASSERT: BM_AIO_WRITE_ALL_PAGES is not set. */
		अचिन्हित पूर्णांक hपूर्णांक;
		क्रम (hपूर्णांक = 0; hपूर्णांक < b->n_biपंचांगap_hपूर्णांकs; hपूर्णांक++) अणु
			i = b->al_biपंचांगap_hपूर्णांकs[hपूर्णांक];
			अगर (i >= num_pages) /* == -1U: no hपूर्णांक here. */
				जारी;
			/* Several AL-extents may poपूर्णांक to the same page. */
			अगर (!test_and_clear_bit(BM_PAGE_HINT_WRITEOUT,
			    &page_निजी(b->bm_pages[i])))
				जारी;
			/* Has it even changed? */
			अगर (bm_test_page_unchanged(b->bm_pages[i]))
				जारी;
			atomic_inc(&ctx->in_flight);
			bm_page_io_async(ctx, i);
			++count;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < num_pages; i++) अणु
			/* ignore completely unchanged pages */
			अगर (lazy_ग_लिखोout_upper_idx && i == lazy_ग_लिखोout_upper_idx)
				अवरोध;
			अगर (!(flags & BM_AIO_WRITE_ALL_PAGES) &&
			    bm_test_page_unchanged(b->bm_pages[i])) अणु
				dynamic_drbd_dbg(device, "skipped bm write for idx %u\n", i);
				जारी;
			पूर्ण
			/* during lazy ग_लिखोout,
			 * ignore those pages not marked क्रम lazy ग_लिखोout. */
			अगर (lazy_ग_लिखोout_upper_idx &&
			    !bm_test_page_lazy_ग_लिखोout(b->bm_pages[i])) अणु
				dynamic_drbd_dbg(device, "skipped bm lazy write for idx %u\n", i);
				जारी;
			पूर्ण
			atomic_inc(&ctx->in_flight);
			bm_page_io_async(ctx, i);
			++count;
			cond_resched();
		पूर्ण
	पूर्ण

	/*
	 * We initialize ctx->in_flight to one to make sure drbd_bm_endio
	 * will not set ctx->करोne early, and decrement / test it here.  If there
	 * are still some bios in flight, we need to रुको क्रम them here.
	 * If all IO is करोne alपढ़ोy (or nothing had been submitted), there is
	 * no need to रुको.  Still, we need to put the kref associated with the
	 * "in_flight reached zero, all done" event.
	 */
	अगर (!atomic_dec_and_test(&ctx->in_flight))
		रुको_until_करोne_or_क्रमce_detached(device, device->ldev, &ctx->करोne);
	अन्यथा
		kref_put(&ctx->kref, &drbd_bm_aio_ctx_destroy);

	/* summary क्रम global biपंचांगap IO */
	अगर (flags == 0) अणु
		अचिन्हित पूर्णांक ms = jअगरfies_to_msecs(jअगरfies - now);
		अगर (ms > 5) अणु
			drbd_info(device, "bitmap %s of %u pages took %u ms\n",
				 (flags & BM_AIO_READ) ? "READ" : "WRITE",
				 count, ms);
		पूर्ण
	पूर्ण

	अगर (ctx->error) अणु
		drbd_alert(device, "we had at least one MD IO ERROR during bitmap IO\n");
		drbd_chk_io_error(device, 1, DRBD_META_IO_ERROR);
		err = -EIO; /* ctx->error ? */
	पूर्ण

	अगर (atomic_पढ़ो(&ctx->in_flight))
		err = -EIO; /* Disk समयout/क्रमce-detach during IO... */

	now = jअगरfies;
	अगर (flags & BM_AIO_READ) अणु
		b->bm_set = bm_count_bits(b);
		drbd_info(device, "recounting of set bits took additional %lu jiffies\n",
		     jअगरfies - now);
	पूर्ण
	now = b->bm_set;

	अगर ((flags & ~BM_AIO_READ) == 0)
		drbd_info(device, "%s (%lu bits) marked out-of-sync by on disk bit-map.\n",
		     ppsize(ppb, now << (BM_BLOCK_SHIFT-10)), now);

	kref_put(&ctx->kref, &drbd_bm_aio_ctx_destroy);
	वापस err;
पूर्ण

/**
 * drbd_bm_पढ़ो() - Read the whole biपंचांगap from its on disk location.
 * @device:	DRBD device.
 */
पूर्णांक drbd_bm_पढ़ो(काष्ठा drbd_device *device) __must_hold(local)
अणु
	वापस bm_rw(device, BM_AIO_READ, 0);
पूर्ण

/**
 * drbd_bm_ग_लिखो() - Write the whole biपंचांगap to its on disk location.
 * @device:	DRBD device.
 *
 * Will only ग_लिखो pages that have changed since last IO.
 */
पूर्णांक drbd_bm_ग_लिखो(काष्ठा drbd_device *device) __must_hold(local)
अणु
	वापस bm_rw(device, 0, 0);
पूर्ण

/**
 * drbd_bm_ग_लिखो_all() - Write the whole biपंचांगap to its on disk location.
 * @device:	DRBD device.
 *
 * Will ग_लिखो all pages.
 */
पूर्णांक drbd_bm_ग_लिखो_all(काष्ठा drbd_device *device) __must_hold(local)
अणु
	वापस bm_rw(device, BM_AIO_WRITE_ALL_PAGES, 0);
पूर्ण

/**
 * drbd_bm_ग_लिखो_lazy() - Write biपंचांगap pages 0 to @upper_idx-1, अगर they have changed.
 * @device:	DRBD device.
 * @upper_idx:	0: ग_लिखो all changed pages; +ve: page index to stop scanning क्रम changed pages
 */
पूर्णांक drbd_bm_ग_लिखो_lazy(काष्ठा drbd_device *device, अचिन्हित upper_idx) __must_hold(local)
अणु
	वापस bm_rw(device, BM_AIO_COPY_PAGES, upper_idx);
पूर्ण

/**
 * drbd_bm_ग_लिखो_copy_pages() - Write the whole biपंचांगap to its on disk location.
 * @device:	DRBD device.
 *
 * Will only ग_लिखो pages that have changed since last IO.
 * In contrast to drbd_bm_ग_लिखो(), this will copy the biपंचांगap pages
 * to temporary ग_लिखोout pages. It is पूर्णांकended to trigger a full ग_लिखो-out
 * जबतक still allowing the biपंचांगap to change, क्रम example अगर a resync or online
 * verअगरy is पातed due to a failed peer disk, जबतक local IO जारीs, or
 * pending resync acks are still being processed.
 */
पूर्णांक drbd_bm_ग_लिखो_copy_pages(काष्ठा drbd_device *device) __must_hold(local)
अणु
	वापस bm_rw(device, BM_AIO_COPY_PAGES, 0);
पूर्ण

/**
 * drbd_bm_ग_लिखो_hपूर्णांकed() - Write biपंचांगap pages with "hint" marks, अगर they have changed.
 * @device:	DRBD device.
 */
पूर्णांक drbd_bm_ग_लिखो_hपूर्णांकed(काष्ठा drbd_device *device) __must_hold(local)
अणु
	वापस bm_rw(device, BM_AIO_WRITE_HINTED | BM_AIO_COPY_PAGES, 0);
पूर्ण

/* NOTE
 * find_first_bit वापसs पूर्णांक, we वापस अचिन्हित दीर्घ.
 * For this to work on 32bit arch with bitnumbers > (1<<32),
 * we'd need to वापस u64, and get a whole lot of other places
 * fixed where we still use अचिन्हित दीर्घ.
 *
 * this वापसs a bit number, NOT a sector!
 */
अटल अचिन्हित दीर्घ __bm_find_next(काष्ठा drbd_device *device, अचिन्हित दीर्घ bm_fo,
	स्थिर पूर्णांक find_zero_bit)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित दीर्घ *p_addr;
	अचिन्हित दीर्घ bit_offset;
	अचिन्हित i;


	अगर (bm_fo > b->bm_bits) अणु
		drbd_err(device, "bm_fo=%lu bm_bits=%lu\n", bm_fo, b->bm_bits);
		bm_fo = DRBD_END_OF_BITMAP;
	पूर्ण अन्यथा अणु
		जबतक (bm_fo < b->bm_bits) अणु
			/* bit offset of the first bit in the page */
			bit_offset = bm_fo & ~BITS_PER_PAGE_MASK;
			p_addr = __bm_map_pidx(b, bm_bit_to_page_idx(b, bm_fo));

			अगर (find_zero_bit)
				i = find_next_zero_bit_le(p_addr,
						PAGE_SIZE*8, bm_fo & BITS_PER_PAGE_MASK);
			अन्यथा
				i = find_next_bit_le(p_addr,
						PAGE_SIZE*8, bm_fo & BITS_PER_PAGE_MASK);

			__bm_unmap(p_addr);
			अगर (i < PAGE_SIZE*8) अणु
				bm_fo = bit_offset + i;
				अगर (bm_fo >= b->bm_bits)
					अवरोध;
				जाओ found;
			पूर्ण
			bm_fo = bit_offset + PAGE_SIZE*8;
		पूर्ण
		bm_fo = DRBD_END_OF_BITMAP;
	पूर्ण
 found:
	वापस bm_fo;
पूर्ण

अटल अचिन्हित दीर्घ bm_find_next(काष्ठा drbd_device *device,
	अचिन्हित दीर्घ bm_fo, स्थिर पूर्णांक find_zero_bit)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित दीर्घ i = DRBD_END_OF_BITMAP;

	अगर (!expect(b))
		वापस i;
	अगर (!expect(b->bm_pages))
		वापस i;

	spin_lock_irq(&b->bm_lock);
	अगर (BM_DONT_TEST & b->bm_flags)
		bm_prपूर्णांक_lock_info(device);

	i = __bm_find_next(device, bm_fo, find_zero_bit);

	spin_unlock_irq(&b->bm_lock);
	वापस i;
पूर्ण

अचिन्हित दीर्घ drbd_bm_find_next(काष्ठा drbd_device *device, अचिन्हित दीर्घ bm_fo)
अणु
	वापस bm_find_next(device, bm_fo, 0);
पूर्ण

#अगर 0
/* not yet needed क्रम anything. */
अचिन्हित दीर्घ drbd_bm_find_next_zero(काष्ठा drbd_device *device, अचिन्हित दीर्घ bm_fo)
अणु
	वापस bm_find_next(device, bm_fo, 1);
पूर्ण
#पूर्ण_अगर

/* करोes not spin_lock_irqsave.
 * you must take drbd_bm_lock() first */
अचिन्हित दीर्घ _drbd_bm_find_next(काष्ठा drbd_device *device, अचिन्हित दीर्घ bm_fo)
अणु
	/* WARN_ON(!(BM_DONT_SET & device->b->bm_flags)); */
	वापस __bm_find_next(device, bm_fo, 0);
पूर्ण

अचिन्हित दीर्घ _drbd_bm_find_next_zero(काष्ठा drbd_device *device, अचिन्हित दीर्घ bm_fo)
अणु
	/* WARN_ON(!(BM_DONT_SET & device->b->bm_flags)); */
	वापस __bm_find_next(device, bm_fo, 1);
पूर्ण

/* वापसs number of bits actually changed.
 * क्रम val != 0, we change 0 -> 1, वापस code positive
 * क्रम val == 0, we change 1 -> 0, वापस code negative
 * wants bitnr, not sector.
 * expected to be called क्रम only a few bits (e - s about BITS_PER_LONG).
 * Must hold biपंचांगap lock alपढ़ोy. */
अटल पूर्णांक __bm_change_bits_to(काष्ठा drbd_device *device, स्थिर अचिन्हित दीर्घ s,
	अचिन्हित दीर्घ e, पूर्णांक val)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित दीर्घ *p_addr = शून्य;
	अचिन्हित दीर्घ bitnr;
	अचिन्हित पूर्णांक last_page_nr = -1U;
	पूर्णांक c = 0;
	पूर्णांक changed_total = 0;

	अगर (e >= b->bm_bits) अणु
		drbd_err(device, "ASSERT FAILED: bit_s=%lu bit_e=%lu bm_bits=%lu\n",
				s, e, b->bm_bits);
		e = b->bm_bits ? b->bm_bits -1 : 0;
	पूर्ण
	क्रम (bitnr = s; bitnr <= e; bitnr++) अणु
		अचिन्हित पूर्णांक page_nr = bm_bit_to_page_idx(b, bitnr);
		अगर (page_nr != last_page_nr) अणु
			अगर (p_addr)
				__bm_unmap(p_addr);
			अगर (c < 0)
				bm_set_page_lazy_ग_लिखोout(b->bm_pages[last_page_nr]);
			अन्यथा अगर (c > 0)
				bm_set_page_need_ग_लिखोout(b->bm_pages[last_page_nr]);
			changed_total += c;
			c = 0;
			p_addr = __bm_map_pidx(b, page_nr);
			last_page_nr = page_nr;
		पूर्ण
		अगर (val)
			c += (0 == __test_and_set_bit_le(bitnr & BITS_PER_PAGE_MASK, p_addr));
		अन्यथा
			c -= (0 != __test_and_clear_bit_le(bitnr & BITS_PER_PAGE_MASK, p_addr));
	पूर्ण
	अगर (p_addr)
		__bm_unmap(p_addr);
	अगर (c < 0)
		bm_set_page_lazy_ग_लिखोout(b->bm_pages[last_page_nr]);
	अन्यथा अगर (c > 0)
		bm_set_page_need_ग_लिखोout(b->bm_pages[last_page_nr]);
	changed_total += c;
	b->bm_set += changed_total;
	वापस changed_total;
पूर्ण

/* वापसs number of bits actually changed.
 * क्रम val != 0, we change 0 -> 1, वापस code positive
 * क्रम val == 0, we change 1 -> 0, वापस code negative
 * wants bitnr, not sector */
अटल पूर्णांक bm_change_bits_to(काष्ठा drbd_device *device, स्थिर अचिन्हित दीर्घ s,
	स्थिर अचिन्हित दीर्घ e, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	पूर्णांक c = 0;

	अगर (!expect(b))
		वापस 1;
	अगर (!expect(b->bm_pages))
		वापस 0;

	spin_lock_irqsave(&b->bm_lock, flags);
	अगर ((val ? BM_DONT_SET : BM_DONT_CLEAR) & b->bm_flags)
		bm_prपूर्णांक_lock_info(device);

	c = __bm_change_bits_to(device, s, e, val);

	spin_unlock_irqrestore(&b->bm_lock, flags);
	वापस c;
पूर्ण

/* वापसs number of bits changed 0 -> 1 */
पूर्णांक drbd_bm_set_bits(काष्ठा drbd_device *device, स्थिर अचिन्हित दीर्घ s, स्थिर अचिन्हित दीर्घ e)
अणु
	वापस bm_change_bits_to(device, s, e, 1);
पूर्ण

/* वापसs number of bits changed 1 -> 0 */
पूर्णांक drbd_bm_clear_bits(काष्ठा drbd_device *device, स्थिर अचिन्हित दीर्घ s, स्थिर अचिन्हित दीर्घ e)
अणु
	वापस -bm_change_bits_to(device, s, e, 0);
पूर्ण

/* sets all bits in full words,
 * from first_word up to, but not including, last_word */
अटल अंतरभूत व्योम bm_set_full_words_within_one_page(काष्ठा drbd_biपंचांगap *b,
		पूर्णांक page_nr, पूर्णांक first_word, पूर्णांक last_word)
अणु
	पूर्णांक i;
	पूर्णांक bits;
	पूर्णांक changed = 0;
	अचिन्हित दीर्घ *paddr = kmap_atomic(b->bm_pages[page_nr]);

	/* I think it is more cache line मित्रly to hweight_दीर्घ then set to ~0UL,
	 * than to first biपंचांगap_weight() all words, then biपंचांगap_fill() all words */
	क्रम (i = first_word; i < last_word; i++) अणु
		bits = hweight_दीर्घ(paddr[i]);
		paddr[i] = ~0UL;
		changed += BITS_PER_LONG - bits;
	पूर्ण
	kunmap_atomic(paddr);
	अगर (changed) अणु
		/* We only need lazy ग_लिखोout, the inक्रमmation is still in the
		 * remote biपंचांगap as well, and is reस्थिरructed during the next
		 * biपंचांगap exchange, अगर lost locally due to a crash. */
		bm_set_page_lazy_ग_लिखोout(b->bm_pages[page_nr]);
		b->bm_set += changed;
	पूर्ण
पूर्ण

/* Same thing as drbd_bm_set_bits,
 * but more efficient क्रम a large bit range.
 * You must first drbd_bm_lock().
 * Can be called to set the whole biपंचांगap in one go.
 * Sets bits from s to e _inclusive_. */
व्योम _drbd_bm_set_bits(काष्ठा drbd_device *device, स्थिर अचिन्हित दीर्घ s, स्थिर अचिन्हित दीर्घ e)
अणु
	/* First set_bit from the first bit (s)
	 * up to the next दीर्घ boundary (sl),
	 * then assign full words up to the last दीर्घ boundary (el),
	 * then set_bit up to and including the last bit (e).
	 *
	 * Do not use स_रखो, because we must account क्रम changes,
	 * so we need to loop over the words with hweight() anyways.
	 */
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित दीर्घ sl = ALIGN(s,BITS_PER_LONG);
	अचिन्हित दीर्घ el = (e+1) & ~((अचिन्हित दीर्घ)BITS_PER_LONG-1);
	पूर्णांक first_page;
	पूर्णांक last_page;
	पूर्णांक page_nr;
	पूर्णांक first_word;
	पूर्णांक last_word;

	अगर (e - s <= 3*BITS_PER_LONG) अणु
		/* करोn't bother; el and sl may even be wrong. */
		spin_lock_irq(&b->bm_lock);
		__bm_change_bits_to(device, s, e, 1);
		spin_unlock_irq(&b->bm_lock);
		वापस;
	पूर्ण

	/* dअगरference is large enough that we can trust sl and el */

	spin_lock_irq(&b->bm_lock);

	/* bits filling the current दीर्घ */
	अगर (sl)
		__bm_change_bits_to(device, s, sl-1, 1);

	first_page = sl >> (3 + PAGE_SHIFT);
	last_page = el >> (3 + PAGE_SHIFT);

	/* MLPP: modulo दीर्घs per page */
	/* LWPP: दीर्घ words per page */
	first_word = MLPP(sl >> LN2_BPL);
	last_word = LWPP;

	/* first and full pages, unless first page == last page */
	क्रम (page_nr = first_page; page_nr < last_page; page_nr++) अणु
		bm_set_full_words_within_one_page(device->biपंचांगap, page_nr, first_word, last_word);
		spin_unlock_irq(&b->bm_lock);
		cond_resched();
		first_word = 0;
		spin_lock_irq(&b->bm_lock);
	पूर्ण
	/* last page (respectively only page, क्रम first page == last page) */
	last_word = MLPP(el >> LN2_BPL);

	/* consider biपंचांगap->bm_bits = 32768, biपंचांगap->bm_number_of_pages = 1. (or multiples).
	 * ==> e = 32767, el = 32768, last_page = 2,
	 * and now last_word = 0.
	 * We करो not want to touch last_page in this हाल,
	 * as we did not allocate it, it is not present in biपंचांगap->bm_pages.
	 */
	अगर (last_word)
		bm_set_full_words_within_one_page(device->biपंचांगap, last_page, first_word, last_word);

	/* possibly trailing bits.
	 * example: (e & 63) == 63, el will be e+1.
	 * अगर that even was the very last bit,
	 * it would trigger an निश्चित in __bm_change_bits_to()
	 */
	अगर (el <= e)
		__bm_change_bits_to(device, el, e, 1);
	spin_unlock_irq(&b->bm_lock);
पूर्ण

/* वापसs bit state
 * wants bitnr, NOT sector.
 * inherently racy... area needs to be locked by means of अणुal,rsपूर्ण_lru
 *  1 ... bit set
 *  0 ... bit not set
 * -1 ... first out of bounds access, stop testing क्रम bits!
 */
पूर्णांक drbd_bm_test_bit(काष्ठा drbd_device *device, स्थिर अचिन्हित दीर्घ bitnr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित दीर्घ *p_addr;
	पूर्णांक i;

	अगर (!expect(b))
		वापस 0;
	अगर (!expect(b->bm_pages))
		वापस 0;

	spin_lock_irqsave(&b->bm_lock, flags);
	अगर (BM_DONT_TEST & b->bm_flags)
		bm_prपूर्णांक_lock_info(device);
	अगर (bitnr < b->bm_bits) अणु
		p_addr = bm_map_pidx(b, bm_bit_to_page_idx(b, bitnr));
		i = test_bit_le(bitnr & BITS_PER_PAGE_MASK, p_addr) ? 1 : 0;
		bm_unmap(p_addr);
	पूर्ण अन्यथा अगर (bitnr == b->bm_bits) अणु
		i = -1;
	पूर्ण अन्यथा अणु /* (bitnr > b->bm_bits) */
		drbd_err(device, "bitnr=%lu > bm_bits=%lu\n", bitnr, b->bm_bits);
		i = 0;
	पूर्ण

	spin_unlock_irqrestore(&b->bm_lock, flags);
	वापस i;
पूर्ण

/* वापसs number of bits set in the range [s, e] */
पूर्णांक drbd_bm_count_bits(काष्ठा drbd_device *device, स्थिर अचिन्हित दीर्घ s, स्थिर अचिन्हित दीर्घ e)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	अचिन्हित दीर्घ *p_addr = शून्य;
	अचिन्हित दीर्घ bitnr;
	अचिन्हित पूर्णांक page_nr = -1U;
	पूर्णांक c = 0;

	/* If this is called without a biपंचांगap, that is a bug.  But just to be
	 * robust in हाल we screwed up अन्यथाwhere, in that हाल pretend there
	 * was one dirty bit in the requested area, so we won't try to करो a
	 * local पढ़ो there (no biपंचांगap probably implies no disk) */
	अगर (!expect(b))
		वापस 1;
	अगर (!expect(b->bm_pages))
		वापस 1;

	spin_lock_irqsave(&b->bm_lock, flags);
	अगर (BM_DONT_TEST & b->bm_flags)
		bm_prपूर्णांक_lock_info(device);
	क्रम (bitnr = s; bitnr <= e; bitnr++) अणु
		अचिन्हित पूर्णांक idx = bm_bit_to_page_idx(b, bitnr);
		अगर (page_nr != idx) अणु
			page_nr = idx;
			अगर (p_addr)
				bm_unmap(p_addr);
			p_addr = bm_map_pidx(b, idx);
		पूर्ण
		अगर (expect(bitnr < b->bm_bits))
			c += (0 != test_bit_le(bitnr - (page_nr << (PAGE_SHIFT+3)), p_addr));
		अन्यथा
			drbd_err(device, "bitnr=%lu bm_bits=%lu\n", bitnr, b->bm_bits);
	पूर्ण
	अगर (p_addr)
		bm_unmap(p_addr);
	spin_unlock_irqrestore(&b->bm_lock, flags);
	वापस c;
पूर्ण


/* inherently racy...
 * वापस value may be alपढ़ोy out-of-date when this function वापसs.
 * but the general usage is that this is only use during a cstate when bits are
 * only cleared, not set, and typically only care क्रम the हाल when the वापस
 * value is zero, or we alपढ़ोy "locked" this "bitmap extent" by other means.
 *
 * enr is bm-extent number, since we chose to name one sector (512 bytes)
 * worth of the biपंचांगap a "bitmap extent".
 *
 * TODO
 * I think since we use it like a reference count, we should use the real
 * reference count of some biपंचांगap extent element from some lru instead...
 *
 */
पूर्णांक drbd_bm_e_weight(काष्ठा drbd_device *device, अचिन्हित दीर्घ enr)
अणु
	काष्ठा drbd_biपंचांगap *b = device->biपंचांगap;
	पूर्णांक count, s, e;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *p_addr, *bm;

	अगर (!expect(b))
		वापस 0;
	अगर (!expect(b->bm_pages))
		वापस 0;

	spin_lock_irqsave(&b->bm_lock, flags);
	अगर (BM_DONT_TEST & b->bm_flags)
		bm_prपूर्णांक_lock_info(device);

	s = S2W(enr);
	e = min((माप_प्रकार)S2W(enr+1), b->bm_words);
	count = 0;
	अगर (s < b->bm_words) अणु
		पूर्णांक n = e-s;
		p_addr = bm_map_pidx(b, bm_word_to_page_idx(b, s));
		bm = p_addr + MLPP(s);
		count += biपंचांगap_weight(bm, n * BITS_PER_LONG);
		bm_unmap(p_addr);
	पूर्ण अन्यथा अणु
		drbd_err(device, "start offset (%d) too large in drbd_bm_e_weight\n", s);
	पूर्ण
	spin_unlock_irqrestore(&b->bm_lock, flags);
	वापस count;
पूर्ण
