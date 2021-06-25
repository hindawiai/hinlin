<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Inject a hwpoison memory failure on a arbitrary pfn */
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/hugetlb.h>
#समावेश "internal.h"

अटल काष्ठा dentry *hwpoison_dir;

अटल पूर्णांक hwpoison_inject(व्योम *data, u64 val)
अणु
	अचिन्हित दीर्घ pfn = val;
	काष्ठा page *p;
	काष्ठा page *hpage;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!pfn_valid(pfn))
		वापस -ENXIO;

	p = pfn_to_page(pfn);
	hpage = compound_head(p);

	अगर (!hwpoison_filter_enable)
		जाओ inject;

	shake_page(hpage, 0);
	/*
	 * This implies unable to support non-LRU pages.
	 */
	अगर (!PageLRU(hpage) && !PageHuge(p))
		वापस 0;

	/*
	 * करो a racy check to make sure PG_hwpoison will only be set क्रम
	 * the targeted owner (or on a मुक्त page).
	 * memory_failure() will reकरो the check reliably inside page lock.
	 */
	err = hwpoison_filter(hpage);
	अगर (err)
		वापस 0;

inject:
	pr_info("Injecting memory failure at pfn %#lx\n", pfn);
	वापस memory_failure(pfn, 0);
पूर्ण

अटल पूर्णांक hwpoison_unpoison(व्योम *data, u64 val)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	वापस unpoison_memory(val);
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(hwpoison_fops, शून्य, hwpoison_inject, "%lli\n");
DEFINE_DEBUGFS_ATTRIBUTE(unpoison_fops, शून्य, hwpoison_unpoison, "%lli\n");

अटल व्योम pfn_inject_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(hwpoison_dir);
पूर्ण

अटल पूर्णांक pfn_inject_init(व्योम)
अणु
	hwpoison_dir = debugfs_create_dir("hwpoison", शून्य);

	/*
	 * Note that the below poison/unpoison पूर्णांकerfaces करो not involve
	 * hardware status change, hence करो not require hardware support.
	 * They are मुख्यly क्रम testing hwpoison in software level.
	 */
	debugfs_create_file("corrupt-pfn", 0200, hwpoison_dir, शून्य,
			    &hwpoison_fops);

	debugfs_create_file("unpoison-pfn", 0200, hwpoison_dir, शून्य,
			    &unpoison_fops);

	debugfs_create_u32("corrupt-filter-enable", 0600, hwpoison_dir,
			   &hwpoison_filter_enable);

	debugfs_create_u32("corrupt-filter-dev-major", 0600, hwpoison_dir,
			   &hwpoison_filter_dev_major);

	debugfs_create_u32("corrupt-filter-dev-minor", 0600, hwpoison_dir,
			   &hwpoison_filter_dev_minor);

	debugfs_create_u64("corrupt-filter-flags-mask", 0600, hwpoison_dir,
			   &hwpoison_filter_flags_mask);

	debugfs_create_u64("corrupt-filter-flags-value", 0600, hwpoison_dir,
			   &hwpoison_filter_flags_value);

#अगर_घोषित CONFIG_MEMCG
	debugfs_create_u64("corrupt-filter-memcg", 0600, hwpoison_dir,
			   &hwpoison_filter_memcg);
#पूर्ण_अगर

	वापस 0;
पूर्ण

module_init(pfn_inject_init);
module_निकास(pfn_inject_निकास);
MODULE_LICENSE("GPL");
