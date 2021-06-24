<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* include/linux/dm9000.h
 *
 * Copyright (c) 2004 Simtec Electronics
 *   Ben Dooks <ben@simtec.co.uk>
 *
 * Header file क्रम dm9000 platक्रमm data
*/

#अगर_अघोषित __DM9000_PLATFORM_DATA
#घोषणा __DM9000_PLATFORM_DATA __खाता__

#समावेश <linux/अगर_ether.h>

/* IO control flags */

#घोषणा DM9000_PLATF_8BITONLY	(0x0001)
#घोषणा DM9000_PLATF_16BITONLY	(0x0002)
#घोषणा DM9000_PLATF_32BITONLY	(0x0004)
#घोषणा DM9000_PLATF_EXT_PHY	(0x0008)
#घोषणा DM9000_PLATF_NO_EEPROM	(0x0010)
#घोषणा DM9000_PLATF_SIMPLE_PHY (0x0020)  /* Use NSR to find LinkStatus */

/* platक्रमm data क्रम platक्रमm device काष्ठाure's platक्रमm_data field */

काष्ठा dm9000_plat_data अणु
	अचिन्हित पूर्णांक	flags;
	अचिन्हित अक्षर	dev_addr[ETH_ALEN];

	/* allow replacement IO routines */

	व्योम	(*inblk)(व्योम __iomem *reg, व्योम *data, पूर्णांक len);
	व्योम	(*outblk)(व्योम __iomem *reg, व्योम *data, पूर्णांक len);
	व्योम	(*dumpblk)(व्योम __iomem *reg, पूर्णांक len);
पूर्ण;

#पूर्ण_अगर /* __DM9000_PLATFORM_DATA */

