<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctamixer.h
 *
 * @Brief
 * This file contains the definition of the Audio Mixer
 * resource management object.
 *
 * @Author	Liu Chun
 * @Date 	May 21 2008
 */

#अगर_अघोषित CTAMIXER_H
#घोषणा CTAMIXER_H

#समावेश "ctresource.h"
#समावेश <linux/spinlock.h>
#समावेश <sound/core.h>

/* Define the descriptor of a summation node resource */
काष्ठा sum अणु
	काष्ठा rsc rsc;		/* Basic resource info */
	अचिन्हित अक्षर idx[8];
पूर्ण;

/* Define sum resource request description info */
काष्ठा sum_desc अणु
	अचिन्हित पूर्णांक msr;
पूर्ण;

काष्ठा sum_mgr अणु
	काष्ठा rsc_mgr mgr;	/* Basic resource manager info */
	काष्ठा snd_card *card;	/* poपूर्णांकer to this card */
	spinlock_t mgr_lock;

	 /* request one sum resource */
	पूर्णांक (*get_sum)(काष्ठा sum_mgr *mgr,
			स्थिर काष्ठा sum_desc *desc, काष्ठा sum **rsum);
	/* वापस one sum resource */
	पूर्णांक (*put_sum)(काष्ठा sum_mgr *mgr, काष्ठा sum *sum);
पूर्ण;

/* Conकाष्ठाor and deकाष्ठाor of daio resource manager */
पूर्णांक sum_mgr_create(काष्ठा hw *hw, काष्ठा sum_mgr **rsum_mgr);
पूर्णांक sum_mgr_destroy(काष्ठा sum_mgr *sum_mgr);

/* Define the descriptor of a amixer resource */
काष्ठा amixer_rsc_ops;

काष्ठा amixer अणु
	काष्ठा rsc rsc;		/* Basic resource info */
	अचिन्हित अक्षर idx[8];
	काष्ठा rsc *input;	/* poपूर्णांकer to a resource acting as source */
	काष्ठा sum *sum;	/* Put amixer output to this summation node */
	स्थिर काष्ठा amixer_rsc_ops *ops;	/* AMixer specअगरic operations */
पूर्ण;

काष्ठा amixer_rsc_ops अणु
	पूर्णांक (*set_input)(काष्ठा amixer *amixer, काष्ठा rsc *rsc);
	पूर्णांक (*set_scale)(काष्ठा amixer *amixer, अचिन्हित पूर्णांक scale);
	पूर्णांक (*set_invalid_squash)(काष्ठा amixer *amixer, अचिन्हित पूर्णांक iv);
	पूर्णांक (*set_sum)(काष्ठा amixer *amixer, काष्ठा sum *sum);
	पूर्णांक (*commit_ग_लिखो)(काष्ठा amixer *amixer);
	/* Only क्रम पूर्णांकerleaved recording */
	पूर्णांक (*commit_raw_ग_लिखो)(काष्ठा amixer *amixer);
	पूर्णांक (*setup)(काष्ठा amixer *amixer, काष्ठा rsc *input,
			अचिन्हित पूर्णांक scale, काष्ठा sum *sum);
	पूर्णांक (*get_scale)(काष्ठा amixer *amixer);
पूर्ण;

/* Define amixer resource request description info */
काष्ठा amixer_desc अणु
	अचिन्हित पूर्णांक msr;
पूर्ण;

काष्ठा amixer_mgr अणु
	काष्ठा rsc_mgr mgr;	/* Basic resource manager info */
	काष्ठा snd_card *card;	/* poपूर्णांकer to this card */
	spinlock_t mgr_lock;

	 /* request one amixer resource */
	पूर्णांक (*get_amixer)(काष्ठा amixer_mgr *mgr,
			  स्थिर काष्ठा amixer_desc *desc,
			  काष्ठा amixer **ramixer);
	/* वापस one amixer resource */
	पूर्णांक (*put_amixer)(काष्ठा amixer_mgr *mgr, काष्ठा amixer *amixer);
पूर्ण;

/* Conकाष्ठाor and deकाष्ठाor of amixer resource manager */
पूर्णांक amixer_mgr_create(काष्ठा hw *hw, काष्ठा amixer_mgr **ramixer_mgr);
पूर्णांक amixer_mgr_destroy(काष्ठा amixer_mgr *amixer_mgr);

#पूर्ण_अगर /* CTAMIXER_H */
