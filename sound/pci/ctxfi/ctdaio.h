<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctdaपन.स
 *
 * @Brief
 * This file contains the definition of Digital Audio Input Output
 * resource management object.
 *
 * @Author	Liu Chun
 * @Date 	May 23 2008
 */

#अगर_अघोषित CTDAIO_H
#घोषणा CTDAIO_H

#समावेश "ctresource.h"
#समावेश "ctimap.h"
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <sound/core.h>

/* Define the descriptor of a daio resource */
क्रमागत DAIOTYP अणु
	LINEO1,
	LINEO2,
	LINEO3,
	LINEO4,
	SPDIFOO,	/* S/PDIF Out (Flexijack/Optical) */
	LINEIM,
	SPDIFIO,	/* S/PDIF In (Flexijack/Optical) on the card */
	MIC,		/* Dedicated mic on Titanium HD */
	SPDIFI1,	/* S/PDIF In on पूर्णांकernal Drive Bay */
	NUM_DAIOTYP
पूर्ण;

काष्ठा dao_rsc_ops;
काष्ठा dai_rsc_ops;
काष्ठा daio_mgr;

काष्ठा daio अणु
	काष्ठा rsc rscl;	/* Basic resource info क्रम left TX/RX */
	काष्ठा rsc rscr;	/* Basic resource info क्रम right TX/RX */
	क्रमागत DAIOTYP type;
पूर्ण;

काष्ठा dao अणु
	काष्ठा daio daio;
	स्थिर काष्ठा dao_rsc_ops *ops;	/* DAO specअगरic operations */
	काष्ठा imapper **imappers;
	काष्ठा daio_mgr *mgr;
	काष्ठा hw *hw;
	व्योम *ctrl_blk;
पूर्ण;

काष्ठा dai अणु
	काष्ठा daio daio;
	स्थिर काष्ठा dai_rsc_ops *ops;	/* DAI specअगरic operations */
	काष्ठा hw *hw;
	व्योम *ctrl_blk;
पूर्ण;

काष्ठा dao_desc अणु
	अचिन्हित पूर्णांक msr:4;
	अचिन्हित पूर्णांक passthru:1;
पूर्ण;

काष्ठा dao_rsc_ops अणु
	पूर्णांक (*set_spos)(काष्ठा dao *dao, अचिन्हित पूर्णांक spos);
	पूर्णांक (*commit_ग_लिखो)(काष्ठा dao *dao);
	पूर्णांक (*get_spos)(काष्ठा dao *dao, अचिन्हित पूर्णांक *spos);
	पूर्णांक (*reinit)(काष्ठा dao *dao, स्थिर काष्ठा dao_desc *desc);
	पूर्णांक (*set_left_input)(काष्ठा dao *dao, काष्ठा rsc *input);
	पूर्णांक (*set_right_input)(काष्ठा dao *dao, काष्ठा rsc *input);
	पूर्णांक (*clear_left_input)(काष्ठा dao *dao);
	पूर्णांक (*clear_right_input)(काष्ठा dao *dao);
पूर्ण;

काष्ठा dai_rsc_ops अणु
	पूर्णांक (*set_srt_srcl)(काष्ठा dai *dai, काष्ठा rsc *src);
	पूर्णांक (*set_srt_srcr)(काष्ठा dai *dai, काष्ठा rsc *src);
	पूर्णांक (*set_srt_msr)(काष्ठा dai *dai, अचिन्हित पूर्णांक msr);
	पूर्णांक (*set_enb_src)(काष्ठा dai *dai, अचिन्हित पूर्णांक enb);
	पूर्णांक (*set_enb_srt)(काष्ठा dai *dai, अचिन्हित पूर्णांक enb);
	पूर्णांक (*commit_ग_लिखो)(काष्ठा dai *dai);
पूर्ण;

/* Define daio resource request description info */
काष्ठा daio_desc अणु
	अचिन्हित पूर्णांक type:4;
	अचिन्हित पूर्णांक msr:4;
	अचिन्हित पूर्णांक passthru:1;
पूर्ण;

काष्ठा daio_mgr अणु
	काष्ठा rsc_mgr mgr;	/* Basic resource manager info */
	काष्ठा snd_card *card;	/* poपूर्णांकer to this card */
	spinlock_t mgr_lock;
	spinlock_t imap_lock;
	काष्ठा list_head imappers;
	काष्ठा imapper *init_imap;
	अचिन्हित पूर्णांक init_imap_added;

	 /* request one daio resource */
	पूर्णांक (*get_daio)(काष्ठा daio_mgr *mgr,
			स्थिर काष्ठा daio_desc *desc, काष्ठा daio **rdaio);
	/* वापस one daio resource */
	पूर्णांक (*put_daio)(काष्ठा daio_mgr *mgr, काष्ठा daio *daio);
	पूर्णांक (*daio_enable)(काष्ठा daio_mgr *mgr, काष्ठा daio *daio);
	पूर्णांक (*daio_disable)(काष्ठा daio_mgr *mgr, काष्ठा daio *daio);
	पूर्णांक (*imap_add)(काष्ठा daio_mgr *mgr, काष्ठा imapper *entry);
	पूर्णांक (*imap_delete)(काष्ठा daio_mgr *mgr, काष्ठा imapper *entry);
	पूर्णांक (*commit_ग_लिखो)(काष्ठा daio_mgr *mgr);
पूर्ण;

/* Conकाष्ठाor and deकाष्ठाor of daio resource manager */
पूर्णांक daio_mgr_create(काष्ठा hw *hw, काष्ठा daio_mgr **rdaio_mgr);
पूर्णांक daio_mgr_destroy(काष्ठा daio_mgr *daio_mgr);

#पूर्ण_अगर /* CTDAIO_H */
