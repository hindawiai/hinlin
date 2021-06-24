<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * bvec iterator
 *
 * Copyright (C) 2001 Ming Lei <ming.lei@canonical.com>
 */
#अगर_अघोषित __LINUX_BVEC_ITER_H
#घोषणा __LINUX_BVEC_ITER_H

#समावेश <linux/bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/सीमा.स>
#समावेश <linux/minmax.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>

काष्ठा page;

/**
 * काष्ठा bio_vec - a contiguous range of physical memory addresses
 * @bv_page:   First page associated with the address range.
 * @bv_len:    Number of bytes in the address range.
 * @bv_offset: Start of the address range relative to the start of @bv_page.
 *
 * The following holds क्रम a bvec अगर n * PAGE_SIZE < bv_offset + bv_len:
 *
 *   nth_page(@bv_page, n) == @bv_page + n
 *
 * This holds because page_is_mergeable() checks the above property.
 */
काष्ठा bio_vec अणु
	काष्ठा page	*bv_page;
	अचिन्हित पूर्णांक	bv_len;
	अचिन्हित पूर्णांक	bv_offset;
पूर्ण;

काष्ठा bvec_iter अणु
	sector_t		bi_sector;	/* device address in 512 byte
						   sectors */
	अचिन्हित पूर्णांक		bi_size;	/* residual I/O count */

	अचिन्हित पूर्णांक		bi_idx;		/* current index पूर्णांकo bvl_vec */

	अचिन्हित पूर्णांक            bi_bvec_करोne;	/* number of bytes completed in
						   current bvec */
पूर्ण;

काष्ठा bvec_iter_all अणु
	काष्ठा bio_vec	bv;
	पूर्णांक		idx;
	अचिन्हित	करोne;
पूर्ण;

/*
 * various member access, note that bio_data should of course not be used
 * on highmem page vectors
 */
#घोषणा __bvec_iter_bvec(bvec, iter)	(&(bvec)[(iter).bi_idx])

/* multi-page (mp_bvec) helpers */
#घोषणा mp_bvec_iter_page(bvec, iter)				\
	(__bvec_iter_bvec((bvec), (iter))->bv_page)

#घोषणा mp_bvec_iter_len(bvec, iter)				\
	min((iter).bi_size,					\
	    __bvec_iter_bvec((bvec), (iter))->bv_len - (iter).bi_bvec_करोne)

#घोषणा mp_bvec_iter_offset(bvec, iter)				\
	(__bvec_iter_bvec((bvec), (iter))->bv_offset + (iter).bi_bvec_करोne)

#घोषणा mp_bvec_iter_page_idx(bvec, iter)			\
	(mp_bvec_iter_offset((bvec), (iter)) / PAGE_SIZE)

#घोषणा mp_bvec_iter_bvec(bvec, iter)				\
((काष्ठा bio_vec) अणु						\
	.bv_page	= mp_bvec_iter_page((bvec), (iter)),	\
	.bv_len		= mp_bvec_iter_len((bvec), (iter)),	\
	.bv_offset	= mp_bvec_iter_offset((bvec), (iter)),	\
पूर्ण)

/* For building single-page bvec in flight */
 #घोषणा bvec_iter_offset(bvec, iter)				\
	(mp_bvec_iter_offset((bvec), (iter)) % PAGE_SIZE)

#घोषणा bvec_iter_len(bvec, iter)				\
	min_t(अचिन्हित, mp_bvec_iter_len((bvec), (iter)),		\
	      PAGE_SIZE - bvec_iter_offset((bvec), (iter)))

#घोषणा bvec_iter_page(bvec, iter)				\
	(mp_bvec_iter_page((bvec), (iter)) +			\
	 mp_bvec_iter_page_idx((bvec), (iter)))

#घोषणा bvec_iter_bvec(bvec, iter)				\
((काष्ठा bio_vec) अणु						\
	.bv_page	= bvec_iter_page((bvec), (iter)),	\
	.bv_len		= bvec_iter_len((bvec), (iter)),	\
	.bv_offset	= bvec_iter_offset((bvec), (iter)),	\
पूर्ण)

अटल अंतरभूत bool bvec_iter_advance(स्थिर काष्ठा bio_vec *bv,
		काष्ठा bvec_iter *iter, अचिन्हित bytes)
अणु
	अचिन्हित पूर्णांक idx = iter->bi_idx;

	अगर (WARN_ONCE(bytes > iter->bi_size,
		     "Attempted to advance past end of bvec iter\n")) अणु
		iter->bi_size = 0;
		वापस false;
	पूर्ण

	iter->bi_size -= bytes;
	bytes += iter->bi_bvec_करोne;

	जबतक (bytes && bytes >= bv[idx].bv_len) अणु
		bytes -= bv[idx].bv_len;
		idx++;
	पूर्ण

	iter->bi_idx = idx;
	iter->bi_bvec_करोne = bytes;
	वापस true;
पूर्ण

/*
 * A simpler version of bvec_iter_advance(), @bytes should not span
 * across multiple bvec entries, i.e. bytes <= bv[i->bi_idx].bv_len
 */
अटल अंतरभूत व्योम bvec_iter_advance_single(स्थिर काष्ठा bio_vec *bv,
				काष्ठा bvec_iter *iter, अचिन्हित पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक करोne = iter->bi_bvec_करोne + bytes;

	अगर (करोne == bv[iter->bi_idx].bv_len) अणु
		करोne = 0;
		iter->bi_idx++;
	पूर्ण
	iter->bi_bvec_करोne = करोne;
	iter->bi_size -= bytes;
पूर्ण

#घोषणा क्रम_each_bvec(bvl, bio_vec, iter, start)			\
	क्रम (iter = (start);						\
	     (iter).bi_size &&						\
		((bvl = bvec_iter_bvec((bio_vec), (iter))), 1);	\
	     bvec_iter_advance_single((bio_vec), &(iter), (bvl).bv_len))

/* क्रम iterating one bio from start to end */
#घोषणा BVEC_ITER_ALL_INIT (काष्ठा bvec_iter)				\
अणु									\
	.bi_sector	= 0,						\
	.bi_size	= अच_पूर्णांक_उच्च,					\
	.bi_idx		= 0,						\
	.bi_bvec_करोne	= 0,						\
पूर्ण

अटल अंतरभूत काष्ठा bio_vec *bvec_init_iter_all(काष्ठा bvec_iter_all *iter_all)
अणु
	iter_all->करोne = 0;
	iter_all->idx = 0;

	वापस &iter_all->bv;
पूर्ण

अटल अंतरभूत व्योम bvec_advance(स्थिर काष्ठा bio_vec *bvec,
				काष्ठा bvec_iter_all *iter_all)
अणु
	काष्ठा bio_vec *bv = &iter_all->bv;

	अगर (iter_all->करोne) अणु
		bv->bv_page++;
		bv->bv_offset = 0;
	पूर्ण अन्यथा अणु
		bv->bv_page = bvec->bv_page + (bvec->bv_offset >> PAGE_SHIFT);
		bv->bv_offset = bvec->bv_offset & ~PAGE_MASK;
	पूर्ण
	bv->bv_len = min_t(अचिन्हित पूर्णांक, PAGE_SIZE - bv->bv_offset,
			   bvec->bv_len - iter_all->करोne);
	iter_all->करोne += bv->bv_len;

	अगर (iter_all->करोne == bvec->bv_len) अणु
		iter_all->idx++;
		iter_all->करोne = 0;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __LINUX_BVEC_ITER_H */
