<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USBMIXER_H
#घोषणा __USBMIXER_H

#समावेश <sound/info.h>

काष्ठा media_mixer_ctl;

काष्ठा usbmix_connector_map अणु
	u8 id;
	u8 delegated_id;
	u8 control;
	u8 channel;
पूर्ण;

काष्ठा usb_mixer_पूर्णांकerface अणु
	काष्ठा snd_usb_audio *chip;
	काष्ठा usb_host_पूर्णांकerface *hostअगर;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक ignore_ctl_error;
	काष्ठा urb *urb;
	/* array[MAX_ID_ELEMS], indexed by unit id */
	काष्ठा usb_mixer_elem_list **id_elems;

	/* the usb audio specअगरication version this पूर्णांकerface complies to */
	पूर्णांक protocol;

	/* optional connector delegation map */
	स्थिर काष्ठा usbmix_connector_map *connector_map;

	/* Sound Blaster remote control stuff */
	स्थिर काष्ठा rc_config *rc_cfg;
	u32 rc_code;
	रुको_queue_head_t rc_रुकोq;
	काष्ठा urb *rc_urb;
	काष्ठा usb_ctrlrequest *rc_setup_packet;
	u8 rc_buffer[6];
	काष्ठा media_mixer_ctl *media_mixer_ctl;

	bool disconnected;

	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा usb_mixer_पूर्णांकerface *mixer);
	व्योम (*निजी_suspend)(काष्ठा usb_mixer_पूर्णांकerface *mixer);
पूर्ण;

#घोषणा MAX_CHANNELS	16	/* max logical channels */

क्रमागत अणु
	USB_MIXER_BOOLEAN,
	USB_MIXER_INV_BOOLEAN,
	USB_MIXER_S8,
	USB_MIXER_U8,
	USB_MIXER_S16,
	USB_MIXER_U16,
	USB_MIXER_S32,
	USB_MIXER_U32,
पूर्ण;

प्रकार व्योम (*usb_mixer_elem_dump_func_t)(काष्ठा snd_info_buffer *buffer,
					 काष्ठा usb_mixer_elem_list *list);
प्रकार पूर्णांक (*usb_mixer_elem_resume_func_t)(काष्ठा usb_mixer_elem_list *elem);

काष्ठा usb_mixer_elem_list अणु
	काष्ठा usb_mixer_पूर्णांकerface *mixer;
	काष्ठा usb_mixer_elem_list *next_id_elem; /* list of controls with same id */
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक id;
	bool is_std_info;
	usb_mixer_elem_dump_func_t dump;
	usb_mixer_elem_resume_func_t resume;
	usb_mixer_elem_resume_func_t reset_resume;
पूर्ण;

/* iterate over mixer element list of the given unit id */
#घोषणा क्रम_each_mixer_elem(list, mixer, id)	\
	क्रम ((list) = (mixer)->id_elems[id]; (list); (list) = (list)->next_id_elem)
#घोषणा mixer_elem_list_to_info(list) \
	container_of(list, काष्ठा usb_mixer_elem_info, head)

काष्ठा usb_mixer_elem_info अणु
	काष्ठा usb_mixer_elem_list head;
	अचिन्हित पूर्णांक control;	/* CS or ICN (high byte) */
	अचिन्हित पूर्णांक cmask; /* channel mask biपंचांगap: 0 = master */
	अचिन्हित पूर्णांक idx_off; /* Control index offset */
	अचिन्हित पूर्णांक ch_पढ़ोonly;
	अचिन्हित पूर्णांक master_पढ़ोonly;
	पूर्णांक channels;
	पूर्णांक val_type;
	पूर्णांक min, max, res;
	पूर्णांक dBmin, dBmax;
	पूर्णांक cached;
	पूर्णांक cache_val[MAX_CHANNELS];
	u8 initialized;
	u8 min_mute;
	व्योम *निजी_data;
पूर्ण;

पूर्णांक snd_usb_create_mixer(काष्ठा snd_usb_audio *chip, पूर्णांक ctrlअगर,
			 पूर्णांक ignore_error);
व्योम snd_usb_mixer_disconnect(काष्ठा usb_mixer_पूर्णांकerface *mixer);

व्योम snd_usb_mixer_notअगरy_id(काष्ठा usb_mixer_पूर्णांकerface *mixer, पूर्णांक unitid);

पूर्णांक snd_usb_mixer_set_ctl_value(काष्ठा usb_mixer_elem_info *cval,
				पूर्णांक request, पूर्णांक validx, पूर्णांक value_set);

पूर्णांक snd_usb_mixer_add_list(काष्ठा usb_mixer_elem_list *list,
			   काष्ठा snd_kcontrol *kctl,
			   bool is_std_info);

#घोषणा snd_usb_mixer_add_control(list, kctl) \
	snd_usb_mixer_add_list(list, kctl, true)

व्योम snd_usb_mixer_elem_init_std(काष्ठा usb_mixer_elem_list *list,
				 काष्ठा usb_mixer_पूर्णांकerface *mixer,
				 पूर्णांक unitid);

पूर्णांक snd_usb_mixer_vol_tlv(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
			  अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *_tlv);

#अगर_घोषित CONFIG_PM
पूर्णांक snd_usb_mixer_suspend(काष्ठा usb_mixer_पूर्णांकerface *mixer);
पूर्णांक snd_usb_mixer_resume(काष्ठा usb_mixer_पूर्णांकerface *mixer, bool reset_resume);
#पूर्ण_अगर

पूर्णांक snd_usb_set_cur_mix_value(काष्ठा usb_mixer_elem_info *cval, पूर्णांक channel,
                             पूर्णांक index, पूर्णांक value);

पूर्णांक snd_usb_get_cur_mix_value(काष्ठा usb_mixer_elem_info *cval,
                             पूर्णांक channel, पूर्णांक index, पूर्णांक *value);

बाह्य व्योम snd_usb_mixer_elem_मुक्त(काष्ठा snd_kcontrol *kctl);

बाह्य स्थिर काष्ठा snd_kcontrol_new *snd_usb_feature_unit_ctl;

#पूर्ण_अगर /* __USBMIXER_H */
