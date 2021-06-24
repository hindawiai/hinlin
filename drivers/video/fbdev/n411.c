<शैली गुरु>
/*
 * linux/drivers/video/n411.c -- Platक्रमm device क्रम N411 EPD kit
 *
 * Copyright (C) 2008, Jaya Kumar
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Layout is based on skeletonfb.c by James Simmons and Geert Uytterhoeven.
 *
 * This driver is written to be used with the Hecuba display controller
 * board, and tested with the EInk 800x600 display in 1 bit mode.
 * The पूर्णांकerface between Hecuba and the host is TTL based GPIO. The
 * GPIO requirements are 8 writable data lines and 6 lines क्रम control.
 * Only 4 of the controls are actually used here but 6 क्रम future use.
 * The driver requires the IO addresses क्रम data and control GPIO at
 * load समय. It is also possible to use this display with a standard
 * PC parallel port.
 *
 * General notes:
 * - User must set dio_addr=0xIOADDR cio_addr=0xIOADDR c2io_addr=0xIOADDR
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
#समावेश <linux/list.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/irq.h>

#समावेश <video/hecubafb.h>

अटल अचिन्हित दीर्घ dio_addr;
अटल अचिन्हित दीर्घ cio_addr;
अटल अचिन्हित दीर्घ c2io_addr;
अटल अचिन्हित दीर्घ splashval;
अटल अचिन्हित पूर्णांक nosplash;
अटल अचिन्हित अक्षर ctl;

अटल व्योम n411_set_ctl(काष्ठा hecubafb_par *par, अचिन्हित अक्षर bit, अचिन्हित
							अक्षर state)
अणु
	चयन (bit) अणु
	हाल HCB_CD_BIT:
		अगर (state)
			ctl &= ~(HCB_CD_BIT);
		अन्यथा
			ctl |= HCB_CD_BIT;
		अवरोध;
	हाल HCB_DS_BIT:
		अगर (state)
			ctl &= ~(HCB_DS_BIT);
		अन्यथा
			ctl |= HCB_DS_BIT;
		अवरोध;
	पूर्ण
	outb(ctl, cio_addr);
पूर्ण

अटल अचिन्हित अक्षर n411_get_ctl(काष्ठा hecubafb_par *par)
अणु
	वापस inb(c2io_addr);
पूर्ण

अटल व्योम n411_set_data(काष्ठा hecubafb_par *par, अचिन्हित अक्षर value)
अणु
	outb(value, dio_addr);
पूर्ण

अटल व्योम n411_रुको_क्रम_ack(काष्ठा hecubafb_par *par, पूर्णांक clear)
अणु
	पूर्णांक समयout;
	अचिन्हित अक्षर पंचांगp;

	समयout = 500;
	करो अणु
		पंचांगp = n411_get_ctl(par);
		अगर ((पंचांगp & HCB_ACK_BIT) && (!clear))
			वापस;
		अन्यथा अगर (!(पंचांगp & HCB_ACK_BIT) && (clear))
			वापस;
		udelay(1);
	पूर्ण जबतक (समयout--);
	prपूर्णांकk(KERN_ERR "timed out waiting for ack\n");
पूर्ण

अटल पूर्णांक n411_init_control(काष्ठा hecubafb_par *par)
अणु
	अचिन्हित अक्षर पंचांगp;
	/* क्रम init, we want the following setup to be set:
	WUP = lo
	ACK = hi
	DS = hi
	RW = hi
	CD = lo
	*/

	/* ग_लिखो WUP to lo, DS to hi, RW to hi, CD to lo */
	ctl = HCB_WUP_BIT | HCB_RW_BIT | HCB_CD_BIT ;
	n411_set_ctl(par, HCB_DS_BIT, 1);

	/* check ACK is not lo */
	पंचांगp = n411_get_ctl(par);
	अगर (पंचांगp & HCB_ACK_BIT) अणु
		prपूर्णांकk(KERN_ERR "Fail because ACK is already low\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक n411_init_board(काष्ठा hecubafb_par *par)
अणु
	पूर्णांक retval;

	retval = n411_init_control(par);
	अगर (retval)
		वापस retval;

	par->send_command(par, APOLLO_INIT_DISPLAY);
	par->send_data(par, 0x81);

	/* have to रुको जबतक display resets */
	udelay(1000);

	/* अगर we were told to splash the screen, we just clear it */
	अगर (!nosplash) अणु
		par->send_command(par, APOLLO_ERASE_DISPLAY);
		par->send_data(par, splashval);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा hecuba_board n411_board = अणु
	.owner			= THIS_MODULE,
	.init			= n411_init_board,
	.set_ctl		= n411_set_ctl,
	.set_data		= n411_set_data,
	.रुको_क्रम_ack		= n411_रुको_क्रम_ack,
पूर्ण;

अटल काष्ठा platक्रमm_device *n411_device;
अटल पूर्णांक __init n411_init(व्योम)
अणु
	पूर्णांक ret;
	अगर (!dio_addr || !cio_addr || !c2io_addr) अणु
		prपूर्णांकk(KERN_WARNING "no IO addresses supplied\n");
		वापस -EINVAL;
	पूर्ण

	/* request our platक्रमm independent driver */
	request_module("hecubafb");

	n411_device = platक्रमm_device_alloc("hecubafb", -1);
	अगर (!n411_device)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_data(n411_device, &n411_board,
				       माप(n411_board));
	अगर (ret)
		जाओ put_plat_device;

	/* this _add binds hecubafb to n411. hecubafb refcounts n411 */
	ret = platक्रमm_device_add(n411_device);

	अगर (ret)
		जाओ put_plat_device;

	वापस 0;

put_plat_device:
	platक्रमm_device_put(n411_device);
	वापस ret;
पूर्ण

अटल व्योम __निकास n411_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(n411_device);
पूर्ण

module_init(n411_init);
module_निकास(n411_निकास);

module_param(nosplash, uपूर्णांक, 0);
MODULE_PARM_DESC(nosplash, "Disable doing the splash screen");
module_param_hw(dio_addr, uदीर्घ, ioport, 0);
MODULE_PARM_DESC(dio_addr, "IO address for data, eg: 0x480");
module_param_hw(cio_addr, uदीर्घ, ioport, 0);
MODULE_PARM_DESC(cio_addr, "IO address for control, eg: 0x400");
module_param_hw(c2io_addr, uदीर्घ, ioport, 0);
MODULE_PARM_DESC(c2io_addr, "IO address for secondary control, eg: 0x408");
module_param(splashval, uदीर्घ, 0);
MODULE_PARM_DESC(splashval, "Splash pattern: 0x00 is black, 0x01 is white");

MODULE_DESCRIPTION("board driver for n411 hecuba/apollo epd kit");
MODULE_AUTHOR("Jaya Kumar");
MODULE_LICENSE("GPL");

