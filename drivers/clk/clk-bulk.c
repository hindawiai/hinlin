<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2017 NXP
 *
 * Dong Aisheng <aisheng.करोng@nxp.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

अटल पूर्णांक __must_check of_clk_bulk_get(काष्ठा device_node *np, पूर्णांक num_clks,
					काष्ठा clk_bulk_data *clks)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < num_clks; i++) अणु
		clks[i].id = शून्य;
		clks[i].clk = शून्य;
	पूर्ण

	क्रम (i = 0; i < num_clks; i++) अणु
		of_property_पढ़ो_string_index(np, "clock-names", i, &clks[i].id);
		clks[i].clk = of_clk_get(np, i);
		अगर (IS_ERR(clks[i].clk)) अणु
			ret = PTR_ERR(clks[i].clk);
			pr_err("%pOF: Failed to get clk index: %d ret: %d\n",
			       np, i, ret);
			clks[i].clk = शून्य;
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	clk_bulk_put(i, clks);

	वापस ret;
पूर्ण

अटल पूर्णांक __must_check of_clk_bulk_get_all(काष्ठा device_node *np,
					    काष्ठा clk_bulk_data **clks)
अणु
	काष्ठा clk_bulk_data *clk_bulk;
	पूर्णांक num_clks;
	पूर्णांक ret;

	num_clks = of_clk_get_parent_count(np);
	अगर (!num_clks)
		वापस 0;

	clk_bulk = kदो_स्मृति_array(num_clks, माप(*clk_bulk), GFP_KERNEL);
	अगर (!clk_bulk)
		वापस -ENOMEM;

	ret = of_clk_bulk_get(np, num_clks, clk_bulk);
	अगर (ret) अणु
		kमुक्त(clk_bulk);
		वापस ret;
	पूर्ण

	*clks = clk_bulk;

	वापस num_clks;
पूर्ण

व्योम clk_bulk_put(पूर्णांक num_clks, काष्ठा clk_bulk_data *clks)
अणु
	जबतक (--num_clks >= 0) अणु
		clk_put(clks[num_clks].clk);
		clks[num_clks].clk = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(clk_bulk_put);

अटल पूर्णांक __clk_bulk_get(काष्ठा device *dev, पूर्णांक num_clks,
			  काष्ठा clk_bulk_data *clks, bool optional)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < num_clks; i++)
		clks[i].clk = शून्य;

	क्रम (i = 0; i < num_clks; i++) अणु
		clks[i].clk = clk_get(dev, clks[i].id);
		अगर (IS_ERR(clks[i].clk)) अणु
			ret = PTR_ERR(clks[i].clk);
			clks[i].clk = शून्य;

			अगर (ret == -ENOENT && optional)
				जारी;

			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to get clk '%s': %d\n",
					clks[i].id, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	clk_bulk_put(i, clks);

	वापस ret;
पूर्ण

पूर्णांक __must_check clk_bulk_get(काष्ठा device *dev, पूर्णांक num_clks,
			      काष्ठा clk_bulk_data *clks)
अणु
	वापस __clk_bulk_get(dev, num_clks, clks, false);
पूर्ण
EXPORT_SYMBOL(clk_bulk_get);

पूर्णांक __must_check clk_bulk_get_optional(काष्ठा device *dev, पूर्णांक num_clks,
				       काष्ठा clk_bulk_data *clks)
अणु
	वापस __clk_bulk_get(dev, num_clks, clks, true);
पूर्ण
EXPORT_SYMBOL_GPL(clk_bulk_get_optional);

व्योम clk_bulk_put_all(पूर्णांक num_clks, काष्ठा clk_bulk_data *clks)
अणु
	अगर (IS_ERR_OR_शून्य(clks))
		वापस;

	clk_bulk_put(num_clks, clks);

	kमुक्त(clks);
पूर्ण
EXPORT_SYMBOL(clk_bulk_put_all);

पूर्णांक __must_check clk_bulk_get_all(काष्ठा device *dev,
				  काष्ठा clk_bulk_data **clks)
अणु
	काष्ठा device_node *np = dev_of_node(dev);

	अगर (!np)
		वापस 0;

	वापस of_clk_bulk_get_all(np, clks);
पूर्ण
EXPORT_SYMBOL(clk_bulk_get_all);

#अगर_घोषित CONFIG_HAVE_CLK_PREPARE

/**
 * clk_bulk_unprepare - unकरो preparation of a set of घड़ी sources
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table being unprepared
 *
 * clk_bulk_unprepare may sleep, which dअगरferentiates it from clk_bulk_disable.
 * Returns 0 on success, -EERROR otherwise.
 */
व्योम clk_bulk_unprepare(पूर्णांक num_clks, स्थिर काष्ठा clk_bulk_data *clks)
अणु
	जबतक (--num_clks >= 0)
		clk_unprepare(clks[num_clks].clk);
पूर्ण
EXPORT_SYMBOL_GPL(clk_bulk_unprepare);

/**
 * clk_bulk_prepare - prepare a set of घड़ीs
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table being prepared
 *
 * clk_bulk_prepare may sleep, which dअगरferentiates it from clk_bulk_enable.
 * Returns 0 on success, -EERROR otherwise.
 */
पूर्णांक __must_check clk_bulk_prepare(पूर्णांक num_clks,
				  स्थिर काष्ठा clk_bulk_data *clks)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < num_clks; i++) अणु
		ret = clk_prepare(clks[i].clk);
		अगर (ret) अणु
			pr_err("Failed to prepare clk '%s': %d\n",
				clks[i].id, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	clk_bulk_unprepare(i, clks);

	वापस  ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_bulk_prepare);

#पूर्ण_अगर /* CONFIG_HAVE_CLK_PREPARE */

/**
 * clk_bulk_disable - gate a set of घड़ीs
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table being gated
 *
 * clk_bulk_disable must not sleep, which dअगरferentiates it from
 * clk_bulk_unprepare. clk_bulk_disable must be called beक्रमe
 * clk_bulk_unprepare.
 */
व्योम clk_bulk_disable(पूर्णांक num_clks, स्थिर काष्ठा clk_bulk_data *clks)
अणु

	जबतक (--num_clks >= 0)
		clk_disable(clks[num_clks].clk);
पूर्ण
EXPORT_SYMBOL_GPL(clk_bulk_disable);

/**
 * clk_bulk_enable - ungate a set of घड़ीs
 * @num_clks: the number of clk_bulk_data
 * @clks: the clk_bulk_data table being ungated
 *
 * clk_bulk_enable must not sleep
 * Returns 0 on success, -EERROR otherwise.
 */
पूर्णांक __must_check clk_bulk_enable(पूर्णांक num_clks, स्थिर काष्ठा clk_bulk_data *clks)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < num_clks; i++) अणु
		ret = clk_enable(clks[i].clk);
		अगर (ret) अणु
			pr_err("Failed to enable clk '%s': %d\n",
				clks[i].id, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	clk_bulk_disable(i, clks);

	वापस  ret;
पूर्ण
EXPORT_SYMBOL_GPL(clk_bulk_enable);
