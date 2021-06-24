<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/mtd/maps/ixp4xx.c
 *
 * MTD Map file क्रम IXP4XX based प्रणालीs. Please करो not make per-board
 * changes in here. If your board needs special setup, करो it in your
 * platक्रमm level code in arch/arm/mach-ixp4xx/board-setup.c
 *
 * Original Author: Intel Corporation
 * Maपूर्णांकainer: Deepak Saxena <dsaxena@mvista.com>
 *
 * Copyright (C) 2002 Intel Corporation
 * Copyright (C) 2003-2004 MontaVista Software, Inc.
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mach/flash.h>

#समावेश <linux/reboot.h>

/*
 * Read/ग_लिखो a 16 bit word from flash address 'addr'.
 *
 * When the cpu is in little-endian mode it swizzles the address lines
 * ('address coherency') so we need to unकरो the swizzling to ensure commands
 * and the like end up on the correct flash address.
 *
 * To further complicate matters, due to the way the expansion bus controller
 * handles 32 bit पढ़ोs, the byte stream ABCD is stored on the flash as:
 *     D15    D0
 *     +---+---+
 *     | A | B | 0
 *     +---+---+
 *     | C | D | 2
 *     +---+---+
 * This means that on LE प्रणालीs each 16 bit word must be swapped. Note that
 * this requires CONFIG_MTD_CFI_BE_BYTE_SWAP to be enabled to 'unswap' the CFI
 * data and other flash commands which are always in D7-D0.
 */
#अगर_अघोषित __ARMEB__
#अगर_अघोषित CONFIG_MTD_CFI_BE_BYTE_SWAP
#  error CONFIG_MTD_CFI_BE_BYTE_SWAP required
#पूर्ण_अगर

अटल अंतरभूत u16 flash_पढ़ो16(व्योम __iomem *addr)
अणु
	वापस be16_to_cpu(__raw_पढ़ोw((व्योम __iomem *)((अचिन्हित दीर्घ)addr ^ 0x2)));
पूर्ण

अटल अंतरभूत व्योम flash_ग_लिखो16(u16 d, व्योम __iomem *addr)
अणु
	__raw_ग_लिखोw(cpu_to_be16(d), (व्योम __iomem *)((अचिन्हित दीर्घ)addr ^ 0x2));
पूर्ण

#घोषणा	BYTE0(h)	((h) & 0xFF)
#घोषणा	BYTE1(h)	(((h) >> 8) & 0xFF)

#अन्यथा

अटल अंतरभूत u16 flash_पढ़ो16(स्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोw(addr);
पूर्ण

अटल अंतरभूत व्योम flash_ग_लिखो16(u16 d, व्योम __iomem *addr)
अणु
	__raw_ग_लिखोw(d, addr);
पूर्ण

#घोषणा	BYTE0(h)	(((h) >> 8) & 0xFF)
#घोषणा	BYTE1(h)	((h) & 0xFF)
#पूर्ण_अगर

अटल map_word ixp4xx_पढ़ो16(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	map_word val;
	val.x[0] = flash_पढ़ो16(map->virt + ofs);
	वापस val;
पूर्ण

/*
 * The IXP4xx expansion bus only allows 16-bit wide acceses
 * when attached to a 16-bit wide device (such as the 28F128J3A),
 * so we can't just स_नकल_fromio().
 */
अटल व्योम ixp4xx_copy_from(काष्ठा map_info *map, व्योम *to,
			     अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	u8 *dest = (u8 *) to;
	व्योम __iomem *src = map->virt + from;

	अगर (len <= 0)
		वापस;

	अगर (from & 1) अणु
		*dest++ = BYTE1(flash_पढ़ो16(src-1));
		src++;
		--len;
	पूर्ण

	जबतक (len >= 2) अणु
		u16 data = flash_पढ़ो16(src);
		*dest++ = BYTE0(data);
		*dest++ = BYTE1(data);
		src += 2;
		len -= 2;
	पूर्ण

	अगर (len > 0)
		*dest++ = BYTE0(flash_पढ़ो16(src));
पूर्ण

/*
 * Unaligned ग_लिखोs are ignored, causing the 8-bit
 * probe to fail and proceed to the 16-bit probe (which succeeds).
 */
अटल व्योम ixp4xx_probe_ग_लिखो16(काष्ठा map_info *map, map_word d, अचिन्हित दीर्घ adr)
अणु
	अगर (!(adr & 1))
		flash_ग_लिखो16(d.x[0], map->virt + adr);
पूर्ण

/*
 * Fast ग_लिखो16 function without the probing check above
 */
अटल व्योम ixp4xx_ग_लिखो16(काष्ठा map_info *map, map_word d, अचिन्हित दीर्घ adr)
अणु
	flash_ग_लिखो16(d.x[0], map->virt + adr);
पूर्ण

काष्ठा ixp4xx_flash_info अणु
	काष्ठा mtd_info *mtd;
	काष्ठा map_info map;
	काष्ठा resource *res;
पूर्ण;

अटल स्थिर अक्षर * स्थिर probes[] = अणु "RedBoot", "cmdlinepart", शून्य पूर्ण;

अटल पूर्णांक ixp4xx_flash_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा flash_platक्रमm_data *plat = dev_get_platdata(&dev->dev);
	काष्ठा ixp4xx_flash_info *info = platक्रमm_get_drvdata(dev);

	अगर(!info)
		वापस 0;

	अगर (info->mtd) अणु
		mtd_device_unरेजिस्टर(info->mtd);
		map_destroy(info->mtd);
	पूर्ण

	अगर (plat->निकास)
		plat->निकास();

	वापस 0;
पूर्ण

अटल पूर्णांक ixp4xx_flash_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा flash_platक्रमm_data *plat = dev_get_platdata(&dev->dev);
	काष्ठा ixp4xx_flash_info *info;
	काष्ठा mtd_part_parser_data ppdata = अणु
		.origin = dev->resource->start,
	पूर्ण;
	पूर्णांक err = -1;

	अगर (!plat)
		वापस -ENODEV;

	अगर (plat->init) अणु
		err = plat->init();
		अगर (err)
			वापस err;
	पूर्ण

	info = devm_kzalloc(&dev->dev, माप(काष्ठा ixp4xx_flash_info),
			    GFP_KERNEL);
	अगर(!info) अणु
		err = -ENOMEM;
		जाओ Error;
	पूर्ण

	platक्रमm_set_drvdata(dev, info);

	/*
	 * Tell the MTD layer we're not 1:1 mapped so that it करोes
	 * not attempt to करो a direct access on us.
	 */
	info->map.phys = NO_XIP;
	info->map.size = resource_size(dev->resource);

	/*
	 * We only support 16-bit accesses क्रम now. If and when
	 * any board use 8-bit access, we'll fixup the driver to
	 * handle that.
	 */
	info->map.bankwidth = 2;
	info->map.name = dev_name(&dev->dev);
	info->map.पढ़ो = ixp4xx_पढ़ो16;
	info->map.ग_लिखो = ixp4xx_probe_ग_लिखो16;
	info->map.copy_from = ixp4xx_copy_from;

	info->map.virt = devm_ioremap_resource(&dev->dev, dev->resource);
	अगर (IS_ERR(info->map.virt)) अणु
		err = PTR_ERR(info->map.virt);
		जाओ Error;
	पूर्ण

	info->mtd = करो_map_probe(plat->map_name, &info->map);
	अगर (!info->mtd) अणु
		prपूर्णांकk(KERN_ERR "IXP4XXFlash: map_probe failed\n");
		err = -ENXIO;
		जाओ Error;
	पूर्ण
	info->mtd->dev.parent = &dev->dev;

	/* Use the fast version */
	info->map.ग_लिखो = ixp4xx_ग_लिखो16;

	err = mtd_device_parse_रेजिस्टर(info->mtd, probes, &ppdata,
			plat->parts, plat->nr_parts);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Could not parse partitions\n");
		जाओ Error;
	पूर्ण

	वापस 0;

Error:
	ixp4xx_flash_हटाओ(dev);
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver ixp4xx_flash_driver = अणु
	.probe		= ixp4xx_flash_probe,
	.हटाओ		= ixp4xx_flash_हटाओ,
	.driver		= अणु
		.name	= "IXP4XX-Flash",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ixp4xx_flash_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MTD map driver for Intel IXP4xx systems");
MODULE_AUTHOR("Deepak Saxena");
MODULE_ALIAS("platform:IXP4XX-Flash");
