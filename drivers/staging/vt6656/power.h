<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: घातer.h
 *
 * Purpose: Handles 802.11 घातer management  functions
 *
 * Author: Lynकरोn Chen
 *
 * Date: July 17, 2002
 *
 */

#अगर_अघोषित __POWER_H__
#घोषणा __POWER_H__

#घोषणा C_PWBT	1000 /* micro sec. घातer up beक्रमe TBTT */

पूर्णांक vnt_disable_घातer_saving(काष्ठा vnt_निजी *priv);
व्योम vnt_enable_घातer_saving(काष्ठा vnt_निजी *priv, u16 listen_पूर्णांकerval);
पूर्णांक vnt_next_tbtt_wakeup(काष्ठा vnt_निजी *priv);

#पूर्ण_अगर /* __POWER_H__ */
