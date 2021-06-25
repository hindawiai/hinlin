<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic System Framebuffers on x86
 * Copyright (c) 2012-2013 David Herrmann <dh.herrmann@gmail.com>
 */

/*
 * Simple-Framebuffer support क्रम x86 प्रणालीs
 * Create a platक्रमm-device क्रम any available boot framebuffer. The
 * simple-framebuffer platक्रमm device is alपढ़ोy available on DT प्रणालीs, so
 * this module parses the global "screen_info" object and creates a suitable
 * platक्रमm device compatible with the "simple-framebuffer" DT object. If
 * the framebuffer is incompatible, we instead create a legacy
 * "vesa-framebuffer", "efi-framebuffer" or "platform-framebuffer" device and
 * pass the screen_info as platक्रमm_data. This allows legacy drivers
 * to pick these devices up without messing with simple-framebuffer drivers.
 * The global "screen_info" is still valid at all बार.
 *
 * If CONFIG_X86_SYSFB is not selected, we never रेजिस्टर "simple-framebuffer"
 * platक्रमm devices, but only use legacy framebuffer devices क्रम
 * backwards compatibility.
 *
 * TODO: We set the dev_id field of all platक्रमm-devices to 0. This allows
 * other x86 OF/DT parsers to create such devices, too. However, they must
 * start at offset 1 क्रम this to work.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_data/simplefb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/screen_info.h>
#समावेश <यंत्र/sysfb.h>

अटल __init पूर्णांक sysfb_init(व्योम)
अणु
	काष्ठा screen_info *si = &screen_info;
	काष्ठा simplefb_platक्रमm_data mode;
	काष्ठा platक्रमm_device *pd;
	स्थिर अक्षर *name;
	bool compatible;
	पूर्णांक ret;

	sysfb_apply_efi_quirks();

	/* try to create a simple-framebuffer device */
	compatible = parse_mode(si, &mode);
	अगर (compatible) अणु
		ret = create_simplefb(si, &mode);
		अगर (!ret)
			वापस 0;
	पूर्ण

	/* अगर the FB is incompatible, create a legacy framebuffer device */
	अगर (si->orig_video_isVGA == VIDEO_TYPE_EFI)
		name = "efi-framebuffer";
	अन्यथा अगर (si->orig_video_isVGA == VIDEO_TYPE_VLFB)
		name = "vesa-framebuffer";
	अन्यथा
		name = "platform-framebuffer";

	pd = platक्रमm_device_रेजिस्टर_resndata(शून्य, name, 0,
					       शून्य, 0, si, माप(*si));
	वापस PTR_ERR_OR_ZERO(pd);
पूर्ण

/* must execute after PCI subप्रणाली क्रम EFI quirks */
device_initcall(sysfb_init);
