<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * For boards with physically mapped flash and using
 * drivers/mtd/maps/physmap.c mapping driver.
 *
 * Copyright (C) 2003 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 */

#अगर_अघोषित __LINUX_MTD_PHYSMAP__
#घोषणा __LINUX_MTD_PHYSMAP__

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

काष्ठा map_info;
काष्ठा platक्रमm_device;

काष्ठा physmap_flash_data अणु
	अचिन्हित पूर्णांक		width;
	पूर्णांक			(*init)(काष्ठा platक्रमm_device *);
	व्योम			(*निकास)(काष्ठा platक्रमm_device *);
	व्योम			(*set_vpp)(काष्ठा platक्रमm_device *, पूर्णांक);
	अचिन्हित पूर्णांक		nr_parts;
	अचिन्हित पूर्णांक		pfow_base;
	अक्षर                    *probe_type;
	काष्ठा mtd_partition	*parts;
	स्थिर अक्षर * स्थिर	*part_probe_types;
पूर्ण;

#पूर्ण_अगर /* __LINUX_MTD_PHYSMAP__ */
