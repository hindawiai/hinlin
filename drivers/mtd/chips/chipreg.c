<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Registration क्रम chip drivers
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/mtd.h>

अटल DEFINE_SPINLOCK(chip_drvs_lock);
अटल LIST_HEAD(chip_drvs_list);

व्योम रेजिस्टर_mtd_chip_driver(काष्ठा mtd_chip_driver *drv)
अणु
	spin_lock(&chip_drvs_lock);
	list_add(&drv->list, &chip_drvs_list);
	spin_unlock(&chip_drvs_lock);
पूर्ण

व्योम unरेजिस्टर_mtd_chip_driver(काष्ठा mtd_chip_driver *drv)
अणु
	spin_lock(&chip_drvs_lock);
	list_del(&drv->list);
	spin_unlock(&chip_drvs_lock);
पूर्ण

अटल काष्ठा mtd_chip_driver *get_mtd_chip_driver (स्थिर अक्षर *name)
अणु
	काष्ठा list_head *pos;
	काष्ठा mtd_chip_driver *ret = शून्य, *this;

	spin_lock(&chip_drvs_lock);

	list_क्रम_each(pos, &chip_drvs_list) अणु
		this = list_entry(pos, typeof(*this), list);

		अगर (!म_भेद(this->name, name)) अणु
			ret = this;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret && !try_module_get(ret->module))
		ret = शून्य;

	spin_unlock(&chip_drvs_lock);

	वापस ret;
पूर्ण

	/* Hide all the horrid details, like some silly person taking
	   get_module_symbol() away from us, from the caller. */

काष्ठा mtd_info *करो_map_probe(स्थिर अक्षर *name, काष्ठा map_info *map)
अणु
	काष्ठा mtd_chip_driver *drv;
	काष्ठा mtd_info *ret;

	drv = get_mtd_chip_driver(name);

	अगर (!drv && !request_module("%s", name))
		drv = get_mtd_chip_driver(name);

	अगर (!drv)
		वापस शून्य;

	ret = drv->probe(map);

	/* We decrease the use count here. It may have been a
	   probe-only module, which is no दीर्घer required from this
	   poपूर्णांक, having given us a handle on (and increased the use
	   count of) the actual driver code.
	*/
	module_put(drv->module);

	वापस ret;
पूर्ण
/*
 * Destroy an MTD device which was created क्रम a map device.
 * Make sure the MTD device is alपढ़ोy unरेजिस्टरed beक्रमe calling this
 */
व्योम map_destroy(काष्ठा mtd_info *mtd)
अणु
	काष्ठा map_info *map = mtd->priv;

	अगर (map->fldrv->destroy)
		map->fldrv->destroy(mtd);

	module_put(map->fldrv->module);

	kमुक्त(mtd);
पूर्ण

EXPORT_SYMBOL(रेजिस्टर_mtd_chip_driver);
EXPORT_SYMBOL(unरेजिस्टर_mtd_chip_driver);
EXPORT_SYMBOL(करो_map_probe);
EXPORT_SYMBOL(map_destroy);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("Core routines for registering and invoking MTD chip drivers");
