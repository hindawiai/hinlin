<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __USBAUDIO_H
#घोषणा __USBAUDIO_H
/*
 *   (Tentative) USB Audio Driver क्रम ALSA
 *
 *   Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

/* handling of USB venकरोr/product ID pairs as 32-bit numbers */
#घोषणा USB_ID(venकरोr, product) (((venकरोr) << 16) | (product))
#घोषणा USB_ID_VENDOR(id) ((id) >> 16)
#घोषणा USB_ID_PRODUCT(id) ((u16)(id))

/*
 *
 */

काष्ठा media_device;
काष्ठा media_पूर्णांकf_devnode;

#घोषणा MAX_CARD_INTERFACES	16

काष्ठा snd_usb_audio अणु
	पूर्णांक index;
	काष्ठा usb_device *dev;
	काष्ठा snd_card *card;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf[MAX_CARD_INTERFACES];
	u32 usb_id;
	uपूर्णांक16_t quirk_type;
	काष्ठा mutex mutex;
	अचिन्हित पूर्णांक प्रणाली_suspend;
	atomic_t active;
	atomic_t shutकरोwn;
	atomic_t usage_count;
	रुको_queue_head_t shutकरोwn_रुको;
	अचिन्हित पूर्णांक txfr_quirk:1; /* Subframe boundaries on transfers */
	अचिन्हित पूर्णांक tx_length_quirk:1; /* Put length specअगरier in transfers */
	अचिन्हित पूर्णांक need_delayed_रेजिस्टर:1; /* warn क्रम delayed registration */
	अचिन्हित पूर्णांक playback_first:1;	/* क्रम implicit fb: करोn't रुको क्रम the first capture URBs */
	पूर्णांक num_पूर्णांकerfaces;
	पूर्णांक num_suspended_पूर्णांकf;
	पूर्णांक sample_rate_पढ़ो_error;

	पूर्णांक badd_profile;		/* UAC3 BADD profile */

	काष्ठा list_head pcm_list;	/* list of pcm streams */
	काष्ठा list_head ep_list;	/* list of audio-related endpoपूर्णांकs */
	काष्ठा list_head अगरace_ref_list; /* list of पूर्णांकerface refcounts */
	पूर्णांक pcm_devs;

	काष्ठा list_head midi_list;	/* list of midi पूर्णांकerfaces */

	काष्ठा list_head mixer_list;	/* list of mixer पूर्णांकerfaces */

	पूर्णांक setup;			/* from the 'device_setup' module param */
	bool generic_implicit_fb;	/* from the 'implicit_fb' module param */
	bool स्वतःघड़ी;			/* from the 'autoclock' module param */

	काष्ठा usb_host_पूर्णांकerface *ctrl_पूर्णांकf;	/* the audio control पूर्णांकerface */
	काष्ठा media_device *media_dev;
	काष्ठा media_पूर्णांकf_devnode *ctl_पूर्णांकf_media_devnode;
पूर्ण;

#घोषणा USB_AUDIO_IFACE_UNUSED	((व्योम *)-1L)

#घोषणा usb_audio_err(chip, fmt, args...) \
	dev_err(&(chip)->dev->dev, fmt, ##args)
#घोषणा usb_audio_warn(chip, fmt, args...) \
	dev_warn(&(chip)->dev->dev, fmt, ##args)
#घोषणा usb_audio_info(chip, fmt, args...) \
	dev_info(&(chip)->dev->dev, fmt, ##args)
#घोषणा usb_audio_dbg(chip, fmt, args...) \
	dev_dbg(&(chip)->dev->dev, fmt, ##args)

/*
 * Inक्रमmation about devices with broken descriptors
 */

/* special values क्रम .अगरnum */
#घोषणा QUIRK_NODEV_INTERFACE		-3	/* वापस -ENODEV */
#घोषणा QUIRK_NO_INTERFACE		-2
#घोषणा QUIRK_ANY_INTERFACE		-1

क्रमागत quirk_type अणु
	QUIRK_IGNORE_INTERFACE,
	QUIRK_COMPOSITE,
	QUIRK_AUTODETECT,
	QUIRK_MIDI_STANDARD_INTERFACE,
	QUIRK_MIDI_FIXED_ENDPOINT,
	QUIRK_MIDI_YAMAHA,
	QUIRK_MIDI_ROLAND,
	QUIRK_MIDI_MIDIMAN,
	QUIRK_MIDI_NOVATION,
	QUIRK_MIDI_RAW_BYTES,
	QUIRK_MIDI_EMAGIC,
	QUIRK_MIDI_CME,
	QUIRK_MIDI_AKAI,
	QUIRK_MIDI_US122L,
	QUIRK_MIDI_FTDI,
	QUIRK_MIDI_CH345,
	QUIRK_AUDIO_STANDARD_INTERFACE,
	QUIRK_AUDIO_FIXED_ENDPOINT,
	QUIRK_AUDIO_EसूचीOL_UAXX,
	QUIRK_AUDIO_ALIGN_TRANSFER,
	QUIRK_AUDIO_STANDARD_MIXER,
	QUIRK_SETUP_FMT_AFTER_RESUME,
	QUIRK_SETUP_DISABLE_AUTOSUSPEND,

	QUIRK_TYPE_COUNT
पूर्ण;

काष्ठा snd_usb_audio_quirk अणु
	स्थिर अक्षर *venकरोr_name;
	स्थिर अक्षर *product_name;
	पूर्णांक16_t अगरnum;
	uपूर्णांक16_t type;
	bool shares_media_device;
	स्थिर व्योम *data;
पूर्ण;

#घोषणा combine_word(s)    ((*(s)) | ((अचिन्हित पूर्णांक)(s)[1] << 8))
#घोषणा combine_triple(s)  (combine_word(s) | ((अचिन्हित पूर्णांक)(s)[2] << 16))
#घोषणा combine_quad(s)    (combine_triple(s) | ((अचिन्हित पूर्णांक)(s)[3] << 24))

पूर्णांक snd_usb_lock_shutकरोwn(काष्ठा snd_usb_audio *chip);
व्योम snd_usb_unlock_shutकरोwn(काष्ठा snd_usb_audio *chip);

बाह्य bool snd_usb_use_vदो_स्मृति;
बाह्य bool snd_usb_skip_validation;

#पूर्ण_अगर /* __USBAUDIO_H */
