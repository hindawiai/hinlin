<शैली गुरु>
/*
 * Copyright 2015-2017 Advanced Micro Devices, Inc.
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

#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश "kfd_crat.h"
#समावेश "kfd_priv.h"
#समावेश "kfd_topology.h"
#समावेश "kfd_iommu.h"
#समावेश "amdgpu.h"
#समावेश "amdgpu_amdkfd.h"

/* GPU Processor ID base क्रम dGPUs क्रम which VCRAT needs to be created.
 * GPU processor ID are expressed with Bit[31]=1.
 * The base is set to 0x8000_0000 + 0x1000 to aव्योम collision with GPU IDs
 * used in the CRAT.
 */
अटल uपूर्णांक32_t gpu_processor_id_low = 0x80001000;

/* Return the next available gpu_processor_id and increment it क्रम next GPU
 *	@total_cu_count - Total CUs present in the GPU including ones
 *			  masked off
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_and_inc_gpu_processor_id(
				अचिन्हित पूर्णांक total_cu_count)
अणु
	पूर्णांक current_id = gpu_processor_id_low;

	gpu_processor_id_low += total_cu_count;
	वापस current_id;
पूर्ण

/* Static table to describe GPU Cache inक्रमmation */
काष्ठा kfd_gpu_cache_info अणु
	uपूर्णांक32_t	cache_size;
	uपूर्णांक32_t	cache_level;
	uपूर्णांक32_t	flags;
	/* Indicates how many Compute Units share this cache
	 * Value = 1 indicates the cache is not shared
	 */
	uपूर्णांक32_t	num_cu_shared;
पूर्ण;

अटल काष्ठा kfd_gpu_cache_info kaveri_cache_info[] = अणु
	अणु
		/* TCP L1 Cache per CU */
		.cache_size = 16,
		.cache_level = 1,
		.flags = (CRAT_CACHE_FLAGS_ENABLED |
				CRAT_CACHE_FLAGS_DATA_CACHE |
				CRAT_CACHE_FLAGS_SIMD_CACHE),
		.num_cu_shared = 1,

	पूर्ण,
	अणु
		/* Scalar L1 Inकाष्ठाion Cache (in SQC module) per bank */
		.cache_size = 16,
		.cache_level = 1,
		.flags = (CRAT_CACHE_FLAGS_ENABLED |
				CRAT_CACHE_FLAGS_INST_CACHE |
				CRAT_CACHE_FLAGS_SIMD_CACHE),
		.num_cu_shared = 2,
	पूर्ण,
	अणु
		/* Scalar L1 Data Cache (in SQC module) per bank */
		.cache_size = 8,
		.cache_level = 1,
		.flags = (CRAT_CACHE_FLAGS_ENABLED |
				CRAT_CACHE_FLAGS_DATA_CACHE |
				CRAT_CACHE_FLAGS_SIMD_CACHE),
		.num_cu_shared = 2,
	पूर्ण,

	/* TODO: Add L2 Cache inक्रमmation */
पूर्ण;


अटल काष्ठा kfd_gpu_cache_info carrizo_cache_info[] = अणु
	अणु
		/* TCP L1 Cache per CU */
		.cache_size = 16,
		.cache_level = 1,
		.flags = (CRAT_CACHE_FLAGS_ENABLED |
				CRAT_CACHE_FLAGS_DATA_CACHE |
				CRAT_CACHE_FLAGS_SIMD_CACHE),
		.num_cu_shared = 1,
	पूर्ण,
	अणु
		/* Scalar L1 Inकाष्ठाion Cache (in SQC module) per bank */
		.cache_size = 8,
		.cache_level = 1,
		.flags = (CRAT_CACHE_FLAGS_ENABLED |
				CRAT_CACHE_FLAGS_INST_CACHE |
				CRAT_CACHE_FLAGS_SIMD_CACHE),
		.num_cu_shared = 4,
	पूर्ण,
	अणु
		/* Scalar L1 Data Cache (in SQC module) per bank. */
		.cache_size = 4,
		.cache_level = 1,
		.flags = (CRAT_CACHE_FLAGS_ENABLED |
				CRAT_CACHE_FLAGS_DATA_CACHE |
				CRAT_CACHE_FLAGS_SIMD_CACHE),
		.num_cu_shared = 4,
	पूर्ण,

	/* TODO: Add L2 Cache inक्रमmation */
पूर्ण;

/* NOTE: In future अगर more inक्रमmation is added to काष्ठा kfd_gpu_cache_info
 * the following ASICs may need a separate table.
 */
#घोषणा hawaii_cache_info kaveri_cache_info
#घोषणा tonga_cache_info carrizo_cache_info
#घोषणा fiji_cache_info  carrizo_cache_info
#घोषणा polaris10_cache_info carrizo_cache_info
#घोषणा polaris11_cache_info carrizo_cache_info
#घोषणा polaris12_cache_info carrizo_cache_info
#घोषणा vegam_cache_info carrizo_cache_info
/* TODO - check & update Vega10 cache details */
#घोषणा vega10_cache_info carrizo_cache_info
#घोषणा raven_cache_info carrizo_cache_info
#घोषणा renoir_cache_info carrizo_cache_info
/* TODO - check & update Navi10 cache details */
#घोषणा navi10_cache_info carrizo_cache_info
#घोषणा vangogh_cache_info carrizo_cache_info

अटल व्योम kfd_populated_cu_info_cpu(काष्ठा kfd_topology_device *dev,
		काष्ठा crat_subtype_computeunit *cu)
अणु
	dev->node_props.cpu_cores_count = cu->num_cpu_cores;
	dev->node_props.cpu_core_id_base = cu->processor_id_low;
	अगर (cu->hsa_capability & CRAT_CU_FLAGS_IOMMU_PRESENT)
		dev->node_props.capability |= HSA_CAP_ATS_PRESENT;

	pr_debug("CU CPU: cores=%d id_base=%d\n", cu->num_cpu_cores,
			cu->processor_id_low);
पूर्ण

अटल व्योम kfd_populated_cu_info_gpu(काष्ठा kfd_topology_device *dev,
		काष्ठा crat_subtype_computeunit *cu)
अणु
	dev->node_props.simd_id_base = cu->processor_id_low;
	dev->node_props.simd_count = cu->num_simd_cores;
	dev->node_props.lds_size_in_kb = cu->lds_size_in_kb;
	dev->node_props.max_waves_per_simd = cu->max_waves_simd;
	dev->node_props.wave_front_size = cu->wave_front_size;
	dev->node_props.array_count = cu->array_count;
	dev->node_props.cu_per_simd_array = cu->num_cu_per_array;
	dev->node_props.simd_per_cu = cu->num_simd_per_cu;
	dev->node_props.max_slots_scratch_cu = cu->max_slots_scatch_cu;
	अगर (cu->hsa_capability & CRAT_CU_FLAGS_HOT_PLUGGABLE)
		dev->node_props.capability |= HSA_CAP_HOT_PLUGGABLE;
	pr_debug("CU GPU: id_base=%d\n", cu->processor_id_low);
पूर्ण

/* kfd_parse_subtype_cu - parse compute unit subtypes and attach it to correct
 * topology device present in the device_list
 */
अटल पूर्णांक kfd_parse_subtype_cu(काष्ठा crat_subtype_computeunit *cu,
				काष्ठा list_head *device_list)
अणु
	काष्ठा kfd_topology_device *dev;

	pr_debug("Found CU entry in CRAT table with proximity_domain=%d caps=%x\n",
			cu->proximity_करोमुख्य, cu->hsa_capability);
	list_क्रम_each_entry(dev, device_list, list) अणु
		अगर (cu->proximity_करोमुख्य == dev->proximity_करोमुख्य) अणु
			अगर (cu->flags & CRAT_CU_FLAGS_CPU_PRESENT)
				kfd_populated_cu_info_cpu(dev, cu);

			अगर (cu->flags & CRAT_CU_FLAGS_GPU_PRESENT)
				kfd_populated_cu_info_gpu(dev, cu);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा kfd_mem_properties *
find_subtype_mem(uपूर्णांक32_t heap_type, uपूर्णांक32_t flags, uपूर्णांक32_t width,
		काष्ठा kfd_topology_device *dev)
अणु
	काष्ठा kfd_mem_properties *props;

	list_क्रम_each_entry(props, &dev->mem_props, list) अणु
		अगर (props->heap_type == heap_type
				&& props->flags == flags
				&& props->width == width)
			वापस props;
	पूर्ण

	वापस शून्य;
पूर्ण
/* kfd_parse_subtype_mem - parse memory subtypes and attach it to correct
 * topology device present in the device_list
 */
अटल पूर्णांक kfd_parse_subtype_mem(काष्ठा crat_subtype_memory *mem,
				काष्ठा list_head *device_list)
अणु
	काष्ठा kfd_mem_properties *props;
	काष्ठा kfd_topology_device *dev;
	uपूर्णांक32_t heap_type;
	uपूर्णांक64_t size_in_bytes;
	uपूर्णांक32_t flags = 0;
	uपूर्णांक32_t width;

	pr_debug("Found memory entry in CRAT table with proximity_domain=%d\n",
			mem->proximity_करोमुख्य);
	list_क्रम_each_entry(dev, device_list, list) अणु
		अगर (mem->proximity_करोमुख्य == dev->proximity_करोमुख्य) अणु
			/* We're on GPU node */
			अगर (dev->node_props.cpu_cores_count == 0) अणु
				/* APU */
				अगर (mem->visibility_type == 0)
					heap_type =
						HSA_MEM_HEAP_TYPE_FB_PRIVATE;
				/* dGPU */
				अन्यथा
					heap_type = mem->visibility_type;
			पूर्ण अन्यथा
				heap_type = HSA_MEM_HEAP_TYPE_SYSTEM;

			अगर (mem->flags & CRAT_MEM_FLAGS_HOT_PLUGGABLE)
				flags |= HSA_MEM_FLAGS_HOT_PLUGGABLE;
			अगर (mem->flags & CRAT_MEM_FLAGS_NON_VOLATILE)
				flags |= HSA_MEM_FLAGS_NON_VOLATILE;

			size_in_bytes =
				((uपूर्णांक64_t)mem->length_high << 32) +
							mem->length_low;
			width = mem->width;

			/* Multiple banks of the same type are aggregated पूर्णांकo
			 * one. User mode करोesn't care about multiple physical
			 * memory segments. It's managed as a single भव
			 * heap क्रम user mode.
			 */
			props = find_subtype_mem(heap_type, flags, width, dev);
			अगर (props) अणु
				props->size_in_bytes += size_in_bytes;
				अवरोध;
			पूर्ण

			props = kfd_alloc_काष्ठा(props);
			अगर (!props)
				वापस -ENOMEM;

			props->heap_type = heap_type;
			props->flags = flags;
			props->size_in_bytes = size_in_bytes;
			props->width = width;

			dev->node_props.mem_banks_count++;
			list_add_tail(&props->list, &dev->mem_props);

			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* kfd_parse_subtype_cache - parse cache subtypes and attach it to correct
 * topology device present in the device_list
 */
अटल पूर्णांक kfd_parse_subtype_cache(काष्ठा crat_subtype_cache *cache,
			काष्ठा list_head *device_list)
अणु
	काष्ठा kfd_cache_properties *props;
	काष्ठा kfd_topology_device *dev;
	uपूर्णांक32_t id;
	uपूर्णांक32_t total_num_of_cu;

	id = cache->processor_id_low;

	pr_debug("Found cache entry in CRAT table with processor_id=%d\n", id);
	list_क्रम_each_entry(dev, device_list, list) अणु
		total_num_of_cu = (dev->node_props.array_count *
					dev->node_props.cu_per_simd_array);

		/* Cache infomration in CRAT करोesn't have proximity_करोमुख्य
		 * inक्रमmation as it is associated with a CPU core or GPU
		 * Compute Unit. So map the cache using CPU core Id or SIMD
		 * (GPU) ID.
		 * TODO: This works because currently we can safely assume that
		 *  Compute Units are parsed beक्रमe caches are parsed. In
		 *  future, हटाओ this dependency
		 */
		अगर ((id >= dev->node_props.cpu_core_id_base &&
			id <= dev->node_props.cpu_core_id_base +
				dev->node_props.cpu_cores_count) ||
			(id >= dev->node_props.simd_id_base &&
			id < dev->node_props.simd_id_base +
				total_num_of_cu)) अणु
			props = kfd_alloc_काष्ठा(props);
			अगर (!props)
				वापस -ENOMEM;

			props->processor_id_low = id;
			props->cache_level = cache->cache_level;
			props->cache_size = cache->cache_size;
			props->cacheline_size = cache->cache_line_size;
			props->cachelines_per_tag = cache->lines_per_tag;
			props->cache_assoc = cache->associativity;
			props->cache_latency = cache->cache_latency;
			स_नकल(props->sibling_map, cache->sibling_map,
					माप(props->sibling_map));

			अगर (cache->flags & CRAT_CACHE_FLAGS_DATA_CACHE)
				props->cache_type |= HSA_CACHE_TYPE_DATA;
			अगर (cache->flags & CRAT_CACHE_FLAGS_INST_CACHE)
				props->cache_type |= HSA_CACHE_TYPE_INSTRUCTION;
			अगर (cache->flags & CRAT_CACHE_FLAGS_CPU_CACHE)
				props->cache_type |= HSA_CACHE_TYPE_CPU;
			अगर (cache->flags & CRAT_CACHE_FLAGS_SIMD_CACHE)
				props->cache_type |= HSA_CACHE_TYPE_HSACU;

			dev->cache_count++;
			dev->node_props.caches_count++;
			list_add_tail(&props->list, &dev->cache_props);

			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* kfd_parse_subtype_iolink - parse iolink subtypes and attach it to correct
 * topology device present in the device_list
 */
अटल पूर्णांक kfd_parse_subtype_iolink(काष्ठा crat_subtype_iolink *iolink,
					काष्ठा list_head *device_list)
अणु
	काष्ठा kfd_iolink_properties *props = शून्य, *props2;
	काष्ठा kfd_topology_device *dev, *to_dev;
	uपूर्णांक32_t id_from;
	uपूर्णांक32_t id_to;

	id_from = iolink->proximity_करोमुख्य_from;
	id_to = iolink->proximity_करोमुख्य_to;

	pr_debug("Found IO link entry in CRAT table with id_from=%d, id_to %d\n",
			id_from, id_to);
	list_क्रम_each_entry(dev, device_list, list) अणु
		अगर (id_from == dev->proximity_करोमुख्य) अणु
			props = kfd_alloc_काष्ठा(props);
			अगर (!props)
				वापस -ENOMEM;

			props->node_from = id_from;
			props->node_to = id_to;
			props->ver_maj = iolink->version_major;
			props->ver_min = iolink->version_minor;
			props->iolink_type = iolink->io_पूर्णांकerface_type;

			अगर (props->iolink_type == CRAT_IOLINK_TYPE_PCIEXPRESS)
				props->weight = 20;
			अन्यथा अगर (props->iolink_type == CRAT_IOLINK_TYPE_XGMI)
				props->weight = 15 * iolink->num_hops_xgmi;
			अन्यथा
				props->weight = node_distance(id_from, id_to);

			props->min_latency = iolink->minimum_latency;
			props->max_latency = iolink->maximum_latency;
			props->min_bandwidth = iolink->minimum_bandwidth_mbs;
			props->max_bandwidth = iolink->maximum_bandwidth_mbs;
			props->rec_transfer_size =
					iolink->recommended_transfer_size;

			dev->io_link_count++;
			dev->node_props.io_links_count++;
			list_add_tail(&props->list, &dev->io_link_props);
			अवरोध;
		पूर्ण
	पूर्ण

	/* CPU topology is created beक्रमe GPUs are detected, so CPU->GPU
	 * links are not built at that समय. If a PCIe type is discovered, it
	 * means a GPU is detected and we are adding GPU->CPU to the topology.
	 * At this समय, also add the corresponded CPU->GPU link अगर GPU
	 * is large bar.
	 * For xGMI, we only added the link with one direction in the crat
	 * table, add corresponded reversed direction link now.
	 */
	अगर (props && (iolink->flags & CRAT_IOLINK_FLAGS_BI_सूचीECTIONAL)) अणु
		to_dev = kfd_topology_device_by_proximity_करोमुख्य(id_to);
		अगर (!to_dev)
			वापस -ENODEV;
		/* same everything but the other direction */
		props2 = kmemdup(props, माप(*props2), GFP_KERNEL);
		props2->node_from = id_to;
		props2->node_to = id_from;
		props2->kobj = शून्य;
		to_dev->io_link_count++;
		to_dev->node_props.io_links_count++;
		list_add_tail(&props2->list, &to_dev->io_link_props);
	पूर्ण

	वापस 0;
पूर्ण

/* kfd_parse_subtype - parse subtypes and attach it to correct topology device
 * present in the device_list
 *	@sub_type_hdr - subtype section of crat_image
 *	@device_list - list of topology devices present in this crat_image
 */
अटल पूर्णांक kfd_parse_subtype(काष्ठा crat_subtype_generic *sub_type_hdr,
				काष्ठा list_head *device_list)
अणु
	काष्ठा crat_subtype_computeunit *cu;
	काष्ठा crat_subtype_memory *mem;
	काष्ठा crat_subtype_cache *cache;
	काष्ठा crat_subtype_iolink *iolink;
	पूर्णांक ret = 0;

	चयन (sub_type_hdr->type) अणु
	हाल CRAT_SUBTYPE_COMPUTEUNIT_AFFINITY:
		cu = (काष्ठा crat_subtype_computeunit *)sub_type_hdr;
		ret = kfd_parse_subtype_cu(cu, device_list);
		अवरोध;
	हाल CRAT_SUBTYPE_MEMORY_AFFINITY:
		mem = (काष्ठा crat_subtype_memory *)sub_type_hdr;
		ret = kfd_parse_subtype_mem(mem, device_list);
		अवरोध;
	हाल CRAT_SUBTYPE_CACHE_AFFINITY:
		cache = (काष्ठा crat_subtype_cache *)sub_type_hdr;
		ret = kfd_parse_subtype_cache(cache, device_list);
		अवरोध;
	हाल CRAT_SUBTYPE_TLB_AFFINITY:
		/*
		 * For now, nothing to करो here
		 */
		pr_debug("Found TLB entry in CRAT table (not processing)\n");
		अवरोध;
	हाल CRAT_SUBTYPE_CCOMPUTE_AFFINITY:
		/*
		 * For now, nothing to करो here
		 */
		pr_debug("Found CCOMPUTE entry in CRAT table (not processing)\n");
		अवरोध;
	हाल CRAT_SUBTYPE_IOLINK_AFFINITY:
		iolink = (काष्ठा crat_subtype_iolink *)sub_type_hdr;
		ret = kfd_parse_subtype_iolink(iolink, device_list);
		अवरोध;
	शेष:
		pr_warn("Unknown subtype %d in CRAT\n",
				sub_type_hdr->type);
	पूर्ण

	वापस ret;
पूर्ण

/* kfd_parse_crat_table - parse CRAT table. For each node present in CRAT
 * create a kfd_topology_device and add in to device_list. Also parse
 * CRAT subtypes and attach it to appropriate kfd_topology_device
 *	@crat_image - input image containing CRAT
 *	@device_list - [OUT] list of kfd_topology_device generated after
 *		       parsing crat_image
 *	@proximity_करोमुख्य - Proximity करोमुख्य of the first device in the table
 *
 *	Return - 0 अगर successful अन्यथा -ve value
 */
पूर्णांक kfd_parse_crat_table(व्योम *crat_image, काष्ठा list_head *device_list,
			 uपूर्णांक32_t proximity_करोमुख्य)
अणु
	काष्ठा kfd_topology_device *top_dev = शून्य;
	काष्ठा crat_subtype_generic *sub_type_hdr;
	uपूर्णांक16_t node_id;
	पूर्णांक ret = 0;
	काष्ठा crat_header *crat_table = (काष्ठा crat_header *)crat_image;
	uपूर्णांक16_t num_nodes;
	uपूर्णांक32_t image_len;

	अगर (!crat_image)
		वापस -EINVAL;

	अगर (!list_empty(device_list)) अणु
		pr_warn("Error device list should be empty\n");
		वापस -EINVAL;
	पूर्ण

	num_nodes = crat_table->num_करोमुख्यs;
	image_len = crat_table->length;

	pr_debug("Parsing CRAT table with %d nodes\n", num_nodes);

	क्रम (node_id = 0; node_id < num_nodes; node_id++) अणु
		top_dev = kfd_create_topology_device(device_list);
		अगर (!top_dev)
			अवरोध;
		top_dev->proximity_करोमुख्य = proximity_करोमुख्य++;
	पूर्ण

	अगर (!top_dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	स_नकल(top_dev->oem_id, crat_table->oem_id, CRAT_OEMID_LENGTH);
	स_नकल(top_dev->oem_table_id, crat_table->oem_table_id,
			CRAT_OEMTABLEID_LENGTH);
	top_dev->oem_revision = crat_table->oem_revision;

	sub_type_hdr = (काष्ठा crat_subtype_generic *)(crat_table+1);
	जबतक ((अक्षर *)sub_type_hdr + माप(काष्ठा crat_subtype_generic) <
			((अक्षर *)crat_image) + image_len) अणु
		अगर (sub_type_hdr->flags & CRAT_SUBTYPE_FLAGS_ENABLED) अणु
			ret = kfd_parse_subtype(sub_type_hdr, device_list);
			अगर (ret)
				अवरोध;
		पूर्ण

		sub_type_hdr = (typeof(sub_type_hdr))((अक्षर *)sub_type_hdr +
				sub_type_hdr->length);
	पूर्ण

err:
	अगर (ret)
		kfd_release_topology_device_list(device_list);

	वापस ret;
पूर्ण

/* Helper function. See kfd_fill_gpu_cache_info क्रम parameter description */
अटल पूर्णांक fill_in_pcache(काष्ठा crat_subtype_cache *pcache,
				काष्ठा kfd_gpu_cache_info *pcache_info,
				काष्ठा kfd_cu_info *cu_info,
				पूर्णांक mem_available,
				पूर्णांक cu_biपंचांगask,
				पूर्णांक cache_type, अचिन्हित पूर्णांक cu_processor_id,
				पूर्णांक cu_block)
अणु
	अचिन्हित पूर्णांक cu_sibling_map_mask;
	पूर्णांक first_active_cu;

	/* First check अगर enough memory is available */
	अगर (माप(काष्ठा crat_subtype_cache) > mem_available)
		वापस -ENOMEM;

	cu_sibling_map_mask = cu_biपंचांगask;
	cu_sibling_map_mask >>= cu_block;
	cu_sibling_map_mask &=
		((1 << pcache_info[cache_type].num_cu_shared) - 1);
	first_active_cu = ffs(cu_sibling_map_mask);

	/* CU could be inactive. In हाल of shared cache find the first active
	 * CU. and inहाल of non-shared cache check अगर the CU is inactive. If
	 * inactive active skip it
	 */
	अगर (first_active_cu) अणु
		स_रखो(pcache, 0, माप(काष्ठा crat_subtype_cache));
		pcache->type = CRAT_SUBTYPE_CACHE_AFFINITY;
		pcache->length = माप(काष्ठा crat_subtype_cache);
		pcache->flags = pcache_info[cache_type].flags;
		pcache->processor_id_low = cu_processor_id
					 + (first_active_cu - 1);
		pcache->cache_level = pcache_info[cache_type].cache_level;
		pcache->cache_size = pcache_info[cache_type].cache_size;

		/* Sibling map is w.r.t processor_id_low, so shअगरt out
		 * inactive CU
		 */
		cu_sibling_map_mask =
			cu_sibling_map_mask >> (first_active_cu - 1);

		pcache->sibling_map[0] = (uपूर्णांक8_t)(cu_sibling_map_mask & 0xFF);
		pcache->sibling_map[1] =
				(uपूर्णांक8_t)((cu_sibling_map_mask >> 8) & 0xFF);
		pcache->sibling_map[2] =
				(uपूर्णांक8_t)((cu_sibling_map_mask >> 16) & 0xFF);
		pcache->sibling_map[3] =
				(uपूर्णांक8_t)((cu_sibling_map_mask >> 24) & 0xFF);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/* kfd_fill_gpu_cache_info - Fill GPU cache info using kfd_gpu_cache_info
 * tables
 *
 *	@kdev - [IN] GPU device
 *	@gpu_processor_id - [IN] GPU processor ID to which these caches
 *			    associate
 *	@available_size - [IN] Amount of memory available in pcache
 *	@cu_info - [IN] Compute Unit info obtained from KGD
 *	@pcache - [OUT] memory पूर्णांकo which cache data is to be filled in.
 *	@size_filled - [OUT] amount of data used up in pcache.
 *	@num_of_entries - [OUT] number of caches added
 */
अटल पूर्णांक kfd_fill_gpu_cache_info(काष्ठा kfd_dev *kdev,
			पूर्णांक gpu_processor_id,
			पूर्णांक available_size,
			काष्ठा kfd_cu_info *cu_info,
			काष्ठा crat_subtype_cache *pcache,
			पूर्णांक *size_filled,
			पूर्णांक *num_of_entries)
अणु
	काष्ठा kfd_gpu_cache_info *pcache_info;
	पूर्णांक num_of_cache_types = 0;
	पूर्णांक i, j, k;
	पूर्णांक ct = 0;
	पूर्णांक mem_available = available_size;
	अचिन्हित पूर्णांक cu_processor_id;
	पूर्णांक ret;

	चयन (kdev->device_info->asic_family) अणु
	हाल CHIP_KAVERI:
		pcache_info = kaveri_cache_info;
		num_of_cache_types = ARRAY_SIZE(kaveri_cache_info);
		अवरोध;
	हाल CHIP_HAWAII:
		pcache_info = hawaii_cache_info;
		num_of_cache_types = ARRAY_SIZE(hawaii_cache_info);
		अवरोध;
	हाल CHIP_CARRIZO:
		pcache_info = carrizo_cache_info;
		num_of_cache_types = ARRAY_SIZE(carrizo_cache_info);
		अवरोध;
	हाल CHIP_TONGA:
		pcache_info = tonga_cache_info;
		num_of_cache_types = ARRAY_SIZE(tonga_cache_info);
		अवरोध;
	हाल CHIP_FIJI:
		pcache_info = fiji_cache_info;
		num_of_cache_types = ARRAY_SIZE(fiji_cache_info);
		अवरोध;
	हाल CHIP_POLARIS10:
		pcache_info = polaris10_cache_info;
		num_of_cache_types = ARRAY_SIZE(polaris10_cache_info);
		अवरोध;
	हाल CHIP_POLARIS11:
		pcache_info = polaris11_cache_info;
		num_of_cache_types = ARRAY_SIZE(polaris11_cache_info);
		अवरोध;
	हाल CHIP_POLARIS12:
		pcache_info = polaris12_cache_info;
		num_of_cache_types = ARRAY_SIZE(polaris12_cache_info);
		अवरोध;
	हाल CHIP_VEGAM:
		pcache_info = vegam_cache_info;
		num_of_cache_types = ARRAY_SIZE(vegam_cache_info);
		अवरोध;
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
	हाल CHIP_ARCTURUS:
	हाल CHIP_ALDEBARAN:
		pcache_info = vega10_cache_info;
		num_of_cache_types = ARRAY_SIZE(vega10_cache_info);
		अवरोध;
	हाल CHIP_RAVEN:
		pcache_info = raven_cache_info;
		num_of_cache_types = ARRAY_SIZE(raven_cache_info);
		अवरोध;
	हाल CHIP_RENOIR:
		pcache_info = renoir_cache_info;
		num_of_cache_types = ARRAY_SIZE(renoir_cache_info);
		अवरोध;
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI12:
	हाल CHIP_NAVI14:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
		pcache_info = navi10_cache_info;
		num_of_cache_types = ARRAY_SIZE(navi10_cache_info);
		अवरोध;
	हाल CHIP_VANGOGH:
		pcache_info = vangogh_cache_info;
		num_of_cache_types = ARRAY_SIZE(vangogh_cache_info);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*size_filled = 0;
	*num_of_entries = 0;

	/* For each type of cache listed in the kfd_gpu_cache_info table,
	 * go through all available Compute Units.
	 * The [i,j,k] loop will
	 *		अगर kfd_gpu_cache_info.num_cu_shared = 1
	 *			will parse through all available CU
	 *		If (kfd_gpu_cache_info.num_cu_shared != 1)
	 *			then it will consider only one CU from
	 *			the shared unit
	 */

	क्रम (ct = 0; ct < num_of_cache_types; ct++) अणु
		cu_processor_id = gpu_processor_id;
		क्रम (i = 0; i < cu_info->num_shader_engines; i++) अणु
			क्रम (j = 0; j < cu_info->num_shader_arrays_per_engine;
				j++) अणु
				क्रम (k = 0; k < cu_info->num_cu_per_sh;
					k += pcache_info[ct].num_cu_shared) अणु

					ret = fill_in_pcache(pcache,
						pcache_info,
						cu_info,
						mem_available,
						cu_info->cu_biपंचांगap[i % 4][j + i / 4],
						ct,
						cu_processor_id,
						k);

					अगर (ret < 0)
						अवरोध;

					अगर (!ret) अणु
						pcache++;
						(*num_of_entries)++;
						mem_available -=
							माप(*pcache);
						(*size_filled) +=
							माप(*pcache);
					पूर्ण

					/* Move to next CU block */
					cu_processor_id +=
						pcache_info[ct].num_cu_shared;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	pr_debug("Added [%d] GPU cache entries\n", *num_of_entries);

	वापस 0;
पूर्ण

अटल bool kfd_ignore_crat(व्योम)
अणु
	bool ret;

	अगर (ignore_crat)
		वापस true;

#अगर_अघोषित KFD_SUPPORT_IOMMU_V2
	ret = true;
#अन्यथा
	ret = false;
#पूर्ण_अगर

	वापस ret;
पूर्ण

/*
 * kfd_create_crat_image_acpi - Allocates memory क्रम CRAT image and
 * copies CRAT from ACPI (अगर available).
 * NOTE: Call kfd_destroy_crat_image to मुक्त CRAT image memory
 *
 *	@crat_image: CRAT पढ़ो from ACPI. If no CRAT in ACPI then
 *		     crat_image will be शून्य
 *	@size: [OUT] size of crat_image
 *
 *	Return 0 अगर successful अन्यथा वापस error code
 */
पूर्णांक kfd_create_crat_image_acpi(व्योम **crat_image, माप_प्रकार *size)
अणु
	काष्ठा acpi_table_header *crat_table;
	acpi_status status;
	व्योम *pcrat_image;
	पूर्णांक rc = 0;

	अगर (!crat_image)
		वापस -EINVAL;

	*crat_image = शून्य;

	अगर (kfd_ignore_crat()) अणु
		pr_info("CRAT table disabled by module option\n");
		वापस -ENODATA;
	पूर्ण

	/* Fetch the CRAT table from ACPI */
	status = acpi_get_table(CRAT_SIGNATURE, 0, &crat_table);
	अगर (status == AE_NOT_FOUND) अणु
		pr_warn("CRAT table not found\n");
		वापस -ENODATA;
	पूर्ण अन्यथा अगर (ACPI_FAILURE(status)) अणु
		स्थिर अक्षर *err = acpi_क्रमmat_exception(status);

		pr_err("CRAT table error: %s\n", err);
		वापस -EINVAL;
	पूर्ण

	pcrat_image = kvदो_स्मृति(crat_table->length, GFP_KERNEL);
	अगर (!pcrat_image) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(pcrat_image, crat_table, crat_table->length);
	*crat_image = pcrat_image;
	*size = crat_table->length;
out:
	acpi_put_table(crat_table);
	वापस rc;
पूर्ण

/* Memory required to create Virtual CRAT.
 * Since there is no easy way to predict the amount of memory required, the
 * following amount is allocated क्रम GPU Virtual CRAT. This is
 * expected to cover all known conditions. But to be safe additional check
 * is put in the code to ensure we करोn't overग_लिखो.
 */
#घोषणा VCRAT_SIZE_FOR_GPU	(4 * PAGE_SIZE)

/* kfd_fill_cu_क्रम_cpu - Fill in Compute info क्रम the given CPU NUMA node
 *
 *	@numa_node_id: CPU NUMA node id
 *	@avail_size: Available size in the memory
 *	@sub_type_hdr: Memory पूर्णांकo which compute info will be filled in
 *
 *	Return 0 अगर successful अन्यथा वापस -ve value
 */
अटल पूर्णांक kfd_fill_cu_क्रम_cpu(पूर्णांक numa_node_id, पूर्णांक *avail_size,
				पूर्णांक proximity_करोमुख्य,
				काष्ठा crat_subtype_computeunit *sub_type_hdr)
अणु
	स्थिर काष्ठा cpumask *cpumask;

	*avail_size -= माप(काष्ठा crat_subtype_computeunit);
	अगर (*avail_size < 0)
		वापस -ENOMEM;

	स_रखो(sub_type_hdr, 0, माप(काष्ठा crat_subtype_computeunit));

	/* Fill in subtype header data */
	sub_type_hdr->type = CRAT_SUBTYPE_COMPUTEUNIT_AFFINITY;
	sub_type_hdr->length = माप(काष्ठा crat_subtype_computeunit);
	sub_type_hdr->flags = CRAT_SUBTYPE_FLAGS_ENABLED;

	cpumask = cpumask_of_node(numa_node_id);

	/* Fill in CU data */
	sub_type_hdr->flags |= CRAT_CU_FLAGS_CPU_PRESENT;
	sub_type_hdr->proximity_करोमुख्य = proximity_करोमुख्य;
	sub_type_hdr->processor_id_low = kfd_numa_node_to_apic_id(numa_node_id);
	अगर (sub_type_hdr->processor_id_low == -1)
		वापस -EINVAL;

	sub_type_hdr->num_cpu_cores = cpumask_weight(cpumask);

	वापस 0;
पूर्ण

/* kfd_fill_mem_info_क्रम_cpu - Fill in Memory info क्रम the given CPU NUMA node
 *
 *	@numa_node_id: CPU NUMA node id
 *	@avail_size: Available size in the memory
 *	@sub_type_hdr: Memory पूर्णांकo which compute info will be filled in
 *
 *	Return 0 अगर successful अन्यथा वापस -ve value
 */
अटल पूर्णांक kfd_fill_mem_info_क्रम_cpu(पूर्णांक numa_node_id, पूर्णांक *avail_size,
			पूर्णांक proximity_करोमुख्य,
			काष्ठा crat_subtype_memory *sub_type_hdr)
अणु
	uपूर्णांक64_t mem_in_bytes = 0;
	pg_data_t *pgdat;
	पूर्णांक zone_type;

	*avail_size -= माप(काष्ठा crat_subtype_memory);
	अगर (*avail_size < 0)
		वापस -ENOMEM;

	स_रखो(sub_type_hdr, 0, माप(काष्ठा crat_subtype_memory));

	/* Fill in subtype header data */
	sub_type_hdr->type = CRAT_SUBTYPE_MEMORY_AFFINITY;
	sub_type_hdr->length = माप(काष्ठा crat_subtype_memory);
	sub_type_hdr->flags = CRAT_SUBTYPE_FLAGS_ENABLED;

	/* Fill in Memory Subunit data */

	/* Unlike si_meminfo, si_meminfo_node is not exported. So
	 * the following lines are duplicated from si_meminfo_node
	 * function
	 */
	pgdat = NODE_DATA(numa_node_id);
	क्रम (zone_type = 0; zone_type < MAX_NR_ZONES; zone_type++)
		mem_in_bytes += zone_managed_pages(&pgdat->node_zones[zone_type]);
	mem_in_bytes <<= PAGE_SHIFT;

	sub_type_hdr->length_low = lower_32_bits(mem_in_bytes);
	sub_type_hdr->length_high = upper_32_bits(mem_in_bytes);
	sub_type_hdr->proximity_करोमुख्य = proximity_करोमुख्य;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल पूर्णांक kfd_fill_iolink_info_क्रम_cpu(पूर्णांक numa_node_id, पूर्णांक *avail_size,
				uपूर्णांक32_t *num_entries,
				काष्ठा crat_subtype_iolink *sub_type_hdr)
अणु
	पूर्णांक nid;
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);
	uपूर्णांक8_t link_type;

	अगर (c->x86_venकरोr == X86_VENDOR_AMD)
		link_type = CRAT_IOLINK_TYPE_HYPERTRANSPORT;
	अन्यथा
		link_type = CRAT_IOLINK_TYPE_QPI_1_1;

	*num_entries = 0;

	/* Create IO links from this node to other CPU nodes */
	क्रम_each_online_node(nid) अणु
		अगर (nid == numa_node_id) /* node itself */
			जारी;

		*avail_size -= माप(काष्ठा crat_subtype_iolink);
		अगर (*avail_size < 0)
			वापस -ENOMEM;

		स_रखो(sub_type_hdr, 0, माप(काष्ठा crat_subtype_iolink));

		/* Fill in subtype header data */
		sub_type_hdr->type = CRAT_SUBTYPE_IOLINK_AFFINITY;
		sub_type_hdr->length = माप(काष्ठा crat_subtype_iolink);
		sub_type_hdr->flags = CRAT_SUBTYPE_FLAGS_ENABLED;

		/* Fill in IO link data */
		sub_type_hdr->proximity_करोमुख्य_from = numa_node_id;
		sub_type_hdr->proximity_करोमुख्य_to = nid;
		sub_type_hdr->io_पूर्णांकerface_type = link_type;

		(*num_entries)++;
		sub_type_hdr++;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* kfd_create_vcrat_image_cpu - Create Virtual CRAT क्रम CPU
 *
 *	@pcrat_image: Fill in VCRAT क्रम CPU
 *	@size:	[IN] allocated size of crat_image.
 *		[OUT] actual size of data filled in crat_image
 */
अटल पूर्णांक kfd_create_vcrat_image_cpu(व्योम *pcrat_image, माप_प्रकार *size)
अणु
	काष्ठा crat_header *crat_table = (काष्ठा crat_header *)pcrat_image;
	काष्ठा acpi_table_header *acpi_table;
	acpi_status status;
	काष्ठा crat_subtype_generic *sub_type_hdr;
	पूर्णांक avail_size = *size;
	पूर्णांक numa_node_id;
#अगर_घोषित CONFIG_X86_64
	uपूर्णांक32_t entries = 0;
#पूर्ण_अगर
	पूर्णांक ret = 0;

	अगर (!pcrat_image)
		वापस -EINVAL;

	/* Fill in CRAT Header.
	 * Modअगरy length and total_entries as subunits are added.
	 */
	avail_size -= माप(काष्ठा crat_header);
	अगर (avail_size < 0)
		वापस -ENOMEM;

	स_रखो(crat_table, 0, माप(काष्ठा crat_header));
	स_नकल(&crat_table->signature, CRAT_SIGNATURE,
			माप(crat_table->signature));
	crat_table->length = माप(काष्ठा crat_header);

	status = acpi_get_table("DSDT", 0, &acpi_table);
	अगर (status != AE_OK)
		pr_warn("DSDT table not found for OEM information\n");
	अन्यथा अणु
		crat_table->oem_revision = acpi_table->revision;
		स_नकल(crat_table->oem_id, acpi_table->oem_id,
				CRAT_OEMID_LENGTH);
		स_नकल(crat_table->oem_table_id, acpi_table->oem_table_id,
				CRAT_OEMTABLEID_LENGTH);
		acpi_put_table(acpi_table);
	पूर्ण
	crat_table->total_entries = 0;
	crat_table->num_करोमुख्यs = 0;

	sub_type_hdr = (काष्ठा crat_subtype_generic *)(crat_table+1);

	क्रम_each_online_node(numa_node_id) अणु
		अगर (kfd_numa_node_to_apic_id(numa_node_id) == -1)
			जारी;

		/* Fill in Subtype: Compute Unit */
		ret = kfd_fill_cu_क्रम_cpu(numa_node_id, &avail_size,
			crat_table->num_करोमुख्यs,
			(काष्ठा crat_subtype_computeunit *)sub_type_hdr);
		अगर (ret < 0)
			वापस ret;
		crat_table->length += sub_type_hdr->length;
		crat_table->total_entries++;

		sub_type_hdr = (typeof(sub_type_hdr))((अक्षर *)sub_type_hdr +
			sub_type_hdr->length);

		/* Fill in Subtype: Memory */
		ret = kfd_fill_mem_info_क्रम_cpu(numa_node_id, &avail_size,
			crat_table->num_करोमुख्यs,
			(काष्ठा crat_subtype_memory *)sub_type_hdr);
		अगर (ret < 0)
			वापस ret;
		crat_table->length += sub_type_hdr->length;
		crat_table->total_entries++;

		sub_type_hdr = (typeof(sub_type_hdr))((अक्षर *)sub_type_hdr +
			sub_type_hdr->length);

		/* Fill in Subtype: IO Link */
#अगर_घोषित CONFIG_X86_64
		ret = kfd_fill_iolink_info_क्रम_cpu(numa_node_id, &avail_size,
				&entries,
				(काष्ठा crat_subtype_iolink *)sub_type_hdr);
		अगर (ret < 0)
			वापस ret;

		अगर (entries) अणु
			crat_table->length += (sub_type_hdr->length * entries);
			crat_table->total_entries += entries;

			sub_type_hdr = (typeof(sub_type_hdr))((अक्षर *)sub_type_hdr +
					sub_type_hdr->length * entries);
		पूर्ण
#अन्यथा
		pr_info("IO link not available for non x86 platforms\n");
#पूर्ण_अगर

		crat_table->num_करोमुख्यs++;
	पूर्ण

	/* TODO: Add cache Subtype क्रम CPU.
	 * Currently, CPU cache inक्रमmation is available in function
	 * detect_cache_attributes(cpu) defined in the file
	 * ./arch/x86/kernel/cpu/पूर्णांकel_cacheinfo.c. This function is not
	 * exported and to get the same inक्रमmation the code needs to be
	 * duplicated.
	 */

	*size = crat_table->length;
	pr_info("Virtual CRAT table created for CPU\n");

	वापस 0;
पूर्ण

अटल पूर्णांक kfd_fill_gpu_memory_affinity(पूर्णांक *avail_size,
		काष्ठा kfd_dev *kdev, uपूर्णांक8_t type, uपूर्णांक64_t size,
		काष्ठा crat_subtype_memory *sub_type_hdr,
		uपूर्णांक32_t proximity_करोमुख्य,
		स्थिर काष्ठा kfd_local_mem_info *local_mem_info)
अणु
	*avail_size -= माप(काष्ठा crat_subtype_memory);
	अगर (*avail_size < 0)
		वापस -ENOMEM;

	स_रखो((व्योम *)sub_type_hdr, 0, माप(काष्ठा crat_subtype_memory));
	sub_type_hdr->type = CRAT_SUBTYPE_MEMORY_AFFINITY;
	sub_type_hdr->length = माप(काष्ठा crat_subtype_memory);
	sub_type_hdr->flags |= CRAT_SUBTYPE_FLAGS_ENABLED;

	sub_type_hdr->proximity_करोमुख्य = proximity_करोमुख्य;

	pr_debug("Fill gpu memory affinity - type 0x%x size 0x%llx\n",
			type, size);

	sub_type_hdr->length_low = lower_32_bits(size);
	sub_type_hdr->length_high = upper_32_bits(size);

	sub_type_hdr->width = local_mem_info->vram_width;
	sub_type_hdr->visibility_type = type;

	वापस 0;
पूर्ण

/* kfd_fill_gpu_direct_io_link - Fill in direct io link from GPU
 * to its NUMA node
 *	@avail_size: Available size in the memory
 *	@kdev - [IN] GPU device
 *	@sub_type_hdr: Memory पूर्णांकo which io link info will be filled in
 *	@proximity_करोमुख्य - proximity करोमुख्य of the GPU node
 *
 *	Return 0 अगर successful अन्यथा वापस -ve value
 */
अटल पूर्णांक kfd_fill_gpu_direct_io_link_to_cpu(पूर्णांक *avail_size,
			काष्ठा kfd_dev *kdev,
			काष्ठा crat_subtype_iolink *sub_type_hdr,
			uपूर्णांक32_t proximity_करोमुख्य)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kdev->kgd;

	*avail_size -= माप(काष्ठा crat_subtype_iolink);
	अगर (*avail_size < 0)
		वापस -ENOMEM;

	स_रखो((व्योम *)sub_type_hdr, 0, माप(काष्ठा crat_subtype_iolink));

	/* Fill in subtype header data */
	sub_type_hdr->type = CRAT_SUBTYPE_IOLINK_AFFINITY;
	sub_type_hdr->length = माप(काष्ठा crat_subtype_iolink);
	sub_type_hdr->flags |= CRAT_SUBTYPE_FLAGS_ENABLED;
	अगर (kfd_dev_is_large_bar(kdev))
		sub_type_hdr->flags |= CRAT_IOLINK_FLAGS_BI_सूचीECTIONAL;

	/* Fill in IOLINK subtype.
	 * TODO: Fill-in other fields of iolink subtype
	 */
	अगर (adev->gmc.xgmi.connected_to_cpu) अणु
		/*
		 * with host gpu xgmi link, host can access gpu memory whether
		 * or not pcie bar type is large, so always create bidirectional
		 * io link.
		 */
		sub_type_hdr->flags |= CRAT_IOLINK_FLAGS_BI_सूचीECTIONAL;
		sub_type_hdr->io_पूर्णांकerface_type = CRAT_IOLINK_TYPE_XGMI;
	पूर्ण अन्यथा अणु
		sub_type_hdr->io_पूर्णांकerface_type = CRAT_IOLINK_TYPE_PCIEXPRESS;
	पूर्ण

	sub_type_hdr->proximity_करोमुख्य_from = proximity_करोमुख्य;
#अगर_घोषित CONFIG_NUMA
	अगर (kdev->pdev->dev.numa_node == NUMA_NO_NODE)
		sub_type_hdr->proximity_करोमुख्य_to = 0;
	अन्यथा
		sub_type_hdr->proximity_करोमुख्य_to = kdev->pdev->dev.numa_node;
#अन्यथा
	sub_type_hdr->proximity_करोमुख्य_to = 0;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक kfd_fill_gpu_xgmi_link_to_gpu(पूर्णांक *avail_size,
			काष्ठा kfd_dev *kdev,
			काष्ठा kfd_dev *peer_kdev,
			काष्ठा crat_subtype_iolink *sub_type_hdr,
			uपूर्णांक32_t proximity_करोमुख्य_from,
			uपूर्णांक32_t proximity_करोमुख्य_to)
अणु
	*avail_size -= माप(काष्ठा crat_subtype_iolink);
	अगर (*avail_size < 0)
		वापस -ENOMEM;

	स_रखो((व्योम *)sub_type_hdr, 0, माप(काष्ठा crat_subtype_iolink));

	sub_type_hdr->type = CRAT_SUBTYPE_IOLINK_AFFINITY;
	sub_type_hdr->length = माप(काष्ठा crat_subtype_iolink);
	sub_type_hdr->flags |= CRAT_SUBTYPE_FLAGS_ENABLED |
			       CRAT_IOLINK_FLAGS_BI_सूचीECTIONAL;

	sub_type_hdr->io_पूर्णांकerface_type = CRAT_IOLINK_TYPE_XGMI;
	sub_type_hdr->proximity_करोमुख्य_from = proximity_करोमुख्य_from;
	sub_type_hdr->proximity_करोमुख्य_to = proximity_करोमुख्य_to;
	sub_type_hdr->num_hops_xgmi =
		amdgpu_amdkfd_get_xgmi_hops_count(kdev->kgd, peer_kdev->kgd);
	वापस 0;
पूर्ण

/* kfd_create_vcrat_image_gpu - Create Virtual CRAT क्रम CPU
 *
 *	@pcrat_image: Fill in VCRAT क्रम GPU
 *	@size:	[IN] allocated size of crat_image.
 *		[OUT] actual size of data filled in crat_image
 */
अटल पूर्णांक kfd_create_vcrat_image_gpu(व्योम *pcrat_image,
				      माप_प्रकार *size, काष्ठा kfd_dev *kdev,
				      uपूर्णांक32_t proximity_करोमुख्य)
अणु
	काष्ठा crat_header *crat_table = (काष्ठा crat_header *)pcrat_image;
	काष्ठा crat_subtype_generic *sub_type_hdr;
	काष्ठा kfd_local_mem_info local_mem_info;
	काष्ठा kfd_topology_device *peer_dev;
	काष्ठा crat_subtype_computeunit *cu;
	काष्ठा kfd_cu_info cu_info;
	पूर्णांक avail_size = *size;
	uपूर्णांक32_t total_num_of_cu;
	पूर्णांक num_of_cache_entries = 0;
	पूर्णांक cache_mem_filled = 0;
	uपूर्णांक32_t nid = 0;
	पूर्णांक ret = 0;

	अगर (!pcrat_image || avail_size < VCRAT_SIZE_FOR_GPU)
		वापस -EINVAL;

	/* Fill the CRAT Header.
	 * Modअगरy length and total_entries as subunits are added.
	 */
	avail_size -= माप(काष्ठा crat_header);
	अगर (avail_size < 0)
		वापस -ENOMEM;

	स_रखो(crat_table, 0, माप(काष्ठा crat_header));

	स_नकल(&crat_table->signature, CRAT_SIGNATURE,
			माप(crat_table->signature));
	/* Change length as we add more subtypes*/
	crat_table->length = माप(काष्ठा crat_header);
	crat_table->num_करोमुख्यs = 1;
	crat_table->total_entries = 0;

	/* Fill in Subtype: Compute Unit
	 * First fill in the sub type header and then sub type data
	 */
	avail_size -= माप(काष्ठा crat_subtype_computeunit);
	अगर (avail_size < 0)
		वापस -ENOMEM;

	sub_type_hdr = (काष्ठा crat_subtype_generic *)(crat_table + 1);
	स_रखो(sub_type_hdr, 0, माप(काष्ठा crat_subtype_computeunit));

	sub_type_hdr->type = CRAT_SUBTYPE_COMPUTEUNIT_AFFINITY;
	sub_type_hdr->length = माप(काष्ठा crat_subtype_computeunit);
	sub_type_hdr->flags = CRAT_SUBTYPE_FLAGS_ENABLED;

	/* Fill CU subtype data */
	cu = (काष्ठा crat_subtype_computeunit *)sub_type_hdr;
	cu->flags |= CRAT_CU_FLAGS_GPU_PRESENT;
	cu->proximity_करोमुख्य = proximity_करोमुख्य;

	amdgpu_amdkfd_get_cu_info(kdev->kgd, &cu_info);
	cu->num_simd_per_cu = cu_info.simd_per_cu;
	cu->num_simd_cores = cu_info.simd_per_cu * cu_info.cu_active_number;
	cu->max_waves_simd = cu_info.max_waves_per_simd;

	cu->wave_front_size = cu_info.wave_front_size;
	cu->array_count = cu_info.num_shader_arrays_per_engine *
		cu_info.num_shader_engines;
	total_num_of_cu = (cu->array_count * cu_info.num_cu_per_sh);
	cu->processor_id_low = get_and_inc_gpu_processor_id(total_num_of_cu);
	cu->num_cu_per_array = cu_info.num_cu_per_sh;
	cu->max_slots_scatch_cu = cu_info.max_scratch_slots_per_cu;
	cu->num_banks = cu_info.num_shader_engines;
	cu->lds_size_in_kb = cu_info.lds_size;

	cu->hsa_capability = 0;

	/* Check अगर this node supports IOMMU. During parsing this flag will
	 * translate to HSA_CAP_ATS_PRESENT
	 */
	अगर (!kfd_iommu_check_device(kdev))
		cu->hsa_capability |= CRAT_CU_FLAGS_IOMMU_PRESENT;

	crat_table->length += sub_type_hdr->length;
	crat_table->total_entries++;

	/* Fill in Subtype: Memory. Only on प्रणालीs with large BAR (no
	 * निजी FB), report memory as खुला. On other प्रणालीs
	 * report the total FB size (खुला+निजी) as a single
	 * निजी heap.
	 */
	amdgpu_amdkfd_get_local_mem_info(kdev->kgd, &local_mem_info);
	sub_type_hdr = (typeof(sub_type_hdr))((अक्षर *)sub_type_hdr +
			sub_type_hdr->length);

	अगर (debug_largebar)
		local_mem_info.local_mem_size_निजी = 0;

	अगर (local_mem_info.local_mem_size_निजी == 0)
		ret = kfd_fill_gpu_memory_affinity(&avail_size,
				kdev, HSA_MEM_HEAP_TYPE_FB_PUBLIC,
				local_mem_info.local_mem_size_खुला,
				(काष्ठा crat_subtype_memory *)sub_type_hdr,
				proximity_करोमुख्य,
				&local_mem_info);
	अन्यथा
		ret = kfd_fill_gpu_memory_affinity(&avail_size,
				kdev, HSA_MEM_HEAP_TYPE_FB_PRIVATE,
				local_mem_info.local_mem_size_खुला +
				local_mem_info.local_mem_size_निजी,
				(काष्ठा crat_subtype_memory *)sub_type_hdr,
				proximity_करोमुख्य,
				&local_mem_info);
	अगर (ret < 0)
		वापस ret;

	crat_table->length += माप(काष्ठा crat_subtype_memory);
	crat_table->total_entries++;

	/* TODO: Fill in cache inक्रमmation. This inक्रमmation is NOT पढ़ोily
	 * available in KGD
	 */
	sub_type_hdr = (typeof(sub_type_hdr))((अक्षर *)sub_type_hdr +
		sub_type_hdr->length);
	ret = kfd_fill_gpu_cache_info(kdev, cu->processor_id_low,
				avail_size,
				&cu_info,
				(काष्ठा crat_subtype_cache *)sub_type_hdr,
				&cache_mem_filled,
				&num_of_cache_entries);

	अगर (ret < 0)
		वापस ret;

	crat_table->length += cache_mem_filled;
	crat_table->total_entries += num_of_cache_entries;
	avail_size -= cache_mem_filled;

	/* Fill in Subtype: IO_LINKS
	 *  Only direct links are added here which is Link from GPU to
	 *  to its NUMA node. Indirect links are added by userspace.
	 */
	sub_type_hdr = (typeof(sub_type_hdr))((अक्षर *)sub_type_hdr +
		cache_mem_filled);
	ret = kfd_fill_gpu_direct_io_link_to_cpu(&avail_size, kdev,
		(काष्ठा crat_subtype_iolink *)sub_type_hdr, proximity_करोमुख्य);

	अगर (ret < 0)
		वापस ret;

	crat_table->length += sub_type_hdr->length;
	crat_table->total_entries++;


	/* Fill in Subtype: IO_LINKS
	 * Direct links from GPU to other GPUs through xGMI.
	 * We will loop GPUs that alपढ़ोy be processed (with lower value
	 * of proximity_करोमुख्य), add the link क्रम the GPUs with same
	 * hive id (from this GPU to other GPU) . The reversed iolink
	 * (from other GPU to this GPU) will be added
	 * in kfd_parse_subtype_iolink.
	 */
	अगर (kdev->hive_id) अणु
		क्रम (nid = 0; nid < proximity_करोमुख्य; ++nid) अणु
			peer_dev = kfd_topology_device_by_proximity_करोमुख्य(nid);
			अगर (!peer_dev->gpu)
				जारी;
			अगर (peer_dev->gpu->hive_id != kdev->hive_id)
				जारी;
			sub_type_hdr = (typeof(sub_type_hdr))(
				(अक्षर *)sub_type_hdr +
				माप(काष्ठा crat_subtype_iolink));
			ret = kfd_fill_gpu_xgmi_link_to_gpu(
				&avail_size, kdev, peer_dev->gpu,
				(काष्ठा crat_subtype_iolink *)sub_type_hdr,
				proximity_करोमुख्य, nid);
			अगर (ret < 0)
				वापस ret;
			crat_table->length += sub_type_hdr->length;
			crat_table->total_entries++;
		पूर्ण
	पूर्ण
	*size = crat_table->length;
	pr_info("Virtual CRAT table created for GPU\n");

	वापस ret;
पूर्ण

/* kfd_create_crat_image_भव - Allocates memory क्रम CRAT image and
 *		creates a Virtual CRAT (VCRAT) image
 *
 * NOTE: Call kfd_destroy_crat_image to मुक्त CRAT image memory
 *
 *	@crat_image: VCRAT image created because ACPI करोes not have a
 *		     CRAT क्रम this device
 *	@size: [OUT] size of भव crat_image
 *	@flags:	COMPUTE_UNIT_CPU - Create VCRAT क्रम CPU device
 *		COMPUTE_UNIT_GPU - Create VCRAT क्रम GPU
 *		(COMPUTE_UNIT_CPU | COMPUTE_UNIT_GPU) - Create VCRAT क्रम APU
 *			-- this option is not currently implemented.
 *			The assumption is that all AMD APUs will have CRAT
 *	@kdev: Valid kfd_device required अगर flags contain COMPUTE_UNIT_GPU
 *
 *	Return 0 अगर successful अन्यथा वापस -ve value
 */
पूर्णांक kfd_create_crat_image_भव(व्योम **crat_image, माप_प्रकार *size,
				  पूर्णांक flags, काष्ठा kfd_dev *kdev,
				  uपूर्णांक32_t proximity_करोमुख्य)
अणु
	व्योम *pcrat_image = शून्य;
	पूर्णांक ret = 0, num_nodes;
	माप_प्रकार dyn_size;

	अगर (!crat_image)
		वापस -EINVAL;

	*crat_image = शून्य;

	/* Allocate the CPU Virtual CRAT size based on the number of online
	 * nodes. Allocate VCRAT_SIZE_FOR_GPU क्रम GPU भव CRAT image.
	 * This should cover all the current conditions. A check is put not
	 * to overग_लिखो beyond allocated size क्रम GPUs
	 */
	चयन (flags) अणु
	हाल COMPUTE_UNIT_CPU:
		num_nodes = num_online_nodes();
		dyn_size = माप(काष्ठा crat_header) +
			num_nodes * (माप(काष्ठा crat_subtype_computeunit) +
			माप(काष्ठा crat_subtype_memory) +
			(num_nodes - 1) * माप(काष्ठा crat_subtype_iolink));
		pcrat_image = kvदो_स्मृति(dyn_size, GFP_KERNEL);
		अगर (!pcrat_image)
			वापस -ENOMEM;
		*size = dyn_size;
		pr_debug("CRAT size is %ld", dyn_size);
		ret = kfd_create_vcrat_image_cpu(pcrat_image, size);
		अवरोध;
	हाल COMPUTE_UNIT_GPU:
		अगर (!kdev)
			वापस -EINVAL;
		pcrat_image = kvदो_स्मृति(VCRAT_SIZE_FOR_GPU, GFP_KERNEL);
		अगर (!pcrat_image)
			वापस -ENOMEM;
		*size = VCRAT_SIZE_FOR_GPU;
		ret = kfd_create_vcrat_image_gpu(pcrat_image, size, kdev,
						 proximity_करोमुख्य);
		अवरोध;
	हाल (COMPUTE_UNIT_CPU | COMPUTE_UNIT_GPU):
		/* TODO: */
		ret = -EINVAL;
		pr_err("VCRAT not implemented for APU\n");
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (!ret)
		*crat_image = pcrat_image;
	अन्यथा
		kvमुक्त(pcrat_image);

	वापस ret;
पूर्ण


/* kfd_destroy_crat_image
 *
 *	@crat_image: [IN] - crat_image from kfd_create_crat_image_xxx(..)
 *
 */
व्योम kfd_destroy_crat_image(व्योम *crat_image)
अणु
	kvमुक्त(crat_image);
पूर्ण
