<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SND_USB_MIXER_QUIRKS_H
#घोषणा SND_USB_MIXER_QUIRKS_H

पूर्णांक snd_usb_mixer_apply_create_quirk(काष्ठा usb_mixer_पूर्णांकerface *mixer);

व्योम snd_emuusb_set_samplerate(काष्ठा snd_usb_audio *chip,
			       अचिन्हित अक्षर samplerate_id);

व्योम snd_usb_mixer_rc_memory_change(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				    पूर्णांक unitid);

व्योम snd_usb_mixer_fu_apply_quirk(काष्ठा usb_mixer_पूर्णांकerface *mixer,
				  काष्ठा usb_mixer_elem_info *cval, पूर्णांक unitid,
				  काष्ठा snd_kcontrol *kctl);

#अगर_घोषित CONFIG_PM
व्योम snd_usb_mixer_resume_quirk(काष्ठा usb_mixer_पूर्णांकerface *mixer);
#पूर्ण_अगर

#पूर्ण_अगर /* SND_USB_MIXER_QUIRKS_H */

