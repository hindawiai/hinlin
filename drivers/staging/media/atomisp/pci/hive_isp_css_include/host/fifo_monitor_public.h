<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __FIFO_MONITOR_PUBLIC_H_INCLUDED__
#घोषणा __FIFO_MONITOR_PUBLIC_H_INCLUDED__

#समावेश "system_local.h"

प्रकार काष्ठा fअगरo_channel_state_s		fअगरo_channel_state_t;
प्रकार काष्ठा fअगरo_चयन_state_s		fअगरo_चयन_state_t;
प्रकार काष्ठा fअगरo_monitor_state_s		fअगरo_monitor_state_t;

/*! Set a fअगरo चयन multiplex

 \param	ID[in]				FIFO_MONITOR identअगरier
 \param	चयन_id[in]		fअगरo चयन identअगरier
 \param	sel[in]				fअगरo चयन selector

 \लeturn none, fअगरo_चयन[चयन_id].sel = sel
 */
STORAGE_CLASS_FIFO_MONITOR_H व्योम fअगरo_चयन_set(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर fअगरo_चयन_t			चयन_id,
    स्थिर hrt_data				sel);

/*! Get a fअगरo चयन multiplex

 \param	ID[in]				FIFO_MONITOR identअगरier
 \param	चयन_id[in]		fअगरo चयन identअगरier

 \लeturn fअगरo_चयन[चयन_id].sel
 */
STORAGE_CLASS_FIFO_MONITOR_H hrt_data fअगरo_चयन_get(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर fअगरo_चयन_t			चयन_id);

/*! Read the state of FIFO_MONITOR[ID]

 \param	ID[in]				FIFO_MONITOR identअगरier
 \param	state[out]			fअगरo monitor state काष्ठाure

 \लeturn none, state = FIFO_MONITOR[ID].state
 */
व्योम fअगरo_monitor_get_state(
    स्थिर fअगरo_monitor_ID_t		ID,
    fअगरo_monitor_state_t		*state);

/*! Read the state of a fअगरo channel

 \param	ID[in]				FIFO_MONITOR identअगरier
 \param	channel_id[in]		fअगरo channel identअगरier
 \param	state[out]			fअगरo channel state काष्ठाure

 \लeturn none, state = fअगरo_channel[channel_id].state
 */
व्योम fअगरo_channel_get_state(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर fअगरo_channel_t		channel_id,
    fअगरo_channel_state_t		*state);

/*! Read the state of a fअगरo चयन

 \param	ID[in]				FIFO_MONITOR identअगरier
 \param	चयन_id[in]		fअगरo चयन identअगरier
 \param	state[out]			fअगरo चयन state काष्ठाure

 \लeturn none, state = fअगरo_चयन[चयन_id].state
 */
व्योम fअगरo_चयन_get_state(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर fअगरo_चयन_t			चयन_id,
    fअगरo_चयन_state_t			*state);

/*! Write to a control रेजिस्टर of FIFO_MONITOR[ID]

 \param	ID[in]				FIFO_MONITOR identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn none, FIFO_MONITOR[ID].ctrl[reg] = value
 */
STORAGE_CLASS_FIFO_MONITOR_H व्योम fअगरo_monitor_reg_store(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक			reg,
    स्थिर hrt_data				value);

/*! Read from a control रेजिस्टर of FIFO_MONITOR[ID]

 \param	ID[in]				FIFO_MONITOR identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn FIFO_MONITOR[ID].ctrl[reg]
 */
STORAGE_CLASS_FIFO_MONITOR_H hrt_data fअगरo_monitor_reg_load(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक			reg);

#पूर्ण_अगर /* __FIFO_MONITOR_PUBLIC_H_INCLUDED__ */
