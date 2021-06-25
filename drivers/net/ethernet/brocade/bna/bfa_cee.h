<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

#अगर_अघोषित __BFA_CEE_H__
#घोषणा __BFA_CEE_H__

#समावेश "bfa_defs_cna.h"
#समावेश "bfa_ioc.h"

प्रकार व्योम (*bfa_cee_get_attr_cbfn_t) (व्योम *dev, क्रमागत bfa_status status);
प्रकार व्योम (*bfa_cee_get_stats_cbfn_t) (व्योम *dev, क्रमागत bfa_status status);
प्रकार व्योम (*bfa_cee_reset_stats_cbfn_t) (व्योम *dev, क्रमागत bfa_status status);

काष्ठा bfa_cee_cbfn अणु
	bfa_cee_get_attr_cbfn_t    get_attr_cbfn;
	व्योम *get_attr_cbarg;
	bfa_cee_get_stats_cbfn_t   get_stats_cbfn;
	व्योम *get_stats_cbarg;
	bfa_cee_reset_stats_cbfn_t reset_stats_cbfn;
	व्योम *reset_stats_cbarg;
पूर्ण;

काष्ठा bfa_cee अणु
	व्योम *dev;
	bool get_attr_pending;
	bool get_stats_pending;
	bool reset_stats_pending;
	क्रमागत bfa_status get_attr_status;
	क्रमागत bfa_status get_stats_status;
	क्रमागत bfa_status reset_stats_status;
	काष्ठा bfa_cee_cbfn cbfn;
	काष्ठा bfa_ioc_notअगरy ioc_notअगरy;
	काष्ठा bfa_cee_attr *attr;
	काष्ठा bfa_cee_stats *stats;
	काष्ठा bfa_dma attr_dma;
	काष्ठा bfa_dma stats_dma;
	काष्ठा bfa_ioc *ioc;
	काष्ठा bfa_mbox_cmd get_cfg_mb;
	काष्ठा bfa_mbox_cmd get_stats_mb;
	काष्ठा bfa_mbox_cmd reset_stats_mb;
पूर्ण;

u32 bfa_nw_cee_meminfo(व्योम);
व्योम bfa_nw_cee_mem_claim(काष्ठा bfa_cee *cee, u8 *dma_kva,
	u64 dma_pa);
व्योम bfa_nw_cee_attach(काष्ठा bfa_cee *cee, काष्ठा bfa_ioc *ioc, व्योम *dev);
क्रमागत bfa_status bfa_nw_cee_get_attr(काष्ठा bfa_cee *cee,
				काष्ठा bfa_cee_attr *attr,
				bfa_cee_get_attr_cbfn_t cbfn, व्योम *cbarg);
#पूर्ण_अगर /* __BFA_CEE_H__ */
