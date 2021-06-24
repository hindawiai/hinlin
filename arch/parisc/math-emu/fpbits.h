<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *
 * Floating-poपूर्णांक emulation code
 *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) <bame@debian.org>
 */

#अगर_घोषित __NO_PA_HDRS
    PA header file -- करो not include this header file क्रम non-PA builds.
#पूर्ण_अगर


/*
 *  These macros are deचिन्हित to be portable to all machines that have
 *  a wordsize greater than or equal to 32 bits that support the portable
 *  C compiler and the standard C preprocessor.  Wordsize (शेष 32)
 *  and bitfield assignment (शेष left-to-right,  unlike VAX, PDP-11)
 *  should be predefined using the स्थिरants HOSTWDSZ and BITFRL and
 *  the C compiler "-D" flag (e.g., -DHOSTWDSZ=36 -DBITFLR क्रम the DEC-20).
 *  Note that the macro arguments assume that the पूर्णांकeger being referenced
 *  is a 32-bit पूर्णांकeger (right-justअगरied on the 20) and that bit 0 is the
 *  most signअगरicant bit.
 */

#अगर_अघोषित HOSTWDSZ
#घोषणा	HOSTWDSZ	32
#पूर्ण_अगर


/*###########################  Macros  ######################################*/

/*-------------------------------------------------------------------------
 * NewDeclareBitField_Reference - Declare a काष्ठाure similar to the simulator
 * function "DeclBitfR" except its use is restricted to occur within a larger
 * enclosing काष्ठाure or जोड़ definition.  This declaration is an unnamed
 * काष्ठाure with the argument, name, as the member name and the argument,
 * uname, as the element name. 
 *----------------------------------------------------------------------- */
#घोषणा Bitfield_extract(start, length, object) 	\
    ((object) >> (HOSTWDSZ - (start) - (length)) & 	\
    ((अचिन्हित)-1 >> (HOSTWDSZ - (length))))

#घोषणा Bitfield_चिन्हित_extract(start, length, object) \
    ((पूर्णांक)((object) << start) >> (HOSTWDSZ - (length)))

#घोषणा Bitfield_mask(start, len, object)		\
    ((object) & (((अचिन्हित)-1 >> (HOSTWDSZ-len)) << (HOSTWDSZ-start-len)))

#घोषणा Bitfield_deposit(value,start,len,object)  object = \
    ((object) & ~(((अचिन्हित)-1 >> (HOSTWDSZ-len)) << (HOSTWDSZ-start-len))) | \
    (((value) & ((अचिन्हित)-1 >> (HOSTWDSZ-len))) << (HOSTWDSZ-start-len))
