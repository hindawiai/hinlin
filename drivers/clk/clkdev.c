<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/clk/clkdev.c
 *
 *  Copyright (C) 2008 Russell King.
 *
 * Helper क्रम the clk API to assist looking up a काष्ठा clk.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/mutex.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>

#समावेश "clk.h"

अटल LIST_HEAD(घड़ीs);
अटल DEFINE_MUTEX(घड़ीs_mutex);

/*
 * Find the correct काष्ठा clk क्रम the device and connection ID.
 * We करो slightly fuzzy matching here:
 *  An entry with a शून्य ID is assumed to be a wildcard.
 *  If an entry has a device ID, it must match
 *  If an entry has a connection ID, it must match
 * Then we take the most specअगरic entry - with the following
 * order of precedence: dev+con > dev only > con only.
 */
अटल काष्ठा clk_lookup *clk_find(स्थिर अक्षर *dev_id, स्थिर अक्षर *con_id)
अणु
	काष्ठा clk_lookup *p, *cl = शून्य;
	पूर्णांक match, best_found = 0, best_possible = 0;

	अगर (dev_id)
		best_possible += 2;
	अगर (con_id)
		best_possible += 1;

	lockdep_निश्चित_held(&घड़ीs_mutex);

	list_क्रम_each_entry(p, &घड़ीs, node) अणु
		match = 0;
		अगर (p->dev_id) अणु
			अगर (!dev_id || म_भेद(p->dev_id, dev_id))
				जारी;
			match += 2;
		पूर्ण
		अगर (p->con_id) अणु
			अगर (!con_id || म_भेद(p->con_id, con_id))
				जारी;
			match += 1;
		पूर्ण

		अगर (match > best_found) अणु
			cl = p;
			अगर (match != best_possible)
				best_found = match;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
	वापस cl;
पूर्ण

काष्ठा clk_hw *clk_find_hw(स्थिर अक्षर *dev_id, स्थिर अक्षर *con_id)
अणु
	काष्ठा clk_lookup *cl;
	काष्ठा clk_hw *hw = ERR_PTR(-ENOENT);

	mutex_lock(&घड़ीs_mutex);
	cl = clk_find(dev_id, con_id);
	अगर (cl)
		hw = cl->clk_hw;
	mutex_unlock(&घड़ीs_mutex);

	वापस hw;
पूर्ण

अटल काष्ठा clk *__clk_get_sys(काष्ठा device *dev, स्थिर अक्षर *dev_id,
				 स्थिर अक्षर *con_id)
अणु
	काष्ठा clk_hw *hw = clk_find_hw(dev_id, con_id);

	वापस clk_hw_create_clk(dev, hw, dev_id, con_id);
पूर्ण

काष्ठा clk *clk_get_sys(स्थिर अक्षर *dev_id, स्थिर अक्षर *con_id)
अणु
	वापस __clk_get_sys(शून्य, dev_id, con_id);
पूर्ण
EXPORT_SYMBOL(clk_get_sys);

काष्ठा clk *clk_get(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	स्थिर अक्षर *dev_id = dev ? dev_name(dev) : शून्य;
	काष्ठा clk_hw *hw;

	अगर (dev && dev->of_node) अणु
		hw = of_clk_get_hw(dev->of_node, 0, con_id);
		अगर (!IS_ERR(hw) || PTR_ERR(hw) == -EPROBE_DEFER)
			वापस clk_hw_create_clk(dev, hw, dev_id, con_id);
	पूर्ण

	वापस __clk_get_sys(dev, dev_id, con_id);
पूर्ण
EXPORT_SYMBOL(clk_get);

व्योम clk_put(काष्ठा clk *clk)
अणु
	__clk_put(clk);
पूर्ण
EXPORT_SYMBOL(clk_put);

अटल व्योम __clkdev_add(काष्ठा clk_lookup *cl)
अणु
	mutex_lock(&घड़ीs_mutex);
	list_add_tail(&cl->node, &घड़ीs);
	mutex_unlock(&घड़ीs_mutex);
पूर्ण

व्योम clkdev_add(काष्ठा clk_lookup *cl)
अणु
	अगर (!cl->clk_hw)
		cl->clk_hw = __clk_get_hw(cl->clk);
	__clkdev_add(cl);
पूर्ण
EXPORT_SYMBOL(clkdev_add);

व्योम clkdev_add_table(काष्ठा clk_lookup *cl, माप_प्रकार num)
अणु
	mutex_lock(&घड़ीs_mutex);
	जबतक (num--) अणु
		cl->clk_hw = __clk_get_hw(cl->clk);
		list_add_tail(&cl->node, &घड़ीs);
		cl++;
	पूर्ण
	mutex_unlock(&घड़ीs_mutex);
पूर्ण

#घोषणा MAX_DEV_ID	20
#घोषणा MAX_CON_ID	16

काष्ठा clk_lookup_alloc अणु
	काष्ठा clk_lookup cl;
	अक्षर	dev_id[MAX_DEV_ID];
	अक्षर	con_id[MAX_CON_ID];
पूर्ण;

अटल काष्ठा clk_lookup * __ref
vclkdev_alloc(काष्ठा clk_hw *hw, स्थिर अक्षर *con_id, स्थिर अक्षर *dev_fmt,
	बहु_सूची ap)
अणु
	काष्ठा clk_lookup_alloc *cla;

	cla = kzalloc(माप(*cla), GFP_KERNEL);
	अगर (!cla)
		वापस शून्य;

	cla->cl.clk_hw = hw;
	अगर (con_id) अणु
		strlcpy(cla->con_id, con_id, माप(cla->con_id));
		cla->cl.con_id = cla->con_id;
	पूर्ण

	अगर (dev_fmt) अणु
		vscnम_लिखो(cla->dev_id, माप(cla->dev_id), dev_fmt, ap);
		cla->cl.dev_id = cla->dev_id;
	पूर्ण

	वापस &cla->cl;
पूर्ण

अटल काष्ठा clk_lookup *
vclkdev_create(काष्ठा clk_hw *hw, स्थिर अक्षर *con_id, स्थिर अक्षर *dev_fmt,
	बहु_सूची ap)
अणु
	काष्ठा clk_lookup *cl;

	cl = vclkdev_alloc(hw, con_id, dev_fmt, ap);
	अगर (cl)
		__clkdev_add(cl);

	वापस cl;
पूर्ण

काष्ठा clk_lookup * __ref
clkdev_alloc(काष्ठा clk *clk, स्थिर अक्षर *con_id, स्थिर अक्षर *dev_fmt, ...)
अणु
	काष्ठा clk_lookup *cl;
	बहु_सूची ap;

	बहु_शुरू(ap, dev_fmt);
	cl = vclkdev_alloc(__clk_get_hw(clk), con_id, dev_fmt, ap);
	बहु_पूर्ण(ap);

	वापस cl;
पूर्ण
EXPORT_SYMBOL(clkdev_alloc);

काष्ठा clk_lookup *
clkdev_hw_alloc(काष्ठा clk_hw *hw, स्थिर अक्षर *con_id, स्थिर अक्षर *dev_fmt, ...)
अणु
	काष्ठा clk_lookup *cl;
	बहु_सूची ap;

	बहु_शुरू(ap, dev_fmt);
	cl = vclkdev_alloc(hw, con_id, dev_fmt, ap);
	बहु_पूर्ण(ap);

	वापस cl;
पूर्ण
EXPORT_SYMBOL(clkdev_hw_alloc);

/**
 * clkdev_create - allocate and add a clkdev lookup काष्ठाure
 * @clk: काष्ठा clk to associate with all clk_lookups
 * @con_id: connection ID string on device
 * @dev_fmt: क्रमmat string describing device name
 *
 * Returns a clk_lookup काष्ठाure, which can be later unरेजिस्टरed and
 * मुक्तd.
 */
काष्ठा clk_lookup *clkdev_create(काष्ठा clk *clk, स्थिर अक्षर *con_id,
	स्थिर अक्षर *dev_fmt, ...)
अणु
	काष्ठा clk_lookup *cl;
	बहु_सूची ap;

	बहु_शुरू(ap, dev_fmt);
	cl = vclkdev_create(__clk_get_hw(clk), con_id, dev_fmt, ap);
	बहु_पूर्ण(ap);

	वापस cl;
पूर्ण
EXPORT_SYMBOL_GPL(clkdev_create);

/**
 * clkdev_hw_create - allocate and add a clkdev lookup काष्ठाure
 * @hw: काष्ठा clk_hw to associate with all clk_lookups
 * @con_id: connection ID string on device
 * @dev_fmt: क्रमmat string describing device name
 *
 * Returns a clk_lookup काष्ठाure, which can be later unरेजिस्टरed and
 * मुक्तd.
 */
काष्ठा clk_lookup *clkdev_hw_create(काष्ठा clk_hw *hw, स्थिर अक्षर *con_id,
	स्थिर अक्षर *dev_fmt, ...)
अणु
	काष्ठा clk_lookup *cl;
	बहु_सूची ap;

	बहु_शुरू(ap, dev_fmt);
	cl = vclkdev_create(hw, con_id, dev_fmt, ap);
	बहु_पूर्ण(ap);

	वापस cl;
पूर्ण
EXPORT_SYMBOL_GPL(clkdev_hw_create);

पूर्णांक clk_add_alias(स्थिर अक्षर *alias, स्थिर अक्षर *alias_dev_name,
	स्थिर अक्षर *con_id, काष्ठा device *dev)
अणु
	काष्ठा clk *r = clk_get(dev, con_id);
	काष्ठा clk_lookup *l;

	अगर (IS_ERR(r))
		वापस PTR_ERR(r);

	l = clkdev_create(r, alias, alias_dev_name ? "%s" : शून्य,
			  alias_dev_name);
	clk_put(r);

	वापस l ? 0 : -ENODEV;
पूर्ण
EXPORT_SYMBOL(clk_add_alias);

/*
 * clkdev_drop - हटाओ a घड़ी dynamically allocated
 */
व्योम clkdev_drop(काष्ठा clk_lookup *cl)
अणु
	mutex_lock(&घड़ीs_mutex);
	list_del(&cl->node);
	mutex_unlock(&घड़ीs_mutex);
	kमुक्त(cl);
पूर्ण
EXPORT_SYMBOL(clkdev_drop);

अटल काष्ठा clk_lookup *__clk_रेजिस्टर_clkdev(काष्ठा clk_hw *hw,
						स्थिर अक्षर *con_id,
						स्थिर अक्षर *dev_id, ...)
अणु
	काष्ठा clk_lookup *cl;
	बहु_सूची ap;

	बहु_शुरू(ap, dev_id);
	cl = vclkdev_create(hw, con_id, dev_id, ap);
	बहु_पूर्ण(ap);

	वापस cl;
पूर्ण

अटल पूर्णांक करो_clk_रेजिस्टर_clkdev(काष्ठा clk_hw *hw,
	काष्ठा clk_lookup **cl, स्थिर अक्षर *con_id, स्थिर अक्षर *dev_id)
अणु
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	/*
	 * Since dev_id can be शून्य, and शून्य is handled specially, we must
	 * pass it as either a शून्य क्रमmat string, or with "%s".
	 */
	अगर (dev_id)
		*cl = __clk_रेजिस्टर_clkdev(hw, con_id, "%s", dev_id);
	अन्यथा
		*cl = __clk_रेजिस्टर_clkdev(hw, con_id, शून्य);

	वापस *cl ? 0 : -ENOMEM;
पूर्ण

/**
 * clk_रेजिस्टर_clkdev - रेजिस्टर one घड़ी lookup क्रम a काष्ठा clk
 * @clk: काष्ठा clk to associate with all clk_lookups
 * @con_id: connection ID string on device
 * @dev_id: string describing device name
 *
 * con_id or dev_id may be शून्य as a wildcard, just as in the rest of
 * clkdev.
 *
 * To make things easier क्रम mass registration, we detect error clks
 * from a previous clk_रेजिस्टर() call, and वापस the error code क्रम
 * those.  This is to permit this function to be called immediately
 * after clk_रेजिस्टर().
 */
पूर्णांक clk_रेजिस्टर_clkdev(काष्ठा clk *clk, स्थिर अक्षर *con_id,
	स्थिर अक्षर *dev_id)
अणु
	काष्ठा clk_lookup *cl;

	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	वापस करो_clk_रेजिस्टर_clkdev(__clk_get_hw(clk), &cl, con_id,
					      dev_id);
पूर्ण
EXPORT_SYMBOL(clk_रेजिस्टर_clkdev);

/**
 * clk_hw_रेजिस्टर_clkdev - रेजिस्टर one घड़ी lookup क्रम a काष्ठा clk_hw
 * @hw: काष्ठा clk_hw to associate with all clk_lookups
 * @con_id: connection ID string on device
 * @dev_id: क्रमmat string describing device name
 *
 * con_id or dev_id may be शून्य as a wildcard, just as in the rest of
 * clkdev.
 *
 * To make things easier क्रम mass registration, we detect error clk_hws
 * from a previous clk_hw_रेजिस्टर_*() call, and वापस the error code क्रम
 * those.  This is to permit this function to be called immediately
 * after clk_hw_रेजिस्टर_*().
 */
पूर्णांक clk_hw_रेजिस्टर_clkdev(काष्ठा clk_hw *hw, स्थिर अक्षर *con_id,
	स्थिर अक्षर *dev_id)
अणु
	काष्ठा clk_lookup *cl;

	वापस करो_clk_रेजिस्टर_clkdev(hw, &cl, con_id, dev_id);
पूर्ण
EXPORT_SYMBOL(clk_hw_रेजिस्टर_clkdev);

अटल व्योम devm_clkdev_release(काष्ठा device *dev, व्योम *res)
अणु
	clkdev_drop(*(काष्ठा clk_lookup **)res);
पूर्ण

अटल पूर्णांक devm_clk_match_clkdev(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा clk_lookup **l = res;

	वापस *l == data;
पूर्ण

/**
 * devm_clk_release_clkdev - Resource managed clkdev lookup release
 * @dev: device this lookup is bound
 * @con_id: connection ID string on device
 * @dev_id: क्रमmat string describing device name
 *
 * Drop the clkdev lookup created with devm_clk_hw_रेजिस्टर_clkdev.
 * Normally this function will not need to be called and the resource
 * management code will ensure that the resource is मुक्तd.
 */
व्योम devm_clk_release_clkdev(काष्ठा device *dev, स्थिर अक्षर *con_id,
			     स्थिर अक्षर *dev_id)
अणु
	काष्ठा clk_lookup *cl;
	पूर्णांक rval;

	mutex_lock(&घड़ीs_mutex);
	cl = clk_find(dev_id, con_id);
	mutex_unlock(&घड़ीs_mutex);

	WARN_ON(!cl);
	rval = devres_release(dev, devm_clkdev_release,
			      devm_clk_match_clkdev, cl);
	WARN_ON(rval);
पूर्ण
EXPORT_SYMBOL(devm_clk_release_clkdev);

/**
 * devm_clk_hw_रेजिस्टर_clkdev - managed clk lookup registration क्रम clk_hw
 * @dev: device this lookup is bound
 * @hw: काष्ठा clk_hw to associate with all clk_lookups
 * @con_id: connection ID string on device
 * @dev_id: क्रमmat string describing device name
 *
 * con_id or dev_id may be शून्य as a wildcard, just as in the rest of
 * clkdev.
 *
 * To make things easier क्रम mass registration, we detect error clk_hws
 * from a previous clk_hw_रेजिस्टर_*() call, and वापस the error code क्रम
 * those.  This is to permit this function to be called immediately
 * after clk_hw_रेजिस्टर_*().
 */
पूर्णांक devm_clk_hw_रेजिस्टर_clkdev(काष्ठा device *dev, काष्ठा clk_hw *hw,
				स्थिर अक्षर *con_id, स्थिर अक्षर *dev_id)
अणु
	पूर्णांक rval = -ENOMEM;
	काष्ठा clk_lookup **cl;

	cl = devres_alloc(devm_clkdev_release, माप(*cl), GFP_KERNEL);
	अगर (cl) अणु
		rval = करो_clk_रेजिस्टर_clkdev(hw, cl, con_id, dev_id);
		अगर (!rval)
			devres_add(dev, cl);
		अन्यथा
			devres_मुक्त(cl);
	पूर्ण
	वापस rval;
पूर्ण
EXPORT_SYMBOL(devm_clk_hw_रेजिस्टर_clkdev);
