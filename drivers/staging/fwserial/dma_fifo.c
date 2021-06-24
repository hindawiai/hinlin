<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * DMA-able FIFO implementation
 *
 * Copyright (C) 2012 Peter Hurley <peter@hurleysoftware.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/bug.h>

#समावेश "dma_fifo.h"

#अगर_घोषित DEBUG_TRACING
#घोषणा df_trace(s, args...) pr_debug(s, ##args)
#अन्यथा
#घोषणा df_trace(s, args...)
#पूर्ण_अगर

#घोषणा FAIL(fअगरo, condition, क्रमmat...) (अणु				\
	fअगरo->corrupt = !!(condition);					\
	WARN(fअगरo->corrupt, क्रमmat);					\
पूर्ण)

/*
 * निजी helper fn to determine अगर check is in खोलो पूर्णांकerval (lo,hi)
 */
अटल bool addr_check(अचिन्हित पूर्णांक check, अचिन्हित पूर्णांक lo, अचिन्हित पूर्णांक hi)
अणु
	वापस check - (lo + 1) < (hi - 1) - lo;
पूर्ण

/**
 * dma_fअगरo_init: initialize the fअगरo to a valid but inoperative state
 * @fअगरo: address of in-place "struct dma_fifo" object
 */
व्योम dma_fअगरo_init(काष्ठा dma_fअगरo *fअगरo)
अणु
	स_रखो(fअगरo, 0, माप(*fअगरo));
	INIT_LIST_HEAD(&fअगरo->pending);
पूर्ण

/**
 * dma_fअगरo_alloc - initialize and allocate dma_fअगरo
 * @fअगरo: address of in-place "struct dma_fifo" object
 * @size: 'apparent' size, in bytes, of fअगरo
 * @align: dma alignment to मुख्यtain (should be at least cpu cache alignment),
 *         must be घातer of 2
 * @tx_limit: maximum # of bytes transmissible per dma (rounded करोwn to
 *            multiple of alignment, but at least align size)
 * @खोलो_limit: maximum # of outstanding dma transactions allowed
 * @gfp_mask: get_मुक्त_pages mask, passed to kदो_स्मृति()
 *
 * The 'apparent' size will be rounded up to next greater aligned size.
 * Returns 0 अगर no error, otherwise an error code
 */
पूर्णांक dma_fअगरo_alloc(काष्ठा dma_fअगरo *fअगरo, पूर्णांक size, अचिन्हित पूर्णांक align,
		   पूर्णांक tx_limit, पूर्णांक खोलो_limit, gfp_t gfp_mask)
अणु
	पूर्णांक capacity;

	अगर (!is_घातer_of_2(align) || size < 0)
		वापस -EINVAL;

	size = round_up(size, align);
	capacity = size + align * खोलो_limit + align * DMA_FIFO_GUARD;
	fअगरo->data = kदो_स्मृति(capacity, gfp_mask);
	अगर (!fअगरo->data)
		वापस -ENOMEM;

	fअगरo->in = 0;
	fअगरo->out = 0;
	fअगरo->करोne = 0;
	fअगरo->size = size;
	fअगरo->avail = size;
	fअगरo->align = align;
	fअगरo->tx_limit = max_t(पूर्णांक, round_करोwn(tx_limit, align), align);
	fअगरo->खोलो = 0;
	fअगरo->खोलो_limit = खोलो_limit;
	fअगरo->guard = size + align * खोलो_limit;
	fअगरo->capacity = capacity;
	fअगरo->corrupt = 0;

	वापस 0;
पूर्ण

/**
 * dma_fअगरo_मुक्त - मुक्तs the fअगरo
 * @fअगरo: address of in-place "struct dma_fifo" to मुक्त
 *
 * Also reinits the fअगरo to a valid but inoperative state. This
 * allows the fअगरo to be reused with a dअगरferent target requiring
 * dअगरferent fअगरo parameters.
 */
व्योम dma_fअगरo_मुक्त(काष्ठा dma_fअगरo *fअगरo)
अणु
	काष्ठा dma_pending *pending, *next;

	अगर (!fअगरo->data)
		वापस;

	list_क्रम_each_entry_safe(pending, next, &fअगरo->pending, link)
		list_del_init(&pending->link);
	kमुक्त(fअगरo->data);
	fअगरo->data = शून्य;
पूर्ण

/**
 * dma_fअगरo_reset - dumps the fअगरo contents and reinits क्रम reuse
 * @fअगरo: address of in-place "struct dma_fifo" to reset
 */
व्योम dma_fअगरo_reset(काष्ठा dma_fअगरo *fअगरo)
अणु
	काष्ठा dma_pending *pending, *next;

	अगर (!fअगरo->data)
		वापस;

	list_क्रम_each_entry_safe(pending, next, &fअगरo->pending, link)
		list_del_init(&pending->link);
	fअगरo->in = 0;
	fअगरo->out = 0;
	fअगरo->करोne = 0;
	fअगरo->avail = fअगरo->size;
	fअगरo->खोलो = 0;
	fअगरo->corrupt = 0;
पूर्ण

/**
 * dma_fअगरo_in - copies data पूर्णांकo the fअगरo
 * @fअगरo: address of in-place "struct dma_fifo" to ग_लिखो to
 * @src: buffer to copy from
 * @n: # of bytes to copy
 *
 * Returns the # of bytes actually copied, which can be less than requested अगर
 * the fअगरo becomes full. If < 0, वापस is error code.
 */
पूर्णांक dma_fअगरo_in(काष्ठा dma_fअगरo *fअगरo, स्थिर व्योम *src, पूर्णांक n)
अणु
	पूर्णांक ofs, l;

	अगर (!fअगरo->data)
		वापस -ENOENT;
	अगर (fअगरo->corrupt)
		वापस -ENXIO;

	अगर (n > fअगरo->avail)
		n = fअगरo->avail;
	अगर (n <= 0)
		वापस 0;

	ofs = fअगरo->in % fअगरo->capacity;
	l = min(n, fअगरo->capacity - ofs);
	स_नकल(fअगरo->data + ofs, src, l);
	स_नकल(fअगरo->data, src + l, n - l);

	अगर (FAIL(fअगरo, addr_check(fअगरo->करोne, fअगरo->in, fअगरo->in + n) ||
		 fअगरo->avail < n,
		 "fifo corrupt: in:%u out:%u done:%u n:%d avail:%d",
		 fअगरo->in, fअगरo->out, fअगरo->करोne, n, fअगरo->avail))
		वापस -ENXIO;

	fअगरo->in += n;
	fअगरo->avail -= n;

	df_trace("in:%u out:%u done:%u n:%d avail:%d", fअगरo->in, fअगरo->out,
		 fअगरo->करोne, n, fअगरo->avail);

	वापस n;
पूर्ण

/**
 * dma_fअगरo_out_pend - माला_लो address/len of next avail पढ़ो and marks as pended
 * @fअगरo: address of in-place "struct dma_fifo" to पढ़ो from
 * @pended: address of काष्ठाure to fill with पढ़ो address/len
 *          The data/len fields will be शून्य/0 अगर no dma is pended.
 *
 * Returns the # of used bytes reमुख्यing in fअगरo (ie, अगर > 0, more data
 * reमुख्यs in the fअगरo that was not pended). If < 0, वापस is error code.
 */
पूर्णांक dma_fअगरo_out_pend(काष्ठा dma_fअगरo *fअगरo, काष्ठा dma_pending *pended)
अणु
	अचिन्हित पूर्णांक len, n, ofs, l, limit;

	अगर (!fअगरo->data)
		वापस -ENOENT;
	अगर (fअगरo->corrupt)
		वापस -ENXIO;

	pended->len = 0;
	pended->data = शून्य;
	pended->out = fअगरo->out;

	len = fअगरo->in - fअगरo->out;
	अगर (!len)
		वापस -ENODATA;
	अगर (fअगरo->खोलो == fअगरo->खोलो_limit)
		वापस -EAGAIN;

	n = len;
	ofs = fअगरo->out % fअगरo->capacity;
	l = fअगरo->capacity - ofs;
	limit = min_t(अचिन्हित पूर्णांक, l, fअगरo->tx_limit);
	अगर (n > limit) अणु
		n = limit;
		fअगरo->out += limit;
	पूर्ण अन्यथा अगर (ofs + n > fअगरo->guard) अणु
		fअगरo->out += l;
		fअगरo->in = fअगरo->out;
	पूर्ण अन्यथा अणु
		fअगरo->out += round_up(n, fअगरo->align);
		fअगरo->in = fअगरo->out;
	पूर्ण

	df_trace("in: %u out: %u done: %u n: %d len: %u avail: %d", fअगरo->in,
		 fअगरo->out, fअगरo->करोne, n, len, fअगरo->avail);

	pended->len = n;
	pended->data = fअगरo->data + ofs;
	pended->next = fअगरo->out;
	list_add_tail(&pended->link, &fअगरo->pending);
	++fअगरo->खोलो;

	अगर (FAIL(fअगरo, fअगरo->खोलो > fअगरo->खोलो_limit,
		 "past open limit:%d (limit:%d)",
		 fअगरo->खोलो, fअगरo->खोलो_limit))
		वापस -ENXIO;
	अगर (FAIL(fअगरo, fअगरo->out & (fअगरo->align - 1),
		 "fifo out unaligned:%u (align:%u)",
		 fअगरo->out, fअगरo->align))
		वापस -ENXIO;

	वापस len - n;
पूर्ण

/**
 * dma_fअगरo_out_complete - marks pended dma as completed
 * @fअगरo: address of in-place "struct dma_fifo" which was पढ़ो from
 * @complete: address of काष्ठाure क्रम previously pended dma to mark completed
 */
पूर्णांक dma_fअगरo_out_complete(काष्ठा dma_fअगरo *fअगरo, काष्ठा dma_pending *complete)
अणु
	काष्ठा dma_pending *pending, *next, *पंचांगp;

	अगर (!fअगरo->data)
		वापस -ENOENT;
	अगर (fअगरo->corrupt)
		वापस -ENXIO;
	अगर (list_empty(&fअगरo->pending) && fअगरo->खोलो == 0)
		वापस -EINVAL;

	अगर (FAIL(fअगरo, list_empty(&fअगरo->pending) != (fअगरo->खोलो == 0),
		 "pending list disagrees with open count:%d",
		 fअगरo->खोलो))
		वापस -ENXIO;

	पंचांगp = complete->data;
	*पंचांगp = *complete;
	list_replace(&complete->link, &पंचांगp->link);
	dp_mark_completed(पंचांगp);

	/* Only update the fअगरo in the original pended order */
	list_क्रम_each_entry_safe(pending, next, &fअगरo->pending, link) अणु
		अगर (!dp_is_completed(pending)) अणु
			df_trace("still pending: saved out: %u len: %d",
				 pending->out, pending->len);
			अवरोध;
		पूर्ण

		अगर (FAIL(fअगरo, pending->out != fअगरo->करोne ||
			 addr_check(fअगरo->in, fअगरo->करोne, pending->next),
			 "in:%u out:%u done:%u saved:%u next:%u",
			 fअगरo->in, fअगरo->out, fअगरo->करोne, pending->out,
			 pending->next))
			वापस -ENXIO;

		list_del_init(&pending->link);
		fअगरo->करोne = pending->next;
		fअगरo->avail += pending->len;
		--fअगरo->खोलो;

		df_trace("in: %u out: %u done: %u len: %u avail: %d", fअगरo->in,
			 fअगरo->out, fअगरo->करोne, pending->len, fअगरo->avail);
	पूर्ण

	अगर (FAIL(fअगरo, fअगरo->खोलो < 0, "open dma:%d < 0", fअगरo->खोलो))
		वापस -ENXIO;
	अगर (FAIL(fअगरo, fअगरo->avail > fअगरo->size, "fifo avail:%d > size:%d",
		 fअगरo->avail, fअगरo->size))
		वापस -ENXIO;

	वापस 0;
पूर्ण
