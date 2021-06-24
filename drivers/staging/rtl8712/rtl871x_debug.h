<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RTL871X_DEBUG_H__
#घोषणा __RTL871X_DEBUG_H__

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

#घोषणा _drv_emerg_			1
#घोषणा _drv_alert_			2
#घोषणा _drv_crit_			3
#घोषणा _drv_err_			4
#घोषणा	_drv_warning_			5
#घोषणा _drv_notice_			6
#घोषणा _drv_info_			7
#घोषणा _drv_dump_			8
#घोषणा	_drv_debug_			9

#घोषणा _module_rtl871x_xmit_c_		BIT(0)
#घोषणा _module_xmit_osdep_c_		BIT(1)
#घोषणा _module_rtl871x_recv_c_		BIT(2)
#घोषणा _module_recv_osdep_c_		BIT(3)
#घोषणा _module_rtl871x_mlme_c_		BIT(4)
#घोषणा	_module_mlme_osdep_c_		BIT(5)
#घोषणा _module_rtl871x_sta_mgt_c_	BIT(6)
#घोषणा _module_rtl871x_cmd_c_		BIT(7)
#घोषणा	_module_cmd_osdep_c_		BIT(8)
#घोषणा _module_rtl871x_io_c_		BIT(9)
#घोषणा	_module_io_osdep_c_		BIT(10)
#घोषणा _module_os_पूर्णांकfs_c_		BIT(11)
#घोषणा _module_rtl871x_security_c_	BIT(12)
#घोषणा _module_rtl871x_eeprom_c_	BIT(13)
#घोषणा _module_hal_init_c_		BIT(14)
#घोषणा _module_hci_hal_init_c_		BIT(15)
#घोषणा _module_rtl871x_ioctl_c_	BIT(16)
#घोषणा _module_rtl871x_ioctl_set_c_	BIT(17)
#घोषणा _module_rtl871x_pwrctrl_c_	BIT(19)
#घोषणा _module_hci_पूर्णांकfs_c_		BIT(20)
#घोषणा _module_hci_ops_c_		BIT(21)
#घोषणा _module_osdep_service_c_	BIT(22)
#घोषणा _module_rtl871x_mp_ioctl_c_	BIT(23)
#घोषणा _module_hci_ops_os_c_		BIT(24)
#घोषणा _module_rtl871x_ioctl_os_c	BIT(25)
#घोषणा _module_rtl8712_cmd_c_		BIT(26)
#घोषणा _module_rtl871x_mp_c_		BIT(27)
#घोषणा _module_rtl8712_xmit_c_		BIT(28)
#घोषणा _module_rtl8712_efuse_c_	BIT(29)
#घोषणा _module_rtl8712_recv_c_		BIT(30)
#घोषणा _module_rtl8712_led_c_		BIT(31)

#अघोषित _MODULE_DEFINE_

#अगर defined _RTL871X_XMIT_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_xmit_c_
#या_अगर defined _XMIT_OSDEP_C_
	#घोषणा _MODULE_DEFINE_	_module_xmit_osdep_c_
#या_अगर defined _RTL871X_RECV_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_recv_c_
#या_अगर defined _RECV_OSDEP_C_
	#घोषणा _MODULE_DEFINE_	_module_recv_osdep_c_
#या_अगर defined _RTL871X_MLME_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_mlme_c_
#या_अगर defined _MLME_OSDEP_C_
	#घोषणा _MODULE_DEFINE_	_module_mlme_osdep_c_
#या_अगर defined _RTL871X_STA_MGT_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_sta_mgt_c_
#या_अगर defined _RTL871X_CMD_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_cmd_c_
#या_अगर defined _CMD_OSDEP_C_
	#घोषणा _MODULE_DEFINE_	_module_cmd_osdep_c_
#या_अगर defined _RTL871X_IO_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_io_c_
#या_अगर defined _IO_OSDEP_C_
	#घोषणा _MODULE_DEFINE_	_module_io_osdep_c_
#या_अगर defined _OS_INTFS_C_
	#घोषणा	_MODULE_DEFINE_	_module_os_पूर्णांकfs_c_
#या_अगर defined _RTL871X_SECURITY_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_security_c_
#या_अगर defined _RTL871X_EEPROM_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_eeprom_c_
#या_अगर defined _HAL_INIT_C_
	#घोषणा	_MODULE_DEFINE_	_module_hal_init_c_
#या_अगर defined _HCI_HAL_INIT_C_
	#घोषणा	_MODULE_DEFINE_	_module_hci_hal_init_c_
#या_अगर defined _RTL871X_IOCTL_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_ioctl_c_
#या_अगर defined _RTL871X_IOCTL_SET_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_ioctl_set_c_
#या_अगर defined _RTL871X_PWRCTRL_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_pwrctrl_c_
#या_अगर defined _HCI_INTF_C_
	#घोषणा	_MODULE_DEFINE_	_module_hci_पूर्णांकfs_c_
#या_अगर defined _HCI_OPS_C_
	#घोषणा	_MODULE_DEFINE_	_module_hci_ops_c_
#या_अगर defined _OSDEP_HCI_INTF_C_
	#घोषणा	_MODULE_DEFINE_	_module_hci_पूर्णांकfs_c_
#या_अगर defined _OSDEP_SERVICE_C_
	#घोषणा	_MODULE_DEFINE_	_module_osdep_service_c_
#या_अगर defined _RTL871X_MP_IOCTL_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_mp_ioctl_c_
#या_अगर defined _HCI_OPS_OS_C_
	#घोषणा	_MODULE_DEFINE_	_module_hci_ops_os_c_
#या_अगर defined _RTL871X_IOCTL_LINUX_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_ioctl_os_c
#या_अगर defined _RTL871X_MP_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_mp_c_
#या_अगर defined _RTL8712_CMD_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl8712_cmd_c_
#या_अगर defined _RTL8712_XMIT_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl8712_xmit_c_
#या_अगर defined _RTL8712_EFUSE_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl8712_efuse_c_
#या_अगर defined _RTL8712_RECV_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl8712_recv_c_
#अन्यथा
	#अघोषित	_MODULE_DEFINE_
#पूर्ण_अगर

#घोषणा _dbgdump	prपूर्णांकk

#घोषणा MSG_8712(x, ...) अणुपूर्ण

#घोषणा DBG_8712(x, ...)  अणुपूर्ण

#घोषणा WRN_8712(x, ...)  अणुपूर्ण

#घोषणा ERR_8712(x, ...)  अणुपूर्ण

#अघोषित MSG_8712
#घोषणा MSG_8712 _dbgdump

#अघोषित DBG_8712
#घोषणा DBG_8712 _dbgdump

#अघोषित WRN_8712
#घोषणा WRN_8712 _dbgdump

#अघोषित ERR_8712
#घोषणा ERR_8712 _dbgdump

#पूर्ण_अगर	/*__RTL871X_DEBUG_H__*/

