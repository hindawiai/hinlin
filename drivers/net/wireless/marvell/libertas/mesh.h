<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Contains all definitions needed क्रम the Libertas' MESH implementation.
 */
#अगर_अघोषित _LBS_MESH_H_
#घोषणा _LBS_MESH_H_


#समावेश <net/iw_handler.h>
#समावेश <net/lib80211.h>

#समावेश "host.h"
#समावेश "dev.h"

#अगर_घोषित CONFIG_LIBERTAS_MESH

काष्ठा net_device;

व्योम lbs_init_mesh(काष्ठा lbs_निजी *priv);
व्योम lbs_start_mesh(काष्ठा lbs_निजी *priv);
पूर्णांक lbs_deinit_mesh(काष्ठा lbs_निजी *priv);

व्योम lbs_हटाओ_mesh(काष्ठा lbs_निजी *priv);

अटल अंतरभूत bool lbs_mesh_activated(काष्ठा lbs_निजी *priv)
अणु
	वापस !!priv->mesh_tlv;
पूर्ण

पूर्णांक lbs_mesh_set_channel(काष्ठा lbs_निजी *priv, u8 channel);

/* Sending / Receiving */

काष्ठा rxpd;
काष्ठा txpd;

काष्ठा net_device *lbs_mesh_set_dev(काष्ठा lbs_निजी *priv,
	काष्ठा net_device *dev, काष्ठा rxpd *rxpd);
व्योम lbs_mesh_set_txpd(काष्ठा lbs_निजी *priv,
	काष्ठा net_device *dev, काष्ठा txpd *txpd);


/* Command handling */

काष्ठा cmd_ds_command;
काष्ठा cmd_ds_mesh_access;
काष्ठा cmd_ds_mesh_config;


/* Ethtool statistics */

काष्ठा ethtool_stats;

व्योम lbs_mesh_ethtool_get_stats(काष्ठा net_device *dev,
	काष्ठा ethtool_stats *stats, uपूर्णांक64_t *data);
पूर्णांक lbs_mesh_ethtool_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset);
व्योम lbs_mesh_ethtool_get_strings(काष्ठा net_device *dev,
	uपूर्णांक32_t stringset, uपूर्णांक8_t *s);


#अन्यथा

#घोषणा lbs_init_mesh(priv)	करो अणु पूर्ण जबतक (0)
#घोषणा lbs_deinit_mesh(priv)	करो अणु पूर्ण जबतक (0)
#घोषणा lbs_start_mesh(priv)	करो अणु पूर्ण जबतक (0)
#घोषणा lbs_add_mesh(priv)	करो अणु पूर्ण जबतक (0)
#घोषणा lbs_हटाओ_mesh(priv)	करो अणु पूर्ण जबतक (0)
#घोषणा lbs_mesh_set_dev(priv, dev, rxpd) (dev)
#घोषणा lbs_mesh_set_txpd(priv, dev, txpd) करो अणु पूर्ण जबतक (0)
#घोषणा lbs_mesh_set_channel(priv, channel) (0)
#घोषणा lbs_mesh_activated(priv) (false)

#पूर्ण_अगर



#पूर्ण_अगर
