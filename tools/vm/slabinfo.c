<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Slabinfo: Tool to get reports about sद_असल
 *
 * (C) 2007 sgi, Christoph Lameter
 * (C) 2011 Linux Foundation, Christoph Lameter
 *
 * Compile with:
 *
 * gcc -o slabinfo slabinfo.c
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <dirent.h>
#समावेश <strings.h>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <मानकतर्क.स>
#समावेश <getopt.h>
#समावेश <regex.h>
#समावेश <त्रुटिसं.स>

#घोषणा MAX_SLABS 500
#घोषणा MAX_ALIASES 500
#घोषणा MAX_NODES 1024

काष्ठा slabinfo अणु
	अक्षर *name;
	पूर्णांक alias;
	पूर्णांक refs;
	पूर्णांक aliases, align, cache_dma, cpu_sद_असल, destroy_by_rcu;
	अचिन्हित पूर्णांक hwcache_align, object_size, objs_per_slab;
	अचिन्हित पूर्णांक sanity_checks, slab_size, store_user, trace;
	पूर्णांक order, poison, reclaim_account, red_zone;
	अचिन्हित दीर्घ partial, objects, sद_असल, objects_partial, objects_total;
	अचिन्हित दीर्घ alloc_fastpath, alloc_slowpath;
	अचिन्हित दीर्घ मुक्त_fastpath, मुक्त_slowpath;
	अचिन्हित दीर्घ मुक्त_frozen, मुक्त_add_partial, मुक्त_हटाओ_partial;
	अचिन्हित दीर्घ alloc_from_partial, alloc_slab, मुक्त_slab, alloc_refill;
	अचिन्हित दीर्घ cpuslab_flush, deactivate_full, deactivate_empty;
	अचिन्हित दीर्घ deactivate_to_head, deactivate_to_tail;
	अचिन्हित दीर्घ deactivate_remote_मुक्तs, order_fallback;
	अचिन्हित दीर्घ cmpxchg_द्विगुन_cpu_fail, cmpxchg_द्विगुन_fail;
	अचिन्हित दीर्घ alloc_node_mismatch, deactivate_bypass;
	अचिन्हित दीर्घ cpu_partial_alloc, cpu_partial_मुक्त;
	पूर्णांक numa[MAX_NODES];
	पूर्णांक numa_partial[MAX_NODES];
पूर्ण slabinfo[MAX_SLABS];

काष्ठा aliasinfo अणु
	अक्षर *name;
	अक्षर *ref;
	काष्ठा slabinfo *slab;
पूर्ण aliasinfo[MAX_ALIASES];

पूर्णांक sद_असल;
पूर्णांक actual_sद_असल;
पूर्णांक aliases;
पूर्णांक alias_tarमाला_लो;
पूर्णांक highest_node;

अक्षर buffer[4096];

पूर्णांक show_empty;
पूर्णांक show_report;
पूर्णांक show_alias;
पूर्णांक show_slab;
पूर्णांक skip_zero = 1;
पूर्णांक show_numa;
पूर्णांक show_track;
पूर्णांक show_first_alias;
पूर्णांक validate;
पूर्णांक shrink;
पूर्णांक show_inverted;
पूर्णांक show_single_ref;
पूर्णांक show_totals;
पूर्णांक sort_size;
पूर्णांक sort_active;
पूर्णांक set_debug;
पूर्णांक show_ops;
पूर्णांक sort_partial;
पूर्णांक show_activity;
पूर्णांक output_lines = -1;
पूर्णांक sort_loss;
पूर्णांक extended_totals;
पूर्णांक show_bytes;
पूर्णांक unreclaim_only;

/* Debug options */
पूर्णांक sanity;
पूर्णांक redzone;
पूर्णांक poison;
पूर्णांक tracking;
पूर्णांक tracing;

पूर्णांक page_size;

regex_t pattern;

अटल व्योम fatal(स्थिर अक्षर *x, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, x);
	भख_लिखो(मानक_त्रुटि, x, ap);
	बहु_पूर्ण(ap);
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम usage(व्योम)
अणु
	म_लिखो("slabinfo 4/15/2011. (c) 2007 sgi/(c) 2011 Linux Foundation.\n\n"
		"slabinfo [-aABDefhilLnoPrsStTUvXz1] [N=K] [-dafzput] [slab-regexp]\n"
		"-a|--aliases           Show aliases\n"
		"-A|--activity          Most active slabs first\n"
		"-B|--Bytes             Show size in bytes\n"
		"-D|--display-active    Switch line format to activity\n"
		"-e|--empty             Show empty slabs\n"
		"-f|--first-alias       Show first alias\n"
		"-h|--help              Show usage information\n"
		"-i|--inverted          Inverted list\n"
		"-l|--slabs             Show slabs\n"
		"-L|--Loss              Sort by loss\n"
		"-n|--numa              Show NUMA information\n"
		"-N|--lines=K           Show the first K slabs\n"
		"-o|--ops               Show kmem_cache_ops\n"
		"-P|--partial		Sort by number of partial slabs\n"
		"-r|--report            Detailed report on single slabs\n"
		"-s|--shrink            Shrink slabs\n"
		"-S|--Size              Sort by size\n"
		"-t|--tracking          Show alloc/free information\n"
		"-T|--Totals            Show summary information\n"
		"-U|--Unreclaim         Show unreclaimable slabs only\n"
		"-v|--validate          Validate slabs\n"
		"-X|--Xtotals           Show extended summary information\n"
		"-z|--zero              Include empty slabs\n"
		"-1|--1ref              Single reference\n"

		"\n"
		"-d  | --debug          Switch off all debug options\n"
		"-da | --debug=a        Switch on all debug options (--debug=FZPU)\n"

		"\n"
		"-d[afzput] | --debug=[afzput]\n"
		"    f | F              Sanity Checks (SLAB_CONSISTENCY_CHECKS)\n"
		"    z | Z              Redzoning\n"
		"    p | P              Poisoning\n"
		"    u | U              Tracking\n"
		"    t | T              Tracing\n"

		"\nSorting options (--Loss, --Size, --Partial) are mutually exclusive\n"
	);
पूर्ण

अटल अचिन्हित दीर्घ पढ़ो_obj(स्थिर अक्षर *name)
अणु
	खाता *f = ख_खोलो(name, "r");

	अगर (!f)
		buffer[0] = 0;
	अन्यथा अणु
		अगर (!ख_माला_लो(buffer, माप(buffer), f))
			buffer[0] = 0;
		ख_बंद(f);
		अगर (buffer[म_माप(buffer)] == '\n')
			buffer[म_माप(buffer)] = 0;
	पूर्ण
	वापस म_माप(buffer);
पूर्ण


/*
 * Get the contents of an attribute
 */
अटल अचिन्हित दीर्घ get_obj(स्थिर अक्षर *name)
अणु
	अगर (!पढ़ो_obj(name))
		वापस 0;

	वापस म_से_द(buffer);
पूर्ण

अटल अचिन्हित दीर्घ get_obj_and_str(स्थिर अक्षर *name, अक्षर **x)
अणु
	अचिन्हित दीर्घ result = 0;
	अक्षर *p;

	*x = शून्य;

	अगर (!पढ़ो_obj(name)) अणु
		x = शून्य;
		वापस 0;
	पूर्ण
	result = म_से_अदीर्घ(buffer, &p, 10);
	जबतक (*p == ' ')
		p++;
	अगर (*p)
		*x = strdup(p);
	वापस result;
पूर्ण

अटल व्योम set_obj(काष्ठा slabinfo *s, स्थिर अक्षर *name, पूर्णांक n)
अणु
	अक्षर x[100];
	खाता *f;

	snम_लिखो(x, 100, "%s/%s", s->name, name);
	f = ख_खोलो(x, "w");
	अगर (!f)
		fatal("Cannot write to %s\n", x);

	ख_लिखो(f, "%d\n", n);
	ख_बंद(f);
पूर्ण

अटल अचिन्हित दीर्घ पढ़ो_slab_obj(काष्ठा slabinfo *s, स्थिर अक्षर *name)
अणु
	अक्षर x[100];
	खाता *f;
	माप_प्रकार l;

	snम_लिखो(x, 100, "%s/%s", s->name, name);
	f = ख_खोलो(x, "r");
	अगर (!f) अणु
		buffer[0] = 0;
		l = 0;
	पूर्ण अन्यथा अणु
		l = ख_पढ़ो(buffer, 1, माप(buffer), f);
		buffer[l] = 0;
		ख_बंद(f);
	पूर्ण
	वापस l;
पूर्ण


/*
 * Put a size string together
 */
अटल पूर्णांक store_size(अक्षर *buffer, अचिन्हित दीर्घ value)
अणु
	अचिन्हित दीर्घ भागisor = 1;
	अक्षर trailer = 0;
	पूर्णांक n;

	अगर (!show_bytes) अणु
		अगर (value > 1000000000UL) अणु
			भागisor = 100000000UL;
			trailer = 'G';
		पूर्ण अन्यथा अगर (value > 1000000UL) अणु
			भागisor = 100000UL;
			trailer = 'M';
		पूर्ण अन्यथा अगर (value > 1000UL) अणु
			भागisor = 100;
			trailer = 'K';
		पूर्ण
	पूर्ण

	value /= भागisor;
	n = प्र_लिखो(buffer, "%ld",value);
	अगर (trailer) अणु
		buffer[n] = trailer;
		n++;
		buffer[n] = 0;
	पूर्ण
	अगर (भागisor != 1) अणु
		स_हटाओ(buffer + n - 2, buffer + n - 3, 4);
		buffer[n-2] = '.';
		n++;
	पूर्ण
	वापस n;
पूर्ण

अटल व्योम decode_numa_list(पूर्णांक *numa, अक्षर *t)
अणु
	पूर्णांक node;
	पूर्णांक nr;

	स_रखो(numa, 0, MAX_NODES * माप(पूर्णांक));

	अगर (!t)
		वापस;

	जबतक (*t == 'N') अणु
		t++;
		node = म_से_अदीर्घ(t, &t, 10);
		अगर (*t == '=') अणु
			t++;
			nr = म_से_अदीर्घ(t, &t, 10);
			numa[node] = nr;
			अगर (node > highest_node)
				highest_node = node;
		पूर्ण
		जबतक (*t == ' ')
			t++;
	पूर्ण
पूर्ण

अटल व्योम slab_validate(काष्ठा slabinfo *s)
अणु
	अगर (म_भेद(s->name, "*") == 0)
		वापस;

	set_obj(s, "validate", 1);
पूर्ण

अटल व्योम slab_shrink(काष्ठा slabinfo *s)
अणु
	अगर (म_भेद(s->name, "*") == 0)
		वापस;

	set_obj(s, "shrink", 1);
पूर्ण

पूर्णांक line = 0;

अटल व्योम first_line(व्योम)
अणु
	अगर (show_activity)
		म_लिखो("Name                   Objects      Alloc       Free"
			"   %%Fast Fallb O CmpX   UL\n");
	अन्यथा
		म_लिखो("Name                   Objects Objsize           %s "
			"Slabs/Part/Cpu  O/S O %%Fr %%Ef Flg\n",
			sort_loss ? " Loss" : "Space");
पूर्ण

/*
 * Find the लघुest alias of a slab
 */
अटल काष्ठा aliasinfo *find_one_alias(काष्ठा slabinfo *find)
अणु
	काष्ठा aliasinfo *a;
	काष्ठा aliasinfo *best = शून्य;

	क्रम(a = aliasinfo;a < aliasinfo + aliases; a++) अणु
		अगर (a->slab == find &&
			(!best || म_माप(best->name) < म_माप(a->name))) अणु
				best = a;
				अगर (म_भेदन(a->name,"kmall", 5) == 0)
					वापस best;
			पूर्ण
	पूर्ण
	वापस best;
पूर्ण

अटल अचिन्हित दीर्घ slab_size(काष्ठा slabinfo *s)
अणु
	वापस 	s->sद_असल * (page_size << s->order);
पूर्ण

अटल अचिन्हित दीर्घ slab_activity(काष्ठा slabinfo *s)
अणु
	वापस 	s->alloc_fastpath + s->मुक्त_fastpath +
		s->alloc_slowpath + s->मुक्त_slowpath;
पूर्ण

अटल अचिन्हित दीर्घ slab_waste(काष्ठा slabinfo *s)
अणु
	वापस	slab_size(s) - s->objects * s->object_size;
पूर्ण

अटल व्योम slab_numa(काष्ठा slabinfo *s, पूर्णांक mode)
अणु
	पूर्णांक node;

	अगर (म_भेद(s->name, "*") == 0)
		वापस;

	अगर (!highest_node) अणु
		म_लिखो("\n%s: No NUMA information available.\n", s->name);
		वापस;
	पूर्ण

	अगर (skip_zero && !s->sद_असल)
		वापस;

	अगर (!line) अणु
		म_लिखो("\n%-21s:", mode ? "NUMA nodes" : "Slab");
		क्रम(node = 0; node <= highest_node; node++)
			म_लिखो(" %4d", node);
		म_लिखो("\n----------------------");
		क्रम(node = 0; node <= highest_node; node++)
			म_लिखो("-----");
		म_लिखो("\n");
	पूर्ण
	म_लिखो("%-21s ", mode ? "All slabs" : s->name);
	क्रम(node = 0; node <= highest_node; node++) अणु
		अक्षर b[20];

		store_size(b, s->numa[node]);
		म_लिखो(" %4s", b);
	पूर्ण
	म_लिखो("\n");
	अगर (mode) अणु
		म_लिखो("%-21s ", "Partial slabs");
		क्रम(node = 0; node <= highest_node; node++) अणु
			अक्षर b[20];

			store_size(b, s->numa_partial[node]);
			म_लिखो(" %4s", b);
		पूर्ण
		म_लिखो("\n");
	पूर्ण
	line++;
पूर्ण

अटल व्योम show_tracking(काष्ठा slabinfo *s)
अणु
	म_लिखो("\n%s: Kernel object allocation\n", s->name);
	म_लिखो("-----------------------------------------------------------------------\n");
	अगर (पढ़ो_slab_obj(s, "alloc_calls"))
		म_लिखो("%s", buffer);
	अन्यथा
		म_लिखो("No Data\n");

	म_लिखो("\n%s: Kernel object freeing\n", s->name);
	म_लिखो("------------------------------------------------------------------------\n");
	अगर (पढ़ो_slab_obj(s, "free_calls"))
		म_लिखो("%s", buffer);
	अन्यथा
		म_लिखो("No Data\n");

पूर्ण

अटल व्योम ops(काष्ठा slabinfo *s)
अणु
	अगर (म_भेद(s->name, "*") == 0)
		वापस;

	अगर (पढ़ो_slab_obj(s, "ops")) अणु
		म_लिखो("\n%s: kmem_cache operations\n", s->name);
		म_लिखो("--------------------------------------------\n");
		म_लिखो("%s", buffer);
	पूर्ण अन्यथा
		म_लिखो("\n%s has no kmem_cache operations\n", s->name);
पूर्ण

अटल स्थिर अक्षर *onoff(पूर्णांक x)
अणु
	अगर (x)
		वापस "On ";
	वापस "Off";
पूर्ण

अटल व्योम slab_stats(काष्ठा slabinfo *s)
अणु
	अचिन्हित दीर्घ total_alloc;
	अचिन्हित दीर्घ total_मुक्त;
	अचिन्हित दीर्घ total;

	अगर (!s->alloc_slab)
		वापस;

	total_alloc = s->alloc_fastpath + s->alloc_slowpath;
	total_मुक्त = s->मुक्त_fastpath + s->मुक्त_slowpath;

	अगर (!total_alloc)
		वापस;

	म_लिखो("\n");
	म_लिखो("Slab Perf Counter       Alloc     Free %%Al %%Fr\n");
	म_लिखो("--------------------------------------------------\n");
	म_लिखो("Fastpath             %8lu %8lu %3lu %3lu\n",
		s->alloc_fastpath, s->मुक्त_fastpath,
		s->alloc_fastpath * 100 / total_alloc,
		total_मुक्त ? s->मुक्त_fastpath * 100 / total_मुक्त : 0);
	म_लिखो("Slowpath             %8lu %8lu %3lu %3lu\n",
		total_alloc - s->alloc_fastpath, s->मुक्त_slowpath,
		(total_alloc - s->alloc_fastpath) * 100 / total_alloc,
		total_मुक्त ? s->मुक्त_slowpath * 100 / total_मुक्त : 0);
	म_लिखो("Page Alloc           %8lu %8lu %3lu %3lu\n",
		s->alloc_slab, s->मुक्त_slab,
		s->alloc_slab * 100 / total_alloc,
		total_मुक्त ? s->मुक्त_slab * 100 / total_मुक्त : 0);
	म_लिखो("Add partial          %8lu %8lu %3lu %3lu\n",
		s->deactivate_to_head + s->deactivate_to_tail,
		s->मुक्त_add_partial,
		(s->deactivate_to_head + s->deactivate_to_tail) * 100 / total_alloc,
		total_मुक्त ? s->मुक्त_add_partial * 100 / total_मुक्त : 0);
	म_लिखो("Remove partial       %8lu %8lu %3lu %3lu\n",
		s->alloc_from_partial, s->मुक्त_हटाओ_partial,
		s->alloc_from_partial * 100 / total_alloc,
		total_मुक्त ? s->मुक्त_हटाओ_partial * 100 / total_मुक्त : 0);

	म_लिखो("Cpu partial list     %8lu %8lu %3lu %3lu\n",
		s->cpu_partial_alloc, s->cpu_partial_मुक्त,
		s->cpu_partial_alloc * 100 / total_alloc,
		total_मुक्त ? s->cpu_partial_मुक्त * 100 / total_मुक्त : 0);

	म_लिखो("RemoteObj/SlabFrozen %8lu %8lu %3lu %3lu\n",
		s->deactivate_remote_मुक्तs, s->मुक्त_frozen,
		s->deactivate_remote_मुक्तs * 100 / total_alloc,
		total_मुक्त ? s->मुक्त_frozen * 100 / total_मुक्त : 0);

	म_लिखो("Total                %8lu %8lu\n\n", total_alloc, total_मुक्त);

	अगर (s->cpuslab_flush)
		म_लिखो("Flushes %8lu\n", s->cpuslab_flush);

	total = s->deactivate_full + s->deactivate_empty +
			s->deactivate_to_head + s->deactivate_to_tail + s->deactivate_bypass;

	अगर (total) अणु
		म_लिखो("\nSlab Deactivation             Occurrences %%\n");
		म_लिखो("-------------------------------------------------\n");
		म_लिखो("Slab full                     %7lu  %3lu%%\n",
			s->deactivate_full, (s->deactivate_full * 100) / total);
		म_लिखो("Slab empty                    %7lu  %3lu%%\n",
			s->deactivate_empty, (s->deactivate_empty * 100) / total);
		म_लिखो("Moved to head of partial list %7lu  %3lu%%\n",
			s->deactivate_to_head, (s->deactivate_to_head * 100) / total);
		म_लिखो("Moved to tail of partial list %7lu  %3lu%%\n",
			s->deactivate_to_tail, (s->deactivate_to_tail * 100) / total);
		म_लिखो("Deactivation bypass           %7lu  %3lu%%\n",
			s->deactivate_bypass, (s->deactivate_bypass * 100) / total);
		म_लिखो("Refilled from foreign frees   %7lu  %3lu%%\n",
			s->alloc_refill, (s->alloc_refill * 100) / total);
		म_लिखो("Node mismatch                 %7lu  %3lu%%\n",
			s->alloc_node_mismatch, (s->alloc_node_mismatch * 100) / total);
	पूर्ण

	अगर (s->cmpxchg_द्विगुन_fail || s->cmpxchg_द्विगुन_cpu_fail) अणु
		म_लिखो("\nCmpxchg_double Looping\n------------------------\n");
		म_लिखो("Locked Cmpxchg Double redos   %lu\nUnlocked Cmpxchg Double redos %lu\n",
			s->cmpxchg_द्विगुन_fail, s->cmpxchg_द्विगुन_cpu_fail);
	पूर्ण
पूर्ण

अटल व्योम report(काष्ठा slabinfo *s)
अणु
	अगर (म_भेद(s->name, "*") == 0)
		वापस;

	म_लिखो("\nSlabcache: %-15s  Aliases: %2d Order : %2d Objects: %lu\n",
		s->name, s->aliases, s->order, s->objects);
	अगर (s->hwcache_align)
		म_लिखो("** Hardware cacheline aligned\n");
	अगर (s->cache_dma)
		म_लिखो("** Memory is allocated in a special DMA zone\n");
	अगर (s->destroy_by_rcu)
		म_लिखो("** Slabs are destroyed via RCU\n");
	अगर (s->reclaim_account)
		म_लिखो("** Reclaim accounting active\n");

	म_लिखो("\nSizes (bytes)     Slabs              Debug                Memory\n");
	म_लिखो("------------------------------------------------------------------------\n");
	म_लिखो("Object : %7d  Total  : %7ld   Sanity Checks : %s  Total: %7ld\n",
			s->object_size, s->sद_असल, onoff(s->sanity_checks),
			s->sद_असल * (page_size << s->order));
	म_लिखो("SlabObj: %7d  Full   : %7ld   Redzoning     : %s  Used : %7ld\n",
			s->slab_size, s->sद_असल - s->partial - s->cpu_sद_असल,
			onoff(s->red_zone), s->objects * s->object_size);
	म_लिखो("SlabSiz: %7d  Partial: %7ld   Poisoning     : %s  Loss : %7ld\n",
			page_size << s->order, s->partial, onoff(s->poison),
			s->sद_असल * (page_size << s->order) - s->objects * s->object_size);
	म_लिखो("Loss   : %7d  CpuSlab: %7d   Tracking      : %s  Lalig: %7ld\n",
			s->slab_size - s->object_size, s->cpu_sद_असल, onoff(s->store_user),
			(s->slab_size - s->object_size) * s->objects);
	म_लिखो("Align  : %7d  Objects: %7d   Tracing       : %s  Lpadd: %7ld\n",
			s->align, s->objs_per_slab, onoff(s->trace),
			((page_size << s->order) - s->objs_per_slab * s->slab_size) *
			s->sद_असल);

	ops(s);
	show_tracking(s);
	slab_numa(s, 1);
	slab_stats(s);
पूर्ण

अटल व्योम slabcache(काष्ठा slabinfo *s)
अणु
	अक्षर size_str[20];
	अक्षर dist_str[40];
	अक्षर flags[20];
	अक्षर *p = flags;

	अगर (म_भेद(s->name, "*") == 0)
		वापस;

	अगर (unreclaim_only && s->reclaim_account)
		वापस;

	अगर (actual_sद_असल == 1) अणु
		report(s);
		वापस;
	पूर्ण

	अगर (skip_zero && !show_empty && !s->sद_असल)
		वापस;

	अगर (show_empty && s->sद_असल)
		वापस;

	अगर (sort_loss == 0)
		store_size(size_str, slab_size(s));
	अन्यथा
		store_size(size_str, slab_waste(s));
	snम_लिखो(dist_str, 40, "%lu/%lu/%d", s->sद_असल - s->cpu_sद_असल,
						s->partial, s->cpu_sद_असल);

	अगर (!line++)
		first_line();

	अगर (s->aliases)
		*p++ = '*';
	अगर (s->cache_dma)
		*p++ = 'd';
	अगर (s->hwcache_align)
		*p++ = 'A';
	अगर (s->poison)
		*p++ = 'P';
	अगर (s->reclaim_account)
		*p++ = 'a';
	अगर (s->red_zone)
		*p++ = 'Z';
	अगर (s->sanity_checks)
		*p++ = 'F';
	अगर (s->store_user)
		*p++ = 'U';
	अगर (s->trace)
		*p++ = 'T';

	*p = 0;
	अगर (show_activity) अणु
		अचिन्हित दीर्घ total_alloc;
		अचिन्हित दीर्घ total_मुक्त;

		total_alloc = s->alloc_fastpath + s->alloc_slowpath;
		total_मुक्त = s->मुक्त_fastpath + s->मुक्त_slowpath;

		म_लिखो("%-21s %8ld %10ld %10ld %3ld %3ld %5ld %1d %4ld %4ld\n",
			s->name, s->objects,
			total_alloc, total_मुक्त,
			total_alloc ? (s->alloc_fastpath * 100 / total_alloc) : 0,
			total_मुक्त ? (s->मुक्त_fastpath * 100 / total_मुक्त) : 0,
			s->order_fallback, s->order, s->cmpxchg_द्विगुन_fail,
			s->cmpxchg_द्विगुन_cpu_fail);
	पूर्ण अन्यथा अणु
		म_लिखो("%-21s %8ld %7d %15s %14s %4d %1d %3ld %3ld %s\n",
			s->name, s->objects, s->object_size, size_str, dist_str,
			s->objs_per_slab, s->order,
			s->sद_असल ? (s->partial * 100) / s->sद_असल : 100,
			s->sद_असल ? (s->objects * s->object_size * 100) /
				(s->sद_असल * (page_size << s->order)) : 100,
			flags);
	पूर्ण
पूर्ण

/*
 * Analyze debug options. Return false अगर something is amiss.
 */
अटल पूर्णांक debug_opt_scan(अक्षर *opt)
अणु
	अगर (!opt || !opt[0] || म_भेद(opt, "-") == 0)
		वापस 1;

	अगर (strहालcmp(opt, "a") == 0) अणु
		sanity = 1;
		poison = 1;
		redzone = 1;
		tracking = 1;
		वापस 1;
	पूर्ण

	क्रम ( ; *opt; opt++)
		चयन (*opt) अणु
		हाल 'F' : case 'f':
			अगर (sanity)
				वापस 0;
			sanity = 1;
			अवरोध;
		हाल 'P' : case 'p':
			अगर (poison)
				वापस 0;
			poison = 1;
			अवरोध;

		हाल 'Z' : case 'z':
			अगर (redzone)
				वापस 0;
			redzone = 1;
			अवरोध;

		हाल 'U' : case 'u':
			अगर (tracking)
				वापस 0;
			tracking = 1;
			अवरोध;

		हाल 'T' : case 't':
			अगर (tracing)
				वापस 0;
			tracing = 1;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक slab_empty(काष्ठा slabinfo *s)
अणु
	अगर (s->objects > 0)
		वापस 0;

	/*
	 * We may still have sद_असल even अगर there are no objects. Shrinking will
	 * हटाओ them.
	 */
	अगर (s->sद_असल != 0)
		set_obj(s, "shrink", 1);

	वापस 1;
पूर्ण

अटल व्योम slab_debug(काष्ठा slabinfo *s)
अणु
	अगर (म_भेद(s->name, "*") == 0)
		वापस;

	अगर (sanity && !s->sanity_checks) अणु
		set_obj(s, "sanity_checks", 1);
	पूर्ण
	अगर (!sanity && s->sanity_checks) अणु
		अगर (slab_empty(s))
			set_obj(s, "sanity_checks", 0);
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "%s not empty cannot disable sanity checks\n", s->name);
	पूर्ण
	अगर (redzone && !s->red_zone) अणु
		अगर (slab_empty(s))
			set_obj(s, "red_zone", 1);
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "%s not empty cannot enable redzoning\n", s->name);
	पूर्ण
	अगर (!redzone && s->red_zone) अणु
		अगर (slab_empty(s))
			set_obj(s, "red_zone", 0);
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "%s not empty cannot disable redzoning\n", s->name);
	पूर्ण
	अगर (poison && !s->poison) अणु
		अगर (slab_empty(s))
			set_obj(s, "poison", 1);
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "%s not empty cannot enable poisoning\n", s->name);
	पूर्ण
	अगर (!poison && s->poison) अणु
		अगर (slab_empty(s))
			set_obj(s, "poison", 0);
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "%s not empty cannot disable poisoning\n", s->name);
	पूर्ण
	अगर (tracking && !s->store_user) अणु
		अगर (slab_empty(s))
			set_obj(s, "store_user", 1);
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "%s not empty cannot enable tracking\n", s->name);
	पूर्ण
	अगर (!tracking && s->store_user) अणु
		अगर (slab_empty(s))
			set_obj(s, "store_user", 0);
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "%s not empty cannot disable tracking\n", s->name);
	पूर्ण
	अगर (tracing && !s->trace) अणु
		अगर (sद_असल == 1)
			set_obj(s, "trace", 1);
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "%s can only enable trace for one slab at a time\n", s->name);
	पूर्ण
	अगर (!tracing && s->trace)
		set_obj(s, "trace", 1);
पूर्ण

अटल व्योम totals(व्योम)
अणु
	काष्ठा slabinfo *s;

	पूर्णांक used_sद_असल = 0;
	अक्षर b1[20], b2[20], b3[20], b4[20];
	अचिन्हित दीर्घ दीर्घ max = 1ULL << 63;

	/* Object size */
	अचिन्हित दीर्घ दीर्घ min_objsize = max, max_objsize = 0, avg_objsize;

	/* Number of partial sद_असल in a slabcache */
	अचिन्हित दीर्घ दीर्घ min_partial = max, max_partial = 0,
				avg_partial, total_partial = 0;

	/* Number of sद_असल in a slab cache */
	अचिन्हित दीर्घ दीर्घ min_sद_असल = max, max_sद_असल = 0,
				avg_sद_असल, total_sद_असल = 0;

	/* Size of the whole slab */
	अचिन्हित दीर्घ दीर्घ min_size = max, max_size = 0,
				avg_size, total_size = 0;

	/* Bytes used क्रम object storage in a slab */
	अचिन्हित दीर्घ दीर्घ min_used = max, max_used = 0,
				avg_used, total_used = 0;

	/* Waste: Bytes used क्रम alignment and padding */
	अचिन्हित दीर्घ दीर्घ min_waste = max, max_waste = 0,
				avg_waste, total_waste = 0;
	/* Number of objects in a slab */
	अचिन्हित दीर्घ दीर्घ min_objects = max, max_objects = 0,
				avg_objects, total_objects = 0;
	/* Waste per object */
	अचिन्हित दीर्घ दीर्घ min_objwaste = max,
				max_objwaste = 0, avg_objwaste,
				total_objwaste = 0;

	/* Memory per object */
	अचिन्हित दीर्घ दीर्घ min_memobj = max,
				max_memobj = 0, avg_memobj,
				total_objsize = 0;

	/* Percentage of partial sद_असल per slab */
	अचिन्हित दीर्घ min_ppart = 100, max_ppart = 0,
				avg_ppart, total_ppart = 0;

	/* Number of objects in partial sद_असल */
	अचिन्हित दीर्घ min_partobj = max, max_partobj = 0,
				avg_partobj, total_partobj = 0;

	/* Percentage of partial objects of all objects in a slab */
	अचिन्हित दीर्घ min_ppartobj = 100, max_ppartobj = 0,
				avg_ppartobj, total_ppartobj = 0;


	क्रम (s = slabinfo; s < slabinfo + sद_असल; s++) अणु
		अचिन्हित दीर्घ दीर्घ size;
		अचिन्हित दीर्घ used;
		अचिन्हित दीर्घ दीर्घ wasted;
		अचिन्हित दीर्घ दीर्घ objwaste;
		अचिन्हित दीर्घ percentage_partial_sद_असल;
		अचिन्हित दीर्घ percentage_partial_objs;

		अगर (!s->sद_असल || !s->objects)
			जारी;

		used_sद_असल++;

		size = slab_size(s);
		used = s->objects * s->object_size;
		wasted = size - used;
		objwaste = s->slab_size - s->object_size;

		percentage_partial_sद_असल = s->partial * 100 / s->sद_असल;
		अगर (percentage_partial_sद_असल > 100)
			percentage_partial_sद_असल = 100;

		percentage_partial_objs = s->objects_partial * 100
							/ s->objects;

		अगर (percentage_partial_objs > 100)
			percentage_partial_objs = 100;

		अगर (s->object_size < min_objsize)
			min_objsize = s->object_size;
		अगर (s->partial < min_partial)
			min_partial = s->partial;
		अगर (s->sद_असल < min_sद_असल)
			min_sद_असल = s->sद_असल;
		अगर (size < min_size)
			min_size = size;
		अगर (wasted < min_waste)
			min_waste = wasted;
		अगर (objwaste < min_objwaste)
			min_objwaste = objwaste;
		अगर (s->objects < min_objects)
			min_objects = s->objects;
		अगर (used < min_used)
			min_used = used;
		अगर (s->objects_partial < min_partobj)
			min_partobj = s->objects_partial;
		अगर (percentage_partial_sद_असल < min_ppart)
			min_ppart = percentage_partial_sद_असल;
		अगर (percentage_partial_objs < min_ppartobj)
			min_ppartobj = percentage_partial_objs;
		अगर (s->slab_size < min_memobj)
			min_memobj = s->slab_size;

		अगर (s->object_size > max_objsize)
			max_objsize = s->object_size;
		अगर (s->partial > max_partial)
			max_partial = s->partial;
		अगर (s->sद_असल > max_sद_असल)
			max_sद_असल = s->sद_असल;
		अगर (size > max_size)
			max_size = size;
		अगर (wasted > max_waste)
			max_waste = wasted;
		अगर (objwaste > max_objwaste)
			max_objwaste = objwaste;
		अगर (s->objects > max_objects)
			max_objects = s->objects;
		अगर (used > max_used)
			max_used = used;
		अगर (s->objects_partial > max_partobj)
			max_partobj = s->objects_partial;
		अगर (percentage_partial_sद_असल > max_ppart)
			max_ppart = percentage_partial_sद_असल;
		अगर (percentage_partial_objs > max_ppartobj)
			max_ppartobj = percentage_partial_objs;
		अगर (s->slab_size > max_memobj)
			max_memobj = s->slab_size;

		total_partial += s->partial;
		total_sद_असल += s->sद_असल;
		total_size += size;
		total_waste += wasted;

		total_objects += s->objects;
		total_used += used;
		total_partobj += s->objects_partial;
		total_ppart += percentage_partial_sद_असल;
		total_ppartobj += percentage_partial_objs;

		total_objwaste += s->objects * objwaste;
		total_objsize += s->objects * s->slab_size;
	पूर्ण

	अगर (!total_objects) अणु
		म_लिखो("No objects\n");
		वापस;
	पूर्ण
	अगर (!used_sद_असल) अणु
		म_लिखो("No slabs\n");
		वापस;
	पूर्ण

	/* Per slab averages */
	avg_partial = total_partial / used_sद_असल;
	avg_sद_असल = total_sद_असल / used_sद_असल;
	avg_size = total_size / used_sद_असल;
	avg_waste = total_waste / used_sद_असल;

	avg_objects = total_objects / used_sद_असल;
	avg_used = total_used / used_sद_असल;
	avg_partobj = total_partobj / used_sद_असल;
	avg_ppart = total_ppart / used_sद_असल;
	avg_ppartobj = total_ppartobj / used_sद_असल;

	/* Per object object sizes */
	avg_objsize = total_used / total_objects;
	avg_objwaste = total_objwaste / total_objects;
	avg_partobj = total_partobj * 100 / total_objects;
	avg_memobj = total_objsize / total_objects;

	म_लिखो("Slabcache Totals\n");
	म_लिखो("----------------\n");
	म_लिखो("Slabcaches : %15d   Aliases  : %11d->%-3d  Active:    %3d\n",
			sद_असल, aliases, alias_tarमाला_लो, used_sद_असल);

	store_size(b1, total_size);store_size(b2, total_waste);
	store_size(b3, total_waste * 100 / total_used);
	म_लिखो("Memory used: %15s   # Loss   : %15s   MRatio:%6s%%\n", b1, b2, b3);

	store_size(b1, total_objects);store_size(b2, total_partobj);
	store_size(b3, total_partobj * 100 / total_objects);
	म_लिखो("# Objects  : %15s   # PartObj: %15s   ORatio:%6s%%\n", b1, b2, b3);

	म_लिखो("\n");
	म_लिखो("Per Cache         Average              "
		"Min              Max            Total\n");
	म_लिखो("---------------------------------------"
		"-------------------------------------\n");

	store_size(b1, avg_objects);store_size(b2, min_objects);
	store_size(b3, max_objects);store_size(b4, total_objects);
	म_लिखो("#Objects  %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	store_size(b1, avg_sद_असल);store_size(b2, min_sद_असल);
	store_size(b3, max_sद_असल);store_size(b4, total_sद_असल);
	म_लिखो("#Slabs    %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	store_size(b1, avg_partial);store_size(b2, min_partial);
	store_size(b3, max_partial);store_size(b4, total_partial);
	म_लिखो("#PartSlab %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);
	store_size(b1, avg_ppart);store_size(b2, min_ppart);
	store_size(b3, max_ppart);
	store_size(b4, total_partial * 100  / total_sद_असल);
	म_लिखो("%%PartSlab%15s%% %15s%% %15s%% %15s%%\n",
			b1,	b2,	b3,	b4);

	store_size(b1, avg_partobj);store_size(b2, min_partobj);
	store_size(b3, max_partobj);
	store_size(b4, total_partobj);
	म_लिखो("PartObjs  %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	store_size(b1, avg_ppartobj);store_size(b2, min_ppartobj);
	store_size(b3, max_ppartobj);
	store_size(b4, total_partobj * 100 / total_objects);
	म_लिखो("%% PartObj%15s%% %15s%% %15s%% %15s%%\n",
			b1,	b2,	b3,	b4);

	store_size(b1, avg_size);store_size(b2, min_size);
	store_size(b3, max_size);store_size(b4, total_size);
	म_लिखो("Memory    %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	store_size(b1, avg_used);store_size(b2, min_used);
	store_size(b3, max_used);store_size(b4, total_used);
	म_लिखो("Used      %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	store_size(b1, avg_waste);store_size(b2, min_waste);
	store_size(b3, max_waste);store_size(b4, total_waste);
	म_लिखो("Loss      %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	म_लिखो("\n");
	म_लिखो("Per Object        Average              "
		"Min              Max\n");
	म_लिखो("---------------------------------------"
		"--------------------\n");

	store_size(b1, avg_memobj);store_size(b2, min_memobj);
	store_size(b3, max_memobj);
	म_लिखो("Memory    %15s  %15s  %15s\n",
			b1,	b2,	b3);
	store_size(b1, avg_objsize);store_size(b2, min_objsize);
	store_size(b3, max_objsize);
	म_लिखो("User      %15s  %15s  %15s\n",
			b1,	b2,	b3);

	store_size(b1, avg_objwaste);store_size(b2, min_objwaste);
	store_size(b3, max_objwaste);
	म_लिखो("Loss      %15s  %15s  %15s\n",
			b1,	b2,	b3);
पूर्ण

अटल व्योम sort_sद_असल(व्योम)
अणु
	काष्ठा slabinfo *s1,*s2;

	क्रम (s1 = slabinfo; s1 < slabinfo + sद_असल; s1++) अणु
		क्रम (s2 = s1 + 1; s2 < slabinfo + sद_असल; s2++) अणु
			पूर्णांक result;

			अगर (sort_size)
				result = slab_size(s1) < slab_size(s2);
			अन्यथा अगर (sort_active)
				result = slab_activity(s1) < slab_activity(s2);
			अन्यथा अगर (sort_loss)
				result = slab_waste(s1) < slab_waste(s2);
			अन्यथा अगर (sort_partial)
				result = s1->partial < s2->partial;
			अन्यथा
				result = strहालcmp(s1->name, s2->name);

			अगर (show_inverted)
				result = -result;

			अगर (result > 0) अणु
				काष्ठा slabinfo t;

				स_नकल(&t, s1, माप(काष्ठा slabinfo));
				स_नकल(s1, s2, माप(काष्ठा slabinfo));
				स_नकल(s2, &t, माप(काष्ठा slabinfo));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sort_aliases(व्योम)
अणु
	काष्ठा aliasinfo *a1,*a2;

	क्रम (a1 = aliasinfo; a1 < aliasinfo + aliases; a1++) अणु
		क्रम (a2 = a1 + 1; a2 < aliasinfo + aliases; a2++) अणु
			अक्षर *n1, *n2;

			n1 = a1->name;
			n2 = a2->name;
			अगर (show_alias && !show_inverted) अणु
				n1 = a1->ref;
				n2 = a2->ref;
			पूर्ण
			अगर (strहालcmp(n1, n2) > 0) अणु
				काष्ठा aliasinfo t;

				स_नकल(&t, a1, माप(काष्ठा aliasinfo));
				स_नकल(a1, a2, माप(काष्ठा aliasinfo));
				स_नकल(a2, &t, माप(काष्ठा aliasinfo));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम link_sद_असल(व्योम)
अणु
	काष्ठा aliasinfo *a;
	काष्ठा slabinfo *s;

	क्रम (a = aliasinfo; a < aliasinfo + aliases; a++) अणु

		क्रम (s = slabinfo; s < slabinfo + sद_असल; s++)
			अगर (म_भेद(a->ref, s->name) == 0) अणु
				a->slab = s;
				s->refs++;
				अवरोध;
			पूर्ण
		अगर (s == slabinfo + sद_असल)
			fatal("Unresolved alias %s\n", a->ref);
	पूर्ण
पूर्ण

अटल व्योम alias(व्योम)
अणु
	काष्ठा aliasinfo *a;
	अक्षर *active = शून्य;

	sort_aliases();
	link_sद_असल();

	क्रम(a = aliasinfo; a < aliasinfo + aliases; a++) अणु

		अगर (!show_single_ref && a->slab->refs == 1)
			जारी;

		अगर (!show_inverted) अणु
			अगर (active) अणु
				अगर (म_भेद(a->slab->name, active) == 0) अणु
					म_लिखो(" %s", a->name);
					जारी;
				पूर्ण
			पूर्ण
			म_लिखो("\n%-12s <- %s", a->slab->name, a->name);
			active = a->slab->name;
		पूर्ण
		अन्यथा
			म_लिखो("%-15s -> %s\n", a->name, a->slab->name);
	पूर्ण
	अगर (active)
		म_लिखो("\n");
पूर्ण


अटल व्योम नाम_sद_असल(व्योम)
अणु
	काष्ठा slabinfo *s;
	काष्ठा aliasinfo *a;

	क्रम (s = slabinfo; s < slabinfo + sद_असल; s++) अणु
		अगर (*s->name != ':')
			जारी;

		अगर (s->refs > 1 && !show_first_alias)
			जारी;

		a = find_one_alias(s);

		अगर (a)
			s->name = a->name;
		अन्यथा अणु
			s->name = "*";
			actual_sद_असल--;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक slab_mismatch(अक्षर *slab)
अणु
	वापस regexec(&pattern, slab, 0, शून्य, 0);
पूर्ण

अटल व्योम पढ़ो_slab_dir(व्योम)
अणु
	सूची *dir;
	काष्ठा dirent *de;
	काष्ठा slabinfo *slab = slabinfo;
	काष्ठा aliasinfo *alias = aliasinfo;
	अक्षर *p;
	अक्षर *t;
	पूर्णांक count;

	अगर (स_बदलो("/sys/kernel/slab") && स_बदलो("/sys/slab"))
		fatal("SYSFS support for SLUB not active\n");

	dir = सूची_खोलो(".");
	जबतक ((de = सूची_पढ़ो(dir))) अणु
		अगर (de->d_name[0] == '.' ||
			(de->d_name[0] != ':' && slab_mismatch(de->d_name)))
				जारी;
		चयन (de->d_type) अणु
		   हाल DT_LNK:
			alias->name = strdup(de->d_name);
			count = पढ़ोlink(de->d_name, buffer, माप(buffer)-1);

			अगर (count < 0)
				fatal("Cannot read symlink %s\n", de->d_name);

			buffer[count] = 0;
			p = buffer + count;
			जबतक (p > buffer && p[-1] != '/')
				p--;
			alias->ref = strdup(p);
			alias++;
			अवरोध;
		   हाल DT_सूची:
			अगर (स_बदलो(de->d_name))
				fatal("Unable to access slab %s\n", slab->name);
			slab->name = strdup(de->d_name);
			slab->alias = 0;
			slab->refs = 0;
			slab->aliases = get_obj("aliases");
			slab->align = get_obj("align");
			slab->cache_dma = get_obj("cache_dma");
			slab->cpu_sद_असल = get_obj("cpu_slabs");
			slab->destroy_by_rcu = get_obj("destroy_by_rcu");
			slab->hwcache_align = get_obj("hwcache_align");
			slab->object_size = get_obj("object_size");
			slab->objects = get_obj("objects");
			slab->objects_partial = get_obj("objects_partial");
			slab->objects_total = get_obj("objects_total");
			slab->objs_per_slab = get_obj("objs_per_slab");
			slab->order = get_obj("order");
			slab->partial = get_obj("partial");
			slab->partial = get_obj_and_str("partial", &t);
			decode_numa_list(slab->numa_partial, t);
			मुक्त(t);
			slab->poison = get_obj("poison");
			slab->reclaim_account = get_obj("reclaim_account");
			slab->red_zone = get_obj("red_zone");
			slab->sanity_checks = get_obj("sanity_checks");
			slab->slab_size = get_obj("slab_size");
			slab->sद_असल = get_obj_and_str("slabs", &t);
			decode_numa_list(slab->numa, t);
			मुक्त(t);
			slab->store_user = get_obj("store_user");
			slab->trace = get_obj("trace");
			slab->alloc_fastpath = get_obj("alloc_fastpath");
			slab->alloc_slowpath = get_obj("alloc_slowpath");
			slab->मुक्त_fastpath = get_obj("free_fastpath");
			slab->मुक्त_slowpath = get_obj("free_slowpath");
			slab->मुक्त_frozen= get_obj("free_frozen");
			slab->मुक्त_add_partial = get_obj("free_add_partial");
			slab->मुक्त_हटाओ_partial = get_obj("free_remove_partial");
			slab->alloc_from_partial = get_obj("alloc_from_partial");
			slab->alloc_slab = get_obj("alloc_slab");
			slab->alloc_refill = get_obj("alloc_refill");
			slab->मुक्त_slab = get_obj("free_slab");
			slab->cpuslab_flush = get_obj("cpuslab_flush");
			slab->deactivate_full = get_obj("deactivate_full");
			slab->deactivate_empty = get_obj("deactivate_empty");
			slab->deactivate_to_head = get_obj("deactivate_to_head");
			slab->deactivate_to_tail = get_obj("deactivate_to_tail");
			slab->deactivate_remote_मुक्तs = get_obj("deactivate_remote_frees");
			slab->order_fallback = get_obj("order_fallback");
			slab->cmpxchg_द्विगुन_cpu_fail = get_obj("cmpxchg_double_cpu_fail");
			slab->cmpxchg_द्विगुन_fail = get_obj("cmpxchg_double_fail");
			slab->cpu_partial_alloc = get_obj("cpu_partial_alloc");
			slab->cpu_partial_मुक्त = get_obj("cpu_partial_free");
			slab->alloc_node_mismatch = get_obj("alloc_node_mismatch");
			slab->deactivate_bypass = get_obj("deactivate_bypass");
			स_बदलो("..");
			अगर (slab->name[0] == ':')
				alias_tarमाला_लो++;
			slab++;
			अवरोध;
		   शेष :
			fatal("Unknown file type %lx\n", de->d_type);
		पूर्ण
	पूर्ण
	बंद_सूची(dir);
	sद_असल = slab - slabinfo;
	actual_sद_असल = sद_असल;
	aliases = alias - aliasinfo;
	अगर (sद_असल > MAX_SLABS)
		fatal("Too many slabs\n");
	अगर (aliases > MAX_ALIASES)
		fatal("Too many aliases\n");
पूर्ण

अटल व्योम output_sद_असल(व्योम)
अणु
	काष्ठा slabinfo *slab;
	पूर्णांक lines = output_lines;

	क्रम (slab = slabinfo; (slab < slabinfo + sद_असल) &&
			lines != 0; slab++) अणु

		अगर (slab->alias)
			जारी;

		अगर (lines != -1)
			lines--;

		अगर (show_numa)
			slab_numa(slab, 0);
		अन्यथा अगर (show_track)
			show_tracking(slab);
		अन्यथा अगर (validate)
			slab_validate(slab);
		अन्यथा अगर (shrink)
			slab_shrink(slab);
		अन्यथा अगर (set_debug)
			slab_debug(slab);
		अन्यथा अगर (show_ops)
			ops(slab);
		अन्यथा अगर (show_slab)
			slabcache(slab);
		अन्यथा अगर (show_report)
			report(slab);
	पूर्ण
पूर्ण

अटल व्योम _xtotals(अक्षर *heading, अक्षर *underline,
		     पूर्णांक loss, पूर्णांक size, पूर्णांक partial)
अणु
	म_लिखो("%s%s", heading, underline);
	line = 0;
	sort_loss = loss;
	sort_size = size;
	sort_partial = partial;
	sort_sद_असल();
	output_sद_असल();
पूर्ण

अटल व्योम xtotals(व्योम)
अणु
	अक्षर *heading, *underline;

	totals();

	link_sद_असल();
	नाम_sद_असल();

	heading = "\nSlabs sorted by size\n";
	underline = "--------------------\n";
	_xtotals(heading, underline, 0, 1, 0);

	heading = "\nSlabs sorted by loss\n";
	underline = "--------------------\n";
	_xtotals(heading, underline, 1, 0, 0);

	heading = "\nSlabs sorted by number of partial slabs\n";
	underline = "---------------------------------------\n";
	_xtotals(heading, underline, 0, 0, 1);

	म_लिखो("\n");
पूर्ण

काष्ठा option opts[] = अणु
	अणु "aliases", no_argument, शून्य, 'a' पूर्ण,
	अणु "activity", no_argument, शून्य, 'A' पूर्ण,
	अणु "Bytes", no_argument, शून्य, 'B'पूर्ण,
	अणु "debug", optional_argument, शून्य, 'd' पूर्ण,
	अणु "display-activity", no_argument, शून्य, 'D' पूर्ण,
	अणु "empty", no_argument, शून्य, 'e' पूर्ण,
	अणु "first-alias", no_argument, शून्य, 'f' पूर्ण,
	अणु "help", no_argument, शून्य, 'h' पूर्ण,
	अणु "inverted", no_argument, शून्य, 'i'पूर्ण,
	अणु "slabs", no_argument, शून्य, 'l' पूर्ण,
	अणु "Loss", no_argument, शून्य, 'L'पूर्ण,
	अणु "numa", no_argument, शून्य, 'n' पूर्ण,
	अणु "lines", required_argument, शून्य, 'N'पूर्ण,
	अणु "ops", no_argument, शून्य, 'o' पूर्ण,
	अणु "partial", no_argument, शून्य, 'p'पूर्ण,
	अणु "report", no_argument, शून्य, 'r' पूर्ण,
	अणु "shrink", no_argument, शून्य, 's' पूर्ण,
	अणु "Size", no_argument, शून्य, 'S'पूर्ण,
	अणु "tracking", no_argument, शून्य, 't'पूर्ण,
	अणु "Totals", no_argument, शून्य, 'T'पूर्ण,
	अणु "Unreclaim", no_argument, शून्य, 'U'पूर्ण,
	अणु "validate", no_argument, शून्य, 'v' पूर्ण,
	अणु "Xtotals", no_argument, शून्य, 'X'पूर्ण,
	अणु "zero", no_argument, शून्य, 'z' पूर्ण,
	अणु "1ref", no_argument, शून्य, '1'पूर्ण,
	अणु शून्य, 0, शून्य, 0 पूर्ण
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक c;
	पूर्णांक err;
	अक्षर *pattern_source;

	page_size = getpagesize();

	जबतक ((c = getopt_दीर्घ(argc, argv, "aABd::DefhilLnN:oPrsStTUvXz1",
						opts, शून्य)) != -1)
		चयन (c) अणु
		हाल 'a':
			show_alias = 1;
			अवरोध;
		हाल 'A':
			sort_active = 1;
			अवरोध;
		हाल 'B':
			show_bytes = 1;
			अवरोध;
		हाल 'd':
			set_debug = 1;
			अगर (!debug_opt_scan(optarg))
				fatal("Invalid debug option '%s'\n", optarg);
			अवरोध;
		हाल 'D':
			show_activity = 1;
			अवरोध;
		हाल 'e':
			show_empty = 1;
			अवरोध;
		हाल 'f':
			show_first_alias = 1;
			अवरोध;
		हाल 'h':
			usage();
			वापस 0;
		हाल 'i':
			show_inverted = 1;
			अवरोध;
		हाल 'l':
			show_slab = 1;
			अवरोध;
		हाल 'L':
			sort_loss = 1;
			अवरोध;
		हाल 'n':
			show_numa = 1;
			अवरोध;
		हाल 'N':
			अगर (optarg) अणु
				output_lines = म_से_प(optarg);
				अगर (output_lines < 1)
					output_lines = 1;
			पूर्ण
			अवरोध;
		हाल 'o':
			show_ops = 1;
			अवरोध;
		हाल 'r':
			show_report = 1;
			अवरोध;
		हाल 'P':
			sort_partial = 1;
			अवरोध;
		हाल 's':
			shrink = 1;
			अवरोध;
		हाल 'S':
			sort_size = 1;
			अवरोध;
		हाल 't':
			show_track = 1;
			अवरोध;
		हाल 'T':
			show_totals = 1;
			अवरोध;
		हाल 'U':
			unreclaim_only = 1;
			अवरोध;
		हाल 'v':
			validate = 1;
			अवरोध;
		हाल 'X':
			अगर (output_lines == -1)
				output_lines = 1;
			extended_totals = 1;
			show_bytes = 1;
			अवरोध;
		हाल 'z':
			skip_zero = 0;
			अवरोध;
		हाल '1':
			show_single_ref = 1;
			अवरोध;
		शेष:
			fatal("%s: Invalid option '%c'\n", argv[0], optopt);

	पूर्ण

	अगर (!show_slab && !show_alias && !show_track && !show_report
		&& !validate && !shrink && !set_debug && !show_ops)
			show_slab = 1;

	अगर (argc > optind)
		pattern_source = argv[optind];
	अन्यथा
		pattern_source = ".*";

	err = regcomp(&pattern, pattern_source, REG_ICASE|REG_NOSUB);
	अगर (err)
		fatal("%s: Invalid pattern '%s' code %d\n",
			argv[0], pattern_source, err);
	पढ़ो_slab_dir();
	अगर (show_alias) अणु
		alias();
	पूर्ण अन्यथा अगर (extended_totals) अणु
		xtotals();
	पूर्ण अन्यथा अगर (show_totals) अणु
		totals();
	पूर्ण अन्यथा अणु
		link_sद_असल();
		नाम_sद_असल();
		sort_sद_असल();
		output_sद_असल();
	पूर्ण
	वापस 0;
पूर्ण
