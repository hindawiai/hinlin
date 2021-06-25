<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BCM63XX_NVRAM_H
#घोषणा BCM63XX_NVRAM_H

#समावेश <linux/types.h>

/**
 * bcm63xx_nvram_init() - initializes nvram
 * @nvram:	address of the nvram data
 *
 * Initialized the local nvram copy from the target address and checks
 * its checksum.
 */
व्योम bcm63xx_nvram_init(व्योम *nvram);

/**
 * bcm63xx_nvram_get_name() - वापसs the board name according to nvram
 *
 * Returns the board name field from nvram. Note that it might not be
 * null terminated अगर it is exactly 16 bytes दीर्घ.
 */
u8 *bcm63xx_nvram_get_name(व्योम);

/**
 * bcm63xx_nvram_get_mac_address() - रेजिस्टर & वापस a new mac address
 * @mac:	poपूर्णांकer to array क्रम allocated mac
 *
 * Registers and वापसs a mac address from the allocated macs from nvram.
 *
 * Returns 0 on success.
 */
पूर्णांक bcm63xx_nvram_get_mac_address(u8 *mac);

पूर्णांक bcm63xx_nvram_get_psi_size(व्योम);

#पूर्ण_अगर /* BCM63XX_NVRAM_H */
