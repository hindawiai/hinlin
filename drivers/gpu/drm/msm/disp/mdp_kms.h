<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MDP_KMS_H__
#घोषणा __MDP_KMS_H__

#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "msm_drv.h"
#समावेश "msm_kms.h"
#समावेश "mdp_common.xml.h"

काष्ठा mdp_kms;

काष्ठा mdp_kms_funcs अणु
	काष्ठा msm_kms_funcs base;
	व्योम (*set_irqmask)(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t irqmask,
		uपूर्णांक32_t old_irqmask);
पूर्ण;

काष्ठा mdp_kms अणु
	काष्ठा msm_kms base;

	स्थिर काष्ठा mdp_kms_funcs *funcs;

	/* irq handling: */
	bool in_irq;
	काष्ठा list_head irq_list;    /* list of mdp4_irq */
	uपूर्णांक32_t vblank_mask;         /* irq bits set क्रम userspace vblank */
	uपूर्णांक32_t cur_irq_mask;        /* current irq mask */
पूर्ण;
#घोषणा to_mdp_kms(x) container_of(x, काष्ठा mdp_kms, base)

अटल अंतरभूत पूर्णांक mdp_kms_init(काष्ठा mdp_kms *mdp_kms,
		स्थिर काष्ठा mdp_kms_funcs *funcs)
अणु
	mdp_kms->funcs = funcs;
	INIT_LIST_HEAD(&mdp_kms->irq_list);
	वापस msm_kms_init(&mdp_kms->base, &funcs->base);
पूर्ण

अटल अंतरभूत व्योम mdp_kms_destroy(काष्ठा mdp_kms *mdp_kms)
अणु
	msm_kms_destroy(&mdp_kms->base);
पूर्ण

/*
 * irq helpers:
 */

/* For transiently रेजिस्टरing क्रम dअगरferent MDP irqs that various parts
 * of the KMS code need during setup/configuration.  These are not
 * necessarily the same as what drm_vblank_get/put() are requesting, and
 * the hysteresis in drm_vblank_put() is not necessarily desirable क्रम
 * पूर्णांकernal housekeeping related irq usage.
 */
काष्ठा mdp_irq अणु
	काष्ठा list_head node;
	uपूर्णांक32_t irqmask;
	bool रेजिस्टरed;
	व्योम (*irq)(काष्ठा mdp_irq *irq, uपूर्णांक32_t irqstatus);
पूर्ण;

व्योम mdp_dispatch_irqs(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t status);
व्योम mdp_update_vblank_mask(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t mask, bool enable);
व्योम mdp_irq_रुको(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t irqmask);
व्योम mdp_irq_रेजिस्टर(काष्ठा mdp_kms *mdp_kms, काष्ठा mdp_irq *irq);
व्योम mdp_irq_unरेजिस्टर(काष्ठा mdp_kms *mdp_kms, काष्ठा mdp_irq *irq);
व्योम mdp_irq_update(काष्ठा mdp_kms *mdp_kms);

/*
 * pixel क्रमmat helpers:
 */

काष्ठा mdp_क्रमmat अणु
	काष्ठा msm_क्रमmat base;
	क्रमागत mdp_bpc bpc_r, bpc_g, bpc_b;
	क्रमागत mdp_bpc_alpha bpc_a;
	uपूर्णांक8_t unpack[4];
	bool alpha_enable, unpack_tight;
	uपूर्णांक8_t cpp, unpack_count;
	क्रमागत mdp_fetch_type fetch_type;
	क्रमागत mdp_chroma_samp_type chroma_sample;
	bool is_yuv;
पूर्ण;
#घोषणा to_mdp_क्रमmat(x) container_of(x, काष्ठा mdp_क्रमmat, base)
#घोषणा MDP_FORMAT_IS_YUV(mdp_क्रमmat) ((mdp_क्रमmat)->is_yuv)

uपूर्णांक32_t mdp_get_क्रमmats(uपूर्णांक32_t *क्रमmats, uपूर्णांक32_t max_क्रमmats, bool rgb_only);
स्थिर काष्ठा msm_क्रमmat *mdp_get_क्रमmat(काष्ठा msm_kms *kms, uपूर्णांक32_t क्रमmat, uपूर्णांक64_t modअगरier);

/* MDP capabilities */
#घोषणा MDP_CAP_SMP		BIT(0)	/* Shared Memory Pool                 */
#घोषणा MDP_CAP_DSC		BIT(1)	/* VESA Display Stream Compression    */
#घोषणा MDP_CAP_CDM		BIT(2)	/* Chroma Down Module (HDMI 2.0 YUV)  */
#घोषणा MDP_CAP_SRC_SPLIT	BIT(3)	/* Source Split of SSPPs */

/* MDP pipe capabilities */
#घोषणा MDP_PIPE_CAP_HFLIP			BIT(0)
#घोषणा MDP_PIPE_CAP_VFLIP			BIT(1)
#घोषणा MDP_PIPE_CAP_SCALE			BIT(2)
#घोषणा MDP_PIPE_CAP_CSC			BIT(3)
#घोषणा MDP_PIPE_CAP_DECIMATION			BIT(4)
#घोषणा MDP_PIPE_CAP_SW_PIX_EXT			BIT(5)
#घोषणा MDP_PIPE_CAP_CURSOR			BIT(6)

/* MDP layer mixer caps */
#घोषणा MDP_LM_CAP_DISPLAY			BIT(0)
#घोषणा MDP_LM_CAP_WB				BIT(1)
#घोषणा MDP_LM_CAP_PAIR				BIT(2)

अटल अंतरभूत bool pipe_supports_yuv(uपूर्णांक32_t pipe_caps)
अणु
	वापस (pipe_caps & MDP_PIPE_CAP_SCALE) &&
		(pipe_caps & MDP_PIPE_CAP_CSC);
पूर्ण

क्रमागत csc_type अणु
	CSC_RGB2RGB = 0,
	CSC_YUV2RGB,
	CSC_RGB2YUV,
	CSC_YUV2YUV,
	CSC_MAX
पूर्ण;

काष्ठा csc_cfg अणु
	क्रमागत csc_type type;
	uपूर्णांक32_t matrix[9];
	uपूर्णांक32_t pre_bias[3];
	uपूर्णांक32_t post_bias[3];
	uपूर्णांक32_t pre_clamp[6];
	uपूर्णांक32_t post_clamp[6];
पूर्ण;

काष्ठा csc_cfg *mdp_get_शेष_csc_cfg(क्रमागत csc_type);

#पूर्ण_अगर /* __MDP_KMS_H__ */
