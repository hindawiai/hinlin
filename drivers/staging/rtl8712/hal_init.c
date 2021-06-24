<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * hal_init.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>.
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _HAL_INIT_C_

#समावेश <linux/usb.h>
#समावेश <linux/device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "usb_osintf.h"

#घोषणा FWBUFF_ALIGN_SZ 512
#घोषणा MAX_DUMP_FWSZ (48 * 1024)

अटल व्योम rtl871x_load_fw_cb(स्थिर काष्ठा firmware *firmware, व्योम *context)
अणु
	काष्ठा _adapter *adapter = context;

	अगर (!firmware) अणु
		काष्ठा usb_device *udev = adapter->dvobjpriv.pusbdev;
		काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf = adapter->pusb_पूर्णांकf;

		dev_err(&udev->dev, "r8712u: Firmware request failed\n");
		usb_put_dev(udev);
		usb_set_पूर्णांकfdata(usb_पूर्णांकf, शून्य);
		complete(&adapter->rtl8712_fw_पढ़ोy);
		वापस;
	पूर्ण
	adapter->fw = firmware;
	/* firmware available - start netdev */
	रेजिस्टर_netdev(adapter->pnetdev);
	complete(&adapter->rtl8712_fw_पढ़ोy);
पूर्ण

अटल स्थिर अक्षर firmware_file[] = "rtlwifi/rtl8712u.bin";

पूर्णांक rtl871x_load_fw(काष्ठा _adapter *padapter)
अणु
	काष्ठा device *dev = &padapter->dvobjpriv.pusbdev->dev;
	पूर्णांक rc;

	init_completion(&padapter->rtl8712_fw_पढ़ोy);
	dev_info(dev, "r8712u: Loading firmware from \"%s\"\n", firmware_file);
	rc = request_firmware_noरुको(THIS_MODULE, 1, firmware_file, dev,
				     GFP_KERNEL, padapter, rtl871x_load_fw_cb);
	अगर (rc)
		dev_err(dev, "r8712u: Firmware request error %d\n", rc);
	वापस rc;
पूर्ण
MODULE_FIRMWARE("rtlwifi/rtl8712u.bin");

अटल u32 rtl871x_खोलो_fw(काष्ठा _adapter *adapter, स्थिर u8 **mappedfw)
अणु
	अगर (adapter->fw->size > 200000) अणु
		dev_err(&adapter->pnetdev->dev, "r8712u: Bad fw->size of %zu\n",
			adapter->fw->size);
		वापस 0;
	पूर्ण
	*mappedfw = adapter->fw->data;
	वापस adapter->fw->size;
पूर्ण

अटल व्योम fill_fwpriv(काष्ठा _adapter *adapter, काष्ठा fw_priv *fwpriv)
अणु
	काष्ठा dvobj_priv *dvobj = &adapter->dvobjpriv;
	काष्ठा registry_priv *regpriv = &adapter->registrypriv;

	स_रखो(fwpriv, 0, माप(काष्ठा fw_priv));
	/* toकरो: check अगर needs endian conversion */
	fwpriv->hci_sel =  RTL8712_HCI_TYPE_72USB;
	fwpriv->usb_ep_num = (u8)dvobj->nr_endpoपूर्णांक;
	fwpriv->bw_40MHz_en = regpriv->cbw40_enable;
	चयन (regpriv->rf_config) अणु
	हाल RTL8712_RF_1T1R:
		fwpriv->rf_config = RTL8712_RFC_1T1R;
		अवरोध;
	हाल RTL8712_RF_2T2R:
		fwpriv->rf_config = RTL8712_RFC_2T2R;
		अवरोध;
	हाल RTL8712_RF_1T2R:
	शेष:
		fwpriv->rf_config = RTL8712_RFC_1T2R;
	पूर्ण
	fwpriv->mp_mode = (regpriv->mp_mode == 1);
	/* 0:off 1:on 2:स्वतः */
	fwpriv->vcs_type = regpriv->vrtl_carrier_sense;
	fwpriv->vcs_mode = regpriv->vcs_type; /* 1:RTS/CTS 2:CTS to self */
	/* शेष enable turbo_mode */
	fwpriv->turbo_mode = (regpriv->wअगरi_test != 1);
	fwpriv->low_घातer_mode = regpriv->low_घातer;
पूर्ण

अटल व्योम update_fwhdr(काष्ठा fw_hdr	*pfwhdr, स्थिर u8 *pmappedfw)
अणु
	pfwhdr->signature = le16_to_cpu(*(__le16 *)pmappedfw);
	pfwhdr->version = le16_to_cpu(*(__le16 *)(pmappedfw + 2));
	/* define the size of boot loader */
	pfwhdr->dmem_size = le32_to_cpu(*(__le32 *)(pmappedfw + 4));
	/* define the size of FW in IMEM */
	pfwhdr->img_IMEM_size = le32_to_cpu(*(__le32 *)(pmappedfw + 8));
	/* define the size of FW in SRAM */
	pfwhdr->img_SRAM_size = le32_to_cpu(*(__le32 *)(pmappedfw + 12));
	/* define the size of DMEM variable */
	pfwhdr->fw_priv_sz = le32_to_cpu(*(__le32 *)(pmappedfw + 16));
पूर्ण

अटल u8 chk_fwhdr(काष्ठा fw_hdr *pfwhdr, u32 ulfilelength)
अणु
	u32	fwhdrsz, fw_sz;

	/* check signature */
	अगर ((pfwhdr->signature != 0x8712) && (pfwhdr->signature != 0x8192))
		वापस _FAIL;
	/* check fw_priv_sze & माप(काष्ठा fw_priv) */
	अगर (pfwhdr->fw_priv_sz != माप(काष्ठा fw_priv))
		वापस _FAIL;
	/* check fw_sz & image_fw_sz */
	fwhdrsz = दुरत्व(काष्ठा fw_hdr, fwpriv) + pfwhdr->fw_priv_sz;
	fw_sz =  fwhdrsz + pfwhdr->img_IMEM_size + pfwhdr->img_SRAM_size +
		 pfwhdr->dmem_size;
	अगर (fw_sz != ulfilelength)
		वापस _FAIL;
	वापस _SUCCESS;
पूर्ण

अटल u8 rtl8712_dl_fw(काष्ठा _adapter *adapter)
अणु
	sपूर्णांक i;
	u8 पंचांगp8, पंचांगp8_a;
	u16 पंचांगp16;
	u32 maxlen = 0; /* क्रम compare usage */
	uपूर्णांक dump_imem_sz, imem_sz, dump_emem_sz, emem_sz; /* max = 49152; */
	काष्ठा fw_hdr fwhdr;
	u32 ulfilelength;	/* FW file size */
	स्थिर u8 *mappedfw = शून्य;
	u8 *पंचांगpअक्षर = शून्य, *payload, *ptr;
	काष्ठा tx_desc *txdesc;
	u32 txdscp_sz = माप(काष्ठा tx_desc);
	u8 ret = _FAIL;

	ulfilelength = rtl871x_खोलो_fw(adapter, &mappedfw);
	अगर (mappedfw && (ulfilelength > 0)) अणु
		update_fwhdr(&fwhdr, mappedfw);
		अगर (chk_fwhdr(&fwhdr, ulfilelength) == _FAIL)
			वापस ret;
		fill_fwpriv(adapter, &fwhdr.fwpriv);
		/* firmware check ok */
		maxlen = (fwhdr.img_IMEM_size > fwhdr.img_SRAM_size) ?
			  fwhdr.img_IMEM_size : fwhdr.img_SRAM_size;
		maxlen += txdscp_sz;
		पंचांगpअक्षर = kदो_स्मृति(maxlen + FWBUFF_ALIGN_SZ, GFP_KERNEL);
		अगर (!पंचांगpअक्षर)
			वापस ret;

		txdesc = (काष्ठा tx_desc *)(पंचांगpअक्षर + FWBUFF_ALIGN_SZ -
			    ((addr_t)(पंचांगpअक्षर) & (FWBUFF_ALIGN_SZ - 1)));
		payload = (u8 *)(txdesc) + txdscp_sz;
		ptr = (u8 *)mappedfw + दुरत्व(काष्ठा fw_hdr, fwpriv) +
		      fwhdr.fw_priv_sz;
		/* Download FirmWare */
		/* 1. determine IMEM code size and Load IMEM Code Section */
		imem_sz = fwhdr.img_IMEM_size;
		करो अणु
			स_रखो(txdesc, 0, TXDESC_SIZE);
			अगर (imem_sz >  MAX_DUMP_FWSZ/*49152*/) अणु
				dump_imem_sz = MAX_DUMP_FWSZ;
			पूर्ण अन्यथा अणु
				dump_imem_sz = imem_sz;
				txdesc->txdw0 |= cpu_to_le32(BIT(28));
			पूर्ण
			txdesc->txdw0 |= cpu_to_le32(dump_imem_sz &
						       0x0000ffff);
			स_नकल(payload, ptr, dump_imem_sz);
			r8712_ग_लिखो_mem(adapter, RTL8712_DMA_VOQ,
					dump_imem_sz + TXDESC_SIZE,
					(u8 *)txdesc);
			ptr += dump_imem_sz;
			imem_sz -= dump_imem_sz;
		पूर्ण जबतक (imem_sz > 0);
		i = 10;
		पंचांगp16 = r8712_पढ़ो16(adapter, TCR);
		जबतक (((पंचांगp16 & _IMEM_CODE_DONE) == 0) && (i > 0)) अणु
			usleep_range(10, 1000);
			पंचांगp16 = r8712_पढ़ो16(adapter, TCR);
			i--;
		पूर्ण
		अगर (i == 0 || (पंचांगp16 & _IMEM_CHK_RPT) == 0)
			जाओ निकास_fail;

		/* 2.Download EMEM code size and Load EMEM Code Section */
		emem_sz = fwhdr.img_SRAM_size;
		करो अणु
			स_रखो(txdesc, 0, TXDESC_SIZE);
			अगर (emem_sz >  MAX_DUMP_FWSZ) अणु /* max=48k */
				dump_emem_sz = MAX_DUMP_FWSZ;
			पूर्ण अन्यथा अणु
				dump_emem_sz = emem_sz;
				txdesc->txdw0 |= cpu_to_le32(BIT(28));
			पूर्ण
			txdesc->txdw0 |= cpu_to_le32(dump_emem_sz &
						       0x0000ffff);
			स_नकल(payload, ptr, dump_emem_sz);
			r8712_ग_लिखो_mem(adapter, RTL8712_DMA_VOQ,
					dump_emem_sz + TXDESC_SIZE,
					(u8 *)txdesc);
			ptr += dump_emem_sz;
			emem_sz -= dump_emem_sz;
		पूर्ण जबतक (emem_sz > 0);
		i = 5;
		पंचांगp16 = r8712_पढ़ो16(adapter, TCR);
		जबतक (((पंचांगp16 & _EMEM_CODE_DONE) == 0) && (i > 0)) अणु
			usleep_range(10, 1000);
			पंचांगp16 = r8712_पढ़ो16(adapter, TCR);
			i--;
		पूर्ण
		अगर (i == 0 || (पंचांगp16 & _EMEM_CHK_RPT) == 0)
			जाओ निकास_fail;

		/* 3.Enable CPU */
		पंचांगp8 = r8712_पढ़ो8(adapter, SYS_CLKR);
		r8712_ग_लिखो8(adapter, SYS_CLKR, पंचांगp8 | BIT(2));
		पंचांगp8_a = r8712_पढ़ो8(adapter, SYS_CLKR);
		अगर (पंचांगp8_a != (पंचांगp8 | BIT(2)))
			जाओ निकास_fail;

		पंचांगp8 = r8712_पढ़ो8(adapter, SYS_FUNC_EN + 1);
		r8712_ग_लिखो8(adapter, SYS_FUNC_EN + 1, पंचांगp8 | BIT(2));
		पंचांगp8_a = r8712_पढ़ो8(adapter, SYS_FUNC_EN + 1);
		अगर (पंचांगp8_a != (पंचांगp8 | BIT(2)))
			जाओ निकास_fail;

		r8712_पढ़ो32(adapter, TCR);

		/* 4.polling IMEM Ready */
		i = 100;
		पंचांगp16 = r8712_पढ़ो16(adapter, TCR);
		जबतक (((पंचांगp16 & _IMEM_RDY) == 0) && (i > 0)) अणु
			msleep(20);
			पंचांगp16 = r8712_पढ़ो16(adapter, TCR);
			i--;
		पूर्ण
		अगर (i == 0) अणु
			r8712_ग_लिखो16(adapter, 0x10250348, 0xc000);
			r8712_ग_लिखो16(adapter, 0x10250348, 0xc001);
			r8712_ग_लिखो16(adapter, 0x10250348, 0x2000);
			r8712_ग_लिखो16(adapter, 0x10250348, 0x2001);
			r8712_ग_लिखो16(adapter, 0x10250348, 0x2002);
			r8712_ग_लिखो16(adapter, 0x10250348, 0x2003);
			जाओ निकास_fail;
		पूर्ण
		/* 5.Download DMEM code size and Load EMEM Code Section */
		स_रखो(txdesc, 0, TXDESC_SIZE);
		txdesc->txdw0 |= cpu_to_le32(fwhdr.fw_priv_sz & 0x0000ffff);
		txdesc->txdw0 |= cpu_to_le32(BIT(28));
		स_नकल(payload, &fwhdr.fwpriv, fwhdr.fw_priv_sz);
		r8712_ग_लिखो_mem(adapter, RTL8712_DMA_VOQ,
				fwhdr.fw_priv_sz + TXDESC_SIZE, (u8 *)txdesc);

		/* polling dmem code करोne */
		i = 100;
		पंचांगp16 = r8712_पढ़ो16(adapter, TCR);
		जबतक (((पंचांगp16 & _DMEM_CODE_DONE) == 0) && (i > 0)) अणु
			msleep(20);
			पंचांगp16 = r8712_पढ़ो16(adapter, TCR);
			i--;
		पूर्ण
		अगर (i == 0)
			जाओ निकास_fail;

		पंचांगp8 = r8712_पढ़ो8(adapter, 0x1025000A);
		अगर (पंचांगp8 & BIT(4)) /* When boot from EEPROM,
				    * & FW need more समय to पढ़ो EEPROM
				    */
			i = 60;
		अन्यथा			/* boot from EFUSE */
			i = 30;
		पंचांगp16 = r8712_पढ़ो16(adapter, TCR);
		जबतक (((पंचांगp16 & _FWRDY) == 0) && (i > 0)) अणु
			msleep(100);
			पंचांगp16 = r8712_पढ़ो16(adapter, TCR);
			i--;
		पूर्ण
		अगर (i == 0)
			जाओ निकास_fail;
	पूर्ण अन्यथा अणु
		जाओ निकास_fail;
	पूर्ण
	ret = _SUCCESS;

निकास_fail:
	kमुक्त(पंचांगpअक्षर);
	वापस ret;
पूर्ण

uपूर्णांक rtl8712_hal_init(काष्ठा _adapter *padapter)
अणु
	u32 val32;
	पूर्णांक i;

	/* r8712 firmware करोwnload */
	अगर (rtl8712_dl_fw(padapter) != _SUCCESS)
		वापस _FAIL;

	netdev_info(padapter->pnetdev, "1 RCR=0x%x\n",
		    r8712_पढ़ो32(padapter, RCR));
	val32 = r8712_पढ़ो32(padapter, RCR);
	r8712_ग_लिखो32(padapter, RCR, (val32 | BIT(26))); /* Enable RX TCP
							  * Checksum offload
							  */
	netdev_info(padapter->pnetdev, "2 RCR=0x%x\n",
		    r8712_पढ़ो32(padapter, RCR));
	val32 = r8712_पढ़ो32(padapter, RCR);
	r8712_ग_लिखो32(padapter, RCR, (val32 | BIT(25))); /* Append PHY status */
	val32 = r8712_पढ़ो32(padapter, 0x10250040);
	r8712_ग_लिखो32(padapter,  0x10250040, (val32 & 0x00FFFFFF));
	/* क्रम usb rx aggregation */
	r8712_ग_लिखो8(padapter, 0x102500B5, r8712_पढ़ो8(padapter, 0x102500B5) |
	       BIT(0)); /* page = 128bytes */
	r8712_ग_लिखो8(padapter, 0x102500BD, r8712_पढ़ो8(padapter, 0x102500BD) |
	       BIT(7)); /* enable usb rx aggregation */
	r8712_ग_लिखो8(padapter, 0x102500D9, 1); /* TH=1 => means that invalidate
						*  usb rx aggregation
						*/
	r8712_ग_लिखो8(padapter, 0x1025FE5B, 0x04); /* 1.7ms/4 */
	/* Fix the RX FIFO issue(USB error) */
	r8712_ग_लिखो8(padapter, 0x1025fe5C, r8712_पढ़ो8(padapter, 0x1025fe5C)
		     | BIT(7));
	क्रम (i = 0; i < ETH_ALEN; i++)
		padapter->eeprompriv.mac_addr[i] = r8712_पढ़ो8(padapter,
							       MACID + i);
	वापस _SUCCESS;
पूर्ण

uपूर्णांक rtl8712_hal_deinit(काष्ठा _adapter *padapter)
अणु
	r8712_ग_लिखो8(padapter, RF_CTRL, 0x00);
	/* Turn off BB */
	msleep(20);
	/* Turn off MAC	*/
	r8712_ग_लिखो8(padapter, SYS_CLKR + 1, 0x38); /* Switch Control Path */
	r8712_ग_लिखो8(padapter, SYS_FUNC_EN + 1, 0x70);
	r8712_ग_लिखो8(padapter, PMC_FSM, 0x06);  /* Enable Loader Data Keep */
	r8712_ग_लिखो8(padapter, SYS_ISO_CTRL, 0xF9); /* Isolation संकेतs from
						     * CORE, PLL
						     */
	r8712_ग_लिखो8(padapter, SYS_ISO_CTRL + 1, 0xe8); /* Enable EFUSE 1.2V */
	r8712_ग_लिखो8(padapter, AFE_PLL_CTRL, 0x00); /* Disable AFE PLL. */
	r8712_ग_लिखो8(padapter, LDOA15_CTRL, 0x54);  /* Disable A15V */
	r8712_ग_लिखो8(padapter, SYS_FUNC_EN + 1, 0x50); /* Disable E-Fuse 1.2V */
	r8712_ग_लिखो8(padapter, LDOV12D_CTRL, 0x24); /* Disable LDO12(क्रम CE) */
	r8712_ग_लिखो8(padapter, AFE_MISC, 0x30); /* Disable AFE BG&MB */
	/* Option क्रम Disable 1.6V LDO.	*/
	r8712_ग_लिखो8(padapter, SPS0_CTRL, 0x56); /* Disable 1.6V LDO */
	r8712_ग_लिखो8(padapter, SPS0_CTRL + 1, 0x43);  /* Set SW PFM */
	वापस _SUCCESS;
पूर्ण

uपूर्णांक rtl871x_hal_init(काष्ठा _adapter *padapter)
अणु
	padapter->hw_init_completed = false;
	अगर (!padapter->halpriv.hal_bus_init)
		वापस _FAIL;
	अगर (padapter->halpriv.hal_bus_init(padapter) != _SUCCESS)
		वापस _FAIL;
	अगर (rtl8712_hal_init(padapter) == _SUCCESS) अणु
		padapter->hw_init_completed = true;
	पूर्ण अन्यथा अणु
		padapter->hw_init_completed = false;
		वापस _FAIL;
	पूर्ण
	वापस _SUCCESS;
पूर्ण
