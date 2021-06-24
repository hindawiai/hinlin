<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-or-later OR BSD-2-Clause)
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2006 David Gibson, IBM Corporation.
 *     EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#समावेश "libfdt_env.h"

#समावेश <fdt.h>
#समावेश <libfdt.h>

#समावेश "libfdt_internal.h"

काष्ठा fdt_errtabent अणु
	स्थिर अक्षर *str;
पूर्ण;

#घोषणा FDT_ERRTABENT(val) \
	[(val)] = अणु .str = #val, पूर्ण

अटल काष्ठा fdt_errtabent fdt_errtable[] = अणु
	FDT_ERRTABENT(FDT_ERR_NOTFOUND),
	FDT_ERRTABENT(FDT_ERR_EXISTS),
	FDT_ERRTABENT(FDT_ERR_NOSPACE),

	FDT_ERRTABENT(FDT_ERR_BADOFFSET),
	FDT_ERRTABENT(FDT_ERR_BADPATH),
	FDT_ERRTABENT(FDT_ERR_BADPHANDLE),
	FDT_ERRTABENT(FDT_ERR_BADSTATE),

	FDT_ERRTABENT(FDT_ERR_TRUNCATED),
	FDT_ERRTABENT(FDT_ERR_BADMAGIC),
	FDT_ERRTABENT(FDT_ERR_BADVERSION),
	FDT_ERRTABENT(FDT_ERR_BADSTRUCTURE),
	FDT_ERRTABENT(FDT_ERR_BADLAYOUT),
	FDT_ERRTABENT(FDT_ERR_INTERNAL),
	FDT_ERRTABENT(FDT_ERR_BADNCELLS),
	FDT_ERRTABENT(FDT_ERR_BADVALUE),
	FDT_ERRTABENT(FDT_ERR_BADOVERLAY),
	FDT_ERRTABENT(FDT_ERR_NOPHANDLES),
	FDT_ERRTABENT(FDT_ERR_BADFLAGS),
पूर्ण;
#घोषणा FDT_ERRTABSIZE	((पूर्णांक)(माप(fdt_errtable) / माप(fdt_errtable[0])))

स्थिर अक्षर *fdt_म_त्रुटि(पूर्णांक errval)
अणु
	अगर (errval > 0)
		वापस "<valid offset/length>";
	अन्यथा अगर (errval == 0)
		वापस "<no error>";
	अन्यथा अगर (-errval < FDT_ERRTABSIZE) अणु
		स्थिर अक्षर *s = fdt_errtable[-errval].str;

		अगर (s)
			वापस s;
	पूर्ण

	वापस "<unknown error>";
पूर्ण
