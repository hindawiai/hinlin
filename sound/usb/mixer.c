<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   (Tentative) USB Audio Driver क्रम ALSA
 *
 *   Mixer control part
 *
 *   Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 *
 *   Many codes borrowed from audio.c by
 *	    Alan Cox (alan@lxorguk.ukuu.org.uk)
 *	    Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 */

/*
 * TODOs, क्रम both the mixer and the streaming पूर्णांकerfaces:
 *
 *  - support क्रम UAC2 effect units
 *  - support क्रम graphical equalizers
 *  - RANGE and MEM set commands (UAC2)
 *  - RANGE and MEM पूर्णांकerrupt dispatchers (UAC2)
 *  - audio channel clustering (UAC2)
 *  - audio sample rate converter units (UAC2)
 *  - proper handling of घड़ी multipliers (UAC2)
 *  - dispatch घड़ी change notअगरications (UAC2)
 *  	- stop PCM streams which use a घड़ी that became invalid
 *  	- stop PCM streams which use a घड़ी selector that has changed
 *  	- parse available sample rates again when घड़ी sources changed
 */

#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/audio-v2.h>
#समावेश <linux/usb/audio-v3.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/info.h>
#समावेश <sound/tlv.h>

#समावेश "usbaudio.h"
#समावेश "mixer.h"
#समावेश "helper.h"
#समावेश "mixer_quirks.h"
#समावेश "power.h"

#घोषणा MAX_ID_ELEMS	256

काष्ठा usb_audio_term अणु
	पूर्णांक id;
	पूर्णांक type;
	पूर्णांक channels;
	अचिन्हित पूर्णांक chconfig;
	पूर्णांक name;
पूर्ण;

काष्ठा usbmix_name_map;

काष्ठा mixer_build अणु
	काष्ठा snd_usb_audio *chip;
	काष्ठा usb_mixer_पूर्णांकerface *mixer;
	अचिन्हित अक्षर *buffer;
	अचिन्हित पूर्णांक buflen;
	DECLARE_BITMAP(unitbiपंचांगap, MAX_ID_ELEMS);
	DECLARE_BITMAP(termbiपंचांगap, MAX_ID_ELEMS);
	काष्ठा usb_audio_term oterm;
	स्थिर काष्ठा usbmix_name_map *map;
	स्थिर काष्ठा usbmix_selector_map *selector_map;
पूर्ण;

/*E-mu 0202/0404/0204 eXtension Unit(XU) control*/
क्रमागत अणु
	USB_XU_CLOCK_RATE 		= 0xe301,
	USB_XU_CLOCK_SOURCE		= 0xe302,
	USB_XU_DIGITAL_IO_STATUS	= 0xe303,
	USB_XU_DEVICE_OPTIONS		= 0xe304,
	USB_XU_सूचीECT_MONITORING	= 0xe305,
	USB_XU_METERING			= 0xe306
पूर्ण;
क्रमागत अणु
	USB_XU_CLOCK_SOURCE_SELECTOR = 0x02,	/* घड़ी source*/
	USB_XU_CLOCK_RATE_SELECTOR = 0x03,	/* घड़ी rate */
	USB_XU_DIGITAL_FORMAT_SELECTOR = 0x01,	/* the spdअगर क्रमmat */
	USB_XU_SOFT_LIMIT_SELECTOR = 0x03	/* soft limiter */
पूर्ण;

/*
 * manual mapping of mixer names
 * अगर the mixer topology is too complicated and the parsed names are
 * ambiguous, add the entries in usbmixer_maps.c.
 */
#समावेश "mixer_maps.c"

अटल स्थिर काष्ठा usbmix_name_map *
find_map(स्थिर काष्ठा usbmix_name_map *p, पूर्णांक unitid, पूर्णांक control)
अणु
	अगर (!p)
		वापस शून्य;

	क्रम (; p->id; p++) अणु
		अगर (p->id == unitid &&
		    (!control || !p->control || control == p->control))
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

/* get the mapped name अगर the unit matches */
अटल पूर्णांक
check_mapped_name(स्थिर काष्ठा usbmix_name_map *p, अक्षर *buf, पूर्णांक buflen)
अणु
	पूर्णांक len;

	अगर (!p || !p->name)
		वापस 0;

	buflen--;
	len = strscpy(buf, p->name, buflen);
	वापस len < 0 ? buflen : len;
पूर्ण

/* ignore the error value अगर ignore_ctl_error flag is set */
#घोषणा filter_error(cval, err) \
	((cval)->head.mixer->ignore_ctl_error ? 0 : (err))

/* check whether the control should be ignored */
अटल अंतरभूत पूर्णांक
check_ignored_ctl(स्थिर काष्ठा usbmix_name_map *p)
अणु
	अगर (!p || p->name || p->dB)
		वापस 0;
	वापस 1;
पूर्ण

/* dB mapping */
अटल अंतरभूत व्योम check_mapped_dB(स्थिर काष्ठा usbmix_name_map *p,
				   काष्ठा usb_mixer_elem_info *cval)
अणु
	अगर (p && p->dB) अणु
		cval->dBmin = p->dB->min;
		cval->dBmax = p->dB->max;
		cval->initialized = 1;
	पूर्ण
पूर्ण

/* get the mapped selector source name */
अटल पूर्णांक check_mapped_selector_name(काष्ठा mixer_build *state, पूर्णांक unitid,
				      पूर्णांक index, अक्षर *buf, पूर्णांक buflen)
अणु
	स्थिर काष्ठा usbmix_selector_map *p;
	पूर्णांक len;

	अगर (!state->selector_map)
		वापस 0;
	क्रम (p = state->selector_map; p->id; p++) अणु
		अगर (p->id == unitid && index < p->count) अणु
			len = strscpy(buf, p->names[index], buflen);
			वापस len < 0 ? buflen : len;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * find an audio control unit with the given unit id
 */
अटल व्योम *find_audio_control_unit(काष्ठा mixer_build *state,
				     अचिन्हित अक्षर unit)
अणु
	/* we just parse the header */
	काष्ठा uac_feature_unit_descriptor *hdr = शून्य;

	जबतक ((hdr = snd_usb_find_desc(state->buffer, state->buflen, hdr,
					USB_DT_CS_INTERFACE)) != शून्य) अणु
		अगर (hdr->bLength >= 4 &&
		    hdr->bDescriptorSubtype >= UAC_INPUT_TERMINAL &&
		    hdr->bDescriptorSubtype <= UAC3_SAMPLE_RATE_CONVERTER &&
		    hdr->bUnitID == unit)
			वापस hdr;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * copy a string with the given id
 */
अटल पूर्णांक snd_usb_copy_string_desc(काष्ठा snd_usb_audio *chip,
				    पूर्णांक index, अक्षर *buf, पूर्णांक maxlen)
अणु
	पूर्णांक len = usb_string(chip->dev, index, buf, maxlen - 1);

	अगर (len < 0)
		वापस 0;

	buf[len] = 0;
	वापस len;
पूर्ण

/*
 * convert from the byte/word on usb descriptor to the zero-based पूर्णांकeger
 */
अटल पूर्णांक convert_चिन्हित_value(काष्ठा usb_mixer_elem_info *cval, पूर्णांक val)
अणु
	चयन (cval->val_type) अणु
	हाल USB_MIXER_BOOLEAN:
		वापस !!val;
	हाल USB_MIXER_INV_BOOLEAN:
		वापस !val;
	हाल USB_MIXER_U8:
		val &= 0xff;
		अवरोध;
	हाल USB_MIXER_S8:
		val &= 0xff;
		अगर (val >= 0x80)
			val -= 0x100;
		अवरोध;
	हाल USB_MIXER_U16:
		val &= 0xffff;
		अवरोध;
	हाल USB_MIXER_S16:
		val &= 0xffff;
		अगर (val >= 0x8000)
			val -= 0x10000;
		अवरोध;
	पूर्ण
	वापस val;
पूर्ण

/*
 * convert from the zero-based पूर्णांक to the byte/word क्रम usb descriptor
 */
अटल पूर्णांक convert_bytes_value(काष्ठा usb_mixer_elem_info *cval, पूर्णांक val)
अणु
	चयन (cval->val_type) अणु
	हाल USB_MIXER_BOOLEAN:
		वापस !!val;
	हाल USB_MIXER_INV_BOOLEAN:
		वापस !val;
	हाल USB_MIXER_S8:
	हाल USB_MIXER_U8:
		वापस val & 0xff;
	हाल USB_MIXER_S16:
	हाल USB_MIXER_U16:
		वापस val & 0xffff;
	पूर्ण
	वापस 0; /* not reached */
पूर्ण

अटल पूर्णांक get_relative_value(काष्ठा usb_mixer_elem_info *cval, पूर्णांक val)
अणु
	अगर (!cval->res)
		cval->res = 1;
	अगर (val < cval->min)
		वापस 0;
	अन्यथा अगर (val >= cval->max)
		वापस DIV_ROUND_UP(cval->max - cval->min, cval->res);
	अन्यथा
		वापस (val - cval->min) / cval->res;
पूर्ण

अटल पूर्णांक get_असल_value(काष्ठा usb_mixer_elem_info *cval, पूर्णांक val)
अणु
	अगर (val < 0)
		वापस cval->min;
	अगर (!cval->res)
		cval->res = 1;
	val *= cval->res;
	val += cval->min;
	अगर (val > cval->max)
		वापस cval->max;
	वापस val;
पूर्ण

अटल पूर्णांक uac2_ctl_value_size(पूर्णांक val_type)
अणु
	चयन (val_type) अणु
	हाल USB_MIXER_S32:
	हाल USB_MIXER_U32:
		वापस 4;
	हाल USB_MIXER_S16:
	हाल USB_MIXER_U16:
		वापस 2;
	शेष:
		वापस 1;
	पूर्ण
	वापस 0; /* unreachable */
पूर्ण


/*
 * retrieve a mixer value
 */

अटल अंतरभूत पूर्णांक mixer_ctrl_पूर्णांकf(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	वापस get_अगरace_desc(mixer->hostअगर)->bInterfaceNumber;
पूर्ण

अटल पूर्णांक get_ctl_value_v1(काष्ठा usb_mixer_elem_info *cval, पूर्णांक request,
			    पूर्णांक validx, पूर्णांक *value_ret)
अणु
	काष्ठा snd_usb_audio *chip = cval->head.mixer->chip;
	अचिन्हित अक्षर buf[2];
	पूर्णांक val_len = cval->val_type >= USB_MIXER_S16 ? 2 : 1;
	पूर्णांक समयout = 10;
	पूर्णांक idx = 0, err;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस -EIO;

	जबतक (समयout-- > 0) अणु
		idx = mixer_ctrl_पूर्णांकf(cval->head.mixer) | (cval->head.id << 8);
		err = snd_usb_ctl_msg(chip->dev, usb_rcvctrlpipe(chip->dev, 0), request,
				      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_IN,
				      validx, idx, buf, val_len);
		अगर (err >= val_len) अणु
			*value_ret = convert_चिन्हित_value(cval, snd_usb_combine_bytes(buf, val_len));
			err = 0;
			जाओ out;
		पूर्ण अन्यथा अगर (err == -ETIMEDOUT) अणु
			जाओ out;
		पूर्ण
	पूर्ण
	usb_audio_dbg(chip,
		"cannot get ctl value: req = %#x, wValue = %#x, wIndex = %#x, type = %d\n",
		request, validx, idx, cval->val_type);
	err = -EINVAL;

 out:
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक get_ctl_value_v2(काष्ठा usb_mixer_elem_info *cval, पूर्णांक request,
			    पूर्णांक validx, पूर्णांक *value_ret)
अणु
	काष्ठा snd_usb_audio *chip = cval->head.mixer->chip;
	/* enough space क्रम one range */
	अचिन्हित अक्षर buf[माप(__u16) + 3 * माप(__u32)];
	अचिन्हित अक्षर *val;
	पूर्णांक idx = 0, ret, val_size, size;
	__u8 bRequest;

	val_size = uac2_ctl_value_size(cval->val_type);

	अगर (request == UAC_GET_CUR) अणु
		bRequest = UAC2_CS_CUR;
		size = val_size;
	पूर्ण अन्यथा अणु
		bRequest = UAC2_CS_RANGE;
		size = माप(__u16) + 3 * val_size;
	पूर्ण

	स_रखो(buf, 0, माप(buf));

	ret = snd_usb_lock_shutकरोwn(chip) ? -EIO : 0;
	अगर (ret)
		जाओ error;

	idx = mixer_ctrl_पूर्णांकf(cval->head.mixer) | (cval->head.id << 8);
	ret = snd_usb_ctl_msg(chip->dev, usb_rcvctrlpipe(chip->dev, 0), bRequest,
			      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_IN,
			      validx, idx, buf, size);
	snd_usb_unlock_shutकरोwn(chip);

	अगर (ret < 0) अणु
error:
		usb_audio_err(chip,
			"cannot get ctl value: req = %#x, wValue = %#x, wIndex = %#x, type = %d\n",
			request, validx, idx, cval->val_type);
		वापस ret;
	पूर्ण

	/* FIXME: how should we handle multiple triplets here? */

	चयन (request) अणु
	हाल UAC_GET_CUR:
		val = buf;
		अवरोध;
	हाल UAC_GET_MIN:
		val = buf + माप(__u16);
		अवरोध;
	हाल UAC_GET_MAX:
		val = buf + माप(__u16) + val_size;
		अवरोध;
	हाल UAC_GET_RES:
		val = buf + माप(__u16) + val_size * 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*value_ret = convert_चिन्हित_value(cval,
					  snd_usb_combine_bytes(val, val_size));

	वापस 0;
पूर्ण

अटल पूर्णांक get_ctl_value(काष्ठा usb_mixer_elem_info *cval, पूर्णांक request,
			 पूर्णांक validx, पूर्णांक *value_ret)
अणु
	validx += cval->idx_off;

	वापस (cval->head.mixer->protocol == UAC_VERSION_1) ?
		get_ctl_value_v1(cval, request, validx, value_ret) :
		get_ctl_value_v2(cval, request, validx, value_ret);
पूर्ण

अटल पूर्णांक get_cur_ctl_value(काष्ठा usb_mixer_elem_info *cval,
			     पूर्णांक validx, पूर्णांक *value)
अणु
	वापस get_ctl_value(cval, UAC_GET_CUR, validx, value);
पूर्ण

/* channel = 0: master, 1 = first channel */
अटल अंतरभूत पूर्णांक get_cur_mix_raw(काष्ठा usb_mixer_elem_info *cval,
				  पूर्णांक channel, पूर्णांक *value)
अणु
	वापस get_ctl_value(cval, UAC_GET_CUR,
			     (cval->control << 8) | channel,
			     value);
पूर्ण

पूर्णांक snd_usb_get_cur_mix_value(काष्ठा usb_mixer_elem_info *cval,
			     पूर्णांक channel, पूर्णांक index, पूर्णांक *value)
अणु
	पूर्णांक err;

	अगर (cval->cached & (1 << channel)) अणु
		*value = cval->cache_val[index];
		वापस 0;
	पूर्ण
	err = get_cur_mix_raw(cval, channel, value);
	अगर (err < 0) अणु
		अगर (!cval->head.mixer->ignore_ctl_error)
			usb_audio_dbg(cval->head.mixer->chip,
				"cannot get current value for control %d ch %d: err = %d\n",
				      cval->control, channel, err);
		वापस err;
	पूर्ण
	cval->cached |= 1 << channel;
	cval->cache_val[index] = *value;
	वापस 0;
पूर्ण

/*
 * set a mixer value
 */

पूर्णांक snd_usb_mixer_set_ctl_value(काष्ठा usb_mixer_elem_info *cval,
				पूर्णांक request, पूर्णांक validx, पूर्णांक value_set)
अणु
	काष्ठा snd_usb_audio *chip = cval->head.mixer->chip;
	अचिन्हित अक्षर buf[4];
	पूर्णांक idx = 0, val_len, err, समयout = 10;

	validx += cval->idx_off;


	अगर (cval->head.mixer->protocol == UAC_VERSION_1) अणु
		val_len = cval->val_type >= USB_MIXER_S16 ? 2 : 1;
	पूर्ण अन्यथा अणु /* UAC_VERSION_2/3 */
		val_len = uac2_ctl_value_size(cval->val_type);

		/* FIXME */
		अगर (request != UAC_SET_CUR) अणु
			usb_audio_dbg(chip, "RANGE setting not yet supported\n");
			वापस -EINVAL;
		पूर्ण

		request = UAC2_CS_CUR;
	पूर्ण

	value_set = convert_bytes_value(cval, value_set);
	buf[0] = value_set & 0xff;
	buf[1] = (value_set >> 8) & 0xff;
	buf[2] = (value_set >> 16) & 0xff;
	buf[3] = (value_set >> 24) & 0xff;

	err = snd_usb_lock_shutकरोwn(chip);
	अगर (err < 0)
		वापस -EIO;

	जबतक (समयout-- > 0) अणु
		idx = mixer_ctrl_पूर्णांकf(cval->head.mixer) | (cval->head.id << 8);
		err = snd_usb_ctl_msg(chip->dev,
				      usb_sndctrlpipe(chip->dev, 0), request,
				      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_OUT,
				      validx, idx, buf, val_len);
		अगर (err >= 0) अणु
			err = 0;
			जाओ out;
		पूर्ण अन्यथा अगर (err == -ETIMEDOUT) अणु
			जाओ out;
		पूर्ण
	पूर्ण
	usb_audio_dbg(chip, "cannot set ctl value: req = %#x, wValue = %#x, wIndex = %#x, type = %d, data = %#x/%#x\n",
		      request, validx, idx, cval->val_type, buf[0], buf[1]);
	err = -EINVAL;

 out:
	snd_usb_unlock_shutकरोwn(chip);
	वापस err;
पूर्ण

अटल पूर्णांक set_cur_ctl_value(काष्ठा usb_mixer_elem_info *cval,
			     पूर्णांक validx, पूर्णांक value)
अणु
	वापस snd_usb_mixer_set_ctl_value(cval, UAC_SET_CUR, validx, value);
पूर्ण

पूर्णांक snd_usb_set_cur_mix_value(काष्ठा usb_mixer_elem_info *cval, पूर्णांक channel,
			     पूर्णांक index, पूर्णांक value)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक पढ़ो_only = (channel == 0) ?
		cval->master_पढ़ोonly :
		cval->ch_पढ़ोonly & (1 << (channel - 1));

	अगर (पढ़ो_only) अणु
		usb_audio_dbg(cval->head.mixer->chip,
			      "%s(): channel %d of control %d is read_only\n",
			    __func__, channel, cval->control);
		वापस 0;
	पूर्ण

	err = snd_usb_mixer_set_ctl_value(cval,
					  UAC_SET_CUR, (cval->control << 8) | channel,
					  value);
	अगर (err < 0)
		वापस err;
	cval->cached |= 1 << channel;
	cval->cache_val[index] = value;
	वापस 0;
पूर्ण

/*
 * TLV callback क्रम mixer volume controls
 */
पूर्णांक snd_usb_mixer_vol_tlv(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
			 अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *_tlv)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;
	DECLARE_TLV_DB_MINMAX(scale, 0, 0);

	अगर (size < माप(scale))
		वापस -ENOMEM;
	अगर (cval->min_mute)
		scale[0] = SNDRV_CTL_TLVT_DB_MINMAX_MUTE;
	scale[2] = cval->dBmin;
	scale[3] = cval->dBmax;
	अगर (copy_to_user(_tlv, scale, माप(scale)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * parser routines begin here...
 */

अटल पूर्णांक parse_audio_unit(काष्ठा mixer_build *state, पूर्णांक unitid);


/*
 * check अगर the input/output channel routing is enabled on the given biपंचांगap.
 * used क्रम mixer unit parser
 */
अटल पूर्णांक check_matrix_biपंचांगap(अचिन्हित अक्षर *bmap,
			       पूर्णांक ich, पूर्णांक och, पूर्णांक num_outs)
अणु
	पूर्णांक idx = ich * num_outs + och;
	वापस bmap[idx >> 3] & (0x80 >> (idx & 7));
पूर्ण

/*
 * add an alsa control element
 * search and increment the index until an empty slot is found.
 *
 * अगर failed, give up and मुक्त the control instance.
 */

पूर्णांक snd_usb_mixer_add_list(काष्ठा usb_mixer_elem_list *list,
			   काष्ठा snd_kcontrol *kctl,
			   bool is_std_info)
अणु
	काष्ठा usb_mixer_पूर्णांकerface *mixer = list->mixer;
	पूर्णांक err;

	जबतक (snd_ctl_find_id(mixer->chip->card, &kctl->id))
		kctl->id.index++;
	err = snd_ctl_add(mixer->chip->card, kctl);
	अगर (err < 0) अणु
		usb_audio_dbg(mixer->chip, "cannot add control (err = %d)\n",
			      err);
		वापस err;
	पूर्ण
	list->kctl = kctl;
	list->is_std_info = is_std_info;
	list->next_id_elem = mixer->id_elems[list->id];
	mixer->id_elems[list->id] = list;
	वापस 0;
पूर्ण

/*
 * get a terminal name string
 */

अटल काष्ठा iterm_name_combo अणु
	पूर्णांक type;
	अक्षर *name;
पूर्ण iterm_names[] = अणु
	अणु 0x0300, "Output" पूर्ण,
	अणु 0x0301, "Speaker" पूर्ण,
	अणु 0x0302, "Headphone" पूर्ण,
	अणु 0x0303, "HMD Audio" पूर्ण,
	अणु 0x0304, "Desktop Speaker" पूर्ण,
	अणु 0x0305, "Room Speaker" पूर्ण,
	अणु 0x0306, "Com Speaker" पूर्ण,
	अणु 0x0307, "LFE" पूर्ण,
	अणु 0x0600, "External In" पूर्ण,
	अणु 0x0601, "Analog In" पूर्ण,
	अणु 0x0602, "Digital In" पूर्ण,
	अणु 0x0603, "Line" पूर्ण,
	अणु 0x0604, "Legacy In" पूर्ण,
	अणु 0x0605, "IEC958 In" पूर्ण,
	अणु 0x0606, "1394 DA Stream" पूर्ण,
	अणु 0x0607, "1394 DV Stream" पूर्ण,
	अणु 0x0700, "Embedded" पूर्ण,
	अणु 0x0701, "Noise Source" पूर्ण,
	अणु 0x0702, "Equalization Noise" पूर्ण,
	अणु 0x0703, "CD" पूर्ण,
	अणु 0x0704, "DAT" पूर्ण,
	अणु 0x0705, "DCC" पूर्ण,
	अणु 0x0706, "MiniDisk" पूर्ण,
	अणु 0x0707, "Analog Tape" पूर्ण,
	अणु 0x0708, "Phonograph" पूर्ण,
	अणु 0x0709, "VCR Audio" पूर्ण,
	अणु 0x070a, "Video Disk Audio" पूर्ण,
	अणु 0x070b, "DVD Audio" पूर्ण,
	अणु 0x070c, "TV Tuner Audio" पूर्ण,
	अणु 0x070d, "Satellite Rec Audio" पूर्ण,
	अणु 0x070e, "Cable Tuner Audio" पूर्ण,
	अणु 0x070f, "DSS Audio" पूर्ण,
	अणु 0x0710, "Radio Receiver" पूर्ण,
	अणु 0x0711, "Radio Transmitter" पूर्ण,
	अणु 0x0712, "Multi-Track Recorder" पूर्ण,
	अणु 0x0713, "Synthesizer" पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल पूर्णांक get_term_name(काष्ठा snd_usb_audio *chip, काष्ठा usb_audio_term *iterm,
			 अचिन्हित अक्षर *name, पूर्णांक maxlen, पूर्णांक term_only)
अणु
	काष्ठा iterm_name_combo *names;
	पूर्णांक len;

	अगर (iterm->name) अणु
		len = snd_usb_copy_string_desc(chip, iterm->name,
						name, maxlen);
		अगर (len)
			वापस len;
	पूर्ण

	/* भव type - not a real terminal */
	अगर (iterm->type >> 16) अणु
		अगर (term_only)
			वापस 0;
		चयन (iterm->type >> 16) अणु
		हाल UAC3_SELECTOR_UNIT:
			म_नकल(name, "Selector");
			वापस 8;
		हाल UAC3_PROCESSING_UNIT:
			म_नकल(name, "Process Unit");
			वापस 12;
		हाल UAC3_EXTENSION_UNIT:
			म_नकल(name, "Ext Unit");
			वापस 8;
		हाल UAC3_MIXER_UNIT:
			म_नकल(name, "Mixer");
			वापस 5;
		शेष:
			वापस प्र_लिखो(name, "Unit %d", iterm->id);
		पूर्ण
	पूर्ण

	चयन (iterm->type & 0xff00) अणु
	हाल 0x0100:
		म_नकल(name, "PCM");
		वापस 3;
	हाल 0x0200:
		म_नकल(name, "Mic");
		वापस 3;
	हाल 0x0400:
		म_नकल(name, "Headset");
		वापस 7;
	हाल 0x0500:
		म_नकल(name, "Phone");
		वापस 5;
	पूर्ण

	क्रम (names = iterm_names; names->type; names++) अणु
		अगर (names->type == iterm->type) अणु
			म_नकल(name, names->name);
			वापस म_माप(names->name);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Get logical cluster inक्रमmation क्रम UAC3 devices.
 */
अटल पूर्णांक get_cluster_channels_v3(काष्ठा mixer_build *state, अचिन्हित पूर्णांक cluster_id)
अणु
	काष्ठा uac3_cluster_header_descriptor c_header;
	पूर्णांक err;

	err = snd_usb_ctl_msg(state->chip->dev,
			usb_rcvctrlpipe(state->chip->dev, 0),
			UAC3_CS_REQ_HIGH_CAPABILITY_DESCRIPTOR,
			USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_IN,
			cluster_id,
			snd_usb_ctrl_पूर्णांकf(state->chip),
			&c_header, माप(c_header));
	अगर (err < 0)
		जाओ error;
	अगर (err != माप(c_header)) अणु
		err = -EIO;
		जाओ error;
	पूर्ण

	वापस c_header.bNrChannels;

error:
	usb_audio_err(state->chip, "cannot request logical cluster ID: %d (err: %d)\n", cluster_id, err);
	वापस err;
पूर्ण

/*
 * Get number of channels क्रम a Mixer Unit.
 */
अटल पूर्णांक uac_mixer_unit_get_channels(काष्ठा mixer_build *state,
				       काष्ठा uac_mixer_unit_descriptor *desc)
अणु
	पूर्णांक mu_channels;

	चयन (state->mixer->protocol) अणु
	हाल UAC_VERSION_1:
	हाल UAC_VERSION_2:
	शेष:
		अगर (desc->bLength < माप(*desc) + desc->bNrInPins + 1)
			वापस 0; /* no bmControls -> skip */
		mu_channels = uac_mixer_unit_bNrChannels(desc);
		अवरोध;
	हाल UAC_VERSION_3:
		mu_channels = get_cluster_channels_v3(state,
				uac3_mixer_unit_wClusterDescrID(desc));
		अवरोध;
	पूर्ण

	वापस mu_channels;
पूर्ण

/*
 * Parse Input Terminal Unit
 */
अटल पूर्णांक __check_input_term(काष्ठा mixer_build *state, पूर्णांक id,
			      काष्ठा usb_audio_term *term);

अटल पूर्णांक parse_term_uac1_iterm_unit(काष्ठा mixer_build *state,
				      काष्ठा usb_audio_term *term,
				      व्योम *p1, पूर्णांक id)
अणु
	काष्ठा uac_input_terminal_descriptor *d = p1;

	term->type = le16_to_cpu(d->wTerminalType);
	term->channels = d->bNrChannels;
	term->chconfig = le16_to_cpu(d->wChannelConfig);
	term->name = d->iTerminal;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_term_uac2_iterm_unit(काष्ठा mixer_build *state,
				      काष्ठा usb_audio_term *term,
				      व्योम *p1, पूर्णांक id)
अणु
	काष्ठा uac2_input_terminal_descriptor *d = p1;
	पूर्णांक err;

	/* call recursively to verअगरy the referenced घड़ी entity */
	err = __check_input_term(state, d->bCSourceID, term);
	अगर (err < 0)
		वापस err;

	/* save input term properties after recursion,
	 * to ensure they are not overriden by the recursion calls
	 */
	term->id = id;
	term->type = le16_to_cpu(d->wTerminalType);
	term->channels = d->bNrChannels;
	term->chconfig = le32_to_cpu(d->bmChannelConfig);
	term->name = d->iTerminal;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_term_uac3_iterm_unit(काष्ठा mixer_build *state,
				      काष्ठा usb_audio_term *term,
				      व्योम *p1, पूर्णांक id)
अणु
	काष्ठा uac3_input_terminal_descriptor *d = p1;
	पूर्णांक err;

	/* call recursively to verअगरy the referenced घड़ी entity */
	err = __check_input_term(state, d->bCSourceID, term);
	अगर (err < 0)
		वापस err;

	/* save input term properties after recursion,
	 * to ensure they are not overriden by the recursion calls
	 */
	term->id = id;
	term->type = le16_to_cpu(d->wTerminalType);

	err = get_cluster_channels_v3(state, le16_to_cpu(d->wClusterDescrID));
	अगर (err < 0)
		वापस err;
	term->channels = err;

	/* REVISIT: UAC3 IT करोesn't have channels cfg */
	term->chconfig = 0;

	term->name = le16_to_cpu(d->wTerminalDescrStr);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_term_mixer_unit(काष्ठा mixer_build *state,
				 काष्ठा usb_audio_term *term,
				 व्योम *p1, पूर्णांक id)
अणु
	काष्ठा uac_mixer_unit_descriptor *d = p1;
	पूर्णांक protocol = state->mixer->protocol;
	पूर्णांक err;

	err = uac_mixer_unit_get_channels(state, d);
	अगर (err <= 0)
		वापस err;

	term->type = UAC3_MIXER_UNIT << 16; /* भव type */
	term->channels = err;
	अगर (protocol != UAC_VERSION_3) अणु
		term->chconfig = uac_mixer_unit_wChannelConfig(d, protocol);
		term->name = uac_mixer_unit_iMixer(d);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parse_term_selector_unit(काष्ठा mixer_build *state,
				    काष्ठा usb_audio_term *term,
				    व्योम *p1, पूर्णांक id)
अणु
	काष्ठा uac_selector_unit_descriptor *d = p1;
	पूर्णांक err;

	/* call recursively to retrieve the channel info */
	err = __check_input_term(state, d->baSourceID[0], term);
	अगर (err < 0)
		वापस err;
	term->type = UAC3_SELECTOR_UNIT << 16; /* भव type */
	term->id = id;
	अगर (state->mixer->protocol != UAC_VERSION_3)
		term->name = uac_selector_unit_iSelector(d);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_term_proc_unit(काष्ठा mixer_build *state,
				काष्ठा usb_audio_term *term,
				व्योम *p1, पूर्णांक id, पूर्णांक vtype)
अणु
	काष्ठा uac_processing_unit_descriptor *d = p1;
	पूर्णांक protocol = state->mixer->protocol;
	पूर्णांक err;

	अगर (d->bNrInPins) अणु
		/* call recursively to retrieve the channel info */
		err = __check_input_term(state, d->baSourceID[0], term);
		अगर (err < 0)
			वापस err;
	पूर्ण

	term->type = vtype << 16; /* भव type */
	term->id = id;

	अगर (protocol == UAC_VERSION_3)
		वापस 0;

	अगर (!term->channels) अणु
		term->channels = uac_processing_unit_bNrChannels(d);
		term->chconfig = uac_processing_unit_wChannelConfig(d, protocol);
	पूर्ण
	term->name = uac_processing_unit_iProcessing(d, protocol);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_term_effect_unit(काष्ठा mixer_build *state,
				  काष्ठा usb_audio_term *term,
				  व्योम *p1, पूर्णांक id)
अणु
	काष्ठा uac2_effect_unit_descriptor *d = p1;
	पूर्णांक err;

	err = __check_input_term(state, d->bSourceID, term);
	अगर (err < 0)
		वापस err;
	term->type = UAC3_EFFECT_UNIT << 16; /* भव type */
	term->id = id;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_term_uac2_घड़ी_source(काष्ठा mixer_build *state,
					काष्ठा usb_audio_term *term,
					व्योम *p1, पूर्णांक id)
अणु
	काष्ठा uac_घड़ी_source_descriptor *d = p1;

	term->type = UAC3_CLOCK_SOURCE << 16; /* भव type */
	term->id = id;
	term->name = d->iClockSource;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_term_uac3_घड़ी_source(काष्ठा mixer_build *state,
					काष्ठा usb_audio_term *term,
					व्योम *p1, पूर्णांक id)
अणु
	काष्ठा uac3_घड़ी_source_descriptor *d = p1;

	term->type = UAC3_CLOCK_SOURCE << 16; /* भव type */
	term->id = id;
	term->name = le16_to_cpu(d->wClockSourceStr);
	वापस 0;
पूर्ण

#घोषणा PTYPE(a, b)	((a) << 8 | (b))

/*
 * parse the source unit recursively until it reaches to a terminal
 * or a branched unit.
 */
अटल पूर्णांक __check_input_term(काष्ठा mixer_build *state, पूर्णांक id,
			      काष्ठा usb_audio_term *term)
अणु
	पूर्णांक protocol = state->mixer->protocol;
	व्योम *p1;
	अचिन्हित अक्षर *hdr;

	क्रम (;;) अणु
		/* a loop in the terminal chain? */
		अगर (test_and_set_bit(id, state->termbiपंचांगap))
			वापस -EINVAL;

		p1 = find_audio_control_unit(state, id);
		अगर (!p1)
			अवरोध;
		अगर (!snd_usb_validate_audio_desc(p1, protocol))
			अवरोध; /* bad descriptor */

		hdr = p1;
		term->id = id;

		चयन (PTYPE(protocol, hdr[2])) अणु
		हाल PTYPE(UAC_VERSION_1, UAC_FEATURE_UNIT):
		हाल PTYPE(UAC_VERSION_2, UAC_FEATURE_UNIT):
		हाल PTYPE(UAC_VERSION_3, UAC3_FEATURE_UNIT): अणु
			/* the header is the same क्रम all versions */
			काष्ठा uac_feature_unit_descriptor *d = p1;

			id = d->bSourceID;
			अवरोध; /* जारी to parse */
		पूर्ण
		हाल PTYPE(UAC_VERSION_1, UAC_INPUT_TERMINAL):
			वापस parse_term_uac1_iterm_unit(state, term, p1, id);
		हाल PTYPE(UAC_VERSION_2, UAC_INPUT_TERMINAL):
			वापस parse_term_uac2_iterm_unit(state, term, p1, id);
		हाल PTYPE(UAC_VERSION_3, UAC_INPUT_TERMINAL):
			वापस parse_term_uac3_iterm_unit(state, term, p1, id);
		हाल PTYPE(UAC_VERSION_1, UAC_MIXER_UNIT):
		हाल PTYPE(UAC_VERSION_2, UAC_MIXER_UNIT):
		हाल PTYPE(UAC_VERSION_3, UAC3_MIXER_UNIT):
			वापस parse_term_mixer_unit(state, term, p1, id);
		हाल PTYPE(UAC_VERSION_1, UAC_SELECTOR_UNIT):
		हाल PTYPE(UAC_VERSION_2, UAC_SELECTOR_UNIT):
		हाल PTYPE(UAC_VERSION_2, UAC2_CLOCK_SELECTOR):
		हाल PTYPE(UAC_VERSION_3, UAC3_SELECTOR_UNIT):
		हाल PTYPE(UAC_VERSION_3, UAC3_CLOCK_SELECTOR):
			वापस parse_term_selector_unit(state, term, p1, id);
		हाल PTYPE(UAC_VERSION_1, UAC1_PROCESSING_UNIT):
		हाल PTYPE(UAC_VERSION_2, UAC2_PROCESSING_UNIT_V2):
		हाल PTYPE(UAC_VERSION_3, UAC3_PROCESSING_UNIT):
			वापस parse_term_proc_unit(state, term, p1, id,
						    UAC3_PROCESSING_UNIT);
		हाल PTYPE(UAC_VERSION_2, UAC2_EFFECT_UNIT):
		हाल PTYPE(UAC_VERSION_3, UAC3_EFFECT_UNIT):
			वापस parse_term_effect_unit(state, term, p1, id);
		हाल PTYPE(UAC_VERSION_1, UAC1_EXTENSION_UNIT):
		हाल PTYPE(UAC_VERSION_2, UAC2_EXTENSION_UNIT_V2):
		हाल PTYPE(UAC_VERSION_3, UAC3_EXTENSION_UNIT):
			वापस parse_term_proc_unit(state, term, p1, id,
						    UAC3_EXTENSION_UNIT);
		हाल PTYPE(UAC_VERSION_2, UAC2_CLOCK_SOURCE):
			वापस parse_term_uac2_घड़ी_source(state, term, p1, id);
		हाल PTYPE(UAC_VERSION_3, UAC3_CLOCK_SOURCE):
			वापस parse_term_uac3_घड़ी_source(state, term, p1, id);
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण


अटल पूर्णांक check_input_term(काष्ठा mixer_build *state, पूर्णांक id,
			    काष्ठा usb_audio_term *term)
अणु
	स_रखो(term, 0, माप(*term));
	स_रखो(state->termbiपंचांगap, 0, माप(state->termbiपंचांगap));
	वापस __check_input_term(state, id, term);
पूर्ण

/*
 * Feature Unit
 */

/* feature unit control inक्रमmation */
काष्ठा usb_feature_control_info अणु
	पूर्णांक control;
	स्थिर अक्षर *name;
	पूर्णांक type;	/* data type क्रम uac1 */
	पूर्णांक type_uac2;	/* data type क्रम uac2 अगर dअगरferent from uac1, अन्यथा -1 */
पूर्ण;

अटल स्थिर काष्ठा usb_feature_control_info audio_feature_info[] = अणु
	अणु UAC_FU_MUTE,			"Mute",			USB_MIXER_INV_BOOLEAN, -1 पूर्ण,
	अणु UAC_FU_VOLUME,		"Volume",		USB_MIXER_S16, -1 पूर्ण,
	अणु UAC_FU_BASS,			"Tone Control - Bass",	USB_MIXER_S8, -1 पूर्ण,
	अणु UAC_FU_MID,			"Tone Control - Mid",	USB_MIXER_S8, -1 पूर्ण,
	अणु UAC_FU_TREBLE,		"Tone Control - Treble", USB_MIXER_S8, -1 पूर्ण,
	अणु UAC_FU_GRAPHIC_EQUALIZER,	"Graphic Equalizer",	USB_MIXER_S8, -1 पूर्ण, /* FIXME: not implemented yet */
	अणु UAC_FU_AUTOMATIC_GAIN,	"Auto Gain Control",	USB_MIXER_BOOLEAN, -1 पूर्ण,
	अणु UAC_FU_DELAY,			"Delay Control",	USB_MIXER_U16, USB_MIXER_U32 पूर्ण,
	अणु UAC_FU_BASS_BOOST,		"Bass Boost",		USB_MIXER_BOOLEAN, -1 पूर्ण,
	अणु UAC_FU_LOUDNESS,		"Loudness",		USB_MIXER_BOOLEAN, -1 पूर्ण,
	/* UAC2 specअगरic */
	अणु UAC2_FU_INPUT_GAIN,		"Input Gain Control",	USB_MIXER_S16, -1 पूर्ण,
	अणु UAC2_FU_INPUT_GAIN_PAD,	"Input Gain Pad Control", USB_MIXER_S16, -1 पूर्ण,
	अणु UAC2_FU_PHASE_INVERTER,	 "Phase Inverter Control", USB_MIXER_BOOLEAN, -1 पूर्ण,
पूर्ण;

अटल व्योम usb_mixer_elem_info_मुक्त(काष्ठा usb_mixer_elem_info *cval)
अणु
	kमुक्त(cval);
पूर्ण

/* निजी_मुक्त callback */
व्योम snd_usb_mixer_elem_मुक्त(काष्ठा snd_kcontrol *kctl)
अणु
	usb_mixer_elem_info_मुक्त(kctl->निजी_data);
	kctl->निजी_data = शून्य;
पूर्ण

/*
 * पूर्णांकerface to ALSA control क्रम feature/mixer units
 */

/* volume control quirks */
अटल व्योम volume_control_quirks(काष्ठा usb_mixer_elem_info *cval,
				  काष्ठा snd_kcontrol *kctl)
अणु
	काष्ठा snd_usb_audio *chip = cval->head.mixer->chip;
	चयन (chip->usb_id) अणु
	हाल USB_ID(0x0763, 0x2030): /* M-Audio Fast Track C400 */
	हाल USB_ID(0x0763, 0x2031): /* M-Audio Fast Track C600 */
		अगर (म_भेद(kctl->id.name, "Effect Duration") == 0) अणु
			cval->min = 0x0000;
			cval->max = 0xffff;
			cval->res = 0x00e6;
			अवरोध;
		पूर्ण
		अगर (म_भेद(kctl->id.name, "Effect Volume") == 0 ||
		    म_भेद(kctl->id.name, "Effect Feedback Volume") == 0) अणु
			cval->min = 0x00;
			cval->max = 0xff;
			अवरोध;
		पूर्ण
		अगर (म_माला(kctl->id.name, "Effect Return") != शून्य) अणु
			cval->min = 0xb706;
			cval->max = 0xff7b;
			cval->res = 0x0073;
			अवरोध;
		पूर्ण
		अगर ((म_माला(kctl->id.name, "Playback Volume") != शून्य) ||
			(म_माला(kctl->id.name, "Effect Send") != शून्य)) अणु
			cval->min = 0xb5fb; /* -73 dB = 0xb6ff */
			cval->max = 0xfcfe;
			cval->res = 0x0073;
		पूर्ण
		अवरोध;

	हाल USB_ID(0x0763, 0x2081): /* M-Audio Fast Track Ultra 8R */
	हाल USB_ID(0x0763, 0x2080): /* M-Audio Fast Track Ultra */
		अगर (म_भेद(kctl->id.name, "Effect Duration") == 0) अणु
			usb_audio_info(chip,
				       "set quirk for FTU Effect Duration\n");
			cval->min = 0x0000;
			cval->max = 0x7f00;
			cval->res = 0x0100;
			अवरोध;
		पूर्ण
		अगर (म_भेद(kctl->id.name, "Effect Volume") == 0 ||
		    म_भेद(kctl->id.name, "Effect Feedback Volume") == 0) अणु
			usb_audio_info(chip,
				       "set quirks for FTU Effect Feedback/Volume\n");
			cval->min = 0x00;
			cval->max = 0x7f;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल USB_ID(0x0d8c, 0x0103):
		अगर (!म_भेद(kctl->id.name, "PCM Playback Volume")) अणु
			usb_audio_info(chip,
				 "set volume quirk for CM102-A+/102S+\n");
			cval->min = -256;
		पूर्ण
		अवरोध;

	हाल USB_ID(0x0471, 0x0101):
	हाल USB_ID(0x0471, 0x0104):
	हाल USB_ID(0x0471, 0x0105):
	हाल USB_ID(0x0672, 0x1041):
	/* quirk क्रम UDA1321/N101.
	 * note that detection between firmware 2.1.1.7 (N101)
	 * and later 2.1.1.21 is not very clear from datasheets.
	 * I hope that the min value is -15360 क्रम newer firmware --jk
	 */
		अगर (!म_भेद(kctl->id.name, "PCM Playback Volume") &&
		    cval->min == -15616) अणु
			usb_audio_info(chip,
				 "set volume quirk for UDA1321/N101 chip\n");
			cval->max = -256;
		पूर्ण
		अवरोध;

	हाल USB_ID(0x046d, 0x09a4):
		अगर (!म_भेद(kctl->id.name, "Mic Capture Volume")) अणु
			usb_audio_info(chip,
				"set volume quirk for QuickCam E3500\n");
			cval->min = 6080;
			cval->max = 8768;
			cval->res = 192;
		पूर्ण
		अवरोध;

	हाल USB_ID(0x046d, 0x0807): /* Logitech Webcam C500 */
	हाल USB_ID(0x046d, 0x0808):
	हाल USB_ID(0x046d, 0x0809):
	हाल USB_ID(0x046d, 0x0819): /* Logitech Webcam C210 */
	हाल USB_ID(0x046d, 0x081b): /* HD Webcam c310 */
	हाल USB_ID(0x046d, 0x081d): /* HD Webcam c510 */
	हाल USB_ID(0x046d, 0x0825): /* HD Webcam c270 */
	हाल USB_ID(0x046d, 0x0826): /* HD Webcam c525 */
	हाल USB_ID(0x046d, 0x08ca): /* Logitech Quickcam Fusion */
	हाल USB_ID(0x046d, 0x0991):
	हाल USB_ID(0x046d, 0x09a2): /* QuickCam Communicate Deluxe/S7500 */
	/* Most audio usb devices lie about volume resolution.
	 * Most Logitech webcams have res = 384.
	 * Probably there is some logitech magic behind this number --fishor
	 */
		अगर (!म_भेद(kctl->id.name, "Mic Capture Volume")) अणु
			usb_audio_info(chip,
				"set resolution quirk: cval->res = 384\n");
			cval->res = 384;
		पूर्ण
		अवरोध;
	हाल USB_ID(0x0495, 0x3042): /* ESS Technology Asus USB DAC */
		अगर ((म_माला(kctl->id.name, "Playback Volume") != शून्य) ||
			म_माला(kctl->id.name, "Capture Volume") != शून्य) अणु
			cval->min >>= 8;
			cval->max = 0;
			cval->res = 1;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/*
 * retrieve the minimum and maximum values क्रम the specअगरied control
 */
अटल पूर्णांक get_min_max_with_quirks(काष्ठा usb_mixer_elem_info *cval,
				   पूर्णांक शेष_min, काष्ठा snd_kcontrol *kctl)
अणु
	/* क्रम failsafe */
	cval->min = शेष_min;
	cval->max = cval->min + 1;
	cval->res = 1;
	cval->dBmin = cval->dBmax = 0;

	अगर (cval->val_type == USB_MIXER_BOOLEAN ||
	    cval->val_type == USB_MIXER_INV_BOOLEAN) अणु
		cval->initialized = 1;
	पूर्ण अन्यथा अणु
		पूर्णांक minchn = 0;
		अगर (cval->cmask) अणु
			पूर्णांक i;
			क्रम (i = 0; i < MAX_CHANNELS; i++)
				अगर (cval->cmask & (1 << i)) अणु
					minchn = i + 1;
					अवरोध;
				पूर्ण
		पूर्ण
		अगर (get_ctl_value(cval, UAC_GET_MAX, (cval->control << 8) | minchn, &cval->max) < 0 ||
		    get_ctl_value(cval, UAC_GET_MIN, (cval->control << 8) | minchn, &cval->min) < 0) अणु
			usb_audio_err(cval->head.mixer->chip,
				      "%d:%d: cannot get min/max values for control %d (id %d)\n",
				   cval->head.id, mixer_ctrl_पूर्णांकf(cval->head.mixer),
							       cval->control, cval->head.id);
			वापस -EINVAL;
		पूर्ण
		अगर (get_ctl_value(cval, UAC_GET_RES,
				  (cval->control << 8) | minchn,
				  &cval->res) < 0) अणु
			cval->res = 1;
		पूर्ण अन्यथा अगर (cval->head.mixer->protocol == UAC_VERSION_1) अणु
			पूर्णांक last_valid_res = cval->res;

			जबतक (cval->res > 1) अणु
				अगर (snd_usb_mixer_set_ctl_value(cval, UAC_SET_RES,
								(cval->control << 8) | minchn,
								cval->res / 2) < 0)
					अवरोध;
				cval->res /= 2;
			पूर्ण
			अगर (get_ctl_value(cval, UAC_GET_RES,
					  (cval->control << 8) | minchn, &cval->res) < 0)
				cval->res = last_valid_res;
		पूर्ण
		अगर (cval->res == 0)
			cval->res = 1;

		/* Additional checks क्रम the proper resolution
		 *
		 * Some devices report smaller resolutions than actually
		 * reacting.  They करोn't वापस errors but simply clip
		 * to the lower aligned value.
		 */
		अगर (cval->min + cval->res < cval->max) अणु
			पूर्णांक last_valid_res = cval->res;
			पूर्णांक saved, test, check;
			अगर (get_cur_mix_raw(cval, minchn, &saved) < 0)
				जाओ no_res_check;
			क्रम (;;) अणु
				test = saved;
				अगर (test < cval->max)
					test += cval->res;
				अन्यथा
					test -= cval->res;
				अगर (test < cval->min || test > cval->max ||
				    snd_usb_set_cur_mix_value(cval, minchn, 0, test) ||
				    get_cur_mix_raw(cval, minchn, &check)) अणु
					cval->res = last_valid_res;
					अवरोध;
				पूर्ण
				अगर (test == check)
					अवरोध;
				cval->res *= 2;
			पूर्ण
			snd_usb_set_cur_mix_value(cval, minchn, 0, saved);
		पूर्ण

no_res_check:
		cval->initialized = 1;
	पूर्ण

	अगर (kctl)
		volume_control_quirks(cval, kctl);

	/* USB descriptions contain the dB scale in 1/256 dB unit
	 * जबतक ALSA TLV contains in 1/100 dB unit
	 */
	cval->dBmin = (convert_चिन्हित_value(cval, cval->min) * 100) / 256;
	cval->dBmax = (convert_चिन्हित_value(cval, cval->max) * 100) / 256;
	अगर (cval->dBmin > cval->dBmax) अणु
		/* something is wrong; assume it's either from/to 0dB */
		अगर (cval->dBmin < 0)
			cval->dBmax = 0;
		अन्यथा अगर (cval->dBmin > 0)
			cval->dBmin = 0;
		अगर (cval->dBmin > cval->dBmax) अणु
			/* totally crap, वापस an error */
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* अगर the max volume is too low, it's likely a bogus range;
		 * here we use -96dB as the threshold
		 */
		अगर (cval->dBmax <= -9600) अणु
			usb_audio_info(cval->head.mixer->chip,
				       "%d:%d: bogus dB values (%d/%d), disabling dB reporting\n",
				       cval->head.id, mixer_ctrl_पूर्णांकf(cval->head.mixer),
				       cval->dBmin, cval->dBmax);
			cval->dBmin = cval->dBmax = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा get_min_max(cval, def)	get_min_max_with_quirks(cval, def, शून्य)

/* get a feature/mixer unit info */
अटल पूर्णांक mixer_ctl_feature_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;

	अगर (cval->val_type == USB_MIXER_BOOLEAN ||
	    cval->val_type == USB_MIXER_INV_BOOLEAN)
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	अन्यथा
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = cval->channels;
	अगर (cval->val_type == USB_MIXER_BOOLEAN ||
	    cval->val_type == USB_MIXER_INV_BOOLEAN) अणु
		uinfo->value.पूर्णांकeger.min = 0;
		uinfo->value.पूर्णांकeger.max = 1;
	पूर्ण अन्यथा अणु
		अगर (!cval->initialized) अणु
			get_min_max_with_quirks(cval, 0, kcontrol);
			अगर (cval->initialized && cval->dBmin >= cval->dBmax) अणु
				kcontrol->vd[0].access &= 
					~(SNDRV_CTL_ELEM_ACCESS_TLV_READ |
					  SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK);
				snd_ctl_notअगरy(cval->head.mixer->chip->card,
					       SNDRV_CTL_EVENT_MASK_INFO,
					       &kcontrol->id);
			पूर्ण
		पूर्ण
		uinfo->value.पूर्णांकeger.min = 0;
		uinfo->value.पूर्णांकeger.max =
			DIV_ROUND_UP(cval->max - cval->min, cval->res);
	पूर्ण
	वापस 0;
पूर्ण

/* get the current value from feature/mixer unit */
अटल पूर्णांक mixer_ctl_feature_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;
	पूर्णांक c, cnt, val, err;

	ucontrol->value.पूर्णांकeger.value[0] = cval->min;
	अगर (cval->cmask) अणु
		cnt = 0;
		क्रम (c = 0; c < MAX_CHANNELS; c++) अणु
			अगर (!(cval->cmask & (1 << c)))
				जारी;
			err = snd_usb_get_cur_mix_value(cval, c + 1, cnt, &val);
			अगर (err < 0)
				वापस filter_error(cval, err);
			val = get_relative_value(cval, val);
			ucontrol->value.पूर्णांकeger.value[cnt] = val;
			cnt++;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अणु
		/* master channel */
		err = snd_usb_get_cur_mix_value(cval, 0, 0, &val);
		अगर (err < 0)
			वापस filter_error(cval, err);
		val = get_relative_value(cval, val);
		ucontrol->value.पूर्णांकeger.value[0] = val;
	पूर्ण
	वापस 0;
पूर्ण

/* put the current value to feature/mixer unit */
अटल पूर्णांक mixer_ctl_feature_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;
	पूर्णांक c, cnt, val, oval, err;
	पूर्णांक changed = 0;

	अगर (cval->cmask) अणु
		cnt = 0;
		क्रम (c = 0; c < MAX_CHANNELS; c++) अणु
			अगर (!(cval->cmask & (1 << c)))
				जारी;
			err = snd_usb_get_cur_mix_value(cval, c + 1, cnt, &oval);
			अगर (err < 0)
				वापस filter_error(cval, err);
			val = ucontrol->value.पूर्णांकeger.value[cnt];
			val = get_असल_value(cval, val);
			अगर (oval != val) अणु
				snd_usb_set_cur_mix_value(cval, c + 1, cnt, val);
				changed = 1;
			पूर्ण
			cnt++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* master channel */
		err = snd_usb_get_cur_mix_value(cval, 0, 0, &oval);
		अगर (err < 0)
			वापस filter_error(cval, err);
		val = ucontrol->value.पूर्णांकeger.value[0];
		val = get_असल_value(cval, val);
		अगर (val != oval) अणु
			snd_usb_set_cur_mix_value(cval, 0, 0, val);
			changed = 1;
		पूर्ण
	पूर्ण
	वापस changed;
पूर्ण

/* get the boolean value from the master channel of a UAC control */
अटल पूर्णांक mixer_ctl_master_bool_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;
	पूर्णांक val, err;

	err = snd_usb_get_cur_mix_value(cval, 0, 0, &val);
	अगर (err < 0)
		वापस filter_error(cval, err);
	val = (val != 0);
	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक get_connector_value(काष्ठा usb_mixer_elem_info *cval,
			       अक्षर *name, पूर्णांक *val)
अणु
	काष्ठा snd_usb_audio *chip = cval->head.mixer->chip;
	पूर्णांक idx = 0, validx, ret;

	validx = cval->control << 8 | 0;

	ret = snd_usb_lock_shutकरोwn(chip) ? -EIO : 0;
	अगर (ret)
		जाओ error;

	idx = mixer_ctrl_पूर्णांकf(cval->head.mixer) | (cval->head.id << 8);
	अगर (cval->head.mixer->protocol == UAC_VERSION_2) अणु
		काष्ठा uac2_connectors_ctl_blk uac2_conn;

		ret = snd_usb_ctl_msg(chip->dev, usb_rcvctrlpipe(chip->dev, 0), UAC2_CS_CUR,
				      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_IN,
				      validx, idx, &uac2_conn, माप(uac2_conn));
		अगर (val)
			*val = !!uac2_conn.bNrChannels;
	पूर्ण अन्यथा अणु /* UAC_VERSION_3 */
		काष्ठा uac3_insertion_ctl_blk uac3_conn;

		ret = snd_usb_ctl_msg(chip->dev, usb_rcvctrlpipe(chip->dev, 0), UAC2_CS_CUR,
				      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_IN,
				      validx, idx, &uac3_conn, माप(uac3_conn));
		अगर (val)
			*val = !!uac3_conn.bmConInserted;
	पूर्ण

	snd_usb_unlock_shutकरोwn(chip);

	अगर (ret < 0) अणु
		अगर (name && म_माला(name, "Speaker")) अणु
			अगर (val)
				*val = 1;
			वापस 0;
		पूर्ण
error:
		usb_audio_err(chip,
			"cannot get connectors status: req = %#x, wValue = %#x, wIndex = %#x, type = %d\n",
			UAC_GET_CUR, validx, idx, cval->val_type);
		वापस filter_error(cval, ret);
	पूर्ण

	वापस ret;
पूर्ण

/* get the connectors status and report it as boolean type */
अटल पूर्णांक mixer_ctl_connector_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;
	पूर्णांक ret, val;

	ret = get_connector_value(cval, kcontrol->id.name, &val);

	अगर (ret < 0)
		वापस ret;

	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new usb_feature_unit_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "", /* will be filled later manually */
	.info = mixer_ctl_feature_info,
	.get = mixer_ctl_feature_get,
	.put = mixer_ctl_feature_put,
पूर्ण;

/* the पढ़ो-only variant */
अटल स्थिर काष्ठा snd_kcontrol_new usb_feature_unit_ctl_ro = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "", /* will be filled later manually */
	.info = mixer_ctl_feature_info,
	.get = mixer_ctl_feature_get,
	.put = शून्य,
पूर्ण;

/*
 * A control which shows the boolean value from पढ़ोing a UAC control on
 * the master channel.
 */
अटल स्थिर काष्ठा snd_kcontrol_new usb_bool_master_control_ctl_ro = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.name = "", /* will be filled later manually */
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = snd_ctl_boolean_mono_info,
	.get = mixer_ctl_master_bool_get,
	.put = शून्य,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new usb_connector_ctl_ro = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.name = "", /* will be filled later manually */
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = snd_ctl_boolean_mono_info,
	.get = mixer_ctl_connector_get,
	.put = शून्य,
पूर्ण;

/*
 * This symbol is exported in order to allow the mixer quirks to
 * hook up to the standard feature unit control mechanism
 */
स्थिर काष्ठा snd_kcontrol_new *snd_usb_feature_unit_ctl = &usb_feature_unit_ctl;

/*
 * build a feature control
 */
अटल माप_प्रकार append_ctl_name(काष्ठा snd_kcontrol *kctl, स्थिर अक्षर *str)
अणु
	वापस strlcat(kctl->id.name, str, माप(kctl->id.name));
पूर्ण

/*
 * A lot of headsets/headphones have a "Speaker" mixer. Make sure we
 * नाम it to "Headphone". We determine अगर something is a headphone
 * similar to how udev determines क्रमm factor.
 */
अटल व्योम check_no_speaker_on_headset(काष्ठा snd_kcontrol *kctl,
					काष्ठा snd_card *card)
अणु
	स्थिर अक्षर *names_to_check[] = अणु
		"Headset", "headset", "Headphone", "headphone", शून्यपूर्ण;
	स्थिर अक्षर **s;
	bool found = false;

	अगर (म_भेद("Speaker", kctl->id.name))
		वापस;

	क्रम (s = names_to_check; *s; s++)
		अगर (म_माला(card->लघुname, *s)) अणु
			found = true;
			अवरोध;
		पूर्ण

	अगर (!found)
		वापस;

	strscpy(kctl->id.name, "Headphone", माप(kctl->id.name));
पूर्ण

अटल स्थिर काष्ठा usb_feature_control_info *get_feature_control_info(पूर्णांक control)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(audio_feature_info); ++i) अणु
		अगर (audio_feature_info[i].control == control)
			वापस &audio_feature_info[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __build_feature_ctl(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				स्थिर काष्ठा usbmix_name_map *imap,
				अचिन्हित पूर्णांक ctl_mask, पूर्णांक control,
				काष्ठा usb_audio_term *iterm,
				काष्ठा usb_audio_term *oterm,
				पूर्णांक unitid, पूर्णांक nameid, पूर्णांक पढ़ोonly_mask)
अणु
	स्थिर काष्ठा usb_feature_control_info *ctl_info;
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक mapped_name = 0;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा usb_mixer_elem_info *cval;
	स्थिर काष्ठा usbmix_name_map *map;
	अचिन्हित पूर्णांक range;

	अगर (control == UAC_FU_GRAPHIC_EQUALIZER) अणु
		/* FIXME: not supported yet */
		वापस;
	पूर्ण

	map = find_map(imap, unitid, control);
	अगर (check_ignored_ctl(map))
		वापस;

	cval = kzalloc(माप(*cval), GFP_KERNEL);
	अगर (!cval)
		वापस;
	snd_usb_mixer_elem_init_std(&cval->head, mixer, unitid);
	cval->control = control;
	cval->cmask = ctl_mask;

	ctl_info = get_feature_control_info(control);
	अगर (!ctl_info) अणु
		usb_mixer_elem_info_मुक्त(cval);
		वापस;
	पूर्ण
	अगर (mixer->protocol == UAC_VERSION_1)
		cval->val_type = ctl_info->type;
	अन्यथा /* UAC_VERSION_2 */
		cval->val_type = ctl_info->type_uac2 >= 0 ?
			ctl_info->type_uac2 : ctl_info->type;

	अगर (ctl_mask == 0) अणु
		cval->channels = 1;	/* master channel */
		cval->master_पढ़ोonly = पढ़ोonly_mask;
	पूर्ण अन्यथा अणु
		पूर्णांक i, c = 0;
		क्रम (i = 0; i < 16; i++)
			अगर (ctl_mask & (1 << i))
				c++;
		cval->channels = c;
		cval->ch_पढ़ोonly = पढ़ोonly_mask;
	पूर्ण

	/*
	 * If all channels in the mask are marked पढ़ो-only, make the control
	 * पढ़ो-only. snd_usb_set_cur_mix_value() will check the mask again and won't
	 * issue ग_लिखो commands to पढ़ो-only channels.
	 */
	अगर (cval->channels == पढ़ोonly_mask)
		kctl = snd_ctl_new1(&usb_feature_unit_ctl_ro, cval);
	अन्यथा
		kctl = snd_ctl_new1(&usb_feature_unit_ctl, cval);

	अगर (!kctl) अणु
		usb_audio_err(mixer->chip, "cannot malloc kcontrol\n");
		usb_mixer_elem_info_मुक्त(cval);
		वापस;
	पूर्ण
	kctl->निजी_मुक्त = snd_usb_mixer_elem_मुक्त;

	len = check_mapped_name(map, kctl->id.name, माप(kctl->id.name));
	mapped_name = len != 0;
	अगर (!len && nameid)
		len = snd_usb_copy_string_desc(mixer->chip, nameid,
				kctl->id.name, माप(kctl->id.name));

	चयन (control) अणु
	हाल UAC_FU_MUTE:
	हाल UAC_FU_VOLUME:
		/*
		 * determine the control name.  the rule is:
		 * - अगर a name id is given in descriptor, use it.
		 * - अगर the connected input can be determined, then use the name
		 *   of terminal type.
		 * - अगर the connected output can be determined, use it.
		 * - otherwise, anonymous name.
		 */
		अगर (!len) अणु
			अगर (iterm)
				len = get_term_name(mixer->chip, iterm,
						    kctl->id.name,
						    माप(kctl->id.name), 1);
			अगर (!len && oterm)
				len = get_term_name(mixer->chip, oterm,
						    kctl->id.name,
						    माप(kctl->id.name), 1);
			अगर (!len)
				snम_लिखो(kctl->id.name, माप(kctl->id.name),
					 "Feature %d", unitid);
		पूर्ण

		अगर (!mapped_name)
			check_no_speaker_on_headset(kctl, mixer->chip->card);

		/*
		 * determine the stream direction:
		 * अगर the connected output is USB stream, then it's likely a
		 * capture stream.  otherwise it should be playback (hopefully :)
		 */
		अगर (!mapped_name && oterm && !(oterm->type >> 16)) अणु
			अगर ((oterm->type & 0xff00) == 0x0100)
				append_ctl_name(kctl, " Capture");
			अन्यथा
				append_ctl_name(kctl, " Playback");
		पूर्ण
		append_ctl_name(kctl, control == UAC_FU_MUTE ?
				" Switch" : " Volume");
		अवरोध;
	शेष:
		अगर (!len)
			strscpy(kctl->id.name, audio_feature_info[control-1].name,
				माप(kctl->id.name));
		अवरोध;
	पूर्ण

	/* get min/max values */
	get_min_max_with_quirks(cval, 0, kctl);

	/* skip a bogus volume range */
	अगर (cval->max <= cval->min) अणु
		usb_audio_dbg(mixer->chip,
			      "[%d] FU [%s] skipped due to invalid volume\n",
			      cval->head.id, kctl->id.name);
		snd_ctl_मुक्त_one(kctl);
		वापस;
	पूर्ण


	अगर (control == UAC_FU_VOLUME) अणु
		check_mapped_dB(map, cval);
		अगर (cval->dBmin < cval->dBmax || !cval->initialized) अणु
			kctl->tlv.c = snd_usb_mixer_vol_tlv;
			kctl->vd[0].access |=
				SNDRV_CTL_ELEM_ACCESS_TLV_READ |
				SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK;
		पूर्ण
	पूर्ण

	snd_usb_mixer_fu_apply_quirk(mixer, cval, unitid, kctl);

	range = (cval->max - cval->min) / cval->res;
	/*
	 * Are there devices with volume range more than 255? I use a bit more
	 * to be sure. 384 is a resolution magic number found on Logitech
	 * devices. It will definitively catch all buggy Logitech devices.
	 */
	अगर (range > 384) अणु
		usb_audio_warn(mixer->chip,
			       "Warning! Unlikely big volume range (=%u), cval->res is probably wrong.",
			       range);
		usb_audio_warn(mixer->chip,
			       "[%d] FU [%s] ch = %d, val = %d/%d/%d",
			       cval->head.id, kctl->id.name, cval->channels,
			       cval->min, cval->max, cval->res);
	पूर्ण

	usb_audio_dbg(mixer->chip, "[%d] FU [%s] ch = %d, val = %d/%d/%d\n",
		      cval->head.id, kctl->id.name, cval->channels,
		      cval->min, cval->max, cval->res);
	snd_usb_mixer_add_control(&cval->head, kctl);
पूर्ण

अटल व्योम build_feature_ctl(काष्ठा mixer_build *state, व्योम *raw_desc,
			      अचिन्हित पूर्णांक ctl_mask, पूर्णांक control,
			      काष्ठा usb_audio_term *iterm, पूर्णांक unitid,
			      पूर्णांक पढ़ोonly_mask)
अणु
	काष्ठा uac_feature_unit_descriptor *desc = raw_desc;
	पूर्णांक nameid = uac_feature_unit_iFeature(desc);

	__build_feature_ctl(state->mixer, state->map, ctl_mask, control,
			iterm, &state->oterm, unitid, nameid, पढ़ोonly_mask);
पूर्ण

अटल व्योम build_feature_ctl_badd(काष्ठा usb_mixer_पूर्णांकerface *mixer,
			      अचिन्हित पूर्णांक ctl_mask, पूर्णांक control, पूर्णांक unitid,
			      स्थिर काष्ठा usbmix_name_map *badd_map)
अणु
	__build_feature_ctl(mixer, badd_map, ctl_mask, control,
			शून्य, शून्य, unitid, 0, 0);
पूर्ण

अटल व्योम get_connector_control_name(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				       काष्ठा usb_audio_term *term,
				       bool is_input, अक्षर *name, पूर्णांक name_size)
अणु
	पूर्णांक name_len = get_term_name(mixer->chip, term, name, name_size, 0);

	अगर (name_len == 0)
		strscpy(name, "Unknown", name_size);

	/*
	 *  sound/core/ctljack.c has a convention of naming jack controls
	 * by ending in " Jack".  Make it slightly more useful by
	 * indicating Input or Output after the terminal name.
	 */
	अगर (is_input)
		strlcat(name, " - Input Jack", name_size);
	अन्यथा
		strlcat(name, " - Output Jack", name_size);
पूर्ण

/* Build a mixer control क्रम a UAC connector control (jack-detect) */
अटल व्योम build_connector_control(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				    स्थिर काष्ठा usbmix_name_map *imap,
				    काष्ठा usb_audio_term *term, bool is_input)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा usb_mixer_elem_info *cval;
	स्थिर काष्ठा usbmix_name_map *map;

	map = find_map(imap, term->id, 0);
	अगर (check_ignored_ctl(map))
		वापस;

	cval = kzalloc(माप(*cval), GFP_KERNEL);
	अगर (!cval)
		वापस;
	snd_usb_mixer_elem_init_std(&cval->head, mixer, term->id);
	/*
	 * UAC2: The first byte from पढ़ोing the UAC2_TE_CONNECTOR control वापसs the
	 * number of channels connected.
	 *
	 * UAC3: The first byte specअगरies size of biपंचांगap क्रम the inserted controls. The
	 * following byte(s) specअगरies which connectors are inserted.
	 *
	 * This boolean ctl will simply report अगर any channels are connected
	 * or not.
	 */
	अगर (mixer->protocol == UAC_VERSION_2)
		cval->control = UAC2_TE_CONNECTOR;
	अन्यथा /* UAC_VERSION_3 */
		cval->control = UAC3_TE_INSERTION;

	cval->val_type = USB_MIXER_BOOLEAN;
	cval->channels = 1; /* report true अगर any channel is connected */
	cval->min = 0;
	cval->max = 1;
	kctl = snd_ctl_new1(&usb_connector_ctl_ro, cval);
	अगर (!kctl) अणु
		usb_audio_err(mixer->chip, "cannot malloc kcontrol\n");
		usb_mixer_elem_info_मुक्त(cval);
		वापस;
	पूर्ण

	अगर (check_mapped_name(map, kctl->id.name, माप(kctl->id.name)))
		strlcat(kctl->id.name, " Jack", माप(kctl->id.name));
	अन्यथा
		get_connector_control_name(mixer, term, is_input, kctl->id.name,
					   माप(kctl->id.name));
	kctl->निजी_मुक्त = snd_usb_mixer_elem_मुक्त;
	snd_usb_mixer_add_control(&cval->head, kctl);
पूर्ण

अटल पूर्णांक parse_घड़ी_source_unit(काष्ठा mixer_build *state, पूर्णांक unitid,
				   व्योम *_ftr)
अणु
	काष्ठा uac_घड़ी_source_descriptor *hdr = _ftr;
	काष्ठा usb_mixer_elem_info *cval;
	काष्ठा snd_kcontrol *kctl;
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	पूर्णांक ret;

	अगर (state->mixer->protocol != UAC_VERSION_2)
		वापस -EINVAL;

	/*
	 * The only property of this unit we are पूर्णांकerested in is the
	 * घड़ी source validity. If that isn't पढ़ोable, just bail out.
	 */
	अगर (!uac_v2v3_control_is_पढ़ोable(hdr->bmControls,
				      UAC2_CS_CONTROL_CLOCK_VALID))
		वापस 0;

	cval = kzalloc(माप(*cval), GFP_KERNEL);
	अगर (!cval)
		वापस -ENOMEM;

	snd_usb_mixer_elem_init_std(&cval->head, state->mixer, hdr->bClockID);

	cval->min = 0;
	cval->max = 1;
	cval->channels = 1;
	cval->val_type = USB_MIXER_BOOLEAN;
	cval->control = UAC2_CS_CONTROL_CLOCK_VALID;

	cval->master_पढ़ोonly = 1;
	/* From UAC2 5.2.5.1.2 "Only the get request is supported." */
	kctl = snd_ctl_new1(&usb_bool_master_control_ctl_ro, cval);

	अगर (!kctl) अणु
		usb_mixer_elem_info_मुक्त(cval);
		वापस -ENOMEM;
	पूर्ण

	kctl->निजी_मुक्त = snd_usb_mixer_elem_मुक्त;
	ret = snd_usb_copy_string_desc(state->chip, hdr->iClockSource,
				       name, माप(name));
	अगर (ret > 0)
		snम_लिखो(kctl->id.name, माप(kctl->id.name),
			 "%s Validity", name);
	अन्यथा
		snम_लिखो(kctl->id.name, माप(kctl->id.name),
			 "Clock Source %d Validity", hdr->bClockID);

	वापस snd_usb_mixer_add_control(&cval->head, kctl);
पूर्ण

/*
 * parse a feature unit
 *
 * most of controls are defined here.
 */
अटल पूर्णांक parse_audio_feature_unit(काष्ठा mixer_build *state, पूर्णांक unitid,
				    व्योम *_ftr)
अणु
	पूर्णांक channels, i, j;
	काष्ठा usb_audio_term iterm;
	अचिन्हित पूर्णांक master_bits;
	पूर्णांक err, csize;
	काष्ठा uac_feature_unit_descriptor *hdr = _ftr;
	__u8 *bmaControls;

	अगर (state->mixer->protocol == UAC_VERSION_1) अणु
		csize = hdr->bControlSize;
		channels = (hdr->bLength - 7) / csize - 1;
		bmaControls = hdr->bmaControls;
	पूर्ण अन्यथा अगर (state->mixer->protocol == UAC_VERSION_2) अणु
		काष्ठा uac2_feature_unit_descriptor *ftr = _ftr;
		csize = 4;
		channels = (hdr->bLength - 6) / 4 - 1;
		bmaControls = ftr->bmaControls;
	पूर्ण अन्यथा अणु /* UAC_VERSION_3 */
		काष्ठा uac3_feature_unit_descriptor *ftr = _ftr;

		csize = 4;
		channels = (ftr->bLength - 7) / 4 - 1;
		bmaControls = ftr->bmaControls;
	पूर्ण

	/* parse the source unit */
	err = parse_audio_unit(state, hdr->bSourceID);
	अगर (err < 0)
		वापस err;

	/* determine the input source type and name */
	err = check_input_term(state, hdr->bSourceID, &iterm);
	अगर (err < 0)
		वापस err;

	master_bits = snd_usb_combine_bytes(bmaControls, csize);
	/* master configuration quirks */
	चयन (state->chip->usb_id) अणु
	हाल USB_ID(0x08bb, 0x2702):
		usb_audio_info(state->chip,
			       "usbmixer: master volume quirk for PCM2702 chip\n");
		/* disable non-functional volume control */
		master_bits &= ~UAC_CONTROL_BIT(UAC_FU_VOLUME);
		अवरोध;
	हाल USB_ID(0x1130, 0xf211):
		usb_audio_info(state->chip,
			       "usbmixer: volume control quirk for Tenx TP6911 Audio Headset\n");
		/* disable non-functional volume control */
		channels = 0;
		अवरोध;

	पूर्ण

	अगर (state->mixer->protocol == UAC_VERSION_1) अणु
		/* check all control types */
		क्रम (i = 0; i < 10; i++) अणु
			अचिन्हित पूर्णांक ch_bits = 0;
			पूर्णांक control = audio_feature_info[i].control;

			क्रम (j = 0; j < channels; j++) अणु
				अचिन्हित पूर्णांक mask;

				mask = snd_usb_combine_bytes(bmaControls +
							     csize * (j+1), csize);
				अगर (mask & (1 << i))
					ch_bits |= (1 << j);
			पूर्ण
			/* audio class v1 controls are never पढ़ो-only */

			/*
			 * The first channel must be set
			 * (क्रम ease of programming).
			 */
			अगर (ch_bits & 1)
				build_feature_ctl(state, _ftr, ch_bits, control,
						  &iterm, unitid, 0);
			अगर (master_bits & (1 << i))
				build_feature_ctl(state, _ftr, 0, control,
						  &iterm, unitid, 0);
		पूर्ण
	पूर्ण अन्यथा अणु /* UAC_VERSION_2/3 */
		क्रम (i = 0; i < ARRAY_SIZE(audio_feature_info); i++) अणु
			अचिन्हित पूर्णांक ch_bits = 0;
			अचिन्हित पूर्णांक ch_पढ़ो_only = 0;
			पूर्णांक control = audio_feature_info[i].control;

			क्रम (j = 0; j < channels; j++) अणु
				अचिन्हित पूर्णांक mask;

				mask = snd_usb_combine_bytes(bmaControls +
							     csize * (j+1), csize);
				अगर (uac_v2v3_control_is_पढ़ोable(mask, control)) अणु
					ch_bits |= (1 << j);
					अगर (!uac_v2v3_control_is_ग_लिखोable(mask, control))
						ch_पढ़ो_only |= (1 << j);
				पूर्ण
			पूर्ण

			/*
			 * NOTE: build_feature_ctl() will mark the control
			 * पढ़ो-only अगर all channels are marked पढ़ो-only in
			 * the descriptors. Otherwise, the control will be
			 * reported as ग_लिखोable, but the driver will not
			 * actually issue a ग_लिखो command क्रम पढ़ो-only
			 * channels.
			 */

			/*
			 * The first channel must be set
			 * (क्रम ease of programming).
			 */
			अगर (ch_bits & 1)
				build_feature_ctl(state, _ftr, ch_bits, control,
						  &iterm, unitid, ch_पढ़ो_only);
			अगर (uac_v2v3_control_is_पढ़ोable(master_bits, control))
				build_feature_ctl(state, _ftr, 0, control,
						  &iterm, unitid,
						  !uac_v2v3_control_is_ग_लिखोable(master_bits,
										 control));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Mixer Unit
 */

/* check whether the given in/out overflows bmMixerControls matrix */
अटल bool mixer_biपंचांगap_overflow(काष्ठा uac_mixer_unit_descriptor *desc,
				  पूर्णांक protocol, पूर्णांक num_ins, पूर्णांक num_outs)
अणु
	u8 *hdr = (u8 *)desc;
	u8 *c = uac_mixer_unit_bmControls(desc, protocol);
	माप_प्रकार rest; /* reमुख्यing bytes after bmMixerControls */

	चयन (protocol) अणु
	हाल UAC_VERSION_1:
	शेष:
		rest = 1; /* iMixer */
		अवरोध;
	हाल UAC_VERSION_2:
		rest = 2; /* bmControls + iMixer */
		अवरोध;
	हाल UAC_VERSION_3:
		rest = 6; /* bmControls + wMixerDescrStr */
		अवरोध;
	पूर्ण

	/* overflow? */
	वापस c + (num_ins * num_outs + 7) / 8 + rest > hdr + hdr[0];
पूर्ण

/*
 * build a mixer unit control
 *
 * the callbacks are identical with feature unit.
 * input channel number (zero based) is given in control field instead.
 */
अटल व्योम build_mixer_unit_ctl(काष्ठा mixer_build *state,
				 काष्ठा uac_mixer_unit_descriptor *desc,
				 पूर्णांक in_pin, पूर्णांक in_ch, पूर्णांक num_outs,
				 पूर्णांक unitid, काष्ठा usb_audio_term *iterm)
अणु
	काष्ठा usb_mixer_elem_info *cval;
	अचिन्हित पूर्णांक i, len;
	काष्ठा snd_kcontrol *kctl;
	स्थिर काष्ठा usbmix_name_map *map;

	map = find_map(state->map, unitid, 0);
	अगर (check_ignored_ctl(map))
		वापस;

	cval = kzalloc(माप(*cval), GFP_KERNEL);
	अगर (!cval)
		वापस;

	snd_usb_mixer_elem_init_std(&cval->head, state->mixer, unitid);
	cval->control = in_ch + 1; /* based on 1 */
	cval->val_type = USB_MIXER_S16;
	क्रम (i = 0; i < num_outs; i++) अणु
		__u8 *c = uac_mixer_unit_bmControls(desc, state->mixer->protocol);

		अगर (check_matrix_biपंचांगap(c, in_ch, i, num_outs)) अणु
			cval->cmask |= (1 << i);
			cval->channels++;
		पूर्ण
	पूर्ण

	/* get min/max values */
	get_min_max(cval, 0);

	kctl = snd_ctl_new1(&usb_feature_unit_ctl, cval);
	अगर (!kctl) अणु
		usb_audio_err(state->chip, "cannot malloc kcontrol\n");
		usb_mixer_elem_info_मुक्त(cval);
		वापस;
	पूर्ण
	kctl->निजी_मुक्त = snd_usb_mixer_elem_मुक्त;

	len = check_mapped_name(map, kctl->id.name, माप(kctl->id.name));
	अगर (!len)
		len = get_term_name(state->chip, iterm, kctl->id.name,
				    माप(kctl->id.name), 0);
	अगर (!len)
		len = प्र_लिखो(kctl->id.name, "Mixer Source %d", in_ch + 1);
	append_ctl_name(kctl, " Volume");

	usb_audio_dbg(state->chip, "[%d] MU [%s] ch = %d, val = %d/%d\n",
		    cval->head.id, kctl->id.name, cval->channels, cval->min, cval->max);
	snd_usb_mixer_add_control(&cval->head, kctl);
पूर्ण

अटल पूर्णांक parse_audio_input_terminal(काष्ठा mixer_build *state, पूर्णांक unitid,
				      व्योम *raw_desc)
अणु
	काष्ठा usb_audio_term iterm;
	अचिन्हित पूर्णांक control, bmctls, term_id;

	अगर (state->mixer->protocol == UAC_VERSION_2) अणु
		काष्ठा uac2_input_terminal_descriptor *d_v2 = raw_desc;
		control = UAC2_TE_CONNECTOR;
		term_id = d_v2->bTerminalID;
		bmctls = le16_to_cpu(d_v2->bmControls);
	पूर्ण अन्यथा अगर (state->mixer->protocol == UAC_VERSION_3) अणु
		काष्ठा uac3_input_terminal_descriptor *d_v3 = raw_desc;
		control = UAC3_TE_INSERTION;
		term_id = d_v3->bTerminalID;
		bmctls = le32_to_cpu(d_v3->bmControls);
	पूर्ण अन्यथा अणु
		वापस 0; /* UAC1. No Insertion control */
	पूर्ण

	check_input_term(state, term_id, &iterm);

	/* Check क्रम jack detection. */
	अगर ((iterm.type & 0xff00) != 0x0100 &&
	    uac_v2v3_control_is_पढ़ोable(bmctls, control))
		build_connector_control(state->mixer, state->map, &iterm, true);

	वापस 0;
पूर्ण

/*
 * parse a mixer unit
 */
अटल पूर्णांक parse_audio_mixer_unit(काष्ठा mixer_build *state, पूर्णांक unitid,
				  व्योम *raw_desc)
अणु
	काष्ठा uac_mixer_unit_descriptor *desc = raw_desc;
	काष्ठा usb_audio_term iterm;
	पूर्णांक input_pins, num_ins, num_outs;
	पूर्णांक pin, ich, err;

	err = uac_mixer_unit_get_channels(state, desc);
	अगर (err < 0) अणु
		usb_audio_err(state->chip,
			      "invalid MIXER UNIT descriptor %d\n",
			      unitid);
		वापस err;
	पूर्ण

	num_outs = err;
	input_pins = desc->bNrInPins;

	num_ins = 0;
	ich = 0;
	क्रम (pin = 0; pin < input_pins; pin++) अणु
		err = parse_audio_unit(state, desc->baSourceID[pin]);
		अगर (err < 0)
			जारी;
		/* no bmControls field (e.g. Maya44) -> ignore */
		अगर (!num_outs)
			जारी;
		err = check_input_term(state, desc->baSourceID[pin], &iterm);
		अगर (err < 0)
			वापस err;
		num_ins += iterm.channels;
		अगर (mixer_biपंचांगap_overflow(desc, state->mixer->protocol,
					  num_ins, num_outs))
			अवरोध;
		क्रम (; ich < num_ins; ich++) अणु
			पूर्णांक och, ich_has_controls = 0;

			क्रम (och = 0; och < num_outs; och++) अणु
				__u8 *c = uac_mixer_unit_bmControls(desc,
						state->mixer->protocol);

				अगर (check_matrix_biपंचांगap(c, ich, och, num_outs)) अणु
					ich_has_controls = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (ich_has_controls)
				build_mixer_unit_ctl(state, desc, pin, ich, num_outs,
						     unitid, &iterm);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Processing Unit / Extension Unit
 */

/* get callback क्रम processing/extension unit */
अटल पूर्णांक mixer_ctl_procunit_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;
	पूर्णांक err, val;

	err = get_cur_ctl_value(cval, cval->control << 8, &val);
	अगर (err < 0) अणु
		ucontrol->value.पूर्णांकeger.value[0] = cval->min;
		वापस filter_error(cval, err);
	पूर्ण
	val = get_relative_value(cval, val);
	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;
पूर्ण

/* put callback क्रम processing/extension unit */
अटल पूर्णांक mixer_ctl_procunit_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;
	पूर्णांक val, oval, err;

	err = get_cur_ctl_value(cval, cval->control << 8, &oval);
	अगर (err < 0)
		वापस filter_error(cval, err);
	val = ucontrol->value.पूर्णांकeger.value[0];
	val = get_असल_value(cval, val);
	अगर (val != oval) अणु
		set_cur_ctl_value(cval, cval->control << 8, val);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* alsa control पूर्णांकerface क्रम processing/extension unit */
अटल स्थिर काष्ठा snd_kcontrol_new mixer_procunit_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "", /* will be filled later */
	.info = mixer_ctl_feature_info,
	.get = mixer_ctl_procunit_get,
	.put = mixer_ctl_procunit_put,
पूर्ण;

/*
 * predefined data क्रम processing units
 */
काष्ठा procunit_value_info अणु
	पूर्णांक control;
	स्थिर अक्षर *suffix;
	पूर्णांक val_type;
	पूर्णांक min_value;
पूर्ण;

काष्ठा procunit_info अणु
	पूर्णांक type;
	अक्षर *name;
	स्थिर काष्ठा procunit_value_info *values;
पूर्ण;

अटल स्थिर काष्ठा procunit_value_info undefined_proc_info[] = अणु
	अणु 0x00, "Control Undefined", 0 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा procunit_value_info upकरोwn_proc_info[] = अणु
	अणु UAC_UD_ENABLE, "Switch", USB_MIXER_BOOLEAN पूर्ण,
	अणु UAC_UD_MODE_SELECT, "Mode Select", USB_MIXER_U8, 1 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
अटल स्थिर काष्ठा procunit_value_info prologic_proc_info[] = अणु
	अणु UAC_DP_ENABLE, "Switch", USB_MIXER_BOOLEAN पूर्ण,
	अणु UAC_DP_MODE_SELECT, "Mode Select", USB_MIXER_U8, 1 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
अटल स्थिर काष्ठा procunit_value_info threed_enh_proc_info[] = अणु
	अणु UAC_3D_ENABLE, "Switch", USB_MIXER_BOOLEAN पूर्ण,
	अणु UAC_3D_SPACE, "Spaciousness", USB_MIXER_U8 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
अटल स्थिर काष्ठा procunit_value_info reverb_proc_info[] = अणु
	अणु UAC_REVERB_ENABLE, "Switch", USB_MIXER_BOOLEAN पूर्ण,
	अणु UAC_REVERB_LEVEL, "Level", USB_MIXER_U8 पूर्ण,
	अणु UAC_REVERB_TIME, "Time", USB_MIXER_U16 पूर्ण,
	अणु UAC_REVERB_FEEDBACK, "Feedback", USB_MIXER_U8 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
अटल स्थिर काष्ठा procunit_value_info chorus_proc_info[] = अणु
	अणु UAC_CHORUS_ENABLE, "Switch", USB_MIXER_BOOLEAN पूर्ण,
	अणु UAC_CHORUS_LEVEL, "Level", USB_MIXER_U8 पूर्ण,
	अणु UAC_CHORUS_RATE, "Rate", USB_MIXER_U16 पूर्ण,
	अणु UAC_CHORUS_DEPTH, "Depth", USB_MIXER_U16 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
अटल स्थिर काष्ठा procunit_value_info dcr_proc_info[] = अणु
	अणु UAC_DCR_ENABLE, "Switch", USB_MIXER_BOOLEAN पूर्ण,
	अणु UAC_DCR_RATE, "Ratio", USB_MIXER_U16 पूर्ण,
	अणु UAC_DCR_MAXAMPL, "Max Amp", USB_MIXER_S16 पूर्ण,
	अणु UAC_DCR_THRESHOLD, "Threshold", USB_MIXER_S16 पूर्ण,
	अणु UAC_DCR_ATTACK_TIME, "Attack Time", USB_MIXER_U16 पूर्ण,
	अणु UAC_DCR_RELEASE_TIME, "Release Time", USB_MIXER_U16 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा procunit_info procunits[] = अणु
	अणु UAC_PROCESS_UP_DOWNMIX, "Up Down", upकरोwn_proc_info पूर्ण,
	अणु UAC_PROCESS_DOLBY_PROLOGIC, "Dolby Prologic", prologic_proc_info पूर्ण,
	अणु UAC_PROCESS_STEREO_EXTENDER, "3D Stereo Extender", threed_enh_proc_info पूर्ण,
	अणु UAC_PROCESS_REVERB, "Reverb", reverb_proc_info पूर्ण,
	अणु UAC_PROCESS_CHORUS, "Chorus", chorus_proc_info पूर्ण,
	अणु UAC_PROCESS_DYN_RANGE_COMP, "DCR", dcr_proc_info पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा procunit_value_info uac3_upकरोwn_proc_info[] = अणु
	अणु UAC3_UD_MODE_SELECT, "Mode Select", USB_MIXER_U8, 1 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
अटल स्थिर काष्ठा procunit_value_info uac3_stereo_ext_proc_info[] = अणु
	अणु UAC3_EXT_WIDTH_CONTROL, "Width Control", USB_MIXER_U8 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा procunit_info uac3_procunits[] = अणु
	अणु UAC3_PROCESS_UP_DOWNMIX, "Up Down", uac3_upकरोwn_proc_info पूर्ण,
	अणु UAC3_PROCESS_STEREO_EXTENDER, "3D Stereo Extender", uac3_stereo_ext_proc_info पूर्ण,
	अणु UAC3_PROCESS_MULTI_FUNCTION, "Multi-Function", undefined_proc_info पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

/*
 * predefined data क्रम extension units
 */
अटल स्थिर काष्ठा procunit_value_info घड़ी_rate_xu_info[] = अणु
	अणु USB_XU_CLOCK_RATE_SELECTOR, "Selector", USB_MIXER_U8, 0 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
अटल स्थिर काष्ठा procunit_value_info घड़ी_source_xu_info[] = अणु
	अणु USB_XU_CLOCK_SOURCE_SELECTOR, "External", USB_MIXER_BOOLEAN पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
अटल स्थिर काष्ठा procunit_value_info spdअगर_क्रमmat_xu_info[] = अणु
	अणु USB_XU_DIGITAL_FORMAT_SELECTOR, "SPDIF/AC3", USB_MIXER_BOOLEAN पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
अटल स्थिर काष्ठा procunit_value_info soft_limit_xu_info[] = अणु
	अणु USB_XU_SOFT_LIMIT_SELECTOR, " ", USB_MIXER_BOOLEAN पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
अटल स्थिर काष्ठा procunit_info extunits[] = अणु
	अणु USB_XU_CLOCK_RATE, "Clock rate", घड़ी_rate_xu_info पूर्ण,
	अणु USB_XU_CLOCK_SOURCE, "DigitalIn CLK source", घड़ी_source_xu_info पूर्ण,
	अणु USB_XU_DIGITAL_IO_STATUS, "DigitalOut format:", spdअगर_क्रमmat_xu_info पूर्ण,
	अणु USB_XU_DEVICE_OPTIONS, "AnalogueIn Soft Limit", soft_limit_xu_info पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/*
 * build a processing/extension unit
 */
अटल पूर्णांक build_audio_procunit(काष्ठा mixer_build *state, पूर्णांक unitid,
				व्योम *raw_desc, स्थिर काष्ठा procunit_info *list,
				bool extension_unit)
अणु
	काष्ठा uac_processing_unit_descriptor *desc = raw_desc;
	पूर्णांक num_ins;
	काष्ठा usb_mixer_elem_info *cval;
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक i, err, nameid, type, len, val;
	स्थिर काष्ठा procunit_info *info;
	स्थिर काष्ठा procunit_value_info *valinfo;
	स्थिर काष्ठा usbmix_name_map *map;
	अटल स्थिर काष्ठा procunit_value_info शेष_value_info[] = अणु
		अणु 0x01, "Switch", USB_MIXER_BOOLEAN पूर्ण,
		अणु 0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा procunit_info शेष_info = अणु
		0, शून्य, शेष_value_info
	पूर्ण;
	स्थिर अक्षर *name = extension_unit ?
		"Extension Unit" : "Processing Unit";

	num_ins = desc->bNrInPins;
	क्रम (i = 0; i < num_ins; i++) अणु
		err = parse_audio_unit(state, desc->baSourceID[i]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	type = le16_to_cpu(desc->wProcessType);
	क्रम (info = list; info && info->type; info++)
		अगर (info->type == type)
			अवरोध;
	अगर (!info || !info->type)
		info = &शेष_info;

	क्रम (valinfo = info->values; valinfo->control; valinfo++) अणु
		__u8 *controls = uac_processing_unit_bmControls(desc, state->mixer->protocol);

		अगर (state->mixer->protocol == UAC_VERSION_1) अणु
			अगर (!(controls[valinfo->control / 8] &
					(1 << ((valinfo->control % 8) - 1))))
				जारी;
		पूर्ण अन्यथा अणु /* UAC_VERSION_2/3 */
			अगर (!uac_v2v3_control_is_पढ़ोable(controls[valinfo->control / 8],
							  valinfo->control))
				जारी;
		पूर्ण

		map = find_map(state->map, unitid, valinfo->control);
		अगर (check_ignored_ctl(map))
			जारी;
		cval = kzalloc(माप(*cval), GFP_KERNEL);
		अगर (!cval)
			वापस -ENOMEM;
		snd_usb_mixer_elem_init_std(&cval->head, state->mixer, unitid);
		cval->control = valinfo->control;
		cval->val_type = valinfo->val_type;
		cval->channels = 1;

		अगर (state->mixer->protocol > UAC_VERSION_1 &&
		    !uac_v2v3_control_is_ग_लिखोable(controls[valinfo->control / 8],
						   valinfo->control))
			cval->master_पढ़ोonly = 1;

		/* get min/max values */
		चयन (type) अणु
		हाल UAC_PROCESS_UP_DOWNMIX: अणु
			bool mode_sel = false;

			चयन (state->mixer->protocol) अणु
			हाल UAC_VERSION_1:
			हाल UAC_VERSION_2:
			शेष:
				अगर (cval->control == UAC_UD_MODE_SELECT)
					mode_sel = true;
				अवरोध;
			हाल UAC_VERSION_3:
				अगर (cval->control == UAC3_UD_MODE_SELECT)
					mode_sel = true;
				अवरोध;
			पूर्ण

			अगर (mode_sel) अणु
				__u8 *control_spec = uac_processing_unit_specअगरic(desc,
								state->mixer->protocol);
				cval->min = 1;
				cval->max = control_spec[0];
				cval->res = 1;
				cval->initialized = 1;
				अवरोध;
			पूर्ण

			get_min_max(cval, valinfo->min_value);
			अवरोध;
		पूर्ण
		हाल USB_XU_CLOCK_RATE:
			/*
			 * E-Mu USB 0404/0202/TrackerPre/0204
			 * samplerate control quirk
			 */
			cval->min = 0;
			cval->max = 5;
			cval->res = 1;
			cval->initialized = 1;
			अवरोध;
		शेष:
			get_min_max(cval, valinfo->min_value);
			अवरोध;
		पूर्ण

		err = get_cur_ctl_value(cval, cval->control << 8, &val);
		अगर (err < 0) अणु
			usb_mixer_elem_info_मुक्त(cval);
			वापस -EINVAL;
		पूर्ण

		kctl = snd_ctl_new1(&mixer_procunit_ctl, cval);
		अगर (!kctl) अणु
			usb_mixer_elem_info_मुक्त(cval);
			वापस -ENOMEM;
		पूर्ण
		kctl->निजी_मुक्त = snd_usb_mixer_elem_मुक्त;

		अगर (check_mapped_name(map, kctl->id.name, माप(kctl->id.name))) अणु
			/* nothing */ ;
		पूर्ण अन्यथा अगर (info->name) अणु
			strscpy(kctl->id.name, info->name, माप(kctl->id.name));
		पूर्ण अन्यथा अणु
			अगर (extension_unit)
				nameid = uac_extension_unit_iExtension(desc, state->mixer->protocol);
			अन्यथा
				nameid = uac_processing_unit_iProcessing(desc, state->mixer->protocol);
			len = 0;
			अगर (nameid)
				len = snd_usb_copy_string_desc(state->chip,
							       nameid,
							       kctl->id.name,
							       माप(kctl->id.name));
			अगर (!len)
				strscpy(kctl->id.name, name, माप(kctl->id.name));
		पूर्ण
		append_ctl_name(kctl, " ");
		append_ctl_name(kctl, valinfo->suffix);

		usb_audio_dbg(state->chip,
			      "[%d] PU [%s] ch = %d, val = %d/%d\n",
			      cval->head.id, kctl->id.name, cval->channels,
			      cval->min, cval->max);

		err = snd_usb_mixer_add_control(&cval->head, kctl);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parse_audio_processing_unit(काष्ठा mixer_build *state, पूर्णांक unitid,
				       व्योम *raw_desc)
अणु
	चयन (state->mixer->protocol) अणु
	हाल UAC_VERSION_1:
	हाल UAC_VERSION_2:
	शेष:
		वापस build_audio_procunit(state, unitid, raw_desc,
					    procunits, false);
	हाल UAC_VERSION_3:
		वापस build_audio_procunit(state, unitid, raw_desc,
					    uac3_procunits, false);
	पूर्ण
पूर्ण

अटल पूर्णांक parse_audio_extension_unit(काष्ठा mixer_build *state, पूर्णांक unitid,
				      व्योम *raw_desc)
अणु
	/*
	 * Note that we parse extension units with processing unit descriptors.
	 * That's ok as the layout is the same.
	 */
	वापस build_audio_procunit(state, unitid, raw_desc, extunits, true);
पूर्ण

/*
 * Selector Unit
 */

/*
 * info callback क्रम selector unit
 * use an क्रमागतerator type क्रम routing
 */
अटल पूर्णांक mixer_ctl_selector_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;
	स्थिर अक्षर **itemlist = (स्थिर अक्षर **)kcontrol->निजी_value;

	अगर (snd_BUG_ON(!itemlist))
		वापस -EINVAL;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, cval->max, itemlist);
पूर्ण

/* get callback क्रम selector unit */
अटल पूर्णांक mixer_ctl_selector_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;
	पूर्णांक val, err;

	err = get_cur_ctl_value(cval, cval->control << 8, &val);
	अगर (err < 0) अणु
		ucontrol->value.क्रमागतerated.item[0] = 0;
		वापस filter_error(cval, err);
	पूर्ण
	val = get_relative_value(cval, val);
	ucontrol->value.क्रमागतerated.item[0] = val;
	वापस 0;
पूर्ण

/* put callback क्रम selector unit */
अटल पूर्णांक mixer_ctl_selector_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *cval = kcontrol->निजी_data;
	पूर्णांक val, oval, err;

	err = get_cur_ctl_value(cval, cval->control << 8, &oval);
	अगर (err < 0)
		वापस filter_error(cval, err);
	val = ucontrol->value.क्रमागतerated.item[0];
	val = get_असल_value(cval, val);
	अगर (val != oval) अणु
		set_cur_ctl_value(cval, cval->control << 8, val);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* alsa control पूर्णांकerface क्रम selector unit */
अटल स्थिर काष्ठा snd_kcontrol_new mixer_selectunit_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "", /* will be filled later */
	.info = mixer_ctl_selector_info,
	.get = mixer_ctl_selector_get,
	.put = mixer_ctl_selector_put,
पूर्ण;

/*
 * निजी मुक्त callback.
 * मुक्त both निजी_data and निजी_value
 */
अटल व्योम usb_mixer_selector_elem_मुक्त(काष्ठा snd_kcontrol *kctl)
अणु
	पूर्णांक i, num_ins = 0;

	अगर (kctl->निजी_data) अणु
		काष्ठा usb_mixer_elem_info *cval = kctl->निजी_data;
		num_ins = cval->max;
		usb_mixer_elem_info_मुक्त(cval);
		kctl->निजी_data = शून्य;
	पूर्ण
	अगर (kctl->निजी_value) अणु
		अक्षर **itemlist = (अक्षर **)kctl->निजी_value;
		क्रम (i = 0; i < num_ins; i++)
			kमुक्त(itemlist[i]);
		kमुक्त(itemlist);
		kctl->निजी_value = 0;
	पूर्ण
पूर्ण

/*
 * parse a selector unit
 */
अटल पूर्णांक parse_audio_selector_unit(काष्ठा mixer_build *state, पूर्णांक unitid,
				     व्योम *raw_desc)
अणु
	काष्ठा uac_selector_unit_descriptor *desc = raw_desc;
	अचिन्हित पूर्णांक i, nameid, len;
	पूर्णांक err;
	काष्ठा usb_mixer_elem_info *cval;
	काष्ठा snd_kcontrol *kctl;
	स्थिर काष्ठा usbmix_name_map *map;
	अक्षर **namelist;

	क्रम (i = 0; i < desc->bNrInPins; i++) अणु
		err = parse_audio_unit(state, desc->baSourceID[i]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (desc->bNrInPins == 1) /* only one ? nonsense! */
		वापस 0;

	map = find_map(state->map, unitid, 0);
	अगर (check_ignored_ctl(map))
		वापस 0;

	cval = kzalloc(माप(*cval), GFP_KERNEL);
	अगर (!cval)
		वापस -ENOMEM;
	snd_usb_mixer_elem_init_std(&cval->head, state->mixer, unitid);
	cval->val_type = USB_MIXER_U8;
	cval->channels = 1;
	cval->min = 1;
	cval->max = desc->bNrInPins;
	cval->res = 1;
	cval->initialized = 1;

	चयन (state->mixer->protocol) अणु
	हाल UAC_VERSION_1:
	शेष:
		cval->control = 0;
		अवरोध;
	हाल UAC_VERSION_2:
	हाल UAC_VERSION_3:
		अगर (desc->bDescriptorSubtype == UAC2_CLOCK_SELECTOR ||
		    desc->bDescriptorSubtype == UAC3_CLOCK_SELECTOR)
			cval->control = UAC2_CX_CLOCK_SELECTOR;
		अन्यथा /* UAC2/3_SELECTOR_UNIT */
			cval->control = UAC2_SU_SELECTOR;
		अवरोध;
	पूर्ण

	namelist = kसुस्मृति(desc->bNrInPins, माप(अक्षर *), GFP_KERNEL);
	अगर (!namelist) अणु
		err = -ENOMEM;
		जाओ error_cval;
	पूर्ण
#घोषणा MAX_ITEM_NAME_LEN	64
	क्रम (i = 0; i < desc->bNrInPins; i++) अणु
		काष्ठा usb_audio_term iterm;
		namelist[i] = kदो_स्मृति(MAX_ITEM_NAME_LEN, GFP_KERNEL);
		अगर (!namelist[i]) अणु
			err = -ENOMEM;
			जाओ error_name;
		पूर्ण
		len = check_mapped_selector_name(state, unitid, i, namelist[i],
						 MAX_ITEM_NAME_LEN);
		अगर (! len && check_input_term(state, desc->baSourceID[i], &iterm) >= 0)
			len = get_term_name(state->chip, &iterm, namelist[i],
					    MAX_ITEM_NAME_LEN, 0);
		अगर (! len)
			प्र_लिखो(namelist[i], "Input %u", i);
	पूर्ण

	kctl = snd_ctl_new1(&mixer_selectunit_ctl, cval);
	अगर (! kctl) अणु
		usb_audio_err(state->chip, "cannot malloc kcontrol\n");
		err = -ENOMEM;
		जाओ error_name;
	पूर्ण
	kctl->निजी_value = (अचिन्हित दीर्घ)namelist;
	kctl->निजी_मुक्त = usb_mixer_selector_elem_मुक्त;

	/* check the अटल mapping table at first */
	len = check_mapped_name(map, kctl->id.name, माप(kctl->id.name));
	अगर (!len) अणु
		/* no mapping ? */
		चयन (state->mixer->protocol) अणु
		हाल UAC_VERSION_1:
		हाल UAC_VERSION_2:
		शेष:
		/* अगर iSelector is given, use it */
			nameid = uac_selector_unit_iSelector(desc);
			अगर (nameid)
				len = snd_usb_copy_string_desc(state->chip,
							nameid, kctl->id.name,
							माप(kctl->id.name));
			अवरोध;
		हाल UAC_VERSION_3:
			/* TODO: Class-Specअगरic strings not yet supported */
			अवरोध;
		पूर्ण

		/* ... or pick up the terminal name at next */
		अगर (!len)
			len = get_term_name(state->chip, &state->oterm,
				    kctl->id.name, माप(kctl->id.name), 0);
		/* ... or use the fixed string "USB" as the last resort */
		अगर (!len)
			strscpy(kctl->id.name, "USB", माप(kctl->id.name));

		/* and add the proper suffix */
		अगर (desc->bDescriptorSubtype == UAC2_CLOCK_SELECTOR ||
		    desc->bDescriptorSubtype == UAC3_CLOCK_SELECTOR)
			append_ctl_name(kctl, " Clock Source");
		अन्यथा अगर ((state->oterm.type & 0xff00) == 0x0100)
			append_ctl_name(kctl, " Capture Source");
		अन्यथा
			append_ctl_name(kctl, " Playback Source");
	पूर्ण

	usb_audio_dbg(state->chip, "[%d] SU [%s] items = %d\n",
		    cval->head.id, kctl->id.name, desc->bNrInPins);
	वापस snd_usb_mixer_add_control(&cval->head, kctl);

 error_name:
	क्रम (i = 0; i < desc->bNrInPins; i++)
		kमुक्त(namelist[i]);
	kमुक्त(namelist);
 error_cval:
	usb_mixer_elem_info_मुक्त(cval);
	वापस err;
पूर्ण

/*
 * parse an audio unit recursively
 */

अटल पूर्णांक parse_audio_unit(काष्ठा mixer_build *state, पूर्णांक unitid)
अणु
	अचिन्हित अक्षर *p1;
	पूर्णांक protocol = state->mixer->protocol;

	अगर (test_and_set_bit(unitid, state->unitbiपंचांगap))
		वापस 0; /* the unit alपढ़ोy visited */

	p1 = find_audio_control_unit(state, unitid);
	अगर (!p1) अणु
		usb_audio_err(state->chip, "unit %d not found!\n", unitid);
		वापस -EINVAL;
	पूर्ण

	अगर (!snd_usb_validate_audio_desc(p1, protocol)) अणु
		usb_audio_dbg(state->chip, "invalid unit %d\n", unitid);
		वापस 0; /* skip invalid unit */
	पूर्ण

	चयन (PTYPE(protocol, p1[2])) अणु
	हाल PTYPE(UAC_VERSION_1, UAC_INPUT_TERMINAL):
	हाल PTYPE(UAC_VERSION_2, UAC_INPUT_TERMINAL):
	हाल PTYPE(UAC_VERSION_3, UAC_INPUT_TERMINAL):
		वापस parse_audio_input_terminal(state, unitid, p1);
	हाल PTYPE(UAC_VERSION_1, UAC_MIXER_UNIT):
	हाल PTYPE(UAC_VERSION_2, UAC_MIXER_UNIT):
	हाल PTYPE(UAC_VERSION_3, UAC3_MIXER_UNIT):
		वापस parse_audio_mixer_unit(state, unitid, p1);
	हाल PTYPE(UAC_VERSION_2, UAC2_CLOCK_SOURCE):
	हाल PTYPE(UAC_VERSION_3, UAC3_CLOCK_SOURCE):
		वापस parse_घड़ी_source_unit(state, unitid, p1);
	हाल PTYPE(UAC_VERSION_1, UAC_SELECTOR_UNIT):
	हाल PTYPE(UAC_VERSION_2, UAC_SELECTOR_UNIT):
	हाल PTYPE(UAC_VERSION_3, UAC3_SELECTOR_UNIT):
	हाल PTYPE(UAC_VERSION_2, UAC2_CLOCK_SELECTOR):
	हाल PTYPE(UAC_VERSION_3, UAC3_CLOCK_SELECTOR):
		वापस parse_audio_selector_unit(state, unitid, p1);
	हाल PTYPE(UAC_VERSION_1, UAC_FEATURE_UNIT):
	हाल PTYPE(UAC_VERSION_2, UAC_FEATURE_UNIT):
	हाल PTYPE(UAC_VERSION_3, UAC3_FEATURE_UNIT):
		वापस parse_audio_feature_unit(state, unitid, p1);
	हाल PTYPE(UAC_VERSION_1, UAC1_PROCESSING_UNIT):
	हाल PTYPE(UAC_VERSION_2, UAC2_PROCESSING_UNIT_V2):
	हाल PTYPE(UAC_VERSION_3, UAC3_PROCESSING_UNIT):
		वापस parse_audio_processing_unit(state, unitid, p1);
	हाल PTYPE(UAC_VERSION_1, UAC1_EXTENSION_UNIT):
	हाल PTYPE(UAC_VERSION_2, UAC2_EXTENSION_UNIT_V2):
	हाल PTYPE(UAC_VERSION_3, UAC3_EXTENSION_UNIT):
		वापस parse_audio_extension_unit(state, unitid, p1);
	हाल PTYPE(UAC_VERSION_2, UAC2_EFFECT_UNIT):
	हाल PTYPE(UAC_VERSION_3, UAC3_EFFECT_UNIT):
		वापस 0; /* FIXME - effect units not implemented yet */
	शेष:
		usb_audio_err(state->chip,
			      "unit %u: unexpected type 0x%02x\n",
			      unitid, p1[2]);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम snd_usb_mixer_मुक्त(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	/* समाप्त pending URBs */
	snd_usb_mixer_disconnect(mixer);

	kमुक्त(mixer->id_elems);
	अगर (mixer->urb) अणु
		kमुक्त(mixer->urb->transfer_buffer);
		usb_मुक्त_urb(mixer->urb);
	पूर्ण
	usb_मुक्त_urb(mixer->rc_urb);
	kमुक्त(mixer->rc_setup_packet);
	kमुक्त(mixer);
पूर्ण

अटल पूर्णांक snd_usb_mixer_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा usb_mixer_पूर्णांकerface *mixer = device->device_data;
	snd_usb_mixer_मुक्त(mixer);
	वापस 0;
पूर्ण

/* UAC3 predefined channels configuration */
काष्ठा uac3_badd_profile अणु
	पूर्णांक subclass;
	स्थिर अक्षर *name;
	पूर्णांक c_chmask;	/* capture channels mask */
	पूर्णांक p_chmask;	/* playback channels mask */
	पूर्णांक st_chmask;	/* side tone mixing channel mask */
पूर्ण;

अटल स्थिर काष्ठा uac3_badd_profile uac3_badd_profiles[] = अणु
	अणु
		/*
		 * BAIF, BAOF or combination of both
		 * IN: Mono or Stereo cfg, Mono alt possible
		 * OUT: Mono or Stereo cfg, Mono alt possible
		 */
		.subclass = UAC3_FUNCTION_SUBCLASS_GENERIC_IO,
		.name = "GENERIC IO",
		.c_chmask = -1,		/* dynamic channels */
		.p_chmask = -1,		/* dynamic channels */
	पूर्ण,
	अणु
		/* BAOF; Stereo only cfg, Mono alt possible */
		.subclass = UAC3_FUNCTION_SUBCLASS_HEADPHONE,
		.name = "HEADPHONE",
		.p_chmask = 3,
	पूर्ण,
	अणु
		/* BAOF; Mono or Stereo cfg, Mono alt possible */
		.subclass = UAC3_FUNCTION_SUBCLASS_SPEAKER,
		.name = "SPEAKER",
		.p_chmask = -1,		/* dynamic channels */
	पूर्ण,
	अणु
		/* BAIF; Mono or Stereo cfg, Mono alt possible */
		.subclass = UAC3_FUNCTION_SUBCLASS_MICROPHONE,
		.name = "MICROPHONE",
		.c_chmask = -1,		/* dynamic channels */
	पूर्ण,
	अणु
		/*
		 * BAIOF topology
		 * IN: Mono only
		 * OUT: Mono or Stereo cfg, Mono alt possible
		 */
		.subclass = UAC3_FUNCTION_SUBCLASS_HEADSET,
		.name = "HEADSET",
		.c_chmask = 1,
		.p_chmask = -1,		/* dynamic channels */
		.st_chmask = 1,
	पूर्ण,
	अणु
		/* BAIOF; IN: Mono only; OUT: Stereo only, Mono alt possible */
		.subclass = UAC3_FUNCTION_SUBCLASS_HEADSET_ADAPTER,
		.name = "HEADSET ADAPTER",
		.c_chmask = 1,
		.p_chmask = 3,
		.st_chmask = 1,
	पूर्ण,
	अणु
		/* BAIF + BAOF; IN: Mono only; OUT: Mono only */
		.subclass = UAC3_FUNCTION_SUBCLASS_SPEAKERPHONE,
		.name = "SPEAKERPHONE",
		.c_chmask = 1,
		.p_chmask = 1,
	पूर्ण,
	अणु 0 पूर्ण /* terminator */
पूर्ण;

अटल bool uac3_badd_func_has_valid_channels(काष्ठा usb_mixer_पूर्णांकerface *mixer,
					      स्थिर काष्ठा uac3_badd_profile *f,
					      पूर्णांक c_chmask, पूर्णांक p_chmask)
अणु
	/*
	 * If both playback/capture channels are dynamic, make sure
	 * at least one channel is present
	 */
	अगर (f->c_chmask < 0 && f->p_chmask < 0) अणु
		अगर (!c_chmask && !p_chmask) अणु
			usb_audio_warn(mixer->chip, "BAAD %s: no channels?",
				       f->name);
			वापस false;
		पूर्ण
		वापस true;
	पूर्ण

	अगर ((f->c_chmask < 0 && !c_chmask) ||
	    (f->c_chmask >= 0 && f->c_chmask != c_chmask)) अणु
		usb_audio_warn(mixer->chip, "BAAD %s c_chmask mismatch",
			       f->name);
		वापस false;
	पूर्ण
	अगर ((f->p_chmask < 0 && !p_chmask) ||
	    (f->p_chmask >= 0 && f->p_chmask != p_chmask)) अणु
		usb_audio_warn(mixer->chip, "BAAD %s p_chmask mismatch",
			       f->name);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * create mixer controls क्रम UAC3 BADD profiles
 *
 * UAC3 BADD device करोesn't contain CS descriptors thus we will guess everything
 *
 * BADD device may contain Mixer Unit, which करोesn't have any controls, skip it
 */
अटल पूर्णांक snd_usb_mixer_controls_badd(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				       पूर्णांक ctrlअगर)
अणु
	काष्ठा usb_device *dev = mixer->chip->dev;
	काष्ठा usb_पूर्णांकerface_assoc_descriptor *assoc;
	पूर्णांक badd_profile = mixer->chip->badd_profile;
	स्थिर काष्ठा uac3_badd_profile *f;
	स्थिर काष्ठा usbmix_ctl_map *map;
	पूर्णांक p_chmask = 0, c_chmask = 0, st_chmask = 0;
	पूर्णांक i;

	assoc = usb_अगरnum_to_अगर(dev, ctrlअगर)->पूर्णांकf_assoc;

	/* Detect BADD capture/playback channels from AS EP descriptors */
	क्रम (i = 0; i < assoc->bInterfaceCount; i++) अणु
		पूर्णांक पूर्णांकf = assoc->bFirstInterface + i;

		काष्ठा usb_पूर्णांकerface *अगरace;
		काष्ठा usb_host_पूर्णांकerface *alts;
		काष्ठा usb_पूर्णांकerface_descriptor *altsd;
		अचिन्हित पूर्णांक maxpacksize;
		अक्षर dir_in;
		पूर्णांक chmask, num;

		अगर (पूर्णांकf == ctrlअगर)
			जारी;

		अगरace = usb_अगरnum_to_अगर(dev, पूर्णांकf);
		अगर (!अगरace)
			जारी;

		num = अगरace->num_altsetting;

		अगर (num < 2)
			वापस -EINVAL;

		/*
		 * The number of Channels in an AudioStreaming पूर्णांकerface
		 * and the audio sample bit resolution (16 bits or 24
		 * bits) can be derived from the wMaxPacketSize field in
		 * the Standard AS Audio Data Endpoपूर्णांक descriptor in
		 * Alternate Setting 1
		 */
		alts = &अगरace->altsetting[1];
		altsd = get_अगरace_desc(alts);

		अगर (altsd->bNumEndpoपूर्णांकs < 1)
			वापस -EINVAL;

		/* check direction */
		dir_in = (get_endpoपूर्णांक(alts, 0)->bEndpoपूर्णांकAddress & USB_सूची_IN);
		maxpacksize = le16_to_cpu(get_endpoपूर्णांक(alts, 0)->wMaxPacketSize);

		चयन (maxpacksize) अणु
		शेष:
			usb_audio_err(mixer->chip,
				"incorrect wMaxPacketSize 0x%x for BADD profile\n",
				maxpacksize);
			वापस -EINVAL;
		हाल UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_16:
		हाल UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_16:
		हाल UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_24:
		हाल UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_24:
			chmask = 1;
			अवरोध;
		हाल UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_16:
		हाल UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_16:
		हाल UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_24:
		हाल UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_24:
			chmask = 3;
			अवरोध;
		पूर्ण

		अगर (dir_in)
			c_chmask = chmask;
		अन्यथा
			p_chmask = chmask;
	पूर्ण

	usb_audio_dbg(mixer->chip,
		"UAC3 BADD profile 0x%x: detected c_chmask=%d p_chmask=%d\n",
		badd_profile, c_chmask, p_chmask);

	/* check the mapping table */
	क्रम (map = uac3_badd_usbmix_ctl_maps; map->id; map++) अणु
		अगर (map->id == badd_profile)
			अवरोध;
	पूर्ण

	अगर (!map->id)
		वापस -EINVAL;

	क्रम (f = uac3_badd_profiles; f->name; f++) अणु
		अगर (badd_profile == f->subclass)
			अवरोध;
	पूर्ण
	अगर (!f->name)
		वापस -EINVAL;
	अगर (!uac3_badd_func_has_valid_channels(mixer, f, c_chmask, p_chmask))
		वापस -EINVAL;
	st_chmask = f->st_chmask;

	/* Playback */
	अगर (p_chmask) अणु
		/* Master channel, always writable */
		build_feature_ctl_badd(mixer, 0, UAC_FU_MUTE,
				       UAC3_BADD_FU_ID2, map->map);
		/* Mono/Stereo volume channels, always writable */
		build_feature_ctl_badd(mixer, p_chmask, UAC_FU_VOLUME,
				       UAC3_BADD_FU_ID2, map->map);
	पूर्ण

	/* Capture */
	अगर (c_chmask) अणु
		/* Master channel, always writable */
		build_feature_ctl_badd(mixer, 0, UAC_FU_MUTE,
				       UAC3_BADD_FU_ID5, map->map);
		/* Mono/Stereo volume channels, always writable */
		build_feature_ctl_badd(mixer, c_chmask, UAC_FU_VOLUME,
				       UAC3_BADD_FU_ID5, map->map);
	पूर्ण

	/* Side tone-mixing */
	अगर (st_chmask) अणु
		/* Master channel, always writable */
		build_feature_ctl_badd(mixer, 0, UAC_FU_MUTE,
				       UAC3_BADD_FU_ID7, map->map);
		/* Mono volume channel, always writable */
		build_feature_ctl_badd(mixer, 1, UAC_FU_VOLUME,
				       UAC3_BADD_FU_ID7, map->map);
	पूर्ण

	/* Insertion Control */
	अगर (f->subclass == UAC3_FUNCTION_SUBCLASS_HEADSET_ADAPTER) अणु
		काष्ठा usb_audio_term iterm, oterm;

		/* Input Term - Insertion control */
		स_रखो(&iterm, 0, माप(iterm));
		iterm.id = UAC3_BADD_IT_ID4;
		iterm.type = UAC_BIसूची_TERMINAL_HEADSET;
		build_connector_control(mixer, map->map, &iterm, true);

		/* Output Term - Insertion control */
		स_रखो(&oterm, 0, माप(oterm));
		oterm.id = UAC3_BADD_OT_ID3;
		oterm.type = UAC_BIसूची_TERMINAL_HEADSET;
		build_connector_control(mixer, map->map, &oterm, false);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * create mixer controls
 *
 * walk through all UAC_OUTPUT_TERMINAL descriptors to search क्रम mixers
 */
अटल पूर्णांक snd_usb_mixer_controls(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	काष्ठा mixer_build state;
	पूर्णांक err;
	स्थिर काष्ठा usbmix_ctl_map *map;
	व्योम *p;

	स_रखो(&state, 0, माप(state));
	state.chip = mixer->chip;
	state.mixer = mixer;
	state.buffer = mixer->hostअगर->extra;
	state.buflen = mixer->hostअगर->extralen;

	/* check the mapping table */
	क्रम (map = usbmix_ctl_maps; map->id; map++) अणु
		अगर (map->id == state.chip->usb_id) अणु
			state.map = map->map;
			state.selector_map = map->selector_map;
			mixer->connector_map = map->connector_map;
			mixer->ignore_ctl_error |= map->ignore_ctl_error;
			अवरोध;
		पूर्ण
	पूर्ण

	p = शून्य;
	जबतक ((p = snd_usb_find_csपूर्णांक_desc(mixer->hostअगर->extra,
					    mixer->hostअगर->extralen,
					    p, UAC_OUTPUT_TERMINAL)) != शून्य) अणु
		अगर (!snd_usb_validate_audio_desc(p, mixer->protocol))
			जारी; /* skip invalid descriptor */

		अगर (mixer->protocol == UAC_VERSION_1) अणु
			काष्ठा uac1_output_terminal_descriptor *desc = p;

			/* mark terminal ID as visited */
			set_bit(desc->bTerminalID, state.unitbiपंचांगap);
			state.oterm.id = desc->bTerminalID;
			state.oterm.type = le16_to_cpu(desc->wTerminalType);
			state.oterm.name = desc->iTerminal;
			err = parse_audio_unit(&state, desc->bSourceID);
			अगर (err < 0 && err != -EINVAL)
				वापस err;
		पूर्ण अन्यथा अगर (mixer->protocol == UAC_VERSION_2) अणु
			काष्ठा uac2_output_terminal_descriptor *desc = p;

			/* mark terminal ID as visited */
			set_bit(desc->bTerminalID, state.unitbiपंचांगap);
			state.oterm.id = desc->bTerminalID;
			state.oterm.type = le16_to_cpu(desc->wTerminalType);
			state.oterm.name = desc->iTerminal;
			err = parse_audio_unit(&state, desc->bSourceID);
			अगर (err < 0 && err != -EINVAL)
				वापस err;

			/*
			 * For UAC2, use the same approach to also add the
			 * घड़ी selectors
			 */
			err = parse_audio_unit(&state, desc->bCSourceID);
			अगर (err < 0 && err != -EINVAL)
				वापस err;

			अगर ((state.oterm.type & 0xff00) != 0x0100 &&
			    uac_v2v3_control_is_पढ़ोable(le16_to_cpu(desc->bmControls),
							 UAC2_TE_CONNECTOR)) अणु
				build_connector_control(state.mixer, state.map,
							&state.oterm, false);
			पूर्ण
		पूर्ण अन्यथा अणु  /* UAC_VERSION_3 */
			काष्ठा uac3_output_terminal_descriptor *desc = p;

			/* mark terminal ID as visited */
			set_bit(desc->bTerminalID, state.unitbiपंचांगap);
			state.oterm.id = desc->bTerminalID;
			state.oterm.type = le16_to_cpu(desc->wTerminalType);
			state.oterm.name = le16_to_cpu(desc->wTerminalDescrStr);
			err = parse_audio_unit(&state, desc->bSourceID);
			अगर (err < 0 && err != -EINVAL)
				वापस err;

			/*
			 * For UAC3, use the same approach to also add the
			 * घड़ी selectors
			 */
			err = parse_audio_unit(&state, desc->bCSourceID);
			अगर (err < 0 && err != -EINVAL)
				वापस err;

			अगर ((state.oterm.type & 0xff00) != 0x0100 &&
			    uac_v2v3_control_is_पढ़ोable(le32_to_cpu(desc->bmControls),
							 UAC3_TE_INSERTION)) अणु
				build_connector_control(state.mixer, state.map,
							&state.oterm, false);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक delegate_notअगरy(काष्ठा usb_mixer_पूर्णांकerface *mixer, पूर्णांक unitid,
			   u8 *control, u8 *channel)
अणु
	स्थिर काष्ठा usbmix_connector_map *map = mixer->connector_map;

	अगर (!map)
		वापस unitid;

	क्रम (; map->id; map++) अणु
		अगर (map->id == unitid) अणु
			अगर (control && map->control)
				*control = map->control;
			अगर (channel && map->channel)
				*channel = map->channel;
			वापस map->delegated_id;
		पूर्ण
	पूर्ण
	वापस unitid;
पूर्ण

व्योम snd_usb_mixer_notअगरy_id(काष्ठा usb_mixer_पूर्णांकerface *mixer, पूर्णांक unitid)
अणु
	काष्ठा usb_mixer_elem_list *list;

	unitid = delegate_notअगरy(mixer, unitid, शून्य, शून्य);

	क्रम_each_mixer_elem(list, mixer, unitid) अणु
		काष्ठा usb_mixer_elem_info *info;

		अगर (!list->is_std_info)
			जारी;
		info = mixer_elem_list_to_info(list);
		/* invalidate cache, so the value is पढ़ो from the device */
		info->cached = 0;
		snd_ctl_notअगरy(mixer->chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &list->kctl->id);
	पूर्ण
पूर्ण

अटल व्योम snd_usb_mixer_dump_cval(काष्ठा snd_info_buffer *buffer,
				    काष्ठा usb_mixer_elem_list *list)
अणु
	काष्ठा usb_mixer_elem_info *cval = mixer_elem_list_to_info(list);
	अटल स्थिर अक्षर * स्थिर val_types[] = अणु"BOOLEAN", "INV_BOOLEAN",
				    "S8", "U8", "S16", "U16"पूर्ण;
	snd_iम_लिखो(buffer, "    Info: id=%i, control=%i, cmask=0x%x, "
			    "channels=%i, type=\"%s\"\n", cval->head.id,
			    cval->control, cval->cmask, cval->channels,
			    val_types[cval->val_type]);
	snd_iम_लिखो(buffer, "    Volume: min=%i, max=%i, dBmin=%i, dBmax=%i\n",
			    cval->min, cval->max, cval->dBmin, cval->dBmax);
पूर्ण

अटल व्योम snd_usb_mixer_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_usb_audio *chip = entry->निजी_data;
	काष्ठा usb_mixer_पूर्णांकerface *mixer;
	काष्ठा usb_mixer_elem_list *list;
	पूर्णांक unitid;

	list_क्रम_each_entry(mixer, &chip->mixer_list, list) अणु
		snd_iम_लिखो(buffer,
			"USB Mixer: usb_id=0x%08x, ctrlif=%i, ctlerr=%i\n",
				chip->usb_id, mixer_ctrl_पूर्णांकf(mixer),
				mixer->ignore_ctl_error);
		snd_iम_लिखो(buffer, "Card: %s\n", chip->card->दीर्घname);
		क्रम (unitid = 0; unitid < MAX_ID_ELEMS; unitid++) अणु
			क्रम_each_mixer_elem(list, mixer, unitid) अणु
				snd_iम_लिखो(buffer, "  Unit: %i\n", list->id);
				अगर (list->kctl)
					snd_iम_लिखो(buffer,
						    "    Control: name=\"%s\", index=%i\n",
						    list->kctl->id.name,
						    list->kctl->id.index);
				अगर (list->dump)
					list->dump(buffer, list);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_usb_mixer_पूर्णांकerrupt_v2(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				       पूर्णांक attribute, पूर्णांक value, पूर्णांक index)
अणु
	काष्ठा usb_mixer_elem_list *list;
	__u8 unitid = (index >> 8) & 0xff;
	__u8 control = (value >> 8) & 0xff;
	__u8 channel = value & 0xff;
	अचिन्हित पूर्णांक count = 0;

	अगर (channel >= MAX_CHANNELS) अणु
		usb_audio_dbg(mixer->chip,
			"%s(): bogus channel number %d\n",
			__func__, channel);
		वापस;
	पूर्ण

	unitid = delegate_notअगरy(mixer, unitid, &control, &channel);

	क्रम_each_mixer_elem(list, mixer, unitid)
		count++;

	अगर (count == 0)
		वापस;

	क्रम_each_mixer_elem(list, mixer, unitid) अणु
		काष्ठा usb_mixer_elem_info *info;

		अगर (!list->kctl)
			जारी;
		अगर (!list->is_std_info)
			जारी;

		info = mixer_elem_list_to_info(list);
		अगर (count > 1 && info->control != control)
			जारी;

		चयन (attribute) अणु
		हाल UAC2_CS_CUR:
			/* invalidate cache, so the value is पढ़ो from the device */
			अगर (channel)
				info->cached &= ~(1 << channel);
			अन्यथा /* master channel */
				info->cached = 0;

			snd_ctl_notअगरy(mixer->chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &info->head.kctl->id);
			अवरोध;

		हाल UAC2_CS_RANGE:
			/* TODO */
			अवरोध;

		हाल UAC2_CS_MEM:
			/* TODO */
			अवरोध;

		शेष:
			usb_audio_dbg(mixer->chip,
				"unknown attribute %d in interrupt\n",
				attribute);
			अवरोध;
		पूर्ण /* चयन */
	पूर्ण
पूर्ण

अटल व्योम snd_usb_mixer_पूर्णांकerrupt(काष्ठा urb *urb)
अणु
	काष्ठा usb_mixer_पूर्णांकerface *mixer = urb->context;
	पूर्णांक len = urb->actual_length;
	पूर्णांक ustatus = urb->status;

	अगर (ustatus != 0)
		जाओ requeue;

	अगर (mixer->protocol == UAC_VERSION_1) अणु
		काष्ठा uac1_status_word *status;

		क्रम (status = urb->transfer_buffer;
		     len >= माप(*status);
		     len -= माप(*status), status++) अणु
			dev_dbg(&urb->dev->dev, "status interrupt: %02x %02x\n",
						status->bStatusType,
						status->bOriginator);

			/* ignore any notअगरications not from the control पूर्णांकerface */
			अगर ((status->bStatusType & UAC1_STATUS_TYPE_ORIG_MASK) !=
				UAC1_STATUS_TYPE_ORIG_AUDIO_CONTROL_IF)
				जारी;

			अगर (status->bStatusType & UAC1_STATUS_TYPE_MEM_CHANGED)
				snd_usb_mixer_rc_memory_change(mixer, status->bOriginator);
			अन्यथा
				snd_usb_mixer_notअगरy_id(mixer, status->bOriginator);
		पूर्ण
	पूर्ण अन्यथा अणु /* UAC_VERSION_2 */
		काष्ठा uac2_पूर्णांकerrupt_data_msg *msg;

		क्रम (msg = urb->transfer_buffer;
		     len >= माप(*msg);
		     len -= माप(*msg), msg++) अणु
			/* drop venकरोr specअगरic and endpoपूर्णांक requests */
			अगर ((msg->bInfo & UAC2_INTERRUPT_DATA_MSG_VENDOR) ||
			    (msg->bInfo & UAC2_INTERRUPT_DATA_MSG_EP))
				जारी;

			snd_usb_mixer_पूर्णांकerrupt_v2(mixer, msg->bAttribute,
						   le16_to_cpu(msg->wValue),
						   le16_to_cpu(msg->wIndex));
		पूर्ण
	पूर्ण

requeue:
	अगर (ustatus != -ENOENT &&
	    ustatus != -ECONNRESET &&
	    ustatus != -ESHUTDOWN) अणु
		urb->dev = mixer->chip->dev;
		usb_submit_urb(urb, GFP_ATOMIC);
	पूर्ण
पूर्ण

/* create the handler क्रम the optional status पूर्णांकerrupt endpoपूर्णांक */
अटल पूर्णांक snd_usb_mixer_status_create(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	व्योम *transfer_buffer;
	पूर्णांक buffer_length;
	अचिन्हित पूर्णांक epnum;

	/* we need one पूर्णांकerrupt input endpoपूर्णांक */
	अगर (get_अगरace_desc(mixer->hostअगर)->bNumEndpoपूर्णांकs < 1)
		वापस 0;
	ep = get_endpoपूर्णांक(mixer->hostअगर, 0);
	अगर (!usb_endpoपूर्णांक_dir_in(ep) || !usb_endpoपूर्णांक_xfer_पूर्णांक(ep))
		वापस 0;

	epnum = usb_endpoपूर्णांक_num(ep);
	buffer_length = le16_to_cpu(ep->wMaxPacketSize);
	transfer_buffer = kदो_स्मृति(buffer_length, GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस -ENOMEM;
	mixer->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!mixer->urb) अणु
		kमुक्त(transfer_buffer);
		वापस -ENOMEM;
	पूर्ण
	usb_fill_पूर्णांक_urb(mixer->urb, mixer->chip->dev,
			 usb_rcvपूर्णांकpipe(mixer->chip->dev, epnum),
			 transfer_buffer, buffer_length,
			 snd_usb_mixer_पूर्णांकerrupt, mixer, ep->bInterval);
	usb_submit_urb(mixer->urb, GFP_KERNEL);
	वापस 0;
पूर्ण

पूर्णांक snd_usb_create_mixer(काष्ठा snd_usb_audio *chip, पूर्णांक ctrlअगर,
			 पूर्णांक ignore_error)
अणु
	अटल स्थिर काष्ठा snd_device_ops dev_ops = अणु
		.dev_मुक्त = snd_usb_mixer_dev_मुक्त
	पूर्ण;
	काष्ठा usb_mixer_पूर्णांकerface *mixer;
	पूर्णांक err;

	म_नकल(chip->card->mixername, "USB Mixer");

	mixer = kzalloc(माप(*mixer), GFP_KERNEL);
	अगर (!mixer)
		वापस -ENOMEM;
	mixer->chip = chip;
	mixer->ignore_ctl_error = ignore_error;
	mixer->id_elems = kसुस्मृति(MAX_ID_ELEMS, माप(*mixer->id_elems),
				  GFP_KERNEL);
	अगर (!mixer->id_elems) अणु
		kमुक्त(mixer);
		वापस -ENOMEM;
	पूर्ण

	mixer->hostअगर = &usb_अगरnum_to_अगर(chip->dev, ctrlअगर)->altsetting[0];
	चयन (get_अगरace_desc(mixer->hostअगर)->bInterfaceProtocol) अणु
	हाल UAC_VERSION_1:
	शेष:
		mixer->protocol = UAC_VERSION_1;
		अवरोध;
	हाल UAC_VERSION_2:
		mixer->protocol = UAC_VERSION_2;
		अवरोध;
	हाल UAC_VERSION_3:
		mixer->protocol = UAC_VERSION_3;
		अवरोध;
	पूर्ण

	अगर (mixer->protocol == UAC_VERSION_3 &&
			chip->badd_profile >= UAC3_FUNCTION_SUBCLASS_GENERIC_IO) अणु
		err = snd_usb_mixer_controls_badd(mixer, ctrlअगर);
		अगर (err < 0)
			जाओ _error;
	पूर्ण अन्यथा अणु
		err = snd_usb_mixer_controls(mixer);
		अगर (err < 0)
			जाओ _error;
	पूर्ण

	err = snd_usb_mixer_status_create(mixer);
	अगर (err < 0)
		जाओ _error;

	err = snd_usb_mixer_apply_create_quirk(mixer);
	अगर (err < 0)
		जाओ _error;

	err = snd_device_new(chip->card, SNDRV_DEV_CODEC, mixer, &dev_ops);
	अगर (err < 0)
		जाओ _error;

	अगर (list_empty(&chip->mixer_list))
		snd_card_ro_proc_new(chip->card, "usbmixer", chip,
				     snd_usb_mixer_proc_पढ़ो);

	list_add(&mixer->list, &chip->mixer_list);
	वापस 0;

_error:
	snd_usb_mixer_मुक्त(mixer);
	वापस err;
पूर्ण

व्योम snd_usb_mixer_disconnect(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	अगर (mixer->disconnected)
		वापस;
	अगर (mixer->urb)
		usb_समाप्त_urb(mixer->urb);
	अगर (mixer->rc_urb)
		usb_समाप्त_urb(mixer->rc_urb);
	अगर (mixer->निजी_मुक्त)
		mixer->निजी_मुक्त(mixer);
	mixer->disconnected = true;
पूर्ण

#अगर_घोषित CONFIG_PM
/* stop any bus activity of a mixer */
अटल व्योम snd_usb_mixer_inactivate(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	usb_समाप्त_urb(mixer->urb);
	usb_समाप्त_urb(mixer->rc_urb);
पूर्ण

अटल पूर्णांक snd_usb_mixer_activate(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	पूर्णांक err;

	अगर (mixer->urb) अणु
		err = usb_submit_urb(mixer->urb, GFP_NOIO);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_usb_mixer_suspend(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	snd_usb_mixer_inactivate(mixer);
	अगर (mixer->निजी_suspend)
		mixer->निजी_suspend(mixer);
	वापस 0;
पूर्ण

अटल पूर्णांक restore_mixer_value(काष्ठा usb_mixer_elem_list *list)
अणु
	काष्ठा usb_mixer_elem_info *cval = mixer_elem_list_to_info(list);
	पूर्णांक c, err, idx;

	अगर (cval->cmask) अणु
		idx = 0;
		क्रम (c = 0; c < MAX_CHANNELS; c++) अणु
			अगर (!(cval->cmask & (1 << c)))
				जारी;
			अगर (cval->cached & (1 << (c + 1))) अणु
				err = snd_usb_set_cur_mix_value(cval, c + 1, idx,
							cval->cache_val[idx]);
				अगर (err < 0)
					वापस err;
			पूर्ण
			idx++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* master */
		अगर (cval->cached) अणु
			err = snd_usb_set_cur_mix_value(cval, 0, 0, *cval->cache_val);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक शेष_mixer_resume(काष्ठा usb_mixer_elem_list *list)
अणु
	काष्ठा usb_mixer_elem_info *cval = mixer_elem_list_to_info(list);

	/* get connector value to "wake up" the USB audio */
	अगर (cval->val_type == USB_MIXER_BOOLEAN && cval->channels == 1)
		get_connector_value(cval, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक शेष_mixer_reset_resume(काष्ठा usb_mixer_elem_list *list)
अणु
	पूर्णांक err = शेष_mixer_resume(list);

	अगर (err < 0)
		वापस err;
	वापस restore_mixer_value(list);
पूर्ण

पूर्णांक snd_usb_mixer_resume(काष्ठा usb_mixer_पूर्णांकerface *mixer, bool reset_resume)
अणु
	काष्ठा usb_mixer_elem_list *list;
	usb_mixer_elem_resume_func_t f;
	पूर्णांक id, err;

	/* restore cached mixer values */
	क्रम (id = 0; id < MAX_ID_ELEMS; id++) अणु
		क्रम_each_mixer_elem(list, mixer, id) अणु
			अगर (reset_resume)
				f = list->reset_resume;
			अन्यथा
				f = list->resume;
			अगर (f) अणु
				err = f(list);
				अगर (err < 0)
					वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	snd_usb_mixer_resume_quirk(mixer);

	वापस snd_usb_mixer_activate(mixer);
पूर्ण
#पूर्ण_अगर

व्योम snd_usb_mixer_elem_init_std(काष्ठा usb_mixer_elem_list *list,
				 काष्ठा usb_mixer_पूर्णांकerface *mixer,
				 पूर्णांक unitid)
अणु
	list->mixer = mixer;
	list->id = unitid;
	list->dump = snd_usb_mixer_dump_cval;
#अगर_घोषित CONFIG_PM
	list->resume = शेष_mixer_resume;
	list->reset_resume = शेष_mixer_reset_resume;
#पूर्ण_अगर
पूर्ण
