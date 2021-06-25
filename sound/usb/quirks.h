<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USBAUDIO_QUIRKS_H
#घोषणा __USBAUDIO_QUIRKS_H

काष्ठा audioक्रमmat;
काष्ठा snd_usb_endpoपूर्णांक;
काष्ठा snd_usb_substream;

पूर्णांक snd_usb_create_quirk(काष्ठा snd_usb_audio *chip,
			 काष्ठा usb_पूर्णांकerface *अगरace,
			 काष्ठा usb_driver *driver,
			 स्थिर काष्ठा snd_usb_audio_quirk *quirk);

पूर्णांक snd_usb_apply_पूर्णांकerface_quirk(काष्ठा snd_usb_audio *chip,
				  पूर्णांक अगरace,
				  पूर्णांक altno);

पूर्णांक snd_usb_apply_boot_quirk(काष्ठा usb_device *dev,
			     काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     स्थिर काष्ठा snd_usb_audio_quirk *quirk,
			     अचिन्हित पूर्णांक usb_id);

पूर्णांक snd_usb_apply_boot_quirk_once(काष्ठा usb_device *dev,
				  काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				  स्थिर काष्ठा snd_usb_audio_quirk *quirk,
				  अचिन्हित पूर्णांक usb_id);

व्योम snd_usb_set_क्रमmat_quirk(काष्ठा snd_usb_substream *subs,
			      स्थिर काष्ठा audioक्रमmat *fmt);

bool snd_usb_get_sample_rate_quirk(काष्ठा snd_usb_audio *chip);

पूर्णांक snd_usb_is_big_endian_क्रमmat(काष्ठा snd_usb_audio *chip,
				 स्थिर काष्ठा audioक्रमmat *fp);

व्योम snd_usb_endpoपूर्णांक_start_quirk(काष्ठा snd_usb_endpoपूर्णांक *ep);

व्योम snd_usb_set_पूर्णांकerface_quirk(काष्ठा snd_usb_audio *chip);
व्योम snd_usb_ctl_msg_quirk(काष्ठा usb_device *dev, अचिन्हित पूर्णांक pipe,
			   __u8 request, __u8 requesttype, __u16 value,
			   __u16 index, व्योम *data, __u16 size);

पूर्णांक snd_usb_select_mode_quirk(काष्ठा snd_usb_audio *chip,
			      स्थिर काष्ठा audioक्रमmat *fmt);

u64 snd_usb_पूर्णांकerface_dsd_क्रमmat_quirks(काष्ठा snd_usb_audio *chip,
					काष्ठा audioक्रमmat *fp,
					अचिन्हित पूर्णांक sample_bytes);

व्योम snd_usb_audioक्रमmat_attributes_quirk(काष्ठा snd_usb_audio *chip,
					  काष्ठा audioक्रमmat *fp,
					  पूर्णांक stream);

bool snd_usb_registration_quirk(काष्ठा snd_usb_audio *chip, पूर्णांक अगरace);

#पूर्ण_अगर /* __USBAUDIO_QUIRKS_H */
