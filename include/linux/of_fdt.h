<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम working with the Flattened Device Tree data क्रमmat
 *
 * Copyright 2009 Benjamin Herrenschmidt, IBM Corp
 * benh@kernel.crashing.org
 */

#अगर_अघोषित _LINUX_OF_FDT_H
#घोषणा _LINUX_OF_FDT_H

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>

/* Definitions used by the flattened device tree */
#घोषणा OF_DT_HEADER		0xd00dfeed	/* marker */

#अगर_अघोषित __ASSEMBLY__

#अगर defined(CONFIG_OF_FLATTREE)

काष्ठा device_node;

/* For scanning an arbitrary device-tree at any समय */
बाह्य व्योम *of_fdt_unflatten_tree(स्थिर अचिन्हित दीर्घ *blob,
				   काष्ठा device_node *dad,
				   काष्ठा device_node **mynodes);

/* TBD: Temporary export of fdt globals - हटाओ when code fully merged */
बाह्य पूर्णांक __initdata dt_root_addr_cells;
बाह्य पूर्णांक __initdata dt_root_size_cells;
बाह्य व्योम *initial_boot_params;

बाह्य अक्षर __dtb_start[];
बाह्य अक्षर __dtb_end[];

/* Other Prototypes */
बाह्य u64 of_flat_dt_translate_address(अचिन्हित दीर्घ node);
बाह्य व्योम of_fdt_limit_memory(पूर्णांक limit);
#पूर्ण_अगर /* CONFIG_OF_FLATTREE */

#अगर_घोषित CONFIG_OF_EARLY_FLATTREE
/* For scanning the flat device-tree at boot समय */
बाह्य पूर्णांक of_scan_flat_dt(पूर्णांक (*it)(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				     पूर्णांक depth, व्योम *data),
			   व्योम *data);
बाह्य पूर्णांक of_scan_flat_dt_subnodes(अचिन्हित दीर्घ node,
				    पूर्णांक (*it)(अचिन्हित दीर्घ node,
					      स्थिर अक्षर *uname,
					      व्योम *data),
				    व्योम *data);
बाह्य पूर्णांक of_get_flat_dt_subnode_by_name(अचिन्हित दीर्घ node,
					  स्थिर अक्षर *uname);
बाह्य स्थिर व्योम *of_get_flat_dt_prop(अचिन्हित दीर्घ node, स्थिर अक्षर *name,
				       पूर्णांक *size);
बाह्य पूर्णांक of_flat_dt_is_compatible(अचिन्हित दीर्घ node, स्थिर अक्षर *name);
बाह्य अचिन्हित दीर्घ of_get_flat_dt_root(व्योम);
बाह्य uपूर्णांक32_t of_get_flat_dt_phandle(अचिन्हित दीर्घ node);

बाह्य पूर्णांक early_init_dt_scan_chosen(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				     पूर्णांक depth, व्योम *data);
बाह्य पूर्णांक early_init_dt_scan_memory(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				     पूर्णांक depth, व्योम *data);
बाह्य पूर्णांक early_init_dt_scan_chosen_मानक_निकास(व्योम);
बाह्य व्योम early_init_fdt_scan_reserved_mem(व्योम);
बाह्य व्योम early_init_fdt_reserve_self(व्योम);
बाह्य व्योम __init early_init_dt_scan_chosen_arch(अचिन्हित दीर्घ node);
बाह्य व्योम early_init_dt_add_memory_arch(u64 base, u64 size);
बाह्य पूर्णांक early_init_dt_mark_hotplug_memory_arch(u64 base, u64 size);
बाह्य पूर्णांक early_init_dt_reserve_memory_arch(phys_addr_t base, phys_addr_t size,
					     bool no_map);
बाह्य u64 dt_mem_next_cell(पूर्णांक s, स्थिर __be32 **cellp);

/* Early flat tree scan hooks */
बाह्य पूर्णांक early_init_dt_scan_root(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				   पूर्णांक depth, व्योम *data);

बाह्य bool early_init_dt_scan(व्योम *params);
बाह्य bool early_init_dt_verअगरy(व्योम *params);
बाह्य व्योम early_init_dt_scan_nodes(व्योम);

बाह्य स्थिर अक्षर *of_flat_dt_get_machine_name(व्योम);
बाह्य स्थिर व्योम *of_flat_dt_match_machine(स्थिर व्योम *शेष_match,
		स्थिर व्योम * (*get_next_compat)(स्थिर अक्षर * स्थिर**));

/* Other Prototypes */
बाह्य व्योम unflatten_device_tree(व्योम);
बाह्य व्योम unflatten_and_copy_device_tree(व्योम);
बाह्य व्योम early_init_devtree(व्योम *);
बाह्य व्योम early_get_first_memblock_info(व्योम *, phys_addr_t *);
#अन्यथा /* CONFIG_OF_EARLY_FLATTREE */
अटल अंतरभूत पूर्णांक early_init_dt_scan_chosen_मानक_निकास(व्योम) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम early_init_fdt_scan_reserved_mem(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम early_init_fdt_reserve_self(व्योम) अणुपूर्ण
अटल अंतरभूत स्थिर अक्षर *of_flat_dt_get_machine_name(व्योम) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम unflatten_device_tree(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम unflatten_and_copy_device_tree(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_OF_EARLY_FLATTREE */

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _LINUX_OF_FDT_H */
