<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	mcfslt.h -- ColdFire पूर्णांकernal Slice (SLT) समयr support defines.
 *
 *	(C) Copyright 2004, Greg Ungerer (gerg@snapgear.com)
 *	(C) Copyright 2009, Philippe De Muyter (phdm@macqel.be)
 */

/****************************************************************************/
#अगर_अघोषित mcfslt_h
#घोषणा mcfslt_h
/****************************************************************************/

/*
 *	Define the SLT समयr रेजिस्टर set addresses.
 */
#घोषणा MCFSLT_STCNT		0x00	/* Terminal count */
#घोषणा MCFSLT_SCR		0x04	/* Control */
#घोषणा MCFSLT_SCNT		0x08	/* Current count */
#घोषणा MCFSLT_SSR		0x0C	/* Status */

/*
 *	Bit definitions क्रम the SCR control रेजिस्टर.
 */
#घोषणा MCFSLT_SCR_RUN		0x04000000	/* Run mode (continuous) */
#घोषणा MCFSLT_SCR_IEN		0x02000000	/* Interrupt enable */
#घोषणा MCFSLT_SCR_TEN		0x01000000	/* Timer enable */

/*
 *	Bit definitions क्रम the SSR status रेजिस्टर.
 */
#घोषणा MCFSLT_SSR_BE		0x02000000	/* Bus error condition */
#घोषणा MCFSLT_SSR_TE		0x01000000	/* Timeout condition */

/****************************************************************************/
#पूर्ण_अगर	/* mcfslt_h */
