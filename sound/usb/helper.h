<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USBAUDIO_HELPER_H
#घोषणा __USBAUDIO_HELPER_H

अचिन्हित पूर्णांक snd_usb_combine_bytes(अचिन्हित अक्षर *bytes, पूर्णांक size);

व्योम *snd_usb_find_desc(व्योम *descstart, पूर्णांक desclen, व्योम *after, u8 dtype);
व्योम *snd_usb_find_csपूर्णांक_desc(व्योम *descstart, पूर्णांक desclen, व्योम *after, u8 dsubtype);

पूर्णांक snd_usb_ctl_msg(काष्ठा usb_device *dev, अचिन्हित पूर्णांक pipe,
		    __u8 request, __u8 requesttype, __u16 value, __u16 index,
		    व्योम *data, __u16 size);

अचिन्हित अक्षर snd_usb_parse_dataपूर्णांकerval(काष्ठा snd_usb_audio *chip,
					 काष्ठा usb_host_पूर्णांकerface *alts);

काष्ठा usb_host_पूर्णांकerface *
snd_usb_get_host_पूर्णांकerface(काष्ठा snd_usb_audio *chip, पूर्णांक अगरnum, पूर्णांक altsetting);

/*
 * retrieve usb_पूर्णांकerface descriptor from the host पूर्णांकerface
 * (conditional क्रम compatibility with the older API)
 */
#घोषणा get_अगरace_desc(अगरace)	(&(अगरace)->desc)
#घोषणा get_endpoपूर्णांक(alt,ep)	(&(alt)->endpoपूर्णांक[ep].desc)
#घोषणा get_ep_desc(ep)		(&(ep)->desc)
#घोषणा get_cfg_desc(cfg)	(&(cfg)->desc)

#घोषणा snd_usb_get_speed(dev) ((dev)->speed)

अटल अंतरभूत पूर्णांक snd_usb_ctrl_पूर्णांकf(काष्ठा snd_usb_audio *chip)
अणु
	वापस get_अगरace_desc(chip->ctrl_पूर्णांकf)->bInterfaceNumber;
पूर्ण

/* in validate.c */
bool snd_usb_validate_audio_desc(व्योम *p, पूर्णांक protocol);
bool snd_usb_validate_midi_desc(व्योम *p);

#पूर्ण_अगर /* __USBAUDIO_HELPER_H */
