<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Berkeley style UIO काष्ठाures	-	Alan Cox 1994.
 */
#अगर_अघोषित __LINUX_UIO_H
#घोषणा __LINUX_UIO_H

#समावेश <linux/kernel.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <uapi/linux/uपन.स>

काष्ठा page;
काष्ठा pipe_inode_info;

काष्ठा kvec अणु
	व्योम *iov_base; /* and that should *never* hold a userland poपूर्णांकer */
	माप_प्रकार iov_len;
पूर्ण;

क्रमागत iter_type अणु
	/* iter types */
	ITER_IOVEC = 4,
	ITER_KVEC = 8,
	ITER_BVEC = 16,
	ITER_PIPE = 32,
	ITER_DISCARD = 64,
	ITER_XARRAY = 128,
पूर्ण;

काष्ठा iov_iter अणु
	/*
	 * Bit 0 is the पढ़ो/ग_लिखो bit, set अगर we're writing.
	 * Bit 1 is the BVEC_FLAG_NO_REF bit, set अगर type is a bvec and
	 * the caller isn't expecting to drop a page reference when करोne.
	 */
	अचिन्हित पूर्णांक type;
	माप_प्रकार iov_offset;
	माप_प्रकार count;
	जोड़ अणु
		स्थिर काष्ठा iovec *iov;
		स्थिर काष्ठा kvec *kvec;
		स्थिर काष्ठा bio_vec *bvec;
		काष्ठा xarray *xarray;
		काष्ठा pipe_inode_info *pipe;
	पूर्ण;
	जोड़ अणु
		अचिन्हित दीर्घ nr_segs;
		काष्ठा अणु
			अचिन्हित पूर्णांक head;
			अचिन्हित पूर्णांक start_head;
		पूर्ण;
		loff_t xarray_start;
	पूर्ण;
पूर्ण;

अटल अंतरभूत क्रमागत iter_type iov_iter_type(स्थिर काष्ठा iov_iter *i)
अणु
	वापस i->type & ~(READ | WRITE);
पूर्ण

अटल अंतरभूत bool iter_is_iovec(स्थिर काष्ठा iov_iter *i)
अणु
	वापस iov_iter_type(i) == ITER_IOVEC;
पूर्ण

अटल अंतरभूत bool iov_iter_is_kvec(स्थिर काष्ठा iov_iter *i)
अणु
	वापस iov_iter_type(i) == ITER_KVEC;
पूर्ण

अटल अंतरभूत bool iov_iter_is_bvec(स्थिर काष्ठा iov_iter *i)
अणु
	वापस iov_iter_type(i) == ITER_BVEC;
पूर्ण

अटल अंतरभूत bool iov_iter_is_pipe(स्थिर काष्ठा iov_iter *i)
अणु
	वापस iov_iter_type(i) == ITER_PIPE;
पूर्ण

अटल अंतरभूत bool iov_iter_is_discard(स्थिर काष्ठा iov_iter *i)
अणु
	वापस iov_iter_type(i) == ITER_DISCARD;
पूर्ण

अटल अंतरभूत bool iov_iter_is_xarray(स्थिर काष्ठा iov_iter *i)
अणु
	वापस iov_iter_type(i) == ITER_XARRAY;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर iov_iter_rw(स्थिर काष्ठा iov_iter *i)
अणु
	वापस i->type & (READ | WRITE);
पूर्ण

/*
 * Total number of bytes covered by an iovec.
 *
 * NOTE that it is not safe to use this function until all the iovec's
 * segment lengths have been validated.  Because the inभागidual lengths can
 * overflow a माप_प्रकार when added together.
 */
अटल अंतरभूत माप_प्रकार iov_length(स्थिर काष्ठा iovec *iov, अचिन्हित दीर्घ nr_segs)
अणु
	अचिन्हित दीर्घ seg;
	माप_प्रकार ret = 0;

	क्रम (seg = 0; seg < nr_segs; seg++)
		ret += iov[seg].iov_len;
	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा iovec iov_iter_iovec(स्थिर काष्ठा iov_iter *iter)
अणु
	वापस (काष्ठा iovec) अणु
		.iov_base = iter->iov->iov_base + iter->iov_offset,
		.iov_len = min(iter->count,
			       iter->iov->iov_len - iter->iov_offset),
	पूर्ण;
पूर्ण

माप_प्रकार iov_iter_copy_from_user_atomic(काष्ठा page *page,
		काष्ठा iov_iter *i, अचिन्हित दीर्घ offset, माप_प्रकार bytes);
व्योम iov_iter_advance(काष्ठा iov_iter *i, माप_प्रकार bytes);
व्योम iov_iter_revert(काष्ठा iov_iter *i, माप_प्रकार bytes);
पूर्णांक iov_iter_fault_in_पढ़ोable(काष्ठा iov_iter *i, माप_प्रकार bytes);
माप_प्रकार iov_iter_single_seg_count(स्थिर काष्ठा iov_iter *i);
माप_प्रकार copy_page_to_iter(काष्ठा page *page, माप_प्रकार offset, माप_प्रकार bytes,
			 काष्ठा iov_iter *i);
माप_प्रकार copy_page_from_iter(काष्ठा page *page, माप_प्रकार offset, माप_प्रकार bytes,
			 काष्ठा iov_iter *i);

माप_प्रकार _copy_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i);
माप_प्रकार _copy_from_iter(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i);
bool _copy_from_iter_full(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i);
माप_प्रकार _copy_from_iter_nocache(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i);
bool _copy_from_iter_full_nocache(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i);

अटल __always_अंतरभूत __must_check
माप_प्रकार copy_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अगर (unlikely(!check_copy_size(addr, bytes, true)))
		वापस 0;
	अन्यथा
		वापस _copy_to_iter(addr, bytes, i);
पूर्ण

अटल __always_अंतरभूत __must_check
माप_प्रकार copy_from_iter(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अगर (unlikely(!check_copy_size(addr, bytes, false)))
		वापस 0;
	अन्यथा
		वापस _copy_from_iter(addr, bytes, i);
पूर्ण

अटल __always_अंतरभूत __must_check
bool copy_from_iter_full(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अगर (unlikely(!check_copy_size(addr, bytes, false)))
		वापस false;
	अन्यथा
		वापस _copy_from_iter_full(addr, bytes, i);
पूर्ण

अटल __always_अंतरभूत __must_check
माप_प्रकार copy_from_iter_nocache(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अगर (unlikely(!check_copy_size(addr, bytes, false)))
		वापस 0;
	अन्यथा
		वापस _copy_from_iter_nocache(addr, bytes, i);
पूर्ण

अटल __always_अंतरभूत __must_check
bool copy_from_iter_full_nocache(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अगर (unlikely(!check_copy_size(addr, bytes, false)))
		वापस false;
	अन्यथा
		वापस _copy_from_iter_full_nocache(addr, bytes, i);
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE
/*
 * Note, users like pmem that depend on the stricter semantics of
 * copy_from_iter_flushcache() than copy_from_iter_nocache() must check क्रम
 * IS_ENABLED(CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE) beक्रमe assuming that the
 * destination is flushed from the cache on वापस.
 */
माप_प्रकार _copy_from_iter_flushcache(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i);
#अन्यथा
#घोषणा _copy_from_iter_flushcache _copy_from_iter_nocache
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_HAS_COPY_MC
माप_प्रकार _copy_mc_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i);
#अन्यथा
#घोषणा _copy_mc_to_iter _copy_to_iter
#पूर्ण_अगर

अटल __always_अंतरभूत __must_check
माप_प्रकार copy_from_iter_flushcache(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अगर (unlikely(!check_copy_size(addr, bytes, false)))
		वापस 0;
	अन्यथा
		वापस _copy_from_iter_flushcache(addr, bytes, i);
पूर्ण

अटल __always_अंतरभूत __must_check
माप_प्रकार copy_mc_to_iter(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	अगर (unlikely(!check_copy_size(addr, bytes, true)))
		वापस 0;
	अन्यथा
		वापस _copy_mc_to_iter(addr, bytes, i);
पूर्ण

माप_प्रकार iov_iter_zero(माप_प्रकार bytes, काष्ठा iov_iter *);
अचिन्हित दीर्घ iov_iter_alignment(स्थिर काष्ठा iov_iter *i);
अचिन्हित दीर्घ iov_iter_gap_alignment(स्थिर काष्ठा iov_iter *i);
व्योम iov_iter_init(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction, स्थिर काष्ठा iovec *iov,
			अचिन्हित दीर्घ nr_segs, माप_प्रकार count);
व्योम iov_iter_kvec(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction, स्थिर काष्ठा kvec *kvec,
			अचिन्हित दीर्घ nr_segs, माप_प्रकार count);
व्योम iov_iter_bvec(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction, स्थिर काष्ठा bio_vec *bvec,
			अचिन्हित दीर्घ nr_segs, माप_प्रकार count);
व्योम iov_iter_pipe(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction, काष्ठा pipe_inode_info *pipe,
			माप_प्रकार count);
व्योम iov_iter_discard(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction, माप_प्रकार count);
व्योम iov_iter_xarray(काष्ठा iov_iter *i, अचिन्हित पूर्णांक direction, काष्ठा xarray *xarray,
		     loff_t start, माप_प्रकार count);
sमाप_प्रकार iov_iter_get_pages(काष्ठा iov_iter *i, काष्ठा page **pages,
			माप_प्रकार maxsize, अचिन्हित maxpages, माप_प्रकार *start);
sमाप_प्रकार iov_iter_get_pages_alloc(काष्ठा iov_iter *i, काष्ठा page ***pages,
			माप_प्रकार maxsize, माप_प्रकार *start);
पूर्णांक iov_iter_npages(स्थिर काष्ठा iov_iter *i, पूर्णांक maxpages);

स्थिर व्योम *dup_iter(काष्ठा iov_iter *new, काष्ठा iov_iter *old, gfp_t flags);

अटल अंतरभूत माप_प्रकार iov_iter_count(स्थिर काष्ठा iov_iter *i)
अणु
	वापस i->count;
पूर्ण

/*
 * Cap the iov_iter by given limit; note that the second argument is
 * *not* the new size - it's upper limit क्रम such.  Passing it a value
 * greater than the amount of data in iov_iter is fine - it'll just करो
 * nothing in that हाल.
 */
अटल अंतरभूत व्योम iov_iter_truncate(काष्ठा iov_iter *i, u64 count)
अणु
	/*
	 * count करोesn't have to fit in माप_प्रकार - comparison extends both
	 * opeअक्रमs to u64 here and any value that would be truncated by
	 * conversion in assignement is by definition greater than all
	 * values of माप_प्रकार, including old i->count.
	 */
	अगर (i->count > count)
		i->count = count;
पूर्ण

/*
 * reexpand a previously truncated iterator; count must be no more than how much
 * we had shrunk it.
 */
अटल अंतरभूत व्योम iov_iter_reexpand(काष्ठा iov_iter *i, माप_प्रकार count)
अणु
	i->count = count;
पूर्ण

काष्ठा csum_state अणु
	__wsum csum;
	माप_प्रकार off;
पूर्ण;

माप_प्रकार csum_and_copy_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes, व्योम *csstate, काष्ठा iov_iter *i);
माप_प्रकार csum_and_copy_from_iter(व्योम *addr, माप_प्रकार bytes, __wsum *csum, काष्ठा iov_iter *i);
bool csum_and_copy_from_iter_full(व्योम *addr, माप_प्रकार bytes, __wsum *csum, काष्ठा iov_iter *i);
माप_प्रकार hash_and_copy_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes, व्योम *hashp,
		काष्ठा iov_iter *i);

काष्ठा iovec *iovec_from_user(स्थिर काष्ठा iovec __user *uvector,
		अचिन्हित दीर्घ nr_segs, अचिन्हित दीर्घ fast_segs,
		काष्ठा iovec *fast_iov, bool compat);
sमाप_प्रकार import_iovec(पूर्णांक type, स्थिर काष्ठा iovec __user *uvec,
		 अचिन्हित nr_segs, अचिन्हित fast_segs, काष्ठा iovec **iovp,
		 काष्ठा iov_iter *i);
sमाप_प्रकार __import_iovec(पूर्णांक type, स्थिर काष्ठा iovec __user *uvec,
		 अचिन्हित nr_segs, अचिन्हित fast_segs, काष्ठा iovec **iovp,
		 काष्ठा iov_iter *i, bool compat);
पूर्णांक import_single_range(पूर्णांक type, व्योम __user *buf, माप_प्रकार len,
		 काष्ठा iovec *iov, काष्ठा iov_iter *i);

पूर्णांक iov_iter_क्रम_each_range(काष्ठा iov_iter *i, माप_प्रकार bytes,
			    पूर्णांक (*f)(काष्ठा kvec *vec, व्योम *context),
			    व्योम *context);

#पूर्ण_अगर
