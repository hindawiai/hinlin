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

#अगर_अघोषित KFD_CRAT_H_INCLUDED
#घोषणा KFD_CRAT_H_INCLUDED

#समावेश <linux/types.h>

#आशय pack(1)

/*
 * 4CC signature values क्रम the CRAT and CDIT ACPI tables
 */

#घोषणा CRAT_SIGNATURE	"CRAT"
#घोषणा CDIT_SIGNATURE	"CDIT"

/*
 * Component Resource Association Table (CRAT)
 */

#घोषणा CRAT_OEMID_LENGTH	6
#घोषणा CRAT_OEMTABLEID_LENGTH	8
#घोषणा CRAT_RESERVED_LENGTH	6

#घोषणा CRAT_OEMID_64BIT_MASK ((1ULL << (CRAT_OEMID_LENGTH * 8)) - 1)

/* Compute Unit flags */
#घोषणा COMPUTE_UNIT_CPU	(1 << 0)  /* Create Virtual CRAT क्रम CPU */
#घोषणा COMPUTE_UNIT_GPU	(1 << 1)  /* Create Virtual CRAT क्रम GPU */

काष्ठा crat_header अणु
	uपूर्णांक32_t	signature;
	uपूर्णांक32_t	length;
	uपूर्णांक8_t		revision;
	uपूर्णांक8_t		checksum;
	uपूर्णांक8_t		oem_id[CRAT_OEMID_LENGTH];
	uपूर्णांक8_t		oem_table_id[CRAT_OEMTABLEID_LENGTH];
	uपूर्णांक32_t	oem_revision;
	uपूर्णांक32_t	creator_id;
	uपूर्णांक32_t	creator_revision;
	uपूर्णांक32_t	total_entries;
	uपूर्णांक16_t	num_करोमुख्यs;
	uपूर्णांक8_t		reserved[CRAT_RESERVED_LENGTH];
पूर्ण;

/*
 * The header काष्ठाure is immediately followed by total_entries of the
 * data definitions
 */

/*
 * The currently defined subtype entries in the CRAT
 */
#घोषणा CRAT_SUBTYPE_COMPUTEUNIT_AFFINITY	0
#घोषणा CRAT_SUBTYPE_MEMORY_AFFINITY		1
#घोषणा CRAT_SUBTYPE_CACHE_AFFINITY		2
#घोषणा CRAT_SUBTYPE_TLB_AFFINITY		3
#घोषणा CRAT_SUBTYPE_CCOMPUTE_AFFINITY		4
#घोषणा CRAT_SUBTYPE_IOLINK_AFFINITY		5
#घोषणा CRAT_SUBTYPE_MAX			6

#घोषणा CRAT_SIBLINGMAP_SIZE	32

/*
 * ComputeUnit Affinity काष्ठाure and definitions
 */
#घोषणा CRAT_CU_FLAGS_ENABLED		0x00000001
#घोषणा CRAT_CU_FLAGS_HOT_PLUGGABLE	0x00000002
#घोषणा CRAT_CU_FLAGS_CPU_PRESENT	0x00000004
#घोषणा CRAT_CU_FLAGS_GPU_PRESENT	0x00000008
#घोषणा CRAT_CU_FLAGS_IOMMU_PRESENT	0x00000010
#घोषणा CRAT_CU_FLAGS_RESERVED		0xffffffe0

#घोषणा CRAT_COMPUTEUNIT_RESERVED_LENGTH 4

काष्ठा crat_subtype_computeunit अणु
	uपूर्णांक8_t		type;
	uपूर्णांक8_t		length;
	uपूर्णांक16_t	reserved;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	proximity_करोमुख्य;
	uपूर्णांक32_t	processor_id_low;
	uपूर्णांक16_t	num_cpu_cores;
	uपूर्णांक16_t	num_simd_cores;
	uपूर्णांक16_t	max_waves_simd;
	uपूर्णांक16_t	io_count;
	uपूर्णांक16_t	hsa_capability;
	uपूर्णांक16_t	lds_size_in_kb;
	uपूर्णांक8_t		wave_front_size;
	uपूर्णांक8_t		num_banks;
	uपूर्णांक16_t	micro_engine_id;
	uपूर्णांक8_t		array_count;
	uपूर्णांक8_t		num_cu_per_array;
	uपूर्णांक8_t		num_simd_per_cu;
	uपूर्णांक8_t		max_slots_scatch_cu;
	uपूर्णांक8_t		reserved2[CRAT_COMPUTEUNIT_RESERVED_LENGTH];
पूर्ण;

/*
 * HSA Memory Affinity काष्ठाure and definitions
 */
#घोषणा CRAT_MEM_FLAGS_ENABLED		0x00000001
#घोषणा CRAT_MEM_FLAGS_HOT_PLUGGABLE	0x00000002
#घोषणा CRAT_MEM_FLAGS_NON_VOLATILE	0x00000004
#घोषणा CRAT_MEM_FLAGS_RESERVED		0xfffffff8

#घोषणा CRAT_MEMORY_RESERVED_LENGTH 8

काष्ठा crat_subtype_memory अणु
	uपूर्णांक8_t		type;
	uपूर्णांक8_t		length;
	uपूर्णांक16_t	reserved;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	proximity_करोमुख्य;
	uपूर्णांक32_t	base_addr_low;
	uपूर्णांक32_t	base_addr_high;
	uपूर्णांक32_t	length_low;
	uपूर्णांक32_t	length_high;
	uपूर्णांक32_t	width;
	uपूर्णांक8_t		visibility_type; /* क्रम भव (dGPU) CRAT */
	uपूर्णांक8_t		reserved2[CRAT_MEMORY_RESERVED_LENGTH - 1];
पूर्ण;

/*
 * HSA Cache Affinity काष्ठाure and definitions
 */
#घोषणा CRAT_CACHE_FLAGS_ENABLED	0x00000001
#घोषणा CRAT_CACHE_FLAGS_DATA_CACHE	0x00000002
#घोषणा CRAT_CACHE_FLAGS_INST_CACHE	0x00000004
#घोषणा CRAT_CACHE_FLAGS_CPU_CACHE	0x00000008
#घोषणा CRAT_CACHE_FLAGS_SIMD_CACHE	0x00000010
#घोषणा CRAT_CACHE_FLAGS_RESERVED	0xffffffe0

#घोषणा CRAT_CACHE_RESERVED_LENGTH 8

काष्ठा crat_subtype_cache अणु
	uपूर्णांक8_t		type;
	uपूर्णांक8_t		length;
	uपूर्णांक16_t	reserved;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	processor_id_low;
	uपूर्णांक8_t		sibling_map[CRAT_SIBLINGMAP_SIZE];
	uपूर्णांक32_t	cache_size;
	uपूर्णांक8_t		cache_level;
	uपूर्णांक8_t		lines_per_tag;
	uपूर्णांक16_t	cache_line_size;
	uपूर्णांक8_t		associativity;
	uपूर्णांक8_t		cache_properties;
	uपूर्णांक16_t	cache_latency;
	uपूर्णांक8_t		reserved2[CRAT_CACHE_RESERVED_LENGTH];
पूर्ण;

/*
 * HSA TLB Affinity काष्ठाure and definitions
 */
#घोषणा CRAT_TLB_FLAGS_ENABLED	0x00000001
#घोषणा CRAT_TLB_FLAGS_DATA_TLB	0x00000002
#घोषणा CRAT_TLB_FLAGS_INST_TLB	0x00000004
#घोषणा CRAT_TLB_FLAGS_CPU_TLB	0x00000008
#घोषणा CRAT_TLB_FLAGS_SIMD_TLB	0x00000010
#घोषणा CRAT_TLB_FLAGS_RESERVED	0xffffffe0

#घोषणा CRAT_TLB_RESERVED_LENGTH 4

काष्ठा crat_subtype_tlb अणु
	uपूर्णांक8_t		type;
	uपूर्णांक8_t		length;
	uपूर्णांक16_t	reserved;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	processor_id_low;
	uपूर्णांक8_t		sibling_map[CRAT_SIBLINGMAP_SIZE];
	uपूर्णांक32_t	tlb_level;
	uपूर्णांक8_t		data_tlb_associativity_2mb;
	uपूर्णांक8_t		data_tlb_size_2mb;
	uपूर्णांक8_t		inकाष्ठाion_tlb_associativity_2mb;
	uपूर्णांक8_t		inकाष्ठाion_tlb_size_2mb;
	uपूर्णांक8_t		data_tlb_associativity_4k;
	uपूर्णांक8_t		data_tlb_size_4k;
	uपूर्णांक8_t		inकाष्ठाion_tlb_associativity_4k;
	uपूर्णांक8_t		inकाष्ठाion_tlb_size_4k;
	uपूर्णांक8_t		data_tlb_associativity_1gb;
	uपूर्णांक8_t		data_tlb_size_1gb;
	uपूर्णांक8_t		inकाष्ठाion_tlb_associativity_1gb;
	uपूर्णांक8_t		inकाष्ठाion_tlb_size_1gb;
	uपूर्णांक8_t		reserved2[CRAT_TLB_RESERVED_LENGTH];
पूर्ण;

/*
 * HSA CCompute/APU Affinity काष्ठाure and definitions
 */
#घोषणा CRAT_CCOMPUTE_FLAGS_ENABLED	0x00000001
#घोषणा CRAT_CCOMPUTE_FLAGS_RESERVED	0xfffffffe

#घोषणा CRAT_CCOMPUTE_RESERVED_LENGTH 16

काष्ठा crat_subtype_ccompute अणु
	uपूर्णांक8_t		type;
	uपूर्णांक8_t		length;
	uपूर्णांक16_t	reserved;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	processor_id_low;
	uपूर्णांक8_t		sibling_map[CRAT_SIBLINGMAP_SIZE];
	uपूर्णांक32_t	apu_size;
	uपूर्णांक8_t		reserved2[CRAT_CCOMPUTE_RESERVED_LENGTH];
पूर्ण;

/*
 * HSA IO Link Affinity काष्ठाure and definitions
 */
#घोषणा CRAT_IOLINK_FLAGS_ENABLED		(1 << 0)
#घोषणा CRAT_IOLINK_FLAGS_NON_COHERENT		(1 << 1)
#घोषणा CRAT_IOLINK_FLAGS_NO_ATOMICS_32_BIT	(1 << 2)
#घोषणा CRAT_IOLINK_FLAGS_NO_ATOMICS_64_BIT	(1 << 3)
#घोषणा CRAT_IOLINK_FLAGS_NO_PEER_TO_PEER_DMA	(1 << 4)
#घोषणा CRAT_IOLINK_FLAGS_BI_सूचीECTIONAL 	(1 << 31)
#घोषणा CRAT_IOLINK_FLAGS_RESERVED_MASK		0x7fffffe0

/*
 * IO पूर्णांकerface types
 */
#घोषणा CRAT_IOLINK_TYPE_UNDEFINED	0
#घोषणा CRAT_IOLINK_TYPE_HYPERTRANSPORT	1
#घोषणा CRAT_IOLINK_TYPE_PCIEXPRESS	2
#घोषणा CRAT_IOLINK_TYPE_AMBA		3
#घोषणा CRAT_IOLINK_TYPE_MIPI		4
#घोषणा CRAT_IOLINK_TYPE_QPI_1_1	5
#घोषणा CRAT_IOLINK_TYPE_RESERVED1	6
#घोषणा CRAT_IOLINK_TYPE_RESERVED2	7
#घोषणा CRAT_IOLINK_TYPE_RAPID_IO	8
#घोषणा CRAT_IOLINK_TYPE_INFINIBAND	9
#घोषणा CRAT_IOLINK_TYPE_RESERVED3	10
#घोषणा CRAT_IOLINK_TYPE_XGMI		11
#घोषणा CRAT_IOLINK_TYPE_XGOP		12
#घोषणा CRAT_IOLINK_TYPE_GZ		13
#घोषणा CRAT_IOLINK_TYPE_ETHERNET_RDMA	14
#घोषणा CRAT_IOLINK_TYPE_RDMA_OTHER	15
#घोषणा CRAT_IOLINK_TYPE_OTHER		16
#घोषणा CRAT_IOLINK_TYPE_MAX		255

#घोषणा CRAT_IOLINK_RESERVED_LENGTH	24

काष्ठा crat_subtype_iolink अणु
	uपूर्णांक8_t		type;
	uपूर्णांक8_t		length;
	uपूर्णांक16_t	reserved;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	proximity_करोमुख्य_from;
	uपूर्णांक32_t	proximity_करोमुख्य_to;
	uपूर्णांक8_t		io_पूर्णांकerface_type;
	uपूर्णांक8_t		version_major;
	uपूर्णांक16_t	version_minor;
	uपूर्णांक32_t	minimum_latency;
	uपूर्णांक32_t	maximum_latency;
	uपूर्णांक32_t	minimum_bandwidth_mbs;
	uपूर्णांक32_t	maximum_bandwidth_mbs;
	uपूर्णांक32_t	recommended_transfer_size;
	uपूर्णांक8_t		reserved2[CRAT_IOLINK_RESERVED_LENGTH - 1];
	uपूर्णांक8_t		num_hops_xgmi;
पूर्ण;

/*
 * HSA generic sub-type header
 */

#घोषणा CRAT_SUBTYPE_FLAGS_ENABLED 0x00000001

काष्ठा crat_subtype_generic अणु
	uपूर्णांक8_t		type;
	uपूर्णांक8_t		length;
	uपूर्णांक16_t	reserved;
	uपूर्णांक32_t	flags;
पूर्ण;

/*
 * Component Locality Distance Inक्रमmation Table (CDIT)
 */
#घोषणा CDIT_OEMID_LENGTH	6
#घोषणा CDIT_OEMTABLEID_LENGTH	8

काष्ठा cdit_header अणु
	uपूर्णांक32_t	signature;
	uपूर्णांक32_t	length;
	uपूर्णांक8_t		revision;
	uपूर्णांक8_t		checksum;
	uपूर्णांक8_t		oem_id[CDIT_OEMID_LENGTH];
	uपूर्णांक8_t		oem_table_id[CDIT_OEMTABLEID_LENGTH];
	uपूर्णांक32_t	oem_revision;
	uपूर्णांक32_t	creator_id;
	uपूर्णांक32_t	creator_revision;
	uपूर्णांक32_t	total_entries;
	uपूर्णांक16_t	num_करोमुख्यs;
	uपूर्णांक8_t		entry[1];
पूर्ण;

#आशय pack()

काष्ठा kfd_dev;

पूर्णांक kfd_create_crat_image_acpi(व्योम **crat_image, माप_प्रकार *size);
व्योम kfd_destroy_crat_image(व्योम *crat_image);
पूर्णांक kfd_parse_crat_table(व्योम *crat_image, काष्ठा list_head *device_list,
			 uपूर्णांक32_t proximity_करोमुख्य);
पूर्णांक kfd_create_crat_image_भव(व्योम **crat_image, माप_प्रकार *size,
				  पूर्णांक flags, काष्ठा kfd_dev *kdev,
				  uपूर्णांक32_t proximity_करोमुख्य);

#पूर्ण_अगर /* KFD_CRAT_H_INCLUDED */
