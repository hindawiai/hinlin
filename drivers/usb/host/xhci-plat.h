<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * xhci-plat.h - xHCI host controller driver platक्रमm Bus Glue.
 *
 * Copyright (C) 2015 Renesas Electronics Corporation
 */

#अगर_अघोषित _XHCI_PLAT_H
#घोषणा _XHCI_PLAT_H

#समावेश "xhci.h"	/* क्रम hcd_to_xhci() */

काष्ठा xhci_plat_priv अणु
	स्थिर अक्षर *firmware_name;
	अचिन्हित दीर्घ दीर्घ quirks;
	पूर्णांक (*plat_setup)(काष्ठा usb_hcd *);
	व्योम (*plat_start)(काष्ठा usb_hcd *);
	पूर्णांक (*init_quirk)(काष्ठा usb_hcd *);
	पूर्णांक (*suspend_quirk)(काष्ठा usb_hcd *);
	पूर्णांक (*resume_quirk)(काष्ठा usb_hcd *);
पूर्ण;

#घोषणा hcd_to_xhci_priv(h) ((काष्ठा xhci_plat_priv *)hcd_to_xhci(h)->priv)
#घोषणा xhci_to_priv(x) ((काष्ठा xhci_plat_priv *)(x)->priv)
#पूर्ण_अगर	/* _XHCI_PLAT_H */
