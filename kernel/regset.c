<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/regset.h>

अटल पूर्णांक __regset_get(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			अचिन्हित पूर्णांक size,
			व्योम **data)
अणु
	व्योम *p = *data, *to_मुक्त = शून्य;
	पूर्णांक res;

	अगर (!regset->regset_get)
		वापस -EOPNOTSUPP;
	अगर (size > regset->n * regset->size)
		size = regset->n * regset->size;
	अगर (!p) अणु
		to_मुक्त = p = kzalloc(size, GFP_KERNEL);
		अगर (!p)
			वापस -ENOMEM;
	पूर्ण
	res = regset->regset_get(target, regset,
			   (काष्ठा membuf)अणु.p = p, .left = sizeपूर्ण);
	अगर (res < 0) अणु
		kमुक्त(to_मुक्त);
		वापस res;
	पूर्ण
	*data = p;
	वापस size - res;
पूर्ण

पूर्णांक regset_get(काष्ठा task_काष्ठा *target,
	       स्थिर काष्ठा user_regset *regset,
	       अचिन्हित पूर्णांक size,
	       व्योम *data)
अणु
	वापस __regset_get(target, regset, size, &data);
पूर्ण
EXPORT_SYMBOL(regset_get);

पूर्णांक regset_get_alloc(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक size,
		     व्योम **data)
अणु
	*data = शून्य;
	वापस __regset_get(target, regset, size, data);
पूर्ण
EXPORT_SYMBOL(regset_get_alloc);

/**
 * copy_regset_to_user - fetch a thपढ़ो's user_regset data पूर्णांकo user memory
 * @target:	thपढ़ो to be examined
 * @view:	&काष्ठा user_regset_view describing user thपढ़ो machine state
 * @setno:	index in @view->regsets
 * @offset:	offset पूर्णांकo the regset data, in bytes
 * @size:	amount of data to copy, in bytes
 * @data:	user-mode poपूर्णांकer to copy पूर्णांकo
 */
पूर्णांक copy_regset_to_user(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset_view *view,
			अचिन्हित पूर्णांक setno,
			अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक size,
			व्योम __user *data)
अणु
	स्थिर काष्ठा user_regset *regset = &view->regsets[setno];
	व्योम *buf;
	पूर्णांक ret;

	ret = regset_get_alloc(target, regset, size, &buf);
	अगर (ret > 0)
		ret = copy_to_user(data, buf, ret) ? -EFAULT : 0;
	kमुक्त(buf);
	वापस ret;
पूर्ण
