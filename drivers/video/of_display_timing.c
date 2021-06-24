<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OF helpers क्रम parsing display timings
 *
 * Copyright (c) 2012 Steffen Trumtrar <s.trumtrar@pengutronix.de>, Pengutronix
 *
 * based on of_videomode.c by Sascha Hauer <s.hauer@pengutronix.de>
 */
#समावेश <linux/export.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <video/display_timing.h>
#समावेश <video/of_display_timing.h>

/**
 * parse_timing_property - parse timing_entry from device_node
 * @np: device_node with the property
 * @name: name of the property
 * @result: will be set to the वापस value
 *
 * DESCRIPTION:
 * Every display_timing can be specअगरied with either just the typical value or
 * a range consisting of min/typ/max. This function helps handling this
 **/
अटल पूर्णांक parse_timing_property(स्थिर काष्ठा device_node *np, स्थिर अक्षर *name,
			  काष्ठा timing_entry *result)
अणु
	काष्ठा property *prop;
	पूर्णांक length, cells, ret;

	prop = of_find_property(np, name, &length);
	अगर (!prop) अणु
		pr_err("%pOF: could not find property %s\n", np, name);
		वापस -EINVAL;
	पूर्ण

	cells = length / माप(u32);
	अगर (cells == 1) अणु
		ret = of_property_पढ़ो_u32(np, name, &result->typ);
		result->min = result->typ;
		result->max = result->typ;
	पूर्ण अन्यथा अगर (cells == 3) अणु
		ret = of_property_पढ़ो_u32_array(np, name, &result->min, cells);
	पूर्ण अन्यथा अणु
		pr_err("%pOF: illegal timing specification in %s\n", np, name);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * of_parse_display_timing - parse display_timing entry from device_node
 * @np: device_node with the properties
 * @dt: display_timing that contains the result. I may be partially written in हाल of errors
 **/
अटल पूर्णांक of_parse_display_timing(स्थिर काष्ठा device_node *np,
		काष्ठा display_timing *dt)
अणु
	u32 val = 0;
	पूर्णांक ret = 0;

	स_रखो(dt, 0, माप(*dt));

	ret |= parse_timing_property(np, "hback-porch", &dt->hback_porch);
	ret |= parse_timing_property(np, "hfront-porch", &dt->hfront_porch);
	ret |= parse_timing_property(np, "hactive", &dt->hactive);
	ret |= parse_timing_property(np, "hsync-len", &dt->hsync_len);
	ret |= parse_timing_property(np, "vback-porch", &dt->vback_porch);
	ret |= parse_timing_property(np, "vfront-porch", &dt->vfront_porch);
	ret |= parse_timing_property(np, "vactive", &dt->vactive);
	ret |= parse_timing_property(np, "vsync-len", &dt->vsync_len);
	ret |= parse_timing_property(np, "clock-frequency", &dt->pixelघड़ी);

	dt->flags = 0;
	अगर (!of_property_पढ़ो_u32(np, "vsync-active", &val))
		dt->flags |= val ? DISPLAY_FLAGS_VSYNC_HIGH :
				DISPLAY_FLAGS_VSYNC_LOW;
	अगर (!of_property_पढ़ो_u32(np, "hsync-active", &val))
		dt->flags |= val ? DISPLAY_FLAGS_HSYNC_HIGH :
				DISPLAY_FLAGS_HSYNC_LOW;
	अगर (!of_property_पढ़ो_u32(np, "de-active", &val))
		dt->flags |= val ? DISPLAY_FLAGS_DE_HIGH :
				DISPLAY_FLAGS_DE_LOW;
	अगर (!of_property_पढ़ो_u32(np, "pixelclk-active", &val))
		dt->flags |= val ? DISPLAY_FLAGS_PIXDATA_POSEDGE :
				DISPLAY_FLAGS_PIXDATA_NEGEDGE;

	अगर (!of_property_पढ़ो_u32(np, "syncclk-active", &val))
		dt->flags |= val ? DISPLAY_FLAGS_SYNC_POSEDGE :
				DISPLAY_FLAGS_SYNC_NEGEDGE;
	अन्यथा अगर (dt->flags & (DISPLAY_FLAGS_PIXDATA_POSEDGE |
			      DISPLAY_FLAGS_PIXDATA_NEGEDGE))
		dt->flags |= dt->flags & DISPLAY_FLAGS_PIXDATA_POSEDGE ?
				DISPLAY_FLAGS_SYNC_POSEDGE :
				DISPLAY_FLAGS_SYNC_NEGEDGE;

	अगर (of_property_पढ़ो_bool(np, "interlaced"))
		dt->flags |= DISPLAY_FLAGS_INTERLACED;
	अगर (of_property_पढ़ो_bool(np, "doublescan"))
		dt->flags |= DISPLAY_FLAGS_DOUBLESCAN;
	अगर (of_property_पढ़ो_bool(np, "doubleclk"))
		dt->flags |= DISPLAY_FLAGS_DOUBLECLK;

	अगर (ret) अणु
		pr_err("%pOF: error reading timing properties\n", np);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * of_get_display_timing - parse a display_timing entry
 * @np: device_node with the timing subnode
 * @name: name of the timing node
 * @dt: display_timing काष्ठा to fill
 **/
पूर्णांक of_get_display_timing(स्थिर काष्ठा device_node *np, स्थिर अक्षर *name,
		काष्ठा display_timing *dt)
अणु
	काष्ठा device_node *timing_np;
	पूर्णांक ret;

	अगर (!np)
		वापस -EINVAL;

	timing_np = of_get_child_by_name(np, name);
	अगर (!timing_np)
		वापस -ENOENT;

	ret = of_parse_display_timing(timing_np, dt);

	of_node_put(timing_np);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_get_display_timing);

/**
 * of_get_display_timings - parse all display_timing entries from a device_node
 * @np: device_node with the subnodes
 **/
काष्ठा display_timings *of_get_display_timings(स्थिर काष्ठा device_node *np)
अणु
	काष्ठा device_node *timings_np;
	काष्ठा device_node *entry;
	काष्ठा device_node *native_mode;
	काष्ठा display_timings *disp;

	अगर (!np)
		वापस शून्य;

	timings_np = of_get_child_by_name(np, "display-timings");
	अगर (!timings_np) अणु
		pr_err("%pOF: could not find display-timings node\n", np);
		वापस शून्य;
	पूर्ण

	disp = kzalloc(माप(*disp), GFP_KERNEL);
	अगर (!disp) अणु
		pr_err("%pOF: could not allocate struct disp'\n", np);
		जाओ dispfail;
	पूर्ण

	entry = of_parse_phandle(timings_np, "native-mode", 0);
	/* assume first child as native mode अगर none provided */
	अगर (!entry)
		entry = of_get_next_child(timings_np, शून्य);
	/* अगर there is no child, it is useless to go on */
	अगर (!entry) अणु
		pr_err("%pOF: no timing specifications given\n", np);
		जाओ entryfail;
	पूर्ण

	pr_debug("%pOF: using %pOFn as default timing\n", np, entry);

	native_mode = entry;

	disp->num_timings = of_get_child_count(timings_np);
	अगर (disp->num_timings == 0) अणु
		/* should never happen, as entry was alपढ़ोy found above */
		pr_err("%pOF: no timings specified\n", np);
		जाओ entryfail;
	पूर्ण

	disp->timings = kसुस्मृति(disp->num_timings,
				माप(काष्ठा display_timing *),
				GFP_KERNEL);
	अगर (!disp->timings) अणु
		pr_err("%pOF: could not allocate timings array\n", np);
		जाओ entryfail;
	पूर्ण

	disp->num_timings = 0;
	disp->native_mode = 0;

	क्रम_each_child_of_node(timings_np, entry) अणु
		काष्ठा display_timing *dt;
		पूर्णांक r;

		dt = kzalloc(माप(*dt), GFP_KERNEL);
		अगर (!dt) अणु
			pr_err("%pOF: could not allocate display_timing struct\n",
				np);
			जाओ timingfail;
		पूर्ण

		r = of_parse_display_timing(entry, dt);
		अगर (r) अणु
			/*
			 * to not encourage wrong devicetrees, fail in हाल of
			 * an error
			 */
			pr_err("%pOF: error in timing %d\n",
				np, disp->num_timings + 1);
			kमुक्त(dt);
			जाओ timingfail;
		पूर्ण

		अगर (native_mode == entry)
			disp->native_mode = disp->num_timings;

		disp->timings[disp->num_timings] = dt;
		disp->num_timings++;
	पूर्ण
	of_node_put(timings_np);
	/*
	 * native_mode poपूर्णांकs to the device_node वापसed by of_parse_phandle
	 * thereक्रमe call of_node_put on it
	 */
	of_node_put(native_mode);

	pr_debug("%pOF: got %d timings. Using timing #%d as default\n",
		np, disp->num_timings,
		disp->native_mode + 1);

	वापस disp;

timingfail:
	of_node_put(native_mode);
	display_timings_release(disp);
	disp = शून्य;
entryfail:
	kमुक्त(disp);
dispfail:
	of_node_put(timings_np);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(of_get_display_timings);
