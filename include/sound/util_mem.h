<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_UTIL_MEM_H
#घोषणा __SOUND_UTIL_MEM_H

#समावेश <linux/mutex.h>
/*
 *  Copyright (C) 2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Generic memory management routines क्रम soundcard memory allocation
 */

/*
 * memory block
 */
काष्ठा snd_util_memblk अणु
	अचिन्हित पूर्णांक size;		/* size of this block */
	अचिन्हित पूर्णांक offset;		/* zero-offset of this block */
	काष्ठा list_head list;		/* link */
पूर्ण;

#घोषणा snd_util_memblk_argptr(blk)	(व्योम*)((अक्षर*)(blk) + माप(काष्ठा snd_util_memblk))

/*
 * memory management inक्रमmation
 */
काष्ठा snd_util_memhdr अणु
	अचिन्हित पूर्णांक size;		/* size of whole data */
	काष्ठा list_head block;		/* block linked-list header */
	पूर्णांक nblocks;			/* # of allocated blocks */
	अचिन्हित पूर्णांक used;		/* used memory size */
	पूर्णांक block_extra_size;		/* extra data size of chunk */
	काष्ठा mutex block_mutex;	/* lock */
पूर्ण;

/*
 * prototypes
 */
काष्ठा snd_util_memhdr *snd_util_memhdr_new(पूर्णांक memsize);
व्योम snd_util_memhdr_मुक्त(काष्ठा snd_util_memhdr *hdr);
काष्ठा snd_util_memblk *snd_util_mem_alloc(काष्ठा snd_util_memhdr *hdr, पूर्णांक size);
पूर्णांक snd_util_mem_मुक्त(काष्ठा snd_util_memhdr *hdr, काष्ठा snd_util_memblk *blk);
पूर्णांक snd_util_mem_avail(काष्ठा snd_util_memhdr *hdr);

/* functions without mutex */
काष्ठा snd_util_memblk *__snd_util_mem_alloc(काष्ठा snd_util_memhdr *hdr, पूर्णांक size);
व्योम __snd_util_mem_मुक्त(काष्ठा snd_util_memhdr *hdr, काष्ठा snd_util_memblk *blk);
काष्ठा snd_util_memblk *__snd_util_memblk_new(काष्ठा snd_util_memhdr *hdr,
					      अचिन्हित पूर्णांक units,
					      काष्ठा list_head *prev);

#पूर्ण_अगर /* __SOUND_UTIL_MEM_H */
