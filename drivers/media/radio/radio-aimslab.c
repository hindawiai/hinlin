<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AimsLab RadioTrack (aka RadioVeveal) driver
 *
 * Copyright 1997 M. Kirkwood
 *
 * Converted to the radio-isa framework by Hans Verkuil <hans.verkuil@cisco.com>
 * Converted to V4L2 API by Mauro Carvalho Chehab <mchehab@kernel.org>
 * Converted to new API by Alan Cox <alan@lxorguk.ukuu.org.uk>
 * Various bugfixes and enhancements by Russell Kroll <rkroll@exploits.org>
 *
 * Notes on the hardware (reverse engineered from other peoples'
 * reverse engineering of AIMS' code :-)
 *
 *  Frequency control is करोne digitally -- ie out(port,encodefreq(95.8));
 *
 *  The संकेत strength query is unsurprisingly inaccurate.  And it seems
 *  to indicate that (on my card, at least) the frequency setting isn't
 *  too great.  (I have to tune up .025MHz from what the freq should be
 *  to get a report that the thing is tuned.)
 *
 *  Volume control is (ugh) analogue:
 *   out(port, start_increasing_volume);
 *   रुको(a_wee_जबतक);
 *   out(port, stop_changing_the_volume);
 *
 * Fully tested with the Keene USB FM Transmitter and the v4l2-compliance tool.
 */

#समावेश <linux/module.h>	/* Modules			*/
#समावेश <linux/init.h>		/* Initdata			*/
#समावेश <linux/ioport.h>	/* request_region		*/
#समावेश <linux/delay.h>	/* msleep			*/
#समावेश <linux/videodev2.h>	/* kernel radio काष्ठाs		*/
#समावेश <linux/पन.स>		/* outb, outb_p			*/
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश "radio-isa.h"
#समावेश "lm7000.h"

MODULE_AUTHOR("M. Kirkwood");
MODULE_DESCRIPTION("A driver for the RadioTrack/RadioReveal radio card.");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0.0");

#अगर_अघोषित CONFIG_RADIO_RTRACK_PORT
#घोषणा CONFIG_RADIO_RTRACK_PORT -1
#पूर्ण_अगर

#घोषणा RTRACK_MAX 2

अटल पूर्णांक io[RTRACK_MAX] = अणु [0] = CONFIG_RADIO_RTRACK_PORT,
			      [1 ... (RTRACK_MAX - 1)] = -1 पूर्ण;
अटल पूर्णांक radio_nr[RTRACK_MAX]	= अणु [0 ... (RTRACK_MAX - 1)] = -1 पूर्ण;

module_param_array(io, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(io, "I/O addresses of the RadioTrack card (0x20f or 0x30f)");
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");

काष्ठा rtrack अणु
	काष्ठा radio_isa_card isa;
	पूर्णांक curvol;
पूर्ण;

अटल काष्ठा radio_isa_card *rtrack_alloc(व्योम)
अणु
	काष्ठा rtrack *rt = kzalloc(माप(काष्ठा rtrack), GFP_KERNEL);

	अगर (rt)
		rt->curvol = 0xff;
	वापस rt ? &rt->isa : शून्य;
पूर्ण

#घोषणा AIMS_BIT_TUN_CE		(1 << 0)
#घोषणा AIMS_BIT_TUN_CLK	(1 << 1)
#घोषणा AIMS_BIT_TUN_DATA	(1 << 2)
#घोषणा AIMS_BIT_VOL_CE		(1 << 3)
#घोषणा AIMS_BIT_TUN_STRQ	(1 << 4)
/* bit 5 is not connected */
#घोषणा AIMS_BIT_VOL_UP		(1 << 6)	/* active low */
#घोषणा AIMS_BIT_VOL_DN		(1 << 7)	/* active low */

अटल व्योम rtrack_set_pins(व्योम *handle, u8 pins)
अणु
	काष्ठा radio_isa_card *isa = handle;
	काष्ठा rtrack *rt = container_of(isa, काष्ठा rtrack, isa);
	u8 bits = AIMS_BIT_VOL_DN | AIMS_BIT_VOL_UP | AIMS_BIT_TUN_STRQ;

	अगर (!v4l2_ctrl_g_ctrl(rt->isa.mute))
		bits |= AIMS_BIT_VOL_CE;

	अगर (pins & LM7000_DATA)
		bits |= AIMS_BIT_TUN_DATA;
	अगर (pins & LM7000_CLK)
		bits |= AIMS_BIT_TUN_CLK;
	अगर (pins & LM7000_CE)
		bits |= AIMS_BIT_TUN_CE;

	outb_p(bits, rt->isa.io);
पूर्ण

अटल पूर्णांक rtrack_s_frequency(काष्ठा radio_isa_card *isa, u32 freq)
अणु
	lm7000_set_freq(freq, isa, rtrack_set_pins);

	वापस 0;
पूर्ण

अटल u32 rtrack_g_संकेत(काष्ठा radio_isa_card *isa)
अणु
	/* bit set = no संकेत present */
	वापस 0xffff * !(inb(isa->io) & 2);
पूर्ण

अटल पूर्णांक rtrack_s_mute_volume(काष्ठा radio_isa_card *isa, bool mute, पूर्णांक vol)
अणु
	काष्ठा rtrack *rt = container_of(isa, काष्ठा rtrack, isa);
	पूर्णांक curvol = rt->curvol;

	अगर (mute) अणु
		outb(0xd0, isa->io);	/* volume steady + sigstr + off	*/
		वापस 0;
	पूर्ण
	अगर (vol == 0) अणु			/* volume = 0 means mute the card */
		outb(0x48, isa->io);	/* volume करोwn but still "on"	*/
		msleep(curvol * 3);	/* make sure it's totally करोwn	*/
	पूर्ण अन्यथा अगर (curvol < vol) अणु
		outb(0x98, isa->io);	/* volume up + sigstr + on	*/
		क्रम (; curvol < vol; curvol++)
			mdelay(3);
	पूर्ण अन्यथा अगर (curvol > vol) अणु
		outb(0x58, isa->io);	/* volume करोwn + sigstr + on	*/
		क्रम (; curvol > vol; curvol--)
			mdelay(3);
	पूर्ण
	outb(0xd8, isa->io);		/* volume steady + sigstr + on	*/
	rt->curvol = vol;
	वापस 0;
पूर्ण

/* Mute card - prevents noisy bootups */
अटल पूर्णांक rtrack_initialize(काष्ठा radio_isa_card *isa)
अणु
	/* this ensures that the volume is all the way up  */
	outb(0x90, isa->io);	/* volume up but still "on"	*/
	msleep(3000);		/* make sure it's totally up	*/
	outb(0xc0, isa->io);	/* steady volume, mute card	*/
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा radio_isa_ops rtrack_ops = अणु
	.alloc = rtrack_alloc,
	.init = rtrack_initialize,
	.s_mute_volume = rtrack_s_mute_volume,
	.s_frequency = rtrack_s_frequency,
	.g_संकेत = rtrack_g_संकेत,
पूर्ण;

अटल स्थिर पूर्णांक rtrack_ioports[] = अणु 0x20f, 0x30f पूर्ण;

अटल काष्ठा radio_isa_driver rtrack_driver = अणु
	.driver = अणु
		.match		= radio_isa_match,
		.probe		= radio_isa_probe,
		.हटाओ		= radio_isa_हटाओ,
		.driver		= अणु
			.name	= "radio-aimslab",
		पूर्ण,
	पूर्ण,
	.io_params = io,
	.radio_nr_params = radio_nr,
	.io_ports = rtrack_ioports,
	.num_of_io_ports = ARRAY_SIZE(rtrack_ioports),
	.region_size = 2,
	.card = "AIMSlab RadioTrack/RadioReveal",
	.ops = &rtrack_ops,
	.has_stereo = true,
	.max_volume = 0xff,
पूर्ण;

अटल पूर्णांक __init rtrack_init(व्योम)
अणु
	वापस isa_रेजिस्टर_driver(&rtrack_driver.driver, RTRACK_MAX);
पूर्ण

अटल व्योम __निकास rtrack_निकास(व्योम)
अणु
	isa_unरेजिस्टर_driver(&rtrack_driver.driver);
पूर्ण

module_init(rtrack_init);
module_निकास(rtrack_निकास);
