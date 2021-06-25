<शैली गुरु>
/******************************************************************************
 * acpi.h
 * acpi file क्रम करोमुख्य 0 kernel
 *
 * Copyright (c) 2011 Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
 * Copyright (c) 2011 Yu Ke <ke.yu@पूर्णांकel.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित _XEN_ACPI_H
#घोषणा _XEN_ACPI_H

#समावेश <linux/types.h>

#अगर_घोषित CONFIG_XEN_DOM0
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <xen/xen.h>
#समावेश <linux/acpi.h>

पूर्णांक xen_acpi_notअगरy_hypervisor_sleep(u8 sleep_state,
				     u32 pm1a_cnt, u32 pm1b_cnd);
पूर्णांक xen_acpi_notअगरy_hypervisor_extended_sleep(u8 sleep_state,
				     u32 val_a, u32 val_b);

अटल अंतरभूत पूर्णांक xen_acpi_suspend_lowlevel(व्योम)
अणु
	/*
	* Xen will save and restore CPU context, so
	* we can skip that and just go straight to
	* the suspend.
	*/
	acpi_enter_sleep_state(ACPI_STATE_S3);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xen_acpi_sleep_रेजिस्टर(व्योम)
अणु
	अगर (xen_initial_करोमुख्य()) अणु
		acpi_os_set_prepare_sleep(
			&xen_acpi_notअगरy_hypervisor_sleep);
		acpi_os_set_prepare_extended_sleep(
			&xen_acpi_notअगरy_hypervisor_extended_sleep);

		acpi_suspend_lowlevel = xen_acpi_suspend_lowlevel;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम xen_acpi_sleep_रेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* _XEN_ACPI_H */
