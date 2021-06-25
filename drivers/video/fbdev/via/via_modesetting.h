<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.
 * Copyright 2010 Florian Tobias Schandinat <FlorianSchandinat@gmx.de>
 */
/*
 * basic modesetting functions
 */

#अगर_अघोषित __VIA_MODESETTING_H__
#घोषणा __VIA_MODESETTING_H__

#समावेश <linux/types.h>


#घोषणा VIA_PITCH_SIZE	(1<<3)
#घोषणा VIA_PITCH_MAX	0x3FF8


काष्ठा via_display_timing अणु
	u16 hor_total;
	u16 hor_addr;
	u16 hor_blank_start;
	u16 hor_blank_end;
	u16 hor_sync_start;
	u16 hor_sync_end;
	u16 ver_total;
	u16 ver_addr;
	u16 ver_blank_start;
	u16 ver_blank_end;
	u16 ver_sync_start;
	u16 ver_sync_end;
पूर्ण;


व्योम via_set_primary_timing(स्थिर काष्ठा via_display_timing *timing);
व्योम via_set_secondary_timing(स्थिर काष्ठा via_display_timing *timing);
व्योम via_set_primary_address(u32 addr);
व्योम via_set_secondary_address(u32 addr);
व्योम via_set_primary_pitch(u32 pitch);
व्योम via_set_secondary_pitch(u32 pitch);
व्योम via_set_primary_color_depth(u8 depth);
व्योम via_set_secondary_color_depth(u8 depth);

#पूर्ण_अगर /* __VIA_MODESETTING_H__ */
