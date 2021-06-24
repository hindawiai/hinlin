<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * Cipher operations.
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 *               2002 Adam J. Richter <adam@yggdrasil.com>
 *               2004 Jean-Luc Cooke <jlcooke@certainkey.com>
 */

#समावेश <crypto/scatterwalk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>

अटल अंतरभूत व्योम स_नकल_dir(व्योम *buf, व्योम *sgdata, माप_प्रकार nbytes, पूर्णांक out)
अणु
	व्योम *src = out ? buf : sgdata;
	व्योम *dst = out ? sgdata : buf;

	स_नकल(dst, src, nbytes);
पूर्ण

व्योम scatterwalk_copychunks(व्योम *buf, काष्ठा scatter_walk *walk,
			    माप_प्रकार nbytes, पूर्णांक out)
अणु
	क्रम (;;) अणु
		अचिन्हित पूर्णांक len_this_page = scatterwalk_pagelen(walk);
		u8 *vaddr;

		अगर (len_this_page > nbytes)
			len_this_page = nbytes;

		अगर (out != 2) अणु
			vaddr = scatterwalk_map(walk);
			स_नकल_dir(buf, vaddr, len_this_page, out);
			scatterwalk_unmap(vaddr);
		पूर्ण

		scatterwalk_advance(walk, len_this_page);

		अगर (nbytes == len_this_page)
			अवरोध;

		buf += len_this_page;
		nbytes -= len_this_page;

		scatterwalk_pageकरोne(walk, out & 1, 1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(scatterwalk_copychunks);

व्योम scatterwalk_map_and_copy(व्योम *buf, काष्ठा scatterlist *sg,
			      अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक nbytes, पूर्णांक out)
अणु
	काष्ठा scatter_walk walk;
	काष्ठा scatterlist पंचांगp[2];

	अगर (!nbytes)
		वापस;

	sg = scatterwalk_ffwd(पंचांगp, sg, start);

	scatterwalk_start(&walk, sg);
	scatterwalk_copychunks(buf, &walk, nbytes, out);
	scatterwalk_करोne(&walk, out, 0);
पूर्ण
EXPORT_SYMBOL_GPL(scatterwalk_map_and_copy);

काष्ठा scatterlist *scatterwalk_ffwd(काष्ठा scatterlist dst[2],
				     काष्ठा scatterlist *src,
				     अचिन्हित पूर्णांक len)
अणु
	क्रम (;;) अणु
		अगर (!len)
			वापस src;

		अगर (src->length > len)
			अवरोध;

		len -= src->length;
		src = sg_next(src);
	पूर्ण

	sg_init_table(dst, 2);
	sg_set_page(dst, sg_page(src), src->length - len, src->offset + len);
	scatterwalk_crypto_chain(dst, sg_next(src), 2);

	वापस dst;
पूर्ण
EXPORT_SYMBOL_GPL(scatterwalk_ffwd);
