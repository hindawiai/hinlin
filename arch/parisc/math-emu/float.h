<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *
 * Floating-poपूर्णांक emulation code
 *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) <bame@debian.org>
 */
/*
 * BEGIN_DESC
 * 
 *  File: 
 *      @(#)	pa/spmath/भग्न.स		$Revision: 1.1 $
 * 
 *  Purpose:
 *      <<please update with a synopis of the functionality provided by this file>>
 * 
 *  BE header:  no
 *
 *  Shipped:  yes
 *	/usr/conf/pa/spmath/भग्न.स
 *
 * END_DESC  
*/

#अगर_घोषित __NO_PA_HDRS
    PA header file -- करो not include this header file क्रम non-PA builds.
#पूर्ण_अगर

#समावेश "fpbits.h"
#समावेश "hppa.h"
/*
 * Want to pick up the FPU capability flags, not the PDC काष्ठाures.
 * 'LOCORE' isn't really true in this case, but we don't want the C काष्ठाures
 * so it suits our purposes
 */
#घोषणा LOCORE
#समावेश "fpu.h"

/*
 * Declare the basic काष्ठाures क्रम the 3 dअगरferent
 * भग्नing-poपूर्णांक precisions.
 *        
 * Single number  
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|       exp     |               mantissa                      |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
#घोषणा	Sall(object) (object)
#घोषणा	Ssign(object) Bitfield_extract( 0,  1,object)
#घोषणा	Sचिन्हितsign(object) Bitfield_चिन्हित_extract( 0,  1,object)
#घोषणा	Sexponent(object) Bitfield_extract( 1,  8,object)
#घोषणा	Smantissa(object) Bitfield_mask( 9, 23,object)
#घोषणा	Sसंकेतing(object) Bitfield_extract( 9,  1,object)
#घोषणा	Sसंकेतingnan(object) Bitfield_extract( 1,  9,object)
#घोषणा	Shigh2mantissa(object) Bitfield_extract( 9,  2,object)
#घोषणा	Sexponenपंचांगantissa(object) Bitfield_mask( 1, 31,object)
#घोषणा	Ssignexponent(object) Bitfield_extract( 0,  9,object)
#घोषणा	Shidden(object) Bitfield_extract( 8,  1,object)
#घोषणा	Shiddenoverflow(object) Bitfield_extract( 7,  1,object)
#घोषणा	Shiddenhigh7mantissa(object) Bitfield_extract( 8,  8,object)
#घोषणा	Shiddenhigh3mantissa(object) Bitfield_extract( 8,  4,object)
#घोषणा	Slow(object) Bitfield_mask( 31,  1,object)
#घोषणा	Slow4(object) Bitfield_mask( 28,  4,object)
#घोषणा	Slow31(object) Bitfield_mask( 1, 31,object)
#घोषणा	Shigh31(object) Bitfield_extract( 0, 31,object)
#घोषणा	Sचिन्हितhigh31(object) Bitfield_चिन्हित_extract( 0, 31,object)
#घोषणा	Shigh4(object) Bitfield_extract( 0,  4,object)
#घोषणा	Sbit24(object) Bitfield_extract( 24,  1,object)
#घोषणा	Sbit28(object) Bitfield_extract( 28,  1,object)
#घोषणा	Sbit29(object) Bitfield_extract( 29,  1,object)
#घोषणा	Sbit30(object) Bitfield_extract( 30,  1,object)
#घोषणा	Sbit31(object) Bitfield_mask( 31,  1,object)

#घोषणा Deposit_ssign(object,value) Bitfield_deposit(value,0,1,object)
#घोषणा Deposit_sexponent(object,value) Bitfield_deposit(value,1,8,object)
#घोषणा Deposit_smantissa(object,value) Bitfield_deposit(value,9,23,object)
#घोषणा Deposit_shigh2mantissa(object,value) Bitfield_deposit(value,9,2,object)
#घोषणा Deposit_sexponenपंचांगantissa(object,value) \
    Bitfield_deposit(value,1,31,object)
#घोषणा Deposit_ssignexponent(object,value) Bitfield_deposit(value,0,9,object)
#घोषणा Deposit_slow(object,value) Bitfield_deposit(value,31,1,object)
#घोषणा Deposit_shigh4(object,value) Bitfield_deposit(value,0,4,object)

#घोषणा	Is_ssign(object) Bitfield_mask( 0,  1,object)
#घोषणा	Is_sसंकेतing(object) Bitfield_mask( 9,  1,object)
#घोषणा	Is_shidden(object) Bitfield_mask( 8,  1,object)
#घोषणा	Is_shiddenoverflow(object) Bitfield_mask( 7,  1,object)
#घोषणा	Is_slow(object) Bitfield_mask( 31,  1,object)
#घोषणा	Is_sbit24(object) Bitfield_mask( 24,  1,object)
#घोषणा	Is_sbit28(object) Bitfield_mask( 28,  1,object)
#घोषणा	Is_sbit29(object) Bitfield_mask( 29,  1,object)
#घोषणा	Is_sbit30(object) Bitfield_mask( 30,  1,object)
#घोषणा	Is_sbit31(object) Bitfield_mask( 31,  1,object)

/* 
 * Double number.
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|       exponent      |          mantissa part 1              |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    mantissa part 2                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
#घोषणा Dallp1(object) (object)
#घोषणा Dsign(object) Bitfield_extract( 0,  1,object)
#घोषणा Dचिन्हितsign(object) Bitfield_चिन्हित_extract( 0,  1,object)
#घोषणा Dexponent(object) Bitfield_extract( 1,  11,object)
#घोषणा Dmantissap1(object) Bitfield_mask( 12, 20,object)
#घोषणा Dसंकेतing(object) Bitfield_extract( 12,  1,object)
#घोषणा Dसंकेतingnan(object) Bitfield_extract( 1,  12,object)
#घोषणा Dhigh2mantissa(object) Bitfield_extract( 12,  2,object)
#घोषणा Dexponenपंचांगantissap1(object) Bitfield_mask( 1, 31,object)
#घोषणा Dsignexponent(object) Bitfield_extract( 0, 12,object)
#घोषणा Dhidden(object) Bitfield_extract( 11,  1,object)
#घोषणा Dhiddenoverflow(object) Bitfield_extract( 10,  1,object)
#घोषणा Dhiddenhigh7mantissa(object) Bitfield_extract( 11,  8,object)
#घोषणा Dhiddenhigh3mantissa(object) Bitfield_extract( 11,  4,object)
#घोषणा Dlowp1(object) Bitfield_mask( 31,  1,object)
#घोषणा Dlow31p1(object) Bitfield_mask( 1, 31,object)
#घोषणा Dhighp1(object) Bitfield_extract( 0,  1,object)
#घोषणा Dhigh4p1(object) Bitfield_extract( 0,  4,object)
#घोषणा Dhigh31p1(object) Bitfield_extract( 0, 31,object)
#घोषणा Dचिन्हितhigh31p1(object) Bitfield_चिन्हित_extract( 0, 31,object)
#घोषणा Dbit3p1(object) Bitfield_extract( 3,  1,object)

#घोषणा Deposit_dsign(object,value) Bitfield_deposit(value,0,1,object)
#घोषणा Deposit_dexponent(object,value) Bitfield_deposit(value,1,11,object)
#घोषणा Deposit_dmantissap1(object,value) Bitfield_deposit(value,12,20,object)
#घोषणा Deposit_dhigh2mantissa(object,value) Bitfield_deposit(value,12,2,object)
#घोषणा Deposit_dexponenपंचांगantissap1(object,value) \
    Bitfield_deposit(value,1,31,object)
#घोषणा Deposit_dsignexponent(object,value) Bitfield_deposit(value,0,12,object)
#घोषणा Deposit_dlowp1(object,value) Bitfield_deposit(value,31,1,object)
#घोषणा Deposit_dhigh4p1(object,value) Bitfield_deposit(value,0,4,object)

#घोषणा Is_dsign(object) Bitfield_mask( 0,  1,object)
#घोषणा Is_dसंकेतing(object) Bitfield_mask( 12,  1,object)
#घोषणा Is_dhidden(object) Bitfield_mask( 11,  1,object)
#घोषणा Is_dhiddenoverflow(object) Bitfield_mask( 10,  1,object)
#घोषणा Is_dlowp1(object) Bitfield_mask( 31,  1,object)
#घोषणा Is_dhighp1(object) Bitfield_mask( 0,  1,object)
#घोषणा Is_dbit3p1(object) Bitfield_mask( 3,  1,object)

#घोषणा Dallp2(object) (object)
#घोषणा Dmantissap2(object) (object)
#घोषणा Dlowp2(object) Bitfield_mask( 31,  1,object)
#घोषणा Dlow4p2(object) Bitfield_mask( 28,  4,object)
#घोषणा Dlow31p2(object) Bitfield_mask( 1, 31,object)
#घोषणा Dhighp2(object) Bitfield_extract( 0,  1,object)
#घोषणा Dhigh31p2(object) Bitfield_extract( 0, 31,object)
#घोषणा Dbit2p2(object) Bitfield_extract( 2,  1,object)
#घोषणा Dbit3p2(object) Bitfield_extract( 3,  1,object)
#घोषणा Dbit21p2(object) Bitfield_extract( 21,  1,object)
#घोषणा Dbit28p2(object) Bitfield_extract( 28,  1,object)
#घोषणा Dbit29p2(object) Bitfield_extract( 29,  1,object)
#घोषणा Dbit30p2(object) Bitfield_extract( 30,  1,object)
#घोषणा Dbit31p2(object) Bitfield_mask( 31,  1,object)

#घोषणा Deposit_dlowp2(object,value) Bitfield_deposit(value,31,1,object)

#घोषणा Is_dlowp2(object) Bitfield_mask( 31,  1,object)
#घोषणा Is_dhighp2(object) Bitfield_mask( 0,  1,object)
#घोषणा Is_dbit2p2(object) Bitfield_mask( 2,  1,object)
#घोषणा Is_dbit3p2(object) Bitfield_mask( 3,  1,object)
#घोषणा Is_dbit21p2(object) Bitfield_mask( 21,  1,object)
#घोषणा Is_dbit28p2(object) Bitfield_mask( 28,  1,object)
#घोषणा Is_dbit29p2(object) Bitfield_mask( 29,  1,object)
#घोषणा Is_dbit30p2(object) Bitfield_mask( 30,  1,object)
#घोषणा Is_dbit31p2(object) Bitfield_mask( 31,  1,object)

/* 
 * Quad number.
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|          exponent           |      mantissa part 1          |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    mantissa part 2                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    mantissa part 3                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    mantissa part 4                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
प्रकार काष्ठा
    अणु
    जोड़
	अणु
	काष्ठा अणु अचिन्हित qallp1; पूर्ण u_qallp1;
/* Not needed क्रम now...
	Bitfield_extract( 0,  1,u_qsign,qsign)
	Bitfield_चिन्हित_extract( 0,  1,u_qचिन्हितsign,qचिन्हितsign)
	Bitfield_extract( 1, 15,u_qexponent,qexponent)
	Bitfield_extract(16, 16,u_qmantissap1,qmantissap1)
	Bitfield_extract(16,  1,u_qसंकेतing,qसंकेतing)
	Bitfield_extract(1,  16,u_qसंकेतingnan,qसंकेतingnan)
	Bitfield_extract(16,  2,u_qhigh2mantissa,qhigh2mantissa)
	Bitfield_extract( 1, 31,u_qexponenपंचांगantissap1,qexponenपंचांगantissap1)
	Bitfield_extract( 0, 16,u_qsignexponent,qsignexponent)
	Bitfield_extract(15,  1,u_qhidden,qhidden)
	Bitfield_extract(14,  1,u_qhiddenoverflow,qhiddenoverflow)
	Bitfield_extract(15,  8,u_qhiddenhigh7mantissa,qhiddenhigh7mantissa)
	Bitfield_extract(15,  4,u_qhiddenhigh3mantissa,qhiddenhigh3mantissa)
	Bitfield_extract(31,  1,u_qlowp1,qlowp1)
	Bitfield_extract( 1, 31,u_qlow31p1,qlow31p1)
	Bitfield_extract( 0,  1,u_qhighp1,qhighp1)
	Bitfield_extract( 0,  4,u_qhigh4p1,qhigh4p1)
	Bitfield_extract( 0, 31,u_qhigh31p1,qhigh31p1)
  */
	पूर्ण quad_u1;
    जोड़
	अणु
	काष्ठा अणु अचिन्हित qallp2; पूर्ण u_qallp2;
  /* Not needed क्रम now...
	Bitfield_extract(31,  1,u_qlowp2,qlowp2)
	Bitfield_extract( 1, 31,u_qlow31p2,qlow31p2)
	Bitfield_extract( 0,  1,u_qhighp2,qhighp2)
	Bitfield_extract( 0, 31,u_qhigh31p2,qhigh31p2)
   */
	पूर्ण quad_u2;
    जोड़
	अणु
	काष्ठा अणु अचिन्हित qallp3; पूर्ण u_qallp3;
  /* Not needed क्रम now...
	Bitfield_extract(31,  1,u_qlowp3,qlowp3)
	Bitfield_extract( 1, 31,u_qlow31p3,qlow31p3)
	Bitfield_extract( 0,  1,u_qhighp3,qhighp3)
	Bitfield_extract( 0, 31,u_qhigh31p3,qhigh31p3)
   */ 
	पूर्ण quad_u3;
    जोड़
	अणु
	काष्ठा अणु अचिन्हित qallp4; पूर्ण u_qallp4;
    /* Not need क्रम now...
	Bitfield_extract(31,  1,u_qlowp4,qlowp4)
	Bitfield_extract( 1, 31,u_qlow31p4,qlow31p4)
	Bitfield_extract( 0,  1,u_qhighp4,qhighp4)
	Bitfield_extract( 0, 31,u_qhigh31p4,qhigh31p4)
     */
	पूर्ण quad_u4;
    पूर्ण quad_भग्नing_poपूर्णांक;

/* Extension - An additional काष्ठाure to hold the guard, round and
 *             sticky bits during computations.
 */
#घोषणा Extall(object) (object)
#घोषणा Extsign(object) Bitfield_extract( 0,  1,object)
#घोषणा Exthigh31(object) Bitfield_extract( 0, 31,object)
#घोषणा Extlow31(object) Bitfield_extract( 1, 31,object)
#घोषणा Extlow(object) Bitfield_extract( 31,  1,object)

/*
 * Single extended - The upper word is just like single precision,
 *                 but one additional word of mantissa is needed.
 */
#घोषणा Sextallp1(object) (object)
#घोषणा Sextallp2(object) (object)
#घोषणा Sextlowp1(object) Bitfield_extract( 31,  1,object)
#घोषणा Sexthighp2(object) Bitfield_extract( 0,  1,object)
#घोषणा Sextlow31p2(object) Bitfield_extract( 1, 31,object)
#घोषणा Sexthiddenoverflow(object) Bitfield_extract( 4,  1,object)
#घोषणा Is_sexthiddenoverflow(object) Bitfield_mask( 4,  1,object)

/*
 * Double extended - The upper two words are just like द्विगुन precision,
 *		     but two additional words of mantissa are needed.
 */
#घोषणा Dextallp1(object) (object)
#घोषणा Dextallp2(object) (object)
#घोषणा Dextallp3(object) (object)
#घोषणा Dextallp4(object) (object)
#घोषणा Dextlowp2(object) Bitfield_extract( 31,  1,object)
#घोषणा Dexthighp3(object) Bitfield_extract( 0,  1,object)
#घोषणा Dextlow31p3(object) Bitfield_extract( 1, 31,object)
#घोषणा Dexthiddenoverflow(object) Bitfield_extract( 10,  1,object)
#घोषणा Is_dexthiddenoverflow(object) Bitfield_mask( 10,  1,object)
#घोषणा Deposit_dextlowp4(object,value) Bitfield_deposit(value,31,1,object)

/*
 * Declare the basic काष्ठाures क्रम the 3 dअगरferent
 * fixed-poपूर्णांक precisions.
 *        
 * Single number  
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|                    पूर्णांकeger                                  |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
प्रकार पूर्णांक sgl_पूर्णांकeger;

/* 
 * Double number.
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|                     high पूर्णांकeger                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                       low पूर्णांकeger                             |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
काष्ठा dपूर्णांक अणु
        पूर्णांक  wd0;
        अचिन्हित पूर्णांक wd1;
पूर्ण;

काष्ठा dblwd अणु
        अचिन्हित पूर्णांक wd0;
        अचिन्हित पूर्णांक wd1;
पूर्ण;

/* 
 * Quad number.
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|                  पूर्णांकeger part1                              |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    पूर्णांकeger part 2                             |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    पूर्णांकeger part 3                             |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    पूर्णांकeger part 4                             |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */

काष्ठा quadwd अणु
        पूर्णांक  wd0;
        अचिन्हित पूर्णांक wd1;
        अचिन्हित पूर्णांक wd2;
        अचिन्हित पूर्णांक wd3;
पूर्ण;

प्रकार काष्ठा quadwd quad_पूर्णांकeger;


/* useful प्रकारs */
प्रकार अचिन्हित पूर्णांक sgl_भग्नing_poपूर्णांक;
प्रकार काष्ठा dblwd dbl_भग्नing_poपूर्णांक;
प्रकार काष्ठा dपूर्णांक dbl_पूर्णांकeger;
प्रकार काष्ठा dblwd dbl_अचिन्हित;

/* 
 * Define the dअगरferent precisions' parameters.
 */
#घोषणा SGL_BITLENGTH 32
#घोषणा SGL_EMAX 127
#घोषणा SGL_EMIN (-126)
#घोषणा SGL_BIAS 127
#घोषणा SGL_WRAP 192
#घोषणा SGL_अनन्त_EXPONENT (SGL_EMAX+SGL_BIAS+1)
#घोषणा SGL_THRESHOLD 32
#घोषणा SGL_EXP_LENGTH 8
#घोषणा SGL_P 24

#घोषणा DBL_BITLENGTH 64
#घोषणा DBL_EMAX 1023
#घोषणा DBL_EMIN (-1022)
#घोषणा DBL_BIAS 1023
#घोषणा DBL_WRAP 1536
#घोषणा DBL_अनन्त_EXPONENT (DBL_EMAX+DBL_BIAS+1)
#घोषणा DBL_THRESHOLD 64
#घोषणा DBL_EXP_LENGTH 11
#घोषणा DBL_P 53

#घोषणा QUAD_BITLENGTH 128
#घोषणा QUAD_EMAX 16383
#घोषणा QUAD_EMIN (-16382)
#घोषणा QUAD_BIAS 16383
#घोषणा QUAD_WRAP 24576
#घोषणा QUAD_अनन्त_EXPONENT (QUAD_EMAX+QUAD_BIAS+1)
#घोषणा QUAD_P 113

/* Boolean Values etc. */
#घोषणा FALSE 0
#घोषणा TRUE (!FALSE)
#घोषणा NOT !
#घोषणा XOR ^

/* other स्थिरants */
#अघोषित शून्य
#घोषणा शून्य 0
#घोषणा NIL 0
#घोषणा SGL 0
#घोषणा DBL 1
#घोषणा BADFMT 2
#घोषणा QUAD 3


/* Types */
प्रकार पूर्णांक boolean;
प्रकार पूर्णांक FORMAT;
प्रकार पूर्णांक VOID;


/* Declare status रेजिस्टर equivalent to FPUs architecture.
 *
 *  0 1 2 3 4 5 6 7 8 910 1 2 3 4 5 6 7 8 920 1 2 3 4 5 6 7 8 930 1
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |V|Z|O|U|I|C|  rsv  |  model    | version |RM |rsv|T|r|V|Z|O|U|I|
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
#घोषणा Cbit(object) Bitfield_extract( 5, 1,object)
#घोषणा Tbit(object) Bitfield_extract( 25, 1,object)
#घोषणा Roundingmode(object) Bitfield_extract( 21, 2,object)
#घोषणा Invalidtrap(object) Bitfield_extract( 27, 1,object)
#घोषणा Divisionbyzerotrap(object) Bitfield_extract( 28, 1,object)
#घोषणा Overflowtrap(object) Bitfield_extract( 29, 1,object)
#घोषणा Underflowtrap(object) Bitfield_extract( 30, 1,object)
#घोषणा Inexacttrap(object) Bitfield_extract( 31, 1,object)
#घोषणा Invalidflag(object) Bitfield_extract( 0, 1,object)
#घोषणा Divisionbyzeroflag(object) Bitfield_extract( 1, 1,object)
#घोषणा Overflowflag(object) Bitfield_extract( 2, 1,object)
#घोषणा Underflowflag(object) Bitfield_extract( 3, 1,object)
#घोषणा Inexactflag(object) Bitfield_extract( 4, 1,object)
#घोषणा Allflags(object) Bitfield_extract( 0, 5,object)

/* Definitions relevant to the status रेजिस्टर */

/* Rounding Modes */
#घोषणा ROUNDNEAREST 0
#घोषणा ROUNDZERO    1
#घोषणा ROUNDPLUS    2
#घोषणा ROUNDMINUS   3

/* Exceptions */
#घोषणा NOEXCEPTION		0x0
#घोषणा INVALIDEXCEPTION	0x20
#घोषणा DIVISIONBYZEROEXCEPTION	0x10
#घोषणा OVERFLOWEXCEPTION	0x08
#घोषणा UNDERFLOWEXCEPTION	0x04
#घोषणा INEXACTEXCEPTION	0x02
#घोषणा UNIMPLEMENTEDEXCEPTION	0x01

/* New exceptions क्रम the 2E Opcode */
#घोषणा OPC_2E_INVALIDEXCEPTION     0x30
#घोषणा OPC_2E_OVERFLOWEXCEPTION    0x18
#घोषणा OPC_2E_UNDERFLOWEXCEPTION   0x0c
#घोषणा OPC_2E_INEXACTEXCEPTION     0x12

/* Declare exception रेजिस्टरs equivalent to FPUs architecture 
 *
 *  0 1 2 3 4 5 6 7 8 910 1 2 3 4 5 6 7 8 920 1 2 3 4 5 6 7 8 930 1
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |excepttype |  r1     | r2/ext  |  operation  |parm |n| t/cond  |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
#घोषणा Allexception(object) (object)
#घोषणा Exceptiontype(object) Bitfield_extract( 0, 6,object)
#घोषणा Inकाष्ठाionfield(object) Bitfield_mask( 6,26,object)
#घोषणा Parmfield(object) Bitfield_extract( 23, 3,object)
#घोषणा Rabit(object) Bitfield_extract( 24, 1,object)
#घोषणा Ibit(object) Bitfield_extract( 25, 1,object)

#घोषणा Set_exceptiontype(object,value) Bitfield_deposit(value, 0, 6,object)
#घोषणा Set_parmfield(object,value) Bitfield_deposit(value, 23, 3,object)
#घोषणा Set_exceptiontype_and_instr_field(exception,inकाष्ठाion,object) \
    object = exception << 26 | inकाष्ठाion

/* Declare the condition field
 *
 *  0 1 2 3 4 5 6 7 8 910 1 2 3 4 5 6 7 8 920 1 2 3 4 5 6 7 8 930 1
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                     |G|L|E|U|X|
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
#घोषणा Greaterthanbit(object) Bitfield_extract( 27, 1,object)
#घोषणा Lessthanbit(object) Bitfield_extract( 28, 1,object)
#घोषणा Equalbit(object) Bitfield_extract( 29, 1,object)
#घोषणा Unorderedbit(object) Bitfield_extract( 30, 1,object)
#घोषणा Exceptionbit(object) Bitfield_extract( 31, 1,object)

/* An alias name क्रम the status रेजिस्टर */
#घोषणा Fpustatus_रेजिस्टर (*status)

/**************************************************
 * Status रेजिस्टर referencing and manipulation.  *
 **************************************************/

/* Rounding mode */
#घोषणा Rounding_mode()  Roundingmode(Fpustatus_रेजिस्टर)
#घोषणा Is_rounding_mode(rmode) \
    (Roundingmode(Fpustatus_रेजिस्टर) == rmode)
#घोषणा Set_rounding_mode(value) \
    Bitfield_deposit(value,21,2,Fpustatus_रेजिस्टर)

/* Boolean testing of the trap enable bits */
#घोषणा Is_invalidtrap_enabled() Invalidtrap(Fpustatus_रेजिस्टर)
#घोषणा Is_भागisionbyzerotrap_enabled() Divisionbyzerotrap(Fpustatus_रेजिस्टर)
#घोषणा Is_overflowtrap_enabled() Overflowtrap(Fpustatus_रेजिस्टर)
#घोषणा Is_underflowtrap_enabled() Underflowtrap(Fpustatus_रेजिस्टर)
#घोषणा Is_inexacttrap_enabled() Inexacttrap(Fpustatus_रेजिस्टर)

/* Set the indicated flags in the status रेजिस्टर */
#घोषणा Set_invalidflag() Bitfield_deposit(1,0,1,Fpustatus_रेजिस्टर)
#घोषणा Set_भागisionbyzeroflag() Bitfield_deposit(1,1,1,Fpustatus_रेजिस्टर)
#घोषणा Set_overflowflag() Bitfield_deposit(1,2,1,Fpustatus_रेजिस्टर)
#घोषणा Set_underflowflag() Bitfield_deposit(1,3,1,Fpustatus_रेजिस्टर)
#घोषणा Set_inexactflag() Bitfield_deposit(1,4,1,Fpustatus_रेजिस्टर)

#घोषणा Clear_all_flags() Bitfield_deposit(0,0,5,Fpustatus_रेजिस्टर)

/* Manipulate the trap and condition code bits (tbit and cbit) */
#घोषणा Set_tbit() Bitfield_deposit(1,25,1,Fpustatus_रेजिस्टर)
#घोषणा Clear_tbit() Bitfield_deposit(0,25,1,Fpustatus_रेजिस्टर)
#घोषणा Is_tbit_set() Tbit(Fpustatus_रेजिस्टर)
#घोषणा Is_cbit_set() Cbit(Fpustatus_रेजिस्टर)

#घोषणा Set_status_cbit(value)  \
        Bitfield_deposit(value,5,1,Fpustatus_रेजिस्टर)

/*******************************
 * Condition field referencing *
 *******************************/
#घोषणा Unordered(cond) Unorderedbit(cond)
#घोषणा Equal(cond) Equalbit(cond)
#घोषणा Lessthan(cond) Lessthanbit(cond)
#घोषणा Greaterthan(cond) Greaterthanbit(cond)
#घोषणा Exception(cond) Exceptionbit(cond)


/* Defines क्रम the extension */
#घोषणा Ext_isone_sign(extent) (Extsign(extent))
#घोषणा Ext_isnotzero(extent) \
    (Extall(extent))
#घोषणा Ext_isnotzero_lower(extent) \
    (Extlow31(extent))
#घोषणा Ext_leftshअगरtby1(extent) \
    Extall(extent) <<= 1
#घोषणा Ext_negate(extent) \
    (पूर्णांक )Extall(extent) = 0 - (पूर्णांक )Extall(extent)
#घोषणा Ext_setone_low(extent) Bitfield_deposit(1,31,1,extent)
#घोषणा Ext_setzero(extent) Extall(extent) = 0

प्रकार पूर्णांक operation;

/* error messages */

#घोषणा		NONE		0
#घोषणा		UNDEFFPINST	1

/* Function definitions: opcode, opclass */
#घोषणा FTEST	(1<<2) | 0
#घोषणा FCPY	(2<<2) | 0
#घोषणा FABS	(3<<2) | 0
#घोषणा FSQRT   (4<<2) | 0
#घोषणा FRND    (5<<2) | 0

#घोषणा FCNVFF	(0<<2) | 1
#घोषणा FCNVXF	(1<<2) | 1
#घोषणा FCNVFX	(2<<2) | 1
#घोषणा FCNVFXT	(3<<2) | 1

#घोषणा FCMP    (0<<2) | 2

#घोषणा FADD	(0<<2) | 3
#घोषणा FSUB	(1<<2) | 3
#घोषणा FMPY	(2<<2) | 3
#घोषणा FDIV	(3<<2) | 3
#घोषणा FREM	(4<<2) | 3

