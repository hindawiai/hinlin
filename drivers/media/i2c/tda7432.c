<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * For the STS-Thompson TDA7432 audio processor chip
 *
 * Handles audio functions: volume, balance, tone, loudness
 * This driver will not complain अगर used with any
 * other i2c device with the same address.
 *
 * Muting and tone control by Jonathan Isom <jisom@ematic.com>
 *
 * Copyright (c) 2000 Eric Sandeen <eric_sandeen@bigfoot.com>
 * Copyright (c) 2006 Mauro Carvalho Chehab <mchehab@kernel.org>
 *
 * Based on tda9855.c by Steve VanDeBogart (vandebo@uclink.berkeley.edu)
 * Which was based on tda8425.c by Greg Alexander (c) 1998
 *
 * OPTIONS:
 * debug    - set to 1 अगर you'd like to see debug messages
 *            set to 2 अगर you'd like to be inundated with debug messages
 *
 * loudness - set between 0 and 15 क्रम varying degrees of loudness effect
 *
 * maxvol   - set maximum volume to +20db (1), शेष is 0db(0)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/i2c.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>

#अगर_अघोषित VIDEO_AUDIO_BALANCE
# define VIDEO_AUDIO_BALANCE 32
#पूर्ण_अगर

MODULE_AUTHOR("Eric Sandeen <eric_sandeen@bigfoot.com>");
MODULE_DESCRIPTION("bttv driver for the tda7432 audio processor chip");
MODULE_LICENSE("GPL");

अटल पूर्णांक maxvol;
अटल पूर्णांक loudness; /* disable loudness by शेष */
अटल पूर्णांक debug;	 /* insmod parameter */
module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Set debugging level from 0 to 3. Default is off(0).");
module_param(loudness, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(loudness, "Turn loudness on(1) else off(0). Default is off(0).");
module_param(maxvol, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(maxvol, "Set maximum volume to +20dB(0) else +0dB(1). Default is +20dB(0).");


/* Structure of address and subaddresses क्रम the tda7432 */

काष्ठा tda7432 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा अणु
		/* bass/treble cluster */
		काष्ठा v4l2_ctrl *bass;
		काष्ठा v4l2_ctrl *treble;
	पूर्ण;
	काष्ठा अणु
		/* mute/balance cluster */
		काष्ठा v4l2_ctrl *mute;
		काष्ठा v4l2_ctrl *balance;
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा tda7432 *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tda7432, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा tda7432, hdl)->sd;
पूर्ण

/* The TDA7432 is made by STS-Thompson
 * http://www.st.com
 * http://us.st.com/stonline/books/pdf/करोcs/4056.pdf
 *
 * TDA7432: I2C-bus controlled basic audio processor
 *
 * The TDA7432 controls basic audio functions like volume, balance,
 * and tone control (including loudness).  It also has four channel
 * output (क्रम front and rear).  Since most vidcap cards probably
 * करोn't have 4 channel output, this driver will set front & rear
 * together (no independent control).
 */

		/* Subaddresses क्रम TDA7432 */

#घोषणा TDA7432_IN	0x00 /* Input select                 */
#घोषणा TDA7432_VL	0x01 /* Volume                       */
#घोषणा TDA7432_TN	0x02 /* Bass, Treble (Tone)          */
#घोषणा TDA7432_LF	0x03 /* Attenuation LF (Left Front)  */
#घोषणा TDA7432_LR	0x04 /* Attenuation LR (Left Rear)   */
#घोषणा TDA7432_RF	0x05 /* Attenuation RF (Right Front) */
#घोषणा TDA7432_RR	0x06 /* Attenuation RR (Right Rear)  */
#घोषणा TDA7432_LD	0x07 /* Loudness                     */


		/* Masks क्रम bits in TDA7432 subaddresses */

/* Many of these not used - just क्रम करोcumentation */

/* Subaddress 0x00 - Input selection and bass control */

/* Bits 0,1,2 control input:
 * 0x00 - Stereo input
 * 0x02 - Mono input
 * 0x03 - Mute  (Using Attenuators Plays better with modules)
 * Mono probably isn't used - I'm guessing only the stereo
 * input is connected on most cards, so we'll set it to stereo.
 *
 * Bit 3 controls bass cut: 0/1 is non-symmetric/symmetric bass cut
 * Bit 4 controls bass range: 0/1 is extended/standard bass range
 *
 * Highest 3 bits not used
 */

#घोषणा TDA7432_STEREO_IN	0
#घोषणा TDA7432_MONO_IN		2	/* Probably won't be used */
#घोषणा TDA7432_BASS_SYM	1 << 3
#घोषणा TDA7432_BASS_NORM	1 << 4

/* Subaddress 0x01 - Volume */

/* Lower 7 bits control volume from -79dB to +32dB in 1dB steps
 * Recommended maximum is +20 dB
 *
 * +32dB: 0x00
 * +20dB: 0x0c
 *   0dB: 0x20
 * -79dB: 0x6f
 *
 * MSB (bit 7) controls loudness: 1/0 is loudness on/off
 */

#घोषणा	TDA7432_VOL_0DB		0x20
#घोषणा TDA7432_LD_ON		1 << 7


/* Subaddress 0x02 - Tone control */

/* Bits 0,1,2 control असलolute treble gain from 0dB to 14dB
 * 0x0 is 14dB, 0x7 is 0dB
 *
 * Bit 3 controls treble attenuation/gain (sign)
 * 1 = gain (+)
 * 0 = attenuation (-)
 *
 * Bits 4,5,6 control असलolute bass gain from 0dB to 14dB
 * (This is only true क्रम normal base range, set in 0x00)
 * 0x0 << 4 is 14dB, 0x7 is 0dB
 *
 * Bit 7 controls bass attenuation/gain (sign)
 * 1 << 7 = gain (+)
 * 0 << 7 = attenuation (-)
 *
 * Example:
 * 1 1 0 1 0 1 0 1 is +4dB bass, -4dB treble
 */

#घोषणा TDA7432_TREBLE_0DB		0xf
#घोषणा TDA7432_TREBLE			7
#घोषणा TDA7432_TREBLE_GAIN		1 << 3
#घोषणा TDA7432_BASS_0DB		0xf
#घोषणा TDA7432_BASS			7 << 4
#घोषणा TDA7432_BASS_GAIN		1 << 7


/* Subaddress 0x03 - Left  Front attenuation */
/* Subaddress 0x04 - Left  Rear  attenuation */
/* Subaddress 0x05 - Right Front attenuation */
/* Subaddress 0x06 - Right Rear  attenuation */

/* Bits 0,1,2,3,4 control attenuation from 0dB to -37.5dB
 * in 1.5dB steps.
 *
 * 0x00 is     0dB
 * 0x1f is -37.5dB
 *
 * Bit 5 mutes that channel when set (1 = mute, 0 = unmute)
 * We'll use the mute on the input, though (above)
 * Bits 6,7 unused
 */

#घोषणा TDA7432_ATTEN_0DB	0x00
#घोषणा TDA7432_MUTE        0x1 << 5


/* Subaddress 0x07 - Loudness Control */

/* Bits 0,1,2,3 control loudness from 0dB to -15dB in 1dB steps
 * when bit 4 is NOT set
 *
 * 0x0 is   0dB
 * 0xf is -15dB
 *
 * If bit 4 is set, then there is a flat attenuation according to
 * the lower 4 bits, as above.
 *
 * Bits 5,6,7 unused
 */



/* Begin code */

अटल पूर्णांक tda7432_ग_लिखो(काष्ठा v4l2_subdev *sd, पूर्णांक subaddr, पूर्णांक val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	अचिन्हित अक्षर buffer[2];

	v4l2_dbg(2, debug, sd, "In tda7432_write\n");
	v4l2_dbg(1, debug, sd, "Writing %d 0x%x\n", subaddr, val);
	buffer[0] = subaddr;
	buffer[1] = val;
	अगर (2 != i2c_master_send(client, buffer, 2)) अणु
		v4l2_err(sd, "I/O error, trying (write %d 0x%x)\n",
		       subaddr, val);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tda7432_set(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	अचिन्हित अक्षर buf[16];

	buf[0]  = TDA7432_IN;
	buf[1]  = TDA7432_STEREO_IN |  /* Main (stereo) input   */
		  TDA7432_BASS_SYM  |  /* Symmetric bass cut    */
		  TDA7432_BASS_NORM;   /* Normal bass range     */
	buf[2]  = 0x3b;
	अगर (loudness)			 /* Turn loudness on?     */
		buf[2] |= TDA7432_LD_ON;
	buf[3]  = TDA7432_TREBLE_0DB | (TDA7432_BASS_0DB << 4);
	buf[4]  = TDA7432_ATTEN_0DB;
	buf[5]  = TDA7432_ATTEN_0DB;
	buf[6]  = TDA7432_ATTEN_0DB;
	buf[7]  = TDA7432_ATTEN_0DB;
	buf[8]  = loudness;
	अगर (9 != i2c_master_send(client, buf, 9)) अणु
		v4l2_err(sd, "I/O error, trying tda7432_set\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda7432_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tda7432 *state = to_state(sd);

	v4l2_ctrl_handler_log_status(&state->hdl, sd->name);
	वापस 0;
पूर्ण

अटल पूर्णांक tda7432_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा tda7432 *t = to_state(sd);
	u8 bass, treble, volume;
	u8 lf, lr, rf, rr;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		अगर (t->balance->val < 0) अणु
			/* shअगरted to left, attenuate right */
			rr = rf = -t->balance->val;
			lr = lf = TDA7432_ATTEN_0DB;
		पूर्ण अन्यथा अगर (t->balance->val > 0) अणु
			/* shअगरted to right, attenuate left */
			rr = rf = TDA7432_ATTEN_0DB;
			lr = lf = t->balance->val;
		पूर्ण अन्यथा अणु
			/* centered */
			rr = rf = TDA7432_ATTEN_0DB;
			lr = lf = TDA7432_ATTEN_0DB;
		पूर्ण
		अगर (t->mute->val) अणु
			lf |= TDA7432_MUTE;
			lr |= TDA7432_MUTE;
			rf |= TDA7432_MUTE;
			rr |= TDA7432_MUTE;
		पूर्ण
		/* Mute & update balance*/
		tda7432_ग_लिखो(sd, TDA7432_LF, lf);
		tda7432_ग_लिखो(sd, TDA7432_LR, lr);
		tda7432_ग_लिखो(sd, TDA7432_RF, rf);
		tda7432_ग_लिखो(sd, TDA7432_RR, rr);
		वापस 0;
	हाल V4L2_CID_AUDIO_VOLUME:
		volume = 0x6f - ctrl->val;
		अगर (loudness)		/* Turn on the loudness bit */
			volume |= TDA7432_LD_ON;

		tda7432_ग_लिखो(sd, TDA7432_VL, volume);
		वापस 0;
	हाल V4L2_CID_AUDIO_BASS:
		bass = t->bass->val;
		treble = t->treble->val;
		अगर (bass >= 0x8)
			bass = 14 - (bass - 8);
		अगर (treble >= 0x8)
			treble = 14 - (treble - 8);

		tda7432_ग_लिखो(sd, TDA7432_TN, 0x10 | (bass << 4) | treble);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops tda7432_ctrl_ops = अणु
	.s_ctrl = tda7432_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops tda7432_core_ops = अणु
	.log_status = tda7432_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tda7432_ops = अणु
	.core = &tda7432_core_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

/* *********************** *
 * i2c पूर्णांकerface functions *
 * *********************** */

अटल पूर्णांक tda7432_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tda7432 *t;
	काष्ठा v4l2_subdev *sd;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	t = devm_kzalloc(&client->dev, माप(*t), GFP_KERNEL);
	अगर (!t)
		वापस -ENOMEM;
	sd = &t->sd;
	v4l2_i2c_subdev_init(sd, client, &tda7432_ops);
	v4l2_ctrl_handler_init(&t->hdl, 5);
	v4l2_ctrl_new_std(&t->hdl, &tda7432_ctrl_ops,
		V4L2_CID_AUDIO_VOLUME, 0, maxvol ? 0x68 : 0x4f, 1, maxvol ? 0x5d : 0x47);
	t->mute = v4l2_ctrl_new_std(&t->hdl, &tda7432_ctrl_ops,
		V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	t->balance = v4l2_ctrl_new_std(&t->hdl, &tda7432_ctrl_ops,
		V4L2_CID_AUDIO_BALANCE, -31, 31, 1, 0);
	t->bass = v4l2_ctrl_new_std(&t->hdl, &tda7432_ctrl_ops,
		V4L2_CID_AUDIO_BASS, 0, 14, 1, 7);
	t->treble = v4l2_ctrl_new_std(&t->hdl, &tda7432_ctrl_ops,
		V4L2_CID_AUDIO_TREBLE, 0, 14, 1, 7);
	sd->ctrl_handler = &t->hdl;
	अगर (t->hdl.error) अणु
		पूर्णांक err = t->hdl.error;

		v4l2_ctrl_handler_मुक्त(&t->hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_cluster(2, &t->bass);
	v4l2_ctrl_cluster(2, &t->mute);
	v4l2_ctrl_handler_setup(&t->hdl);
	अगर (loudness < 0 || loudness > 15) अणु
		v4l2_warn(sd, "loudness parameter must be between 0 and 15\n");
		अगर (loudness < 0)
			loudness = 0;
		अगर (loudness > 15)
			loudness = 15;
	पूर्ण

	tda7432_set(sd);
	वापस 0;
पूर्ण

अटल पूर्णांक tda7432_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा tda7432 *t = to_state(sd);

	tda7432_set(sd);
	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&t->hdl);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tda7432_id[] = अणु
	अणु "tda7432", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tda7432_id);

अटल काष्ठा i2c_driver tda7432_driver = अणु
	.driver = अणु
		.name	= "tda7432",
	पूर्ण,
	.probe		= tda7432_probe,
	.हटाओ		= tda7432_हटाओ,
	.id_table	= tda7432_id,
पूर्ण;

module_i2c_driver(tda7432_driver);
