<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Handle caching attributes in page tables (PAT)
 *
 * Authors: Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 *          Suresh B Siddha <suresh.b.siddha@पूर्णांकel.com>
 *
 * Interval tree used to store the PAT memory type reservations.
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerval_tree_generic.h>
#समावेश <linux/sched.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/memtype.h>

#समावेश "memtype.h"

/*
 * The memtype tree keeps track of memory type क्रम specअगरic
 * physical memory areas. Without proper tracking, conflicting memory
 * types in dअगरferent mappings can cause CPU cache corruption.
 *
 * The tree is an पूर्णांकerval tree (augmented rbtree) which tree is ordered
 * by the starting address. The tree can contain multiple entries क्रम
 * dअगरferent regions which overlap. All the aliases have the same
 * cache attributes of course, as enक्रमced by the PAT logic.
 *
 * memtype_lock protects the rbtree.
 */

अटल अंतरभूत u64 पूर्णांकerval_start(काष्ठा memtype *entry)
अणु
	वापस entry->start;
पूर्ण

अटल अंतरभूत u64 पूर्णांकerval_end(काष्ठा memtype *entry)
अणु
	वापस entry->end - 1;
पूर्ण

INTERVAL_TREE_DEFINE(काष्ठा memtype, rb, u64, subtree_max_end,
		     पूर्णांकerval_start, पूर्णांकerval_end,
		     अटल, पूर्णांकerval)

अटल काष्ठा rb_root_cached memtype_rbroot = RB_ROOT_CACHED;

क्रमागत अणु
	MEMTYPE_EXACT_MATCH	= 0,
	MEMTYPE_END_MATCH	= 1
पूर्ण;

अटल काष्ठा memtype *memtype_match(u64 start, u64 end, पूर्णांक match_type)
अणु
	काष्ठा memtype *entry_match;

	entry_match = पूर्णांकerval_iter_first(&memtype_rbroot, start, end-1);

	जबतक (entry_match != शून्य && entry_match->start < end) अणु
		अगर ((match_type == MEMTYPE_EXACT_MATCH) &&
		    (entry_match->start == start) && (entry_match->end == end))
			वापस entry_match;

		अगर ((match_type == MEMTYPE_END_MATCH) &&
		    (entry_match->start < start) && (entry_match->end == end))
			वापस entry_match;

		entry_match = पूर्णांकerval_iter_next(entry_match, start, end-1);
	पूर्ण

	वापस शून्य; /* Returns शून्य अगर there is no match */
पूर्ण

अटल पूर्णांक memtype_check_conflict(u64 start, u64 end,
				  क्रमागत page_cache_mode reqtype,
				  क्रमागत page_cache_mode *newtype)
अणु
	काष्ठा memtype *entry_match;
	क्रमागत page_cache_mode found_type = reqtype;

	entry_match = पूर्णांकerval_iter_first(&memtype_rbroot, start, end-1);
	अगर (entry_match == शून्य)
		जाओ success;

	अगर (entry_match->type != found_type && newtype == शून्य)
		जाओ failure;

	dprपूर्णांकk("Overlap at 0x%Lx-0x%Lx\n", entry_match->start, entry_match->end);
	found_type = entry_match->type;

	entry_match = पूर्णांकerval_iter_next(entry_match, start, end-1);
	जबतक (entry_match) अणु
		अगर (entry_match->type != found_type)
			जाओ failure;

		entry_match = पूर्णांकerval_iter_next(entry_match, start, end-1);
	पूर्ण
success:
	अगर (newtype)
		*newtype = found_type;

	वापस 0;

failure:
	pr_info("x86/PAT: %s:%d conflicting memory types %Lx-%Lx %s<->%s\n",
		current->comm, current->pid, start, end,
		cattr_name(found_type), cattr_name(entry_match->type));

	वापस -EBUSY;
पूर्ण

पूर्णांक memtype_check_insert(काष्ठा memtype *entry_new, क्रमागत page_cache_mode *ret_type)
अणु
	पूर्णांक err = 0;

	err = memtype_check_conflict(entry_new->start, entry_new->end, entry_new->type, ret_type);
	अगर (err)
		वापस err;

	अगर (ret_type)
		entry_new->type = *ret_type;

	पूर्णांकerval_insert(entry_new, &memtype_rbroot);
	वापस 0;
पूर्ण

काष्ठा memtype *memtype_erase(u64 start, u64 end)
अणु
	काष्ठा memtype *entry_old;

	/*
	 * Since the memtype_rbroot tree allows overlapping ranges,
	 * memtype_erase() checks with EXACT_MATCH first, i.e. मुक्त
	 * a whole node क्रम the munmap हाल.  If no such entry is found,
	 * it then checks with END_MATCH, i.e. shrink the size of a node
	 * from the end क्रम the mremap हाल.
	 */
	entry_old = memtype_match(start, end, MEMTYPE_EXACT_MATCH);
	अगर (!entry_old) अणु
		entry_old = memtype_match(start, end, MEMTYPE_END_MATCH);
		अगर (!entry_old)
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (entry_old->start == start) अणु
		/* munmap: erase this node */
		पूर्णांकerval_हटाओ(entry_old, &memtype_rbroot);
	पूर्ण अन्यथा अणु
		/* mremap: update the end value of this node */
		पूर्णांकerval_हटाओ(entry_old, &memtype_rbroot);
		entry_old->end = start;
		पूर्णांकerval_insert(entry_old, &memtype_rbroot);

		वापस शून्य;
	पूर्ण

	वापस entry_old;
पूर्ण

काष्ठा memtype *memtype_lookup(u64 addr)
अणु
	वापस पूर्णांकerval_iter_first(&memtype_rbroot, addr, addr + PAGE_SIZE-1);
पूर्ण

/*
 * Debugging helper, copy the Nth entry of the tree पूर्णांकo a
 * a copy क्रम prपूर्णांकout. This allows us to prपूर्णांक out the tree
 * via debugfs, without holding the memtype_lock too दीर्घ:
 */
#अगर_घोषित CONFIG_DEBUG_FS
पूर्णांक memtype_copy_nth_element(काष्ठा memtype *entry_out, loff_t pos)
अणु
	काष्ठा memtype *entry_match;
	पूर्णांक i = 1;

	entry_match = पूर्णांकerval_iter_first(&memtype_rbroot, 0, अच_दीर्घ_उच्च);

	जबतक (entry_match && pos != i) अणु
		entry_match = पूर्णांकerval_iter_next(entry_match, 0, अच_दीर्घ_उच्च);
		i++;
	पूर्ण

	अगर (entry_match) अणु /* pos == i */
		*entry_out = *entry_match;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस 1;
	पूर्ण
पूर्ण
#पूर्ण_अगर
