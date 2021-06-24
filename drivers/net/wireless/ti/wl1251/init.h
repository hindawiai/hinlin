<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1251
 *
 * Copyright (C) 2009 Nokia Corporation
 */

#अगर_अघोषित __WL1251_INIT_H__
#घोषणा __WL1251_INIT_H__

#समावेश "wl1251.h"

क्रमागत अणु
	/* best efक्रमt/legacy */
	AC_BE = 0,

	/* background */
	AC_BK = 1,

	/* video */
	AC_VI = 2,

	/* voice */
	AC_VO = 3,

	/* broadcast dummy access category */
	AC_BCAST = 4,

	NUM_ACCESS_CATEGORIES = 4
पूर्ण;

/* following are defult values क्रम the IE fields*/
#घोषणा CWMIN_BK  15
#घोषणा CWMIN_BE  15
#घोषणा CWMIN_VI  7
#घोषणा CWMIN_VO  3
#घोषणा CWMAX_BK  1023
#घोषणा CWMAX_BE  63
#घोषणा CWMAX_VI  15
#घोषणा CWMAX_VO  7

/* slot number setting to start transmission at PIFS पूर्णांकerval */
#घोषणा AIFS_PIFS 1

/*
 * slot number setting to start transmission at DIFS पूर्णांकerval - normal DCF
 * access
 */
#घोषणा AIFS_DIFS 2

#घोषणा AIFSN_BK  7
#घोषणा AIFSN_BE  3
#घोषणा AIFSN_VI  AIFS_PIFS
#घोषणा AIFSN_VO  AIFS_PIFS
#घोषणा TXOP_BK   0
#घोषणा TXOP_BE   0
#घोषणा TXOP_VI   3008
#घोषणा TXOP_VO   1504

पूर्णांक wl1251_hw_init_hwenc_config(काष्ठा wl1251 *wl);
पूर्णांक wl1251_hw_init_ढाँचाs_config(काष्ठा wl1251 *wl);
पूर्णांक wl1251_hw_init_rx_config(काष्ठा wl1251 *wl, u32 config, u32 filter);
पूर्णांक wl1251_hw_init_phy_config(काष्ठा wl1251 *wl);
पूर्णांक wl1251_hw_init_beacon_filter(काष्ठा wl1251 *wl);
पूर्णांक wl1251_hw_init_pta(काष्ठा wl1251 *wl);
पूर्णांक wl1251_hw_init_energy_detection(काष्ठा wl1251 *wl);
पूर्णांक wl1251_hw_init_beacon_broadcast(काष्ठा wl1251 *wl);
पूर्णांक wl1251_hw_init_घातer_auth(काष्ठा wl1251 *wl);
पूर्णांक wl1251_hw_init_mem_config(काष्ठा wl1251 *wl);
पूर्णांक wl1251_hw_init(काष्ठा wl1251 *wl);

#पूर्ण_अगर
