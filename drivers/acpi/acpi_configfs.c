<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI configfs support
 *
 * Copyright (c) 2016 Intel Corporation
 */

#घोषणा pr_fmt(fmt) "ACPI configfs: " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/configfs.h>
#समावेश <linux/acpi.h>
#समावेश <linux/security.h>

#समावेश "acpica/accommon.h"
#समावेश "acpica/actables.h"

अटल काष्ठा config_group *acpi_table_group;

काष्ठा acpi_table अणु
	काष्ठा config_item cfg;
	काष्ठा acpi_table_header *header;
	u32 index;
पूर्ण;

अटल sमाप_प्रकार acpi_table_aml_ग_लिखो(काष्ठा config_item *cfg,
				    स्थिर व्योम *data, माप_प्रकार size)
अणु
	स्थिर काष्ठा acpi_table_header *header = data;
	काष्ठा acpi_table *table;
	पूर्णांक ret = security_locked_करोwn(LOCKDOWN_ACPI_TABLES);

	अगर (ret)
		वापस ret;

	table = container_of(cfg, काष्ठा acpi_table, cfg);

	अगर (table->header) अणु
		pr_err("table already loaded\n");
		वापस -EBUSY;
	पूर्ण

	अगर (header->length != size) अणु
		pr_err("invalid table length\n");
		वापस -EINVAL;
	पूर्ण

	अगर (स_भेद(header->signature, ACPI_SIG_SSDT, 4)) अणु
		pr_err("invalid table signature\n");
		वापस -EINVAL;
	पूर्ण

	table = container_of(cfg, काष्ठा acpi_table, cfg);

	table->header = kmemdup(header, header->length, GFP_KERNEL);
	अगर (!table->header)
		वापस -ENOMEM;

	ret = acpi_load_table(table->header, &table->index);
	अगर (ret) अणु
		kमुक्त(table->header);
		table->header = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा acpi_table_header *get_header(काष्ठा config_item *cfg)
अणु
	काष्ठा acpi_table *table = container_of(cfg, काष्ठा acpi_table, cfg);

	अगर (!table->header)
		pr_err("table not loaded\n");

	वापस table->header;
पूर्ण

अटल sमाप_प्रकार acpi_table_aml_पढ़ो(काष्ठा config_item *cfg,
				   व्योम *data, माप_प्रकार size)
अणु
	काष्ठा acpi_table_header *h = get_header(cfg);

	अगर (!h)
		वापस -EINVAL;

	अगर (data)
		स_नकल(data, h, h->length);

	वापस h->length;
पूर्ण

#घोषणा MAX_ACPI_TABLE_SIZE (128 * 1024)

CONFIGFS_BIN_ATTR(acpi_table_, aml, शून्य, MAX_ACPI_TABLE_SIZE);

अटल काष्ठा configfs_bin_attribute *acpi_table_bin_attrs[] = अणु
	&acpi_table_attr_aml,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार acpi_table_signature_show(काष्ठा config_item *cfg, अक्षर *str)
अणु
	काष्ठा acpi_table_header *h = get_header(cfg);

	अगर (!h)
		वापस -EINVAL;

	वापस प्र_लिखो(str, "%.*s\n", ACPI_NAMESEG_SIZE, h->signature);
पूर्ण

अटल sमाप_प्रकार acpi_table_length_show(काष्ठा config_item *cfg, अक्षर *str)
अणु
	काष्ठा acpi_table_header *h = get_header(cfg);

	अगर (!h)
		वापस -EINVAL;

	वापस प्र_लिखो(str, "%d\n", h->length);
पूर्ण

अटल sमाप_प्रकार acpi_table_revision_show(काष्ठा config_item *cfg, अक्षर *str)
अणु
	काष्ठा acpi_table_header *h = get_header(cfg);

	अगर (!h)
		वापस -EINVAL;

	वापस प्र_लिखो(str, "%d\n", h->revision);
पूर्ण

अटल sमाप_प्रकार acpi_table_oem_id_show(काष्ठा config_item *cfg, अक्षर *str)
अणु
	काष्ठा acpi_table_header *h = get_header(cfg);

	अगर (!h)
		वापस -EINVAL;

	वापस प्र_लिखो(str, "%.*s\n", ACPI_OEM_ID_SIZE, h->oem_id);
पूर्ण

अटल sमाप_प्रकार acpi_table_oem_table_id_show(काष्ठा config_item *cfg, अक्षर *str)
अणु
	काष्ठा acpi_table_header *h = get_header(cfg);

	अगर (!h)
		वापस -EINVAL;

	वापस प्र_लिखो(str, "%.*s\n", ACPI_OEM_TABLE_ID_SIZE, h->oem_table_id);
पूर्ण

अटल sमाप_प्रकार acpi_table_oem_revision_show(काष्ठा config_item *cfg, अक्षर *str)
अणु
	काष्ठा acpi_table_header *h = get_header(cfg);

	अगर (!h)
		वापस -EINVAL;

	वापस प्र_लिखो(str, "%d\n", h->oem_revision);
पूर्ण

अटल sमाप_प्रकार acpi_table_asl_compiler_id_show(काष्ठा config_item *cfg,
					       अक्षर *str)
अणु
	काष्ठा acpi_table_header *h = get_header(cfg);

	अगर (!h)
		वापस -EINVAL;

	वापस प्र_लिखो(str, "%.*s\n", ACPI_NAMESEG_SIZE, h->asl_compiler_id);
पूर्ण

अटल sमाप_प्रकार acpi_table_asl_compiler_revision_show(काष्ठा config_item *cfg,
						     अक्षर *str)
अणु
	काष्ठा acpi_table_header *h = get_header(cfg);

	अगर (!h)
		वापस -EINVAL;

	वापस प्र_लिखो(str, "%d\n", h->asl_compiler_revision);
पूर्ण

CONFIGFS_ATTR_RO(acpi_table_, signature);
CONFIGFS_ATTR_RO(acpi_table_, length);
CONFIGFS_ATTR_RO(acpi_table_, revision);
CONFIGFS_ATTR_RO(acpi_table_, oem_id);
CONFIGFS_ATTR_RO(acpi_table_, oem_table_id);
CONFIGFS_ATTR_RO(acpi_table_, oem_revision);
CONFIGFS_ATTR_RO(acpi_table_, asl_compiler_id);
CONFIGFS_ATTR_RO(acpi_table_, asl_compiler_revision);

अटल काष्ठा configfs_attribute *acpi_table_attrs[] = अणु
	&acpi_table_attr_signature,
	&acpi_table_attr_length,
	&acpi_table_attr_revision,
	&acpi_table_attr_oem_id,
	&acpi_table_attr_oem_table_id,
	&acpi_table_attr_oem_revision,
	&acpi_table_attr_asl_compiler_id,
	&acpi_table_attr_asl_compiler_revision,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type acpi_table_type = अणु
	.ct_owner = THIS_MODULE,
	.ct_bin_attrs = acpi_table_bin_attrs,
	.ct_attrs = acpi_table_attrs,
पूर्ण;

अटल काष्ठा config_item *acpi_table_make_item(काष्ठा config_group *group,
						स्थिर अक्षर *name)
अणु
	काष्ठा acpi_table *table;

	table = kzalloc(माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस ERR_PTR(-ENOMEM);

	config_item_init_type_name(&table->cfg, name, &acpi_table_type);
	वापस &table->cfg;
पूर्ण

अटल व्योम acpi_table_drop_item(काष्ठा config_group *group,
				 काष्ठा config_item *cfg)
अणु
	काष्ठा acpi_table *table = container_of(cfg, काष्ठा acpi_table, cfg);

	ACPI_INFO(("Host-directed Dynamic ACPI Table Unload"));
	acpi_unload_table(table->index);
	config_item_put(cfg);
पूर्ण

अटल काष्ठा configfs_group_operations acpi_table_group_ops = अणु
	.make_item = acpi_table_make_item,
	.drop_item = acpi_table_drop_item,
पूर्ण;

अटल स्थिर काष्ठा config_item_type acpi_tables_type = अणु
	.ct_owner = THIS_MODULE,
	.ct_group_ops = &acpi_table_group_ops,
पूर्ण;

अटल स्थिर काष्ठा config_item_type acpi_root_group_type = अणु
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा configfs_subप्रणाली acpi_configfs = अणु
	.su_group = अणु
		.cg_item = अणु
			.ci_namebuf = "acpi",
			.ci_type = &acpi_root_group_type,
		पूर्ण,
	पूर्ण,
	.su_mutex = __MUTEX_INITIALIZER(acpi_configfs.su_mutex),
पूर्ण;

अटल पूर्णांक __init acpi_configfs_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा config_group *root = &acpi_configfs.su_group;

	config_group_init(root);

	ret = configfs_रेजिस्टर_subप्रणाली(&acpi_configfs);
	अगर (ret)
		वापस ret;

	acpi_table_group = configfs_रेजिस्टर_शेष_group(root, "table",
							   &acpi_tables_type);
	अगर (IS_ERR(acpi_table_group)) अणु
		configfs_unरेजिस्टर_subप्रणाली(&acpi_configfs);
		वापस PTR_ERR(acpi_table_group);
	पूर्ण

	वापस 0;
पूर्ण
module_init(acpi_configfs_init);

अटल व्योम __निकास acpi_configfs_निकास(व्योम)
अणु
	configfs_unरेजिस्टर_शेष_group(acpi_table_group);
	configfs_unरेजिस्टर_subप्रणाली(&acpi_configfs);
पूर्ण
module_निकास(acpi_configfs_निकास);

MODULE_AUTHOR("Octavian Purdila <octavian.purdila@intel.com>");
MODULE_DESCRIPTION("ACPI configfs support");
MODULE_LICENSE("GPL v2");
