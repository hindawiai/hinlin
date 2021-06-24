<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * radio-aztech.c - Aztech radio card driver
 *
 * Converted to the radio-isa framework by Hans Verkuil <hans.verkuil@xs4all.nl>
 * Converted to V4L2 API by Mauro Carvalho Chehab <mchehab@kernel.org>
 * Adapted to support the Video क्रम Linux API by
 * Russell Kroll <rkroll@exploits.org>.  Based on original tuner code by:
 *
 * Quay Ly
 * Donald Song
 * Jason Lewis      (jlewis@twilight.vtc.vsc.edu)
 * Scott McGrath    (smcgrath@twilight.vtc.vsc.edu)
 * William McGrath  (wmcgrath@twilight.vtc.vsc.edu)
 *
 * Fully tested with the Keene USB FM Transmitter and the v4l2-compliance tool.
*/

#समावेश <linux/module.h>	/* Modules			*/
#समावेश <linux/init.h>		/* Initdata			*/
#समावेश <linux/ioport.h>	/* request_region		*/
#समावेश <linux/delay.h>	/* udelay			*/
#समावेश <linux/videodev2.h>	/* kernel radio काष्ठाs		*/
#समावेश <linux/पन.स>		/* outb, outb_p			*/
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश "radio-isa.h"
#समावेश "lm7000.h"

MODULE_AUTHOR("Russell Kroll, Quay Lu, Donald Song, Jason Lewis, Scott McGrath, William McGrath");
MODULE_DESCRIPTION("A driver for the Aztech radio card.");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0.0");

/* acceptable ports: 0x350 (JP3 लघुed), 0x358 (JP3 खोलो) */
#अगर_अघोषित CONFIG_RADIO_AZTECH_PORT
#घोषणा CONFIG_RADIO_AZTECH_PORT -1
#पूर्ण_अगर

#घोषणा AZTECH_MAX 2

अटल पूर्णांक io[AZTECH_MAX] = अणु [0] = CONFIG_RADIO_AZTECH_PORT,
			      [1 ... (AZTECH_MAX - 1)] = -1 पूर्ण;
अटल पूर्णांक radio_nr[AZTECH_MAX]	= अणु [0 ... (AZTECH_MAX - 1)] = -1 पूर्ण;

module_param_array(io, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(io, "I/O addresses of the Aztech card (0x350 or 0x358)");
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");

काष्ठा aztech अणु
	काष्ठा radio_isa_card isa;
	पूर्णांक curvol;
पूर्ण;

/* bit definitions क्रम रेजिस्टर पढ़ो */
#घोषणा AZTECH_BIT_NOT_TUNED	(1 << 0)
#घोषणा AZTECH_BIT_MONO		(1 << 1)
/* bit definitions क्रम रेजिस्टर ग_लिखो */
#घोषणा AZTECH_BIT_TUN_CE	(1 << 1)
#घोषणा AZTECH_BIT_TUN_CLK	(1 << 6)
#घोषणा AZTECH_BIT_TUN_DATA	(1 << 7)
/* bits 0 and 2 are volume control, bits 3..5 are not connected */

अटल व्योम aztech_set_pins(व्योम *handle, u8 pins)
अणु
	काष्ठा radio_isa_card *isa = handle;
	काष्ठा aztech *az = container_of(isa, काष्ठा aztech, isa);
	u8 bits = az->curvol;

	अगर (pins & LM7000_DATA)
		bits |= AZTECH_BIT_TUN_DATA;
	अगर (pins & LM7000_CLK)
		bits |= AZTECH_BIT_TUN_CLK;
	अगर (pins & LM7000_CE)
		bits |= AZTECH_BIT_TUN_CE;

	outb_p(bits, az->isa.io);
पूर्ण

अटल काष्ठा radio_isa_card *aztech_alloc(व्योम)
अणु
	काष्ठा aztech *az = kzalloc(माप(*az), GFP_KERNEL);

	वापस az ? &az->isa : शून्य;
पूर्ण

अटल पूर्णांक aztech_s_frequency(काष्ठा radio_isa_card *isa, u32 freq)
अणु
	lm7000_set_freq(freq, isa, aztech_set_pins);

	वापस 0;
पूर्ण

अटल u32 aztech_g_rxsubchans(काष्ठा radio_isa_card *isa)
अणु
	अगर (inb(isa->io) & AZTECH_BIT_MONO)
		वापस V4L2_TUNER_SUB_MONO;
	वापस V4L2_TUNER_SUB_STEREO;
पूर्ण

अटल u32 aztech_g_संकेत(काष्ठा radio_isa_card *isa)
अणु
	वापस (inb(isa->io) & AZTECH_BIT_NOT_TUNED) ? 0 : 0xffff;
पूर्ण

अटल पूर्णांक aztech_s_mute_volume(काष्ठा radio_isa_card *isa, bool mute, पूर्णांक vol)
अणु
	काष्ठा aztech *az = container_of(isa, काष्ठा aztech, isa);

	अगर (mute)
		vol = 0;
	az->curvol = (vol & 1) + ((vol & 2) << 1);
	outb(az->curvol, isa->io);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा radio_isa_ops aztech_ops = अणु
	.alloc = aztech_alloc,
	.s_mute_volume = aztech_s_mute_volume,
	.s_frequency = aztech_s_frequency,
	.g_rxsubchans = aztech_g_rxsubchans,
	.g_संकेत = aztech_g_संकेत,
पूर्ण;

अटल स्थिर पूर्णांक aztech_ioports[] = अणु 0x350, 0x358 पूर्ण;

अटल काष्ठा radio_isa_driver aztech_driver = अणु
	.driver = अणु
		.match		= radio_isa_match,
		.probe		= radio_isa_probe,
		.हटाओ		= radio_isa_हटाओ,
		.driver		= अणु
			.name	= "radio-aztech",
		पूर्ण,
	पूर्ण,
	.io_params = io,
	.radio_nr_params = radio_nr,
	.io_ports = aztech_ioports,
	.num_of_io_ports = ARRAY_SIZE(aztech_ioports),
	.region_size = 8,
	.card = "Aztech Radio",
	.ops = &aztech_ops,
	.has_stereo = true,
	.max_volume = 3,
पूर्ण;

अटल पूर्णांक __init aztech_init(व्योम)
अणु
	वापस isa_रेजिस्टर_driver(&aztech_driver.driver, AZTECH_MAX);
पूर्ण

अटल व्योम __निकास aztech_निकास(व्योम)
अणु
	isa_unरेजिस्टर_driver(&aztech_driver.driver);
पूर्ण

module_init(aztech_init);
module_निकास(aztech_निकास);
