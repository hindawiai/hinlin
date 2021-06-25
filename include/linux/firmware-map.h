<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/firmware-map.h:
 *  Copyright (C) 2008 SUSE LINUX Products GmbH
 *  by Bernhard Walle <bernhard.walle@gmx.de>
 */
#अगर_अघोषित _LINUX_FIRMWARE_MAP_H
#घोषणा _LINUX_FIRMWARE_MAP_H

#समावेश <linux/list.h>

/*
 * provide a dummy पूर्णांकerface अगर CONFIG_FIRMWARE_MEMMAP is disabled
 */
#अगर_घोषित CONFIG_FIRMWARE_MEMMAP

पूर्णांक firmware_map_add_early(u64 start, u64 end, स्थिर अक्षर *type);
पूर्णांक firmware_map_add_hotplug(u64 start, u64 end, स्थिर अक्षर *type);
पूर्णांक firmware_map_हटाओ(u64 start, u64 end, स्थिर अक्षर *type);

#अन्यथा /* CONFIG_FIRMWARE_MEMMAP */

अटल अंतरभूत पूर्णांक firmware_map_add_early(u64 start, u64 end, स्थिर अक्षर *type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक firmware_map_add_hotplug(u64 start, u64 end, स्थिर अक्षर *type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक firmware_map_हटाओ(u64 start, u64 end, स्थिर अक्षर *type)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_FIRMWARE_MEMMAP */

#पूर्ण_अगर /* _LINUX_FIRMWARE_MAP_H */
