<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Marvell PTP driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 */

#अगर_अघोषित PTP_H
#घोषणा PTP_H

#समावेश <linux/समयcounter.h>
#समावेश <linux/समय64.h>
#समावेश <linux/spinlock.h>

काष्ठा ptp अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *reg_base;
	u32 घड़ी_rate;
पूर्ण;

काष्ठा ptp *ptp_get(व्योम);
व्योम ptp_put(काष्ठा ptp *ptp);

बाह्य काष्ठा pci_driver ptp_driver;

#पूर्ण_अगर
