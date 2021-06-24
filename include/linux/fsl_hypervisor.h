<शैली गुरु>
/*
 * Freescale hypervisor ioctl and kernel पूर्णांकerface
 *
 * Copyright (C) 2008-2011 Freescale Semiconductor, Inc.
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * This software is provided by Freescale Semiconductor "as is" and any
 * express or implied warranties, including, but not limited to, the implied
 * warranties of merchantability and fitness क्रम a particular purpose are
 * disclaimed. In no event shall Freescale Semiconductor be liable क्रम any
 * direct, indirect, incidental, special, exemplary, or consequential damages
 * (including, but not limited to, procurement of substitute goods or services;
 * loss of use, data, or profits; or business पूर्णांकerruption) however caused and
 * on any theory of liability, whether in contract, strict liability, or tort
 * (including negligence or otherwise) arising in any way out of the use of this
 * software, even अगर advised of the possibility of such damage.
 *
 * This file is used by the Freescale hypervisor management driver.  It can
 * also be included by applications that need to communicate with the driver
 * via the ioctl पूर्णांकerface.
 */
#अगर_अघोषित FSL_HYPERVISOR_H
#घोषणा FSL_HYPERVISOR_H

#समावेश <uapi/linux/fsl_hypervisor.h>


/**
 * fsl_hv_event_रेजिस्टर() - रेजिस्टर a callback क्रम failover events
 * @nb: poपूर्णांकer to caller-supplied notअगरier_block काष्ठाure
 *
 * This function is called by device drivers to रेजिस्टर their callback
 * functions क्रम fail-over events.
 *
 * The caller should allocate a notअगरier_block object and initialize the
 * 'priority' and 'notifier_call' fields.
 */
पूर्णांक fsl_hv_failover_रेजिस्टर(काष्ठा notअगरier_block *nb);

/**
 * fsl_hv_event_unरेजिस्टर() - unरेजिस्टर a callback क्रम failover events
 * @nb: the same 'nb' used in previous fsl_hv_failover_रेजिस्टर call
 */
पूर्णांक fsl_hv_failover_unरेजिस्टर(काष्ठा notअगरier_block *nb);

#पूर्ण_अगर
