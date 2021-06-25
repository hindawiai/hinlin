<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
-------------------------------------------------------------------------------
The macro `BITS64' can be defined to indicate that 64-bit पूर्णांकeger types are
supported by the compiler.
-------------------------------------------------------------------------------
*/
#घोषणा BITS64

/*
-------------------------------------------------------------------------------
Each of the following `प्रकार's defines the most convenient type that holds
पूर्णांकegers of at least as many bits as specअगरied.  For example, `uपूर्णांक8' should
be the most convenient type that can hold अचिन्हित पूर्णांकegers of as many as
8 bits.  The `flag' type must be able to hold either a 0 or 1.  For most
implementations of C, `flag', `uint8', and `int8' should all be `typedef'ed
to the same as `पूर्णांक'.
-------------------------------------------------------------------------------
*/
प्रकार अक्षर flag;
प्रकार अचिन्हित अक्षर uपूर्णांक8;
प्रकार चिन्हित अक्षर पूर्णांक8;
प्रकार पूर्णांक uपूर्णांक16;
प्रकार पूर्णांक पूर्णांक16;
प्रकार अचिन्हित पूर्णांक uपूर्णांक32;
प्रकार चिन्हित पूर्णांक पूर्णांक32;
#अगर_घोषित BITS64
प्रकार अचिन्हित दीर्घ दीर्घ पूर्णांक bits64;
प्रकार चिन्हित दीर्घ दीर्घ पूर्णांक sbits64;
#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
Each of the following `प्रकार's defines a type that holds पूर्णांकegers
of _exactly_ the number of bits specअगरied.  For instance, क्रम most
implementation of C, `bits16' and `sbits16' should be `typedef'ed to
`अचिन्हित लघु पूर्णांक' and `signed short int' (or `short int'), respectively.
-------------------------------------------------------------------------------
*/
प्रकार अचिन्हित अक्षर bits8;
प्रकार चिन्हित अक्षर sbits8;
प्रकार अचिन्हित लघु पूर्णांक bits16;
प्रकार चिन्हित लघु पूर्णांक sbits16;
प्रकार अचिन्हित पूर्णांक bits32;
प्रकार चिन्हित पूर्णांक sbits32;
#अगर_घोषित BITS64
प्रकार अचिन्हित दीर्घ दीर्घ पूर्णांक uपूर्णांक64;
प्रकार चिन्हित दीर्घ दीर्घ पूर्णांक पूर्णांक64;
#पूर्ण_अगर

#अगर_घोषित BITS64
/*
-------------------------------------------------------------------------------
The `LIT64' macro takes as its argument a textual पूर्णांकeger literal and अगर
necessary ``marks'' the literal as having a 64-bit पूर्णांकeger type.  For
example, the Gnu C Compiler (`gcc') requires that 64-bit literals be
appended with the letters `LL' standing for `long long', which is `gcc's
name क्रम the 64-bit पूर्णांकeger type.  Some compilers may allow `LIT64' to be
defined as the identity macro:  `#घोषणा LIT64( a ) a'.
-------------------------------------------------------------------------------
*/
#घोषणा LIT64( a ) a##LL
#पूर्ण_अगर

/*
-------------------------------------------------------------------------------
The macro `INLINE' can be used beक्रमe functions that should be अंतरभूतd.  If
a compiler करोes not support explicit inlining, this macro should be defined
to be `अटल'.
-------------------------------------------------------------------------------
*/
#घोषणा INLINE अटल अंतरभूत


/* For use as a GCC soft-भग्न library we need some special function names. */

#अगर_घोषित __LIBFLOAT__

/* Some 32-bit ops can be mapped straight across by just changing the name. */
#घोषणा भग्न32_add			__addsf3
#घोषणा भग्न32_sub			__subsf3
#घोषणा भग्न32_mul			__mulsf3
#घोषणा भग्न32_भाग			__भागsf3
#घोषणा पूर्णांक32_to_भग्न32		__भग्नsisf
#घोषणा भग्न32_to_पूर्णांक32_round_to_zero	__fixsfsi
#घोषणा भग्न32_to_uपूर्णांक32_round_to_zero	__fixunssfsi

/* These ones go through the glue code.  To aव्योम namespace pollution
   we नाम the पूर्णांकernal functions too.  */
#घोषणा भग्न32_eq			___भग्न32_eq
#घोषणा भग्न32_le			___भग्न32_le
#घोषणा भग्न32_lt			___भग्न32_lt

/* All the 64-bit ops have to go through the glue, so we pull the same
   trick.  */
#घोषणा भग्न64_add			___भग्न64_add
#घोषणा भग्न64_sub			___भग्न64_sub
#घोषणा भग्न64_mul			___भग्न64_mul
#घोषणा भग्न64_भाग			___भग्न64_भाग
#घोषणा पूर्णांक32_to_भग्न64		___पूर्णांक32_to_भग्न64
#घोषणा भग्न64_to_पूर्णांक32_round_to_zero	___भग्न64_to_पूर्णांक32_round_to_zero
#घोषणा भग्न64_to_uपूर्णांक32_round_to_zero	___भग्न64_to_uपूर्णांक32_round_to_zero
#घोषणा भग्न64_to_भग्न32		___भग्न64_to_भग्न32
#घोषणा भग्न32_to_भग्न64		___भग्न32_to_भग्न64
#घोषणा भग्न64_eq			___भग्न64_eq
#घोषणा भग्न64_le			___भग्न64_le
#घोषणा भग्न64_lt			___भग्न64_lt

#अगर 0
#घोषणा भग्न64_add			__adddf3
#घोषणा भग्न64_sub			__subdf3
#घोषणा भग्न64_mul			__muldf3
#घोषणा भग्न64_भाग			__भागdf3
#घोषणा पूर्णांक32_to_भग्न64		__भग्नsidf
#घोषणा भग्न64_to_पूर्णांक32_round_to_zero	__fixdfsi
#घोषणा भग्न64_to_uपूर्णांक32_round_to_zero	__fixunsdfsi
#घोषणा भग्न64_to_भग्न32		__truncdfsf2
#घोषणा भग्न32_to_भग्न64		__extendsfdf2
#पूर्ण_अगर

#पूर्ण_अगर
