<शैली गुरु>
/*
 * am200epd.c -- Platक्रमm device क्रम AM200 EPD kit
 *
 * Copyright (C) 2008, Jaya Kumar
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Layout is based on skeletonfb.c by James Simmons and Geert Uytterhoeven.
 *
 * This work was made possible by help and equipment support from E-Ink
 * Corporation. http://support.eink.com/community
 *
 * This driver is written to be used with the Metronome display controller.
 * on the AM200 EPD prototype kit/development kit with an E-Ink 800x600
 * Vizplex EPD on a Gumstix board using the Lyre पूर्णांकerface board.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpपन.स>

#समावेश "pxa25x.h"
#समावेश "gumstix.h"
#समावेश <linux/platक्रमm_data/video-pxafb.h>

#समावेश "generic.h"

#समावेश <video/metronomefb.h>

अटल अचिन्हित पूर्णांक panel_type = 6;
अटल काष्ठा platक्रमm_device *am200_device;
अटल काष्ठा metronome_board am200_board;

अटल काष्ठा pxafb_mode_info am200_fb_mode_9inch7 = अणु
	.pixघड़ी	= 40000,
	.xres		= 1200,
	.yres		= 842,
	.bpp		= 16,
	.hsync_len	= 2,
	.left_margin	= 2,
	.right_margin	= 2,
	.vsync_len	= 1,
	.upper_margin	= 2,
	.lower_margin	= 25,
	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mode_info am200_fb_mode_8inch = अणु
	.pixघड़ी	= 40000,
	.xres		= 1088,
	.yres		= 791,
	.bpp		= 16,
	.hsync_len	= 28,
	.left_margin	= 8,
	.right_margin	= 30,
	.vsync_len	= 8,
	.upper_margin	= 10,
	.lower_margin	= 8,
	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mode_info am200_fb_mode_6inch = अणु
	.pixघड़ी	= 40189,
	.xres		= 832,
	.yres		= 622,
	.bpp		= 16,
	.hsync_len	= 28,
	.left_margin	= 34,
	.right_margin	= 34,
	.vsync_len	= 25,
	.upper_margin	= 0,
	.lower_margin	= 2,
	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mach_info am200_fb_info = अणु
	.modes		= &am200_fb_mode_6inch,
	.num_modes	= 1,
	.lcd_conn	= LCD_TYPE_COLOR_TFT | LCD_PCLK_EDGE_FALL |
			  LCD_AC_BIAS_FREQ(24),
पूर्ण;

/* रेजिस्टर offsets क्रम gpio control */
#घोषणा LED_GPIO_PIN 51
#घोषणा STDBY_GPIO_PIN 48
#घोषणा RST_GPIO_PIN 49
#घोषणा RDY_GPIO_PIN 32
#घोषणा ERR_GPIO_PIN 17
#घोषणा PCBPWR_GPIO_PIN 16
अटल पूर्णांक gpios[] = अणु LED_GPIO_PIN , STDBY_GPIO_PIN , RST_GPIO_PIN,
			RDY_GPIO_PIN, ERR_GPIO_PIN, PCBPWR_GPIO_PIN पूर्ण;
अटल अक्षर *gpio_names[] = अणु "LED" , "STDBY" , "RST", "RDY", "ERR", "PCBPWR" पूर्ण;

अटल पूर्णांक am200_init_gpio_regs(काष्ठा metronomefb_par *par)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(gpios); i++) अणु
		err = gpio_request(gpios[i], gpio_names[i]);
		अगर (err) अणु
			dev_err(&am200_device->dev, "failed requesting "
				"gpio %s, err=%d\n", gpio_names[i], err);
			जाओ err_req_gpio;
		पूर्ण
	पूर्ण

	gpio_direction_output(LED_GPIO_PIN, 0);
	gpio_direction_output(STDBY_GPIO_PIN, 0);
	gpio_direction_output(RST_GPIO_PIN, 0);

	gpio_direction_input(RDY_GPIO_PIN);
	gpio_direction_input(ERR_GPIO_PIN);

	gpio_direction_output(PCBPWR_GPIO_PIN, 0);

	वापस 0;

err_req_gpio:
	जबतक (--i >= 0)
		gpio_मुक्त(gpios[i]);

	वापस err;
पूर्ण

अटल व्योम am200_cleanup(काष्ठा metronomefb_par *par)
अणु
	पूर्णांक i;

	मुक्त_irq(PXA_GPIO_TO_IRQ(RDY_GPIO_PIN), par);

	क्रम (i = 0; i < ARRAY_SIZE(gpios); i++)
		gpio_मुक्त(gpios[i]);
पूर्ण

अटल पूर्णांक am200_share_video_mem(काष्ठा fb_info *info)
अणु
	/* rough check अगर this is our desired fb and not something अन्यथा */
	अगर ((info->var.xres != am200_fb_info.modes->xres)
		|| (info->var.yres != am200_fb_info.modes->yres))
		वापस 0;

	/* we've now been notअगरied that we have our new fb */
	am200_board.metromem = info->screen_base;
	am200_board.host_fbinfo = info;

	/* try to refcount host drv since we are the consumer after this */
	अगर (!try_module_get(info->fbops->owner))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक am200_unshare_video_mem(काष्ठा fb_info *info)
अणु
	dev_dbg(&am200_device->dev, "ENTER %s\n", __func__);

	अगर (info != am200_board.host_fbinfo)
		वापस 0;

	module_put(am200_board.host_fbinfo->fbops->owner);
	वापस 0;
पूर्ण

अटल पूर्णांक am200_fb_notअगरier_callback(काष्ठा notअगरier_block *self,
				 अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा fb_event *evdata = data;
	काष्ठा fb_info *info = evdata->info;

	dev_dbg(&am200_device->dev, "ENTER %s\n", __func__);

	अगर (event == FB_EVENT_FB_REGISTERED)
		वापस am200_share_video_mem(info);
	अन्यथा अगर (event == FB_EVENT_FB_UNREGISTERED)
		वापस am200_unshare_video_mem(info);

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block am200_fb_notअगर = अणु
	.notअगरier_call = am200_fb_notअगरier_callback,
पूर्ण;

/* this माला_लो called as part of our init. these steps must be करोne now so
 * that we can use pxa_set_fb_info */
अटल व्योम __init am200_presetup_fb(व्योम)
अणु
	पूर्णांक fw;
	पूर्णांक fh;
	पूर्णांक padding_size;
	पूर्णांक totalsize;

	चयन (panel_type) अणु
	हाल 6:
		am200_fb_info.modes = &am200_fb_mode_6inch;
		अवरोध;
	हाल 8:
		am200_fb_info.modes = &am200_fb_mode_8inch;
		अवरोध;
	हाल 97:
		am200_fb_info.modes = &am200_fb_mode_9inch7;
		अवरोध;
	शेष:
		dev_err(&am200_device->dev, "invalid panel_type selection,"
						" setting to 6\n");
		am200_fb_info.modes = &am200_fb_mode_6inch;
		अवरोध;
	पूर्ण

	/* the frame buffer is भागided as follows:
	command | CRC | padding
	16kb waveक्रमm data | CRC | padding
	image data | CRC
	*/

	fw = am200_fb_info.modes->xres;
	fh = am200_fb_info.modes->yres;

	/* waveक्रमm must be 16k + 2 क्रम checksum */
	am200_board.wfm_size = roundup(16*1024 + 2, fw);

	padding_size = PAGE_SIZE + (4 * fw);

	/* total is 1 cmd , 1 wfm, padding and image */
	totalsize = fw + am200_board.wfm_size + padding_size + (fw*fh);

	/* save this off because we're manipulating fw after this and
	 * we'll need it when we're पढ़ोy to setup the framebuffer */
	am200_board.fw = fw;
	am200_board.fh = fh;

	/* the reason we करो this adjusपंचांगent is because we want to acquire
	 * more framebuffer memory without imposing custom awareness on the
	 * underlying pxafb driver */
	am200_fb_info.modes->yres = DIV_ROUND_UP(totalsize, fw);

	/* we भागide since we told the LCD controller we're 16bpp */
	am200_fb_info.modes->xres /= 2;

	pxa_set_fb_info(शून्य, &am200_fb_info);

पूर्ण

/* this माला_लो called by metronomefb as part of its init, in our हाल, we
 * have alपढ़ोy completed initial framebuffer init in presetup_fb so we
 * can just setup the fb access poपूर्णांकers */
अटल पूर्णांक am200_setup_fb(काष्ठा metronomefb_par *par)
अणु
	पूर्णांक fw;
	पूर्णांक fh;

	fw = am200_board.fw;
	fh = am200_board.fh;

	/* metromem was set up by the notअगरier in share_video_mem so now
	 * we can use its value to calculate the other entries */
	par->metromem_cmd = (काष्ठा metromem_cmd *) am200_board.metromem;
	par->metromem_wfm = am200_board.metromem + fw;
	par->metromem_img = par->metromem_wfm + am200_board.wfm_size;
	par->metromem_img_csum = (u16 *) (par->metromem_img + (fw * fh));
	par->metromem_dma = am200_board.host_fbinfo->fix.smem_start;

	वापस 0;
पूर्ण

अटल पूर्णांक am200_get_panel_type(व्योम)
अणु
	वापस panel_type;
पूर्ण

अटल irqवापस_t am200_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा metronomefb_par *par = dev_id;

	wake_up_पूर्णांकerruptible(&par->रुकोq);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक am200_setup_irq(काष्ठा fb_info *info)
अणु
	पूर्णांक ret;

	ret = request_irq(PXA_GPIO_TO_IRQ(RDY_GPIO_PIN), am200_handle_irq,
				IRQF_TRIGGER_FALLING, "AM200", info->par);
	अगर (ret)
		dev_err(&am200_device->dev, "request_irq failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम am200_set_rst(काष्ठा metronomefb_par *par, पूर्णांक state)
अणु
	gpio_set_value(RST_GPIO_PIN, state);
पूर्ण

अटल व्योम am200_set_stdby(काष्ठा metronomefb_par *par, पूर्णांक state)
अणु
	gpio_set_value(STDBY_GPIO_PIN, state);
पूर्ण

अटल पूर्णांक am200_रुको_event(काष्ठा metronomefb_par *par)
अणु
	वापस रुको_event_समयout(par->रुकोq, gpio_get_value(RDY_GPIO_PIN), HZ);
पूर्ण

अटल पूर्णांक am200_रुको_event_पूर्णांकr(काष्ठा metronomefb_par *par)
अणु
	वापस रुको_event_पूर्णांकerruptible_समयout(par->रुकोq,
					gpio_get_value(RDY_GPIO_PIN), HZ);
पूर्ण

अटल काष्ठा metronome_board am200_board = अणु
	.owner			= THIS_MODULE,
	.setup_irq		= am200_setup_irq,
	.setup_io		= am200_init_gpio_regs,
	.setup_fb		= am200_setup_fb,
	.set_rst		= am200_set_rst,
	.set_stdby		= am200_set_stdby,
	.met_रुको_event		= am200_रुको_event,
	.met_रुको_event_पूर्णांकr	= am200_रुको_event_पूर्णांकr,
	.get_panel_type		= am200_get_panel_type,
	.cleanup		= am200_cleanup,
पूर्ण;

अटल अचिन्हित दीर्घ am200_pin_config[] __initdata = अणु
	GPIO51_GPIO,
	GPIO49_GPIO,
	GPIO48_GPIO,
	GPIO32_GPIO,
	GPIO17_GPIO,
	GPIO16_GPIO,
पूर्ण;

पूर्णांक __init am200_init(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * Beक्रमe anything अन्यथा, we request notअगरication क्रम any fb
	 * creation events.
	 *
	 * FIXME: This is terrible and needs to be nuked. The notअगरier is used
	 * to get at the fb base address from the boot splash fb driver, which
	 * is then passed to metronomefb. Instaed of metronomfb or this board
	 * support file here figuring this out on their own.
	 *
	 * See also the #अगर_घोषित in fbmem.c.
	 */
	fb_रेजिस्टर_client(&am200_fb_notअगर);

	pxa2xx_mfp_config(ARRAY_AND_SIZE(am200_pin_config));

	/* request our platक्रमm independent driver */
	request_module("metronomefb");

	am200_device = platक्रमm_device_alloc("metronomefb", -1);
	अगर (!am200_device)
		वापस -ENOMEM;

	/* the am200_board that will be seen by metronomefb is a copy */
	platक्रमm_device_add_data(am200_device, &am200_board,
					माप(am200_board));

	/* this _add binds metronomefb to am200. metronomefb refcounts am200 */
	ret = platक्रमm_device_add(am200_device);

	अगर (ret) अणु
		platक्रमm_device_put(am200_device);
		fb_unरेजिस्टर_client(&am200_fb_notअगर);
		वापस ret;
	पूर्ण

	am200_presetup_fb();

	वापस 0;
पूर्ण

module_param(panel_type, uपूर्णांक, 0);
MODULE_PARM_DESC(panel_type, "Select the panel type: 6, 8, 97");

MODULE_DESCRIPTION("board driver for am200 metronome epd kit");
MODULE_AUTHOR("Jaya Kumar");
MODULE_LICENSE("GPL");
