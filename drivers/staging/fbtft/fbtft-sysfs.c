<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "fbtft.h"
#समावेश "internal.h"

अटल पूर्णांक get_next_uदीर्घ(अक्षर **str_p, अचिन्हित दीर्घ *val, अक्षर *sep, पूर्णांक base)
अणु
	अक्षर *p_val;

	अगर (!str_p || !(*str_p))
		वापस -EINVAL;

	p_val = strsep(str_p, sep);

	अगर (!p_val)
		वापस -EINVAL;

	वापस kम_से_अदीर्घ(p_val, base, val);
पूर्ण

पूर्णांक fbtft_gamma_parse_str(काष्ठा fbtft_par *par, u32 *curves,
			  स्थिर अक्षर *str, पूर्णांक size)
अणु
	अक्षर *str_p, *curve_p = शून्य;
	अक्षर *पंचांगp;
	अचिन्हित दीर्घ val = 0;
	पूर्णांक ret = 0;
	पूर्णांक curve_counter, value_counter;
	पूर्णांक _count;

	fbtft_par_dbg(DEBUG_SYSFS, par, "%s() str=\n", __func__);

	अगर (!str || !curves)
		वापस -EINVAL;

	fbtft_par_dbg(DEBUG_SYSFS, par, "%s\n", str);

	पंचांगp = kmemdup(str, size + 1, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	/* replace optional separators */
	str_p = पंचांगp;
	जबतक (*str_p) अणु
		अगर (*str_p == ',')
			*str_p = ' ';
		अगर (*str_p == ';')
			*str_p = '\n';
		str_p++;
	पूर्ण

	str_p = strim(पंचांगp);

	curve_counter = 0;
	जबतक (str_p) अणु
		अगर (curve_counter == par->gamma.num_curves) अणु
			dev_err(par->info->device, "Gamma: Too many curves\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		curve_p = strsep(&str_p, "\n");
		value_counter = 0;
		जबतक (curve_p) अणु
			अगर (value_counter == par->gamma.num_values) अणु
				dev_err(par->info->device,
					"Gamma: Too many values\n");
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			ret = get_next_uदीर्घ(&curve_p, &val, " ", 16);
			अगर (ret)
				जाओ out;

			_count = curve_counter * par->gamma.num_values +
				 value_counter;
			curves[_count] = val;
			value_counter++;
		पूर्ण
		अगर (value_counter != par->gamma.num_values) अणु
			dev_err(par->info->device, "Gamma: Too few values\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		curve_counter++;
	पूर्ण
	अगर (curve_counter != par->gamma.num_curves) अणु
		dev_err(par->info->device, "Gamma: Too few curves\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

out:
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
प्र_लिखो_gamma(काष्ठा fbtft_par *par, u32 *curves, अक्षर *buf)
अणु
	sमाप_प्रकार len = 0;
	अचिन्हित पूर्णांक i, j;

	mutex_lock(&par->gamma.lock);
	क्रम (i = 0; i < par->gamma.num_curves; i++) अणु
		क्रम (j = 0; j < par->gamma.num_values; j++)
			len += scnम_लिखो(&buf[len], PAGE_SIZE,
			     "%04x ", curves[i * par->gamma.num_values + j]);
		buf[len - 1] = '\n';
	पूर्ण
	mutex_unlock(&par->gamma.lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार store_gamma_curve(काष्ठा device *device,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	काष्ठा fbtft_par *par = fb_info->par;
	u32 पंचांगp_curves[FBTFT_GAMMA_MAX_VALUES_TOTAL];
	पूर्णांक ret;

	ret = fbtft_gamma_parse_str(par, पंचांगp_curves, buf, count);
	अगर (ret)
		वापस ret;

	ret = par->fbtftops.set_gamma(par, पंचांगp_curves);
	अगर (ret)
		वापस ret;

	mutex_lock(&par->gamma.lock);
	स_नकल(par->gamma.curves, पंचांगp_curves,
	       par->gamma.num_curves * par->gamma.num_values *
	       माप(पंचांगp_curves[0]));
	mutex_unlock(&par->gamma.lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_gamma_curve(काष्ठा device *device,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	काष्ठा fbtft_par *par = fb_info->par;

	वापस प्र_लिखो_gamma(par, par->gamma.curves, buf);
पूर्ण

अटल काष्ठा device_attribute gamma_device_attrs[] = अणु
	__ATTR(gamma, 0660, show_gamma_curve, store_gamma_curve),
पूर्ण;

व्योम fbtft_expand_debug_value(अचिन्हित दीर्घ *debug)
अणु
	चयन (*debug & 0x7) अणु
	हाल 1:
		*debug |= DEBUG_LEVEL_1;
		अवरोध;
	हाल 2:
		*debug |= DEBUG_LEVEL_2;
		अवरोध;
	हाल 3:
		*debug |= DEBUG_LEVEL_3;
		अवरोध;
	हाल 4:
		*debug |= DEBUG_LEVEL_4;
		अवरोध;
	हाल 5:
		*debug |= DEBUG_LEVEL_5;
		अवरोध;
	हाल 6:
		*debug |= DEBUG_LEVEL_6;
		अवरोध;
	हाल 7:
		*debug = 0xFFFFFFFF;
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार store_debug(काष्ठा device *device,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	काष्ठा fbtft_par *par = fb_info->par;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &par->debug);
	अगर (ret)
		वापस ret;
	fbtft_expand_debug_value(&par->debug);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_debug(काष्ठा device *device,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(device);
	काष्ठा fbtft_par *par = fb_info->par;

	वापस sysfs_emit(buf, "%lu\n", par->debug);
पूर्ण

अटल काष्ठा device_attribute debug_device_attr =
	__ATTR(debug, 0660, show_debug, store_debug);

व्योम fbtft_sysfs_init(काष्ठा fbtft_par *par)
अणु
	device_create_file(par->info->dev, &debug_device_attr);
	अगर (par->gamma.curves && par->fbtftops.set_gamma)
		device_create_file(par->info->dev, &gamma_device_attrs[0]);
पूर्ण

व्योम fbtft_sysfs_निकास(काष्ठा fbtft_par *par)
अणु
	device_हटाओ_file(par->info->dev, &debug_device_attr);
	अगर (par->gamma.curves && par->fbtftops.set_gamma)
		device_हटाओ_file(par->info->dev, &gamma_device_attrs[0]);
पूर्ण
