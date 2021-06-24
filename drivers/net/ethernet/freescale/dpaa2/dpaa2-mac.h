<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2019 NXP */
#अगर_अघोषित DPAA2_MAC_H
#घोषणा DPAA2_MAC_H

#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/phylink.h>
#समावेश <linux/pcs-lynx.h>

#समावेश "dpmac.h"
#समावेश "dpmac-cmd.h"

काष्ठा dpaa2_mac अणु
	काष्ठा fsl_mc_device *mc_dev;
	काष्ठा dpmac_link_state state;
	काष्ठा net_device *net_dev;
	काष्ठा fsl_mc_io *mc_io;
	काष्ठा dpmac_attr attr;

	काष्ठा phylink_config phylink_config;
	काष्ठा phylink *phylink;
	phy_पूर्णांकerface_t अगर_mode;
	क्रमागत dpmac_link_type अगर_link_type;
	काष्ठा lynx_pcs *pcs;
पूर्ण;

bool dpaa2_mac_is_type_fixed(काष्ठा fsl_mc_device *dpmac_dev,
			     काष्ठा fsl_mc_io *mc_io);

पूर्णांक dpaa2_mac_खोलो(काष्ठा dpaa2_mac *mac);

व्योम dpaa2_mac_बंद(काष्ठा dpaa2_mac *mac);

पूर्णांक dpaa2_mac_connect(काष्ठा dpaa2_mac *mac);

व्योम dpaa2_mac_disconnect(काष्ठा dpaa2_mac *mac);

पूर्णांक dpaa2_mac_get_sset_count(व्योम);

व्योम dpaa2_mac_get_strings(u8 *data);

व्योम dpaa2_mac_get_ethtool_stats(काष्ठा dpaa2_mac *mac, u64 *data);

#पूर्ण_अगर /* DPAA2_MAC_H */
