<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश "pci.h"
#समावेश "rtw8723de.h"

अटल स्थिर काष्ठा pci_device_id rtw_8723de_id_table[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_REALTEK, 0xD723),
		.driver_data = (kernel_uदीर्घ_t)&rtw8723d_hw_spec
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, rtw_8723de_id_table);

अटल काष्ठा pci_driver rtw_8723de_driver = अणु
	.name = "rtw_8723de",
	.id_table = rtw_8723de_id_table,
	.probe = rtw_pci_probe,
	.हटाओ = rtw_pci_हटाओ,
	.driver.pm = &rtw_pm_ops,
	.shutकरोwn = rtw_pci_shutकरोwn,
पूर्ण;
module_pci_driver(rtw_8723de_driver);

MODULE_AUTHOR("Realtek Corporation");
MODULE_DESCRIPTION("Realtek 802.11n wireless 8723de driver");
MODULE_LICENSE("Dual BSD/GPL");
