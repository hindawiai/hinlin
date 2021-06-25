<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2016 VMware, Inc., Palo Alto, CA., USA
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

/**
 * काष्ठा vmw_user_simple_resource - User-space simple resource काष्ठा
 *
 * @base: The TTM base object implementing user-space visibility.
 * @account_size: How much memory was accounted क्रम this object.
 * @simple: The embedded काष्ठा vmw_simple_resource.
 */
काष्ठा vmw_user_simple_resource अणु
	काष्ठा tपंचांग_base_object base;
	माप_प्रकार account_size;
	काष्ठा vmw_simple_resource simple;
/*
 * Nothing to be placed after @simple, since size of @simple is
 * unknown.
 */
पूर्ण;


/**
 * vmw_simple_resource_init - Initialize a simple resource object.
 *
 * @dev_priv: Poपूर्णांकer to a काष्ठा device निजी.
 * @simple: The काष्ठा vmw_simple_resource to initialize.
 * @data: Data passed to the inक्रमmation initialization function.
 * @res_मुक्त: Function poपूर्णांकer to destroy the simple resource.
 *
 * Returns:
 *   0 अगर succeeded.
 *   Negative error value अगर error, in which हाल the resource will have been
 * मुक्तd.
 */
अटल पूर्णांक vmw_simple_resource_init(काष्ठा vmw_निजी *dev_priv,
				    काष्ठा vmw_simple_resource *simple,
				    व्योम *data,
				    व्योम (*res_मुक्त)(काष्ठा vmw_resource *res))
अणु
	काष्ठा vmw_resource *res = &simple->res;
	पूर्णांक ret;

	ret = vmw_resource_init(dev_priv, res, false, res_मुक्त,
				&simple->func->res_func);

	अगर (ret) अणु
		res_मुक्त(res);
		वापस ret;
	पूर्ण

	ret = simple->func->init(res, data);
	अगर (ret) अणु
		vmw_resource_unreference(&res);
		वापस ret;
	पूर्ण

	simple->res.hw_destroy = simple->func->hw_destroy;

	वापस 0;
पूर्ण

/**
 * vmw_simple_resource_मुक्त - Free a simple resource object.
 *
 * @res: The काष्ठा vmw_resource member of the simple resource object.
 *
 * Frees memory and memory accounting क्रम the object.
 */
अटल व्योम vmw_simple_resource_मुक्त(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_user_simple_resource *usimple =
		container_of(res, काष्ठा vmw_user_simple_resource,
			     simple.res);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	माप_प्रकार size = usimple->account_size;

	tपंचांग_base_object_kमुक्त(usimple, base);
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), size);
पूर्ण

/**
 * vmw_simple_resource_base_release - TTM object release callback
 *
 * @p_base: The काष्ठा tपंचांग_base_object member of the simple resource object.
 *
 * Called when the last reference to the embedded काष्ठा tपंचांग_base_object is
 * gone. Typically results in an object मुक्त, unless there are other
 * references to the embedded काष्ठा vmw_resource.
 */
अटल व्योम vmw_simple_resource_base_release(काष्ठा tपंचांग_base_object **p_base)
अणु
	काष्ठा tपंचांग_base_object *base = *p_base;
	काष्ठा vmw_user_simple_resource *usimple =
		container_of(base, काष्ठा vmw_user_simple_resource, base);
	काष्ठा vmw_resource *res = &usimple->simple.res;

	*p_base = शून्य;
	vmw_resource_unreference(&res);
पूर्ण

/**
 * vmw_simple_resource_create_ioctl - Helper to set up an ioctl function to
 * create a काष्ठा vmw_simple_resource.
 *
 * @dev: Poपूर्णांकer to a काष्ठा drm device.
 * @data: Ioctl argument.
 * @file_priv: Poपूर्णांकer to a काष्ठा drm_file identअगरying the caller.
 * @func: Poपूर्णांकer to a काष्ठा vmw_simple_resource_func identअगरying the
 * simple resource type.
 *
 * Returns:
 *   0 अगर success,
 *   Negative error value on error.
 */
पूर्णांक
vmw_simple_resource_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv,
				 स्थिर काष्ठा vmw_simple_resource_func *func)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा vmw_user_simple_resource *usimple;
	काष्ठा vmw_resource *res;
	काष्ठा vmw_resource *पंचांगp;
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	माप_प्रकार alloc_size;
	माप_प्रकार account_size;
	पूर्णांक ret;

	alloc_size = दुरत्व(काष्ठा vmw_user_simple_resource, simple) +
	  func->size;
	account_size = tपंचांग_round_pot(alloc_size) + VMW_IDA_ACC_SIZE +
		TTM_OBJ_EXTRA_SIZE;

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (ret)
		वापस ret;

	ret = tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv), account_size,
				   &ctx);
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
	अगर (ret) अणु
		अगर (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for %s"
				  " creation.\n", func->res_func.type_name);

		जाओ out_ret;
	पूर्ण

	usimple = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!usimple) अणु
		tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv),
				    account_size);
		ret = -ENOMEM;
		जाओ out_ret;
	पूर्ण

	usimple->simple.func = func;
	usimple->account_size = account_size;
	res = &usimple->simple.res;
	usimple->base.shareable = false;
	usimple->base.tfile = शून्य;

	/*
	 * From here on, the deकाष्ठाor takes over resource मुक्तing.
	 */
	ret = vmw_simple_resource_init(dev_priv, &usimple->simple,
				       data, vmw_simple_resource_मुक्त);
	अगर (ret)
		जाओ out_ret;

	पंचांगp = vmw_resource_reference(res);
	ret = tपंचांग_base_object_init(tfile, &usimple->base, false,
				   func->tपंचांग_res_type,
				   &vmw_simple_resource_base_release, शून्य);

	अगर (ret) अणु
		vmw_resource_unreference(&पंचांगp);
		जाओ out_err;
	पूर्ण

	func->set_arg_handle(data, usimple->base.handle);
out_err:
	vmw_resource_unreference(&res);
out_ret:
	वापस ret;
पूर्ण

/**
 * vmw_simple_resource_lookup - Look up a simple resource from its user-space
 * handle.
 *
 * @tfile: काष्ठा tपंचांग_object_file identअगरying the caller.
 * @handle: The user-space handle.
 * @func: The काष्ठा vmw_simple_resource_func identअगरying the simple resource
 * type.
 *
 * Returns: Refcounted poपूर्णांकer to the embedded काष्ठा vmw_resource अगर
 * successfule. Error poपूर्णांकer otherwise.
 */
काष्ठा vmw_resource *
vmw_simple_resource_lookup(काष्ठा tपंचांग_object_file *tfile,
			   uपूर्णांक32_t handle,
			   स्थिर काष्ठा vmw_simple_resource_func *func)
अणु
	काष्ठा vmw_user_simple_resource *usimple;
	काष्ठा tपंचांग_base_object *base;
	काष्ठा vmw_resource *res;

	base = tपंचांग_base_object_lookup(tfile, handle);
	अगर (!base) अणु
		VMW_DEBUG_USER("Invalid %s handle 0x%08lx.\n",
			       func->res_func.type_name,
			       (अचिन्हित दीर्घ) handle);
		वापस ERR_PTR(-ESRCH);
	पूर्ण

	अगर (tपंचांग_base_object_type(base) != func->tपंचांग_res_type) अणु
		tपंचांग_base_object_unref(&base);
		VMW_DEBUG_USER("Invalid type of %s handle 0x%08lx.\n",
			       func->res_func.type_name,
			       (अचिन्हित दीर्घ) handle);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	usimple = container_of(base, typeof(*usimple), base);
	res = vmw_resource_reference(&usimple->simple.res);
	tपंचांग_base_object_unref(&base);

	वापस res;
पूर्ण
