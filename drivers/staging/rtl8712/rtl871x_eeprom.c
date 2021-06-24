<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_eeprom.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _RTL871X_EEPROM_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

अटल व्योम up_clk(काष्ठा _adapter *padapter, u16 *x)
अणु
	*x = *x | _EESK;
	r8712_ग_लिखो8(padapter, EE_9346CR, (u8)*x);
	udelay(CLOCK_RATE);
पूर्ण

अटल व्योम करोwn_clk(काष्ठा _adapter *padapter, u16 *x)
अणु
	*x = *x & ~_EESK;
	r8712_ग_लिखो8(padapter, EE_9346CR, (u8)*x);
	udelay(CLOCK_RATE);
पूर्ण

अटल व्योम shअगरt_out_bits(काष्ठा _adapter *padapter, u16 data, u16 count)
अणु
	u16 x, mask;

	अगर (padapter->surprise_हटाओd)
		जाओ out;
	mask = 0x01 << (count - 1);
	x = r8712_पढ़ो8(padapter, EE_9346CR);
	x &= ~(_EEDO | _EEDI);
	करो अणु
		x &= ~_EEDI;
		अगर (data & mask)
			x |= _EEDI;
		अगर (padapter->surprise_हटाओd)
			जाओ out;
		r8712_ग_लिखो8(padapter, EE_9346CR, (u8)x);
		udelay(CLOCK_RATE);
		up_clk(padapter, &x);
		करोwn_clk(padapter, &x);
		mask >>= 1;
	पूर्ण जबतक (mask);
	अगर (padapter->surprise_हटाओd)
		जाओ out;
	x &= ~_EEDI;
	r8712_ग_लिखो8(padapter, EE_9346CR, (u8)x);
out:;
पूर्ण

अटल u16 shअगरt_in_bits(काष्ठा _adapter *padapter)
अणु
	u16 x, d = 0, i;

	अगर (padapter->surprise_हटाओd)
		जाओ out;
	x = r8712_पढ़ो8(padapter, EE_9346CR);
	x &= ~(_EEDO | _EEDI);
	d = 0;
	क्रम (i = 0; i < 16; i++) अणु
		d <<= 1;
		up_clk(padapter, &x);
		अगर (padapter->surprise_हटाओd)
			जाओ out;
		x = r8712_पढ़ो8(padapter, EE_9346CR);
		x &= ~(_EEDI);
		अगर (x & _EEDO)
			d |= 1;
		करोwn_clk(padapter, &x);
	पूर्ण
out:
	वापस d;
पूर्ण

अटल व्योम standby(काष्ठा _adapter *padapter)
अणु
	u8   x;

	x = r8712_पढ़ो8(padapter, EE_9346CR);
	x &= ~(_EECS | _EESK);
	r8712_ग_लिखो8(padapter, EE_9346CR, x);
	udelay(CLOCK_RATE);
	x |= _EECS;
	r8712_ग_लिखो8(padapter, EE_9346CR, x);
	udelay(CLOCK_RATE);
पूर्ण

अटल u16 रुको_eeprom_cmd_करोne(काष्ठा _adapter *padapter)
अणु
	u8	x;
	u16	i;

	standby(padapter);
	क्रम (i = 0; i < 200; i++) अणु
		x = r8712_पढ़ो8(padapter, EE_9346CR);
		अगर (x & _EEDO)
			वापस true;
		udelay(CLOCK_RATE);
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम eeprom_clean(काष्ठा _adapter *padapter)
अणु
	u16 x;

	अगर (padapter->surprise_हटाओd)
		वापस;
	x = r8712_पढ़ो8(padapter, EE_9346CR);
	अगर (padapter->surprise_हटाओd)
		वापस;
	x &= ~(_EECS | _EEDI);
	r8712_ग_लिखो8(padapter, EE_9346CR, (u8)x);
	अगर (padapter->surprise_हटाओd)
		वापस;
	up_clk(padapter, &x);
	अगर (padapter->surprise_हटाओd)
		वापस;
	करोwn_clk(padapter, &x);
पूर्ण

व्योम r8712_eeprom_ग_लिखो16(काष्ठा _adapter *padapter, u16 reg, u16 data)
अणु
	u8 x;
	u8 पंचांगp8_ori, पंचांगp8_new, पंचांगp8_clk_ori, पंचांगp8_clk_new;

	पंचांगp8_ori = r8712_पढ़ो8(padapter, 0x102502f1);
	पंचांगp8_new = पंचांगp8_ori & 0xf7;
	अगर (पंचांगp8_ori != पंचांगp8_new)
		r8712_ग_लिखो8(padapter, 0x102502f1, पंचांगp8_new);
	पंचांगp8_clk_ori = r8712_पढ़ो8(padapter, 0x10250003);
	पंचांगp8_clk_new = पंचांगp8_clk_ori | 0x20;
	अगर (पंचांगp8_clk_new != पंचांगp8_clk_ori)
		r8712_ग_लिखो8(padapter, 0x10250003, पंचांगp8_clk_new);
	x = r8712_पढ़ो8(padapter, EE_9346CR);
	x &= ~(_EEDI | _EEDO | _EESK | _EEM0);
	x |= _EEM1 | _EECS;
	r8712_ग_लिखो8(padapter, EE_9346CR, x);
	shअगरt_out_bits(padapter, EEPROM_EWEN_OPCODE, 5);
	अगर (padapter->eeprom_address_size == 8)	/*CF+ and SDIO*/
		shअगरt_out_bits(padapter, 0, 6);
	अन्यथा	/* USB */
		shअगरt_out_bits(padapter, 0, 4);
	standby(padapter);
	/* Erase this particular word.  Write the erase opcode and रेजिस्टर
	 * number in that order. The opcode is 3bits in length; reg is 6
	 * bits दीर्घ.
	 */
	standby(padapter);
	/* ग_लिखो the new word to the EEPROM
	 * send the ग_लिखो opcode the EEPORM
	 */
	shअगरt_out_bits(padapter, EEPROM_WRITE_OPCODE, 3);
	/* select which word in the EEPROM that we are writing to. */
	shअगरt_out_bits(padapter, reg, padapter->eeprom_address_size);
	/* ग_लिखो the data to the selected EEPROM word. */
	shअगरt_out_bits(padapter, data, 16);
	अगर (रुको_eeprom_cmd_करोne(padapter)) अणु
		standby(padapter);
		shअगरt_out_bits(padapter, EEPROM_EWDS_OPCODE, 5);
		shअगरt_out_bits(padapter, reg, 4);
		eeprom_clean(padapter);
	पूर्ण
	अगर (पंचांगp8_clk_new != पंचांगp8_clk_ori)
		r8712_ग_लिखो8(padapter, 0x10250003, पंचांगp8_clk_ori);
	अगर (पंचांगp8_new != पंचांगp8_ori)
		r8712_ग_लिखो8(padapter, 0x102502f1, पंचांगp8_ori);
पूर्ण

u16 r8712_eeprom_पढ़ो16(काष्ठा _adapter *padapter, u16 reg) /*ReadEEprom*/
अणु
	u16 x;
	u16 data = 0;
	u8 पंचांगp8_ori, पंचांगp8_new, पंचांगp8_clk_ori, पंचांगp8_clk_new;

	पंचांगp8_ori = r8712_पढ़ो8(padapter, 0x102502f1);
	पंचांगp8_new = पंचांगp8_ori & 0xf7;
	अगर (पंचांगp8_ori != पंचांगp8_new)
		r8712_ग_लिखो8(padapter, 0x102502f1, पंचांगp8_new);
	पंचांगp8_clk_ori = r8712_पढ़ो8(padapter, 0x10250003);
	पंचांगp8_clk_new = पंचांगp8_clk_ori | 0x20;
	अगर (पंचांगp8_clk_new != पंचांगp8_clk_ori)
		r8712_ग_लिखो8(padapter, 0x10250003, पंचांगp8_clk_new);
	अगर (padapter->surprise_हटाओd)
		जाओ out;
	/* select EEPROM, reset bits, set _EECS */
	x = r8712_पढ़ो8(padapter, EE_9346CR);
	अगर (padapter->surprise_हटाओd)
		जाओ out;
	x &= ~(_EEDI | _EEDO | _EESK | _EEM0);
	x |= _EEM1 | _EECS;
	r8712_ग_लिखो8(padapter, EE_9346CR, (अचिन्हित अक्षर)x);
	/* ग_लिखो the पढ़ो opcode and रेजिस्टर number in that order
	 * The opcode is 3bits in length, reg is 6 bits दीर्घ
	 */
	shअगरt_out_bits(padapter, EEPROM_READ_OPCODE, 3);
	shअगरt_out_bits(padapter, reg, padapter->eeprom_address_size);
	/* Now पढ़ो the data (16 bits) in from the selected EEPROM word */
	data = shअगरt_in_bits(padapter);
	eeprom_clean(padapter);
out:
	अगर (पंचांगp8_clk_new != पंचांगp8_clk_ori)
		r8712_ग_लिखो8(padapter, 0x10250003, पंचांगp8_clk_ori);
	अगर (पंचांगp8_new != पंचांगp8_ori)
		r8712_ग_लिखो8(padapter, 0x102502f1, पंचांगp8_ori);
	वापस data;
पूर्ण
