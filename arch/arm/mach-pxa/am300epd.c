<शैली गुरु>
/*
 * am300epd.c -- Platक्रमm device क्रम AM300 EPD kit
 *
 * Copyright (C) 2008, Jaya Kumar
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * This work was made possible by help and equipment support from E-Ink
 * Corporation. http://support.eink.com/community
 *
 * This driver is written to be used with the Broadsheet display controller.
 * on the AM300 EPD prototype kit/development kit with an E-Ink 800x600
 * Vizplex EPD on a Gumstix board using the Broadsheet पूर्णांकerface board.
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

#समावेश "gumstix.h"
#समावेश "mfp-pxa25x.h"
#समावेश <mach/irqs.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>

#समावेश "generic.h"

#समावेश <video/broadsheetfb.h>

अटल अचिन्हित पूर्णांक panel_type = 6;
अटल काष्ठा platक्रमm_device *am300_device;
अटल काष्ठा broadsheet_board am300_board;

अटल अचिन्हित दीर्घ am300_pin_config[] __initdata = अणु
	GPIO16_GPIO,
	GPIO17_GPIO,
	GPIO32_GPIO,
	GPIO48_GPIO,
	GPIO49_GPIO,
	GPIO51_GPIO,
	GPIO74_GPIO,
	GPIO75_GPIO,
	GPIO76_GPIO,
	GPIO77_GPIO,

	/* this is the 16-bit hdb bus 58-73 */
	GPIO58_GPIO,
	GPIO59_GPIO,
	GPIO60_GPIO,
	GPIO61_GPIO,

	GPIO62_GPIO,
	GPIO63_GPIO,
	GPIO64_GPIO,
	GPIO65_GPIO,

	GPIO66_GPIO,
	GPIO67_GPIO,
	GPIO68_GPIO,
	GPIO69_GPIO,

	GPIO70_GPIO,
	GPIO71_GPIO,
	GPIO72_GPIO,
	GPIO73_GPIO,
पूर्ण;

/* रेजिस्टर offsets क्रम gpio control */
#घोषणा PWR_GPIO_PIN	16
#घोषणा CFG_GPIO_PIN	17
#घोषणा RDY_GPIO_PIN	32
#घोषणा DC_GPIO_PIN	48
#घोषणा RST_GPIO_PIN	49
#घोषणा LED_GPIO_PIN	51
#घोषणा RD_GPIO_PIN	74
#घोषणा WR_GPIO_PIN	75
#घोषणा CS_GPIO_PIN	76
#घोषणा IRQ_GPIO_PIN	77

/* hdb bus */
#घोषणा DB0_GPIO_PIN	58
#घोषणा DB15_GPIO_PIN	73

अटल पूर्णांक gpios[] = अणु PWR_GPIO_PIN, CFG_GPIO_PIN, RDY_GPIO_PIN, DC_GPIO_PIN,
			RST_GPIO_PIN, RD_GPIO_PIN, WR_GPIO_PIN, CS_GPIO_PIN,
			IRQ_GPIO_PIN, LED_GPIO_PIN पूर्ण;
अटल अक्षर *gpio_names[] = अणु "PWR", "CFG", "RDY", "DC", "RST", "RD", "WR",
				"CS", "IRQ", "LED" पूर्ण;

अटल पूर्णांक am300_रुको_event(काष्ठा broadsheetfb_par *par)
अणु
	/* toकरो: improve err recovery */
	रुको_event(par->रुकोq, gpio_get_value(RDY_GPIO_PIN));
	वापस 0;
पूर्ण

अटल पूर्णांक am300_init_gpio_regs(काष्ठा broadsheetfb_par *par)
अणु
	पूर्णांक i;
	पूर्णांक err;
	अक्षर dbname[8];

	क्रम (i = 0; i < ARRAY_SIZE(gpios); i++) अणु
		err = gpio_request(gpios[i], gpio_names[i]);
		अगर (err) अणु
			dev_err(&am300_device->dev, "failed requesting "
				"gpio %s, err=%d\n", gpio_names[i], err);
			जाओ err_req_gpio;
		पूर्ण
	पूर्ण

	/* we also need to take care of the hdb bus */
	क्रम (i = DB0_GPIO_PIN; i <= DB15_GPIO_PIN; i++) अणु
		प्र_लिखो(dbname, "DB%d", i);
		err = gpio_request(i, dbname);
		अगर (err) अणु
			dev_err(&am300_device->dev, "failed requesting "
				"gpio %d, err=%d\n", i, err);
			जाओ err_req_gpio2;
		पूर्ण
	पूर्ण

	/* setup the outमाला_दो and init values */
	gpio_direction_output(PWR_GPIO_PIN, 0);
	gpio_direction_output(CFG_GPIO_PIN, 1);
	gpio_direction_output(DC_GPIO_PIN, 0);
	gpio_direction_output(RD_GPIO_PIN, 1);
	gpio_direction_output(WR_GPIO_PIN, 1);
	gpio_direction_output(CS_GPIO_PIN, 1);
	gpio_direction_output(RST_GPIO_PIN, 0);

	/* setup the inमाला_दो */
	gpio_direction_input(RDY_GPIO_PIN);
	gpio_direction_input(IRQ_GPIO_PIN);

	/* start the hdb bus as an input */
	क्रम (i = DB0_GPIO_PIN; i <= DB15_GPIO_PIN; i++)
		gpio_direction_output(i, 0);

	/* go पूर्णांकo command mode */
	gpio_set_value(CFG_GPIO_PIN, 1);
	gpio_set_value(RST_GPIO_PIN, 0);
	msleep(10);
	gpio_set_value(RST_GPIO_PIN, 1);
	msleep(10);
	am300_रुको_event(par);

	वापस 0;

err_req_gpio2:
	जबतक (--i >= DB0_GPIO_PIN)
		gpio_मुक्त(i);
	i = ARRAY_SIZE(gpios);
err_req_gpio:
	जबतक (--i >= 0)
		gpio_मुक्त(gpios[i]);

	वापस err;
पूर्ण

अटल पूर्णांक am300_init_board(काष्ठा broadsheetfb_par *par)
अणु
	वापस am300_init_gpio_regs(par);
पूर्ण

अटल व्योम am300_cleanup(काष्ठा broadsheetfb_par *par)
अणु
	पूर्णांक i;

	मुक्त_irq(PXA_GPIO_TO_IRQ(RDY_GPIO_PIN), par);

	क्रम (i = 0; i < ARRAY_SIZE(gpios); i++)
		gpio_मुक्त(gpios[i]);

	क्रम (i = DB0_GPIO_PIN; i <= DB15_GPIO_PIN; i++)
		gpio_मुक्त(i);

पूर्ण

अटल u16 am300_get_hdb(काष्ठा broadsheetfb_par *par)
अणु
	u16 res = 0;
	पूर्णांक i;

	क्रम (i = 0; i <= (DB15_GPIO_PIN - DB0_GPIO_PIN) ; i++)
		res |= (gpio_get_value(DB0_GPIO_PIN + i)) ? (1 << i) : 0;

	वापस res;
पूर्ण

अटल व्योम am300_set_hdb(काष्ठा broadsheetfb_par *par, u16 data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= (DB15_GPIO_PIN - DB0_GPIO_PIN) ; i++)
		gpio_set_value(DB0_GPIO_PIN + i, (data >> i) & 0x01);
पूर्ण


अटल व्योम am300_set_ctl(काष्ठा broadsheetfb_par *par, अचिन्हित अक्षर bit,
				u8 state)
अणु
	चयन (bit) अणु
	हाल BS_CS:
		gpio_set_value(CS_GPIO_PIN, state);
		अवरोध;
	हाल BS_DC:
		gpio_set_value(DC_GPIO_PIN, state);
		अवरोध;
	हाल BS_WR:
		gpio_set_value(WR_GPIO_PIN, state);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक am300_get_panel_type(व्योम)
अणु
	वापस panel_type;
पूर्ण

अटल irqवापस_t am300_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा broadsheetfb_par *par = dev_id;

	wake_up(&par->रुकोq);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक am300_setup_irq(काष्ठा fb_info *info)
अणु
	पूर्णांक ret;
	काष्ठा broadsheetfb_par *par = info->par;

	ret = request_irq(PXA_GPIO_TO_IRQ(RDY_GPIO_PIN), am300_handle_irq,
				IRQF_TRIGGER_RISING, "AM300", par);
	अगर (ret)
		dev_err(&am300_device->dev, "request_irq failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा broadsheet_board am300_board = अणु
	.owner			= THIS_MODULE,
	.init			= am300_init_board,
	.cleanup		= am300_cleanup,
	.set_hdb		= am300_set_hdb,
	.get_hdb		= am300_get_hdb,
	.set_ctl		= am300_set_ctl,
	.रुको_क्रम_rdy		= am300_रुको_event,
	.get_panel_type		= am300_get_panel_type,
	.setup_irq		= am300_setup_irq,
पूर्ण;

पूर्णांक __init am300_init(व्योम)
अणु
	पूर्णांक ret;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(am300_pin_config));

	/* request our platक्रमm independent driver */
	request_module("broadsheetfb");

	am300_device = platक्रमm_device_alloc("broadsheetfb", -1);
	अगर (!am300_device)
		वापस -ENOMEM;

	/* the am300_board that will be seen by broadsheetfb is a copy */
	platक्रमm_device_add_data(am300_device, &am300_board,
					माप(am300_board));

	ret = platक्रमm_device_add(am300_device);

	अगर (ret) अणु
		platक्रमm_device_put(am300_device);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

module_param(panel_type, uपूर्णांक, 0);
MODULE_PARM_DESC(panel_type, "Select the panel type: 37, 6, 97");

MODULE_DESCRIPTION("board driver for am300 epd kit");
MODULE_AUTHOR("Jaya Kumar");
MODULE_LICENSE("GPL");
