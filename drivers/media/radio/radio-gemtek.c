<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GemTek radio card driver
 *
 * Copyright 1998 Jonas Munsin <jmunsin@iki.fi>
 *
 * GemTek hasn't released any specs on the card, so the protocol had to
 * be reverse engineered with करोsemu.
 *
 * Besides the protocol changes, this is mostly a copy of:
 *
 *    RadioTrack II driver क्रम Linux radio support (C) 1998 Ben Pfaff
 *
 *    Based on RadioTrack I/RadioReveal (C) 1997 M. Kirkwood
 *    Converted to new API by Alan Cox <alan@lxorguk.ukuu.org.uk>
 *    Various bugfixes and enhancements by Russell Kroll <rkroll@exploits.org>
 *
 * Converted to the radio-isa framework by Hans Verkuil <hans.verkuil@cisco.com>
 * Converted to V4L2 API by Mauro Carvalho Chehab <mchehab@kernel.org>
 *
 * Note: this card seems to swap the left and right audio channels!
 *
 * Fully tested with the Keene USB FM Transmitter and the v4l2-compliance tool.
 */

#समावेश <linux/module.h>	/* Modules			*/
#समावेश <linux/init.h>		/* Initdata			*/
#समावेश <linux/ioport.h>	/* request_region		*/
#समावेश <linux/delay.h>	/* udelay			*/
#समावेश <linux/videodev2.h>	/* kernel radio काष्ठाs		*/
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>		/* outb, outb_p			*/
#समावेश <linux/pnp.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश "radio-isa.h"

/*
 * Module info.
 */

MODULE_AUTHOR("Jonas Munsin, Pekka Seppथअnen <pexu@kapsi.fi>");
MODULE_DESCRIPTION("A driver for the GemTek Radio card.");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0.0");

/*
 * Module params.
 */

#अगर_अघोषित CONFIG_RADIO_GEMTEK_PORT
#घोषणा CONFIG_RADIO_GEMTEK_PORT -1
#पूर्ण_अगर
#अगर_अघोषित CONFIG_RADIO_GEMTEK_PROBE
#घोषणा CONFIG_RADIO_GEMTEK_PROBE 1
#पूर्ण_अगर

#घोषणा GEMTEK_MAX 4

अटल bool probe = CONFIG_RADIO_GEMTEK_PROBE;
अटल bool hardmute;
अटल पूर्णांक io[GEMTEK_MAX] = अणु [0] = CONFIG_RADIO_GEMTEK_PORT,
			      [1 ... (GEMTEK_MAX - 1)] = -1 पूर्ण;
अटल पूर्णांक radio_nr[GEMTEK_MAX]	= अणु [0 ... (GEMTEK_MAX - 1)] = -1 पूर्ण;

module_param(probe, bool, 0444);
MODULE_PARM_DESC(probe, "Enable automatic device probing.");

module_param(hardmute, bool, 0644);
MODULE_PARM_DESC(hardmute, "Enable 'hard muting' by shutting down PLL, may reduce static noise.");

module_param_array(io, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(io, "Force I/O ports for the GemTek Radio card if automatic probing is disabled or fails. The most common I/O ports are: 0x20c 0x30c, 0x24c or 0x34c (0x20c, 0x248 and 0x28c have been reported to work for the combined sound/radiocard).");

module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");

/*
 * Frequency calculation स्थिरants.  Intermediate frequency 10.52 MHz (nominal
 * value 10.7 MHz), reference भागisor 6.39 kHz (nominal 6.25 kHz).
 */
#घोषणा FSCALE		8
#घोषणा IF_OFFSET	((अचिन्हित पूर्णांक)(10.52 * 16000 * (1<<FSCALE)))
#घोषणा REF_FREQ	((अचिन्हित पूर्णांक)(6.39 * 16 * (1<<FSCALE)))

#घोषणा GEMTEK_CK		0x01	/* Clock संकेत			*/
#घोषणा GEMTEK_DA		0x02	/* Serial data			*/
#घोषणा GEMTEK_CE		0x04	/* Chip enable			*/
#घोषणा GEMTEK_NS		0x08	/* No संकेत			*/
#घोषणा GEMTEK_MT		0x10	/* Line mute			*/
#घोषणा GEMTEK_STDF_3_125_KHZ	0x01	/* Standard frequency 3.125 kHz	*/
#घोषणा GEMTEK_PLL_OFF		0x07	/* PLL off			*/

#घोषणा BU2614_BUS_SIZE	32	/* BU2614 / BU2614FS bus size		*/

#घोषणा SHORT_DELAY 5		/* usec */
#घोषणा LONG_DELAY 75		/* usec */

काष्ठा gemtek अणु
	काष्ठा radio_isa_card isa;
	bool muted;
	u32 bu2614data;
पूर्ण;

#घोषणा BU2614_FREQ_BITS	16 /* D0..D15, Frequency data		*/
#घोषणा BU2614_PORT_BITS	3 /* P0..P2, Output port control data	*/
#घोषणा BU2614_VOID_BITS	4 /* unused				*/
#घोषणा BU2614_FMES_BITS	1 /* CT, Frequency measurement beginning data */
#घोषणा BU2614_STDF_BITS	3 /* R0..R2, Standard frequency data	*/
#घोषणा BU2614_SWIN_BITS	1 /* S, Switch between FMIN / AMIN	*/
#घोषणा BU2614_SWAL_BITS        1 /* PS, Swallow counter भागision (AMIN only)*/
#घोषणा BU2614_VOID2_BITS	1 /* unused				*/
#घोषणा BU2614_FMUN_BITS	1 /* GT, Frequency measurement समय & unlock */
#घोषणा BU2614_TEST_BITS	1 /* TS, Test data is input		*/

#घोषणा BU2614_FREQ_SHIFT	0
#घोषणा BU2614_PORT_SHIFT	(BU2614_FREQ_BITS + BU2614_FREQ_SHIFT)
#घोषणा BU2614_VOID_SHIFT	(BU2614_PORT_BITS + BU2614_PORT_SHIFT)
#घोषणा BU2614_FMES_SHIFT	(BU2614_VOID_BITS + BU2614_VOID_SHIFT)
#घोषणा BU2614_STDF_SHIFT	(BU2614_FMES_BITS + BU2614_FMES_SHIFT)
#घोषणा BU2614_SWIN_SHIFT	(BU2614_STDF_BITS + BU2614_STDF_SHIFT)
#घोषणा BU2614_SWAL_SHIFT	(BU2614_SWIN_BITS + BU2614_SWIN_SHIFT)
#घोषणा BU2614_VOID2_SHIFT	(BU2614_SWAL_BITS + BU2614_SWAL_SHIFT)
#घोषणा BU2614_FMUN_SHIFT	(BU2614_VOID2_BITS + BU2614_VOID2_SHIFT)
#घोषणा BU2614_TEST_SHIFT	(BU2614_FMUN_BITS + BU2614_FMUN_SHIFT)

#घोषणा MKMASK(field)	(((1UL<<BU2614_##field##_BITS) - 1) << \
			BU2614_##field##_SHIFT)
#घोषणा BU2614_PORT_MASK	MKMASK(PORT)
#घोषणा BU2614_FREQ_MASK	MKMASK(FREQ)
#घोषणा BU2614_VOID_MASK	MKMASK(VOID)
#घोषणा BU2614_FMES_MASK	MKMASK(FMES)
#घोषणा BU2614_STDF_MASK	MKMASK(STDF)
#घोषणा BU2614_SWIN_MASK	MKMASK(SWIN)
#घोषणा BU2614_SWAL_MASK	MKMASK(SWAL)
#घोषणा BU2614_VOID2_MASK	MKMASK(VOID2)
#घोषणा BU2614_FMUN_MASK	MKMASK(FMUN)
#घोषणा BU2614_TEST_MASK	MKMASK(TEST)

/*
 * Set data which will be sent to BU2614FS.
 */
#घोषणा gemtek_bu2614_set(dev, field, data) ((dev)->bu2614data = \
	((dev)->bu2614data & ~field##_MASK) | ((data) << field##_SHIFT))

/*
 * Transmit settings to BU2614FS over GemTek IC.
 */
अटल व्योम gemtek_bu2614_transmit(काष्ठा gemtek *gt)
अणु
	काष्ठा radio_isa_card *isa = &gt->isa;
	पूर्णांक i, bit, q, mute;

	mute = gt->muted ? GEMTEK_MT : 0x00;

	outb_p(mute | GEMTEK_CE | GEMTEK_DA | GEMTEK_CK, isa->io);
	udelay(LONG_DELAY);

	क्रम (i = 0, q = gt->bu2614data; i < 32; i++, q >>= 1) अणु
		bit = (q & 1) ? GEMTEK_DA : 0;
		outb_p(mute | GEMTEK_CE | bit, isa->io);
		udelay(SHORT_DELAY);
		outb_p(mute | GEMTEK_CE | bit | GEMTEK_CK, isa->io);
		udelay(SHORT_DELAY);
	पूर्ण

	outb_p(mute | GEMTEK_DA | GEMTEK_CK, isa->io);
	udelay(SHORT_DELAY);
पूर्ण

/*
 * Calculate भागisor from FM-frequency क्रम BU2614FS (3.125 KHz STDF expected).
 */
अटल अचिन्हित दीर्घ gemtek_convfreq(अचिन्हित दीर्घ freq)
अणु
	वापस ((freq << FSCALE) + IF_OFFSET + REF_FREQ / 2) / REF_FREQ;
पूर्ण

अटल काष्ठा radio_isa_card *gemtek_alloc(व्योम)
अणु
	काष्ठा gemtek *gt = kzalloc(माप(*gt), GFP_KERNEL);

	अगर (gt)
		gt->muted = true;
	वापस gt ? &gt->isa : शून्य;
पूर्ण

/*
 * Set FM-frequency.
 */
अटल पूर्णांक gemtek_s_frequency(काष्ठा radio_isa_card *isa, u32 freq)
अणु
	काष्ठा gemtek *gt = container_of(isa, काष्ठा gemtek, isa);

	अगर (hardmute && gt->muted)
		वापस 0;

	gemtek_bu2614_set(gt, BU2614_PORT, 0);
	gemtek_bu2614_set(gt, BU2614_FMES, 0);
	gemtek_bu2614_set(gt, BU2614_SWIN, 0);	/* FM-mode	*/
	gemtek_bu2614_set(gt, BU2614_SWAL, 0);
	gemtek_bu2614_set(gt, BU2614_FMUN, 1);	/* GT bit set	*/
	gemtek_bu2614_set(gt, BU2614_TEST, 0);
	gemtek_bu2614_set(gt, BU2614_STDF, GEMTEK_STDF_3_125_KHZ);
	gemtek_bu2614_set(gt, BU2614_FREQ, gemtek_convfreq(freq));
	gemtek_bu2614_transmit(gt);
	वापस 0;
पूर्ण

/*
 * Set mute flag.
 */
अटल पूर्णांक gemtek_s_mute_volume(काष्ठा radio_isa_card *isa, bool mute, पूर्णांक vol)
अणु
	काष्ठा gemtek *gt = container_of(isa, काष्ठा gemtek, isa);
	पूर्णांक i;

	gt->muted = mute;
	अगर (hardmute) अणु
		अगर (!mute)
			वापस gemtek_s_frequency(isa, isa->freq);

		/* Turn off PLL, disable data output */
		gemtek_bu2614_set(gt, BU2614_PORT, 0);
		gemtek_bu2614_set(gt, BU2614_FMES, 0);	/* CT bit off	*/
		gemtek_bu2614_set(gt, BU2614_SWIN, 0);	/* FM-mode	*/
		gemtek_bu2614_set(gt, BU2614_SWAL, 0);
		gemtek_bu2614_set(gt, BU2614_FMUN, 0);	/* GT bit off	*/
		gemtek_bu2614_set(gt, BU2614_TEST, 0);
		gemtek_bu2614_set(gt, BU2614_STDF, GEMTEK_PLL_OFF);
		gemtek_bu2614_set(gt, BU2614_FREQ, 0);
		gemtek_bu2614_transmit(gt);
		वापस 0;
	पूर्ण

	/* Read bus contents (CE, CK and DA). */
	i = inb_p(isa->io);
	/* Write it back with mute flag set. */
	outb_p((i >> 5) | (mute ? GEMTEK_MT : 0), isa->io);
	udelay(SHORT_DELAY);
	वापस 0;
पूर्ण

अटल u32 gemtek_g_rxsubchans(काष्ठा radio_isa_card *isa)
अणु
	अगर (inb_p(isa->io) & GEMTEK_NS)
		वापस V4L2_TUNER_SUB_MONO;
	वापस V4L2_TUNER_SUB_STEREO;
पूर्ण

/*
 * Check अगर requested card acts like GemTek Radio card.
 */
अटल bool gemtek_probe(काष्ठा radio_isa_card *isa, पूर्णांक io)
अणु
	पूर्णांक i, q;

	q = inb_p(io);	/* Read bus contents beक्रमe probing. */
	/* Try to turn on CE, CK and DA respectively and check अगर card responds
	   properly. */
	क्रम (i = 0; i < 3; ++i) अणु
		outb_p(1 << i, io);
		udelay(SHORT_DELAY);

		अगर ((inb_p(io) & ~GEMTEK_NS) != (0x17 | (1 << (i + 5))))
			वापस false;
	पूर्ण
	outb_p(q >> 5, io);	/* Write bus contents back. */
	udelay(SHORT_DELAY);
	वापस true;
पूर्ण

अटल स्थिर काष्ठा radio_isa_ops gemtek_ops = अणु
	.alloc = gemtek_alloc,
	.probe = gemtek_probe,
	.s_mute_volume = gemtek_s_mute_volume,
	.s_frequency = gemtek_s_frequency,
	.g_rxsubchans = gemtek_g_rxsubchans,
पूर्ण;

अटल स्थिर पूर्णांक gemtek_ioports[] = अणु 0x20c, 0x30c, 0x24c, 0x34c, 0x248, 0x28c पूर्ण;

#अगर_घोषित CONFIG_PNP
अटल स्थिर काष्ठा pnp_device_id gemtek_pnp_devices[] = अणु
	/* AOpen FX-3D/Pro Radio */
	अणु.id = "ADS7183", .driver_data = 0पूर्ण,
	अणु.id = ""पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp, gemtek_pnp_devices);
#पूर्ण_अगर

अटल काष्ठा radio_isa_driver gemtek_driver = अणु
	.driver = अणु
		.match		= radio_isa_match,
		.probe		= radio_isa_probe,
		.हटाओ		= radio_isa_हटाओ,
		.driver		= अणु
			.name	= "radio-gemtek",
		पूर्ण,
	पूर्ण,
#अगर_घोषित CONFIG_PNP
	.pnp_driver = अणु
		.name		= "radio-gemtek",
		.id_table	= gemtek_pnp_devices,
		.probe		= radio_isa_pnp_probe,
		.हटाओ		= radio_isa_pnp_हटाओ,
	पूर्ण,
#पूर्ण_अगर
	.io_params = io,
	.radio_nr_params = radio_nr,
	.io_ports = gemtek_ioports,
	.num_of_io_ports = ARRAY_SIZE(gemtek_ioports),
	.region_size = 1,
	.card = "GemTek Radio",
	.ops = &gemtek_ops,
	.has_stereo = true,
पूर्ण;

अटल पूर्णांक __init gemtek_init(व्योम)
अणु
	gemtek_driver.probe = probe;
#अगर_घोषित CONFIG_PNP
	pnp_रेजिस्टर_driver(&gemtek_driver.pnp_driver);
#पूर्ण_अगर
	वापस isa_रेजिस्टर_driver(&gemtek_driver.driver, GEMTEK_MAX);
पूर्ण

अटल व्योम __निकास gemtek_निकास(व्योम)
अणु
	hardmute = true;	/* Turn off PLL */
#अगर_घोषित CONFIG_PNP
	pnp_unरेजिस्टर_driver(&gemtek_driver.pnp_driver);
#पूर्ण_अगर
	isa_unरेजिस्टर_driver(&gemtek_driver.driver);
पूर्ण

module_init(gemtek_init);
module_निकास(gemtek_निकास);
