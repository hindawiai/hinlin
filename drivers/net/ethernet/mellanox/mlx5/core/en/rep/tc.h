<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_REP_TC_H__
#घोषणा __MLX5_EN_REP_TC_H__

#समावेश <linux/skbuff.h>
#समावेश "en_tc.h"
#समावेश "en_rep.h"

#अगर IS_ENABLED(CONFIG_MLX5_CLS_ACT)

पूर्णांक mlx5e_rep_tc_init(काष्ठा mlx5e_rep_priv *rpriv);
व्योम mlx5e_rep_tc_cleanup(काष्ठा mlx5e_rep_priv *rpriv);

पूर्णांक mlx5e_rep_tc_netdevice_event_रेजिस्टर(काष्ठा mlx5e_rep_priv *rpriv);
व्योम mlx5e_rep_tc_netdevice_event_unरेजिस्टर(काष्ठा mlx5e_rep_priv *rpriv);

व्योम mlx5e_rep_tc_enable(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_rep_tc_disable(काष्ठा mlx5e_priv *priv);

पूर्णांक mlx5e_rep_tc_event_port_affinity(काष्ठा mlx5e_priv *priv);

व्योम mlx5e_rep_update_flows(काष्ठा mlx5e_priv *priv,
			    काष्ठा mlx5e_encap_entry *e,
			    bool neigh_connected,
			    अचिन्हित अक्षर ha[ETH_ALEN]);

पूर्णांक mlx5e_rep_encap_entry_attach(काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5e_encap_entry *e,
				 काष्ठा mlx5e_neigh *m_neigh,
				 काष्ठा net_device *neigh_dev);
व्योम mlx5e_rep_encap_entry_detach(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5e_encap_entry *e);

पूर्णांक mlx5e_rep_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
		       व्योम *type_data);

bool mlx5e_rep_tc_update_skb(काष्ठा mlx5_cqe64 *cqe,
			     काष्ठा sk_buff *skb,
			     काष्ठा mlx5e_tc_update_priv *tc_priv);
व्योम mlx5_rep_tc_post_napi_receive(काष्ठा mlx5e_tc_update_priv *tc_priv);

#अन्यथा /* CONFIG_MLX5_CLS_ACT */

काष्ठा mlx5e_rep_priv;
अटल अंतरभूत पूर्णांक
mlx5e_rep_tc_init(काष्ठा mlx5e_rep_priv *rpriv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम
mlx5e_rep_tc_cleanup(काष्ठा mlx5e_rep_priv *rpriv) अणुपूर्ण

अटल अंतरभूत पूर्णांक
mlx5e_rep_tc_netdevice_event_रेजिस्टर(काष्ठा mlx5e_rep_priv *rpriv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम
mlx5e_rep_tc_netdevice_event_unरेजिस्टर(काष्ठा mlx5e_rep_priv *rpriv) अणुपूर्ण

अटल अंतरभूत व्योम
mlx5e_rep_tc_enable(काष्ठा mlx5e_priv *priv) अणुपूर्ण
अटल अंतरभूत व्योम
mlx5e_rep_tc_disable(काष्ठा mlx5e_priv *priv) अणुपूर्ण

अटल अंतरभूत पूर्णांक
mlx5e_rep_tc_event_port_affinity(काष्ठा mlx5e_priv *priv) अणु वापस NOTIFY_DONE; पूर्ण

अटल अंतरभूत पूर्णांक
mlx5e_rep_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
		   व्योम *type_data) अणु वापस -EOPNOTSUPP; पूर्ण

काष्ठा mlx5e_tc_update_priv;
अटल अंतरभूत bool
mlx5e_rep_tc_update_skb(काष्ठा mlx5_cqe64 *cqe,
			काष्ठा sk_buff *skb,
			काष्ठा mlx5e_tc_update_priv *tc_priv) अणु वापस true; पूर्ण
अटल अंतरभूत व्योम
mlx5_rep_tc_post_napi_receive(काष्ठा mlx5e_tc_update_priv *tc_priv) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_CLS_ACT */

#पूर्ण_अगर /* __MLX5_EN_REP_TC_H__ */
