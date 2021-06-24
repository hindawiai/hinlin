<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __MDP5_CFG_H__
#घोषणा __MDP5_CFG_H__

#समावेश "msm_drv.h"

/*
 * mdp5_cfg
 *
 * This module configures the dynamic offsets used by mdp5.xml.h
 * (initialized in mdp5_cfg.c)
 */
बाह्य स्थिर काष्ठा mdp5_cfg_hw *mdp5_cfg;

#घोषणा MAX_CTL			8
#घोषणा MAX_BASES		8
#घोषणा MAX_SMP_BLOCKS		44
#घोषणा MAX_CLIENTS		32

प्रकार DECLARE_BITMAP(mdp5_smp_state_t, MAX_SMP_BLOCKS);

#घोषणा MDP5_SUB_BLOCK_DEFINITION \
	अचिन्हित पूर्णांक count; \
	uपूर्णांक32_t base[MAX_BASES]

काष्ठा mdp5_sub_block अणु
	MDP5_SUB_BLOCK_DEFINITION;
पूर्ण;

काष्ठा mdp5_lm_instance अणु
	पूर्णांक id;
	पूर्णांक pp;
	पूर्णांक dspp;
	uपूर्णांक32_t caps;
पूर्ण;

काष्ठा mdp5_lm_block अणु
	MDP5_SUB_BLOCK_DEFINITION;
	काष्ठा mdp5_lm_instance instances[MAX_BASES];
	uपूर्णांक32_t nb_stages;		/* number of stages per blender */
	uपूर्णांक32_t max_width;		/* Maximum output resolution */
	uपूर्णांक32_t max_height;
पूर्ण;

काष्ठा mdp5_pipe_block अणु
	MDP5_SUB_BLOCK_DEFINITION;
	uपूर्णांक32_t caps;			/* pipe capabilities */
पूर्ण;

काष्ठा mdp5_ctl_block अणु
	MDP5_SUB_BLOCK_DEFINITION;
	uपूर्णांक32_t flush_hw_mask;		/* FLUSH रेजिस्टर's hardware mask */
पूर्ण;

काष्ठा mdp5_smp_block अणु
	पूर्णांक mmb_count;			/* number of SMP MMBs */
	पूर्णांक mmb_size;			/* MMB: size in bytes */
	uपूर्णांक32_t clients[MAX_CLIENTS];	/* SMP port allocation /pipe */
	mdp5_smp_state_t reserved_state;/* SMP MMBs अटलally allocated */
	uपूर्णांक8_t reserved[MAX_CLIENTS];	/* # of MMBs allocated per client */
पूर्ण;

काष्ठा mdp5_mdp_block अणु
	MDP5_SUB_BLOCK_DEFINITION;
	uपूर्णांक32_t caps;			/* MDP capabilities: MDP_CAP_xxx bits */
पूर्ण;

#घोषणा MDP5_INTF_NUM_MAX	5

काष्ठा mdp5_पूर्णांकf_block अणु
	uपूर्णांक32_t base[MAX_BASES];
	u32 connect[MDP5_INTF_NUM_MAX]; /* array of क्रमागत mdp5_पूर्णांकf_type */
पूर्ण;

काष्ठा mdp5_cfg_hw अणु
	अक्षर  *name;

	काष्ठा mdp5_mdp_block mdp;
	काष्ठा mdp5_smp_block smp;
	काष्ठा mdp5_ctl_block ctl;
	काष्ठा mdp5_pipe_block pipe_vig;
	काष्ठा mdp5_pipe_block pipe_rgb;
	काष्ठा mdp5_pipe_block pipe_dma;
	काष्ठा mdp5_pipe_block pipe_cursor;
	काष्ठा mdp5_lm_block  lm;
	काष्ठा mdp5_sub_block dspp;
	काष्ठा mdp5_sub_block ad;
	काष्ठा mdp5_sub_block pp;
	काष्ठा mdp5_sub_block dsc;
	काष्ठा mdp5_sub_block cdm;
	काष्ठा mdp5_पूर्णांकf_block पूर्णांकf;

	uपूर्णांक32_t max_clk;
पूर्ण;

/* platक्रमm config data (ie. from DT, or pdata) */
काष्ठा mdp5_cfg_platक्रमm अणु
	काष्ठा iommu_करोमुख्य *iommu;
पूर्ण;

काष्ठा mdp5_cfg अणु
	स्थिर काष्ठा mdp5_cfg_hw *hw;
	काष्ठा mdp5_cfg_platक्रमm platक्रमm;
पूर्ण;

काष्ठा mdp5_kms;
काष्ठा mdp5_cfg_handler;

स्थिर काष्ठा mdp5_cfg_hw *mdp5_cfg_get_hw_config(काष्ठा mdp5_cfg_handler *cfg_hnd);
काष्ठा mdp5_cfg *mdp5_cfg_get_config(काष्ठा mdp5_cfg_handler *cfg_hnd);
पूर्णांक mdp5_cfg_get_hw_rev(काष्ठा mdp5_cfg_handler *cfg_hnd);

#घोषणा mdp5_cfg_पूर्णांकf_is_भव(पूर्णांकf_type) (अणु	\
	typeof(पूर्णांकf_type) __val = (पूर्णांकf_type);	\
	(__val) >= INTF_VIRTUAL ? true : false; पूर्ण)

काष्ठा mdp5_cfg_handler *mdp5_cfg_init(काष्ठा mdp5_kms *mdp5_kms,
		uपूर्णांक32_t major, uपूर्णांक32_t minor);
व्योम mdp5_cfg_destroy(काष्ठा mdp5_cfg_handler *cfg_hnd);

#पूर्ण_अगर /* __MDP5_CFG_H__ */
