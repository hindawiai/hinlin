<शैली गुरु>
/*======================================================================

    Device driver क्रम the PCMCIA control functionality of StrongARM
    SA-1100 microprocessors.

    The contents of this file are subject to the Mozilla Public
    License Version 1.1 (the "License"); you may not use this file
    except in compliance with the License. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS
    IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    implied. See the License क्रम the specअगरic language governing
    rights and limitations under the License.

    The initial developer of the original code is John G. Dorsey
    <john+@cs.cmu.edu>.  Portions created by John G. Dorsey are
    Copyright (C) 1999 John G. Dorsey.  All Rights Reserved.

    Alternatively, the contents of this file may be used under the
    terms of the GNU Public License version 2 (the "GPL"), in which
    हाल the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you करो not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.

======================================================================*/

#अगर !defined(_PCMCIA_SA1100_H)
# define _PCMCIA_SA1100_H

/* SA-1100 PCMCIA Memory and I/O timing
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * The SA-1110 Developer's Manual, section 10.2.5, says the following:
 *
 *  "To calculate the recommended BS_xx value क्रम each address space:
 *   भागide the command width समय (the greater of twIOWR and twIORD,
 *   or the greater of twWE and twOE) by processor cycle समय; भागide
 *   by 2; भागide again by 3 (number of BCLK's per command निश्चितion);
 *   round up to the next whole number; and subtract 1."
 */

/* MECR: Expansion Memory Configuration Register
 * (SA-1100 Developers Manual, p.10-13; SA-1110 Developers Manual, p.10-24)
 *
 * MECR layout is:
 *
 *   FAST1 BSM1<4:0> BSA1<4:0> BSIO1<4:0> FAST0 BSM0<4:0> BSA0<4:0> BSIO0<4:0>
 *
 * (This layout is actually true only क्रम the SA-1110; the FASTn bits are
 * reserved on the SA-1100.)
 */

#घोषणा MECR_SOCKET_0_SHIFT (0)
#घोषणा MECR_SOCKET_1_SHIFT (16)

#घोषणा MECR_BS_MASK        (0x1f)
#घोषणा MECR_FAST_MODE_MASK (0x01)

#घोषणा MECR_BSIO_SHIFT (0)
#घोषणा MECR_BSA_SHIFT  (5)
#घोषणा MECR_BSM_SHIFT  (10)
#घोषणा MECR_FAST_SHIFT (15)

#घोषणा MECR_SET(mecr, sock, shअगरt, mask, bs) \
((mecr)=((mecr)&~(((mask)<<(shअगरt))<<\
                  ((sock)==0?MECR_SOCKET_0_SHIFT:MECR_SOCKET_1_SHIFT)))|\
        (((bs)<<(shअगरt))<<((sock)==0?MECR_SOCKET_0_SHIFT:MECR_SOCKET_1_SHIFT)))

#घोषणा MECR_GET(mecr, sock, shअगरt, mask) \
((((mecr)>>(((sock)==0)?MECR_SOCKET_0_SHIFT:MECR_SOCKET_1_SHIFT))>>\
 (shअगरt))&(mask))

#घोषणा MECR_BSIO_SET(mecr, sock, bs) \
MECR_SET((mecr), (sock), MECR_BSIO_SHIFT, MECR_BS_MASK, (bs))

#घोषणा MECR_BSIO_GET(mecr, sock) \
MECR_GET((mecr), (sock), MECR_BSIO_SHIFT, MECR_BS_MASK)

#घोषणा MECR_BSA_SET(mecr, sock, bs) \
MECR_SET((mecr), (sock), MECR_BSA_SHIFT, MECR_BS_MASK, (bs))

#घोषणा MECR_BSA_GET(mecr, sock) \
MECR_GET((mecr), (sock), MECR_BSA_SHIFT, MECR_BS_MASK)

#घोषणा MECR_BSM_SET(mecr, sock, bs) \
MECR_SET((mecr), (sock), MECR_BSM_SHIFT, MECR_BS_MASK, (bs))

#घोषणा MECR_BSM_GET(mecr, sock) \
MECR_GET((mecr), (sock), MECR_BSM_SHIFT, MECR_BS_MASK)

#घोषणा MECR_FAST_SET(mecr, sock, fast) \
MECR_SET((mecr), (sock), MECR_FAST_SHIFT, MECR_FAST_MODE_MASK, (fast))

#घोषणा MECR_FAST_GET(mecr, sock) \
MECR_GET((mecr), (sock), MECR_FAST_SHIFT, MECR_FAST_MODE_MASK)


/* This function implements the BS value calculation क्रम setting the MECR
 * using पूर्णांकeger arithmetic:
 */
अटल अंतरभूत अचिन्हित पूर्णांक sa1100_pcmcia_mecr_bs(अचिन्हित पूर्णांक pcmcia_cycle_ns,
						 अचिन्हित पूर्णांक cpu_घड़ी_khz)अणु
  अचिन्हित पूर्णांक t = ((pcmcia_cycle_ns * cpu_घड़ी_khz) / 6) - 1000000;
  वापस (t / 1000000) + (((t % 1000000) == 0) ? 0 : 1);
पूर्ण

/* This function वापसs the (approximate) command निश्चितion period, in
 * nanoseconds, क्रम a given CPU घड़ी frequency and MECR BS value:
 */
अटल अंतरभूत अचिन्हित पूर्णांक sa1100_pcmcia_cmd_समय(अचिन्हित पूर्णांक cpu_घड़ी_khz,
						  अचिन्हित पूर्णांक pcmcia_mecr_bs)अणु
  वापस (((10000000 * 2) / cpu_घड़ी_khz) * (3 * (pcmcia_mecr_bs + 1))) / 10;
पूर्ण


पूर्णांक sa11xx_drv_pcmcia_add_one(काष्ठा soc_pcmcia_socket *skt);
व्योम sa11xx_drv_pcmcia_ops(काष्ठा pcmcia_low_level *ops);
बाह्य पूर्णांक sa11xx_drv_pcmcia_probe(काष्ठा device *dev, काष्ठा pcmcia_low_level *ops, पूर्णांक first, पूर्णांक nr);

#पूर्ण_अगर  /* !defined(_PCMCIA_SA1100_H) */
