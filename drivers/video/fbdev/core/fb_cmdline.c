<शैली गुरु>
/*
 *  linux/drivers/video/fb_cmdline.c
 *
 *  Copyright (C) 2014 Intel Corp
 *  Copyright (C) 1994 Martin Schaller
 *
 *	2001 - Documented with DocBook
 *	- Brad Douglas <brad@neruo.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Authors:
 *    Vetter <danie.vetter@ffwll.ch>
 */
#समावेश <linux/init.h>
#समावेश <linux/fb.h>

अटल अक्षर *video_options[FB_MAX] __पढ़ो_mostly;
अटल पूर्णांक ofonly __पढ़ो_mostly;

स्थिर अक्षर *fb_mode_option;
EXPORT_SYMBOL_GPL(fb_mode_option);

/**
 * fb_get_options - get kernel boot parameters
 * @name:   framebuffer name as it would appear in
 *          the boot parameter line
 *          (video=<name>:<options>)
 * @option: the option will be stored here
 *
 * NOTE: Needed to मुख्यtain backwards compatibility
 */
पूर्णांक fb_get_options(स्थिर अक्षर *name, अक्षर **option)
अणु
	अक्षर *opt, *options = शून्य;
	पूर्णांक retval = 0;
	पूर्णांक name_len = म_माप(name), i;

	अगर (name_len && ofonly && म_भेदन(name, "offb", 4))
		retval = 1;

	अगर (name_len && !retval) अणु
		क्रम (i = 0; i < FB_MAX; i++) अणु
			अगर (video_options[i] == शून्य)
				जारी;
			अगर (!video_options[i][0])
				जारी;
			opt = video_options[i];
			अगर (!म_भेदन(name, opt, name_len) &&
			    opt[name_len] == ':')
				options = opt + name_len + 1;
		पूर्ण
	पूर्ण
	/* No match, pass global option */
	अगर (!options && option && fb_mode_option)
		options = kstrdup(fb_mode_option, GFP_KERNEL);
	अगर (options && !म_भेदन(options, "off", 3))
		retval = 1;

	अगर (option)
		*option = options;

	वापस retval;
पूर्ण
EXPORT_SYMBOL(fb_get_options);

/**
 *	video_setup - process command line options
 *	@options: string of options
 *
 *	Process command line options क्रम frame buffer subप्रणाली.
 *
 *	NOTE: This function is a __setup and __init function.
 *            It only stores the options.  Drivers have to call
 *            fb_get_options() as necessary.
 */
अटल पूर्णांक __init video_setup(अक्षर *options)
अणु
	अगर (!options || !*options)
		जाओ out;

	अगर (!म_भेदन(options, "ofonly", 6)) अणु
		ofonly = 1;
		जाओ out;
	पूर्ण

	अगर (म_अक्षर(options, ':')) अणु
		/* named */
		पूर्णांक i;

		क्रम (i = 0; i < FB_MAX; i++) अणु
			अगर (video_options[i] == शून्य) अणु
				video_options[i] = options;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* global */
		fb_mode_option = options;
	पूर्ण

out:
	वापस 1;
पूर्ण
__setup("video=", video_setup);
