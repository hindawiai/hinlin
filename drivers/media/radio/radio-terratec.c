<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Terratec ActiveRadio ISA Standalone card driver क्रम Linux radio support
 * (c) 1999 R. Offermanns (rolf@offermanns.de)
 * based on the aimslab radio driver from M. Kirkwood
 * many thanks to Michael Becker and Friedhelm Birth (from TerraTec)
 *
 *
 * History:
 * 1999-05-21	First preview release
 *
 *  Notes on the hardware:
 *  There are two "main" chips on the card:
 *  - Philips OM5610 (http://www-us.semiconductors.philips.com/acrobat/datasheets/OM5610_2.pdf)
 *  - Philips SAA6588 (http://www-us.semiconductors.philips.com/acrobat/datasheets/SAA6588_1.pdf)
 *  (you can get the datasheet at the above links)
 *
 *  Frequency control is करोne digitally -- ie out(port,encodefreq(95.8));
 *  Volume Control is करोne digitally
 *
 * Converted to the radio-isa framework by Hans Verkuil <hans.verkuil@cisco.com>
 * Converted to V4L2 API by Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#समावेश <linux/module.h>	/* Modules			*/
#समावेश <linux/init.h>		/* Initdata			*/
#समावेश <linux/ioport.h>	/* request_region		*/
#समावेश <linux/videodev2.h>	/* kernel radio काष्ठाs		*/
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>		/* outb, outb_p			*/
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश "radio-isa.h"

MODULE_AUTHOR("R. Offermans & others");
MODULE_DESCRIPTION("A driver for the TerraTec ActiveRadio Standalone radio card.");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1.99");

/* Note: there seems to be only one possible port (0x590), but without
   hardware this is hard to verअगरy. For now, this is the only one we will
   support. */
अटल पूर्णांक io = 0x590;
अटल पूर्णांक radio_nr = -1;

module_param(radio_nr, पूर्णांक, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device number");

#घोषणा WRT_DIS		0x00
#घोषणा CLK_OFF		0x00
#घोषणा IIC_DATA	0x01
#घोषणा IIC_CLK		0x02
#घोषणा DATA		0x04
#घोषणा CLK_ON		0x08
#घोषणा WRT_EN		0x10

अटल काष्ठा radio_isa_card *terratec_alloc(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा radio_isa_card), GFP_KERNEL);
पूर्ण

अटल पूर्णांक terratec_s_mute_volume(काष्ठा radio_isa_card *isa, bool mute, पूर्णांक vol)
अणु
	पूर्णांक i;

	अगर (mute)
		vol = 0;
	vol = vol + (vol * 32); /* change both channels */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (vol & (0x80 >> i))
			outb(0x80, isa->io + 1);
		अन्यथा
			outb(0x00, isa->io + 1);
	पूर्ण
	वापस 0;
पूर्ण


/* this is the worst part in this driver */
/* many more or less strange things are going on here, but hey, it works :) */

अटल पूर्णांक terratec_s_frequency(काष्ठा radio_isa_card *isa, u32 freq)
अणु
	पूर्णांक i;
	पूर्णांक p;
	पूर्णांक temp;
	दीर्घ rest;
	अचिन्हित अक्षर buffer[25];		/* we have to bit shअगरt 25 रेजिस्टरs */

	freq = freq / 160;			/* convert the freq. to a nice to handle value */
	स_रखो(buffer, 0, माप(buffer));

	rest = freq * 10 + 10700;	/* I once had understood what is going on here */
					/* maybe some wise guy (friedhelm?) can comment this stuff */
	i = 13;
	p = 10;
	temp = 102400;
	जबतक (rest != 0) अणु
		अगर (rest % temp  == rest)
			buffer[i] = 0;
		अन्यथा अणु
			buffer[i] = 1;
			rest = rest - temp;
		पूर्ण
		i--;
		p--;
		temp = temp / 2;
	पूर्ण

	क्रम (i = 24; i > -1; i--) अणु	/* bit shअगरt the values to the radiocard */
		अगर (buffer[i] == 1) अणु
			outb(WRT_EN | DATA, isa->io);
			outb(WRT_EN | DATA | CLK_ON, isa->io);
			outb(WRT_EN | DATA, isa->io);
		पूर्ण अन्यथा अणु
			outb(WRT_EN | 0x00, isa->io);
			outb(WRT_EN | 0x00 | CLK_ON, isa->io);
		पूर्ण
	पूर्ण
	outb(0x00, isa->io);
	वापस 0;
पूर्ण

अटल u32 terratec_g_संकेत(काष्ठा radio_isa_card *isa)
अणु
	/* bit set = no संकेत present	*/
	वापस (inb(isa->io) & 2) ? 0 : 0xffff;
पूर्ण

अटल स्थिर काष्ठा radio_isa_ops terratec_ops = अणु
	.alloc = terratec_alloc,
	.s_mute_volume = terratec_s_mute_volume,
	.s_frequency = terratec_s_frequency,
	.g_संकेत = terratec_g_संकेत,
पूर्ण;

अटल स्थिर पूर्णांक terratec_ioports[] = अणु 0x590 पूर्ण;

अटल काष्ठा radio_isa_driver terratec_driver = अणु
	.driver = अणु
		.match		= radio_isa_match,
		.probe		= radio_isa_probe,
		.हटाओ		= radio_isa_हटाओ,
		.driver		= अणु
			.name	= "radio-terratec",
		पूर्ण,
	पूर्ण,
	.io_params = &io,
	.radio_nr_params = &radio_nr,
	.io_ports = terratec_ioports,
	.num_of_io_ports = ARRAY_SIZE(terratec_ioports),
	.region_size = 2,
	.card = "TerraTec ActiveRadio",
	.ops = &terratec_ops,
	.has_stereo = true,
	.max_volume = 10,
पूर्ण;

अटल पूर्णांक __init terratec_init(व्योम)
अणु
	वापस isa_रेजिस्टर_driver(&terratec_driver.driver, 1);
पूर्ण

अटल व्योम __निकास terratec_निकास(व्योम)
अणु
	isa_unरेजिस्टर_driver(&terratec_driver.driver);
पूर्ण

module_init(terratec_init);
module_निकास(terratec_निकास);

