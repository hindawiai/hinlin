<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>

#समावेश <linux/usb/composite.h>

अटल LIST_HEAD(func_list);
अटल DEFINE_MUTEX(func_lock);

अटल काष्ठा usb_function_instance *try_get_usb_function_instance(स्थिर अक्षर *name)
अणु
	काष्ठा usb_function_driver *fd;
	काष्ठा usb_function_instance *fi;

	fi = ERR_PTR(-ENOENT);
	mutex_lock(&func_lock);
	list_क्रम_each_entry(fd, &func_list, list) अणु

		अगर (म_भेद(name, fd->name))
			जारी;

		अगर (!try_module_get(fd->mod)) अणु
			fi = ERR_PTR(-EBUSY);
			अवरोध;
		पूर्ण
		fi = fd->alloc_inst();
		अगर (IS_ERR(fi))
			module_put(fd->mod);
		अन्यथा
			fi->fd = fd;
		अवरोध;
	पूर्ण
	mutex_unlock(&func_lock);
	वापस fi;
पूर्ण

काष्ठा usb_function_instance *usb_get_function_instance(स्थिर अक्षर *name)
अणु
	काष्ठा usb_function_instance *fi;
	पूर्णांक ret;

	fi = try_get_usb_function_instance(name);
	अगर (!IS_ERR(fi))
		वापस fi;
	ret = PTR_ERR(fi);
	अगर (ret != -ENOENT)
		वापस fi;
	ret = request_module("usbfunc:%s", name);
	अगर (ret < 0)
		वापस ERR_PTR(ret);
	वापस try_get_usb_function_instance(name);
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_function_instance);

काष्ठा usb_function *usb_get_function(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा usb_function *f;

	f = fi->fd->alloc_func(fi);
	अगर (IS_ERR(f))
		वापस f;
	f->fi = fi;
	वापस f;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_function);

व्योम usb_put_function_instance(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा module *mod;

	अगर (!fi)
		वापस;

	mod = fi->fd->mod;
	fi->मुक्त_func_inst(fi);
	module_put(mod);
पूर्ण
EXPORT_SYMBOL_GPL(usb_put_function_instance);

व्योम usb_put_function(काष्ठा usb_function *f)
अणु
	अगर (!f)
		वापस;

	f->मुक्त_func(f);
पूर्ण
EXPORT_SYMBOL_GPL(usb_put_function);

पूर्णांक usb_function_रेजिस्टर(काष्ठा usb_function_driver *newf)
अणु
	काष्ठा usb_function_driver *fd;
	पूर्णांक ret;

	ret = -EEXIST;

	mutex_lock(&func_lock);
	list_क्रम_each_entry(fd, &func_list, list) अणु
		अगर (!म_भेद(fd->name, newf->name))
			जाओ out;
	पूर्ण
	ret = 0;
	list_add_tail(&newf->list, &func_list);
out:
	mutex_unlock(&func_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_function_रेजिस्टर);

व्योम usb_function_unरेजिस्टर(काष्ठा usb_function_driver *fd)
अणु
	mutex_lock(&func_lock);
	list_del(&fd->list);
	mutex_unlock(&func_lock);
पूर्ण
EXPORT_SYMBOL_GPL(usb_function_unरेजिस्टर);
