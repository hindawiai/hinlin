<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat. All rights reserved.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_CACHE_POLICY_INTERNAL_H
#घोषणा DM_CACHE_POLICY_INTERNAL_H

#समावेश <linux/vदो_स्मृति.h>
#समावेश "dm-cache-policy.h"

/*----------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक policy_lookup(काष्ठा dm_cache_policy *p, dm_oblock_t oblock, dm_cblock_t *cblock,
				पूर्णांक data_dir, bool fast_copy, bool *background_queued)
अणु
	वापस p->lookup(p, oblock, cblock, data_dir, fast_copy, background_queued);
पूर्ण

अटल अंतरभूत पूर्णांक policy_lookup_with_work(काष्ठा dm_cache_policy *p,
					  dm_oblock_t oblock, dm_cblock_t *cblock,
					  पूर्णांक data_dir, bool fast_copy,
					  काष्ठा policy_work **work)
अणु
	अगर (!p->lookup_with_work) अणु
		*work = शून्य;
		वापस p->lookup(p, oblock, cblock, data_dir, fast_copy, शून्य);
	पूर्ण

	वापस p->lookup_with_work(p, oblock, cblock, data_dir, fast_copy, work);
पूर्ण

अटल अंतरभूत पूर्णांक policy_get_background_work(काष्ठा dm_cache_policy *p,
					     bool idle, काष्ठा policy_work **result)
अणु
	वापस p->get_background_work(p, idle, result);
पूर्ण

अटल अंतरभूत व्योम policy_complete_background_work(काष्ठा dm_cache_policy *p,
						   काष्ठा policy_work *work,
						   bool success)
अणु
	वापस p->complete_background_work(p, work, success);
पूर्ण

अटल अंतरभूत व्योम policy_set_dirty(काष्ठा dm_cache_policy *p, dm_cblock_t cblock)
अणु
	p->set_dirty(p, cblock);
पूर्ण

अटल अंतरभूत व्योम policy_clear_dirty(काष्ठा dm_cache_policy *p, dm_cblock_t cblock)
अणु
	p->clear_dirty(p, cblock);
पूर्ण

अटल अंतरभूत पूर्णांक policy_load_mapping(काष्ठा dm_cache_policy *p,
				      dm_oblock_t oblock, dm_cblock_t cblock,
				      bool dirty, uपूर्णांक32_t hपूर्णांक, bool hपूर्णांक_valid)
अणु
	वापस p->load_mapping(p, oblock, cblock, dirty, hपूर्णांक, hपूर्णांक_valid);
पूर्ण

अटल अंतरभूत पूर्णांक policy_invalidate_mapping(काष्ठा dm_cache_policy *p,
					    dm_cblock_t cblock)
अणु
	वापस p->invalidate_mapping(p, cblock);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t policy_get_hपूर्णांक(काष्ठा dm_cache_policy *p,
				       dm_cblock_t cblock)
अणु
	वापस p->get_hपूर्णांक ? p->get_hपूर्णांक(p, cblock) : 0;
पूर्ण

अटल अंतरभूत dm_cblock_t policy_residency(काष्ठा dm_cache_policy *p)
अणु
	वापस p->residency(p);
पूर्ण

अटल अंतरभूत व्योम policy_tick(काष्ठा dm_cache_policy *p, bool can_block)
अणु
	अगर (p->tick)
		वापस p->tick(p, can_block);
पूर्ण

अटल अंतरभूत पूर्णांक policy_emit_config_values(काष्ठा dm_cache_policy *p, अक्षर *result,
					    अचिन्हित maxlen, sमाप_प्रकार *sz_ptr)
अणु
	sमाप_प्रकार sz = *sz_ptr;
	अगर (p->emit_config_values)
		वापस p->emit_config_values(p, result, maxlen, sz_ptr);

	DMEMIT("0 ");
	*sz_ptr = sz;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक policy_set_config_value(काष्ठा dm_cache_policy *p,
					  स्थिर अक्षर *key, स्थिर अक्षर *value)
अणु
	वापस p->set_config_value ? p->set_config_value(p, key, value) : -EINVAL;
पूर्ण

अटल अंतरभूत व्योम policy_allow_migrations(काष्ठा dm_cache_policy *p, bool allow)
अणु
	वापस p->allow_migrations(p, allow);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Some utility functions commonly used by policies and the core target.
 */
अटल अंतरभूत माप_प्रकार bitset_size_in_bytes(अचिन्हित nr_entries)
अणु
	वापस माप(अचिन्हित दीर्घ) * dm_भाग_up(nr_entries, BITS_PER_LONG);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *alloc_bitset(अचिन्हित nr_entries)
अणु
	माप_प्रकार s = bitset_size_in_bytes(nr_entries);
	वापस vzalloc(s);
पूर्ण

अटल अंतरभूत व्योम clear_bitset(व्योम *bitset, अचिन्हित nr_entries)
अणु
	माप_प्रकार s = bitset_size_in_bytes(nr_entries);
	स_रखो(bitset, 0, s);
पूर्ण

अटल अंतरभूत व्योम मुक्त_bitset(अचिन्हित दीर्घ *bits)
अणु
	vमुक्त(bits);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Creates a new cache policy given a policy name, a cache size, an origin size and the block size.
 */
काष्ठा dm_cache_policy *dm_cache_policy_create(स्थिर अक्षर *name, dm_cblock_t cache_size,
					       sector_t origin_size, sector_t block_size);

/*
 * Destroys the policy.  This drops references to the policy module as well
 * as calling it's destroy method.  So always use this rather than calling
 * the policy->destroy method directly.
 */
व्योम dm_cache_policy_destroy(काष्ठा dm_cache_policy *p);

/*
 * In हाल we've क्रमgotten.
 */
स्थिर अक्षर *dm_cache_policy_get_name(काष्ठा dm_cache_policy *p);

स्थिर अचिन्हित *dm_cache_policy_get_version(काष्ठा dm_cache_policy *p);

माप_प्रकार dm_cache_policy_get_hपूर्णांक_size(काष्ठा dm_cache_policy *p);

/*----------------------------------------------------------------*/

#पूर्ण_अगर /* DM_CACHE_POLICY_INTERNAL_H */
