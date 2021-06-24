<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Generic memory management routines क्रम soundcard memory allocation
 */

#समावेश <linux/mutex.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/util_स्मृति.स>

MODULE_AUTHOR("Takashi Iwai");
MODULE_DESCRIPTION("Generic memory management routines for soundcard memory allocation");
MODULE_LICENSE("GPL");

#घोषणा get_memblk(p)	list_entry(p, काष्ठा snd_util_memblk, list)

/*
 * create a new memory manager
 */
काष्ठा snd_util_memhdr *
snd_util_memhdr_new(पूर्णांक memsize)
अणु
	काष्ठा snd_util_memhdr *hdr;

	hdr = kzalloc(माप(*hdr), GFP_KERNEL);
	अगर (hdr == शून्य)
		वापस शून्य;
	hdr->size = memsize;
	mutex_init(&hdr->block_mutex);
	INIT_LIST_HEAD(&hdr->block);

	वापस hdr;
पूर्ण

/*
 * मुक्त a memory manager
 */
व्योम snd_util_memhdr_मुक्त(काष्ठा snd_util_memhdr *hdr)
अणु
	काष्ठा list_head *p;

	अगर (!hdr)
		वापस;
	/* release all blocks */
	जबतक ((p = hdr->block.next) != &hdr->block) अणु
		list_del(p);
		kमुक्त(get_memblk(p));
	पूर्ण
	kमुक्त(hdr);
पूर्ण

/*
 * allocate a memory block (without mutex)
 */
काष्ठा snd_util_memblk *
__snd_util_mem_alloc(काष्ठा snd_util_memhdr *hdr, पूर्णांक size)
अणु
	काष्ठा snd_util_memblk *blk;
	अचिन्हित पूर्णांक units, prev_offset;
	काष्ठा list_head *p;

	अगर (snd_BUG_ON(!hdr || size <= 0))
		वापस शून्य;

	/* word alignment */
	units = size;
	अगर (units & 1)
		units++;
	अगर (units > hdr->size)
		वापस शून्य;

	/* look क्रम empty block */
	prev_offset = 0;
	list_क्रम_each(p, &hdr->block) अणु
		blk = get_memblk(p);
		अगर (blk->offset - prev_offset >= units)
			जाओ __found;
		prev_offset = blk->offset + blk->size;
	पूर्ण
	अगर (hdr->size - prev_offset < units)
		वापस शून्य;

__found:
	वापस __snd_util_memblk_new(hdr, units, p->prev);
पूर्ण


/*
 * create a new memory block with the given size
 * the block is linked next to prev
 */
काष्ठा snd_util_memblk *
__snd_util_memblk_new(काष्ठा snd_util_memhdr *hdr, अचिन्हित पूर्णांक units,
		      काष्ठा list_head *prev)
अणु
	काष्ठा snd_util_memblk *blk;

	blk = kदो_स्मृति(माप(काष्ठा snd_util_memblk) + hdr->block_extra_size,
		      GFP_KERNEL);
	अगर (blk == शून्य)
		वापस शून्य;

	अगर (prev == &hdr->block)
		blk->offset = 0;
	अन्यथा अणु
		काष्ठा snd_util_memblk *p = get_memblk(prev);
		blk->offset = p->offset + p->size;
	पूर्ण
	blk->size = units;
	list_add(&blk->list, prev);
	hdr->nblocks++;
	hdr->used += units;
	वापस blk;
पूर्ण


/*
 * allocate a memory block (with mutex)
 */
काष्ठा snd_util_memblk *
snd_util_mem_alloc(काष्ठा snd_util_memhdr *hdr, पूर्णांक size)
अणु
	काष्ठा snd_util_memblk *blk;
	mutex_lock(&hdr->block_mutex);
	blk = __snd_util_mem_alloc(hdr, size);
	mutex_unlock(&hdr->block_mutex);
	वापस blk;
पूर्ण


/*
 * हटाओ the block from linked-list and मुक्त resource
 * (without mutex)
 */
व्योम
__snd_util_mem_मुक्त(काष्ठा snd_util_memhdr *hdr, काष्ठा snd_util_memblk *blk)
अणु
	list_del(&blk->list);
	hdr->nblocks--;
	hdr->used -= blk->size;
	kमुक्त(blk);
पूर्ण

/*
 * मुक्त a memory block (with mutex)
 */
पूर्णांक snd_util_mem_मुक्त(काष्ठा snd_util_memhdr *hdr, काष्ठा snd_util_memblk *blk)
अणु
	अगर (snd_BUG_ON(!hdr || !blk))
		वापस -EINVAL;

	mutex_lock(&hdr->block_mutex);
	__snd_util_mem_मुक्त(hdr, blk);
	mutex_unlock(&hdr->block_mutex);
	वापस 0;
पूर्ण

/*
 * वापस available memory size
 */
पूर्णांक snd_util_mem_avail(काष्ठा snd_util_memhdr *hdr)
अणु
	अचिन्हित पूर्णांक size;
	mutex_lock(&hdr->block_mutex);
	size = hdr->size - hdr->used;
	mutex_unlock(&hdr->block_mutex);
	वापस size;
पूर्ण


EXPORT_SYMBOL(snd_util_memhdr_new);
EXPORT_SYMBOL(snd_util_memhdr_मुक्त);
EXPORT_SYMBOL(snd_util_mem_alloc);
EXPORT_SYMBOL(snd_util_mem_मुक्त);
EXPORT_SYMBOL(snd_util_mem_avail);
EXPORT_SYMBOL(__snd_util_mem_alloc);
EXPORT_SYMBOL(__snd_util_mem_मुक्त);
EXPORT_SYMBOL(__snd_util_memblk_new);
