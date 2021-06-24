<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Normal mappings of chips in physical memory
 *
 * Copyright (C) 2003 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 *
 * 031022 - [jsun] add run-समय configure and partition setup
 *
 * Device tree support:
 *    Copyright (C) 2006 MontaVista Software Inc.
 *    Author: Vitaly Wool <vwool@ru.mvista.com>
 *
 *    Revised to handle newer style flash binding by:
 *    Copyright (C) 2007 David Gibson, IBM Corporation.
 *
 * GPIO address extension:
 *    Handle the हाल where a flash device is mostly addressed using physical
 *    line and supplemented by GPIOs.  This way you can hook up say a 8MiB flash
 *    to a 2MiB memory range and use the GPIOs to select a particular range.
 *
 *    Copyright तऊ 2000 Nicolas Pitre <nico@cam.org>
 *    Copyright तऊ 2005-2009 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/concat.h>
#समावेश <linux/mtd/cfi_endian.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/gpio/consumer.h>

#समावेश "physmap-bt1-rom.h"
#समावेश "physmap-gemini.h"
#समावेश "physmap-ixp4xx.h"
#समावेश "physmap-versatile.h"

काष्ठा physmap_flash_info अणु
	अचिन्हित पूर्णांक		nmaps;
	काष्ठा mtd_info		**mtds;
	काष्ठा mtd_info		*cmtd;
	काष्ठा map_info		*maps;
	spinlock_t		vpp_lock;
	पूर्णांक			vpp_refcnt;
	स्थिर अक्षर		*probe_type;
	स्थिर अक्षर * स्थिर	*part_types;
	अचिन्हित पूर्णांक		nparts;
	स्थिर काष्ठा mtd_partition *parts;
	काष्ठा gpio_descs	*gpios;
	अचिन्हित पूर्णांक		gpio_values;
	अचिन्हित पूर्णांक		win_order;
पूर्ण;

अटल पूर्णांक physmap_flash_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा physmap_flash_info *info;
	काष्ठा physmap_flash_data *physmap_data;
	पूर्णांक i, err = 0;

	info = platक्रमm_get_drvdata(dev);
	अगर (!info) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (info->cmtd) अणु
		err = mtd_device_unरेजिस्टर(info->cmtd);
		अगर (err)
			जाओ out;

		अगर (info->cmtd != info->mtds[0])
			mtd_concat_destroy(info->cmtd);
	पूर्ण

	क्रम (i = 0; i < info->nmaps; i++) अणु
		अगर (info->mtds[i])
			map_destroy(info->mtds[i]);
	पूर्ण

	physmap_data = dev_get_platdata(&dev->dev);
	अगर (physmap_data && physmap_data->निकास)
		physmap_data->निकास(dev);

out:
	pm_runसमय_put(&dev->dev);
	pm_runसमय_disable(&dev->dev);
	वापस err;
पूर्ण

अटल व्योम physmap_set_vpp(काष्ठा map_info *map, पूर्णांक state)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा physmap_flash_data *physmap_data;
	काष्ठा physmap_flash_info *info;
	अचिन्हित दीर्घ flags;

	pdev = (काष्ठा platक्रमm_device *)map->map_priv_1;
	physmap_data = dev_get_platdata(&pdev->dev);

	अगर (!physmap_data->set_vpp)
		वापस;

	info = platक्रमm_get_drvdata(pdev);

	spin_lock_irqsave(&info->vpp_lock, flags);
	अगर (state) अणु
		अगर (++info->vpp_refcnt == 1)    /* first nested 'on' */
			physmap_data->set_vpp(pdev, 1);
	पूर्ण अन्यथा अणु
		अगर (--info->vpp_refcnt == 0)    /* last nested 'off' */
			physmap_data->set_vpp(pdev, 0);
	पूर्ण
	spin_unlock_irqrestore(&info->vpp_lock, flags);
पूर्ण

#अगर IS_ENABLED(CONFIG_MTD_PHYSMAP_GPIO_ADDR)
अटल व्योम physmap_set_addr_gpios(काष्ठा physmap_flash_info *info,
				   अचिन्हित दीर्घ ofs)
अणु
	अचिन्हित पूर्णांक i;

	ofs >>= info->win_order;
	अगर (info->gpio_values == ofs)
		वापस;

	क्रम (i = 0; i < info->gpios->ndescs; i++) अणु
		अगर ((BIT(i) & ofs) == (BIT(i) & info->gpio_values))
			जारी;

		gpiod_set_value(info->gpios->desc[i], !!(BIT(i) & ofs));
	पूर्ण

	info->gpio_values = ofs;
पूर्ण

#घोषणा win_mask(order)		(BIT(order) - 1)

अटल map_word physmap_addr_gpios_पढ़ो(काष्ठा map_info *map,
					अचिन्हित दीर्घ ofs)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा physmap_flash_info *info;
	map_word mw;
	u16 word;

	pdev = (काष्ठा platक्रमm_device *)map->map_priv_1;
	info = platक्रमm_get_drvdata(pdev);
	physmap_set_addr_gpios(info, ofs);

	word = पढ़ोw(map->virt + (ofs & win_mask(info->win_order)));
	mw.x[0] = word;
	वापस mw;
पूर्ण

अटल व्योम physmap_addr_gpios_copy_from(काष्ठा map_info *map, व्योम *buf,
					 अचिन्हित दीर्घ ofs, sमाप_प्रकार len)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा physmap_flash_info *info;

	pdev = (काष्ठा platक्रमm_device *)map->map_priv_1;
	info = platक्रमm_get_drvdata(pdev);

	जबतक (len) अणु
		अचिन्हित पूर्णांक winofs = ofs & win_mask(info->win_order);
		अचिन्हित पूर्णांक chunklen = min_t(अचिन्हित पूर्णांक, len,
					      BIT(info->win_order) - winofs);

		physmap_set_addr_gpios(info, ofs);
		स_नकल_fromio(buf, map->virt + winofs, chunklen);
		len -= chunklen;
		buf += chunklen;
		ofs += chunklen;
	पूर्ण
पूर्ण

अटल व्योम physmap_addr_gpios_ग_लिखो(काष्ठा map_info *map, map_word mw,
				     अचिन्हित दीर्घ ofs)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा physmap_flash_info *info;
	u16 word;

	pdev = (काष्ठा platक्रमm_device *)map->map_priv_1;
	info = platक्रमm_get_drvdata(pdev);
	physmap_set_addr_gpios(info, ofs);

	word = mw.x[0];
	ग_लिखोw(word, map->virt + (ofs & win_mask(info->win_order)));
पूर्ण

अटल व्योम physmap_addr_gpios_copy_to(काष्ठा map_info *map, अचिन्हित दीर्घ ofs,
				       स्थिर व्योम *buf, sमाप_प्रकार len)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा physmap_flash_info *info;

	pdev = (काष्ठा platक्रमm_device *)map->map_priv_1;
	info = platक्रमm_get_drvdata(pdev);

	जबतक (len) अणु
		अचिन्हित पूर्णांक winofs = ofs & win_mask(info->win_order);
		अचिन्हित पूर्णांक chunklen = min_t(अचिन्हित पूर्णांक, len,
					      BIT(info->win_order) - winofs);

		physmap_set_addr_gpios(info, ofs);
		स_नकल_toio(map->virt + winofs, buf, chunklen);
		len -= chunklen;
		buf += chunklen;
		ofs += chunklen;
	पूर्ण
पूर्ण

अटल पूर्णांक physmap_addr_gpios_map_init(काष्ठा map_info *map)
अणु
	map->phys = NO_XIP;
	map->पढ़ो = physmap_addr_gpios_पढ़ो;
	map->copy_from = physmap_addr_gpios_copy_from;
	map->ग_लिखो = physmap_addr_gpios_ग_लिखो;
	map->copy_to = physmap_addr_gpios_copy_to;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक physmap_addr_gpios_map_init(काष्ठा map_info *map)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MTD_PHYSMAP_OF)
अटल स्थिर काष्ठा of_device_id of_flash_match[] = अणु
	अणु
		.compatible = "cfi-flash",
		.data = "cfi_probe",
	पूर्ण,
	अणु
		/*
		 * FIXME: JEDEC chips can't be safely and reliably
		 * probed, although the mtd code माला_लो it right in
		 * practice most of the समय.  We should use the
		 * venकरोr and device ids specअगरied by the binding to
		 * bypass the heuristic probe code, but the mtd layer
		 * provides, at present, no पूर्णांकerface क्रम करोing so
		 * :(.
		 */
		.compatible = "jedec-flash",
		.data = "jedec_probe",
	पूर्ण,
	अणु
		.compatible = "mtd-ram",
		.data = "map_ram",
	पूर्ण,
	अणु
		.compatible = "mtd-rom",
		.data = "map_rom",
	पूर्ण,
	अणु
		.type = "rom",
		.compatible = "direct-mapped"
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_flash_match);

अटल स्थिर अक्षर * स्थिर of_शेष_part_probes[] = अणु
	"cmdlinepart", "RedBoot", "ofpart", "ofoldpart", शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर *of_get_part_probes(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा device_node *dp = dev->dev.of_node;
	स्थिर अक्षर **res;
	पूर्णांक count;

	count = of_property_count_strings(dp, "linux,part-probe");
	अगर (count < 0)
		वापस of_शेष_part_probes;

	res = devm_kसुस्मृति(&dev->dev, count + 1, माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस शून्य;

	count = of_property_पढ़ो_string_array(dp, "linux,part-probe", res,
					      count);
	अगर (count < 0)
		वापस शून्य;

	वापस res;
पूर्ण

अटल स्थिर अक्षर *of_select_probe_type(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा device_node *dp = dev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	स्थिर अक्षर *probe_type;

	match = of_match_device(of_flash_match, &dev->dev);
	probe_type = match->data;
	अगर (probe_type)
		वापस probe_type;

	dev_warn(&dev->dev,
		 "Device tree uses obsolete \"direct-mapped\" flash binding\n");

	of_property_पढ़ो_string(dp, "probe-type", &probe_type);
	अगर (!probe_type)
		वापस शून्य;

	अगर (!म_भेद(probe_type, "CFI")) अणु
		probe_type = "cfi_probe";
	पूर्ण अन्यथा अगर (!म_भेद(probe_type, "JEDEC")) अणु
		probe_type = "jedec_probe";
	पूर्ण अन्यथा अगर (!म_भेद(probe_type, "ROM")) अणु
		probe_type = "map_rom";
	पूर्ण अन्यथा अणु
		dev_warn(&dev->dev,
			 "obsolete_probe: don't know probe type '%s', mapping as rom\n",
			 probe_type);
		probe_type = "map_rom";
	पूर्ण

	वापस probe_type;
पूर्ण

अटल पूर्णांक physmap_flash_of_init(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा physmap_flash_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा device_node *dp = dev->dev.of_node;
	स्थिर अक्षर *mtd_name = शून्य;
	पूर्णांक err, swap = 0;
	bool map_indirect;
	अचिन्हित पूर्णांक i;
	u32 bankwidth;

	अगर (!dp)
		वापस -EINVAL;

	info->probe_type = of_select_probe_type(dev);

	info->part_types = of_get_part_probes(dev);
	अगर (!info->part_types)
		वापस -ENOMEM;

	of_property_पढ़ो_string(dp, "linux,mtd-name", &mtd_name);

	map_indirect = of_property_पढ़ो_bool(dp, "no-unaligned-direct-access");

	err = of_property_पढ़ो_u32(dp, "bank-width", &bankwidth);
	अगर (err) अणु
		dev_err(&dev->dev, "Can't get bank width from device tree\n");
		वापस err;
	पूर्ण

	अगर (of_property_पढ़ो_bool(dp, "big-endian"))
		swap = CFI_BIG_ENDIAN;
	अन्यथा अगर (of_property_पढ़ो_bool(dp, "little-endian"))
		swap = CFI_LITTLE_ENDIAN;

	क्रम (i = 0; i < info->nmaps; i++) अणु
		info->maps[i].name = mtd_name;
		info->maps[i].swap = swap;
		info->maps[i].bankwidth = bankwidth;
		info->maps[i].device_node = dp;

		err = of_flash_probe_bt1_rom(dev, dp, &info->maps[i]);
		अगर (err)
			वापस err;

		err = of_flash_probe_gemini(dev, dp, &info->maps[i]);
		अगर (err)
			वापस err;

		err = of_flash_probe_ixp4xx(dev, dp, &info->maps[i]);
		अगर (err)
			वापस err;

		err = of_flash_probe_versatile(dev, dp, &info->maps[i]);
		अगर (err)
			वापस err;

		/*
		 * On some platक्रमms (e.g. MPC5200) a direct 1:1 mapping
		 * may cause problems with JFFS2 usage, as the local bus (LPB)
		 * करोesn't support unaligned accesses as implemented in the
		 * JFFS2 code via स_नकल(). By setting NO_XIP, the
		 * flash will not be exposed directly to the MTD users
		 * (e.g. JFFS2) any more.
		 */
		अगर (map_indirect)
			info->maps[i].phys = NO_XIP;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा /* IS_ENABLED(CONFIG_MTD_PHYSMAP_OF) */
#घोषणा of_flash_match शून्य

अटल पूर्णांक physmap_flash_of_init(काष्ठा platक्रमm_device *dev)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_MTD_PHYSMAP_OF) */

अटल स्थिर अक्षर * स्थिर rom_probe_types[] = अणु
	"cfi_probe", "jedec_probe", "qinfo_probe", "map_rom",
पूर्ण;

अटल स्थिर अक्षर * स्थिर part_probe_types[] = अणु
	"cmdlinepart", "RedBoot", "afs", शून्य
पूर्ण;

अटल पूर्णांक physmap_flash_pdata_init(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा physmap_flash_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा physmap_flash_data *physmap_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	physmap_data = dev_get_platdata(&dev->dev);
	अगर (!physmap_data)
		वापस -EINVAL;

	info->probe_type = physmap_data->probe_type;
	info->part_types = physmap_data->part_probe_types ? : part_probe_types;
	info->parts = physmap_data->parts;
	info->nparts = physmap_data->nr_parts;

	अगर (physmap_data->init) अणु
		err = physmap_data->init(dev);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < info->nmaps; i++) अणु
		info->maps[i].bankwidth = physmap_data->width;
		info->maps[i].pfow_base = physmap_data->pfow_base;
		info->maps[i].set_vpp = physmap_set_vpp;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक physmap_flash_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा physmap_flash_info *info;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (!dev->dev.of_node && !dev_get_platdata(&dev->dev))
		वापस -EINVAL;

	info = devm_kzalloc(&dev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	जबतक (platक्रमm_get_resource(dev, IORESOURCE_MEM, info->nmaps))
		info->nmaps++;

	अगर (!info->nmaps)
		वापस -ENODEV;

	info->maps = devm_kzalloc(&dev->dev,
				  माप(*info->maps) * info->nmaps,
				  GFP_KERNEL);
	अगर (!info->maps)
		वापस -ENOMEM;

	info->mtds = devm_kzalloc(&dev->dev,
				  माप(*info->mtds) * info->nmaps,
				  GFP_KERNEL);
	अगर (!info->mtds)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(dev, info);

	info->gpios = devm_gpiod_get_array_optional(&dev->dev, "addr",
						    GPIOD_OUT_LOW);
	अगर (IS_ERR(info->gpios))
		वापस PTR_ERR(info->gpios);

	अगर (info->gpios && info->nmaps > 1) अणु
		dev_err(&dev->dev, "addr-gpios only supported for nmaps == 1\n");
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_enable(&dev->dev);
	pm_runसमय_get_sync(&dev->dev);

	अगर (dev->dev.of_node)
		err = physmap_flash_of_init(dev);
	अन्यथा
		err = physmap_flash_pdata_init(dev);

	अगर (err) अणु
		pm_runसमय_put(&dev->dev);
		pm_runसमय_disable(&dev->dev);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < info->nmaps; i++) अणु
		काष्ठा resource *res;

		res = platक्रमm_get_resource(dev, IORESOURCE_MEM, i);
		info->maps[i].virt = devm_ioremap_resource(&dev->dev, res);
		अगर (IS_ERR(info->maps[i].virt)) अणु
			err = PTR_ERR(info->maps[i].virt);
			जाओ err_out;
		पूर्ण

		dev_notice(&dev->dev, "physmap platform flash device: %pR\n",
			   res);

		अगर (!info->maps[i].name)
			info->maps[i].name = dev_name(&dev->dev);

		अगर (!info->maps[i].phys)
			info->maps[i].phys = res->start;

		info->win_order = get_biपंचांगask_order(resource_size(res)) - 1;
		info->maps[i].size = BIT(info->win_order +
					 (info->gpios ?
					  info->gpios->ndescs : 0));

		info->maps[i].map_priv_1 = (अचिन्हित दीर्घ)dev;

		अगर (info->gpios) अणु
			err = physmap_addr_gpios_map_init(&info->maps[i]);
			अगर (err)
				जाओ err_out;
		पूर्ण

#अगर_घोषित CONFIG_MTD_COMPLEX_MAPPINGS
		/*
		 * Only use the simple_map implementation अगर map hooks are not
		 * implemented. Since map->पढ़ो() is mandatory checking क्रम its
		 * presence is enough.
		 */
		अगर (!info->maps[i].पढ़ो)
			simple_map_init(&info->maps[i]);
#अन्यथा
		simple_map_init(&info->maps[i]);
#पूर्ण_अगर

		अगर (info->probe_type) अणु
			info->mtds[i] = करो_map_probe(info->probe_type,
						     &info->maps[i]);
		पूर्ण अन्यथा अणु
			पूर्णांक j;

			क्रम (j = 0; j < ARRAY_SIZE(rom_probe_types); j++) अणु
				info->mtds[i] = करो_map_probe(rom_probe_types[j],
							     &info->maps[i]);
				अगर (info->mtds[i])
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (!info->mtds[i]) अणु
			dev_err(&dev->dev, "map_probe failed\n");
			err = -ENXIO;
			जाओ err_out;
		पूर्ण
		info->mtds[i]->dev.parent = &dev->dev;
	पूर्ण

	अगर (info->nmaps == 1) अणु
		info->cmtd = info->mtds[0];
	पूर्ण अन्यथा अणु
		/*
		 * We detected multiple devices. Concatenate them together.
		 */
		info->cmtd = mtd_concat_create(info->mtds, info->nmaps,
					       dev_name(&dev->dev));
		अगर (!info->cmtd)
			err = -ENXIO;
	पूर्ण
	अगर (err)
		जाओ err_out;

	spin_lock_init(&info->vpp_lock);

	mtd_set_of_node(info->cmtd, dev->dev.of_node);
	err = mtd_device_parse_रेजिस्टर(info->cmtd, info->part_types, शून्य,
					info->parts, info->nparts);
	अगर (err)
		जाओ err_out;

	वापस 0;

err_out:
	physmap_flash_हटाओ(dev);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम physmap_flash_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा physmap_flash_info *info = platक्रमm_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < info->nmaps && info->mtds[i]; i++)
		अगर (mtd_suspend(info->mtds[i]) == 0)
			mtd_resume(info->mtds[i]);
पूर्ण
#अन्यथा
#घोषणा physmap_flash_shutकरोwn शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver physmap_flash_driver = अणु
	.probe		= physmap_flash_probe,
	.हटाओ		= physmap_flash_हटाओ,
	.shutकरोwn	= physmap_flash_shutकरोwn,
	.driver		= अणु
		.name	= "physmap-flash",
		.of_match_table = of_flash_match,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_MTD_PHYSMAP_COMPAT
अटल काष्ठा physmap_flash_data physmap_flash_data = अणु
	.width		= CONFIG_MTD_PHYSMAP_BANKWIDTH,
पूर्ण;

अटल काष्ठा resource physmap_flash_resource = अणु
	.start		= CONFIG_MTD_PHYSMAP_START,
	.end		= CONFIG_MTD_PHYSMAP_START + CONFIG_MTD_PHYSMAP_LEN - 1,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device physmap_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &physmap_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &physmap_flash_resource,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init physmap_init(व्योम)
अणु
	पूर्णांक err;

	err = platक्रमm_driver_रेजिस्टर(&physmap_flash_driver);
#अगर_घोषित CONFIG_MTD_PHYSMAP_COMPAT
	अगर (err == 0) अणु
		err = platक्रमm_device_रेजिस्टर(&physmap_flash);
		अगर (err)
			platक्रमm_driver_unरेजिस्टर(&physmap_flash_driver);
	पूर्ण
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल व्योम __निकास physmap_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_MTD_PHYSMAP_COMPAT
	platक्रमm_device_unरेजिस्टर(&physmap_flash);
#पूर्ण_अगर
	platक्रमm_driver_unरेजिस्टर(&physmap_flash_driver);
पूर्ण

module_init(physmap_init);
module_निकास(physmap_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_AUTHOR("Vitaly Wool <vwool@ru.mvista.com>");
MODULE_AUTHOR("Mike Frysinger <vapier@gentoo.org>");
MODULE_DESCRIPTION("Generic configurable MTD map driver");

/* legacy platक्रमm drivers can't hotplug or coldplg */
#अगर_अघोषित CONFIG_MTD_PHYSMAP_COMPAT
/* work with hotplug and coldplug */
MODULE_ALIAS("platform:physmap-flash");
#पूर्ण_अगर
