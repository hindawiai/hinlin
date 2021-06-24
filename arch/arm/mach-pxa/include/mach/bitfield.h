<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	खाता    	bitfield.h
 *
 *	Version 	1.1
 *	Author  	Copyright (c) Marc A. Viredaz, 1998
 *	        	DEC Western Research Laboratory, Palo Alto, CA
 *	Date    	April 1998 (April 1997)
 *	System  	Advanced RISC Machine (ARM)
 *	Language	C or ARM Assembly
 *	Purpose 	Definition of macros to operate on bit fields.
 */



#अगर_अघोषित __BITFIELD_H
#घोषणा __BITFIELD_H

#अगर_अघोषित __ASSEMBLY__
#घोषणा UData(Data)	((अचिन्हित दीर्घ) (Data))
#अन्यथा
#घोषणा UData(Data)	(Data)
#पूर्ण_अगर


/*
 * MACRO: Fld
 *
 * Purpose
 *    The macro "Fld" encodes a bit field, given its size and its shअगरt value
 *    with respect to bit 0.
 *
 * Note
 *    A more पूर्णांकuitive way to encode bit fields would have been to use their
 *    mask. However, extracting size and shअगरt value inक्रमmation from a bit
 *    field's mask is cumbersome and might अवरोध the assembler (255-अक्षरacter
 *    line-size limit).
 *
 * Input
 *    Size      	Size of the bit field, in number of bits.
 *    Shft      	Shअगरt value of the bit field with respect to bit 0.
 *
 * Output
 *    Fld       	Encoded bit field.
 */

#घोषणा Fld(Size, Shft)	(((Size) << 16) + (Shft))


/*
 * MACROS: FSize, FShft, FMsk, FAlnMsk, F1stBit
 *
 * Purpose
 *    The macros "FSize", "FShft", "FMsk", "FAlnMsk", and "F1stBit" वापस
 *    the size, shअगरt value, mask, aligned mask, and first bit of a
 *    bit field.
 *
 * Input
 *    Field     	Encoded bit field (using the macro "Fld").
 *
 * Output
 *    FSize     	Size of the bit field, in number of bits.
 *    FShft     	Shअगरt value of the bit field with respect to bit 0.
 *    FMsk      	Mask क्रम the bit field.
 *    FAlnMsk   	Mask क्रम the bit field, aligned on bit 0.
 *    F1stBit   	First bit of the bit field.
 */

#घोषणा FSize(Field)	((Field) >> 16)
#घोषणा FShft(Field)	((Field) & 0x0000FFFF)
#घोषणा FMsk(Field)	(((UData (1) << FSize (Field)) - 1) << FShft (Field))
#घोषणा FAlnMsk(Field)	((UData (1) << FSize (Field)) - 1)
#घोषणा F1stBit(Field)	(UData (1) << FShft (Field))


/*
 * MACRO: FInsrt
 *
 * Purpose
 *    The macro "FInsrt" inserts a value पूर्णांकo a bit field by shअगरting the
 *    क्रमmer appropriately.
 *
 * Input
 *    Value     	Bit-field value.
 *    Field     	Encoded bit field (using the macro "Fld").
 *
 * Output
 *    FInsrt    	Bit-field value positioned appropriately.
 */

#घोषणा FInsrt(Value, Field) \
                	(UData (Value) << FShft (Field))


/*
 * MACRO: FExtr
 *
 * Purpose
 *    The macro "FExtr" extracts the value of a bit field by masking and
 *    shअगरting it appropriately.
 *
 * Input
 *    Data      	Data containing the bit-field to be extracted.
 *    Field     	Encoded bit field (using the macro "Fld").
 *
 * Output
 *    FExtr     	Bit-field value.
 */

#घोषणा FExtr(Data, Field) \
                	((UData (Data) >> FShft (Field)) & FAlnMsk (Field))


#पूर्ण_अगर /* __BITFIELD_H */
