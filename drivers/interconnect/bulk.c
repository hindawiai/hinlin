<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>

/**
 * of_icc_bulk_get() - get पूर्णांकerconnect paths
 * @dev: the device requesting the path
 * @num_paths: the number of icc_bulk_data
 * @paths: the table with the paths we want to get
 *
 * Returns 0 on success or negative त्रुटि_सं otherwise.
 */
पूर्णांक __must_check of_icc_bulk_get(काष्ठा device *dev, पूर्णांक num_paths,
				 काष्ठा icc_bulk_data *paths)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < num_paths; i++) अणु
		paths[i].path = of_icc_get(dev, paths[i].name);
		अगर (IS_ERR(paths[i].path)) अणु
			ret = PTR_ERR(paths[i].path);
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "of_icc_get() failed on path %s (%d)\n",
					paths[i].name, ret);
			paths[i].path = शून्य;
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	icc_bulk_put(i, paths);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_icc_bulk_get);

/**
 * icc_bulk_put() - put a list of पूर्णांकerconnect paths
 * @num_paths: the number of icc_bulk_data
 * @paths: the icc_bulk_data table with the paths being put
 */
व्योम icc_bulk_put(पूर्णांक num_paths, काष्ठा icc_bulk_data *paths)
अणु
	जबतक (--num_paths >= 0) अणु
		icc_put(paths[num_paths].path);
		paths[num_paths].path = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(icc_bulk_put);

/**
 * icc_bulk_set_bw() - set bandwidth to a set of paths
 * @num_paths: the number of icc_bulk_data
 * @paths: the icc_bulk_data table containing the paths and bandwidth
 *
 * Returns 0 on success or negative त्रुटि_सं otherwise.
 */
पूर्णांक icc_bulk_set_bw(पूर्णांक num_paths, स्थिर काष्ठा icc_bulk_data *paths)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num_paths; i++) अणु
		ret = icc_set_bw(paths[i].path, paths[i].avg_bw, paths[i].peak_bw);
		अगर (ret) अणु
			pr_err("icc_set_bw() failed on path %s (%d)\n", paths[i].name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(icc_bulk_set_bw);

/**
 * icc_bulk_enable() - enable a previously disabled set of paths
 * @num_paths: the number of icc_bulk_data
 * @paths: the icc_bulk_data table containing the paths and bandwidth
 *
 * Returns 0 on success or negative त्रुटि_सं otherwise.
 */
पूर्णांक icc_bulk_enable(पूर्णांक num_paths, स्थिर काष्ठा icc_bulk_data *paths)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < num_paths; i++) अणु
		ret = icc_enable(paths[i].path);
		अगर (ret) अणु
			pr_err("icc_enable() failed on path %s (%d)\n", paths[i].name, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	icc_bulk_disable(i, paths);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(icc_bulk_enable);

/**
 * icc_bulk_disable() - disable a set of पूर्णांकerconnect paths
 * @num_paths: the number of icc_bulk_data
 * @paths: the icc_bulk_data table containing the paths and bandwidth
 */
व्योम icc_bulk_disable(पूर्णांक num_paths, स्थिर काष्ठा icc_bulk_data *paths)
अणु
	जबतक (--num_paths >= 0)
		icc_disable(paths[num_paths].path);
पूर्ण
EXPORT_SYMBOL_GPL(icc_bulk_disable);
