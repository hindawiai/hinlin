<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	See the file "skfddi.c" क्रम further inक्रमmation.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

/*
	Init SMT
	call all module level initialization routines
*/

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"

व्योम init_fddi_driver(काष्ठा s_smc *smc, u_अक्षर *mac_addr);

/* define global debug variable */
#अगर defined(DEBUG) && !defined(DEBUG_BRD)
काष्ठा smt_debug debug;
#पूर्ण_अगर

#अगर_अघोषित MULT_OEM
#घोषणा OEMID(smc,i)	oem_id[i]
	बाह्य u_अक्षर	oem_id[] ;
#अन्यथा	/* MULT_OEM */
#घोषणा OEMID(smc,i)	smc->hw.oem_id->oi_mark[i]
	बाह्य काष्ठा s_oem_ids	oem_ids[] ;
#पूर्ण_अगर	/* MULT_OEM */

/*
 * Set OEM specअगरic values
 *
 * Can not be called in smt_reset_शेषs, because it is not sure that
 * the OEM ID is alपढ़ोy defined.
 */
अटल व्योम set_oem_spec_val(काष्ठा s_smc *smc)
अणु
	काष्ठा fddi_mib *mib ;

	mib = &smc->mib ;

	/*
	 * set IBM specअगरic values
	 */
	अगर (OEMID(smc,0) == 'I') अणु
		mib->fddiSMTConnectionPolicy = POLICY_MM ;
	पूर्ण
पूर्ण

/*
 * Init SMT
 */
पूर्णांक init_smt(काष्ठा s_smc *smc, u_अक्षर *mac_addr)
/* u_अक्षर *mac_addr;	canonical address or शून्य */
अणु
	पूर्णांक	p ;

#अगर defined(DEBUG) && !defined(DEBUG_BRD)
	debug.d_smt = 0 ;
	debug.d_smtf = 0 ;
	debug.d_rmt = 0 ;
	debug.d_ecm = 0 ;
	debug.d_pcm = 0 ;
	debug.d_cfm = 0 ;

	debug.d_plc = 0 ;
#अगर_घोषित	ESS
	debug.d_ess = 0 ;
#पूर्ण_अगर
#अगर_घोषित	SBA
	debug.d_sba = 0 ;
#पूर्ण_अगर
#पूर्ण_अगर	/* DEBUG && !DEBUG_BRD */

	/* First initialize the ports mib->poपूर्णांकers */
	क्रम ( p = 0; p < NUMPHYS; p ++ ) अणु
		smc->y[p].mib = & smc->mib.p[p] ;
	पूर्ण

	set_oem_spec_val(smc) ;	
	(व्योम) smt_set_mac_opvalues(smc) ;
	init_fddi_driver(smc,mac_addr) ;	/* HW driver */
	smt_fixup_mib(smc) ;		/* update values that depend on s.sas */

	ev_init(smc) ;			/* event queue */
#अगर_अघोषित	SLIM_SMT
	smt_init_evc(smc) ;		/* evcs in MIB */
#पूर्ण_अगर	/* no SLIM_SMT */
	smt_समयr_init(smc) ;		/* समयr package */
	smt_agent_init(smc) ;		/* SMT frame manager */

	pcm_init(smc) ;			/* PCM state machine */
	ecm_init(smc) ;			/* ECM state machine */
	cfm_init(smc) ;			/* CFM state machine */
	rmt_init(smc) ;			/* RMT state machine */

	क्रम (p = 0 ; p < NUMPHYS ; p++) अणु
		pcm(smc,p,0) ;		/* PCM A state machine */
	पूर्ण
	ecm(smc,0) ;			/* ECM state machine */
	cfm(smc,0) ;			/* CFM state machine */
	rmt(smc,0) ;			/* RMT state machine */

	smt_agent_task(smc) ;		/* NIF FSM etc */

        PNMI_INIT(smc) ;                /* PNMI initialization */

	वापस 0;
पूर्ण

