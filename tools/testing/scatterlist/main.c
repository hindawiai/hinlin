<शैली गुरु>
#समावेश <मानकपन.स>
#समावेश <निश्चित.स>

#समावेश <linux/scatterlist.h>

#घोषणा MAX_PAGES (64)

काष्ठा test अणु
	पूर्णांक alloc_ret;
	अचिन्हित num_pages;
	अचिन्हित *pfn;
	अचिन्हित *pfn_app;
	अचिन्हित size;
	अचिन्हित पूर्णांक max_seg;
	अचिन्हित पूर्णांक expected_segments;
पूर्ण;

अटल व्योम set_pages(काष्ठा page **pages, स्थिर अचिन्हित *array, अचिन्हित num)
अणु
	अचिन्हित पूर्णांक i;

	निश्चित(num < MAX_PAGES);
	क्रम (i = 0; i < num; i++)
		pages[i] = (काष्ठा page *)(अचिन्हित दीर्घ)
			   ((1 + array[i]) * PAGE_SIZE);
पूर्ण

#घोषणा pfn(...) (अचिन्हित [])अणु __VA_ARGS__ पूर्ण

अटल व्योम fail(काष्ठा test *test, काष्ठा sg_table *st, स्थिर अक्षर *cond)
अणु
	अचिन्हित पूर्णांक i;

	ख_लिखो(मानक_त्रुटि, "Failed on '%s'!\n\n", cond);

	म_लिखो("size = %u, max segment = %u, expected nents = %u\nst->nents = %u, st->orig_nents= %u\n",
	       test->size, test->max_seg, test->expected_segments, st->nents,
	       st->orig_nents);

	म_लिखो("%u input PFNs:", test->num_pages);
	क्रम (i = 0; i < test->num_pages; i++)
		म_लिखो(" %x", test->pfn[i]);
	म_लिखो("\n");

	निकास(1);
पूर्ण

#घोषणा VALIDATE(cond, st, test) \
	अगर (!(cond)) \
		fail((test), (st), #cond);

पूर्णांक मुख्य(व्योम)
अणु
	स्थिर अचिन्हित पूर्णांक sgmax = अच_पूर्णांक_उच्च;
	काष्ठा test *test, tests[] = अणु
		अणु -EINVAL, 1, pfn(0), शून्य, PAGE_SIZE, 0, 1 पूर्ण,
		अणु 0, 1, pfn(0), शून्य, PAGE_SIZE, PAGE_SIZE + 1, 1 पूर्ण,
		अणु 0, 1, pfn(0), शून्य, PAGE_SIZE, sgmax, 1 पूर्ण,
		अणु 0, 1, pfn(0), शून्य, 1, sgmax, 1 पूर्ण,
		अणु 0, 2, pfn(0, 1), शून्य, 2 * PAGE_SIZE, sgmax, 1 पूर्ण,
		अणु 0, 2, pfn(1, 0), शून्य, 2 * PAGE_SIZE, sgmax, 2 पूर्ण,
		अणु 0, 3, pfn(0, 1, 2), शून्य, 3 * PAGE_SIZE, sgmax, 1 पूर्ण,
		अणु 0, 3, pfn(0, 1, 2), शून्य, 3 * PAGE_SIZE, sgmax, 1 पूर्ण,
		अणु 0, 3, pfn(0, 1, 2), pfn(3, 4, 5), 3 * PAGE_SIZE, sgmax, 1 पूर्ण,
		अणु 0, 3, pfn(0, 1, 2), pfn(4, 5, 6), 3 * PAGE_SIZE, sgmax, 2 पूर्ण,
		अणु 0, 3, pfn(0, 2, 1), शून्य, 3 * PAGE_SIZE, sgmax, 3 पूर्ण,
		अणु 0, 3, pfn(0, 1, 3), शून्य, 3 * PAGE_SIZE, sgmax, 2 पूर्ण,
		अणु 0, 3, pfn(1, 2, 4), शून्य, 3 * PAGE_SIZE, sgmax, 2 पूर्ण,
		अणु 0, 3, pfn(1, 3, 4), शून्य, 3 * PAGE_SIZE, sgmax, 2 पूर्ण,
		अणु 0, 4, pfn(0, 1, 3, 4), शून्य, 4 * PAGE_SIZE, sgmax, 2 पूर्ण,
		अणु 0, 5, pfn(0, 1, 3, 4, 5), शून्य, 5 * PAGE_SIZE, sgmax, 2 पूर्ण,
		अणु 0, 5, pfn(0, 1, 3, 4, 6), शून्य, 5 * PAGE_SIZE, sgmax, 3 पूर्ण,
		अणु 0, 5, pfn(0, 1, 2, 3, 4), शून्य, 5 * PAGE_SIZE, sgmax, 1 पूर्ण,
		अणु 0, 5, pfn(0, 1, 2, 3, 4), शून्य, 5 * PAGE_SIZE, 2 * PAGE_SIZE,
		  3 पूर्ण,
		अणु 0, 6, pfn(0, 1, 2, 3, 4, 5), शून्य, 6 * PAGE_SIZE,
		  2 * PAGE_SIZE, 3 पूर्ण,
		अणु 0, 6, pfn(0, 2, 3, 4, 5, 6), शून्य, 6 * PAGE_SIZE,
		  2 * PAGE_SIZE, 4 पूर्ण,
		अणु 0, 6, pfn(0, 1, 3, 4, 5, 6), pfn(7, 8, 9, 10, 11, 12),
		  6 * PAGE_SIZE, 12 * PAGE_SIZE, 2 पूर्ण,
		अणु 0, 0, शून्य, शून्य, 0, 0, 0 पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0, test = tests; test->expected_segments; test++, i++) अणु
		पूर्णांक left_pages = test->pfn_app ? test->num_pages : 0;
		काष्ठा page *pages[MAX_PAGES];
		काष्ठा sg_table st;
		काष्ठा scatterlist *sg;

		set_pages(pages, test->pfn, test->num_pages);

		sg = __sg_alloc_table_from_pages(&st, pages, test->num_pages, 0,
				test->size, test->max_seg, शून्य, left_pages, GFP_KERNEL);
		निश्चित(PTR_ERR_OR_ZERO(sg) == test->alloc_ret);

		अगर (test->alloc_ret)
			जारी;

		अगर (test->pfn_app) अणु
			set_pages(pages, test->pfn_app, test->num_pages);
			sg = __sg_alloc_table_from_pages(&st, pages, test->num_pages, 0,
					test->size, test->max_seg, sg, 0, GFP_KERNEL);

			निश्चित(PTR_ERR_OR_ZERO(sg) == test->alloc_ret);
		पूर्ण

		VALIDATE(st.nents == test->expected_segments, &st, test);
		अगर (!test->pfn_app)
			VALIDATE(st.orig_nents == test->expected_segments, &st, test);

		sg_मुक्त_table(&st);
	पूर्ण

	निश्चित(i == (माप(tests) / माप(tests[0])) - 1);

	वापस 0;
पूर्ण
