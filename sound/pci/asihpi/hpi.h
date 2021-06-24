<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2011  AudioScience Inc. <support@audioscience.com>


*/
/** \पile hpi.h

 AudioScience Hardware Programming Interface (HPI)
 खुला API definition.

 The HPI is a low-level hardware असलtraction layer to all
 AudioScience digital audio adapters

(C) Copyright AudioScience Inc. 1998-2010
*/

#अगर_अघोषित _HPI_H_
#घोषणा _HPI_H_

#समावेश <linux/types.h>
#घोषणा HPI_BUILD_KERNEL_MODE

/******************************************************************************/
/********       HPI API DEFINITIONS                                       *****/
/******************************************************************************/

/*******************************************/
/**  Audio क्रमmat types
\ingroup stream
*/
क्रमागत HPI_FORMATS अणु
/** Used पूर्णांकernally on adapter. */
	HPI_FORMAT_MIXER_NATIVE = 0,
/** 8-bit अचिन्हित PCM. Winकरोws equivalent is WAVE_FORMAT_PCM. */
	HPI_FORMAT_PCM8_UNSIGNED = 1,
/** 16-bit चिन्हित PCM. Winकरोws equivalent is WAVE_FORMAT_PCM. */
	HPI_FORMAT_PCM16_SIGNED = 2,
/** MPEG-1 Layer-1. */
	HPI_FORMAT_MPEG_L1 = 3,
/** MPEG-1 Layer-2.

Winकरोws equivalent is WAVE_FORMAT_MPEG.

The following table shows what combinations of mode and bitrate are possible:

<table border=1 cellspacing=0 cellpadding=5>
<tr>
<td><p><b>Bitrate (kbs)</b></p>
<td><p><b>Mono</b></p>
<td><p><b>Stereo,<br>Joपूर्णांक Stereo or<br>Dual Channel</b></p>

<tr><td>32<td>X<td>_
<tr><td>40<td>_<td>_
<tr><td>48<td>X<td>_
<tr><td>56<td>X<td>_
<tr><td>64<td>X<td>X
<tr><td>80<td>X<td>_
<tr><td>96<td>X<td>X
<tr><td>112<td>X<td>X
<tr><td>128<td>X<td>X
<tr><td>160<td>X<td>X
<tr><td>192<td>X<td>X
<tr><td>224<td>_<td>X
<tr><td>256<td>-<td>X
<tr><td>320<td>-<td>X
<tr><td>384<td>_<td>X
</table>
*/
	HPI_FORMAT_MPEG_L2 = 4,
/** MPEG-1 Layer-3.
Winकरोws equivalent is WAVE_FORMAT_MPEG.

The following table shows what combinations of mode and bitrate are possible:

<table border=1 cellspacing=0 cellpadding=5>
<tr>
<td><p><b>Bitrate (kbs)</b></p>
<td><p><b>Mono<br>Stereo @ 8,<br>11.025 and<br>12kHz*</b></p>
<td><p><b>Mono<br>Stereo @ 16,<br>22.050 and<br>24kHz*</b></p>
<td><p><b>Mono<br>Stereo @ 32,<br>44.1 and<br>48kHz</b></p>

<tr><td>16<td>X<td>X<td>_
<tr><td>24<td>X<td>X<td>_
<tr><td>32<td>X<td>X<td>X
<tr><td>40<td>X<td>X<td>X
<tr><td>48<td>X<td>X<td>X
<tr><td>56<td>X<td>X<td>X
<tr><td>64<td>X<td>X<td>X
<tr><td>80<td>_<td>X<td>X
<tr><td>96<td>_<td>X<td>X
<tr><td>112<td>_<td>X<td>X
<tr><td>128<td>_<td>X<td>X
<tr><td>144<td>_<td>X<td>_
<tr><td>160<td>_<td>X<td>X
<tr><td>192<td>_<td>_<td>X
<tr><td>224<td>_<td>_<td>X
<tr><td>256<td>-<td>_<td>X
<tr><td>320<td>-<td>_<td>X
</table>
\म * Available on the ASI6000 series only
*/
	HPI_FORMAT_MPEG_L3 = 5,
/** Dolby AC-2. */
	HPI_FORMAT_DOLBY_AC2 = 6,
/** Dolbt AC-3. */
	HPI_FORMAT_DOLBY_AC3 = 7,
/** 16-bit PCM big-endian. */
	HPI_FORMAT_PCM16_BIGENDIAN = 8,
/** TAGIT-1 algorithm - hits. */
	HPI_FORMAT_AA_TAGIT1_HITS = 9,
/** TAGIT-1 algorithm - inserts. */
	HPI_FORMAT_AA_TAGIT1_INSERTS = 10,
/** 32-bit चिन्हित PCM. Winकरोws equivalent is WAVE_FORMAT_PCM.
Each sample is a 32bit word. The most signअगरicant 24 bits contain a 24-bit
sample and the least signअगरicant 8 bits are set to 0.
*/
	HPI_FORMAT_PCM32_SIGNED = 11,
/** Raw bitstream - unknown क्रमmat. */
	HPI_FORMAT_RAW_BITSTREAM = 12,
/** TAGIT-1 algorithm hits - extended. */
	HPI_FORMAT_AA_TAGIT1_HITS_EX1 = 13,
/** 32-bit PCM as an IEEE भग्न. Winकरोws equivalent is WAVE_FORMAT_IEEE_FLOAT.
Each sample is a 32bit word in IEEE754 भग्नing poपूर्णांक क्रमmat.
The range is +1.0 to -1.0, which corresponds to digital fullscale.
*/
	HPI_FORMAT_PCM32_FLOAT = 14,
/** 24-bit PCM चिन्हित. Winकरोws equivalent is WAVE_FORMAT_PCM. */
	HPI_FORMAT_PCM24_SIGNED = 15,
/** OEM क्रमmat 1 - निजी. */
	HPI_FORMAT_OEM1 = 16,
/** OEM क्रमmat 2 - निजी. */
	HPI_FORMAT_OEM2 = 17,
/** Undefined क्रमmat. */
	HPI_FORMAT_UNDEFINED = 0xffff
पूर्ण;

/*******************************************/
/** Stream States
\ingroup stream
*/
क्रमागत HPI_STREAM_STATES अणु
	/** State stopped - stream is stopped. */
	HPI_STATE_STOPPED = 1,
	/** State playing - stream is playing audio. */
	HPI_STATE_PLAYING = 2,
	/** State recording - stream is recording. */
	HPI_STATE_RECORDING = 3,
	/** State drained - playing stream ran out of data to play. */
	HPI_STATE_DRAINED = 4,
	/** State generate sine - to be implemented. */
	HPI_STATE_SINEGEN = 5,
	/** State रुको - used क्रम पूर्णांकer-card sync to mean रुकोing क्रम all
		cards to be पढ़ोy. */
	HPI_STATE_WAIT = 6
पूर्ण;
/*******************************************/
/** Source node types
\ingroup mixer
*/
क्रमागत HPI_SOURCENODES अणु
	/** This define can be used instead of 0 to indicate
	that there is no valid source node. A control that
	exists on a destination node can be searched क्रम using a source
	node value of either 0, or HPI_SOURCENODE_NONE */
	HPI_SOURCENODE_NONE = 100,
	/** Out Stream (Play) node. */
	HPI_SOURCENODE_OSTREAM = 101,
	/** Line in node - could be analog, AES/EBU or network. */
	HPI_SOURCENODE_LINEIN = 102,
	HPI_SOURCENODE_AESEBU_IN = 103,	     /**< AES/EBU input node. */
	HPI_SOURCENODE_TUNER = 104,	     /**< tuner node. */
	HPI_SOURCENODE_RF = 105,	     /**< RF input node. */
	HPI_SOURCENODE_CLOCK_SOURCE = 106,   /**< घड़ी source node. */
	HPI_SOURCENODE_RAW_BITSTREAM = 107,  /**< raw bitstream node. */
	HPI_SOURCENODE_MICROPHONE = 108,     /**< microphone node. */
	/** Cobranet input node -
	    Audio samples come from the Cobranet network and पूर्णांकo the device. */
	HPI_SOURCENODE_COBRANET = 109,
	HPI_SOURCENODE_ANALOG = 110,	     /**< analog input node. */
	HPI_SOURCENODE_ADAPTER = 111,	     /**< adapter node. */
	/** RTP stream input node - This node is a destination क्रम
	    packets of RTP audio samples from other devices. */
	HPI_SOURCENODE_RTP_DESTINATION = 112,
	HPI_SOURCENODE_INTERNAL = 113,	     /**< node पूर्णांकernal to the device. */
	HPI_SOURCENODE_AVB = 114,	     /**< AVB input stream */
	HPI_SOURCENODE_BLULINK = 115,	     /**< BLU-link input channel */
	/* !!!Update this  AND hpidebug.h अगर you add a new sourcenode type!!! */
	HPI_SOURCENODE_LAST_INDEX = 115	     /**< largest ID */
		/* AX6 max sourcenode types = 15 */
पूर्ण;

/*******************************************/
/** Destination node types
\ingroup mixer
*/
क्रमागत HPI_DESTNODES अणु
	/** This define can be used instead of 0 to indicate
	that there is no valid destination node. A control that
	exists on a source node can be searched क्रम using a destination
	node value of either 0, or HPI_DESTNODE_NONE */
	HPI_DESTNODE_NONE = 200,
	/** In Stream (Record) node. */
	HPI_DESTNODE_ISTREAM = 201,
	HPI_DESTNODE_LINEOUT = 202,	     /**< line out node. */
	HPI_DESTNODE_AESEBU_OUT = 203,	     /**< AES/EBU output node. */
	HPI_DESTNODE_RF = 204,		     /**< RF output node. */
	HPI_DESTNODE_SPEAKER = 205,	     /**< speaker output node. */
	/** Cobranet output node -
	    Audio samples from the device are sent out on the Cobranet network.*/
	HPI_DESTNODE_COBRANET = 206,
	HPI_DESTNODE_ANALOG = 207,	     /**< analog output node. */
	/** RTP stream output node - This node is a source क्रम
	    packets of RTP audio samples that are sent to other devices. */
	HPI_DESTNODE_RTP_SOURCE = 208,
	HPI_DESTNODE_AVB = 209,		     /**< AVB output stream */
	HPI_DESTNODE_INTERNAL = 210,	     /**< node पूर्णांकernal to the device. */
	HPI_DESTNODE_BLULINK = 211,	     /**< BLU-link output channel. */
	/* !!!Update this AND hpidebug.h अगर you add a new destnode type!!! */
	HPI_DESTNODE_LAST_INDEX = 211	     /**< largest ID */
		/* AX6 max destnode types = 15 */
पूर्ण;

/*******************************************/
/** Mixer control types
\ingroup mixer
*/
क्रमागत HPI_CONTROLS अणु
	HPI_CONTROL_GENERIC = 0,	/**< generic control. */
	HPI_CONTROL_CONNECTION = 1, /**< A connection between nodes. */
	HPI_CONTROL_VOLUME = 2,	      /**< volume control - works in dB_fs. */
	HPI_CONTROL_METER = 3,	/**< peak meter control. */
	HPI_CONTROL_MUTE = 4,	/*mute control - not used at present. */
	HPI_CONTROL_MULTIPLEXER = 5,	/**< multiplexer control. */

	HPI_CONTROL_AESEBU_TRANSMITTER = 6, /**< AES/EBU transmitter control */
	HPI_CONTROL_AESEBUTX = 6,	/* HPI_CONTROL_AESEBU_TRANSMITTER */

	HPI_CONTROL_AESEBU_RECEIVER = 7, /**< AES/EBU receiver control. */
	HPI_CONTROL_AESEBURX = 7,	/* HPI_CONTROL_AESEBU_RECEIVER */

	HPI_CONTROL_LEVEL = 8, /**< level/trim control - works in d_bu. */
	HPI_CONTROL_TUNER = 9,	/**< tuner control. */
/*      HPI_CONTROL_ONOFFSWITCH =       10 */
	HPI_CONTROL_VOX = 11,	/**< vox control. */
/*      HPI_CONTROL_AES18_TRANSMITTER = 12 */
/*      HPI_CONTROL_AES18_RECEIVER = 13 */
/*      HPI_CONTROL_AES18_BLOCKGENERATOR  = 14 */
	HPI_CONTROL_CHANNEL_MODE = 15,	/**< channel mode control. */

	HPI_CONTROL_BITSTREAM = 16,	/**< bitstream control. */
	HPI_CONTROL_SAMPLECLOCK = 17,	/**< sample घड़ी control. */
	HPI_CONTROL_MICROPHONE = 18,	/**< microphone control. */
	HPI_CONTROL_PARAMETRIC_EQ = 19,	/**< parametric EQ control. */
	HPI_CONTROL_EQUALIZER = 19,	/*HPI_CONTROL_PARAMETRIC_EQ */

	HPI_CONTROL_COMPANDER = 20,	/**< compander control. */
	HPI_CONTROL_COBRANET = 21,	/**< cobranet control. */
	HPI_CONTROL_TONEDETECTOR = 22,	/**< tone detector control. */
	HPI_CONTROL_SILENCEDETECTOR = 23,	/**< silence detector control. */
	HPI_CONTROL_PAD = 24,	/**< tuner PAD control. */
	HPI_CONTROL_SRC = 25,	/**< samplerate converter control. */
	HPI_CONTROL_UNIVERSAL = 26,	/**< universal control. */

/*  !!! Update this AND hpidebug.h अगर you add a new control type!!!*/
	HPI_CONTROL_LAST_INDEX = 26 /**<highest control type ID */
/* WARNING types 256 or greater impact bit packing in all AX6 DSP code */
पूर्ण;

/*******************************************/
/** Adapter properties
These are used in HPI_AdapterSetProperty() and HPI_AdapterGetProperty()
\ingroup adapter
*/
क्रमागत HPI_ADAPTER_PROPERTIES अणु
/** \पूर्णांकernal Used in dwProperty field of HPI_AdapterSetProperty() and
HPI_AdapterGetProperty(). This errata applies to all ASI6000 cards with both
analog and digital outमाला_दो. The CS4224 A/D+D/A has a one sample delay between
left and right channels on both its input (ADC) and output (DAC).
More details are available in Cirrus Logic errata ER284B2.
PDF available from www.cirrus.com, released by Cirrus in 2001.
*/
	HPI_ADAPTER_PROPERTY_ERRATA_1 = 1,

/** Adapter grouping property
Indicates whether the adapter supports the grouping API (क्रम ASIO and SSX2)
*/
	HPI_ADAPTER_PROPERTY_GROUPING = 2,

/** Driver SSX2 property
Tells the kernel driver to turn on SSX2 stream mapping.
This feature is not used by the DSP. In fact the call is completely processed
by the driver and is not passed on to the DSP at all.
*/
	HPI_ADAPTER_PROPERTY_ENABLE_SSX2 = 3,

/** Adapter SSX2 property
Indicates the state of the adapter's SSX2 setting. This setting is stored in
non-अस्थिर memory on the adapter. A typical call sequence would be to use
HPI_ADAPTER_PROPERTY_SSX2_SETTING to set SSX2 on the adapter and then to reload
the driver. The driver would query HPI_ADAPTER_PROPERTY_SSX2_SETTING during
startup and अगर SSX2 is set, it would then call HPI_ADAPTER_PROPERTY_ENABLE_SSX2
to enable SSX2 stream mapping within the kernel level of the driver.
*/
	HPI_ADAPTER_PROPERTY_SSX2_SETTING = 4,

/** Enables/disables PCI(e) IRQ.
A setting of 0 indicates that no पूर्णांकerrupts are being generated. A DSP boot
this property is set to 0. Setting to a non-zero value specअगरies the number
of frames of audio that should be processed between पूर्णांकerrupts. This property
should be set to multiple of the mixer पूर्णांकerval as पढ़ो back from the
HPI_ADAPTER_PROPERTY_INTERVAL property.
*/
	HPI_ADAPTER_PROPERTY_IRQ_RATE = 5,

/** Base number क्रम पढ़ोonly properties */
	HPI_ADAPTER_PROPERTY_READONLYBASE = 256,

/** Reaकरोnly adapter latency property.
This property वापसs in the input and output latency in samples.
Property 1 is the estimated input latency
in samples, जबतक Property 2 is that output latency in  samples.
*/
	HPI_ADAPTER_PROPERTY_LATENCY = 256,

/** Reaकरोnly adapter granularity property.
The granulariy is the smallest size chunk of stereo samples that is processed by
the adapter.
This property वापसs the record granularity in samples in Property 1.
Property 2 वापसs the play granularity.
*/
	HPI_ADAPTER_PROPERTY_GRANULARITY = 257,

/** Reaकरोnly adapter number of current channels property.
Property 1 is the number of record channels per record device.
Property 2 is the number of play channels per playback device.*/
	HPI_ADAPTER_PROPERTY_CURCHANNELS = 258,

/** Reaकरोnly adapter software version.
The SOFTWARE_VERSION property वापसs the version of the software running
on the adapter as Major.Minor.Release.
Property 1 contains Major in bits 15..8 and Minor in bits 7..0.
Property 2 contains Release in bits 7..0. */
	HPI_ADAPTER_PROPERTY_SOFTWARE_VERSION = 259,

/** Reaकरोnly adapter MAC address MSBs.
The MAC_ADDRESS_MSB property वापसs
the most signअगरicant 32 bits of the MAC address.
Property 1 contains bits 47..32 of the MAC address.
Property 2 contains bits 31..16 of the MAC address. */
	HPI_ADAPTER_PROPERTY_MAC_ADDRESS_MSB = 260,

/** Reaकरोnly adapter MAC address LSBs
The MAC_ADDRESS_LSB property वापसs
the least signअगरicant 16 bits of the MAC address.
Property 1 contains bits 15..0 of the MAC address. */
	HPI_ADAPTER_PROPERTY_MAC_ADDRESS_LSB = 261,

/** Reaकरोnly extended adapter type number
The EXTENDED_ADAPTER_TYPE property वापसs the 4 digits of an extended
adapter type, i.e ASI8920-0022, 0022 is the extended type.
The digits are वापसed as ASCII अक्षरacters rather than the hex digits that
are वापसed क्रम the मुख्य type
Property 1 वापसs the 1st two (left most) digits, i.e "00"
in the example above, the upper byte being the left most digit.
Property 2 वापसs the 2nd two digits, i.e "22" in the example above*/
	HPI_ADAPTER_PROPERTY_EXTENDED_ADAPTER_TYPE = 262,

/** Reaकरोnly debug log buffer inक्रमmation */
	HPI_ADAPTER_PROPERTY_LOGTABLEN = 263,
	HPI_ADAPTER_PROPERTY_LOGTABBEG = 264,

/** Reaकरोnly adapter IP address
For 192.168.1.101
Property 1 वापसs the 1st two (left most) digits, i.e 192*256 + 168
in the example above, the upper byte being the left most digit.
Property 2 वापसs the 2nd two digits, i.e 1*256 + 101 in the example above, */
	HPI_ADAPTER_PROPERTY_IP_ADDRESS = 265,

/** Reaकरोnly adapter buffer processed count. Returns a buffer processed count
that is incremented every समय all buffers क्रम all streams are updated. This
is useful क्रम checking completion of all stream operations across the adapter
when using grouped streams.
*/
	HPI_ADAPTER_PROPERTY_BUFFER_UPDATE_COUNT = 266,

/** Reaकरोnly mixer and stream पूर्णांकervals

These पूर्णांकervals are  measured in mixer frames.
To convert to समय, भागide  by the adapter samplerate.

The mixer पूर्णांकerval is the number of frames processed in one mixer iteration.
The stream update पूर्णांकerval is the पूर्णांकerval at which streams check क्रम and
process data, and BBM host buffer counters are updated.

Property 1 is the mixer पूर्णांकerval in mixer frames.
Property 2 is the stream update पूर्णांकerval in mixer frames.
*/
	HPI_ADAPTER_PROPERTY_INTERVAL = 267,
/** Adapter capabilities 1
Property 1 - adapter can करो multichannel (SSX1)
Property 2 - adapter can करो stream grouping (supports SSX2)
*/
	HPI_ADAPTER_PROPERTY_CAPS1 = 268,
/** Adapter capabilities 2
Property 1 - adapter can करो samplerate conversion (MRX)
Property 2 - adapter can करो बारtretch (TSX)
*/
	HPI_ADAPTER_PROPERTY_CAPS2 = 269,

/** Reaकरोnly adapter sync header connection count.
*/
	HPI_ADAPTER_PROPERTY_SYNC_HEADER_CONNECTIONS = 270,
/** Reaकरोnly supports SSX2 property.
Indicates the adapter supports SSX2 in some mode setting. The
वापस value is true (1) or false (0). If the current adapter
mode is MONO SSX2 is disabled, even though this property will
वापस true.
*/
	HPI_ADAPTER_PROPERTY_SUPPORTS_SSX2 = 271,
/** Reaकरोnly supports PCI(e) IRQ.
Indicates that the adapter in it's current mode supports पूर्णांकerrupts
across the host bus. Note, this करोes not imply that पूर्णांकerrupts are
enabled. Instead it indicates that they can be enabled.
*/
	HPI_ADAPTER_PROPERTY_SUPPORTS_IRQ = 272,
/** Reaकरोnly supports firmware updating.
Indicates that the adapter implements an पूर्णांकerface to update firmware
on the adapter.
*/
	HPI_ADAPTER_PROPERTY_SUPPORTS_FW_UPDATE = 273,
/** Reaकरोnly Firmware IDs
Identअगरiy firmware independent of inभागidual adapter type.
May be used as a filter क्रम firmware update images.
Property 1 = Bootloader ID
Property 2 = Main program ID
*/
	HPI_ADAPTER_PROPERTY_FIRMWARE_ID = 274
पूर्ण;

/** Adapter mode commands

Used in wQueryOrSet parameter of HPI_AdapterSetModeEx().
\ingroup adapter
*/
क्रमागत HPI_ADAPTER_MODE_CMDS अणु
	/** Set the mode to the given parameter */
	HPI_ADAPTER_MODE_SET = 0,
	/** Return 0 or error depending whether mode is valid,
	but करोn't set the mode */
	HPI_ADAPTER_MODE_QUERY = 1
पूर्ण;

/** Adapter Modes
 These are used by HPI_AdapterSetModeEx()

\warning - more than 16 possible modes अवरोधs
a biपंचांगask in the Winकरोws WAVE DLL
\ingroup adapter
*/
क्रमागत HPI_ADAPTER_MODES अणु
/** 4 outstream mode.
- ASI6114: 1 instream
- ASI6044: 4 instreams
- ASI6012: 1 instream
- ASI6102: no instreams
- ASI6022, ASI6122: 2 instreams
- ASI5111, ASI5101: 2 instreams
- ASI652x, ASI662x: 2 instreams
- ASI654x, ASI664x: 4 instreams
*/
	HPI_ADAPTER_MODE_4OSTREAM = 1,

/** 6 outstream mode.
- ASI6012: 1 instream,
- ASI6022, ASI6122: 2 instreams
- ASI652x, ASI662x: 4 instreams
*/
	HPI_ADAPTER_MODE_6OSTREAM = 2,

/** 8 outstream mode.
- ASI6114: 8 instreams
- ASI6118: 8 instreams
- ASI6585: 8 instreams
*/
	HPI_ADAPTER_MODE_8OSTREAM = 3,

/** 16 outstream mode.
- ASI6416 16 instreams
- ASI6518, ASI6618 16 instreams
- ASI6118 16 mono out and in streams
*/
	HPI_ADAPTER_MODE_16OSTREAM = 4,

/** one outstream mode.
- ASI5111 1 outstream, 1 instream
*/
	HPI_ADAPTER_MODE_1OSTREAM = 5,

/** ASI504X mode 1. 12 outstream, 4 instream 0 to 48kHz sample rates
	(see ASI504X datasheet क्रम more info).
*/
	HPI_ADAPTER_MODE_1 = 6,

/** ASI504X mode 2. 4 outstreams, 4 instreams at 0 to 192kHz sample rates
	(see ASI504X datasheet क्रम more info).
*/
	HPI_ADAPTER_MODE_2 = 7,

/** ASI504X mode 3. 4 outstreams, 4 instreams at 0 to 192kHz sample rates
	(see ASI504X datasheet क्रम more info).
*/
	HPI_ADAPTER_MODE_3 = 8,

/** ASI504X multichannel mode.
	2 outstreams -> 4 line outs = 1 to 8 channel streams),
	4 lineins -> 1 instream (1 to 8 channel streams) at 0-48kHz.
	For more info see the SSX Specअगरication.
*/
	HPI_ADAPTER_MODE_MULTICHANNEL = 9,

/** 12 outstream mode.
- ASI6514, ASI6614: 2 instreams
- ASI6540,ASI6544: 8 instreams
- ASI6640,ASI6644: 8 instreams
*/
	HPI_ADAPTER_MODE_12OSTREAM = 10,

/** 9 outstream mode.
- ASI6044: 8 instreams
*/
	HPI_ADAPTER_MODE_9OSTREAM = 11,

/** mono mode.
- ASI6416: 16 outstreams/instreams
- ASI5402: 2 outstreams/instreams
*/
	HPI_ADAPTER_MODE_MONO = 12,

/** Low latency mode.
- ASI6416/ASI6316: 1 16 channel outstream and instream
*/
	HPI_ADAPTER_MODE_LOW_LATENCY = 13
पूर्ण;

/* Note, adapters can have more than one capability -
encoding as bitfield is recommended. */
#घोषणा HPI_CAPABILITY_NONE             (0)
#घोषणा HPI_CAPABILITY_MPEG_LAYER3      (1)

/* Set this equal to maximum capability index,
Must not be greater than 32 - see axnvdef.h */
#घोषणा HPI_CAPABILITY_MAX                      1
/* #घोषणा HPI_CAPABILITY_AAC              2 */

/******************************************* STREAM ATTRIBUTES ****/

/** MPEG Ancillary Data modes

The mode क्रम the ancillary data insertion or extraction to operate in.
\ingroup stream
*/
क्रमागत HPI_MPEG_ANC_MODES अणु
	/** the MPEG frames have energy inक्रमmation stored in them (5 bytes per stereo frame, 3 per mono) */
	HPI_MPEG_ANC_HASENERGY = 0,
	/** the entire ancillary data field is taken up by data from the Anc data buffer
	On encode, the encoder will insert the energy bytes beक्रमe filling the reमुख्यder
	of the ancillary data space with data from the ancillary data buffer.
	*/
	HPI_MPEG_ANC_RAW = 1
पूर्ण;

/** Ancillary Data Alignment
\ingroup instream
*/
क्रमागत HPI_ISTREAM_MPEG_ANC_ALIGNS अणु
	/** data is packed against the end of data, then padded to the end of frame */
	HPI_MPEG_ANC_ALIGN_LEFT = 0,
	/** data is packed against the end of the frame */
	HPI_MPEG_ANC_ALIGN_RIGHT = 1
पूर्ण;

/** MPEG modes
MPEG modes - can be used optionally क्रम HPI_FormatCreate()
parameter dwAttributes.

Using any mode setting other than HPI_MPEG_MODE_DEFAULT
with single channel क्रमmat will वापस an error.
\ingroup stream
*/
क्रमागत HPI_MPEG_MODES अणु
/** Causes the MPEG-1 Layer II bitstream to be recorded
in single_channel mode when the number of channels is 1 and in stereo when the
number of channels is 2. */
	HPI_MPEG_MODE_DEFAULT = 0,
	/** Standard stereo without joपूर्णांक-stereo compression */
	HPI_MPEG_MODE_STEREO = 1,
	/** Joपूर्णांक stereo  */
	HPI_MPEG_MODE_JOINTSTEREO = 2,
	/** Left and Right channels are completely independent */
	HPI_MPEG_MODE_DUALCHANNEL = 3
पूर्ण;
/******************************************* MIXER ATTRIBUTES ****/

/* \defgroup mixer_flags Mixer flags क्रम HPI_MIXER_GET_CONTROL_MULTIPLE_VALUES
अणु
*/
#घोषणा HPI_MIXER_GET_CONTROL_MULTIPLE_CHANGED  (0)
#घोषणा HPI_MIXER_GET_CONTROL_MULTIPLE_RESET    (1)
/*पूर्ण*/

/** Commands used by HPI_MixerStore()
\ingroup mixer
*/
क्रमागत HPI_MIXER_STORE_COMMAND अणु
/** Save all mixer control settings. */
	HPI_MIXER_STORE_SAVE = 1,
/** Restore all controls from saved. */
	HPI_MIXER_STORE_RESTORE = 2,
/** Delete saved control settings. */
	HPI_MIXER_STORE_DELETE = 3,
/** Enable स्वतः storage of some control settings. */
	HPI_MIXER_STORE_ENABLE = 4,
/** Disable स्वतः storage of some control settings. */
	HPI_MIXER_STORE_DISABLE = 5,
/** Unimplemented - save the attributes of a single control. */
	HPI_MIXER_STORE_SAVE_SINGLE = 6
पूर्ण;

/****************************/
/* CONTROL ATTRIBUTE VALUES */
/****************************/

/** Used by mixer plugin enable functions

E.g. HPI_ParametricEq_SetState()
\ingroup mixer
*/
क्रमागत HPI_SWITCH_STATES अणु
	HPI_SWITCH_OFF = 0,	/**< turn the mixer plugin on. */
	HPI_SWITCH_ON = 1	/**< turn the mixer plugin off. */
पूर्ण;

/* Volume control special gain values */

/** volumes units are 100ths of a dB
\ingroup volume
*/
#घोषणा HPI_UNITS_PER_dB                100
/** turns volume control OFF or MUTE
\ingroup volume
*/
#घोषणा HPI_GAIN_OFF                    (-100 * HPI_UNITS_PER_dB)

/** channel mask specअगरying all channels
\ingroup volume
*/
#घोषणा HPI_BITMASK_ALL_CHANNELS        (0xFFFFFFFF)

/** value वापसed क्रम no संकेत
\ingroup meter
*/
#घोषणा HPI_METER_MINIMUM               (-150 * HPI_UNITS_PER_dB)

/** स्वतःfade profiles
\ingroup volume
*/
क्रमागत HPI_VOLUME_AUTOFADES अणु
/** log fade - dB attenuation changes linearly over समय */
	HPI_VOLUME_AUTOFADE_LOG = 2,
/** linear fade - amplitude changes linearly */
	HPI_VOLUME_AUTOFADE_LINEAR = 3
पूर्ण;

/** The physical encoding क्रमmat of the AESEBU I/O.

Used in HPI_Aesebu_Transmitter_SetFormat(), HPI_Aesebu_Receiver_SetFormat()
aदीर्घ with related Get and Query functions
\ingroup aestx
*/
क्रमागत HPI_AESEBU_FORMATS अणु
/** AES/EBU physical क्रमmat - AES/EBU balanced "professional"  */
	HPI_AESEBU_FORMAT_AESEBU = 1,
/** AES/EBU physical क्रमmat - S/PDIF unbalanced "consumer"      */
	HPI_AESEBU_FORMAT_SPDIF = 2
पूर्ण;

/** AES/EBU error status bits

Returned by HPI_Aesebu_Receiver_GetErrorStatus()
\ingroup aesrx
*/
क्रमागत HPI_AESEBU_ERRORS अणु
/**  bit0: 1 when PLL is not locked */
	HPI_AESEBU_ERROR_NOT_LOCKED = 0x01,
/**  bit1: 1 when संकेत quality is poor */
	HPI_AESEBU_ERROR_POOR_QUALITY = 0x02,
/** bit2: 1 when there is a parity error */
	HPI_AESEBU_ERROR_PARITY_ERROR = 0x04,
/**  bit3: 1 when there is a bi-phase coding violation */
	HPI_AESEBU_ERROR_BIPHASE_VIOLATION = 0x08,
/**  bit4: 1 when the validity bit is high */
	HPI_AESEBU_ERROR_VALIDITY = 0x10,
/**  bit5: 1 when the CRC error bit is high */
	HPI_AESEBU_ERROR_CRC = 0x20
पूर्ण;

/** \चddtogroup pad
\अणु
*/
/** The text string containing the station/channel combination. */
#घोषणा HPI_PAD_CHANNEL_NAME_LEN        16
/** The text string containing the artist. */
#घोषणा HPI_PAD_ARTIST_LEN              64
/** The text string containing the title. */
#घोषणा HPI_PAD_TITLE_LEN               64
/** The text string containing the comment. */
#घोषणा HPI_PAD_COMMENT_LEN             256
/** The PTY when the tuner has not received any PTY. */
#घोषणा HPI_PAD_PROGRAM_TYPE_INVALID    0xffff
/** \पूर्ण */

/** Data types क्रम PTY string translation.
\ingroup rds
*/
क्रमागत eHPI_RDS_type अणु
	HPI_RDS_DATATYPE_RDS = 0,	/**< RDS bitstream.*/
	HPI_RDS_DATATYPE_RBDS = 1	/**< RBDS bitstream.*/
पूर्ण;

/** Tuner bands

Used क्रम HPI_Tuner_SetBand(),HPI_Tuner_GetBand()
\ingroup tuner
*/
क्रमागत HPI_TUNER_BAND अणु
	HPI_TUNER_BAND_AM = 1,	 /**< AM band */
	HPI_TUNER_BAND_FM = 2,	 /**< FM band (mono) */
	HPI_TUNER_BAND_TV_NTSC_M = 3,	 /**< NTSC-M TV band*/
	HPI_TUNER_BAND_TV = 3,	/* use TV_NTSC_M */
	HPI_TUNER_BAND_FM_STEREO = 4,	 /**< FM band (stereo) */
	HPI_TUNER_BAND_AUX = 5,	 /**< auxiliary input */
	HPI_TUNER_BAND_TV_PAL_BG = 6,	 /**< PAL-B/G TV band*/
	HPI_TUNER_BAND_TV_PAL_I = 7,	 /**< PAL-I TV band*/
	HPI_TUNER_BAND_TV_PAL_DK = 8,	 /**< PAL-D/K TV band*/
	HPI_TUNER_BAND_TV_SECAM_L = 9,	 /**< SECAM-L TV band*/
	HPI_TUNER_BAND_DAB = 10,
	HPI_TUNER_BAND_LAST = 10 /**< the index of the last tuner band. */
पूर्ण;

/** Tuner mode attributes

Used by HPI_Tuner_SetMode(), HPI_Tuner_GetMode()
\ingroup tuner

*/
क्रमागत HPI_TUNER_MODES अणु
	HPI_TUNER_MODE_RSS = 1,	/**< control  RSS */
	HPI_TUNER_MODE_RDS = 2	/**< control  RBDS/RDS */
पूर्ण;

/** Tuner mode attribute values

Used by HPI_Tuner_SetMode(), HPI_Tuner_GetMode()
\ingroup tuner
*/
क्रमागत HPI_TUNER_MODE_VALUES अणु
/* RSS attribute values */
	HPI_TUNER_MODE_RSS_DISABLE = 0,	/**< RSS disable */
	HPI_TUNER_MODE_RSS_ENABLE = 1,	/**< RSS enable */

/* RDS mode attributes */
	HPI_TUNER_MODE_RDS_DISABLE = 0,	/**< RDS - disabled */
	HPI_TUNER_MODE_RDS_RDS = 1,  /**< RDS - RDS mode */
	HPI_TUNER_MODE_RDS_RBDS = 2 /**<  RDS - RBDS mode */
पूर्ण;

/** Tuner Status Bits

These bitfield values are वापसed by a call to HPI_Tuner_GetStatus().
Multiple fields are वापसed from a single call.
\ingroup tuner
*/
क्रमागत HPI_TUNER_STATUS_BITS अणु
	HPI_TUNER_VIDEO_COLOR_PRESENT = 0x0001,	/**< video color is present. */
	HPI_TUNER_VIDEO_IS_60HZ = 0x0020, /**< 60 hz video detected. */
	HPI_TUNER_VIDEO_HORZ_SYNC_MISSING = 0x0040, /**< video HSYNC is missing. */
	HPI_TUNER_VIDEO_STATUS_VALID = 0x0100, /**< video status is valid. */
	HPI_TUNER_DIGITAL = 0x0200, /**< tuner reports digital programming. */
	HPI_TUNER_MULTIPROGRAM = 0x0400, /**< tuner reports multiple programs. */
	HPI_TUNER_PLL_LOCKED = 0x1000, /**< the tuner's PLL is locked. */
	HPI_TUNER_FM_STEREO = 0x2000 /**< tuner reports back FM stereo. */
पूर्ण;

/** Channel Modes
Used क्रम HPI_ChannelModeSet/Get()
\ingroup channelmode
*/
क्रमागत HPI_CHANNEL_MODES अणु
/** Left channel out = left channel in, Right channel out = right channel in. */
	HPI_CHANNEL_MODE_NORMAL = 1,
/** Left channel out = right channel in, Right channel out = left channel in. */
	HPI_CHANNEL_MODE_SWAP = 2,
/** Left channel out = left channel in, Right channel out = left channel in. */
	HPI_CHANNEL_MODE_LEFT_TO_STEREO = 3,
/** Left channel out = right channel in, Right channel out = right channel in.*/
	HPI_CHANNEL_MODE_RIGHT_TO_STEREO = 4,
/** Left channel out = (left channel in + right channel in)/2,
    Right channel out = mute. */
	HPI_CHANNEL_MODE_STEREO_TO_LEFT = 5,
/** Left channel out = mute,
    Right channel out = (right channel in + left channel in)/2. */
	HPI_CHANNEL_MODE_STEREO_TO_RIGHT = 6,
	HPI_CHANNEL_MODE_LAST = 6
पूर्ण;

/** SampleClock source values
\ingroup sampleघड़ी
*/
क्रमागत HPI_SAMPLECLOCK_SOURCES अणु
/** The sampleघड़ी output is derived from its local samplerate generator.
    The local samplerate may be set using HPI_SampleClock_SetLocalRate(). */
	HPI_SAMPLECLOCK_SOURCE_LOCAL = 1,
/** The adapter is घड़ीed from a dedicated AES/EBU SampleClock input.*/
	HPI_SAMPLECLOCK_SOURCE_AESEBU_SYNC = 2,
/** From बाह्यal wordघड़ी connector */
	HPI_SAMPLECLOCK_SOURCE_WORD = 3,
/** Board-to-board header */
	HPI_SAMPLECLOCK_SOURCE_WORD_HEADER = 4,
/** FUTURE - SMPTE घड़ी. */
	HPI_SAMPLECLOCK_SOURCE_SMPTE = 5,
/** One of the aesebu inमाला_दो */
	HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT = 6,
/** From a network पूर्णांकerface e.g. Cobranet or Livewire at either 48 or 96kHz */
	HPI_SAMPLECLOCK_SOURCE_NETWORK = 8,
/** From previous adjacent module (ASI2416 only)*/
	HPI_SAMPLECLOCK_SOURCE_PREV_MODULE = 10,
/** Blu link sample घड़ी*/
	HPI_SAMPLECLOCK_SOURCE_BLULINK = 11,
/*! Update this अगर you add a new घड़ी source.*/
	HPI_SAMPLECLOCK_SOURCE_LAST = 11
पूर्ण;

/** Equalizer filter types. Used by HPI_ParametricEq_SetBand()
\ingroup parmeq
*/
क्रमागत HPI_FILTER_TYPE अणु
	HPI_FILTER_TYPE_BYPASS = 0,	/**< filter is turned off */

	HPI_FILTER_TYPE_LOWSHELF = 1,	/**< EQ low shelf */
	HPI_FILTER_TYPE_HIGHSHELF = 2,	/**< EQ high shelf */
	HPI_FILTER_TYPE_EQ_BAND = 3,	/**< EQ gain */

	HPI_FILTER_TYPE_LOWPASS = 4,	/**< standard low pass */
	HPI_FILTER_TYPE_HIGHPASS = 5,	/**< standard high pass */
	HPI_FILTER_TYPE_BANDPASS = 6,	/**< standard band pass */
	HPI_FILTER_TYPE_BANDSTOP = 7	/**< standard band stop/notch */
पूर्ण;

/** Async Event sources
\ingroup async
*/
क्रमागत ASYNC_EVENT_SOURCES अणु
	HPI_ASYNC_EVENT_GPIO = 1,	/**< GPIO event. */
	HPI_ASYNC_EVENT_SILENCE = 2,	/**< silence event detected. */
	HPI_ASYNC_EVENT_TONE = 3	/**< tone event detected. */
पूर्ण;
/*******************************************/
/** HPI Error codes

Almost all HPI functions वापस an error code
A वापस value of zero means there was no error.
Otherwise one of these error codes is वापसed.
Error codes can be converted to a descriptive string using HPI_GetErrorText()

\नote When a new error code is added HPI_GetErrorText() MUST be updated.
\नote Codes 1-100 are reserved क्रम driver use
\ingroup utility
*/
क्रमागत HPI_ERROR_CODES अणु
	/** Message type करोes not exist. */
	HPI_ERROR_INVALID_TYPE = 100,
	/** Object type करोes not exist. */
	HPI_ERROR_INVALID_OBJ = 101,
	/** Function करोes not exist. */
	HPI_ERROR_INVALID_FUNC = 102,
	/** The specअगरied object करोes not exist. */
	HPI_ERROR_INVALID_OBJ_INDEX = 103,
	/** Trying to access an object that has not been खोलोed yet. */
	HPI_ERROR_OBJ_NOT_OPEN = 104,
	/** Trying to खोलो an alपढ़ोy खोलो object. */
	HPI_ERROR_OBJ_ALREADY_OPEN = 105,
	/** PCI, ISA resource not valid. */
	HPI_ERROR_INVALID_RESOURCE = 106,
	/* HPI_ERROR_SUBSYSFINDADAPTERS_GETINFO= 107 */
	/** Default response was never updated with actual error code. */
	HPI_ERROR_INVALID_RESPONSE = 108,
	/** wSize field of response was not updated,
	indicating that the message was not processed. */
	HPI_ERROR_PROCESSING_MESSAGE = 109,
	/** The network did not respond in a समयly manner. */
	HPI_ERROR_NETWORK_TIMEOUT = 110,
	/* An HPI handle is invalid (uninitialised?). */
	HPI_ERROR_INVALID_HANDLE = 111,
	/** A function or attribute has not been implemented yet. */
	HPI_ERROR_UNIMPLEMENTED = 112,
	/** There are too many clients attempting
	    to access a network resource. */
	HPI_ERROR_NETWORK_TOO_MANY_CLIENTS = 113,
	/** Response buffer passed to HPI_Message
	    was smaller than वापसed response.
	    wSpecअगरicError field of hpi response contains the required size.
	*/
	HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL = 114,
	/** The वापसed response did not match the sent message */
	HPI_ERROR_RESPONSE_MISMATCH = 115,
	/** A control setting that should have been cached was not. */
	HPI_ERROR_CONTROL_CACHING = 116,
	/** A message buffer in the path to the adapter was smaller
	    than the message size.
	    wSpecअगरicError field of hpi response contains the actual size.
	*/
	HPI_ERROR_MESSAGE_BUFFER_TOO_SMALL = 117,

	/* HPI_ERROR_TOO_MANY_ADAPTERS= 200 */
	/** Bad adpater. */
	HPI_ERROR_BAD_ADAPTER = 201,
	/** Adapter number out of range or not set properly. */
	HPI_ERROR_BAD_ADAPTER_NUMBER = 202,
	/** 2 adapters with the same adapter number. */
	HPI_ERROR_DUPLICATE_ADAPTER_NUMBER = 203,
	/** DSP code failed to bootload. Usually a DSP memory test failure. */
	HPI_ERROR_DSP_BOOTLOAD = 204,
	/** Couldn't find or खोलो the DSP code file. */
	HPI_ERROR_DSP_खाता_NOT_FOUND = 206,
	/** Internal DSP hardware error. */
	HPI_ERROR_DSP_HARDWARE = 207,
	/** Could not allocate memory */
	HPI_ERROR_MEMORY_ALLOC = 208,
	/** Failed to correctly load/config PLD. (unused) */
	HPI_ERROR_PLD_LOAD = 209,
	/** Unexpected end of file, block length too big etc. */
	HPI_ERROR_DSP_खाता_FORMAT = 210,

	/** Found but could not खोलो DSP code file. */
	HPI_ERROR_DSP_खाता_ACCESS_DENIED = 211,
	/** First DSP code section header not found in DSP file. */
	HPI_ERROR_DSP_खाता_NO_HEADER = 212,
	/* HPI_ERROR_DSP_खाता_READ_ERROR= 213, */
	/** DSP code क्रम adapter family not found. */
	HPI_ERROR_DSP_SECTION_NOT_FOUND = 214,
	/** Other OS specअगरic error खोलोing DSP file. */
	HPI_ERROR_DSP_खाता_OTHER_ERROR = 215,
	/** Sharing violation खोलोing DSP code file. */
	HPI_ERROR_DSP_खाता_SHARING_VIOLATION = 216,
	/** DSP code section header had size == 0. */
	HPI_ERROR_DSP_खाता_शून्य_HEADER = 217,

	/* HPI_ERROR_FLASH = 220, */

	/** Flash has bad checksum */
	HPI_ERROR_BAD_CHECKSUM = 221,
	HPI_ERROR_BAD_SEQUENCE = 222,
	HPI_ERROR_FLASH_ERASE = 223,
	HPI_ERROR_FLASH_PROGRAM = 224,
	HPI_ERROR_FLASH_VERIFY = 225,
	HPI_ERROR_FLASH_TYPE = 226,
	HPI_ERROR_FLASH_START = 227,
	HPI_ERROR_FLASH_READ = 228,
	HPI_ERROR_FLASH_READ_NO_खाता = 229,
	HPI_ERROR_FLASH_SIZE = 230,

	/** Reserved क्रम OEMs. */
	HPI_ERROR_RESERVED_1 = 290,

	/* HPI_ERROR_INVALID_STREAM = 300 use HPI_ERROR_INVALID_OBJ_INDEX */
	/** Invalid compression क्रमmat. */
	HPI_ERROR_INVALID_FORMAT = 301,
	/** Invalid क्रमmat samplerate */
	HPI_ERROR_INVALID_SAMPLERATE = 302,
	/** Invalid क्रमmat number of channels. */
	HPI_ERROR_INVALID_CHANNELS = 303,
	/** Invalid क्रमmat bitrate. */
	HPI_ERROR_INVALID_BITRATE = 304,
	/** Invalid datasize used क्रम stream पढ़ो/ग_लिखो. */
	HPI_ERROR_INVALID_DATASIZE = 305,
	/* HPI_ERROR_BUFFER_FULL = 306 use HPI_ERROR_INVALID_DATASIZE */
	/* HPI_ERROR_BUFFER_EMPTY = 307 use HPI_ERROR_INVALID_DATASIZE */
	/** Null data poपूर्णांकer used क्रम stream पढ़ो/ग_लिखो. */
	HPI_ERROR_INVALID_DATA_POINTER = 308,
	/** Packet ordering error क्रम stream पढ़ो/ग_लिखो. */
	HPI_ERROR_INVALID_PACKET_ORDER = 309,

	/** Object can't करो requested operation in its current
	    state, eg set क्रमmat, change rec mux state जबतक recording.*/
	HPI_ERROR_INVALID_OPERATION = 310,

	/** Where a SRG is shared amongst streams, an incompatible samplerate
	    is one that is dअगरferent to any currently active stream. */
	HPI_ERROR_INCOMPATIBLE_SAMPLERATE = 311,
	/** Adapter mode is illegal.*/
	HPI_ERROR_BAD_ADAPTER_MODE = 312,

	/** There have been too many attempts to set the adapter's
	capabilities (using bad keys), the card should be वापसed
	to ASI अगर further capabilities updates are required */
	HPI_ERROR_TOO_MANY_CAPABILITY_CHANGE_ATTEMPTS = 313,
	/** Streams on dअगरferent adapters cannot be grouped. */
	HPI_ERROR_NO_INTERADAPTER_GROUPS = 314,
	/** Streams on dअगरferent DSPs cannot be grouped. */
	HPI_ERROR_NO_INTERDSP_GROUPS = 315,
	/** Stream रुको cancelled beक्रमe threshold reached. */
	HPI_ERROR_WAIT_CANCELLED = 316,
	/** A अक्षरacter string is invalid. */
	HPI_ERROR_INVALID_STRING = 317,

	/** Invalid mixer node क्रम this adapter. */
	HPI_ERROR_INVALID_NODE = 400,
	/** Invalid control. */
	HPI_ERROR_INVALID_CONTROL = 401,
	/** Invalid control value was passed. */
	HPI_ERROR_INVALID_CONTROL_VALUE = 402,
	/** Control attribute not supported by this control. */
	HPI_ERROR_INVALID_CONTROL_ATTRIBUTE = 403,
	/** Control is disabled. */
	HPI_ERROR_CONTROL_DISABLED = 404,
	/** I2C transaction failed due to a missing ACK. */
	HPI_ERROR_CONTROL_I2C_MISSING_ACK = 405,
	HPI_ERROR_I2C_MISSING_ACK = 405,
	/** Control is busy, or coming out of
	reset and cannot be accessed at this समय. */
	HPI_ERROR_CONTROL_NOT_READY = 407,

	/** Non अस्थिर memory */
	HPI_ERROR_NVMEM_BUSY = 450,
	HPI_ERROR_NVMEM_FULL = 451,
	HPI_ERROR_NVMEM_FAIL = 452,

	/** I2C */
	HPI_ERROR_I2C_BAD_ADR = 460,

	/** Entity type did not match requested type */
	HPI_ERROR_ENTITY_TYPE_MISMATCH = 470,
	/** Entity item count did not match requested count */
	HPI_ERROR_ENTITY_ITEM_COUNT = 471,
	/** Entity type is not one of the valid types */
	HPI_ERROR_ENTITY_TYPE_INVALID = 472,
	/** Entity role is not one of the valid roles */
	HPI_ERROR_ENTITY_ROLE_INVALID = 473,
	/** Entity size करोesn't match target size */
	HPI_ERROR_ENTITY_SIZE_MISMATCH = 474,

	/* AES18 specअगरic errors were 500..507 */

	/** custom error to use क्रम debugging */
	HPI_ERROR_CUSTOM = 600,

	/** hpioct32.c can't obtain mutex */
	HPI_ERROR_MUTEX_TIMEOUT = 700,

	/** Backend errors used to be greater than this.
	    \deprecated Now, all backends वापस only errors defined here in hpi.h
	*/
	HPI_ERROR_BACKEND_BASE = 900,

	/** Communication with DSP failed */
	HPI_ERROR_DSP_COMMUNICATION = 900
		/* Note that the dsp communication error is set to this value so that
		   it reमुख्यs compatible with any software that expects such errors
		   to be backend errors i.e. >= 900.
		   Do not define any new error codes with values > 900.
		 */
पूर्ण;

/** \defgroup maximums HPI maximum values
\अणु
*/
/** Maximum number of PCI HPI adapters */
#घोषणा HPI_MAX_ADAPTERS                20
/** Maximum number of in or out streams per adapter */
#घोषणा HPI_MAX_STREAMS                 16
#घोषणा HPI_MAX_CHANNELS                2	/* per stream */
#घोषणा HPI_MAX_NODES                   8	/* per mixer ? */
#घोषणा HPI_MAX_CONTROLS                4	/* per node ? */
/** maximum number of ancillary bytes per MPEG frame */
#घोषणा HPI_MAX_ANC_BYTES_PER_FRAME     (64)
#घोषणा HPI_STRING_LEN                  16

/** Networked adapters have index >= 100 */
#घोषणा HPI_MIN_NETWORK_ADAPTER_IDX 100

/** Velocity units */
#घोषणा HPI_OSTREAM_VELOCITY_UNITS      4096
/** OutStream बारcale units */
#घोषणा HPI_OSTREAM_TIMESCALE_UNITS     10000
/** OutStream बारcale passthrough - turns बारcaling on in passthough mode */
#घोषणा HPI_OSTREAM_TIMESCALE_PASSTHROUGH       99999

/**\पूर्ण*/

/**************/
/* STRUCTURES */
#अगर_अघोषित DISABLE_PRAGMA_PACK1
#आशय pack(push, 1)
#पूर्ण_अगर

/** Structure containing sample क्रमmat inक्रमmation.
    See also HPI_FormatCreate().
  */
काष्ठा hpi_क्रमmat अणु
	u32 sample_rate;
				/**< 11025, 32000, 44100 ... */
	u32 bit_rate;		  /**< क्रम MPEG */
	u32 attributes;
				/**< Stereo/Joपूर्णांकStereo/Mono */
	u16 mode_legacy;
				/**< Legacy ancillary mode or idle bit  */
	u16 unused;		  /**< Unused */
	u16 channels;	  /**< 1,2..., (or ancillary mode or idle bit */
	u16 क्रमmat;	  /**< HPI_FORMAT_PCM16, _MPEG etc. see #HPI_FORMATS. */
पूर्ण;

काष्ठा hpi_anc_frame अणु
	u32 valid_bits_in_this_frame;
	u8 b_data[HPI_MAX_ANC_BYTES_PER_FRAME];
पूर्ण;

/** An object क्रम containing a single async event.
*/
काष्ठा hpi_async_event अणु
	u16 event_type;	/**< type of event. \sa async_event  */
	u16 sequence; /**< Sequence number, allows lost event detection */
	u32 state; /**< New state */
	u32 h_object; /**< handle to the object वापसing the event. */
	जोड़ अणु
		काष्ठा अणु
			u16 index; /**< GPIO bit index. */
		पूर्ण gpio;
		काष्ठा अणु
			u16 node_index;	/**< what node is the control on ? */
			u16 node_type; /**< what type of node is the control on ? */
		पूर्ण control;
	पूर्ण u;
पूर्ण;

#अगर_अघोषित DISABLE_PRAGMA_PACK1
#आशय pack(pop)
#पूर्ण_अगर

/*****************/
/* HPI FUNCTIONS */
/*****************/

/* Stream */
u16 hpi_stream_estimate_buffer_size(काष्ठा hpi_क्रमmat *pF,
	u32 host_polling_rate_in_milli_seconds, u32 *recommended_buffer_size);

/*************/
/* SubSystem */
/*************/

u16 hpi_subsys_get_version_ex(u32 *pversion_ex);

u16 hpi_subsys_get_num_adapters(पूर्णांक *pn_num_adapters);

u16 hpi_subsys_get_adapter(पूर्णांक iterator, u32 *padapter_index,
	u16 *pw_adapter_type);

/***********/
/* Adapter */
/***********/

u16 hpi_adapter_खोलो(u16 adapter_index);

u16 hpi_adapter_बंद(u16 adapter_index);

u16 hpi_adapter_get_info(u16 adapter_index, u16 *pw_num_outstreams,
	u16 *pw_num_instreams, u16 *pw_version, u32 *pserial_number,
	u16 *pw_adapter_type);

u16 hpi_adapter_get_module_by_index(u16 adapter_index, u16 module_index,
	u16 *pw_num_outमाला_दो, u16 *pw_num_inमाला_दो, u16 *pw_version,
	u32 *pserial_number, u16 *pw_module_type, u32 *ph_module);

u16 hpi_adapter_set_mode(u16 adapter_index, u32 adapter_mode);

u16 hpi_adapter_set_mode_ex(u16 adapter_index, u32 adapter_mode,
	u16 query_or_set);

u16 hpi_adapter_get_mode(u16 adapter_index, u32 *padapter_mode);

u16 hpi_adapter_get_निश्चित2(u16 adapter_index, u16 *p_निश्चित_count,
	अक्षर *psz_निश्चित, u32 *p_param1, u32 *p_param2,
	u32 *p_dsp_string_addr, u16 *p_processor_id);

u16 hpi_adapter_test_निश्चित(u16 adapter_index, u16 निश्चित_id);

u16 hpi_adapter_enable_capability(u16 adapter_index, u16 capability, u32 key);

u16 hpi_adapter_self_test(u16 adapter_index);

u16 hpi_adapter_debug_पढ़ो(u16 adapter_index, u32 dsp_address, अक्षर *p_bytes,
	पूर्णांक *count_bytes);

u16 hpi_adapter_set_property(u16 adapter_index, u16 property, u16 paramter1,
	u16 paramter2);

u16 hpi_adapter_get_property(u16 adapter_index, u16 property,
	u16 *pw_paramter1, u16 *pw_paramter2);

u16 hpi_adapter_क्रमागतerate_property(u16 adapter_index, u16 index,
	u16 what_to_क्रमागतerate, u16 property_index, u32 *psetting);
/*************/
/* OutStream */
/*************/
u16 hpi_outstream_खोलो(u16 adapter_index, u16 outstream_index,
	u32 *ph_outstream);

u16 hpi_outstream_बंद(u32 h_outstream);

u16 hpi_outstream_get_info_ex(u32 h_outstream, u16 *pw_state,
	u32 *pbuffer_size, u32 *pdata_to_play, u32 *psamples_played,
	u32 *pauxiliary_data_to_play);

u16 hpi_outstream_ग_लिखो_buf(u32 h_outstream, स्थिर u8 *pb_ग_लिखो_buf,
	u32 bytes_to_ग_लिखो, स्थिर काष्ठा hpi_क्रमmat *p_क्रमmat);

u16 hpi_outstream_start(u32 h_outstream);

u16 hpi_outstream_रुको_start(u32 h_outstream);

u16 hpi_outstream_stop(u32 h_outstream);

u16 hpi_outstream_sinegen(u32 h_outstream);

u16 hpi_outstream_reset(u32 h_outstream);

u16 hpi_outstream_query_क्रमmat(u32 h_outstream, काष्ठा hpi_क्रमmat *p_क्रमmat);

u16 hpi_outstream_set_क्रमmat(u32 h_outstream, काष्ठा hpi_क्रमmat *p_क्रमmat);

u16 hpi_outstream_set_punch_in_out(u32 h_outstream, u32 punch_in_sample,
	u32 punch_out_sample);

u16 hpi_outstream_set_velocity(u32 h_outstream, लघु velocity);

u16 hpi_outstream_ancillary_reset(u32 h_outstream, u16 mode);

u16 hpi_outstream_ancillary_get_info(u32 h_outstream, u32 *pframes_available);

u16 hpi_outstream_ancillary_पढ़ो(u32 h_outstream,
	काष्ठा hpi_anc_frame *p_anc_frame_buffer,
	u32 anc_frame_buffer_size_in_bytes,
	u32 number_of_ancillary_frames_to_पढ़ो);

u16 hpi_outstream_set_समय_scale(u32 h_outstream, u32 समय_scaleX10000);

u16 hpi_outstream_host_buffer_allocate(u32 h_outstream, u32 size_in_bytes);

u16 hpi_outstream_host_buffer_मुक्त(u32 h_outstream);

u16 hpi_outstream_group_add(u32 h_outstream, u32 h_stream);

u16 hpi_outstream_group_get_map(u32 h_outstream, u32 *poutstream_map,
	u32 *pinstream_map);

u16 hpi_outstream_group_reset(u32 h_outstream);

/************/
/* InStream */
/************/
u16 hpi_instream_खोलो(u16 adapter_index, u16 instream_index,
	u32 *ph_instream);

u16 hpi_instream_बंद(u32 h_instream);

u16 hpi_instream_query_क्रमmat(u32 h_instream,
	स्थिर काष्ठा hpi_क्रमmat *p_क्रमmat);

u16 hpi_instream_set_क्रमmat(u32 h_instream,
	स्थिर काष्ठा hpi_क्रमmat *p_क्रमmat);

u16 hpi_instream_पढ़ो_buf(u32 h_instream, u8 *pb_पढ़ो_buf, u32 bytes_to_पढ़ो);

u16 hpi_instream_start(u32 h_instream);

u16 hpi_instream_रुको_start(u32 h_instream);

u16 hpi_instream_stop(u32 h_instream);

u16 hpi_instream_reset(u32 h_instream);

u16 hpi_instream_get_info_ex(u32 h_instream, u16 *pw_state, u32 *pbuffer_size,
	u32 *pdata_recorded, u32 *psamples_recorded,
	u32 *pauxiliary_data_recorded);

u16 hpi_instream_ancillary_reset(u32 h_instream, u16 bytes_per_frame,
	u16 mode, u16 alignment, u16 idle_bit);

u16 hpi_instream_ancillary_get_info(u32 h_instream, u32 *pframe_space);

u16 hpi_instream_ancillary_ग_लिखो(u32 h_instream,
	स्थिर काष्ठा hpi_anc_frame *p_anc_frame_buffer,
	u32 anc_frame_buffer_size_in_bytes,
	u32 number_of_ancillary_frames_to_ग_लिखो);

u16 hpi_instream_host_buffer_allocate(u32 h_instream, u32 size_in_bytes);

u16 hpi_instream_host_buffer_मुक्त(u32 h_instream);

u16 hpi_instream_group_add(u32 h_instream, u32 h_stream);

u16 hpi_instream_group_get_map(u32 h_instream, u32 *poutstream_map,
	u32 *pinstream_map);

u16 hpi_instream_group_reset(u32 h_instream);

/*********/
/* Mixer */
/*********/
u16 hpi_mixer_खोलो(u16 adapter_index, u32 *ph_mixer);

u16 hpi_mixer_बंद(u32 h_mixer);

u16 hpi_mixer_get_control(u32 h_mixer, u16 src_node_type,
	u16 src_node_type_index, u16 dst_node_type, u16 dst_node_type_index,
	u16 control_type, u32 *ph_control);

u16 hpi_mixer_get_control_by_index(u32 h_mixer, u16 control_index,
	u16 *pw_src_node_type, u16 *pw_src_node_index, u16 *pw_dst_node_type,
	u16 *pw_dst_node_index, u16 *pw_control_type, u32 *ph_control);

u16 hpi_mixer_store(u32 h_mixer, क्रमागत HPI_MIXER_STORE_COMMAND command,
	u16 index);
/************/
/* Controls */
/************/
/******************/
/* Volume control */
/******************/
u16 hpi_volume_set_gain(u32 h_control, लघु an_gain0_01dB[HPI_MAX_CHANNELS]
	);

u16 hpi_volume_get_gain(u32 h_control,
	लघु an_gain0_01dB_out[HPI_MAX_CHANNELS]
	);

u16 hpi_volume_set_mute(u32 h_control, u32 mute);

u16 hpi_volume_get_mute(u32 h_control, u32 *mute);

#घोषणा hpi_volume_get_range hpi_volume_query_range
u16 hpi_volume_query_range(u32 h_control, लघु *min_gain_01dB,
	लघु *max_gain_01dB, लघु *step_gain_01dB);

u16 hpi_volume_query_channels(स्थिर u32 h_control, u32 *p_channels);

u16 hpi_volume_स्वतः_fade(u32 h_control,
	लघु an_stop_gain0_01dB[HPI_MAX_CHANNELS], u32 duration_ms);

u16 hpi_volume_स्वतः_fade_profile(u32 h_control,
	लघु an_stop_gain0_01dB[HPI_MAX_CHANNELS], u32 duration_ms,
	u16 profile);

u16 hpi_volume_query_स्वतः_fade_profile(स्थिर u32 h_control, स्थिर u32 i,
	u16 *profile);

/*****************/
/* Level control */
/*****************/
u16 hpi_level_query_range(u32 h_control, लघु *min_gain_01dB,
	लघु *max_gain_01dB, लघु *step_gain_01dB);

u16 hpi_level_set_gain(u32 h_control, लघु an_gain0_01dB[HPI_MAX_CHANNELS]
	);

u16 hpi_level_get_gain(u32 h_control,
	लघु an_gain0_01dB_out[HPI_MAX_CHANNELS]
	);

/*****************/
/* Meter control */
/*****************/
u16 hpi_meter_query_channels(स्थिर u32 h_meter, u32 *p_channels);

u16 hpi_meter_get_peak(u32 h_control,
	लघु an_peak0_01dB_out[HPI_MAX_CHANNELS]
	);

u16 hpi_meter_get_rms(u32 h_control, लघु an_peak0_01dB_out[HPI_MAX_CHANNELS]
	);

u16 hpi_meter_set_peak_ballistics(u32 h_control, u16 attack, u16 decay);

u16 hpi_meter_set_rms_ballistics(u32 h_control, u16 attack, u16 decay);

u16 hpi_meter_get_peak_ballistics(u32 h_control, u16 *attack, u16 *decay);

u16 hpi_meter_get_rms_ballistics(u32 h_control, u16 *attack, u16 *decay);

/************************/
/* ChannelMode control */
/************************/
u16 hpi_channel_mode_query_mode(स्थिर u32 h_mode, स्थिर u32 index,
	u16 *pw_mode);

u16 hpi_channel_mode_set(u32 h_control, u16 mode);

u16 hpi_channel_mode_get(u32 h_control, u16 *mode);

/*****************/
/* Tuner control */
/*****************/
u16 hpi_tuner_query_band(स्थिर u32 h_tuner, स्थिर u32 index, u16 *pw_band);

u16 hpi_tuner_set_band(u32 h_control, u16 band);

u16 hpi_tuner_get_band(u32 h_control, u16 *pw_band);

u16 hpi_tuner_query_frequency(स्थिर u32 h_tuner, स्थिर u32 index,
	स्थिर u16 band, u32 *pfreq);

u16 hpi_tuner_set_frequency(u32 h_control, u32 freq_ink_hz);

u16 hpi_tuner_get_frequency(u32 h_control, u32 *pw_freq_ink_hz);

u16 hpi_tuner_get_rf_level(u32 h_control, लघु *pw_level);

u16 hpi_tuner_get_raw_rf_level(u32 h_control, लघु *pw_level);

u16 hpi_tuner_query_gain(स्थिर u32 h_tuner, स्थिर u32 index, u16 *pw_gain);

u16 hpi_tuner_set_gain(u32 h_control, लघु gain);

u16 hpi_tuner_get_gain(u32 h_control, लघु *pn_gain);

u16 hpi_tuner_get_status(u32 h_control, u16 *pw_status_mask, u16 *pw_status);

u16 hpi_tuner_set_mode(u32 h_control, u32 mode, u32 value);

u16 hpi_tuner_get_mode(u32 h_control, u32 mode, u32 *pn_value);

u16 hpi_tuner_get_rds(u32 h_control, अक्षर *p_rds_data);

u16 hpi_tuner_query_deemphasis(स्थिर u32 h_tuner, स्थिर u32 index,
	स्थिर u16 band, u32 *pdeemphasis);

u16 hpi_tuner_set_deemphasis(u32 h_control, u32 deemphasis);
u16 hpi_tuner_get_deemphasis(u32 h_control, u32 *pdeemphasis);

u16 hpi_tuner_query_program(स्थिर u32 h_tuner, u32 *pbiपंचांगap_program);

u16 hpi_tuner_set_program(u32 h_control, u32 program);

u16 hpi_tuner_get_program(u32 h_control, u32 *pprogram);

u16 hpi_tuner_get_hd_radio_dsp_version(u32 h_control, अक्षर *psz_dsp_version,
	स्थिर u32 string_size);

u16 hpi_tuner_get_hd_radio_sdk_version(u32 h_control, अक्षर *psz_sdk_version,
	स्थिर u32 string_size);

u16 hpi_tuner_get_hd_radio_संकेत_quality(u32 h_control, u32 *pquality);

u16 hpi_tuner_get_hd_radio_संकेत_blend(u32 h_control, u32 *pblend);

u16 hpi_tuner_set_hd_radio_संकेत_blend(u32 h_control, स्थिर u32 blend);

/***************/
/* PAD control */
/***************/

u16 hpi_pad_get_channel_name(u32 h_control, अक्षर *psz_string,
	स्थिर u32 string_length);

u16 hpi_pad_get_artist(u32 h_control, अक्षर *psz_string,
	स्थिर u32 string_length);

u16 hpi_pad_get_title(u32 h_control, अक्षर *psz_string,
	स्थिर u32 string_length);

u16 hpi_pad_get_comment(u32 h_control, अक्षर *psz_string,
	स्थिर u32 string_length);

u16 hpi_pad_get_program_type(u32 h_control, u32 *ppTY);

u16 hpi_pad_get_rdsPI(u32 h_control, u32 *ppI);

u16 hpi_pad_get_program_type_string(u32 h_control, स्थिर u32 data_type,
	स्थिर u32 pTY, अक्षर *psz_string, स्थिर u32 string_length);

/****************************/
/* AES/EBU Receiver control */
/****************************/
u16 hpi_aesebu_receiver_query_क्रमmat(स्थिर u32 h_aes_rx, स्थिर u32 index,
	u16 *pw_क्रमmat);

u16 hpi_aesebu_receiver_set_क्रमmat(u32 h_control, u16 source);

u16 hpi_aesebu_receiver_get_क्रमmat(u32 h_control, u16 *pw_source);

u16 hpi_aesebu_receiver_get_sample_rate(u32 h_control, u32 *psample_rate);

u16 hpi_aesebu_receiver_get_user_data(u32 h_control, u16 index, u16 *pw_data);

u16 hpi_aesebu_receiver_get_channel_status(u32 h_control, u16 index,
	u16 *pw_data);

u16 hpi_aesebu_receiver_get_error_status(u32 h_control, u16 *pw_error_data);

/*******************************/
/* AES/EBU Transmitter control */
/*******************************/
u16 hpi_aesebu_transmitter_set_sample_rate(u32 h_control, u32 sample_rate);

u16 hpi_aesebu_transmitter_set_user_data(u32 h_control, u16 index, u16 data);

u16 hpi_aesebu_transmitter_set_channel_status(u32 h_control, u16 index,
	u16 data);

u16 hpi_aesebu_transmitter_get_channel_status(u32 h_control, u16 index,
	u16 *pw_data);

u16 hpi_aesebu_transmitter_query_क्रमmat(स्थिर u32 h_aes_tx, स्थिर u32 index,
	u16 *pw_क्रमmat);

u16 hpi_aesebu_transmitter_set_क्रमmat(u32 h_control, u16 output_क्रमmat);

u16 hpi_aesebu_transmitter_get_क्रमmat(u32 h_control, u16 *pw_output_क्रमmat);

/***********************/
/* Multiplexer control */
/***********************/
u16 hpi_multiplexer_set_source(u32 h_control, u16 source_node_type,
	u16 source_node_index);

u16 hpi_multiplexer_get_source(u32 h_control, u16 *source_node_type,
	u16 *source_node_index);

u16 hpi_multiplexer_query_source(u32 h_control, u16 index,
	u16 *source_node_type, u16 *source_node_index);

/***************/
/* Vox control */
/***************/
u16 hpi_vox_set_threshold(u32 h_control, लघु an_gain0_01dB);

u16 hpi_vox_get_threshold(u32 h_control, लघु *an_gain0_01dB);

/*********************/
/* Bitstream control */
/*********************/
u16 hpi_bitstream_set_घड़ी_edge(u32 h_control, u16 edge_type);

u16 hpi_bitstream_set_data_polarity(u32 h_control, u16 polarity);

u16 hpi_bitstream_get_activity(u32 h_control, u16 *pw_clk_activity,
	u16 *pw_data_activity);

/***********************/
/* SampleClock control */
/***********************/

u16 hpi_sample_घड़ी_query_source(स्थिर u32 h_घड़ी, स्थिर u32 index,
	u16 *pw_source);

u16 hpi_sample_घड़ी_set_source(u32 h_control, u16 source);

u16 hpi_sample_घड़ी_get_source(u32 h_control, u16 *pw_source);

u16 hpi_sample_घड़ी_query_source_index(स्थिर u32 h_घड़ी, स्थिर u32 index,
	स्थिर u32 source, u16 *pw_source_index);

u16 hpi_sample_घड़ी_set_source_index(u32 h_control, u16 source_index);

u16 hpi_sample_घड़ी_get_source_index(u32 h_control, u16 *pw_source_index);

u16 hpi_sample_घड़ी_get_sample_rate(u32 h_control, u32 *psample_rate);

u16 hpi_sample_घड़ी_query_local_rate(स्थिर u32 h_घड़ी, स्थिर u32 index,
	u32 *psource);

u16 hpi_sample_घड़ी_set_local_rate(u32 h_control, u32 sample_rate);

u16 hpi_sample_घड़ी_get_local_rate(u32 h_control, u32 *psample_rate);

u16 hpi_sample_घड़ी_set_स्वतः(u32 h_control, u32 enable);

u16 hpi_sample_घड़ी_get_स्वतः(u32 h_control, u32 *penable);

u16 hpi_sample_घड़ी_set_local_rate_lock(u32 h_control, u32 lock);

u16 hpi_sample_घड़ी_get_local_rate_lock(u32 h_control, u32 *plock);

/***********************/
/* Microphone control */
/***********************/
u16 hpi_microphone_set_phantom_घातer(u32 h_control, u16 on_off);

u16 hpi_microphone_get_phantom_घातer(u32 h_control, u16 *pw_on_off);

/********************************/
/* Parametric Equalizer control */
/********************************/
u16 hpi_parametric_eq_get_info(u32 h_control, u16 *pw_number_of_bands,
	u16 *pw_enabled);

u16 hpi_parametric_eq_set_state(u32 h_control, u16 on_off);

u16 hpi_parametric_eq_set_band(u32 h_control, u16 index, u16 type,
	u32 frequency_hz, लघु q100, लघु gain0_01dB);

u16 hpi_parametric_eq_get_band(u32 h_control, u16 index, u16 *pn_type,
	u32 *pfrequency_hz, लघु *pnQ100, लघु *pn_gain0_01dB);

u16 hpi_parametric_eq_get_coeffs(u32 h_control, u16 index, लघु coeffs[5]
	);

/*******************************/
/* Compressor Expander control */
/*******************************/

u16 hpi_compander_set_enable(u32 h_control, u32 on);

u16 hpi_compander_get_enable(u32 h_control, u32 *pon);

u16 hpi_compander_set_makeup_gain(u32 h_control, लघु makeup_gain0_01dB);

u16 hpi_compander_get_makeup_gain(u32 h_control, लघु *pn_makeup_gain0_01dB);

u16 hpi_compander_set_attack_समय_स्थिरant(u32 h_control, u32 index,
	u32 attack);

u16 hpi_compander_get_attack_समय_स्थिरant(u32 h_control, u32 index,
	u32 *pw_attack);

u16 hpi_compander_set_decay_समय_स्थिरant(u32 h_control, u32 index,
	u32 decay);

u16 hpi_compander_get_decay_समय_स्थिरant(u32 h_control, u32 index,
	u32 *pw_decay);

u16 hpi_compander_set_threshold(u32 h_control, u32 index,
	लघु threshold0_01dB);

u16 hpi_compander_get_threshold(u32 h_control, u32 index,
	लघु *pn_threshold0_01dB);

u16 hpi_compander_set_ratio(u32 h_control, u32 index, u32 ratio100);

u16 hpi_compander_get_ratio(u32 h_control, u32 index, u32 *pw_ratio100);

/********************/
/* Cobranet control */
/********************/
u16 hpi_cobranet_hmi_ग_लिखो(u32 h_control, u32 hmi_address, u32 byte_count,
	u8 *pb_data);

u16 hpi_cobranet_hmi_पढ़ो(u32 h_control, u32 hmi_address, u32 max_byte_count,
	u32 *pbyte_count, u8 *pb_data);

u16 hpi_cobranet_hmi_get_status(u32 h_control, u32 *pstatus,
	u32 *pपढ़ोable_size, u32 *pग_लिखोable_size);

u16 hpi_cobranet_get_ip_address(u32 h_control, u32 *pdw_ip_address);

u16 hpi_cobranet_set_ip_address(u32 h_control, u32 dw_ip_address);

u16 hpi_cobranet_get_अटल_ip_address(u32 h_control, u32 *pdw_ip_address);

u16 hpi_cobranet_set_अटल_ip_address(u32 h_control, u32 dw_ip_address);

u16 hpi_cobranet_get_macaddress(u32 h_control, u32 *p_mac_msbs,
	u32 *p_mac_lsbs);

/*************************/
/* Tone Detector control */
/*************************/
u16 hpi_tone_detector_get_state(u32 hC, u32 *state);

u16 hpi_tone_detector_set_enable(u32 hC, u32 enable);

u16 hpi_tone_detector_get_enable(u32 hC, u32 *enable);

u16 hpi_tone_detector_set_event_enable(u32 hC, u32 event_enable);

u16 hpi_tone_detector_get_event_enable(u32 hC, u32 *event_enable);

u16 hpi_tone_detector_set_threshold(u32 hC, पूर्णांक threshold);

u16 hpi_tone_detector_get_threshold(u32 hC, पूर्णांक *threshold);

u16 hpi_tone_detector_get_frequency(u32 hC, u32 index, u32 *frequency);

/****************************/
/* Silence Detector control */
/****************************/
u16 hpi_silence_detector_get_state(u32 hC, u32 *state);

u16 hpi_silence_detector_set_enable(u32 hC, u32 enable);

u16 hpi_silence_detector_get_enable(u32 hC, u32 *enable);

u16 hpi_silence_detector_set_event_enable(u32 hC, u32 event_enable);

u16 hpi_silence_detector_get_event_enable(u32 hC, u32 *event_enable);

u16 hpi_silence_detector_set_delay(u32 hC, u32 delay);

u16 hpi_silence_detector_get_delay(u32 hC, u32 *delay);

u16 hpi_silence_detector_set_threshold(u32 hC, पूर्णांक threshold);

u16 hpi_silence_detector_get_threshold(u32 hC, पूर्णांक *threshold);
/*********************/
/* Utility functions */
/*********************/

u16 hpi_क्रमmat_create(काष्ठा hpi_क्रमmat *p_क्रमmat, u16 channels, u16 क्रमmat,
	u32 sample_rate, u32 bit_rate, u32 attributes);

#पूर्ण_अगर	 /*_HPI_H_ */
