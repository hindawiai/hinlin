<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel IXP4xx OF physmap add-on
 * Copyright (C) 2019 Linus Walleij <linus.walleij@linaro.org>
 *
 * Based on the ixp4xx.c map driver, originally written by:
 * Intel Corporation
 * Deepak Saxena <dsaxena@mvista.com>
 * Copyright (C) 2002 Intel Corporation
 * Copyright (C) 2003-2004 MontaVista Software, Inc.
 */
#समावेश <linux/export.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/xip.h>
#समावेश "physmap-ixp4xx.h"

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
#अगर_अघोषित CONFIG_CPU_BIG_ENDIAN

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

अटल व्योम ixp4xx_ग_लिखो16(काष्ठा map_info *map, map_word d, अचिन्हित दीर्घ adr)
अणु
	flash_ग_लिखो16(d.x[0], map->virt + adr);
पूर्ण

पूर्णांक of_flash_probe_ixp4xx(काष्ठा platक्रमm_device *pdev,
			  काष्ठा device_node *np,
			  काष्ठा map_info *map)
अणु
	काष्ठा device *dev = &pdev->dev;

	/* Multiplatक्रमm guard */
	अगर (!of_device_is_compatible(np, "intel,ixp4xx-flash"))
		वापस 0;

	map->पढ़ो = ixp4xx_पढ़ो16;
	map->ग_लिखो = ixp4xx_ग_लिखो16;
	map->copy_from = ixp4xx_copy_from;
	map->copy_to = शून्य;

	dev_info(dev, "initialized Intel IXP4xx-specific physmap control\n");

	वापस 0;
पूर्ण
