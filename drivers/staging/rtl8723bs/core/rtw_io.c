<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
/*

The purpose of rtw_io.c

a. provides the API

b. provides the protocol engine

c. provides the software पूर्णांकerface between caller and the hardware पूर्णांकerface


Compiler Flag Option:

1. CONFIG_SDIO_HCI:
    a. USE_SYNC_IRP:  Only sync operations are provided.
    b. USE_ASYNC_IRP:Both sync/async operations are provided.

jackson@realtek.com.tw

*/

#घोषणा _RTW_IO_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>

#घोषणा rtw_le16_to_cpu(val)		val
#घोषणा rtw_le32_to_cpu(val)		val
#घोषणा rtw_cpu_to_le16(val)		val
#घोषणा rtw_cpu_to_le32(val)		val

u8 _rtw_पढ़ो8(काष्ठा adapter *adapter, u32 addr)
अणु
	/* काष्ठा	io_queue	*pio_queue = (काष्ठा io_queue *)adapter->pio_queue; */
	काष्ठा io_priv *pio_priv = &adapter->iopriv;
	काष्ठा	पूर्णांकf_hdl		*pपूर्णांकfhdl = &(pio_priv->पूर्णांकf);
	u8 (*_पढ़ो8)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);

	_पढ़ो8 = pपूर्णांकfhdl->io_ops._पढ़ो8;

	वापस _पढ़ो8(pपूर्णांकfhdl, addr);
पूर्ण

u16 _rtw_पढ़ो16(काष्ठा adapter *adapter, u32 addr)
अणु
	u16 r_val;
	/* काष्ठा	io_queue	*pio_queue = (काष्ठा io_queue *)adapter->pio_queue; */
	काष्ठा io_priv *pio_priv = &adapter->iopriv;
	काष्ठा	पूर्णांकf_hdl		*pपूर्णांकfhdl = &(pio_priv->पूर्णांकf);
	u16 (*_पढ़ो16)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);

	_पढ़ो16 = pपूर्णांकfhdl->io_ops._पढ़ो16;

	r_val = _पढ़ो16(pपूर्णांकfhdl, addr);
	वापस rtw_le16_to_cpu(r_val);
पूर्ण

u32 _rtw_पढ़ो32(काष्ठा adapter *adapter, u32 addr)
अणु
	u32 r_val;
	/* काष्ठा	io_queue	*pio_queue = (काष्ठा io_queue *)adapter->pio_queue; */
	काष्ठा io_priv *pio_priv = &adapter->iopriv;
	काष्ठा	पूर्णांकf_hdl		*pपूर्णांकfhdl = &(pio_priv->पूर्णांकf);
	u32 (*_पढ़ो32)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);

	_पढ़ो32 = pपूर्णांकfhdl->io_ops._पढ़ो32;

	r_val = _पढ़ो32(pपूर्णांकfhdl, addr);
	वापस rtw_le32_to_cpu(r_val);

पूर्ण

पूर्णांक _rtw_ग_लिखो8(काष्ठा adapter *adapter, u32 addr, u8 val)
अणु
	/* काष्ठा	io_queue	*pio_queue = (काष्ठा io_queue *)adapter->pio_queue; */
	काष्ठा io_priv *pio_priv = &adapter->iopriv;
	काष्ठा	पूर्णांकf_hdl		*pपूर्णांकfhdl = &(pio_priv->पूर्णांकf);
	पूर्णांक (*_ग_लिखो8)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u8 val);
	पूर्णांक ret;

	_ग_लिखो8 = pपूर्णांकfhdl->io_ops._ग_लिखो8;

	ret = _ग_लिखो8(pपूर्णांकfhdl, addr, val);

	वापस RTW_STATUS_CODE(ret);
पूर्ण
पूर्णांक _rtw_ग_लिखो16(काष्ठा adapter *adapter, u32 addr, u16 val)
अणु
	/* काष्ठा	io_queue	*pio_queue = (काष्ठा io_queue *)adapter->pio_queue; */
	काष्ठा io_priv *pio_priv = &adapter->iopriv;
	काष्ठा	पूर्णांकf_hdl		*pपूर्णांकfhdl = &(pio_priv->पूर्णांकf);
	पूर्णांक (*_ग_लिखो16)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u16 val);
	पूर्णांक ret;

	_ग_लिखो16 = pपूर्णांकfhdl->io_ops._ग_लिखो16;

	ret = _ग_लिखो16(pपूर्णांकfhdl, addr, val);
	वापस RTW_STATUS_CODE(ret);
पूर्ण
पूर्णांक _rtw_ग_लिखो32(काष्ठा adapter *adapter, u32 addr, u32 val)
अणु
	/* काष्ठा	io_queue	*pio_queue = (काष्ठा io_queue *)adapter->pio_queue; */
	काष्ठा io_priv *pio_priv = &adapter->iopriv;
	काष्ठा	पूर्णांकf_hdl		*pपूर्णांकfhdl = &(pio_priv->पूर्णांकf);
	पूर्णांक (*_ग_लिखो32)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 val);
	पूर्णांक ret;

	_ग_लिखो32 = pपूर्णांकfhdl->io_ops._ग_लिखो32;

	ret = _ग_लिखो32(pपूर्णांकfhdl, addr, val);

	वापस RTW_STATUS_CODE(ret);
पूर्ण

u8 _rtw_sd_f0_पढ़ो8(काष्ठा adapter *adapter, u32 addr)
अणु
	u8 r_val = 0x00;
	काष्ठा io_priv *pio_priv = &adapter->iopriv;
	काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl = &(pio_priv->पूर्णांकf);
	u8 (*_sd_f0_पढ़ो8)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);

	_sd_f0_पढ़ो8 = pपूर्णांकfhdl->io_ops._sd_f0_पढ़ो8;

	अगर (_sd_f0_पढ़ो8)
		r_val = _sd_f0_पढ़ो8(pपूर्णांकfhdl, addr);
	अन्यथा
		netdev_warn(adapter->pnetdev,
			    FUNC_ADPT_FMT " _sd_f0_read8 callback is NULL\n",
			    FUNC_ADPT_ARG(adapter));

	वापस r_val;
पूर्ण

u32 _rtw_ग_लिखो_port(काष्ठा adapter *adapter, u32 addr, u32 cnt, u8 *pmem)
अणु
	u32 (*_ग_लिखो_port)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pmem);
	काष्ठा io_priv *pio_priv = &adapter->iopriv;
	काष्ठा	पूर्णांकf_hdl		*pपूर्णांकfhdl = &(pio_priv->पूर्णांकf);

	_ग_लिखो_port = pपूर्णांकfhdl->io_ops._ग_लिखो_port;

	वापस _ग_लिखो_port(pपूर्णांकfhdl, addr, cnt, pmem);
पूर्ण

पूर्णांक rtw_init_io_priv(काष्ठा adapter *padapter, व्योम (*set_पूर्णांकf_ops)(काष्ठा adapter *padapter, काष्ठा _io_ops *pops))
अणु
	काष्ठा io_priv *piopriv = &padapter->iopriv;
	काष्ठा पूर्णांकf_hdl *pपूर्णांकf = &piopriv->पूर्णांकf;

	अगर (!set_पूर्णांकf_ops)
		वापस _FAIL;

	piopriv->padapter = padapter;
	pपूर्णांकf->padapter = padapter;
	pपूर्णांकf->pपूर्णांकf_dev = adapter_to_dvobj(padapter);

	set_पूर्णांकf_ops(padapter, &pपूर्णांकf->io_ops);

	वापस _SUCCESS;
पूर्ण

/*
* Increase and check अगर the continual_io_error of this @param dvobjprive is larger than MAX_CONTINUAL_IO_ERR
* @वापस true:
* @वापस false:
*/
पूर्णांक rtw_inc_and_chk_continual_io_error(काष्ठा dvobj_priv *dvobj)
अणु
	पूर्णांक ret = false;
	पूर्णांक value = atomic_inc_वापस(&dvobj->continual_io_error);
	अगर (value > MAX_CONTINUAL_IO_ERR)
		ret = true;

	वापस ret;
पूर्ण

/*
* Set the continual_io_error of this @param dvobjprive to 0
*/
व्योम rtw_reset_continual_io_error(काष्ठा dvobj_priv *dvobj)
अणु
	atomic_set(&dvobj->continual_io_error, 0);
पूर्ण
