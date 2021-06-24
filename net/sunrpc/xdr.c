<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/xdr.c
 *
 * Generic XDR support.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/bvec.h>
#समावेश <trace/events/sunrpc.h>

अटल व्योम _copy_to_pages(काष्ठा page **, माप_प्रकार, स्थिर अक्षर *, माप_प्रकार);


/*
 * XDR functions क्रम basic NFS types
 */
__be32 *
xdr_encode_netobj(__be32 *p, स्थिर काष्ठा xdr_netobj *obj)
अणु
	अचिन्हित पूर्णांक	quadlen = XDR_QUADLEN(obj->len);

	p[quadlen] = 0;		/* zero trailing bytes */
	*p++ = cpu_to_be32(obj->len);
	स_नकल(p, obj->data, obj->len);
	वापस p + XDR_QUADLEN(obj->len);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_encode_netobj);

__be32 *
xdr_decode_netobj(__be32 *p, काष्ठा xdr_netobj *obj)
अणु
	अचिन्हित पूर्णांक	len;

	अगर ((len = be32_to_cpu(*p++)) > XDR_MAX_NETOBJ)
		वापस शून्य;
	obj->len  = len;
	obj->data = (u8 *) p;
	वापस p + XDR_QUADLEN(len);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_decode_netobj);

/**
 * xdr_encode_opaque_fixed - Encode fixed length opaque data
 * @p: poपूर्णांकer to current position in XDR buffer.
 * @ptr: poपूर्णांकer to data to encode (or शून्य)
 * @nbytes: size of data.
 *
 * Copy the array of data of length nbytes at ptr to the XDR buffer
 * at position p, then align to the next 32-bit boundary by padding
 * with zero bytes (see RFC1832).
 * Note: अगर ptr is शून्य, only the padding is perक्रमmed.
 *
 * Returns the updated current XDR buffer position
 *
 */
__be32 *xdr_encode_opaque_fixed(__be32 *p, स्थिर व्योम *ptr, अचिन्हित पूर्णांक nbytes)
अणु
	अगर (likely(nbytes != 0)) अणु
		अचिन्हित पूर्णांक quadlen = XDR_QUADLEN(nbytes);
		अचिन्हित पूर्णांक padding = (quadlen << 2) - nbytes;

		अगर (ptr != शून्य)
			स_नकल(p, ptr, nbytes);
		अगर (padding != 0)
			स_रखो((अक्षर *)p + nbytes, 0, padding);
		p += quadlen;
	पूर्ण
	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_encode_opaque_fixed);

/**
 * xdr_encode_opaque - Encode variable length opaque data
 * @p: poपूर्णांकer to current position in XDR buffer.
 * @ptr: poपूर्णांकer to data to encode (or शून्य)
 * @nbytes: size of data.
 *
 * Returns the updated current XDR buffer position
 */
__be32 *xdr_encode_opaque(__be32 *p, स्थिर व्योम *ptr, अचिन्हित पूर्णांक nbytes)
अणु
	*p++ = cpu_to_be32(nbytes);
	वापस xdr_encode_opaque_fixed(p, ptr, nbytes);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_encode_opaque);

__be32 *
xdr_encode_string(__be32 *p, स्थिर अक्षर *string)
अणु
	वापस xdr_encode_array(p, string, म_माप(string));
पूर्ण
EXPORT_SYMBOL_GPL(xdr_encode_string);

__be32 *
xdr_decode_string_inplace(__be32 *p, अक्षर **sp,
			  अचिन्हित पूर्णांक *lenp, अचिन्हित पूर्णांक maxlen)
अणु
	u32 len;

	len = be32_to_cpu(*p++);
	अगर (len > maxlen)
		वापस शून्य;
	*lenp = len;
	*sp = (अक्षर *) p;
	वापस p + XDR_QUADLEN(len);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_decode_string_inplace);

/**
 * xdr_terminate_string - '\0'-terminate a string residing in an xdr_buf
 * @buf: XDR buffer where string resides
 * @len: length of string, in bytes
 *
 */
व्योम xdr_terminate_string(स्थिर काष्ठा xdr_buf *buf, स्थिर u32 len)
अणु
	अक्षर *kaddr;

	kaddr = kmap_atomic(buf->pages[0]);
	kaddr[buf->page_base + len] = '\0';
	kunmap_atomic(kaddr);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_terminate_string);

माप_प्रकार xdr_buf_pagecount(स्थिर काष्ठा xdr_buf *buf)
अणु
	अगर (!buf->page_len)
		वापस 0;
	वापस (buf->page_base + buf->page_len + PAGE_SIZE - 1) >> PAGE_SHIFT;
पूर्ण

पूर्णांक
xdr_alloc_bvec(काष्ठा xdr_buf *buf, gfp_t gfp)
अणु
	माप_प्रकार i, n = xdr_buf_pagecount(buf);

	अगर (n != 0 && buf->bvec == शून्य) अणु
		buf->bvec = kदो_स्मृति_array(n, माप(buf->bvec[0]), gfp);
		अगर (!buf->bvec)
			वापस -ENOMEM;
		क्रम (i = 0; i < n; i++) अणु
			buf->bvec[i].bv_page = buf->pages[i];
			buf->bvec[i].bv_len = PAGE_SIZE;
			buf->bvec[i].bv_offset = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम
xdr_मुक्त_bvec(काष्ठा xdr_buf *buf)
अणु
	kमुक्त(buf->bvec);
	buf->bvec = शून्य;
पूर्ण

/**
 * xdr_अंतरभूत_pages - Prepare receive buffer क्रम a large reply
 * @xdr: xdr_buf पूर्णांकo which reply will be placed
 * @offset: expected offset where data payload will start, in bytes
 * @pages: vector of काष्ठा page poपूर्णांकers
 * @base: offset in first page where receive should start, in bytes
 * @len: expected size of the upper layer data payload, in bytes
 *
 */
व्योम
xdr_अंतरभूत_pages(काष्ठा xdr_buf *xdr, अचिन्हित पूर्णांक offset,
		 काष्ठा page **pages, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len)
अणु
	काष्ठा kvec *head = xdr->head;
	काष्ठा kvec *tail = xdr->tail;
	अक्षर *buf = (अक्षर *)head->iov_base;
	अचिन्हित पूर्णांक buflen = head->iov_len;

	head->iov_len  = offset;

	xdr->pages = pages;
	xdr->page_base = base;
	xdr->page_len = len;

	tail->iov_base = buf + offset;
	tail->iov_len = buflen - offset;
	xdr->buflen += len;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_अंतरभूत_pages);

/*
 * Helper routines क्रम करोing 'memmove' like operations on a काष्ठा xdr_buf
 */

/**
 * _shअगरt_data_left_pages
 * @pages: vector of pages containing both the source and dest memory area.
 * @pgto_base: page vector address of destination
 * @pgfrom_base: page vector address of source
 * @len: number of bytes to copy
 *
 * Note: the addresses pgto_base and pgfrom_base are both calculated in
 *       the same way:
 *            अगर a memory area starts at byte 'base' in page 'pages[i]',
 *            then its address is given as (i << PAGE_CACHE_SHIFT) + base
 * Alse note: pgto_base must be < pgfrom_base, but the memory areas
 * 	they poपूर्णांक to may overlap.
 */
अटल व्योम
_shअगरt_data_left_pages(काष्ठा page **pages, माप_प्रकार pgto_base,
			माप_प्रकार pgfrom_base, माप_प्रकार len)
अणु
	काष्ठा page **pgfrom, **pgto;
	अक्षर *vfrom, *vto;
	माप_प्रकार copy;

	BUG_ON(pgfrom_base <= pgto_base);

	अगर (!len)
		वापस;

	pgto = pages + (pgto_base >> PAGE_SHIFT);
	pgfrom = pages + (pgfrom_base >> PAGE_SHIFT);

	pgto_base &= ~PAGE_MASK;
	pgfrom_base &= ~PAGE_MASK;

	करो अणु
		अगर (pgto_base >= PAGE_SIZE) अणु
			pgto_base = 0;
			pgto++;
		पूर्ण
		अगर (pgfrom_base >= PAGE_SIZE)अणु
			pgfrom_base = 0;
			pgfrom++;
		पूर्ण

		copy = len;
		अगर (copy > (PAGE_SIZE - pgto_base))
			copy = PAGE_SIZE - pgto_base;
		अगर (copy > (PAGE_SIZE - pgfrom_base))
			copy = PAGE_SIZE - pgfrom_base;

		vto = kmap_atomic(*pgto);
		अगर (*pgto != *pgfrom) अणु
			vfrom = kmap_atomic(*pgfrom);
			स_नकल(vto + pgto_base, vfrom + pgfrom_base, copy);
			kunmap_atomic(vfrom);
		पूर्ण अन्यथा
			स_हटाओ(vto + pgto_base, vto + pgfrom_base, copy);
		flush_dcache_page(*pgto);
		kunmap_atomic(vto);

		pgto_base += copy;
		pgfrom_base += copy;

	पूर्ण जबतक ((len -= copy) != 0);
पूर्ण

/**
 * _shअगरt_data_right_pages
 * @pages: vector of pages containing both the source and dest memory area.
 * @pgto_base: page vector address of destination
 * @pgfrom_base: page vector address of source
 * @len: number of bytes to copy
 *
 * Note: the addresses pgto_base and pgfrom_base are both calculated in
 *       the same way:
 *            अगर a memory area starts at byte 'base' in page 'pages[i]',
 *            then its address is given as (i << PAGE_SHIFT) + base
 * Also note: pgfrom_base must be < pgto_base, but the memory areas
 * 	they poपूर्णांक to may overlap.
 */
अटल व्योम
_shअगरt_data_right_pages(काष्ठा page **pages, माप_प्रकार pgto_base,
		माप_प्रकार pgfrom_base, माप_प्रकार len)
अणु
	काष्ठा page **pgfrom, **pgto;
	अक्षर *vfrom, *vto;
	माप_प्रकार copy;

	BUG_ON(pgto_base <= pgfrom_base);

	अगर (!len)
		वापस;

	pgto_base += len;
	pgfrom_base += len;

	pgto = pages + (pgto_base >> PAGE_SHIFT);
	pgfrom = pages + (pgfrom_base >> PAGE_SHIFT);

	pgto_base &= ~PAGE_MASK;
	pgfrom_base &= ~PAGE_MASK;

	करो अणु
		/* Are any poपूर्णांकers crossing a page boundary? */
		अगर (pgto_base == 0) अणु
			pgto_base = PAGE_SIZE;
			pgto--;
		पूर्ण
		अगर (pgfrom_base == 0) अणु
			pgfrom_base = PAGE_SIZE;
			pgfrom--;
		पूर्ण

		copy = len;
		अगर (copy > pgto_base)
			copy = pgto_base;
		अगर (copy > pgfrom_base)
			copy = pgfrom_base;
		pgto_base -= copy;
		pgfrom_base -= copy;

		vto = kmap_atomic(*pgto);
		अगर (*pgto != *pgfrom) अणु
			vfrom = kmap_atomic(*pgfrom);
			स_नकल(vto + pgto_base, vfrom + pgfrom_base, copy);
			kunmap_atomic(vfrom);
		पूर्ण अन्यथा
			स_हटाओ(vto + pgto_base, vto + pgfrom_base, copy);
		flush_dcache_page(*pgto);
		kunmap_atomic(vto);

	पूर्ण जबतक ((len -= copy) != 0);
पूर्ण

/**
 * _copy_to_pages
 * @pages: array of pages
 * @pgbase: page vector address of destination
 * @p: poपूर्णांकer to source data
 * @len: length
 *
 * Copies data from an arbitrary memory location पूर्णांकo an array of pages
 * The copy is assumed to be non-overlapping.
 */
अटल व्योम
_copy_to_pages(काष्ठा page **pages, माप_प्रकार pgbase, स्थिर अक्षर *p, माप_प्रकार len)
अणु
	काष्ठा page **pgto;
	अक्षर *vto;
	माप_प्रकार copy;

	अगर (!len)
		वापस;

	pgto = pages + (pgbase >> PAGE_SHIFT);
	pgbase &= ~PAGE_MASK;

	क्रम (;;) अणु
		copy = PAGE_SIZE - pgbase;
		अगर (copy > len)
			copy = len;

		vto = kmap_atomic(*pgto);
		स_नकल(vto + pgbase, p, copy);
		kunmap_atomic(vto);

		len -= copy;
		अगर (len == 0)
			अवरोध;

		pgbase += copy;
		अगर (pgbase == PAGE_SIZE) अणु
			flush_dcache_page(*pgto);
			pgbase = 0;
			pgto++;
		पूर्ण
		p += copy;
	पूर्ण
	flush_dcache_page(*pgto);
पूर्ण

/**
 * _copy_from_pages
 * @p: poपूर्णांकer to destination
 * @pages: array of pages
 * @pgbase: offset of source data
 * @len: length
 *
 * Copies data पूर्णांकo an arbitrary memory location from an array of pages
 * The copy is assumed to be non-overlapping.
 */
व्योम
_copy_from_pages(अक्षर *p, काष्ठा page **pages, माप_प्रकार pgbase, माप_प्रकार len)
अणु
	काष्ठा page **pgfrom;
	अक्षर *vfrom;
	माप_प्रकार copy;

	अगर (!len)
		वापस;

	pgfrom = pages + (pgbase >> PAGE_SHIFT);
	pgbase &= ~PAGE_MASK;

	करो अणु
		copy = PAGE_SIZE - pgbase;
		अगर (copy > len)
			copy = len;

		vfrom = kmap_atomic(*pgfrom);
		स_नकल(p, vfrom + pgbase, copy);
		kunmap_atomic(vfrom);

		pgbase += copy;
		अगर (pgbase == PAGE_SIZE) अणु
			pgbase = 0;
			pgfrom++;
		पूर्ण
		p += copy;

	पूर्ण जबतक ((len -= copy) != 0);
पूर्ण
EXPORT_SYMBOL_GPL(_copy_from_pages);

अटल व्योम xdr_buf_iov_zero(स्थिर काष्ठा kvec *iov, अचिन्हित पूर्णांक base,
			     अचिन्हित पूर्णांक len)
अणु
	अगर (base >= iov->iov_len)
		वापस;
	अगर (len > iov->iov_len - base)
		len = iov->iov_len - base;
	स_रखो(iov->iov_base + base, 0, len);
पूर्ण

/**
 * xdr_buf_pages_zero
 * @buf: xdr_buf
 * @pgbase: beginning offset
 * @len: length
 */
अटल व्योम xdr_buf_pages_zero(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक pgbase,
			       अचिन्हित पूर्णांक len)
अणु
	काष्ठा page **pages = buf->pages;
	काष्ठा page **page;
	अक्षर *vpage;
	अचिन्हित पूर्णांक zero;

	अगर (!len)
		वापस;
	अगर (pgbase >= buf->page_len) अणु
		xdr_buf_iov_zero(buf->tail, pgbase - buf->page_len, len);
		वापस;
	पूर्ण
	अगर (pgbase + len > buf->page_len) अणु
		xdr_buf_iov_zero(buf->tail, 0, pgbase + len - buf->page_len);
		len = buf->page_len - pgbase;
	पूर्ण

	pgbase += buf->page_base;

	page = pages + (pgbase >> PAGE_SHIFT);
	pgbase &= ~PAGE_MASK;

	करो अणु
		zero = PAGE_SIZE - pgbase;
		अगर (zero > len)
			zero = len;

		vpage = kmap_atomic(*page);
		स_रखो(vpage + pgbase, 0, zero);
		kunmap_atomic(vpage);

		flush_dcache_page(*page);
		pgbase = 0;
		page++;

	पूर्ण जबतक ((len -= zero) != 0);
पूर्ण

अटल अचिन्हित पूर्णांक xdr_buf_pages_fill_sparse(स्थिर काष्ठा xdr_buf *buf,
					      अचिन्हित पूर्णांक buflen, gfp_t gfp)
अणु
	अचिन्हित पूर्णांक i, npages, pagelen;

	अगर (!(buf->flags & XDRBUF_SPARSE_PAGES))
		वापस buflen;
	अगर (buflen <= buf->head->iov_len)
		वापस buflen;
	pagelen = buflen - buf->head->iov_len;
	अगर (pagelen > buf->page_len)
		pagelen = buf->page_len;
	npages = (pagelen + buf->page_base + PAGE_SIZE - 1) >> PAGE_SHIFT;
	क्रम (i = 0; i < npages; i++) अणु
		अगर (!buf->pages[i])
			जारी;
		buf->pages[i] = alloc_page(gfp);
		अगर (likely(buf->pages[i]))
			जारी;
		buflen -= pagelen;
		pagelen = i << PAGE_SHIFT;
		अगर (pagelen > buf->page_base)
			buflen += pagelen - buf->page_base;
		अवरोध;
	पूर्ण
	वापस buflen;
पूर्ण

अटल व्योम xdr_buf_try_expand(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा kvec *head = buf->head;
	काष्ठा kvec *tail = buf->tail;
	अचिन्हित पूर्णांक sum = head->iov_len + buf->page_len + tail->iov_len;
	अचिन्हित पूर्णांक मुक्त_space, newlen;

	अगर (sum > buf->len) अणु
		मुक्त_space = min_t(अचिन्हित पूर्णांक, sum - buf->len, len);
		newlen = xdr_buf_pages_fill_sparse(buf, buf->len + मुक्त_space,
						   GFP_KERNEL);
		मुक्त_space = newlen - buf->len;
		buf->len = newlen;
		len -= मुक्त_space;
		अगर (!len)
			वापस;
	पूर्ण

	अगर (buf->buflen > sum) अणु
		/* Expand the tail buffer */
		मुक्त_space = min_t(अचिन्हित पूर्णांक, buf->buflen - sum, len);
		tail->iov_len += मुक्त_space;
		buf->len += मुक्त_space;
	पूर्ण
पूर्ण

अटल व्योम xdr_buf_tail_copy_right(स्थिर काष्ठा xdr_buf *buf,
				    अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
				    अचिन्हित पूर्णांक shअगरt)
अणु
	स्थिर काष्ठा kvec *tail = buf->tail;
	अचिन्हित पूर्णांक to = base + shअगरt;

	अगर (to >= tail->iov_len)
		वापस;
	अगर (len + to > tail->iov_len)
		len = tail->iov_len - to;
	स_हटाओ(tail->iov_base + to, tail->iov_base + base, len);
पूर्ण

अटल व्योम xdr_buf_pages_copy_right(स्थिर काष्ठा xdr_buf *buf,
				     अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
				     अचिन्हित पूर्णांक shअगरt)
अणु
	स्थिर काष्ठा kvec *tail = buf->tail;
	अचिन्हित पूर्णांक to = base + shअगरt;
	अचिन्हित पूर्णांक pglen = 0;
	अचिन्हित पूर्णांक talen = 0, tato = 0;

	अगर (base >= buf->page_len)
		वापस;
	अगर (len > buf->page_len - base)
		len = buf->page_len - base;
	अगर (to >= buf->page_len) अणु
		tato = to - buf->page_len;
		अगर (tail->iov_len >= len + tato)
			talen = len;
		अन्यथा अगर (tail->iov_len > tato)
			talen = tail->iov_len - tato;
	पूर्ण अन्यथा अगर (len + to >= buf->page_len) अणु
		pglen = buf->page_len - to;
		talen = len - pglen;
		अगर (talen > tail->iov_len)
			talen = tail->iov_len;
	पूर्ण अन्यथा
		pglen = len;

	_copy_from_pages(tail->iov_base + tato, buf->pages,
			 buf->page_base + base + pglen, talen);
	_shअगरt_data_right_pages(buf->pages, buf->page_base + to,
				buf->page_base + base, pglen);
पूर्ण

अटल व्योम xdr_buf_head_copy_right(स्थिर काष्ठा xdr_buf *buf,
				    अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
				    अचिन्हित पूर्णांक shअगरt)
अणु
	स्थिर काष्ठा kvec *head = buf->head;
	स्थिर काष्ठा kvec *tail = buf->tail;
	अचिन्हित पूर्णांक to = base + shअगरt;
	अचिन्हित पूर्णांक pglen = 0, pgto = 0;
	अचिन्हित पूर्णांक talen = 0, tato = 0;

	अगर (base >= head->iov_len)
		वापस;
	अगर (len > head->iov_len - base)
		len = head->iov_len - base;
	अगर (to >= buf->page_len + head->iov_len) अणु
		tato = to - buf->page_len - head->iov_len;
		talen = len;
	पूर्ण अन्यथा अगर (to >= head->iov_len) अणु
		pgto = to - head->iov_len;
		pglen = len;
		अगर (pgto + pglen > buf->page_len) अणु
			talen = pgto + pglen - buf->page_len;
			pglen -= talen;
		पूर्ण
	पूर्ण अन्यथा अणु
		pglen = len - to;
		अगर (pglen > buf->page_len) अणु
			talen = pglen - buf->page_len;
			pglen = buf->page_len;
		पूर्ण
	पूर्ण

	len -= talen;
	base += len;
	अगर (talen + tato > tail->iov_len)
		talen = tail->iov_len > tato ? tail->iov_len - tato : 0;
	स_नकल(tail->iov_base + tato, head->iov_base + base, talen);

	len -= pglen;
	base -= pglen;
	_copy_to_pages(buf->pages, buf->page_base + pgto, head->iov_base + base,
		       pglen);

	base -= len;
	स_हटाओ(head->iov_base + to, head->iov_base + base, len);
पूर्ण

अटल व्योम xdr_buf_tail_shअगरt_right(स्थिर काष्ठा xdr_buf *buf,
				     अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
				     अचिन्हित पूर्णांक shअगरt)
अणु
	स्थिर काष्ठा kvec *tail = buf->tail;

	अगर (base >= tail->iov_len || !shअगरt || !len)
		वापस;
	xdr_buf_tail_copy_right(buf, base, len, shअगरt);
पूर्ण

अटल व्योम xdr_buf_pages_shअगरt_right(स्थिर काष्ठा xdr_buf *buf,
				      अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
				      अचिन्हित पूर्णांक shअगरt)
अणु
	अगर (!shअगरt || !len)
		वापस;
	अगर (base >= buf->page_len) अणु
		xdr_buf_tail_shअगरt_right(buf, base - buf->page_len, len, shअगरt);
		वापस;
	पूर्ण
	अगर (base + len > buf->page_len)
		xdr_buf_tail_shअगरt_right(buf, 0, base + len - buf->page_len,
					 shअगरt);
	xdr_buf_pages_copy_right(buf, base, len, shअगरt);
पूर्ण

अटल व्योम xdr_buf_head_shअगरt_right(स्थिर काष्ठा xdr_buf *buf,
				     अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
				     अचिन्हित पूर्णांक shअगरt)
अणु
	स्थिर काष्ठा kvec *head = buf->head;

	अगर (!shअगरt)
		वापस;
	अगर (base >= head->iov_len) अणु
		xdr_buf_pages_shअगरt_right(buf, head->iov_len - base, len,
					  shअगरt);
		वापस;
	पूर्ण
	अगर (base + len > head->iov_len)
		xdr_buf_pages_shअगरt_right(buf, 0, base + len - head->iov_len,
					  shअगरt);
	xdr_buf_head_copy_right(buf, base, len, shअगरt);
पूर्ण

अटल व्योम xdr_buf_tail_copy_left(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base,
				   अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक shअगरt)
अणु
	स्थिर काष्ठा kvec *tail = buf->tail;

	अगर (base >= tail->iov_len)
		वापस;
	अगर (len > tail->iov_len - base)
		len = tail->iov_len - base;
	/* Shअगरt data पूर्णांकo head */
	अगर (shअगरt > buf->page_len + base) अणु
		स्थिर काष्ठा kvec *head = buf->head;
		अचिन्हित पूर्णांक hdto =
			head->iov_len + buf->page_len + base - shअगरt;
		अचिन्हित पूर्णांक hdlen = len;

		अगर (WARN_ONCE(shअगरt > head->iov_len + buf->page_len + base,
			      "SUNRPC: Misaligned data.\n"))
			वापस;
		अगर (hdto + hdlen > head->iov_len)
			hdlen = head->iov_len - hdto;
		स_नकल(head->iov_base + hdto, tail->iov_base + base, hdlen);
		base += hdlen;
		len -= hdlen;
		अगर (!len)
			वापस;
	पूर्ण
	/* Shअगरt data पूर्णांकo pages */
	अगर (shअगरt > base) अणु
		अचिन्हित पूर्णांक pgto = buf->page_len + base - shअगरt;
		अचिन्हित पूर्णांक pglen = len;

		अगर (pgto + pglen > buf->page_len)
			pglen = buf->page_len - pgto;
		_copy_to_pages(buf->pages, buf->page_base + pgto,
			       tail->iov_base + base, pglen);
		base += pglen;
		len -= pglen;
		अगर (!len)
			वापस;
	पूर्ण
	स_हटाओ(tail->iov_base + base - shअगरt, tail->iov_base + base, len);
पूर्ण

अटल व्योम xdr_buf_pages_copy_left(स्थिर काष्ठा xdr_buf *buf,
				    अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
				    अचिन्हित पूर्णांक shअगरt)
अणु
	अचिन्हित पूर्णांक pgto;

	अगर (base >= buf->page_len)
		वापस;
	अगर (len > buf->page_len - base)
		len = buf->page_len - base;
	/* Shअगरt data पूर्णांकo head */
	अगर (shअगरt > base) अणु
		स्थिर काष्ठा kvec *head = buf->head;
		अचिन्हित पूर्णांक hdto = head->iov_len + base - shअगरt;
		अचिन्हित पूर्णांक hdlen = len;

		अगर (WARN_ONCE(shअगरt > head->iov_len + base,
			      "SUNRPC: Misaligned data.\n"))
			वापस;
		अगर (hdto + hdlen > head->iov_len)
			hdlen = head->iov_len - hdto;
		_copy_from_pages(head->iov_base + hdto, buf->pages,
				 buf->page_base + base, hdlen);
		base += hdlen;
		len -= hdlen;
		अगर (!len)
			वापस;
	पूर्ण
	pgto = base - shअगरt;
	_shअगरt_data_left_pages(buf->pages, buf->page_base + pgto,
			       buf->page_base + base, len);
पूर्ण

अटल व्योम xdr_buf_tail_shअगरt_left(स्थिर काष्ठा xdr_buf *buf,
				    अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
				    अचिन्हित पूर्णांक shअगरt)
अणु
	अगर (!shअगरt || !len)
		वापस;
	xdr_buf_tail_copy_left(buf, base, len, shअगरt);
पूर्ण

अटल व्योम xdr_buf_pages_shअगरt_left(स्थिर काष्ठा xdr_buf *buf,
				     अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
				     अचिन्हित पूर्णांक shअगरt)
अणु
	अगर (!shअगरt || !len)
		वापस;
	अगर (base >= buf->page_len) अणु
		xdr_buf_tail_shअगरt_left(buf, base - buf->page_len, len, shअगरt);
		वापस;
	पूर्ण
	xdr_buf_pages_copy_left(buf, base, len, shअगरt);
	len += base;
	अगर (len <= buf->page_len)
		वापस;
	xdr_buf_tail_copy_left(buf, 0, len - buf->page_len, shअगरt);
पूर्ण

/**
 * xdr_shrink_bufhead
 * @buf: xdr_buf
 * @len: new length of buf->head[0]
 *
 * Shrinks XDR buffer's header kvec buf->head[0], setting it to
 * 'len' bytes. The extra data is not lost, but is instead
 * moved पूर्णांकo the अंतरभूतd pages and/or the tail.
 */
अटल अचिन्हित पूर्णांक xdr_shrink_bufhead(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा kvec *head = buf->head;
	अचिन्हित पूर्णांक shअगरt, buflen = max(buf->len, len);

	WARN_ON_ONCE(len > head->iov_len);
	अगर (head->iov_len > buflen) अणु
		buf->buflen -= head->iov_len - buflen;
		head->iov_len = buflen;
	पूर्ण
	अगर (len >= head->iov_len)
		वापस 0;
	shअगरt = head->iov_len - len;
	xdr_buf_try_expand(buf, shअगरt);
	xdr_buf_head_shअगरt_right(buf, len, buflen - len, shअगरt);
	head->iov_len = len;
	buf->buflen -= shअगरt;
	buf->len -= shअगरt;
	वापस shअगरt;
पूर्ण

/**
 * xdr_shrink_pagelen - shrinks buf->pages to @len bytes
 * @buf: xdr_buf
 * @len: new page buffer length
 *
 * The extra data is not lost, but is instead moved पूर्णांकo buf->tail.
 * Returns the actual number of bytes moved.
 */
अटल अचिन्हित पूर्णांक xdr_shrink_pagelen(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक shअगरt, buflen = buf->len - buf->head->iov_len;

	WARN_ON_ONCE(len > buf->page_len);
	अगर (buf->head->iov_len >= buf->len || len > buflen)
		buflen = len;
	अगर (buf->page_len > buflen) अणु
		buf->buflen -= buf->page_len - buflen;
		buf->page_len = buflen;
	पूर्ण
	अगर (len >= buf->page_len)
		वापस 0;
	shअगरt = buf->page_len - len;
	xdr_buf_try_expand(buf, shअगरt);
	xdr_buf_pages_shअगरt_right(buf, len, buflen - len, shअगरt);
	buf->page_len = len;
	buf->len -= shअगरt;
	buf->buflen -= shअगरt;
	वापस shअगरt;
पूर्ण

व्योम
xdr_shअगरt_buf(काष्ठा xdr_buf *buf, माप_प्रकार len)
अणु
	xdr_shrink_bufhead(buf, buf->head->iov_len - len);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_shअगरt_buf);

/**
 * xdr_stream_pos - Return the current offset from the start of the xdr_stream
 * @xdr: poपूर्णांकer to काष्ठा xdr_stream
 */
अचिन्हित पूर्णांक xdr_stream_pos(स्थिर काष्ठा xdr_stream *xdr)
अणु
	वापस (अचिन्हित पूर्णांक)(XDR_QUADLEN(xdr->buf->len) - xdr->nwords) << 2;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_stream_pos);

अटल व्योम xdr_stream_set_pos(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक pos)
अणु
	अचिन्हित पूर्णांक blen = xdr->buf->len;

	xdr->nwords = blen > pos ? XDR_QUADLEN(blen) - XDR_QUADLEN(pos) : 0;
पूर्ण

अटल व्योम xdr_stream_page_set_pos(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक pos)
अणु
	xdr_stream_set_pos(xdr, pos + xdr->buf->head[0].iov_len);
पूर्ण

/**
 * xdr_page_pos - Return the current offset from the start of the xdr pages
 * @xdr: poपूर्णांकer to काष्ठा xdr_stream
 */
अचिन्हित पूर्णांक xdr_page_pos(स्थिर काष्ठा xdr_stream *xdr)
अणु
	अचिन्हित पूर्णांक pos = xdr_stream_pos(xdr);

	WARN_ON(pos < xdr->buf->head[0].iov_len);
	वापस pos - xdr->buf->head[0].iov_len;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_page_pos);

/**
 * xdr_init_encode - Initialize a काष्ठा xdr_stream क्रम sending data.
 * @xdr: poपूर्णांकer to xdr_stream काष्ठा
 * @buf: poपूर्णांकer to XDR buffer in which to encode data
 * @p: current poपूर्णांकer inside XDR buffer
 * @rqst: poपूर्णांकer to controlling rpc_rqst, क्रम debugging
 *
 * Note: at the moment the RPC client only passes the length of our
 *	 scratch buffer in the xdr_buf's header kvec. Previously this
 *	 meant we needed to call xdr_adjust_iovec() after encoding the
 *	 data. With the new scheme, the xdr_stream manages the details
 *	 of the buffer length, and takes care of adjusting the kvec
 *	 length क्रम us.
 */
व्योम xdr_init_encode(काष्ठा xdr_stream *xdr, काष्ठा xdr_buf *buf, __be32 *p,
		     काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा kvec *iov = buf->head;
	पूर्णांक scratch_len = buf->buflen - buf->page_len - buf->tail[0].iov_len;

	xdr_reset_scratch_buffer(xdr);
	BUG_ON(scratch_len < 0);
	xdr->buf = buf;
	xdr->iov = iov;
	xdr->p = (__be32 *)((अक्षर *)iov->iov_base + iov->iov_len);
	xdr->end = (__be32 *)((अक्षर *)iov->iov_base + scratch_len);
	BUG_ON(iov->iov_len > scratch_len);

	अगर (p != xdr->p && p != शून्य) अणु
		माप_प्रकार len;

		BUG_ON(p < xdr->p || p > xdr->end);
		len = (अक्षर *)p - (अक्षर *)xdr->p;
		xdr->p = p;
		buf->len += len;
		iov->iov_len += len;
	पूर्ण
	xdr->rqst = rqst;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_init_encode);

/**
 * xdr_commit_encode - Ensure all data is written to buffer
 * @xdr: poपूर्णांकer to xdr_stream
 *
 * We handle encoding across page boundaries by giving the caller a
 * temporary location to ग_लिखो to, then later copying the data पूर्णांकo
 * place; xdr_commit_encode करोes that copying.
 *
 * Normally the caller करोesn't need to call this directly, as the
 * following xdr_reserve_space will करो it.  But an explicit call may be
 * required at the end of encoding, or any other समय when the xdr_buf
 * data might be पढ़ो.
 */
अंतरभूत व्योम xdr_commit_encode(काष्ठा xdr_stream *xdr)
अणु
	पूर्णांक shअगरt = xdr->scratch.iov_len;
	व्योम *page;

	अगर (shअगरt == 0)
		वापस;
	page = page_address(*xdr->page_ptr);
	स_नकल(xdr->scratch.iov_base, page, shअगरt);
	स_हटाओ(page, page + shअगरt, (व्योम *)xdr->p - page);
	xdr_reset_scratch_buffer(xdr);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_commit_encode);

अटल __be32 *xdr_get_next_encode_buffer(काष्ठा xdr_stream *xdr,
		माप_प्रकार nbytes)
अणु
	__be32 *p;
	पूर्णांक space_left;
	पूर्णांक frag1bytes, frag2bytes;

	अगर (nbytes > PAGE_SIZE)
		जाओ out_overflow; /* Bigger buffers require special handling */
	अगर (xdr->buf->len + nbytes > xdr->buf->buflen)
		जाओ out_overflow; /* Sorry, we're totally out of space */
	frag1bytes = (xdr->end - xdr->p) << 2;
	frag2bytes = nbytes - frag1bytes;
	अगर (xdr->iov)
		xdr->iov->iov_len += frag1bytes;
	अन्यथा
		xdr->buf->page_len += frag1bytes;
	xdr->page_ptr++;
	xdr->iov = शून्य;
	/*
	 * If the last encode didn't end exactly on a page boundary, the
	 * next one will straddle boundaries.  Encode पूर्णांकo the next
	 * page, then copy it back later in xdr_commit_encode.  We use
	 * the "scratch" iov to track any temporarily unused fragment of
	 * space at the end of the previous buffer:
	 */
	xdr_set_scratch_buffer(xdr, xdr->p, frag1bytes);
	p = page_address(*xdr->page_ptr);
	/*
	 * Note this is where the next encode will start after we've
	 * shअगरted this one back:
	 */
	xdr->p = (व्योम *)p + frag2bytes;
	space_left = xdr->buf->buflen - xdr->buf->len;
	xdr->end = (व्योम *)p + min_t(पूर्णांक, space_left, PAGE_SIZE);
	xdr->buf->page_len += frag2bytes;
	xdr->buf->len += nbytes;
	वापस p;
out_overflow:
	trace_rpc_xdr_overflow(xdr, nbytes);
	वापस शून्य;
पूर्ण

/**
 * xdr_reserve_space - Reserve buffer space क्रम sending
 * @xdr: poपूर्णांकer to xdr_stream
 * @nbytes: number of bytes to reserve
 *
 * Checks that we have enough buffer space to encode 'nbytes' more
 * bytes of data. If so, update the total xdr_buf length, and
 * adjust the length of the current kvec.
 */
__be32 * xdr_reserve_space(काष्ठा xdr_stream *xdr, माप_प्रकार nbytes)
अणु
	__be32 *p = xdr->p;
	__be32 *q;

	xdr_commit_encode(xdr);
	/* align nbytes on the next 32-bit boundary */
	nbytes += 3;
	nbytes &= ~3;
	q = p + (nbytes >> 2);
	अगर (unlikely(q > xdr->end || q < p))
		वापस xdr_get_next_encode_buffer(xdr, nbytes);
	xdr->p = q;
	अगर (xdr->iov)
		xdr->iov->iov_len += nbytes;
	अन्यथा
		xdr->buf->page_len += nbytes;
	xdr->buf->len += nbytes;
	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_reserve_space);


/**
 * xdr_reserve_space_vec - Reserves a large amount of buffer space क्रम sending
 * @xdr: poपूर्णांकer to xdr_stream
 * @vec: poपूर्णांकer to a kvec array
 * @nbytes: number of bytes to reserve
 *
 * Reserves enough buffer space to encode 'nbytes' of data and stores the
 * poपूर्णांकers in 'vec'. The size argument passed to xdr_reserve_space() is
 * determined based on the number of bytes reमुख्यing in the current page to
 * aव्योम invalidating iov_base poपूर्णांकers when xdr_commit_encode() is called.
 */
पूर्णांक xdr_reserve_space_vec(काष्ठा xdr_stream *xdr, काष्ठा kvec *vec, माप_प्रकार nbytes)
अणु
	पूर्णांक thislen;
	पूर्णांक v = 0;
	__be32 *p;

	/*
	 * svcrdma requires every READ payload to start somewhere
	 * in xdr->pages.
	 */
	अगर (xdr->iov == xdr->buf->head) अणु
		xdr->iov = शून्य;
		xdr->end = xdr->p;
	पूर्ण

	जबतक (nbytes) अणु
		thislen = xdr->buf->page_len % PAGE_SIZE;
		thislen = min_t(माप_प्रकार, nbytes, PAGE_SIZE - thislen);

		p = xdr_reserve_space(xdr, thislen);
		अगर (!p)
			वापस -EIO;

		vec[v].iov_base = p;
		vec[v].iov_len = thislen;
		v++;
		nbytes -= thislen;
	पूर्ण

	वापस v;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_reserve_space_vec);

/**
 * xdr_truncate_encode - truncate an encode buffer
 * @xdr: poपूर्णांकer to xdr_stream
 * @len: new length of buffer
 *
 * Truncates the xdr stream, so that xdr->buf->len == len,
 * and xdr->p poपूर्णांकs at offset len from the start of the buffer, and
 * head, tail, and page lengths are adjusted to correspond.
 *
 * If this means moving xdr->p to a dअगरferent buffer, we assume that
 * the end poपूर्णांकer should be set to the end of the current page,
 * except in the हाल of the head buffer when we assume the head
 * buffer's current length represents the end of the available buffer.
 *
 * This is *not* safe to use on a buffer that alपढ़ोy has अंतरभूतd page
 * cache pages (as in a zero-copy server पढ़ो reply), except क्रम the
 * simple हाल of truncating from one position in the tail to another.
 *
 */
व्योम xdr_truncate_encode(काष्ठा xdr_stream *xdr, माप_प्रकार len)
अणु
	काष्ठा xdr_buf *buf = xdr->buf;
	काष्ठा kvec *head = buf->head;
	काष्ठा kvec *tail = buf->tail;
	पूर्णांक fraglen;
	पूर्णांक new;

	अगर (len > buf->len) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण
	xdr_commit_encode(xdr);

	fraglen = min_t(पूर्णांक, buf->len - len, tail->iov_len);
	tail->iov_len -= fraglen;
	buf->len -= fraglen;
	अगर (tail->iov_len) अणु
		xdr->p = tail->iov_base + tail->iov_len;
		WARN_ON_ONCE(!xdr->end);
		WARN_ON_ONCE(!xdr->iov);
		वापस;
	पूर्ण
	WARN_ON_ONCE(fraglen);
	fraglen = min_t(पूर्णांक, buf->len - len, buf->page_len);
	buf->page_len -= fraglen;
	buf->len -= fraglen;

	new = buf->page_base + buf->page_len;

	xdr->page_ptr = buf->pages + (new >> PAGE_SHIFT);

	अगर (buf->page_len) अणु
		xdr->p = page_address(*xdr->page_ptr);
		xdr->end = (व्योम *)xdr->p + PAGE_SIZE;
		xdr->p = (व्योम *)xdr->p + (new % PAGE_SIZE);
		WARN_ON_ONCE(xdr->iov);
		वापस;
	पूर्ण
	अगर (fraglen)
		xdr->end = head->iov_base + head->iov_len;
	/* (otherwise assume xdr->end is alपढ़ोy set) */
	xdr->page_ptr--;
	head->iov_len = len;
	buf->len = len;
	xdr->p = head->iov_base + head->iov_len;
	xdr->iov = buf->head;
पूर्ण
EXPORT_SYMBOL(xdr_truncate_encode);

/**
 * xdr_restrict_buflen - decrease available buffer space
 * @xdr: poपूर्णांकer to xdr_stream
 * @newbuflen: new maximum number of bytes available
 *
 * Adjust our idea of how much space is available in the buffer.
 * If we've alपढ़ोy used too much space in the buffer, वापसs -1.
 * If the available space is alपढ़ोy smaller than newbuflen, वापसs 0
 * and करोes nothing.  Otherwise, adjusts xdr->buf->buflen to newbuflen
 * and ensures xdr->end is set at most offset newbuflen from the start
 * of the buffer.
 */
पूर्णांक xdr_restrict_buflen(काष्ठा xdr_stream *xdr, पूर्णांक newbuflen)
अणु
	काष्ठा xdr_buf *buf = xdr->buf;
	पूर्णांक left_in_this_buf = (व्योम *)xdr->end - (व्योम *)xdr->p;
	पूर्णांक end_offset = buf->len + left_in_this_buf;

	अगर (newbuflen < 0 || newbuflen < buf->len)
		वापस -1;
	अगर (newbuflen > buf->buflen)
		वापस 0;
	अगर (newbuflen < end_offset)
		xdr->end = (व्योम *)xdr->end + newbuflen - end_offset;
	buf->buflen = newbuflen;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(xdr_restrict_buflen);

/**
 * xdr_ग_लिखो_pages - Insert a list of pages पूर्णांकo an XDR buffer क्रम sending
 * @xdr: poपूर्णांकer to xdr_stream
 * @pages: list of pages
 * @base: offset of first byte
 * @len: length of data in bytes
 *
 */
व्योम xdr_ग_लिखो_pages(काष्ठा xdr_stream *xdr, काष्ठा page **pages, अचिन्हित पूर्णांक base,
		 अचिन्हित पूर्णांक len)
अणु
	काष्ठा xdr_buf *buf = xdr->buf;
	काष्ठा kvec *iov = buf->tail;
	buf->pages = pages;
	buf->page_base = base;
	buf->page_len = len;

	iov->iov_base = (अक्षर *)xdr->p;
	iov->iov_len  = 0;
	xdr->iov = iov;

	अगर (len & 3) अणु
		अचिन्हित पूर्णांक pad = 4 - (len & 3);

		BUG_ON(xdr->p >= xdr->end);
		iov->iov_base = (अक्षर *)xdr->p + (len & 3);
		iov->iov_len  += pad;
		len += pad;
		*xdr->p++ = 0;
	पूर्ण
	buf->buflen += len;
	buf->len += len;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_ग_लिखो_pages);

अटल अचिन्हित पूर्णांक xdr_set_iov(काष्ठा xdr_stream *xdr, काष्ठा kvec *iov,
				अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len)
अणु
	अगर (len > iov->iov_len)
		len = iov->iov_len;
	अगर (unlikely(base > len))
		base = len;
	xdr->p = (__be32*)(iov->iov_base + base);
	xdr->end = (__be32*)(iov->iov_base + len);
	xdr->iov = iov;
	xdr->page_ptr = शून्य;
	वापस len - base;
पूर्ण

अटल अचिन्हित पूर्णांक xdr_set_tail_base(काष्ठा xdr_stream *xdr,
				      अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len)
अणु
	काष्ठा xdr_buf *buf = xdr->buf;

	xdr_stream_set_pos(xdr, base + buf->page_len + buf->head->iov_len);
	वापस xdr_set_iov(xdr, buf->tail, base, len);
पूर्ण

अटल अचिन्हित पूर्णांक xdr_set_page_base(काष्ठा xdr_stream *xdr,
				      अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक pgnr;
	अचिन्हित पूर्णांक maxlen;
	अचिन्हित पूर्णांक pgoff;
	अचिन्हित पूर्णांक pgend;
	व्योम *kaddr;

	maxlen = xdr->buf->page_len;
	अगर (base >= maxlen) अणु
		base = maxlen;
		maxlen = 0;
	पूर्ण अन्यथा
		maxlen -= base;
	अगर (len > maxlen)
		len = maxlen;

	xdr_stream_page_set_pos(xdr, base);
	base += xdr->buf->page_base;

	pgnr = base >> PAGE_SHIFT;
	xdr->page_ptr = &xdr->buf->pages[pgnr];
	kaddr = page_address(*xdr->page_ptr);

	pgoff = base & ~PAGE_MASK;
	xdr->p = (__be32*)(kaddr + pgoff);

	pgend = pgoff + len;
	अगर (pgend > PAGE_SIZE)
		pgend = PAGE_SIZE;
	xdr->end = (__be32*)(kaddr + pgend);
	xdr->iov = शून्य;
	वापस len;
पूर्ण

अटल व्योम xdr_set_page(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक base,
			 अचिन्हित पूर्णांक len)
अणु
	अगर (xdr_set_page_base(xdr, base, len) == 0) अणु
		base -= xdr->buf->page_len;
		xdr_set_tail_base(xdr, base, len);
	पूर्ण
पूर्ण

अटल व्योम xdr_set_next_page(काष्ठा xdr_stream *xdr)
अणु
	अचिन्हित पूर्णांक newbase;

	newbase = (1 + xdr->page_ptr - xdr->buf->pages) << PAGE_SHIFT;
	newbase -= xdr->buf->page_base;
	अगर (newbase < xdr->buf->page_len)
		xdr_set_page_base(xdr, newbase, xdr_stream_reमुख्यing(xdr));
	अन्यथा
		xdr_set_tail_base(xdr, 0, xdr_stream_reमुख्यing(xdr));
पूर्ण

अटल bool xdr_set_next_buffer(काष्ठा xdr_stream *xdr)
अणु
	अगर (xdr->page_ptr != शून्य)
		xdr_set_next_page(xdr);
	अन्यथा अगर (xdr->iov == xdr->buf->head)
		xdr_set_page(xdr, 0, xdr_stream_reमुख्यing(xdr));
	वापस xdr->p != xdr->end;
पूर्ण

/**
 * xdr_init_decode - Initialize an xdr_stream क्रम decoding data.
 * @xdr: poपूर्णांकer to xdr_stream काष्ठा
 * @buf: poपूर्णांकer to XDR buffer from which to decode data
 * @p: current poपूर्णांकer inside XDR buffer
 * @rqst: poपूर्णांकer to controlling rpc_rqst, क्रम debugging
 */
व्योम xdr_init_decode(काष्ठा xdr_stream *xdr, काष्ठा xdr_buf *buf, __be32 *p,
		     काष्ठा rpc_rqst *rqst)
अणु
	xdr->buf = buf;
	xdr_reset_scratch_buffer(xdr);
	xdr->nwords = XDR_QUADLEN(buf->len);
	अगर (xdr_set_iov(xdr, buf->head, 0, buf->len) == 0 &&
	    xdr_set_page_base(xdr, 0, buf->len) == 0)
		xdr_set_iov(xdr, buf->tail, 0, buf->len);
	अगर (p != शून्य && p > xdr->p && xdr->end >= p) अणु
		xdr->nwords -= p - xdr->p;
		xdr->p = p;
	पूर्ण
	xdr->rqst = rqst;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_init_decode);

/**
 * xdr_init_decode_pages - Initialize an xdr_stream क्रम decoding पूर्णांकo pages
 * @xdr: poपूर्णांकer to xdr_stream काष्ठा
 * @buf: poपूर्णांकer to XDR buffer from which to decode data
 * @pages: list of pages to decode पूर्णांकo
 * @len: length in bytes of buffer in pages
 */
व्योम xdr_init_decode_pages(काष्ठा xdr_stream *xdr, काष्ठा xdr_buf *buf,
			   काष्ठा page **pages, अचिन्हित पूर्णांक len)
अणु
	स_रखो(buf, 0, माप(*buf));
	buf->pages =  pages;
	buf->page_len =  len;
	buf->buflen =  len;
	buf->len = len;
	xdr_init_decode(xdr, buf, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_init_decode_pages);

अटल __be32 * __xdr_अंतरभूत_decode(काष्ठा xdr_stream *xdr, माप_प्रकार nbytes)
अणु
	अचिन्हित पूर्णांक nwords = XDR_QUADLEN(nbytes);
	__be32 *p = xdr->p;
	__be32 *q = p + nwords;

	अगर (unlikely(nwords > xdr->nwords || q > xdr->end || q < p))
		वापस शून्य;
	xdr->p = q;
	xdr->nwords -= nwords;
	वापस p;
पूर्ण

अटल __be32 *xdr_copy_to_scratch(काष्ठा xdr_stream *xdr, माप_प्रकार nbytes)
अणु
	__be32 *p;
	अक्षर *cpdest = xdr->scratch.iov_base;
	माप_प्रकार cplen = (अक्षर *)xdr->end - (अक्षर *)xdr->p;

	अगर (nbytes > xdr->scratch.iov_len)
		जाओ out_overflow;
	p = __xdr_अंतरभूत_decode(xdr, cplen);
	अगर (p == शून्य)
		वापस शून्य;
	स_नकल(cpdest, p, cplen);
	अगर (!xdr_set_next_buffer(xdr))
		जाओ out_overflow;
	cpdest += cplen;
	nbytes -= cplen;
	p = __xdr_अंतरभूत_decode(xdr, nbytes);
	अगर (p == शून्य)
		वापस शून्य;
	स_नकल(cpdest, p, nbytes);
	वापस xdr->scratch.iov_base;
out_overflow:
	trace_rpc_xdr_overflow(xdr, nbytes);
	वापस शून्य;
पूर्ण

/**
 * xdr_अंतरभूत_decode - Retrieve XDR data to decode
 * @xdr: poपूर्णांकer to xdr_stream काष्ठा
 * @nbytes: number of bytes of data to decode
 *
 * Check अगर the input buffer is दीर्घ enough to enable us to decode
 * 'nbytes' more bytes of data starting at the current position.
 * If so वापस the current poपूर्णांकer, then update the current
 * poपूर्णांकer position.
 */
__be32 * xdr_अंतरभूत_decode(काष्ठा xdr_stream *xdr, माप_प्रकार nbytes)
अणु
	__be32 *p;

	अगर (unlikely(nbytes == 0))
		वापस xdr->p;
	अगर (xdr->p == xdr->end && !xdr_set_next_buffer(xdr))
		जाओ out_overflow;
	p = __xdr_अंतरभूत_decode(xdr, nbytes);
	अगर (p != शून्य)
		वापस p;
	वापस xdr_copy_to_scratch(xdr, nbytes);
out_overflow:
	trace_rpc_xdr_overflow(xdr, nbytes);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_अंतरभूत_decode);

अटल व्योम xdr_realign_pages(काष्ठा xdr_stream *xdr)
अणु
	काष्ठा xdr_buf *buf = xdr->buf;
	काष्ठा kvec *iov = buf->head;
	अचिन्हित पूर्णांक cur = xdr_stream_pos(xdr);
	अचिन्हित पूर्णांक copied;

	/* Realign pages to current poपूर्णांकer position */
	अगर (iov->iov_len > cur) अणु
		copied = xdr_shrink_bufhead(buf, cur);
		trace_rpc_xdr_alignment(xdr, cur, copied);
		xdr_set_page(xdr, 0, buf->page_len);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक xdr_align_pages(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा xdr_buf *buf = xdr->buf;
	अचिन्हित पूर्णांक nwords = XDR_QUADLEN(len);
	अचिन्हित पूर्णांक copied;

	अगर (xdr->nwords == 0)
		वापस 0;

	xdr_realign_pages(xdr);
	अगर (nwords > xdr->nwords) अणु
		nwords = xdr->nwords;
		len = nwords << 2;
	पूर्ण
	अगर (buf->page_len <= len)
		len = buf->page_len;
	अन्यथा अगर (nwords < xdr->nwords) अणु
		/* Truncate page data and move it पूर्णांकo the tail */
		copied = xdr_shrink_pagelen(buf, len);
		trace_rpc_xdr_alignment(xdr, len, copied);
	पूर्ण
	वापस len;
पूर्ण

/**
 * xdr_पढ़ो_pages - align page-based XDR data to current poपूर्णांकer position
 * @xdr: poपूर्णांकer to xdr_stream काष्ठा
 * @len: number of bytes of page data
 *
 * Moves data beyond the current poपूर्णांकer position from the XDR head[] buffer
 * पूर्णांकo the page list. Any data that lies beyond current position + @len
 * bytes is moved पूर्णांकo the XDR tail[]. The xdr_stream current position is
 * then advanced past that data to align to the next XDR object in the tail.
 *
 * Returns the number of XDR encoded bytes now contained in the pages
 */
अचिन्हित पूर्णांक xdr_पढ़ो_pages(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक nwords = XDR_QUADLEN(len);
	अचिन्हित पूर्णांक base, end, pglen;

	pglen = xdr_align_pages(xdr, nwords << 2);
	अगर (pglen == 0)
		वापस 0;

	base = (nwords << 2) - pglen;
	end = xdr_stream_reमुख्यing(xdr) - pglen;

	xdr_set_tail_base(xdr, base, end);
	वापस len <= pglen ? len : pglen;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_पढ़ो_pages);

अचिन्हित पूर्णांक xdr_align_data(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक offset,
			    अचिन्हित पूर्णांक length)
अणु
	काष्ठा xdr_buf *buf = xdr->buf;
	अचिन्हित पूर्णांक from, bytes, len;
	अचिन्हित पूर्णांक shअगरt;

	xdr_realign_pages(xdr);
	from = xdr_page_pos(xdr);

	अगर (from >= buf->page_len + buf->tail->iov_len)
		वापस 0;
	अगर (from + buf->head->iov_len >= buf->len)
		वापस 0;

	len = buf->len - buf->head->iov_len;

	/* We only shअगरt data left! */
	अगर (WARN_ONCE(from < offset, "SUNRPC: misaligned data src=%u dst=%u\n",
		      from, offset))
		वापस 0;
	अगर (WARN_ONCE(offset > buf->page_len,
		      "SUNRPC: buffer overflow. offset=%u, page_len=%u\n",
		      offset, buf->page_len))
		वापस 0;

	/* Move page data to the left */
	shअगरt = from - offset;
	xdr_buf_pages_shअगरt_left(buf, from, len, shअगरt);

	bytes = xdr_stream_reमुख्यing(xdr);
	अगर (length > bytes)
		length = bytes;
	bytes -= length;

	xdr->buf->len -= shअगरt;
	xdr_set_page(xdr, offset + length, bytes);
	वापस length;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_align_data);

अचिन्हित पूर्णांक xdr_expand_hole(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक offset,
			     अचिन्हित पूर्णांक length)
अणु
	काष्ठा xdr_buf *buf = xdr->buf;
	अचिन्हित पूर्णांक from, to, shअगरt;

	xdr_realign_pages(xdr);
	from = xdr_page_pos(xdr);
	to = xdr_align_size(offset + length);

	/* Could the hole be behind us? */
	अगर (to > from) अणु
		अचिन्हित पूर्णांक buflen = buf->len - buf->head->iov_len;
		shअगरt = to - from;
		xdr_buf_try_expand(buf, shअगरt);
		xdr_buf_pages_shअगरt_right(buf, from, buflen, shअगरt);
		xdr_set_page(xdr, to, xdr_stream_reमुख्यing(xdr));
	पूर्ण अन्यथा अगर (to != from)
		xdr_align_data(xdr, to, 0);
	xdr_buf_pages_zero(buf, offset, length);

	वापस length;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_expand_hole);

/**
 * xdr_enter_page - decode data from the XDR page
 * @xdr: poपूर्णांकer to xdr_stream काष्ठा
 * @len: number of bytes of page data
 *
 * Moves data beyond the current poपूर्णांकer position from the XDR head[] buffer
 * पूर्णांकo the page list. Any data that lies beyond current position + "len"
 * bytes is moved पूर्णांकo the XDR tail[]. The current poपूर्णांकer is then
 * repositioned at the beginning of the first XDR page.
 */
व्योम xdr_enter_page(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक len)
अणु
	len = xdr_align_pages(xdr, len);
	/*
	 * Position current poपूर्णांकer at beginning of tail, and
	 * set reमुख्यing message length.
	 */
	अगर (len != 0)
		xdr_set_page_base(xdr, 0, len);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_enter_page);

अटल स्थिर काष्ठा kvec empty_iov = अणु.iov_base = शून्य, .iov_len = 0पूर्ण;

व्योम xdr_buf_from_iov(स्थिर काष्ठा kvec *iov, काष्ठा xdr_buf *buf)
अणु
	buf->head[0] = *iov;
	buf->tail[0] = empty_iov;
	buf->page_len = 0;
	buf->buflen = buf->len = iov->iov_len;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_buf_from_iov);

/**
 * xdr_buf_subsegment - set subbuf to a portion of buf
 * @buf: an xdr buffer
 * @subbuf: the result buffer
 * @base: beginning of range in bytes
 * @len: length of range in bytes
 *
 * sets @subbuf to an xdr buffer representing the portion of @buf of
 * length @len starting at offset @base.
 *
 * @buf and @subbuf may be poपूर्णांकers to the same काष्ठा xdr_buf.
 *
 * Returns -1 अगर base of length are out of bounds.
 */
पूर्णांक xdr_buf_subsegment(स्थिर काष्ठा xdr_buf *buf, काष्ठा xdr_buf *subbuf,
		       अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len)
अणु
	subbuf->buflen = subbuf->len = len;
	अगर (base < buf->head[0].iov_len) अणु
		subbuf->head[0].iov_base = buf->head[0].iov_base + base;
		subbuf->head[0].iov_len = min_t(अचिन्हित पूर्णांक, len,
						buf->head[0].iov_len - base);
		len -= subbuf->head[0].iov_len;
		base = 0;
	पूर्ण अन्यथा अणु
		base -= buf->head[0].iov_len;
		subbuf->head[0].iov_base = buf->head[0].iov_base;
		subbuf->head[0].iov_len = 0;
	पूर्ण

	अगर (base < buf->page_len) अणु
		subbuf->page_len = min(buf->page_len - base, len);
		base += buf->page_base;
		subbuf->page_base = base & ~PAGE_MASK;
		subbuf->pages = &buf->pages[base >> PAGE_SHIFT];
		len -= subbuf->page_len;
		base = 0;
	पूर्ण अन्यथा अणु
		base -= buf->page_len;
		subbuf->pages = buf->pages;
		subbuf->page_base = 0;
		subbuf->page_len = 0;
	पूर्ण

	अगर (base < buf->tail[0].iov_len) अणु
		subbuf->tail[0].iov_base = buf->tail[0].iov_base + base;
		subbuf->tail[0].iov_len = min_t(अचिन्हित पूर्णांक, len,
						buf->tail[0].iov_len - base);
		len -= subbuf->tail[0].iov_len;
		base = 0;
	पूर्ण अन्यथा अणु
		base -= buf->tail[0].iov_len;
		subbuf->tail[0].iov_base = buf->tail[0].iov_base;
		subbuf->tail[0].iov_len = 0;
	पूर्ण

	अगर (base || len)
		वापस -1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_buf_subsegment);

/**
 * xdr_stream_subsegment - set @subbuf to a portion of @xdr
 * @xdr: an xdr_stream set up क्रम decoding
 * @subbuf: the result buffer
 * @nbytes: length of @xdr to extract, in bytes
 *
 * Sets up @subbuf to represent a portion of @xdr. The portion
 * starts at the current offset in @xdr, and extends क्रम a length
 * of @nbytes. If this is successful, @xdr is advanced to the next
 * position following that portion.
 *
 * Return values:
 *   %true: @subbuf has been initialized, and @xdr has been advanced.
 *   %false: a bounds error has occurred
 */
bool xdr_stream_subsegment(काष्ठा xdr_stream *xdr, काष्ठा xdr_buf *subbuf,
			   अचिन्हित पूर्णांक nbytes)
अणु
	अचिन्हित पूर्णांक reमुख्यing, offset, len;

	अगर (xdr_buf_subsegment(xdr->buf, subbuf, xdr_stream_pos(xdr), nbytes))
		वापस false;

	अगर (subbuf->head[0].iov_len)
		अगर (!__xdr_अंतरभूत_decode(xdr, subbuf->head[0].iov_len))
			वापस false;

	reमुख्यing = subbuf->page_len;
	offset = subbuf->page_base;
	जबतक (reमुख्यing) अणु
		len = min_t(अचिन्हित पूर्णांक, reमुख्यing, PAGE_SIZE) - offset;

		अगर (xdr->p == xdr->end && !xdr_set_next_buffer(xdr))
			वापस false;
		अगर (!__xdr_अंतरभूत_decode(xdr, len))
			वापस false;

		reमुख्यing -= len;
		offset = 0;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_stream_subsegment);

/**
 * xdr_buf_trim - lop at most "len" bytes off the end of "buf"
 * @buf: buf to be trimmed
 * @len: number of bytes to reduce "buf" by
 *
 * Trim an xdr_buf by the given number of bytes by fixing up the lengths. Note
 * that it's possible that we'll trim less than that amount अगर the xdr_buf is
 * too small, or अगर (क्रम instance) it's all in the head and the parser has
 * alपढ़ोy पढ़ो too far पूर्णांकo it.
 */
व्योम xdr_buf_trim(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक len)
अणु
	माप_प्रकार cur;
	अचिन्हित पूर्णांक trim = len;

	अगर (buf->tail[0].iov_len) अणु
		cur = min_t(माप_प्रकार, buf->tail[0].iov_len, trim);
		buf->tail[0].iov_len -= cur;
		trim -= cur;
		अगर (!trim)
			जाओ fix_len;
	पूर्ण

	अगर (buf->page_len) अणु
		cur = min_t(अचिन्हित पूर्णांक, buf->page_len, trim);
		buf->page_len -= cur;
		trim -= cur;
		अगर (!trim)
			जाओ fix_len;
	पूर्ण

	अगर (buf->head[0].iov_len) अणु
		cur = min_t(माप_प्रकार, buf->head[0].iov_len, trim);
		buf->head[0].iov_len -= cur;
		trim -= cur;
	पूर्ण
fix_len:
	buf->len -= (len - trim);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_buf_trim);

अटल व्योम __पढ़ो_bytes_from_xdr_buf(स्थिर काष्ठा xdr_buf *subbuf,
				      व्योम *obj, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक this_len;

	this_len = min_t(अचिन्हित पूर्णांक, len, subbuf->head[0].iov_len);
	स_नकल(obj, subbuf->head[0].iov_base, this_len);
	len -= this_len;
	obj += this_len;
	this_len = min_t(अचिन्हित पूर्णांक, len, subbuf->page_len);
	_copy_from_pages(obj, subbuf->pages, subbuf->page_base, this_len);
	len -= this_len;
	obj += this_len;
	this_len = min_t(अचिन्हित पूर्णांक, len, subbuf->tail[0].iov_len);
	स_नकल(obj, subbuf->tail[0].iov_base, this_len);
पूर्ण

/* obj is assumed to poपूर्णांक to allocated memory of size at least len: */
पूर्णांक पढ़ो_bytes_from_xdr_buf(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base,
			    व्योम *obj, अचिन्हित पूर्णांक len)
अणु
	काष्ठा xdr_buf subbuf;
	पूर्णांक status;

	status = xdr_buf_subsegment(buf, &subbuf, base, len);
	अगर (status != 0)
		वापस status;
	__पढ़ो_bytes_from_xdr_buf(&subbuf, obj, len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पढ़ो_bytes_from_xdr_buf);

अटल व्योम __ग_लिखो_bytes_to_xdr_buf(स्थिर काष्ठा xdr_buf *subbuf,
				     व्योम *obj, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक this_len;

	this_len = min_t(अचिन्हित पूर्णांक, len, subbuf->head[0].iov_len);
	स_नकल(subbuf->head[0].iov_base, obj, this_len);
	len -= this_len;
	obj += this_len;
	this_len = min_t(अचिन्हित पूर्णांक, len, subbuf->page_len);
	_copy_to_pages(subbuf->pages, subbuf->page_base, obj, this_len);
	len -= this_len;
	obj += this_len;
	this_len = min_t(अचिन्हित पूर्णांक, len, subbuf->tail[0].iov_len);
	स_नकल(subbuf->tail[0].iov_base, obj, this_len);
पूर्ण

/* obj is assumed to poपूर्णांक to allocated memory of size at least len: */
पूर्णांक ग_लिखो_bytes_to_xdr_buf(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base,
			   व्योम *obj, अचिन्हित पूर्णांक len)
अणु
	काष्ठा xdr_buf subbuf;
	पूर्णांक status;

	status = xdr_buf_subsegment(buf, &subbuf, base, len);
	अगर (status != 0)
		वापस status;
	__ग_लिखो_bytes_to_xdr_buf(&subbuf, obj, len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ग_लिखो_bytes_to_xdr_buf);

पूर्णांक xdr_decode_word(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base, u32 *obj)
अणु
	__be32	raw;
	पूर्णांक	status;

	status = पढ़ो_bytes_from_xdr_buf(buf, base, &raw, माप(*obj));
	अगर (status)
		वापस status;
	*obj = be32_to_cpu(raw);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_decode_word);

पूर्णांक xdr_encode_word(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base, u32 obj)
अणु
	__be32	raw = cpu_to_be32(obj);

	वापस ग_लिखो_bytes_to_xdr_buf(buf, base, &raw, माप(obj));
पूर्ण
EXPORT_SYMBOL_GPL(xdr_encode_word);

/* Returns 0 on success, or अन्यथा a negative error code. */
अटल पूर्णांक xdr_xcode_array2(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base,
			    काष्ठा xdr_array2_desc *desc, पूर्णांक encode)
अणु
	अक्षर *elem = शून्य, *c;
	अचिन्हित पूर्णांक copied = 0, toकरो, avail_here;
	काष्ठा page **ppages = शून्य;
	पूर्णांक err;

	अगर (encode) अणु
		अगर (xdr_encode_word(buf, base, desc->array_len) != 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (xdr_decode_word(buf, base, &desc->array_len) != 0 ||
		    desc->array_len > desc->array_maxlen ||
		    (अचिन्हित दीर्घ) base + 4 + desc->array_len *
				    desc->elem_size > buf->len)
			वापस -EINVAL;
	पूर्ण
	base += 4;

	अगर (!desc->xcode)
		वापस 0;

	toकरो = desc->array_len * desc->elem_size;

	/* process head */
	अगर (toकरो && base < buf->head->iov_len) अणु
		c = buf->head->iov_base + base;
		avail_here = min_t(अचिन्हित पूर्णांक, toकरो,
				   buf->head->iov_len - base);
		toकरो -= avail_here;

		जबतक (avail_here >= desc->elem_size) अणु
			err = desc->xcode(desc, c);
			अगर (err)
				जाओ out;
			c += desc->elem_size;
			avail_here -= desc->elem_size;
		पूर्ण
		अगर (avail_here) अणु
			अगर (!elem) अणु
				elem = kदो_स्मृति(desc->elem_size, GFP_KERNEL);
				err = -ENOMEM;
				अगर (!elem)
					जाओ out;
			पूर्ण
			अगर (encode) अणु
				err = desc->xcode(desc, elem);
				अगर (err)
					जाओ out;
				स_नकल(c, elem, avail_here);
			पूर्ण अन्यथा
				स_नकल(elem, c, avail_here);
			copied = avail_here;
		पूर्ण
		base = buf->head->iov_len;  /* align to start of pages */
	पूर्ण

	/* process pages array */
	base -= buf->head->iov_len;
	अगर (toकरो && base < buf->page_len) अणु
		अचिन्हित पूर्णांक avail_page;

		avail_here = min(toकरो, buf->page_len - base);
		toकरो -= avail_here;

		base += buf->page_base;
		ppages = buf->pages + (base >> PAGE_SHIFT);
		base &= ~PAGE_MASK;
		avail_page = min_t(अचिन्हित पूर्णांक, PAGE_SIZE - base,
					avail_here);
		c = kmap(*ppages) + base;

		जबतक (avail_here) अणु
			avail_here -= avail_page;
			अगर (copied || avail_page < desc->elem_size) अणु
				अचिन्हित पूर्णांक l = min(avail_page,
					desc->elem_size - copied);
				अगर (!elem) अणु
					elem = kदो_स्मृति(desc->elem_size,
						       GFP_KERNEL);
					err = -ENOMEM;
					अगर (!elem)
						जाओ out;
				पूर्ण
				अगर (encode) अणु
					अगर (!copied) अणु
						err = desc->xcode(desc, elem);
						अगर (err)
							जाओ out;
					पूर्ण
					स_नकल(c, elem + copied, l);
					copied += l;
					अगर (copied == desc->elem_size)
						copied = 0;
				पूर्ण अन्यथा अणु
					स_नकल(elem + copied, c, l);
					copied += l;
					अगर (copied == desc->elem_size) अणु
						err = desc->xcode(desc, elem);
						अगर (err)
							जाओ out;
						copied = 0;
					पूर्ण
				पूर्ण
				avail_page -= l;
				c += l;
			पूर्ण
			जबतक (avail_page >= desc->elem_size) अणु
				err = desc->xcode(desc, c);
				अगर (err)
					जाओ out;
				c += desc->elem_size;
				avail_page -= desc->elem_size;
			पूर्ण
			अगर (avail_page) अणु
				अचिन्हित पूर्णांक l = min(avail_page,
					    desc->elem_size - copied);
				अगर (!elem) अणु
					elem = kदो_स्मृति(desc->elem_size,
						       GFP_KERNEL);
					err = -ENOMEM;
					अगर (!elem)
						जाओ out;
				पूर्ण
				अगर (encode) अणु
					अगर (!copied) अणु
						err = desc->xcode(desc, elem);
						अगर (err)
							जाओ out;
					पूर्ण
					स_नकल(c, elem + copied, l);
					copied += l;
					अगर (copied == desc->elem_size)
						copied = 0;
				पूर्ण अन्यथा अणु
					स_नकल(elem + copied, c, l);
					copied += l;
					अगर (copied == desc->elem_size) अणु
						err = desc->xcode(desc, elem);
						अगर (err)
							जाओ out;
						copied = 0;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (avail_here) अणु
				kunmap(*ppages);
				ppages++;
				c = kmap(*ppages);
			पूर्ण

			avail_page = min(avail_here,
				 (अचिन्हित पूर्णांक) PAGE_SIZE);
		पूर्ण
		base = buf->page_len;  /* align to start of tail */
	पूर्ण

	/* process tail */
	base -= buf->page_len;
	अगर (toकरो) अणु
		c = buf->tail->iov_base + base;
		अगर (copied) अणु
			अचिन्हित पूर्णांक l = desc->elem_size - copied;

			अगर (encode)
				स_नकल(c, elem + copied, l);
			अन्यथा अणु
				स_नकल(elem + copied, c, l);
				err = desc->xcode(desc, elem);
				अगर (err)
					जाओ out;
			पूर्ण
			toकरो -= l;
			c += l;
		पूर्ण
		जबतक (toकरो) अणु
			err = desc->xcode(desc, c);
			अगर (err)
				जाओ out;
			c += desc->elem_size;
			toकरो -= desc->elem_size;
		पूर्ण
	पूर्ण
	err = 0;

out:
	kमुक्त(elem);
	अगर (ppages)
		kunmap(*ppages);
	वापस err;
पूर्ण

पूर्णांक xdr_decode_array2(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base,
		      काष्ठा xdr_array2_desc *desc)
अणु
	अगर (base >= buf->len)
		वापस -EINVAL;

	वापस xdr_xcode_array2(buf, base, desc, 0);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_decode_array2);

पूर्णांक xdr_encode_array2(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base,
		      काष्ठा xdr_array2_desc *desc)
अणु
	अगर ((अचिन्हित दीर्घ) base + 4 + desc->array_len * desc->elem_size >
	    buf->head->iov_len + buf->page_len + buf->tail->iov_len)
		वापस -EINVAL;

	वापस xdr_xcode_array2(buf, base, desc, 1);
पूर्ण
EXPORT_SYMBOL_GPL(xdr_encode_array2);

पूर्णांक xdr_process_buf(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक offset,
		    अचिन्हित पूर्णांक len,
		    पूर्णांक (*actor)(काष्ठा scatterlist *, व्योम *), व्योम *data)
अणु
	पूर्णांक i, ret = 0;
	अचिन्हित पूर्णांक page_len, thislen, page_offset;
	काष्ठा scatterlist      sg[1];

	sg_init_table(sg, 1);

	अगर (offset >= buf->head[0].iov_len) अणु
		offset -= buf->head[0].iov_len;
	पूर्ण अन्यथा अणु
		thislen = buf->head[0].iov_len - offset;
		अगर (thislen > len)
			thislen = len;
		sg_set_buf(sg, buf->head[0].iov_base + offset, thislen);
		ret = actor(sg, data);
		अगर (ret)
			जाओ out;
		offset = 0;
		len -= thislen;
	पूर्ण
	अगर (len == 0)
		जाओ out;

	अगर (offset >= buf->page_len) अणु
		offset -= buf->page_len;
	पूर्ण अन्यथा अणु
		page_len = buf->page_len - offset;
		अगर (page_len > len)
			page_len = len;
		len -= page_len;
		page_offset = (offset + buf->page_base) & (PAGE_SIZE - 1);
		i = (offset + buf->page_base) >> PAGE_SHIFT;
		thislen = PAGE_SIZE - page_offset;
		करो अणु
			अगर (thislen > page_len)
				thislen = page_len;
			sg_set_page(sg, buf->pages[i], thislen, page_offset);
			ret = actor(sg, data);
			अगर (ret)
				जाओ out;
			page_len -= thislen;
			i++;
			page_offset = 0;
			thislen = PAGE_SIZE;
		पूर्ण जबतक (page_len != 0);
		offset = 0;
	पूर्ण
	अगर (len == 0)
		जाओ out;
	अगर (offset < buf->tail[0].iov_len) अणु
		thislen = buf->tail[0].iov_len - offset;
		अगर (thislen > len)
			thislen = len;
		sg_set_buf(sg, buf->tail[0].iov_base + offset, thislen);
		ret = actor(sg, data);
		len -= thislen;
	पूर्ण
	अगर (len != 0)
		ret = -EINVAL;
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_process_buf);

/**
 * xdr_stream_decode_opaque - Decode variable length opaque
 * @xdr: poपूर्णांकer to xdr_stream
 * @ptr: location to store opaque data
 * @size: size of storage buffer @ptr
 *
 * Return values:
 *   On success, वापसs size of object stored in *@ptr
 *   %-EBADMSG on XDR buffer overflow
 *   %-EMSGSIZE on overflow of storage buffer @ptr
 */
sमाप_प्रकार xdr_stream_decode_opaque(काष्ठा xdr_stream *xdr, व्योम *ptr, माप_प्रकार size)
अणु
	sमाप_प्रकार ret;
	व्योम *p;

	ret = xdr_stream_decode_opaque_अंतरभूत(xdr, &p, size);
	अगर (ret <= 0)
		वापस ret;
	स_नकल(ptr, p, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_stream_decode_opaque);

/**
 * xdr_stream_decode_opaque_dup - Decode and duplicate variable length opaque
 * @xdr: poपूर्णांकer to xdr_stream
 * @ptr: location to store poपूर्णांकer to opaque data
 * @maxlen: maximum acceptable object size
 * @gfp_flags: GFP mask to use
 *
 * Return values:
 *   On success, वापसs size of object stored in *@ptr
 *   %-EBADMSG on XDR buffer overflow
 *   %-EMSGSIZE अगर the size of the object would exceed @maxlen
 *   %-ENOMEM on memory allocation failure
 */
sमाप_प्रकार xdr_stream_decode_opaque_dup(काष्ठा xdr_stream *xdr, व्योम **ptr,
		माप_प्रकार maxlen, gfp_t gfp_flags)
अणु
	sमाप_प्रकार ret;
	व्योम *p;

	ret = xdr_stream_decode_opaque_अंतरभूत(xdr, &p, maxlen);
	अगर (ret > 0) अणु
		*ptr = kmemdup(p, ret, gfp_flags);
		अगर (*ptr != शून्य)
			वापस ret;
		ret = -ENOMEM;
	पूर्ण
	*ptr = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_stream_decode_opaque_dup);

/**
 * xdr_stream_decode_string - Decode variable length string
 * @xdr: poपूर्णांकer to xdr_stream
 * @str: location to store string
 * @size: size of storage buffer @str
 *
 * Return values:
 *   On success, वापसs length of NUL-terminated string stored in *@str
 *   %-EBADMSG on XDR buffer overflow
 *   %-EMSGSIZE on overflow of storage buffer @str
 */
sमाप_प्रकार xdr_stream_decode_string(काष्ठा xdr_stream *xdr, अक्षर *str, माप_प्रकार size)
अणु
	sमाप_प्रकार ret;
	व्योम *p;

	ret = xdr_stream_decode_opaque_अंतरभूत(xdr, &p, size);
	अगर (ret > 0) अणु
		स_नकल(str, p, ret);
		str[ret] = '\0';
		वापस म_माप(str);
	पूर्ण
	*str = '\0';
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_stream_decode_string);

/**
 * xdr_stream_decode_string_dup - Decode and duplicate variable length string
 * @xdr: poपूर्णांकer to xdr_stream
 * @str: location to store poपूर्णांकer to string
 * @maxlen: maximum acceptable string length
 * @gfp_flags: GFP mask to use
 *
 * Return values:
 *   On success, वापसs length of NUL-terminated string stored in *@ptr
 *   %-EBADMSG on XDR buffer overflow
 *   %-EMSGSIZE अगर the size of the string would exceed @maxlen
 *   %-ENOMEM on memory allocation failure
 */
sमाप_प्रकार xdr_stream_decode_string_dup(काष्ठा xdr_stream *xdr, अक्षर **str,
		माप_प्रकार maxlen, gfp_t gfp_flags)
अणु
	व्योम *p;
	sमाप_प्रकार ret;

	ret = xdr_stream_decode_opaque_अंतरभूत(xdr, &p, maxlen);
	अगर (ret > 0) अणु
		अक्षर *s = kmemdup_nul(p, ret, gfp_flags);
		अगर (s != शून्य) अणु
			*str = s;
			वापस म_माप(s);
		पूर्ण
		ret = -ENOMEM;
	पूर्ण
	*str = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xdr_stream_decode_string_dup);
