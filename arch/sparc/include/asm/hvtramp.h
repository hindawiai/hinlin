<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_HVTRAP_H
#घोषणा _SPARC64_HVTRAP_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

काष्ठा hvtramp_mapping अणु
	__u64		vaddr;
	__u64		tte;
पूर्ण;

काष्ठा hvtramp_descr अणु
	__u32			cpu;
	__u32			num_mappings;
	__u64			fault_info_va;
	__u64			fault_info_pa;
	__u64			thपढ़ो_reg;
	काष्ठा hvtramp_mapping	maps[1];
पूर्ण;

व्योम hv_cpu_startup(अचिन्हित दीर्घ hvdescr_pa);

#पूर्ण_अगर

#घोषणा HVTRAMP_DESCR_CPU		0x00
#घोषणा HVTRAMP_DESCR_NUM_MAPPINGS	0x04
#घोषणा HVTRAMP_DESCR_FAULT_INFO_VA	0x08
#घोषणा HVTRAMP_DESCR_FAULT_INFO_PA	0x10
#घोषणा HVTRAMP_DESCR_THREAD_REG	0x18
#घोषणा HVTRAMP_DESCR_MAPS		0x20

#घोषणा HVTRAMP_MAPPING_VADDR		0x00
#घोषणा HVTRAMP_MAPPING_TTE		0x08
#घोषणा HVTRAMP_MAPPING_SIZE		0x10

#पूर्ण_अगर /* _SPARC64_HVTRAP_H */
