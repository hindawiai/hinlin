<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/mm/mmzone.c
 *
 * management codes क्रम pgdats, zones and page flags
 */


#समावेश <linux/मानकघोष.स>
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>

काष्ठा pglist_data *first_online_pgdat(व्योम)
अणु
	वापस NODE_DATA(first_online_node);
पूर्ण

काष्ठा pglist_data *next_online_pgdat(काष्ठा pglist_data *pgdat)
अणु
	पूर्णांक nid = next_online_node(pgdat->node_id);

	अगर (nid == MAX_NUMNODES)
		वापस शून्य;
	वापस NODE_DATA(nid);
पूर्ण

/*
 * next_zone - helper magic क्रम क्रम_each_zone()
 */
काष्ठा zone *next_zone(काष्ठा zone *zone)
अणु
	pg_data_t *pgdat = zone->zone_pgdat;

	अगर (zone < pgdat->node_zones + MAX_NR_ZONES - 1)
		zone++;
	अन्यथा अणु
		pgdat = next_online_pgdat(pgdat);
		अगर (pgdat)
			zone = pgdat->node_zones;
		अन्यथा
			zone = शून्य;
	पूर्ण
	वापस zone;
पूर्ण

अटल अंतरभूत पूर्णांक zref_in_nodemask(काष्ठा zoneref *zref, nodemask_t *nodes)
अणु
#अगर_घोषित CONFIG_NUMA
	वापस node_isset(zonelist_node_idx(zref), *nodes);
#अन्यथा
	वापस 1;
#पूर्ण_अगर /* CONFIG_NUMA */
पूर्ण

/* Returns the next zone at or below highest_zoneidx in a zonelist */
काष्ठा zoneref *__next_zones_zonelist(काष्ठा zoneref *z,
					क्रमागत zone_type highest_zoneidx,
					nodemask_t *nodes)
अणु
	/*
	 * Find the next suitable zone to use क्रम the allocation.
	 * Only filter based on nodemask अगर it's set
	 */
	अगर (unlikely(nodes == शून्य))
		जबतक (zonelist_zone_idx(z) > highest_zoneidx)
			z++;
	अन्यथा
		जबतक (zonelist_zone_idx(z) > highest_zoneidx ||
				(z->zone && !zref_in_nodemask(z, nodes)))
			z++;

	वापस z;
पूर्ण

व्योम lruvec_init(काष्ठा lruvec *lruvec)
अणु
	क्रमागत lru_list lru;

	स_रखो(lruvec, 0, माप(काष्ठा lruvec));
	spin_lock_init(&lruvec->lru_lock);

	क्रम_each_lru(lru)
		INIT_LIST_HEAD(&lruvec->lists[lru]);
पूर्ण

#अगर defined(CONFIG_NUMA_BALANCING) && !defined(LAST_CPUPID_NOT_IN_PAGE_FLAGS)
पूर्णांक page_cpupid_xchg_last(काष्ठा page *page, पूर्णांक cpupid)
अणु
	अचिन्हित दीर्घ old_flags, flags;
	पूर्णांक last_cpupid;

	करो अणु
		old_flags = flags = page->flags;
		last_cpupid = page_cpupid_last(page);

		flags &= ~(LAST_CPUPID_MASK << LAST_CPUPID_PGSHIFT);
		flags |= (cpupid & LAST_CPUPID_MASK) << LAST_CPUPID_PGSHIFT;
	पूर्ण जबतक (unlikely(cmpxchg(&page->flags, old_flags, flags) != old_flags));

	वापस last_cpupid;
पूर्ण
#पूर्ण_अगर
