<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/highस्मृति.स>
#समावेश <linux/export.h>
#समावेश <linux/swap.h> /* क्रम totalram_pages */
#समावेश <linux/memblock.h>

व्योम __init set_highmem_pages_init(व्योम)
अणु
	काष्ठा zone *zone;
	पूर्णांक nid;

	/*
	 * Explicitly reset zone->managed_pages because set_highmem_pages_init()
	 * is invoked beक्रमe memblock_मुक्त_all()
	 */
	reset_all_zones_managed_pages();
	क्रम_each_zone(zone) अणु
		अचिन्हित दीर्घ zone_start_pfn, zone_end_pfn;

		अगर (!is_highmem(zone))
			जारी;

		zone_start_pfn = zone->zone_start_pfn;
		zone_end_pfn = zone_start_pfn + zone->spanned_pages;

		nid = zone_to_nid(zone);
		prपूर्णांकk(KERN_INFO "Initializing %s for node %d (%08lx:%08lx)\n",
				zone->name, nid, zone_start_pfn, zone_end_pfn);

		add_highpages_with_active_regions(nid, zone_start_pfn,
				 zone_end_pfn);
	पूर्ण
पूर्ण
