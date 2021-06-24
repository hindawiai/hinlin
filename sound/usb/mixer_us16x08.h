<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USB_MIXER_US16X08_H
#घोषणा __USB_MIXER_US16X08_H

#घोषणा SND_US16X08_MAX_CHANNELS 16

/* define some bias, cause some alsa-mixers wont work with
 * negative ranges or अगर mixer-min != 0
 */
#घोषणा SND_US16X08_NO_BIAS 0
#घोषणा SND_US16X08_FADER_BIAS 127
#घोषणा SND_US16X08_EQ_HIGHFREQ_BIAS 0x20
#घोषणा SND_US16X08_COMP_THRESHOLD_BIAS 0x20
#घोषणा SND_US16X08_COMP_ATTACK_BIAS 2
#घोषणा SND_US16X08_COMP_RELEASE_BIAS 1

/* get macro क्रम components of kcontrol निजी_value */
#घोषणा SND_US16X08_KCBIAS(x) (((x)->निजी_value >> 24) & 0xff)
#घोषणा SND_US16X08_KCSTEP(x) (((x)->निजी_value >> 16) & 0xff)
#घोषणा SND_US16X08_KCMIN(x) (((x)->निजी_value >> 8) & 0xff)
#घोषणा SND_US16X08_KCMAX(x) (((x)->निजी_value >> 0) & 0xff)
/* set macro क्रम kcontrol निजी_value */
#घोषणा SND_US16X08_KCSET(bias, step, min, max)  \
	(((bias) << 24) | ((step) << 16) | ((min) << 8) | (max))

/* the URB request/type to control Tascam mixers */
#घोषणा SND_US16X08_URB_REQUEST 0x1D
#घोषणा SND_US16X08_URB_REQUESTTYPE 0x40

/* the URB params to retrieve meter ranges */
#घोषणा SND_US16X08_URB_METER_REQUEST       0x1e
#घोषणा SND_US16X08_URB_METER_REQUESTTYPE   0xc0

#घोषणा MUA0(x, y) ((x)[(y) * 10 + 4])
#घोषणा MUA1(x, y) ((x)[(y) * 10 + 5])
#घोषणा MUA2(x, y) ((x)[(y) * 10 + 6])
#घोषणा MUB0(x, y) ((x)[(y) * 10 + 7])
#घोषणा MUB1(x, y) ((x)[(y) * 10 + 8])
#घोषणा MUB2(x, y) ((x)[(y) * 10 + 9])
#घोषणा MUC0(x, y) ((x)[(y) * 10 + 10])
#घोषणा MUC1(x, y) ((x)[(y) * 10 + 11])
#घोषणा MUC2(x, y) ((x)[(y) * 10 + 12])
#घोषणा MUC3(x, y) ((x)[(y) * 10 + 13])

/* Common Channel control IDs */
#घोषणा SND_US16X08_ID_BYPASS 0x45
#घोषणा SND_US16X08_ID_BUSS_OUT 0x44
#घोषणा SND_US16X08_ID_PHASE 0x85
#घोषणा SND_US16X08_ID_MUTE 0x83
#घोषणा SND_US16X08_ID_FADER 0x81
#घोषणा SND_US16X08_ID_PAN 0x82
#घोषणा SND_US16X08_ID_METER 0xB1

#घोषणा SND_US16X08_ID_EQ_BAND_COUNT 4
#घोषणा SND_US16X08_ID_EQ_PARAM_COUNT 4

/* EQ level IDs */
#घोषणा SND_US16X08_ID_EQLOWLEVEL 0x01
#घोषणा SND_US16X08_ID_EQLOWMIDLEVEL 0x02
#घोषणा SND_US16X08_ID_EQHIGHMIDLEVEL 0x03
#घोषणा SND_US16X08_ID_EQHIGHLEVEL 0x04

/* EQ frequence IDs */
#घोषणा SND_US16X08_ID_EQLOWFREQ 0x11
#घोषणा SND_US16X08_ID_EQLOWMIDFREQ 0x12
#घोषणा SND_US16X08_ID_EQHIGHMIDFREQ 0x13
#घोषणा SND_US16X08_ID_EQHIGHFREQ 0x14

/* EQ width IDs */
#घोषणा SND_US16X08_ID_EQLOWMIDWIDTH 0x22
#घोषणा SND_US16X08_ID_EQHIGHMIDWIDTH 0x23

#घोषणा SND_US16X08_ID_EQENABLE 0x30

#घोषणा EQ_STORE_BAND_IDX(x) ((x) & 0xf)
#घोषणा EQ_STORE_PARAM_IDX(x) (((x) & 0xf0) >> 4)

#घोषणा SND_US16X08_ID_ROUTE 0x00

/* Compressor Ids */
#घोषणा SND_US16X08_ID_COMP_BASE	0x32
#घोषणा SND_US16X08_ID_COMP_THRESHOLD	SND_US16X08_ID_COMP_BASE
#घोषणा SND_US16X08_ID_COMP_RATIO	(SND_US16X08_ID_COMP_BASE + 1)
#घोषणा SND_US16X08_ID_COMP_ATTACK	(SND_US16X08_ID_COMP_BASE + 2)
#घोषणा SND_US16X08_ID_COMP_RELEASE	(SND_US16X08_ID_COMP_BASE + 3)
#घोषणा SND_US16X08_ID_COMP_GAIN	(SND_US16X08_ID_COMP_BASE + 4)
#घोषणा SND_US16X08_ID_COMP_SWITCH	(SND_US16X08_ID_COMP_BASE + 5)
#घोषणा SND_US16X08_ID_COMP_COUNT	6

#घोषणा COMP_STORE_IDX(x) ((x) - SND_US16X08_ID_COMP_BASE)

काष्ठा snd_us16x08_eq_store अणु
	u8 val[SND_US16X08_ID_EQ_BAND_COUNT][SND_US16X08_ID_EQ_PARAM_COUNT]
		[SND_US16X08_MAX_CHANNELS];
पूर्ण;

काष्ठा snd_us16x08_comp_store अणु
	u8 val[SND_US16X08_ID_COMP_COUNT][SND_US16X08_MAX_CHANNELS];
पूर्ण;

काष्ठा snd_us16x08_meter_store अणु
	पूर्णांक meter_level[SND_US16X08_MAX_CHANNELS];
	पूर्णांक master_level[2]; /* level of meter क्रम master output */
	पूर्णांक comp_index; /* round trip channel selector */
	पूर्णांक comp_active_index; /* channel select from user space mixer */
	पूर्णांक comp_level[16]; /* compressor reduction level */
	काष्ठा snd_us16x08_comp_store *comp_store;
पूर्ण;

काष्ठा snd_us16x08_control_params अणु
	स्थिर काष्ठा snd_kcontrol_new *kcontrol_new;
	पूर्णांक control_id;
	पूर्णांक type;
	पूर्णांक num_channels;
	स्थिर अक्षर *name;
	पूर्णांक शेष_val;
पूर्ण;

#घोषणा snd_us16x08_चयन_info snd_ctl_boolean_mono_info

पूर्णांक snd_us16x08_controls_create(काष्ठा usb_mixer_पूर्णांकerface *mixer);
#पूर्ण_अगर /* __USB_MIXER_US16X08_H */
