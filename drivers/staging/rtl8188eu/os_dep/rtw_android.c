<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>

#समावेश <rtw_android.h>
#समावेश <osdep_service.h>
#समावेश <rtw_debug.h>
#समावेश <rtw_ioctl_set.h>

अटल स्थिर अक्षर *android_wअगरi_cmd_str[ANDROID_WIFI_CMD_MAX] = अणु
	"START",
	"STOP",
	"SCAN-ACTIVE",
	"SCAN-PASSIVE",
	"RSSI",
	"LINKSPEED",
	"RXFILTER-START",
	"RXFILTER-STOP",
	"RXFILTER-ADD",
	"RXFILTER-REMOVE",
	"BTCOEXSCAN-START",
	"BTCOEXSCAN-STOP",
	"BTCOEXMODE",
	"SETSUSPENDOPT",
	"P2P_DEV_ADDR",
	"SETFWPATH",
	"SETBAND",
	"GETBAND",
	"COUNTRY",
	"P2P_SET_NOA",
	"P2P_GET_NOA",
	"P2P_SET_PS",
	"SET_AP_WPS_P2P_IE",
	"MACADDR",
	"BLOCK",
	"WFD-ENABLE",
	"WFD-DISABLE",
	"WFD-SET-TCPPORT",
	"WFD-SET-MAXTPUT",
	"WFD-SET-DEVTYPE",
पूर्ण;

काष्ठा android_wअगरi_priv_cmd अणु
	स्थिर अक्षर __user *buf;
	पूर्णांक used_len;
	पूर्णांक total_len;
पूर्ण;

पूर्णांक rtw_android_cmdstr_to_num(अक्षर *cmdstr)
अणु
	पूर्णांक cmd_num;

	क्रम (cmd_num = 0; cmd_num < ANDROID_WIFI_CMD_MAX; cmd_num++)
		अगर (!strnहालcmp(cmdstr, android_wअगरi_cmd_str[cmd_num],
				 म_माप(android_wअगरi_cmd_str[cmd_num])))
			अवरोध;
	वापस cmd_num;
पूर्ण

अटल पूर्णांक rtw_android_get_rssi(काष्ठा net_device *net, अक्षर *command,
				पूर्णांक total_len)
अणु
	काष्ठा adapter *padapter = netdev_priv(net);
	काष्ठा	mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा	wlan_network	*pcur_network = &pmlmepriv->cur_network;
	पूर्णांक bytes_written = 0;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		bytes_written += snम_लिखो(&command[bytes_written], total_len,
					  "%s rssi %d",
					  pcur_network->network.ssid.ssid,
					  padapter->recvpriv.rssi);
	पूर्ण
	वापस bytes_written;
पूर्ण

अटल पूर्णांक rtw_android_get_link_speed(काष्ठा net_device *net, अक्षर *command,
				      पूर्णांक total_len)
अणु
	काष्ठा adapter *padapter = netdev_priv(net);
	u16 link_speed;

	link_speed = rtw_get_cur_max_rate(padapter) / 10;
	वापस snम_लिखो(command, total_len, "LinkSpeed %d",
				 link_speed);
पूर्ण

अटल पूर्णांक rtw_android_get_macaddr(काष्ठा net_device *net, अक्षर *command,
				   पूर्णांक total_len)
अणु
	वापस snम_लिखो(command, total_len, "Macaddr = %pM",
				 net->dev_addr);
पूर्ण

अटल पूर्णांक android_set_cntry(काष्ठा net_device *net, अक्षर *command,
			     पूर्णांक total_len)
अणु
	काष्ठा adapter *adapter = netdev_priv(net);
	अक्षर *country_code = command + म_माप(android_wअगरi_cmd_str[ANDROID_WIFI_CMD_COUNTRY]) + 1;
	पूर्णांक ret;

	ret = rtw_set_country(adapter, country_code);
	वापस (ret == _SUCCESS) ? 0 : -1;
पूर्ण

अटल पूर्णांक android_get_p2p_addr(काष्ठा net_device *net, अक्षर *command,
				पूर्णांक total_len)
अणु
	/* We use the same address as our HW MAC address */
	स_नकल(command, net->dev_addr, ETH_ALEN);
	वापस ETH_ALEN;
पूर्ण

पूर्णांक rtw_android_priv_cmd(काष्ठा net_device *net, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	पूर्णांक ret = 0;
	अक्षर *command;
	पूर्णांक cmd_num;
	पूर्णांक bytes_written = 0;
	काष्ठा android_wअगरi_priv_cmd priv_cmd;

	अगर (!अगरr->अगरr_data)
		वापस -EINVAL;
	अगर (copy_from_user(&priv_cmd, अगरr->अगरr_data, माप(priv_cmd)))
		वापस -EFAULT;
	अगर (priv_cmd.total_len < 1)
		वापस -EINVAL;
	command = memdup_user(priv_cmd.buf, priv_cmd.total_len);
	अगर (IS_ERR(command))
		वापस PTR_ERR(command);
	command[priv_cmd.total_len - 1] = 0;
	DBG_88E("%s: Android private cmd \"%s\" on %s\n",
		__func__, command, अगरr->अगरr_name);
	cmd_num = rtw_android_cmdstr_to_num(command);
	चयन (cmd_num) अणु
	हाल ANDROID_WIFI_CMD_START:
		जाओ response;
	हाल ANDROID_WIFI_CMD_SETFWPATH:
		जाओ response;
	पूर्ण
	चयन (cmd_num) अणु
	हाल ANDROID_WIFI_CMD_STOP:
		अवरोध;
	हाल ANDROID_WIFI_CMD_SCAN_ACTIVE:
		अवरोध;
	हाल ANDROID_WIFI_CMD_SCAN_PASSIVE:
		अवरोध;
	हाल ANDROID_WIFI_CMD_RSSI:
		bytes_written = rtw_android_get_rssi(net, command,
						     priv_cmd.total_len);
		अवरोध;
	हाल ANDROID_WIFI_CMD_LINKSPEED:
		bytes_written = rtw_android_get_link_speed(net, command,
							   priv_cmd.total_len);
		अवरोध;
	हाल ANDROID_WIFI_CMD_MACADDR:
		bytes_written = rtw_android_get_macaddr(net, command,
							priv_cmd.total_len);
		अवरोध;
	हाल ANDROID_WIFI_CMD_BLOCK:
		अवरोध;
	हाल ANDROID_WIFI_CMD_RXFILTER_START:
		अवरोध;
	हाल ANDROID_WIFI_CMD_RXFILTER_STOP:
		अवरोध;
	हाल ANDROID_WIFI_CMD_RXFILTER_ADD:
		अवरोध;
	हाल ANDROID_WIFI_CMD_RXFILTER_REMOVE:
		अवरोध;
	हाल ANDROID_WIFI_CMD_BTCOEXSCAN_START:
		/* TBD: BTCOEXSCAN-START */
		अवरोध;
	हाल ANDROID_WIFI_CMD_BTCOEXSCAN_STOP:
		/* TBD: BTCOEXSCAN-STOP */
		अवरोध;
	हाल ANDROID_WIFI_CMD_BTCOEXMODE:
		अवरोध;
	हाल ANDROID_WIFI_CMD_SETSUSPENDOPT:
		अवरोध;
	हाल ANDROID_WIFI_CMD_SETBAND:
		अवरोध;
	हाल ANDROID_WIFI_CMD_GETBAND:
		अवरोध;
	हाल ANDROID_WIFI_CMD_COUNTRY:
		bytes_written = android_set_cntry(net, command,
						  priv_cmd.total_len);
		अवरोध;
	हाल ANDROID_WIFI_CMD_P2P_DEV_ADDR:
		bytes_written = android_get_p2p_addr(net, command,
						     priv_cmd.total_len);
		अवरोध;
	हाल ANDROID_WIFI_CMD_P2P_SET_NOA:
		अवरोध;
	हाल ANDROID_WIFI_CMD_P2P_GET_NOA:
		अवरोध;
	हाल ANDROID_WIFI_CMD_P2P_SET_PS:
		अवरोध;
	शेष:
		DBG_88E("Unknown PRIVATE command %s - ignored\n", command);
		snम_लिखो(command, 3, "OK");
		bytes_written = म_माप("OK");
	पूर्ण

response:
	अगर (bytes_written >= 0) अणु
		अगर ((bytes_written == 0) && (priv_cmd.total_len > 0))
			command[0] = '\0';
		अगर (bytes_written >= priv_cmd.total_len) अणु
			DBG_88E("%s: bytes_written = %d\n", __func__,
				bytes_written);
			bytes_written = priv_cmd.total_len;
		पूर्ण अन्यथा अणु
			bytes_written++;
		पूर्ण
		priv_cmd.used_len = bytes_written;
		अगर (copy_to_user((अक्षर __user *)priv_cmd.buf, command,
				 bytes_written)) अणु
			DBG_88E("%s: failed to copy data to user buffer\n",
				__func__);
			ret = -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = bytes_written;
	पूर्ण
	kमुक्त(command);
	वापस ret;
पूर्ण
