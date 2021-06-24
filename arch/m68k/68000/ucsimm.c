<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1993 Hamish Macकरोnald
 *  Copyright (C) 1999 D. Jeff Dionne
 *  Copyright (C) 2001 Georges Menie, Ken Desmet
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <यंत्र/bootstd.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/MC68VZ328.h>


#समावेश "m68328.h"

अचिन्हित अक्षर *cs8900a_hwaddr;
अटल पूर्णांक त्रुटि_सं;

_bsc0(अक्षर *, माला_लोerialnum)
_bsc1(अचिन्हित अक्षर *, gethwaddr, पूर्णांक, a)
_bsc1(अक्षर *, getbenv, अक्षर *, a)

व्योम __init init_ucsimm(अक्षर *command, पूर्णांक size)
अणु
	अक्षर *p;

	pr_info("uCsimm/uCdimm serial string [%s]\n", माला_लोerialnum());
	p = cs8900a_hwaddr = gethwaddr(0);
	pr_info("uCsimm/uCdimm hwaddr %pM\n", p);
	p = getbenv("APPEND");
	अगर (p)
		म_नकल(p, command);
	अन्यथा
		command[0] = 0;
पूर्ण
