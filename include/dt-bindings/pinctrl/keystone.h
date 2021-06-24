<शैली गुरु>
/*
 * This header provides स्थिरants क्रम Keystone pinctrl bindings.
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _DT_BINDINGS_PINCTRL_KEYSTONE_H
#घोषणा _DT_BINDINGS_PINCTRL_KEYSTONE_H

#घोषणा MUX_MODE0	0
#घोषणा MUX_MODE1	1
#घोषणा MUX_MODE2	2
#घोषणा MUX_MODE3	3
#घोषणा MUX_MODE4	4
#घोषणा MUX_MODE5	5

#घोषणा BUFFER_CLASS_B	(0 << 19)
#घोषणा BUFFER_CLASS_C	(1 << 19)
#घोषणा BUFFER_CLASS_D	(2 << 19)
#घोषणा BUFFER_CLASS_E	(3 << 19)

#घोषणा PULL_DISABLE	(1 << 16)
#घोषणा PIN_PULLUP	(1 << 17)
#घोषणा PIN_PULLDOWN	(0 << 17)

#घोषणा KEYSTONE_IOPAD_OFFSET(pa, offset) (((pa) & 0xffff) - (offset))

#घोषणा K2G_CORE_IOPAD(pa) KEYSTONE_IOPAD_OFFSET((pa), 0x1000)

#पूर्ण_अगर
