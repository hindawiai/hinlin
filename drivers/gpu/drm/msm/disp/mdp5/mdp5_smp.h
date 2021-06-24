<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MDP5_SMP_H__
#घोषणा __MDP5_SMP_H__

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "msm_drv.h"

/*
 * SMP - Shared Memory Pool:
 *
 * SMP blocks are shared between all the clients, where each plane in
 * a scanout buffer is a SMP client.  Ie. scanout of 3 plane I420 on
 * pipe VIG0 => 3 clients: VIG0_Y, VIG0_CB, VIG0_CR.
 *
 * Based on the size of the attached scanout buffer, a certain # of
 * blocks must be allocated to that client out of the shared pool.
 *
 * In some hw, some blocks are अटलally allocated क्रम certain pipes
 * and CANNOT be re-allocated (eg: MMB0 and MMB1 both tied to RGB0).
 *
 *
 * Atomic SMP State:
 *
 * On atomic updates that modअगरy SMP configuration, the state is cloned
 * (copied) and modअगरied.  For test-only, or in हालs where atomic
 * update fails (or अगर we hit ww_mutex deadlock/backoff condition) the
 * new state is simply thrown away.
 *
 * Because the SMP रेजिस्टरs are not द्विगुन buffered, updates are a
 * two step process:
 *
 * 1) in _prepare_commit() we configure things (via पढ़ो-modअगरy-ग_लिखो)
 *    क्रम the newly asचिन्हित pipes, so we करोn't take away blocks
 *    asचिन्हित to pipes that are still scanning out
 * 2) in _complete_commit(), after vblank/etc, we clear things क्रम the
 *    released clients, since at that poपूर्णांक old pipes are no दीर्घer
 *    scanning out.
 */
काष्ठा mdp5_smp_state अणु
	/* global state of what blocks are in use: */
	mdp5_smp_state_t state;

	/* per client state of what blocks they are using: */
	mdp5_smp_state_t client_state[MAX_CLIENTS];

	/* asचिन्हित pipes (hw updated at _prepare_commit()): */
	अचिन्हित दीर्घ asचिन्हित;

	/* released pipes (hw updated at _complete_commit()): */
	अचिन्हित दीर्घ released;
पूर्ण;

काष्ठा mdp5_kms;
काष्ठा mdp5_smp;

/*
 * SMP module prototypes:
 * mdp5_smp_init() वापसs a SMP @handler,
 * which is then used to call the other mdp5_smp_*(handler, ...) functions.
 */

काष्ठा mdp5_smp *mdp5_smp_init(काष्ठा mdp5_kms *mdp5_kms,
		स्थिर काष्ठा mdp5_smp_block *cfg);
व्योम  mdp5_smp_destroy(काष्ठा mdp5_smp *smp);

व्योम mdp5_smp_dump(काष्ठा mdp5_smp *smp, काष्ठा drm_prपूर्णांकer *p);

uपूर्णांक32_t mdp5_smp_calculate(काष्ठा mdp5_smp *smp,
		स्थिर काष्ठा mdp_क्रमmat *क्रमmat,
		u32 width, bool hdecim);

पूर्णांक mdp5_smp_assign(काष्ठा mdp5_smp *smp, काष्ठा mdp5_smp_state *state,
		क्रमागत mdp5_pipe pipe, uपूर्णांक32_t blkcfg);
व्योम mdp5_smp_release(काष्ठा mdp5_smp *smp, काष्ठा mdp5_smp_state *state,
		क्रमागत mdp5_pipe pipe);

व्योम mdp5_smp_prepare_commit(काष्ठा mdp5_smp *smp, काष्ठा mdp5_smp_state *state);
व्योम mdp5_smp_complete_commit(काष्ठा mdp5_smp *smp, काष्ठा mdp5_smp_state *state);

#पूर्ण_अगर /* __MDP5_SMP_H__ */
