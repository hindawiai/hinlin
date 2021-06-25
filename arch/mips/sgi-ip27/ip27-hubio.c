<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1992-1997, 2000-2003 Silicon Graphics, Inc.
 * Copyright (C) 2004 Christoph Hellwig.
 *
 * Support functions क्रम the HUB ASIC - mostly PIO mapping related.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/माला.स>
#समावेश <linux/mmzone.h>
#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/पन.स>
#समावेश <यंत्र/xtalk/xtalk.h>


अटल पूर्णांक क्रमce_fire_and_क्रमget = 1;

/**
 * hub_pio_map	-  establish a HUB PIO mapping
 *
 * @hub:	hub to perक्रमm PIO mapping on
 * @widget:	widget ID to perक्रमm PIO mapping क्रम
 * @xtalk_addr: xtalk_address that needs to be mapped
 * @size:	size of the PIO mapping
 *
 **/
अचिन्हित दीर्घ hub_pio_map(nasid_t nasid, xwidgetnum_t widget,
			  अचिन्हित दीर्घ xtalk_addr, माप_प्रकार size)
अणु
	अचिन्हित i;

	/* use small-winकरोw mapping अगर possible */
	अगर ((xtalk_addr % SWIN_SIZE) + size <= SWIN_SIZE)
		वापस NODE_SWIN_BASE(nasid, widget) + (xtalk_addr % SWIN_SIZE);

	अगर ((xtalk_addr % BWIN_SIZE) + size > BWIN_SIZE) अणु
		prपूर्णांकk(KERN_WARNING "PIO mapping at hub %d widget %d addr 0x%lx"
				" too big (%ld)\n",
				nasid, widget, xtalk_addr, size);
		वापस 0;
	पूर्ण

	xtalk_addr &= ~(BWIN_SIZE-1);
	क्रम (i = 0; i < HUB_NUM_BIG_WINDOW; i++) अणु
		अगर (test_and_set_bit(i, hub_data(nasid)->h_bigwin_used))
			जारी;

		/*
		 * The code below करोes a PIO ग_लिखो to setup an ITTE entry.
		 *
		 * We need to prevent other CPUs from seeing our updated
		 * memory shaकरोw of the ITTE (in the piomap) until the ITTE
		 * entry is actually set up; otherwise, another CPU might
		 * attempt a PIO prematurely.
		 *
		 * Also, the only way we can know that an entry has been
		 * received  by the hub and can be used by future PIO पढ़ोs/
		 * ग_लिखोs is by पढ़ोing back the ITTE entry after writing it.
		 *
		 * For these two reasons, we PIO पढ़ो back the ITTE entry
		 * after we ग_लिखो it.
		 */
		IIO_ITTE_PUT(nasid, i, HUB_PIO_MAP_TO_MEM, widget, xtalk_addr);
		__raw_पढ़ोq(IIO_ITTE_GET(nasid, i));

		वापस NODE_BWIN_BASE(nasid, widget) + (xtalk_addr % BWIN_SIZE);
	पूर्ण

	prपूर्णांकk(KERN_WARNING "unable to establish PIO mapping for at"
			" hub %d widget %d addr 0x%lx\n",
			nasid, widget, xtalk_addr);
	वापस 0;
पूर्ण


/*
 * hub_setup_prb(nasid, prbnum, credits, conveyor)
 *
 *	Put a PRB पूर्णांकo fire-and-क्रमget mode अगर conveyor isn't set.  Otherwise,
 *	put it पूर्णांकo conveyor belt mode with the specअगरied number of credits.
 */
अटल व्योम hub_setup_prb(nasid_t nasid, पूर्णांक prbnum, पूर्णांक credits)
अणु
	जोड़ iprb_u prb;
	पूर्णांक prb_offset;

	/*
	 * Get the current रेजिस्टर value.
	 */
	prb_offset = IIO_IOPRB(prbnum);
	prb.iprb_regval = REMOTE_HUB_L(nasid, prb_offset);

	/*
	 * Clear out some fields.
	 */
	prb.iprb_ovflow = 1;
	prb.iprb_bnakctr = 0;
	prb.iprb_anakctr = 0;

	/*
	 * Enable or disable fire-and-क्रमget mode.
	 */
	prb.iprb_ff = क्रमce_fire_and_क्रमget ? 1 : 0;

	/*
	 * Set the appropriate number of PIO credits क्रम the widget.
	 */
	prb.iprb_xtalkctr = credits;

	/*
	 * Store the new value to the रेजिस्टर.
	 */
	REMOTE_HUB_S(nasid, prb_offset, prb.iprb_regval);
पूर्ण

/**
 * hub_set_piomode  -  set pio mode क्रम a given hub
 *
 * @nasid:	physical node ID क्रम the hub in question
 *
 * Put the hub पूर्णांकo either "PIO conveyor belt" mode or "fire-and-forget" mode.
 * To करो this, we have to make असलolutely sure that no PIOs are in progress
 * so we turn off access to all widमाला_लो क्रम the duration of the function.
 *
 * XXX - This code should really check what kind of widget we're talking
 * to.	Bridges can only handle three requests, but XG will करो more.
 * How many can crossbow handle to widget 0?  We're assuming 1.
 *
 * XXX - There is a bug in the crossbow that link reset PIOs करो not
 * वापस ग_लिखो responses.  The easiest solution to this problem is to
 * leave widget 0 (xbow) in fire-and-क्रमget mode at all बार.	This
 * only affects pio's to xbow रेजिस्टरs, which should be rare.
 **/
अटल व्योम hub_set_piomode(nasid_t nasid)
अणु
	u64 ii_iowa;
	जोड़ hubii_wcr_u ii_wcr;
	अचिन्हित i;

	ii_iowa = REMOTE_HUB_L(nasid, IIO_OUTWIDGET_ACCESS);
	REMOTE_HUB_S(nasid, IIO_OUTWIDGET_ACCESS, 0);

	ii_wcr.wcr_reg_value = REMOTE_HUB_L(nasid, IIO_WCR);

	अगर (ii_wcr.iwcr_dir_con) अणु
		/*
		 * Assume a bridge here.
		 */
		hub_setup_prb(nasid, 0, 3);
	पूर्ण अन्यथा अणु
		/*
		 * Assume a crossbow here.
		 */
		hub_setup_prb(nasid, 0, 1);
	पूर्ण

	/*
	 * XXX - Here's where we should take the widget type पूर्णांकo
	 * when account assigning credits.
	 */
	क्रम (i = HUB_WIDGET_ID_MIN; i <= HUB_WIDGET_ID_MAX; i++)
		hub_setup_prb(nasid, i, 3);

	REMOTE_HUB_S(nasid, IIO_OUTWIDGET_ACCESS, ii_iowa);
पूर्ण

/*
 * hub_pio_init	 -  PIO-related hub initialization
 *
 * @hub:	hubinfo काष्ठाure क्रम our hub
 */
व्योम hub_pio_init(nasid_t nasid)
अणु
	अचिन्हित i;

	/* initialize big winकरोw piomaps क्रम this hub */
	biपंचांगap_zero(hub_data(nasid)->h_bigwin_used, HUB_NUM_BIG_WINDOW);
	क्रम (i = 0; i < HUB_NUM_BIG_WINDOW; i++)
		IIO_ITTE_DISABLE(nasid, i);

	hub_set_piomode(nasid);
पूर्ण
