<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2015 Freescale Semiconductor Inc.
 * Copyright 2018-2019 NXP
 */
#अगर_अघोषित DPAA2_ETH_DEBUGFS_H
#घोषणा DPAA2_ETH_DEBUGFS_H

#समावेश <linux/dcache.h>

काष्ठा dpaa2_eth_priv;

काष्ठा dpaa2_debugfs अणु
	काष्ठा dentry *dir;
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
व्योम dpaa2_eth_dbg_init(व्योम);
व्योम dpaa2_eth_dbg_निकास(व्योम);
व्योम dpaa2_dbg_add(काष्ठा dpaa2_eth_priv *priv);
व्योम dpaa2_dbg_हटाओ(काष्ठा dpaa2_eth_priv *priv);
#अन्यथा
अटल अंतरभूत व्योम dpaa2_eth_dbg_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम dpaa2_eth_dbg_निकास(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम dpaa2_dbg_add(काष्ठा dpaa2_eth_priv *priv) अणुपूर्ण
अटल अंतरभूत व्योम dpaa2_dbg_हटाओ(काष्ठा dpaa2_eth_priv *priv) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#पूर्ण_अगर /* DPAA2_ETH_DEBUGFS_H */
