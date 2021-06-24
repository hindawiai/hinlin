<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic show_mem() implementation
 *
 * Copyright (C) 2008 Johannes Weiner <hannes@saeurebad.de>
 */

#समावेश <linux/mm.h>
#समावेश <linux/cma.h>

व्योम show_mem(अचिन्हित पूर्णांक filter, nodemask_t *nodemask)
अणु
	pg_data_t *pgdat;
	अचिन्हित दीर्घ total = 0, reserved = 0, highmem = 0;

	prपूर्णांकk("Mem-Info:\n");
	show_मुक्त_areas(filter, nodemask);

	क्रम_each_online_pgdat(pgdat) अणु
		पूर्णांक zoneid;

		क्रम (zoneid = 0; zoneid < MAX_NR_ZONES; zoneid++) अणु
			काष्ठा zone *zone = &pgdat->node_zones[zoneid];
			अगर (!populated_zone(zone))
				जारी;

			total += zone->present_pages;
			reserved += zone->present_pages - zone_managed_pages(zone);

			अगर (is_highmem_idx(zoneid))
				highmem += zone->present_pages;
		पूर्ण
	पूर्ण

	prपूर्णांकk("%lu pages RAM\n", total);
	prपूर्णांकk("%lu pages HighMem/MovableOnly\n", highmem);
	prपूर्णांकk("%lu pages reserved\n", reserved);
#अगर_घोषित CONFIG_CMA
	prपूर्णांकk("%lu pages cma reserved\n", totalcma_pages);
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_FAILURE
	prपूर्णांकk("%lu pages hwpoisoned\n", atomic_दीर्घ_पढ़ो(&num_poisoned_pages));
#पूर्ण_अगर
पूर्ण
