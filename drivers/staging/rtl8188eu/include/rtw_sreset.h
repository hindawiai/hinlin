<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTW_SRESET_C_
#घोषणा _RTW_SRESET_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

काष्ठा sreset_priv अणु
	u8 wअगरi_error_status;
पूर्ण;

#समावेश <rtl8188e_hal.h>

#घोषणा	WIFI_STATUS_SUCCESS		0
#घोषणा	USB_VEN_REQ_CMD_FAIL		BIT(0)
#घोषणा	USB_READ_PORT_FAIL		BIT(1)
#घोषणा	USB_WRITE_PORT_FAIL		BIT(2)
#घोषणा	WIFI_MAC_TXDMA_ERROR		BIT(3)
#घोषणा   WIFI_TX_HANG			BIT(4)
#घोषणा	WIFI_RX_HANG			BIT(5)
#घोषणा		WIFI_IF_NOT_EXIST	BIT(6)

व्योम sreset_set_wअगरi_error_status(काष्ठा adapter *padapter, u32 status);

#पूर्ण_अगर
