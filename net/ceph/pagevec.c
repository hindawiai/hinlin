<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/namei.h>
#समावेश <linux/ग_लिखोback.h>

#समावेश <linux/ceph/libceph.h>

व्योम ceph_put_page_vector(काष्ठा page **pages, पूर्णांक num_pages, bool dirty)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_pages; i++) अणु
		अगर (dirty)
			set_page_dirty_lock(pages[i]);
		put_page(pages[i]);
	पूर्ण
	kvमुक्त(pages);
पूर्ण
EXPORT_SYMBOL(ceph_put_page_vector);

व्योम ceph_release_page_vector(काष्ठा page **pages, पूर्णांक num_pages)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_pages; i++)
		__मुक्त_pages(pages[i], 0);
	kमुक्त(pages);
पूर्ण
EXPORT_SYMBOL(ceph_release_page_vector);

/*
 * allocate a vector new pages
 */
काष्ठा page **ceph_alloc_page_vector(पूर्णांक num_pages, gfp_t flags)
अणु
	काष्ठा page **pages;
	पूर्णांक i;

	pages = kदो_स्मृति_array(num_pages, माप(*pages), flags);
	अगर (!pages)
		वापस ERR_PTR(-ENOMEM);
	क्रम (i = 0; i < num_pages; i++) अणु
		pages[i] = __page_cache_alloc(flags);
		अगर (pages[i] == शून्य) अणु
			ceph_release_page_vector(pages, i);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण
	वापस pages;
पूर्ण
EXPORT_SYMBOL(ceph_alloc_page_vector);

/*
 * copy user data पूर्णांकo a page vector
 */
पूर्णांक ceph_copy_user_to_page_vector(काष्ठा page **pages,
					 स्थिर व्योम __user *data,
					 loff_t off, माप_प्रकार len)
अणु
	पूर्णांक i = 0;
	पूर्णांक po = off & ~PAGE_MASK;
	पूर्णांक left = len;
	पूर्णांक l, bad;

	जबतक (left > 0) अणु
		l = min_t(पूर्णांक, PAGE_SIZE-po, left);
		bad = copy_from_user(page_address(pages[i]) + po, data, l);
		अगर (bad == l)
			वापस -EFAULT;
		data += l - bad;
		left -= l - bad;
		po += l - bad;
		अगर (po == PAGE_SIZE) अणु
			po = 0;
			i++;
		पूर्ण
	पूर्ण
	वापस len;
पूर्ण
EXPORT_SYMBOL(ceph_copy_user_to_page_vector);

व्योम ceph_copy_to_page_vector(काष्ठा page **pages,
				    स्थिर व्योम *data,
				    loff_t off, माप_प्रकार len)
अणु
	पूर्णांक i = 0;
	माप_प्रकार po = off & ~PAGE_MASK;
	माप_प्रकार left = len;

	जबतक (left > 0) अणु
		माप_प्रकार l = min_t(माप_प्रकार, PAGE_SIZE-po, left);

		स_नकल(page_address(pages[i]) + po, data, l);
		data += l;
		left -= l;
		po += l;
		अगर (po == PAGE_SIZE) अणु
			po = 0;
			i++;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ceph_copy_to_page_vector);

व्योम ceph_copy_from_page_vector(काष्ठा page **pages,
				    व्योम *data,
				    loff_t off, माप_प्रकार len)
अणु
	पूर्णांक i = 0;
	माप_प्रकार po = off & ~PAGE_MASK;
	माप_प्रकार left = len;

	जबतक (left > 0) अणु
		माप_प्रकार l = min_t(माप_प्रकार, PAGE_SIZE-po, left);

		स_नकल(data, page_address(pages[i]) + po, l);
		data += l;
		left -= l;
		po += l;
		अगर (po == PAGE_SIZE) अणु
			po = 0;
			i++;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ceph_copy_from_page_vector);

/*
 * Zero an extent within a page vector.  Offset is relative to the
 * start of the first page.
 */
व्योम ceph_zero_page_vector_range(पूर्णांक off, पूर्णांक len, काष्ठा page **pages)
अणु
	पूर्णांक i = off >> PAGE_SHIFT;

	off &= ~PAGE_MASK;

	करोut("zero_page_vector_page %u~%u\n", off, len);

	/* leading partial page? */
	अगर (off) अणु
		पूर्णांक end = min((पूर्णांक)PAGE_SIZE, off + len);
		करोut("zeroing %d %p head from %d\n", i, pages[i],
		     (पूर्णांक)off);
		zero_user_segment(pages[i], off, end);
		len -= (end - off);
		i++;
	पूर्ण
	जबतक (len >= PAGE_SIZE) अणु
		करोut("zeroing %d %p len=%d\n", i, pages[i], len);
		zero_user_segment(pages[i], 0, PAGE_SIZE);
		len -= PAGE_SIZE;
		i++;
	पूर्ण
	/* trailing partial page? */
	अगर (len) अणु
		करोut("zeroing %d %p tail to %d\n", i, pages[i], (पूर्णांक)len);
		zero_user_segment(pages[i], 0, len);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ceph_zero_page_vector_range);
