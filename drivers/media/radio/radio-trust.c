<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* radio-trust.c - Trust FM Radio card driver क्रम Linux 2.2
 * by Eric Lammerts <eric@scपूर्णांकilla.utwente.nl>
 *
 * Based on radio-aztech.c. Original notes:
 *
 * Adapted to support the Video क्रम Linux API by
 * Russell Kroll <rkroll@exploits.org>.  Based on original tuner code by:
 *
 * Quay Ly
 * Donald Song
 * Jason Lewis      (jlewis@twilight.vtc.vsc.edu)
 * Scott McGrath    (smcgrath@twilight.vtc.vsc.edu)
 * William McGrath  (wmcgrath@twilight.vtc.vsc.edu)
 *
 * Converted to V4L2 API by Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश "radio-isa.h"

MODULE_AUTHOR("Eric Lammerts, Russell Kroll, Quay Lu, Donald Song, Jason Lewis, Scott McGrath, William McGrath");
MODULE_DESCRIPTION("A driver for the Trust FM Radio card.");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1.99");

/* acceptable ports: 0x350 (JP3 लघुed), 0x358 (JP3 खोलो) */

#अगर_अघोषित CONFIG_RADIO_TRUST_PORT
#घोषणा CONFIG_RADIO_TRUST_PORT -1
#पूर्ण_अगर

#घोषणा TRUST_MAX 2

अटल पूर्णांक io[TRUST_MAX] = अणु [0] = CONFIG_RADIO_TRUST_PORT,
			      [1 ... (TRUST_MAX - 1)] = -1 पूर्ण;
अटल पूर्णांक radio_nr[TRUST_MAX] = अणु [0 ... (TRUST_MAX - 1)] = -1 पूर्ण;

module_param_array(io, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(io, "I/O addresses of the Trust FM Radio card (0x350 or 0x358)");
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");

काष्ठा trust अणु
	काष्ठा radio_isa_card isa;
	पूर्णांक ioval;
पूर्ण;

अटल काष्ठा radio_isa_card *trust_alloc(व्योम)
अणु
	काष्ठा trust *tr = kzalloc(माप(*tr), GFP_KERNEL);

	वापस tr ? &tr->isa : शून्य;
पूर्ण

/* i2c addresses */
#घोषणा TDA7318_ADDR 0x88
#घोषणा TSA6060T_ADDR 0xc4

#घोषणा TR_DELAY करो अणु inb(tr->isa.io); inb(tr->isa.io); inb(tr->isa.io); पूर्ण जबतक (0)
#घोषणा TR_SET_SCL outb(tr->ioval |= 2, tr->isa.io)
#घोषणा TR_CLR_SCL outb(tr->ioval &= 0xfd, tr->isa.io)
#घोषणा TR_SET_SDA outb(tr->ioval |= 1, tr->isa.io)
#घोषणा TR_CLR_SDA outb(tr->ioval &= 0xfe, tr->isa.io)

अटल व्योम ग_लिखो_i2c(काष्ठा trust *tr, पूर्णांक n, ...)
अणु
	अचिन्हित अक्षर val, mask;
	बहु_सूची args;

	बहु_शुरू(args, n);

	/* start condition */
	TR_SET_SDA;
	TR_SET_SCL;
	TR_DELAY;
	TR_CLR_SDA;
	TR_CLR_SCL;
	TR_DELAY;

	क्रम (; n; n--) अणु
		val = बहु_तर्क(args, अचिन्हित);
		क्रम (mask = 0x80; mask; mask >>= 1) अणु
			अगर (val & mask)
				TR_SET_SDA;
			अन्यथा
				TR_CLR_SDA;
			TR_SET_SCL;
			TR_DELAY;
			TR_CLR_SCL;
			TR_DELAY;
		पूर्ण
		/* acknowledge bit */
		TR_SET_SDA;
		TR_SET_SCL;
		TR_DELAY;
		TR_CLR_SCL;
		TR_DELAY;
	पूर्ण

	/* stop condition */
	TR_CLR_SDA;
	TR_DELAY;
	TR_SET_SCL;
	TR_DELAY;
	TR_SET_SDA;
	TR_DELAY;

	बहु_पूर्ण(args);
पूर्ण

अटल पूर्णांक trust_s_mute_volume(काष्ठा radio_isa_card *isa, bool mute, पूर्णांक vol)
अणु
	काष्ठा trust *tr = container_of(isa, काष्ठा trust, isa);

	tr->ioval = (tr->ioval & 0xf7) | (mute << 3);
	outb(tr->ioval, isa->io);
	ग_लिखो_i2c(tr, 2, TDA7318_ADDR, vol ^ 0x1f);
	वापस 0;
पूर्ण

अटल पूर्णांक trust_s_stereo(काष्ठा radio_isa_card *isa, bool stereo)
अणु
	काष्ठा trust *tr = container_of(isa, काष्ठा trust, isa);

	tr->ioval = (tr->ioval & 0xfb) | (!stereo << 2);
	outb(tr->ioval, isa->io);
	वापस 0;
पूर्ण

अटल u32 trust_g_संकेत(काष्ठा radio_isa_card *isa)
अणु
	पूर्णांक i, v;

	क्रम (i = 0, v = 0; i < 100; i++)
		v |= inb(isa->io);
	वापस (v & 1) ? 0 : 0xffff;
पूर्ण

अटल पूर्णांक trust_s_frequency(काष्ठा radio_isa_card *isa, u32 freq)
अणु
	काष्ठा trust *tr = container_of(isa, काष्ठा trust, isa);

	freq /= 160;	/* Convert to 10 kHz units	*/
	freq += 1070;	/* Add 10.7 MHz IF		*/
	ग_लिखो_i2c(tr, 5, TSA6060T_ADDR, (freq << 1) | 1,
			freq >> 7, 0x60 | ((freq >> 15) & 1), 0);
	वापस 0;
पूर्ण

अटल पूर्णांक basstreble2chip[15] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 14, 13, 12, 11, 10, 9, 8
पूर्ण;

अटल पूर्णांक trust_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा radio_isa_card *isa =
		container_of(ctrl->handler, काष्ठा radio_isa_card, hdl);
	काष्ठा trust *tr = container_of(isa, काष्ठा trust, isa);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_BASS:
		ग_लिखो_i2c(tr, 2, TDA7318_ADDR, 0x60 | basstreble2chip[ctrl->val]);
		वापस 0;
	हाल V4L2_CID_AUDIO_TREBLE:
		ग_लिखो_i2c(tr, 2, TDA7318_ADDR, 0x70 | basstreble2chip[ctrl->val]);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops trust_ctrl_ops = अणु
	.s_ctrl = trust_s_ctrl,
पूर्ण;

अटल पूर्णांक trust_initialize(काष्ठा radio_isa_card *isa)
अणु
	काष्ठा trust *tr = container_of(isa, काष्ठा trust, isa);

	tr->ioval = 0xf;
	ग_लिखो_i2c(tr, 2, TDA7318_ADDR, 0x80);	/* speaker att. LF = 0 dB */
	ग_लिखो_i2c(tr, 2, TDA7318_ADDR, 0xa0);	/* speaker att. RF = 0 dB */
	ग_लिखो_i2c(tr, 2, TDA7318_ADDR, 0xc0);	/* speaker att. LR = 0 dB */
	ग_लिखो_i2c(tr, 2, TDA7318_ADDR, 0xe0);	/* speaker att. RR = 0 dB */
	ग_लिखो_i2c(tr, 2, TDA7318_ADDR, 0x40);	/* stereo 1 input, gain = 18.75 dB */

	v4l2_ctrl_new_std(&isa->hdl, &trust_ctrl_ops,
				V4L2_CID_AUDIO_BASS, 0, 15, 1, 8);
	v4l2_ctrl_new_std(&isa->hdl, &trust_ctrl_ops,
				V4L2_CID_AUDIO_TREBLE, 0, 15, 1, 8);
	वापस isa->hdl.error;
पूर्ण

अटल स्थिर काष्ठा radio_isa_ops trust_ops = अणु
	.init = trust_initialize,
	.alloc = trust_alloc,
	.s_mute_volume = trust_s_mute_volume,
	.s_frequency = trust_s_frequency,
	.s_stereo = trust_s_stereo,
	.g_संकेत = trust_g_संकेत,
पूर्ण;

अटल स्थिर पूर्णांक trust_ioports[] = अणु 0x350, 0x358 पूर्ण;

अटल काष्ठा radio_isa_driver trust_driver = अणु
	.driver = अणु
		.match		= radio_isa_match,
		.probe		= radio_isa_probe,
		.हटाओ		= radio_isa_हटाओ,
		.driver		= अणु
			.name	= "radio-trust",
		पूर्ण,
	पूर्ण,
	.io_params = io,
	.radio_nr_params = radio_nr,
	.io_ports = trust_ioports,
	.num_of_io_ports = ARRAY_SIZE(trust_ioports),
	.region_size = 2,
	.card = "Trust FM Radio",
	.ops = &trust_ops,
	.has_stereo = true,
	.max_volume = 31,
पूर्ण;

अटल पूर्णांक __init trust_init(व्योम)
अणु
	वापस isa_रेजिस्टर_driver(&trust_driver.driver, TRUST_MAX);
पूर्ण

अटल व्योम __निकास trust_निकास(व्योम)
अणु
	isa_unरेजिस्टर_driver(&trust_driver.driver);
पूर्ण

module_init(trust_init);
module_निकास(trust_निकास);
