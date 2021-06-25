<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ALSA SoC TPA6130A2 amplअगरier driver
 *
 * Copyright (C) Nokia Corporation
 *
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#अगर_अघोषित __TPA6130A2_H__
#घोषणा __TPA6130A2_H__

/* Register addresses */
#घोषणा TPA6130A2_REG_CONTROL		0x01
#घोषणा TPA6130A2_REG_VOL_MUTE		0x02
#घोषणा TPA6130A2_REG_OUT_IMPEDANCE	0x03
#घोषणा TPA6130A2_REG_VERSION		0x04

/* Register bits */
/* TPA6130A2_REG_CONTROL (0x01) */
#घोषणा TPA6130A2_SWS_SHIFT		0
#घोषणा TPA6130A2_SWS			(0x01 << TPA6130A2_SWS_SHIFT)
#घोषणा TPA6130A2_TERMAL		(0x01 << 1)
#घोषणा TPA6130A2_MODE(x)		(x << 4)
#घोषणा TPA6130A2_MODE_STEREO		(0x00)
#घोषणा TPA6130A2_MODE_DUAL_MONO	(0x01)
#घोषणा TPA6130A2_MODE_BRIDGE		(0x02)
#घोषणा TPA6130A2_MODE_MASK		(0x03)
#घोषणा TPA6130A2_HP_EN_R_SHIFT		6
#घोषणा TPA6130A2_HP_EN_R		(0x01 << TPA6130A2_HP_EN_R_SHIFT)
#घोषणा TPA6130A2_HP_EN_L_SHIFT		7
#घोषणा TPA6130A2_HP_EN_L		(0x01 << TPA6130A2_HP_EN_L_SHIFT)

/* TPA6130A2_REG_VOL_MUTE (0x02) */
#घोषणा TPA6130A2_VOLUME(x)		((x & 0x3f) << 0)
#घोषणा TPA6130A2_MUTE_R		(0x01 << 6)
#घोषणा TPA6130A2_MUTE_L		(0x01 << 7)

/* TPA6130A2_REG_OUT_IMPEDANCE (0x03) */
#घोषणा TPA6130A2_HIZ_R			(0x01 << 0)
#घोषणा TPA6130A2_HIZ_L			(0x01 << 1)

/* TPA6130A2_REG_VERSION (0x04) */
#घोषणा TPA6130A2_VERSION_MASK		(0x0f)

#पूर्ण_अगर /* __TPA6130A2_H__ */
