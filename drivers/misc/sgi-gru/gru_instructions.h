<शैली गुरु>
/*
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#अगर_अघोषित __GRU_INSTRUCTIONS_H__
#घोषणा __GRU_INSTRUCTIONS_H__

बाह्य पूर्णांक gru_check_status_proc(व्योम *cb);
बाह्य पूर्णांक gru_रुको_proc(व्योम *cb);
बाह्य व्योम gru_रुको_पात_proc(व्योम *cb);



/*
 * Architecture dependent functions
 */

#अगर defined(CONFIG_IA64)
#समावेश <linux/compiler.h>
#समावेश <यंत्र/पूर्णांकrinsics.h>
#घोषणा __flush_cache(p)		ia64_fc((अचिन्हित दीर्घ)p)
/* Use अस्थिर on IA64 to ensure ordering via st4.rel */
#घोषणा gru_ordered_store_uदीर्घ(p, v)					\
		करो अणु							\
			barrier();					\
			*((अस्थिर अचिन्हित दीर्घ *)(p)) = v; /* क्रमce st.rel */	\
		पूर्ण जबतक (0)
#या_अगर defined(CONFIG_X86_64)
#समावेश <यंत्र/cacheflush.h>
#घोषणा __flush_cache(p)		clflush(p)
#घोषणा gru_ordered_store_uदीर्घ(p, v)					\
		करो अणु							\
			barrier();					\
			*(अचिन्हित दीर्घ *)p = v;			\
		पूर्ण जबतक (0)
#अन्यथा
#त्रुटि "Unsupported architecture"
#पूर्ण_अगर

/*
 * Control block status and exception codes
 */
#घोषणा CBS_IDLE			0
#घोषणा CBS_EXCEPTION			1
#घोषणा CBS_ACTIVE			2
#घोषणा CBS_CALL_OS			3

/* CB substatus biपंचांगasks */
#घोषणा CBSS_MSG_QUEUE_MASK		7
#घोषणा CBSS_IMPLICIT_ABORT_ACTIVE_MASK	8

/* CB substatus message queue values (low 3 bits of substatus) */
#घोषणा CBSS_NO_ERROR			0
#घोषणा CBSS_LB_OVERFLOWED		1
#घोषणा CBSS_QLIMIT_REACHED		2
#घोषणा CBSS_PAGE_OVERFLOW		3
#घोषणा CBSS_AMO_NACKED			4
#घोषणा CBSS_PUT_NACKED			5

/*
 * Structure used to fetch exception detail क्रम CBs that terminate with
 * CBS_EXCEPTION
 */
काष्ठा control_block_extended_exc_detail अणु
	अचिन्हित दीर्घ	cb;
	पूर्णांक		opc;
	पूर्णांक		ecause;
	पूर्णांक		exopc;
	दीर्घ		exceptdet0;
	पूर्णांक		exceptdet1;
	पूर्णांक		cbrstate;
	पूर्णांक		cbrexecstatus;
पूर्ण;

/*
 * Inकाष्ठाion क्रमmats
 */

/*
 * Generic inकाष्ठाion क्रमmat.
 * This definition has precise bit field definitions.
 */
काष्ठा gru_inकाष्ठाion_bits अणु
    /* DW 0  - low */
    अचिन्हित पूर्णांक		icmd:      1;
    अचिन्हित अक्षर		ima:	   3;	/* CB_DelRep, unmapped mode */
    अचिन्हित अक्षर		reserved0: 4;
    अचिन्हित पूर्णांक		xtype:     3;
    अचिन्हित पूर्णांक		iaa0:      2;
    अचिन्हित पूर्णांक		iaa1:      2;
    अचिन्हित अक्षर		reserved1: 1;
    अचिन्हित अक्षर		opc:       8;	/* opcode */
    अचिन्हित अक्षर		exopc:     8;	/* extended opcode */
    /* DW 0  - high */
    अचिन्हित पूर्णांक		idef2:    22;	/* TRi0 */
    अचिन्हित अक्षर		reserved2: 2;
    अचिन्हित अक्षर		istatus:   2;
    अचिन्हित अक्षर		isubstatus:4;
    अचिन्हित अक्षर		reserved3: 1;
    अचिन्हित अक्षर		tlb_fault_color: 1;
    /* DW 1 */
    अचिन्हित दीर्घ		idef4;		/* 42 bits: TRi1, BufSize */
    /* DW 2-6 */
    अचिन्हित दीर्घ		idef1;		/* BAddr0 */
    अचिन्हित दीर्घ		idef5;		/* Nelem */
    अचिन्हित दीर्घ		idef6;		/* Stride, Opeअक्रम1 */
    अचिन्हित दीर्घ		idef3;		/* BAddr1, Value, Opeअक्रम2 */
    अचिन्हित दीर्घ		reserved4;
    /* DW 7 */
    अचिन्हित दीर्घ		avalue;		 /* AValue */
पूर्ण;

/*
 * Generic inकाष्ठाion with मित्रlier names. This क्रमmat is used
 * क्रम अंतरभूत inकाष्ठाions.
 */
काष्ठा gru_inकाष्ठाion अणु
    /* DW 0 */
    जोड़ अणु
    	अचिन्हित दीर्घ		op64;    /* icmd,xtype,iaa0,ima,opc,tri0 */
	काष्ठा अणु
		अचिन्हित पूर्णांक	op32;
		अचिन्हित पूर्णांक	tri0;
	पूर्ण;
    पूर्ण;
    अचिन्हित दीर्घ		tri1_bufsize;		/* DW 1 */
    अचिन्हित दीर्घ		baddr0;			/* DW 2 */
    अचिन्हित दीर्घ		nelem;			/* DW 3 */
    अचिन्हित दीर्घ		op1_stride;		/* DW 4 */
    अचिन्हित दीर्घ		op2_value_baddr1;	/* DW 5 */
    अचिन्हित दीर्घ		reserved0;		/* DW 6 */
    अचिन्हित दीर्घ		avalue;			/* DW 7 */
पूर्ण;

/* Some shअगरts and masks क्रम the low 64 bits of a GRU command */
#घोषणा GRU_CB_ICMD_SHFT	0
#घोषणा GRU_CB_ICMD_MASK	0x1
#घोषणा GRU_CB_XTYPE_SHFT	8
#घोषणा GRU_CB_XTYPE_MASK	0x7
#घोषणा GRU_CB_IAA0_SHFT	11
#घोषणा GRU_CB_IAA0_MASK	0x3
#घोषणा GRU_CB_IAA1_SHFT	13
#घोषणा GRU_CB_IAA1_MASK	0x3
#घोषणा GRU_CB_IMA_SHFT		1
#घोषणा GRU_CB_IMA_MASK		0x3
#घोषणा GRU_CB_OPC_SHFT		16
#घोषणा GRU_CB_OPC_MASK		0xff
#घोषणा GRU_CB_EXOPC_SHFT	24
#घोषणा GRU_CB_EXOPC_MASK	0xff
#घोषणा GRU_IDEF2_SHFT		32
#घोषणा GRU_IDEF2_MASK		0x3ffff
#घोषणा GRU_ISTATUS_SHFT	56
#घोषणा GRU_ISTATUS_MASK	0x3

/* GRU inकाष्ठाion opcodes (opc field) */
#घोषणा OP_NOP		0x00
#घोषणा OP_BCOPY	0x01
#घोषणा OP_VLOAD	0x02
#घोषणा OP_IVLOAD	0x03
#घोषणा OP_VSTORE	0x04
#घोषणा OP_IVSTORE	0x05
#घोषणा OP_VSET		0x06
#घोषणा OP_IVSET	0x07
#घोषणा OP_MESQ		0x08
#घोषणा OP_GAMXR	0x09
#घोषणा OP_GAMIR	0x0a
#घोषणा OP_GAMIRR	0x0b
#घोषणा OP_GAMER	0x0c
#घोषणा OP_GAMERR	0x0d
#घोषणा OP_BSTORE	0x0e
#घोषणा OP_VFLUSH	0x0f


/* Extended opcodes values (exopc field) */

/* GAMIR - AMOs with implicit opeअक्रमs */
#घोषणा EOP_IR_FETCH	0x01 /* Plain fetch of memory */
#घोषणा EOP_IR_CLR	0x02 /* Fetch and clear */
#घोषणा EOP_IR_INC	0x05 /* Fetch and increment */
#घोषणा EOP_IR_DEC	0x07 /* Fetch and decrement */
#घोषणा EOP_IR_QCHK1	0x0d /* Queue check, 64 byte msg */
#घोषणा EOP_IR_QCHK2	0x0e /* Queue check, 128 byte msg */

/* GAMIRR - Registered AMOs with implicit opeअक्रमs */
#घोषणा EOP_IRR_FETCH	0x01 /* Registered fetch of memory */
#घोषणा EOP_IRR_CLR	0x02 /* Registered fetch and clear */
#घोषणा EOP_IRR_INC	0x05 /* Registered fetch and increment */
#घोषणा EOP_IRR_DEC	0x07 /* Registered fetch and decrement */
#घोषणा EOP_IRR_DECZ	0x0f /* Registered fetch and decrement, update on zero*/

/* GAMER - AMOs with explicit opeअक्रमs */
#घोषणा EOP_ER_SWAP	0x00 /* Exchange argument and memory */
#घोषणा EOP_ER_OR	0x01 /* Logical OR with memory */
#घोषणा EOP_ER_AND	0x02 /* Logical AND with memory */
#घोषणा EOP_ER_XOR	0x03 /* Logical XOR with memory */
#घोषणा EOP_ER_ADD	0x04 /* Add value to memory */
#घोषणा EOP_ER_CSWAP	0x08 /* Compare with opeअक्रम2, ग_लिखो opeअक्रम1 अगर match*/
#घोषणा EOP_ER_CADD	0x0c /* Queue check, opeअक्रम1*64 byte msg */

/* GAMERR - Registered AMOs with explicit opeअक्रमs */
#घोषणा EOP_ERR_SWAP	0x00 /* Exchange argument and memory */
#घोषणा EOP_ERR_OR	0x01 /* Logical OR with memory */
#घोषणा EOP_ERR_AND	0x02 /* Logical AND with memory */
#घोषणा EOP_ERR_XOR	0x03 /* Logical XOR with memory */
#घोषणा EOP_ERR_ADD	0x04 /* Add value to memory */
#घोषणा EOP_ERR_CSWAP	0x08 /* Compare with opeअक्रम2, ग_लिखो opeअक्रम1 अगर match*/
#घोषणा EOP_ERR_EPOLL	0x09 /* Poll क्रम equality */
#घोषणा EOP_ERR_NPOLL	0x0a /* Poll क्रम inequality */

/* GAMXR - SGI Arithmetic unit */
#घोषणा EOP_XR_CSWAP	0x0b /* Masked compare exchange */


/* Transfer types (xtype field) */
#घोषणा XTYPE_B		0x0	/* byte */
#घोषणा XTYPE_S		0x1	/* लघु (2-byte) */
#घोषणा XTYPE_W		0x2	/* word (4-byte) */
#घोषणा XTYPE_DW	0x3	/* द्विगुनword (8-byte) */
#घोषणा XTYPE_CL	0x6	/* cacheline (64-byte) */


/* Inकाष्ठाion access attributes (iaa0, iaa1 fields) */
#घोषणा IAA_RAM		0x0	/* normal cached RAM access */
#घोषणा IAA_NCRAM	0x2	/* noncoherent RAM access */
#घोषणा IAA_MMIO	0x1	/* noncoherent memory-mapped I/O space */
#घोषणा IAA_REGISTER	0x3	/* memory-mapped रेजिस्टरs, etc. */


/* Inकाष्ठाion mode attributes (ima field) */
#घोषणा IMA_MAPPED	0x0	/* Virtual mode  */
#घोषणा IMA_CB_DELAY	0x1	/* hold पढ़ो responses until status changes */
#घोषणा IMA_UNMAPPED	0x2	/* bypass the TLBs (OS only) */
#घोषणा IMA_INTERRUPT	0x4	/* Interrupt when inकाष्ठाion completes */

/* CBE ecause bits */
#घोषणा CBE_CAUSE_RI				(1 << 0)
#घोषणा CBE_CAUSE_INVALID_INSTRUCTION		(1 << 1)
#घोषणा CBE_CAUSE_UNMAPPED_MODE_FORBIDDEN	(1 << 2)
#घोषणा CBE_CAUSE_PE_CHECK_DATA_ERROR		(1 << 3)
#घोषणा CBE_CAUSE_IAA_GAA_MISMATCH		(1 << 4)
#घोषणा CBE_CAUSE_DATA_SEGMENT_LIMIT_EXCEPTION	(1 << 5)
#घोषणा CBE_CAUSE_OS_FATAL_TLB_FAULT		(1 << 6)
#घोषणा CBE_CAUSE_EXECUTION_HW_ERROR		(1 << 7)
#घोषणा CBE_CAUSE_TLBHW_ERROR			(1 << 8)
#घोषणा CBE_CAUSE_RA_REQUEST_TIMEOUT		(1 << 9)
#घोषणा CBE_CAUSE_HA_REQUEST_TIMEOUT		(1 << 10)
#घोषणा CBE_CAUSE_RA_RESPONSE_FATAL		(1 << 11)
#घोषणा CBE_CAUSE_RA_RESPONSE_NON_FATAL		(1 << 12)
#घोषणा CBE_CAUSE_HA_RESPONSE_FATAL		(1 << 13)
#घोषणा CBE_CAUSE_HA_RESPONSE_NON_FATAL		(1 << 14)
#घोषणा CBE_CAUSE_ADDRESS_SPACE_DECODE_ERROR	(1 << 15)
#घोषणा CBE_CAUSE_PROTOCOL_STATE_DATA_ERROR	(1 << 16)
#घोषणा CBE_CAUSE_RA_RESPONSE_DATA_ERROR	(1 << 17)
#घोषणा CBE_CAUSE_HA_RESPONSE_DATA_ERROR	(1 << 18)
#घोषणा CBE_CAUSE_FORCED_ERROR			(1 << 19)

/* CBE cbrexecstatus bits */
#घोषणा CBR_EXS_ABORT_OCC_BIT			0
#घोषणा CBR_EXS_INT_OCC_BIT			1
#घोषणा CBR_EXS_PENDING_BIT			2
#घोषणा CBR_EXS_QUEUED_BIT			3
#घोषणा CBR_EXS_TLB_INVAL_BIT			4
#घोषणा CBR_EXS_EXCEPTION_BIT			5
#घोषणा CBR_EXS_CB_INT_PENDING_BIT		6

#घोषणा CBR_EXS_ABORT_OCC			(1 << CBR_EXS_ABORT_OCC_BIT)
#घोषणा CBR_EXS_INT_OCC				(1 << CBR_EXS_INT_OCC_BIT)
#घोषणा CBR_EXS_PENDING				(1 << CBR_EXS_PENDING_BIT)
#घोषणा CBR_EXS_QUEUED				(1 << CBR_EXS_QUEUED_BIT)
#घोषणा CBR_EXS_TLB_INVAL			(1 << CBR_EXS_TLB_INVAL_BIT)
#घोषणा CBR_EXS_EXCEPTION			(1 << CBR_EXS_EXCEPTION_BIT)
#घोषणा CBR_EXS_CB_INT_PENDING			(1 << CBR_EXS_CB_INT_PENDING_BIT)

/*
 * Exceptions are retried क्रम the following हालs. If any OTHER bits are set
 * in ecause, the exception is not retryable.
 */
#घोषणा EXCEPTION_RETRY_BITS (CBE_CAUSE_EXECUTION_HW_ERROR |		\
			      CBE_CAUSE_TLBHW_ERROR |			\
			      CBE_CAUSE_RA_REQUEST_TIMEOUT |		\
			      CBE_CAUSE_RA_RESPONSE_NON_FATAL |		\
			      CBE_CAUSE_HA_RESPONSE_NON_FATAL |		\
			      CBE_CAUSE_RA_RESPONSE_DATA_ERROR |	\
			      CBE_CAUSE_HA_RESPONSE_DATA_ERROR		\
			      )

/* Message queue head काष्ठाure */
जोड़ gru_mesqhead अणु
	अचिन्हित दीर्घ	val;
	काष्ठा अणु
		अचिन्हित पूर्णांक	head;
		अचिन्हित पूर्णांक	limit;
	पूर्ण;
पूर्ण;


/* Generate the low word of a GRU inकाष्ठाion */
अटल अंतरभूत अचिन्हित दीर्घ
__opdword(अचिन्हित अक्षर opcode, अचिन्हित अक्षर exopc, अचिन्हित अक्षर xtype,
       अचिन्हित अक्षर iaa0, अचिन्हित अक्षर iaa1,
       अचिन्हित दीर्घ idef2, अचिन्हित अक्षर ima)
अणु
    वापस (1 << GRU_CB_ICMD_SHFT) |
	   ((अचिन्हित दीर्घ)CBS_ACTIVE << GRU_ISTATUS_SHFT) |
	   (idef2<< GRU_IDEF2_SHFT) |
	   (iaa0 << GRU_CB_IAA0_SHFT) |
	   (iaa1 << GRU_CB_IAA1_SHFT) |
	   (ima << GRU_CB_IMA_SHFT) |
	   (xtype << GRU_CB_XTYPE_SHFT) |
	   (opcode << GRU_CB_OPC_SHFT) |
	   (exopc << GRU_CB_EXOPC_SHFT);
पूर्ण

/*
 * Architecture specअगरic पूर्णांकrinsics
 */
अटल अंतरभूत व्योम gru_flush_cache(व्योम *p)
अणु
	__flush_cache(p);
पूर्ण

/*
 * Store the lower 64 bits of the command including the "start" bit. Then
 * start the inकाष्ठाion executing.
 */
अटल अंतरभूत व्योम gru_start_inकाष्ठाion(काष्ठा gru_inकाष्ठाion *ins, अचिन्हित दीर्घ op64)
अणु
	gru_ordered_store_uदीर्घ(ins, op64);
	mb();
	gru_flush_cache(ins);
पूर्ण


/* Convert "hints" to IMA */
#घोषणा CB_IMA(h)		((h) | IMA_UNMAPPED)

/* Convert data segment cache line index पूर्णांकo TRI0 / TRI1 value */
#घोषणा GRU_DINDEX(i)		((i) * GRU_CACHE_LINE_BYTES)

/* Inline functions क्रम GRU inकाष्ठाions.
 *     Note:
 *     	- nelem and stride are in elements
 *     	- tri0/tri1 is in bytes क्रम the beginning of the data segment.
 */
अटल अंतरभूत व्योम gru_vload_phys(व्योम *cb, अचिन्हित दीर्घ gpa,
		अचिन्हित पूर्णांक tri0, पूर्णांक iaa, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (काष्ठा gru_inकाष्ठाion *)cb;

	ins->baddr0 = (दीर्घ)gpa | ((अचिन्हित दीर्घ)iaa << 62);
	ins->nelem = 1;
	ins->op1_stride = 1;
	gru_start_inकाष्ठाion(ins, __opdword(OP_VLOAD, 0, XTYPE_DW, iaa, 0,
					(अचिन्हित दीर्घ)tri0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_vstore_phys(व्योम *cb, अचिन्हित दीर्घ gpa,
		अचिन्हित पूर्णांक tri0, पूर्णांक iaa, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (काष्ठा gru_inकाष्ठाion *)cb;

	ins->baddr0 = (दीर्घ)gpa | ((अचिन्हित दीर्घ)iaa << 62);
	ins->nelem = 1;
	ins->op1_stride = 1;
	gru_start_inकाष्ठाion(ins, __opdword(OP_VSTORE, 0, XTYPE_DW, iaa, 0,
					(अचिन्हित दीर्घ)tri0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_vload(व्योम *cb, अचिन्हित दीर्घ mem_addr,
		अचिन्हित पूर्णांक tri0, अचिन्हित अक्षर xtype, अचिन्हित दीर्घ nelem,
		अचिन्हित दीर्घ stride, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (काष्ठा gru_inकाष्ठाion *)cb;

	ins->baddr0 = (दीर्घ)mem_addr;
	ins->nelem = nelem;
	ins->op1_stride = stride;
	gru_start_inकाष्ठाion(ins, __opdword(OP_VLOAD, 0, xtype, IAA_RAM, 0,
					(अचिन्हित दीर्घ)tri0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_vstore(व्योम *cb, अचिन्हित दीर्घ mem_addr,
		अचिन्हित पूर्णांक tri0, अचिन्हित अक्षर xtype, अचिन्हित दीर्घ nelem,
		अचिन्हित दीर्घ stride, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)mem_addr;
	ins->nelem = nelem;
	ins->op1_stride = stride;
	gru_start_inकाष्ठाion(ins, __opdword(OP_VSTORE, 0, xtype, IAA_RAM, 0,
					tri0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_ivload(व्योम *cb, अचिन्हित दीर्घ mem_addr,
		अचिन्हित पूर्णांक tri0, अचिन्हित पूर्णांक tri1, अचिन्हित अक्षर xtype,
		अचिन्हित दीर्घ nelem, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)mem_addr;
	ins->nelem = nelem;
	ins->tri1_bufsize = tri1;
	gru_start_inकाष्ठाion(ins, __opdword(OP_IVLOAD, 0, xtype, IAA_RAM, 0,
					tri0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_ivstore(व्योम *cb, अचिन्हित दीर्घ mem_addr,
		अचिन्हित पूर्णांक tri0, अचिन्हित पूर्णांक tri1,
		अचिन्हित अक्षर xtype, अचिन्हित दीर्घ nelem, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)mem_addr;
	ins->nelem = nelem;
	ins->tri1_bufsize = tri1;
	gru_start_inकाष्ठाion(ins, __opdword(OP_IVSTORE, 0, xtype, IAA_RAM, 0,
					tri0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_vset(व्योम *cb, अचिन्हित दीर्घ mem_addr,
		अचिन्हित दीर्घ value, अचिन्हित अक्षर xtype, अचिन्हित दीर्घ nelem,
		अचिन्हित दीर्घ stride, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)mem_addr;
	ins->op2_value_baddr1 = value;
	ins->nelem = nelem;
	ins->op1_stride = stride;
	gru_start_inकाष्ठाion(ins, __opdword(OP_VSET, 0, xtype, IAA_RAM, 0,
					 0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_ivset(व्योम *cb, अचिन्हित दीर्घ mem_addr,
		अचिन्हित पूर्णांक tri1, अचिन्हित दीर्घ value, अचिन्हित अक्षर xtype,
		अचिन्हित दीर्घ nelem, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)mem_addr;
	ins->op2_value_baddr1 = value;
	ins->nelem = nelem;
	ins->tri1_bufsize = tri1;
	gru_start_inकाष्ठाion(ins, __opdword(OP_IVSET, 0, xtype, IAA_RAM, 0,
					0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_vflush(व्योम *cb, अचिन्हित दीर्घ mem_addr,
		अचिन्हित दीर्घ nelem, अचिन्हित अक्षर xtype, अचिन्हित दीर्घ stride,
		अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)mem_addr;
	ins->op1_stride = stride;
	ins->nelem = nelem;
	gru_start_inकाष्ठाion(ins, __opdword(OP_VFLUSH, 0, xtype, IAA_RAM, 0,
					0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_nop(व्योम *cb, पूर्णांक hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	gru_start_inकाष्ठाion(ins, __opdword(OP_NOP, 0, 0, 0, 0, 0, CB_IMA(hपूर्णांकs)));
पूर्ण


अटल अंतरभूत व्योम gru_bcopy(व्योम *cb, स्थिर अचिन्हित दीर्घ src,
		अचिन्हित दीर्घ dest,
		अचिन्हित पूर्णांक tri0, अचिन्हित पूर्णांक xtype, अचिन्हित दीर्घ nelem,
		अचिन्हित पूर्णांक bufsize, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)src;
	ins->op2_value_baddr1 = (दीर्घ)dest;
	ins->nelem = nelem;
	ins->tri1_bufsize = bufsize;
	gru_start_inकाष्ठाion(ins, __opdword(OP_BCOPY, 0, xtype, IAA_RAM,
					IAA_RAM, tri0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_bstore(व्योम *cb, स्थिर अचिन्हित दीर्घ src,
		अचिन्हित दीर्घ dest, अचिन्हित पूर्णांक tri0, अचिन्हित पूर्णांक xtype,
		अचिन्हित दीर्घ nelem, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)src;
	ins->op2_value_baddr1 = (दीर्घ)dest;
	ins->nelem = nelem;
	gru_start_inकाष्ठाion(ins, __opdword(OP_BSTORE, 0, xtype, 0, IAA_RAM,
					tri0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_gamir(व्योम *cb, पूर्णांक exopc, अचिन्हित दीर्घ src,
		अचिन्हित पूर्णांक xtype, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)src;
	gru_start_inकाष्ठाion(ins, __opdword(OP_GAMIR, exopc, xtype, IAA_RAM, 0,
					0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_gamirr(व्योम *cb, पूर्णांक exopc, अचिन्हित दीर्घ src,
		अचिन्हित पूर्णांक xtype, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)src;
	gru_start_inकाष्ठाion(ins, __opdword(OP_GAMIRR, exopc, xtype, IAA_RAM, 0,
					0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_gamer(व्योम *cb, पूर्णांक exopc, अचिन्हित दीर्घ src,
		अचिन्हित पूर्णांक xtype,
		अचिन्हित दीर्घ opeअक्रम1, अचिन्हित दीर्घ opeअक्रम2,
		अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)src;
	ins->op1_stride = opeअक्रम1;
	ins->op2_value_baddr1 = opeअक्रम2;
	gru_start_inकाष्ठाion(ins, __opdword(OP_GAMER, exopc, xtype, IAA_RAM, 0,
					0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_gamerr(व्योम *cb, पूर्णांक exopc, अचिन्हित दीर्घ src,
		अचिन्हित पूर्णांक xtype, अचिन्हित दीर्घ opeअक्रम1,
		अचिन्हित दीर्घ opeअक्रम2, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)src;
	ins->op1_stride = opeअक्रम1;
	ins->op2_value_baddr1 = opeअक्रम2;
	gru_start_inकाष्ठाion(ins, __opdword(OP_GAMERR, exopc, xtype, IAA_RAM, 0,
					0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_gamxr(व्योम *cb, अचिन्हित दीर्घ src,
		अचिन्हित पूर्णांक tri0, अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)src;
	ins->nelem = 4;
	gru_start_inकाष्ठाion(ins, __opdword(OP_GAMXR, EOP_XR_CSWAP, XTYPE_DW,
				 IAA_RAM, 0, 0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत व्योम gru_mesq(व्योम *cb, अचिन्हित दीर्घ queue,
		अचिन्हित दीर्घ tri0, अचिन्हित दीर्घ nelem,
		अचिन्हित दीर्घ hपूर्णांकs)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	ins->baddr0 = (दीर्घ)queue;
	ins->nelem = nelem;
	gru_start_inकाष्ठाion(ins, __opdword(OP_MESQ, 0, XTYPE_CL, IAA_RAM, 0,
					tri0, CB_IMA(hपूर्णांकs)));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ gru_get_amo_value(व्योम *cb)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	वापस ins->avalue;
पूर्ण

अटल अंतरभूत पूर्णांक gru_get_amo_value_head(व्योम *cb)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	वापस ins->avalue & 0xffffffff;
पूर्ण

अटल अंतरभूत पूर्णांक gru_get_amo_value_limit(व्योम *cb)
अणु
	काष्ठा gru_inकाष्ठाion *ins = (व्योम *)cb;

	वापस ins->avalue >> 32;
पूर्ण

अटल अंतरभूत जोड़ gru_mesqhead  gru_mesq_head(पूर्णांक head, पूर्णांक limit)
अणु
	जोड़ gru_mesqhead mqh;

	mqh.head = head;
	mqh.limit = limit;
	वापस mqh;
पूर्ण

/*
 * Get काष्ठा control_block_extended_exc_detail क्रम CB.
 */
बाह्य पूर्णांक gru_get_cb_exception_detail(व्योम *cb,
		       काष्ठा control_block_extended_exc_detail *excdet);

#घोषणा GRU_EXC_STR_SIZE		256


/*
 * Control block definition क्रम checking status
 */
काष्ठा gru_control_block_status अणु
	अचिन्हित पूर्णांक	icmd		:1;
	अचिन्हित पूर्णांक	ima		:3;
	अचिन्हित पूर्णांक	reserved0	:4;
	अचिन्हित पूर्णांक	unused1		:24;
	अचिन्हित पूर्णांक	unused2		:24;
	अचिन्हित पूर्णांक	istatus		:2;
	अचिन्हित पूर्णांक	isubstatus	:4;
	अचिन्हित पूर्णांक	unused3		:2;
पूर्ण;

/* Get CB status */
अटल अंतरभूत पूर्णांक gru_get_cb_status(व्योम *cb)
अणु
	काष्ठा gru_control_block_status *cbs = (व्योम *)cb;

	वापस cbs->istatus;
पूर्ण

/* Get CB message queue substatus */
अटल अंतरभूत पूर्णांक gru_get_cb_message_queue_substatus(व्योम *cb)
अणु
	काष्ठा gru_control_block_status *cbs = (व्योम *)cb;

	वापस cbs->isubstatus & CBSS_MSG_QUEUE_MASK;
पूर्ण

/* Get CB substatus */
अटल अंतरभूत पूर्णांक gru_get_cb_substatus(व्योम *cb)
अणु
	काष्ठा gru_control_block_status *cbs = (व्योम *)cb;

	वापस cbs->isubstatus;
पूर्ण

/*
 * User पूर्णांकerface to check an inकाष्ठाion status. UPM and exceptions
 * are handled स्वतःmatically. However, this function करोes NOT रुको
 * क्रम an active inकाष्ठाion to complete.
 *
 */
अटल अंतरभूत पूर्णांक gru_check_status(व्योम *cb)
अणु
	काष्ठा gru_control_block_status *cbs = (व्योम *)cb;
	पूर्णांक ret;

	ret = cbs->istatus;
	अगर (ret != CBS_ACTIVE)
		ret = gru_check_status_proc(cb);
	वापस ret;
पूर्ण

/*
 * User पूर्णांकerface (via अंतरभूत function) to रुको क्रम an inकाष्ठाion
 * to complete. Completion status (IDLE or EXCEPTION is वापसed
 * to the user. Exception due to hardware errors are स्वतःmatically
 * retried beक्रमe वापसing an exception.
 *
 */
अटल अंतरभूत पूर्णांक gru_रुको(व्योम *cb)
अणु
	वापस gru_रुको_proc(cb);
पूर्ण

/*
 * Wait क्रम CB to complete. Aborts program अगर error. (Note: error करोes NOT
 * mean TLB mis - only fatal errors such as memory parity error or user
 * bugs will cause termination.
 */
अटल अंतरभूत व्योम gru_रुको_पात(व्योम *cb)
अणु
	gru_रुको_पात_proc(cb);
पूर्ण

/*
 * Get a poपूर्णांकer to the start of a gseg
 * 	p	- Any valid poपूर्णांकer within the gseg
 */
अटल अंतरभूत व्योम *gru_get_gseg_poपूर्णांकer (व्योम *p)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)p & ~(GRU_GSEG_PAGESIZE - 1));
पूर्ण

/*
 * Get a poपूर्णांकer to a control block
 * 	gseg	- GSeg address वापसed from gru_get_thपढ़ो_gru_segment()
 * 	index	- index of desired CB
 */
अटल अंतरभूत व्योम *gru_get_cb_poपूर्णांकer(व्योम *gseg,
						      पूर्णांक index)
अणु
	वापस gseg + GRU_CB_BASE + index * GRU_HANDLE_STRIDE;
पूर्ण

/*
 * Get a poपूर्णांकer to a cacheline in the data segment portion of a GSeg
 * 	gseg	- GSeg address वापसed from gru_get_thपढ़ो_gru_segment()
 * 	index	- index of desired cache line
 */
अटल अंतरभूत व्योम *gru_get_data_poपूर्णांकer(व्योम *gseg, पूर्णांक index)
अणु
	वापस gseg + GRU_DS_BASE + index * GRU_CACHE_LINE_BYTES;
पूर्ण

/*
 * Convert a vaddr पूर्णांकo the tri index within the GSEG
 * 	vaddr		- भव address of within gseg
 */
अटल अंतरभूत पूर्णांक gru_get_tri(व्योम *vaddr)
अणु
	वापस ((अचिन्हित दीर्घ)vaddr & (GRU_GSEG_PAGESIZE - 1)) - GRU_DS_BASE;
पूर्ण
#पूर्ण_अगर		/* __GRU_INSTRUCTIONS_H__ */
