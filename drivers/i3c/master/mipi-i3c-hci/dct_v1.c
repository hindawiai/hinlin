<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/i3c/master.h>
#समावेश <linux/पन.स>

#समावेश "hci.h"
#समावेश "dct.h"

/*
 * Device Characteristic Table
 */

व्योम i3c_hci_dct_get_val(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक dct_idx,
			 u64 *pid, अचिन्हित पूर्णांक *dcr, अचिन्हित पूर्णांक *bcr)
अणु
	व्योम __iomem *reg = hci->DCT_regs + dct_idx * 4 * 4;
	u32 dct_entry_data[4];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		dct_entry_data[i] = पढ़ोl(reg);
		reg += 4;
	पूर्ण

	*pid = ((u64)dct_entry_data[0]) << (47 - 32 + 1) |
	       FIELD_GET(W1_MASK(47, 32), dct_entry_data[1]);
	*dcr = FIELD_GET(W2_MASK(71, 64), dct_entry_data[2]);
	*bcr = FIELD_GET(W2_MASK(79, 72), dct_entry_data[2]);
पूर्ण
