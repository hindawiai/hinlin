<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_EEPROM_C_

#समावेश <drv_conf.h>
#समावेश <osdep_service.h>
#समावेश <drv_types.h>

व्योम up_clk(_adapter *padapter,	 u16 *x)
अणु
_func_enter_;
	*x = *x | _EESK;
	rtw_ग_लिखो8(padapter, EE_9346CR, (u8)*x);
	udelay(CLOCK_RATE);

_func_निकास_;

पूर्ण

व्योम करोwn_clk(_adapter *padapter, u16 *x)
अणु
_func_enter_;
	*x = *x & ~_EESK;
	rtw_ग_लिखो8(padapter, EE_9346CR, (u8)*x);
	udelay(CLOCK_RATE);
_func_निकास_;
पूर्ण

व्योम shअगरt_out_bits(_adapter *padapter, u16 data, u16 count)
अणु
	u16 x, mask;
_func_enter_;

	अगर (padapter->bSurpriseRemoved)
		जाओ out;

	mask = 0x01 << (count - 1);
	x = rtw_पढ़ो8(padapter, EE_9346CR);

	x &= ~(_EEDO | _EEDI);

	करो अणु
		x &= ~_EEDI;
		अगर (data & mask)
			x |= _EEDI;
		अगर (padapter->bSurpriseRemoved)
			जाओ out;

		rtw_ग_लिखो8(padapter, EE_9346CR, (u8)x);
		udelay(CLOCK_RATE);
		up_clk(padapter, &x);
		करोwn_clk(padapter, &x);
		mask = mask >> 1;
	पूर्ण जबतक (mask);
	अगर (padapter->bSurpriseRemoved)
		जाओ out;

	x &= ~_EEDI;
	rtw_ग_लिखो8(padapter, EE_9346CR, (u8)x);
out:
_func_निकास_;
पूर्ण

u16 shअगरt_in_bits(_adapter *padapter)
अणु
	u16 x, d = 0, i;
_func_enter_;
	अगर (padapter->bSurpriseRemoved)
		जाओ out;

	x = rtw_पढ़ो8(padapter, EE_9346CR);

	x &= ~(_EEDO | _EEDI);
	d = 0;

	क्रम (i = 0; i < 16; i++) अणु
		d = d << 1;
		up_clk(padapter, &x);
	अगर (padapter->bSurpriseRemoved)
		जाओ out;

		x = rtw_पढ़ो8(padapter, EE_9346CR);

		x &= ~(_EEDI);
		अगर (x & _EEDO)
		d |= 1;

		करोwn_clk(padapter, &x);
	पूर्ण
out:
_func_निकास_;

	वापस d;
पूर्ण

व्योम standby(_adapter *padapter)
अणु
	u8   x;
_func_enter_;
	x = rtw_पढ़ो8(padapter, EE_9346CR);

	x &= ~(_EECS | _EESK);
	rtw_ग_लिखो8(padapter, EE_9346CR, x);

	udelay(CLOCK_RATE);
	x |= _EECS;
	rtw_ग_लिखो8(padapter, EE_9346CR, x);
	udelay(CLOCK_RATE);
_func_निकास_;
पूर्ण

व्योम eeprom_clean(_adapter *padapter)
अणु
	u16 x;
_func_enter_;
	अगर (padapter->bSurpriseRemoved)
		जाओ out;

	x = rtw_पढ़ो8(padapter, EE_9346CR);
	अगर (padapter->bSurpriseRemoved)
		जाओ out;

	x &= ~(_EECS | _EEDI);
	rtw_ग_लिखो8(padapter, EE_9346CR, (u8)x);
	अगर (padapter->bSurpriseRemoved)
		जाओ out;

	up_clk(padapter, &x);
	अगर (padapter->bSurpriseRemoved)
		जाओ out;

	करोwn_clk(padapter, &x);
out:
_func_निकास_;
पूर्ण

u16 eeprom_पढ़ो16(_adapter *padapter, u16 reg) /*ReadEEprom*/
अणु

	u16 x;
	u16 data = 0;

_func_enter_;

	अगर (padapter->bSurpriseRemoved)
		जाओ out;

	/* select EEPROM, reset bits, set _EECS*/
	x = rtw_पढ़ो8(padapter, EE_9346CR);

	अगर (padapter->bSurpriseRemoved)
		जाओ out;

	x &= ~(_EEDI | _EEDO | _EESK | _EEM0);
	x |= _EEM1 | _EECS;
	rtw_ग_लिखो8(padapter, EE_9346CR, (अचिन्हित अक्षर)x);

	/* ग_लिखो the पढ़ो opcode and रेजिस्टर number in that order*/
	/* The opcode is 3bits in length, reg is 6 bits दीर्घ*/
	shअगरt_out_bits(padapter, EEPROM_READ_OPCODE, 3);
	shअगरt_out_bits(padapter, reg, padapter->EepromAddressSize);

	/* Now पढ़ो the data (16 bits) in from the selected EEPROM word*/
	data = shअगरt_in_bits(padapter);

	eeprom_clean(padapter);
out:
_func_निकास_;
	वापस data;


पूर्ण

/*addr_off : address offset of the entry in eeprom (not the tuple number of eeprom (reg); that is addr_off !=reg)*/
u8 eeprom_पढ़ो(_adapter *padapter, u32 addr_off, u8 sz, u8 *rbuf)
अणु
	u8 quotient, reमुख्यder, addr_2align_odd;
	u16 reg, sपंचांगp, i = 0, idx = 0;
_func_enter_;
	reg = (u16)(addr_off >> 1);
	addr_2align_odd = (u8)(addr_off & 0x1);

	/*पढ़ो that start at high part: e.g  1,3,5,7,9,...*/
	अगर (addr_2align_odd) अणु
		sपंचांगp = eeprom_पढ़ो16(padapter, reg);
		rbuf[idx++] = (u8) ((sपंचांगp>>8)&0xff); /*वापस hogh-part of the लघु*/
		reg++; sz--;
	पूर्ण

	quotient = sz >> 1;
	reमुख्यder = sz & 0x1;

	क्रम (i = 0; i < quotient; i++) अणु
		sपंचांगp = eeprom_पढ़ो16(padapter, reg+i);
		rbuf[idx++] = (u8) (sपंचांगp&0xff);
		rbuf[idx++] = (u8) ((sपंचांगp>>8)&0xff);
	पूर्ण

	reg = reg+i;
	अगर (reमुख्यder) अणु /*end of पढ़ो at lower part of लघु : 0,2,4,6,...*/
		sपंचांगp = eeprom_पढ़ो16(padapter, reg);
		rbuf[idx] = (u8)(sपंचांगp & 0xff);
	पूर्ण
_func_निकास_;
	वापस true;
पूर्ण
