<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

#अगर_अघोषित __BFA_PORT_H__
#घोषणा __BFA_PORT_H__

#समावेश "bfa_defs_svc.h"
#समावेश "bfa_ioc.h"
#समावेश "bfa_cs.h"

प्रकार व्योम (*bfa_port_stats_cbfn_t) (व्योम *dev, bfa_status_t status);
प्रकार व्योम (*bfa_port_endis_cbfn_t) (व्योम *dev, bfa_status_t status);

काष्ठा bfa_port_s अणु
	व्योम				*dev;
	काष्ठा bfa_ioc_s		*ioc;
	काष्ठा bfa_trc_mod_s		*trcmod;
	u32			msgtag;
	bfa_boolean_t			stats_busy;
	काष्ठा bfa_mbox_cmd_s		stats_mb;
	bfa_port_stats_cbfn_t		stats_cbfn;
	व्योम				*stats_cbarg;
	bfa_status_t			stats_status;
	समय64_t			stats_reset_समय;
	जोड़ bfa_port_stats_u		*stats;
	काष्ठा bfa_dma_s		stats_dma;
	bfa_boolean_t			endis_pending;
	काष्ठा bfa_mbox_cmd_s		endis_mb;
	bfa_port_endis_cbfn_t		endis_cbfn;
	व्योम				*endis_cbarg;
	bfa_status_t			endis_status;
	काष्ठा bfa_ioc_notअगरy_s		ioc_notअगरy;
	bfa_boolean_t			pbc_disabled;
	bfa_boolean_t			dport_enabled;
	काष्ठा bfa_mem_dma_s		port_dma;
पूर्ण;

#घोषणा BFA_MEM_PORT_DMA(__bfa)		(&((__bfa)->modules.port.port_dma))

व्योम	     bfa_port_attach(काष्ठा bfa_port_s *port, काष्ठा bfa_ioc_s *ioc,
				व्योम *dev, काष्ठा bfa_trc_mod_s *trcmod);
व्योम	bfa_port_notअगरy(व्योम *arg, क्रमागत bfa_ioc_event_e event);

bfa_status_t bfa_port_get_stats(काष्ठा bfa_port_s *port,
				 जोड़ bfa_port_stats_u *stats,
				 bfa_port_stats_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t bfa_port_clear_stats(काष्ठा bfa_port_s *port,
				   bfa_port_stats_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t bfa_port_enable(काष्ठा bfa_port_s *port,
			      bfa_port_endis_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t bfa_port_disable(काष्ठा bfa_port_s *port,
			       bfa_port_endis_cbfn_t cbfn, व्योम *cbarg);
u32     bfa_port_meminfo(व्योम);
व्योम	     bfa_port_mem_claim(काष्ठा bfa_port_s *port,
				 u8 *dma_kva, u64 dma_pa);
व्योम	bfa_port_set_dportenabled(काष्ठा bfa_port_s *port,
				  bfa_boolean_t enabled);

/*
 * CEE declaration
 */
प्रकार व्योम (*bfa_cee_get_attr_cbfn_t) (व्योम *dev, bfa_status_t status);
प्रकार व्योम (*bfa_cee_get_stats_cbfn_t) (व्योम *dev, bfa_status_t status);
प्रकार व्योम (*bfa_cee_reset_stats_cbfn_t) (व्योम *dev, bfa_status_t status);

काष्ठा bfa_cee_cbfn_s अणु
	bfa_cee_get_attr_cbfn_t		get_attr_cbfn;
	व्योम				*get_attr_cbarg;
	bfa_cee_get_stats_cbfn_t	get_stats_cbfn;
	व्योम				*get_stats_cbarg;
	bfa_cee_reset_stats_cbfn_t	reset_stats_cbfn;
	व्योम				*reset_stats_cbarg;
पूर्ण;

काष्ठा bfa_cee_s अणु
	व्योम *dev;
	bfa_boolean_t		get_attr_pending;
	bfa_boolean_t		get_stats_pending;
	bfa_boolean_t		reset_stats_pending;
	bfa_status_t		get_attr_status;
	bfa_status_t		get_stats_status;
	bfa_status_t		reset_stats_status;
	काष्ठा bfa_cee_cbfn_s	cbfn;
	काष्ठा bfa_ioc_notअगरy_s	ioc_notअगरy;
	काष्ठा bfa_trc_mod_s	*trcmod;
	काष्ठा bfa_cee_attr_s	*attr;
	काष्ठा bfa_cee_stats_s	*stats;
	काष्ठा bfa_dma_s	attr_dma;
	काष्ठा bfa_dma_s	stats_dma;
	काष्ठा bfa_ioc_s	*ioc;
	काष्ठा bfa_mbox_cmd_s	get_cfg_mb;
	काष्ठा bfa_mbox_cmd_s	get_stats_mb;
	काष्ठा bfa_mbox_cmd_s	reset_stats_mb;
	काष्ठा bfa_mem_dma_s	cee_dma;
पूर्ण;

#घोषणा BFA_MEM_CEE_DMA(__bfa)	(&((__bfa)->modules.cee.cee_dma))

u32	bfa_cee_meminfo(व्योम);
व्योम	bfa_cee_mem_claim(काष्ठा bfa_cee_s *cee, u8 *dma_kva, u64 dma_pa);
व्योम	bfa_cee_attach(काष्ठा bfa_cee_s *cee,
			काष्ठा bfa_ioc_s *ioc, व्योम *dev);
bfa_status_t	bfa_cee_get_attr(काष्ठा bfa_cee_s *cee,
				काष्ठा bfa_cee_attr_s *attr,
				bfa_cee_get_attr_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t	bfa_cee_get_stats(काष्ठा bfa_cee_s *cee,
				काष्ठा bfa_cee_stats_s *stats,
				bfa_cee_get_stats_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t	bfa_cee_reset_stats(काष्ठा bfa_cee_s *cee,
				bfa_cee_reset_stats_cbfn_t cbfn, व्योम *cbarg);

#पूर्ण_अगर	/* __BFA_PORT_H__ */
