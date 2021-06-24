<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

#अगर_अघोषित _SKFP_H_SMTSTATE_H_
#घोषणा _SKFP_H_SMTSTATE_H_

/*
 *	SMT state definitions
 */

#अगर_अघोषित	KERNEL
/*
 * PCM states
 */
#घोषणा PC0_OFF			0
#घोषणा PC1_BREAK		1
#घोषणा PC2_TRACE		2
#घोषणा PC3_CONNECT		3
#घोषणा PC4_NEXT		4
#घोषणा PC5_SIGNAL		5
#घोषणा PC6_JOIN		6
#घोषणा PC7_VERIFY		7
#घोषणा PC8_ACTIVE		8
#घोषणा PC9_MAINT		9

/*
 * PCM modes
 */
#घोषणा PM_NONE			0
#घोषणा PM_PEER			1
#घोषणा PM_TREE			2

/*
 * PCM type
 */
#घोषणा TA			0
#घोषणा TB			1
#घोषणा TS			2
#घोषणा TM			3
#घोषणा TNONE			4

/*
 * CFM states
 */
#घोषणा SC0_ISOLATED	0		/* isolated */
#घोषणा SC1_WRAP_A	5		/* wrap A */
#घोषणा SC2_WRAP_B	6		/* wrap B */
#घोषणा SC4_THRU_A	12		/* through A */
#घोषणा SC5_THRU_B	7		/* through B (SMt 6.2) */
#घोषणा SC7_WRAP_S	8		/* SAS */

/*
 * ECM states
 */
#घोषणा EC0_OUT		0
#घोषणा EC1_IN		1
#घोषणा EC2_TRACE	2
#घोषणा EC3_LEAVE	3
#घोषणा EC4_PATH_TEST	4
#घोषणा EC5_INSERT	5
#घोषणा EC6_CHECK	6
#घोषणा EC7_DEINSERT	7

/*
 * RMT states
 */
#घोषणा RM0_ISOLATED	0
#घोषणा RM1_NON_OP	1		/* not operational */
#घोषणा RM2_RING_OP	2		/* ring operational */
#घोषणा RM3_DETECT	3		/* detect dupl addresses */
#घोषणा RM4_NON_OP_DUP	4		/* dupl. addr detected */
#घोषणा RM5_RING_OP_DUP	5		/* ring oper. with dupl. addr */
#घोषणा RM6_सूचीECTED	6		/* sending directed beacons */
#घोषणा RM7_TRACE	7		/* trace initiated */
#पूर्ण_अगर

काष्ठा pcm_state अणु
	अचिन्हित अक्षर	pcm_type ;		/* TA TB TS TM */
	अचिन्हित अक्षर	pcm_state ;		/* state PC[0-9]_* */
	अचिन्हित अक्षर	pcm_mode ;		/* PM_अणुNONE,PEER,TREEपूर्ण */
	अचिन्हित अक्षर	pcm_neighbor ;		/* TA TB TS TM */
	अचिन्हित अक्षर	pcm_bsf ;		/* flag bs : TRUE/FALSE */
	अचिन्हित अक्षर	pcm_lsf ;		/* flag ls : TRUE/FALSE */
	अचिन्हित अक्षर	pcm_lct_fail ;		/* counter lct_fail */
	अचिन्हित अक्षर	pcm_ls_rx ;		/* rx line state */
	लघु		pcm_r_val ;		/* संकेतing bits */
	लघु		pcm_t_val ;		/* संकेतing bits */
पूर्ण ;

काष्ठा smt_state अणु
	काष्ठा pcm_state pcm_state[NUMPHYS] ;	/* port A & port B */
पूर्ण ;

#पूर्ण_अगर

