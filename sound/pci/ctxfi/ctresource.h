<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctresource.h
 *
 * @Brief
 * This file contains the definition of generic hardware resources क्रम
 * resource management.
 *
 * @Author	Liu Chun
 * @Date 	May 13 2008
 */

#अगर_अघोषित CTRESOURCE_H
#घोषणा CTRESOURCE_H

#समावेश <linux/types.h>

क्रमागत RSCTYP अणु
	SRC,
	SRCIMP,
	AMIXER,
	SUM,
	DAIO,
	NUM_RSCTYP	/* This must be the last one and less than 16 */
पूर्ण;

काष्ठा rsc_ops;

काष्ठा rsc अणु
	u32 idx:12;	/* The index of a resource */
	u32 type:4;	/* The type (RSCTYP) of a resource */
	u32 conj:12;	/* Current conjugate index */
	u32 msr:4;	/* The Master Sample Rate a resource working on */
	व्योम *ctrl_blk;	/* Chip specअगरic control info block क्रम a resource */
	काष्ठा hw *hw;	/* Chip specअगरic object क्रम hardware access means */
	स्थिर काष्ठा rsc_ops *ops;	/* Generic resource operations */
पूर्ण;

काष्ठा rsc_ops अणु
	पूर्णांक (*master)(काष्ठा rsc *rsc);	/* Move to master resource */
	पूर्णांक (*next_conj)(काष्ठा rsc *rsc); /* Move to next conjugate resource */
	पूर्णांक (*index)(स्थिर काष्ठा rsc *rsc); /* Return the index of resource */
	/* Return the output slot number */
	पूर्णांक (*output_slot)(स्थिर काष्ठा rsc *rsc);
पूर्ण;

पूर्णांक
rsc_init(काष्ठा rsc *rsc, u32 idx, क्रमागत RSCTYP type, u32 msr, काष्ठा hw *hw);
पूर्णांक rsc_uninit(काष्ठा rsc *rsc);

काष्ठा rsc_mgr अणु
	क्रमागत RSCTYP type; /* The type (RSCTYP) of resource to manage */
	अचिन्हित पूर्णांक amount; /* The total amount of a kind of resource */
	अचिन्हित पूर्णांक avail; /* The amount of currently available resources */
	अचिन्हित अक्षर *rscs; /* The bit-map क्रम resource allocation */
	व्योम *ctrl_blk; /* Chip specअगरic control info block */
	काष्ठा hw *hw; /* Chip specअगरic object क्रम hardware access */
पूर्ण;

/* Resource management is based on bit-map mechanism */
पूर्णांक rsc_mgr_init(काष्ठा rsc_mgr *mgr, क्रमागत RSCTYP type,
		 अचिन्हित पूर्णांक amount, काष्ठा hw *hw);
पूर्णांक rsc_mgr_uninit(काष्ठा rsc_mgr *mgr);
पूर्णांक mgr_get_resource(काष्ठा rsc_mgr *mgr, अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक *ridx);
पूर्णांक mgr_put_resource(काष्ठा rsc_mgr *mgr, अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक idx);

#पूर्ण_अगर /* CTRESOURCE_H */
