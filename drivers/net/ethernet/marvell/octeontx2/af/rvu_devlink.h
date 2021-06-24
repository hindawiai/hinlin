<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Marvell OcteonTx2 RVU Devlink
 *
 * Copyright (C) 2020 Marvell.
 *
 */

#अगर_अघोषित RVU_DEVLINK_H
#घोषणा  RVU_DEVLINK_H

#घोषणा RVU_REPORTERS(_name)  \
अटल स्थिर काष्ठा devlink_health_reporter_ops  rvu_ ## _name ## _reporter_ops =  अणु \
	.name = #_name, \
	.recover = rvu_ ## _name ## _recover, \
	.dump = rvu_ ## _name ## _dump, \
पूर्ण

क्रमागत npa_af_rvu_health अणु
	NPA_AF_RVU_INTR,
	NPA_AF_RVU_GEN,
	NPA_AF_RVU_ERR,
	NPA_AF_RVU_RAS,
पूर्ण;

काष्ठा rvu_npa_event_ctx अणु
	u64 npa_af_rvu_पूर्णांक;
	u64 npa_af_rvu_gen;
	u64 npa_af_rvu_err;
	u64 npa_af_rvu_ras;
पूर्ण;

काष्ठा rvu_npa_health_reporters अणु
	काष्ठा rvu_npa_event_ctx *npa_event_ctx;
	काष्ठा devlink_health_reporter *rvu_hw_npa_पूर्णांकr_reporter;
	काष्ठा work_काष्ठा              पूर्णांकr_work;
	काष्ठा devlink_health_reporter *rvu_hw_npa_gen_reporter;
	काष्ठा work_काष्ठा              gen_work;
	काष्ठा devlink_health_reporter *rvu_hw_npa_err_reporter;
	काष्ठा work_काष्ठा             err_work;
	काष्ठा devlink_health_reporter *rvu_hw_npa_ras_reporter;
	काष्ठा work_काष्ठा              ras_work;
पूर्ण;

क्रमागत nix_af_rvu_health अणु
	NIX_AF_RVU_INTR,
	NIX_AF_RVU_GEN,
	NIX_AF_RVU_ERR,
	NIX_AF_RVU_RAS,
पूर्ण;

काष्ठा rvu_nix_event_ctx अणु
	u64 nix_af_rvu_पूर्णांक;
	u64 nix_af_rvu_gen;
	u64 nix_af_rvu_err;
	u64 nix_af_rvu_ras;
पूर्ण;

काष्ठा rvu_nix_health_reporters अणु
	काष्ठा rvu_nix_event_ctx *nix_event_ctx;
	काष्ठा devlink_health_reporter *rvu_hw_nix_पूर्णांकr_reporter;
	काष्ठा work_काष्ठा		पूर्णांकr_work;
	काष्ठा devlink_health_reporter *rvu_hw_nix_gen_reporter;
	काष्ठा work_काष्ठा		gen_work;
	काष्ठा devlink_health_reporter *rvu_hw_nix_err_reporter;
	काष्ठा work_काष्ठा		err_work;
	काष्ठा devlink_health_reporter *rvu_hw_nix_ras_reporter;
	काष्ठा work_काष्ठा		ras_work;
पूर्ण;

काष्ठा rvu_devlink अणु
	काष्ठा devlink *dl;
	काष्ठा rvu *rvu;
	काष्ठा workqueue_काष्ठा *devlink_wq;
	काष्ठा rvu_npa_health_reporters *rvu_npa_health_reporter;
	काष्ठा rvu_nix_health_reporters *rvu_nix_health_reporter;
पूर्ण;

/* Devlink APIs */
पूर्णांक rvu_रेजिस्टर_dl(काष्ठा rvu *rvu);
व्योम rvu_unरेजिस्टर_dl(काष्ठा rvu *rvu);

#पूर्ण_अगर /* RVU_DEVLINK_H */
