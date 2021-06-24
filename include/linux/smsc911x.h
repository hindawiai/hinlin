<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/***************************************************************************
 *
 * Copyright (C) 2004-2008 SMSC
 * Copyright (C) 2005-2008 ARM
 *
 ***************************************************************************/
#अगर_अघोषित __LINUX_SMSC911X_H__
#घोषणा __LINUX_SMSC911X_H__

#समावेश <linux/phy.h>
#समावेश <linux/अगर_ether.h>

/* platक्रमm_device configuration data, should be asचिन्हित to
 * the platक्रमm_device's dev.platक्रमm_data */
काष्ठा smsc911x_platक्रमm_config अणु
	अचिन्हित पूर्णांक irq_polarity;
	अचिन्हित पूर्णांक irq_type;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक shअगरt;
	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	अचिन्हित अक्षर mac[ETH_ALEN];
पूर्ण;

/* Constants क्रम platक्रमm_device irq polarity configuration */
#घोषणा SMSC911X_IRQ_POLARITY_ACTIVE_LOW	0
#घोषणा SMSC911X_IRQ_POLARITY_ACTIVE_HIGH	1

/* Constants क्रम platक्रमm_device irq type configuration */
#घोषणा SMSC911X_IRQ_TYPE_OPEN_DRAIN		0
#घोषणा SMSC911X_IRQ_TYPE_PUSH_PULL		1

/* Constants क्रम flags */
#घोषणा SMSC911X_USE_16BIT 			(BIT(0))
#घोषणा SMSC911X_USE_32BIT 			(BIT(1))
#घोषणा SMSC911X_FORCE_INTERNAL_PHY		(BIT(2))
#घोषणा SMSC911X_FORCE_EXTERNAL_PHY 		(BIT(3))
#घोषणा SMSC911X_SAVE_MAC_ADDRESS		(BIT(4))

/*
 * SMSC911X_SWAP_FIFO:
 * Enables software byte swap क्रम fअगरo data. Should only be used as a
 * "last resort" in the हाल of big endian mode on boards with incorrectly
 * routed data bus to older devices such as LAN9118. Newer devices such as
 * LAN9221 can handle this in hardware, there are रेजिस्टरs to control
 * this swapping but the driver करोesn't currently use them.
 */
#घोषणा SMSC911X_SWAP_FIFO			(BIT(5))

#पूर्ण_अगर /* __LINUX_SMSC911X_H__ */
