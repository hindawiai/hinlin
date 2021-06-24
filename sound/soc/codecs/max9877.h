<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * max9877.h  --  amp driver क्रम max9877
 *
 * Copyright (C) 2009 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#अगर_अघोषित _MAX9877_H
#घोषणा _MAX9877_H

#घोषणा MAX9877_INPUT_MODE		0x00
#घोषणा MAX9877_SPK_VOLUME		0x01
#घोषणा MAX9877_HPL_VOLUME		0x02
#घोषणा MAX9877_HPR_VOLUME		0x03
#घोषणा MAX9877_OUTPUT_MODE		0x04

/* MAX9877_INPUT_MODE */
#घोषणा MAX9877_INB			(1 << 4)
#घोषणा MAX9877_INA			(1 << 5)
#घोषणा MAX9877_ZCD			(1 << 6)

/* MAX9877_OUTPUT_MODE */
#घोषणा MAX9877_OUTMODE_MASK		(15 << 0)
#घोषणा MAX9877_OSC_MASK		(3 << 4)
#घोषणा MAX9877_OSC_OFFSET		4
#घोषणा MAX9877_BYPASS			(1 << 6)
#घोषणा MAX9877_SHDN			(1 << 7)

#पूर्ण_अगर
