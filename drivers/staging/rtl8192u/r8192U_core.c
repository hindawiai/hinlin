<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192U
 *
 * Based on the r8187 driver, which is:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Contact Inक्रमmation:
 * Jerry chuang <wlanfae@realtek.com>
 */

#अगर_अघोषित CONFIG_FORCE_HARD_FLOAT
द्विगुन __भग्नsidf(पूर्णांक i)
अणु
	वापस i;
पूर्ण

अचिन्हित पूर्णांक __fixunsdfsi(द्विगुन d)
अणु
	वापस d;
पूर्ण

द्विगुन __adddf3(द्विगुन a, द्विगुन b)
अणु
	वापस a + b;
पूर्ण

द्विगुन __addsf3(भग्न a, भग्न b)
अणु
	वापस a + b;
पूर्ण

द्विगुन __subdf3(द्विगुन a, द्विगुन b)
अणु
	वापस a - b;
पूर्ण

द्विगुन __extendsfdf2(भग्न a)
अणु
	वापस a;
पूर्ण
#पूर्ण_अगर

#घोषणा CONFIG_RTL8192_IO_MAP

#समावेश <linux/uaccess.h>
#समावेश "r8192U_hw.h"
#समावेश "r8192U.h"
#समावेश "r8190_rtl8256.h" /* RTL8225 Radio frontend */
#समावेश "r8180_93cx6.h"   /* Card EEPROM */
#समावेश "r8192U_wx.h"
#समावेश "r819xU_phy.h"
#समावेश "r819xU_phyreg.h"
#समावेश "r819xU_cmdpkt.h"
#समावेश "r8192U_dm.h"
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
/* FIXME: check अगर 2.6.7 is ok */

#समावेश "ieee80211/dot11d.h"
/* set here to खोलो your trace code. */
u32 rt_global_debug_component = COMP_DOWN	|
				COMP_SEC	|
				COMP_ERR; /* always खोलो err flags on */

#घोषणा TOTAL_CAM_ENTRY 32
#घोषणा CAM_CONTENT_COUNT 8

अटल स्थिर काष्ठा usb_device_id rtl8192_usb_id_tbl[] = अणु
	/* Realtek */
	अणुUSB_DEVICE(0x0bda, 0x8709)पूर्ण,
	/* Corega */
	अणुUSB_DEVICE(0x07aa, 0x0043)पूर्ण,
	/* Belkin */
	अणुUSB_DEVICE(0x050d, 0x805E)पूर्ण,
	/* Sitecom */
	अणुUSB_DEVICE(0x0df6, 0x0031)पूर्ण,
	/* EnGenius */
	अणुUSB_DEVICE(0x1740, 0x9201)पूर्ण,
	/* Dlink */
	अणुUSB_DEVICE(0x2001, 0x3301)पूर्ण,
	/* Zinwell */
	अणुUSB_DEVICE(0x5a57, 0x0290)पूर्ण,
	/* LG */
	अणुUSB_DEVICE(0x043e, 0x7a01)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_VERSION("V 1.1");
MODULE_DEVICE_TABLE(usb, rtl8192_usb_id_tbl);
MODULE_DESCRIPTION("Linux driver for Realtek RTL8192 USB WiFi cards");

अटल अक्षर *अगरname = "wlan%d";
अटल पूर्णांक hwwep = 1;  /* शेष use hw. set 0 to use software security */
अटल पूर्णांक channels = 0x3fff;

module_param(अगरname, अक्षरp, 0644);
module_param(hwwep, पूर्णांक, 0644);
module_param(channels, पूर्णांक, 0644);

MODULE_PARM_DESC(अगरname, " Net interface name, wlan%d=default");
MODULE_PARM_DESC(hwwep, " Try to use hardware security support. ");
MODULE_PARM_DESC(channels, " Channel bitmask for specific locales. NYI");

अटल पूर्णांक rtl8192_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     स्थिर काष्ठा usb_device_id *id);
अटल व्योम rtl8192_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

अटल काष्ठा usb_driver rtl8192_usb_driver = अणु
	.name		= RTL819XU_MODULE_NAME,		  /* Driver name   */
	.id_table	= rtl8192_usb_id_tbl,		  /* PCI_ID table  */
	.probe		= rtl8192_usb_probe,		  /* probe fn      */
	.disconnect	= rtl8192_usb_disconnect,	  /* हटाओ fn     */
	.suspend	= शून्य,				  /* PM suspend fn */
	.resume		= शून्य,				  /* PM resume fn  */
पूर्ण;

काष्ठा CHANNEL_LIST अणु
	u8	Channel[32];
	u8	Len;
पूर्ण;

अटल काष्ठा CHANNEL_LIST ChannelPlan[] = अणु
	/* FCC */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 36, 40, 44, 48, 52, 56, 60, 64, 149, 153, 157, 161, 165पूर्ण, 24पूर्ण,
	/* IC */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11पूर्ण, 11पूर्ण,
	/* ETSI */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 36, 40, 44, 48, 52, 56, 60, 64पूर्ण, 21पूर्ण,
	/* Spain. Change to ETSI. */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,
	/* France. Change to ETSI. */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,
	/* MKK */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 36, 40, 44, 48, 52, 56, 60, 64पूर्ण, 22पूर्ण,
	/* MKK1 */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 36, 40, 44, 48, 52, 56, 60, 64पूर्ण, 22पूर्ण,
	/* Israel. */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,
	/* For 11a , TELEC */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 36, 40, 44, 48, 52, 56, 60, 64पूर्ण, 22पूर्ण,
	/* MIC */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 36, 40, 44, 48, 52, 56, 60, 64पूर्ण, 22पूर्ण,
	/* For Global Doमुख्य. 1-11:active scan, 12-14 passive scan. */
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14पूर्ण, 14पूर्ण
पूर्ण;

अटल व्योम rtl819x_set_channel_map(u8 channel_plan, काष्ठा r8192_priv *priv)
अणु
	पूर्णांक i, max_chan = -1, min_chan = -1;
	काष्ठा ieee80211_device *ieee = priv->ieee80211;

	चयन (channel_plan) अणु
	हाल COUNTRY_CODE_FCC:
	हाल COUNTRY_CODE_IC:
	हाल COUNTRY_CODE_ETSI:
	हाल COUNTRY_CODE_SPAIN:
	हाल COUNTRY_CODE_FRANCE:
	हाल COUNTRY_CODE_MKK:
	हाल COUNTRY_CODE_MKK1:
	हाल COUNTRY_CODE_ISRAEL:
	हाल COUNTRY_CODE_TELEC:
	हाल COUNTRY_CODE_MIC:
		rtl8192u_करोt11d_init(ieee);
		ieee->bGlobalDoमुख्य = false;
		/* actually 8225 & 8256 rf chips only support B,G,24N mode */
		अगर ((priv->rf_chip == RF_8225) || (priv->rf_chip == RF_8256)) अणु
			min_chan = 1;
			max_chan = 14;
		पूर्ण अन्यथा अणु
			RT_TRACE(COMP_ERR,
				 "unknown rf chip, can't set channel map in function:%s()\n",
				 __func__);
		पूर्ण
		अगर (ChannelPlan[channel_plan].Len != 0) अणु
			/* Clear old channel map */
			स_रखो(GET_DOT11D_INFO(ieee)->channel_map, 0,
			       माप(GET_DOT11D_INFO(ieee)->channel_map));
			/* Set new channel map */
			क्रम (i = 0; i < ChannelPlan[channel_plan].Len; i++) अणु
				अगर (ChannelPlan[channel_plan].Channel[i] < min_chan || ChannelPlan[channel_plan].Channel[i] > max_chan)
					अवरोध;
				GET_DOT11D_INFO(ieee)->channel_map[ChannelPlan[channel_plan].Channel[i]] = 1;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल COUNTRY_CODE_GLOBAL_DOMAIN:
		/* this flag enabled to follow 11d country IE setting,
		 * otherwise, it shall follow global करोमुख्य settings.
		 */
		GET_DOT11D_INFO(ieee)->करोt11d_enabled = 0;
		करोt11d_reset(ieee);
		ieee->bGlobalDoमुख्य = true;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम CamResetAllEntry(काष्ठा net_device *dev)
अणु
	u32 ulcommand = 0;
	/* In अटल WEP, OID_ADD_KEY or OID_ADD_WEP are set beक्रमe STA
	 * associate to AP. However, ResetKey is called on
	 * OID_802_11_INFRASTRUCTURE_MODE and MlmeAssociateRequest. In this
	 * condition, Cam can not be reset because upper layer will not set
	 * this अटल key again.
	 */
	ulcommand |= BIT(31) | BIT(30);
	ग_लिखो_nic_dword(dev, RWCAM, ulcommand);
पूर्ण

पूर्णांक ग_लिखो_nic_byte_E(काष्ठा net_device *dev, पूर्णांक indx, u8 data)
अणु
	पूर्णांक status;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा usb_device *udev = priv->udev;
	u8 *usbdata = kzalloc(माप(data), GFP_KERNEL);

	अगर (!usbdata)
		वापस -ENOMEM;
	*usbdata = data;

	status = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				 RTL8187_REQ_SET_REGS, RTL8187_REQT_WRITE,
				 indx | 0xfe00, 0, usbdata, 1, HZ / 2);
	kमुक्त(usbdata);

	अगर (status < 0) अणु
		netdev_err(dev, "%s TimeOut! status: %d\n", __func__, status);
		वापस status;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक पढ़ो_nic_byte_E(काष्ठा net_device *dev, पूर्णांक indx, u8 *data)
अणु
	पूर्णांक status;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा usb_device *udev = priv->udev;
	u8 *usbdata = kzalloc(माप(u8), GFP_KERNEL);

	अगर (!usbdata)
		वापस -ENOMEM;

	status = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				 RTL8187_REQ_GET_REGS, RTL8187_REQT_READ,
				 indx | 0xfe00, 0, usbdata, 1, HZ / 2);
	*data = *usbdata;
	kमुक्त(usbdata);

	अगर (status < 0) अणु
		netdev_err(dev, "%s failure status: %d\n", __func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/* as 92U has extend page from 4 to 16, so modअगरy functions below. */
पूर्णांक ग_लिखो_nic_byte(काष्ठा net_device *dev, पूर्णांक indx, u8 data)
अणु
	पूर्णांक status;

	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा usb_device *udev = priv->udev;
	u8 *usbdata = kzalloc(माप(data), GFP_KERNEL);

	अगर (!usbdata)
		वापस -ENOMEM;
	*usbdata = data;

	status = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				 RTL8187_REQ_SET_REGS, RTL8187_REQT_WRITE,
				 (indx & 0xff) | 0xff00, (indx >> 8) & 0x0f,
				 usbdata, 1, HZ / 2);
	kमुक्त(usbdata);

	अगर (status < 0) अणु
		netdev_err(dev, "%s TimeOut! status: %d\n", __func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ग_लिखो_nic_word(काष्ठा net_device *dev, पूर्णांक indx, u16 data)
अणु
	पूर्णांक status;

	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा usb_device *udev = priv->udev;
	u16 *usbdata = kzalloc(माप(data), GFP_KERNEL);

	अगर (!usbdata)
		वापस -ENOMEM;
	*usbdata = data;

	status = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				 RTL8187_REQ_SET_REGS, RTL8187_REQT_WRITE,
				 (indx & 0xff) | 0xff00, (indx >> 8) & 0x0f,
				 usbdata, 2, HZ / 2);
	kमुक्त(usbdata);

	अगर (status < 0) अणु
		netdev_err(dev, "%s TimeOut! status: %d\n", __func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ग_लिखो_nic_dword(काष्ठा net_device *dev, पूर्णांक indx, u32 data)
अणु
	पूर्णांक status;

	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा usb_device *udev = priv->udev;
	u32 *usbdata = kzalloc(माप(data), GFP_KERNEL);

	अगर (!usbdata)
		वापस -ENOMEM;
	*usbdata = data;

	status = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				 RTL8187_REQ_SET_REGS, RTL8187_REQT_WRITE,
				 (indx & 0xff) | 0xff00, (indx >> 8) & 0x0f,
				 usbdata, 4, HZ / 2);
	kमुक्त(usbdata);

	अगर (status < 0) अणु
		netdev_err(dev, "%s TimeOut! status: %d\n", __func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पढ़ो_nic_byte(काष्ठा net_device *dev, पूर्णांक indx, u8 *data)
अणु
	पूर्णांक status;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा usb_device *udev = priv->udev;
	u8 *usbdata = kzalloc(माप(u8), GFP_KERNEL);

	अगर (!usbdata)
		वापस -ENOMEM;

	status = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				 RTL8187_REQ_GET_REGS, RTL8187_REQT_READ,
				 (indx & 0xff) | 0xff00, (indx >> 8) & 0x0f,
				 usbdata, 1, HZ / 2);
	*data = *usbdata;
	kमुक्त(usbdata);

	अगर (status < 0) अणु
		netdev_err(dev, "%s failure status: %d\n", __func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पढ़ो_nic_word(काष्ठा net_device *dev, पूर्णांक indx, u16 *data)
अणु
	पूर्णांक status;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा usb_device *udev = priv->udev;
	u16 *usbdata = kzalloc(माप(u16), GFP_KERNEL);

	अगर (!usbdata)
		वापस -ENOMEM;

	status = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				 RTL8187_REQ_GET_REGS, RTL8187_REQT_READ,
				 (indx & 0xff) | 0xff00, (indx >> 8) & 0x0f,
				 usbdata, 2, HZ / 2);
	*data = *usbdata;
	kमुक्त(usbdata);

	अगर (status < 0) अणु
		netdev_err(dev, "%s failure status: %d\n", __func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_nic_word_E(काष्ठा net_device *dev, पूर्णांक indx, u16 *data)
अणु
	पूर्णांक status;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा usb_device *udev = priv->udev;
	u16 *usbdata = kzalloc(माप(u16), GFP_KERNEL);

	अगर (!usbdata)
		वापस -ENOMEM;

	status = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				 RTL8187_REQ_GET_REGS, RTL8187_REQT_READ,
				 indx | 0xfe00, 0, usbdata, 2, HZ / 2);
	*data = *usbdata;
	kमुक्त(usbdata);

	अगर (status < 0) अणु
		netdev_err(dev, "%s failure status: %d\n", __func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पढ़ो_nic_dword(काष्ठा net_device *dev, पूर्णांक indx, u32 *data)
अणु
	पूर्णांक status;

	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा usb_device *udev = priv->udev;
	u32 *usbdata = kzalloc(माप(u32), GFP_KERNEL);

	अगर (!usbdata)
		वापस -ENOMEM;

	status = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				 RTL8187_REQ_GET_REGS, RTL8187_REQT_READ,
				 (indx & 0xff) | 0xff00, (indx >> 8) & 0x0f,
				 usbdata, 4, HZ / 2);
	*data = *usbdata;
	kमुक्त(usbdata);

	अगर (status < 0) अणु
		netdev_err(dev, "%s failure status: %d\n", __func__, status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/* u8 पढ़ो_phy_cck(काष्ठा net_device *dev, u8 adr); */
/* u8 पढ़ो_phy_ofdm(काष्ठा net_device *dev, u8 adr); */
/* this might still called in what was the PHY rtl8185/rtl8192 common code
 * plans are to possibility turn it again in one common code...
 */
अंतरभूत व्योम क्रमce_pci_posting(काष्ठा net_device *dev)
अणु
पूर्ण

अटल काष्ठा net_device_stats *rtl8192_stats(काष्ठा net_device *dev);
अटल व्योम rtl8192_restart(काष्ठा work_काष्ठा *work);
अटल व्योम watch_करोg_समयr_callback(काष्ठा समयr_list *t);

/****************************************************************************
 *   -----------------------------PROCFS STUFF-------------------------
 ****************************************************************************/

अटल काष्ठा proc_dir_entry *rtl8192_proc;

अटल पूर्णांक __maybe_unused proc_get_stats_ap(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा net_device *dev = m->निजी;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	काष्ठा ieee80211_network *target;

	list_क्रम_each_entry(target, &ieee->network_list, list) अणु
		स्थिर अक्षर *wpa = "non_WPA";

		अगर (target->wpa_ie_len > 0 || target->rsn_ie_len > 0)
			wpa = "WPA";

		seq_म_लिखो(m, "%s %s\n", target->ssid, wpa);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused proc_get_रेजिस्टरs(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा net_device *dev = m->निजी;
	पूर्णांक i, n, max = 0xff;
	u8 byte_rd;

	seq_माला_दो(m, "\n####################page 0##################\n ");

	क्रम (n = 0; n <= max;) अणु
		seq_म_लिखो(m, "\nD:  %2x > ", n);

		क्रम (i = 0; i < 16 && n <= max; i++, n++) अणु
			पढ़ो_nic_byte(dev, 0x000 | n, &byte_rd);
			seq_म_लिखो(m, "%2x ", byte_rd);
		पूर्ण
	पूर्ण

	seq_माला_दो(m, "\n####################page 1##################\n ");
	क्रम (n = 0; n <= max;) अणु
		seq_म_लिखो(m, "\nD:  %2x > ", n);

		क्रम (i = 0; i < 16 && n <= max; i++, n++) अणु
			पढ़ो_nic_byte(dev, 0x100 | n, &byte_rd);
			seq_म_लिखो(m, "%2x ", byte_rd);
		पूर्ण
	पूर्ण

	seq_माला_दो(m, "\n####################page 3##################\n ");
	क्रम (n = 0; n <= max;) अणु
		seq_म_लिखो(m, "\nD:  %2x > ", n);

		क्रम (i = 0; i < 16 && n <= max; i++, n++) अणु
			पढ़ो_nic_byte(dev, 0x300 | n, &byte_rd);
			seq_म_लिखो(m, "%2x ", byte_rd);
		पूर्ण
	पूर्ण

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused proc_get_stats_tx(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा net_device *dev = m->निजी;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);

	seq_म_लिखो(m,
		   "TX VI priority ok int: %lu\n"
		   "TX VI priority error int: %lu\n"
		   "TX VO priority ok int: %lu\n"
		   "TX VO priority error int: %lu\n"
		   "TX BE priority ok int: %lu\n"
		   "TX BE priority error int: %lu\n"
		   "TX BK priority ok int: %lu\n"
		   "TX BK priority error int: %lu\n"
		   "TX MANAGE priority ok int: %lu\n"
		   "TX MANAGE priority error int: %lu\n"
		   "TX BEACON priority ok int: %lu\n"
		   "TX BEACON priority error int: %lu\n"
		   "TX queue resume: %lu\n"
		   "TX queue stopped?: %d\n"
		   "TX fifo overflow: %lu\n"
		   "TX VI queue: %d\n"
		   "TX VO queue: %d\n"
		   "TX BE queue: %d\n"
		   "TX BK queue: %d\n"
		   "TX VI dropped: %lu\n"
		   "TX VO dropped: %lu\n"
		   "TX BE dropped: %lu\n"
		   "TX BK dropped: %lu\n"
		   "TX total data packets %lu\n",
		   priv->stats.txviokपूर्णांक,
		   priv->stats.txvierr,
		   priv->stats.txvookपूर्णांक,
		   priv->stats.txvoerr,
		   priv->stats.txbeokपूर्णांक,
		   priv->stats.txbeerr,
		   priv->stats.txbkokपूर्णांक,
		   priv->stats.txbkerr,
		   priv->stats.txmanageokपूर्णांक,
		   priv->stats.txmanageerr,
		   priv->stats.txbeaconokपूर्णांक,
		   priv->stats.txbeaconerr,
		   priv->stats.txresumed,
		   netअगर_queue_stopped(dev),
		   priv->stats.txoverflow,
		   atomic_पढ़ो(&(priv->tx_pending[VI_PRIORITY])),
		   atomic_पढ़ो(&(priv->tx_pending[VO_PRIORITY])),
		   atomic_पढ़ो(&(priv->tx_pending[BE_PRIORITY])),
		   atomic_पढ़ो(&(priv->tx_pending[BK_PRIORITY])),
		   priv->stats.txvidrop,
		   priv->stats.txvodrop,
		   priv->stats.txbedrop,
		   priv->stats.txbkdrop,
		   priv->stats.txdatapkt
		);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused proc_get_stats_rx(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा net_device *dev = m->निजी;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);

	seq_म_लिखो(m,
		   "RX packets: %lu\n"
		   "RX urb status error: %lu\n"
		   "RX invalid urb error: %lu\n",
		   priv->stats.rxoktotal,
		   priv->stats.rxstaterr,
		   priv->stats.rxurberr);

	वापस 0;
पूर्ण

अटल व्योम rtl8192_proc_module_init(व्योम)
अणु
	RT_TRACE(COMP_INIT, "Initializing proc filesystem");
	rtl8192_proc = proc_सूची_गढ़ो(RTL819XU_MODULE_NAME, init_net.proc_net);
पूर्ण

अटल व्योम rtl8192_proc_init_one(काष्ठा net_device *dev)
अणु
	काष्ठा proc_dir_entry *dir;

	अगर (!rtl8192_proc)
		वापस;

	dir = proc_सूची_गढ़ो_data(dev->name, 0, rtl8192_proc, dev);
	अगर (!dir)
		वापस;

	proc_create_single("stats-rx", S_IFREG | 0444, dir,
			   proc_get_stats_rx);
	proc_create_single("stats-tx", S_IFREG | 0444, dir,
			   proc_get_stats_tx);
	proc_create_single("stats-ap", S_IFREG | 0444, dir,
			   proc_get_stats_ap);
	proc_create_single("registers", S_IFREG | 0444, dir,
			   proc_get_रेजिस्टरs);
पूर्ण

अटल व्योम rtl8192_proc_हटाओ_one(काष्ठा net_device *dev)
अणु
	हटाओ_proc_subtree(dev->name, rtl8192_proc);
पूर्ण

/****************************************************************************
 *  -----------------------------MISC STUFF-------------------------
 *****************************************************************************/

लघु check_nic_enough_desc(काष्ठा net_device *dev, पूर्णांक queue_index)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक used = atomic_पढ़ो(&priv->tx_pending[queue_index]);

	वापस (used < MAX_TX_URB);
पूर्ण

अटल व्योम tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	schedule_work(&priv->reset_wq);
पूर्ण

व्योम rtl8192_update_msr(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8 msr;

	पढ़ो_nic_byte(dev, MSR, &msr);
	msr &= ~MSR_LINK_MASK;

	/* करो not change in link_state != WLAN_LINK_ASSOCIATED.
	 * msr must be updated अगर the state is ASSOCIATING.
	 * this is पूर्णांकentional and make sense क्रम ad-hoc and
	 * master (see the create BSS/IBSS func)
	 */
	अगर (priv->ieee80211->state == IEEE80211_LINKED) अणु
		अगर (priv->ieee80211->iw_mode == IW_MODE_INFRA)
			msr |= (MSR_LINK_MANAGED << MSR_LINK_SHIFT);
		अन्यथा अगर (priv->ieee80211->iw_mode == IW_MODE_ADHOC)
			msr |= (MSR_LINK_ADHOC << MSR_LINK_SHIFT);
		अन्यथा अगर (priv->ieee80211->iw_mode == IW_MODE_MASTER)
			msr |= (MSR_LINK_MASTER << MSR_LINK_SHIFT);

	पूर्ण अन्यथा अणु
		msr |= (MSR_LINK_NONE << MSR_LINK_SHIFT);
	पूर्ण

	ग_लिखो_nic_byte(dev, MSR, msr);
पूर्ण

व्योम rtl8192_set_chan(काष्ठा net_device *dev, लघु ch)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);

	RT_TRACE(COMP_CH, "=====>%s()====ch:%d\n", __func__, ch);
	priv->chan = ch;

	/* this hack should aव्योम frame TX during channel setting*/

	/* need to implement rf set channel here */

	अगर (priv->rf_set_chan)
		priv->rf_set_chan(dev, priv->chan);
	mdelay(10);
पूर्ण

अटल व्योम rtl8192_rx_isr(काष्ठा urb *urb);

अटल u32 get_rxpacket_shअगरtbytes_819xusb(काष्ठा ieee80211_rx_stats *pstats)
अणु
	वापस (माप(काष्ठा rx_desc_819x_usb) + pstats->RxDrvInfoSize
		+ pstats->RxBufShअगरt);
पूर्ण

व्योम rtl8192_rx_enable(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा urb *entry;
	काष्ठा sk_buff *skb;
	काष्ठा rtl8192_rx_info *info;

	/* nomal packet rx procedure */
	जबतक (skb_queue_len(&priv->rx_queue) < MAX_RX_URB) अणु
		skb = __dev_alloc_skb(RX_URB_SIZE, GFP_KERNEL);
		अगर (!skb)
			अवरोध;
		entry = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!entry) अणु
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
		usb_fill_bulk_urb(entry, priv->udev,
				  usb_rcvbulkpipe(priv->udev, 3),
				  skb_tail_poपूर्णांकer(skb),
				  RX_URB_SIZE, rtl8192_rx_isr, skb);
		info = (काष्ठा rtl8192_rx_info *)skb->cb;
		info->urb = entry;
		info->dev = dev;
		info->out_pipe = 3; /* denote rx normal packet queue */
		skb_queue_tail(&priv->rx_queue, skb);
		usb_submit_urb(entry, GFP_KERNEL);
	पूर्ण

	/* command packet rx procedure */
	जबतक (skb_queue_len(&priv->rx_queue) < MAX_RX_URB + 3) अणु
		skb = __dev_alloc_skb(RX_URB_SIZE, GFP_KERNEL);
		अगर (!skb)
			अवरोध;
		entry = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!entry) अणु
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
		usb_fill_bulk_urb(entry, priv->udev,
				  usb_rcvbulkpipe(priv->udev, 9),
				  skb_tail_poपूर्णांकer(skb),
				  RX_URB_SIZE, rtl8192_rx_isr, skb);
		info = (काष्ठा rtl8192_rx_info *)skb->cb;
		info->urb = entry;
		info->dev = dev;
		info->out_pipe = 9; /* denote rx cmd packet queue */
		skb_queue_tail(&priv->rx_queue, skb);
		usb_submit_urb(entry, GFP_KERNEL);
	पूर्ण
पूर्ण

व्योम rtl8192_set_rxconf(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	u32 rxconf;

	पढ़ो_nic_dword(dev, RCR, &rxconf);
	rxconf = rxconf & ~MAC_FILTER_MASK;
	rxconf = rxconf | RCR_AMF;
	rxconf = rxconf | RCR_ADF;
	rxconf = rxconf | RCR_AB;
	rxconf = rxconf | RCR_AM;

	अगर (dev->flags & IFF_PROMISC)
		DMESG("NIC in promisc mode");

	अगर (priv->ieee80211->iw_mode == IW_MODE_MONITOR ||
	    dev->flags & IFF_PROMISC) अणु
		rxconf = rxconf | RCR_AAP;
	पूर्ण अन्यथा अणु
		rxconf = rxconf | RCR_APM;
		rxconf = rxconf | RCR_CBSSID;
	पूर्ण

	अगर (priv->ieee80211->iw_mode == IW_MODE_MONITOR) अणु
		rxconf = rxconf | RCR_AICV;
		rxconf = rxconf | RCR_APWRMGT;
	पूर्ण

	अगर (priv->crcmon == 1 && priv->ieee80211->iw_mode == IW_MODE_MONITOR)
		rxconf = rxconf | RCR_ACRC32;

	rxconf = rxconf & ~RX_FIFO_THRESHOLD_MASK;
	rxconf = rxconf | (RX_FIFO_THRESHOLD_NONE << RX_FIFO_THRESHOLD_SHIFT);
	rxconf = rxconf & ~MAX_RX_DMA_MASK;
	rxconf = rxconf | ((u32)7 << RCR_MXDMA_OFFSET);

	rxconf = rxconf | RCR_ONLYERLPKT;

	ग_लिखो_nic_dword(dev, RCR, rxconf);
पूर्ण

व्योम rtl8192_rtx_disable(काष्ठा net_device *dev)
अणु
	u8 cmd;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा sk_buff *skb;
	काष्ठा rtl8192_rx_info *info;

	पढ़ो_nic_byte(dev, CMDR, &cmd);
	ग_लिखो_nic_byte(dev, CMDR, cmd & ~(CR_TE | CR_RE));
	क्रमce_pci_posting(dev);
	mdelay(10);

	जबतक ((skb = __skb_dequeue(&priv->rx_queue))) अणु
		info = (काष्ठा rtl8192_rx_info *)skb->cb;
		अगर (!info->urb)
			जारी;

		usb_समाप्त_urb(info->urb);
		kमुक्त_skb(skb);
	पूर्ण

	अगर (skb_queue_len(&priv->skb_queue))
		netdev_warn(dev, "skb_queue not empty\n");

	skb_queue_purge(&priv->skb_queue);
पूर्ण

/* The prototype of rx_isr has changed since one version of Linux Kernel */
अटल व्योम rtl8192_rx_isr(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)urb->context;
	काष्ठा rtl8192_rx_info *info = (काष्ठा rtl8192_rx_info *)skb->cb;
	काष्ठा net_device *dev = info->dev;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक out_pipe = info->out_pipe;
	पूर्णांक err;

	अगर (!priv->up)
		वापस;

	अगर (unlikely(urb->status)) अणु
		info->urb = शून्य;
		priv->stats.rxstaterr++;
		priv->ieee80211->stats.rx_errors++;
		usb_मुक्त_urb(urb);
		वापस;
	पूर्ण
	skb_unlink(skb, &priv->rx_queue);
	skb_put(skb, urb->actual_length);

	skb_queue_tail(&priv->skb_queue, skb);
	tasklet_schedule(&priv->irq_rx_tasklet);

	skb = dev_alloc_skb(RX_URB_SIZE);
	अगर (unlikely(!skb)) अणु
		usb_मुक्त_urb(urb);
		netdev_err(dev, "%s(): can't alloc skb\n", __func__);
		/* TODO check rx queue length and refill *somewhere* */
		वापस;
	पूर्ण

	usb_fill_bulk_urb(urb, priv->udev,
			  usb_rcvbulkpipe(priv->udev, out_pipe),
			  skb_tail_poपूर्णांकer(skb),
			  RX_URB_SIZE, rtl8192_rx_isr, skb);

	info = (काष्ठा rtl8192_rx_info *)skb->cb;
	info->urb = urb;
	info->dev = dev;
	info->out_pipe = out_pipe;

	urb->transfer_buffer = skb_tail_poपूर्णांकer(skb);
	urb->context = skb;
	skb_queue_tail(&priv->rx_queue, skb);
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err && err != -EPERM)
		netdev_err(dev,
			   "can not submit rxurb, err is %x, URB status is %x\n",
			   err, urb->status);
पूर्ण

अटल u32 rtl819xusb_rx_command_packet(काष्ठा net_device *dev,
					काष्ठा ieee80211_rx_stats *pstats)
अणु
	u32	status;

	status = cmpk_message_handle_rx(dev, pstats);
	अगर (status)
		DMESG("rxcommandpackethandle819xusb: It is a command packet\n");

	वापस status;
पूर्ण

अटल व्योम rtl8192_data_hard_stop(काष्ठा net_device *dev)
अणु
	/* FIXME !! */
पूर्ण

अटल व्योम rtl8192_data_hard_resume(काष्ठा net_device *dev)
अणु
	/* FIXME !! */
पूर्ण

/* this function TX data frames when the ieee80211 stack requires this.
 * It checks also अगर we need to stop the ieee tx queue, eventually करो it
 */
अटल व्योम rtl8192_hard_data_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   पूर्णांक rate)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	u8 queue_index = tcb_desc->queue_index;

	/* shall not be referred by command packet */
	RTL8192U_ASSERT(queue_index != TXCMD_QUEUE);

	spin_lock_irqsave(&priv->tx_lock, flags);

	*(काष्ठा net_device **)(skb->cb) = dev;
	tcb_desc->bTxEnableFwCalcDur = 1;
	skb_push(skb, priv->ieee80211->tx_headroom);
	ret = rtl8192_tx(dev, skb);

	spin_unlock_irqrestore(&priv->tx_lock, flags);
पूर्ण

/* This is a rough attempt to TX a frame
 * This is called by the ieee 80211 stack to TX management frames.
 * If the ring is full packet are dropped (क्रम data frame the queue
 * is stopped beक्रमe this can happen).
 */
अटल पूर्णांक rtl8192_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	u8 queue_index = tcb_desc->queue_index;

	spin_lock_irqsave(&priv->tx_lock, flags);

	स_नकल((अचिन्हित अक्षर *)(skb->cb), &dev, माप(dev));
	अगर (queue_index == TXCMD_QUEUE) अणु
		skb_push(skb, USB_HWDESC_HEADER_LEN);
		rtl819xU_tx_cmd(dev, skb);
		ret = 1;
	पूर्ण अन्यथा अणु
		skb_push(skb, priv->ieee80211->tx_headroom);
		ret = rtl8192_tx(dev, skb);
	पूर्ण

	spin_unlock_irqrestore(&priv->tx_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम rtl8192_tx_isr(काष्ठा urb *tx_urb)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)tx_urb->context;
	काष्ठा net_device *dev;
	काष्ठा r8192_priv *priv = शून्य;
	काष्ठा cb_desc *tcb_desc;
	u8  queue_index;

	अगर (!skb)
		वापस;

	dev = *(काष्ठा net_device **)(skb->cb);
	tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	queue_index = tcb_desc->queue_index;

	priv = ieee80211_priv(dev);

	अगर (tcb_desc->queue_index != TXCMD_QUEUE) अणु
		अगर (tx_urb->status == 0) अणु
			netअगर_trans_update(dev);
			priv->stats.txoktotal++;
			priv->ieee80211->LinkDetectInfo.NumTxOkInPeriod++;
			priv->stats.txbytesunicast +=
				(skb->len - priv->ieee80211->tx_headroom);
		पूर्ण अन्यथा अणु
			priv->ieee80211->stats.tx_errors++;
			/* TODO */
		पूर्ण
	पूर्ण

	/* मुक्त skb and tx_urb */
	dev_kमुक्त_skb_any(skb);
	usb_मुक्त_urb(tx_urb);
	atomic_dec(&priv->tx_pending[queue_index]);

	/*
	 * Handle HW Beacon:
	 * We had transfer our beacon frame to host controller at this moment.
	 *
	 *
	 * Caution:
	 * Handling the रुको queue of command packets.
	 * For Tx command packets, we must not करो TCB fragment because it is
	 * not handled right now. We must cut the packets to match the size of
	 * TX_CMD_PKT beक्रमe we send it.
	 */

	/* Handle MPDU in रुको queue. */
	अगर (queue_index != BEACON_QUEUE) अणु
		/* Don't send data frame during scanning.*/
		अगर ((skb_queue_len(&priv->ieee80211->skb_रुकोQ[queue_index]) != 0) &&
		    (!(priv->ieee80211->queue_stop))) अणु
			skb = skb_dequeue(&(priv->ieee80211->skb_रुकोQ[queue_index]));
			अगर (skb)
				priv->ieee80211->sofपंचांगac_hard_start_xmit(skb,
									 dev);

			वापस; /* aव्योम further processing AMSDU */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl8192_config_rate(काष्ठा net_device *dev, u16 *rate_config)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_network *net;
	u8 i = 0, basic_rate = 0;

	net = &priv->ieee80211->current_network;

	क्रम (i = 0; i < net->rates_len; i++) अणु
		basic_rate = net->rates[i] & 0x7f;
		चयन (basic_rate) अणु
		हाल MGN_1M:
			*rate_config |= RRSR_1M;
			अवरोध;
		हाल MGN_2M:
			*rate_config |= RRSR_2M;
			अवरोध;
		हाल MGN_5_5M:
			*rate_config |= RRSR_5_5M;
			अवरोध;
		हाल MGN_11M:
			*rate_config |= RRSR_11M;
			अवरोध;
		हाल MGN_6M:
			*rate_config |= RRSR_6M;
			अवरोध;
		हाल MGN_9M:
			*rate_config |= RRSR_9M;
			अवरोध;
		हाल MGN_12M:
			*rate_config |= RRSR_12M;
			अवरोध;
		हाल MGN_18M:
			*rate_config |= RRSR_18M;
			अवरोध;
		हाल MGN_24M:
			*rate_config |= RRSR_24M;
			अवरोध;
		हाल MGN_36M:
			*rate_config |= RRSR_36M;
			अवरोध;
		हाल MGN_48M:
			*rate_config |= RRSR_48M;
			अवरोध;
		हाल MGN_54M:
			*rate_config |= RRSR_54M;
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < net->rates_ex_len; i++) अणु
		basic_rate = net->rates_ex[i] & 0x7f;
		चयन (basic_rate) अणु
		हाल MGN_1M:
			*rate_config |= RRSR_1M;
			अवरोध;
		हाल MGN_2M:
			*rate_config |= RRSR_2M;
			अवरोध;
		हाल MGN_5_5M:
			*rate_config |= RRSR_5_5M;
			अवरोध;
		हाल MGN_11M:
			*rate_config |= RRSR_11M;
			अवरोध;
		हाल MGN_6M:
			*rate_config |= RRSR_6M;
			अवरोध;
		हाल MGN_9M:
			*rate_config |= RRSR_9M;
			अवरोध;
		हाल MGN_12M:
			*rate_config |= RRSR_12M;
			अवरोध;
		हाल MGN_18M:
			*rate_config |= RRSR_18M;
			अवरोध;
		हाल MGN_24M:
			*rate_config |= RRSR_24M;
			अवरोध;
		हाल MGN_36M:
			*rate_config |= RRSR_36M;
			अवरोध;
		हाल MGN_48M:
			*rate_config |= RRSR_48M;
			अवरोध;
		हाल MGN_54M:
			*rate_config |= RRSR_54M;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा SHORT_SLOT_TIME 9
#घोषणा NON_SHORT_SLOT_TIME 20

अटल व्योम rtl8192_update_cap(काष्ठा net_device *dev, u16 cap)
अणु
	u32 पंचांगp = 0;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_network *net = &priv->ieee80211->current_network;

	priv->लघु_preamble = cap & WLAN_CAPABILITY_SHORT_PREAMBLE;
	पंचांगp = priv->basic_rate;
	अगर (priv->लघु_preamble)
		पंचांगp |= BRSR_AckShortPmb;
	ग_लिखो_nic_dword(dev, RRSR, पंचांगp);

	अगर (net->mode & (IEEE_G | IEEE_N_24G)) अणु
		u8 slot_समय = 0;

		अगर ((cap & WLAN_CAPABILITY_SHORT_SLOT) &&
		    (!priv->ieee80211->pHTInfo->bCurrentRT2RTLongSlotTime))
			/* लघु slot समय */
			slot_समय = SHORT_SLOT_TIME;
		अन्यथा	/* दीर्घ slot समय */
			slot_समय = NON_SHORT_SLOT_TIME;
		priv->slot_समय = slot_समय;
		ग_लिखो_nic_byte(dev, SLOT_TIME, slot_समय);
	पूर्ण
पूर्ण

अटल व्योम rtl8192_net_update(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_network *net;
	u16 BcnTimeCfg = 0, BcnCW = 6, BcnIFS = 0xf;
	u16 rate_config = 0;

	net = &priv->ieee80211->current_network;

	rtl8192_config_rate(dev, &rate_config);
	priv->basic_rate = rate_config & 0x15f;

	ग_लिखो_nic_dword(dev, BSSIDR, ((u32 *)net->bssid)[0]);
	ग_लिखो_nic_word(dev, BSSIDR + 4, ((u16 *)net->bssid)[2]);

	rtl8192_update_msr(dev);
	अगर (priv->ieee80211->iw_mode == IW_MODE_ADHOC) अणु
		ग_लिखो_nic_word(dev, ATIMWND, 2);
		ग_लिखो_nic_word(dev, BCN_DMATIME, 1023);
		ग_लिखो_nic_word(dev, BCN_INTERVAL, net->beacon_पूर्णांकerval);
		ग_लिखो_nic_word(dev, BCN_DRV_EARLY_INT, 1);
		ग_लिखो_nic_byte(dev, BCN_ERR_THRESH, 100);
		BcnTimeCfg |= (BcnCW << BCN_TCFG_CW_SHIFT);
		/* TODO: BcnIFS may required to be changed on ASIC */
		BcnTimeCfg |= BcnIFS << BCN_TCFG_IFS;

		ग_लिखो_nic_word(dev, BCN_TCFG, BcnTimeCfg);
	पूर्ण
पूर्ण

/* temporary hw beacon is not used any more.
 * खोलो it when necessary
 */
व्योम rtl819xusb_beacon_tx(काष्ठा net_device *dev, u16  tx_rate)
अणु
पूर्ण

लघु rtl819xU_tx_cmd(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक			status;
	काष्ठा urb		*tx_urb;
	अचिन्हित पूर्णांक		idx_pipe;
	काष्ठा tx_desc_cmd_819x_usb *pdesc = (काष्ठा tx_desc_cmd_819x_usb *)skb->data;
	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	u8 queue_index = tcb_desc->queue_index;

	atomic_inc(&priv->tx_pending[queue_index]);
	tx_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!tx_urb) अणु
		dev_kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(pdesc, 0, USB_HWDESC_HEADER_LEN);
	/* Tx descriptor ought to be set according to the skb->cb */
	pdesc->FirstSeg = 1;
	pdesc->LastSeg = 1;
	pdesc->CmdInit = tcb_desc->bCmdOrInit;
	pdesc->TxBufferSize = tcb_desc->txbuf_size;
	pdesc->OWN = 1;
	pdesc->LINIP = tcb_desc->bLastIniPkt;

	/*---------------------------------------------------------------------
	 * Fill up USB_OUT_CONTEXT.
	 *---------------------------------------------------------------------
	 */
	idx_pipe = 0x04;
	usb_fill_bulk_urb(tx_urb, priv->udev,
			  usb_sndbulkpipe(priv->udev, idx_pipe),
			  skb->data, skb->len, rtl8192_tx_isr, skb);

	status = usb_submit_urb(tx_urb, GFP_ATOMIC);

	अगर (!status)
		वापस 0;

	DMESGE("Error TX CMD URB, error %d", status);
	dev_kमुक्त_skb(skb);
	usb_मुक्त_urb(tx_urb);
	वापस -1;
पूर्ण

/*
 * Mapping Software/Hardware descriptor queue id to "Queue Select Field"
 * in TxFwInfo data काष्ठाure
 * 2006.10.30 by Emily
 *
 * \param QUEUEID       Software Queue
 */
अटल u8 MapHwQueueToFirmwareQueue(u8 QueueID)
अणु
	u8 QueueSelect = 0x0;       /* शेष set to */

	चयन (QueueID) अणु
	हाल BE_QUEUE:
		QueueSelect = QSLT_BE;
		अवरोध;

	हाल BK_QUEUE:
		QueueSelect = QSLT_BK;
		अवरोध;

	हाल VO_QUEUE:
		QueueSelect = QSLT_VO;
		अवरोध;

	हाल VI_QUEUE:
		QueueSelect = QSLT_VI;
		अवरोध;
	हाल MGNT_QUEUE:
		QueueSelect = QSLT_MGNT;
		अवरोध;

	हाल BEACON_QUEUE:
		QueueSelect = QSLT_BEACON;
		अवरोध;

		/* TODO: mark other queue selection until we verअगरy it is OK */
		/* TODO: Remove Assertions */
	हाल TXCMD_QUEUE:
		QueueSelect = QSLT_CMD;
		अवरोध;
	हाल HIGH_QUEUE:
		QueueSelect = QSLT_HIGH;
		अवरोध;

	शेष:
		RT_TRACE(COMP_ERR,
			 "TransmitTCB(): Impossible Queue Selection: %d\n",
			 QueueID);
		अवरोध;
	पूर्ण
	वापस QueueSelect;
पूर्ण

अटल u8 MRateToHwRate8190Pci(u8 rate)
अणु
	u8  ret = DESC90_RATE1M;

	चयन (rate) अणु
	हाल MGN_1M:
		ret = DESC90_RATE1M;
		अवरोध;
	हाल MGN_2M:
		ret = DESC90_RATE2M;
		अवरोध;
	हाल MGN_5_5M:
		ret = DESC90_RATE5_5M;
		अवरोध;
	हाल MGN_11M:
		ret = DESC90_RATE11M;
		अवरोध;
	हाल MGN_6M:
		ret = DESC90_RATE6M;
		अवरोध;
	हाल MGN_9M:
		ret = DESC90_RATE9M;
		अवरोध;
	हाल MGN_12M:
		ret = DESC90_RATE12M;
		अवरोध;
	हाल MGN_18M:
		ret = DESC90_RATE18M;
		अवरोध;
	हाल MGN_24M:
		ret = DESC90_RATE24M;
		अवरोध;
	हाल MGN_36M:
		ret = DESC90_RATE36M;
		अवरोध;
	हाल MGN_48M:
		ret = DESC90_RATE48M;
		अवरोध;
	हाल MGN_54M:
		ret = DESC90_RATE54M;
		अवरोध;

	/* HT rate since here */
	हाल MGN_MCS0:
		ret = DESC90_RATEMCS0;
		अवरोध;
	हाल MGN_MCS1:
		ret = DESC90_RATEMCS1;
		अवरोध;
	हाल MGN_MCS2:
		ret = DESC90_RATEMCS2;
		अवरोध;
	हाल MGN_MCS3:
		ret = DESC90_RATEMCS3;
		अवरोध;
	हाल MGN_MCS4:
		ret = DESC90_RATEMCS4;
		अवरोध;
	हाल MGN_MCS5:
		ret = DESC90_RATEMCS5;
		अवरोध;
	हाल MGN_MCS6:
		ret = DESC90_RATEMCS6;
		अवरोध;
	हाल MGN_MCS7:
		ret = DESC90_RATEMCS7;
		अवरोध;
	हाल MGN_MCS8:
		ret = DESC90_RATEMCS8;
		अवरोध;
	हाल MGN_MCS9:
		ret = DESC90_RATEMCS9;
		अवरोध;
	हाल MGN_MCS10:
		ret = DESC90_RATEMCS10;
		अवरोध;
	हाल MGN_MCS11:
		ret = DESC90_RATEMCS11;
		अवरोध;
	हाल MGN_MCS12:
		ret = DESC90_RATEMCS12;
		अवरोध;
	हाल MGN_MCS13:
		ret = DESC90_RATEMCS13;
		अवरोध;
	हाल MGN_MCS14:
		ret = DESC90_RATEMCS14;
		अवरोध;
	हाल MGN_MCS15:
		ret = DESC90_RATEMCS15;
		अवरोध;
	हाल (0x80 | 0x20):
		ret = DESC90_RATEMCS32;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल u8 QueryIsShort(u8 TxHT, u8 TxRate, काष्ठा cb_desc *tcb_desc)
अणु
	u8   पंचांगp_Short;

	पंचांगp_Short = (TxHT == 1) ?
			((tcb_desc->bUseShortGI) ? 1 : 0) :
			((tcb_desc->bUseShortPreamble) ? 1 : 0);

	अगर (TxHT == 1 && TxRate != DESC90_RATEMCS15)
		पंचांगp_Short = 0;

	वापस पंचांगp_Short;
पूर्ण

अटल व्योम tx_zero_isr(काष्ठा urb *tx_urb)
अणु
पूर्ण

/*
 * The tx procedure is just as following,
 * skb->cb will contain all the following inक्रमmation,
 * priority, morefrag, rate, &dev.
 */
लघु rtl8192_tx(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	काष्ठा tx_desc_819x_usb *tx_desc = (काष्ठा tx_desc_819x_usb *)skb->data;
	काष्ठा tx_fwinfo_819x_usb *tx_fwinfo =
		(काष्ठा tx_fwinfo_819x_usb *)(skb->data + USB_HWDESC_HEADER_LEN);
	काष्ठा usb_device *udev = priv->udev;
	पूर्णांक pend;
	पूर्णांक status, rt = -1;
	काष्ठा urb *tx_urb = शून्य, *tx_urb_zero = शून्य;
	अचिन्हित पूर्णांक idx_pipe;

	pend = atomic_पढ़ो(&priv->tx_pending[tcb_desc->queue_index]);
	/* we are locked here so the two atomic_पढ़ो and inc are executed
	 * without पूर्णांकerleaves
	 * !!! For debug purpose
	 */
	अगर (pend > MAX_TX_URB) अणु
		netdev_dbg(dev, "To discard skb packet!\n");
		dev_kमुक्त_skb_any(skb);
		वापस -1;
	पूर्ण

	tx_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!tx_urb) अणु
		dev_kमुक्त_skb_any(skb);
		वापस -ENOMEM;
	पूर्ण

	/* Fill Tx firmware info */
	स_रखो(tx_fwinfo, 0, माप(काष्ठा tx_fwinfo_819x_usb));
	/* DWORD 0 */
	tx_fwinfo->TxHT = (tcb_desc->data_rate & 0x80) ? 1 : 0;
	tx_fwinfo->TxRate = MRateToHwRate8190Pci(tcb_desc->data_rate);
	tx_fwinfo->EnableCPUDur = tcb_desc->bTxEnableFwCalcDur;
	tx_fwinfo->Short = QueryIsShort(tx_fwinfo->TxHT, tx_fwinfo->TxRate,
					tcb_desc);
	अगर (tcb_desc->bAMPDUEnable) अणु /* AMPDU enabled */
		tx_fwinfo->AllowAggregation = 1;
		/* DWORD 1 */
		tx_fwinfo->RxMF = tcb_desc->ampdu_factor;
		tx_fwinfo->RxAMD = tcb_desc->ampdu_density & 0x07;
	पूर्ण अन्यथा अणु
		tx_fwinfo->AllowAggregation = 0;
		/* DWORD 1 */
		tx_fwinfo->RxMF = 0;
		tx_fwinfo->RxAMD = 0;
	पूर्ण

	/* Protection mode related */
	tx_fwinfo->RtsEnable = (tcb_desc->bRTSEnable) ? 1 : 0;
	tx_fwinfo->CtsEnable = (tcb_desc->bCTSEnable) ? 1 : 0;
	tx_fwinfo->RtsSTBC = (tcb_desc->bRTSSTBC) ? 1 : 0;
	tx_fwinfo->RtsHT = (tcb_desc->rts_rate & 0x80) ? 1 : 0;
	tx_fwinfo->RtsRate =  MRateToHwRate8190Pci((u8)tcb_desc->rts_rate);
	tx_fwinfo->RtsSubcarrier = (tx_fwinfo->RtsHT == 0) ? (tcb_desc->RTSSC) : 0;
	tx_fwinfo->RtsBandwidth = (tx_fwinfo->RtsHT == 1) ? ((tcb_desc->bRTSBW) ? 1 : 0) : 0;
	tx_fwinfo->RtsShort = (tx_fwinfo->RtsHT == 0) ? (tcb_desc->bRTSUseShortPreamble ? 1 : 0) :
			      (tcb_desc->bRTSUseShortGI ? 1 : 0);

	/* Set Bandwidth and sub-channel settings. */
	अगर (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20_40) अणु
		अगर (tcb_desc->bPacketBW) अणु
			tx_fwinfo->TxBandwidth = 1;
			/* use duplicated mode */
			tx_fwinfo->TxSubCarrier = 0;
		पूर्ण अन्यथा अणु
			tx_fwinfo->TxBandwidth = 0;
			tx_fwinfo->TxSubCarrier = priv->nCur40MhzPrimeSC;
		पूर्ण
	पूर्ण अन्यथा अणु
		tx_fwinfo->TxBandwidth = 0;
		tx_fwinfo->TxSubCarrier = 0;
	पूर्ण

	/* Fill Tx descriptor */
	स_रखो(tx_desc, 0, माप(काष्ठा tx_desc_819x_usb));
	/* DWORD 0 */
	tx_desc->LINIP = 0;
	tx_desc->CmdInit = 1;
	tx_desc->Offset =  माप(काष्ठा tx_fwinfo_819x_usb) + 8;
	tx_desc->PktSize = (skb->len - TX_PACKET_SHIFT_BYTES) & 0xffff;

	/*DWORD 1*/
	tx_desc->SecCAMID = 0;
	tx_desc->RATid = tcb_desc->RATRIndex;
	tx_desc->NoEnc = 1;
	tx_desc->SecType = 0x0;
	अगर (tcb_desc->bHwSec) अणु
		चयन (priv->ieee80211->pairwise_key_type) अणु
		हाल KEY_TYPE_WEP40:
		हाल KEY_TYPE_WEP104:
			tx_desc->SecType = 0x1;
			tx_desc->NoEnc = 0;
			अवरोध;
		हाल KEY_TYPE_TKIP:
			tx_desc->SecType = 0x2;
			tx_desc->NoEnc = 0;
			अवरोध;
		हाल KEY_TYPE_CCMP:
			tx_desc->SecType = 0x3;
			tx_desc->NoEnc = 0;
			अवरोध;
		हाल KEY_TYPE_NA:
			tx_desc->SecType = 0x0;
			tx_desc->NoEnc = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	tx_desc->QueueSelect = MapHwQueueToFirmwareQueue(tcb_desc->queue_index);
	tx_desc->TxFWInfoSize =  माप(काष्ठा tx_fwinfo_819x_usb);

	tx_desc->DISFB = tcb_desc->bTxDisableRateFallBack;
	tx_desc->USERATE = tcb_desc->bTxUseDriverAssingedRate;

	/* Fill fields that are required to be initialized in
	 * all of the descriptors
	 */
	/* DWORD 0 */
	tx_desc->FirstSeg = 1;
	tx_desc->LastSeg = 1;
	tx_desc->OWN = 1;

	/* DWORD 2 */
	tx_desc->TxBufferSize = (u32)(skb->len - USB_HWDESC_HEADER_LEN);
	idx_pipe = 0x5;

	/* To submit bulk urb */
	usb_fill_bulk_urb(tx_urb, udev,
			  usb_sndbulkpipe(udev, idx_pipe), skb->data,
			  skb->len, rtl8192_tx_isr, skb);

	status = usb_submit_urb(tx_urb, GFP_ATOMIC);
	अगर (!status) अणु
		/* We need to send 0 byte packet whenever
		 * 512N bytes/64N(HIGN SPEED/NORMAL SPEED) bytes packet has
		 * been transmitted. Otherwise, it will be halt to रुको क्रम
		 * another packet.
		 */
		bool bSend0Byte = false;
		u8 zero = 0;

		अगर (udev->speed == USB_SPEED_HIGH) अणु
			अगर (skb->len > 0 && skb->len % 512 == 0)
				bSend0Byte = true;
		पूर्ण अन्यथा अणु
			अगर (skb->len > 0 && skb->len % 64 == 0)
				bSend0Byte = true;
		पूर्ण
		अगर (bSend0Byte) अणु
			tx_urb_zero = usb_alloc_urb(0, GFP_ATOMIC);
			अगर (!tx_urb_zero) अणु
				rt = -ENOMEM;
				जाओ error;
			पूर्ण
			usb_fill_bulk_urb(tx_urb_zero, udev,
					  usb_sndbulkpipe(udev, idx_pipe),
					  &zero, 0, tx_zero_isr, dev);
			status = usb_submit_urb(tx_urb_zero, GFP_ATOMIC);
			अगर (status) अणु
				RT_TRACE(COMP_ERR,
					 "Error TX URB for zero byte %d, error %d",
					 atomic_पढ़ो(&priv->tx_pending[tcb_desc->queue_index]),
					 status);
				जाओ error;
			पूर्ण
		पूर्ण
		netअगर_trans_update(dev);
		atomic_inc(&priv->tx_pending[tcb_desc->queue_index]);
		वापस 0;
	पूर्ण

	RT_TRACE(COMP_ERR, "Error TX URB %d, error %d",
		 atomic_पढ़ो(&priv->tx_pending[tcb_desc->queue_index]),
		 status);

error:
	dev_kमुक्त_skb_any(skb);
	usb_मुक्त_urb(tx_urb);
	usb_मुक्त_urb(tx_urb_zero);
	वापस rt;
पूर्ण

अटल लघु rtl8192_usb_initendpoपूर्णांकs(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	priv->rx_urb = kदो_स्मृति_array(MAX_RX_URB + 1, माप(काष्ठा urb *),
				     GFP_KERNEL);
	अगर (!priv->rx_urb)
		वापस -ENOMEM;

#अगर_अघोषित JACKSON_NEW_RX
	क्रम (i = 0; i < (MAX_RX_URB + 1); i++) अणु
		priv->rx_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!priv->rx_urb[i])
			वापस -ENOMEM;

		priv->rx_urb[i]->transfer_buffer =
			kदो_स्मृति(RX_URB_SIZE, GFP_KERNEL);
		अगर (!priv->rx_urb[i]->transfer_buffer)
			वापस -ENOMEM;

		priv->rx_urb[i]->transfer_buffer_length = RX_URB_SIZE;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित THOMAS_BEACON
	अणु
		दीर्घ align = 0;
		व्योम *oldaddr, *newaddr;

		priv->rx_urb[16] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!priv->rx_urb[16])
			वापस -ENOMEM;
		priv->oldaddr = kदो_स्मृति(16, GFP_KERNEL);
		अगर (!priv->oldaddr)
			वापस -ENOMEM;
		oldaddr = priv->oldaddr;
		align = ((दीर्घ)oldaddr) & 3;
		अगर (align) अणु
			newaddr = oldaddr + 4 - align;
			priv->rx_urb[16]->transfer_buffer_length = 16 - 4 + align;
		पूर्ण अन्यथा अणु
			newaddr = oldaddr;
			priv->rx_urb[16]->transfer_buffer_length = 16;
		पूर्ण
		priv->rx_urb[16]->transfer_buffer = newaddr;
	पूर्ण
#पूर्ण_अगर

	स_रखो(priv->rx_urb, 0, माप(काष्ठा urb *) * MAX_RX_URB);
	priv->pp_rxskb = kसुस्मृति(MAX_RX_URB, माप(काष्ठा sk_buff *),
				 GFP_KERNEL);
	अगर (!priv->pp_rxskb) अणु
		kमुक्त(priv->rx_urb);

		priv->pp_rxskb = शून्य;
		priv->rx_urb = शून्य;

		DMESGE("Endpoint Alloc Failure");
		वापस -ENOMEM;
	पूर्ण

	netdev_dbg(dev, "End of initendpoints\n");
	वापस 0;
पूर्ण

#अगर_घोषित THOMAS_BEACON
अटल व्योम rtl8192_usb_deleteendpoपूर्णांकs(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->rx_urb) अणु
		क्रम (i = 0; i < (MAX_RX_URB + 1); i++) अणु
			usb_समाप्त_urb(priv->rx_urb[i]);
			usb_मुक्त_urb(priv->rx_urb[i]);
		पूर्ण
		kमुक्त(priv->rx_urb);
		priv->rx_urb = शून्य;
	पूर्ण
	kमुक्त(priv->oldaddr);
	priv->oldaddr = शून्य;

	kमुक्त(priv->pp_rxskb);
	priv->pp_rxskb = शून्य;
पूर्ण
#अन्यथा
व्योम rtl8192_usb_deleteendpoपूर्णांकs(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

#अगर_अघोषित JACKSON_NEW_RX

	अगर (priv->rx_urb) अणु
		क्रम (i = 0; i < (MAX_RX_URB + 1); i++) अणु
			usb_समाप्त_urb(priv->rx_urb[i]);
			kमुक्त(priv->rx_urb[i]->transfer_buffer);
			usb_मुक्त_urb(priv->rx_urb[i]);
		पूर्ण
		kमुक्त(priv->rx_urb);
		priv->rx_urb = शून्य;
	पूर्ण
#अन्यथा
	kमुक्त(priv->rx_urb);
	priv->rx_urb = शून्य;
	kमुक्त(priv->oldaddr);
	priv->oldaddr = शून्य;

	kमुक्त(priv->pp_rxskb);
	priv->pp_rxskb = 0;

#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

अटल व्योम rtl8192_update_ratr_table(काष्ठा net_device *dev);
अटल व्योम rtl8192_link_change(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_device *ieee = priv->ieee80211;

	अगर (ieee->state == IEEE80211_LINKED) अणु
		rtl8192_net_update(dev);
		rtl8192_update_ratr_table(dev);
		/* Add this as in pure N mode, wep encryption will use software
		 * way, but there is no chance to set this as wep will not set
		 * group key in wext.
		 */
		अगर (ieee->pairwise_key_type == KEY_TYPE_WEP40 ||
		    ieee->pairwise_key_type == KEY_TYPE_WEP104)
			EnableHWSecurityConfig8192(dev);
	पूर्ण
	/*update timing params*/
	अगर (ieee->iw_mode == IW_MODE_INFRA || ieee->iw_mode == IW_MODE_ADHOC) अणु
		u32 reg = 0;

		पढ़ो_nic_dword(dev, RCR, &reg);
		अगर (priv->ieee80211->state == IEEE80211_LINKED)
			priv->ReceiveConfig = reg |= RCR_CBSSID;
		अन्यथा
			priv->ReceiveConfig = reg &= ~RCR_CBSSID;
		ग_लिखो_nic_dword(dev, RCR, reg);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ieee80211_qos_parameters def_qos_parameters = अणु
	अणुcpu_to_le16(3), cpu_to_le16(3), cpu_to_le16(3), cpu_to_le16(3)पूर्ण,
	अणुcpu_to_le16(7), cpu_to_le16(7), cpu_to_le16(7), cpu_to_le16(7)पूर्ण,
	अणु2, 2, 2, 2पूर्ण,/* aअगरs */
	अणु0, 0, 0, 0पूर्ण,/* flags */
	अणु0, 0, 0, 0पूर्ण /* tx_op_limit */
पूर्ण;

अटल व्योम rtl8192_update_beacon(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा r8192_priv *priv = container_of(work, काष्ठा r8192_priv,
					       update_beacon_wq.work);
	काष्ठा net_device *dev = priv->ieee80211->dev;
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	काष्ठा ieee80211_network *net = &ieee->current_network;

	अगर (ieee->pHTInfo->bCurrentHTSupport)
		HTUpdateSelfAndPeerSetting(ieee, net);
	ieee->pHTInfo->bCurrentRT2RTLongSlotTime =
		net->bssht.bdRT2RTLongSlotTime;
	rtl8192_update_cap(dev, net->capability);
पूर्ण

/*
 * background support to run QoS activate functionality
 */
अटल पूर्णांक WDCAPARA_ADD[] = अणुEDCAPARA_BE, EDCAPARA_BK,
			     EDCAPARA_VI, EDCAPARA_VOपूर्ण;
अटल व्योम rtl8192_qos_activate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा r8192_priv *priv = container_of(work, काष्ठा r8192_priv,
					       qos_activate);
	काष्ठा net_device *dev = priv->ieee80211->dev;
	काष्ठा ieee80211_qos_parameters *qos_parameters =
		&priv->ieee80211->current_network.qos_data.parameters;
	u8 mode = priv->ieee80211->current_network.mode;
	u32  u1bAIFS;
	u32 u4bAcParam;
	u32 op_limit;
	u32 cw_max;
	u32 cw_min;
	पूर्णांक i;

	mutex_lock(&priv->mutex);
	अगर (priv->ieee80211->state != IEEE80211_LINKED)
		जाओ success;
	RT_TRACE(COMP_QOS,
		 "qos active process with associate response received\n");
	/* It better set slot समय at first
	 *
	 * For we just support b/g mode at present, let the slot समय at
	 * 9/20 selection
	 *
	 * update the ac parameter to related रेजिस्टरs
	 */
	क्रम (i = 0; i <  QOS_QUEUE_NUM; i++) अणु
		/* Mode G/A: slotTimeTimer = 9; Mode B: 20 */
		u1bAIFS = qos_parameters->aअगरs[i] * ((mode & (IEEE_G | IEEE_N_24G)) ? 9 : 20) + aSअगरsTime;
		u1bAIFS <<= AC_PARAM_AIFS_OFFSET;
		op_limit = (u32)le16_to_cpu(qos_parameters->tx_op_limit[i]);
		op_limit <<= AC_PARAM_TXOP_LIMIT_OFFSET;
		cw_max = (u32)le16_to_cpu(qos_parameters->cw_max[i]);
		cw_max <<= AC_PARAM_ECW_MAX_OFFSET;
		cw_min = (u32)le16_to_cpu(qos_parameters->cw_min[i]);
		cw_min <<= AC_PARAM_ECW_MIN_OFFSET;
		u4bAcParam = op_limit | cw_max | cw_min | u1bAIFS;
		ग_लिखो_nic_dword(dev, WDCAPARA_ADD[i], u4bAcParam);
	पूर्ण

success:
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक rtl8192_qos_handle_probe_response(काष्ठा r8192_priv *priv,
					     पूर्णांक active_network,
					     काष्ठा ieee80211_network *network)
अणु
	पूर्णांक ret = 0;
	u32 size = माप(काष्ठा ieee80211_qos_parameters);

	अगर (priv->ieee80211->state != IEEE80211_LINKED)
		वापस ret;

	अगर (priv->ieee80211->iw_mode != IW_MODE_INFRA)
		वापस ret;

	अगर (network->flags & NETWORK_HAS_QOS_MASK) अणु
		अगर (active_network &&
		    (network->flags & NETWORK_HAS_QOS_PARAMETERS))
			network->qos_data.active = network->qos_data.supported;

		अगर ((network->qos_data.active == 1) && (active_network == 1) &&
		    (network->flags & NETWORK_HAS_QOS_PARAMETERS) &&
		    (network->qos_data.old_param_count !=
		     network->qos_data.param_count)) अणु
			network->qos_data.old_param_count =
				network->qos_data.param_count;
			schedule_work(&priv->qos_activate);
			RT_TRACE(COMP_QOS,
				 "QoS parameters change call qos_activate\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(&priv->ieee80211->current_network.qos_data.parameters,
		       &def_qos_parameters, size);

		अगर ((network->qos_data.active == 1) && (active_network == 1)) अणु
			schedule_work(&priv->qos_activate);
			RT_TRACE(COMP_QOS,
				 "QoS was disabled call qos_activate\n");
		पूर्ण
		network->qos_data.active = 0;
		network->qos_data.supported = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* handle and manage frame from beacon and probe response */
अटल पूर्णांक rtl8192_handle_beacon(काष्ठा net_device *dev,
				 काष्ठा ieee80211_beacon *beacon,
				 काष्ठा ieee80211_network *network)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	rtl8192_qos_handle_probe_response(priv, 1, network);
	schedule_delayed_work(&priv->update_beacon_wq, 0);
	वापस 0;
पूर्ण

/*
 * handling the beaconing responses. अगर we get dअगरferent QoS setting
 * off the network from the associated setting, adjust the QoS
 * setting
 */
अटल पूर्णांक rtl8192_qos_association_resp(काष्ठा r8192_priv *priv,
					काष्ठा ieee80211_network *network)
अणु
	अचिन्हित दीर्घ flags;
	u32 size = माप(काष्ठा ieee80211_qos_parameters);
	पूर्णांक set_qos_param = 0;

	अगर (!priv || !network)
		वापस 0;

	अगर (priv->ieee80211->state != IEEE80211_LINKED)
		वापस 0;

	अगर (priv->ieee80211->iw_mode != IW_MODE_INFRA)
		वापस 0;

	spin_lock_irqsave(&priv->ieee80211->lock, flags);
	अगर (network->flags & NETWORK_HAS_QOS_PARAMETERS) अणु
		स_नकल(&priv->ieee80211->current_network.qos_data.parameters,
		       &network->qos_data.parameters,
		       माप(काष्ठा ieee80211_qos_parameters));
		priv->ieee80211->current_network.qos_data.active = 1;
		set_qos_param = 1;
		/* update qos parameter क्रम current network */
		priv->ieee80211->current_network.qos_data.old_param_count =
			priv->ieee80211->current_network.qos_data.param_count;
		priv->ieee80211->current_network.qos_data.param_count =
			network->qos_data.param_count;
	पूर्ण अन्यथा अणु
		स_नकल(&priv->ieee80211->current_network.qos_data.parameters,
		       &def_qos_parameters, size);
		priv->ieee80211->current_network.qos_data.active = 0;
		priv->ieee80211->current_network.qos_data.supported = 0;
		set_qos_param = 1;
	पूर्ण

	spin_unlock_irqrestore(&priv->ieee80211->lock, flags);

	RT_TRACE(COMP_QOS, "%s: network->flags = %d,%d\n", __func__,
		 network->flags,
		 priv->ieee80211->current_network.qos_data.active);
	अगर (set_qos_param == 1)
		schedule_work(&priv->qos_activate);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8192_handle_assoc_response(काष्ठा net_device *dev,
					 काष्ठा ieee80211_assoc_response_frame *resp,
					 काष्ठा ieee80211_network *network)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	rtl8192_qos_association_resp(priv, network);
	वापस 0;
पूर्ण

अटल व्योम rtl8192_update_ratr_table(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	u8 *pMcsRate = ieee->करोt11HTOperationalRateSet;
	u32 ratr_value = 0;
	u8 rate_index = 0;

	rtl8192_config_rate(dev, (u16 *)(&ratr_value));
	ratr_value |= (*(u16 *)(pMcsRate)) << 12;
	चयन (ieee->mode) अणु
	हाल IEEE_A:
		ratr_value &= 0x00000FF0;
		अवरोध;
	हाल IEEE_B:
		ratr_value &= 0x0000000F;
		अवरोध;
	हाल IEEE_G:
		ratr_value &= 0x00000FF7;
		अवरोध;
	हाल IEEE_N_24G:
	हाल IEEE_N_5G:
		अगर (ieee->pHTInfo->PeerMimoPs == MIMO_PS_STATIC) अणु
			ratr_value &= 0x0007F007;
		पूर्ण अन्यथा अणु
			अगर (priv->rf_type == RF_1T2R)
				ratr_value &= 0x000FF007;
			अन्यथा
				ratr_value &= 0x0F81F007;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ratr_value &= 0x0FFFFFFF;
	अगर (ieee->pHTInfo->bCurTxBW40MHz && ieee->pHTInfo->bCurShortGI40MHz)
		ratr_value |= 0x80000000;
	अन्यथा अगर (!ieee->pHTInfo->bCurTxBW40MHz &&
		 ieee->pHTInfo->bCurShortGI20MHz)
		ratr_value |= 0x80000000;
	ग_लिखो_nic_dword(dev, RATR0 + rate_index * 4, ratr_value);
	ग_लिखो_nic_byte(dev, UFWP, 1);
पूर्ण

अटल u8 ccmp_ie[4] = अणु0x00, 0x50, 0xf2, 0x04पूर्ण;
अटल u8 ccmp_rsn_ie[4] = अणु0x00, 0x0f, 0xac, 0x04पूर्ण;
अटल bool GetNmodeSupportBySecCfg8192(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	काष्ठा ieee80211_network *network = &ieee->current_network;
	पूर्णांक wpa_ie_len = ieee->wpa_ie_len;
	काष्ठा ieee80211_crypt_data *crypt;
	पूर्णांक encrypt;

	crypt = ieee->crypt[ieee->tx_keyidx];
	/* we use connecting AP's capability instead of only security config
	 * on our driver to distinguish whether it should use N mode or G mode
	 */
	encrypt = (network->capability & WLAN_CAPABILITY_PRIVACY) ||
		  (ieee->host_encrypt && crypt && crypt->ops &&
		   (म_भेद(crypt->ops->name, "WEP") == 0));

	/* simply judge  */
	अगर (encrypt && (wpa_ie_len == 0)) अणु
		/* wep encryption, no N mode setting */
		वापस false;
	पूर्ण अन्यथा अगर ((wpa_ie_len != 0)) अणु
		/* parse pairwise key type */
		अगर (((ieee->wpa_ie[0] == 0xdd) && (!स_भेद(&(ieee->wpa_ie[14]), ccmp_ie, 4))) || ((ieee->wpa_ie[0] == 0x30) && (!स_भेद(&ieee->wpa_ie[10], ccmp_rsn_ie, 4))))
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण अन्यथा अणु
		वापस true;
	पूर्ण

	वापस true;
पूर्ण

अटल bool GetHalfNmodeSupportByAPs819xUsb(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	वापस priv->ieee80211->bHalfWirelessN24GMode;
पूर्ण

अटल व्योम rtl8192_refresh_supportrate(काष्ठा r8192_priv *priv)
अणु
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	/* We करो not consider set support rate क्रम ABG mode, only
	 * HT MCS rate is set here.
	 */
	अगर (ieee->mode == WIRELESS_MODE_N_24G ||
	    ieee->mode == WIRELESS_MODE_N_5G)
		स_नकल(ieee->Regकरोt11HTOperationalRateSet,
		       ieee->RegHTSuppRateSet, 16);
	अन्यथा
		स_रखो(ieee->Regकरोt11HTOperationalRateSet, 0, 16);
पूर्ण

अटल u8 rtl8192_getSupportedWireleeMode(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8 ret = 0;

	चयन (priv->rf_chip) अणु
	हाल RF_8225:
	हाल RF_8256:
	हाल RF_PSEUDO_11N:
		ret = WIRELESS_MODE_N_24G | WIRELESS_MODE_G | WIRELESS_MODE_B;
		अवरोध;
	हाल RF_8258:
		ret = WIRELESS_MODE_A | WIRELESS_MODE_N_5G;
		अवरोध;
	शेष:
		ret = WIRELESS_MODE_B;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम rtl8192_SetWirelessMode(काष्ठा net_device *dev, u8 wireless_mode)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8 bSupportMode = rtl8192_getSupportedWireleeMode(dev);

	अगर (wireless_mode == WIRELESS_MODE_AUTO ||
	    (wireless_mode & bSupportMode) == 0) अणु
		अगर (bSupportMode & WIRELESS_MODE_N_24G) अणु
			wireless_mode = WIRELESS_MODE_N_24G;
		पूर्ण अन्यथा अगर (bSupportMode & WIRELESS_MODE_N_5G) अणु
			wireless_mode = WIRELESS_MODE_N_5G;
		पूर्ण अन्यथा अगर ((bSupportMode & WIRELESS_MODE_A)) अणु
			wireless_mode = WIRELESS_MODE_A;
		पूर्ण अन्यथा अगर ((bSupportMode & WIRELESS_MODE_G)) अणु
			wireless_mode = WIRELESS_MODE_G;
		पूर्ण अन्यथा अगर ((bSupportMode & WIRELESS_MODE_B)) अणु
			wireless_mode = WIRELESS_MODE_B;
		पूर्ण अन्यथा अणु
			RT_TRACE(COMP_ERR,
				 "%s(), No valid wireless mode supported, SupportedWirelessMode(%x)!!!\n",
				 __func__, bSupportMode);
			wireless_mode = WIRELESS_MODE_B;
		पूर्ण
	पूर्ण
	priv->ieee80211->mode = wireless_mode;

	अगर (wireless_mode == WIRELESS_MODE_N_24G ||
	    wireless_mode == WIRELESS_MODE_N_5G)
		priv->ieee80211->pHTInfo->bEnableHT = 1;
	अन्यथा
		priv->ieee80211->pHTInfo->bEnableHT = 0;
	RT_TRACE(COMP_INIT, "Current Wireless Mode is %x\n", wireless_mode);
	rtl8192_refresh_supportrate(priv);
पूर्ण

/* init priv variables here. only non_zero value should be initialized here. */
अटल पूर्णांक rtl8192_init_priv_variable(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8 i;

	priv->card_8192 = NIC_8192U;
	priv->chan = 1; /* set to channel 1 */
	priv->ieee80211->mode = WIRELESS_MODE_AUTO; /* SET AUTO */
	priv->ieee80211->iw_mode = IW_MODE_INFRA;
	priv->ieee80211->ieee_up = 0;
	priv->retry_rts = DEFAULT_RETRY_RTS;
	priv->retry_data = DEFAULT_RETRY_DATA;
	priv->ieee80211->rts = DEFAULT_RTS_THRESHOLD;
	priv->ieee80211->rate = 110; /* 11 mbps */
	priv->ieee80211->लघु_slot = 1;
	priv->promisc = (dev->flags & IFF_PROMISC) ? 1 : 0;
	priv->CckPwEnl = 6;
	/* क्रम silent reset */
	priv->IrpPendingCount = 1;
	priv->ResetProgress = RESET_TYPE_NORESET;
	priv->bForcedSilentReset = false;
	priv->bDisableNormalResetCheck = false;
	priv->क्रमce_reset = false;

	/* we करोn't use FW पढ़ो/ग_लिखो RF until stable firmware is available. */
	priv->ieee80211->FwRWRF = 0;
	priv->ieee80211->current_network.beacon_पूर्णांकerval =
		DEFAULT_BEACONINTERVAL;
	priv->ieee80211->sofपंचांगac_features  = IEEE_SOFTMAC_SCAN |
		IEEE_SOFTMAC_ASSOCIATE | IEEE_SOFTMAC_PROBERQ |
		IEEE_SOFTMAC_PROBERS | IEEE_SOFTMAC_TX_QUEUE |
		IEEE_SOFTMAC_BEACONS;

	priv->ieee80211->active_scan = 1;
	priv->ieee80211->modulation =
		IEEE80211_CCK_MODULATION | IEEE80211_OFDM_MODULATION;
	priv->ieee80211->host_encrypt = 1;
	priv->ieee80211->host_decrypt = 1;
	priv->ieee80211->start_send_beacons = शून्य;
	priv->ieee80211->stop_send_beacons = शून्य;
	priv->ieee80211->sofपंचांगac_hard_start_xmit = rtl8192_hard_start_xmit;
	priv->ieee80211->set_chan = rtl8192_set_chan;
	priv->ieee80211->link_change = rtl8192_link_change;
	priv->ieee80211->sofपंचांगac_data_hard_start_xmit = rtl8192_hard_data_xmit;
	priv->ieee80211->data_hard_stop = rtl8192_data_hard_stop;
	priv->ieee80211->data_hard_resume = rtl8192_data_hard_resume;
	priv->ieee80211->init_wmmparam_flag = 0;
	priv->ieee80211->fts = DEFAULT_FRAG_THRESHOLD;
	priv->ieee80211->check_nic_enough_desc = check_nic_enough_desc;
	priv->ieee80211->tx_headroom = TX_PACKET_SHIFT_BYTES;
	priv->ieee80211->qos_support = 1;

	priv->ieee80211->SetBWModeHandler = rtl8192_SetBWMode;
	priv->ieee80211->handle_assoc_response = rtl8192_handle_assoc_response;
	priv->ieee80211->handle_beacon = rtl8192_handle_beacon;

	priv->ieee80211->GetNmodeSupportBySecCfg = GetNmodeSupportBySecCfg8192;
	priv->ieee80211->GetHalfNmodeSupportByAPsHandler =
		GetHalfNmodeSupportByAPs819xUsb;
	priv->ieee80211->SetWirelessMode = rtl8192_SetWirelessMode;

	priv->ieee80211->InitialGainHandler = InitialGain819xUsb;
	priv->card_type = USB;
	priv->ShortRetryLimit = 0x30;
	priv->LongRetryLimit = 0x30;
	priv->EarlyRxThreshold = 7;
	priv->enable_gpio0 = 0;
	priv->TransmitConfig =
		/* Max DMA Burst Size per Tx DMA Burst, 7: reserved. */
		(TCR_MXDMA_2048 << TCR_MXDMA_OFFSET)	  |
		/* Short retry limit */
		(priv->ShortRetryLimit << TCR_SRL_OFFSET) |
		/* Long retry limit */
		(priv->LongRetryLimit << TCR_LRL_OFFSET)  |
		/* FALSE: HW provides PLCP length and LENGEXT
		 * TRUE: SW provides them
		 */
		(false ? TCR_SAT : 0);
	priv->ReceiveConfig	=
		/* accept management/data */
		RCR_AMF | RCR_ADF |
		/* accept control frame क्रम SW AP needs PS-poll */
		RCR_ACF |
		/* accept BC/MC/UC */
		RCR_AB | RCR_AM | RCR_APM |
		/* Max DMA Burst Size per Rx DMA Burst, 7: unlimited. */
		((u32)7 << RCR_MXDMA_OFFSET) |
		/* Rx FIFO Threshold, 7: No Rx threshold. */
		(priv->EarlyRxThreshold << RX_FIFO_THRESHOLD_SHIFT) |
		(priv->EarlyRxThreshold == 7 ? RCR_ONLYERLPKT : 0);

	priv->AcmControl = 0;
	priv->pFirmware = kzalloc(माप(rt_firmware), GFP_KERNEL);
	अगर (!priv->pFirmware)
		वापस -ENOMEM;

	/* rx related queue */
	skb_queue_head_init(&priv->rx_queue);
	skb_queue_head_init(&priv->skb_queue);

	/* Tx related queue */
	क्रम (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_head_init(&priv->ieee80211->skb_रुकोQ[i]);
	क्रम (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_head_init(&priv->ieee80211->skb_aggQ[i]);
	क्रम (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_head_init(&priv->ieee80211->skb_drv_aggQ[i]);
	priv->rf_set_chan = rtl8192_phy_SwChnl;

	वापस 0;
पूर्ण

/* init lock here */
अटल व्योम rtl8192_init_priv_lock(काष्ठा r8192_priv *priv)
अणु
	spin_lock_init(&priv->tx_lock);
	spin_lock_init(&priv->irq_lock);
	mutex_init(&priv->wx_mutex);
	mutex_init(&priv->mutex);
पूर्ण

अटल व्योम rtl819x_watchकरोg_wqcallback(काष्ठा work_काष्ठा *work);

अटल व्योम rtl8192_irq_rx_tasklet(काष्ठा tasklet_काष्ठा *t);
/* init tasklet and रुको_queue here. only 2.6 above kernel is considered */
#घोषणा DRV_NAME "wlan0"
अटल व्योम rtl8192_init_priv_task(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	INIT_WORK(&priv->reset_wq, rtl8192_restart);

	INIT_DELAYED_WORK(&priv->watch_करोg_wq,
			  rtl819x_watchकरोg_wqcallback);
	INIT_DELAYED_WORK(&priv->txघातer_tracking_wq,
			  dm_txघातer_trackingcallback);
	INIT_DELAYED_WORK(&priv->rfpath_check_wq,
			  dm_rf_pathcheck_workitemcallback);
	INIT_DELAYED_WORK(&priv->update_beacon_wq,
			  rtl8192_update_beacon);
	INIT_DELAYED_WORK(&priv->initialgain_operate_wq,
			  InitialGainOperateWorkItemCallBack);
	INIT_WORK(&priv->qos_activate, rtl8192_qos_activate);

	tasklet_setup(&priv->irq_rx_tasklet, rtl8192_irq_rx_tasklet);
पूर्ण

अटल व्योम rtl8192_get_eeprom_size(काष्ठा net_device *dev)
अणु
	u16 curCR = 0;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	RT_TRACE(COMP_EPROM, "===========>%s()\n", __func__);
	पढ़ो_nic_word_E(dev, EPROM_CMD, &curCR);
	RT_TRACE(COMP_EPROM,
		 "read from Reg EPROM_CMD(%x):%x\n", EPROM_CMD, curCR);
	/* whether need I consider BIT(5?) */
	priv->epromtype =
		(curCR & Cmd9346CR_9356SEL) ? EPROM_93c56 : EPROM_93c46;
	RT_TRACE(COMP_EPROM,
		 "<===========%s(), epromtype:%d\n", __func__, priv->epromtype);
पूर्ण

/* used to swap endian. as ntohl & htonl are not necessary
 * to swap endian, so use this instead.
 */
अटल अंतरभूत u16 endian_swap(u16 *data)
अणु
	u16 पंचांगp = *data;
	*data = (पंचांगp >> 8) | (पंचांगp << 8);
	वापस *data;
पूर्ण

अटल पूर्णांक rtl8192_पढ़ो_eeprom_info(काष्ठा net_device *dev)
अणु
	u16 wEPROM_ID = 0;
	u8 bMac_Tmp_Addr[6] = अणु0x00, 0xe0, 0x4c, 0x00, 0x00, 0x02पूर्ण;
	u8 bLoad_From_EEPOM = false;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u16 पंचांगpValue = 0;
	पूर्णांक i;
	पूर्णांक ret;

	RT_TRACE(COMP_EPROM, "===========>%s()\n", __func__);
	ret = eprom_पढ़ो(dev, 0); /* first पढ़ो EEPROM ID out; */
	अगर (ret < 0)
		वापस ret;
	wEPROM_ID = (u16)ret;
	RT_TRACE(COMP_EPROM, "EEPROM ID is 0x%x\n", wEPROM_ID);

	अगर (wEPROM_ID != RTL8190_EEPROM_ID)
		RT_TRACE(COMP_ERR,
			 "EEPROM ID is invalid(is 0x%x(should be 0x%x)\n",
			 wEPROM_ID, RTL8190_EEPROM_ID);
	अन्यथा
		bLoad_From_EEPOM = true;

	अगर (bLoad_From_EEPOM) अणु
		पंचांगpValue = eprom_पढ़ो(dev, EEPROM_VID >> 1);
		ret = eprom_पढ़ो(dev, EEPROM_VID >> 1);
		अगर (ret < 0)
			वापस ret;
		पंचांगpValue = (u16)ret;
		priv->eeprom_vid = endian_swap(&पंचांगpValue);
		ret = eprom_पढ़ो(dev, EEPROM_PID >> 1);
		अगर (ret < 0)
			वापस ret;
		priv->eeprom_pid = (u16)ret;
		ret = eprom_पढ़ो(dev, EEPROM_CHANNEL_PLAN >> 1);
		अगर (ret < 0)
			वापस ret;
		पंचांगpValue = (u16)ret;
		priv->eeprom_ChannelPlan = (पंचांगpValue & 0xff00) >> 8;
		priv->btxघातerdata_पढ़ोfromEEPORM = true;
		ret = eprom_पढ़ो(dev, (EEPROM_CUSTOMER_ID >> 1)) >> 8;
		अगर (ret < 0)
			वापस ret;
		priv->eeprom_CustomerID = (u16)ret;
	पूर्ण अन्यथा अणु
		priv->eeprom_vid = 0;
		priv->eeprom_pid = 0;
		priv->card_8192_version = VERSION_819XU_B;
		priv->eeprom_ChannelPlan = 0;
		priv->eeprom_CustomerID = 0;
	पूर्ण
	RT_TRACE(COMP_EPROM,
		 "vid:0x%4x, pid:0x%4x, CustomID:0x%2x, ChanPlan:0x%x\n",
		 priv->eeprom_vid, priv->eeprom_pid, priv->eeprom_CustomerID,
		 priv->eeprom_ChannelPlan);
	/* set channelplan from eeprom */
	priv->ChannelPlan = priv->eeprom_ChannelPlan;
	अगर (bLoad_From_EEPOM) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 6; i += 2) अणु
			ret = eprom_पढ़ो(dev, (u16)((EEPROM_NODE_ADDRESS_BYTE_0 + i) >> 1));
			अगर (ret < 0)
				वापस ret;
			*(u16 *)(&dev->dev_addr[i]) = (u16)ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(dev->dev_addr, bMac_Tmp_Addr, 6);
		/* should I set IDR0 here? */
	पूर्ण
	RT_TRACE(COMP_EPROM, "MAC addr:%pM\n", dev->dev_addr);
	priv->rf_type = RTL819X_DEFAULT_RF_TYPE; /* शेष 1T2R */
	priv->rf_chip = RF_8256;

	अगर (priv->card_8192_version == VERSION_819XU_A) अणु
		/* पढ़ो Tx घातer gain offset of legacy OFDM to HT rate */
		अगर (bLoad_From_EEPOM) अणु
			ret = eprom_पढ़ो(dev, (EEPROM_TX_POWER_DIFF >> 1));
			अगर (ret < 0)
				वापस ret;
			priv->EEPROMTxPowerDअगरf = ((u16)ret & 0xff00) >> 8;
		पूर्ण अन्यथा
			priv->EEPROMTxPowerDअगरf = EEPROM_DEFAULT_TX_POWER;
		RT_TRACE(COMP_EPROM, "TxPowerDiff:%d\n", priv->EEPROMTxPowerDअगरf);
		/* पढ़ो ThermalMeter from EEPROM */
		अगर (bLoad_From_EEPOM) अणु
			ret = eprom_पढ़ो(dev, (EEPROM_THERMAL_METER >> 1));
			अगर (ret < 0)
				वापस ret;
			priv->EEPROMThermalMeter = (u8)((u16)ret & 0x00ff);
		पूर्ण अन्यथा
			priv->EEPROMThermalMeter = EEPROM_DEFAULT_THERNAL_METER;
		RT_TRACE(COMP_EPROM, "ThermalMeter:%d\n", priv->EEPROMThermalMeter);
		/* क्रम tx घातer track */
		priv->TSSI_13dBm = priv->EEPROMThermalMeter * 100;
		/* पढ़ो antenna tx घातer offset of B/C/D to A from EEPROM */
		अगर (bLoad_From_EEPOM) अणु
			ret = eprom_पढ़ो(dev, (EEPROM_PW_DIFF >> 1));
			अगर (ret < 0)
				वापस ret;
			priv->EEPROMPwDअगरf = ((u16)ret & 0x0f00) >> 8;
		पूर्ण अन्यथा
			priv->EEPROMPwDअगरf = EEPROM_DEFAULT_PW_DIFF;
		RT_TRACE(COMP_EPROM, "TxPwDiff:%d\n", priv->EEPROMPwDअगरf);
		/* Read CrystalCap from EEPROM */
		अगर (bLoad_From_EEPOM) अणु
			ret = eprom_पढ़ो(dev, (EEPROM_CRYSTAL_CAP >> 1));
			अगर (ret < 0)
				वापस ret;
			priv->EEPROMCrystalCap = (u16)ret & 0x0f;
		पूर्ण अन्यथा
			priv->EEPROMCrystalCap = EEPROM_DEFAULT_CRYSTAL_CAP;
		RT_TRACE(COMP_EPROM, "CrystalCap = %d\n", priv->EEPROMCrystalCap);
		/* get per-channel Tx घातer level */
		अगर (bLoad_From_EEPOM) अणु
			ret = eprom_पढ़ो(dev, (EEPROM_TX_PW_INDEX_VER >> 1));
			अगर (ret < 0)
				वापस ret;
			priv->EEPROM_Def_Ver = ((u16)ret & 0xff00) >> 8;
		पूर्ण अन्यथा
			priv->EEPROM_Def_Ver = 1;
		RT_TRACE(COMP_EPROM, "EEPROM_DEF_VER:%d\n", priv->EEPROM_Def_Ver);
		अगर (priv->EEPROM_Def_Ver == 0) अणु /* old eeprom definition */
			पूर्णांक i;

			अगर (bLoad_From_EEPOM) अणु
				ret = eprom_पढ़ो(dev, (EEPROM_TX_PW_INDEX_CCK >> 1));
				अगर (ret < 0)
					वापस ret;
				priv->EEPROMTxPowerLevelCCK = ((u16)ret & 0xff00) >> 8;
			पूर्ण अन्यथा
				priv->EEPROMTxPowerLevelCCK = 0x10;
			RT_TRACE(COMP_EPROM, "CCK Tx Power Levl: 0x%02x\n", priv->EEPROMTxPowerLevelCCK);
			क्रम (i = 0; i < 3; i++) अणु
				अगर (bLoad_From_EEPOM) अणु
					ret = eprom_पढ़ो(dev, (EEPROM_TX_PW_INDEX_OFDM_24G + i) >> 1);
					अगर (ret < 0)
						वापस ret;
					अगर (((EEPROM_TX_PW_INDEX_OFDM_24G + i) % 2) == 0)
						पंचांगpValue = (u16)ret & 0x00ff;
					अन्यथा
						पंचांगpValue = ((u16)ret & 0xff00) >> 8;
				पूर्ण अन्यथा अणु
					पंचांगpValue = 0x10;
				पूर्ण
				priv->EEPROMTxPowerLevelOFDM24G[i] = (u8)पंचांगpValue;
				RT_TRACE(COMP_EPROM, "OFDM 2.4G Tx Power Level, Index %d = 0x%02x\n", i, priv->EEPROMTxPowerLevelCCK);
			पूर्ण
		पूर्ण अन्यथा अगर (priv->EEPROM_Def_Ver == 1) अणु
			अगर (bLoad_From_EEPOM) अणु
				ret = eprom_पढ़ो(dev, EEPROM_TX_PW_INDEX_CCK_V1 >> 1);
				अगर (ret < 0)
					वापस ret;
				पंचांगpValue = ((u16)ret & 0xff00) >> 8;
			पूर्ण अन्यथा अणु
				पंचांगpValue = 0x10;
			पूर्ण
			priv->EEPROMTxPowerLevelCCK_V1[0] = (u8)पंचांगpValue;

			अगर (bLoad_From_EEPOM) अणु
				ret = eprom_पढ़ो(dev, (EEPROM_TX_PW_INDEX_CCK_V1 + 2) >> 1);
				अगर (ret < 0)
					वापस ret;
				पंचांगpValue = (u16)ret;
			पूर्ण अन्यथा
				पंचांगpValue = 0x1010;
			*((u16 *)(&priv->EEPROMTxPowerLevelCCK_V1[1])) = पंचांगpValue;
			अगर (bLoad_From_EEPOM)
				पंचांगpValue = eprom_पढ़ो(dev,
					EEPROM_TX_PW_INDEX_OFDM_24G_V1 >> 1);
			अन्यथा
				पंचांगpValue = 0x1010;
			*((u16 *)(&priv->EEPROMTxPowerLevelOFDM24G[0])) = पंचांगpValue;
			अगर (bLoad_From_EEPOM)
				पंचांगpValue = eprom_पढ़ो(dev, (EEPROM_TX_PW_INDEX_OFDM_24G_V1 + 2) >> 1);
			अन्यथा
				पंचांगpValue = 0x10;
			priv->EEPROMTxPowerLevelOFDM24G[2] = (u8)पंचांगpValue;
		पूर्ण /* endअगर EEPROM_Def_Ver == 1 */

		/* update HAL variables */
		क्रम (i = 0; i < 14; i++) अणु
			अगर (i <= 3)
				priv->TxPowerLevelOFDM24G[i] = priv->EEPROMTxPowerLevelOFDM24G[0];
			अन्यथा अगर (i >= 4 && i <= 9)
				priv->TxPowerLevelOFDM24G[i] = priv->EEPROMTxPowerLevelOFDM24G[1];
			अन्यथा
				priv->TxPowerLevelOFDM24G[i] = priv->EEPROMTxPowerLevelOFDM24G[2];
		पूर्ण

		क्रम (i = 0; i < 14; i++) अणु
			अगर (priv->EEPROM_Def_Ver == 0) अणु
				अगर (i <= 3)
					priv->TxPowerLevelCCK[i] = priv->EEPROMTxPowerLevelOFDM24G[0] + (priv->EEPROMTxPowerLevelCCK - priv->EEPROMTxPowerLevelOFDM24G[1]);
				अन्यथा अगर (i >= 4 && i <= 9)
					priv->TxPowerLevelCCK[i] = priv->EEPROMTxPowerLevelCCK;
				अन्यथा
					priv->TxPowerLevelCCK[i] = priv->EEPROMTxPowerLevelOFDM24G[2] + (priv->EEPROMTxPowerLevelCCK - priv->EEPROMTxPowerLevelOFDM24G[1]);
			पूर्ण अन्यथा अगर (priv->EEPROM_Def_Ver == 1) अणु
				अगर (i <= 3)
					priv->TxPowerLevelCCK[i] = priv->EEPROMTxPowerLevelCCK_V1[0];
				अन्यथा अगर (i >= 4 && i <= 9)
					priv->TxPowerLevelCCK[i] = priv->EEPROMTxPowerLevelCCK_V1[1];
				अन्यथा
					priv->TxPowerLevelCCK[i] = priv->EEPROMTxPowerLevelCCK_V1[2];
			पूर्ण
		पूर्ण
		priv->TxPowerDअगरf = priv->EEPROMPwDअगरf;
		/* Antenna B gain offset to antenna A, bit0~3 */
		priv->AntennaTxPwDअगरf[0] = (priv->EEPROMTxPowerDअगरf & 0xf);
		/* Antenna C gain offset to antenna A, bit4~7 */
		priv->AntennaTxPwDअगरf[1] =
			(priv->EEPROMTxPowerDअगरf & 0xf0) >> 4;
		/* CrystalCap, bit12~15 */
		priv->CrystalCap = priv->EEPROMCrystalCap;
		/* ThermalMeter, bit0~3 क्रम RFIC1, bit4~7 क्रम RFIC2
		 * 92U करोes not enable TX घातer tracking.
		 */
		priv->ThermalMeter[0] = priv->EEPROMThermalMeter;
	पूर्ण /* end अगर VersionID == VERSION_819XU_A */

	/* क्रम dlink led */
	चयन (priv->eeprom_CustomerID) अणु
	हाल EEPROM_CID_RUNTOP:
		priv->CustomerID = RT_CID_819x_RUNTOP;
		अवरोध;

	हाल EEPROM_CID_DLINK:
		priv->CustomerID = RT_CID_DLINK;
		अवरोध;

	शेष:
		priv->CustomerID = RT_CID_DEFAULT;
		अवरोध;
	पूर्ण

	चयन (priv->CustomerID) अणु
	हाल RT_CID_819x_RUNTOP:
		priv->LedStrategy = SW_LED_MODE2;
		अवरोध;

	हाल RT_CID_DLINK:
		priv->LedStrategy = SW_LED_MODE4;
		अवरोध;

	शेष:
		priv->LedStrategy = SW_LED_MODE0;
		अवरोध;
	पूर्ण

	अगर (priv->rf_type == RF_1T2R)
		RT_TRACE(COMP_EPROM, "\n1T2R config\n");
	अन्यथा
		RT_TRACE(COMP_EPROM, "\n2T4R config\n");

	/* We can only know RF type in the function. So we have to init
	 * DIG RATR table again.
	 */
	init_rate_adaptive(dev);

	RT_TRACE(COMP_EPROM, "<===========%s()\n", __func__);

	वापस 0;
पूर्ण

अटल लघु rtl8192_get_channel_map(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->ChannelPlan > COUNTRY_CODE_GLOBAL_DOMAIN) अणु
		netdev_err(dev,
			   "rtl8180_init: Error channel plan! Set to default.\n");
		priv->ChannelPlan = 0;
	पूर्ण
	RT_TRACE(COMP_INIT, "Channel plan is %d\n", priv->ChannelPlan);

	rtl819x_set_channel_map(priv->ChannelPlan, priv);
	वापस 0;
पूर्ण

अटल लघु rtl8192_init(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक err;

	स_रखो(&(priv->stats), 0, माप(काष्ठा Stats));
	स_रखो(priv->txqueue_to_outpipemap, 0, 9);
#अगर_घोषित PIPE12
	अणु
		पूर्णांक i = 0;
		u8 queuetopipe[] = अणु3, 2, 1, 0, 4, 8, 7, 6, 5पूर्ण;

		स_नकल(priv->txqueue_to_outpipemap, queuetopipe, 9);
	पूर्ण
#अन्यथा
	अणु
		u8 queuetopipe[] = अणु3, 2, 1, 0, 4, 4, 0, 4, 4पूर्ण;

		स_नकल(priv->txqueue_to_outpipemap, queuetopipe, 9);
	पूर्ण
#पूर्ण_अगर
	err = rtl8192_init_priv_variable(dev);
	अगर (err)
		वापस err;

	rtl8192_init_priv_lock(priv);
	rtl8192_init_priv_task(dev);
	rtl8192_get_eeprom_size(dev);
	err = rtl8192_पढ़ो_eeprom_info(dev);
	अगर (err) अणु
		DMESG("Reading EEPROM info failed");
		वापस err;
	पूर्ण
	rtl8192_get_channel_map(dev);
	init_hal_dm(dev);
	समयr_setup(&priv->watch_करोg_समयr, watch_करोg_समयr_callback, 0);
	अगर (rtl8192_usb_initendpoपूर्णांकs(dev) != 0) अणु
		DMESG("Endopoints initialization failed");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 *function:  This function actually only set RRSR, RATR and BW_OPMODE रेजिस्टरs
 *	     not to करो all the hw config as its name says
 *   input:  net_device dev
 *  output:  none
 *  वापस:  none
 *  notice:  This part need to modअगरied according to the rate set we filtered
 * ****************************************************************************/
अटल व्योम rtl8192_hwconfig(काष्ठा net_device *dev)
अणु
	u32 regRATR = 0, regRRSR = 0;
	u8 regBwOpMode = 0, regTmp = 0;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32 ratr_value = 0;

	/* Set RRSR, RATR, and BW_OPMODE रेजिस्टरs */
	चयन (priv->ieee80211->mode) अणु
	हाल WIRELESS_MODE_B:
		regBwOpMode = BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_CCK;
		regRRSR = RATE_ALL_CCK;
		अवरोध;
	हाल WIRELESS_MODE_A:
		regBwOpMode = BW_OPMODE_5G | BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_OFDM_AG;
		regRRSR = RATE_ALL_OFDM_AG;
		अवरोध;
	हाल WIRELESS_MODE_G:
		regBwOpMode = BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		अवरोध;
	हाल WIRELESS_MODE_AUTO:
		regBwOpMode = BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG |
			  RATE_ALL_OFDM_1SS | RATE_ALL_OFDM_2SS;
		regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		अवरोध;
	हाल WIRELESS_MODE_N_24G:
		/* It support CCK rate by शेष. CCK rate will be filtered
		 * out only when associated AP करोes not support it.
		 */
		regBwOpMode = BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG |
			  RATE_ALL_OFDM_1SS | RATE_ALL_OFDM_2SS;
		regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		अवरोध;
	हाल WIRELESS_MODE_N_5G:
		regBwOpMode = BW_OPMODE_5G;
		regRATR = RATE_ALL_OFDM_AG | RATE_ALL_OFDM_1SS |
			  RATE_ALL_OFDM_2SS;
		regRRSR = RATE_ALL_OFDM_AG;
		अवरोध;
	पूर्ण

	ग_लिखो_nic_byte(dev, BW_OPMODE, regBwOpMode);
	ratr_value = regRATR;
	अगर (priv->rf_type == RF_1T2R)
		ratr_value &= ~(RATE_ALL_OFDM_2SS);
	ग_लिखो_nic_dword(dev, RATR0, ratr_value);
	ग_लिखो_nic_byte(dev, UFWP, 1);
	पढ़ो_nic_byte(dev, 0x313, &regTmp);
	regRRSR = ((regTmp) << 24) | (regRRSR & 0x00ffffff);
	ग_लिखो_nic_dword(dev, RRSR, regRRSR);

	/* Set Retry Limit here */
	ग_लिखो_nic_word(dev, RETRY_LIMIT,
		       priv->ShortRetryLimit << RETRY_LIMIT_SHORT_SHIFT |
		       priv->LongRetryLimit << RETRY_LIMIT_LONG_SHIFT);
	/* Set Contention Winकरोw here */

	/* Set Tx AGC */

	/* Set Tx Antenna including Feedback control */

	/* Set Auto Rate fallback control */
पूर्ण

/* InitializeAdapter and PhyCfg */
अटल bool rtl8192_adapter_start(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32 dwRegRead = 0;
	bool init_status = true;
	u8 SECR_value = 0x0;
	u8 पंचांगp;

	RT_TRACE(COMP_INIT, "====>%s()\n", __func__);
	priv->Rf_Mode = RF_OP_By_SW_3wire;
	/* क्रम ASIC घातer on sequence */
	ग_लिखो_nic_byte_E(dev, 0x5f, 0x80);
	mdelay(50);
	ग_लिखो_nic_byte_E(dev, 0x5f, 0xf0);
	ग_लिखो_nic_byte_E(dev, 0x5d, 0x00);
	ग_लिखो_nic_byte_E(dev, 0x5e, 0x80);
	ग_लिखो_nic_byte(dev, 0x17, 0x37);
	mdelay(10);
	priv->pFirmware->firmware_status = FW_STATUS_0_INIT;
	/* config CPUReset Register */
	/* Firmware Reset or not? */
	पढ़ो_nic_dword(dev, CPU_GEN, &dwRegRead);
	अगर (priv->pFirmware->firmware_status == FW_STATUS_0_INIT)
		dwRegRead |= CPU_GEN_SYSTEM_RESET; /* करो nothing here? */
	अन्यथा अगर (priv->pFirmware->firmware_status == FW_STATUS_5_READY)
		dwRegRead |= CPU_GEN_FIRMWARE_RESET;
	अन्यथा
		RT_TRACE(COMP_ERR,
			 "ERROR in %s(): undefined firmware state(%d)\n",
			 __func__,   priv->pFirmware->firmware_status);

	ग_लिखो_nic_dword(dev, CPU_GEN, dwRegRead);
	/* config BB. */
	rtl8192_BBConfig(dev);

	/* Loopback mode or not */
	priv->LoopbackMode = RTL819xU_NO_LOOPBACK;

	पढ़ो_nic_dword(dev, CPU_GEN, &dwRegRead);
	अगर (priv->LoopbackMode == RTL819xU_NO_LOOPBACK)
		dwRegRead = (dwRegRead & CPU_GEN_NO_LOOPBACK_MSK) |
			    CPU_GEN_NO_LOOPBACK_SET;
	अन्यथा अगर (priv->LoopbackMode == RTL819xU_MAC_LOOPBACK)
		dwRegRead |= CPU_CCK_LOOPBACK;
	अन्यथा
		RT_TRACE(COMP_ERR,
			 "Serious error in %s(): wrong loopback mode setting(%d)\n",
			 __func__,  priv->LoopbackMode);

	ग_लिखो_nic_dword(dev, CPU_GEN, dwRegRead);

	/* after reset cpu, we need रुको क्रम a seconds to ग_लिखो in रेजिस्टर. */
	udelay(500);

	/* add क्रम new bitfile:usb suspend reset pin set to 1. Do we need? */
	पढ़ो_nic_byte_E(dev, 0x5f, &पंचांगp);
	ग_लिखो_nic_byte_E(dev, 0x5f, पंचांगp | 0x20);

	/* Set Hardware */
	rtl8192_hwconfig(dev);

	/* turn on Tx/Rx */
	ग_लिखो_nic_byte(dev, CMDR, CR_RE | CR_TE);

	/* set IDR0 here */
	ग_लिखो_nic_dword(dev, MAC0, ((u32 *)dev->dev_addr)[0]);
	ग_लिखो_nic_word(dev, MAC4, ((u16 *)(dev->dev_addr + 4))[0]);

	/* set RCR */
	ग_लिखो_nic_dword(dev, RCR, priv->ReceiveConfig);

	/* Initialize Number of Reserved Pages in Firmware Queue */
	ग_लिखो_nic_dword(dev, RQPN1,
		NUM_OF_PAGE_IN_FW_QUEUE_BK << RSVD_FW_QUEUE_PAGE_BK_SHIFT |
		NUM_OF_PAGE_IN_FW_QUEUE_BE << RSVD_FW_QUEUE_PAGE_BE_SHIFT |
		NUM_OF_PAGE_IN_FW_QUEUE_VI << RSVD_FW_QUEUE_PAGE_VI_SHIFT |
		NUM_OF_PAGE_IN_FW_QUEUE_VO << RSVD_FW_QUEUE_PAGE_VO_SHIFT);
	ग_लिखो_nic_dword(dev, RQPN2,
		NUM_OF_PAGE_IN_FW_QUEUE_MGNT << RSVD_FW_QUEUE_PAGE_MGNT_SHIFT |
		NUM_OF_PAGE_IN_FW_QUEUE_CMD << RSVD_FW_QUEUE_PAGE_CMD_SHIFT);
	ग_लिखो_nic_dword(dev, RQPN3,
		APPLIED_RESERVED_QUEUE_IN_FW |
		NUM_OF_PAGE_IN_FW_QUEUE_BCN << RSVD_FW_QUEUE_PAGE_BCN_SHIFT);
	ग_लिखो_nic_dword(dev, RATR0 + 4 * 7, (RATE_ALL_OFDM_AG | RATE_ALL_CCK));

	/* Set AckTimeout */
	/* TODO: (it value is only क्रम FPGA version). need to be changed!! */
	ग_लिखो_nic_byte(dev, ACK_TIMEOUT, 0x30);

	अगर (priv->ResetProgress == RESET_TYPE_NORESET)
		rtl8192_SetWirelessMode(dev, priv->ieee80211->mode);
	अगर (priv->ResetProgress == RESET_TYPE_NORESET) अणु
		CamResetAllEntry(dev);
		SECR_value |= SCR_TxEncEnable;
		SECR_value |= SCR_RxDecEnable;
		SECR_value |= SCR_NoSKMC;
		ग_लिखो_nic_byte(dev, SECR, SECR_value);
	पूर्ण

	/* Beacon related */
	ग_लिखो_nic_word(dev, ATIMWND, 2);
	ग_लिखो_nic_word(dev, BCN_INTERVAL, 100);

#घोषणा DEFAULT_EDCA 0x005e4332
	अणु
		पूर्णांक i;

		क्रम (i = 0; i < QOS_QUEUE_NUM; i++)
			ग_लिखो_nic_dword(dev, WDCAPARA_ADD[i], DEFAULT_EDCA);
	पूर्ण

	rtl8192_phy_configmac(dev);

	अगर (priv->card_8192_version == VERSION_819XU_A) अणु
		rtl8192_phy_getTxPower(dev);
		rtl8192_phy_setTxPower(dev, priv->chan);
	पूर्ण

	/* Firmware करोwnload */
	init_status = init_firmware(dev);
	अगर (!init_status) अणु
		RT_TRACE(COMP_ERR, "ERR!!! %s(): Firmware download is failed\n",
			 __func__);
		वापस init_status;
	पूर्ण
	RT_TRACE(COMP_INIT, "%s():after firmware download\n", __func__);

	/* config RF. */
	अगर (priv->ResetProgress == RESET_TYPE_NORESET) अणु
		rtl8192_phy_RFConfig(dev);
		RT_TRACE(COMP_INIT, "%s():after phy RF config\n", __func__);
	पूर्ण

	अगर (priv->ieee80211->FwRWRF)
		/* We can क्रमce firmware to करो RF-R/W */
		priv->Rf_Mode = RF_OP_By_FW;
	अन्यथा
		priv->Rf_Mode = RF_OP_By_SW_3wire;

	rtl8192_phy_updateInitGain(dev);
	/*--set CCK and OFDM Block "ON"--*/
	rtl8192_setBBreg(dev, rFPGA0_RFMOD, bCCKEn, 0x1);
	rtl8192_setBBreg(dev, rFPGA0_RFMOD, bOFDMEn, 0x1);

	अगर (priv->ResetProgress == RESET_TYPE_NORESET) अणु
		/* अगर D or C cut */
		u8 पंचांगpvalue;

		पढ़ो_nic_byte(dev, 0x301, &पंचांगpvalue);
		अगर (पंचांगpvalue == 0x03) अणु
			priv->bDcut = true;
			RT_TRACE(COMP_POWER_TRACKING, "D-cut\n");
		पूर्ण अन्यथा अणु
			priv->bDcut = false;
			RT_TRACE(COMP_POWER_TRACKING, "C-cut\n");
		पूर्ण
		dm_initialize_txघातer_tracking(dev);

		अगर (priv->bDcut) अणु
			u32 i, TempCCk;
			u32 पंचांगpRegA = rtl8192_QueryBBReg(dev,
							 rOFDM0_XATxIQImbalance,
							 bMaskDWord);

			क्रम (i = 0; i < TxBBGainTableLength; i++) अणु
				अगर (पंचांगpRegA == priv->txbbgain_table[i].txbbgain_value) अणु
					priv->rfa_txघातertrackingindex = (u8)i;
					priv->rfa_txघातertrackingindex_real =
						(u8)i;
					priv->rfa_txघातertracking_शेष =
						priv->rfa_txघातertrackingindex;
					अवरोध;
				पूर्ण
			पूर्ण

			TempCCk = rtl8192_QueryBBReg(dev,
						     rCCK0_TxFilter1,
						     bMaskByte2);

			क्रम (i = 0; i < CCKTxBBGainTableLength; i++) अणु
				अगर (TempCCk == priv->cck_txbbgain_table[i].ccktxbb_valuearray[0]) अणु
					priv->cck_present_attenuation_20Mशेष = (u8)i;
					अवरोध;
				पूर्ण
			पूर्ण
			priv->cck_present_attenuation_40Mशेष = 0;
			priv->cck_present_attenuation_dअगरference = 0;
			priv->cck_present_attenuation =
				priv->cck_present_attenuation_20Mशेष;
		पूर्ण
	पूर्ण
	ग_लिखो_nic_byte(dev, 0x87, 0x0);

	वापस init_status;
पूर्ण

/* this configures रेजिस्टरs क्रम beacon tx and enables it via
 * rtl8192_beacon_tx_enable(). rtl8192_beacon_tx_disable() might
 * be used to stop beacon transmission
 */
/***************************************************************************
 *   -------------------------------NET STUFF---------------------------
 ***************************************************************************/

अटल काष्ठा net_device_stats *rtl8192_stats(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	वापस &priv->ieee80211->stats;
पूर्ण

अटल bool HalTxCheckStuck819xUsb(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u16		RegTxCounter;
	bool		bStuck = false;

	पढ़ो_nic_word(dev, 0x128, &RegTxCounter);
	RT_TRACE(COMP_RESET,
		 "%s():RegTxCounter is %d,TxCounter is %d\n", __func__,
		 RegTxCounter, priv->TxCounter);
	अगर (priv->TxCounter == RegTxCounter)
		bStuck = true;

	priv->TxCounter = RegTxCounter;

	वापस bStuck;
पूर्ण

/*
 *	<Assumption: RT_TX_SPINLOCK is acquired.>
 *	First added: 2006.11.19 by emily
 */
अटल RESET_TYPE TxCheckStuck(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8			QueueID;
	bool			bCheckFwTxCnt = false;

	/* Decide such threshold according to current घातer save mode */

	क्रम (QueueID = 0; QueueID <= BEACON_QUEUE; QueueID++) अणु
		अगर (QueueID == TXCMD_QUEUE)
			जारी;
		अगर ((skb_queue_len(&priv->ieee80211->skb_रुकोQ[QueueID]) == 0)  && (skb_queue_len(&priv->ieee80211->skb_aggQ[QueueID]) == 0))
			जारी;

		bCheckFwTxCnt = true;
	पूर्ण
	अगर (bCheckFwTxCnt) अणु
		अगर (HalTxCheckStuck819xUsb(dev)) अणु
			RT_TRACE(COMP_RESET,
				 "%s: Fw indicates no Tx condition!\n",
				 __func__);
			वापस RESET_TYPE_SILENT;
		पूर्ण
	पूर्ण
	वापस RESET_TYPE_NORESET;
पूर्ण

अटल bool HalRxCheckStuck819xUsb(काष्ठा net_device *dev)
अणु
	u16	RegRxCounter;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	bool bStuck = false;
	अटल u8	rx_chk_cnt;

	पढ़ो_nic_word(dev, 0x130, &RegRxCounter);
	RT_TRACE(COMP_RESET,
		 "%s(): RegRxCounter is %d,RxCounter is %d\n", __func__,
		 RegRxCounter, priv->RxCounter);
	/* If rssi is small, we should check rx क्रम दीर्घ समय because of bad rx.
	 * or maybe it will continuous silent reset every 2 seconds.
	 */
	rx_chk_cnt++;
	अगर (priv->undecorated_smoothed_pwdb >= (RATE_ADAPTIVE_TH_HIGH + 5)) अणु
		rx_chk_cnt = 0;	/* high rssi, check rx stuck right now. */
	पूर्ण अन्यथा अगर (priv->undecorated_smoothed_pwdb < (RATE_ADAPTIVE_TH_HIGH + 5) &&
		   ((priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20 && priv->undecorated_smoothed_pwdb >= RATE_ADAPTIVE_TH_LOW_40M) ||
		    (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20 && priv->undecorated_smoothed_pwdb >= RATE_ADAPTIVE_TH_LOW_20M))) अणु
		अगर (rx_chk_cnt < 2)
			वापस bStuck;

		rx_chk_cnt = 0;
	पूर्ण अन्यथा अगर (((priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20 && priv->undecorated_smoothed_pwdb < RATE_ADAPTIVE_TH_LOW_40M) ||
		    (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20 && priv->undecorated_smoothed_pwdb < RATE_ADAPTIVE_TH_LOW_20M)) &&
		     priv->undecorated_smoothed_pwdb >= VERY_LOW_RSSI) अणु
		अगर (rx_chk_cnt < 4)
			वापस bStuck;

		rx_chk_cnt = 0;
	पूर्ण अन्यथा अणु
		अगर (rx_chk_cnt < 8)
			वापस bStuck;

		rx_chk_cnt = 0;
	पूर्ण

	अगर (priv->RxCounter == RegRxCounter)
		bStuck = true;

	priv->RxCounter = RegRxCounter;

	वापस bStuck;
पूर्ण

अटल RESET_TYPE RxCheckStuck(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	bool        bRxCheck = false;

	अगर (priv->IrpPendingCount > 1)
		bRxCheck = true;

	अगर (bRxCheck) अणु
		अगर (HalRxCheckStuck819xUsb(dev)) अणु
			RT_TRACE(COMP_RESET, "RxStuck Condition\n");
			वापस RESET_TYPE_SILENT;
		पूर्ण
	पूर्ण
	वापस RESET_TYPE_NORESET;
पूर्ण

/**
 * This function is called by Checkक्रमhang to check whether we should
 * ask OS to reset driver
 *
 * \param pAdapter	The adapter context क्रम this miniport
 *
 * Note:NIC with USB पूर्णांकerface sholud not call this function because we
 * cannot scan descriptor to judge whether there is tx stuck.
 * Note: This function may be required to be reग_लिखो क्रम Vista OS.
 * <<<Assumption: Tx spinlock has been acquired >>>
 *
 * 8185 and 8185b करोes not implement this function.
 */
अटल RESET_TYPE rtl819x_अगरcheck_resetornot(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	RESET_TYPE	TxResetType = RESET_TYPE_NORESET;
	RESET_TYPE	RxResetType = RESET_TYPE_NORESET;
	RT_RF_POWER_STATE	rfState;

	rfState = priv->ieee80211->eRFPowerState;

	TxResetType = TxCheckStuck(dev);
	अगर (rfState != eRfOff ||
	    (priv->ieee80211->iw_mode != IW_MODE_ADHOC)) अणु
		/* If driver is in the status of firmware करोwnload failure,
		 * driver skips RF initialization and RF is in turned off
		 * state. Driver should check whether Rx stuck and करो silent
		 * reset. And अगर driver is in firmware करोwnload failure status,
		 * driver should initialize RF in the following silent reset
		 * procedure
		 *
		 * Driver should not check RX stuck in IBSS mode because it is
		 * required to set Check BSSID in order to send beacon,
		 * however, अगर check BSSID is set, STA cannot hear any packet
		 * at all.
		 */
		RxResetType = RxCheckStuck(dev);
	पूर्ण
	अगर (TxResetType == RESET_TYPE_NORMAL ||
	    RxResetType == RESET_TYPE_NORMAL) अणु
		वापस RESET_TYPE_NORMAL;
	पूर्ण अन्यथा अगर (TxResetType == RESET_TYPE_SILENT ||
		   RxResetType == RESET_TYPE_SILENT) अणु
		RT_TRACE(COMP_RESET, "%s():silent reset\n", __func__);
		वापस RESET_TYPE_SILENT;
	पूर्ण अन्यथा अणु
		वापस RESET_TYPE_NORESET;
	पूर्ण
पूर्ण

अटल व्योम rtl8192_cancel_deferred_work(काष्ठा r8192_priv *priv);
अटल पूर्णांक _rtl8192_up(काष्ठा net_device *dev);
अटल पूर्णांक rtl8192_बंद(काष्ठा net_device *dev);

अटल व्योम CamRestoreAllEntry(काष्ठा net_device *dev)
अणु
	u8 EntryId = 0;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8	*MacAddr = priv->ieee80211->current_network.bssid;

	अटल u8	CAM_CONST_ADDR[4][6] = अणु
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x01पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x02पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x03पूर्ण पूर्ण;
	अटल u8	CAM_CONST_BROAD[] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	RT_TRACE(COMP_SEC, "%s:\n", __func__);

	अगर ((priv->ieee80211->pairwise_key_type == KEY_TYPE_WEP40) ||
	    (priv->ieee80211->pairwise_key_type == KEY_TYPE_WEP104)) अणु
		क्रम (EntryId = 0; EntryId < 4; EntryId++) अणु
			MacAddr = CAM_CONST_ADDR[EntryId];
			setKey(dev, EntryId, EntryId,
			       priv->ieee80211->pairwise_key_type,
			       MacAddr, 0, शून्य);
		पूर्ण

	पूर्ण अन्यथा अगर (priv->ieee80211->pairwise_key_type == KEY_TYPE_TKIP) अणु
		अगर (priv->ieee80211->iw_mode == IW_MODE_ADHOC)
			setKey(dev, 4, 0, priv->ieee80211->pairwise_key_type,
			       (u8 *)dev->dev_addr, 0, शून्य);
		अन्यथा
			setKey(dev, 4, 0, priv->ieee80211->pairwise_key_type,
			       MacAddr, 0, शून्य);
	पूर्ण अन्यथा अगर (priv->ieee80211->pairwise_key_type == KEY_TYPE_CCMP) अणु
		अगर (priv->ieee80211->iw_mode == IW_MODE_ADHOC)
			setKey(dev, 4, 0, priv->ieee80211->pairwise_key_type,
			       (u8 *)dev->dev_addr, 0, शून्य);
		अन्यथा
			setKey(dev, 4, 0, priv->ieee80211->pairwise_key_type,
			       MacAddr, 0, शून्य);
	पूर्ण

	अगर (priv->ieee80211->group_key_type == KEY_TYPE_TKIP) अणु
		MacAddr = CAM_CONST_BROAD;
		क्रम (EntryId = 1; EntryId < 4; EntryId++) अणु
			setKey(dev, EntryId, EntryId,
			       priv->ieee80211->group_key_type,
			       MacAddr, 0, शून्य);
		पूर्ण
		अगर (priv->ieee80211->iw_mode == IW_MODE_ADHOC)
			setKey(dev, 0, 0, priv->ieee80211->group_key_type,
			       CAM_CONST_ADDR[0], 0, शून्य);
	पूर्ण अन्यथा अगर (priv->ieee80211->group_key_type == KEY_TYPE_CCMP) अणु
		MacAddr = CAM_CONST_BROAD;
		क्रम (EntryId = 1; EntryId < 4; EntryId++) अणु
			setKey(dev, EntryId, EntryId,
			       priv->ieee80211->group_key_type,
			       MacAddr, 0, शून्य);
		पूर्ण

		अगर (priv->ieee80211->iw_mode == IW_MODE_ADHOC)
			setKey(dev, 0, 0, priv->ieee80211->group_key_type,
			       CAM_CONST_ADDR[0], 0, शून्य);
	पूर्ण
पूर्ण

/* This function is used to fix Tx/Rx stop bug temporarily.
 * This function will करो "system reset" to NIC when Tx or Rx is stuck.
 * The method checking Tx/Rx stuck of this function is supported by FW,
 * which reports Tx and Rx counter to रेजिस्टर 0x128 and 0x130.
 */
अटल व्योम rtl819x_अगरsilentreset(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8	reset_बार = 0;
	पूर्णांक reset_status = 0;
	काष्ठा ieee80211_device *ieee = priv->ieee80211;

	/* If we need to check CCK stop, please uncomment this line. */
	/* bStuck = Adapter->HalFunc.CheckHWStopHandler(Adapter); */

	अगर (priv->ResetProgress == RESET_TYPE_NORESET) अणु
RESET_START:

		RT_TRACE(COMP_RESET, "=========>Reset progress!!\n");

		/* Set the variable क्रम reset. */
		priv->ResetProgress = RESET_TYPE_SILENT;
		mutex_lock(&priv->wx_mutex);
		अगर (priv->up == 0) अणु
			RT_TRACE(COMP_ERR,
				 "%s():the driver is not up! return\n",
				 __func__);
			mutex_unlock(&priv->wx_mutex);
			वापस;
		पूर्ण
		priv->up = 0;
		RT_TRACE(COMP_RESET,
			 "%s():======>start to down the driver\n",
			 __func__);

		rtl8192_rtx_disable(dev);
		rtl8192_cancel_deferred_work(priv);
		deinit_hal_dm(dev);
		del_समयr_sync(&priv->watch_करोg_समयr);

		ieee->sync_scan_hurryup = 1;
		अगर (ieee->state == IEEE80211_LINKED) अणु
			mutex_lock(&ieee->wx_mutex);
			netdev_dbg(dev, "ieee->state is IEEE80211_LINKED\n");
			ieee80211_stop_send_beacons(priv->ieee80211);
			del_समयr_sync(&ieee->associate_समयr);
			cancel_delayed_work(&ieee->associate_retry_wq);
			ieee80211_stop_scan(ieee);
			netअगर_carrier_off(dev);
			mutex_unlock(&ieee->wx_mutex);
		पूर्ण अन्यथा अणु
			netdev_dbg(dev, "ieee->state is NOT LINKED\n");
			ieee80211_sofपंचांगac_stop_protocol(priv->ieee80211);
		पूर्ण
		mutex_unlock(&priv->wx_mutex);
		RT_TRACE(COMP_RESET,
			 "%s():<==========down process is finished\n",
			 __func__);
		RT_TRACE(COMP_RESET,
			 "%s():===========>start up the driver\n",
			 __func__);
		reset_status = _rtl8192_up(dev);

		RT_TRACE(COMP_RESET,
			 "%s():<===========up process is finished\n",
			 __func__);
		अगर (reset_status == -EAGAIN) अणु
			अगर (reset_बार < 3) अणु
				reset_बार++;
				जाओ RESET_START;
			पूर्ण अन्यथा अणु
				RT_TRACE(COMP_ERR,
					 " ERR!!! %s():  Reset Failed!!\n",
					 __func__);
			पूर्ण
		पूर्ण
		ieee->is_silent_reset = 1;
		EnableHWSecurityConfig8192(dev);
		अगर (ieee->state == IEEE80211_LINKED &&
		    ieee->iw_mode == IW_MODE_INFRA) अणु
			ieee->set_chan(ieee->dev,
				       ieee->current_network.channel);

			queue_work(ieee->wq, &ieee->associate_complete_wq);

		पूर्ण अन्यथा अगर (ieee->state == IEEE80211_LINKED &&
			   ieee->iw_mode == IW_MODE_ADHOC) अणु
			ieee->set_chan(ieee->dev,
				       ieee->current_network.channel);
			ieee->link_change(ieee->dev);

			ieee80211_start_send_beacons(ieee);

			अगर (ieee->data_hard_resume)
				ieee->data_hard_resume(ieee->dev);
			netअगर_carrier_on(ieee->dev);
		पूर्ण

		CamRestoreAllEntry(dev);

		priv->ResetProgress = RESET_TYPE_NORESET;
		priv->reset_count++;

		priv->bForcedSilentReset = false;
		priv->bResetInProgress = false;

		/* For test --> क्रमce ग_लिखो UFWP. */
		ग_लिखो_nic_byte(dev, UFWP, 1);
		RT_TRACE(COMP_RESET,
			 "Reset finished!! ====>[%d]\n",
			 priv->reset_count);
	पूर्ण
पूर्ण

अटल व्योम rtl819x_update_rxcounts(काष्ठा r8192_priv *priv, u32 *TotalRxBcnNum,
			     u32 *TotalRxDataNum)
अणु
	u16			SlotIndex;
	u16			i;

	*TotalRxBcnNum = 0;
	*TotalRxDataNum = 0;

	SlotIndex = (priv->ieee80211->LinkDetectInfo.SlotIndex++) %
		    (priv->ieee80211->LinkDetectInfo.SlotNum);
	priv->ieee80211->LinkDetectInfo.RxBcnNum[SlotIndex] =
		priv->ieee80211->LinkDetectInfo.NumRecvBcnInPeriod;
	priv->ieee80211->LinkDetectInfo.RxDataNum[SlotIndex] =
		priv->ieee80211->LinkDetectInfo.NumRecvDataInPeriod;
	क्रम (i = 0; i < priv->ieee80211->LinkDetectInfo.SlotNum; i++) अणु
		*TotalRxBcnNum += priv->ieee80211->LinkDetectInfo.RxBcnNum[i];
		*TotalRxDataNum += priv->ieee80211->LinkDetectInfo.RxDataNum[i];
	पूर्ण
पूर्ण

अटल व्योम rtl819x_watchकरोg_wqcallback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा r8192_priv *priv = container_of(dwork,
					       काष्ठा r8192_priv, watch_करोg_wq);
	काष्ठा net_device *dev = priv->ieee80211->dev;
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	RESET_TYPE	ResetType = RESET_TYPE_NORESET;
	अटल u8	check_reset_cnt;
	bool bBusyTraffic = false;
	u32	TotalRxBcnNum = 0;
	u32	TotalRxDataNum = 0;

	अगर (!priv->up)
		वापस;
	hal_dm_watchकरोg(dev);

	/* to get busy traffic condition */
	अगर (ieee->state == IEEE80211_LINKED) अणु
		अगर (ieee->LinkDetectInfo.NumRxOkInPeriod > 666 ||
		    ieee->LinkDetectInfo.NumTxOkInPeriod > 666) अणु
			bBusyTraffic = true;
		पूर्ण
		ieee->LinkDetectInfo.NumRxOkInPeriod = 0;
		ieee->LinkDetectInfo.NumTxOkInPeriod = 0;
		ieee->LinkDetectInfo.bBusyTraffic = bBusyTraffic;
	पूर्ण
	/* क्रम AP roaming */
	अगर (priv->ieee80211->state == IEEE80211_LINKED &&
	    priv->ieee80211->iw_mode == IW_MODE_INFRA) अणु
		rtl819x_update_rxcounts(priv, &TotalRxBcnNum, &TotalRxDataNum);
		अगर ((TotalRxBcnNum + TotalRxDataNum) == 0) अणु
#अगर_घोषित TODO
			अगर (rfState == eRfOff)
				RT_TRACE(COMP_ERR, "========>%s()\n", __func__);
#पूर्ण_अगर
			netdev_dbg(dev,
				   "===>%s(): AP is power off, connect another one\n",
				   __func__);
			priv->ieee80211->state = IEEE80211_ASSOCIATING;
			notअगरy_wx_assoc_event(priv->ieee80211);
			RemovePeerTS(priv->ieee80211,
				     priv->ieee80211->current_network.bssid);
			priv->ieee80211->link_change(dev);
			queue_work(priv->ieee80211->wq,
				   &priv->ieee80211->associate_procedure_wq);
		पूर्ण
	पूर्ण
	priv->ieee80211->LinkDetectInfo.NumRecvBcnInPeriod = 0;
	priv->ieee80211->LinkDetectInfo.NumRecvDataInPeriod = 0;
	/* check अगर reset the driver */
	अगर (check_reset_cnt++ >= 3) अणु
		ResetType = rtl819x_अगरcheck_resetornot(dev);
		check_reset_cnt = 3;
	पूर्ण
	/* This is control by OID set in Pomelo */
	अगर ((priv->क्रमce_reset) || (priv->ResetProgress == RESET_TYPE_NORESET &&
	    (priv->bForcedSilentReset ||
	    (!priv->bDisableNormalResetCheck && ResetType == RESET_TYPE_SILENT)))) अणु
		RT_TRACE(COMP_RESET,
			 "%s():priv->force_reset is %d,priv->ResetProgress is %d, priv->bForcedSilentReset is %d,priv->bDisableNormalResetCheck is %d,ResetType is %d\n",
			 __func__, priv->क्रमce_reset, priv->ResetProgress,
			 priv->bForcedSilentReset,
			 priv->bDisableNormalResetCheck, ResetType);
		rtl819x_अगरsilentreset(dev);
	पूर्ण
	priv->क्रमce_reset = false;
	priv->bForcedSilentReset = false;
	priv->bResetInProgress = false;
	RT_TRACE(COMP_TRACE, " <==RtUsbCheckForHangWorkItemCallback()\n");
पूर्ण

अटल व्योम watch_करोg_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा r8192_priv *priv = from_समयr(priv, t, watch_करोg_समयr);

	schedule_delayed_work(&priv->watch_करोg_wq, 0);
	mod_समयr(&priv->watch_करोg_समयr,
		  jअगरfies + msecs_to_jअगरfies(IEEE80211_WATCH_DOG_TIME));
पूर्ण

अटल पूर्णांक _rtl8192_up(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक init_status = 0;

	priv->up = 1;
	priv->ieee80211->ieee_up = 1;
	RT_TRACE(COMP_INIT, "Bringing up iface");
	init_status = rtl8192_adapter_start(dev);
	अगर (!init_status) अणु
		RT_TRACE(COMP_ERR, "ERR!!! %s(): initialization failed!\n",
			 __func__);
		priv->up = priv->ieee80211->ieee_up = 0;
		वापस -EAGAIN;
	पूर्ण
	RT_TRACE(COMP_INIT, "start adapter finished\n");
	rtl8192_rx_enable(dev);
	अगर (priv->ieee80211->state != IEEE80211_LINKED)
		ieee80211_sofपंचांगac_start_protocol(priv->ieee80211);
	ieee80211_reset_queue(priv->ieee80211);
	watch_करोg_समयr_callback(&priv->watch_करोg_समयr);
	अगर (!netअगर_queue_stopped(dev))
		netअगर_start_queue(dev);
	अन्यथा
		netअगर_wake_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8192_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक ret;

	mutex_lock(&priv->wx_mutex);
	ret = rtl8192_up(dev);
	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

पूर्णांक rtl8192_up(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->up == 1)
		वापस -1;

	वापस _rtl8192_up(dev);
पूर्ण

अटल पूर्णांक rtl8192_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक ret;

	mutex_lock(&priv->wx_mutex);

	ret = rtl8192_करोwn(dev);

	mutex_unlock(&priv->wx_mutex);

	वापस ret;
पूर्ण

पूर्णांक rtl8192_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	पूर्णांक i;

	अगर (priv->up == 0)
		वापस -1;

	priv->up = 0;
	priv->ieee80211->ieee_up = 0;
	RT_TRACE(COMP_DOWN, "==========>%s()\n", __func__);
	/* FIXME */
	अगर (!netअगर_queue_stopped(dev))
		netअगर_stop_queue(dev);

	rtl8192_rtx_disable(dev);

	/* Tx related queue release */
	क्रम (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_purge(&priv->ieee80211->skb_रुकोQ[i]);
	क्रम (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_purge(&priv->ieee80211->skb_aggQ[i]);

	क्रम (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_purge(&priv->ieee80211->skb_drv_aggQ[i]);

	/* as cancel_delayed_work will del work->समयr, so अगर work is not
	 * defined as काष्ठा delayed_work, it will corrupt
	 */
	rtl8192_cancel_deferred_work(priv);
	deinit_hal_dm(dev);
	del_समयr_sync(&priv->watch_करोg_समयr);

	ieee80211_sofपंचांगac_stop_protocol(priv->ieee80211);
	स_रखो(&priv->ieee80211->current_network, 0,
	       दुरत्व(काष्ठा ieee80211_network, list));
	RT_TRACE(COMP_DOWN, "<==========%s()\n", __func__);

	वापस 0;
पूर्ण

व्योम rtl8192_commit(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->up == 0)
		वापस;
	priv->up = 0;

	rtl8192_cancel_deferred_work(priv);
	del_समयr_sync(&priv->watch_करोg_समयr);

	ieee80211_sofपंचांगac_stop_protocol(priv->ieee80211);

	rtl8192_rtx_disable(dev);
	_rtl8192_up(dev);
पूर्ण

अटल व्योम rtl8192_restart(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा r8192_priv *priv = container_of(work, काष्ठा r8192_priv,
					       reset_wq);
	काष्ठा net_device *dev = priv->ieee80211->dev;

	mutex_lock(&priv->wx_mutex);

	rtl8192_commit(dev);

	mutex_unlock(&priv->wx_mutex);
पूर्ण

अटल व्योम r8192_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	लघु promisc;

	/* FIXME FIXME */

	promisc = (dev->flags & IFF_PROMISC) ? 1 : 0;

	अगर (promisc != priv->promisc)

		priv->promisc = promisc;
पूर्ण

अटल पूर्णांक r8192_set_mac_adr(काष्ठा net_device *dev, व्योम *mac)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा sockaddr *addr = mac;

	mutex_lock(&priv->wx_mutex);

	ether_addr_copy(dev->dev_addr, addr->sa_data);

	schedule_work(&priv->reset_wq);
	mutex_unlock(&priv->wx_mutex);

	वापस 0;
पूर्ण

/* based on ipw2200 driver */
अटल पूर्णांक rtl8192_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा iwreq *wrq = (काष्ठा iwreq *)rq;
	पूर्णांक ret = -1;
	काष्ठा ieee80211_device *ieee = priv->ieee80211;
	u32 key[4];
	u8 broadcast_addr[6] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा iw_poपूर्णांक *p = &wrq->u.data;
	काष्ठा ieee_param *ipw = शून्य;

	mutex_lock(&priv->wx_mutex);

	अगर (p->length < माप(काष्ठा ieee_param) || !p->poपूर्णांकer) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ipw = memdup_user(p->poपूर्णांकer, p->length);
	अगर (IS_ERR(ipw)) अणु
		ret = PTR_ERR(ipw);
		जाओ out;
	पूर्ण

	चयन (cmd) अणु
	हाल RTL_IOCTL_WPA_SUPPLICANT:
		/* parse here क्रम HW security */
		अगर (ipw->cmd == IEEE_CMD_SET_ENCRYPTION) अणु
			अगर (ipw->u.crypt.set_tx) अणु
				अगर (म_भेद(ipw->u.crypt.alg, "CCMP") == 0) अणु
					ieee->pairwise_key_type = KEY_TYPE_CCMP;
				पूर्ण अन्यथा अगर (म_भेद(ipw->u.crypt.alg, "TKIP") == 0) अणु
					ieee->pairwise_key_type = KEY_TYPE_TKIP;
				पूर्ण अन्यथा अगर (म_भेद(ipw->u.crypt.alg, "WEP") == 0) अणु
					अगर (ipw->u.crypt.key_len == 13)
						ieee->pairwise_key_type = KEY_TYPE_WEP104;
					अन्यथा अगर (ipw->u.crypt.key_len == 5)
						ieee->pairwise_key_type = KEY_TYPE_WEP40;
				पूर्ण अन्यथा अणु
					ieee->pairwise_key_type = KEY_TYPE_NA;
				पूर्ण

				अगर (ieee->pairwise_key_type) अणु
					स_नकल((u8 *)key, ipw->u.crypt.key, 16);
					EnableHWSecurityConfig8192(dev);
					/* We fill both index entry and 4th
					 * entry क्रम pairwise key as in IPW
					 * पूर्णांकerface, adhoc will only get here,
					 * so we need index entry क्रम its
					 * शेष key serching!
					 */
					setKey(dev, 4, ipw->u.crypt.idx,
					       ieee->pairwise_key_type,
					       (u8 *)ieee->ap_mac_addr,
					       0, key);
					अगर (ieee->auth_mode != 2)
						setKey(dev, ipw->u.crypt.idx,
						       ipw->u.crypt.idx,
						       ieee->pairwise_key_type,
						       (u8 *)ieee->ap_mac_addr,
						       0, key);
				पूर्ण
			पूर्ण अन्यथा अणु
				स_नकल((u8 *)key, ipw->u.crypt.key, 16);
				अगर (म_भेद(ipw->u.crypt.alg, "CCMP") == 0) अणु
					ieee->group_key_type = KEY_TYPE_CCMP;
				पूर्ण अन्यथा अगर (म_भेद(ipw->u.crypt.alg, "TKIP") == 0) अणु
					ieee->group_key_type = KEY_TYPE_TKIP;
				पूर्ण अन्यथा अगर (म_भेद(ipw->u.crypt.alg, "WEP") == 0) अणु
					अगर (ipw->u.crypt.key_len == 13)
						ieee->group_key_type = KEY_TYPE_WEP104;
					अन्यथा अगर (ipw->u.crypt.key_len == 5)
						ieee->group_key_type = KEY_TYPE_WEP40;
				पूर्ण अन्यथा अणु
					ieee->group_key_type = KEY_TYPE_NA;
				पूर्ण

				अगर (ieee->group_key_type) अणु
					setKey(dev, ipw->u.crypt.idx,
					       /* KeyIndex */
					       ipw->u.crypt.idx,
					       /* KeyType */
					       ieee->group_key_type,
					       /* MacAddr */
					       broadcast_addr,
					       /* DefaultKey */
					       0,
					       /* KeyContent */
					       key);
				पूर्ण
			पूर्ण
		पूर्ण
		ret = ieee80211_wpa_supplicant_ioctl(priv->ieee80211,
						     &wrq->u.data);
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	kमुक्त(ipw);
	ipw = शून्य;
out:
	mutex_unlock(&priv->wx_mutex);
	वापस ret;
पूर्ण

अटल u8 HwRateToMRate90(bool bIsHT, u8 rate)
अणु
	u8  ret_rate = 0xff;

	अगर (!bIsHT) अणु
		चयन (rate) अणु
		हाल DESC90_RATE1M:
			ret_rate = MGN_1M;
			अवरोध;
		हाल DESC90_RATE2M:
			ret_rate = MGN_2M;
			अवरोध;
		हाल DESC90_RATE5_5M:
			ret_rate = MGN_5_5M;
			अवरोध;
		हाल DESC90_RATE11M:
			ret_rate = MGN_11M;
			अवरोध;
		हाल DESC90_RATE6M:
			ret_rate = MGN_6M;
			अवरोध;
		हाल DESC90_RATE9M:
			ret_rate = MGN_9M;
			अवरोध;
		हाल DESC90_RATE12M:
			ret_rate = MGN_12M;
			अवरोध;
		हाल DESC90_RATE18M:
			ret_rate = MGN_18M;
			अवरोध;
		हाल DESC90_RATE24M:
			ret_rate = MGN_24M;
			अवरोध;
		हाल DESC90_RATE36M:
			ret_rate = MGN_36M;
			अवरोध;
		हाल DESC90_RATE48M:
			ret_rate = MGN_48M;
			अवरोध;
		हाल DESC90_RATE54M:
			ret_rate = MGN_54M;
			अवरोध;

		शेष:
			ret_rate = 0xff;
			RT_TRACE(COMP_RECV,
				 "%s: Non supported Rate [%x], bIsHT = %d!!!\n",
				 __func__, rate, bIsHT);
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अणु
		चयन (rate) अणु
		हाल DESC90_RATEMCS0:
			ret_rate = MGN_MCS0;
			अवरोध;
		हाल DESC90_RATEMCS1:
			ret_rate = MGN_MCS1;
			अवरोध;
		हाल DESC90_RATEMCS2:
			ret_rate = MGN_MCS2;
			अवरोध;
		हाल DESC90_RATEMCS3:
			ret_rate = MGN_MCS3;
			अवरोध;
		हाल DESC90_RATEMCS4:
			ret_rate = MGN_MCS4;
			अवरोध;
		हाल DESC90_RATEMCS5:
			ret_rate = MGN_MCS5;
			अवरोध;
		हाल DESC90_RATEMCS6:
			ret_rate = MGN_MCS6;
			अवरोध;
		हाल DESC90_RATEMCS7:
			ret_rate = MGN_MCS7;
			अवरोध;
		हाल DESC90_RATEMCS8:
			ret_rate = MGN_MCS8;
			अवरोध;
		हाल DESC90_RATEMCS9:
			ret_rate = MGN_MCS9;
			अवरोध;
		हाल DESC90_RATEMCS10:
			ret_rate = MGN_MCS10;
			अवरोध;
		हाल DESC90_RATEMCS11:
			ret_rate = MGN_MCS11;
			अवरोध;
		हाल DESC90_RATEMCS12:
			ret_rate = MGN_MCS12;
			अवरोध;
		हाल DESC90_RATEMCS13:
			ret_rate = MGN_MCS13;
			अवरोध;
		हाल DESC90_RATEMCS14:
			ret_rate = MGN_MCS14;
			अवरोध;
		हाल DESC90_RATEMCS15:
			ret_rate = MGN_MCS15;
			अवरोध;
		हाल DESC90_RATEMCS32:
			ret_rate = 0x80 | 0x20;
			अवरोध;

		शेष:
			ret_rate = 0xff;
			RT_TRACE(COMP_RECV,
				 "%s: Non supported Rate [%x], bIsHT = %d!!!\n",
				 __func__, rate, bIsHT);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret_rate;
पूर्ण

/**
 * Function:     UpdateRxPktTimeStamp
 * Overview:     Record the TSF समय stamp when receiving a packet
 *
 * Input:
 *       PADAPTER        Adapter
 *       PRT_RFD         pRfd,
 *
 * Output:
 *       PRT_RFD         pRfd
 *                               (pRfd->Status.TimeStampHigh is updated)
 *                               (pRfd->Status.TimeStampLow is updated)
 * Return:
 *               None
 */
अटल व्योम UpdateRxPktTimeStamp8190(काष्ठा net_device *dev,
				     काष्ठा ieee80211_rx_stats *stats)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);

	अगर (stats->bIsAMPDU && !stats->bFirstMPDU) अणु
		stats->mac_समय[0] = priv->LastRxDescTSFLow;
		stats->mac_समय[1] = priv->LastRxDescTSFHigh;
	पूर्ण अन्यथा अणु
		priv->LastRxDescTSFLow = stats->mac_समय[0];
		priv->LastRxDescTSFHigh = stats->mac_समय[1];
	पूर्ण
पूर्ण

/* 0-100 index. */
अटल दीर्घ rtl819x_translate_todbm(u8 संकेत_strength_index)
अणु
	दीर्घ	संकेत_घातer; /* in dBm. */

	/* Translate to dBm (x=0.5y-95). */
	संकेत_घातer = (दीर्घ)((संकेत_strength_index + 1) >> 1);
	संकेत_घातer -= 95;

	वापस संकेत_घातer;
पूर्ण

/* We can not declare RSSI/EVM total value of sliding winकरोw to
 * be a local अटल. Otherwise, it may increase when we वापस from S3/S4. The
 * value will be kept in memory or disk. Declare the value in the adaptor
 * and it will be reinitialized when वापसed from S3/S4.
 */
अटल व्योम rtl8192_process_phyinfo(काष्ठा r8192_priv *priv, u8 *buffer,
				    काष्ठा ieee80211_rx_stats *pprevious_stats,
				    काष्ठा ieee80211_rx_stats *pcurrent_stats)
अणु
	bool bcheck = false;
	u8	rfpath;
	u32	nspatial_stream, पंचांगp_val;
	अटल u32 slide_rssi_index, slide_rssi_statistics;
	अटल u32 slide_evm_index, slide_evm_statistics;
	अटल u32 last_rssi, last_evm;

	अटल u32 slide_beacon_adc_pwdb_index;
	अटल u32 slide_beacon_adc_pwdb_statistics;
	अटल u32 last_beacon_adc_pwdb;

	काष्ठा rtl_80211_hdr_3addr *hdr;
	u16 sc;
	अचिन्हित पूर्णांक seq;

	hdr = (काष्ठा rtl_80211_hdr_3addr *)buffer;
	sc = le16_to_cpu(hdr->seq_ctl);
	seq = WLAN_GET_SEQ_SEQ(sc);
	/* to record the sequence number */
	pcurrent_stats->Seq_Num = seq;

	/* Check whether we should take the previous packet पूर्णांकo accounting */
	अगर (!pprevious_stats->bIsAMPDU) अणु
		/* अगर previous packet is not aggregated packet */
		bcheck = true;
	पूर्ण

	अगर (slide_rssi_statistics++ >= PHY_RSSI_SLID_WIN_MAX) अणु
		slide_rssi_statistics = PHY_RSSI_SLID_WIN_MAX;
		last_rssi = priv->stats.slide_संकेत_strength[slide_rssi_index];
		priv->stats.slide_rssi_total -= last_rssi;
	पूर्ण
	priv->stats.slide_rssi_total += pprevious_stats->SignalStrength;

	priv->stats.slide_संकेत_strength[slide_rssi_index++] =
		pprevious_stats->SignalStrength;
	अगर (slide_rssi_index >= PHY_RSSI_SLID_WIN_MAX)
		slide_rssi_index = 0;

	/* <1> Showed on UI क्रम user, in dbm */
	पंचांगp_val = priv->stats.slide_rssi_total / slide_rssi_statistics;
	priv->stats.संकेत_strength = rtl819x_translate_todbm((u8)पंचांगp_val);
	pcurrent_stats->rssi = priv->stats.संकेत_strength;

	/* If the previous packet करोes not match the criteria, neglect it */
	अगर (!pprevious_stats->bPacketMatchBSSID) अणु
		अगर (!pprevious_stats->bToSelfBA)
			वापस;
	पूर्ण

	अगर (!bcheck)
		वापस;

	/* only rtl8190 supported
	 * rtl8190_process_cck_rxpathsel(priv,pprevious_stats);
	 */

	/* Check RSSI */
	priv->stats.num_process_phyinfo++;

	/* record the general संकेत strength to the sliding winकरोw. */

	/* <2> Showed on UI क्रम engineering
	 * hardware करोes not provide rssi inक्रमmation क्रम each rf path in CCK
	 */
	अगर (!pprevious_stats->bIsCCK &&
	    (pprevious_stats->bPacketToSelf || pprevious_stats->bToSelfBA)) अणु
		क्रम (rfpath = RF90_PATH_A; rfpath < priv->NumTotalRFPath; rfpath++) अणु
			अगर (!rtl8192_phy_CheckIsLegalRFPath(priv->ieee80211->dev,
							    rfpath))
				जारी;
			अगर (priv->stats.rx_rssi_percentage[rfpath] == 0)
				priv->stats.rx_rssi_percentage[rfpath] =
					pprevious_stats->RxMIMOSignalStrength[rfpath];
			अगर (pprevious_stats->RxMIMOSignalStrength[rfpath]  > priv->stats.rx_rssi_percentage[rfpath]) अणु
				priv->stats.rx_rssi_percentage[rfpath] =
					((priv->stats.rx_rssi_percentage[rfpath] * (RX_SMOOTH_FACTOR - 1)) +
					 (pprevious_stats->RxMIMOSignalStrength[rfpath])) / (RX_SMOOTH_FACTOR);
				priv->stats.rx_rssi_percentage[rfpath] = priv->stats.rx_rssi_percentage[rfpath]  + 1;
			पूर्ण अन्यथा अणु
				priv->stats.rx_rssi_percentage[rfpath] =
					((priv->stats.rx_rssi_percentage[rfpath] * (RX_SMOOTH_FACTOR - 1)) +
					 (pprevious_stats->RxMIMOSignalStrength[rfpath])) / (RX_SMOOTH_FACTOR);
			पूर्ण
			RT_TRACE(COMP_DBG,
				 "priv->stats.rx_rssi_percentage[rfPath]  = %d\n",
				 priv->stats.rx_rssi_percentage[rfpath]);
		पूर्ण
	पूर्ण

	/* Check PWDB. */
	RT_TRACE(COMP_RXDESC, "Smooth %s PWDB = %d\n",
		 pprevious_stats->bIsCCK ? "CCK" : "OFDM",
		 pprevious_stats->RxPWDBAll);

	अगर (pprevious_stats->bPacketBeacon) अणु
		/* record the beacon pwdb to the sliding winकरोw. */
		अगर (slide_beacon_adc_pwdb_statistics++ >= PHY_Beacon_RSSI_SLID_WIN_MAX) अणु
			slide_beacon_adc_pwdb_statistics = PHY_Beacon_RSSI_SLID_WIN_MAX;
			last_beacon_adc_pwdb = priv->stats.Slide_Beacon_pwdb[slide_beacon_adc_pwdb_index];
			priv->stats.Slide_Beacon_Total -= last_beacon_adc_pwdb;
		पूर्ण
		priv->stats.Slide_Beacon_Total += pprevious_stats->RxPWDBAll;
		priv->stats.Slide_Beacon_pwdb[slide_beacon_adc_pwdb_index] = pprevious_stats->RxPWDBAll;
		slide_beacon_adc_pwdb_index++;
		अगर (slide_beacon_adc_pwdb_index >= PHY_Beacon_RSSI_SLID_WIN_MAX)
			slide_beacon_adc_pwdb_index = 0;
		pprevious_stats->RxPWDBAll = priv->stats.Slide_Beacon_Total / slide_beacon_adc_pwdb_statistics;
		अगर (pprevious_stats->RxPWDBAll >= 3)
			pprevious_stats->RxPWDBAll -= 3;
	पूर्ण

	RT_TRACE(COMP_RXDESC, "Smooth %s PWDB = %d\n",
		 pprevious_stats->bIsCCK ? "CCK" : "OFDM",
		 pprevious_stats->RxPWDBAll);

	अगर (pprevious_stats->bPacketToSelf ||
	    pprevious_stats->bPacketBeacon ||
	    pprevious_stats->bToSelfBA) अणु
		अगर (priv->undecorated_smoothed_pwdb < 0)
			/* initialize */
			priv->undecorated_smoothed_pwdb =
				pprevious_stats->RxPWDBAll;
		अगर (pprevious_stats->RxPWDBAll > (u32)priv->undecorated_smoothed_pwdb) अणु
			priv->undecorated_smoothed_pwdb =
				(((priv->undecorated_smoothed_pwdb) * (RX_SMOOTH_FACTOR - 1)) +
				 (pprevious_stats->RxPWDBAll)) / (RX_SMOOTH_FACTOR);
			priv->undecorated_smoothed_pwdb = priv->undecorated_smoothed_pwdb + 1;
		पूर्ण अन्यथा अणु
			priv->undecorated_smoothed_pwdb =
				(((priv->undecorated_smoothed_pwdb) * (RX_SMOOTH_FACTOR - 1)) +
				 (pprevious_stats->RxPWDBAll)) / (RX_SMOOTH_FACTOR);
		पूर्ण
	पूर्ण

	/* Check EVM */
	/* record the general EVM to the sliding winकरोw. */
	अगर (pprevious_stats->SignalQuality) अणु
		अगर (pprevious_stats->bPacketToSelf ||
		    pprevious_stats->bPacketBeacon ||
		    pprevious_stats->bToSelfBA) अणु
			अगर (slide_evm_statistics++ >= PHY_RSSI_SLID_WIN_MAX) अणु
				slide_evm_statistics = PHY_RSSI_SLID_WIN_MAX;
				last_evm = priv->stats.slide_evm[slide_evm_index];
				priv->stats.slide_evm_total -= last_evm;
			पूर्ण

			priv->stats.slide_evm_total +=
				pprevious_stats->SignalQuality;

			priv->stats.slide_evm[slide_evm_index++] =
				pprevious_stats->SignalQuality;
			अगर (slide_evm_index >= PHY_RSSI_SLID_WIN_MAX)
				slide_evm_index = 0;

			/* <1> Showed on UI क्रम user, in percentage. */
			पंचांगp_val = priv->stats.slide_evm_total /
				  slide_evm_statistics;
			priv->stats.संकेत_quality = पंचांगp_val;
			/* Showed on UI क्रम user in Winकरोws Vista,
			 * क्रम Link quality.
			 */
			priv->stats.last_संकेत_strength_inpercent = पंचांगp_val;
		पूर्ण

		/* <2> Showed on UI क्रम engineering */
		अगर (pprevious_stats->bPacketToSelf ||
		    pprevious_stats->bPacketBeacon ||
		    pprevious_stats->bToSelfBA) अणु
			क्रम (nspatial_stream = 0; nspatial_stream < 2; nspatial_stream++) अणु /* 2 spatial stream */
				अगर (pprevious_stats->RxMIMOSignalQuality[nspatial_stream] != -1) अणु
					अगर (priv->stats.rx_evm_percentage[nspatial_stream] == 0) /* initialize */
						priv->stats.rx_evm_percentage[nspatial_stream] = pprevious_stats->RxMIMOSignalQuality[nspatial_stream];
					priv->stats.rx_evm_percentage[nspatial_stream] =
						((priv->stats.rx_evm_percentage[nspatial_stream] * (RX_SMOOTH_FACTOR - 1)) +
						 (pprevious_stats->RxMIMOSignalQuality[nspatial_stream] * 1)) / (RX_SMOOTH_FACTOR);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	rtl819x_query_rxpwrpercentage()
 *
 * Overview:
 *
 * Input:		अक्षर		antघातer
 *
 * Output:		NONE
 *
 * Return:		0-100 percentage
 *---------------------------------------------------------------------------
 */
अटल u8 rtl819x_query_rxpwrpercentage(s8 antघातer)
अणु
	अगर ((antघातer <= -100) || (antघातer >= 20))
		वापस	0;
	अन्यथा अगर (antघातer >= 0)
		वापस	100;
	अन्यथा
		वापस	100 + antघातer;

पूर्ण	/* QueryRxPwrPercentage */

अटल u8 rtl819x_evm_dbtopercentage(s8 value)
अणु
	s8 ret_val = clamp(-value, 0, 33) * 3;

	अगर (ret_val == 99)
		ret_val = 100;

	वापस ret_val;
पूर्ण

/* We want good-looking क्रम संकेत strength/quality */
अटल दीर्घ rtl819x_संकेत_scale_mapping(दीर्घ currsig)
अणु
	दीर्घ retsig;

	/* Step 1. Scale mapping. */
	अगर (currsig >= 61 && currsig <= 100)
		retsig = 90 + ((currsig - 60) / 4);
	अन्यथा अगर (currsig >= 41 && currsig <= 60)
		retsig = 78 + ((currsig - 40) / 2);
	अन्यथा अगर (currsig >= 31 && currsig <= 40)
		retsig = 66 + (currsig - 30);
	अन्यथा अगर (currsig >= 21 && currsig <= 30)
		retsig = 54 + (currsig - 20);
	अन्यथा अगर (currsig >= 5 && currsig <= 20)
		retsig = 42 + (((currsig - 5) * 2) / 3);
	अन्यथा अगर (currsig == 4)
		retsig = 36;
	अन्यथा अगर (currsig == 3)
		retsig = 27;
	अन्यथा अगर (currsig == 2)
		retsig = 18;
	अन्यथा अगर (currsig == 1)
		retsig = 9;
	अन्यथा
		retsig = currsig;

	वापस retsig;
पूर्ण

अटल अंतरभूत bool rx_hal_is_cck_rate(काष्ठा rx_drvinfo_819x_usb *pdrvinfo)
अणु
	अगर (pdrvinfo->RxHT)
		वापस false;

	चयन (pdrvinfo->RxRate) अणु
	हाल DESC90_RATE1M:
	हाल DESC90_RATE2M:
	हाल DESC90_RATE5_5M:
	हाल DESC90_RATE11M:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम rtl8192_query_rxphystatus(काष्ठा r8192_priv *priv,
				      काष्ठा ieee80211_rx_stats *pstats,
				      काष्ठा rx_drvinfo_819x_usb  *pdrvinfo,
				      काष्ठा ieee80211_rx_stats *precord_stats,
				      bool bpacket_match_bssid,
				      bool bpacket_toself,
				      bool bPacketBeacon,
				      bool bToSelfBA)
अणु
	phy_sts_ofdm_819xusb_t *pofdm_buf;
	phy_sts_cck_819xusb_t	*pcck_buf;
	काष्ठा phy_ofdm_rx_status_rxsc_sgien_exपूर्णांकfflag *prxsc;
	u8	*prxpkt;
	u8	i, max_spatial_stream, पंचांगp_rxsnr, पंचांगp_rxevm, rxsc_sgien_exflg;
	s8	rx_pwr[4], rx_pwr_all = 0;
	s8	rx_snrX, rx_evmX;
	u8	evm, pwdb_all;
	u32	RSSI, total_rssi = 0;
	u8	is_cck_rate = 0;
	u8	rf_rx_num = 0;
	u8	sq;

	priv->stats.numqry_phystatus++;

	is_cck_rate = rx_hal_is_cck_rate(pdrvinfo);

	/* Record it क्रम next packet processing */
	स_रखो(precord_stats, 0, माप(काष्ठा ieee80211_rx_stats));
	pstats->bPacketMatchBSSID =
		precord_stats->bPacketMatchBSSID = bpacket_match_bssid;
	pstats->bPacketToSelf = precord_stats->bPacketToSelf = bpacket_toself;
	pstats->bIsCCK = precord_stats->bIsCCK = is_cck_rate;
	pstats->bPacketBeacon = precord_stats->bPacketBeacon = bPacketBeacon;
	pstats->bToSelfBA = precord_stats->bToSelfBA = bToSelfBA;

	prxpkt = (u8 *)pdrvinfo;

	/* Move poपूर्णांकer to the 16th bytes. Phy status start address. */
	prxpkt += माप(काष्ठा rx_drvinfo_819x_usb);

	/* Initial the cck and ofdm buffer poपूर्णांकer */
	pcck_buf = (phy_sts_cck_819xusb_t *)prxpkt;
	pofdm_buf = (phy_sts_ofdm_819xusb_t *)prxpkt;

	pstats->RxMIMOSignalQuality[0] = -1;
	pstats->RxMIMOSignalQuality[1] = -1;
	precord_stats->RxMIMOSignalQuality[0] = -1;
	precord_stats->RxMIMOSignalQuality[1] = -1;

	अगर (is_cck_rate) अणु
		/* (1)Hardware करोes not provide RSSI क्रम CCK */

		/* (2)PWDB, Average PWDB calculated by hardware
		 * (क्रम rate adaptive)
		 */
		u8 report;

		priv->stats.numqry_phystatusCCK++;

		अगर (!priv->bCckHighPower) अणु
			report = pcck_buf->cck_agc_rpt & 0xc0;
			report >>= 6;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -35 - (pcck_buf->cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -23 - (pcck_buf->cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -11 - (pcck_buf->cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 6 - (pcck_buf->cck_agc_rpt & 0x3e);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			report = pcck_buf->cck_agc_rpt & 0x60;
			report >>= 5;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -35 - ((pcck_buf->cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -23 - ((pcck_buf->cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -11 - ((pcck_buf->cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 6 - ((pcck_buf->cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			पूर्ण
		पूर्ण

		pwdb_all = rtl819x_query_rxpwrpercentage(rx_pwr_all);
		pstats->RxPWDBAll = precord_stats->RxPWDBAll = pwdb_all;
		pstats->RecvSignalPower = pwdb_all;

		/* (3) Get Signal Quality (EVM) */

		अगर (pstats->RxPWDBAll > 40) अणु
			sq = 100;
		पूर्ण अन्यथा अणु
			sq = pcck_buf->sq_rpt;

			अगर (pcck_buf->sq_rpt > 64)
				sq = 0;
			अन्यथा अगर (pcck_buf->sq_rpt < 20)
				sq = 100;
			अन्यथा
				sq = ((64 - sq) * 100) / 44;
		पूर्ण
		pstats->SignalQuality = precord_stats->SignalQuality = sq;
		pstats->RxMIMOSignalQuality[0] =
			precord_stats->RxMIMOSignalQuality[0] = sq;
		pstats->RxMIMOSignalQuality[1] =
			precord_stats->RxMIMOSignalQuality[1] = -1;

	पूर्ण अन्यथा अणु
		priv->stats.numqry_phystatusHT++;

		/* (1)Get RSSI क्रम HT rate */
		क्रम (i = RF90_PATH_A; i < priv->NumTotalRFPath; i++) अणु
			/* We will judge RF RX path now. */
			अगर (priv->brfpath_rxenable[i])
				rf_rx_num++;
			अन्यथा
				जारी;

			अगर (!rtl8192_phy_CheckIsLegalRFPath(priv->ieee80211->dev, i))
				जारी;

			rx_pwr[i] =
				((pofdm_buf->trsw_gain_X[i] & 0x3F) * 2) - 106;

			/* Get Rx snr value in DB */
			पंचांगp_rxsnr =	pofdm_buf->rxsnr_X[i];
			rx_snrX = (s8)(पंचांगp_rxsnr);
			rx_snrX /= 2;
			priv->stats.rxSNRdB[i] = (दीर्घ)rx_snrX;

			/* Translate DBM to percentage. */
			RSSI = rtl819x_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += RSSI;

			/* Record Signal Strength क्रम next packet */
			pstats->RxMIMOSignalStrength[i] = (u8)RSSI;
			precord_stats->RxMIMOSignalStrength[i] = (u8)RSSI;
		पूर्ण

		/* (2)PWDB, Average PWDB calculated by hardware
		 * (क्रम rate adaptive)
		 */
		rx_pwr_all = (((pofdm_buf->pwdb_all) >> 1) & 0x7f) - 106;
		pwdb_all = rtl819x_query_rxpwrpercentage(rx_pwr_all);

		pstats->RxPWDBAll = precord_stats->RxPWDBAll = pwdb_all;
		pstats->RxPower = precord_stats->RxPower =  rx_pwr_all;

		/* (3)EVM of HT rate */
		अगर (pdrvinfo->RxHT && pdrvinfo->RxRate >= DESC90_RATEMCS8 &&
		    pdrvinfo->RxRate <= DESC90_RATEMCS15)
			/* both spatial stream make sense */
			max_spatial_stream = 2;
		अन्यथा
			/* only spatial stream 1 makes sense */
			max_spatial_stream = 1;

		क्रम (i = 0; i < max_spatial_stream; i++) अणु
			पंचांगp_rxevm =	pofdm_buf->rxevm_X[i];
			rx_evmX = (s8)(पंचांगp_rxevm);

			/* Do not use shअगरt operation like "rx_evmX >>= 1"
			 * because the compiler of मुक्त build environment will
			 * set the most signअगरicant bit to "zero" when करोing
			 * shअगरting operation which may change a negative value
			 * to positive one, then the dbm value (which is
			 * supposed to be negative) is not correct anymore.
			 */
			rx_evmX /= 2;	/* dbm */

			evm = rtl819x_evm_dbtopercentage(rx_evmX);
			अगर (i == 0)
				/* Fill value in RFD, Get the first spatial
				 * stream only
				 */
				pstats->SignalQuality =
					precord_stats->SignalQuality =
					evm & 0xff;
			pstats->RxMIMOSignalQuality[i] =
				precord_stats->RxMIMOSignalQuality[i] =
				evm & 0xff;
		पूर्ण

		/* record rx statistics क्रम debug */
		rxsc_sgien_exflg = pofdm_buf->rxsc_sgien_exflg;
		prxsc =	(काष्ठा phy_ofdm_rx_status_rxsc_sgien_exपूर्णांकfflag *)
			&rxsc_sgien_exflg;
		अगर (pdrvinfo->BW)	/* 40M channel */
			priv->stats.received_bwtype[1 + prxsc->rxsc]++;
		अन्यथा			/* 20M channel */
			priv->stats.received_bwtype[0]++;
	पूर्ण

	/* UI BSS List संकेत strength(in percentage), make it good looking,
	 * from 0~100. It is asचिन्हित to the BSS List in
	 * GetValueFromBeaconOrProbeRsp().
	 */
	अगर (is_cck_rate) अणु
		pstats->SignalStrength =
			precord_stats->SignalStrength =
			(u8)(rtl819x_संकेत_scale_mapping((दीर्घ)pwdb_all));
	पूर्ण अन्यथा अणु
		/* We can judge RX path number now. */
		अगर (rf_rx_num != 0) अणु
			pstats->SignalStrength =
				precord_stats->SignalStrength =
				(u8)(rtl819x_संकेत_scale_mapping((दीर्घ)(total_rssi /= rf_rx_num)));
		पूर्ण
	पूर्ण
पूर्ण	/* QueryRxPhyStatus8190Pci */

अटल व्योम rtl8192_record_rxdesc_क्रमlateruse(काष्ठा ieee80211_rx_stats *psrc_stats,
					      काष्ठा ieee80211_rx_stats *ptarget_stats)
अणु
	ptarget_stats->bIsAMPDU = psrc_stats->bIsAMPDU;
	ptarget_stats->bFirstMPDU = psrc_stats->bFirstMPDU;
	ptarget_stats->Seq_Num = psrc_stats->Seq_Num;
पूर्ण

अटल व्योम TranslateRxSignalStuff819xUsb(काष्ठा sk_buff *skb,
					  काष्ठा ieee80211_rx_stats *pstats,
					  काष्ठा rx_drvinfo_819x_usb  *pdrvinfo)
अणु
	/* TODO: We must only check packet क्रम current MAC address.
	 * Not finish
	 */
	काष्ठा rtl8192_rx_info *info = (काष्ठा rtl8192_rx_info *)skb->cb;
	काष्ठा net_device *dev = info->dev;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	bool bpacket_match_bssid, bpacket_toself;
	bool bPacketBeacon = false, bToSelfBA = false;
	अटल काष्ठा ieee80211_rx_stats  previous_stats;
	काष्ठा rtl_80211_hdr_3addr *hdr;
	u16 fc, type;

	/* Get Signal Quality क्रम only RX data queue (but not command queue) */

	u8 *पंचांगp_buf;
	u8  *praddr;

	/* Get MAC frame start address. */
	पंचांगp_buf = (u8 *)skb->data;

	hdr = (काष्ठा rtl_80211_hdr_3addr *)पंचांगp_buf;
	fc = le16_to_cpu(hdr->frame_ctl);
	type = WLAN_FC_GET_TYPE(fc);
	praddr = hdr->addr1;

	/* Check अगर the received packet is acceptable. */
	bpacket_match_bssid = (type != IEEE80211_FTYPE_CTL) &&
			       (ether_addr_equal(priv->ieee80211->current_network.bssid,  (fc & IEEE80211_FCTL_TODS) ? hdr->addr1 : (fc & IEEE80211_FCTL_FROMDS) ? hdr->addr2 : hdr->addr3))
			       && (!pstats->bHwError) && (!pstats->bCRC) && (!pstats->bICV);
	bpacket_toself =  bpacket_match_bssid &
			  (ether_addr_equal(praddr, priv->ieee80211->dev->dev_addr));

	अगर (WLAN_FC_GET_FRAMETYPE(fc) == IEEE80211_STYPE_BEACON)
		bPacketBeacon = true;
	अगर (WLAN_FC_GET_FRAMETYPE(fc) == IEEE80211_STYPE_BLOCKACK) अणु
		अगर ((ether_addr_equal(praddr, dev->dev_addr)))
			bToSelfBA = true;
	पूर्ण

	अगर (bpacket_match_bssid)
		priv->stats.numpacket_matchbssid++;
	अगर (bpacket_toself)
		priv->stats.numpacket_toself++;
	/* Process PHY inक्रमmation क्रम previous packet (RSSI/PWDB/EVM)
	 * Because phy inक्रमmation is contained in the last packet of AMPDU
	 * only, so driver should process phy inक्रमmation of previous packet
	 */
	rtl8192_process_phyinfo(priv, पंचांगp_buf, &previous_stats, pstats);
	rtl8192_query_rxphystatus(priv, pstats, pdrvinfo, &previous_stats,
				  bpacket_match_bssid, bpacket_toself,
				  bPacketBeacon, bToSelfBA);
	rtl8192_record_rxdesc_क्रमlateruse(pstats, &previous_stats);
पूर्ण

/**
 * Function:	UpdateReceivedRateHistogramStatistics
 * Overview:	Record the received data rate
 *
 * Input:
 *	काष्ठा net_device *dev
 *	काष्ठा ieee80211_rx_stats *stats
 *
 * Output:
 *
 *			(priv->stats.ReceivedRateHistogram[] is updated)
 * Return:
 *		None
 */
अटल व्योम
UpdateReceivedRateHistogramStatistics8190(काष्ठा net_device *dev,
					  काष्ठा ieee80211_rx_stats *stats)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	/* 0: Total, 1:OK, 2:CRC, 3:ICV */
	u32 rcvType = 1;
	u32 rateIndex;
	/* 1: लघु preamble/GI, 0: दीर्घ preamble/GI */
	u32 preamble_guardपूर्णांकerval;

	अगर (stats->bCRC)
		rcvType = 2;
	अन्यथा अगर (stats->bICV)
		rcvType = 3;

	अगर (stats->bShortPreamble)
		preamble_guardपूर्णांकerval = 1; /* लघु */
	अन्यथा
		preamble_guardपूर्णांकerval = 0; /* दीर्घ */

	चयन (stats->rate) अणु
	/* CCK rate */
	हाल MGN_1M:
		rateIndex = 0;
		अवरोध;
	हाल MGN_2M:
		rateIndex = 1;
		अवरोध;
	हाल MGN_5_5M:
		rateIndex = 2;
		अवरोध;
	हाल MGN_11M:
		rateIndex = 3;
		अवरोध;
	/* Legacy OFDM rate */
	हाल MGN_6M:
		rateIndex = 4;
		अवरोध;
	हाल MGN_9M:
		rateIndex = 5;
		अवरोध;
	हाल MGN_12M:
		rateIndex = 6;
		अवरोध;
	हाल MGN_18M:
		rateIndex = 7;
		अवरोध;
	हाल MGN_24M:
		rateIndex = 8;
		अवरोध;
	हाल MGN_36M:
		rateIndex = 9;
		अवरोध;
	हाल MGN_48M:
		rateIndex = 10;
		अवरोध;
	हाल MGN_54M:
		rateIndex = 11;
		अवरोध;
	/* 11n High throughput rate */
	हाल MGN_MCS0:
		rateIndex = 12;
		अवरोध;
	हाल MGN_MCS1:
		rateIndex = 13;
		अवरोध;
	हाल MGN_MCS2:
		rateIndex = 14;
		अवरोध;
	हाल MGN_MCS3:
		rateIndex = 15;
		अवरोध;
	हाल MGN_MCS4:
		rateIndex = 16;
		अवरोध;
	हाल MGN_MCS5:
		rateIndex = 17;
		अवरोध;
	हाल MGN_MCS6:
		rateIndex = 18;
		अवरोध;
	हाल MGN_MCS7:
		rateIndex = 19;
		अवरोध;
	हाल MGN_MCS8:
		rateIndex = 20;
		अवरोध;
	हाल MGN_MCS9:
		rateIndex = 21;
		अवरोध;
	हाल MGN_MCS10:
		rateIndex = 22;
		अवरोध;
	हाल MGN_MCS11:
		rateIndex = 23;
		अवरोध;
	हाल MGN_MCS12:
		rateIndex = 24;
		अवरोध;
	हाल MGN_MCS13:
		rateIndex = 25;
		अवरोध;
	हाल MGN_MCS14:
		rateIndex = 26;
		अवरोध;
	हाल MGN_MCS15:
		rateIndex = 27;
		अवरोध;
	शेष:
		rateIndex = 28;
		अवरोध;
	पूर्ण
	priv->stats.received_preamble_GI[preamble_guardपूर्णांकerval][rateIndex]++;
	priv->stats.received_rate_histogram[0][rateIndex]++; /* total */
	priv->stats.received_rate_histogram[rcvType][rateIndex]++;
पूर्ण

अटल व्योम query_rxdesc_status(काष्ठा sk_buff *skb,
				काष्ठा ieee80211_rx_stats *stats,
				bool bIsRxAggrSubframe)
अणु
	काष्ठा rtl8192_rx_info *info = (काष्ठा rtl8192_rx_info *)skb->cb;
	काष्ठा net_device *dev = info->dev;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा rx_drvinfo_819x_usb  *driver_info = शून्य;

	/* Get Rx Descriptor Inक्रमmation */
	काष्ठा rx_desc_819x_usb *desc = (काष्ठा rx_desc_819x_usb *)skb->data;

	stats->Length = desc->Length;
	stats->RxDrvInfoSize = desc->RxDrvInfoSize;
	stats->RxBufShअगरt = 0;
	stats->bICV = desc->ICV;
	stats->bCRC = desc->CRC32;
	stats->bHwError = stats->bCRC | stats->bICV;
	/* RTL8190 set this bit to indicate that Hw करोes not decrypt packet */
	stats->Decrypted = !desc->SWDec;

	अगर ((priv->ieee80211->pHTInfo->bCurrentHTSupport) &&
	    (priv->ieee80211->pairwise_key_type == KEY_TYPE_CCMP))
		stats->bHwError = false;
	अन्यथा
		stats->bHwError = stats->bCRC | stats->bICV;

	अगर (stats->Length < 24 || stats->Length > MAX_8192U_RX_SIZE)
		stats->bHwError |= 1;
	/* Get Driver Info */
	/* TODO: Need to verअगरy it on FGPA platक्रमm
	 * Driver info are written to the RxBuffer following rx desc
	 */
	अगर (stats->RxDrvInfoSize != 0) अणु
		driver_info = (काष्ठा rx_drvinfo_819x_usb *)(skb->data
				+ माप(काष्ठा rx_desc_819x_usb)
				+ stats->RxBufShअगरt
			      );
		/* unit: 0.5M */
		/* TODO */
		अगर (!stats->bHwError) अणु
			u8	ret_rate;

			ret_rate = HwRateToMRate90(driver_info->RxHT,
						   driver_info->RxRate);
			अगर (ret_rate == 0xff) अणु
				/* Abnormal Case: Receive CRC OK packet with Rx
				 * descriptor indicating non supported rate.
				 * Special Error Handling here
				 */

				stats->bHwError = 1;
				/* Set 1M rate by शेष */
				stats->rate = MGN_1M;
			पूर्ण अन्यथा अणु
				stats->rate = ret_rate;
			पूर्ण
		पूर्ण अन्यथा अणु
			stats->rate = 0x02;
		पूर्ण

		stats->bShortPreamble = driver_info->SPLCP;

		UpdateReceivedRateHistogramStatistics8190(dev, stats);

		stats->bIsAMPDU = (driver_info->PartAggr == 1);
		stats->bFirstMPDU = (driver_info->PartAggr == 1) &&
				    (driver_info->FirstAGGR == 1);
		stats->TimeStampLow = driver_info->TSFL;

		UpdateRxPktTimeStamp8190(dev, stats);

		/* Rx A-MPDU */
		अगर (driver_info->FirstAGGR == 1 || driver_info->PartAggr == 1)
			RT_TRACE(COMP_RXDESC,
				 "driver_info->FirstAGGR = %d, driver_info->PartAggr = %d\n",
				 driver_info->FirstAGGR, driver_info->PartAggr);
	पूर्ण

	skb_pull(skb, माप(काष्ठा rx_desc_819x_usb));
	/* Get Total offset of MPDU Frame Body */
	अगर ((stats->RxBufShअगरt + stats->RxDrvInfoSize) > 0) अणु
		stats->bShअगरt = 1;
		skb_pull(skb, stats->RxBufShअगरt + stats->RxDrvInfoSize);
	पूर्ण

	अगर (driver_info) अणु
		stats->RxIs40MHzPacket = driver_info->BW;
		TranslateRxSignalStuff819xUsb(skb, stats, driver_info);
	पूर्ण
पूर्ण

अटल व्योम rtl8192_rx_nomal(काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl8192_rx_info *info = (काष्ठा rtl8192_rx_info *)skb->cb;
	काष्ठा net_device *dev = info->dev;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा ieee80211_rx_stats stats = अणु
		.संकेत = 0,
		.noise = 0x100 - 98,
		.rate = 0,
		.freq = IEEE80211_24GHZ_BAND,
	पूर्ण;
	u32 rx_pkt_len = 0;
	काष्ठा rtl_80211_hdr_1addr *ieee80211_hdr = शून्य;
	bool unicast_packet = false;

	/* 20 is क्रम ps-poll */
	अगर ((skb->len >= (20 + माप(काष्ठा rx_desc_819x_usb))) && (skb->len < RX_URB_SIZE)) अणु
		/* first packet should not contain Rx aggregation header */
		query_rxdesc_status(skb, &stats, false);
		/* TODO */
		/* hardware related info */
		/* Process the MPDU received */
		skb_trim(skb, skb->len - 4/*sCrcLng*/);

		rx_pkt_len = skb->len;
		ieee80211_hdr = (काष्ठा rtl_80211_hdr_1addr *)skb->data;
		unicast_packet = false;
		अगर (is_broadcast_ether_addr(ieee80211_hdr->addr1)) अणु
			/* TODO */
		पूर्ण अन्यथा अगर (is_multicast_ether_addr(ieee80211_hdr->addr1)) अणु
			/* TODO */
		पूर्ण अन्यथा अणु
			/* unicast packet */
			unicast_packet = true;
		पूर्ण

		अगर (!ieee80211_rx(priv->ieee80211, skb, &stats)) अणु
			dev_kमुक्त_skb_any(skb);
		पूर्ण अन्यथा अणु
			priv->stats.rxoktotal++;
			अगर (unicast_packet)
				priv->stats.rxbytesunicast += rx_pkt_len;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->stats.rxurberr++;
		netdev_dbg(dev, "actual_length: %d\n", skb->len);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम rtl819xusb_process_received_packet(काष्ठा net_device *dev,
					       काष्ठा ieee80211_rx_stats *pstats)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	/* Get shअगरted bytes of Starting address of 802.11 header. */
	pstats->भव_address += get_rxpacket_shअगरtbytes_819xusb(pstats);
#अगर_घोषित TODO	/* about HCT */
	अगर (!Adapter->bInHctTest)
		CountRxErrStatistics(Adapter, pRfd);
#पूर्ण_अगर
#अगर_घोषित ENABLE_PS  /* क्रम adding ps function in future */
	RT_RF_POWER_STATE rtState;
	/* When RF is off, we should not count the packet क्रम hw/sw synchronize
	 * reason, ie. there may be a duration जबतक sw चयन is changed and
	 * hw चयन is being changed.
	 */
	Adapter->HalFunc.GetHwRegHandler(Adapter, HW_VAR_RF_STATE,
					 (u8 *)(&rtState));
	अगर (rtState == eRfOff)
		वापस;
#पूर्ण_अगर
	priv->stats.rxframgment++;

#अगर_घोषित TODO
	RmMonitorSignalStrength(Adapter, pRfd);
#पूर्ण_अगर
	/* We have to release RFD and वापस अगर rx pkt is cmd pkt. */
	अगर (rtl819xusb_rx_command_packet(dev, pstats))
		वापस;

#अगर_घोषित SW_CRC_CHECK
	SwCrcCheck();
#पूर्ण_अगर
पूर्ण

अटल व्योम query_rx_cmdpkt_desc_status(काष्ठा sk_buff *skb,
					काष्ठा ieee80211_rx_stats *stats)
अणु
	काष्ठा rx_desc_819x_usb *desc = (काष्ठा rx_desc_819x_usb *)skb->data;

	/* Get Rx Descriptor Inक्रमmation */
	stats->भव_address = (u8 *)skb->data;
	stats->Length = desc->Length;
	stats->RxDrvInfoSize = 0;
	stats->RxBufShअगरt = 0;
	stats->packetlength = stats->Length - scrclng;
	stats->fraglength = stats->packetlength;
	stats->fragoffset = 0;
	stats->ntotalfrag = 1;
पूर्ण

अटल व्योम rtl8192_rx_cmd(काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl8192_rx_info *info = (काष्ठा rtl8192_rx_info *)skb->cb;
	काष्ठा net_device *dev = info->dev;
	/* TODO */
	काष्ठा ieee80211_rx_stats stats = अणु
		.संकेत = 0,
		.noise = 0x100 - 98,
		.rate = 0,
		.freq = IEEE80211_24GHZ_BAND,
	पूर्ण;

	अगर ((skb->len >= (20 + माप(काष्ठा rx_desc_819x_usb))) && (skb->len < RX_URB_SIZE)) अणु
		query_rx_cmdpkt_desc_status(skb, &stats);
		/* prfd->queue_id = 1; */

		/* Process the command packet received. */

		rtl819xusb_process_received_packet(dev, &stats);

		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम rtl8192_irq_rx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा r8192_priv *priv = from_tasklet(priv, t, irq_rx_tasklet);
	काष्ठा sk_buff *skb;
	काष्ठा rtl8192_rx_info *info;

	जबतक (शून्य != (skb = skb_dequeue(&priv->skb_queue))) अणु
		info = (काष्ठा rtl8192_rx_info *)skb->cb;
		चयन (info->out_pipe) अणु
		/* Nomal packet pipe */
		हाल 3:
			priv->IrpPendingCount--;
			rtl8192_rx_nomal(skb);
			अवरोध;

		/* Command packet pipe */
		हाल 9:
			RT_TRACE(COMP_RECV, "command in-pipe index(%d)\n",
				 info->out_pipe);

			rtl8192_rx_cmd(skb);
			अवरोध;

		शेष: /* should never get here! */
			RT_TRACE(COMP_ERR, "Unknown in-pipe index(%d)\n",
				 info->out_pipe);
			dev_kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops rtl8192_netdev_ops = अणु
	.nकरो_खोलो               = rtl8192_खोलो,
	.nकरो_stop               = rtl8192_बंद,
	.nकरो_get_stats          = rtl8192_stats,
	.nकरो_tx_समयout         = tx_समयout,
	.nकरो_करो_ioctl           = rtl8192_ioctl,
	.nकरो_set_rx_mode	= r8192_set_multicast,
	.nकरो_set_mac_address    = r8192_set_mac_adr,
	.nकरो_validate_addr      = eth_validate_addr,
	.nकरो_start_xmit         = ieee80211_xmit,
पूर्ण;

/****************************************************************************
 *    ---------------------------- USB_STUFF---------------------------
 *****************************************************************************/

अटल पूर्णांक rtl8192_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा r8192_priv *priv = शून्य;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक ret;

	RT_TRACE(COMP_INIT, "Oops: i'm coming\n");

	dev = alloc_ieee80211(माप(काष्ठा r8192_priv));
	अगर (!dev)
		वापस -ENOMEM;

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);
	SET_NETDEV_DEV(dev, &पूर्णांकf->dev);
	priv = ieee80211_priv(dev);
	priv->ieee80211 = netdev_priv(dev);
	priv->udev = udev;

	dev->netdev_ops = &rtl8192_netdev_ops;

	dev->wireless_handlers = &r8192_wx_handlers_def;

	dev->type = ARPHRD_ETHER;

	dev->watchकरोg_समयo = HZ * 3;

	अगर (dev_alloc_name(dev, अगरname) < 0) अणु
		RT_TRACE(COMP_INIT,
			 "Oops: devname already taken! Trying wlan%%d...\n");
		अगरname = "wlan%d";
		dev_alloc_name(dev, अगरname);
	पूर्ण

	RT_TRACE(COMP_INIT, "Driver probe completed1\n");
	अगर (rtl8192_init(dev) != 0) अणु
		RT_TRACE(COMP_ERR, "Initialization failed");
		ret = -ENODEV;
		जाओ fail;
	पूर्ण
	netअगर_carrier_off(dev);
	netअगर_stop_queue(dev);

	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		जाओ fail2;

	RT_TRACE(COMP_INIT, "dev name=======> %s\n", dev->name);
	rtl8192_proc_init_one(dev);

	RT_TRACE(COMP_INIT, "Driver probe completed\n");
	वापस 0;

fail2:
	rtl8192_करोwn(dev);
fail:
	kमुक्त(priv->pFirmware);
	priv->pFirmware = शून्य;
	rtl8192_usb_deleteendpoपूर्णांकs(dev);
	msleep(10);
	मुक्त_ieee80211(dev);

	RT_TRACE(COMP_ERR, "wlan driver load failed\n");
	वापस ret;
पूर्ण

/* detach all the work and समयr काष्ठाure declared or inititialize
 * in r8192U_init function.
 */
अटल व्योम rtl8192_cancel_deferred_work(काष्ठा r8192_priv *priv)
अणु
	cancel_work_sync(&priv->reset_wq);
	cancel_delayed_work(&priv->watch_करोg_wq);
	cancel_delayed_work(&priv->update_beacon_wq);
	cancel_work_sync(&priv->qos_activate);
पूर्ण

अटल व्योम rtl8192_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा net_device *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	unरेजिस्टर_netdev(dev);

	RT_TRACE(COMP_DOWN, "=============>wlan driver to be removed\n");
	rtl8192_proc_हटाओ_one(dev);

	rtl8192_करोwn(dev);
	kमुक्त(priv->pFirmware);
	priv->pFirmware = शून्य;
	rtl8192_usb_deleteendpoपूर्णांकs(dev);
	usleep_range(10000, 11000);
	मुक्त_ieee80211(dev);

	RT_TRACE(COMP_DOWN, "wlan driver removed\n");
पूर्ण

अटल पूर्णांक __init rtl8192_usb_module_init(व्योम)
अणु
	पूर्णांक ret;

#अगर_घोषित CONFIG_IEEE80211_DEBUG
	ret = ieee80211_debug_init();
	अगर (ret) अणु
		pr_err("ieee80211_debug_init() failed %d\n", ret);
		वापस ret;
	पूर्ण
#पूर्ण_अगर
	ret = ieee80211_crypto_init();
	अगर (ret) अणु
		pr_err("ieee80211_crypto_init() failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ieee80211_crypto_tkip_init();
	अगर (ret) अणु
		pr_err("ieee80211_crypto_tkip_init() failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ieee80211_crypto_ccmp_init();
	अगर (ret) अणु
		pr_err("ieee80211_crypto_ccmp_init() failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ieee80211_crypto_wep_init();
	अगर (ret) अणु
		pr_err("ieee80211_crypto_wep_init() failed %d\n", ret);
		वापस ret;
	पूर्ण

	pr_info("\nLinux kernel driver for RTL8192 based WLAN cards\n");
	pr_info("Copyright (c) 2007-2008, Realsil Wlan\n");
	RT_TRACE(COMP_INIT, "Initializing module");
	RT_TRACE(COMP_INIT, "Wireless extensions version %d", WIRELESS_EXT);
	rtl8192_proc_module_init();
	वापस usb_रेजिस्टर(&rtl8192_usb_driver);
पूर्ण

अटल व्योम __निकास rtl8192_usb_module_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&rtl8192_usb_driver);

	RT_TRACE(COMP_DOWN, "Exiting");
पूर्ण

व्योम EnableHWSecurityConfig8192(काष्ठा net_device *dev)
अणु
	u8 SECR_value = 0x0;
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)ieee80211_priv(dev);
	काष्ठा ieee80211_device *ieee = priv->ieee80211;

	SECR_value = SCR_TxEncEnable | SCR_RxDecEnable;
	अगर (((ieee->pairwise_key_type == KEY_TYPE_WEP40) || (ieee->pairwise_key_type == KEY_TYPE_WEP104)) && (priv->ieee80211->auth_mode != 2)) अणु
		SECR_value |= SCR_RxUseDK;
		SECR_value |= SCR_TxUseDK;
	पूर्ण अन्यथा अगर ((ieee->iw_mode == IW_MODE_ADHOC) && (ieee->pairwise_key_type & (KEY_TYPE_CCMP | KEY_TYPE_TKIP))) अणु
		SECR_value |= SCR_RxUseDK;
		SECR_value |= SCR_TxUseDK;
	पूर्ण
	/* add HWSec active enable here.
	 * शेष using hwsec. when peer AP is in N mode only and
	 * pairwise_key_type is none_aes(which HT_IOT_ACT_PURE_N_MODE indicates
	 * it), use software security. when peer AP is in b,g,n mode mixed and
	 * pairwise_key_type is none_aes, use g mode hw security.
	 */

	ieee->hwsec_active = 1;

	/* add hwsec_support flag to totol control hw_sec on/off */
	अगर ((ieee->pHTInfo->IOTAction & HT_IOT_ACT_PURE_N_MODE) || !hwwep) अणु
		ieee->hwsec_active = 0;
		SECR_value &= ~SCR_RxDecEnable;
	पूर्ण
	RT_TRACE(COMP_SEC, "%s:, hwsec:%d, pairwise_key:%d, SECR_value:%x\n",
		 __func__, ieee->hwsec_active, ieee->pairwise_key_type,
		 SECR_value);
	ग_लिखो_nic_byte(dev, SECR,  SECR_value);
पूर्ण

व्योम setKey(काष्ठा net_device *dev, u8 entryno, u8 keyindex, u16 keytype,
	    u8 *macaddr, u8 शेषkey, u32 *keycontent)
अणु
	u32 target_command = 0;
	u32 target_content = 0;
	u16 us_config = 0;
	u8 i;

	अगर (entryno >= TOTAL_CAM_ENTRY)
		RT_TRACE(COMP_ERR, "cam entry exceeds in %s\n", __func__);

	RT_TRACE(COMP_SEC,
		 "====>to %s, dev:%p, EntryNo:%d, KeyIndex:%d, KeyType:%d, MacAddr%pM\n",
		 __func__, dev, entryno, keyindex, keytype, macaddr);

	अगर (शेषkey)
		us_config |= BIT(15) | (keytype << 2);
	अन्यथा
		us_config |= BIT(15) | (keytype << 2) | keyindex;

	क्रम (i = 0; i < CAM_CONTENT_COUNT; i++) अणु
		target_command  = i + CAM_CONTENT_COUNT * entryno;
		target_command |= BIT(31) | BIT(16);

		अगर (i == 0) अणु /* MAC|Config */
			target_content = (u32)(*(macaddr + 0)) << 16 |
					(u32)(*(macaddr + 1)) << 24 |
					(u32)us_config;

			ग_लिखो_nic_dword(dev, WCAMI, target_content);
			ग_लिखो_nic_dword(dev, RWCAM, target_command);
		पूर्ण अन्यथा अगर (i == 1) अणु /* MAC */
			target_content = (u32)(*(macaddr + 2))	 |
					(u32)(*(macaddr + 3)) <<  8 |
					(u32)(*(macaddr + 4)) << 16 |
					(u32)(*(macaddr + 5)) << 24;
			ग_लिखो_nic_dword(dev, WCAMI, target_content);
			ग_लिखो_nic_dword(dev, RWCAM, target_command);
		पूर्ण अन्यथा अणु
			/* Key Material */
			अगर (keycontent) अणु
				ग_लिखो_nic_dword(dev, WCAMI,
						*(keycontent + i - 2));
				ग_लिखो_nic_dword(dev, RWCAM, target_command);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/***************************************************************************
 *    ------------------- module init / निकास stubs ----------------
 ****************************************************************************/
module_init(rtl8192_usb_module_init);
module_निकास(rtl8192_usb_module_निकास);
