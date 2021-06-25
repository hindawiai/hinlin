<शैली गुरु>
#अगर_अघोषित INFTREES_H
#घोषणा INFTREES_H

/* inftrees.h -- header to use inftrees.c
 * Copyright (C) 1995-2005 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the compression library and is
   subject to change. Applications should only use zlib.h.
 */

/* Structure क्रम decoding tables.  Each entry provides either the
   inक्रमmation needed to करो the operation requested by the code that
   indexed that table entry, or it provides a poपूर्णांकer to another
   table that indexes more bits of the code.  op indicates whether
   the entry is a poपूर्णांकer to another table, a literal, a length or
   distance, an end-of-block, or an invalid code.  For a table
   poपूर्णांकer, the low four bits of op is the number of index bits of
   that table.  For a length or distance, the low four bits of op
   is the number of extra bits to get after the code.  bits is
   the number of bits in this code or part of the code to drop off
   of the bit buffer.  val is the actual byte to output in the हाल
   of a literal, the base length or distance, or the offset from
   the current table to the next table.  Each entry is four bytes. */
प्रकार काष्ठा अणु
    अचिन्हित अक्षर op;           /* operation, extra bits, table bits */
    अचिन्हित अक्षर bits;         /* bits in this part of the code */
    अचिन्हित लघु val;         /* offset in table or code value */
पूर्ण code;

/* op values as set by inflate_table():
    00000000 - literal
    0000tttt - table link, tttt != 0 is the number of table index bits
    0001eeee - length or distance, eeee is the number of extra bits
    01100000 - end of block
    01000000 - invalid code
 */

/* Maximum size of dynamic tree.  The maximum found in a दीर्घ but non-
   exhaustive search was 1444 code काष्ठाures (852 क्रम length/literals
   and 592 क्रम distances, the latter actually the result of an
   exhaustive search).  The true maximum is not known, but the value
   below is more than safe. */
#घोषणा ENOUGH 2048
#घोषणा MAXD 592

/* Type of code to build क्रम inftable() */
प्रकार क्रमागत अणु
    CODES,
    LENS,
    DISTS
पूर्ण codetype;

बाह्य पूर्णांक zlib_inflate_table (codetype type, अचिन्हित लघु *lens,
                             अचिन्हित codes, code **table,
                             अचिन्हित *bits, अचिन्हित लघु *work);
#पूर्ण_अगर
