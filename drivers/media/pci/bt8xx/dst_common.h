<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Frontend-driver क्रम TwinHan DST Frontend

	Copyright (C) 2003 Jamie Honan
	Copyright (C) 2004, 2005 Manu Abraham (manu@kromtek.com)

*/

#अगर_अघोषित DST_COMMON_H
#घोषणा DST_COMMON_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश "bt878.h"

#समावेश "dst_ca.h"


#घोषणा NO_DELAY		0
#घोषणा LONG_DELAY		1
#घोषणा DEVICE_INIT		2

#घोषणा DELAY			1

#घोषणा DST_TYPE_IS_SAT		0
#घोषणा DST_TYPE_IS_TERR	1
#घोषणा DST_TYPE_IS_CABLE	2
#घोषणा DST_TYPE_IS_ATSC	3

#घोषणा DST_TYPE_HAS_TS188	1
#घोषणा DST_TYPE_HAS_TS204	2
#घोषणा DST_TYPE_HAS_SYMDIV	4
#घोषणा DST_TYPE_HAS_FW_1	8
#घोषणा DST_TYPE_HAS_FW_2	16
#घोषणा DST_TYPE_HAS_FW_3	32
#घोषणा DST_TYPE_HAS_FW_BUILD	64
#घोषणा DST_TYPE_HAS_OBS_REGS	128
#घोषणा DST_TYPE_HAS_INC_COUNT	256
#घोषणा DST_TYPE_HAS_MULTI_FE	512
#घोषणा DST_TYPE_HAS_NEWTUNE_2	1024
#घोषणा DST_TYPE_HAS_DBOARD	2048
#घोषणा DST_TYPE_HAS_VLF	4096

/*	Card capability list	*/

#घोषणा DST_TYPE_HAS_MAC	1
#घोषणा DST_TYPE_HAS_DISEQC3	2
#घोषणा DST_TYPE_HAS_DISEQC4	4
#घोषणा DST_TYPE_HAS_DISEQC5	8
#घोषणा DST_TYPE_HAS_MOTO	16
#घोषणा DST_TYPE_HAS_CA		32
#घोषणा	DST_TYPE_HAS_ANALOG	64	/*	Analog inमाला_दो	*/
#घोषणा DST_TYPE_HAS_SESSION	128

#घोषणा TUNER_TYPE_MULTI	1
#घोषणा TUNER_TYPE_UNKNOWN	2
/*	DVB-S		*/
#घोषणा TUNER_TYPE_L64724	4
#घोषणा TUNER_TYPE_STV0299	8
#घोषणा TUNER_TYPE_MB86A15	16

/*	DVB-T		*/
#घोषणा TUNER_TYPE_TDA10046	32

/*	ATSC		*/
#घोषणा TUNER_TYPE_NXT200x	64


#घोषणा RDC_8820_PIO_0_DISABLE	0
#घोषणा RDC_8820_PIO_0_ENABLE	1
#घोषणा RDC_8820_INT		2
#घोषणा RDC_8820_RESET		4

/*	DST Communication	*/
#घोषणा GET_REPLY		1
#घोषणा NO_REPLY		0

#घोषणा GET_ACK			1
#घोषणा FIXED_COMM		8

#घोषणा ACK			0xff

काष्ठा dst_state अणु

	काष्ठा i2c_adapter* i2c;

	काष्ठा bt878* bt;

	/* configuration settings */
	स्थिर काष्ठा dst_config* config;

	काष्ठा dvb_frontend frontend;

	/* निजी ASIC data */
	u8 tx_tuna[10];
	u8 rx_tuna[10];
	u8 rxbuffer[10];
	u8 diseq_flags;
	u8 dst_type;
	u32 type_flags;
	u32 frequency;		/* पूर्णांकermediate frequency in kHz क्रम QPSK */
	क्रमागत fe_spectral_inversion inversion;
	u32 symbol_rate;	/* symbol rate in Symbols per second */
	क्रमागत fe_code_rate fec;
	क्रमागत fe_sec_voltage voltage;
	क्रमागत fe_sec_tone_mode tone;
	u32 decode_freq;
	u8 decode_lock;
	u16 decode_strength;
	u16 decode_snr;
	अचिन्हित दीर्घ cur_jअगरf;
	u8 k22;
	u32 bandwidth;
	u32 dst_hw_cap;
	u8 dst_fw_version;
	क्रमागत fe_sec_mini_cmd minicmd;
	क्रमागत fe_modulation modulation;
	u8 messages[256];
	u8 mac_address[8];
	u8 fw_version[8];
	u8 card_info[8];
	u8 venकरोr[8];
	u8 board_info[8];
	u32 tuner_type;
	अक्षर *tuner_name;
	काष्ठा mutex dst_mutex;
	अक्षर fw_name[8];
	काष्ठा dvb_device *dst_ca;
पूर्ण;

काष्ठा tuner_types अणु
	u32 tuner_type;
	अक्षर *tuner_name;
	अक्षर *board_name;
	अक्षर *fw_name;
पूर्ण;

काष्ठा dst_types अणु
	अक्षर *device_id;
	पूर्णांक offset;
	u8 dst_type;
	u32 type_flags;
	u32 dst_feature;
	u32 tuner_type;
पूर्ण;

काष्ठा dst_config
अणु
	/* the ASIC i2c address */
	u8 demod_address;
पूर्ण;

पूर्णांक rdc_reset_state(काष्ठा dst_state *state);

पूर्णांक dst_रुको_dst_पढ़ोy(काष्ठा dst_state *state, u8 delay_mode);
पूर्णांक dst_pio_disable(काष्ठा dst_state *state);
पूर्णांक dst_error_recovery(काष्ठा dst_state* state);
पूर्णांक dst_error_bailout(काष्ठा dst_state *state);
पूर्णांक dst_comm_init(काष्ठा dst_state* state);

पूर्णांक ग_लिखो_dst(काष्ठा dst_state *state, u8 * data, u8 len);
पूर्णांक पढ़ो_dst(काष्ठा dst_state *state, u8 * ret, u8 len);
u8 dst_check_sum(u8 * buf, u32 len);
काष्ठा dst_state* dst_attach(काष्ठा dst_state* state, काष्ठा dvb_adapter *dvb_adapter);
काष्ठा dvb_device *dst_ca_attach(काष्ठा dst_state *state, काष्ठा dvb_adapter *dvb_adapter);


#पूर्ण_अगर // DST_COMMON_H
