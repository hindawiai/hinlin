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

#अगर_अघोषित	_HWM_
#घोषणा	_HWM_

#समावेश "mbuf.h"

/*
 * MACRO क्रम DMA synchronization:
 *	The descriptor 'desc' is flushed for the device 'flag'.
 *	Devices are the CPU (DDI_DMA_SYNC_FORCPU) and the
 *	adapter (DDI_DMA_SYNC_FORDEV).
 *
 *	'desc'	Poपूर्णांकer to a Rx or Tx descriptor.
 *	'flag'	Flag क्रम direction (view क्रम CPU or DEVICE) that
 *		should be synchronized.
 *
 *	Empty macros and defines are specअगरied here. The real macro
 *	is os-specअगरic and should be defined in osdef1st.h.
 */
#अगर_अघोषित DRV_BUF_FLUSH
#घोषणा DRV_BUF_FLUSH(desc,flag)
#घोषणा DDI_DMA_SYNC_FORCPU
#घोषणा DDI_DMA_SYNC_FORDEV
#पूर्ण_अगर

	/*
	 * hardware modul dependent receive modes
	 */
#घोषणा	RX_ENABLE_PASS_SMT	21
#घोषणा	RX_DISABLE_PASS_SMT	22
#घोषणा	RX_ENABLE_PASS_NSA	23
#घोषणा	RX_DISABLE_PASS_NSA	24
#घोषणा	RX_ENABLE_PASS_DB	25
#घोषणा	RX_DISABLE_PASS_DB	26
#घोषणा	RX_DISABLE_PASS_ALL	27
#घोषणा	RX_DISABLE_LLC_PROMISC	28
#घोषणा	RX_ENABLE_LLC_PROMISC	29


#अगर_अघोषित	DMA_RD
#घोषणा DMA_RD		1	/* memory -> hw */
#पूर्ण_अगर
#अगर_अघोषित DMA_WR
#घोषणा DMA_WR		2	/* hw -> memory */
#पूर्ण_अगर
#घोषणा SMT_BUF		0x80

	/*
	 * bits of the frame status byte
	 */
#घोषणा EN_IRQ_खातापूर्ण	0x02	/* get IRQ after end of frame transmission */
#घोषणा	LOC_TX		0x04	/* send frame to the local SMT */
#घोषणा LAST_FRAG	0x08	/* last TxD of the frame */
#घोषणा	FIRST_FRAG	0x10	/* first TxD of the frame */
#घोषणा	LAN_TX		0x20	/* send frame to network अगर set */
#घोषणा RING_DOWN	0x40	/* error: unable to send, ring करोwn */
#घोषणा OUT_OF_TXD	0x80	/* error: not enough TxDs available */


#अगर_अघोषित शून्य
#घोषणा शून्य 		0
#पूर्ण_अगर

#घोषणा C_INDIC		(1L<<25)
#घोषणा A_INDIC		(1L<<26)
#घोषणा	RD_FS_LOCAL	0x80

	/*
	 * DEBUG FLAGS
	 */
#घोषणा	DEBUG_SMTF	1
#घोषणा	DEBUG_SMT	2
#घोषणा	DEBUG_ECM	3
#घोषणा	DEBUG_RMT	4
#घोषणा	DEBUG_CFM	5
#घोषणा	DEBUG_PCM	6
#घोषणा	DEBUG_SBA	7
#घोषणा	DEBUG_ESS	8

#घोषणा	DB_HWM_RX	10
#घोषणा	DB_HWM_TX	11
#घोषणा DB_HWM_GEN	12

काष्ठा s_mbuf_pool अणु
#अगर_अघोषित	MB_OUTSIDE_SMC
	SMbuf		mb[MAX_MBUF] ;		/* mbuf pool */
#पूर्ण_अगर
	SMbuf		*mb_start ;		/* poपूर्णांकs to the first mb */
	SMbuf		*mb_मुक्त ;		/* मुक्त queue */
पूर्ण ;

काष्ठा hwm_r अणु
	/*
	 * hardware modul specअगरic receive variables
	 */
	u_पूर्णांक			len ;		/* length of the whole frame */
	अक्षर			*mb_pos ;	/* SMbuf receive position */
पूर्ण ;

काष्ठा hw_modul अणु
	/*
	 * All hardware modul specअगरic variables
	 */
	काष्ठा	s_mbuf_pool	mbuf_pool ;
	काष्ठा	hwm_r	r ;

	जोड़ s_fp_descr अस्थिर *descr_p ; /* poपूर्णांकs to the desriptor area */

	u_लघु pass_SMT ;		/* pass SMT frames */
	u_लघु pass_NSA ;		/* pass all NSA frames */
	u_लघु pass_DB ;		/* pass Direct Beacon Frames */
	u_लघु pass_llc_promisc ;	/* pass all llc frames (शेष ON) */

	SMbuf	*llc_rx_pipe ;		/* poपूर्णांकs to the first queued llc fr */
	SMbuf	*llc_rx_tail ;		/* poपूर्णांकs to the last queued llc fr */
	पूर्णांक	queued_rx_frames ;	/* number of queued frames */

	SMbuf	*txd_tx_pipe ;		/* poपूर्णांकs to first mb in the txd ring */
	SMbuf	*txd_tx_tail ;		/* poपूर्णांकs to last mb in the txd ring */
	पूर्णांक	queued_txd_mb ;		/* number of SMT MBufs in txd ring */

	पूर्णांक	rx_अवरोध ;		/* rev. was अवरोधed because ind. off */
	पूर्णांक	leave_isr ;		/* leave fddi_isr immedeately अगर set */
	पूर्णांक	isr_flag ;		/* set, when HWM is entered from isr */
	/*
	 * variables क्रम the current transmit frame
	 */
	काष्ठा s_smt_tx_queue *tx_p ;	/* poपूर्णांकer to the transmit queue */
	u_दीर्घ	tx_descr ;		/* tx descriptor क्रम FORMAC+ */
	पूर्णांक	tx_len ;		/* tx frame length */
	SMbuf	*tx_mb ;		/* SMT tx MBuf poपूर्णांकer */
	अक्षर	*tx_data ;		/* data poपूर्णांकer to the SMT tx Mbuf */

	पूर्णांक	detec_count ;		/* counter क्रम out of RxD condition */
	u_दीर्घ	rx_len_error ;		/* rx len FORMAC != sum of fragments */
पूर्ण ;


/*
 * DEBUG काष्ठाs and macros
 */

#अगर_घोषित	DEBUG
काष्ठा os_debug अणु
	पूर्णांक	hwm_rx ;
	पूर्णांक	hwm_tx ;
	पूर्णांक	hwm_gen ;
पूर्ण ;
#पूर्ण_अगर

#अगर_घोषित	DEBUG
#अगर_घोषित	DEBUG_BRD
#घोषणा	DB_P	smc->debug
#अन्यथा
#घोषणा DB_P	debug
#पूर्ण_अगर

#घोषणा DB_RX(lev, fmt, ...)						\
करो अणु									\
	अगर (DB_P.d_os.hwm_rx >= (lev))					\
		म_लिखो(fmt "\n", ##__VA_ARGS__);			\
पूर्ण जबतक (0)
#घोषणा DB_TX(lev, fmt, ...)						\
करो अणु									\
	अगर (DB_P.d_os.hwm_tx >= (lev))					\
		म_लिखो(fmt "\n", ##__VA_ARGS__);			\
पूर्ण जबतक (0)
#घोषणा DB_GEN(lev, fmt, ...)						\
करो अणु									\
	अगर (DB_P.d_os.hwm_gen >= (lev))					\
		म_लिखो(fmt "\n", ##__VA_ARGS__);			\
पूर्ण जबतक (0)
#अन्यथा	/* DEBUG */
#घोषणा DB_RX(lev, fmt, ...)	no_prपूर्णांकk(fmt "\n", ##__VA_ARGS__)
#घोषणा DB_TX(lev, fmt, ...)	no_prपूर्णांकk(fmt "\n", ##__VA_ARGS__)
#घोषणा DB_GEN(lev, fmt, ...)	no_prपूर्णांकk(fmt "\n", ##__VA_ARGS__)
#पूर्ण_अगर	/* DEBUG */

#अगर_अघोषित	SK_BREAK
#घोषणा	SK_BREAK()
#पूर्ण_अगर


/*
 * HWM Macros
 */

/*
 *	BEGIN_MANUAL_ENTRY(HWM_GET_TX_PHYS)
 *	u_दीर्घ HWM_GET_TX_PHYS(txd)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This macro may be invoked by the OS-specअगरic module to पढ़ो
 *		the physical address of the specअगरied TxD.
 *
 * para	txd	poपूर्णांकer to the TxD
 *
 *	END_MANUAL_ENTRY
 */
#घोषणा	HWM_GET_TX_PHYS(txd)		(u_दीर्घ)AIX_REVERSE((txd)->txd_tbadr)

/*
 *	BEGIN_MANUAL_ENTRY(HWM_GET_TX_LEN)
 *	पूर्णांक HWM_GET_TX_LEN(txd)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This macro may be invoked by the OS-specअगरic module to पढ़ो
 *		the fragment length of the specअगरied TxD
 *
 * para	rxd	poपूर्णांकer to the TxD
 *
 * वापस	the length of the fragment in bytes
 *
 *	END_MANUAL_ENTRY
 */
#घोषणा	HWM_GET_TX_LEN(txd)	((पूर्णांक)AIX_REVERSE((txd)->txd_tbctrl)& RD_LENGTH)

/*
 *	BEGIN_MANUAL_ENTRY(HWM_GET_TX_USED)
 *	txd *HWM_GET_TX_USED(smc,queue)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This macro may be invoked by the OS-specअगरic module to get the
 *		number of used TxDs क्रम the queue, specअगरied by the index.
 *
 * para	queue	the number of the send queue: Can be specअगरied by
 *		QUEUE_A0, QUEUE_S or (frame_status & QUEUE_A0)
 *
 * वापस	number of used TxDs क्रम this send queue
 *
 *	END_MANUAL_ENTRY
 */
#घोषणा	HWM_GET_TX_USED(smc,queue)	(पूर्णांक) (smc)->hw.fp.tx_q[queue].tx_used

/*
 *	BEGIN_MANUAL_ENTRY(HWM_GET_CURR_TXD)
 *	txd *HWM_GET_CURR_TXD(smc,queue)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This macro may be invoked by the OS-specअगरic module to get the
 *		poपूर्णांकer to the TxD which poपूर्णांकs to the current queue put
 *		position.
 *
 * para	queue	the number of the send queue: Can be specअगरied by
 *		QUEUE_A0, QUEUE_S or (frame_status & QUEUE_A0)
 *
 * वापस	poपूर्णांकer to the current TxD
 *
 *	END_MANUAL_ENTRY
 */
#घोषणा	HWM_GET_CURR_TXD(smc,queue)	(काष्ठा s_smt_fp_txd अस्थिर *)\
					(smc)->hw.fp.tx_q[queue].tx_curr_put

/*
 *	BEGIN_MANUAL_ENTRY(HWM_GET_RX_FRAG_LEN)
 *	पूर्णांक HWM_GET_RX_FRAG_LEN(rxd)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This macro may be invoked by the OS-specअगरic module to पढ़ो
 *		the fragment length of the specअगरied RxD
 *
 * para	rxd	poपूर्णांकer to the RxD
 *
 * वापस	the length of the fragment in bytes
 *
 *	END_MANUAL_ENTRY
 */
#घोषणा	HWM_GET_RX_FRAG_LEN(rxd)	((पूर्णांक)AIX_REVERSE((rxd)->rxd_rbctrl)& \
				RD_LENGTH)

/*
 *	BEGIN_MANUAL_ENTRY(HWM_GET_RX_PHYS)
 *	u_दीर्घ HWM_GET_RX_PHYS(rxd)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This macro may be invoked by the OS-specअगरic module to पढ़ो
 *		the physical address of the specअगरied RxD.
 *
 * para	rxd	poपूर्णांकer to the RxD
 *
 * वापस	the RxD's physical poपूर्णांकer to the data fragment
 *
 *	END_MANUAL_ENTRY
 */
#घोषणा	HWM_GET_RX_PHYS(rxd)	(u_दीर्घ)AIX_REVERSE((rxd)->rxd_rbadr)

/*
 *	BEGIN_MANUAL_ENTRY(HWM_GET_RX_USED)
 *	पूर्णांक HWM_GET_RX_USED(smc)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This macro may be invoked by the OS-specअगरic module to get
 *		the count of used RXDs in receive queue 1.
 *
 * वापस	the used RXD count of receive queue 1
 *
 * NOTE: Remember, because of an ASIC bug at least one RXD should be unused
 *	 in the descriptor ring !
 *
 *	END_MANUAL_ENTRY
 */
#घोषणा	HWM_GET_RX_USED(smc)	((पूर्णांक)(smc)->hw.fp.rx_q[QUEUE_R1].rx_used)

/*
 *	BEGIN_MANUAL_ENTRY(HWM_GET_RX_FREE)
 *	पूर्णांक HWM_GET_RX_FREE(smc)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This macro may be invoked by the OS-specअगरic module to get
 *		the rxd_मुक्त count of receive queue 1.
 *
 * वापस	the rxd_मुक्त count of receive queue 1
 *
 *	END_MANUAL_ENTRY
 */
#घोषणा	HWM_GET_RX_FREE(smc)	((पूर्णांक)(smc)->hw.fp.rx_q[QUEUE_R1].rx_मुक्त-1)

/*
 *	BEGIN_MANUAL_ENTRY(HWM_GET_CURR_RXD)
 *	rxd *HWM_GET_CURR_RXD(smc)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This macro may be invoked by the OS-specअगरic module to get the
 *		poपूर्णांकer to the RxD which poपूर्णांकs to the current queue put
 *		position.
 *
 * वापस	poपूर्णांकer to the current RxD
 *
 *	END_MANUAL_ENTRY
 */
#घोषणा	HWM_GET_CURR_RXD(smc)	(काष्ठा s_smt_fp_rxd अस्थिर *)\
				(smc)->hw.fp.rx_q[QUEUE_R1].rx_curr_put

/*
 *	BEGIN_MANUAL_ENTRY(HWM_RX_CHECK)
 *	व्योम HWM_RX_CHECK(smc,low_water)
 *
 * function	MACRO		(hardware module, hwmपंचांग.h)
 *		This macro is invoked by the OS-specअगरic beक्रमe it left the
 *		function mac_drv_rx_complete. This macro calls mac_drv_fill_rxd
 *		अगर the number of used RxDs is equal or lower than the
 *		the given low water mark.
 *
 * para	low_water	low water mark of used RxD's
 *
 *	END_MANUAL_ENTRY
 */
#अगर_अघोषित HWM_NO_FLOW_CTL
#घोषणा	HWM_RX_CHECK(smc,low_water) अणु\
	अगर ((low_water) >= (smc)->hw.fp.rx_q[QUEUE_R1].rx_used) अणु\
		mac_drv_fill_rxd(smc) ;\
	पूर्ण\
पूर्ण
#अन्यथा
#घोषणा	HWM_RX_CHECK(smc,low_water)		mac_drv_fill_rxd(smc)
#पूर्ण_अगर

#अगर_अघोषित	HWM_EBASE
#घोषणा	HWM_EBASE	500
#पूर्ण_अगर

#घोषणा	HWM_E0001	HWM_EBASE + 1
#घोषणा	HWM_E0001_MSG	"HWM: Wrong size of s_rxd_os struct"
#घोषणा	HWM_E0002	HWM_EBASE + 2
#घोषणा	HWM_E0002_MSG	"HWM: Wrong size of s_txd_os struct"
#घोषणा	HWM_E0003	HWM_EBASE + 3
#घोषणा	HWM_E0003_MSG	"HWM: smt_free_mbuf() called with NULL pointer"
#घोषणा	HWM_E0004	HWM_EBASE + 4
#घोषणा	HWM_E0004_MSG	"HWM: Parity error rx queue 1"
#घोषणा	HWM_E0005	HWM_EBASE + 5
#घोषणा	HWM_E0005_MSG	"HWM: Encoding error rx queue 1"
#घोषणा	HWM_E0006	HWM_EBASE + 6
#घोषणा	HWM_E0006_MSG	"HWM: Encoding error async tx queue"
#घोषणा	HWM_E0007	HWM_EBASE + 7
#घोषणा	HWM_E0007_MSG	"HWM: Encoding error sync tx queue"
#घोषणा	HWM_E0008	HWM_EBASE + 8
#घोषणा	HWM_E0008_MSG	""
#घोषणा	HWM_E0009	HWM_EBASE + 9
#घोषणा	HWM_E0009_MSG	"HWM: Out of RxD condition detected"
#घोषणा	HWM_E0010	HWM_EBASE + 10
#घोषणा	HWM_E0010_MSG	"HWM: A protocol layer has tried to send a frame with an invalid frame control"
#घोषणा HWM_E0011	HWM_EBASE + 11
#घोषणा HWM_E0011_MSG	"HWM: mac_drv_clear_tx_queue was called although the hardware wasn't stopped"
#घोषणा HWM_E0012	HWM_EBASE + 12
#घोषणा HWM_E0012_MSG	"HWM: mac_drv_clear_rx_queue was called although the hardware wasn't stopped"
#घोषणा HWM_E0013	HWM_EBASE + 13
#घोषणा HWM_E0013_MSG	"HWM: mac_drv_repair_descr was called although the hardware wasn't stopped"

#पूर्ण_अगर
