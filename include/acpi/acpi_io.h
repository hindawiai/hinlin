<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ACPI_IO_H_
#घोषणा _ACPI_IO_H_

#समावेश <linux/पन.स>

#समावेश <यंत्र/acpi.h>

#अगर_अघोषित acpi_os_ioremap
अटल अंतरभूत व्योम __iomem *acpi_os_ioremap(acpi_physical_address phys,
					    acpi_size size)
अणु
       वापस ioremap_cache(phys, size);
पूर्ण
#पूर्ण_अगर

बाह्य bool acpi_permanent_mmap;

व्योम __iomem __ref
*acpi_os_map_iomem(acpi_physical_address phys, acpi_size size);
व्योम __ref acpi_os_unmap_iomem(व्योम __iomem *virt, acpi_size size);
व्योम __iomem *acpi_os_get_iomem(acpi_physical_address phys, अचिन्हित पूर्णांक size);

व्योम __iomem *acpi_os_map_generic_address(काष्ठा acpi_generic_address *addr);
व्योम acpi_os_unmap_generic_address(काष्ठा acpi_generic_address *addr);

#पूर्ण_अगर
