<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright तऊ 2018 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
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
#अगर_अघोषित _VMWGFX_VALIDATION_H_
#घोषणा _VMWGFX_VALIDATION_H_

#समावेश <linux/list.h>
#समावेश <linux/ww_mutex.h>

#समावेश <drm/drm_hashtab.h>
#समावेश <drm/tपंचांग/tपंचांग_execbuf_util.h>

#घोषणा VMW_RES_सूचीTY_NONE 0
#घोषणा VMW_RES_सूचीTY_SET BIT(0)
#घोषणा VMW_RES_सूचीTY_CLEAR BIT(1)

/**
 * काष्ठा vmw_validation_mem - Custom पूर्णांकerface to provide memory reservations
 * क्रम the validation code.
 * @reserve_mem: Callback to reserve memory
 * @unreserve_mem: Callback to unreserve memory
 * @gran: Reservation granularity. Contains a hपूर्णांक how much memory should
 * be reserved in each call to @reserve_mem(). A slow implementation may want
 * reservation to be करोne in large batches.
 */
काष्ठा vmw_validation_mem अणु
	पूर्णांक (*reserve_mem)(काष्ठा vmw_validation_mem *m, माप_प्रकार size);
	व्योम (*unreserve_mem)(काष्ठा vmw_validation_mem *m, माप_प्रकार size);
	माप_प्रकार gran;
पूर्ण;

/**
 * काष्ठा vmw_validation_context - Per command submission validation context
 * @ht: Hash table used to find resource- or buffer object duplicates
 * @resource_list: List head क्रम resource validation metadata
 * @resource_ctx_list: List head क्रम resource validation metadata क्रम
 * resources that need to be validated beक्रमe those in @resource_list
 * @bo_list: List head क्रम buffer objects
 * @page_list: List of pages used by the memory allocator
 * @ticket: Ticked used क्रम ww mutex locking
 * @res_mutex: Poपूर्णांकer to mutex used क्रम resource reserving
 * @merge_dups: Whether to merge metadata क्रम duplicate resources or
 * buffer objects
 * @mem_size_left: Free memory left in the last page in @page_list
 * @page_address: Kernel भव address of the last page in @page_list
 * @vm: A poपूर्णांकer to the memory reservation पूर्णांकerface or शून्य अगर no
 * memory reservation is needed.
 * @vm_size_left: Amount of reserved memory that so far has not been allocated.
 * @total_mem: Amount of reserved memory.
 */
काष्ठा vmw_validation_context अणु
	काष्ठा drm_खोलो_hash *ht;
	काष्ठा list_head resource_list;
	काष्ठा list_head resource_ctx_list;
	काष्ठा list_head bo_list;
	काष्ठा list_head page_list;
	काष्ठा ww_acquire_ctx ticket;
	काष्ठा mutex *res_mutex;
	अचिन्हित पूर्णांक merge_dups;
	अचिन्हित पूर्णांक mem_size_left;
	u8 *page_address;
	काष्ठा vmw_validation_mem *vm;
	माप_प्रकार vm_size_left;
	माप_प्रकार total_mem;
पूर्ण;

काष्ठा vmw_buffer_object;
काष्ठा vmw_resource;
काष्ठा vmw_fence_obj;

#अगर 0
/**
 * DECLARE_VAL_CONTEXT - Declare a validation context with initialization
 * @_name: The name of the variable
 * @_ht: The hash table used to find dups or शून्य अगर none
 * @_merge_dups: Whether to merge duplicate buffer object- or resource
 * entries. If set to true, ideally a hash table poपूर्णांकer should be supplied
 * as well unless the number of resources and buffer objects per validation
 * is known to be very small
 */
#पूर्ण_अगर
#घोषणा DECLARE_VAL_CONTEXT(_name, _ht, _merge_dups)			\
	काष्ठा vmw_validation_context _name =				\
	अणु .ht = _ht,							\
	  .resource_list = LIST_HEAD_INIT((_name).resource_list),	\
	  .resource_ctx_list = LIST_HEAD_INIT((_name).resource_ctx_list), \
	  .bo_list = LIST_HEAD_INIT((_name).bo_list),			\
	  .page_list = LIST_HEAD_INIT((_name).page_list),		\
	  .res_mutex = शून्य,						\
	  .merge_dups = _merge_dups,					\
	  .mem_size_left = 0,						\
	पूर्ण

/**
 * vmw_validation_has_bos - वापस whether the validation context has
 * any buffer objects रेजिस्टरed.
 *
 * @ctx: The validation context
 * Returns: Whether any buffer objects are रेजिस्टरed
 */
अटल अंतरभूत bool
vmw_validation_has_bos(काष्ठा vmw_validation_context *ctx)
अणु
	वापस !list_empty(&ctx->bo_list);
पूर्ण

/**
 * vmw_validation_set_val_mem - Register a validation mem object क्रम
 * validation memory reservation
 * @ctx: The validation context
 * @vm: Poपूर्णांकer to a काष्ठा vmw_validation_mem
 *
 * Must be set beक्रमe the first attempt to allocate validation memory.
 */
अटल अंतरभूत व्योम
vmw_validation_set_val_mem(काष्ठा vmw_validation_context *ctx,
			   काष्ठा vmw_validation_mem *vm)
अणु
	ctx->vm = vm;
पूर्ण

/**
 * vmw_validation_set_ht - Register a hash table क्रम duplicate finding
 * @ctx: The validation context
 * @ht: Poपूर्णांकer to a hash table to use क्रम duplicate finding
 * This function is पूर्णांकended to be used अगर the hash table wasn't
 * available at validation context declaration समय
 */
अटल अंतरभूत व्योम vmw_validation_set_ht(काष्ठा vmw_validation_context *ctx,
					 काष्ठा drm_खोलो_hash *ht)
अणु
	ctx->ht = ht;
पूर्ण

/**
 * vmw_validation_bo_reserve - Reserve buffer objects रेजिस्टरed with a
 * validation context
 * @ctx: The validation context
 * @पूर्णांकr: Perक्रमm रुकोs पूर्णांकerruptible
 *
 * Return: Zero on success, -ERESTARTSYS when पूर्णांकerrupted, negative error
 * code on failure
 */
अटल अंतरभूत पूर्णांक
vmw_validation_bo_reserve(काष्ठा vmw_validation_context *ctx,
			  bool पूर्णांकr)
अणु
	वापस tपंचांग_eu_reserve_buffers(&ctx->ticket, &ctx->bo_list, पूर्णांकr,
				      शून्य);
पूर्ण

/**
 * vmw_validation_bo_fence - Unreserve and fence buffer objects रेजिस्टरed
 * with a validation context
 * @ctx: The validation context
 *
 * This function unreserves the buffer objects previously reserved using
 * vmw_validation_bo_reserve, and fences them with a fence object.
 */
अटल अंतरभूत व्योम
vmw_validation_bo_fence(काष्ठा vmw_validation_context *ctx,
			काष्ठा vmw_fence_obj *fence)
अणु
	tपंचांग_eu_fence_buffer_objects(&ctx->ticket, &ctx->bo_list,
				    (व्योम *) fence);
पूर्ण

/**
 * vmw_validation_context_init - Initialize a validation context
 * @ctx: Poपूर्णांकer to the validation context to initialize
 *
 * This function initializes a validation context with @merge_dups set
 * to false
 */
अटल अंतरभूत व्योम
vmw_validation_context_init(काष्ठा vmw_validation_context *ctx)
अणु
	स_रखो(ctx, 0, माप(*ctx));
	INIT_LIST_HEAD(&ctx->resource_list);
	INIT_LIST_HEAD(&ctx->resource_ctx_list);
	INIT_LIST_HEAD(&ctx->bo_list);
पूर्ण

/**
 * vmw_validation_align - Align a validation memory allocation
 * @val: The size to be aligned
 *
 * Returns: @val aligned to the granularity used by the validation memory
 * allocator.
 */
अटल अंतरभूत अचिन्हित पूर्णांक vmw_validation_align(अचिन्हित पूर्णांक val)
अणु
	वापस ALIGN(val, माप(दीर्घ));
पूर्ण

पूर्णांक vmw_validation_add_bo(काष्ठा vmw_validation_context *ctx,
			  काष्ठा vmw_buffer_object *vbo,
			  bool as_mob, bool cpu_blit);
पूर्णांक vmw_validation_bo_validate_single(काष्ठा tपंचांग_buffer_object *bo,
				      bool पूर्णांकerruptible,
				      bool validate_as_mob);
पूर्णांक vmw_validation_bo_validate(काष्ठा vmw_validation_context *ctx, bool पूर्णांकr);
व्योम vmw_validation_unref_lists(काष्ठा vmw_validation_context *ctx);
पूर्णांक vmw_validation_add_resource(काष्ठा vmw_validation_context *ctx,
				काष्ठा vmw_resource *res,
				माप_प्रकार priv_size,
				u32 dirty,
				व्योम **p_node,
				bool *first_usage);
व्योम vmw_validation_drop_ht(काष्ठा vmw_validation_context *ctx);
पूर्णांक vmw_validation_res_reserve(काष्ठा vmw_validation_context *ctx,
			       bool पूर्णांकr);
व्योम vmw_validation_res_unreserve(काष्ठा vmw_validation_context *ctx,
				  bool backoff);
व्योम vmw_validation_res_चयन_backup(काष्ठा vmw_validation_context *ctx,
				      व्योम *val_निजी,
				      काष्ठा vmw_buffer_object *vbo,
				      अचिन्हित दीर्घ backup_offset);
पूर्णांक vmw_validation_res_validate(काष्ठा vmw_validation_context *ctx, bool पूर्णांकr);

पूर्णांक vmw_validation_prepare(काष्ठा vmw_validation_context *ctx,
			   काष्ठा mutex *mutex, bool पूर्णांकr);
व्योम vmw_validation_revert(काष्ठा vmw_validation_context *ctx);
व्योम vmw_validation_करोne(काष्ठा vmw_validation_context *ctx,
			 काष्ठा vmw_fence_obj *fence);

व्योम *vmw_validation_mem_alloc(काष्ठा vmw_validation_context *ctx,
			       अचिन्हित पूर्णांक size);
पूर्णांक vmw_validation_preload_bo(काष्ठा vmw_validation_context *ctx);
पूर्णांक vmw_validation_preload_res(काष्ठा vmw_validation_context *ctx,
			       अचिन्हित पूर्णांक size);
व्योम vmw_validation_res_set_dirty(काष्ठा vmw_validation_context *ctx,
				  व्योम *val_निजी, u32 dirty);
व्योम vmw_validation_bo_backoff(काष्ठा vmw_validation_context *ctx);

#पूर्ण_अगर
