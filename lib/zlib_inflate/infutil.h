<शैली गुरु>
/* infutil.h -- types and macros common to blocks and codes
 * Copyright (C) 1995-1998 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h 
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the compression library and is
   subject to change. Applications should only use zlib.h.
 */

#अगर_अघोषित _INFUTIL_H
#घोषणा _INFUTIL_H

#समावेश <linux/zlib.h>
#अगर_घोषित CONFIG_ZLIB_DFLTCC
#समावेश "../zlib_dfltcc/dfltcc.h"
#समावेश <यंत्र/page.h>
#पूर्ण_अगर

/* memory allocation क्रम inflation */

काष्ठा inflate_workspace अणु
	काष्ठा inflate_state inflate_state;
#अगर_घोषित CONFIG_ZLIB_DFLTCC
	काष्ठा dfltcc_state dfltcc_state;
	अचिन्हित अक्षर working_winकरोw[(1 << MAX_WBITS) + PAGE_SIZE];
#अन्यथा
	अचिन्हित अक्षर working_winकरोw[(1 << MAX_WBITS)];
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_ZLIB_DFLTCC
/* dfltcc_state must be द्विगुनword aligned क्रम DFLTCC call */
अटल_निश्चित(दुरत्व(काष्ठा inflate_workspace, dfltcc_state) % 8 == 0);
#पूर्ण_अगर

#घोषणा WS(strm) ((काष्ठा inflate_workspace *)(strm->workspace))

#पूर्ण_अगर
