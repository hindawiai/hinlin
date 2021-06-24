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
	SMT समयr
*/

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"

अटल व्योम समयr_करोne(काष्ठा s_smc *smc, पूर्णांक restart);

व्योम smt_समयr_init(काष्ठा s_smc *smc)
अणु
	smc->t.st_queue = शून्य;
	smc->t.st_fast.पंचांग_active = FALSE ;
	smc->t.st_fast.पंचांग_next = शून्य;
	hwt_init(smc) ;
पूर्ण

व्योम smt_समयr_stop(काष्ठा s_smc *smc, काष्ठा smt_समयr *समयr)
अणु
	काष्ठा smt_समयr	**prev ;
	काष्ठा smt_समयr	*पंचांग ;

	/*
	 * हटाओ समयr from queue
	 */
	समयr->पंचांग_active = FALSE ;
	अगर (smc->t.st_queue == समयr && !समयr->पंचांग_next) अणु
		hwt_stop(smc) ;
	पूर्ण
	क्रम (prev = &smc->t.st_queue ; (पंचांग = *prev) ; prev = &पंचांग->पंचांग_next ) अणु
		अगर (पंचांग == समयr) अणु
			*prev = पंचांग->पंचांग_next ;
			अगर (पंचांग->पंचांग_next) अणु
				पंचांग->पंचांग_next->पंचांग_delta += पंचांग->पंचांग_delta ;
			पूर्ण
			वापस ;
		पूर्ण
	पूर्ण
पूर्ण

व्योम smt_समयr_start(काष्ठा s_smc *smc, काष्ठा smt_समयr *समयr, u_दीर्घ समय,
		     u_दीर्घ token)
अणु
	काष्ठा smt_समयr	**prev ;
	काष्ठा smt_समयr	*पंचांग ;
	u_दीर्घ			delta = 0 ;

	समय /= 16 ;		/* input is uS, घड़ी ticks are 16uS */
	अगर (!समय)
		समय = 1 ;
	smt_समयr_stop(smc,समयr) ;
	समयr->पंचांग_smc = smc ;
	समयr->पंचांग_token = token ;
	समयr->पंचांग_active = TRUE ;
	अगर (!smc->t.st_queue) अणु
		smc->t.st_queue = समयr ;
		समयr->पंचांग_next = शून्य;
		समयr->पंचांग_delta = समय ;
		hwt_start(smc,समय) ;
		वापस ;
	पूर्ण
	/*
	 * समयr correction
	 */
	समयr_करोne(smc,0) ;

	/*
	 * find position in queue
	 */
	delta = 0 ;
	क्रम (prev = &smc->t.st_queue ; (पंचांग = *prev) ; prev = &पंचांग->पंचांग_next ) अणु
		अगर (delta + पंचांग->पंचांग_delta > समय) अणु
			अवरोध ;
		पूर्ण
		delta += पंचांग->पंचांग_delta ;
	पूर्ण
	/* insert in queue */
	*prev = समयr ;
	समयr->पंचांग_next = पंचांग ;
	समयr->पंचांग_delta = समय - delta ;
	अगर (पंचांग)
		पंचांग->पंचांग_delta -= समयr->पंचांग_delta ;
	/*
	 * start new with first
	 */
	hwt_start(smc,smc->t.st_queue->पंचांग_delta) ;
पूर्ण

व्योम smt_क्रमce_irq(काष्ठा s_smc *smc)
अणु
	smt_समयr_start(smc,&smc->t.st_fast,32L, EV_TOKEN(EVENT_SMT,SM_FAST)); 
पूर्ण

व्योम smt_समयr_करोne(काष्ठा s_smc *smc)
अणु
	समयr_करोne(smc,1) ;
पूर्ण

अटल व्योम समयr_करोne(काष्ठा s_smc *smc, पूर्णांक restart)
अणु
	u_दीर्घ			delta ;
	काष्ठा smt_समयr	*पंचांग ;
	काष्ठा smt_समयr	*next ;
	काष्ठा smt_समयr	**last ;
	पूर्णांक			करोne = 0 ;

	delta = hwt_पढ़ो(smc) ;
	last = &smc->t.st_queue ;
	पंचांग = smc->t.st_queue ;
	जबतक (पंचांग && !करोne) अणु
		अगर (delta >= पंचांग->पंचांग_delta) अणु
			पंचांग->पंचांग_active = FALSE ;
			delta -= पंचांग->पंचांग_delta ;
			last = &पंचांग->पंचांग_next ;
			पंचांग = पंचांग->पंचांग_next ;
		पूर्ण
		अन्यथा अणु
			पंचांग->पंचांग_delta -= delta ;
			delta = 0 ;
			करोne = 1 ;
		पूर्ण
	पूर्ण
	*last = शून्य;
	next = smc->t.st_queue ;
	smc->t.st_queue = पंचांग ;

	क्रम ( पंचांग = next ; पंचांग ; पंचांग = next) अणु
		next = पंचांग->पंचांग_next ;
		समयr_event(smc,पंचांग->पंचांग_token) ;
	पूर्ण

	अगर (restart && smc->t.st_queue)
		hwt_start(smc,smc->t.st_queue->पंचांग_delta) ;
पूर्ण

