<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  FM Driver क्रम Connectivity chip of Texas Instruments.
 *  FM RX module header.
 *
 *  Copyright (C) 2011 Texas Instruments
 */

#अगर_अघोषित _FMDRV_RX_H
#घोषणा _FMDRV_RX_H

पूर्णांक fm_rx_set_freq(काष्ठा fmdev *, u32);
पूर्णांक fm_rx_set_mute_mode(काष्ठा fmdev *, u8);
पूर्णांक fm_rx_set_stereo_mono(काष्ठा fmdev *, u16);
पूर्णांक fm_rx_set_rds_mode(काष्ठा fmdev *, u8);
पूर्णांक fm_rx_set_rds_प्रणाली(काष्ठा fmdev *, u8);
पूर्णांक fm_rx_set_volume(काष्ठा fmdev *, u16);
पूर्णांक fm_rx_set_rssi_threshold(काष्ठा fmdev *, लघु);
पूर्णांक fm_rx_set_region(काष्ठा fmdev *, u8);
पूर्णांक fm_rx_set_rfdepend_sofपंचांगute(काष्ठा fmdev *, u8);
पूर्णांक fm_rx_set_deemphasis_mode(काष्ठा fmdev *, u16);
पूर्णांक fm_rx_set_af_चयन(काष्ठा fmdev *, u8);

व्योम fm_rx_reset_rds_cache(काष्ठा fmdev *);
व्योम fm_rx_reset_station_info(काष्ठा fmdev *);

पूर्णांक fm_rx_seek(काष्ठा fmdev *, u32, u32, u32);

पूर्णांक fm_rx_get_rds_mode(काष्ठा fmdev *, u8 *);
पूर्णांक fm_rx_get_mute_mode(काष्ठा fmdev *, u8 *);
पूर्णांक fm_rx_get_volume(काष्ठा fmdev *, u16 *);
पूर्णांक fm_rx_get_band_freq_range(काष्ठा fmdev *,
					u32 *, u32 *);
पूर्णांक fm_rx_get_stereo_mono(काष्ठा fmdev *, u16 *);
पूर्णांक fm_rx_get_rssi_level(काष्ठा fmdev *, u16 *);
पूर्णांक fm_rx_get_rssi_threshold(काष्ठा fmdev *, लघु *);
पूर्णांक fm_rx_get_rfdepend_sofपंचांगute(काष्ठा fmdev *, u8 *);
पूर्णांक fm_rx_get_deemph_mode(काष्ठा fmdev *, u16 *);
पूर्णांक fm_rx_get_af_चयन(काष्ठा fmdev *, u8 *);
व्योम fm_rx_get_region(काष्ठा fmdev *, u8 *);

पूर्णांक fm_rx_set_chanl_spacing(काष्ठा fmdev *, u8);
पूर्णांक fm_rx_get_chanl_spacing(काष्ठा fmdev *, u8 *);
#पूर्ण_अगर

