<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ddbridge-mci.h: Digital Devices micro code पूर्णांकerface
 *
 * Copyright (C) 2017-2018 Digital Devices GmbH
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *                         Ralph Metzler <rjkm@metzlerbros.de>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _DDBRIDGE_MCI_H_
#घोषणा _DDBRIDGE_MCI_H_

#घोषणा MCI_DEMOD_MAX                       8
#घोषणा MCI_TUNER_MAX                       4
#घोषणा DEMOD_UNUSED                        (0xFF)

#घोषणा MCI_CONTROL                         (0x500)
#घोषणा MCI_COMMAND                         (0x600)
#घोषणा MCI_RESULT                          (0x680)

#घोषणा MCI_COMMAND_SIZE                    (0x80)
#घोषणा MCI_RESULT_SIZE                     (0x80)

#घोषणा MCI_CONTROL_START_COMMAND           (0x00000001)
#घोषणा MCI_CONTROL_ENABLE_DONE_INTERRUPT   (0x00000002)
#घोषणा MCI_CONTROL_RESET                   (0x00008000)
#घोषणा MCI_CONTROL_READY                   (0x00010000)

#घोषणा SX8_TSCONFIG                        (0x280)

#घोषणा SX8_TSCONFIG_MODE_MASK              (0x00000003)
#घोषणा SX8_TSCONFIG_MODE_OFF               (0x00000000)
#घोषणा SX8_TSCONFIG_MODE_NORMAL            (0x00000001)
#घोषणा SX8_TSCONFIG_MODE_IQ                (0x00000003)

/*
 * IQMode is only available on MaxSX8 on a single tuner
 *
 * IQ_MODE_SAMPLES
 *       sampling rate is 1550/24 MHz (64.583 MHz)
 *       channel agc is frozen, to allow stitching the FFT results together
 *
 * IQ_MODE_VTM
 *       sampling rate is the supplied symbolrate
 *       channel agc is active
 *
 * in both हालs करोwn sampling is करोne with a RRC Filter (currently fixed to
 * alpha = 0.05) which causes some (ca 5%) aliasing at the edges from
 * outside the spectrum
 */

#घोषणा SX8_TSCONFIG_TSHEADER               (0x00000004)
#घोषणा SX8_TSCONFIG_BURST                  (0x00000008)

#घोषणा SX8_TSCONFIG_BURSTSIZE_MASK         (0x00000030)
#घोषणा SX8_TSCONFIG_BURSTSIZE_2K           (0x00000000)
#घोषणा SX8_TSCONFIG_BURSTSIZE_4K           (0x00000010)
#घोषणा SX8_TSCONFIG_BURSTSIZE_8K           (0x00000020)
#घोषणा SX8_TSCONFIG_BURSTSIZE_16K          (0x00000030)

#घोषणा SX8_DEMOD_STOPPED        (0)
#घोषणा SX8_DEMOD_IQ_MODE        (1)
#घोषणा SX8_DEMOD_WAIT_SIGNAL    (2)
#घोषणा SX8_DEMOD_WAIT_MATYPE    (3)
#घोषणा SX8_DEMOD_TIMEOUT        (14)
#घोषणा SX8_DEMOD_LOCKED         (15)

#घोषणा MCI_CMD_STOP             (0x01)
#घोषणा MCI_CMD_GETSTATUS        (0x02)
#घोषणा MCI_CMD_GETSIGNALINFO    (0x03)
#घोषणा MCI_CMD_RFPOWER          (0x04)

#घोषणा MCI_CMD_SEARCH_DVBS      (0x10)

#घोषणा MCI_CMD_GET_IQSYMBOL     (0x30)

#घोषणा SX8_CMD_INPUT_ENABLE     (0x40)
#घोषणा SX8_CMD_INPUT_DISABLE    (0x41)
#घोषणा SX8_CMD_START_IQ         (0x42)
#घोषणा SX8_CMD_STOP_IQ          (0x43)
#घोषणा SX8_CMD_ENABLE_IQOUTPUT  (0x44)
#घोषणा SX8_CMD_DISABLE_IQOUTPUT (0x45)

#घोषणा MCI_STATUS_OK            (0x00)
#घोषणा MCI_STATUS_UNSUPPORTED   (0x80)
#घोषणा MCI_STATUS_RETRY         (0xFD)
#घोषणा MCI_STATUS_NOT_READY     (0xFE)
#घोषणा MCI_STATUS_ERROR         (0xFF)

#घोषणा MCI_SUCCESS(status)      ((status & MCI_STATUS_UNSUPPORTED) == 0)

काष्ठा mci_command अणु
	जोड़ अणु
		u32 command_word;
		काष्ठा अणु
			u8  command;
			u8  tuner;
			u8  demod;
			u8  output;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		u32 params[31];
		काष्ठा अणु
			/*
			 * Bit 0: DVB-S Enabled
			 * Bit 1: DVB-S2 Enabled
			 * Bit 7: InputStreamID
			 */
			u8  flags;
			/*
			 * Bit 0: QPSK,
			 * Bit 1: 8PSK/8APSK
			 * Bit 2: 16APSK
			 * Bit 3: 32APSK
			 * Bit 4: 64APSK
			 * Bit 5: 128APSK
			 * Bit 6: 256APSK
			 */
			u8  s2_modulation_mask;
			u8  rsvd1;
			u8  retry;
			u32 frequency;
			u32 symbol_rate;
			u8  input_stream_id;
			u8  rsvd2[3];
			u32 scrambling_sequence_index;
			u32 frequency_range;
		पूर्ण dvbs2_search;

		काष्ठा अणु
			u8  tap;
			u8  rsvd;
			u16 poपूर्णांक;
		पूर्ण get_iq_symbol;

		काष्ठा अणु
			/*
			 * Bit 0: 0=VTM/1=SCAN
			 * Bit 1: Set Gain
			 */
			u8  flags;
			u8  roll_off;
			u8  rsvd1;
			u8  rsvd2;
			u32 frequency;
			u32 symbol_rate; /* Only in VTM mode */
			u16 gain;
		पूर्ण sx8_start_iq;

		काष्ठा अणु
			/*
			 * Bit 1:0 = STVVGLNA Gain.
			 *   0 = AGC, 1 = 0dB, 2 = Minimum, 3 = Maximum
			 */
			u8  flags;
		पूर्ण sx8_input_enable;
	पूर्ण;
पूर्ण;

काष्ठा mci_result अणु
	जोड़ अणु
		u32 status_word;
		काष्ठा अणु
			u8  status;
			u8  mode;
			u16 समय;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		u32 result[27];
		काष्ठा अणु
			/* 1 = DVB-S, 2 = DVB-S2X */
			u8  standard;
			/* puncture rate क्रम DVB-S */
			u8  pls_code;
			/* 2-0: rolloff */
			u8  roll_off;
			u8  rsvd;
			/* actual frequency in Hz */
			u32 frequency;
			/* actual symbolrate in Hz */
			u32 symbol_rate;
			/* channel घातer in dBm x 100 */
			s16 channel_घातer;
			/* band घातer in dBm x 100 */
			s16 band_घातer;
			/*
			 * SNR in dB x 100
			 * Note: negative values are valid in DVB-S2
			 */
			s16 संकेत_to_noise;
			s16 rsvd2;
			/*
			 * Counter क्रम packet errors
			 * (set to 0 on start command)
			 */
			u32 packet_errors;
			/* Bit error rate: PreRS in DVB-S, PreBCH in DVB-S2X */
			u32 ber_numerator;
			u32 ber_denominator;
		पूर्ण dvbs2_संकेत_info;

		काष्ठा अणु
			s16 i;
			s16 q;
		पूर्ण iq_symbol;
	पूर्ण;
	u32 version[4];
पूर्ण;

काष्ठा mci_base अणु
	काष्ठा list_head     mci_list;
	व्योम                *key;
	काष्ठा ddb_link     *link;
	काष्ठा completion    completion;
	काष्ठा device       *dev;
	काष्ठा mutex         tuner_lock; /* concurrent tuner access lock */
	काष्ठा mutex         mci_lock; /* concurrent MCI access lock */
	पूर्णांक                  count;
	पूर्णांक                  type;
पूर्ण;

काष्ठा mci अणु
	काष्ठा mci_base     *base;
	काष्ठा dvb_frontend  fe;
	पूर्णांक                  nr;
	पूर्णांक                  demod;
	पूर्णांक                  tuner;
पूर्ण;

काष्ठा mci_cfg अणु
	पूर्णांक                  type;
	काष्ठा dvb_frontend_ops *fe_ops;
	u32                  base_size;
	u32                  state_size;
	पूर्णांक (*init)(काष्ठा mci *mci);
	पूर्णांक (*base_init)(काष्ठा mci_base *mci_base);
	पूर्णांक (*set_input)(काष्ठा dvb_frontend *fe, पूर्णांक input);
पूर्ण;

/* defined in ddbridge-sx8.c */
बाह्य स्थिर काष्ठा mci_cfg ddb_max_sx8_cfg;

पूर्णांक ddb_mci_cmd(काष्ठा mci *state, काष्ठा mci_command *command,
		काष्ठा mci_result *result);
पूर्णांक ddb_mci_config(काष्ठा mci *state, u32 config);

काष्ठा dvb_frontend
*ddb_mci_attach(काष्ठा ddb_input *input, काष्ठा mci_cfg *cfg, पूर्णांक nr,
		पूर्णांक (**fn_set_input)(काष्ठा dvb_frontend *fe, पूर्णांक input));

#पूर्ण_अगर /* _DDBRIDGE_MCI_H_ */
