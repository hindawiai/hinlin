<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Standalone xHCI debug capability driver
 *
 * Copyright (C) 2016 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __LINUX_XHCI_DBGP_H
#घोषणा __LINUX_XHCI_DBGP_H

#अगर_घोषित CONFIG_EARLY_PRINTK_USB_XDBC
पूर्णांक __init early_xdbc_parse_parameter(अक्षर *s);
पूर्णांक __init early_xdbc_setup_hardware(व्योम);
व्योम __init early_xdbc_रेजिस्टर_console(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक __init early_xdbc_setup_hardware(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम __init early_xdbc_रेजिस्टर_console(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_EARLY_PRINTK_USB_XDBC */
#पूर्ण_अगर /* __LINUX_XHCI_DBGP_H */
