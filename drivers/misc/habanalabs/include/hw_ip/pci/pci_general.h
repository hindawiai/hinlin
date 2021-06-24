<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित INCLUDE_PCI_GENERAL_H_
#घोषणा INCLUDE_PCI_GENERAL_H_

/* PCI CONFIGURATION SPACE */
#घोषणा mmPCI_CONFIG_ELBI_ADDR		0xFF0
#घोषणा mmPCI_CONFIG_ELBI_DATA		0xFF4
#घोषणा mmPCI_CONFIG_ELBI_CTRL		0xFF8
#घोषणा PCI_CONFIG_ELBI_CTRL_WRITE	(1 << 31)

#घोषणा mmPCI_CONFIG_ELBI_STS		0xFFC
#घोषणा PCI_CONFIG_ELBI_STS_ERR		(1 << 30)
#घोषणा PCI_CONFIG_ELBI_STS_DONE	(1 << 31)
#घोषणा PCI_CONFIG_ELBI_STS_MASK	(PCI_CONFIG_ELBI_STS_ERR | \
					PCI_CONFIG_ELBI_STS_DONE)

#पूर्ण_अगर /* INCLUDE_PCI_GENERAL_H_ */
