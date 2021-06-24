<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Admin Function driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "rvu_struct.h"
#समावेश "common.h"
#समावेश "mbox.h"
#समावेश "rvu.h"

काष्ठा reg_range अणु
	u64  start;
	u64  end;
पूर्ण;

काष्ठा hw_reg_map अणु
	u8	regblk;
	u8	num_ranges;
	u64	mask;
#घोषणा	 MAX_REG_RANGES	8
	काष्ठा reg_range range[MAX_REG_RANGES];
पूर्ण;

अटल काष्ठा hw_reg_map txsch_reg_map[NIX_TXSCH_LVL_CNT] = अणु
	अणुNIX_TXSCH_LVL_SMQ, 2, 0xFFFF, अणुअणु0x0700, 0x0708पूर्ण, अणु0x1400, 0x14C8पूर्ण पूर्ण पूर्ण,
	अणुNIX_TXSCH_LVL_TL4, 3, 0xFFFF, अणुअणु0x0B00, 0x0B08पूर्ण, अणु0x0B10, 0x0B18पूर्ण,
			      अणु0x1200, 0x12E0पूर्ण पूर्ण पूर्ण,
	अणुNIX_TXSCH_LVL_TL3, 3, 0xFFFF, अणुअणु0x1000, 0x10E0पूर्ण, अणु0x1600, 0x1608पूर्ण,
			      अणु0x1610, 0x1618पूर्ण पूर्ण पूर्ण,
	अणुNIX_TXSCH_LVL_TL2, 2, 0xFFFF, अणुअणु0x0E00, 0x0EE0पूर्ण, अणु0x1700, 0x17B0पूर्ण पूर्ण पूर्ण,
	अणुNIX_TXSCH_LVL_TL1, 1, 0xFFFF, अणुअणु0x0C00, 0x0D98पूर्ण पूर्ण पूर्ण,
पूर्ण;

bool rvu_check_valid_reg(पूर्णांक regmap, पूर्णांक regblk, u64 reg)
अणु
	पूर्णांक idx;
	काष्ठा hw_reg_map *map;

	/* Only 64bit offsets */
	अगर (reg & 0x07)
		वापस false;

	अगर (regmap == TXSCHQ_HWREGMAP) अणु
		अगर (regblk >= NIX_TXSCH_LVL_CNT)
			वापस false;
		map = &txsch_reg_map[regblk];
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	/* Should never happen */
	अगर (map->regblk != regblk)
		वापस false;

	reg &= map->mask;

	क्रम (idx = 0; idx < map->num_ranges; idx++) अणु
		अगर (reg >= map->range[idx].start &&
		    reg < map->range[idx].end)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
