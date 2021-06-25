<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Zoltrix Radio Plus driver
 * Copyright 1998 C. van Schaik <carl@leg.uct.ac.za>
 *
 * BUGS
 *  Due to the inconsistency in पढ़ोing from the संकेत flags
 *  it is dअगरficult to get an accurate tuned संकेत.
 *
 *  It seems that the card is not linear to 0 volume. It cuts off
 *  at a low volume, and it is not possible (at least I have not found)
 *  to get fine volume control over the low volume range.
 *
 *  Some code derived from code by Romolo Manfredini
 *				   romolo@bicnet.it
 *
 * 1999-05-06 - (C. van Schaik)
 *	      - Make संकेत strength and stereo scans
 *		kinder to cpu जबतक in delay
 * 1999-01-05 - (C. van Schaik)
 *	      - Changed tuning to 1/160Mhz accuracy
 *	      - Added stereo support
 *		(card शेषs to stereo)
 *		(can explicitly क्रमce mono on the card)
 *		(can detect अगर station is in stereo)
 *	      - Added unmute function
 *	      - Reworked ioctl functions
 * 2002-07-15 - Fix Stereo typo
 *
 * 2006-07-24 - Converted to V4L2 API
 *		by Mauro Carvalho Chehab <mchehab@kernel.org>
 *
 * Converted to the radio-isa framework by Hans Verkuil <hans.verkuil@cisco.com>
 *
 * Note that this is the driver क्रम the Zoltrix Radio Plus.
 * This driver करोes not work क्रम the Zoltrix Radio Plus 108 or the
 * Zoltrix Radio Plus क्रम Winकरोws.
 *
 * Fully tested with the Keene USB FM Transmitter and the v4l2-compliance tool.
 */

#समावेश <linux/module.h>	/* Modules                        */
#समावेश <linux/init.h>		/* Initdata                       */
#समावेश <linux/ioport.h>	/* request_region		  */
#समावेश <linux/delay.h>	/* udelay, msleep                 */
#समावेश <linux/videodev2.h>	/* kernel radio काष्ठाs           */
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>		/* outb, outb_p                   */
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश "radio-isa.h"

MODULE_AUTHOR("C. van Schaik");
MODULE_DESCRIPTION("A driver for the Zoltrix Radio Plus.");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1.99");

#अगर_अघोषित CONFIG_RADIO_ZOLTRIX_PORT
#घोषणा CONFIG_RADIO_ZOLTRIX_PORT -1
#पूर्ण_अगर

#घोषणा ZOLTRIX_MAX 2

अटल पूर्णांक io[ZOLTRIX_MAX] = अणु [0] = CONFIG_RADIO_ZOLTRIX_PORT,
			       [1 ... (ZOLTRIX_MAX - 1)] = -1 पूर्ण;
अटल पूर्णांक radio_nr[ZOLTRIX_MAX] = अणु [0 ... (ZOLTRIX_MAX - 1)] = -1 पूर्ण;

module_param_array(io, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(io, "I/O addresses of the Zoltrix Radio Plus card (0x20c or 0x30c)");
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");

काष्ठा zoltrix अणु
	काष्ठा radio_isa_card isa;
	पूर्णांक curvol;
	bool muted;
पूर्ण;

अटल काष्ठा radio_isa_card *zoltrix_alloc(व्योम)
अणु
	काष्ठा zoltrix *zol = kzalloc(माप(*zol), GFP_KERNEL);

	वापस zol ? &zol->isa : शून्य;
पूर्ण

अटल पूर्णांक zoltrix_s_mute_volume(काष्ठा radio_isa_card *isa, bool mute, पूर्णांक vol)
अणु
	काष्ठा zoltrix *zol = container_of(isa, काष्ठा zoltrix, isa);

	zol->curvol = vol;
	zol->muted = mute;
	अगर (mute || vol == 0) अणु
		outb(0, isa->io);
		outb(0, isa->io);
		inb(isa->io + 3);            /* Zoltrix needs to be पढ़ो to confirm */
		वापस 0;
	पूर्ण

	outb(vol - 1, isa->io);
	msleep(10);
	inb(isa->io + 2);
	वापस 0;
पूर्ण

/* tunes the radio to the desired frequency */
अटल पूर्णांक zoltrix_s_frequency(काष्ठा radio_isa_card *isa, u32 freq)
अणु
	काष्ठा zoltrix *zol = container_of(isa, काष्ठा zoltrix, isa);
	काष्ठा v4l2_device *v4l2_dev = &isa->v4l2_dev;
	अचिन्हित दीर्घ दीर्घ biपंचांगask, f, m;
	bool stereo = isa->stereo;
	पूर्णांक i;

	अगर (freq == 0) अणु
		v4l2_warn(v4l2_dev, "cannot set a frequency of 0.\n");
		वापस -EINVAL;
	पूर्ण

	m = (freq / 160 - 8800) * 2;
	f = (अचिन्हित दीर्घ दीर्घ)m + 0x4d1c;

	biपंचांगask = 0xc480402c10080000ull;
	i = 45;

	outb(0, isa->io);
	outb(0, isa->io);
	inb(isa->io + 3);            /* Zoltrix needs to be पढ़ो to confirm */

	outb(0x40, isa->io);
	outb(0xc0, isa->io);

	biपंचांगask = (biपंचांगask ^ ((f & 0xff) << 47) ^ ((f & 0xff00) << 30) ^ (stereo << 31));
	जबतक (i--) अणु
		अगर ((biपंचांगask & 0x8000000000000000ull) != 0) अणु
			outb(0x80, isa->io);
			udelay(50);
			outb(0x00, isa->io);
			udelay(50);
			outb(0x80, isa->io);
			udelay(50);
		पूर्ण अन्यथा अणु
			outb(0xc0, isa->io);
			udelay(50);
			outb(0x40, isa->io);
			udelay(50);
			outb(0xc0, isa->io);
			udelay(50);
		पूर्ण
		biपंचांगask *= 2;
	पूर्ण
	/* termination sequence */
	outb(0x80, isa->io);
	outb(0xc0, isa->io);
	outb(0x40, isa->io);
	udelay(1000);
	inb(isa->io + 2);
	udelay(1000);

	वापस zoltrix_s_mute_volume(isa, zol->muted, zol->curvol);
पूर्ण

/* Get संकेत strength */
अटल u32 zoltrix_g_rxsubchans(काष्ठा radio_isa_card *isa)
अणु
	काष्ठा zoltrix *zol = container_of(isa, काष्ठा zoltrix, isa);
	पूर्णांक a, b;

	outb(0x00, isa->io);         /* This stuff I found to करो nothing */
	outb(zol->curvol, isa->io);
	msleep(20);

	a = inb(isa->io);
	msleep(10);
	b = inb(isa->io);

	वापस (a == b && a == 0xcf) ?
		V4L2_TUNER_SUB_STEREO : V4L2_TUNER_SUB_MONO;
पूर्ण

अटल u32 zoltrix_g_संकेत(काष्ठा radio_isa_card *isa)
अणु
	काष्ठा zoltrix *zol = container_of(isa, काष्ठा zoltrix, isa);
	पूर्णांक a, b;

	outb(0x00, isa->io);         /* This stuff I found to करो nothing */
	outb(zol->curvol, isa->io);
	msleep(20);

	a = inb(isa->io);
	msleep(10);
	b = inb(isa->io);

	अगर (a != b)
		वापस 0;

	/* I found this out by playing with a binary scanner on the card io */
	वापस (a == 0xcf || a == 0xdf || a == 0xef) ? 0xffff : 0;
पूर्ण

अटल पूर्णांक zoltrix_s_stereo(काष्ठा radio_isa_card *isa, bool stereo)
अणु
	वापस zoltrix_s_frequency(isa, isa->freq);
पूर्ण

अटल स्थिर काष्ठा radio_isa_ops zoltrix_ops = अणु
	.alloc = zoltrix_alloc,
	.s_mute_volume = zoltrix_s_mute_volume,
	.s_frequency = zoltrix_s_frequency,
	.s_stereo = zoltrix_s_stereo,
	.g_rxsubchans = zoltrix_g_rxsubchans,
	.g_संकेत = zoltrix_g_संकेत,
पूर्ण;

अटल स्थिर पूर्णांक zoltrix_ioports[] = अणु 0x20c, 0x30c पूर्ण;

अटल काष्ठा radio_isa_driver zoltrix_driver = अणु
	.driver = अणु
		.match		= radio_isa_match,
		.probe		= radio_isa_probe,
		.हटाओ		= radio_isa_हटाओ,
		.driver		= अणु
			.name	= "radio-zoltrix",
		पूर्ण,
	पूर्ण,
	.io_params = io,
	.radio_nr_params = radio_nr,
	.io_ports = zoltrix_ioports,
	.num_of_io_ports = ARRAY_SIZE(zoltrix_ioports),
	.region_size = 2,
	.card = "Zoltrix Radio Plus",
	.ops = &zoltrix_ops,
	.has_stereo = true,
	.max_volume = 15,
पूर्ण;

अटल पूर्णांक __init zoltrix_init(व्योम)
अणु
	वापस isa_रेजिस्टर_driver(&zoltrix_driver.driver, ZOLTRIX_MAX);
पूर्ण

अटल व्योम __निकास zoltrix_निकास(व्योम)
अणु
	isa_unरेजिस्टर_driver(&zoltrix_driver.driver);
पूर्ण

module_init(zoltrix_init);
module_निकास(zoltrix_निकास);

