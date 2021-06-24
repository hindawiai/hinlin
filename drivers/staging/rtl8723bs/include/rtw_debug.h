<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_DEBUG_H__
#घोषणा __RTW_DEBUG_H__

#समावेश <linux/trace_seq.h>

#घोषणा _drv_always_		1
#घोषणा _drv_emerg_			2
#घोषणा _drv_alert_			3
#घोषणा _drv_crit_			4
#घोषणा _drv_err_			5
#घोषणा	_drv_warning_		6
#घोषणा _drv_notice_		7
#घोषणा _drv_info_			8
#घोषणा _drv_dump_			9
#घोषणा	_drv_debug_			10


#घोषणा _module_rtl871x_xmit_c_		BIT(0)
#घोषणा _module_xmit_osdep_c_		BIT(1)
#घोषणा _module_rtl871x_recv_c_		BIT(2)
#घोषणा _module_recv_osdep_c_		BIT(3)
#घोषणा _module_rtl871x_mlme_c_		BIT(4)
#घोषणा _module_mlme_osdep_c_		BIT(5)
#घोषणा _module_rtl871x_sta_mgt_c_		BIT(6)
#घोषणा _module_rtl871x_cmd_c_			BIT(7)
#घोषणा _module_cmd_osdep_c_		BIT(8)
#घोषणा _module_rtl871x_io_c_				BIT(9)
#घोषणा _module_io_osdep_c_		BIT(10)
#घोषणा _module_os_पूर्णांकfs_c_			BIT(11)
#घोषणा _module_rtl871x_security_c_		BIT(12)
#घोषणा _module_rtl871x_eeprom_c_			BIT(13)
#घोषणा _module_hal_init_c_		BIT(14)
#घोषणा _module_hci_hal_init_c_		BIT(15)
#घोषणा _module_rtl871x_ioctl_c_		BIT(16)
#घोषणा _module_rtl871x_ioctl_set_c_		BIT(17)
#घोषणा _module_rtl871x_ioctl_query_c_	BIT(18)
#घोषणा _module_rtl871x_pwrctrl_c_			BIT(19)
#घोषणा _module_hci_पूर्णांकfs_c_			BIT(20)
#घोषणा _module_hci_ops_c_			BIT(21)
#घोषणा _module_osdep_service_c_			BIT(22)
#घोषणा _module_mp_			BIT(23)
#घोषणा _module_hci_ops_os_c_			BIT(24)
#घोषणा _module_rtl871x_ioctl_os_c		BIT(25)
#घोषणा _module_rtl8712_cmd_c_		BIT(26)
/* define _module_efuse_			BIT(27) */
#घोषणा	_module_rtl8192c_xmit_c_ BIT(28)
#घोषणा _module_hal_xmit_c_	BIT(28)
#घोषणा _module_efuse_			BIT(29)
#घोषणा _module_rtl8712_recv_c_		BIT(30)
#घोषणा _module_rtl8712_led_c_		BIT(31)

#अघोषित _MODULE_DEFINE_

#अगर defined _RTW_XMIT_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_xmit_c_
#या_अगर defined _XMIT_OSDEP_C_
	#घोषणा _MODULE_DEFINE_	_module_xmit_osdep_c_
#या_अगर defined _RTW_RECV_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_recv_c_
#या_अगर defined _RECV_OSDEP_C_
	#घोषणा _MODULE_DEFINE_	_module_recv_osdep_c_
#या_अगर defined _RTW_MLME_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_mlme_c_
#या_अगर defined _MLME_OSDEP_C_
	#घोषणा _MODULE_DEFINE_	_module_mlme_osdep_c_
#या_अगर defined _RTW_MLME_EXT_C_
	#घोषणा _MODULE_DEFINE_ 1
#या_अगर defined _RTW_STA_MGT_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_sta_mgt_c_
#या_अगर defined _RTW_CMD_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_cmd_c_
#या_अगर defined _CMD_OSDEP_C_
	#घोषणा _MODULE_DEFINE_	_module_cmd_osdep_c_
#या_अगर defined _RTW_IO_C_
	#घोषणा _MODULE_DEFINE_	_module_rtl871x_io_c_
#या_अगर defined _IO_OSDEP_C_
	#घोषणा _MODULE_DEFINE_	_module_io_osdep_c_
#या_अगर defined _OS_INTFS_C_
	#घोषणा	_MODULE_DEFINE_	_module_os_पूर्णांकfs_c_
#या_अगर defined _RTW_SECURITY_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_security_c_
#या_अगर defined _RTW_EEPROM_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_eeprom_c_
#या_अगर defined _HAL_INTF_C_
	#घोषणा	_MODULE_DEFINE_	_module_hal_init_c_
#या_अगर (defined _HCI_HAL_INIT_C_) || (defined _SDIO_HALINIT_C_)
	#घोषणा	_MODULE_DEFINE_	_module_hci_hal_init_c_
#या_अगर defined _RTL871X_IOCTL_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_ioctl_c_
#या_अगर defined _RTL871X_IOCTL_SET_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_ioctl_set_c_
#या_अगर defined _RTL871X_IOCTL_QUERY_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_ioctl_query_c_
#या_अगर defined _RTL871X_PWRCTRL_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_pwrctrl_c_
#या_अगर defined _RTW_PWRCTRL_C_
	#घोषणा	_MODULE_DEFINE_	1
#या_अगर defined _HCI_INTF_C_
	#घोषणा	_MODULE_DEFINE_	_module_hci_पूर्णांकfs_c_
#या_अगर defined _HCI_OPS_C_
	#घोषणा	_MODULE_DEFINE_	_module_hci_ops_c_
#या_अगर defined _SDIO_OPS_C_
	#घोषणा	_MODULE_DEFINE_ 1
#या_अगर defined _OSDEP_HCI_INTF_C_
	#घोषणा	_MODULE_DEFINE_	_module_hci_पूर्णांकfs_c_
#या_अगर defined _OSDEP_SERVICE_C_
	#घोषणा	_MODULE_DEFINE_	_module_osdep_service_c_
#या_अगर defined _HCI_OPS_OS_C_
	#घोषणा	_MODULE_DEFINE_	_module_hci_ops_os_c_
#या_अगर defined _RTL871X_IOCTL_LINUX_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl871x_ioctl_os_c
#या_अगर defined _RTL8712_CMD_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl8712_cmd_c_
#या_अगर defined _RTL8192C_XMIT_C_
	#घोषणा	_MODULE_DEFINE_	1
#या_अगर defined _RTL8723AS_XMIT_C_
	#घोषणा	_MODULE_DEFINE_	1
#या_अगर defined _RTL8712_RECV_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl8712_recv_c_
#या_अगर defined _RTL8192CU_RECV_C_
	#घोषणा	_MODULE_DEFINE_	_module_rtl8712_recv_c_
#या_अगर defined _RTL871X_MLME_EXT_C_
	#घोषणा _MODULE_DEFINE_	_module_mlme_osdep_c_
#या_अगर defined _RTW_EFUSE_C_
	#घोषणा	_MODULE_DEFINE_	_module_efuse_
#पूर्ण_अगर

#अघोषित _dbgdump

#अगर_अघोषित _RTL871X_DEBUG_C_
	बाह्य u32 GlobalDebugLevel;
	बाह्य u64 GlobalDebugComponents;
#पूर्ण_अगर

#घोषणा _dbgdump prपूर्णांकk

#घोषणा DRIVER_PREFIX "RTL8723BS: "

#अगर defined(_dbgdump)

/* without driver-defined prefix */
#अघोषित _DBG_871X_LEVEL
#घोषणा _DBG_871X_LEVEL(level, fmt, arg...)	   \
	करो अणु\
		अगर (level <= GlobalDebugLevel) अणु\
			अगर (level <= _drv_err_ && level > _drv_always_) \
				_dbgdump("ERROR " fmt, ##arg);\
			अन्यथा \
				_dbgdump(fmt, ##arg);\
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा RTW_DBGDUMP शून्य /* 'stream' क्रम _dbgdump */

/* dump message to selected 'stream' */
#घोषणा DBG_871X_SEL(sel, fmt, arg...)					\
	करो अणु								\
		अगर (sel == RTW_DBGDUMP)					\
			_DBG_871X_LEVEL(_drv_always_, fmt, ##arg);	\
		अन्यथा							\
			seq_म_लिखो(sel, fmt, ##arg);			\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* defined(_dbgdump) */

व्योम sd_f0_reg_dump(व्योम *sel, काष्ठा adapter *adapter);

व्योम mac_reg_dump(व्योम *sel, काष्ठा adapter *adapter);
व्योम bb_reg_dump(व्योम *sel, काष्ठा adapter *adapter);
व्योम rf_reg_dump(व्योम *sel, काष्ठा adapter *adapter);

#पूर्ण_अगर	/* __RTW_DEBUG_H__ */
