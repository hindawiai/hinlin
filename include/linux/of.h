<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित _LINUX_OF_H
#घोषणा _LINUX_OF_H
/*
 * Definitions क्रम talking to the Open Firmware PROM on
 * Power Macपूर्णांकosh and other computers.
 *
 * Copyright (C) 1996-2005 Paul Mackerras.
 *
 * Updates क्रम PPC64 by Peter Bergner & David Engebretsen, IBM Corp.
 * Updates क्रम SPARC64 by David S. Miller
 * Derived from PowerPC and Sparc prom.h files by Stephen Rothwell, IBM Corp.
 */
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kobject.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/topology.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/property.h>
#समावेश <linux/list.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/त्रुटिसं.स>

प्रकार u32 phandle;
प्रकार u32 ihandle;

काष्ठा property अणु
	अक्षर	*name;
	पूर्णांक	length;
	व्योम	*value;
	काष्ठा property *next;
#अगर defined(CONFIG_OF_DYNAMIC) || defined(CONFIG_SPARC)
	अचिन्हित दीर्घ _flags;
#पूर्ण_अगर
#अगर defined(CONFIG_OF_PROMTREE)
	अचिन्हित पूर्णांक unique_id;
#पूर्ण_अगर
#अगर defined(CONFIG_OF_KOBJ)
	काष्ठा bin_attribute attr;
#पूर्ण_अगर
पूर्ण;

#अगर defined(CONFIG_SPARC)
काष्ठा of_irq_controller;
#पूर्ण_अगर

काष्ठा device_node अणु
	स्थिर अक्षर *name;
	phandle phandle;
	स्थिर अक्षर *full_name;
	काष्ठा fwnode_handle fwnode;

	काष्ठा	property *properties;
	काष्ठा	property *deadprops;	/* हटाओd properties */
	काष्ठा	device_node *parent;
	काष्ठा	device_node *child;
	काष्ठा	device_node *sibling;
#अगर defined(CONFIG_OF_KOBJ)
	काष्ठा	kobject kobj;
#पूर्ण_अगर
	अचिन्हित दीर्घ _flags;
	व्योम	*data;
#अगर defined(CONFIG_SPARC)
	अचिन्हित पूर्णांक unique_id;
	काष्ठा of_irq_controller *irq_trans;
#पूर्ण_अगर
पूर्ण;

#घोषणा MAX_PHANDLE_ARGS 16
काष्ठा of_phandle_args अणु
	काष्ठा device_node *np;
	पूर्णांक args_count;
	uपूर्णांक32_t args[MAX_PHANDLE_ARGS];
पूर्ण;

काष्ठा of_phandle_iterator अणु
	/* Common iterator inक्रमmation */
	स्थिर अक्षर *cells_name;
	पूर्णांक cell_count;
	स्थिर काष्ठा device_node *parent;

	/* List size inक्रमmation */
	स्थिर __be32 *list_end;
	स्थिर __be32 *phandle_end;

	/* Current position state */
	स्थिर __be32 *cur;
	uपूर्णांक32_t cur_count;
	phandle phandle;
	काष्ठा device_node *node;
पूर्ण;

काष्ठा of_reconfig_data अणु
	काष्ठा device_node	*dn;
	काष्ठा property		*prop;
	काष्ठा property		*old_prop;
पूर्ण;

/* initialize a node */
बाह्य काष्ठा kobj_type of_node_ktype;
बाह्य स्थिर काष्ठा fwnode_operations of_fwnode_ops;
अटल अंतरभूत व्योम of_node_init(काष्ठा device_node *node)
अणु
#अगर defined(CONFIG_OF_KOBJ)
	kobject_init(&node->kobj, &of_node_ktype);
#पूर्ण_अगर
	fwnode_init(&node->fwnode, &of_fwnode_ops);
पूर्ण

#अगर defined(CONFIG_OF_KOBJ)
#घोषणा of_node_kobj(n) (&(n)->kobj)
#अन्यथा
#घोषणा of_node_kobj(n) शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF_DYNAMIC
बाह्य काष्ठा device_node *of_node_get(काष्ठा device_node *node);
बाह्य व्योम of_node_put(काष्ठा device_node *node);
#अन्यथा /* CONFIG_OF_DYNAMIC */
/* Dummy ref counting routines - to be implemented later */
अटल अंतरभूत काष्ठा device_node *of_node_get(काष्ठा device_node *node)
अणु
	वापस node;
पूर्ण
अटल अंतरभूत व्योम of_node_put(काष्ठा device_node *node) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_OF_DYNAMIC */

/* Poपूर्णांकer क्रम first entry in chain of all nodes. */
बाह्य काष्ठा device_node *of_root;
बाह्य काष्ठा device_node *of_chosen;
बाह्य काष्ठा device_node *of_aliases;
बाह्य काष्ठा device_node *of_मानक_निकास;
बाह्य raw_spinlock_t devtree_lock;

/*
 * काष्ठा device_node flag descriptions
 * (need to be visible even when !CONFIG_OF)
 */
#घोषणा OF_DYNAMIC		1 /* (and properties) allocated via kदो_स्मृति */
#घोषणा OF_DETACHED		2 /* detached from the device tree */
#घोषणा OF_POPULATED		3 /* device alपढ़ोy created */
#घोषणा OF_POPULATED_BUS	4 /* platक्रमm bus created क्रम children */
#घोषणा OF_OVERLAY		5 /* allocated क्रम an overlay */
#घोषणा OF_OVERLAY_FREE_CSET	6 /* in overlay cset being मुक्तd */

#घोषणा OF_BAD_ADDR	((u64)-1)

#अगर_घोषित CONFIG_OF
व्योम of_core_init(व्योम);

अटल अंतरभूत bool is_of_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस !IS_ERR_OR_शून्य(fwnode) && fwnode->ops == &of_fwnode_ops;
पूर्ण

#घोषणा to_of_node(__fwnode)						\
	(अणु								\
		typeof(__fwnode) __to_of_node_fwnode = (__fwnode);	\
									\
		is_of_node(__to_of_node_fwnode) ?			\
			container_of(__to_of_node_fwnode,		\
				     काष्ठा device_node, fwnode) :	\
			शून्य;						\
	पूर्ण)

#घोषणा of_fwnode_handle(node)						\
	(अणु								\
		typeof(node) __of_fwnode_handle_node = (node);		\
									\
		__of_fwnode_handle_node ?				\
			&__of_fwnode_handle_node->fwnode : शून्य;	\
	पूर्ण)

अटल अंतरभूत bool of_have_populated_dt(व्योम)
अणु
	वापस of_root != शून्य;
पूर्ण

अटल अंतरभूत bool of_node_is_root(स्थिर काष्ठा device_node *node)
अणु
	वापस node && (node->parent == शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक of_node_check_flag(काष्ठा device_node *n, अचिन्हित दीर्घ flag)
अणु
	वापस test_bit(flag, &n->_flags);
पूर्ण

अटल अंतरभूत पूर्णांक of_node_test_and_set_flag(काष्ठा device_node *n,
					    अचिन्हित दीर्घ flag)
अणु
	वापस test_and_set_bit(flag, &n->_flags);
पूर्ण

अटल अंतरभूत व्योम of_node_set_flag(काष्ठा device_node *n, अचिन्हित दीर्घ flag)
अणु
	set_bit(flag, &n->_flags);
पूर्ण

अटल अंतरभूत व्योम of_node_clear_flag(काष्ठा device_node *n, अचिन्हित दीर्घ flag)
अणु
	clear_bit(flag, &n->_flags);
पूर्ण

#अगर defined(CONFIG_OF_DYNAMIC) || defined(CONFIG_SPARC)
अटल अंतरभूत पूर्णांक of_property_check_flag(काष्ठा property *p, अचिन्हित दीर्घ flag)
अणु
	वापस test_bit(flag, &p->_flags);
पूर्ण

अटल अंतरभूत व्योम of_property_set_flag(काष्ठा property *p, अचिन्हित दीर्घ flag)
अणु
	set_bit(flag, &p->_flags);
पूर्ण

अटल अंतरभूत व्योम of_property_clear_flag(काष्ठा property *p, अचिन्हित दीर्घ flag)
अणु
	clear_bit(flag, &p->_flags);
पूर्ण
#पूर्ण_अगर

बाह्य काष्ठा device_node *__of_find_all_nodes(काष्ठा device_node *prev);
बाह्य काष्ठा device_node *of_find_all_nodes(काष्ठा device_node *prev);

/*
 * OF address retrieval & translation
 */

/* Helper to पढ़ो a big number; size is in cells (not bytes) */
अटल अंतरभूत u64 of_पढ़ो_number(स्थिर __be32 *cell, पूर्णांक size)
अणु
	u64 r = 0;
	क्रम (; size--; cell++)
		r = (r << 32) | be32_to_cpu(*cell);
	वापस r;
पूर्ण

/* Like of_पढ़ो_number, but we want an अचिन्हित दीर्घ result */
अटल अंतरभूत अचिन्हित दीर्घ of_पढ़ो_uदीर्घ(स्थिर __be32 *cell, पूर्णांक size)
अणु
	/* toss away upper bits अगर अचिन्हित दीर्घ is smaller than u64 */
	वापस of_पढ़ो_number(cell, size);
पूर्ण

#अगर defined(CONFIG_SPARC)
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर

#घोषणा OF_IS_DYNAMIC(x) test_bit(OF_DYNAMIC, &x->_flags)
#घोषणा OF_MARK_DYNAMIC(x) set_bit(OF_DYNAMIC, &x->_flags)

बाह्य bool of_node_name_eq(स्थिर काष्ठा device_node *np, स्थिर अक्षर *name);
बाह्य bool of_node_name_prefix(स्थिर काष्ठा device_node *np, स्थिर अक्षर *prefix);

अटल अंतरभूत स्थिर अक्षर *of_node_full_name(स्थिर काष्ठा device_node *np)
अणु
	वापस np ? np->full_name : "<no-node>";
पूर्ण

#घोषणा क्रम_each_of_allnodes_from(from, dn) \
	क्रम (dn = __of_find_all_nodes(from); dn; dn = __of_find_all_nodes(dn))
#घोषणा क्रम_each_of_allnodes(dn) क्रम_each_of_allnodes_from(शून्य, dn)
बाह्य काष्ठा device_node *of_find_node_by_name(काष्ठा device_node *from,
	स्थिर अक्षर *name);
बाह्य काष्ठा device_node *of_find_node_by_type(काष्ठा device_node *from,
	स्थिर अक्षर *type);
बाह्य काष्ठा device_node *of_find_compatible_node(काष्ठा device_node *from,
	स्थिर अक्षर *type, स्थिर अक्षर *compat);
बाह्य काष्ठा device_node *of_find_matching_node_and_match(
	काष्ठा device_node *from,
	स्थिर काष्ठा of_device_id *matches,
	स्थिर काष्ठा of_device_id **match);

बाह्य काष्ठा device_node *of_find_node_opts_by_path(स्थिर अक्षर *path,
	स्थिर अक्षर **opts);
अटल अंतरभूत काष्ठा device_node *of_find_node_by_path(स्थिर अक्षर *path)
अणु
	वापस of_find_node_opts_by_path(path, शून्य);
पूर्ण

बाह्य काष्ठा device_node *of_find_node_by_phandle(phandle handle);
बाह्य काष्ठा device_node *of_get_parent(स्थिर काष्ठा device_node *node);
बाह्य काष्ठा device_node *of_get_next_parent(काष्ठा device_node *node);
बाह्य काष्ठा device_node *of_get_next_child(स्थिर काष्ठा device_node *node,
					     काष्ठा device_node *prev);
बाह्य काष्ठा device_node *of_get_next_available_child(
	स्थिर काष्ठा device_node *node, काष्ठा device_node *prev);

बाह्य काष्ठा device_node *of_get_compatible_child(स्थिर काष्ठा device_node *parent,
					स्थिर अक्षर *compatible);
बाह्य काष्ठा device_node *of_get_child_by_name(स्थिर काष्ठा device_node *node,
					स्थिर अक्षर *name);

/* cache lookup */
बाह्य काष्ठा device_node *of_find_next_cache_node(स्थिर काष्ठा device_node *);
बाह्य पूर्णांक of_find_last_cache_level(अचिन्हित पूर्णांक cpu);
बाह्य काष्ठा device_node *of_find_node_with_property(
	काष्ठा device_node *from, स्थिर अक्षर *prop_name);

बाह्य काष्ठा property *of_find_property(स्थिर काष्ठा device_node *np,
					 स्थिर अक्षर *name,
					 पूर्णांक *lenp);
बाह्य पूर्णांक of_property_count_elems_of_size(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *propname, पूर्णांक elem_size);
बाह्य पूर्णांक of_property_पढ़ो_u32_index(स्थिर काष्ठा device_node *np,
				       स्थिर अक्षर *propname,
				       u32 index, u32 *out_value);
बाह्य पूर्णांक of_property_पढ़ो_u64_index(स्थिर काष्ठा device_node *np,
				       स्थिर अक्षर *propname,
				       u32 index, u64 *out_value);
बाह्य पूर्णांक of_property_पढ़ो_variable_u8_array(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *propname, u8 *out_values,
					माप_प्रकार sz_min, माप_प्रकार sz_max);
बाह्य पूर्णांक of_property_पढ़ो_variable_u16_array(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *propname, u16 *out_values,
					माप_प्रकार sz_min, माप_प्रकार sz_max);
बाह्य पूर्णांक of_property_पढ़ो_variable_u32_array(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *propname,
					u32 *out_values,
					माप_प्रकार sz_min,
					माप_प्रकार sz_max);
बाह्य पूर्णांक of_property_पढ़ो_u64(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *propname, u64 *out_value);
बाह्य पूर्णांक of_property_पढ़ो_variable_u64_array(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *propname,
					u64 *out_values,
					माप_प्रकार sz_min,
					माप_प्रकार sz_max);

बाह्य पूर्णांक of_property_पढ़ो_string(स्थिर काष्ठा device_node *np,
				   स्थिर अक्षर *propname,
				   स्थिर अक्षर **out_string);
बाह्य पूर्णांक of_property_match_string(स्थिर काष्ठा device_node *np,
				    स्थिर अक्षर *propname,
				    स्थिर अक्षर *string);
बाह्य पूर्णांक of_property_पढ़ो_string_helper(स्थिर काष्ठा device_node *np,
					      स्थिर अक्षर *propname,
					      स्थिर अक्षर **out_strs, माप_प्रकार sz, पूर्णांक index);
बाह्य पूर्णांक of_device_is_compatible(स्थिर काष्ठा device_node *device,
				   स्थिर अक्षर *);
बाह्य पूर्णांक of_device_compatible_match(काष्ठा device_node *device,
				      स्थिर अक्षर *स्थिर *compat);
बाह्य bool of_device_is_available(स्थिर काष्ठा device_node *device);
बाह्य bool of_device_is_big_endian(स्थिर काष्ठा device_node *device);
बाह्य स्थिर व्योम *of_get_property(स्थिर काष्ठा device_node *node,
				स्थिर अक्षर *name,
				पूर्णांक *lenp);
बाह्य काष्ठा device_node *of_get_cpu_node(पूर्णांक cpu, अचिन्हित पूर्णांक *thपढ़ो);
बाह्य काष्ठा device_node *of_get_next_cpu_node(काष्ठा device_node *prev);
बाह्य काष्ठा device_node *of_get_cpu_state_node(काष्ठा device_node *cpu_node,
						 पूर्णांक index);

#घोषणा क्रम_each_property_of_node(dn, pp) \
	क्रम (pp = dn->properties; pp != शून्य; pp = pp->next)

बाह्य पूर्णांक of_n_addr_cells(काष्ठा device_node *np);
बाह्य पूर्णांक of_n_size_cells(काष्ठा device_node *np);
बाह्य स्थिर काष्ठा of_device_id *of_match_node(
	स्थिर काष्ठा of_device_id *matches, स्थिर काष्ठा device_node *node);
बाह्य पूर्णांक of_modalias_node(काष्ठा device_node *node, अक्षर *modalias, पूर्णांक len);
बाह्य व्योम of_prपूर्णांक_phandle_args(स्थिर अक्षर *msg, स्थिर काष्ठा of_phandle_args *args);
बाह्य काष्ठा device_node *of_parse_phandle(स्थिर काष्ठा device_node *np,
					    स्थिर अक्षर *phandle_name,
					    पूर्णांक index);
बाह्य पूर्णांक of_parse_phandle_with_args(स्थिर काष्ठा device_node *np,
	स्थिर अक्षर *list_name, स्थिर अक्षर *cells_name, पूर्णांक index,
	काष्ठा of_phandle_args *out_args);
बाह्य पूर्णांक of_parse_phandle_with_args_map(स्थिर काष्ठा device_node *np,
	स्थिर अक्षर *list_name, स्थिर अक्षर *stem_name, पूर्णांक index,
	काष्ठा of_phandle_args *out_args);
बाह्य पूर्णांक of_parse_phandle_with_fixed_args(स्थिर काष्ठा device_node *np,
	स्थिर अक्षर *list_name, पूर्णांक cells_count, पूर्णांक index,
	काष्ठा of_phandle_args *out_args);
बाह्य पूर्णांक of_count_phandle_with_args(स्थिर काष्ठा device_node *np,
	स्थिर अक्षर *list_name, स्थिर अक्षर *cells_name);

/* phandle iterator functions */
बाह्य पूर्णांक of_phandle_iterator_init(काष्ठा of_phandle_iterator *it,
				    स्थिर काष्ठा device_node *np,
				    स्थिर अक्षर *list_name,
				    स्थिर अक्षर *cells_name,
				    पूर्णांक cell_count);

बाह्य पूर्णांक of_phandle_iterator_next(काष्ठा of_phandle_iterator *it);
बाह्य पूर्णांक of_phandle_iterator_args(काष्ठा of_phandle_iterator *it,
				    uपूर्णांक32_t *args,
				    पूर्णांक size);

बाह्य व्योम of_alias_scan(व्योम * (*dt_alloc)(u64 size, u64 align));
बाह्य पूर्णांक of_alias_get_id(काष्ठा device_node *np, स्थिर अक्षर *stem);
बाह्य पूर्णांक of_alias_get_highest_id(स्थिर अक्षर *stem);
बाह्य पूर्णांक of_alias_get_alias_list(स्थिर काष्ठा of_device_id *matches,
				   स्थिर अक्षर *stem, अचिन्हित दीर्घ *biपंचांगap,
				   अचिन्हित पूर्णांक nbits);

बाह्य पूर्णांक of_machine_is_compatible(स्थिर अक्षर *compat);

बाह्य पूर्णांक of_add_property(काष्ठा device_node *np, काष्ठा property *prop);
बाह्य पूर्णांक of_हटाओ_property(काष्ठा device_node *np, काष्ठा property *prop);
बाह्य पूर्णांक of_update_property(काष्ठा device_node *np, काष्ठा property *newprop);

/* For updating the device tree at runसमय */
#घोषणा OF_RECONFIG_ATTACH_NODE		0x0001
#घोषणा OF_RECONFIG_DETACH_NODE		0x0002
#घोषणा OF_RECONFIG_ADD_PROPERTY	0x0003
#घोषणा OF_RECONFIG_REMOVE_PROPERTY	0x0004
#घोषणा OF_RECONFIG_UPDATE_PROPERTY	0x0005

बाह्य पूर्णांक of_attach_node(काष्ठा device_node *);
बाह्य पूर्णांक of_detach_node(काष्ठा device_node *);

#घोषणा of_match_ptr(_ptr)	(_ptr)

/**
 * of_property_पढ़ो_u8_array - Find and पढ़ो an array of u8 from a property.
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_values:	poपूर्णांकer to वापस value, modअगरied only अगर वापस value is 0.
 * @sz:		number of array elements to पढ़ो
 *
 * Search क्रम a property in a device node and पढ़ो 8-bit value(s) from
 * it.
 *
 * dts entry of array should be like:
 *  ``property = /bits/ 8 <0x50 0x60 0x70>;``
 *
 * Return: 0 on success, -EINVAL अगर the property करोes not exist,
 * -ENODATA अगर property करोes not have a value, and -EOVERFLOW अगर the
 * property data isn't large enough.
 *
 * The out_values is modअगरied only अगर a valid u8 value can be decoded.
 */
अटल अंतरभूत पूर्णांक of_property_पढ़ो_u8_array(स्थिर काष्ठा device_node *np,
					    स्थिर अक्षर *propname,
					    u8 *out_values, माप_प्रकार sz)
अणु
	पूर्णांक ret = of_property_पढ़ो_variable_u8_array(np, propname, out_values,
						     sz, 0);
	अगर (ret >= 0)
		वापस 0;
	अन्यथा
		वापस ret;
पूर्ण

/**
 * of_property_पढ़ो_u16_array - Find and पढ़ो an array of u16 from a property.
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_values:	poपूर्णांकer to वापस value, modअगरied only अगर वापस value is 0.
 * @sz:		number of array elements to पढ़ो
 *
 * Search क्रम a property in a device node and पढ़ो 16-bit value(s) from
 * it.
 *
 * dts entry of array should be like:
 *  ``property = /bits/ 16 <0x5000 0x6000 0x7000>;``
 *
 * Return: 0 on success, -EINVAL अगर the property करोes not exist,
 * -ENODATA अगर property करोes not have a value, and -EOVERFLOW अगर the
 * property data isn't large enough.
 *
 * The out_values is modअगरied only अगर a valid u16 value can be decoded.
 */
अटल अंतरभूत पूर्णांक of_property_पढ़ो_u16_array(स्थिर काष्ठा device_node *np,
					     स्थिर अक्षर *propname,
					     u16 *out_values, माप_प्रकार sz)
अणु
	पूर्णांक ret = of_property_पढ़ो_variable_u16_array(np, propname, out_values,
						      sz, 0);
	अगर (ret >= 0)
		वापस 0;
	अन्यथा
		वापस ret;
पूर्ण

/**
 * of_property_पढ़ो_u32_array - Find and पढ़ो an array of 32 bit पूर्णांकegers
 * from a property.
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_values:	poपूर्णांकer to वापस value, modअगरied only अगर वापस value is 0.
 * @sz:		number of array elements to पढ़ो
 *
 * Search क्रम a property in a device node and पढ़ो 32-bit value(s) from
 * it.
 *
 * Return: 0 on success, -EINVAL अगर the property करोes not exist,
 * -ENODATA अगर property करोes not have a value, and -EOVERFLOW अगर the
 * property data isn't large enough.
 *
 * The out_values is modअगरied only अगर a valid u32 value can be decoded.
 */
अटल अंतरभूत पूर्णांक of_property_पढ़ो_u32_array(स्थिर काष्ठा device_node *np,
					     स्थिर अक्षर *propname,
					     u32 *out_values, माप_प्रकार sz)
अणु
	पूर्णांक ret = of_property_पढ़ो_variable_u32_array(np, propname, out_values,
						      sz, 0);
	अगर (ret >= 0)
		वापस 0;
	अन्यथा
		वापस ret;
पूर्ण

/**
 * of_property_पढ़ो_u64_array - Find and पढ़ो an array of 64 bit पूर्णांकegers
 * from a property.
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_values:	poपूर्णांकer to वापस value, modअगरied only अगर वापस value is 0.
 * @sz:		number of array elements to पढ़ो
 *
 * Search क्रम a property in a device node and पढ़ो 64-bit value(s) from
 * it.
 *
 * Return: 0 on success, -EINVAL अगर the property करोes not exist,
 * -ENODATA अगर property करोes not have a value, and -EOVERFLOW अगर the
 * property data isn't large enough.
 *
 * The out_values is modअगरied only अगर a valid u64 value can be decoded.
 */
अटल अंतरभूत पूर्णांक of_property_पढ़ो_u64_array(स्थिर काष्ठा device_node *np,
					     स्थिर अक्षर *propname,
					     u64 *out_values, माप_प्रकार sz)
अणु
	पूर्णांक ret = of_property_पढ़ो_variable_u64_array(np, propname, out_values,
						      sz, 0);
	अगर (ret >= 0)
		वापस 0;
	अन्यथा
		वापस ret;
पूर्ण

/*
 * काष्ठा property *prop;
 * स्थिर __be32 *p;
 * u32 u;
 *
 * of_property_क्रम_each_u32(np, "propname", prop, p, u)
 *         prपूर्णांकk("U32 value: %x\n", u);
 */
स्थिर __be32 *of_prop_next_u32(काष्ठा property *prop, स्थिर __be32 *cur,
			       u32 *pu);
/*
 * काष्ठा property *prop;
 * स्थिर अक्षर *s;
 *
 * of_property_क्रम_each_string(np, "propname", prop, s)
 *         prपूर्णांकk("String value: %s\n", s);
 */
स्थिर अक्षर *of_prop_next_string(काष्ठा property *prop, स्थिर अक्षर *cur);

bool of_console_check(काष्ठा device_node *dn, अक्षर *name, पूर्णांक index);

बाह्य पूर्णांक of_cpu_node_to_id(काष्ठा device_node *np);

पूर्णांक of_map_id(काष्ठा device_node *np, u32 id,
	       स्थिर अक्षर *map_name, स्थिर अक्षर *map_mask_name,
	       काष्ठा device_node **target, u32 *id_out);

phys_addr_t of_dma_get_max_cpu_address(काष्ठा device_node *np);

काष्ठा kimage;
व्योम *of_kexec_alloc_and_setup_fdt(स्थिर काष्ठा kimage *image,
				   अचिन्हित दीर्घ initrd_load_addr,
				   अचिन्हित दीर्घ initrd_len,
				   स्थिर अक्षर *cmdline, माप_प्रकार extra_fdt_size);
पूर्णांक ima_get_kexec_buffer(व्योम **addr, माप_प्रकार *size);
पूर्णांक ima_मुक्त_kexec_buffer(व्योम);
#अन्यथा /* CONFIG_OF */

अटल अंतरभूत व्योम of_core_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत bool is_of_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा device_node *to_of_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool of_node_name_eq(स्थिर काष्ठा device_node *np, स्थिर अक्षर *name)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool of_node_name_prefix(स्थिर काष्ठा device_node *np, स्थिर अक्षर *prefix)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत स्थिर अक्षर* of_node_full_name(स्थिर काष्ठा device_node *np)
अणु
	वापस "<no-node>";
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_find_node_by_name(काष्ठा device_node *from,
	स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_find_node_by_type(काष्ठा device_node *from,
	स्थिर अक्षर *type)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_find_matching_node_and_match(
	काष्ठा device_node *from,
	स्थिर काष्ठा of_device_id *matches,
	स्थिर काष्ठा of_device_id **match)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_find_node_by_path(स्थिर अक्षर *path)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_find_node_opts_by_path(स्थिर अक्षर *path,
	स्थिर अक्षर **opts)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_find_node_by_phandle(phandle handle)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_get_parent(स्थिर काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_get_next_parent(काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_get_next_child(
	स्थिर काष्ठा device_node *node, काष्ठा device_node *prev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_get_next_available_child(
	स्थिर काष्ठा device_node *node, काष्ठा device_node *prev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_find_node_with_property(
	काष्ठा device_node *from, स्थिर अक्षर *prop_name)
अणु
	वापस शून्य;
पूर्ण

#घोषणा of_fwnode_handle(node) शून्य

अटल अंतरभूत bool of_have_populated_dt(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_get_compatible_child(स्थिर काष्ठा device_node *parent,
					स्थिर अक्षर *compatible)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_get_child_by_name(
					स्थिर काष्ठा device_node *node,
					स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_device_is_compatible(स्थिर काष्ठा device_node *device,
					  स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत  पूर्णांक of_device_compatible_match(काष्ठा device_node *device,
					      स्थिर अक्षर *स्थिर *compat)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool of_device_is_available(स्थिर काष्ठा device_node *device)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool of_device_is_big_endian(स्थिर काष्ठा device_node *device)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा property *of_find_property(स्थिर काष्ठा device_node *np,
						स्थिर अक्षर *name,
						पूर्णांक *lenp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_find_compatible_node(
						काष्ठा device_node *from,
						स्थिर अक्षर *type,
						स्थिर अक्षर *compat)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_count_elems_of_size(स्थिर काष्ठा device_node *np,
			स्थिर अक्षर *propname, पूर्णांक elem_size)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_u8_array(स्थिर काष्ठा device_node *np,
			स्थिर अक्षर *propname, u8 *out_values, माप_प्रकार sz)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_u16_array(स्थिर काष्ठा device_node *np,
			स्थिर अक्षर *propname, u16 *out_values, माप_प्रकार sz)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_u32_array(स्थिर काष्ठा device_node *np,
					     स्थिर अक्षर *propname,
					     u32 *out_values, माप_प्रकार sz)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_u64_array(स्थिर काष्ठा device_node *np,
					     स्थिर अक्षर *propname,
					     u64 *out_values, माप_प्रकार sz)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_u32_index(स्थिर काष्ठा device_node *np,
			स्थिर अक्षर *propname, u32 index, u32 *out_value)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_u64_index(स्थिर काष्ठा device_node *np,
			स्थिर अक्षर *propname, u32 index, u64 *out_value)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत स्थिर व्योम *of_get_property(स्थिर काष्ठा device_node *node,
				स्थिर अक्षर *name,
				पूर्णांक *lenp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_get_cpu_node(पूर्णांक cpu,
					अचिन्हित पूर्णांक *thपढ़ो)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_get_next_cpu_node(काष्ठा device_node *prev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_get_cpu_state_node(काष्ठा device_node *cpu_node,
					पूर्णांक index)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_n_addr_cells(काष्ठा device_node *np)
अणु
	वापस 0;

पूर्ण
अटल अंतरभूत पूर्णांक of_n_size_cells(काष्ठा device_node *np)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_variable_u8_array(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *propname, u8 *out_values,
					माप_प्रकार sz_min, माप_प्रकार sz_max)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_variable_u16_array(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *propname, u16 *out_values,
					माप_प्रकार sz_min, माप_प्रकार sz_max)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_variable_u32_array(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *propname,
					u32 *out_values,
					माप_प्रकार sz_min,
					माप_प्रकार sz_max)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_u64(स्थिर काष्ठा device_node *np,
				       स्थिर अक्षर *propname, u64 *out_value)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_variable_u64_array(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *propname,
					u64 *out_values,
					माप_प्रकार sz_min,
					माप_प्रकार sz_max)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_string(स्थिर काष्ठा device_node *np,
					  स्थिर अक्षर *propname,
					  स्थिर अक्षर **out_string)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_match_string(स्थिर काष्ठा device_node *np,
					   स्थिर अक्षर *propname,
					   स्थिर अक्षर *string)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_string_helper(स्थिर काष्ठा device_node *np,
						 स्थिर अक्षर *propname,
						 स्थिर अक्षर **out_strs, माप_प्रकार sz, पूर्णांक index)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_parse_phandle(स्थिर काष्ठा device_node *np,
						   स्थिर अक्षर *phandle_name,
						   पूर्णांक index)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_parse_phandle_with_args(स्थिर काष्ठा device_node *np,
					     स्थिर अक्षर *list_name,
					     स्थिर अक्षर *cells_name,
					     पूर्णांक index,
					     काष्ठा of_phandle_args *out_args)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_parse_phandle_with_args_map(स्थिर काष्ठा device_node *np,
						 स्थिर अक्षर *list_name,
						 स्थिर अक्षर *stem_name,
						 पूर्णांक index,
						 काष्ठा of_phandle_args *out_args)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_parse_phandle_with_fixed_args(स्थिर काष्ठा device_node *np,
	स्थिर अक्षर *list_name, पूर्णांक cells_count, पूर्णांक index,
	काष्ठा of_phandle_args *out_args)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_count_phandle_with_args(काष्ठा device_node *np,
					     स्थिर अक्षर *list_name,
					     स्थिर अक्षर *cells_name)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_phandle_iterator_init(काष्ठा of_phandle_iterator *it,
					   स्थिर काष्ठा device_node *np,
					   स्थिर अक्षर *list_name,
					   स्थिर अक्षर *cells_name,
					   पूर्णांक cell_count)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_phandle_iterator_next(काष्ठा of_phandle_iterator *it)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_phandle_iterator_args(काष्ठा of_phandle_iterator *it,
					   uपूर्णांक32_t *args,
					   पूर्णांक size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक of_alias_get_id(काष्ठा device_node *np, स्थिर अक्षर *stem)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_alias_get_highest_id(स्थिर अक्षर *stem)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_alias_get_alias_list(स्थिर काष्ठा of_device_id *matches,
					  स्थिर अक्षर *stem, अचिन्हित दीर्घ *biपंचांगap,
					  अचिन्हित पूर्णांक nbits)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_machine_is_compatible(स्थिर अक्षर *compat)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक of_हटाओ_property(काष्ठा device_node *np, काष्ठा property *prop)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool of_console_check(स्थिर काष्ठा device_node *dn, स्थिर अक्षर *name, पूर्णांक index)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत स्थिर __be32 *of_prop_next_u32(काष्ठा property *prop,
		स्थिर __be32 *cur, u32 *pu)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *of_prop_next_string(काष्ठा property *prop,
		स्थिर अक्षर *cur)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक of_node_check_flag(काष्ठा device_node *n, अचिन्हित दीर्घ flag)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक of_node_test_and_set_flag(काष्ठा device_node *n,
					    अचिन्हित दीर्घ flag)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम of_node_set_flag(काष्ठा device_node *n, अचिन्हित दीर्घ flag)
अणु
पूर्ण

अटल अंतरभूत व्योम of_node_clear_flag(काष्ठा device_node *n, अचिन्हित दीर्घ flag)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक of_property_check_flag(काष्ठा property *p, अचिन्हित दीर्घ flag)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम of_property_set_flag(काष्ठा property *p, अचिन्हित दीर्घ flag)
अणु
पूर्ण

अटल अंतरभूत व्योम of_property_clear_flag(काष्ठा property *p, अचिन्हित दीर्घ flag)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक of_cpu_node_to_id(काष्ठा device_node *np)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक of_map_id(काष्ठा device_node *np, u32 id,
			     स्थिर अक्षर *map_name, स्थिर अक्षर *map_mask_name,
			     काष्ठा device_node **target, u32 *id_out)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत phys_addr_t of_dma_get_max_cpu_address(काष्ठा device_node *np)
अणु
	वापस PHYS_ADDR_MAX;
पूर्ण

#घोषणा of_match_ptr(_ptr)	शून्य
#घोषणा of_match_node(_matches, _node)	शून्य
#पूर्ण_अगर /* CONFIG_OF */

/* Default string compare functions, Allow arch यंत्र/prom.h to override */
#अगर !defined(of_compat_cmp)
#घोषणा of_compat_cmp(s1, s2, l)	strहालcmp((s1), (s2))
#घोषणा of_prop_cmp(s1, s2)		म_भेद((s1), (s2))
#घोषणा of_node_cmp(s1, s2)		strहालcmp((s1), (s2))
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक of_prop_val_eq(काष्ठा property *p1, काष्ठा property *p2)
अणु
	वापस p1->length == p2->length &&
	       !स_भेद(p1->value, p2->value, (माप_प्रकार)p1->length);
पूर्ण

#अगर defined(CONFIG_OF) && defined(CONFIG_NUMA)
बाह्य पूर्णांक of_node_to_nid(काष्ठा device_node *np);
#अन्यथा
अटल अंतरभूत पूर्णांक of_node_to_nid(काष्ठा device_node *device)
अणु
	वापस NUMA_NO_NODE;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF_NUMA
बाह्य पूर्णांक of_numa_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक of_numa_init(व्योम)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा device_node *of_find_matching_node(
	काष्ठा device_node *from,
	स्थिर काष्ठा of_device_id *matches)
अणु
	वापस of_find_matching_node_and_match(from, matches, शून्य);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *of_node_get_device_type(स्थिर काष्ठा device_node *np)
अणु
	वापस of_get_property(np, "device_type", शून्य);
पूर्ण

अटल अंतरभूत bool of_node_is_type(स्थिर काष्ठा device_node *np, स्थिर अक्षर *type)
अणु
	स्थिर अक्षर *match = of_node_get_device_type(np);

	वापस np && match && type && !म_भेद(match, type);
पूर्ण

/**
 * of_property_count_u8_elems - Count the number of u8 elements in a property
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 *
 * Search क्रम a property in a device node and count the number of u8 elements
 * in it.
 *
 * Return: The number of elements on sucess, -EINVAL अगर the property करोes
 * not exist or its length करोes not match a multiple of u8 and -ENODATA अगर the
 * property करोes not have a value.
 */
अटल अंतरभूत पूर्णांक of_property_count_u8_elems(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *propname)
अणु
	वापस of_property_count_elems_of_size(np, propname, माप(u8));
पूर्ण

/**
 * of_property_count_u16_elems - Count the number of u16 elements in a property
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 *
 * Search क्रम a property in a device node and count the number of u16 elements
 * in it.
 *
 * Return: The number of elements on sucess, -EINVAL अगर the property करोes
 * not exist or its length करोes not match a multiple of u16 and -ENODATA अगर the
 * property करोes not have a value.
 */
अटल अंतरभूत पूर्णांक of_property_count_u16_elems(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *propname)
अणु
	वापस of_property_count_elems_of_size(np, propname, माप(u16));
पूर्ण

/**
 * of_property_count_u32_elems - Count the number of u32 elements in a property
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 *
 * Search क्रम a property in a device node and count the number of u32 elements
 * in it.
 *
 * Return: The number of elements on sucess, -EINVAL अगर the property करोes
 * not exist or its length करोes not match a multiple of u32 and -ENODATA अगर the
 * property करोes not have a value.
 */
अटल अंतरभूत पूर्णांक of_property_count_u32_elems(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *propname)
अणु
	वापस of_property_count_elems_of_size(np, propname, माप(u32));
पूर्ण

/**
 * of_property_count_u64_elems - Count the number of u64 elements in a property
 *
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 *
 * Search क्रम a property in a device node and count the number of u64 elements
 * in it.
 *
 * Return: The number of elements on sucess, -EINVAL अगर the property करोes
 * not exist or its length करोes not match a multiple of u64 and -ENODATA अगर the
 * property करोes not have a value.
 */
अटल अंतरभूत पूर्णांक of_property_count_u64_elems(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *propname)
अणु
	वापस of_property_count_elems_of_size(np, propname, माप(u64));
पूर्ण

/**
 * of_property_पढ़ो_string_array() - Read an array of strings from a multiple
 * strings property.
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @out_strs:	output array of string poपूर्णांकers.
 * @sz:		number of array elements to पढ़ो.
 *
 * Search क्रम a property in a device tree node and retrieve a list of
 * terminated string values (poपूर्णांकer to data, not a copy) in that property.
 *
 * Return: If @out_strs is शून्य, the number of strings in the property is वापसed.
 */
अटल अंतरभूत पूर्णांक of_property_पढ़ो_string_array(स्थिर काष्ठा device_node *np,
						स्थिर अक्षर *propname, स्थिर अक्षर **out_strs,
						माप_प्रकार sz)
अणु
	वापस of_property_पढ़ो_string_helper(np, propname, out_strs, sz, 0);
पूर्ण

/**
 * of_property_count_strings() - Find and वापस the number of strings from a
 * multiple strings property.
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 *
 * Search क्रम a property in a device tree node and retrieve the number of null
 * terminated string contain in it.
 *
 * Return: The number of strings on success, -EINVAL अगर the property करोes not
 * exist, -ENODATA अगर property करोes not have a value, and -EILSEQ अगर the string
 * is not null-terminated within the length of the property data.
 */
अटल अंतरभूत पूर्णांक of_property_count_strings(स्थिर काष्ठा device_node *np,
					    स्थिर अक्षर *propname)
अणु
	वापस of_property_पढ़ो_string_helper(np, propname, शून्य, 0, 0);
पूर्ण

/**
 * of_property_पढ़ो_string_index() - Find and पढ़ो a string from a multiple
 * strings property.
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 * @index:	index of the string in the list of strings
 * @output:	poपूर्णांकer to null terminated वापस string, modअगरied only अगर
 *		वापस value is 0.
 *
 * Search क्रम a property in a device tree node and retrieve a null
 * terminated string value (poपूर्णांकer to data, not a copy) in the list of strings
 * contained in that property.
 *
 * Return: 0 on success, -EINVAL अगर the property करोes not exist, -ENODATA अगर
 * property करोes not have a value, and -EILSEQ अगर the string is not
 * null-terminated within the length of the property data.
 *
 * The out_string poपूर्णांकer is modअगरied only अगर a valid string can be decoded.
 */
अटल अंतरभूत पूर्णांक of_property_पढ़ो_string_index(स्थिर काष्ठा device_node *np,
						स्थिर अक्षर *propname,
						पूर्णांक index, स्थिर अक्षर **output)
अणु
	पूर्णांक rc = of_property_पढ़ो_string_helper(np, propname, output, 1, index);
	वापस rc < 0 ? rc : 0;
पूर्ण

/**
 * of_property_पढ़ो_bool - Find a property
 * @np:		device node from which the property value is to be पढ़ो.
 * @propname:	name of the property to be searched.
 *
 * Search क्रम a property in a device node.
 *
 * Return: true अगर the property exists false otherwise.
 */
अटल अंतरभूत bool of_property_पढ़ो_bool(स्थिर काष्ठा device_node *np,
					 स्थिर अक्षर *propname)
अणु
	काष्ठा property *prop = of_find_property(np, propname, शून्य);

	वापस prop ? true : false;
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_u8(स्थिर काष्ठा device_node *np,
				       स्थिर अक्षर *propname,
				       u8 *out_value)
अणु
	वापस of_property_पढ़ो_u8_array(np, propname, out_value, 1);
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_u16(स्थिर काष्ठा device_node *np,
				       स्थिर अक्षर *propname,
				       u16 *out_value)
अणु
	वापस of_property_पढ़ो_u16_array(np, propname, out_value, 1);
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_u32(स्थिर काष्ठा device_node *np,
				       स्थिर अक्षर *propname,
				       u32 *out_value)
अणु
	वापस of_property_पढ़ो_u32_array(np, propname, out_value, 1);
पूर्ण

अटल अंतरभूत पूर्णांक of_property_पढ़ो_s32(स्थिर काष्ठा device_node *np,
				       स्थिर अक्षर *propname,
				       s32 *out_value)
अणु
	वापस of_property_पढ़ो_u32(np, propname, (u32*) out_value);
पूर्ण

#घोषणा of_क्रम_each_phandle(it, err, np, ln, cn, cc)			\
	क्रम (of_phandle_iterator_init((it), (np), (ln), (cn), (cc)),	\
	     err = of_phandle_iterator_next(it);			\
	     err == 0;							\
	     err = of_phandle_iterator_next(it))

#घोषणा of_property_क्रम_each_u32(np, propname, prop, p, u)	\
	क्रम (prop = of_find_property(np, propname, शून्य),	\
		p = of_prop_next_u32(prop, शून्य, &u);		\
		p;						\
		p = of_prop_next_u32(prop, p, &u))

#घोषणा of_property_क्रम_each_string(np, propname, prop, s)	\
	क्रम (prop = of_find_property(np, propname, शून्य),	\
		s = of_prop_next_string(prop, शून्य);		\
		s;						\
		s = of_prop_next_string(prop, s))

#घोषणा क्रम_each_node_by_name(dn, name) \
	क्रम (dn = of_find_node_by_name(शून्य, name); dn; \
	     dn = of_find_node_by_name(dn, name))
#घोषणा क्रम_each_node_by_type(dn, type) \
	क्रम (dn = of_find_node_by_type(शून्य, type); dn; \
	     dn = of_find_node_by_type(dn, type))
#घोषणा क्रम_each_compatible_node(dn, type, compatible) \
	क्रम (dn = of_find_compatible_node(शून्य, type, compatible); dn; \
	     dn = of_find_compatible_node(dn, type, compatible))
#घोषणा क्रम_each_matching_node(dn, matches) \
	क्रम (dn = of_find_matching_node(शून्य, matches); dn; \
	     dn = of_find_matching_node(dn, matches))
#घोषणा क्रम_each_matching_node_and_match(dn, matches, match) \
	क्रम (dn = of_find_matching_node_and_match(शून्य, matches, match); \
	     dn; dn = of_find_matching_node_and_match(dn, matches, match))

#घोषणा क्रम_each_child_of_node(parent, child) \
	क्रम (child = of_get_next_child(parent, शून्य); child != शून्य; \
	     child = of_get_next_child(parent, child))
#घोषणा क्रम_each_available_child_of_node(parent, child) \
	क्रम (child = of_get_next_available_child(parent, शून्य); child != शून्य; \
	     child = of_get_next_available_child(parent, child))

#घोषणा क्रम_each_of_cpu_node(cpu) \
	क्रम (cpu = of_get_next_cpu_node(शून्य); cpu != शून्य; \
	     cpu = of_get_next_cpu_node(cpu))

#घोषणा क्रम_each_node_with_property(dn, prop_name) \
	क्रम (dn = of_find_node_with_property(शून्य, prop_name); dn; \
	     dn = of_find_node_with_property(dn, prop_name))

अटल अंतरभूत पूर्णांक of_get_child_count(स्थिर काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	पूर्णांक num = 0;

	क्रम_each_child_of_node(np, child)
		num++;

	वापस num;
पूर्ण

अटल अंतरभूत पूर्णांक of_get_available_child_count(स्थिर काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	पूर्णांक num = 0;

	क्रम_each_available_child_of_node(np, child)
		num++;

	वापस num;
पूर्ण

#अगर defined(CONFIG_OF) && !defined(MODULE)
#घोषणा _OF_DECLARE(table, name, compat, fn, fn_type)			\
	अटल स्थिर काष्ठा of_device_id __of_table_##name		\
		__used __section("__" #table "_of_table")		\
		__aligned(__alignof__(काष्ठा of_device_id))		\
		 = अणु .compatible = compat,				\
		     .data = (fn == (fn_type)शून्य) ? fn : fn  पूर्ण
#अन्यथा
#घोषणा _OF_DECLARE(table, name, compat, fn, fn_type)			\
	अटल स्थिर काष्ठा of_device_id __of_table_##name		\
		__attribute__((unused))					\
		 = अणु .compatible = compat,				\
		     .data = (fn == (fn_type)शून्य) ? fn : fn पूर्ण
#पूर्ण_अगर

प्रकार पूर्णांक (*of_init_fn_2)(काष्ठा device_node *, काष्ठा device_node *);
प्रकार पूर्णांक (*of_init_fn_1_ret)(काष्ठा device_node *);
प्रकार व्योम (*of_init_fn_1)(काष्ठा device_node *);

#घोषणा OF_DECLARE_1(table, name, compat, fn) \
		_OF_DECLARE(table, name, compat, fn, of_init_fn_1)
#घोषणा OF_DECLARE_1_RET(table, name, compat, fn) \
		_OF_DECLARE(table, name, compat, fn, of_init_fn_1_ret)
#घोषणा OF_DECLARE_2(table, name, compat, fn) \
		_OF_DECLARE(table, name, compat, fn, of_init_fn_2)

/**
 * काष्ठा of_changeset_entry	- Holds a changeset entry
 *
 * @node:	list_head क्रम the log list
 * @action:	notअगरier action
 * @np:		poपूर्णांकer to the device node affected
 * @prop:	poपूर्णांकer to the property affected
 * @old_prop:	hold a poपूर्णांकer to the original property
 *
 * Every modअगरication of the device tree during a changeset
 * is held in a list of of_changeset_entry काष्ठाures.
 * That way we can recover from a partial application, or we can
 * revert the changeset
 */
काष्ठा of_changeset_entry अणु
	काष्ठा list_head node;
	अचिन्हित दीर्घ action;
	काष्ठा device_node *np;
	काष्ठा property *prop;
	काष्ठा property *old_prop;
पूर्ण;

/**
 * काष्ठा of_changeset - changeset tracker काष्ठाure
 *
 * @entries:	list_head क्रम the changeset entries
 *
 * changesets are a convenient way to apply bulk changes to the
 * live tree. In हाल of an error, changes are rolled-back.
 * changesets live on after initial application, and अगर not
 * destroyed after use, they can be reverted in one single call.
 */
काष्ठा of_changeset अणु
	काष्ठा list_head entries;
पूर्ण;

क्रमागत of_reconfig_change अणु
	OF_RECONFIG_NO_CHANGE = 0,
	OF_RECONFIG_CHANGE_ADD,
	OF_RECONFIG_CHANGE_REMOVE,
पूर्ण;

#अगर_घोषित CONFIG_OF_DYNAMIC
बाह्य पूर्णांक of_reconfig_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *);
बाह्य पूर्णांक of_reconfig_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *);
बाह्य पूर्णांक of_reconfig_notअगरy(अचिन्हित दीर्घ, काष्ठा of_reconfig_data *rd);
बाह्य पूर्णांक of_reconfig_get_state_change(अचिन्हित दीर्घ action,
					काष्ठा of_reconfig_data *arg);

बाह्य व्योम of_changeset_init(काष्ठा of_changeset *ocs);
बाह्य व्योम of_changeset_destroy(काष्ठा of_changeset *ocs);
बाह्य पूर्णांक of_changeset_apply(काष्ठा of_changeset *ocs);
बाह्य पूर्णांक of_changeset_revert(काष्ठा of_changeset *ocs);
बाह्य पूर्णांक of_changeset_action(काष्ठा of_changeset *ocs,
		अचिन्हित दीर्घ action, काष्ठा device_node *np,
		काष्ठा property *prop);

अटल अंतरभूत पूर्णांक of_changeset_attach_node(काष्ठा of_changeset *ocs,
		काष्ठा device_node *np)
अणु
	वापस of_changeset_action(ocs, OF_RECONFIG_ATTACH_NODE, np, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक of_changeset_detach_node(काष्ठा of_changeset *ocs,
		काष्ठा device_node *np)
अणु
	वापस of_changeset_action(ocs, OF_RECONFIG_DETACH_NODE, np, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक of_changeset_add_property(काष्ठा of_changeset *ocs,
		काष्ठा device_node *np, काष्ठा property *prop)
अणु
	वापस of_changeset_action(ocs, OF_RECONFIG_ADD_PROPERTY, np, prop);
पूर्ण

अटल अंतरभूत पूर्णांक of_changeset_हटाओ_property(काष्ठा of_changeset *ocs,
		काष्ठा device_node *np, काष्ठा property *prop)
अणु
	वापस of_changeset_action(ocs, OF_RECONFIG_REMOVE_PROPERTY, np, prop);
पूर्ण

अटल अंतरभूत पूर्णांक of_changeset_update_property(काष्ठा of_changeset *ocs,
		काष्ठा device_node *np, काष्ठा property *prop)
अणु
	वापस of_changeset_action(ocs, OF_RECONFIG_UPDATE_PROPERTY, np, prop);
पूर्ण
#अन्यथा /* CONFIG_OF_DYNAMIC */
अटल अंतरभूत पूर्णांक of_reconfig_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक of_reconfig_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक of_reconfig_notअगरy(अचिन्हित दीर्घ action,
				     काष्ठा of_reconfig_data *arg)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक of_reconfig_get_state_change(अचिन्हित दीर्घ action,
						काष्ठा of_reconfig_data *arg)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_DYNAMIC */

/**
 * of_device_is_प्रणाली_घातer_controller - Tells अगर प्रणाली-घातer-controller is found क्रम device_node
 * @np: Poपूर्णांकer to the given device_node
 *
 * Return: true अगर present false otherwise
 */
अटल अंतरभूत bool of_device_is_प्रणाली_घातer_controller(स्थिर काष्ठा device_node *np)
अणु
	वापस of_property_पढ़ो_bool(np, "system-power-controller");
पूर्ण

/*
 * Overlay support
 */

क्रमागत of_overlay_notअगरy_action अणु
	OF_OVERLAY_PRE_APPLY = 0,
	OF_OVERLAY_POST_APPLY,
	OF_OVERLAY_PRE_REMOVE,
	OF_OVERLAY_POST_REMOVE,
पूर्ण;

काष्ठा of_overlay_notअगरy_data अणु
	काष्ठा device_node *overlay;
	काष्ठा device_node *target;
पूर्ण;

#अगर_घोषित CONFIG_OF_OVERLAY

पूर्णांक of_overlay_fdt_apply(स्थिर व्योम *overlay_fdt, u32 overlay_fdt_size,
			 पूर्णांक *ovcs_id);
पूर्णांक of_overlay_हटाओ(पूर्णांक *ovcs_id);
पूर्णांक of_overlay_हटाओ_all(व्योम);

पूर्णांक of_overlay_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb);
पूर्णांक of_overlay_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb);

#अन्यथा

अटल अंतरभूत पूर्णांक of_overlay_fdt_apply(व्योम *overlay_fdt, u32 overlay_fdt_size,
				       पूर्णांक *ovcs_id)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक of_overlay_हटाओ(पूर्णांक *ovcs_id)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक of_overlay_हटाओ_all(व्योम)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक of_overlay_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक of_overlay_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_OF_H */
