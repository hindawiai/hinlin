<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Firmware-Assisted Dump support on POWERVM platक्रमm.
 *
 * Copyright 2011, Mahesh Salgaonkar, IBM Corporation.
 * Copyright 2019, Hari Bathini, IBM Corporation.
 */

#अगर_अघोषित _PSERIES_RTAS_FADUMP_H
#घोषणा _PSERIES_RTAS_FADUMP_H

/*
 * On some Power प्रणालीs where RMO is 128MB, it still requires minimum of
 * 256MB क्रम kernel to boot successfully. When kdump infraकाष्ठाure is
 * configured to save vmcore over network, we run पूर्णांकo OOM issue जबतक
 * loading modules related to network setup. Hence we need additional 64M
 * of memory to aव्योम OOM issue.
 */
#घोषणा RTAS_FADUMP_MIN_BOOT_MEM	((0x1UL << 28) + (0x1UL << 26))

/* Firmware provided dump sections */
#घोषणा RTAS_FADUMP_CPU_STATE_DATA	0x0001
#घोषणा RTAS_FADUMP_HPTE_REGION		0x0002
#घोषणा RTAS_FADUMP_REAL_MODE_REGION	0x0011

/* Dump request flag */
#घोषणा RTAS_FADUMP_REQUEST_FLAG	0x00000001

/* Dump status flag */
#घोषणा RTAS_FADUMP_ERROR_FLAG		0x2000

/* Kernel Dump section info */
काष्ठा rtas_fadump_section अणु
	__be32	request_flag;
	__be16	source_data_type;
	__be16	error_flags;
	__be64	source_address;
	__be64	source_len;
	__be64	bytes_dumped;
	__be64	destination_address;
पूर्ण;

/* ibm,configure-kernel-dump header. */
काष्ठा rtas_fadump_section_header अणु
	__be32	dump_क्रमmat_version;
	__be16	dump_num_sections;
	__be16	dump_status_flag;
	__be32	offset_first_dump_section;

	/* Fields क्रम disk dump option. */
	__be32	dd_block_size;
	__be64	dd_block_offset;
	__be64	dd_num_blocks;
	__be32	dd_offset_disk_path;

	/* Maximum समय allowed to prevent an स्वतःmatic dump-reboot. */
	__be32	max_समय_स्वतः;
पूर्ण;

/*
 * Firmware Assisted dump memory काष्ठाure. This काष्ठाure is required क्रम
 * रेजिस्टरing future kernel dump with घातer firmware through rtas call.
 *
 * No disk dump option. Hence disk dump path string section is not included.
 */
काष्ठा rtas_fadump_mem_काष्ठा अणु
	काष्ठा rtas_fadump_section_header	header;

	/* Kernel dump sections */
	काष्ठा rtas_fadump_section		cpu_state_data;
	काष्ठा rtas_fadump_section		hpte_region;

	/*
	 * TODO: Extend multiple boot memory regions support in the kernel
	 *       क्रम this platक्रमm.
	 */
	काष्ठा rtas_fadump_section		rmr_region;
पूर्ण;

/*
 * The firmware-assisted dump क्रमmat.
 *
 * The रेजिस्टर save area is an area in the partition's memory used to preserve
 * the रेजिस्टर contents (CPU state data) क्रम the active CPUs during a firmware
 * assisted dump. The dump क्रमmat contains रेजिस्टर save area header followed
 * by रेजिस्टर entries. Each list of रेजिस्टरs क्रम a CPU starts with "CPUSTRT"
 * and ends with "CPUEND".
 */

/* Register save area header. */
काष्ठा rtas_fadump_reg_save_area_header अणु
	__be64		magic_number;
	__be32		version;
	__be32		num_cpu_offset;
पूर्ण;

/* Register entry. */
काष्ठा rtas_fadump_reg_entry अणु
	__be64		reg_id;
	__be64		reg_value;
पूर्ण;

/* Utility macros */
#घोषणा RTAS_FADUMP_SKIP_TO_NEXT_CPU(reg_entry)				\
(अणु									\
	जबतक (be64_to_cpu(reg_entry->reg_id) !=			\
	       fadump_str_to_u64("CPUEND"))				\
		reg_entry++;						\
	reg_entry++;							\
पूर्ण)

#घोषणा RTAS_FADUMP_CPU_ID_MASK			((1UL << 32) - 1)

#पूर्ण_अगर /* _PSERIES_RTAS_FADUMP_H */
