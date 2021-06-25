<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwarf-regs.c : Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.
 *
 * Copyright (C) 2013 Cavium, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#समावेश <मानकपन.स>
#समावेश <dwarf-regs.h>

अटल स्थिर अक्षर *mips_gpr_names[32] = अणु
	"$0", "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9",
	"$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19",
	"$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29",
	"$30", "$31"
पूर्ण;

स्थिर अक्षर *get_arch_regstr(अचिन्हित पूर्णांक n)
अणु
	अगर (n < 32)
		वापस mips_gpr_names[n];
	अगर (n == 64)
		वापस "hi";
	अगर (n == 65)
		वापस "lo";
	वापस शून्य;
पूर्ण
