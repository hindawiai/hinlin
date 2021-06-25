<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	 This is part of the rtl8180-sa2400 driver
 *	 released under the GPL (See file COPYING क्रम details).
 *	 Copyright (c) 2005 Andrea Merello <andrea.merello@gmail.com>
 *
 *
 *	 This files contains programming code क्रम the rtl8256
 *	 radio frontend.
 *
 *	 *Many* thanks to Realtek Corp. क्रम their great support!
 */

#अगर_अघोषित RTL8225H
#घोषणा RTL8225H

#घोषणा RTL819X_TOTAL_RF_PATH 2 /* क्रम 8192U */
व्योम phy_set_rf8256_bandwidth(काष्ठा net_device *dev,
			      क्रमागत ht_channel_width bandwidth);
व्योम phy_rf8256_config(काष्ठा net_device *dev);
व्योम phy_set_rf8256_cck_tx_घातer(काष्ठा net_device *dev, u8 घातerlevel);
व्योम phy_set_rf8256_ofdm_tx_घातer(काष्ठा net_device *dev, u8 घातerlevel);

#पूर्ण_अगर
