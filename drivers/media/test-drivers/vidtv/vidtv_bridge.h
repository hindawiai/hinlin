<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * The Virtual DTV test driver serves as a reference DVB driver and helps
 * validate the existing APIs in the media subप्रणाली. It can also aid
 * developers working on userspace applications.
 *
 * When this module is loaded, it will attempt to modprobe 'dvb_vidtv_tuner' and 'dvb_vidtv_demod'.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#अगर_अघोषित VIDTV_BRIDGE_H
#घोषणा VIDTV_BRIDGE_H

/*
 * For now, only one frontend is supported. See vidtv_start_streaming()
 */
#घोषणा NUM_FE 1
#घोषणा VIDTV_PDEV_NAME "vidtv"

#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/media-device.h>

#समावेश "vidtv_mux.h"

/**
 * काष्ठा vidtv_dvb - Vidtv bridge state
 * @pdev: The platक्रमm device. Obtained when the bridge is probed.
 * @fe: The frontends. Obtained when probing the demodulator modules.
 * @adapter: Represents a DTV adapter. See 'dvb_register_adapter'.
 * @demux: The demux used by the dvb_dmx_swfilter_packets() call.
 * @dmx_dev: Represents a demux device.
 * @dmx_fe: The frontends associated with the demux.
 * @i2c_adapter: The i2c_adapter associated with the bridge driver.
 * @i2c_client_demod: The i2c_clients associated with the demodulator modules.
 * @i2c_client_tuner: The i2c_clients associated with the tuner modules.
 * @nfeeds: The number of feeds active.
 * @feed_lock: Protects access to the start/stop stream logic/data.
 * @streaming: Whether we are streaming now.
 * @mux: The असलtraction responsible क्रम delivering MPEG TS packets to the bridge.
 * @mdev: The media_device काष्ठा क्रम media controller support.
 */
काष्ठा vidtv_dvb अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा dvb_frontend *fe[NUM_FE];
	काष्ठा dvb_adapter adapter;
	काष्ठा dvb_demux demux;
	काष्ठा dmxdev dmx_dev;
	काष्ठा dmx_frontend dmx_fe[NUM_FE];
	काष्ठा i2c_adapter i2c_adapter;
	काष्ठा i2c_client *i2c_client_demod[NUM_FE];
	काष्ठा i2c_client *i2c_client_tuner[NUM_FE];

	u32 nfeeds;
	काष्ठा mutex feed_lock; /* Protects access to the start/stop stream logic/data. */

	bool streaming;

	काष्ठा vidtv_mux *mux;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	काष्ठा media_device mdev;
#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER_DVB */
पूर्ण;

#पूर्ण_अगर // VIDTV_BRIDG_H
