<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License क्रम more details.
 */

#अगर_अघोषित __UAPI_SOUND_TLV_H
#घोषणा __UAPI_SOUND_TLV_H

#घोषणा SNDRV_CTL_TLVT_CONTAINER 0	/* one level करोwn - group of TLVs */
#घोषणा SNDRV_CTL_TLVT_DB_SCALE	1       /* dB scale */
#घोषणा SNDRV_CTL_TLVT_DB_LINEAR 2	/* linear volume */
#घोषणा SNDRV_CTL_TLVT_DB_RANGE 3	/* dB range container */
#घोषणा SNDRV_CTL_TLVT_DB_MINMAX 4	/* dB scale with min/max */
#घोषणा SNDRV_CTL_TLVT_DB_MINMAX_MUTE 5	/* dB scale with min/max with mute */

/*
 * channel-mapping TLV items
 *  TLV length must match with num_channels
 */
#घोषणा SNDRV_CTL_TLVT_CHMAP_FIXED	0x101	/* fixed channel position */
#घोषणा SNDRV_CTL_TLVT_CHMAP_VAR	0x102	/* channels मुक्तly swappable */
#घोषणा SNDRV_CTL_TLVT_CHMAP_PAIRED	0x103	/* pair-wise swappable */

/*
 * TLV काष्ठाure is right behind the काष्ठा snd_ctl_tlv:
 *   अचिन्हित पूर्णांक type  	- see SNDRV_CTL_TLVT_*
 *   अचिन्हित पूर्णांक length
 *   .... data aligned to माप(अचिन्हित पूर्णांक), use
 *        block_length = (length + (माप(अचिन्हित पूर्णांक) - 1)) &
 *                       ~(माप(अचिन्हित पूर्णांक) - 1)) ....
 */
#घोषणा SNDRV_CTL_TLVD_ITEM(type, ...) \
	(type), SNDRV_CTL_TLVD_LENGTH(__VA_ARGS__), __VA_ARGS__
#घोषणा SNDRV_CTL_TLVD_LENGTH(...) \
	((अचिन्हित पूर्णांक)माप((स्थिर अचिन्हित पूर्णांक[]) अणु __VA_ARGS__ पूर्ण))

/* Accessor offsets क्रम TLV data items */
#घोषणा SNDRV_CTL_TLVO_TYPE		0
#घोषणा SNDRV_CTL_TLVO_LEN		1

#घोषणा SNDRV_CTL_TLVD_CONTAINER_ITEM(...) \
	SNDRV_CTL_TLVD_ITEM(SNDRV_CTL_TLVT_CONTAINER, __VA_ARGS__)
#घोषणा SNDRV_CTL_TLVD_DECLARE_CONTAINER(name, ...) \
	अचिन्हित पूर्णांक name[] = अणु \
		SNDRV_CTL_TLVD_CONTAINER_ITEM(__VA_ARGS__) \
	पूर्ण

#घोषणा SNDRV_CTL_TLVD_DB_SCALE_MASK	0xffff
#घोषणा SNDRV_CTL_TLVD_DB_SCALE_MUTE	0x10000
#घोषणा SNDRV_CTL_TLVD_DB_SCALE_ITEM(min, step, mute) \
	SNDRV_CTL_TLVD_ITEM(SNDRV_CTL_TLVT_DB_SCALE, \
			    (min), \
			    ((step) & SNDRV_CTL_TLVD_DB_SCALE_MASK) | \
			     ((mute) ? SNDRV_CTL_TLVD_DB_SCALE_MUTE : 0))
#घोषणा SNDRV_CTL_TLVD_DECLARE_DB_SCALE(name, min, step, mute) \
	अचिन्हित पूर्णांक name[] = अणु \
		SNDRV_CTL_TLVD_DB_SCALE_ITEM(min, step, mute) \
	पूर्ण

/* Accessor offsets क्रम min, mute and step items in dB scale type TLV */
#घोषणा SNDRV_CTL_TLVO_DB_SCALE_MIN		2
#घोषणा SNDRV_CTL_TLVO_DB_SCALE_MUTE_AND_STEP	3

/* dB scale specअगरied with min/max values instead of step */
#घोषणा SNDRV_CTL_TLVD_DB_MINMAX_ITEM(min_dB, max_dB) \
	SNDRV_CTL_TLVD_ITEM(SNDRV_CTL_TLVT_DB_MINMAX, (min_dB), (max_dB))
#घोषणा SNDRV_CTL_TLVD_DB_MINMAX_MUTE_ITEM(min_dB, max_dB) \
	SNDRV_CTL_TLVD_ITEM(SNDRV_CTL_TLVT_DB_MINMAX_MUTE, (min_dB), (max_dB))
#घोषणा SNDRV_CTL_TLVD_DECLARE_DB_MINMAX(name, min_dB, max_dB) \
	अचिन्हित पूर्णांक name[] = अणु \
		SNDRV_CTL_TLVD_DB_MINMAX_ITEM(min_dB, max_dB) \
	पूर्ण
#घोषणा SNDRV_CTL_TLVD_DECLARE_DB_MINMAX_MUTE(name, min_dB, max_dB) \
	अचिन्हित पूर्णांक name[] = अणु \
		SNDRV_CTL_TLVD_DB_MINMAX_MUTE_ITEM(min_dB, max_dB) \
	पूर्ण

/* Accessor offsets क्रम min, max items in db-minmax types of TLV. */
#घोषणा SNDRV_CTL_TLVO_DB_MINMAX_MIN	2
#घोषणा SNDRV_CTL_TLVO_DB_MINMAX_MAX	3

/* linear volume between min_dB and max_dB (.01dB unit) */
#घोषणा SNDRV_CTL_TLVD_DB_LINEAR_ITEM(min_dB, max_dB) \
	SNDRV_CTL_TLVD_ITEM(SNDRV_CTL_TLVT_DB_LINEAR, (min_dB), (max_dB))
#घोषणा SNDRV_CTL_TLVD_DECLARE_DB_LINEAR(name, min_dB, max_dB) \
	अचिन्हित पूर्णांक name[] = अणु \
		SNDRV_CTL_TLVD_DB_LINEAR_ITEM(min_dB, max_dB) \
	पूर्ण

/* Accessor offsets क्रम min, max items in db-linear type of TLV. */
#घोषणा SNDRV_CTL_TLVO_DB_LINEAR_MIN	2
#घोषणा SNDRV_CTL_TLVO_DB_LINEAR_MAX	3

/* dB range container:
 * Items in dB range container must be ordered by their values and by their
 * dB values. This implies that larger values must correspond with larger
 * dB values (which is also required क्रम all other mixer controls).
 */
/* Each item is: <min> <max> <TLV> */
#घोषणा SNDRV_CTL_TLVD_DB_RANGE_ITEM(...) \
	SNDRV_CTL_TLVD_ITEM(SNDRV_CTL_TLVT_DB_RANGE, __VA_ARGS__)
#घोषणा SNDRV_CTL_TLVD_DECLARE_DB_RANGE(name, ...) \
	अचिन्हित पूर्णांक name[] = अणु \
		SNDRV_CTL_TLVD_DB_RANGE_ITEM(__VA_ARGS__) \
	पूर्ण

#घोषणा SNDRV_CTL_TLVD_DB_GAIN_MUTE	-9999999

#पूर्ण_अगर
