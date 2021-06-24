<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/gfp.h>

अटल व्योम devm_clk_release(काष्ठा device *dev, व्योम *res)
अणु
	clk_put(*(काष्ठा clk **)res);
पूर्ण

काष्ठा clk *devm_clk_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	काष्ठा clk **ptr, *clk;

	ptr = devres_alloc(devm_clk_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	clk = clk_get(dev, id);
	अगर (!IS_ERR(clk)) अणु
		*ptr = clk;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस clk;
पूर्ण
EXPORT_SYMBOL(devm_clk_get);

काष्ठा clk *devm_clk_get_optional(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	काष्ठा clk *clk = devm_clk_get(dev, id);

	अगर (clk == ERR_PTR(-ENOENT))
		वापस शून्य;

	वापस clk;
पूर्ण
EXPORT_SYMBOL(devm_clk_get_optional);

काष्ठा clk_bulk_devres अणु
	काष्ठा clk_bulk_data *clks;
	पूर्णांक num_clks;
पूर्ण;

अटल व्योम devm_clk_bulk_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा clk_bulk_devres *devres = res;

	clk_bulk_put(devres->num_clks, devres->clks);
पूर्ण

अटल पूर्णांक __devm_clk_bulk_get(काष्ठा device *dev, पूर्णांक num_clks,
			       काष्ठा clk_bulk_data *clks, bool optional)
अणु
	काष्ठा clk_bulk_devres *devres;
	पूर्णांक ret;

	devres = devres_alloc(devm_clk_bulk_release,
			      माप(*devres), GFP_KERNEL);
	अगर (!devres)
		वापस -ENOMEM;

	अगर (optional)
		ret = clk_bulk_get_optional(dev, num_clks, clks);
	अन्यथा
		ret = clk_bulk_get(dev, num_clks, clks);
	अगर (!ret) अणु
		devres->clks = clks;
		devres->num_clks = num_clks;
		devres_add(dev, devres);
	पूर्ण अन्यथा अणु
		devres_मुक्त(devres);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक __must_check devm_clk_bulk_get(काष्ठा device *dev, पूर्णांक num_clks,
		      काष्ठा clk_bulk_data *clks)
अणु
	वापस __devm_clk_bulk_get(dev, num_clks, clks, false);
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_bulk_get);

पूर्णांक __must_check devm_clk_bulk_get_optional(काष्ठा device *dev, पूर्णांक num_clks,
		      काष्ठा clk_bulk_data *clks)
अणु
	वापस __devm_clk_bulk_get(dev, num_clks, clks, true);
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_bulk_get_optional);

पूर्णांक __must_check devm_clk_bulk_get_all(काष्ठा device *dev,
				       काष्ठा clk_bulk_data **clks)
अणु
	काष्ठा clk_bulk_devres *devres;
	पूर्णांक ret;

	devres = devres_alloc(devm_clk_bulk_release,
			      माप(*devres), GFP_KERNEL);
	अगर (!devres)
		वापस -ENOMEM;

	ret = clk_bulk_get_all(dev, &devres->clks);
	अगर (ret > 0) अणु
		*clks = devres->clks;
		devres->num_clks = ret;
		devres_add(dev, devres);
	पूर्ण अन्यथा अणु
		devres_मुक्त(devres);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_bulk_get_all);

अटल पूर्णांक devm_clk_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा clk **c = res;
	अगर (!c || !*c) अणु
		WARN_ON(!c || !*c);
		वापस 0;
	पूर्ण
	वापस *c == data;
पूर्ण

व्योम devm_clk_put(काष्ठा device *dev, काष्ठा clk *clk)
अणु
	पूर्णांक ret;

	ret = devres_release(dev, devm_clk_release, devm_clk_match, clk);

	WARN_ON(ret);
पूर्ण
EXPORT_SYMBOL(devm_clk_put);

काष्ठा clk *devm_get_clk_from_child(काष्ठा device *dev,
				    काष्ठा device_node *np, स्थिर अक्षर *con_id)
अणु
	काष्ठा clk **ptr, *clk;

	ptr = devres_alloc(devm_clk_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	clk = of_clk_get_by_name(np, con_id);
	अगर (!IS_ERR(clk)) अणु
		*ptr = clk;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस clk;
पूर्ण
EXPORT_SYMBOL(devm_get_clk_from_child);
