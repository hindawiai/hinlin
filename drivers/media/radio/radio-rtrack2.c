<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RadioTrack II driver
 * Copyright 1998 Ben Pfaff
 *
 * Based on RadioTrack I/RadioReveal (C) 1997 M. Kirkwood
 * Converted to new API by Alan Cox <alan@lxorguk.ukuu.org.uk>
 * Various bugfixes and enhancements by Russell Kroll <rkroll@exploits.org>
 *
 * Converted to the radio-isa framework by Hans Verkuil <hans.verkuil@cisco.com>
 * Converted to V4L2 API by Mauro Carvalho Chehab <mchehab@kernel.org>
 *
 * Fully tested with actual hardware and the v4l2-compliance tool.
 */

#समावेश <linux/module.h>	/* Modules			*/
#समावेश <linux/init.h>		/* Initdata			*/
#समावेश <linux/ioport.h>	/* request_region		*/
#समावेश <linux/delay.h>	/* udelay			*/
#समावेश <linux/videodev2.h>	/* kernel radio काष्ठाs		*/
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>		/* outb, outb_p			*/
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश "radio-isa.h"

MODULE_AUTHOR("Ben Pfaff");
MODULE_DESCRIPTION("A driver for the RadioTrack II radio card.");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1.99");

#अगर_अघोषित CONFIG_RADIO_RTRACK2_PORT
#घोषणा CONFIG_RADIO_RTRACK2_PORT -1
#पूर्ण_अगर

#घोषणा RTRACK2_MAX 2

अटल पूर्णांक io[RTRACK2_MAX] = अणु [0] = CONFIG_RADIO_RTRACK2_PORT,
			      [1 ... (RTRACK2_MAX - 1)] = -1 पूर्ण;
अटल पूर्णांक radio_nr[RTRACK2_MAX] = अणु [0 ... (RTRACK2_MAX - 1)] = -1 पूर्ण;

module_param_array(io, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(io, "I/O addresses of the RadioTrack card (0x20f or 0x30f)");
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");

अटल काष्ठा radio_isa_card *rtrack2_alloc(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा radio_isa_card), GFP_KERNEL);
पूर्ण

अटल व्योम zero(काष्ठा radio_isa_card *isa)
अणु
	outb_p(1, isa->io);
	outb_p(3, isa->io);
	outb_p(1, isa->io);
पूर्ण

अटल व्योम one(काष्ठा radio_isa_card *isa)
अणु
	outb_p(5, isa->io);
	outb_p(7, isa->io);
	outb_p(5, isa->io);
पूर्ण

अटल पूर्णांक rtrack2_s_frequency(काष्ठा radio_isa_card *isa, u32 freq)
अणु
	पूर्णांक i;

	freq = freq / 200 + 856;

	outb_p(0xc8, isa->io);
	outb_p(0xc9, isa->io);
	outb_p(0xc9, isa->io);

	क्रम (i = 0; i < 10; i++)
		zero(isa);

	क्रम (i = 14; i >= 0; i--)
		अगर (freq & (1 << i))
			one(isa);
		अन्यथा
			zero(isa);

	outb_p(0xc8, isa->io);
	outb_p(v4l2_ctrl_g_ctrl(isa->mute), isa->io);
	वापस 0;
पूर्ण

अटल u32 rtrack2_g_संकेत(काष्ठा radio_isa_card *isa)
अणु
	/* bit set = no संकेत present	*/
	वापस (inb(isa->io) & 2) ? 0 : 0xffff;
पूर्ण

अटल पूर्णांक rtrack2_s_mute_volume(काष्ठा radio_isa_card *isa, bool mute, पूर्णांक vol)
अणु
	outb(mute, isa->io);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा radio_isa_ops rtrack2_ops = अणु
	.alloc = rtrack2_alloc,
	.s_mute_volume = rtrack2_s_mute_volume,
	.s_frequency = rtrack2_s_frequency,
	.g_संकेत = rtrack2_g_संकेत,
पूर्ण;

अटल स्थिर पूर्णांक rtrack2_ioports[] = अणु 0x20f, 0x30f पूर्ण;

अटल काष्ठा radio_isa_driver rtrack2_driver = अणु
	.driver = अणु
		.match		= radio_isa_match,
		.probe		= radio_isa_probe,
		.हटाओ		= radio_isa_हटाओ,
		.driver		= अणु
			.name	= "radio-rtrack2",
		पूर्ण,
	पूर्ण,
	.io_params = io,
	.radio_nr_params = radio_nr,
	.io_ports = rtrack2_ioports,
	.num_of_io_ports = ARRAY_SIZE(rtrack2_ioports),
	.region_size = 4,
	.card = "AIMSlab RadioTrack II",
	.ops = &rtrack2_ops,
	.has_stereo = true,
पूर्ण;

अटल पूर्णांक __init rtrack2_init(व्योम)
अणु
	वापस isa_रेजिस्टर_driver(&rtrack2_driver.driver, RTRACK2_MAX);
पूर्ण

अटल व्योम __निकास rtrack2_निकास(व्योम)
अणु
	isa_unरेजिस्टर_driver(&rtrack2_driver.driver);
पूर्ण

module_init(rtrack2_init);
module_निकास(rtrack2_निकास);
