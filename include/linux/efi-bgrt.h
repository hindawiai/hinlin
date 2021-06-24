<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_EFI_BGRT_H
#घोषणा _LINUX_EFI_BGRT_H

#समावेश <linux/acpi.h>

#अगर_घोषित CONFIG_ACPI_BGRT

व्योम efi_bgrt_init(काष्ठा acpi_table_header *table);
पूर्णांक __init acpi_parse_bgrt(काष्ठा acpi_table_header *table);

/* The BGRT data itself; only valid अगर bgrt_image != शून्य. */
बाह्य माप_प्रकार bgrt_image_size;
बाह्य काष्ठा acpi_table_bgrt bgrt_tab;

#अन्यथा /* !CONFIG_ACPI_BGRT */

अटल अंतरभूत व्योम efi_bgrt_init(काष्ठा acpi_table_header *table) अणुपूर्ण
अटल अंतरभूत पूर्णांक __init acpi_parse_bgrt(काष्ठा acpi_table_header *table)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_ACPI_BGRT */

#पूर्ण_अगर /* _LINUX_EFI_BGRT_H */
