<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  *********************************************************************
    *  SB1250 Board Support Package
    *
    *  Global स्थिरants and macros		File: sb1250_defs.h
    *
    *  This file contains macros and definitions used by the other
    *  include files.
    *
    *  SB1250 specअगरication level:  User's manual 1/02/02
    *
    *********************************************************************
    *
    *  Copyright 2000,2001,2002,2003
    *  Broadcom Corporation. All rights reserved.
    *
    ********************************************************************* */

#अगर_अघोषित _SB1250_DEFS_H
#घोषणा _SB1250_DEFS_H

/*
 * These headers require ANSI C89 string concatenation, and GCC or other
 * 'long long' (64-bit पूर्णांकeger) support.
 */
#अगर !defined(__STDC__) && !defined(_MSC_VER)
#त्रुटि SiByte headers require ANSI C89 support
#पूर्ण_अगर


/*  *********************************************************************
    *  Macros क्रम feature tests, used to enable include file features
    *  क्रम chip features only present in certain chip revisions.
    *
    *  SIBYTE_HDR_FEATURES may be defined to be the mask value chip/revision
    *  which is to be exposed by the headers.  If undefined, it शेषs to
    *  "all features."
    *
    *  Use like:
    *
    *	 #घोषणा SIBYTE_HDR_FEATURES	SIBYTE_HDR_FMASK_112x_PASS1
    *
    *		Generate defines only क्रम that revision of chip.
    *
    *	 #अगर SIBYTE_HDR_FEATURE(chip,pass)
    *
    *		True अगर header features क्रम that revision or later of
    *		that particular chip type are enabled in SIBYTE_HDR_FEATURES.
    *		(Use this to bracket #घोषणाs क्रम features present in a given
    *		revision and later.)
    *
    *		Note that there is no implied ordering between chip types.
    *
    *		Note also that 'chip' and 'pass' must textually exactly
    *		match the defines below.  So, क्रम example,
    *		SIBYTE_HDR_FEATURE(112x, PASS1) is OK, but
    *		SIBYTE_HDR_FEATURE(1120, pass1) is not (क्रम two reasons).
    *
    *	 #अगर SIBYTE_HDR_FEATURE_UP_TO(chip,pass)
    *
    *		Same as SIBYTE_HDR_FEATURE, but true क्रम the named revision
    *		and earlier revisions of the named chip type.
    *
    *	 #अगर SIBYTE_HDR_FEATURE_EXACT(chip,pass)
    *
    *		Same as SIBYTE_HDR_FEATURE, but only true क्रम the named
    *		revision of the named chip type.  (Note that this CANNOT
    *		be used to verअगरy that you're compiling only क्रम that
    *		particular chip/revision.  It will be true any समय this
    *		chip/revision is included in SIBYTE_HDR_FEATURES.)
    *
    *	 #अगर SIBYTE_HDR_FEATURE_CHIP(chip)
    *
    *		True अगर header features क्रम (any revision of) that chip type
    *		are enabled in SIBYTE_HDR_FEATURES.  (Use this to bracket
    *		#घोषणाs क्रम features specअगरic to a given chip type.)
    *
    *  Mask values currently include room क्रम additional revisions of each
    *  chip type, but can be rक्रमागतbered at will.  Note that they MUST fit
    *  पूर्णांकo 31 bits and may not include C type स्थिरructs, क्रम safe use in
    *  CPP conditionals.  Bit positions within chip types DO indicate
    *  ordering, so be careful when adding support क्रम new minor revs.
    ********************************************************************* */

#घोषणा SIBYTE_HDR_FMASK_1250_ALL		0x000000ff
#घोषणा SIBYTE_HDR_FMASK_1250_PASS1		0x00000001
#घोषणा SIBYTE_HDR_FMASK_1250_PASS2		0x00000002
#घोषणा SIBYTE_HDR_FMASK_1250_PASS3		0x00000004

#घोषणा SIBYTE_HDR_FMASK_112x_ALL		0x00000f00
#घोषणा SIBYTE_HDR_FMASK_112x_PASS1		0x00000100

#घोषणा SIBYTE_HDR_FMASK_1480_ALL		0x0000f000
#घोषणा SIBYTE_HDR_FMASK_1480_PASS1		0x00001000
#घोषणा SIBYTE_HDR_FMASK_1480_PASS2		0x00002000

/* Bit mask क्रम chip/revision.	(use _ALL क्रम all revisions of a chip).	 */
#घोषणा SIBYTE_HDR_FMASK(chip, pass)					\
    (SIBYTE_HDR_FMASK_ ## chip ## _ ## pass)
#घोषणा SIBYTE_HDR_FMASK_ALLREVS(chip)					\
    (SIBYTE_HDR_FMASK_ ## chip ## _ALL)

/* Default स्थिरant value क्रम all chips, all revisions */
#घोषणा SIBYTE_HDR_FMASK_ALL						\
    (SIBYTE_HDR_FMASK_1250_ALL | SIBYTE_HDR_FMASK_112x_ALL		\
     | SIBYTE_HDR_FMASK_1480_ALL)

/* This one is used क्रम the "original" BCM1250/BCM112x chips.  We use this
   to weed out स्थिरants and macros that करो not exist on later chips like
   the BCM1480	*/
#घोषणा SIBYTE_HDR_FMASK_1250_112x_ALL					\
    (SIBYTE_HDR_FMASK_1250_ALL | SIBYTE_HDR_FMASK_112x_ALL)
#घोषणा SIBYTE_HDR_FMASK_1250_112x SIBYTE_HDR_FMASK_1250_112x_ALL

#अगर_अघोषित SIBYTE_HDR_FEATURES
#घोषणा SIBYTE_HDR_FEATURES			SIBYTE_HDR_FMASK_ALL
#पूर्ण_अगर


/* Bit mask क्रम revisions of chip exclusively beक्रमe the named revision.  */
#घोषणा SIBYTE_HDR_FMASK_BEFORE(chip, pass)				\
    ((SIBYTE_HDR_FMASK(chip, pass) - 1) & SIBYTE_HDR_FMASK_ALLREVS(chip))

/* Bit mask क्रम revisions of chip exclusively after the named revision.	 */
#घोषणा SIBYTE_HDR_FMASK_AFTER(chip, pass)				\
    (~(SIBYTE_HDR_FMASK(chip, pass)					\
     | (SIBYTE_HDR_FMASK(chip, pass) - 1)) & SIBYTE_HDR_FMASK_ALLREVS(chip))


/* True अगर header features enabled क्रम (any revision of) that chip type.  */
#घोषणा SIBYTE_HDR_FEATURE_CHIP(chip)					\
    (!! (SIBYTE_HDR_FMASK_ALLREVS(chip) & SIBYTE_HDR_FEATURES))

/* True क्रम all versions of the BCM1250 and BCM1125, but not true क्रम
   anything अन्यथा */
#घोषणा SIBYTE_HDR_FEATURE_1250_112x \
      (SIBYTE_HDR_FEATURE_CHIP(1250) || SIBYTE_HDR_FEATURE_CHIP(112x))
/*    (!!  (SIBYTE_HDR_FEATURES & SIBYHTE_HDR_FMASK_1250_112x)) */

/* True अगर header features enabled क्रम that rev or later, inclusive.  */
#घोषणा SIBYTE_HDR_FEATURE(chip, pass)					\
    (!! ((SIBYTE_HDR_FMASK(chip, pass)					\
	  | SIBYTE_HDR_FMASK_AFTER(chip, pass)) & SIBYTE_HDR_FEATURES))

/* True अगर header features enabled क्रम exactly that rev.  */
#घोषणा SIBYTE_HDR_FEATURE_EXACT(chip, pass)				\
    (!! (SIBYTE_HDR_FMASK(chip, pass) & SIBYTE_HDR_FEATURES))

/* True अगर header features enabled क्रम that rev or beक्रमe, inclusive.  */
#घोषणा SIBYTE_HDR_FEATURE_UP_TO(chip, pass)				\
    (!! ((SIBYTE_HDR_FMASK(chip, pass)					\
	 | SIBYTE_HDR_FMASK_BEFORE(chip, pass)) & SIBYTE_HDR_FEATURES))


/*  *********************************************************************
    *  Naming schemes क्रम स्थिरants in these files:
    *
    *  M_xxx	       MASK स्थिरant (identअगरies bits in a रेजिस्टर).
    *		       For multi-bit fields, all bits in the field will
    *		       be set.
    *
    *  K_xxx	       "Code" स्थिरant (value क्रम data in a multi-bit
    *		       field).	The value is right justअगरied.
    *
    *  V_xxx	       "Value" स्थिरant.  This is the same as the
    *		       corresponding "K_xxx" स्थिरant, except it is
    *		       shअगरted to the correct position in the रेजिस्टर.
    *
    *  S_xxx	       SHIFT स्थिरant.	This is the number of bits that
    *		       a field value (code) needs to be shअगरted
    *		       (towards the left) to put the value in the right
    *		       position क्रम the रेजिस्टर.
    *
    *  A_xxx	       ADDRESS स्थिरant.  This will be a physical
    *		       address.	 Use the PHYS_TO_K1 macro to generate
    *		       a K1SEG address.
    *
    *  R_xxx	       RELATIVE offset स्थिरant.  This is an offset from
    *		       an A_xxx स्थिरant (usually the first रेजिस्टर in
    *		       a group).
    *
    *  G_xxx(X)	       GET value.  This macro obtains a multi-bit field
    *		       from a रेजिस्टर, masks it, and shअगरts it to
    *		       the bottom of the रेजिस्टर (retrieving a K_xxx
    *		       value, क्रम example).
    *
    *  V_xxx(X)	       VALUE.  This macro computes the value of a
    *		       K_xxx स्थिरant shअगरted to the correct position
    *		       in the रेजिस्टर.
    ********************************************************************* */




/*
 * Cast to 64-bit number.  Presumably the syntax is dअगरferent in
 * assembly language.
 *
 * Note: you'll need to define uपूर्णांक32_t and uपूर्णांक64_t in your headers.
 */

#अगर !defined(__ASSEMBLY__)
#घोषणा _SB_MAKE64(x) ((uपूर्णांक64_t)(x))
#घोषणा _SB_MAKE32(x) ((uपूर्णांक32_t)(x))
#अन्यथा
#घोषणा _SB_MAKE64(x) (x)
#घोषणा _SB_MAKE32(x) (x)
#पूर्ण_अगर


/*
 * Make a mask क्रम 1 bit at position 'n'
 */

#घोषणा _SB_MAKEMASK1(n) (_SB_MAKE64(1) << _SB_MAKE64(n))
#घोषणा _SB_MAKEMASK1_32(n) (_SB_MAKE32(1) << _SB_MAKE32(n))

/*
 * Make a mask क्रम 'v' bits at position 'n'
 */

#घोषणा _SB_MAKEMASK(v, n) (_SB_MAKE64((_SB_MAKE64(1)<<(v))-1) << _SB_MAKE64(n))
#घोषणा _SB_MAKEMASK_32(v, n) (_SB_MAKE32((_SB_MAKE32(1)<<(v))-1) << _SB_MAKE32(n))

/*
 * Make a value at 'v' at bit position 'n'
 */

#घोषणा _SB_MAKEVALUE(v, n) (_SB_MAKE64(v) << _SB_MAKE64(n))
#घोषणा _SB_MAKEVALUE_32(v, n) (_SB_MAKE32(v) << _SB_MAKE32(n))

#घोषणा _SB_GETVALUE(v, n, m) ((_SB_MAKE64(v) & _SB_MAKE64(m)) >> _SB_MAKE64(n))
#घोषणा _SB_GETVALUE_32(v, n, m) ((_SB_MAKE32(v) & _SB_MAKE32(m)) >> _SB_MAKE32(n))

/*
 * Macros to पढ़ो/ग_लिखो on-chip रेजिस्टरs
 * XXX should we करो the PHYS_TO_K1 here?
 */


#अगर defined(__mips64) && !defined(__ASSEMBLY__)
#घोषणा SBWRITECSR(csr, val) *((अस्थिर uपूर्णांक64_t *) PHYS_TO_K1(csr)) = (val)
#घोषणा SBREADCSR(csr) (*((अस्थिर uपूर्णांक64_t *) PHYS_TO_K1(csr)))
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
