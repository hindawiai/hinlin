<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tw9910 Driver header
 *
 * Copyright (C) 2008 Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 *
 * Based on ov772x.h
 *
 * Copyright (C) Kuninori Morimoto <morimoto.kuninori@renesas.com>
 */

#अगर_अघोषित __TW9910_H__
#घोषणा __TW9910_H__

/* MPOUT (multi-purpose output) pin functions */
क्रमागत tw9910_mpout_pin अणु
	TW9910_MPO_VLOSS,
	TW9910_MPO_HLOCK,
	TW9910_MPO_SLOCK,
	TW9910_MPO_VLOCK,
	TW9910_MPO_MONO,
	TW9910_MPO_DET50,
	TW9910_MPO_FIELD,
	TW9910_MPO_RTCO,
पूर्ण;

/**
 * काष्ठा tw9910_video_info - tw9910 driver पूर्णांकerface काष्ठाure
 * @buswidth:		Parallel data bus width (8 or 16).
 * @mpout:		Selected function of MPOUT (multi-purpose output) pin.
 *			See क्रमागत tw9910_mpout_pin
 */
काष्ठा tw9910_video_info अणु
	अचिन्हित दीर्घ		buswidth;
	क्रमागत tw9910_mpout_pin	mpout;
पूर्ण;


#पूर्ण_अगर /* __TW9910_H__ */
