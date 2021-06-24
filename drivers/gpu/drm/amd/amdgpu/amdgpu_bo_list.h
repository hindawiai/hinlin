<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#अगर_अघोषित __AMDGPU_BO_LIST_H__
#घोषणा __AMDGPU_BO_LIST_H__

#समावेश <drm/tपंचांग/tपंचांग_execbuf_util.h>
#समावेश <drm/amdgpu_drm.h>

काष्ठा amdgpu_device;
काष्ठा amdgpu_bo;
काष्ठा amdgpu_bo_va;
काष्ठा amdgpu_fpriv;

काष्ठा amdgpu_bo_list_entry अणु
	काष्ठा tपंचांग_validate_buffer	tv;
	काष्ठा amdgpu_bo_va		*bo_va;
	uपूर्णांक32_t			priority;
	काष्ठा page			**user_pages;
	bool				user_invalidated;
पूर्ण;

काष्ठा amdgpu_bo_list अणु
	काष्ठा rcu_head rhead;
	काष्ठा kref refcount;
	काष्ठा amdgpu_bo *gds_obj;
	काष्ठा amdgpu_bo *gws_obj;
	काष्ठा amdgpu_bo *oa_obj;
	अचिन्हित first_userptr;
	अचिन्हित num_entries;
पूर्ण;

पूर्णांक amdgpu_bo_list_get(काष्ठा amdgpu_fpriv *fpriv, पूर्णांक id,
		       काष्ठा amdgpu_bo_list **result);
व्योम amdgpu_bo_list_get_list(काष्ठा amdgpu_bo_list *list,
			     काष्ठा list_head *validated);
व्योम amdgpu_bo_list_put(काष्ठा amdgpu_bo_list *list);
पूर्णांक amdgpu_bo_create_list_entry_array(काष्ठा drm_amdgpu_bo_list_in *in,
				      काष्ठा drm_amdgpu_bo_list_entry **info_param);

पूर्णांक amdgpu_bo_list_create(काष्ठा amdgpu_device *adev,
				 काष्ठा drm_file *filp,
				 काष्ठा drm_amdgpu_bo_list_entry *info,
				 अचिन्हित num_entries,
				 काष्ठा amdgpu_bo_list **list);

अटल अंतरभूत काष्ठा amdgpu_bo_list_entry *
amdgpu_bo_list_array_entry(काष्ठा amdgpu_bo_list *list, अचिन्हित index)
अणु
	काष्ठा amdgpu_bo_list_entry *array = (व्योम *)&list[1];

	वापस &array[index];
पूर्ण

#घोषणा amdgpu_bo_list_क्रम_each_entry(e, list) \
	क्रम (e = amdgpu_bo_list_array_entry(list, 0); \
	     e != amdgpu_bo_list_array_entry(list, (list)->num_entries); \
	     ++e)

#घोषणा amdgpu_bo_list_क्रम_each_userptr_entry(e, list) \
	क्रम (e = amdgpu_bo_list_array_entry(list, (list)->first_userptr); \
	     e != amdgpu_bo_list_array_entry(list, (list)->num_entries); \
	     ++e)

#पूर्ण_अगर
