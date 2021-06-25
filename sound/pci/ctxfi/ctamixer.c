<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctamixer.c
 *
 * @Brief
 * This file contains the implementation of the Audio Mixer
 * resource management object.
 *
 * @Author	Liu Chun
 * @Date 	May 21 2008
 */

#समावेश "ctamixer.h"
#समावेश "cthardware.h"
#समावेश <linux/slab.h>

#घोषणा AMIXER_RESOURCE_NUM	256
#घोषणा SUM_RESOURCE_NUM	256

#घोषणा AMIXER_Y_IMMEDIATE	1

#घोषणा BLANK_SLOT		4094

अटल पूर्णांक amixer_master(काष्ठा rsc *rsc)
अणु
	rsc->conj = 0;
	वापस rsc->idx = container_of(rsc, काष्ठा amixer, rsc)->idx[0];
पूर्ण

अटल पूर्णांक amixer_next_conj(काष्ठा rsc *rsc)
अणु
	rsc->conj++;
	वापस container_of(rsc, काष्ठा amixer, rsc)->idx[rsc->conj];
पूर्ण

अटल पूर्णांक amixer_index(स्थिर काष्ठा rsc *rsc)
अणु
	वापस container_of(rsc, काष्ठा amixer, rsc)->idx[rsc->conj];
पूर्ण

अटल पूर्णांक amixer_output_slot(स्थिर काष्ठा rsc *rsc)
अणु
	वापस (amixer_index(rsc) << 4) + 0x4;
पूर्ण

अटल स्थिर काष्ठा rsc_ops amixer_basic_rsc_ops = अणु
	.master		= amixer_master,
	.next_conj	= amixer_next_conj,
	.index		= amixer_index,
	.output_slot	= amixer_output_slot,
पूर्ण;

अटल पूर्णांक amixer_set_input(काष्ठा amixer *amixer, काष्ठा rsc *rsc)
अणु
	काष्ठा hw *hw;

	hw = amixer->rsc.hw;
	hw->amixer_set_mode(amixer->rsc.ctrl_blk, AMIXER_Y_IMMEDIATE);
	amixer->input = rsc;
	अगर (!rsc)
		hw->amixer_set_x(amixer->rsc.ctrl_blk, BLANK_SLOT);
	अन्यथा
		hw->amixer_set_x(amixer->rsc.ctrl_blk,
					rsc->ops->output_slot(rsc));

	वापस 0;
पूर्ण

/* y is a 14-bit immediate स्थिरant */
अटल पूर्णांक amixer_set_y(काष्ठा amixer *amixer, अचिन्हित पूर्णांक y)
अणु
	काष्ठा hw *hw;

	hw = amixer->rsc.hw;
	hw->amixer_set_y(amixer->rsc.ctrl_blk, y);

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_set_invalid_squash(काष्ठा amixer *amixer, अचिन्हित पूर्णांक iv)
अणु
	काष्ठा hw *hw;

	hw = amixer->rsc.hw;
	hw->amixer_set_iv(amixer->rsc.ctrl_blk, iv);

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_set_sum(काष्ठा amixer *amixer, काष्ठा sum *sum)
अणु
	काष्ठा hw *hw;

	hw = amixer->rsc.hw;
	amixer->sum = sum;
	अगर (!sum) अणु
		hw->amixer_set_se(amixer->rsc.ctrl_blk, 0);
	पूर्ण अन्यथा अणु
		hw->amixer_set_se(amixer->rsc.ctrl_blk, 1);
		hw->amixer_set_sadr(amixer->rsc.ctrl_blk,
					sum->rsc.ops->index(&sum->rsc));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_commit_ग_लिखो(काष्ठा amixer *amixer)
अणु
	काष्ठा hw *hw;
	अचिन्हित पूर्णांक index;
	पूर्णांक i;
	काष्ठा rsc *input;
	काष्ठा sum *sum;

	hw = amixer->rsc.hw;
	input = amixer->input;
	sum = amixer->sum;

	/* Program master and conjugate resources */
	amixer->rsc.ops->master(&amixer->rsc);
	अगर (input)
		input->ops->master(input);

	अगर (sum)
		sum->rsc.ops->master(&sum->rsc);

	क्रम (i = 0; i < amixer->rsc.msr; i++) अणु
		hw->amixer_set_dirty_all(amixer->rsc.ctrl_blk);
		अगर (input) अणु
			hw->amixer_set_x(amixer->rsc.ctrl_blk,
						input->ops->output_slot(input));
			input->ops->next_conj(input);
		पूर्ण
		अगर (sum) अणु
			hw->amixer_set_sadr(amixer->rsc.ctrl_blk,
						sum->rsc.ops->index(&sum->rsc));
			sum->rsc.ops->next_conj(&sum->rsc);
		पूर्ण
		index = amixer->rsc.ops->output_slot(&amixer->rsc);
		hw->amixer_commit_ग_लिखो(hw, index, amixer->rsc.ctrl_blk);
		amixer->rsc.ops->next_conj(&amixer->rsc);
	पूर्ण
	amixer->rsc.ops->master(&amixer->rsc);
	अगर (input)
		input->ops->master(input);

	अगर (sum)
		sum->rsc.ops->master(&sum->rsc);

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_commit_raw_ग_लिखो(काष्ठा amixer *amixer)
अणु
	काष्ठा hw *hw;
	अचिन्हित पूर्णांक index;

	hw = amixer->rsc.hw;
	index = amixer->rsc.ops->output_slot(&amixer->rsc);
	hw->amixer_commit_ग_लिखो(hw, index, amixer->rsc.ctrl_blk);

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_get_y(काष्ठा amixer *amixer)
अणु
	काष्ठा hw *hw;

	hw = amixer->rsc.hw;
	वापस hw->amixer_get_y(amixer->rsc.ctrl_blk);
पूर्ण

अटल पूर्णांक amixer_setup(काष्ठा amixer *amixer, काष्ठा rsc *input,
			अचिन्हित पूर्णांक scale, काष्ठा sum *sum)
अणु
	amixer_set_input(amixer, input);
	amixer_set_y(amixer, scale);
	amixer_set_sum(amixer, sum);
	amixer_commit_ग_लिखो(amixer);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amixer_rsc_ops amixer_ops = अणु
	.set_input		= amixer_set_input,
	.set_invalid_squash	= amixer_set_invalid_squash,
	.set_scale		= amixer_set_y,
	.set_sum		= amixer_set_sum,
	.commit_ग_लिखो		= amixer_commit_ग_लिखो,
	.commit_raw_ग_लिखो	= amixer_commit_raw_ग_लिखो,
	.setup			= amixer_setup,
	.get_scale		= amixer_get_y,
पूर्ण;

अटल पूर्णांक amixer_rsc_init(काष्ठा amixer *amixer,
			   स्थिर काष्ठा amixer_desc *desc,
			   काष्ठा amixer_mgr *mgr)
अणु
	पूर्णांक err;

	err = rsc_init(&amixer->rsc, amixer->idx[0],
			AMIXER, desc->msr, mgr->mgr.hw);
	अगर (err)
		वापस err;

	/* Set amixer specअगरic operations */
	amixer->rsc.ops = &amixer_basic_rsc_ops;
	amixer->ops = &amixer_ops;
	amixer->input = शून्य;
	amixer->sum = शून्य;

	amixer_setup(amixer, शून्य, 0, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_rsc_uninit(काष्ठा amixer *amixer)
अणु
	amixer_setup(amixer, शून्य, 0, शून्य);
	rsc_uninit(&amixer->rsc);
	amixer->ops = शून्य;
	amixer->input = शून्य;
	amixer->sum = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक get_amixer_rsc(काष्ठा amixer_mgr *mgr,
			  स्थिर काष्ठा amixer_desc *desc,
			  काष्ठा amixer **ramixer)
अणु
	पूर्णांक err, i;
	अचिन्हित पूर्णांक idx;
	काष्ठा amixer *amixer;
	अचिन्हित दीर्घ flags;

	*ramixer = शून्य;

	/* Allocate mem क्रम amixer resource */
	amixer = kzalloc(माप(*amixer), GFP_KERNEL);
	अगर (!amixer)
		वापस -ENOMEM;

	/* Check whether there are sufficient
	 * amixer resources to meet request. */
	err = 0;
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	क्रम (i = 0; i < desc->msr; i++) अणु
		err = mgr_get_resource(&mgr->mgr, 1, &idx);
		अगर (err)
			अवरोध;

		amixer->idx[i] = idx;
	पूर्ण
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	अगर (err) अणु
		dev_err(mgr->card->dev,
			"Can't meet AMIXER resource request!\n");
		जाओ error;
	पूर्ण

	err = amixer_rsc_init(amixer, desc, mgr);
	अगर (err)
		जाओ error;

	*ramixer = amixer;

	वापस 0;

error:
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	क्रम (i--; i >= 0; i--)
		mgr_put_resource(&mgr->mgr, 1, amixer->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	kमुक्त(amixer);
	वापस err;
पूर्ण

अटल पूर्णांक put_amixer_rsc(काष्ठा amixer_mgr *mgr, काष्ठा amixer *amixer)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&mgr->mgr_lock, flags);
	क्रम (i = 0; i < amixer->rsc.msr; i++)
		mgr_put_resource(&mgr->mgr, 1, amixer->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	amixer_rsc_uninit(amixer);
	kमुक्त(amixer);

	वापस 0;
पूर्ण

पूर्णांक amixer_mgr_create(काष्ठा hw *hw, काष्ठा amixer_mgr **ramixer_mgr)
अणु
	पूर्णांक err;
	काष्ठा amixer_mgr *amixer_mgr;

	*ramixer_mgr = शून्य;
	amixer_mgr = kzalloc(माप(*amixer_mgr), GFP_KERNEL);
	अगर (!amixer_mgr)
		वापस -ENOMEM;

	err = rsc_mgr_init(&amixer_mgr->mgr, AMIXER, AMIXER_RESOURCE_NUM, hw);
	अगर (err)
		जाओ error;

	spin_lock_init(&amixer_mgr->mgr_lock);

	amixer_mgr->get_amixer = get_amixer_rsc;
	amixer_mgr->put_amixer = put_amixer_rsc;
	amixer_mgr->card = hw->card;

	*ramixer_mgr = amixer_mgr;

	वापस 0;

error:
	kमुक्त(amixer_mgr);
	वापस err;
पूर्ण

पूर्णांक amixer_mgr_destroy(काष्ठा amixer_mgr *amixer_mgr)
अणु
	rsc_mgr_uninit(&amixer_mgr->mgr);
	kमुक्त(amixer_mgr);
	वापस 0;
पूर्ण

/* SUM resource management */

अटल पूर्णांक sum_master(काष्ठा rsc *rsc)
अणु
	rsc->conj = 0;
	वापस rsc->idx = container_of(rsc, काष्ठा sum, rsc)->idx[0];
पूर्ण

अटल पूर्णांक sum_next_conj(काष्ठा rsc *rsc)
अणु
	rsc->conj++;
	वापस container_of(rsc, काष्ठा sum, rsc)->idx[rsc->conj];
पूर्ण

अटल पूर्णांक sum_index(स्थिर काष्ठा rsc *rsc)
अणु
	वापस container_of(rsc, काष्ठा sum, rsc)->idx[rsc->conj];
पूर्ण

अटल पूर्णांक sum_output_slot(स्थिर काष्ठा rsc *rsc)
अणु
	वापस (sum_index(rsc) << 4) + 0xc;
पूर्ण

अटल स्थिर काष्ठा rsc_ops sum_basic_rsc_ops = अणु
	.master		= sum_master,
	.next_conj	= sum_next_conj,
	.index		= sum_index,
	.output_slot	= sum_output_slot,
पूर्ण;

अटल पूर्णांक sum_rsc_init(काष्ठा sum *sum,
			स्थिर काष्ठा sum_desc *desc,
			काष्ठा sum_mgr *mgr)
अणु
	पूर्णांक err;

	err = rsc_init(&sum->rsc, sum->idx[0], SUM, desc->msr, mgr->mgr.hw);
	अगर (err)
		वापस err;

	sum->rsc.ops = &sum_basic_rsc_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक sum_rsc_uninit(काष्ठा sum *sum)
अणु
	rsc_uninit(&sum->rsc);
	वापस 0;
पूर्ण

अटल पूर्णांक get_sum_rsc(काष्ठा sum_mgr *mgr,
		       स्थिर काष्ठा sum_desc *desc,
		       काष्ठा sum **rsum)
अणु
	पूर्णांक err, i;
	अचिन्हित पूर्णांक idx;
	काष्ठा sum *sum;
	अचिन्हित दीर्घ flags;

	*rsum = शून्य;

	/* Allocate mem क्रम sum resource */
	sum = kzalloc(माप(*sum), GFP_KERNEL);
	अगर (!sum)
		वापस -ENOMEM;

	/* Check whether there are sufficient sum resources to meet request. */
	err = 0;
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	क्रम (i = 0; i < desc->msr; i++) अणु
		err = mgr_get_resource(&mgr->mgr, 1, &idx);
		अगर (err)
			अवरोध;

		sum->idx[i] = idx;
	पूर्ण
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	अगर (err) अणु
		dev_err(mgr->card->dev,
			"Can't meet SUM resource request!\n");
		जाओ error;
	पूर्ण

	err = sum_rsc_init(sum, desc, mgr);
	अगर (err)
		जाओ error;

	*rsum = sum;

	वापस 0;

error:
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	क्रम (i--; i >= 0; i--)
		mgr_put_resource(&mgr->mgr, 1, sum->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	kमुक्त(sum);
	वापस err;
पूर्ण

अटल पूर्णांक put_sum_rsc(काष्ठा sum_mgr *mgr, काष्ठा sum *sum)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&mgr->mgr_lock, flags);
	क्रम (i = 0; i < sum->rsc.msr; i++)
		mgr_put_resource(&mgr->mgr, 1, sum->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	sum_rsc_uninit(sum);
	kमुक्त(sum);

	वापस 0;
पूर्ण

पूर्णांक sum_mgr_create(काष्ठा hw *hw, काष्ठा sum_mgr **rsum_mgr)
अणु
	पूर्णांक err;
	काष्ठा sum_mgr *sum_mgr;

	*rsum_mgr = शून्य;
	sum_mgr = kzalloc(माप(*sum_mgr), GFP_KERNEL);
	अगर (!sum_mgr)
		वापस -ENOMEM;

	err = rsc_mgr_init(&sum_mgr->mgr, SUM, SUM_RESOURCE_NUM, hw);
	अगर (err)
		जाओ error;

	spin_lock_init(&sum_mgr->mgr_lock);

	sum_mgr->get_sum = get_sum_rsc;
	sum_mgr->put_sum = put_sum_rsc;
	sum_mgr->card = hw->card;

	*rsum_mgr = sum_mgr;

	वापस 0;

error:
	kमुक्त(sum_mgr);
	वापस err;
पूर्ण

पूर्णांक sum_mgr_destroy(काष्ठा sum_mgr *sum_mgr)
अणु
	rsc_mgr_uninit(&sum_mgr->mgr);
	kमुक्त(sum_mgr);
	वापस 0;
पूर्ण

