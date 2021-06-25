<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../base.h"
#समावेश "../efuse.h"
#समावेश "fw_common.h"
#समावेश <linux/module.h>

व्योम rtl8723_enable_fw_करोwnload(काष्ठा ieee80211_hw *hw, bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp;

	अगर (enable) अणु
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1,
			       पंचांगp | 0x04);

		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, पंचांगp | 0x01);

		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL + 2);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL + 2, पंचांगp & 0xf7);
	पूर्ण अन्यथा अणु
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, पंचांगp & 0xfe);

		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL + 1, 0x00);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_enable_fw_करोwnload);

व्योम rtl8723_ग_लिखो_fw(काष्ठा ieee80211_hw *hw,
		      क्रमागत version_8723e version,
		      u8 *buffer, u32 size, u8 max_page)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 *bufferptr = buffer;
	u32 page_nums, reमुख्य_size;
	u32 page, offset;

	rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE, "FW size is %d bytes,\n", size);

	rtl_fill_dummy(bufferptr, &size);

	page_nums = size / FW_8192C_PAGE_SIZE;
	reमुख्य_size = size % FW_8192C_PAGE_SIZE;

	अगर (page_nums > max_page) अणु
		pr_err("Page numbers should not greater than %d\n",
		       max_page);
	पूर्ण
	क्रम (page = 0; page < page_nums; page++) अणु
		offset = page * FW_8192C_PAGE_SIZE;
		rtl_fw_page_ग_लिखो(hw, page, (bufferptr + offset),
				  FW_8192C_PAGE_SIZE);
	पूर्ण

	अगर (reमुख्य_size) अणु
		offset = page_nums * FW_8192C_PAGE_SIZE;
		page = page_nums;
		rtl_fw_page_ग_लिखो(hw, page, (bufferptr + offset), reमुख्य_size);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE, "FW write done.\n");
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_ग_लिखो_fw);

व्योम rtl8723ae_firmware_selfreset(काष्ठा ieee80211_hw *hw)
अणु
	u8 u1b_पंचांगp;
	u8 delay = 100;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_HMETFR + 3, 0x20);
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);

	जबतक (u1b_पंचांगp & BIT(2)) अणु
		delay--;
		अगर (delay == 0)
			अवरोध;
		udelay(50);
		u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	पूर्ण
	अगर (delay == 0) अणु
		u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1,
			       u1b_पंचांगp&(~BIT(2)));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723ae_firmware_selfreset);

व्योम rtl8723be_firmware_selfreset(काष्ठा ieee80211_hw *hw)
अणु
	u8 u1b_पंचांगp;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL + 1, (u1b_पंचांगp & (~BIT(0))));

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, (u1b_पंचांगp & (~BIT(2))));
	udelay(50);

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_RSV_CTRL + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL + 1, (u1b_पंचांगp | BIT(0)));

	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, (u1b_पंचांगp | BIT(2)));

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"_8051Reset8723be(): 8051 reset success .\n");
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723be_firmware_selfreset);

पूर्णांक rtl8723_fw_मुक्त_to_go(काष्ठा ieee80211_hw *hw, bool is_8723be,
			  पूर्णांक max_count)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक err = -EIO;
	u32 counter = 0;
	u32 value32;

	करो अणु
		value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL);
	पूर्ण जबतक ((counter++ < max_count) &&
		 (!(value32 & FWDL_CHKSUM_RPT)));

	अगर (counter >= max_count) अणु
		pr_err("chksum report fail ! REG_MCUFWDL:0x%08x .\n",
		       value32);
		जाओ निकास;
	पूर्ण
	value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL) | MCUFWDL_RDY;
	value32 &= ~WINTINI_RDY;
	rtl_ग_लिखो_dword(rtlpriv, REG_MCUFWDL, value32);

	अगर (is_8723be)
		rtl8723be_firmware_selfreset(hw);
	counter = 0;

	करो अणु
		value32 = rtl_पढ़ो_dword(rtlpriv, REG_MCUFWDL);
		अगर (value32 & WINTINI_RDY) अणु
			rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE,
				"Polling FW ready success!! REG_MCUFWDL:0x%08x .\n",
				value32);
			err = 0;
			जाओ निकास;
		पूर्ण

		mdelay(FW_8192C_POLLING_DELAY);

	पूर्ण जबतक (counter++ < max_count);

	pr_err("Polling FW ready fail!! REG_MCUFWDL:0x%08x .\n",
	       value32);

निकास:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_fw_मुक्त_to_go);

पूर्णांक rtl8723_करोwnload_fw(काष्ठा ieee80211_hw *hw,
			bool is_8723be, पूर्णांक max_count)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtlwअगरi_firmware_header *pfwheader;
	u8 *pfwdata;
	u32 fwsize;
	पूर्णांक err;
	क्रमागत version_8723e version = rtlhal->version;
	पूर्णांक max_page;

	अगर (rtlpriv->max_fw_size == 0 || !rtlhal->pfirmware)
		वापस 1;

	pfwheader = (काष्ठा rtlwअगरi_firmware_header *)rtlhal->pfirmware;
	rtlhal->fw_version = le16_to_cpu(pfwheader->version);
	rtlhal->fw_subversion = pfwheader->subversion;
	pfwdata = rtlhal->pfirmware;
	fwsize = rtlhal->fwsize;

	अगर (!is_8723be)
		max_page = 6;
	अन्यथा
		max_page = 8;
	अगर (rtlpriv->cfg->ops->is_fw_header(pfwheader)) अणु
		rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD,
			"Firmware Version(%d), Signature(%#x), Size(%d)\n",
			pfwheader->version, pfwheader->signature,
			(पूर्णांक)माप(काष्ठा rtlwअगरi_firmware_header));

		pfwdata = pfwdata + माप(काष्ठा rtlwअगरi_firmware_header);
		fwsize = fwsize - माप(काष्ठा rtlwअगरi_firmware_header);
	पूर्ण

	अगर (rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL)&BIT(7)) अणु
		अगर (is_8723be)
			rtl8723be_firmware_selfreset(hw);
		अन्यथा
			rtl8723ae_firmware_selfreset(hw);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0x00);
	पूर्ण
	rtl8723_enable_fw_करोwnload(hw, true);
	rtl8723_ग_लिखो_fw(hw, version, pfwdata, fwsize, max_page);
	rtl8723_enable_fw_करोwnload(hw, false);

	err = rtl8723_fw_मुक्त_to_go(hw, is_8723be, max_count);
	अगर (err)
		pr_err("Firmware is not ready to run!\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_करोwnload_fw);

bool rtl8723_cmd_send_packet(काष्ठा ieee80211_hw *hw,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring;
	काष्ठा rtl_tx_desc *pdesc;
	काष्ठा sk_buff *pskb = शून्य;
	अचिन्हित दीर्घ flags;

	ring = &rtlpci->tx_ring[BEACON_QUEUE];

	pskb = __skb_dequeue(&ring->queue);
	kमुक्त_skb(pskb);
	spin_lock_irqsave(&rtlpriv->locks.irq_th_lock, flags);

	pdesc = &ring->desc[0];
	rtlpriv->cfg->ops->fill_tx_cmddesc(hw, (u8 *)pdesc, 1, 1, skb);

	__skb_queue_tail(&ring->queue, skb);

	spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);

	rtlpriv->cfg->ops->tx_polling(hw, BEACON_QUEUE);

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_cmd_send_packet);
