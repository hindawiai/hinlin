<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* drivers/mtd/maps/plat-ram.c
 *
 * (c) 2004-2005 Simtec Electronics
 *	http://www.simtec.co.uk/products/SWLINUX/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Generic platक्रमm device based RAM map
*/

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/plat-ram.h>

#समावेश <यंत्र/पन.स>

/* निजी काष्ठाure क्रम each mtd platक्रमm ram device created */

काष्ठा platram_info अणु
	काष्ठा device		*dev;
	काष्ठा mtd_info		*mtd;
	काष्ठा map_info		 map;
	काष्ठा platdata_mtd_ram	*pdata;
पूर्ण;

/* to_platram_info()
 *
 * device निजी data to काष्ठा platram_info conversion
*/

अटल अंतरभूत काष्ठा platram_info *to_platram_info(काष्ठा platक्रमm_device *dev)
अणु
	वापस platक्रमm_get_drvdata(dev);
पूर्ण

/* platram_setrw
 *
 * call the platक्रमm device's set rw/ro control
 *
 * to = 0 => पढ़ो-only
 *    = 1 => पढ़ो-ग_लिखो
*/

अटल अंतरभूत व्योम platram_setrw(काष्ठा platram_info *info, पूर्णांक to)
अणु
	अगर (info->pdata == शून्य)
		वापस;

	अगर (info->pdata->set_rw != शून्य)
		(info->pdata->set_rw)(info->dev, to);
पूर्ण

/* platram_हटाओ
 *
 * called to हटाओ the device from the driver's control
*/

अटल पूर्णांक platram_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platram_info *info = to_platram_info(pdev);

	dev_dbg(&pdev->dev, "removing device\n");

	अगर (info == शून्य)
		वापस 0;

	अगर (info->mtd) अणु
		mtd_device_unरेजिस्टर(info->mtd);
		map_destroy(info->mtd);
	पूर्ण

	/* ensure ram is left पढ़ो-only */

	platram_setrw(info, PLATRAM_RO);

	kमुक्त(info);

	वापस 0;
पूर्ण

/* platram_probe
 *
 * called from device drive प्रणाली when a device matching our
 * driver is found.
*/

अटल पूर्णांक platram_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platdata_mtd_ram	*pdata;
	काष्ठा platram_info *info;
	काष्ठा resource *res;
	पूर्णांक err = 0;

	dev_dbg(&pdev->dev, "probe entered\n");

	अगर (dev_get_platdata(&pdev->dev) == शून्य) अणु
		dev_err(&pdev->dev, "no platform data supplied\n");
		err = -ENOENT;
		जाओ निकास_error;
	पूर्ण

	pdata = dev_get_platdata(&pdev->dev);

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (info == शून्य) अणु
		err = -ENOMEM;
		जाओ निकास_error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);

	info->dev = &pdev->dev;
	info->pdata = pdata;

	/* get the resource क्रम the memory mapping */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	info->map.virt = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(info->map.virt)) अणु
		err = PTR_ERR(info->map.virt);
		dev_err(&pdev->dev, "failed to ioremap() region\n");
		जाओ निकास_मुक्त;
	पूर्ण

	dev_dbg(&pdev->dev, "got platform resource %p (0x%llx)\n", res,
		(अचिन्हित दीर्घ दीर्घ)res->start);

	/* setup map parameters */

	info->map.phys = res->start;
	info->map.size = resource_size(res);
	info->map.name = pdata->mapname != शून्य ?
			(अक्षर *)pdata->mapname : (अक्षर *)pdev->name;
	info->map.bankwidth = pdata->bankwidth;

	dev_dbg(&pdev->dev, "virt %p, %lu bytes\n", info->map.virt, info->map.size);

	simple_map_init(&info->map);

	dev_dbg(&pdev->dev, "initialised map, probing for mtd\n");

	/* probe क्रम the right mtd map driver
	 * supplied by the platक्रमm_data काष्ठा */

	अगर (pdata->map_probes) अणु
		स्थिर अक्षर * स्थिर *map_probes = pdata->map_probes;

		क्रम ( ; !info->mtd && *map_probes; map_probes++)
			info->mtd = करो_map_probe(*map_probes , &info->map);
	पूर्ण
	/* fallback to map_ram */
	अन्यथा
		info->mtd = करो_map_probe("map_ram", &info->map);

	अगर (info->mtd == शून्य) अणु
		dev_err(&pdev->dev, "failed to probe for map_ram\n");
		err = -ENOMEM;
		जाओ निकास_मुक्त;
	पूर्ण

	info->mtd->dev.parent = &pdev->dev;

	platram_setrw(info, PLATRAM_RW);

	/* check to see अगर there are any available partitions, or whether
	 * to add this device whole */

	err = mtd_device_parse_रेजिस्टर(info->mtd, pdata->probes, शून्य,
					pdata->partitions,
					pdata->nr_partitions);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register mtd device\n");
		जाओ निकास_मुक्त;
	पूर्ण

	dev_info(&pdev->dev, "registered mtd device\n");

	अगर (pdata->nr_partitions) अणु
		/* add the whole device. */
		err = mtd_device_रेजिस्टर(info->mtd, शून्य, 0);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"failed to register the entire device\n");
			जाओ निकास_मुक्त;
		पूर्ण
	पूर्ण

	वापस 0;

 निकास_मुक्त:
	platram_हटाओ(pdev);
 निकास_error:
	वापस err;
पूर्ण

/* device driver info */

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:mtd-ram");

अटल काष्ठा platक्रमm_driver platram_driver = अणु
	.probe		= platram_probe,
	.हटाओ		= platram_हटाओ,
	.driver		= अणु
		.name	= "mtd-ram",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(platram_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("MTD platform RAM map driver");
