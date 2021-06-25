<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * bebob.h - a part of driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#अगर_अघोषित SOUND_BEBOB_H_INCLUDED
#घोषणा SOUND_BEBOB_H_INCLUDED

#समावेश <linux/compat.h>
#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/info.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/firewire.h>
#समावेश <sound/hwdep.h>

#समावेश "../lib.h"
#समावेश "../fcp.h"
#समावेश "../packets-buffer.h"
#समावेश "../iso-resources.h"
#समावेश "../amdtp-am824.h"
#समावेश "../cmp.h"

/* basic रेजिस्टर addresses on DM1000/DM1100/DM1500 */
#घोषणा BEBOB_ADDR_REG_INFO	0xffffc8020000ULL
#घोषणा BEBOB_ADDR_REG_REQ	0xffffc8021000ULL

काष्ठा snd_bebob;

#घोषणा SND_BEBOB_STRM_FMT_ENTRIES	7
काष्ठा snd_bebob_stream_क्रमmation अणु
	अचिन्हित पूर्णांक pcm;
	अचिन्हित पूर्णांक midi;
पूर्ण;
/* this is a lookup table क्रम index of stream क्रमmations */
बाह्य स्थिर अचिन्हित पूर्णांक snd_bebob_rate_table[SND_BEBOB_STRM_FMT_ENTRIES];

/* device specअगरic operations */
क्रमागत snd_bebob_घड़ी_प्रकारype अणु
	SND_BEBOB_CLOCK_TYPE_INTERNAL = 0,
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,
	SND_BEBOB_CLOCK_TYPE_SYT,
पूर्ण;
काष्ठा snd_bebob_घड़ी_spec अणु
	अचिन्हित पूर्णांक num;
	स्थिर अक्षर *स्थिर *labels;
	स्थिर क्रमागत snd_bebob_घड़ी_प्रकारype *types;
	पूर्णांक (*get)(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक *id);
पूर्ण;
काष्ठा snd_bebob_rate_spec अणु
	पूर्णांक (*get)(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक *rate);
	पूर्णांक (*set)(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक rate);
पूर्ण;
काष्ठा snd_bebob_meter_spec अणु
	अचिन्हित पूर्णांक num;
	स्थिर अक्षर *स्थिर *labels;
	पूर्णांक (*get)(काष्ठा snd_bebob *bebob, u32 *target, अचिन्हित पूर्णांक size);
पूर्ण;
काष्ठा snd_bebob_spec अणु
	स्थिर काष्ठा snd_bebob_घड़ी_spec *घड़ी;
	स्थिर काष्ठा snd_bebob_rate_spec *rate;
	स्थिर काष्ठा snd_bebob_meter_spec *meter;
पूर्ण;

काष्ठा snd_bebob अणु
	काष्ठा snd_card *card;
	काष्ठा fw_unit *unit;
	पूर्णांक card_index;

	काष्ठा mutex mutex;
	spinlock_t lock;

	bool रेजिस्टरed;
	काष्ठा delayed_work dwork;

	स्थिर काष्ठा ieee1394_device_id *entry;
	स्थिर काष्ठा snd_bebob_spec *spec;

	अचिन्हित पूर्णांक midi_input_ports;
	अचिन्हित पूर्णांक midi_output_ports;

	काष्ठा amdtp_stream tx_stream;
	काष्ठा amdtp_stream rx_stream;
	काष्ठा cmp_connection out_conn;
	काष्ठा cmp_connection in_conn;
	अचिन्हित पूर्णांक substreams_counter;

	काष्ठा snd_bebob_stream_क्रमmation
		tx_stream_क्रमmations[SND_BEBOB_STRM_FMT_ENTRIES];
	काष्ठा snd_bebob_stream_क्रमmation
		rx_stream_क्रमmations[SND_BEBOB_STRM_FMT_ENTRIES];

	पूर्णांक sync_input_plug;

	/* क्रम uapi */
	पूर्णांक dev_lock_count;
	bool dev_lock_changed;
	रुको_queue_head_t hwdep_रुको;

	/* क्रम M-Audio special devices */
	व्योम *maudio_special_quirk;

	/* For BeBoB version quirk. */
	अचिन्हित पूर्णांक version;

	काष्ठा amdtp_करोमुख्य करोमुख्य;
पूर्ण;

अटल अंतरभूत पूर्णांक
snd_bebob_पढ़ो_block(काष्ठा fw_unit *unit, u64 addr, व्योम *buf, पूर्णांक size)
अणु
	वापस snd_fw_transaction(unit, TCODE_READ_BLOCK_REQUEST,
				  BEBOB_ADDR_REG_INFO + addr,
				  buf, size, 0);
पूर्ण

अटल अंतरभूत पूर्णांक
snd_bebob_पढ़ो_quad(काष्ठा fw_unit *unit, u64 addr, u32 *buf)
अणु
	वापस snd_fw_transaction(unit, TCODE_READ_QUADLET_REQUEST,
				  BEBOB_ADDR_REG_INFO + addr,
				  (व्योम *)buf, माप(u32), 0);
पूर्ण

/* AV/C Audio Subunit Specअगरication 1.0 (Oct 2000, 1394TA) */
पूर्णांक avc_audio_set_selector(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक subunit_id,
			   अचिन्हित पूर्णांक fb_id, अचिन्हित पूर्णांक num);
पूर्णांक avc_audio_get_selector(काष्ठा fw_unit *unit, अचिन्हित  पूर्णांक subunit_id,
			   अचिन्हित पूर्णांक fb_id, अचिन्हित पूर्णांक *num);

/*
 * AVC command extensions, AV/C Unit and Subunit, Revision 17
 * (Nov 2003, BridgeCo)
 */
#घोषणा	AVC_BRIDGECO_ADDR_BYTES	6
क्रमागत avc_bridgeco_plug_dir अणु
	AVC_BRIDGECO_PLUG_सूची_IN	= 0x00,
	AVC_BRIDGECO_PLUG_सूची_OUT	= 0x01
पूर्ण;
क्रमागत avc_bridgeco_plug_mode अणु
	AVC_BRIDGECO_PLUG_MODE_UNIT		= 0x00,
	AVC_BRIDGECO_PLUG_MODE_SUBUNIT		= 0x01,
	AVC_BRIDGECO_PLUG_MODE_FUNCTION_BLOCK	= 0x02
पूर्ण;
क्रमागत avc_bridgeco_plug_unit अणु
	AVC_BRIDGECO_PLUG_UNIT_ISOC	= 0x00,
	AVC_BRIDGECO_PLUG_UNIT_EXT	= 0x01,
	AVC_BRIDGECO_PLUG_UNIT_ASYNC	= 0x02
पूर्ण;
क्रमागत avc_bridgeco_plug_type अणु
	AVC_BRIDGECO_PLUG_TYPE_ISOC	= 0x00,
	AVC_BRIDGECO_PLUG_TYPE_ASYNC	= 0x01,
	AVC_BRIDGECO_PLUG_TYPE_MIDI	= 0x02,
	AVC_BRIDGECO_PLUG_TYPE_SYNC	= 0x03,
	AVC_BRIDGECO_PLUG_TYPE_ANA	= 0x04,
	AVC_BRIDGECO_PLUG_TYPE_DIG	= 0x05,
	AVC_BRIDGECO_PLUG_TYPE_ADDITION	= 0x06
पूर्ण;
अटल अंतरभूत व्योम
avc_bridgeco_fill_unit_addr(u8 buf[AVC_BRIDGECO_ADDR_BYTES],
			    क्रमागत avc_bridgeco_plug_dir dir,
			    क्रमागत avc_bridgeco_plug_unit unit,
			    अचिन्हित पूर्णांक pid)
अणु
	buf[0] = 0xff;	/* Unit */
	buf[1] = dir;
	buf[2] = AVC_BRIDGECO_PLUG_MODE_UNIT;
	buf[3] = unit;
	buf[4] = 0xff & pid;
	buf[5] = 0xff;	/* reserved */
पूर्ण
अटल अंतरभूत व्योम
avc_bridgeco_fill_msu_addr(u8 buf[AVC_BRIDGECO_ADDR_BYTES],
			   क्रमागत avc_bridgeco_plug_dir dir,
			   अचिन्हित पूर्णांक pid)
अणु
	buf[0] = 0x60;	/* Music subunit */
	buf[1] = dir;
	buf[2] = AVC_BRIDGECO_PLUG_MODE_SUBUNIT;
	buf[3] = 0xff & pid;
	buf[4] = 0xff;	/* reserved */
	buf[5] = 0xff;	/* reserved */
पूर्ण
पूर्णांक avc_bridgeco_get_plug_ch_pos(काष्ठा fw_unit *unit,
				 u8 addr[AVC_BRIDGECO_ADDR_BYTES],
				 u8 *buf, अचिन्हित पूर्णांक len);
पूर्णांक avc_bridgeco_get_plug_type(काष्ठा fw_unit *unit,
			       u8 addr[AVC_BRIDGECO_ADDR_BYTES],
			       क्रमागत avc_bridgeco_plug_type *type);
पूर्णांक avc_bridgeco_get_plug_ch_count(काष्ठा fw_unit *unit, u8 addr[AVC_BRIDGECO_ADDR_BYTES],
				   अचिन्हित पूर्णांक *ch_count);
पूर्णांक avc_bridgeco_get_plug_section_type(काष्ठा fw_unit *unit,
				       u8 addr[AVC_BRIDGECO_ADDR_BYTES],
				       अचिन्हित पूर्णांक id, u8 *type);
पूर्णांक avc_bridgeco_get_plug_input(काष्ठा fw_unit *unit,
				u8 addr[AVC_BRIDGECO_ADDR_BYTES],
				u8 input[7]);
पूर्णांक avc_bridgeco_get_plug_strm_fmt(काष्ठा fw_unit *unit,
				   u8 addr[AVC_BRIDGECO_ADDR_BYTES], u8 *buf,
				   अचिन्हित पूर्णांक *len, अचिन्हित पूर्णांक eid);

/* क्रम AMDTP streaming */
पूर्णांक snd_bebob_stream_get_rate(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक *rate);
पूर्णांक snd_bebob_stream_set_rate(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक rate);
पूर्णांक snd_bebob_stream_get_घड़ी_src(काष्ठा snd_bebob *bebob,
				   क्रमागत snd_bebob_घड़ी_प्रकारype *src);
पूर्णांक snd_bebob_stream_discover(काष्ठा snd_bebob *bebob);
पूर्णांक snd_bebob_stream_init_duplex(काष्ठा snd_bebob *bebob);
पूर्णांक snd_bebob_stream_reserve_duplex(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक rate,
				    अचिन्हित पूर्णांक frames_per_period,
				    अचिन्हित पूर्णांक frames_per_buffer);
पूर्णांक snd_bebob_stream_start_duplex(काष्ठा snd_bebob *bebob);
व्योम snd_bebob_stream_stop_duplex(काष्ठा snd_bebob *bebob);
व्योम snd_bebob_stream_destroy_duplex(काष्ठा snd_bebob *bebob);

व्योम snd_bebob_stream_lock_changed(काष्ठा snd_bebob *bebob);
पूर्णांक snd_bebob_stream_lock_try(काष्ठा snd_bebob *bebob);
व्योम snd_bebob_stream_lock_release(काष्ठा snd_bebob *bebob);

व्योम snd_bebob_proc_init(काष्ठा snd_bebob *bebob);

पूर्णांक snd_bebob_create_midi_devices(काष्ठा snd_bebob *bebob);

पूर्णांक snd_bebob_create_pcm_devices(काष्ठा snd_bebob *bebob);

पूर्णांक snd_bebob_create_hwdep_device(काष्ठा snd_bebob *bebob);

/* model specअगरic operations */
बाह्य स्थिर काष्ठा snd_bebob_spec phase88_rack_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec yamaha_terratec_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec saffirepro_26_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec saffirepro_10_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec saffire_le_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec saffire_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec maudio_fw410_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec maudio_audiophile_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec maudio_solo_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec maudio_ozonic_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec maudio_nrv10_spec;
बाह्य स्थिर काष्ठा snd_bebob_spec maudio_special_spec;
पूर्णांक snd_bebob_maudio_special_discover(काष्ठा snd_bebob *bebob, bool is1814);
पूर्णांक snd_bebob_maudio_load_firmware(काष्ठा fw_unit *unit);

#घोषणा SND_BEBOB_DEV_ENTRY(venकरोr, model, data) \
अणु \
	.match_flags	= IEEE1394_MATCH_VENDOR_ID | \
			  IEEE1394_MATCH_MODEL_ID, \
	.venकरोr_id	= venकरोr, \
	.model_id	= model, \
	.driver_data	= (kernel_uदीर्घ_t)data \
पूर्ण

#पूर्ण_अगर
