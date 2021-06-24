<शैली गुरु>
/*
 * A Remote Heap.  Remote means that we करोn't touch the memory that the
 * heap poपूर्णांकs to. Normal heap implementations use the memory they manage
 * to place their list. We cannot करो that because the memory we manage may
 * have special properties, क्रम example it is uncachable or of dअगरferent
 * endianess.
 *
 * Author: Pantelis Antoniou <panto@पूर्णांकracom.gr>
 *
 * 2004 (c) INTRACOM S.A. Greece. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/rheap.h>

/*
 * Fixup a list_head, needed when copying lists.  If the poपूर्णांकers fall
 * between s and e, apply the delta.  This assumes that
 * माप(काष्ठा list_head *) == माप(अचिन्हित दीर्घ *).
 */
अटल अंतरभूत व्योम fixup(अचिन्हित दीर्घ s, अचिन्हित दीर्घ e, पूर्णांक d,
			 काष्ठा list_head *l)
अणु
	अचिन्हित दीर्घ *pp;

	pp = (अचिन्हित दीर्घ *)&l->next;
	अगर (*pp >= s && *pp < e)
		*pp += d;

	pp = (अचिन्हित दीर्घ *)&l->prev;
	अगर (*pp >= s && *pp < e)
		*pp += d;
पूर्ण

/* Grow the allocated blocks */
अटल पूर्णांक grow(rh_info_t * info, पूर्णांक max_blocks)
अणु
	rh_block_t *block, *blk;
	पूर्णांक i, new_blocks;
	पूर्णांक delta;
	अचिन्हित दीर्घ blks, blke;

	अगर (max_blocks <= info->max_blocks)
		वापस -EINVAL;

	new_blocks = max_blocks - info->max_blocks;

	block = kदो_स्मृति_array(max_blocks, माप(rh_block_t), GFP_ATOMIC);
	अगर (block == शून्य)
		वापस -ENOMEM;

	अगर (info->max_blocks > 0) अणु

		/* copy old block area */
		स_नकल(block, info->block,
		       माप(rh_block_t) * info->max_blocks);

		delta = (अक्षर *)block - (अक्षर *)info->block;

		/* and fixup list poपूर्णांकers */
		blks = (अचिन्हित दीर्घ)info->block;
		blke = (अचिन्हित दीर्घ)(info->block + info->max_blocks);

		क्रम (i = 0, blk = block; i < info->max_blocks; i++, blk++)
			fixup(blks, blke, delta, &blk->list);

		fixup(blks, blke, delta, &info->empty_list);
		fixup(blks, blke, delta, &info->मुक्त_list);
		fixup(blks, blke, delta, &info->taken_list);

		/* मुक्त the old allocated memory */
		अगर ((info->flags & RHIF_STATIC_BLOCK) == 0)
			kमुक्त(info->block);
	पूर्ण

	info->block = block;
	info->empty_slots += new_blocks;
	info->max_blocks = max_blocks;
	info->flags &= ~RHIF_STATIC_BLOCK;

	/* add all new blocks to the मुक्त list */
	blk = block + info->max_blocks - new_blocks;
	क्रम (i = 0; i < new_blocks; i++, blk++)
		list_add(&blk->list, &info->empty_list);

	वापस 0;
पूर्ण

/*
 * Assure at least the required amount of empty slots.  If this function
 * causes a grow in the block area then all poपूर्णांकers kept to the block
 * area are invalid!
 */
अटल पूर्णांक assure_empty(rh_info_t * info, पूर्णांक slots)
अणु
	पूर्णांक max_blocks;

	/* This function is not meant to be used to grow uncontrollably */
	अगर (slots >= 4)
		वापस -EINVAL;

	/* Enough space */
	अगर (info->empty_slots >= slots)
		वापस 0;

	/* Next 16 sized block */
	max_blocks = ((info->max_blocks + slots) + 15) & ~15;

	वापस grow(info, max_blocks);
पूर्ण

अटल rh_block_t *get_slot(rh_info_t * info)
अणु
	rh_block_t *blk;

	/* If no more मुक्त slots, and failure to extend. */
	/* XXX: You should have called assure_empty beक्रमe */
	अगर (info->empty_slots == 0) अणु
		prपूर्णांकk(KERN_ERR "rh: out of slots; crash is imminent.\n");
		वापस शून्य;
	पूर्ण

	/* Get empty slot to use */
	blk = list_entry(info->empty_list.next, rh_block_t, list);
	list_del_init(&blk->list);
	info->empty_slots--;

	/* Initialize */
	blk->start = 0;
	blk->size = 0;
	blk->owner = शून्य;

	वापस blk;
पूर्ण

अटल अंतरभूत व्योम release_slot(rh_info_t * info, rh_block_t * blk)
अणु
	list_add(&blk->list, &info->empty_list);
	info->empty_slots++;
पूर्ण

अटल व्योम attach_मुक्त_block(rh_info_t * info, rh_block_t * blkn)
अणु
	rh_block_t *blk;
	rh_block_t *beक्रमe;
	rh_block_t *after;
	rh_block_t *next;
	पूर्णांक size;
	अचिन्हित दीर्घ s, e, bs, be;
	काष्ठा list_head *l;

	/* We assume that they are aligned properly */
	size = blkn->size;
	s = blkn->start;
	e = s + size;

	/* Find the blocks immediately beक्रमe and after the given one
	 * (अगर any) */
	beक्रमe = शून्य;
	after = शून्य;
	next = शून्य;

	list_क्रम_each(l, &info->मुक्त_list) अणु
		blk = list_entry(l, rh_block_t, list);

		bs = blk->start;
		be = bs + blk->size;

		अगर (next == शून्य && s >= bs)
			next = blk;

		अगर (be == s)
			beक्रमe = blk;

		अगर (e == bs)
			after = blk;

		/* If both are not null, अवरोध now */
		अगर (beक्रमe != शून्य && after != शून्य)
			अवरोध;
	पूर्ण

	/* Now check अगर they are really adjacent */
	अगर (beक्रमe && s != (beक्रमe->start + beक्रमe->size))
		beक्रमe = शून्य;

	अगर (after && e != after->start)
		after = शून्य;

	/* No coalescing; list insert and वापस */
	अगर (beक्रमe == शून्य && after == शून्य) अणु

		अगर (next != शून्य)
			list_add(&blkn->list, &next->list);
		अन्यथा
			list_add(&blkn->list, &info->मुक्त_list);

		वापस;
	पूर्ण

	/* We करोn't need it anymore */
	release_slot(info, blkn);

	/* Grow the beक्रमe block */
	अगर (beक्रमe != शून्य && after == शून्य) अणु
		beक्रमe->size += size;
		वापस;
	पूर्ण

	/* Grow the after block backwards */
	अगर (beक्रमe == शून्य && after != शून्य) अणु
		after->start -= size;
		after->size += size;
		वापस;
	पूर्ण

	/* Grow the beक्रमe block, and release the after block */
	beक्रमe->size += size + after->size;
	list_del(&after->list);
	release_slot(info, after);
पूर्ण

अटल व्योम attach_taken_block(rh_info_t * info, rh_block_t * blkn)
अणु
	rh_block_t *blk;
	काष्ठा list_head *l;

	/* Find the block immediately beक्रमe the given one (अगर any) */
	list_क्रम_each(l, &info->taken_list) अणु
		blk = list_entry(l, rh_block_t, list);
		अगर (blk->start > blkn->start) अणु
			list_add_tail(&blkn->list, &blk->list);
			वापस;
		पूर्ण
	पूर्ण

	list_add_tail(&blkn->list, &info->taken_list);
पूर्ण

/*
 * Create a remote heap dynamically.  Note that no memory क्रम the blocks
 * are allocated.  It will upon the first allocation
 */
rh_info_t *rh_create(अचिन्हित पूर्णांक alignment)
अणु
	rh_info_t *info;

	/* Alignment must be a घातer of two */
	अगर ((alignment & (alignment - 1)) != 0)
		वापस ERR_PTR(-EINVAL);

	info = kदो_स्मृति(माप(*info), GFP_ATOMIC);
	अगर (info == शून्य)
		वापस ERR_PTR(-ENOMEM);

	info->alignment = alignment;

	/* Initially everything as empty */
	info->block = शून्य;
	info->max_blocks = 0;
	info->empty_slots = 0;
	info->flags = 0;

	INIT_LIST_HEAD(&info->empty_list);
	INIT_LIST_HEAD(&info->मुक्त_list);
	INIT_LIST_HEAD(&info->taken_list);

	वापस info;
पूर्ण
EXPORT_SYMBOL_GPL(rh_create);

/*
 * Destroy a dynamically created remote heap.  Deallocate only अगर the areas
 * are not अटल
 */
व्योम rh_destroy(rh_info_t * info)
अणु
	अगर ((info->flags & RHIF_STATIC_BLOCK) == 0)
		kमुक्त(info->block);

	अगर ((info->flags & RHIF_STATIC_INFO) == 0)
		kमुक्त(info);
पूर्ण
EXPORT_SYMBOL_GPL(rh_destroy);

/*
 * Initialize in place a remote heap info block.  This is needed to support
 * operation very early in the startup of the kernel, when it is not yet safe
 * to call kदो_स्मृति.
 */
व्योम rh_init(rh_info_t * info, अचिन्हित पूर्णांक alignment, पूर्णांक max_blocks,
	     rh_block_t * block)
अणु
	पूर्णांक i;
	rh_block_t *blk;

	/* Alignment must be a घातer of two */
	अगर ((alignment & (alignment - 1)) != 0)
		वापस;

	info->alignment = alignment;

	/* Initially everything as empty */
	info->block = block;
	info->max_blocks = max_blocks;
	info->empty_slots = max_blocks;
	info->flags = RHIF_STATIC_INFO | RHIF_STATIC_BLOCK;

	INIT_LIST_HEAD(&info->empty_list);
	INIT_LIST_HEAD(&info->मुक्त_list);
	INIT_LIST_HEAD(&info->taken_list);

	/* Add all new blocks to the मुक्त list */
	क्रम (i = 0, blk = block; i < max_blocks; i++, blk++)
		list_add(&blk->list, &info->empty_list);
पूर्ण
EXPORT_SYMBOL_GPL(rh_init);

/* Attach a मुक्त memory region, coalesces regions अगर adjacent */
पूर्णांक rh_attach_region(rh_info_t * info, अचिन्हित दीर्घ start, पूर्णांक size)
अणु
	rh_block_t *blk;
	अचिन्हित दीर्घ s, e, m;
	पूर्णांक r;

	/* The region must be aligned */
	s = start;
	e = s + size;
	m = info->alignment - 1;

	/* Round start up */
	s = (s + m) & ~m;

	/* Round end करोwn */
	e = e & ~m;

	अगर (IS_ERR_VALUE(e) || (e < s))
		वापस -दुस्फल;

	/* Take final values */
	start = s;
	size = e - s;

	/* Grow the blocks, अगर needed */
	r = assure_empty(info, 1);
	अगर (r < 0)
		वापस r;

	blk = get_slot(info);
	blk->start = start;
	blk->size = size;
	blk->owner = शून्य;

	attach_मुक्त_block(info, blk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rh_attach_region);

/* Detatch given address range, splits मुक्त block अगर needed. */
अचिन्हित दीर्घ rh_detach_region(rh_info_t * info, अचिन्हित दीर्घ start, पूर्णांक size)
अणु
	काष्ठा list_head *l;
	rh_block_t *blk, *newblk;
	अचिन्हित दीर्घ s, e, m, bs, be;

	/* Validate size */
	अगर (size <= 0)
		वापस (अचिन्हित दीर्घ) -EINVAL;

	/* The region must be aligned */
	s = start;
	e = s + size;
	m = info->alignment - 1;

	/* Round start up */
	s = (s + m) & ~m;

	/* Round end करोwn */
	e = e & ~m;

	अगर (assure_empty(info, 1) < 0)
		वापस (अचिन्हित दीर्घ) -ENOMEM;

	blk = शून्य;
	list_क्रम_each(l, &info->मुक्त_list) अणु
		blk = list_entry(l, rh_block_t, list);
		/* The range must lie entirely inside one मुक्त block */
		bs = blk->start;
		be = blk->start + blk->size;
		अगर (s >= bs && e <= be)
			अवरोध;
		blk = शून्य;
	पूर्ण

	अगर (blk == शून्य)
		वापस (अचिन्हित दीर्घ) -ENOMEM;

	/* Perfect fit */
	अगर (bs == s && be == e) अणु
		/* Delete from मुक्त list, release slot */
		list_del(&blk->list);
		release_slot(info, blk);
		वापस s;
	पूर्ण

	/* blk still in मुक्त list, with updated start and/or size */
	अगर (bs == s || be == e) अणु
		अगर (bs == s)
			blk->start += size;
		blk->size -= size;

	पूर्ण अन्यथा अणु
		/* The front मुक्त fragment */
		blk->size = s - bs;

		/* the back मुक्त fragment */
		newblk = get_slot(info);
		newblk->start = e;
		newblk->size = be - e;

		list_add(&newblk->list, &blk->list);
	पूर्ण

	वापस s;
पूर्ण
EXPORT_SYMBOL_GPL(rh_detach_region);

/* Allocate a block of memory at the specअगरied alignment.  The value वापसed
 * is an offset पूर्णांकo the buffer initialized by rh_init(), or a negative number
 * अगर there is an error.
 */
अचिन्हित दीर्घ rh_alloc_align(rh_info_t * info, पूर्णांक size, पूर्णांक alignment, स्थिर अक्षर *owner)
अणु
	काष्ठा list_head *l;
	rh_block_t *blk;
	rh_block_t *newblk;
	अचिन्हित दीर्घ start, sp_size;

	/* Validate size, and alignment must be घातer of two */
	अगर (size <= 0 || (alignment & (alignment - 1)) != 0)
		वापस (अचिन्हित दीर्घ) -EINVAL;

	/* Align to configured alignment */
	size = (size + (info->alignment - 1)) & ~(info->alignment - 1);

	अगर (assure_empty(info, 2) < 0)
		वापस (अचिन्हित दीर्घ) -ENOMEM;

	blk = शून्य;
	list_क्रम_each(l, &info->मुक्त_list) अणु
		blk = list_entry(l, rh_block_t, list);
		अगर (size <= blk->size) अणु
			start = (blk->start + alignment - 1) & ~(alignment - 1);
			अगर (start + size <= blk->start + blk->size)
				अवरोध;
		पूर्ण
		blk = शून्य;
	पूर्ण

	अगर (blk == शून्य)
		वापस (अचिन्हित दीर्घ) -ENOMEM;

	/* Just fits */
	अगर (blk->size == size) अणु
		/* Move from मुक्त list to taken list */
		list_del(&blk->list);
		newblk = blk;
	पूर्ण अन्यथा अणु
		/* Fragment caused, split अगर needed */
		/* Create block क्रम fragment in the beginning */
		sp_size = start - blk->start;
		अगर (sp_size) अणु
			rh_block_t *spblk;

			spblk = get_slot(info);
			spblk->start = blk->start;
			spblk->size = sp_size;
			/* add beक्रमe the blk */
			list_add(&spblk->list, blk->list.prev);
		पूर्ण
		newblk = get_slot(info);
		newblk->start = start;
		newblk->size = size;

		/* blk still in मुक्त list, with updated start and size
		 * क्रम fragment in the end */
		blk->start = start + size;
		blk->size -= sp_size + size;
		/* No fragment in the end, हटाओ blk */
		अगर (blk->size == 0) अणु
			list_del(&blk->list);
			release_slot(info, blk);
		पूर्ण
	पूर्ण

	newblk->owner = owner;
	attach_taken_block(info, newblk);

	वापस start;
पूर्ण
EXPORT_SYMBOL_GPL(rh_alloc_align);

/* Allocate a block of memory at the शेष alignment.  The value वापसed is
 * an offset पूर्णांकo the buffer initialized by rh_init(), or a negative number अगर
 * there is an error.
 */
अचिन्हित दीर्घ rh_alloc(rh_info_t * info, पूर्णांक size, स्थिर अक्षर *owner)
अणु
	वापस rh_alloc_align(info, size, info->alignment, owner);
पूर्ण
EXPORT_SYMBOL_GPL(rh_alloc);

/* Allocate a block of memory at the given offset, rounded up to the शेष
 * alignment.  The value वापसed is an offset पूर्णांकo the buffer initialized by
 * rh_init(), or a negative number अगर there is an error.
 */
अचिन्हित दीर्घ rh_alloc_fixed(rh_info_t * info, अचिन्हित दीर्घ start, पूर्णांक size, स्थिर अक्षर *owner)
अणु
	काष्ठा list_head *l;
	rh_block_t *blk, *newblk1, *newblk2;
	अचिन्हित दीर्घ s, e, m, bs = 0, be = 0;

	/* Validate size */
	अगर (size <= 0)
		वापस (अचिन्हित दीर्घ) -EINVAL;

	/* The region must be aligned */
	s = start;
	e = s + size;
	m = info->alignment - 1;

	/* Round start up */
	s = (s + m) & ~m;

	/* Round end करोwn */
	e = e & ~m;

	अगर (assure_empty(info, 2) < 0)
		वापस (अचिन्हित दीर्घ) -ENOMEM;

	blk = शून्य;
	list_क्रम_each(l, &info->मुक्त_list) अणु
		blk = list_entry(l, rh_block_t, list);
		/* The range must lie entirely inside one मुक्त block */
		bs = blk->start;
		be = blk->start + blk->size;
		अगर (s >= bs && e <= be)
			अवरोध;
		blk = शून्य;
	पूर्ण

	अगर (blk == शून्य)
		वापस (अचिन्हित दीर्घ) -ENOMEM;

	/* Perfect fit */
	अगर (bs == s && be == e) अणु
		/* Move from मुक्त list to taken list */
		list_del(&blk->list);
		blk->owner = owner;

		start = blk->start;
		attach_taken_block(info, blk);

		वापस start;

	पूर्ण

	/* blk still in मुक्त list, with updated start and/or size */
	अगर (bs == s || be == e) अणु
		अगर (bs == s)
			blk->start += size;
		blk->size -= size;

	पूर्ण अन्यथा अणु
		/* The front मुक्त fragment */
		blk->size = s - bs;

		/* The back मुक्त fragment */
		newblk2 = get_slot(info);
		newblk2->start = e;
		newblk2->size = be - e;

		list_add(&newblk2->list, &blk->list);
	पूर्ण

	newblk1 = get_slot(info);
	newblk1->start = s;
	newblk1->size = e - s;
	newblk1->owner = owner;

	start = newblk1->start;
	attach_taken_block(info, newblk1);

	वापस start;
पूर्ण
EXPORT_SYMBOL_GPL(rh_alloc_fixed);

/* Deallocate the memory previously allocated by one of the rh_alloc functions.
 * The वापस value is the size of the deallocated block, or a negative number
 * अगर there is an error.
 */
पूर्णांक rh_मुक्त(rh_info_t * info, अचिन्हित दीर्घ start)
अणु
	rh_block_t *blk, *blk2;
	काष्ठा list_head *l;
	पूर्णांक size;

	/* Linear search क्रम block */
	blk = शून्य;
	list_क्रम_each(l, &info->taken_list) अणु
		blk2 = list_entry(l, rh_block_t, list);
		अगर (start < blk2->start)
			अवरोध;
		blk = blk2;
	पूर्ण

	अगर (blk == शून्य || start > (blk->start + blk->size))
		वापस -EINVAL;

	/* Remove from taken list */
	list_del(&blk->list);

	/* Get size of मुक्तd block */
	size = blk->size;
	attach_मुक्त_block(info, blk);

	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(rh_मुक्त);

पूर्णांक rh_get_stats(rh_info_t * info, पूर्णांक what, पूर्णांक max_stats, rh_stats_t * stats)
अणु
	rh_block_t *blk;
	काष्ठा list_head *l;
	काष्ठा list_head *h;
	पूर्णांक nr;

	चयन (what) अणु

	हाल RHGS_FREE:
		h = &info->मुक्त_list;
		अवरोध;

	हाल RHGS_TAKEN:
		h = &info->taken_list;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Linear search क्रम block */
	nr = 0;
	list_क्रम_each(l, h) अणु
		blk = list_entry(l, rh_block_t, list);
		अगर (stats != शून्य && nr < max_stats) अणु
			stats->start = blk->start;
			stats->size = blk->size;
			stats->owner = blk->owner;
			stats++;
		पूर्ण
		nr++;
	पूर्ण

	वापस nr;
पूर्ण
EXPORT_SYMBOL_GPL(rh_get_stats);

पूर्णांक rh_set_owner(rh_info_t * info, अचिन्हित दीर्घ start, स्थिर अक्षर *owner)
अणु
	rh_block_t *blk, *blk2;
	काष्ठा list_head *l;
	पूर्णांक size;

	/* Linear search क्रम block */
	blk = शून्य;
	list_क्रम_each(l, &info->taken_list) अणु
		blk2 = list_entry(l, rh_block_t, list);
		अगर (start < blk2->start)
			अवरोध;
		blk = blk2;
	पूर्ण

	अगर (blk == शून्य || start > (blk->start + blk->size))
		वापस -EINVAL;

	blk->owner = owner;
	size = blk->size;

	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(rh_set_owner);

व्योम rh_dump(rh_info_t * info)
अणु
	अटल rh_stats_t st[32];	/* XXX maximum 32 blocks */
	पूर्णांक maxnr;
	पूर्णांक i, nr;

	maxnr = ARRAY_SIZE(st);

	prपूर्णांकk(KERN_INFO
	       "info @0x%p (%d slots empty / %d max)\n",
	       info, info->empty_slots, info->max_blocks);

	prपूर्णांकk(KERN_INFO "  Free:\n");
	nr = rh_get_stats(info, RHGS_FREE, maxnr, st);
	अगर (nr > maxnr)
		nr = maxnr;
	क्रम (i = 0; i < nr; i++)
		prपूर्णांकk(KERN_INFO
		       "    0x%lx-0x%lx (%u)\n",
		       st[i].start, st[i].start + st[i].size,
		       st[i].size);
	prपूर्णांकk(KERN_INFO "\n");

	prपूर्णांकk(KERN_INFO "  Taken:\n");
	nr = rh_get_stats(info, RHGS_TAKEN, maxnr, st);
	अगर (nr > maxnr)
		nr = maxnr;
	क्रम (i = 0; i < nr; i++)
		prपूर्णांकk(KERN_INFO
		       "    0x%lx-0x%lx (%u) %s\n",
		       st[i].start, st[i].start + st[i].size,
		       st[i].size, st[i].owner != शून्य ? st[i].owner : "");
	prपूर्णांकk(KERN_INFO "\n");
पूर्ण
EXPORT_SYMBOL_GPL(rh_dump);

व्योम rh_dump_blk(rh_info_t * info, rh_block_t * blk)
अणु
	prपूर्णांकk(KERN_INFO
	       "blk @0x%p: 0x%lx-0x%lx (%u)\n",
	       blk, blk->start, blk->start + blk->size, blk->size);
पूर्ण
EXPORT_SYMBOL_GPL(rh_dump_blk);

