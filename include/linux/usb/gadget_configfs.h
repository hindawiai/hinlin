<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __GADGET_CONFIGFS__
#घोषणा __GADGET_CONFIGFS__

#समावेश <linux/configfs.h>

पूर्णांक check_user_usb_string(स्थिर अक्षर *name,
		काष्ठा usb_gadget_strings *stringtab_dev);

#घोषणा GS_STRINGS_W(__काष्ठा, __name)	\
अटल sमाप_प्रकार __काष्ठा##_##__name##_store(काष्ठा config_item *item, \
		स्थिर अक्षर *page, माप_प्रकार len)		\
अणु							\
	काष्ठा __काष्ठा *gs = to_##__काष्ठा(item);	\
	पूर्णांक ret;					\
							\
	ret = usb_string_copy(page, &gs->__name);	\
	अगर (ret)					\
		वापस ret;				\
	वापस len;					\
पूर्ण

#घोषणा GS_STRINGS_R(__काष्ठा, __name)	\
अटल sमाप_प्रकार __काष्ठा##_##__name##_show(काष्ठा config_item *item, अक्षर *page) \
अणु	\
	काष्ठा __काष्ठा *gs = to_##__काष्ठा(item);	\
	वापस प्र_लिखो(page, "%s\n", gs->__name ?: "");	\
पूर्ण

#घोषणा GS_STRINGS_RW(काष्ठा_name, _name)	\
	GS_STRINGS_R(काष्ठा_name, _name)	\
	GS_STRINGS_W(काष्ठा_name, _name)	\
	CONFIGFS_ATTR(काष्ठा_name##_, _name)

#घोषणा USB_CONFIG_STRING_RW_OPS(काष्ठा_in)				\
अटल काष्ठा configfs_item_operations काष्ठा_in##_langid_item_ops = अणु	\
	.release                = काष्ठा_in##_attr_release,		\
पूर्ण;									\
									\
अटल काष्ठा config_item_type काष्ठा_in##_langid_type = अणु		\
	.ct_item_ops	= &काष्ठा_in##_langid_item_ops,			\
	.ct_attrs	= काष्ठा_in##_langid_attrs,			\
	.ct_owner	= THIS_MODULE,					\
पूर्ण

#घोषणा USB_CONFIG_STRINGS_LANG(काष्ठा_in, काष्ठा_member)	\
	अटल काष्ठा config_group *काष्ठा_in##_strings_make(		\
			काष्ठा config_group *group,			\
			स्थिर अक्षर *name)				\
	अणु								\
	काष्ठा काष्ठा_member *gi;					\
	काष्ठा काष्ठा_in *gs;						\
	काष्ठा काष्ठा_in *new;						\
	पूर्णांक langs = 0;							\
	पूर्णांक ret;							\
									\
	new = kzalloc(माप(*new), GFP_KERNEL);			\
	अगर (!new)							\
		वापस ERR_PTR(-ENOMEM);				\
									\
	ret = check_user_usb_string(name, &new->stringtab_dev);		\
	अगर (ret)							\
		जाओ err;						\
	config_group_init_type_name(&new->group, name,			\
			&काष्ठा_in##_langid_type);			\
									\
	gi = container_of(group, काष्ठा काष्ठा_member, strings_group);	\
	ret = -EEXIST;							\
	list_क्रम_each_entry(gs, &gi->string_list, list) अणु		\
		अगर (gs->stringtab_dev.language == new->stringtab_dev.language) \
			जाओ err;					\
		langs++;						\
	पूर्ण								\
	ret = -EOVERFLOW;						\
	अगर (langs >= MAX_USB_STRING_LANGS)				\
		जाओ err;						\
									\
	list_add_tail(&new->list, &gi->string_list);			\
	वापस &new->group;						\
err:									\
	kमुक्त(new);							\
	वापस ERR_PTR(ret);						\
पूर्ण									\
									\
अटल व्योम काष्ठा_in##_strings_drop(					\
		काष्ठा config_group *group,				\
		काष्ठा config_item *item)				\
अणु									\
	config_item_put(item);						\
पूर्ण									\
									\
अटल काष्ठा configfs_group_operations काष्ठा_in##_strings_ops = अणु	\
	.make_group     = &काष्ठा_in##_strings_make,			\
	.drop_item      = &काष्ठा_in##_strings_drop,			\
पूर्ण;									\
									\
अटल काष्ठा config_item_type काष्ठा_in##_strings_type = अणु		\
	.ct_group_ops   = &काष्ठा_in##_strings_ops,			\
	.ct_owner       = THIS_MODULE,					\
पूर्ण

#पूर्ण_अगर
