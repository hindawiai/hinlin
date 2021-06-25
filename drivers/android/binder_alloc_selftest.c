<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* binder_alloc_selftest.c
 *
 * Android IPC Subप्रणाली
 *
 * Copyright (C) 2017 Google, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mm_types.h>
#समावेश <linux/err.h>
#समावेश "binder_alloc.h"

#घोषणा BUFFER_NUM 5
#घोषणा BUFFER_MIN_SIZE (PAGE_SIZE / 8)

अटल bool binder_selftest_run = true;
अटल पूर्णांक binder_selftest_failures;
अटल DEFINE_MUTEX(binder_selftest_lock);

/**
 * क्रमागत buf_end_align_type - Page alignment of a buffer
 * end with regard to the end of the previous buffer.
 *
 * In the pictures below, buf2 refers to the buffer we
 * are aligning. buf1 refers to previous buffer by addr.
 * Symbol [ means the start of a buffer, ] means the end
 * of a buffer, and | means page boundaries.
 */
क्रमागत buf_end_align_type अणु
	/**
	 * @SAME_PAGE_UNALIGNED: The end of this buffer is on
	 * the same page as the end of the previous buffer and
	 * is not page aligned. Examples:
	 * buf1 ][ buf2 ][ ...
	 * buf1 ]|[ buf2 ][ ...
	 */
	SAME_PAGE_UNALIGNED = 0,
	/**
	 * @SAME_PAGE_ALIGNED: When the end of the previous buffer
	 * is not page aligned, the end of this buffer is on the
	 * same page as the end of the previous buffer and is page
	 * aligned. When the previous buffer is page aligned, the
	 * end of this buffer is aligned to the next page boundary.
	 * Examples:
	 * buf1 ][ buf2 ]| ...
	 * buf1 ]|[ buf2 ]| ...
	 */
	SAME_PAGE_ALIGNED,
	/**
	 * @NEXT_PAGE_UNALIGNED: The end of this buffer is on
	 * the page next to the end of the previous buffer and
	 * is not page aligned. Examples:
	 * buf1 ][ buf2 | buf2 ][ ...
	 * buf1 ]|[ buf2 | buf2 ][ ...
	 */
	NEXT_PAGE_UNALIGNED,
	/**
	 * @NEXT_PAGE_ALIGNED: The end of this buffer is on
	 * the page next to the end of the previous buffer and
	 * is page aligned. Examples:
	 * buf1 ][ buf2 | buf2 ]| ...
	 * buf1 ]|[ buf2 | buf2 ]| ...
	 */
	NEXT_PAGE_ALIGNED,
	/**
	 * @NEXT_NEXT_UNALIGNED: The end of this buffer is on
	 * the page that follows the page after the end of the
	 * previous buffer and is not page aligned. Examples:
	 * buf1 ][ buf2 | buf2 | buf2 ][ ...
	 * buf1 ]|[ buf2 | buf2 | buf2 ][ ...
	 */
	NEXT_NEXT_UNALIGNED,
	LOOP_END,
पूर्ण;

अटल व्योम pr_err_size_seq(माप_प्रकार *sizes, पूर्णांक *seq)
अणु
	पूर्णांक i;

	pr_err("alloc sizes: ");
	क्रम (i = 0; i < BUFFER_NUM; i++)
		pr_cont("[%zu]", sizes[i]);
	pr_cont("\n");
	pr_err("free seq: ");
	क्रम (i = 0; i < BUFFER_NUM; i++)
		pr_cont("[%d]", seq[i]);
	pr_cont("\n");
पूर्ण

अटल bool check_buffer_pages_allocated(काष्ठा binder_alloc *alloc,
					 काष्ठा binder_buffer *buffer,
					 माप_प्रकार size)
अणु
	व्योम __user *page_addr;
	व्योम __user *end;
	पूर्णांक page_index;

	end = (व्योम __user *)PAGE_ALIGN((uपूर्णांकptr_t)buffer->user_data + size);
	page_addr = buffer->user_data;
	क्रम (; page_addr < end; page_addr += PAGE_SIZE) अणु
		page_index = (page_addr - alloc->buffer) / PAGE_SIZE;
		अगर (!alloc->pages[page_index].page_ptr ||
		    !list_empty(&alloc->pages[page_index].lru)) अणु
			pr_err("expect alloc but is %s at page index %d\n",
			       alloc->pages[page_index].page_ptr ?
			       "lru" : "free", page_index);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम binder_selftest_alloc_buf(काष्ठा binder_alloc *alloc,
				      काष्ठा binder_buffer *buffers[],
				      माप_प्रकार *sizes, पूर्णांक *seq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BUFFER_NUM; i++) अणु
		buffers[i] = binder_alloc_new_buf(alloc, sizes[i], 0, 0, 0, 0);
		अगर (IS_ERR(buffers[i]) ||
		    !check_buffer_pages_allocated(alloc, buffers[i],
						  sizes[i])) अणु
			pr_err_size_seq(sizes, seq);
			binder_selftest_failures++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम binder_selftest_मुक्त_buf(काष्ठा binder_alloc *alloc,
				     काष्ठा binder_buffer *buffers[],
				     माप_प्रकार *sizes, पूर्णांक *seq, माप_प्रकार end)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BUFFER_NUM; i++)
		binder_alloc_मुक्त_buf(alloc, buffers[seq[i]]);

	क्रम (i = 0; i < end / PAGE_SIZE; i++) अणु
		/**
		 * Error message on a मुक्त page can be false positive
		 * अगर binder shrinker ran during binder_alloc_मुक्त_buf
		 * calls above.
		 */
		अगर (list_empty(&alloc->pages[i].lru)) अणु
			pr_err_size_seq(sizes, seq);
			pr_err("expect lru but is %s at page index %d\n",
			       alloc->pages[i].page_ptr ? "alloc" : "free", i);
			binder_selftest_failures++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम binder_selftest_मुक्त_page(काष्ठा binder_alloc *alloc)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ count;

	जबतक ((count = list_lru_count(&binder_alloc_lru))) अणु
		list_lru_walk(&binder_alloc_lru, binder_alloc_मुक्त_page,
			      शून्य, count);
	पूर्ण

	क्रम (i = 0; i < (alloc->buffer_size / PAGE_SIZE); i++) अणु
		अगर (alloc->pages[i].page_ptr) अणु
			pr_err("expect free but is %s at page index %d\n",
			       list_empty(&alloc->pages[i].lru) ?
			       "alloc" : "lru", i);
			binder_selftest_failures++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम binder_selftest_alloc_मुक्त(काष्ठा binder_alloc *alloc,
				       माप_प्रकार *sizes, पूर्णांक *seq, माप_प्रकार end)
अणु
	काष्ठा binder_buffer *buffers[BUFFER_NUM];

	binder_selftest_alloc_buf(alloc, buffers, sizes, seq);
	binder_selftest_मुक्त_buf(alloc, buffers, sizes, seq, end);

	/* Allocate from lru. */
	binder_selftest_alloc_buf(alloc, buffers, sizes, seq);
	अगर (list_lru_count(&binder_alloc_lru))
		pr_err("lru list should be empty but is not\n");

	binder_selftest_मुक्त_buf(alloc, buffers, sizes, seq, end);
	binder_selftest_मुक्त_page(alloc);
पूर्ण

अटल bool is_dup(पूर्णांक *seq, पूर्णांक index, पूर्णांक val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < index; i++) अणु
		अगर (seq[i] == val)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Generate BUFFER_NUM factorial मुक्त orders. */
अटल व्योम binder_selftest_मुक्त_seq(काष्ठा binder_alloc *alloc,
				     माप_प्रकार *sizes, पूर्णांक *seq,
				     पूर्णांक index, माप_प्रकार end)
अणु
	पूर्णांक i;

	अगर (index == BUFFER_NUM) अणु
		binder_selftest_alloc_मुक्त(alloc, sizes, seq, end);
		वापस;
	पूर्ण
	क्रम (i = 0; i < BUFFER_NUM; i++) अणु
		अगर (is_dup(seq, index, i))
			जारी;
		seq[index] = i;
		binder_selftest_मुक्त_seq(alloc, sizes, seq, index + 1, end);
	पूर्ण
पूर्ण

अटल व्योम binder_selftest_alloc_size(काष्ठा binder_alloc *alloc,
				       माप_प्रकार *end_offset)
अणु
	पूर्णांक i;
	पूर्णांक seq[BUFFER_NUM] = अणु0पूर्ण;
	माप_प्रकार front_sizes[BUFFER_NUM];
	माप_प्रकार back_sizes[BUFFER_NUM];
	माप_प्रकार last_offset, offset = 0;

	क्रम (i = 0; i < BUFFER_NUM; i++) अणु
		last_offset = offset;
		offset = end_offset[i];
		front_sizes[i] = offset - last_offset;
		back_sizes[BUFFER_NUM - i - 1] = front_sizes[i];
	पूर्ण
	/*
	 * Buffers share the first or last few pages.
	 * Only BUFFER_NUM - 1 buffer sizes are adjustable since
	 * we need one giant buffer beक्रमe getting to the last page.
	 */
	back_sizes[0] += alloc->buffer_size - end_offset[BUFFER_NUM - 1];
	binder_selftest_मुक्त_seq(alloc, front_sizes, seq, 0,
				 end_offset[BUFFER_NUM - 1]);
	binder_selftest_मुक्त_seq(alloc, back_sizes, seq, 0, alloc->buffer_size);
पूर्ण

अटल व्योम binder_selftest_alloc_offset(काष्ठा binder_alloc *alloc,
					 माप_प्रकार *end_offset, पूर्णांक index)
अणु
	पूर्णांक align;
	माप_प्रकार end, prev;

	अगर (index == BUFFER_NUM) अणु
		binder_selftest_alloc_size(alloc, end_offset);
		वापस;
	पूर्ण
	prev = index == 0 ? 0 : end_offset[index - 1];
	end = prev;

	BUILD_BUG_ON(BUFFER_MIN_SIZE * BUFFER_NUM >= PAGE_SIZE);

	क्रम (align = SAME_PAGE_UNALIGNED; align < LOOP_END; align++) अणु
		अगर (align % 2)
			end = ALIGN(end, PAGE_SIZE);
		अन्यथा
			end += BUFFER_MIN_SIZE;
		end_offset[index] = end;
		binder_selftest_alloc_offset(alloc, end_offset, index + 1);
	पूर्ण
पूर्ण

/**
 * binder_selftest_alloc() - Test alloc and मुक्त of buffer pages.
 * @alloc: Poपूर्णांकer to alloc काष्ठा.
 *
 * Allocate BUFFER_NUM buffers to cover all page alignment हालs,
 * then मुक्त them in all orders possible. Check that pages are
 * correctly allocated, put onto lru when buffers are मुक्तd, and
 * are मुक्तd when binder_alloc_मुक्त_page is called.
 */
व्योम binder_selftest_alloc(काष्ठा binder_alloc *alloc)
अणु
	माप_प्रकार end_offset[BUFFER_NUM];

	अगर (!binder_selftest_run)
		वापस;
	mutex_lock(&binder_selftest_lock);
	अगर (!binder_selftest_run || !alloc->vma)
		जाओ करोne;
	pr_info("STARTED\n");
	binder_selftest_alloc_offset(alloc, end_offset, 0);
	binder_selftest_run = false;
	अगर (binder_selftest_failures > 0)
		pr_info("%d tests FAILED\n", binder_selftest_failures);
	अन्यथा
		pr_info("PASSED\n");

करोne:
	mutex_unlock(&binder_selftest_lock);
पूर्ण
