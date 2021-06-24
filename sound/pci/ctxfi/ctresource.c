<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctresource.c
 *
 * @Brief
 * This file contains the implementation of some generic helper functions.
 *
 * @Author	Liu Chun
 * @Date 	May 15 2008
 */

#समावेश "ctresource.h"
#समावेश "cthardware.h"
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

#घोषणा AUDIO_SLOT_BLOCK_NUM 	256

/* Resource allocation based on bit-map management mechanism */
अटल पूर्णांक
get_resource(u8 *rscs, अचिन्हित पूर्णांक amount,
	     अचिन्हित पूर्णांक multi, अचिन्हित पूर्णांक *ridx)
अणु
	पूर्णांक i, j, k, n;

	/* Check whether there are sufficient resources to meet request. */
	क्रम (i = 0, n = multi; i < amount; i++) अणु
		j = i / 8;
		k = i % 8;
		अगर (rscs[j] & ((u8)1 << k)) अणु
			n = multi;
			जारी;
		पूर्ण
		अगर (!(--n))
			अवरोध; /* found sufficient contiguous resources */
	पूर्ण

	अगर (i >= amount) अणु
		/* Can not find sufficient contiguous resources */
		वापस -ENOENT;
	पूर्ण

	/* Mark the contiguous bits in resource bit-map as used */
	क्रम (n = multi; n > 0; n--) अणु
		j = i / 8;
		k = i % 8;
		rscs[j] |= ((u8)1 << k);
		i--;
	पूर्ण

	*ridx = i + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक put_resource(u8 *rscs, अचिन्हित पूर्णांक multi, अचिन्हित पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक i, j, k, n;

	/* Mark the contiguous bits in resource bit-map as used */
	क्रम (n = multi, i = idx; n > 0; n--) अणु
		j = i / 8;
		k = i % 8;
		rscs[j] &= ~((u8)1 << k);
		i++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mgr_get_resource(काष्ठा rsc_mgr *mgr, अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक *ridx)
अणु
	पूर्णांक err;

	अगर (n > mgr->avail)
		वापस -ENOENT;

	err = get_resource(mgr->rscs, mgr->amount, n, ridx);
	अगर (!err)
		mgr->avail -= n;

	वापस err;
पूर्ण

पूर्णांक mgr_put_resource(काष्ठा rsc_mgr *mgr, अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक idx)
अणु
	put_resource(mgr->rscs, n, idx);
	mgr->avail += n;

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित अक्षर offset_in_audio_slot_block[NUM_RSCTYP] = अणु
	/* SRC channel is at Audio Ring slot 1 every 16 slots. */
	[SRC]		= 0x1,
	[AMIXER]	= 0x4,
	[SUM]		= 0xc,
पूर्ण;

अटल पूर्णांक rsc_index(स्थिर काष्ठा rsc *rsc)
अणु
    वापस rsc->conj;
पूर्ण

अटल पूर्णांक audio_ring_slot(स्थिर काष्ठा rsc *rsc)
अणु
    वापस (rsc->conj << 4) + offset_in_audio_slot_block[rsc->type];
पूर्ण

अटल पूर्णांक rsc_next_conj(काष्ठा rsc *rsc)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; (i < 8) && (!(rsc->msr & (0x1 << i))); )
		i++;
	rsc->conj += (AUDIO_SLOT_BLOCK_NUM >> i);
	वापस rsc->conj;
पूर्ण

अटल पूर्णांक rsc_master(काष्ठा rsc *rsc)
अणु
	वापस rsc->conj = rsc->idx;
पूर्ण

अटल स्थिर काष्ठा rsc_ops rsc_generic_ops = अणु
	.index		= rsc_index,
	.output_slot	= audio_ring_slot,
	.master		= rsc_master,
	.next_conj	= rsc_next_conj,
पूर्ण;

पूर्णांक
rsc_init(काष्ठा rsc *rsc, u32 idx, क्रमागत RSCTYP type, u32 msr, काष्ठा hw *hw)
अणु
	पूर्णांक err = 0;

	rsc->idx = idx;
	rsc->conj = idx;
	rsc->type = type;
	rsc->msr = msr;
	rsc->hw = hw;
	rsc->ops = &rsc_generic_ops;
	अगर (!hw) अणु
		rsc->ctrl_blk = शून्य;
		वापस 0;
	पूर्ण

	चयन (type) अणु
	हाल SRC:
		err = hw->src_rsc_get_ctrl_blk(&rsc->ctrl_blk);
		अवरोध;
	हाल AMIXER:
		err = hw->amixer_rsc_get_ctrl_blk(&rsc->ctrl_blk);
		अवरोध;
	हाल SRCIMP:
	हाल SUM:
	हाल DAIO:
		अवरोध;
	शेष:
		dev_err(((काष्ठा hw *)hw)->card->dev,
			"Invalid resource type value %d!\n", type);
		वापस -EINVAL;
	पूर्ण

	अगर (err) अणु
		dev_err(((काष्ठा hw *)hw)->card->dev,
			"Failed to get resource control block!\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rsc_uninit(काष्ठा rsc *rsc)
अणु
	अगर ((शून्य != rsc->hw) && (शून्य != rsc->ctrl_blk)) अणु
		चयन (rsc->type) अणु
		हाल SRC:
			rsc->hw->src_rsc_put_ctrl_blk(rsc->ctrl_blk);
			अवरोध;
		हाल AMIXER:
			rsc->hw->amixer_rsc_put_ctrl_blk(rsc->ctrl_blk);
			अवरोध;
		हाल SUM:
		हाल DAIO:
			अवरोध;
		शेष:
			dev_err(((काष्ठा hw *)rsc->hw)->card->dev,
				"Invalid resource type value %d!\n",
				rsc->type);
			अवरोध;
		पूर्ण

		rsc->hw = rsc->ctrl_blk = शून्य;
	पूर्ण

	rsc->idx = rsc->conj = 0;
	rsc->type = NUM_RSCTYP;
	rsc->msr = 0;

	वापस 0;
पूर्ण

पूर्णांक rsc_mgr_init(काष्ठा rsc_mgr *mgr, क्रमागत RSCTYP type,
		 अचिन्हित पूर्णांक amount, काष्ठा hw *hw)
अणु
	पूर्णांक err = 0;

	mgr->type = NUM_RSCTYP;

	mgr->rscs = kzalloc(DIV_ROUND_UP(amount, 8), GFP_KERNEL);
	अगर (!mgr->rscs)
		वापस -ENOMEM;

	चयन (type) अणु
	हाल SRC:
		err = hw->src_mgr_get_ctrl_blk(&mgr->ctrl_blk);
		अवरोध;
	हाल SRCIMP:
		err = hw->srcimp_mgr_get_ctrl_blk(&mgr->ctrl_blk);
		अवरोध;
	हाल AMIXER:
		err = hw->amixer_mgr_get_ctrl_blk(&mgr->ctrl_blk);
		अवरोध;
	हाल DAIO:
		err = hw->daio_mgr_get_ctrl_blk(hw, &mgr->ctrl_blk);
		अवरोध;
	हाल SUM:
		अवरोध;
	शेष:
		dev_err(hw->card->dev,
			"Invalid resource type value %d!\n", type);
		err = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (err) अणु
		dev_err(hw->card->dev,
			"Failed to get manager control block!\n");
		जाओ error;
	पूर्ण

	mgr->type = type;
	mgr->avail = mgr->amount = amount;
	mgr->hw = hw;

	वापस 0;

error:
	kमुक्त(mgr->rscs);
	वापस err;
पूर्ण

पूर्णांक rsc_mgr_uninit(काष्ठा rsc_mgr *mgr)
अणु
	kमुक्त(mgr->rscs);
	mgr->rscs = शून्य;

	अगर ((शून्य != mgr->hw) && (शून्य != mgr->ctrl_blk)) अणु
		चयन (mgr->type) अणु
		हाल SRC:
			mgr->hw->src_mgr_put_ctrl_blk(mgr->ctrl_blk);
			अवरोध;
		हाल SRCIMP:
			mgr->hw->srcimp_mgr_put_ctrl_blk(mgr->ctrl_blk);
			अवरोध;
		हाल AMIXER:
			mgr->hw->amixer_mgr_put_ctrl_blk(mgr->ctrl_blk);
			अवरोध;
		हाल DAIO:
			mgr->hw->daio_mgr_put_ctrl_blk(mgr->ctrl_blk);
			अवरोध;
		हाल SUM:
			अवरोध;
		शेष:
			dev_err(((काष्ठा hw *)mgr->hw)->card->dev,
				"Invalid resource type value %d!\n",
				mgr->type);
			अवरोध;
		पूर्ण

		mgr->hw = mgr->ctrl_blk = शून्य;
	पूर्ण

	mgr->type = NUM_RSCTYP;
	mgr->avail = mgr->amount = 0;

	वापस 0;
पूर्ण
