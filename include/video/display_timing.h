<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2012 Steffen Trumtrar <s.trumtrar@pengutronix.de>
 *
 * description of display timings
 */

#अगर_अघोषित __LINUX_DISPLAY_TIMING_H
#घोषणा __LINUX_DISPLAY_TIMING_H

#समावेश <linux/bitops.h>
#समावेश <linux/types.h>

क्रमागत display_flags अणु
	DISPLAY_FLAGS_HSYNC_LOW		= BIT(0),
	DISPLAY_FLAGS_HSYNC_HIGH	= BIT(1),
	DISPLAY_FLAGS_VSYNC_LOW		= BIT(2),
	DISPLAY_FLAGS_VSYNC_HIGH	= BIT(3),

	/* data enable flag */
	DISPLAY_FLAGS_DE_LOW		= BIT(4),
	DISPLAY_FLAGS_DE_HIGH		= BIT(5),
	/* drive data on pos. edge */
	DISPLAY_FLAGS_PIXDATA_POSEDGE	= BIT(6),
	/* drive data on neg. edge */
	DISPLAY_FLAGS_PIXDATA_NEGEDGE	= BIT(7),
	DISPLAY_FLAGS_INTERLACED	= BIT(8),
	DISPLAY_FLAGS_DOUBLESCAN	= BIT(9),
	DISPLAY_FLAGS_DOUBLECLK		= BIT(10),
	/* drive sync on pos. edge */
	DISPLAY_FLAGS_SYNC_POSEDGE	= BIT(11),
	/* drive sync on neg. edge */
	DISPLAY_FLAGS_SYNC_NEGEDGE	= BIT(12),
पूर्ण;

/*
 * A single संकेत can be specअगरied via a range of minimal and maximal values
 * with a typical value, that lies somewhere inbetween.
 */
काष्ठा timing_entry अणु
	u32 min;
	u32 typ;
	u32 max;
पूर्ण;

/*
 * Single "mode" entry. This describes one set of संकेत timings a display can
 * have in one setting. This काष्ठा can later be converted to काष्ठा videomode
 * (see include/video/videomode.h). As each timing_entry can be defined as a
 * range, one काष्ठा display_timing may become multiple काष्ठा videomodes.
 *
 * Example: hsync active high, vsync active low
 *
 *				    Active Video
 * Video  ______________________XXXXXXXXXXXXXXXXXXXXXX_____________________
 *	  |<- sync ->|<- back ->|<----- active ----->|<- front ->|<- sync..
 *	  |	     |	 porch  |		     |	 porch	 |
 *
 * HSync _|त/त/त/त/त/त/त/त/त/त/|___________________________________________|त/त/त/त/त/त/त/त/त/
 *
 * VSync त/|__________|त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/त/|_________
 */
काष्ठा display_timing अणु
	काष्ठा timing_entry pixelघड़ी;

	काष्ठा timing_entry hactive;		/* hor. active video */
	काष्ठा timing_entry hfront_porch;	/* hor. front porch */
	काष्ठा timing_entry hback_porch;	/* hor. back porch */
	काष्ठा timing_entry hsync_len;		/* hor. sync len */

	काष्ठा timing_entry vactive;		/* ver. active video */
	काष्ठा timing_entry vfront_porch;	/* ver. front porch */
	काष्ठा timing_entry vback_porch;	/* ver. back porch */
	काष्ठा timing_entry vsync_len;		/* ver. sync len */

	क्रमागत display_flags flags;		/* display flags */
पूर्ण;

/*
 * This describes all timing settings a display provides.
 * The native_mode is the शेष setting क्रम this display.
 * Drivers that can handle multiple videomodes should work with this काष्ठा and
 * convert each entry to the desired end result.
 */
काष्ठा display_timings अणु
	अचिन्हित पूर्णांक num_timings;
	अचिन्हित पूर्णांक native_mode;

	काष्ठा display_timing **timings;
पूर्ण;

/* get one entry from काष्ठा display_timings */
अटल अंतरभूत काष्ठा display_timing *display_timings_get(स्थिर काष्ठा
							 display_timings *disp,
							 अचिन्हित पूर्णांक index)
अणु
	अगर (disp->num_timings > index)
		वापस disp->timings[index];
	अन्यथा
		वापस शून्य;
पूर्ण

व्योम display_timings_release(काष्ठा display_timings *disp);

#पूर्ण_अगर
