<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * generic display timing functions
 *
 * Copyright (c) 2012 Steffen Trumtrar <s.trumtrar@pengutronix.de>, Pengutronix
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <video/display_timing.h>
#समावेश <video/videomode.h>

व्योम videomode_from_timing(स्थिर काष्ठा display_timing *dt,
			  काष्ठा videomode *vm)
अणु
	vm->pixelघड़ी = dt->pixelघड़ी.typ;
	vm->hactive = dt->hactive.typ;
	vm->hfront_porch = dt->hfront_porch.typ;
	vm->hback_porch = dt->hback_porch.typ;
	vm->hsync_len = dt->hsync_len.typ;

	vm->vactive = dt->vactive.typ;
	vm->vfront_porch = dt->vfront_porch.typ;
	vm->vback_porch = dt->vback_porch.typ;
	vm->vsync_len = dt->vsync_len.typ;

	vm->flags = dt->flags;
पूर्ण
EXPORT_SYMBOL_GPL(videomode_from_timing);

पूर्णांक videomode_from_timings(स्थिर काष्ठा display_timings *disp,
			  काष्ठा videomode *vm, अचिन्हित पूर्णांक index)
अणु
	काष्ठा display_timing *dt;

	dt = display_timings_get(disp, index);
	अगर (!dt)
		वापस -EINVAL;

	videomode_from_timing(dt, vm);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(videomode_from_timings);
