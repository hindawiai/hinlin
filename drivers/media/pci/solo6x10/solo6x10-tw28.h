<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

#अगर_अघोषित __SOLO6X10_TW28_H
#घोषणा __SOLO6X10_TW28_H

#समावेश "solo6x10.h"

#घोषणा TW_NUM_CHIP				4
#घोषणा TW_BASE_ADDR				0x28
#घोषणा TW_CHIP_OFFSET_ADDR(n)			(TW_BASE_ADDR + (n))

/* tw2815 */
#घोषणा TW_AV_STAT_ADDR				0x5a
#घोषणा TW_HUE_ADDR(n)				(0x07 | ((n) << 4))
#घोषणा TW_SATURATION_ADDR(n)			(0x08 | ((n) << 4))
#घोषणा TW_CONTRAST_ADDR(n)			(0x09 | ((n) << 4))
#घोषणा TW_BRIGHTNESS_ADDR(n)			(0x0a | ((n) << 4))
#घोषणा TW_AUDIO_OUTPUT_VOL_ADDR		0x70
#घोषणा TW_AUDIO_INPUT_GAIN_ADDR(n)		(0x60 + ((n > 1) ? 1 : 0))

/* tw286x */
#घोषणा TW286x_AV_STAT_ADDR			0xfd
#घोषणा TW286x_HUE_ADDR(n)			(0x06 | ((n) << 4))
#घोषणा TW286x_SATURATIONU_ADDR(n)		(0x04 | ((n) << 4))
#घोषणा TW286x_SATURATIONV_ADDR(n)		(0x05 | ((n) << 4))
#घोषणा TW286x_CONTRAST_ADDR(n)			(0x02 | ((n) << 4))
#घोषणा TW286x_BRIGHTNESS_ADDR(n)		(0x01 | ((n) << 4))
#घोषणा TW286x_SHARPNESS(n)			(0x03 | ((n) << 4))
#घोषणा TW286x_AUDIO_OUTPUT_VOL_ADDR		0xdf
#घोषणा TW286x_AUDIO_INPUT_GAIN_ADDR(n)		(0xD0 + ((n > 1) ? 1 : 0))

पूर्णांक solo_tw28_init(काष्ठा solo_dev *solo_dev);

पूर्णांक tw28_set_ctrl_val(काष्ठा solo_dev *solo_dev, u32 ctrl, u8 ch, s32 val);
पूर्णांक tw28_get_ctrl_val(काष्ठा solo_dev *solo_dev, u32 ctrl, u8 ch, s32 *val);
bool tw28_has_sharpness(काष्ठा solo_dev *solo_dev, u8 ch);

u8 tw28_get_audio_gain(काष्ठा solo_dev *solo_dev, u8 ch);
व्योम tw28_set_audio_gain(काष्ठा solo_dev *solo_dev, u8 ch, u8 val);
पूर्णांक tw28_get_video_status(काष्ठा solo_dev *solo_dev, u8 ch);

#अगर 0
अचिन्हित पूर्णांक tw2815_get_audio_status(काष्ठा SOLO *solo);
व्योम tw2815_Set_AudioOutVol(काष्ठा SOLO *solo, अचिन्हित पूर्णांक u_val);
#पूर्ण_अगर

#पूर्ण_अगर /* __SOLO6X10_TW28_H */
