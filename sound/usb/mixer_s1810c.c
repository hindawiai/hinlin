<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Presonus Studio 1810c driver क्रम ALSA
 * Copyright (C) 2019 Nick Kossअगरidis <mickflemm@gmail.com>
 *
 * Based on reverse engineering of the communication protocol
 * between the winकरोws driver / Univeral Control (UC) program
 * and the device, through usbmon.
 *
 * For now this bypasses the mixer, with all channels split,
 * so that the software can mix with greater flexibility.
 * It also adds controls क्रम the 4 buttons on the front of
 * the device.
 */

#समावेश <linux/usb.h>
#समावेश <linux/usb/audio-v2.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>

#समावेश "usbaudio.h"
#समावेश "mixer.h"
#समावेश "mixer_quirks.h"
#समावेश "helper.h"
#समावेश "mixer_s1810c.h"

#घोषणा SC1810C_CMD_REQ	160
#घोषणा SC1810C_CMD_REQTYPE \
	(USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT)
#घोषणा SC1810C_CMD_F1		0x50617269
#घोषणा SC1810C_CMD_F2		0x14

/*
 * DISCLAIMER: These are just guesses based on the
 * dumps I got.
 *
 * It seems like a selects between
 * device (0), mixer (0x64) and output (0x65)
 *
 * For mixer (0x64):
 *  * b selects an input channel (see below).
 *  * c selects an output channel pair (see below).
 *  * d selects left (0) or right (1) of that pair.
 *  * e 0-> disconnect, 0x01000000-> connect,
 *	0x0109-> used क्रम stereo-linking channels,
 *	e is also used क्रम setting volume levels
 *	in which हाल b is also set so I guess
 *	this way it is possible to set the volume
 *	level from the specअगरied input to the
 *	specअगरied output.
 *
 * IN Channels:
 * 0  - 7  Mic/Inst/Line (Analog inमाला_दो)
 * 8  - 9  S/PDIF
 * 10 - 17 ADAT
 * 18 - 35 DAW (Inमाला_दो from the host)
 *
 * OUT Channels (pairs):
 * 0 -> Main out
 * 1 -> Line1/2
 * 2 -> Line3/4
 * 3 -> S/PDIF
 * 4 -> ADAT?
 *
 * For device (0):
 *  * b and c are not used, at least not on the
 *    dumps I got.
 *  * d sets the control id to be modअगरied
 *    (see below).
 *  * e sets the setting क्रम that control.
 *    (so क्रम the चयनes I was पूर्णांकerested
 *    in it's 0/1)
 *
 * For output (0x65):
 *   * b is the output channel (see above).
 *   * c is zero.
 *   * e I guess the same as with mixer except 0x0109
 *	 which I didn't see in my dumps.
 *
 * The two fixed fields have the same values क्रम
 * mixer and output but a dअगरferent set क्रम device.
 */
काष्ठा s1810c_ctl_packet अणु
	u32 a;
	u32 b;
	u32 fixed1;
	u32 fixed2;
	u32 c;
	u32 d;
	u32 e;
पूर्ण;

#घोषणा SC1810C_CTL_LINE_SW	0
#घोषणा SC1810C_CTL_MUTE_SW	1
#घोषणा SC1810C_CTL_AB_SW	3
#घोषणा SC1810C_CTL_48V_SW	4

#घोषणा SC1810C_SET_STATE_REQ	161
#घोषणा SC1810C_SET_STATE_REQTYPE SC1810C_CMD_REQTYPE
#घोषणा SC1810C_SET_STATE_F1	0x64656D73
#घोषणा SC1810C_SET_STATE_F2	0xF4

#घोषणा SC1810C_GET_STATE_REQ	162
#घोषणा SC1810C_GET_STATE_REQTYPE \
	(USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN)
#घोषणा SC1810C_GET_STATE_F1	SC1810C_SET_STATE_F1
#घोषणा SC1810C_GET_STATE_F2	SC1810C_SET_STATE_F2

#घोषणा SC1810C_STATE_F1_IDX	2
#घोषणा SC1810C_STATE_F2_IDX	3

/*
 * This packet includes mixer volumes and
 * various other fields, it's an extended
 * version of ctl_packet, with a and b
 * being zero and dअगरferent f1/f2.
 */
काष्ठा s1810c_state_packet अणु
	u32 fields[63];
पूर्ण;

#घोषणा SC1810C_STATE_48V_SW	58
#घोषणा SC1810C_STATE_LINE_SW	59
#घोषणा SC1810C_STATE_MUTE_SW	60
#घोषणा SC1810C_STATE_AB_SW	62

काष्ठा s1810_mixer_state अणु
	uपूर्णांक16_t seqnum;
	काष्ठा mutex usb_mutex;
	काष्ठा mutex data_mutex;
पूर्ण;

अटल पूर्णांक
snd_s1810c_send_ctl_packet(काष्ठा usb_device *dev, u32 a,
			   u32 b, u32 c, u32 d, u32 e)
अणु
	काष्ठा s1810c_ctl_packet pkt = अणु 0 पूर्ण;
	पूर्णांक ret = 0;

	pkt.fixed1 = SC1810C_CMD_F1;
	pkt.fixed2 = SC1810C_CMD_F2;

	pkt.a = a;
	pkt.b = b;
	pkt.c = c;
	pkt.d = d;
	/*
	 * Value क्रम settings 0/1 क्रम this
	 * output channel is always 0 (probably because
	 * there is no ADAT output on 1810c)
	 */
	pkt.e = (c == 4) ? 0 : e;

	ret = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0),
			      SC1810C_CMD_REQ,
			      SC1810C_CMD_REQTYPE, 0, 0, &pkt, माप(pkt));
	अगर (ret < 0) अणु
		dev_warn(&dev->dev, "could not send ctl packet\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * When खोलोing Universal Control the program periodicaly
 * sends and receives state packets क्रम syncinc state between
 * the device and the host.
 *
 * Note that अगर we send only the request to get data back we'll
 * get an error, we need to first send an empty state packet and
 * then ask to receive a filled. Their seqnumbers must also match.
 */
अटल पूर्णांक
snd_sc1810c_get_status_field(काष्ठा usb_device *dev,
			     u32 *field, पूर्णांक field_idx, uपूर्णांक16_t *seqnum)
अणु
	काष्ठा s1810c_state_packet pkt_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा s1810c_state_packet pkt_in = अणु अणु 0 पूर्ण पूर्ण;
	पूर्णांक ret = 0;

	pkt_out.fields[SC1810C_STATE_F1_IDX] = SC1810C_SET_STATE_F1;
	pkt_out.fields[SC1810C_STATE_F2_IDX] = SC1810C_SET_STATE_F2;
	ret = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0),
			      SC1810C_SET_STATE_REQ,
			      SC1810C_SET_STATE_REQTYPE,
			      (*seqnum), 0, &pkt_out, माप(pkt_out));
	अगर (ret < 0) अणु
		dev_warn(&dev->dev, "could not send state packet (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0),
			      SC1810C_GET_STATE_REQ,
			      SC1810C_GET_STATE_REQTYPE,
			      (*seqnum), 0, &pkt_in, माप(pkt_in));
	अगर (ret < 0) अणु
		dev_warn(&dev->dev, "could not get state field %u (%d)\n",
			 field_idx, ret);
		वापस ret;
	पूर्ण

	(*field) = pkt_in.fields[field_idx];
	(*seqnum)++;
	वापस 0;
पूर्ण

/*
 * This is what I got when bypassing the mixer with
 * all channels split. I'm not 100% sure of what's going
 * on, I could probably clean this up based on my observations
 * but I prefer to keep the same behavior as the winकरोws driver.
 */
अटल पूर्णांक snd_s1810c_init_mixer_maps(काष्ठा snd_usb_audio *chip)
अणु
	u32 a, b, c, e, n, off;
	काष्ठा usb_device *dev = chip->dev;

	/* Set initial volume levels ? */
	a = 0x64;
	e = 0xbc;
	क्रम (n = 0; n < 2; n++) अणु
		off = n * 18;
		क्रम (b = off, c = 0; b < 18 + off; b++) अणु
			/* This channel to all outमाला_दो ? */
			क्रम (c = 0; c <= 8; c++) अणु
				snd_s1810c_send_ctl_packet(dev, a, b, c, 0, e);
				snd_s1810c_send_ctl_packet(dev, a, b, c, 1, e);
			पूर्ण
			/* This channel to मुख्य output (again) */
			snd_s1810c_send_ctl_packet(dev, a, b, 0, 0, e);
			snd_s1810c_send_ctl_packet(dev, a, b, 0, 1, e);
		पूर्ण
		/*
		 * I noticed on UC that DAW channels have dअगरferent
		 * initial volumes, so this makes sense.
		 */
		e = 0xb53bf0;
	पूर्ण

	/* Connect analog outमाला_दो ? */
	a = 0x65;
	e = 0x01000000;
	क्रम (b = 1; b < 3; b++) अणु
		snd_s1810c_send_ctl_packet(dev, a, b, 0, 0, e);
		snd_s1810c_send_ctl_packet(dev, a, b, 0, 1, e);
	पूर्ण
	snd_s1810c_send_ctl_packet(dev, a, 0, 0, 0, e);
	snd_s1810c_send_ctl_packet(dev, a, 0, 0, 1, e);

	/* Set initial volume levels क्रम S/PDIF mappings ? */
	a = 0x64;
	e = 0xbc;
	c = 3;
	क्रम (n = 0; n < 2; n++) अणु
		off = n * 18;
		क्रम (b = off; b < 18 + off; b++) अणु
			snd_s1810c_send_ctl_packet(dev, a, b, c, 0, e);
			snd_s1810c_send_ctl_packet(dev, a, b, c, 1, e);
		पूर्ण
		e = 0xb53bf0;
	पूर्ण

	/* Connect S/PDIF output ? */
	a = 0x65;
	e = 0x01000000;
	snd_s1810c_send_ctl_packet(dev, a, 3, 0, 0, e);
	snd_s1810c_send_ctl_packet(dev, a, 3, 0, 1, e);

	/* Connect all outमाला_दो (again) ? */
	a = 0x65;
	e = 0x01000000;
	क्रम (b = 0; b < 4; b++) अणु
		snd_s1810c_send_ctl_packet(dev, a, b, 0, 0, e);
		snd_s1810c_send_ctl_packet(dev, a, b, 0, 1, e);
	पूर्ण

	/* Basic routing to get sound out of the device */
	a = 0x64;
	e = 0x01000000;
	क्रम (c = 0; c < 4; c++) अणु
		क्रम (b = 0; b < 36; b++) अणु
			अगर ((c == 0 && b == 18) ||	/* DAW1/2 -> Main */
			    (c == 1 && b == 20) ||	/* DAW3/4 -> Line3/4 */
			    (c == 2 && b == 22) ||	/* DAW4/5 -> Line5/6 */
			    (c == 3 && b == 24)) अणु	/* DAW5/6 -> S/PDIF */
				/* Left */
				snd_s1810c_send_ctl_packet(dev, a, b, c, 0, e);
				snd_s1810c_send_ctl_packet(dev, a, b, c, 1, 0);
				b++;
				/* Right */
				snd_s1810c_send_ctl_packet(dev, a, b, c, 0, 0);
				snd_s1810c_send_ctl_packet(dev, a, b, c, 1, e);
			पूर्ण अन्यथा अणु
				/* Leave the rest disconnected */
				snd_s1810c_send_ctl_packet(dev, a, b, c, 0, 0);
				snd_s1810c_send_ctl_packet(dev, a, b, c, 1, 0);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Set initial volume levels क्रम S/PDIF (again) ? */
	a = 0x64;
	e = 0xbc;
	c = 3;
	क्रम (n = 0; n < 2; n++) अणु
		off = n * 18;
		क्रम (b = off; b < 18 + off; b++) अणु
			snd_s1810c_send_ctl_packet(dev, a, b, c, 0, e);
			snd_s1810c_send_ctl_packet(dev, a, b, c, 1, e);
		पूर्ण
		e = 0xb53bf0;
	पूर्ण

	/* Connect S/PDIF outमाला_दो (again) ? */
	a = 0x65;
	e = 0x01000000;
	snd_s1810c_send_ctl_packet(dev, a, 3, 0, 0, e);
	snd_s1810c_send_ctl_packet(dev, a, 3, 0, 1, e);

	/* Again ? */
	snd_s1810c_send_ctl_packet(dev, a, 3, 0, 0, e);
	snd_s1810c_send_ctl_packet(dev, a, 3, 0, 1, e);

	वापस 0;
पूर्ण

/*
 * Sync state with the device and retrieve the requested field,
 * whose index is specअगरied in (kctl->निजी_value & 0xFF),
 * from the received fields array.
 */
अटल पूर्णांक
snd_s1810c_get_चयन_state(काष्ठा usb_mixer_पूर्णांकerface *mixer,
			    काष्ठा snd_kcontrol *kctl, u32 *state)
अणु
	काष्ठा snd_usb_audio *chip = mixer->chip;
	काष्ठा s1810_mixer_state *निजी = mixer->निजी_data;
	u32 field = 0;
	u32 ctl_idx = (u32) (kctl->निजी_value & 0xFF);
	पूर्णांक ret = 0;

	mutex_lock(&निजी->usb_mutex);
	ret = snd_sc1810c_get_status_field(chip->dev, &field,
					   ctl_idx, &निजी->seqnum);
	अगर (ret < 0)
		जाओ unlock;

	*state = field;
 unlock:
	mutex_unlock(&निजी->usb_mutex);
	वापस ret ? ret : 0;
पूर्ण

/*
 * Send a control packet to the device क्रम the control id
 * specअगरied in (kctl->निजी_value >> 8) with value
 * specअगरied in (kctl->निजी_value >> 16).
 */
अटल पूर्णांक
snd_s1810c_set_चयन_state(काष्ठा usb_mixer_पूर्णांकerface *mixer,
			    काष्ठा snd_kcontrol *kctl)
अणु
	काष्ठा snd_usb_audio *chip = mixer->chip;
	काष्ठा s1810_mixer_state *निजी = mixer->निजी_data;
	u32 pval = (u32) kctl->निजी_value;
	u32 ctl_id = (pval >> 8) & 0xFF;
	u32 ctl_val = (pval >> 16) & 0x1;
	पूर्णांक ret = 0;

	mutex_lock(&निजी->usb_mutex);
	ret = snd_s1810c_send_ctl_packet(chip->dev, 0, 0, 0, ctl_id, ctl_val);
	mutex_unlock(&निजी->usb_mutex);
	वापस ret;
पूर्ण

/* Generic get/set/init functions क्रम चयन controls */

अटल पूर्णांक
snd_s1810c_चयन_get(काष्ठा snd_kcontrol *kctl,
		      काष्ठा snd_ctl_elem_value *ctl_elem)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kctl);
	काष्ठा usb_mixer_पूर्णांकerface *mixer = list->mixer;
	काष्ठा s1810_mixer_state *निजी = mixer->निजी_data;
	u32 pval = (u32) kctl->निजी_value;
	u32 ctl_idx = pval & 0xFF;
	u32 state = 0;
	पूर्णांक ret = 0;

	mutex_lock(&निजी->data_mutex);
	ret = snd_s1810c_get_चयन_state(mixer, kctl, &state);
	अगर (ret < 0)
		जाओ unlock;

	चयन (ctl_idx) अणु
	हाल SC1810C_STATE_LINE_SW:
	हाल SC1810C_STATE_AB_SW:
		ctl_elem->value.क्रमागतerated.item[0] = (पूर्णांक)state;
		अवरोध;
	शेष:
		ctl_elem->value.पूर्णांकeger.value[0] = (दीर्घ)state;
	पूर्ण

 unlock:
	mutex_unlock(&निजी->data_mutex);
	वापस (ret < 0) ? ret : 0;
पूर्ण

अटल पूर्णांक
snd_s1810c_चयन_set(काष्ठा snd_kcontrol *kctl,
		      काष्ठा snd_ctl_elem_value *ctl_elem)
अणु
	काष्ठा usb_mixer_elem_list *list = snd_kcontrol_chip(kctl);
	काष्ठा usb_mixer_पूर्णांकerface *mixer = list->mixer;
	काष्ठा s1810_mixer_state *निजी = mixer->निजी_data;
	u32 pval = (u32) kctl->निजी_value;
	u32 ctl_idx = pval & 0xFF;
	u32 curval = 0;
	u32 newval = 0;
	पूर्णांक ret = 0;

	mutex_lock(&निजी->data_mutex);
	ret = snd_s1810c_get_चयन_state(mixer, kctl, &curval);
	अगर (ret < 0)
		जाओ unlock;

	चयन (ctl_idx) अणु
	हाल SC1810C_STATE_LINE_SW:
	हाल SC1810C_STATE_AB_SW:
		newval = (u32) ctl_elem->value.क्रमागतerated.item[0];
		अवरोध;
	शेष:
		newval = (u32) ctl_elem->value.पूर्णांकeger.value[0];
	पूर्ण

	अगर (curval == newval)
		जाओ unlock;

	kctl->निजी_value &= ~(0x1 << 16);
	kctl->निजी_value |= (अचिन्हित पूर्णांक)(newval & 0x1) << 16;
	ret = snd_s1810c_set_चयन_state(mixer, kctl);

 unlock:
	mutex_unlock(&निजी->data_mutex);
	वापस (ret < 0) ? 0 : 1;
पूर्ण

अटल पूर्णांक
snd_s1810c_चयन_init(काष्ठा usb_mixer_पूर्णांकerface *mixer,
		       स्थिर काष्ठा snd_kcontrol_new *new_kctl)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा usb_mixer_elem_info *elem;

	elem = kzalloc(माप(काष्ठा usb_mixer_elem_info), GFP_KERNEL);
	अगर (!elem)
		वापस -ENOMEM;

	elem->head.mixer = mixer;
	elem->control = 0;
	elem->head.id = 0;
	elem->channels = 1;

	kctl = snd_ctl_new1(new_kctl, elem);
	अगर (!kctl) अणु
		kमुक्त(elem);
		वापस -ENOMEM;
	पूर्ण
	kctl->निजी_मुक्त = snd_usb_mixer_elem_मुक्त;

	वापस snd_usb_mixer_add_control(&elem->head, kctl);
पूर्ण

अटल पूर्णांक
snd_s1810c_line_sw_info(काष्ठा snd_kcontrol *kctl,
			काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[2] = अणु
		"Preamp On (Mic/Inst)",
		"Preamp Off (Line in)"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, ARRAY_SIZE(texts), texts);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_s1810c_line_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Line 1/2 Source Type",
	.info = snd_s1810c_line_sw_info,
	.get = snd_s1810c_चयन_get,
	.put = snd_s1810c_चयन_set,
	.निजी_value = (SC1810C_STATE_LINE_SW | SC1810C_CTL_LINE_SW << 8)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_s1810c_mute_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Mute Main Out Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = snd_s1810c_चयन_get,
	.put = snd_s1810c_चयन_set,
	.निजी_value = (SC1810C_STATE_MUTE_SW | SC1810C_CTL_MUTE_SW << 8)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_s1810c_48v_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "48V Phantom Power On Mic Inputs Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = snd_s1810c_चयन_get,
	.put = snd_s1810c_चयन_set,
	.निजी_value = (SC1810C_STATE_48V_SW | SC1810C_CTL_48V_SW << 8)
पूर्ण;

अटल पूर्णांक
snd_s1810c_ab_sw_info(काष्ठा snd_kcontrol *kctl,
		      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[2] = अणु
		"1/2",
		"3/4"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, ARRAY_SIZE(texts), texts);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_s1810c_ab_sw = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Headphone 1 Source Route",
	.info = snd_s1810c_ab_sw_info,
	.get = snd_s1810c_चयन_get,
	.put = snd_s1810c_चयन_set,
	.निजी_value = (SC1810C_STATE_AB_SW | SC1810C_CTL_AB_SW << 8)
पूर्ण;

अटल व्योम snd_sc1810_mixer_state_मुक्त(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	काष्ठा s1810_mixer_state *निजी = mixer->निजी_data;
	kमुक्त(निजी);
	mixer->निजी_data = शून्य;
पूर्ण

/* Entry poपूर्णांक, called from mixer_quirks.c */
पूर्णांक snd_sc1810_init_mixer(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	काष्ठा s1810_mixer_state *निजी = शून्य;
	काष्ठा snd_usb_audio *chip = mixer->chip;
	काष्ठा usb_device *dev = chip->dev;
	पूर्णांक ret = 0;

	/* Run this only once */
	अगर (!list_empty(&chip->mixer_list))
		वापस 0;

	dev_info(&dev->dev,
		 "Presonus Studio 1810c, device_setup: %u\n", chip->setup);
	अगर (chip->setup == 1)
		dev_info(&dev->dev, "(8out/18in @ 48kHz)\n");
	अन्यथा अगर (chip->setup == 2)
		dev_info(&dev->dev, "(6out/8in @ 192kHz)\n");
	अन्यथा
		dev_info(&dev->dev, "(8out/14in @ 96kHz)\n");

	ret = snd_s1810c_init_mixer_maps(chip);
	अगर (ret < 0)
		वापस ret;

	निजी = kzalloc(माप(काष्ठा s1810_mixer_state), GFP_KERNEL);
	अगर (!निजी)
		वापस -ENOMEM;

	mutex_init(&निजी->usb_mutex);
	mutex_init(&निजी->data_mutex);

	mixer->निजी_data = निजी;
	mixer->निजी_मुक्त = snd_sc1810_mixer_state_मुक्त;

	निजी->seqnum = 1;

	ret = snd_s1810c_चयन_init(mixer, &snd_s1810c_line_sw);
	अगर (ret < 0)
		वापस ret;

	ret = snd_s1810c_चयन_init(mixer, &snd_s1810c_mute_sw);
	अगर (ret < 0)
		वापस ret;

	ret = snd_s1810c_चयन_init(mixer, &snd_s1810c_48v_sw);
	अगर (ret < 0)
		वापस ret;

	ret = snd_s1810c_चयन_init(mixer, &snd_s1810c_ab_sw);
	अगर (ret < 0)
		वापस ret;
	वापस ret;
पूर्ण
