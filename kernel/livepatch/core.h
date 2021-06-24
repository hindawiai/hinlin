<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIVEPATCH_CORE_H
#घोषणा _LIVEPATCH_CORE_H

#समावेश <linux/livepatch.h>

बाह्य काष्ठा mutex klp_mutex;
बाह्य काष्ठा list_head klp_patches;

#घोषणा klp_क्रम_each_patch_safe(patch, पंचांगp_patch)		\
	list_क्रम_each_entry_safe(patch, पंचांगp_patch, &klp_patches, list)

#घोषणा klp_क्रम_each_patch(patch)	\
	list_क्रम_each_entry(patch, &klp_patches, list)

व्योम klp_मुक्त_patch_async(काष्ठा klp_patch *patch);
व्योम klp_मुक्त_replaced_patches_async(काष्ठा klp_patch *new_patch);
व्योम klp_unpatch_replaced_patches(काष्ठा klp_patch *new_patch);
व्योम klp_discard_nops(काष्ठा klp_patch *new_patch);

अटल अंतरभूत bool klp_is_object_loaded(काष्ठा klp_object *obj)
अणु
	वापस !obj->name || obj->mod;
पूर्ण

अटल अंतरभूत पूर्णांक klp_pre_patch_callback(काष्ठा klp_object *obj)
अणु
	पूर्णांक ret = 0;

	अगर (obj->callbacks.pre_patch)
		ret = (*obj->callbacks.pre_patch)(obj);

	obj->callbacks.post_unpatch_enabled = !ret;

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम klp_post_patch_callback(काष्ठा klp_object *obj)
अणु
	अगर (obj->callbacks.post_patch)
		(*obj->callbacks.post_patch)(obj);
पूर्ण

अटल अंतरभूत व्योम klp_pre_unpatch_callback(काष्ठा klp_object *obj)
अणु
	अगर (obj->callbacks.pre_unpatch)
		(*obj->callbacks.pre_unpatch)(obj);
पूर्ण

अटल अंतरभूत व्योम klp_post_unpatch_callback(काष्ठा klp_object *obj)
अणु
	अगर (obj->callbacks.post_unpatch_enabled &&
	    obj->callbacks.post_unpatch)
		(*obj->callbacks.post_unpatch)(obj);

	obj->callbacks.post_unpatch_enabled = false;
पूर्ण

#पूर्ण_अगर /* _LIVEPATCH_CORE_H */
