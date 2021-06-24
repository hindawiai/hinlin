<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPU local store allocation routines
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_csa.h>
#समावेश <यंत्र/mmu.h>

#समावेश "spufs.h"

पूर्णांक spu_alloc_lscsa(काष्ठा spu_state *csa)
अणु
	काष्ठा spu_lscsa *lscsa;
	अचिन्हित अक्षर *p;

	lscsa = vzalloc(माप(*lscsa));
	अगर (!lscsa)
		वापस -ENOMEM;
	csa->lscsa = lscsa;

	/* Set LS pages reserved to allow क्रम user-space mapping. */
	क्रम (p = lscsa->ls; p < lscsa->ls + LS_SIZE; p += PAGE_SIZE)
		SetPageReserved(vदो_स्मृति_to_page(p));

	वापस 0;
पूर्ण

व्योम spu_मुक्त_lscsa(काष्ठा spu_state *csa)
अणु
	/* Clear reserved bit beक्रमe vमुक्त. */
	अचिन्हित अक्षर *p;

	अगर (csa->lscsa == शून्य)
		वापस;

	क्रम (p = csa->lscsa->ls; p < csa->lscsa->ls + LS_SIZE; p += PAGE_SIZE)
		ClearPageReserved(vदो_स्मृति_to_page(p));

	vमुक्त(csa->lscsa);
पूर्ण
