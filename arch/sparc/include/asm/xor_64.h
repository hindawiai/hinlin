<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/यंत्र/xor.h
 *
 * High speed xor_block operation क्रम RAID4/5 utilizing the
 * UltraSparc Visual Inकाष्ठाion Set and Niagara block-init
 * twin-load inकाष्ठाions.
 *
 * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)
 * Copyright (C) 2006 David S. Miller <davem@davemloft.net>
 */

#समावेश <यंत्र/spitfire.h>

व्योम xor_vis_2(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);
व्योम xor_vis_3(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
	       अचिन्हित दीर्घ *);
व्योम xor_vis_4(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
	       अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);
व्योम xor_vis_5(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
	       अचिन्हित दीर्घ *, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);

/* XXX Ugh, ग_लिखो cheetah versions... -DaveM */

अटल काष्ठा xor_block_ढाँचा xor_block_VIS = अणु
        .name	= "VIS",
        .करो_2	= xor_vis_2,
        .करो_3	= xor_vis_3,
        .करो_4	= xor_vis_4,
        .करो_5	= xor_vis_5,
पूर्ण;

व्योम xor_niagara_2(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);
व्योम xor_niagara_3(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
		   अचिन्हित दीर्घ *);
व्योम xor_niagara_4(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
		   अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);
व्योम xor_niagara_5(अचिन्हित दीर्घ, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *,
		   अचिन्हित दीर्घ *, अचिन्हित दीर्घ *, अचिन्हित दीर्घ *);

अटल काष्ठा xor_block_ढाँचा xor_block_niagara = अणु
        .name	= "Niagara",
        .करो_2	= xor_niagara_2,
        .करो_3	= xor_niagara_3,
        .करो_4	= xor_niagara_4,
        .करो_5	= xor_niagara_5,
पूर्ण;

#अघोषित XOR_TRY_TEMPLATES
#घोषणा XOR_TRY_TEMPLATES				\
	करो अणु						\
		xor_speed(&xor_block_VIS);		\
		xor_speed(&xor_block_niagara);		\
	पूर्ण जबतक (0)

/* For VIS क्रम everything except Niagara.  */
#घोषणा XOR_SELECT_TEMPLATE(FASTEST) \
	((tlb_type == hypervisor && \
	  (sun4v_chip_type == SUN4V_CHIP_NIAGARA1 || \
	   sun4v_chip_type == SUN4V_CHIP_NIAGARA2 || \
	   sun4v_chip_type == SUN4V_CHIP_NIAGARA3 || \
	   sun4v_chip_type == SUN4V_CHIP_NIAGARA4 || \
	   sun4v_chip_type == SUN4V_CHIP_NIAGARA5)) ? \
	 &xor_block_niagara : \
	 &xor_block_VIS)
