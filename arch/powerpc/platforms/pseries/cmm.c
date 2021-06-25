<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Collaborative memory management पूर्णांकerface.
 *
 * Copyright (C) 2008 IBM Corporation
 * Author(s): Brian King (brking@linux.vnet.ibm.com),
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/oom.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/swap.h>
#समावेश <linux/device.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/magic.h>
#समावेश <linux/balloon_compaction.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/mmu.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/memory.h>
#समावेश <यंत्र/plpar_wrappers.h>

#समावेश "pseries.h"

#घोषणा CMM_DRIVER_VERSION	"1.0.0"
#घोषणा CMM_DEFAULT_DELAY	1
#घोषणा CMM_HOTPLUG_DELAY	5
#घोषणा CMM_DEBUG			0
#घोषणा CMM_DISABLE		0
#घोषणा CMM_OOM_KB		1024
#घोषणा CMM_MIN_MEM_MB		256
#घोषणा KB2PAGES(_p)		((_p)>>(PAGE_SHIFT-10))
#घोषणा PAGES2KB(_p)		((_p)<<(PAGE_SHIFT-10))

#घोषणा CMM_MEM_HOTPLUG_PRI	1

अटल अचिन्हित पूर्णांक delay = CMM_DEFAULT_DELAY;
अटल अचिन्हित पूर्णांक hotplug_delay = CMM_HOTPLUG_DELAY;
अटल अचिन्हित पूर्णांक oom_kb = CMM_OOM_KB;
अटल अचिन्हित पूर्णांक cmm_debug = CMM_DEBUG;
अटल अचिन्हित पूर्णांक cmm_disabled = CMM_DISABLE;
अटल अचिन्हित दीर्घ min_mem_mb = CMM_MIN_MEM_MB;
अटल bool __पढ़ो_mostly simulate;
अटल अचिन्हित दीर्घ simulate_loan_target_kb;
अटल काष्ठा device cmm_dev;

MODULE_AUTHOR("Brian King <brking@linux.vnet.ibm.com>");
MODULE_DESCRIPTION("IBM System p Collaborative Memory Manager");
MODULE_LICENSE("GPL");
MODULE_VERSION(CMM_DRIVER_VERSION);

module_param_named(delay, delay, uपूर्णांक, 0644);
MODULE_PARM_DESC(delay, "Delay (in seconds) between polls to query hypervisor paging requests. "
		 "[Default=" __stringअगरy(CMM_DEFAULT_DELAY) "]");
module_param_named(hotplug_delay, hotplug_delay, uपूर्णांक, 0644);
MODULE_PARM_DESC(hotplug_delay, "Delay (in seconds) after memory hotplug remove "
		 "before loaning resumes. "
		 "[Default=" __stringअगरy(CMM_HOTPLUG_DELAY) "]");
module_param_named(oom_kb, oom_kb, uपूर्णांक, 0644);
MODULE_PARM_DESC(oom_kb, "Amount of memory in kb to free on OOM. "
		 "[Default=" __stringअगरy(CMM_OOM_KB) "]");
module_param_named(min_mem_mb, min_mem_mb, uदीर्घ, 0644);
MODULE_PARM_DESC(min_mem_mb, "Minimum amount of memory (in MB) to not balloon. "
		 "[Default=" __stringअगरy(CMM_MIN_MEM_MB) "]");
module_param_named(debug, cmm_debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Enable module debugging logging. Set to 1 to enable. "
		 "[Default=" __stringअगरy(CMM_DEBUG) "]");
module_param_named(simulate, simulate, bool, 0444);
MODULE_PARM_DESC(simulate, "Enable simulation mode (no communication with hw).");

#घोषणा cmm_dbg(...) अगर (cmm_debug) अणु prपूर्णांकk(KERN_INFO "cmm: "__VA_ARGS__); पूर्ण

अटल atomic_दीर्घ_t loaned_pages;
अटल अचिन्हित दीर्घ loaned_pages_target;
अटल अचिन्हित दीर्घ oom_मुक्तd_pages;

अटल DEFINE_MUTEX(hotplug_mutex);
अटल पूर्णांक hotplug_occurred; /* रक्षित by the hotplug mutex */

अटल काष्ठा task_काष्ठा *cmm_thपढ़ो_ptr;
अटल काष्ठा balloon_dev_info b_dev_info;

अटल दीर्घ plpar_page_set_loaned(काष्ठा page *page)
अणु
	स्थिर अचिन्हित दीर्घ vpa = page_to_phys(page);
	अचिन्हित दीर्घ cmo_page_sz = cmo_get_page_size();
	दीर्घ rc = 0;
	पूर्णांक i;

	अगर (unlikely(simulate))
		वापस 0;

	क्रम (i = 0; !rc && i < PAGE_SIZE; i += cmo_page_sz)
		rc = plpar_hcall_norets(H_PAGE_INIT, H_PAGE_SET_LOANED, vpa + i, 0);

	क्रम (i -= cmo_page_sz; rc && i != 0; i -= cmo_page_sz)
		plpar_hcall_norets(H_PAGE_INIT, H_PAGE_SET_ACTIVE,
				   vpa + i - cmo_page_sz, 0);

	वापस rc;
पूर्ण

अटल दीर्घ plpar_page_set_active(काष्ठा page *page)
अणु
	स्थिर अचिन्हित दीर्घ vpa = page_to_phys(page);
	अचिन्हित दीर्घ cmo_page_sz = cmo_get_page_size();
	दीर्घ rc = 0;
	पूर्णांक i;

	अगर (unlikely(simulate))
		वापस 0;

	क्रम (i = 0; !rc && i < PAGE_SIZE; i += cmo_page_sz)
		rc = plpar_hcall_norets(H_PAGE_INIT, H_PAGE_SET_ACTIVE, vpa + i, 0);

	क्रम (i -= cmo_page_sz; rc && i != 0; i -= cmo_page_sz)
		plpar_hcall_norets(H_PAGE_INIT, H_PAGE_SET_LOANED,
				   vpa + i - cmo_page_sz, 0);

	वापस rc;
पूर्ण

/**
 * cmm_alloc_pages - Allocate pages and mark them as loaned
 * @nr:	number of pages to allocate
 *
 * Return value:
 * 	number of pages requested to be allocated which were not
 **/
अटल दीर्घ cmm_alloc_pages(दीर्घ nr)
अणु
	काष्ठा page *page;
	दीर्घ rc;

	cmm_dbg("Begin request for %ld pages\n", nr);

	जबतक (nr) अणु
		/* Exit अगर a hotplug operation is in progress or occurred */
		अगर (mutex_trylock(&hotplug_mutex)) अणु
			अगर (hotplug_occurred) अणु
				mutex_unlock(&hotplug_mutex);
				अवरोध;
			पूर्ण
			mutex_unlock(&hotplug_mutex);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण

		page = balloon_page_alloc();
		अगर (!page)
			अवरोध;
		rc = plpar_page_set_loaned(page);
		अगर (rc) अणु
			pr_err("%s: Can not set page to loaned. rc=%ld\n", __func__, rc);
			__मुक्त_page(page);
			अवरोध;
		पूर्ण

		balloon_page_enqueue(&b_dev_info, page);
		atomic_दीर्घ_inc(&loaned_pages);
		adjust_managed_page_count(page, -1);
		nr--;
	पूर्ण

	cmm_dbg("End request with %ld pages unfulfilled\n", nr);
	वापस nr;
पूर्ण

/**
 * cmm_मुक्त_pages - Free pages and mark them as active
 * @nr:	number of pages to मुक्त
 *
 * Return value:
 * 	number of pages requested to be मुक्तd which were not
 **/
अटल दीर्घ cmm_मुक्त_pages(दीर्घ nr)
अणु
	काष्ठा page *page;

	cmm_dbg("Begin free of %ld pages.\n", nr);
	जबतक (nr) अणु
		page = balloon_page_dequeue(&b_dev_info);
		अगर (!page)
			अवरोध;
		plpar_page_set_active(page);
		adjust_managed_page_count(page, 1);
		__मुक्त_page(page);
		atomic_दीर्घ_dec(&loaned_pages);
		nr--;
	पूर्ण
	cmm_dbg("End request with %ld pages unfulfilled\n", nr);
	वापस nr;
पूर्ण

/**
 * cmm_oom_notअगरy - OOM notअगरier
 * @self:	notअगरier block काष्ठा
 * @dummy:	not used
 * @parm:	वापसed - number of pages मुक्तd
 *
 * Return value:
 * 	NOTIFY_OK
 **/
अटल पूर्णांक cmm_oom_notअगरy(काष्ठा notअगरier_block *self,
			  अचिन्हित दीर्घ dummy, व्योम *parm)
अणु
	अचिन्हित दीर्घ *मुक्तd = parm;
	दीर्घ nr = KB2PAGES(oom_kb);

	cmm_dbg("OOM processing started\n");
	nr = cmm_मुक्त_pages(nr);
	loaned_pages_target = atomic_दीर्घ_पढ़ो(&loaned_pages);
	*मुक्तd += KB2PAGES(oom_kb) - nr;
	oom_मुक्तd_pages += KB2PAGES(oom_kb) - nr;
	cmm_dbg("OOM processing complete\n");
	वापस NOTIFY_OK;
पूर्ण

/**
 * cmm_get_mpp - Read memory perक्रमmance parameters
 *
 * Makes hcall to query the current page loan request from the hypervisor.
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम cmm_get_mpp(व्योम)
अणु
	स्थिर दीर्घ __loaned_pages = atomic_दीर्घ_पढ़ो(&loaned_pages);
	स्थिर दीर्घ total_pages = totalram_pages() + __loaned_pages;
	पूर्णांक rc;
	काष्ठा hvcall_mpp_data mpp_data;
	चिन्हित दीर्घ active_pages_target, page_loan_request, target;
	चिन्हित दीर्घ min_mem_pages = (min_mem_mb * 1024 * 1024) / PAGE_SIZE;

	अगर (likely(!simulate)) अणु
		rc = h_get_mpp(&mpp_data);
		अगर (rc != H_SUCCESS)
			वापस;
		page_loan_request = भाग_s64((s64)mpp_data.loan_request,
					    PAGE_SIZE);
		target = page_loan_request + __loaned_pages;
	पूर्ण अन्यथा अणु
		target = KB2PAGES(simulate_loan_target_kb);
		page_loan_request = target - __loaned_pages;
	पूर्ण

	अगर (target < 0 || total_pages < min_mem_pages)
		target = 0;

	अगर (target > oom_मुक्तd_pages)
		target -= oom_मुक्तd_pages;
	अन्यथा
		target = 0;

	active_pages_target = total_pages - target;

	अगर (min_mem_pages > active_pages_target)
		target = total_pages - min_mem_pages;

	अगर (target < 0)
		target = 0;

	loaned_pages_target = target;

	cmm_dbg("delta = %ld, loaned = %lu, target = %lu, oom = %lu, totalram = %lu\n",
		page_loan_request, __loaned_pages, loaned_pages_target,
		oom_मुक्तd_pages, totalram_pages());
पूर्ण

अटल काष्ठा notअगरier_block cmm_oom_nb = अणु
	.notअगरier_call = cmm_oom_notअगरy
पूर्ण;

/**
 * cmm_thपढ़ो - CMM task thपढ़ो
 * @dummy:	not used
 *
 * Return value:
 * 	0
 **/
अटल पूर्णांक cmm_thपढ़ो(व्योम *dummy)
अणु
	अचिन्हित दीर्घ समयleft;
	दीर्घ __loaned_pages;

	जबतक (1) अणु
		समयleft = msleep_पूर्णांकerruptible(delay * 1000);

		अगर (kthपढ़ो_should_stop() || समयleft)
			अवरोध;

		अगर (mutex_trylock(&hotplug_mutex)) अणु
			अगर (hotplug_occurred) अणु
				hotplug_occurred = 0;
				mutex_unlock(&hotplug_mutex);
				cmm_dbg("Hotplug operation has occurred, "
						"loaning activity suspended "
						"for %d seconds.\n",
						hotplug_delay);
				समयleft = msleep_पूर्णांकerruptible(hotplug_delay *
						1000);
				अगर (kthपढ़ो_should_stop() || समयleft)
					अवरोध;
				जारी;
			पूर्ण
			mutex_unlock(&hotplug_mutex);
		पूर्ण अन्यथा अणु
			cmm_dbg("Hotplug operation in progress, activity "
					"suspended\n");
			जारी;
		पूर्ण

		cmm_get_mpp();

		__loaned_pages = atomic_दीर्घ_पढ़ो(&loaned_pages);
		अगर (loaned_pages_target > __loaned_pages) अणु
			अगर (cmm_alloc_pages(loaned_pages_target - __loaned_pages))
				loaned_pages_target = __loaned_pages;
		पूर्ण अन्यथा अगर (loaned_pages_target < __loaned_pages)
			cmm_मुक्त_pages(__loaned_pages - loaned_pages_target);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा CMM_SHOW(name, क्रमmat, args...)			\
	अटल sमाप_प्रकार show_##name(काष्ठा device *dev,	\
				   काष्ठा device_attribute *attr,	\
				   अक्षर *buf)			\
	अणु							\
		वापस प्र_लिखो(buf, क्रमmat, ##args);		\
	पूर्ण							\
	अटल DEVICE_ATTR(name, 0444, show_##name, शून्य)

CMM_SHOW(loaned_kb, "%lu\n", PAGES2KB(atomic_दीर्घ_पढ़ो(&loaned_pages)));
CMM_SHOW(loaned_target_kb, "%lu\n", PAGES2KB(loaned_pages_target));

अटल sमाप_प्रकार show_oom_pages(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", PAGES2KB(oom_मुक्तd_pages));
पूर्ण

अटल sमाप_प्रकार store_oom_pages(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val = simple_म_से_अदीर्घ (buf, शून्य, 10);

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (val != 0)
		वापस -EBADMSG;

	oom_मुक्तd_pages = 0;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(oom_मुक्तd_kb, 0644,
		   show_oom_pages, store_oom_pages);

अटल काष्ठा device_attribute *cmm_attrs[] = अणु
	&dev_attr_loaned_kb,
	&dev_attr_loaned_target_kb,
	&dev_attr_oom_मुक्तd_kb,
पूर्ण;

अटल DEVICE_ULONG_ATTR(simulate_loan_target_kb, 0644,
			 simulate_loan_target_kb);

अटल काष्ठा bus_type cmm_subsys = अणु
	.name = "cmm",
	.dev_name = "cmm",
पूर्ण;

अटल व्योम cmm_release_device(काष्ठा device *dev)
अणु
पूर्ण

/**
 * cmm_sysfs_रेजिस्टर - Register with sysfs
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक cmm_sysfs_रेजिस्टर(काष्ठा device *dev)
अणु
	पूर्णांक i, rc;

	अगर ((rc = subsys_प्रणाली_रेजिस्टर(&cmm_subsys, शून्य)))
		वापस rc;

	dev->id = 0;
	dev->bus = &cmm_subsys;
	dev->release = cmm_release_device;

	अगर ((rc = device_रेजिस्टर(dev)))
		जाओ subsys_unरेजिस्टर;

	क्रम (i = 0; i < ARRAY_SIZE(cmm_attrs); i++) अणु
		अगर ((rc = device_create_file(dev, cmm_attrs[i])))
			जाओ fail;
	पूर्ण

	अगर (!simulate)
		वापस 0;
	rc = device_create_file(dev, &dev_attr_simulate_loan_target_kb.attr);
	अगर (rc)
		जाओ fail;
	वापस 0;

fail:
	जबतक (--i >= 0)
		device_हटाओ_file(dev, cmm_attrs[i]);
	device_unरेजिस्टर(dev);
subsys_unरेजिस्टर:
	bus_unरेजिस्टर(&cmm_subsys);
	वापस rc;
पूर्ण

/**
 * cmm_unरेजिस्टर_sysfs - Unरेजिस्टर from sysfs
 *
 **/
अटल व्योम cmm_unरेजिस्टर_sysfs(काष्ठा device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cmm_attrs); i++)
		device_हटाओ_file(dev, cmm_attrs[i]);
	device_unरेजिस्टर(dev);
	bus_unरेजिस्टर(&cmm_subsys);
पूर्ण

/**
 * cmm_reboot_notअगरier - Make sure pages are not still marked as "loaned"
 *
 **/
अटल पूर्णांक cmm_reboot_notअगरier(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ action, व्योम *unused)
अणु
	अगर (action == SYS_RESTART) अणु
		अगर (cmm_thपढ़ो_ptr)
			kthपढ़ो_stop(cmm_thपढ़ो_ptr);
		cmm_thपढ़ो_ptr = शून्य;
		cmm_मुक्त_pages(atomic_दीर्घ_पढ़ो(&loaned_pages));
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block cmm_reboot_nb = अणु
	.notअगरier_call = cmm_reboot_notअगरier,
पूर्ण;

/**
 * cmm_memory_cb - Handle memory hotplug notअगरier calls
 * @self:	notअगरier block काष्ठा
 * @action:	action to take
 * @arg:	काष्ठा memory_notअगरy data क्रम handler
 *
 * Return value:
 *	NOTIFY_OK or notअगरier error based on subfunction वापस value
 *
 **/
अटल पूर्णांक cmm_memory_cb(काष्ठा notअगरier_block *self,
			अचिन्हित दीर्घ action, व्योम *arg)
अणु
	पूर्णांक ret = 0;

	चयन (action) अणु
	हाल MEM_GOING_OFFLINE:
		mutex_lock(&hotplug_mutex);
		hotplug_occurred = 1;
		अवरोध;
	हाल MEM_OFFLINE:
	हाल MEM_CANCEL_OFFLINE:
		mutex_unlock(&hotplug_mutex);
		cmm_dbg("Memory offline operation complete.\n");
		अवरोध;
	हाल MEM_GOING_ONLINE:
	हाल MEM_ONLINE:
	हाल MEM_CANCEL_ONLINE:
		अवरोध;
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल काष्ठा notअगरier_block cmm_mem_nb = अणु
	.notअगरier_call = cmm_memory_cb,
	.priority = CMM_MEM_HOTPLUG_PRI
पूर्ण;

#अगर_घोषित CONFIG_BALLOON_COMPACTION
अटल काष्ठा vfsmount *balloon_mnt;

अटल पूर्णांक cmm_init_fs_context(काष्ठा fs_context *fc)
अणु
	वापस init_pseuकरो(fc, PPC_CMM_MAGIC) ? 0 : -ENOMEM;
पूर्ण

अटल काष्ठा file_प्रणाली_type balloon_fs = अणु
	.name = "ppc-cmm",
	.init_fs_context = cmm_init_fs_context,
	.समाप्त_sb = समाप्त_anon_super,
पूर्ण;

अटल पूर्णांक cmm_migratepage(काष्ठा balloon_dev_info *b_dev_info,
			   काष्ठा page *newpage, काष्ठा page *page,
			   क्रमागत migrate_mode mode)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * loan/"inflate" the newpage first.
	 *
	 * We might race against the cmm_thपढ़ो who might discover after our
	 * loan request that another page is to be unloaned. However, once
	 * the cmm_thपढ़ो runs again later, this error will स्वतःmatically
	 * be corrected.
	 */
	अगर (plpar_page_set_loaned(newpage)) अणु
		/* Unlikely, but possible. Tell the caller not to retry now. */
		pr_err_ratelimited("%s: Cannot set page to loaned.", __func__);
		वापस -EBUSY;
	पूर्ण

	/* balloon page list reference */
	get_page(newpage);

	/*
	 * When we migrate a page to a dअगरferent zone, we have to fixup the
	 * count of both involved zones as we adjusted the managed page count
	 * when inflating.
	 */
	अगर (page_zone(page) != page_zone(newpage)) अणु
		adjust_managed_page_count(page, 1);
		adjust_managed_page_count(newpage, -1);
	पूर्ण

	spin_lock_irqsave(&b_dev_info->pages_lock, flags);
	balloon_page_insert(b_dev_info, newpage);
	balloon_page_delete(page);
	b_dev_info->isolated_pages--;
	spin_unlock_irqrestore(&b_dev_info->pages_lock, flags);

	/*
	 * activate/"deflate" the old page. We ignore any errors just like the
	 * other callers.
	 */
	plpar_page_set_active(page);

	/* balloon page list reference */
	put_page(page);

	वापस MIGRATEPAGE_SUCCESS;
पूर्ण

अटल पूर्णांक cmm_balloon_compaction_init(व्योम)
अणु
	पूर्णांक rc;

	balloon_devinfo_init(&b_dev_info);
	b_dev_info.migratepage = cmm_migratepage;

	balloon_mnt = kern_mount(&balloon_fs);
	अगर (IS_ERR(balloon_mnt)) अणु
		rc = PTR_ERR(balloon_mnt);
		balloon_mnt = शून्य;
		वापस rc;
	पूर्ण

	b_dev_info.inode = alloc_anon_inode(balloon_mnt->mnt_sb);
	अगर (IS_ERR(b_dev_info.inode)) अणु
		rc = PTR_ERR(b_dev_info.inode);
		b_dev_info.inode = शून्य;
		kern_unmount(balloon_mnt);
		balloon_mnt = शून्य;
		वापस rc;
	पूर्ण

	b_dev_info.inode->i_mapping->a_ops = &balloon_aops;
	वापस 0;
पूर्ण
अटल व्योम cmm_balloon_compaction_deinit(व्योम)
अणु
	अगर (b_dev_info.inode)
		iput(b_dev_info.inode);
	b_dev_info.inode = शून्य;
	kern_unmount(balloon_mnt);
	balloon_mnt = शून्य;
पूर्ण
#अन्यथा /* CONFIG_BALLOON_COMPACTION */
अटल पूर्णांक cmm_balloon_compaction_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम cmm_balloon_compaction_deinit(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BALLOON_COMPACTION */

/**
 * cmm_init - Module initialization
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक cmm_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!firmware_has_feature(FW_FEATURE_CMO) && !simulate)
		वापस -EOPNOTSUPP;

	rc = cmm_balloon_compaction_init();
	अगर (rc)
		वापस rc;

	rc = रेजिस्टर_oom_notअगरier(&cmm_oom_nb);
	अगर (rc < 0)
		जाओ out_balloon_compaction;

	अगर ((rc = रेजिस्टर_reboot_notअगरier(&cmm_reboot_nb)))
		जाओ out_oom_notअगरier;

	अगर ((rc = cmm_sysfs_रेजिस्टर(&cmm_dev)))
		जाओ out_reboot_notअगरier;

	rc = रेजिस्टर_memory_notअगरier(&cmm_mem_nb);
	अगर (rc)
		जाओ out_unरेजिस्टर_notअगरier;

	अगर (cmm_disabled)
		वापस 0;

	cmm_thपढ़ो_ptr = kthपढ़ो_run(cmm_thपढ़ो, शून्य, "cmmthread");
	अगर (IS_ERR(cmm_thपढ़ो_ptr)) अणु
		rc = PTR_ERR(cmm_thपढ़ो_ptr);
		जाओ out_unरेजिस्टर_notअगरier;
	पूर्ण

	वापस 0;
out_unरेजिस्टर_notअगरier:
	unरेजिस्टर_memory_notअगरier(&cmm_mem_nb);
	cmm_unरेजिस्टर_sysfs(&cmm_dev);
out_reboot_notअगरier:
	unरेजिस्टर_reboot_notअगरier(&cmm_reboot_nb);
out_oom_notअगरier:
	unरेजिस्टर_oom_notअगरier(&cmm_oom_nb);
out_balloon_compaction:
	cmm_balloon_compaction_deinit();
	वापस rc;
पूर्ण

/**
 * cmm_निकास - Module निकास
 *
 * Return value:
 * 	nothing
 **/
अटल व्योम cmm_निकास(व्योम)
अणु
	अगर (cmm_thपढ़ो_ptr)
		kthपढ़ो_stop(cmm_thपढ़ो_ptr);
	unरेजिस्टर_oom_notअगरier(&cmm_oom_nb);
	unरेजिस्टर_reboot_notअगरier(&cmm_reboot_nb);
	unरेजिस्टर_memory_notअगरier(&cmm_mem_nb);
	cmm_मुक्त_pages(atomic_दीर्घ_पढ़ो(&loaned_pages));
	cmm_unरेजिस्टर_sysfs(&cmm_dev);
	cmm_balloon_compaction_deinit();
पूर्ण

/**
 * cmm_set_disable - Disable/Enable CMM
 *
 * Return value:
 * 	0 on success / other on failure
 **/
अटल पूर्णांक cmm_set_disable(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक disable = simple_म_से_अदीर्घ(val, शून्य, 10);

	अगर (disable != 0 && disable != 1)
		वापस -EINVAL;

	अगर (disable && !cmm_disabled) अणु
		अगर (cmm_thपढ़ो_ptr)
			kthपढ़ो_stop(cmm_thपढ़ो_ptr);
		cmm_thपढ़ो_ptr = शून्य;
		cmm_मुक्त_pages(atomic_दीर्घ_पढ़ो(&loaned_pages));
	पूर्ण अन्यथा अगर (!disable && cmm_disabled) अणु
		cmm_thपढ़ो_ptr = kthपढ़ो_run(cmm_thपढ़ो, शून्य, "cmmthread");
		अगर (IS_ERR(cmm_thपढ़ो_ptr))
			वापस PTR_ERR(cmm_thपढ़ो_ptr);
	पूर्ण

	cmm_disabled = disable;
	वापस 0;
पूर्ण

module_param_call(disable, cmm_set_disable, param_get_uपूर्णांक,
		  &cmm_disabled, 0644);
MODULE_PARM_DESC(disable, "Disable CMM. Set to 1 to disable. "
		 "[Default=" __stringअगरy(CMM_DISABLE) "]");

module_init(cmm_init);
module_निकास(cmm_निकास);
