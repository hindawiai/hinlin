<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * fbsysfs.c - framebuffer device class and attributes
 *
 * Copyright (c) 2004 James Simmons <jsimmons@infradead.org>
 */

/*
 * Note:  currently there's only stubs क्रम framebuffer_alloc and
 * framebuffer_release here.  The reson क्रम that is that until all drivers
 * are converted to use it a sysfsअगरication will खोलो OOPSable races.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/fbcon.h>
#समावेश <linux/console.h>
#समावेश <linux/module.h>

#घोषणा FB_SYSFS_FLAG_ATTR 1

/**
 * framebuffer_alloc - creates a new frame buffer info काष्ठाure
 *
 * @size: size of driver निजी data, can be zero
 * @dev: poपूर्णांकer to the device क्रम this fb, this can be शून्य
 *
 * Creates a new frame buffer info काष्ठाure. Also reserves @size bytes
 * क्रम driver निजी data (info->par). info->par (अगर any) will be
 * aligned to माप(दीर्घ).
 *
 * Returns the new काष्ठाure, or शून्य अगर an error occurred.
 *
 */
काष्ठा fb_info *framebuffer_alloc(माप_प्रकार size, काष्ठा device *dev)
अणु
#घोषणा BYTES_PER_LONG (BITS_PER_LONG/8)
#घोषणा PADDING (BYTES_PER_LONG - (माप(काष्ठा fb_info) % BYTES_PER_LONG))
	पूर्णांक fb_info_size = माप(काष्ठा fb_info);
	काष्ठा fb_info *info;
	अक्षर *p;

	अगर (size)
		fb_info_size += PADDING;

	p = kzalloc(fb_info_size + size, GFP_KERNEL);

	अगर (!p)
		वापस शून्य;

	info = (काष्ठा fb_info *) p;

	अगर (size)
		info->par = p + fb_info_size;

	info->device = dev;
	info->fbcon_rotate_hपूर्णांक = -1;

#अगर IS_ENABLED(CONFIG_FB_BACKLIGHT)
	mutex_init(&info->bl_curve_mutex);
#पूर्ण_अगर

	वापस info;
#अघोषित PADDING
#अघोषित BYTES_PER_LONG
पूर्ण
EXPORT_SYMBOL(framebuffer_alloc);

/**
 * framebuffer_release - marks the काष्ठाure available क्रम मुक्तing
 *
 * @info: frame buffer info काष्ठाure
 *
 * Drop the reference count of the device embedded in the
 * framebuffer info काष्ठाure.
 *
 */
व्योम framebuffer_release(काष्ठा fb_info *info)
अणु
	अगर (!info)
		वापस;
	kमुक्त(info->apertures);
	kमुक्त(info);
पूर्ण
EXPORT_SYMBOL(framebuffer_release);

अटल पूर्णांक activate(काष्ठा fb_info *fb_info, काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक err;

	var->activate |= FB_ACTIVATE_FORCE;
	console_lock();
	err = fb_set_var(fb_info, var);
	अगर (!err)
		fbcon_update_vcs(fb_info, var->activate & FB_ACTIVATE_ALL);
	console_unlock();
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक mode_string(अक्षर *buf, अचिन्हित पूर्णांक offset,
		       स्थिर काष्ठा fb_videomode *mode)
अणु
	अक्षर m = 'U';
	अक्षर v = 'p';

	अगर (mode->flag & FB_MODE_IS_DETAILED)
		m = 'D';
	अगर (mode->flag & FB_MODE_IS_VESA)
		m = 'V';
	अगर (mode->flag & FB_MODE_IS_STANDARD)
		m = 'S';

	अगर (mode->vmode & FB_VMODE_INTERLACED)
		v = 'i';
	अगर (mode->vmode & FB_VMODE_DOUBLE)
		v = 'd';

	वापस snम_लिखो(&buf[offset], PAGE_SIZE - offset, "%c:%dx%d%c-%d\n",
	                m, mode->xres, mode->yres, v, mode->refresh);
पूर्ण

अटल sमाप_प्रकार store_mode(काष्ठा device *device, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	अक्षर mstr[100];
	काष्ठा fb_var_screeninfo var;
	काष्ठा fb_modelist *modelist;
	काष्ठा fb_videomode *mode;
	काष्ठा list_head *pos;
	माप_प्रकार i;
	पूर्णांक err;

	स_रखो(&var, 0, माप(var));

	list_क्रम_each(pos, &fb_info->modelist) अणु
		modelist = list_entry(pos, काष्ठा fb_modelist, list);
		mode = &modelist->mode;
		i = mode_string(mstr, 0, mode);
		अगर (म_भेदन(mstr, buf, max(count, i)) == 0) अणु

			var = fb_info->var;
			fb_videomode_to_var(&var, mode);
			अगर ((err = activate(fb_info, &var)))
				वापस err;
			fb_info->mode = mode;
			वापस count;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार show_mode(काष्ठा device *device, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);

	अगर (!fb_info->mode)
		वापस 0;

	वापस mode_string(buf, 0, fb_info->mode);
पूर्ण

अटल sमाप_प्रकार store_modes(काष्ठा device *device,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	LIST_HEAD(old_list);
	पूर्णांक i = count / माप(काष्ठा fb_videomode);

	अगर (i * माप(काष्ठा fb_videomode) != count)
		वापस -EINVAL;

	console_lock();
	lock_fb_info(fb_info);

	list_splice(&fb_info->modelist, &old_list);
	fb_videomode_to_modelist((स्थिर काष्ठा fb_videomode *)buf, i,
				 &fb_info->modelist);
	अगर (fb_new_modelist(fb_info)) अणु
		fb_destroy_modelist(&fb_info->modelist);
		list_splice(&old_list, &fb_info->modelist);
	पूर्ण अन्यथा
		fb_destroy_modelist(&old_list);

	unlock_fb_info(fb_info);
	console_unlock();

	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_modes(काष्ठा device *device, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	अचिन्हित पूर्णांक i;
	काष्ठा list_head *pos;
	काष्ठा fb_modelist *modelist;
	स्थिर काष्ठा fb_videomode *mode;

	i = 0;
	list_क्रम_each(pos, &fb_info->modelist) अणु
		modelist = list_entry(pos, काष्ठा fb_modelist, list);
		mode = &modelist->mode;
		i += mode_string(buf, i, mode);
	पूर्ण
	वापस i;
पूर्ण

अटल sमाप_प्रकार store_bpp(काष्ठा device *device, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	काष्ठा fb_var_screeninfo var;
	अक्षर ** last = शून्य;
	पूर्णांक err;

	var = fb_info->var;
	var.bits_per_pixel = simple_म_से_अदीर्घ(buf, last, 0);
	अगर ((err = activate(fb_info, &var)))
		वापस err;
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_bpp(काष्ठा device *device, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", fb_info->var.bits_per_pixel);
पूर्ण

अटल sमाप_प्रकार store_rotate(काष्ठा device *device,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	काष्ठा fb_var_screeninfo var;
	अक्षर **last = शून्य;
	पूर्णांक err;

	var = fb_info->var;
	var.rotate = simple_म_से_अदीर्घ(buf, last, 0);

	अगर ((err = activate(fb_info, &var)))
		वापस err;

	वापस count;
पूर्ण


अटल sमाप_प्रकार show_rotate(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", fb_info->var.rotate);
पूर्ण

अटल sमाप_प्रकार store_भव(काष्ठा device *device,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	काष्ठा fb_var_screeninfo var;
	अक्षर *last = शून्य;
	पूर्णांक err;

	var = fb_info->var;
	var.xres_भव = simple_म_से_अदीर्घ(buf, &last, 0);
	last++;
	अगर (last - buf >= count)
		वापस -EINVAL;
	var.yres_भव = simple_म_से_अदीर्घ(last, &last, 0);

	अगर ((err = activate(fb_info, &var)))
		वापस err;
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_भव(काष्ठा device *device,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d,%d\n", fb_info->var.xres_भव,
			fb_info->var.yres_भव);
पूर्ण

अटल sमाप_प्रकार show_stride(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", fb_info->fix.line_length);
पूर्ण

अटल sमाप_प्रकार store_blank(काष्ठा device *device,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	अक्षर *last = शून्य;
	पूर्णांक err, arg;

	arg = simple_म_से_अदीर्घ(buf, &last, 0);
	console_lock();
	err = fb_blank(fb_info, arg);
	/* might again call पूर्णांकo fb_blank */
	fbcon_fb_blanked(fb_info, arg);
	console_unlock();
	अगर (err < 0)
		वापस err;
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_blank(काष्ठा device *device,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
//	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार store_console(काष्ठा device *device,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
//	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_console(काष्ठा device *device,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
//	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार store_cursor(काष्ठा device *device,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
//	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_cursor(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
//	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार store_pan(काष्ठा device *device,
			 काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	काष्ठा fb_var_screeninfo var;
	अक्षर *last = शून्य;
	पूर्णांक err;

	var = fb_info->var;
	var.xoffset = simple_म_से_अदीर्घ(buf, &last, 0);
	last++;
	अगर (last - buf >= count)
		वापस -EINVAL;
	var.yoffset = simple_म_से_अदीर्घ(last, &last, 0);

	console_lock();
	err = fb_pan_display(fb_info, &var);
	console_unlock();

	अगर (err < 0)
		वापस err;
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pan(काष्ठा device *device,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d,%d\n", fb_info->var.xoffset,
			fb_info->var.yoffset);
पूर्ण

अटल sमाप_प्रकार show_name(काष्ठा device *device,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", fb_info->fix.id);
पूर्ण

अटल sमाप_प्रकार store_fbstate(काष्ठा device *device,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	u32 state;
	अक्षर *last = शून्य;

	state = simple_म_से_अदीर्घ(buf, &last, 0);

	console_lock();
	lock_fb_info(fb_info);

	fb_set_suspend(fb_info, (पूर्णांक)state);

	unlock_fb_info(fb_info);
	console_unlock();

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_fbstate(काष्ठा device *device,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", fb_info->state);
पूर्ण

#अगर IS_ENABLED(CONFIG_FB_BACKLIGHT)
अटल sमाप_प्रकार store_bl_curve(काष्ठा device *device,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	u8 पंचांगp_curve[FB_BACKLIGHT_LEVELS];
	अचिन्हित पूर्णांक i;

	/* Some drivers करोn't use framebuffer_alloc(), but those also
	 * करोn't have backlights.
	 */
	अगर (!fb_info || !fb_info->bl_dev)
		वापस -ENODEV;

	अगर (count != (FB_BACKLIGHT_LEVELS / 8 * 24))
		वापस -EINVAL;

	क्रम (i = 0; i < (FB_BACKLIGHT_LEVELS / 8); ++i)
		अगर (माला_पूछो(&buf[i * 24],
			"%2hhx %2hhx %2hhx %2hhx %2hhx %2hhx %2hhx %2hhx\n",
			&पंचांगp_curve[i * 8 + 0],
			&पंचांगp_curve[i * 8 + 1],
			&पंचांगp_curve[i * 8 + 2],
			&पंचांगp_curve[i * 8 + 3],
			&पंचांगp_curve[i * 8 + 4],
			&पंचांगp_curve[i * 8 + 5],
			&पंचांगp_curve[i * 8 + 6],
			&पंचांगp_curve[i * 8 + 7]) != 8)
			वापस -EINVAL;

	/* If there has been an error in the input data, we won't
	 * reach this loop.
	 */
	mutex_lock(&fb_info->bl_curve_mutex);
	क्रम (i = 0; i < FB_BACKLIGHT_LEVELS; ++i)
		fb_info->bl_curve[i] = पंचांगp_curve[i];
	mutex_unlock(&fb_info->bl_curve_mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_bl_curve(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	sमाप_प्रकार len = 0;
	अचिन्हित पूर्णांक i;

	/* Some drivers करोn't use framebuffer_alloc(), but those also
	 * करोn't have backlights.
	 */
	अगर (!fb_info || !fb_info->bl_dev)
		वापस -ENODEV;

	mutex_lock(&fb_info->bl_curve_mutex);
	क्रम (i = 0; i < FB_BACKLIGHT_LEVELS; i += 8)
		len += scnम_लिखो(&buf[len], PAGE_SIZE - len, "%8ph\n",
				fb_info->bl_curve + i);
	mutex_unlock(&fb_info->bl_curve_mutex);

	वापस len;
पूर्ण
#पूर्ण_अगर

/* When cmap is added back in it should be a binary attribute
 * not a text one. Consideration should also be given to converting
 * fbdev to use configfs instead of sysfs */
अटल काष्ठा device_attribute device_attrs[] = अणु
	__ATTR(bits_per_pixel, S_IRUGO|S_IWUSR, show_bpp, store_bpp),
	__ATTR(blank, S_IRUGO|S_IWUSR, show_blank, store_blank),
	__ATTR(console, S_IRUGO|S_IWUSR, show_console, store_console),
	__ATTR(cursor, S_IRUGO|S_IWUSR, show_cursor, store_cursor),
	__ATTR(mode, S_IRUGO|S_IWUSR, show_mode, store_mode),
	__ATTR(modes, S_IRUGO|S_IWUSR, show_modes, store_modes),
	__ATTR(pan, S_IRUGO|S_IWUSR, show_pan, store_pan),
	__ATTR(भव_size, S_IRUGO|S_IWUSR, show_भव, store_भव),
	__ATTR(name, S_IRUGO, show_name, शून्य),
	__ATTR(stride, S_IRUGO, show_stride, शून्य),
	__ATTR(rotate, S_IRUGO|S_IWUSR, show_rotate, store_rotate),
	__ATTR(state, S_IRUGO|S_IWUSR, show_fbstate, store_fbstate),
#अगर IS_ENABLED(CONFIG_FB_BACKLIGHT)
	__ATTR(bl_curve, S_IRUGO|S_IWUSR, show_bl_curve, store_bl_curve),
#पूर्ण_अगर
पूर्ण;

पूर्णांक fb_init_device(काष्ठा fb_info *fb_info)
अणु
	पूर्णांक i, error = 0;

	dev_set_drvdata(fb_info->dev, fb_info);

	fb_info->class_flag |= FB_SYSFS_FLAG_ATTR;

	क्रम (i = 0; i < ARRAY_SIZE(device_attrs); i++) अणु
		error = device_create_file(fb_info->dev, &device_attrs[i]);

		अगर (error)
			अवरोध;
	पूर्ण

	अगर (error) अणु
		जबतक (--i >= 0)
			device_हटाओ_file(fb_info->dev, &device_attrs[i]);
		fb_info->class_flag &= ~FB_SYSFS_FLAG_ATTR;
	पूर्ण

	वापस 0;
पूर्ण

व्योम fb_cleanup_device(काष्ठा fb_info *fb_info)
अणु
	अचिन्हित पूर्णांक i;

	अगर (fb_info->class_flag & FB_SYSFS_FLAG_ATTR) अणु
		क्रम (i = 0; i < ARRAY_SIZE(device_attrs); i++)
			device_हटाओ_file(fb_info->dev, &device_attrs[i]);

		fb_info->class_flag &= ~FB_SYSFS_FLAG_ATTR;
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_FB_BACKLIGHT)
/* This function generates a linear backlight curve
 *
 *     0: off
 *   1-7: min
 * 8-127: linear from min to max
 */
व्योम fb_bl_शेष_curve(काष्ठा fb_info *fb_info, u8 off, u8 min, u8 max)
अणु
	अचिन्हित पूर्णांक i, flat, count, range = (max - min);

	mutex_lock(&fb_info->bl_curve_mutex);

	fb_info->bl_curve[0] = off;

	क्रम (flat = 1; flat < (FB_BACKLIGHT_LEVELS / 16); ++flat)
		fb_info->bl_curve[flat] = min;

	count = FB_BACKLIGHT_LEVELS * 15 / 16;
	क्रम (i = 0; i < count; ++i)
		fb_info->bl_curve[flat + i] = min + (range * (i + 1) / count);

	mutex_unlock(&fb_info->bl_curve_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(fb_bl_शेष_curve);
#पूर्ण_अगर
