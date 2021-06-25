<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BUS_NUMA_H
#घोषणा __BUS_NUMA_H
/*
 * sub bus (transparent) will use entres from 3 to store extra from
 * root, so need to make sure we have enough slot there.
 */
काष्ठा pci_root_res अणु
	काष्ठा list_head list;
	काष्ठा resource res;
पूर्ण;

काष्ठा pci_root_info अणु
	काष्ठा list_head list;
	अक्षर name[12];
	काष्ठा list_head resources;
	काष्ठा resource busn;
	पूर्णांक node;
	पूर्णांक link;
पूर्ण;

बाह्य काष्ठा list_head pci_root_infos;
काष्ठा pci_root_info *alloc_pci_root_info(पूर्णांक bus_min, पूर्णांक bus_max,
						पूर्णांक node, पूर्णांक link);
बाह्य व्योम update_res(काष्ठा pci_root_info *info, resource_माप_प्रकार start,
		      resource_माप_प्रकार end, अचिन्हित दीर्घ flags, पूर्णांक merge);
#पूर्ण_अगर
