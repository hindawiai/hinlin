<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2012 Steffen Trumtrar <s.trumtrar@pengutronix.de>
 *
 * generic videomode description
 */

#अगर_अघोषित __LINUX_VIDEOMODE_H
#घोषणा __LINUX_VIDEOMODE_H

#समावेश <linux/types.h>
#समावेश <video/display_timing.h>

/*
 * Subप्रणाली independent description of a videomode.
 * Can be generated from काष्ठा display_timing.
 */
काष्ठा videomode अणु
	अचिन्हित दीर्घ pixelघड़ी;	/* pixelघड़ी in Hz */

	u32 hactive;
	u32 hfront_porch;
	u32 hback_porch;
	u32 hsync_len;

	u32 vactive;
	u32 vfront_porch;
	u32 vback_porch;
	u32 vsync_len;

	क्रमागत display_flags flags; /* display flags */
पूर्ण;

/**
 * videomode_from_timing - convert display timing to videomode
 * @dt: display_timing काष्ठाure
 * @vm: वापस value
 *
 * DESCRIPTION:
 * This function converts a काष्ठा display_timing to a काष्ठा videomode.
 */
व्योम videomode_from_timing(स्थिर काष्ठा display_timing *dt,
			  काष्ठा videomode *vm);

/**
 * videomode_from_timings - convert one display timings entry to videomode
 * @disp: काष्ठाure with all possible timing entries
 * @vm: वापस value
 * @index: index पूर्णांकo the list of display timings in devicetree
 *
 * DESCRIPTION:
 * This function converts one काष्ठा display_timing entry to a काष्ठा videomode.
 */
पूर्णांक videomode_from_timings(स्थिर काष्ठा display_timings *disp,
			  काष्ठा videomode *vm, अचिन्हित पूर्णांक index);

#पूर्ण_अगर
