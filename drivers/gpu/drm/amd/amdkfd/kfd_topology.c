<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/acpi.h>
#समावेश <linux/hash.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/log2.h>
#समावेश <linux/dmi.h>
#समावेश <linux/atomic.h>

#समावेश "kfd_priv.h"
#समावेश "kfd_crat.h"
#समावेश "kfd_topology.h"
#समावेश "kfd_device_queue_manager.h"
#समावेश "kfd_iommu.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu_ras.h"

/* topology_device_list - Master list of all topology devices */
अटल काष्ठा list_head topology_device_list;
अटल काष्ठा kfd_प्रणाली_properties sys_props;

अटल DECLARE_RWSEM(topology_lock);
अटल atomic_t topology_crat_proximity_करोमुख्य;

काष्ठा kfd_topology_device *kfd_topology_device_by_proximity_करोमुख्य(
						uपूर्णांक32_t proximity_करोमुख्य)
अणु
	काष्ठा kfd_topology_device *top_dev;
	काष्ठा kfd_topology_device *device = शून्य;

	करोwn_पढ़ो(&topology_lock);

	list_क्रम_each_entry(top_dev, &topology_device_list, list)
		अगर (top_dev->proximity_करोमुख्य == proximity_करोमुख्य) अणु
			device = top_dev;
			अवरोध;
		पूर्ण

	up_पढ़ो(&topology_lock);

	वापस device;
पूर्ण

काष्ठा kfd_topology_device *kfd_topology_device_by_id(uपूर्णांक32_t gpu_id)
अणु
	काष्ठा kfd_topology_device *top_dev = शून्य;
	काष्ठा kfd_topology_device *ret = शून्य;

	करोwn_पढ़ो(&topology_lock);

	list_क्रम_each_entry(top_dev, &topology_device_list, list)
		अगर (top_dev->gpu_id == gpu_id) अणु
			ret = top_dev;
			अवरोध;
		पूर्ण

	up_पढ़ो(&topology_lock);

	वापस ret;
पूर्ण

काष्ठा kfd_dev *kfd_device_by_id(uपूर्णांक32_t gpu_id)
अणु
	काष्ठा kfd_topology_device *top_dev;

	top_dev = kfd_topology_device_by_id(gpu_id);
	अगर (!top_dev)
		वापस शून्य;

	वापस top_dev->gpu;
पूर्ण

काष्ठा kfd_dev *kfd_device_by_pci_dev(स्थिर काष्ठा pci_dev *pdev)
अणु
	काष्ठा kfd_topology_device *top_dev;
	काष्ठा kfd_dev *device = शून्य;

	करोwn_पढ़ो(&topology_lock);

	list_क्रम_each_entry(top_dev, &topology_device_list, list)
		अगर (top_dev->gpu && top_dev->gpu->pdev == pdev) अणु
			device = top_dev->gpu;
			अवरोध;
		पूर्ण

	up_पढ़ो(&topology_lock);

	वापस device;
पूर्ण

काष्ठा kfd_dev *kfd_device_by_kgd(स्थिर काष्ठा kgd_dev *kgd)
अणु
	काष्ठा kfd_topology_device *top_dev;
	काष्ठा kfd_dev *device = शून्य;

	करोwn_पढ़ो(&topology_lock);

	list_क्रम_each_entry(top_dev, &topology_device_list, list)
		अगर (top_dev->gpu && top_dev->gpu->kgd == kgd) अणु
			device = top_dev->gpu;
			अवरोध;
		पूर्ण

	up_पढ़ो(&topology_lock);

	वापस device;
पूर्ण

/* Called with ग_लिखो topology_lock acquired */
अटल व्योम kfd_release_topology_device(काष्ठा kfd_topology_device *dev)
अणु
	काष्ठा kfd_mem_properties *mem;
	काष्ठा kfd_cache_properties *cache;
	काष्ठा kfd_iolink_properties *iolink;
	काष्ठा kfd_perf_properties *perf;

	list_del(&dev->list);

	जबतक (dev->mem_props.next != &dev->mem_props) अणु
		mem = container_of(dev->mem_props.next,
				काष्ठा kfd_mem_properties, list);
		list_del(&mem->list);
		kमुक्त(mem);
	पूर्ण

	जबतक (dev->cache_props.next != &dev->cache_props) अणु
		cache = container_of(dev->cache_props.next,
				काष्ठा kfd_cache_properties, list);
		list_del(&cache->list);
		kमुक्त(cache);
	पूर्ण

	जबतक (dev->io_link_props.next != &dev->io_link_props) अणु
		iolink = container_of(dev->io_link_props.next,
				काष्ठा kfd_iolink_properties, list);
		list_del(&iolink->list);
		kमुक्त(iolink);
	पूर्ण

	जबतक (dev->perf_props.next != &dev->perf_props) अणु
		perf = container_of(dev->perf_props.next,
				काष्ठा kfd_perf_properties, list);
		list_del(&perf->list);
		kमुक्त(perf);
	पूर्ण

	kमुक्त(dev);
पूर्ण

व्योम kfd_release_topology_device_list(काष्ठा list_head *device_list)
अणु
	काष्ठा kfd_topology_device *dev;

	जबतक (!list_empty(device_list)) अणु
		dev = list_first_entry(device_list,
				       काष्ठा kfd_topology_device, list);
		kfd_release_topology_device(dev);
	पूर्ण
पूर्ण

अटल व्योम kfd_release_live_view(व्योम)
अणु
	kfd_release_topology_device_list(&topology_device_list);
	स_रखो(&sys_props, 0, माप(sys_props));
पूर्ण

काष्ठा kfd_topology_device *kfd_create_topology_device(
				काष्ठा list_head *device_list)
अणु
	काष्ठा kfd_topology_device *dev;

	dev = kfd_alloc_काष्ठा(dev);
	अगर (!dev) अणु
		pr_err("No memory to allocate a topology device");
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&dev->mem_props);
	INIT_LIST_HEAD(&dev->cache_props);
	INIT_LIST_HEAD(&dev->io_link_props);
	INIT_LIST_HEAD(&dev->perf_props);

	list_add_tail(&dev->list, device_list);

	वापस dev;
पूर्ण


#घोषणा sysfs_show_gen_prop(buffer, offs, fmt, ...)		\
		(offs += snम_लिखो(buffer+offs, PAGE_SIZE-offs,	\
				  fmt, __VA_ARGS__))
#घोषणा sysfs_show_32bit_prop(buffer, offs, name, value) \
		sysfs_show_gen_prop(buffer, offs, "%s %u\n", name, value)
#घोषणा sysfs_show_64bit_prop(buffer, offs, name, value) \
		sysfs_show_gen_prop(buffer, offs, "%s %llu\n", name, value)
#घोषणा sysfs_show_32bit_val(buffer, offs, value) \
		sysfs_show_gen_prop(buffer, offs, "%u\n", value)
#घोषणा sysfs_show_str_val(buffer, offs, value) \
		sysfs_show_gen_prop(buffer, offs, "%s\n", value)

अटल sमाप_प्रकार sysprops_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		अक्षर *buffer)
अणु
	पूर्णांक offs = 0;

	/* Making sure that the buffer is an empty string */
	buffer[0] = 0;

	अगर (attr == &sys_props.attr_genid) अणु
		sysfs_show_32bit_val(buffer, offs,
				     sys_props.generation_count);
	पूर्ण अन्यथा अगर (attr == &sys_props.attr_props) अणु
		sysfs_show_64bit_prop(buffer, offs, "platform_oem",
				      sys_props.platक्रमm_oem);
		sysfs_show_64bit_prop(buffer, offs, "platform_id",
				      sys_props.platक्रमm_id);
		sysfs_show_64bit_prop(buffer, offs, "platform_rev",
				      sys_props.platक्रमm_rev);
	पूर्ण अन्यथा अणु
		offs = -EINVAL;
	पूर्ण

	वापस offs;
पूर्ण

अटल व्योम kfd_topology_kobj_release(काष्ठा kobject *kobj)
अणु
	kमुक्त(kobj);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops sysprops_ops = अणु
	.show = sysprops_show,
पूर्ण;

अटल काष्ठा kobj_type sysprops_type = अणु
	.release = kfd_topology_kobj_release,
	.sysfs_ops = &sysprops_ops,
पूर्ण;

अटल sमाप_प्रकार iolink_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		अक्षर *buffer)
अणु
	पूर्णांक offs = 0;
	काष्ठा kfd_iolink_properties *iolink;

	/* Making sure that the buffer is an empty string */
	buffer[0] = 0;

	iolink = container_of(attr, काष्ठा kfd_iolink_properties, attr);
	अगर (iolink->gpu && kfd_devcgroup_check_permission(iolink->gpu))
		वापस -EPERM;
	sysfs_show_32bit_prop(buffer, offs, "type", iolink->iolink_type);
	sysfs_show_32bit_prop(buffer, offs, "version_major", iolink->ver_maj);
	sysfs_show_32bit_prop(buffer, offs, "version_minor", iolink->ver_min);
	sysfs_show_32bit_prop(buffer, offs, "node_from", iolink->node_from);
	sysfs_show_32bit_prop(buffer, offs, "node_to", iolink->node_to);
	sysfs_show_32bit_prop(buffer, offs, "weight", iolink->weight);
	sysfs_show_32bit_prop(buffer, offs, "min_latency", iolink->min_latency);
	sysfs_show_32bit_prop(buffer, offs, "max_latency", iolink->max_latency);
	sysfs_show_32bit_prop(buffer, offs, "min_bandwidth",
			      iolink->min_bandwidth);
	sysfs_show_32bit_prop(buffer, offs, "max_bandwidth",
			      iolink->max_bandwidth);
	sysfs_show_32bit_prop(buffer, offs, "recommended_transfer_size",
			      iolink->rec_transfer_size);
	sysfs_show_32bit_prop(buffer, offs, "flags", iolink->flags);

	वापस offs;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops iolink_ops = अणु
	.show = iolink_show,
पूर्ण;

अटल काष्ठा kobj_type iolink_type = अणु
	.release = kfd_topology_kobj_release,
	.sysfs_ops = &iolink_ops,
पूर्ण;

अटल sमाप_प्रकार mem_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		अक्षर *buffer)
अणु
	पूर्णांक offs = 0;
	काष्ठा kfd_mem_properties *mem;

	/* Making sure that the buffer is an empty string */
	buffer[0] = 0;

	mem = container_of(attr, काष्ठा kfd_mem_properties, attr);
	अगर (mem->gpu && kfd_devcgroup_check_permission(mem->gpu))
		वापस -EPERM;
	sysfs_show_32bit_prop(buffer, offs, "heap_type", mem->heap_type);
	sysfs_show_64bit_prop(buffer, offs, "size_in_bytes",
			      mem->size_in_bytes);
	sysfs_show_32bit_prop(buffer, offs, "flags", mem->flags);
	sysfs_show_32bit_prop(buffer, offs, "width", mem->width);
	sysfs_show_32bit_prop(buffer, offs, "mem_clk_max",
			      mem->mem_clk_max);

	वापस offs;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops mem_ops = अणु
	.show = mem_show,
पूर्ण;

अटल काष्ठा kobj_type mem_type = अणु
	.release = kfd_topology_kobj_release,
	.sysfs_ops = &mem_ops,
पूर्ण;

अटल sमाप_प्रकार kfd_cache_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		अक्षर *buffer)
अणु
	पूर्णांक offs = 0;
	uपूर्णांक32_t i, j;
	काष्ठा kfd_cache_properties *cache;

	/* Making sure that the buffer is an empty string */
	buffer[0] = 0;

	cache = container_of(attr, काष्ठा kfd_cache_properties, attr);
	अगर (cache->gpu && kfd_devcgroup_check_permission(cache->gpu))
		वापस -EPERM;
	sysfs_show_32bit_prop(buffer, offs, "processor_id_low",
			cache->processor_id_low);
	sysfs_show_32bit_prop(buffer, offs, "level", cache->cache_level);
	sysfs_show_32bit_prop(buffer, offs, "size", cache->cache_size);
	sysfs_show_32bit_prop(buffer, offs, "cache_line_size",
			      cache->cacheline_size);
	sysfs_show_32bit_prop(buffer, offs, "cache_lines_per_tag",
			      cache->cachelines_per_tag);
	sysfs_show_32bit_prop(buffer, offs, "association", cache->cache_assoc);
	sysfs_show_32bit_prop(buffer, offs, "latency", cache->cache_latency);
	sysfs_show_32bit_prop(buffer, offs, "type", cache->cache_type);
	offs += snम_लिखो(buffer+offs, PAGE_SIZE-offs, "sibling_map ");
	क्रम (i = 0; i < CRAT_SIBLINGMAP_SIZE; i++)
		क्रम (j = 0; j < माप(cache->sibling_map[0])*8; j++)
			/* Check each bit */
			offs += snम_लिखो(buffer+offs, PAGE_SIZE-offs, "%d,",
					 (cache->sibling_map[i] >> j) & 1);

	/* Replace the last "," with end of line */
	buffer[offs-1] = '\n';
	वापस offs;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops cache_ops = अणु
	.show = kfd_cache_show,
पूर्ण;

अटल काष्ठा kobj_type cache_type = अणु
	.release = kfd_topology_kobj_release,
	.sysfs_ops = &cache_ops,
पूर्ण;

/****** Sysfs of Perक्रमmance Counters ******/

काष्ठा kfd_perf_attr अणु
	काष्ठा kobj_attribute attr;
	uपूर्णांक32_t data;
पूर्ण;

अटल sमाप_प्रकार perf_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attrs,
			अक्षर *buf)
अणु
	पूर्णांक offs = 0;
	काष्ठा kfd_perf_attr *attr;

	buf[0] = 0;
	attr = container_of(attrs, काष्ठा kfd_perf_attr, attr);
	अगर (!attr->data) /* invalid data क्रम PMC */
		वापस 0;
	अन्यथा
		वापस sysfs_show_32bit_val(buf, offs, attr->data);
पूर्ण

#घोषणा KFD_PERF_DESC(_name, _data)			\
अणु							\
	.attr  = __ATTR(_name, 0444, perf_show, शून्य),	\
	.data = _data,					\
पूर्ण

अटल काष्ठा kfd_perf_attr perf_attr_iommu[] = अणु
	KFD_PERF_DESC(max_concurrent, 0),
	KFD_PERF_DESC(num_counters, 0),
	KFD_PERF_DESC(counter_ids, 0),
पूर्ण;
/****************************************/

अटल sमाप_प्रकार node_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		अक्षर *buffer)
अणु
	पूर्णांक offs = 0;
	काष्ठा kfd_topology_device *dev;
	uपूर्णांक32_t log_max_watch_addr;

	/* Making sure that the buffer is an empty string */
	buffer[0] = 0;

	अगर (म_भेद(attr->name, "gpu_id") == 0) अणु
		dev = container_of(attr, काष्ठा kfd_topology_device,
				attr_gpuid);
		अगर (dev->gpu && kfd_devcgroup_check_permission(dev->gpu))
			वापस -EPERM;
		वापस sysfs_show_32bit_val(buffer, offs, dev->gpu_id);
	पूर्ण

	अगर (म_भेद(attr->name, "name") == 0) अणु
		dev = container_of(attr, काष्ठा kfd_topology_device,
				attr_name);

		अगर (dev->gpu && kfd_devcgroup_check_permission(dev->gpu))
			वापस -EPERM;
		वापस sysfs_show_str_val(buffer, offs, dev->node_props.name);
	पूर्ण

	dev = container_of(attr, काष्ठा kfd_topology_device,
			attr_props);
	अगर (dev->gpu && kfd_devcgroup_check_permission(dev->gpu))
		वापस -EPERM;
	sysfs_show_32bit_prop(buffer, offs, "cpu_cores_count",
			      dev->node_props.cpu_cores_count);
	sysfs_show_32bit_prop(buffer, offs, "simd_count",
			      dev->gpu ? dev->node_props.simd_count : 0);
	sysfs_show_32bit_prop(buffer, offs, "mem_banks_count",
			      dev->node_props.mem_banks_count);
	sysfs_show_32bit_prop(buffer, offs, "caches_count",
			      dev->node_props.caches_count);
	sysfs_show_32bit_prop(buffer, offs, "io_links_count",
			      dev->node_props.io_links_count);
	sysfs_show_32bit_prop(buffer, offs, "cpu_core_id_base",
			      dev->node_props.cpu_core_id_base);
	sysfs_show_32bit_prop(buffer, offs, "simd_id_base",
			      dev->node_props.simd_id_base);
	sysfs_show_32bit_prop(buffer, offs, "max_waves_per_simd",
			      dev->node_props.max_waves_per_simd);
	sysfs_show_32bit_prop(buffer, offs, "lds_size_in_kb",
			      dev->node_props.lds_size_in_kb);
	sysfs_show_32bit_prop(buffer, offs, "gds_size_in_kb",
			      dev->node_props.gds_size_in_kb);
	sysfs_show_32bit_prop(buffer, offs, "num_gws",
			      dev->node_props.num_gws);
	sysfs_show_32bit_prop(buffer, offs, "wave_front_size",
			      dev->node_props.wave_front_size);
	sysfs_show_32bit_prop(buffer, offs, "array_count",
			      dev->node_props.array_count);
	sysfs_show_32bit_prop(buffer, offs, "simd_arrays_per_engine",
			      dev->node_props.simd_arrays_per_engine);
	sysfs_show_32bit_prop(buffer, offs, "cu_per_simd_array",
			      dev->node_props.cu_per_simd_array);
	sysfs_show_32bit_prop(buffer, offs, "simd_per_cu",
			      dev->node_props.simd_per_cu);
	sysfs_show_32bit_prop(buffer, offs, "max_slots_scratch_cu",
			      dev->node_props.max_slots_scratch_cu);
	sysfs_show_32bit_prop(buffer, offs, "vendor_id",
			      dev->node_props.venकरोr_id);
	sysfs_show_32bit_prop(buffer, offs, "device_id",
			      dev->node_props.device_id);
	sysfs_show_32bit_prop(buffer, offs, "location_id",
			      dev->node_props.location_id);
	sysfs_show_32bit_prop(buffer, offs, "domain",
			      dev->node_props.करोमुख्य);
	sysfs_show_32bit_prop(buffer, offs, "drm_render_minor",
			      dev->node_props.drm_render_minor);
	sysfs_show_64bit_prop(buffer, offs, "hive_id",
			      dev->node_props.hive_id);
	sysfs_show_32bit_prop(buffer, offs, "num_sdma_engines",
			      dev->node_props.num_sdma_engines);
	sysfs_show_32bit_prop(buffer, offs, "num_sdma_xgmi_engines",
			      dev->node_props.num_sdma_xgmi_engines);
	sysfs_show_32bit_prop(buffer, offs, "num_sdma_queues_per_engine",
			      dev->node_props.num_sdma_queues_per_engine);
	sysfs_show_32bit_prop(buffer, offs, "num_cp_queues",
			      dev->node_props.num_cp_queues);

	अगर (dev->gpu) अणु
		log_max_watch_addr =
			__ilog2_u32(dev->gpu->device_info->num_of_watch_poपूर्णांकs);

		अगर (log_max_watch_addr) अणु
			dev->node_props.capability |=
					HSA_CAP_WATCH_POINTS_SUPPORTED;

			dev->node_props.capability |=
				((log_max_watch_addr <<
					HSA_CAP_WATCH_POINTS_TOTALBITS_SHIFT) &
				HSA_CAP_WATCH_POINTS_TOTALBITS_MASK);
		पूर्ण

		अगर (dev->gpu->device_info->asic_family == CHIP_TONGA)
			dev->node_props.capability |=
					HSA_CAP_AQL_QUEUE_DOUBLE_MAP;

		sysfs_show_32bit_prop(buffer, offs, "max_engine_clk_fcompute",
			dev->node_props.max_engine_clk_fcompute);

		sysfs_show_64bit_prop(buffer, offs, "local_mem_size", 0ULL);

		sysfs_show_32bit_prop(buffer, offs, "fw_version",
				      dev->gpu->mec_fw_version);
		sysfs_show_32bit_prop(buffer, offs, "capability",
				      dev->node_props.capability);
		sysfs_show_32bit_prop(buffer, offs, "sdma_fw_version",
				      dev->gpu->sdma_fw_version);
		sysfs_show_64bit_prop(buffer, offs, "unique_id",
				      amdgpu_amdkfd_get_unique_id(dev->gpu->kgd));

	पूर्ण

	वापस sysfs_show_32bit_prop(buffer, offs, "max_engine_clk_ccompute",
				     cpufreq_quick_get_max(0)/1000);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops node_ops = अणु
	.show = node_show,
पूर्ण;

अटल काष्ठा kobj_type node_type = अणु
	.release = kfd_topology_kobj_release,
	.sysfs_ops = &node_ops,
पूर्ण;

अटल व्योम kfd_हटाओ_sysfs_file(काष्ठा kobject *kobj, काष्ठा attribute *attr)
अणु
	sysfs_हटाओ_file(kobj, attr);
	kobject_del(kobj);
	kobject_put(kobj);
पूर्ण

अटल व्योम kfd_हटाओ_sysfs_node_entry(काष्ठा kfd_topology_device *dev)
अणु
	काष्ठा kfd_iolink_properties *iolink;
	काष्ठा kfd_cache_properties *cache;
	काष्ठा kfd_mem_properties *mem;
	काष्ठा kfd_perf_properties *perf;

	अगर (dev->kobj_iolink) अणु
		list_क्रम_each_entry(iolink, &dev->io_link_props, list)
			अगर (iolink->kobj) अणु
				kfd_हटाओ_sysfs_file(iolink->kobj,
							&iolink->attr);
				iolink->kobj = शून्य;
			पूर्ण
		kobject_del(dev->kobj_iolink);
		kobject_put(dev->kobj_iolink);
		dev->kobj_iolink = शून्य;
	पूर्ण

	अगर (dev->kobj_cache) अणु
		list_क्रम_each_entry(cache, &dev->cache_props, list)
			अगर (cache->kobj) अणु
				kfd_हटाओ_sysfs_file(cache->kobj,
							&cache->attr);
				cache->kobj = शून्य;
			पूर्ण
		kobject_del(dev->kobj_cache);
		kobject_put(dev->kobj_cache);
		dev->kobj_cache = शून्य;
	पूर्ण

	अगर (dev->kobj_mem) अणु
		list_क्रम_each_entry(mem, &dev->mem_props, list)
			अगर (mem->kobj) अणु
				kfd_हटाओ_sysfs_file(mem->kobj, &mem->attr);
				mem->kobj = शून्य;
			पूर्ण
		kobject_del(dev->kobj_mem);
		kobject_put(dev->kobj_mem);
		dev->kobj_mem = शून्य;
	पूर्ण

	अगर (dev->kobj_perf) अणु
		list_क्रम_each_entry(perf, &dev->perf_props, list) अणु
			kमुक्त(perf->attr_group);
			perf->attr_group = शून्य;
		पूर्ण
		kobject_del(dev->kobj_perf);
		kobject_put(dev->kobj_perf);
		dev->kobj_perf = शून्य;
	पूर्ण

	अगर (dev->kobj_node) अणु
		sysfs_हटाओ_file(dev->kobj_node, &dev->attr_gpuid);
		sysfs_हटाओ_file(dev->kobj_node, &dev->attr_name);
		sysfs_हटाओ_file(dev->kobj_node, &dev->attr_props);
		kobject_del(dev->kobj_node);
		kobject_put(dev->kobj_node);
		dev->kobj_node = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक kfd_build_sysfs_node_entry(काष्ठा kfd_topology_device *dev,
		uपूर्णांक32_t id)
अणु
	काष्ठा kfd_iolink_properties *iolink;
	काष्ठा kfd_cache_properties *cache;
	काष्ठा kfd_mem_properties *mem;
	काष्ठा kfd_perf_properties *perf;
	पूर्णांक ret;
	uपूर्णांक32_t i, num_attrs;
	काष्ठा attribute **attrs;

	अगर (WARN_ON(dev->kobj_node))
		वापस -EEXIST;

	/*
	 * Creating the sysfs folders
	 */
	dev->kobj_node = kfd_alloc_काष्ठा(dev->kobj_node);
	अगर (!dev->kobj_node)
		वापस -ENOMEM;

	ret = kobject_init_and_add(dev->kobj_node, &node_type,
			sys_props.kobj_nodes, "%d", id);
	अगर (ret < 0) अणु
		kobject_put(dev->kobj_node);
		वापस ret;
	पूर्ण

	dev->kobj_mem = kobject_create_and_add("mem_banks", dev->kobj_node);
	अगर (!dev->kobj_mem)
		वापस -ENOMEM;

	dev->kobj_cache = kobject_create_and_add("caches", dev->kobj_node);
	अगर (!dev->kobj_cache)
		वापस -ENOMEM;

	dev->kobj_iolink = kobject_create_and_add("io_links", dev->kobj_node);
	अगर (!dev->kobj_iolink)
		वापस -ENOMEM;

	dev->kobj_perf = kobject_create_and_add("perf", dev->kobj_node);
	अगर (!dev->kobj_perf)
		वापस -ENOMEM;

	/*
	 * Creating sysfs files क्रम node properties
	 */
	dev->attr_gpuid.name = "gpu_id";
	dev->attr_gpuid.mode = KFD_SYSFS_खाता_MODE;
	sysfs_attr_init(&dev->attr_gpuid);
	dev->attr_name.name = "name";
	dev->attr_name.mode = KFD_SYSFS_खाता_MODE;
	sysfs_attr_init(&dev->attr_name);
	dev->attr_props.name = "properties";
	dev->attr_props.mode = KFD_SYSFS_खाता_MODE;
	sysfs_attr_init(&dev->attr_props);
	ret = sysfs_create_file(dev->kobj_node, &dev->attr_gpuid);
	अगर (ret < 0)
		वापस ret;
	ret = sysfs_create_file(dev->kobj_node, &dev->attr_name);
	अगर (ret < 0)
		वापस ret;
	ret = sysfs_create_file(dev->kobj_node, &dev->attr_props);
	अगर (ret < 0)
		वापस ret;

	i = 0;
	list_क्रम_each_entry(mem, &dev->mem_props, list) अणु
		mem->kobj = kzalloc(माप(काष्ठा kobject), GFP_KERNEL);
		अगर (!mem->kobj)
			वापस -ENOMEM;
		ret = kobject_init_and_add(mem->kobj, &mem_type,
				dev->kobj_mem, "%d", i);
		अगर (ret < 0) अणु
			kobject_put(mem->kobj);
			वापस ret;
		पूर्ण

		mem->attr.name = "properties";
		mem->attr.mode = KFD_SYSFS_खाता_MODE;
		sysfs_attr_init(&mem->attr);
		ret = sysfs_create_file(mem->kobj, &mem->attr);
		अगर (ret < 0)
			वापस ret;
		i++;
	पूर्ण

	i = 0;
	list_क्रम_each_entry(cache, &dev->cache_props, list) अणु
		cache->kobj = kzalloc(माप(काष्ठा kobject), GFP_KERNEL);
		अगर (!cache->kobj)
			वापस -ENOMEM;
		ret = kobject_init_and_add(cache->kobj, &cache_type,
				dev->kobj_cache, "%d", i);
		अगर (ret < 0) अणु
			kobject_put(cache->kobj);
			वापस ret;
		पूर्ण

		cache->attr.name = "properties";
		cache->attr.mode = KFD_SYSFS_खाता_MODE;
		sysfs_attr_init(&cache->attr);
		ret = sysfs_create_file(cache->kobj, &cache->attr);
		अगर (ret < 0)
			वापस ret;
		i++;
	पूर्ण

	i = 0;
	list_क्रम_each_entry(iolink, &dev->io_link_props, list) अणु
		iolink->kobj = kzalloc(माप(काष्ठा kobject), GFP_KERNEL);
		अगर (!iolink->kobj)
			वापस -ENOMEM;
		ret = kobject_init_and_add(iolink->kobj, &iolink_type,
				dev->kobj_iolink, "%d", i);
		अगर (ret < 0) अणु
			kobject_put(iolink->kobj);
			वापस ret;
		पूर्ण

		iolink->attr.name = "properties";
		iolink->attr.mode = KFD_SYSFS_खाता_MODE;
		sysfs_attr_init(&iolink->attr);
		ret = sysfs_create_file(iolink->kobj, &iolink->attr);
		अगर (ret < 0)
			वापस ret;
		i++;
	पूर्ण

	/* All hardware blocks have the same number of attributes. */
	num_attrs = ARRAY_SIZE(perf_attr_iommu);
	list_क्रम_each_entry(perf, &dev->perf_props, list) अणु
		perf->attr_group = kzalloc(माप(काष्ठा kfd_perf_attr)
			* num_attrs + माप(काष्ठा attribute_group),
			GFP_KERNEL);
		अगर (!perf->attr_group)
			वापस -ENOMEM;

		attrs = (काष्ठा attribute **)(perf->attr_group + 1);
		अगर (!म_भेद(perf->block_name, "iommu")) अणु
		/* Inक्रमmation of IOMMU's num_counters and counter_ids is shown
		 * under /sys/bus/event_source/devices/amd_iommu. We करोn't
		 * duplicate here.
		 */
			perf_attr_iommu[0].data = perf->max_concurrent;
			क्रम (i = 0; i < num_attrs; i++)
				attrs[i] = &perf_attr_iommu[i].attr.attr;
		पूर्ण
		perf->attr_group->name = perf->block_name;
		perf->attr_group->attrs = attrs;
		ret = sysfs_create_group(dev->kobj_perf, perf->attr_group);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Called with ग_लिखो topology lock acquired */
अटल पूर्णांक kfd_build_sysfs_node_tree(व्योम)
अणु
	काष्ठा kfd_topology_device *dev;
	पूर्णांक ret;
	uपूर्णांक32_t i = 0;

	list_क्रम_each_entry(dev, &topology_device_list, list) अणु
		ret = kfd_build_sysfs_node_entry(dev, i);
		अगर (ret < 0)
			वापस ret;
		i++;
	पूर्ण

	वापस 0;
पूर्ण

/* Called with ग_लिखो topology lock acquired */
अटल व्योम kfd_हटाओ_sysfs_node_tree(व्योम)
अणु
	काष्ठा kfd_topology_device *dev;

	list_क्रम_each_entry(dev, &topology_device_list, list)
		kfd_हटाओ_sysfs_node_entry(dev);
पूर्ण

अटल पूर्णांक kfd_topology_update_sysfs(व्योम)
अणु
	पूर्णांक ret;

	अगर (!sys_props.kobj_topology) अणु
		sys_props.kobj_topology =
				kfd_alloc_काष्ठा(sys_props.kobj_topology);
		अगर (!sys_props.kobj_topology)
			वापस -ENOMEM;

		ret = kobject_init_and_add(sys_props.kobj_topology,
				&sysprops_type,  &kfd_device->kobj,
				"topology");
		अगर (ret < 0) अणु
			kobject_put(sys_props.kobj_topology);
			वापस ret;
		पूर्ण

		sys_props.kobj_nodes = kobject_create_and_add("nodes",
				sys_props.kobj_topology);
		अगर (!sys_props.kobj_nodes)
			वापस -ENOMEM;

		sys_props.attr_genid.name = "generation_id";
		sys_props.attr_genid.mode = KFD_SYSFS_खाता_MODE;
		sysfs_attr_init(&sys_props.attr_genid);
		ret = sysfs_create_file(sys_props.kobj_topology,
				&sys_props.attr_genid);
		अगर (ret < 0)
			वापस ret;

		sys_props.attr_props.name = "system_properties";
		sys_props.attr_props.mode = KFD_SYSFS_खाता_MODE;
		sysfs_attr_init(&sys_props.attr_props);
		ret = sysfs_create_file(sys_props.kobj_topology,
				&sys_props.attr_props);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	kfd_हटाओ_sysfs_node_tree();

	वापस kfd_build_sysfs_node_tree();
पूर्ण

अटल व्योम kfd_topology_release_sysfs(व्योम)
अणु
	kfd_हटाओ_sysfs_node_tree();
	अगर (sys_props.kobj_topology) अणु
		sysfs_हटाओ_file(sys_props.kobj_topology,
				&sys_props.attr_genid);
		sysfs_हटाओ_file(sys_props.kobj_topology,
				&sys_props.attr_props);
		अगर (sys_props.kobj_nodes) अणु
			kobject_del(sys_props.kobj_nodes);
			kobject_put(sys_props.kobj_nodes);
			sys_props.kobj_nodes = शून्य;
		पूर्ण
		kobject_del(sys_props.kobj_topology);
		kobject_put(sys_props.kobj_topology);
		sys_props.kobj_topology = शून्य;
	पूर्ण
पूर्ण

/* Called with ग_लिखो topology_lock acquired */
अटल व्योम kfd_topology_update_device_list(काष्ठा list_head *temp_list,
					काष्ठा list_head *master_list)
अणु
	जबतक (!list_empty(temp_list)) अणु
		list_move_tail(temp_list->next, master_list);
		sys_props.num_devices++;
	पूर्ण
पूर्ण

अटल व्योम kfd_debug_prपूर्णांक_topology(व्योम)
अणु
	काष्ठा kfd_topology_device *dev;

	करोwn_पढ़ो(&topology_lock);

	dev = list_last_entry(&topology_device_list,
			काष्ठा kfd_topology_device, list);
	अगर (dev) अणु
		अगर (dev->node_props.cpu_cores_count &&
				dev->node_props.simd_count) अणु
			pr_info("Topology: Add APU node [0x%0x:0x%0x]\n",
				dev->node_props.device_id,
				dev->node_props.venकरोr_id);
		पूर्ण अन्यथा अगर (dev->node_props.cpu_cores_count)
			pr_info("Topology: Add CPU node\n");
		अन्यथा अगर (dev->node_props.simd_count)
			pr_info("Topology: Add dGPU node [0x%0x:0x%0x]\n",
				dev->node_props.device_id,
				dev->node_props.venकरोr_id);
	पूर्ण
	up_पढ़ो(&topology_lock);
पूर्ण

/* Helper function क्रम पूर्णांकializing platक्रमm_xx members of
 * kfd_प्रणाली_properties. Uses OEM info from the last CPU/APU node.
 */
अटल व्योम kfd_update_प्रणाली_properties(व्योम)
अणु
	काष्ठा kfd_topology_device *dev;

	करोwn_पढ़ो(&topology_lock);
	dev = list_last_entry(&topology_device_list,
			काष्ठा kfd_topology_device, list);
	अगर (dev) अणु
		sys_props.platक्रमm_id =
			(*((uपूर्णांक64_t *)dev->oem_id)) & CRAT_OEMID_64BIT_MASK;
		sys_props.platक्रमm_oem = *((uपूर्णांक64_t *)dev->oem_table_id);
		sys_props.platक्रमm_rev = dev->oem_revision;
	पूर्ण
	up_पढ़ो(&topology_lock);
पूर्ण

अटल व्योम find_प्रणाली_memory(स्थिर काष्ठा dmi_header *dm,
	व्योम *निजी)
अणु
	काष्ठा kfd_mem_properties *mem;
	u16 mem_width, mem_घड़ी;
	काष्ठा kfd_topology_device *kdev =
		(काष्ठा kfd_topology_device *)निजी;
	स्थिर u8 *dmi_data = (स्थिर u8 *)(dm + 1);

	अगर (dm->type == DMI_ENTRY_MEM_DEVICE && dm->length >= 0x15) अणु
		mem_width = (u16)(*(स्थिर u16 *)(dmi_data + 0x6));
		mem_घड़ी = (u16)(*(स्थिर u16 *)(dmi_data + 0x11));
		list_क्रम_each_entry(mem, &kdev->mem_props, list) अणु
			अगर (mem_width != 0xFFFF && mem_width != 0)
				mem->width = mem_width;
			अगर (mem_घड़ी != 0)
				mem->mem_clk_max = mem_घड़ी;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Perक्रमmance counters inक्रमmation is not part of CRAT but we would like to
 * put them in the sysfs under topology directory क्रम Thunk to get the data.
 * This function is called beक्रमe updating the sysfs.
 */
अटल पूर्णांक kfd_add_perf_to_topology(काष्ठा kfd_topology_device *kdev)
अणु
	/* These are the only counters supported so far */
	वापस kfd_iommu_add_perf_counters(kdev);
पूर्ण

/* kfd_add_non_crat_inक्रमmation - Add inक्रमmation that is not currently
 *	defined in CRAT but is necessary क्रम KFD topology
 * @dev - topology device to which addition info is added
 */
अटल व्योम kfd_add_non_crat_inक्रमmation(काष्ठा kfd_topology_device *kdev)
अणु
	/* Check अगर CPU only node. */
	अगर (!kdev->gpu) अणु
		/* Add प्रणाली memory inक्रमmation */
		dmi_walk(find_प्रणाली_memory, kdev);
	पूर्ण
	/* TODO: For GPU node, rearrange code from kfd_topology_add_device */
पूर्ण

/* kfd_is_acpi_crat_invalid - CRAT from ACPI is valid only क्रम AMD APU devices.
 *	Ignore CRAT क्रम all other devices. AMD APU is identअगरied अगर both CPU
 *	and GPU cores are present.
 * @device_list - topology device list created by parsing ACPI CRAT table.
 * @वापस - TRUE अगर invalid, FALSE is valid.
 */
अटल bool kfd_is_acpi_crat_invalid(काष्ठा list_head *device_list)
अणु
	काष्ठा kfd_topology_device *dev;

	list_क्रम_each_entry(dev, device_list, list) अणु
		अगर (dev->node_props.cpu_cores_count &&
			dev->node_props.simd_count)
			वापस false;
	पूर्ण
	pr_info("Ignoring ACPI CRAT on non-APU system\n");
	वापस true;
पूर्ण

पूर्णांक kfd_topology_init(व्योम)
अणु
	व्योम *crat_image = शून्य;
	माप_प्रकार image_size = 0;
	पूर्णांक ret;
	काष्ठा list_head temp_topology_device_list;
	पूर्णांक cpu_only_node = 0;
	काष्ठा kfd_topology_device *kdev;
	पूर्णांक proximity_करोमुख्य;

	/* topology_device_list - Master list of all topology devices
	 * temp_topology_device_list - temporary list created जबतक parsing CRAT
	 * or VCRAT. Once parsing is complete the contents of list is moved to
	 * topology_device_list
	 */

	/* Initialize the head क्रम the both the lists */
	INIT_LIST_HEAD(&topology_device_list);
	INIT_LIST_HEAD(&temp_topology_device_list);
	init_rwsem(&topology_lock);

	स_रखो(&sys_props, 0, माप(sys_props));

	/* Proximity करोमुख्यs in ACPI CRAT tables start counting at
	 * 0. The same should be true क्रम भव CRAT tables created
	 * at this stage. GPUs added later in kfd_topology_add_device
	 * use a counter.
	 */
	proximity_करोमुख्य = 0;

	/*
	 * Get the CRAT image from the ACPI. If ACPI करोesn't have one
	 * or अगर ACPI CRAT is invalid create a भव CRAT.
	 * NOTE: The current implementation expects all AMD APUs to have
	 *	CRAT. If no CRAT is available, it is assumed to be a CPU
	 */
	ret = kfd_create_crat_image_acpi(&crat_image, &image_size);
	अगर (!ret) अणु
		ret = kfd_parse_crat_table(crat_image,
					   &temp_topology_device_list,
					   proximity_करोमुख्य);
		अगर (ret ||
		    kfd_is_acpi_crat_invalid(&temp_topology_device_list)) अणु
			kfd_release_topology_device_list(
				&temp_topology_device_list);
			kfd_destroy_crat_image(crat_image);
			crat_image = शून्य;
		पूर्ण
	पूर्ण

	अगर (!crat_image) अणु
		ret = kfd_create_crat_image_भव(&crat_image, &image_size,
						    COMPUTE_UNIT_CPU, शून्य,
						    proximity_करोमुख्य);
		cpu_only_node = 1;
		अगर (ret) अणु
			pr_err("Error creating VCRAT table for CPU\n");
			वापस ret;
		पूर्ण

		ret = kfd_parse_crat_table(crat_image,
					   &temp_topology_device_list,
					   proximity_करोमुख्य);
		अगर (ret) अणु
			pr_err("Error parsing VCRAT table for CPU\n");
			जाओ err;
		पूर्ण
	पूर्ण

	kdev = list_first_entry(&temp_topology_device_list,
				काष्ठा kfd_topology_device, list);
	kfd_add_perf_to_topology(kdev);

	करोwn_ग_लिखो(&topology_lock);
	kfd_topology_update_device_list(&temp_topology_device_list,
					&topology_device_list);
	atomic_set(&topology_crat_proximity_करोमुख्य, sys_props.num_devices-1);
	ret = kfd_topology_update_sysfs();
	up_ग_लिखो(&topology_lock);

	अगर (!ret) अणु
		sys_props.generation_count++;
		kfd_update_प्रणाली_properties();
		kfd_debug_prपूर्णांक_topology();
	पूर्ण अन्यथा
		pr_err("Failed to update topology in sysfs ret=%d\n", ret);

	/* For nodes with GPU, this inक्रमmation माला_लो added
	 * when GPU is detected (kfd_topology_add_device).
	 */
	अगर (cpu_only_node) अणु
		/* Add additional inक्रमmation to CPU only node created above */
		करोwn_ग_लिखो(&topology_lock);
		kdev = list_first_entry(&topology_device_list,
				काष्ठा kfd_topology_device, list);
		up_ग_लिखो(&topology_lock);
		kfd_add_non_crat_inक्रमmation(kdev);
	पूर्ण

err:
	kfd_destroy_crat_image(crat_image);
	वापस ret;
पूर्ण

व्योम kfd_topology_shutकरोwn(व्योम)
अणु
	करोwn_ग_लिखो(&topology_lock);
	kfd_topology_release_sysfs();
	kfd_release_live_view();
	up_ग_लिखो(&topology_lock);
पूर्ण

अटल uपूर्णांक32_t kfd_generate_gpu_id(काष्ठा kfd_dev *gpu)
अणु
	uपूर्णांक32_t hashout;
	uपूर्णांक32_t buf[7];
	uपूर्णांक64_t local_mem_size;
	पूर्णांक i;
	काष्ठा kfd_local_mem_info local_mem_info;

	अगर (!gpu)
		वापस 0;

	amdgpu_amdkfd_get_local_mem_info(gpu->kgd, &local_mem_info);

	local_mem_size = local_mem_info.local_mem_size_निजी +
			local_mem_info.local_mem_size_खुला;

	buf[0] = gpu->pdev->devfn;
	buf[1] = gpu->pdev->subप्रणाली_venकरोr |
		(gpu->pdev->subप्रणाली_device << 16);
	buf[2] = pci_करोमुख्य_nr(gpu->pdev->bus);
	buf[3] = gpu->pdev->device;
	buf[4] = gpu->pdev->bus->number;
	buf[5] = lower_32_bits(local_mem_size);
	buf[6] = upper_32_bits(local_mem_size);

	क्रम (i = 0, hashout = 0; i < 7; i++)
		hashout ^= hash_32(buf[i], KFD_GPU_ID_HASH_WIDTH);

	वापस hashout;
पूर्ण
/* kfd_assign_gpu - Attach @gpu to the correct kfd topology device. If
 *		the GPU device is not alपढ़ोy present in the topology device
 *		list then वापस शून्य. This means a new topology device has to
 *		be created क्रम this GPU.
 */
अटल काष्ठा kfd_topology_device *kfd_assign_gpu(काष्ठा kfd_dev *gpu)
अणु
	काष्ठा kfd_topology_device *dev;
	काष्ठा kfd_topology_device *out_dev = शून्य;
	काष्ठा kfd_mem_properties *mem;
	काष्ठा kfd_cache_properties *cache;
	काष्ठा kfd_iolink_properties *iolink;

	करोwn_ग_लिखो(&topology_lock);
	list_क्रम_each_entry(dev, &topology_device_list, list) अणु
		/* Discrete GPUs need their own topology device list
		 * entries. Don't assign them to CPU/APU nodes.
		 */
		अगर (!gpu->use_iommu_v2 &&
		    dev->node_props.cpu_cores_count)
			जारी;

		अगर (!dev->gpu && (dev->node_props.simd_count > 0)) अणु
			dev->gpu = gpu;
			out_dev = dev;

			list_क्रम_each_entry(mem, &dev->mem_props, list)
				mem->gpu = dev->gpu;
			list_क्रम_each_entry(cache, &dev->cache_props, list)
				cache->gpu = dev->gpu;
			list_क्रम_each_entry(iolink, &dev->io_link_props, list)
				iolink->gpu = dev->gpu;
			अवरोध;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&topology_lock);
	वापस out_dev;
पूर्ण

अटल व्योम kfd_notअगरy_gpu_change(uपूर्णांक32_t gpu_id, पूर्णांक arrival)
अणु
	/*
	 * TODO: Generate an event क्रम thunk about the arrival/removal
	 * of the GPU
	 */
पूर्ण

/* kfd_fill_mem_clk_max_info - Since CRAT करोesn't have memory घड़ी info,
 *		patch this after CRAT parsing.
 */
अटल व्योम kfd_fill_mem_clk_max_info(काष्ठा kfd_topology_device *dev)
अणु
	काष्ठा kfd_mem_properties *mem;
	काष्ठा kfd_local_mem_info local_mem_info;

	अगर (!dev)
		वापस;

	/* Currently, amdgpu driver (amdgpu_mc) deals only with GPUs with
	 * single bank of VRAM local memory.
	 * क्रम dGPUs - VCRAT reports only one bank of Local Memory
	 * क्रम APUs - If CRAT from ACPI reports more than one bank, then
	 *	all the banks will report the same mem_clk_max inक्रमmation
	 */
	amdgpu_amdkfd_get_local_mem_info(dev->gpu->kgd, &local_mem_info);

	list_क्रम_each_entry(mem, &dev->mem_props, list)
		mem->mem_clk_max = local_mem_info.mem_clk_max;
पूर्ण

अटल व्योम kfd_fill_iolink_non_crat_info(काष्ठा kfd_topology_device *dev)
अणु
	काष्ठा kfd_iolink_properties *link, *cpu_link;
	काष्ठा kfd_topology_device *cpu_dev;
	uपूर्णांक32_t cap;
	uपूर्णांक32_t cpu_flag = CRAT_IOLINK_FLAGS_ENABLED;
	uपूर्णांक32_t flag = CRAT_IOLINK_FLAGS_ENABLED;

	अगर (!dev || !dev->gpu)
		वापस;

	pcie_capability_पढ़ो_dword(dev->gpu->pdev,
			PCI_EXP_DEVCAP2, &cap);

	अगर (!(cap & (PCI_EXP_DEVCAP2_ATOMIC_COMP32 |
		     PCI_EXP_DEVCAP2_ATOMIC_COMP64)))
		cpu_flag |= CRAT_IOLINK_FLAGS_NO_ATOMICS_32_BIT |
			CRAT_IOLINK_FLAGS_NO_ATOMICS_64_BIT;

	अगर (!dev->gpu->pci_atomic_requested ||
	    dev->gpu->device_info->asic_family == CHIP_HAWAII)
		flag |= CRAT_IOLINK_FLAGS_NO_ATOMICS_32_BIT |
			CRAT_IOLINK_FLAGS_NO_ATOMICS_64_BIT;

	/* GPU only creates direct links so apply flags setting to all */
	list_क्रम_each_entry(link, &dev->io_link_props, list) अणु
		link->flags = flag;
		cpu_dev = kfd_topology_device_by_proximity_करोमुख्य(
				link->node_to);
		अगर (cpu_dev) अणु
			list_क्रम_each_entry(cpu_link,
					    &cpu_dev->io_link_props, list)
				अगर (cpu_link->node_to == link->node_from)
					cpu_link->flags = cpu_flag;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक kfd_topology_add_device(काष्ठा kfd_dev *gpu)
अणु
	uपूर्णांक32_t gpu_id;
	काष्ठा kfd_topology_device *dev;
	काष्ठा kfd_cu_info cu_info;
	पूर्णांक res = 0;
	काष्ठा list_head temp_topology_device_list;
	व्योम *crat_image = शून्य;
	माप_प्रकार image_size = 0;
	पूर्णांक proximity_करोमुख्य;
	काष्ठा amdgpu_device *adev;

	INIT_LIST_HEAD(&temp_topology_device_list);

	gpu_id = kfd_generate_gpu_id(gpu);

	pr_debug("Adding new GPU (ID: 0x%x) to topology\n", gpu_id);

	proximity_करोमुख्य = atomic_inc_वापस(&topology_crat_proximity_करोमुख्य);

	/* Check to see अगर this gpu device exists in the topology_device_list.
	 * If so, assign the gpu to that device,
	 * अन्यथा create a Virtual CRAT क्रम this gpu device and then parse that
	 * CRAT to create a new topology device. Once created assign the gpu to
	 * that topology device
	 */
	dev = kfd_assign_gpu(gpu);
	अगर (!dev) अणु
		res = kfd_create_crat_image_भव(&crat_image, &image_size,
						    COMPUTE_UNIT_GPU, gpu,
						    proximity_करोमुख्य);
		अगर (res) अणु
			pr_err("Error creating VCRAT for GPU (ID: 0x%x)\n",
			       gpu_id);
			वापस res;
		पूर्ण
		res = kfd_parse_crat_table(crat_image,
					   &temp_topology_device_list,
					   proximity_करोमुख्य);
		अगर (res) अणु
			pr_err("Error parsing VCRAT for GPU (ID: 0x%x)\n",
			       gpu_id);
			जाओ err;
		पूर्ण

		करोwn_ग_लिखो(&topology_lock);
		kfd_topology_update_device_list(&temp_topology_device_list,
			&topology_device_list);

		/* Update the SYSFS tree, since we added another topology
		 * device
		 */
		res = kfd_topology_update_sysfs();
		up_ग_लिखो(&topology_lock);

		अगर (!res)
			sys_props.generation_count++;
		अन्यथा
			pr_err("Failed to update GPU (ID: 0x%x) to sysfs topology. res=%d\n",
						gpu_id, res);
		dev = kfd_assign_gpu(gpu);
		अगर (WARN_ON(!dev)) अणु
			res = -ENODEV;
			जाओ err;
		पूर्ण
	पूर्ण

	dev->gpu_id = gpu_id;
	gpu->id = gpu_id;

	/* TODO: Move the following lines to function
	 *	kfd_add_non_crat_inक्रमmation
	 */

	/* Fill-in additional inक्रमmation that is not available in CRAT but
	 * needed क्रम the topology
	 */

	amdgpu_amdkfd_get_cu_info(dev->gpu->kgd, &cu_info);

	म_नकलन(dev->node_props.name, gpu->device_info->asic_name,
			KFD_TOPOLOGY_PUBLIC_NAME_SIZE);

	dev->node_props.simd_arrays_per_engine =
		cu_info.num_shader_arrays_per_engine;

	dev->node_props.venकरोr_id = gpu->pdev->venकरोr;
	dev->node_props.device_id = gpu->pdev->device;
	dev->node_props.capability |=
		((amdgpu_amdkfd_get_asic_rev_id(dev->gpu->kgd) <<
			HSA_CAP_ASIC_REVISION_SHIFT) &
			HSA_CAP_ASIC_REVISION_MASK);
	dev->node_props.location_id = pci_dev_id(gpu->pdev);
	dev->node_props.करोमुख्य = pci_करोमुख्य_nr(gpu->pdev->bus);
	dev->node_props.max_engine_clk_fcompute =
		amdgpu_amdkfd_get_max_engine_घड़ी_in_mhz(dev->gpu->kgd);
	dev->node_props.max_engine_clk_ccompute =
		cpufreq_quick_get_max(0) / 1000;
	dev->node_props.drm_render_minor =
		gpu->shared_resources.drm_render_minor;

	dev->node_props.hive_id = gpu->hive_id;
	dev->node_props.num_sdma_engines = gpu->device_info->num_sdma_engines;
	dev->node_props.num_sdma_xgmi_engines =
				gpu->device_info->num_xgmi_sdma_engines;
	dev->node_props.num_sdma_queues_per_engine =
				gpu->device_info->num_sdma_queues_per_engine;
	dev->node_props.num_gws = (dev->gpu->gws &&
		dev->gpu->dqm->sched_policy != KFD_SCHED_POLICY_NO_HWS) ?
		amdgpu_amdkfd_get_num_gws(dev->gpu->kgd) : 0;
	dev->node_props.num_cp_queues = get_cp_queues_num(dev->gpu->dqm);

	kfd_fill_mem_clk_max_info(dev);
	kfd_fill_iolink_non_crat_info(dev);

	चयन (dev->gpu->device_info->asic_family) अणु
	हाल CHIP_KAVERI:
	हाल CHIP_HAWAII:
	हाल CHIP_TONGA:
		dev->node_props.capability |= ((HSA_CAP_DOORBELL_TYPE_PRE_1_0 <<
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_SHIFT) &
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_MASK);
		अवरोध;
	हाल CHIP_CARRIZO:
	हाल CHIP_FIJI:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		pr_debug("Adding doorbell packet type capability\n");
		dev->node_props.capability |= ((HSA_CAP_DOORBELL_TYPE_1_0 <<
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_SHIFT) &
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_MASK);
		अवरोध;
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
	हाल CHIP_RAVEN:
	हाल CHIP_RENOIR:
	हाल CHIP_ARCTURUS:
	हाल CHIP_ALDEBARAN:
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI12:
	हाल CHIP_NAVI14:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_VANGOGH:
	हाल CHIP_DIMGREY_CAVEFISH:
		dev->node_props.capability |= ((HSA_CAP_DOORBELL_TYPE_2_0 <<
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_SHIFT) &
			HSA_CAP_DOORBELL_TYPE_TOTALBITS_MASK);
		अवरोध;
	शेष:
		WARN(1, "Unexpected ASIC family %u",
		     dev->gpu->device_info->asic_family);
	पूर्ण

	/*
	* Overग_लिखो ATS capability according to needs_iommu_device to fix
	* potential missing corresponding bit in CRAT of BIOS.
	*/
	अगर (dev->gpu->use_iommu_v2)
		dev->node_props.capability |= HSA_CAP_ATS_PRESENT;
	अन्यथा
		dev->node_props.capability &= ~HSA_CAP_ATS_PRESENT;

	/* Fix errors in CZ CRAT.
	 * simd_count: Carrizo CRAT reports wrong simd_count, probably
	 *		because it करोesn't consider masked out CUs
	 * max_waves_per_simd: Carrizo reports wrong max_waves_per_simd
	 */
	अगर (dev->gpu->device_info->asic_family == CHIP_CARRIZO) अणु
		dev->node_props.simd_count =
			cu_info.simd_per_cu * cu_info.cu_active_number;
		dev->node_props.max_waves_per_simd = 10;
	पूर्ण

	adev = (काष्ठा amdgpu_device *)(dev->gpu->kgd);
	/* kfd only concerns sram ecc on GFX and HBM ecc on UMC */
	dev->node_props.capability |=
		((adev->ras_features & BIT(AMDGPU_RAS_BLOCK__GFX)) != 0) ?
		HSA_CAP_SRAM_EDCSUPPORTED : 0;
	dev->node_props.capability |= ((adev->ras_features & BIT(AMDGPU_RAS_BLOCK__UMC)) != 0) ?
		HSA_CAP_MEM_EDCSUPPORTED : 0;

	अगर (adev->asic_type != CHIP_VEGA10)
		dev->node_props.capability |= (adev->ras_features != 0) ?
			HSA_CAP_RASEVENTNOTIFY : 0;

	kfd_debug_prपूर्णांक_topology();

	अगर (!res)
		kfd_notअगरy_gpu_change(gpu_id, 1);
err:
	kfd_destroy_crat_image(crat_image);
	वापस res;
पूर्ण

पूर्णांक kfd_topology_हटाओ_device(काष्ठा kfd_dev *gpu)
अणु
	काष्ठा kfd_topology_device *dev, *पंचांगp;
	uपूर्णांक32_t gpu_id;
	पूर्णांक res = -ENODEV;

	करोwn_ग_लिखो(&topology_lock);

	list_क्रम_each_entry_safe(dev, पंचांगp, &topology_device_list, list)
		अगर (dev->gpu == gpu) अणु
			gpu_id = dev->gpu_id;
			kfd_हटाओ_sysfs_node_entry(dev);
			kfd_release_topology_device(dev);
			sys_props.num_devices--;
			res = 0;
			अगर (kfd_topology_update_sysfs() < 0)
				kfd_topology_release_sysfs();
			अवरोध;
		पूर्ण

	up_ग_लिखो(&topology_lock);

	अगर (!res)
		kfd_notअगरy_gpu_change(gpu_id, 0);

	वापस res;
पूर्ण

/* kfd_topology_क्रमागत_kfd_devices - Enumerate through all devices in KFD
 *	topology. If GPU device is found @idx, then valid kfd_dev poपूर्णांकer is
 *	वापसed through @kdev
 * Return -	0: On success (@kdev will be शून्य क्रम non GPU nodes)
 *		-1: If end of list
 */
पूर्णांक kfd_topology_क्रमागत_kfd_devices(uपूर्णांक8_t idx, काष्ठा kfd_dev **kdev)
अणु

	काष्ठा kfd_topology_device *top_dev;
	uपूर्णांक8_t device_idx = 0;

	*kdev = शून्य;
	करोwn_पढ़ो(&topology_lock);

	list_क्रम_each_entry(top_dev, &topology_device_list, list) अणु
		अगर (device_idx == idx) अणु
			*kdev = top_dev->gpu;
			up_पढ़ो(&topology_lock);
			वापस 0;
		पूर्ण

		device_idx++;
	पूर्ण

	up_पढ़ो(&topology_lock);

	वापस -1;

पूर्ण

अटल पूर्णांक kfd_cpumask_to_apic_id(स्थिर काष्ठा cpumask *cpumask)
अणु
	पूर्णांक first_cpu_of_numa_node;

	अगर (!cpumask || cpumask == cpu_none_mask)
		वापस -1;
	first_cpu_of_numa_node = cpumask_first(cpumask);
	अगर (first_cpu_of_numa_node >= nr_cpu_ids)
		वापस -1;
#अगर_घोषित CONFIG_X86_64
	वापस cpu_data(first_cpu_of_numa_node).apicid;
#अन्यथा
	वापस first_cpu_of_numa_node;
#पूर्ण_अगर
पूर्ण

/* kfd_numa_node_to_apic_id - Returns the APIC ID of the first logical processor
 *	of the given NUMA node (numa_node_id)
 * Return -1 on failure
 */
पूर्णांक kfd_numa_node_to_apic_id(पूर्णांक numa_node_id)
अणु
	अगर (numa_node_id == -1) अणु
		pr_warn("Invalid NUMA Node. Use online CPU mask\n");
		वापस kfd_cpumask_to_apic_id(cpu_online_mask);
	पूर्ण
	वापस kfd_cpumask_to_apic_id(cpumask_of_node(numa_node_id));
पूर्ण

व्योम kfd_द्विगुन_confirm_iommu_support(काष्ठा kfd_dev *gpu)
अणु
	काष्ठा kfd_topology_device *dev;

	gpu->use_iommu_v2 = false;

	अगर (!gpu->device_info->needs_iommu_device)
		वापस;

	करोwn_पढ़ो(&topology_lock);

	/* Only use IOMMUv2 अगर there is an APU topology node with no GPU
	 * asचिन्हित yet. This GPU will be asचिन्हित to it.
	 */
	list_क्रम_each_entry(dev, &topology_device_list, list)
		अगर (dev->node_props.cpu_cores_count &&
		    dev->node_props.simd_count &&
		    !dev->gpu)
			gpu->use_iommu_v2 = true;

	up_पढ़ो(&topology_lock);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

पूर्णांक kfd_debugfs_hqds_by_device(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा kfd_topology_device *dev;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक r = 0;

	करोwn_पढ़ो(&topology_lock);

	list_क्रम_each_entry(dev, &topology_device_list, list) अणु
		अगर (!dev->gpu) अणु
			i++;
			जारी;
		पूर्ण

		seq_म_लिखो(m, "Node %u, gpu_id %x:\n", i++, dev->gpu->id);
		r = dqm_debugfs_hqds(m, dev->gpu->dqm);
		अगर (r)
			अवरोध;
	पूर्ण

	up_पढ़ो(&topology_lock);

	वापस r;
पूर्ण

पूर्णांक kfd_debugfs_rls_by_device(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा kfd_topology_device *dev;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक r = 0;

	करोwn_पढ़ो(&topology_lock);

	list_क्रम_each_entry(dev, &topology_device_list, list) अणु
		अगर (!dev->gpu) अणु
			i++;
			जारी;
		पूर्ण

		seq_म_लिखो(m, "Node %u, gpu_id %x:\n", i++, dev->gpu->id);
		r = pm_debugfs_runlist(m, &dev->gpu->dqm->packets);
		अगर (r)
			अवरोध;
	पूर्ण

	up_पढ़ो(&topology_lock);

	वापस r;
पूर्ण

#पूर्ण_अगर
