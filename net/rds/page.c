<शैली गुरु>
/*
 * Copyright (c) 2006 Oracle.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/highस्मृति.स>
#समावेश <linux/gfp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/export.h>

#समावेश "rds.h"

काष्ठा rds_page_reमुख्यder अणु
	काष्ठा page	*r_page;
	अचिन्हित दीर्घ	r_offset;
पूर्ण;

अटल
DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा rds_page_reमुख्यder, rds_page_reमुख्यders);

/**
 * rds_page_reमुख्यder_alloc - build up regions of a message.
 *
 * @scat: Scatter list क्रम message
 * @bytes: the number of bytes needed.
 * @gfp: the रुकोing behaviour of the allocation
 *
 * @gfp is always ored with __GFP_HIGHMEM.  Callers must be prepared to
 * kmap the pages, etc.
 *
 * If @bytes is at least a full page then this just वापसs a page from
 * alloc_page().
 *
 * If @bytes is a partial page then this stores the unused region of the
 * page in a per-cpu काष्ठाure.  Future partial-page allocations may be
 * satisfied from that cached region.  This lets us waste less memory on
 * small allocations with minimal complनिकासy.  It works because the transmit
 * path passes पढ़ो-only page regions करोwn to devices.  They hold a page
 * reference until they are करोne with the region.
 */
पूर्णांक rds_page_reमुख्यder_alloc(काष्ठा scatterlist *scat, अचिन्हित दीर्घ bytes,
			     gfp_t gfp)
अणु
	काष्ठा rds_page_reमुख्यder *rem;
	अचिन्हित दीर्घ flags;
	काष्ठा page *page;
	पूर्णांक ret;

	gfp |= __GFP_HIGHMEM;

	/* jump straight to allocation अगर we're trying क्रम a huge page */
	अगर (bytes >= PAGE_SIZE) अणु
		page = alloc_page(gfp);
		अगर (!page) अणु
			ret = -ENOMEM;
		पूर्ण अन्यथा अणु
			sg_set_page(scat, page, PAGE_SIZE, 0);
			ret = 0;
		पूर्ण
		जाओ out;
	पूर्ण

	rem = &per_cpu(rds_page_reमुख्यders, get_cpu());
	local_irq_save(flags);

	जबतक (1) अणु
		/* aव्योम a tiny region getting stuck by tossing it */
		अगर (rem->r_page && bytes > (PAGE_SIZE - rem->r_offset)) अणु
			rds_stats_inc(s_page_reमुख्यder_miss);
			__मुक्त_page(rem->r_page);
			rem->r_page = शून्य;
		पूर्ण

		/* hand out a fragment from the cached page */
		अगर (rem->r_page && bytes <= (PAGE_SIZE - rem->r_offset)) अणु
			sg_set_page(scat, rem->r_page, bytes, rem->r_offset);
			get_page(sg_page(scat));

			अगर (rem->r_offset != 0)
				rds_stats_inc(s_page_reमुख्यder_hit);

			rem->r_offset += ALIGN(bytes, 8);
			अगर (rem->r_offset >= PAGE_SIZE) अणु
				__मुक्त_page(rem->r_page);
				rem->r_page = शून्य;
			पूर्ण
			ret = 0;
			अवरोध;
		पूर्ण

		/* alloc अगर there is nothing क्रम us to use */
		local_irq_restore(flags);
		put_cpu();

		page = alloc_page(gfp);

		rem = &per_cpu(rds_page_reमुख्यders, get_cpu());
		local_irq_save(flags);

		अगर (!page) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		/* did someone race to fill the reमुख्यder beक्रमe us? */
		अगर (rem->r_page) अणु
			__मुक्त_page(page);
			जारी;
		पूर्ण

		/* otherwise install our page and loop around to alloc */
		rem->r_page = page;
		rem->r_offset = 0;
	पूर्ण

	local_irq_restore(flags);
	put_cpu();
out:
	rdsdebug("bytes %lu ret %d %p %u %u\n", bytes, ret,
		 ret ? शून्य : sg_page(scat), ret ? 0 : scat->offset,
		 ret ? 0 : scat->length);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rds_page_reमुख्यder_alloc);

व्योम rds_page_निकास(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा rds_page_reमुख्यder *rem;

		rem = &per_cpu(rds_page_reमुख्यders, cpu);
		rdsdebug("cpu %u\n", cpu);

		अगर (rem->r_page)
			__मुक्त_page(rem->r_page);
		rem->r_page = शून्य;
	पूर्ण
पूर्ण
