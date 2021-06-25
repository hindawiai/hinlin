<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm_init.c - Memory initialisation verअगरication and debugging
 *
 * Copyright 2008 IBM Corporation, 2008
 * Author Mel Gorman <mel@csn.ul.ie>
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/kobject.h>
#समावेश <linux/export.h>
#समावेश <linux/memory.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/sched.h>
#समावेश <linux/mman.h>
#समावेश "internal.h"

#अगर_घोषित CONFIG_DEBUG_MEMORY_INIT
पूर्णांक __meminitdata mminit_loglevel;

/* The zonelists are simply reported, validation is manual. */
व्योम __init mminit_verअगरy_zonelist(व्योम)
अणु
	पूर्णांक nid;

	अगर (mminit_loglevel < MMINIT_VERIFY)
		वापस;

	क्रम_each_online_node(nid) अणु
		pg_data_t *pgdat = NODE_DATA(nid);
		काष्ठा zone *zone;
		काष्ठा zoneref *z;
		काष्ठा zonelist *zonelist;
		पूर्णांक i, listid, zoneid;

		BUILD_BUG_ON(MAX_ZONELISTS > 2);
		क्रम (i = 0; i < MAX_ZONELISTS * MAX_NR_ZONES; i++) अणु

			/* Identअगरy the zone and nodelist */
			zoneid = i % MAX_NR_ZONES;
			listid = i / MAX_NR_ZONES;
			zonelist = &pgdat->node_zonelists[listid];
			zone = &pgdat->node_zones[zoneid];
			अगर (!populated_zone(zone))
				जारी;

			/* Prपूर्णांक inक्रमmation about the zonelist */
			prपूर्णांकk(KERN_DEBUG "mminit::zonelist %s %d:%s = ",
				listid > 0 ? "thisnode" : "general", nid,
				zone->name);

			/* Iterate the zonelist */
			क्रम_each_zone_zonelist(zone, z, zonelist, zoneid)
				pr_cont("%d:%s ", zone_to_nid(zone), zone->name);
			pr_cont("\n");
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init mminit_verअगरy_pageflags_layout(व्योम)
अणु
	पूर्णांक shअगरt, width;
	अचिन्हित दीर्घ or_mask, add_mask;

	shअगरt = 8 * माप(अचिन्हित दीर्घ);
	width = shअगरt - SECTIONS_WIDTH - NODES_WIDTH - ZONES_WIDTH
		- LAST_CPUPID_SHIFT - KASAN_TAG_WIDTH;
	mminit_dprपूर्णांकk(MMINIT_TRACE, "pageflags_layout_widths",
		"Section %d Node %d Zone %d Lastcpupid %d Kasantag %d Flags %d\n",
		SECTIONS_WIDTH,
		NODES_WIDTH,
		ZONES_WIDTH,
		LAST_CPUPID_WIDTH,
		KASAN_TAG_WIDTH,
		NR_PAGEFLAGS);
	mminit_dprपूर्णांकk(MMINIT_TRACE, "pageflags_layout_shifts",
		"Section %d Node %d Zone %d Lastcpupid %d Kasantag %d\n",
		SECTIONS_SHIFT,
		NODES_SHIFT,
		ZONES_SHIFT,
		LAST_CPUPID_SHIFT,
		KASAN_TAG_WIDTH);
	mminit_dprपूर्णांकk(MMINIT_TRACE, "pageflags_layout_pgshifts",
		"Section %lu Node %lu Zone %lu Lastcpupid %lu Kasantag %lu\n",
		(अचिन्हित दीर्घ)SECTIONS_PGSHIFT,
		(अचिन्हित दीर्घ)NODES_PGSHIFT,
		(अचिन्हित दीर्घ)ZONES_PGSHIFT,
		(अचिन्हित दीर्घ)LAST_CPUPID_PGSHIFT,
		(अचिन्हित दीर्घ)KASAN_TAG_PGSHIFT);
	mminit_dprपूर्णांकk(MMINIT_TRACE, "pageflags_layout_nodezoneid",
		"Node/Zone ID: %lu -> %lu\n",
		(अचिन्हित दीर्घ)(ZONEID_PGOFF + ZONEID_SHIFT),
		(अचिन्हित दीर्घ)ZONEID_PGOFF);
	mminit_dprपूर्णांकk(MMINIT_TRACE, "pageflags_layout_usage",
		"location: %d -> %d layout %d -> %d unused %d -> %d page-flags\n",
		shअगरt, width, width, NR_PAGEFLAGS, NR_PAGEFLAGS, 0);
#अगर_घोषित NODE_NOT_IN_PAGE_FLAGS
	mminit_dprपूर्णांकk(MMINIT_TRACE, "pageflags_layout_nodeflags",
		"Node not in page flags");
#पूर्ण_अगर
#अगर_घोषित LAST_CPUPID_NOT_IN_PAGE_FLAGS
	mminit_dprपूर्णांकk(MMINIT_TRACE, "pageflags_layout_nodeflags",
		"Last cpupid not in page flags");
#पूर्ण_अगर

	अगर (SECTIONS_WIDTH) अणु
		shअगरt -= SECTIONS_WIDTH;
		BUG_ON(shअगरt != SECTIONS_PGSHIFT);
	पूर्ण
	अगर (NODES_WIDTH) अणु
		shअगरt -= NODES_WIDTH;
		BUG_ON(shअगरt != NODES_PGSHIFT);
	पूर्ण
	अगर (ZONES_WIDTH) अणु
		shअगरt -= ZONES_WIDTH;
		BUG_ON(shअगरt != ZONES_PGSHIFT);
	पूर्ण

	/* Check क्रम biपंचांगask overlaps */
	or_mask = (ZONES_MASK << ZONES_PGSHIFT) |
			(NODES_MASK << NODES_PGSHIFT) |
			(SECTIONS_MASK << SECTIONS_PGSHIFT);
	add_mask = (ZONES_MASK << ZONES_PGSHIFT) +
			(NODES_MASK << NODES_PGSHIFT) +
			(SECTIONS_MASK << SECTIONS_PGSHIFT);
	BUG_ON(or_mask != add_mask);
पूर्ण

अटल __init पूर्णांक set_mminit_loglevel(अक्षर *str)
अणु
	get_option(&str, &mminit_loglevel);
	वापस 0;
पूर्ण
early_param("mminit_loglevel", set_mminit_loglevel);
#पूर्ण_अगर /* CONFIG_DEBUG_MEMORY_INIT */

काष्ठा kobject *mm_kobj;
EXPORT_SYMBOL_GPL(mm_kobj);

#अगर_घोषित CONFIG_SMP
s32 vm_committed_as_batch = 32;

व्योम mm_compute_batch(पूर्णांक overcommit_policy)
अणु
	u64 memsized_batch;
	s32 nr = num_present_cpus();
	s32 batch = max_t(s32, nr*2, 32);
	अचिन्हित दीर्घ ram_pages = totalram_pages();

	/*
	 * For policy OVERCOMMIT_NEVER, set batch size to 0.4% of
	 * (total memory/#cpus), and lअगरt it to 25% क्रम other policies
	 * to easy the possible lock contention क्रम percpu_counter
	 * vm_committed_as, जबतक the max limit is पूर्णांक_उच्च
	 */
	अगर (overcommit_policy == OVERCOMMIT_NEVER)
		memsized_batch = min_t(u64, ram_pages/nr/256, पूर्णांक_उच्च);
	अन्यथा
		memsized_batch = min_t(u64, ram_pages/nr/4, पूर्णांक_उच्च);

	vm_committed_as_batch = max_t(s32, memsized_batch, batch);
पूर्ण

अटल पूर्णांक __meminit mm_compute_batch_notअगरier(काष्ठा notअगरier_block *self,
					अचिन्हित दीर्घ action, व्योम *arg)
अणु
	चयन (action) अणु
	हाल MEM_ONLINE:
	हाल MEM_OFFLINE:
		mm_compute_batch(sysctl_overcommit_memory);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block compute_batch_nb __meminitdata = अणु
	.notअगरier_call = mm_compute_batch_notअगरier,
	.priority = IPC_CALLBACK_PRI, /* use lowest priority */
पूर्ण;

अटल पूर्णांक __init mm_compute_batch_init(व्योम)
अणु
	mm_compute_batch(sysctl_overcommit_memory);
	रेजिस्टर_hoपंचांगemory_notअगरier(&compute_batch_nb);

	वापस 0;
पूर्ण

__initcall(mm_compute_batch_init);

#पूर्ण_अगर

अटल पूर्णांक __init mm_sysfs_init(व्योम)
अणु
	mm_kobj = kobject_create_and_add("mm", kernel_kobj);
	अगर (!mm_kobj)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
postcore_initcall(mm_sysfs_init);
