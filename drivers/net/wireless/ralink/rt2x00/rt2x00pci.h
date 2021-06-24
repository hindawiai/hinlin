<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00pci
	Abstract: Data काष्ठाures क्रम the rt2x00pci module.
 */

#अगर_अघोषित RT2X00PCI_H
#घोषणा RT2X00PCI_H

#समावेश <linux/पन.स>
#समावेश <linux/pci.h>

/*
 * PCI driver handlers.
 */
पूर्णांक rt2x00pci_probe(काष्ठा pci_dev *pci_dev, स्थिर काष्ठा rt2x00_ops *ops);
व्योम rt2x00pci_हटाओ(काष्ठा pci_dev *pci_dev);

बाह्य स्थिर काष्ठा dev_pm_ops rt2x00pci_pm_ops;

#पूर्ण_अगर /* RT2X00PCI_H */
