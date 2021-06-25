<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * acpi_lpit.c - LPIT table processing functions
 *
 * Copyright (C) 2017 Intel Corporation. All rights reserved.
 */

#समावेश <linux/cpu.h>
#समावेश <linux/acpi.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/tsc.h>

काष्ठा lpit_residency_info अणु
	काष्ठा acpi_generic_address gaddr;
	u64 frequency;
	व्योम __iomem *iomem_addr;
पूर्ण;

/* Storage क्रम an memory mapped and FFH based entries */
अटल काष्ठा lpit_residency_info residency_info_mem;
अटल काष्ठा lpit_residency_info residency_info_ffh;

अटल पूर्णांक lpit_पढ़ो_residency_counter_us(u64 *counter, bool io_mem)
अणु
	पूर्णांक err;

	अगर (io_mem) अणु
		u64 count = 0;
		पूर्णांक error;

		error = acpi_os_पढ़ो_iomem(residency_info_mem.iomem_addr, &count,
					   residency_info_mem.gaddr.bit_width);
		अगर (error)
			वापस error;

		*counter = भाग64_u64(count * 1000000ULL, residency_info_mem.frequency);
		वापस 0;
	पूर्ण

	err = rdmsrl_safe(residency_info_ffh.gaddr.address, counter);
	अगर (!err) अणु
		u64 mask = GENMASK_ULL(residency_info_ffh.gaddr.bit_offset +
				       residency_info_ffh.gaddr. bit_width - 1,
				       residency_info_ffh.gaddr.bit_offset);

		*counter &= mask;
		*counter >>= residency_info_ffh.gaddr.bit_offset;
		*counter = भाग64_u64(*counter * 1000000ULL, residency_info_ffh.frequency);
		वापस 0;
	पूर्ण

	वापस -ENODATA;
पूर्ण

अटल sमाप_प्रकार low_घातer_idle_प्रणाली_residency_us_show(काष्ठा device *dev,
						       काष्ठा device_attribute *attr,
						       अक्षर *buf)
अणु
	u64 counter;
	पूर्णांक ret;

	ret = lpit_पढ़ो_residency_counter_us(&counter, true);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%llu\n", counter);
पूर्ण
अटल DEVICE_ATTR_RO(low_घातer_idle_प्रणाली_residency_us);

अटल sमाप_प्रकार low_घातer_idle_cpu_residency_us_show(काष्ठा device *dev,
						    काष्ठा device_attribute *attr,
						    अक्षर *buf)
अणु
	u64 counter;
	पूर्णांक ret;

	ret = lpit_पढ़ो_residency_counter_us(&counter, false);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%llu\n", counter);
पूर्ण
अटल DEVICE_ATTR_RO(low_घातer_idle_cpu_residency_us);

पूर्णांक lpit_पढ़ो_residency_count_address(u64 *address)
अणु
	अगर (!residency_info_mem.gaddr.address)
		वापस -EINVAL;

	*address = residency_info_mem.gaddr.address;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lpit_पढ़ो_residency_count_address);

अटल व्योम lpit_update_residency(काष्ठा lpit_residency_info *info,
				 काष्ठा acpi_lpit_native *lpit_native)
अणु
	info->frequency = lpit_native->counter_frequency ?
				lpit_native->counter_frequency : tsc_khz * 1000;
	अगर (!info->frequency)
		info->frequency = 1;

	info->gaddr = lpit_native->residency_counter;
	अगर (info->gaddr.space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
		info->iomem_addr = ioremap(info->gaddr.address,
						   info->gaddr.bit_width / 8);
		अगर (!info->iomem_addr)
			वापस;

		अगर (!(acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0))
			वापस;

		/* Silently fail, अगर cpuidle attribute group is not present */
		sysfs_add_file_to_group(&cpu_subsys.dev_root->kobj,
					&dev_attr_low_घातer_idle_प्रणाली_residency_us.attr,
					"cpuidle");
	पूर्ण अन्यथा अगर (info->gaddr.space_id == ACPI_ADR_SPACE_FIXED_HARDWARE) अणु
		अगर (!(acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0))
			वापस;

		/* Silently fail, अगर cpuidle attribute group is not present */
		sysfs_add_file_to_group(&cpu_subsys.dev_root->kobj,
					&dev_attr_low_घातer_idle_cpu_residency_us.attr,
					"cpuidle");
	पूर्ण
पूर्ण

अटल व्योम lpit_process(u64 begin, u64 end)
अणु
	जबतक (begin + माप(काष्ठा acpi_lpit_native) <= end) अणु
		काष्ठा acpi_lpit_native *lpit_native = (काष्ठा acpi_lpit_native *)begin;

		अगर (!lpit_native->header.type && !lpit_native->header.flags) अणु
			अगर (lpit_native->residency_counter.space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY &&
			    !residency_info_mem.gaddr.address) अणु
				lpit_update_residency(&residency_info_mem, lpit_native);
			पूर्ण अन्यथा अगर (lpit_native->residency_counter.space_id == ACPI_ADR_SPACE_FIXED_HARDWARE &&
				   !residency_info_ffh.gaddr.address) अणु
				lpit_update_residency(&residency_info_ffh, lpit_native);
			पूर्ण
		पूर्ण
		begin += lpit_native->header.length;
	पूर्ण
पूर्ण

व्योम acpi_init_lpit(व्योम)
अणु
	acpi_status status;
	काष्ठा acpi_table_lpit *lpit;

	status = acpi_get_table(ACPI_SIG_LPIT, 0, (काष्ठा acpi_table_header **)&lpit);
	अगर (ACPI_FAILURE(status))
		वापस;

	lpit_process((u64)lpit + माप(*lpit),
		     (u64)lpit + lpit->header.length);

	acpi_put_table((काष्ठा acpi_table_header *)lpit);
पूर्ण
