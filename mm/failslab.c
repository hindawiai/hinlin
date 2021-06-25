<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fault-inject.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश "slab.h"

अटल काष्ठा अणु
	काष्ठा fault_attr attr;
	bool ignore_gfp_reclaim;
	bool cache_filter;
पूर्ण failslab = अणु
	.attr = FAULT_ATTR_INITIALIZER,
	.ignore_gfp_reclaim = true,
	.cache_filter = false,
पूर्ण;

bool __should_failslab(काष्ठा kmem_cache *s, gfp_t gfpflags)
अणु
	/* No fault-injection क्रम bootstrap cache */
	अगर (unlikely(s == kmem_cache))
		वापस false;

	अगर (gfpflags & __GFP_NOFAIL)
		वापस false;

	अगर (failslab.ignore_gfp_reclaim &&
			(gfpflags & __GFP_सूचीECT_RECLAIM))
		वापस false;

	अगर (failslab.cache_filter && !(s->flags & SLAB_FAILSLAB))
		वापस false;

	वापस should_fail(&failslab.attr, s->object_size);
पूर्ण

अटल पूर्णांक __init setup_failslab(अक्षर *str)
अणु
	वापस setup_fault_attr(&failslab.attr, str);
पूर्ण
__setup("failslab=", setup_failslab);

#अगर_घोषित CONFIG_FAULT_INJECTION_DEBUG_FS
अटल पूर्णांक __init failslab_debugfs_init(व्योम)
अणु
	काष्ठा dentry *dir;
	umode_t mode = S_IFREG | 0600;

	dir = fault_create_debugfs_attr("failslab", शून्य, &failslab.attr);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	debugfs_create_bool("ignore-gfp-wait", mode, dir,
			    &failslab.ignore_gfp_reclaim);
	debugfs_create_bool("cache-filter", mode, dir,
			    &failslab.cache_filter);

	वापस 0;
पूर्ण

late_initcall(failslab_debugfs_init);

#पूर्ण_अगर /* CONFIG_FAULT_INJECTION_DEBUG_FS */
