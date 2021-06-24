<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * <linux/usb/audपन.स> -- USB Audio definitions.
 *
 * Copyright (C) 2006 Thumtronics Pty Ltd.
 * Developed क्रम Thumtronics by Grey Innovation
 * Ben Williamson <ben.williamson@greyinnovation.com>
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 2, as published by the Free Software Foundation.
 *
 * This file holds USB स्थिरants and काष्ठाures defined
 * by the USB Device Class Definition क्रम Audio Devices.
 * Comments below reference relevant sections of that करोcument:
 *
 * http://www.usb.org/developers/devclass_करोcs/audio10.pdf
 *
 * Types and defines in this file are either specअगरic to version 1.0 of
 * this standard or common क्रम newer versions.
 */

#अगर_अघोषित _UAPI__LINUX_USB_AUDIO_H
#घोषणा _UAPI__LINUX_USB_AUDIO_H

#समावेश <linux/types.h>

/* bInterfaceProtocol values to denote the version of the standard used */
#घोषणा UAC_VERSION_1			0x00
#घोषणा UAC_VERSION_2			0x20
#घोषणा UAC_VERSION_3			0x30

/* A.2 Audio Interface Subclass Codes */
#घोषणा USB_SUBCLASS_AUDIOCONTROL	0x01
#घोषणा USB_SUBCLASS_AUDIOSTREAMING	0x02
#घोषणा USB_SUBCLASS_MIDISTREAMING	0x03

/* A.5 Audio Class-Specअगरic AC Interface Descriptor Subtypes */
#घोषणा UAC_HEADER			0x01
#घोषणा UAC_INPUT_TERMINAL		0x02
#घोषणा UAC_OUTPUT_TERMINAL		0x03
#घोषणा UAC_MIXER_UNIT			0x04
#घोषणा UAC_SELECTOR_UNIT		0x05
#घोषणा UAC_FEATURE_UNIT		0x06
#घोषणा UAC1_PROCESSING_UNIT		0x07
#घोषणा UAC1_EXTENSION_UNIT		0x08

/* A.6 Audio Class-Specअगरic AS Interface Descriptor Subtypes */
#घोषणा UAC_AS_GENERAL			0x01
#घोषणा UAC_FORMAT_TYPE			0x02
#घोषणा UAC_FORMAT_SPECIFIC		0x03

/* A.7 Processing Unit Process Types */
#घोषणा UAC_PROCESS_UNDEFINED		0x00
#घोषणा UAC_PROCESS_UP_DOWNMIX		0x01
#घोषणा UAC_PROCESS_DOLBY_PROLOGIC	0x02
#घोषणा UAC_PROCESS_STEREO_EXTENDER	0x03
#घोषणा UAC_PROCESS_REVERB		0x04
#घोषणा UAC_PROCESS_CHORUS		0x05
#घोषणा UAC_PROCESS_DYN_RANGE_COMP	0x06

/* A.8 Audio Class-Specअगरic Endpoपूर्णांक Descriptor Subtypes */
#घोषणा UAC_EP_GENERAL			0x01

/* A.9 Audio Class-Specअगरic Request Codes */
#घोषणा UAC_SET_			0x00
#घोषणा UAC_GET_			0x80

#घोषणा UAC__CUR			0x1
#घोषणा UAC__MIN			0x2
#घोषणा UAC__MAX			0x3
#घोषणा UAC__RES			0x4
#घोषणा UAC__MEM			0x5

#घोषणा UAC_SET_CUR			(UAC_SET_ | UAC__CUR)
#घोषणा UAC_GET_CUR			(UAC_GET_ | UAC__CUR)
#घोषणा UAC_SET_MIN			(UAC_SET_ | UAC__MIN)
#घोषणा UAC_GET_MIN			(UAC_GET_ | UAC__MIN)
#घोषणा UAC_SET_MAX			(UAC_SET_ | UAC__MAX)
#घोषणा UAC_GET_MAX			(UAC_GET_ | UAC__MAX)
#घोषणा UAC_SET_RES			(UAC_SET_ | UAC__RES)
#घोषणा UAC_GET_RES			(UAC_GET_ | UAC__RES)
#घोषणा UAC_SET_MEM			(UAC_SET_ | UAC__MEM)
#घोषणा UAC_GET_MEM			(UAC_GET_ | UAC__MEM)

#घोषणा UAC_GET_STAT			0xff

/* A.10 Control Selector Codes */

/* A.10.1 Terminal Control Selectors */
#घोषणा UAC_TERM_COPY_PROTECT		0x01

/* A.10.2 Feature Unit Control Selectors */
#घोषणा UAC_FU_MUTE			0x01
#घोषणा UAC_FU_VOLUME			0x02
#घोषणा UAC_FU_BASS			0x03
#घोषणा UAC_FU_MID			0x04
#घोषणा UAC_FU_TREBLE			0x05
#घोषणा UAC_FU_GRAPHIC_EQUALIZER	0x06
#घोषणा UAC_FU_AUTOMATIC_GAIN		0x07
#घोषणा UAC_FU_DELAY			0x08
#घोषणा UAC_FU_BASS_BOOST		0x09
#घोषणा UAC_FU_LOUDNESS			0x0a

#घोषणा UAC_CONTROL_BIT(CS)	(1 << ((CS) - 1))

/* A.10.3.1 Up/Down-mix Processing Unit Controls Selectors */
#घोषणा UAC_UD_ENABLE			0x01
#घोषणा UAC_UD_MODE_SELECT		0x02

/* A.10.3.2 Dolby Prologic (पंचांग) Processing Unit Controls Selectors */
#घोषणा UAC_DP_ENABLE			0x01
#घोषणा UAC_DP_MODE_SELECT		0x02

/* A.10.3.3 3D Stereo Extender Processing Unit Control Selectors */
#घोषणा UAC_3D_ENABLE			0x01
#घोषणा UAC_3D_SPACE			0x02

/* A.10.3.4 Reverberation Processing Unit Control Selectors */
#घोषणा UAC_REVERB_ENABLE		0x01
#घोषणा UAC_REVERB_LEVEL		0x02
#घोषणा UAC_REVERB_TIME			0x03
#घोषणा UAC_REVERB_FEEDBACK		0x04

/* A.10.3.5 Chorus Processing Unit Control Selectors */
#घोषणा UAC_CHORUS_ENABLE		0x01
#घोषणा UAC_CHORUS_LEVEL		0x02
#घोषणा UAC_CHORUS_RATE			0x03
#घोषणा UAC_CHORUS_DEPTH		0x04

/* A.10.3.6 Dynamic Range Compressor Unit Control Selectors */
#घोषणा UAC_DCR_ENABLE			0x01
#घोषणा UAC_DCR_RATE			0x02
#घोषणा UAC_DCR_MAXAMPL			0x03
#घोषणा UAC_DCR_THRESHOLD		0x04
#घोषणा UAC_DCR_ATTACK_TIME		0x05
#घोषणा UAC_DCR_RELEASE_TIME		0x06

/* A.10.4 Extension Unit Control Selectors */
#घोषणा UAC_XU_ENABLE			0x01

/* MIDI - A.1 MS Class-Specअगरic Interface Descriptor Subtypes */
#घोषणा UAC_MS_HEADER			0x01
#घोषणा UAC_MIDI_IN_JACK		0x02
#घोषणा UAC_MIDI_OUT_JACK		0x03

/* MIDI - A.1 MS Class-Specअगरic Endpoपूर्णांक Descriptor Subtypes */
#घोषणा UAC_MS_GENERAL			0x01

/* Terminals - 2.1 USB Terminal Types */
#घोषणा UAC_TERMINAL_UNDEFINED		0x100
#घोषणा UAC_TERMINAL_STREAMING		0x101
#घोषणा UAC_TERMINAL_VENDOR_SPEC	0x1FF

/* Terminal Control Selectors */
/* 4.3.2  Class-Specअगरic AC Interface Descriptor */
काष्ठा uac1_ac_header_descriptor अणु
	__u8  bLength;			/* 8 + n */
	__u8  bDescriptorType;		/* USB_DT_CS_INTERFACE */
	__u8  bDescriptorSubtype;	/* UAC_MS_HEADER */
	__le16 bcdADC;			/* 0x0100 */
	__le16 wTotalLength;		/* includes Unit and Terminal desc. */
	__u8  bInCollection;		/* n */
	__u8  baInterfaceNr[];		/* [n] */
पूर्ण __attribute__ ((packed));

#घोषणा UAC_DT_AC_HEADER_SIZE(n)	(8 + (n))

/* As above, but more useful क्रम defining your own descriptors: */
#घोषणा DECLARE_UAC_AC_HEADER_DESCRIPTOR(n)			\
काष्ठा uac1_ac_header_descriptor_##n अणु			\
	__u8  bLength;						\
	__u8  bDescriptorType;					\
	__u8  bDescriptorSubtype;				\
	__le16 bcdADC;						\
	__le16 wTotalLength;					\
	__u8  bInCollection;					\
	__u8  baInterfaceNr[n];					\
पूर्ण __attribute__ ((packed))

/* 4.3.2.1 Input Terminal Descriptor */
काष्ठा uac_input_terminal_descriptor अणु
	__u8  bLength;			/* in bytes: 12 */
	__u8  bDescriptorType;		/* CS_INTERFACE descriptor type */
	__u8  bDescriptorSubtype;	/* INPUT_TERMINAL descriptor subtype */
	__u8  bTerminalID;		/* Constant uniquely terminal ID */
	__le16 wTerminalType;		/* USB Audio Terminal Types */
	__u8  bAssocTerminal;		/* ID of the Output Terminal associated */
	__u8  bNrChannels;		/* Number of logical output channels */
	__le16 wChannelConfig;
	__u8  iChannelNames;
	__u8  iTerminal;
पूर्ण __attribute__ ((packed));

#घोषणा UAC_DT_INPUT_TERMINAL_SIZE			12

/* Terminals - 2.2 Input Terminal Types */
#घोषणा UAC_INPUT_TERMINAL_UNDEFINED			0x200
#घोषणा UAC_INPUT_TERMINAL_MICROPHONE			0x201
#घोषणा UAC_INPUT_TERMINAL_DESKTOP_MICROPHONE		0x202
#घोषणा UAC_INPUT_TERMINAL_PERSONAL_MICROPHONE		0x203
#घोषणा UAC_INPUT_TERMINAL_OMNI_सूची_MICROPHONE		0x204
#घोषणा UAC_INPUT_TERMINAL_MICROPHONE_ARRAY		0x205
#घोषणा UAC_INPUT_TERMINAL_PROC_MICROPHONE_ARRAY	0x206

/* Terminals - control selectors */

#घोषणा UAC_TERMINAL_CS_COPY_PROTECT_CONTROL		0x01

/* 4.3.2.2 Output Terminal Descriptor */
काष्ठा uac1_output_terminal_descriptor अणु
	__u8  bLength;			/* in bytes: 9 */
	__u8  bDescriptorType;		/* CS_INTERFACE descriptor type */
	__u8  bDescriptorSubtype;	/* OUTPUT_TERMINAL descriptor subtype */
	__u8  bTerminalID;		/* Constant uniquely terminal ID */
	__le16 wTerminalType;		/* USB Audio Terminal Types */
	__u8  bAssocTerminal;		/* ID of the Input Terminal associated */
	__u8  bSourceID;		/* ID of the connected Unit or Terminal*/
	__u8  iTerminal;
पूर्ण __attribute__ ((packed));

#घोषणा UAC_DT_OUTPUT_TERMINAL_SIZE			9

/* Terminals - 2.3 Output Terminal Types */
#घोषणा UAC_OUTPUT_TERMINAL_UNDEFINED			0x300
#घोषणा UAC_OUTPUT_TERMINAL_SPEAKER			0x301
#घोषणा UAC_OUTPUT_TERMINAL_HEADPHONES			0x302
#घोषणा UAC_OUTPUT_TERMINAL_HEAD_MOUNTED_DISPLAY_AUDIO	0x303
#घोषणा UAC_OUTPUT_TERMINAL_DESKTOP_SPEAKER		0x304
#घोषणा UAC_OUTPUT_TERMINAL_ROOM_SPEAKER		0x305
#घोषणा UAC_OUTPUT_TERMINAL_COMMUNICATION_SPEAKER	0x306
#घोषणा UAC_OUTPUT_TERMINAL_LOW_FREQ_EFFECTS_SPEAKER	0x307

/* Terminals - 2.4 Bi-directional Terminal Types */
#घोषणा UAC_BIसूची_TERMINAL_UNDEFINED			0x400
#घोषणा UAC_BIसूची_TERMINAL_HANDSET			0x401
#घोषणा UAC_BIसूची_TERMINAL_HEADSET			0x402
#घोषणा UAC_BIसूची_TERMINAL_SPEAKER_PHONE		0x403
#घोषणा UAC_BIसूची_TERMINAL_ECHO_SUPPRESSING		0x404
#घोषणा UAC_BIसूची_TERMINAL_ECHO_CANCELING		0x405

/* Set bControlSize = 2 as शेष setting */
#घोषणा UAC_DT_FEATURE_UNIT_SIZE(ch)		(7 + ((ch) + 1) * 2)

/* As above, but more useful क्रम defining your own descriptors: */
#घोषणा DECLARE_UAC_FEATURE_UNIT_DESCRIPTOR(ch)			\
काष्ठा uac_feature_unit_descriptor_##ch अणु			\
	__u8  bLength;						\
	__u8  bDescriptorType;					\
	__u8  bDescriptorSubtype;				\
	__u8  bUnitID;						\
	__u8  bSourceID;					\
	__u8  bControlSize;					\
	__le16 bmaControls[ch + 1];				\
	__u8  iFeature;						\
पूर्ण __attribute__ ((packed))

/* 4.3.2.3 Mixer Unit Descriptor */
काष्ठा uac_mixer_unit_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bUnitID;
	__u8 bNrInPins;
	__u8 baSourceID[];
पूर्ण __attribute__ ((packed));

अटल अंतरभूत __u8 uac_mixer_unit_bNrChannels(काष्ठा uac_mixer_unit_descriptor *desc)
अणु
	वापस desc->baSourceID[desc->bNrInPins];
पूर्ण

अटल अंतरभूत __u32 uac_mixer_unit_wChannelConfig(काष्ठा uac_mixer_unit_descriptor *desc,
						  पूर्णांक protocol)
अणु
	अगर (protocol == UAC_VERSION_1)
		वापस (desc->baSourceID[desc->bNrInPins + 2] << 8) |
			desc->baSourceID[desc->bNrInPins + 1];
	अन्यथा
		वापस  (desc->baSourceID[desc->bNrInPins + 4] << 24) |
			(desc->baSourceID[desc->bNrInPins + 3] << 16) |
			(desc->baSourceID[desc->bNrInPins + 2] << 8)  |
			(desc->baSourceID[desc->bNrInPins + 1]);
पूर्ण

अटल अंतरभूत __u8 uac_mixer_unit_iChannelNames(काष्ठा uac_mixer_unit_descriptor *desc,
						पूर्णांक protocol)
अणु
	वापस (protocol == UAC_VERSION_1) ?
		desc->baSourceID[desc->bNrInPins + 3] :
		desc->baSourceID[desc->bNrInPins + 5];
पूर्ण

अटल अंतरभूत __u8 *uac_mixer_unit_bmControls(काष्ठा uac_mixer_unit_descriptor *desc,
					      पूर्णांक protocol)
अणु
	चयन (protocol) अणु
	हाल UAC_VERSION_1:
		वापस &desc->baSourceID[desc->bNrInPins + 4];
	हाल UAC_VERSION_2:
		वापस &desc->baSourceID[desc->bNrInPins + 6];
	हाल UAC_VERSION_3:
		वापस &desc->baSourceID[desc->bNrInPins + 2];
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत __u16 uac3_mixer_unit_wClusterDescrID(काष्ठा uac_mixer_unit_descriptor *desc)
अणु
	वापस (desc->baSourceID[desc->bNrInPins + 1] << 8) |
		desc->baSourceID[desc->bNrInPins];
पूर्ण

अटल अंतरभूत __u8 uac_mixer_unit_iMixer(काष्ठा uac_mixer_unit_descriptor *desc)
अणु
	__u8 *raw = (__u8 *) desc;
	वापस raw[desc->bLength - 1];
पूर्ण

/* 4.3.2.4 Selector Unit Descriptor */
काष्ठा uac_selector_unit_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bUपूर्णांकID;
	__u8 bNrInPins;
	__u8 baSourceID[];
पूर्ण __attribute__ ((packed));

अटल अंतरभूत __u8 uac_selector_unit_iSelector(काष्ठा uac_selector_unit_descriptor *desc)
अणु
	__u8 *raw = (__u8 *) desc;
	वापस raw[desc->bLength - 1];
पूर्ण

/* 4.3.2.5 Feature Unit Descriptor */
काष्ठा uac_feature_unit_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bUnitID;
	__u8 bSourceID;
	__u8 bControlSize;
	__u8 bmaControls[0]; /* variable length */
पूर्ण __attribute__((packed));

अटल अंतरभूत __u8 uac_feature_unit_iFeature(काष्ठा uac_feature_unit_descriptor *desc)
अणु
	__u8 *raw = (__u8 *) desc;
	वापस raw[desc->bLength - 1];
पूर्ण

/* 4.3.2.6 Processing Unit Descriptors */
काष्ठा uac_processing_unit_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bUnitID;
	__le16 wProcessType;
	__u8 bNrInPins;
	__u8 baSourceID[];
पूर्ण __attribute__ ((packed));

अटल अंतरभूत __u8 uac_processing_unit_bNrChannels(काष्ठा uac_processing_unit_descriptor *desc)
अणु
	वापस desc->baSourceID[desc->bNrInPins];
पूर्ण

अटल अंतरभूत __u32 uac_processing_unit_wChannelConfig(काष्ठा uac_processing_unit_descriptor *desc,
						       पूर्णांक protocol)
अणु
	अगर (protocol == UAC_VERSION_1)
		वापस (desc->baSourceID[desc->bNrInPins + 2] << 8) |
			desc->baSourceID[desc->bNrInPins + 1];
	अन्यथा
		वापस  (desc->baSourceID[desc->bNrInPins + 4] << 24) |
			(desc->baSourceID[desc->bNrInPins + 3] << 16) |
			(desc->baSourceID[desc->bNrInPins + 2] << 8)  |
			(desc->baSourceID[desc->bNrInPins + 1]);
पूर्ण

अटल अंतरभूत __u8 uac_processing_unit_iChannelNames(काष्ठा uac_processing_unit_descriptor *desc,
						     पूर्णांक protocol)
अणु
	वापस (protocol == UAC_VERSION_1) ?
		desc->baSourceID[desc->bNrInPins + 3] :
		desc->baSourceID[desc->bNrInPins + 5];
पूर्ण

अटल अंतरभूत __u8 uac_processing_unit_bControlSize(काष्ठा uac_processing_unit_descriptor *desc,
						    पूर्णांक protocol)
अणु
	चयन (protocol) अणु
	हाल UAC_VERSION_1:
		वापस desc->baSourceID[desc->bNrInPins + 4];
	हाल UAC_VERSION_2:
		वापस 2; /* in UAC2, this value is स्थिरant */
	हाल UAC_VERSION_3:
		वापस 4; /* in UAC3, this value is स्थिरant */
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल अंतरभूत __u8 *uac_processing_unit_bmControls(काष्ठा uac_processing_unit_descriptor *desc,
						   पूर्णांक protocol)
अणु
	चयन (protocol) अणु
	हाल UAC_VERSION_1:
		वापस &desc->baSourceID[desc->bNrInPins + 5];
	हाल UAC_VERSION_2:
		वापस &desc->baSourceID[desc->bNrInPins + 6];
	हाल UAC_VERSION_3:
		वापस &desc->baSourceID[desc->bNrInPins + 2];
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत __u8 uac_processing_unit_iProcessing(काष्ठा uac_processing_unit_descriptor *desc,
						   पूर्णांक protocol)
अणु
	__u8 control_size = uac_processing_unit_bControlSize(desc, protocol);

	चयन (protocol) अणु
	हाल UAC_VERSION_1:
	हाल UAC_VERSION_2:
	शेष:
		वापस *(uac_processing_unit_bmControls(desc, protocol)
			 + control_size);
	हाल UAC_VERSION_3:
		वापस 0; /* UAC3 करोes not have this field */
	पूर्ण
पूर्ण

अटल अंतरभूत __u8 *uac_processing_unit_specअगरic(काष्ठा uac_processing_unit_descriptor *desc,
						 पूर्णांक protocol)
अणु
	__u8 control_size = uac_processing_unit_bControlSize(desc, protocol);

	चयन (protocol) अणु
	हाल UAC_VERSION_1:
	हाल UAC_VERSION_2:
	शेष:
		वापस uac_processing_unit_bmControls(desc, protocol)
			+ control_size + 1;
	हाल UAC_VERSION_3:
		वापस uac_processing_unit_bmControls(desc, protocol)
			+ control_size;
	पूर्ण
पूर्ण

/*
 * Extension Unit (XU) has almost compatible layout with Processing Unit, but
 * on UAC2, it has a dअगरferent bmControls size (bControlSize); it's 1 byte क्रम
 * XU जबतक 2 bytes क्रम PU.  The last iExtension field is a one-byte index as
 * well as iProcessing field of PU.
 */
अटल अंतरभूत __u8 uac_extension_unit_bControlSize(काष्ठा uac_processing_unit_descriptor *desc,
						   पूर्णांक protocol)
अणु
	चयन (protocol) अणु
	हाल UAC_VERSION_1:
		वापस desc->baSourceID[desc->bNrInPins + 4];
	हाल UAC_VERSION_2:
		वापस 1; /* in UAC2, this value is स्थिरant */
	हाल UAC_VERSION_3:
		वापस 4; /* in UAC3, this value is स्थिरant */
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल अंतरभूत __u8 uac_extension_unit_iExtension(काष्ठा uac_processing_unit_descriptor *desc,
						 पूर्णांक protocol)
अणु
	__u8 control_size = uac_extension_unit_bControlSize(desc, protocol);

	चयन (protocol) अणु
	हाल UAC_VERSION_1:
	हाल UAC_VERSION_2:
	शेष:
		वापस *(uac_processing_unit_bmControls(desc, protocol)
			 + control_size);
	हाल UAC_VERSION_3:
		वापस 0; /* UAC3 करोes not have this field */
	पूर्ण
पूर्ण

/* 4.5.2 Class-Specअगरic AS Interface Descriptor */
काष्ठा uac1_as_header_descriptor अणु
	__u8  bLength;			/* in bytes: 7 */
	__u8  bDescriptorType;		/* USB_DT_CS_INTERFACE */
	__u8  bDescriptorSubtype;	/* AS_GENERAL */
	__u8  bTerminalLink;		/* Terminal ID of connected Terminal */
	__u8  bDelay;			/* Delay पूर्णांकroduced by the data path */
	__le16 wFormatTag;		/* The Audio Data Format */
पूर्ण __attribute__ ((packed));

#घोषणा UAC_DT_AS_HEADER_SIZE		7

/* Formats - A.1.1 Audio Data Format Type I Codes */
#घोषणा UAC_FORMAT_TYPE_I_UNDEFINED	0x0
#घोषणा UAC_FORMAT_TYPE_I_PCM		0x1
#घोषणा UAC_FORMAT_TYPE_I_PCM8		0x2
#घोषणा UAC_FORMAT_TYPE_I_IEEE_FLOAT	0x3
#घोषणा UAC_FORMAT_TYPE_I_ALAW		0x4
#घोषणा UAC_FORMAT_TYPE_I_MULAW		0x5

काष्ठा uac_क्रमmat_type_i_continuous_descriptor अणु
	__u8  bLength;			/* in bytes: 8 + (ns * 3) */
	__u8  bDescriptorType;		/* USB_DT_CS_INTERFACE */
	__u8  bDescriptorSubtype;	/* FORMAT_TYPE */
	__u8  bFormatType;		/* FORMAT_TYPE_1 */
	__u8  bNrChannels;		/* physical channels in the stream */
	__u8  bSubframeSize;		/* */
	__u8  bBitResolution;
	__u8  bSamFreqType;
	__u8  tLowerSamFreq[3];
	__u8  tUpperSamFreq[3];
पूर्ण __attribute__ ((packed));

#घोषणा UAC_FORMAT_TYPE_I_CONTINUOUS_DESC_SIZE	14

काष्ठा uac_क्रमmat_type_i_discrete_descriptor अणु
	__u8  bLength;			/* in bytes: 8 + (ns * 3) */
	__u8  bDescriptorType;		/* USB_DT_CS_INTERFACE */
	__u8  bDescriptorSubtype;	/* FORMAT_TYPE */
	__u8  bFormatType;		/* FORMAT_TYPE_1 */
	__u8  bNrChannels;		/* physical channels in the stream */
	__u8  bSubframeSize;		/* */
	__u8  bBitResolution;
	__u8  bSamFreqType;
	__u8  tSamFreq[][3];
पूर्ण __attribute__ ((packed));

#घोषणा DECLARE_UAC_FORMAT_TYPE_I_DISCRETE_DESC(n)		\
काष्ठा uac_क्रमmat_type_i_discrete_descriptor_##n अणु		\
	__u8  bLength;						\
	__u8  bDescriptorType;					\
	__u8  bDescriptorSubtype;				\
	__u8  bFormatType;					\
	__u8  bNrChannels;					\
	__u8  bSubframeSize;					\
	__u8  bBitResolution;					\
	__u8  bSamFreqType;					\
	__u8  tSamFreq[n][3];					\
पूर्ण __attribute__ ((packed))

#घोषणा UAC_FORMAT_TYPE_I_DISCRETE_DESC_SIZE(n)	(8 + (n * 3))

काष्ठा uac_क्रमmat_type_i_ext_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bFormatType;
	__u8 bSubslotSize;
	__u8 bBitResolution;
	__u8 bHeaderLength;
	__u8 bControlSize;
	__u8 bSideBandProtocol;
पूर्ण __attribute__((packed));

/* Formats - Audio Data Format Type I Codes */

#घोषणा UAC_FORMAT_TYPE_II_MPEG	0x1001
#घोषणा UAC_FORMAT_TYPE_II_AC3	0x1002

काष्ठा uac_क्रमmat_type_ii_discrete_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bFormatType;
	__le16 wMaxBitRate;
	__le16 wSamplesPerFrame;
	__u8 bSamFreqType;
	__u8 tSamFreq[][3];
पूर्ण __attribute__((packed));

काष्ठा uac_क्रमmat_type_ii_ext_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bFormatType;
	__le16 wMaxBitRate;
	__le16 wSamplesPerFrame;
	__u8 bHeaderLength;
	__u8 bSideBandProtocol;
पूर्ण __attribute__((packed));

/* type III */
#घोषणा UAC_FORMAT_TYPE_III_IEC1937_AC3	0x2001
#घोषणा UAC_FORMAT_TYPE_III_IEC1937_MPEG1_LAYER1	0x2002
#घोषणा UAC_FORMAT_TYPE_III_IEC1937_MPEG2_NOEXT	0x2003
#घोषणा UAC_FORMAT_TYPE_III_IEC1937_MPEG2_EXT	0x2004
#घोषणा UAC_FORMAT_TYPE_III_IEC1937_MPEG2_LAYER1_LS	0x2005
#घोषणा UAC_FORMAT_TYPE_III_IEC1937_MPEG2_LAYER23_LS	0x2006

/* Formats - A.2 Format Type Codes */
#घोषणा UAC_FORMAT_TYPE_UNDEFINED	0x0
#घोषणा UAC_FORMAT_TYPE_I		0x1
#घोषणा UAC_FORMAT_TYPE_II		0x2
#घोषणा UAC_FORMAT_TYPE_III		0x3
#घोषणा UAC_EXT_FORMAT_TYPE_I		0x81
#घोषणा UAC_EXT_FORMAT_TYPE_II		0x82
#घोषणा UAC_EXT_FORMAT_TYPE_III		0x83

काष्ठा uac_iso_endpoपूर्णांक_descriptor अणु
	__u8  bLength;			/* in bytes: 7 */
	__u8  bDescriptorType;		/* USB_DT_CS_ENDPOINT */
	__u8  bDescriptorSubtype;	/* EP_GENERAL */
	__u8  bmAttributes;
	__u8  bLockDelayUnits;
	__le16 wLockDelay;
पूर्ण __attribute__((packed));
#घोषणा UAC_ISO_ENDPOINT_DESC_SIZE	7

#घोषणा UAC_EP_CS_ATTR_SAMPLE_RATE	0x01
#घोषणा UAC_EP_CS_ATTR_PITCH_CONTROL	0x02
#घोषणा UAC_EP_CS_ATTR_FILL_MAX		0x80

/* status word क्रमmat (3.7.1.1) */

#घोषणा UAC1_STATUS_TYPE_ORIG_MASK		0x0f
#घोषणा UAC1_STATUS_TYPE_ORIG_AUDIO_CONTROL_IF	0x0
#घोषणा UAC1_STATUS_TYPE_ORIG_AUDIO_STREAM_IF	0x1
#घोषणा UAC1_STATUS_TYPE_ORIG_AUDIO_STREAM_EP	0x2

#घोषणा UAC1_STATUS_TYPE_IRQ_PENDING		(1 << 7)
#घोषणा UAC1_STATUS_TYPE_MEM_CHANGED		(1 << 6)

काष्ठा uac1_status_word अणु
	__u8 bStatusType;
	__u8 bOriginator;
पूर्ण __attribute__((packed));


#पूर्ण_अगर /* _UAPI__LINUX_USB_AUDIO_H */
