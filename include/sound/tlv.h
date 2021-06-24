<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_TLV_H
#घोषणा __SOUND_TLV_H

/*
 *  Advanced Linux Sound Architecture - ALSA - Driver
 *  Copyright (c) 2006 by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <uapi/sound/tlv.h>

/* For historical reasons, these macros are aliases to the ones in UAPI. */
#घोषणा TLV_ITEM			SNDRV_CTL_TLVD_ITEM
#घोषणा TLV_LENGTH			SNDRV_CTL_TLVD_LENGTH

#घोषणा TLV_CONTAINER_ITEM		SNDRV_CTL_TLVD_CONTAINER_ITEM
#घोषणा DECLARE_TLV_CONTAINER		SNDRV_CTL_TLVD_DECLARE_CONTAINER

#घोषणा TLV_DB_SCALE_MASK		SNDRV_CTL_TLVD_DB_SCALE_MASK
#घोषणा TLV_DB_SCALE_MUTE		SNDRV_CTL_TLVD_DB_SCALE_MUTE
#घोषणा TLV_DB_SCALE_ITEM		SNDRV_CTL_TLVD_DB_SCALE_ITEM
#घोषणा DECLARE_TLV_DB_SCALE		SNDRV_CTL_TLVD_DECLARE_DB_SCALE

#घोषणा TLV_DB_MINMAX_ITEM		SNDRV_CTL_TLVD_DB_MINMAX_ITEM
#घोषणा TLV_DB_MINMAX_MUTE_ITEM		SNDRV_CTL_TLVD_DB_MINMAX_MUTE_ITEM
#घोषणा DECLARE_TLV_DB_MINMAX		SNDRV_CTL_TLVD_DECLARE_DB_MINMAX
#घोषणा DECLARE_TLV_DB_MINMAX_MUTE	SNDRV_CTL_TLVD_DECLARE_DB_MINMAX_MUTE

#घोषणा TLV_DB_LINEAR_ITEM		SNDRV_CTL_TLVD_DB_LINEAR_ITEM
#घोषणा DECLARE_TLV_DB_LINEAR		SNDRV_CTL_TLVD_DECLARE_DB_LINEAR

#घोषणा TLV_DB_RANGE_ITEM		SNDRV_CTL_TLVD_DB_RANGE_ITEM
#घोषणा DECLARE_TLV_DB_RANGE		SNDRV_CTL_TLVD_DECLARE_DB_RANGE

#घोषणा TLV_DB_GAIN_MUTE		SNDRV_CTL_TLVD_DB_GAIN_MUTE

/*
 * The below assumes that each item TLV is 4 words like DB_SCALE or LINEAR.
 * This is an old fasion and obsoleted by commit bf1d1c9b6179("ALSA: tlv: add
 * DECLARE_TLV_DB_RANGE()").
 */
#घोषणा TLV_DB_RANGE_HEAD(num) \
	SNDRV_CTL_TLVT_DB_RANGE, 6 * (num) * माप(अचिन्हित पूर्णांक)

#पूर्ण_अगर /* __SOUND_TLV_H */
