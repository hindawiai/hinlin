<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * apei.h - ACPI Platक्रमm Error Interface
 */

#अगर_अघोषित ACPI_APEI_H
#घोषणा ACPI_APEI_H

#समावेश <linux/acpi.h>
#समावेश <linux/cper.h>
#समावेश <यंत्र/ioctls.h>

#घोषणा APEI_ERST_INVALID_RECORD_ID	0xffffffffffffffffULL

#घोषणा APEI_ERST_CLEAR_RECORD		_IOW('E', 1, u64)
#घोषणा APEI_ERST_GET_RECORD_COUNT	_IOR('E', 2, u32)

#अगर_घोषित __KERNEL__

क्रमागत hest_status अणु
	HEST_ENABLED,
	HEST_DISABLED,
	HEST_NOT_FOUND,
पूर्ण;

बाह्य पूर्णांक hest_disable;
बाह्य पूर्णांक erst_disable;
#अगर_घोषित CONFIG_ACPI_APEI_GHES
बाह्य bool ghes_disable;
#अन्यथा
#घोषणा ghes_disable 1
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_APEI
व्योम __init acpi_hest_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_hest_init(व्योम) अणु वापस; पूर्ण
#पूर्ण_अगर

प्रकार पूर्णांक (*apei_hest_func_t)(काष्ठा acpi_hest_header *hest_hdr, व्योम *data);
पूर्णांक apei_hest_parse(apei_hest_func_t func, व्योम *data);

पूर्णांक erst_ग_लिखो(स्थिर काष्ठा cper_record_header *record);
sमाप_प्रकार erst_get_record_count(व्योम);
पूर्णांक erst_get_record_id_begin(पूर्णांक *pos);
पूर्णांक erst_get_record_id_next(पूर्णांक *pos, u64 *record_id);
व्योम erst_get_record_id_end(व्योम);
sमाप_प्रकार erst_पढ़ो(u64 record_id, काष्ठा cper_record_header *record,
		  माप_प्रकार buflen);
पूर्णांक erst_clear(u64 record_id);

पूर्णांक arch_apei_enable_cmcff(काष्ठा acpi_hest_header *hest_hdr, व्योम *data);
व्योम arch_apei_report_mem_error(पूर्णांक sev, काष्ठा cper_sec_mem_err *mem_err);

#पूर्ण_अगर
#पूर्ण_अगर
