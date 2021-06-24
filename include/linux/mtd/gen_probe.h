<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright तऊ 2001      Red Hat UK Limited
 * Copyright तऊ 2001-2010 David Woodhouse <dwmw2@infradead.org>
 */

#अगर_अघोषित __LINUX_MTD_GEN_PROBE_H__
#घोषणा __LINUX_MTD_GEN_PROBE_H__

#समावेश <linux/mtd/flashchip.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/bitops.h>

काष्ठा chip_probe अणु
	अक्षर *name;
	पूर्णांक (*probe_chip)(काष्ठा map_info *map, __u32 base,
			  अचिन्हित दीर्घ *chip_map, काष्ठा cfi_निजी *cfi);
पूर्ण;

काष्ठा mtd_info *mtd_करो_chip_probe(काष्ठा map_info *map, काष्ठा chip_probe *cp);

#पूर्ण_अगर /* __LINUX_MTD_GEN_PROBE_H__ */
