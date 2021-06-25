<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Memory subप्रणाली support
 *
 * Written by Matt Tolentino <matthew.e.tolentino@पूर्णांकel.com>
 *            Dave Hansen <haveblue@us.ibm.com>
 *
 * This file provides the necessary infraकाष्ठाure to represent
 * a SPARSEMEM-memory-model प्रणाली's physical memory in /sysfs.
 * All arch-independent code that assumes MEMORY_HOTPLUG requires
 * SPARSEMEM should be contained here, or in mm/memory_hotplug.c.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/topology.h>
#समावेश <linux/capability.h>
#समावेश <linux/device.h>
#समावेश <linux/memory.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/mm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/xarray.h>

#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>

#घोषणा MEMORY_CLASS_NAME	"memory"

अटल स्थिर अक्षर *स्थिर online_type_to_str[] = अणु
	[MMOP_OFFLINE] = "offline",
	[MMOP_ONLINE] = "online",
	[MMOP_ONLINE_KERNEL] = "online_kernel",
	[MMOP_ONLINE_MOVABLE] = "online_movable",
पूर्ण;

पूर्णांक mhp_online_type_from_str(स्थिर अक्षर *str)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(online_type_to_str); i++) अणु
		अगर (sysfs_streq(str, online_type_to_str[i]))
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा to_memory_block(dev) container_of(dev, काष्ठा memory_block, dev)

अटल पूर्णांक sections_per_block;

अटल अंतरभूत अचिन्हित दीर्घ memory_block_id(अचिन्हित दीर्घ section_nr)
अणु
	वापस section_nr / sections_per_block;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pfn_to_block_id(अचिन्हित दीर्घ pfn)
अणु
	वापस memory_block_id(pfn_to_section_nr(pfn));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ phys_to_block_id(अचिन्हित दीर्घ phys)
अणु
	वापस pfn_to_block_id(PFN_DOWN(phys));
पूर्ण

अटल पूर्णांक memory_subsys_online(काष्ठा device *dev);
अटल पूर्णांक memory_subsys_offline(काष्ठा device *dev);

अटल काष्ठा bus_type memory_subsys = अणु
	.name = MEMORY_CLASS_NAME,
	.dev_name = MEMORY_CLASS_NAME,
	.online = memory_subsys_online,
	.offline = memory_subsys_offline,
पूर्ण;

/*
 * Memory blocks are cached in a local radix tree to aव्योम
 * a costly linear search क्रम the corresponding device on
 * the subप्रणाली bus.
 */
अटल DEFINE_XARRAY(memory_blocks);

अटल BLOCKING_NOTIFIER_HEAD(memory_chain);

पूर्णांक रेजिस्टर_memory_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&memory_chain, nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_memory_notअगरier);

व्योम unरेजिस्टर_memory_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&memory_chain, nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_memory_notअगरier);

अटल व्योम memory_block_release(काष्ठा device *dev)
अणु
	काष्ठा memory_block *mem = to_memory_block(dev);

	kमुक्त(mem);
पूर्ण

अचिन्हित दीर्घ __weak memory_block_size_bytes(व्योम)
अणु
	वापस MIN_MEMORY_BLOCK_SIZE;
पूर्ण
EXPORT_SYMBOL_GPL(memory_block_size_bytes);

/*
 * Show the first physical section index (number) of this memory block.
 */
अटल sमाप_प्रकार phys_index_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा memory_block *mem = to_memory_block(dev);
	अचिन्हित दीर्घ phys_index;

	phys_index = mem->start_section_nr / sections_per_block;

	वापस sysfs_emit(buf, "%08lx\n", phys_index);
पूर्ण

/*
 * Legacy पूर्णांकerface that we cannot हटाओ. Always indicate "removable"
 * with CONFIG_MEMORY_HOTREMOVE - bad heuristic.
 */
अटल sमाप_प्रकार removable_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", (पूर्णांक)IS_ENABLED(CONFIG_MEMORY_HOTREMOVE));
पूर्ण

/*
 * online, offline, going offline, etc.
 */
अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा memory_block *mem = to_memory_block(dev);
	स्थिर अक्षर *output;

	/*
	 * We can probably put these states in a nice little array
	 * so that they're not खोलो-coded
	 */
	चयन (mem->state) अणु
	हाल MEM_ONLINE:
		output = "online";
		अवरोध;
	हाल MEM_OFFLINE:
		output = "offline";
		अवरोध;
	हाल MEM_GOING_OFFLINE:
		output = "going-offline";
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस sysfs_emit(buf, "ERROR-UNKNOWN-%ld\n", mem->state);
	पूर्ण

	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण

पूर्णांक memory_notअगरy(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस blocking_notअगरier_call_chain(&memory_chain, val, v);
पूर्ण

अटल पूर्णांक memory_block_online(काष्ठा memory_block *mem)
अणु
	अचिन्हित दीर्घ start_pfn = section_nr_to_pfn(mem->start_section_nr);
	अचिन्हित दीर्घ nr_pages = PAGES_PER_SECTION * sections_per_block;
	अचिन्हित दीर्घ nr_vmemmap_pages = mem->nr_vmemmap_pages;
	काष्ठा zone *zone;
	पूर्णांक ret;

	zone = zone_क्रम_pfn_range(mem->online_type, mem->nid, start_pfn, nr_pages);

	/*
	 * Although vmemmap pages have a dअगरferent lअगरecycle than the pages
	 * they describe (they reमुख्य until the memory is unplugged), करोing
	 * their initialization and accounting at memory onlining/offlining
	 * stage helps to keep accounting easier to follow - e.g vmemmaps
	 * beदीर्घ to the same zone as the memory they backed.
	 */
	अगर (nr_vmemmap_pages) अणु
		ret = mhp_init_memmap_on_memory(start_pfn, nr_vmemmap_pages, zone);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = online_pages(start_pfn + nr_vmemmap_pages,
			   nr_pages - nr_vmemmap_pages, zone);
	अगर (ret) अणु
		अगर (nr_vmemmap_pages)
			mhp_deinit_memmap_on_memory(start_pfn, nr_vmemmap_pages);
		वापस ret;
	पूर्ण

	/*
	 * Account once onlining succeeded. If the zone was unpopulated, it is
	 * now alपढ़ोy properly populated.
	 */
	अगर (nr_vmemmap_pages)
		adjust_present_page_count(zone, nr_vmemmap_pages);

	वापस ret;
पूर्ण

अटल पूर्णांक memory_block_offline(काष्ठा memory_block *mem)
अणु
	अचिन्हित दीर्घ start_pfn = section_nr_to_pfn(mem->start_section_nr);
	अचिन्हित दीर्घ nr_pages = PAGES_PER_SECTION * sections_per_block;
	अचिन्हित दीर्घ nr_vmemmap_pages = mem->nr_vmemmap_pages;
	काष्ठा zone *zone;
	पूर्णांक ret;

	/*
	 * Unaccount beक्रमe offlining, such that unpopulated zone and kthपढ़ोs
	 * can properly be torn करोwn in offline_pages().
	 */
	अगर (nr_vmemmap_pages) अणु
		zone = page_zone(pfn_to_page(start_pfn));
		adjust_present_page_count(zone, -nr_vmemmap_pages);
	पूर्ण

	ret = offline_pages(start_pfn + nr_vmemmap_pages,
			    nr_pages - nr_vmemmap_pages);
	अगर (ret) अणु
		/* offline_pages() failed. Account back. */
		अगर (nr_vmemmap_pages)
			adjust_present_page_count(zone, nr_vmemmap_pages);
		वापस ret;
	पूर्ण

	अगर (nr_vmemmap_pages)
		mhp_deinit_memmap_on_memory(start_pfn, nr_vmemmap_pages);

	वापस ret;
पूर्ण

/*
 * MEMORY_HOTPLUG depends on SPARSEMEM in mm/Kconfig, so it is
 * OK to have direct references to sparsemem variables in here.
 */
अटल पूर्णांक
memory_block_action(काष्ठा memory_block *mem, अचिन्हित दीर्घ action)
अणु
	पूर्णांक ret;

	चयन (action) अणु
	हाल MEM_ONLINE:
		ret = memory_block_online(mem);
		अवरोध;
	हाल MEM_OFFLINE:
		ret = memory_block_offline(mem);
		अवरोध;
	शेष:
		WARN(1, KERN_WARNING "%s(%ld, %ld) unknown action: "
		     "%ld\n", __func__, mem->start_section_nr, action, action);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक memory_block_change_state(काष्ठा memory_block *mem,
		अचिन्हित दीर्घ to_state, अचिन्हित दीर्घ from_state_req)
अणु
	पूर्णांक ret = 0;

	अगर (mem->state != from_state_req)
		वापस -EINVAL;

	अगर (to_state == MEM_OFFLINE)
		mem->state = MEM_GOING_OFFLINE;

	ret = memory_block_action(mem, to_state);
	mem->state = ret ? from_state_req : to_state;

	वापस ret;
पूर्ण

/* The device lock serializes operations on memory_subsys_[online|offline] */
अटल पूर्णांक memory_subsys_online(काष्ठा device *dev)
अणु
	काष्ठा memory_block *mem = to_memory_block(dev);
	पूर्णांक ret;

	अगर (mem->state == MEM_ONLINE)
		वापस 0;

	/*
	 * When called via device_online() without configuring the online_type,
	 * we want to शेष to MMOP_ONLINE.
	 */
	अगर (mem->online_type == MMOP_OFFLINE)
		mem->online_type = MMOP_ONLINE;

	ret = memory_block_change_state(mem, MEM_ONLINE, MEM_OFFLINE);
	mem->online_type = MMOP_OFFLINE;

	वापस ret;
पूर्ण

अटल पूर्णांक memory_subsys_offline(काष्ठा device *dev)
अणु
	काष्ठा memory_block *mem = to_memory_block(dev);

	अगर (mem->state == MEM_OFFLINE)
		वापस 0;

	वापस memory_block_change_state(mem, MEM_OFFLINE, MEM_ONLINE);
पूर्ण

अटल sमाप_प्रकार state_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	स्थिर पूर्णांक online_type = mhp_online_type_from_str(buf);
	काष्ठा memory_block *mem = to_memory_block(dev);
	पूर्णांक ret;

	अगर (online_type < 0)
		वापस -EINVAL;

	ret = lock_device_hotplug_sysfs();
	अगर (ret)
		वापस ret;

	चयन (online_type) अणु
	हाल MMOP_ONLINE_KERNEL:
	हाल MMOP_ONLINE_MOVABLE:
	हाल MMOP_ONLINE:
		/* mem->online_type is रक्षित by device_hotplug_lock */
		mem->online_type = online_type;
		ret = device_online(&mem->dev);
		अवरोध;
	हाल MMOP_OFFLINE:
		ret = device_offline(&mem->dev);
		अवरोध;
	शेष:
		ret = -EINVAL; /* should never happen */
	पूर्ण

	unlock_device_hotplug();

	अगर (ret < 0)
		वापस ret;
	अगर (ret)
		वापस -EINVAL;

	वापस count;
पूर्ण

/*
 * Legacy पूर्णांकerface that we cannot हटाओ: s390x exposes the storage increment
 * covered by a memory block, allowing क्रम identअगरying which memory blocks
 * comprise a storage increment. Since a memory block spans complete
 * storage increments nowadays, this पूर्णांकerface is basically unused. Other
 * archs never exposed != 0.
 */
अटल sमाप_प्रकार phys_device_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा memory_block *mem = to_memory_block(dev);
	अचिन्हित दीर्घ start_pfn = section_nr_to_pfn(mem->start_section_nr);

	वापस sysfs_emit(buf, "%d\n",
			  arch_get_memory_phys_device(start_pfn));
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
अटल पूर्णांक prपूर्णांक_allowed_zone(अक्षर *buf, पूर्णांक len, पूर्णांक nid,
			      अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages,
			      पूर्णांक online_type, काष्ठा zone *शेष_zone)
अणु
	काष्ठा zone *zone;

	zone = zone_क्रम_pfn_range(online_type, nid, start_pfn, nr_pages);
	अगर (zone == शेष_zone)
		वापस 0;

	वापस sysfs_emit_at(buf, len, " %s", zone->name);
पूर्ण

अटल sमाप_प्रकार valid_zones_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा memory_block *mem = to_memory_block(dev);
	अचिन्हित दीर्घ start_pfn = section_nr_to_pfn(mem->start_section_nr);
	अचिन्हित दीर्घ nr_pages = PAGES_PER_SECTION * sections_per_block;
	काष्ठा zone *शेष_zone;
	पूर्णांक len = 0;
	पूर्णांक nid;

	/*
	 * Check the existing zone. Make sure that we करो that only on the
	 * online nodes otherwise the page_zone is not reliable
	 */
	अगर (mem->state == MEM_ONLINE) अणु
		/*
		 * The block contains more than one zone can not be offlined.
		 * This can happen e.g. क्रम ZONE_DMA and ZONE_DMA32
		 */
		शेष_zone = test_pages_in_a_zone(start_pfn,
						    start_pfn + nr_pages);
		अगर (!शेष_zone)
			वापस sysfs_emit(buf, "%s\n", "none");
		len += sysfs_emit_at(buf, len, "%s", शेष_zone->name);
		जाओ out;
	पूर्ण

	nid = mem->nid;
	शेष_zone = zone_क्रम_pfn_range(MMOP_ONLINE, nid, start_pfn,
					  nr_pages);

	len += sysfs_emit_at(buf, len, "%s", शेष_zone->name);
	len += prपूर्णांक_allowed_zone(buf, len, nid, start_pfn, nr_pages,
				  MMOP_ONLINE_KERNEL, शेष_zone);
	len += prपूर्णांक_allowed_zone(buf, len, nid, start_pfn, nr_pages,
				  MMOP_ONLINE_MOVABLE, शेष_zone);
out:
	len += sysfs_emit_at(buf, len, "\n");
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(valid_zones);
#पूर्ण_अगर

अटल DEVICE_ATTR_RO(phys_index);
अटल DEVICE_ATTR_RW(state);
अटल DEVICE_ATTR_RO(phys_device);
अटल DEVICE_ATTR_RO(removable);

/*
 * Show the memory block size (shared by all memory blocks).
 */
अटल sमाप_प्रकार block_size_bytes_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%lx\n", memory_block_size_bytes());
पूर्ण

अटल DEVICE_ATTR_RO(block_size_bytes);

/*
 * Memory स्वतः online policy.
 */

अटल sमाप_प्रकार स्वतः_online_blocks_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%s\n",
			  online_type_to_str[mhp_शेष_online_type]);
पूर्ण

अटल sमाप_प्रकार स्वतः_online_blocks_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	स्थिर पूर्णांक online_type = mhp_online_type_from_str(buf);

	अगर (online_type < 0)
		वापस -EINVAL;

	mhp_शेष_online_type = online_type;
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(स्वतः_online_blocks);

/*
 * Some architectures will have custom drivers to करो this, and
 * will not need to करो it from userspace.  The fake hot-add code
 * as well as ppc64 will करो all of their discovery in userspace
 * and will require this पूर्णांकerface.
 */
#अगर_घोषित CONFIG_ARCH_MEMORY_PROBE
अटल sमाप_प्रकार probe_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u64 phys_addr;
	पूर्णांक nid, ret;
	अचिन्हित दीर्घ pages_per_block = PAGES_PER_SECTION * sections_per_block;

	ret = kम_से_अदीर्घl(buf, 0, &phys_addr);
	अगर (ret)
		वापस ret;

	अगर (phys_addr & ((pages_per_block << PAGE_SHIFT) - 1))
		वापस -EINVAL;

	ret = lock_device_hotplug_sysfs();
	अगर (ret)
		वापस ret;

	nid = memory_add_physaddr_to_nid(phys_addr);
	ret = __add_memory(nid, phys_addr,
			   MIN_MEMORY_BLOCK_SIZE * sections_per_block,
			   MHP_NONE);

	अगर (ret)
		जाओ out;

	ret = count;
out:
	unlock_device_hotplug();
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_WO(probe);
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMORY_FAILURE
/*
 * Support क्रम offlining pages of memory
 */

/* Soft offline a page */
अटल sमाप_प्रकार soft_offline_page_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	u64 pfn;
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (kम_से_अदीर्घl(buf, 0, &pfn) < 0)
		वापस -EINVAL;
	pfn >>= PAGE_SHIFT;
	ret = soft_offline_page(pfn, 0);
	वापस ret == 0 ? count : ret;
पूर्ण

/* Forcibly offline a page, including समाप्तing processes. */
अटल sमाप_प्रकार hard_offline_page_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	u64 pfn;
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (kम_से_अदीर्घl(buf, 0, &pfn) < 0)
		वापस -EINVAL;
	pfn >>= PAGE_SHIFT;
	ret = memory_failure(pfn, 0);
	वापस ret ? ret : count;
पूर्ण

अटल DEVICE_ATTR_WO(soft_offline_page);
अटल DEVICE_ATTR_WO(hard_offline_page);
#पूर्ण_अगर

/* See phys_device_show(). */
पूर्णांक __weak arch_get_memory_phys_device(अचिन्हित दीर्घ start_pfn)
अणु
	वापस 0;
पूर्ण

/*
 * A reference क्रम the वापसed memory block device is acquired.
 *
 * Called under device_hotplug_lock.
 */
अटल काष्ठा memory_block *find_memory_block_by_id(अचिन्हित दीर्घ block_id)
अणु
	काष्ठा memory_block *mem;

	mem = xa_load(&memory_blocks, block_id);
	अगर (mem)
		get_device(&mem->dev);
	वापस mem;
पूर्ण

/*
 * Called under device_hotplug_lock.
 */
काष्ठा memory_block *find_memory_block(काष्ठा mem_section *section)
अणु
	अचिन्हित दीर्घ block_id = memory_block_id(__section_nr(section));

	वापस find_memory_block_by_id(block_id);
पूर्ण

अटल काष्ठा attribute *memory_memblk_attrs[] = अणु
	&dev_attr_phys_index.attr,
	&dev_attr_state.attr,
	&dev_attr_phys_device.attr,
	&dev_attr_removable.attr,
#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
	&dev_attr_valid_zones.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल काष्ठा attribute_group memory_memblk_attr_group = अणु
	.attrs = memory_memblk_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *memory_memblk_attr_groups[] = अणु
	&memory_memblk_attr_group,
	शून्य,
पूर्ण;

/*
 * रेजिस्टर_memory - Setup a sysfs device क्रम a memory block
 */
अटल
पूर्णांक रेजिस्टर_memory(काष्ठा memory_block *memory)
अणु
	पूर्णांक ret;

	memory->dev.bus = &memory_subsys;
	memory->dev.id = memory->start_section_nr / sections_per_block;
	memory->dev.release = memory_block_release;
	memory->dev.groups = memory_memblk_attr_groups;
	memory->dev.offline = memory->state == MEM_OFFLINE;

	ret = device_रेजिस्टर(&memory->dev);
	अगर (ret) अणु
		put_device(&memory->dev);
		वापस ret;
	पूर्ण
	ret = xa_err(xa_store(&memory_blocks, memory->dev.id, memory,
			      GFP_KERNEL));
	अगर (ret) अणु
		put_device(&memory->dev);
		device_unरेजिस्टर(&memory->dev);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक init_memory_block(अचिन्हित दीर्घ block_id, अचिन्हित दीर्घ state,
			     अचिन्हित दीर्घ nr_vmemmap_pages)
अणु
	काष्ठा memory_block *mem;
	पूर्णांक ret = 0;

	mem = find_memory_block_by_id(block_id);
	अगर (mem) अणु
		put_device(&mem->dev);
		वापस -EEXIST;
	पूर्ण
	mem = kzalloc(माप(*mem), GFP_KERNEL);
	अगर (!mem)
		वापस -ENOMEM;

	mem->start_section_nr = block_id * sections_per_block;
	mem->state = state;
	mem->nid = NUMA_NO_NODE;
	mem->nr_vmemmap_pages = nr_vmemmap_pages;

	ret = रेजिस्टर_memory(mem);

	वापस ret;
पूर्ण

अटल पूर्णांक add_memory_block(अचिन्हित दीर्घ base_section_nr)
अणु
	पूर्णांक section_count = 0;
	अचिन्हित दीर्घ nr;

	क्रम (nr = base_section_nr; nr < base_section_nr + sections_per_block;
	     nr++)
		अगर (present_section_nr(nr))
			section_count++;

	अगर (section_count == 0)
		वापस 0;
	वापस init_memory_block(memory_block_id(base_section_nr),
				 MEM_ONLINE, 0);
पूर्ण

अटल व्योम unरेजिस्टर_memory(काष्ठा memory_block *memory)
अणु
	अगर (WARN_ON_ONCE(memory->dev.bus != &memory_subsys))
		वापस;

	WARN_ON(xa_erase(&memory_blocks, memory->dev.id) == शून्य);

	/* drop the ref. we got via find_memory_block() */
	put_device(&memory->dev);
	device_unरेजिस्टर(&memory->dev);
पूर्ण

/*
 * Create memory block devices क्रम the given memory area. Start and size
 * have to be aligned to memory block granularity. Memory block devices
 * will be initialized as offline.
 *
 * Called under device_hotplug_lock.
 */
पूर्णांक create_memory_block_devices(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ vmemmap_pages)
अणु
	स्थिर अचिन्हित दीर्घ start_block_id = pfn_to_block_id(PFN_DOWN(start));
	अचिन्हित दीर्घ end_block_id = pfn_to_block_id(PFN_DOWN(start + size));
	काष्ठा memory_block *mem;
	अचिन्हित दीर्घ block_id;
	पूर्णांक ret = 0;

	अगर (WARN_ON_ONCE(!IS_ALIGNED(start, memory_block_size_bytes()) ||
			 !IS_ALIGNED(size, memory_block_size_bytes())))
		वापस -EINVAL;

	क्रम (block_id = start_block_id; block_id != end_block_id; block_id++) अणु
		ret = init_memory_block(block_id, MEM_OFFLINE, vmemmap_pages);
		अगर (ret)
			अवरोध;
	पूर्ण
	अगर (ret) अणु
		end_block_id = block_id;
		क्रम (block_id = start_block_id; block_id != end_block_id;
		     block_id++) अणु
			mem = find_memory_block_by_id(block_id);
			अगर (WARN_ON_ONCE(!mem))
				जारी;
			unरेजिस्टर_memory(mem);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Remove memory block devices क्रम the given memory area. Start and size
 * have to be aligned to memory block granularity. Memory block devices
 * have to be offline.
 *
 * Called under device_hotplug_lock.
 */
व्योम हटाओ_memory_block_devices(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	स्थिर अचिन्हित दीर्घ start_block_id = pfn_to_block_id(PFN_DOWN(start));
	स्थिर अचिन्हित दीर्घ end_block_id = pfn_to_block_id(PFN_DOWN(start + size));
	काष्ठा memory_block *mem;
	अचिन्हित दीर्घ block_id;

	अगर (WARN_ON_ONCE(!IS_ALIGNED(start, memory_block_size_bytes()) ||
			 !IS_ALIGNED(size, memory_block_size_bytes())))
		वापस;

	क्रम (block_id = start_block_id; block_id != end_block_id; block_id++) अणु
		mem = find_memory_block_by_id(block_id);
		अगर (WARN_ON_ONCE(!mem))
			जारी;
		unरेजिस्टर_memory_block_under_nodes(mem);
		unरेजिस्टर_memory(mem);
	पूर्ण
पूर्ण

/* वापस true अगर the memory block is offlined, otherwise, वापस false */
bool is_memblock_offlined(काष्ठा memory_block *mem)
अणु
	वापस mem->state == MEM_OFFLINE;
पूर्ण

अटल काष्ठा attribute *memory_root_attrs[] = अणु
#अगर_घोषित CONFIG_ARCH_MEMORY_PROBE
	&dev_attr_probe.attr,
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMORY_FAILURE
	&dev_attr_soft_offline_page.attr,
	&dev_attr_hard_offline_page.attr,
#पूर्ण_अगर

	&dev_attr_block_size_bytes.attr,
	&dev_attr_स्वतः_online_blocks.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group memory_root_attr_group = अणु
	.attrs = memory_root_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *memory_root_attr_groups[] = अणु
	&memory_root_attr_group,
	शून्य,
पूर्ण;

/*
 * Initialize the sysfs support क्रम memory devices. At the समय this function
 * is called, we cannot have concurrent creation/deletion of memory block
 * devices, the device_hotplug_lock is not needed.
 */
व्योम __init memory_dev_init(व्योम)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ block_sz, nr;

	/* Validate the configured memory block size */
	block_sz = memory_block_size_bytes();
	अगर (!is_घातer_of_2(block_sz) || block_sz < MIN_MEMORY_BLOCK_SIZE)
		panic("Memory block size not suitable: 0x%lx\n", block_sz);
	sections_per_block = block_sz / MIN_MEMORY_BLOCK_SIZE;

	ret = subsys_प्रणाली_रेजिस्टर(&memory_subsys, memory_root_attr_groups);
	अगर (ret)
		panic("%s() failed to register subsystem: %d\n", __func__, ret);

	/*
	 * Create entries क्रम memory sections that were found
	 * during boot and have been initialized
	 */
	क्रम (nr = 0; nr <= __highest_present_section_nr;
	     nr += sections_per_block) अणु
		ret = add_memory_block(nr);
		अगर (ret)
			panic("%s() failed to add memory block: %d\n", __func__,
			      ret);
	पूर्ण
पूर्ण

/**
 * walk_memory_blocks - walk through all present memory blocks overlapped
 *			by the range [start, start + size)
 *
 * @start: start address of the memory range
 * @size: size of the memory range
 * @arg: argument passed to func
 * @func: callback क्रम each memory section walked
 *
 * This function walks through all present memory blocks overlapped by the
 * range [start, start + size), calling func on each memory block.
 *
 * In हाल func() वापसs an error, walking is पातed and the error is
 * वापसed.
 *
 * Called under device_hotplug_lock.
 */
पूर्णांक walk_memory_blocks(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
		       व्योम *arg, walk_memory_blocks_func_t func)
अणु
	स्थिर अचिन्हित दीर्घ start_block_id = phys_to_block_id(start);
	स्थिर अचिन्हित दीर्घ end_block_id = phys_to_block_id(start + size - 1);
	काष्ठा memory_block *mem;
	अचिन्हित दीर्घ block_id;
	पूर्णांक ret = 0;

	अगर (!size)
		वापस 0;

	क्रम (block_id = start_block_id; block_id <= end_block_id; block_id++) अणु
		mem = find_memory_block_by_id(block_id);
		अगर (!mem)
			जारी;

		ret = func(mem, arg);
		put_device(&mem->dev);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

काष्ठा क्रम_each_memory_block_cb_data अणु
	walk_memory_blocks_func_t func;
	व्योम *arg;
पूर्ण;

अटल पूर्णांक क्रम_each_memory_block_cb(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा memory_block *mem = to_memory_block(dev);
	काष्ठा क्रम_each_memory_block_cb_data *cb_data = data;

	वापस cb_data->func(mem, cb_data->arg);
पूर्ण

/**
 * क्रम_each_memory_block - walk through all present memory blocks
 *
 * @arg: argument passed to func
 * @func: callback क्रम each memory block walked
 *
 * This function walks through all present memory blocks, calling func on
 * each memory block.
 *
 * In हाल func() वापसs an error, walking is पातed and the error is
 * वापसed.
 */
पूर्णांक क्रम_each_memory_block(व्योम *arg, walk_memory_blocks_func_t func)
अणु
	काष्ठा क्रम_each_memory_block_cb_data cb_data = अणु
		.func = func,
		.arg = arg,
	पूर्ण;

	वापस bus_क्रम_each_dev(&memory_subsys, शून्य, &cb_data,
				क्रम_each_memory_block_cb);
पूर्ण
