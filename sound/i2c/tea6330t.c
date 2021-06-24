<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Routines क्रम control of the TEA6330T circuit via i2c bus
 *  Sound fader control circuit क्रम car radios by Philips Semiconductors
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tea6330t.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Routines for control of the TEA6330T circuit via i2c bus");
MODULE_LICENSE("GPL");

#घोषणा TEA6330T_ADDR			(0x80>>1) /* fixed address */

#घोषणा TEA6330T_SADDR_VOLUME_LEFT	0x00	/* volume left */
#घोषणा TEA6330T_SADDR_VOLUME_RIGHT	0x01	/* volume right */
#घोषणा TEA6330T_SADDR_BASS		0x02	/* bass control */
#घोषणा TEA6330T_SADDR_TREBLE		0x03	/* treble control */
#घोषणा TEA6330T_SADDR_FADER		0x04	/* fader control */
#घोषणा   TEA6330T_MFN			0x20	/* mute control क्रम selected channels */
#घोषणा   TEA6330T_FCH			0x10	/* select fader channels - front or rear */
#घोषणा TEA6330T_SADDR_AUDIO_SWITCH	0x05	/* audio चयन */
#घोषणा   TEA6330T_GMU			0x80	/* mute control, general mute */
#घोषणा   TEA6330T_EQN			0x40	/* equalizer चयनover (0=equalizer-on) */


काष्ठा tea6330t अणु
	काष्ठा snd_i2c_device *device;
	काष्ठा snd_i2c_bus *bus;
	पूर्णांक equalizer;
	पूर्णांक fader;
	अचिन्हित अक्षर regs[8];
	अचिन्हित अक्षर mleft, mright;
	अचिन्हित अक्षर bass, treble;
	अचिन्हित अक्षर max_bass, max_treble;
पूर्ण;


पूर्णांक snd_tea6330t_detect(काष्ठा snd_i2c_bus *bus, पूर्णांक equalizer)
अणु
	पूर्णांक res;

	snd_i2c_lock(bus);
	res = snd_i2c_probeaddr(bus, TEA6330T_ADDR);
	snd_i2c_unlock(bus);
	वापस res;
पूर्ण

#अगर 0
अटल व्योम snd_tea6330t_set(काष्ठा tea6330t *tea,
			     अचिन्हित अक्षर addr, अचिन्हित अक्षर value)
अणु
#अगर 0
	prपूर्णांकk(KERN_DEBUG "set - 0x%x/0x%x\n", addr, value);
#पूर्ण_अगर
	snd_i2c_ग_लिखो(tea->bus, TEA6330T_ADDR, addr, value, 1);
पूर्ण
#पूर्ण_अगर

#घोषणा TEA6330T_MASTER_VOLUME(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_tea6330t_info_master_volume, \
  .get = snd_tea6330t_get_master_volume, .put = snd_tea6330t_put_master_volume पूर्ण

अटल पूर्णांक snd_tea6330t_info_master_volume(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 43;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_tea6330t_get_master_volume(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tea6330t *tea = snd_kcontrol_chip(kcontrol);
	
	snd_i2c_lock(tea->bus);
	ucontrol->value.पूर्णांकeger.value[0] = tea->mleft - 0x14;
	ucontrol->value.पूर्णांकeger.value[1] = tea->mright - 0x14;
	snd_i2c_unlock(tea->bus);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_tea6330t_put_master_volume(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tea6330t *tea = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, count, err;
	अचिन्हित अक्षर bytes[3];
	अचिन्हित अक्षर val1, val2;
	
	val1 = (ucontrol->value.पूर्णांकeger.value[0] % 44) + 0x14;
	val2 = (ucontrol->value.पूर्णांकeger.value[1] % 44) + 0x14;
	snd_i2c_lock(tea->bus);
	change = val1 != tea->mleft || val2 != tea->mright;
	tea->mleft = val1;
	tea->mright = val2;
	count = 0;
	अगर (tea->regs[TEA6330T_SADDR_VOLUME_LEFT] != 0) अणु
		bytes[count++] = TEA6330T_SADDR_VOLUME_LEFT;
		bytes[count++] = tea->regs[TEA6330T_SADDR_VOLUME_LEFT] = tea->mleft;
	पूर्ण
	अगर (tea->regs[TEA6330T_SADDR_VOLUME_RIGHT] != 0) अणु
		अगर (count == 0)
			bytes[count++] = TEA6330T_SADDR_VOLUME_RIGHT;
		bytes[count++] = tea->regs[TEA6330T_SADDR_VOLUME_RIGHT] = tea->mright;
	पूर्ण
	अगर (count > 0) अणु
		अगर ((err = snd_i2c_sendbytes(tea->device, bytes, count)) < 0)
			change = err;
	पूर्ण
	snd_i2c_unlock(tea->bus);
	वापस change;
पूर्ण

#घोषणा TEA6330T_MASTER_SWITCH(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_tea6330t_info_master_चयन, \
  .get = snd_tea6330t_get_master_चयन, .put = snd_tea6330t_put_master_चयन पूर्ण

#घोषणा snd_tea6330t_info_master_चयन		snd_ctl_boolean_stereo_info

अटल पूर्णांक snd_tea6330t_get_master_चयन(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tea6330t *tea = snd_kcontrol_chip(kcontrol);
	
	snd_i2c_lock(tea->bus);
	ucontrol->value.पूर्णांकeger.value[0] = tea->regs[TEA6330T_SADDR_VOLUME_LEFT] == 0 ? 0 : 1;
	ucontrol->value.पूर्णांकeger.value[1] = tea->regs[TEA6330T_SADDR_VOLUME_RIGHT] == 0 ? 0 : 1;
	snd_i2c_unlock(tea->bus);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_tea6330t_put_master_चयन(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tea6330t *tea = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, err;
	अचिन्हित अक्षर bytes[3];
	अचिन्हित अक्षर oval1, oval2, val1, val2;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] & 1;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & 1;
	snd_i2c_lock(tea->bus);
	oval1 = tea->regs[TEA6330T_SADDR_VOLUME_LEFT] == 0 ? 0 : 1;
	oval2 = tea->regs[TEA6330T_SADDR_VOLUME_RIGHT] == 0 ? 0 : 1;
	change = val1 != oval1 || val2 != oval2;
	tea->regs[TEA6330T_SADDR_VOLUME_LEFT] = val1 ? tea->mleft : 0;
	tea->regs[TEA6330T_SADDR_VOLUME_RIGHT] = val2 ? tea->mright : 0;
	bytes[0] = TEA6330T_SADDR_VOLUME_LEFT;
	bytes[1] = tea->regs[TEA6330T_SADDR_VOLUME_LEFT];
	bytes[2] = tea->regs[TEA6330T_SADDR_VOLUME_RIGHT];
	अगर ((err = snd_i2c_sendbytes(tea->device, bytes, 3)) < 0)
		change = err;
	snd_i2c_unlock(tea->bus);
	वापस change;
पूर्ण

#घोषणा TEA6330T_BASS(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_tea6330t_info_bass, \
  .get = snd_tea6330t_get_bass, .put = snd_tea6330t_put_bass पूर्ण

अटल पूर्णांक snd_tea6330t_info_bass(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा tea6330t *tea = snd_kcontrol_chip(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = tea->max_bass;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_tea6330t_get_bass(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tea6330t *tea = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.पूर्णांकeger.value[0] = tea->bass;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_tea6330t_put_bass(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tea6330t *tea = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, err;
	अचिन्हित अक्षर bytes[2];
	अचिन्हित अक्षर val1;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] % (tea->max_bass + 1);
	snd_i2c_lock(tea->bus);
	tea->bass = val1;
	val1 += tea->equalizer ? 7 : 3;
	change = tea->regs[TEA6330T_SADDR_BASS] != val1;
	bytes[0] = TEA6330T_SADDR_BASS;
	bytes[1] = tea->regs[TEA6330T_SADDR_BASS] = val1;
	अगर ((err = snd_i2c_sendbytes(tea->device, bytes, 2)) < 0)
		change = err;
	snd_i2c_unlock(tea->bus);
	वापस change;
पूर्ण

#घोषणा TEA6330T_TREBLE(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_tea6330t_info_treble, \
  .get = snd_tea6330t_get_treble, .put = snd_tea6330t_put_treble पूर्ण

अटल पूर्णांक snd_tea6330t_info_treble(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा tea6330t *tea = snd_kcontrol_chip(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = tea->max_treble;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_tea6330t_get_treble(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tea6330t *tea = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.पूर्णांकeger.value[0] = tea->treble;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_tea6330t_put_treble(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tea6330t *tea = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, err;
	अचिन्हित अक्षर bytes[2];
	अचिन्हित अक्षर val1;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] % (tea->max_treble + 1);
	snd_i2c_lock(tea->bus);
	tea->treble = val1;
	val1 += 3;
	change = tea->regs[TEA6330T_SADDR_TREBLE] != val1;
	bytes[0] = TEA6330T_SADDR_TREBLE;
	bytes[1] = tea->regs[TEA6330T_SADDR_TREBLE] = val1;
	अगर ((err = snd_i2c_sendbytes(tea->device, bytes, 2)) < 0)
		change = err;
	snd_i2c_unlock(tea->bus);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_tea6330t_controls[] = अणु
TEA6330T_MASTER_SWITCH("Master Playback Switch", 0),
TEA6330T_MASTER_VOLUME("Master Playback Volume", 0),
TEA6330T_BASS("Tone Control - Bass", 0),
TEA6330T_TREBLE("Tone Control - Treble", 0)
पूर्ण;

अटल व्योम snd_tea6330_मुक्त(काष्ठा snd_i2c_device *device)
अणु
	kमुक्त(device->निजी_data);
पूर्ण
                                        
पूर्णांक snd_tea6330t_update_mixer(काष्ठा snd_card *card,
			      काष्ठा snd_i2c_bus *bus,
			      पूर्णांक equalizer, पूर्णांक fader)
अणु
	काष्ठा snd_i2c_device *device;
	काष्ठा tea6330t *tea;
	स्थिर काष्ठा snd_kcontrol_new *knew;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err = -ENOMEM;
	u8 शेष_treble, शेष_bass;
	अचिन्हित अक्षर bytes[7];

	tea = kzalloc(माप(*tea), GFP_KERNEL);
	अगर (tea == शून्य)
		वापस -ENOMEM;
	अगर ((err = snd_i2c_device_create(bus, "TEA6330T", TEA6330T_ADDR, &device)) < 0) अणु
		kमुक्त(tea);
		वापस err;
	पूर्ण
	tea->device = device;
	tea->bus = bus;
	tea->equalizer = equalizer;
	tea->fader = fader;
	device->निजी_data = tea;
	device->निजी_मुक्त = snd_tea6330_मुक्त;

	snd_i2c_lock(bus);

	/* turn fader off and handle equalizer */
	tea->regs[TEA6330T_SADDR_FADER] = 0x3f;
	tea->regs[TEA6330T_SADDR_AUDIO_SWITCH] = equalizer ? 0 : TEA6330T_EQN;
	/* initialize mixer */
	अगर (!tea->equalizer) अणु
		tea->max_bass = 9;
		tea->max_treble = 8;
		शेष_bass = 3 + 4;
		tea->bass = 4;
		शेष_treble = 3 + 4;
		tea->treble = 4;
	पूर्ण अन्यथा अणु
		tea->max_bass = 5;
		tea->max_treble = 0;
		शेष_bass = 7 + 4;
		tea->bass = 4;
		शेष_treble = 3;
		tea->treble = 0;
	पूर्ण
	tea->mleft = tea->mright = 0x14;
	tea->regs[TEA6330T_SADDR_BASS] = शेष_bass;
	tea->regs[TEA6330T_SADDR_TREBLE] = शेष_treble;

	/* compose I2C message and put the hardware to initial state */
	bytes[0] = TEA6330T_SADDR_VOLUME_LEFT;
	क्रम (idx = 0; idx < 6; idx++)
		bytes[idx+1] = tea->regs[idx];
	अगर ((err = snd_i2c_sendbytes(device, bytes, 7)) < 0)
		जाओ __error;

	म_जोड़ो(card->mixername, ",TEA6330T");
	अगर ((err = snd_component_add(card, "TEA6330T")) < 0)
		जाओ __error;

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_tea6330t_controls); idx++) अणु
		knew = &snd_tea6330t_controls[idx];
		अगर (tea->treble == 0 && !म_भेद(knew->name, "Tone Control - Treble"))
			जारी;
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(knew, tea))) < 0)
			जाओ __error;
	पूर्ण

	snd_i2c_unlock(bus);
	वापस 0;
	
      __error:
      	snd_i2c_unlock(bus);
      	snd_i2c_device_मुक्त(device);
      	वापस err;
पूर्ण

EXPORT_SYMBOL(snd_tea6330t_detect);
EXPORT_SYMBOL(snd_tea6330t_update_mixer);
