<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com/
// Author: Vignesh Raghavendra <vigneshr@ti.com>

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/hyperbus.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/of.h>
#समावेश <linux/types.h>

अटल काष्ठा hyperbus_device *map_to_hbdev(काष्ठा map_info *map)
अणु
	वापस container_of(map, काष्ठा hyperbus_device, map);
पूर्ण

अटल map_word hyperbus_पढ़ो16(काष्ठा map_info *map, अचिन्हित दीर्घ addr)
अणु
	काष्ठा hyperbus_device *hbdev = map_to_hbdev(map);
	काष्ठा hyperbus_ctlr *ctlr = hbdev->ctlr;
	map_word पढ़ो_data;

	पढ़ो_data.x[0] = ctlr->ops->पढ़ो16(hbdev, addr);

	वापस पढ़ो_data;
पूर्ण

अटल व्योम hyperbus_ग_लिखो16(काष्ठा map_info *map, map_word d,
			     अचिन्हित दीर्घ addr)
अणु
	काष्ठा hyperbus_device *hbdev = map_to_hbdev(map);
	काष्ठा hyperbus_ctlr *ctlr = hbdev->ctlr;

	ctlr->ops->ग_लिखो16(hbdev, addr, d.x[0]);
पूर्ण

अटल व्योम hyperbus_copy_from(काष्ठा map_info *map, व्योम *to,
			       अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	काष्ठा hyperbus_device *hbdev = map_to_hbdev(map);
	काष्ठा hyperbus_ctlr *ctlr = hbdev->ctlr;

	ctlr->ops->copy_from(hbdev, to, from, len);
पूर्ण

अटल व्योम hyperbus_copy_to(काष्ठा map_info *map, अचिन्हित दीर्घ to,
			     स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	काष्ठा hyperbus_device *hbdev = map_to_hbdev(map);
	काष्ठा hyperbus_ctlr *ctlr = hbdev->ctlr;

	ctlr->ops->copy_to(hbdev, to, from, len);
पूर्ण

पूर्णांक hyperbus_रेजिस्टर_device(काष्ठा hyperbus_device *hbdev)
अणु
	स्थिर काष्ठा hyperbus_ops *ops;
	काष्ठा hyperbus_ctlr *ctlr;
	काष्ठा device_node *np;
	काष्ठा map_info *map;
	काष्ठा device *dev;
	पूर्णांक ret;

	अगर (!hbdev || !hbdev->np || !hbdev->ctlr || !hbdev->ctlr->dev) अणु
		pr_err("hyperbus: please fill all the necessary fields!\n");
		वापस -EINVAL;
	पूर्ण

	np = hbdev->np;
	ctlr = hbdev->ctlr;
	अगर (!of_device_is_compatible(np, "cypress,hyperflash")) अणु
		dev_err(ctlr->dev, "\"cypress,hyperflash\" compatible missing\n");
		वापस -ENODEV;
	पूर्ण

	hbdev->memtype = HYPERFLASH;

	dev = ctlr->dev;
	map = &hbdev->map;
	map->name = dev_name(dev);
	map->bankwidth = 2;
	map->device_node = np;

	simple_map_init(map);
	ops = ctlr->ops;
	अगर (ops) अणु
		अगर (ops->पढ़ो16)
			map->पढ़ो = hyperbus_पढ़ो16;
		अगर (ops->ग_लिखो16)
			map->ग_लिखो = hyperbus_ग_लिखो16;
		अगर (ops->copy_to)
			map->copy_to = hyperbus_copy_to;
		अगर (ops->copy_from)
			map->copy_from = hyperbus_copy_from;

		अगर (ops->calibrate && !ctlr->calibrated) अणु
			ret = ops->calibrate(hbdev);
			अगर (!ret) अणु
				dev_err(dev, "Calibration failed\n");
				वापस -ENODEV;
			पूर्ण
			ctlr->calibrated = true;
		पूर्ण
	पूर्ण

	hbdev->mtd = करो_map_probe("cfi_probe", map);
	अगर (!hbdev->mtd) अणु
		dev_err(dev, "probing of hyperbus device failed\n");
		वापस -ENODEV;
	पूर्ण

	hbdev->mtd->dev.parent = dev;
	mtd_set_of_node(hbdev->mtd, np);

	ret = mtd_device_रेजिस्टर(hbdev->mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "failed to register mtd device\n");
		map_destroy(hbdev->mtd);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hyperbus_रेजिस्टर_device);

पूर्णांक hyperbus_unरेजिस्टर_device(काष्ठा hyperbus_device *hbdev)
अणु
	पूर्णांक ret = 0;

	अगर (hbdev && hbdev->mtd) अणु
		ret = mtd_device_unरेजिस्टर(hbdev->mtd);
		map_destroy(hbdev->mtd);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hyperbus_unरेजिस्टर_device);

MODULE_DESCRIPTION("HyperBus Framework");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Vignesh Raghavendra <vigneshr@ti.com>");
