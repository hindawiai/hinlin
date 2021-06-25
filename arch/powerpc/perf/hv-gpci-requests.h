<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश "req-gen/_begin.h"

/*
 * Based on the करोcument "getPerfCountInfo v1.07"
 */

/*
 * #घोषणा REQUEST_NAME counter_request_name
 * #घोषणा REQUEST_NUM r_num
 * #घोषणा REQUEST_IDX_KIND starting_index_kind
 * #समावेश I(REQUEST_BEGIN)
 * REQUEST(
 *	__field(...)
 *	__field(...)
 *	__array(...)
 *	__count(...)
 * )
 * #समावेश I(REQUEST_END)
 *
 * - starting_index_kind is one of the following, depending on the event:
 *
 *   hw_chip_id: hardware chip id or -1 क्रम current hw chip
 *   partition_id
 *   sibling_part_id,
 *   phys_processor_idx:
 *   0xffffffffffffffff: or -1, which means it is irrelavant क्रम the event
 *
 * __count(offset, bytes, name):
 *	a counter that should be exposed via perf
 * __field(offset, bytes, name)
 *	a normal field
 * __array(offset, bytes, name)
 *	an array of bytes
 *
 *
 *	@bytes क्रम __count, and __field _must_ be a numeral token
 *	in decimal, not an expression and not in hex.
 *
 *
 * TODO:
 *	- expose secondary index (अगर any counter ever uses it, only 0xA0
 *	  appears to use it right now, and it करोesn't have any counters)
 *	- embed versioning info
 *	- include counter descriptions
 */
#घोषणा REQUEST_NAME dispatch_समयbase_by_processor
#घोषणा REQUEST_NUM 0x10
#घोषणा REQUEST_IDX_KIND "phys_processor_idx=?"
#समावेश I(REQUEST_BEGIN)
REQUEST(__count(0,	8,	processor_समय_in_समयbase_cycles)
	__field(0x8,	4,	hw_processor_id)
	__field(0xC,	2,	owning_part_id)
	__field(0xE,	1,	processor_state)
	__field(0xF,	1,	version)
	__field(0x10,	4,	hw_chip_id)
	__field(0x14,	4,	phys_module_id)
	__field(0x18,	4,	primary_affinity_करोमुख्य_idx)
	__field(0x1C,	4,	secondary_affinity_करोमुख्य_idx)
	__field(0x20,	4,	processor_version)
	__field(0x24,	2,	logical_processor_idx)
	__field(0x26,	2,	reserved)
	__field(0x28,	4,	processor_id_रेजिस्टर)
	__field(0x2C,	4,	phys_processor_idx)
)
#समावेश I(REQUEST_END)

#घोषणा REQUEST_NAME entitled_capped_uncapped_करोnated_idle_समयbase_by_partition
#घोषणा REQUEST_NUM 0x20
#घोषणा REQUEST_IDX_KIND "sibling_part_id=?"
#समावेश I(REQUEST_BEGIN)
REQUEST(__field(0,	8,	partition_id)
	__count(0x8,	8,	entitled_cycles)
	__count(0x10,	8,	consumed_capped_cycles)
	__count(0x18,	8,	consumed_uncapped_cycles)
	__count(0x20,	8,	cycles_करोnated)
	__count(0x28,	8,	purr_idle_cycles)
)
#समावेश I(REQUEST_END)

/*
 * Not available क्रम counter_info_version >= 0x8, use
 * run_inकाष्ठाion_cycles_by_partition(0x100) instead.
 */
#घोषणा REQUEST_NAME run_inकाष्ठाions_run_cycles_by_partition
#घोषणा REQUEST_NUM 0x30
#घोषणा REQUEST_IDX_KIND "sibling_part_id=?"
#समावेश I(REQUEST_BEGIN)
REQUEST(__field(0,	8,	partition_id)
	__count(0x8,	8,	inकाष्ठाions_completed)
	__count(0x10,	8,	cycles)
)
#समावेश I(REQUEST_END)

#घोषणा REQUEST_NAME प्रणाली_perक्रमmance_capabilities
#घोषणा REQUEST_NUM 0x40
#घोषणा REQUEST_IDX_KIND "starting_index=0xffffffff"
#समावेश I(REQUEST_BEGIN)
REQUEST(__field(0,	1,	perf_collect_privileged)
	__field(0x1,	1,	capability_mask)
	__array(0x2,	0xE,	reserved)
)
#समावेश I(REQUEST_END)

#घोषणा REQUEST_NAME processor_bus_utilization_abc_links
#घोषणा REQUEST_NUM 0x50
#घोषणा REQUEST_IDX_KIND "hw_chip_id=?"
#समावेश I(REQUEST_BEGIN)
REQUEST(__field(0,	4,	hw_chip_id)
	__array(0x4,	0xC,	reserved1)
	__count(0x10,	8,	total_link_cycles)
	__count(0x18,	8,	idle_cycles_क्रम_a_link)
	__count(0x20,	8,	idle_cycles_क्रम_b_link)
	__count(0x28,	8,	idle_cycles_क्रम_c_link)
	__array(0x30,	0x20,	reserved2)
)
#समावेश I(REQUEST_END)

#घोषणा REQUEST_NAME processor_bus_utilization_wxyz_links
#घोषणा REQUEST_NUM 0x60
#घोषणा REQUEST_IDX_KIND "hw_chip_id=?"
#समावेश I(REQUEST_BEGIN)
REQUEST(__field(0,	4,	hw_chip_id)
	__array(0x4,	0xC,	reserved1)
	__count(0x10,	8,	total_link_cycles)
	__count(0x18,	8,	idle_cycles_क्रम_w_link)
	__count(0x20,	8,	idle_cycles_क्रम_x_link)
	__count(0x28,	8,	idle_cycles_क्रम_y_link)
	__count(0x30,	8,	idle_cycles_क्रम_z_link)
	__array(0x38,	0x28,	reserved2)
)
#समावेश I(REQUEST_END)

#घोषणा REQUEST_NAME processor_bus_utilization_gx_links
#घोषणा REQUEST_NUM 0x70
#घोषणा REQUEST_IDX_KIND "hw_chip_id=?"
#समावेश I(REQUEST_BEGIN)
REQUEST(__field(0,	4,	hw_chip_id)
	__array(0x4,	0xC,	reserved1)
	__count(0x10,	8,	gx0_in_address_cycles)
	__count(0x18,	8,	gx0_in_data_cycles)
	__count(0x20,	8,	gx0_in_retries)
	__count(0x28,	8,	gx0_in_bus_cycles)
	__count(0x30,	8,	gx0_in_cycles_total)
	__count(0x38,	8,	gx0_out_address_cycles)
	__count(0x40,	8,	gx0_out_data_cycles)
	__count(0x48,	8,	gx0_out_retries)
	__count(0x50,	8,	gx0_out_bus_cycles)
	__count(0x58,	8,	gx0_out_cycles_total)
	__count(0x60,	8,	gx1_in_address_cycles)
	__count(0x68,	8,	gx1_in_data_cycles)
	__count(0x70,	8,	gx1_in_retries)
	__count(0x78,	8,	gx1_in_bus_cycles)
	__count(0x80,	8,	gx1_in_cycles_total)
	__count(0x88,	8,	gx1_out_address_cycles)
	__count(0x90,	8,	gx1_out_data_cycles)
	__count(0x98,	8,	gx1_out_retries)
	__count(0xA0,	8,	gx1_out_bus_cycles)
	__count(0xA8,	8,	gx1_out_cycles_total)
)
#समावेश I(REQUEST_END)

#घोषणा REQUEST_NAME processor_bus_utilization_mc_links
#घोषणा REQUEST_NUM 0x80
#घोषणा REQUEST_IDX_KIND "hw_chip_id=?"
#समावेश I(REQUEST_BEGIN)
REQUEST(__field(0,	4,	hw_chip_id)
	__array(0x4,	0xC,	reserved1)
	__count(0x10,	8,	mc0_frames)
	__count(0x18,	8,	mc0_पढ़ोs)
	__count(0x20,	8,	mc0_ग_लिखो)
	__count(0x28,	8,	mc0_total_cycles)
	__count(0x30,	8,	mc1_frames)
	__count(0x38,	8,	mc1_पढ़ोs)
	__count(0x40,	8,	mc1_ग_लिखोs)
	__count(0x48,	8,	mc1_total_cycles)
)
#समावेश I(REQUEST_END)

/* Processor_config (0x90) skipped, no counters */
/* Current_processor_frequency (0x91) skipped, no counters */

#घोषणा REQUEST_NAME processor_core_utilization
#घोषणा REQUEST_NUM 0x94
#घोषणा REQUEST_IDX_KIND "phys_processor_idx=?"
#समावेश I(REQUEST_BEGIN)
REQUEST(__field(0,	4,	phys_processor_idx)
	__field(0x4,	4,	hw_processor_id)
	__count(0x8,	8,	cycles_across_any_thपढ़ो)
	__count(0x10,	8,	समयbase_at_collection)
	__count(0x18,	8,	purr_cycles)
	__count(0x20,	8,	sum_of_cycles_across_all_thपढ़ोs)
	__count(0x28,	8,	inकाष्ठाions_completed)
)
#समावेश I(REQUEST_END)

/* Processor_core_घातer_mode (0x95) skipped, no counters */
/* Affinity_करोमुख्य_inक्रमmation_by_भव_processor (0xA0) skipped,
 *	no counters */
/* Affinity_करोमुख्य_inक्रमmation_by_करोमुख्य (0xB0) skipped, no counters */
/* Affinity_करोमुख्य_inक्रमmation_by_partition (0xB1) skipped, no counters */
/* Physical_memory_info (0xC0) skipped, no counters */
/* Processor_bus_topology (0xD0) skipped, no counters */

#घोषणा REQUEST_NAME partition_hypervisor_queuing_बार
#घोषणा REQUEST_NUM 0xE0
#घोषणा REQUEST_IDX_KIND "partition_id=?"
#समावेश I(REQUEST_BEGIN)
REQUEST(__field(0,	2, partition_id)
	__array(0x2,	6, reserved1)
	__count(0x8,	8, समय_रुकोing_क्रम_entitlement)
	__count(0x10,	8, बार_रुकोed_क्रम_entitlement)
	__count(0x18,	8, समय_रुकोing_क्रम_phys_processor)
	__count(0x20,	8, बार_रुकोed_क्रम_phys_processor)
	__count(0x28,	8, dispatches_on_home_core)
	__count(0x30,	8, dispatches_on_home_primary_affinity_करोमुख्य)
	__count(0x38,	8, dispatches_on_home_secondary_affinity_करोमुख्य)
	__count(0x40,	8, dispatches_off_home_secondary_affinity_करोमुख्य)
	__count(0x48,	8, dispatches_on_dedicated_processor_करोnating_cycles)
)
#समावेश I(REQUEST_END)

#घोषणा REQUEST_NAME प्रणाली_hypervisor_बार
#घोषणा REQUEST_NUM 0xF0
#घोषणा REQUEST_IDX_KIND "starting_index=0xffffffff"
#समावेश I(REQUEST_BEGIN)
REQUEST(__count(0,	8,	समय_spent_to_dispatch_भव_processors)
	__count(0x8,	8,	समय_spent_processing_भव_processor_समयrs)
	__count(0x10,	8,	समय_spent_managing_partitions_over_entitlement)
	__count(0x18,	8,	समय_spent_on_प्रणाली_management)
)
#समावेश I(REQUEST_END)

#घोषणा REQUEST_NAME प्रणाली_tlbie_count_and_समय
#घोषणा REQUEST_NUM 0xF4
#घोषणा REQUEST_IDX_KIND "starting_index=0xffffffff"
#समावेश I(REQUEST_BEGIN)
REQUEST(__count(0,	8,	tlbie_inकाष्ठाions_issued)
	/*
	 * FIXME: The spec says the offset here is 0x10, which I suspect
	 *	  is wrong.
	 */
	__count(0x8,	8,	समय_spent_issuing_tlbies)
)
#समावेश I(REQUEST_END)

#घोषणा REQUEST_NAME partition_inकाष्ठाion_count_and_समय
#घोषणा REQUEST_NUM 0x100
#घोषणा REQUEST_IDX_KIND "partition_id=?"
#समावेश I(REQUEST_BEGIN)
REQUEST(__field(0,	2,	partition_id)
	__array(0x2,	0x6,	reserved1)
	__count(0x8,	8,	inकाष्ठाions_perक्रमmed)
	__count(0x10,	8,	समय_collected)
)
#समावेश I(REQUEST_END)

/* set_mmcrh (0x80001000) skipped, no counters */
/* retrieve_hpmcx (0x80002000) skipped, no counters */

#समावेश "req-gen/_end.h"
