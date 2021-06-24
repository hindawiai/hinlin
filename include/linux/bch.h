<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Generic binary BCH encoding/decoding library
 *
 * Copyright तऊ 2011 Parrot S.A.
 *
 * Author: Ivan Djelic <ivan.djelic@parrot.com>
 *
 * Description:
 *
 * This library provides runसमय configurable encoding/decoding of binary
 * Bose-Chaudhuri-Hocquenghem (BCH) codes.
*/
#अगर_अघोषित _BCH_H
#घोषणा _BCH_H

#समावेश <linux/types.h>

/**
 * काष्ठा bch_control - BCH control काष्ठाure
 * @m:          Galois field order
 * @n:          maximum codeword size in bits (= 2^m-1)
 * @t:          error correction capability in bits
 * @ecc_bits:   ecc exact size in bits, i.e. generator polynomial degree (<=m*t)
 * @ecc_bytes:  ecc max size (m*t bits) in bytes
 * @a_घात_tab:  Galois field GF(2^m) exponentiation lookup table
 * @a_log_tab:  Galois field GF(2^m) log lookup table
 * @mod8_tab:   reमुख्यder generator polynomial lookup tables
 * @ecc_buf:    ecc parity words buffer
 * @ecc_buf2:   ecc parity words buffer
 * @xi_tab:     GF(2^m) base क्रम solving degree 2 polynomial roots
 * @syn:        syndrome buffer
 * @cache:      log-based polynomial representation buffer
 * @elp:        error locator polynomial
 * @poly_2t:    temporary polynomials of degree 2t
 * @swap_bits:  swap bits within data and syndrome bytes
 */
काष्ठा bch_control अणु
	अचिन्हित पूर्णांक    m;
	अचिन्हित पूर्णांक    n;
	अचिन्हित पूर्णांक    t;
	अचिन्हित पूर्णांक    ecc_bits;
	अचिन्हित पूर्णांक    ecc_bytes;
/* निजी: */
	uपूर्णांक16_t       *a_घात_tab;
	uपूर्णांक16_t       *a_log_tab;
	uपूर्णांक32_t       *mod8_tab;
	uपूर्णांक32_t       *ecc_buf;
	uपूर्णांक32_t       *ecc_buf2;
	अचिन्हित पूर्णांक   *xi_tab;
	अचिन्हित पूर्णांक   *syn;
	पूर्णांक            *cache;
	काष्ठा gf_poly *elp;
	काष्ठा gf_poly *poly_2t[4];
	bool		swap_bits;
पूर्ण;

काष्ठा bch_control *bch_init(पूर्णांक m, पूर्णांक t, अचिन्हित पूर्णांक prim_poly,
			     bool swap_bits);

व्योम bch_मुक्त(काष्ठा bch_control *bch);

व्योम bch_encode(काष्ठा bch_control *bch, स्थिर uपूर्णांक8_t *data,
		अचिन्हित पूर्णांक len, uपूर्णांक8_t *ecc);

पूर्णांक bch_decode(काष्ठा bch_control *bch, स्थिर uपूर्णांक8_t *data, अचिन्हित पूर्णांक len,
	       स्थिर uपूर्णांक8_t *recv_ecc, स्थिर uपूर्णांक8_t *calc_ecc,
	       स्थिर अचिन्हित पूर्णांक *syn, अचिन्हित पूर्णांक *errloc);

#पूर्ण_अगर /* _BCH_H */
