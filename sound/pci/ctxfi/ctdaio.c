<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctdaio.c
 *
 * @Brief
 * This file contains the implementation of Digital Audio Input Output
 * resource management object.
 *
 * @Author	Liu Chun
 * @Date 	May 23 2008
 */

#समावेश "ctdaio.h"
#समावेश "cthardware.h"
#समावेश "ctimap.h"
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>

#घोषणा DAIO_OUT_MAX		SPDIFOO

काष्ठा daio_usage अणु
	अचिन्हित लघु data;
पूर्ण;

काष्ठा daio_rsc_idx अणु
	अचिन्हित लघु left;
	अचिन्हित लघु right;
पूर्ण;

अटल स्थिर काष्ठा daio_rsc_idx idx_20k1[NUM_DAIOTYP] = अणु
	[LINEO1] = अणु.left = 0x00, .right = 0x01पूर्ण,
	[LINEO2] = अणु.left = 0x18, .right = 0x19पूर्ण,
	[LINEO3] = अणु.left = 0x08, .right = 0x09पूर्ण,
	[LINEO4] = अणु.left = 0x10, .right = 0x11पूर्ण,
	[LINEIM] = अणु.left = 0x1b5, .right = 0x1bdपूर्ण,
	[SPDIFOO] = अणु.left = 0x20, .right = 0x21पूर्ण,
	[SPDIFIO] = अणु.left = 0x15, .right = 0x1dपूर्ण,
	[SPDIFI1] = अणु.left = 0x95, .right = 0x9dपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा daio_rsc_idx idx_20k2[NUM_DAIOTYP] = अणु
	[LINEO1] = अणु.left = 0x40, .right = 0x41पूर्ण,
	[LINEO2] = अणु.left = 0x60, .right = 0x61पूर्ण,
	[LINEO3] = अणु.left = 0x50, .right = 0x51पूर्ण,
	[LINEO4] = अणु.left = 0x70, .right = 0x71पूर्ण,
	[LINEIM] = अणु.left = 0x45, .right = 0xc5पूर्ण,
	[MIC]	 = अणु.left = 0x55, .right = 0xd5पूर्ण,
	[SPDIFOO] = अणु.left = 0x00, .right = 0x01पूर्ण,
	[SPDIFIO] = अणु.left = 0x05, .right = 0x85पूर्ण,
पूर्ण;

अटल पूर्णांक daio_master(काष्ठा rsc *rsc)
अणु
	/* Actually, this is not the resource index of DAIO.
	 * For DAO, it is the input mapper index. And, क्रम DAI,
	 * it is the output समय-slot index. */
	वापस rsc->conj = rsc->idx;
पूर्ण

अटल पूर्णांक daio_index(स्थिर काष्ठा rsc *rsc)
अणु
	वापस rsc->conj;
पूर्ण

अटल पूर्णांक daio_out_next_conj(काष्ठा rsc *rsc)
अणु
	वापस rsc->conj += 2;
पूर्ण

अटल पूर्णांक daio_in_next_conj_20k1(काष्ठा rsc *rsc)
अणु
	वापस rsc->conj += 0x200;
पूर्ण

अटल पूर्णांक daio_in_next_conj_20k2(काष्ठा rsc *rsc)
अणु
	वापस rsc->conj += 0x100;
पूर्ण

अटल स्थिर काष्ठा rsc_ops daio_out_rsc_ops = अणु
	.master		= daio_master,
	.next_conj	= daio_out_next_conj,
	.index		= daio_index,
	.output_slot	= शून्य,
पूर्ण;

अटल स्थिर काष्ठा rsc_ops daio_in_rsc_ops_20k1 = अणु
	.master		= daio_master,
	.next_conj	= daio_in_next_conj_20k1,
	.index		= शून्य,
	.output_slot	= daio_index,
पूर्ण;

अटल स्थिर काष्ठा rsc_ops daio_in_rsc_ops_20k2 = अणु
	.master		= daio_master,
	.next_conj	= daio_in_next_conj_20k2,
	.index		= शून्य,
	.output_slot	= daio_index,
पूर्ण;

अटल अचिन्हित पूर्णांक daio_device_index(क्रमागत DAIOTYP type, काष्ठा hw *hw)
अणु
	चयन (hw->chip_type) अणु
	हाल ATC20K1:
		चयन (type) अणु
		हाल SPDIFOO:	वापस 0;
		हाल SPDIFIO:	वापस 0;
		हाल SPDIFI1:	वापस 1;
		हाल LINEO1:	वापस 4;
		हाल LINEO2:	वापस 7;
		हाल LINEO3:	वापस 5;
		हाल LINEO4:	वापस 6;
		हाल LINEIM:	वापस 7;
		शेष:	वापस -EINVAL;
		पूर्ण
	हाल ATC20K2:
		चयन (type) अणु
		हाल SPDIFOO:	वापस 0;
		हाल SPDIFIO:	वापस 0;
		हाल LINEO1:	वापस 4;
		हाल LINEO2:	वापस 7;
		हाल LINEO3:	वापस 5;
		हाल LINEO4:	वापस 6;
		हाल LINEIM:	वापस 4;
		हाल MIC:	वापस 5;
		शेष:	वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dao_rsc_reinit(काष्ठा dao *dao, स्थिर काष्ठा dao_desc *desc);

अटल पूर्णांक dao_spdअगर_get_spos(काष्ठा dao *dao, अचिन्हित पूर्णांक *spos)
अणु
	dao->hw->dao_get_spos(dao->ctrl_blk, spos);
	वापस 0;
पूर्ण

अटल पूर्णांक dao_spdअगर_set_spos(काष्ठा dao *dao, अचिन्हित पूर्णांक spos)
अणु
	dao->hw->dao_set_spos(dao->ctrl_blk, spos);
	वापस 0;
पूर्ण

अटल पूर्णांक dao_commit_ग_लिखो(काष्ठा dao *dao)
अणु
	dao->hw->dao_commit_ग_लिखो(dao->hw,
		daio_device_index(dao->daio.type, dao->hw), dao->ctrl_blk);
	वापस 0;
पूर्ण

अटल पूर्णांक dao_set_left_input(काष्ठा dao *dao, काष्ठा rsc *input)
अणु
	काष्ठा imapper *entry;
	काष्ठा daio *daio = &dao->daio;
	पूर्णांक i;

	entry = kzalloc((माप(*entry) * daio->rscl.msr), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	dao->ops->clear_left_input(dao);
	/* Program master and conjugate resources */
	input->ops->master(input);
	daio->rscl.ops->master(&daio->rscl);
	क्रम (i = 0; i < daio->rscl.msr; i++, entry++) अणु
		entry->slot = input->ops->output_slot(input);
		entry->user = entry->addr = daio->rscl.ops->index(&daio->rscl);
		dao->mgr->imap_add(dao->mgr, entry);
		dao->imappers[i] = entry;

		input->ops->next_conj(input);
		daio->rscl.ops->next_conj(&daio->rscl);
	पूर्ण
	input->ops->master(input);
	daio->rscl.ops->master(&daio->rscl);

	वापस 0;
पूर्ण

अटल पूर्णांक dao_set_right_input(काष्ठा dao *dao, काष्ठा rsc *input)
अणु
	काष्ठा imapper *entry;
	काष्ठा daio *daio = &dao->daio;
	पूर्णांक i;

	entry = kzalloc((माप(*entry) * daio->rscr.msr), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	dao->ops->clear_right_input(dao);
	/* Program master and conjugate resources */
	input->ops->master(input);
	daio->rscr.ops->master(&daio->rscr);
	क्रम (i = 0; i < daio->rscr.msr; i++, entry++) अणु
		entry->slot = input->ops->output_slot(input);
		entry->user = entry->addr = daio->rscr.ops->index(&daio->rscr);
		dao->mgr->imap_add(dao->mgr, entry);
		dao->imappers[daio->rscl.msr + i] = entry;

		input->ops->next_conj(input);
		daio->rscr.ops->next_conj(&daio->rscr);
	पूर्ण
	input->ops->master(input);
	daio->rscr.ops->master(&daio->rscr);

	वापस 0;
पूर्ण

अटल पूर्णांक dao_clear_left_input(काष्ठा dao *dao)
अणु
	काष्ठा imapper *entry;
	काष्ठा daio *daio = &dao->daio;
	पूर्णांक i;

	अगर (!dao->imappers[0])
		वापस 0;

	entry = dao->imappers[0];
	dao->mgr->imap_delete(dao->mgr, entry);
	/* Program conjugate resources */
	क्रम (i = 1; i < daio->rscl.msr; i++) अणु
		entry = dao->imappers[i];
		dao->mgr->imap_delete(dao->mgr, entry);
		dao->imappers[i] = शून्य;
	पूर्ण

	kमुक्त(dao->imappers[0]);
	dao->imappers[0] = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक dao_clear_right_input(काष्ठा dao *dao)
अणु
	काष्ठा imapper *entry;
	काष्ठा daio *daio = &dao->daio;
	पूर्णांक i;

	अगर (!dao->imappers[daio->rscl.msr])
		वापस 0;

	entry = dao->imappers[daio->rscl.msr];
	dao->mgr->imap_delete(dao->mgr, entry);
	/* Program conjugate resources */
	क्रम (i = 1; i < daio->rscr.msr; i++) अणु
		entry = dao->imappers[daio->rscl.msr + i];
		dao->mgr->imap_delete(dao->mgr, entry);
		dao->imappers[daio->rscl.msr + i] = शून्य;
	पूर्ण

	kमुक्त(dao->imappers[daio->rscl.msr]);
	dao->imappers[daio->rscl.msr] = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dao_rsc_ops dao_ops = अणु
	.set_spos		= dao_spdअगर_set_spos,
	.commit_ग_लिखो		= dao_commit_ग_लिखो,
	.get_spos		= dao_spdअगर_get_spos,
	.reinit			= dao_rsc_reinit,
	.set_left_input		= dao_set_left_input,
	.set_right_input	= dao_set_right_input,
	.clear_left_input	= dao_clear_left_input,
	.clear_right_input	= dao_clear_right_input,
पूर्ण;

अटल पूर्णांक dai_set_srt_srcl(काष्ठा dai *dai, काष्ठा rsc *src)
अणु
	src->ops->master(src);
	dai->hw->dai_srt_set_srcm(dai->ctrl_blk, src->ops->index(src));
	वापस 0;
पूर्ण

अटल पूर्णांक dai_set_srt_srcr(काष्ठा dai *dai, काष्ठा rsc *src)
अणु
	src->ops->master(src);
	dai->hw->dai_srt_set_srco(dai->ctrl_blk, src->ops->index(src));
	वापस 0;
पूर्ण

अटल पूर्णांक dai_set_srt_msr(काष्ठा dai *dai, अचिन्हित पूर्णांक msr)
अणु
	अचिन्हित पूर्णांक rsr;

	क्रम (rsr = 0; msr > 1; msr >>= 1)
		rsr++;

	dai->hw->dai_srt_set_rsr(dai->ctrl_blk, rsr);
	वापस 0;
पूर्ण

अटल पूर्णांक dai_set_enb_src(काष्ठा dai *dai, अचिन्हित पूर्णांक enb)
अणु
	dai->hw->dai_srt_set_ec(dai->ctrl_blk, enb);
	वापस 0;
पूर्ण

अटल पूर्णांक dai_set_enb_srt(काष्ठा dai *dai, अचिन्हित पूर्णांक enb)
अणु
	dai->hw->dai_srt_set_et(dai->ctrl_blk, enb);
	वापस 0;
पूर्ण

अटल पूर्णांक dai_commit_ग_लिखो(काष्ठा dai *dai)
अणु
	dai->hw->dai_commit_ग_लिखो(dai->hw,
		daio_device_index(dai->daio.type, dai->hw), dai->ctrl_blk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dai_rsc_ops dai_ops = अणु
	.set_srt_srcl		= dai_set_srt_srcl,
	.set_srt_srcr		= dai_set_srt_srcr,
	.set_srt_msr		= dai_set_srt_msr,
	.set_enb_src		= dai_set_enb_src,
	.set_enb_srt		= dai_set_enb_srt,
	.commit_ग_लिखो		= dai_commit_ग_लिखो,
पूर्ण;

अटल पूर्णांक daio_rsc_init(काष्ठा daio *daio,
			 स्थिर काष्ठा daio_desc *desc,
			 काष्ठा hw *hw)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक idx_l, idx_r;

	चयन (hw->chip_type) अणु
	हाल ATC20K1:
		idx_l = idx_20k1[desc->type].left;
		idx_r = idx_20k1[desc->type].right;
		अवरोध;
	हाल ATC20K2:
		idx_l = idx_20k2[desc->type].left;
		idx_r = idx_20k2[desc->type].right;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	err = rsc_init(&daio->rscl, idx_l, DAIO, desc->msr, hw);
	अगर (err)
		वापस err;

	err = rsc_init(&daio->rscr, idx_r, DAIO, desc->msr, hw);
	अगर (err)
		जाओ error1;

	/* Set daio->rscl/r->ops to daio specअगरic ones */
	अगर (desc->type <= DAIO_OUT_MAX) अणु
		daio->rscl.ops = daio->rscr.ops = &daio_out_rsc_ops;
	पूर्ण अन्यथा अणु
		चयन (hw->chip_type) अणु
		हाल ATC20K1:
			daio->rscl.ops = daio->rscr.ops = &daio_in_rsc_ops_20k1;
			अवरोध;
		हाल ATC20K2:
			daio->rscl.ops = daio->rscr.ops = &daio_in_rsc_ops_20k2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	daio->type = desc->type;

	वापस 0;

error1:
	rsc_uninit(&daio->rscl);
	वापस err;
पूर्ण

अटल पूर्णांक daio_rsc_uninit(काष्ठा daio *daio)
अणु
	rsc_uninit(&daio->rscl);
	rsc_uninit(&daio->rscr);

	वापस 0;
पूर्ण

अटल पूर्णांक dao_rsc_init(काष्ठा dao *dao,
			स्थिर काष्ठा daio_desc *desc,
			काष्ठा daio_mgr *mgr)
अणु
	काष्ठा hw *hw = mgr->mgr.hw;
	अचिन्हित पूर्णांक conf;
	पूर्णांक err;

	err = daio_rsc_init(&dao->daio, desc, mgr->mgr.hw);
	अगर (err)
		वापस err;

	dao->imappers = kzalloc(array3_size(माप(व्योम *), desc->msr, 2),
				GFP_KERNEL);
	अगर (!dao->imappers) अणु
		err = -ENOMEM;
		जाओ error1;
	पूर्ण
	dao->ops = &dao_ops;
	dao->mgr = mgr;
	dao->hw = hw;
	err = hw->dao_get_ctrl_blk(&dao->ctrl_blk);
	अगर (err)
		जाओ error2;

	hw->daio_mgr_dsb_dao(mgr->mgr.ctrl_blk,
			daio_device_index(dao->daio.type, hw));
	hw->daio_mgr_commit_ग_लिखो(hw, mgr->mgr.ctrl_blk);

	conf = (desc->msr & 0x7) | (desc->passthru << 3);
	hw->daio_mgr_dao_init(mgr->mgr.ctrl_blk,
			daio_device_index(dao->daio.type, hw), conf);
	hw->daio_mgr_enb_dao(mgr->mgr.ctrl_blk,
			daio_device_index(dao->daio.type, hw));
	hw->daio_mgr_commit_ग_लिखो(hw, mgr->mgr.ctrl_blk);

	वापस 0;

error2:
	kमुक्त(dao->imappers);
	dao->imappers = शून्य;
error1:
	daio_rsc_uninit(&dao->daio);
	वापस err;
पूर्ण

अटल पूर्णांक dao_rsc_uninit(काष्ठा dao *dao)
अणु
	अगर (dao->imappers) अणु
		अगर (dao->imappers[0])
			dao_clear_left_input(dao);

		अगर (dao->imappers[dao->daio.rscl.msr])
			dao_clear_right_input(dao);

		kमुक्त(dao->imappers);
		dao->imappers = शून्य;
	पूर्ण
	dao->hw->dao_put_ctrl_blk(dao->ctrl_blk);
	dao->hw = dao->ctrl_blk = शून्य;
	daio_rsc_uninit(&dao->daio);

	वापस 0;
पूर्ण

अटल पूर्णांक dao_rsc_reinit(काष्ठा dao *dao, स्थिर काष्ठा dao_desc *desc)
अणु
	काष्ठा daio_mgr *mgr = dao->mgr;
	काष्ठा daio_desc dsc = अणु0पूर्ण;

	dsc.type = dao->daio.type;
	dsc.msr = desc->msr;
	dsc.passthru = desc->passthru;
	dao_rsc_uninit(dao);
	वापस dao_rsc_init(dao, &dsc, mgr);
पूर्ण

अटल पूर्णांक dai_rsc_init(काष्ठा dai *dai,
			स्थिर काष्ठा daio_desc *desc,
			काष्ठा daio_mgr *mgr)
अणु
	पूर्णांक err;
	काष्ठा hw *hw = mgr->mgr.hw;
	अचिन्हित पूर्णांक rsr, msr;

	err = daio_rsc_init(&dai->daio, desc, mgr->mgr.hw);
	अगर (err)
		वापस err;

	dai->ops = &dai_ops;
	dai->hw = mgr->mgr.hw;
	err = hw->dai_get_ctrl_blk(&dai->ctrl_blk);
	अगर (err)
		जाओ error1;

	क्रम (rsr = 0, msr = desc->msr; msr > 1; msr >>= 1)
		rsr++;

	hw->dai_srt_set_rsr(dai->ctrl_blk, rsr);
	hw->dai_srt_set_drat(dai->ctrl_blk, 0);
	/* शेष to disabling control of a SRC */
	hw->dai_srt_set_ec(dai->ctrl_blk, 0);
	hw->dai_srt_set_et(dai->ctrl_blk, 0); /* शेष to disabling SRT */
	hw->dai_commit_ग_लिखो(hw,
		daio_device_index(dai->daio.type, dai->hw), dai->ctrl_blk);

	वापस 0;

error1:
	daio_rsc_uninit(&dai->daio);
	वापस err;
पूर्ण

अटल पूर्णांक dai_rsc_uninit(काष्ठा dai *dai)
अणु
	dai->hw->dai_put_ctrl_blk(dai->ctrl_blk);
	dai->hw = dai->ctrl_blk = शून्य;
	daio_rsc_uninit(&dai->daio);
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_get_rsc(काष्ठा rsc_mgr *mgr, क्रमागत DAIOTYP type)
अणु
	अगर (((काष्ठा daio_usage *)mgr->rscs)->data & (0x1 << type))
		वापस -ENOENT;

	((काष्ठा daio_usage *)mgr->rscs)->data |= (0x1 << type);

	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_put_rsc(काष्ठा rsc_mgr *mgr, क्रमागत DAIOTYP type)
अणु
	((काष्ठा daio_usage *)mgr->rscs)->data &= ~(0x1 << type);

	वापस 0;
पूर्ण

अटल पूर्णांक get_daio_rsc(काष्ठा daio_mgr *mgr,
			स्थिर काष्ठा daio_desc *desc,
			काष्ठा daio **rdaio)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	*rdaio = शून्य;

	/* Check whether there are sufficient daio resources to meet request. */
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	err = daio_mgr_get_rsc(&mgr->mgr, desc->type);
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	अगर (err) अणु
		dev_err(mgr->card->dev,
			"Can't meet DAIO resource request!\n");
		वापस err;
	पूर्ण

	err = -ENOMEM;
	/* Allocate mem क्रम daio resource */
	अगर (desc->type <= DAIO_OUT_MAX) अणु
		काष्ठा dao *dao = kzalloc(माप(*dao), GFP_KERNEL);
		अगर (!dao)
			जाओ error;

		err = dao_rsc_init(dao, desc, mgr);
		अगर (err) अणु
			kमुक्त(dao);
			जाओ error;
		पूर्ण

		*rdaio = &dao->daio;
	पूर्ण अन्यथा अणु
		काष्ठा dai *dai = kzalloc(माप(*dai), GFP_KERNEL);
		अगर (!dai)
			जाओ error;

		err = dai_rsc_init(dai, desc, mgr);
		अगर (err) अणु
			kमुक्त(dai);
			जाओ error;
		पूर्ण

		*rdaio = &dai->daio;
	पूर्ण

	mgr->daio_enable(mgr, *rdaio);
	mgr->commit_ग_लिखो(mgr);

	वापस 0;

error:
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	daio_mgr_put_rsc(&mgr->mgr, desc->type);
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक put_daio_rsc(काष्ठा daio_mgr *mgr, काष्ठा daio *daio)
अणु
	अचिन्हित दीर्घ flags;

	mgr->daio_disable(mgr, daio);
	mgr->commit_ग_लिखो(mgr);

	spin_lock_irqsave(&mgr->mgr_lock, flags);
	daio_mgr_put_rsc(&mgr->mgr, daio->type);
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);

	अगर (daio->type <= DAIO_OUT_MAX) अणु
		dao_rsc_uninit(container_of(daio, काष्ठा dao, daio));
		kमुक्त(container_of(daio, काष्ठा dao, daio));
	पूर्ण अन्यथा अणु
		dai_rsc_uninit(container_of(daio, काष्ठा dai, daio));
		kमुक्त(container_of(daio, काष्ठा dai, daio));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_enb_daio(काष्ठा daio_mgr *mgr, काष्ठा daio *daio)
अणु
	काष्ठा hw *hw = mgr->mgr.hw;

	अगर (DAIO_OUT_MAX >= daio->type) अणु
		hw->daio_mgr_enb_dao(mgr->mgr.ctrl_blk,
				daio_device_index(daio->type, hw));
	पूर्ण अन्यथा अणु
		hw->daio_mgr_enb_dai(mgr->mgr.ctrl_blk,
				daio_device_index(daio->type, hw));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_dsb_daio(काष्ठा daio_mgr *mgr, काष्ठा daio *daio)
अणु
	काष्ठा hw *hw = mgr->mgr.hw;

	अगर (DAIO_OUT_MAX >= daio->type) अणु
		hw->daio_mgr_dsb_dao(mgr->mgr.ctrl_blk,
				daio_device_index(daio->type, hw));
	पूर्ण अन्यथा अणु
		hw->daio_mgr_dsb_dai(mgr->mgr.ctrl_blk,
				daio_device_index(daio->type, hw));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक daio_map_op(व्योम *data, काष्ठा imapper *entry)
अणु
	काष्ठा rsc_mgr *mgr = &((काष्ठा daio_mgr *)data)->mgr;
	काष्ठा hw *hw = mgr->hw;

	hw->daio_mgr_set_imaparc(mgr->ctrl_blk, entry->slot);
	hw->daio_mgr_set_imapnxt(mgr->ctrl_blk, entry->next);
	hw->daio_mgr_set_imapaddr(mgr->ctrl_blk, entry->addr);
	hw->daio_mgr_commit_ग_लिखो(mgr->hw, mgr->ctrl_blk);

	वापस 0;
पूर्ण

अटल पूर्णांक daio_imap_add(काष्ठा daio_mgr *mgr, काष्ठा imapper *entry)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&mgr->imap_lock, flags);
	अगर (!entry->addr && mgr->init_imap_added) अणु
		input_mapper_delete(&mgr->imappers, mgr->init_imap,
							daio_map_op, mgr);
		mgr->init_imap_added = 0;
	पूर्ण
	err = input_mapper_add(&mgr->imappers, entry, daio_map_op, mgr);
	spin_unlock_irqrestore(&mgr->imap_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक daio_imap_delete(काष्ठा daio_mgr *mgr, काष्ठा imapper *entry)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&mgr->imap_lock, flags);
	err = input_mapper_delete(&mgr->imappers, entry, daio_map_op, mgr);
	अगर (list_empty(&mgr->imappers)) अणु
		input_mapper_add(&mgr->imappers, mgr->init_imap,
							daio_map_op, mgr);
		mgr->init_imap_added = 1;
	पूर्ण
	spin_unlock_irqrestore(&mgr->imap_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक daio_mgr_commit_ग_लिखो(काष्ठा daio_mgr *mgr)
अणु
	काष्ठा hw *hw = mgr->mgr.hw;

	hw->daio_mgr_commit_ग_लिखो(hw, mgr->mgr.ctrl_blk);
	वापस 0;
पूर्ण

पूर्णांक daio_mgr_create(काष्ठा hw *hw, काष्ठा daio_mgr **rdaio_mgr)
अणु
	पूर्णांक err, i;
	काष्ठा daio_mgr *daio_mgr;
	काष्ठा imapper *entry;

	*rdaio_mgr = शून्य;
	daio_mgr = kzalloc(माप(*daio_mgr), GFP_KERNEL);
	अगर (!daio_mgr)
		वापस -ENOMEM;

	err = rsc_mgr_init(&daio_mgr->mgr, DAIO, NUM_DAIOTYP, hw);
	अगर (err)
		जाओ error1;

	spin_lock_init(&daio_mgr->mgr_lock);
	spin_lock_init(&daio_mgr->imap_lock);
	INIT_LIST_HEAD(&daio_mgr->imappers);
	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		err = -ENOMEM;
		जाओ error2;
	पूर्ण
	entry->slot = entry->addr = entry->next = entry->user = 0;
	list_add(&entry->list, &daio_mgr->imappers);
	daio_mgr->init_imap = entry;
	daio_mgr->init_imap_added = 1;

	daio_mgr->get_daio = get_daio_rsc;
	daio_mgr->put_daio = put_daio_rsc;
	daio_mgr->daio_enable = daio_mgr_enb_daio;
	daio_mgr->daio_disable = daio_mgr_dsb_daio;
	daio_mgr->imap_add = daio_imap_add;
	daio_mgr->imap_delete = daio_imap_delete;
	daio_mgr->commit_ग_लिखो = daio_mgr_commit_ग_लिखो;
	daio_mgr->card = hw->card;

	क्रम (i = 0; i < 8; i++) अणु
		hw->daio_mgr_dsb_dao(daio_mgr->mgr.ctrl_blk, i);
		hw->daio_mgr_dsb_dai(daio_mgr->mgr.ctrl_blk, i);
	पूर्ण
	hw->daio_mgr_commit_ग_लिखो(hw, daio_mgr->mgr.ctrl_blk);

	*rdaio_mgr = daio_mgr;

	वापस 0;

error2:
	rsc_mgr_uninit(&daio_mgr->mgr);
error1:
	kमुक्त(daio_mgr);
	वापस err;
पूर्ण

पूर्णांक daio_mgr_destroy(काष्ठा daio_mgr *daio_mgr)
अणु
	अचिन्हित दीर्घ flags;

	/* मुक्त daio input mapper list */
	spin_lock_irqsave(&daio_mgr->imap_lock, flags);
	मुक्त_input_mapper_list(&daio_mgr->imappers);
	spin_unlock_irqrestore(&daio_mgr->imap_lock, flags);

	rsc_mgr_uninit(&daio_mgr->mgr);
	kमुक्त(daio_mgr);

	वापस 0;
पूर्ण

