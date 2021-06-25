<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ALSA USB Audio Driver
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>,
 *                       Clemens Ladisch <clemens@ladisch.de>
 */

/*
 * The contents of this file are part of the driver's id_table.
 *
 * In a perfect world, this file would be empty.
 */

/*
 * Use this क्रम devices where other पूर्णांकerfaces are standard compliant,
 * to prevent the quirk being applied to those पूर्णांकerfaces. (To work with
 * hotplugging, bDeviceClass must be set to USB_CLASS_PER_INTERFACE.)
 */
#घोषणा USB_DEVICE_VENDOR_SPEC(vend, prod) \
	.match_flags = USB_DEVICE_ID_MATCH_VENDOR | \
		       USB_DEVICE_ID_MATCH_PRODUCT | \
		       USB_DEVICE_ID_MATCH_INT_CLASS, \
	.idVenकरोr = vend, \
	.idProduct = prod, \
	.bInterfaceClass = USB_CLASS_VENDOR_SPEC

/* A standard entry matching with vid/pid and the audio class/subclass */
#घोषणा USB_AUDIO_DEVICE(vend, prod) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_INT_CLASS | \
		       USB_DEVICE_ID_MATCH_INT_SUBCLASS, \
	.idVenकरोr = vend, \
	.idProduct = prod, \
	.bInterfaceClass = USB_CLASS_AUDIO, \
	.bInterfaceSubClass = USB_SUBCLASS_AUDIOCONTROL

/* FTDI devices */
अणु
	USB_DEVICE(0x0403, 0xb8d8),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "STARR LABS", */
		/* .product_name = "Starr Labs MIDI USB device", */
		.अगरnum = 0,
		.type = QUIRK_MIDI_FTDI
	पूर्ण
पूर्ण,

अणु
	/* Creative BT-D1 */
	USB_DEVICE(0x041e, 0x0005),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = 1,
		.type = QUIRK_AUDIO_FIXED_ENDPOINT,
		.data = &(स्थिर काष्ठा audioक्रमmat) अणु
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
			.channels = 2,
			.अगरace = 1,
			.altsetting = 1,
			.altset_idx = 1,
			.endpoपूर्णांक = 0x03,
			.ep_attr = USB_ENDPOINT_XFER_ISOC,
			.attributes = 0,
			.rates = SNDRV_PCM_RATE_CONTINUOUS,
			.rate_min = 48000,
			.rate_max = 48000,
		पूर्ण
	पूर्ण
पूर्ण,

/* E-Mu 0202 USB */
अणु USB_DEVICE_VENDOR_SPEC(0x041e, 0x3f02) पूर्ण,
/* E-Mu 0404 USB */
अणु USB_DEVICE_VENDOR_SPEC(0x041e, 0x3f04) पूर्ण,
/* E-Mu Tracker Pre */
अणु USB_DEVICE_VENDOR_SPEC(0x041e, 0x3f0a) पूर्ण,
/* E-Mu 0204 USB */
अणु USB_DEVICE_VENDOR_SPEC(0x041e, 0x3f19) पूर्ण,

/*
 * HP Wireless Audio
 * When not ignored, causes instability issues क्रम some users, क्रमcing them to
 * skip the entire module.
 */
अणु
	USB_DEVICE(0x0424, 0xb832),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Standard Microsystems Corp.",
		.product_name = "HP Wireless Audio",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			/* Mixer */
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE,
			पूर्ण,
			/* Playback */
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE,
			पूर्ण,
			/* Capture */
			अणु
				.अगरnum = 2,
				.type = QUIRK_IGNORE_INTERFACE,
			पूर्ण,
			/* HID Device, .अगरnum = 3 */
			अणु
				.अगरnum = -1,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/*
 * Logitech QuickCam: bDeviceClass is venकरोr-specअगरic, so generic पूर्णांकerface
 * class matches करो not take effect without an explicit ID match.
 */
अणु USB_AUDIO_DEVICE(0x046d, 0x0850) पूर्ण,
अणु USB_AUDIO_DEVICE(0x046d, 0x08ae) पूर्ण,
अणु USB_AUDIO_DEVICE(0x046d, 0x08c6) पूर्ण,
अणु USB_AUDIO_DEVICE(0x046d, 0x08f0) पूर्ण,
अणु USB_AUDIO_DEVICE(0x046d, 0x08f5) पूर्ण,
अणु USB_AUDIO_DEVICE(0x046d, 0x08f6) पूर्ण,
अणु USB_AUDIO_DEVICE(0x046d, 0x0990) पूर्ण,

/*
 * Yamaha devices
 */

#घोषणा YAMAHA_DEVICE(id, name) अणु \
	USB_DEVICE(0x0499, id), \
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु \
		.venकरोr_name = "Yamaha", \
		.product_name = name, \
		.अगरnum = QUIRK_ANY_INTERFACE, \
		.type = QUIRK_MIDI_YAMAHA \
	पूर्ण \
पूर्ण
#घोषणा YAMAHA_INTERFACE(id, पूर्णांकf, name) अणु \
	USB_DEVICE_VENDOR_SPEC(0x0499, id), \
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु \
		.venकरोr_name = "Yamaha", \
		.product_name = name, \
		.अगरnum = पूर्णांकf, \
		.type = QUIRK_MIDI_YAMAHA \
	पूर्ण \
पूर्ण
YAMAHA_DEVICE(0x1000, "UX256"),
YAMAHA_DEVICE(0x1001, "MU1000"),
YAMAHA_DEVICE(0x1002, "MU2000"),
YAMAHA_DEVICE(0x1003, "MU500"),
YAMAHA_INTERFACE(0x1004, 3, "UW500"),
YAMAHA_DEVICE(0x1005, "MOTIF6"),
YAMAHA_DEVICE(0x1006, "MOTIF7"),
YAMAHA_DEVICE(0x1007, "MOTIF8"),
YAMAHA_DEVICE(0x1008, "UX96"),
YAMAHA_DEVICE(0x1009, "UX16"),
YAMAHA_INTERFACE(0x100a, 3, "EOS BX"),
YAMAHA_DEVICE(0x100c, "UC-MX"),
YAMAHA_DEVICE(0x100d, "UC-KX"),
YAMAHA_DEVICE(0x100e, "S08"),
YAMAHA_DEVICE(0x100f, "CLP-150"),
YAMAHA_DEVICE(0x1010, "CLP-170"),
YAMAHA_DEVICE(0x1011, "P-250"),
YAMAHA_DEVICE(0x1012, "TYROS"),
YAMAHA_DEVICE(0x1013, "PF-500"),
YAMAHA_DEVICE(0x1014, "S90"),
YAMAHA_DEVICE(0x1015, "MOTIF-R"),
YAMAHA_DEVICE(0x1016, "MDP-5"),
YAMAHA_DEVICE(0x1017, "CVP-204"),
YAMAHA_DEVICE(0x1018, "CVP-206"),
YAMAHA_DEVICE(0x1019, "CVP-208"),
YAMAHA_DEVICE(0x101a, "CVP-210"),
YAMAHA_DEVICE(0x101b, "PSR-1100"),
YAMAHA_DEVICE(0x101c, "PSR-2100"),
YAMAHA_DEVICE(0x101d, "CLP-175"),
YAMAHA_DEVICE(0x101e, "PSR-K1"),
YAMAHA_DEVICE(0x101f, "EZ-J24"),
YAMAHA_DEVICE(0x1020, "EZ-250i"),
YAMAHA_DEVICE(0x1021, "MOTIF ES 6"),
YAMAHA_DEVICE(0x1022, "MOTIF ES 7"),
YAMAHA_DEVICE(0x1023, "MOTIF ES 8"),
YAMAHA_DEVICE(0x1024, "CVP-301"),
YAMAHA_DEVICE(0x1025, "CVP-303"),
YAMAHA_DEVICE(0x1026, "CVP-305"),
YAMAHA_DEVICE(0x1027, "CVP-307"),
YAMAHA_DEVICE(0x1028, "CVP-309"),
YAMAHA_DEVICE(0x1029, "CVP-309GP"),
YAMAHA_DEVICE(0x102a, "PSR-1500"),
YAMAHA_DEVICE(0x102b, "PSR-3000"),
YAMAHA_DEVICE(0x102e, "ELS-01/01C"),
YAMAHA_DEVICE(0x1030, "PSR-295/293"),
YAMAHA_DEVICE(0x1031, "DGX-205/203"),
YAMAHA_DEVICE(0x1032, "DGX-305"),
YAMAHA_DEVICE(0x1033, "DGX-505"),
YAMAHA_DEVICE(0x1034, शून्य),
YAMAHA_DEVICE(0x1035, शून्य),
YAMAHA_DEVICE(0x1036, शून्य),
YAMAHA_DEVICE(0x1037, शून्य),
YAMAHA_DEVICE(0x1038, शून्य),
YAMAHA_DEVICE(0x1039, शून्य),
YAMAHA_DEVICE(0x103a, शून्य),
YAMAHA_DEVICE(0x103b, शून्य),
YAMAHA_DEVICE(0x103c, शून्य),
YAMAHA_DEVICE(0x103d, शून्य),
YAMAHA_DEVICE(0x103e, शून्य),
YAMAHA_DEVICE(0x103f, शून्य),
YAMAHA_DEVICE(0x1040, शून्य),
YAMAHA_DEVICE(0x1041, शून्य),
YAMAHA_DEVICE(0x1042, शून्य),
YAMAHA_DEVICE(0x1043, शून्य),
YAMAHA_DEVICE(0x1044, शून्य),
YAMAHA_DEVICE(0x1045, शून्य),
YAMAHA_INTERFACE(0x104e, 0, शून्य),
YAMAHA_DEVICE(0x104f, शून्य),
YAMAHA_DEVICE(0x1050, शून्य),
YAMAHA_DEVICE(0x1051, शून्य),
YAMAHA_DEVICE(0x1052, शून्य),
YAMAHA_INTERFACE(0x1053, 0, शून्य),
YAMAHA_INTERFACE(0x1054, 0, शून्य),
YAMAHA_DEVICE(0x1055, शून्य),
YAMAHA_DEVICE(0x1056, शून्य),
YAMAHA_DEVICE(0x1057, शून्य),
YAMAHA_DEVICE(0x1058, शून्य),
YAMAHA_DEVICE(0x1059, शून्य),
YAMAHA_DEVICE(0x105a, शून्य),
YAMAHA_DEVICE(0x105b, शून्य),
YAMAHA_DEVICE(0x105c, शून्य),
YAMAHA_DEVICE(0x105d, शून्य),
अणु
	USB_DEVICE(0x0499, 0x1503),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "Yamaha", */
		/* .product_name = "MOX6/MOX8", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_YAMAHA
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0499, 0x1507),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "Yamaha", */
		/* .product_name = "THR10", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_YAMAHA
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0499, 0x1509),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "Yamaha", */
		/* .product_name = "Steinberg UR22", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_YAMAHA
			पूर्ण,
			अणु
				.अगरnum = 4,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0499, 0x150a),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "Yamaha", */
		/* .product_name = "THR5A", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_YAMAHA
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0499, 0x150c),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "Yamaha", */
		/* .product_name = "THR10C", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_YAMAHA
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
YAMAHA_DEVICE(0x2000, "DGP-7"),
YAMAHA_DEVICE(0x2001, "DGP-5"),
YAMAHA_DEVICE(0x2002, शून्य),
YAMAHA_DEVICE(0x2003, शून्य),
YAMAHA_DEVICE(0x5000, "CS1D"),
YAMAHA_DEVICE(0x5001, "DSP1D"),
YAMAHA_DEVICE(0x5002, "DME32"),
YAMAHA_DEVICE(0x5003, "DM2000"),
YAMAHA_DEVICE(0x5004, "02R96"),
YAMAHA_DEVICE(0x5005, "ACU16-C"),
YAMAHA_DEVICE(0x5006, "NHB32-C"),
YAMAHA_DEVICE(0x5007, "DM1000"),
YAMAHA_DEVICE(0x5008, "01V96"),
YAMAHA_DEVICE(0x5009, "SPX2000"),
YAMAHA_DEVICE(0x500a, "PM5D"),
YAMAHA_DEVICE(0x500b, "DME64N"),
YAMAHA_DEVICE(0x500c, "DME24N"),
YAMAHA_DEVICE(0x500d, शून्य),
YAMAHA_DEVICE(0x500e, शून्य),
YAMAHA_DEVICE(0x500f, शून्य),
YAMAHA_DEVICE(0x7000, "DTX"),
YAMAHA_DEVICE(0x7010, "UB99"),
#अघोषित YAMAHA_DEVICE
#अघोषित YAMAHA_INTERFACE
/* this catches most recent venकरोr-specअगरic Yamaha devices */
अणु
	.match_flags = USB_DEVICE_ID_MATCH_VENDOR |
	               USB_DEVICE_ID_MATCH_INT_CLASS,
	.idVenकरोr = 0x0499,
	.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_AUTODETECT
	पूर्ण
पूर्ण,

/*
 * Roland/RolandED/Edirol/BOSS devices
 */
अणु
	USB_DEVICE(0x0582, 0x0000),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "UA-100",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
					.channels = 4,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = 0,
					.endpoपूर्णांक = 0x01,
					.ep_attr = 0x09,
					.rates = SNDRV_PCM_RATE_CONTINUOUS,
					.rate_min = 44100,
					.rate_max = 44100,
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
					.channels = 2,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_FILL_MAX,
					.endpoपूर्णांक = 0x81,
					.ep_attr = 0x05,
					.rates = SNDRV_PCM_RATE_CONTINUOUS,
					.rate_min = 44100,
					.rate_max = 44100,
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0007,
					.in_cables  = 0x0007
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x0002),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UM-4",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x000f,
					.in_cables  = 0x000f
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x0003),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "SC-8850",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x003f,
					.in_cables  = 0x003f
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x0004),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "U-8",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0005,
					.in_cables  = 0x0005
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* Has ID 0x0099 when not in "Advanced Driver" mode.
	 * The UM-2EX has only one input, but we cannot detect this. */
	USB_DEVICE(0x0582, 0x0005),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UM-2",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0003,
					.in_cables  = 0x0003
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x0007),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "SC-8820",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0013,
					.in_cables  = 0x0013
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x0008),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "PC-300",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x009d when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0009),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UM-1",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x000b),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "SK-500",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0013,
					.in_cables  = 0x0013
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* thanks to Emiliano Grilli <emillo@libero.it>
	 * क्रम helping researching this data */
	USB_DEVICE(0x0582, 0x000c),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "SC-D70",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0007,
					.in_cables  = 0x0007
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु	/*
	 * This quirk is क्रम the "Advanced Driver" mode of the Edirol UA-5.
	 * If the advanced mode चयन at the back of the unit is off, the
	 * UA-5 has ID 0x0582/0x0011 and is standard compliant (no quirks),
	 * but offers only 16-bit PCM.
	 * In advanced mode, the UA-5 will output S24_3LE samples (two
	 * channels) at the rate indicated on the front चयन, including
	 * the 96kHz sample rate.
	 */
	USB_DEVICE(0x0582, 0x0010),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UA-5",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0013 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0012),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "XV-5050",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0015 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0014),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UM-880",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x01ff,
			.in_cables  = 0x01ff
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0017 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0016),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "SD-90",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x000f,
					.in_cables  = 0x000f
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x001c when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x001b),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "MMP-2",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x001e when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x001d),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "V-SYNTH",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0024 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0023),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UM-550",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x003f,
			.in_cables  = 0x003f
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * This quirk is क्रम the "Advanced Driver" mode. If off, the UA-20
	 * has ID 0x0026 and is standard compliant, but has only 16-bit PCM
	 * and no MIDI.
	 */
	USB_DEVICE(0x0582, 0x0025),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UA-20",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 2,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = 0,
					.endpoपूर्णांक = 0x01,
					.ep_attr = 0x01,
					.rates = SNDRV_PCM_RATE_CONTINUOUS,
					.rate_min = 44100,
					.rate_max = 44100,
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 2,
					.अगरace = 2,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = 0,
					.endpoपूर्णांक = 0x82,
					.ep_attr = 0x01,
					.rates = SNDRV_PCM_RATE_CONTINUOUS,
					.rate_min = 44100,
					.rate_max = 44100,
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0028 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0027),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "SD-20",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0003,
			.in_cables  = 0x0007
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x002a when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0029),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "SD-80",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x000f,
			.in_cables  = 0x000f
		पूर्ण
	पूर्ण
पूर्ण,
अणु	/*
	 * This quirk is क्रम the "Advanced" modes of the Edirol UA-700.
	 * If the sample क्रमmat चयन is not in an advanced setting, the
	 * UA-700 has ID 0x0582/0x002c and is standard compliant (no quirks),
	 * but offers only 16-bit PCM and no MIDI.
	 */
	USB_DEVICE_VENDOR_SPEC(0x0582, 0x002b),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UA-700",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x002e when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x002d),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "XV-2020",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0030 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x002f),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "VariOS",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0007,
			.in_cables  = 0x0007
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0034 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0033),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "PCR",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0003,
			.in_cables  = 0x0007
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * Has ID 0x0038 when not in "Advanced Driver" mode;
	 * later revisions use IDs 0x0054 and 0x00a2.
	 */
	USB_DEVICE(0x0582, 0x0037),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "Digital Piano",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * This quirk is क्रम the "Advanced Driver" mode.  If off, the GS-10
	 * has ID 0x003c and is standard compliant, but has only 16-bit PCM
	 * and no MIDI.
	 */
	USB_DEVICE_VENDOR_SPEC(0x0582, 0x003b),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "BOSS",
		.product_name = "GS-10",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = & (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0041 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0040),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "GI-20",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0043 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0042),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "RS-70",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0049 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0047),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "EDIROL", */
		/* .product_name = "UR-80", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			/* in the 96 kHz modes, only पूर्णांकerface 1 is there */
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x004a when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0048),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "EDIROL", */
		/* .product_name = "UR-80", */
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0003,
			.in_cables  = 0x0007
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x004e when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x004c),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "PCR-A",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x004f when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x004d),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "PCR-A",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0003,
			.in_cables  = 0x0007
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * This quirk is क्रम the "Advanced Driver" mode. If off, the UA-3FX
	 * is standard compliant, but has only 16-bit PCM.
	 */
	USB_DEVICE(0x0582, 0x0050),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UA-3FX",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x0052),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UM-1SX",
		.अगरnum = 0,
		.type = QUIRK_MIDI_STANDARD_INTERFACE
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x0060),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "EXR Series",
		.अगरnum = 0,
		.type = QUIRK_MIDI_STANDARD_INTERFACE
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0066 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0064),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "EDIROL", */
		/* .product_name = "PCR-1", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0067 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0065),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "EDIROL", */
		/* .product_name = "PCR-1", */
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0003
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x006e when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x006d),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "FANTOM-X",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु	/*
	 * This quirk is क्रम the "Advanced" modes of the Edirol UA-25.
	 * If the चयन is not in an advanced setting, the UA-25 has
	 * ID 0x0582/0x0073 and is standard compliant (no quirks), but
	 * offers only 16-bit PCM at 44.1 kHz and no MIDI.
	 */
	USB_DEVICE_VENDOR_SPEC(0x0582, 0x0074),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UA-25",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0076 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0075),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "BOSS",
		.product_name = "DR-880",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x007b when not in "Advanced Driver" mode */
	USB_DEVICE_VENDOR_SPEC(0x0582, 0x007a),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		/* "RD" or "RD-700SX"? */
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0003,
			.in_cables  = 0x0003
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x0081 when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x0080),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Roland",
		.product_name = "G-70",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* has ID 0x008c when not in "Advanced Driver" mode */
	USB_DEVICE(0x0582, 0x008b),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "PC-50",
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * This quirk is क्रम the "Advanced Driver" mode. If off, the UA-4FX
	 * is standard compliant, but has only 16-bit PCM and no MIDI.
	 */
	USB_DEVICE(0x0582, 0x00a3),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UA-4FX",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* Edirol M-16DX */
	USB_DEVICE(0x0582, 0x00c4),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* Advanced modes of the Edirol UA-25EX.
	 * For the standard mode, UA-25EX has ID 0582:00e7, which
	 * offers only 16-bit PCM at 44.1 kHz and no MIDI.
	 */
	USB_DEVICE_VENDOR_SPEC(0x0582, 0x00e6),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "EDIROL",
		.product_name = "UA-25EX",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_EसूचीOL_UAXX
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* Edirol UM-3G */
	USB_DEVICE_VENDOR_SPEC(0x0582, 0x0108),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = 0,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0007,
			.in_cables  = 0x0007
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* BOSS ME-25 */
	USB_DEVICE(0x0582, 0x0113),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* only 44.1 kHz works at the moment */
	USB_DEVICE(0x0582, 0x0120),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "Roland", */
		/* .product_name = "OCTO-CAPTURE", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
					.channels = 10,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x05,
					.ep_attr = 0x05,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
					.channels = 12,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x85,
					.ep_attr = 0x25,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 4,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* only 44.1 kHz works at the moment */
	USB_DEVICE(0x0582, 0x012f),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "Roland", */
		/* .product_name = "QUAD-CAPTURE", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
					.channels = 4,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x05,
					.ep_attr = 0x05,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
					.channels = 6,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x85,
					.ep_attr = 0x25,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 4,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x0159),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "Roland", */
		/* .product_name = "UA-22", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/* UA101 and co are supported by another driver */
अणु
	USB_DEVICE(0x0582, 0x0044), /* UA-1000 high speed */
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_NODEV_INTERFACE
	पूर्ण,
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x007d), /* UA-101 high speed */
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_NODEV_INTERFACE
	पूर्ण,
पूर्ण,
अणु
	USB_DEVICE(0x0582, 0x008d), /* UA-101 full speed */
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_NODEV_INTERFACE
	पूर्ण,
पूर्ण,

/* this catches most recent venकरोr-specअगरic Roland devices */
अणु
	.match_flags = USB_DEVICE_ID_MATCH_VENDOR |
	               USB_DEVICE_ID_MATCH_INT_CLASS,
	.idVenकरोr = 0x0582,
	.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_AUTODETECT
	पूर्ण
पूर्ण,

/* Guillemot devices */
अणु
	/*
	 * This is क्रम the "Windows Edition" where the बाह्यal MIDI ports are
	 * the only MIDI ports; the control data is reported through HID
	 * पूर्णांकerfaces.  The "Macintosh Edition" has ID 0xd002 and uses standard
	 * compliant USB MIDI ports क्रम बाह्यal MIDI and controls.
	 */
	USB_DEVICE_VENDOR_SPEC(0x06f8, 0xb000),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Hercules",
		.product_name = "DJ Console (WE)",
		.अगरnum = 4,
		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,

/* Midiman/M-Audio devices */
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x1002),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "MidiSport 2x2",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_MIDI_MIDIMAN,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0003,
			.in_cables  = 0x0003
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x1011),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "MidiSport 1x1",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_MIDI_MIDIMAN,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x1015),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "Keystation",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_MIDI_MIDIMAN,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x1021),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "MidiSport 4x4",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_MIDI_MIDIMAN,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x000f,
			.in_cables  = 0x000f
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * For hardware revision 1.05; in the later revisions (1.10 and
	 * 1.21), 0x1031 is the ID क्रम the device without firmware.
	 * Thanks to Olaf Giesbrecht <Olaf_Giesbrecht@yahoo.de>
	 */
	USB_DEVICE_VER(0x0763, 0x1031, 0x0100, 0x0109),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "MidiSport 8x8",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_MIDI_MIDIMAN,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x01ff,
			.in_cables  = 0x01ff
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x1033),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "MidiSport 8x8",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_MIDI_MIDIMAN,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x01ff,
			.in_cables  = 0x01ff
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x1041),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "MidiSport 2x4",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_MIDI_MIDIMAN,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x000f,
			.in_cables  = 0x0003
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x2001),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "Quattro",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = & (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			/*
			 * Interfaces 0-2 are "Windows-compatible", 16-bit only,
			 * and share endpoपूर्णांकs with the other पूर्णांकerfaces.
			 * Ignore them.  The other पूर्णांकerfaces can करो 24 bits,
			 * but captured samples are big-endian (see usbaudio.c).
			 */
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 4,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 5,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 6,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 7,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 8,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 9,
				.type = QUIRK_MIDI_MIDIMAN,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x2003),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "AudioPhile",
		.अगरnum = 6,
		.type = QUIRK_MIDI_MIDIMAN,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x2008),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "Ozone",
		.अगरnum = 3,
		.type = QUIRK_MIDI_MIDIMAN,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x200d),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "M-Audio",
		.product_name = "OmniStudio",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = & (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 4,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 5,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 6,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 7,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 8,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 9,
				.type = QUIRK_MIDI_MIDIMAN,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0763, 0x2019),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "M-Audio", */
		/* .product_name = "Ozone Academic", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = & (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_MIDIMAN,
				.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x2030),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "M-Audio", */
		/* .product_name = "Fast Track C400", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = &(स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			/* Playback */
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 6,
					.अगरace = 2,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x01,
					.ep_attr = 0x09,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000 |
						 SNDRV_PCM_RATE_88200 |
						 SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 4,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
							44100, 48000, 88200, 96000
					पूर्ण,
					.घड़ी = 0x80,
				पूर्ण
			पूर्ण,
			/* Capture */
			अणु
				.अगरnum = 3,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 4,
					.अगरace = 3,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x81,
					.ep_attr = 0x05,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000 |
						 SNDRV_PCM_RATE_88200 |
						 SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 4,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000, 88200, 96000
					पूर्ण,
					.घड़ी = 0x80,
				पूर्ण
			पूर्ण,
			/* MIDI */
			अणु
				.अगरnum = -1 /* Interface = 4 */
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x2031),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "M-Audio", */
		/* .product_name = "Fast Track C600", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = &(स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			/* Playback */
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8,
					.अगरace = 2,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x01,
					.ep_attr = 0x09,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000 |
						 SNDRV_PCM_RATE_88200 |
						 SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 4,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
							44100, 48000, 88200, 96000
					पूर्ण,
					.घड़ी = 0x80,
				पूर्ण
			पूर्ण,
			/* Capture */
			अणु
				.अगरnum = 3,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 6,
					.अगरace = 3,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x81,
					.ep_attr = 0x05,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000 |
						 SNDRV_PCM_RATE_88200 |
						 SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 4,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000, 88200, 96000
					पूर्ण,
					.घड़ी = 0x80,
				पूर्ण
			पूर्ण,
			/* MIDI */
			अणु
				.अगरnum = -1 /* Interface = 4 */
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x2080),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "M-Audio", */
		/* .product_name = "Fast Track Ultra", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = & (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x01,
					.ep_attr = 0x09,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000 |
						 SNDRV_PCM_RATE_88200 |
						 SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 4,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000, 88200, 96000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8,
					.अगरace = 2,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x81,
					.ep_attr = 0x05,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000 |
						 SNDRV_PCM_RATE_88200 |
						 SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 4,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000, 88200, 96000
					पूर्ण
				पूर्ण
			पूर्ण,
			/* पूर्णांकerface 3 (MIDI) is standard compliant */
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0763, 0x2081),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "M-Audio", */
		/* .product_name = "Fast Track Ultra 8R", */
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = & (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x01,
					.ep_attr = 0x09,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000 |
						 SNDRV_PCM_RATE_88200 |
						 SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 4,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
							44100, 48000, 88200, 96000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8,
					.अगरace = 2,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x81,
					.ep_attr = 0x05,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000 |
						 SNDRV_PCM_RATE_88200 |
						 SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 4,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000, 88200, 96000
					पूर्ण
				पूर्ण
			पूर्ण,
			/* पूर्णांकerface 3 (MIDI) is standard compliant */
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/* Casio devices */
अणु
	USB_DEVICE(0x07cf, 0x6801),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Casio",
		.product_name = "PL-40R",
		.अगरnum = 0,
		.type = QUIRK_MIDI_YAMAHA
	पूर्ण
पूर्ण,
अणु
	/* this ID is used by several devices without a product ID */
	USB_DEVICE(0x07cf, 0x6802),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Casio",
		.product_name = "Keyboard",
		.अगरnum = 0,
		.type = QUIRK_MIDI_YAMAHA
	पूर्ण
पूर्ण,

/* Mark of the Unicorn devices */
अणु
	/* thanks to Robert A. Lerche <ral 'at' msbit.com> */
	.match_flags = USB_DEVICE_ID_MATCH_VENDOR |
		       USB_DEVICE_ID_MATCH_PRODUCT |
		       USB_DEVICE_ID_MATCH_DEV_SUBCLASS,
	.idVenकरोr = 0x07fd,
	.idProduct = 0x0001,
	.bDeviceSubClass = 2,
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "MOTU",
		.product_name = "Fastlane",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = & (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_MIDI_RAW_BYTES
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/* Emagic devices */
अणु
	USB_DEVICE(0x086a, 0x0001),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Emagic",
		.product_name = "Unitor8",
		.अगरnum = 2,
		.type = QUIRK_MIDI_EMAGIC,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x80ff,
			.in_cables  = 0x80ff
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x086a, 0x0002),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Emagic",
		/* .product_name = "AMT8", */
		.अगरnum = 2,
		.type = QUIRK_MIDI_EMAGIC,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x80ff,
			.in_cables  = 0x80ff
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x086a, 0x0003),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Emagic",
		/* .product_name = "MT4", */
		.अगरnum = 2,
		.type = QUIRK_MIDI_EMAGIC,
		.data = & (स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
			.out_cables = 0x800f,
			.in_cables  = 0x8003
		पूर्ण
	पूर्ण
पूर्ण,

/* KORG devices */
अणु
	USB_DEVICE_VENDOR_SPEC(0x0944, 0x0200),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "KORG, Inc.",
		/* .product_name = "PANDORA PX5D", */
		.अगरnum = 3,
		.type = QUIRK_MIDI_STANDARD_INTERFACE,
	पूर्ण
पूर्ण,

अणु
	USB_DEVICE_VENDOR_SPEC(0x0944, 0x0201),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "KORG, Inc.",
		/* .product_name = "ToneLab ST", */
		.अगरnum = 3,
		.type = QUIRK_MIDI_STANDARD_INTERFACE,
	पूर्ण
पूर्ण,

अणु
	USB_DEVICE_VENDOR_SPEC(0x0944, 0x0204),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "KORG, Inc.",
		/* .product_name = "ToneLab EX", */
		.अगरnum = 3,
		.type = QUIRK_MIDI_STANDARD_INTERFACE,
	पूर्ण
पूर्ण,

/* AKAI devices */
अणु
	USB_DEVICE(0x09e8, 0x0062),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "AKAI",
		.product_name = "MPD16",
		.अगरnum = 0,
		.type = QUIRK_MIDI_AKAI,
	पूर्ण
पूर्ण,

अणु
	/* Akai MPC Element */
	USB_DEVICE(0x09e8, 0x0021),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = & (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_MIDI_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/* Steinberg devices */
अणु
	/* Steinberg MI2 */
	USB_DEVICE_VENDOR_SPEC(0x0a4e, 0x2040),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = & (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* Steinberg MI4 */
	USB_DEVICE_VENDOR_SPEC(0x0a4e, 0x4040),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = & (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/* TerraTec devices */
अणु
	USB_DEVICE_VENDOR_SPEC(0x0ccd, 0x0012),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "TerraTec",
		.product_name = "PHASE 26",
		.अगरnum = 3,
		.type = QUIRK_MIDI_STANDARD_INTERFACE
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0ccd, 0x0013),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "TerraTec",
		.product_name = "PHASE 26",
		.अगरnum = 3,
		.type = QUIRK_MIDI_STANDARD_INTERFACE
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x0ccd, 0x0014),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "TerraTec",
		.product_name = "PHASE 26",
		.अगरnum = 3,
		.type = QUIRK_MIDI_STANDARD_INTERFACE
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x0ccd, 0x0035),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Miditech",
		.product_name = "Play'n Roll",
		.अगरnum = 0,
		.type = QUIRK_MIDI_CME
	पूर्ण
पूर्ण,

/* Novation EMS devices */
अणु
	USB_DEVICE_VENDOR_SPEC(0x1235, 0x0001),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Novation",
		.product_name = "ReMOTE Audio/XStation",
		.अगरnum = 4,
		.type = QUIRK_MIDI_NOVATION
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x1235, 0x0002),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Novation",
		.product_name = "Speedio",
		.अगरnum = 3,
		.type = QUIRK_MIDI_NOVATION
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x1235, 0x000a),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "Novation", */
		/* .product_name = "Nocturn", */
		.अगरnum = 0,
		.type = QUIRK_MIDI_RAW_BYTES
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x1235, 0x000e),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		/* .venकरोr_name = "Novation", */
		/* .product_name = "Launchpad", */
		.अगरnum = 0,
		.type = QUIRK_MIDI_RAW_BYTES
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x1235, 0x0010),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Focusrite",
		.product_name = "Saffire 6 USB",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 4,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x01,
					.ep_attr = USB_ENDPOINT_XFER_ISOC,
					.dataपूर्णांकerval = 1,
					.maxpacksize = 0x024c,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000,
					.rate_min = 44100,
					.rate_max = 48000,
					.nr_rates = 2,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 2,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = 0,
					.endpoपूर्णांक = 0x82,
					.ep_attr = USB_ENDPOINT_XFER_ISOC,
					.dataपूर्णांकerval = 1,
					.maxpacksize = 0x0126,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000,
					.rate_min = 44100,
					.rate_max = 48000,
					.nr_rates = 2,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_MIDI_RAW_BYTES
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE(0x1235, 0x0018),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Novation",
		.product_name = "Twitch",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 4,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x01,
					.ep_attr = USB_ENDPOINT_XFER_ISOC,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000,
					.rate_min = 44100,
					.rate_max = 48000,
					.nr_rates = 2,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_MIDI_RAW_BYTES
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	USB_DEVICE_VENDOR_SPEC(0x1235, 0x4661),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Novation",
		.product_name = "ReMOTE25",
		.अगरnum = 0,
		.type = QUIRK_MIDI_NOVATION
	पूर्ण
पूर्ण,

/* Access Music devices */
अणु
	/* VirusTI Desktop */
	USB_DEVICE_VENDOR_SPEC(0x133e, 0x0815),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = &(स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 3,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_cables = 0x0003,
					.in_cables  = 0x0003
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 4,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/* Lenovo ThinkStation P620 Rear Line-in, Line-out and Microphone */
अणु
	USB_DEVICE(0x17aa, 0x1046),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_SETUP_DISABLE_AUTOSUSPEND
	पूर्ण
पूर्ण,
/* Lenovo ThinkStation P620 Internal Speaker + Front Headset */
अणु
	USB_DEVICE(0x17aa, 0x104d),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_SETUP_DISABLE_AUTOSUSPEND
	पूर्ण
पूर्ण,

/* Native Instruments MK2 series */
अणु
	/* Komplete Audio 6 */
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr = 0x17cc,
	.idProduct = 0x1000,
पूर्ण,
अणु
	/* Traktor Audio 6 */
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr = 0x17cc,
	.idProduct = 0x1010,
पूर्ण,
अणु
	/* Traktor Audio 10 */
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr = 0x17cc,
	.idProduct = 0x1020,
पूर्ण,

/* QinHeng devices */
अणु
	USB_DEVICE(0x1a86, 0x752d),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "QinHeng",
		.product_name = "CH345",
		.अगरnum = 1,
		.type = QUIRK_MIDI_CH345
	पूर्ण
पूर्ण,

/* KeithMcMillen Stringport */
अणु USB_DEVICE(0x1f38, 0x0001) पूर्ण, /* FIXME: should be more restrictive matching */

/* Miditech devices */
अणु
	USB_DEVICE(0x4752, 0x0011),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Miditech",
		.product_name = "Midistart-2",
		.अगरnum = 0,
		.type = QUIRK_MIDI_CME
	पूर्ण
पूर्ण,

/* Central Music devices */
अणु
	/* this ID used by both Miditech MidiStudio-2 and CME UF-x */
	USB_DEVICE(0x7104, 0x2202),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = 0,
		.type = QUIRK_MIDI_CME
	पूर्ण
पूर्ण,

/*
 * Auvitek au0828 devices with audio पूर्णांकerface.
 * This should be kept in sync with drivers/media/usb/au0828/au0828-cards.c
 * Please notice that some drivers are DVB only, and करोn't need to be
 * here. That's the हाल, क्रम example, of DVICO_FUSIONHDTV7.
 */

#घोषणा AU0828_DEVICE(vid, pid, vname, pname) अणु \
	USB_AUDIO_DEVICE(vid, pid), \
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु \
		.venकरोr_name = vname, \
		.product_name = pname, \
		.अगरnum = QUIRK_ANY_INTERFACE, \
		.type = QUIRK_AUDIO_ALIGN_TRANSFER, \
		.shares_media_device = 1, \
	पूर्ण \
पूर्ण

AU0828_DEVICE(0x2040, 0x7200, "Hauppauge", "HVR-950Q"),
AU0828_DEVICE(0x2040, 0x7240, "Hauppauge", "HVR-850"),
AU0828_DEVICE(0x2040, 0x7210, "Hauppauge", "HVR-950Q"),
AU0828_DEVICE(0x2040, 0x7217, "Hauppauge", "HVR-950Q"),
AU0828_DEVICE(0x2040, 0x721b, "Hauppauge", "HVR-950Q"),
AU0828_DEVICE(0x2040, 0x721e, "Hauppauge", "HVR-950Q"),
AU0828_DEVICE(0x2040, 0x721f, "Hauppauge", "HVR-950Q"),
AU0828_DEVICE(0x2040, 0x7280, "Hauppauge", "HVR-950Q"),
AU0828_DEVICE(0x0fd9, 0x0008, "Hauppauge", "HVR-950Q"),
AU0828_DEVICE(0x2040, 0x7201, "Hauppauge", "HVR-950Q-MXL"),
AU0828_DEVICE(0x2040, 0x7211, "Hauppauge", "HVR-950Q-MXL"),
AU0828_DEVICE(0x2040, 0x7281, "Hauppauge", "HVR-950Q-MXL"),
AU0828_DEVICE(0x05e1, 0x0480, "Hauppauge", "Woodbury"),
AU0828_DEVICE(0x2040, 0x8200, "Hauppauge", "Woodbury"),
AU0828_DEVICE(0x2040, 0x7260, "Hauppauge", "HVR-950Q"),
AU0828_DEVICE(0x2040, 0x7213, "Hauppauge", "HVR-950Q"),
AU0828_DEVICE(0x2040, 0x7270, "Hauppauge", "HVR-950Q"),

/* Syntek STK1160 */
अणु
	USB_AUDIO_DEVICE(0x05e1, 0x0408),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Syntek",
		.product_name = "STK1160",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_AUDIO_ALIGN_TRANSFER
	पूर्ण
पूर्ण,

/* Digidesign Mbox */
अणु
	/* Thanks to Clemens Ladisch <clemens@ladisch.de> */
	USB_DEVICE(0x0dba, 0x1000),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Digidesign",
		.product_name = "MBox",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[])अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3BE,
					.channels = 2,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = 0x4,
					.endpoपूर्णांक = 0x02,
					.ep_attr = USB_ENDPOINT_XFER_ISOC |
						USB_ENDPOINT_SYNC_SYNC,
					.maxpacksize = 0x130,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						48000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3BE,
					.channels = 2,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = 0x4,
					.endpoपूर्णांक = 0x81,
					.ep_attr = USB_ENDPOINT_XFER_ISOC |
						USB_ENDPOINT_SYNC_ASYNC,
					.maxpacksize = 0x130,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						48000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/* DIGIDESIGN MBOX 2 */
अणु
	USB_DEVICE(0x0dba, 0x3000),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Digidesign",
		.product_name = "Mbox 2",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3BE,
					.channels = 2,
					.अगरace = 2,
					.altsetting = 2,
					.altset_idx = 1,
					.attributes = 0x00,
					.endpoपूर्णांक = 0x03,
					.ep_attr = USB_ENDPOINT_SYNC_ASYNC,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						48000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 4,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
				.क्रमmats = SNDRV_PCM_FMTBIT_S24_3BE,
					.channels = 2,
					.अगरace = 4,
					.altsetting = 2,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x85,
					.ep_attr = USB_ENDPOINT_SYNC_SYNC,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						48000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 5,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 6,
				.type = QUIRK_MIDI_MIDIMAN,
				.data = &(स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info) अणु
					.out_ep =  0x02,
					.out_cables = 0x0001,
					.in_ep = 0x81,
					.in_पूर्णांकerval = 0x01,
					.in_cables = 0x0001
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/* Tascam US122 MKII - playback-only support */
	USB_DEVICE_VENDOR_SPEC(0x0644, 0x8021),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "TASCAM",
		.product_name = "US122 MKII",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_IGNORE_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 2,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x02,
					.ep_attr = USB_ENDPOINT_XFER_ISOC,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000 |
						 SNDRV_PCM_RATE_88200 |
						 SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 4,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000, 88200, 96000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/* Microsoft XboxLive Headset/Xbox Communicator */
अणु
	USB_DEVICE(0x045e, 0x0283),
	.bInterfaceClass = USB_CLASS_PER_INTERFACE,
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "Microsoft",
		.product_name = "XboxLive Headset/Xbox Communicator",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = &(स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				/* playback */
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
					.channels = 1,
					.अगरace = 0,
					.altsetting = 0,
					.altset_idx = 0,
					.attributes = 0,
					.endpoपूर्णांक = 0x04,
					.ep_attr = 0x05,
					.rates = SNDRV_PCM_RATE_CONTINUOUS,
					.rate_min = 22050,
					.rate_max = 22050
				पूर्ण
			पूर्ण,
			अणु
				/* capture */
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
					.channels = 1,
					.अगरace = 1,
					.altsetting = 0,
					.altset_idx = 0,
					.attributes = 0,
					.endpoपूर्णांक = 0x85,
					.ep_attr = 0x05,
					.rates = SNDRV_PCM_RATE_CONTINUOUS,
					.rate_min = 16000,
					.rate_max = 16000
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/* Reloop Play */
अणु
	USB_DEVICE(0x200c, 0x100b),
	.bInterfaceClass = USB_CLASS_PER_INTERFACE,
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = &(स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 4,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x01,
					.ep_attr = USB_ENDPOINT_SYNC_ADAPTIVE,
					.rates = SNDRV_PCM_RATE_44100 |
						 SNDRV_PCM_RATE_48000,
					.rate_min = 44100,
					.rate_max = 48000,
					.nr_rates = 2,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

अणु
	/*
	 * ZOOM R16/24 in audio पूर्णांकerface mode.
	 * Playback requires an extra four byte LE length indicator
	 * at the start of each isochronous packet. This quirk is
	 * enabled in create_standard_audio_quirk().
	 */
	USB_DEVICE(0x1686, 0x00dd),
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				/* Playback  */
				.अगरnum = 1,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE,
			पूर्ण,
			अणु
				/* Capture */
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_INTERFACE,
			पूर्ण,
			अणु
				/* Midi */
				.अगरnum = 3,
				.type = QUIRK_MIDI_STANDARD_INTERFACE
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण,
		पूर्ण
	पूर्ण
पूर्ण,

अणु
	/*
	 * Some USB MIDI devices करोn't have an audio control पूर्णांकerface,
	 * so we have to grab MIDI streaming पूर्णांकerfaces here.
	 */
	.match_flags = USB_DEVICE_ID_MATCH_INT_CLASS |
		       USB_DEVICE_ID_MATCH_INT_SUBCLASS,
	.bInterfaceClass = USB_CLASS_AUDIO,
	.bInterfaceSubClass = USB_SUBCLASS_MIDISTREAMING,
	.driver_info = (अचिन्हित दीर्घ) & (स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_MIDI_STANDARD_INTERFACE
	पूर्ण
पूर्ण,

/* disabled due to regression क्रम other devices;
 * see https://bugzilla.kernel.org/show_bug.cgi?id=199905
 */
#अगर 0
अणु
	/*
	 * Nura's first gen headphones use Cambridge Silicon Radio's venकरोr
	 * ID, but it looks like the product ID actually is only क्रम Nura.
	 * The capture पूर्णांकerface करोes not work at all (even on Winकरोws),
	 * and only the 48 kHz sample rate works क्रम the playback पूर्णांकerface.
	 */
	USB_DEVICE(0x0a12, 0x1243),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			/* Capture */
			अणु
				.अगरnum = 1,
				.type = QUIRK_IGNORE_INTERFACE,
			पूर्ण,
			/* Playback */
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
					.channels = 2,
					.अगरace = 2,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_FILL_MAX |
						UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x03,
					.ep_attr = USB_ENDPOINT_XFER_ISOC,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						48000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण,
		पूर्ण
	पूर्ण
पूर्ण,
#पूर्ण_अगर /* disabled */

अणु
	/*
	 * Bower's & Wilkins PX headphones only support the 48 kHz sample rate
	 * even though it advertises more. The capture पूर्णांकerface करोesn't work
	 * even on winकरोws.
	 */
	USB_DEVICE(0x19b5, 0x0021),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			/* Playback */
			अणु
				.अगरnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
					.channels = 2,
					.अगरace = 1,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = UAC_EP_CS_ATTR_FILL_MAX |
						UAC_EP_CS_ATTR_SAMPLE_RATE,
					.endpoपूर्णांक = 0x03,
					.ep_attr = USB_ENDPOINT_XFER_ISOC,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						48000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण,
		पूर्ण
	पूर्ण
पूर्ण,
/* MOTU Microbook II */
अणु
	USB_DEVICE_VENDOR_SPEC(0x07fd, 0x0004),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "MOTU",
		.product_name = "MicroBookII",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3BE,
					.channels = 6,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = 0,
					.endpoपूर्णांक = 0x84,
					.rates = SNDRV_PCM_RATE_96000,
					.ep_attr = USB_ENDPOINT_XFER_ISOC |
						   USB_ENDPOINT_SYNC_ASYNC,
					.rate_min = 96000,
					.rate_max = 96000,
					.nr_rates = 1,
					.maxpacksize = 0x00d8,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						96000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3BE,
					.channels = 8,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = 0,
					.endpoपूर्णांक = 0x03,
					.rates = SNDRV_PCM_RATE_96000,
					.ep_attr = USB_ENDPOINT_XFER_ISOC |
						   USB_ENDPOINT_SYNC_ASYNC,
					.rate_min = 96000,
					.rate_max = 96000,
					.nr_rates = 1,
					.maxpacksize = 0x0120,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						96000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * PIONEER DJ DDJ-SX3
	 * PCM is 12 channels out, 10 channels in @ 44.1 fixed
	 * पूर्णांकerface 0, venकरोr class alt setting 1 क्रम endpoपूर्णांकs 5 and 0x86
	 * The feedback क्रम the output is the input.
	 */
	USB_DEVICE_VENDOR_SPEC(0x2b73, 0x0023),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
					.channels = 12,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x05,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						   USB_ENDPOINT_SYNC_ASYNC,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
					.channels = 10,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x86,
					.ep_idx = 1,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						 USB_ENDPOINT_SYNC_ASYNC|
						 USB_ENDPOINT_USAGE_IMPLICIT_FB,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * Pioneer DJ DJM-250MK2
	 * PCM is 8 channels out @ 48 fixed (endpoपूर्णांक 0x01)
	 * and 8 channels in @ 48 fixed (endpoपूर्णांक 0x82).
	 *
	 * Both playback and recording is working, even simultaneously.
	 *
	 * Playback channels could be mapped to:
	 *  - CH1
	 *  - CH2
	 *  - AUX
	 *
	 * Recording channels could be mapped to:
	 *  - Post CH1 Fader
	 *  - Post CH2 Fader
	 *  - Cross Fader A
	 *  - Cross Fader B
	 *  - MIC
	 *  - AUX
	 *  - REC OUT
	 *
	 * There is reमुख्यing problem with recording directly from PHONO/LINE.
	 * If we map a channel to:
	 *  - CH1 Control Tone PHONO
	 *  - CH1 Control Tone LINE
	 *  - CH2 Control Tone PHONO
	 *  - CH2 Control Tone LINE
	 * it is silent.
	 * There is no संकेत even on other operating प्रणालीs with official drivers.
	 * The संकेत appears only when a supported application is started.
	 * This needs to be investigated yet...
	 * (there is quite a lot communication on the USB in both directions)
	 *
	 * In current version this mixer could be used क्रम playback
	 * and क्रम recording from vinyls (through Post CH* Fader)
	 * but not क्रम DVS (Digital Vinyl Systems) like in Mixxx.
	 */
	USB_DEVICE_VENDOR_SPEC(0x2b73, 0x0017),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8, // outमाला_दो
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x01,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						USB_ENDPOINT_SYNC_ASYNC,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 48000 पूर्ण
					पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8, // inमाला_दो
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x82,
					.ep_idx = 1,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_IMPLICIT_FB,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 48000 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * PIONEER DJ DDJ-RB
	 * PCM is 4 channels out, 2 dummy channels in @ 44.1 fixed
	 * The feedback क्रम the output is the dummy input.
	 */
	USB_DEVICE_VENDOR_SPEC(0x2b73, 0x000e),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 4,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x01,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						   USB_ENDPOINT_SYNC_ASYNC,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 2,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x82,
					.ep_idx = 1,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						 USB_ENDPOINT_SYNC_ASYNC|
						 USB_ENDPOINT_USAGE_IMPLICIT_FB,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

अणु
	/*
	 * PIONEER DJ DDJ-RR
	 * PCM is 6 channels out & 4 channels in @ 44.1 fixed
	 */
	USB_DEVICE_VENDOR_SPEC(0x2b73, 0x000d),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 6, //Master, Headphones & Booth
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x01,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						   USB_ENDPOINT_SYNC_ASYNC,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 4, //2x RCA inमाला_दो (CH1 & CH2)
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x82,
					.ep_idx = 1,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						 USB_ENDPOINT_SYNC_ASYNC|
						 USB_ENDPOINT_USAGE_IMPLICIT_FB,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

अणु
	/*
	 * PIONEER DJ DDJ-SR2
	 * PCM is 4 channels out, 6 channels in @ 44.1 fixed
	 * The Feedback क्रम the output is the input
	 */
	USB_DEVICE_VENDOR_SPEC(0x2b73, 0x001e),
		.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 4,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x01,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						USB_ENDPOINT_SYNC_ASYNC,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 6,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x82,
					.ep_idx = 1,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
					USB_ENDPOINT_USAGE_IMPLICIT_FB,
					.rates = SNDRV_PCM_RATE_44100,
					.rate_min = 44100,
					.rate_max = 44100,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

अणु
	/*
	 * Pioneer DJ DJM-900NXS2
	 * 10 channels playback & 12 channels capture @ 44.1/48/96kHz S24LE
	 */
	USB_DEVICE_VENDOR_SPEC(0x2b73, 0x000a),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 10,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x01,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
					    USB_ENDPOINT_SYNC_ASYNC,
					.rates = SNDRV_PCM_RATE_44100|
					    SNDRV_PCM_RATE_48000|
					    SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 3,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000, 96000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 12,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x82,
					.ep_idx = 1,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
					    USB_ENDPOINT_SYNC_ASYNC|
					    USB_ENDPOINT_USAGE_IMPLICIT_FB,
					.rates = SNDRV_PCM_RATE_44100|
					    SNDRV_PCM_RATE_48000|
					    SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 3,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु
						44100, 48000, 96000
					पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

/*
 * MacroSilicon MS2109 based HDMI capture cards
 *
 * These claim 96kHz 1ch in the descriptors, but are actually 48kHz 2ch.
 * They also need QUIRK_AUDIO_ALIGN_TRANSFER, which makes one wonder अगर
 * they pretend to be 96kHz mono as a workaround क्रम stereo being broken
 * by that...
 *
 * They also have an issue with initial stream alignment that causes the
 * channels to be swapped and out of phase, which is dealt with in quirks.c.
 */
अणु
	USB_AUDIO_DEVICE(0x534d, 0x2109),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.venकरोr_name = "MacroSilicon",
		.product_name = "MS2109",
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = &(स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_ALIGN_TRANSFER,
			पूर्ण,
			अणु
				.अगरnum = 2,
				.type = QUIRK_AUDIO_STANDARD_MIXER,
			पूर्ण,
			अणु
				.अगरnum = 3,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
					.channels = 2,
					.अगरace = 3,
					.altsetting = 1,
					.altset_idx = 1,
					.attributes = 0,
					.endpoपूर्णांक = 0x82,
					.ep_attr = USB_ENDPOINT_XFER_ISOC |
						USB_ENDPOINT_SYNC_ASYNC,
					.rates = SNDRV_PCM_RATE_CONTINUOUS,
					.rate_min = 48000,
					.rate_max = 48000,
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * Pioneer DJ DJM-750
	 * 8 channels playback & 8 channels capture @ 44.1/48/96kHz S24LE
	 */
	USB_DEVICE_VENDOR_SPEC(0x08e4, 0x017f),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x05,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
					    USB_ENDPOINT_SYNC_ASYNC,
					.rates = SNDRV_PCM_RATE_44100|
						SNDRV_PCM_RATE_48000|
						SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 3,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100, 48000, 96000 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x86,
					.ep_idx = 1,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_IMPLICIT_FB,
					.rates = SNDRV_PCM_RATE_44100|
						SNDRV_PCM_RATE_48000|
						SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 3,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100, 48000, 96000 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * Pioneer DJ DJM-850
	 * 8 channels playback and 8 channels capture @ 44.1/48/96kHz S24LE
	 * Playback on EP 0x05
	 * Capture on EP 0x86
	 */
	USB_DEVICE_VENDOR_SPEC(0x08e4, 0x0163),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x05,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
					    USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_DATA,
					.rates = SNDRV_PCM_RATE_44100|
						SNDRV_PCM_RATE_48000|
						SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 3,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100, 48000, 96000 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8,
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x86,
					.ep_idx = 1,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_DATA,
					.rates = SNDRV_PCM_RATE_44100|
						SNDRV_PCM_RATE_48000|
						SNDRV_PCM_RATE_96000,
					.rate_min = 44100,
					.rate_max = 96000,
					.nr_rates = 3,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 44100, 48000, 96000 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	/*
	 * Pioneer DJ DJM-450
	 * PCM is 8 channels out @ 48 fixed (endpoपूर्णांक 0x01)
	 * and 8 channels in @ 48 fixed (endpoपूर्णांक 0x82).
	 */
	USB_DEVICE_VENDOR_SPEC(0x2b73, 0x0013),
	.driver_info = (अचिन्हित दीर्घ) &(स्थिर काष्ठा snd_usb_audio_quirk) अणु
		.अगरnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (स्थिर काष्ठा snd_usb_audio_quirk[]) अणु
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8, // outमाला_दो
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x01,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						USB_ENDPOINT_SYNC_ASYNC,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 48000 पूर्ण
					पूर्ण
			पूर्ण,
			अणु
				.अगरnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = &(स्थिर काष्ठा audioक्रमmat) अणु
					.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
					.channels = 8, // inमाला_दो
					.अगरace = 0,
					.altsetting = 1,
					.altset_idx = 1,
					.endpoपूर्णांक = 0x82,
					.ep_idx = 1,
					.ep_attr = USB_ENDPOINT_XFER_ISOC|
						USB_ENDPOINT_SYNC_ASYNC|
						USB_ENDPOINT_USAGE_IMPLICIT_FB,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (अचिन्हित पूर्णांक[]) अणु 48000 पूर्ण
				पूर्ण
			पूर्ण,
			अणु
				.अगरnum = -1
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण,

#अघोषित USB_DEVICE_VENDOR_SPEC
#अघोषित USB_AUDIO_DEVICE
