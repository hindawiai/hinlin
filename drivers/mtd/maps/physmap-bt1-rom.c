<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Authors:
 *   Serge Semin <Sergey.Semin@baikalelectronics.ru>
 *
 * Baikal-T1 Physically Mapped Internal ROM driver
 */
#समावेश <linux/bits.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/xip.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश "physmap-bt1-rom.h"

/*
 * Baikal-T1 SoC ROMs are only accessible by the dword-aligned inकाष्ठाions.
 * We have to take this पूर्णांकo account when implementing the data पढ़ो-methods.
 * Note there is no need in bothering with endianness, since both Baikal-T1
 * CPU and MMIO are LE.
 */
अटल map_word __xipram bt1_rom_map_पढ़ो(काष्ठा map_info *map,
					  अचिन्हित दीर्घ ofs)
अणु
	व्योम __iomem *src = map->virt + ofs;
	अचिन्हित पूर्णांक shअगरt;
	map_word ret;
	u32 data;

	/* Read data within offset dword. */
	shअगरt = (uपूर्णांकptr_t)src & 0x3;
	data = पढ़ोl_relaxed(src - shअगरt);
	अगर (!shअगरt) अणु
		ret.x[0] = data;
		वापस ret;
	पूर्ण
	ret.x[0] = data >> (shअगरt * BITS_PER_BYTE);

	/* Read data from the next dword. */
	shअगरt = 4 - shअगरt;
	अगर (ofs + shअगरt >= map->size)
		वापस ret;

	data = पढ़ोl_relaxed(src + shअगरt);
	ret.x[0] |= data << (shअगरt * BITS_PER_BYTE);

	वापस ret;
पूर्ण

अटल व्योम __xipram bt1_rom_map_copy_from(काष्ठा map_info *map,
					   व्योम *to, अचिन्हित दीर्घ from,
					   sमाप_प्रकार len)
अणु
	व्योम __iomem *src = map->virt + from;
	अचिन्हित पूर्णांक shअगरt, chunk;
	u32 data;

	अगर (len <= 0 || from >= map->size)
		वापस;

	/* Make sure we करोn't go over the map limit. */
	len = min_t(sमाप_प्रकार, map->size - from, len);

	/*
	 * Since requested data size can be pretty big we have to implement
	 * the copy procedure as optimal as possible. That's why it's split
	 * up पूर्णांकo the next three stages: unaligned head, aligned body,
	 * unaligned tail.
	 */
	shअगरt = (uपूर्णांकptr_t)src & 0x3;
	अगर (shअगरt) अणु
		chunk = min_t(sमाप_प्रकार, 4 - shअगरt, len);
		data = पढ़ोl_relaxed(src - shअगरt);
		स_नकल(to, (अक्षर *)&data + shअगरt, chunk);
		src += chunk;
		to += chunk;
		len -= chunk;
	पूर्ण

	जबतक (len >= 4) अणु
		data = पढ़ोl_relaxed(src);
		स_नकल(to, &data, 4);
		src += 4;
		to += 4;
		len -= 4;
	पूर्ण

	अगर (len) अणु
		data = पढ़ोl_relaxed(src);
		स_नकल(to, &data, len);
	पूर्ण
पूर्ण

पूर्णांक of_flash_probe_bt1_rom(काष्ठा platक्रमm_device *pdev,
			   काष्ठा device_node *np,
			   काष्ठा map_info *map)
अणु
	काष्ठा device *dev = &pdev->dev;

	/* It's supposed to be पढ़ो-only MTD. */
	अगर (!of_device_is_compatible(np, "mtd-rom")) अणु
		dev_info(dev, "No mtd-rom compatible string\n");
		वापस 0;
	पूर्ण

	/* Multiplatक्रमm guard. */
	अगर (!of_device_is_compatible(np, "baikal,bt1-int-rom"))
		वापस 0;

	/* Sanity check the device parameters retrieved from DTB. */
	अगर (map->bankwidth != 4)
		dev_warn(dev, "Bank width is supposed to be 32 bits wide\n");

	map->पढ़ो = bt1_rom_map_पढ़ो;
	map->copy_from = bt1_rom_map_copy_from;

	वापस 0;
पूर्ण
