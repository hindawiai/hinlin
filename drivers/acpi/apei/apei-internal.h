<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * apei-पूर्णांकernal.h - ACPI Platक्रमm Error Interface पूर्णांकernal
 * definitions.
 */

#अगर_अघोषित APEI_INTERNAL_H
#घोषणा APEI_INTERNAL_H

#समावेश <linux/cper.h>
#समावेश <linux/acpi.h>

काष्ठा apei_exec_context;

प्रकार पूर्णांक (*apei_exec_ins_func_t)(काष्ठा apei_exec_context *ctx,
				    काष्ठा acpi_whea_header *entry);

#घोषणा APEI_EXEC_INS_ACCESS_REGISTER	0x0001

काष्ठा apei_exec_ins_type अणु
	u32 flags;
	apei_exec_ins_func_t run;
पूर्ण;

काष्ठा apei_exec_context अणु
	u32 ip;
	u64 value;
	u64 var1;
	u64 var2;
	u64 src_base;
	u64 dst_base;
	काष्ठा apei_exec_ins_type *ins_table;
	u32 inकाष्ठाions;
	काष्ठा acpi_whea_header *action_table;
	u32 entries;
पूर्ण;

व्योम apei_exec_ctx_init(काष्ठा apei_exec_context *ctx,
			काष्ठा apei_exec_ins_type *ins_table,
			u32 inकाष्ठाions,
			काष्ठा acpi_whea_header *action_table,
			u32 entries);

अटल अंतरभूत व्योम apei_exec_ctx_set_input(काष्ठा apei_exec_context *ctx,
					   u64 input)
अणु
	ctx->value = input;
पूर्ण

अटल अंतरभूत u64 apei_exec_ctx_get_output(काष्ठा apei_exec_context *ctx)
अणु
	वापस ctx->value;
पूर्ण

पूर्णांक __apei_exec_run(काष्ठा apei_exec_context *ctx, u8 action, bool optional);

अटल अंतरभूत पूर्णांक apei_exec_run(काष्ठा apei_exec_context *ctx, u8 action)
अणु
	वापस __apei_exec_run(ctx, action, 0);
पूर्ण

/* It is optional whether the firmware provides the action */
अटल अंतरभूत पूर्णांक apei_exec_run_optional(काष्ठा apei_exec_context *ctx, u8 action)
अणु
	वापस __apei_exec_run(ctx, action, 1);
पूर्ण

/* Common inकाष्ठाion implementation */

/* IP has been set in inकाष्ठाion function */
#घोषणा APEI_EXEC_SET_IP	1

पूर्णांक apei_map_generic_address(काष्ठा acpi_generic_address *reg);

अटल अंतरभूत व्योम apei_unmap_generic_address(काष्ठा acpi_generic_address *reg)
अणु
	acpi_os_unmap_generic_address(reg);
पूर्ण

पूर्णांक apei_पढ़ो(u64 *val, काष्ठा acpi_generic_address *reg);
पूर्णांक apei_ग_लिखो(u64 val, काष्ठा acpi_generic_address *reg);

पूर्णांक __apei_exec_पढ़ो_रेजिस्टर(काष्ठा acpi_whea_header *entry, u64 *val);
पूर्णांक __apei_exec_ग_लिखो_रेजिस्टर(काष्ठा acpi_whea_header *entry, u64 val);
पूर्णांक apei_exec_पढ़ो_रेजिस्टर(काष्ठा apei_exec_context *ctx,
			    काष्ठा acpi_whea_header *entry);
पूर्णांक apei_exec_पढ़ो_रेजिस्टर_value(काष्ठा apei_exec_context *ctx,
				  काष्ठा acpi_whea_header *entry);
पूर्णांक apei_exec_ग_लिखो_रेजिस्टर(काष्ठा apei_exec_context *ctx,
			     काष्ठा acpi_whea_header *entry);
पूर्णांक apei_exec_ग_लिखो_रेजिस्टर_value(काष्ठा apei_exec_context *ctx,
				   काष्ठा acpi_whea_header *entry);
पूर्णांक apei_exec_noop(काष्ठा apei_exec_context *ctx,
		   काष्ठा acpi_whea_header *entry);
पूर्णांक apei_exec_pre_map_gars(काष्ठा apei_exec_context *ctx);
पूर्णांक apei_exec_post_unmap_gars(काष्ठा apei_exec_context *ctx);

काष्ठा apei_resources अणु
	काष्ठा list_head iomem;
	काष्ठा list_head ioport;
पूर्ण;

अटल अंतरभूत व्योम apei_resources_init(काष्ठा apei_resources *resources)
अणु
	INIT_LIST_HEAD(&resources->iomem);
	INIT_LIST_HEAD(&resources->ioport);
पूर्ण

व्योम apei_resources_fini(काष्ठा apei_resources *resources);
पूर्णांक apei_resources_add(काष्ठा apei_resources *resources,
		       अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
		       bool iomem);
पूर्णांक apei_resources_sub(काष्ठा apei_resources *resources1,
		       काष्ठा apei_resources *resources2);
पूर्णांक apei_resources_request(काष्ठा apei_resources *resources,
			   स्थिर अक्षर *desc);
व्योम apei_resources_release(काष्ठा apei_resources *resources);
पूर्णांक apei_exec_collect_resources(काष्ठा apei_exec_context *ctx,
				काष्ठा apei_resources *resources);

काष्ठा dentry;
काष्ठा dentry *apei_get_debugfs_dir(व्योम);

अटल अंतरभूत u32 cper_estatus_len(काष्ठा acpi_hest_generic_status *estatus)
अणु
	अगर (estatus->raw_data_length)
		वापस estatus->raw_data_offset + \
			estatus->raw_data_length;
	अन्यथा
		वापस माप(*estatus) + estatus->data_length;
पूर्ण

व्योम cper_estatus_prपूर्णांक(स्थिर अक्षर *pfx,
			स्थिर काष्ठा acpi_hest_generic_status *estatus);
पूर्णांक cper_estatus_check_header(स्थिर काष्ठा acpi_hest_generic_status *estatus);
पूर्णांक cper_estatus_check(स्थिर काष्ठा acpi_hest_generic_status *estatus);

पूर्णांक apei_osc_setup(व्योम);
#पूर्ण_अगर
