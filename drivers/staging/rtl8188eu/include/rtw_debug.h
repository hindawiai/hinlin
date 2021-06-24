<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_DEBUG_H__
#घोषणा __RTW_DEBUG_H__

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

#घोषणा DRIVERVERSION	"v4.1.4_6773.20130222"
#घोषणा _drv_always_			1
#घोषणा _drv_emerg_			2
#घोषणा _drv_alert_			3
#घोषणा _drv_crit_			4
#घोषणा _drv_err_			5
#घोषणा	_drv_warning_			6
#घोषणा _drv_notice_			7
#घोषणा _drv_info_			8
#घोषणा	_drv_debug_			9

#घोषणा _module_rtl871x_xmit_c_		BIT(0)
#घोषणा _module_xmit_osdep_c_		BIT(1)
#घोषणा _module_rtl871x_recv_c_		BIT(2)
#घोषणा _module_recv_osdep_c_		BIT(3)
#घोषणा _module_rtl871x_mlme_c_		BIT(4)
#घोषणा _module_mlme_osdep_c_		BIT(5)
#घोषणा _module_rtl871x_sta_mgt_c_	BIT(6)
#घोषणा _module_rtl871x_cmd_c_		BIT(7)
#घोषणा _module_cmd_osdep_c_		BIT(8)
#घोषणा _module_rtl871x_io_c_		BIT(9)
#घोषणा _module_io_osdep_c_		BIT(10)
#घोषणा _module_os_पूर्णांकfs_c_		BIT(11)
#घोषणा _module_rtl871x_security_c_	BIT(12)
#घोषणा _module_rtl871x_eeprom_c_	BIT(13)
#घोषणा _module_hal_init_c_		BIT(14)
#घोषणा _module_hci_hal_init_c_		BIT(15)
#घोषणा _module_rtl871x_ioctl_c_	BIT(16)
#घोषणा _module_rtl871x_ioctl_set_c_	BIT(17)
#घोषणा _module_rtl871x_ioctl_query_c_	BIT(18)
#घोषणा _module_rtl871x_pwrctrl_c_	BIT(19)
#घोषणा _module_hci_पूर्णांकfs_c_		BIT(20)
#घोषणा _module_hci_ops_c_		BIT(21)
#घोषणा _module_osdep_service_c_	BIT(22)
#घोषणा _module_mp_			BIT(23)
#घोषणा _module_hci_ops_os_c_		BIT(24)
#घोषणा _module_rtl871x_ioctl_os_c	BIT(25)
#घोषणा _module_rtl8712_cmd_c_		BIT(26)
#घोषणा	_module_rtl8192c_xmit_c_	BIT(27)
#घोषणा _module_hal_xmit_c_		BIT(28)
#घोषणा _module_efuse_			BIT(29)
#घोषणा _module_rtl8712_recv_c_		BIT(30)
#घोषणा _module_rtl8712_led_c_		BIT(31)

#घोषणा DRIVER_PREFIX	"R8188EU: "

बाह्य u32 GlobalDebugLevel;

#घोषणा DBG_88E_LEVEL(_level, fmt, arg...)				\
	करो अणु								\
		अगर (_level <= GlobalDebugLevel)				\
			pr_info(DRIVER_PREFIX fmt, ##arg);	\
	पूर्ण जबतक (0)

#घोषणा DBG_88E(...)							\
	करो अणु								\
		अगर (_drv_err_ <= GlobalDebugLevel)			\
			pr_info(DRIVER_PREFIX __VA_ARGS__);		\
	पूर्ण जबतक (0)

#घोषणा MSG_88E(...)							\
	करो अणु								\
		अगर (_drv_err_ <= GlobalDebugLevel)			\
			pr_info(DRIVER_PREFIX __VA_ARGS__);			\
	पूर्ण जबतक (0)

#घोषणा RT_TRACE(_comp, _level, fmt)					\
	करो अणु								\
		अगर (_level <= GlobalDebugLevel) अणु			\
			pr_info("%s [0x%08x,%d]", DRIVER_PREFIX,	\
				 (अचिन्हित पूर्णांक)_comp, _level);		\
			pr_info fmt;					\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा RT_PRINT_DATA(_comp, _level, _titlestring, _hexdata, _hexdatalen)\
	करो अणु								\
		अगर (_level <= GlobalDebugLevel) अणु			\
			पूर्णांक __i;					\
			u8	*ptr = (u8 *)_hexdata;			\
			pr_info("%s", DRIVER_PREFIX);			\
			pr_info(_titlestring);				\
			क्रम (__i = 0; __i < (पूर्णांक)_hexdatalen; __i++) अणु	\
				pr_info("%02X%s", ptr[__i],		\
					 (((__i + 1) % 4) == 0) ?	\
					 "  " : " ");	\
				अगर (((__i + 1) % 16) == 0)		\
					pr_cont("\n");			\
			पूर्ण						\
			pr_cont("\n");					\
		पूर्ण							\
	पूर्ण जबतक (0)

पूर्णांक proc_get_drv_version(अक्षर *page, अक्षर **start,
			 off_t offset, पूर्णांक count,
			 पूर्णांक *eof, व्योम *data);

पूर्णांक proc_get_ग_लिखो_reg(अक्षर *page, अक्षर **start,
		       off_t offset, पूर्णांक count,
		       पूर्णांक *eof, व्योम *data);

पूर्णांक proc_set_ग_लिखो_reg(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		       अचिन्हित दीर्घ count, व्योम *data);
पूर्णांक proc_get_पढ़ो_reg(अक्षर *page, अक्षर **start,
		      off_t offset, पूर्णांक count,
		      पूर्णांक *eof, व्योम *data);

पूर्णांक proc_set_पढ़ो_reg(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		      अचिन्हित दीर्घ count, व्योम *data);

पूर्णांक proc_get_adapter_state(अक्षर *page, अक्षर **start,
			   off_t offset, पूर्णांक count,
			   पूर्णांक *eof, व्योम *data);

पूर्णांक proc_get_best_channel(अक्षर *page, अक्षर **start,
			  off_t offset, पूर्णांक count,
			  पूर्णांक *eof, व्योम *data);

#पूर्ण_अगर	/* __RTW_DEBUG_H__ */
