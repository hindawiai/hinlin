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

#अगर_अघोषित __KFD_TOPOLOGY_H__
#घोषणा __KFD_TOPOLOGY_H__

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश "kfd_crat.h"

#घोषणा KFD_TOPOLOGY_PUBLIC_NAME_SIZE 32

#घोषणा HSA_CAP_HOT_PLUGGABLE			0x00000001
#घोषणा HSA_CAP_ATS_PRESENT			0x00000002
#घोषणा HSA_CAP_SHARED_WITH_GRAPHICS		0x00000004
#घोषणा HSA_CAP_QUEUE_SIZE_POW2			0x00000008
#घोषणा HSA_CAP_QUEUE_SIZE_32BIT		0x00000010
#घोषणा HSA_CAP_QUEUE_IDLE_EVENT		0x00000020
#घोषणा HSA_CAP_VA_LIMIT			0x00000040
#घोषणा HSA_CAP_WATCH_POINTS_SUPPORTED		0x00000080
#घोषणा HSA_CAP_WATCH_POINTS_TOTALBITS_MASK	0x00000f00
#घोषणा HSA_CAP_WATCH_POINTS_TOTALBITS_SHIFT	8
#घोषणा HSA_CAP_DOORBELL_TYPE_TOTALBITS_MASK	0x00003000
#घोषणा HSA_CAP_DOORBELL_TYPE_TOTALBITS_SHIFT	12

#घोषणा HSA_CAP_DOORBELL_TYPE_PRE_1_0		0x0
#घोषणा HSA_CAP_DOORBELL_TYPE_1_0		0x1
#घोषणा HSA_CAP_DOORBELL_TYPE_2_0		0x2
#घोषणा HSA_CAP_AQL_QUEUE_DOUBLE_MAP		0x00004000

#घोषणा HSA_CAP_RESERVED_WAS_SRAM_EDCSUPPORTED	0x00080000 /* Old buggy user mode depends on this being 0 */
#घोषणा HSA_CAP_MEM_EDCSUPPORTED		0x00100000
#घोषणा HSA_CAP_RASEVENTNOTIFY			0x00200000
#घोषणा HSA_CAP_ASIC_REVISION_MASK		0x03c00000
#घोषणा HSA_CAP_ASIC_REVISION_SHIFT		22
#घोषणा HSA_CAP_SRAM_EDCSUPPORTED		0x04000000

#घोषणा HSA_CAP_RESERVED			0xf80f8000

काष्ठा kfd_node_properties अणु
	uपूर्णांक64_t hive_id;
	uपूर्णांक32_t cpu_cores_count;
	uपूर्णांक32_t simd_count;
	uपूर्णांक32_t mem_banks_count;
	uपूर्णांक32_t caches_count;
	uपूर्णांक32_t io_links_count;
	uपूर्णांक32_t cpu_core_id_base;
	uपूर्णांक32_t simd_id_base;
	uपूर्णांक32_t capability;
	uपूर्णांक32_t max_waves_per_simd;
	uपूर्णांक32_t lds_size_in_kb;
	uपूर्णांक32_t gds_size_in_kb;
	uपूर्णांक32_t num_gws;
	uपूर्णांक32_t wave_front_size;
	uपूर्णांक32_t array_count;
	uपूर्णांक32_t simd_arrays_per_engine;
	uपूर्णांक32_t cu_per_simd_array;
	uपूर्णांक32_t simd_per_cu;
	uपूर्णांक32_t max_slots_scratch_cu;
	uपूर्णांक32_t engine_id;
	uपूर्णांक32_t venकरोr_id;
	uपूर्णांक32_t device_id;
	uपूर्णांक32_t location_id;
	uपूर्णांक32_t करोमुख्य;
	uपूर्णांक32_t max_engine_clk_fcompute;
	uपूर्णांक32_t max_engine_clk_ccompute;
	पूर्णांक32_t  drm_render_minor;
	uपूर्णांक32_t num_sdma_engines;
	uपूर्णांक32_t num_sdma_xgmi_engines;
	uपूर्णांक32_t num_sdma_queues_per_engine;
	uपूर्णांक32_t num_cp_queues;
	अक्षर name[KFD_TOPOLOGY_PUBLIC_NAME_SIZE];
पूर्ण;

#घोषणा HSA_MEM_HEAP_TYPE_SYSTEM	0
#घोषणा HSA_MEM_HEAP_TYPE_FB_PUBLIC	1
#घोषणा HSA_MEM_HEAP_TYPE_FB_PRIVATE	2
#घोषणा HSA_MEM_HEAP_TYPE_GPU_GDS	3
#घोषणा HSA_MEM_HEAP_TYPE_GPU_LDS	4
#घोषणा HSA_MEM_HEAP_TYPE_GPU_SCRATCH	5

#घोषणा HSA_MEM_FLAGS_HOT_PLUGGABLE	0x00000001
#घोषणा HSA_MEM_FLAGS_NON_VOLATILE	0x00000002
#घोषणा HSA_MEM_FLAGS_RESERVED		0xfffffffc

काष्ठा kfd_mem_properties अणु
	काष्ठा list_head	list;
	uपूर्णांक32_t		heap_type;
	uपूर्णांक64_t		size_in_bytes;
	uपूर्णांक32_t		flags;
	uपूर्णांक32_t		width;
	uपूर्णांक32_t		mem_clk_max;
	काष्ठा kfd_dev		*gpu;
	काष्ठा kobject		*kobj;
	काष्ठा attribute	attr;
पूर्ण;

#घोषणा HSA_CACHE_TYPE_DATA		0x00000001
#घोषणा HSA_CACHE_TYPE_INSTRUCTION	0x00000002
#घोषणा HSA_CACHE_TYPE_CPU		0x00000004
#घोषणा HSA_CACHE_TYPE_HSACU		0x00000008
#घोषणा HSA_CACHE_TYPE_RESERVED		0xfffffff0

काष्ठा kfd_cache_properties अणु
	काष्ठा list_head	list;
	uपूर्णांक32_t		processor_id_low;
	uपूर्णांक32_t		cache_level;
	uपूर्णांक32_t		cache_size;
	uपूर्णांक32_t		cacheline_size;
	uपूर्णांक32_t		cachelines_per_tag;
	uपूर्णांक32_t		cache_assoc;
	uपूर्णांक32_t		cache_latency;
	uपूर्णांक32_t		cache_type;
	uपूर्णांक8_t			sibling_map[CRAT_SIBLINGMAP_SIZE];
	काष्ठा kfd_dev		*gpu;
	काष्ठा kobject		*kobj;
	काष्ठा attribute	attr;
पूर्ण;

काष्ठा kfd_iolink_properties अणु
	काष्ठा list_head	list;
	uपूर्णांक32_t		iolink_type;
	uपूर्णांक32_t		ver_maj;
	uपूर्णांक32_t		ver_min;
	uपूर्णांक32_t		node_from;
	uपूर्णांक32_t		node_to;
	uपूर्णांक32_t		weight;
	uपूर्णांक32_t		min_latency;
	uपूर्णांक32_t		max_latency;
	uपूर्णांक32_t		min_bandwidth;
	uपूर्णांक32_t		max_bandwidth;
	uपूर्णांक32_t		rec_transfer_size;
	uपूर्णांक32_t		flags;
	काष्ठा kfd_dev		*gpu;
	काष्ठा kobject		*kobj;
	काष्ठा attribute	attr;
पूर्ण;

काष्ठा kfd_perf_properties अणु
	काष्ठा list_head	list;
	अक्षर			block_name[16];
	uपूर्णांक32_t		max_concurrent;
	काष्ठा attribute_group	*attr_group;
पूर्ण;

काष्ठा kfd_topology_device अणु
	काष्ठा list_head		list;
	uपूर्णांक32_t			gpu_id;
	uपूर्णांक32_t			proximity_करोमुख्य;
	काष्ठा kfd_node_properties	node_props;
	काष्ठा list_head		mem_props;
	uपूर्णांक32_t			cache_count;
	काष्ठा list_head		cache_props;
	uपूर्णांक32_t			io_link_count;
	काष्ठा list_head		io_link_props;
	काष्ठा list_head		perf_props;
	काष्ठा kfd_dev			*gpu;
	काष्ठा kobject			*kobj_node;
	काष्ठा kobject			*kobj_mem;
	काष्ठा kobject			*kobj_cache;
	काष्ठा kobject			*kobj_iolink;
	काष्ठा kobject			*kobj_perf;
	काष्ठा attribute		attr_gpuid;
	काष्ठा attribute		attr_name;
	काष्ठा attribute		attr_props;
	uपूर्णांक8_t				oem_id[CRAT_OEMID_LENGTH];
	uपूर्णांक8_t				oem_table_id[CRAT_OEMTABLEID_LENGTH];
	uपूर्णांक32_t			oem_revision;
पूर्ण;

काष्ठा kfd_प्रणाली_properties अणु
	uपूर्णांक32_t		num_devices;     /* Number of H-NUMA nodes */
	uपूर्णांक32_t		generation_count;
	uपूर्णांक64_t		platक्रमm_oem;
	uपूर्णांक64_t		platक्रमm_id;
	uपूर्णांक64_t		platक्रमm_rev;
	काष्ठा kobject		*kobj_topology;
	काष्ठा kobject		*kobj_nodes;
	काष्ठा attribute	attr_genid;
	काष्ठा attribute	attr_props;
पूर्ण;

काष्ठा kfd_topology_device *kfd_create_topology_device(
		काष्ठा list_head *device_list);
व्योम kfd_release_topology_device_list(काष्ठा list_head *device_list);

#पूर्ण_अगर /* __KFD_TOPOLOGY_H__ */
