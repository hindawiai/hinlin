<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
 *
 * This driver is derived from the Linux sym53c8xx driver.
 * Copyright (C) 1998-2000  Gerard Roudier
 *
 * The sym53c8xx driver is derived from the ncr53c8xx driver that had been 
 * a port of the FreeBSD ncr driver to Linux-1.2.13.
 *
 * The original ncr driver has been written क्रम 386bsd and FreeBSD by
 *         Wolfgang Stanglmeier        <wolf@cologne.de>
 *         Stefan Esser                <se@mi.Uni-Koeln.de>
 * Copyright (C) 1994  Wolfgang Stanglmeier
 *
 * Other major contributions:
 *
 * NVRAM detection and पढ़ोing.
 * Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#समावेश <linux/gfp.h>

#अगर_अघोषित SYM_HIPD_H
#घोषणा SYM_HIPD_H

/*
 *  Generic driver options.
 *
 *  They may be defined in platक्रमm specअगरic headers, अगर they 
 *  are useful.
 *
 *    SYM_OPT_HANDLE_DEVICE_QUEUEING
 *        When this option is set, the driver will use a queue per 
 *        device and handle QUEUE FULL status requeuing पूर्णांकernally.
 *
 *    SYM_OPT_LIMIT_COMMAND_REORDERING
 *        When this option is set, the driver tries to limit tagged 
 *        command reordering to some reasonable value.
 *        (set क्रम Linux)
 */
#अगर 0
#घोषणा SYM_OPT_HANDLE_DEVICE_QUEUEING
#घोषणा SYM_OPT_LIMIT_COMMAND_REORDERING
#पूर्ण_अगर

/*
 *  Active debugging tags and verbosity.
 *  Both DEBUG_FLAGS and sym_verbose can be redefined 
 *  by the platक्रमm specअगरic code to something अन्यथा.
 */
#घोषणा DEBUG_ALLOC	(0x0001)
#घोषणा DEBUG_PHASE	(0x0002)
#घोषणा DEBUG_POLL	(0x0004)
#घोषणा DEBUG_QUEUE	(0x0008)
#घोषणा DEBUG_RESULT	(0x0010)
#घोषणा DEBUG_SCATTER	(0x0020)
#घोषणा DEBUG_SCRIPT	(0x0040)
#घोषणा DEBUG_TINY	(0x0080)
#घोषणा DEBUG_TIMING	(0x0100)
#घोषणा DEBUG_NEGO	(0x0200)
#घोषणा DEBUG_TAGS	(0x0400)
#घोषणा DEBUG_POINTER	(0x0800)

#अगर_अघोषित DEBUG_FLAGS
#घोषणा DEBUG_FLAGS	(0x0000)
#पूर्ण_अगर

#अगर_अघोषित sym_verbose
#घोषणा sym_verbose	(np->verbose)
#पूर्ण_अगर

/*
 *  These ones should have been alपढ़ोy defined.
 */
#अगर_अघोषित निश्चित
#घोषणा	निश्चित(expression) अणु \
	अगर (!(expression)) अणु \
		(व्योम)panic( \
			"assertion \"%s\" failed: file \"%s\", line %d\n", \
			#expression, \
			__खाता__, __LINE__); \
	पूर्ण \
पूर्ण
#पूर्ण_अगर

/*
 *  Number of tasks per device we want to handle.
 */
#अगर	SYM_CONF_MAX_TAG_ORDER > 8
#त्रुटि	"more than 256 tags per logical unit not allowed."
#पूर्ण_अगर
#घोषणा	SYM_CONF_MAX_TASK	(1<<SYM_CONF_MAX_TAG_ORDER)

/*
 *  Donnot use more tasks that we can handle.
 */
#अगर_अघोषित	SYM_CONF_MAX_TAG
#घोषणा	SYM_CONF_MAX_TAG	SYM_CONF_MAX_TASK
#पूर्ण_अगर
#अगर	SYM_CONF_MAX_TAG > SYM_CONF_MAX_TASK
#अघोषित	SYM_CONF_MAX_TAG
#घोषणा	SYM_CONF_MAX_TAG	SYM_CONF_MAX_TASK
#पूर्ण_अगर

/*
 *    This one means 'NO TAG for this job'
 */
#घोषणा NO_TAG	(256)

/*
 *  Number of SCSI tarमाला_लो.
 */
#अगर	SYM_CONF_MAX_TARGET > 16
#त्रुटि	"more than 16 targets not allowed."
#पूर्ण_अगर

/*
 *  Number of logical units per target.
 */
#अगर	SYM_CONF_MAX_LUN > 64
#त्रुटि	"more than 64 logical units per target not allowed."
#पूर्ण_अगर

/*
 *    Asynchronous pre-scaler (ns). Shall be 40 क्रम 
 *    the SCSI timings to be compliant.
 */
#घोषणा	SYM_CONF_MIN_ASYNC (40)


/*
 * MEMORY ALLOCATOR.
 */

#घोषणा SYM_MEM_WARN	1	/* Warn on failed operations */

#घोषणा SYM_MEM_PAGE_ORDER 0	/* 1 PAGE  maximum */
#घोषणा SYM_MEM_CLUSTER_SHIFT	(PAGE_SHIFT+SYM_MEM_PAGE_ORDER)
#घोषणा SYM_MEM_FREE_UNUSED	/* Free unused pages immediately */
/*
 *  Shortest memory chunk is (1<<SYM_MEM_SHIFT), currently 16.
 *  Actual allocations happen as SYM_MEM_CLUSTER_SIZE sized.
 *  (1 PAGE at a समय is just fine).
 */
#घोषणा SYM_MEM_SHIFT	4
#घोषणा SYM_MEM_CLUSTER_SIZE	(1UL << SYM_MEM_CLUSTER_SHIFT)
#घोषणा SYM_MEM_CLUSTER_MASK	(SYM_MEM_CLUSTER_SIZE-1)

/*
 *  Number of entries in the START and DONE queues.
 *
 *  We limit to 1 PAGE in order to succeed allocation of 
 *  these queues. Each entry is 8 bytes दीर्घ (2 DWORDS).
 */
#अगर_घोषित	SYM_CONF_MAX_START
#घोषणा	SYM_CONF_MAX_QUEUE (SYM_CONF_MAX_START+2)
#अन्यथा
#घोषणा	SYM_CONF_MAX_QUEUE (7*SYM_CONF_MAX_TASK+2)
#घोषणा	SYM_CONF_MAX_START (SYM_CONF_MAX_QUEUE-2)
#पूर्ण_अगर

#अगर	SYM_CONF_MAX_QUEUE > SYM_MEM_CLUSTER_SIZE/8
#अघोषित	SYM_CONF_MAX_QUEUE
#घोषणा	SYM_CONF_MAX_QUEUE (SYM_MEM_CLUSTER_SIZE/8)
#अघोषित	SYM_CONF_MAX_START
#घोषणा	SYM_CONF_MAX_START (SYM_CONF_MAX_QUEUE-2)
#पूर्ण_अगर

/*
 *  For this one, we want a लघु name :-)
 */
#घोषणा MAX_QUEUE	SYM_CONF_MAX_QUEUE

/*
 *  Common definitions क्रम both bus space based and legacy IO methods.
 */

#घोषणा INB_OFF(np, o)		ioपढ़ो8(np->s.ioaddr + (o))
#घोषणा INW_OFF(np, o)		ioपढ़ो16(np->s.ioaddr + (o))
#घोषणा INL_OFF(np, o)		ioपढ़ो32(np->s.ioaddr + (o))

#घोषणा OUTB_OFF(np, o, val)	ioग_लिखो8((val), np->s.ioaddr + (o))
#घोषणा OUTW_OFF(np, o, val)	ioग_लिखो16((val), np->s.ioaddr + (o))
#घोषणा OUTL_OFF(np, o, val)	ioग_लिखो32((val), np->s.ioaddr + (o))

#घोषणा INB(np, r)		INB_OFF(np, दुरत्व(काष्ठा sym_reg, r))
#घोषणा INW(np, r)		INW_OFF(np, दुरत्व(काष्ठा sym_reg, r))
#घोषणा INL(np, r)		INL_OFF(np, दुरत्व(काष्ठा sym_reg, r))

#घोषणा OUTB(np, r, v)		OUTB_OFF(np, दुरत्व(काष्ठा sym_reg, r), (v))
#घोषणा OUTW(np, r, v)		OUTW_OFF(np, दुरत्व(काष्ठा sym_reg, r), (v))
#घोषणा OUTL(np, r, v)		OUTL_OFF(np, दुरत्व(काष्ठा sym_reg, r), (v))

#घोषणा OUTONB(np, r, m)	OUTB(np, r, INB(np, r) | (m))
#घोषणा OUTOFFB(np, r, m)	OUTB(np, r, INB(np, r) & ~(m))
#घोषणा OUTONW(np, r, m)	OUTW(np, r, INW(np, r) | (m))
#घोषणा OUTOFFW(np, r, m)	OUTW(np, r, INW(np, r) & ~(m))
#घोषणा OUTONL(np, r, m)	OUTL(np, r, INL(np, r) | (m))
#घोषणा OUTOFFL(np, r, m)	OUTL(np, r, INL(np, r) & ~(m))

/*
 *  We normally want the chip to have a consistent view
 *  of driver पूर्णांकernal data काष्ठाures when we restart it.
 *  Thus these macros.
 */
#घोषणा OUTL_DSP(np, v)				\
	करो अणु					\
		MEMORY_WRITE_BARRIER();		\
		OUTL(np, nc_dsp, (v));		\
	पूर्ण जबतक (0)

#घोषणा OUTONB_STD()				\
	करो अणु					\
		MEMORY_WRITE_BARRIER();		\
		OUTONB(np, nc_dcntl, (STD|NOCOM));	\
	पूर्ण जबतक (0)

/*
 *  Command control block states.
 */
#घोषणा HS_IDLE		(0)
#घोषणा HS_BUSY		(1)
#घोषणा HS_NEGOTIATE	(2)	/* sync/wide data transfer*/
#घोषणा HS_DISCONNECT	(3)	/* Disconnected by target */
#घोषणा HS_WAIT		(4)	/* रुकोing क्रम resource	  */

#घोषणा HS_DONEMASK	(0x80)
#घोषणा HS_COMPLETE	(4|HS_DONEMASK)
#घोषणा HS_SEL_TIMEOUT	(5|HS_DONEMASK)	/* Selection समयout      */
#घोषणा HS_UNEXPECTED	(6|HS_DONEMASK)	/* Unexpected disconnect  */
#घोषणा HS_COMP_ERR	(7|HS_DONEMASK)	/* Completed with error	  */

/*
 *  Software Interrupt Codes
 */
#घोषणा	SIR_BAD_SCSI_STATUS	(1)
#घोषणा	SIR_SEL_ATN_NO_MSG_OUT	(2)
#घोषणा	SIR_MSG_RECEIVED	(3)
#घोषणा	SIR_MSG_WEIRD		(4)
#घोषणा	SIR_NEGO_FAILED		(5)
#घोषणा	SIR_NEGO_PROTO		(6)
#घोषणा	SIR_SCRIPT_STOPPED	(7)
#घोषणा	SIR_REJECT_TO_SEND	(8)
#घोषणा	SIR_SWIDE_OVERRUN	(9)
#घोषणा	SIR_SODL_UNDERRUN	(10)
#घोषणा	SIR_RESEL_NO_MSG_IN	(11)
#घोषणा	SIR_RESEL_NO_IDENTIFY	(12)
#घोषणा	SIR_RESEL_BAD_LUN	(13)
#घोषणा	SIR_TARGET_SELECTED	(14)
#घोषणा	SIR_RESEL_BAD_I_T_L	(15)
#घोषणा	SIR_RESEL_BAD_I_T_L_Q	(16)
#घोषणा	SIR_ABORT_SENT		(17)
#घोषणा	SIR_RESEL_ABORTED	(18)
#घोषणा	SIR_MSG_OUT_DONE	(19)
#घोषणा	SIR_COMPLETE_ERROR	(20)
#घोषणा	SIR_DATA_OVERRUN	(21)
#घोषणा	SIR_BAD_PHASE		(22)
#अगर	SYM_CONF_DMA_ADDRESSING_MODE == 2
#घोषणा	SIR_DMAP_सूचीTY		(23)
#घोषणा	SIR_MAX			(23)
#अन्यथा
#घोषणा	SIR_MAX			(22)
#पूर्ण_अगर

/*
 *  Extended error bit codes.
 *  xerr_status field of काष्ठा sym_ccb.
 */
#घोषणा	XE_EXTRA_DATA	(1)	/* unexpected data phase	 */
#घोषणा	XE_BAD_PHASE	(1<<1)	/* illegal phase (4/5)		 */
#घोषणा	XE_PARITY_ERR	(1<<2)	/* unrecovered SCSI parity error */
#घोषणा	XE_SODL_UNRUN	(1<<3)	/* ODD transfer in DATA OUT phase */
#घोषणा	XE_SWIDE_OVRUN	(1<<4)	/* ODD transfer in DATA IN phase */

/*
 *  Negotiation status.
 *  nego_status field of काष्ठा sym_ccb.
 */
#घोषणा NS_SYNC		(1)
#घोषणा NS_WIDE		(2)
#घोषणा NS_PPR		(3)

/*
 *  A CCB hashed table is used to retrieve CCB address 
 *  from DSA value.
 */
#घोषणा CCB_HASH_SHIFT		8
#घोषणा CCB_HASH_SIZE		(1UL << CCB_HASH_SHIFT)
#घोषणा CCB_HASH_MASK		(CCB_HASH_SIZE-1)
#अगर 1
#घोषणा CCB_HASH_CODE(dsa)	\
	(((dsa) >> (_LGRU16_(माप(काष्ठा sym_ccb)))) & CCB_HASH_MASK)
#अन्यथा
#घोषणा CCB_HASH_CODE(dsa)	(((dsa) >> 9) & CCB_HASH_MASK)
#पूर्ण_अगर

#अगर	SYM_CONF_DMA_ADDRESSING_MODE == 2
/*
 *  We may want to use segment रेजिस्टरs क्रम 64 bit DMA.
 *  16 segments रेजिस्टरs -> up to 64 GB addressable.
 */
#घोषणा SYM_DMAP_SHIFT	(4)
#घोषणा SYM_DMAP_SIZE	(1u<<SYM_DMAP_SHIFT)
#घोषणा SYM_DMAP_MASK	(SYM_DMAP_SIZE-1)
#पूर्ण_अगर

/*
 *  Device flags.
 */
#घोषणा SYM_DISC_ENABLED	(1)
#घोषणा SYM_TAGS_ENABLED	(1<<1)
#घोषणा SYM_SCAN_BOOT_DISABLED	(1<<2)
#घोषणा SYM_SCAN_LUNS_DISABLED	(1<<3)

/*
 *  Host adapter miscellaneous flags.
 */
#घोषणा SYM_AVOID_BUS_RESET	(1)

/*
 *  Misc.
 */
#घोषणा SYM_SNOOP_TIMEOUT (10000000)
#घोषणा BUS_8_BIT	0
#घोषणा BUS_16_BIT	1

/*
 *  Gather negotiable parameters value
 */
काष्ठा sym_trans अणु
	u8 period;
	u8 offset;
	अचिन्हित पूर्णांक width:1;
	अचिन्हित पूर्णांक iu:1;
	अचिन्हित पूर्णांक dt:1;
	अचिन्हित पूर्णांक qas:1;
	अचिन्हित पूर्णांक check_nego:1;
	अचिन्हित पूर्णांक renego:2;
पूर्ण;

/*
 *  Global TCB HEADER.
 *
 *  Due to lack of indirect addressing on earlier NCR chips,
 *  this subकाष्ठाure is copied from the TCB to a global 
 *  address after selection.
 *  For SYMBIOS chips that support LOAD/STORE this copy is 
 *  not needed and thus not perक्रमmed.
 */
काष्ठा sym_tcbh अणु
	/*
	 *  Scripts bus addresses of LUN table accessed from scripts.
	 *  LUN #0 is a special हाल, since multi-lun devices are rare, 
	 *  and we we want to speed-up the general हाल and not waste 
	 *  resources.
	 */
	u32	luntbl_sa;	/* bus address of this table	*/
	u32	lun0_sa;	/* bus address of LCB #0	*/
	/*
	 *  Actual SYNC/WIDE IO रेजिस्टरs value क्रम this target.
	 *  'sval', 'wval' and 'uval' are पढ़ो from SCRIPTS and 
	 *  so have alignment स्थिरraपूर्णांकs.
	 */
/*0*/	u_अक्षर	uval;		/* -> SCNTL4 रेजिस्टर		*/
/*1*/	u_अक्षर	sval;		/* -> SXFER  io रेजिस्टर	*/
/*2*/	u_अक्षर	filler1;
/*3*/	u_अक्षर	wval;		/* -> SCNTL3 io रेजिस्टर	*/
पूर्ण;

/*
 *  Target Control Block
 */
काष्ठा sym_tcb अणु
	/*
	 *  TCB header.
	 *  Assumed at offset 0.
	 */
/*0*/	काष्ठा sym_tcbh head;

	/*
	 *  LUN table used by the SCRIPTS processor.
	 *  An array of bus addresses is used on reselection.
	 */
	u32	*luntbl;	/* LCBs bus address table	*/
	पूर्णांक	nlcb;		/* Number of valid LCBs (including LUN #0) */

	/*
	 *  LUN table used by the C code.
	 */
	काष्ठा sym_lcb *lun0p;		/* LCB of LUN #0 (usual हाल)	*/
#अगर SYM_CONF_MAX_LUN > 1
	काष्ठा sym_lcb **lunmp;		/* Other LCBs [1..MAX_LUN]	*/
#पूर्ण_अगर

#अगर_घोषित	SYM_HAVE_STCB
	/*
	 *  O/S specअगरic data काष्ठाure.
	 */
	काष्ठा sym_stcb s;
#पूर्ण_अगर

	/* Transfer goal */
	काष्ठा sym_trans tgoal;

	/* Last prपूर्णांकed transfer speed */
	काष्ठा sym_trans tprपूर्णांक;

	/*
	 * Keep track of the CCB used क्रम the negotiation in order
	 * to ensure that only 1 negotiation is queued at a समय.
	 */
	काष्ठा sym_ccb *  nego_cp;	/* CCB used क्रम the nego		*/

	/*
	 *  Set when we want to reset the device.
	 */
	u_अक्षर	to_reset;

	/*
	 *  Other user settable limits and options.
	 *  These limits are पढ़ो from the NVRAM अगर present.
	 */
	अचिन्हित अक्षर	usrflags;
	अचिन्हित अक्षर	usr_period;
	अचिन्हित अक्षर	usr_width;
	अचिन्हित लघु	usrtags;
	काष्ठा scsi_target *starget;
पूर्ण;

/*
 *  Global LCB HEADER.
 *
 *  Due to lack of indirect addressing on earlier NCR chips,
 *  this subकाष्ठाure is copied from the LCB to a global 
 *  address after selection.
 *  For SYMBIOS chips that support LOAD/STORE this copy is 
 *  not needed and thus not perक्रमmed.
 */
काष्ठा sym_lcbh अणु
	/*
	 *  SCRIPTS address jumped by SCRIPTS on reselection.
	 *  For not probed logical units, this address poपूर्णांकs to 
	 *  SCRIPTS that deal with bad LU handling (must be at 
	 *  offset zero of the LCB क्रम that reason).
	 */
/*0*/	u32	resel_sa;

	/*
	 *  Task (bus address of a CCB) पढ़ो from SCRIPTS that poपूर्णांकs 
	 *  to the unique ITL nexus allowed to be disconnected.
	 */
	u32	itl_task_sa;

	/*
	 *  Task table bus address (पढ़ो from SCRIPTS).
	 */
	u32	itlq_tbl_sa;
पूर्ण;

/*
 *  Logical Unit Control Block
 */
काष्ठा sym_lcb अणु
	/*
	 *  TCB header.
	 *  Assumed at offset 0.
	 */
/*0*/	काष्ठा sym_lcbh head;

	/*
	 *  Task table पढ़ो from SCRIPTS that contains poपूर्णांकers to 
	 *  ITLQ nexuses. The bus address पढ़ो from SCRIPTS is 
	 *  inside the header.
	 */
	u32	*itlq_tbl;	/* Kernel भव address	*/

	/*
	 *  Busy CCBs management.
	 */
	u_लघु	busy_itlq;	/* Number of busy tagged CCBs	*/
	u_लघु	busy_itl;	/* Number of busy untagged CCBs	*/

	/*
	 *  Circular tag allocation buffer.
	 */
	u_लघु	ia_tag;		/* Tag allocation index		*/
	u_लघु	अगर_tag;		/* Tag release index		*/
	u_अक्षर	*cb_tags;	/* Circular tags buffer		*/

	/*
	 *  O/S specअगरic data काष्ठाure.
	 */
#अगर_घोषित	SYM_HAVE_SLCB
	काष्ठा sym_slcb s;
#पूर्ण_अगर

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	/*
	 *  Optionnaly the driver can handle device queueing, 
	 *  and requeues पूर्णांकernally command to reकरो.
	 */
	SYM_QUEHEAD रुकोing_ccbq;
	SYM_QUEHEAD started_ccbq;
	पूर्णांक	num_sgood;
	u_लघु	started_tags;
	u_लघु	started_no_tag;
	u_लघु	started_max;
	u_लघु	started_limit;
#पूर्ण_अगर

#अगर_घोषित SYM_OPT_LIMIT_COMMAND_REORDERING
	/*
	 *  Optionally the driver can try to prevent SCSI 
	 *  IOs from being reordered too much.
	 */
	u_अक्षर		tags_si;	/* Current index to tags sum	*/
	u_लघु		tags_sum[2];	/* Tags sum counters		*/
	u_लघु		tags_since;	/* # of tags since last चयन	*/
#पूर्ण_अगर

	/*
	 *  Set when we want to clear all tasks.
	 */
	u_अक्षर to_clear;

	/*
	 *  Capabilities.
	 */
	u_अक्षर	user_flags;
	u_अक्षर	curr_flags;
पूर्ण;

/*
 *  Action from SCRIPTS on a task.
 *  Is part of the CCB, but is also used separately to plug 
 *  error handling action to perक्रमm from SCRIPTS.
 */
काष्ठा sym_actscr अणु
	u32	start;		/* Jumped by SCRIPTS after selection	*/
	u32	restart;	/* Jumped by SCRIPTS on relection	*/
पूर्ण;

/*
 *  Phase mismatch context.
 *
 *  It is part of the CCB and is used as parameters क्रम the 
 *  DATA poपूर्णांकer. We need two contexts to handle correctly the 
 *  SAVED DATA POINTER.
 */
काष्ठा sym_pmc अणु
	काष्ठा	sym_tblmove sg;	/* Updated पूर्णांकerrupted SG block	*/
	u32	ret;		/* SCRIPT वापस address	*/
पूर्ण;

/*
 *  LUN control block lookup.
 *  We use a direct poपूर्णांकer क्रम LUN #0, and a table of 
 *  poपूर्णांकers which is only allocated क्रम devices that support 
 *  LUN(s) > 0.
 */
#अगर SYM_CONF_MAX_LUN <= 1
#घोषणा sym_lp(tp, lun) (!lun) ? (tp)->lun0p : शून्य
#अन्यथा
#घोषणा sym_lp(tp, lun) \
	(!lun) ? (tp)->lun0p : (tp)->lunmp ? (tp)->lunmp[((u8)lun)] : शून्य
#पूर्ण_अगर

/*
 *  Status are used by the host and the script processor.
 *
 *  The last four bytes (status[4]) are copied to the 
 *  scratchb रेजिस्टर (declared as scr0..scr3) just after the 
 *  select/reselect, and copied back just after disconnecting.
 *  Inside the script the XX_REG are used.
 */

/*
 *  Last four bytes (script)
 */
#घोषणा  HX_REG	scr0
#घोषणा  HX_PRT	nc_scr0
#घोषणा  HS_REG	scr1
#घोषणा  HS_PRT	nc_scr1
#घोषणा  SS_REG	scr2
#घोषणा  SS_PRT	nc_scr2
#घोषणा  HF_REG	scr3
#घोषणा  HF_PRT	nc_scr3

/*
 *  Last four bytes (host)
 */
#घोषणा  host_xflags   phys.head.status[0]
#घोषणा  host_status   phys.head.status[1]
#घोषणा  ssss_status   phys.head.status[2]
#घोषणा  host_flags    phys.head.status[3]

/*
 *  Host flags
 */
#घोषणा HF_IN_PM0	1u
#घोषणा HF_IN_PM1	(1u<<1)
#घोषणा HF_ACT_PM	(1u<<2)
#घोषणा HF_DP_SAVED	(1u<<3)
#घोषणा HF_SENSE	(1u<<4)
#घोषणा HF_EXT_ERR	(1u<<5)
#घोषणा HF_DATA_IN	(1u<<6)
#अगर_घोषित SYM_CONF_IARB_SUPPORT
#घोषणा HF_HINT_IARB	(1u<<7)
#पूर्ण_अगर

/*
 *  More host flags
 */
#अगर	SYM_CONF_DMA_ADDRESSING_MODE == 2
#घोषणा	HX_DMAP_सूचीTY	(1u<<7)
#पूर्ण_अगर

/*
 *  Global CCB HEADER.
 *
 *  Due to lack of indirect addressing on earlier NCR chips,
 *  this subकाष्ठाure is copied from the ccb to a global 
 *  address after selection (or reselection) and copied back 
 *  beक्रमe disconnect.
 *  For SYMBIOS chips that support LOAD/STORE this copy is 
 *  not needed and thus not perक्रमmed.
 */

काष्ठा sym_ccbh अणु
	/*
	 *  Start and restart SCRIPTS addresses (must be at 0).
	 */
/*0*/	काष्ठा sym_actscr go;

	/*
	 *  SCRIPTS jump address that deal with data poपूर्णांकers.
	 *  'savep' poपूर्णांकs to the position in the script responsible 
	 *  क्रम the actual transfer of data.
	 *  It's written on reception of a SAVE_DATA_POINTER message.
	 */
	u32	savep;		/* Jump address to saved data poपूर्णांकer	*/
	u32	lastp;		/* SCRIPTS address at end of data	*/

	/*
	 *  Status fields.
	 */
	u8	status[4];
पूर्ण;

/*
 *  GET/SET the value of the data poपूर्णांकer used by SCRIPTS.
 *
 *  We must distinguish between the LOAD/STORE-based SCRIPTS 
 *  that use directly the header in the CCB, and the NCR-GENERIC 
 *  SCRIPTS that use the copy of the header in the HCB.
 */
#अगर	SYM_CONF_GENERIC_SUPPORT
#घोषणा sym_set_script_dp(np, cp, dp)				\
	करो अणु							\
		अगर (np->features & FE_LDSTR)			\
			cp->phys.head.lastp = cpu_to_scr(dp);	\
		अन्यथा						\
			np->ccb_head.lastp = cpu_to_scr(dp);	\
	पूर्ण जबतक (0)
#घोषणा sym_get_script_dp(np, cp) 				\
	scr_to_cpu((np->features & FE_LDSTR) ?			\
		cp->phys.head.lastp : np->ccb_head.lastp)
#अन्यथा
#घोषणा sym_set_script_dp(np, cp, dp)				\
	करो अणु							\
		cp->phys.head.lastp = cpu_to_scr(dp);		\
	पूर्ण जबतक (0)

#घोषणा sym_get_script_dp(np, cp) (cp->phys.head.lastp)
#पूर्ण_अगर

/*
 *  Data Structure Block
 *
 *  During execution of a ccb by the script processor, the 
 *  DSA (data काष्ठाure address) रेजिस्टर poपूर्णांकs to this 
 *  subकाष्ठाure of the ccb.
 */
काष्ठा sym_dsb अणु
	/*
	 *  CCB header.
	 *  Also assumed at offset 0 of the sym_ccb काष्ठाure.
	 */
/*0*/	काष्ठा sym_ccbh head;

	/*
	 *  Phase mismatch contexts.
	 *  We need two to handle correctly the SAVED DATA POINTER.
	 *  MUST BOTH BE AT OFFSET < 256, due to using 8 bit arithmetic 
	 *  क्रम address calculation from SCRIPTS.
	 */
	काष्ठा sym_pmc pm0;
	काष्ठा sym_pmc pm1;

	/*
	 *  Table data क्रम Script
	 */
	काष्ठा sym_tblsel  select;
	काष्ठा sym_tblmove smsg;
	काष्ठा sym_tblmove smsg_ext;
	काष्ठा sym_tblmove cmd;
	काष्ठा sym_tblmove sense;
	काष्ठा sym_tblmove wresid;
	काष्ठा sym_tblmove data [SYM_CONF_MAX_SG];
पूर्ण;

/*
 *  Our Command Control Block
 */
काष्ठा sym_ccb अणु
	/*
	 *  This is the data काष्ठाure which is poपूर्णांकed by the DSA 
	 *  रेजिस्टर when it is executed by the script processor.
	 *  It must be the first entry.
	 */
	काष्ठा sym_dsb phys;

	/*
	 *  Poपूर्णांकer to CAM ccb and related stuff.
	 */
	काष्ठा scsi_cmnd *cmd;	/* CAM scsiio ccb		*/
	u8	cdb_buf[16];	/* Copy of CDB			*/
#घोषणा	SYM_SNS_BBUF_LEN 32
	u8	sns_bbuf[SYM_SNS_BBUF_LEN]; /* Bounce buffer क्रम sense data */
	पूर्णांक	data_len;	/* Total data length		*/
	पूर्णांक	segments;	/* Number of SG segments	*/

	u8	order;		/* Tag type (अगर tagged command)	*/
	अचिन्हित अक्षर odd_byte_adjusपंचांगent;	/* odd-sized req on wide bus */

	u_अक्षर	nego_status;	/* Negotiation status		*/
	u_अक्षर	xerr_status;	/* Extended error flags		*/
	u32	extra_bytes;	/* Extraneous bytes transferred	*/

	/*
	 *  Message areas.
	 *  We prepare a message to be sent after selection.
	 *  We may use a second one अगर the command is rescheduled 
	 *  due to CHECK_CONDITION or COMMAND TERMINATED.
	 *  Contents are IDENTIFY and SIMPLE_TAG.
	 *  While negotiating sync or wide transfer,
	 *  a SDTR or WDTR message is appended.
	 */
	u_अक्षर	scsi_smsg [12];
	u_अक्षर	scsi_smsg2[12];

	/*
	 *  Auto request sense related fields.
	 */
	u_अक्षर	sensecmd[6];	/* Request Sense command	*/
	u_अक्षर	sv_scsi_status;	/* Saved SCSI status 		*/
	u_अक्षर	sv_xerr_status;	/* Saved extended status	*/
	पूर्णांक	sv_resid;	/* Saved residual		*/

	/*
	 *  Other fields.
	 */
	u32	ccb_ba;		/* BUS address of this CCB	*/
	u_लघु	tag;		/* Tag क्रम this transfer	*/
				/*  NO_TAG means no tag		*/
	u_अक्षर	target;
	u_अक्षर	lun;
	काष्ठा sym_ccb *link_ccbh;	/* Host adapter CCB hash chain	*/
	SYM_QUEHEAD link_ccbq;	/* Link to मुक्त/busy CCB queue	*/
	u32	startp;		/* Initial data poपूर्णांकer		*/
	u32	goalp;		/* Expected last data poपूर्णांकer	*/
	पूर्णांक	ext_sg;		/* Extreme data poपूर्णांकer, used	*/
	पूर्णांक	ext_ofs;	/*  to calculate the residual.	*/
#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	SYM_QUEHEAD link2_ccbq;	/* Link क्रम device queueing	*/
	u_अक्षर	started;	/* CCB queued to the squeue	*/
#पूर्ण_अगर
	u_अक्षर	to_पात;	/* Want this IO to be पातed	*/
#अगर_घोषित SYM_OPT_LIMIT_COMMAND_REORDERING
	u_अक्षर	tags_si;	/* Lun tags sum index (0,1)	*/
#पूर्ण_अगर
पूर्ण;

#घोषणा CCB_BA(cp,lbl)	cpu_to_scr(cp->ccb_ba + दुरत्व(काष्ठा sym_ccb, lbl))

प्रकार काष्ठा device *m_pool_ident_t;

/*
 *  Host Control Block
 */
काष्ठा sym_hcb अणु
	/*
	 *  Global headers.
	 *  Due to poorness of addressing capabilities, earlier 
	 *  chips (810, 815, 825) copy part of the data काष्ठाures 
	 *  (CCB, TCB and LCB) in fixed areas.
	 */
#अगर	SYM_CONF_GENERIC_SUPPORT
	काष्ठा sym_ccbh	ccb_head;
	काष्ठा sym_tcbh	tcb_head;
	काष्ठा sym_lcbh	lcb_head;
#पूर्ण_अगर
	/*
	 *  Idle task and invalid task actions and 
	 *  their bus addresses.
	 */
	काष्ठा sym_actscr idletask, notask, bad_itl, bad_itlq;
	u32 idletask_ba, notask_ba, bad_itl_ba, bad_itlq_ba;

	/*
	 *  Dummy lun table to protect us against target 
	 *  वापसing bad lun number on reselection.
	 */
	u32	*badluntbl;	/* Table physical address	*/
	u32	badlun_sa;	/* SCRIPT handler BUS address	*/

	/*
	 *  Bus address of this host control block.
	 */
	u32	hcb_ba;

	/*
	 *  Bit 32-63 of the on-chip RAM bus address in LE क्रमmat.
	 *  The START_RAM64 script loads the MMRS and MMWS from this 
	 *  field.
	 */
	u32	scr_ram_seg;

	/*
	 *  Initial value of some IO रेजिस्टर bits.
	 *  These values are assumed to have been set by BIOS, and may 
	 *  be used to probe adapter implementation dअगरferences.
	 */
	u_अक्षर	sv_scntl0, sv_scntl3, sv_dmode, sv_dcntl, sv_ctest3, sv_ctest4,
		sv_ctest5, sv_gpcntl, sv_stest2, sv_stest4, sv_scntl4,
		sv_stest1;

	/*
	 *  Actual initial value of IO रेजिस्टर bits used by the 
	 *  driver. They are loaded at initialisation according to  
	 *  features that are to be enabled/disabled.
	 */
	u_अक्षर	rv_scntl0, rv_scntl3, rv_dmode, rv_dcntl, rv_ctest3, rv_ctest4, 
		rv_ctest5, rv_stest2, rv_ccntl0, rv_ccntl1, rv_scntl4;

	/*
	 *  Target data.
	 */
	काष्ठा sym_tcb	target[SYM_CONF_MAX_TARGET];

	/*
	 *  Target control block bus address array used by the SCRIPT 
	 *  on reselection.
	 */
	u32		*targtbl;
	u32		targtbl_ba;

	/*
	 *  DMA pool handle क्रम this HBA.
	 */
	m_pool_ident_t	bus_dmat;

	/*
	 *  O/S specअगरic data काष्ठाure
	 */
	काष्ठा sym_shcb s;

	/*
	 *  Physical bus addresses of the chip.
	 */
	u32		mmio_ba;	/* MMIO 32 bit BUS address	*/
	u32		ram_ba;		/* RAM 32 bit BUS address	*/

	/*
	 *  SCRIPTS भव and physical bus addresses.
	 *  'script'  is loaded in the on-chip RAM अगर present.
	 *  'scripth' stays in मुख्य memory क्रम all chips except the 
	 *  53C895A, 53C896 and 53C1010 that provide 8K on-chip RAM.
	 */
	u_अक्षर		*scripta0;	/* Copy of scripts A, B, Z	*/
	u_अक्षर		*scriptb0;
	u_अक्षर		*scriptz0;
	u32		scripta_ba;	/* Actual scripts A, B, Z	*/
	u32		scriptb_ba;	/* 32 bit bus addresses.	*/
	u32		scriptz_ba;
	u_लघु		scripta_sz;	/* Actual size of script A, B, Z*/
	u_लघु		scriptb_sz;
	u_लघु		scriptz_sz;

	/*
	 *  Bus addresses, setup and patch methods क्रम 
	 *  the selected firmware.
	 */
	काष्ठा sym_fwa_ba fwa_bas;	/* Useful SCRIPTA bus addresses	*/
	काष्ठा sym_fwb_ba fwb_bas;	/* Useful SCRIPTB bus addresses	*/
	काष्ठा sym_fwz_ba fwz_bas;	/* Useful SCRIPTZ bus addresses	*/
	व्योम		(*fw_setup)(काष्ठा sym_hcb *np, काष्ठा sym_fw *fw);
	व्योम		(*fw_patch)(काष्ठा Scsi_Host *);
	अक्षर		*fw_name;

	/*
	 *  General controller parameters and configuration.
	 */
	u_पूर्णांक	features;	/* Chip features map		*/
	u_अक्षर	myaddr;		/* SCSI id of the adapter	*/
	u_अक्षर	maxburst;	/* log base 2 of dwords burst	*/
	u_अक्षर	maxwide;	/* Maximum transfer width	*/
	u_अक्षर	minsync;	/* Min sync period factor (ST)	*/
	u_अक्षर	maxsync;	/* Max sync period factor (ST)	*/
	u_अक्षर	maxoffs;	/* Max scsi offset        (ST)	*/
	u_अक्षर	minsync_dt;	/* Min sync period factor (DT)	*/
	u_अक्षर	maxsync_dt;	/* Max sync period factor (DT)	*/
	u_अक्षर	maxoffs_dt;	/* Max scsi offset        (DT)	*/
	u_अक्षर	multiplier;	/* Clock multiplier (1,2,4)	*/
	u_अक्षर	घड़ी_भागn;	/* Number of घड़ी भागisors	*/
	u32	घड़ी_khz;	/* SCSI घड़ी frequency in KHz	*/
	u32	pciclk_khz;	/* Estimated PCI घड़ी  in KHz	*/
	/*
	 *  Start queue management.
	 *  It is filled up by the host processor and accessed by the 
	 *  SCRIPTS processor in order to start SCSI commands.
	 */
	अस्थिर		/* Prevent code optimizations	*/
	u32	*squeue;	/* Start queue भव address	*/
	u32	squeue_ba;	/* Start queue BUS address	*/
	u_लघु	squeueput;	/* Next मुक्त slot of the queue	*/
	u_लघु	actccbs;	/* Number of allocated CCBs	*/

	/*
	 *  Command completion queue.
	 *  It is the same size as the start queue to aव्योम overflow.
	 */
	u_लघु	dqueueget;	/* Next position to scan	*/
	अस्थिर		/* Prevent code optimizations	*/
	u32	*dqueue;	/* Completion (करोne) queue	*/
	u32	dqueue_ba;	/* Done queue BUS address	*/

	/*
	 *  Miscellaneous buffers accessed by the scripts-processor.
	 *  They shall be DWORD aligned, because they may be पढ़ो or 
	 *  written with a script command.
	 */
	u_अक्षर		msgout[8];	/* Buffer क्रम MESSAGE OUT 	*/
	u_अक्षर		msgin [8];	/* Buffer क्रम MESSAGE IN	*/
	u32		lasपंचांगsg;	/* Last SCSI message sent	*/
	u32		scratch;	/* Scratch क्रम SCSI receive	*/
					/* Also used क्रम cache test 	*/
	/*
	 *  Miscellaneous configuration and status parameters.
	 */
	u_अक्षर		usrflags;	/* Miscellaneous user flags	*/
	u_अक्षर		scsi_mode;	/* Current SCSI BUS mode	*/
	u_अक्षर		verbose;	/* Verbosity क्रम this controller*/

	/*
	 *  CCB lists and queue.
	 */
	काष्ठा sym_ccb **ccbh;			/* CCBs hashed by DSA value	*/
					/* CCB_HASH_SIZE lists of CCBs	*/
	SYM_QUEHEAD	मुक्त_ccbq;	/* Queue of available CCBs	*/
	SYM_QUEHEAD	busy_ccbq;	/* Queue of busy CCBs		*/

	/*
	 *  During error handling and/or recovery,
	 *  active CCBs that are to be completed with 
	 *  error or requeued are moved from the busy_ccbq
	 *  to the comp_ccbq prior to completion.
	 */
	SYM_QUEHEAD	comp_ccbq;

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	SYM_QUEHEAD	dummy_ccbq;
#पूर्ण_अगर

	/*
	 *  IMMEDIATE ARBITRATION (IARB) control.
	 *
	 *  We keep track in 'last_cp' of the last CCB that has been 
	 *  queued to the SCRIPTS processor and clear 'last_cp' when 
	 *  this CCB completes. If last_cp is not zero at the moment 
	 *  we queue a new CCB, we set a flag in 'last_cp' that is 
	 *  used by the SCRIPTS as a hपूर्णांक क्रम setting IARB.
	 *  We करोnnot set more than 'iarb_max' consecutive hपूर्णांकs क्रम 
	 *  IARB in order to leave devices a chance to reselect.
	 *  By the way, any non zero value of 'iarb_max' is unfair. :)
	 */
#अगर_घोषित SYM_CONF_IARB_SUPPORT
	u_लघु		iarb_max;	/* Max. # consecutive IARB hपूर्णांकs*/
	u_लघु		iarb_count;	/* Actual # of these hपूर्णांकs	*/
	काष्ठा sym_ccb *	last_cp;
#पूर्ण_अगर

	/*
	 *  Command पात handling.
	 *  We need to synchronize tightly with the SCRIPTS 
	 *  processor in order to handle things correctly.
	 */
	u_अक्षर		abrt_msg[4];	/* Message to send buffer	*/
	काष्ठा sym_tblmove abrt_tbl;	/* Table क्रम the MOV of it 	*/
	काष्ठा sym_tblsel  abrt_sel;	/* Sync params क्रम selection	*/
	u_अक्षर		istat_sem;	/* Tells the chip to stop (SEM)	*/

	/*
	 *  64 bit DMA handling.
	 */
#अगर	SYM_CONF_DMA_ADDRESSING_MODE != 0
	u_अक्षर	use_dac;		/* Use PCI DAC cycles		*/
#अगर	SYM_CONF_DMA_ADDRESSING_MODE == 2
	u_अक्षर	dmap_dirty;		/* Dma segments रेजिस्टरs dirty	*/
	u32	dmap_bah[SYM_DMAP_SIZE];/* Segment रेजिस्टरs map	*/
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;

#अगर SYM_CONF_DMA_ADDRESSING_MODE == 0
#घोषणा use_dac(np)	0
#घोषणा set_dac(np)	करो अणु पूर्ण जबतक (0)
#अन्यथा
#घोषणा use_dac(np)	(np)->use_dac
#घोषणा set_dac(np)	(np)->use_dac = 1
#पूर्ण_अगर

#घोषणा HCB_BA(np, lbl)	(np->hcb_ba + दुरत्व(काष्ठा sym_hcb, lbl))


/*
 *  FIRMWARES (sym_fw.c)
 */
काष्ठा sym_fw * sym_find_firmware(काष्ठा sym_chip *chip);
व्योम sym_fw_bind_script(काष्ठा sym_hcb *np, u32 *start, पूर्णांक len);

/*
 *  Driver methods called from O/S specअगरic code.
 */
अक्षर *sym_driver_name(व्योम);
व्योम sym_prपूर्णांक_xerr(काष्ठा scsi_cmnd *cmd, पूर्णांक x_status);
पूर्णांक sym_reset_scsi_bus(काष्ठा sym_hcb *np, पूर्णांक enab_पूर्णांक);
काष्ठा sym_chip *sym_lookup_chip_table(u_लघु device_id, u_अक्षर revision);
#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
व्योम sym_start_next_ccbs(काष्ठा sym_hcb *np, काष्ठा sym_lcb *lp, पूर्णांक maxn);
#अन्यथा
व्योम sym_put_start_queue(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp);
#पूर्ण_अगर
व्योम sym_start_up(काष्ठा Scsi_Host *, पूर्णांक reason);
irqवापस_t sym_पूर्णांकerrupt(काष्ठा Scsi_Host *);
पूर्णांक sym_clear_tasks(काष्ठा sym_hcb *np, पूर्णांक cam_status, पूर्णांक target, पूर्णांक lun, पूर्णांक task);
काष्ठा sym_ccb *sym_get_ccb(काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *cmd, u_अक्षर tag_order);
व्योम sym_मुक्त_ccb(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp);
काष्ठा sym_lcb *sym_alloc_lcb(काष्ठा sym_hcb *np, u_अक्षर tn, u_अक्षर ln);
पूर्णांक sym_मुक्त_lcb(काष्ठा sym_hcb *np, u_अक्षर tn, u_अक्षर ln);
पूर्णांक sym_queue_scsiio(काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *csio, काष्ठा sym_ccb *cp);
पूर्णांक sym_पात_scsiio(काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *ccb, पूर्णांक समयd_out);
पूर्णांक sym_reset_scsi_target(काष्ठा sym_hcb *np, पूर्णांक target);
व्योम sym_hcb_मुक्त(काष्ठा sym_hcb *np);
पूर्णांक sym_hcb_attach(काष्ठा Scsi_Host *shost, काष्ठा sym_fw *fw, काष्ठा sym_nvram *nvram);

/*
 *  Build a scatter/gather entry.
 *
 *  For 64 bit प्रणालीs, we use the 8 upper bits of the size field 
 *  to provide bus address bits 32-39 to the SCRIPTS processor.
 *  This allows the 895A, 896, 1010 to address up to 1 TB of memory.
 */

#अगर   SYM_CONF_DMA_ADDRESSING_MODE == 0
#घोषणा DMA_DAC_MASK	DMA_BIT_MASK(32)
#घोषणा sym_build_sge(np, data, badd, len)	\
करो अणु						\
	(data)->addr = cpu_to_scr(badd);	\
	(data)->size = cpu_to_scr(len);		\
पूर्ण जबतक (0)
#या_अगर SYM_CONF_DMA_ADDRESSING_MODE == 1
#घोषणा DMA_DAC_MASK	DMA_BIT_MASK(40)
#घोषणा sym_build_sge(np, data, badd, len)				\
करो अणु									\
	(data)->addr = cpu_to_scr(badd);				\
	(data)->size = cpu_to_scr((((badd) >> 8) & 0xff000000) + len);	\
पूर्ण जबतक (0)
#या_अगर SYM_CONF_DMA_ADDRESSING_MODE == 2
#घोषणा DMA_DAC_MASK	DMA_BIT_MASK(64)
पूर्णांक sym_lookup_dmap(काष्ठा sym_hcb *np, u32 h, पूर्णांक s);
अटल अंतरभूत व्योम
sym_build_sge(काष्ठा sym_hcb *np, काष्ठा sym_tblmove *data, u64 badd, पूर्णांक len)
अणु
	u32 h = (badd>>32);
	पूर्णांक s = (h&SYM_DMAP_MASK);

	अगर (h != np->dmap_bah[s])
		जाओ bad;
good:
	(data)->addr = cpu_to_scr(badd);
	(data)->size = cpu_to_scr((s<<24) + len);
	वापस;
bad:
	s = sym_lookup_dmap(np, h, s);
	जाओ good;
पूर्ण
#अन्यथा
#त्रुटि "Unsupported DMA addressing mode"
#पूर्ण_अगर

/*
 *  MEMORY ALLOCATOR.
 */

#घोषणा sym_get_mem_cluster()	\
	(व्योम *) __get_मुक्त_pages(GFP_ATOMIC, SYM_MEM_PAGE_ORDER)
#घोषणा sym_मुक्त_mem_cluster(p)	\
	मुक्त_pages((अचिन्हित दीर्घ)p, SYM_MEM_PAGE_ORDER)

/*
 *  Link between मुक्त memory chunks of a given size.
 */
प्रकार काष्ठा sym_m_link अणु
	काष्ठा sym_m_link *next;
पूर्ण *m_link_p;

/*
 *  Virtual to bus physical translation क्रम a given cluster.
 *  Such a काष्ठाure is only useful with DMA असलtraction.
 */
प्रकार काष्ठा sym_m_vtob अणु	/* Virtual to Bus address translation */
	काष्ठा sym_m_vtob *next;
	व्योम *vaddr;		/* Virtual address */
	dma_addr_t baddr;	/* Bus physical address */
पूर्ण *m_vtob_p;

/* Hash this stuff a bit to speed up translations */
#घोषणा VTOB_HASH_SHIFT		5
#घोषणा VTOB_HASH_SIZE		(1UL << VTOB_HASH_SHIFT)
#घोषणा VTOB_HASH_MASK		(VTOB_HASH_SIZE-1)
#घोषणा VTOB_HASH_CODE(m)	\
	((((अचिन्हित दीर्घ)(m)) >> SYM_MEM_CLUSTER_SHIFT) & VTOB_HASH_MASK)

/*
 *  Memory pool of a given kind.
 *  Ideally, we want to use:
 *  1) 1 pool क्रम memory we करोnnot need to involve in DMA.
 *  2) The same pool क्रम controllers that require same DMA 
 *     स्थिरraपूर्णांकs and features.
 *     The OS specअगरic m_pool_id_t thing and the sym_m_pool_match() 
 *     method are expected to tell the driver about.
 */
प्रकार काष्ठा sym_m_pool अणु
	m_pool_ident_t	dev_dmat;	/* Identअगरies the pool (see above) */
	व्योम * (*get_mem_cluster)(काष्ठा sym_m_pool *);
#अगर_घोषित	SYM_MEM_FREE_UNUSED
	व्योम (*मुक्त_mem_cluster)(काष्ठा sym_m_pool *, व्योम *);
#पूर्ण_अगर
#घोषणा M_GET_MEM_CLUSTER()		mp->get_mem_cluster(mp)
#घोषणा M_FREE_MEM_CLUSTER(p)		mp->मुक्त_mem_cluster(mp, p)
	पूर्णांक nump;
	m_vtob_p vtob[VTOB_HASH_SIZE];
	काष्ठा sym_m_pool *next;
	काष्ठा sym_m_link h[SYM_MEM_CLUSTER_SHIFT - SYM_MEM_SHIFT + 1];
पूर्ण *m_pool_p;

/*
 *  Alloc, मुक्त and translate addresses to bus physical 
 *  क्रम DMAable memory.
 */
व्योम *__sym_सुस्मृति_dma(m_pool_ident_t dev_dmat, पूर्णांक size, अक्षर *name);
व्योम __sym_mमुक्त_dma(m_pool_ident_t dev_dmat, व्योम *m, पूर्णांक size, अक्षर *name);
dma_addr_t __vtobus(m_pool_ident_t dev_dmat, व्योम *m);

/*
 * Verbs used by the driver code क्रम DMAable memory handling.
 * The _uvptv_ macro aव्योमs a nasty warning about poपूर्णांकer to अस्थिर 
 * being discarded.
 */
#घोषणा _uvptv_(p) ((व्योम *)((u_दीर्घ)(p)))

#घोषणा _sym_सुस्मृति_dma(np, l, n)	__sym_सुस्मृति_dma(np->bus_dmat, l, n)
#घोषणा _sym_mमुक्त_dma(np, p, l, n)	\
			__sym_mमुक्त_dma(np->bus_dmat, _uvptv_(p), l, n)
#घोषणा sym_सुस्मृति_dma(l, n)		_sym_सुस्मृति_dma(np, l, n)
#घोषणा sym_mमुक्त_dma(p, l, n)		_sym_mमुक्त_dma(np, p, l, n)
#घोषणा vtobus(p)			__vtobus(np->bus_dmat, _uvptv_(p))

/*
 *  We have to provide the driver memory allocator with methods क्रम 
 *  it to मुख्यtain भव to bus physical address translations.
 */

#घोषणा sym_m_pool_match(mp_id1, mp_id2)	(mp_id1 == mp_id2)

अटल अंतरभूत व्योम *sym_m_get_dma_mem_cluster(m_pool_p mp, m_vtob_p vbp)
अणु
	व्योम *vaddr = शून्य;
	dma_addr_t baddr = 0;

	vaddr = dma_alloc_coherent(mp->dev_dmat, SYM_MEM_CLUSTER_SIZE, &baddr,
			GFP_ATOMIC);
	अगर (vaddr) अणु
		vbp->vaddr = vaddr;
		vbp->baddr = baddr;
	पूर्ण
	वापस vaddr;
पूर्ण

अटल अंतरभूत व्योम sym_m_मुक्त_dma_mem_cluster(m_pool_p mp, m_vtob_p vbp)
अणु
	dma_मुक्त_coherent(mp->dev_dmat, SYM_MEM_CLUSTER_SIZE, vbp->vaddr,
			vbp->baddr);
पूर्ण

#पूर्ण_अगर /* SYM_HIPD_H */
