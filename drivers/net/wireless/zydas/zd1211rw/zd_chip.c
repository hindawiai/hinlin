<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 */

/* This file implements all the hardware specअगरic functions क्रम the ZD1211
 * and ZD1211B chips. Support क्रम the ZD1211B was possible after Timothy
 * Legge sent me a ZD1211B device. Thank you Tim. -- Uli
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश "zd_def.h"
#समावेश "zd_chip.h"
#समावेश "zd_mac.h"
#समावेश "zd_rf.h"

व्योम zd_chip_init(काष्ठा zd_chip *chip,
	         काष्ठा ieee80211_hw *hw,
		 काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	स_रखो(chip, 0, माप(*chip));
	mutex_init(&chip->mutex);
	zd_usb_init(&chip->usb, hw, पूर्णांकf);
	zd_rf_init(&chip->rf);
पूर्ण

व्योम zd_chip_clear(काष्ठा zd_chip *chip)
अणु
	ZD_ASSERT(!mutex_is_locked(&chip->mutex));
	zd_usb_clear(&chip->usb);
	zd_rf_clear(&chip->rf);
	mutex_destroy(&chip->mutex);
	ZD_MEMCLEAR(chip, माप(*chip));
पूर्ण

अटल पूर्णांक scnprपूर्णांक_mac_oui(काष्ठा zd_chip *chip, अक्षर *buffer, माप_प्रकार size)
अणु
	u8 *addr = zd_mac_get_perm_addr(zd_chip_to_mac(chip));
	वापस scnम_लिखो(buffer, size, "%3phD", addr);
पूर्ण

/* Prपूर्णांकs an identअगरier line, which will support debugging. */
अटल पूर्णांक scnprपूर्णांक_id(काष्ठा zd_chip *chip, अक्षर *buffer, माप_प्रकार size)
अणु
	पूर्णांक i = 0;

	i = scnम_लिखो(buffer, size, "zd1211%s chip ",
		      zd_chip_is_zd1211b(chip) ? "b" : "");
	i += zd_usb_scnprपूर्णांक_id(&chip->usb, buffer+i, size-i);
	i += scnम_लिखो(buffer+i, size-i, " ");
	i += scnprपूर्णांक_mac_oui(chip, buffer+i, size-i);
	i += scnम_लिखो(buffer+i, size-i, " ");
	i += zd_rf_scnprपूर्णांक_id(&chip->rf, buffer+i, size-i);
	i += scnम_लिखो(buffer+i, size-i, " pa%1x %c%c%c%c%c", chip->pa_type,
		chip->patch_cck_gain ? 'g' : '-',
		chip->patch_cr157 ? '7' : '-',
		chip->patch_6m_band_edge ? '6' : '-',
		chip->new_phy_layout ? 'N' : '-',
		chip->al2230s_bit ? 'S' : '-');
	वापस i;
पूर्ण

अटल व्योम prपूर्णांक_id(काष्ठा zd_chip *chip)
अणु
	अक्षर buffer[80];

	scnprपूर्णांक_id(chip, buffer, माप(buffer));
	buffer[माप(buffer)-1] = 0;
	dev_info(zd_chip_dev(chip), "%s\n", buffer);
पूर्ण

अटल zd_addr_t inc_addr(zd_addr_t addr)
अणु
	u16 a = (u16)addr;
	/* Control रेजिस्टरs use byte addressing, but everything अन्यथा uses word
	 * addressing. */
	अगर ((a & 0xf000) == CR_START)
		a += 2;
	अन्यथा
		a += 1;
	वापस (zd_addr_t)a;
पूर्ण

/* Read a variable number of 32-bit values. Parameter count is not allowed to
 * exceed USB_MAX_IOREAD32_COUNT.
 */
पूर्णांक zd_ioपढ़ो32v_locked(काष्ठा zd_chip *chip, u32 *values, स्थिर zd_addr_t *addr,
		 अचिन्हित पूर्णांक count)
अणु
	पूर्णांक r;
	पूर्णांक i;
	zd_addr_t a16[USB_MAX_IOREAD32_COUNT * 2];
	u16 v16[USB_MAX_IOREAD32_COUNT * 2];
	अचिन्हित पूर्णांक count16;

	अगर (count > USB_MAX_IOREAD32_COUNT)
		वापस -EINVAL;

	/* Use stack क्रम values and addresses. */
	count16 = 2 * count;
	BUG_ON(count16 * माप(zd_addr_t) > माप(a16));
	BUG_ON(count16 * माप(u16) > माप(v16));

	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक j = 2*i;
		/* We पढ़ो the high word always first. */
		a16[j] = inc_addr(addr[i]);
		a16[j+1] = addr[i];
	पूर्ण

	r = zd_ioपढ़ो16v_locked(chip, v16, a16, count16);
	अगर (r) अणु
		dev_dbg_f(zd_chip_dev(chip),
			  "error: %s. Error number %d\n", __func__, r);
		वापस r;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक j = 2*i;
		values[i] = (v16[j] << 16) | v16[j+1];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _zd_ioग_लिखो32v_async_locked(काष्ठा zd_chip *chip,
				       स्थिर काष्ठा zd_ioreq32 *ioreqs,
				       अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i, j, r;
	काष्ठा zd_ioreq16 ioreqs16[USB_MAX_IOWRITE32_COUNT * 2];
	अचिन्हित पूर्णांक count16;

	/* Use stack क्रम values and addresses. */

	ZD_ASSERT(mutex_is_locked(&chip->mutex));

	अगर (count == 0)
		वापस 0;
	अगर (count > USB_MAX_IOWRITE32_COUNT)
		वापस -EINVAL;

	count16 = 2 * count;
	BUG_ON(count16 * माप(काष्ठा zd_ioreq16) > माप(ioreqs16));

	क्रम (i = 0; i < count; i++) अणु
		j = 2*i;
		/* We ग_लिखो the high word always first. */
		ioreqs16[j].value   = ioreqs[i].value >> 16;
		ioreqs16[j].addr    = inc_addr(ioreqs[i].addr);
		ioreqs16[j+1].value = ioreqs[i].value;
		ioreqs16[j+1].addr  = ioreqs[i].addr;
	पूर्ण

	r = zd_usb_ioग_लिखो16v_async(&chip->usb, ioreqs16, count16);
#अगर_घोषित DEBUG
	अगर (r) अणु
		dev_dbg_f(zd_chip_dev(chip),
			  "error %d in zd_usb_write16v\n", r);
	पूर्ण
#पूर्ण_अगर /* DEBUG */
	वापस r;
पूर्ण

पूर्णांक _zd_ioग_लिखो32v_locked(काष्ठा zd_chip *chip, स्थिर काष्ठा zd_ioreq32 *ioreqs,
			  अचिन्हित पूर्णांक count)
अणु
	पूर्णांक r;

	zd_usb_ioग_लिखो16v_async_start(&chip->usb);
	r = _zd_ioग_लिखो32v_async_locked(chip, ioreqs, count);
	अगर (r) अणु
		zd_usb_ioग_लिखो16v_async_end(&chip->usb, 0);
		वापस r;
	पूर्ण
	वापस zd_usb_ioग_लिखो16v_async_end(&chip->usb, 50 /* ms */);
पूर्ण

पूर्णांक zd_ioग_लिखो16a_locked(काष्ठा zd_chip *chip,
                  स्थिर काष्ठा zd_ioreq16 *ioreqs, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक i, j, t, max;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	zd_usb_ioग_लिखो16v_async_start(&chip->usb);

	क्रम (i = 0; i < count; i += j + t) अणु
		t = 0;
		max = count-i;
		अगर (max > USB_MAX_IOWRITE16_COUNT)
			max = USB_MAX_IOWRITE16_COUNT;
		क्रम (j = 0; j < max; j++) अणु
			अगर (!ioreqs[i+j].addr) अणु
				t = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		r = zd_usb_ioग_लिखो16v_async(&chip->usb, &ioreqs[i], j);
		अगर (r) अणु
			zd_usb_ioग_लिखो16v_async_end(&chip->usb, 0);
			dev_dbg_f(zd_chip_dev(chip),
				  "error zd_usb_iowrite16v. Error number %d\n",
				  r);
			वापस r;
		पूर्ण
	पूर्ण

	वापस zd_usb_ioग_लिखो16v_async_end(&chip->usb, 50 /* ms */);
पूर्ण

/* Writes a variable number of 32 bit रेजिस्टरs. The functions will split
 * that in several USB requests. A split can be क्रमced by inserting an IO
 * request with an zero address field.
 */
पूर्णांक zd_ioग_लिखो32a_locked(काष्ठा zd_chip *chip,
	          स्थिर काष्ठा zd_ioreq32 *ioreqs, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक i, j, t, max;

	zd_usb_ioग_लिखो16v_async_start(&chip->usb);

	क्रम (i = 0; i < count; i += j + t) अणु
		t = 0;
		max = count-i;
		अगर (max > USB_MAX_IOWRITE32_COUNT)
			max = USB_MAX_IOWRITE32_COUNT;
		क्रम (j = 0; j < max; j++) अणु
			अगर (!ioreqs[i+j].addr) अणु
				t = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		r = _zd_ioग_लिखो32v_async_locked(chip, &ioreqs[i], j);
		अगर (r) अणु
			zd_usb_ioग_लिखो16v_async_end(&chip->usb, 0);
			dev_dbg_f(zd_chip_dev(chip),
				"error _%s. Error number %d\n", __func__,
				r);
			वापस r;
		पूर्ण
	पूर्ण

	वापस zd_usb_ioग_लिखो16v_async_end(&chip->usb, 50 /* ms */);
पूर्ण

पूर्णांक zd_ioपढ़ो16(काष्ठा zd_chip *chip, zd_addr_t addr, u16 *value)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = zd_ioपढ़ो16_locked(chip, value, addr);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

पूर्णांक zd_ioपढ़ो32(काष्ठा zd_chip *chip, zd_addr_t addr, u32 *value)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = zd_ioपढ़ो32_locked(chip, value, addr);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

पूर्णांक zd_ioग_लिखो16(काष्ठा zd_chip *chip, zd_addr_t addr, u16 value)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = zd_ioग_लिखो16_locked(chip, value, addr);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

पूर्णांक zd_ioग_लिखो32(काष्ठा zd_chip *chip, zd_addr_t addr, u32 value)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = zd_ioग_लिखो32_locked(chip, value, addr);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

पूर्णांक zd_ioपढ़ो32v(काष्ठा zd_chip *chip, स्थिर zd_addr_t *addresses,
	          u32 *values, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = zd_ioपढ़ो32v_locked(chip, values, addresses, count);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

पूर्णांक zd_ioग_लिखो32a(काष्ठा zd_chip *chip, स्थिर काष्ठा zd_ioreq32 *ioreqs,
	          अचिन्हित पूर्णांक count)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = zd_ioग_लिखो32a_locked(chip, ioreqs, count);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

अटल पूर्णांक पढ़ो_pod(काष्ठा zd_chip *chip, u8 *rf_type)
अणु
	पूर्णांक r;
	u32 value;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_ioपढ़ो32_locked(chip, &value, E2P_POD);
	अगर (r)
		जाओ error;
	dev_dbg_f(zd_chip_dev(chip), "E2P_POD %#010x\n", value);

	/* FIXME: AL2230 handling (Bit 7 in POD) */
	*rf_type = value & 0x0f;
	chip->pa_type = (value >> 16) & 0x0f;
	chip->patch_cck_gain = (value >> 8) & 0x1;
	chip->patch_cr157 = (value >> 13) & 0x1;
	chip->patch_6m_band_edge = (value >> 21) & 0x1;
	chip->new_phy_layout = (value >> 31) & 0x1;
	chip->al2230s_bit = (value >> 7) & 0x1;
	chip->link_led = ((value >> 4) & 1) ? LED1 : LED2;
	chip->supports_tx_led = 1;
	अगर (value & (1 << 24)) अणु /* LED scenario */
		अगर (value & (1 << 29))
			chip->supports_tx_led = 0;
	पूर्ण

	dev_dbg_f(zd_chip_dev(chip),
		"RF %s %#01x PA type %#01x patch CCK %d patch CR157 %d "
		"patch 6M %d new PHY %d link LED%d tx led %d\n",
		zd_rf_name(*rf_type), *rf_type,
		chip->pa_type, chip->patch_cck_gain,
		chip->patch_cr157, chip->patch_6m_band_edge,
		chip->new_phy_layout,
		chip->link_led == LED1 ? 1 : 2,
		chip->supports_tx_led);
	वापस 0;
error:
	*rf_type = 0;
	chip->pa_type = 0;
	chip->patch_cck_gain = 0;
	chip->patch_cr157 = 0;
	chip->patch_6m_band_edge = 0;
	chip->new_phy_layout = 0;
	वापस r;
पूर्ण

अटल पूर्णांक zd_ग_लिखो_mac_addr_common(काष्ठा zd_chip *chip, स्थिर u8 *mac_addr,
				    स्थिर काष्ठा zd_ioreq32 *in_reqs,
				    स्थिर अक्षर *type)
अणु
	पूर्णांक r;
	काष्ठा zd_ioreq32 reqs[2] = अणुin_reqs[0], in_reqs[1]पूर्ण;

	अगर (mac_addr) अणु
		reqs[0].value = (mac_addr[3] << 24)
			      | (mac_addr[2] << 16)
			      | (mac_addr[1] <<  8)
			      |  mac_addr[0];
		reqs[1].value = (mac_addr[5] <<  8)
			      |  mac_addr[4];
		dev_dbg_f(zd_chip_dev(chip), "%s addr %pM\n", type, mac_addr);
	पूर्ण अन्यथा अणु
		dev_dbg_f(zd_chip_dev(chip), "set NULL %s\n", type);
	पूर्ण

	mutex_lock(&chip->mutex);
	r = zd_ioग_लिखो32a_locked(chip, reqs, ARRAY_SIZE(reqs));
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

/* MAC address: अगर custom mac addresses are to be used CR_MAC_ADDR_P1 and
 *              CR_MAC_ADDR_P2 must be overwritten
 */
पूर्णांक zd_ग_लिखो_mac_addr(काष्ठा zd_chip *chip, स्थिर u8 *mac_addr)
अणु
	अटल स्थिर काष्ठा zd_ioreq32 reqs[2] = अणु
		[0] = अणु .addr = CR_MAC_ADDR_P1 पूर्ण,
		[1] = अणु .addr = CR_MAC_ADDR_P2 पूर्ण,
	पूर्ण;

	वापस zd_ग_लिखो_mac_addr_common(chip, mac_addr, reqs, "mac");
पूर्ण

पूर्णांक zd_ग_लिखो_bssid(काष्ठा zd_chip *chip, स्थिर u8 *bssid)
अणु
	अटल स्थिर काष्ठा zd_ioreq32 reqs[2] = अणु
		[0] = अणु .addr = CR_BSSID_P1 पूर्ण,
		[1] = अणु .addr = CR_BSSID_P2 पूर्ण,
	पूर्ण;

	वापस zd_ग_लिखो_mac_addr_common(chip, bssid, reqs, "bssid");
पूर्ण

पूर्णांक zd_पढ़ो_regकरोमुख्य(काष्ठा zd_chip *chip, u8 *regकरोमुख्य)
अणु
	पूर्णांक r;
	u32 value;

	mutex_lock(&chip->mutex);
	r = zd_ioपढ़ो32_locked(chip, &value, E2P_SUBID);
	mutex_unlock(&chip->mutex);
	अगर (r)
		वापस r;

	*regकरोमुख्य = value >> 16;
	dev_dbg_f(zd_chip_dev(chip), "regdomain: %#04x\n", *regकरोमुख्य);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_values(काष्ठा zd_chip *chip, u8 *values, माप_प्रकार count,
	               zd_addr_t e2p_addr, u32 guard)
अणु
	पूर्णांक r;
	पूर्णांक i;
	u32 v;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	क्रम (i = 0;;) अणु
		r = zd_ioपढ़ो32_locked(chip, &v,
			               (zd_addr_t)((u16)e2p_addr+i/2));
		अगर (r)
			वापस r;
		v -= guard;
		अगर (i+4 < count) अणु
			values[i++] = v;
			values[i++] = v >>  8;
			values[i++] = v >> 16;
			values[i++] = v >> 24;
			जारी;
		पूर्ण
		क्रम (;i < count; i++)
			values[i] = v >> (8*(i%3));
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक पढ़ो_pwr_cal_values(काष्ठा zd_chip *chip)
अणु
	वापस पढ़ो_values(chip, chip->pwr_cal_values,
		        E2P_CHANNEL_COUNT, E2P_PWR_CAL_VALUE1,
			0);
पूर्ण

अटल पूर्णांक पढ़ो_pwr_पूर्णांक_values(काष्ठा zd_chip *chip)
अणु
	वापस पढ़ो_values(chip, chip->pwr_पूर्णांक_values,
		        E2P_CHANNEL_COUNT, E2P_PWR_INT_VALUE1,
			E2P_PWR_INT_GUARD);
पूर्ण

अटल पूर्णांक पढ़ो_ofdm_cal_values(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;
	पूर्णांक i;
	अटल स्थिर zd_addr_t addresses[] = अणु
		E2P_36M_CAL_VALUE1,
		E2P_48M_CAL_VALUE1,
		E2P_54M_CAL_VALUE1,
	पूर्ण;

	क्रम (i = 0; i < 3; i++) अणु
		r = पढ़ो_values(chip, chip->ofdm_cal_values[i],
				E2P_CHANNEL_COUNT, addresses[i], 0);
		अगर (r)
			वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_cal_पूर्णांक_tables(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;

	r = पढ़ो_pwr_cal_values(chip);
	अगर (r)
		वापस r;
	r = पढ़ो_pwr_पूर्णांक_values(chip);
	अगर (r)
		वापस r;
	r = पढ़ो_ofdm_cal_values(chip);
	अगर (r)
		वापस r;
	वापस 0;
पूर्ण

/* phy means physical रेजिस्टरs */
पूर्णांक zd_chip_lock_phy_regs(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;
	u32 पंचांगp;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_ioपढ़ो32_locked(chip, &पंचांगp, CR_REG1);
	अगर (r) अणु
		dev_err(zd_chip_dev(chip), "error ioread32(CR_REG1): %d\n", r);
		वापस r;
	पूर्ण

	पंचांगp &= ~UNLOCK_PHY_REGS;

	r = zd_ioग_लिखो32_locked(chip, पंचांगp, CR_REG1);
	अगर (r)
		dev_err(zd_chip_dev(chip), "error iowrite32(CR_REG1): %d\n", r);
	वापस r;
पूर्ण

पूर्णांक zd_chip_unlock_phy_regs(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;
	u32 पंचांगp;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_ioपढ़ो32_locked(chip, &पंचांगp, CR_REG1);
	अगर (r) अणु
		dev_err(zd_chip_dev(chip),
			"error ioread32(CR_REG1): %d\n", r);
		वापस r;
	पूर्ण

	पंचांगp |= UNLOCK_PHY_REGS;

	r = zd_ioग_लिखो32_locked(chip, पंचांगp, CR_REG1);
	अगर (r)
		dev_err(zd_chip_dev(chip), "error iowrite32(CR_REG1): %d\n", r);
	वापस r;
पूर्ण

/* ZD_CR157 can be optionally patched by the EEPROM क्रम original ZD1211 */
अटल पूर्णांक patch_cr157(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;
	u16 value;

	अगर (!chip->patch_cr157)
		वापस 0;

	r = zd_ioपढ़ो16_locked(chip, &value, E2P_PHY_REG);
	अगर (r)
		वापस r;

	dev_dbg_f(zd_chip_dev(chip), "patching value %x\n", value >> 8);
	वापस zd_ioग_लिखो32_locked(chip, value >> 8, ZD_CR157);
पूर्ण

/*
 * 6M band edge can be optionally overwritten क्रम certain RF's
 * Venकरोr driver says: क्रम FCC regulation, enabled per HWFeature 6M band edge
 * bit (क्रम AL2230, AL2230S)
 */
अटल पूर्णांक patch_6m_band_edge(काष्ठा zd_chip *chip, u8 channel)
अणु
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	अगर (!chip->patch_6m_band_edge)
		वापस 0;

	वापस zd_rf_patch_6m_band_edge(&chip->rf, channel);
पूर्ण

/* Generic implementation of 6M band edge patching, used by most RFs via
 * zd_rf_generic_patch_6m() */
पूर्णांक zd_chip_generic_patch_6m_band(काष्ठा zd_chip *chip, पूर्णांक channel)
अणु
	काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR128, 0x14 पूर्ण, अणु ZD_CR129, 0x12 पूर्ण, अणु ZD_CR130, 0x10 पूर्ण,
		अणु ZD_CR47,  0x1e पूर्ण,
	पूर्ण;

	/* FIXME: Channel 11 is not the edge क्रम all regulatory करोमुख्यs. */
	अगर (channel == 1 || channel == 11)
		ioreqs[0].value = 0x12;

	dev_dbg_f(zd_chip_dev(chip), "patching for channel %d\n", channel);
	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक zd1211_hw_reset_phy(काष्ठा zd_chip *chip)
अणु
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR0,   0x0a पूर्ण, अणु ZD_CR1,   0x06 पूर्ण, अणु ZD_CR2,   0x26 पूर्ण,
		अणु ZD_CR3,   0x38 पूर्ण, अणु ZD_CR4,   0x80 पूर्ण, अणु ZD_CR9,   0xa0 पूर्ण,
		अणु ZD_CR10,  0x81 पूर्ण, अणु ZD_CR11,  0x00 पूर्ण, अणु ZD_CR12,  0x7f पूर्ण,
		अणु ZD_CR13,  0x8c पूर्ण, अणु ZD_CR14,  0x80 पूर्ण, अणु ZD_CR15,  0x3d पूर्ण,
		अणु ZD_CR16,  0x20 पूर्ण, अणु ZD_CR17,  0x1e पूर्ण, अणु ZD_CR18,  0x0a पूर्ण,
		अणु ZD_CR19,  0x48 पूर्ण, अणु ZD_CR20,  0x0c पूर्ण, अणु ZD_CR21,  0x0c पूर्ण,
		अणु ZD_CR22,  0x23 पूर्ण, अणु ZD_CR23,  0x90 पूर्ण, अणु ZD_CR24,  0x14 पूर्ण,
		अणु ZD_CR25,  0x40 पूर्ण, अणु ZD_CR26,  0x10 पूर्ण, अणु ZD_CR27,  0x19 पूर्ण,
		अणु ZD_CR28,  0x7f पूर्ण, अणु ZD_CR29,  0x80 पूर्ण, अणु ZD_CR30,  0x4b पूर्ण,
		अणु ZD_CR31,  0x60 पूर्ण, अणु ZD_CR32,  0x43 पूर्ण, अणु ZD_CR33,  0x08 पूर्ण,
		अणु ZD_CR34,  0x06 पूर्ण, अणु ZD_CR35,  0x0a पूर्ण, अणु ZD_CR36,  0x00 पूर्ण,
		अणु ZD_CR37,  0x00 पूर्ण, अणु ZD_CR38,  0x38 पूर्ण, अणु ZD_CR39,  0x0c पूर्ण,
		अणु ZD_CR40,  0x84 पूर्ण, अणु ZD_CR41,  0x2a पूर्ण, अणु ZD_CR42,  0x80 पूर्ण,
		अणु ZD_CR43,  0x10 पूर्ण, अणु ZD_CR44,  0x12 पूर्ण, अणु ZD_CR46,  0xff पूर्ण,
		अणु ZD_CR47,  0x1E पूर्ण, अणु ZD_CR48,  0x26 पूर्ण, अणु ZD_CR49,  0x5b पूर्ण,
		अणु ZD_CR64,  0xd0 पूर्ण, अणु ZD_CR65,  0x04 पूर्ण, अणु ZD_CR66,  0x58 पूर्ण,
		अणु ZD_CR67,  0xc9 पूर्ण, अणु ZD_CR68,  0x88 पूर्ण, अणु ZD_CR69,  0x41 पूर्ण,
		अणु ZD_CR70,  0x23 पूर्ण, अणु ZD_CR71,  0x10 पूर्ण, अणु ZD_CR72,  0xff पूर्ण,
		अणु ZD_CR73,  0x32 पूर्ण, अणु ZD_CR74,  0x30 पूर्ण, अणु ZD_CR75,  0x65 पूर्ण,
		अणु ZD_CR76,  0x41 पूर्ण, अणु ZD_CR77,  0x1b पूर्ण, अणु ZD_CR78,  0x30 पूर्ण,
		अणु ZD_CR79,  0x68 पूर्ण, अणु ZD_CR80,  0x64 पूर्ण, अणु ZD_CR81,  0x64 पूर्ण,
		अणु ZD_CR82,  0x00 पूर्ण, अणु ZD_CR83,  0x00 पूर्ण, अणु ZD_CR84,  0x00 पूर्ण,
		अणु ZD_CR85,  0x02 पूर्ण, अणु ZD_CR86,  0x00 पूर्ण, अणु ZD_CR87,  0x00 पूर्ण,
		अणु ZD_CR88,  0xff पूर्ण, अणु ZD_CR89,  0xfc पूर्ण, अणु ZD_CR90,  0x00 पूर्ण,
		अणु ZD_CR91,  0x00 पूर्ण, अणु ZD_CR92,  0x00 पूर्ण, अणु ZD_CR93,  0x08 पूर्ण,
		अणु ZD_CR94,  0x00 पूर्ण, अणु ZD_CR95,  0x00 पूर्ण, अणु ZD_CR96,  0xff पूर्ण,
		अणु ZD_CR97,  0xe7 पूर्ण, अणु ZD_CR98,  0x00 पूर्ण, अणु ZD_CR99,  0x00 पूर्ण,
		अणु ZD_CR100, 0x00 पूर्ण, अणु ZD_CR101, 0xae पूर्ण, अणु ZD_CR102, 0x02 पूर्ण,
		अणु ZD_CR103, 0x00 पूर्ण, अणु ZD_CR104, 0x03 पूर्ण, अणु ZD_CR105, 0x65 पूर्ण,
		अणु ZD_CR106, 0x04 पूर्ण, अणु ZD_CR107, 0x00 पूर्ण, अणु ZD_CR108, 0x0a पूर्ण,
		अणु ZD_CR109, 0xaa पूर्ण, अणु ZD_CR110, 0xaa पूर्ण, अणु ZD_CR111, 0x25 पूर्ण,
		अणु ZD_CR112, 0x25 पूर्ण, अणु ZD_CR113, 0x00 पूर्ण, अणु ZD_CR119, 0x1e पूर्ण,
		अणु ZD_CR125, 0x90 पूर्ण, अणु ZD_CR126, 0x00 पूर्ण, अणु ZD_CR127, 0x00 पूर्ण,
		अणु पूर्ण,
		अणु ZD_CR5,   0x00 पूर्ण, अणु ZD_CR6,   0x00 पूर्ण, अणु ZD_CR7,   0x00 पूर्ण,
		अणु ZD_CR8,   0x00 पूर्ण, अणु ZD_CR9,   0x20 पूर्ण, अणु ZD_CR12,  0xf0 पूर्ण,
		अणु ZD_CR20,  0x0e पूर्ण, अणु ZD_CR21,  0x0e पूर्ण, अणु ZD_CR27,  0x10 पूर्ण,
		अणु ZD_CR44,  0x33 पूर्ण, अणु ZD_CR47,  0x1E पूर्ण, अणु ZD_CR83,  0x24 पूर्ण,
		अणु ZD_CR84,  0x04 पूर्ण, अणु ZD_CR85,  0x00 पूर्ण, अणु ZD_CR86,  0x0C पूर्ण,
		अणु ZD_CR87,  0x12 पूर्ण, अणु ZD_CR88,  0x0C पूर्ण, अणु ZD_CR89,  0x00 पूर्ण,
		अणु ZD_CR90,  0x10 पूर्ण, अणु ZD_CR91,  0x08 पूर्ण, अणु ZD_CR93,  0x00 पूर्ण,
		अणु ZD_CR94,  0x01 पूर्ण, अणु ZD_CR95,  0x00 पूर्ण, अणु ZD_CR96,  0x50 पूर्ण,
		अणु ZD_CR97,  0x37 पूर्ण, अणु ZD_CR98,  0x35 पूर्ण, अणु ZD_CR101, 0x13 पूर्ण,
		अणु ZD_CR102, 0x27 पूर्ण, अणु ZD_CR103, 0x27 पूर्ण, अणु ZD_CR104, 0x18 पूर्ण,
		अणु ZD_CR105, 0x12 पूर्ण, अणु ZD_CR109, 0x27 पूर्ण, अणु ZD_CR110, 0x27 पूर्ण,
		अणु ZD_CR111, 0x27 पूर्ण, अणु ZD_CR112, 0x27 पूर्ण, अणु ZD_CR113, 0x27 पूर्ण,
		अणु ZD_CR114, 0x27 पूर्ण, अणु ZD_CR115, 0x26 पूर्ण, अणु ZD_CR116, 0x24 पूर्ण,
		अणु ZD_CR117, 0xfc पूर्ण, अणु ZD_CR118, 0xfa पूर्ण, अणु ZD_CR120, 0x4f पूर्ण,
		अणु ZD_CR125, 0xaa पूर्ण, अणु ZD_CR127, 0x03 पूर्ण, अणु ZD_CR128, 0x14 पूर्ण,
		अणु ZD_CR129, 0x12 पूर्ण, अणु ZD_CR130, 0x10 पूर्ण, अणु ZD_CR131, 0x0C पूर्ण,
		अणु ZD_CR136, 0xdf पूर्ण, अणु ZD_CR137, 0x40 पूर्ण, अणु ZD_CR138, 0xa0 पूर्ण,
		अणु ZD_CR139, 0xb0 पूर्ण, अणु ZD_CR140, 0x99 पूर्ण, अणु ZD_CR141, 0x82 पूर्ण,
		अणु ZD_CR142, 0x54 पूर्ण, अणु ZD_CR143, 0x1c पूर्ण, अणु ZD_CR144, 0x6c पूर्ण,
		अणु ZD_CR147, 0x07 पूर्ण, अणु ZD_CR148, 0x4c पूर्ण, अणु ZD_CR149, 0x50 पूर्ण,
		अणु ZD_CR150, 0x0e पूर्ण, अणु ZD_CR151, 0x18 पूर्ण, अणु ZD_CR160, 0xfe पूर्ण,
		अणु ZD_CR161, 0xee पूर्ण, अणु ZD_CR162, 0xaa पूर्ण, अणु ZD_CR163, 0xfa पूर्ण,
		अणु ZD_CR164, 0xfa पूर्ण, अणु ZD_CR165, 0xea पूर्ण, अणु ZD_CR166, 0xbe पूर्ण,
		अणु ZD_CR167, 0xbe पूर्ण, अणु ZD_CR168, 0x6a पूर्ण, अणु ZD_CR169, 0xba पूर्ण,
		अणु ZD_CR170, 0xba पूर्ण, अणु ZD_CR171, 0xba पूर्ण,
		/* Note: ZD_CR204 must lead the ZD_CR203 */
		अणु ZD_CR204, 0x7d पूर्ण,
		अणु पूर्ण,
		अणु ZD_CR203, 0x30 पूर्ण,
	पूर्ण;

	पूर्णांक r, t;

	dev_dbg_f(zd_chip_dev(chip), "\n");

	r = zd_chip_lock_phy_regs(chip);
	अगर (r)
		जाओ out;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	अगर (r)
		जाओ unlock;

	r = patch_cr157(chip);
unlock:
	t = zd_chip_unlock_phy_regs(chip);
	अगर (t && !r)
		r = t;
out:
	वापस r;
पूर्ण

अटल पूर्णांक zd1211b_hw_reset_phy(काष्ठा zd_chip *chip)
अणु
	अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR0,   0x14 पूर्ण, अणु ZD_CR1,   0x06 पूर्ण, अणु ZD_CR2,   0x26 पूर्ण,
		अणु ZD_CR3,   0x38 पूर्ण, अणु ZD_CR4,   0x80 पूर्ण, अणु ZD_CR9,   0xe0 पूर्ण,
		अणु ZD_CR10,  0x81 पूर्ण,
		/* घातer control अणु अणु ZD_CR11,  1 << 6 पूर्ण, */
		अणु ZD_CR11,  0x00 पूर्ण,
		अणु ZD_CR12,  0xf0 पूर्ण, अणु ZD_CR13,  0x8c पूर्ण, अणु ZD_CR14,  0x80 पूर्ण,
		अणु ZD_CR15,  0x3d पूर्ण, अणु ZD_CR16,  0x20 पूर्ण, अणु ZD_CR17,  0x1e पूर्ण,
		अणु ZD_CR18,  0x0a पूर्ण, अणु ZD_CR19,  0x48 पूर्ण,
		अणु ZD_CR20,  0x10 पूर्ण, /* Org:0x0E, ComTrend:RalLink AP */
		अणु ZD_CR21,  0x0e पूर्ण, अणु ZD_CR22,  0x23 पूर्ण, अणु ZD_CR23,  0x90 पूर्ण,
		अणु ZD_CR24,  0x14 पूर्ण, अणु ZD_CR25,  0x40 पूर्ण, अणु ZD_CR26,  0x10 पूर्ण,
		अणु ZD_CR27,  0x10 पूर्ण, अणु ZD_CR28,  0x7f पूर्ण, अणु ZD_CR29,  0x80 पूर्ण,
		अणु ZD_CR30,  0x4b पूर्ण, /* ASIC/FWT, no joपूर्णांकly decoder */
		अणु ZD_CR31,  0x60 पूर्ण, अणु ZD_CR32,  0x43 पूर्ण, अणु ZD_CR33,  0x08 पूर्ण,
		अणु ZD_CR34,  0x06 पूर्ण, अणु ZD_CR35,  0x0a पूर्ण, अणु ZD_CR36,  0x00 पूर्ण,
		अणु ZD_CR37,  0x00 पूर्ण, अणु ZD_CR38,  0x38 पूर्ण, अणु ZD_CR39,  0x0c पूर्ण,
		अणु ZD_CR40,  0x84 पूर्ण, अणु ZD_CR41,  0x2a पूर्ण, अणु ZD_CR42,  0x80 पूर्ण,
		अणु ZD_CR43,  0x10 पूर्ण, अणु ZD_CR44,  0x33 पूर्ण, अणु ZD_CR46,  0xff पूर्ण,
		अणु ZD_CR47,  0x1E पूर्ण, अणु ZD_CR48,  0x26 पूर्ण, अणु ZD_CR49,  0x5b पूर्ण,
		अणु ZD_CR64,  0xd0 पूर्ण, अणु ZD_CR65,  0x04 पूर्ण, अणु ZD_CR66,  0x58 पूर्ण,
		अणु ZD_CR67,  0xc9 पूर्ण, अणु ZD_CR68,  0x88 पूर्ण, अणु ZD_CR69,  0x41 पूर्ण,
		अणु ZD_CR70,  0x23 पूर्ण, अणु ZD_CR71,  0x10 पूर्ण, अणु ZD_CR72,  0xff पूर्ण,
		अणु ZD_CR73,  0x32 पूर्ण, अणु ZD_CR74,  0x30 पूर्ण, अणु ZD_CR75,  0x65 पूर्ण,
		अणु ZD_CR76,  0x41 पूर्ण, अणु ZD_CR77,  0x1b पूर्ण, अणु ZD_CR78,  0x30 पूर्ण,
		अणु ZD_CR79,  0xf0 पूर्ण, अणु ZD_CR80,  0x64 पूर्ण, अणु ZD_CR81,  0x64 पूर्ण,
		अणु ZD_CR82,  0x00 पूर्ण, अणु ZD_CR83,  0x24 पूर्ण, अणु ZD_CR84,  0x04 पूर्ण,
		अणु ZD_CR85,  0x00 पूर्ण, अणु ZD_CR86,  0x0c पूर्ण, अणु ZD_CR87,  0x12 पूर्ण,
		अणु ZD_CR88,  0x0c पूर्ण, अणु ZD_CR89,  0x00 पूर्ण, अणु ZD_CR90,  0x58 पूर्ण,
		अणु ZD_CR91,  0x04 पूर्ण, अणु ZD_CR92,  0x00 पूर्ण, अणु ZD_CR93,  0x00 पूर्ण,
		अणु ZD_CR94,  0x01 पूर्ण,
		अणु ZD_CR95,  0x20 पूर्ण, /* ZD1211B */
		अणु ZD_CR96,  0x50 पूर्ण, अणु ZD_CR97,  0x37 पूर्ण, अणु ZD_CR98,  0x35 पूर्ण,
		अणु ZD_CR99,  0x00 पूर्ण, अणु ZD_CR100, 0x01 पूर्ण, अणु ZD_CR101, 0x13 पूर्ण,
		अणु ZD_CR102, 0x27 पूर्ण, अणु ZD_CR103, 0x27 पूर्ण, अणु ZD_CR104, 0x18 पूर्ण,
		अणु ZD_CR105, 0x12 पूर्ण, अणु ZD_CR106, 0x04 पूर्ण, अणु ZD_CR107, 0x00 पूर्ण,
		अणु ZD_CR108, 0x0a पूर्ण, अणु ZD_CR109, 0x27 पूर्ण, अणु ZD_CR110, 0x27 पूर्ण,
		अणु ZD_CR111, 0x27 पूर्ण, अणु ZD_CR112, 0x27 पूर्ण, अणु ZD_CR113, 0x27 पूर्ण,
		अणु ZD_CR114, 0x27 पूर्ण, अणु ZD_CR115, 0x26 पूर्ण, अणु ZD_CR116, 0x24 पूर्ण,
		अणु ZD_CR117, 0xfc पूर्ण, अणु ZD_CR118, 0xfa पूर्ण, अणु ZD_CR119, 0x1e पूर्ण,
		अणु ZD_CR125, 0x90 पूर्ण, अणु ZD_CR126, 0x00 पूर्ण, अणु ZD_CR127, 0x00 पूर्ण,
		अणु ZD_CR128, 0x14 पूर्ण, अणु ZD_CR129, 0x12 पूर्ण, अणु ZD_CR130, 0x10 पूर्ण,
		अणु ZD_CR131, 0x0c पूर्ण, अणु ZD_CR136, 0xdf पूर्ण, अणु ZD_CR137, 0xa0 पूर्ण,
		अणु ZD_CR138, 0xa8 पूर्ण, अणु ZD_CR139, 0xb4 पूर्ण, अणु ZD_CR140, 0x98 पूर्ण,
		अणु ZD_CR141, 0x82 पूर्ण, अणु ZD_CR142, 0x53 पूर्ण, अणु ZD_CR143, 0x1c पूर्ण,
		अणु ZD_CR144, 0x6c पूर्ण, अणु ZD_CR147, 0x07 पूर्ण, अणु ZD_CR148, 0x40 पूर्ण,
		अणु ZD_CR149, 0x40 पूर्ण, /* Org:0x50 ComTrend:RalLink AP */
		अणु ZD_CR150, 0x14 पूर्ण, /* Org:0x0E ComTrend:RalLink AP */
		अणु ZD_CR151, 0x18 पूर्ण, अणु ZD_CR159, 0x70 पूर्ण, अणु ZD_CR160, 0xfe पूर्ण,
		अणु ZD_CR161, 0xee पूर्ण, अणु ZD_CR162, 0xaa पूर्ण, अणु ZD_CR163, 0xfa पूर्ण,
		अणु ZD_CR164, 0xfa पूर्ण, अणु ZD_CR165, 0xea पूर्ण, अणु ZD_CR166, 0xbe पूर्ण,
		अणु ZD_CR167, 0xbe पूर्ण, अणु ZD_CR168, 0x6a पूर्ण, अणु ZD_CR169, 0xba पूर्ण,
		अणु ZD_CR170, 0xba पूर्ण, अणु ZD_CR171, 0xba पूर्ण,
		/* Note: ZD_CR204 must lead the ZD_CR203 */
		अणु ZD_CR204, 0x7d पूर्ण,
		अणुपूर्ण,
		अणु ZD_CR203, 0x30 पूर्ण,
	पूर्ण;

	पूर्णांक r, t;

	dev_dbg_f(zd_chip_dev(chip), "\n");

	r = zd_chip_lock_phy_regs(chip);
	अगर (r)
		जाओ out;

	r = zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	t = zd_chip_unlock_phy_regs(chip);
	अगर (t && !r)
		r = t;
out:
	वापस r;
पूर्ण

अटल पूर्णांक hw_reset_phy(काष्ठा zd_chip *chip)
अणु
	वापस zd_chip_is_zd1211b(chip) ? zd1211b_hw_reset_phy(chip) :
		                  zd1211_hw_reset_phy(chip);
पूर्ण

अटल पूर्णांक zd1211_hw_init_hmac(काष्ठा zd_chip *chip)
अणु
	अटल स्थिर काष्ठा zd_ioreq32 ioreqs[] = अणु
		अणु CR_ZD1211_RETRY_MAX,		ZD1211_RETRY_COUNT पूर्ण,
		अणु CR_RX_THRESHOLD,		0x000c0640 पूर्ण,
	पूर्ण;

	dev_dbg_f(zd_chip_dev(chip), "\n");
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	वापस zd_ioग_लिखो32a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक zd1211b_hw_init_hmac(काष्ठा zd_chip *chip)
अणु
	अटल स्थिर काष्ठा zd_ioreq32 ioreqs[] = अणु
		अणु CR_ZD1211B_RETRY_MAX,		ZD1211B_RETRY_COUNT पूर्ण,
		अणु CR_ZD1211B_CWIN_MAX_MIN_AC0,	0x007f003f पूर्ण,
		अणु CR_ZD1211B_CWIN_MAX_MIN_AC1,	0x007f003f पूर्ण,
		अणु CR_ZD1211B_CWIN_MAX_MIN_AC2,  0x003f001f पूर्ण,
		अणु CR_ZD1211B_CWIN_MAX_MIN_AC3,  0x001f000f पूर्ण,
		अणु CR_ZD1211B_AIFS_CTL1,		0x00280028 पूर्ण,
		अणु CR_ZD1211B_AIFS_CTL2,		0x008C003C पूर्ण,
		अणु CR_ZD1211B_TXOP,		0x01800824 पूर्ण,
		अणु CR_RX_THRESHOLD,		0x000c0eff, पूर्ण,
	पूर्ण;

	dev_dbg_f(zd_chip_dev(chip), "\n");
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	वापस zd_ioग_लिखो32a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक hw_init_hmac(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;
	अटल स्थिर काष्ठा zd_ioreq32 ioreqs[] = अणु
		अणु CR_ACK_TIMEOUT_EXT,		0x20 पूर्ण,
		अणु CR_ADDA_MBIAS_WARMTIME,	0x30000808 पूर्ण,
		अणु CR_SNIFFER_ON,		0 पूर्ण,
		अणु CR_RX_FILTER,			STA_RX_FILTER पूर्ण,
		अणु CR_GROUP_HASH_P1,		0x00 पूर्ण,
		अणु CR_GROUP_HASH_P2,		0x80000000 पूर्ण,
		अणु CR_REG1,			0xa4 पूर्ण,
		अणु CR_ADDA_PWR_DWN,		0x7f पूर्ण,
		अणु CR_BCN_PLCP_CFG,		0x00f00401 पूर्ण,
		अणु CR_PHY_DELAY,			0x00 पूर्ण,
		अणु CR_ACK_TIMEOUT_EXT,		0x80 पूर्ण,
		अणु CR_ADDA_PWR_DWN,		0x00 पूर्ण,
		अणु CR_ACK_TIME_80211,		0x100 पूर्ण,
		अणु CR_RX_PE_DELAY,		0x70 पूर्ण,
		अणु CR_PS_CTRL,			0x10000000 पूर्ण,
		अणु CR_RTS_CTS_RATE,		0x02030203 पूर्ण,
		अणु CR_AFTER_PNP,			0x1 पूर्ण,
		अणु CR_WEP_PROTECT,		0x114 पूर्ण,
		अणु CR_IFS_VALUE,			IFS_VALUE_DEFAULT पूर्ण,
		अणु CR_CAM_MODE,			MODE_AP_WDSपूर्ण,
	पूर्ण;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_ioग_लिखो32a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	अगर (r)
		वापस r;

	वापस zd_chip_is_zd1211b(chip) ?
		zd1211b_hw_init_hmac(chip) : zd1211_hw_init_hmac(chip);
पूर्ण

काष्ठा aw_pt_bi अणु
	u32 atim_wnd_period;
	u32 pre_tbtt;
	u32 beacon_पूर्णांकerval;
पूर्ण;

अटल पूर्णांक get_aw_pt_bi(काष्ठा zd_chip *chip, काष्ठा aw_pt_bi *s)
अणु
	पूर्णांक r;
	अटल स्थिर zd_addr_t aw_pt_bi_addr[] =
		अणु CR_ATIM_WND_PERIOD, CR_PRE_TBTT, CR_BCN_INTERVAL पूर्ण;
	u32 values[3];

	r = zd_ioपढ़ो32v_locked(chip, values, (स्थिर zd_addr_t *)aw_pt_bi_addr,
		         ARRAY_SIZE(aw_pt_bi_addr));
	अगर (r) अणु
		स_रखो(s, 0, माप(*s));
		वापस r;
	पूर्ण

	s->atim_wnd_period = values[0];
	s->pre_tbtt = values[1];
	s->beacon_पूर्णांकerval = values[2];
	वापस 0;
पूर्ण

अटल पूर्णांक set_aw_pt_bi(काष्ठा zd_chip *chip, काष्ठा aw_pt_bi *s)
अणु
	काष्ठा zd_ioreq32 reqs[3];
	u16 b_पूर्णांकerval = s->beacon_पूर्णांकerval & 0xffff;

	अगर (b_पूर्णांकerval <= 5)
		b_पूर्णांकerval = 5;
	अगर (s->pre_tbtt < 4 || s->pre_tbtt >= b_पूर्णांकerval)
		s->pre_tbtt = b_पूर्णांकerval - 1;
	अगर (s->atim_wnd_period >= s->pre_tbtt)
		s->atim_wnd_period = s->pre_tbtt - 1;

	reqs[0].addr = CR_ATIM_WND_PERIOD;
	reqs[0].value = s->atim_wnd_period;
	reqs[1].addr = CR_PRE_TBTT;
	reqs[1].value = s->pre_tbtt;
	reqs[2].addr = CR_BCN_INTERVAL;
	reqs[2].value = (s->beacon_पूर्णांकerval & ~0xffff) | b_पूर्णांकerval;

	वापस zd_ioग_लिखो32a_locked(chip, reqs, ARRAY_SIZE(reqs));
पूर्ण


अटल पूर्णांक set_beacon_पूर्णांकerval(काष्ठा zd_chip *chip, u16 पूर्णांकerval,
			       u8 dtim_period, पूर्णांक type)
अणु
	पूर्णांक r;
	काष्ठा aw_pt_bi s;
	u32 b_पूर्णांकerval, mode_flag;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));

	अगर (पूर्णांकerval > 0) अणु
		चयन (type) अणु
		हाल NL80211_IFTYPE_ADHOC:
		हाल NL80211_IFTYPE_MESH_POINT:
			mode_flag = BCN_MODE_IBSS;
			अवरोध;
		हाल NL80211_IFTYPE_AP:
			mode_flag = BCN_MODE_AP;
			अवरोध;
		शेष:
			mode_flag = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		dtim_period = 0;
		mode_flag = 0;
	पूर्ण

	b_पूर्णांकerval = mode_flag | (dtim_period << 16) | पूर्णांकerval;

	r = zd_ioग_लिखो32_locked(chip, b_पूर्णांकerval, CR_BCN_INTERVAL);
	अगर (r)
		वापस r;
	r = get_aw_pt_bi(chip, &s);
	अगर (r)
		वापस r;
	वापस set_aw_pt_bi(chip, &s);
पूर्ण

पूर्णांक zd_set_beacon_पूर्णांकerval(काष्ठा zd_chip *chip, u16 पूर्णांकerval, u8 dtim_period,
			   पूर्णांक type)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = set_beacon_पूर्णांकerval(chip, पूर्णांकerval, dtim_period, type);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

अटल पूर्णांक hw_init(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;

	dev_dbg_f(zd_chip_dev(chip), "\n");
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = hw_reset_phy(chip);
	अगर (r)
		वापस r;

	r = hw_init_hmac(chip);
	अगर (r)
		वापस r;

	वापस set_beacon_पूर्णांकerval(chip, 100, 0, NL80211_IFTYPE_UNSPECIFIED);
पूर्ण

अटल zd_addr_t fw_reg_addr(काष्ठा zd_chip *chip, u16 offset)
अणु
	वापस (zd_addr_t)((u16)chip->fw_regs_base + offset);
पूर्ण

#अगर_घोषित DEBUG
अटल पूर्णांक dump_cr(काष्ठा zd_chip *chip, स्थिर zd_addr_t addr,
	           स्थिर अक्षर *addr_string)
अणु
	पूर्णांक r;
	u32 value;

	r = zd_ioपढ़ो32_locked(chip, &value, addr);
	अगर (r) अणु
		dev_dbg_f(zd_chip_dev(chip),
			"error reading %s. Error number %d\n", addr_string, r);
		वापस r;
	पूर्ण

	dev_dbg_f(zd_chip_dev(chip), "%s %#010x\n",
		addr_string, (अचिन्हित पूर्णांक)value);
	वापस 0;
पूर्ण

अटल पूर्णांक test_init(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;

	r = dump_cr(chip, CR_AFTER_PNP, "CR_AFTER_PNP");
	अगर (r)
		वापस r;
	r = dump_cr(chip, CR_GPI_EN, "CR_GPI_EN");
	अगर (r)
		वापस r;
	वापस dump_cr(chip, CR_INTERRUPT, "CR_INTERRUPT");
पूर्ण

अटल व्योम dump_fw_रेजिस्टरs(काष्ठा zd_chip *chip)
अणु
	स्थिर zd_addr_t addr[4] = अणु
		fw_reg_addr(chip, FW_REG_FIRMWARE_VER),
		fw_reg_addr(chip, FW_REG_USB_SPEED),
		fw_reg_addr(chip, FW_REG_FIX_TX_RATE),
		fw_reg_addr(chip, FW_REG_LED_LINK_STATUS),
	पूर्ण;

	पूर्णांक r;
	u16 values[4];

	r = zd_ioपढ़ो16v_locked(chip, values, (स्थिर zd_addr_t*)addr,
		         ARRAY_SIZE(addr));
	अगर (r) अणु
		dev_dbg_f(zd_chip_dev(chip), "error %d zd_ioread16v_locked\n",
			 r);
		वापस;
	पूर्ण

	dev_dbg_f(zd_chip_dev(chip), "FW_FIRMWARE_VER %#06hx\n", values[0]);
	dev_dbg_f(zd_chip_dev(chip), "FW_USB_SPEED %#06hx\n", values[1]);
	dev_dbg_f(zd_chip_dev(chip), "FW_FIX_TX_RATE %#06hx\n", values[2]);
	dev_dbg_f(zd_chip_dev(chip), "FW_LINK_STATUS %#06hx\n", values[3]);
पूर्ण
#पूर्ण_अगर /* DEBUG */

अटल पूर्णांक prपूर्णांक_fw_version(काष्ठा zd_chip *chip)
अणु
	काष्ठा wiphy *wiphy = zd_chip_to_mac(chip)->hw->wiphy;
	पूर्णांक r;
	u16 version;

	r = zd_ioपढ़ो16_locked(chip, &version,
		fw_reg_addr(chip, FW_REG_FIRMWARE_VER));
	अगर (r)
		वापस r;

	dev_info(zd_chip_dev(chip),"firmware version %04hx\n", version);

	snम_लिखो(wiphy->fw_version, माप(wiphy->fw_version),
			"%04hx", version);

	वापस 0;
पूर्ण

अटल पूर्णांक set_mandatory_rates(काष्ठा zd_chip *chip, पूर्णांक gmode)
अणु
	u32 rates;
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	/* This sets the mandatory rates, which only depend from the standard
	 * that the device is supporting. Until further notice we should try
	 * to support 802.11g also क्रम full speed USB.
	 */
	अगर (!gmode)
		rates = CR_RATE_1M|CR_RATE_2M|CR_RATE_5_5M|CR_RATE_11M;
	अन्यथा
		rates = CR_RATE_1M|CR_RATE_2M|CR_RATE_5_5M|CR_RATE_11M|
			CR_RATE_6M|CR_RATE_12M|CR_RATE_24M;

	वापस zd_ioग_लिखो32_locked(chip, rates, CR_MANDATORY_RATE_TBL);
पूर्ण

पूर्णांक zd_chip_set_rts_cts_rate_locked(काष्ठा zd_chip *chip,
				    पूर्णांक preamble)
अणु
	u32 value = 0;

	dev_dbg_f(zd_chip_dev(chip), "preamble=%x\n", preamble);
	value |= preamble << RTSCTS_SH_RTS_PMB_TYPE;
	value |= preamble << RTSCTS_SH_CTS_PMB_TYPE;

	/* We always send 11M RTS/self-CTS messages, like the venकरोr driver. */
	value |= ZD_PURE_RATE(ZD_CCK_RATE_11M) << RTSCTS_SH_RTS_RATE;
	value |= ZD_RX_CCK << RTSCTS_SH_RTS_MOD_TYPE;
	value |= ZD_PURE_RATE(ZD_CCK_RATE_11M) << RTSCTS_SH_CTS_RATE;
	value |= ZD_RX_CCK << RTSCTS_SH_CTS_MOD_TYPE;

	वापस zd_ioग_लिखो32_locked(chip, value, CR_RTS_CTS_RATE);
पूर्ण

पूर्णांक zd_chip_enable_hwपूर्णांक(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = zd_ioग_लिखो32_locked(chip, HWINT_ENABLED, CR_INTERRUPT);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

अटल पूर्णांक disable_hwपूर्णांक(काष्ठा zd_chip *chip)
अणु
	वापस zd_ioग_लिखो32_locked(chip, HWINT_DISABLED, CR_INTERRUPT);
पूर्ण

पूर्णांक zd_chip_disable_hwपूर्णांक(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = disable_hwपूर्णांक(chip);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

अटल पूर्णांक पढ़ो_fw_regs_offset(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_ioपढ़ो16_locked(chip, (u16*)&chip->fw_regs_base,
		               FWRAW_REGS_ADDR);
	अगर (r)
		वापस r;
	dev_dbg_f(zd_chip_dev(chip), "fw_regs_base: %#06hx\n",
		  (u16)chip->fw_regs_base);

	वापस 0;
पूर्ण

/* Read mac address using pre-firmware पूर्णांकerface */
पूर्णांक zd_chip_पढ़ो_mac_addr_fw(काष्ठा zd_chip *chip, u8 *addr)
अणु
	dev_dbg_f(zd_chip_dev(chip), "\n");
	वापस zd_usb_पढ़ो_fw(&chip->usb, E2P_MAC_ADDR_P1, addr,
		ETH_ALEN);
पूर्ण

पूर्णांक zd_chip_init_hw(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;
	u8 rf_type;

	dev_dbg_f(zd_chip_dev(chip), "\n");

	mutex_lock(&chip->mutex);

#अगर_घोषित DEBUG
	r = test_init(chip);
	अगर (r)
		जाओ out;
#पूर्ण_अगर
	r = zd_ioग_लिखो32_locked(chip, 1, CR_AFTER_PNP);
	अगर (r)
		जाओ out;

	r = पढ़ो_fw_regs_offset(chip);
	अगर (r)
		जाओ out;

	/* GPI is always disabled, also in the other driver.
	 */
	r = zd_ioग_लिखो32_locked(chip, 0, CR_GPI_EN);
	अगर (r)
		जाओ out;
	r = zd_ioग_लिखो32_locked(chip, CWIN_SIZE, CR_CWMIN_CWMAX);
	अगर (r)
		जाओ out;
	/* Currently we support IEEE 802.11g क्रम full and high speed USB.
	 * It might be discussed, whether we should support pure b mode क्रम
	 * full speed USB.
	 */
	r = set_mandatory_rates(chip, 1);
	अगर (r)
		जाओ out;
	/* Disabling पूर्णांकerrupts is certainly a smart thing here.
	 */
	r = disable_hwपूर्णांक(chip);
	अगर (r)
		जाओ out;
	r = पढ़ो_pod(chip, &rf_type);
	अगर (r)
		जाओ out;
	r = hw_init(chip);
	अगर (r)
		जाओ out;
	r = zd_rf_init_hw(&chip->rf, rf_type);
	अगर (r)
		जाओ out;

	r = prपूर्णांक_fw_version(chip);
	अगर (r)
		जाओ out;

#अगर_घोषित DEBUG
	dump_fw_रेजिस्टरs(chip);
	r = test_init(chip);
	अगर (r)
		जाओ out;
#पूर्ण_अगर /* DEBUG */

	r = पढ़ो_cal_पूर्णांक_tables(chip);
	अगर (r)
		जाओ out;

	prपूर्णांक_id(chip);
out:
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

अटल पूर्णांक update_pwr_पूर्णांक(काष्ठा zd_chip *chip, u8 channel)
अणु
	u8 value = chip->pwr_पूर्णांक_values[channel - 1];
	वापस zd_ioग_लिखो16_locked(chip, value, ZD_CR31);
पूर्ण

अटल पूर्णांक update_pwr_cal(काष्ठा zd_chip *chip, u8 channel)
अणु
	u8 value = chip->pwr_cal_values[channel-1];
	वापस zd_ioग_लिखो16_locked(chip, value, ZD_CR68);
पूर्ण

अटल पूर्णांक update_ofdm_cal(काष्ठा zd_chip *chip, u8 channel)
अणु
	काष्ठा zd_ioreq16 ioreqs[3];

	ioreqs[0].addr = ZD_CR67;
	ioreqs[0].value = chip->ofdm_cal_values[OFDM_36M_INDEX][channel-1];
	ioreqs[1].addr = ZD_CR66;
	ioreqs[1].value = chip->ofdm_cal_values[OFDM_48M_INDEX][channel-1];
	ioreqs[2].addr = ZD_CR65;
	ioreqs[2].value = chip->ofdm_cal_values[OFDM_54M_INDEX][channel-1];

	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

अटल पूर्णांक update_channel_पूर्णांकegration_and_calibration(काष्ठा zd_chip *chip,
	                                              u8 channel)
अणु
	पूर्णांक r;

	अगर (!zd_rf_should_update_pwr_पूर्णांक(&chip->rf))
		वापस 0;

	r = update_pwr_पूर्णांक(chip, channel);
	अगर (r)
		वापस r;
	अगर (zd_chip_is_zd1211b(chip)) अणु
		अटल स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
			अणु ZD_CR69, 0x28 पूर्ण,
			अणुपूर्ण,
			अणु ZD_CR69, 0x2a पूर्ण,
		पूर्ण;

		r = update_ofdm_cal(chip, channel);
		अगर (r)
			वापस r;
		r = update_pwr_cal(chip, channel);
		अगर (r)
			वापस r;
		r = zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/* The CCK baseband gain can be optionally patched by the EEPROM */
अटल पूर्णांक patch_cck_gain(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;
	u32 value;

	अगर (!chip->patch_cck_gain || !zd_rf_should_patch_cck_gain(&chip->rf))
		वापस 0;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_ioपढ़ो32_locked(chip, &value, E2P_PHY_REG);
	अगर (r)
		वापस r;
	dev_dbg_f(zd_chip_dev(chip), "patching value %x\n", value & 0xff);
	वापस zd_ioग_लिखो16_locked(chip, value & 0xff, ZD_CR47);
पूर्ण

पूर्णांक zd_chip_set_channel(काष्ठा zd_chip *chip, u8 channel)
अणु
	पूर्णांक r, t;

	mutex_lock(&chip->mutex);
	r = zd_chip_lock_phy_regs(chip);
	अगर (r)
		जाओ out;
	r = zd_rf_set_channel(&chip->rf, channel);
	अगर (r)
		जाओ unlock;
	r = update_channel_पूर्णांकegration_and_calibration(chip, channel);
	अगर (r)
		जाओ unlock;
	r = patch_cck_gain(chip);
	अगर (r)
		जाओ unlock;
	r = patch_6m_band_edge(chip, channel);
	अगर (r)
		जाओ unlock;
	r = zd_ioग_लिखो32_locked(chip, 0, CR_CONFIG_PHILIPS);
unlock:
	t = zd_chip_unlock_phy_regs(chip);
	अगर (t && !r)
		r = t;
out:
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

u8 zd_chip_get_channel(काष्ठा zd_chip *chip)
अणु
	u8 channel;

	mutex_lock(&chip->mutex);
	channel = chip->rf.channel;
	mutex_unlock(&chip->mutex);
	वापस channel;
पूर्ण

पूर्णांक zd_chip_control_leds(काष्ठा zd_chip *chip, क्रमागत led_status status)
अणु
	स्थिर zd_addr_t a[] = अणु
		fw_reg_addr(chip, FW_REG_LED_LINK_STATUS),
		CR_LED,
	पूर्ण;

	पूर्णांक r;
	u16 v[ARRAY_SIZE(a)];
	काष्ठा zd_ioreq16 ioreqs[ARRAY_SIZE(a)] = अणु
		[0] = अणु fw_reg_addr(chip, FW_REG_LED_LINK_STATUS) पूर्ण,
		[1] = अणु CR_LED पूर्ण,
	पूर्ण;
	u16 other_led;

	mutex_lock(&chip->mutex);
	r = zd_ioपढ़ो16v_locked(chip, v, (स्थिर zd_addr_t *)a, ARRAY_SIZE(a));
	अगर (r)
		जाओ out;

	other_led = chip->link_led == LED1 ? LED2 : LED1;

	चयन (status) अणु
	हाल ZD_LED_OFF:
		ioreqs[0].value = FW_LINK_OFF;
		ioreqs[1].value = v[1] & ~(LED1|LED2);
		अवरोध;
	हाल ZD_LED_SCANNING:
		ioreqs[0].value = FW_LINK_OFF;
		ioreqs[1].value = v[1] & ~other_led;
		अगर ((u32)kसमय_get_seconds() % 3 == 0) अणु
			ioreqs[1].value &= ~chip->link_led;
		पूर्ण अन्यथा अणु
			ioreqs[1].value |= chip->link_led;
		पूर्ण
		अवरोध;
	हाल ZD_LED_ASSOCIATED:
		ioreqs[0].value = FW_LINK_TX;
		ioreqs[1].value = v[1] & ~other_led;
		ioreqs[1].value |= chip->link_led;
		अवरोध;
	शेष:
		r = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (v[0] != ioreqs[0].value || v[1] != ioreqs[1].value) अणु
		r = zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
		अगर (r)
			जाओ out;
	पूर्ण
	r = 0;
out:
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

पूर्णांक zd_chip_set_basic_rates(काष्ठा zd_chip *chip, u16 cr_rates)
अणु
	पूर्णांक r;

	अगर (cr_rates & ~(CR_RATES_80211B|CR_RATES_80211G))
		वापस -EINVAL;

	mutex_lock(&chip->mutex);
	r = zd_ioग_लिखो32_locked(chip, cr_rates, CR_BASIC_RATE_TBL);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

अटल अंतरभूत u8 zd_rate_from_ofdm_plcp_header(स्थिर व्योम *rx_frame)
अणु
	वापस ZD_OFDM | zd_ofdm_plcp_header_rate(rx_frame);
पूर्ण

/**
 * zd_rx_rate - report zd-rate
 * @rx_frame: received frame
 * @status: rx_status as given by the device
 *
 * This function converts the rate as encoded in the received packet to the
 * zd-rate, we are using on other places in the driver.
 */
u8 zd_rx_rate(स्थिर व्योम *rx_frame, स्थिर काष्ठा rx_status *status)
अणु
	u8 zd_rate;
	अगर (status->frame_status & ZD_RX_OFDM) अणु
		zd_rate = zd_rate_from_ofdm_plcp_header(rx_frame);
	पूर्ण अन्यथा अणु
		चयन (zd_cck_plcp_header_संकेत(rx_frame)) अणु
		हाल ZD_CCK_PLCP_SIGNAL_1M:
			zd_rate = ZD_CCK_RATE_1M;
			अवरोध;
		हाल ZD_CCK_PLCP_SIGNAL_2M:
			zd_rate = ZD_CCK_RATE_2M;
			अवरोध;
		हाल ZD_CCK_PLCP_SIGNAL_5M5:
			zd_rate = ZD_CCK_RATE_5_5M;
			अवरोध;
		हाल ZD_CCK_PLCP_SIGNAL_11M:
			zd_rate = ZD_CCK_RATE_11M;
			अवरोध;
		शेष:
			zd_rate = 0;
		पूर्ण
	पूर्ण

	वापस zd_rate;
पूर्ण

पूर्णांक zd_chip_चयन_radio_on(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = zd_चयन_radio_on(&chip->rf);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

पूर्णांक zd_chip_चयन_radio_off(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = zd_चयन_radio_off(&chip->rf);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

पूर्णांक zd_chip_enable_पूर्णांक(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	r = zd_usb_enable_पूर्णांक(&chip->usb);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

व्योम zd_chip_disable_पूर्णांक(काष्ठा zd_chip *chip)
अणु
	mutex_lock(&chip->mutex);
	zd_usb_disable_पूर्णांक(&chip->usb);
	mutex_unlock(&chip->mutex);

	/* cancel pending पूर्णांकerrupt work */
	cancel_work_sync(&zd_chip_to_mac(chip)->process_पूर्णांकr);
पूर्ण

पूर्णांक zd_chip_enable_rxtx(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;

	mutex_lock(&chip->mutex);
	zd_usb_enable_tx(&chip->usb);
	r = zd_usb_enable_rx(&chip->usb);
	zd_tx_watchकरोg_enable(&chip->usb);
	mutex_unlock(&chip->mutex);
	वापस r;
पूर्ण

व्योम zd_chip_disable_rxtx(काष्ठा zd_chip *chip)
अणु
	mutex_lock(&chip->mutex);
	zd_tx_watchकरोg_disable(&chip->usb);
	zd_usb_disable_rx(&chip->usb);
	zd_usb_disable_tx(&chip->usb);
	mutex_unlock(&chip->mutex);
पूर्ण

पूर्णांक zd_rख_डालोv_locked(काष्ठा zd_chip *chip,
	               स्थिर u32* values, अचिन्हित पूर्णांक count, u8 bits)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		r = zd_rख_डालो_locked(chip, values[i], bits);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * We can optionally program the RF directly through CR regs, अगर supported by
 * the hardware. This is much faster than the older method.
 */
पूर्णांक zd_rख_डालो_cr_locked(काष्ठा zd_chip *chip, u32 value)
अणु
	स्थिर काष्ठा zd_ioreq16 ioreqs[] = अणु
		अणु ZD_CR244, (value >> 16) & 0xff पूर्ण,
		अणु ZD_CR243, (value >>  8) & 0xff पूर्ण,
		अणु ZD_CR242,  value        & 0xff पूर्ण,
	पूर्ण;
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	वापस zd_ioग_लिखो16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

पूर्णांक zd_rख_डालोv_cr_locked(काष्ठा zd_chip *chip,
	                  स्थिर u32 *values, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		r = zd_rख_डालो_cr_locked(chip, values[i]);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक zd_chip_set_multicast_hash(काष्ठा zd_chip *chip,
	                       काष्ठा zd_mc_hash *hash)
अणु
	स्थिर काष्ठा zd_ioreq32 ioreqs[] = अणु
		अणु CR_GROUP_HASH_P1, hash->low पूर्ण,
		अणु CR_GROUP_HASH_P2, hash->high पूर्ण,
	पूर्ण;

	वापस zd_ioग_लिखो32a(chip, ioreqs, ARRAY_SIZE(ioreqs));
पूर्ण

u64 zd_chip_get_tsf(काष्ठा zd_chip *chip)
अणु
	पूर्णांक r;
	अटल स्थिर zd_addr_t aw_pt_bi_addr[] =
		अणु CR_TSF_LOW_PART, CR_TSF_HIGH_PART पूर्ण;
	u32 values[2];
	u64 tsf;

	mutex_lock(&chip->mutex);
	r = zd_ioपढ़ो32v_locked(chip, values, (स्थिर zd_addr_t *)aw_pt_bi_addr,
	                        ARRAY_SIZE(aw_pt_bi_addr));
	mutex_unlock(&chip->mutex);
	अगर (r)
		वापस 0;

	tsf = values[1];
	tsf = (tsf << 32) | values[0];

	वापस tsf;
पूर्ण
