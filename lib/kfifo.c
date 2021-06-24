<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A generic kernel FIFO implementation
 *
 * Copyright (C) 2009/2010 Stefani Seibold <stefani@seibold.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/log2.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kfअगरo.h>

/*
 * पूर्णांकernal helper to calculate the unused elements in a fअगरo
 */
अटल अंतरभूत अचिन्हित पूर्णांक kfअगरo_unused(काष्ठा __kfअगरo *fअगरo)
अणु
	वापस (fअगरo->mask + 1) - (fअगरo->in - fअगरo->out);
पूर्ण

पूर्णांक __kfअगरo_alloc(काष्ठा __kfअगरo *fअगरo, अचिन्हित पूर्णांक size,
		माप_प्रकार esize, gfp_t gfp_mask)
अणु
	/*
	 * round up to the next घातer of 2, since our 'let the indices
	 * wrap' technique works only in this हाल.
	 */
	size = roundup_घात_of_two(size);

	fअगरo->in = 0;
	fअगरo->out = 0;
	fअगरo->esize = esize;

	अगर (size < 2) अणु
		fअगरo->data = शून्य;
		fअगरo->mask = 0;
		वापस -EINVAL;
	पूर्ण

	fअगरo->data = kदो_स्मृति_array(esize, size, gfp_mask);

	अगर (!fअगरo->data) अणु
		fअगरo->mask = 0;
		वापस -ENOMEM;
	पूर्ण
	fअगरo->mask = size - 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_alloc);

व्योम __kfअगरo_मुक्त(काष्ठा __kfअगरo *fअगरo)
अणु
	kमुक्त(fअगरo->data);
	fअगरo->in = 0;
	fअगरo->out = 0;
	fअगरo->esize = 0;
	fअगरo->data = शून्य;
	fअगरo->mask = 0;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_मुक्त);

पूर्णांक __kfअगरo_init(काष्ठा __kfअगरo *fअगरo, व्योम *buffer,
		अचिन्हित पूर्णांक size, माप_प्रकार esize)
अणु
	size /= esize;

	अगर (!is_घातer_of_2(size))
		size = roundकरोwn_घात_of_two(size);

	fअगरo->in = 0;
	fअगरo->out = 0;
	fअगरo->esize = esize;
	fअगरo->data = buffer;

	अगर (size < 2) अणु
		fअगरo->mask = 0;
		वापस -EINVAL;
	पूर्ण
	fअगरo->mask = size - 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_init);

अटल व्योम kfअगरo_copy_in(काष्ठा __kfअगरo *fअगरo, स्थिर व्योम *src,
		अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off)
अणु
	अचिन्हित पूर्णांक size = fअगरo->mask + 1;
	अचिन्हित पूर्णांक esize = fअगरo->esize;
	अचिन्हित पूर्णांक l;

	off &= fअगरo->mask;
	अगर (esize != 1) अणु
		off *= esize;
		size *= esize;
		len *= esize;
	पूर्ण
	l = min(len, size - off);

	स_नकल(fअगरo->data + off, src, l);
	स_नकल(fअगरo->data, src + l, len - l);
	/*
	 * make sure that the data in the fअगरo is up to date beक्रमe
	 * incrementing the fअगरo->in index counter
	 */
	smp_wmb();
पूर्ण

अचिन्हित पूर्णांक __kfअगरo_in(काष्ठा __kfअगरo *fअगरo,
		स्थिर व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक l;

	l = kfअगरo_unused(fअगरo);
	अगर (len > l)
		len = l;

	kfअगरo_copy_in(fअगरo, buf, len, fअगरo->in);
	fअगरo->in += len;
	वापस len;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_in);

अटल व्योम kfअगरo_copy_out(काष्ठा __kfअगरo *fअगरo, व्योम *dst,
		अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off)
अणु
	अचिन्हित पूर्णांक size = fअगरo->mask + 1;
	अचिन्हित पूर्णांक esize = fअगरo->esize;
	अचिन्हित पूर्णांक l;

	off &= fअगरo->mask;
	अगर (esize != 1) अणु
		off *= esize;
		size *= esize;
		len *= esize;
	पूर्ण
	l = min(len, size - off);

	स_नकल(dst, fअगरo->data + off, l);
	स_नकल(dst + l, fअगरo->data, len - l);
	/*
	 * make sure that the data is copied beक्रमe
	 * incrementing the fअगरo->out index counter
	 */
	smp_wmb();
पूर्ण

अचिन्हित पूर्णांक __kfअगरo_out_peek(काष्ठा __kfअगरo *fअगरo,
		व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक l;

	l = fअगरo->in - fअगरo->out;
	अगर (len > l)
		len = l;

	kfअगरo_copy_out(fअगरo, buf, len, fअगरo->out);
	वापस len;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_out_peek);

अचिन्हित पूर्णांक __kfअगरo_out(काष्ठा __kfअगरo *fअगरo,
		व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	len = __kfअगरo_out_peek(fअगरo, buf, len);
	fअगरo->out += len;
	वापस len;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_out);

अटल अचिन्हित दीर्घ kfअगरo_copy_from_user(काष्ठा __kfअगरo *fअगरo,
	स्थिर व्योम __user *from, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off,
	अचिन्हित पूर्णांक *copied)
अणु
	अचिन्हित पूर्णांक size = fअगरo->mask + 1;
	अचिन्हित पूर्णांक esize = fअगरo->esize;
	अचिन्हित पूर्णांक l;
	अचिन्हित दीर्घ ret;

	off &= fअगरo->mask;
	अगर (esize != 1) अणु
		off *= esize;
		size *= esize;
		len *= esize;
	पूर्ण
	l = min(len, size - off);

	ret = copy_from_user(fअगरo->data + off, from, l);
	अगर (unlikely(ret))
		ret = DIV_ROUND_UP(ret + len - l, esize);
	अन्यथा अणु
		ret = copy_from_user(fअगरo->data, from + l, len - l);
		अगर (unlikely(ret))
			ret = DIV_ROUND_UP(ret, esize);
	पूर्ण
	/*
	 * make sure that the data in the fअगरo is up to date beक्रमe
	 * incrementing the fअगरo->in index counter
	 */
	smp_wmb();
	*copied = len - ret * esize;
	/* वापस the number of elements which are not copied */
	वापस ret;
पूर्ण

पूर्णांक __kfअगरo_from_user(काष्ठा __kfअगरo *fअगरo, स्थिर व्योम __user *from,
		अचिन्हित दीर्घ len, अचिन्हित पूर्णांक *copied)
अणु
	अचिन्हित पूर्णांक l;
	अचिन्हित दीर्घ ret;
	अचिन्हित पूर्णांक esize = fअगरo->esize;
	पूर्णांक err;

	अगर (esize != 1)
		len /= esize;

	l = kfअगरo_unused(fअगरo);
	अगर (len > l)
		len = l;

	ret = kfअगरo_copy_from_user(fअगरo, from, len, fअगरo->in, copied);
	अगर (unlikely(ret)) अणु
		len -= ret;
		err = -EFAULT;
	पूर्ण अन्यथा
		err = 0;
	fअगरo->in += len;
	वापस err;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_from_user);

अटल अचिन्हित दीर्घ kfअगरo_copy_to_user(काष्ठा __kfअगरo *fअगरo, व्योम __user *to,
		अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक *copied)
अणु
	अचिन्हित पूर्णांक l;
	अचिन्हित दीर्घ ret;
	अचिन्हित पूर्णांक size = fअगरo->mask + 1;
	अचिन्हित पूर्णांक esize = fअगरo->esize;

	off &= fअगरo->mask;
	अगर (esize != 1) अणु
		off *= esize;
		size *= esize;
		len *= esize;
	पूर्ण
	l = min(len, size - off);

	ret = copy_to_user(to, fअगरo->data + off, l);
	अगर (unlikely(ret))
		ret = DIV_ROUND_UP(ret + len - l, esize);
	अन्यथा अणु
		ret = copy_to_user(to + l, fअगरo->data, len - l);
		अगर (unlikely(ret))
			ret = DIV_ROUND_UP(ret, esize);
	पूर्ण
	/*
	 * make sure that the data is copied beक्रमe
	 * incrementing the fअगरo->out index counter
	 */
	smp_wmb();
	*copied = len - ret * esize;
	/* वापस the number of elements which are not copied */
	वापस ret;
पूर्ण

पूर्णांक __kfअगरo_to_user(काष्ठा __kfअगरo *fअगरo, व्योम __user *to,
		अचिन्हित दीर्घ len, अचिन्हित पूर्णांक *copied)
अणु
	अचिन्हित पूर्णांक l;
	अचिन्हित दीर्घ ret;
	अचिन्हित पूर्णांक esize = fअगरo->esize;
	पूर्णांक err;

	अगर (esize != 1)
		len /= esize;

	l = fअगरo->in - fअगरo->out;
	अगर (len > l)
		len = l;
	ret = kfअगरo_copy_to_user(fअगरo, to, len, fअगरo->out, copied);
	अगर (unlikely(ret)) अणु
		len -= ret;
		err = -EFAULT;
	पूर्ण अन्यथा
		err = 0;
	fअगरo->out += len;
	वापस err;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_to_user);

अटल पूर्णांक setup_sgl_buf(काष्ठा scatterlist *sgl, व्योम *buf,
		पूर्णांक nents, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक n;
	अचिन्हित पूर्णांक l;
	अचिन्हित पूर्णांक off;
	काष्ठा page *page;

	अगर (!nents)
		वापस 0;

	अगर (!len)
		वापस 0;

	n = 0;
	page = virt_to_page(buf);
	off = offset_in_page(buf);
	l = 0;

	जबतक (len >= l + PAGE_SIZE - off) अणु
		काष्ठा page *npage;

		l += PAGE_SIZE;
		buf += PAGE_SIZE;
		npage = virt_to_page(buf);
		अगर (page_to_phys(page) != page_to_phys(npage) - l) अणु
			sg_set_page(sgl, page, l - off, off);
			sgl = sg_next(sgl);
			अगर (++n == nents || sgl == शून्य)
				वापस n;
			page = npage;
			len -= l - off;
			l = off = 0;
		पूर्ण
	पूर्ण
	sg_set_page(sgl, page, len, off);
	वापस n + 1;
पूर्ण

अटल अचिन्हित पूर्णांक setup_sgl(काष्ठा __kfअगरo *fअगरo, काष्ठा scatterlist *sgl,
		पूर्णांक nents, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off)
अणु
	अचिन्हित पूर्णांक size = fअगरo->mask + 1;
	अचिन्हित पूर्णांक esize = fअगरo->esize;
	अचिन्हित पूर्णांक l;
	अचिन्हित पूर्णांक n;

	off &= fअगरo->mask;
	अगर (esize != 1) अणु
		off *= esize;
		size *= esize;
		len *= esize;
	पूर्ण
	l = min(len, size - off);

	n = setup_sgl_buf(sgl, fअगरo->data + off, nents, l);
	n += setup_sgl_buf(sgl + n, fअगरo->data, nents - n, len - l);

	वापस n;
पूर्ण

अचिन्हित पूर्णांक __kfअगरo_dma_in_prepare(काष्ठा __kfअगरo *fअगरo,
		काष्ठा scatterlist *sgl, पूर्णांक nents, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक l;

	l = kfअगरo_unused(fअगरo);
	अगर (len > l)
		len = l;

	वापस setup_sgl(fअगरo, sgl, nents, len, fअगरo->in);
पूर्ण
EXPORT_SYMBOL(__kfअगरo_dma_in_prepare);

अचिन्हित पूर्णांक __kfअगरo_dma_out_prepare(काष्ठा __kfअगरo *fअगरo,
		काष्ठा scatterlist *sgl, पूर्णांक nents, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक l;

	l = fअगरo->in - fअगरo->out;
	अगर (len > l)
		len = l;

	वापस setup_sgl(fअगरo, sgl, nents, len, fअगरo->out);
पूर्ण
EXPORT_SYMBOL(__kfअगरo_dma_out_prepare);

अचिन्हित पूर्णांक __kfअगरo_max_r(अचिन्हित पूर्णांक len, माप_प्रकार recsize)
अणु
	अचिन्हित पूर्णांक max = (1 << (recsize << 3)) - 1;

	अगर (len > max)
		वापस max;
	वापस len;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_max_r);

#घोषणा	__KFIFO_PEEK(data, out, mask) \
	((data)[(out) & (mask)])
/*
 * __kfअगरo_peek_n पूर्णांकernal helper function क्रम determinate the length of
 * the next record in the fअगरo
 */
अटल अचिन्हित पूर्णांक __kfअगरo_peek_n(काष्ठा __kfअगरo *fअगरo, माप_प्रकार recsize)
अणु
	अचिन्हित पूर्णांक l;
	अचिन्हित पूर्णांक mask = fअगरo->mask;
	अचिन्हित अक्षर *data = fअगरo->data;

	l = __KFIFO_PEEK(data, fअगरo->out, mask);

	अगर (--recsize)
		l |= __KFIFO_PEEK(data, fअगरo->out + 1, mask) << 8;

	वापस l;
पूर्ण

#घोषणा	__KFIFO_POKE(data, in, mask, val) \
	( \
	(data)[(in) & (mask)] = (अचिन्हित अक्षर)(val) \
	)

/*
 * __kfअगरo_poke_n पूर्णांकernal helper function क्रम storeing the length of
 * the record पूर्णांकo the fअगरo
 */
अटल व्योम __kfअगरo_poke_n(काष्ठा __kfअगरo *fअगरo, अचिन्हित पूर्णांक n, माप_प्रकार recsize)
अणु
	अचिन्हित पूर्णांक mask = fअगरo->mask;
	अचिन्हित अक्षर *data = fअगरo->data;

	__KFIFO_POKE(data, fअगरo->in, mask, n);

	अगर (recsize > 1)
		__KFIFO_POKE(data, fअगरo->in + 1, mask, n >> 8);
पूर्ण

अचिन्हित पूर्णांक __kfअगरo_len_r(काष्ठा __kfअगरo *fअगरo, माप_प्रकार recsize)
अणु
	वापस __kfअगरo_peek_n(fअगरo, recsize);
पूर्ण
EXPORT_SYMBOL(__kfअगरo_len_r);

अचिन्हित पूर्णांक __kfअगरo_in_r(काष्ठा __kfअगरo *fअगरo, स्थिर व्योम *buf,
		अचिन्हित पूर्णांक len, माप_प्रकार recsize)
अणु
	अगर (len + recsize > kfअगरo_unused(fअगरo))
		वापस 0;

	__kfअगरo_poke_n(fअगरo, len, recsize);

	kfअगरo_copy_in(fअगरo, buf, len, fअगरo->in + recsize);
	fअगरo->in += len + recsize;
	वापस len;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_in_r);

अटल अचिन्हित पूर्णांक kfअगरo_out_copy_r(काष्ठा __kfअगरo *fअगरo,
	व्योम *buf, अचिन्हित पूर्णांक len, माप_प्रकार recsize, अचिन्हित पूर्णांक *n)
अणु
	*n = __kfअगरo_peek_n(fअगरo, recsize);

	अगर (len > *n)
		len = *n;

	kfअगरo_copy_out(fअगरo, buf, len, fअगरo->out + recsize);
	वापस len;
पूर्ण

अचिन्हित पूर्णांक __kfअगरo_out_peek_r(काष्ठा __kfअगरo *fअगरo, व्योम *buf,
		अचिन्हित पूर्णांक len, माप_प्रकार recsize)
अणु
	अचिन्हित पूर्णांक n;

	अगर (fअगरo->in == fअगरo->out)
		वापस 0;

	वापस kfअगरo_out_copy_r(fअगरo, buf, len, recsize, &n);
पूर्ण
EXPORT_SYMBOL(__kfअगरo_out_peek_r);

अचिन्हित पूर्णांक __kfअगरo_out_r(काष्ठा __kfअगरo *fअगरo, व्योम *buf,
		अचिन्हित पूर्णांक len, माप_प्रकार recsize)
अणु
	अचिन्हित पूर्णांक n;

	अगर (fअगरo->in == fअगरo->out)
		वापस 0;

	len = kfअगरo_out_copy_r(fअगरo, buf, len, recsize, &n);
	fअगरo->out += n + recsize;
	वापस len;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_out_r);

व्योम __kfअगरo_skip_r(काष्ठा __kfअगरo *fअगरo, माप_प्रकार recsize)
अणु
	अचिन्हित पूर्णांक n;

	n = __kfअगरo_peek_n(fअगरo, recsize);
	fअगरo->out += n + recsize;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_skip_r);

पूर्णांक __kfअगरo_from_user_r(काष्ठा __kfअगरo *fअगरo, स्थिर व्योम __user *from,
	अचिन्हित दीर्घ len, अचिन्हित पूर्णांक *copied, माप_प्रकार recsize)
अणु
	अचिन्हित दीर्घ ret;

	len = __kfअगरo_max_r(len, recsize);

	अगर (len + recsize > kfअगरo_unused(fअगरo)) अणु
		*copied = 0;
		वापस 0;
	पूर्ण

	__kfअगरo_poke_n(fअगरo, len, recsize);

	ret = kfअगरo_copy_from_user(fअगरo, from, len, fअगरo->in + recsize, copied);
	अगर (unlikely(ret)) अणु
		*copied = 0;
		वापस -EFAULT;
	पूर्ण
	fअगरo->in += len + recsize;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_from_user_r);

पूर्णांक __kfअगरo_to_user_r(काष्ठा __kfअगरo *fअगरo, व्योम __user *to,
	अचिन्हित दीर्घ len, अचिन्हित पूर्णांक *copied, माप_प्रकार recsize)
अणु
	अचिन्हित दीर्घ ret;
	अचिन्हित पूर्णांक n;

	अगर (fअगरo->in == fअगरo->out) अणु
		*copied = 0;
		वापस 0;
	पूर्ण

	n = __kfअगरo_peek_n(fअगरo, recsize);
	अगर (len > n)
		len = n;

	ret = kfअगरo_copy_to_user(fअगरo, to, len, fअगरo->out + recsize, copied);
	अगर (unlikely(ret)) अणु
		*copied = 0;
		वापस -EFAULT;
	पूर्ण
	fअगरo->out += n + recsize;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_to_user_r);

अचिन्हित पूर्णांक __kfअगरo_dma_in_prepare_r(काष्ठा __kfअगरo *fअगरo,
	काष्ठा scatterlist *sgl, पूर्णांक nents, अचिन्हित पूर्णांक len, माप_प्रकार recsize)
अणु
	BUG_ON(!nents);

	len = __kfअगरo_max_r(len, recsize);

	अगर (len + recsize > kfअगरo_unused(fअगरo))
		वापस 0;

	वापस setup_sgl(fअगरo, sgl, nents, len, fअगरo->in + recsize);
पूर्ण
EXPORT_SYMBOL(__kfअगरo_dma_in_prepare_r);

व्योम __kfअगरo_dma_in_finish_r(काष्ठा __kfअगरo *fअगरo,
	अचिन्हित पूर्णांक len, माप_प्रकार recsize)
अणु
	len = __kfअगरo_max_r(len, recsize);
	__kfअगरo_poke_n(fअगरo, len, recsize);
	fअगरo->in += len + recsize;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_dma_in_finish_r);

अचिन्हित पूर्णांक __kfअगरo_dma_out_prepare_r(काष्ठा __kfअगरo *fअगरo,
	काष्ठा scatterlist *sgl, पूर्णांक nents, अचिन्हित पूर्णांक len, माप_प्रकार recsize)
अणु
	BUG_ON(!nents);

	len = __kfअगरo_max_r(len, recsize);

	अगर (len + recsize > fअगरo->in - fअगरo->out)
		वापस 0;

	वापस setup_sgl(fअगरo, sgl, nents, len, fअगरo->out + recsize);
पूर्ण
EXPORT_SYMBOL(__kfअगरo_dma_out_prepare_r);

व्योम __kfअगरo_dma_out_finish_r(काष्ठा __kfअगरo *fअगरo, माप_प्रकार recsize)
अणु
	अचिन्हित पूर्णांक len;

	len = __kfअगरo_peek_n(fअगरo, recsize);
	fअगरo->out += len + recsize;
पूर्ण
EXPORT_SYMBOL(__kfअगरo_dma_out_finish_r);
