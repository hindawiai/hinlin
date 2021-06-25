<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sched-करोमुख्यs (multiprocessor balancing) flag declarations.
 */

#अगर_अघोषित SD_FLAG
# error "Incorrect import of SD flags definitions"
#पूर्ण_अगर

/*
 * Hierarchical metaflags
 *
 * SHARED_CHILD: These flags are meant to be set from the base करोमुख्य upwards.
 * If a करोमुख्य has this flag set, all of its children should have it set. This
 * is usually because the flag describes some shared resource (all CPUs in that
 * करोमुख्य share the same resource), or because they are tied to a scheduling
 * behaviour that we want to disable at some poपूर्णांक in the hierarchy क्रम
 * scalability reasons.
 *
 * In those हालs it करोesn't make sense to have the flag set क्रम a करोमुख्य but
 * not have it in (some of) its children: sched करोमुख्यs ALWAYS span their child
 * करोमुख्यs, so operations करोne with parent करोमुख्यs will cover CPUs in the lower
 * child करोमुख्यs.
 *
 *
 * SHARED_PARENT: These flags are meant to be set from the highest करोमुख्य
 * करोwnwards. If a करोमुख्य has this flag set, all of its parents should have it
 * set. This is usually क्रम topology properties that start to appear above a
 * certain level (e.g. करोमुख्य starts spanning CPUs outside of the base CPU's
 * socket).
 */
#घोषणा SDF_SHARED_CHILD       0x1
#घोषणा SDF_SHARED_PARENT      0x2

/*
 * Behavioural metaflags
 *
 * NEEDS_GROUPS: These flags are only relevant अगर the करोमुख्य they are set on has
 * more than one group. This is usually क्रम balancing flags (load balancing
 * involves equalizing a metric between groups), or क्रम flags describing some
 * shared resource (which would be shared between groups).
 */
#घोषणा SDF_NEEDS_GROUPS       0x4

/*
 * Balance when about to become idle
 *
 * SHARED_CHILD: Set from the base करोमुख्य up to cpuset.sched_relax_करोमुख्य_level.
 * NEEDS_GROUPS: Load balancing flag.
 */
SD_FLAG(SD_BALANCE_NEWIDLE, SDF_SHARED_CHILD | SDF_NEEDS_GROUPS)

/*
 * Balance on exec
 *
 * SHARED_CHILD: Set from the base करोमुख्य up to the NUMA reclaim level.
 * NEEDS_GROUPS: Load balancing flag.
 */
SD_FLAG(SD_BALANCE_EXEC, SDF_SHARED_CHILD | SDF_NEEDS_GROUPS)

/*
 * Balance on विभाजन, clone
 *
 * SHARED_CHILD: Set from the base करोमुख्य up to the NUMA reclaim level.
 * NEEDS_GROUPS: Load balancing flag.
 */
SD_FLAG(SD_BALANCE_FORK, SDF_SHARED_CHILD | SDF_NEEDS_GROUPS)

/*
 * Balance on wakeup
 *
 * SHARED_CHILD: Set from the base करोमुख्य up to cpuset.sched_relax_करोमुख्य_level.
 * NEEDS_GROUPS: Load balancing flag.
 */
SD_FLAG(SD_BALANCE_WAKE, SDF_SHARED_CHILD | SDF_NEEDS_GROUPS)

/*
 * Consider waking task on waking CPU.
 *
 * SHARED_CHILD: Set from the base करोमुख्य up to the NUMA reclaim level.
 */
SD_FLAG(SD_WAKE_AFFINE, SDF_SHARED_CHILD)

/*
 * Doमुख्य members have dअगरferent CPU capacities
 *
 * SHARED_PARENT: Set from the topmost करोमुख्य करोwn to the first करोमुख्य where
 *                asymmetry is detected.
 * NEEDS_GROUPS: Per-CPU capacity is asymmetric between groups.
 */
SD_FLAG(SD_ASYM_CPUCAPACITY, SDF_SHARED_PARENT | SDF_NEEDS_GROUPS)

/*
 * Doमुख्य members share CPU capacity (i.e. SMT)
 *
 * SHARED_CHILD: Set from the base करोमुख्य up until spanned CPUs no दीर्घer share
 *               CPU capacity.
 * NEEDS_GROUPS: Capacity is shared between groups.
 */
SD_FLAG(SD_SHARE_CPUCAPACITY, SDF_SHARED_CHILD | SDF_NEEDS_GROUPS)

/*
 * Doमुख्य members share CPU package resources (i.e. caches)
 *
 * SHARED_CHILD: Set from the base करोमुख्य up until spanned CPUs no दीर्घer share
 *               the same cache(s).
 * NEEDS_GROUPS: Caches are shared between groups.
 */
SD_FLAG(SD_SHARE_PKG_RESOURCES, SDF_SHARED_CHILD | SDF_NEEDS_GROUPS)

/*
 * Only a single load balancing instance
 *
 * SHARED_PARENT: Set क्रम all NUMA levels above NODE. Could be set from a
 *                dअगरferent level upwards, but it करोesn't change that अगर a
 *                करोमुख्य has this flag set, then all of its parents need to have
 *                it too (otherwise the serialization करोesn't make sense).
 * NEEDS_GROUPS: No poपूर्णांक in preserving करोमुख्य अगर it has a single group.
 */
SD_FLAG(SD_SERIALIZE, SDF_SHARED_PARENT | SDF_NEEDS_GROUPS)

/*
 * Place busy tasks earlier in the करोमुख्य
 *
 * SHARED_CHILD: Usually set on the SMT level. Technically could be set further
 *               up, but currently assumed to be set from the base करोमुख्य
 *               upwards (see update_top_cache_करोमुख्य()).
 * NEEDS_GROUPS: Load balancing flag.
 */
SD_FLAG(SD_ASYM_PACKING, SDF_SHARED_CHILD | SDF_NEEDS_GROUPS)

/*
 * Prefer to place tasks in a sibling करोमुख्य
 *
 * Set up until करोमुख्यs start spanning NUMA nodes. Close to being a SHARED_CHILD
 * flag, but cleared below करोमुख्यs with SD_ASYM_CPUCAPACITY.
 *
 * NEEDS_GROUPS: Load balancing flag.
 */
SD_FLAG(SD_PREFER_SIBLING, SDF_NEEDS_GROUPS)

/*
 * sched_groups of this level overlap
 *
 * SHARED_PARENT: Set क्रम all NUMA levels above NODE.
 * NEEDS_GROUPS: Overlaps can only exist with more than one group.
 */
SD_FLAG(SD_OVERLAP, SDF_SHARED_PARENT | SDF_NEEDS_GROUPS)

/*
 * Cross-node balancing
 *
 * SHARED_PARENT: Set क्रम all NUMA levels above NODE.
 * NEEDS_GROUPS: No poपूर्णांक in preserving करोमुख्य अगर it has a single group.
 */
SD_FLAG(SD_NUMA, SDF_SHARED_PARENT | SDF_NEEDS_GROUPS)
