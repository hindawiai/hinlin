<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/compr_mm.h
 *
 * Memory management क्रम pre-boot and ramdisk uncompressors
 *
 * Authors: Alain Knaff <alain@knaff.lu>
 *
 */

#अगर_अघोषित DECOMPR_MM_H
#घोषणा DECOMPR_MM_H

#अगर_घोषित STATIC

/* Code active when included from pre-boot environment: */

/*
 * Some architectures want to ensure there is no local data in their
 * pre-boot environment, so that data can arbitrarily relocated (via
 * GOT references).  This is achieved by defining STATIC_RW_DATA to
 * be null.
 */
#अगर_अघोषित STATIC_RW_DATA
#घोषणा STATIC_RW_DATA अटल
#पूर्ण_अगर

/* A trivial दो_स्मृति implementation, adapted from
 *  दो_स्मृति by Hannu Savolainen 1993 and Matthias Urlichs 1994
 */
STATIC_RW_DATA अचिन्हित दीर्घ दो_स्मृति_ptr;
STATIC_RW_DATA पूर्णांक दो_स्मृति_count;

अटल व्योम *दो_स्मृति(पूर्णांक size)
अणु
	व्योम *p;

	अगर (size < 0)
		वापस शून्य;
	अगर (!दो_स्मृति_ptr)
		दो_स्मृति_ptr = मुक्त_mem_ptr;

	दो_स्मृति_ptr = (दो_स्मृति_ptr + 3) & ~3;     /* Align */

	p = (व्योम *)दो_स्मृति_ptr;
	दो_स्मृति_ptr += size;

	अगर (मुक्त_mem_end_ptr && दो_स्मृति_ptr >= मुक्त_mem_end_ptr)
		वापस शून्य;

	दो_स्मृति_count++;
	वापस p;
पूर्ण

अटल व्योम मुक्त(व्योम *where)
अणु
	दो_स्मृति_count--;
	अगर (!दो_स्मृति_count)
		दो_स्मृति_ptr = मुक्त_mem_ptr;
पूर्ण

#घोषणा large_दो_स्मृति(a) दो_स्मृति(a)
#घोषणा large_मुक्त(a) मुक्त(a)

#घोषणा INIT

#अन्यथा /* STATIC */

/* Code active when compiled standalone क्रम use when loading ramdisk: */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

/* Use defines rather than अटल अंतरभूत in order to aव्योम spurious
 * warnings when not needed (indeed large_दो_स्मृति / large_मुक्त are not
 * needed by inflate */

#घोषणा दो_स्मृति(a) kदो_स्मृति(a, GFP_KERNEL)
#घोषणा मुक्त(a) kमुक्त(a)

#घोषणा large_दो_स्मृति(a) vदो_स्मृति(a)
#घोषणा large_मुक्त(a) vमुक्त(a)

#घोषणा INIT __init
#घोषणा STATIC

#समावेश <linux/init.h>

#पूर्ण_अगर /* STATIC */

#पूर्ण_अगर /* DECOMPR_MM_H */
