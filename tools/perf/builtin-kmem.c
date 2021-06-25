<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "builtin.h"
#समावेश "perf.h"

#समावेश "util/dso.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/config.h"
#समावेश "util/map.h"
#समावेश "util/symbol.h"
#समावेश "util/thread.h"
#समावेश "util/header.h"
#समावेश "util/session.h"
#समावेश "util/tool.h"
#समावेश "util/callchain.h"
#समावेश "util/time-utils.h"
#समावेश <linux/err.h>

#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश "util/trace-event.h"
#समावेश "util/data.h"
#समावेश "util/cpumap.h"

#समावेश "util/debug.h"
#समावेश "util/string2.h"

#समावेश <linux/kernel.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <क्षेत्र.स>
#समावेश <regex.h>

#समावेश <linux/प्रकार.स>

अटल पूर्णांक	kmem_slab;
अटल पूर्णांक	kmem_page;

अटल दीर्घ	kmem_page_size;
अटल क्रमागत अणु
	KMEM_SLAB,
	KMEM_PAGE,
पूर्ण kmem_शेष = KMEM_SLAB;  /* क्रम backward compatibility */

काष्ठा alloc_stat;
प्रकार पूर्णांक (*sort_fn_t)(व्योम *, व्योम *);

अटल पूर्णांक			alloc_flag;
अटल पूर्णांक			caller_flag;

अटल पूर्णांक			alloc_lines = -1;
अटल पूर्णांक			caller_lines = -1;

अटल bool			raw_ip;

काष्ठा alloc_stat अणु
	u64	call_site;
	u64	ptr;
	u64	bytes_req;
	u64	bytes_alloc;
	u64	last_alloc;
	u32	hit;
	u32	pingpong;

	लघु	alloc_cpu;

	काष्ठा rb_node node;
पूर्ण;

अटल काष्ठा rb_root root_alloc_stat;
अटल काष्ठा rb_root root_alloc_sorted;
अटल काष्ठा rb_root root_caller_stat;
अटल काष्ठा rb_root root_caller_sorted;

अटल अचिन्हित दीर्घ total_requested, total_allocated, total_मुक्तd;
अटल अचिन्हित दीर्घ nr_allocs, nr_cross_allocs;

/* filters क्रम controlling start and stop of समय of analysis */
अटल काष्ठा perf_समय_पूर्णांकerval pसमय;
स्थिर अक्षर *समय_str;

अटल पूर्णांक insert_alloc_stat(अचिन्हित दीर्घ call_site, अचिन्हित दीर्घ ptr,
			     पूर्णांक bytes_req, पूर्णांक bytes_alloc, पूर्णांक cpu)
अणु
	काष्ठा rb_node **node = &root_alloc_stat.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा alloc_stat *data = शून्य;

	जबतक (*node) अणु
		parent = *node;
		data = rb_entry(*node, काष्ठा alloc_stat, node);

		अगर (ptr > data->ptr)
			node = &(*node)->rb_right;
		अन्यथा अगर (ptr < data->ptr)
			node = &(*node)->rb_left;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (data && data->ptr == ptr) अणु
		data->hit++;
		data->bytes_req += bytes_req;
		data->bytes_alloc += bytes_alloc;
	पूर्ण अन्यथा अणु
		data = दो_स्मृति(माप(*data));
		अगर (!data) अणु
			pr_err("%s: malloc failed\n", __func__);
			वापस -1;
		पूर्ण
		data->ptr = ptr;
		data->pingpong = 0;
		data->hit = 1;
		data->bytes_req = bytes_req;
		data->bytes_alloc = bytes_alloc;

		rb_link_node(&data->node, parent, node);
		rb_insert_color(&data->node, &root_alloc_stat);
	पूर्ण
	data->call_site = call_site;
	data->alloc_cpu = cpu;
	data->last_alloc = bytes_alloc;

	वापस 0;
पूर्ण

अटल पूर्णांक insert_caller_stat(अचिन्हित दीर्घ call_site,
			      पूर्णांक bytes_req, पूर्णांक bytes_alloc)
अणु
	काष्ठा rb_node **node = &root_caller_stat.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा alloc_stat *data = शून्य;

	जबतक (*node) अणु
		parent = *node;
		data = rb_entry(*node, काष्ठा alloc_stat, node);

		अगर (call_site > data->call_site)
			node = &(*node)->rb_right;
		अन्यथा अगर (call_site < data->call_site)
			node = &(*node)->rb_left;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (data && data->call_site == call_site) अणु
		data->hit++;
		data->bytes_req += bytes_req;
		data->bytes_alloc += bytes_alloc;
	पूर्ण अन्यथा अणु
		data = दो_स्मृति(माप(*data));
		अगर (!data) अणु
			pr_err("%s: malloc failed\n", __func__);
			वापस -1;
		पूर्ण
		data->call_site = call_site;
		data->pingpong = 0;
		data->hit = 1;
		data->bytes_req = bytes_req;
		data->bytes_alloc = bytes_alloc;

		rb_link_node(&data->node, parent, node);
		rb_insert_color(&data->node, &root_caller_stat);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evsel__process_alloc_event(काष्ठा evsel *evsel, काष्ठा perf_sample *sample)
अणु
	अचिन्हित दीर्घ ptr = evsel__पूर्णांकval(evsel, sample, "ptr"),
		      call_site = evsel__पूर्णांकval(evsel, sample, "call_site");
	पूर्णांक bytes_req = evsel__पूर्णांकval(evsel, sample, "bytes_req"),
	    bytes_alloc = evsel__पूर्णांकval(evsel, sample, "bytes_alloc");

	अगर (insert_alloc_stat(call_site, ptr, bytes_req, bytes_alloc, sample->cpu) ||
	    insert_caller_stat(call_site, bytes_req, bytes_alloc))
		वापस -1;

	total_requested += bytes_req;
	total_allocated += bytes_alloc;

	nr_allocs++;
	वापस 0;
पूर्ण

अटल पूर्णांक evsel__process_alloc_node_event(काष्ठा evsel *evsel, काष्ठा perf_sample *sample)
अणु
	पूर्णांक ret = evsel__process_alloc_event(evsel, sample);

	अगर (!ret) अणु
		पूर्णांक node1 = cpu__get_node(sample->cpu),
		    node2 = evsel__पूर्णांकval(evsel, sample, "node");

		अगर (node1 != node2)
			nr_cross_allocs++;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ptr_cmp(व्योम *, व्योम *);
अटल पूर्णांक slab_callsite_cmp(व्योम *, व्योम *);

अटल काष्ठा alloc_stat *search_alloc_stat(अचिन्हित दीर्घ ptr,
					    अचिन्हित दीर्घ call_site,
					    काष्ठा rb_root *root,
					    sort_fn_t sort_fn)
अणु
	काष्ठा rb_node *node = root->rb_node;
	काष्ठा alloc_stat key = अणु .ptr = ptr, .call_site = call_site पूर्ण;

	जबतक (node) अणु
		काष्ठा alloc_stat *data;
		पूर्णांक cmp;

		data = rb_entry(node, काष्ठा alloc_stat, node);

		cmp = sort_fn(&key, data);
		अगर (cmp < 0)
			node = node->rb_left;
		अन्यथा अगर (cmp > 0)
			node = node->rb_right;
		अन्यथा
			वापस data;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक evsel__process_मुक्त_event(काष्ठा evsel *evsel, काष्ठा perf_sample *sample)
अणु
	अचिन्हित दीर्घ ptr = evsel__पूर्णांकval(evsel, sample, "ptr");
	काष्ठा alloc_stat *s_alloc, *s_caller;

	s_alloc = search_alloc_stat(ptr, 0, &root_alloc_stat, ptr_cmp);
	अगर (!s_alloc)
		वापस 0;

	total_मुक्तd += s_alloc->last_alloc;

	अगर ((लघु)sample->cpu != s_alloc->alloc_cpu) अणु
		s_alloc->pingpong++;

		s_caller = search_alloc_stat(0, s_alloc->call_site,
					     &root_caller_stat,
					     slab_callsite_cmp);
		अगर (!s_caller)
			वापस -1;
		s_caller->pingpong++;
	पूर्ण
	s_alloc->alloc_cpu = -1;

	वापस 0;
पूर्ण

अटल u64 total_page_alloc_bytes;
अटल u64 total_page_मुक्त_bytes;
अटल u64 total_page_nomatch_bytes;
अटल u64 total_page_fail_bytes;
अटल अचिन्हित दीर्घ nr_page_allocs;
अटल अचिन्हित दीर्घ nr_page_मुक्तs;
अटल अचिन्हित दीर्घ nr_page_fails;
अटल अचिन्हित दीर्घ nr_page_nomatch;

अटल bool use_pfn;
अटल bool live_page;
अटल काष्ठा perf_session *kmem_session;

#घोषणा MAX_MIGRATE_TYPES  6
#घोषणा MAX_PAGE_ORDER     11

अटल पूर्णांक order_stats[MAX_PAGE_ORDER][MAX_MIGRATE_TYPES];

काष्ठा page_stat अणु
	काष्ठा rb_node 	node;
	u64 		page;
	u64 		callsite;
	पूर्णांक 		order;
	अचिन्हित 	gfp_flags;
	अचिन्हित 	migrate_type;
	u64		alloc_bytes;
	u64 		मुक्त_bytes;
	पूर्णांक 		nr_alloc;
	पूर्णांक 		nr_मुक्त;
पूर्ण;

अटल काष्ठा rb_root page_live_tree;
अटल काष्ठा rb_root page_alloc_tree;
अटल काष्ठा rb_root page_alloc_sorted;
अटल काष्ठा rb_root page_caller_tree;
अटल काष्ठा rb_root page_caller_sorted;

काष्ठा alloc_func अणु
	u64 start;
	u64 end;
	अक्षर *name;
पूर्ण;

अटल पूर्णांक nr_alloc_funcs;
अटल काष्ठा alloc_func *alloc_func_list;

अटल पूर्णांक funcmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा alloc_func *fa = a;
	स्थिर काष्ठा alloc_func *fb = b;

	अगर (fa->start > fb->start)
		वापस 1;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक callcmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा alloc_func *fa = a;
	स्थिर काष्ठा alloc_func *fb = b;

	अगर (fb->start <= fa->start && fa->end < fb->end)
		वापस 0;

	अगर (fa->start > fb->start)
		वापस 1;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक build_alloc_func_list(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा map *kernel_map;
	काष्ठा symbol *sym;
	काष्ठा rb_node *node;
	काष्ठा alloc_func *func;
	काष्ठा machine *machine = &kmem_session->machines.host;
	regex_t alloc_func_regex;
	अटल स्थिर अक्षर pattern[] = "^_?_?(alloc|get_मुक्त|get_zeroed)_pages?";

	ret = regcomp(&alloc_func_regex, pattern, REG_EXTENDED);
	अगर (ret) अणु
		अक्षर err[बफ_मान];

		regerror(ret, &alloc_func_regex, err, माप(err));
		pr_err("Invalid regex: %s\n%s", pattern, err);
		वापस -EINVAL;
	पूर्ण

	kernel_map = machine__kernel_map(machine);
	अगर (map__load(kernel_map) < 0) अणु
		pr_err("cannot load kernel map\n");
		वापस -ENOENT;
	पूर्ण

	map__क्रम_each_symbol(kernel_map, sym, node) अणु
		अगर (regexec(&alloc_func_regex, sym->name, 0, शून्य, 0))
			जारी;

		func = पुनः_स्मृति(alloc_func_list,
			       (nr_alloc_funcs + 1) * माप(*func));
		अगर (func == शून्य)
			वापस -ENOMEM;

		pr_debug("alloc func: %s\n", sym->name);
		func[nr_alloc_funcs].start = sym->start;
		func[nr_alloc_funcs].end   = sym->end;
		func[nr_alloc_funcs].name  = sym->name;

		alloc_func_list = func;
		nr_alloc_funcs++;
	पूर्ण

	क्विक(alloc_func_list, nr_alloc_funcs, माप(*func), funcmp);

	regमुक्त(&alloc_func_regex);
	वापस 0;
पूर्ण

/*
 * Find first non-memory allocation function from callchain.
 * The allocation functions are in the 'alloc_func_list'.
 */
अटल u64 find_callsite(काष्ठा evsel *evsel, काष्ठा perf_sample *sample)
अणु
	काष्ठा addr_location al;
	काष्ठा machine *machine = &kmem_session->machines.host;
	काष्ठा callchain_cursor_node *node;

	अगर (alloc_func_list == शून्य) अणु
		अगर (build_alloc_func_list() < 0)
			जाओ out;
	पूर्ण

	al.thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid, sample->tid);
	sample__resolve_callchain(sample, &callchain_cursor, शून्य, evsel, &al, 16);

	callchain_cursor_commit(&callchain_cursor);
	जबतक (true) अणु
		काष्ठा alloc_func key, *caller;
		u64 addr;

		node = callchain_cursor_current(&callchain_cursor);
		अगर (node == शून्य)
			अवरोध;

		key.start = key.end = node->ip;
		caller = द्वा_खोज(&key, alloc_func_list, nr_alloc_funcs,
				 माप(key), callcmp);
		अगर (!caller) अणु
			/* found */
			अगर (node->ms.map)
				addr = map__unmap_ip(node->ms.map, node->ip);
			अन्यथा
				addr = node->ip;

			वापस addr;
		पूर्ण अन्यथा
			pr_debug3("skipping alloc function: %s\n", caller->name);

		callchain_cursor_advance(&callchain_cursor);
	पूर्ण

out:
	pr_debug2("unknown callsite: %"PRIx64 "\n", sample->ip);
	वापस sample->ip;
पूर्ण

काष्ठा sort_dimension अणु
	स्थिर अक्षर		name[20];
	sort_fn_t		cmp;
	काष्ठा list_head	list;
पूर्ण;

अटल LIST_HEAD(page_alloc_sort_input);
अटल LIST_HEAD(page_caller_sort_input);

अटल काष्ठा page_stat *
__page_stat__findnew_page(काष्ठा page_stat *pstat, bool create)
अणु
	काष्ठा rb_node **node = &page_live_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा page_stat *data;

	जबतक (*node) अणु
		s64 cmp;

		parent = *node;
		data = rb_entry(*node, काष्ठा page_stat, node);

		cmp = data->page - pstat->page;
		अगर (cmp < 0)
			node = &parent->rb_left;
		अन्यथा अगर (cmp > 0)
			node = &parent->rb_right;
		अन्यथा
			वापस data;
	पूर्ण

	अगर (!create)
		वापस शून्य;

	data = zalloc(माप(*data));
	अगर (data != शून्य) अणु
		data->page = pstat->page;
		data->order = pstat->order;
		data->gfp_flags = pstat->gfp_flags;
		data->migrate_type = pstat->migrate_type;

		rb_link_node(&data->node, parent, node);
		rb_insert_color(&data->node, &page_live_tree);
	पूर्ण

	वापस data;
पूर्ण

अटल काष्ठा page_stat *page_stat__find_page(काष्ठा page_stat *pstat)
अणु
	वापस __page_stat__findnew_page(pstat, false);
पूर्ण

अटल काष्ठा page_stat *page_stat__findnew_page(काष्ठा page_stat *pstat)
अणु
	वापस __page_stat__findnew_page(pstat, true);
पूर्ण

अटल काष्ठा page_stat *
__page_stat__findnew_alloc(काष्ठा page_stat *pstat, bool create)
अणु
	काष्ठा rb_node **node = &page_alloc_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा page_stat *data;
	काष्ठा sort_dimension *sort;

	जबतक (*node) अणु
		पूर्णांक cmp = 0;

		parent = *node;
		data = rb_entry(*node, काष्ठा page_stat, node);

		list_क्रम_each_entry(sort, &page_alloc_sort_input, list) अणु
			cmp = sort->cmp(pstat, data);
			अगर (cmp)
				अवरोध;
		पूर्ण

		अगर (cmp < 0)
			node = &parent->rb_left;
		अन्यथा अगर (cmp > 0)
			node = &parent->rb_right;
		अन्यथा
			वापस data;
	पूर्ण

	अगर (!create)
		वापस शून्य;

	data = zalloc(माप(*data));
	अगर (data != शून्य) अणु
		data->page = pstat->page;
		data->order = pstat->order;
		data->gfp_flags = pstat->gfp_flags;
		data->migrate_type = pstat->migrate_type;

		rb_link_node(&data->node, parent, node);
		rb_insert_color(&data->node, &page_alloc_tree);
	पूर्ण

	वापस data;
पूर्ण

अटल काष्ठा page_stat *page_stat__find_alloc(काष्ठा page_stat *pstat)
अणु
	वापस __page_stat__findnew_alloc(pstat, false);
पूर्ण

अटल काष्ठा page_stat *page_stat__findnew_alloc(काष्ठा page_stat *pstat)
अणु
	वापस __page_stat__findnew_alloc(pstat, true);
पूर्ण

अटल काष्ठा page_stat *
__page_stat__findnew_caller(काष्ठा page_stat *pstat, bool create)
अणु
	काष्ठा rb_node **node = &page_caller_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा page_stat *data;
	काष्ठा sort_dimension *sort;

	जबतक (*node) अणु
		पूर्णांक cmp = 0;

		parent = *node;
		data = rb_entry(*node, काष्ठा page_stat, node);

		list_क्रम_each_entry(sort, &page_caller_sort_input, list) अणु
			cmp = sort->cmp(pstat, data);
			अगर (cmp)
				अवरोध;
		पूर्ण

		अगर (cmp < 0)
			node = &parent->rb_left;
		अन्यथा अगर (cmp > 0)
			node = &parent->rb_right;
		अन्यथा
			वापस data;
	पूर्ण

	अगर (!create)
		वापस शून्य;

	data = zalloc(माप(*data));
	अगर (data != शून्य) अणु
		data->callsite = pstat->callsite;
		data->order = pstat->order;
		data->gfp_flags = pstat->gfp_flags;
		data->migrate_type = pstat->migrate_type;

		rb_link_node(&data->node, parent, node);
		rb_insert_color(&data->node, &page_caller_tree);
	पूर्ण

	वापस data;
पूर्ण

अटल काष्ठा page_stat *page_stat__find_caller(काष्ठा page_stat *pstat)
अणु
	वापस __page_stat__findnew_caller(pstat, false);
पूर्ण

अटल काष्ठा page_stat *page_stat__findnew_caller(काष्ठा page_stat *pstat)
अणु
	वापस __page_stat__findnew_caller(pstat, true);
पूर्ण

अटल bool valid_page(u64 pfn_or_page)
अणु
	अगर (use_pfn && pfn_or_page == -1UL)
		वापस false;
	अगर (!use_pfn && pfn_or_page == 0)
		वापस false;
	वापस true;
पूर्ण

काष्ठा gfp_flag अणु
	अचिन्हित पूर्णांक flags;
	अक्षर *compact_str;
	अक्षर *human_पढ़ोable;
पूर्ण;

अटल काष्ठा gfp_flag *gfps;
अटल पूर्णांक nr_gfps;

अटल पूर्णांक gfpcmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा gfp_flag *fa = a;
	स्थिर काष्ठा gfp_flag *fb = b;

	वापस fa->flags - fb->flags;
पूर्ण

/* see include/trace/events/mmflags.h */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *original;
	स्थिर अक्षर *compact;
पूर्ण gfp_compact_table[] = अणु
	अणु "GFP_TRANSHUGE",		"THP" पूर्ण,
	अणु "GFP_TRANSHUGE_LIGHT",	"THL" पूर्ण,
	अणु "GFP_HIGHUSER_MOVABLE",	"HUM" पूर्ण,
	अणु "GFP_HIGHUSER",		"HU" पूर्ण,
	अणु "GFP_USER",			"U" पूर्ण,
	अणु "GFP_KERNEL_ACCOUNT",		"KAC" पूर्ण,
	अणु "GFP_KERNEL",			"K" पूर्ण,
	अणु "GFP_NOFS",			"NF" पूर्ण,
	अणु "GFP_ATOMIC",			"A" पूर्ण,
	अणु "GFP_NOIO",			"NI" पूर्ण,
	अणु "GFP_NOWAIT",			"NW" पूर्ण,
	अणु "GFP_DMA",			"D" पूर्ण,
	अणु "__GFP_HIGHMEM",		"HM" पूर्ण,
	अणु "GFP_DMA32",			"D32" पूर्ण,
	अणु "__GFP_HIGH",			"H" पूर्ण,
	अणु "__GFP_ATOMIC",		"_A" पूर्ण,
	अणु "__GFP_IO",			"I" पूर्ण,
	अणु "__GFP_FS",			"F" पूर्ण,
	अणु "__GFP_NOWARN",		"NWR" पूर्ण,
	अणु "__GFP_RETRY_MAYFAIL",	"R" पूर्ण,
	अणु "__GFP_NOFAIL",		"NF" पूर्ण,
	अणु "__GFP_NORETRY",		"NR" पूर्ण,
	अणु "__GFP_COMP",			"C" पूर्ण,
	अणु "__GFP_ZERO",			"Z" पूर्ण,
	अणु "__GFP_NOMEMALLOC",		"NMA" पूर्ण,
	अणु "__GFP_MEMALLOC",		"MA" पूर्ण,
	अणु "__GFP_HARDWALL",		"HW" पूर्ण,
	अणु "__GFP_THISNODE",		"TN" पूर्ण,
	अणु "__GFP_RECLAIMABLE",		"RC" पूर्ण,
	अणु "__GFP_MOVABLE",		"M" पूर्ण,
	अणु "__GFP_ACCOUNT",		"AC" पूर्ण,
	अणु "__GFP_WRITE",		"WR" पूर्ण,
	अणु "__GFP_RECLAIM",		"R" पूर्ण,
	अणु "__GFP_DIRECT_RECLAIM",	"DR" पूर्ण,
	अणु "__GFP_KSWAPD_RECLAIM",	"KR" पूर्ण,
पूर्ण;

अटल माप_प्रकार max_gfp_len;

अटल अक्षर *compact_gfp_flags(अक्षर *gfp_flags)
अणु
	अक्षर *orig_flags = strdup(gfp_flags);
	अक्षर *new_flags = शून्य;
	अक्षर *str, *pos = शून्य;
	माप_प्रकार len = 0;

	अगर (orig_flags == शून्य)
		वापस शून्य;

	str = म_मोहर_r(orig_flags, "|", &pos);
	जबतक (str) अणु
		माप_प्रकार i;
		अक्षर *new;
		स्थिर अक्षर *cpt;

		क्रम (i = 0; i < ARRAY_SIZE(gfp_compact_table); i++) अणु
			अगर (म_भेद(gfp_compact_table[i].original, str))
				जारी;

			cpt = gfp_compact_table[i].compact;
			new = पुनः_स्मृति(new_flags, len + म_माप(cpt) + 2);
			अगर (new == शून्य) अणु
				मुक्त(new_flags);
				मुक्त(orig_flags);
				वापस शून्य;
			पूर्ण

			new_flags = new;

			अगर (!len) अणु
				म_नकल(new_flags, cpt);
			पूर्ण अन्यथा अणु
				म_जोड़ो(new_flags, "|");
				म_जोड़ो(new_flags, cpt);
				len++;
			पूर्ण

			len += म_माप(cpt);
		पूर्ण

		str = म_मोहर_r(शून्य, "|", &pos);
	पूर्ण

	अगर (max_gfp_len < len)
		max_gfp_len = len;

	मुक्त(orig_flags);
	वापस new_flags;
पूर्ण

अटल अक्षर *compact_gfp_string(अचिन्हित दीर्घ gfp_flags)
अणु
	काष्ठा gfp_flag key = अणु
		.flags = gfp_flags,
	पूर्ण;
	काष्ठा gfp_flag *gfp;

	gfp = द्वा_खोज(&key, gfps, nr_gfps, माप(*gfps), gfpcmp);
	अगर (gfp)
		वापस gfp->compact_str;

	वापस शून्य;
पूर्ण

अटल पूर्णांक parse_gfp_flags(काष्ठा evsel *evsel, काष्ठा perf_sample *sample,
			   अचिन्हित पूर्णांक gfp_flags)
अणु
	काष्ठा tep_record record = अणु
		.cpu = sample->cpu,
		.data = sample->raw_data,
		.size = sample->raw_size,
	पूर्ण;
	काष्ठा trace_seq seq;
	अक्षर *str, *pos = शून्य;

	अगर (nr_gfps) अणु
		काष्ठा gfp_flag key = अणु
			.flags = gfp_flags,
		पूर्ण;

		अगर (द्वा_खोज(&key, gfps, nr_gfps, माप(*gfps), gfpcmp))
			वापस 0;
	पूर्ण

	trace_seq_init(&seq);
	tep_prपूर्णांक_event(evsel->tp_क्रमmat->tep,
			&seq, &record, "%s", TEP_PRINT_INFO);

	str = म_मोहर_r(seq.buffer, " ", &pos);
	जबतक (str) अणु
		अगर (!म_भेदन(str, "gfp_flags=", 10)) अणु
			काष्ठा gfp_flag *new;

			new = पुनः_स्मृति(gfps, (nr_gfps + 1) * माप(*gfps));
			अगर (new == शून्य)
				वापस -ENOMEM;

			gfps = new;
			new += nr_gfps++;

			new->flags = gfp_flags;
			new->human_पढ़ोable = strdup(str + 10);
			new->compact_str = compact_gfp_flags(str + 10);
			अगर (!new->human_पढ़ोable || !new->compact_str)
				वापस -ENOMEM;

			क्विक(gfps, nr_gfps, माप(*gfps), gfpcmp);
		पूर्ण

		str = म_मोहर_r(शून्य, " ", &pos);
	पूर्ण

	trace_seq_destroy(&seq);
	वापस 0;
पूर्ण

अटल पूर्णांक evsel__process_page_alloc_event(काष्ठा evsel *evsel, काष्ठा perf_sample *sample)
अणु
	u64 page;
	अचिन्हित पूर्णांक order = evsel__पूर्णांकval(evsel, sample, "order");
	अचिन्हित पूर्णांक gfp_flags = evsel__पूर्णांकval(evsel, sample, "gfp_flags");
	अचिन्हित पूर्णांक migrate_type = evsel__पूर्णांकval(evsel, sample,
						       "migratetype");
	u64 bytes = kmem_page_size << order;
	u64 callsite;
	काष्ठा page_stat *pstat;
	काष्ठा page_stat this = अणु
		.order = order,
		.gfp_flags = gfp_flags,
		.migrate_type = migrate_type,
	पूर्ण;

	अगर (use_pfn)
		page = evsel__पूर्णांकval(evsel, sample, "pfn");
	अन्यथा
		page = evsel__पूर्णांकval(evsel, sample, "page");

	nr_page_allocs++;
	total_page_alloc_bytes += bytes;

	अगर (!valid_page(page)) अणु
		nr_page_fails++;
		total_page_fail_bytes += bytes;

		वापस 0;
	पूर्ण

	अगर (parse_gfp_flags(evsel, sample, gfp_flags) < 0)
		वापस -1;

	callsite = find_callsite(evsel, sample);

	/*
	 * This is to find the current page (with correct gfp flags and
	 * migrate type) at मुक्त event.
	 */
	this.page = page;
	pstat = page_stat__findnew_page(&this);
	अगर (pstat == शून्य)
		वापस -ENOMEM;

	pstat->nr_alloc++;
	pstat->alloc_bytes += bytes;
	pstat->callsite = callsite;

	अगर (!live_page) अणु
		pstat = page_stat__findnew_alloc(&this);
		अगर (pstat == शून्य)
			वापस -ENOMEM;

		pstat->nr_alloc++;
		pstat->alloc_bytes += bytes;
		pstat->callsite = callsite;
	पूर्ण

	this.callsite = callsite;
	pstat = page_stat__findnew_caller(&this);
	अगर (pstat == शून्य)
		वापस -ENOMEM;

	pstat->nr_alloc++;
	pstat->alloc_bytes += bytes;

	order_stats[order][migrate_type]++;

	वापस 0;
पूर्ण

अटल पूर्णांक evsel__process_page_मुक्त_event(काष्ठा evsel *evsel, काष्ठा perf_sample *sample)
अणु
	u64 page;
	अचिन्हित पूर्णांक order = evsel__पूर्णांकval(evsel, sample, "order");
	u64 bytes = kmem_page_size << order;
	काष्ठा page_stat *pstat;
	काष्ठा page_stat this = अणु
		.order = order,
	पूर्ण;

	अगर (use_pfn)
		page = evsel__पूर्णांकval(evsel, sample, "pfn");
	अन्यथा
		page = evsel__पूर्णांकval(evsel, sample, "page");

	nr_page_मुक्तs++;
	total_page_मुक्त_bytes += bytes;

	this.page = page;
	pstat = page_stat__find_page(&this);
	अगर (pstat == शून्य) अणु
		pr_debug2("missing free at page %"PRIx64" (order: %d)\n",
			  page, order);

		nr_page_nomatch++;
		total_page_nomatch_bytes += bytes;

		वापस 0;
	पूर्ण

	this.gfp_flags = pstat->gfp_flags;
	this.migrate_type = pstat->migrate_type;
	this.callsite = pstat->callsite;

	rb_erase(&pstat->node, &page_live_tree);
	मुक्त(pstat);

	अगर (live_page) अणु
		order_stats[this.order][this.migrate_type]--;
	पूर्ण अन्यथा अणु
		pstat = page_stat__find_alloc(&this);
		अगर (pstat == शून्य)
			वापस -ENOMEM;

		pstat->nr_मुक्त++;
		pstat->मुक्त_bytes += bytes;
	पूर्ण

	pstat = page_stat__find_caller(&this);
	अगर (pstat == शून्य)
		वापस -ENOENT;

	pstat->nr_मुक्त++;
	pstat->मुक्त_bytes += bytes;

	अगर (live_page) अणु
		pstat->nr_alloc--;
		pstat->alloc_bytes -= bytes;

		अगर (pstat->nr_alloc == 0) अणु
			rb_erase(&pstat->node, &page_caller_tree);
			मुक्त(pstat);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool perf_kmem__skip_sample(काष्ठा perf_sample *sample)
अणु
	/* skip sample based on समय? */
	अगर (perf_समय__skip_sample(&pसमय, sample->समय))
		वापस true;

	वापस false;
पूर्ण

प्रकार पूर्णांक (*tracepoपूर्णांक_handler)(काष्ठा evsel *evsel,
				  काष्ठा perf_sample *sample);

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool __maybe_unused,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine)
अणु
	पूर्णांक err = 0;
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid,
							sample->tid);

	अगर (thपढ़ो == शून्य) अणु
		pr_debug("problem processing %d event, skipping it.\n",
			 event->header.type);
		वापस -1;
	पूर्ण

	अगर (perf_kmem__skip_sample(sample))
		वापस 0;

	dump_म_लिखो(" ... thread: %s:%d\n", thपढ़ो__comm_str(thपढ़ो), thपढ़ो->tid);

	अगर (evsel->handler != शून्य) अणु
		tracepoपूर्णांक_handler f = evsel->handler;
		err = f(evsel, sample);
	पूर्ण

	thपढ़ो__put(thपढ़ो);

	वापस err;
पूर्ण

अटल काष्ठा perf_tool perf_kmem = अणु
	.sample		 = process_sample_event,
	.comm		 = perf_event__process_comm,
	.mmap		 = perf_event__process_mmap,
	.mmap2		 = perf_event__process_mmap2,
	.namespaces	 = perf_event__process_namespaces,
	.ordered_events	 = true,
पूर्ण;

अटल द्विगुन fragmentation(अचिन्हित दीर्घ n_req, अचिन्हित दीर्घ n_alloc)
अणु
	अगर (n_alloc == 0)
		वापस 0.0;
	अन्यथा
		वापस 100.0 - (100.0 * n_req / n_alloc);
पूर्ण

अटल व्योम __prपूर्णांक_slab_result(काष्ठा rb_root *root,
				काष्ठा perf_session *session,
				पूर्णांक n_lines, पूर्णांक is_caller)
अणु
	काष्ठा rb_node *next;
	काष्ठा machine *machine = &session->machines.host;

	म_लिखो("%.105s\n", graph_करोtted_line);
	म_लिखो(" %-34s |",  is_caller ? "Callsite": "Alloc Ptr");
	म_लिखो(" Total_alloc/Per | Total_req/Per   | Hit      | Ping-pong | Frag\n");
	म_लिखो("%.105s\n", graph_करोtted_line);

	next = rb_first(root);

	जबतक (next && n_lines--) अणु
		काष्ठा alloc_stat *data = rb_entry(next, काष्ठा alloc_stat,
						   node);
		काष्ठा symbol *sym = शून्य;
		काष्ठा map *map;
		अक्षर buf[बफ_मान];
		u64 addr;

		अगर (is_caller) अणु
			addr = data->call_site;
			अगर (!raw_ip)
				sym = machine__find_kernel_symbol(machine, addr, &map);
		पूर्ण अन्यथा
			addr = data->ptr;

		अगर (sym != शून्य)
			snम_लिखो(buf, माप(buf), "%s+%" PRIx64 "", sym->name,
				 addr - map->unmap_ip(map, sym->start));
		अन्यथा
			snम_लिखो(buf, माप(buf), "%#" PRIx64 "", addr);
		म_लिखो(" %-34s |", buf);

		म_लिखो(" %9llu/%-5lu | %9llu/%-5lu | %8lu | %9lu | %6.3f%%\n",
		       (अचिन्हित दीर्घ दीर्घ)data->bytes_alloc,
		       (अचिन्हित दीर्घ)data->bytes_alloc / data->hit,
		       (अचिन्हित दीर्घ दीर्घ)data->bytes_req,
		       (अचिन्हित दीर्घ)data->bytes_req / data->hit,
		       (अचिन्हित दीर्घ)data->hit,
		       (अचिन्हित दीर्घ)data->pingpong,
		       fragmentation(data->bytes_req, data->bytes_alloc));

		next = rb_next(next);
	पूर्ण

	अगर (n_lines == -1)
		म_लिखो(" ...                                | ...             | ...             | ...      | ...       | ...   \n");

	म_लिखो("%.105s\n", graph_करोtted_line);
पूर्ण

अटल स्थिर अक्षर * स्थिर migrate_type_str[] = अणु
	"UNMOVABL",
	"RECLAIM",
	"MOVABLE",
	"RESERVED",
	"CMA/ISLT",
	"UNKNOWN",
पूर्ण;

अटल व्योम __prपूर्णांक_page_alloc_result(काष्ठा perf_session *session, पूर्णांक n_lines)
अणु
	काष्ठा rb_node *next = rb_first(&page_alloc_sorted);
	काष्ठा machine *machine = &session->machines.host;
	स्थिर अक्षर *क्रमmat;
	पूर्णांक gfp_len = max(म_माप("GFP flags"), max_gfp_len);

	म_लिखो("\n%.105s\n", graph_करोtted_line);
	म_लिखो(" %-16s | %5s alloc (KB) | Hits      | Order | Mig.type | %-*s | Callsite\n",
	       use_pfn ? "PFN" : "Page", live_page ? "Live" : "Total",
	       gfp_len, "GFP flags");
	म_लिखो("%.105s\n", graph_करोtted_line);

	अगर (use_pfn)
		क्रमmat = " %16llu | %'16llu | %'9d | %5d | %8s | %-*s | %s\n";
	अन्यथा
		क्रमmat = " %016llx | %'16llu | %'9d | %5d | %8s | %-*s | %s\n";

	जबतक (next && n_lines--) अणु
		काष्ठा page_stat *data;
		काष्ठा symbol *sym;
		काष्ठा map *map;
		अक्षर buf[32];
		अक्षर *caller = buf;

		data = rb_entry(next, काष्ठा page_stat, node);
		sym = machine__find_kernel_symbol(machine, data->callsite, &map);
		अगर (sym)
			caller = sym->name;
		अन्यथा
			scnम_लिखो(buf, माप(buf), "%"PRIx64, data->callsite);

		म_लिखो(क्रमmat, (अचिन्हित दीर्घ दीर्घ)data->page,
		       (अचिन्हित दीर्घ दीर्घ)data->alloc_bytes / 1024,
		       data->nr_alloc, data->order,
		       migrate_type_str[data->migrate_type],
		       gfp_len, compact_gfp_string(data->gfp_flags), caller);

		next = rb_next(next);
	पूर्ण

	अगर (n_lines == -1) अणु
		म_लिखो(" ...              | ...              | ...       | ...   | ...      | %-*s | ...\n",
		       gfp_len, "...");
	पूर्ण

	म_लिखो("%.105s\n", graph_करोtted_line);
पूर्ण

अटल व्योम __prपूर्णांक_page_caller_result(काष्ठा perf_session *session, पूर्णांक n_lines)
अणु
	काष्ठा rb_node *next = rb_first(&page_caller_sorted);
	काष्ठा machine *machine = &session->machines.host;
	पूर्णांक gfp_len = max(म_माप("GFP flags"), max_gfp_len);

	म_लिखो("\n%.105s\n", graph_करोtted_line);
	म_लिखो(" %5s alloc (KB) | Hits      | Order | Mig.type | %-*s | Callsite\n",
	       live_page ? "Live" : "Total", gfp_len, "GFP flags");
	म_लिखो("%.105s\n", graph_करोtted_line);

	जबतक (next && n_lines--) अणु
		काष्ठा page_stat *data;
		काष्ठा symbol *sym;
		काष्ठा map *map;
		अक्षर buf[32];
		अक्षर *caller = buf;

		data = rb_entry(next, काष्ठा page_stat, node);
		sym = machine__find_kernel_symbol(machine, data->callsite, &map);
		अगर (sym)
			caller = sym->name;
		अन्यथा
			scnम_लिखो(buf, माप(buf), "%"PRIx64, data->callsite);

		म_लिखो(" %'16llu | %'9d | %5d | %8s | %-*s | %s\n",
		       (अचिन्हित दीर्घ दीर्घ)data->alloc_bytes / 1024,
		       data->nr_alloc, data->order,
		       migrate_type_str[data->migrate_type],
		       gfp_len, compact_gfp_string(data->gfp_flags), caller);

		next = rb_next(next);
	पूर्ण

	अगर (n_lines == -1) अणु
		म_लिखो(" ...              | ...       | ...   | ...      | %-*s | ...\n",
		       gfp_len, "...");
	पूर्ण

	म_लिखो("%.105s\n", graph_करोtted_line);
पूर्ण

अटल व्योम prपूर्णांक_gfp_flags(व्योम)
अणु
	पूर्णांक i;

	म_लिखो("#\n");
	म_लिखो("# GFP flags\n");
	म_लिखो("# ---------\n");
	क्रम (i = 0; i < nr_gfps; i++) अणु
		म_लिखो("# %08x: %*s: %s\n", gfps[i].flags,
		       (पूर्णांक) max_gfp_len, gfps[i].compact_str,
		       gfps[i].human_पढ़ोable);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_slab_summary(व्योम)
अणु
	म_लिखो("\nSUMMARY (SLAB allocator)");
	म_लिखो("\n========================\n");
	म_लिखो("Total bytes requested: %'lu\n", total_requested);
	म_लिखो("Total bytes allocated: %'lu\n", total_allocated);
	म_लिखो("Total bytes freed:     %'lu\n", total_मुक्तd);
	अगर (total_allocated > total_मुक्तd) अणु
		म_लिखो("Net total bytes allocated: %'lu\n",
		total_allocated - total_मुक्तd);
	पूर्ण
	म_लिखो("Total bytes wasted on internal fragmentation: %'lu\n",
	       total_allocated - total_requested);
	म_लिखो("Internal fragmentation: %f%%\n",
	       fragmentation(total_requested, total_allocated));
	म_लिखो("Cross CPU allocations: %'lu/%'lu\n", nr_cross_allocs, nr_allocs);
पूर्ण

अटल व्योम prपूर्णांक_page_summary(व्योम)
अणु
	पूर्णांक o, m;
	u64 nr_alloc_मुक्तd = nr_page_मुक्तs - nr_page_nomatch;
	u64 total_alloc_मुक्तd_bytes = total_page_मुक्त_bytes - total_page_nomatch_bytes;

	म_लिखो("\nSUMMARY (page allocator)");
	म_लिखो("\n========================\n");
	म_लिखो("%-30s: %'16lu   [ %'16"PRIu64" KB ]\n", "Total allocation requests",
	       nr_page_allocs, total_page_alloc_bytes / 1024);
	म_लिखो("%-30s: %'16lu   [ %'16"PRIu64" KB ]\n", "Total free requests",
	       nr_page_मुक्तs, total_page_मुक्त_bytes / 1024);
	म_लिखो("\n");

	म_लिखो("%-30s: %'16"PRIu64"   [ %'16"PRIu64" KB ]\n", "Total alloc+freed requests",
	       nr_alloc_मुक्तd, (total_alloc_मुक्तd_bytes) / 1024);
	म_लिखो("%-30s: %'16"PRIu64"   [ %'16"PRIu64" KB ]\n", "Total alloc-only requests",
	       nr_page_allocs - nr_alloc_मुक्तd,
	       (total_page_alloc_bytes - total_alloc_मुक्तd_bytes) / 1024);
	म_लिखो("%-30s: %'16lu   [ %'16"PRIu64" KB ]\n", "Total free-only requests",
	       nr_page_nomatch, total_page_nomatch_bytes / 1024);
	म_लिखो("\n");

	म_लिखो("%-30s: %'16lu   [ %'16"PRIu64" KB ]\n", "Total allocation failures",
	       nr_page_fails, total_page_fail_bytes / 1024);
	म_लिखो("\n");

	म_लिखो("%5s  %12s  %12s  %12s  %12s  %12s\n", "Order",  "Unmovable",
	       "Reclaimable", "Movable", "Reserved", "CMA/Isolated");
	म_लिखो("%.5s  %.12s  %.12s  %.12s  %.12s  %.12s\n", graph_करोtted_line,
	       graph_करोtted_line, graph_करोtted_line, graph_करोtted_line,
	       graph_करोtted_line, graph_करोtted_line);

	क्रम (o = 0; o < MAX_PAGE_ORDER; o++) अणु
		म_लिखो("%5d", o);
		क्रम (m = 0; m < MAX_MIGRATE_TYPES - 1; m++) अणु
			अगर (order_stats[o][m])
				म_लिखो("  %'12d", order_stats[o][m]);
			अन्यथा
				म_लिखो("  %12c", '.');
		पूर्ण
		म_लिखो("\n");
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_slab_result(काष्ठा perf_session *session)
अणु
	अगर (caller_flag)
		__prपूर्णांक_slab_result(&root_caller_sorted, session, caller_lines, 1);
	अगर (alloc_flag)
		__prपूर्णांक_slab_result(&root_alloc_sorted, session, alloc_lines, 0);
	prपूर्णांक_slab_summary();
पूर्ण

अटल व्योम prपूर्णांक_page_result(काष्ठा perf_session *session)
अणु
	अगर (caller_flag || alloc_flag)
		prपूर्णांक_gfp_flags();
	अगर (caller_flag)
		__prपूर्णांक_page_caller_result(session, caller_lines);
	अगर (alloc_flag)
		__prपूर्णांक_page_alloc_result(session, alloc_lines);
	prपूर्णांक_page_summary();
पूर्ण

अटल व्योम prपूर्णांक_result(काष्ठा perf_session *session)
अणु
	अगर (kmem_slab)
		prपूर्णांक_slab_result(session);
	अगर (kmem_page)
		prपूर्णांक_page_result(session);
पूर्ण

अटल LIST_HEAD(slab_caller_sort);
अटल LIST_HEAD(slab_alloc_sort);
अटल LIST_HEAD(page_caller_sort);
अटल LIST_HEAD(page_alloc_sort);

अटल व्योम sort_slab_insert(काष्ठा rb_root *root, काष्ठा alloc_stat *data,
			     काष्ठा list_head *sort_list)
अणु
	काष्ठा rb_node **new = &(root->rb_node);
	काष्ठा rb_node *parent = शून्य;
	काष्ठा sort_dimension *sort;

	जबतक (*new) अणु
		काष्ठा alloc_stat *this;
		पूर्णांक cmp = 0;

		this = rb_entry(*new, काष्ठा alloc_stat, node);
		parent = *new;

		list_क्रम_each_entry(sort, sort_list, list) अणु
			cmp = sort->cmp(data, this);
			अगर (cmp)
				अवरोध;
		पूर्ण

		अगर (cmp > 0)
			new = &((*new)->rb_left);
		अन्यथा
			new = &((*new)->rb_right);
	पूर्ण

	rb_link_node(&data->node, parent, new);
	rb_insert_color(&data->node, root);
पूर्ण

अटल व्योम __sort_slab_result(काष्ठा rb_root *root, काष्ठा rb_root *root_sorted,
			       काष्ठा list_head *sort_list)
अणु
	काष्ठा rb_node *node;
	काष्ठा alloc_stat *data;

	क्रम (;;) अणु
		node = rb_first(root);
		अगर (!node)
			अवरोध;

		rb_erase(node, root);
		data = rb_entry(node, काष्ठा alloc_stat, node);
		sort_slab_insert(root_sorted, data, sort_list);
	पूर्ण
पूर्ण

अटल व्योम sort_page_insert(काष्ठा rb_root *root, काष्ठा page_stat *data,
			     काष्ठा list_head *sort_list)
अणु
	काष्ठा rb_node **new = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा sort_dimension *sort;

	जबतक (*new) अणु
		काष्ठा page_stat *this;
		पूर्णांक cmp = 0;

		this = rb_entry(*new, काष्ठा page_stat, node);
		parent = *new;

		list_क्रम_each_entry(sort, sort_list, list) अणु
			cmp = sort->cmp(data, this);
			अगर (cmp)
				अवरोध;
		पूर्ण

		अगर (cmp > 0)
			new = &parent->rb_left;
		अन्यथा
			new = &parent->rb_right;
	पूर्ण

	rb_link_node(&data->node, parent, new);
	rb_insert_color(&data->node, root);
पूर्ण

अटल व्योम __sort_page_result(काष्ठा rb_root *root, काष्ठा rb_root *root_sorted,
			       काष्ठा list_head *sort_list)
अणु
	काष्ठा rb_node *node;
	काष्ठा page_stat *data;

	क्रम (;;) अणु
		node = rb_first(root);
		अगर (!node)
			अवरोध;

		rb_erase(node, root);
		data = rb_entry(node, काष्ठा page_stat, node);
		sort_page_insert(root_sorted, data, sort_list);
	पूर्ण
पूर्ण

अटल व्योम sort_result(व्योम)
अणु
	अगर (kmem_slab) अणु
		__sort_slab_result(&root_alloc_stat, &root_alloc_sorted,
				   &slab_alloc_sort);
		__sort_slab_result(&root_caller_stat, &root_caller_sorted,
				   &slab_caller_sort);
	पूर्ण
	अगर (kmem_page) अणु
		अगर (live_page)
			__sort_page_result(&page_live_tree, &page_alloc_sorted,
					   &page_alloc_sort);
		अन्यथा
			__sort_page_result(&page_alloc_tree, &page_alloc_sorted,
					   &page_alloc_sort);

		__sort_page_result(&page_caller_tree, &page_caller_sorted,
				   &page_caller_sort);
	पूर्ण
पूर्ण

अटल पूर्णांक __cmd_kmem(काष्ठा perf_session *session)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा evsel *evsel;
	स्थिर काष्ठा evsel_str_handler kmem_tracepoपूर्णांकs[] = अणु
		/* slab allocator */
		अणु "kmem:kmalloc",		evsel__process_alloc_event, पूर्ण,
		अणु "kmem:kmem_cache_alloc",	evsel__process_alloc_event, पूर्ण,
		अणु "kmem:kmalloc_node",		evsel__process_alloc_node_event, पूर्ण,
		अणु "kmem:kmem_cache_alloc_node", evsel__process_alloc_node_event, पूर्ण,
		अणु "kmem:kfree",			evsel__process_मुक्त_event, पूर्ण,
		अणु "kmem:kmem_cache_free",	evsel__process_मुक्त_event, पूर्ण,
		/* page allocator */
		अणु "kmem:mm_page_alloc",		evsel__process_page_alloc_event, पूर्ण,
		अणु "kmem:mm_page_free",		evsel__process_page_मुक्त_event, पूर्ण,
	पूर्ण;

	अगर (!perf_session__has_traces(session, "kmem record"))
		जाओ out;

	अगर (perf_session__set_tracepoपूर्णांकs_handlers(session, kmem_tracepoपूर्णांकs)) अणु
		pr_err("Initializing perf session tracepoint handlers failed\n");
		जाओ out;
	पूर्ण

	evlist__क्रम_each_entry(session->evlist, evsel) अणु
		अगर (!म_भेद(evsel__name(evsel), "kmem:mm_page_alloc") &&
		    evsel__field(evsel, "pfn")) अणु
			use_pfn = true;
			अवरोध;
		पूर्ण
	पूर्ण

	setup_pager();
	err = perf_session__process_events(session);
	अगर (err != 0) अणु
		pr_err("error during process events: %d\n", err);
		जाओ out;
	पूर्ण
	sort_result();
	prपूर्णांक_result(session);
out:
	वापस err;
पूर्ण

/* slab sort keys */
अटल पूर्णांक ptr_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा alloc_stat *l = a;
	काष्ठा alloc_stat *r = b;

	अगर (l->ptr < r->ptr)
		वापस -1;
	अन्यथा अगर (l->ptr > r->ptr)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension ptr_sort_dimension = अणु
	.name	= "ptr",
	.cmp	= ptr_cmp,
पूर्ण;

अटल पूर्णांक slab_callsite_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा alloc_stat *l = a;
	काष्ठा alloc_stat *r = b;

	अगर (l->call_site < r->call_site)
		वापस -1;
	अन्यथा अगर (l->call_site > r->call_site)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension callsite_sort_dimension = अणु
	.name	= "callsite",
	.cmp	= slab_callsite_cmp,
पूर्ण;

अटल पूर्णांक hit_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा alloc_stat *l = a;
	काष्ठा alloc_stat *r = b;

	अगर (l->hit < r->hit)
		वापस -1;
	अन्यथा अगर (l->hit > r->hit)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension hit_sort_dimension = अणु
	.name	= "hit",
	.cmp	= hit_cmp,
पूर्ण;

अटल पूर्णांक bytes_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा alloc_stat *l = a;
	काष्ठा alloc_stat *r = b;

	अगर (l->bytes_alloc < r->bytes_alloc)
		वापस -1;
	अन्यथा अगर (l->bytes_alloc > r->bytes_alloc)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension bytes_sort_dimension = अणु
	.name	= "bytes",
	.cmp	= bytes_cmp,
पूर्ण;

अटल पूर्णांक frag_cmp(व्योम *a, व्योम *b)
अणु
	द्विगुन x, y;
	काष्ठा alloc_stat *l = a;
	काष्ठा alloc_stat *r = b;

	x = fragmentation(l->bytes_req, l->bytes_alloc);
	y = fragmentation(r->bytes_req, r->bytes_alloc);

	अगर (x < y)
		वापस -1;
	अन्यथा अगर (x > y)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension frag_sort_dimension = अणु
	.name	= "frag",
	.cmp	= frag_cmp,
पूर्ण;

अटल पूर्णांक pingpong_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा alloc_stat *l = a;
	काष्ठा alloc_stat *r = b;

	अगर (l->pingpong < r->pingpong)
		वापस -1;
	अन्यथा अगर (l->pingpong > r->pingpong)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension pingpong_sort_dimension = अणु
	.name	= "pingpong",
	.cmp	= pingpong_cmp,
पूर्ण;

/* page sort keys */
अटल पूर्णांक page_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा page_stat *l = a;
	काष्ठा page_stat *r = b;

	अगर (l->page < r->page)
		वापस -1;
	अन्यथा अगर (l->page > r->page)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension page_sort_dimension = अणु
	.name	= "page",
	.cmp	= page_cmp,
पूर्ण;

अटल पूर्णांक page_callsite_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा page_stat *l = a;
	काष्ठा page_stat *r = b;

	अगर (l->callsite < r->callsite)
		वापस -1;
	अन्यथा अगर (l->callsite > r->callsite)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension page_callsite_sort_dimension = अणु
	.name	= "callsite",
	.cmp	= page_callsite_cmp,
पूर्ण;

अटल पूर्णांक page_hit_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा page_stat *l = a;
	काष्ठा page_stat *r = b;

	अगर (l->nr_alloc < r->nr_alloc)
		वापस -1;
	अन्यथा अगर (l->nr_alloc > r->nr_alloc)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension page_hit_sort_dimension = अणु
	.name	= "hit",
	.cmp	= page_hit_cmp,
पूर्ण;

अटल पूर्णांक page_bytes_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा page_stat *l = a;
	काष्ठा page_stat *r = b;

	अगर (l->alloc_bytes < r->alloc_bytes)
		वापस -1;
	अन्यथा अगर (l->alloc_bytes > r->alloc_bytes)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension page_bytes_sort_dimension = अणु
	.name	= "bytes",
	.cmp	= page_bytes_cmp,
पूर्ण;

अटल पूर्णांक page_order_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा page_stat *l = a;
	काष्ठा page_stat *r = b;

	अगर (l->order < r->order)
		वापस -1;
	अन्यथा अगर (l->order > r->order)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension page_order_sort_dimension = अणु
	.name	= "order",
	.cmp	= page_order_cmp,
पूर्ण;

अटल पूर्णांक migrate_type_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा page_stat *l = a;
	काष्ठा page_stat *r = b;

	/* क्रम पूर्णांकernal use to find मुक्त'd page */
	अगर (l->migrate_type == -1U)
		वापस 0;

	अगर (l->migrate_type < r->migrate_type)
		वापस -1;
	अन्यथा अगर (l->migrate_type > r->migrate_type)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension migrate_type_sort_dimension = अणु
	.name	= "migtype",
	.cmp	= migrate_type_cmp,
पूर्ण;

अटल पूर्णांक gfp_flags_cmp(व्योम *a, व्योम *b)
अणु
	काष्ठा page_stat *l = a;
	काष्ठा page_stat *r = b;

	/* क्रम पूर्णांकernal use to find मुक्त'd page */
	अगर (l->gfp_flags == -1U)
		वापस 0;

	अगर (l->gfp_flags < r->gfp_flags)
		वापस -1;
	अन्यथा अगर (l->gfp_flags > r->gfp_flags)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा sort_dimension gfp_flags_sort_dimension = अणु
	.name	= "gfp",
	.cmp	= gfp_flags_cmp,
पूर्ण;

अटल काष्ठा sort_dimension *slab_sorts[] = अणु
	&ptr_sort_dimension,
	&callsite_sort_dimension,
	&hit_sort_dimension,
	&bytes_sort_dimension,
	&frag_sort_dimension,
	&pingpong_sort_dimension,
पूर्ण;

अटल काष्ठा sort_dimension *page_sorts[] = अणु
	&page_sort_dimension,
	&page_callsite_sort_dimension,
	&page_hit_sort_dimension,
	&page_bytes_sort_dimension,
	&page_order_sort_dimension,
	&migrate_type_sort_dimension,
	&gfp_flags_sort_dimension,
पूर्ण;

अटल पूर्णांक slab_sort_dimension__add(स्थिर अक्षर *tok, काष्ठा list_head *list)
अणु
	काष्ठा sort_dimension *sort;
	पूर्णांक i;

	क्रम (i = 0; i < (पूर्णांक)ARRAY_SIZE(slab_sorts); i++) अणु
		अगर (!म_भेद(slab_sorts[i]->name, tok)) अणु
			sort = memdup(slab_sorts[i], माप(*slab_sorts[i]));
			अगर (!sort) अणु
				pr_err("%s: memdup failed\n", __func__);
				वापस -1;
			पूर्ण
			list_add_tail(&sort->list, list);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक page_sort_dimension__add(स्थिर अक्षर *tok, काष्ठा list_head *list)
अणु
	काष्ठा sort_dimension *sort;
	पूर्णांक i;

	क्रम (i = 0; i < (पूर्णांक)ARRAY_SIZE(page_sorts); i++) अणु
		अगर (!म_भेद(page_sorts[i]->name, tok)) अणु
			sort = memdup(page_sorts[i], माप(*page_sorts[i]));
			अगर (!sort) अणु
				pr_err("%s: memdup failed\n", __func__);
				वापस -1;
			पूर्ण
			list_add_tail(&sort->list, list);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक setup_slab_sorting(काष्ठा list_head *sort_list, स्थिर अक्षर *arg)
अणु
	अक्षर *tok;
	अक्षर *str = strdup(arg);
	अक्षर *pos = str;

	अगर (!str) अणु
		pr_err("%s: strdup failed\n", __func__);
		वापस -1;
	पूर्ण

	जबतक (true) अणु
		tok = strsep(&pos, ",");
		अगर (!tok)
			अवरोध;
		अगर (slab_sort_dimension__add(tok, sort_list) < 0) अणु
			pr_err("Unknown slab --sort key: '%s'", tok);
			मुक्त(str);
			वापस -1;
		पूर्ण
	पूर्ण

	मुक्त(str);
	वापस 0;
पूर्ण

अटल पूर्णांक setup_page_sorting(काष्ठा list_head *sort_list, स्थिर अक्षर *arg)
अणु
	अक्षर *tok;
	अक्षर *str = strdup(arg);
	अक्षर *pos = str;

	अगर (!str) अणु
		pr_err("%s: strdup failed\n", __func__);
		वापस -1;
	पूर्ण

	जबतक (true) अणु
		tok = strsep(&pos, ",");
		अगर (!tok)
			अवरोध;
		अगर (page_sort_dimension__add(tok, sort_list) < 0) अणु
			pr_err("Unknown page --sort key: '%s'", tok);
			मुक्त(str);
			वापस -1;
		पूर्ण
	पूर्ण

	मुक्त(str);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_sort_opt(स्थिर काष्ठा option *opt __maybe_unused,
			  स्थिर अक्षर *arg, पूर्णांक unset __maybe_unused)
अणु
	अगर (!arg)
		वापस -1;

	अगर (kmem_page > kmem_slab ||
	    (kmem_page == 0 && kmem_slab == 0 && kmem_शेष == KMEM_PAGE)) अणु
		अगर (caller_flag > alloc_flag)
			वापस setup_page_sorting(&page_caller_sort, arg);
		अन्यथा
			वापस setup_page_sorting(&page_alloc_sort, arg);
	पूर्ण अन्यथा अणु
		अगर (caller_flag > alloc_flag)
			वापस setup_slab_sorting(&slab_caller_sort, arg);
		अन्यथा
			वापस setup_slab_sorting(&slab_alloc_sort, arg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_caller_opt(स्थिर काष्ठा option *opt __maybe_unused,
			    स्थिर अक्षर *arg __maybe_unused,
			    पूर्णांक unset __maybe_unused)
अणु
	caller_flag = (alloc_flag + 1);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_alloc_opt(स्थिर काष्ठा option *opt __maybe_unused,
			   स्थिर अक्षर *arg __maybe_unused,
			   पूर्णांक unset __maybe_unused)
अणु
	alloc_flag = (caller_flag + 1);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_slab_opt(स्थिर काष्ठा option *opt __maybe_unused,
			  स्थिर अक्षर *arg __maybe_unused,
			  पूर्णांक unset __maybe_unused)
अणु
	kmem_slab = (kmem_page + 1);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_page_opt(स्थिर काष्ठा option *opt __maybe_unused,
			  स्थिर अक्षर *arg __maybe_unused,
			  पूर्णांक unset __maybe_unused)
अणु
	kmem_page = (kmem_slab + 1);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_line_opt(स्थिर काष्ठा option *opt __maybe_unused,
			  स्थिर अक्षर *arg, पूर्णांक unset __maybe_unused)
अणु
	पूर्णांक lines;

	अगर (!arg)
		वापस -1;

	lines = म_से_अदीर्घ(arg, शून्य, 10);

	अगर (caller_flag > alloc_flag)
		caller_lines = lines;
	अन्यथा
		alloc_lines = lines;

	वापस 0;
पूर्ण

अटल पूर्णांक __cmd_record(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर * स्थिर record_args[] = अणु
	"record", "-a", "-R", "-c", "1",
	पूर्ण;
	स्थिर अक्षर * स्थिर slab_events[] = अणु
	"-e", "kmem:kmalloc",
	"-e", "kmem:kmalloc_node",
	"-e", "kmem:kfree",
	"-e", "kmem:kmem_cache_alloc",
	"-e", "kmem:kmem_cache_alloc_node",
	"-e", "kmem:kmem_cache_free",
	पूर्ण;
	स्थिर अक्षर * स्थिर page_events[] = अणु
	"-e", "kmem:mm_page_alloc",
	"-e", "kmem:mm_page_free",
	पूर्ण;
	अचिन्हित पूर्णांक rec_argc, i, j;
	स्थिर अक्षर **rec_argv;

	rec_argc = ARRAY_SIZE(record_args) + argc - 1;
	अगर (kmem_slab)
		rec_argc += ARRAY_SIZE(slab_events);
	अगर (kmem_page)
		rec_argc += ARRAY_SIZE(page_events) + 1; /* क्रम -g */

	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));

	अगर (rec_argv == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(record_args); i++)
		rec_argv[i] = strdup(record_args[i]);

	अगर (kmem_slab) अणु
		क्रम (j = 0; j < ARRAY_SIZE(slab_events); j++, i++)
			rec_argv[i] = strdup(slab_events[j]);
	पूर्ण
	अगर (kmem_page) अणु
		rec_argv[i++] = strdup("-g");

		क्रम (j = 0; j < ARRAY_SIZE(page_events); j++, i++)
			rec_argv[i] = strdup(page_events[j]);
	पूर्ण

	क्रम (j = 1; j < (अचिन्हित पूर्णांक)argc; j++, i++)
		rec_argv[i] = argv[j];

	वापस cmd_record(i, rec_argv);
पूर्ण

अटल पूर्णांक kmem_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb __maybe_unused)
अणु
	अगर (!म_भेद(var, "kmem.default")) अणु
		अगर (!म_भेद(value, "slab"))
			kmem_शेष = KMEM_SLAB;
		अन्यथा अगर (!म_भेद(value, "page"))
			kmem_शेष = KMEM_PAGE;
		अन्यथा
			pr_err("invalid default value ('slab' or 'page' required): %s\n",
			       value);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cmd_kmem(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर * स्थिर शेष_slab_sort = "frag,hit,bytes";
	स्थिर अक्षर * स्थिर शेष_page_sort = "bytes,hit";
	काष्ठा perf_data data = अणु
		.mode = PERF_DATA_MODE_READ,
	पूर्ण;
	स्थिर काष्ठा option kmem_options[] = अणु
	OPT_STRING('i', "input", &input_name, "file", "input file name"),
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show symbol address, etc)"),
	OPT_CALLBACK_NOOPT(0, "caller", शून्य, शून्य,
			   "show per-callsite statistics", parse_caller_opt),
	OPT_CALLBACK_NOOPT(0, "alloc", शून्य, शून्य,
			   "show per-allocation statistics", parse_alloc_opt),
	OPT_CALLBACK('s', "sort", शून्य, "key[,key2...]",
		     "sort by keys: ptr, callsite, bytes, hit, pingpong, frag, "
		     "page, order, migtype, gfp", parse_sort_opt),
	OPT_CALLBACK('l', "line", शून्य, "num", "show n lines", parse_line_opt),
	OPT_BOOLEAN(0, "raw-ip", &raw_ip, "show raw ip instead of symbol"),
	OPT_BOOLEAN('f', "force", &data.force, "don't complain, करो it"),
	OPT_CALLBACK_NOOPT(0, "slab", शून्य, शून्य, "Analyze slab allocator",
			   parse_slab_opt),
	OPT_CALLBACK_NOOPT(0, "page", शून्य, शून्य, "Analyze page allocator",
			   parse_page_opt),
	OPT_BOOLEAN(0, "live", &live_page, "Show live page stat"),
	OPT_STRING(0, "time", &समय_str, "str",
		   "Time span of interest (start,stop)"),
	OPT_END()
	पूर्ण;
	स्थिर अक्षर *स्थिर kmem_subcommands[] = अणु "record", "stat", शून्य पूर्ण;
	स्थिर अक्षर *kmem_usage[] = अणु
		शून्य,
		शून्य
	पूर्ण;
	काष्ठा perf_session *session;
	अटल स्थिर अक्षर errmsg[] = "No %s allocation events found.  Have you run 'perf kmem record --%s'?\n";
	पूर्णांक ret = perf_config(kmem_config, शून्य);

	अगर (ret)
		वापस ret;

	argc = parse_options_subcommand(argc, argv, kmem_options,
					kmem_subcommands, kmem_usage,
					PARSE_OPT_STOP_AT_NON_OPTION);

	अगर (!argc)
		usage_with_options(kmem_usage, kmem_options);

	अगर (kmem_slab == 0 && kmem_page == 0) अणु
		अगर (kmem_शेष == KMEM_SLAB)
			kmem_slab = 1;
		अन्यथा
			kmem_page = 1;
	पूर्ण

	अगर (!म_भेदन(argv[0], "rec", 3)) अणु
		symbol__init(शून्य);
		वापस __cmd_record(argc, argv);
	पूर्ण

	data.path = input_name;

	kmem_session = session = perf_session__new(&data, false, &perf_kmem);
	अगर (IS_ERR(session))
		वापस PTR_ERR(session);

	ret = -1;

	अगर (kmem_slab) अणु
		अगर (!evlist__find_tracepoपूर्णांक_by_name(session->evlist, "kmem:kmalloc")) अणु
			pr_err(errmsg, "slab", "slab");
			जाओ out_delete;
		पूर्ण
	पूर्ण

	अगर (kmem_page) अणु
		काष्ठा evsel *evsel = evlist__find_tracepoपूर्णांक_by_name(session->evlist, "kmem:mm_page_alloc");

		अगर (evsel == शून्य) अणु
			pr_err(errmsg, "page", "page");
			जाओ out_delete;
		पूर्ण

		kmem_page_size = tep_get_page_size(evsel->tp_क्रमmat->tep);
		symbol_conf.use_callchain = true;
	पूर्ण

	symbol__init(&session->header.env);

	अगर (perf_समय__parse_str(&pसमय, समय_str) != 0) अणु
		pr_err("Invalid time string\n");
		ret = -EINVAL;
		जाओ out_delete;
	पूर्ण

	अगर (!म_भेद(argv[0], "stat")) अणु
		रखो_क्षेत्र(LC_ALL, "");

		अगर (cpu__setup_cpunode_map())
			जाओ out_delete;

		अगर (list_empty(&slab_caller_sort))
			setup_slab_sorting(&slab_caller_sort, शेष_slab_sort);
		अगर (list_empty(&slab_alloc_sort))
			setup_slab_sorting(&slab_alloc_sort, शेष_slab_sort);
		अगर (list_empty(&page_caller_sort))
			setup_page_sorting(&page_caller_sort, शेष_page_sort);
		अगर (list_empty(&page_alloc_sort))
			setup_page_sorting(&page_alloc_sort, शेष_page_sort);

		अगर (kmem_page) अणु
			setup_page_sorting(&page_alloc_sort_input,
					   "page,order,migtype,gfp");
			setup_page_sorting(&page_caller_sort_input,
					   "callsite,order,migtype,gfp");
		पूर्ण
		ret = __cmd_kmem(session);
	पूर्ण अन्यथा
		usage_with_options(kmem_usage, kmem_options);

out_delete:
	perf_session__delete(session);

	वापस ret;
पूर्ण

