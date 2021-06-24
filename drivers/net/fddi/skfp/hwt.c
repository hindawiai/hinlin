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
 * Timer Driver क्रम FBI board (समयr chip 82C54)
 */

/*
 * Modअगरications:
 *
 *	28-Jun-1994 sw	Edit v1.6.
 *			MCA: Added support क्रम the SK-NET FDDI-FM2 adapter. The
 *			 following functions have been added(+) or modअगरied(*):
 *			 hwt_start(*), hwt_stop(*), hwt_restart(*), hwt_पढ़ो(*)
 */

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"

/*
 * Prototypes of local functions.
 */
/* 28-Jun-1994 sw - Note: hwt_restart() is also used in module 'drvfbi.c'. */
/*अटल व्योम hwt_restart() ; */

/************************
 *
 *	hwt_start
 *
 *	Start hardware समयr (घड़ी ticks are 16us).
 *
 *	व्योम hwt_start(
 *		काष्ठा s_smc *smc,
 *		u_दीर्घ समय) ;
 * In
 *	smc - A poपूर्णांकer to the SMT Context काष्ठाure.
 *
 *	समय - The समय in units of 16us to load the समयr with.
 * Out
 *	Nothing.
 *
 ************************/
#घोषणा	HWT_MAX	(65000)

व्योम hwt_start(काष्ठा s_smc *smc, u_दीर्घ समय)
अणु
	u_लघु	cnt ;

	अगर (समय > HWT_MAX)
		समय = HWT_MAX ;

	smc->hw.t_start = समय ;
	smc->hw.t_stop = 0L ;

	cnt = (u_लघु)समय ;
	/*
	 * अगर समय < 16 us
	 *	समय = 16 us
	 */
	अगर (!cnt)
		cnt++ ;

	outpd(ADDR(B2_TI_INI), (u_दीर्घ) cnt * 200) ;	/* Load समयr value. */
	outpw(ADDR(B2_TI_CRTL), TIM_START) ;		/* Start समयr. */

	smc->hw.समयr_activ = TRUE ;
पूर्ण

/************************
 *
 *	hwt_stop
 *
 *	Stop hardware समयr.
 *
 *	व्योम hwt_stop(
 *		काष्ठा s_smc *smc) ;
 * In
 *	smc - A poपूर्णांकer to the SMT Context काष्ठाure.
 * Out
 *	Nothing.
 *
 ************************/
व्योम hwt_stop(काष्ठा s_smc *smc)
अणु
	outpw(ADDR(B2_TI_CRTL), TIM_STOP) ;
	outpw(ADDR(B2_TI_CRTL), TIM_CL_IRQ) ;

	smc->hw.समयr_activ = FALSE ;
पूर्ण

/************************
 *
 *	hwt_init
 *
 *	Initialize hardware समयr.
 *
 *	व्योम hwt_init(
 *		काष्ठा s_smc *smc) ;
 * In
 *	smc - A poपूर्णांकer to the SMT Context काष्ठाure.
 * Out
 *	Nothing.
 *
 ************************/
व्योम hwt_init(काष्ठा s_smc *smc)
अणु
	smc->hw.t_start = 0 ;
	smc->hw.t_stop	= 0 ;
	smc->hw.समयr_activ = FALSE ;

	hwt_restart(smc) ;
पूर्ण

/************************
 *
 *	hwt_restart
 *
 *	Clear समयr पूर्णांकerrupt.
 *
 *	व्योम hwt_restart(
 *		काष्ठा s_smc *smc) ;
 * In
 *	smc - A poपूर्णांकer to the SMT Context काष्ठाure.
 * Out
 *	Nothing.
 *
 ************************/
व्योम hwt_restart(काष्ठा s_smc *smc)
अणु
	hwt_stop(smc) ;
पूर्ण

/************************
 *
 *	hwt_पढ़ो
 *
 *	Stop hardware समयr and पढ़ो समय elapsed since last start.
 *
 *	u_दीर्घ hwt_पढ़ो(smc) ;
 * In
 *	smc - A poपूर्णांकer to the SMT Context काष्ठाure.
 * Out
 *	The elapsed समय since last start in units of 16us.
 *
 ************************/
u_दीर्घ hwt_पढ़ो(काष्ठा s_smc *smc)
अणु
	u_लघु	tr ;
	u_दीर्घ	is ;

	अगर (smc->hw.समयr_activ) अणु
		hwt_stop(smc) ;
		tr = (u_लघु)((inpd(ADDR(B2_TI_VAL))/200) & 0xffff) ;

		is = GET_ISR() ;
		/* Check अगर समयr expired (or wraparound). */
		अगर ((tr > smc->hw.t_start) || (is & IS_TIMINT)) अणु
			hwt_restart(smc) ;
			smc->hw.t_stop = smc->hw.t_start ;
		पूर्ण
		अन्यथा
			smc->hw.t_stop = smc->hw.t_start - tr ;
	पूर्ण
	वापस smc->hw.t_stop;
पूर्ण

#अगर_घोषित	PCI
/************************
 *
 *	hwt_quick_पढ़ो
 *
 *	Stop hardware समयr and पढ़ो समयr value and start the समयr again.
 *
 *	u_दीर्घ hwt_पढ़ो(smc) ;
 * In
 *	smc - A poपूर्णांकer to the SMT Context काष्ठाure.
 * Out
 *	current समयr value in units of 80ns.
 *
 ************************/
u_दीर्घ hwt_quick_पढ़ो(काष्ठा s_smc *smc)
अणु
	u_दीर्घ पूर्णांकerval ;
	u_दीर्घ समय ;

	पूर्णांकerval = inpd(ADDR(B2_TI_INI)) ;
	outpw(ADDR(B2_TI_CRTL), TIM_STOP) ;
	समय = inpd(ADDR(B2_TI_VAL)) ;
	outpd(ADDR(B2_TI_INI),समय) ;
	outpw(ADDR(B2_TI_CRTL), TIM_START) ;
	outpd(ADDR(B2_TI_INI),पूर्णांकerval) ;

	वापस समय;
पूर्ण

/************************
 *
 *	hwt_रुको_समय(smc,start,duration)
 *
 *	This function वापसes after the amount of समय is elapsed
 *	since the start समय.
 * 
 * para	start		start समय
 *	duration	समय to रुको
 *
 * NOTE: The function will वापस immediately, अगर the समयr is not
 *	 started
 ************************/
व्योम hwt_रुको_समय(काष्ठा s_smc *smc, u_दीर्घ start, दीर्घ पूर्णांक duration)
अणु
	दीर्घ	dअगरf ;
	दीर्घ	पूर्णांकerval ;
	पूर्णांक	wrapped ;

	/*
	 * check अगर समयr is running
	 */
	अगर (smc->hw.समयr_activ == FALSE ||
		hwt_quick_पढ़ो(smc) == hwt_quick_पढ़ो(smc)) अणु
		वापस ;
	पूर्ण

	पूर्णांकerval = inpd(ADDR(B2_TI_INI)) ;
	अगर (पूर्णांकerval > duration) अणु
		करो अणु
			dअगरf = (दीर्घ)(start - hwt_quick_पढ़ो(smc)) ;
			अगर (dअगरf < 0) अणु
				dअगरf += पूर्णांकerval ;
			पूर्ण
		पूर्ण जबतक (dअगरf <= duration) ;
	पूर्ण
	अन्यथा अणु
		dअगरf = पूर्णांकerval ;
		wrapped = 0 ;
		करो अणु
			अगर (!wrapped) अणु
				अगर (hwt_quick_पढ़ो(smc) >= start) अणु
					dअगरf += पूर्णांकerval ;
					wrapped = 1 ;
				पूर्ण
			पूर्ण
			अन्यथा अणु
				अगर (hwt_quick_पढ़ो(smc) < start) अणु
					wrapped = 0 ;
				पूर्ण
			पूर्ण
		पूर्ण जबतक (dअगरf <= duration) ;
	पूर्ण
पूर्ण
#पूर्ण_अगर

