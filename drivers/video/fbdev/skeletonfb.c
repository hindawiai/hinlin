<शैली गुरु>
/*
 * linux/drivers/video/skeletonfb.c -- Skeleton क्रम a frame buffer device
 *
 *  Modअगरied to new api Jan 2001 by James Simmons (jsimmons@transभव.com)
 *
 *  Created 28 Dec 1997 by Geert Uytterhoeven
 *
 *
 *  I have started rewriting this driver as a example of the upcoming new API
 *  The primary goal is to हटाओ the console code from fbdev and place it
 *  पूर्णांकo fbcon.c. This reduces the code and makes writing a new fbdev driver
 *  easy since the author करोesn't need to worry about console पूर्णांकernals. It
 *  also allows the ability to run fbdev without a console/tty प्रणाली on top 
 *  of it. 
 *
 *  First the roles of काष्ठा fb_info and काष्ठा display have changed. Struct
 *  display will go away. The way the new framebuffer console code will
 *  work is that it will act to translate data about the tty/console in 
 *  काष्ठा vc_data to data in a device independent way in काष्ठा fb_info. Then
 *  various functions in काष्ठा fb_ops will be called to store the device 
 *  dependent state in the par field in काष्ठा fb_info and to change the 
 *  hardware to that state. This allows a very clean separation of the fbdev
 *  layer from the console layer. It also allows one to use fbdev on its own
 *  which is a bounus क्रम embedded devices. The reason this approach works is  
 *  क्रम each framebuffer device when used as a tty/console device is allocated
 *  a set of भव terminals to it. Only one भव terminal can be active 
 *  per framebuffer device. We alपढ़ोy have all the data we need in काष्ठा 
 *  vc_data so why store a bunch of colormaps and other fbdev specअगरic data
 *  per भव terminal. 
 *
 *  As you can see करोing this makes the con parameter pretty much useless
 *  क्रम काष्ठा fb_ops functions, as it should be. Also having काष्ठा  
 *  fb_var_screeninfo and other data in fb_info pretty much eliminates the 
 *  need क्रम get_fix and get_var. Once all drivers use the fix, var, and cmap
 *  fbcon can be written around these fields. This will also eliminate the
 *  need to regenerate काष्ठा fb_var_screeninfo, काष्ठा fb_fix_screeninfo
 *  काष्ठा fb_cmap every समय get_var, get_fix, get_cmap functions are called
 *  as many drivers करो now. 
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

    /*
     *  This is just simple sample code.
     *
     *  No warranty that it actually compiles.
     *  Even less warranty that it actually works :-)
     */

/*
 * Driver data
 */
अटल अक्षर *mode_option;

/*
 *  If your driver supports multiple boards, you should make the  
 *  below data types arrays, or allocate them dynamically (using kदो_स्मृति()). 
 */ 

/* 
 * This काष्ठाure defines the hardware state of the graphics card. Normally
 * you place this in a header file in linux/include/video. This file usually
 * also includes रेजिस्टर inक्रमmation. That allows other driver subप्रणालीs
 * and userland applications the ability to use the same header file to 
 * aव्योम duplicate work and easy porting of software. 
 */
काष्ठा xxx_par;

/*
 * Here we define the शेष काष्ठाs fb_fix_screeninfo and fb_var_screeninfo
 * अगर we करोn't use modedb. If we करो use modedb see xxxfb_init how to use it
 * to get a fb_var_screeninfo. Otherwise define a शेष var as well. 
 */
अटल स्थिर काष्ठा fb_fix_screeninfo xxxfb_fix = अणु
	.id =		"FB's name", 
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_PSEUDOCOLOR,
	.xpanstep =	1,
	.ypanstep =	1,
	.ywrapstep =	1, 
	.accel =	FB_ACCEL_NONE,
पूर्ण;

    /*
     * 	Modern graphical hardware not only supports pipelines but some 
     *  also support multiple monitors where each display can have its  
     *  its own unique data. In this हाल each display could be  
     *  represented by a separate framebuffer device thus a separate 
     *  काष्ठा fb_info. Now the काष्ठा xxx_par represents the graphics
     *  hardware state thus only one exist per card. In this हाल the 
     *  काष्ठा xxx_par क्रम each graphics card would be shared between 
     *  every काष्ठा fb_info that represents a framebuffer on that card. 
     *  This allows when one display changes it video resolution (info->var) 
     *  the other displays know instantly. Each display can always be
     *  aware of the entire hardware state that affects it because they share
     *  the same xxx_par काष्ठा. The other side of the coin is multiple
     *  graphics cards that pass data around until it is finally displayed
     *  on one monitor. Such examples are the vooकरोo 1 cards and high end
     *  NUMA graphics servers. For this हाल we have a bunch of pars, each
     *  one that represents a graphics state, that beदीर्घ to one काष्ठा 
     *  fb_info. Their you would want to have *par poपूर्णांक to a array of device
     *  states and have each काष्ठा fb_ops function deal with all those 
     *  states. I hope this covers every possible hardware design. If not
     *  feel मुक्त to send your ideas at jsimmons@users.sf.net 
     */

    /*
     *  If your driver supports multiple boards or it supports multiple 
     *  framebuffers, you should make these arrays, or allocate them 
     *  dynamically using framebuffer_alloc() and मुक्त them with
     *  framebuffer_release().
     */ 
अटल काष्ठा fb_info info;

    /* 
     * Each one represents the state of the hardware. Most hardware have
     * just one hardware state. These here represent the शेष state(s). 
     */
अटल काष्ठा xxx_par __initdata current_par;

पूर्णांक xxxfb_init(व्योम);

/**
 *	xxxfb_खोलो - Optional function. Called when the framebuffer is
 *		     first accessed.
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *	@user: tell us अगर the userland (value=1) or the console is accessing
 *	       the framebuffer. 
 *
 *	This function is the first function called in the framebuffer api.
 *	Usually you करोn't need to provide this function. The हाल where it 
 *	is used is to change from a text mode hardware state to a graphics
 * 	mode state. 
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक xxxfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
    वापस 0;
पूर्ण

/**
 *	xxxfb_release - Optional function. Called when the framebuffer 
 *			device is बंदd. 
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *	@user: tell us अगर the userland (value=1) or the console is accessing
 *	       the framebuffer. 
 *	
 *	Thus function is called when we बंद /dev/fb or the framebuffer 
 *	console प्रणाली is released. Usually you करोn't need this function.
 *	The हाल where it is usually used is to go from a graphics state
 *	to a text mode state.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक xxxfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
    वापस 0;
पूर्ण

/**
 *      xxxfb_check_var - Optional function. Validates a var passed in. 
 *      @var: frame buffer variable screen काष्ठाure
 *      @info: frame buffer काष्ठाure that represents a single frame buffer 
 *
 *	Checks to see अगर the hardware supports the state requested by
 *	var passed in. This function करोes not alter the hardware state!!! 
 *	This means the data stored in काष्ठा fb_info and काष्ठा xxx_par करो 
 *      not change. This includes the var inside of काष्ठा fb_info. 
 *	Do NOT change these. This function can be called on its own अगर we
 *	पूर्णांकent to only test a mode and not actually set it. The stuff in 
 *	modedb.c is a example of this. If the var passed in is slightly 
 *	off by what the hardware can support then we alter the var PASSED in
 *	to what we can करो.
 *
 *      For values that are off, this function must round them _up_ to the
 *      next value that is supported by the hardware.  If the value is
 *      greater than the highest value supported by the hardware, then this
 *      function must वापस -EINVAL.
 *
 *      Exception to the above rule:  Some drivers have a fixed mode, ie,
 *      the hardware is alपढ़ोy set at boot up, and cannot be changed.  In
 *      this हाल, it is more acceptable that this function just वापस
 *      a copy of the currently working var (info->var). Better is to not
 *      implement this function, as the upper layer will करो the copying
 *      of the current var क्रम you.
 *
 *      Note:  This is the only function where the contents of var can be
 *      मुक्तly adjusted after the driver has been रेजिस्टरed. If you find
 *      that you have code outside of this function that alters the content
 *      of var, then you are करोing something wrong.  Note also that the
 *      contents of info->var must be left untouched at all बार after
 *      driver registration.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक xxxfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
    /* ... */
    वापस 0;	   	
पूर्ण

/**
 *      xxxfb_set_par - Optional function. Alters the hardware state.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Using the fb_var_screeninfo in fb_info we set the resolution of the
 *	this particular framebuffer. This function alters the par AND the
 *	fb_fix_screeninfo stored in fb_info. It करोesn't not alter var in 
 *	fb_info since we are using that data. This means we depend on the
 *	data in var inside fb_info to be supported by the hardware. 
 *
 *      This function is also used to recover/restore the hardware to a
 *      known working state.
 *
 *	xxxfb_check_var is always called beक्रमe xxxfb_set_par to ensure that
 *      the contents of var is always valid.
 *
 *	Again अगर you can't change the resolution you don't need this function.
 *
 *      However, even अगर your hardware करोes not support mode changing,
 *      a set_par might be needed to at least initialize the hardware to
 *      a known working state, especially अगर it came back from another
 *      process that also modअगरies the same hardware, such as X.
 *
 *      If this is the हाल, a combination such as the following should work:
 *
 *      अटल पूर्णांक xxxfb_check_var(काष्ठा fb_var_screeninfo *var,
 *                                काष्ठा fb_info *info)
 *      अणु
 *              *var = info->var;
 *              वापस 0;
 *      पूर्ण
 *
 *      अटल पूर्णांक xxxfb_set_par(काष्ठा fb_info *info)
 *      अणु
 *              init your hardware here
 *      पूर्ण
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक xxxfb_set_par(काष्ठा fb_info *info)
अणु
    काष्ठा xxx_par *par = info->par;
    /* ... */
    वापस 0;	
पूर्ण

/**
 *  	xxxfb_setcolreg - Optional function. Sets a color रेजिस्टर.
 *      @regno: Which रेजिस्टर in the CLUT we are programming 
 *      @red: The red value which can be up to 16 bits wide 
 *	@green: The green value which can be up to 16 bits wide 
 *	@blue:  The blue value which can be up to 16 bits wide.
 *	@transp: If supported, the alpha value which can be up to 16 bits wide.
 *      @info: frame buffer info काष्ठाure
 * 
 *  	Set a single color रेजिस्टर. The values supplied have a 16 bit
 *  	magnitude which needs to be scaled in this function क्रम the hardware. 
 *	Things to take पूर्णांकo consideration are how many color रेजिस्टरs, अगर
 *	any, are supported with the current color visual. With truecolor mode
 *	no color palettes are supported. Here a pseuकरो palette is created
 *	which we store the value in pseuकरो_palette in काष्ठा fb_info. For
 *	pseuकरोcolor mode we have a limited color palette. To deal with this
 *	we can program what color is displayed क्रम a particular pixel value.
 *	DirectColor is similar in that we can program each color field. If
 *	we have a अटल colormap we करोn't need to implement this function. 
 * 
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक xxxfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
    अगर (regno >= 256)  /* no. of hw रेजिस्टरs */
       वापस -EINVAL;
    /*
     * Program hardware... करो anything you want with transp
     */

    /* grayscale works only partially under directcolor */
    अगर (info->var.grayscale) अणु
       /* grayscale = 0.30*R + 0.59*G + 0.11*B */
       red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
    पूर्ण

    /* Directcolor:
     *   var->अणुcolorपूर्ण.offset contains start of bitfield
     *   var->अणुcolorपूर्ण.length contains length of bitfield
     *   अणुhardwarespecअगरicपूर्ण contains width of DAC
     *   pseuकरो_palette[X] is programmed to (X << red.offset) |
     *                                      (X << green.offset) |
     *                                      (X << blue.offset)
     *   RAMDAC[X] is programmed to (red, green, blue)
     *   color depth = SUM(var->अणुcolorपूर्ण.length)
     *
     * Pseuकरोcolor:
     *    var->अणुcolorपूर्ण.offset is 0 unless the palette index takes less than
     *                        bits_per_pixel bits and is stored in the upper
     *                        bits of the pixel value
     *    var->अणुcolorपूर्ण.length is set so that 1 << length is the number of
     *                        available palette entries
     *    pseuकरो_palette is not used
     *    RAMDAC[X] is programmed to (red, green, blue)
     *    color depth = var->अणुcolorपूर्ण.length
     *
     * Static pseuकरोcolor:
     *    same as Pseuकरोcolor, but the RAMDAC is not programmed (पढ़ो-only)
     *
     * Mono01/Mono10:
     *    Has only 2 values, black on white or white on black (fg on bg),
     *    var->अणुcolorपूर्ण.offset is 0
     *    white = (1 << var->अणुcolorपूर्ण.length) - 1, black = 0
     *    pseuकरो_palette is not used
     *    RAMDAC करोes not exist
     *    color depth is always 2
     *
     * Truecolor:
     *    करोes not use RAMDAC (usually has 3 of them).
     *    var->अणुcolorपूर्ण.offset contains start of bitfield
     *    var->अणुcolorपूर्ण.length contains length of bitfield
     *    pseuकरो_palette is programmed to (red << red.offset) |
     *                                    (green << green.offset) |
     *                                    (blue << blue.offset) |
     *                                    (transp << transp.offset)
     *    RAMDAC करोes not exist
     *    color depth = SUM(var->अणुcolorपूर्ण.lengthपूर्ण)
     *
     *  The color depth is used by fbcon क्रम choosing the logo and also
     *  क्रम color palette transक्रमmation अगर color depth < 4
     *
     *  As can be seen from the above, the field bits_per_pixel is _NOT_
     *  a criteria क्रम describing the color visual.
     *
     *  A common mistake is assuming that bits_per_pixel <= 8 is pseuकरोcolor,
     *  and higher than that, true/directcolor.  This is incorrect, one needs
     *  to look at the fix->visual.
     *
     *  Another common mistake is using bits_per_pixel to calculate the color
     *  depth.  The bits_per_pixel field करोes not directly translate to color
     *  depth. You have to compute क्रम the color depth (using the color
     *  bitfields) and fix->visual as seen above.
     */

    /*
     * This is the poपूर्णांक where the color is converted to something that
     * is acceptable by the hardware.
     */
#घोषणा CNVT_TOHW(val,width) ((((val)<<(width))+0x7FFF-(val))>>16)
    red = CNVT_TOHW(red, info->var.red.length);
    green = CNVT_TOHW(green, info->var.green.length);
    blue = CNVT_TOHW(blue, info->var.blue.length);
    transp = CNVT_TOHW(transp, info->var.transp.length);
#अघोषित CNVT_TOHW
    /*
     * This is the poपूर्णांक where the function feeds the color to the hardware
     * palette after converting the colors to something acceptable by
     * the hardware. Note, only FB_VISUAL_सूचीECTCOLOR and
     * FB_VISUAL_PSEUDOCOLOR visuals need to ग_लिखो to the hardware palette.
     * If you have code that ग_लिखोs to the hardware CLUT, and it's not
     * any of the above visuals, then you are करोing something wrong.
     */
    अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR ||
	info->fix.visual == FB_VISUAL_TRUECOLOR)
	    ग_लिखो_अणुred|green|blue|transpपूर्ण_to_clut();

    /* This is the poपूर्णांक were you need to fill up the contents of
     * info->pseuकरो_palette. This काष्ठाure is used _only_ by fbcon, thus
     * it only contains 16 entries to match the number of colors supported
     * by the console. The pseuकरो_palette is used only अगर the visual is
     * in directcolor or truecolor mode.  With other visuals, the
     * pseuकरो_palette is not used. (This might change in the future.)
     *
     * The contents of the pseuकरो_palette is in raw pixel क्रमmat.  Ie, each
     * entry can be written directly to the framebuffer without any conversion.
     * The pseuकरो_palette is (व्योम *).  However, अगर using the generic
     * drawing functions (cfb_imageblit, cfb_fillrect), the pseuकरो_palette
     * must be casted to (u32 *) _regardless_ of the bits per pixel. If the
     * driver is using its own drawing functions, then it can use whatever
     * size it wants.
     */
    अगर (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
	    u32 v;

	    अगर (regno >= 16)
		    वापस -EINVAL;

	    v = (red << info->var.red.offset) |
		    (green << info->var.green.offset) |
		    (blue << info->var.blue.offset) |
		    (transp << info->var.transp.offset);

	    ((u32*)(info->pseuकरो_palette))[regno] = v;
    पूर्ण

    /* ... */
    वापस 0;
पूर्ण

/**
 *      xxxfb_pan_display - NOT a required function. Pans the display.
 *      @var: frame buffer variable screen काष्ठाure
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Pan (or wrap, depending on the `vmode' field) the display using the
 *  	`xoffset' and `yoffset' fields of the `var' काष्ठाure.
 *  	If the values करोn't fit, वापस -EINVAL.
 *
 *      Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक xxxfb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
    /*
     * If your hardware करोes not support panning, _करो_ _not_ implement this
     * function. Creating a dummy function will just confuse user apps.
     */

    /*
     * Note that even अगर this function is fully functional, a setting of
     * 0 in both xpanstep and ypanstep means that this function will never
     * get called.
     */

    /* ... */
    वापस 0;
पूर्ण

/**
 *      xxxfb_blank - NOT a required function. Blanks the display.
 *      @blank_mode: the blank mode we want. 
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *      Blank the screen अगर blank_mode != FB_BLANK_UNBLANK, अन्यथा unblank.
 *      Return 0 अगर blanking succeeded, != 0 अगर un-/blanking failed due to
 *      e.g. a video mode which करोesn't support it.
 *
 *      Implements VESA suspend and घातerकरोwn modes on hardware that supports
 *      disabling hsync/vsync:
 *
 *      FB_BLANK_NORMAL = display is blanked, syncs are on.
 *      FB_BLANK_HSYNC_SUSPEND = hsync off
 *      FB_BLANK_VSYNC_SUSPEND = vsync off
 *      FB_BLANK_POWERDOWN =  hsync and vsync off
 *
 *      If implementing this function, at least support FB_BLANK_UNBLANK.
 *      Return !0 क्रम any modes that are unimplemented.
 *
 */
अटल पूर्णांक xxxfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
    /* ... */
    वापस 0;
पूर्ण

/* ------------ Accelerated Functions --------------------- */

/*
 * We provide our own functions अगर we have hardware acceleration
 * or non packed pixel क्रमmat layouts. If we have no hardware 
 * acceleration, we can use a generic unaccelerated function. If using
 * a pack pixel क्रमmat just use the functions in cfb_*.c. Each file 
 * has one of the three dअगरferent accel functions we support.
 */

/**
 *      xxxfb_fillrect - REQUIRED function. Can use generic routines अगर 
 *		 	 non acclerated hardware and packed pixel based.
 *			 Draws a rectangle on the screen.		
 *
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *	@region: The काष्ठाure representing the rectangular region we 
 *		 wish to draw to.
 *
 *	This drawing operation places/हटाओs a retangle on the screen 
 *	depending on the rastering operation with the value of color which
 *	is in the current color depth क्रमmat.
 */
व्योम xxxfb_fillrect(काष्ठा fb_info *p, स्थिर काष्ठा fb_fillrect *region)
अणु
/*	Meaning of काष्ठा fb_fillrect
 *
 *	@dx: The x and y corrdinates of the upper left hand corner of the 
 *	@dy: area we want to draw to. 
 *	@width: How wide the rectangle is we want to draw.
 *	@height: How tall the rectangle is we want to draw.
 *	@color:	The color to fill in the rectangle with. 
 *	@rop: The raster operation. We can draw the rectangle with a COPY
 *	      of XOR which provides erasing effect. 
 */
पूर्ण

/**
 *      xxxfb_copyarea - REQUIRED function. Can use generic routines अगर
 *                       non acclerated hardware and packed pixel based.
 *                       Copies one area of the screen to another area.
 *
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *      @area: Structure providing the data to copy the framebuffer contents
 *	       from one region to another.
 *
 *      This drawing operation copies a rectangular area from one area of the
 *	screen to another area.
 */
व्योम xxxfb_copyarea(काष्ठा fb_info *p, स्थिर काष्ठा fb_copyarea *area) 
अणु
/*
 *      @dx: The x and y coordinates of the upper left hand corner of the
 *	@dy: destination area on the screen.
 *      @width: How wide the rectangle is we want to copy.
 *      @height: How tall the rectangle is we want to copy.
 *      @sx: The x and y coordinates of the upper left hand corner of the
 *      @sy: source area on the screen.
 */
पूर्ण


/**
 *      xxxfb_imageblit - REQUIRED function. Can use generic routines अगर
 *                        non acclerated hardware and packed pixel based.
 *                        Copies a image from प्रणाली memory to the screen. 
 *
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *	@image:	काष्ठाure defining the image.
 *
 *      This drawing operation draws a image on the screen. It can be a 
 *	mono image (needed क्रम font handling) or a color image (needed क्रम
 *	tux). 
 */
व्योम xxxfb_imageblit(काष्ठा fb_info *p, स्थिर काष्ठा fb_image *image) 
अणु
/*
 *      @dx: The x and y coordinates of the upper left hand corner of the
 *	@dy: destination area to place the image on the screen.
 *      @width: How wide the image is we want to copy.
 *      @height: How tall the image is we want to copy.
 *      @fg_color: For mono biपंचांगap images this is color data क्रम     
 *      @bg_color: the क्रमeground and background of the image to
 *		   ग_लिखो directly to the frmaebuffer.
 *	@depth:	How many bits represent a single pixel क्रम this image.
 *	@data: The actual data used to स्थिरruct the image on the display.
 *	@cmap: The colormap used क्रम color images.   
 */

/*
 * The generic function, cfb_imageblit, expects that the biपंचांगap scanlines are
 * padded to the next byte.  Most hardware accelerators may require padding to
 * the next u16 or the next u32.  If that is the हाल, the driver can specअगरy
 * this by setting info->pixmap.scan_align = 2 or 4.  See a more
 * comprehensive description of the pixmap below.
 */
पूर्ण

/**
 *	xxxfb_cursor - 	OPTIONAL. If your hardware lacks support
 *			क्रम a cursor, leave this field शून्य.
 *
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *	@cursor: काष्ठाure defining the cursor to draw.
 *
 *      This operation is used to set or alter the properities of the
 *	cursor.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
पूर्णांक xxxfb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
/*
 *      @set: 	Which fields we are altering in काष्ठा fb_cursor 
 *	@enable: Disable or enable the cursor 
 *      @rop: 	The bit operation we want to करो. 
 *      @mask:  This is the cursor mask biपंचांगap. 
 *      @dest:  A image of the area we are going to display the cursor.
 *		Used पूर्णांकernally by the driver.	 
 *      @hot:	The hot spot. 
 *	@image:	The actual data क्रम the cursor image.
 *
 *      NOTES ON FLAGS (cursor->set):
 *
 *      FB_CUR_SETIMAGE - the cursor image has changed (cursor->image.data)
 *      FB_CUR_SETPOS   - the cursor position has changed (cursor->image.dx|dy)
 *      FB_CUR_SETHOT   - the cursor hot spot has changed (cursor->hot.dx|dy)
 *      FB_CUR_SETCMAP  - the cursor colors has changed (cursor->fg_color|bg_color)
 *      FB_CUR_SETSHAPE - the cursor biपंचांगask has changed (cursor->mask)
 *      FB_CUR_SETSIZE  - the cursor size has changed (cursor->width|height)
 *      FB_CUR_SETALL   - everything has changed
 *
 *      NOTES ON ROPs (cursor->rop, Raster Operation)
 *
 *      ROP_XOR         - cursor->image.data XOR cursor->mask
 *      ROP_COPY        - curosr->image.data AND cursor->mask
 *
 *      OTHER NOTES:
 *
 *      - fbcon only supports a 2-color cursor (cursor->image.depth = 1)
 *      - The fb_cursor काष्ठाure, @cursor, _will_ always contain valid
 *        fields, whether any particular bitfields in cursor->set is set
 *        or not.
 */
पूर्ण

/**
 *	xxxfb_sync - NOT a required function. Normally the accel engine 
 *		     क्रम a graphics card take a specअगरic amount of समय.
 *		     Often we have to रुको क्रम the accelerator to finish
 *		     its operation beक्रमe we can ग_लिखो to the framebuffer
 *		     so we can have consistent display output. 
 *
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *      If the driver has implemented its own hardware-based drawing function,
 *      implementing this function is highly recommended.
 */
पूर्णांक xxxfb_sync(काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

    /*
     *  Frame buffer operations
     */

अटल स्थिर काष्ठा fb_ops xxxfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_खोलो	= xxxfb_खोलो,
	.fb_पढ़ो	= xxxfb_पढ़ो,
	.fb_ग_लिखो	= xxxfb_ग_लिखो,
	.fb_release	= xxxfb_release,
	.fb_check_var	= xxxfb_check_var,
	.fb_set_par	= xxxfb_set_par,
	.fb_setcolreg	= xxxfb_setcolreg,
	.fb_blank	= xxxfb_blank,
	.fb_pan_display	= xxxfb_pan_display,
	.fb_fillrect	= xxxfb_fillrect, 	/* Needed !!! */
	.fb_copyarea	= xxxfb_copyarea,	/* Needed !!! */
	.fb_imageblit	= xxxfb_imageblit,	/* Needed !!! */
	.fb_cursor	= xxxfb_cursor,		/* Optional !!! */
	.fb_sync	= xxxfb_sync,
	.fb_ioctl	= xxxfb_ioctl,
	.fb_mmap	= xxxfb_mmap,
पूर्ण;

/* ------------------------------------------------------------------------- */

    /*
     *  Initialization
     */

/* अटल पूर्णांक __init xxfb_probe (काष्ठा platक्रमm_device *pdev) -- क्रम platक्रमm devs */
अटल पूर्णांक xxxfb_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *ent)
अणु
    काष्ठा fb_info *info;
    काष्ठा xxx_par *par;
    काष्ठा device *device = &dev->dev; /* or &pdev->dev */
    पूर्णांक cmap_len, retval;	
   
    /*
     * Dynamically allocate info and par
     */
    info = framebuffer_alloc(माप(काष्ठा xxx_par), device);

    अगर (!info) अणु
	    /* जाओ error path */
    पूर्ण

    par = info->par;

    /* 
     * Here we set the screen_base to the भव memory address
     * क्रम the framebuffer. Usually we obtain the resource address
     * from the bus layer and then translate it to भव memory
     * space via ioremap. Consult ioport.h. 
     */
    info->screen_base = framebuffer_भव_memory;
    info->fbops = &xxxfb_ops;
    info->fix = xxxfb_fix;
    info->pseuकरो_palette = pseuकरो_palette; /* The pseuकरोpalette is an
					    * 16-member array
					    */
    /*
     * Set up flags to indicate what sort of acceleration your
     * driver can provide (pan/wrap/copyarea/etc.) and whether it
     * is a module -- see FBINFO_* in include/linux/fb.h
     *
     * If your hardware can support any of the hardware accelerated functions
     * fbcon perक्रमmance will improve अगर info->flags is set properly.
     *
     * FBINFO_HWACCEL_COPYAREA - hardware moves
     * FBINFO_HWACCEL_FILLRECT - hardware fills
     * FBINFO_HWACCEL_IMAGEBLIT - hardware mono->color expansion
     * FBINFO_HWACCEL_YPAN - hardware can pan display in y-axis
     * FBINFO_HWACCEL_YWRAP - hardware can wrap display in y-axis
     * FBINFO_HWACCEL_DISABLED - supports hardware accels, but disabled
     * FBINFO_READS_FAST - अगर set, prefer moves over mono->color expansion
     * FBINFO_MISC_TILEBLITTING - hardware can करो tile blits
     *
     * NOTE: These are क्रम fbcon use only.
     */
    info->flags = FBINFO_DEFAULT;

/********************* This stage is optional ******************************/
     /*
     * The काष्ठा pixmap is a scratch pad क्रम the drawing functions. This
     * is where the monochrome biपंचांगap is स्थिरructed by the higher layers
     * and then passed to the accelerator.  For drivers that uses
     * cfb_imageblit, you can skip this part.  For those that have a more
     * rigorous requirement, this stage is needed
     */

    /* PIXMAP_SIZE should be small enough to optimize drawing, but not
     * large enough that memory is wasted.  A safe size is
     * (max_xres * max_font_height/8). max_xres is driver dependent,
     * max_font_height is 32.
     */
    info->pixmap.addr = kदो_स्मृति(PIXMAP_SIZE, GFP_KERNEL);
    अगर (!info->pixmap.addr) अणु
	    /* जाओ error */
    पूर्ण

    info->pixmap.size = PIXMAP_SIZE;

    /*
     * FB_PIXMAP_SYSTEM - memory is in प्रणाली ram
     * FB_PIXMAP_IO     - memory is iomapped
     * FB_PIXMAP_SYNC   - अगर set, will call fb_sync() per access to pixmap,
     *                    usually अगर FB_PIXMAP_IO is set.
     *
     * Currently, FB_PIXMAP_IO is unimplemented.
     */
    info->pixmap.flags = FB_PIXMAP_SYSTEM;

    /*
     * scan_align is the number of padding क्रम each scanline.  It is in bytes.
     * Thus क्रम accelerators that need padding to the next u32, put 4 here.
     */
    info->pixmap.scan_align = 4;

    /*
     * buf_align is the amount to be padded क्रम the buffer. For example,
     * the i810fb needs a scan_align of 2 but expects it to be fed with
     * dwords, so a buf_align = 4 is required.
     */
    info->pixmap.buf_align = 4;

    /* access_align is how many bits can be accessed from the framebuffer
     * ie. some epson cards allow 16-bit access only.  Most drivers will
     * be safe with u32 here.
     *
     * NOTE: This field is currently unused.
     */
    info->pixmap.access_align = 32;
/***************************** End optional stage ***************************/

    /*
     * This should give a reasonable शेष video mode. The following is
     * करोne when we can set a video mode. 
     */
    अगर (!mode_option)
	mode_option = "640x480@60";	 	

    retval = fb_find_mode(&info->var, info, mode_option, शून्य, 0, शून्य, 8);
  
    अगर (!retval || retval == 4)
	वापस -EINVAL;			

    /* This has to be करोne! */
    अगर (fb_alloc_cmap(&info->cmap, cmap_len, 0))
	वापस -ENOMEM;
	
    /* 
     * The following is करोne in the हाल of having hardware with a अटल 
     * mode. If we are setting the mode ourselves we करोn't call this. 
     */	
    info->var = xxxfb_var;

    /*
     * For drivers that can...
     */
    xxxfb_check_var(&info->var, info);

    /*
     * Does a call to fb_set_par() beक्रमe रेजिस्टर_framebuffer needed?  This
     * will depend on you and the hardware.  If you are sure that your driver
     * is the only device in the प्रणाली, a call to fb_set_par() is safe.
     *
     * Hardware in x86 प्रणालीs has a VGA core.  Calling set_par() at this
     * poपूर्णांक will corrupt the VGA console, so it might be safer to skip a
     * call to set_par here and just allow fbcon to करो it क्रम you.
     */
    /* xxxfb_set_par(info); */

    अगर (रेजिस्टर_framebuffer(info) < 0) अणु
	fb_dealloc_cmap(&info->cmap);
	वापस -EINVAL;
    पूर्ण
    fb_info(info, "%s frame buffer device\n", info->fix.id);
    pci_set_drvdata(dev, info); /* or platक्रमm_set_drvdata(pdev, info) */
    वापस 0;
पूर्ण

    /*
     *  Cleanup
     */
/* अटल व्योम xxxfb_हटाओ(काष्ठा platक्रमm_device *pdev) */
अटल व्योम xxxfb_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);
	/* or platक्रमm_get_drvdata(pdev); */

	अगर (info) अणु
		unरेजिस्टर_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);
		/* ... */
		framebuffer_release(info);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PCI
#अगर_घोषित CONFIG_PM
/**
 *	xxxfb_suspend - Optional but recommended function. Suspend the device.
 *	@dev: PCI device
 *	@msg: the suspend event code.
 *
 *      See Documentation/driver-api/pm/devices.rst क्रम more inक्रमmation
 */
अटल पूर्णांक xxxfb_suspend(काष्ठा pci_dev *dev, pm_message_t msg)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);
	काष्ठा xxxfb_par *par = info->par;

	/* suspend here */
	वापस 0;
पूर्ण

/**
 *	xxxfb_resume - Optional but recommended function. Resume the device.
 *	@dev: PCI device
 *
 *      See Documentation/driver-api/pm/devices.rst क्रम more inक्रमmation
 */
अटल पूर्णांक xxxfb_resume(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);
	काष्ठा xxxfb_par *par = info->par;

	/* resume here */
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा xxxfb_suspend शून्य
#घोषणा xxxfb_resume शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा pci_device_id xxxfb_id_table[] = अणु
	अणु PCI_VENDOR_ID_XXX, PCI_DEVICE_ID_XXX,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_BASE_CLASS_DISPLAY << 16,
	  PCI_CLASS_MASK, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

/* For PCI drivers */
अटल काष्ठा pci_driver xxxfb_driver = अणु
	.name =		"xxxfb",
	.id_table =	xxxfb_id_table,
	.probe =	xxxfb_probe,
	.हटाओ =	xxxfb_हटाओ,
	.suspend =      xxxfb_suspend, /* optional but recommended */
	.resume =       xxxfb_resume,  /* optional but recommended */
पूर्ण;

MODULE_DEVICE_TABLE(pci, xxxfb_id_table);

पूर्णांक __init xxxfb_init(व्योम)
अणु
	/*
	 *  For kernel boot options (in 'video=xxxfb:<options>' क्रमmat)
	 */
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("xxxfb", &option))
		वापस -ENODEV;
	xxxfb_setup(option);
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&xxxfb_driver);
पूर्ण

अटल व्योम __निकास xxxfb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&xxxfb_driver);
पूर्ण
#अन्यथा /* non PCI, platक्रमm drivers */
#समावेश <linux/platक्रमm_device.h>
/* क्रम platक्रमm devices */

#अगर_घोषित CONFIG_PM
/**
 *	xxxfb_suspend - Optional but recommended function. Suspend the device.
 *	@dev: platक्रमm device
 *	@msg: the suspend event code.
 *
 *      See Documentation/driver-api/pm/devices.rst क्रम more inक्रमmation
 */
अटल पूर्णांक xxxfb_suspend(काष्ठा platक्रमm_device *dev, pm_message_t msg)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा xxxfb_par *par = info->par;

	/* suspend here */
	वापस 0;
पूर्ण

/**
 *	xxxfb_resume - Optional but recommended function. Resume the device.
 *	@dev: platक्रमm device
 *
 *      See Documentation/driver-api/pm/devices.rst क्रम more inक्रमmation
 */
अटल पूर्णांक xxxfb_resume(काष्ठा platक्रमm_dev *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा xxxfb_par *par = info->par;

	/* resume here */
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा xxxfb_suspend शून्य
#घोषणा xxxfb_resume शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा platक्रमm_device_driver xxxfb_driver = अणु
	.probe = xxxfb_probe,
	.हटाओ = xxxfb_हटाओ,
	.suspend = xxxfb_suspend, /* optional but recommended */
	.resume = xxxfb_resume,   /* optional but recommended */
	.driver = अणु
		.name = "xxxfb",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *xxxfb_device;

#अगर_अघोषित MODULE
    /*
     *  Setup
     */

/*
 * Only necessary अगर your driver takes special options,
 * otherwise we fall back on the generic fb_setup().
 */
पूर्णांक __init xxxfb_setup(अक्षर *options)
अणु
    /* Parse user specअगरied options (`video=xxxfb:') */
पूर्ण
#पूर्ण_अगर /* MODULE */

अटल पूर्णांक __init xxxfb_init(व्योम)
अणु
	पूर्णांक ret;
	/*
	 *  For kernel boot options (in 'video=xxxfb:<options>' क्रमmat)
	 */
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("xxxfb", &option))
		वापस -ENODEV;
	xxxfb_setup(option);
#पूर्ण_अगर
	ret = platक्रमm_driver_रेजिस्टर(&xxxfb_driver);

	अगर (!ret) अणु
		xxxfb_device = platक्रमm_device_रेजिस्टर_simple("xxxfb", 0,
								शून्य, 0);

		अगर (IS_ERR(xxxfb_device)) अणु
			platक्रमm_driver_unरेजिस्टर(&xxxfb_driver);
			ret = PTR_ERR(xxxfb_device);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास xxxfb_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(xxxfb_device);
	platक्रमm_driver_unरेजिस्टर(&xxxfb_driver);
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

/* ------------------------------------------------------------------------- */


    /*
     *  Modularization
     */

module_init(xxxfb_init);
module_निकास(xxxfb_निकास);

MODULE_LICENSE("GPL");
