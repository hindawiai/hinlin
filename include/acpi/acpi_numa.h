<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ACPI_NUMA_H
#घोषणा __ACPI_NUMA_H

#अगर_घोषित CONFIG_ACPI_NUMA
#समावेश <linux/kernel.h>
#समावेश <linux/numa.h>

/* Proximity biपंचांगap length */
#अगर MAX_NUMNODES > 256
#घोषणा MAX_PXM_DOMAINS MAX_NUMNODES
#अन्यथा
#घोषणा MAX_PXM_DOMAINS (256)	/* Old pxm spec is defined 8 bit */
#पूर्ण_अगर

बाह्य पूर्णांक pxm_to_node(पूर्णांक);
बाह्य पूर्णांक node_to_pxm(पूर्णांक);
बाह्य पूर्णांक acpi_map_pxm_to_node(पूर्णांक);
बाह्य अचिन्हित अक्षर acpi_srat_revision;
बाह्य व्योम disable_srat(व्योम);

बाह्य व्योम bad_srat(व्योम);
बाह्य पूर्णांक srat_disabled(व्योम);

#अन्यथा				/* CONFIG_ACPI_NUMA */
अटल अंतरभूत व्योम disable_srat(व्योम)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक pxm_to_node(पूर्णांक pxm)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक node_to_pxm(पूर्णांक node)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर				/* CONFIG_ACPI_NUMA */

#अगर_घोषित CONFIG_ACPI_HMAT
बाह्य व्योम disable_hmat(व्योम);
#अन्यथा				/* CONFIG_ACPI_HMAT */
अटल अंतरभूत व्योम disable_hmat(व्योम)
अणु
पूर्ण
#पूर्ण_अगर				/* CONFIG_ACPI_HMAT */
#पूर्ण_अगर				/* __ACP_NUMA_H */
