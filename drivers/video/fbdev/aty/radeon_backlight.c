<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight code क्रम ATI Radeon based graphic cards
 *
 * Copyright (c) 2000 Ani Joshi <ajoshi@kernel.crashing.org>
 * Copyright (c) 2003 Benjamin Herrenschmidt <benh@kernel.crashing.org>
 * Copyright (c) 2006 Michael Hanselmann <linux-kernel@hansmi.ch>
 */

#समावेश "radeonfb.h"
#समावेश <linux/backlight.h>
#समावेश <linux/slab.h>

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
#समावेश <यंत्र/backlight.h>
#पूर्ण_अगर

#घोषणा MAX_RADEON_LEVEL 0xFF

काष्ठा radeon_bl_privdata अणु
	काष्ठा radeonfb_info *rinfo;
	uपूर्णांक8_t negative;
पूर्ण;

अटल पूर्णांक radeon_bl_get_level_brightness(काष्ठा radeon_bl_privdata *pdata,
		पूर्णांक level)
अणु
	पूर्णांक rlevel;

	/* Get and convert the value */
	/* No locking of bl_curve since we पढ़ो a single value */
	rlevel = pdata->rinfo->info->bl_curve[level] *
		 FB_BACKLIGHT_MAX / MAX_RADEON_LEVEL;

	अगर (rlevel < 0)
		rlevel = 0;
	अन्यथा अगर (rlevel > MAX_RADEON_LEVEL)
		rlevel = MAX_RADEON_LEVEL;

	अगर (pdata->negative)
		rlevel = MAX_RADEON_LEVEL - rlevel;

	वापस rlevel;
पूर्ण

अटल पूर्णांक radeon_bl_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा radeon_bl_privdata *pdata = bl_get_data(bd);
	काष्ठा radeonfb_info *rinfo = pdata->rinfo;
	u32 lvds_gen_cntl, पंचांगpPixclksCntl;
	पूर्णांक level;

	अगर (rinfo->mon1_type != MT_LCD)
		वापस 0;

	/* We turn off the LCD completely instead of just dimming the
	 * backlight. This provides some greater घातer saving and the display
	 * is useless without backlight anyway.
	 */
        अगर (bd->props.घातer != FB_BLANK_UNBLANK ||
	    bd->props.fb_blank != FB_BLANK_UNBLANK)
		level = 0;
	अन्यथा
		level = bd->props.brightness;

	del_समयr_sync(&rinfo->lvds_समयr);
	radeon_engine_idle();

	lvds_gen_cntl = INREG(LVDS_GEN_CNTL);
	अगर (level > 0) अणु
		lvds_gen_cntl &= ~LVDS_DISPLAY_DIS;
		अगर (!(lvds_gen_cntl & LVDS_BLON) || !(lvds_gen_cntl & LVDS_ON)) अणु
			lvds_gen_cntl |= (rinfo->init_state.lvds_gen_cntl & LVDS_DIGON);
			lvds_gen_cntl |= LVDS_BLON | LVDS_EN;
			OUTREG(LVDS_GEN_CNTL, lvds_gen_cntl);
			lvds_gen_cntl &= ~LVDS_BL_MOD_LEVEL_MASK;
			lvds_gen_cntl |=
				(radeon_bl_get_level_brightness(pdata, level) <<
				 LVDS_BL_MOD_LEVEL_SHIFT);
			lvds_gen_cntl |= LVDS_ON;
			lvds_gen_cntl |= (rinfo->init_state.lvds_gen_cntl & LVDS_BL_MOD_EN);
			rinfo->pending_lvds_gen_cntl = lvds_gen_cntl;
			mod_समयr(&rinfo->lvds_समयr,
				  jअगरfies + msecs_to_jअगरfies(rinfo->panel_info.pwr_delay));
		पूर्ण अन्यथा अणु
			lvds_gen_cntl &= ~LVDS_BL_MOD_LEVEL_MASK;
			lvds_gen_cntl |=
				(radeon_bl_get_level_brightness(pdata, level) <<
				 LVDS_BL_MOD_LEVEL_SHIFT);
			OUTREG(LVDS_GEN_CNTL, lvds_gen_cntl);
		पूर्ण
		rinfo->init_state.lvds_gen_cntl &= ~LVDS_STATE_MASK;
		rinfo->init_state.lvds_gen_cntl |= rinfo->pending_lvds_gen_cntl
			& LVDS_STATE_MASK;
	पूर्ण अन्यथा अणु
		/* Asic bug, when turning off LVDS_ON, we have to make sure
		   RADEON_PIXCLK_LVDS_ALWAYS_ON bit is off
		*/
		पंचांगpPixclksCntl = INPLL(PIXCLKS_CNTL);
		अगर (rinfo->is_mobility || rinfo->is_IGP)
			OUTPLLP(PIXCLKS_CNTL, 0, ~PIXCLK_LVDS_ALWAYS_ONb);
		lvds_gen_cntl &= ~(LVDS_BL_MOD_LEVEL_MASK | LVDS_BL_MOD_EN);
		lvds_gen_cntl |= (radeon_bl_get_level_brightness(pdata, 0) <<
				  LVDS_BL_MOD_LEVEL_SHIFT);
		lvds_gen_cntl |= LVDS_DISPLAY_DIS;
		OUTREG(LVDS_GEN_CNTL, lvds_gen_cntl);
		udelay(100);
		lvds_gen_cntl &= ~(LVDS_ON | LVDS_EN);
		OUTREG(LVDS_GEN_CNTL, lvds_gen_cntl);
		lvds_gen_cntl &= ~(LVDS_DIGON);
		rinfo->pending_lvds_gen_cntl = lvds_gen_cntl;
		mod_समयr(&rinfo->lvds_समयr,
			  jअगरfies + msecs_to_jअगरfies(rinfo->panel_info.pwr_delay));
		अगर (rinfo->is_mobility || rinfo->is_IGP)
			OUTPLL(PIXCLKS_CNTL, पंचांगpPixclksCntl);
	पूर्ण
	rinfo->init_state.lvds_gen_cntl &= ~LVDS_STATE_MASK;
	rinfo->init_state.lvds_gen_cntl |= (lvds_gen_cntl & LVDS_STATE_MASK);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops radeon_bl_data = अणु
	.update_status	= radeon_bl_update_status,
पूर्ण;

व्योम radeonfb_bl_init(काष्ठा radeonfb_info *rinfo)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bd;
	काष्ठा radeon_bl_privdata *pdata;
	अक्षर name[12];

	अगर (rinfo->mon1_type != MT_LCD)
		वापस;

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	अगर (!pmac_has_backlight_type("ati") &&
	    !pmac_has_backlight_type("mnca"))
		वापस;
#पूर्ण_अगर

	pdata = kदो_स्मृति(माप(काष्ठा radeon_bl_privdata), GFP_KERNEL);
	अगर (!pdata) अणु
		prपूर्णांकk("radeonfb: Memory allocation failed\n");
		जाओ error;
	पूर्ण

	snम_लिखो(name, माप(name), "radeonbl%d", rinfo->info->node);

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = FB_BACKLIGHT_LEVELS - 1;
	bd = backlight_device_रेजिस्टर(name, rinfo->info->dev, pdata,
				       &radeon_bl_data, &props);
	अगर (IS_ERR(bd)) अणु
		rinfo->info->bl_dev = शून्य;
		prपूर्णांकk("radeonfb: Backlight registration failed\n");
		जाओ error;
	पूर्ण

	pdata->rinfo = rinfo;

	/* Parकरोn me क्रम that hack... maybe some day we can figure out in what
	 * direction backlight should work on a given panel?
	 */
	pdata->negative =
		(rinfo->family != CHIP_FAMILY_RV200 &&
		 rinfo->family != CHIP_FAMILY_RV250 &&
		 rinfo->family != CHIP_FAMILY_RV280 &&
		 rinfo->family != CHIP_FAMILY_RV350);

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	pdata->negative = pdata->negative ||
		of_machine_is_compatible("PowerBook4,3") ||
		of_machine_is_compatible("PowerBook6,3") ||
		of_machine_is_compatible("PowerBook6,5");
#पूर्ण_अगर

	rinfo->info->bl_dev = bd;
	fb_bl_शेष_curve(rinfo->info, 0,
		 63 * FB_BACKLIGHT_MAX / MAX_RADEON_LEVEL,
		217 * FB_BACKLIGHT_MAX / MAX_RADEON_LEVEL);

	bd->props.brightness = bd->props.max_brightness;
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	prपूर्णांकk("radeonfb: Backlight initialized (%s)\n", name);

	वापस;

error:
	kमुक्त(pdata);
	वापस;
पूर्ण

व्योम radeonfb_bl_निकास(काष्ठा radeonfb_info *rinfo)
अणु
	काष्ठा backlight_device *bd = rinfo->info->bl_dev;

	अगर (bd) अणु
		काष्ठा radeon_bl_privdata *pdata;

		pdata = bl_get_data(bd);
		backlight_device_unरेजिस्टर(bd);
		kमुक्त(pdata);
		rinfo->info->bl_dev = शून्य;

		prपूर्णांकk("radeonfb: Backlight unloaded\n");
	पूर्ण
पूर्ण
