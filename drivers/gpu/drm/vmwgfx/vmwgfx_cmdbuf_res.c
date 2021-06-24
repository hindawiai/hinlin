<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2014-2015 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_resource_priv.h"

#घोषणा VMW_CMDBUF_RES_MAN_HT_ORDER 12

/**
 * काष्ठा vmw_cmdbuf_res - Command buffer managed resource entry.
 *
 * @res: Refcounted poपूर्णांकer to a काष्ठा vmw_resource.
 * @hash: Hash entry क्रम the manager hash table.
 * @head: List head used either by the staging list or the manager list
 * of commited resources.
 * @state: Staging state of this resource entry.
 * @man: Poपूर्णांकer to a resource manager क्रम this entry.
 */
काष्ठा vmw_cmdbuf_res अणु
	काष्ठा vmw_resource *res;
	काष्ठा drm_hash_item hash;
	काष्ठा list_head head;
	क्रमागत vmw_cmdbuf_res_state state;
	काष्ठा vmw_cmdbuf_res_manager *man;
पूर्ण;

/**
 * काष्ठा vmw_cmdbuf_res_manager - Command buffer resource manager.
 *
 * @resources: Hash table containing staged and commited command buffer
 * resources
 * @list: List of commited command buffer resources.
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure.
 *
 * @resources and @list are रक्षित by the cmdbuf mutex क्रम now.
 */
काष्ठा vmw_cmdbuf_res_manager अणु
	काष्ठा drm_खोलो_hash resources;
	काष्ठा list_head list;
	काष्ठा vmw_निजी *dev_priv;
पूर्ण;


/**
 * vmw_cmdbuf_res_lookup - Look up a command buffer resource
 *
 * @man: Poपूर्णांकer to the command buffer resource manager
 * @res_type: The resource type, that combined with the user key
 * identअगरies the resource.
 * @user_key: The user key.
 *
 * Returns a valid refcounted काष्ठा vmw_resource poपूर्णांकer on success,
 * an error poपूर्णांकer on failure.
 */
काष्ठा vmw_resource *
vmw_cmdbuf_res_lookup(काष्ठा vmw_cmdbuf_res_manager *man,
		      क्रमागत vmw_cmdbuf_res_type res_type,
		      u32 user_key)
अणु
	काष्ठा drm_hash_item *hash;
	पूर्णांक ret;
	अचिन्हित दीर्घ key = user_key | (res_type << 24);

	ret = drm_ht_find_item(&man->resources, key, &hash);
	अगर (unlikely(ret != 0))
		वापस ERR_PTR(ret);

	वापस drm_hash_entry(hash, काष्ठा vmw_cmdbuf_res, hash)->res;
पूर्ण

/**
 * vmw_cmdbuf_res_मुक्त - Free a command buffer resource.
 *
 * @man: Poपूर्णांकer to the command buffer resource manager
 * @entry: Poपूर्णांकer to a काष्ठा vmw_cmdbuf_res.
 *
 * Frees a काष्ठा vmw_cmdbuf_res entry and drops its reference to the
 * काष्ठा vmw_resource.
 */
अटल व्योम vmw_cmdbuf_res_मुक्त(काष्ठा vmw_cmdbuf_res_manager *man,
				काष्ठा vmw_cmdbuf_res *entry)
अणु
	list_del(&entry->head);
	WARN_ON(drm_ht_हटाओ_item(&man->resources, &entry->hash));
	vmw_resource_unreference(&entry->res);
	kमुक्त(entry);
पूर्ण

/**
 * vmw_cmdbuf_res_commit - Commit a list of command buffer resource actions
 *
 * @list: Caller's list of command buffer resource actions.
 *
 * This function commits a list of command buffer resource
 * additions or removals.
 * It is typically called when the execbuf ioctl call triggering these
 * actions has commited the fअगरo contents to the device.
 */
व्योम vmw_cmdbuf_res_commit(काष्ठा list_head *list)
अणु
	काष्ठा vmw_cmdbuf_res *entry, *next;

	list_क्रम_each_entry_safe(entry, next, list, head) अणु
		list_del(&entry->head);
		अगर (entry->res->func->commit_notअगरy)
			entry->res->func->commit_notअगरy(entry->res,
							entry->state);
		चयन (entry->state) अणु
		हाल VMW_CMDBUF_RES_ADD:
			entry->state = VMW_CMDBUF_RES_COMMITTED;
			list_add_tail(&entry->head, &entry->man->list);
			अवरोध;
		हाल VMW_CMDBUF_RES_DEL:
			vmw_resource_unreference(&entry->res);
			kमुक्त(entry);
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * vmw_cmdbuf_res_revert - Revert a list of command buffer resource actions
 *
 * @list: Caller's list of command buffer resource action
 *
 * This function reverts a list of command buffer resource
 * additions or removals.
 * It is typically called when the execbuf ioctl call triggering these
 * actions failed क्रम some reason, and the command stream was never
 * submitted.
 */
व्योम vmw_cmdbuf_res_revert(काष्ठा list_head *list)
अणु
	काष्ठा vmw_cmdbuf_res *entry, *next;

	list_क्रम_each_entry_safe(entry, next, list, head) अणु
		चयन (entry->state) अणु
		हाल VMW_CMDBUF_RES_ADD:
			vmw_cmdbuf_res_मुक्त(entry->man, entry);
			अवरोध;
		हाल VMW_CMDBUF_RES_DEL:
			drm_ht_insert_item(&entry->man->resources, &entry->hash);
			list_del(&entry->head);
			list_add_tail(&entry->head, &entry->man->list);
			entry->state = VMW_CMDBUF_RES_COMMITTED;
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * vmw_cmdbuf_res_add - Stage a command buffer managed resource क्रम addition.
 *
 * @man: Poपूर्णांकer to the command buffer resource manager.
 * @res_type: The resource type.
 * @user_key: The user-space id of the resource.
 * @res: Valid (refcount != 0) poपूर्णांकer to a काष्ठा vmw_resource.
 * @list: The staging list.
 *
 * This function allocates a काष्ठा vmw_cmdbuf_res entry and adds the
 * resource to the hash table of the manager identअगरied by @man. The
 * entry is then put on the staging list identअगरied by @list.
 */
पूर्णांक vmw_cmdbuf_res_add(काष्ठा vmw_cmdbuf_res_manager *man,
		       क्रमागत vmw_cmdbuf_res_type res_type,
		       u32 user_key,
		       काष्ठा vmw_resource *res,
		       काष्ठा list_head *list)
अणु
	काष्ठा vmw_cmdbuf_res *cres;
	पूर्णांक ret;

	cres = kzalloc(माप(*cres), GFP_KERNEL);
	अगर (unlikely(!cres))
		वापस -ENOMEM;

	cres->hash.key = user_key | (res_type << 24);
	ret = drm_ht_insert_item(&man->resources, &cres->hash);
	अगर (unlikely(ret != 0)) अणु
		kमुक्त(cres);
		जाओ out_invalid_key;
	पूर्ण

	cres->state = VMW_CMDBUF_RES_ADD;
	cres->res = vmw_resource_reference(res);
	cres->man = man;
	list_add_tail(&cres->head, list);

out_invalid_key:
	वापस ret;
पूर्ण

/**
 * vmw_cmdbuf_res_हटाओ - Stage a command buffer managed resource क्रम removal.
 *
 * @man: Poपूर्णांकer to the command buffer resource manager.
 * @res_type: The resource type.
 * @user_key: The user-space id of the resource.
 * @list: The staging list.
 * @res_p: If the resource is in an alपढ़ोy committed state, poपूर्णांकs to the
 * काष्ठा vmw_resource on successful वापस. The poपूर्णांकer will be
 * non ref-counted.
 *
 * This function looks up the काष्ठा vmw_cmdbuf_res entry from the manager
 * hash table and, अगर it exists, हटाओs it. Depending on its current staging
 * state it then either हटाओs the entry from the staging list or adds it
 * to it with a staging state of removal.
 */
पूर्णांक vmw_cmdbuf_res_हटाओ(काष्ठा vmw_cmdbuf_res_manager *man,
			  क्रमागत vmw_cmdbuf_res_type res_type,
			  u32 user_key,
			  काष्ठा list_head *list,
			  काष्ठा vmw_resource **res_p)
अणु
	काष्ठा vmw_cmdbuf_res *entry;
	काष्ठा drm_hash_item *hash;
	पूर्णांक ret;

	ret = drm_ht_find_item(&man->resources, user_key | (res_type << 24),
			       &hash);
	अगर (likely(ret != 0))
		वापस -EINVAL;

	entry = drm_hash_entry(hash, काष्ठा vmw_cmdbuf_res, hash);

	चयन (entry->state) अणु
	हाल VMW_CMDBUF_RES_ADD:
		vmw_cmdbuf_res_मुक्त(man, entry);
		*res_p = शून्य;
		अवरोध;
	हाल VMW_CMDBUF_RES_COMMITTED:
		(व्योम) drm_ht_हटाओ_item(&man->resources, &entry->hash);
		list_del(&entry->head);
		entry->state = VMW_CMDBUF_RES_DEL;
		list_add_tail(&entry->head, list);
		*res_p = entry->res;
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_cmdbuf_res_man_create - Allocate a command buffer managed resource
 * manager.
 *
 * @dev_priv: Poपूर्णांकer to a काष्ठा vmw_निजी
 *
 * Allocates and initializes a command buffer managed resource manager. Returns
 * an error poपूर्णांकer on failure.
 */
काष्ठा vmw_cmdbuf_res_manager *
vmw_cmdbuf_res_man_create(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_cmdbuf_res_manager *man;
	पूर्णांक ret;

	man = kzalloc(माप(*man), GFP_KERNEL);
	अगर (!man)
		वापस ERR_PTR(-ENOMEM);

	man->dev_priv = dev_priv;
	INIT_LIST_HEAD(&man->list);
	ret = drm_ht_create(&man->resources, VMW_CMDBUF_RES_MAN_HT_ORDER);
	अगर (ret == 0)
		वापस man;

	kमुक्त(man);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * vmw_cmdbuf_res_man_destroy - Destroy a command buffer managed resource
 * manager.
 *
 * @man: Poपूर्णांकer to the  manager to destroy.
 *
 * This function destroys a command buffer managed resource manager and
 * unreferences / मुक्तs all command buffer managed resources and -entries
 * associated with it.
 */
व्योम vmw_cmdbuf_res_man_destroy(काष्ठा vmw_cmdbuf_res_manager *man)
अणु
	काष्ठा vmw_cmdbuf_res *entry, *next;

	list_क्रम_each_entry_safe(entry, next, &man->list, head)
		vmw_cmdbuf_res_मुक्त(man, entry);

	drm_ht_हटाओ(&man->resources);
	kमुक्त(man);
पूर्ण

/**
 * vmw_cmdbuf_res_man_size - Return the size of a command buffer managed
 * resource manager
 *
 * Returns the approximate allocation size of a command buffer managed
 * resource manager.
 */
माप_प्रकार vmw_cmdbuf_res_man_size(व्योम)
अणु
	अटल माप_प्रकार res_man_size;

	अगर (unlikely(res_man_size == 0))
		res_man_size =
			tपंचांग_round_pot(माप(काष्ठा vmw_cmdbuf_res_manager)) +
			tपंचांग_round_pot(माप(काष्ठा hlist_head) <<
				      VMW_CMDBUF_RES_MAN_HT_ORDER);

	वापस res_man_size;
पूर्ण
