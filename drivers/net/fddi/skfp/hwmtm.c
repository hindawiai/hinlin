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

#घोषणा	HWMTM

#अगर_अघोषित FDDI
#घोषणा	FDDI
#पूर्ण_अगर

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"
#समावेश "h/supern_2.h"
#समावेश "h/skfbiinc.h"

/*
	-------------------------------------------------------------
	DOCUMENTATION
	-------------------------------------------------------------
	BEGIN_MANUAL_ENTRY(DOCUMENTATION)

			T B D

	END_MANUAL_ENTRY
*/
/*
	-------------------------------------------------------------
	LOCAL VARIABLES:
	-------------------------------------------------------------
*/
#अगर_घोषित COMMON_MB_POOL
अटल	SMbuf *mb_start = 0 ;
अटल	SMbuf *mb_मुक्त = 0 ;
अटल	पूर्णांक mb_init = FALSE ;
अटल	पूर्णांक call_count = 0 ;
#पूर्ण_अगर

/*
	-------------------------------------------------------------
	EXTERNE VARIABLES:
	-------------------------------------------------------------
*/

#अगर_घोषित	DEBUG
#अगर_अघोषित	DEBUG_BRD
बाह्य	काष्ठा smt_debug	debug ;
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित	NDIS_OS2
बाह्य	u_अक्षर	offDepth ;
बाह्य	u_अक्षर	क्रमce_irq_pending ;
#पूर्ण_अगर

/*
	-------------------------------------------------------------
	LOCAL FUNCTIONS:
	-------------------------------------------------------------
*/

अटल व्योम queue_llc_rx(काष्ठा s_smc *smc, SMbuf *mb);
अटल व्योम smt_to_llc(काष्ठा s_smc *smc, SMbuf *mb);
अटल व्योम init_txd_ring(काष्ठा s_smc *smc);
अटल व्योम init_rxd_ring(काष्ठा s_smc *smc);
अटल व्योम queue_txd_mb(काष्ठा s_smc *smc, SMbuf *mb);
अटल u_दीर्घ init_descr_ring(काष्ठा s_smc *smc, जोड़ s_fp_descr अस्थिर *start,
			      पूर्णांक count);
अटल u_दीर्घ repair_txd_ring(काष्ठा s_smc *smc, काष्ठा s_smt_tx_queue *queue);
अटल u_दीर्घ repair_rxd_ring(काष्ठा s_smc *smc, काष्ठा s_smt_rx_queue *queue);
अटल SMbuf* get_llc_rx(काष्ठा s_smc *smc);
अटल SMbuf* get_txd_mb(काष्ठा s_smc *smc);
अटल व्योम mac_drv_clear_txd(काष्ठा s_smc *smc);

/*
	-------------------------------------------------------------
	EXTERNAL FUNCTIONS:
	-------------------------------------------------------------
*/
/*	The बाह्यal SMT functions are listed in cmtdef.h */

बाह्य व्योम* mac_drv_get_space(काष्ठा s_smc *smc, अचिन्हित पूर्णांक size);
बाह्य व्योम* mac_drv_get_desc_mem(काष्ठा s_smc *smc, अचिन्हित पूर्णांक size);
बाह्य व्योम mac_drv_fill_rxd(काष्ठा s_smc *smc);
बाह्य व्योम mac_drv_tx_complete(काष्ठा s_smc *smc,
				अस्थिर काष्ठा s_smt_fp_txd *txd);
बाह्य व्योम mac_drv_rx_complete(काष्ठा s_smc *smc,
				अस्थिर काष्ठा s_smt_fp_rxd *rxd,
				पूर्णांक frag_count, पूर्णांक len);
बाह्य व्योम mac_drv_requeue_rxd(काष्ठा s_smc *smc, 
				अस्थिर काष्ठा s_smt_fp_rxd *rxd,
				पूर्णांक frag_count);
बाह्य व्योम mac_drv_clear_rxd(काष्ठा s_smc *smc,
			      अस्थिर काष्ठा s_smt_fp_rxd *rxd, पूर्णांक frag_count);

#अगर_घोषित	USE_OS_CPY
बाह्य व्योम hwm_cpy_rxd2mb(व्योम);
बाह्य व्योम hwm_cpy_txd2mb(व्योम);
#पूर्ण_अगर

#अगर_घोषित	ALL_RX_COMPLETE
बाह्य व्योम mac_drv_all_receives_complete(व्योम);
#पूर्ण_अगर

बाह्य u_दीर्घ mac_drv_virt2phys(काष्ठा s_smc *smc, व्योम *virt);
बाह्य u_दीर्घ dma_master(काष्ठा s_smc *smc, व्योम *virt, पूर्णांक len, पूर्णांक flag);

#अगर_घोषित	NDIS_OS2
बाह्य व्योम post_proc(व्योम);
#अन्यथा
बाह्य व्योम dma_complete(काष्ठा s_smc *smc, अस्थिर जोड़ s_fp_descr *descr,
			 पूर्णांक flag);
#पूर्ण_अगर

बाह्य पूर्णांक mac_drv_rx_init(काष्ठा s_smc *smc, पूर्णांक len, पूर्णांक fc, अक्षर *look_ahead,
			   पूर्णांक la_len);

/*
	-------------------------------------------------------------
	PUBLIC FUNCTIONS:
	-------------------------------------------------------------
*/
व्योम process_receive(काष्ठा s_smc *smc);
व्योम fddi_isr(काष्ठा s_smc *smc);
व्योम smt_मुक्त_mbuf(काष्ठा s_smc *smc, SMbuf *mb);
व्योम init_driver_fplus(काष्ठा s_smc *smc);
व्योम mac_drv_rx_mode(काष्ठा s_smc *smc, पूर्णांक mode);
व्योम init_fddi_driver(काष्ठा s_smc *smc, u_अक्षर *mac_addr);
व्योम mac_drv_clear_tx_queue(काष्ठा s_smc *smc);
व्योम mac_drv_clear_rx_queue(काष्ठा s_smc *smc);
व्योम hwm_tx_frag(काष्ठा s_smc *smc, अक्षर far *virt, u_दीर्घ phys, पूर्णांक len,
		 पूर्णांक frame_status);
व्योम hwm_rx_frag(काष्ठा s_smc *smc, अक्षर far *virt, u_दीर्घ phys, पूर्णांक len,
		 पूर्णांक frame_status);

पूर्णांक mac_drv_init(काष्ठा s_smc *smc);
पूर्णांक hwm_tx_init(काष्ठा s_smc *smc, u_अक्षर fc, पूर्णांक frag_count, पूर्णांक frame_len,
		पूर्णांक frame_status);

u_पूर्णांक mac_drv_check_space(व्योम);

SMbuf* smt_get_mbuf(काष्ठा s_smc *smc);

#अगर_घोषित DEBUG
	व्योम mac_drv_debug_lev(काष्ठा s_smc *smc, पूर्णांक flag, पूर्णांक lev);
#पूर्ण_अगर

/*
	-------------------------------------------------------------
	MACROS:
	-------------------------------------------------------------
*/
#अगर_अघोषित	UNUSED
#अगर_घोषित	lपूर्णांक
#घोषणा UNUSED(x)	(x) = (x)
#अन्यथा
#घोषणा UNUSED(x)
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित	USE_CAN_ADDR
#घोषणा MA		smc->hw.fddi_canon_addr.a
#घोषणा	GROUP_ADDR_BIT	0x01
#अन्यथा
#घोषणा	MA		smc->hw.fddi_home_addr.a
#घोषणा	GROUP_ADDR_BIT	0x80
#पूर्ण_अगर

#घोषणा RXD_TXD_COUNT	(HWM_ASYNC_TXD_COUNT+HWM_SYNC_TXD_COUNT+\
			SMT_R1_RXD_COUNT+SMT_R2_RXD_COUNT)

#अगर_घोषित	MB_OUTSIDE_SMC
#घोषणा	EXT_VIRT_MEM	((RXD_TXD_COUNT+1)*माप(काष्ठा s_smt_fp_txd) +\
			MAX_MBUF*माप(SMbuf))
#घोषणा	EXT_VIRT_MEM_2	((RXD_TXD_COUNT+1)*माप(काष्ठा s_smt_fp_txd))
#अन्यथा
#घोषणा	EXT_VIRT_MEM	((RXD_TXD_COUNT+1)*माप(काष्ठा s_smt_fp_txd))
#पूर्ण_अगर

	/*
	 * define critical पढ़ो क्रम 16 Bit drivers
	 */
#अगर	defined(NDIS_OS2) || defined(ODI2)
#घोषणा CR_READ(var)	((var) & 0xffff0000 | ((var) & 0xffff))
#अन्यथा
#घोषणा CR_READ(var)	(__le32)(var)
#पूर्ण_अगर

#घोषणा IMASK_SLOW	(IS_PLINT1 | IS_PLINT2 | IS_TIMINT | IS_TOKEN | \
			 IS_MINTR1 | IS_MINTR2 | IS_MINTR3 | IS_R1_P | \
			 IS_R1_C | IS_XA_C | IS_XS_C)

/*
	-------------------------------------------------------------
	INIT- AND SMT FUNCTIONS:
	-------------------------------------------------------------
*/


/*
 *	BEGIN_MANUAL_ENTRY(mac_drv_check_space)
 *	u_पूर्णांक mac_drv_check_space()
 *
 *	function	DOWNCALL	(drvsr.c)
 *			This function calculates the needed non भव
 *			memory क्रम MBufs, RxD and TxD descriptors etc.
 *			needed by the driver.
 *
 *	वापस		u_पूर्णांक	memory in bytes
 *
 *	END_MANUAL_ENTRY
 */
u_पूर्णांक mac_drv_check_space(व्योम)
अणु
#अगर_घोषित	MB_OUTSIDE_SMC
#अगर_घोषित	COMMON_MB_POOL
	call_count++ ;
	अगर (call_count == 1) अणु
		वापस EXT_VIRT_MEM;
	पूर्ण
	अन्यथा अणु
		वापस EXT_VIRT_MEM_2;
	पूर्ण
#अन्यथा
	वापस EXT_VIRT_MEM;
#पूर्ण_अगर
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 *	BEGIN_MANUAL_ENTRY(mac_drv_init)
 *	व्योम mac_drv_init(smc)
 *
 *	function	DOWNCALL	(drvsr.c)
 *			In this function the hardware module allocates it's
 *			memory.
 *			The operating प्रणाली dependent module should call
 *			mac_drv_init once, after the adatper is detected.
 *	END_MANUAL_ENTRY
 */
पूर्णांक mac_drv_init(काष्ठा s_smc *smc)
अणु
	अगर (माप(काष्ठा s_smt_fp_rxd) % 16) अणु
		SMT_PANIC(smc,HWM_E0001,HWM_E0001_MSG) ;
	पूर्ण
	अगर (माप(काष्ठा s_smt_fp_txd) % 16) अणु
		SMT_PANIC(smc,HWM_E0002,HWM_E0002_MSG) ;
	पूर्ण

	/*
	 * get the required memory क्रम the RxDs and TxDs
	 */
	अगर (!(smc->os.hwm.descr_p = (जोड़ s_fp_descr अस्थिर *)
		mac_drv_get_desc_mem(smc,(u_पूर्णांक)
		(RXD_TXD_COUNT+1)*माप(काष्ठा s_smt_fp_txd)))) अणु
		वापस 1;	/* no space the hwm modul can't work */
	पूर्ण

	/*
	 * get the memory क्रम the SMT MBufs
	 */
#अगर_अघोषित	MB_OUTSIDE_SMC
	smc->os.hwm.mbuf_pool.mb_start=(SMbuf *)(&smc->os.hwm.mbuf_pool.mb[0]) ;
#अन्यथा
#अगर_अघोषित	COMMON_MB_POOL
	अगर (!(smc->os.hwm.mbuf_pool.mb_start = (SMbuf *) mac_drv_get_space(smc,
		MAX_MBUF*माप(SMbuf)))) अणु
		वापस 1;	/* no space the hwm modul can't work */
	पूर्ण
#अन्यथा
	अगर (!mb_start) अणु
		अगर (!(mb_start = (SMbuf *) mac_drv_get_space(smc,
			MAX_MBUF*माप(SMbuf)))) अणु
			वापस 1;	/* no space the hwm modul can't work */
		पूर्ण
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 *	BEGIN_MANUAL_ENTRY(init_driver_fplus)
 *	init_driver_fplus(smc)
 *
 * Sets hardware modul specअगरic values क्रम the mode रेजिस्टर 2
 * (e.g. the byte alignment क्रम the received frames, the position of the
 *	 least signअगरicant byte etc.)
 *	END_MANUAL_ENTRY
 */
व्योम init_driver_fplus(काष्ठा s_smc *smc)
अणु
	smc->hw.fp.mdr2init = FM_LSB | FM_BMMODE | FM_ENNPRQ | FM_ENHSRQ | 3 ;

#अगर_घोषित	PCI
	smc->hw.fp.mdr2init |= FM_CHKPAR | FM_PARITY ;
#पूर्ण_अगर
	smc->hw.fp.mdr3init = FM_MENRQAUNLCK | FM_MENRS ;

#अगर_घोषित	USE_CAN_ADDR
	/* enable address bit swapping */
	smc->hw.fp.frselreg_init = FM_ENXMTADSWAP | FM_ENRCVADSWAP ;
#पूर्ण_अगर
पूर्ण

अटल u_दीर्घ init_descr_ring(काष्ठा s_smc *smc,
			      जोड़ s_fp_descr अस्थिर *start,
			      पूर्णांक count)
अणु
	पूर्णांक i ;
	जोड़ s_fp_descr अस्थिर *d1 ;
	जोड़ s_fp_descr अस्थिर *d2 ;
	u_दीर्घ	phys ;

	DB_GEN(3, "descr ring starts at = %p", start);
	क्रम (i=count-1, d1=start; i ; i--) अणु
		d2 = d1 ;
		d1++ ;		/* descr is owned by the host */
		d2->r.rxd_rbctrl = cpu_to_le32(BMU_CHECK) ;
		d2->r.rxd_next = &d1->r ;
		phys = mac_drv_virt2phys(smc,(व्योम *)d1) ;
		d2->r.rxd_nrdadr = cpu_to_le32(phys) ;
	पूर्ण
	DB_GEN(3, "descr ring ends at = %p", d1);
	d1->r.rxd_rbctrl = cpu_to_le32(BMU_CHECK) ;
	d1->r.rxd_next = &start->r ;
	phys = mac_drv_virt2phys(smc,(व्योम *)start) ;
	d1->r.rxd_nrdadr = cpu_to_le32(phys) ;

	क्रम (i=count, d1=start; i ; i--) अणु
		DRV_BUF_FLUSH(&d1->r,DDI_DMA_SYNC_FORDEV) ;
		d1++;
	पूर्ण
	वापस phys;
पूर्ण

अटल व्योम init_txd_ring(काष्ठा s_smc *smc)
अणु
	काष्ठा s_smt_fp_txd अस्थिर *ds ;
	काष्ठा s_smt_tx_queue *queue ;
	u_दीर्घ	phys ;

	/*
	 * initialize the transmit descriptors
	 */
	ds = (काष्ठा s_smt_fp_txd अस्थिर *) ((अक्षर *)smc->os.hwm.descr_p +
		SMT_R1_RXD_COUNT*माप(काष्ठा s_smt_fp_rxd)) ;
	queue = smc->hw.fp.tx[QUEUE_A0] ;
	DB_GEN(3, "Init async TxD ring, %d TxDs", HWM_ASYNC_TXD_COUNT);
	(व्योम)init_descr_ring(smc,(जोड़ s_fp_descr अस्थिर *)ds,
		HWM_ASYNC_TXD_COUNT) ;
	phys = le32_to_cpu(ds->txd_ntdadr) ;
	ds++ ;
	queue->tx_curr_put = queue->tx_curr_get = ds ;
	ds-- ;
	queue->tx_मुक्त = HWM_ASYNC_TXD_COUNT ;
	queue->tx_used = 0 ;
	outpd(ADDR(B5_XA_DA),phys) ;

	ds = (काष्ठा s_smt_fp_txd अस्थिर *) ((अक्षर *)ds +
		HWM_ASYNC_TXD_COUNT*माप(काष्ठा s_smt_fp_txd)) ;
	queue = smc->hw.fp.tx[QUEUE_S] ;
	DB_GEN(3, "Init sync TxD ring, %d TxDs", HWM_SYNC_TXD_COUNT);
	(व्योम)init_descr_ring(smc,(जोड़ s_fp_descr अस्थिर *)ds,
		HWM_SYNC_TXD_COUNT) ;
	phys = le32_to_cpu(ds->txd_ntdadr) ;
	ds++ ;
	queue->tx_curr_put = queue->tx_curr_get = ds ;
	queue->tx_मुक्त = HWM_SYNC_TXD_COUNT ;
	queue->tx_used = 0 ;
	outpd(ADDR(B5_XS_DA),phys) ;
पूर्ण

अटल व्योम init_rxd_ring(काष्ठा s_smc *smc)
अणु
	काष्ठा s_smt_fp_rxd अस्थिर *ds ;
	काष्ठा s_smt_rx_queue *queue ;
	u_दीर्घ	phys ;

	/*
	 * initialize the receive descriptors
	 */
	ds = (काष्ठा s_smt_fp_rxd अस्थिर *) smc->os.hwm.descr_p ;
	queue = smc->hw.fp.rx[QUEUE_R1] ;
	DB_GEN(3, "Init RxD ring, %d RxDs", SMT_R1_RXD_COUNT);
	(व्योम)init_descr_ring(smc,(जोड़ s_fp_descr अस्थिर *)ds,
		SMT_R1_RXD_COUNT) ;
	phys = le32_to_cpu(ds->rxd_nrdadr) ;
	ds++ ;
	queue->rx_curr_put = queue->rx_curr_get = ds ;
	queue->rx_मुक्त = SMT_R1_RXD_COUNT ;
	queue->rx_used = 0 ;
	outpd(ADDR(B4_R1_DA),phys) ;
पूर्ण

/*
 *	BEGIN_MANUAL_ENTRY(init_fddi_driver)
 *	व्योम init_fddi_driver(smc,mac_addr)
 *
 * initializes the driver and it's variables
 *
 *	END_MANUAL_ENTRY
 */
व्योम init_fddi_driver(काष्ठा s_smc *smc, u_अक्षर *mac_addr)
अणु
	SMbuf	*mb ;
	पूर्णांक	i ;

	init_board(smc,mac_addr) ;
	(व्योम)init_fplus(smc) ;

	/*
	 * initialize the SMbufs क्रम the SMT
	 */
#अगर_अघोषित	COMMON_MB_POOL
	mb = smc->os.hwm.mbuf_pool.mb_start ;
	smc->os.hwm.mbuf_pool.mb_मुक्त = (SMbuf *)शून्य ;
	क्रम (i = 0; i < MAX_MBUF; i++) अणु
		mb->sm_use_count = 1 ;
		smt_मुक्त_mbuf(smc,mb)	;
		mb++ ;
	पूर्ण
#अन्यथा
	mb = mb_start ;
	अगर (!mb_init) अणु
		mb_मुक्त = 0 ;
		क्रम (i = 0; i < MAX_MBUF; i++) अणु
			mb->sm_use_count = 1 ;
			smt_मुक्त_mbuf(smc,mb)	;
			mb++ ;
		पूर्ण
		mb_init = TRUE ;
	पूर्ण
#पूर्ण_अगर

	/*
	 * initialize the other variables
	 */
	smc->os.hwm.llc_rx_pipe = smc->os.hwm.llc_rx_tail = (SMbuf *)शून्य ;
	smc->os.hwm.txd_tx_pipe = smc->os.hwm.txd_tx_tail = शून्य ;
	smc->os.hwm.pass_SMT = smc->os.hwm.pass_NSA = smc->os.hwm.pass_DB = 0 ;
	smc->os.hwm.pass_llc_promisc = TRUE ;
	smc->os.hwm.queued_rx_frames = smc->os.hwm.queued_txd_mb = 0 ;
	smc->os.hwm.detec_count = 0 ;
	smc->os.hwm.rx_अवरोध = 0 ;
	smc->os.hwm.rx_len_error = 0 ;
	smc->os.hwm.isr_flag = FALSE ;

	/*
	 * make sure that the start poपूर्णांकer is 16 byte aligned
	 */
	i = 16 - ((दीर्घ)smc->os.hwm.descr_p & 0xf) ;
	अगर (i != 16) अणु
		DB_GEN(3, "i = %d", i);
		smc->os.hwm.descr_p = (जोड़ s_fp_descr अस्थिर *)
			((अक्षर *)smc->os.hwm.descr_p+i) ;
	पूर्ण
	DB_GEN(3, "pt to descr area = %p", smc->os.hwm.descr_p);

	init_txd_ring(smc) ;
	init_rxd_ring(smc) ;
	mac_drv_fill_rxd(smc) ;

	init_plc(smc) ;
पूर्ण


SMbuf *smt_get_mbuf(काष्ठा s_smc *smc)
अणु
	रेजिस्टर SMbuf	*mb ;

#अगर_अघोषित	COMMON_MB_POOL
	mb = smc->os.hwm.mbuf_pool.mb_मुक्त ;
#अन्यथा
	mb = mb_मुक्त ;
#पूर्ण_अगर
	अगर (mb) अणु
#अगर_अघोषित	COMMON_MB_POOL
		smc->os.hwm.mbuf_pool.mb_मुक्त = mb->sm_next ;
#अन्यथा
		mb_मुक्त = mb->sm_next ;
#पूर्ण_अगर
		mb->sm_off = 8 ;
		mb->sm_use_count = 1 ;
	पूर्ण
	DB_GEN(3, "get SMbuf: mb = %p", mb);
	वापस mb;	/* May be शून्य */
पूर्ण

व्योम smt_मुक्त_mbuf(काष्ठा s_smc *smc, SMbuf *mb)
अणु

	अगर (mb) अणु
		mb->sm_use_count-- ;
		DB_GEN(3, "free_mbuf: sm_use_count = %d", mb->sm_use_count);
		/*
		 * If the use_count is != zero the MBuf is queued
		 * more than once and must not queued पूर्णांकo the
		 * मुक्त MBuf queue
		 */
		अगर (!mb->sm_use_count) अणु
			DB_GEN(3, "free SMbuf: mb = %p", mb);
#अगर_अघोषित	COMMON_MB_POOL
			mb->sm_next = smc->os.hwm.mbuf_pool.mb_मुक्त ;
			smc->os.hwm.mbuf_pool.mb_मुक्त = mb ;
#अन्यथा
			mb->sm_next = mb_मुक्त ;
			mb_मुक्त = mb ;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	अन्यथा
		SMT_PANIC(smc,HWM_E0003,HWM_E0003_MSG) ;
पूर्ण


/*
 *	BEGIN_MANUAL_ENTRY(mac_drv_repair_descr)
 *	व्योम mac_drv_repair_descr(smc)
 *
 * function	called from SMT	(HWM / hwmपंचांग.c)
 *		The BMU is idle when this function is called.
 *		Mac_drv_repair_descr sets up the physical address
 *		क्रम all receive and transmit queues where the BMU
 *		should जारी.
 *		It may be that the BMU was reseted during a fragmented
 *		transfer. In this हाल there are some fragments which will
 *		never completed by the BMU. The OWN bit of this fragments
 *		must be चयनed to be owned by the host.
 *
 *		Give a start command to the receive BMU.
 *		Start the transmit BMUs अगर transmit frames pending.
 *
 *	END_MANUAL_ENTRY
 */
व्योम mac_drv_repair_descr(काष्ठा s_smc *smc)
अणु
	u_दीर्घ	phys ;

	अगर (smc->hw.hw_state != STOPPED) अणु
		SK_BREAK() ;
		SMT_PANIC(smc,HWM_E0013,HWM_E0013_MSG) ;
		वापस ;
	पूर्ण

	/*
	 * repair tx queues: करोn't start
	 */
	phys = repair_txd_ring(smc,smc->hw.fp.tx[QUEUE_A0]) ;
	outpd(ADDR(B5_XA_DA),phys) ;
	अगर (smc->hw.fp.tx_q[QUEUE_A0].tx_used) अणु
		outpd(ADDR(B0_XA_CSR),CSR_START) ;
	पूर्ण
	phys = repair_txd_ring(smc,smc->hw.fp.tx[QUEUE_S]) ;
	outpd(ADDR(B5_XS_DA),phys) ;
	अगर (smc->hw.fp.tx_q[QUEUE_S].tx_used) अणु
		outpd(ADDR(B0_XS_CSR),CSR_START) ;
	पूर्ण

	/*
	 * repair rx queues
	 */
	phys = repair_rxd_ring(smc,smc->hw.fp.rx[QUEUE_R1]) ;
	outpd(ADDR(B4_R1_DA),phys) ;
	outpd(ADDR(B0_R1_CSR),CSR_START) ;
पूर्ण

अटल u_दीर्घ repair_txd_ring(काष्ठा s_smc *smc, काष्ठा s_smt_tx_queue *queue)
अणु
	पूर्णांक i ;
	पूर्णांक tx_used ;
	u_दीर्घ phys ;
	u_दीर्घ tbctrl ;
	काष्ठा s_smt_fp_txd अस्थिर *t ;

	SK_UNUSED(smc) ;

	t = queue->tx_curr_get ;
	tx_used = queue->tx_used ;
	क्रम (i = tx_used+queue->tx_मुक्त-1 ; i ; i-- ) अणु
		t = t->txd_next ;
	पूर्ण
	phys = le32_to_cpu(t->txd_ntdadr) ;

	t = queue->tx_curr_get ;
	जबतक (tx_used) अणु
		DRV_BUF_FLUSH(t,DDI_DMA_SYNC_FORCPU) ;
		tbctrl = le32_to_cpu(t->txd_tbctrl) ;

		अगर (tbctrl & BMU_OWN) अणु
			अगर (tbctrl & BMU_STF) अणु
				अवरोध ;		/* निकास the loop */
			पूर्ण
			अन्यथा अणु
				/*
				 * repair the descriptor
				 */
				t->txd_tbctrl &= ~cpu_to_le32(BMU_OWN) ;
			पूर्ण
		पूर्ण
		phys = le32_to_cpu(t->txd_ntdadr) ;
		DRV_BUF_FLUSH(t,DDI_DMA_SYNC_FORDEV) ;
		t = t->txd_next ;
		tx_used-- ;
	पूर्ण
	वापस phys;
पूर्ण

/*
 * Repairs the receive descriptor ring and वापसs the physical address
 * where the BMU should जारी working.
 *
 *	o The physical address where the BMU was stopped has to be
 *	  determined. This is the next RxD after rx_curr_get with an OWN
 *	  bit set.
 *	o The BMU should start working at beginning of the next frame.
 *	  RxDs with an OWN bit set but with a reset STF bit should be
 *	  skipped and owned by the driver (OWN = 0). 
 */
अटल u_दीर्घ repair_rxd_ring(काष्ठा s_smc *smc, काष्ठा s_smt_rx_queue *queue)
अणु
	पूर्णांक i ;
	पूर्णांक rx_used ;
	u_दीर्घ phys ;
	u_दीर्घ rbctrl ;
	काष्ठा s_smt_fp_rxd अस्थिर *r ;

	SK_UNUSED(smc) ;

	r = queue->rx_curr_get ;
	rx_used = queue->rx_used ;
	क्रम (i = SMT_R1_RXD_COUNT-1 ; i ; i-- ) अणु
		r = r->rxd_next ;
	पूर्ण
	phys = le32_to_cpu(r->rxd_nrdadr) ;

	r = queue->rx_curr_get ;
	जबतक (rx_used) अणु
		DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORCPU) ;
		rbctrl = le32_to_cpu(r->rxd_rbctrl) ;

		अगर (rbctrl & BMU_OWN) अणु
			अगर (rbctrl & BMU_STF) अणु
				अवरोध ;		/* निकास the loop */
			पूर्ण
			अन्यथा अणु
				/*
				 * repair the descriptor
				 */
				r->rxd_rbctrl &= ~cpu_to_le32(BMU_OWN) ;
			पूर्ण
		पूर्ण
		phys = le32_to_cpu(r->rxd_nrdadr) ;
		DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORDEV) ;
		r = r->rxd_next ;
		rx_used-- ;
	पूर्ण
	वापस phys;
पूर्ण


/*
	-------------------------------------------------------------
	INTERRUPT SERVICE ROUTINE:
	-------------------------------------------------------------
*/

/*
 *	BEGIN_MANUAL_ENTRY(fddi_isr)
 *	व्योम fddi_isr(smc)
 *
 * function	DOWNCALL	(drvsr.c)
 *		पूर्णांकerrupt service routine, handles the पूर्णांकerrupt requests
 *		generated by the FDDI adapter.
 *
 * NOTE:	The operating प्रणाली dependent module must guarantee that the
 *		पूर्णांकerrupts of the adapter are disabled when it calls fddi_isr.
 *
 *	About the USE_BREAK_ISR mechanismn:
 *
 *	The मुख्य requirement of this mechanismn is to क्रमce an समयr IRQ when
 *	leaving process_receive() with leave_isr set. process_receive() may
 *	be called at any समय from anywhere!
 *	To be sure we करोn't miss such event we set 'force_irq' per शेष.
 *	We have to क्रमce and Timer IRQ अगर 'smc->os.hwm.leave_isr' AND
 *	'force_irq' are set. 'force_irq' may be reset अगर a receive complete
 *	IRQ is pending.
 *
 *	END_MANUAL_ENTRY
 */
व्योम fddi_isr(काष्ठा s_smc *smc)
अणु
	u_दीर्घ		is ;		/* ISR source */
	u_लघु		stu, stl ;
	SMbuf		*mb ;

#अगर_घोषित	USE_BREAK_ISR
	पूर्णांक	क्रमce_irq ;
#पूर्ण_अगर

#अगर_घोषित	ODI2
	अगर (smc->os.hwm.rx_अवरोध) अणु
		mac_drv_fill_rxd(smc) ;
		अगर (smc->hw.fp.rx_q[QUEUE_R1].rx_used > 0) अणु
			smc->os.hwm.rx_अवरोध = 0 ;
			process_receive(smc) ;
		पूर्ण
		अन्यथा अणु
			smc->os.hwm.detec_count = 0 ;
			smt_क्रमce_irq(smc) ;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	smc->os.hwm.isr_flag = TRUE ;

#अगर_घोषित	USE_BREAK_ISR
	क्रमce_irq = TRUE ;
	अगर (smc->os.hwm.leave_isr) अणु
		smc->os.hwm.leave_isr = FALSE ;
		process_receive(smc) ;
	पूर्ण
#पूर्ण_अगर

	जबतक ((is = GET_ISR() & ISR_MASK)) अणु
		NDD_TRACE("CH0B",is,0,0) ;
		DB_GEN(7, "ISA = 0x%lx", is);

		अगर (is & IMASK_SLOW) अणु
			NDD_TRACE("CH1b",is,0,0) ;
			अगर (is & IS_PLINT1) अणु	/* PLC1 */
				plc1_irq(smc) ;
			पूर्ण
			अगर (is & IS_PLINT2) अणु	/* PLC2 */
				plc2_irq(smc) ;
			पूर्ण
			अगर (is & IS_MINTR1) अणु	/* FORMAC+ STU1(U/L) */
				stu = inpw(FM_A(FM_ST1U)) ;
				stl = inpw(FM_A(FM_ST1L)) ;
				DB_GEN(6, "Slow transmit complete");
				mac1_irq(smc,stu,stl) ;
			पूर्ण
			अगर (is & IS_MINTR2) अणु	/* FORMAC+ STU2(U/L) */
				stu= inpw(FM_A(FM_ST2U)) ;
				stl= inpw(FM_A(FM_ST2L)) ;
				DB_GEN(6, "Slow receive complete");
				DB_GEN(7, "stl = %x : stu = %x", stl, stu);
				mac2_irq(smc,stu,stl) ;
			पूर्ण
			अगर (is & IS_MINTR3) अणु	/* FORMAC+ STU3(U/L) */
				stu= inpw(FM_A(FM_ST3U)) ;
				stl= inpw(FM_A(FM_ST3L)) ;
				DB_GEN(6, "FORMAC Mode Register 3");
				mac3_irq(smc,stu,stl) ;
			पूर्ण
			अगर (is & IS_TIMINT) अणु	/* Timer 82C54-2 */
				समयr_irq(smc) ;
#अगर_घोषित	NDIS_OS2
				क्रमce_irq_pending = 0 ;
#पूर्ण_अगर
				/*
				 * out of RxD detection
				 */
				अगर (++smc->os.hwm.detec_count > 4) अणु
					/*
					 * check out of RxD condition
					 */
					 process_receive(smc) ;
				पूर्ण
			पूर्ण
			अगर (is & IS_TOKEN) अणु	/* Restricted Token Monitor */
				rपंचांग_irq(smc) ;
			पूर्ण
			अगर (is & IS_R1_P) अणु	/* Parity error rx queue 1 */
				/* clear IRQ */
				outpd(ADDR(B4_R1_CSR),CSR_IRQ_CL_P) ;
				SMT_PANIC(smc,HWM_E0004,HWM_E0004_MSG) ;
			पूर्ण
			अगर (is & IS_R1_C) अणु	/* Encoding error rx queue 1 */
				/* clear IRQ */
				outpd(ADDR(B4_R1_CSR),CSR_IRQ_CL_C) ;
				SMT_PANIC(smc,HWM_E0005,HWM_E0005_MSG) ;
			पूर्ण
			अगर (is & IS_XA_C) अणु	/* Encoding error async tx q */
				/* clear IRQ */
				outpd(ADDR(B5_XA_CSR),CSR_IRQ_CL_C) ;
				SMT_PANIC(smc,HWM_E0006,HWM_E0006_MSG) ;
			पूर्ण
			अगर (is & IS_XS_C) अणु	/* Encoding error sync tx q */
				/* clear IRQ */
				outpd(ADDR(B5_XS_CSR),CSR_IRQ_CL_C) ;
				SMT_PANIC(smc,HWM_E0007,HWM_E0007_MSG) ;
			पूर्ण
		पूर्ण

		/*
		 *	Fast Tx complete Async/Sync Queue (BMU service)
		 */
		अगर (is & (IS_XS_F|IS_XA_F)) अणु
			DB_GEN(6, "Fast tx complete queue");
			/*
			 * clear IRQ, Note: no IRQ is lost, because
			 * 	we always service both queues
			 */
			outpd(ADDR(B5_XS_CSR),CSR_IRQ_CL_F) ;
			outpd(ADDR(B5_XA_CSR),CSR_IRQ_CL_F) ;
			mac_drv_clear_txd(smc) ;
			llc_restart_tx(smc) ;
		पूर्ण

		/*
		 *	Fast Rx Complete (BMU service)
		 */
		अगर (is & IS_R1_F) अणु
			DB_GEN(6, "Fast receive complete");
			/* clear IRQ */
#अगर_अघोषित USE_BREAK_ISR
			outpd(ADDR(B4_R1_CSR),CSR_IRQ_CL_F) ;
			process_receive(smc) ;
#अन्यथा
			process_receive(smc) ;
			अगर (smc->os.hwm.leave_isr) अणु
				क्रमce_irq = FALSE ;
			पूर्ण अन्यथा अणु
				outpd(ADDR(B4_R1_CSR),CSR_IRQ_CL_F) ;
				process_receive(smc) ;
			पूर्ण
#पूर्ण_अगर
		पूर्ण

#अगर_अघोषित	NDIS_OS2
		जबतक ((mb = get_llc_rx(smc))) अणु
			smt_to_llc(smc,mb) ;
		पूर्ण
#अन्यथा
		अगर (offDepth)
			post_proc() ;

		जबतक (!offDepth && (mb = get_llc_rx(smc))) अणु
			smt_to_llc(smc,mb) ;
		पूर्ण

		अगर (!offDepth && smc->os.hwm.rx_अवरोध) अणु
			process_receive(smc) ;
		पूर्ण
#पूर्ण_अगर
		अगर (smc->q.ev_get != smc->q.ev_put) अणु
			NDD_TRACE("CH2a",0,0,0) ;
			ev_dispatcher(smc) ;
		पूर्ण
#अगर_घोषित	NDIS_OS2
		post_proc() ;
		अगर (offDepth) अणु		/* leave fddi_isr because */
			अवरोध ;		/* indications not allowed */
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित	USE_BREAK_ISR
		अगर (smc->os.hwm.leave_isr) अणु
			अवरोध ;		/* leave fddi_isr */
		पूर्ण
#पूर्ण_अगर

		/* NOTE: when the isr is left, no rx is pending */
	पूर्ण	/* end of पूर्णांकerrupt source polling loop */

#अगर_घोषित	USE_BREAK_ISR
	अगर (smc->os.hwm.leave_isr && क्रमce_irq) अणु
		smt_क्रमce_irq(smc) ;
	पूर्ण
#पूर्ण_अगर
	smc->os.hwm.isr_flag = FALSE ;
	NDD_TRACE("CH0E",0,0,0) ;
पूर्ण


/*
	-------------------------------------------------------------
	RECEIVE FUNCTIONS:
	-------------------------------------------------------------
*/

#अगर_अघोषित	NDIS_OS2
/*
 *	BEGIN_MANUAL_ENTRY(mac_drv_rx_mode)
 *	व्योम mac_drv_rx_mode(smc,mode)
 *
 * function	DOWNCALL	(fplus.c)
 *		Corresponding to the parameter mode, the operating प्रणाली
 *		dependent module can activate several receive modes.
 *
 * para	mode	= 1:	RX_ENABLE_ALLMULTI	enable all multicasts
 *		= 2:	RX_DISABLE_ALLMULTI	disable "enable all multicasts"
 *		= 3:	RX_ENABLE_PROMISC	enable promiscuous
 *		= 4:	RX_DISABLE_PROMISC	disable promiscuous
 *		= 5:	RX_ENABLE_NSA		enable rec. of all NSA frames
 *			(disabled after 'driver reset' & 'set station address')
 *		= 6:	RX_DISABLE_NSA		disable rec. of all NSA frames
 *
 *		= 21:	RX_ENABLE_PASS_SMT	( see description )
 *		= 22:	RX_DISABLE_PASS_SMT	(  "	   "	  )
 *		= 23:	RX_ENABLE_PASS_NSA	(  "	   "	  )
 *		= 24:	RX_DISABLE_PASS_NSA	(  "	   "	  )
 *		= 25:	RX_ENABLE_PASS_DB	(  "	   "	  )
 *		= 26:	RX_DISABLE_PASS_DB	(  "	   "	  )
 *		= 27:	RX_DISABLE_PASS_ALL	(  "	   "	  )
 *		= 28:	RX_DISABLE_LLC_PROMISC	(  "	   "	  )
 *		= 29:	RX_ENABLE_LLC_PROMISC	(  "	   "	  )
 *
 *
 *		RX_ENABLE_PASS_SMT / RX_DISABLE_PASS_SMT
 *
 *		If the operating प्रणाली dependent module activates the
 *		mode RX_ENABLE_PASS_SMT, the hardware module
 *		duplicates all SMT frames with the frame control
 *		FC_SMT_INFO and passes them to the LLC receive channel
 *		by calling mac_drv_rx_init.
 *		The SMT Frames which are sent by the local SMT and the NSA
 *		frames whose A- and C-Indicator is not set are also duplicated
 *		and passed.
 *		The receive mode RX_DISABLE_PASS_SMT disables the passing
 *		of SMT frames.
 *
 *		RX_ENABLE_PASS_NSA / RX_DISABLE_PASS_NSA
 *
 *		If the operating प्रणाली dependent module activates the
 *		mode RX_ENABLE_PASS_NSA, the hardware module
 *		duplicates all NSA frames with frame control FC_SMT_NSA
 *		and a set A-Indicator and passed them to the LLC
 *		receive channel by calling mac_drv_rx_init.
 *		All NSA Frames which are sent by the local SMT
 *		are also duplicated and passed.
 *		The receive mode RX_DISABLE_PASS_NSA disables the passing
 *		of NSA frames with the A- or C-Indicator set.
 *
 * NOTE:	For fear that the hardware module receives NSA frames with
 *		a reset A-Indicator, the operating प्रणाली dependent module
 *		has to call mac_drv_rx_mode with the mode RX_ENABLE_NSA
 *		beक्रमe activate the RX_ENABLE_PASS_NSA mode and after every
 *		'driver reset' and 'set station address'.
 *
 *		RX_ENABLE_PASS_DB / RX_DISABLE_PASS_DB
 *
 *		If the operating प्रणाली dependent module activates the
 *		mode RX_ENABLE_PASS_DB, direct BEACON frames
 *		(FC_BEACON frame control) are passed to the LLC receive
 *		channel by mac_drv_rx_init.
 *		The receive mode RX_DISABLE_PASS_DB disables the passing
 *		of direct BEACON frames.
 *
 *		RX_DISABLE_PASS_ALL
 *
 *		Disables all special receives modes. It is equal to
 *		call mac_drv_set_rx_mode successively with the
 *		parameters RX_DISABLE_NSA, RX_DISABLE_PASS_SMT,
 *		RX_DISABLE_PASS_NSA and RX_DISABLE_PASS_DB.
 *
 *		RX_ENABLE_LLC_PROMISC
 *
 *		(शेष) all received LLC frames and all SMT/NSA/DBEACON
 *		frames depending on the attitude of the flags
 *		PASS_SMT/PASS_NSA/PASS_DBEACON will be delivered to the
 *		LLC layer
 *
 *		RX_DISABLE_LLC_PROMISC
 *
 *		all received SMT/NSA/DBEACON frames depending on the
 *		attitude of the flags PASS_SMT/PASS_NSA/PASS_DBEACON
 *		will be delivered to the LLC layer.
 *		all received LLC frames with a directed address, Multicast
 *		or Broadcast address will be delivered to the LLC
 *		layer too.
 *
 *	END_MANUAL_ENTRY
 */
व्योम mac_drv_rx_mode(काष्ठा s_smc *smc, पूर्णांक mode)
अणु
	चयन(mode) अणु
	हाल RX_ENABLE_PASS_SMT:
		smc->os.hwm.pass_SMT = TRUE ;
		अवरोध ;
	हाल RX_DISABLE_PASS_SMT:
		smc->os.hwm.pass_SMT = FALSE ;
		अवरोध ;
	हाल RX_ENABLE_PASS_NSA:
		smc->os.hwm.pass_NSA = TRUE ;
		अवरोध ;
	हाल RX_DISABLE_PASS_NSA:
		smc->os.hwm.pass_NSA = FALSE ;
		अवरोध ;
	हाल RX_ENABLE_PASS_DB:
		smc->os.hwm.pass_DB = TRUE ;
		अवरोध ;
	हाल RX_DISABLE_PASS_DB:
		smc->os.hwm.pass_DB = FALSE ;
		अवरोध ;
	हाल RX_DISABLE_PASS_ALL:
		smc->os.hwm.pass_SMT = smc->os.hwm.pass_NSA = FALSE ;
		smc->os.hwm.pass_DB = FALSE ;
		smc->os.hwm.pass_llc_promisc = TRUE ;
		mac_set_rx_mode(smc,RX_DISABLE_NSA) ;
		अवरोध ;
	हाल RX_DISABLE_LLC_PROMISC:
		smc->os.hwm.pass_llc_promisc = FALSE ;
		अवरोध ;
	हाल RX_ENABLE_LLC_PROMISC:
		smc->os.hwm.pass_llc_promisc = TRUE ;
		अवरोध ;
	हाल RX_ENABLE_ALLMULTI:
	हाल RX_DISABLE_ALLMULTI:
	हाल RX_ENABLE_PROMISC:
	हाल RX_DISABLE_PROMISC:
	हाल RX_ENABLE_NSA:
	हाल RX_DISABLE_NSA:
	शेष:
		mac_set_rx_mode(smc,mode) ;
		अवरोध ;
	पूर्ण
पूर्ण
#पूर्ण_अगर	/* अगरndef NDIS_OS2 */

/*
 * process receive queue
 */
व्योम process_receive(काष्ठा s_smc *smc)
अणु
	पूर्णांक i ;
	पूर्णांक n ;
	पूर्णांक frag_count ;		/* number of RxDs of the curr rx buf */
	पूर्णांक used_frags ;		/* number of RxDs of the curr frame */
	काष्ठा s_smt_rx_queue *queue ;	/* poपूर्णांकs to the queue ctl काष्ठा */
	काष्ठा s_smt_fp_rxd अस्थिर *r ;	/* rxd poपूर्णांकer */
	काष्ठा s_smt_fp_rxd अस्थिर *rxd ;	/* first rxd of rx frame */
	u_दीर्घ rbctrl ;			/* receive buffer control word */
	u_दीर्घ rfsw ;			/* receive frame status word */
	u_लघु rx_used ;
	u_अक्षर far *virt ;
	अक्षर far *data ;
	SMbuf *mb ;
	u_अक्षर fc ;			/* Frame control */
	पूर्णांक len ;			/* Frame length */

	smc->os.hwm.detec_count = 0 ;
	queue = smc->hw.fp.rx[QUEUE_R1] ;
	NDD_TRACE("RHxB",0,0,0) ;
	क्रम ( ; ; ) अणु
		r = queue->rx_curr_get ;
		rx_used = queue->rx_used ;
		frag_count = 0 ;

#अगर_घोषित	USE_BREAK_ISR
		अगर (smc->os.hwm.leave_isr) अणु
			जाओ rx_end ;
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित	NDIS_OS2
		अगर (offDepth) अणु
			smc->os.hwm.rx_अवरोध = 1 ;
			जाओ rx_end ;
		पूर्ण
		smc->os.hwm.rx_अवरोध = 0 ;
#पूर्ण_अगर
#अगर_घोषित	ODI2
		अगर (smc->os.hwm.rx_अवरोध) अणु
			जाओ rx_end ;
		पूर्ण
#पूर्ण_अगर
		n = 0 ;
		करो अणु
			DB_RX(5, "Check RxD %p for OWN and EOF", r);
			DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORCPU) ;
			rbctrl = le32_to_cpu(CR_READ(r->rxd_rbctrl));

			अगर (rbctrl & BMU_OWN) अणु
				NDD_TRACE("RHxE",r,rfsw,rbctrl) ;
				DB_RX(4, "End of RxDs");
				जाओ rx_end ;
			पूर्ण
			/*
			 * out of RxD detection
			 */
			अगर (!rx_used) अणु
				SK_BREAK() ;
				SMT_PANIC(smc,HWM_E0009,HWM_E0009_MSG) ;
				/* Either we करोn't have an RxD or all
				 * RxDs are filled. Thereक्रमe it's allowed
				 * क्रम to set the STOPPED flag */
				smc->hw.hw_state = STOPPED ;
				mac_drv_clear_rx_queue(smc) ;
				smc->hw.hw_state = STARTED ;
				mac_drv_fill_rxd(smc) ;
				smc->os.hwm.detec_count = 0 ;
				जाओ rx_end ;
			पूर्ण
			rfsw = le32_to_cpu(r->rxd_rfsw) ;
			अगर ((rbctrl & BMU_STF) != ((rbctrl & BMU_ST_BUF) <<5)) अणु
				/*
				 * The BMU_STF bit is deleted, 1 frame is
				 * placed पूर्णांकo more than 1 rx buffer
				 *
				 * skip frame by setting the rx len to 0
				 *
				 * अगर fragment count == 0
				 *	The missing STF bit beदीर्घs to the
				 *	current frame, search क्रम the
				 *	खातापूर्ण bit to complete the frame
				 * अन्यथा
				 *	the fragment beदीर्घs to the next frame,
				 *	निकास the loop and process the frame
				 */
				SK_BREAK() ;
				rfsw = 0 ;
				अगर (frag_count) अणु
					अवरोध ;
				पूर्ण
			पूर्ण
			n += rbctrl & 0xffff ;
			r = r->rxd_next ;
			frag_count++ ;
			rx_used-- ;
		पूर्ण जबतक (!(rbctrl & BMU_खातापूर्ण)) ;
		used_frags = frag_count ;
		DB_RX(5, "EOF set in RxD, used_frags = %d", used_frags);

		/* may be next 2 DRV_BUF_FLUSH() can be skipped, because */
		/* BMU_ST_BUF will not be changed by the ASIC */
		DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORCPU) ;
		जबतक (rx_used && !(r->rxd_rbctrl & cpu_to_le32(BMU_ST_BUF))) अणु
			DB_RX(5, "Check STF bit in %p", r);
			r = r->rxd_next ;
			DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORCPU) ;
			frag_count++ ;
			rx_used-- ;
		पूर्ण
		DB_RX(5, "STF bit found");

		/*
		 * The received frame is finished क्रम the process receive
		 */
		rxd = queue->rx_curr_get ;
		queue->rx_curr_get = r ;
		queue->rx_मुक्त += frag_count ;
		queue->rx_used = rx_used ;

		/*
		 * ASIC Errata no. 7 (STF - Bit Bug)
		 */
		rxd->rxd_rbctrl &= cpu_to_le32(~BMU_STF) ;

		क्रम (r=rxd, i=frag_count ; i ; r=r->rxd_next, i--)अणु
			DB_RX(5, "dma_complete for RxD %p", r);
			dma_complete(smc,(जोड़ s_fp_descr अस्थिर *)r,DMA_WR);
		पूर्ण
		smc->hw.fp.err_stats.err_valid++ ;
		smc->mib.m[MAC0].fddiMACCopied_Ct++ ;

		/* the length of the data including the FC */
		len = (rfsw & RD_LENGTH) - 4 ;

		DB_RX(4, "frame length = %d", len);
		/*
		 * check the frame_length and all error flags
		 */
		अगर (rfsw & (RX_MSRABT|RX_FS_E|RX_FS_CRC|RX_FS_IMPL))अणु
			अगर (rfsw & RD_S_MSRABT) अणु
				DB_RX(2, "Frame aborted by the FORMAC");
				smc->hw.fp.err_stats.err_पात++ ;
			पूर्ण
			/*
			 * check frame status
			 */
			अगर (rfsw & RD_S_SEAC2) अणु
				DB_RX(2, "E-Indicator set");
				smc->hw.fp.err_stats.err_e_indicator++ ;
			पूर्ण
			अगर (rfsw & RD_S_SFRMERR) अणु
				DB_RX(2, "CRC error");
				smc->hw.fp.err_stats.err_crc++ ;
			पूर्ण
			अगर (rfsw & RX_FS_IMPL) अणु
				DB_RX(2, "Implementer frame");
				smc->hw.fp.err_stats.err_imp_frame++ ;
			पूर्ण
			जाओ पात_frame ;
		पूर्ण
		अगर (len > FDDI_RAW_MTU-4) अणु
			DB_RX(2, "Frame too long error");
			smc->hw.fp.err_stats.err_too_दीर्घ++ ;
			जाओ पात_frame ;
		पूर्ण
		/*
		 * SUPERNET 3 Bug: FORMAC delivers status words
		 * of पातed frames to the BMU
		 */
		अगर (len <= 4) अणु
			DB_RX(2, "Frame length = 0");
			जाओ पात_frame ;
		पूर्ण

		अगर (len != (n-4)) अणु
			DB_RX(4, "BMU: rx len differs: [%d:%d]", len, n);
			smc->os.hwm.rx_len_error++ ;
			जाओ पात_frame ;
		पूर्ण

		/*
		 * Check SA == MA
		 */
		virt = (u_अक्षर far *) rxd->rxd_virt ;
		DB_RX(2, "FC = %x", *virt);
		अगर (virt[12] == MA[5] &&
		    virt[11] == MA[4] &&
		    virt[10] == MA[3] &&
		    virt[9] == MA[2] &&
		    virt[8] == MA[1] &&
		    (virt[7] & ~GROUP_ADDR_BIT) == MA[0]) अणु
			जाओ पात_frame ;
		पूर्ण

		/*
		 * test अगर LLC frame
		 */
		अगर (rfsw & RX_FS_LLC) अणु
			/*
			 * अगर pass_llc_promisc is disable
			 *	अगर DA != Multicast or Broadcast or DA!=MA
			 *		पात the frame
			 */
			अगर (!smc->os.hwm.pass_llc_promisc) अणु
				अगर(!(virt[1] & GROUP_ADDR_BIT)) अणु
					अगर (virt[6] != MA[5] ||
					    virt[5] != MA[4] ||
					    virt[4] != MA[3] ||
					    virt[3] != MA[2] ||
					    virt[2] != MA[1] ||
					    virt[1] != MA[0]) अणु
						DB_RX(2, "DA != MA and not multi- or broadcast");
						जाओ पात_frame ;
					पूर्ण
				पूर्ण
			पूर्ण

			/*
			 * LLC frame received
			 */
			DB_RX(4, "LLC - receive");
			mac_drv_rx_complete(smc,rxd,frag_count,len) ;
		पूर्ण
		अन्यथा अणु
			अगर (!(mb = smt_get_mbuf(smc))) अणु
				smc->hw.fp.err_stats.err_no_buf++ ;
				DB_RX(4, "No SMbuf; receive terminated");
				जाओ पात_frame ;
			पूर्ण
			data = smtod(mb,अक्षर *) - 1 ;

			/*
			 * copy the frame पूर्णांकo a SMT_MBuf
			 */
#अगर_घोषित USE_OS_CPY
			hwm_cpy_rxd2mb(rxd,data,len) ;
#अन्यथा
			क्रम (r=rxd, i=used_frags ; i ; r=r->rxd_next, i--)अणु
				n = le32_to_cpu(r->rxd_rbctrl) & RD_LENGTH ;
				DB_RX(6, "cp SMT frame to mb: len = %d", n);
				स_नकल(data,r->rxd_virt,n) ;
				data += n ;
			पूर्ण
			data = smtod(mb,अक्षर *) - 1 ;
#पूर्ण_अगर
			fc = *(अक्षर *)mb->sm_data = *data ;
			mb->sm_len = len - 1 ;		/* len - fc */
			data++ ;

			/*
			 * SMT frame received
			 */
			चयन(fc) अणु
			हाल FC_SMT_INFO :
				smc->hw.fp.err_stats.err_smt_frame++ ;
				DB_RX(5, "SMT frame received");

				अगर (smc->os.hwm.pass_SMT) अणु
					DB_RX(5, "pass SMT frame");
					mac_drv_rx_complete(smc, rxd,
						frag_count,len) ;
				पूर्ण
				अन्यथा अणु
					DB_RX(5, "requeue RxD");
					mac_drv_requeue_rxd(smc,rxd,frag_count);
				पूर्ण

				smt_received_pack(smc,mb,(पूर्णांक)(rfsw>>25)) ;
				अवरोध ;
			हाल FC_SMT_NSA :
				smc->hw.fp.err_stats.err_smt_frame++ ;
				DB_RX(5, "SMT frame received");

				/* अगर pass_NSA set pass the NSA frame or */
				/* pass_SMT set and the A-Indicator */
				/* is not set, pass the NSA frame */
				अगर (smc->os.hwm.pass_NSA ||
					(smc->os.hwm.pass_SMT &&
					!(rfsw & A_INDIC))) अणु
					DB_RX(5, "pass SMT frame");
					mac_drv_rx_complete(smc, rxd,
						frag_count,len) ;
				पूर्ण
				अन्यथा अणु
					DB_RX(5, "requeue RxD");
					mac_drv_requeue_rxd(smc,rxd,frag_count);
				पूर्ण

				smt_received_pack(smc,mb,(पूर्णांक)(rfsw>>25)) ;
				अवरोध ;
			हाल FC_BEACON :
				अगर (smc->os.hwm.pass_DB) अणु
					DB_RX(5, "pass DB frame");
					mac_drv_rx_complete(smc, rxd,
						frag_count,len) ;
				पूर्ण
				अन्यथा अणु
					DB_RX(5, "requeue RxD");
					mac_drv_requeue_rxd(smc,rxd,frag_count);
				पूर्ण
				smt_मुक्त_mbuf(smc,mb) ;
				अवरोध ;
			शेष :
				/*
				 * unknown FC पात the frame
				 */
				DB_RX(2, "unknown FC error");
				smt_मुक्त_mbuf(smc,mb) ;
				DB_RX(5, "requeue RxD");
				mac_drv_requeue_rxd(smc,rxd,frag_count) ;
				अगर ((fc & 0xf0) == FC_MAC)
					smc->hw.fp.err_stats.err_mac_frame++ ;
				अन्यथा
					smc->hw.fp.err_stats.err_imp_frame++ ;

				अवरोध ;
			पूर्ण
		पूर्ण

		DB_RX(3, "next RxD is %p", queue->rx_curr_get);
		NDD_TRACE("RHx1",queue->rx_curr_get,0,0) ;

		जारी ;
	/*--------------------------------------------------------------------*/
पात_frame:
		DB_RX(5, "requeue RxD");
		mac_drv_requeue_rxd(smc,rxd,frag_count) ;

		DB_RX(3, "next RxD is %p", queue->rx_curr_get);
		NDD_TRACE("RHx2",queue->rx_curr_get,0,0) ;
	पूर्ण
rx_end:
#अगर_घोषित	ALL_RX_COMPLETE
	mac_drv_all_receives_complete(smc) ;
#पूर्ण_अगर
	वापस ;	/* lपूर्णांक bug: needs वापस detect end of function */
पूर्ण

अटल व्योम smt_to_llc(काष्ठा s_smc *smc, SMbuf *mb)
अणु
	u_अक्षर	fc ;

	DB_RX(4, "send a queued frame to the llc layer");
	smc->os.hwm.r.len = mb->sm_len ;
	smc->os.hwm.r.mb_pos = smtod(mb,अक्षर *) ;
	fc = *smc->os.hwm.r.mb_pos ;
	(व्योम)mac_drv_rx_init(smc,(पूर्णांक)mb->sm_len,(पूर्णांक)fc,
		smc->os.hwm.r.mb_pos,(पूर्णांक)mb->sm_len) ;
	smt_मुक्त_mbuf(smc,mb) ;
पूर्ण

/*
 *	BEGIN_MANUAL_ENTRY(hwm_rx_frag)
 *	व्योम hwm_rx_frag(smc,virt,phys,len,frame_status)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This function calls dma_master क्रम preparing the
 *		प्रणाली hardware क्रम the DMA transfer and initializes
 *		the current RxD with the length and the physical and
 *		भव address of the fragment. Furthermore, it sets the
 *		STF and खातापूर्ण bits depending on the frame status byte,
 *		चयनes the OWN flag of the RxD, so that it is owned by the
 *		adapter and issues an rx_start.
 *
 * para	virt	भव poपूर्णांकer to the fragment
 *	len	the length of the fragment
 *	frame_status	status of the frame, see design description
 *
 * NOTE:	It is possible to call this function with a fragment length
 *		of zero.
 *
 *	END_MANUAL_ENTRY
 */
व्योम hwm_rx_frag(काष्ठा s_smc *smc, अक्षर far *virt, u_दीर्घ phys, पूर्णांक len,
		 पूर्णांक frame_status)
अणु
	काष्ठा s_smt_fp_rxd अस्थिर *r ;
	__le32	rbctrl;

	NDD_TRACE("RHfB",virt,len,frame_status) ;
	DB_RX(2, "hwm_rx_frag: len = %d, frame_status = %x", len, frame_status);
	r = smc->hw.fp.rx_q[QUEUE_R1].rx_curr_put ;
	r->rxd_virt = virt ;
	r->rxd_rbadr = cpu_to_le32(phys) ;
	rbctrl = cpu_to_le32( (((__u32)frame_status &
		(FIRST_FRAG|LAST_FRAG))<<26) |
		(((u_दीर्घ) frame_status & FIRST_FRAG) << 21) |
		BMU_OWN | BMU_CHECK | BMU_EN_IRQ_खातापूर्ण | len) ;
	r->rxd_rbctrl = rbctrl ;

	DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORDEV) ;
	outpd(ADDR(B0_R1_CSR),CSR_START) ;
	smc->hw.fp.rx_q[QUEUE_R1].rx_मुक्त-- ;
	smc->hw.fp.rx_q[QUEUE_R1].rx_used++ ;
	smc->hw.fp.rx_q[QUEUE_R1].rx_curr_put = r->rxd_next ;
	NDD_TRACE("RHfE",r,le32_to_cpu(r->rxd_rbadr),0) ;
पूर्ण

/*
 *	BEGINN_MANUAL_ENTRY(mac_drv_clear_rx_queue)
 *
 * व्योम mac_drv_clear_rx_queue(smc)
 * काष्ठा s_smc *smc ;
 *
 * function	DOWNCALL	(hardware module, hwmपंचांग.c)
 *		mac_drv_clear_rx_queue is called by the OS-specअगरic module
 *		after it has issued a card_stop.
 *		In this हाल, the frames in the receive queue are obsolete and
 *		should be हटाओd. For removing mac_drv_clear_rx_queue
 *		calls dma_master क्रम each RxD and mac_drv_clear_rxd क्रम each
 *		receive buffer.
 *
 * NOTE:	calling sequence card_stop:
 *		CLI_FBI(), card_stop(),
 *		mac_drv_clear_tx_queue(), mac_drv_clear_rx_queue(),
 *
 * NOTE:	The caller is responsible that the BMUs are idle
 *		when this function is called.
 *
 *	END_MANUAL_ENTRY
 */
व्योम mac_drv_clear_rx_queue(काष्ठा s_smc *smc)
अणु
	काष्ठा s_smt_fp_rxd अस्थिर *r ;
	काष्ठा s_smt_fp_rxd अस्थिर *next_rxd ;
	काष्ठा s_smt_rx_queue *queue ;
	पूर्णांक frag_count ;
	पूर्णांक i ;

	अगर (smc->hw.hw_state != STOPPED) अणु
		SK_BREAK() ;
		SMT_PANIC(smc,HWM_E0012,HWM_E0012_MSG) ;
		वापस ;
	पूर्ण

	queue = smc->hw.fp.rx[QUEUE_R1] ;
	DB_RX(5, "clear_rx_queue");

	/*
	 * dma_complete and mac_drv_clear_rxd क्रम all RxDs / receive buffers
	 */
	r = queue->rx_curr_get ;
	जबतक (queue->rx_used) अणु
		DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORCPU) ;
		DB_RX(5, "switch OWN bit of RxD 0x%p", r);
		r->rxd_rbctrl &= ~cpu_to_le32(BMU_OWN) ;
		frag_count = 1 ;
		DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORDEV) ;
		r = r->rxd_next ;
		DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORCPU) ;
		जबतक (r != queue->rx_curr_put &&
			!(r->rxd_rbctrl & cpu_to_le32(BMU_ST_BUF))) अणु
			DB_RX(5, "Check STF bit in %p", r);
			r->rxd_rbctrl &= ~cpu_to_le32(BMU_OWN) ;
			DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORDEV) ;
			r = r->rxd_next ;
			DRV_BUF_FLUSH(r,DDI_DMA_SYNC_FORCPU) ;
			frag_count++ ;
		पूर्ण
		DB_RX(5, "STF bit found");
		next_rxd = r ;

		क्रम (r=queue->rx_curr_get,i=frag_count; i ; r=r->rxd_next,i--)अणु
			DB_RX(5, "dma_complete for RxD %p", r);
			dma_complete(smc,(जोड़ s_fp_descr अस्थिर *)r,DMA_WR);
		पूर्ण

		DB_RX(5, "mac_drv_clear_rxd: RxD %p frag_count %d",
		      queue->rx_curr_get, frag_count);
		mac_drv_clear_rxd(smc,queue->rx_curr_get,frag_count) ;

		queue->rx_curr_get = next_rxd ;
		queue->rx_used -= frag_count ;
		queue->rx_मुक्त += frag_count ;
	पूर्ण
पूर्ण


/*
	-------------------------------------------------------------
	SEND FUNCTIONS:
	-------------------------------------------------------------
*/

/*
 *	BEGIN_MANUAL_ENTRY(hwm_tx_init)
 *	पूर्णांक hwm_tx_init(smc,fc,frag_count,frame_len,frame_status)
 *
 * function	DOWN_CALL	(hardware module, hwmपंचांग.c)
 *		hwm_tx_init checks अगर the frame can be sent through the
 *		corresponding send queue.
 *
 * para	fc	the frame control. To determine through which
 *		send queue the frame should be transmitted.
 *		0x50 - 0x57:	asynchronous LLC frame
 *		0xD0 - 0xD7:	synchronous LLC frame
 *		0x41, 0x4F:	SMT frame to the network
 *		0x42:		SMT frame to the network and to the local SMT
 *		0x43:		SMT frame to the local SMT
 *	frag_count	count of the fragments क्रम this frame
 *	frame_len	length of the frame
 *	frame_status	status of the frame, the send queue bit is alपढ़ोy
 *			specअगरied
 *
 * वापस		frame_status
 *
 *	END_MANUAL_ENTRY
 */
पूर्णांक hwm_tx_init(काष्ठा s_smc *smc, u_अक्षर fc, पूर्णांक frag_count, पूर्णांक frame_len,
		पूर्णांक frame_status)
अणु
	NDD_TRACE("THiB",fc,frag_count,frame_len) ;
	smc->os.hwm.tx_p = smc->hw.fp.tx[frame_status & QUEUE_A0] ;
	smc->os.hwm.tx_descr = TX_DESCRIPTOR | (((u_दीर्घ)(frame_len-1)&3)<<27) ;
	smc->os.hwm.tx_len = frame_len ;
	DB_TX(3, "hwm_tx_init: fc = %x, len = %d", fc, frame_len);
	अगर ((fc & ~(FC_SYNC_BIT|FC_LLC_PRIOR)) == FC_ASYNC_LLC) अणु
		frame_status |= LAN_TX ;
	पूर्ण
	अन्यथा अणु
		चयन (fc) अणु
		हाल FC_SMT_INFO :
		हाल FC_SMT_NSA :
			frame_status |= LAN_TX ;
			अवरोध ;
		हाल FC_SMT_LOC :
			frame_status |= LOC_TX ;
			अवरोध ;
		हाल FC_SMT_LAN_LOC :
			frame_status |= LAN_TX | LOC_TX ;
			अवरोध ;
		शेष :
			SMT_PANIC(smc,HWM_E0010,HWM_E0010_MSG) ;
		पूर्ण
	पूर्ण
	अगर (!smc->hw.mac_ring_is_up) अणु
		frame_status &= ~LAN_TX ;
		frame_status |= RING_DOWN ;
		DB_TX(2, "Ring is down: terminate LAN_TX");
	पूर्ण
	अगर (frag_count > smc->os.hwm.tx_p->tx_मुक्त) अणु
#अगर_अघोषित	NDIS_OS2
		mac_drv_clear_txd(smc) ;
		अगर (frag_count > smc->os.hwm.tx_p->tx_मुक्त) अणु
			DB_TX(2, "Out of TxDs, terminate LAN_TX");
			frame_status &= ~LAN_TX ;
			frame_status |= OUT_OF_TXD ;
		पूर्ण
#अन्यथा
		DB_TX(2, "Out of TxDs, terminate LAN_TX");
		frame_status &= ~LAN_TX ;
		frame_status |= OUT_OF_TXD ;
#पूर्ण_अगर
	पूर्ण
	DB_TX(3, "frame_status = %x", frame_status);
	NDD_TRACE("THiE",frame_status,smc->os.hwm.tx_p->tx_मुक्त,0) ;
	वापस frame_status;
पूर्ण

/*
 *	BEGIN_MANUAL_ENTRY(hwm_tx_frag)
 *	व्योम hwm_tx_frag(smc,virt,phys,len,frame_status)
 *
 * function	DOWNCALL	(hardware module, hwmपंचांग.c)
 *		If the frame should be sent to the LAN, this function calls
 *		dma_master, fills the current TxD with the भव and the
 *		physical address, sets the STF and खातापूर्ण bits dependent on
 *		the frame status, and requests the BMU to start the
 *		transmit.
 *		If the frame should be sent to the local SMT, an SMT_MBuf
 *		is allocated अगर the FIRST_FRAG bit is set in the frame_status.
 *		The fragment of the frame is copied पूर्णांकo the SMT MBuf.
 *		The function smt_received_pack is called अगर the LAST_FRAG
 *		bit is set in the frame_status word.
 *
 * para	virt	भव poपूर्णांकer to the fragment
 *	len	the length of the fragment
 *	frame_status	status of the frame, see design description
 *
 * वापस	nothing वापसed, no parameter is modअगरied
 *
 * NOTE:	It is possible to invoke this macro with a fragment length
 *		of zero.
 *
 *	END_MANUAL_ENTRY
 */
व्योम hwm_tx_frag(काष्ठा s_smc *smc, अक्षर far *virt, u_दीर्घ phys, पूर्णांक len,
		 पूर्णांक frame_status)
अणु
	काष्ठा s_smt_fp_txd अस्थिर *t ;
	काष्ठा s_smt_tx_queue *queue ;
	__le32	tbctrl ;

	queue = smc->os.hwm.tx_p ;

	NDD_TRACE("THfB",virt,len,frame_status) ;
	/* Bug fix: AF / May 31 1999 (#missing)
	 * snmpinfo problem reported by IBM is caused by invalid
	 * t-poपूर्णांकer (txd) अगर LAN_TX is not set but LOC_TX only.
	 * Set: t = queue->tx_curr_put  here !
	 */
	t = queue->tx_curr_put ;

	DB_TX(2, "hwm_tx_frag: len = %d, frame_status = %x", len, frame_status);
	अगर (frame_status & LAN_TX) अणु
		/* '*t' is alपढ़ोy defined */
		DB_TX(3, "LAN_TX: TxD = %p, virt = %p", t, virt);
		t->txd_virt = virt ;
		t->txd_txdscr = cpu_to_le32(smc->os.hwm.tx_descr) ;
		t->txd_tbadr = cpu_to_le32(phys) ;
		tbctrl = cpu_to_le32((((__u32)frame_status &
			(FIRST_FRAG|LAST_FRAG|EN_IRQ_खातापूर्ण))<< 26) |
			BMU_OWN|BMU_CHECK |len) ;
		t->txd_tbctrl = tbctrl ;

#अगर_अघोषित	AIX
		DRV_BUF_FLUSH(t,DDI_DMA_SYNC_FORDEV) ;
		outpd(queue->tx_bmu_ctl,CSR_START) ;
#अन्यथा	/* अगरndef AIX */
		DRV_BUF_FLUSH(t,DDI_DMA_SYNC_FORDEV) ;
		अगर (frame_status & QUEUE_A0) अणु
			outpd(ADDR(B0_XA_CSR),CSR_START) ;
		पूर्ण
		अन्यथा अणु
			outpd(ADDR(B0_XS_CSR),CSR_START) ;
		पूर्ण
#पूर्ण_अगर
		queue->tx_मुक्त-- ;
		queue->tx_used++ ;
		queue->tx_curr_put = t->txd_next ;
		अगर (frame_status & LAST_FRAG) अणु
			smc->mib.m[MAC0].fddiMACTransmit_Ct++ ;
		पूर्ण
	पूर्ण
	अगर (frame_status & LOC_TX) अणु
		DB_TX(3, "LOC_TX:");
		अगर (frame_status & FIRST_FRAG) अणु
			अगर(!(smc->os.hwm.tx_mb = smt_get_mbuf(smc))) अणु
				smc->hw.fp.err_stats.err_no_buf++ ;
				DB_TX(4, "No SMbuf; transmit terminated");
			पूर्ण
			अन्यथा अणु
				smc->os.hwm.tx_data =
					smtod(smc->os.hwm.tx_mb,अक्षर *) - 1 ;
#अगर_घोषित USE_OS_CPY
#अगर_घोषित PASS_1ST_TXD_2_TX_COMP
				hwm_cpy_txd2mb(t,smc->os.hwm.tx_data,
					smc->os.hwm.tx_len) ;
#पूर्ण_अगर
#पूर्ण_अगर
			पूर्ण
		पूर्ण
		अगर (smc->os.hwm.tx_mb) अणु
#अगर_अघोषित	USE_OS_CPY
			DB_TX(3, "copy fragment into MBuf");
			स_नकल(smc->os.hwm.tx_data,virt,len) ;
			smc->os.hwm.tx_data += len ;
#पूर्ण_अगर
			अगर (frame_status & LAST_FRAG) अणु
#अगर_घोषित	USE_OS_CPY
#अगर_अघोषित PASS_1ST_TXD_2_TX_COMP
				/*
				 * hwm_cpy_txd2mb(txd,data,len) copies 'len' 
				 * bytes from the भव poपूर्णांकer in 'rxd'
				 * to 'data'. The भव poपूर्णांकer of the 
				 * os-specअगरic tx-buffer should be written
				 * in the LAST txd.
				 */ 
				hwm_cpy_txd2mb(t,smc->os.hwm.tx_data,
					smc->os.hwm.tx_len) ;
#पूर्ण_अगर	/* nPASS_1ST_TXD_2_TX_COMP */
#पूर्ण_अगर	/* USE_OS_CPY */
				smc->os.hwm.tx_data =
					smtod(smc->os.hwm.tx_mb,अक्षर *) - 1 ;
				*(अक्षर *)smc->os.hwm.tx_mb->sm_data =
					*smc->os.hwm.tx_data ;
				smc->os.hwm.tx_data++ ;
				smc->os.hwm.tx_mb->sm_len =
					smc->os.hwm.tx_len - 1 ;
				DB_TX(3, "pass LLC frame to SMT");
				smt_received_pack(smc,smc->os.hwm.tx_mb,
						RD_FS_LOCAL) ;
			पूर्ण
		पूर्ण
	पूर्ण
	NDD_TRACE("THfE",t,queue->tx_मुक्त,0) ;
पूर्ण


/*
 * queues a receive क्रम later send
 */
अटल व्योम queue_llc_rx(काष्ठा s_smc *smc, SMbuf *mb)
अणु
	DB_GEN(4, "queue_llc_rx: mb = %p", mb);
	smc->os.hwm.queued_rx_frames++ ;
	mb->sm_next = (SMbuf *)शून्य ;
	अगर (smc->os.hwm.llc_rx_pipe == शून्य) अणु
		smc->os.hwm.llc_rx_pipe = mb ;
	पूर्ण
	अन्यथा अणु
		smc->os.hwm.llc_rx_tail->sm_next = mb ;
	पूर्ण
	smc->os.hwm.llc_rx_tail = mb ;

	/*
	 * क्रमce an समयr IRQ to receive the data
	 */
	अगर (!smc->os.hwm.isr_flag) अणु
		smt_क्रमce_irq(smc) ;
	पूर्ण
पूर्ण

/*
 * get a SMbuf from the llc_rx_queue
 */
अटल SMbuf *get_llc_rx(काष्ठा s_smc *smc)
अणु
	SMbuf	*mb ;

	अगर ((mb = smc->os.hwm.llc_rx_pipe)) अणु
		smc->os.hwm.queued_rx_frames-- ;
		smc->os.hwm.llc_rx_pipe = mb->sm_next ;
	पूर्ण
	DB_GEN(4, "get_llc_rx: mb = 0x%p", mb);
	वापस mb;
पूर्ण

/*
 * queues a transmit SMT MBuf during the समय were the MBuf is
 * queued the TxD ring
 */
अटल व्योम queue_txd_mb(काष्ठा s_smc *smc, SMbuf *mb)
अणु
	DB_GEN(4, "_rx: queue_txd_mb = %p", mb);
	smc->os.hwm.queued_txd_mb++ ;
	mb->sm_next = (SMbuf *)शून्य ;
	अगर (smc->os.hwm.txd_tx_pipe == शून्य) अणु
		smc->os.hwm.txd_tx_pipe = mb ;
	पूर्ण
	अन्यथा अणु
		smc->os.hwm.txd_tx_tail->sm_next = mb ;
	पूर्ण
	smc->os.hwm.txd_tx_tail = mb ;
पूर्ण

/*
 * get a SMbuf from the txd_tx_queue
 */
अटल SMbuf *get_txd_mb(काष्ठा s_smc *smc)
अणु
	SMbuf *mb ;

	अगर ((mb = smc->os.hwm.txd_tx_pipe)) अणु
		smc->os.hwm.queued_txd_mb-- ;
		smc->os.hwm.txd_tx_pipe = mb->sm_next ;
	पूर्ण
	DB_GEN(4, "get_txd_mb: mb = 0x%p", mb);
	वापस mb;
पूर्ण

/*
 *	SMT Send function
 */
व्योम smt_send_mbuf(काष्ठा s_smc *smc, SMbuf *mb, पूर्णांक fc)
अणु
	अक्षर far *data ;
	पूर्णांक	len ;
	पूर्णांक	n ;
	पूर्णांक	i ;
	पूर्णांक	frag_count ;
	पूर्णांक	frame_status ;
	SK_LOC_DECL(अक्षर far,*virt[3]) ;
	पूर्णांक	frag_len[3] ;
	काष्ठा s_smt_tx_queue *queue ;
	काष्ठा s_smt_fp_txd अस्थिर *t ;
	u_दीर्घ	phys ;
	__le32	tbctrl;

	NDD_TRACE("THSB",mb,fc,0) ;
	DB_TX(4, "smt_send_mbuf: mb = 0x%p, fc = 0x%x", mb, fc);

	mb->sm_off-- ;	/* set to fc */
	mb->sm_len++ ;	/* + fc */
	data = smtod(mb,अक्षर *) ;
	*data = fc ;
	अगर (fc == FC_SMT_LOC)
		*data = FC_SMT_INFO ;

	/*
	 * determine the frag count and the virt addresses of the frags
	 */
	frag_count = 0 ;
	len = mb->sm_len ;
	जबतक (len) अणु
		n = SMT_PAGESIZE - ((दीर्घ)data & (SMT_PAGESIZE-1)) ;
		अगर (n >= len) अणु
			n = len ;
		पूर्ण
		DB_TX(5, "frag: virt/len = 0x%p/%d", data, n);
		virt[frag_count] = data ;
		frag_len[frag_count] = n ;
		frag_count++ ;
		len -= n ;
		data += n ;
	पूर्ण

	/*
	 * determine the frame status
	 */
	queue = smc->hw.fp.tx[QUEUE_A0] ;
	अगर (fc == FC_BEACON || fc == FC_SMT_LOC) अणु
		frame_status = LOC_TX ;
	पूर्ण
	अन्यथा अणु
		frame_status = LAN_TX ;
		अगर ((smc->os.hwm.pass_NSA &&(fc == FC_SMT_NSA)) ||
		   (smc->os.hwm.pass_SMT &&(fc == FC_SMT_INFO)))
			frame_status |= LOC_TX ;
	पूर्ण

	अगर (!smc->hw.mac_ring_is_up || frag_count > queue->tx_मुक्त) अणु
		frame_status &= ~LAN_TX;
		अगर (frame_status) अणु
			DB_TX(2, "Ring is down: terminate LAN_TX");
		पूर्ण
		अन्यथा अणु
			DB_TX(2, "Ring is down: terminate transmission");
			smt_मुक्त_mbuf(smc,mb) ;
			वापस ;
		पूर्ण
	पूर्ण
	DB_TX(5, "frame_status = 0x%x", frame_status);

	अगर ((frame_status & LAN_TX) && (frame_status & LOC_TX)) अणु
		mb->sm_use_count = 2 ;
	पूर्ण

	अगर (frame_status & LAN_TX) अणु
		t = queue->tx_curr_put ;
		frame_status |= FIRST_FRAG ;
		क्रम (i = 0; i < frag_count; i++) अणु
			DB_TX(5, "init TxD = 0x%p", t);
			अगर (i == frag_count-1) अणु
				frame_status |= LAST_FRAG ;
				t->txd_txdscr = cpu_to_le32(TX_DESCRIPTOR |
					(((__u32)(mb->sm_len-1)&3) << 27)) ;
			पूर्ण
			t->txd_virt = virt[i] ;
			phys = dma_master(smc, (व्योम far *)virt[i],
				frag_len[i], DMA_RD|SMT_BUF) ;
			t->txd_tbadr = cpu_to_le32(phys) ;
			tbctrl = cpu_to_le32((((__u32)frame_status &
				(FIRST_FRAG|LAST_FRAG)) << 26) |
				BMU_OWN | BMU_CHECK | BMU_SMT_TX |frag_len[i]) ;
			t->txd_tbctrl = tbctrl ;
#अगर_अघोषित	AIX
			DRV_BUF_FLUSH(t,DDI_DMA_SYNC_FORDEV) ;
			outpd(queue->tx_bmu_ctl,CSR_START) ;
#अन्यथा
			DRV_BUF_FLUSH(t,DDI_DMA_SYNC_FORDEV) ;
			outpd(ADDR(B0_XA_CSR),CSR_START) ;
#पूर्ण_अगर
			frame_status &= ~FIRST_FRAG ;
			queue->tx_curr_put = t = t->txd_next ;
			queue->tx_मुक्त-- ;
			queue->tx_used++ ;
		पूर्ण
		smc->mib.m[MAC0].fddiMACTransmit_Ct++ ;
		queue_txd_mb(smc,mb) ;
	पूर्ण

	अगर (frame_status & LOC_TX) अणु
		DB_TX(5, "pass Mbuf to LLC queue");
		queue_llc_rx(smc,mb) ;
	पूर्ण

	/*
	 * We need to unqueue the मुक्त SMT_MBUFs here, because it may
	 * be that the SMT want's to send more than 1 frame क्रम one करोwn call
	 */
	mac_drv_clear_txd(smc) ;
	NDD_TRACE("THSE",t,queue->tx_मुक्त,frag_count) ;
पूर्ण

/*	BEGIN_MANUAL_ENTRY(mac_drv_clear_txd)
 *	व्योम mac_drv_clear_txd(smc)
 *
 * function	DOWNCALL	(hardware module, hwmपंचांग.c)
 *		mac_drv_clear_txd searches in both send queues क्रम TxD's
 *		which were finished by the adapter. It calls dma_complete
 *		क्रम each TxD. If the last fragment of an LLC frame is
 *		reached, it calls mac_drv_tx_complete to release the
 *		send buffer.
 *
 * वापस	nothing
 *
 *	END_MANUAL_ENTRY
 */
अटल व्योम mac_drv_clear_txd(काष्ठा s_smc *smc)
अणु
	काष्ठा s_smt_tx_queue *queue ;
	काष्ठा s_smt_fp_txd अस्थिर *t1 ;
	काष्ठा s_smt_fp_txd अस्थिर *t2 = शून्य ;
	SMbuf *mb ;
	u_दीर्घ	tbctrl ;
	पूर्णांक i ;
	पूर्णांक frag_count ;
	पूर्णांक n ;

	NDD_TRACE("THcB",0,0,0) ;
	क्रम (i = QUEUE_S; i <= QUEUE_A0; i++) अणु
		queue = smc->hw.fp.tx[i] ;
		t1 = queue->tx_curr_get ;
		DB_TX(5, "clear_txd: QUEUE = %d (0=sync/1=async)", i);

		क्रम ( ; ; ) अणु
			frag_count = 0 ;

			करो अणु
				DRV_BUF_FLUSH(t1,DDI_DMA_SYNC_FORCPU) ;
				DB_TX(5, "check OWN/EOF bit of TxD 0x%p", t1);
				tbctrl = le32_to_cpu(CR_READ(t1->txd_tbctrl));

				अगर (tbctrl & BMU_OWN || !queue->tx_used)अणु
					DB_TX(4, "End of TxDs queue %d", i);
					जाओ मुक्त_next_queue ;	/* next queue */
				पूर्ण
				t1 = t1->txd_next ;
				frag_count++ ;
			पूर्ण जबतक (!(tbctrl & BMU_खातापूर्ण)) ;

			t1 = queue->tx_curr_get ;
			क्रम (n = frag_count; n; n--) अणु
				tbctrl = le32_to_cpu(t1->txd_tbctrl) ;
				dma_complete(smc,
					(जोड़ s_fp_descr अस्थिर *) t1,
					(पूर्णांक) (DMA_RD |
					((tbctrl & BMU_SMT_TX) >> 18))) ;
				t2 = t1 ;
				t1 = t1->txd_next ;
			पूर्ण

			अगर (tbctrl & BMU_SMT_TX) अणु
				mb = get_txd_mb(smc) ;
				smt_मुक्त_mbuf(smc,mb) ;
			पूर्ण
			अन्यथा अणु
#अगर_अघोषित PASS_1ST_TXD_2_TX_COMP
				DB_TX(4, "mac_drv_tx_comp for TxD 0x%p", t2);
				mac_drv_tx_complete(smc,t2) ;
#अन्यथा
				DB_TX(4, "mac_drv_tx_comp for TxD 0x%x",
				      queue->tx_curr_get);
				mac_drv_tx_complete(smc,queue->tx_curr_get) ;
#पूर्ण_अगर
			पूर्ण
			queue->tx_curr_get = t1 ;
			queue->tx_मुक्त += frag_count ;
			queue->tx_used -= frag_count ;
		पूर्ण
मुक्त_next_queue: ;
	पूर्ण
	NDD_TRACE("THcE",0,0,0) ;
पूर्ण

/*
 *	BEGINN_MANUAL_ENTRY(mac_drv_clear_tx_queue)
 *
 * व्योम mac_drv_clear_tx_queue(smc)
 * काष्ठा s_smc *smc ;
 *
 * function	DOWNCALL	(hardware module, hwmपंचांग.c)
 *		mac_drv_clear_tx_queue is called from the SMT when
 *		the RMT state machine has entered the ISOLATE state.
 *		This function is also called by the os-specअगरic module
 *		after it has called the function card_stop().
 *		In this हाल, the frames in the send queues are obsolete and
 *		should be हटाओd.
 *
 * note		calling sequence:
 *		CLI_FBI(), card_stop(),
 *		mac_drv_clear_tx_queue(), mac_drv_clear_rx_queue(),
 *
 * NOTE:	The caller is responsible that the BMUs are idle
 *		when this function is called.
 *
 *	END_MANUAL_ENTRY
 */
व्योम mac_drv_clear_tx_queue(काष्ठा s_smc *smc)
अणु
	काष्ठा s_smt_fp_txd अस्थिर *t ;
	काष्ठा s_smt_tx_queue *queue ;
	पूर्णांक tx_used ;
	पूर्णांक i ;

	अगर (smc->hw.hw_state != STOPPED) अणु
		SK_BREAK() ;
		SMT_PANIC(smc,HWM_E0011,HWM_E0011_MSG) ;
		वापस ;
	पूर्ण

	क्रम (i = QUEUE_S; i <= QUEUE_A0; i++) अणु
		queue = smc->hw.fp.tx[i] ;
		DB_TX(5, "clear_tx_queue: QUEUE = %d (0=sync/1=async)", i);

		/*
		 * चयन the OWN bit of all pending frames to the host
		 */
		t = queue->tx_curr_get ;
		tx_used = queue->tx_used ;
		जबतक (tx_used) अणु
			DRV_BUF_FLUSH(t,DDI_DMA_SYNC_FORCPU) ;
			DB_TX(5, "switch OWN bit of TxD 0x%p", t);
			t->txd_tbctrl &= ~cpu_to_le32(BMU_OWN) ;
			DRV_BUF_FLUSH(t,DDI_DMA_SYNC_FORDEV) ;
			t = t->txd_next ;
			tx_used-- ;
		पूर्ण
	पूर्ण

	/*
	 * release all TxD's क्रम both send queues
	 */
	mac_drv_clear_txd(smc) ;

	क्रम (i = QUEUE_S; i <= QUEUE_A0; i++) अणु
		queue = smc->hw.fp.tx[i] ;
		t = queue->tx_curr_get ;

		/*
		 * ग_लिखो the phys poपूर्णांकer of the NEXT descriptor पूर्णांकo the
		 * BMU's current address descriptor poपूर्णांकer and set
		 * tx_curr_get and tx_curr_put to this position
		 */
		अगर (i == QUEUE_S) अणु
			outpd(ADDR(B5_XS_DA),le32_to_cpu(t->txd_ntdadr)) ;
		पूर्ण
		अन्यथा अणु
			outpd(ADDR(B5_XA_DA),le32_to_cpu(t->txd_ntdadr)) ;
		पूर्ण

		queue->tx_curr_put = queue->tx_curr_get->txd_next ;
		queue->tx_curr_get = queue->tx_curr_put ;
	पूर्ण
पूर्ण


/*
	-------------------------------------------------------------
	TEST FUNCTIONS:
	-------------------------------------------------------------
*/

#अगर_घोषित	DEBUG
/*
 *	BEGIN_MANUAL_ENTRY(mac_drv_debug_lev)
 *	व्योम mac_drv_debug_lev(smc,flag,lev)
 *
 * function	DOWNCALL	(drvsr.c)
 *		To get a special debug info the user can assign a debug level
 *		to any debug flag.
 *
 * para	flag	debug flag, possible values are:
 *			= 0:	reset all debug flags (the defined level is
 *				ignored)
 *			= 1:	debug.d_smtf
 *			= 2:	debug.d_smt
 *			= 3:	debug.d_ecm
 *			= 4:	debug.d_rmt
 *			= 5:	debug.d_cfm
 *			= 6:	debug.d_pcm
 *
 *			= 10:	debug.d_os.hwm_rx (hardware module receive path)
 *			= 11:	debug.d_os.hwm_tx(hardware module transmit path)
 *			= 12:	debug.d_os.hwm_gen(hardware module general flag)
 *
 *	lev	debug level
 *
 *	END_MANUAL_ENTRY
 */
व्योम mac_drv_debug_lev(काष्ठा s_smc *smc, पूर्णांक flag, पूर्णांक lev)
अणु
	चयन(flag) अणु
	हाल (पूर्णांक)शून्य:
		DB_P.d_smtf = DB_P.d_smt = DB_P.d_ecm = DB_P.d_rmt = 0 ;
		DB_P.d_cfm = 0 ;
		DB_P.d_os.hwm_rx = DB_P.d_os.hwm_tx = DB_P.d_os.hwm_gen = 0 ;
#अगर_घोषित	SBA
		DB_P.d_sba = 0 ;
#पूर्ण_अगर
#अगर_घोषित	ESS
		DB_P.d_ess = 0 ;
#पूर्ण_अगर
		अवरोध ;
	हाल DEBUG_SMTF:
		DB_P.d_smtf = lev ;
		अवरोध ;
	हाल DEBUG_SMT:
		DB_P.d_smt = lev ;
		अवरोध ;
	हाल DEBUG_ECM:
		DB_P.d_ecm = lev ;
		अवरोध ;
	हाल DEBUG_RMT:
		DB_P.d_rmt = lev ;
		अवरोध ;
	हाल DEBUG_CFM:
		DB_P.d_cfm = lev ;
		अवरोध ;
	हाल DEBUG_PCM:
		DB_P.d_pcm = lev ;
		अवरोध ;
	हाल DEBUG_SBA:
#अगर_घोषित	SBA
		DB_P.d_sba = lev ;
#पूर्ण_अगर
		अवरोध ;
	हाल DEBUG_ESS:
#अगर_घोषित	ESS
		DB_P.d_ess = lev ;
#पूर्ण_अगर
		अवरोध ;
	हाल DB_HWM_RX:
		DB_P.d_os.hwm_rx = lev ;
		अवरोध ;
	हाल DB_HWM_TX:
		DB_P.d_os.hwm_tx = lev ;
		अवरोध ;
	हाल DB_HWM_GEN:
		DB_P.d_os.hwm_gen = lev ;
		अवरोध ;
	शेष:
		अवरोध ;
	पूर्ण
पूर्ण
#पूर्ण_अगर
