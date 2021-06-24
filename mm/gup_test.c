<शैली गुरु>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/debugfs.h>
#समावेश "gup_test.h"

अटल व्योम put_back_pages(अचिन्हित पूर्णांक cmd, काष्ठा page **pages,
			   अचिन्हित दीर्घ nr_pages, अचिन्हित पूर्णांक gup_test_flags)
अणु
	अचिन्हित दीर्घ i;

	चयन (cmd) अणु
	हाल GUP_FAST_BENCHMARK:
	हाल GUP_BASIC_TEST:
		क्रम (i = 0; i < nr_pages; i++)
			put_page(pages[i]);
		अवरोध;

	हाल PIN_FAST_BENCHMARK:
	हाल PIN_BASIC_TEST:
	हाल PIN_LONGTERM_BENCHMARK:
		unpin_user_pages(pages, nr_pages);
		अवरोध;
	हाल DUMP_USER_PAGES_TEST:
		अगर (gup_test_flags & GUP_TEST_FLAG_DUMP_PAGES_USE_PIN) अणु
			unpin_user_pages(pages, nr_pages);
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < nr_pages; i++)
				put_page(pages[i]);

		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम verअगरy_dma_pinned(अचिन्हित पूर्णांक cmd, काष्ठा page **pages,
			      अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ i;
	काष्ठा page *page;

	चयन (cmd) अणु
	हाल PIN_FAST_BENCHMARK:
	हाल PIN_BASIC_TEST:
	हाल PIN_LONGTERM_BENCHMARK:
		क्रम (i = 0; i < nr_pages; i++) अणु
			page = pages[i];
			अगर (WARN(!page_maybe_dma_pinned(page),
				 "pages[%lu] is NOT dma-pinned\n", i)) अणु

				dump_page(page, "gup_test failure");
				अवरोध;
			पूर्ण अन्यथा अगर (cmd == PIN_LONGTERM_BENCHMARK &&
				WARN(!is_pinnable_page(page),
				     "pages[%lu] is NOT pinnable but pinned\n",
				     i)) अणु
				dump_page(page, "gup_test failure");
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dump_pages_test(काष्ठा gup_test *gup, काष्ठा page **pages,
			    अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित पूर्णांक index_to_dump;
	अचिन्हित पूर्णांक i;

	/*
	 * Zero out any user-supplied page index that is out of range. Remember:
	 * .which_pages[] contains a 1-based set of page indices.
	 */
	क्रम (i = 0; i < GUP_TEST_MAX_PAGES_TO_DUMP; i++) अणु
		अगर (gup->which_pages[i] > nr_pages) अणु
			pr_warn("ZEROING due to out of range: .which_pages[%u]: %u\n",
				i, gup->which_pages[i]);
			gup->which_pages[i] = 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < GUP_TEST_MAX_PAGES_TO_DUMP; i++) अणु
		index_to_dump = gup->which_pages[i];

		अगर (index_to_dump) अणु
			index_to_dump--; // Decode from 1-based, to 0-based
			pr_info("---- page #%u, starting from user virt addr: 0x%llx\n",
				index_to_dump, gup->addr);
			dump_page(pages[index_to_dump],
				  "gup_test: dump_pages() test");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __gup_test_ioctl(अचिन्हित पूर्णांक cmd,
		काष्ठा gup_test *gup)
अणु
	kसमय_प्रकार start_समय, end_समय;
	अचिन्हित दीर्घ i, nr_pages, addr, next;
	दीर्घ nr;
	काष्ठा page **pages;
	पूर्णांक ret = 0;
	bool needs_mmap_lock =
		cmd != GUP_FAST_BENCHMARK && cmd != PIN_FAST_BENCHMARK;

	अगर (gup->size > अच_दीर्घ_उच्च)
		वापस -EINVAL;

	nr_pages = gup->size / PAGE_SIZE;
	pages = kvसुस्मृति(nr_pages, माप(व्योम *), GFP_KERNEL);
	अगर (!pages)
		वापस -ENOMEM;

	अगर (needs_mmap_lock && mmap_पढ़ो_lock_समाप्तable(current->mm)) अणु
		ret = -EINTR;
		जाओ मुक्त_pages;
	पूर्ण

	i = 0;
	nr = gup->nr_pages_per_call;
	start_समय = kसमय_get();
	क्रम (addr = gup->addr; addr < gup->addr + gup->size; addr = next) अणु
		अगर (nr != gup->nr_pages_per_call)
			अवरोध;

		next = addr + nr * PAGE_SIZE;
		अगर (next > gup->addr + gup->size) अणु
			next = gup->addr + gup->size;
			nr = (next - addr) / PAGE_SIZE;
		पूर्ण

		चयन (cmd) अणु
		हाल GUP_FAST_BENCHMARK:
			nr = get_user_pages_fast(addr, nr, gup->gup_flags,
						 pages + i);
			अवरोध;
		हाल GUP_BASIC_TEST:
			nr = get_user_pages(addr, nr, gup->gup_flags, pages + i,
					    शून्य);
			अवरोध;
		हाल PIN_FAST_BENCHMARK:
			nr = pin_user_pages_fast(addr, nr, gup->gup_flags,
						 pages + i);
			अवरोध;
		हाल PIN_BASIC_TEST:
			nr = pin_user_pages(addr, nr, gup->gup_flags, pages + i,
					    शून्य);
			अवरोध;
		हाल PIN_LONGTERM_BENCHMARK:
			nr = pin_user_pages(addr, nr,
					    gup->gup_flags | FOLL_LONGTERM,
					    pages + i, शून्य);
			अवरोध;
		हाल DUMP_USER_PAGES_TEST:
			अगर (gup->test_flags & GUP_TEST_FLAG_DUMP_PAGES_USE_PIN)
				nr = pin_user_pages(addr, nr, gup->gup_flags,
						    pages + i, शून्य);
			अन्यथा
				nr = get_user_pages(addr, nr, gup->gup_flags,
						    pages + i, शून्य);
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण

		अगर (nr <= 0)
			अवरोध;
		i += nr;
	पूर्ण
	end_समय = kसमय_get();

	/* Shअगरting the meaning of nr_pages: now it is actual number pinned: */
	nr_pages = i;

	gup->get_delta_usec = kसमय_us_delta(end_समय, start_समय);
	gup->size = addr - gup->addr;

	/*
	 * Take an un-benchmark-समयd moment to verअगरy DMA pinned
	 * state: prपूर्णांक a warning अगर any non-dma-pinned pages are found:
	 */
	verअगरy_dma_pinned(cmd, pages, nr_pages);

	अगर (cmd == DUMP_USER_PAGES_TEST)
		dump_pages_test(gup, pages, nr_pages);

	start_समय = kसमय_get();

	put_back_pages(cmd, pages, nr_pages, gup->test_flags);

	end_समय = kसमय_get();
	gup->put_delta_usec = kसमय_us_delta(end_समय, start_समय);

unlock:
	अगर (needs_mmap_lock)
		mmap_पढ़ो_unlock(current->mm);
मुक्त_pages:
	kvमुक्त(pages);
	वापस ret;
पूर्ण

अटल दीर्घ gup_test_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	काष्ठा gup_test gup;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल GUP_FAST_BENCHMARK:
	हाल PIN_FAST_BENCHMARK:
	हाल PIN_LONGTERM_BENCHMARK:
	हाल GUP_BASIC_TEST:
	हाल PIN_BASIC_TEST:
	हाल DUMP_USER_PAGES_TEST:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&gup, (व्योम __user *)arg, माप(gup)))
		वापस -EFAULT;

	ret = __gup_test_ioctl(cmd, &gup);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user((व्योम __user *)arg, &gup, माप(gup)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations gup_test_fops = अणु
	.खोलो = nonseekable_खोलो,
	.unlocked_ioctl = gup_test_ioctl,
पूर्ण;

अटल पूर्णांक __init gup_test_init(व्योम)
अणु
	debugfs_create_file_unsafe("gup_test", 0600, शून्य, शून्य,
				   &gup_test_fops);

	वापस 0;
पूर्ण

late_initcall(gup_test_init);
