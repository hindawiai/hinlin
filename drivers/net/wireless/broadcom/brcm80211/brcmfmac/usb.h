<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2011 Broadcom Corporation
 */
#अगर_अघोषित BRCMFMAC_USB_H
#घोषणा BRCMFMAC_USB_H

क्रमागत brcmf_usb_state अणु
	BRCMFMAC_USB_STATE_DOWN,
	BRCMFMAC_USB_STATE_DL_FAIL,
	BRCMFMAC_USB_STATE_DL_DONE,
	BRCMFMAC_USB_STATE_UP,
	BRCMFMAC_USB_STATE_SLEEP
पूर्ण;

काष्ठा brcmf_stats अणु
	u32 tx_ctlpkts;
	u32 tx_ctlerrs;
	u32 rx_ctlpkts;
	u32 rx_ctlerrs;
पूर्ण;

काष्ठा brcmf_usbdev अणु
	काष्ठा brcmf_bus *bus;
	काष्ठा brcmf_usbdev_info *devinfo;
	क्रमागत brcmf_usb_state state;
	काष्ठा brcmf_stats stats;
	पूर्णांक ntxq, nrxq, rxsize;
	u32 bus_mtu;
	पूर्णांक devid;
	पूर्णांक chiprev; /* chip revision number */
पूर्ण;

/* IO Request Block (IRB) */
काष्ठा brcmf_usbreq अणु
	काष्ठा list_head list;
	काष्ठा brcmf_usbdev_info *devinfo;
	काष्ठा urb *urb;
	काष्ठा sk_buff  *skb;
पूर्ण;

#पूर्ण_अगर /* BRCMFMAC_USB_H */
