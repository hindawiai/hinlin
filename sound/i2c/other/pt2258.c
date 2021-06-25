<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA Driver क्रम the PT2258 volume controller.
 *
 *	Copyright (c) 2006  Jochen Voss <voss@seehuhn.de>
 */      

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/i2c.h>
#समावेश <sound/pt2258.h>
#समावेश <linux/module.h>

MODULE_AUTHOR("Jochen Voss <voss@seehuhn.de>");
MODULE_DESCRIPTION("PT2258 volume controller (Princeton Technology Corp.)");
MODULE_LICENSE("GPL");

#घोषणा PT2258_CMD_RESET 0xc0
#घोषणा PT2258_CMD_UNMUTE 0xf8
#घोषणा PT2258_CMD_MUTE 0xf9

अटल स्थिर अचिन्हित अक्षर pt2258_channel_code[12] = अणु
	0x80, 0x90,		/* channel 1: -10dB, -1dB */
	0x40, 0x50,		/* channel 2: -10dB, -1dB */
	0x00, 0x10,		/* channel 3: -10dB, -1dB */
	0x20, 0x30,		/* channel 4: -10dB, -1dB */
	0x60, 0x70,		/* channel 5: -10dB, -1dB */
	0xa0, 0xb0		/* channel 6: -10dB, -1dB */
पूर्ण;

पूर्णांक snd_pt2258_reset(काष्ठा snd_pt2258 *pt)
अणु
	अचिन्हित अक्षर bytes[2];
	पूर्णांक i;

	/* reset chip */
	bytes[0] = PT2258_CMD_RESET;
	snd_i2c_lock(pt->i2c_bus);
	अगर (snd_i2c_sendbytes(pt->i2c_dev, bytes, 1) != 1)
		जाओ __error;
	snd_i2c_unlock(pt->i2c_bus);

	/* mute all channels */
	pt->mute = 1;
	bytes[0] = PT2258_CMD_MUTE;
	snd_i2c_lock(pt->i2c_bus);
	अगर (snd_i2c_sendbytes(pt->i2c_dev, bytes, 1) != 1)
		जाओ __error;
	snd_i2c_unlock(pt->i2c_bus);

	/* set all channels to 0dB */
	क्रम (i = 0; i < 6; ++i)
		pt->volume[i] = 0;
	bytes[0] = 0xd0;
	bytes[1] = 0xe0;
	snd_i2c_lock(pt->i2c_bus);
	अगर (snd_i2c_sendbytes(pt->i2c_dev, bytes, 2) != 2)
		जाओ __error;
	snd_i2c_unlock(pt->i2c_bus);

	वापस 0;

      __error:
	snd_i2c_unlock(pt->i2c_bus);
	snd_prपूर्णांकk(KERN_ERR "PT2258 reset failed\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक pt2258_stereo_volume_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 79;
	वापस 0;
पूर्ण

अटल पूर्णांक pt2258_stereo_volume_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pt2258 *pt = kcontrol->निजी_data;
	पूर्णांक base = kcontrol->निजी_value;

	/* chip करोes not support रेजिस्टर पढ़ोs */
	ucontrol->value.पूर्णांकeger.value[0] = 79 - pt->volume[base];
	ucontrol->value.पूर्णांकeger.value[1] = 79 - pt->volume[base + 1];
	वापस 0;
पूर्ण

अटल पूर्णांक pt2258_stereo_volume_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pt2258 *pt = kcontrol->निजी_data;
	पूर्णांक base = kcontrol->निजी_value;
	अचिन्हित अक्षर bytes[2];
	पूर्णांक val0, val1;

	val0 = 79 - ucontrol->value.पूर्णांकeger.value[0];
	val1 = 79 - ucontrol->value.पूर्णांकeger.value[1];
	अगर (val0 < 0 || val0 > 79 || val1 < 0 || val1 > 79)
		वापस -EINVAL;
	अगर (val0 == pt->volume[base] && val1 == pt->volume[base + 1])
		वापस 0;

	pt->volume[base] = val0;
	bytes[0] = pt2258_channel_code[2 * base] | (val0 / 10);
	bytes[1] = pt2258_channel_code[2 * base + 1] | (val0 % 10);
	snd_i2c_lock(pt->i2c_bus);
	अगर (snd_i2c_sendbytes(pt->i2c_dev, bytes, 2) != 2)
		जाओ __error;
	snd_i2c_unlock(pt->i2c_bus);

	pt->volume[base + 1] = val1;
	bytes[0] = pt2258_channel_code[2 * base + 2] | (val1 / 10);
	bytes[1] = pt2258_channel_code[2 * base + 3] | (val1 % 10);
	snd_i2c_lock(pt->i2c_bus);
	अगर (snd_i2c_sendbytes(pt->i2c_dev, bytes, 2) != 2)
		जाओ __error;
	snd_i2c_unlock(pt->i2c_bus);

	वापस 1;

      __error:
	snd_i2c_unlock(pt->i2c_bus);
	snd_prपूर्णांकk(KERN_ERR "PT2258 access failed\n");
	वापस -EIO;
पूर्ण

#घोषणा pt2258_चयन_info	snd_ctl_boolean_mono_info

अटल पूर्णांक pt2258_चयन_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pt2258 *pt = kcontrol->निजी_data;

	ucontrol->value.पूर्णांकeger.value[0] = !pt->mute;
	वापस 0;
पूर्ण

अटल पूर्णांक pt2258_चयन_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pt2258 *pt = kcontrol->निजी_data;
	अचिन्हित अक्षर bytes[2];
	पूर्णांक val;

	val = !ucontrol->value.पूर्णांकeger.value[0];
	अगर (pt->mute == val)
		वापस 0;

	pt->mute = val;
	bytes[0] = val ? PT2258_CMD_MUTE : PT2258_CMD_UNMUTE;
	snd_i2c_lock(pt->i2c_bus);
	अगर (snd_i2c_sendbytes(pt->i2c_dev, bytes, 1) != 1)
		जाओ __error;
	snd_i2c_unlock(pt->i2c_bus);

	वापस 1;

      __error:
	snd_i2c_unlock(pt->i2c_bus);
	snd_prपूर्णांकk(KERN_ERR "PT2258 access failed 2\n");
	वापस -EIO;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(pt2258_db_scale, -7900, 100, 0);

पूर्णांक snd_pt2258_build_controls(काष्ठा snd_pt2258 *pt)
अणु
	काष्ठा snd_kcontrol_new knew;
	अक्षर *names[3] = अणु
		"Mic Loopback Playback Volume",
		"Line Loopback Playback Volume",
		"CD Loopback Playback Volume"
	पूर्ण;
	पूर्णांक i, err;

	क्रम (i = 0; i < 3; ++i) अणु
		स_रखो(&knew, 0, माप(knew));
		knew.name = names[i];
		knew.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		knew.count = 1;
		knew.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
		    SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		knew.निजी_value = 2 * i;
		knew.info = pt2258_stereo_volume_info;
		knew.get = pt2258_stereo_volume_get;
		knew.put = pt2258_stereo_volume_put;
		knew.tlv.p = pt2258_db_scale;

		err = snd_ctl_add(pt->card, snd_ctl_new1(&knew, pt));
		अगर (err < 0)
			वापस err;
	पूर्ण

	स_रखो(&knew, 0, माप(knew));
	knew.name = "Loopback Switch";
	knew.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	knew.info = pt2258_चयन_info;
	knew.get = pt2258_चयन_get;
	knew.put = pt2258_चयन_put;
	knew.access = 0;
	err = snd_ctl_add(pt->card, snd_ctl_new1(&knew, pt));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_pt2258_reset);
EXPORT_SYMBOL(snd_pt2258_build_controls);
