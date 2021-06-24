<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश "pci.h"
#समावेश "rtw8821ce.h"

अटल स्थिर काष्ठा pci_device_id rtw_8821ce_id_table[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_REALTEK, 0xC821),
		.driver_data = (kernel_uदीर्घ_t)&rtw8821c_hw_spec
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, rtw_8821ce_id_table);

अटल काष्ठा pci_driver rtw_8821ce_driver = अणु
	.name = "rtw_8821ce",
	.id_table = rtw_8821ce_id_table,
	.probe = rtw_pci_probe,
	.हटाओ = rtw_pci_हटाओ,
	.driver.pm = &rtw_pm_ops,
	.shutकरोwn = rtw_pci_shutकरोwn,
पूर्ण;
module_pci_driver(rtw_8821ce_driver);

MODULE_AUTHOR("Realtek Corporation");
MODULE_DESCRIPTION("Realtek 802.11ac wireless 8821ce driver");
MODULE_LICENSE("Dual BSD/GPL");
