<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   USB Audio Driver क्रम ALSA
 *
 *   Quirks and venकरोr-specअगरic extensions क्रम mixer पूर्णांकerfaces
 *
 *   Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 *
 *   Many codes borrowed from audio.c by
 *	    Alan Cox (alan@lxorguk.ukuu.org.uk)
 *	    Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *   Audio Advantage Micro II support added by:
 *	    Przemek Rudy (prudy1@o2.pl)
 */

#समावेश <linux/hid.h>
#समावेश <linux/init.h>
#समावेश <linux/math64.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>

#समावेश <sound/asoundef.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/info.h>
#समावेश <sound/tlv.h>

#समावेश "usbaudio.h"
#समावेश "mixer.h"
#समावेश "mixer_quirks.h"
#समावेश "mixer_scarlett.h"
#समावेश "mixer_scarlett_gen2.h"
#समावेश "mixer_us16x08.h"
#समावेश "mixer_s1810c.h"
#समावेश "helper.h"

काष्ठा std_mono_table अणु
	अचिन्हित पूर्णांक unitid, control, cmask;
	पूर्णांक val_type;
	स्थिर अक्षर *name;
	snd_kcontrol_tlv_rw_t *tlv_callback;
पूर्ण;

/* This function allows क्रम the creation of standard UAC controls.
 * See the quirks क्रम M-Audio FTUs or Ebox-44.
 * If you करोn't want to set a TLV callback pass शून्य.
 *
 * Since there करोesn't seem to be a devices that needs a multichannel
 * version, we keep it mono क्रम simplicity.
 */
अटल पूर्णांक snd_create_std_mono_ctl_offset(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				अचिन्हित पूर्णांक unitid,
				अचिन्हित पूर्णांक control,
				अचिन्हित पूर्णांक cmask,
				पूर्णांक val_type,
				अचिन्हित पूर्णांक idx_off,
				स्थिर अक्षर *name,
				snd_kcontrol_tlv_rw_t *tlv_callback)
अणु
	काष्ठा usb_mixer_elem_info *cval;
	काष्ठा snd_kcontrol *kctl;

	cval = kzalloc(माप(*cval), GFP_KERNEL);
	अगर (!cval)
		वापस -ENOMEM;

	snd_usb_mixer_elem_init_std(&cval->head, mixer, unitid);
	cval->val_type = val_type;
	cval->channels = 1;
	cval->control = control;
	cval->cmask = cmask;
	cval->idx_off = idx_off;

	/* get_min_max() is called only क्रम पूर्णांकeger volumes later,
	 * so provide a लघु-cut क्रम booleans */
	cval->min = 0;
	cval->max = 1;
	cval->res = 0;
	cval->dBmin = 0;
	cval->dBmax = 0;

	/* Create control */
	kctl = snd_ctl_new1(snd_usb_feature_unit_ctl, cval);
	अगर (!kctl) अणु
		kमुक्त(cval);
		वापस -ENOMEM;
	पूर्ण

	/* Set name */
	snम_लिखो(kctl->id.name, माप(kctl->id.name), name);
	kctl->निजी_मुक्त = snd_usb_mixer_elem_मुक्त;

	/* set TLV */
	अगर (tlv_callback) अणु
		kctl->tlv.c = tlv_callback;
		kctl->vd[0].access |=
			SNDRV_CTL_ELEM_ACCESS_TLV_READ |
			SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK;
	पूर्ण
	/* Add control to mixer */
	वापस snd_usb_mixer_add_control(&cval->head, kctl);
पूर्ण

अटल पूर्णांक snd_create_std_mono_ctl(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				अचिन्हित पूर्णांक unitid,
				अचिन्हित पूर्णांक control,
				अचिन्हित पूर्णांक cmask,
				पूर्णांक val_type,
				स्थिर अक्षर *name,
				snd_kcontrol_tlv_rw_t *tlv_callback)
अणु
	वापस snd_create_std_mono_ctl_offset(mixer, unitid, control, cmask,
		val_type, 0 /* Offset */, name, tlv_callback);
पूर्ण

/*
 * Create a set of standard UAC controls from a table
 */
अटल पूर्णांक snd_create_std_mono_table(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				     स्थिर काष्ठा std_mono_table *t)
अणु
	पूर्णांक err;

	जबतक (t->name != शून्य) अणु
		err = snd_create_std_mono_ctl(mixer, t->unitid, t->control,
				t->cmask, t->val_type, t->name, t->tlv_callback);
		अगर (err < 0)
			वापस err;
		t++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक add_single_ctl_with_resume(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				      पूर्णांक id,
				      usb_mixer_elem_resume_func_t resume,
				      स्थिर काष्ठा snd_kcontrol_new *knew,
				      काष्ठा usb_mixer_elem_list **listp)
अणु
	काष्ठा usb_mixer_elem_list *list;
	काष्ठा snd_kcontrol *kctl;

	list = kzalloc(माप(*list), GFP_KERNEL);
	अगर (!list)
		वापस -ENOMEM;
	अगर (listp)
		*listp = list;
	list->mixer = mixer;
	list->id = id;
	list->reset_resume = resume;
	kctl = snd_ctl_new1(knew, list);
	अगर (!kctl) अणु
		kमुक्त(list);
		वापस -ENOMEM;
	पूर्ण
	kctl->निजी_मुक्त = snd_usb_mixer_elem_मुक्त;
	/* करोn't use snd_usb_mixer_add_control() here, this is a special list element */
	वापस snd_usb_mixer_add_list(list, kctl, false);
पूर्ण

/*
 * Sound Blaster remote control configuration
 *
 * क्रमmat of remote control data:
 * Extigy:       xx 00
 * Audigy 2 NX:  06 80 xx 00 00 00
 * Live! 24-bit: 06 80 xx yy 22 83
 */
अटल स्थिर काष्ठा rc_config अणु
	u32 usb_id;
	u8  offset;
	u8  length;
	u8  packet_length;
	u8  min_packet_length; /* minimum accepted length of the URB result */
	u8  mute_mixer_id;
	u32 mute_code;
पूर्ण rc_configs[] = अणु
	अणु USB_ID(0x041e, 0x3000), 0, 1, 2, 1,  18, 0x0013 पूर्ण, /* Extigy       */
	अणु USB_ID(0x041e, 0x3020), 2, 1, 6, 6,  18, 0x0013 पूर्ण, /* Audigy 2 NX  */
	अणु USB_ID(0x041e, 0x3040), 2, 2, 6, 6,  2,  0x6e91 पूर्ण, /* Live! 24-bit */
	अणु USB_ID(0x041e, 0x3042), 0, 1, 1, 1,  1,  0x000d पूर्ण, /* Usb X-Fi S51 */
	अणु USB_ID(0x041e, 0x30df), 0, 1, 1, 1,  1,  0x000d पूर्ण, /* Usb X-Fi S51 Pro */
	अणु USB_ID(0x041e, 0x3237), 0, 1, 1, 1,  1,  0x000d पूर्ण, /* Usb X-Fi S51 Pro */
	अणु USB_ID(0x041e, 0x3263), 0, 1, 1, 1,  1,  0x000d पूर्ण, /* Usb X-Fi S51 Pro */
	अणु USB_ID(0x041e, 0x3048), 2, 2, 6, 6,  2,  0x6e91 पूर्ण, /* Toshiba SB0500 */
पूर्ण;

अटल व्योम snd_usb_soundblaster_remote_complete(काष्ठा urb *urb)
अणु
	काष्ठा usb_mixer_पूर्णांकerface *mixer = urb->context;
	स्थिर काष्ठा rc_config *rc = mixer->rc_cfg;
	u32 code;

	अगर (urb->status < 0 || urb->actual_length < rc->min_packet_length)
		वापस;

	code = mixer->rc_buffer[rc->offset];
	अगर (rc->length == 2)
		code |= mixer->rc_buffer[rc->offset + 1] << 8;

	/* the Mute button actually changes the mixer control */
	अगर (code == rc->mute_code)
		snd_usb_mixer_notअगरy_id(mixer, rc->mute_mixer_id);
	mixer->rc_code = code;
	wmb();
	wake_up(&mixer->rc_रुकोq);
पूर्ण

अटल दीर्घ snd_usb_sbrc_hwdep_पढ़ो(काष्ठा snd_hwdep *hw, अक्षर __user *buf,
				     दीर्घ count, loff_t *offset)
अणु
	काष्ठा usb_mixer_पूर्णांकerface *mixer = hw->निजी_data;
	पूर्णांक err;
	u32 rc_code;

	अगर (count != 1 && count != 4)
		वापस -EINVAL;
	err = रुको_event_पूर्णांकerruptible(mixer->rc_रुकोq,
				       (rc_code = xchg(&mixer->rc_code, 0)) != 0);
	अगर (err == 0) अणु
		अगर (count == 1)
			err = put_user(rc_code, buf);
		अन्यथा
			err = put_user(rc_code, (u32 __user *)buf);
	पूर्ण
	वापस err < 0 ? err : count;
पूर्ण

अटल __poll_t snd_usb_sbrc_hwdep_poll(काष्ठा snd_hwdep *hw, काष्ठा file *file,
					    poll_table *रुको)
अणु
	काष्ठा usb_mixer_पूर्णांकerface *mixer = hw->निजी_data;

	poll_रुको(file, &mixer->rc_रुकोq, रुको);
	वापस mixer->rc_code ? EPOLLIN | EPOLLRDNORM : 0;
पूर्ण

अटल पूर्णांक snd_usb_soundblaster_remote_init(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	काष्ठा snd_hwdep *hwdep;
	पूर्णांक err, len, i;

	क्रम (i = 0; i < ARRAY_SIZE(rc_configs); ++i)
		अगर (rc_configs[i].usb_id == mixer->chip->usb_id)
			अवरोध;
	अगर (i >= ARRAY_SIZE(rc_configs))
		वापस 0;
	mixer->rc_cfg = &rc_configs[i];

	len = mixer->rc_cfg->packet_length;

	init_रुकोqueue_head(&mixer->rc_रुकोq);
	err = snd_hwdep_new(mixer->chip->card, "SB remote control", 0, &hwdep);
	अगर (err < 0)
		वापस err;
	snम_लिखो(hwdep->name, माप(hwdep->name),
		 "%s remote control", mixer->chip->card->लघुname);
	hwdep->अगरace = SNDRV_HWDEP_IFACE_SB_RC;
	hwdep->निजी_data = mixer;
	hwdep->ops.पढ़ो = snd_usb_sbrc_hwdep_पढ़ो;
	hwdep->ops.poll = snd_usb_sbrc_hwdep_poll;
	hwdep->exclusive = 1;

	mixer->rc_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!mixer->rc_urb)
		वापस -ENOMEM;
	mixer->rc_setup_packet = kदो_स्मृति(माप(*mixer->rc_setup_packet), GFP_KERNEL);
	अगर (!mixer->rc_setup_packet) अणु
		usb_मुक्त_urb(mixer->rc_urb);
		mixer->rc_urb = शून्य;
		वापस -ENOMEM;
	पूर्ण
	mixer->rc_setup_packet->bRequestType =
		USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE;
	mixer->rc_setup_packet->bRequest = UAC_GET_MEM;
	mixer->rc_setup_packet->wValue = cpu_to_le16(0);
	mixer->rc_setup_packet->wIndex = cpu_to_le16(0);
	mixer->rc_setup_packet->wLength = cpu_to_le16(len);
	usb_fill_control_urb(mixer->rc_urb, mixer->chip->dev,
			     usb_rcvctrlpipe(mixer->chip->dev, 0),
			     (u8*)mixer->rc_setup_packet, mixer->rc_buffer, len,
			     snd_usb_soundblaster_remote_complete, mixer);
	वापस 0;
पूर्ण

#घोषणा snd_audigy2nx_led_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_audigy2nx_led_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = kcontrol->निजी_value >> 8;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_audigy2nx_led_update(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				    पूर्णांक value, पूर्णांक index)
अणु
	काष्ठा snd_usb_audio *chip = mixer->chip;
	पूर्णांक err;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;

	अगर (chip->usb_id == USB_ID(0x041e, 0x3042))
		err = snd_usb_ctl_msg(chip->dev,
			      usb_sndctrlpipe(chip->dev, 0), 0x24,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			      !value, 0, शून्य, 0);
	/* USB X-Fi S51 Pro */
	अगर (chip->usb_id == USB_ID(0x041e, 0x30df))
		err = snd_usb_ctl_msg(chip->dev,
			      usb_sndctrlpipe(chip->dev, 0), 0x24,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			      !value, 0, शून्य, 0);
	अन्यथा
		err = snd_usb_ctl_msg(chip->dev,
			      usb_sndctrlpipe(chip->dev, 0), 0x24,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			      value, index + 2, शून्य, 0);
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_audigy2nx_led_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	काष्ठा usb_mixer_पूर्णांकerface *mixer = list->mixer;
	पूर्णांक index = kcontrol->निजी_value & 0xff;
	अचिन्हित पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक old_value = kcontrol->निजी_value >> 8;
	पूर्णांक err;

	अगर (value > 1)
		वापस -EINVAL;
	अगर (value == old_value)
		वापस 0;
	kcontrol->निजी_value = (value << 8) | index;
	err = snd_audigy2nx_led_update(mixer, value, index);
	वापस err < 0 ? err : 1;
पूर्ण

अटल पूर्णांक snd_audigy2nx_led_resume(काष्ठा usb_mixer_elem_list *list)
अणु
	पूर्णांक priv_value = list->kctl->निजी_value;

	वापस snd_audigy2nx_led_update(list->mixer, priv_value >> 8,
					priv_value & 0xff);
पूर्ण

/* name and निजी_value are set dynamically */
अटल स्थिर काष्ठा snd_kcontrol_new snd_audigy2nx_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = snd_audigy2nx_led_info,
	.get = snd_audigy2nx_led_get,
	.put = snd_audigy2nx_led_put,
पूर्ण;

अटल स्थिर अक्षर * स्थिर snd_audigy2nx_led_names[] = अणु
	"CMSS LED Switch",
	"Power LED Switch",
	"Dolby Digital LED Switch",
पूर्ण;

अटल पूर्णांक snd_audigy2nx_controls_create(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < ARRAY_SIZE(snd_audigy2nx_led_names); ++i) अणु
		काष्ठा snd_kcontrol_new knew;

		/* USB X-Fi S51 करोesn't have a CMSS LED */
		अगर ((mixer->chip->usb_id == USB_ID(0x041e, 0x3042)) && i == 0)
			जारी;
		/* USB X-Fi S51 Pro करोesn't have one either */
		अगर ((mixer->chip->usb_id == USB_ID(0x041e, 0x30df)) && i == 0)
			जारी;
		अगर (i > 1 && /* Live24ext has 2 LEDs only */
			(mixer->chip->usb_id == USB_ID(0x041e, 0x3040) ||
			 mixer->chip->usb_id == USB_ID(0x041e, 0x3042) ||
			 mixer->chip->usb_id == USB_ID(0x041e, 0x30df) ||
			 mixer->chip->usb_id == USB_ID(0x041e, 0x3048)))
			अवरोध; 

		knew = snd_audigy2nx_control;
		knew.name = snd_audigy2nx_led_names[i];
		knew.निजी_value = (1 << 8) | i; /* LED on as शेष */
		err = add_single_ctl_with_resume(mixer, 0,
						 snd_audigy2nx_led_resume,
						 &knew, शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_audigy2nx_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				    काष्ठा snd_info_buffer *buffer)
अणु
	अटल स्थिर काष्ठा sb_jack अणु
		पूर्णांक unitid;
		स्थिर अक्षर *name;
	पूर्ण  jacks_audigy2nx[] = अणु
		अणु4,  "dig in "पूर्ण,
		अणु7,  "line in"पूर्ण,
		अणु19, "spk out"पूर्ण,
		अणु20, "hph out"पूर्ण,
		अणु-1, शून्यपूर्ण
	पूर्ण, jacks_live24ext[] = अणु
		अणु4,  "line in"पूर्ण, /* &1=Line, &2=Mic*/
		अणु3,  "hph out"पूर्ण, /* headphones */
		अणु0,  "RC     "पूर्ण, /* last command, 6 bytes see rc_config above */
		अणु-1, शून्यपूर्ण
	पूर्ण;
	स्थिर काष्ठा sb_jack *jacks;
	काष्ठा usb_mixer_पूर्णांकerface *mixer = entry->निजी_data;
	पूर्णांक i, err;
	u8 buf[3];

	snd_iम_लिखो(buffer, "%s jacks\n\n", mixer->chip->card->लघुname);
	अगर (mixer->chip->usb_id == USB_ID(0x041e, 0x3020))
		jacks = jacks_audigy2nx;
	अन्यथा अगर (mixer->chip->usb_id == USB_ID(0x041e, 0x3040) ||
		 mixer->chip->usb_id == USB_ID(0x041e, 0x3048))
		jacks = jacks_live24ext;
	अन्यथा
		वापस;

	क्रम (i = 0; jacks[i].name; ++i) अणु
		snd_iम_लिखो(buffer, "%s: ", jacks[i].name);
		err = snd_usb_lock_shutकरोwn(mixer->chip);
		अगर (err < 0)
			वापस;
		err = snd_usb_ctl_msg(mixer->chip->dev,
				      usb_rcvctrlpipe(mixer->chip->dev, 0),
				      UAC_GET_MEM, USB_सूची_IN | USB_TYPE_CLASS |
				      USB_RECIP_INTERFACE, 0,
				      jacks[i].unitid << 8, buf, 3);
		snd_usb_unlock_shutकरोwn(mixer->chip);
		अगर (err == 3 && (buf[0] == 3 || buf[0] == 6))
			snd_iम_लिखो(buffer, "%02x %02x\n", buf[1], buf[2]);
		अन्यथा
			snd_iम_लिखो(buffer, "?\n");
	पूर्ण
पूर्ण

/* EMU0204 */
अटल पूर्णांक snd_emu0204_ch_चयन_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु"1/2", "3/4"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, ARRAY_SIZE(texts), texts);
पूर्ण

अटल पूर्णांक snd_emu0204_ch_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = kcontrol->निजी_value;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu0204_ch_चयन_update(काष्ठा usb_mixer_पूर्णांकerface *mixer,
					पूर्णांक value)
अणु
	काष्ठा snd_usb_audio *chip = mixer->chip;
	पूर्णांक err;
	अचिन्हित अक्षर buf[2];

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;

	buf[0] = 0x01;
	buf[1] = value ? 0x02 : 0x01;
	err = snd_usb_ctl_msg(chip->dev,
		      usb_sndctrlpipe(chip->dev, 0), UAC_SET_CUR,
		      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_OUT,
		      0x0400, 0x0e00, buf, 2);
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_emu0204_ch_चयन_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	काष्ठा usb_mixer_पूर्णांकerface *mixer = list->mixer;
	अचिन्हित पूर्णांक value = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक err;

	अगर (value > 1)
		वापस -EINVAL;

	अगर (value == kcontrol->निजी_value)
		वापस 0;

	kcontrol->निजी_value = value;
	err = snd_emu0204_ch_चयन_update(mixer, value);
	वापस err < 0 ? err : 1;
पूर्ण

अटल पूर्णांक snd_emu0204_ch_चयन_resume(काष्ठा usb_mixer_elem_list *list)
अणु
	वापस snd_emu0204_ch_चयन_update(list->mixer,
					    list->kctl->निजी_value);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu0204_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Front Jack Channels",
	.info = snd_emu0204_ch_चयन_info,
	.get = snd_emu0204_ch_चयन_get,
	.put = snd_emu0204_ch_चयन_put,
	.निजी_value = 0,
पूर्ण;

अटल पूर्णांक snd_emu0204_controls_create(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	वापस add_single_ctl_with_resume(mixer, 0,
					  snd_emu0204_ch_चयन_resume,
					  &snd_emu0204_control, शून्य);
पूर्ण

/* ASUS Xonar U1 / U3 controls */

अटल पूर्णांक snd_xonar_u1_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = !!(kcontrol->निजी_value & 0x02);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_xonar_u1_चयन_update(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				      अचिन्हित अक्षर status)
अणु
	काष्ठा snd_usb_audio *chip = mixer->chip;
	पूर्णांक err;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;
	err = snd_usb_ctl_msg(chip->dev,
			      usb_sndctrlpipe(chip->dev, 0), 0x08,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			      50, 0, &status, 1);
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_xonar_u1_चयन_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	u8 old_status, new_status;
	पूर्णांक err;

	old_status = kcontrol->निजी_value;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		new_status = old_status | 0x02;
	अन्यथा
		new_status = old_status & ~0x02;
	अगर (new_status == old_status)
		वापस 0;

	kcontrol->निजी_value = new_status;
	err = snd_xonar_u1_चयन_update(list->mixer, new_status);
	वापस err < 0 ? err : 1;
पूर्ण

अटल पूर्णांक snd_xonar_u1_चयन_resume(काष्ठा usb_mixer_elem_list *list)
अणु
	वापस snd_xonar_u1_चयन_update(list->mixer,
					  list->kctl->निजी_value);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_xonar_u1_output_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Digital Playback Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = snd_xonar_u1_चयन_get,
	.put = snd_xonar_u1_चयन_put,
	.निजी_value = 0x05,
पूर्ण;

अटल पूर्णांक snd_xonar_u1_controls_create(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	वापस add_single_ctl_with_resume(mixer, 0,
					  snd_xonar_u1_चयन_resume,
					  &snd_xonar_u1_output_चयन, शून्य);
पूर्ण

/* Digidesign Mbox 1 घड़ी source चयन (पूर्णांकernal/spdअगर) */

अटल पूर्णांक snd_mbox1_चयन_get(काष्ठा snd_kcontrol *kctl,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = kctl->निजी_value;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mbox1_चयन_update(काष्ठा usb_mixer_पूर्णांकerface *mixer, पूर्णांक val)
अणु
	काष्ठा snd_usb_audio *chip = mixer->chip;
	पूर्णांक err;
	अचिन्हित अक्षर buff[3];

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;

	/* Prepare क्रम magic command to toggle घड़ी source */
	err = snd_usb_ctl_msg(chip->dev,
				usb_rcvctrlpipe(chip->dev, 0), 0x81,
				USB_सूची_IN |
				USB_TYPE_CLASS |
				USB_RECIP_INTERFACE, 0x00, 0x500, buff, 1);
	अगर (err < 0)
		जाओ err;
	err = snd_usb_ctl_msg(chip->dev,
				usb_rcvctrlpipe(chip->dev, 0), 0x81,
				USB_सूची_IN |
				USB_TYPE_CLASS |
				USB_RECIP_ENDPOINT, 0x100, 0x81, buff, 3);
	अगर (err < 0)
		जाओ err;

	/* 2 possibilities:	Internal    -> send sample rate
	 *			S/PDIF sync -> send zeroes
	 * NB: Sample rate locked to 48kHz on purpose to
	 *     prevent user from resetting the sample rate
	 *     जबतक S/PDIF sync is enabled and confusing
	 *     this configuration.
	 */
	अगर (val == 0) अणु
		buff[0] = 0x80;
		buff[1] = 0xbb;
		buff[2] = 0x00;
	पूर्ण अन्यथा अणु
		buff[0] = buff[1] = buff[2] = 0x00;
	पूर्ण

	/* Send the magic command to toggle the घड़ी source */
	err = snd_usb_ctl_msg(chip->dev,
				usb_sndctrlpipe(chip->dev, 0), 0x1,
				USB_TYPE_CLASS |
				USB_RECIP_ENDPOINT, 0x100, 0x81, buff, 3);
	अगर (err < 0)
		जाओ err;
	err = snd_usb_ctl_msg(chip->dev,
				usb_rcvctrlpipe(chip->dev, 0), 0x81,
				USB_सूची_IN |
				USB_TYPE_CLASS |
				USB_RECIP_ENDPOINT, 0x100, 0x81, buff, 3);
	अगर (err < 0)
		जाओ err;
	err = snd_usb_ctl_msg(chip->dev,
				usb_rcvctrlpipe(chip->dev, 0), 0x81,
				USB_सूची_IN |
				USB_TYPE_CLASS |
				USB_RECIP_ENDPOINT, 0x100, 0x2, buff, 3);
	अगर (err < 0)
		जाओ err;

err:
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_mbox1_चयन_put(काष्ठा snd_kcontrol *kctl,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kctl);
	काष्ठा usb_mixer_पूर्णांकerface *mixer = list->mixer;
	पूर्णांक err;
	bool cur_val, new_val;

	cur_val = kctl->निजी_value;
	new_val = ucontrol->value.क्रमागतerated.item[0];
	अगर (cur_val == new_val)
		वापस 0;

	kctl->निजी_value = new_val;
	err = snd_mbox1_चयन_update(mixer, new_val);
	वापस err < 0 ? err : 1;
पूर्ण

अटल पूर्णांक snd_mbox1_चयन_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[2] = अणु
		"Internal",
		"S/PDIF"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, ARRAY_SIZE(texts), texts);
पूर्ण

अटल पूर्णांक snd_mbox1_चयन_resume(काष्ठा usb_mixer_elem_list *list)
अणु
	वापस snd_mbox1_चयन_update(list->mixer, list->kctl->निजी_value);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_mbox1_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Clock Source",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = snd_mbox1_चयन_info,
	.get = snd_mbox1_चयन_get,
	.put = snd_mbox1_चयन_put,
	.निजी_value = 0
पूर्ण;

अटल पूर्णांक snd_mbox1_create_sync_चयन(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	वापस add_single_ctl_with_resume(mixer, 0,
					  snd_mbox1_चयन_resume,
					  &snd_mbox1_चयन, शून्य);
पूर्ण

/* Native Instruments device quirks */

#घोषणा _MAKE_NI_CONTROL(bRequest,wIndex) ((bRequest) << 16 | (wIndex))

अटल पूर्णांक snd_ni_control_init_val(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				   काष्ठा snd_kcontrol *kctl)
अणु
	काष्ठा usb_device *dev = mixer->chip->dev;
	अचिन्हित पूर्णांक pval = kctl->निजी_value;
	u8 value;
	पूर्णांक err;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0),
			      (pval >> 16) & 0xff,
			      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
			      0, pval & 0xffff, &value, 1);
	अगर (err < 0) अणु
		dev_err(&dev->dev,
			"unable to issue vendor read request (ret = %d)", err);
		वापस err;
	पूर्ण

	kctl->निजी_value |= ((अचिन्हित पूर्णांक)value << 24);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_nativeinstruments_control_get(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = kcontrol->निजी_value >> 24;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ni_update_cur_val(काष्ठा usb_mixer_elem_list *list)
अणु
	काष्ठा snd_usb_audio *chip = list->mixer->chip;
	अचिन्हित पूर्णांक pval = list->kctl->निजी_value;
	पूर्णांक err;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;
	err = usb_control_msg(chip->dev, usb_sndctrlpipe(chip->dev, 0),
			      (pval >> 16) & 0xff,
			      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
			      pval >> 24, pval & 0xffff, शून्य, 0, 1000);
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_nativeinstruments_control_put(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	u8 oldval = (kcontrol->निजी_value >> 24) & 0xff;
	u8 newval = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक err;

	अगर (oldval == newval)
		वापस 0;

	kcontrol->निजी_value &= ~(0xff << 24);
	kcontrol->निजी_value |= (अचिन्हित पूर्णांक)newval << 24;
	err = snd_ni_update_cur_val(list);
	वापस err < 0 ? err : 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_nativeinstruments_ta6_mixers[] = अणु
	अणु
		.name = "Direct Thru Channel A",
		.निजी_value = _MAKE_NI_CONTROL(0x01, 0x03),
	पूर्ण,
	अणु
		.name = "Direct Thru Channel B",
		.निजी_value = _MAKE_NI_CONTROL(0x01, 0x05),
	पूर्ण,
	अणु
		.name = "Phono Input Channel A",
		.निजी_value = _MAKE_NI_CONTROL(0x02, 0x03),
	पूर्ण,
	अणु
		.name = "Phono Input Channel B",
		.निजी_value = _MAKE_NI_CONTROL(0x02, 0x05),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_nativeinstruments_ta10_mixers[] = अणु
	अणु
		.name = "Direct Thru Channel A",
		.निजी_value = _MAKE_NI_CONTROL(0x01, 0x03),
	पूर्ण,
	अणु
		.name = "Direct Thru Channel B",
		.निजी_value = _MAKE_NI_CONTROL(0x01, 0x05),
	पूर्ण,
	अणु
		.name = "Direct Thru Channel C",
		.निजी_value = _MAKE_NI_CONTROL(0x01, 0x07),
	पूर्ण,
	अणु
		.name = "Direct Thru Channel D",
		.निजी_value = _MAKE_NI_CONTROL(0x01, 0x09),
	पूर्ण,
	अणु
		.name = "Phono Input Channel A",
		.निजी_value = _MAKE_NI_CONTROL(0x02, 0x03),
	पूर्ण,
	अणु
		.name = "Phono Input Channel B",
		.निजी_value = _MAKE_NI_CONTROL(0x02, 0x05),
	पूर्ण,
	अणु
		.name = "Phono Input Channel C",
		.निजी_value = _MAKE_NI_CONTROL(0x02, 0x07),
	पूर्ण,
	अणु
		.name = "Phono Input Channel D",
		.निजी_value = _MAKE_NI_CONTROL(0x02, 0x09),
	पूर्ण,
पूर्ण;

अटल पूर्णांक snd_nativeinstruments_create_mixer(काष्ठा usb_mixer_पूर्णांकerface *mixer,
					      स्थिर काष्ठा snd_kcontrol_new *kc,
					      अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i, err = 0;
	काष्ठा snd_kcontrol_new ढाँचा = अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.get = snd_nativeinstruments_control_get,
		.put = snd_nativeinstruments_control_put,
		.info = snd_ctl_boolean_mono_info,
	पूर्ण;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा usb_mixer_elem_list *list;

		ढाँचा.name = kc[i].name;
		ढाँचा.निजी_value = kc[i].निजी_value;

		err = add_single_ctl_with_resume(mixer, 0,
						 snd_ni_update_cur_val,
						 &ढाँचा, &list);
		अगर (err < 0)
			अवरोध;
		snd_ni_control_init_val(mixer, list->kctl);
	पूर्ण

	वापस err;
पूर्ण

/* M-Audio FastTrack Ultra quirks */
/* FTU Effect चयन (also used by C400/C600) */
अटल पूर्णांक snd_ftu_eff_चयन_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[8] = अणु
		"Room 1", "Room 2", "Room 3", "Hall 1",
		"Hall 2", "Plate", "Delay", "Echo"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, ARRAY_SIZE(texts), texts);
पूर्ण

अटल पूर्णांक snd_ftu_eff_चयन_init(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				   काष्ठा snd_kcontrol *kctl)
अणु
	काष्ठा usb_device *dev = mixer->chip->dev;
	अचिन्हित पूर्णांक pval = kctl->निजी_value;
	पूर्णांक err;
	अचिन्हित अक्षर value[2];

	value[0] = 0x00;
	value[1] = 0x00;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC_GET_CUR,
			      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_IN,
			      pval & 0xff00,
			      snd_usb_ctrl_पूर्णांकf(mixer->chip) | ((pval & 0xff) << 8),
			      value, 2);
	अगर (err < 0)
		वापस err;

	kctl->निजी_value |= (अचिन्हित पूर्णांक)value[0] << 24;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ftu_eff_चयन_get(काष्ठा snd_kcontrol *kctl,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = kctl->निजी_value >> 24;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ftu_eff_चयन_update(काष्ठा usb_mixer_elem_list *list)
अणु
	काष्ठा snd_usb_audio *chip = list->mixer->chip;
	अचिन्हित पूर्णांक pval = list->kctl->निजी_value;
	अचिन्हित अक्षर value[2];
	पूर्णांक err;

	value[0] = pval >> 24;
	value[1] = 0;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;
	err = snd_usb_ctl_msg(chip->dev,
			      usb_sndctrlpipe(chip->dev, 0),
			      UAC_SET_CUR,
			      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_OUT,
			      pval & 0xff00,
			      snd_usb_ctrl_पूर्णांकf(chip) | ((pval & 0xff) << 8),
			      value, 2);
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_ftu_eff_चयन_put(काष्ठा snd_kcontrol *kctl,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kctl);
	अचिन्हित पूर्णांक pval = list->kctl->निजी_value;
	पूर्णांक cur_val, err, new_val;

	cur_val = pval >> 24;
	new_val = ucontrol->value.क्रमागतerated.item[0];
	अगर (cur_val == new_val)
		वापस 0;

	kctl->निजी_value &= ~(0xff << 24);
	kctl->निजी_value |= new_val << 24;
	err = snd_ftu_eff_चयन_update(list);
	वापस err < 0 ? err : 1;
पूर्ण

अटल पूर्णांक snd_ftu_create_effect_चयन(काष्ठा usb_mixer_पूर्णांकerface *mixer,
	पूर्णांक validx, पूर्णांक bUnitID)
अणु
	अटल काष्ठा snd_kcontrol_new ढाँचा = अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Effect Program Switch",
		.index = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = snd_ftu_eff_चयन_info,
		.get = snd_ftu_eff_चयन_get,
		.put = snd_ftu_eff_चयन_put
	पूर्ण;
	काष्ठा usb_mixer_elem_list *list;
	पूर्णांक err;

	err = add_single_ctl_with_resume(mixer, bUnitID,
					 snd_ftu_eff_चयन_update,
					 &ढाँचा, &list);
	अगर (err < 0)
		वापस err;
	list->kctl->निजी_value = (validx << 8) | bUnitID;
	snd_ftu_eff_चयन_init(mixer, list->kctl);
	वापस 0;
पूर्ण

/* Create volume controls क्रम FTU devices*/
अटल पूर्णांक snd_ftu_create_volume_ctls(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अक्षर name[64];
	अचिन्हित पूर्णांक control, cmask;
	पूर्णांक in, out, err;

	स्थिर अचिन्हित पूर्णांक id = 5;
	स्थिर पूर्णांक val_type = USB_MIXER_S16;

	क्रम (out = 0; out < 8; out++) अणु
		control = out + 1;
		क्रम (in = 0; in < 8; in++) अणु
			cmask = 1 << in;
			snम_लिखो(name, माप(name),
				"AIn%d - Out%d Capture Volume",
				in  + 1, out + 1);
			err = snd_create_std_mono_ctl(mixer, id, control,
							cmask, val_type, name,
							&snd_usb_mixer_vol_tlv);
			अगर (err < 0)
				वापस err;
		पूर्ण
		क्रम (in = 8; in < 16; in++) अणु
			cmask = 1 << in;
			snम_लिखो(name, माप(name),
				"DIn%d - Out%d Playback Volume",
				in - 7, out + 1);
			err = snd_create_std_mono_ctl(mixer, id, control,
							cmask, val_type, name,
							&snd_usb_mixer_vol_tlv);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* This control needs a volume quirk, see mixer.c */
अटल पूर्णांक snd_ftu_create_effect_volume_ctl(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अटल स्थिर अक्षर name[] = "Effect Volume";
	स्थिर अचिन्हित पूर्णांक id = 6;
	स्थिर पूर्णांक val_type = USB_MIXER_U8;
	स्थिर अचिन्हित पूर्णांक control = 2;
	स्थिर अचिन्हित पूर्णांक cmask = 0;

	वापस snd_create_std_mono_ctl(mixer, id, control, cmask, val_type,
					name, snd_usb_mixer_vol_tlv);
पूर्ण

/* This control needs a volume quirk, see mixer.c */
अटल पूर्णांक snd_ftu_create_effect_duration_ctl(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अटल स्थिर अक्षर name[] = "Effect Duration";
	स्थिर अचिन्हित पूर्णांक id = 6;
	स्थिर पूर्णांक val_type = USB_MIXER_S16;
	स्थिर अचिन्हित पूर्णांक control = 3;
	स्थिर अचिन्हित पूर्णांक cmask = 0;

	वापस snd_create_std_mono_ctl(mixer, id, control, cmask, val_type,
					name, snd_usb_mixer_vol_tlv);
पूर्ण

/* This control needs a volume quirk, see mixer.c */
अटल पूर्णांक snd_ftu_create_effect_feedback_ctl(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अटल स्थिर अक्षर name[] = "Effect Feedback Volume";
	स्थिर अचिन्हित पूर्णांक id = 6;
	स्थिर पूर्णांक val_type = USB_MIXER_U8;
	स्थिर अचिन्हित पूर्णांक control = 4;
	स्थिर अचिन्हित पूर्णांक cmask = 0;

	वापस snd_create_std_mono_ctl(mixer, id, control, cmask, val_type,
					name, शून्य);
पूर्ण

अटल पूर्णांक snd_ftu_create_effect_वापस_ctls(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अचिन्हित पूर्णांक cmask;
	पूर्णांक err, ch;
	अक्षर name[48];

	स्थिर अचिन्हित पूर्णांक id = 7;
	स्थिर पूर्णांक val_type = USB_MIXER_S16;
	स्थिर अचिन्हित पूर्णांक control = 7;

	क्रम (ch = 0; ch < 4; ++ch) अणु
		cmask = 1 << ch;
		snम_लिखो(name, माप(name),
			"Effect Return %d Volume", ch + 1);
		err = snd_create_std_mono_ctl(mixer, id, control,
						cmask, val_type, name,
						snd_usb_mixer_vol_tlv);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ftu_create_effect_send_ctls(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अचिन्हित पूर्णांक  cmask;
	पूर्णांक err, ch;
	अक्षर name[48];

	स्थिर अचिन्हित पूर्णांक id = 5;
	स्थिर पूर्णांक val_type = USB_MIXER_S16;
	स्थिर अचिन्हित पूर्णांक control = 9;

	क्रम (ch = 0; ch < 8; ++ch) अणु
		cmask = 1 << ch;
		snम_लिखो(name, माप(name),
			"Effect Send AIn%d Volume", ch + 1);
		err = snd_create_std_mono_ctl(mixer, id, control, cmask,
						val_type, name,
						snd_usb_mixer_vol_tlv);
		अगर (err < 0)
			वापस err;
	पूर्ण
	क्रम (ch = 8; ch < 16; ++ch) अणु
		cmask = 1 << ch;
		snम_लिखो(name, माप(name),
			"Effect Send DIn%d Volume", ch - 7);
		err = snd_create_std_mono_ctl(mixer, id, control, cmask,
						val_type, name,
						snd_usb_mixer_vol_tlv);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ftu_create_mixer(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	पूर्णांक err;

	err = snd_ftu_create_volume_ctls(mixer);
	अगर (err < 0)
		वापस err;

	err = snd_ftu_create_effect_चयन(mixer, 1, 6);
	अगर (err < 0)
		वापस err;

	err = snd_ftu_create_effect_volume_ctl(mixer);
	अगर (err < 0)
		वापस err;

	err = snd_ftu_create_effect_duration_ctl(mixer);
	अगर (err < 0)
		वापस err;

	err = snd_ftu_create_effect_feedback_ctl(mixer);
	अगर (err < 0)
		वापस err;

	err = snd_ftu_create_effect_वापस_ctls(mixer);
	अगर (err < 0)
		वापस err;

	err = snd_ftu_create_effect_send_ctls(mixer);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

व्योम snd_emuusb_set_samplerate(काष्ठा snd_usb_audio *chip,
			       अचिन्हित अक्षर samplerate_id)
अणु
	काष्ठा usb_mixer_पूर्णांकerface *mixer;
	काष्ठा usb_mixer_elem_info *cval;
	पूर्णांक unitid = 12; /* SampleRate ExtensionUnit ID */

	list_क्रम_each_entry(mixer, &chip->mixer_list, list) अणु
		अगर (mixer->id_elems[unitid]) अणु
			cval = mixer_elem_list_to_info(mixer->id_elems[unitid]);
			snd_usb_mixer_set_ctl_value(cval, UAC_SET_CUR,
						    cval->control << 8,
						    samplerate_id);
			snd_usb_mixer_notअगरy_id(mixer, unitid);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* M-Audio Fast Track C400/C600 */
/* C400/C600 volume controls, this control needs a volume quirk, see mixer.c */
अटल पूर्णांक snd_c400_create_vol_ctls(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अक्षर name[64];
	अचिन्हित पूर्णांक cmask, offset;
	पूर्णांक out, chan, err;
	पूर्णांक num_outs = 0;
	पूर्णांक num_ins = 0;

	स्थिर अचिन्हित पूर्णांक id = 0x40;
	स्थिर पूर्णांक val_type = USB_MIXER_S16;
	स्थिर पूर्णांक control = 1;

	चयन (mixer->chip->usb_id) अणु
	हाल USB_ID(0x0763, 0x2030):
		num_outs = 6;
		num_ins = 4;
		अवरोध;
	हाल USB_ID(0x0763, 0x2031):
		num_outs = 8;
		num_ins = 6;
		अवरोध;
	पूर्ण

	क्रम (chan = 0; chan < num_outs + num_ins; chan++) अणु
		क्रम (out = 0; out < num_outs; out++) अणु
			अगर (chan < num_outs) अणु
				snम_लिखो(name, माप(name),
					"PCM%d-Out%d Playback Volume",
					chan + 1, out + 1);
			पूर्ण अन्यथा अणु
				snम_लिखो(name, माप(name),
					"In%d-Out%d Playback Volume",
					chan - num_outs + 1, out + 1);
			पूर्ण

			cmask = (out == 0) ? 0 : 1 << (out - 1);
			offset = chan * num_outs;
			err = snd_create_std_mono_ctl_offset(mixer, id, control,
						cmask, val_type, offset, name,
						&snd_usb_mixer_vol_tlv);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* This control needs a volume quirk, see mixer.c */
अटल पूर्णांक snd_c400_create_effect_volume_ctl(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अटल स्थिर अक्षर name[] = "Effect Volume";
	स्थिर अचिन्हित पूर्णांक id = 0x43;
	स्थिर पूर्णांक val_type = USB_MIXER_U8;
	स्थिर अचिन्हित पूर्णांक control = 3;
	स्थिर अचिन्हित पूर्णांक cmask = 0;

	वापस snd_create_std_mono_ctl(mixer, id, control, cmask, val_type,
					name, snd_usb_mixer_vol_tlv);
पूर्ण

/* This control needs a volume quirk, see mixer.c */
अटल पूर्णांक snd_c400_create_effect_duration_ctl(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अटल स्थिर अक्षर name[] = "Effect Duration";
	स्थिर अचिन्हित पूर्णांक id = 0x43;
	स्थिर पूर्णांक val_type = USB_MIXER_S16;
	स्थिर अचिन्हित पूर्णांक control = 4;
	स्थिर अचिन्हित पूर्णांक cmask = 0;

	वापस snd_create_std_mono_ctl(mixer, id, control, cmask, val_type,
					name, snd_usb_mixer_vol_tlv);
पूर्ण

/* This control needs a volume quirk, see mixer.c */
अटल पूर्णांक snd_c400_create_effect_feedback_ctl(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अटल स्थिर अक्षर name[] = "Effect Feedback Volume";
	स्थिर अचिन्हित पूर्णांक id = 0x43;
	स्थिर पूर्णांक val_type = USB_MIXER_U8;
	स्थिर अचिन्हित पूर्णांक control = 5;
	स्थिर अचिन्हित पूर्णांक cmask = 0;

	वापस snd_create_std_mono_ctl(mixer, id, control, cmask, val_type,
					name, शून्य);
पूर्ण

अटल पूर्णांक snd_c400_create_effect_vol_ctls(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अक्षर name[64];
	अचिन्हित पूर्णांक cmask;
	पूर्णांक chan, err;
	पूर्णांक num_outs = 0;
	पूर्णांक num_ins = 0;

	स्थिर अचिन्हित पूर्णांक id = 0x42;
	स्थिर पूर्णांक val_type = USB_MIXER_S16;
	स्थिर पूर्णांक control = 1;

	चयन (mixer->chip->usb_id) अणु
	हाल USB_ID(0x0763, 0x2030):
		num_outs = 6;
		num_ins = 4;
		अवरोध;
	हाल USB_ID(0x0763, 0x2031):
		num_outs = 8;
		num_ins = 6;
		अवरोध;
	पूर्ण

	क्रम (chan = 0; chan < num_outs + num_ins; chan++) अणु
		अगर (chan < num_outs) अणु
			snम_लिखो(name, माप(name),
				"Effect Send DOut%d",
				chan + 1);
		पूर्ण अन्यथा अणु
			snम_लिखो(name, माप(name),
				"Effect Send AIn%d",
				chan - num_outs + 1);
		पूर्ण

		cmask = (chan == 0) ? 0 : 1 << (chan - 1);
		err = snd_create_std_mono_ctl(mixer, id, control,
						cmask, val_type, name,
						&snd_usb_mixer_vol_tlv);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_c400_create_effect_ret_vol_ctls(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अक्षर name[64];
	अचिन्हित पूर्णांक cmask;
	पूर्णांक chan, err;
	पूर्णांक num_outs = 0;
	पूर्णांक offset = 0;

	स्थिर अचिन्हित पूर्णांक id = 0x40;
	स्थिर पूर्णांक val_type = USB_MIXER_S16;
	स्थिर पूर्णांक control = 1;

	चयन (mixer->chip->usb_id) अणु
	हाल USB_ID(0x0763, 0x2030):
		num_outs = 6;
		offset = 0x3c;
		/* अणु 0x3c, 0x43, 0x3e, 0x45, 0x40, 0x47 पूर्ण */
		अवरोध;
	हाल USB_ID(0x0763, 0x2031):
		num_outs = 8;
		offset = 0x70;
		/* अणु 0x70, 0x79, 0x72, 0x7b, 0x74, 0x7d, 0x76, 0x7f पूर्ण */
		अवरोध;
	पूर्ण

	क्रम (chan = 0; chan < num_outs; chan++) अणु
		snम_लिखो(name, माप(name),
			"Effect Return %d",
			chan + 1);

		cmask = (chan == 0) ? 0 :
			1 << (chan + (chan % 2) * num_outs - 1);
		err = snd_create_std_mono_ctl_offset(mixer, id, control,
						cmask, val_type, offset, name,
						&snd_usb_mixer_vol_tlv);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_c400_create_mixer(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	पूर्णांक err;

	err = snd_c400_create_vol_ctls(mixer);
	अगर (err < 0)
		वापस err;

	err = snd_c400_create_effect_vol_ctls(mixer);
	अगर (err < 0)
		वापस err;

	err = snd_c400_create_effect_ret_vol_ctls(mixer);
	अगर (err < 0)
		वापस err;

	err = snd_ftu_create_effect_चयन(mixer, 2, 0x43);
	अगर (err < 0)
		वापस err;

	err = snd_c400_create_effect_volume_ctl(mixer);
	अगर (err < 0)
		वापस err;

	err = snd_c400_create_effect_duration_ctl(mixer);
	अगर (err < 0)
		वापस err;

	err = snd_c400_create_effect_feedback_ctl(mixer);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/*
 * The mixer units क्रम Ebox-44 are corrupt, and even where they
 * are valid they presents mono controls as L and R channels of
 * stereo. So we provide a good mixer here.
 */
अटल स्थिर काष्ठा std_mono_table ebox44_table[] = अणु
	अणु
		.unitid = 4,
		.control = 1,
		.cmask = 0x0,
		.val_type = USB_MIXER_INV_BOOLEAN,
		.name = "Headphone Playback Switch"
	पूर्ण,
	अणु
		.unitid = 4,
		.control = 2,
		.cmask = 0x1,
		.val_type = USB_MIXER_S16,
		.name = "Headphone A Mix Playback Volume"
	पूर्ण,
	अणु
		.unitid = 4,
		.control = 2,
		.cmask = 0x2,
		.val_type = USB_MIXER_S16,
		.name = "Headphone B Mix Playback Volume"
	पूर्ण,

	अणु
		.unitid = 7,
		.control = 1,
		.cmask = 0x0,
		.val_type = USB_MIXER_INV_BOOLEAN,
		.name = "Output Playback Switch"
	पूर्ण,
	अणु
		.unitid = 7,
		.control = 2,
		.cmask = 0x1,
		.val_type = USB_MIXER_S16,
		.name = "Output A Playback Volume"
	पूर्ण,
	अणु
		.unitid = 7,
		.control = 2,
		.cmask = 0x2,
		.val_type = USB_MIXER_S16,
		.name = "Output B Playback Volume"
	पूर्ण,

	अणु
		.unitid = 10,
		.control = 1,
		.cmask = 0x0,
		.val_type = USB_MIXER_INV_BOOLEAN,
		.name = "Input Capture Switch"
	पूर्ण,
	अणु
		.unitid = 10,
		.control = 2,
		.cmask = 0x1,
		.val_type = USB_MIXER_S16,
		.name = "Input A Capture Volume"
	पूर्ण,
	अणु
		.unitid = 10,
		.control = 2,
		.cmask = 0x2,
		.val_type = USB_MIXER_S16,
		.name = "Input B Capture Volume"
	पूर्ण,

	अणुपूर्ण
पूर्ण;

/* Audio Advantage Micro II findings:
 *
 * Mapping spdअगर AES bits to venकरोr रेजिस्टर.bit:
 * AES0: [0 0 0 0 2.3 2.2 2.1 2.0] - शेष 0x00
 * AES1: [3.3 3.2.3.1.3.0 2.7 2.6 2.5 2.4] - शेष: 0x01
 * AES2: [0 0 0 0 0 0 0 0]
 * AES3: [0 0 0 0 0 0 x 0] - 'x' bit is set basing on standard usb request
 *                           (UAC_EP_CS_ATTR_SAMPLE_RATE) क्रम Audio Devices
 *
 * घातer on values:
 * r2: 0x10
 * r3: 0x20 (b7 is zeroed just beक्रमe playback (except IEC61937) and set
 *           just after it to 0xa0, presumably it disables/mutes some analog
 *           parts when there is no audio.)
 * r9: 0x28
 *
 * Optical transmitter on/off:
 * venकरोr रेजिस्टर.bit: 9.1
 * 0 - on (0x28 रेजिस्टर value)
 * 1 - off (0x2a रेजिस्टर value)
 *
 */
अटल पूर्णांक snd_microii_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_microii_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_usb_audio *chip = list->mixer->chip;
	पूर्णांक err;
	काष्ठा usb_पूर्णांकerface *अगरace;
	काष्ठा usb_host_पूर्णांकerface *alts;
	अचिन्हित पूर्णांक ep;
	अचिन्हित अक्षर data[3];
	पूर्णांक rate;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;

	ucontrol->value.iec958.status[0] = kcontrol->निजी_value & 0xff;
	ucontrol->value.iec958.status[1] = (kcontrol->निजी_value >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = 0x00;

	/* use known values क्रम that card: पूर्णांकerface#1 altsetting#1 */
	अगरace = usb_अगरnum_to_अगर(chip->dev, 1);
	अगर (!अगरace || अगरace->num_altsetting < 2) अणु
		err = -EINVAL;
		जाओ end;
	पूर्ण
	alts = &अगरace->altsetting[1];
	अगर (get_अगरace_desc(alts)->bNumEndpoपूर्णांकs < 1) अणु
		err = -EINVAL;
		जाओ end;
	पूर्ण
	ep = get_endpoपूर्णांक(alts, 0)->bEndpoपूर्णांकAddress;

	err = snd_usb_ctl_msg(chip->dev,
			usb_rcvctrlpipe(chip->dev, 0),
			UAC_GET_CUR,
			USB_TYPE_CLASS | USB_RECIP_ENDPOINT | USB_सूची_IN,
			UAC_EP_CS_ATTR_SAMPLE_RATE << 8,
			ep,
			data,
			माप(data));
	अगर (err < 0)
		जाओ end;

	rate = data[0] | (data[1] << 8) | (data[2] << 16);
	ucontrol->value.iec958.status[3] = (rate == 48000) ?
			IEC958_AES3_CON_FS_48000 : IEC958_AES3_CON_FS_44100;

	err = 0;
 end:
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_microii_spdअगर_शेष_update(काष्ठा usb_mixer_elem_list *list)
अणु
	काष्ठा snd_usb_audio *chip = list->mixer->chip;
	अचिन्हित पूर्णांक pval = list->kctl->निजी_value;
	u8 reg;
	पूर्णांक err;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;

	reg = ((pval >> 4) & 0xf0) | (pval & 0x0f);
	err = snd_usb_ctl_msg(chip->dev,
			usb_sndctrlpipe(chip->dev, 0),
			UAC_SET_CUR,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			reg,
			2,
			शून्य,
			0);
	अगर (err < 0)
		जाओ end;

	reg = (pval & IEC958_AES0_NONAUDIO) ? 0xa0 : 0x20;
	reg |= (pval >> 12) & 0x0f;
	err = snd_usb_ctl_msg(chip->dev,
			usb_sndctrlpipe(chip->dev, 0),
			UAC_SET_CUR,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			reg,
			3,
			शून्य,
			0);
	अगर (err < 0)
		जाओ end;

 end:
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_microii_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक pval, pval_old;
	पूर्णांक err;

	pval = pval_old = kcontrol->निजी_value;
	pval &= 0xfffff0f0;
	pval |= (ucontrol->value.iec958.status[1] & 0x0f) << 8;
	pval |= (ucontrol->value.iec958.status[0] & 0x0f);

	pval &= 0xffff0fff;
	pval |= (ucontrol->value.iec958.status[1] & 0xf0) << 8;

	/* The frequency bits in AES3 cannot be set via रेजिस्टर access. */

	/* Silently ignore any bits from the request that cannot be set. */

	अगर (pval == pval_old)
		वापस 0;

	kcontrol->निजी_value = pval;
	err = snd_microii_spdअगर_शेष_update(list);
	वापस err < 0 ? err : 1;
पूर्ण

अटल पूर्णांक snd_microii_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0x0f;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0x00;
	ucontrol->value.iec958.status[3] = 0x00;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_microii_spdअगर_चयन_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = !(kcontrol->निजी_value & 0x02);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_microii_spdअगर_चयन_update(काष्ठा usb_mixer_elem_list *list)
अणु
	काष्ठा snd_usb_audio *chip = list->mixer->chip;
	u8 reg = list->kctl->निजी_value;
	पूर्णांक err;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;

	err = snd_usb_ctl_msg(chip->dev,
			usb_sndctrlpipe(chip->dev, 0),
			UAC_SET_CUR,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			reg,
			9,
			शून्य,
			0);

	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_microii_spdअगर_चयन_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	u8 reg;
	पूर्णांक err;

	reg = ucontrol->value.पूर्णांकeger.value[0] ? 0x28 : 0x2a;
	अगर (reg != list->kctl->निजी_value)
		वापस 0;

	kcontrol->निजी_value = reg;
	err = snd_microii_spdअगर_चयन_update(list);
	वापस err < 0 ? err : 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_microii_mixer_spdअगर[] = अणु
	अणु
		.अगरace =    SNDRV_CTL_ELEM_IFACE_PCM,
		.name =     SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.info =     snd_microii_spdअगर_info,
		.get =      snd_microii_spdअगर_शेष_get,
		.put =      snd_microii_spdअगर_शेष_put,
		.निजी_value = 0x00000100UL,/* reset value */
	पूर्ण,
	अणु
		.access =   SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace =    SNDRV_CTL_ELEM_IFACE_PCM,
		.name =     SNDRV_CTL_NAME_IEC958("", PLAYBACK, MASK),
		.info =     snd_microii_spdअगर_info,
		.get =      snd_microii_spdअगर_mask_get,
	पूर्ण,
	अणु
		.अगरace =    SNDRV_CTL_ELEM_IFACE_MIXER,
		.name =     SNDRV_CTL_NAME_IEC958("", PLAYBACK, SWITCH),
		.info =     snd_ctl_boolean_mono_info,
		.get =      snd_microii_spdअगर_चयन_get,
		.put =      snd_microii_spdअगर_चयन_put,
		.निजी_value = 0x00000028UL,/* reset value */
	पूर्ण
पूर्ण;

अटल पूर्णांक snd_microii_controls_create(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	पूर्णांक err, i;
	अटल स्थिर usb_mixer_elem_resume_func_t resume_funcs[] = अणु
		snd_microii_spdअगर_शेष_update,
		शून्य,
		snd_microii_spdअगर_चयन_update
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(snd_microii_mixer_spdअगर); ++i) अणु
		err = add_single_ctl_with_resume(mixer, 0,
						 resume_funcs[i],
						 &snd_microii_mixer_spdअगर[i],
						 शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Creative Sound Blaster E1 */

अटल पूर्णांक snd_soundblaster_e1_चयन_get(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = kcontrol->निजी_value;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_soundblaster_e1_चयन_update(काष्ठा usb_mixer_पूर्णांकerface *mixer,
					     अचिन्हित अक्षर state)
अणु
	काष्ठा snd_usb_audio *chip = mixer->chip;
	पूर्णांक err;
	अचिन्हित अक्षर buff[2];

	buff[0] = 0x02;
	buff[1] = state ? 0x02 : 0x00;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;
	err = snd_usb_ctl_msg(chip->dev,
			usb_sndctrlpipe(chip->dev, 0), HID_REQ_SET_REPORT,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_OUT,
			0x0202, 3, buff, 2);
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_soundblaster_e1_चयन_put(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर value = !!ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक err;

	अगर (kcontrol->निजी_value == value)
		वापस 0;
	kcontrol->निजी_value = value;
	err = snd_soundblaster_e1_चयन_update(list->mixer, value);
	वापस err < 0 ? err : 1;
पूर्ण

अटल पूर्णांक snd_soundblaster_e1_चयन_resume(काष्ठा usb_mixer_elem_list *list)
अणु
	वापस snd_soundblaster_e1_चयन_update(list->mixer,
						 list->kctl->निजी_value);
पूर्ण

अटल पूर्णांक snd_soundblaster_e1_चयन_info(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[2] = अणु
		"Mic", "Aux"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, ARRAY_SIZE(texts), texts);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_soundblaster_e1_input_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Input Source",
	.info = snd_soundblaster_e1_चयन_info,
	.get = snd_soundblaster_e1_चयन_get,
	.put = snd_soundblaster_e1_चयन_put,
	.निजी_value = 0,
पूर्ण;

अटल पूर्णांक snd_soundblaster_e1_चयन_create(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	वापस add_single_ctl_with_resume(mixer, 0,
					  snd_soundblaster_e1_चयन_resume,
					  &snd_soundblaster_e1_input_चयन,
					  शून्य);
पूर्ण

अटल व्योम dell_करोck_init_vol(काष्ठा snd_usb_audio *chip, पूर्णांक ch, पूर्णांक id)
अणु
	u16 buf = 0;

	snd_usb_ctl_msg(chip->dev, usb_sndctrlpipe(chip->dev, 0), UAC_SET_CUR,
			USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_OUT,
			ch, snd_usb_ctrl_पूर्णांकf(chip) | (id << 8),
			&buf, 2);
पूर्ण

अटल पूर्णांक dell_करोck_mixer_init(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	/* fix to 0dB playback volumes */
	dell_करोck_init_vol(mixer->chip, 1, 16);
	dell_करोck_init_vol(mixer->chip, 2, 16);
	dell_करोck_init_vol(mixer->chip, 1, 19);
	dell_करोck_init_vol(mixer->chip, 2, 19);
	वापस 0;
पूर्ण

/* RME Class Compliant device quirks */

#घोषणा SND_RME_GET_STATUS1			23
#घोषणा SND_RME_GET_CURRENT_FREQ		17
#घोषणा SND_RME_CLK_SYSTEM_SHIFT		16
#घोषणा SND_RME_CLK_SYSTEM_MASK			0x1f
#घोषणा SND_RME_CLK_AES_SHIFT			8
#घोषणा SND_RME_CLK_SPDIF_SHIFT			12
#घोषणा SND_RME_CLK_AES_SPDIF_MASK		0xf
#घोषणा SND_RME_CLK_SYNC_SHIFT			6
#घोषणा SND_RME_CLK_SYNC_MASK			0x3
#घोषणा SND_RME_CLK_FREQMUL_SHIFT		18
#घोषणा SND_RME_CLK_FREQMUL_MASK		0x7
#घोषणा SND_RME_CLK_SYSTEM(x) \
	((x >> SND_RME_CLK_SYSTEM_SHIFT) & SND_RME_CLK_SYSTEM_MASK)
#घोषणा SND_RME_CLK_AES(x) \
	((x >> SND_RME_CLK_AES_SHIFT) & SND_RME_CLK_AES_SPDIF_MASK)
#घोषणा SND_RME_CLK_SPDIF(x) \
	((x >> SND_RME_CLK_SPDIF_SHIFT) & SND_RME_CLK_AES_SPDIF_MASK)
#घोषणा SND_RME_CLK_SYNC(x) \
	((x >> SND_RME_CLK_SYNC_SHIFT) & SND_RME_CLK_SYNC_MASK)
#घोषणा SND_RME_CLK_FREQMUL(x) \
	((x >> SND_RME_CLK_FREQMUL_SHIFT) & SND_RME_CLK_FREQMUL_MASK)
#घोषणा SND_RME_CLK_AES_LOCK			0x1
#घोषणा SND_RME_CLK_AES_SYNC			0x4
#घोषणा SND_RME_CLK_SPDIF_LOCK			0x2
#घोषणा SND_RME_CLK_SPDIF_SYNC			0x8
#घोषणा SND_RME_SPDIF_IF_SHIFT			4
#घोषणा SND_RME_SPDIF_FORMAT_SHIFT		5
#घोषणा SND_RME_BINARY_MASK			0x1
#घोषणा SND_RME_SPDIF_IF(x) \
	((x >> SND_RME_SPDIF_IF_SHIFT) & SND_RME_BINARY_MASK)
#घोषणा SND_RME_SPDIF_FORMAT(x) \
	((x >> SND_RME_SPDIF_FORMAT_SHIFT) & SND_RME_BINARY_MASK)

अटल स्थिर u32 snd_rme_rate_table[] = अणु
	32000, 44100, 48000, 50000,
	64000, 88200, 96000, 100000,
	128000, 176400, 192000, 200000,
	256000,	352800, 384000, 400000,
	512000, 705600, 768000, 800000
पूर्ण;
/* maximum number of items क्रम AES and S/PDIF rates क्रम above table */
#घोषणा SND_RME_RATE_IDX_AES_SPDIF_NUM		12

क्रमागत snd_rme_करोमुख्य अणु
	SND_RME_DOMAIN_SYSTEM,
	SND_RME_DOMAIN_AES,
	SND_RME_DOMAIN_SPDIF
पूर्ण;

क्रमागत snd_rme_घड़ी_status अणु
	SND_RME_CLOCK_NOLOCK,
	SND_RME_CLOCK_LOCK,
	SND_RME_CLOCK_SYNC
पूर्ण;

अटल पूर्णांक snd_rme_पढ़ो_value(काष्ठा snd_usb_audio *chip,
			      अचिन्हित पूर्णांक item,
			      u32 *value)
अणु
	काष्ठा usb_device *dev = chip->dev;
	पूर्णांक err;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0),
			      item,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0, 0,
			      value, माप(*value));
	अगर (err < 0)
		dev_err(&dev->dev,
			"unable to issue vendor read request %d (ret = %d)",
			item, err);
	वापस err;
पूर्ण

अटल पूर्णांक snd_rme_get_status1(काष्ठा snd_kcontrol *kcontrol,
			       u32 *status1)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_usb_audio *chip = list->mixer->chip;
	पूर्णांक err;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;
	err = snd_rme_पढ़ो_value(chip, SND_RME_GET_STATUS1, status1);
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_rme_rate_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 status1;
	u32 rate = 0;
	पूर्णांक idx;
	पूर्णांक err;

	err = snd_rme_get_status1(kcontrol, &status1);
	अगर (err < 0)
		वापस err;
	चयन (kcontrol->निजी_value) अणु
	हाल SND_RME_DOMAIN_SYSTEM:
		idx = SND_RME_CLK_SYSTEM(status1);
		अगर (idx < ARRAY_SIZE(snd_rme_rate_table))
			rate = snd_rme_rate_table[idx];
		अवरोध;
	हाल SND_RME_DOMAIN_AES:
		idx = SND_RME_CLK_AES(status1);
		अगर (idx < SND_RME_RATE_IDX_AES_SPDIF_NUM)
			rate = snd_rme_rate_table[idx];
		अवरोध;
	हाल SND_RME_DOMAIN_SPDIF:
		idx = SND_RME_CLK_SPDIF(status1);
		अगर (idx < SND_RME_RATE_IDX_AES_SPDIF_NUM)
			rate = snd_rme_rate_table[idx];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = rate;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme_sync_state_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 status1;
	पूर्णांक idx = SND_RME_CLOCK_NOLOCK;
	पूर्णांक err;

	err = snd_rme_get_status1(kcontrol, &status1);
	अगर (err < 0)
		वापस err;
	चयन (kcontrol->निजी_value) अणु
	हाल SND_RME_DOMAIN_AES:  /* AES */
		अगर (status1 & SND_RME_CLK_AES_SYNC)
			idx = SND_RME_CLOCK_SYNC;
		अन्यथा अगर (status1 & SND_RME_CLK_AES_LOCK)
			idx = SND_RME_CLOCK_LOCK;
		अवरोध;
	हाल SND_RME_DOMAIN_SPDIF:  /* SPDIF */
		अगर (status1 & SND_RME_CLK_SPDIF_SYNC)
			idx = SND_RME_CLOCK_SYNC;
		अन्यथा अगर (status1 & SND_RME_CLK_SPDIF_LOCK)
			idx = SND_RME_CLOCK_LOCK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ucontrol->value.क्रमागतerated.item[0] = idx;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme_spdअगर_अगर_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 status1;
	पूर्णांक err;

	err = snd_rme_get_status1(kcontrol, &status1);
	अगर (err < 0)
		वापस err;
	ucontrol->value.क्रमागतerated.item[0] = SND_RME_SPDIF_IF(status1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme_spdअगर_क्रमmat_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 status1;
	पूर्णांक err;

	err = snd_rme_get_status1(kcontrol, &status1);
	अगर (err < 0)
		वापस err;
	ucontrol->value.क्रमागतerated.item[0] = SND_RME_SPDIF_FORMAT(status1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme_sync_source_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 status1;
	पूर्णांक err;

	err = snd_rme_get_status1(kcontrol, &status1);
	अगर (err < 0)
		वापस err;
	ucontrol->value.क्रमागतerated.item[0] = SND_RME_CLK_SYNC(status1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme_current_freq_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_usb_audio *chip = list->mixer->chip;
	u32 status1;
	स्थिर u64 num = 104857600000000ULL;
	u32 den;
	अचिन्हित पूर्णांक freq;
	पूर्णांक err;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;
	err = snd_rme_पढ़ो_value(chip, SND_RME_GET_STATUS1, &status1);
	अगर (err < 0)
		जाओ end;
	err = snd_rme_पढ़ो_value(chip, SND_RME_GET_CURRENT_FREQ, &den);
	अगर (err < 0)
		जाओ end;
	freq = (den == 0) ? 0 : भाग64_u64(num, den);
	freq <<= SND_RME_CLK_FREQMUL(status1);
	ucontrol->value.पूर्णांकeger.value[0] = freq;

end:
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_rme_rate_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	चयन (kcontrol->निजी_value) अणु
	हाल SND_RME_DOMAIN_SYSTEM:
		uinfo->value.पूर्णांकeger.min = 32000;
		uinfo->value.पूर्णांकeger.max = 800000;
		अवरोध;
	हाल SND_RME_DOMAIN_AES:
	हाल SND_RME_DOMAIN_SPDIF:
	शेष:
		uinfo->value.पूर्णांकeger.min = 0;
		uinfo->value.पूर्णांकeger.max = 200000;
	पूर्ण
	uinfo->value.पूर्णांकeger.step = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme_sync_state_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर sync_states[] = अणु
		"No Lock", "Lock", "Sync"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1,
				 ARRAY_SIZE(sync_states), sync_states);
पूर्ण

अटल पूर्णांक snd_rme_spdअगर_अगर_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर spdअगर_अगर[] = अणु
		"Coaxial", "Optical"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1,
				 ARRAY_SIZE(spdअगर_अगर), spdअगर_अगर);
पूर्ण

अटल पूर्णांक snd_rme_spdअगर_क्रमmat_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर optical_type[] = अणु
		"Consumer", "Professional"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1,
				 ARRAY_SIZE(optical_type), optical_type);
पूर्ण

अटल पूर्णांक snd_rme_sync_source_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर sync_sources[] = अणु
		"Internal", "AES", "SPDIF", "Internal"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1,
				 ARRAY_SIZE(sync_sources), sync_sources);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_rme_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "AES Rate",
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_rme_rate_info,
		.get = snd_rme_rate_get,
		.निजी_value = SND_RME_DOMAIN_AES
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "AES Sync",
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_rme_sync_state_info,
		.get = snd_rme_sync_state_get,
		.निजी_value = SND_RME_DOMAIN_AES
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "SPDIF Rate",
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_rme_rate_info,
		.get = snd_rme_rate_get,
		.निजी_value = SND_RME_DOMAIN_SPDIF
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "SPDIF Sync",
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_rme_sync_state_info,
		.get = snd_rme_sync_state_get,
		.निजी_value = SND_RME_DOMAIN_SPDIF
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "SPDIF Interface",
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_rme_spdअगर_अगर_info,
		.get = snd_rme_spdअगर_अगर_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "SPDIF Format",
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_rme_spdअगर_क्रमmat_info,
		.get = snd_rme_spdअगर_क्रमmat_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Sync Source",
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_rme_sync_source_info,
		.get = snd_rme_sync_source_get
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "System Rate",
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_rme_rate_info,
		.get = snd_rme_rate_get,
		.निजी_value = SND_RME_DOMAIN_SYSTEM
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Current Frequency",
		.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.info = snd_rme_rate_info,
		.get = snd_rme_current_freq_get
	पूर्ण
पूर्ण;

अटल पूर्णांक snd_rme_controls_create(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < ARRAY_SIZE(snd_rme_controls); ++i) अणु
		err = add_single_ctl_with_resume(mixer, 0,
						 शून्य,
						 &snd_rme_controls[i],
						 शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * RME Babyface Pro (FS)
 *
 * These devices exposes a couple of DSP functions via request to EP0.
 * Switches are available via control रेजिस्टरs, जबतक routing is controlled
 * by controlling the volume on each possible crossing poपूर्णांक.
 * Volume control is linear, from -inf (dec. 0) to +6dB (dec. 65536) with
 * 0dB being at dec. 32768.
 */
क्रमागत अणु
	SND_BBFPRO_CTL_REG1 = 0,
	SND_BBFPRO_CTL_REG2
पूर्ण;

#घोषणा SND_BBFPRO_CTL_REG_MASK 1
#घोषणा SND_BBFPRO_CTL_IDX_MASK 0xff
#घोषणा SND_BBFPRO_CTL_IDX_SHIFT 1
#घोषणा SND_BBFPRO_CTL_VAL_MASK 1
#घोषणा SND_BBFPRO_CTL_VAL_SHIFT 9
#घोषणा SND_BBFPRO_CTL_REG1_CLK_MASTER 0
#घोषणा SND_BBFPRO_CTL_REG1_CLK_OPTICAL 1
#घोषणा SND_BBFPRO_CTL_REG1_SPDIF_PRO 7
#घोषणा SND_BBFPRO_CTL_REG1_SPDIF_EMPH 8
#घोषणा SND_BBFPRO_CTL_REG1_SPDIF_OPTICAL 10
#घोषणा SND_BBFPRO_CTL_REG2_48V_AN1 0
#घोषणा SND_BBFPRO_CTL_REG2_48V_AN2 1
#घोषणा SND_BBFPRO_CTL_REG2_SENS_IN3 2
#घोषणा SND_BBFPRO_CTL_REG2_SENS_IN4 3
#घोषणा SND_BBFPRO_CTL_REG2_PAD_AN1 4
#घोषणा SND_BBFPRO_CTL_REG2_PAD_AN2 5

#घोषणा SND_BBFPRO_MIXER_IDX_MASK 0x1ff
#घोषणा SND_BBFPRO_MIXER_VAL_MASK 0x3ffff
#घोषणा SND_BBFPRO_MIXER_VAL_SHIFT 9
#घोषणा SND_BBFPRO_MIXER_VAL_MIN 0 // -inf
#घोषणा SND_BBFPRO_MIXER_VAL_MAX 65536 // +6dB

#घोषणा SND_BBFPRO_USBREQ_CTL_REG1 0x10
#घोषणा SND_BBFPRO_USBREQ_CTL_REG2 0x17
#घोषणा SND_BBFPRO_USBREQ_MIXER 0x12

अटल पूर्णांक snd_bbfpro_ctl_update(काष्ठा usb_mixer_पूर्णांकerface *mixer, u8 reg,
				 u8 index, u8 value)
अणु
	पूर्णांक err;
	u16 usb_req, usb_idx, usb_val;
	काष्ठा snd_usb_audio *chip = mixer->chip;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;

	अगर (reg == SND_BBFPRO_CTL_REG1) अणु
		usb_req = SND_BBFPRO_USBREQ_CTL_REG1;
		अगर (index == SND_BBFPRO_CTL_REG1_CLK_OPTICAL) अणु
			usb_idx = 3;
			usb_val = value ? 3 : 0;
		पूर्ण अन्यथा अणु
			usb_idx = 1 << index;
			usb_val = value ? usb_idx : 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		usb_req = SND_BBFPRO_USBREQ_CTL_REG2;
		usb_idx = 1 << index;
		usb_val = value ? usb_idx : 0;
	पूर्ण

	err = snd_usb_ctl_msg(chip->dev,
			      usb_sndctrlpipe(chip->dev, 0), usb_req,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      usb_val, usb_idx, शून्य, 0);

	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_bbfpro_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u8 reg, idx, val;
	पूर्णांक pv;

	pv = kcontrol->निजी_value;
	reg = pv & SND_BBFPRO_CTL_REG_MASK;
	idx = (pv >> SND_BBFPRO_CTL_IDX_SHIFT) & SND_BBFPRO_CTL_IDX_MASK;
	val = kcontrol->निजी_value >> SND_BBFPRO_CTL_VAL_SHIFT;

	अगर ((reg == SND_BBFPRO_CTL_REG1 &&
	     idx == SND_BBFPRO_CTL_REG1_CLK_OPTICAL) ||
	    (reg == SND_BBFPRO_CTL_REG2 &&
	    (idx == SND_BBFPRO_CTL_REG2_SENS_IN3 ||
	     idx == SND_BBFPRO_CTL_REG2_SENS_IN4))) अणु
		ucontrol->value.क्रमागतerated.item[0] = val;
	पूर्ण अन्यथा अणु
		ucontrol->value.पूर्णांकeger.value[0] = val;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bbfpro_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	u8 reg, idx;
	पूर्णांक pv;

	pv = kcontrol->निजी_value;
	reg = pv & SND_BBFPRO_CTL_REG_MASK;
	idx = (pv >> SND_BBFPRO_CTL_IDX_SHIFT) & SND_BBFPRO_CTL_IDX_MASK;

	अगर (reg == SND_BBFPRO_CTL_REG1 &&
	    idx == SND_BBFPRO_CTL_REG1_CLK_OPTICAL) अणु
		अटल स्थिर अक्षर * स्थिर texts[2] = अणु
			"AutoSync",
			"Internal"
		पूर्ण;
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
	पूर्ण अन्यथा अगर (reg == SND_BBFPRO_CTL_REG2 &&
		   (idx == SND_BBFPRO_CTL_REG2_SENS_IN3 ||
		    idx == SND_BBFPRO_CTL_REG2_SENS_IN4)) अणु
		अटल स्थिर अक्षर * स्थिर texts[2] = अणु
			"-10dBV",
			"+4dBu"
		पूर्ण;
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
	पूर्ण

	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bbfpro_ctl_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक err;
	u8 reg, idx;
	पूर्णांक old_value, pv, val;

	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	काष्ठा usb_mixer_पूर्णांकerface *mixer = list->mixer;

	pv = kcontrol->निजी_value;
	reg = pv & SND_BBFPRO_CTL_REG_MASK;
	idx = (pv >> SND_BBFPRO_CTL_IDX_SHIFT) & SND_BBFPRO_CTL_IDX_MASK;
	old_value = (pv >> SND_BBFPRO_CTL_VAL_SHIFT) & SND_BBFPRO_CTL_VAL_MASK;

	अगर ((reg == SND_BBFPRO_CTL_REG1 &&
	     idx == SND_BBFPRO_CTL_REG1_CLK_OPTICAL) ||
	    (reg == SND_BBFPRO_CTL_REG2 &&
	    (idx == SND_BBFPRO_CTL_REG2_SENS_IN3 ||
	     idx == SND_BBFPRO_CTL_REG2_SENS_IN4))) अणु
		val = ucontrol->value.क्रमागतerated.item[0];
	पूर्ण अन्यथा अणु
		val = ucontrol->value.पूर्णांकeger.value[0];
	पूर्ण

	अगर (val > 1)
		वापस -EINVAL;

	अगर (val == old_value)
		वापस 0;

	kcontrol->निजी_value = reg
		| ((idx & SND_BBFPRO_CTL_IDX_MASK) << SND_BBFPRO_CTL_IDX_SHIFT)
		| ((val & SND_BBFPRO_CTL_VAL_MASK) << SND_BBFPRO_CTL_VAL_SHIFT);

	err = snd_bbfpro_ctl_update(mixer, reg, idx, val);
	वापस err < 0 ? err : 1;
पूर्ण

अटल पूर्णांक snd_bbfpro_ctl_resume(काष्ठा usb_mixer_elem_list *list)
अणु
	u8 reg, idx;
	पूर्णांक value, pv;

	pv = list->kctl->निजी_value;
	reg = pv & SND_BBFPRO_CTL_REG_MASK;
	idx = (pv >> SND_BBFPRO_CTL_IDX_SHIFT) & SND_BBFPRO_CTL_IDX_MASK;
	value = (pv >> SND_BBFPRO_CTL_VAL_SHIFT) & SND_BBFPRO_CTL_VAL_MASK;

	वापस snd_bbfpro_ctl_update(list->mixer, reg, idx, value);
पूर्ण

अटल पूर्णांक snd_bbfpro_vol_update(काष्ठा usb_mixer_पूर्णांकerface *mixer, u16 index,
				 u32 value)
अणु
	काष्ठा snd_usb_audio *chip = mixer->chip;
	पूर्णांक err;
	u16 idx;
	u16 usb_idx, usb_val;
	u32 v;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस err;

	idx = index & SND_BBFPRO_MIXER_IDX_MASK;
	// 18 bit linear volume, split so 2 bits end up in index.
	v = value & SND_BBFPRO_MIXER_VAL_MASK;
	usb_idx = idx | (v & 0x3) << 14;
	usb_val = (v >> 2) & 0xffff;

	err = snd_usb_ctl_msg(chip->dev,
			      usb_sndctrlpipe(chip->dev, 0),
			      SND_BBFPRO_USBREQ_MIXER,
			      USB_सूची_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE,
			      usb_val, usb_idx, शून्य, 0);

	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_bbfpro_vol_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] =
		kcontrol->निजी_value >> SND_BBFPRO_MIXER_VAL_SHIFT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bbfpro_vol_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = SND_BBFPRO_MIXER_VAL_MIN;
	uinfo->value.पूर्णांकeger.max = SND_BBFPRO_MIXER_VAL_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bbfpro_vol_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक err;
	u16 idx;
	u32 new_val, old_value, uvalue;
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	काष्ठा usb_mixer_पूर्णांकerface *mixer = list->mixer;

	uvalue = ucontrol->value.पूर्णांकeger.value[0];
	idx = kcontrol->निजी_value & SND_BBFPRO_MIXER_IDX_MASK;
	old_value = kcontrol->निजी_value >> SND_BBFPRO_MIXER_VAL_SHIFT;

	अगर (uvalue > SND_BBFPRO_MIXER_VAL_MAX)
		वापस -EINVAL;

	अगर (uvalue == old_value)
		वापस 0;

	new_val = uvalue & SND_BBFPRO_MIXER_VAL_MASK;

	kcontrol->निजी_value = idx
		| (new_val << SND_BBFPRO_MIXER_VAL_SHIFT);

	err = snd_bbfpro_vol_update(mixer, idx, new_val);
	वापस err < 0 ? err : 1;
पूर्ण

अटल पूर्णांक snd_bbfpro_vol_resume(काष्ठा usb_mixer_elem_list *list)
अणु
	पूर्णांक pv = list->kctl->निजी_value;
	u16 idx = pv & SND_BBFPRO_MIXER_IDX_MASK;
	u32 val = (pv >> SND_BBFPRO_MIXER_VAL_SHIFT)
		& SND_BBFPRO_MIXER_VAL_MASK;
	वापस snd_bbfpro_vol_update(list->mixer, idx, val);
पूर्ण

// Predfine elements
अटल स्थिर काष्ठा snd_kcontrol_new snd_bbfpro_ctl_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.index = 0,
	.info = snd_bbfpro_ctl_info,
	.get = snd_bbfpro_ctl_get,
	.put = snd_bbfpro_ctl_put
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_bbfpro_vol_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.index = 0,
	.info = snd_bbfpro_vol_info,
	.get = snd_bbfpro_vol_get,
	.put = snd_bbfpro_vol_put
पूर्ण;

अटल पूर्णांक snd_bbfpro_ctl_add(काष्ठा usb_mixer_पूर्णांकerface *mixer, u8 reg,
			      u8 index, अक्षर *name)
अणु
	काष्ठा snd_kcontrol_new knew = snd_bbfpro_ctl_control;

	knew.name = name;
	knew.निजी_value = (reg & SND_BBFPRO_CTL_REG_MASK)
		| ((index & SND_BBFPRO_CTL_IDX_MASK)
			<< SND_BBFPRO_CTL_IDX_SHIFT);

	वापस add_single_ctl_with_resume(mixer, 0, snd_bbfpro_ctl_resume,
		&knew, शून्य);
पूर्ण

अटल पूर्णांक snd_bbfpro_vol_add(काष्ठा usb_mixer_पूर्णांकerface *mixer, u16 index,
			      अक्षर *name)
अणु
	काष्ठा snd_kcontrol_new knew = snd_bbfpro_vol_control;

	knew.name = name;
	knew.निजी_value = index & SND_BBFPRO_MIXER_IDX_MASK;

	वापस add_single_ctl_with_resume(mixer, 0, snd_bbfpro_vol_resume,
		&knew, शून्य);
पूर्ण

अटल पूर्णांक snd_bbfpro_controls_create(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	पूर्णांक err, i, o;
	अक्षर name[48];

	अटल स्थिर अक्षर * स्थिर input[] = अणु
		"AN1", "AN2", "IN3", "IN4", "AS1", "AS2", "ADAT3",
		"ADAT4", "ADAT5", "ADAT6", "ADAT7", "ADAT8"पूर्ण;

	अटल स्थिर अक्षर * स्थिर output[] = अणु
		"AN1", "AN2", "PH3", "PH4", "AS1", "AS2", "ADAT3", "ADAT4",
		"ADAT5", "ADAT6", "ADAT7", "ADAT8"पूर्ण;

	क्रम (o = 0 ; o < 12 ; ++o) अणु
		क्रम (i = 0 ; i < 12 ; ++i) अणु
			// Line routing
			snम_लिखो(name, माप(name),
				 "%s-%s-%s Playback Volume",
				 (i < 2 ? "Mic" : "Line"),
				 input[i], output[o]);
			err = snd_bbfpro_vol_add(mixer, (26 * o + i), name);
			अगर (err < 0)
				वापस err;

			// PCM routing... yes, it is output remapping
			snम_लिखो(name, माप(name),
				 "PCM-%s-%s Playback Volume",
				 output[i], output[o]);
			err = snd_bbfpro_vol_add(mixer, (26 * o + 12 + i),
						 name);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	// Control Reg 1
	err = snd_bbfpro_ctl_add(mixer, SND_BBFPRO_CTL_REG1,
				 SND_BBFPRO_CTL_REG1_CLK_OPTICAL,
				 "Sample Clock Source");
	अगर (err < 0)
		वापस err;

	err = snd_bbfpro_ctl_add(mixer, SND_BBFPRO_CTL_REG1,
				 SND_BBFPRO_CTL_REG1_SPDIF_PRO,
				 "IEC958 Pro Mask");
	अगर (err < 0)
		वापस err;

	err = snd_bbfpro_ctl_add(mixer, SND_BBFPRO_CTL_REG1,
				 SND_BBFPRO_CTL_REG1_SPDIF_EMPH,
				 "IEC958 Emphasis");
	अगर (err < 0)
		वापस err;

	err = snd_bbfpro_ctl_add(mixer, SND_BBFPRO_CTL_REG1,
				 SND_BBFPRO_CTL_REG1_SPDIF_OPTICAL,
				 "IEC958 Switch");
	अगर (err < 0)
		वापस err;

	// Control Reg 2
	err = snd_bbfpro_ctl_add(mixer, SND_BBFPRO_CTL_REG2,
				 SND_BBFPRO_CTL_REG2_48V_AN1,
				 "Mic-AN1 48V");
	अगर (err < 0)
		वापस err;

	err = snd_bbfpro_ctl_add(mixer, SND_BBFPRO_CTL_REG2,
				 SND_BBFPRO_CTL_REG2_48V_AN2,
				 "Mic-AN2 48V");
	अगर (err < 0)
		वापस err;

	err = snd_bbfpro_ctl_add(mixer, SND_BBFPRO_CTL_REG2,
				 SND_BBFPRO_CTL_REG2_SENS_IN3,
				 "Line-IN3 Sens.");
	अगर (err < 0)
		वापस err;

	err = snd_bbfpro_ctl_add(mixer, SND_BBFPRO_CTL_REG2,
				 SND_BBFPRO_CTL_REG2_SENS_IN4,
				 "Line-IN4 Sens.");
	अगर (err < 0)
		वापस err;

	err = snd_bbfpro_ctl_add(mixer, SND_BBFPRO_CTL_REG2,
				 SND_BBFPRO_CTL_REG2_PAD_AN1,
				 "Mic-AN1 PAD");
	अगर (err < 0)
		वापस err;

	err = snd_bbfpro_ctl_add(mixer, SND_BBFPRO_CTL_REG2,
				 SND_BBFPRO_CTL_REG2_PAD_AN2,
				 "Mic-AN2 PAD");
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/*
 * Pioneer DJ DJM Mixers
 *
 * These devices generally have options क्रम soft-चयनing the playback and
 * capture sources in addition to the recording level. Although dअगरferent
 * devices have dअगरferent configurations, there seems to be canonical values
 * क्रम specअगरic capture/playback types:  See the definitions of these below.
 *
 * The wValue is masked with the stereo channel number. e.g. Setting Ch2 to
 * capture phono would be 0x0203. Capture, playback and capture level have
 * dअगरferent wIndexes.
 */

// Capture types
#घोषणा SND_DJM_CAP_LINE	0x00
#घोषणा SND_DJM_CAP_CDLINE	0x01
#घोषणा SND_DJM_CAP_DIGITAL	0x02
#घोषणा SND_DJM_CAP_PHONO	0x03
#घोषणा SND_DJM_CAP_PFADER	0x06
#घोषणा SND_DJM_CAP_XFADERA	0x07
#घोषणा SND_DJM_CAP_XFADERB	0x08
#घोषणा SND_DJM_CAP_MIC		0x09
#घोषणा SND_DJM_CAP_AUX		0x0d
#घोषणा SND_DJM_CAP_RECOUT	0x0a
#घोषणा SND_DJM_CAP_NONE	0x0f
#घोषणा SND_DJM_CAP_CH1PFADER	0x11
#घोषणा SND_DJM_CAP_CH2PFADER	0x12
#घोषणा SND_DJM_CAP_CH3PFADER	0x13
#घोषणा SND_DJM_CAP_CH4PFADER	0x14

// Playback types
#घोषणा SND_DJM_PB_CH1		0x00
#घोषणा SND_DJM_PB_CH2		0x01
#घोषणा SND_DJM_PB_AUX		0x04

#घोषणा SND_DJM_WINDEX_CAP	0x8002
#घोषणा SND_DJM_WINDEX_CAPLVL	0x8003
#घोषणा SND_DJM_WINDEX_PB	0x8016

// kcontrol->निजी_value layout
#घोषणा SND_DJM_VALUE_MASK	0x0000ffff
#घोषणा SND_DJM_GROUP_MASK	0x00ff0000
#घोषणा SND_DJM_DEVICE_MASK	0xff000000
#घोषणा SND_DJM_GROUP_SHIFT	16
#घोषणा SND_DJM_DEVICE_SHIFT	24

// device table index
// used क्रम the snd_djm_devices table, so please update accordingly
#घोषणा SND_DJM_250MK2_IDX	0x0
#घोषणा SND_DJM_750_IDX		0x1
#घोषणा SND_DJM_850_IDX		0x2
#घोषणा SND_DJM_900NXS2_IDX	0x3


#घोषणा SND_DJM_CTL(_name, suffix, _शेष_value, _windex) अणु \
	.name = _name, \
	.options = snd_djm_opts_##suffix, \
	.noptions = ARRAY_SIZE(snd_djm_opts_##suffix), \
	.शेष_value = _शेष_value, \
	.wIndex = _windex पूर्ण

#घोषणा SND_DJM_DEVICE(suffix) अणु \
	.controls = snd_djm_ctls_##suffix, \
	.ncontrols = ARRAY_SIZE(snd_djm_ctls_##suffix) पूर्ण


काष्ठा snd_djm_device अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा snd_djm_ctl *controls;
	माप_प्रकार ncontrols;
पूर्ण;

काष्ठा snd_djm_ctl अणु
	स्थिर अक्षर *name;
	स्थिर u16 *options;
	माप_प्रकार noptions;
	u16 शेष_value;
	u16 wIndex;
पूर्ण;

अटल स्थिर अक्षर *snd_djm_get_label_caplevel(u16 wvalue)
अणु
	चयन (wvalue) अणु
	हाल 0x0000:	वापस "-19dB";
	हाल 0x0100:	वापस "-15dB";
	हाल 0x0200:	वापस "-10dB";
	हाल 0x0300:	वापस "-5dB";
	शेष:	वापस शून्य;
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर *snd_djm_get_label_cap_common(u16 wvalue)
अणु
	चयन (wvalue & 0x00ff) अणु
	हाल SND_DJM_CAP_LINE:		वापस "Control Tone LINE";
	हाल SND_DJM_CAP_CDLINE:	वापस "Control Tone CD/LINE";
	हाल SND_DJM_CAP_DIGITAL:	वापस "Control Tone DIGITAL";
	हाल SND_DJM_CAP_PHONO:		वापस "Control Tone PHONO";
	हाल SND_DJM_CAP_PFADER:	वापस "Post Fader";
	हाल SND_DJM_CAP_XFADERA:	वापस "Cross Fader A";
	हाल SND_DJM_CAP_XFADERB:	वापस "Cross Fader B";
	हाल SND_DJM_CAP_MIC:		वापस "Mic";
	हाल SND_DJM_CAP_RECOUT:	वापस "Rec Out";
	हाल SND_DJM_CAP_AUX:		वापस "Aux";
	हाल SND_DJM_CAP_NONE:		वापस "None";
	हाल SND_DJM_CAP_CH1PFADER:	वापस "Post Fader Ch1";
	हाल SND_DJM_CAP_CH2PFADER:	वापस "Post Fader Ch2";
	हाल SND_DJM_CAP_CH3PFADER:	वापस "Post Fader Ch3";
	हाल SND_DJM_CAP_CH4PFADER:	वापस "Post Fader Ch4";
	शेष:			वापस शून्य;
	पूर्ण
पूर्ण;

// The DJM-850 has dअगरferent values क्रम CD/LINE and LINE capture
// control options than the other DJM declared in this file.
अटल स्थिर अक्षर *snd_djm_get_label_cap_850(u16 wvalue)
अणु
	चयन (wvalue & 0x00ff) अणु
	हाल 0x00:		वापस "Control Tone CD/LINE";
	हाल 0x01:		वापस "Control Tone LINE";
	शेष:		वापस snd_djm_get_label_cap_common(wvalue);
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर *snd_djm_get_label_cap(u8 device_idx, u16 wvalue)
अणु
	चयन (device_idx) अणु
	हाल SND_DJM_850_IDX:		वापस snd_djm_get_label_cap_850(wvalue);
	शेष:			वापस snd_djm_get_label_cap_common(wvalue);
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर *snd_djm_get_label_pb(u16 wvalue)
अणु
	चयन (wvalue & 0x00ff) अणु
	हाल SND_DJM_PB_CH1:	वापस "Ch1";
	हाल SND_DJM_PB_CH2:	वापस "Ch2";
	हाल SND_DJM_PB_AUX:	वापस "Aux";
	शेष:		वापस शून्य;
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर *snd_djm_get_label(u8 device_idx, u16 wvalue, u16 windex)
अणु
	चयन (windex) अणु
	हाल SND_DJM_WINDEX_CAPLVL:	वापस snd_djm_get_label_caplevel(wvalue);
	हाल SND_DJM_WINDEX_CAP:	वापस snd_djm_get_label_cap(device_idx, wvalue);
	हाल SND_DJM_WINDEX_PB:		वापस snd_djm_get_label_pb(wvalue);
	शेष:			वापस शून्य;
	पूर्ण
पूर्ण;

// common DJM capture level option values
अटल स्थिर u16 snd_djm_opts_cap_level[] = अणु
	0x0000, 0x0100, 0x0200, 0x0300 पूर्ण;


// DJM-250MK2
अटल स्थिर u16 snd_djm_opts_250mk2_cap1[] = अणु
	0x0103, 0x0100, 0x0106, 0x0107, 0x0108, 0x0109, 0x010d, 0x010a पूर्ण;

अटल स्थिर u16 snd_djm_opts_250mk2_cap2[] = अणु
	0x0203, 0x0200, 0x0206, 0x0207, 0x0208, 0x0209, 0x020d, 0x020a पूर्ण;

अटल स्थिर u16 snd_djm_opts_250mk2_cap3[] = अणु
	0x030a, 0x0311, 0x0312, 0x0307, 0x0308, 0x0309, 0x030d पूर्ण;

अटल स्थिर u16 snd_djm_opts_250mk2_pb1[] = अणु 0x0100, 0x0101, 0x0104 पूर्ण;
अटल स्थिर u16 snd_djm_opts_250mk2_pb2[] = अणु 0x0200, 0x0201, 0x0204 पूर्ण;
अटल स्थिर u16 snd_djm_opts_250mk2_pb3[] = अणु 0x0300, 0x0301, 0x0304 पूर्ण;

अटल स्थिर काष्ठा snd_djm_ctl snd_djm_ctls_250mk2[] = अणु
	SND_DJM_CTL("Capture Level", cap_level, 0, SND_DJM_WINDEX_CAPLVL),
	SND_DJM_CTL("Ch1 Input",   250mk2_cap1, 2, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch2 Input",   250mk2_cap2, 2, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch3 Input",   250mk2_cap3, 0, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch1 Output",   250mk2_pb1, 0, SND_DJM_WINDEX_PB),
	SND_DJM_CTL("Ch2 Output",   250mk2_pb2, 1, SND_DJM_WINDEX_PB),
	SND_DJM_CTL("Ch3 Output",   250mk2_pb3, 2, SND_DJM_WINDEX_PB)
पूर्ण;


// DJM-750
अटल स्थिर u16 snd_djm_opts_750_cap1[] = अणु
	0x0101, 0x0103, 0x0106, 0x0107, 0x0108, 0x0109, 0x010a, 0x010f पूर्ण;
अटल स्थिर u16 snd_djm_opts_750_cap2[] = अणु
	0x0200, 0x0201, 0x0206, 0x0207, 0x0208, 0x0209, 0x020a, 0x020f पूर्ण;
अटल स्थिर u16 snd_djm_opts_750_cap3[] = अणु
	0x0300, 0x0301, 0x0306, 0x0307, 0x0308, 0x0309, 0x030a, 0x030f पूर्ण;
अटल स्थिर u16 snd_djm_opts_750_cap4[] = अणु
	0x0401, 0x0403, 0x0406, 0x0407, 0x0408, 0x0409, 0x040a, 0x040f पूर्ण;

अटल स्थिर काष्ठा snd_djm_ctl snd_djm_ctls_750[] = अणु
	SND_DJM_CTL("Capture Level", cap_level, 0, SND_DJM_WINDEX_CAPLVL),
	SND_DJM_CTL("Ch1 Input",   750_cap1, 2, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch2 Input",   750_cap2, 2, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch3 Input",   750_cap3, 0, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch4 Input",   750_cap4, 0, SND_DJM_WINDEX_CAP)
पूर्ण;


// DJM-850
अटल स्थिर u16 snd_djm_opts_850_cap1[] = अणु
	0x0100, 0x0103, 0x0106, 0x0107, 0x0108, 0x0109, 0x010a, 0x010f पूर्ण;
अटल स्थिर u16 snd_djm_opts_850_cap2[] = अणु
	0x0200, 0x0201, 0x0206, 0x0207, 0x0208, 0x0209, 0x020a, 0x020f पूर्ण;
अटल स्थिर u16 snd_djm_opts_850_cap3[] = अणु
	0x0300, 0x0301, 0x0306, 0x0307, 0x0308, 0x0309, 0x030a, 0x030f पूर्ण;
अटल स्थिर u16 snd_djm_opts_850_cap4[] = अणु
	0x0400, 0x0403, 0x0406, 0x0407, 0x0408, 0x0409, 0x040a, 0x040f पूर्ण;

अटल स्थिर काष्ठा snd_djm_ctl snd_djm_ctls_850[] = अणु
	SND_DJM_CTL("Capture Level", cap_level, 0, SND_DJM_WINDEX_CAPLVL),
	SND_DJM_CTL("Ch1 Input",   850_cap1, 1, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch2 Input",   850_cap2, 0, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch3 Input",   850_cap3, 0, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch4 Input",   850_cap4, 1, SND_DJM_WINDEX_CAP)
पूर्ण;


// DJM-900NXS2
अटल स्थिर u16 snd_djm_opts_900nxs2_cap1[] = अणु
	0x0100, 0x0102, 0x0103, 0x0106, 0x0107, 0x0108, 0x0109, 0x010a पूर्ण;
अटल स्थिर u16 snd_djm_opts_900nxs2_cap2[] = अणु
	0x0200, 0x0202, 0x0203, 0x0206, 0x0207, 0x0208, 0x0209, 0x020a पूर्ण;
अटल स्थिर u16 snd_djm_opts_900nxs2_cap3[] = अणु
	0x0300, 0x0302, 0x0303, 0x0306, 0x0307, 0x0308, 0x0309, 0x030a पूर्ण;
अटल स्थिर u16 snd_djm_opts_900nxs2_cap4[] = अणु
	0x0400, 0x0402, 0x0403, 0x0406, 0x0407, 0x0408, 0x0409, 0x040a पूर्ण;
अटल स्थिर u16 snd_djm_opts_900nxs2_cap5[] = अणु
	0x0507, 0x0508, 0x0509, 0x050a, 0x0511, 0x0512, 0x0513, 0x0514 पूर्ण;

अटल स्थिर काष्ठा snd_djm_ctl snd_djm_ctls_900nxs2[] = अणु
	SND_DJM_CTL("Capture Level", cap_level, 0, SND_DJM_WINDEX_CAPLVL),
	SND_DJM_CTL("Ch1 Input",   900nxs2_cap1, 2, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch2 Input",   900nxs2_cap2, 2, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch3 Input",   900nxs2_cap3, 2, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch4 Input",   900nxs2_cap4, 2, SND_DJM_WINDEX_CAP),
	SND_DJM_CTL("Ch5 Input",   900nxs2_cap5, 3, SND_DJM_WINDEX_CAP)
पूर्ण;


अटल स्थिर काष्ठा snd_djm_device snd_djm_devices[] = अणु
	SND_DJM_DEVICE(250mk2),
	SND_DJM_DEVICE(750),
	SND_DJM_DEVICE(850),
	SND_DJM_DEVICE(900nxs2)
पूर्ण;


अटल पूर्णांक snd_djm_controls_info(काष्ठा snd_kcontrol *kctl,
				काष्ठा snd_ctl_elem_info *info)
अणु
	अचिन्हित दीर्घ निजी_value = kctl->निजी_value;
	u8 device_idx = (निजी_value & SND_DJM_DEVICE_MASK) >> SND_DJM_DEVICE_SHIFT;
	u8 ctl_idx = (निजी_value & SND_DJM_GROUP_MASK) >> SND_DJM_GROUP_SHIFT;
	स्थिर काष्ठा snd_djm_device *device = &snd_djm_devices[device_idx];
	स्थिर अक्षर *name;
	स्थिर काष्ठा snd_djm_ctl *ctl;
	माप_प्रकार noptions;

	अगर (ctl_idx >= device->ncontrols)
		वापस -EINVAL;

	ctl = &device->controls[ctl_idx];
	noptions = ctl->noptions;
	अगर (info->value.क्रमागतerated.item >= noptions)
		info->value.क्रमागतerated.item = noptions - 1;

	name = snd_djm_get_label(device_idx,
				ctl->options[info->value.क्रमागतerated.item],
				ctl->wIndex);
	अगर (!name)
		वापस -EINVAL;

	strscpy(info->value.क्रमागतerated.name, name, माप(info->value.क्रमागतerated.name));
	info->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	info->count = 1;
	info->value.क्रमागतerated.items = noptions;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_djm_controls_update(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				u8 device_idx, u8 group, u16 value)
अणु
	पूर्णांक err;
	स्थिर काष्ठा snd_djm_device *device = &snd_djm_devices[device_idx];

	अगर ((group >= device->ncontrols) || value >= device->controls[group].noptions)
		वापस -EINVAL;

	err = snd_usb_lock_shutकरोwn(mixer->chip);
	अगर (err)
		वापस err;

	err = snd_usb_ctl_msg(
		mixer->chip->dev, usb_sndctrlpipe(mixer->chip->dev, 0),
		USB_REQ_SET_FEATURE,
		USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		device->controls[group].options[value],
		device->controls[group].wIndex,
		शून्य, 0);

	snd_usb_unlock_shutकरोwn(mixer->chip);
	वापस err;
पूर्ण

अटल पूर्णांक snd_djm_controls_get(काष्ठा snd_kcontrol *kctl,
				काष्ठा snd_ctl_elem_value *elem)
अणु
	elem->value.क्रमागतerated.item[0] = kctl->निजी_value & SND_DJM_VALUE_MASK;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_djm_controls_put(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_value *elem)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kctl);
	काष्ठा usb_mixer_पूर्णांकerface *mixer = list->mixer;
	अचिन्हित दीर्घ निजी_value = kctl->निजी_value;

	u8 device = (निजी_value & SND_DJM_DEVICE_MASK) >> SND_DJM_DEVICE_SHIFT;
	u8 group = (निजी_value & SND_DJM_GROUP_MASK) >> SND_DJM_GROUP_SHIFT;
	u16 value = elem->value.क्रमागतerated.item[0];

	kctl->निजी_value = (((अचिन्हित दीर्घ)device << SND_DJM_DEVICE_SHIFT) |
			      (group << SND_DJM_GROUP_SHIFT) |
			      value);

	वापस snd_djm_controls_update(mixer, device, group, value);
पूर्ण

अटल पूर्णांक snd_djm_controls_resume(काष्ठा usb_mixer_elem_list *list)
अणु
	अचिन्हित दीर्घ निजी_value = list->kctl->निजी_value;
	u8 device = (निजी_value & SND_DJM_DEVICE_MASK) >> SND_DJM_DEVICE_SHIFT;
	u8 group = (निजी_value & SND_DJM_GROUP_MASK) >> SND_DJM_GROUP_SHIFT;
	u16 value = (निजी_value & SND_DJM_VALUE_MASK);

	वापस snd_djm_controls_update(list->mixer, device, group, value);
पूर्ण

अटल पूर्णांक snd_djm_controls_create(काष्ठा usb_mixer_पूर्णांकerface *mixer,
		स्थिर u8 device_idx)
अणु
	पूर्णांक err, i;
	u16 value;

	स्थिर काष्ठा snd_djm_device *device = &snd_djm_devices[device_idx];

	काष्ठा snd_kcontrol_new knew = अणु
		.अगरace  = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.index = 0,
		.info = snd_djm_controls_info,
		.get  = snd_djm_controls_get,
		.put  = snd_djm_controls_put
	पूर्ण;

	क्रम (i = 0; i < device->ncontrols; i++) अणु
		value = device->controls[i].शेष_value;
		knew.name = device->controls[i].name;
		knew.निजी_value = (
			((अचिन्हित दीर्घ)device_idx << SND_DJM_DEVICE_SHIFT) |
			(i << SND_DJM_GROUP_SHIFT) |
			value);
		err = snd_djm_controls_update(mixer, device_idx, i, value);
		अगर (err)
			वापस err;
		err = add_single_ctl_with_resume(mixer, 0, snd_djm_controls_resume,
						 &knew, शून्य);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_usb_mixer_apply_create_quirk(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	पूर्णांक err = 0;

	err = snd_usb_soundblaster_remote_init(mixer);
	अगर (err < 0)
		वापस err;

	चयन (mixer->chip->usb_id) अणु
	/* Tascam US-16x08 */
	हाल USB_ID(0x0644, 0x8047):
		err = snd_us16x08_controls_create(mixer);
		अवरोध;
	हाल USB_ID(0x041e, 0x3020):
	हाल USB_ID(0x041e, 0x3040):
	हाल USB_ID(0x041e, 0x3042):
	हाल USB_ID(0x041e, 0x30df):
	हाल USB_ID(0x041e, 0x3048):
		err = snd_audigy2nx_controls_create(mixer);
		अगर (err < 0)
			अवरोध;
		snd_card_ro_proc_new(mixer->chip->card, "audigy2nx",
				     mixer, snd_audigy2nx_proc_पढ़ो);
		अवरोध;

	/* EMU0204 */
	हाल USB_ID(0x041e, 0x3f19):
		err = snd_emu0204_controls_create(mixer);
		अवरोध;

	हाल USB_ID(0x0763, 0x2030): /* M-Audio Fast Track C400 */
	हाल USB_ID(0x0763, 0x2031): /* M-Audio Fast Track C400 */
		err = snd_c400_create_mixer(mixer);
		अवरोध;

	हाल USB_ID(0x0763, 0x2080): /* M-Audio Fast Track Ultra */
	हाल USB_ID(0x0763, 0x2081): /* M-Audio Fast Track Ultra 8R */
		err = snd_ftu_create_mixer(mixer);
		अवरोध;

	हाल USB_ID(0x0b05, 0x1739): /* ASUS Xonar U1 */
	हाल USB_ID(0x0b05, 0x1743): /* ASUS Xonar U1 (2) */
	हाल USB_ID(0x0b05, 0x17a0): /* ASUS Xonar U3 */
		err = snd_xonar_u1_controls_create(mixer);
		अवरोध;

	हाल USB_ID(0x0d8c, 0x0103): /* Audio Advantage Micro II */
		err = snd_microii_controls_create(mixer);
		अवरोध;

	हाल USB_ID(0x0dba, 0x1000): /* Digidesign Mbox 1 */
		err = snd_mbox1_create_sync_चयन(mixer);
		अवरोध;

	हाल USB_ID(0x17cc, 0x1011): /* Traktor Audio 6 */
		err = snd_nativeinstruments_create_mixer(mixer,
				snd_nativeinstruments_ta6_mixers,
				ARRAY_SIZE(snd_nativeinstruments_ta6_mixers));
		अवरोध;

	हाल USB_ID(0x17cc, 0x1021): /* Traktor Audio 10 */
		err = snd_nativeinstruments_create_mixer(mixer,
				snd_nativeinstruments_ta10_mixers,
				ARRAY_SIZE(snd_nativeinstruments_ta10_mixers));
		अवरोध;

	हाल USB_ID(0x200c, 0x1018): /* Electrix Ebox-44 */
		/* detection is disabled in mixer_maps.c */
		err = snd_create_std_mono_table(mixer, ebox44_table);
		अवरोध;

	हाल USB_ID(0x1235, 0x8012): /* Focusrite Scarlett 6i6 */
	हाल USB_ID(0x1235, 0x8002): /* Focusrite Scarlett 8i6 */
	हाल USB_ID(0x1235, 0x8004): /* Focusrite Scarlett 18i6 */
	हाल USB_ID(0x1235, 0x8014): /* Focusrite Scarlett 18i8 */
	हाल USB_ID(0x1235, 0x800c): /* Focusrite Scarlett 18i20 */
		err = snd_scarlett_controls_create(mixer);
		अवरोध;

	हाल USB_ID(0x1235, 0x8203): /* Focusrite Scarlett 6i6 2nd Gen */
	हाल USB_ID(0x1235, 0x8204): /* Focusrite Scarlett 18i8 2nd Gen */
	हाल USB_ID(0x1235, 0x8201): /* Focusrite Scarlett 18i20 2nd Gen */
		err = snd_scarlett_gen2_init(mixer);
		अवरोध;

	हाल USB_ID(0x041e, 0x323b): /* Creative Sound Blaster E1 */
		err = snd_soundblaster_e1_चयन_create(mixer);
		अवरोध;
	हाल USB_ID(0x0bda, 0x4014): /* Dell WD15 करोck */
		err = dell_करोck_mixer_init(mixer);
		अवरोध;

	हाल USB_ID(0x2a39, 0x3fd2): /* RME ADI-2 Pro */
	हाल USB_ID(0x2a39, 0x3fd3): /* RME ADI-2 DAC */
	हाल USB_ID(0x2a39, 0x3fd4): /* RME */
		err = snd_rme_controls_create(mixer);
		अवरोध;

	हाल USB_ID(0x0194f, 0x010c): /* Presonus Studio 1810c */
		err = snd_sc1810_init_mixer(mixer);
		अवरोध;
	हाल USB_ID(0x2a39, 0x3fb0): /* RME Babyface Pro FS */
		err = snd_bbfpro_controls_create(mixer);
		अवरोध;
	हाल USB_ID(0x2b73, 0x0017): /* Pioneer DJ DJM-250MK2 */
		err = snd_djm_controls_create(mixer, SND_DJM_250MK2_IDX);
		अवरोध;
	हाल USB_ID(0x08e4, 0x017f): /* Pioneer DJ DJM-750 */
		err = snd_djm_controls_create(mixer, SND_DJM_750_IDX);
		अवरोध;
	हाल USB_ID(0x08e4, 0x0163): /* Pioneer DJ DJM-850 */
		err = snd_djm_controls_create(mixer, SND_DJM_850_IDX);
		अवरोध;
	हाल USB_ID(0x2b73, 0x000a): /* Pioneer DJ DJM-900NXS2 */
		err = snd_djm_controls_create(mixer, SND_DJM_900NXS2_IDX);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM
व्योम snd_usb_mixer_resume_quirk(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	चयन (mixer->chip->usb_id) अणु
	हाल USB_ID(0x0bda, 0x4014): /* Dell WD15 करोck */
		dell_करोck_mixer_init(mixer);
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम snd_usb_mixer_rc_memory_change(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				    पूर्णांक unitid)
अणु
	अगर (!mixer->rc_cfg)
		वापस;
	/* unit ids specअगरic to Extigy/Audigy 2 NX: */
	चयन (unitid) अणु
	हाल 0: /* remote control */
		mixer->rc_urb->dev = mixer->chip->dev;
		usb_submit_urb(mixer->rc_urb, GFP_ATOMIC);
		अवरोध;
	हाल 4: /* digital in jack */
	हाल 7: /* line in jacks */
	हाल 19: /* speaker out jacks */
	हाल 20: /* headphones out jack */
		अवरोध;
	/* live24ext: 4 = line-in jack */
	हाल 3:	/* hp-out jack (may actuate Mute) */
		अगर (mixer->chip->usb_id == USB_ID(0x041e, 0x3040) ||
		    mixer->chip->usb_id == USB_ID(0x041e, 0x3048))
			snd_usb_mixer_notअगरy_id(mixer, mixer->rc_cfg->mute_mixer_id);
		अवरोध;
	शेष:
		usb_audio_dbg(mixer->chip, "memory change in unknown unit %d\n", unitid);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम snd_dragonfly_quirk_db_scale(काष्ठा usb_mixer_पूर्णांकerface *mixer,
					 काष्ठा usb_mixer_elem_info *cval,
					 काष्ठा snd_kcontrol *kctl)
अणु
	/* Approximation using 10 ranges based on output measurement on hw v1.2.
	 * This seems बंद to the cubic mapping e.g. alsamixer uses. */
	अटल स्थिर DECLARE_TLV_DB_RANGE(scale,
		 0,  1, TLV_DB_MINMAX_ITEM(-5300, -4970),
		 2,  5, TLV_DB_MINMAX_ITEM(-4710, -4160),
		 6,  7, TLV_DB_MINMAX_ITEM(-3884, -3710),
		 8, 14, TLV_DB_MINMAX_ITEM(-3443, -2560),
		15, 16, TLV_DB_MINMAX_ITEM(-2475, -2324),
		17, 19, TLV_DB_MINMAX_ITEM(-2228, -2031),
		20, 26, TLV_DB_MINMAX_ITEM(-1910, -1393),
		27, 31, TLV_DB_MINMAX_ITEM(-1322, -1032),
		32, 40, TLV_DB_MINMAX_ITEM(-968, -490),
		41, 50, TLV_DB_MINMAX_ITEM(-441, 0),
	);

	अगर (cval->min == 0 && cval->max == 50) अणु
		usb_audio_info(mixer->chip, "applying DragonFly dB scale quirk (0-50 variant)\n");
		kctl->tlv.p = scale;
		kctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		kctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK;

	पूर्ण अन्यथा अगर (cval->min == 0 && cval->max <= 1000) अणु
		/* Some other clearly broken DragonFly variant.
		 * At least a 0..53 variant (hw v1.0) exists.
		 */
		usb_audio_info(mixer->chip, "ignoring too narrow dB range on a DragonFly device");
		kctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK;
	पूर्ण
पूर्ण

व्योम snd_usb_mixer_fu_apply_quirk(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				  काष्ठा usb_mixer_elem_info *cval, पूर्णांक unitid,
				  काष्ठा snd_kcontrol *kctl)
अणु
	चयन (mixer->chip->usb_id) अणु
	हाल USB_ID(0x21b4, 0x0081): /* AudioQuest DragonFly */
		अगर (unitid == 7 && cval->control == UAC_FU_VOLUME)
			snd_dragonfly_quirk_db_scale(mixer, cval, kctl);
		अवरोध;
	/* lowest playback value is muted on C-Media devices */
	हाल USB_ID(0x0d8c, 0x000c):
	हाल USB_ID(0x0d8c, 0x0014):
		अगर (म_माला(kctl->id.name, "Playback"))
			cval->min_mute = 1;
		अवरोध;
	पूर्ण
पूर्ण

