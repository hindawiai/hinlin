<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * saa717x - Philips SAA717xHL video decoder driver
 *
 * Based on the saa7115 driver
 *
 * Changes by Ohta Kyuma <alpha292@bremen.or.jp>
 *    - Apply to SAA717x,NEC uPD64031,uPD64083. (1/31/2004)
 *
 * Changes by T.Adachi (tadachi@tadachi-net.com)
 *    - support audio, video scaler etc, and checked the initialize sequence.
 *
 * Cleaned up by Hans Verkuil <hverkuil@xs4all.nl>
 *
 * Note: this is a reversed engineered driver based on captures from
 * the I2C bus under Winकरोws. This chip is very similar to the saa7134,
 * though. Unक्रमtunately, this driver is currently only working क्रम NTSC.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>

#समावेश <linux/videodev2.h>
#समावेश <linux/i2c.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

MODULE_DESCRIPTION("Philips SAA717x audio/video decoder driver");
MODULE_AUTHOR("K. Ohta, T. Adachi, Hans Verkuil");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-1)");

/*
 * Generic i2c probe
 * concerning the addresses: i2c wants 7 bit (without the r/w bit), so '>>1'
 */

काष्ठा saa717x_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	v4l2_std_id std;
	पूर्णांक input;
	पूर्णांक enable;
	पूर्णांक radio;
	पूर्णांक playback;
	पूर्णांक audio;
	पूर्णांक tuner_audio_mode;
	पूर्णांक audio_मुख्य_mute;
	पूर्णांक audio_मुख्य_vol_r;
	पूर्णांक audio_मुख्य_vol_l;
	u16 audio_मुख्य_bass;
	u16 audio_मुख्य_treble;
	u16 audio_मुख्य_volume;
	u16 audio_मुख्य_balance;
	पूर्णांक audio_input;
पूर्ण;

अटल अंतरभूत काष्ठा saa717x_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा saa717x_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा saa717x_state, hdl)->sd;
पूर्ण

/* ----------------------------------------------------------------------- */

/* क्रम audio mode */
#घोषणा TUNER_AUDIO_MONO	0  /* LL */
#घोषणा TUNER_AUDIO_STEREO	1  /* LR */
#घोषणा TUNER_AUDIO_LANG1	2  /* LL */
#घोषणा TUNER_AUDIO_LANG2	3  /* RR */

#घोषणा SAA717X_NTSC_WIDTH	(704)
#घोषणा SAA717X_NTSC_HEIGHT	(480)

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa717x_ग_लिखो(काष्ठा v4l2_subdev *sd, u32 reg, u32 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा i2c_adapter *adap = client->adapter;
	पूर्णांक fw_addr = reg == 0x454 || (reg >= 0x464 && reg <= 0x478) || reg == 0x480 || reg == 0x488;
	अचिन्हित अक्षर mm1[6];
	काष्ठा i2c_msg msg;

	msg.flags = 0;
	msg.addr = client->addr;
	mm1[0] = (reg >> 8) & 0xff;
	mm1[1] = reg & 0xff;

	अगर (fw_addr) अणु
		mm1[4] = (value >> 16) & 0xff;
		mm1[3] = (value >> 8) & 0xff;
		mm1[2] = value & 0xff;
	पूर्ण अन्यथा अणु
		mm1[2] = value & 0xff;
	पूर्ण
	msg.len = fw_addr ? 5 : 3; /* Long Registers have *only* three bytes! */
	msg.buf = mm1;
	v4l2_dbg(2, debug, sd, "wrote:  reg 0x%03x=%08x\n", reg, value);
	वापस i2c_transfer(adap, &msg, 1) == 1;
पूर्ण

अटल व्योम saa717x_ग_लिखो_regs(काष्ठा v4l2_subdev *sd, u32 *data)
अणु
	जबतक (data[0] || data[1]) अणु
		saa717x_ग_लिखो(sd, data[0], data[1]);
		data += 2;
	पूर्ण
पूर्ण

अटल u32 saa717x_पढ़ो(काष्ठा v4l2_subdev *sd, u32 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा i2c_adapter *adap = client->adapter;
	पूर्णांक fw_addr = (reg >= 0x404 && reg <= 0x4b8) || reg == 0x528;
	अचिन्हित अक्षर mm1[2];
	अचिन्हित अक्षर mm2[4] = अणु 0, 0, 0, 0 पूर्ण;
	काष्ठा i2c_msg msgs[2];
	u32 value;

	msgs[0].flags = 0;
	msgs[1].flags = I2C_M_RD;
	msgs[0].addr = msgs[1].addr = client->addr;
	mm1[0] = (reg >> 8) & 0xff;
	mm1[1] = reg & 0xff;
	msgs[0].len = 2;
	msgs[0].buf = mm1;
	msgs[1].len = fw_addr ? 3 : 1; /* Multibyte Registers contains *only* 3 bytes */
	msgs[1].buf = mm2;
	i2c_transfer(adap, msgs, 2);

	अगर (fw_addr)
		value = (mm2[2] << 16)  | (mm2[1] << 8) | mm2[0];
	अन्यथा
		value = mm2[0];

	v4l2_dbg(2, debug, sd, "read:  reg 0x%03x=0x%08x\n", reg, value);
	वापस value;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल u32 reg_init_initialize[] =
अणु
	/* from linux driver */
	0x101, 0x008, /* Increment delay */

	0x103, 0x000, /* Analog input control 2 */
	0x104, 0x090, /* Analog input control 3 */
	0x105, 0x090, /* Analog input control 4 */
	0x106, 0x0eb, /* Horizontal sync start */
	0x107, 0x0e0, /* Horizontal sync stop */
	0x109, 0x055, /* Luminance control */

	0x10f, 0x02a, /* Chroma gain control */
	0x110, 0x000, /* Chroma control 2 */

	0x114, 0x045, /* analog/ADC */

	0x118, 0x040, /* RAW data gain */
	0x119, 0x080, /* RAW data offset */

	0x044, 0x000, /* VBI horizontal input winकरोw start (L) TASK A */
	0x045, 0x000, /* VBI horizontal input winकरोw start (H) TASK A */
	0x046, 0x0cf, /* VBI horizontal input winकरोw stop (L) TASK A */
	0x047, 0x002, /* VBI horizontal input winकरोw stop (H) TASK A */

	0x049, 0x000, /* VBI vertical input winकरोw start (H) TASK A */

	0x04c, 0x0d0, /* VBI horizontal output length (L) TASK A */
	0x04d, 0x002, /* VBI horizontal output length (H) TASK A */

	0x064, 0x080, /* Lumina brightness TASK A */
	0x065, 0x040, /* Luminance contrast TASK A */
	0x066, 0x040, /* Chroma saturation TASK A */
	/* 067H: Reserved */
	0x068, 0x000, /* VBI horizontal scaling increment (L) TASK A */
	0x069, 0x004, /* VBI horizontal scaling increment (H) TASK A */
	0x06a, 0x000, /* VBI phase offset TASK A */

	0x06e, 0x000, /* Horizontal phase offset Luma TASK A */
	0x06f, 0x000, /* Horizontal phase offset Chroma TASK A */

	0x072, 0x000, /* Vertical filter mode TASK A */

	0x084, 0x000, /* VBI horizontal input winकरोw start (L) TAKS B */
	0x085, 0x000, /* VBI horizontal input winकरोw start (H) TAKS B */
	0x086, 0x0cf, /* VBI horizontal input winकरोw stop (L) TAKS B */
	0x087, 0x002, /* VBI horizontal input winकरोw stop (H) TAKS B */

	0x089, 0x000, /* VBI vertical input winकरोw start (H) TAKS B */

	0x08c, 0x0d0, /* VBI horizontal output length (L) TASK B */
	0x08d, 0x002, /* VBI horizontal output length (H) TASK B */

	0x0a4, 0x080, /* Lumina brightness TASK B */
	0x0a5, 0x040, /* Luminance contrast TASK B */
	0x0a6, 0x040, /* Chroma saturation TASK B */
	/* 0A7H reserved */
	0x0a8, 0x000, /* VBI horizontal scaling increment (L) TASK B */
	0x0a9, 0x004, /* VBI horizontal scaling increment (H) TASK B */
	0x0aa, 0x000, /* VBI phase offset TASK B */

	0x0ae, 0x000, /* Horizontal phase offset Luma TASK B */
	0x0af, 0x000, /*Horizontal phase offset Chroma TASK B */

	0x0b2, 0x000, /* Vertical filter mode TASK B */

	0x00c, 0x000, /* Start poपूर्णांक GREEN path */
	0x00d, 0x000, /* Start poपूर्णांक BLUE path */
	0x00e, 0x000, /* Start poपूर्णांक RED path */

	0x010, 0x010, /* GREEN path gamma curve --- */
	0x011, 0x020,
	0x012, 0x030,
	0x013, 0x040,
	0x014, 0x050,
	0x015, 0x060,
	0x016, 0x070,
	0x017, 0x080,
	0x018, 0x090,
	0x019, 0x0a0,
	0x01a, 0x0b0,
	0x01b, 0x0c0,
	0x01c, 0x0d0,
	0x01d, 0x0e0,
	0x01e, 0x0f0,
	0x01f, 0x0ff, /* --- GREEN path gamma curve */

	0x020, 0x010, /* BLUE path gamma curve --- */
	0x021, 0x020,
	0x022, 0x030,
	0x023, 0x040,
	0x024, 0x050,
	0x025, 0x060,
	0x026, 0x070,
	0x027, 0x080,
	0x028, 0x090,
	0x029, 0x0a0,
	0x02a, 0x0b0,
	0x02b, 0x0c0,
	0x02c, 0x0d0,
	0x02d, 0x0e0,
	0x02e, 0x0f0,
	0x02f, 0x0ff, /* --- BLUE path gamma curve */

	0x030, 0x010, /* RED path gamma curve --- */
	0x031, 0x020,
	0x032, 0x030,
	0x033, 0x040,
	0x034, 0x050,
	0x035, 0x060,
	0x036, 0x070,
	0x037, 0x080,
	0x038, 0x090,
	0x039, 0x0a0,
	0x03a, 0x0b0,
	0x03b, 0x0c0,
	0x03c, 0x0d0,
	0x03d, 0x0e0,
	0x03e, 0x0f0,
	0x03f, 0x0ff, /* --- RED path gamma curve */

	0x109, 0x085, /* Luminance control  */

	/**** from app start ****/
	0x584, 0x000, /* AGC gain control */
	0x585, 0x000, /* Program count */
	0x586, 0x003, /* Status reset */
	0x588, 0x0ff, /* Number of audio samples (L) */
	0x589, 0x00f, /* Number of audio samples (M) */
	0x58a, 0x000, /* Number of audio samples (H) */
	0x58b, 0x000, /* Audio select */
	0x58c, 0x010, /* Audio channel assign1 */
	0x58d, 0x032, /* Audio channel assign2 */
	0x58e, 0x054, /* Audio channel assign3 */
	0x58f, 0x023, /* Audio क्रमmat */
	0x590, 0x000, /* SIF control */

	0x595, 0x000, /* ?? */
	0x596, 0x000, /* ?? */
	0x597, 0x000, /* ?? */

	0x464, 0x00, /* Digital input crossbar1 */

	0x46c, 0xbbbb10, /* Digital output selection1-3 */
	0x470, 0x101010, /* Digital output selection4-6 */

	0x478, 0x00, /* Sound feature control */

	0x474, 0x18, /* Sofपंचांगute control */

	0x454, 0x0425b9, /* Sound Easy programming(reset) */
	0x454, 0x042539, /* Sound Easy programming(reset) */


	/**** common setting( of DVD play, including scaler commands) ****/
	0x042, 0x003, /* Data path configuration क्रम VBI (TASK A) */

	0x082, 0x003, /* Data path configuration क्रम VBI (TASK B) */

	0x108, 0x0f8, /* Sync control */
	0x2a9, 0x0fd, /* ??? */
	0x102, 0x089, /* select video input "mode 9" */
	0x111, 0x000, /* Mode/delay control */

	0x10e, 0x00a, /* Chroma control 1 */

	0x594, 0x002, /* SIF, analog I/O select */

	0x454, 0x0425b9, /* Sound  */
	0x454, 0x042539,

	0x111, 0x000,
	0x10e, 0x00a,
	0x464, 0x000,
	0x300, 0x000,
	0x301, 0x006,
	0x302, 0x000,
	0x303, 0x006,
	0x308, 0x040,
	0x309, 0x000,
	0x30a, 0x000,
	0x30b, 0x000,
	0x000, 0x002,
	0x001, 0x000,
	0x002, 0x000,
	0x003, 0x000,
	0x004, 0x033,
	0x040, 0x01d,
	0x041, 0x001,
	0x042, 0x004,
	0x043, 0x000,
	0x080, 0x01e,
	0x081, 0x001,
	0x082, 0x004,
	0x083, 0x000,
	0x190, 0x018,
	0x115, 0x000,
	0x116, 0x012,
	0x117, 0x018,
	0x04a, 0x011,
	0x08a, 0x011,
	0x04b, 0x000,
	0x08b, 0x000,
	0x048, 0x000,
	0x088, 0x000,
	0x04e, 0x012,
	0x08e, 0x012,
	0x058, 0x012,
	0x098, 0x012,
	0x059, 0x000,
	0x099, 0x000,
	0x05a, 0x003,
	0x09a, 0x003,
	0x05b, 0x001,
	0x09b, 0x001,
	0x054, 0x008,
	0x094, 0x008,
	0x055, 0x000,
	0x095, 0x000,
	0x056, 0x0c7,
	0x096, 0x0c7,
	0x057, 0x002,
	0x097, 0x002,
	0x0ff, 0x0ff,
	0x060, 0x001,
	0x0a0, 0x001,
	0x061, 0x000,
	0x0a1, 0x000,
	0x062, 0x000,
	0x0a2, 0x000,
	0x063, 0x000,
	0x0a3, 0x000,
	0x070, 0x000,
	0x0b0, 0x000,
	0x071, 0x004,
	0x0b1, 0x004,
	0x06c, 0x0e9,
	0x0ac, 0x0e9,
	0x06d, 0x003,
	0x0ad, 0x003,
	0x05c, 0x0d0,
	0x09c, 0x0d0,
	0x05d, 0x002,
	0x09d, 0x002,
	0x05e, 0x0f2,
	0x09e, 0x0f2,
	0x05f, 0x000,
	0x09f, 0x000,
	0x074, 0x000,
	0x0b4, 0x000,
	0x075, 0x000,
	0x0b5, 0x000,
	0x076, 0x000,
	0x0b6, 0x000,
	0x077, 0x000,
	0x0b7, 0x000,
	0x195, 0x008,
	0x0ff, 0x0ff,
	0x108, 0x0f8,
	0x111, 0x000,
	0x10e, 0x00a,
	0x2a9, 0x0fd,
	0x464, 0x001,
	0x454, 0x042135,
	0x598, 0x0e7,
	0x599, 0x07d,
	0x59a, 0x018,
	0x59c, 0x066,
	0x59d, 0x090,
	0x59e, 0x001,
	0x584, 0x000,
	0x585, 0x000,
	0x586, 0x003,
	0x588, 0x0ff,
	0x589, 0x00f,
	0x58a, 0x000,
	0x58b, 0x000,
	0x58c, 0x010,
	0x58d, 0x032,
	0x58e, 0x054,
	0x58f, 0x023,
	0x590, 0x000,
	0x595, 0x000,
	0x596, 0x000,
	0x597, 0x000,
	0x464, 0x000,
	0x46c, 0xbbbb10,
	0x470, 0x101010,


	0x478, 0x000,
	0x474, 0x018,
	0x454, 0x042135,
	0x598, 0x0e7,
	0x599, 0x07d,
	0x59a, 0x018,
	0x59c, 0x066,
	0x59d, 0x090,
	0x59e, 0x001,
	0x584, 0x000,
	0x585, 0x000,
	0x586, 0x003,
	0x588, 0x0ff,
	0x589, 0x00f,
	0x58a, 0x000,
	0x58b, 0x000,
	0x58c, 0x010,
	0x58d, 0x032,
	0x58e, 0x054,
	0x58f, 0x023,
	0x590, 0x000,
	0x595, 0x000,
	0x596, 0x000,
	0x597, 0x000,
	0x464, 0x000,
	0x46c, 0xbbbb10,
	0x470, 0x101010,

	0x478, 0x000,
	0x474, 0x018,
	0x454, 0x042135,
	0x598, 0x0e7,
	0x599, 0x07d,
	0x59a, 0x018,
	0x59c, 0x066,
	0x59d, 0x090,
	0x59e, 0x001,
	0x584, 0x000,
	0x585, 0x000,
	0x586, 0x003,
	0x588, 0x0ff,
	0x589, 0x00f,
	0x58a, 0x000,
	0x58b, 0x000,
	0x58c, 0x010,
	0x58d, 0x032,
	0x58e, 0x054,
	0x58f, 0x023,
	0x590, 0x000,
	0x595, 0x000,
	0x596, 0x000,
	0x597, 0x000,
	0x464, 0x000,
	0x46c, 0xbbbb10,
	0x470, 0x101010,
	0x478, 0x000,
	0x474, 0x018,
	0x454, 0x042135,
	0x193, 0x000,
	0x300, 0x000,
	0x301, 0x006,
	0x302, 0x000,
	0x303, 0x006,
	0x308, 0x040,
	0x309, 0x000,
	0x30a, 0x000,
	0x30b, 0x000,
	0x000, 0x002,
	0x001, 0x000,
	0x002, 0x000,
	0x003, 0x000,
	0x004, 0x033,
	0x040, 0x01d,
	0x041, 0x001,
	0x042, 0x004,
	0x043, 0x000,
	0x080, 0x01e,
	0x081, 0x001,
	0x082, 0x004,
	0x083, 0x000,
	0x190, 0x018,
	0x115, 0x000,
	0x116, 0x012,
	0x117, 0x018,
	0x04a, 0x011,
	0x08a, 0x011,
	0x04b, 0x000,
	0x08b, 0x000,
	0x048, 0x000,
	0x088, 0x000,
	0x04e, 0x012,
	0x08e, 0x012,
	0x058, 0x012,
	0x098, 0x012,
	0x059, 0x000,
	0x099, 0x000,
	0x05a, 0x003,
	0x09a, 0x003,
	0x05b, 0x001,
	0x09b, 0x001,
	0x054, 0x008,
	0x094, 0x008,
	0x055, 0x000,
	0x095, 0x000,
	0x056, 0x0c7,
	0x096, 0x0c7,
	0x057, 0x002,
	0x097, 0x002,
	0x060, 0x001,
	0x0a0, 0x001,
	0x061, 0x000,
	0x0a1, 0x000,
	0x062, 0x000,
	0x0a2, 0x000,
	0x063, 0x000,
	0x0a3, 0x000,
	0x070, 0x000,
	0x0b0, 0x000,
	0x071, 0x004,
	0x0b1, 0x004,
	0x06c, 0x0e9,
	0x0ac, 0x0e9,
	0x06d, 0x003,
	0x0ad, 0x003,
	0x05c, 0x0d0,
	0x09c, 0x0d0,
	0x05d, 0x002,
	0x09d, 0x002,
	0x05e, 0x0f2,
	0x09e, 0x0f2,
	0x05f, 0x000,
	0x09f, 0x000,
	0x074, 0x000,
	0x0b4, 0x000,
	0x075, 0x000,
	0x0b5, 0x000,
	0x076, 0x000,
	0x0b6, 0x000,
	0x077, 0x000,
	0x0b7, 0x000,
	0x195, 0x008,
	0x598, 0x0e7,
	0x599, 0x07d,
	0x59a, 0x018,
	0x59c, 0x066,
	0x59d, 0x090,
	0x59e, 0x001,
	0x584, 0x000,
	0x585, 0x000,
	0x586, 0x003,
	0x588, 0x0ff,
	0x589, 0x00f,
	0x58a, 0x000,
	0x58b, 0x000,
	0x58c, 0x010,
	0x58d, 0x032,
	0x58e, 0x054,
	0x58f, 0x023,
	0x590, 0x000,
	0x595, 0x000,
	0x596, 0x000,
	0x597, 0x000,
	0x464, 0x000,
	0x46c, 0xbbbb10,
	0x470, 0x101010,
	0x478, 0x000,
	0x474, 0x018,
	0x454, 0x042135,
	0x193, 0x0a6,
	0x108, 0x0f8,
	0x042, 0x003,
	0x082, 0x003,
	0x454, 0x0425b9,
	0x454, 0x042539,
	0x193, 0x000,
	0x193, 0x0a6,
	0x464, 0x000,

	0, 0
पूर्ण;

/* Tuner */
अटल u32 reg_init_tuner_input[] = अणु
	0x108, 0x0f8, /* Sync control */
	0x111, 0x000, /* Mode/delay control */
	0x10e, 0x00a, /* Chroma control 1 */
	0, 0
पूर्ण;

/* Composite */
अटल u32 reg_init_composite_input[] = अणु
	0x108, 0x0e8, /* Sync control */
	0x111, 0x000, /* Mode/delay control */
	0x10e, 0x04a, /* Chroma control 1 */
	0, 0
पूर्ण;

/* S-Video */
अटल u32 reg_init_svideo_input[] = अणु
	0x108, 0x0e8, /* Sync control */
	0x111, 0x000, /* Mode/delay control */
	0x10e, 0x04a, /* Chroma control 1 */
	0, 0
पूर्ण;

अटल u32 reg_set_audio_ढाँचा[4][2] =
अणु
	अणु /* क्रम MONO
		tadachi 6/29 DMA audio output select?
		Register 0x46c
		7-4: DMA2, 3-0: DMA1 ch. DMA4, DMA3 DMA2, DMA1
		0: MAIN left,  1: MAIN right
		2: AUX1 left,  3: AUX1 right
		4: AUX2 left,  5: AUX2 right
		6: DPL left,   7: DPL  right
		8: DPL center, 9: DPL surround
		A: monitor output, B: digital sense */
		0xbbbb00,

		/* tadachi 6/29 DAC and I2S output select?
		   Register 0x470
		   7-4:DAC right ch. 3-0:DAC left ch.
		   I2S1 right,left  I2S2 right,left */
		0x00,
	पूर्ण,
	अणु /* क्रम STEREO */
		0xbbbb10, 0x101010,
	पूर्ण,
	अणु /* क्रम LANG1 */
		0xbbbb00, 0x00,
	पूर्ण,
	अणु /* क्रम LANG2/SAP */
		0xbbbb11, 0x111111,
	पूर्ण
पूर्ण;


/* Get detected audio flags (from saa7134 driver) */
अटल व्योम get_inf_dev_status(काष्ठा v4l2_subdev *sd,
		पूर्णांक *dual_flag, पूर्णांक *stereo_flag)
अणु
	u32 reg_data3;

	अटल अक्षर *stdres[0x20] = अणु
		[0x00] = "no standard detected",
		[0x01] = "B/G (in progress)",
		[0x02] = "D/K (in progress)",
		[0x03] = "M (in progress)",

		[0x04] = "B/G A2",
		[0x05] = "B/G NICAM",
		[0x06] = "D/K A2 (1)",
		[0x07] = "D/K A2 (2)",
		[0x08] = "D/K A2 (3)",
		[0x09] = "D/K NICAM",
		[0x0a] = "L NICAM",
		[0x0b] = "I NICAM",

		[0x0c] = "M Korea",
		[0x0d] = "M BTSC ",
		[0x0e] = "M EIAJ",

		[0x0f] = "FM radio / IF 10.7 / 50 deemp",
		[0x10] = "FM radio / IF 10.7 / 75 deemp",
		[0x11] = "FM radio / IF sel / 50 deemp",
		[0x12] = "FM radio / IF sel / 75 deemp",

		[0x13 ... 0x1e] = "unknown",
		[0x1f] = "??? [in progress]",
	पूर्ण;


	*dual_flag = *stereo_flag = 0;

	/* (demdec status: 0x528) */

	/* पढ़ो current status */
	reg_data3 = saa717x_पढ़ो(sd, 0x0528);

	v4l2_dbg(1, debug, sd, "tvaudio thread status: 0x%x [%s%s%s]\n",
		reg_data3, stdres[reg_data3 & 0x1f],
		(reg_data3 & 0x000020) ? ",stereo" : "",
		(reg_data3 & 0x000040) ? ",dual"   : "");
	v4l2_dbg(1, debug, sd, "detailed status: "
		"%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s\n",
		(reg_data3 & 0x000080) ? " A2/EIAJ pilot tone "     : "",
		(reg_data3 & 0x000100) ? " A2/EIAJ dual "           : "",
		(reg_data3 & 0x000200) ? " A2/EIAJ stereo "         : "",
		(reg_data3 & 0x000400) ? " A2/EIAJ noise mute "     : "",

		(reg_data3 & 0x000800) ? " BTSC/FM radio pilot "    : "",
		(reg_data3 & 0x001000) ? " SAP carrier "            : "",
		(reg_data3 & 0x002000) ? " BTSC stereo noise mute " : "",
		(reg_data3 & 0x004000) ? " SAP noise mute "         : "",
		(reg_data3 & 0x008000) ? " VDSP "                   : "",

		(reg_data3 & 0x010000) ? " NICST "                  : "",
		(reg_data3 & 0x020000) ? " NICDU "                  : "",
		(reg_data3 & 0x040000) ? " NICAM muted "            : "",
		(reg_data3 & 0x080000) ? " NICAM reserve sound "    : "",

		(reg_data3 & 0x100000) ? " init done "              : "");

	अगर (reg_data3 & 0x000220) अणु
		v4l2_dbg(1, debug, sd, "ST!!!\n");
		*stereo_flag = 1;
	पूर्ण

	अगर (reg_data3 & 0x000140) अणु
		v4l2_dbg(1, debug, sd, "DUAL!!!\n");
		*dual_flag = 1;
	पूर्ण
पूर्ण

/* regs ग_लिखो to set audio mode */
अटल व्योम set_audio_mode(काष्ठा v4l2_subdev *sd, पूर्णांक audio_mode)
अणु
	v4l2_dbg(1, debug, sd, "writing registers to set audio mode by set %d\n",
			audio_mode);

	saa717x_ग_लिखो(sd, 0x46c, reg_set_audio_ढाँचा[audio_mode][0]);
	saa717x_ग_लिखो(sd, 0x470, reg_set_audio_ढाँचा[audio_mode][1]);
पूर्ण

/* ग_लिखो regs to set audio volume, bass and treble */
अटल पूर्णांक set_audio_regs(काष्ठा v4l2_subdev *sd,
		काष्ठा saa717x_state *decoder)
अणु
	u8 mute = 0xac; /* -84 dB */
	u32 val;
	अचिन्हित पूर्णांक work_l, work_r;

	/* set SIF analog I/O select */
	saa717x_ग_लिखो(sd, 0x0594, decoder->audio_input);
	v4l2_dbg(1, debug, sd, "set audio input %d\n",
			decoder->audio_input);

	/* normalize ( 65535 to 0 -> 24 to -40 (not -84)) */
	work_l = (min(65536 - decoder->audio_मुख्य_balance, 32768) * decoder->audio_मुख्य_volume) / 32768;
	work_r = (min(decoder->audio_मुख्य_balance, (u16)32768) * decoder->audio_मुख्य_volume) / 32768;
	decoder->audio_मुख्य_vol_l = (दीर्घ)work_l * (24 - (-40)) / 65535 - 40;
	decoder->audio_मुख्य_vol_r = (दीर्घ)work_r * (24 - (-40)) / 65535 - 40;

	/* set मुख्य volume */
	/* मुख्य volume L[7-0],R[7-0],0x00  24=24dB,-83dB, -84(mute) */
	/*    def:0dB->6dB(MPG600GR) */
	/* अगर mute is on, set mute */
	अगर (decoder->audio_मुख्य_mute) अणु
		val = mute | (mute << 8);
	पूर्ण अन्यथा अणु
		val = (u8)decoder->audio_मुख्य_vol_l |
			((u8)decoder->audio_मुख्य_vol_r << 8);
	पूर्ण

	saa717x_ग_लिखो(sd, 0x480, val);

	/* set bass and treble */
	val = decoder->audio_मुख्य_bass & 0x1f;
	val |= (decoder->audio_मुख्य_treble & 0x1f) << 5;
	saa717x_ग_लिखो(sd, 0x488, val);
	वापस 0;
पूर्ण

/********** scaling staff ***********/
अटल व्योम set_h_prescale(काष्ठा v4l2_subdev *sd,
		पूर्णांक task, पूर्णांक prescale)
अणु
	अटल स्थिर काष्ठा अणु
		पूर्णांक xpsc;
		पूर्णांक xacl;
		पूर्णांक xc2_1;
		पूर्णांक xdcg;
		पूर्णांक vpfy;
	पूर्ण vals[] = अणु
		/* XPSC XACL XC2_1 XDCG VPFY */
		अणु    1,   0,    0,    0,   0 पूर्ण,
		अणु    2,   2,    1,    2,   2 पूर्ण,
		अणु    3,   4,    1,    3,   2 पूर्ण,
		अणु    4,   8,    1,    4,   2 पूर्ण,
		अणु    5,   8,    1,    4,   2 पूर्ण,
		अणु    6,   8,    1,    4,   3 पूर्ण,
		अणु    7,   8,    1,    4,   3 पूर्ण,
		अणु    8,  15,    0,    4,   3 पूर्ण,
		अणु    9,  15,    0,    4,   3 पूर्ण,
		अणु   10,  16,    1,    5,   3 पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक count = ARRAY_SIZE(vals);
	पूर्णांक i, task_shअगरt;

	task_shअगरt = task * 0x40;
	क्रम (i = 0; i < count; i++)
		अगर (vals[i].xpsc == prescale)
			अवरोध;
	अगर (i == count)
		वापस;

	/* horizontal prescaling */
	saa717x_ग_लिखो(sd, 0x60 + task_shअगरt, vals[i].xpsc);
	/* accumulation length */
	saa717x_ग_लिखो(sd, 0x61 + task_shअगरt, vals[i].xacl);
	/* level control */
	saa717x_ग_लिखो(sd, 0x62 + task_shअगरt,
			(vals[i].xc2_1 << 3) | vals[i].xdcg);
	/*FIR prefilter control */
	saa717x_ग_लिखो(sd, 0x63 + task_shअगरt,
			(vals[i].vpfy << 2) | vals[i].vpfy);
पूर्ण

/********** scaling staff ***********/
अटल व्योम set_v_scale(काष्ठा v4l2_subdev *sd, पूर्णांक task, पूर्णांक yscale)
अणु
	पूर्णांक task_shअगरt;

	task_shअगरt = task * 0x40;
	/* Vertical scaling ratio (LOW) */
	saa717x_ग_लिखो(sd, 0x70 + task_shअगरt, yscale & 0xff);
	/* Vertical scaling ratio (HI) */
	saa717x_ग_लिखो(sd, 0x71 + task_shअगरt, yscale >> 8);
पूर्ण

अटल पूर्णांक saa717x_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा saa717x_state *state = to_state(sd);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		saa717x_ग_लिखो(sd, 0x10a, ctrl->val);
		वापस 0;

	हाल V4L2_CID_CONTRAST:
		saa717x_ग_लिखो(sd, 0x10b, ctrl->val);
		वापस 0;

	हाल V4L2_CID_SATURATION:
		saa717x_ग_लिखो(sd, 0x10c, ctrl->val);
		वापस 0;

	हाल V4L2_CID_HUE:
		saa717x_ग_लिखो(sd, 0x10d, ctrl->val);
		वापस 0;

	हाल V4L2_CID_AUDIO_MUTE:
		state->audio_मुख्य_mute = ctrl->val;
		अवरोध;

	हाल V4L2_CID_AUDIO_VOLUME:
		state->audio_मुख्य_volume = ctrl->val;
		अवरोध;

	हाल V4L2_CID_AUDIO_BALANCE:
		state->audio_मुख्य_balance = ctrl->val;
		अवरोध;

	हाल V4L2_CID_AUDIO_TREBLE:
		state->audio_मुख्य_treble = ctrl->val;
		अवरोध;

	हाल V4L2_CID_AUDIO_BASS:
		state->audio_मुख्य_bass = ctrl->val;
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण
	set_audio_regs(sd, state);
	वापस 0;
पूर्ण

अटल पूर्णांक saa717x_s_video_routing(काष्ठा v4l2_subdev *sd,
				   u32 input, u32 output, u32 config)
अणु
	काष्ठा saa717x_state *decoder = to_state(sd);
	पूर्णांक is_tuner = input & 0x80;  /* tuner input flag */

	input &= 0x7f;

	v4l2_dbg(1, debug, sd, "decoder set input (%d)\n", input);
	/* inमाला_दो from 0-9 are available*/
	/* saa717x have mode0-mode9 but mode5 is reserved. */
	अगर (input > 9 || input == 5)
		वापस -EINVAL;

	अगर (decoder->input != input) अणु
		पूर्णांक input_line = input;

		decoder->input = input_line;
		v4l2_dbg(1, debug, sd,  "now setting %s input %d\n",
				input_line >= 6 ? "S-Video" : "Composite",
				input_line);

		/* select mode */
		saa717x_ग_लिखो(sd, 0x102,
				(saa717x_पढ़ो(sd, 0x102) & 0xf0) |
				input_line);

		/* bypass chrominance trap क्रम modes 6..9 */
		saa717x_ग_लिखो(sd, 0x109,
				(saa717x_पढ़ो(sd, 0x109) & 0x7f) |
				(input_line < 6 ? 0x0 : 0x80));

		/* change audio_mode */
		अगर (is_tuner) अणु
			/* tuner */
			set_audio_mode(sd, decoder->tuner_audio_mode);
		पूर्ण अन्यथा अणु
			/* Force to STEREO mode अगर Composite or
			 * S-Video were chosen */
			set_audio_mode(sd, TUNER_AUDIO_STEREO);
		पूर्ण
		/* change initialize procedure (Composite/S-Video) */
		अगर (is_tuner)
			saa717x_ग_लिखो_regs(sd, reg_init_tuner_input);
		अन्यथा अगर (input_line >= 6)
			saa717x_ग_लिखो_regs(sd, reg_init_svideo_input);
		अन्यथा
			saa717x_ग_लिखो_regs(sd, reg_init_composite_input);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक saa717x_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->val = saa717x_पढ़ो(sd, reg->reg);
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक saa717x_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	u16 addr = reg->reg & 0xffff;
	u8 val = reg->val & 0xff;

	saa717x_ग_लिखो(sd, addr, val);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक saa717x_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	पूर्णांक prescale, h_scale, v_scale;

	v4l2_dbg(1, debug, sd, "decoder set size\n");

	अगर (क्रमmat->pad || fmt->code != MEDIA_BUS_FMT_FIXED)
		वापस -EINVAL;

	/* FIXME need better bounds checking here */
	अगर (fmt->width < 1 || fmt->width > 1440)
		वापस -EINVAL;
	अगर (fmt->height < 1 || fmt->height > 960)
		वापस -EINVAL;

	fmt->field = V4L2_FIELD_INTERLACED;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		वापस 0;

	/* scaling setting */
	/* NTSC and पूर्णांकerlace only */
	prescale = SAA717X_NTSC_WIDTH / fmt->width;
	अगर (prescale == 0)
		prescale = 1;
	h_scale = 1024 * SAA717X_NTSC_WIDTH / prescale / fmt->width;
	/* पूर्णांकerlace */
	v_scale = 512 * 2 * SAA717X_NTSC_HEIGHT / fmt->height;

	/* Horizontal prescaling etc */
	set_h_prescale(sd, 0, prescale);
	set_h_prescale(sd, 1, prescale);

	/* Horizontal scaling increment */
	/* TASK A */
	saa717x_ग_लिखो(sd, 0x6C, (u8)(h_scale & 0xFF));
	saa717x_ग_लिखो(sd, 0x6D, (u8)((h_scale >> 8) & 0xFF));
	/* TASK B */
	saa717x_ग_लिखो(sd, 0xAC, (u8)(h_scale & 0xFF));
	saa717x_ग_लिखो(sd, 0xAD, (u8)((h_scale >> 8) & 0xFF));

	/* Vertical prescaling etc */
	set_v_scale(sd, 0, v_scale);
	set_v_scale(sd, 1, v_scale);

	/* set video output size */
	/* video number of pixels at output */
	/* TASK A */
	saa717x_ग_लिखो(sd, 0x5C, (u8)(fmt->width & 0xFF));
	saa717x_ग_लिखो(sd, 0x5D, (u8)((fmt->width >> 8) & 0xFF));
	/* TASK B */
	saa717x_ग_लिखो(sd, 0x9C, (u8)(fmt->width & 0xFF));
	saa717x_ग_लिखो(sd, 0x9D, (u8)((fmt->width >> 8) & 0xFF));

	/* video number of lines at output */
	/* TASK A */
	saa717x_ग_लिखो(sd, 0x5E, (u8)(fmt->height & 0xFF));
	saa717x_ग_लिखो(sd, 0x5F, (u8)((fmt->height >> 8) & 0xFF));
	/* TASK B */
	saa717x_ग_लिखो(sd, 0x9E, (u8)(fmt->height & 0xFF));
	saa717x_ग_लिखो(sd, 0x9F, (u8)((fmt->height >> 8) & 0xFF));
	वापस 0;
पूर्ण

अटल पूर्णांक saa717x_s_radio(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा saa717x_state *decoder = to_state(sd);

	decoder->radio = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक saa717x_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा saa717x_state *decoder = to_state(sd);

	v4l2_dbg(1, debug, sd, "decoder set norm ");
	v4l2_dbg(1, debug, sd, "(not yet implemented)\n");

	decoder->radio = 0;
	decoder->std = std;
	वापस 0;
पूर्ण

अटल पूर्णांक saa717x_s_audio_routing(काष्ठा v4l2_subdev *sd,
				   u32 input, u32 output, u32 config)
अणु
	काष्ठा saa717x_state *decoder = to_state(sd);

	अगर (input < 3) अणु /* FIXME! --tadachi */
		decoder->audio_input = input;
		v4l2_dbg(1, debug, sd,
				"set decoder audio input to %d\n",
				decoder->audio_input);
		set_audio_regs(sd, decoder);
		वापस 0;
	पूर्ण
	वापस -दुस्फल;
पूर्ण

अटल पूर्णांक saa717x_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा saa717x_state *decoder = to_state(sd);

	v4l2_dbg(1, debug, sd, "decoder %s output\n",
			enable ? "enable" : "disable");
	decoder->enable = enable;
	saa717x_ग_लिखो(sd, 0x193, enable ? 0xa6 : 0x26);
	वापस 0;
पूर्ण

/* change audio mode */
अटल पूर्णांक saa717x_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा saa717x_state *decoder = to_state(sd);
	पूर्णांक audio_mode;
	अक्षर *mes[4] = अणु
		"MONO", "STEREO", "LANG1", "LANG2/SAP"
	पूर्ण;

	audio_mode = TUNER_AUDIO_STEREO;

	चयन (vt->audmode) अणु
		हाल V4L2_TUNER_MODE_MONO:
			audio_mode = TUNER_AUDIO_MONO;
			अवरोध;
		हाल V4L2_TUNER_MODE_STEREO:
			audio_mode = TUNER_AUDIO_STEREO;
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG2:
			audio_mode = TUNER_AUDIO_LANG2;
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG1:
			audio_mode = TUNER_AUDIO_LANG1;
			अवरोध;
	पूर्ण

	v4l2_dbg(1, debug, sd, "change audio mode to %s\n",
			mes[audio_mode]);
	decoder->tuner_audio_mode = audio_mode;
	/* The रेजिस्टरs are not changed here. */
	/* See DECODER_ENABLE_OUTPUT section. */
	set_audio_mode(sd, decoder->tuner_audio_mode);
	वापस 0;
पूर्ण

अटल पूर्णांक saa717x_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा saa717x_state *decoder = to_state(sd);
	पूर्णांक dual_f, stereo_f;

	अगर (decoder->radio)
		वापस 0;
	get_inf_dev_status(sd, &dual_f, &stereo_f);

	v4l2_dbg(1, debug, sd, "DETECT==st:%d dual:%d\n",
			stereo_f, dual_f);

	/* mono */
	अगर ((dual_f == 0) && (stereo_f == 0)) अणु
		vt->rxsubchans = V4L2_TUNER_SUB_MONO;
		v4l2_dbg(1, debug, sd, "DETECT==MONO\n");
	पूर्ण

	/* stereo */
	अगर (stereo_f == 1) अणु
		अगर (vt->audmode == V4L2_TUNER_MODE_STEREO ||
				vt->audmode == V4L2_TUNER_MODE_LANG1) अणु
			vt->rxsubchans = V4L2_TUNER_SUB_STEREO;
			v4l2_dbg(1, debug, sd, "DETECT==ST(ST)\n");
		पूर्ण अन्यथा अणु
			vt->rxsubchans = V4L2_TUNER_SUB_MONO;
			v4l2_dbg(1, debug, sd, "DETECT==ST(MONO)\n");
		पूर्ण
	पूर्ण

	/* dual */
	अगर (dual_f == 1) अणु
		अगर (vt->audmode == V4L2_TUNER_MODE_LANG2) अणु
			vt->rxsubchans = V4L2_TUNER_SUB_LANG2 | V4L2_TUNER_SUB_MONO;
			v4l2_dbg(1, debug, sd, "DETECT==DUAL1\n");
		पूर्ण अन्यथा अणु
			vt->rxsubchans = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_MONO;
			v4l2_dbg(1, debug, sd, "DETECT==DUAL2\n");
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa717x_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा saa717x_state *state = to_state(sd);

	v4l2_ctrl_handler_log_status(&state->hdl, sd->name);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops saa717x_ctrl_ops = अणु
	.s_ctrl = saa717x_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops saa717x_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = saa717x_g_रेजिस्टर,
	.s_रेजिस्टर = saa717x_s_रेजिस्टर,
#पूर्ण_अगर
	.log_status = saa717x_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops saa717x_tuner_ops = अणु
	.g_tuner = saa717x_g_tuner,
	.s_tuner = saa717x_s_tuner,
	.s_radio = saa717x_s_radio,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops saa717x_video_ops = अणु
	.s_std = saa717x_s_std,
	.s_routing = saa717x_s_video_routing,
	.s_stream = saa717x_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops saa717x_audio_ops = अणु
	.s_routing = saa717x_s_audio_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops saa717x_pad_ops = अणु
	.set_fmt = saa717x_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops saa717x_ops = अणु
	.core = &saa717x_core_ops,
	.tuner = &saa717x_tuner_ops,
	.audio = &saa717x_audio_ops,
	.video = &saa717x_video_ops,
	.pad = &saa717x_pad_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */


/* i2c implementation */

/* ----------------------------------------------------------------------- */
अटल पूर्णांक saa717x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा saa717x_state *decoder;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा v4l2_subdev *sd;
	u8 id = 0;
	अक्षर *p = "";

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	decoder = devm_kzalloc(&client->dev, माप(*decoder), GFP_KERNEL);
	अगर (decoder == शून्य)
		वापस -ENOMEM;

	sd = &decoder->sd;
	v4l2_i2c_subdev_init(sd, client, &saa717x_ops);

	अगर (saa717x_ग_लिखो(sd, 0x5a4, 0xfe) &&
			saa717x_ग_लिखो(sd, 0x5a5, 0x0f) &&
			saa717x_ग_लिखो(sd, 0x5a6, 0x00) &&
			saa717x_ग_लिखो(sd, 0x5a7, 0x01))
		id = saa717x_पढ़ो(sd, 0x5a0);
	अगर (id != 0xc2 && id != 0x32 && id != 0xf2 && id != 0x6c) अणु
		v4l2_dbg(1, debug, sd, "saa717x not found (id=%02x)\n", id);
		वापस -ENODEV;
	पूर्ण
	अगर (id == 0xc2)
		p = "saa7173";
	अन्यथा अगर (id == 0x32)
		p = "saa7174A";
	अन्यथा अगर (id == 0x6c)
		p = "saa7174HL";
	अन्यथा
		p = "saa7171";
	v4l2_info(sd, "%s found @ 0x%x (%s)\n", p,
			client->addr << 1, client->adapter->name);

	hdl = &decoder->hdl;
	v4l2_ctrl_handler_init(hdl, 9);
	/* add in ascending ID order */
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 68);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 64);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, 65535, 65535 / 100, 42000);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_AUDIO_BALANCE, 0, 65535, 65535 / 100, 32768);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_AUDIO_BASS, -16, 15, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_AUDIO_TREBLE, -16, 15, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa717x_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		पूर्णांक err = hdl->error;

		v4l2_ctrl_handler_मुक्त(hdl);
		वापस err;
	पूर्ण

	decoder->std = V4L2_STD_NTSC;
	decoder->input = -1;
	decoder->enable = 1;

	/* FIXME!! */
	decoder->playback = 0;	/* initially capture mode used */
	decoder->audio = 1; /* DECODER_AUDIO_48_KHZ */

	decoder->audio_input = 2; /* FIXME!! */

	decoder->tuner_audio_mode = TUNER_AUDIO_STEREO;
	/* set volume, bass and treble */
	decoder->audio_मुख्य_vol_l = 6;
	decoder->audio_मुख्य_vol_r = 6;

	v4l2_dbg(1, debug, sd, "writing init values\n");

	/* FIXME!! */
	saa717x_ग_लिखो_regs(sd, reg_init_initialize);

	v4l2_ctrl_handler_setup(hdl);

	set_current_state(TASK_INTERRUPTIBLE);
	schedule_समयout(2*HZ);
	वापस 0;
पूर्ण

अटल पूर्णांक saa717x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id saa717x_id[] = अणु
	अणु "saa717x", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, saa717x_id);

अटल काष्ठा i2c_driver saa717x_driver = अणु
	.driver = अणु
		.name	= "saa717x",
	पूर्ण,
	.probe		= saa717x_probe,
	.हटाओ		= saa717x_हटाओ,
	.id_table	= saa717x_id,
पूर्ण;

module_i2c_driver(saa717x_driver);
