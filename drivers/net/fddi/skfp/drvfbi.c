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
 * FBI board dependent Driver क्रम SMT and LLC
 */

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"
#समावेश "h/supern_2.h"
#समावेश "h/skfbiinc.h"
#समावेश <linux/bitrev.h>
#समावेश <linux/pci.h>

/*
 * PCM active state
 */
#घोषणा PC8_ACTIVE	8

#घोषणा	LED_Y_ON	0x11	/* Used क्रम ring up/करोwn indication */
#घोषणा	LED_Y_OFF	0x10


#घोषणा MS2BCLK(x)	((x)*12500L)

/*
 * valid configuration values are:
 */

/*
 *	xPOS_ID:xxxx
 *	|	\  /
 *	|	 \/
 *	|	  --------------------- the patched POS_ID of the Adapter
 *	|				xxxx = (Venकरोr ID low byte,
 *	|					Venकरोr ID high byte,
 *	|					Device ID low byte,
 *	|					Device ID high byte)
 *	+------------------------------ the patched oem_id must be
 *					'S' for SK or 'I' क्रम IBM
 *					this is a लघु id क्रम the driver.
 */
#अगर_अघोषित MULT_OEM
#अगर_अघोषित	OEM_CONCEPT
स्थिर u_अक्षर oem_id[] = "xPOS_ID:xxxx" ;
#अन्यथा	/* OEM_CONCEPT */
स्थिर u_अक्षर oem_id[] = OEM_ID ;
#पूर्ण_अगर	/* OEM_CONCEPT */
#घोषणा	ID_BYTE0	8
#घोषणा	OEMID(smc,i)	oem_id[ID_BYTE0 + i]
#अन्यथा	/* MULT_OEM */
स्थिर काष्ठा s_oem_ids oem_ids[] = अणु
#समावेश "oemids.h"
अणु0पूर्ण
पूर्ण;
#घोषणा	OEMID(smc,i)	smc->hw.oem_id->oi_id[i]
#पूर्ण_अगर	/* MULT_OEM */

/* Prototypes of बाह्यal functions */
#अगर_घोषित AIX
बाह्य पूर्णांक AIX_vpdReadByte() ;
#पूर्ण_अगर


/* Prototype of a local function. */
अटल व्योम smt_stop_watchकरोg(काष्ठा s_smc *smc);

/*
 * FDDI card reset
 */
अटल व्योम card_start(काष्ठा s_smc *smc)
अणु
	पूर्णांक i ;
#अगर_घोषित	PCI
	u_अक्षर	rev_id ;
	u_लघु word;
#पूर्ण_अगर

	smt_stop_watchकरोg(smc) ;

#अगर_घोषित	PCI
	/*
	 * make sure no transfer activity is pending
	 */
	outpw(FM_A(FM_MDREG1),FM_MINIT) ;
	outp(ADDR(B0_CTRL), CTRL_HPI_SET) ;
	hwt_रुको_समय(smc,hwt_quick_पढ़ो(smc),MS2BCLK(10)) ;
	/*
	 * now reset everything
	 */
	outp(ADDR(B0_CTRL),CTRL_RST_SET) ;	/* reset क्रम all chips */
	i = (पूर्णांक) inp(ADDR(B0_CTRL)) ;		/* करो dummy पढ़ो */
	SK_UNUSED(i) ;				/* Make LINT happy. */
	outp(ADDR(B0_CTRL), CTRL_RST_CLR) ;

	/*
	 * Reset all bits in the PCI STATUS रेजिस्टर
	 */
	outp(ADDR(B0_TST_CTRL), TST_CFG_WRITE_ON) ;	/* enable क्रम ग_लिखोs */
	word = inpw(PCI_C(PCI_STATUS)) ;
	outpw(PCI_C(PCI_STATUS), word | PCI_STATUS_ERROR_BITS);
	outp(ADDR(B0_TST_CTRL), TST_CFG_WRITE_OFF) ;	/* disable ग_लिखोs */

	/*
	 * Release the reset of all the State machines
	 * Release Master_Reset
	 * Release HPI_SM_Reset
	 */
	outp(ADDR(B0_CTRL), CTRL_MRST_CLR|CTRL_HPI_CLR) ;

	/*
	 * determine the adapter type
	 * Note: Do it here, because some drivers may call card_start() once
	 *	 at very first beक्रमe any other initialization functions is
	 *	 executed.
	 */
	rev_id = inp(PCI_C(PCI_REVISION_ID)) ;
	अगर ((rev_id & 0xf0) == SK_ML_ID_1 || (rev_id & 0xf0) == SK_ML_ID_2) अणु
		smc->hw.hw_is_64bit = TRUE ;
	पूर्ण अन्यथा अणु
		smc->hw.hw_is_64bit = FALSE ;
	पूर्ण

	/*
	 * Watermark initialization
	 */
	अगर (!smc->hw.hw_is_64bit) अणु
		outpd(ADDR(B4_R1_F), RX_WATERMARK) ;
		outpd(ADDR(B5_XA_F), TX_WATERMARK) ;
		outpd(ADDR(B5_XS_F), TX_WATERMARK) ;
	पूर्ण

	outp(ADDR(B0_CTRL),CTRL_RST_CLR) ;	/* clear the reset chips */
	outp(ADDR(B0_LED),LED_GA_OFF|LED_MY_ON|LED_GB_OFF) ; /* ye LED on */

	/* init the समयr value क्रम the watch करोg 2,5 minutes */
	outpd(ADDR(B2_WDOG_INI),0x6FC23AC0) ;

	/* initialize the ISR mask */
	smc->hw.is_imask = ISR_MASK ;
	smc->hw.hw_state = STOPPED ;
#पूर्ण_अगर
	GET_PAGE(0) ;		/* necessary क्रम BOOT */
पूर्ण

व्योम card_stop(काष्ठा s_smc *smc)
अणु
	smt_stop_watchकरोg(smc) ;
	smc->hw.mac_ring_is_up = 0 ;		/* ring करोwn */

#अगर_घोषित	PCI
	/*
	 * make sure no transfer activity is pending
	 */
	outpw(FM_A(FM_MDREG1),FM_MINIT) ;
	outp(ADDR(B0_CTRL), CTRL_HPI_SET) ;
	hwt_रुको_समय(smc,hwt_quick_पढ़ो(smc),MS2BCLK(10)) ;
	/*
	 * now reset everything
	 */
	outp(ADDR(B0_CTRL),CTRL_RST_SET) ;	/* reset क्रम all chips */
	outp(ADDR(B0_CTRL),CTRL_RST_CLR) ;	/* reset क्रम all chips */
	outp(ADDR(B0_LED),LED_GA_OFF|LED_MY_OFF|LED_GB_OFF) ; /* all LEDs off */
	smc->hw.hw_state = STOPPED ;
#पूर्ण_अगर
पूर्ण
/*--------------------------- ISR handling ----------------------------------*/

व्योम mac1_irq(काष्ठा s_smc *smc, u_लघु stu, u_लघु stl)
अणु
	पूर्णांक	restart_tx = 0 ;
again:

	/*
	 * parity error: note encoding error is not possible in tag mode
	 */
	अगर (stl & (FM_SPCEPDS  |	/* parity err. syn.q.*/
		   FM_SPCEPDA0 |	/* parity err. a.q.0 */
		   FM_SPCEPDA1)) अणु	/* parity err. a.q.1 */
		SMT_PANIC(smc,SMT_E0134, SMT_E0134_MSG) ;
	पूर्ण
	/*
	 * buffer underrun: can only occur अगर a tx threshold is specअगरied
	 */
	अगर (stl & (FM_STBURS  |		/* tx buffer underrun syn.q.*/
		   FM_STBURA0 |		/* tx buffer underrun a.q.0 */
		   FM_STBURA1)) अणु	/* tx buffer underrun a.q.2 */
		SMT_PANIC(smc,SMT_E0133, SMT_E0133_MSG) ;
	पूर्ण

	अगर ( (stu & (FM_SXMTABT |		/* transmit पात */
		     FM_STXABRS |		/* syn. tx पात */
		     FM_STXABRA0)) ||		/* asyn. tx पात */
	     (stl & (FM_SQLCKS |		/* lock क्रम syn. q. */
		     FM_SQLCKA0)) ) अणु		/* lock क्रम asyn. q. */
		क्रमmac_tx_restart(smc) ;	/* init tx */
		restart_tx = 1 ;
		stu = inpw(FM_A(FM_ST1U)) ;
		stl = inpw(FM_A(FM_ST1L)) ;
		stu &= ~ (FM_STECFRMA0 | FM_STEFRMA0 | FM_STEFRMS) ;
		अगर (stu || stl)
			जाओ again ;
	पूर्ण

	अगर (stu & (FM_STEFRMA0 |	/* end of asyn tx */
		    FM_STEFRMS)) अणु	/* end of sync tx */
		restart_tx = 1 ;
	पूर्ण

	अगर (restart_tx)
		llc_restart_tx(smc) ;
पूर्ण

/*
 * पूर्णांकerrupt source= plc1
 * this function is called in nwfbisr.यंत्र
 */
व्योम plc1_irq(काष्ठा s_smc *smc)
अणु
	u_लघु	st = inpw(PLC(PB,PL_INTR_EVENT)) ;

	plc_irq(smc,PB,st) ;
पूर्ण

/*
 * पूर्णांकerrupt source= plc2
 * this function is called in nwfbisr.यंत्र
 */
व्योम plc2_irq(काष्ठा s_smc *smc)
अणु
	u_लघु	st = inpw(PLC(PA,PL_INTR_EVENT)) ;

	plc_irq(smc,PA,st) ;
पूर्ण


/*
 * पूर्णांकerrupt source= समयr
 */
व्योम समयr_irq(काष्ठा s_smc *smc)
अणु
	hwt_restart(smc);
	smc->hw.t_stop = smc->hw.t_start;
	smt_समयr_करोne(smc) ;
पूर्ण

/*
 * वापस S-port (PA or PB)
 */
पूर्णांक pcm_get_s_port(काष्ठा s_smc *smc)
अणु
	SK_UNUSED(smc) ;
	वापस PS;
पूर्ण

/*
 * Station Label = "FDDI-XYZ" where
 *
 *	X = connector type
 *	Y = PMD type
 *	Z = port type
 */
#घोषणा STATION_LABEL_CONNECTOR_OFFSET	5
#घोषणा STATION_LABEL_PMD_OFFSET	6
#घोषणा STATION_LABEL_PORT_OFFSET	7

व्योम पढ़ो_address(काष्ठा s_smc *smc, u_अक्षर *mac_addr)
अणु
	अक्षर ConnectorType ;
	अक्षर PmdType ;
	पूर्णांक	i ;

#अगर_घोषित	PCI
	क्रम (i = 0; i < 6; i++) अणु	/* पढ़ो mac address from board */
		smc->hw.fddi_phys_addr.a[i] =
			bitrev8(inp(ADDR(B2_MAC_0+i)));
	पूर्ण
#पूर्ण_अगर

	ConnectorType = inp(ADDR(B2_CONN_TYP)) ;
	PmdType = inp(ADDR(B2_PMD_TYP)) ;

	smc->y[PA].pmd_type[PMD_SK_CONN] =
	smc->y[PB].pmd_type[PMD_SK_CONN] = ConnectorType ;
	smc->y[PA].pmd_type[PMD_SK_PMD ] =
	smc->y[PB].pmd_type[PMD_SK_PMD ] = PmdType ;

	अगर (mac_addr) अणु
		क्रम (i = 0; i < 6 ;i++) अणु
			smc->hw.fddi_canon_addr.a[i] = mac_addr[i] ;
			smc->hw.fddi_home_addr.a[i] = bitrev8(mac_addr[i]);
		पूर्ण
		वापस ;
	पूर्ण
	smc->hw.fddi_home_addr = smc->hw.fddi_phys_addr ;

	क्रम (i = 0; i < 6 ;i++) अणु
		smc->hw.fddi_canon_addr.a[i] =
			bitrev8(smc->hw.fddi_phys_addr.a[i]);
	पूर्ण
पूर्ण

/*
 * FDDI card soft reset
 */
व्योम init_board(काष्ठा s_smc *smc, u_अक्षर *mac_addr)
अणु
	card_start(smc) ;
	पढ़ो_address(smc,mac_addr) ;

	अगर (!(inp(ADDR(B0_DAS)) & DAS_AVAIL))
		smc->s.sas = SMT_SAS ;	/* Single att. station */
	अन्यथा
		smc->s.sas = SMT_DAS ;	/* Dual att. station */

	अगर (!(inp(ADDR(B0_DAS)) & DAS_BYP_ST))
		smc->mib.fddiSMTBypassPresent = 0 ;
		/* without opt. bypass */
	अन्यथा
		smc->mib.fddiSMTBypassPresent = 1 ;
		/* with opt. bypass */
पूर्ण

/*
 * insert or deinsert optical bypass (called by ECM)
 */
व्योम sm_pm_bypass_req(काष्ठा s_smc *smc, पूर्णांक mode)
अणु
	DB_ECMN(1, "ECM : sm_pm_bypass_req(%s)",
		mode == BP_INSERT ? "BP_INSERT" : "BP_DEINSERT");

	अगर (smc->s.sas != SMT_DAS)
		वापस ;

#अगर_घोषित	PCI
	चयन(mode) अणु
	हाल BP_INSERT :
		outp(ADDR(B0_DAS),DAS_BYP_INS) ;	/* insert station */
		अवरोध ;
	हाल BP_DEINSERT :
		outp(ADDR(B0_DAS),DAS_BYP_RMV) ;	/* bypass station */
		अवरोध ;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * check अगर bypass connected
 */
पूर्णांक sm_pm_bypass_present(काष्ठा s_smc *smc)
अणु
	वापस (inp(ADDR(B0_DAS)) & DAS_BYP_ST) ? TRUE : FALSE;
पूर्ण

व्योम plc_clear_irq(काष्ठा s_smc *smc, पूर्णांक p)
अणु
	SK_UNUSED(p) ;

	SK_UNUSED(smc) ;
पूर्ण


/*
 * led_indication called by rmt_indication() and
 * pcm_state_change()
 *
 * Input:
 *	smc:	SMT context
 *	led_event:
 *	0	Only चयन green LEDs according to their respective PCM state
 *	LED_Y_OFF	just चयन yellow LED off
 *	LED_Y_ON	just चयन yello LED on
 */
अटल व्योम led_indication(काष्ठा s_smc *smc, पूर्णांक led_event)
अणु
	/* use smc->hw.mac_ring_is_up == TRUE 
	 * as indication क्रम Ring Operational
	 */
	u_लघु			led_state ;
	काष्ठा s_phy		*phy ;
	काष्ठा fddi_mib_p	*mib_a ;
	काष्ठा fddi_mib_p	*mib_b ;

	phy = &smc->y[PA] ;
	mib_a = phy->mib ;
	phy = &smc->y[PB] ;
	mib_b = phy->mib ;

#अगर_घोषित	PCI
        led_state = 0 ;
	
	/* Ring up = yellow led OFF*/
	अगर (led_event == LED_Y_ON) अणु
		led_state |= LED_MY_ON ;
	पूर्ण
	अन्यथा अगर (led_event == LED_Y_OFF) अणु
		led_state |= LED_MY_OFF ;
	पूर्ण
	अन्यथा अणु	/* PCM state changed */
		/* Link at Port A/S = green led A ON */
		अगर (mib_a->fddiPORTPCMState == PC8_ACTIVE) अणु	
			led_state |= LED_GA_ON ;
		पूर्ण
		अन्यथा अणु
			led_state |= LED_GA_OFF ;
		पूर्ण
		
		/* Link at Port B = green led B ON */
		अगर (mib_b->fddiPORTPCMState == PC8_ACTIVE) अणु
			led_state |= LED_GB_ON ;
		पूर्ण
		अन्यथा अणु
			led_state |= LED_GB_OFF ;
		पूर्ण
	पूर्ण

        outp(ADDR(B0_LED), led_state) ;
#पूर्ण_अगर	/* PCI */

पूर्ण


व्योम pcm_state_change(काष्ठा s_smc *smc, पूर्णांक plc, पूर्णांक p_state)
अणु
	/*
	 * the current implementation of pcm_state_change() in the driver
	 * parts must be नामd to drv_pcm_state_change() which will be called
	 * now after led_indication.
	 */
	DRV_PCM_STATE_CHANGE(smc,plc,p_state) ;
	
	led_indication(smc,0) ;
पूर्ण


व्योम rmt_indication(काष्ठा s_smc *smc, पूर्णांक i)
अणु
	/* Call a driver special function अगर defined */
	DRV_RMT_INDICATION(smc,i) ;

        led_indication(smc, i ? LED_Y_OFF : LED_Y_ON) ;
पूर्ण


/*
 * llc_recover_tx called by init_tx (fplus.c)
 */
व्योम llc_recover_tx(काष्ठा s_smc *smc)
अणु
#अगर_घोषित	LOAD_GEN
	बाह्य	पूर्णांक load_gen_flag ;

	load_gen_flag = 0 ;
#पूर्ण_अगर
#अगर_अघोषित	SYNC
	smc->hw.n_a_send= 0 ;
#अन्यथा
	SK_UNUSED(smc) ;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित MULT_OEM
अटल पूर्णांक is_equal_num(अक्षर comp1[], अक्षर comp2[], पूर्णांक num)
अणु
	पूर्णांक i ;

	क्रम (i = 0 ; i < num ; i++) अणु
		अगर (comp1[i] != comp2[i])
			वापस 0;
	पूर्ण
		वापस 1;
पूर्ण	/* is_equal_num */


/*
 * set the OEM ID शेषs, and test the contents of the OEM data base
 * The शेष OEM is the first ACTIVE entry in the OEM data base 
 *
 * वापसs:	0	success
 *		1	error in data base
 *		2	data base empty
 *		3	no active entry	
 */
पूर्णांक set_oi_id_def(काष्ठा s_smc *smc)
अणु
	पूर्णांक sel_id ;
	पूर्णांक i ;
	पूर्णांक act_entries ;

	i = 0 ;
	sel_id = -1 ;
	act_entries = FALSE ;
	smc->hw.oem_id = 0 ;
	smc->hw.oem_min_status = OI_STAT_ACTIVE ;
	
	/* check OEM data base */
	जबतक (oem_ids[i].oi_status) अणु
		चयन (oem_ids[i].oi_status) अणु
		हाल OI_STAT_ACTIVE:
			act_entries = TRUE ;	/* we have active IDs */
			अगर (sel_id == -1)
				sel_id = i ;	/* save the first active ID */
		हाल OI_STAT_VALID:
		हाल OI_STAT_PRESENT:
			i++ ;
			अवरोध ;			/* entry ok */
		शेष:
			वापस 1;		/* invalid oi_status */
		पूर्ण
	पूर्ण

	अगर (i == 0)
		वापस 2;
	अगर (!act_entries)
		वापस 3;

	/* ok, we have a valid OEM data base with an active entry */
	smc->hw.oem_id = (काष्ठा s_oem_ids *)  &oem_ids[sel_id] ;
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* MULT_OEM */

व्योम driver_get_bia(काष्ठा s_smc *smc, काष्ठा fddi_addr *bia_addr)
अणु
	पूर्णांक i ;

	क्रम (i = 0 ; i < 6 ; i++)
		bia_addr->a[i] = bitrev8(smc->hw.fddi_phys_addr.a[i]);
पूर्ण

व्योम smt_start_watchकरोg(काष्ठा s_smc *smc)
अणु
	SK_UNUSED(smc) ;	/* Make LINT happy. */

#अगर_अघोषित	DEBUG

#अगर_घोषित	PCI
	अगर (smc->hw.wकरोg_used) अणु
		outpw(ADDR(B2_WDOG_CRTL),TIM_START) ;	/* Start समयr. */
	पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* DEBUG */
पूर्ण

अटल व्योम smt_stop_watchकरोg(काष्ठा s_smc *smc)
अणु
	SK_UNUSED(smc) ;	/* Make LINT happy. */
#अगर_अघोषित	DEBUG

#अगर_घोषित	PCI
	अगर (smc->hw.wकरोg_used) अणु
		outpw(ADDR(B2_WDOG_CRTL),TIM_STOP) ;	/* Stop समयr. */
	पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* DEBUG */
पूर्ण

#अगर_घोषित	PCI

व्योम mac_करो_pci_fix(काष्ठा s_smc *smc)
अणु
	SK_UNUSED(smc) ;
पूर्ण
#पूर्ण_अगर	/* PCI */

