<शैली गुरु>
/*
 *  linux/drivers/video/macmodes.c -- Standard MacOS video modes
 *
 *	Copyright (C) 1998 Geert Uytterhoeven
 *
 *      2000 - Removal of OpenFirmware dependencies by:
 *      - Ani Joshi
 *      - Brad Douglas <brad@neruo.com>
 *
 *	2001 - Documented with DocBook
 *	- Brad Douglas <brad@neruo.com>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>

#समावेश "macmodes.h"

    /*
     *  MacOS video mode definitions
     *
     *  Order IS important! If you change these, करोn't क्रमget to update
     *  mac_modes[] below!
     */

#घोषणा DEFAULT_MODEDB_INDEX	0

अटल स्थिर काष्ठा fb_videomode mac_modedb[] = अणु
    अणु
	/* 512x384, 60Hz, Non-Interlaced (15.67 MHz करोt घड़ी) */
	"mac2", 60, 512, 384, 63828, 80, 16, 19, 1, 32, 3,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 640x480, 60 Hz, Non-Interlaced (25.175 MHz करोtघड़ी) */
	"mac5", 60, 640, 480, 39722, 32, 32, 33, 10, 96, 2,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 640x480, 67Hz, Non-Interlaced (30.0 MHz करोtघड़ी) */
	"mac6", 67, 640, 480, 33334, 80, 80, 39, 3, 64, 3,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 640x870, 75Hz (portrait), Non-Interlaced (57.28 MHz करोt घड़ी) */
	"mac7", 75, 640, 870, 17457, 80, 32, 42, 3, 80, 3,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 800x600, 56 Hz, Non-Interlaced (36.00 MHz करोtघड़ी) */
	"mac9", 56, 800, 600, 27778, 112, 40, 22, 1, 72, 2,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 800x600, 60 Hz, Non-Interlaced (40.00 MHz करोtघड़ी) */
	"mac10", 60, 800, 600, 25000, 72, 56, 23, 1, 128, 4,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 800x600, 72 Hz, Non-Interlaced (50.00 MHz करोtघड़ी) */
	"mac11", 72, 800, 600, 20000, 48, 72, 23, 37, 120, 6,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 800x600, 75 Hz, Non-Interlaced (49.50 MHz करोtघड़ी) */
	"mac12", 75, 800, 600, 20203, 144, 32, 21, 1, 80, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 832x624, 75Hz, Non-Interlaced (57.6 MHz करोtघड़ी) */
	"mac13", 75, 832, 624, 17362, 208, 48, 39, 1, 64, 3,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1024x768, 60 Hz, Non-Interlaced (65.00 MHz करोtघड़ी) */
	"mac14", 60, 1024, 768, 15385, 144, 40, 29, 3, 136, 6,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1024x768, 72 Hz, Non-Interlaced (75.00 MHz करोtघड़ी) */
	"mac15", 72, 1024, 768, 13334, 128, 40, 29, 3, 136, 6,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1024x768, 75 Hz, Non-Interlaced (78.75 MHz करोtघड़ी) */
	"mac16", 75, 1024, 768, 12699, 176, 16, 28, 1, 96, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1024x768, 75 Hz, Non-Interlaced (78.75 MHz करोtघड़ी) */
	"mac17", 75, 1024, 768, 12699, 160, 32, 28, 1, 96, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1152x870, 75 Hz, Non-Interlaced (100.0 MHz करोtघड़ी) */
	"mac18", 75, 1152, 870, 10000, 128, 48, 39, 3, 128, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1280x960, 75 Hz, Non-Interlaced (126.00 MHz करोtघड़ी) */
	"mac19", 75, 1280, 960, 7937, 224, 32, 36, 1, 144, 3,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1280x1024, 75 Hz, Non-Interlaced (135.00 MHz करोtघड़ी) */
	"mac20", 75, 1280, 1024, 7408, 232, 64, 38, 1, 112, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1152x768, 60 Hz, Titanium PowerBook */
	"mac21", 60, 1152, 768, 15386, 158, 26, 29, 3, 136, 6,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1600x1024, 60 Hz, Non-Interlaced (112.27 MHz करोtघड़ी) */
	"mac22", 60, 1600, 1024, 8908, 88, 104, 1, 10, 16, 1,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    पूर्ण

#अगर 0
    /* Anyone who has timings क्रम these? */
    अणु
	/* VMODE_512_384_60I: 512x384, 60Hz, Interlaced (NTSC) */
	"mac1", 60, 512, 384, pixघड़ी, left, right, upper, lower, hslen, vslen,
	sync, FB_VMODE_INTERLACED
    पूर्ण, अणु
	/* VMODE_640_480_50I: 640x480, 50Hz, Interlaced (PAL) */
	"mac3", 50, 640, 480, pixघड़ी, left, right, upper, lower, hslen, vslen,
	sync, FB_VMODE_INTERLACED
    पूर्ण, अणु
	/* VMODE_640_480_60I: 640x480, 60Hz, Interlaced (NTSC) */
	"mac4", 60, 640, 480, pixघड़ी, left, right, upper, lower, hslen, vslen,
	sync, FB_VMODE_INTERLACED
    पूर्ण, अणु
	/* VMODE_768_576_50I: 768x576, 50Hz (PAL full frame), Interlaced */
	"mac8", 50, 768, 576, pixघड़ी, left, right, upper, lower, hslen, vslen,
	sync, FB_VMODE_INTERLACED
    पूर्ण,
#पूर्ण_अगर
पूर्ण;


    /*
     *  Mapping between MacOS video mode numbers and video mode definitions
     *
     *  These MUST be ordered in
     *    - increasing resolution
     *    - decreasing pixel घड़ी period
     */

अटल स्थिर काष्ठा mode_map अणु
    पूर्णांक vmode;
    स्थिर काष्ठा fb_videomode *mode;
पूर्ण mac_modes[] = अणु
    /* 512x384 */
    अणु VMODE_512_384_60, &mac_modedb[0] पूर्ण,
    /* 640x480 */
    अणु VMODE_640_480_60, &mac_modedb[1] पूर्ण,
    अणु VMODE_640_480_67, &mac_modedb[2] पूर्ण,
    /* 640x870 */
    अणु VMODE_640_870_75P, &mac_modedb[3] पूर्ण,
    /* 800x600 */
    अणु VMODE_800_600_56, &mac_modedb[4] पूर्ण,
    अणु VMODE_800_600_60, &mac_modedb[5] पूर्ण,
    अणु VMODE_800_600_75, &mac_modedb[7] पूर्ण,
    अणु VMODE_800_600_72, &mac_modedb[6] पूर्ण,
    /* 832x624 */
    अणु VMODE_832_624_75, &mac_modedb[8] पूर्ण,
    /* 1024x768 */
    अणु VMODE_1024_768_60, &mac_modedb[9] पूर्ण,
    अणु VMODE_1024_768_70, &mac_modedb[10] पूर्ण,
    अणु VMODE_1024_768_75V, &mac_modedb[11] पूर्ण,
    अणु VMODE_1024_768_75, &mac_modedb[12] पूर्ण,
    /* 1152x768 */
    अणु VMODE_1152_768_60, &mac_modedb[16] पूर्ण,
    /* 1152x870 */
    अणु VMODE_1152_870_75, &mac_modedb[13] पूर्ण,
    /* 1280x960 */
    अणु VMODE_1280_960_75, &mac_modedb[14] पूर्ण,
    /* 1280x1024 */
    अणु VMODE_1280_1024_75, &mac_modedb[15] पूर्ण,
    /* 1600x1024 */
    अणु VMODE_1600_1024_60, &mac_modedb[17] पूर्ण,
    अणु -1, शून्य पूर्ण
पूर्ण;


    /*
     *  Mapping between monitor sense values and MacOS video mode numbers
     */

अटल स्थिर काष्ठा monitor_map अणु
    पूर्णांक sense;
    पूर्णांक vmode;
पूर्ण mac_monitors[] = अणु
    अणु 0x000, VMODE_1280_1024_75 पूर्ण,	/* 21" RGB */
    अणु 0x114, VMODE_640_870_75P पूर्ण,	/* Portrait Monochrome */
    अणु 0x221, VMODE_512_384_60 पूर्ण,	/* 12" RGB*/
    अणु 0x331, VMODE_1280_1024_75 पूर्ण,	/* 21" RGB (Radius) */
    अणु 0x334, VMODE_1280_1024_75 पूर्ण,	/* 21" mono (Radius) */
    अणु 0x335, VMODE_1280_1024_75 पूर्ण,	/* 21" mono */
    अणु 0x40A, VMODE_640_480_60I पूर्ण,	/* NTSC */
    अणु 0x51E, VMODE_640_870_75P पूर्ण,	/* Portrait RGB */
    अणु 0x603, VMODE_832_624_75 पूर्ण,	/* 12"-16" multiscan */
    अणु 0x60b, VMODE_1024_768_70 पूर्ण,	/* 13"-19" multiscan */
    अणु 0x623, VMODE_1152_870_75 पूर्ण,	/* 13"-21" multiscan */
    अणु 0x62b, VMODE_640_480_67 पूर्ण,	/* 13"/14" RGB */
    अणु 0x700, VMODE_640_480_50I पूर्ण,	/* PAL */
    अणु 0x714, VMODE_640_480_60I पूर्ण,	/* NTSC */
    अणु 0x717, VMODE_800_600_75 पूर्ण,	/* VGA */
    अणु 0x72d, VMODE_832_624_75 पूर्ण,	/* 16" RGB (Goldfish) */
    अणु 0x730, VMODE_768_576_50I पूर्ण,	/* PAL (Alternate) */
    अणु 0x73a, VMODE_1152_870_75 पूर्ण,	/* 3rd party 19" */
    अणु 0x73f, VMODE_640_480_67 पूर्ण,	/* no sense lines connected at all */
    अणु 0xBEEF, VMODE_1600_1024_60 पूर्ण,	/* 22" Apple Cinema Display */
    अणु -1,    VMODE_640_480_60 पूर्ण,	/* catch-all, must be last */
पूर्ण;

/**
 *	mac_vmode_to_var - converts vmode/cmode pair to var काष्ठाure
 *	@vmode: MacOS video mode
 *	@cmode: MacOS color mode
 *	@var: frame buffer video mode काष्ठाure
 *
 *	Converts a MacOS vmode/cmode pair to a frame buffer video
 *	mode काष्ठाure.
 *
 *	Returns negative त्रुटि_सं on error, or zero क्रम success.
 *
 */

पूर्णांक mac_vmode_to_var(पूर्णांक vmode, पूर्णांक cmode, काष्ठा fb_var_screeninfo *var)
अणु
    स्थिर काष्ठा fb_videomode *mode = शून्य;
    स्थिर काष्ठा mode_map *map;

    क्रम (map = mac_modes; map->vmode != -1; map++)
	अगर (map->vmode == vmode) अणु
	    mode = map->mode;
	    अवरोध;
	पूर्ण
    अगर (!mode)
	वापस -EINVAL;

    स_रखो(var, 0, माप(काष्ठा fb_var_screeninfo));
    चयन (cmode) अणु
	हाल CMODE_8:
	    var->bits_per_pixel = 8;
	    var->red.offset = 0;
	    var->red.length = 8;   
	    var->green.offset = 0;
	    var->green.length = 8;
	    var->blue.offset = 0;
	    var->blue.length = 8;
	    अवरोध;

	हाल CMODE_16:
	    var->bits_per_pixel = 16;
	    var->red.offset = 10;
	    var->red.length = 5;
	    var->green.offset = 5;
	    var->green.length = 5;
	    var->blue.offset = 0;
	    var->blue.length = 5;
	    अवरोध;

	हाल CMODE_32:
	    var->bits_per_pixel = 32;
	    var->red.offset = 16;
	    var->red.length = 8;
	    var->green.offset = 8;
	    var->green.length = 8;
	    var->blue.offset = 0;
	    var->blue.length = 8;
	    var->transp.offset = 24;
	    var->transp.length = 8;
	    अवरोध;

	शेष:
	    वापस -EINVAL;
    पूर्ण
    var->xres = mode->xres;
    var->yres = mode->yres;
    var->xres_भव = mode->xres;
    var->yres_भव = mode->yres;
    var->height = -1;
    var->width = -1;
    var->pixघड़ी = mode->pixघड़ी;
    var->left_margin = mode->left_margin;
    var->right_margin = mode->right_margin;
    var->upper_margin = mode->upper_margin;
    var->lower_margin = mode->lower_margin;
    var->hsync_len = mode->hsync_len;
    var->vsync_len = mode->vsync_len;
    var->sync = mode->sync;
    var->vmode = mode->vmode;
    वापस 0;
पूर्ण
EXPORT_SYMBOL(mac_vmode_to_var);

/**
 *	mac_var_to_vmode - convert var काष्ठाure to MacOS vmode/cmode pair
 *	@var: frame buffer video mode काष्ठाure
 *	@vmode: MacOS video mode
 *	@cmode: MacOS color mode
 *
 *	Converts a frame buffer video mode काष्ठाure to a MacOS
 *	vmode/cmode pair.
 *
 *	Returns negative त्रुटि_सं on error, or zero क्रम success.
 *
 */

पूर्णांक mac_var_to_vmode(स्थिर काष्ठा fb_var_screeninfo *var, पूर्णांक *vmode,
		     पूर्णांक *cmode)
अणु
    स्थिर काष्ठा mode_map *map;

    अगर (var->bits_per_pixel <= 8)
	*cmode = CMODE_8;
    अन्यथा अगर (var->bits_per_pixel <= 16)
	*cmode = CMODE_16;
    अन्यथा अगर (var->bits_per_pixel <= 32)
	*cmode = CMODE_32;
    अन्यथा
	वापस -EINVAL;

    /*
     * Find the mac_mode with a matching resolution or failing that, the
     * बंदst larger resolution. Skip modes with a लघुer pixel घड़ी period.
     */
    क्रम (map = mac_modes; map->vmode != -1; map++) अणु
	स्थिर काष्ठा fb_videomode *mode = map->mode;

	अगर (var->xres > mode->xres || var->yres > mode->yres)
	    जारी;
	अगर (var->xres_भव > mode->xres || var->yres_भव > mode->yres)
	    जारी;
	अगर (var->pixघड़ी > mode->pixघड़ी)
	    जारी;
	अगर ((var->vmode & FB_VMODE_MASK) != mode->vmode)
	    जारी;
	*vmode = map->vmode;

	/*
	 * Having found a good resolution, find the matching pixel घड़ी
	 * or failing that, the बंदst दीर्घer pixel घड़ी period.
	 */
	map++;
	जबतक (map->vmode != -1) अणु
	    स्थिर काष्ठा fb_videomode *clk_mode = map->mode;

	    अगर (mode->xres != clk_mode->xres || mode->yres != clk_mode->yres)
		अवरोध;
	    अगर (var->pixघड़ी > mode->pixघड़ी)
	        अवरोध;
	    अगर (mode->vmode != clk_mode->vmode)
		जारी;
	    *vmode = map->vmode;
	    map++;
	पूर्ण
	वापस 0;
    पूर्ण
    वापस -EINVAL;
पूर्ण

/**
 *	mac_map_monitor_sense - Convert monitor sense to vmode
 *	@sense: Macपूर्णांकosh monitor sense number
 *
 *	Converts a Macपूर्णांकosh monitor sense number to a MacOS
 *	vmode number.
 *
 *	Returns MacOS vmode video mode number.
 *
 */

पूर्णांक mac_map_monitor_sense(पूर्णांक sense)
अणु
    स्थिर काष्ठा monitor_map *map;

    क्रम (map = mac_monitors; map->sense != -1; map++)
	अगर (map->sense == sense)
	    अवरोध;
    वापस map->vmode;
पूर्ण
EXPORT_SYMBOL(mac_map_monitor_sense);

/**
 *	mac_find_mode - find a video mode
 *	@var: frame buffer user defined part of display
 *	@info: frame buffer info काष्ठाure
 *	@mode_option: video mode name (see mac_modedb[])
 *	@शेष_bpp: शेष color depth in bits per pixel
 *
 *	Finds a suitable video mode.  Tries to set mode specअगरied
 *	by @mode_option.  If the name of the wanted mode begins with
 *	'mac', the Mac video mode database will be used, otherwise it
 *	will fall back to the standard video mode database.
 *
 *	Note: Function marked as __init and can only be used during
 *	प्रणाली boot.
 *
 *	Returns error code from fb_find_mode (see fb_find_mode
 *	function).
 *
 */

पूर्णांक mac_find_mode(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info,
		  स्थिर अक्षर *mode_option, अचिन्हित पूर्णांक शेष_bpp)
अणु
    स्थिर काष्ठा fb_videomode *db = शून्य;
    अचिन्हित पूर्णांक dbsize = 0;

    अगर (mode_option && !म_भेदन(mode_option, "mac", 3)) अणु
	mode_option += 3;
	db = mac_modedb;
	dbsize = ARRAY_SIZE(mac_modedb);
    पूर्ण
    वापस fb_find_mode(var, info, mode_option, db, dbsize,
			&mac_modedb[DEFAULT_MODEDB_INDEX], शेष_bpp);
पूर्ण
EXPORT_SYMBOL(mac_find_mode);

MODULE_LICENSE("GPL");
