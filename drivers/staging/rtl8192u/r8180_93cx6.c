<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  This files contains card eeprom (93c46 or 93c56) programming routines,
 *  memory is addressed by 16 bits words.
 *
 *  This is part of rtl8180 OpenSource driver.
 *  Copyright (C) Andrea Merello 2004  <andrea.merello@gmail.com>
 *
 *  Parts of this driver are based on the GPL part of the
 *  official realtek driver.
 *
 *  Parts of this driver are based on the rtl8180 driver skeleton
 *  from Patric Schenke & Andres Salomon.
 *
 *  Parts of this driver are based on the Intel Pro Wireless 2100 GPL driver.
 *
 *  We want to thank the Authors of those projects and the Ndiswrapper
 *  project Authors.
 */

#समावेश "r8180_93cx6.h"

अटल व्योम eprom_cs(काष्ठा net_device *dev, लघु bit)
अणु
	u8 cmdreg;
	पूर्णांक err;

	err = पढ़ो_nic_byte_E(dev, EPROM_CMD, &cmdreg);
	अगर (err)
		वापस;
	अगर (bit)
		/* enable EPROM */
		ग_लिखो_nic_byte_E(dev, EPROM_CMD, cmdreg | EPROM_CS_BIT);
	अन्यथा
		/* disable EPROM */
		ग_लिखो_nic_byte_E(dev, EPROM_CMD, cmdreg & ~EPROM_CS_BIT);

	क्रमce_pci_posting(dev);
	udelay(EPROM_DELAY);
पूर्ण

अटल व्योम eprom_ck_cycle(काष्ठा net_device *dev)
अणु
	u8 cmdreg;
	पूर्णांक err;

	err = पढ़ो_nic_byte_E(dev, EPROM_CMD, &cmdreg);
	अगर (err)
		वापस;
	ग_लिखो_nic_byte_E(dev, EPROM_CMD, cmdreg | EPROM_CK_BIT);
	क्रमce_pci_posting(dev);
	udelay(EPROM_DELAY);

	पढ़ो_nic_byte_E(dev, EPROM_CMD, &cmdreg);
	ग_लिखो_nic_byte_E(dev, EPROM_CMD, cmdreg & ~EPROM_CK_BIT);
	क्रमce_pci_posting(dev);
	udelay(EPROM_DELAY);
पूर्ण

अटल व्योम eprom_w(काष्ठा net_device *dev, लघु bit)
अणु
	u8 cmdreg;
	पूर्णांक err;

	err = पढ़ो_nic_byte_E(dev, EPROM_CMD, &cmdreg);
	अगर (err)
		वापस;
	अगर (bit)
		ग_लिखो_nic_byte_E(dev, EPROM_CMD, cmdreg | EPROM_W_BIT);
	अन्यथा
		ग_लिखो_nic_byte_E(dev, EPROM_CMD, cmdreg & ~EPROM_W_BIT);

	क्रमce_pci_posting(dev);
	udelay(EPROM_DELAY);
पूर्ण

अटल लघु eprom_r(काष्ठा net_device *dev)
अणु
	u8 bit;
	पूर्णांक err;

	err = पढ़ो_nic_byte_E(dev, EPROM_CMD, &bit);
	अगर (err)
		वापस err;

	udelay(EPROM_DELAY);

	अगर (bit & EPROM_R_BIT)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम eprom_send_bits_string(काष्ठा net_device *dev, लघु b[], पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		eprom_w(dev, b[i]);
		eprom_ck_cycle(dev);
	पूर्ण
पूर्ण

पूर्णांक eprom_पढ़ो(काष्ठा net_device *dev, u32 addr)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	लघु पढ़ो_cmd[] = अणु1, 1, 0पूर्ण;
	लघु addr_str[8];
	पूर्णांक i;
	पूर्णांक addr_len;
	u32 ret;
	पूर्णांक err;

	ret = 0;
	/* enable EPROM programming */
	ग_लिखो_nic_byte_E(dev, EPROM_CMD,
		       (EPROM_CMD_PROGRAM << EPROM_CMD_OPERATING_MODE_SHIFT));
	क्रमce_pci_posting(dev);
	udelay(EPROM_DELAY);

	अगर (priv->epromtype == EPROM_93c56) अणु
		addr_str[7] = addr & 1;
		addr_str[6] = addr & BIT(1);
		addr_str[5] = addr & BIT(2);
		addr_str[4] = addr & BIT(3);
		addr_str[3] = addr & BIT(4);
		addr_str[2] = addr & BIT(5);
		addr_str[1] = addr & BIT(6);
		addr_str[0] = addr & BIT(7);
		addr_len = 8;
	पूर्ण अन्यथा अणु
		addr_str[5] = addr & 1;
		addr_str[4] = addr & BIT(1);
		addr_str[3] = addr & BIT(2);
		addr_str[2] = addr & BIT(3);
		addr_str[1] = addr & BIT(4);
		addr_str[0] = addr & BIT(5);
		addr_len = 6;
	पूर्ण
	eprom_cs(dev, 1);
	eprom_ck_cycle(dev);
	eprom_send_bits_string(dev, पढ़ो_cmd, 3);
	eprom_send_bits_string(dev, addr_str, addr_len);

	/*
	 * keep chip pin D to low state जबतक पढ़ोing.
	 * I'm unsure if it is necessary, but anyway shouldn't hurt
	 */
	eprom_w(dev, 0);

	क्रम (i = 0; i < 16; i++) अणु
		/* eeprom needs a clk cycle between writing opcode&adr
		 * and पढ़ोing data. (eeprom outs a dummy 0)
		 */
		eprom_ck_cycle(dev);
		err = eprom_r(dev);
		अगर (err < 0)
			वापस err;

		ret |= err << (15 - i);
	पूर्ण

	eprom_cs(dev, 0);
	eprom_ck_cycle(dev);

	/* disable EPROM programming */
	ग_लिखो_nic_byte_E(dev, EPROM_CMD,
		       (EPROM_CMD_NORMAL << EPROM_CMD_OPERATING_MODE_SHIFT));
	वापस ret;
पूर्ण
