<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight code क्रम nVidia based graphic cards
 *
 * Copyright 2004 Antonino Daplas <adaplas@pol.net>
 * Copyright (c) 2006 Michael Hanselmann <linux-kernel@hansmi.ch>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/fb.h>
#समावेश <linux/pci.h>

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
#समावेश <यंत्र/backlight.h>
#पूर्ण_अगर

#समावेश "nv_local.h"
#समावेश "nv_type.h"
#समावेश "nv_proto.h"

/* We करो not have any inक्रमmation about which values are allowed, thus
 * we used safe values.
 */
#घोषणा MIN_LEVEL 0x158
#घोषणा MAX_LEVEL 0x534
#घोषणा LEVEL_STEP ((MAX_LEVEL - MIN_LEVEL) / FB_BACKLIGHT_MAX)

अटल पूर्णांक nvidia_bl_get_level_brightness(काष्ठा nvidia_par *par,
		पूर्णांक level)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(par->pci_dev);
	पूर्णांक nlevel;

	/* Get and convert the value */
	/* No locking of bl_curve since we पढ़ो a single value */
	nlevel = MIN_LEVEL + info->bl_curve[level] * LEVEL_STEP;

	अगर (nlevel < 0)
		nlevel = 0;
	अन्यथा अगर (nlevel < MIN_LEVEL)
		nlevel = MIN_LEVEL;
	अन्यथा अगर (nlevel > MAX_LEVEL)
		nlevel = MAX_LEVEL;

	वापस nlevel;
पूर्ण

अटल पूर्णांक nvidia_bl_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा nvidia_par *par = bl_get_data(bd);
	u32 पंचांगp_pcrt, पंचांगp_pmc, fpcontrol;
	पूर्णांक level;

	अगर (!par->FlatPanel)
		वापस 0;

	अगर (bd->props.घातer != FB_BLANK_UNBLANK ||
	    bd->props.fb_blank != FB_BLANK_UNBLANK)
		level = 0;
	अन्यथा
		level = bd->props.brightness;

	पंचांगp_pmc = NV_RD32(par->PMC, 0x10F0) & 0x0000FFFF;
	पंचांगp_pcrt = NV_RD32(par->PCRTC0, 0x081C) & 0xFFFFFFFC;
	fpcontrol = NV_RD32(par->PRAMDAC, 0x0848) & 0xCFFFFFCC;

	अगर (level > 0) अणु
		पंचांगp_pcrt |= 0x1;
		पंचांगp_pmc |= (1 << 31); /* backlight bit */
		पंचांगp_pmc |= nvidia_bl_get_level_brightness(par, level) << 16;
		fpcontrol |= par->fpSyncs;
	पूर्ण अन्यथा
		fpcontrol |= 0x20000022;

	NV_WR32(par->PCRTC0, 0x081C, पंचांगp_pcrt);
	NV_WR32(par->PMC, 0x10F0, पंचांगp_pmc);
	NV_WR32(par->PRAMDAC, 0x848, fpcontrol);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops nvidia_bl_ops = अणु
	.update_status	= nvidia_bl_update_status,
पूर्ण;

व्योम nvidia_bl_init(काष्ठा nvidia_par *par)
अणु
	काष्ठा backlight_properties props;
	काष्ठा fb_info *info = pci_get_drvdata(par->pci_dev);
	काष्ठा backlight_device *bd;
	अक्षर name[12];

	अगर (!par->FlatPanel)
		वापस;

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	अगर (!machine_is(घातermac) ||
	    !pmac_has_backlight_type("mnca"))
		वापस;
#पूर्ण_अगर

	snम_लिखो(name, माप(name), "nvidiabl%d", info->node);

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = FB_BACKLIGHT_LEVELS - 1;
	bd = backlight_device_रेजिस्टर(name, info->dev, par, &nvidia_bl_ops,
				       &props);
	अगर (IS_ERR(bd)) अणु
		info->bl_dev = शून्य;
		prपूर्णांकk(KERN_WARNING "nvidia: Backlight registration failed\n");
		जाओ error;
	पूर्ण

	info->bl_dev = bd;
	fb_bl_शेष_curve(info, 0,
		0x158 * FB_BACKLIGHT_MAX / MAX_LEVEL,
		0x534 * FB_BACKLIGHT_MAX / MAX_LEVEL);

	bd->props.brightness = bd->props.max_brightness;
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	prपूर्णांकk("nvidia: Backlight initialized (%s)\n", name);

error:
	वापस;
पूर्ण

व्योम nvidia_bl_निकास(काष्ठा nvidia_par *par)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(par->pci_dev);
	काष्ठा backlight_device *bd = info->bl_dev;

	backlight_device_unरेजिस्टर(bd);
	prपूर्णांकk("nvidia: Backlight unloaded\n");
पूर्ण
