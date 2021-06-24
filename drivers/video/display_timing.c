<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * generic display timing functions
 *
 * Copyright (c) 2012 Steffen Trumtrar <s.trumtrar@pengutronix.de>, Pengutronix
 */

#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <video/display_timing.h>

व्योम display_timings_release(काष्ठा display_timings *disp)
अणु
	अगर (disp->timings) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < disp->num_timings; i++)
			kमुक्त(disp->timings[i]);
		kमुक्त(disp->timings);
	पूर्ण
	kमुक्त(disp);
पूर्ण
EXPORT_SYMBOL_GPL(display_timings_release);
