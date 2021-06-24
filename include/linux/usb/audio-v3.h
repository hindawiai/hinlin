<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2017 Ruslan Bilovol <ruslan.bilovol@gmail.com>
 *
 * This file holds USB स्थिरants and काष्ठाures defined
 * by the USB DEVICE CLASS DEFINITION FOR AUDIO DEVICES Release 3.0.
 */

#अगर_अघोषित __LINUX_USB_AUDIO_V3_H
#घोषणा __LINUX_USB_AUDIO_V3_H

#समावेश <linux/types.h>

/*
 * v1.0, v2.0 and v3.0 of this standard have many things in common. For the rest
 * of the definitions, please refer to audपन.स and audio-v2.h
 */

/* All High Capability descriptors have these 2 fields at the beginning */
काष्ठा uac3_hc_descriptor_header अणु
	__le16 wLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__le16 wDescriptorID;
पूर्ण __attribute__ ((packed));

/* 4.3.1 CLUSTER DESCRIPTOR HEADER */
काष्ठा uac3_cluster_header_descriptor अणु
	__le16 wLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__le16 wDescriptorID;
	__u8 bNrChannels;
पूर्ण __attribute__ ((packed));

/* 4.3.2.1 SEGMENTS */
काष्ठा uac3_cluster_segment_descriptor अणु
	__le16 wLength;
	__u8 bSegmentType;
	/* __u8[0]; segment-specअगरic data */
पूर्ण __attribute__ ((packed));

/* 4.3.2.1.1 END SEGMENT */
काष्ठा uac3_cluster_end_segment_descriptor अणु
	__le16 wLength;
	__u8 bSegmentType;		/* Constant END_SEGMENT */
पूर्ण __attribute__ ((packed));

/* 4.3.2.1.3.1 INFORMATION SEGMENT */
काष्ठा uac3_cluster_inक्रमmation_segment_descriptor अणु
	__le16 wLength;
	__u8 bSegmentType;
	__u8 bChPurpose;
	__u8 bChRelationship;
	__u8 bChGroupID;
पूर्ण __attribute__ ((packed));

/* 4.5.2 CLASS-SPECIFIC AC INTERFACE DESCRIPTOR */
काष्ठा uac3_ac_header_descriptor अणु
	__u8 bLength;			/* 10 */
	__u8 bDescriptorType;		/* CS_INTERFACE descriptor type */
	__u8 bDescriptorSubtype;	/* HEADER descriptor subtype */
	__u8 bCategory;

	/* includes Clock Source, Unit, Terminal, and Power Doमुख्य desc. */
	__le16 wTotalLength;

	__le32 bmControls;
पूर्ण __attribute__ ((packed));

/* 4.5.2.1 INPUT TERMINAL DESCRIPTOR */
काष्ठा uac3_input_terminal_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bTerminalID;
	__le16 wTerminalType;
	__u8 bAssocTerminal;
	__u8 bCSourceID;
	__le32 bmControls;
	__le16 wClusterDescrID;
	__le16 wExTerminalDescrID;
	__le16 wConnectorsDescrID;
	__le16 wTerminalDescrStr;
पूर्ण __attribute__((packed));

/* 4.5.2.2 OUTPUT TERMINAL DESCRIPTOR */
काष्ठा uac3_output_terminal_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bTerminalID;
	__le16 wTerminalType;
	__u8 bAssocTerminal;
	__u8 bSourceID;
	__u8 bCSourceID;
	__le32 bmControls;
	__le16 wExTerminalDescrID;
	__le16 wConnectorsDescrID;
	__le16 wTerminalDescrStr;
पूर्ण __attribute__((packed));

/* 4.5.2.7 FEATURE UNIT DESCRIPTOR */
काष्ठा uac3_feature_unit_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bUnitID;
	__u8 bSourceID;
	/* bmaControls is actually u32,
	 * but u8 is needed क्रम the hybrid parser */
	__u8 bmaControls[]; /* variable length */
	/* wFeatureDescrStr omitted */
पूर्ण __attribute__((packed));

#घोषणा UAC3_DT_FEATURE_UNIT_SIZE(ch)		(7 + ((ch) + 1) * 4)

/* As above, but more useful क्रम defining your own descriptors */
#घोषणा DECLARE_UAC3_FEATURE_UNIT_DESCRIPTOR(ch)		\
काष्ठा uac3_feature_unit_descriptor_##ch अणु			\
	__u8 bLength;						\
	__u8 bDescriptorType;					\
	__u8 bDescriptorSubtype;				\
	__u8 bUnitID;						\
	__u8 bSourceID;						\
	__le32 bmaControls[ch + 1];				\
	__le16 wFeatureDescrStr;				\
पूर्ण __attribute__ ((packed))

/* 4.5.2.12 CLOCK SOURCE DESCRIPTOR */
काष्ठा uac3_घड़ी_source_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bClockID;
	__u8 bmAttributes;
	__le32 bmControls;
	__u8 bReferenceTerminal;
	__le16 wClockSourceStr;
पूर्ण __attribute__((packed));

/* bmAttribute fields */
#घोषणा UAC3_CLOCK_SOURCE_TYPE_EXT	0x0
#घोषणा UAC3_CLOCK_SOURCE_TYPE_INT	0x1
#घोषणा UAC3_CLOCK_SOURCE_ASYNC		(0 << 2)
#घोषणा UAC3_CLOCK_SOURCE_SYNCED_TO_SOF	(1 << 1)

/* 4.5.2.13 CLOCK SELECTOR DESCRIPTOR */
काष्ठा uac3_घड़ी_selector_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bClockID;
	__u8 bNrInPins;
	__u8 baCSourceID[];
	/* bmControls and wCSelectorDescrStr omitted */
पूर्ण __attribute__((packed));

/* 4.5.2.14 CLOCK MULTIPLIER DESCRIPTOR */
काष्ठा uac3_घड़ी_multiplier_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bClockID;
	__u8 bCSourceID;
	__le32 bmControls;
	__le16 wCMultiplierDescrStr;
पूर्ण __attribute__((packed));

/* 4.5.2.15 POWER DOMAIN DESCRIPTOR */
काष्ठा uac3_घातer_करोमुख्य_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bPowerDoमुख्यID;
	__le16 waRecoveryTime1;
	__le16 waRecoveryTime2;
	__u8 bNrEntities;
	__u8 baEntityID[];
	/* wPDoमुख्यDescrStr omitted */
पूर्ण __attribute__((packed));

/* As above, but more useful क्रम defining your own descriptors */
#घोषणा DECLARE_UAC3_POWER_DOMAIN_DESCRIPTOR(n)			\
काष्ठा uac3_घातer_करोमुख्य_descriptor_##n अणु			\
	__u8 bLength;						\
	__u8 bDescriptorType;					\
	__u8 bDescriptorSubtype;				\
	__u8 bPowerDoमुख्यID;					\
	__le16 waRecoveryTime1;					\
	__le16 waRecoveryTime2;					\
	__u8 bNrEntities;					\
	__u8 baEntityID[n];					\
	__le16 wPDoमुख्यDescrStr;					\
पूर्ण __attribute__ ((packed))

/* 4.7.2 CLASS-SPECIFIC AS INTERFACE DESCRIPTOR */
काष्ठा uac3_as_header_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__u8 bTerminalLink;
	__le32 bmControls;
	__le16 wClusterDescrID;
	__le64 bmFormats;
	__u8 bSubslotSize;
	__u8 bBitResolution;
	__le16 bmAuxProtocols;
	__u8 bControlSize;
पूर्ण __attribute__((packed));

#घोषणा UAC3_FORMAT_TYPE_I_RAW_DATA	(1 << 6)

/* 4.8.1.2 CLASS-SPECIFIC AS ISOCHRONOUS AUDIO DATA ENDPOINT DESCRIPTOR */
काष्ठा uac3_iso_endpoपूर्णांक_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDescriptorSubtype;
	__le32 bmControls;
	__u8 bLockDelayUnits;
	__le16 wLockDelay;
पूर्ण __attribute__((packed));

/* 5.2.1.6.1 INSERTION CONTROL PARAMETER BLOCK */
काष्ठा uac3_insertion_ctl_blk अणु
	__u8 bSize;
	__u8 bmConInserted;
पूर्ण __attribute__ ((packed));

/* 6.1 INTERRUPT DATA MESSAGE */
काष्ठा uac3_पूर्णांकerrupt_data_msg अणु
	__u8 bInfo;
	__u8 bSourceType;
	__le16 wValue;
	__le16 wIndex;
पूर्ण __attribute__((packed));

/* A.2 AUDIO AUDIO FUNCTION SUBCLASS CODES */
#घोषणा UAC3_FUNCTION_SUBCLASS_UNDEFINED	0x00
#घोषणा UAC3_FUNCTION_SUBCLASS_FULL_ADC_3_0	0x01
/* BADD profiles */
#घोषणा UAC3_FUNCTION_SUBCLASS_GENERIC_IO	0x20
#घोषणा UAC3_FUNCTION_SUBCLASS_HEADPHONE	0x21
#घोषणा UAC3_FUNCTION_SUBCLASS_SPEAKER		0x22
#घोषणा UAC3_FUNCTION_SUBCLASS_MICROPHONE	0x23
#घोषणा UAC3_FUNCTION_SUBCLASS_HEADSET		0x24
#घोषणा UAC3_FUNCTION_SUBCLASS_HEADSET_ADAPTER	0x25
#घोषणा UAC3_FUNCTION_SUBCLASS_SPEAKERPHONE	0x26

/* A.7 AUDIO FUNCTION CATEGORY CODES */
#घोषणा UAC3_FUNCTION_SUBCLASS_UNDEFINED	0x00
#घोषणा UAC3_FUNCTION_DESKTOP_SPEAKER		0x01
#घोषणा UAC3_FUNCTION_HOME_THEATER		0x02
#घोषणा UAC3_FUNCTION_MICROPHONE		0x03
#घोषणा UAC3_FUNCTION_HEADSET			0x04
#घोषणा UAC3_FUNCTION_TELEPHONE			0x05
#घोषणा UAC3_FUNCTION_CONVERTER			0x06
#घोषणा UAC3_FUNCTION_SOUND_RECORDER		0x07
#घोषणा UAC3_FUNCTION_IO_BOX			0x08
#घोषणा UAC3_FUNCTION_MUSICAL_INSTRUMENT	0x09
#घोषणा UAC3_FUNCTION_PRO_AUDIO			0x0a
#घोषणा UAC3_FUNCTION_AUDIO_VIDEO		0x0b
#घोषणा UAC3_FUNCTION_CONTROL_PANEL		0x0c
#घोषणा UAC3_FUNCTION_HEADPHONE			0x0d
#घोषणा UAC3_FUNCTION_GENERIC_SPEAKER		0x0e
#घोषणा UAC3_FUNCTION_HEADSET_ADAPTER		0x0f
#घोषणा UAC3_FUNCTION_SPEAKERPHONE		0x10
#घोषणा UAC3_FUNCTION_OTHER			0xff

/* A.8 AUDIO CLASS-SPECIFIC DESCRIPTOR TYPES */
#घोषणा UAC3_CS_UNDEFINED		0x20
#घोषणा UAC3_CS_DEVICE			0x21
#घोषणा UAC3_CS_CONFIGURATION		0x22
#घोषणा UAC3_CS_STRING			0x23
#घोषणा UAC3_CS_INTERFACE		0x24
#घोषणा UAC3_CS_ENDPOINT		0x25
#घोषणा UAC3_CS_CLUSTER			0x26

/* A.10 CLUSTER DESCRIPTOR SEGMENT TYPES */
#घोषणा UAC3_SEGMENT_UNDEFINED		0x00
#घोषणा UAC3_CLUSTER_DESCRIPTION	0x01
#घोषणा UAC3_CLUSTER_VENDOR_DEFINED	0x1F
#घोषणा UAC3_CHANNEL_INFORMATION	0x20
#घोषणा UAC3_CHANNEL_AMBISONIC		0x21
#घोषणा UAC3_CHANNEL_DESCRIPTION	0x22
#घोषणा UAC3_CHANNEL_VENDOR_DEFINED	0xFE
#घोषणा UAC3_END_SEGMENT		0xFF

/* A.11 CHANNEL PURPOSE DEFINITIONS */
#घोषणा UAC3_PURPOSE_UNDEFINED		0x00
#घोषणा UAC3_PURPOSE_GENERIC_AUDIO	0x01
#घोषणा UAC3_PURPOSE_VOICE		0x02
#घोषणा UAC3_PURPOSE_SPEECH		0x03
#घोषणा UAC3_PURPOSE_AMBIENT		0x04
#घोषणा UAC3_PURPOSE_REFERENCE		0x05
#घोषणा UAC3_PURPOSE_ULTRASONIC		0x06
#घोषणा UAC3_PURPOSE_VIBROKINETIC	0x07
#घोषणा UAC3_PURPOSE_NON_AUDIO		0xFF

/* A.12 CHANNEL RELATIONSHIP DEFINITIONS */
#घोषणा UAC3_CH_RELATIONSHIP_UNDEFINED	0x00
#घोषणा UAC3_CH_MONO			0x01
#घोषणा UAC3_CH_LEFT			0x02
#घोषणा UAC3_CH_RIGHT			0x03
#घोषणा UAC3_CH_ARRAY			0x04
#घोषणा UAC3_CH_PATTERN_X		0x20
#घोषणा UAC3_CH_PATTERN_Y		0x21
#घोषणा UAC3_CH_PATTERN_A		0x22
#घोषणा UAC3_CH_PATTERN_B		0x23
#घोषणा UAC3_CH_PATTERN_M		0x24
#घोषणा UAC3_CH_PATTERN_S		0x25
#घोषणा UAC3_CH_FRONT_LEFT		0x80
#घोषणा UAC3_CH_FRONT_RIGHT		0x81
#घोषणा UAC3_CH_FRONT_CENTER		0x82
#घोषणा UAC3_CH_FRONT_LEFT_OF_CENTER	0x83
#घोषणा UAC3_CH_FRONT_RIGHT_OF_CENTER	0x84
#घोषणा UAC3_CH_FRONT_WIDE_LEFT		0x85
#घोषणा UAC3_CH_FRONT_WIDE_RIGHT	0x86
#घोषणा UAC3_CH_SIDE_LEFT		0x87
#घोषणा UAC3_CH_SIDE_RIGHT		0x88
#घोषणा UAC3_CH_SURROUND_ARRAY_LEFT	0x89
#घोषणा UAC3_CH_SURROUND_ARRAY_RIGHT	0x8A
#घोषणा UAC3_CH_BACK_LEFT		0x8B
#घोषणा UAC3_CH_BACK_RIGHT		0x8C
#घोषणा UAC3_CH_BACK_CENTER		0x8D
#घोषणा UAC3_CH_BACK_LEFT_OF_CENTER	0x8E
#घोषणा UAC3_CH_BACK_RIGHT_OF_CENTER	0x8F
#घोषणा UAC3_CH_BACK_WIDE_LEFT		0x90
#घोषणा UAC3_CH_BACK_WIDE_RIGHT		0x91
#घोषणा UAC3_CH_TOP_CENTER		0x92
#घोषणा UAC3_CH_TOP_FRONT_LEFT		0x93
#घोषणा UAC3_CH_TOP_FRONT_RIGHT		0x94
#घोषणा UAC3_CH_TOP_FRONT_CENTER	0x95
#घोषणा UAC3_CH_TOP_FRONT_LOC		0x96
#घोषणा UAC3_CH_TOP_FRONT_ROC		0x97
#घोषणा UAC3_CH_TOP_FRONT_WIDE_LEFT	0x98
#घोषणा UAC3_CH_TOP_FRONT_WIDE_RIGHT	0x99
#घोषणा UAC3_CH_TOP_SIDE_LEFT		0x9A
#घोषणा UAC3_CH_TOP_SIDE_RIGHT		0x9B
#घोषणा UAC3_CH_TOP_SURR_ARRAY_LEFT	0x9C
#घोषणा UAC3_CH_TOP_SURR_ARRAY_RIGHT	0x9D
#घोषणा UAC3_CH_TOP_BACK_LEFT		0x9E
#घोषणा UAC3_CH_TOP_BACK_RIGHT		0x9F
#घोषणा UAC3_CH_TOP_BACK_CENTER		0xA0
#घोषणा UAC3_CH_TOP_BACK_LOC		0xA1
#घोषणा UAC3_CH_TOP_BACK_ROC		0xA2
#घोषणा UAC3_CH_TOP_BACK_WIDE_LEFT	0xA3
#घोषणा UAC3_CH_TOP_BACK_WIDE_RIGHT	0xA4
#घोषणा UAC3_CH_BOTTOM_CENTER		0xA5
#घोषणा UAC3_CH_BOTTOM_FRONT_LEFT	0xA6
#घोषणा UAC3_CH_BOTTOM_FRONT_RIGHT	0xA7
#घोषणा UAC3_CH_BOTTOM_FRONT_CENTER	0xA8
#घोषणा UAC3_CH_BOTTOM_FRONT_LOC	0xA9
#घोषणा UAC3_CH_BOTTOM_FRONT_ROC	0xAA
#घोषणा UAC3_CH_BOTTOM_FRONT_WIDE_LEFT	0xAB
#घोषणा UAC3_CH_BOTTOM_FRONT_WIDE_RIGHT	0xAC
#घोषणा UAC3_CH_BOTTOM_SIDE_LEFT	0xAD
#घोषणा UAC3_CH_BOTTOM_SIDE_RIGHT	0xAE
#घोषणा UAC3_CH_BOTTOM_SURR_ARRAY_LEFT	0xAF
#घोषणा UAC3_CH_BOTTOM_SURR_ARRAY_RIGHT	0xB0
#घोषणा UAC3_CH_BOTTOM_BACK_LEFT	0xB1
#घोषणा UAC3_CH_BOTTOM_BACK_RIGHT	0xB2
#घोषणा UAC3_CH_BOTTOM_BACK_CENTER	0xB3
#घोषणा UAC3_CH_BOTTOM_BACK_LOC		0xB4
#घोषणा UAC3_CH_BOTTOM_BACK_ROC		0xB5
#घोषणा UAC3_CH_BOTTOM_BACK_WIDE_LEFT	0xB6
#घोषणा UAC3_CH_BOTTOM_BACK_WIDE_RIGHT	0xB7
#घोषणा UAC3_CH_LOW_FREQUENCY_EFFECTS	0xB8
#घोषणा UAC3_CH_LFE_LEFT		0xB9
#घोषणा UAC3_CH_LFE_RIGHT		0xBA
#घोषणा UAC3_CH_HEADPHONE_LEFT		0xBB
#घोषणा UAC3_CH_HEADPHONE_RIGHT		0xBC

/* A.15 AUDIO CLASS-SPECIFIC AC INTERFACE DESCRIPTOR SUBTYPES */
/* see audपन.स क्रम the rest, which is identical to v1 */
#घोषणा UAC3_EXTENDED_TERMINAL		0x04
#घोषणा UAC3_MIXER_UNIT			0x05
#घोषणा UAC3_SELECTOR_UNIT		0x06
#घोषणा UAC3_FEATURE_UNIT		0x07
#घोषणा UAC3_EFFECT_UNIT		0x08
#घोषणा UAC3_PROCESSING_UNIT		0x09
#घोषणा UAC3_EXTENSION_UNIT		0x0a
#घोषणा UAC3_CLOCK_SOURCE		0x0b
#घोषणा UAC3_CLOCK_SELECTOR		0x0c
#घोषणा UAC3_CLOCK_MULTIPLIER		0x0d
#घोषणा UAC3_SAMPLE_RATE_CONVERTER	0x0e
#घोषणा UAC3_CONNECTORS			0x0f
#घोषणा UAC3_POWER_DOMAIN		0x10

/* A.20 PROCESSING UNIT PROCESS TYPES */
#घोषणा UAC3_PROCESS_UNDEFINED		0x00
#घोषणा UAC3_PROCESS_UP_DOWNMIX		0x01
#घोषणा UAC3_PROCESS_STEREO_EXTENDER	0x02
#घोषणा UAC3_PROCESS_MULTI_FUNCTION	0x03

/* A.22 AUDIO CLASS-SPECIFIC REQUEST CODES */
/* see audio-v2.h क्रम the rest, which is identical to v2 */
#घोषणा UAC3_CS_REQ_INTEN			0x04
#घोषणा UAC3_CS_REQ_STRING			0x05
#घोषणा UAC3_CS_REQ_HIGH_CAPABILITY_DESCRIPTOR	0x06

/* A.23.1 AUDIOCONTROL INTERFACE CONTROL SELECTORS */
#घोषणा UAC3_AC_CONTROL_UNDEFINED		0x00
#घोषणा UAC3_AC_ACTIVE_INTERFACE_CONTROL	0x01
#घोषणा UAC3_AC_POWER_DOMAIN_CONTROL		0x02

/* A.23.5 TERMINAL CONTROL SELECTORS */
#घोषणा UAC3_TE_UNDEFINED			0x00
#घोषणा UAC3_TE_INSERTION			0x01
#घोषणा UAC3_TE_OVERLOAD			0x02
#घोषणा UAC3_TE_UNDERFLOW			0x03
#घोषणा UAC3_TE_OVERFLOW			0x04
#घोषणा UAC3_TE_LATENCY 			0x05

/* A.23.10 PROCESSING UNITS CONTROL SELECTROS */

/* Up/Down Mixer */
#घोषणा UAC3_UD_MODE_SELECT			0x01

/* Stereo Extender */
#घोषणा UAC3_EXT_WIDTH_CONTROL			0x01


/* BADD predefined Unit/Terminal values */
#घोषणा UAC3_BADD_IT_ID1	1  /* Input Terminal ID1: bTerminalID = 1 */
#घोषणा UAC3_BADD_FU_ID2	2  /* Feature Unit ID2: bUnitID = 2 */
#घोषणा UAC3_BADD_OT_ID3	3  /* Output Terminal ID3: bTerminalID = 3 */
#घोषणा UAC3_BADD_IT_ID4	4  /* Input Terminal ID4: bTerminalID = 4 */
#घोषणा UAC3_BADD_FU_ID5	5  /* Feature Unit ID5: bUnitID = 5 */
#घोषणा UAC3_BADD_OT_ID6	6  /* Output Terminal ID6: bTerminalID = 6 */
#घोषणा UAC3_BADD_FU_ID7	7  /* Feature Unit ID7: bUnitID = 7 */
#घोषणा UAC3_BADD_MU_ID8	8  /* Mixer Unit ID8: bUnitID = 8 */
#घोषणा UAC3_BADD_CS_ID9	9  /* Clock Source Entity ID9: bClockID = 9 */
#घोषणा UAC3_BADD_PD_ID10	10 /* Power Doमुख्य ID10: bPowerDoमुख्यID = 10 */
#घोषणा UAC3_BADD_PD_ID11	11 /* Power Doमुख्य ID11: bPowerDoमुख्यID = 11 */

/* BADD wMaxPacketSize of AS endpoपूर्णांकs */
#घोषणा UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_16		0x0060
#घोषणा UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_16		0x0062
#घोषणा UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_24		0x0090
#घोषणा UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_24		0x0093
#घोषणा UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_16		0x00C0
#घोषणा UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_16		0x00C4
#घोषणा UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_24		0x0120
#घोषणा UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_24		0x0126

/* BADD sample rate is always fixed to 48kHz */
#घोषणा UAC3_BADD_SAMPLING_RATE				48000

/* BADD घातer करोमुख्यs recovery बार in 50us increments */
#घोषणा UAC3_BADD_PD_RECOVER_D1D0			0x0258	/* 30ms */
#घोषणा UAC3_BADD_PD_RECOVER_D2D0			0x1770	/* 300ms */

#पूर्ण_अगर /* __LINUX_USB_AUDIO_V3_H */
