<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2010-2012 Broadcom. All rights reserved. */

#अगर_अघोषित VCHIQ_CONNECTED_H
#घोषणा VCHIQ_CONNECTED_H

/* ---- Include Files ----------------------------------------------------- */

/* ---- Constants and Types ---------------------------------------------- */

प्रकार व्योम (*VCHIQ_CONNECTED_CALLBACK_T)(व्योम);

/* ---- Variable Externs ------------------------------------------------- */

/* ---- Function Prototypes ---------------------------------------------- */

व्योम vchiq_add_connected_callback(VCHIQ_CONNECTED_CALLBACK_T callback);
व्योम vchiq_call_connected_callbacks(व्योम);

#पूर्ण_अगर /* VCHIQ_CONNECTED_H */
