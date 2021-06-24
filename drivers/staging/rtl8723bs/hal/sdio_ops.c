<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 *******************************************************************************/
#घोषणा _SDIO_OPS_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtl8723b_hal.h>

/*  */
/*  Description: */
/*	The following mapping is क्रम SDIO host local रेजिस्टर space. */
/*  */
/*  Cपढ़ोted by Roger, 2011.01.31. */
/*  */
अटल व्योम hal_sdio_get_cmd_addr_8723b(
	काष्ठा adapter *adapter,
	u8 device_id,
	u32 addr,
	u32 *cmdaddr
)
अणु
	चयन (device_id) अणु
	हाल SDIO_LOCAL_DEVICE_ID:
		*cmdaddr = ((SDIO_LOCAL_DEVICE_ID << 13) | (addr & SDIO_LOCAL_MSK));
		अवरोध;

	हाल WLAN_IOREG_DEVICE_ID:
		*cmdaddr = ((WLAN_IOREG_DEVICE_ID << 13) | (addr & WLAN_IOREG_MSK));
		अवरोध;

	हाल WLAN_TX_HIQ_DEVICE_ID:
		*cmdaddr = ((WLAN_TX_HIQ_DEVICE_ID << 13) | (addr & WLAN_FIFO_MSK));
		अवरोध;

	हाल WLAN_TX_MIQ_DEVICE_ID:
		*cmdaddr = ((WLAN_TX_MIQ_DEVICE_ID << 13) | (addr & WLAN_FIFO_MSK));
		अवरोध;

	हाल WLAN_TX_LOQ_DEVICE_ID:
		*cmdaddr = ((WLAN_TX_LOQ_DEVICE_ID << 13) | (addr & WLAN_FIFO_MSK));
		अवरोध;

	हाल WLAN_RX0FF_DEVICE_ID:
		*cmdaddr = ((WLAN_RX0FF_DEVICE_ID << 13) | (addr & WLAN_RX0FF_MSK));
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल u8 get_deviceid(u32 addr)
अणु
	u8 devide_id;
	u16 pseuकरो_id;

	pseuकरो_id = (u16)(addr >> 16);
	चयन (pseuकरो_id) अणु
	हाल 0x1025:
		devide_id = SDIO_LOCAL_DEVICE_ID;
		अवरोध;

	हाल 0x1026:
		devide_id = WLAN_IOREG_DEVICE_ID;
		अवरोध;

	हाल 0x1031:
		devide_id = WLAN_TX_HIQ_DEVICE_ID;
		अवरोध;

	हाल 0x1032:
		devide_id = WLAN_TX_MIQ_DEVICE_ID;
		अवरोध;

	हाल 0x1033:
		devide_id = WLAN_TX_LOQ_DEVICE_ID;
		अवरोध;

	हाल 0x1034:
		devide_id = WLAN_RX0FF_DEVICE_ID;
		अवरोध;

	शेष:
		devide_id = WLAN_IOREG_DEVICE_ID;
		अवरोध;
	पूर्ण

	वापस devide_id;
पूर्ण

अटल u32 _cvrt2ftaddr(स्थिर u32 addr, u8 *pdevice_id, u16 *poffset)
अणु
	u8 device_id;
	u16 offset;
	u32 ftaddr;

	device_id = get_deviceid(addr);
	offset = 0;

	चयन (device_id) अणु
	हाल SDIO_LOCAL_DEVICE_ID:
		offset = addr & SDIO_LOCAL_MSK;
		अवरोध;

	हाल WLAN_TX_HIQ_DEVICE_ID:
	हाल WLAN_TX_MIQ_DEVICE_ID:
	हाल WLAN_TX_LOQ_DEVICE_ID:
		offset = addr & WLAN_FIFO_MSK;
		अवरोध;

	हाल WLAN_RX0FF_DEVICE_ID:
		offset = addr & WLAN_RX0FF_MSK;
		अवरोध;

	हाल WLAN_IOREG_DEVICE_ID:
	शेष:
		device_id = WLAN_IOREG_DEVICE_ID;
		offset = addr & WLAN_IOREG_MSK;
		अवरोध;
	पूर्ण
	ftaddr = (device_id << 13) | offset;

	अगर (pdevice_id)
		*pdevice_id = device_id;
	अगर (poffset)
		*poffset = offset;

	वापस ftaddr;
पूर्ण

अटल u8 sdio_पढ़ो8(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr)
अणु
	u32 ftaddr;
	ftaddr = _cvrt2ftaddr(addr, शून्य, शून्य);

	वापस sd_पढ़ो8(पूर्णांकfhdl, ftaddr, शून्य);
पूर्ण

अटल u16 sdio_पढ़ो16(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr)
अणु
	u32 ftaddr;
	__le16 le_पंचांगp;

	ftaddr = _cvrt2ftaddr(addr, शून्य, शून्य);
	sd_cmd52_पढ़ो(पूर्णांकfhdl, ftaddr, 2, (u8 *)&le_पंचांगp);

	वापस le16_to_cpu(le_पंचांगp);
पूर्ण

अटल u32 sdio_पढ़ो32(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr)
अणु
	काष्ठा adapter *adapter;
	u8 mac_pwr_ctrl_on;
	u8 device_id;
	u16 offset;
	u32 ftaddr;
	u8 shअगरt;
	u32 val;
	s32 err;
	__le32 le_पंचांगp;

	adapter = पूर्णांकfhdl->padapter;
	ftaddr = _cvrt2ftaddr(addr, &device_id, &offset);

	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	अगर (
		((device_id == WLAN_IOREG_DEVICE_ID) && (offset < 0x100)) ||
		(!mac_pwr_ctrl_on) ||
		(adapter_to_pwrctl(adapter)->fw_current_in_ps_mode)
	) अणु
		err = sd_cmd52_पढ़ो(पूर्णांकfhdl, ftaddr, 4, (u8 *)&le_पंचांगp);
		वापस le32_to_cpu(le_पंचांगp);
	पूर्ण

	/*  4 bytes alignment */
	shअगरt = ftaddr & 0x3;
	अगर (shअगरt == 0) अणु
		val = sd_पढ़ो32(पूर्णांकfhdl, ftaddr, शून्य);
	पूर्ण अन्यथा अणु
		u8 *पंचांगpbuf;

		पंचांगpbuf = rtw_दो_स्मृति(8);
		अगर (!पंचांगpbuf)
			वापस SDIO_ERR_VAL32;

		ftaddr &= ~(u16)0x3;
		sd_पढ़ो(पूर्णांकfhdl, ftaddr, 8, पंचांगpbuf);
		स_नकल(&le_पंचांगp, पंचांगpbuf + shअगरt, 4);
		val = le32_to_cpu(le_पंचांगp);

		kमुक्त(पंचांगpbuf);
	पूर्ण
	वापस val;
पूर्ण

अटल s32 sdio_पढ़ोN(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr, u32 cnt, u8 *buf)
अणु
	काष्ठा adapter *adapter;
	u8 mac_pwr_ctrl_on;
	u8 device_id;
	u16 offset;
	u32 ftaddr;
	u8 shअगरt;
	s32 err;

	adapter = पूर्णांकfhdl->padapter;
	err = 0;

	ftaddr = _cvrt2ftaddr(addr, &device_id, &offset);

	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	अगर (
		((device_id == WLAN_IOREG_DEVICE_ID) && (offset < 0x100)) ||
		(!mac_pwr_ctrl_on) ||
		(adapter_to_pwrctl(adapter)->fw_current_in_ps_mode)
	)
		वापस sd_cmd52_पढ़ो(पूर्णांकfhdl, ftaddr, cnt, buf);

	/*  4 bytes alignment */
	shअगरt = ftaddr & 0x3;
	अगर (shअगरt == 0) अणु
		err = sd_पढ़ो(पूर्णांकfhdl, ftaddr, cnt, buf);
	पूर्ण अन्यथा अणु
		u8 *पंचांगpbuf;
		u32 n;

		ftaddr &= ~(u16)0x3;
		n = cnt + shअगरt;
		पंचांगpbuf = rtw_दो_स्मृति(n);
		अगर (!पंचांगpbuf)
			वापस -1;

		err = sd_पढ़ो(पूर्णांकfhdl, ftaddr, n, पंचांगpbuf);
		अगर (!err)
			स_नकल(buf, पंचांगpbuf + shअगरt, cnt);
		kमुक्त(पंचांगpbuf);
	पूर्ण
	वापस err;
पूर्ण

अटल s32 sdio_ग_लिखो8(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr, u8 val)
अणु
	u32 ftaddr;
	s32 err;

	ftaddr = _cvrt2ftaddr(addr, शून्य, शून्य);
	sd_ग_लिखो8(पूर्णांकfhdl, ftaddr, val, &err);

	वापस err;
पूर्ण

अटल s32 sdio_ग_लिखो16(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr, u16 val)
अणु
	u32 ftaddr;
	__le16 le_पंचांगp;

	ftaddr = _cvrt2ftaddr(addr, शून्य, शून्य);
	le_पंचांगp = cpu_to_le16(val);
	वापस sd_cmd52_ग_लिखो(पूर्णांकfhdl, ftaddr, 2, (u8 *)&le_पंचांगp);
पूर्ण

अटल s32 sdio_ग_लिखो32(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr, u32 val)
अणु
	काष्ठा adapter *adapter;
	u8 mac_pwr_ctrl_on;
	u8 device_id;
	u16 offset;
	u32 ftaddr;
	u8 shअगरt;
	s32 err;
	__le32 le_पंचांगp;

	adapter = पूर्णांकfhdl->padapter;
	err = 0;

	ftaddr = _cvrt2ftaddr(addr, &device_id, &offset);

	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	अगर (
		((device_id == WLAN_IOREG_DEVICE_ID) && (offset < 0x100)) ||
		(!mac_pwr_ctrl_on) ||
		(adapter_to_pwrctl(adapter)->fw_current_in_ps_mode)
	) अणु
		le_पंचांगp = cpu_to_le32(val);

		वापस sd_cmd52_ग_लिखो(पूर्णांकfhdl, ftaddr, 4, (u8 *)&le_पंचांगp);
	पूर्ण

	/*  4 bytes alignment */
	shअगरt = ftaddr & 0x3;
	अगर (shअगरt == 0) अणु
		sd_ग_लिखो32(पूर्णांकfhdl, ftaddr, val, &err);
	पूर्ण अन्यथा अणु
		le_पंचांगp = cpu_to_le32(val);
		err = sd_cmd52_ग_लिखो(पूर्णांकfhdl, ftaddr, 4, (u8 *)&le_पंचांगp);
	पूर्ण
	वापस err;
पूर्ण

अटल s32 sdio_ग_लिखोN(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr, u32 cnt, u8 *buf)
अणु
	काष्ठा adapter *adapter;
	u8 mac_pwr_ctrl_on;
	u8 device_id;
	u16 offset;
	u32 ftaddr;
	u8 shअगरt;
	s32 err;

	adapter = पूर्णांकfhdl->padapter;
	err = 0;

	ftaddr = _cvrt2ftaddr(addr, &device_id, &offset);

	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	अगर (
		((device_id == WLAN_IOREG_DEVICE_ID) && (offset < 0x100)) ||
		(!mac_pwr_ctrl_on) ||
		(adapter_to_pwrctl(adapter)->fw_current_in_ps_mode)
	)
		वापस sd_cmd52_ग_लिखो(पूर्णांकfhdl, ftaddr, cnt, buf);

	shअगरt = ftaddr & 0x3;
	अगर (shअगरt == 0) अणु
		err = sd_ग_लिखो(पूर्णांकfhdl, ftaddr, cnt, buf);
	पूर्ण अन्यथा अणु
		u8 *पंचांगpbuf;
		u32 n;

		ftaddr &= ~(u16)0x3;
		n = cnt + shअगरt;
		पंचांगpbuf = rtw_दो_स्मृति(n);
		अगर (!पंचांगpbuf)
			वापस -1;
		err = sd_पढ़ो(पूर्णांकfhdl, ftaddr, 4, पंचांगpbuf);
		अगर (err) अणु
			kमुक्त(पंचांगpbuf);
			वापस err;
		पूर्ण
		स_नकल(पंचांगpbuf + shअगरt, buf, cnt);
		err = sd_ग_लिखो(पूर्णांकfhdl, ftaddr, n, पंचांगpbuf);
		kमुक्त(पंचांगpbuf);
	पूर्ण
	वापस err;
पूर्ण

अटल u8 sdio_f0_पढ़ो8(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr)
अणु
	वापस sd_f0_पढ़ो8(पूर्णांकfhdl, addr, शून्य);
पूर्ण

अटल व्योम sdio_पढ़ो_mem(
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl,
	u32 addr,
	u32 cnt,
	u8 *rmem
)
अणु
	s32 err;

	err = sdio_पढ़ोN(पूर्णांकfhdl, addr, cnt, rmem);
	/* TODO: Report error is err not zero */
पूर्ण

अटल व्योम sdio_ग_लिखो_mem(
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl,
	u32 addr,
	u32 cnt,
	u8 *wmem
)
अणु
	sdio_ग_लिखोN(पूर्णांकfhdl, addr, cnt, wmem);
पूर्ण

/*
 * Description:
 *Read from RX FIFO
 *Round पढ़ो size to block size,
 *and make sure data transfer will be करोne in one command.
 *
 * Parameters:
 *पूर्णांकfhdl	a poपूर्णांकer of पूर्णांकf_hdl
 *addr		port ID
 *cnt			size to पढ़ो
 *rmem		address to put data
 *
 * Return:
 *_SUCCESS(1)		Success
 *_FAIL(0)		Fail
 */
अटल u32 sdio_पढ़ो_port(
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl,
	u32 addr,
	u32 cnt,
	u8 *mem
)
अणु
	काष्ठा adapter *adapter;
	काष्ठा sdio_data *psdio;
	काष्ठा hal_com_data *hal;
	s32 err;

	adapter = पूर्णांकfhdl->padapter;
	psdio = &adapter_to_dvobj(adapter)->पूर्णांकf_data;
	hal = GET_HAL_DATA(adapter);

	hal_sdio_get_cmd_addr_8723b(adapter, addr, hal->SdioRxFIFOCnt++, &addr);

	अगर (cnt > psdio->block_transfer_len)
		cnt = _RND(cnt, psdio->block_transfer_len);

	err = _sd_पढ़ो(पूर्णांकfhdl, addr, cnt, mem);

	अगर (err)
		वापस _FAIL;
	वापस _SUCCESS;
पूर्ण

/*
 * Description:
 *Write to TX FIFO
 *Align ग_लिखो size block size,
 *and make sure data could be written in one command.
 *
 * Parameters:
 *पूर्णांकfhdl	a poपूर्णांकer of पूर्णांकf_hdl
 *addr		port ID
 *cnt			size to ग_लिखो
 *wmem		data poपूर्णांकer to ग_लिखो
 *
 * Return:
 *_SUCCESS(1)		Success
 *_FAIL(0)		Fail
 */
अटल u32 sdio_ग_लिखो_port(
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl,
	u32 addr,
	u32 cnt,
	u8 *mem
)
अणु
	काष्ठा adapter *adapter;
	काष्ठा sdio_data *psdio;
	s32 err;
	काष्ठा xmit_buf *xmitbuf = (काष्ठा xmit_buf *)mem;

	adapter = पूर्णांकfhdl->padapter;
	psdio = &adapter_to_dvobj(adapter)->पूर्णांकf_data;

	अगर (!adapter->hw_init_completed)
		वापस _FAIL;

	cnt = round_up(cnt, 4);
	hal_sdio_get_cmd_addr_8723b(adapter, addr, cnt >> 2, &addr);

	अगर (cnt > psdio->block_transfer_len)
		cnt = _RND(cnt, psdio->block_transfer_len);

	err = sd_ग_लिखो(पूर्णांकfhdl, addr, cnt, xmitbuf->pdata);

	rtw_sctx_करोne_err(
		&xmitbuf->sctx,
		err ? RTW_SCTX_DONE_WRITE_PORT_ERR : RTW_SCTX_DONE_SUCCESS
	);

	अगर (err)
		वापस _FAIL;
	वापस _SUCCESS;
पूर्ण

व्योम sdio_set_पूर्णांकf_ops(काष्ठा adapter *adapter, काष्ठा _io_ops *ops)
अणु
	ops->_पढ़ो8 = &sdio_पढ़ो8;
	ops->_पढ़ो16 = &sdio_पढ़ो16;
	ops->_पढ़ो32 = &sdio_पढ़ो32;
	ops->_पढ़ो_mem = &sdio_पढ़ो_mem;
	ops->_पढ़ो_port = &sdio_पढ़ो_port;

	ops->_ग_लिखो8 = &sdio_ग_लिखो8;
	ops->_ग_लिखो16 = &sdio_ग_लिखो16;
	ops->_ग_लिखो32 = &sdio_ग_लिखो32;
	ops->_ग_लिखोN = &sdio_ग_लिखोN;
	ops->_ग_लिखो_mem = &sdio_ग_लिखो_mem;
	ops->_ग_लिखो_port = &sdio_ग_लिखो_port;

	ops->_sd_f0_पढ़ो8 = sdio_f0_पढ़ो8;
पूर्ण

/*
 * Toकरो: align address to 4 bytes.
 */
अटल s32 _sdio_local_पढ़ो(
	काष्ठा adapter *adapter,
	u32 addr,
	u32 cnt,
	u8 *buf
)
अणु
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl;
	u8 mac_pwr_ctrl_on;
	s32 err;
	u8 *पंचांगpbuf;
	u32 n;

	पूर्णांकfhdl = &adapter->iopriv.पूर्णांकf;

	hal_sdio_get_cmd_addr_8723b(adapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);

	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	अगर (!mac_pwr_ctrl_on)
		वापस _sd_cmd52_पढ़ो(पूर्णांकfhdl, addr, cnt, buf);

	n = round_up(cnt, 4);
	पंचांगpbuf = rtw_दो_स्मृति(n);
	अगर (!पंचांगpbuf)
		वापस -1;

	err = _sd_पढ़ो(पूर्णांकfhdl, addr, n, पंचांगpbuf);
	अगर (!err)
		स_नकल(buf, पंचांगpbuf, cnt);

	kमुक्त(पंचांगpbuf);

	वापस err;
पूर्ण

/*
 * Toकरो: align address to 4 bytes.
 */
s32 sdio_local_पढ़ो(
	काष्ठा adapter *adapter,
	u32 addr,
	u32 cnt,
	u8 *buf
)
अणु
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl;
	u8 mac_pwr_ctrl_on;
	s32 err;
	u8 *पंचांगpbuf;
	u32 n;

	पूर्णांकfhdl = &adapter->iopriv.पूर्णांकf;

	hal_sdio_get_cmd_addr_8723b(adapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);

	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	अगर (
		(!mac_pwr_ctrl_on) ||
		(adapter_to_pwrctl(adapter)->fw_current_in_ps_mode)
	)
		वापस sd_cmd52_पढ़ो(पूर्णांकfhdl, addr, cnt, buf);

	n = round_up(cnt, 4);
	पंचांगpbuf = rtw_दो_स्मृति(n);
	अगर (!पंचांगpbuf)
		वापस -1;

	err = sd_पढ़ो(पूर्णांकfhdl, addr, n, पंचांगpbuf);
	अगर (!err)
		स_नकल(buf, पंचांगpbuf, cnt);

	kमुक्त(पंचांगpbuf);

	वापस err;
पूर्ण

/*
 * Toकरो: align address to 4 bytes.
 */
s32 sdio_local_ग_लिखो(
	काष्ठा adapter *adapter,
	u32 addr,
	u32 cnt,
	u8 *buf
)
अणु
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl;
	u8 mac_pwr_ctrl_on;
	s32 err;
	u8 *पंचांगpbuf;

	पूर्णांकfhdl = &adapter->iopriv.पूर्णांकf;

	hal_sdio_get_cmd_addr_8723b(adapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);

	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	अगर (
		(!mac_pwr_ctrl_on) ||
		(adapter_to_pwrctl(adapter)->fw_current_in_ps_mode)
	)
		वापस sd_cmd52_ग_लिखो(पूर्णांकfhdl, addr, cnt, buf);

	पंचांगpbuf = rtw_दो_स्मृति(cnt);
	अगर (!पंचांगpbuf)
		वापस -1;

	स_नकल(पंचांगpbuf, buf, cnt);

	err = sd_ग_लिखो(पूर्णांकfhdl, addr, cnt, पंचांगpbuf);

	kमुक्त(पंचांगpbuf);

	वापस err;
पूर्ण

u8 SdioLocalCmd52Read1Byte(काष्ठा adapter *adapter, u32 addr)
अणु
	u8 val = 0;
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl = &adapter->iopriv.पूर्णांकf;

	hal_sdio_get_cmd_addr_8723b(adapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	sd_cmd52_पढ़ो(पूर्णांकfhdl, addr, 1, &val);

	वापस val;
पूर्ण

अटल u16 sdio_local_cmd52_पढ़ो2byte(काष्ठा adapter *adapter, u32 addr)
अणु
	__le16 val = 0;
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl = &adapter->iopriv.पूर्णांकf;

	hal_sdio_get_cmd_addr_8723b(adapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	sd_cmd52_पढ़ो(पूर्णांकfhdl, addr, 2, (u8 *)&val);

	वापस le16_to_cpu(val);
पूर्ण

अटल u32 sdio_local_cmd53_पढ़ो4byte(काष्ठा adapter *adapter, u32 addr)
अणु

	u8 mac_pwr_ctrl_on;
	u32 val = 0;
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl = &adapter->iopriv.पूर्णांकf;
	__le32 le_पंचांगp;

	hal_sdio_get_cmd_addr_8723b(adapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	rtw_hal_get_hwreg(adapter, HW_VAR_APFM_ON_MAC, &mac_pwr_ctrl_on);
	अगर (!mac_pwr_ctrl_on || adapter_to_pwrctl(adapter)->fw_current_in_ps_mode) अणु
		sd_cmd52_पढ़ो(पूर्णांकfhdl, addr, 4, (u8 *)&le_पंचांगp);
		val = le32_to_cpu(le_पंचांगp);
	पूर्ण अन्यथा अणु
		val = sd_पढ़ो32(पूर्णांकfhdl, addr, शून्य);
	पूर्ण
	वापस val;
पूर्ण

व्योम SdioLocalCmd52Write1Byte(काष्ठा adapter *adapter, u32 addr, u8 v)
अणु
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl = &adapter->iopriv.पूर्णांकf;

	hal_sdio_get_cmd_addr_8723b(adapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	sd_cmd52_ग_लिखो(पूर्णांकfhdl, addr, 1, &v);
पूर्ण

अटल व्योम sdio_local_cmd52_ग_लिखो4byte(काष्ठा adapter *adapter, u32 addr, u32 v)
अणु
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl = &adapter->iopriv.पूर्णांकf;
	__le32 le_पंचांगp;

	hal_sdio_get_cmd_addr_8723b(adapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);
	le_पंचांगp = cpu_to_le32(v);
	sd_cmd52_ग_लिखो(पूर्णांकfhdl, addr, 4, (u8 *)&le_पंचांगp);
पूर्ण

अटल s32 पढ़ो_पूर्णांकerrupt_8723b_sdio(काष्ठा adapter *adapter, u32 *phisr)
अणु
	u32 hisr, himr;
	u8 val8, hisr_len;

	अगर (!phisr)
		वापस false;

	himr = GET_HAL_DATA(adapter)->sdio_himr;

	/*  decide how many bytes need to be पढ़ो */
	hisr_len = 0;
	जबतक (himr) अणु
		hisr_len++;
		himr >>= 8;
	पूर्ण

	hisr = 0;
	जबतक (hisr_len != 0) अणु
		hisr_len--;
		val8 = SdioLocalCmd52Read1Byte(adapter, SDIO_REG_HISR + hisr_len);
		hisr |= (val8 << (8 * hisr_len));
	पूर्ण

	*phisr = hisr;

	वापस true;
पूर्ण

/*  */
/*	Description: */
/*		Initialize SDIO Host Interrupt Mask configuration variables क्रम future use. */
/*  */
/*	Assumption: */
/*		Using SDIO Local रेजिस्टर ONLY क्रम configuration. */
/*  */
/*	Created by Roger, 2011.02.11. */
/*  */
व्योम InitInterrupt8723BSdio(काष्ठा adapter *adapter)
अणु
	काष्ठा hal_com_data *haldata;

	haldata = GET_HAL_DATA(adapter);
	haldata->sdio_himr = (u32)(SDIO_HIMR_RX_REQUEST_MSK	|
				   SDIO_HIMR_AVAL_MSK		|
				   0);
पूर्ण

/*  */
/*	Description: */
/*		Initialize System Host Interrupt Mask configuration variables क्रम future use. */
/*  */
/*	Created by Roger, 2011.08.03. */
/*  */
व्योम InitSysInterrupt8723BSdio(काष्ठा adapter *adapter)
अणु
	काष्ठा hal_com_data *haldata;

	haldata = GET_HAL_DATA(adapter);

	haldata->SysIntrMask = (0);
पूर्ण

/*  */
/*	Description: */
/*		Enalbe SDIO Host Interrupt Mask configuration on SDIO local करोमुख्य. */
/*  */
/*	Assumption: */
/*		1. Using SDIO Local रेजिस्टर ONLY क्रम configuration. */
/*		2. PASSIVE LEVEL */
/*  */
/*	Created by Roger, 2011.02.11. */
/*  */
व्योम EnableInterrupt8723BSdio(काष्ठा adapter *adapter)
अणु
	काष्ठा hal_com_data *haldata;
	__le32 himr;
	u32 पंचांगp;

	haldata = GET_HAL_DATA(adapter);

	himr = cpu_to_le32(haldata->sdio_himr);
	sdio_local_ग_लिखो(adapter, SDIO_REG_HIMR, 4, (u8 *)&himr);

	/*  Update current प्रणाली IMR settings */
	पंचांगp = rtw_पढ़ो32(adapter, REG_HSIMR);
	rtw_ग_लिखो32(adapter, REG_HSIMR, पंचांगp | haldata->SysIntrMask);

	/*  */
	/*  <Roger_Notes> There are some C2H CMDs have been sent beक्रमe प्रणाली पूर्णांकerrupt is enabled, e.g., C2H, CPWM. */
	/*  So we need to clear all C2H events that FW has notअगरied, otherwise FW won't schedule any commands anymore. */
	/*  2011.10.19. */
	/*  */
	rtw_ग_लिखो8(adapter, REG_C2HEVT_CLEAR, C2H_EVT_HOST_CLOSE);
पूर्ण

/*  */
/*	Description: */
/*		Disable SDIO Host IMR configuration to mask unnecessary पूर्णांकerrupt service. */
/*  */
/*	Assumption: */
/*		Using SDIO Local रेजिस्टर ONLY क्रम configuration. */
/*  */
/*	Created by Roger, 2011.02.11. */
/*  */
व्योम DisableInterrupt8723BSdio(काष्ठा adapter *adapter)
अणु
	__le32 himr;

	himr = cpu_to_le32(SDIO_HIMR_DISABLED);
	sdio_local_ग_लिखो(adapter, SDIO_REG_HIMR, 4, (u8 *)&himr);
पूर्ण

/*  */
/*	Description: */
/*		Using 0x100 to check the घातer status of FW. */
/*  */
/*	Assumption: */
/*		Using SDIO Local रेजिस्टर ONLY क्रम configuration. */
/*  */
/*	Created by Isaac, 2013.09.10. */
/*  */
u8 CheckIPSStatus(काष्ठा adapter *adapter)
अणु
	अगर (rtw_पढ़ो8(adapter, 0x100) == 0xEA)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल काष्ठा recv_buf *sd_recv_rxfअगरo(काष्ठा adapter *adapter, u32 size)
अणु
	u32 पढ़ोsize, ret;
	u8 *पढ़ोbuf;
	काष्ठा recv_priv *recv_priv;
	काष्ठा recv_buf	*recvbuf;

	/*  Patch क्रम some SDIO Host 4 bytes issue */
	/*  ex. RK3188 */
	पढ़ोsize = round_up(size, 4);

	/* 3 1. alloc recvbuf */
	recv_priv = &adapter->recvpriv;
	recvbuf = rtw_dequeue_recvbuf(&recv_priv->मुक्त_recv_buf_queue);
	अगर (!recvbuf) अणु
		netdev_err(adapter->pnetdev, "%s: alloc recvbuf FAIL!\n",
			   __func__);
		वापस शून्य;
	पूर्ण

	/* 3 2. alloc skb */
	अगर (!recvbuf->pskb) अणु
		SIZE_PTR पंचांगpaddr = 0;
		SIZE_PTR alignment = 0;

		recvbuf->pskb = rtw_skb_alloc(MAX_RECVBUF_SZ + RECVBUFF_ALIGN_SZ);

		अगर (recvbuf->pskb) अणु
			recvbuf->pskb->dev = adapter->pnetdev;

			पंचांगpaddr = (SIZE_PTR)recvbuf->pskb->data;
			alignment = पंचांगpaddr & (RECVBUFF_ALIGN_SZ - 1);
			skb_reserve(recvbuf->pskb, (RECVBUFF_ALIGN_SZ - alignment));
		पूर्ण

		अगर (!recvbuf->pskb)
			वापस शून्य;
	पूर्ण

	/* 3 3. पढ़ो data from rxfअगरo */
	पढ़ोbuf = recvbuf->pskb->data;
	ret = sdio_पढ़ो_port(&adapter->iopriv.पूर्णांकf, WLAN_RX0FF_DEVICE_ID, पढ़ोsize, पढ़ोbuf);
	अगर (ret == _FAIL)
		वापस शून्य;

	/* 3 4. init recvbuf */
	recvbuf->len = size;
	recvbuf->phead = recvbuf->pskb->head;
	recvbuf->pdata = recvbuf->pskb->data;
	skb_set_tail_poपूर्णांकer(recvbuf->pskb, size);
	recvbuf->ptail = skb_tail_poपूर्णांकer(recvbuf->pskb);
	recvbuf->pend = skb_end_poपूर्णांकer(recvbuf->pskb);

	वापस recvbuf;
पूर्ण

अटल व्योम sd_rxhandler(काष्ठा adapter *adapter, काष्ठा recv_buf *recvbuf)
अणु
	काष्ठा recv_priv *recv_priv;
	काष्ठा __queue *pending_queue;

	recv_priv = &adapter->recvpriv;
	pending_queue = &recv_priv->recv_buf_pending_queue;

	/* 3 1. enqueue recvbuf */
	rtw_enqueue_recvbuf(recvbuf, pending_queue);

	/* 3 2. schedule tasklet */
	tasklet_schedule(&recv_priv->recv_tasklet);
पूर्ण

व्योम sd_पूर्णांक_dpc(काष्ठा adapter *adapter)
अणु
	काष्ठा hal_com_data *hal;
	काष्ठा dvobj_priv *dvobj;
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl = &adapter->iopriv.पूर्णांकf;
	काष्ठा pwrctrl_priv *pwrctl;

	hal = GET_HAL_DATA(adapter);
	dvobj = adapter_to_dvobj(adapter);
	pwrctl = dvobj_to_pwrctl(dvobj);

	अगर (hal->sdio_hisr & SDIO_HISR_AVAL) अणु
		u8 मुक्तpage[4];

		_sdio_local_पढ़ो(adapter, SDIO_REG_FREE_TXPG, 4, मुक्तpage);
		complete(&(adapter->xmitpriv.xmit_comp));
	पूर्ण

	अगर (hal->sdio_hisr & SDIO_HISR_CPWM1) अणु
		del_समयr_sync(&(pwrctl->pwr_rpwm_समयr));

		SdioLocalCmd52Read1Byte(adapter, SDIO_REG_HCPWM1_8723B);

		_set_workitem(&(pwrctl->cpwm_event));
	पूर्ण

	अगर (hal->sdio_hisr & SDIO_HISR_TXERR) अणु
		u8 *status;
		u32 addr;

		status = rtw_दो_स्मृति(4);
		अगर (status) अणु
			addr = REG_TXDMA_STATUS;
			hal_sdio_get_cmd_addr_8723b(adapter, WLAN_IOREG_DEVICE_ID, addr, &addr);
			_sd_पढ़ो(पूर्णांकfhdl, addr, 4, status);
			_sd_ग_लिखो(पूर्णांकfhdl, addr, 4, status);
			kमुक्त(status);
		पूर्ण
	पूर्ण

	अगर (hal->sdio_hisr & SDIO_HISR_C2HCMD) अणु
		काष्ठा c2h_evt_hdr_88xx *c2h_evt;

		c2h_evt = rtw_zदो_स्मृति(16);
		अगर (c2h_evt) अणु
			अगर (c2h_evt_पढ़ो_88xx(adapter, (u8 *)c2h_evt) == _SUCCESS) अणु
				अगर (c2h_id_filter_ccx_8723b((u8 *)c2h_evt)) अणु
					/* Handle CCX report here */
					rtw_hal_c2h_handler(adapter, (u8 *)c2h_evt);
					kमुक्त(c2h_evt);
				पूर्ण अन्यथा अणु
					rtw_c2h_wk_cmd(adapter, (u8 *)c2h_evt);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Error handling क्रम दो_स्मृति fail */
			rtw_cbuf_push(adapter->evtpriv.c2h_queue, शून्य);
			_set_workitem(&adapter->evtpriv.c2h_wk);
		पूर्ण
	पूर्ण

	अगर (hal->sdio_hisr & SDIO_HISR_RX_REQUEST) अणु
		काष्ठा recv_buf *recvbuf;
		पूर्णांक alloc_fail_समय = 0;
		u32 hisr;

		hal->sdio_hisr ^= SDIO_HISR_RX_REQUEST;
		करो अणु
			hal->SdioRxFIFOSize = sdio_local_cmd52_पढ़ो2byte(adapter, SDIO_REG_RX0_REQ_LEN);
			अगर (hal->SdioRxFIFOSize != 0) अणु
				recvbuf = sd_recv_rxfअगरo(adapter, hal->SdioRxFIFOSize);
				अगर (recvbuf)
					sd_rxhandler(adapter, recvbuf);
				अन्यथा अणु
					alloc_fail_समय++;
					अगर (alloc_fail_समय >= 10)
						अवरोध;
				पूर्ण
				hal->SdioRxFIFOSize = 0;
			पूर्ण अन्यथा
				अवरोध;

			hisr = 0;
			पढ़ो_पूर्णांकerrupt_8723b_sdio(adapter, &hisr);
			hisr &= SDIO_HISR_RX_REQUEST;
			अगर (!hisr)
				अवरोध;
		पूर्ण जबतक (1);
	पूर्ण
पूर्ण

व्योम sd_पूर्णांक_hdl(काष्ठा adapter *adapter)
अणु
	काष्ठा hal_com_data *hal;

	अगर (
		(adapter->bDriverStopped) || (adapter->bSurpriseRemoved)
	)
		वापस;

	hal = GET_HAL_DATA(adapter);

	hal->sdio_hisr = 0;
	पढ़ो_पूर्णांकerrupt_8723b_sdio(adapter, &hal->sdio_hisr);

	अगर (hal->sdio_hisr & hal->sdio_himr) अणु
		u32 v32;

		hal->sdio_hisr &= hal->sdio_himr;

		/*  clear HISR */
		v32 = hal->sdio_hisr & MASK_SDIO_HISR_CLEAR;
		अगर (v32)
			sdio_local_cmd52_ग_लिखो4byte(adapter, SDIO_REG_HISR, v32);

		sd_पूर्णांक_dpc(adapter);
	पूर्ण
पूर्ण

/*  */
/*	Description: */
/*		Query SDIO Local रेजिस्टर to query current the number of Free TxPacketBuffer page. */
/*  */
/*	Assumption: */
/*		1. Running at PASSIVE_LEVEL */
/*		2. RT_TX_SPINLOCK is NOT acquired. */
/*  */
/*	Created by Roger, 2011.01.28. */
/*  */
u8 HalQueryTxBufferStatus8723BSdio(काष्ठा adapter *adapter)
अणु
	काष्ठा hal_com_data *hal;
	u32 numof_मुक्त_page;

	hal = GET_HAL_DATA(adapter);

	numof_मुक्त_page = sdio_local_cmd53_पढ़ो4byte(adapter, SDIO_REG_FREE_TXPG);

	स_नकल(hal->SdioTxFIFOFreePage, &numof_मुक्त_page, 4);

	वापस true;
पूर्ण

/*  */
/*	Description: */
/*		Query SDIO Local रेजिस्टर to get the current number of TX OQT Free Space. */
/*  */
व्योम HalQueryTxOQTBufferStatus8723BSdio(काष्ठा adapter *adapter)
अणु
	काष्ठा hal_com_data *haldata = GET_HAL_DATA(adapter);

	haldata->SdioTxOQTFreeSpace = SdioLocalCmd52Read1Byte(adapter, SDIO_REG_OQT_FREE_PG);
पूर्ण


