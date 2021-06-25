<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित GHES_H
#घोषणा GHES_H

#समावेश <acpi/apei.h>
#समावेश <acpi/hed.h>

/*
 * One काष्ठा ghes is created क्रम each generic hardware error source.
 * It provides the context क्रम APEI hardware error समयr/IRQ/SCI/NMI
 * handler.
 *
 * estatus: memory buffer क्रम error status block, allocated during
 * HEST parsing.
 */
#घोषणा GHES_EXITING		0x0002

काष्ठा ghes अणु
	जोड़ अणु
		काष्ठा acpi_hest_generic *generic;
		काष्ठा acpi_hest_generic_v2 *generic_v2;
	पूर्ण;
	काष्ठा acpi_hest_generic_status *estatus;
	अचिन्हित दीर्घ flags;
	जोड़ अणु
		काष्ठा list_head list;
		काष्ठा समयr_list समयr;
		अचिन्हित पूर्णांक irq;
	पूर्ण;
पूर्ण;

काष्ठा ghes_estatus_node अणु
	काष्ठा llist_node llnode;
	काष्ठा acpi_hest_generic *generic;
	काष्ठा ghes *ghes;

	पूर्णांक task_work_cpu;
	काष्ठा callback_head task_work;
पूर्ण;

काष्ठा ghes_estatus_cache अणु
	u32 estatus_len;
	atomic_t count;
	काष्ठा acpi_hest_generic *generic;
	अचिन्हित दीर्घ दीर्घ समय_in;
	काष्ठा rcu_head rcu;
पूर्ण;

क्रमागत अणु
	GHES_SEV_NO = 0x0,
	GHES_SEV_CORRECTED = 0x1,
	GHES_SEV_RECOVERABLE = 0x2,
	GHES_SEV_PANIC = 0x3,
पूर्ण;

#अगर_घोषित CONFIG_ACPI_APEI_GHES
/**
 * ghes_रेजिस्टर_venकरोr_record_notअगरier - रेजिस्टर a notअगरier क्रम venकरोr
 * records that the kernel would otherwise ignore.
 * @nb: poपूर्णांकer to the notअगरier_block काष्ठाure of the event handler.
 *
 * वापस 0 : SUCCESS, non-zero : FAIL
 */
पूर्णांक ghes_रेजिस्टर_venकरोr_record_notअगरier(काष्ठा notअगरier_block *nb);

/**
 * ghes_unरेजिस्टर_venकरोr_record_notअगरier - unरेजिस्टर the previously
 * रेजिस्टरed venकरोr record notअगरier.
 * @nb: poपूर्णांकer to the notअगरier_block काष्ठाure of the venकरोr record handler.
 */
व्योम ghes_unरेजिस्टर_venकरोr_record_notअगरier(काष्ठा notअगरier_block *nb);
#पूर्ण_अगर

पूर्णांक ghes_estatus_pool_init(पूर्णांक num_ghes);

/* From drivers/edac/ghes_edac.c */

#अगर_घोषित CONFIG_EDAC_GHES
व्योम ghes_edac_report_mem_error(पूर्णांक sev, काष्ठा cper_sec_mem_err *mem_err);

पूर्णांक ghes_edac_रेजिस्टर(काष्ठा ghes *ghes, काष्ठा device *dev);

व्योम ghes_edac_unरेजिस्टर(काष्ठा ghes *ghes);

#अन्यथा
अटल अंतरभूत व्योम ghes_edac_report_mem_error(पूर्णांक sev,
				       काष्ठा cper_sec_mem_err *mem_err)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ghes_edac_रेजिस्टर(काष्ठा ghes *ghes, काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम ghes_edac_unरेजिस्टर(काष्ठा ghes *ghes)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक acpi_hest_get_version(काष्ठा acpi_hest_generic_data *gdata)
अणु
	वापस gdata->revision >> 8;
पूर्ण

अटल अंतरभूत व्योम *acpi_hest_get_payload(काष्ठा acpi_hest_generic_data *gdata)
अणु
	अगर (acpi_hest_get_version(gdata) >= 3)
		वापस (व्योम *)(((काष्ठा acpi_hest_generic_data_v300 *)(gdata)) + 1);

	वापस gdata + 1;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_hest_get_error_length(काष्ठा acpi_hest_generic_data *gdata)
अणु
	वापस ((काष्ठा acpi_hest_generic_data *)(gdata))->error_data_length;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_hest_get_size(काष्ठा acpi_hest_generic_data *gdata)
अणु
	अगर (acpi_hest_get_version(gdata) >= 3)
		वापस माप(काष्ठा acpi_hest_generic_data_v300);

	वापस माप(काष्ठा acpi_hest_generic_data);
पूर्ण

अटल अंतरभूत पूर्णांक acpi_hest_get_record_size(काष्ठा acpi_hest_generic_data *gdata)
अणु
	वापस (acpi_hest_get_size(gdata) + acpi_hest_get_error_length(gdata));
पूर्ण

अटल अंतरभूत व्योम *acpi_hest_get_next(काष्ठा acpi_hest_generic_data *gdata)
अणु
	वापस (व्योम *)(gdata) + acpi_hest_get_record_size(gdata);
पूर्ण

#घोषणा apei_estatus_क्रम_each_section(estatus, section)			\
	क्रम (section = (काष्ठा acpi_hest_generic_data *)(estatus + 1);	\
	     (व्योम *)section - (व्योम *)(estatus + 1) < estatus->data_length; \
	     section = acpi_hest_get_next(section))

#अगर_घोषित CONFIG_ACPI_APEI_SEA
पूर्णांक ghes_notअगरy_sea(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ghes_notअगरy_sea(व्योम) अणु वापस -ENOENT; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* GHES_H */
