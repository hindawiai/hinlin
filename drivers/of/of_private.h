<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित _LINUX_OF_PRIVATE_H
#घोषणा _LINUX_OF_PRIVATE_H
/*
 * Private symbols used by OF support code
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 */

#घोषणा FDT_ALIGN_SIZE 8

/**
 * काष्ठा alias_prop - Alias property in 'aliases' node
 * @link:	List node to link the काष्ठाure in aliases_lookup list
 * @alias:	Alias property name
 * @np:		Poपूर्णांकer to device_node that the alias stands क्रम
 * @id:		Index value from end of alias name
 * @stem:	Alias string without the index
 *
 * The काष्ठाure represents one alias property of 'aliases' node as
 * an entry in aliases_lookup list.
 */
काष्ठा alias_prop अणु
	काष्ठा list_head link;
	स्थिर अक्षर *alias;
	काष्ठा device_node *np;
	पूर्णांक id;
	अक्षर stem[];
पूर्ण;

#अगर defined(CONFIG_SPARC)
#घोषणा OF_ROOT_NODE_ADDR_CELLS_DEFAULT 2
#अन्यथा
#घोषणा OF_ROOT_NODE_ADDR_CELLS_DEFAULT 1
#पूर्ण_अगर

#घोषणा OF_ROOT_NODE_SIZE_CELLS_DEFAULT 1

बाह्य काष्ठा mutex of_mutex;
बाह्य काष्ठा list_head aliases_lookup;
बाह्य काष्ठा kset *of_kset;

#अगर defined(CONFIG_OF_DYNAMIC)
बाह्य पूर्णांक of_property_notअगरy(पूर्णांक action, काष्ठा device_node *np,
			      काष्ठा property *prop, काष्ठा property *old_prop);
बाह्य व्योम of_node_release(काष्ठा kobject *kobj);
बाह्य पूर्णांक __of_changeset_apply_entries(काष्ठा of_changeset *ocs,
					पूर्णांक *ret_revert);
बाह्य पूर्णांक __of_changeset_apply_notअगरy(काष्ठा of_changeset *ocs);
बाह्य पूर्णांक __of_changeset_revert_entries(काष्ठा of_changeset *ocs,
					 पूर्णांक *ret_apply);
बाह्य पूर्णांक __of_changeset_revert_notअगरy(काष्ठा of_changeset *ocs);
#अन्यथा /* CONFIG_OF_DYNAMIC */
अटल अंतरभूत पूर्णांक of_property_notअगरy(पूर्णांक action, काष्ठा device_node *np,
				     काष्ठा property *prop, काष्ठा property *old_prop)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_DYNAMIC */

#अगर defined(CONFIG_OF_KOBJ)
पूर्णांक of_node_is_attached(काष्ठा device_node *node);
पूर्णांक __of_add_property_sysfs(काष्ठा device_node *np, काष्ठा property *pp);
व्योम __of_हटाओ_property_sysfs(काष्ठा device_node *np, काष्ठा property *prop);
व्योम __of_update_property_sysfs(काष्ठा device_node *np, काष्ठा property *newprop,
		काष्ठा property *oldprop);
पूर्णांक __of_attach_node_sysfs(काष्ठा device_node *np);
व्योम __of_detach_node_sysfs(काष्ठा device_node *np);
#अन्यथा
अटल अंतरभूत पूर्णांक __of_add_property_sysfs(काष्ठा device_node *np, काष्ठा property *pp)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम __of_हटाओ_property_sysfs(काष्ठा device_node *np, काष्ठा property *prop) अणुपूर्ण
अटल अंतरभूत व्योम __of_update_property_sysfs(काष्ठा device_node *np,
		काष्ठा property *newprop, काष्ठा property *oldprop) अणुपूर्ण
अटल अंतरभूत पूर्णांक __of_attach_node_sysfs(काष्ठा device_node *np)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम __of_detach_node_sysfs(काष्ठा device_node *np) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_OF_RESOLVE)
पूर्णांक of_resolve_phandles(काष्ठा device_node *tree);
#पूर्ण_अगर

व्योम __of_phandle_cache_inv_entry(phandle handle);

#अगर defined(CONFIG_OF_OVERLAY)
व्योम of_overlay_mutex_lock(व्योम);
व्योम of_overlay_mutex_unlock(व्योम);
#अन्यथा
अटल अंतरभूत व्योम of_overlay_mutex_lock(व्योम) अणुपूर्ण;
अटल अंतरभूत व्योम of_overlay_mutex_unlock(व्योम) अणुपूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_OF_UNITTEST) && defined(CONFIG_OF_OVERLAY)
बाह्य व्योम __init unittest_unflatten_overlay_base(व्योम);
#अन्यथा
अटल अंतरभूत व्योम unittest_unflatten_overlay_base(व्योम) अणुपूर्ण;
#पूर्ण_अगर

बाह्य व्योम *__unflatten_device_tree(स्थिर व्योम *blob,
			      काष्ठा device_node *dad,
			      काष्ठा device_node **mynodes,
			      व्योम *(*dt_alloc)(u64 size, u64 align),
			      bool detached);

/**
 * General utilities क्रम working with live trees.
 *
 * All functions with two leading underscores operate
 * without taking node references, so you either have to
 * own the devtree lock or work on detached trees only.
 */
काष्ठा property *__of_prop_dup(स्थिर काष्ठा property *prop, gfp_t allocflags);
काष्ठा device_node *__of_node_dup(स्थिर काष्ठा device_node *np,
				  स्थिर अक्षर *full_name);

काष्ठा device_node *__of_find_node_by_path(काष्ठा device_node *parent,
						स्थिर अक्षर *path);
काष्ठा device_node *__of_find_node_by_full_path(काष्ठा device_node *node,
						स्थिर अक्षर *path);

बाह्य स्थिर व्योम *__of_get_property(स्थिर काष्ठा device_node *np,
				     स्थिर अक्षर *name, पूर्णांक *lenp);
बाह्य पूर्णांक __of_add_property(काष्ठा device_node *np, काष्ठा property *prop);
बाह्य पूर्णांक __of_add_property_sysfs(काष्ठा device_node *np,
		काष्ठा property *prop);
बाह्य पूर्णांक __of_हटाओ_property(काष्ठा device_node *np, काष्ठा property *prop);
बाह्य व्योम __of_हटाओ_property_sysfs(काष्ठा device_node *np,
		काष्ठा property *prop);
बाह्य पूर्णांक __of_update_property(काष्ठा device_node *np,
		काष्ठा property *newprop, काष्ठा property **oldprop);
बाह्य व्योम __of_update_property_sysfs(काष्ठा device_node *np,
		काष्ठा property *newprop, काष्ठा property *oldprop);

बाह्य पूर्णांक __of_attach_node_sysfs(काष्ठा device_node *np);
बाह्य व्योम __of_detach_node(काष्ठा device_node *np);
बाह्य व्योम __of_detach_node_sysfs(काष्ठा device_node *np);

बाह्य व्योम __of_sysfs_हटाओ_bin_file(काष्ठा device_node *np,
				       काष्ठा property *prop);

/* illegal phandle value (set when unresolved) */
#घोषणा OF_PHANDLE_ILLEGAL	0xdeadbeef

/* iterators क्रम transactions, used क्रम overlays */
/* क्रमward iterator */
#घोषणा क्रम_each_transaction_entry(_oft, _te) \
	list_क्रम_each_entry(_te, &(_oft)->te_list, node)

/* reverse iterator */
#घोषणा क्रम_each_transaction_entry_reverse(_oft, _te) \
	list_क्रम_each_entry_reverse(_te, &(_oft)->te_list, node)

बाह्य पूर्णांक of_bus_n_addr_cells(काष्ठा device_node *np);
बाह्य पूर्णांक of_bus_n_size_cells(काष्ठा device_node *np);

काष्ठा bus_dma_region;
#अगर defined(CONFIG_OF_ADDRESS) && defined(CONFIG_HAS_DMA)
पूर्णांक of_dma_get_range(काष्ठा device_node *np,
		स्थिर काष्ठा bus_dma_region **map);
#अन्यथा
अटल अंतरभूत पूर्णांक of_dma_get_range(काष्ठा device_node *np,
		स्थिर काष्ठा bus_dma_region **map)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_OF_PRIVATE_H */
