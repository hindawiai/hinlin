<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#समावेश <linux/prime_numbers.h>
#समावेश <linux/अक्रमom.h>

#समावेश "i915_selftest.h"
#समावेश "i915_utils.h"

#घोषणा PFN_BIAS (1 << 10)

काष्ठा pfn_table अणु
	काष्ठा sg_table st;
	अचिन्हित दीर्घ start, end;
पूर्ण;

प्रकार अचिन्हित पूर्णांक (*npages_fn_t)(अचिन्हित दीर्घ n,
				    अचिन्हित दीर्घ count,
				    काष्ठा rnd_state *rnd);

अटल noअंतरभूत पूर्णांक expect_pfn_sg(काष्ठा pfn_table *pt,
				  npages_fn_t npages_fn,
				  काष्ठा rnd_state *rnd,
				  स्थिर अक्षर *who,
				  अचिन्हित दीर्घ समयout)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित दीर्घ pfn, n;

	pfn = pt->start;
	क्रम_each_sg(pt->st.sgl, sg, pt->st.nents, n) अणु
		काष्ठा page *page = sg_page(sg);
		अचिन्हित पूर्णांक npages = npages_fn(n, pt->st.nents, rnd);

		अगर (page_to_pfn(page) != pfn) अणु
			pr_err("%s: %s left pages out of order, expected pfn %lu, found pfn %lu (using for_each_sg)\n",
			       __func__, who, pfn, page_to_pfn(page));
			वापस -EINVAL;
		पूर्ण

		अगर (sg->length != npages * PAGE_SIZE) अणु
			pr_err("%s: %s copied wrong sg length, expected size %lu, found %u (using for_each_sg)\n",
			       __func__, who, npages * PAGE_SIZE, sg->length);
			वापस -EINVAL;
		पूर्ण

		अगर (igt_समयout(समयout, "%s timed out\n", who))
			वापस -EINTR;

		pfn += npages;
	पूर्ण
	अगर (pfn != pt->end) अणु
		pr_err("%s: %s finished on wrong pfn, expected %lu, found %lu\n",
		       __func__, who, pt->end, pfn);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक expect_pfn_sg_page_iter(काष्ठा pfn_table *pt,
					    स्थिर अक्षर *who,
					    अचिन्हित दीर्घ समयout)
अणु
	काष्ठा sg_page_iter sgiter;
	अचिन्हित दीर्घ pfn;

	pfn = pt->start;
	क्रम_each_sg_page(pt->st.sgl, &sgiter, pt->st.nents, 0) अणु
		काष्ठा page *page = sg_page_iter_page(&sgiter);

		अगर (page != pfn_to_page(pfn)) अणु
			pr_err("%s: %s left pages out of order, expected pfn %lu, found pfn %lu (using for_each_sg_page)\n",
			       __func__, who, pfn, page_to_pfn(page));
			वापस -EINVAL;
		पूर्ण

		अगर (igt_समयout(समयout, "%s timed out\n", who))
			वापस -EINTR;

		pfn++;
	पूर्ण
	अगर (pfn != pt->end) अणु
		pr_err("%s: %s finished on wrong pfn, expected %lu, found %lu\n",
		       __func__, who, pt->end, pfn);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक expect_pfn_sgtiter(काष्ठा pfn_table *pt,
				       स्थिर अक्षर *who,
				       अचिन्हित दीर्घ समयout)
अणु
	काष्ठा sgt_iter sgt;
	काष्ठा page *page;
	अचिन्हित दीर्घ pfn;

	pfn = pt->start;
	क्रम_each_sgt_page(page, sgt, &pt->st) अणु
		अगर (page != pfn_to_page(pfn)) अणु
			pr_err("%s: %s left pages out of order, expected pfn %lu, found pfn %lu (using for_each_sgt_page)\n",
			       __func__, who, pfn, page_to_pfn(page));
			वापस -EINVAL;
		पूर्ण

		अगर (igt_समयout(समयout, "%s timed out\n", who))
			वापस -EINTR;

		pfn++;
	पूर्ण
	अगर (pfn != pt->end) अणु
		pr_err("%s: %s finished on wrong pfn, expected %lu, found %lu\n",
		       __func__, who, pt->end, pfn);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक expect_pfn_sgtable(काष्ठा pfn_table *pt,
			      npages_fn_t npages_fn,
			      काष्ठा rnd_state *rnd,
			      स्थिर अक्षर *who,
			      अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक err;

	err = expect_pfn_sg(pt, npages_fn, rnd, who, समयout);
	अगर (err)
		वापस err;

	err = expect_pfn_sg_page_iter(pt, who, समयout);
	अगर (err)
		वापस err;

	err = expect_pfn_sgtiter(pt, who, समयout);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक one(अचिन्हित दीर्घ n,
			अचिन्हित दीर्घ count,
			काष्ठा rnd_state *rnd)
अणु
	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक grow(अचिन्हित दीर्घ n,
			 अचिन्हित दीर्घ count,
			 काष्ठा rnd_state *rnd)
अणु
	वापस n + 1;
पूर्ण

अटल अचिन्हित पूर्णांक shrink(अचिन्हित दीर्घ n,
			   अचिन्हित दीर्घ count,
			   काष्ठा rnd_state *rnd)
अणु
	वापस count - n;
पूर्ण

अटल अचिन्हित पूर्णांक अक्रमom(अचिन्हित दीर्घ n,
			   अचिन्हित दीर्घ count,
			   काष्ठा rnd_state *rnd)
अणु
	वापस 1 + (pअक्रमom_u32_state(rnd) % 1024);
पूर्ण

अटल अचिन्हित पूर्णांक अक्रमom_page_size_pages(अचिन्हित दीर्घ n,
					   अचिन्हित दीर्घ count,
					   काष्ठा rnd_state *rnd)
अणु
	/* 4K, 64K, 2M */
	अटल अचिन्हित पूर्णांक page_count[] = अणु
		BIT(12) >> PAGE_SHIFT,
		BIT(16) >> PAGE_SHIFT,
		BIT(21) >> PAGE_SHIFT,
	पूर्ण;

	वापस page_count[(pअक्रमom_u32_state(rnd) % 3)];
पूर्ण

अटल अंतरभूत bool page_contiguous(काष्ठा page *first,
				   काष्ठा page *last,
				   अचिन्हित दीर्घ npages)
अणु
	वापस first + npages == last;
पूर्ण

अटल पूर्णांक alloc_table(काष्ठा pfn_table *pt,
		       अचिन्हित दीर्घ count, अचिन्हित दीर्घ max,
		       npages_fn_t npages_fn,
		       काष्ठा rnd_state *rnd,
		       पूर्णांक alloc_error)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित दीर्घ n, pfn;

	अगर (sg_alloc_table(&pt->st, max,
			   GFP_KERNEL | __GFP_NORETRY | __GFP_NOWARN))
		वापस alloc_error;

	/* count should be less than 20 to prevent overflowing sg->length */
	GEM_BUG_ON(overflows_type(count * PAGE_SIZE, sg->length));

	/* Conकाष्ठा a table where each scatterlist contains dअगरferent number
	 * of entries. The idea is to check that we can iterate the inभागidual
	 * pages from inside the coalesced lists.
	 */
	pt->start = PFN_BIAS;
	pfn = pt->start;
	sg = pt->st.sgl;
	क्रम (n = 0; n < count; n++) अणु
		अचिन्हित दीर्घ npages = npages_fn(n, count, rnd);

		/* Nobody expects the Sparse Memmap! */
		अगर (!page_contiguous(pfn_to_page(pfn),
				     pfn_to_page(pfn + npages),
				     npages)) अणु
			sg_मुक्त_table(&pt->st);
			वापस -ENOSPC;
		पूर्ण

		अगर (n)
			sg = sg_next(sg);
		sg_set_page(sg, pfn_to_page(pfn), npages * PAGE_SIZE, 0);

		GEM_BUG_ON(page_to_pfn(sg_page(sg)) != pfn);
		GEM_BUG_ON(sg->length != npages * PAGE_SIZE);
		GEM_BUG_ON(sg->offset != 0);

		pfn += npages;
	पूर्ण
	sg_mark_end(sg);
	pt->st.nents = n;
	pt->end = pfn;

	वापस 0;
पूर्ण

अटल स्थिर npages_fn_t npages_funcs[] = अणु
	one,
	grow,
	shrink,
	अक्रमom,
	अक्रमom_page_size_pages,
	शून्य,
पूर्ण;

अटल पूर्णांक igt_sg_alloc(व्योम *ignored)
अणु
	IGT_TIMEOUT(end_समय);
	स्थिर अचिन्हित दीर्घ max_order = 20; /* approximating a 4GiB object */
	काष्ठा rnd_state prng;
	अचिन्हित दीर्घ prime;
	पूर्णांक alloc_error = -ENOMEM;

	क्रम_each_prime_number(prime, max_order) अणु
		अचिन्हित दीर्घ size = BIT(prime);
		पूर्णांक offset;

		क्रम (offset = -1; offset <= 1; offset++) अणु
			अचिन्हित दीर्घ sz = size + offset;
			स्थिर npages_fn_t *npages;
			काष्ठा pfn_table pt;
			पूर्णांक err;

			क्रम (npages = npages_funcs; *npages; npages++) अणु
				pअक्रमom_seed_state(&prng,
						   i915_selftest.अक्रमom_seed);
				err = alloc_table(&pt, sz, sz, *npages, &prng,
						  alloc_error);
				अगर (err == -ENOSPC)
					अवरोध;
				अगर (err)
					वापस err;

				pअक्रमom_seed_state(&prng,
						   i915_selftest.अक्रमom_seed);
				err = expect_pfn_sgtable(&pt, *npages, &prng,
							 "sg_alloc_table",
							 end_समय);
				sg_मुक्त_table(&pt.st);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण

		/* Test at least one continuation beक्रमe accepting oom */
		अगर (size > SG_MAX_SINGLE_ALLOC)
			alloc_error = -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_sg_trim(व्योम *ignored)
अणु
	IGT_TIMEOUT(end_समय);
	स्थिर अचिन्हित दीर्घ max = PAGE_SIZE; /* not prime! */
	काष्ठा pfn_table pt;
	अचिन्हित दीर्घ prime;
	पूर्णांक alloc_error = -ENOMEM;

	क्रम_each_prime_number(prime, max) अणु
		स्थिर npages_fn_t *npages;
		पूर्णांक err;

		क्रम (npages = npages_funcs; *npages; npages++) अणु
			काष्ठा rnd_state prng;

			pअक्रमom_seed_state(&prng, i915_selftest.अक्रमom_seed);
			err = alloc_table(&pt, prime, max, *npages, &prng,
					  alloc_error);
			अगर (err == -ENOSPC)
				अवरोध;
			अगर (err)
				वापस err;

			अगर (i915_sg_trim(&pt.st)) अणु
				अगर (pt.st.orig_nents != prime ||
				    pt.st.nents != prime) अणु
					pr_err("i915_sg_trim failed (nents %u, orig_nents %u), expected %lu\n",
					       pt.st.nents, pt.st.orig_nents, prime);
					err = -EINVAL;
				पूर्ण अन्यथा अणु
					pअक्रमom_seed_state(&prng,
							   i915_selftest.अक्रमom_seed);
					err = expect_pfn_sgtable(&pt,
								 *npages, &prng,
								 "i915_sg_trim",
								 end_समय);
				पूर्ण
			पूर्ण
			sg_मुक्त_table(&pt.st);
			अगर (err)
				वापस err;
		पूर्ण

		/* Test at least one continuation beक्रमe accepting oom */
		अगर (prime > SG_MAX_SINGLE_ALLOC)
			alloc_error = -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक scatterlist_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_sg_alloc),
		SUBTEST(igt_sg_trim),
	पूर्ण;

	वापस i915_subtests(tests, शून्य);
पूर्ण
