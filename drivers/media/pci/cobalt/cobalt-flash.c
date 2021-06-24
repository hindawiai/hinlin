<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Cobalt NOR flash functions
 *
 *  Copyright 2012-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/समय.स>

#समावेश "cobalt-flash.h"

#घोषणा ADRS(offset) (COBALT_BUS_FLASH_BASE + offset)

अटल काष्ठा map_info cobalt_flash_map = अणु
	.name =		"cobalt-flash",
	.bankwidth =	2,         /* 16 bits */
	.size =		0x4000000, /* 64MB */
	.phys =		0,         /* offset  */
पूर्ण;

अटल map_word flash_पढ़ो16(काष्ठा map_info *map, अचिन्हित दीर्घ offset)
अणु
	map_word r;

	r.x[0] = cobalt_bus_पढ़ो32(map->virt, ADRS(offset));
	अगर (offset & 0x2)
		r.x[0] >>= 16;
	अन्यथा
		r.x[0] &= 0x0000ffff;

	वापस r;
पूर्ण

अटल व्योम flash_ग_लिखो16(काष्ठा map_info *map, स्थिर map_word datum,
			  अचिन्हित दीर्घ offset)
अणु
	u16 data = (u16)datum.x[0];

	cobalt_bus_ग_लिखो16(map->virt, ADRS(offset), data);
पूर्ण

अटल व्योम flash_copy_from(काष्ठा map_info *map, व्योम *to,
			    अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	u32 src = from;
	u8 *dest = to;
	u32 data;

	जबतक (len) अणु
		data = cobalt_bus_पढ़ो32(map->virt, ADRS(src));
		करो अणु
			*dest = data >> (8 * (src & 3));
			src++;
			dest++;
			len--;
		पूर्ण जबतक (len && (src % 4));
	पूर्ण
पूर्ण

अटल व्योम flash_copy_to(काष्ठा map_info *map, अचिन्हित दीर्घ to,
			  स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	स्थिर u8 *src = from;
	u32 dest = to;

	pr_info("%s: offset 0x%x: length %zu\n", __func__, dest, len);
	जबतक (len) अणु
		u16 data;

		करो अणु
			data = *src << (8 * (dest & 1));
			src++;
			dest++;
			len--;
		पूर्ण जबतक (len && (dest % 2));

		cobalt_bus_ग_लिखो16(map->virt, ADRS(dest - 2), data);
	पूर्ण
पूर्ण

पूर्णांक cobalt_flash_probe(काष्ठा cobalt *cobalt)
अणु
	काष्ठा map_info *map = &cobalt_flash_map;
	काष्ठा mtd_info *mtd;

	BUG_ON(!map_bankwidth_supported(map->bankwidth));
	map->virt = cobalt->bar1;
	map->पढ़ो = flash_पढ़ो16;
	map->ग_लिखो = flash_ग_लिखो16;
	map->copy_from = flash_copy_from;
	map->copy_to = flash_copy_to;

	mtd = करो_map_probe("cfi_probe", map);
	cobalt->mtd = mtd;
	अगर (!mtd) अणु
		cobalt_err("Probe CFI flash failed!\n");
		वापस -1;
	पूर्ण

	mtd->owner = THIS_MODULE;
	mtd->dev.parent = &cobalt->pci_dev->dev;
	mtd_device_रेजिस्टर(mtd, शून्य, 0);
	वापस 0;
पूर्ण

व्योम cobalt_flash_हटाओ(काष्ठा cobalt *cobalt)
अणु
	अगर (cobalt->mtd) अणु
		mtd_device_unरेजिस्टर(cobalt->mtd);
		map_destroy(cobalt->mtd);
	पूर्ण
पूर्ण
