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
#समावेश <linux/percpu.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/export.h>

#समावेश "rds.h"

/*
 * This file implements a माला_लोockopt() call which copies a set of fixed
 * sized काष्ठाs पूर्णांकo a user-specअगरied buffer as a means of providing
 * पढ़ो-only inक्रमmation about RDS.
 *
 * For a given inक्रमmation source there are a given number of fixed sized
 * काष्ठाs at a given समय.  The काष्ठाs are only copied अगर the user-specअगरied
 * buffer is big enough.  The destination pages that make up the buffer
 * are pinned क्रम the duration of the copy.
 *
 * This gives us the following benefits:
 *
 * - simple implementation, no copy "position" across multiple calls
 * - consistent snapshot of an info source
 * - atomic copy works well with whatever locking info source has
 * - one portable tool to get rds info across implementations
 * - दीर्घ-lived tool can get info without allocating
 *
 * at the following costs:
 *
 * - info source copy must be pinned, may be "large"
 */

काष्ठा rds_info_iterator अणु
	काष्ठा page **pages;
	व्योम *addr;
	अचिन्हित दीर्घ offset;
पूर्ण;

अटल DEFINE_SPINLOCK(rds_info_lock);
अटल rds_info_func rds_info_funcs[RDS_INFO_LAST - RDS_INFO_FIRST + 1];

व्योम rds_info_रेजिस्टर_func(पूर्णांक optname, rds_info_func func)
अणु
	पूर्णांक offset = optname - RDS_INFO_FIRST;

	BUG_ON(optname < RDS_INFO_FIRST || optname > RDS_INFO_LAST);

	spin_lock(&rds_info_lock);
	BUG_ON(rds_info_funcs[offset]);
	rds_info_funcs[offset] = func;
	spin_unlock(&rds_info_lock);
पूर्ण
EXPORT_SYMBOL_GPL(rds_info_रेजिस्टर_func);

व्योम rds_info_deरेजिस्टर_func(पूर्णांक optname, rds_info_func func)
अणु
	पूर्णांक offset = optname - RDS_INFO_FIRST;

	BUG_ON(optname < RDS_INFO_FIRST || optname > RDS_INFO_LAST);

	spin_lock(&rds_info_lock);
	BUG_ON(rds_info_funcs[offset] != func);
	rds_info_funcs[offset] = शून्य;
	spin_unlock(&rds_info_lock);
पूर्ण
EXPORT_SYMBOL_GPL(rds_info_deरेजिस्टर_func);

/*
 * Typically we hold an atomic kmap across multiple rds_info_copy() calls
 * because the kmap is so expensive.  This must be called beक्रमe using blocking
 * operations जबतक holding the mapping and as the iterator is torn करोwn.
 */
व्योम rds_info_iter_unmap(काष्ठा rds_info_iterator *iter)
अणु
	अगर (iter->addr) अणु
		kunmap_atomic(iter->addr);
		iter->addr = शून्य;
	पूर्ण
पूर्ण

/*
 * get_user_pages() called flush_dcache_page() on the pages क्रम us.
 */
व्योम rds_info_copy(काष्ठा rds_info_iterator *iter, व्योम *data,
		   अचिन्हित दीर्घ bytes)
अणु
	अचिन्हित दीर्घ this;

	जबतक (bytes) अणु
		अगर (!iter->addr)
			iter->addr = kmap_atomic(*iter->pages);

		this = min(bytes, PAGE_SIZE - iter->offset);

		rdsdebug("page %p addr %p offset %lu this %lu data %p "
			  "bytes %lu\n", *iter->pages, iter->addr,
			  iter->offset, this, data, bytes);

		स_नकल(iter->addr + iter->offset, data, this);

		data += this;
		bytes -= this;
		iter->offset += this;

		अगर (iter->offset == PAGE_SIZE) अणु
			kunmap_atomic(iter->addr);
			iter->addr = शून्य;
			iter->offset = 0;
			iter->pages++;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rds_info_copy);

/*
 * @optval poपूर्णांकs to the userspace buffer that the inक्रमmation snapshot
 * will be copied पूर्णांकo.
 *
 * @optlen on input is the size of the buffer in userspace.  @optlen
 * on output is the size of the requested snapshot in bytes.
 *
 * This function वापसs -त्रुटि_सं अगर there is a failure, particularly -ENOSPC
 * अगर the given userspace buffer was not large enough to fit the snapshot.
 * On success it वापसs the positive number of bytes of each array element
 * in the snapshot.
 */
पूर्णांक rds_info_माला_लोockopt(काष्ठा socket *sock, पूर्णांक optname, अक्षर __user *optval,
			पूर्णांक __user *optlen)
अणु
	काष्ठा rds_info_iterator iter;
	काष्ठा rds_info_lengths lens;
	अचिन्हित दीर्घ nr_pages = 0;
	अचिन्हित दीर्घ start;
	rds_info_func func;
	काष्ठा page **pages = शून्य;
	पूर्णांक ret;
	पूर्णांक len;
	पूर्णांक total;

	अगर (get_user(len, optlen)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	/* check क्रम all kinds of wrapping and the like */
	start = (अचिन्हित दीर्घ)optval;
	अगर (len < 0 || len > पूर्णांक_उच्च - PAGE_SIZE + 1 || start + len < start) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* a 0 len call is just trying to probe its length */
	अगर (len == 0)
		जाओ call_func;

	nr_pages = (PAGE_ALIGN(start + len) - (start & PAGE_MASK))
			>> PAGE_SHIFT;

	pages = kदो_स्मृति_array(nr_pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ret = pin_user_pages_fast(start, nr_pages, FOLL_WRITE, pages);
	अगर (ret != nr_pages) अणु
		अगर (ret > 0)
			nr_pages = ret;
		अन्यथा
			nr_pages = 0;
		ret = -EAGAIN; /* XXX ? */
		जाओ out;
	पूर्ण

	rdsdebug("len %d nr_pages %lu\n", len, nr_pages);

call_func:
	func = rds_info_funcs[optname - RDS_INFO_FIRST];
	अगर (!func) अणु
		ret = -ENOPROTOOPT;
		जाओ out;
	पूर्ण

	iter.pages = pages;
	iter.addr = शून्य;
	iter.offset = start & (PAGE_SIZE - 1);

	func(sock, len, &iter, &lens);
	BUG_ON(lens.each == 0);

	total = lens.nr * lens.each;

	rds_info_iter_unmap(&iter);

	अगर (total > len) अणु
		len = total;
		ret = -ENOSPC;
	पूर्ण अन्यथा अणु
		len = total;
		ret = lens.each;
	पूर्ण

	अगर (put_user(len, optlen))
		ret = -EFAULT;

out:
	अगर (pages)
		unpin_user_pages(pages, nr_pages);
	kमुक्त(pages);

	वापस ret;
पूर्ण
