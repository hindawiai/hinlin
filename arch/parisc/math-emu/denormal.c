<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *
 * Floating-poपूर्णांक emulation code
 *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) <bame@debian.org>
 */
/*
 * BEGIN_DESC
 *
 *  File:
 *	@(#)	pa/fp/denormal.c		$ Revision: $
 *
 *  Purpose:
 *	<<please update with a synopsis of the functionality provided by this file>>
 *
 *  External Interfaces:
 *	<<the following list was स्वतःgenerated, please review>>
 *	dbl_denormalize(dbl_opndp1,dbl_opndp2,inexactflag,rmode)
 *	sgl_denormalize(sgl_opnd,inexactflag,rmode)
 *
 *  Internal Interfaces:
 *	<<please update>>
 *
 *  Theory:
 *	<<please update with a overview of the operation of this file>>
 *
 * END_DESC
*/



#समावेश "float.h"
#समावेश "sgl_float.h"
#समावेश "dbl_float.h"
#समावेश "hppa.h"
#समावेश <linux/kernel.h>
/* #समावेश <machine/sys/mdep_निजी.h> */

#अघोषित Fpustatus_रेजिस्टर
#घोषणा Fpustatus_रेजिस्टर Fpu_रेजिस्टर[0]

व्योम
sgl_denormalize(अचिन्हित पूर्णांक *sgl_opnd, boolean *inexactflag, पूर्णांक rmode)
अणु
	अचिन्हित पूर्णांक opnd;
	पूर्णांक sign, exponent;
	boolean guardbit = FALSE, stickybit, inexact;

	opnd = *sgl_opnd;
	stickybit = *inexactflag;
        exponent = Sgl_exponent(opnd) - SGL_WRAP;
        sign = Sgl_sign(opnd);
	Sgl_denormalize(opnd,exponent,guardbit,stickybit,inexact);
	अगर (inexact) अणु
	    चयन (rmode) अणु
	      हाल ROUNDPLUS:
		अगर (sign == 0) अणु
			Sgl_increment(opnd);
		पूर्ण
		अवरोध;
	      हाल ROUNDMINUS:
		अगर (sign != 0) अणु
			Sgl_increment(opnd);
		पूर्ण
		अवरोध;
	      हाल ROUNDNEAREST:
		अगर (guardbit && (stickybit || 
		       Sgl_isone_lowmantissa(opnd))) अणु
			   Sgl_increment(opnd);
		पूर्ण
		अवरोध;
	    पूर्ण
	पूर्ण
	Sgl_set_sign(opnd,sign);
	*sgl_opnd = opnd;
	*inexactflag = inexact;
	वापस;
पूर्ण

व्योम
dbl_denormalize(अचिन्हित पूर्णांक *dbl_opndp1,
	अचिन्हित पूर्णांक * dbl_opndp2,
	boolean *inexactflag,
	पूर्णांक rmode)
अणु
	अचिन्हित पूर्णांक opndp1, opndp2;
	पूर्णांक sign, exponent;
	boolean guardbit = FALSE, stickybit, inexact;

	opndp1 = *dbl_opndp1;
	opndp2 = *dbl_opndp2;
	stickybit = *inexactflag;
	exponent = Dbl_exponent(opndp1) - DBL_WRAP;
	sign = Dbl_sign(opndp1);
	Dbl_denormalize(opndp1,opndp2,exponent,guardbit,stickybit,inexact);
	अगर (inexact) अणु
	    चयन (rmode) अणु
	      हाल ROUNDPLUS:
		अगर (sign == 0) अणु
			Dbl_increment(opndp1,opndp2);
		पूर्ण
		अवरोध;
	      हाल ROUNDMINUS:
		अगर (sign != 0) अणु
			Dbl_increment(opndp1,opndp2);
		पूर्ण
		अवरोध;
	      हाल ROUNDNEAREST:
		अगर (guardbit && (stickybit || 
		       Dbl_isone_lowmantissap2(opndp2))) अणु
			   Dbl_increment(opndp1,opndp2);
		पूर्ण
		अवरोध;
	    पूर्ण
	पूर्ण
	Dbl_set_sign(opndp1,sign);
	*dbl_opndp1 = opndp1;
	*dbl_opndp2 = opndp2;
	*inexactflag = inexact;
	वापस;
पूर्ण
