<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic Reed Solomon encoder / decoder library
 *
 * Copyright (C) 2004 Thomas Gleixner (tglx@linutronix.de)
 *
 * RS code lअगरted from reed solomon library written by Phil Karn
 * Copyright 2002 Phil Karn, KA9Q
 */
#अगर_अघोषित _RSLIB_H_
#घोषणा _RSLIB_H_

#समावेश <linux/list.h>
#समावेश <linux/types.h>	/* क्रम gfp_t */
#समावेश <linux/gfp.h>		/* क्रम GFP_KERNEL */

/**
 * काष्ठा rs_codec - rs codec data
 *
 * @mm:		Bits per symbol
 * @nn:		Symbols per block (= (1<<mm)-1)
 * @alpha_to:	log lookup table
 * @index_of:	Antilog lookup table
 * @genpoly:	Generator polynomial
 * @nroots:	Number of generator roots = number of parity symbols
 * @fcr:	First consecutive root, index क्रमm
 * @prim:	Primitive element, index क्रमm
 * @iprim:	prim-th root of 1, index क्रमm
 * @gfpoly:	The primitive generator polynominal
 * @gffunc:	Function to generate the field, अगर non-canonical representation
 * @users:	Users of this काष्ठाure
 * @list:	List entry क्रम the rs codec list
*/
काष्ठा rs_codec अणु
	पूर्णांक		mm;
	पूर्णांक		nn;
	uपूर्णांक16_t	*alpha_to;
	uपूर्णांक16_t	*index_of;
	uपूर्णांक16_t	*genpoly;
	पूर्णांक		nroots;
	पूर्णांक		fcr;
	पूर्णांक		prim;
	पूर्णांक		iprim;
	पूर्णांक		gfpoly;
	पूर्णांक		(*gffunc)(पूर्णांक);
	पूर्णांक		users;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा rs_control - rs control काष्ठाure per instance
 * @codec:	The codec used क्रम this instance
 * @buffers:	Internal scratch buffers used in calls to decode_rs()
 */
काष्ठा rs_control अणु
	काष्ठा rs_codec	*codec;
	uपूर्णांक16_t	buffers[];
पूर्ण;

/* General purpose RS codec, 8-bit data width, symbol width 1-15 bit  */
#अगर_घोषित CONFIG_REED_SOLOMON_ENC8
पूर्णांक encode_rs8(काष्ठा rs_control *rs, uपूर्णांक8_t *data, पूर्णांक len, uपूर्णांक16_t *par,
	       uपूर्णांक16_t invmsk);
#पूर्ण_अगर
#अगर_घोषित CONFIG_REED_SOLOMON_DEC8
पूर्णांक decode_rs8(काष्ठा rs_control *rs, uपूर्णांक8_t *data, uपूर्णांक16_t *par, पूर्णांक len,
		uपूर्णांक16_t *s, पूर्णांक no_eras, पूर्णांक *eras_pos, uपूर्णांक16_t invmsk,
	       uपूर्णांक16_t *corr);
#पूर्ण_अगर

/* General purpose RS codec, 16-bit data width, symbol width 1-15 bit  */
#अगर_घोषित CONFIG_REED_SOLOMON_ENC16
पूर्णांक encode_rs16(काष्ठा rs_control *rs, uपूर्णांक16_t *data, पूर्णांक len, uपूर्णांक16_t *par,
		uपूर्णांक16_t invmsk);
#पूर्ण_अगर
#अगर_घोषित CONFIG_REED_SOLOMON_DEC16
पूर्णांक decode_rs16(काष्ठा rs_control *rs, uपूर्णांक16_t *data, uपूर्णांक16_t *par, पूर्णांक len,
		uपूर्णांक16_t *s, पूर्णांक no_eras, पूर्णांक *eras_pos, uपूर्णांक16_t invmsk,
		uपूर्णांक16_t *corr);
#पूर्ण_अगर

काष्ठा rs_control *init_rs_gfp(पूर्णांक symsize, पूर्णांक gfpoly, पूर्णांक fcr, पूर्णांक prim,
			       पूर्णांक nroots, gfp_t gfp);

/**
 * init_rs - Create a RS control काष्ठा and initialize it
 *  @symsize:	the symbol size (number of bits)
 *  @gfpoly:	the extended Galois field generator polynomial coefficients,
 *		with the 0th coefficient in the low order bit. The polynomial
 *		must be primitive;
 *  @fcr:	the first consecutive root of the rs code generator polynomial
 *		in index क्रमm
 *  @prim:	primitive element to generate polynomial roots
 *  @nroots:	RS code generator polynomial degree (number of roots)
 *
 * Allocations use GFP_KERNEL.
 */
अटल अंतरभूत काष्ठा rs_control *init_rs(पूर्णांक symsize, पूर्णांक gfpoly, पूर्णांक fcr,
					 पूर्णांक prim, पूर्णांक nroots)
अणु
	वापस init_rs_gfp(symsize, gfpoly, fcr, prim, nroots, GFP_KERNEL);
पूर्ण

काष्ठा rs_control *init_rs_non_canonical(पूर्णांक symsize, पूर्णांक (*func)(पूर्णांक),
					 पूर्णांक fcr, पूर्णांक prim, पूर्णांक nroots);

/* Release a rs control काष्ठाure */
व्योम मुक्त_rs(काष्ठा rs_control *rs);

/** modulo replacement क्रम galois field arithmetics
 *
 *  @rs:	Poपूर्णांकer to the RS codec
 *  @x:		the value to reduce
 *
 *  where
 *  rs->mm = number of bits per symbol
 *  rs->nn = (2^rs->mm) - 1
 *
 *  Simple arithmetic modulo would वापस a wrong result क्रम values
 *  >= 3 * rs->nn
*/
अटल अंतरभूत पूर्णांक rs_modnn(काष्ठा rs_codec *rs, पूर्णांक x)
अणु
	जबतक (x >= rs->nn) अणु
		x -= rs->nn;
		x = (x >> rs->mm) + (x & rs->nn);
	पूर्ण
	वापस x;
पूर्ण

#पूर्ण_अगर
