<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * FPDT support क्रम exporting boot and suspend/resume perक्रमmance data
 *
 * Copyright (C) 2021 Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) "ACPI FPDT: " fmt

#समावेश <linux/acpi.h>

/*
 * FPDT contains ACPI table header and a number of fpdt_subtable_entries.
 * Each fpdt_subtable_entry poपूर्णांकs to a subtable: FBPT or S3PT.
 * Each FPDT subtable (FBPT/S3PT) is composed of a fpdt_subtable_header
 * and a number of fpdt perक्रमmance records.
 * Each FPDT perक्रमmance record is composed of a fpdt_record_header and
 * perक्रमmance data fields, क्रम boot or suspend or resume phase.
 */
क्रमागत fpdt_subtable_type अणु
	SUBTABLE_FBPT,
	SUBTABLE_S3PT,
पूर्ण;

काष्ठा fpdt_subtable_entry अणु
	u16 type;		/* refer to क्रमागत fpdt_subtable_type */
	u8 length;
	u8 revision;
	u32 reserved;
	u64 address;		/* physical address of the S3PT/FBPT table */
पूर्ण;

काष्ठा fpdt_subtable_header अणु
	u32 signature;
	u32 length;
पूर्ण;

क्रमागत fpdt_record_type अणु
	RECORD_S3_RESUME,
	RECORD_S3_SUSPEND,
	RECORD_BOOT,
पूर्ण;

काष्ठा fpdt_record_header अणु
	u16 type;		/* refer to क्रमागत fpdt_record_type */
	u8 length;
	u8 revision;
पूर्ण;

काष्ठा resume_perक्रमmance_record अणु
	काष्ठा fpdt_record_header header;
	u32 resume_count;
	u64 resume_prev;
	u64 resume_avg;
पूर्ण __attribute__((packed));

काष्ठा boot_perक्रमmance_record अणु
	काष्ठा fpdt_record_header header;
	u32 reserved;
	u64 firmware_start;
	u64 bootloader_load;
	u64 bootloader_launch;
	u64 निकासbootservice_start;
	u64 निकासbootservice_end;
पूर्ण __attribute__((packed));

काष्ठा suspend_perक्रमmance_record अणु
	काष्ठा fpdt_record_header header;
	u64 suspend_start;
	u64 suspend_end;
पूर्ण __attribute__((packed));


अटल काष्ठा resume_perक्रमmance_record *record_resume;
अटल काष्ठा suspend_perक्रमmance_record *record_suspend;
अटल काष्ठा boot_perक्रमmance_record *record_boot;

#घोषणा FPDT_ATTR(phase, name)	\
अटल sमाप_प्रकार name##_show(काष्ठा kobject *kobj,	\
		 काष्ठा kobj_attribute *attr, अक्षर *buf)	\
अणु	\
	वापस प्र_लिखो(buf, "%llu\n", record_##phase->name);	\
पूर्ण	\
अटल काष्ठा kobj_attribute name##_attr =	\
__ATTR(name##_ns, 0444, name##_show, शून्य)

FPDT_ATTR(resume, resume_prev);
FPDT_ATTR(resume, resume_avg);
FPDT_ATTR(suspend, suspend_start);
FPDT_ATTR(suspend, suspend_end);
FPDT_ATTR(boot, firmware_start);
FPDT_ATTR(boot, bootloader_load);
FPDT_ATTR(boot, bootloader_launch);
FPDT_ATTR(boot, निकासbootservice_start);
FPDT_ATTR(boot, निकासbootservice_end);

अटल sमाप_प्रकार resume_count_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", record_resume->resume_count);
पूर्ण

अटल काष्ठा kobj_attribute resume_count_attr =
__ATTR_RO(resume_count);

अटल काष्ठा attribute *resume_attrs[] = अणु
	&resume_count_attr.attr,
	&resume_prev_attr.attr,
	&resume_avg_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group resume_attr_group = अणु
	.attrs = resume_attrs,
	.name = "resume",
पूर्ण;

अटल काष्ठा attribute *suspend_attrs[] = अणु
	&suspend_start_attr.attr,
	&suspend_end_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group suspend_attr_group = अणु
	.attrs = suspend_attrs,
	.name = "suspend",
पूर्ण;

अटल काष्ठा attribute *boot_attrs[] = अणु
	&firmware_start_attr.attr,
	&bootloader_load_attr.attr,
	&bootloader_launch_attr.attr,
	&निकासbootservice_start_attr.attr,
	&निकासbootservice_end_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group boot_attr_group = अणु
	.attrs = boot_attrs,
	.name = "boot",
पूर्ण;

अटल काष्ठा kobject *fpdt_kobj;

अटल पूर्णांक fpdt_process_subtable(u64 address, u32 subtable_type)
अणु
	काष्ठा fpdt_subtable_header *subtable_header;
	काष्ठा fpdt_record_header *record_header;
	अक्षर *signature = (subtable_type == SUBTABLE_FBPT ? "FBPT" : "S3PT");
	u32 length, offset;
	पूर्णांक result;

	subtable_header = acpi_os_map_memory(address, माप(*subtable_header));
	अगर (!subtable_header)
		वापस -ENOMEM;

	अगर (म_भेदन((अक्षर *)&subtable_header->signature, signature, 4)) अणु
		pr_info(FW_BUG "subtable signature and type mismatch!\n");
		वापस -EINVAL;
	पूर्ण

	length = subtable_header->length;
	acpi_os_unmap_memory(subtable_header, माप(*subtable_header));

	subtable_header = acpi_os_map_memory(address, length);
	अगर (!subtable_header)
		वापस -ENOMEM;

	offset = माप(*subtable_header);
	जबतक (offset < length) अणु
		record_header = (व्योम *)subtable_header + offset;
		offset += record_header->length;

		चयन (record_header->type) अणु
		हाल RECORD_S3_RESUME:
			अगर (subtable_type != SUBTABLE_S3PT) अणु
				pr_err(FW_BUG "Invalid record %d for subtable %s\n",
				     record_header->type, signature);
				वापस -EINVAL;
			पूर्ण
			अगर (record_resume) अणु
				pr_err("Duplicate resume performance record found.\n");
				जारी;
			पूर्ण
			record_resume = (काष्ठा resume_perक्रमmance_record *)record_header;
			result = sysfs_create_group(fpdt_kobj, &resume_attr_group);
			अगर (result)
				वापस result;
			अवरोध;
		हाल RECORD_S3_SUSPEND:
			अगर (subtable_type != SUBTABLE_S3PT) अणु
				pr_err(FW_BUG "Invalid %d for subtable %s\n",
				     record_header->type, signature);
				जारी;
			पूर्ण
			अगर (record_suspend) अणु
				pr_err("Duplicate suspend performance record found.\n");
				जारी;
			पूर्ण
			record_suspend = (काष्ठा suspend_perक्रमmance_record *)record_header;
			result = sysfs_create_group(fpdt_kobj, &suspend_attr_group);
			अगर (result)
				वापस result;
			अवरोध;
		हाल RECORD_BOOT:
			अगर (subtable_type != SUBTABLE_FBPT) अणु
				pr_err(FW_BUG "Invalid %d for subtable %s\n",
				     record_header->type, signature);
				वापस -EINVAL;
			पूर्ण
			अगर (record_boot) अणु
				pr_err("Duplicate boot performance record found.\n");
				जारी;
			पूर्ण
			record_boot = (काष्ठा boot_perक्रमmance_record *)record_header;
			result = sysfs_create_group(fpdt_kobj, &boot_attr_group);
			अगर (result)
				वापस result;
			अवरोध;

		शेष:
			pr_err(FW_BUG "Invalid record %d found.\n", record_header->type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init acpi_init_fpdt(व्योम)
अणु
	acpi_status status;
	काष्ठा acpi_table_header *header;
	काष्ठा fpdt_subtable_entry *subtable;
	u32 offset = माप(*header);

	status = acpi_get_table(ACPI_SIG_FPDT, 0, &header);

	अगर (ACPI_FAILURE(status))
		वापस 0;

	fpdt_kobj = kobject_create_and_add("fpdt", acpi_kobj);
	अगर (!fpdt_kobj)
		वापस -ENOMEM;

	जबतक (offset < header->length) अणु
		subtable = (व्योम *)header + offset;
		चयन (subtable->type) अणु
		हाल SUBTABLE_FBPT:
		हाल SUBTABLE_S3PT:
			fpdt_process_subtable(subtable->address,
					      subtable->type);
			अवरोध;
		शेष:
			pr_info(FW_BUG "Invalid subtable type %d found.\n",
			       subtable->type);
			अवरोध;
		पूर्ण
		offset += माप(*subtable);
	पूर्ण
	वापस 0;
पूर्ण

fs_initcall(acpi_init_fpdt);
