<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2014 Marvell
 *
 * Gregory Clement <gregory.clement@मुक्त-electrons.com>
 */

#अगर_अघोषित __LINUX_XHCI_MVEBU_H
#घोषणा __LINUX_XHCI_MVEBU_H

काष्ठा usb_hcd;

#अगर IS_ENABLED(CONFIG_USB_XHCI_MVEBU)
पूर्णांक xhci_mvebu_mbus_init_quirk(काष्ठा usb_hcd *hcd);
पूर्णांक xhci_mvebu_a3700_plat_setup(काष्ठा usb_hcd *hcd);
पूर्णांक xhci_mvebu_a3700_init_quirk(काष्ठा usb_hcd *hcd);
#अन्यथा
अटल अंतरभूत पूर्णांक xhci_mvebu_mbus_init_quirk(काष्ठा usb_hcd *hcd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xhci_mvebu_a3700_plat_setup(काष्ठा usb_hcd *hcd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xhci_mvebu_a3700_init_quirk(काष्ठा usb_hcd *hcd)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __LINUX_XHCI_MVEBU_H */
