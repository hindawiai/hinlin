<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctsrc.c
 *
 * @Brief
 * This file contains the implementation of the Sample Rate Convertor
 * resource management object.
 *
 * @Author	Liu Chun
 * @Date 	May 13 2008
 */

#समावेश "ctsrc.h"
#समावेश "cthardware.h"
#समावेश <linux/slab.h>

#घोषणा SRC_RESOURCE_NUM	256
#घोषणा SRCIMP_RESOURCE_NUM	256

अटल अचिन्हित पूर्णांक conj_mask;

अटल पूर्णांक src_शेष_config_memrd(काष्ठा src *src);
अटल पूर्णांक src_शेष_config_memwr(काष्ठा src *src);
अटल पूर्णांक src_शेष_config_arcrw(काष्ठा src *src);

अटल पूर्णांक (*src_शेष_config[3])(काष्ठा src *) = अणु
	[MEMRD] = src_शेष_config_memrd,
	[MEMWR] = src_शेष_config_memwr,
	[ARCRW] = src_शेष_config_arcrw
पूर्ण;

अटल पूर्णांक src_set_state(काष्ठा src *src, अचिन्हित पूर्णांक state)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_state(src->rsc.ctrl_blk, state);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_bm(काष्ठा src *src, अचिन्हित पूर्णांक bm)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_bm(src->rsc.ctrl_blk, bm);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_sf(काष्ठा src *src, अचिन्हित पूर्णांक sf)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_sf(src->rsc.ctrl_blk, sf);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_pm(काष्ठा src *src, अचिन्हित पूर्णांक pm)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_pm(src->rsc.ctrl_blk, pm);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_rom(काष्ठा src *src, अचिन्हित पूर्णांक rom)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_rom(src->rsc.ctrl_blk, rom);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_vo(काष्ठा src *src, अचिन्हित पूर्णांक vo)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_vo(src->rsc.ctrl_blk, vo);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_st(काष्ठा src *src, अचिन्हित पूर्णांक st)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_st(src->rsc.ctrl_blk, st);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_bp(काष्ठा src *src, अचिन्हित पूर्णांक bp)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_bp(src->rsc.ctrl_blk, bp);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_cisz(काष्ठा src *src, अचिन्हित पूर्णांक cisz)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_cisz(src->rsc.ctrl_blk, cisz);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_ca(काष्ठा src *src, अचिन्हित पूर्णांक ca)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_ca(src->rsc.ctrl_blk, ca);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_sa(काष्ठा src *src, अचिन्हित पूर्णांक sa)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_sa(src->rsc.ctrl_blk, sa);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_la(काष्ठा src *src, अचिन्हित पूर्णांक la)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_la(src->rsc.ctrl_blk, la);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_pitch(काष्ठा src *src, अचिन्हित पूर्णांक pitch)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_pitch(src->rsc.ctrl_blk, pitch);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_clear_zbufs(काष्ठा src *src)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	hw->src_set_clear_zbufs(src->rsc.ctrl_blk, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक src_commit_ग_लिखो(काष्ठा src *src)
अणु
	काष्ठा hw *hw;
	पूर्णांक i;
	अचिन्हित पूर्णांक dirty = 0;

	hw = src->rsc.hw;
	src->rsc.ops->master(&src->rsc);
	अगर (src->rsc.msr > 1) अणु
		/* Save dirty flags क्रम conjugate resource programming */
		dirty = hw->src_get_dirty(src->rsc.ctrl_blk) & conj_mask;
	पूर्ण
	hw->src_commit_ग_लिखो(hw, src->rsc.ops->index(&src->rsc),
						src->rsc.ctrl_blk);

	/* Program conjugate parameter mixer resources */
	अगर (MEMWR == src->mode)
		वापस 0;

	क्रम (i = 1; i < src->rsc.msr; i++) अणु
		src->rsc.ops->next_conj(&src->rsc);
		hw->src_set_dirty(src->rsc.ctrl_blk, dirty);
		hw->src_commit_ग_लिखो(hw, src->rsc.ops->index(&src->rsc),
							src->rsc.ctrl_blk);
	पूर्ण
	src->rsc.ops->master(&src->rsc);

	वापस 0;
पूर्ण

अटल पूर्णांक src_get_ca(काष्ठा src *src)
अणु
	काष्ठा hw *hw;

	hw = src->rsc.hw;
	वापस hw->src_get_ca(hw, src->rsc.ops->index(&src->rsc),
						src->rsc.ctrl_blk);
पूर्ण

अटल पूर्णांक src_init(काष्ठा src *src)
अणु
	src_शेष_config[src->mode](src);

	वापस 0;
पूर्ण

अटल काष्ठा src *src_next_पूर्णांकerleave(काष्ठा src *src)
अणु
	वापस src->पूर्णांकlv;
पूर्ण

अटल पूर्णांक src_शेष_config_memrd(काष्ठा src *src)
अणु
	काष्ठा hw *hw = src->rsc.hw;
	अचिन्हित पूर्णांक rsr, msr;

	hw->src_set_state(src->rsc.ctrl_blk, SRC_STATE_OFF);
	hw->src_set_bm(src->rsc.ctrl_blk, 1);
	क्रम (rsr = 0, msr = src->rsc.msr; msr > 1; msr >>= 1)
		rsr++;

	hw->src_set_rsr(src->rsc.ctrl_blk, rsr);
	hw->src_set_sf(src->rsc.ctrl_blk, SRC_SF_S16);
	hw->src_set_wr(src->rsc.ctrl_blk, 0);
	hw->src_set_pm(src->rsc.ctrl_blk, 0);
	hw->src_set_rom(src->rsc.ctrl_blk, 0);
	hw->src_set_vo(src->rsc.ctrl_blk, 0);
	hw->src_set_st(src->rsc.ctrl_blk, 0);
	hw->src_set_ilsz(src->rsc.ctrl_blk, src->multi - 1);
	hw->src_set_cisz(src->rsc.ctrl_blk, 0x80);
	hw->src_set_sa(src->rsc.ctrl_blk, 0x0);
	hw->src_set_la(src->rsc.ctrl_blk, 0x1000);
	hw->src_set_ca(src->rsc.ctrl_blk, 0x80);
	hw->src_set_pitch(src->rsc.ctrl_blk, 0x1000000);
	hw->src_set_clear_zbufs(src->rsc.ctrl_blk, 1);

	src->rsc.ops->master(&src->rsc);
	hw->src_commit_ग_लिखो(hw, src->rsc.ops->index(&src->rsc),
						src->rsc.ctrl_blk);

	क्रम (msr = 1; msr < src->rsc.msr; msr++) अणु
		src->rsc.ops->next_conj(&src->rsc);
		hw->src_set_pitch(src->rsc.ctrl_blk, 0x1000000);
		hw->src_commit_ग_लिखो(hw, src->rsc.ops->index(&src->rsc),
							src->rsc.ctrl_blk);
	पूर्ण
	src->rsc.ops->master(&src->rsc);

	वापस 0;
पूर्ण

अटल पूर्णांक src_शेष_config_memwr(काष्ठा src *src)
अणु
	काष्ठा hw *hw = src->rsc.hw;

	hw->src_set_state(src->rsc.ctrl_blk, SRC_STATE_OFF);
	hw->src_set_bm(src->rsc.ctrl_blk, 1);
	hw->src_set_rsr(src->rsc.ctrl_blk, 0);
	hw->src_set_sf(src->rsc.ctrl_blk, SRC_SF_S16);
	hw->src_set_wr(src->rsc.ctrl_blk, 1);
	hw->src_set_pm(src->rsc.ctrl_blk, 0);
	hw->src_set_rom(src->rsc.ctrl_blk, 0);
	hw->src_set_vo(src->rsc.ctrl_blk, 0);
	hw->src_set_st(src->rsc.ctrl_blk, 0);
	hw->src_set_ilsz(src->rsc.ctrl_blk, 0);
	hw->src_set_cisz(src->rsc.ctrl_blk, 0x80);
	hw->src_set_sa(src->rsc.ctrl_blk, 0x0);
	hw->src_set_la(src->rsc.ctrl_blk, 0x1000);
	hw->src_set_ca(src->rsc.ctrl_blk, 0x80);
	hw->src_set_pitch(src->rsc.ctrl_blk, 0x1000000);
	hw->src_set_clear_zbufs(src->rsc.ctrl_blk, 1);

	src->rsc.ops->master(&src->rsc);
	hw->src_commit_ग_लिखो(hw, src->rsc.ops->index(&src->rsc),
						src->rsc.ctrl_blk);

	वापस 0;
पूर्ण

अटल पूर्णांक src_शेष_config_arcrw(काष्ठा src *src)
अणु
	काष्ठा hw *hw = src->rsc.hw;
	अचिन्हित पूर्णांक rsr, msr;
	अचिन्हित पूर्णांक dirty;

	hw->src_set_state(src->rsc.ctrl_blk, SRC_STATE_OFF);
	hw->src_set_bm(src->rsc.ctrl_blk, 0);
	क्रम (rsr = 0, msr = src->rsc.msr; msr > 1; msr >>= 1)
		rsr++;

	hw->src_set_rsr(src->rsc.ctrl_blk, rsr);
	hw->src_set_sf(src->rsc.ctrl_blk, SRC_SF_F32);
	hw->src_set_wr(src->rsc.ctrl_blk, 0);
	hw->src_set_pm(src->rsc.ctrl_blk, 0);
	hw->src_set_rom(src->rsc.ctrl_blk, 0);
	hw->src_set_vo(src->rsc.ctrl_blk, 0);
	hw->src_set_st(src->rsc.ctrl_blk, 0);
	hw->src_set_ilsz(src->rsc.ctrl_blk, 0);
	hw->src_set_cisz(src->rsc.ctrl_blk, 0x80);
	hw->src_set_sa(src->rsc.ctrl_blk, 0x0);
	/*hw->src_set_sa(src->rsc.ctrl_blk, 0x100);*/
	hw->src_set_la(src->rsc.ctrl_blk, 0x1000);
	/*hw->src_set_la(src->rsc.ctrl_blk, 0x03ffffe0);*/
	hw->src_set_ca(src->rsc.ctrl_blk, 0x80);
	hw->src_set_pitch(src->rsc.ctrl_blk, 0x1000000);
	hw->src_set_clear_zbufs(src->rsc.ctrl_blk, 1);

	dirty = hw->src_get_dirty(src->rsc.ctrl_blk);
	src->rsc.ops->master(&src->rsc);
	क्रम (msr = 0; msr < src->rsc.msr; msr++) अणु
		hw->src_set_dirty(src->rsc.ctrl_blk, dirty);
		hw->src_commit_ग_लिखो(hw, src->rsc.ops->index(&src->rsc),
							src->rsc.ctrl_blk);
		src->rsc.ops->next_conj(&src->rsc);
	पूर्ण
	src->rsc.ops->master(&src->rsc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा src_rsc_ops src_rsc_ops = अणु
	.set_state		= src_set_state,
	.set_bm			= src_set_bm,
	.set_sf			= src_set_sf,
	.set_pm			= src_set_pm,
	.set_rom		= src_set_rom,
	.set_vo			= src_set_vo,
	.set_st			= src_set_st,
	.set_bp			= src_set_bp,
	.set_cisz		= src_set_cisz,
	.set_ca			= src_set_ca,
	.set_sa			= src_set_sa,
	.set_la			= src_set_la,
	.set_pitch		= src_set_pitch,
	.set_clr_zbufs		= src_set_clear_zbufs,
	.commit_ग_लिखो		= src_commit_ग_लिखो,
	.get_ca			= src_get_ca,
	.init			= src_init,
	.next_पूर्णांकerleave	= src_next_पूर्णांकerleave,
पूर्ण;

अटल पूर्णांक
src_rsc_init(काष्ठा src *src, u32 idx,
	     स्थिर काष्ठा src_desc *desc, काष्ठा src_mgr *mgr)
अणु
	पूर्णांक err;
	पूर्णांक i, n;
	काष्ठा src *p;

	n = (MEMRD == desc->mode) ? desc->multi : 1;
	क्रम (i = 0, p = src; i < n; i++, p++) अणु
		err = rsc_init(&p->rsc, idx + i, SRC, desc->msr, mgr->mgr.hw);
		अगर (err)
			जाओ error1;

		/* Initialize src specअगरic rsc operations */
		p->ops = &src_rsc_ops;
		p->multi = (0 == i) ? desc->multi : 1;
		p->mode = desc->mode;
		src_शेष_config[desc->mode](p);
		mgr->src_enable(mgr, p);
		p->पूर्णांकlv = p + 1;
	पूर्ण
	(--p)->पूर्णांकlv = शून्य;	/* Set @पूर्णांकlv of the last SRC to शून्य */

	mgr->commit_ग_लिखो(mgr);

	वापस 0;

error1:
	क्रम (i--, p--; i >= 0; i--, p--) अणु
		mgr->src_disable(mgr, p);
		rsc_uninit(&p->rsc);
	पूर्ण
	mgr->commit_ग_लिखो(mgr);
	वापस err;
पूर्ण

अटल पूर्णांक src_rsc_uninit(काष्ठा src *src, काष्ठा src_mgr *mgr)
अणु
	पूर्णांक i, n;
	काष्ठा src *p;

	n = (MEMRD == src->mode) ? src->multi : 1;
	क्रम (i = 0, p = src; i < n; i++, p++) अणु
		mgr->src_disable(mgr, p);
		rsc_uninit(&p->rsc);
		p->multi = 0;
		p->ops = शून्य;
		p->mode = NUM_SRCMODES;
		p->पूर्णांकlv = शून्य;
	पूर्ण
	mgr->commit_ग_लिखो(mgr);

	वापस 0;
पूर्ण

अटल पूर्णांक
get_src_rsc(काष्ठा src_mgr *mgr, स्थिर काष्ठा src_desc *desc, काष्ठा src **rsrc)
अणु
	अचिन्हित पूर्णांक idx = SRC_RESOURCE_NUM;
	पूर्णांक err;
	काष्ठा src *src;
	अचिन्हित दीर्घ flags;

	*rsrc = शून्य;

	/* Check whether there are sufficient src resources to meet request. */
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	अगर (MEMRD == desc->mode)
		err = mgr_get_resource(&mgr->mgr, desc->multi, &idx);
	अन्यथा
		err = mgr_get_resource(&mgr->mgr, 1, &idx);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	अगर (err) अणु
		dev_err(mgr->card->dev,
			"Can't meet SRC resource request!\n");
		वापस err;
	पूर्ण

	/* Allocate mem क्रम master src resource */
	अगर (MEMRD == desc->mode)
		src = kसुस्मृति(desc->multi, माप(*src), GFP_KERNEL);
	अन्यथा
		src = kzalloc(माप(*src), GFP_KERNEL);

	अगर (!src) अणु
		err = -ENOMEM;
		जाओ error1;
	पूर्ण

	err = src_rsc_init(src, idx, desc, mgr);
	अगर (err)
		जाओ error2;

	*rsrc = src;

	वापस 0;

error2:
	kमुक्त(src);
error1:
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	अगर (MEMRD == desc->mode)
		mgr_put_resource(&mgr->mgr, desc->multi, idx);
	अन्यथा
		mgr_put_resource(&mgr->mgr, 1, idx);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक put_src_rsc(काष्ठा src_mgr *mgr, काष्ठा src *src)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mgr->mgr_lock, flags);
	src->rsc.ops->master(&src->rsc);
	अगर (MEMRD == src->mode)
		mgr_put_resource(&mgr->mgr, src->multi,
				 src->rsc.ops->index(&src->rsc));
	अन्यथा
		mgr_put_resource(&mgr->mgr, 1, src->rsc.ops->index(&src->rsc));

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	src_rsc_uninit(src, mgr);
	kमुक्त(src);

	वापस 0;
पूर्ण

अटल पूर्णांक src_enable_s(काष्ठा src_mgr *mgr, काष्ठा src *src)
अणु
	काष्ठा hw *hw = mgr->mgr.hw;
	पूर्णांक i;

	src->rsc.ops->master(&src->rsc);
	क्रम (i = 0; i < src->rsc.msr; i++) अणु
		hw->src_mgr_enbs_src(mgr->mgr.ctrl_blk,
				     src->rsc.ops->index(&src->rsc));
		src->rsc.ops->next_conj(&src->rsc);
	पूर्ण
	src->rsc.ops->master(&src->rsc);

	वापस 0;
पूर्ण

अटल पूर्णांक src_enable(काष्ठा src_mgr *mgr, काष्ठा src *src)
अणु
	काष्ठा hw *hw = mgr->mgr.hw;
	पूर्णांक i;

	src->rsc.ops->master(&src->rsc);
	क्रम (i = 0; i < src->rsc.msr; i++) अणु
		hw->src_mgr_enb_src(mgr->mgr.ctrl_blk,
				    src->rsc.ops->index(&src->rsc));
		src->rsc.ops->next_conj(&src->rsc);
	पूर्ण
	src->rsc.ops->master(&src->rsc);

	वापस 0;
पूर्ण

अटल पूर्णांक src_disable(काष्ठा src_mgr *mgr, काष्ठा src *src)
अणु
	काष्ठा hw *hw = mgr->mgr.hw;
	पूर्णांक i;

	src->rsc.ops->master(&src->rsc);
	क्रम (i = 0; i < src->rsc.msr; i++) अणु
		hw->src_mgr_dsb_src(mgr->mgr.ctrl_blk,
				    src->rsc.ops->index(&src->rsc));
		src->rsc.ops->next_conj(&src->rsc);
	पूर्ण
	src->rsc.ops->master(&src->rsc);

	वापस 0;
पूर्ण

अटल पूर्णांक src_mgr_commit_ग_लिखो(काष्ठा src_mgr *mgr)
अणु
	काष्ठा hw *hw = mgr->mgr.hw;

	hw->src_mgr_commit_ग_लिखो(hw, mgr->mgr.ctrl_blk);

	वापस 0;
पूर्ण

पूर्णांक src_mgr_create(काष्ठा hw *hw, काष्ठा src_mgr **rsrc_mgr)
अणु
	पूर्णांक err, i;
	काष्ठा src_mgr *src_mgr;

	*rsrc_mgr = शून्य;
	src_mgr = kzalloc(माप(*src_mgr), GFP_KERNEL);
	अगर (!src_mgr)
		वापस -ENOMEM;

	err = rsc_mgr_init(&src_mgr->mgr, SRC, SRC_RESOURCE_NUM, hw);
	अगर (err)
		जाओ error1;

	spin_lock_init(&src_mgr->mgr_lock);
	conj_mask = hw->src_dirty_conj_mask();

	src_mgr->get_src = get_src_rsc;
	src_mgr->put_src = put_src_rsc;
	src_mgr->src_enable_s = src_enable_s;
	src_mgr->src_enable = src_enable;
	src_mgr->src_disable = src_disable;
	src_mgr->commit_ग_लिखो = src_mgr_commit_ग_लिखो;
	src_mgr->card = hw->card;

	/* Disable all SRC resources. */
	क्रम (i = 0; i < 256; i++)
		hw->src_mgr_dsb_src(src_mgr->mgr.ctrl_blk, i);

	hw->src_mgr_commit_ग_लिखो(hw, src_mgr->mgr.ctrl_blk);

	*rsrc_mgr = src_mgr;

	वापस 0;

error1:
	kमुक्त(src_mgr);
	वापस err;
पूर्ण

पूर्णांक src_mgr_destroy(काष्ठा src_mgr *src_mgr)
अणु
	rsc_mgr_uninit(&src_mgr->mgr);
	kमुक्त(src_mgr);

	वापस 0;
पूर्ण

/* SRCIMP resource manager operations */

अटल पूर्णांक srcimp_master(काष्ठा rsc *rsc)
अणु
	rsc->conj = 0;
	वापस rsc->idx = container_of(rsc, काष्ठा srcimp, rsc)->idx[0];
पूर्ण

अटल पूर्णांक srcimp_next_conj(काष्ठा rsc *rsc)
अणु
	rsc->conj++;
	वापस container_of(rsc, काष्ठा srcimp, rsc)->idx[rsc->conj];
पूर्ण

अटल पूर्णांक srcimp_index(स्थिर काष्ठा rsc *rsc)
अणु
	वापस container_of(rsc, काष्ठा srcimp, rsc)->idx[rsc->conj];
पूर्ण

अटल स्थिर काष्ठा rsc_ops srcimp_basic_rsc_ops = अणु
	.master		= srcimp_master,
	.next_conj	= srcimp_next_conj,
	.index		= srcimp_index,
	.output_slot	= शून्य,
पूर्ण;

अटल पूर्णांक srcimp_map(काष्ठा srcimp *srcimp, काष्ठा src *src, काष्ठा rsc *input)
अणु
	काष्ठा imapper *entry;
	पूर्णांक i;

	srcimp->rsc.ops->master(&srcimp->rsc);
	src->rsc.ops->master(&src->rsc);
	input->ops->master(input);

	/* Program master and conjugate resources */
	क्रम (i = 0; i < srcimp->rsc.msr; i++) अणु
		entry = &srcimp->imappers[i];
		entry->slot = input->ops->output_slot(input);
		entry->user = src->rsc.ops->index(&src->rsc);
		entry->addr = srcimp->rsc.ops->index(&srcimp->rsc);
		srcimp->mgr->imap_add(srcimp->mgr, entry);
		srcimp->mapped |= (0x1 << i);

		srcimp->rsc.ops->next_conj(&srcimp->rsc);
		input->ops->next_conj(input);
	पूर्ण

	srcimp->rsc.ops->master(&srcimp->rsc);
	input->ops->master(input);

	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_unmap(काष्ठा srcimp *srcimp)
अणु
	पूर्णांक i;

	/* Program master and conjugate resources */
	क्रम (i = 0; i < srcimp->rsc.msr; i++) अणु
		अगर (srcimp->mapped & (0x1 << i)) अणु
			srcimp->mgr->imap_delete(srcimp->mgr,
						 &srcimp->imappers[i]);
			srcimp->mapped &= ~(0x1 << i);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा srcimp_rsc_ops srcimp_ops = अणु
	.map = srcimp_map,
	.unmap = srcimp_unmap
पूर्ण;

अटल पूर्णांक srcimp_rsc_init(काष्ठा srcimp *srcimp,
			   स्थिर काष्ठा srcimp_desc *desc,
			   काष्ठा srcimp_mgr *mgr)
अणु
	पूर्णांक err;

	err = rsc_init(&srcimp->rsc, srcimp->idx[0],
		       SRCIMP, desc->msr, mgr->mgr.hw);
	अगर (err)
		वापस err;

	/* Reserve memory क्रम imapper nodes */
	srcimp->imappers = kसुस्मृति(desc->msr, माप(काष्ठा imapper),
				   GFP_KERNEL);
	अगर (!srcimp->imappers) अणु
		err = -ENOMEM;
		जाओ error1;
	पूर्ण

	/* Set srcimp specअगरic operations */
	srcimp->rsc.ops = &srcimp_basic_rsc_ops;
	srcimp->ops = &srcimp_ops;
	srcimp->mgr = mgr;

	srcimp->rsc.ops->master(&srcimp->rsc);

	वापस 0;

error1:
	rsc_uninit(&srcimp->rsc);
	वापस err;
पूर्ण

अटल पूर्णांक srcimp_rsc_uninit(काष्ठा srcimp *srcimp)
अणु
	kमुक्त(srcimp->imappers);
	srcimp->imappers = शून्य;
	srcimp->ops = शून्य;
	srcimp->mgr = शून्य;
	rsc_uninit(&srcimp->rsc);

	वापस 0;
पूर्ण

अटल पूर्णांक get_srcimp_rsc(काष्ठा srcimp_mgr *mgr,
			  स्थिर काष्ठा srcimp_desc *desc,
			  काष्ठा srcimp **rsrcimp)
अणु
	पूर्णांक err, i;
	अचिन्हित पूर्णांक idx;
	काष्ठा srcimp *srcimp;
	अचिन्हित दीर्घ flags;

	*rsrcimp = शून्य;

	/* Allocate mem क्रम SRCIMP resource */
	srcimp = kzalloc(माप(*srcimp), GFP_KERNEL);
	अगर (!srcimp)
		वापस -ENOMEM;

	/* Check whether there are sufficient SRCIMP resources. */
	err = 0;
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	क्रम (i = 0; i < desc->msr; i++) अणु
		err = mgr_get_resource(&mgr->mgr, 1, &idx);
		अगर (err)
			अवरोध;

		srcimp->idx[i] = idx;
	पूर्ण
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	अगर (err) अणु
		dev_err(mgr->card->dev,
			"Can't meet SRCIMP resource request!\n");
		जाओ error1;
	पूर्ण

	err = srcimp_rsc_init(srcimp, desc, mgr);
	अगर (err)
		जाओ error1;

	*rsrcimp = srcimp;

	वापस 0;

error1:
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	क्रम (i--; i >= 0; i--)
		mgr_put_resource(&mgr->mgr, 1, srcimp->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	kमुक्त(srcimp);
	वापस err;
पूर्ण

अटल पूर्णांक put_srcimp_rsc(काष्ठा srcimp_mgr *mgr, काष्ठा srcimp *srcimp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&mgr->mgr_lock, flags);
	क्रम (i = 0; i < srcimp->rsc.msr; i++)
		mgr_put_resource(&mgr->mgr, 1, srcimp->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	srcimp_rsc_uninit(srcimp);
	kमुक्त(srcimp);

	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_map_op(व्योम *data, काष्ठा imapper *entry)
अणु
	काष्ठा rsc_mgr *mgr = &((काष्ठा srcimp_mgr *)data)->mgr;
	काष्ठा hw *hw = mgr->hw;

	hw->srcimp_mgr_set_imaparc(mgr->ctrl_blk, entry->slot);
	hw->srcimp_mgr_set_imapuser(mgr->ctrl_blk, entry->user);
	hw->srcimp_mgr_set_imapnxt(mgr->ctrl_blk, entry->next);
	hw->srcimp_mgr_set_imapaddr(mgr->ctrl_blk, entry->addr);
	hw->srcimp_mgr_commit_ग_लिखो(mgr->hw, mgr->ctrl_blk);

	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_imap_add(काष्ठा srcimp_mgr *mgr, काष्ठा imapper *entry)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&mgr->imap_lock, flags);
	अगर ((0 == entry->addr) && (mgr->init_imap_added)) अणु
		input_mapper_delete(&mgr->imappers,
				    mgr->init_imap, srcimp_map_op, mgr);
		mgr->init_imap_added = 0;
	पूर्ण
	err = input_mapper_add(&mgr->imappers, entry, srcimp_map_op, mgr);
	spin_unlock_irqrestore(&mgr->imap_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक srcimp_imap_delete(काष्ठा srcimp_mgr *mgr, काष्ठा imapper *entry)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&mgr->imap_lock, flags);
	err = input_mapper_delete(&mgr->imappers, entry, srcimp_map_op, mgr);
	अगर (list_empty(&mgr->imappers)) अणु
		input_mapper_add(&mgr->imappers, mgr->init_imap,
				 srcimp_map_op, mgr);
		mgr->init_imap_added = 1;
	पूर्ण
	spin_unlock_irqrestore(&mgr->imap_lock, flags);

	वापस err;
पूर्ण

पूर्णांक srcimp_mgr_create(काष्ठा hw *hw, काष्ठा srcimp_mgr **rsrcimp_mgr)
अणु
	पूर्णांक err;
	काष्ठा srcimp_mgr *srcimp_mgr;
	काष्ठा imapper *entry;

	*rsrcimp_mgr = शून्य;
	srcimp_mgr = kzalloc(माप(*srcimp_mgr), GFP_KERNEL);
	अगर (!srcimp_mgr)
		वापस -ENOMEM;

	err = rsc_mgr_init(&srcimp_mgr->mgr, SRCIMP, SRCIMP_RESOURCE_NUM, hw);
	अगर (err)
		जाओ error1;

	spin_lock_init(&srcimp_mgr->mgr_lock);
	spin_lock_init(&srcimp_mgr->imap_lock);
	INIT_LIST_HEAD(&srcimp_mgr->imappers);
	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		err = -ENOMEM;
		जाओ error2;
	पूर्ण
	entry->slot = entry->addr = entry->next = entry->user = 0;
	list_add(&entry->list, &srcimp_mgr->imappers);
	srcimp_mgr->init_imap = entry;
	srcimp_mgr->init_imap_added = 1;

	srcimp_mgr->get_srcimp = get_srcimp_rsc;
	srcimp_mgr->put_srcimp = put_srcimp_rsc;
	srcimp_mgr->imap_add = srcimp_imap_add;
	srcimp_mgr->imap_delete = srcimp_imap_delete;
	srcimp_mgr->card = hw->card;

	*rsrcimp_mgr = srcimp_mgr;

	वापस 0;

error2:
	rsc_mgr_uninit(&srcimp_mgr->mgr);
error1:
	kमुक्त(srcimp_mgr);
	वापस err;
पूर्ण

पूर्णांक srcimp_mgr_destroy(काष्ठा srcimp_mgr *srcimp_mgr)
अणु
	अचिन्हित दीर्घ flags;

	/* मुक्त src input mapper list */
	spin_lock_irqsave(&srcimp_mgr->imap_lock, flags);
	मुक्त_input_mapper_list(&srcimp_mgr->imappers);
	spin_unlock_irqrestore(&srcimp_mgr->imap_lock, flags);

	rsc_mgr_uninit(&srcimp_mgr->mgr);
	kमुक्त(srcimp_mgr);

	वापस 0;
पूर्ण
