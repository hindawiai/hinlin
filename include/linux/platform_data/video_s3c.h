<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PLATFORM_DATA_VIDEO_S3C
#घोषणा __PLATFORM_DATA_VIDEO_S3C

/* S3C_FB_MAX_WIN
 * Set to the maximum number of winकरोws that any of the supported hardware
 * can use. Since the platक्रमm data uses this क्रम an array size, having it
 * set to the maximum of any version of the hardware can करो is safe.
 */
#घोषणा S3C_FB_MAX_WIN	(5)

/**
 * काष्ठा s3c_fb_pd_win - per winकरोw setup data
 * @xres     : The winकरोw X size.
 * @yres     : The winकरोw Y size.
 * @भव_x: The भव X size.
 * @भव_y: The भव Y size.
 */
काष्ठा s3c_fb_pd_win अणु
	अचिन्हित लघु		शेष_bpp;
	अचिन्हित लघु		max_bpp;
	अचिन्हित लघु		xres;
	अचिन्हित लघु		yres;
	अचिन्हित लघु		भव_x;
	अचिन्हित लघु		भव_y;
पूर्ण;

/**
 * काष्ठा s3c_fb_platdata -  S3C driver platक्रमm specअगरic inक्रमmation
 * @setup_gpio: Setup the बाह्यal GPIO pins to the right state to transfer
 *		the data from the display प्रणाली to the connected display
 *		device.
 * @vidcon0: The base vidcon0 values to control the panel data क्रमmat.
 * @vidcon1: The base vidcon1 values to control the panel data output.
 * @vtiming: Video timing when connected to a RGB type panel.
 * @win: The setup data क्रम each hardware winकरोw, or शून्य क्रम unused.
 * @display_mode: The LCD output display mode.
 *
 * The platक्रमm data supplies the video driver with all the inक्रमmation
 * it requires to work with the display(s) attached to the machine. It
 * controls the initial mode, the number of display winकरोws (0 is always
 * the base framebuffer) that are initialised etc.
 *
 */
काष्ठा s3c_fb_platdata अणु
	व्योम	(*setup_gpio)(व्योम);

	काष्ठा s3c_fb_pd_win	*win[S3C_FB_MAX_WIN];
	काष्ठा fb_videomode     *vtiming;

	u32			 vidcon0;
	u32			 vidcon1;
पूर्ण;

#पूर्ण_अगर
