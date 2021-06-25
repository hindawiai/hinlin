<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * generic videomode helper
 *
 * Copyright (c) 2012 Steffen Trumtrar <s.trumtrar@pengutronix.de>, Pengutronix
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/of.h>
#समावेश <video/display_timing.h>
#समावेश <video/of_display_timing.h>
#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

/**
 * of_get_videomode - get the videomode #<index> from devicetree
 * @np: devicenode with the display_timings
 * @vm: set to वापस value
 * @index: index पूर्णांकo list of display_timings
 *	    (Set this to OF_USE_NATIVE_MODE to use whatever mode is
 *	     specअगरied as native mode in the DT.)
 *
 * DESCRIPTION:
 * Get a list of all display timings and put the one
 * specअगरied by index पूर्णांकo *vm. This function should only be used, अगर
 * only one videomode is to be retrieved. A driver that needs to work
 * with multiple/all videomodes should work with
 * of_get_display_timings instead.
 **/
पूर्णांक of_get_videomode(काष्ठा device_node *np, काष्ठा videomode *vm,
		     पूर्णांक index)
अणु
	काष्ठा display_timings *disp;
	पूर्णांक ret;

	disp = of_get_display_timings(np);
	अगर (!disp) अणु
		pr_err("%pOF: no timings specified\n", np);
		वापस -EINVAL;
	पूर्ण

	अगर (index == OF_USE_NATIVE_MODE)
		index = disp->native_mode;

	ret = videomode_from_timings(disp, vm, index);

	display_timings_release(disp);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_get_videomode);
