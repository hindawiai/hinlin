<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __LIB_HV_VHCA_H__
#घोषणा __LIB_HV_VHCA_H__

#समावेश "en.h"
#समावेश "lib/hv.h"

काष्ठा mlx5_hv_vhca_agent;
काष्ठा mlx5_hv_vhca;
काष्ठा mlx5_hv_vhca_control_block;

क्रमागत mlx5_hv_vhca_agent_type अणु
	MLX5_HV_VHCA_AGENT_CONTROL = 0,
	MLX5_HV_VHCA_AGENT_STATS   = 1,
	MLX5_HV_VHCA_AGENT_MAX = 32,
पूर्ण;

#अगर IS_ENABLED(CONFIG_PCI_HYPERV_INTERFACE)

काष्ठा mlx5_hv_vhca_control_block अणु
	u32     capabilities;
	u32     control;
	u16     command;
	u16     command_ack;
	u16     version;
	u16     rings;
	u32     reserved1[28];
पूर्ण;

काष्ठा mlx5_hv_vhca *mlx5_hv_vhca_create(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_hv_vhca_destroy(काष्ठा mlx5_hv_vhca *hv_vhca);
पूर्णांक mlx5_hv_vhca_init(काष्ठा mlx5_hv_vhca *hv_vhca);
व्योम mlx5_hv_vhca_cleanup(काष्ठा mlx5_hv_vhca *hv_vhca);
व्योम mlx5_hv_vhca_invalidate(व्योम *context, u64 block_mask);

काष्ठा mlx5_hv_vhca_agent *
mlx5_hv_vhca_agent_create(काष्ठा mlx5_hv_vhca *hv_vhca,
			  क्रमागत mlx5_hv_vhca_agent_type type,
			  व्योम (*control)(काष्ठा mlx5_hv_vhca_agent*,
					  काष्ठा mlx5_hv_vhca_control_block *block),
			  व्योम (*invalidate)(काष्ठा mlx5_hv_vhca_agent*,
					     u64 block_mask),
			  व्योम (*cleanup)(काष्ठा mlx5_hv_vhca_agent *agent),
			  व्योम *context);

व्योम mlx5_hv_vhca_agent_destroy(काष्ठा mlx5_hv_vhca_agent *agent);
पूर्णांक mlx5_hv_vhca_agent_ग_लिखो(काष्ठा mlx5_hv_vhca_agent *agent,
			     व्योम *buf, पूर्णांक len);
व्योम *mlx5_hv_vhca_agent_priv(काष्ठा mlx5_hv_vhca_agent *agent);

#अन्यथा

अटल अंतरभूत काष्ठा mlx5_hv_vhca *
mlx5_hv_vhca_create(काष्ठा mlx5_core_dev *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mlx5_hv_vhca_destroy(काष्ठा mlx5_hv_vhca *hv_vhca)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_hv_vhca_init(काष्ठा mlx5_hv_vhca *hv_vhca)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx5_hv_vhca_cleanup(काष्ठा mlx5_hv_vhca *hv_vhca)
अणु
पूर्ण

अटल अंतरभूत व्योम mlx5_hv_vhca_invalidate(व्योम *context,
					   u64 block_mask)
अणु
पूर्ण

अटल अंतरभूत काष्ठा mlx5_hv_vhca_agent *
mlx5_hv_vhca_agent_create(काष्ठा mlx5_hv_vhca *hv_vhca,
			  क्रमागत mlx5_hv_vhca_agent_type type,
			  व्योम (*control)(काष्ठा mlx5_hv_vhca_agent*,
					  काष्ठा mlx5_hv_vhca_control_block *block),
			  व्योम (*invalidate)(काष्ठा mlx5_hv_vhca_agent*,
					     u64 block_mask),
			  व्योम (*cleanup)(काष्ठा mlx5_hv_vhca_agent *agent),
			  व्योम *context)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mlx5_hv_vhca_agent_destroy(काष्ठा mlx5_hv_vhca_agent *agent)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
mlx5_hv_vhca_ग_लिखो_agent(काष्ठा mlx5_hv_vhca_agent *agent,
			 व्योम *buf, पूर्णांक len)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LIB_HV_VHCA_H__ */
