<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright 2012-2014 VMware, Inc., Palo Alto, CA., USA
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

#अगर_अघोषित _VMWGFX_RESOURCE_PRIV_H_
#घोषणा _VMWGFX_RESOURCE_PRIV_H_

#समावेश "vmwgfx_drv.h"

/*
 * Extra memory required by the resource id's ida storage, which is allocated
 * separately from the base object itself. We estimate an on-average 128 bytes
 * per ida.
 */
#घोषणा VMW_IDA_ACC_SIZE 128

क्रमागत vmw_cmdbuf_res_state अणु
	VMW_CMDBUF_RES_COMMITTED,
	VMW_CMDBUF_RES_ADD,
	VMW_CMDBUF_RES_DEL
पूर्ण;

/**
 * काष्ठा vmw_user_resource_conv - Identअगरy a derived user-exported resource
 * type and provide a function to convert its tपंचांग_base_object poपूर्णांकer to
 * a काष्ठा vmw_resource
 */
काष्ठा vmw_user_resource_conv अणु
	क्रमागत tपंचांग_object_type object_type;
	काष्ठा vmw_resource *(*base_obj_to_res)(काष्ठा tपंचांग_base_object *base);
	व्योम (*res_मुक्त) (काष्ठा vmw_resource *res);
पूर्ण;

/**
 * काष्ठा vmw_res_func - members and functions common क्रम a resource type
 *
 * @res_type:          Enum that identअगरies the lru list to use क्रम eviction.
 * @needs_backup:      Whether the resource is guest-backed and needs
 *                     persistent buffer storage.
 * @type_name:         String that identअगरies the resource type.
 * @backup_placement:  TTM placement क्रम backup buffers.
 * @may_evict          Whether the resource may be evicted.
 * @create:            Create a hardware resource.
 * @destroy:           Destroy a hardware resource.
 * @bind:              Bind a hardware resource to persistent buffer storage.
 * @unbind:            Unbind a hardware resource from persistent
 *                     buffer storage.
 * @commit_notअगरy:     If the resource is a command buffer managed resource,
 *                     callback to notअगरy that a define or हटाओ command
 *                     has been committed to the device.
 * @dirty_alloc:       Allocate a dirty tracker. शून्य अगर dirty-tracking is not
 *                     supported.
 * @dirty_मुक्त:        Free the dirty tracker.
 * @dirty_sync:        Upload the dirty mob contents to the resource.
 * @dirty_add_range:   Add a sequential dirty range to the resource
 *                     dirty tracker.
 * @clean:             Clean the resource.
 */
काष्ठा vmw_res_func अणु
	क्रमागत vmw_res_type res_type;
	bool needs_backup;
	स्थिर अक्षर *type_name;
	काष्ठा tपंचांग_placement *backup_placement;
	bool may_evict;
	u32 prio;
	u32 dirty_prio;

	पूर्णांक (*create) (काष्ठा vmw_resource *res);
	पूर्णांक (*destroy) (काष्ठा vmw_resource *res);
	पूर्णांक (*bind) (काष्ठा vmw_resource *res,
		     काष्ठा tपंचांग_validate_buffer *val_buf);
	पूर्णांक (*unbind) (काष्ठा vmw_resource *res,
		       bool पढ़ोback,
		       काष्ठा tपंचांग_validate_buffer *val_buf);
	व्योम (*commit_notअगरy)(काष्ठा vmw_resource *res,
			      क्रमागत vmw_cmdbuf_res_state state);
	पूर्णांक (*dirty_alloc)(काष्ठा vmw_resource *res);
	व्योम (*dirty_मुक्त)(काष्ठा vmw_resource *res);
	पूर्णांक (*dirty_sync)(काष्ठा vmw_resource *res);
	व्योम (*dirty_range_add)(काष्ठा vmw_resource *res, माप_प्रकार start,
				 माप_प्रकार end);
	पूर्णांक (*clean)(काष्ठा vmw_resource *res);
पूर्ण;

/**
 * काष्ठा vmw_simple_resource_func - members and functions common क्रम the
 * simple resource helpers.
 * @res_func:  काष्ठा vmw_res_func as described above.
 * @tपंचांग_res_type:  TTM resource type used क्रम handle recognition.
 * @size:  Size of the simple resource inक्रमmation काष्ठा.
 * @init:  Initialize the simple resource inक्रमmation.
 * @hw_destroy:  A resource hw_destroy function.
 * @set_arg_handle:  Set the handle output argument of the ioctl create काष्ठा.
 */
काष्ठा vmw_simple_resource_func अणु
	स्थिर काष्ठा vmw_res_func res_func;
	पूर्णांक tपंचांग_res_type;
	माप_प्रकार size;
	पूर्णांक (*init)(काष्ठा vmw_resource *res, व्योम *data);
	व्योम (*hw_destroy)(काष्ठा vmw_resource *res);
	व्योम (*set_arg_handle)(व्योम *data, u32 handle);
पूर्ण;

/**
 * काष्ठा vmw_simple_resource - Kernel only side simple resource
 * @res: The resource we derive from.
 * @func: The method and member भव table.
 */
काष्ठा vmw_simple_resource अणु
	काष्ठा vmw_resource res;
	स्थिर काष्ठा vmw_simple_resource_func *func;
पूर्ण;

पूर्णांक vmw_resource_alloc_id(काष्ठा vmw_resource *res);
व्योम vmw_resource_release_id(काष्ठा vmw_resource *res);
पूर्णांक vmw_resource_init(काष्ठा vmw_निजी *dev_priv, काष्ठा vmw_resource *res,
		      bool delay_id,
		      व्योम (*res_मुक्त) (काष्ठा vmw_resource *res),
		      स्थिर काष्ठा vmw_res_func *func);
पूर्णांक
vmw_simple_resource_create_ioctl(काष्ठा drm_device *dev,
				 व्योम *data,
				 काष्ठा drm_file *file_priv,
				 स्थिर काष्ठा vmw_simple_resource_func *func);
काष्ठा vmw_resource *
vmw_simple_resource_lookup(काष्ठा tपंचांग_object_file *tfile,
			   uपूर्णांक32_t handle,
			   स्थिर काष्ठा vmw_simple_resource_func *func);
#पूर्ण_अगर
