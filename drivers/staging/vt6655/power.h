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

#समावेश "device.h"

#घोषणा C_PWBT                   1000    /* micro sec. घातer up beक्रमe TBTT */
#घोषणा PS_FAST_INTERVAL         1       /* Fast घातer saving listen पूर्णांकerval */
#घोषणा PS_MAX_INTERVAL          4       /* MAX घातer saving listen पूर्णांकerval */

व्योम PSvDisablePowerSaving(काष्ठा vnt_निजी *priv);

व्योम PSvEnablePowerSaving(काष्ठा vnt_निजी *priv, अचिन्हित लघु wListenInterval);

bool PSbIsNextTBTTWakeUp(काष्ठा vnt_निजी *priv);

#पूर्ण_अगर /* __POWER_H__ */
