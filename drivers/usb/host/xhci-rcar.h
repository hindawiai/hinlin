<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * drivers/usb/host/xhci-rcar.h
 *
 * Copyright (C) 2014 Renesas Electronics Corporation
 */

#अगर_अघोषित _XHCI_RCAR_H
#घोषणा _XHCI_RCAR_H

#घोषणा XHCI_RCAR_FIRMWARE_NAME_V1	"r8a779x_usb3_v1.dlmem"
#घोषणा XHCI_RCAR_FIRMWARE_NAME_V2	"r8a779x_usb3_v2.dlmem"
#घोषणा XHCI_RCAR_FIRMWARE_NAME_V3	"r8a779x_usb3_v3.dlmem"

#अगर IS_ENABLED(CONFIG_USB_XHCI_RCAR)
व्योम xhci_rcar_start(काष्ठा usb_hcd *hcd);
पूर्णांक xhci_rcar_init_quirk(काष्ठा usb_hcd *hcd);
पूर्णांक xhci_rcar_resume_quirk(काष्ठा usb_hcd *hcd);
#अन्यथा
अटल अंतरभूत व्योम xhci_rcar_start(काष्ठा usb_hcd *hcd)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक xhci_rcar_init_quirk(काष्ठा usb_hcd *hcd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xhci_rcar_resume_quirk(काष्ठा usb_hcd *hcd)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * On R-Car Gen2 and Gen3, the AC64 bit (bit 0) of HCCPARAMS1 is set
 * to 1. However, these SoCs करोn't support 64-bit address memory
 * poपूर्णांकers. So, this driver clears the AC64 bit of xhci->hcc_params
 * to call dma_set_coherent_mask(dev, DMA_BIT_MASK(32)) in
 * xhci_gen_setup() by using the XHCI_NO_64BIT_SUPPORT quirk.
 *
 * And, since the firmware/पूर्णांकernal CPU control the USBSTS.STS_HALT
 * and the process speed is करोwn when the roothub port enters U3,
 * दीर्घ delay क्रम the handshake of STS_HALT is neeed in xhci_suspend()
 * by using the XHCI_SLOW_SUSPEND quirk.
 */
#घोषणा SET_XHCI_PLAT_PRIV_FOR_RCAR(firmware)				\
	.firmware_name = firmware,					\
	.quirks = XHCI_NO_64BIT_SUPPORT | XHCI_TRUST_TX_LENGTH |	\
		  XHCI_SLOW_SUSPEND,					\
	.init_quirk = xhci_rcar_init_quirk,				\
	.plat_start = xhci_rcar_start,					\
	.resume_quirk = xhci_rcar_resume_quirk,

#पूर्ण_अगर /* _XHCI_RCAR_H */
