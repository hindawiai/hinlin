<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * frontend.h
 *
 * Copyright (C) 2000 Marcus Metzler <marcus@convergence.de>
 *		    Ralph  Metzler <ralph@convergence.de>
 *		    Holger Waechtler <holger@convergence.de>
 *		    Andre Draszik <ad@convergence.de>
 *		    क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#अगर_अघोषित _DVBFRONTEND_H_
#घोषणा _DVBFRONTEND_H_

#समावेश <linux/types.h>

/**
 * क्रमागत fe_caps - Frontend capabilities
 *
 * @FE_IS_STUPID:			There's something wrong at the
 *					frontend, and it can't report its
 *					capabilities.
 * @FE_CAN_INVERSION_AUTO:		Can स्वतः-detect frequency spectral
 *					band inversion
 * @FE_CAN_FEC_1_2:			Supports FEC 1/2
 * @FE_CAN_FEC_2_3:			Supports FEC 2/3
 * @FE_CAN_FEC_3_4:			Supports FEC 3/4
 * @FE_CAN_FEC_4_5:			Supports FEC 4/5
 * @FE_CAN_FEC_5_6:			Supports FEC 5/6
 * @FE_CAN_FEC_6_7:			Supports FEC 6/7
 * @FE_CAN_FEC_7_8:			Supports FEC 7/8
 * @FE_CAN_FEC_8_9:			Supports FEC 8/9
 * @FE_CAN_FEC_AUTO:			Can स्वतः-detect FEC
 * @FE_CAN_QPSK:			Supports QPSK modulation
 * @FE_CAN_QAM_16:			Supports 16-QAM modulation
 * @FE_CAN_QAM_32:			Supports 32-QAM modulation
 * @FE_CAN_QAM_64:			Supports 64-QAM modulation
 * @FE_CAN_QAM_128:			Supports 128-QAM modulation
 * @FE_CAN_QAM_256:			Supports 256-QAM modulation
 * @FE_CAN_QAM_AUTO:			Can स्वतः-detect QAM modulation
 * @FE_CAN_TRANSMISSION_MODE_AUTO:	Can स्वतः-detect transmission mode
 * @FE_CAN_BANDWIDTH_AUTO:		Can स्वतः-detect bandwidth
 * @FE_CAN_GUARD_INTERVAL_AUTO:		Can स्वतः-detect guard पूर्णांकerval
 * @FE_CAN_HIERARCHY_AUTO:		Can स्वतः-detect hierarchy
 * @FE_CAN_8VSB:			Supports 8-VSB modulation
 * @FE_CAN_16VSB:			Supporta 16-VSB modulation
 * @FE_HAS_EXTENDED_CAPS:		Unused
 * @FE_CAN_MULTISTREAM:			Supports multistream filtering
 * @FE_CAN_TURBO_FEC:			Supports "turbo FEC" modulation
 * @FE_CAN_2G_MODULATION:		Supports "2nd generation" modulation,
 *					e. g. DVB-S2, DVB-T2, DVB-C2
 * @FE_NEEDS_BENDING:			Unused
 * @FE_CAN_RECOVER:			Can recover from a cable unplug
 *					स्वतःmatically
 * @FE_CAN_MUTE_TS:			Can stop spurious TS data output
 */
क्रमागत fe_caps अणु
	FE_IS_STUPID			= 0,
	FE_CAN_INVERSION_AUTO		= 0x1,
	FE_CAN_FEC_1_2			= 0x2,
	FE_CAN_FEC_2_3			= 0x4,
	FE_CAN_FEC_3_4			= 0x8,
	FE_CAN_FEC_4_5			= 0x10,
	FE_CAN_FEC_5_6			= 0x20,
	FE_CAN_FEC_6_7			= 0x40,
	FE_CAN_FEC_7_8			= 0x80,
	FE_CAN_FEC_8_9			= 0x100,
	FE_CAN_FEC_AUTO			= 0x200,
	FE_CAN_QPSK			= 0x400,
	FE_CAN_QAM_16			= 0x800,
	FE_CAN_QAM_32			= 0x1000,
	FE_CAN_QAM_64			= 0x2000,
	FE_CAN_QAM_128			= 0x4000,
	FE_CAN_QAM_256			= 0x8000,
	FE_CAN_QAM_AUTO			= 0x10000,
	FE_CAN_TRANSMISSION_MODE_AUTO	= 0x20000,
	FE_CAN_BANDWIDTH_AUTO		= 0x40000,
	FE_CAN_GUARD_INTERVAL_AUTO	= 0x80000,
	FE_CAN_HIERARCHY_AUTO		= 0x100000,
	FE_CAN_8VSB			= 0x200000,
	FE_CAN_16VSB			= 0x400000,
	FE_HAS_EXTENDED_CAPS		= 0x800000,
	FE_CAN_MULTISTREAM		= 0x4000000,
	FE_CAN_TURBO_FEC		= 0x8000000,
	FE_CAN_2G_MODULATION		= 0x10000000,
	FE_NEEDS_BENDING		= 0x20000000,
	FE_CAN_RECOVER			= 0x40000000,
	FE_CAN_MUTE_TS			= 0x80000000
पूर्ण;

/*
 * DEPRECATED: Should be kept just due to backward compatibility.
 */
क्रमागत fe_type अणु
	FE_QPSK,
	FE_QAM,
	FE_OFDM,
	FE_ATSC
पूर्ण;

/**
 * काष्ठा dvb_frontend_info - Frontend properties and capabilities
 *
 * @name:			Name of the frontend
 * @type:			**DEPRECATED**.
 *				Should not be used on modern programs,
 *				as a frontend may have more than one type.
 *				In order to get the support types of a given
 *				frontend, use :c:type:`DTV_ENUM_DELSYS`
 *				instead.
 * @frequency_min:		Minimal frequency supported by the frontend.
 * @frequency_max:		Minimal frequency supported by the frontend.
 * @frequency_stepsize:		All frequencies are multiple of this value.
 * @frequency_tolerance:	Frequency tolerance.
 * @symbol_rate_min:		Minimal symbol rate, in bauds
 *				(क्रम Cable/Satellite प्रणालीs).
 * @symbol_rate_max:		Maximal symbol rate, in bauds
 *				(क्रम Cable/Satellite प्रणालीs).
 * @symbol_rate_tolerance:	Maximal symbol rate tolerance, in ppm
 *				(क्रम Cable/Satellite प्रणालीs).
 * @notअगरier_delay:		**DEPRECATED**. Not used by any driver.
 * @caps:			Capabilities supported by the frontend,
 *				as specअगरied in &क्रमागत fe_caps.
 *
 * .. note:
 *
 *    #. The frequencies are specअगरied in Hz क्रम Terrestrial and Cable
 *       प्रणालीs.
 *    #. The frequencies are specअगरied in kHz क्रम Satellite प्रणालीs.
 */
काष्ठा dvb_frontend_info अणु
	अक्षर       name[128];
	क्रमागत fe_type type;	/* DEPRECATED. Use DTV_ENUM_DELSYS instead */
	__u32      frequency_min;
	__u32      frequency_max;
	__u32      frequency_stepsize;
	__u32      frequency_tolerance;
	__u32      symbol_rate_min;
	__u32      symbol_rate_max;
	__u32      symbol_rate_tolerance;
	__u32      notअगरier_delay;		/* DEPRECATED */
	क्रमागत fe_caps caps;
पूर्ण;

/**
 * काष्ठा dvb_diseqc_master_cmd - DiSEqC master command
 *
 * @msg:
 *	DiSEqC message to be sent. It contains a 3 bytes header with:
 *	framing + address + command, and an optional argument
 *	of up to 3 bytes of data.
 * @msg_len:
 *	Length of the DiSEqC message. Valid values are 3 to 6.
 *
 * Check out the DiSEqC bus spec available on http://www.eutelsat.org/ क्रम
 * the possible messages that can be used.
 */
काष्ठा dvb_diseqc_master_cmd अणु
	__u8 msg[6];
	__u8 msg_len;
पूर्ण;

/**
 * काष्ठा dvb_diseqc_slave_reply - DiSEqC received data
 *
 * @msg:
 *	DiSEqC message buffer to store a message received via DiSEqC.
 *	It contains one byte header with: framing and
 *	an optional argument of up to 3 bytes of data.
 * @msg_len:
 *	Length of the DiSEqC message. Valid values are 0 to 4,
 *	where 0 means no message.
 * @समयout:
 *	Return from ioctl after समयout ms with errorcode when
 *	no message was received.
 *
 * Check out the DiSEqC bus spec available on http://www.eutelsat.org/ क्रम
 * the possible messages that can be used.
 */
काष्ठा dvb_diseqc_slave_reply अणु
	__u8 msg[4];
	__u8 msg_len;
	पूर्णांक  समयout;
पूर्ण;

/**
 * क्रमागत fe_sec_voltage - DC Voltage used to feed the LNBf
 *
 * @SEC_VOLTAGE_13:	Output 13V to the LNBf
 * @SEC_VOLTAGE_18:	Output 18V to the LNBf
 * @SEC_VOLTAGE_OFF:	Don't feed the LNBf with a DC voltage
 */
क्रमागत fe_sec_voltage अणु
	SEC_VOLTAGE_13,
	SEC_VOLTAGE_18,
	SEC_VOLTAGE_OFF
पूर्ण;

/**
 * क्रमागत fe_sec_tone_mode - Type of tone to be send to the LNBf.
 * @SEC_TONE_ON:	Sends a 22kHz tone burst to the antenna.
 * @SEC_TONE_OFF:	Don't send a 22kHz tone to the antenna (except
 *			अगर the ``FE_DISEQC_*`` ioctls are called).
 */
क्रमागत fe_sec_tone_mode अणु
	SEC_TONE_ON,
	SEC_TONE_OFF
पूर्ण;

/**
 * क्रमागत fe_sec_mini_cmd - Type of mini burst to be sent
 *
 * @SEC_MINI_A:		Sends a mini-DiSEqC 22kHz '0' Tone Burst to select
 *			satellite-A
 * @SEC_MINI_B:		Sends a mini-DiSEqC 22kHz '1' Data Burst to select
 *			satellite-B
 */
क्रमागत fe_sec_mini_cmd अणु
	SEC_MINI_A,
	SEC_MINI_B
पूर्ण;

/**
 * क्रमागत fe_status - Enumerates the possible frontend status.
 * @FE_NONE:		The frontend करोesn't have any kind of lock.
 *			That's the initial frontend status
 * @FE_HAS_SIGNAL:	Has found something above the noise level.
 * @FE_HAS_CARRIER:	Has found a संकेत.
 * @FE_HAS_VITERBI:	FEC inner coding (Viterbi, LDPC or other inner code).
 *			is stable.
 * @FE_HAS_SYNC:	Synchronization bytes was found.
 * @FE_HAS_LOCK:	Digital TV were locked and everything is working.
 * @FE_TIMEDOUT:	Fo lock within the last about 2 seconds.
 * @FE_REINIT:		Frontend was reinitialized, application is recommended
 *			to reset DiSEqC, tone and parameters.
 */
क्रमागत fe_status अणु
	FE_NONE			= 0x00,
	FE_HAS_SIGNAL		= 0x01,
	FE_HAS_CARRIER		= 0x02,
	FE_HAS_VITERBI		= 0x04,
	FE_HAS_SYNC		= 0x08,
	FE_HAS_LOCK		= 0x10,
	FE_TIMEDOUT		= 0x20,
	FE_REINIT		= 0x40,
पूर्ण;

/**
 * क्रमागत fe_spectral_inversion - Type of inversion band
 *
 * @INVERSION_OFF:	Don't करो spectral band inversion.
 * @INVERSION_ON:	Do spectral band inversion.
 * @INVERSION_AUTO:	Autodetect spectral band inversion.
 *
 * This parameter indicates अगर spectral inversion should be presumed or
 * not. In the स्वतःmatic setting (``INVERSION_AUTO``) the hardware will try
 * to figure out the correct setting by itself. If the hardware करोesn't
 * support, the %dvb_frontend will try to lock at the carrier first with
 * inversion off. If it fails, it will try to enable inversion.
 */
क्रमागत fe_spectral_inversion अणु
	INVERSION_OFF,
	INVERSION_ON,
	INVERSION_AUTO
पूर्ण;

/**
 * क्रमागत fe_code_rate - Type of Forward Error Correction (FEC)
 *
 *
 * @FEC_NONE: No Forward Error Correction Code
 * @FEC_1_2:  Forward Error Correction Code 1/2
 * @FEC_2_3:  Forward Error Correction Code 2/3
 * @FEC_3_4:  Forward Error Correction Code 3/4
 * @FEC_4_5:  Forward Error Correction Code 4/5
 * @FEC_5_6:  Forward Error Correction Code 5/6
 * @FEC_6_7:  Forward Error Correction Code 6/7
 * @FEC_7_8:  Forward Error Correction Code 7/8
 * @FEC_8_9:  Forward Error Correction Code 8/9
 * @FEC_AUTO: Autodetect Error Correction Code
 * @FEC_3_5:  Forward Error Correction Code 3/5
 * @FEC_9_10: Forward Error Correction Code 9/10
 * @FEC_2_5:  Forward Error Correction Code 2/5
 *
 * Please note that not all FEC types are supported by a given standard.
 */
क्रमागत fe_code_rate अणु
	FEC_NONE = 0,
	FEC_1_2,
	FEC_2_3,
	FEC_3_4,
	FEC_4_5,
	FEC_5_6,
	FEC_6_7,
	FEC_7_8,
	FEC_8_9,
	FEC_AUTO,
	FEC_3_5,
	FEC_9_10,
	FEC_2_5,
पूर्ण;

/**
 * क्रमागत fe_modulation - Type of modulation/स्थिरellation
 * @QPSK:	QPSK modulation
 * @QAM_16:	16-QAM modulation
 * @QAM_32:	32-QAM modulation
 * @QAM_64:	64-QAM modulation
 * @QAM_128:	128-QAM modulation
 * @QAM_256:	256-QAM modulation
 * @QAM_AUTO:	Autodetect QAM modulation
 * @VSB_8:	8-VSB modulation
 * @VSB_16:	16-VSB modulation
 * @PSK_8:	8-PSK modulation
 * @APSK_16:	16-APSK modulation
 * @APSK_32:	32-APSK modulation
 * @DQPSK:	DQPSK modulation
 * @QAM_4_NR:	4-QAM-NR modulation
 *
 * Please note that not all modulations are supported by a given standard.
 *
 */
क्रमागत fe_modulation अणु
	QPSK,
	QAM_16,
	QAM_32,
	QAM_64,
	QAM_128,
	QAM_256,
	QAM_AUTO,
	VSB_8,
	VSB_16,
	PSK_8,
	APSK_16,
	APSK_32,
	DQPSK,
	QAM_4_NR,
पूर्ण;

/**
 * क्रमागत fe_transmit_mode - Transmission mode
 *
 * @TRANSMISSION_MODE_AUTO:
 *	Autodetect transmission mode. The hardware will try to find the
 *	correct FFT-size (अगर capable) to fill in the missing parameters.
 * @TRANSMISSION_MODE_1K:
 *	Transmission mode 1K
 * @TRANSMISSION_MODE_2K:
 *	Transmission mode 2K
 * @TRANSMISSION_MODE_8K:
 *	Transmission mode 8K
 * @TRANSMISSION_MODE_4K:
 *	Transmission mode 4K
 * @TRANSMISSION_MODE_16K:
 *	Transmission mode 16K
 * @TRANSMISSION_MODE_32K:
 *	Transmission mode 32K
 * @TRANSMISSION_MODE_C1:
 *	Single Carrier (C=1) transmission mode (DTMB only)
 * @TRANSMISSION_MODE_C3780:
 *	Multi Carrier (C=3780) transmission mode (DTMB only)
 *
 * Please note that not all transmission modes are supported by a given
 * standard.
 */
क्रमागत fe_transmit_mode अणु
	TRANSMISSION_MODE_2K,
	TRANSMISSION_MODE_8K,
	TRANSMISSION_MODE_AUTO,
	TRANSMISSION_MODE_4K,
	TRANSMISSION_MODE_1K,
	TRANSMISSION_MODE_16K,
	TRANSMISSION_MODE_32K,
	TRANSMISSION_MODE_C1,
	TRANSMISSION_MODE_C3780,
पूर्ण;

/**
 * क्रमागत fe_guard_पूर्णांकerval - Guard पूर्णांकerval
 *
 * @GUARD_INTERVAL_AUTO:	Autodetect the guard पूर्णांकerval
 * @GUARD_INTERVAL_1_128:	Guard पूर्णांकerval 1/128
 * @GUARD_INTERVAL_1_32:	Guard पूर्णांकerval 1/32
 * @GUARD_INTERVAL_1_16:	Guard पूर्णांकerval 1/16
 * @GUARD_INTERVAL_1_8:		Guard पूर्णांकerval 1/8
 * @GUARD_INTERVAL_1_4:		Guard पूर्णांकerval 1/4
 * @GUARD_INTERVAL_19_128:	Guard पूर्णांकerval 19/128
 * @GUARD_INTERVAL_19_256:	Guard पूर्णांकerval 19/256
 * @GUARD_INTERVAL_PN420:	PN length 420 (1/4)
 * @GUARD_INTERVAL_PN595:	PN length 595 (1/6)
 * @GUARD_INTERVAL_PN945:	PN length 945 (1/9)
 *
 * Please note that not all guard पूर्णांकervals are supported by a given standard.
 */
क्रमागत fe_guard_पूर्णांकerval अणु
	GUARD_INTERVAL_1_32,
	GUARD_INTERVAL_1_16,
	GUARD_INTERVAL_1_8,
	GUARD_INTERVAL_1_4,
	GUARD_INTERVAL_AUTO,
	GUARD_INTERVAL_1_128,
	GUARD_INTERVAL_19_128,
	GUARD_INTERVAL_19_256,
	GUARD_INTERVAL_PN420,
	GUARD_INTERVAL_PN595,
	GUARD_INTERVAL_PN945,
पूर्ण;

/**
 * क्रमागत fe_hierarchy - Hierarchy
 * @HIERARCHY_NONE:	No hierarchy
 * @HIERARCHY_AUTO:	Autodetect hierarchy (अगर supported)
 * @HIERARCHY_1:	Hierarchy 1
 * @HIERARCHY_2:	Hierarchy 2
 * @HIERARCHY_4:	Hierarchy 4
 *
 * Please note that not all hierarchy types are supported by a given standard.
 */
क्रमागत fe_hierarchy अणु
	HIERARCHY_NONE,
	HIERARCHY_1,
	HIERARCHY_2,
	HIERARCHY_4,
	HIERARCHY_AUTO
पूर्ण;

/**
 * क्रमागत fe_पूर्णांकerleaving - Interleaving
 * @INTERLEAVING_NONE:	No पूर्णांकerleaving.
 * @INTERLEAVING_AUTO:	Auto-detect पूर्णांकerleaving.
 * @INTERLEAVING_240:	Interleaving of 240 symbols.
 * @INTERLEAVING_720:	Interleaving of 720 symbols.
 *
 * Please note that, currently, only DTMB uses it.
 */
क्रमागत fe_पूर्णांकerleaving अणु
	INTERLEAVING_NONE,
	INTERLEAVING_AUTO,
	INTERLEAVING_240,
	INTERLEAVING_720,
पूर्ण;

/* DVBv5 property Commands */

#घोषणा DTV_UNDEFINED		0
#घोषणा DTV_TUNE		1
#घोषणा DTV_CLEAR		2
#घोषणा DTV_FREQUENCY		3
#घोषणा DTV_MODULATION		4
#घोषणा DTV_BANDWIDTH_HZ	5
#घोषणा DTV_INVERSION		6
#घोषणा DTV_DISEQC_MASTER	7
#घोषणा DTV_SYMBOL_RATE		8
#घोषणा DTV_INNER_FEC		9
#घोषणा DTV_VOLTAGE		10
#घोषणा DTV_TONE		11
#घोषणा DTV_PILOT		12
#घोषणा DTV_ROLLOFF		13
#घोषणा DTV_DISEQC_SLAVE_REPLY	14

/* Basic क्रमागतeration set क्रम querying unlimited capabilities */
#घोषणा DTV_FE_CAPABILITY_COUNT	15
#घोषणा DTV_FE_CAPABILITY	16
#घोषणा DTV_DELIVERY_SYSTEM	17

/* ISDB-T and ISDB-Tsb */
#घोषणा DTV_ISDBT_PARTIAL_RECEPTION	18
#घोषणा DTV_ISDBT_SOUND_BROADCASTING	19

#घोषणा DTV_ISDBT_SB_SUBCHANNEL_ID	20
#घोषणा DTV_ISDBT_SB_SEGMENT_IDX	21
#घोषणा DTV_ISDBT_SB_SEGMENT_COUNT	22

#घोषणा DTV_ISDBT_LAYERA_FEC			23
#घोषणा DTV_ISDBT_LAYERA_MODULATION		24
#घोषणा DTV_ISDBT_LAYERA_SEGMENT_COUNT		25
#घोषणा DTV_ISDBT_LAYERA_TIME_INTERLEAVING	26

#घोषणा DTV_ISDBT_LAYERB_FEC			27
#घोषणा DTV_ISDBT_LAYERB_MODULATION		28
#घोषणा DTV_ISDBT_LAYERB_SEGMENT_COUNT		29
#घोषणा DTV_ISDBT_LAYERB_TIME_INTERLEAVING	30

#घोषणा DTV_ISDBT_LAYERC_FEC			31
#घोषणा DTV_ISDBT_LAYERC_MODULATION		32
#घोषणा DTV_ISDBT_LAYERC_SEGMENT_COUNT		33
#घोषणा DTV_ISDBT_LAYERC_TIME_INTERLEAVING	34

#घोषणा DTV_API_VERSION		35

#घोषणा DTV_CODE_RATE_HP	36
#घोषणा DTV_CODE_RATE_LP	37
#घोषणा DTV_GUARD_INTERVAL	38
#घोषणा DTV_TRANSMISSION_MODE	39
#घोषणा DTV_HIERARCHY		40

#घोषणा DTV_ISDBT_LAYER_ENABLED	41

#घोषणा DTV_STREAM_ID		42
#घोषणा DTV_ISDBS_TS_ID_LEGACY	DTV_STREAM_ID
#घोषणा DTV_DVBT2_PLP_ID_LEGACY	43

#घोषणा DTV_ENUM_DELSYS		44

/* ATSC-MH */
#घोषणा DTV_ATSCMH_FIC_VER		45
#घोषणा DTV_ATSCMH_PARADE_ID		46
#घोषणा DTV_ATSCMH_NOG			47
#घोषणा DTV_ATSCMH_TNOG			48
#घोषणा DTV_ATSCMH_SGN			49
#घोषणा DTV_ATSCMH_PRC			50
#घोषणा DTV_ATSCMH_RS_FRAME_MODE	51
#घोषणा DTV_ATSCMH_RS_FRAME_ENSEMBLE	52
#घोषणा DTV_ATSCMH_RS_CODE_MODE_PRI	53
#घोषणा DTV_ATSCMH_RS_CODE_MODE_SEC	54
#घोषणा DTV_ATSCMH_SCCC_BLOCK_MODE	55
#घोषणा DTV_ATSCMH_SCCC_CODE_MODE_A	56
#घोषणा DTV_ATSCMH_SCCC_CODE_MODE_B	57
#घोषणा DTV_ATSCMH_SCCC_CODE_MODE_C	58
#घोषणा DTV_ATSCMH_SCCC_CODE_MODE_D	59

#घोषणा DTV_INTERLEAVING			60
#घोषणा DTV_LNA					61

/* Quality parameters */
#घोषणा DTV_STAT_SIGNAL_STRENGTH	62
#घोषणा DTV_STAT_CNR			63
#घोषणा DTV_STAT_PRE_ERROR_BIT_COUNT	64
#घोषणा DTV_STAT_PRE_TOTAL_BIT_COUNT	65
#घोषणा DTV_STAT_POST_ERROR_BIT_COUNT	66
#घोषणा DTV_STAT_POST_TOTAL_BIT_COUNT	67
#घोषणा DTV_STAT_ERROR_BLOCK_COUNT	68
#घोषणा DTV_STAT_TOTAL_BLOCK_COUNT	69

/* Physical layer scrambling */
#घोषणा DTV_SCRAMBLING_SEQUENCE_INDEX	70

#घोषणा DTV_MAX_COMMAND		DTV_SCRAMBLING_SEQUENCE_INDEX

/**
 * क्रमागत fe_pilot - Type of pilot tone
 *
 * @PILOT_ON:	Pilot tones enabled
 * @PILOT_OFF:	Pilot tones disabled
 * @PILOT_AUTO:	Autodetect pilot tones
 */
क्रमागत fe_pilot अणु
	PILOT_ON,
	PILOT_OFF,
	PILOT_AUTO,
पूर्ण;

/**
 * क्रमागत fe_rolloff - Rolloff factor
 * @ROLLOFF_35:		Roloff factor: Nऔ=35%
 * @ROLLOFF_20:		Roloff factor: Nऔ=20%
 * @ROLLOFF_25:		Roloff factor: Nऔ=25%
 * @ROLLOFF_AUTO:	Auto-detect the roloff factor.
 *
 * .. note:
 *
 *    Roloff factor of 35% is implied on DVB-S. On DVB-S2, it is शेष.
 */
क्रमागत fe_rolloff अणु
	ROLLOFF_35,
	ROLLOFF_20,
	ROLLOFF_25,
	ROLLOFF_AUTO,
पूर्ण;

/**
 * क्रमागत fe_delivery_प्रणाली - Type of the delivery प्रणाली
 *
 * @SYS_UNDEFINED:
 *	Undefined standard. Generally, indicates an error
 * @SYS_DVBC_ANNEX_A:
 *	Cable TV: DVB-C following ITU-T J.83 Annex A spec
 * @SYS_DVBC_ANNEX_B:
 *	Cable TV: DVB-C following ITU-T J.83 Annex B spec (ClearQAM)
 * @SYS_DVBC_ANNEX_C:
 *	Cable TV: DVB-C following ITU-T J.83 Annex C spec
 * @SYS_ISDBC:
 *	Cable TV: ISDB-C (no drivers yet)
 * @SYS_DVBT:
 *	Terrestrial TV: DVB-T
 * @SYS_DVBT2:
 *	Terrestrial TV: DVB-T2
 * @SYS_ISDBT:
 *	Terrestrial TV: ISDB-T
 * @SYS_ATSC:
 *	Terrestrial TV: ATSC
 * @SYS_ATSCMH:
 *	Terrestrial TV (mobile): ATSC-M/H
 * @SYS_DTMB:
 *	Terrestrial TV: DTMB
 * @SYS_DVBS:
 *	Satellite TV: DVB-S
 * @SYS_DVBS2:
 *	Satellite TV: DVB-S2
 * @SYS_TURBO:
 *	Satellite TV: DVB-S Turbo
 * @SYS_ISDBS:
 *	Satellite TV: ISDB-S
 * @SYS_DAB:
 *	Digital audio: DAB (not fully supported)
 * @SYS_DSS:
 *	Satellite TV: DSS (not fully supported)
 * @SYS_CMMB:
 *	Terrestrial TV (mobile): CMMB (not fully supported)
 * @SYS_DVBH:
 *	Terrestrial TV (mobile): DVB-H (standard deprecated)
 */
क्रमागत fe_delivery_प्रणाली अणु
	SYS_UNDEFINED,
	SYS_DVBC_ANNEX_A,
	SYS_DVBC_ANNEX_B,
	SYS_DVBT,
	SYS_DSS,
	SYS_DVBS,
	SYS_DVBS2,
	SYS_DVBH,
	SYS_ISDBT,
	SYS_ISDBS,
	SYS_ISDBC,
	SYS_ATSC,
	SYS_ATSCMH,
	SYS_DTMB,
	SYS_CMMB,
	SYS_DAB,
	SYS_DVBT2,
	SYS_TURBO,
	SYS_DVBC_ANNEX_C,
पूर्ण;

/* backward compatibility definitions क्रम delivery प्रणालीs */
#घोषणा SYS_DVBC_ANNEX_AC	SYS_DVBC_ANNEX_A
#घोषणा SYS_DMBTH		SYS_DTMB /* DMB-TH is legacy name, use DTMB */

/* ATSC-MH specअगरic parameters */

/**
 * क्रमागत atscmh_sccc_block_mode - Type of Series Concatenated Convolutional
 *				 Code Block Mode.
 *
 * @ATSCMH_SCCC_BLK_SEP:
 *	Separate SCCC: the SCCC outer code mode shall be set independently
 *	क्रम each Group Region (A, B, C, D)
 * @ATSCMH_SCCC_BLK_COMB:
 *	Combined SCCC: all four Regions shall have the same SCCC outer
 *	code mode.
 * @ATSCMH_SCCC_BLK_RES:
 *	Reserved. Shouldn't be used.
 */
क्रमागत atscmh_sccc_block_mode अणु
	ATSCMH_SCCC_BLK_SEP      = 0,
	ATSCMH_SCCC_BLK_COMB     = 1,
	ATSCMH_SCCC_BLK_RES      = 2,
पूर्ण;

/**
 * क्रमागत atscmh_sccc_code_mode - Type of Series Concatenated Convolutional
 *				Code Rate.
 *
 * @ATSCMH_SCCC_CODE_HLF:
 *	The outer code rate of a SCCC Block is 1/2 rate.
 * @ATSCMH_SCCC_CODE_QTR:
 *	The outer code rate of a SCCC Block is 1/4 rate.
 * @ATSCMH_SCCC_CODE_RES:
 *	Reserved. Should not be used.
 */
क्रमागत atscmh_sccc_code_mode अणु
	ATSCMH_SCCC_CODE_HLF     = 0,
	ATSCMH_SCCC_CODE_QTR     = 1,
	ATSCMH_SCCC_CODE_RES     = 2,
पूर्ण;

/**
 * क्रमागत atscmh_rs_frame_ensemble - Reed Solomon(RS) frame ensemble.
 *
 * @ATSCMH_RSFRAME_ENS_PRI:	Primary Ensemble.
 * @ATSCMH_RSFRAME_ENS_SEC:	Secondary Ensemble.
 */
क्रमागत atscmh_rs_frame_ensemble अणु
	ATSCMH_RSFRAME_ENS_PRI   = 0,
	ATSCMH_RSFRAME_ENS_SEC   = 1,
पूर्ण;

/**
 * क्रमागत atscmh_rs_frame_mode - Reed Solomon (RS) frame mode.
 *
 * @ATSCMH_RSFRAME_PRI_ONLY:
 *	Single Frame: There is only a primary RS Frame क्रम all Group
 *	Regions.
 * @ATSCMH_RSFRAME_PRI_SEC:
 *	Dual Frame: There are two separate RS Frames: Primary RS Frame क्रम
 *	Group Region A and B and Secondary RS Frame क्रम Group Region C and
 *	D.
 * @ATSCMH_RSFRAME_RES:
 *	Reserved. Shouldn't be used.
 */
क्रमागत atscmh_rs_frame_mode अणु
	ATSCMH_RSFRAME_PRI_ONLY  = 0,
	ATSCMH_RSFRAME_PRI_SEC   = 1,
	ATSCMH_RSFRAME_RES       = 2,
पूर्ण;

/**
 * क्रमागत atscmh_rs_code_mode
 * @ATSCMH_RSCODE_211_187:	Reed Solomon code (211,187).
 * @ATSCMH_RSCODE_223_187:	Reed Solomon code (223,187).
 * @ATSCMH_RSCODE_235_187:	Reed Solomon code (235,187).
 * @ATSCMH_RSCODE_RES:		Reserved. Shouldn't be used.
 */
क्रमागत atscmh_rs_code_mode अणु
	ATSCMH_RSCODE_211_187    = 0,
	ATSCMH_RSCODE_223_187    = 1,
	ATSCMH_RSCODE_235_187    = 2,
	ATSCMH_RSCODE_RES        = 3,
पूर्ण;

#घोषणा NO_STREAM_ID_FILTER	(~0U)
#घोषणा LNA_AUTO                (~0U)

/**
 * क्रमागत fecap_scale_params - scale types क्रम the quality parameters.
 *
 * @FE_SCALE_NOT_AVAILABLE: That QoS measure is not available. That
 *			    could indicate a temporary or a permanent
 *			    condition.
 * @FE_SCALE_DECIBEL: The scale is measured in 0.001 dB steps, typically
 *		      used on संकेत measures.
 * @FE_SCALE_RELATIVE: The scale is a relative percentual measure,
 *		       ranging from 0 (0%) to 0xffff (100%).
 * @FE_SCALE_COUNTER: The scale counts the occurrence of an event, like
 *		      bit error, block error, lapsed समय.
 */
क्रमागत fecap_scale_params अणु
	FE_SCALE_NOT_AVAILABLE = 0,
	FE_SCALE_DECIBEL,
	FE_SCALE_RELATIVE,
	FE_SCALE_COUNTER
पूर्ण;

/**
 * काष्ठा dtv_stats - Used क्रम पढ़ोing a DTV status property
 *
 * @scale:
 *	Filled with क्रमागत fecap_scale_params - the scale in usage
 *	क्रम that parameter
 *
 * @svalue:
 *	पूर्णांकeger value of the measure, क्रम %FE_SCALE_DECIBEL,
 *	used क्रम dB measures. The unit is 0.001 dB.
 *
 * @uvalue:
 *	अचिन्हित पूर्णांकeger value of the measure, used when @scale is
 *	either %FE_SCALE_RELATIVE or %FE_SCALE_COUNTER.
 *
 * For most delivery प्रणालीs, this will वापस a single value क्रम each
 * parameter.
 *
 * It should be noticed, however, that new OFDM delivery प्रणालीs like
 * ISDB can use dअगरferent modulation types क्रम each group of carriers.
 * On such standards, up to 8 groups of statistics can be provided, one
 * क्रम each carrier group (called "layer" on ISDB).
 *
 * In order to be consistent with other delivery प्रणालीs, the first
 * value refers to the entire set of carriers ("global").
 *
 * @scale should use the value %FE_SCALE_NOT_AVAILABLE when
 * the value क्रम the entire group of carriers or from one specअगरic layer
 * is not provided by the hardware.
 *
 * @len should be filled with the latest filled status + 1.
 *
 * In other words, क्रम ISDB, those values should be filled like::
 *
 *	u.st.stat.svalue[0] = global statistics;
 *	u.st.stat.scale[0] = FE_SCALE_DECIBEL;
 *	u.st.stat.value[1] = layer A statistics;
 *	u.st.stat.scale[1] = FE_SCALE_NOT_AVAILABLE (अगर not available);
 *	u.st.stat.svalue[2] = layer B statistics;
 *	u.st.stat.scale[2] = FE_SCALE_DECIBEL;
 *	u.st.stat.svalue[3] = layer C statistics;
 *	u.st.stat.scale[3] = FE_SCALE_DECIBEL;
 *	u.st.len = 4;
 */
काष्ठा dtv_stats अणु
	__u8 scale;	/* क्रमागत fecap_scale_params type */
	जोड़ अणु
		__u64 uvalue;	/* क्रम counters and relative scales */
		__s64 svalue;	/* क्रम 0.001 dB measures */
	पूर्ण;
पूर्ण __attribute__ ((packed));


#घोषणा MAX_DTV_STATS   4

/**
 * काष्ठा dtv_fe_stats - store Digital TV frontend statistics
 *
 * @len:	length of the statistics - अगर zero, stats is disabled.
 * @stat:	array with digital TV statistics.
 *
 * On most standards, @len can either be 0 or 1. However, क्रम ISDB, each
 * layer is modulated in separate. So, each layer may have its own set
 * of statistics. If so, stat[0] carries on a global value क्रम the property.
 * Indexes 1 to 3 means layer A to B.
 */
काष्ठा dtv_fe_stats अणु
	__u8 len;
	काष्ठा dtv_stats stat[MAX_DTV_STATS];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा dtv_property - store one of frontend command and its value
 *
 * @cmd:		Digital TV command.
 * @reserved:		Not used.
 * @u:			Union with the values क्रम the command.
 * @u.data:		A अचिन्हित 32 bits पूर्णांकeger with command value.
 * @u.buffer:		Struct to store bigger properties.
 *			Currently unused.
 * @u.buffer.data:	an अचिन्हित 32-bits array.
 * @u.buffer.len:	number of elements of the buffer.
 * @u.buffer.reserved1:	Reserved.
 * @u.buffer.reserved2:	Reserved.
 * @u.st:		a &काष्ठा dtv_fe_stats array of statistics.
 * @result:		Currently unused.
 *
 */
काष्ठा dtv_property अणु
	__u32 cmd;
	__u32 reserved[3];
	जोड़ अणु
		__u32 data;
		काष्ठा dtv_fe_stats st;
		काष्ठा अणु
			__u8 data[32];
			__u32 len;
			__u32 reserved1[3];
			व्योम *reserved2;
		पूर्ण buffer;
	पूर्ण u;
	पूर्णांक result;
पूर्ण __attribute__ ((packed));

/* num of properties cannot exceed DTV_IOCTL_MAX_MSGS per ioctl */
#घोषणा DTV_IOCTL_MAX_MSGS 64

/**
 * काष्ठा dtv_properties - a set of command/value pairs.
 *
 * @num:	amount of commands stored at the काष्ठा.
 * @props:	a poपूर्णांकer to &काष्ठा dtv_property.
 */
काष्ठा dtv_properties अणु
	__u32 num;
	काष्ठा dtv_property *props;
पूर्ण;

/*
 * When set, this flag will disable any zigzagging or other "normal" tuning
 * behavior. Additionally, there will be no स्वतःmatic monitoring of the lock
 * status, and hence no frontend events will be generated. If a frontend device
 * is बंदd, this flag will be स्वतःmatically turned off when the device is
 * reखोलोed पढ़ो-ग_लिखो.
 */
#घोषणा FE_TUNE_MODE_ONESHOT 0x01

/* Digital TV Frontend API calls */

#घोषणा FE_GET_INFO		   _IOR('o', 61, काष्ठा dvb_frontend_info)

#घोषणा FE_DISEQC_RESET_OVERLOAD   _IO('o', 62)
#घोषणा FE_DISEQC_SEND_MASTER_CMD  _IOW('o', 63, काष्ठा dvb_diseqc_master_cmd)
#घोषणा FE_DISEQC_RECV_SLAVE_REPLY _IOR('o', 64, काष्ठा dvb_diseqc_slave_reply)
#घोषणा FE_DISEQC_SEND_BURST       _IO('o', 65)  /* fe_sec_mini_cmd_t */

#घोषणा FE_SET_TONE		   _IO('o', 66)  /* fe_sec_tone_mode_t */
#घोषणा FE_SET_VOLTAGE		   _IO('o', 67)  /* fe_sec_voltage_t */
#घोषणा FE_ENABLE_HIGH_LNB_VOLTAGE _IO('o', 68)  /* पूर्णांक */

#घोषणा FE_READ_STATUS		   _IOR('o', 69, fe_status_t)
#घोषणा FE_READ_BER		   _IOR('o', 70, __u32)
#घोषणा FE_READ_SIGNAL_STRENGTH    _IOR('o', 71, __u16)
#घोषणा FE_READ_SNR		   _IOR('o', 72, __u16)
#घोषणा FE_READ_UNCORRECTED_BLOCKS _IOR('o', 73, __u32)

#घोषणा FE_SET_FRONTEND_TUNE_MODE  _IO('o', 81) /* अचिन्हित पूर्णांक */
#घोषणा FE_GET_EVENT		   _IOR('o', 78, काष्ठा dvb_frontend_event)

#घोषणा FE_DISHNETWORK_SEND_LEGACY_CMD _IO('o', 80) /* अचिन्हित पूर्णांक */

#घोषणा FE_SET_PROPERTY		   _IOW('o', 82, काष्ठा dtv_properties)
#घोषणा FE_GET_PROPERTY		   _IOR('o', 83, काष्ठा dtv_properties)

#अगर defined(__DVB_CORE__) || !defined(__KERNEL__)

/*
 * DEPRECATED: Everything below is deprecated in favor of DVBv5 API
 *
 * The DVBv3 only ioctls, काष्ठाs and क्रमागतs should not be used on
 * newer programs, as it करोesn't support the second generation of
 * digital TV standards, nor supports newer delivery प्रणालीs.
 * They also करोn't support modern frontends with usually support multiple
 * delivery प्रणालीs.
 *
 * Drivers shouldn't use them.
 *
 * New applications should use DVBv5 delivery प्रणाली instead
 */

/*
 */

क्रमागत fe_bandwidth अणु
	BANDWIDTH_8_MHZ,
	BANDWIDTH_7_MHZ,
	BANDWIDTH_6_MHZ,
	BANDWIDTH_AUTO,
	BANDWIDTH_5_MHZ,
	BANDWIDTH_10_MHZ,
	BANDWIDTH_1_712_MHZ,
पूर्ण;

/* This is kept क्रम legacy userspace support */
प्रकार क्रमागत fe_sec_voltage fe_sec_voltage_t;
प्रकार क्रमागत fe_caps fe_caps_t;
प्रकार क्रमागत fe_type fe_type_t;
प्रकार क्रमागत fe_sec_tone_mode fe_sec_tone_mode_t;
प्रकार क्रमागत fe_sec_mini_cmd fe_sec_mini_cmd_t;
प्रकार क्रमागत fe_status fe_status_t;
प्रकार क्रमागत fe_spectral_inversion fe_spectral_inversion_t;
प्रकार क्रमागत fe_code_rate fe_code_rate_t;
प्रकार क्रमागत fe_modulation fe_modulation_t;
प्रकार क्रमागत fe_transmit_mode fe_transmit_mode_t;
प्रकार क्रमागत fe_bandwidth fe_bandwidth_t;
प्रकार क्रमागत fe_guard_पूर्णांकerval fe_guard_पूर्णांकerval_t;
प्रकार क्रमागत fe_hierarchy fe_hierarchy_t;
प्रकार क्रमागत fe_pilot fe_pilot_t;
प्रकार क्रमागत fe_rolloff fe_rolloff_t;
प्रकार क्रमागत fe_delivery_प्रणाली fe_delivery_प्रणाली_t;

/* DVBv3 काष्ठाs */

काष्ठा dvb_qpsk_parameters अणु
	__u32		symbol_rate;  /* symbol rate in Symbols per second */
	fe_code_rate_t	fec_inner;    /* क्रमward error correction (see above) */
पूर्ण;

काष्ठा dvb_qam_parameters अणु
	__u32		symbol_rate; /* symbol rate in Symbols per second */
	fe_code_rate_t	fec_inner;   /* क्रमward error correction (see above) */
	fe_modulation_t	modulation;  /* modulation type (see above) */
पूर्ण;

काष्ठा dvb_vsb_parameters अणु
	fe_modulation_t	modulation;  /* modulation type (see above) */
पूर्ण;

काष्ठा dvb_ofdm_parameters अणु
	fe_bandwidth_t      bandwidth;
	fe_code_rate_t      code_rate_HP;  /* high priority stream code rate */
	fe_code_rate_t      code_rate_LP;  /* low priority stream code rate */
	fe_modulation_t     स्थिरellation; /* modulation type (see above) */
	fe_transmit_mode_t  transmission_mode;
	fe_guard_पूर्णांकerval_t guard_पूर्णांकerval;
	fe_hierarchy_t      hierarchy_inक्रमmation;
पूर्ण;

काष्ठा dvb_frontend_parameters अणु
	__u32 frequency;  /* (असलolute) frequency in Hz क्रम DVB-C/DVB-T/ATSC */
			  /* पूर्णांकermediate frequency in kHz क्रम DVB-S */
	fe_spectral_inversion_t inversion;
	जोड़ अणु
		काष्ठा dvb_qpsk_parameters qpsk;	/* DVB-S */
		काष्ठा dvb_qam_parameters  qam;		/* DVB-C */
		काष्ठा dvb_ofdm_parameters ofdm;	/* DVB-T */
		काष्ठा dvb_vsb_parameters vsb;		/* ATSC */
	पूर्ण u;
पूर्ण;

काष्ठा dvb_frontend_event अणु
	fe_status_t status;
	काष्ठा dvb_frontend_parameters parameters;
पूर्ण;

/* DVBv3 API calls */

#घोषणा FE_SET_FRONTEND		   _IOW('o', 76, काष्ठा dvb_frontend_parameters)
#घोषणा FE_GET_FRONTEND		   _IOR('o', 77, काष्ठा dvb_frontend_parameters)

#पूर्ण_अगर

#पूर्ण_अगर /*_DVBFRONTEND_H_*/
