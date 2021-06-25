<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctsrc.h
 *
 * @Brief
 * This file contains the definition of the Sample Rate Convertor
 * resource management object.
 *
 * @Author	Liu Chun
 * @Date 	May 13 2008
 */

#अगर_अघोषित CTSRC_H
#घोषणा CTSRC_H

#समावेश "ctresource.h"
#समावेश "ctimap.h"
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <sound/core.h>

#घोषणा SRC_STATE_OFF	0x0
#घोषणा SRC_STATE_INIT	0x4
#घोषणा SRC_STATE_RUN	0x5

#घोषणा SRC_SF_U8	0x0
#घोषणा SRC_SF_S16	0x1
#घोषणा SRC_SF_S24	0x2
#घोषणा SRC_SF_S32	0x3
#घोषणा SRC_SF_F32	0x4

/* Define the descriptor of a src resource */
क्रमागत SRCMODE अणु
	MEMRD,		/* Read data from host memory */
	MEMWR,		/* Write data to host memory */
	ARCRW,		/* Read from and ग_लिखो to audio ring channel */
	NUM_SRCMODES
पूर्ण;

काष्ठा src_rsc_ops;

काष्ठा src अणु
	काष्ठा rsc rsc; /* Basic resource info */
	काष्ठा src *पूर्णांकlv; /* Poपूर्णांकer to next पूर्णांकerleaved SRC in a series */
	स्थिर काष्ठा src_rsc_ops *ops; /* SRC specअगरic operations */
	/* Number of contiguous srcs क्रम पूर्णांकerleaved usage */
	अचिन्हित अक्षर multi;
	अचिन्हित अक्षर mode; /* Working mode of this SRC resource */
पूर्ण;

काष्ठा src_rsc_ops अणु
	पूर्णांक (*set_state)(काष्ठा src *src, अचिन्हित पूर्णांक state);
	पूर्णांक (*set_bm)(काष्ठा src *src, अचिन्हित पूर्णांक bm);
	पूर्णांक (*set_sf)(काष्ठा src *src, अचिन्हित पूर्णांक sf);
	पूर्णांक (*set_pm)(काष्ठा src *src, अचिन्हित पूर्णांक pm);
	पूर्णांक (*set_rom)(काष्ठा src *src, अचिन्हित पूर्णांक rom);
	पूर्णांक (*set_vo)(काष्ठा src *src, अचिन्हित पूर्णांक vo);
	पूर्णांक (*set_st)(काष्ठा src *src, अचिन्हित पूर्णांक st);
	पूर्णांक (*set_bp)(काष्ठा src *src, अचिन्हित पूर्णांक bp);
	पूर्णांक (*set_cisz)(काष्ठा src *src, अचिन्हित पूर्णांक cisz);
	पूर्णांक (*set_ca)(काष्ठा src *src, अचिन्हित पूर्णांक ca);
	पूर्णांक (*set_sa)(काष्ठा src *src, अचिन्हित पूर्णांक sa);
	पूर्णांक (*set_la)(काष्ठा src *src, अचिन्हित पूर्णांक la);
	पूर्णांक (*set_pitch)(काष्ठा src *src, अचिन्हित पूर्णांक pitch);
	पूर्णांक (*set_clr_zbufs)(काष्ठा src *src);
	पूर्णांक (*commit_ग_लिखो)(काष्ठा src *src);
	पूर्णांक (*get_ca)(काष्ठा src *src);
	पूर्णांक (*init)(काष्ठा src *src);
	काष्ठा src* (*next_पूर्णांकerleave)(काष्ठा src *src);
पूर्ण;

/* Define src resource request description info */
काष्ठा src_desc अणु
	/* Number of contiguous master srcs क्रम पूर्णांकerleaved usage */
	अचिन्हित अक्षर multi;
	अचिन्हित अक्षर msr;
	अचिन्हित अक्षर mode; /* Working mode of the requested srcs */
पूर्ण;

/* Define src manager object */
काष्ठा src_mgr अणु
	काष्ठा rsc_mgr mgr;	/* Basic resource manager info */
	काष्ठा snd_card *card;	/* poपूर्णांकer to this card */
	spinlock_t mgr_lock;

	 /* request src resource */
	पूर्णांक (*get_src)(काष्ठा src_mgr *mgr,
		       स्थिर काष्ठा src_desc *desc, काष्ठा src **rsrc);
	/* वापस src resource */
	पूर्णांक (*put_src)(काष्ठा src_mgr *mgr, काष्ठा src *src);
	पूर्णांक (*src_enable_s)(काष्ठा src_mgr *mgr, काष्ठा src *src);
	पूर्णांक (*src_enable)(काष्ठा src_mgr *mgr, काष्ठा src *src);
	पूर्णांक (*src_disable)(काष्ठा src_mgr *mgr, काष्ठा src *src);
	पूर्णांक (*commit_ग_लिखो)(काष्ठा src_mgr *mgr);
पूर्ण;

/* Define the descriptor of a SRC Input Mapper resource */
काष्ठा srcimp_mgr;
काष्ठा srcimp_rsc_ops;

काष्ठा srcimp अणु
	काष्ठा rsc rsc;
	अचिन्हित अक्षर idx[8];
	काष्ठा imapper *imappers;
	अचिन्हित पूर्णांक mapped; /* A bit-map indicating which conj rsc is mapped */
	काष्ठा srcimp_mgr *mgr;
	स्थिर काष्ठा srcimp_rsc_ops *ops;
पूर्ण;

काष्ठा srcimp_rsc_ops अणु
	पूर्णांक (*map)(काष्ठा srcimp *srcimp, काष्ठा src *user, काष्ठा rsc *input);
	पूर्णांक (*unmap)(काष्ठा srcimp *srcimp);
पूर्ण;

/* Define SRCIMP resource request description info */
काष्ठा srcimp_desc अणु
	अचिन्हित पूर्णांक msr;
पूर्ण;

काष्ठा srcimp_mgr अणु
	काष्ठा rsc_mgr mgr;	/* Basic resource manager info */
	काष्ठा snd_card *card;	/* poपूर्णांकer to this card */
	spinlock_t mgr_lock;
	spinlock_t imap_lock;
	काष्ठा list_head imappers;
	काष्ठा imapper *init_imap;
	अचिन्हित पूर्णांक init_imap_added;

	 /* request srcimp resource */
	पूर्णांक (*get_srcimp)(काष्ठा srcimp_mgr *mgr,
			  स्थिर काष्ठा srcimp_desc *desc,
			  काष्ठा srcimp **rsrcimp);
	/* वापस srcimp resource */
	पूर्णांक (*put_srcimp)(काष्ठा srcimp_mgr *mgr, काष्ठा srcimp *srcimp);
	पूर्णांक (*imap_add)(काष्ठा srcimp_mgr *mgr, काष्ठा imapper *entry);
	पूर्णांक (*imap_delete)(काष्ठा srcimp_mgr *mgr, काष्ठा imapper *entry);
पूर्ण;

/* Conकाष्ठाor and deकाष्ठाor of SRC resource manager */
पूर्णांक src_mgr_create(काष्ठा hw *hw, काष्ठा src_mgr **rsrc_mgr);
पूर्णांक src_mgr_destroy(काष्ठा src_mgr *src_mgr);
/* Conकाष्ठाor and deकाष्ठाor of SRCIMP resource manager */
पूर्णांक srcimp_mgr_create(काष्ठा hw *hw, काष्ठा srcimp_mgr **rsrc_mgr);
पूर्णांक srcimp_mgr_destroy(काष्ठा srcimp_mgr *srcimp_mgr);

#पूर्ण_अगर /* CTSRC_H */
