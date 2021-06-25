<शैली गुरु>
/*
 * This header provides स्थिरants क्रम hisilicon pinctrl bindings.
 *
 * Copyright (c) 2015 Hisilicon Limited.
 * Copyright (c) 2015 Linaro Limited.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _DT_BINDINGS_PINCTRL_HISI_H
#घोषणा _DT_BINDINGS_PINCTRL_HISI_H

/* iomg bit definition */
#घोषणा MUX_M0		0
#घोषणा MUX_M1		1
#घोषणा MUX_M2		2
#घोषणा MUX_M3		3
#घोषणा MUX_M4		4
#घोषणा MUX_M5		5
#घोषणा MUX_M6		6
#घोषणा MUX_M7		7

/* iocg bit definition */
#घोषणा PULL_MASK	(3)
#घोषणा PULL_DIS	(0)
#घोषणा PULL_UP		(1 << 0)
#घोषणा PULL_DOWN	(1 << 1)

/* drive strength definition */
#घोषणा DRIVE_MASK	(7 << 4)
#घोषणा DRIVE1_02MA	(0 << 4)
#घोषणा DRIVE1_04MA	(1 << 4)
#घोषणा DRIVE1_08MA	(2 << 4)
#घोषणा DRIVE1_10MA	(3 << 4)
#घोषणा DRIVE2_02MA	(0 << 4)
#घोषणा DRIVE2_04MA	(1 << 4)
#घोषणा DRIVE2_08MA	(2 << 4)
#घोषणा DRIVE2_10MA	(3 << 4)
#घोषणा DRIVE3_04MA	(0 << 4)
#घोषणा DRIVE3_08MA	(1 << 4)
#घोषणा DRIVE3_12MA	(2 << 4)
#घोषणा DRIVE3_16MA	(3 << 4)
#घोषणा DRIVE3_20MA	(4 << 4)
#घोषणा DRIVE3_24MA	(5 << 4)
#घोषणा DRIVE3_32MA	(6 << 4)
#घोषणा DRIVE3_40MA	(7 << 4)
#घोषणा DRIVE4_02MA	(0 << 4)
#घोषणा DRIVE4_04MA	(2 << 4)
#घोषणा DRIVE4_08MA	(4 << 4)
#घोषणा DRIVE4_10MA	(6 << 4)

/* drive strength definition क्रम hi3660 */
#घोषणा DRIVE6_MASK	(15 << 4)
#घोषणा DRIVE6_04MA	(0 << 4)
#घोषणा DRIVE6_12MA	(4 << 4)
#घोषणा DRIVE6_19MA	(8 << 4)
#घोषणा DRIVE6_27MA	(10 << 4)
#घोषणा DRIVE6_32MA	(15 << 4)
#घोषणा DRIVE7_02MA	(0 << 4)
#घोषणा DRIVE7_04MA	(1 << 4)
#घोषणा DRIVE7_06MA	(2 << 4)
#घोषणा DRIVE7_08MA	(3 << 4)
#घोषणा DRIVE7_10MA	(4 << 4)
#घोषणा DRIVE7_12MA	(5 << 4)
#घोषणा DRIVE7_14MA	(6 << 4)
#घोषणा DRIVE7_16MA	(7 << 4)
#पूर्ण_अगर
