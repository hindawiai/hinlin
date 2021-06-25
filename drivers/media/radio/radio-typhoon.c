<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Typhoon Radio Card driver क्रम radio support
 * (c) 1999 Dr. Henrik Seidel <Henrik.Seidel@gmx.de>
 *
 * Notes on the hardware
 *
 * This card has two output sockets, one क्रम speakers and one क्रम line.
 * The speaker output has volume control, but only in four discrete
 * steps. The line output has neither volume control nor mute.
 *
 * The card has स्वतः-stereo according to its manual, although it all
 * sounds mono to me (even with the Win/DOS drivers). Maybe it's my
 * antenna - I really करोn't know क्रम sure.
 *
 * Frequency control is करोne digitally.
 *
 * Volume control is करोne digitally, but there are only four dअगरferent
 * possible values. So you should better always turn the volume up and
 * use line control. I got the best results by connecting line output
 * to the sound card microphone input. For such a configuration the
 * volume control has no effect, since volume control only influences
 * the speaker output.
 *
 * There is no explicit mute/unmute. So I set the radio frequency to a
 * value where I करो expect just noise and turn the speaker volume करोwn.
 * The frequency change is necessary since the card never seems to be
 * completely silent.
 *
 * Converted to V4L2 API by Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#समावेश <linux/module.h>	/* Modules                        */
#समावेश <linux/init.h>		/* Initdata                       */
#समावेश <linux/ioport.h>	/* request_region		  */
#समावेश <linux/videodev2.h>	/* kernel radio काष्ठाs           */
#समावेश <linux/पन.स>		/* outb, outb_p                   */
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश "radio-isa.h"

#घोषणा DRIVER_VERSION "0.1.2"

MODULE_AUTHOR("Dr. Henrik Seidel");
MODULE_DESCRIPTION("A driver for the Typhoon radio card (a.k.a. EcoRadio).");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1.99");

#अगर_अघोषित CONFIG_RADIO_TYPHOON_PORT
#घोषणा CONFIG_RADIO_TYPHOON_PORT -1
#पूर्ण_अगर

#अगर_अघोषित CONFIG_RADIO_TYPHOON_MUTEFREQ
#घोषणा CONFIG_RADIO_TYPHOON_MUTEFREQ 87000
#पूर्ण_अगर

#घोषणा TYPHOON_MAX 2

अटल पूर्णांक io[TYPHOON_MAX] = अणु [0] = CONFIG_RADIO_TYPHOON_PORT,
			      [1 ... (TYPHOON_MAX - 1)] = -1 पूर्ण;
अटल पूर्णांक radio_nr[TYPHOON_MAX]	= अणु [0 ... (TYPHOON_MAX - 1)] = -1 पूर्ण;
अटल अचिन्हित दीर्घ mutefreq = CONFIG_RADIO_TYPHOON_MUTEFREQ;

module_param_array(io, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(io, "I/O addresses of the Typhoon card (0x316 or 0x336)");
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");
module_param(mutefreq, uदीर्घ, 0);
MODULE_PARM_DESC(mutefreq, "Frequency used when muting the card (in kHz)");

काष्ठा typhoon अणु
	काष्ठा radio_isa_card isa;
	पूर्णांक muted;
पूर्ण;

अटल काष्ठा radio_isa_card *typhoon_alloc(व्योम)
अणु
	काष्ठा typhoon *ty = kzalloc(माप(*ty), GFP_KERNEL);

	वापस ty ? &ty->isa : शून्य;
पूर्ण

अटल पूर्णांक typhoon_s_frequency(काष्ठा radio_isa_card *isa, u32 freq)
अणु
	अचिन्हित दीर्घ outval;
	अचिन्हित दीर्घ x;

	/*
	 * The frequency transfer curve is not linear. The best fit I could
	 * get is
	 *
	 * outval = -155 + exp((f + 15.55) * 0.057))
	 *
	 * where frequency f is in MHz. Since we करोn't have exp in the kernel,
	 * I approximate this function by a third order polynomial.
	 *
	 */

	x = freq / 160;
	outval = (x * x + 2500) / 5000;
	outval = (outval * x + 5000) / 10000;
	outval -= (10 * x * x + 10433) / 20866;
	outval += 4 * x - 11505;

	outb_p((outval >> 8) & 0x01, isa->io + 4);
	outb_p(outval >> 9, isa->io + 6);
	outb_p(outval & 0xff, isa->io + 8);
	वापस 0;
पूर्ण

अटल पूर्णांक typhoon_s_mute_volume(काष्ठा radio_isa_card *isa, bool mute, पूर्णांक vol)
अणु
	काष्ठा typhoon *ty = container_of(isa, काष्ठा typhoon, isa);

	अगर (mute)
		vol = 0;
	vol >>= 14;			/* Map 16 bit to 2 bit */
	vol &= 3;
	outb_p(vol / 2, isa->io);	/* Set the volume, high bit. */
	outb_p(vol % 2, isa->io + 2);	/* Set the volume, low bit. */

	अगर (vol == 0 && !ty->muted) अणु
		ty->muted = true;
		वापस typhoon_s_frequency(isa, mutefreq << 4);
	पूर्ण
	अगर (vol && ty->muted) अणु
		ty->muted = false;
		वापस typhoon_s_frequency(isa, isa->freq);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा radio_isa_ops typhoon_ops = अणु
	.alloc = typhoon_alloc,
	.s_mute_volume = typhoon_s_mute_volume,
	.s_frequency = typhoon_s_frequency,
पूर्ण;

अटल स्थिर पूर्णांक typhoon_ioports[] = अणु 0x316, 0x336 पूर्ण;

अटल काष्ठा radio_isa_driver typhoon_driver = अणु
	.driver = अणु
		.match		= radio_isa_match,
		.probe		= radio_isa_probe,
		.हटाओ		= radio_isa_हटाओ,
		.driver		= अणु
			.name	= "radio-typhoon",
		पूर्ण,
	पूर्ण,
	.io_params = io,
	.radio_nr_params = radio_nr,
	.io_ports = typhoon_ioports,
	.num_of_io_ports = ARRAY_SIZE(typhoon_ioports),
	.region_size = 8,
	.card = "Typhoon Radio",
	.ops = &typhoon_ops,
	.has_stereo = true,
	.max_volume = 3,
पूर्ण;

अटल पूर्णांक __init typhoon_init(व्योम)
अणु
	अगर (mutefreq < 87000 || mutefreq > 108000) अणु
		prपूर्णांकk(KERN_ERR "%s: You must set a frequency (in kHz) used when muting the card,\n",
				typhoon_driver.driver.driver.name);
		prपूर्णांकk(KERN_ERR "%s: e.g. with \"mutefreq=87500\" (87000 <= mutefreq <= 108000)\n",
				typhoon_driver.driver.driver.name);
		वापस -ENODEV;
	पूर्ण
	वापस isa_रेजिस्टर_driver(&typhoon_driver.driver, TYPHOON_MAX);
पूर्ण

अटल व्योम __निकास typhoon_निकास(व्योम)
अणु
	isa_unरेजिस्टर_driver(&typhoon_driver.driver);
पूर्ण


module_init(typhoon_init);
module_निकास(typhoon_निकास);

