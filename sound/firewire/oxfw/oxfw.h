<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * oxfw.h - a part of driver क्रम OXFW970/971 based devices
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/info.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/firewire.h>
#समावेश <sound/hwdep.h>

#समावेश "../lib.h"
#समावेश "../fcp.h"
#समावेश "../packets-buffer.h"
#समावेश "../iso-resources.h"
#समावेश "../amdtp-am824.h"
#समावेश "../cmp.h"

/* This is an arbitrary number क्रम convinience. */
#घोषणा	SND_OXFW_STREAM_FORMAT_ENTRIES	10
काष्ठा snd_oxfw अणु
	काष्ठा snd_card *card;
	काष्ठा fw_unit *unit;
	काष्ठा mutex mutex;
	spinlock_t lock;

	bool रेजिस्टरed;
	काष्ठा delayed_work dwork;

	bool wrong_dbs;
	bool has_output;
	bool has_input;
	u8 *tx_stream_क्रमmats[SND_OXFW_STREAM_FORMAT_ENTRIES];
	u8 *rx_stream_क्रमmats[SND_OXFW_STREAM_FORMAT_ENTRIES];
	bool assumed;
	काष्ठा cmp_connection out_conn;
	काष्ठा cmp_connection in_conn;
	काष्ठा amdtp_stream tx_stream;
	काष्ठा amdtp_stream rx_stream;
	अचिन्हित पूर्णांक substreams_count;

	अचिन्हित पूर्णांक midi_input_ports;
	अचिन्हित पूर्णांक midi_output_ports;

	पूर्णांक dev_lock_count;
	bool dev_lock_changed;
	रुको_queue_head_t hwdep_रुको;

	स्थिर काष्ठा ieee1394_device_id *entry;
	व्योम *spec;

	काष्ठा amdtp_करोमुख्य करोमुख्य;
पूर्ण;

/*
 * AV/C Stream Format Inक्रमmation Specअगरication 1.1 Working Draft
 * (Apr 2005, 1394TA)
 */
पूर्णांक avc_stream_set_क्रमmat(काष्ठा fw_unit *unit, क्रमागत avc_general_plug_dir dir,
			  अचिन्हित पूर्णांक pid, u8 *क्रमmat, अचिन्हित पूर्णांक len);
पूर्णांक avc_stream_get_क्रमmat(काष्ठा fw_unit *unit,
			  क्रमागत avc_general_plug_dir dir, अचिन्हित पूर्णांक pid,
			  u8 *buf, अचिन्हित पूर्णांक *len, अचिन्हित पूर्णांक eid);
अटल अंतरभूत पूर्णांक
avc_stream_get_क्रमmat_single(काष्ठा fw_unit *unit,
			     क्रमागत avc_general_plug_dir dir, अचिन्हित पूर्णांक pid,
			     u8 *buf, अचिन्हित पूर्णांक *len)
अणु
	वापस avc_stream_get_क्रमmat(unit, dir, pid, buf, len, 0xff);
पूर्ण
अटल अंतरभूत पूर्णांक
avc_stream_get_क्रमmat_list(काष्ठा fw_unit *unit,
			   क्रमागत avc_general_plug_dir dir, अचिन्हित पूर्णांक pid,
			   u8 *buf, अचिन्हित पूर्णांक *len,
			   अचिन्हित पूर्णांक eid)
अणु
	वापस avc_stream_get_क्रमmat(unit, dir, pid, buf, len, eid);
पूर्ण

/*
 * AV/C Digital Interface Command Set General Specअगरication 4.2
 * (Sep 2004, 1394TA)
 */
पूर्णांक avc_general_inquiry_sig_fmt(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक rate,
				क्रमागत avc_general_plug_dir dir,
				अचिन्हित लघु pid);

पूर्णांक snd_oxfw_stream_init_duplex(काष्ठा snd_oxfw *oxfw);
पूर्णांक snd_oxfw_stream_reserve_duplex(काष्ठा snd_oxfw *oxfw,
				   काष्ठा amdtp_stream *stream,
				   अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक pcm_channels,
				   अचिन्हित पूर्णांक frames_per_period,
				   अचिन्हित पूर्णांक frames_per_buffer);
पूर्णांक snd_oxfw_stream_start_duplex(काष्ठा snd_oxfw *oxfw);
व्योम snd_oxfw_stream_stop_duplex(काष्ठा snd_oxfw *oxfw);
व्योम snd_oxfw_stream_destroy_duplex(काष्ठा snd_oxfw *oxfw);
व्योम snd_oxfw_stream_update_duplex(काष्ठा snd_oxfw *oxfw);

काष्ठा snd_oxfw_stream_क्रमmation अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक pcm;
	अचिन्हित पूर्णांक midi;
पूर्ण;
पूर्णांक snd_oxfw_stream_parse_क्रमmat(u8 *क्रमmat,
				 काष्ठा snd_oxfw_stream_क्रमmation *क्रमmation);
पूर्णांक snd_oxfw_stream_get_current_क्रमmation(काष्ठा snd_oxfw *oxfw,
				क्रमागत avc_general_plug_dir dir,
				काष्ठा snd_oxfw_stream_क्रमmation *क्रमmation);

पूर्णांक snd_oxfw_stream_discover(काष्ठा snd_oxfw *oxfw);

व्योम snd_oxfw_stream_lock_changed(काष्ठा snd_oxfw *oxfw);
पूर्णांक snd_oxfw_stream_lock_try(काष्ठा snd_oxfw *oxfw);
व्योम snd_oxfw_stream_lock_release(काष्ठा snd_oxfw *oxfw);

पूर्णांक snd_oxfw_create_pcm(काष्ठा snd_oxfw *oxfw);

व्योम snd_oxfw_proc_init(काष्ठा snd_oxfw *oxfw);

पूर्णांक snd_oxfw_create_midi(काष्ठा snd_oxfw *oxfw);

पूर्णांक snd_oxfw_create_hwdep(काष्ठा snd_oxfw *oxfw);

पूर्णांक snd_oxfw_add_spkr(काष्ठा snd_oxfw *oxfw, bool is_lacie);
पूर्णांक snd_oxfw_scs1x_add(काष्ठा snd_oxfw *oxfw);
व्योम snd_oxfw_scs1x_update(काष्ठा snd_oxfw *oxfw);
