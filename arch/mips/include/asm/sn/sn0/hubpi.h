<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Derived from IRIX <sys/SN/SN0/hubpi.h>, revision 1.28.
 *
 * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.
 * Copyright (C) 1999 by Ralf Baechle
 */
#अगर_अघोषित _ASM_SN_SN0_HUBPI_H
#घोषणा _ASM_SN_SN0_HUBPI_H

#समावेश <linux/types.h>

/*
 * Hub I/O पूर्णांकerface रेजिस्टरs
 *
 * All रेजिस्टरs in this file are subject to change until Hub chip tapeout.
 * All रेजिस्टर "addresses" are actually offsets.  Use the LOCAL_HUB
 * or REMOTE_HUB macros to synthesize an actual address
 */

#घोषणा PI_BASE			0x000000

/* General protection and control रेजिस्टरs */

#घोषणा PI_CPU_PROTECT		0x000000 /* CPU Protection		    */
#घोषणा PI_PROT_OVERRD		0x000008 /* Clear CPU Protection bit	    */
#घोषणा PI_IO_PROTECT		0x000010 /* Interrupt Pending Protection    */
#घोषणा PI_REGION_PRESENT	0x000018 /* Indicates whether region exists */
#घोषणा PI_CPU_NUM		0x000020 /* CPU Number ID		    */
#घोषणा PI_CALIAS_SIZE		0x000028 /* Cached Alias Size		    */
#घोषणा PI_MAX_CRB_TIMEOUT	0x000030 /* Maximum Timeout क्रम CRB	    */
#घोषणा PI_CRB_SFACTOR		0x000038 /* Scale factor क्रम CRB समयout    */

/* CALIAS values */
#घोषणा PI_CALIAS_SIZE_0	0
#घोषणा PI_CALIAS_SIZE_4K	1
#घोषणा PI_CALIAS_SIZE_8K	2
#घोषणा PI_CALIAS_SIZE_16K	3
#घोषणा PI_CALIAS_SIZE_32K	4
#घोषणा PI_CALIAS_SIZE_64K	5
#घोषणा PI_CALIAS_SIZE_128K	6
#घोषणा PI_CALIAS_SIZE_256K	7
#घोषणा PI_CALIAS_SIZE_512K	8
#घोषणा PI_CALIAS_SIZE_1M	9
#घोषणा PI_CALIAS_SIZE_2M	10
#घोषणा PI_CALIAS_SIZE_4M	11
#घोषणा PI_CALIAS_SIZE_8M	12
#घोषणा PI_CALIAS_SIZE_16M	13
#घोषणा PI_CALIAS_SIZE_32M	14
#घोषणा PI_CALIAS_SIZE_64M	15

/* Processor control and status checking */

#घोषणा PI_CPU_PRESENT_A	0x000040 /* CPU Present A		    */
#घोषणा PI_CPU_PRESENT_B	0x000048 /* CPU Present B		    */
#घोषणा PI_CPU_ENABLE_A		0x000050 /* CPU Enable A		    */
#घोषणा PI_CPU_ENABLE_B		0x000058 /* CPU Enable B		    */
#घोषणा PI_REPLY_LEVEL		0x000060 /* Reply Level			    */
#घोषणा PI_HARDRESET_BIT	0x020068 /* Bit cleared by s/w on SR	    */
#घोषणा PI_NMI_A		0x000070 /* NMI to CPU A		    */
#घोषणा PI_NMI_B		0x000078 /* NMI to CPU B		    */
#घोषणा PI_NMI_OFFSET		(PI_NMI_B - PI_NMI_A)
#घोषणा PI_SOFTRESET		0x000080 /* Softreset (to both CPUs)	    */

/* Regular Interrupt रेजिस्टर checking.	 */

#घोषणा PI_INT_PEND_MOD		0x000090 /* Write to set pending पूर्णांकs	    */
#घोषणा PI_INT_PEND0		0x000098 /* Read to get pending पूर्णांकs	    */
#घोषणा PI_INT_PEND1		0x0000a0 /* Read to get pending पूर्णांकs	    */
#घोषणा PI_INT_MASK0_A		0x0000a8 /* Interrupt Mask 0 क्रम CPU A	    */
#घोषणा PI_INT_MASK1_A		0x0000b0 /* Interrupt Mask 1 क्रम CPU A	    */
#घोषणा PI_INT_MASK0_B		0x0000b8 /* Interrupt Mask 0 क्रम CPU B	    */
#घोषणा PI_INT_MASK1_B		0x0000c0 /* Interrupt Mask 1 क्रम CPU B	    */

#घोषणा PI_INT_MASK_OFFSET	0x10	 /* Offset from A to B		    */

/* Crosscall पूर्णांकerrupts */

#घोषणा PI_CC_PEND_SET_A	0x0000c8 /* CC Interrupt Pending Set, CPU A */
#घोषणा PI_CC_PEND_SET_B	0x0000d0 /* CC Interrupt Pending Set, CPU B */
#घोषणा PI_CC_PEND_CLR_A	0x0000d8 /* CC Interrupt Pending Clr, CPU A */
#घोषणा PI_CC_PEND_CLR_B	0x0000e0 /* CC Interrupt Pending Clr, CPU B */
#घोषणा PI_CC_MASK		0x0000e8 /* CC Interrupt mask		    */

#घोषणा PI_INT_SET_OFFSET	0x08	 /* Offset from A to B		    */

/* Realसमय Counter and Profiler control रेजिस्टरs */

#घोषणा PI_RT_COUNT		0x030100 /* Real Time Counter		    */
#घोषणा PI_RT_COMPARE_A		0x000108 /* Real Time Compare A		    */
#घोषणा PI_RT_COMPARE_B		0x000110 /* Real Time Compare B		    */
#घोषणा PI_PROखाता_COMPARE	0x000118 /* L5 पूर्णांक to both cpus when == RTC */
#घोषणा PI_RT_PEND_A		0x000120 /* Set अगर RT पूर्णांक क्रम A pending	    */
#घोषणा PI_RT_PEND_B		0x000128 /* Set अगर RT पूर्णांक क्रम B pending	    */
#घोषणा PI_PROF_PEND_A		0x000130 /* Set अगर Prof पूर्णांक क्रम A pending   */
#घोषणा PI_PROF_PEND_B		0x000138 /* Set अगर Prof पूर्णांक क्रम B pending   */
#घोषणा PI_RT_EN_A		0x000140 /* RT पूर्णांक क्रम CPU A enable	    */
#घोषणा PI_RT_EN_B		0x000148 /* RT पूर्णांक क्रम CPU B enable	    */
#घोषणा PI_PROF_EN_A		0x000150 /* PROF पूर्णांक क्रम CPU A enable	    */
#घोषणा PI_PROF_EN_B		0x000158 /* PROF पूर्णांक क्रम CPU B enable	    */
#घोषणा PI_RT_LOCAL_CTRL	0x000160 /* RT control रेजिस्टर		    */
#घोषणा PI_RT_FILTER_CTRL	0x000168 /* GCLK Filter control रेजिस्टर    */

#घोषणा PI_COUNT_OFFSET		0x08	 /* A to B offset क्रम all counts    */

/* Built-In Self Test support */

#घोषणा PI_BIST_WRITE_DATA	0x000200 /* BIST ग_लिखो data		    */
#घोषणा PI_BIST_READ_DATA	0x000208 /* BIST पढ़ो data		    */
#घोषणा PI_BIST_COUNT_TARG	0x000210 /* BIST Count and Target	    */
#घोषणा PI_BIST_READY		0x000218 /* BIST Ready indicator	    */
#घोषणा PI_BIST_SHIFT_LOAD	0x000220 /* BIST control		    */
#घोषणा PI_BIST_SHIFT_UNLOAD	0x000228 /* BIST control		    */
#घोषणा PI_BIST_ENTER_RUN	0x000230 /* BIST control		    */

/* Graphics control रेजिस्टरs */

#घोषणा PI_GFX_PAGE_A		0x000300 /* Graphics page A		    */
#घोषणा PI_GFX_CREDIT_CNTR_A	0x000308 /* Graphics credit counter A	    */
#घोषणा PI_GFX_BIAS_A		0x000310 /* Graphics bias A		    */
#घोषणा PI_GFX_INT_CNTR_A	0x000318 /* Graphics पूर्णांकerrupt counter A    */
#घोषणा PI_GFX_INT_CMP_A	0x000320 /* Graphics पूर्णांकerrupt comparator A */
#घोषणा PI_GFX_PAGE_B		0x000328 /* Graphics page B		    */
#घोषणा PI_GFX_CREDIT_CNTR_B	0x000330 /* Graphics credit counter B	    */
#घोषणा PI_GFX_BIAS_B		0x000338 /* Graphics bias B		    */
#घोषणा PI_GFX_INT_CNTR_B	0x000340 /* Graphics पूर्णांकerrupt counter B    */
#घोषणा PI_GFX_INT_CMP_B	0x000348 /* Graphics पूर्णांकerrupt comparator B */

#घोषणा PI_GFX_OFFSET		(PI_GFX_PAGE_B - PI_GFX_PAGE_A)
#घोषणा PI_GFX_PAGE_ENABLE	0x0000010000000000LL

/* Error and समयout रेजिस्टरs */
#घोषणा PI_ERR_INT_PEND		0x000400 /* Error Interrupt Pending	    */
#घोषणा PI_ERR_INT_MASK_A	0x000408 /* Error Interrupt mask क्रम CPU A  */
#घोषणा PI_ERR_INT_MASK_B	0x000410 /* Error Interrupt mask क्रम CPU B  */
#घोषणा PI_ERR_STACK_ADDR_A	0x000418 /* Error stack address क्रम CPU A   */
#घोषणा PI_ERR_STACK_ADDR_B	0x000420 /* Error stack address क्रम CPU B   */
#घोषणा PI_ERR_STACK_SIZE	0x000428 /* Error Stack Size		    */
#घोषणा PI_ERR_STATUS0_A	0x000430 /* Error Status 0A		    */
#घोषणा PI_ERR_STATUS0_A_RCLR	0x000438 /* Error Status 0A clear on पढ़ो   */
#घोषणा PI_ERR_STATUS1_A	0x000440 /* Error Status 1A		    */
#घोषणा PI_ERR_STATUS1_A_RCLR	0x000448 /* Error Status 1A clear on पढ़ो   */
#घोषणा PI_ERR_STATUS0_B	0x000450 /* Error Status 0B		    */
#घोषणा PI_ERR_STATUS0_B_RCLR	0x000458 /* Error Status 0B clear on पढ़ो   */
#घोषणा PI_ERR_STATUS1_B	0x000460 /* Error Status 1B		    */
#घोषणा PI_ERR_STATUS1_B_RCLR	0x000468 /* Error Status 1B clear on पढ़ो   */
#घोषणा PI_SPOOL_CMP_A		0x000470 /* Spool compare क्रम CPU A	    */
#घोषणा PI_SPOOL_CMP_B		0x000478 /* Spool compare क्रम CPU B	    */
#घोषणा PI_CRB_TIMEOUT_A	0x000480 /* Timed out CRB entries क्रम A	    */
#घोषणा PI_CRB_TIMEOUT_B	0x000488 /* Timed out CRB entries क्रम B	    */
#घोषणा PI_SYSAD_ERRCHK_EN	0x000490 /* Enables SYSAD error checking    */
#घोषणा PI_BAD_CHECK_BIT_A	0x000498 /* Force SYSAD check bit error	    */
#घोषणा PI_BAD_CHECK_BIT_B	0x0004a0 /* Force SYSAD check bit error	    */
#घोषणा PI_NACK_CNT_A		0x0004a8 /* Consecutive NACK counter	    */
#घोषणा PI_NACK_CNT_B		0x0004b0 /*	"	" क्रम CPU B	    */
#घोषणा PI_NACK_CMP		0x0004b8 /* NACK count compare		    */
#घोषणा PI_STACKADDR_OFFSET	(PI_ERR_STACK_ADDR_B - PI_ERR_STACK_ADDR_A)
#घोषणा PI_ERRSTAT_OFFSET	(PI_ERR_STATUS0_B - PI_ERR_STATUS0_A)
#घोषणा PI_RDCLR_OFFSET		(PI_ERR_STATUS0_A_RCLR - PI_ERR_STATUS0_A)

/* Bits in PI_ERR_INT_PEND */
#घोषणा PI_ERR_SPOOL_CMP_B	0x00000001	/* Spool end hit high water */
#घोषणा PI_ERR_SPOOL_CMP_A	0x00000002
#घोषणा PI_ERR_SPUR_MSG_B	0x00000004	/* Spurious message पूर्णांकr.   */
#घोषणा PI_ERR_SPUR_MSG_A	0x00000008
#घोषणा PI_ERR_WRB_TERR_B	0x00000010	/* WRB TERR		    */
#घोषणा PI_ERR_WRB_TERR_A	0x00000020
#घोषणा PI_ERR_WRB_WERR_B	0x00000040	/* WRB WERR		    */
#घोषणा PI_ERR_WRB_WERR_A	0x00000080
#घोषणा PI_ERR_SYSSTATE_B	0x00000100	/* SysState parity error    */
#घोषणा PI_ERR_SYSSTATE_A	0x00000200
#घोषणा PI_ERR_SYSAD_DATA_B	0x00000400	/* SysAD data parity error  */
#घोषणा PI_ERR_SYSAD_DATA_A	0x00000800
#घोषणा PI_ERR_SYSAD_ADDR_B	0x00001000	/* SysAD addr parity error  */
#घोषणा PI_ERR_SYSAD_ADDR_A	0x00002000
#घोषणा PI_ERR_SYSCMD_DATA_B	0x00004000	/* SysCmd data parity error */
#घोषणा PI_ERR_SYSCMD_DATA_A	0x00008000
#घोषणा PI_ERR_SYSCMD_ADDR_B	0x00010000	/* SysCmd addr parity error */
#घोषणा PI_ERR_SYSCMD_ADDR_A	0x00020000
#घोषणा PI_ERR_BAD_SPOOL_B	0x00040000	/* Error spooling to memory */
#घोषणा PI_ERR_BAD_SPOOL_A	0x00080000
#घोषणा PI_ERR_UNCAC_UNCORR_B	0x00100000	/* Uncached uncorrectable   */
#घोषणा PI_ERR_UNCAC_UNCORR_A	0x00200000
#घोषणा PI_ERR_SYSSTATE_TAG_B	0x00400000	/* SysState tag parity error */
#घोषणा PI_ERR_SYSSTATE_TAG_A	0x00800000
#घोषणा PI_ERR_MD_UNCORR	0x01000000	/* Must be cleared in MD    */

#घोषणा PI_ERR_CLEAR_ALL_A	0x00aaaaaa
#घोषणा PI_ERR_CLEAR_ALL_B	0x00555555


/*
 * The following three macros define all possible error पूर्णांक pends.
 */

#घोषणा PI_FATAL_ERR_CPU_A	(PI_ERR_SYSSTATE_TAG_A	| \
				 PI_ERR_BAD_SPOOL_A	| \
				 PI_ERR_SYSCMD_ADDR_A	| \
				 PI_ERR_SYSCMD_DATA_A	| \
				 PI_ERR_SYSAD_ADDR_A	| \
				 PI_ERR_SYSAD_DATA_A	| \
				 PI_ERR_SYSSTATE_A)

#घोषणा PI_MISC_ERR_CPU_A	(PI_ERR_UNCAC_UNCORR_A	| \
				 PI_ERR_WRB_WERR_A	| \
				 PI_ERR_WRB_TERR_A	| \
				 PI_ERR_SPUR_MSG_A	| \
				 PI_ERR_SPOOL_CMP_A)

#घोषणा PI_FATAL_ERR_CPU_B	(PI_ERR_SYSSTATE_TAG_B	| \
				 PI_ERR_BAD_SPOOL_B	| \
				 PI_ERR_SYSCMD_ADDR_B	| \
				 PI_ERR_SYSCMD_DATA_B	| \
				 PI_ERR_SYSAD_ADDR_B	| \
				 PI_ERR_SYSAD_DATA_B	| \
				 PI_ERR_SYSSTATE_B)

#घोषणा PI_MISC_ERR_CPU_B	(PI_ERR_UNCAC_UNCORR_B	| \
				 PI_ERR_WRB_WERR_B	| \
				 PI_ERR_WRB_TERR_B	| \
				 PI_ERR_SPUR_MSG_B	| \
				 PI_ERR_SPOOL_CMP_B)

#घोषणा PI_ERR_GENERIC	(PI_ERR_MD_UNCORR)

/*
 * Error types क्रम PI_ERR_STATUS0_[AB] and error stack:
 * Use the ग_लिखो types अगर WRBRRB is 1 अन्यथा use the पढ़ो types
 */

/* Fields in PI_ERR_STATUS0_[AB] */
#घोषणा PI_ERR_ST0_TYPE_MASK	0x0000000000000007
#घोषणा PI_ERR_ST0_TYPE_SHFT	0
#घोषणा PI_ERR_ST0_REQNUM_MASK	0x0000000000000038
#घोषणा PI_ERR_ST0_REQNUM_SHFT	3
#घोषणा PI_ERR_ST0_SUPPL_MASK	0x000000000001ffc0
#घोषणा PI_ERR_ST0_SUPPL_SHFT	6
#घोषणा PI_ERR_ST0_CMD_MASK	0x0000000001fe0000
#घोषणा PI_ERR_ST0_CMD_SHFT	17
#घोषणा PI_ERR_ST0_ADDR_MASK	0x3ffffffffe000000
#घोषणा PI_ERR_ST0_ADDR_SHFT	25
#घोषणा PI_ERR_ST0_OVERRUN_MASK 0x4000000000000000
#घोषणा PI_ERR_ST0_OVERRUN_SHFT 62
#घोषणा PI_ERR_ST0_VALID_MASK	0x8000000000000000
#घोषणा PI_ERR_ST0_VALID_SHFT	63

/* Fields in PI_ERR_STATUS1_[AB] */
#घोषणा PI_ERR_ST1_SPOOL_MASK	0x00000000001fffff
#घोषणा PI_ERR_ST1_SPOOL_SHFT	0
#घोषणा PI_ERR_ST1_TOUTCNT_MASK 0x000000001fe00000
#घोषणा PI_ERR_ST1_TOUTCNT_SHFT 21
#घोषणा PI_ERR_ST1_INVCNT_MASK	0x0000007fe0000000
#घोषणा PI_ERR_ST1_INVCNT_SHFT	29
#घोषणा PI_ERR_ST1_CRBNUM_MASK	0x0000038000000000
#घोषणा PI_ERR_ST1_CRBNUM_SHFT	39
#घोषणा PI_ERR_ST1_WRBRRB_MASK	0x0000040000000000
#घोषणा PI_ERR_ST1_WRBRRB_SHFT	42
#घोषणा PI_ERR_ST1_CRBSTAT_MASK 0x001ff80000000000
#घोषणा PI_ERR_ST1_CRBSTAT_SHFT 43
#घोषणा PI_ERR_ST1_MSGSRC_MASK	0xffe0000000000000
#घोषणा PI_ERR_ST1_MSGSRC_SHFT	53

/* Fields in the error stack */
#घोषणा PI_ERR_STK_TYPE_MASK	0x0000000000000003
#घोषणा PI_ERR_STK_TYPE_SHFT	0
#घोषणा PI_ERR_STK_SUPPL_MASK	0x0000000000000038
#घोषणा PI_ERR_STK_SUPPL_SHFT	3
#घोषणा PI_ERR_STK_REQNUM_MASK	0x00000000000001c0
#घोषणा PI_ERR_STK_REQNUM_SHFT	6
#घोषणा PI_ERR_STK_CRBNUM_MASK	0x0000000000000e00
#घोषणा PI_ERR_STK_CRBNUM_SHFT	9
#घोषणा PI_ERR_STK_WRBRRB_MASK	0x0000000000001000
#घोषणा PI_ERR_STK_WRBRRB_SHFT	12
#घोषणा PI_ERR_STK_CRBSTAT_MASK 0x00000000007fe000
#घोषणा PI_ERR_STK_CRBSTAT_SHFT 13
#घोषणा PI_ERR_STK_CMD_MASK	0x000000007f800000
#घोषणा PI_ERR_STK_CMD_SHFT	23
#घोषणा PI_ERR_STK_ADDR_MASK	0xffffffff80000000
#घोषणा PI_ERR_STK_ADDR_SHFT	31

/* Error type in the error status or stack on Read CRBs */
#घोषणा PI_ERR_RD_PRERR		1
#घोषणा PI_ERR_RD_DERR		2
#घोषणा PI_ERR_RD_TERR		3

/* Error type in the error status or stack on Write CRBs */
#घोषणा PI_ERR_WR_WERR		0
#घोषणा PI_ERR_WR_PWERR		1
#घोषणा PI_ERR_WR_TERR		3

/* Read or Write CRB in error status or stack */
#घोषणा PI_ERR_RRB	0
#घोषणा PI_ERR_WRB	1
#घोषणा PI_ERR_ANY_CRB	2

/* Address masks in the error status and error stack are not the same */
#घोषणा ERR_STK_ADDR_SHFT	7
#घोषणा ERR_STAT0_ADDR_SHFT	3

#घोषणा PI_MIN_STACK_SIZE 4096	/* For figuring out the size to set */
#घोषणा PI_STACK_SIZE_SHFT	12	/* 4k */

#घोषणा ERR_STACK_SIZE_BYTES(_sz) \
       ((_sz) ? (PI_MIN_STACK_SIZE << ((_sz) - 1)) : 0)

#अगर_अघोषित __ASSEMBLY__
/*
 * क्रमmat of error stack and error status रेजिस्टरs.
 */

काष्ठा err_stack_क्रमmat अणु
	u64	sk_addr	   : 33,   /* address */
		sk_cmd	   :  8,   /* message command */
		sk_crb_sts : 10,   /* status from RRB or WRB */
		sk_rw_rb   :  1,   /* RRB == 0, WRB == 1 */
		sk_crb_num :  3,   /* WRB (0 to 7) or RRB (0 to 4) */
		sk_t5_req  :  3,   /* RRB T5 request number */
		sk_suppl   :  3,   /* lowest 3 bit of supplemental */
		sk_err_type:  3;   /* error type	*/
पूर्ण;

प्रकार जोड़ pi_err_stack अणु
	u64	pi_stk_word;
	काष्ठा	err_stack_क्रमmat pi_stk_fmt;
पूर्ण pi_err_stack_t;

काष्ठा err_status0_क्रमmat अणु
	u64	s0_valid   :  1,   /* Valid */
		s0_ovr_run :  1,   /* Overrun, spooled to memory */
		s0_addr	   : 37,   /* address */
		s0_cmd	   :  8,   /* message command */
		s0_supl	   : 11,   /* message supplemental field */
		s0_t5_req  :  3,   /* RRB T5 request number */
		s0_err_type:  3;   /* error type */
पूर्ण;

प्रकार जोड़ pi_err_stat0 अणु
	u64	pi_stat0_word;
	काष्ठा err_status0_क्रमmat pi_stat0_fmt;
पूर्ण pi_err_stat0_t;

काष्ठा err_status1_क्रमmat अणु
	u64	s1_src	   : 11,   /* message source */
		s1_crb_sts : 10,   /* status from RRB or WRB */
		s1_rw_rb   :  1,   /* RRB == 0, WRB == 1 */
		s1_crb_num :  3,   /* WRB (0 to 7) or RRB (0 to 4) */
		s1_inval_cnt:10,   /* चिन्हित invalidate counter RRB */
		s1_to_cnt  :  8,   /* crb समयout counter */
		s1_spl_cnt : 21;   /* number spooled to memory */
पूर्ण;

प्रकार जोड़ pi_err_stat1 अणु
	u64	pi_stat1_word;
	काष्ठा err_status1_क्रमmat pi_stat1_fmt;
पूर्ण pi_err_stat1_t;

प्रकार u64	rtc_समय_प्रकार;

#पूर्ण_अगर /* !__ASSEMBLY__ */


/* Bits in PI_SYSAD_ERRCHK_EN */
#घोषणा PI_SYSAD_ERRCHK_ECCGEN	0x01	/* Enable ECC generation	    */
#घोषणा PI_SYSAD_ERRCHK_QUALGEN 0x02	/* Enable data quality संकेत gen.  */
#घोषणा PI_SYSAD_ERRCHK_SADP	0x04	/* Enable SysAD parity checking	    */
#घोषणा PI_SYSAD_ERRCHK_CMDP	0x08	/* Enable SysCmd parity checking    */
#घोषणा PI_SYSAD_ERRCHK_STATE	0x10	/* Enable SysState parity checking  */
#घोषणा PI_SYSAD_ERRCHK_QUAL	0x20	/* Enable data quality checking	    */
#घोषणा PI_SYSAD_CHECK_ALL	0x3f	/* Generate and check all संकेतs.  */

/* Interrupt pending bits on R10000 */

#घोषणा HUB_IP_PEND0		0x0400
#घोषणा HUB_IP_PEND1_CC		0x0800
#घोषणा HUB_IP_RT		0x1000
#घोषणा HUB_IP_PROF		0x2000
#घोषणा HUB_IP_ERROR		0x4000
#घोषणा HUB_IP_MASK		0x7c00

/* PI_RT_LOCAL_CTRL mask and shअगरt definitions */

#घोषणा PRLC_USE_INT_SHFT	16
#घोषणा PRLC_USE_INT_MASK	(UINT64_CAST 1 << 16)
#घोषणा PRLC_USE_INT		(UINT64_CAST 1 << 16)
#घोषणा PRLC_GCLK_SHFT		15
#घोषणा PRLC_GCLK_MASK		(UINT64_CAST 1 << 15)
#घोषणा PRLC_GCLK		(UINT64_CAST 1 << 15)
#घोषणा PRLC_GCLK_COUNT_SHFT	8
#घोषणा PRLC_GCLK_COUNT_MASK	(UINT64_CAST 0x7f << 8)
#घोषणा PRLC_MAX_COUNT_SHFT	1
#घोषणा PRLC_MAX_COUNT_MASK	(UINT64_CAST 0x7f << 1)
#घोषणा PRLC_GCLK_EN_SHFT	0
#घोषणा PRLC_GCLK_EN_MASK	(UINT64_CAST 1)
#घोषणा PRLC_GCLK_EN		(UINT64_CAST 1)

/* PI_RT_FILTER_CTRL mask and shअगरt definitions */

/*
 * Bits क्रम NACK_CNT_A/B and NACK_CMP
 */
#घोषणा PI_NACK_CNT_EN_SHFT	20
#घोषणा PI_NACK_CNT_EN_MASK	0x100000
#घोषणा PI_NACK_CNT_MASK	0x0fffff
#घोषणा PI_NACK_CNT_MAX		0x0fffff

#पूर्ण_अगर /* _ASM_SN_SN0_HUBPI_H */
