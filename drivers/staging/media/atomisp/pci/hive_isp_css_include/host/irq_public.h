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

#अगर_अघोषित __IRQ_PUBLIC_H_INCLUDED__
#घोषणा __IRQ_PUBLIC_H_INCLUDED__

#समावेश <type_support.h>
#समावेश "system_local.h"

/*! Read the control रेजिस्टरs of IRQ[ID]

 \param	ID[in]				IRQ identअगरier
 \param	state[out]			irq controller state काष्ठाure

 \लeturn none, state = IRQ[ID].state
 */
व्योम irq_controller_get_state(स्थिर irq_ID_t ID,
			      काष्ठा irq_controller_state *state);

/*! Write to a control रेजिस्टर of IRQ[ID]

 \param	ID[in]				IRQ identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn none, IRQ[ID].ctrl[reg] = value
 */
STORAGE_CLASS_IRQ_H व्योम irq_reg_store(
    स्थिर irq_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर hrt_data		value);

/*! Read from a control रेजिस्टर of IRQ[ID]

 \param	ID[in]				IRQ identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn IRQ[ID].ctrl[reg]
 */
STORAGE_CLASS_IRQ_H hrt_data irq_reg_load(
    स्थिर irq_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg);

/*! Enable an IRQ channel of IRQ[ID] with a mode

 \param	ID[in]				IRQ (device) identअगरier
 \param	irq[in]				IRQ (channel) identअगरier

 \लeturn none, enable(IRQ[ID].channel[irq_ID])
 */
व्योम irq_enable_channel(
    स्थिर irq_ID_t				ID,
    स्थिर अचिन्हित पूर्णांक			irq_ID);

/*! Enable pulse पूर्णांकerrupts क्रम IRQ[ID] with a mode

 \param	ID[in]				IRQ (device) identअगरier
 \param	enable				enable/disable pulse पूर्णांकerrupts

 \लeturn none
 */
व्योम irq_enable_pulse(
    स्थिर irq_ID_t	ID,
    bool			pulse);

/*! Disable an IRQ channel of IRQ[ID]

 \param	ID[in]				IRQ (device) identअगरier
 \param	irq[in]				IRQ (channel) identअगरier

 \लeturn none, disable(IRQ[ID].channel[irq_ID])
 */
व्योम irq_disable_channel(
    स्थिर irq_ID_t				ID,
    स्थिर अचिन्हित पूर्णांक			irq);

/*! Clear the state of all IRQ channels of IRQ[ID]

 \param	ID[in]				IRQ (device) identअगरier

 \लeturn none, clear(IRQ[ID].channel[])
 */
व्योम irq_clear_all(
    स्थिर irq_ID_t				ID);

/*! Return the ID of a संकेतling IRQ channel of IRQ[ID]

 \param	ID[in]				IRQ (device) identअगरier
 \param irq_id[out]			active IRQ (channel) identअगरier

 \Note: This function operates as म_मोहर(), based on the वापस
  state the user is inक्रमmed अगर there are additional संकेतling
  channels

 \लeturn state(IRQ[ID])
 */
क्रमागत hrt_isp_css_irq_status irq_get_channel_id(
    स्थिर irq_ID_t				ID,
    अचिन्हित पूर्णांक				*irq_id);

/*! Raise an पूर्णांकerrupt on channel irq_id of device IRQ[ID]

 \param	ID[in]				IRQ (device) identअगरier
 \param	irq_id[in]			IRQ (channel) identअगरier

 \लeturn none, संकेत(IRQ[ID].channel[irq_id])
 */
व्योम irq_उठाओ(
    स्थिर irq_ID_t				ID,
    स्थिर irq_sw_channel_id_t	irq_id);

/*! Test अगर any IRQ channel of the भव super IRQ has उठाओd a संकेत

 \लeturn any(VIRQ.channel[irq_ID] != 0)
 */
bool any_virq_संकेत(व्योम);

/*! Enable an IRQ channel of the भव super IRQ

 \param	irq[in]				IRQ (channel) identअगरier
 \param	en[in]				predicate channel enable

 \लeturn none, VIRQ.channel[irq_ID].enable = en
 */
व्योम cnd_virq_enable_channel(
    स्थिर क्रमागत virq_id				irq_ID,
    स्थिर bool					en);

/*! Clear the state of all IRQ channels of the भव super IRQ

 \लeturn none, clear(VIRQ.channel[])
 */
व्योम virq_clear_all(व्योम);

/*! Clear the IRQ info state of the भव super IRQ

 \param irq_info[in/out]	The IRQ (channel) state

 \लeturn none
 */
व्योम virq_clear_info(काष्ठा virq_info *irq_info);

/*! Return the ID of a संकेतling IRQ channel of the भव super IRQ

 \param irq_id[out]			active IRQ (channel) identअगरier

 \Note: This function operates as म_मोहर(), based on the वापस
  state the user is inक्रमmed अगर there are additional संकेतling
  channels

 \लeturn state(IRQ[...])
 */
क्रमागत hrt_isp_css_irq_status virq_get_channel_id(
    क्रमागत virq_id					*irq_id);

/*! Return the IDs of all संकेतing IRQ channels of the भव super IRQ

 \param irq_info[out]		all active IRQ (channel) identअगरiers

 \Note: Unlike "irq_get_channel_id()" this function वापसs all
  channel संकेतing info. The new info is OR'd with the current
  info state. N.B. this is the same as repeatedly calling the function
  "irq_get_channel_id()" in a (non-blocked) handler routine

 \लeturn (error(state(IRQ[...]))
 */
क्रमागत hrt_isp_css_irq_status
virq_get_channel_संकेतs(काष्ठा virq_info *irq_info);

#पूर्ण_अगर /* __IRQ_PUBLIC_H_INCLUDED__ */
