<शैली गुरु>
/*
 * IBM PowerPC eBus Infraकाष्ठाure Support.
 *
 * Copyright (c) 2005 IBM Corporation
 *  Joachim Fenkes <fenkes@de.ibm.com>
 *  Heiko J Schick <schickhj@de.ibm.com>
 *
 * All rights reserved.
 *
 * This source code is distributed under a dual license of GPL v2.0 and OpenIB
 * BSD.
 *
 * OpenIB BSD License
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary क्रमm must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the करोcumentation
 * and/or other materials
 * provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _ASM_EBUS_H
#घोषणा _ASM_EBUS_H
#अगर_घोषित __KERNEL__

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>

बाह्य काष्ठा bus_type ibmebus_bus_type;

पूर्णांक ibmebus_रेजिस्टर_driver(काष्ठा platक्रमm_driver *drv);
व्योम ibmebus_unरेजिस्टर_driver(काष्ठा platक्रमm_driver *drv);

पूर्णांक ibmebus_request_irq(u32 ist, irq_handler_t handler,
			अचिन्हित दीर्घ irq_flags, स्थिर अक्षर *devname,
			व्योम *dev_id);
व्योम ibmebus_मुक्त_irq(u32 ist, व्योम *dev_id);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_IBMEBUS_H */
