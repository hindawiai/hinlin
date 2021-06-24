<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 * Copyright (C) 2008 Florian Fainelli <florian@खोलोwrt.org>
 * Copyright (C) 2012 Jonas Gorski <jonas.gorski@gmail.com>
 */

#घोषणा pr_fmt(fmt) "bcm63xx_nvram: " fmt

#समावेश <linux/bcm963xx_nvram.h>
#समावेश <linux/init.h>
#समावेश <linux/crc32.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अगर_ether.h>

#समावेश <bcm63xx_nvram.h>

#घोषणा BCM63XX_DEFAULT_PSI_SIZE	64

अटल काष्ठा bcm963xx_nvram nvram;
अटल पूर्णांक mac_addr_used;

व्योम __init bcm63xx_nvram_init(व्योम *addr)
अणु
	u32 crc, expected_crc;
	u8 hcs_mac_addr[ETH_ALEN] = अणु 0x00, 0x10, 0x18, 0xff, 0xff, 0xff पूर्ण;

	/* extract nvram data */
	स_नकल(&nvram, addr, BCM963XX_NVRAM_V5_SIZE);

	/* check checksum beक्रमe using data */
	अगर (bcm963xx_nvram_checksum(&nvram, &expected_crc, &crc))
		pr_warn("nvram checksum failed, contents may be invalid (expected %08x, got %08x)\n",
			expected_crc, crc);

	/* Cable modems have a dअगरferent NVRAM which is embedded in the eCos
	 * firmware and not easily extractible, give at least a MAC address
	 * pool.
	 */
	अगर (BCMCPU_IS_3368()) अणु
		स_नकल(nvram.mac_addr_base, hcs_mac_addr, ETH_ALEN);
		nvram.mac_addr_count = 2;
	पूर्ण
पूर्ण

u8 *bcm63xx_nvram_get_name(व्योम)
अणु
	वापस nvram.name;
पूर्ण
EXPORT_SYMBOL(bcm63xx_nvram_get_name);

पूर्णांक bcm63xx_nvram_get_mac_address(u8 *mac)
अणु
	u8 *oui;
	पूर्णांक count;

	अगर (mac_addr_used >= nvram.mac_addr_count) अणु
		pr_err("not enough mac addresses\n");
		वापस -ENODEV;
	पूर्ण

	स_नकल(mac, nvram.mac_addr_base, ETH_ALEN);
	oui = mac + ETH_ALEN/2 - 1;
	count = mac_addr_used;

	जबतक (count--) अणु
		u8 *p = mac + ETH_ALEN - 1;

		करो अणु
			(*p)++;
			अगर (*p != 0)
				अवरोध;
			p--;
		पूर्ण जबतक (p != oui);

		अगर (p == oui) अणु
			pr_err("unable to fetch mac address\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	mac_addr_used++;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(bcm63xx_nvram_get_mac_address);

पूर्णांक bcm63xx_nvram_get_psi_size(व्योम)
अणु
	अगर (nvram.psi_size > 0)
		वापस nvram.psi_size;

	वापस BCM63XX_DEFAULT_PSI_SIZE;
पूर्ण
EXPORT_SYMBOL(bcm63xx_nvram_get_psi_size);
