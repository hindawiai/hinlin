<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* r8169_firmware.h: RealTek 8169/8168/8101 ethernet driver.
 *
 * Copyright (c) 2002 ShuChen <shuchen@realtek.com.tw>
 * Copyright (c) 2003 - 2007 Francois Romieu <romieu@fr.zoreil.com>
 * Copyright (c) a lot of people too. Please respect their work.
 *
 * See MAINTAINERS file क्रम support contact inक्रमmation.
 */

#समावेश <linux/device.h>
#समावेश <linux/firmware.h>

काष्ठा rtl8169_निजी;
प्रकार व्योम (*rtl_fw_ग_लिखो_t)(काष्ठा rtl8169_निजी *tp, पूर्णांक reg, पूर्णांक val);
प्रकार पूर्णांक (*rtl_fw_पढ़ो_t)(काष्ठा rtl8169_निजी *tp, पूर्णांक reg);

#घोषणा RTL_VER_SIZE		32

काष्ठा rtl_fw अणु
	rtl_fw_ग_लिखो_t phy_ग_लिखो;
	rtl_fw_पढ़ो_t phy_पढ़ो;
	rtl_fw_ग_लिखो_t mac_mcu_ग_लिखो;
	rtl_fw_पढ़ो_t mac_mcu_पढ़ो;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name;
	काष्ठा device *dev;

	अक्षर version[RTL_VER_SIZE];

	काष्ठा rtl_fw_phy_action अणु
		__le32 *code;
		माप_प्रकार size;
	पूर्ण phy_action;
पूर्ण;

पूर्णांक rtl_fw_request_firmware(काष्ठा rtl_fw *rtl_fw);
व्योम rtl_fw_release_firmware(काष्ठा rtl_fw *rtl_fw);
व्योम rtl_fw_ग_लिखो_firmware(काष्ठा rtl8169_निजी *tp, काष्ठा rtl_fw *rtl_fw);
