<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Derived from IRIX <sys/SN/SN0/hubni.h>, Revision 1.27.
 *
 * Copyright (C) 1992-1997, 1999 Silicon Graphics, Inc.
 * Copyright (C) 1999 by Ralf Baechle
 */
#अगर_अघोषित _ASM_SGI_SN0_HUBNI_H
#घोषणा _ASM_SGI_SN0_HUBNI_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>
#पूर्ण_अगर

/*
 * Hub Network Interface रेजिस्टरs
 *
 * All रेजिस्टरs in this file are subject to change until Hub chip tapeout.
 */

#घोषणा NI_BASE			0x600000
#घोषणा NI_BASE_TABLES		0x630000

#घोषणा NI_STATUS_REV_ID	0x600000 /* Hub network status, rev, and ID */
#घोषणा NI_PORT_RESET		0x600008 /* Reset the network पूर्णांकerface	    */
#घोषणा NI_PROTECTION		0x600010 /* NI रेजिस्टर access permissions  */
#घोषणा NI_GLOBAL_PARMS		0x600018 /* LLP parameters		    */
#घोषणा NI_SCRATCH_REG0		0x600100 /* Scratch रेजिस्टर 0 (64 bits)    */
#घोषणा NI_SCRATCH_REG1		0x600108 /* Scratch रेजिस्टर 1 (64 bits)    */
#घोषणा NI_DIAG_PARMS		0x600110 /* Parameters क्रम diags	    */

#घोषणा NI_VECTOR_PARMS		0x600200 /* Vector PIO routing parameters   */
#घोषणा NI_VECTOR		0x600208 /* Vector PIO route		    */
#घोषणा NI_VECTOR_DATA		0x600210 /* Vector PIO data		    */
#घोषणा NI_VECTOR_STATUS	0x600300 /* Vector PIO वापस status	    */
#घोषणा NI_RETURN_VECTOR	0x600308 /* Vector PIO वापस vector	    */
#घोषणा NI_VECTOR_READ_DATA	0x600310 /* Vector PIO पढ़ो data	    */
#घोषणा NI_VECTOR_CLEAR		0x600380 /* Vector PIO पढ़ो & clear status  */

#घोषणा NI_IO_PROTECT		0x600400 /* PIO protection bits		    */
#घोषणा NI_IO_PROT_OVRRD	0x600408 /* PIO protection bit override	    */

#घोषणा NI_AGE_CPU0_MEMORY	0x600500 /* CPU 0 memory age control	    */
#घोषणा NI_AGE_CPU0_PIO		0x600508 /* CPU 0 PIO age control	    */
#घोषणा NI_AGE_CPU1_MEMORY	0x600510 /* CPU 1 memory age control	    */
#घोषणा NI_AGE_CPU1_PIO		0x600518 /* CPU 1 PIO age control	    */
#घोषणा NI_AGE_GBR_MEMORY	0x600520 /* GBR memory age control	    */
#घोषणा NI_AGE_GBR_PIO		0x600528 /* GBR PIO age control		    */
#घोषणा NI_AGE_IO_MEMORY	0x600530 /* IO memory age control	    */
#घोषणा NI_AGE_IO_PIO		0x600538 /* IO PIO age control		    */
#घोषणा NI_AGE_REG_MIN		NI_AGE_CPU0_MEMORY
#घोषणा NI_AGE_REG_MAX		NI_AGE_IO_PIO

#घोषणा NI_PORT_PARMS		0x608000 /* LLP Parameters		    */
#घोषणा NI_PORT_ERROR		0x608008 /* LLP Errors			    */
#घोषणा NI_PORT_ERROR_CLEAR	0x608088 /* Clear the error bits	    */

#घोषणा NI_META_TABLE0		0x638000 /* First meta routing table entry  */
#घोषणा NI_META_TABLE(_x)	(NI_META_TABLE0 + (8 * (_x)))
#घोषणा NI_META_ENTRIES		32

#घोषणा NI_LOCAL_TABLE0		0x638100 /* First local routing table entry */
#घोषणा NI_LOCAL_TABLE(_x)	(NI_LOCAL_TABLE0 + (8 * (_x)))
#घोषणा NI_LOCAL_ENTRIES	16

/*
 * NI_STATUS_REV_ID mask and shअगरt definitions
 * Have to use UINT64_CAST instead of 'L' suffix, क्रम assembler.
 */

#घोषणा NSRI_8BITMODE_SHFT	30
#घोषणा NSRI_8BITMODE_MASK	(UINT64_CAST 0x1 << 30)
#घोषणा NSRI_LINKUP_SHFT	29
#घोषणा NSRI_LINKUP_MASK	(UINT64_CAST 0x1 << 29)
#घोषणा NSRI_DOWNREASON_SHFT	28		/* 0=failed, 1=never came   */
#घोषणा NSRI_DOWNREASON_MASK	(UINT64_CAST 0x1 << 28) /*    out of reset. */
#घोषणा NSRI_MORENODES_SHFT	18
#घोषणा NSRI_MORENODES_MASK	(UINT64_CAST 1 << 18)	/* Max. # of nodes  */
#घोषणा	 MORE_MEMORY		0
#घोषणा	 MORE_NODES		1
#घोषणा NSRI_REGIONSIZE_SHFT	17
#घोषणा NSRI_REGIONSIZE_MASK	(UINT64_CAST 1 << 17)	/* Granularity	    */
#घोषणा	 REGIONSIZE_FINE	1
#घोषणा	 REGIONSIZE_COARSE	0
#घोषणा NSRI_NODEID_SHFT	8
#घोषणा NSRI_NODEID_MASK	(UINT64_CAST 0x1ff << 8)/* Node (Hub) ID    */
#घोषणा NSRI_REV_SHFT		4
#घोषणा NSRI_REV_MASK		(UINT64_CAST 0xf << 4)	/* Chip Revision    */
#घोषणा NSRI_CHIPID_SHFT	0
#घोषणा NSRI_CHIPID_MASK	(UINT64_CAST 0xf)	/* Chip type ID	    */

/*
 * In fine mode, each node is a region.	 In coarse mode, there are
 * eight nodes per region.
 */
#घोषणा NASID_TO_FINEREG_SHFT	0
#घोषणा NASID_TO_COARSEREG_SHFT 3

/* NI_PORT_RESET mask definitions */

#घोषणा NPR_PORTRESET		(UINT64_CAST 1 << 7)	/* Send warm reset  */
#घोषणा NPR_LINKRESET		(UINT64_CAST 1 << 1)	/* Send link reset  */
#घोषणा NPR_LOCALRESET		(UINT64_CAST 1)		/* Reset entire hub */

/* NI_PROTECTION mask and shअगरt definitions */

#घोषणा NPROT_RESETOK		(UINT64_CAST 1)

/* NI_GLOBAL_PARMS mask and shअगरt definitions */

#घोषणा NGP_MAXRETRY_SHFT	48		/* Maximum retries	    */
#घोषणा NGP_MAXRETRY_MASK	(UINT64_CAST 0x3ff << 48)
#घोषणा NGP_TAILTOWRAP_SHFT	32		/* Tail समयout wrap	    */
#घोषणा NGP_TAILTOWRAP_MASK	(UINT64_CAST 0xffff << 32)

#घोषणा NGP_CREDITTOVAL_SHFT	16		/* Tail समयout wrap	    */
#घोषणा NGP_CREDITTOVAL_MASK	(UINT64_CAST 0xf << 16)
#घोषणा NGP_TAILTOVAL_SHFT	4		/* Tail समयout value	    */
#घोषणा NGP_TAILTOVAL_MASK	(UINT64_CAST 0xf << 4)

/* NI_DIAG_PARMS mask and shअगरt definitions */

#घोषणा NDP_PORTTORESET		(UINT64_CAST 1 << 18)	/* Port पंचांगout reset */
#घोषणा NDP_LLP8BITMODE		(UINT64_CAST 1 << 12)	/* LLP 8-bit mode   */
#घोषणा NDP_PORTDISABLE		(UINT64_CAST 1 <<  6)	/* Port disable	    */
#घोषणा NDP_SENDERROR		(UINT64_CAST 1)		/* Send data error  */

/*
 * NI_VECTOR_PARMS mask and shअगरt definitions.
 * TYPE may be any of the first four PIOTYPEs defined under NI_VECTOR_STATUS.
 */

#घोषणा NVP_PIOID_SHFT		40
#घोषणा NVP_PIOID_MASK		(UINT64_CAST 0x3ff << 40)
#घोषणा NVP_WRITEID_SHFT	32
#घोषणा NVP_WRITEID_MASK	(UINT64_CAST 0xff << 32)
#घोषणा NVP_ADDRESS_MASK	(UINT64_CAST 0xffff8)	/* Bits 19:3	    */
#घोषणा NVP_TYPE_SHFT		0
#घोषणा NVP_TYPE_MASK		(UINT64_CAST 0x3)

/* NI_VECTOR_STATUS mask and shअगरt definitions */

#घोषणा NVS_VALID		(UINT64_CAST 1 << 63)
#घोषणा NVS_OVERRUN		(UINT64_CAST 1 << 62)
#घोषणा NVS_TARGET_SHFT		51
#घोषणा NVS_TARGET_MASK		(UINT64_CAST 0x3ff << 51)
#घोषणा NVS_PIOID_SHFT		40
#घोषणा NVS_PIOID_MASK		(UINT64_CAST 0x3ff << 40)
#घोषणा NVS_WRITEID_SHFT	32
#घोषणा NVS_WRITEID_MASK	(UINT64_CAST 0xff << 32)
#घोषणा NVS_ADDRESS_MASK	(UINT64_CAST 0xfffffff8)   /* Bits 31:3	    */
#घोषणा NVS_TYPE_SHFT		0
#घोषणा NVS_TYPE_MASK		(UINT64_CAST 0x7)
#घोषणा NVS_ERROR_MASK		(UINT64_CAST 0x4)  /* bit set means error */


#घोषणा	 PIOTYPE_READ		0	/* VECTOR_PARMS and VECTOR_STATUS   */
#घोषणा	 PIOTYPE_WRITE		1	/* VECTOR_PARMS and VECTOR_STATUS   */
#घोषणा	 PIOTYPE_UNDEFINED	2	/* VECTOR_PARMS and VECTOR_STATUS   */
#घोषणा	 PIOTYPE_EXCHANGE	3	/* VECTOR_PARMS and VECTOR_STATUS   */
#घोषणा	 PIOTYPE_ADDR_ERR	4	/* VECTOR_STATUS only		    */
#घोषणा	 PIOTYPE_CMD_ERR	5	/* VECTOR_STATUS only		    */
#घोषणा	 PIOTYPE_PROT_ERR	6	/* VECTOR_STATUS only		    */
#घोषणा	 PIOTYPE_UNKNOWN	7	/* VECTOR_STATUS only		    */

/* NI_AGE_XXX mask and shअगरt definitions */

#घोषणा NAGE_VCH_SHFT		10
#घोषणा NAGE_VCH_MASK		(UINT64_CAST 3 << 10)
#घोषणा NAGE_CC_SHFT		8
#घोषणा NAGE_CC_MASK		(UINT64_CAST 3 << 8)
#घोषणा NAGE_AGE_SHFT		0
#घोषणा NAGE_AGE_MASK		(UINT64_CAST 0xff)
#घोषणा NAGE_MASK		(NAGE_VCH_MASK | NAGE_CC_MASK | NAGE_AGE_MASK)

#घोषणा	 VCHANNEL_A		0
#घोषणा	 VCHANNEL_B		1
#घोषणा	 VCHANNEL_ANY		2

/* NI_PORT_PARMS mask and shअगरt definitions */

#घोषणा NPP_शून्यTO_SHFT		10
#घोषणा NPP_शून्यTO_MASK		(UINT64_CAST 0x3f << 16)
#घोषणा NPP_MAXBURST_SHFT	0
#घोषणा NPP_MAXBURST_MASK	(UINT64_CAST 0x3ff)
#घोषणा NPP_RESET_DFLT_HUB20	((UINT64_CAST 1	    << NPP_शून्यTO_SHFT) | \
				 (UINT64_CAST 0x3f0 << NPP_MAXBURST_SHFT))
#घोषणा NPP_RESET_DEFAULTS	((UINT64_CAST 6	    << NPP_शून्यTO_SHFT) | \
				 (UINT64_CAST 0x3f0 << NPP_MAXBURST_SHFT))


/* NI_PORT_ERROR mask and shअगरt definitions */

#घोषणा NPE_LINKRESET		(UINT64_CAST 1 << 37)
#घोषणा NPE_INTERNALERROR	(UINT64_CAST 1 << 36)
#घोषणा NPE_BADMESSAGE		(UINT64_CAST 1 << 35)
#घोषणा NPE_BADDEST		(UINT64_CAST 1 << 34)
#घोषणा NPE_FIFOOVERFLOW	(UINT64_CAST 1 << 33)
#घोषणा NPE_CREDITTO_SHFT	28
#घोषणा NPE_CREDITTO_MASK	(UINT64_CAST 0xf << 28)
#घोषणा NPE_TAILTO_SHFT		24
#घोषणा NPE_TAILTO_MASK		(UINT64_CAST 0xf << 24)
#घोषणा NPE_RETRYCOUNT_SHFT	16
#घोषणा NPE_RETRYCOUNT_MASK	(UINT64_CAST 0xff << 16)
#घोषणा NPE_CBERRCOUNT_SHFT	8
#घोषणा NPE_CBERRCOUNT_MASK	(UINT64_CAST 0xff << 8)
#घोषणा NPE_SNERRCOUNT_SHFT	0
#घोषणा NPE_SNERRCOUNT_MASK	(UINT64_CAST 0xff << 0)
#घोषणा NPE_MASK		0x3effffffff

#घोषणा NPE_COUNT_MAX		0xff

#घोषणा NPE_FATAL_ERRORS	(NPE_LINKRESET | NPE_INTERNALERROR |	\
				 NPE_BADMESSAGE | NPE_BADDEST |		\
				 NPE_FIFOOVERFLOW | NPE_CREDITTO_MASK | \
				 NPE_TAILTO_MASK)

/* NI_META_TABLE mask and shअगरt definitions */

#घोषणा NMT_EXIT_PORT_MASK (UINT64_CAST 0xf)

/* NI_LOCAL_TABLE mask and shअगरt definitions */

#घोषणा NLT_EXIT_PORT_MASK (UINT64_CAST 0xf)

#अगर_अघोषित __ASSEMBLY__

प्रकार जोड़	hubni_port_error_u अणु
	u64	nipe_reg_value;
	काष्ठा अणु
	    u64 nipe_rsvd:	26,	/* unused */
		nipe_lnk_reset:	 1,	/* link reset */
		nipe_पूर्णांकl_err:	 1,	/* पूर्णांकernal error */
		nipe_bad_msg:	 1,	/* bad message */
		nipe_bad_dest:	 1,	/* bad dest	*/
		nipe_fअगरo_ovfl:	 1,	/* fअगरo overflow */
		nipe_rsvd1:	 1,	/* unused */
		nipe_credit_to:	 4,	/* credit समयout */
		nipe_tail_to:	 4,	/* tail समयout */
		nipe_retry_cnt:	 8,	/* retry error count */
		nipe_cb_cnt:	 8,	/* checkbit error count */
		nipe_sn_cnt:	 8;	/* sequence number count */
	पूर्ण nipe_fields_s;
पूर्ण hubni_port_error_t;

#घोषणा NI_LLP_RETRY_MAX	0xff
#घोषणा NI_LLP_CB_MAX		0xff
#घोषणा NI_LLP_SN_MAX		0xff

अटल अंतरभूत पूर्णांक get_region_shअगरt(व्योम)
अणु
	अगर (LOCAL_HUB_L(NI_STATUS_REV_ID) & NSRI_REGIONSIZE_MASK)
		वापस NASID_TO_FINEREG_SHFT;

	वापस NASID_TO_COARSEREG_SHFT;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_SGI_SN0_HUBNI_H */
