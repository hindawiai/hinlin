<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   (Tentative) USB Audio Driver क्रम ALSA
 *
 *   Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 *
 *   Many codes borrowed from audio.c by
 *	    Alan Cox (alan@lxorguk.ukuu.org.uk)
 *	    Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *   Audio Class 3.0 support by Ruslan Bilovol <ruslan.bilovol@gmail.com>
 *
 *  NOTES:
 *
 *   - the linked URBs would be preferred but not used so far because of
 *     the instability of unlinking.
 *   - type II is not supported properly.  there is no device which supports
 *     this type *correctly*.  SB extigy looks as अगर it supports, but it's
 *     indeed an AC3 stream packed in SPDIF frames (i.e. no real AC3 stream).
 */


#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/usb.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/audio-v2.h>
#समावेश <linux/usb/audio-v3.h>
#समावेश <linux/module.h>

#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>

#समावेश "usbaudio.h"
#समावेश "card.h"
#समावेश "midi.h"
#समावेश "mixer.h"
#समावेश "proc.h"
#समावेश "quirks.h"
#समावेश "endpoint.h"
#समावेश "helper.h"
#समावेश "pcm.h"
#समावेश "format.h"
#समावेश "power.h"
#समावेश "stream.h"
#समावेश "media.h"

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("USB Audio");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;/* Enable this card */
/* Venकरोr/product IDs क्रम this card */
अटल पूर्णांक vid[SNDRV_CARDS] = अणु [0 ... (SNDRV_CARDS-1)] = -1 पूर्ण;
अटल पूर्णांक pid[SNDRV_CARDS] = अणु [0 ... (SNDRV_CARDS-1)] = -1 पूर्ण;
अटल पूर्णांक device_setup[SNDRV_CARDS]; /* device parameter क्रम this card */
अटल bool ignore_ctl_error;
अटल bool स्वतःघड़ी = true;
अटल अक्षर *quirk_alias[SNDRV_CARDS];
अटल अक्षर *delayed_रेजिस्टर[SNDRV_CARDS];
अटल bool implicit_fb[SNDRV_CARDS];

bool snd_usb_use_vदो_स्मृति = true;
bool snd_usb_skip_validation;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the USB audio adapter.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the USB audio adapter.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable USB audio adapter.");
module_param_array(vid, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(vid, "Vendor ID for the USB audio device.");
module_param_array(pid, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pid, "Product ID for the USB audio device.");
module_param_array(device_setup, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(device_setup, "Specific device setup (if needed).");
module_param(ignore_ctl_error, bool, 0444);
MODULE_PARM_DESC(ignore_ctl_error,
		 "Ignore errors from USB controller for mixer interfaces.");
module_param(स्वतःघड़ी, bool, 0444);
MODULE_PARM_DESC(स्वतःघड़ी, "Enable auto-clock selection for UAC2 devices (default: yes).");
module_param_array(quirk_alias, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(quirk_alias, "Quirk aliases, e.g. 0123abcd:5678beef.");
module_param_array(delayed_रेजिस्टर, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(delayed_रेजिस्टर, "Quirk for delayed registration, given by id:iface, e.g. 0123abcd:4.");
module_param_array(implicit_fb, bool, शून्य, 0444);
MODULE_PARM_DESC(implicit_fb, "Apply generic implicit feedback sync mode.");
module_param_named(use_vदो_स्मृति, snd_usb_use_vदो_स्मृति, bool, 0444);
MODULE_PARM_DESC(use_vदो_स्मृति, "Use vmalloc for PCM intermediate buffers (default: yes).");
module_param_named(skip_validation, snd_usb_skip_validation, bool, 0444);
MODULE_PARM_DESC(skip_validation, "Skip unit descriptor validation (default: no).");

/*
 * we keep the snd_usb_audio_t instances by ourselves क्रम merging
 * the all पूर्णांकerfaces on the same card as one sound device.
 */

अटल DEFINE_MUTEX(रेजिस्टर_mutex);
अटल काष्ठा snd_usb_audio *usb_chip[SNDRV_CARDS];
अटल काष्ठा usb_driver usb_audio_driver;

/*
 * disconnect streams
 * called from usb_audio_disconnect()
 */
अटल व्योम snd_usb_stream_disconnect(काष्ठा snd_usb_stream *as)
अणु
	पूर्णांक idx;
	काष्ठा snd_usb_substream *subs;

	क्रम (idx = 0; idx < 2; idx++) अणु
		subs = &as->substream[idx];
		अगर (!subs->num_क्रमmats)
			जारी;
		subs->data_endpoपूर्णांक = शून्य;
		subs->sync_endpoपूर्णांक = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_usb_create_stream(काष्ठा snd_usb_audio *chip, पूर्णांक ctrlअगर, पूर्णांक पूर्णांकerface)
अणु
	काष्ठा usb_device *dev = chip->dev;
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_पूर्णांकerface_descriptor *altsd;
	काष्ठा usb_पूर्णांकerface *अगरace = usb_अगरnum_to_अगर(dev, पूर्णांकerface);

	अगर (!अगरace) अणु
		dev_err(&dev->dev, "%u:%d : does not exist\n",
			ctrlअगर, पूर्णांकerface);
		वापस -EINVAL;
	पूर्ण

	alts = &अगरace->altsetting[0];
	altsd = get_अगरace_desc(alts);

	/*
	 * Android with both accessory and audio पूर्णांकerfaces enabled माला_लो the
	 * पूर्णांकerface numbers wrong.
	 */
	अगर ((chip->usb_id == USB_ID(0x18d1, 0x2d04) ||
	     chip->usb_id == USB_ID(0x18d1, 0x2d05)) &&
	    पूर्णांकerface == 0 &&
	    altsd->bInterfaceClass == USB_CLASS_VENDOR_SPEC &&
	    altsd->bInterfaceSubClass == USB_SUBCLASS_VENDOR_SPEC) अणु
		पूर्णांकerface = 2;
		अगरace = usb_अगरnum_to_अगर(dev, पूर्णांकerface);
		अगर (!अगरace)
			वापस -EINVAL;
		alts = &अगरace->altsetting[0];
		altsd = get_अगरace_desc(alts);
	पूर्ण

	अगर (usb_पूर्णांकerface_claimed(अगरace)) अणु
		dev_dbg(&dev->dev, "%d:%d: skipping, already claimed\n",
			ctrlअगर, पूर्णांकerface);
		वापस -EINVAL;
	पूर्ण

	अगर ((altsd->bInterfaceClass == USB_CLASS_AUDIO ||
	     altsd->bInterfaceClass == USB_CLASS_VENDOR_SPEC) &&
	    altsd->bInterfaceSubClass == USB_SUBCLASS_MIDISTREAMING) अणु
		पूर्णांक err = __snd_usbmidi_create(chip->card, अगरace,
					     &chip->midi_list, शून्य,
					     chip->usb_id);
		अगर (err < 0) अणु
			dev_err(&dev->dev,
				"%u:%d: cannot create sequencer device\n",
				ctrlअगर, पूर्णांकerface);
			वापस -EINVAL;
		पूर्ण
		वापस usb_driver_claim_पूर्णांकerface(&usb_audio_driver, अगरace,
						  USB_AUDIO_IFACE_UNUSED);
	पूर्ण

	अगर ((altsd->bInterfaceClass != USB_CLASS_AUDIO &&
	     altsd->bInterfaceClass != USB_CLASS_VENDOR_SPEC) ||
	    altsd->bInterfaceSubClass != USB_SUBCLASS_AUDIOSTREAMING) अणु
		dev_dbg(&dev->dev,
			"%u:%d: skipping non-supported interface %d\n",
			ctrlअगर, पूर्णांकerface, altsd->bInterfaceClass);
		/* skip non-supported classes */
		वापस -EINVAL;
	पूर्ण

	अगर (snd_usb_get_speed(dev) == USB_SPEED_LOW) अणु
		dev_err(&dev->dev, "low speed audio streaming not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (! snd_usb_parse_audio_पूर्णांकerface(chip, पूर्णांकerface)) अणु
		usb_set_पूर्णांकerface(dev, पूर्णांकerface, 0); /* reset the current पूर्णांकerface */
		वापस usb_driver_claim_पूर्णांकerface(&usb_audio_driver, अगरace,
						  USB_AUDIO_IFACE_UNUSED);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * parse audio control descriptor and create pcm/midi streams
 */
अटल पूर्णांक snd_usb_create_streams(काष्ठा snd_usb_audio *chip, पूर्णांक ctrlअगर)
अणु
	काष्ठा usb_device *dev = chip->dev;
	काष्ठा usb_host_पूर्णांकerface *host_अगरace;
	काष्ठा usb_पूर्णांकerface_descriptor *altsd;
	पूर्णांक i, protocol;

	/* find audiocontrol पूर्णांकerface */
	host_अगरace = &usb_अगरnum_to_अगर(dev, ctrlअगर)->altsetting[0];
	altsd = get_अगरace_desc(host_अगरace);
	protocol = altsd->bInterfaceProtocol;

	चयन (protocol) अणु
	शेष:
		dev_warn(&dev->dev,
			 "unknown interface protocol %#02x, assuming v1\n",
			 protocol);
		fallthrough;

	हाल UAC_VERSION_1: अणु
		काष्ठा uac1_ac_header_descriptor *h1;
		पूर्णांक rest_bytes;

		h1 = snd_usb_find_csपूर्णांक_desc(host_अगरace->extra,
							 host_अगरace->extralen,
							 शून्य, UAC_HEADER);
		अगर (!h1 || h1->bLength < माप(*h1)) अणु
			dev_err(&dev->dev, "cannot find UAC_HEADER\n");
			वापस -EINVAL;
		पूर्ण

		rest_bytes = (व्योम *)(host_अगरace->extra +
				host_अगरace->extralen) - (व्योम *)h1;

		/* just to be sure -- this shouldn't hit at all */
		अगर (rest_bytes <= 0) अणु
			dev_err(&dev->dev, "invalid control header\n");
			वापस -EINVAL;
		पूर्ण

		अगर (rest_bytes < माप(*h1)) अणु
			dev_err(&dev->dev, "too short v1 buffer descriptor\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!h1->bInCollection) अणु
			dev_info(&dev->dev, "skipping empty audio interface (v1)\n");
			वापस -EINVAL;
		पूर्ण

		अगर (rest_bytes < h1->bLength) अणु
			dev_err(&dev->dev, "invalid buffer length (v1)\n");
			वापस -EINVAL;
		पूर्ण

		अगर (h1->bLength < माप(*h1) + h1->bInCollection) अणु
			dev_err(&dev->dev, "invalid UAC_HEADER (v1)\n");
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < h1->bInCollection; i++)
			snd_usb_create_stream(chip, ctrlअगर, h1->baInterfaceNr[i]);

		अवरोध;
	पूर्ण

	हाल UAC_VERSION_2:
	हाल UAC_VERSION_3: अणु
		काष्ठा usb_पूर्णांकerface_assoc_descriptor *assoc =
			usb_अगरnum_to_अगर(dev, ctrlअगर)->पूर्णांकf_assoc;

		अगर (!assoc) अणु
			/*
			 * Firmware ग_लिखोrs cannot count to three.  So to find
			 * the IAD on the NuForce UDH-100, also check the next
			 * पूर्णांकerface.
			 */
			काष्ठा usb_पूर्णांकerface *अगरace =
				usb_अगरnum_to_अगर(dev, ctrlअगर + 1);
			अगर (अगरace &&
			    अगरace->पूर्णांकf_assoc &&
			    अगरace->पूर्णांकf_assoc->bFunctionClass == USB_CLASS_AUDIO &&
			    अगरace->पूर्णांकf_assoc->bFunctionProtocol == UAC_VERSION_2)
				assoc = अगरace->पूर्णांकf_assoc;
		पूर्ण

		अगर (!assoc) अणु
			dev_err(&dev->dev, "Audio class v2/v3 interfaces need an interface association\n");
			वापस -EINVAL;
		पूर्ण

		अगर (protocol == UAC_VERSION_3) अणु
			पूर्णांक badd = assoc->bFunctionSubClass;

			अगर (badd != UAC3_FUNCTION_SUBCLASS_FULL_ADC_3_0 &&
			    (badd < UAC3_FUNCTION_SUBCLASS_GENERIC_IO ||
			     badd > UAC3_FUNCTION_SUBCLASS_SPEAKERPHONE)) अणु
				dev_err(&dev->dev,
					"Unsupported UAC3 BADD profile\n");
				वापस -EINVAL;
			पूर्ण

			chip->badd_profile = badd;
		पूर्ण

		क्रम (i = 0; i < assoc->bInterfaceCount; i++) अणु
			पूर्णांक पूर्णांकf = assoc->bFirstInterface + i;

			अगर (पूर्णांकf != ctrlअगर)
				snd_usb_create_stream(chip, ctrlअगर, पूर्णांकf);
		पूर्ण

		अवरोध;
	पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Profile name preset table
 */
काष्ठा usb_audio_device_name अणु
	u32 id;
	स्थिर अक्षर *venकरोr_name;
	स्थिर अक्षर *product_name;
	स्थिर अक्षर *profile_name;	/* override card->दीर्घname */
पूर्ण;

#घोषणा PROखाता_NAME(vid, pid, venकरोr, product, profile)	 \
	अणु .id = USB_ID(vid, pid), .venकरोr_name = (venकरोr),	 \
	  .product_name = (product), .profile_name = (profile) पूर्ण
#घोषणा DEVICE_NAME(vid, pid, venकरोr, product) \
	PROखाता_NAME(vid, pid, venकरोr, product, शून्य)

/* venकरोr/product and profile name presets, sorted in device id order */
अटल स्थिर काष्ठा usb_audio_device_name usb_audio_names[] = अणु
	/* HP Thunderbolt Dock Audio Headset */
	PROखाता_NAME(0x03f0, 0x0269, "HP", "Thunderbolt Dock Audio Headset",
		     "HP-Thunderbolt-Dock-Audio-Headset"),
	/* HP Thunderbolt Dock Audio Module */
	PROखाता_NAME(0x03f0, 0x0567, "HP", "Thunderbolt Dock Audio Module",
		     "HP-Thunderbolt-Dock-Audio-Module"),

	/* Two entries क्रम Gigabyte TRX40 Aorus Master:
	 * TRX40 Aorus Master has two USB-audio devices, one क्रम the front
	 * headphone with ESS SABRE9218 DAC chip, जबतक another क्रम the rest
	 * I/O (the rear panel and the front mic) with Realtek ALC1220-VB.
	 * Here we provide two distinct names क्रम making UCM profiles easier.
	 */
	PROखाता_NAME(0x0414, 0xa000, "Gigabyte", "Aorus Master Front Headphone",
		     "Gigabyte-Aorus-Master-Front-Headphone"),
	PROखाता_NAME(0x0414, 0xa001, "Gigabyte", "Aorus Master Main Audio",
		     "Gigabyte-Aorus-Master-Main-Audio"),

	/* Gigabyte TRX40 Aorus Pro WiFi */
	PROखाता_NAME(0x0414, 0xa002,
		     "Realtek", "ALC1220-VB-DT", "Realtek-ALC1220-VB-Desktop"),

	/* Creative/E-Mu devices */
	DEVICE_NAME(0x041e, 0x3010, "Creative Labs", "Sound Blaster MP3+"),
	/* Creative/Toshiba Mulसमयdia Center SB-0500 */
	DEVICE_NAME(0x041e, 0x3048, "Toshiba", "SB-0500"),

	DEVICE_NAME(0x046d, 0x0990, "Logitech, Inc.", "QuickCam Pro 9000"),

	/* ASUS ROG Strix */
	PROखाता_NAME(0x0b05, 0x1917,
		     "Realtek", "ALC1220-VB-DT", "Realtek-ALC1220-VB-Desktop"),
	/* ASUS PRIME TRX40 PRO-S */
	PROखाता_NAME(0x0b05, 0x1918,
		     "Realtek", "ALC1220-VB-DT", "Realtek-ALC1220-VB-Desktop"),

	/* Dell WD15 Dock */
	PROखाता_NAME(0x0bda, 0x4014, "Dell", "WD15 Dock", "Dell-WD15-Dock"),
	/* Dell WD19 Dock */
	PROखाता_NAME(0x0bda, 0x402e, "Dell", "WD19 Dock", "Dell-WD15-Dock"),

	DEVICE_NAME(0x0ccd, 0x0028, "TerraTec", "Aureon5.1MkII"),

	/*
	 * The original product_name is "USB Sound Device", however this name
	 * is also used by the CM106 based cards, so make it unique.
	 */
	DEVICE_NAME(0x0d8c, 0x0102, शून्य, "ICUSBAUDIO7D"),
	DEVICE_NAME(0x0d8c, 0x0103, शून्य, "Audio Advantage MicroII"),

	/* MSI TRX40 Creator */
	PROखाता_NAME(0x0db0, 0x0d64,
		     "Realtek", "ALC1220-VB-DT", "Realtek-ALC1220-VB-Desktop"),
	/* MSI TRX40 */
	PROखाता_NAME(0x0db0, 0x543d,
		     "Realtek", "ALC1220-VB-DT", "Realtek-ALC1220-VB-Desktop"),

	/* Stanton/N2IT Final Scratch v1 device ('Scratchamp') */
	DEVICE_NAME(0x103d, 0x0100, "Stanton", "ScratchAmp"),
	DEVICE_NAME(0x103d, 0x0101, "Stanton", "ScratchAmp"),

	/* aka. Serato Scratch Live DJ Box */
	DEVICE_NAME(0x13e5, 0x0001, "Rane", "SL-1"),

	/* Lenovo ThinkStation P620 Rear Line-in, Line-out and Microphone */
	PROखाता_NAME(0x17aa, 0x1046, "Lenovo", "ThinkStation P620 Rear",
		     "Lenovo-ThinkStation-P620-Rear"),
	/* Lenovo ThinkStation P620 Internal Speaker + Front Headset */
	PROखाता_NAME(0x17aa, 0x104d, "Lenovo", "ThinkStation P620 Main",
		     "Lenovo-ThinkStation-P620-Main"),

	/* Asrock TRX40 Creator */
	PROखाता_NAME(0x26ce, 0x0a01,
		     "Realtek", "ALC1220-VB-DT", "Realtek-ALC1220-VB-Desktop"),

	अणु पूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा usb_audio_device_name *
lookup_device_name(u32 id)
अणु
	अटल स्थिर काष्ठा usb_audio_device_name *p;

	क्रम (p = usb_audio_names; p->id; p++)
		अगर (p->id == id)
			वापस p;
	वापस शून्य;
पूर्ण

/*
 * मुक्त the chip instance
 *
 * here we have to करो not much, since pcm and controls are alपढ़ोy मुक्तd
 *
 */

अटल व्योम snd_usb_audio_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_usb_audio *chip = card->निजी_data;

	snd_usb_endpoपूर्णांक_मुक्त_all(chip);

	mutex_destroy(&chip->mutex);
	अगर (!atomic_पढ़ो(&chip->shutकरोwn))
		dev_set_drvdata(&chip->dev->dev, शून्य);
पूर्ण

अटल व्योम usb_audio_make_लघुname(काष्ठा usb_device *dev,
				     काष्ठा snd_usb_audio *chip,
				     स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	काष्ठा snd_card *card = chip->card;
	स्थिर काष्ठा usb_audio_device_name *preset;
	स्थिर अक्षर *s = शून्य;

	preset = lookup_device_name(chip->usb_id);
	अगर (preset && preset->product_name)
		s = preset->product_name;
	अन्यथा अगर (quirk && quirk->product_name)
		s = quirk->product_name;
	अगर (s && *s) अणु
		strscpy(card->लघुname, s, माप(card->लघुname));
		वापस;
	पूर्ण

	/* retrieve the device string as लघुname */
	अगर (!dev->descriptor.iProduct ||
	    usb_string(dev, dev->descriptor.iProduct,
		       card->लघुname, माप(card->लघुname)) <= 0) अणु
		/* no name available from anywhere, so use ID */
		प्र_लिखो(card->लघुname, "USB Device %#04x:%#04x",
			USB_ID_VENDOR(chip->usb_id),
			USB_ID_PRODUCT(chip->usb_id));
	पूर्ण

	strim(card->लघुname);
पूर्ण

अटल व्योम usb_audio_make_दीर्घname(काष्ठा usb_device *dev,
				    काष्ठा snd_usb_audio *chip,
				    स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	काष्ठा snd_card *card = chip->card;
	स्थिर काष्ठा usb_audio_device_name *preset;
	स्थिर अक्षर *s = शून्य;
	पूर्णांक len;

	preset = lookup_device_name(chip->usb_id);

	/* लघुcut - अगर any pre-defined string is given, use it */
	अगर (preset && preset->profile_name)
		s = preset->profile_name;
	अगर (s && *s) अणु
		strscpy(card->दीर्घname, s, माप(card->दीर्घname));
		वापस;
	पूर्ण

	अगर (preset && preset->venकरोr_name)
		s = preset->venकरोr_name;
	अन्यथा अगर (quirk && quirk->venकरोr_name)
		s = quirk->venकरोr_name;
	*card->दीर्घname = 0;
	अगर (s && *s) अणु
		strscpy(card->दीर्घname, s, माप(card->दीर्घname));
	पूर्ण अन्यथा अणु
		/* retrieve the venकरोr and device strings as दीर्घname */
		अगर (dev->descriptor.iManufacturer)
			usb_string(dev, dev->descriptor.iManufacturer,
				   card->दीर्घname, माप(card->दीर्घname));
		/* we करोn't really care if there isn't any venकरोr string */
	पूर्ण
	अगर (*card->दीर्घname) अणु
		strim(card->दीर्घname);
		अगर (*card->दीर्घname)
			strlcat(card->दीर्घname, " ", माप(card->दीर्घname));
	पूर्ण

	strlcat(card->दीर्घname, card->लघुname, माप(card->दीर्घname));

	len = strlcat(card->दीर्घname, " at ", माप(card->दीर्घname));

	अगर (len < माप(card->दीर्घname))
		usb_make_path(dev, card->दीर्घname + len, माप(card->दीर्घname) - len);

	चयन (snd_usb_get_speed(dev)) अणु
	हाल USB_SPEED_LOW:
		strlcat(card->दीर्घname, ", low speed", माप(card->दीर्घname));
		अवरोध;
	हाल USB_SPEED_FULL:
		strlcat(card->दीर्घname, ", full speed", माप(card->दीर्घname));
		अवरोध;
	हाल USB_SPEED_HIGH:
		strlcat(card->दीर्घname, ", high speed", माप(card->दीर्घname));
		अवरोध;
	हाल USB_SPEED_SUPER:
		strlcat(card->दीर्घname, ", super speed", माप(card->दीर्घname));
		अवरोध;
	हाल USB_SPEED_SUPER_PLUS:
		strlcat(card->दीर्घname, ", super speed plus", माप(card->दीर्घname));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * create a chip instance and set its names.
 */
अटल पूर्णांक snd_usb_audio_create(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				काष्ठा usb_device *dev, पूर्णांक idx,
				स्थिर काष्ठा snd_usb_audio_quirk *quirk,
				अचिन्हित पूर्णांक usb_id,
				काष्ठा snd_usb_audio **rchip)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_usb_audio *chip;
	पूर्णांक err;
	अक्षर component[14];

	*rchip = शून्य;

	चयन (snd_usb_get_speed(dev)) अणु
	हाल USB_SPEED_LOW:
	हाल USB_SPEED_FULL:
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_WIRELESS:
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		अवरोध;
	शेष:
		dev_err(&dev->dev, "unknown device speed %d\n", snd_usb_get_speed(dev));
		वापस -ENXIO;
	पूर्ण

	err = snd_card_new(&पूर्णांकf->dev, index[idx], id[idx], THIS_MODULE,
			   माप(*chip), &card);
	अगर (err < 0) अणु
		dev_err(&dev->dev, "cannot create card instance %d\n", idx);
		वापस err;
	पूर्ण

	chip = card->निजी_data;
	mutex_init(&chip->mutex);
	init_रुकोqueue_head(&chip->shutकरोwn_रुको);
	chip->index = idx;
	chip->dev = dev;
	chip->card = card;
	chip->setup = device_setup[idx];
	chip->generic_implicit_fb = implicit_fb[idx];
	chip->स्वतःघड़ी = स्वतःघड़ी;
	atomic_set(&chip->active, 1); /* aव्योम स्वतःpm during probing */
	atomic_set(&chip->usage_count, 0);
	atomic_set(&chip->shutकरोwn, 0);

	chip->usb_id = usb_id;
	INIT_LIST_HEAD(&chip->pcm_list);
	INIT_LIST_HEAD(&chip->ep_list);
	INIT_LIST_HEAD(&chip->अगरace_ref_list);
	INIT_LIST_HEAD(&chip->midi_list);
	INIT_LIST_HEAD(&chip->mixer_list);

	card->निजी_मुक्त = snd_usb_audio_मुक्त;

	म_नकल(card->driver, "USB-Audio");
	प्र_लिखो(component, "USB%04x:%04x",
		USB_ID_VENDOR(chip->usb_id), USB_ID_PRODUCT(chip->usb_id));
	snd_component_add(card, component);

	usb_audio_make_लघुname(dev, chip, quirk);
	usb_audio_make_दीर्घname(dev, chip, quirk);

	snd_usb_audio_create_proc(chip);

	*rchip = chip;
	वापस 0;
पूर्ण

/* look क्रम a matching quirk alias id */
अटल bool get_alias_id(काष्ठा usb_device *dev, अचिन्हित पूर्णांक *id)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक src, dst;

	क्रम (i = 0; i < ARRAY_SIZE(quirk_alias); i++) अणु
		अगर (!quirk_alias[i] ||
		    माला_पूछो(quirk_alias[i], "%x:%x", &src, &dst) != 2 ||
		    src != *id)
			जारी;
		dev_info(&dev->dev,
			 "device (%04x:%04x): applying quirk alias %04x:%04x\n",
			 USB_ID_VENDOR(*id), USB_ID_PRODUCT(*id),
			 USB_ID_VENDOR(dst), USB_ID_PRODUCT(dst));
		*id = dst;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool check_delayed_रेजिस्टर_option(काष्ठा snd_usb_audio *chip, पूर्णांक अगरace)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक id, inum;

	क्रम (i = 0; i < ARRAY_SIZE(delayed_रेजिस्टर); i++) अणु
		अगर (delayed_रेजिस्टर[i] &&
		    माला_पूछो(delayed_रेजिस्टर[i], "%x:%x", &id, &inum) == 2 &&
		    id == chip->usb_id)
			वापस inum != अगरace;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा usb_device_id usb_audio_ids[]; /* defined below */

/* look क्रम the corresponding quirk */
अटल स्थिर काष्ठा snd_usb_audio_quirk *
get_alias_quirk(काष्ठा usb_device *dev, अचिन्हित पूर्णांक id)
अणु
	स्थिर काष्ठा usb_device_id *p;

	क्रम (p = usb_audio_ids; p->match_flags; p++) अणु
		/* FIXME: this checks only venकरोr:product pair in the list */
		अगर ((p->match_flags & USB_DEVICE_ID_MATCH_DEVICE) ==
		    USB_DEVICE_ID_MATCH_DEVICE &&
		    p->idVenकरोr == USB_ID_VENDOR(id) &&
		    p->idProduct == USB_ID_PRODUCT(id))
			वापस (स्थिर काष्ठा snd_usb_audio_quirk *)p->driver_info;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * probe the active usb device
 *
 * note that this can be called multiple बार per a device, when it
 * includes multiple audio control पूर्णांकerfaces.
 *
 * thus we check the usb device poपूर्णांकer and creates the card instance
 * only at the first समय.  the successive calls of this function will
 * append the pcm पूर्णांकerface to the corresponding card.
 */
अटल पूर्णांक usb_audio_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *usb_id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	स्थिर काष्ठा snd_usb_audio_quirk *quirk =
		(स्थिर काष्ठा snd_usb_audio_quirk *)usb_id->driver_info;
	काष्ठा snd_usb_audio *chip;
	पूर्णांक i, err;
	काष्ठा usb_host_पूर्णांकerface *alts;
	पूर्णांक अगरnum;
	u32 id;

	alts = &पूर्णांकf->altsetting[0];
	अगरnum = get_अगरace_desc(alts)->bInterfaceNumber;
	id = USB_ID(le16_to_cpu(dev->descriptor.idVenकरोr),
		    le16_to_cpu(dev->descriptor.idProduct));
	अगर (get_alias_id(dev, &id))
		quirk = get_alias_quirk(dev, id);
	अगर (quirk && quirk->अगरnum >= 0 && अगरnum != quirk->अगरnum)
		वापस -ENXIO;
	अगर (quirk && quirk->अगरnum == QUIRK_NODEV_INTERFACE)
		वापस -ENODEV;

	err = snd_usb_apply_boot_quirk(dev, पूर्णांकf, quirk, id);
	अगर (err < 0)
		वापस err;

	/*
	 * found a config.  now रेजिस्टर to ALSA
	 */

	/* check whether it's alपढ़ोy रेजिस्टरed */
	chip = शून्य;
	mutex_lock(&रेजिस्टर_mutex);
	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		अगर (usb_chip[i] && usb_chip[i]->dev == dev) अणु
			अगर (atomic_पढ़ो(&usb_chip[i]->shutकरोwn)) अणु
				dev_err(&dev->dev, "USB device is in the shutdown state, cannot create a card instance\n");
				err = -EIO;
				जाओ __error;
			पूर्ण
			chip = usb_chip[i];
			atomic_inc(&chip->active); /* aव्योम स्वतःpm */
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (! chip) अणु
		err = snd_usb_apply_boot_quirk_once(dev, पूर्णांकf, quirk, id);
		अगर (err < 0)
			जाओ __error;

		/* it's a fresh one.
		 * now look क्रम an empty slot and create a new card instance
		 */
		क्रम (i = 0; i < SNDRV_CARDS; i++)
			अगर (!usb_chip[i] &&
			    (vid[i] == -1 || vid[i] == USB_ID_VENDOR(id)) &&
			    (pid[i] == -1 || pid[i] == USB_ID_PRODUCT(id))) अणु
				अगर (enable[i]) अणु
					err = snd_usb_audio_create(पूर्णांकf, dev, i, quirk,
								   id, &chip);
					अगर (err < 0)
						जाओ __error;
					अवरोध;
				पूर्ण अन्यथा अगर (vid[i] != -1 || pid[i] != -1) अणु
					dev_info(&dev->dev,
						 "device (%04x:%04x) is disabled\n",
						 USB_ID_VENDOR(id),
						 USB_ID_PRODUCT(id));
					err = -ENOENT;
					जाओ __error;
				पूर्ण
			पूर्ण
		अगर (!chip) अणु
			dev_err(&dev->dev, "no available usb audio device\n");
			err = -ENODEV;
			जाओ __error;
		पूर्ण
	पूर्ण

	अगर (chip->num_पूर्णांकerfaces >= MAX_CARD_INTERFACES) अणु
		dev_info(&dev->dev, "Too many interfaces assigned to the single USB-audio card\n");
		err = -EINVAL;
		जाओ __error;
	पूर्ण

	dev_set_drvdata(&dev->dev, chip);

	/*
	 * For devices with more than one control पूर्णांकerface, we assume the
	 * first contains the audio controls. We might need a more specअगरic
	 * check here in the future.
	 */
	अगर (!chip->ctrl_पूर्णांकf)
		chip->ctrl_पूर्णांकf = alts;

	chip->txfr_quirk = 0;
	err = 1; /* जारी */
	अगर (quirk && quirk->अगरnum != QUIRK_NO_INTERFACE) अणु
		/* need some special handlings */
		err = snd_usb_create_quirk(chip, पूर्णांकf, &usb_audio_driver, quirk);
		अगर (err < 0)
			जाओ __error;
	पूर्ण

	अगर (err > 0) अणु
		/* create normal USB audio पूर्णांकerfaces */
		err = snd_usb_create_streams(chip, अगरnum);
		अगर (err < 0)
			जाओ __error;
		err = snd_usb_create_mixer(chip, अगरnum, ignore_ctl_error);
		अगर (err < 0)
			जाओ __error;
	पूर्ण

	अगर (chip->need_delayed_रेजिस्टर) अणु
		dev_info(&dev->dev,
			 "Found post-registration device assignment: %08x:%02x\n",
			 chip->usb_id, अगरnum);
		chip->need_delayed_रेजिस्टर = false; /* clear again */
	पूर्ण

	/* we are allowed to call snd_card_रेजिस्टर() many बार, but first
	 * check to see अगर a device needs to skip it or करो anything special
	 */
	अगर (!snd_usb_registration_quirk(chip, अगरnum) &&
	    !check_delayed_रेजिस्टर_option(chip, अगरnum)) अणु
		err = snd_card_रेजिस्टर(chip->card);
		अगर (err < 0)
			जाओ __error;
	पूर्ण

	अगर (quirk && quirk->shares_media_device) अणु
		/* करोn't want to fail when snd_media_device_create() fails */
		snd_media_device_create(chip, पूर्णांकf);
	पूर्ण

	अगर (quirk)
		chip->quirk_type = quirk->type;

	usb_chip[chip->index] = chip;
	chip->पूर्णांकf[chip->num_पूर्णांकerfaces] = पूर्णांकf;
	chip->num_पूर्णांकerfaces++;
	usb_set_पूर्णांकfdata(पूर्णांकf, chip);
	atomic_dec(&chip->active);
	mutex_unlock(&रेजिस्टर_mutex);
	वापस 0;

 __error:
	अगर (chip) अणु
		/* chip->active is inside the chip->card object,
		 * decrement beक्रमe memory is possibly वापसed.
		 */
		atomic_dec(&chip->active);
		अगर (!chip->num_पूर्णांकerfaces)
			snd_card_मुक्त(chip->card);
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);
	वापस err;
पूर्ण

/*
 * we need to take care of counter, since disconnection can be called also
 * many बार as well as usb_audio_probe().
 */
अटल व्योम usb_audio_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा snd_usb_audio *chip = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा snd_card *card;
	काष्ठा list_head *p;

	अगर (chip == USB_AUDIO_IFACE_UNUSED)
		वापस;

	card = chip->card;

	mutex_lock(&रेजिस्टर_mutex);
	अगर (atomic_inc_वापस(&chip->shutकरोwn) == 1) अणु
		काष्ठा snd_usb_stream *as;
		काष्ठा snd_usb_endpoपूर्णांक *ep;
		काष्ठा usb_mixer_पूर्णांकerface *mixer;

		/* रुको until all pending tasks करोne;
		 * they are रक्षित by snd_usb_lock_shutकरोwn()
		 */
		रुको_event(chip->shutकरोwn_रुको,
			   !atomic_पढ़ो(&chip->usage_count));
		snd_card_disconnect(card);
		/* release the pcm resources */
		list_क्रम_each_entry(as, &chip->pcm_list, list) अणु
			snd_usb_stream_disconnect(as);
		पूर्ण
		/* release the endpoपूर्णांक resources */
		list_क्रम_each_entry(ep, &chip->ep_list, list) अणु
			snd_usb_endpoपूर्णांक_release(ep);
		पूर्ण
		/* release the midi resources */
		list_क्रम_each(p, &chip->midi_list) अणु
			snd_usbmidi_disconnect(p);
		पूर्ण
		/*
		 * Nice to check quirk && quirk->shares_media_device and
		 * then call the snd_media_device_delete(). Don't have
		 * access to the quirk here. snd_media_device_delete()
		 * accesses mixer_list
		 */
		snd_media_device_delete(chip);

		/* release mixer resources */
		list_क्रम_each_entry(mixer, &chip->mixer_list, list) अणु
			snd_usb_mixer_disconnect(mixer);
		पूर्ण
	पूर्ण

	अगर (chip->quirk_type & QUIRK_SETUP_DISABLE_AUTOSUSPEND)
		usb_enable_स्वतःsuspend(पूर्णांकerface_to_usbdev(पूर्णांकf));

	chip->num_पूर्णांकerfaces--;
	अगर (chip->num_पूर्णांकerfaces <= 0) अणु
		usb_chip[chip->index] = शून्य;
		mutex_unlock(&रेजिस्टर_mutex);
		snd_card_मुक्त_when_बंदd(card);
	पूर्ण अन्यथा अणु
		mutex_unlock(&रेजिस्टर_mutex);
	पूर्ण
पूर्ण

/* lock the shutकरोwn (disconnect) task and स्वतःresume */
पूर्णांक snd_usb_lock_shutकरोwn(काष्ठा snd_usb_audio *chip)
अणु
	पूर्णांक err;

	atomic_inc(&chip->usage_count);
	अगर (atomic_पढ़ो(&chip->shutकरोwn)) अणु
		err = -EIO;
		जाओ error;
	पूर्ण
	err = snd_usb_स्वतःresume(chip);
	अगर (err < 0)
		जाओ error;
	वापस 0;

 error:
	अगर (atomic_dec_and_test(&chip->usage_count))
		wake_up(&chip->shutकरोwn_रुको);
	वापस err;
पूर्ण

/* स्वतःsuspend and unlock the shutकरोwn */
व्योम snd_usb_unlock_shutकरोwn(काष्ठा snd_usb_audio *chip)
अणु
	snd_usb_स्वतःsuspend(chip);
	अगर (atomic_dec_and_test(&chip->usage_count))
		wake_up(&chip->shutकरोwn_रुको);
पूर्ण

#अगर_घोषित CONFIG_PM

पूर्णांक snd_usb_स्वतःresume(काष्ठा snd_usb_audio *chip)
अणु
	पूर्णांक i, err;

	अगर (atomic_पढ़ो(&chip->shutकरोwn))
		वापस -EIO;
	अगर (atomic_inc_वापस(&chip->active) != 1)
		वापस 0;

	क्रम (i = 0; i < chip->num_पूर्णांकerfaces; i++) अणु
		err = usb_स्वतःpm_get_पूर्णांकerface(chip->पूर्णांकf[i]);
		अगर (err < 0) अणु
			/* rollback */
			जबतक (--i >= 0)
				usb_स्वतःpm_put_पूर्णांकerface(chip->पूर्णांकf[i]);
			atomic_dec(&chip->active);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम snd_usb_स्वतःsuspend(काष्ठा snd_usb_audio *chip)
अणु
	पूर्णांक i;

	अगर (atomic_पढ़ो(&chip->shutकरोwn))
		वापस;
	अगर (!atomic_dec_and_test(&chip->active))
		वापस;

	क्रम (i = 0; i < chip->num_पूर्णांकerfaces; i++)
		usb_स्वतःpm_put_पूर्णांकerface(chip->पूर्णांकf[i]);
पूर्ण

अटल पूर्णांक usb_audio_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा snd_usb_audio *chip = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा snd_usb_stream *as;
	काष्ठा snd_usb_endpoपूर्णांक *ep;
	काष्ठा usb_mixer_पूर्णांकerface *mixer;
	काष्ठा list_head *p;

	अगर (chip == USB_AUDIO_IFACE_UNUSED)
		वापस 0;

	अगर (!chip->num_suspended_पूर्णांकf++) अणु
		list_क्रम_each_entry(as, &chip->pcm_list, list)
			snd_usb_pcm_suspend(as);
		list_क्रम_each_entry(ep, &chip->ep_list, list)
			snd_usb_endpoपूर्णांक_suspend(ep);
		list_क्रम_each(p, &chip->midi_list)
			snd_usbmidi_suspend(p);
		list_क्रम_each_entry(mixer, &chip->mixer_list, list)
			snd_usb_mixer_suspend(mixer);
	पूर्ण

	अगर (!PMSG_IS_AUTO(message) && !chip->प्रणाली_suspend) अणु
		snd_घातer_change_state(chip->card, SNDRV_CTL_POWER_D3hot);
		chip->प्रणाली_suspend = chip->num_suspended_पूर्णांकf;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __usb_audio_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf, bool reset_resume)
अणु
	काष्ठा snd_usb_audio *chip = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा snd_usb_stream *as;
	काष्ठा usb_mixer_पूर्णांकerface *mixer;
	काष्ठा list_head *p;
	पूर्णांक err = 0;

	अगर (chip == USB_AUDIO_IFACE_UNUSED)
		वापस 0;

	atomic_inc(&chip->active); /* aव्योम स्वतःpm */
	अगर (chip->num_suspended_पूर्णांकf > 1)
		जाओ out;

	list_क्रम_each_entry(as, &chip->pcm_list, list) अणु
		err = snd_usb_pcm_resume(as);
		अगर (err < 0)
			जाओ err_out;
	पूर्ण

	/*
	 * ALSA leaves material resumption to user space
	 * we just notअगरy and restart the mixers
	 */
	list_क्रम_each_entry(mixer, &chip->mixer_list, list) अणु
		err = snd_usb_mixer_resume(mixer, reset_resume);
		अगर (err < 0)
			जाओ err_out;
	पूर्ण

	list_क्रम_each(p, &chip->midi_list) अणु
		snd_usbmidi_resume(p);
	पूर्ण

 out:
	अगर (chip->num_suspended_पूर्णांकf == chip->प्रणाली_suspend) अणु
		snd_घातer_change_state(chip->card, SNDRV_CTL_POWER_D0);
		chip->प्रणाली_suspend = 0;
	पूर्ण
	chip->num_suspended_पूर्णांकf--;

err_out:
	atomic_dec(&chip->active); /* allow स्वतःpm after this poपूर्णांक */
	वापस err;
पूर्ण

अटल पूर्णांक usb_audio_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस __usb_audio_resume(पूर्णांकf, false);
पूर्ण

अटल पूर्णांक usb_audio_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस __usb_audio_resume(पूर्णांकf, true);
पूर्ण
#अन्यथा
#घोषणा usb_audio_suspend	शून्य
#घोषणा usb_audio_resume	शून्य
#घोषणा usb_audio_reset_resume	शून्य
#पूर्ण_अगर		/* CONFIG_PM */

अटल स्थिर काष्ठा usb_device_id usb_audio_ids [] = अणु
#समावेश "quirks-table.h"
    अणु .match_flags = (USB_DEVICE_ID_MATCH_INT_CLASS | USB_DEVICE_ID_MATCH_INT_SUBCLASS),
      .bInterfaceClass = USB_CLASS_AUDIO,
      .bInterfaceSubClass = USB_SUBCLASS_AUDIOCONTROL पूर्ण,
    अणु पूर्ण						/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, usb_audio_ids);

/*
 * entry poपूर्णांक क्रम linux usb पूर्णांकerface
 */

अटल काष्ठा usb_driver usb_audio_driver = अणु
	.name =		"snd-usb-audio",
	.probe =	usb_audio_probe,
	.disconnect =	usb_audio_disconnect,
	.suspend =	usb_audio_suspend,
	.resume =	usb_audio_resume,
	.reset_resume =	usb_audio_reset_resume,
	.id_table =	usb_audio_ids,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(usb_audio_driver);
