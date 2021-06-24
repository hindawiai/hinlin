<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#अगर_अघोषित CFCNFG_H_
#घोषणा CFCNFG_H_
#समावेश <linux/spinlock.h>
#समावेश <linux/netdevice.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfctrl.h>

काष्ठा cfcnfg;

/**
 * क्रमागत cfcnfg_phy_preference - Physical preference HW Abstraction
 *
 * @CFPHYPREF_UNSPECIFIED:	Default physical पूर्णांकerface
 *
 * @CFPHYPREF_LOW_LAT:		Default physical पूर्णांकerface क्रम low-latency
 *				traffic
 * @CFPHYPREF_HIGH_BW:		Default physical पूर्णांकerface क्रम high-bandwidth
 *				traffic
 * @CFPHYPREF_LOOP:		TEST only Loopback पूर्णांकerface simulating modem
 *				responses.
 *
 */
क्रमागत cfcnfg_phy_preference अणु
	CFPHYPREF_UNSPECIFIED,
	CFPHYPREF_LOW_LAT,
	CFPHYPREF_HIGH_BW,
	CFPHYPREF_LOOP
पूर्ण;

/**
 * cfcnfg_create() - Get the CAIF configuration object given network.
 * @net:	Network क्रम the CAIF configuration object.
 */
काष्ठा cfcnfg *get_cfcnfg(काष्ठा net *net);

/**
 * cfcnfg_create() - Create the CAIF configuration object.
 */
काष्ठा cfcnfg *cfcnfg_create(व्योम);

/**
 * cfcnfg_हटाओ() -  Remove the CFCNFG object
 * @cfg: config object
 */
व्योम cfcnfg_हटाओ(काष्ठा cfcnfg *cfg);

/**
 * cfcnfg_add_phy_layer() - Adds a physical layer to the CAIF stack.
 * @cnfg:	Poपूर्णांकer to a CAIF configuration object, created by
 *		cfcnfg_create().
 * @dev:	Poपूर्णांकer to link layer device
 * @phy_layer:	Specअगरy the physical layer. The transmit function
 *		MUST be set in the काष्ठाure.
 * @pref:	The phy (link layer) preference.
 * @link_support: Protocol implementation क्रम link layer specअगरic protocol.
 * @fcs:	Specअगरy अगर checksum is used in CAIF Framing Layer.
 * @head_room:	Head space needed by link specअगरic protocol.
 */
पूर्णांक
cfcnfg_add_phy_layer(काष्ठा cfcnfg *cnfg,
		     काष्ठा net_device *dev, काष्ठा cflayer *phy_layer,
		     क्रमागत cfcnfg_phy_preference pref,
		     काष्ठा cflayer *link_support,
		     bool fcs, पूर्णांक head_room);

/**
 * cfcnfg_del_phy_layer - Deletes an phy layer from the CAIF stack.
 *
 * @cnfg:	Poपूर्णांकer to a CAIF configuration object, created by
 *		cfcnfg_create().
 * @phy_layer:	Adaptation layer to be हटाओd.
 */
पूर्णांक cfcnfg_del_phy_layer(काष्ठा cfcnfg *cnfg, काष्ठा cflayer *phy_layer);

/**
 * cfcnfg_set_phy_state() - Set the state of the physical पूर्णांकerface device.
 * @cnfg:	Configuration object
 * @phy_layer:	Physical Layer representation
 * @up:	State of device
 */
पूर्णांक cfcnfg_set_phy_state(काष्ठा cfcnfg *cnfg, काष्ठा cflayer *phy_layer,
				bool up);

#पूर्ण_अगर				/* CFCNFG_H_ */
