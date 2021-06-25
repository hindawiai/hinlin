<शैली गुरु>
/* mpi-cmp.c  -  MPI functions
 * Copyright (C) 1998, 1999 Free Software Foundation, Inc.
 *
 * This file is part of GnuPG.
 *
 * GnuPG is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GnuPG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#समावेश "mpi-internal.h"

पूर्णांक mpi_cmp_ui(MPI u, अचिन्हित दीर्घ v)
अणु
	mpi_limb_t limb = v;

	mpi_normalize(u);
	अगर (!u->nlimbs && !limb)
		वापस 0;
	अगर (u->sign)
		वापस -1;
	अगर (u->nlimbs > 1)
		वापस 1;

	अगर (u->d[0] == limb)
		वापस 0;
	अन्यथा अगर (u->d[0] > limb)
		वापस 1;
	अन्यथा
		वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_cmp_ui);

अटल पूर्णांक करो_mpi_cmp(MPI u, MPI v, पूर्णांक असलmode)
अणु
	mpi_माप_प्रकार usize;
	mpi_माप_प्रकार vsize;
	पूर्णांक usign;
	पूर्णांक vsign;
	पूर्णांक cmp;

	mpi_normalize(u);
	mpi_normalize(v);

	usize = u->nlimbs;
	vsize = v->nlimbs;
	usign = असलmode ? 0 : u->sign;
	vsign = असलmode ? 0 : v->sign;

	/* Compare sign bits.  */

	अगर (!usign && vsign)
		वापस 1;
	अगर (usign && !vsign)
		वापस -1;

	/* U and V are either both positive or both negative.  */

	अगर (usize != vsize && !usign && !vsign)
		वापस usize - vsize;
	अगर (usize != vsize && usign && vsign)
		वापस vsize + usize;
	अगर (!usize)
		वापस 0;
	cmp = mpihelp_cmp(u->d, v->d, usize);
	अगर (!cmp)
		वापस 0;
	अगर ((cmp < 0?1:0) == (usign?1:0))
		वापस 1;

	वापस -1;
पूर्ण

पूर्णांक mpi_cmp(MPI u, MPI v)
अणु
	वापस करो_mpi_cmp(u, v, 0);
पूर्ण
EXPORT_SYMBOL_GPL(mpi_cmp);

पूर्णांक mpi_cmpअसल(MPI u, MPI v)
अणु
	वापस करो_mpi_cmp(u, v, 1);
पूर्ण
EXPORT_SYMBOL_GPL(mpi_cmpअसल);
