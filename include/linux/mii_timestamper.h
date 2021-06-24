<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम generic समय stamping devices on MII buses.
 * Copyright (C) 2018 Riअक्षरd Cochran <riअक्षरdcochran@gmail.com>
 */
#अगर_अघोषित _LINUX_MII_TIMESTAMPER_H
#घोषणा _LINUX_MII_TIMESTAMPER_H

#समावेश <linux/device.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>

काष्ठा phy_device;

/**
 * काष्ठा mii_बारtamper - Callback पूर्णांकerface to MII समय stamping devices.
 *
 * @rxtstamp:	Requests a Rx बारtamp क्रम 'skb'.  If the skb is accepted,
 *		the MII समय stamping device promises to deliver it using
 *		netअगर_rx() as soon as a बारtamp becomes available. One of
 *		the PTP_CLASS_ values is passed in 'type'.  The function
 *		must वापस true अगर the skb is accepted क्रम delivery.
 *
 * @txtstamp:	Requests a Tx बारtamp क्रम 'skb'.  The MII समय stamping
 *		device promises to deliver it using skb_complete_tx_बारtamp()
 *		as soon as a बारtamp becomes available. One of the PTP_CLASS_
 *		values is passed in 'type'.
 *
 * @hwtstamp:	Handles SIOCSHWTSTAMP ioctl क्रम hardware समय stamping.
 *
 * @link_state: Allows the device to respond to changes in the link
 *		state.  The caller invokes this function जबतक holding
 *		the phy_device mutex.
 *
 * @ts_info:	Handles ethtool queries क्रम hardware समय stamping.
 * @device:	Remembers the device to which the instance beदीर्घs.
 *
 * Drivers क्रम PHY समय stamping devices should embed their
 * mii_बारtamper within a निजी काष्ठाure, obtaining a reference
 * to it using container_of().
 *
 * Drivers क्रम non-PHY समय stamping devices should वापस a poपूर्णांकer
 * to a mii_बारtamper from the probe_channel() callback of their
 * mii_बारtamping_ctrl पूर्णांकerface.
 */
काष्ठा mii_बारtamper अणु
	bool (*rxtstamp)(काष्ठा mii_बारtamper *mii_ts,
			 काष्ठा sk_buff *skb, पूर्णांक type);

	व्योम (*txtstamp)(काष्ठा mii_बारtamper *mii_ts,
			 काष्ठा sk_buff *skb, पूर्णांक type);

	पूर्णांक  (*hwtstamp)(काष्ठा mii_बारtamper *mii_ts,
			 काष्ठा अगरreq *अगरreq);

	व्योम (*link_state)(काष्ठा mii_बारtamper *mii_ts,
			   काष्ठा phy_device *phydev);

	पूर्णांक  (*ts_info)(काष्ठा mii_बारtamper *mii_ts,
			काष्ठा ethtool_ts_info *ts_info);

	काष्ठा device *device;
पूर्ण;

/**
 * काष्ठा mii_बारtamping_ctrl - MII समय stamping controller पूर्णांकerface.
 *
 * @probe_channel:	Callback पूर्णांकo the controller driver announcing the
 *			presence of the 'port' channel.  The 'device' field
 *			had been passed to रेजिस्टर_mii_tstamp_controller().
 *			The driver must वापस either a poपूर्णांकer to a valid
 *			MII बारtamper instance or PTR_ERR.
 *
 * @release_channel:	Releases an instance obtained via .probe_channel.
 */
काष्ठा mii_बारtamping_ctrl अणु
	काष्ठा mii_बारtamper *(*probe_channel)(काष्ठा device *device,
						 अचिन्हित पूर्णांक port);
	व्योम (*release_channel)(काष्ठा device *device,
				काष्ठा mii_बारtamper *mii_ts);
पूर्ण;

#अगर_घोषित CONFIG_NETWORK_PHY_TIMESTAMPING

पूर्णांक रेजिस्टर_mii_tstamp_controller(काष्ठा device *device,
				   काष्ठा mii_बारtamping_ctrl *ctrl);

व्योम unरेजिस्टर_mii_tstamp_controller(काष्ठा device *device);

काष्ठा mii_बारtamper *रेजिस्टर_mii_बारtamper(काष्ठा device_node *node,
						 अचिन्हित पूर्णांक port);

व्योम unरेजिस्टर_mii_बारtamper(काष्ठा mii_बारtamper *mii_ts);

#अन्यथा

अटल अंतरभूत
पूर्णांक रेजिस्टर_mii_tstamp_controller(काष्ठा device *device,
				   काष्ठा mii_बारtamping_ctrl *ctrl)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_mii_tstamp_controller(काष्ठा device *device)
अणु
पूर्ण

अटल अंतरभूत
काष्ठा mii_बारtamper *रेजिस्टर_mii_बारtamper(काष्ठा device_node *node,
						 अचिन्हित पूर्णांक port)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_mii_बारtamper(काष्ठा mii_बारtamper *mii_ts)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
