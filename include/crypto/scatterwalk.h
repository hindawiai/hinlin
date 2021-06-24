<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Cryptographic scatter and gather helpers.
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2002 Adam J. Richter <adam@yggdrasil.com>
 * Copyright (c) 2004 Jean-Luc Cooke <jlcooke@certainkey.com>
 * Copyright (c) 2007 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#अगर_अघोषित _CRYPTO_SCATTERWALK_H
#घोषणा _CRYPTO_SCATTERWALK_H

#समावेश <crypto/algapi.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/scatterlist.h>

अटल अंतरभूत व्योम scatterwalk_crypto_chain(काष्ठा scatterlist *head,
					    काष्ठा scatterlist *sg, पूर्णांक num)
अणु
	अगर (sg)
		sg_chain(head, num, sg);
	अन्यथा
		sg_mark_end(head);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक scatterwalk_pagelen(काष्ठा scatter_walk *walk)
अणु
	अचिन्हित पूर्णांक len = walk->sg->offset + walk->sg->length - walk->offset;
	अचिन्हित पूर्णांक len_this_page = offset_in_page(~walk->offset) + 1;
	वापस len_this_page > len ? len : len_this_page;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक scatterwalk_clamp(काष्ठा scatter_walk *walk,
					     अचिन्हित पूर्णांक nbytes)
अणु
	अचिन्हित पूर्णांक len_this_page = scatterwalk_pagelen(walk);
	वापस nbytes > len_this_page ? len_this_page : nbytes;
पूर्ण

अटल अंतरभूत व्योम scatterwalk_advance(काष्ठा scatter_walk *walk,
				       अचिन्हित पूर्णांक nbytes)
अणु
	walk->offset += nbytes;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक scatterwalk_aligned(काष्ठा scatter_walk *walk,
					       अचिन्हित पूर्णांक alignmask)
अणु
	वापस !(walk->offset & alignmask);
पूर्ण

अटल अंतरभूत काष्ठा page *scatterwalk_page(काष्ठा scatter_walk *walk)
अणु
	वापस sg_page(walk->sg) + (walk->offset >> PAGE_SHIFT);
पूर्ण

अटल अंतरभूत व्योम scatterwalk_unmap(व्योम *vaddr)
अणु
	kunmap_atomic(vaddr);
पूर्ण

अटल अंतरभूत व्योम scatterwalk_start(काष्ठा scatter_walk *walk,
				     काष्ठा scatterlist *sg)
अणु
	walk->sg = sg;
	walk->offset = sg->offset;
पूर्ण

अटल अंतरभूत व्योम *scatterwalk_map(काष्ठा scatter_walk *walk)
अणु
	वापस kmap_atomic(scatterwalk_page(walk)) +
	       offset_in_page(walk->offset);
पूर्ण

अटल अंतरभूत व्योम scatterwalk_pageकरोne(काष्ठा scatter_walk *walk, पूर्णांक out,
					अचिन्हित पूर्णांक more)
अणु
	अगर (out) अणु
		काष्ठा page *page;

		page = sg_page(walk->sg) + ((walk->offset - 1) >> PAGE_SHIFT);
		/* Test ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE first as
		 * PageSlab cannot be optimised away per se due to
		 * use of अस्थिर poपूर्णांकer.
		 */
		अगर (ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE && !PageSlab(page))
			flush_dcache_page(page);
	पूर्ण

	अगर (more && walk->offset >= walk->sg->offset + walk->sg->length)
		scatterwalk_start(walk, sg_next(walk->sg));
पूर्ण

अटल अंतरभूत व्योम scatterwalk_करोne(काष्ठा scatter_walk *walk, पूर्णांक out,
				    पूर्णांक more)
अणु
	अगर (!more || walk->offset >= walk->sg->offset + walk->sg->length ||
	    !(walk->offset & (PAGE_SIZE - 1)))
		scatterwalk_pageकरोne(walk, out, more);
पूर्ण

व्योम scatterwalk_copychunks(व्योम *buf, काष्ठा scatter_walk *walk,
			    माप_प्रकार nbytes, पूर्णांक out);
व्योम *scatterwalk_map(काष्ठा scatter_walk *walk);

व्योम scatterwalk_map_and_copy(व्योम *buf, काष्ठा scatterlist *sg,
			      अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक nbytes, पूर्णांक out);

काष्ठा scatterlist *scatterwalk_ffwd(काष्ठा scatterlist dst[2],
				     काष्ठा scatterlist *src,
				     अचिन्हित पूर्णांक len);

#पूर्ण_अगर  /* _CRYPTO_SCATTERWALK_H */
