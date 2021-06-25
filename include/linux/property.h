<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * property.h - Unअगरied device property पूर्णांकerface.
 *
 * Copyright (C) 2014, Intel Corporation
 * Authors: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#अगर_अघोषित _LINUX_PROPERTY_H_
#घोषणा _LINUX_PROPERTY_H_

#समावेश <linux/bits.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/types.h>

काष्ठा device;

क्रमागत dev_prop_type अणु
	DEV_PROP_U8,
	DEV_PROP_U16,
	DEV_PROP_U32,
	DEV_PROP_U64,
	DEV_PROP_STRING,
	DEV_PROP_REF,
पूर्ण;

क्रमागत dev_dma_attr अणु
	DEV_DMA_NOT_SUPPORTED,
	DEV_DMA_NON_COHERENT,
	DEV_DMA_COHERENT,
पूर्ण;

काष्ठा fwnode_handle *dev_fwnode(काष्ठा device *dev);

bool device_property_present(काष्ठा device *dev, स्थिर अक्षर *propname);
पूर्णांक device_property_पढ़ो_u8_array(काष्ठा device *dev, स्थिर अक्षर *propname,
				  u8 *val, माप_प्रकार nval);
पूर्णांक device_property_पढ़ो_u16_array(काष्ठा device *dev, स्थिर अक्षर *propname,
				   u16 *val, माप_प्रकार nval);
पूर्णांक device_property_पढ़ो_u32_array(काष्ठा device *dev, स्थिर अक्षर *propname,
				   u32 *val, माप_प्रकार nval);
पूर्णांक device_property_पढ़ो_u64_array(काष्ठा device *dev, स्थिर अक्षर *propname,
				   u64 *val, माप_प्रकार nval);
पूर्णांक device_property_पढ़ो_string_array(काष्ठा device *dev, स्थिर अक्षर *propname,
				      स्थिर अक्षर **val, माप_प्रकार nval);
पूर्णांक device_property_पढ़ो_string(काष्ठा device *dev, स्थिर अक्षर *propname,
				स्थिर अक्षर **val);
पूर्णांक device_property_match_string(काष्ठा device *dev,
				 स्थिर अक्षर *propname, स्थिर अक्षर *string);

bool fwnode_device_is_available(स्थिर काष्ठा fwnode_handle *fwnode);
bool fwnode_property_present(स्थिर काष्ठा fwnode_handle *fwnode,
			     स्थिर अक्षर *propname);
पूर्णांक fwnode_property_पढ़ो_u8_array(स्थिर काष्ठा fwnode_handle *fwnode,
				  स्थिर अक्षर *propname, u8 *val,
				  माप_प्रकार nval);
पूर्णांक fwnode_property_पढ़ो_u16_array(स्थिर काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *propname, u16 *val,
				   माप_प्रकार nval);
पूर्णांक fwnode_property_पढ़ो_u32_array(स्थिर काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *propname, u32 *val,
				   माप_प्रकार nval);
पूर्णांक fwnode_property_पढ़ो_u64_array(स्थिर काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *propname, u64 *val,
				   माप_प्रकार nval);
पूर्णांक fwnode_property_पढ़ो_string_array(स्थिर काष्ठा fwnode_handle *fwnode,
				      स्थिर अक्षर *propname, स्थिर अक्षर **val,
				      माप_प्रकार nval);
पूर्णांक fwnode_property_पढ़ो_string(स्थिर काष्ठा fwnode_handle *fwnode,
				स्थिर अक्षर *propname, स्थिर अक्षर **val);
पूर्णांक fwnode_property_match_string(स्थिर काष्ठा fwnode_handle *fwnode,
				 स्थिर अक्षर *propname, स्थिर अक्षर *string);
पूर्णांक fwnode_property_get_reference_args(स्थिर काष्ठा fwnode_handle *fwnode,
				       स्थिर अक्षर *prop, स्थिर अक्षर *nargs_prop,
				       अचिन्हित पूर्णांक nargs, अचिन्हित पूर्णांक index,
				       काष्ठा fwnode_reference_args *args);

काष्ठा fwnode_handle *fwnode_find_reference(स्थिर काष्ठा fwnode_handle *fwnode,
					    स्थिर अक्षर *name,
					    अचिन्हित पूर्णांक index);

स्थिर अक्षर *fwnode_get_name(स्थिर काष्ठा fwnode_handle *fwnode);
स्थिर अक्षर *fwnode_get_name_prefix(स्थिर काष्ठा fwnode_handle *fwnode);
काष्ठा fwnode_handle *fwnode_get_parent(स्थिर काष्ठा fwnode_handle *fwnode);
काष्ठा fwnode_handle *fwnode_get_next_parent(
	काष्ठा fwnode_handle *fwnode);
काष्ठा device *fwnode_get_next_parent_dev(काष्ठा fwnode_handle *fwnode);
अचिन्हित पूर्णांक fwnode_count_parents(स्थिर काष्ठा fwnode_handle *fwn);
काष्ठा fwnode_handle *fwnode_get_nth_parent(काष्ठा fwnode_handle *fwn,
					    अचिन्हित पूर्णांक depth);
bool fwnode_is_ancestor_of(काष्ठा fwnode_handle *test_ancestor,
				  काष्ठा fwnode_handle *test_child);
काष्ठा fwnode_handle *fwnode_get_next_child_node(
	स्थिर काष्ठा fwnode_handle *fwnode, काष्ठा fwnode_handle *child);
काष्ठा fwnode_handle *fwnode_get_next_available_child_node(
	स्थिर काष्ठा fwnode_handle *fwnode, काष्ठा fwnode_handle *child);

#घोषणा fwnode_क्रम_each_child_node(fwnode, child)			\
	क्रम (child = fwnode_get_next_child_node(fwnode, शून्य); child;	\
	     child = fwnode_get_next_child_node(fwnode, child))

#घोषणा fwnode_क्रम_each_available_child_node(fwnode, child)		       \
	क्रम (child = fwnode_get_next_available_child_node(fwnode, शून्य); child;\
	     child = fwnode_get_next_available_child_node(fwnode, child))

काष्ठा fwnode_handle *device_get_next_child_node(
	काष्ठा device *dev, काष्ठा fwnode_handle *child);

#घोषणा device_क्रम_each_child_node(dev, child)				\
	क्रम (child = device_get_next_child_node(dev, शून्य); child;	\
	     child = device_get_next_child_node(dev, child))

काष्ठा fwnode_handle *fwnode_get_named_child_node(
	स्थिर काष्ठा fwnode_handle *fwnode, स्थिर अक्षर *childname);
काष्ठा fwnode_handle *device_get_named_child_node(काष्ठा device *dev,
						  स्थिर अक्षर *childname);

काष्ठा fwnode_handle *fwnode_handle_get(काष्ठा fwnode_handle *fwnode);
व्योम fwnode_handle_put(काष्ठा fwnode_handle *fwnode);

पूर्णांक fwnode_irq_get(काष्ठा fwnode_handle *fwnode, अचिन्हित पूर्णांक index);

अचिन्हित पूर्णांक device_get_child_node_count(काष्ठा device *dev);

अटल अंतरभूत bool device_property_पढ़ो_bool(काष्ठा device *dev,
					     स्थिर अक्षर *propname)
अणु
	वापस device_property_present(dev, propname);
पूर्ण

अटल अंतरभूत पूर्णांक device_property_पढ़ो_u8(काष्ठा device *dev,
					  स्थिर अक्षर *propname, u8 *val)
अणु
	वापस device_property_पढ़ो_u8_array(dev, propname, val, 1);
पूर्ण

अटल अंतरभूत पूर्णांक device_property_पढ़ो_u16(काष्ठा device *dev,
					   स्थिर अक्षर *propname, u16 *val)
अणु
	वापस device_property_पढ़ो_u16_array(dev, propname, val, 1);
पूर्ण

अटल अंतरभूत पूर्णांक device_property_पढ़ो_u32(काष्ठा device *dev,
					   स्थिर अक्षर *propname, u32 *val)
अणु
	वापस device_property_पढ़ो_u32_array(dev, propname, val, 1);
पूर्ण

अटल अंतरभूत पूर्णांक device_property_पढ़ो_u64(काष्ठा device *dev,
					   स्थिर अक्षर *propname, u64 *val)
अणु
	वापस device_property_पढ़ो_u64_array(dev, propname, val, 1);
पूर्ण

अटल अंतरभूत पूर्णांक device_property_count_u8(काष्ठा device *dev, स्थिर अक्षर *propname)
अणु
	वापस device_property_पढ़ो_u8_array(dev, propname, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक device_property_count_u16(काष्ठा device *dev, स्थिर अक्षर *propname)
अणु
	वापस device_property_पढ़ो_u16_array(dev, propname, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक device_property_count_u32(काष्ठा device *dev, स्थिर अक्षर *propname)
अणु
	वापस device_property_पढ़ो_u32_array(dev, propname, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक device_property_count_u64(काष्ठा device *dev, स्थिर अक्षर *propname)
अणु
	वापस device_property_पढ़ो_u64_array(dev, propname, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक device_property_string_array_count(काष्ठा device *dev,
						     स्थिर अक्षर *propname)
अणु
	वापस device_property_पढ़ो_string_array(dev, propname, शून्य, 0);
पूर्ण

अटल अंतरभूत bool fwnode_property_पढ़ो_bool(स्थिर काष्ठा fwnode_handle *fwnode,
					     स्थिर अक्षर *propname)
अणु
	वापस fwnode_property_present(fwnode, propname);
पूर्ण

अटल अंतरभूत पूर्णांक fwnode_property_पढ़ो_u8(स्थिर काष्ठा fwnode_handle *fwnode,
					  स्थिर अक्षर *propname, u8 *val)
अणु
	वापस fwnode_property_पढ़ो_u8_array(fwnode, propname, val, 1);
पूर्ण

अटल अंतरभूत पूर्णांक fwnode_property_पढ़ो_u16(स्थिर काष्ठा fwnode_handle *fwnode,
					   स्थिर अक्षर *propname, u16 *val)
अणु
	वापस fwnode_property_पढ़ो_u16_array(fwnode, propname, val, 1);
पूर्ण

अटल अंतरभूत पूर्णांक fwnode_property_पढ़ो_u32(स्थिर काष्ठा fwnode_handle *fwnode,
					   स्थिर अक्षर *propname, u32 *val)
अणु
	वापस fwnode_property_पढ़ो_u32_array(fwnode, propname, val, 1);
पूर्ण

अटल अंतरभूत पूर्णांक fwnode_property_पढ़ो_u64(स्थिर काष्ठा fwnode_handle *fwnode,
					   स्थिर अक्षर *propname, u64 *val)
अणु
	वापस fwnode_property_पढ़ो_u64_array(fwnode, propname, val, 1);
पूर्ण

अटल अंतरभूत पूर्णांक fwnode_property_count_u8(स्थिर काष्ठा fwnode_handle *fwnode,
					   स्थिर अक्षर *propname)
अणु
	वापस fwnode_property_पढ़ो_u8_array(fwnode, propname, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक fwnode_property_count_u16(स्थिर काष्ठा fwnode_handle *fwnode,
					    स्थिर अक्षर *propname)
अणु
	वापस fwnode_property_पढ़ो_u16_array(fwnode, propname, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक fwnode_property_count_u32(स्थिर काष्ठा fwnode_handle *fwnode,
					    स्थिर अक्षर *propname)
अणु
	वापस fwnode_property_पढ़ो_u32_array(fwnode, propname, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक fwnode_property_count_u64(स्थिर काष्ठा fwnode_handle *fwnode,
					    स्थिर अक्षर *propname)
अणु
	वापस fwnode_property_पढ़ो_u64_array(fwnode, propname, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक
fwnode_property_string_array_count(स्थिर काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *propname)
अणु
	वापस fwnode_property_पढ़ो_string_array(fwnode, propname, शून्य, 0);
पूर्ण

काष्ठा software_node;

/**
 * काष्ठा software_node_ref_args - Reference property with additional arguments
 * @node: Reference to a software node
 * @nargs: Number of elements in @args array
 * @args: Integer arguments
 */
काष्ठा software_node_ref_args अणु
	स्थिर काष्ठा software_node *node;
	अचिन्हित पूर्णांक nargs;
	u64 args[NR_FWNODE_REFERENCE_ARGS];
पूर्ण;

#घोषणा SOFTWARE_NODE_REFERENCE(_ref_, ...)			\
(स्थिर काष्ठा software_node_ref_args) अणु				\
	.node = _ref_,						\
	.nargs = ARRAY_SIZE(((u64[])अणु 0, ##__VA_ARGS__ पूर्ण)) - 1,	\
	.args = अणु __VA_ARGS__ पूर्ण,				\
पूर्ण

/**
 * काष्ठा property_entry - "Built-in" device property representation.
 * @name: Name of the property.
 * @length: Length of data making up the value.
 * @is_अंतरभूत: True when the property value is stored अंतरभूत.
 * @type: Type of the data in जोड़s.
 * @poपूर्णांकer: Poपूर्णांकer to the property when it is not stored अंतरभूत.
 * @value: Value of the property when it is stored अंतरभूत.
 */
काष्ठा property_entry अणु
	स्थिर अक्षर *name;
	माप_प्रकार length;
	bool is_अंतरभूत;
	क्रमागत dev_prop_type type;
	जोड़ अणु
		स्थिर व्योम *poपूर्णांकer;
		जोड़ अणु
			u8 u8_data[माप(u64) / माप(u8)];
			u16 u16_data[माप(u64) / माप(u16)];
			u32 u32_data[माप(u64) / माप(u32)];
			u64 u64_data[माप(u64) / माप(u64)];
			स्थिर अक्षर *str[माप(u64) / माप(अक्षर *)];
		पूर्ण value;
	पूर्ण;
पूर्ण;

/*
 * Note: the below initializers क्रम the anonymous जोड़ are carefully
 * crafted to aव्योम gcc-4.4.4's problems with initialization of anon जोड़s
 * and काष्ठाs.
 */

#घोषणा __PROPERTY_ENTRY_ELEMENT_SIZE(_elem_)				\
	माप(((काष्ठा property_entry *)शून्य)->value._elem_[0])

#घोषणा __PROPERTY_ENTRY_ARRAY_ELSIZE_LEN(_name_, _elsize_, _Type_,	\
					  _val_, _len_)			\
(काष्ठा property_entry) अणु						\
	.name = _name_,							\
	.length = (_len_) * (_elsize_),					\
	.type = DEV_PROP_##_Type_,					\
	अणु .poपूर्णांकer = _val_ पूर्ण,						\
पूर्ण

#घोषणा __PROPERTY_ENTRY_ARRAY_LEN(_name_, _elem_, _Type_, _val_, _len_)\
	__PROPERTY_ENTRY_ARRAY_ELSIZE_LEN(_name_,			\
				__PROPERTY_ENTRY_ELEMENT_SIZE(_elem_),	\
				_Type_, _val_, _len_)

#घोषणा PROPERTY_ENTRY_U8_ARRAY_LEN(_name_, _val_, _len_)		\
	__PROPERTY_ENTRY_ARRAY_LEN(_name_, u8_data, U8, _val_, _len_)
#घोषणा PROPERTY_ENTRY_U16_ARRAY_LEN(_name_, _val_, _len_)		\
	__PROPERTY_ENTRY_ARRAY_LEN(_name_, u16_data, U16, _val_, _len_)
#घोषणा PROPERTY_ENTRY_U32_ARRAY_LEN(_name_, _val_, _len_)		\
	__PROPERTY_ENTRY_ARRAY_LEN(_name_, u32_data, U32, _val_, _len_)
#घोषणा PROPERTY_ENTRY_U64_ARRAY_LEN(_name_, _val_, _len_)		\
	__PROPERTY_ENTRY_ARRAY_LEN(_name_, u64_data, U64, _val_, _len_)
#घोषणा PROPERTY_ENTRY_STRING_ARRAY_LEN(_name_, _val_, _len_)		\
	__PROPERTY_ENTRY_ARRAY_LEN(_name_, str, STRING, _val_, _len_)
#घोषणा PROPERTY_ENTRY_REF_ARRAY_LEN(_name_, _val_, _len_)		\
	__PROPERTY_ENTRY_ARRAY_ELSIZE_LEN(_name_,			\
				माप(काष्ठा software_node_ref_args),	\
				REF, _val_, _len_)

#घोषणा PROPERTY_ENTRY_U8_ARRAY(_name_, _val_)				\
	PROPERTY_ENTRY_U8_ARRAY_LEN(_name_, _val_, ARRAY_SIZE(_val_))
#घोषणा PROPERTY_ENTRY_U16_ARRAY(_name_, _val_)				\
	PROPERTY_ENTRY_U16_ARRAY_LEN(_name_, _val_, ARRAY_SIZE(_val_))
#घोषणा PROPERTY_ENTRY_U32_ARRAY(_name_, _val_)				\
	PROPERTY_ENTRY_U32_ARRAY_LEN(_name_, _val_, ARRAY_SIZE(_val_))
#घोषणा PROPERTY_ENTRY_U64_ARRAY(_name_, _val_)				\
	PROPERTY_ENTRY_U64_ARRAY_LEN(_name_, _val_, ARRAY_SIZE(_val_))
#घोषणा PROPERTY_ENTRY_STRING_ARRAY(_name_, _val_)			\
	PROPERTY_ENTRY_STRING_ARRAY_LEN(_name_, _val_, ARRAY_SIZE(_val_))
#घोषणा PROPERTY_ENTRY_REF_ARRAY(_name_, _val_)			\
	PROPERTY_ENTRY_REF_ARRAY_LEN(_name_, _val_, ARRAY_SIZE(_val_))

#घोषणा __PROPERTY_ENTRY_ELEMENT(_name_, _elem_, _Type_, _val_)		\
(काष्ठा property_entry) अणु						\
	.name = _name_,							\
	.length = __PROPERTY_ENTRY_ELEMENT_SIZE(_elem_),		\
	.is_अंतरभूत = true,						\
	.type = DEV_PROP_##_Type_,					\
	अणु .value = अणु ._elem_[0] = _val_ पूर्ण पूर्ण,				\
पूर्ण

#घोषणा PROPERTY_ENTRY_U8(_name_, _val_)				\
	__PROPERTY_ENTRY_ELEMENT(_name_, u8_data, U8, _val_)
#घोषणा PROPERTY_ENTRY_U16(_name_, _val_)				\
	__PROPERTY_ENTRY_ELEMENT(_name_, u16_data, U16, _val_)
#घोषणा PROPERTY_ENTRY_U32(_name_, _val_)				\
	__PROPERTY_ENTRY_ELEMENT(_name_, u32_data, U32, _val_)
#घोषणा PROPERTY_ENTRY_U64(_name_, _val_)				\
	__PROPERTY_ENTRY_ELEMENT(_name_, u64_data, U64, _val_)
#घोषणा PROPERTY_ENTRY_STRING(_name_, _val_)				\
	__PROPERTY_ENTRY_ELEMENT(_name_, str, STRING, _val_)

#घोषणा PROPERTY_ENTRY_BOOL(_name_)		\
(काष्ठा property_entry) अणु			\
	.name = _name_,				\
	.is_अंतरभूत = true,			\
पूर्ण

#घोषणा PROPERTY_ENTRY_REF(_name_, _ref_, ...)				\
(काष्ठा property_entry) अणु						\
	.name = _name_,							\
	.length = माप(काष्ठा software_node_ref_args),		\
	.type = DEV_PROP_REF,						\
	अणु .poपूर्णांकer = &SOFTWARE_NODE_REFERENCE(_ref_, ##__VA_ARGS__), पूर्ण,	\
पूर्ण

काष्ठा property_entry *
property_entries_dup(स्थिर काष्ठा property_entry *properties);

व्योम property_entries_मुक्त(स्थिर काष्ठा property_entry *properties);

पूर्णांक device_add_properties(काष्ठा device *dev,
			  स्थिर काष्ठा property_entry *properties);
व्योम device_हटाओ_properties(काष्ठा device *dev);

bool device_dma_supported(काष्ठा device *dev);

क्रमागत dev_dma_attr device_get_dma_attr(काष्ठा device *dev);

स्थिर व्योम *device_get_match_data(काष्ठा device *dev);

पूर्णांक device_get_phy_mode(काष्ठा device *dev);

व्योम *device_get_mac_address(काष्ठा device *dev, अक्षर *addr, पूर्णांक alen);

पूर्णांक fwnode_get_phy_mode(काष्ठा fwnode_handle *fwnode);
व्योम *fwnode_get_mac_address(काष्ठा fwnode_handle *fwnode,
			     अक्षर *addr, पूर्णांक alen);
काष्ठा fwnode_handle *fwnode_graph_get_next_endpoपूर्णांक(
	स्थिर काष्ठा fwnode_handle *fwnode, काष्ठा fwnode_handle *prev);
काष्ठा fwnode_handle *
fwnode_graph_get_port_parent(स्थिर काष्ठा fwnode_handle *fwnode);
काष्ठा fwnode_handle *fwnode_graph_get_remote_port_parent(
	स्थिर काष्ठा fwnode_handle *fwnode);
काष्ठा fwnode_handle *fwnode_graph_get_remote_port(
	स्थिर काष्ठा fwnode_handle *fwnode);
काष्ठा fwnode_handle *fwnode_graph_get_remote_endpoपूर्णांक(
	स्थिर काष्ठा fwnode_handle *fwnode);
काष्ठा fwnode_handle *
fwnode_graph_get_remote_node(स्थिर काष्ठा fwnode_handle *fwnode, u32 port,
			     u32 endpoपूर्णांक);

अटल अंतरभूत bool fwnode_graph_is_endpoपूर्णांक(काष्ठा fwnode_handle *fwnode)
अणु
	वापस fwnode_property_present(fwnode, "remote-endpoint");
पूर्ण

/*
 * Fwnode lookup flags
 *
 * @FWNODE_GRAPH_ENDPOINT_NEXT: In the हाल of no exact match, look क्रम the
 *				बंदst endpoपूर्णांक ID greater than the specअगरied
 *				one.
 * @FWNODE_GRAPH_DEVICE_DISABLED: That the device to which the remote
 *				  endpoपूर्णांक of the given endpoपूर्णांक beदीर्घs to,
 *				  may be disabled.
 */
#घोषणा FWNODE_GRAPH_ENDPOINT_NEXT	BIT(0)
#घोषणा FWNODE_GRAPH_DEVICE_DISABLED	BIT(1)

काष्ठा fwnode_handle *
fwnode_graph_get_endpoपूर्णांक_by_id(स्थिर काष्ठा fwnode_handle *fwnode,
				u32 port, u32 endpoपूर्णांक, अचिन्हित दीर्घ flags);

#घोषणा fwnode_graph_क्रम_each_endpoपूर्णांक(fwnode, child)			\
	क्रम (child = शून्य;						\
	     (child = fwnode_graph_get_next_endpoपूर्णांक(fwnode, child)); )

पूर्णांक fwnode_graph_parse_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode,
				काष्ठा fwnode_endpoपूर्णांक *endpoपूर्णांक);

प्रकार व्योम *(*devcon_match_fn_t)(काष्ठा fwnode_handle *fwnode, स्थिर अक्षर *id,
				   व्योम *data);

व्योम *fwnode_connection_find_match(काष्ठा fwnode_handle *fwnode,
				   स्थिर अक्षर *con_id, व्योम *data,
				   devcon_match_fn_t match);

अटल अंतरभूत व्योम *device_connection_find_match(काष्ठा device *dev,
						 स्थिर अक्षर *con_id, व्योम *data,
						 devcon_match_fn_t match)
अणु
	वापस fwnode_connection_find_match(dev_fwnode(dev), con_id, data, match);
पूर्ण

/* -------------------------------------------------------------------------- */
/* Software fwnode support - when HW description is incomplete or missing */

/**
 * काष्ठा software_node - Software node description
 * @name: Name of the software node
 * @parent: Parent of the software node
 * @properties: Array of device properties
 */
काष्ठा software_node अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा software_node *parent;
	स्थिर काष्ठा property_entry *properties;
पूर्ण;

bool is_software_node(स्थिर काष्ठा fwnode_handle *fwnode);
स्थिर काष्ठा software_node *
to_software_node(स्थिर काष्ठा fwnode_handle *fwnode);
काष्ठा fwnode_handle *software_node_fwnode(स्थिर काष्ठा software_node *node);

स्थिर काष्ठा software_node *
software_node_find_by_name(स्थिर काष्ठा software_node *parent,
			   स्थिर अक्षर *name);

पूर्णांक software_node_रेजिस्टर_nodes(स्थिर काष्ठा software_node *nodes);
व्योम software_node_unरेजिस्टर_nodes(स्थिर काष्ठा software_node *nodes);

पूर्णांक software_node_रेजिस्टर_node_group(स्थिर काष्ठा software_node **node_group);
व्योम software_node_unरेजिस्टर_node_group(स्थिर काष्ठा software_node **node_group);

पूर्णांक software_node_रेजिस्टर(स्थिर काष्ठा software_node *node);
व्योम software_node_unरेजिस्टर(स्थिर काष्ठा software_node *node);

पूर्णांक software_node_notअगरy(काष्ठा device *dev, अचिन्हित दीर्घ action);

काष्ठा fwnode_handle *
fwnode_create_software_node(स्थिर काष्ठा property_entry *properties,
			    स्थिर काष्ठा fwnode_handle *parent);
व्योम fwnode_हटाओ_software_node(काष्ठा fwnode_handle *fwnode);

पूर्णांक device_add_software_node(काष्ठा device *dev, स्थिर काष्ठा software_node *node);
व्योम device_हटाओ_software_node(काष्ठा device *dev);

पूर्णांक device_create_managed_software_node(काष्ठा device *dev,
					स्थिर काष्ठा property_entry *properties,
					स्थिर काष्ठा software_node *parent);

#पूर्ण_अगर /* _LINUX_PROPERTY_H_ */
