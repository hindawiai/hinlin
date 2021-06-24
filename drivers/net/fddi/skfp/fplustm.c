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
 * FORMAC+ Driver क्रम tag mode
 */

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"
#समावेश "h/supern_2.h"
#समावेश <linux/bitrev.h>
#समावेश <linux/etherdevice.h>

#अगर_अघोषित UNUSED
#अगर_घोषित  lपूर्णांक
#घोषणा UNUSED(x)	(x) = (x)
#अन्यथा
#घोषणा UNUSED(x)
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा FM_ADDRX	 (FM_ADDET|FM_EXGPA0|FM_EXGPA1)
#घोषणा MS2BCLK(x)	((x)*12500L)
#घोषणा US2BCLK(x)	((x)*1250L)

/*
 * prototypes क्रम अटल function
 */
अटल व्योम build_claim_beacon(काष्ठा s_smc *smc, u_दीर्घ t_request);
अटल पूर्णांक init_mac(काष्ठा s_smc *smc, पूर्णांक all);
अटल व्योम rपंचांग_init(काष्ठा s_smc *smc);
अटल व्योम smt_split_up_fअगरo(काष्ठा s_smc *smc);

#अगर (!defined(NO_SMT_PANIC) || defined(DEBUG))
अटल	अक्षर ग_लिखो_mdr_warning [] = "E350 write_mdr() FM_SNPPND is set\n";
अटल	अक्षर cam_warning [] = "E_SMT_004: CAM still busy\n";
#पूर्ण_अगर

#घोषणा	DUMMY_READ()	smc->hw.mc_dummy = (u_लघु) inp(ADDR(B0_RAP))

#घोषणा	CHECK_NPP() अणु	अचिन्हित पूर्णांक k = 10000 ;\
			जबतक ((inpw(FM_A(FM_STMCHN)) & FM_SNPPND) && k) k--;\
			अगर (!k) अणु \
				SMT_PANIC(smc,SMT_E0130, SMT_E0130_MSG) ; \
			पूर्ण	\
		पूर्ण

#घोषणा	CHECK_CAM() अणु	अचिन्हित पूर्णांक k = 10 ;\
			जबतक (!(inpw(FM_A(FM_AFSTAT)) & FM_DONE) && k) k--;\
			अगर (!k) अणु \
				SMT_PANIC(smc,SMT_E0131, SMT_E0131_MSG) ; \
			पूर्ण	\
		पूर्ण

स्थिर काष्ठा fddi_addr fddi_broadcast = अणुअणु0xff,0xff,0xff,0xff,0xff,0xffपूर्णपूर्ण;
अटल स्थिर काष्ठा fddi_addr null_addr = अणुअणु0,0,0,0,0,0पूर्णपूर्ण;
अटल स्थिर काष्ठा fddi_addr dbeacon_multi = अणुअणु0x01,0x80,0xc2,0x00,0x01,0x00पूर्णपूर्ण;

अटल स्थिर u_लघु my_said = 0xffff ;	/* लघु address (n.u.) */
अटल स्थिर u_लघु my_sagp = 0xffff ;	/* लघु group address (n.u.) */

/*
 * define my address
 */
#अगर_घोषित	USE_CAN_ADDR
#घोषणा MA	smc->hw.fddi_canon_addr
#अन्यथा
#घोषणा MA	smc->hw.fddi_home_addr
#पूर्ण_अगर


/*
 * useful पूर्णांकerrupt bits
 */
अटल स्थिर पूर्णांक mac_imsk1u = FM_STXABRS | FM_STXABRA0 | FM_SXMTABT ;
अटल स्थिर पूर्णांक mac_imsk1l = FM_SQLCKS | FM_SQLCKA0 | FM_SPCEPDS | FM_SPCEPDA0|
			FM_STBURS | FM_STBURA0 ;

	/* delete FM_SRBFL after tests */
अटल स्थिर पूर्णांक mac_imsk2u = FM_SERRSF | FM_SNFSLD | FM_SRCVOVR | FM_SRBFL |
			FM_SMYCLM ;
अटल स्थिर पूर्णांक mac_imsk2l = FM_STRTEXR | FM_SDUPCLM | FM_SFRMCTR |
			FM_SERRCTR | FM_SLSTCTR |
			FM_STRTEXP | FM_SMULTDA | FM_SRNGOP ;

अटल स्थिर पूर्णांक mac_imsk3u = FM_SRCVOVR2 | FM_SRBFL2 ;
अटल स्थिर पूर्णांक mac_imsk3l = FM_SRPERRQ2 | FM_SRPERRQ1 ;

अटल स्थिर पूर्णांक mac_beacon_imsk2u = FM_SOTRBEC | FM_SMYBEC | FM_SBEC |
			FM_SLOCLM | FM_SHICLM | FM_SMYCLM | FM_SCLM ;


अटल u_दीर्घ mac_get_tneg(काष्ठा s_smc *smc)
अणु
	u_दीर्घ	tneg ;

	tneg = (u_दीर्घ)((दीर्घ)inpw(FM_A(FM_TNEG))<<5) ;
	वापस (u_दीर्घ)((tneg + ((inpw(FM_A(FM_TMRS))>>10)&0x1f)) |
		0xffe00000L) ;
पूर्ण

व्योम mac_update_counter(काष्ठा s_smc *smc)
अणु
	smc->mib.m[MAC0].fddiMACFrame_Ct =
		(smc->mib.m[MAC0].fddiMACFrame_Ct & 0xffff0000L)
		+ (u_लघु) inpw(FM_A(FM_FCNTR)) ;
	smc->mib.m[MAC0].fddiMACLost_Ct =
		(smc->mib.m[MAC0].fddiMACLost_Ct & 0xffff0000L)
		+ (u_लघु) inpw(FM_A(FM_LCNTR)) ;
	smc->mib.m[MAC0].fddiMACError_Ct =
		(smc->mib.m[MAC0].fddiMACError_Ct & 0xffff0000L)
		+ (u_लघु) inpw(FM_A(FM_ECNTR)) ;
	smc->mib.m[MAC0].fddiMACT_Neg = mac_get_tneg(smc) ;
#अगर_घोषित SMT_REAL_TOKEN_CT
	/*
	 * If the token counter is emulated it is updated in smt_event.
	 */
	TBD
#अन्यथा
	smt_emulate_token_ct( smc, MAC0 );
#पूर्ण_अगर
पूर्ण

/*
 * ग_लिखो दीर्घ value पूर्णांकo buffer memory over memory data रेजिस्टर (MDR),
 */
अटल व्योम ग_लिखो_mdr(काष्ठा s_smc *smc, u_दीर्घ val)
अणु
	CHECK_NPP() ;
	MDRW(val) ;
पूर्ण

#अगर 0
/*
 * पढ़ो दीर्घ value from buffer memory over memory data रेजिस्टर (MDR),
 */
अटल u_दीर्घ पढ़ो_mdr(काष्ठा s_smc *smc, अचिन्हित पूर्णांक addr)
अणु
	दीर्घ p ;
	CHECK_NPP() ;
	MARR(addr) ;
	outpw(FM_A(FM_CMDREG1),FM_IRMEMWO) ;
	CHECK_NPP() ;	/* needed क्रम PCI to prevent from समयing violations */
/*	p = MDRR() ; */	/* bad पढ़ो values अगर the workaround */
			/* smc->hw.mc_dummy = *((लघु अस्थिर far *)(addr)))*/
			/* is used */
	p = (u_दीर्घ)inpw(FM_A(FM_MDRU))<<16 ;
	p += (u_दीर्घ)inpw(FM_A(FM_MDRL)) ;
	वापस p;
पूर्ण
#पूर्ण_अगर

/*
 * clear buffer memory
 */
अटल व्योम init_ram(काष्ठा s_smc *smc)
अणु
	u_लघु i ;

	smc->hw.fp.fअगरo.rbc_ram_start = 0 ;
	smc->hw.fp.fअगरo.rbc_ram_end =
		smc->hw.fp.fअगरo.rbc_ram_start + RBC_MEM_SIZE ;
	CHECK_NPP() ;
	MARW(smc->hw.fp.fअगरo.rbc_ram_start) ;
	क्रम (i = smc->hw.fp.fअगरo.rbc_ram_start;
		i < (u_लघु) (smc->hw.fp.fअगरo.rbc_ram_end-1); i++)
		ग_लिखो_mdr(smc,0L) ;
	/* Erase the last byte too */
	ग_लिखो_mdr(smc,0L) ;
पूर्ण

/*
 * set receive FIFO poपूर्णांकer
 */
अटल व्योम set_recvptr(काष्ठा s_smc *smc)
अणु
	/*
	 * initialize the poपूर्णांकer क्रम receive queue 1
	 */
	outpw(FM_A(FM_RPR1),smc->hw.fp.fअगरo.rx1_fअगरo_start) ;	/* RPR1 */
	outpw(FM_A(FM_SWPR1),smc->hw.fp.fअगरo.rx1_fअगरo_start) ;	/* SWPR1 */
	outpw(FM_A(FM_WPR1),smc->hw.fp.fअगरo.rx1_fअगरo_start) ;	/* WPR1 */
	outpw(FM_A(FM_EARV1),smc->hw.fp.fअगरo.tx_s_start-1) ;	/* EARV1 */

	/*
	 * initialize the poपूर्णांकer क्रम receive queue 2
	 */
	अगर (smc->hw.fp.fअगरo.rx2_fअगरo_size) अणु
		outpw(FM_A(FM_RPR2),smc->hw.fp.fअगरo.rx2_fअगरo_start) ;
		outpw(FM_A(FM_SWPR2),smc->hw.fp.fअगरo.rx2_fअगरo_start) ;
		outpw(FM_A(FM_WPR2),smc->hw.fp.fअगरo.rx2_fअगरo_start) ;
		outpw(FM_A(FM_EARV2),smc->hw.fp.fअगरo.rbc_ram_end-1) ;
	पूर्ण
	अन्यथा अणु
		outpw(FM_A(FM_RPR2),smc->hw.fp.fअगरo.rbc_ram_end-1) ;
		outpw(FM_A(FM_SWPR2),smc->hw.fp.fअगरo.rbc_ram_end-1) ;
		outpw(FM_A(FM_WPR2),smc->hw.fp.fअगरo.rbc_ram_end-1) ;
		outpw(FM_A(FM_EARV2),smc->hw.fp.fअगरo.rbc_ram_end-1) ;
	पूर्ण
पूर्ण

/*
 * set transmit FIFO poपूर्णांकer
 */
अटल व्योम set_txptr(काष्ठा s_smc *smc)
अणु
	outpw(FM_A(FM_CMDREG2),FM_IRSTQ) ;	/* reset transmit queues */

	/*
	 * initialize the poपूर्णांकer क्रम asynchronous transmit queue
	 */
	outpw(FM_A(FM_RPXA0),smc->hw.fp.fअगरo.tx_a0_start) ;	/* RPXA0 */
	outpw(FM_A(FM_SWPXA0),smc->hw.fp.fअगरo.tx_a0_start) ;	/* SWPXA0 */
	outpw(FM_A(FM_WPXA0),smc->hw.fp.fअगरo.tx_a0_start) ;	/* WPXA0 */
	outpw(FM_A(FM_EAA0),smc->hw.fp.fअगरo.rx2_fअगरo_start-1) ;	/* EAA0 */

	/*
	 * initialize the poपूर्णांकer क्रम synchronous transmit queue
	 */
	अगर (smc->hw.fp.fअगरo.tx_s_size) अणु
		outpw(FM_A(FM_RPXS),smc->hw.fp.fअगरo.tx_s_start) ;
		outpw(FM_A(FM_SWPXS),smc->hw.fp.fअगरo.tx_s_start) ;
		outpw(FM_A(FM_WPXS),smc->hw.fp.fअगरo.tx_s_start) ;
		outpw(FM_A(FM_EAS),smc->hw.fp.fअगरo.tx_a0_start-1) ;
	पूर्ण
	अन्यथा अणु
		outpw(FM_A(FM_RPXS),smc->hw.fp.fअगरo.tx_a0_start-1) ;
		outpw(FM_A(FM_SWPXS),smc->hw.fp.fअगरo.tx_a0_start-1) ;
		outpw(FM_A(FM_WPXS),smc->hw.fp.fअगरo.tx_a0_start-1) ;
		outpw(FM_A(FM_EAS),smc->hw.fp.fअगरo.tx_a0_start-1) ;
	पूर्ण
पूर्ण

/*
 * init memory buffer management रेजिस्टरs
 */
अटल व्योम init_rbc(काष्ठा s_smc *smc)
अणु
	u_लघु	rbc_ram_addr ;

	/*
	 * set unused poपूर्णांकers or permanent poपूर्णांकers
	 */
	rbc_ram_addr = smc->hw.fp.fअगरo.rx2_fअगरo_start - 1 ;

	outpw(FM_A(FM_RPXA1),rbc_ram_addr) ;	/* a1-send poपूर्णांकer */
	outpw(FM_A(FM_WPXA1),rbc_ram_addr) ;
	outpw(FM_A(FM_SWPXA1),rbc_ram_addr) ;
	outpw(FM_A(FM_EAA1),rbc_ram_addr) ;

	set_recvptr(smc) ;
	set_txptr(smc) ;
पूर्ण

/*
 * init rx poपूर्णांकer
 */
अटल व्योम init_rx(काष्ठा s_smc *smc)
अणु
	काष्ठा s_smt_rx_queue	*queue ;

	/*
	 * init all tx data काष्ठाures क्रम receive queue 1
	 */
	smc->hw.fp.rx[QUEUE_R1] = queue = &smc->hw.fp.rx_q[QUEUE_R1] ;
	queue->rx_bmu_ctl = (HW_PTR) ADDR(B0_R1_CSR) ;
	queue->rx_bmu_dsc = (HW_PTR) ADDR(B4_R1_DA) ;

	/*
	 * init all tx data काष्ठाures क्रम receive queue 2
	 */
	smc->hw.fp.rx[QUEUE_R2] = queue = &smc->hw.fp.rx_q[QUEUE_R2] ;
	queue->rx_bmu_ctl = (HW_PTR) ADDR(B0_R2_CSR) ;
	queue->rx_bmu_dsc = (HW_PTR) ADDR(B4_R2_DA) ;
पूर्ण

/*
 * set the TSYNC रेजिस्टर of the FORMAC to regulate synchronous transmission
 */
व्योम set_क्रमmac_tsync(काष्ठा s_smc *smc, दीर्घ sync_bw)
अणु
	outpw(FM_A(FM_TSYNC),(अचिन्हित पूर्णांक) (((-sync_bw) >> 5) & 0xffff) ) ;
पूर्ण

/*
 * init all tx data काष्ठाures
 */
अटल व्योम init_tx(काष्ठा s_smc *smc)
अणु
	काष्ठा s_smt_tx_queue	*queue ;

	/*
	 * init all tx data काष्ठाures क्रम the synchronous queue
	 */
	smc->hw.fp.tx[QUEUE_S] = queue = &smc->hw.fp.tx_q[QUEUE_S] ;
	queue->tx_bmu_ctl = (HW_PTR) ADDR(B0_XS_CSR) ;
	queue->tx_bmu_dsc = (HW_PTR) ADDR(B5_XS_DA) ;

#अगर_घोषित ESS
	set_क्रमmac_tsync(smc,smc->ess.sync_bw) ;
#पूर्ण_अगर

	/*
	 * init all tx data काष्ठाures क्रम the asynchronous queue 0
	 */
	smc->hw.fp.tx[QUEUE_A0] = queue = &smc->hw.fp.tx_q[QUEUE_A0] ;
	queue->tx_bmu_ctl = (HW_PTR) ADDR(B0_XA_CSR) ;
	queue->tx_bmu_dsc = (HW_PTR) ADDR(B5_XA_DA) ;


	llc_recover_tx(smc) ;
पूर्ण

अटल व्योम mac_counter_init(काष्ठा s_smc *smc)
अणु
	पूर्णांक i ;
	u_दीर्घ *ec ;

	/*
	 * clear FORMAC+ frame-, lost- and error counter
	 */
	outpw(FM_A(FM_FCNTR),0) ;
	outpw(FM_A(FM_LCNTR),0) ;
	outpw(FM_A(FM_ECNTR),0) ;
	/*
	 * clear पूर्णांकernal error counter काष्ठाure
	 */
	ec = (u_दीर्घ *)&smc->hw.fp.err_stats ;
	क्रम (i = (माप(काष्ठा err_st)/माप(दीर्घ)) ; i ; i--)
		*ec++ = 0L ;
	smc->mib.m[MAC0].fddiMACRingOp_Ct = 0 ;
पूर्ण

/*
 * set FORMAC address, and t_request
 */
अटल	व्योम set_क्रमmac_addr(काष्ठा s_smc *smc)
अणु
	दीर्घ	t_requ = smc->mib.m[MAC0].fddiMACT_Req ;

	outpw(FM_A(FM_SAID),my_said) ;	/* set लघु address */
	outpw(FM_A(FM_LAIL),(अचिन्हित लघु)((smc->hw.fddi_home_addr.a[4]<<8) +
					smc->hw.fddi_home_addr.a[5])) ;
	outpw(FM_A(FM_LAIC),(अचिन्हित लघु)((smc->hw.fddi_home_addr.a[2]<<8) +
					smc->hw.fddi_home_addr.a[3])) ;
	outpw(FM_A(FM_LAIM),(अचिन्हित लघु)((smc->hw.fddi_home_addr.a[0]<<8) +
					smc->hw.fddi_home_addr.a[1])) ;

	outpw(FM_A(FM_SAGP),my_sagp) ;	/* set लघु group address */

	outpw(FM_A(FM_LAGL),(अचिन्हित लघु)((smc->hw.fp.group_addr.a[4]<<8) +
					smc->hw.fp.group_addr.a[5])) ;
	outpw(FM_A(FM_LAGC),(अचिन्हित लघु)((smc->hw.fp.group_addr.a[2]<<8) +
					smc->hw.fp.group_addr.a[3])) ;
	outpw(FM_A(FM_LAGM),(अचिन्हित लघु)((smc->hw.fp.group_addr.a[0]<<8) +
					smc->hw.fp.group_addr.a[1])) ;

	/* set r_request regs. (MSW & LSW of TRT ) */
	outpw(FM_A(FM_TREQ1),(अचिन्हित लघु)(t_requ>>16)) ;
	outpw(FM_A(FM_TREQ0),(अचिन्हित लघु)t_requ) ;
पूर्ण

अटल व्योम set_पूर्णांक(अक्षर *p, पूर्णांक l)
अणु
	p[0] = (अक्षर)(l >> 24) ;
	p[1] = (अक्षर)(l >> 16) ;
	p[2] = (अक्षर)(l >> 8) ;
	p[3] = (अक्षर)(l >> 0) ;
पूर्ण

/*
 * copy TX descriptor to buffer mem
 * append FC field and MAC frame
 * अगर more bit is set in descr
 *	append poपूर्णांकer to descriptor (endless loop)
 * अन्यथा
 *	append 'end of chain' poपूर्णांकer
 */
अटल व्योम copy_tx_mac(काष्ठा s_smc *smc, u_दीर्घ td, काष्ठा fddi_mac *mac,
			अचिन्हित पूर्णांक off, पूर्णांक len)
/* u_दीर्घ td;		 transmit descriptor */
/* काष्ठा fddi_mac *mac; mac frame poपूर्णांकer */
/* अचिन्हित पूर्णांक off;	 start address within buffer memory */
/* पूर्णांक len ;		 length of the frame including the FC */
अणु
	पूर्णांक	i ;
	__le32	*p ;

	CHECK_NPP() ;
	MARW(off) ;		/* set memory address reg क्रम ग_लिखोs */

	p = (__le32 *) mac ;
	क्रम (i = (len + 3)/4 ; i ; i--) अणु
		अगर (i == 1) अणु
			/* last word, set the tag bit */
			outpw(FM_A(FM_CMDREG2),FM_ISTTB) ;
		पूर्ण
		ग_लिखो_mdr(smc,le32_to_cpu(*p)) ;
		p++ ;
	पूर्ण

	outpw(FM_A(FM_CMDREG2),FM_ISTTB) ;	/* set the tag bit */
	ग_लिखो_mdr(smc,td) ;	/* ग_लिखो over memory data reg to buffer */
पूर्ण

/*
	BEGIN_MANUAL_ENTRY(module;tests;3)
	How to test directed beacon frames
	----------------------------------------------------------------

	o Insert a अवरोध poपूर्णांक in the function build_claim_beacon()
	  beक्रमe calling copy_tx_mac() क्रम building the claim frame.
	o Modअगरy the RM3_DETECT हाल so that the RM6_DETECT state
	  will always entered from the RM3_DETECT state (function rmt_fsm(),
	  rmt.c)
	o Compile the driver.
	o Set the parameter TREQ in the protocol.ini or net.cfg to a
	  small value to make sure your station will win the claim
	  process.
	o Start the driver.
	o When you reach the अवरोध poपूर्णांक, modअगरy the SA and DA address
	  of the claim frame (e.g. SA = DA = 10005affffff).
	o When you see RM3_DETECT and RM6_DETECT, observe the direct
	  beacon frames on the UPPSLANA.

	END_MANUAL_ENTRY
 */
अटल व्योम directed_beacon(काष्ठा s_smc *smc)
अणु
	SK_LOC_DECL(__le32,a[2]) ;

	/*
	 * set UNA in frame
	 * enable FORMAC to send endless queue of directed beacon
	 * important: the UNA starts at byte 1 (not at byte 0)
	 */
	* (अक्षर *) a = (अक्षर) ((दीर्घ)DBEACON_INFO<<24L) ;
	a[1] = 0 ;
	स_नकल((अक्षर *)a+1, (अक्षर *) &smc->mib.m[MAC0].fddiMACUpstreamNbr, ETH_ALEN);

	CHECK_NPP() ;
	 /* set memory address reg क्रम ग_लिखोs */
	MARW(smc->hw.fp.fअगरo.rbc_ram_start+DBEACON_FRAME_OFF+4) ;
	ग_लिखो_mdr(smc,le32_to_cpu(a[0])) ;
	outpw(FM_A(FM_CMDREG2),FM_ISTTB) ;	/* set the tag bit */
	ग_लिखो_mdr(smc,le32_to_cpu(a[1])) ;

	outpw(FM_A(FM_SABC),smc->hw.fp.fअगरo.rbc_ram_start + DBEACON_FRAME_OFF) ;
पूर्ण

/*
	setup claim & beacon poपूर्णांकer
	NOTE :
		special frame packets end with a poपूर्णांकer to their own
		descriptor, and the MORE bit is set in the descriptor
*/
अटल व्योम build_claim_beacon(काष्ठा s_smc *smc, u_दीर्घ t_request)
अणु
	u_पूर्णांक	td ;
	पूर्णांक	len ;
	काष्ठा fddi_mac_sf *mac ;

	/*
	 * build claim packet
	 */
	len = 17 ;
	td = TX_DESCRIPTOR | ((((u_पूर्णांक)len-1)&3)<<27) ;
	mac = &smc->hw.fp.mac_sfb ;
	mac->mac_fc = FC_CLAIM ;
	/* DA == SA in claim frame */
	mac->mac_source = mac->mac_dest = MA ;
	/* 2's complement */
	set_पूर्णांक((अक्षर *)mac->mac_info,(पूर्णांक)t_request) ;

	copy_tx_mac(smc,td,(काष्ठा fddi_mac *)mac,
		smc->hw.fp.fअगरo.rbc_ram_start + CLAIM_FRAME_OFF,len) ;
	/* set CLAIM start poपूर्णांकer */
	outpw(FM_A(FM_SACL),smc->hw.fp.fअगरo.rbc_ram_start + CLAIM_FRAME_OFF) ;

	/*
	 * build beacon packet
	 */
	len = 17 ;
	td = TX_DESCRIPTOR | ((((u_पूर्णांक)len-1)&3)<<27) ;
	mac->mac_fc = FC_BEACON ;
	mac->mac_source = MA ;
	mac->mac_dest = null_addr ;		/* DA == 0 in beacon frame */
	set_पूर्णांक((अक्षर *) mac->mac_info,((पूर्णांक)BEACON_INFO<<24) + 0 ) ;

	copy_tx_mac(smc,td,(काष्ठा fddi_mac *)mac,
		smc->hw.fp.fअगरo.rbc_ram_start + BEACON_FRAME_OFF,len) ;
	/* set beacon start poपूर्णांकer */
	outpw(FM_A(FM_SABC),smc->hw.fp.fअगरo.rbc_ram_start + BEACON_FRAME_OFF) ;

	/*
	 * build directed beacon packet
	 * contains optional UNA
	 */
	len = 23 ;
	td = TX_DESCRIPTOR | ((((u_पूर्णांक)len-1)&3)<<27) ;
	mac->mac_fc = FC_BEACON ;
	mac->mac_source = MA ;
	mac->mac_dest = dbeacon_multi ;		/* multicast */
	set_पूर्णांक((अक्षर *) mac->mac_info,((पूर्णांक)DBEACON_INFO<<24) + 0 ) ;
	set_पूर्णांक((अक्षर *) mac->mac_info+4,0) ;
	set_पूर्णांक((अक्षर *) mac->mac_info+8,0) ;

	copy_tx_mac(smc,td,(काष्ठा fddi_mac *)mac,
		smc->hw.fp.fअगरo.rbc_ram_start + DBEACON_FRAME_OFF,len) ;

	/* end of claim/beacon queue */
	outpw(FM_A(FM_EACB),smc->hw.fp.fअगरo.rx1_fअगरo_start-1) ;

	outpw(FM_A(FM_WPXSF),0) ;
	outpw(FM_A(FM_RPXSF),0) ;
पूर्ण

अटल व्योम क्रमmac_rcv_restart(काष्ठा s_smc *smc)
अणु
	/* enable receive function */
	SETMASK(FM_A(FM_MDREG1),smc->hw.fp.rx_mode,FM_ADDRX) ;

	outpw(FM_A(FM_CMDREG1),FM_ICLLR) ;	/* clear receive lock */
पूर्ण

व्योम क्रमmac_tx_restart(काष्ठा s_smc *smc)
अणु
	outpw(FM_A(FM_CMDREG1),FM_ICLLS) ;	/* clear s-frame lock */
	outpw(FM_A(FM_CMDREG1),FM_ICLLA0) ;	/* clear a-frame lock */
पूर्ण

अटल व्योम enable_क्रमmac(काष्ठा s_smc *smc)
अणु
	/* set क्रमmac IMSK : 0 enables irq */
	outpw(FM_A(FM_IMSK1U),(अचिन्हित लघु)~mac_imsk1u);
	outpw(FM_A(FM_IMSK1L),(अचिन्हित लघु)~mac_imsk1l);
	outpw(FM_A(FM_IMSK2U),(अचिन्हित लघु)~mac_imsk2u);
	outpw(FM_A(FM_IMSK2L),(अचिन्हित लघु)~mac_imsk2l);
	outpw(FM_A(FM_IMSK3U),(अचिन्हित लघु)~mac_imsk3u);
	outpw(FM_A(FM_IMSK3L),(अचिन्हित लघु)~mac_imsk3l);
पूर्ण

#अगर 0	/* Removed because the driver should use the ASICs TX complete IRQ. */
	/* The FORMACs tx complete IRQ should be used any दीर्घer */

/*
	BEGIN_MANUAL_ENTRY(अगर,func;others;4)

	व्योम enable_tx_irq(smc, queue)
	काष्ठा s_smc *smc ;
	u_लघु	queue ;

Function	DOWNCALL	(SMT, fplusपंचांग.c)
		enable_tx_irq() enables the FORMACs transmit complete
		पूर्णांकerrupt of the queue.

Para	queue	= QUEUE_S:	synchronous queue
		= QUEUE_A0:	asynchronous queue

Note	After any ring operational change the transmit complete
	पूर्णांकerrupts are disabled.
	The operating प्रणाली dependent module must enable
	the transmit complete पूर्णांकerrupt of a queue,
		- when it queues the first frame,
		  because of no transmit resources are beeing
		  available and
		- when it escapes from the function llc_restart_tx
		  जबतक some frames are still queued.

	END_MANUAL_ENTRY
 */
व्योम enable_tx_irq(काष्ठा s_smc *smc, u_लघु queue)
/* u_लघु queue; 0 = synchronous queue, 1 = asynchronous queue 0 */
अणु
	u_लघु	imask ;

	imask = ~(inpw(FM_A(FM_IMSK1U))) ;

	अगर (queue == 0) अणु
		outpw(FM_A(FM_IMSK1U),~(imask|FM_STEFRMS)) ;
	पूर्ण
	अगर (queue == 1) अणु
		outpw(FM_A(FM_IMSK1U),~(imask|FM_STEFRMA0)) ;
	पूर्ण
पूर्ण

/*
	BEGIN_MANUAL_ENTRY(अगर,func;others;4)

	व्योम disable_tx_irq(smc, queue)
	काष्ठा s_smc *smc ;
	u_लघु	queue ;

Function	DOWNCALL	(SMT, fplusपंचांग.c)
		disable_tx_irq disables the FORMACs transmit complete
		पूर्णांकerrupt of the queue

Para	queue	= QUEUE_S:	synchronous queue
		= QUEUE_A0:	asynchronous queue

Note	The operating प्रणाली dependent module should disable
	the transmit complete पूर्णांकerrupts अगर it escapes from the
	function llc_restart_tx and no frames are queued.

	END_MANUAL_ENTRY
 */
व्योम disable_tx_irq(काष्ठा s_smc *smc, u_लघु queue)
/* u_लघु queue; 0 = synchronous queue, 1 = asynchronous queue 0 */
अणु
	u_लघु	imask ;

	imask = ~(inpw(FM_A(FM_IMSK1U))) ;

	अगर (queue == 0) अणु
		outpw(FM_A(FM_IMSK1U),~(imask&~FM_STEFRMS)) ;
	पूर्ण
	अगर (queue == 1) अणु
		outpw(FM_A(FM_IMSK1U),~(imask&~FM_STEFRMA0)) ;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम disable_क्रमmac(काष्ठा s_smc *smc)
अणु
	/* clear क्रमmac IMSK : 1 disables irq */
	outpw(FM_A(FM_IMSK1U),MW) ;
	outpw(FM_A(FM_IMSK1L),MW) ;
	outpw(FM_A(FM_IMSK2U),MW) ;
	outpw(FM_A(FM_IMSK2L),MW) ;
	outpw(FM_A(FM_IMSK3U),MW) ;
	outpw(FM_A(FM_IMSK3L),MW) ;
पूर्ण


अटल व्योम mac_ring_up(काष्ठा s_smc *smc, पूर्णांक up)
अणु
	अगर (up) अणु
		क्रमmac_rcv_restart(smc) ;	/* enable receive function */
		smc->hw.mac_ring_is_up = TRUE ;
		llc_restart_tx(smc) ;		/* TX queue */
	पूर्ण
	अन्यथा अणु
		/* disable receive function */
		SETMASK(FM_A(FM_MDREG1),FM_MDISRCV,FM_ADDET) ;

		/* पात current transmit activity */
		outpw(FM_A(FM_CMDREG2),FM_IACTR) ;

		smc->hw.mac_ring_is_up = FALSE ;
	पूर्ण
पूर्ण

/*--------------------------- ISR handling ----------------------------------*/
/*
 * mac1_irq is in drvfbi.c
 */

/*
 * mac2_irq:	status bits क्रम the receive queue 1, and ring status
 * 		ring status indication bits
 */
व्योम mac2_irq(काष्ठा s_smc *smc, u_लघु code_s2u, u_लघु code_s2l)
अणु
	u_लघु	change_s2l ;
	u_लघु	change_s2u ;

	/* (jd) 22-Feb-1999
	 * Restart 2_DMax Timer after end of claiming or beaconing
	 */
	अगर (code_s2u & (FM_SCLM|FM_SHICLM|FM_SBEC|FM_SOTRBEC)) अणु
		queue_event(smc,EVENT_RMT,RM_TX_STATE_CHANGE) ;
	पूर्ण
	अन्यथा अगर (code_s2l & (FM_STKISS)) अणु
		queue_event(smc,EVENT_RMT,RM_TX_STATE_CHANGE) ;
	पूर्ण

	/*
	 * XOR current st bits with the last to aव्योम useless RMT event queuing
	 */
	change_s2l = smc->hw.fp.s2l ^ code_s2l ;
	change_s2u = smc->hw.fp.s2u ^ code_s2u ;

	अगर ((change_s2l & FM_SRNGOP) ||
		(!smc->hw.mac_ring_is_up && ((code_s2l & FM_SRNGOP)))) अणु
		अगर (code_s2l & FM_SRNGOP) अणु
			mac_ring_up(smc,1) ;
			queue_event(smc,EVENT_RMT,RM_RING_OP) ;
			smc->mib.m[MAC0].fddiMACRingOp_Ct++ ;
		पूर्ण
		अन्यथा अणु
			mac_ring_up(smc,0) ;
			queue_event(smc,EVENT_RMT,RM_RING_NON_OP) ;
		पूर्ण
		जाओ mac2_end ;
	पूर्ण
	अगर (code_s2l & FM_SMISFRM) अणु	/* missed frame */
		smc->mib.m[MAC0].fddiMACNotCopied_Ct++ ;
	पूर्ण
	अगर (code_s2u & (FM_SRCVOVR |	/* recv. FIFO overflow */
			FM_SRBFL)) अणु	/* recv. buffer full */
		smc->hw.mac_ct.mac_r_restart_counter++ ;
/*		क्रमmac_rcv_restart(smc) ;	*/
		smt_stat_counter(smc,1) ;
/*		जाओ mac2_end ;			*/
	पूर्ण
	अगर (code_s2u & FM_SOTRBEC)
		queue_event(smc,EVENT_RMT,RM_OTHER_BEACON) ;
	अगर (code_s2u & FM_SMYBEC)
		queue_event(smc,EVENT_RMT,RM_MY_BEACON) ;
	अगर (change_s2u & code_s2u & FM_SLOCLM) अणु
		DB_RMTN(2, "RMT : lower claim received");
	पूर्ण
	अगर ((code_s2u & FM_SMYCLM) && !(code_s2l & FM_SDUPCLM)) अणु
		/*
		 * This is my claim and that claim is not detected as a
		 * duplicate one.
		 */
		queue_event(smc,EVENT_RMT,RM_MY_CLAIM) ;
	पूर्ण
	अगर (code_s2l & FM_SDUPCLM) अणु
		/*
		 * If a duplicate claim frame (same SA but T_Bid != T_Req)
		 * this flag will be set.
		 * In the RMT state machine we need a RM_VALID_CLAIM event
		 * to करो the appropriate state change.
		 * RM(34c)
		 */
		queue_event(smc,EVENT_RMT,RM_VALID_CLAIM) ;
	पूर्ण
	अगर (change_s2u & code_s2u & FM_SHICLM) अणु
		DB_RMTN(2, "RMT : higher claim received");
	पूर्ण
	अगर ( (code_s2l & FM_STRTEXP) ||
	     (code_s2l & FM_STRTEXR) )
		queue_event(smc,EVENT_RMT,RM_TRT_EXP) ;
	अगर (code_s2l & FM_SMULTDA) अणु
		/*
		 * The MAC has found a 2. MAC with the same address.
		 * Signal dup_addr_test = failed to RMT state machine.
		 * RM(25)
		 */
		smc->r.dup_addr_test = DA_FAILED ;
		queue_event(smc,EVENT_RMT,RM_DUP_ADDR) ;
	पूर्ण
	अगर (code_s2u & FM_SBEC)
		smc->hw.fp.err_stats.err_bec_stat++ ;
	अगर (code_s2u & FM_SCLM)
		smc->hw.fp.err_stats.err_clm_stat++ ;
	अगर (code_s2l & FM_STVXEXP)
		smc->mib.m[MAC0].fddiMACTvxExpired_Ct++ ;
	अगर ((code_s2u & (FM_SBEC|FM_SCLM))) अणु
		अगर (!(change_s2l & FM_SRNGOP) && (smc->hw.fp.s2l & FM_SRNGOP)) अणु
			mac_ring_up(smc,0) ;
			queue_event(smc,EVENT_RMT,RM_RING_NON_OP) ;

			mac_ring_up(smc,1) ;
			queue_event(smc,EVENT_RMT,RM_RING_OP) ;
			smc->mib.m[MAC0].fddiMACRingOp_Ct++ ;
		पूर्ण
	पूर्ण
	अगर (code_s2l & FM_SPHINV)
		smc->hw.fp.err_stats.err_phinv++ ;
	अगर (code_s2l & FM_SSIFG)
		smc->hw.fp.err_stats.err_sअगरg_det++ ;
	अगर (code_s2l & FM_STKISS)
		smc->hw.fp.err_stats.err_tkiss++ ;
	अगर (code_s2l & FM_STKERR)
		smc->hw.fp.err_stats.err_tkerr++ ;
	अगर (code_s2l & FM_SFRMCTR)
		smc->mib.m[MAC0].fddiMACFrame_Ct += 0x10000L ;
	अगर (code_s2l & FM_SERRCTR)
		smc->mib.m[MAC0].fddiMACError_Ct += 0x10000L ;
	अगर (code_s2l & FM_SLSTCTR)
		smc->mib.m[MAC0].fddiMACLost_Ct  += 0x10000L ;
	अगर (code_s2u & FM_SERRSF) अणु
		SMT_PANIC(smc,SMT_E0114, SMT_E0114_MSG) ;
	पूर्ण
mac2_end:
	/* notice old status */
	smc->hw.fp.s2l = code_s2l ;
	smc->hw.fp.s2u = code_s2u ;
	outpw(FM_A(FM_IMSK2U),~mac_imsk2u) ;
पूर्ण

/*
 * mac3_irq:	receive queue 2 bits and address detection bits
 */
व्योम mac3_irq(काष्ठा s_smc *smc, u_लघु code_s3u, u_लघु code_s3l)
अणु
	UNUSED(code_s3l) ;

	अगर (code_s3u & (FM_SRCVOVR2 |	/* recv. FIFO overflow */
			FM_SRBFL2)) अणु	/* recv. buffer full */
		smc->hw.mac_ct.mac_r_restart_counter++ ;
		smt_stat_counter(smc,1);
	पूर्ण


	अगर (code_s3u & FM_SRPERRQ2) अणु	/* parity error receive queue 2 */
		SMT_PANIC(smc,SMT_E0115, SMT_E0115_MSG) ;
	पूर्ण
	अगर (code_s3u & FM_SRPERRQ1) अणु	/* parity error receive queue 2 */
		SMT_PANIC(smc,SMT_E0116, SMT_E0116_MSG) ;
	पूर्ण
पूर्ण


/*
 * take क्रमmac offline
 */
अटल व्योम क्रमmac_offline(काष्ठा s_smc *smc)
अणु
	outpw(FM_A(FM_CMDREG2),FM_IACTR) ;/* पात current transmit activity */

	/* disable receive function */
	SETMASK(FM_A(FM_MDREG1),FM_MDISRCV,FM_ADDET) ;

	/* FORMAC+ 'Initialize Mode' */
	SETMASK(FM_A(FM_MDREG1),FM_MINIT,FM_MMODE) ;

	disable_क्रमmac(smc) ;
	smc->hw.mac_ring_is_up = FALSE ;
	smc->hw.hw_state = STOPPED ;
पूर्ण

/*
 * bring क्रमmac online
 */
अटल व्योम क्रमmac_online(काष्ठा s_smc *smc)
अणु
	enable_क्रमmac(smc) ;
	SETMASK(FM_A(FM_MDREG1),FM_MONLINE | FM_SELRA | MDR1INIT |
		smc->hw.fp.rx_mode, FM_MMODE | FM_SELRA | FM_ADDRX) ;
पूर्ण

/*
 * FORMAC+ full init. (tx, rx, समयr, counter, claim & beacon)
 */
पूर्णांक init_fplus(काष्ठा s_smc *smc)
अणु
	smc->hw.fp.nsa_mode = FM_MRNNSAFNMA ;
	smc->hw.fp.rx_mode = FM_MDAMA ;
	smc->hw.fp.group_addr = fddi_broadcast ;
	smc->hw.fp.func_addr = 0 ;
	smc->hw.fp.frselreg_init = 0 ;

	init_driver_fplus(smc) ;
	अगर (smc->s.sas == SMT_DAS)
		smc->hw.fp.mdr3init |= FM_MENDAS ;

	smc->hw.mac_ct.mac_nobuf_counter = 0 ;
	smc->hw.mac_ct.mac_r_restart_counter = 0 ;

	smc->hw.fp.fm_st1u = (HW_PTR) ADDR(B0_ST1U) ;
	smc->hw.fp.fm_st1l = (HW_PTR) ADDR(B0_ST1L) ;
	smc->hw.fp.fm_st2u = (HW_PTR) ADDR(B0_ST2U) ;
	smc->hw.fp.fm_st2l = (HW_PTR) ADDR(B0_ST2L) ;
	smc->hw.fp.fm_st3u = (HW_PTR) ADDR(B0_ST3U) ;
	smc->hw.fp.fm_st3l = (HW_PTR) ADDR(B0_ST3L) ;

	smc->hw.fp.s2l = smc->hw.fp.s2u = 0 ;
	smc->hw.mac_ring_is_up = 0 ;

	mac_counter_init(smc) ;

	/* convert BCKL units to symbol समय */
	smc->hw.mac_pa.t_neg = (u_दीर्घ)0 ;
	smc->hw.mac_pa.t_pri = (u_दीर्घ)0 ;

	/* make sure all PCI settings are correct */
	mac_करो_pci_fix(smc) ;

	वापस init_mac(smc, 1);
	/* enable_क्रमmac(smc) ; */
पूर्ण

अटल पूर्णांक init_mac(काष्ठा s_smc *smc, पूर्णांक all)
अणु
	u_लघु	t_max,x ;
	u_दीर्घ	समय=0 ;

	/*
	 * clear memory
	 */
	outpw(FM_A(FM_MDREG1),FM_MINIT) ;	/* FORMAC+ init mode */
	set_क्रमmac_addr(smc) ;
	outpw(FM_A(FM_MDREG1),FM_MMEMACT) ;	/* FORMAC+ memory activ mode */
	/* Note: Mode रेजिस्टर 2 is set here, inहाल parity is enabled. */
	outpw(FM_A(FM_MDREG2),smc->hw.fp.mdr2init) ;

	अगर (all) अणु
		init_ram(smc) ;
	पूर्ण
	अन्यथा अणु
		/*
		 * reset the HPI, the Master and the BMUs
		 */
		outp(ADDR(B0_CTRL), CTRL_HPI_SET) ;
		समय = hwt_quick_पढ़ो(smc) ;
	पूर्ण

	/*
	 * set all poपूर्णांकers, frames etc
	 */
	smt_split_up_fअगरo(smc) ;

	init_tx(smc) ;
	init_rx(smc) ;
	init_rbc(smc) ;

	build_claim_beacon(smc,smc->mib.m[MAC0].fddiMACT_Req) ;

	/* set RX threshold */
	/* see Errata #SN2 Phantom receive overflow */
	outpw(FM_A(FM_FRMTHR),14<<12) ;		/* चयन on */

	/* set क्रमmac work mode */
	outpw(FM_A(FM_MDREG1),MDR1INIT | FM_SELRA | smc->hw.fp.rx_mode) ;
	outpw(FM_A(FM_MDREG2),smc->hw.fp.mdr2init) ;
	outpw(FM_A(FM_MDREG3),smc->hw.fp.mdr3init) ;
	outpw(FM_A(FM_FRSELREG),smc->hw.fp.frselreg_init) ;

	/* set समयr */
	/*
	 * errata #22 fplus:
	 * T_MAX must not be FFFE
	 * or one of FFDF, FFB8, FF91 (-0x27 etc..)
	 */
	t_max = (u_लघु)(smc->mib.m[MAC0].fddiMACT_Max/32) ;
	x = t_max/0x27 ;
	x *= 0x27 ;
	अगर ((t_max == 0xfffe) || (t_max - x == 0x16))
		t_max-- ;
	outpw(FM_A(FM_TMAX),(u_लघु)t_max) ;

	/* BugFix क्रम report #10204 */
	अगर (smc->mib.m[MAC0].fddiMACTvxValue < (u_दीर्घ) (- US2BCLK(52))) अणु
		outpw(FM_A(FM_TVX), (u_लघु) (- US2BCLK(52))/255 & MB) ;
	पूर्ण अन्यथा अणु
		outpw(FM_A(FM_TVX),
			(u_लघु)((smc->mib.m[MAC0].fddiMACTvxValue/255) & MB)) ;
	पूर्ण

	outpw(FM_A(FM_CMDREG1),FM_ICLLS) ;	/* clear s-frame lock */
	outpw(FM_A(FM_CMDREG1),FM_ICLLA0) ;	/* clear a-frame lock */
	outpw(FM_A(FM_CMDREG1),FM_ICLLR);	/* clear receive lock */

	/* Auto unlock receice threshold क्रम receive queue 1 and 2 */
	outpw(FM_A(FM_UNLCKDLY),(0xff|(0xff<<8))) ;

	rपंचांग_init(smc) ;				/* RT-Monitor */

	अगर (!all) अणु
		/*
		 * after 10ms, reset the BMUs and repair the rings
		 */
		hwt_रुको_समय(smc,समय,MS2BCLK(10)) ;
		outpd(ADDR(B0_R1_CSR),CSR_SET_RESET) ;
		outpd(ADDR(B0_XA_CSR),CSR_SET_RESET) ;
		outpd(ADDR(B0_XS_CSR),CSR_SET_RESET) ;
		outp(ADDR(B0_CTRL), CTRL_HPI_CLR) ;
		outpd(ADDR(B0_R1_CSR),CSR_CLR_RESET) ;
		outpd(ADDR(B0_XA_CSR),CSR_CLR_RESET) ;
		outpd(ADDR(B0_XS_CSR),CSR_CLR_RESET) ;
		अगर (!smc->hw.hw_is_64bit) अणु
			outpd(ADDR(B4_R1_F), RX_WATERMARK) ;
			outpd(ADDR(B5_XA_F), TX_WATERMARK) ;
			outpd(ADDR(B5_XS_F), TX_WATERMARK) ;
		पूर्ण
		smc->hw.hw_state = STOPPED ;
		mac_drv_repair_descr(smc) ;
	पूर्ण
	smc->hw.hw_state = STARTED ;

	वापस 0;
पूर्ण


/*
 * called by CFM
 */
व्योम config_mux(काष्ठा s_smc *smc, पूर्णांक mux)
अणु
	plc_config_mux(smc,mux) ;

	SETMASK(FM_A(FM_MDREG1),FM_SELRA,FM_SELRA) ;
पूर्ण

/*
 * called by RMT
 * enable CLAIM/BEACON पूर्णांकerrupts
 * (only called अगर these events are of पूर्णांकerest, e.g. in DETECT state
 * the पूर्णांकerrupt must not be permanently enabled
 * RMT calls this function periodically (समयr driven polling)
 */
व्योम sm_mac_check_beacon_claim(काष्ठा s_smc *smc)
अणु
	/* set क्रमmac IMSK : 0 enables irq */
	outpw(FM_A(FM_IMSK2U),~(mac_imsk2u | mac_beacon_imsk2u)) ;
	/* the driver must receive the directed beacons */
	क्रमmac_rcv_restart(smc) ;
	process_receive(smc) ;
पूर्ण

/*-------------------------- पूर्णांकerface functions ----------------------------*/
/*
 * control MAC layer	(called by RMT)
 */
व्योम sm_ma_control(काष्ठा s_smc *smc, पूर्णांक mode)
अणु
	चयन(mode) अणु
	हाल MA_OFFLINE :
		/* Add to make the MAC offline in RM0_ISOLATED state */
		क्रमmac_offline(smc) ;
		अवरोध ;
	हाल MA_RESET :
		(व्योम)init_mac(smc,0) ;
		अवरोध ;
	हाल MA_BEACON :
		क्रमmac_online(smc) ;
		अवरोध ;
	हाल MA_सूचीECTED :
		directed_beacon(smc) ;
		अवरोध ;
	हाल MA_TREQ :
		/*
		 * no actions necessary, TREQ is alपढ़ोy set
		 */
		अवरोध ;
	पूर्ण
पूर्ण

पूर्णांक sm_mac_get_tx_state(काष्ठा s_smc *smc)
अणु
	वापस (inpw(FM_A(FM_STMCHN))>>4) & 7;
पूर्ण

/*
 * multicast functions
 */

अटल काष्ठा s_fpmc* mac_get_mc_table(काष्ठा s_smc *smc,
				       काष्ठा fddi_addr *user,
				       काष्ठा fddi_addr *own,
				       पूर्णांक del, पूर्णांक can)
अणु
	काष्ठा s_fpmc	*tb ;
	काष्ठा s_fpmc	*slot ;
	u_अक्षर	*p ;
	पूर्णांक i ;

	/*
	 * set own = can(user)
	 */
	*own = *user ;
	अगर (can) अणु
		p = own->a ;
		क्रम (i = 0 ; i < 6 ; i++, p++)
			*p = bitrev8(*p);
	पूर्ण
	slot = शून्य;
	क्रम (i = 0, tb = smc->hw.fp.mc.table ; i < FPMAX_MULTICAST ; i++, tb++)अणु
		अगर (!tb->n) अणु		/* not used */
			अगर (!del && !slot)	/* अगर !del save first मुक्त */
				slot = tb ;
			जारी ;
		पूर्ण
		अगर (!ether_addr_equal((अक्षर *)&tb->a, (अक्षर *)own))
			जारी ;
		वापस tb;
	पूर्ण
	वापस slot;			/* वापस first मुक्त or शून्य */
पूर्ण

/*
	BEGIN_MANUAL_ENTRY(अगर,func;others;2)

	व्योम mac_clear_multicast(smc)
	काष्ठा s_smc *smc ;

Function	DOWNCALL	(SMT, fplusपंचांग.c)
		Clear all multicast entries

	END_MANUAL_ENTRY()
 */
व्योम mac_clear_multicast(काष्ठा s_smc *smc)
अणु
	काष्ठा s_fpmc	*tb ;
	पूर्णांक i ;

	smc->hw.fp.os_slots_used = 0 ;	/* note the SMT addresses */
					/* will not be deleted */
	क्रम (i = 0, tb = smc->hw.fp.mc.table ; i < FPMAX_MULTICAST ; i++, tb++)अणु
		अगर (!tb->perm) अणु
			tb->n = 0 ;
		पूर्ण
	पूर्ण
पूर्ण

/*
	BEGIN_MANUAL_ENTRY(अगर,func;others;2)

	पूर्णांक mac_add_multicast(smc,addr,can)
	काष्ठा s_smc *smc ;
	काष्ठा fddi_addr *addr ;
	पूर्णांक can ;

Function	DOWNCALL	(SMC, fplusपंचांग.c)
		Add an entry to the multicast table

Para	addr	poपूर्णांकer to a multicast address
	can	= 0:	the multicast address has the physical क्रमmat
		= 1:	the multicast address has the canonical क्रमmat
		| 0x80	permanent

Returns	0: success
	1: address table full

Note	After a 'driver reset' or a 'station set address' all
	entries of the multicast table are cleared.
	In this हाल the driver has to fill the multicast table again.
	After the operating प्रणाली dependent module filled
	the multicast table it must call mac_update_multicast
	to activate the new multicast addresses!

	END_MANUAL_ENTRY()
 */
पूर्णांक mac_add_multicast(काष्ठा s_smc *smc, काष्ठा fddi_addr *addr, पूर्णांक can)
अणु
	SK_LOC_DECL(काष्ठा fddi_addr,own) ;
	काष्ठा s_fpmc	*tb ;

	/*
	 * check अगर there are मुक्त table entries
	 */
	अगर (can & 0x80) अणु
		अगर (smc->hw.fp.smt_slots_used >= SMT_MAX_MULTI) अणु
			वापस 1;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		अगर (smc->hw.fp.os_slots_used >= FPMAX_MULTICAST-SMT_MAX_MULTI) अणु
			वापस 1;
		पूर्ण
	पूर्ण

	/*
	 * find empty slot
	 */
	अगर (!(tb = mac_get_mc_table(smc,addr,&own,0,can & ~0x80)))
		वापस 1;
	tb->n++ ;
	tb->a = own ;
	tb->perm = (can & 0x80) ? 1 : 0 ;

	अगर (can & 0x80)
		smc->hw.fp.smt_slots_used++ ;
	अन्यथा
		smc->hw.fp.os_slots_used++ ;

	वापस 0;
पूर्ण

/*
 * mode
 */

#घोषणा RX_MODE_PROM		0x1
#घोषणा RX_MODE_ALL_MULTI	0x2

/*
	BEGIN_MANUAL_ENTRY(अगर,func;others;2)

	व्योम mac_update_multicast(smc)
	काष्ठा s_smc *smc ;

Function	DOWNCALL	(SMT, fplusपंचांग.c)
		Update FORMAC multicast रेजिस्टरs

	END_MANUAL_ENTRY()
 */
व्योम mac_update_multicast(काष्ठा s_smc *smc)
अणु
	काष्ठा s_fpmc	*tb ;
	u_अक्षर	*fu ;
	पूर्णांक	i ;

	/*
	 * invalidate the CAM
	 */
	outpw(FM_A(FM_AFCMD),FM_IINV_CAM) ;

	/*
	 * set the functional address
	 */
	अगर (smc->hw.fp.func_addr) अणु
		fu = (u_अक्षर *) &smc->hw.fp.func_addr ;
		outpw(FM_A(FM_AFMASK2),0xffff) ;
		outpw(FM_A(FM_AFMASK1),(u_लघु) ~((fu[0] << 8) + fu[1])) ;
		outpw(FM_A(FM_AFMASK0),(u_लघु) ~((fu[2] << 8) + fu[3])) ;
		outpw(FM_A(FM_AFPERS),FM_VALID|FM_DA) ;
		outpw(FM_A(FM_AFCOMP2), 0xc000) ;
		outpw(FM_A(FM_AFCOMP1), 0x0000) ;
		outpw(FM_A(FM_AFCOMP0), 0x0000) ;
		outpw(FM_A(FM_AFCMD),FM_IWRITE_CAM) ;
	पूर्ण

	/*
	 * set the mask and the personality रेजिस्टर(s)
	 */
	outpw(FM_A(FM_AFMASK0),0xffff) ;
	outpw(FM_A(FM_AFMASK1),0xffff) ;
	outpw(FM_A(FM_AFMASK2),0xffff) ;
	outpw(FM_A(FM_AFPERS),FM_VALID|FM_DA) ;

	क्रम (i = 0, tb = smc->hw.fp.mc.table; i < FPMAX_MULTICAST; i++, tb++) अणु
		अगर (tb->n) अणु
			CHECK_CAM() ;

			/*
			 * ग_लिखो the multicast address पूर्णांकo the CAM
			 */
			outpw(FM_A(FM_AFCOMP2),
				(u_लघु)((tb->a.a[0]<<8)+tb->a.a[1])) ;
			outpw(FM_A(FM_AFCOMP1),
				(u_लघु)((tb->a.a[2]<<8)+tb->a.a[3])) ;
			outpw(FM_A(FM_AFCOMP0),
				(u_लघु)((tb->a.a[4]<<8)+tb->a.a[5])) ;
			outpw(FM_A(FM_AFCMD),FM_IWRITE_CAM) ;
		पूर्ण
	पूर्ण
पूर्ण

/*
	BEGIN_MANUAL_ENTRY(अगर,func;others;3)

	व्योम mac_set_rx_mode(smc,mode)
	काष्ठा s_smc *smc ;
	पूर्णांक mode ;

Function	DOWNCALL/INTERN	(SMT, fplusपंचांग.c)
		This function enables / disables the selected receive.
		Don't call this function अगर the hardware module is
		used -- use mac_drv_rx_mode() instead of.

Para	mode =	1	RX_ENABLE_ALLMULTI	enable all multicasts
		2	RX_DISABLE_ALLMULTI	disable "enable all multicasts"
		3	RX_ENABLE_PROMISC	enable promiscuous
		4	RX_DISABLE_PROMISC	disable promiscuous
		5	RX_ENABLE_NSA		enable reception of NSA frames
		6	RX_DISABLE_NSA		disable reception of NSA frames

Note	The selected receive modes will be lost after 'driver reset'
	or 'set station address'

	END_MANUAL_ENTRY
 */
व्योम mac_set_rx_mode(काष्ठा s_smc *smc, पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल RX_ENABLE_ALLMULTI :
		smc->hw.fp.rx_prom |= RX_MODE_ALL_MULTI ;
		अवरोध ;
	हाल RX_DISABLE_ALLMULTI :
		smc->hw.fp.rx_prom &= ~RX_MODE_ALL_MULTI ;
		अवरोध ;
	हाल RX_ENABLE_PROMISC :
		smc->hw.fp.rx_prom |= RX_MODE_PROM ;
		अवरोध ;
	हाल RX_DISABLE_PROMISC :
		smc->hw.fp.rx_prom &= ~RX_MODE_PROM ;
		अवरोध ;
	हाल RX_ENABLE_NSA :
		smc->hw.fp.nsa_mode = FM_MDAMA ;
		smc->hw.fp.rx_mode = (smc->hw.fp.rx_mode & ~FM_ADDET) |
			smc->hw.fp.nsa_mode ;
		अवरोध ;
	हाल RX_DISABLE_NSA :
		smc->hw.fp.nsa_mode = FM_MRNNSAFNMA ;
		smc->hw.fp.rx_mode = (smc->hw.fp.rx_mode & ~FM_ADDET) |
			smc->hw.fp.nsa_mode ;
		अवरोध ;
	पूर्ण
	अगर (smc->hw.fp.rx_prom & RX_MODE_PROM) अणु
		smc->hw.fp.rx_mode = FM_MLIMPROM ;
	पूर्ण
	अन्यथा अगर (smc->hw.fp.rx_prom & RX_MODE_ALL_MULTI) अणु
		smc->hw.fp.rx_mode = smc->hw.fp.nsa_mode | FM_EXGPA0 ;
	पूर्ण
	अन्यथा
		smc->hw.fp.rx_mode = smc->hw.fp.nsa_mode ;
	SETMASK(FM_A(FM_MDREG1),smc->hw.fp.rx_mode,FM_ADDRX) ;
	mac_update_multicast(smc) ;
पूर्ण

/*
	BEGIN_MANUAL_ENTRY(module;tests;3)
	How to test the Restricted Token Monitor
	----------------------------------------------------------------

	o Insert a अवरोध poपूर्णांक in the function rपंचांग_irq()
	o Remove all stations with a restricted token monitor from the
	  network.
	o Connect a UPPS ISA or EISA station to the network.
	o Give the FORMAC of UPPS station the command to send
	  restricted tokens until the ring becomes instable.
	o Now connect your test test client.
	o The restricted token monitor should detect the restricted token,
	  and your अवरोध poपूर्णांक will be reached.
	o You can ovserve how the station will clean the ring.

	END_MANUAL_ENTRY
 */
व्योम rपंचांग_irq(काष्ठा s_smc *smc)
अणु
	outpw(ADDR(B2_RTM_CRTL),TIM_CL_IRQ) ;		/* clear IRQ */
	अगर (inpw(ADDR(B2_RTM_CRTL)) & TIM_RES_TOK) अणु
		outpw(FM_A(FM_CMDREG1),FM_ICL) ;	/* क्रमce claim */
		DB_RMT("RMT: fddiPATHT_Rmode expired");
		AIX_EVENT(smc, (u_दीर्घ) FDDI_RING_STATUS,
				(u_दीर्घ) FDDI_SMT_EVENT,
				(u_दीर्घ) FDDI_RTT, smt_get_event_word(smc));
	पूर्ण
	outpw(ADDR(B2_RTM_CRTL),TIM_START) ;	/* enable RTM monitoring */
पूर्ण

अटल व्योम rपंचांग_init(काष्ठा s_smc *smc)
अणु
	outpd(ADDR(B2_RTM_INI),0) ;		/* समयr = 0 */
	outpw(ADDR(B2_RTM_CRTL),TIM_START) ;	/* enable IRQ */
पूर्ण

व्योम rपंचांग_set_समयr(काष्ठा s_smc *smc)
अणु
	/*
	 * MIB समयr and hardware समयr have the same resolution of 80nS
	 */
	DB_RMT("RMT: setting new fddiPATHT_Rmode, t = %d ns",
	       (पूर्णांक)smc->mib.a[PATH0].fddiPATHT_Rmode);
	outpd(ADDR(B2_RTM_INI),smc->mib.a[PATH0].fddiPATHT_Rmode) ;
पूर्ण

अटल व्योम smt_split_up_fअगरo(काष्ठा s_smc *smc)
अणु

/*
	BEGIN_MANUAL_ENTRY(module;mem;1)
	-------------------------------------------------------------
	RECEIVE BUFFER MEMORY DIVERSION
	-------------------------------------------------------------

	R1_RxD == SMT_R1_RXD_COUNT
	R2_RxD == SMT_R2_RXD_COUNT

	SMT_R1_RXD_COUNT must be unequal zero

		   | R1_RxD R2_RxD |R1_RxD R2_RxD | R1_RxD R2_RxD
		   |   x      0	   |  x	    1-3	  |   x     < 3
	----------------------------------------------------------------------
		   |   63,75 kB	   |    54,75	  |	R1_RxD
	rx queue 1 | RX_FIFO_SPACE | RX_LARGE_FIFO| ------------- * 63,75 kB
		   |		   |		  | R1_RxD+R2_RxD
	----------------------------------------------------------------------
		   |		   |    9 kB	  |     R2_RxD
	rx queue 2 |	0 kB	   | RX_SMALL_FIFO| ------------- * 63,75 kB
		   |  (not used)   |		  | R1_RxD+R2_RxD

	END_MANUAL_ENTRY
*/

	अगर (SMT_R1_RXD_COUNT == 0) अणु
		SMT_PANIC(smc,SMT_E0117, SMT_E0117_MSG) ;
	पूर्ण

	चयन(SMT_R2_RXD_COUNT) अणु
	हाल 0:
		smc->hw.fp.fअगरo.rx1_fअगरo_size = RX_FIFO_SPACE ;
		smc->hw.fp.fअगरo.rx2_fअगरo_size = 0 ;
		अवरोध ;
	हाल 1:
	हाल 2:
	हाल 3:
		smc->hw.fp.fअगरo.rx1_fअगरo_size = RX_LARGE_FIFO ;
		smc->hw.fp.fअगरo.rx2_fअगरo_size = RX_SMALL_FIFO ;
		अवरोध ;
	शेष:	/* this is not the real defaule */
		smc->hw.fp.fअगरo.rx1_fअगरo_size = RX_FIFO_SPACE *
		SMT_R1_RXD_COUNT/(SMT_R1_RXD_COUNT+SMT_R2_RXD_COUNT) ;
		smc->hw.fp.fअगरo.rx2_fअगरo_size = RX_FIFO_SPACE *
		SMT_R2_RXD_COUNT/(SMT_R1_RXD_COUNT+SMT_R2_RXD_COUNT) ;
		अवरोध ;
	पूर्ण

/*
	BEGIN_MANUAL_ENTRY(module;mem;1)
	-------------------------------------------------------------
	TRANSMIT BUFFER MEMORY DIVERSION
	-------------------------------------------------------------


		 | no sync bw	| sync bw available and | sync bw available and
		 | available	| SynchTxMode = SPLIT	| SynchTxMode = ALL
	-----------------------------------------------------------------------
	sync tx	 |     0 kB	|	32 kB		|	55 kB
	queue	 |		|   TX_MEDIUM_FIFO	|   TX_LARGE_FIFO
	-----------------------------------------------------------------------
	async tx |    64 kB	|	32 kB		|	 9 k
	queue	 | TX_FIFO_SPACE|   TX_MEDIUM_FIFO	|   TX_SMALL_FIFO

	END_MANUAL_ENTRY
*/

	/*
	 * set the tx mode bits
	 */
	अगर (smc->mib.a[PATH0].fddiPATHSbaPayload) अणु
#अगर_घोषित ESS
		smc->hw.fp.fअगरo.fअगरo_config_mode |=
			smc->mib.fddiESSSynchTxMode | SYNC_TRAFFIC_ON ;
#पूर्ण_अगर
	पूर्ण
	अन्यथा अणु
		smc->hw.fp.fअगरo.fअगरo_config_mode &=
			~(SEND_ASYNC_AS_SYNC|SYNC_TRAFFIC_ON) ;
	पूर्ण

	/*
	 * split up the FIFO
	 */
	अगर (smc->hw.fp.fअगरo.fअगरo_config_mode & SYNC_TRAFFIC_ON) अणु
		अगर (smc->hw.fp.fअगरo.fअगरo_config_mode & SEND_ASYNC_AS_SYNC) अणु
			smc->hw.fp.fअगरo.tx_s_size = TX_LARGE_FIFO ;
			smc->hw.fp.fअगरo.tx_a0_size = TX_SMALL_FIFO ;
		पूर्ण
		अन्यथा अणु
			smc->hw.fp.fअगरo.tx_s_size = TX_MEDIUM_FIFO ;
			smc->hw.fp.fअगरo.tx_a0_size = TX_MEDIUM_FIFO ;
		पूर्ण
	पूर्ण
	अन्यथा अणु
			smc->hw.fp.fअगरo.tx_s_size = 0 ;
			smc->hw.fp.fअगरo.tx_a0_size = TX_FIFO_SPACE ;
	पूर्ण

	smc->hw.fp.fअगरo.rx1_fअगरo_start = smc->hw.fp.fअगरo.rbc_ram_start +
		RX_FIFO_OFF ;
	smc->hw.fp.fअगरo.tx_s_start = smc->hw.fp.fअगरo.rx1_fअगरo_start +
		smc->hw.fp.fअगरo.rx1_fअगरo_size ;
	smc->hw.fp.fअगरo.tx_a0_start = smc->hw.fp.fअगरo.tx_s_start +
		smc->hw.fp.fअगरo.tx_s_size ;
	smc->hw.fp.fअगरo.rx2_fअगरo_start = smc->hw.fp.fअगरo.tx_a0_start +
		smc->hw.fp.fअगरo.tx_a0_size ;

	DB_SMT("FIFO split: mode = %x", smc->hw.fp.fअगरo.fअगरo_config_mode);
	DB_SMT("rbc_ram_start =	%x	 rbc_ram_end = 	%x",
	       smc->hw.fp.fअगरo.rbc_ram_start, smc->hw.fp.fअगरo.rbc_ram_end);
	DB_SMT("rx1_fifo_start = %x	 tx_s_start = 	%x",
	       smc->hw.fp.fअगरo.rx1_fअगरo_start, smc->hw.fp.fअगरo.tx_s_start);
	DB_SMT("tx_a0_start =	%x	 rx2_fifo_start = 	%x",
	       smc->hw.fp.fअगरo.tx_a0_start, smc->hw.fp.fअगरo.rx2_fअगरo_start);
पूर्ण

व्योम क्रमmac_reinit_tx(काष्ठा s_smc *smc)
अणु
	/*
	 * Split up the FIFO and reinitialize the MAC अगर synchronous
	 * bandwidth becomes available but no synchronous queue is
	 * configured.
	 */
	अगर (!smc->hw.fp.fअगरo.tx_s_size && smc->mib.a[PATH0].fddiPATHSbaPayload)अणु
		(व्योम)init_mac(smc,0) ;
	पूर्ण
पूर्ण

