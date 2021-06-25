<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Low-level parallel port routines क्रम built-in port on SGI IP32
 *
 * Author: Arnaud Giersch <arnaud.giersch@मुक्त.fr>
 *
 * Based on parport_pc.c by
 *	Phil Blundell, Tim Waugh, Jose Renau, David Campbell,
 *	Andrea Arcangeli, et al.
 *
 * Thanks to Ilya A. Volynets-Evenbakh क्रम his help.
 *
 * Copyright (C) 2005, 2006 Arnaud Giersch.
 */

/* Current status:
 *
 *	Basic SPP and PS2 modes are supported.
 *	Support क्रम parallel port IRQ is present.
 *	Hardware SPP (a.k.a. compatibility), EPP, and ECP modes are
 *	supported.
 *	SPP/ECP FIFO can be driven in PIO or DMA mode.  PIO mode can work with
 *	or without पूर्णांकerrupt support.
 *
 *	Hardware ECP mode is not fully implemented (ecp_पढ़ो_data and
 *	ecp_ग_लिखो_addr are actually missing).
 *
 * To करो:
 *
 *	Fully implement ECP mode.
 *	EPP and ECP mode need to be tested.  I currently करो not own any
 *	peripheral supporting these extended mode, and cannot test them.
 *	If DMA mode works well, decide अगर support क्रम PIO FIFO modes should be
 *	dropped.
 *	Use the ioअणुपढ़ो,ग_लिखोपूर्ण family functions when they become available in
 *	the linux-mips.org tree.  Note: the MIPS specअगरic functions पढ़ोsb()
 *	and ग_लिखोsb() are to be translated by ioपढ़ो8_rep() and ioग_लिखो8_rep()
 *	respectively.
 */

/* The built-in parallel port on the SGI 02 workstation (a.k.a. IP32) is an
 * IEEE 1284 parallel port driven by a Texas Instrument TL16PIR552PH chip[1].
 * This chip supports SPP, bidirectional, EPP and ECP modes.  It has a 16 byte
 * FIFO buffer and supports DMA transfers.
 *
 * [1] http://focus.ti.com/करोcs/prod/folders/prपूर्णांक/tl16pir552.hपंचांगl
 *
 * Theoretically, we could simply use the parport_pc module.  It is however
 * not so simple.  The parport_pc code assumes that the parallel port
 * रेजिस्टरs are port-mapped.  On the O2, they are memory-mapped.
 * Furthermore, each रेजिस्टर is replicated on 256 consecutive addresses (as
 * it is क्रम the built-in serial ports on the same chip).
 */

/*--- Some configuration defines ---------------------------------------*/

/* DEBUG_PARPORT_IP32
 *	0	disable debug
 *	1	standard level: pr_debug1 is enabled
 *	2	parport_ip32_dump_state is enabled
 *	>=3	verbose level: pr_debug is enabled
 */
#अगर !defined(DEBUG_PARPORT_IP32)
#	define DEBUG_PARPORT_IP32  0	/* 0 (disabled) क्रम production */
#पूर्ण_अगर

/*----------------------------------------------------------------------*/

/* Setup DEBUG macros.  This is करोne beक्रमe any includes, just in हाल we
 * activate pr_debug() with DEBUG_PARPORT_IP32 >= 3.
 */
#अगर DEBUG_PARPORT_IP32 == 1
#	warning DEBUG_PARPORT_IP32 == 1
#या_अगर DEBUG_PARPORT_IP32 == 2
#	warning DEBUG_PARPORT_IP32 == 2
#या_अगर DEBUG_PARPORT_IP32 >= 3
#	warning DEBUG_PARPORT_IP32 >= 3
#	अगर !defined(DEBUG)
#		define DEBUG /* enable pr_debug() in kernel.h */
#	endअगर
#पूर्ण_अगर

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/parport.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ip32/ip32_पूर्णांकs.h>
#समावेश <यंत्र/ip32/mace.h>

/*--- Global variables -------------------------------------------------*/

/* Verbose probing on by शेष क्रम debugging. */
#अगर DEBUG_PARPORT_IP32 >= 1
#	define DEFAULT_VERBOSE_PROBING	1
#अन्यथा
#	define DEFAULT_VERBOSE_PROBING	0
#पूर्ण_अगर

/* Default prefix क्रम prपूर्णांकk */
#घोषणा PPIP32 "parport_ip32: "

/*
 * These are the module parameters:
 * @features:		bit mask of features to enable/disable
 *			(all enabled by शेष)
 * @verbose_probing:	log chit-chat during initialization
 */
#घोषणा PARPORT_IP32_ENABLE_IRQ	(1U << 0)
#घोषणा PARPORT_IP32_ENABLE_DMA	(1U << 1)
#घोषणा PARPORT_IP32_ENABLE_SPP	(1U << 2)
#घोषणा PARPORT_IP32_ENABLE_EPP	(1U << 3)
#घोषणा PARPORT_IP32_ENABLE_ECP	(1U << 4)
अटल अचिन्हित पूर्णांक features =	~0U;
अटल bool verbose_probing =	DEFAULT_VERBOSE_PROBING;

/* We करो not support more than one port. */
अटल काष्ठा parport *this_port;

/* Timing स्थिरants क्रम FIFO modes.  */
#घोषणा FIFO_NFAULT_TIMEOUT	100	/* milliseconds */
#घोषणा FIFO_POLLING_INTERVAL	50	/* microseconds */

/*--- I/O रेजिस्टर definitions -----------------------------------------*/

/**
 * काष्ठा parport_ip32_regs - भव addresses of parallel port रेजिस्टरs
 * @data:	Data Register
 * @dsr:	Device Status Register
 * @dcr:	Device Control Register
 * @eppAddr:	EPP Address Register
 * @eppData0:	EPP Data Register 0
 * @eppData1:	EPP Data Register 1
 * @eppData2:	EPP Data Register 2
 * @eppData3:	EPP Data Register 3
 * @ecpAFअगरo:	ECP Address FIFO
 * @fअगरo:	General FIFO रेजिस्टर.  The same address is used क्रम:
 *		- cFअगरo, the Parallel Port DATA FIFO
 *		- ecpDFअगरo, the ECP Data FIFO
 *		- tFअगरo, the ECP Test FIFO
 * @cnfgA:	Configuration Register A
 * @cnfgB:	Configuration Register B
 * @ecr:	Extended Control Register
 */
काष्ठा parport_ip32_regs अणु
	व्योम __iomem *data;
	व्योम __iomem *dsr;
	व्योम __iomem *dcr;
	व्योम __iomem *eppAddr;
	व्योम __iomem *eppData0;
	व्योम __iomem *eppData1;
	व्योम __iomem *eppData2;
	व्योम __iomem *eppData3;
	व्योम __iomem *ecpAFअगरo;
	व्योम __iomem *fअगरo;
	व्योम __iomem *cnfgA;
	व्योम __iomem *cnfgB;
	व्योम __iomem *ecr;
पूर्ण;

/* Device Status Register */
#घोषणा DSR_nBUSY		(1U << 7)	/* PARPORT_STATUS_BUSY */
#घोषणा DSR_nACK		(1U << 6)	/* PARPORT_STATUS_ACK */
#घोषणा DSR_PERROR		(1U << 5)	/* PARPORT_STATUS_PAPEROUT */
#घोषणा DSR_SELECT		(1U << 4)	/* PARPORT_STATUS_SELECT */
#घोषणा DSR_nFAULT		(1U << 3)	/* PARPORT_STATUS_ERROR */
#घोषणा DSR_nPRINT		(1U << 2)	/* specअगरic to TL16PIR552 */
/* #घोषणा DSR_reserved		(1U << 1) */
#घोषणा DSR_TIMEOUT		(1U << 0)	/* EPP समयout */

/* Device Control Register */
/* #घोषणा DCR_reserved		(1U << 7) | (1U <<  6) */
#घोषणा DCR_सूची			(1U << 5)	/* direction */
#घोषणा DCR_IRQ			(1U << 4)	/* पूर्णांकerrupt on nAck */
#घोषणा DCR_SELECT		(1U << 3)	/* PARPORT_CONTROL_SELECT */
#घोषणा DCR_nINIT		(1U << 2)	/* PARPORT_CONTROL_INIT */
#घोषणा DCR_AUTOFD		(1U << 1)	/* PARPORT_CONTROL_AUTOFD */
#घोषणा DCR_STROBE		(1U << 0)	/* PARPORT_CONTROL_STROBE */

/* ECP Configuration Register A */
#घोषणा CNFGA_IRQ		(1U << 7)
#घोषणा CNFGA_ID_MASK		((1U << 6) | (1U << 5) | (1U << 4))
#घोषणा CNFGA_ID_SHIFT		4
#घोषणा CNFGA_ID_16		(00U << CNFGA_ID_SHIFT)
#घोषणा CNFGA_ID_8		(01U << CNFGA_ID_SHIFT)
#घोषणा CNFGA_ID_32		(02U << CNFGA_ID_SHIFT)
/* #घोषणा CNFGA_reserved	(1U << 3) */
#घोषणा CNFGA_nBYTEINTRANS	(1U << 2)
#घोषणा CNFGA_PWORDLEFT		((1U << 1) | (1U << 0))

/* ECP Configuration Register B */
#घोषणा CNFGB_COMPRESS		(1U << 7)
#घोषणा CNFGB_INTRVAL		(1U << 6)
#घोषणा CNFGB_IRQ_MASK		((1U << 5) | (1U << 4) | (1U << 3))
#घोषणा CNFGB_IRQ_SHIFT		3
#घोषणा CNFGB_DMA_MASK		((1U << 2) | (1U << 1) | (1U << 0))
#घोषणा CNFGB_DMA_SHIFT		0

/* Extended Control Register */
#घोषणा ECR_MODE_MASK		((1U << 7) | (1U << 6) | (1U << 5))
#घोषणा ECR_MODE_SHIFT		5
#घोषणा ECR_MODE_SPP		(00U << ECR_MODE_SHIFT)
#घोषणा ECR_MODE_PS2		(01U << ECR_MODE_SHIFT)
#घोषणा ECR_MODE_PPF		(02U << ECR_MODE_SHIFT)
#घोषणा ECR_MODE_ECP		(03U << ECR_MODE_SHIFT)
#घोषणा ECR_MODE_EPP		(04U << ECR_MODE_SHIFT)
/* #घोषणा ECR_MODE_reserved	(05U << ECR_MODE_SHIFT) */
#घोषणा ECR_MODE_TST		(06U << ECR_MODE_SHIFT)
#घोषणा ECR_MODE_CFG		(07U << ECR_MODE_SHIFT)
#घोषणा ECR_nERRINTR		(1U << 4)
#घोषणा ECR_DMAEN		(1U << 3)
#घोषणा ECR_SERVINTR		(1U << 2)
#घोषणा ECR_F_FULL		(1U << 1)
#घोषणा ECR_F_EMPTY		(1U << 0)

/*--- Private data -----------------------------------------------------*/

/**
 * क्रमागत parport_ip32_irq_mode - operation mode of पूर्णांकerrupt handler
 * @PARPORT_IP32_IRQ_FWD:	क्रमward पूर्णांकerrupt to the upper parport layer
 * @PARPORT_IP32_IRQ_HERE:	पूर्णांकerrupt is handled locally
 */
क्रमागत parport_ip32_irq_mode अणु PARPORT_IP32_IRQ_FWD, PARPORT_IP32_IRQ_HERE पूर्ण;

/**
 * काष्ठा parport_ip32_निजी - निजी stuff क्रम &काष्ठा parport
 * @regs:		रेजिस्टर addresses
 * @dcr_cache:		cached contents of DCR
 * @dcr_writable:	bit mask of writable DCR bits
 * @pword:		number of bytes per PWord
 * @fअगरo_depth:		number of PWords that FIFO will hold
 * @पढ़ोIntrThreshold:	minimum number of PWords we can पढ़ो
 *			अगर we get an पूर्णांकerrupt
 * @ग_लिखोIntrThreshold:	minimum number of PWords we can ग_लिखो
 *			अगर we get an पूर्णांकerrupt
 * @irq_mode:		operation mode of पूर्णांकerrupt handler क्रम this port
 * @irq_complete:	mutex used to रुको क्रम an पूर्णांकerrupt to occur
 */
काष्ठा parport_ip32_निजी अणु
	काष्ठा parport_ip32_regs	regs;
	अचिन्हित पूर्णांक			dcr_cache;
	अचिन्हित पूर्णांक			dcr_writable;
	अचिन्हित पूर्णांक			pword;
	अचिन्हित पूर्णांक			fअगरo_depth;
	अचिन्हित पूर्णांक			पढ़ोIntrThreshold;
	अचिन्हित पूर्णांक			ग_लिखोIntrThreshold;
	क्रमागत parport_ip32_irq_mode	irq_mode;
	काष्ठा completion		irq_complete;
पूर्ण;

/*--- Debug code -------------------------------------------------------*/

/*
 * pr_debug1 - prपूर्णांक debug messages
 *
 * This is like pr_debug(), but is defined क्रम %DEBUG_PARPORT_IP32 >= 1
 */
#अगर DEBUG_PARPORT_IP32 >= 1
#	define pr_debug1(...)	prपूर्णांकk(KERN_DEBUG __VA_ARGS__)
#अन्यथा /* DEBUG_PARPORT_IP32 < 1 */
#	define pr_debug1(...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * pr_trace, pr_trace1 - trace function calls
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @fmt:	prपूर्णांकk क्रमmat string
 * @...:	parameters क्रम क्रमmat string
 *
 * Macros used to trace function calls.  The given string is क्रमmatted after
 * function name.  pr_trace() uses pr_debug(), and pr_trace1() uses
 * pr_debug1().  __pr_trace() is the low-level macro and is not to be used
 * directly.
 */
#घोषणा __pr_trace(pr, p, fmt, ...)					\
	pr("%s: %s" fmt "\n",						\
	   (अणु स्थिर काष्ठा parport *__p = (p);				\
		   __p ? __p->name : "parport_ip32"; पूर्ण),		\
	   __func__ , ##__VA_ARGS__)
#घोषणा pr_trace(p, fmt, ...)	__pr_trace(pr_debug, p, fmt , ##__VA_ARGS__)
#घोषणा pr_trace1(p, fmt, ...)	__pr_trace(pr_debug1, p, fmt , ##__VA_ARGS__)

/*
 * __pr_probe, pr_probe - prपूर्णांक message अगर @verbose_probing is true
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @fmt:	prपूर्णांकk क्रमmat string
 * @...:	parameters क्रम क्रमmat string
 *
 * For new lines, use pr_probe().  Use __pr_probe() क्रम जारीd lines.
 */
#घोषणा __pr_probe(...)							\
	करो अणु अगर (verbose_probing) prपूर्णांकk(__VA_ARGS__); पूर्ण जबतक (0)
#घोषणा pr_probe(p, fmt, ...)						\
	__pr_probe(KERN_INFO PPIP32 "0x%lx: " fmt, (p)->base , ##__VA_ARGS__)

/*
 * parport_ip32_dump_state - prपूर्णांक रेजिस्टर status of parport
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @str:	string to add in message
 * @show_ecp_config:	shall we dump ECP configuration रेजिस्टरs too?
 *
 * This function is only here क्रम debugging purpose, and should be used with
 * care.  Reading the parallel port रेजिस्टरs may have undesired side effects.
 * Especially अगर @show_ecp_config is true, the parallel port is resetted.
 * This function is only defined अगर %DEBUG_PARPORT_IP32 >= 2.
 */
#अगर DEBUG_PARPORT_IP32 >= 2
अटल व्योम parport_ip32_dump_state(काष्ठा parport *p, अक्षर *str,
				    अचिन्हित पूर्णांक show_ecp_config)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	अचिन्हित पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG PPIP32 "%s: state (%s):\n", p->name, str);
	अणु
		अटल स्थिर अक्षर ecr_modes[8][4] = अणु"SPP", "PS2", "PPF",
						     "ECP", "EPP", "???",
						     "TST", "CFG"पूर्ण;
		अचिन्हित पूर्णांक ecr = पढ़ोb(priv->regs.ecr);
		prपूर्णांकk(KERN_DEBUG PPIP32 "    ecr=0x%02x", ecr);
		pr_cont(" %s",
			ecr_modes[(ecr & ECR_MODE_MASK) >> ECR_MODE_SHIFT]);
		अगर (ecr & ECR_nERRINTR)
			pr_cont(",nErrIntrEn");
		अगर (ecr & ECR_DMAEN)
			pr_cont(",dmaEn");
		अगर (ecr & ECR_SERVINTR)
			pr_cont(",serviceIntr");
		अगर (ecr & ECR_F_FULL)
			pr_cont(",f_full");
		अगर (ecr & ECR_F_EMPTY)
			pr_cont(",f_empty");
		pr_cont("\n");
	पूर्ण
	अगर (show_ecp_config) अणु
		अचिन्हित पूर्णांक oecr, cnfgA, cnfgB;
		oecr = पढ़ोb(priv->regs.ecr);
		ग_लिखोb(ECR_MODE_PS2, priv->regs.ecr);
		ग_लिखोb(ECR_MODE_CFG, priv->regs.ecr);
		cnfgA = पढ़ोb(priv->regs.cnfgA);
		cnfgB = पढ़ोb(priv->regs.cnfgB);
		ग_लिखोb(ECR_MODE_PS2, priv->regs.ecr);
		ग_लिखोb(oecr, priv->regs.ecr);
		prपूर्णांकk(KERN_DEBUG PPIP32 "    cnfgA=0x%02x", cnfgA);
		pr_cont(" ISA-%s", (cnfgA & CNFGA_IRQ) ? "Level" : "Pulses");
		चयन (cnfgA & CNFGA_ID_MASK) अणु
		हाल CNFGA_ID_8:
			pr_cont(",8 bits");
			अवरोध;
		हाल CNFGA_ID_16:
			pr_cont(",16 bits");
			अवरोध;
		हाल CNFGA_ID_32:
			pr_cont(",32 bits");
			अवरोध;
		शेष:
			pr_cont(",unknown ID");
			अवरोध;
		पूर्ण
		अगर (!(cnfgA & CNFGA_nBYTEINTRANS))
			pr_cont(",ByteInTrans");
		अगर ((cnfgA & CNFGA_ID_MASK) != CNFGA_ID_8)
			pr_cont(",%d byte%s left",
				cnfgA & CNFGA_PWORDLEFT,
				((cnfgA & CNFGA_PWORDLEFT) > 1) ? "s" : "");
		pr_cont("\n");
		prपूर्णांकk(KERN_DEBUG PPIP32 "    cnfgB=0x%02x", cnfgB);
		pr_cont(" irq=%u,dma=%u",
			(cnfgB & CNFGB_IRQ_MASK) >> CNFGB_IRQ_SHIFT,
			(cnfgB & CNFGB_DMA_MASK) >> CNFGB_DMA_SHIFT);
		pr_cont(",intrValue=%d", !!(cnfgB & CNFGB_INTRVAL));
		अगर (cnfgB & CNFGB_COMPRESS)
			pr_cont(",compress");
		pr_cont("\n");
	पूर्ण
	क्रम (i = 0; i < 2; i++) अणु
		अचिन्हित पूर्णांक dcr = i ? priv->dcr_cache : पढ़ोb(priv->regs.dcr);
		prपूर्णांकk(KERN_DEBUG PPIP32 "    dcr(%s)=0x%02x",
		       i ? "soft" : "hard", dcr);
		pr_cont(" %s", (dcr & DCR_सूची) ? "rev" : "fwd");
		अगर (dcr & DCR_IRQ)
			pr_cont(",ackIntEn");
		अगर (!(dcr & DCR_SELECT))
			pr_cont(",nSelectIn");
		अगर (dcr & DCR_nINIT)
			pr_cont(",nInit");
		अगर (!(dcr & DCR_AUTOFD))
			pr_cont(",nAutoFD");
		अगर (!(dcr & DCR_STROBE))
			pr_cont(",nStrobe");
		pr_cont("\n");
	पूर्ण
#घोषणा sep (f++ ? ',' : ' ')
	अणु
		अचिन्हित पूर्णांक f = 0;
		अचिन्हित पूर्णांक dsr = पढ़ोb(priv->regs.dsr);
		prपूर्णांकk(KERN_DEBUG PPIP32 "    dsr=0x%02x", dsr);
		अगर (!(dsr & DSR_nBUSY))
			pr_cont("%cBusy", sep);
		अगर (dsr & DSR_nACK)
			pr_cont("%cnAck", sep);
		अगर (dsr & DSR_PERROR)
			pr_cont("%cPError", sep);
		अगर (dsr & DSR_SELECT)
			pr_cont("%cSelect", sep);
		अगर (dsr & DSR_nFAULT)
			pr_cont("%cnFault", sep);
		अगर (!(dsr & DSR_nPRINT))
			pr_cont("%c(Print)", sep);
		अगर (dsr & DSR_TIMEOUT)
			pr_cont("%cTimeout", sep);
		pr_cont("\n");
	पूर्ण
#अघोषित sep
पूर्ण
#अन्यथा /* DEBUG_PARPORT_IP32 < 2 */
#घोषणा parport_ip32_dump_state(...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * CHECK_EXTRA_BITS - track and log extra bits
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @b:		byte to inspect
 * @m:		bit mask of authorized bits
 *
 * This is used to track and log extra bits that should not be there in
 * parport_ip32_ग_लिखो_control() and parport_ip32_frob_control().  It is only
 * defined अगर %DEBUG_PARPORT_IP32 >= 1.
 */
#अगर DEBUG_PARPORT_IP32 >= 1
#घोषणा CHECK_EXTRA_BITS(p, b, m)					\
	करो अणु								\
		अचिन्हित पूर्णांक __b = (b), __m = (m);			\
		अगर (__b & ~__m)						\
			pr_debug1(PPIP32 "%s: extra bits in %s(%s): "	\
				  "0x%02x/0x%02x\n",			\
				  (p)->name, __func__, #b, __b, __m);	\
	पूर्ण जबतक (0)
#अन्यथा /* DEBUG_PARPORT_IP32 < 1 */
#घोषणा CHECK_EXTRA_BITS(...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*--- IP32 parallel port DMA operations --------------------------------*/

/**
 * काष्ठा parport_ip32_dma_data - निजी data needed क्रम DMA operation
 * @dir:	DMA direction (from or to device)
 * @buf:	buffer physical address
 * @len:	buffer length
 * @next:	address of next bytes to DMA transfer
 * @left:	number of bytes reमुख्यing
 * @ctx:	next context to ग_लिखो (0: context_a; 1: context_b)
 * @irq_on:	are the DMA IRQs currently enabled?
 * @lock:	spinlock to protect access to the काष्ठाure
 */
काष्ठा parport_ip32_dma_data अणु
	क्रमागत dma_data_direction		dir;
	dma_addr_t			buf;
	dma_addr_t			next;
	माप_प्रकार				len;
	माप_प्रकार				left;
	अचिन्हित पूर्णांक			ctx;
	अचिन्हित पूर्णांक			irq_on;
	spinlock_t			lock;
पूर्ण;
अटल काष्ठा parport_ip32_dma_data parport_ip32_dma;

/**
 * parport_ip32_dma_setup_context - setup next DMA context
 * @limit:	maximum data size क्रम the context
 *
 * The alignment स्थिरraपूर्णांकs must be verअगरied in caller function, and the
 * parameter @limit must be set accordingly.
 */
अटल व्योम parport_ip32_dma_setup_context(अचिन्हित पूर्णांक limit)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&parport_ip32_dma.lock, flags);
	अगर (parport_ip32_dma.left > 0) अणु
		/* Note: ctxreg is "volatile" here only because
		 * mace->perअगर.ctrl.parport.context_a and context_b are
		 * "volatile".  */
		अस्थिर u64 __iomem *ctxreg = (parport_ip32_dma.ctx == 0) ?
			&mace->perअगर.ctrl.parport.context_a :
			&mace->perअगर.ctrl.parport.context_b;
		u64 count;
		u64 ctxval;
		अगर (parport_ip32_dma.left <= limit) अणु
			count = parport_ip32_dma.left;
			ctxval = MACEPAR_CONTEXT_LASTFLAG;
		पूर्ण अन्यथा अणु
			count = limit;
			ctxval = 0;
		पूर्ण

		pr_trace(शून्य,
			 "(%u): 0x%04x:0x%04x, %u -> %u%s",
			 limit,
			 (अचिन्हित पूर्णांक)parport_ip32_dma.buf,
			 (अचिन्हित पूर्णांक)parport_ip32_dma.next,
			 (अचिन्हित पूर्णांक)count,
			 parport_ip32_dma.ctx, ctxval ? "*" : "");

		ctxval |= parport_ip32_dma.next &
			MACEPAR_CONTEXT_BASEADDR_MASK;
		ctxval |= ((count - 1) << MACEPAR_CONTEXT_DATALEN_SHIFT) &
			MACEPAR_CONTEXT_DATALEN_MASK;
		ग_लिखोq(ctxval, ctxreg);
		parport_ip32_dma.next += count;
		parport_ip32_dma.left -= count;
		parport_ip32_dma.ctx ^= 1U;
	पूर्ण
	/* If there is nothing more to send, disable IRQs to aव्योम to
	 * face an IRQ storm which can lock the machine.  Disable them
	 * only once. */
	अगर (parport_ip32_dma.left == 0 && parport_ip32_dma.irq_on) अणु
		pr_debug(PPIP32 "IRQ off (ctx)\n");
		disable_irq_nosync(MACEISA_PAR_CTXA_IRQ);
		disable_irq_nosync(MACEISA_PAR_CTXB_IRQ);
		parport_ip32_dma.irq_on = 0;
	पूर्ण
	spin_unlock_irqrestore(&parport_ip32_dma.lock, flags);
पूर्ण

/**
 * parport_ip32_dma_पूर्णांकerrupt - DMA पूर्णांकerrupt handler
 * @irq:	पूर्णांकerrupt number
 * @dev_id:	unused
 */
अटल irqवापस_t parport_ip32_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अगर (parport_ip32_dma.left)
		pr_trace(शून्य, "(%d): ctx=%d", irq, parport_ip32_dma.ctx);
	parport_ip32_dma_setup_context(MACEPAR_CONTEXT_DATA_BOUND);
	वापस IRQ_HANDLED;
पूर्ण

#अगर DEBUG_PARPORT_IP32
अटल irqवापस_t parport_ip32_merr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	pr_trace1(शून्य, "(%d)", irq);
	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

/**
 * parport_ip32_dma_start - begins a DMA transfer
 * @p:		partport to work on
 * @dir:	DMA direction: DMA_TO_DEVICE or DMA_FROM_DEVICE
 * @addr:	poपूर्णांकer to data buffer
 * @count:	buffer size
 *
 * Calls to parport_ip32_dma_start() and parport_ip32_dma_stop() must be
 * correctly balanced.
 */
अटल पूर्णांक parport_ip32_dma_start(काष्ठा parport *p,
		क्रमागत dma_data_direction dir, व्योम *addr, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक limit;
	u64 ctrl;

	pr_trace(शून्य, "(%d, %lu)", dir, (अचिन्हित दीर्घ)count);

	/* FIXME - add support क्रम DMA_FROM_DEVICE.  In this हाल, buffer must
	 * be 64 bytes aligned. */
	BUG_ON(dir != DMA_TO_DEVICE);

	/* Reset DMA controller */
	ctrl = MACEPAR_CTLSTAT_RESET;
	ग_लिखोq(ctrl, &mace->perअगर.ctrl.parport.cntlstat);

	/* DMA IRQs should normally be enabled */
	अगर (!parport_ip32_dma.irq_on) अणु
		WARN_ON(1);
		enable_irq(MACEISA_PAR_CTXA_IRQ);
		enable_irq(MACEISA_PAR_CTXB_IRQ);
		parport_ip32_dma.irq_on = 1;
	पूर्ण

	/* Prepare DMA poपूर्णांकers */
	parport_ip32_dma.dir = dir;
	parport_ip32_dma.buf = dma_map_single(&p->bus_dev, addr, count, dir);
	parport_ip32_dma.len = count;
	parport_ip32_dma.next = parport_ip32_dma.buf;
	parport_ip32_dma.left = parport_ip32_dma.len;
	parport_ip32_dma.ctx = 0;

	/* Setup DMA direction and first two contexts */
	ctrl = (dir == DMA_TO_DEVICE) ? 0 : MACEPAR_CTLSTAT_सूचीECTION;
	ग_लिखोq(ctrl, &mace->perअगर.ctrl.parport.cntlstat);
	/* Single transfer should not cross a 4K page boundary */
	limit = MACEPAR_CONTEXT_DATA_BOUND -
		(parport_ip32_dma.next & (MACEPAR_CONTEXT_DATA_BOUND - 1));
	parport_ip32_dma_setup_context(limit);
	parport_ip32_dma_setup_context(MACEPAR_CONTEXT_DATA_BOUND);

	/* Real start of DMA transfer */
	ctrl |= MACEPAR_CTLSTAT_ENABLE;
	ग_लिखोq(ctrl, &mace->perअगर.ctrl.parport.cntlstat);

	वापस 0;
पूर्ण

/**
 * parport_ip32_dma_stop - ends a running DMA transfer
 * @p:		partport to work on
 *
 * Calls to parport_ip32_dma_start() and parport_ip32_dma_stop() must be
 * correctly balanced.
 */
अटल व्योम parport_ip32_dma_stop(काष्ठा parport *p)
अणु
	u64 ctx_a;
	u64 ctx_b;
	u64 ctrl;
	u64 diag;
	माप_प्रकार res[2];	/* अणु[0] = res_a, [1] = res_bपूर्ण */

	pr_trace(शून्य, "()");

	/* Disable IRQs */
	spin_lock_irq(&parport_ip32_dma.lock);
	अगर (parport_ip32_dma.irq_on) अणु
		pr_debug(PPIP32 "IRQ off (stop)\n");
		disable_irq_nosync(MACEISA_PAR_CTXA_IRQ);
		disable_irq_nosync(MACEISA_PAR_CTXB_IRQ);
		parport_ip32_dma.irq_on = 0;
	पूर्ण
	spin_unlock_irq(&parport_ip32_dma.lock);
	/* Force IRQ synchronization, even अगर the IRQs were disabled
	 * अन्यथाwhere. */
	synchronize_irq(MACEISA_PAR_CTXA_IRQ);
	synchronize_irq(MACEISA_PAR_CTXB_IRQ);

	/* Stop DMA transfer */
	ctrl = पढ़ोq(&mace->perअगर.ctrl.parport.cntlstat);
	ctrl &= ~MACEPAR_CTLSTAT_ENABLE;
	ग_लिखोq(ctrl, &mace->perअगर.ctrl.parport.cntlstat);

	/* Adjust residue (parport_ip32_dma.left) */
	ctx_a = पढ़ोq(&mace->perअगर.ctrl.parport.context_a);
	ctx_b = पढ़ोq(&mace->perअगर.ctrl.parport.context_b);
	ctrl = पढ़ोq(&mace->perअगर.ctrl.parport.cntlstat);
	diag = पढ़ोq(&mace->perअगर.ctrl.parport.diagnostic);
	res[0] = (ctrl & MACEPAR_CTLSTAT_CTXA_VALID) ?
		1 + ((ctx_a & MACEPAR_CONTEXT_DATALEN_MASK) >>
		     MACEPAR_CONTEXT_DATALEN_SHIFT) :
		0;
	res[1] = (ctrl & MACEPAR_CTLSTAT_CTXB_VALID) ?
		1 + ((ctx_b & MACEPAR_CONTEXT_DATALEN_MASK) >>
		     MACEPAR_CONTEXT_DATALEN_SHIFT) :
		0;
	अगर (diag & MACEPAR_DIAG_DMACTIVE)
		res[(diag & MACEPAR_DIAG_CTXINUSE) != 0] =
			1 + ((diag & MACEPAR_DIAG_CTRMASK) >>
			     MACEPAR_DIAG_CTRSHIFT);
	parport_ip32_dma.left += res[0] + res[1];

	/* Reset DMA controller, and re-enable IRQs */
	ctrl = MACEPAR_CTLSTAT_RESET;
	ग_लिखोq(ctrl, &mace->perअगर.ctrl.parport.cntlstat);
	pr_debug(PPIP32 "IRQ on (stop)\n");
	enable_irq(MACEISA_PAR_CTXA_IRQ);
	enable_irq(MACEISA_PAR_CTXB_IRQ);
	parport_ip32_dma.irq_on = 1;

	dma_unmap_single(&p->bus_dev, parport_ip32_dma.buf,
			 parport_ip32_dma.len, parport_ip32_dma.dir);
पूर्ण

/**
 * parport_ip32_dma_get_residue - get residue from last DMA transfer
 *
 * Returns the number of bytes reमुख्यing from last DMA transfer.
 */
अटल अंतरभूत माप_प्रकार parport_ip32_dma_get_residue(व्योम)
अणु
	वापस parport_ip32_dma.left;
पूर्ण

/**
 * parport_ip32_dma_रेजिस्टर - initialize DMA engine
 *
 * Returns zero क्रम success.
 */
अटल पूर्णांक parport_ip32_dma_रेजिस्टर(व्योम)
अणु
	पूर्णांक err;

	spin_lock_init(&parport_ip32_dma.lock);
	parport_ip32_dma.irq_on = 1;

	/* Reset DMA controller */
	ग_लिखोq(MACEPAR_CTLSTAT_RESET, &mace->perअगर.ctrl.parport.cntlstat);

	/* Request IRQs */
	err = request_irq(MACEISA_PAR_CTXA_IRQ, parport_ip32_dma_पूर्णांकerrupt,
			  0, "parport_ip32", शून्य);
	अगर (err)
		जाओ fail_a;
	err = request_irq(MACEISA_PAR_CTXB_IRQ, parport_ip32_dma_पूर्णांकerrupt,
			  0, "parport_ip32", शून्य);
	अगर (err)
		जाओ fail_b;
#अगर DEBUG_PARPORT_IP32
	/* FIXME - what is this IRQ क्रम? */
	err = request_irq(MACEISA_PAR_MERR_IRQ, parport_ip32_merr_पूर्णांकerrupt,
			  0, "parport_ip32", शून्य);
	अगर (err)
		जाओ fail_merr;
#पूर्ण_अगर
	वापस 0;

#अगर DEBUG_PARPORT_IP32
fail_merr:
	मुक्त_irq(MACEISA_PAR_CTXB_IRQ, शून्य);
#पूर्ण_अगर
fail_b:
	मुक्त_irq(MACEISA_PAR_CTXA_IRQ, शून्य);
fail_a:
	वापस err;
पूर्ण

/**
 * parport_ip32_dma_unरेजिस्टर - release and मुक्त resources क्रम DMA engine
 */
अटल व्योम parport_ip32_dma_unरेजिस्टर(व्योम)
अणु
#अगर DEBUG_PARPORT_IP32
	मुक्त_irq(MACEISA_PAR_MERR_IRQ, शून्य);
#पूर्ण_अगर
	मुक्त_irq(MACEISA_PAR_CTXB_IRQ, शून्य);
	मुक्त_irq(MACEISA_PAR_CTXA_IRQ, शून्य);
पूर्ण

/*--- Interrupt handlers and associates --------------------------------*/

/**
 * parport_ip32_wakeup - wakes up code रुकोing क्रम an पूर्णांकerrupt
 * @p:		poपूर्णांकer to &काष्ठा parport
 */
अटल अंतरभूत व्योम parport_ip32_wakeup(काष्ठा parport *p)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	complete(&priv->irq_complete);
पूर्ण

/**
 * parport_ip32_पूर्णांकerrupt - पूर्णांकerrupt handler
 * @irq:	पूर्णांकerrupt number
 * @dev_id:	poपूर्णांकer to &काष्ठा parport
 *
 * Caught पूर्णांकerrupts are क्रमwarded to the upper parport layer अगर IRQ_mode is
 * %PARPORT_IP32_IRQ_FWD.
 */
अटल irqवापस_t parport_ip32_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा parport * स्थिर p = dev_id;
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	क्रमागत parport_ip32_irq_mode irq_mode = priv->irq_mode;

	चयन (irq_mode) अणु
	हाल PARPORT_IP32_IRQ_FWD:
		वापस parport_irq_handler(irq, dev_id);

	हाल PARPORT_IP32_IRQ_HERE:
		parport_ip32_wakeup(p);
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*--- Some utility function to manipulate ECR रेजिस्टर -----------------*/

/**
 * parport_ip32_पढ़ो_econtrol - पढ़ो contents of the ECR रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 */
अटल अंतरभूत अचिन्हित पूर्णांक parport_ip32_पढ़ो_econtrol(काष्ठा parport *p)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	वापस पढ़ोb(priv->regs.ecr);
पूर्ण

/**
 * parport_ip32_ग_लिखो_econtrol - ग_लिखो new contents to the ECR रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @c:		new value to ग_लिखो
 */
अटल अंतरभूत व्योम parport_ip32_ग_लिखो_econtrol(काष्ठा parport *p,
					       अचिन्हित पूर्णांक c)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	ग_लिखोb(c, priv->regs.ecr);
पूर्ण

/**
 * parport_ip32_frob_econtrol - change bits from the ECR रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @mask:	bit mask of bits to change
 * @val:	new value क्रम changed bits
 *
 * Read from the ECR, mask out the bits in @mask, exclusive-or with the bits
 * in @val, and ग_लिखो the result to the ECR.
 */
अटल अंतरभूत व्योम parport_ip32_frob_econtrol(काष्ठा parport *p,
					      अचिन्हित पूर्णांक mask,
					      अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक c;
	c = (parport_ip32_पढ़ो_econtrol(p) & ~mask) ^ val;
	parport_ip32_ग_लिखो_econtrol(p, c);
पूर्ण

/**
 * parport_ip32_set_mode - change mode of ECP port
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @mode:	new mode to ग_लिखो in ECR
 *
 * ECR is reset in a sane state (पूर्णांकerrupts and DMA disabled), and placed in
 * mode @mode.  Go through PS2 mode अगर needed.
 */
अटल व्योम parport_ip32_set_mode(काष्ठा parport *p, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक omode;

	mode &= ECR_MODE_MASK;
	omode = parport_ip32_पढ़ो_econtrol(p) & ECR_MODE_MASK;

	अगर (!(mode == ECR_MODE_SPP || mode == ECR_MODE_PS2
	      || omode == ECR_MODE_SPP || omode == ECR_MODE_PS2)) अणु
		/* We have to go through PS2 mode */
		अचिन्हित पूर्णांक ecr = ECR_MODE_PS2 | ECR_nERRINTR | ECR_SERVINTR;
		parport_ip32_ग_लिखो_econtrol(p, ecr);
	पूर्ण
	parport_ip32_ग_लिखो_econtrol(p, mode | ECR_nERRINTR | ECR_SERVINTR);
पूर्ण

/*--- Basic functions needed क्रम parport -------------------------------*/

/**
 * parport_ip32_पढ़ो_data - वापस current contents of the DATA रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 */
अटल अंतरभूत अचिन्हित अक्षर parport_ip32_पढ़ो_data(काष्ठा parport *p)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	वापस पढ़ोb(priv->regs.data);
पूर्ण

/**
 * parport_ip32_ग_लिखो_data - set new contents क्रम the DATA रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @d:		new value to ग_लिखो
 */
अटल अंतरभूत व्योम parport_ip32_ग_लिखो_data(काष्ठा parport *p, अचिन्हित अक्षर d)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	ग_लिखोb(d, priv->regs.data);
पूर्ण

/**
 * parport_ip32_पढ़ो_status - वापस current contents of the DSR रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 */
अटल अंतरभूत अचिन्हित अक्षर parport_ip32_पढ़ो_status(काष्ठा parport *p)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	वापस पढ़ोb(priv->regs.dsr);
पूर्ण

/**
 * __parport_ip32_पढ़ो_control - वापस cached contents of the DCR रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 */
अटल अंतरभूत अचिन्हित पूर्णांक __parport_ip32_पढ़ो_control(काष्ठा parport *p)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	वापस priv->dcr_cache; /* use soft copy */
पूर्ण

/**
 * __parport_ip32_ग_लिखो_control - set new contents क्रम the DCR रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @c:		new value to ग_लिखो
 */
अटल अंतरभूत व्योम __parport_ip32_ग_लिखो_control(काष्ठा parport *p,
						अचिन्हित पूर्णांक c)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	CHECK_EXTRA_BITS(p, c, priv->dcr_writable);
	c &= priv->dcr_writable; /* only writable bits */
	ग_लिखोb(c, priv->regs.dcr);
	priv->dcr_cache = c;		/* update soft copy */
पूर्ण

/**
 * __parport_ip32_frob_control - change bits from the DCR रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @mask:	bit mask of bits to change
 * @val:	new value क्रम changed bits
 *
 * This is equivalent to पढ़ो from the DCR, mask out the bits in @mask,
 * exclusive-or with the bits in @val, and ग_लिखो the result to the DCR.
 * Actually, the cached contents of the DCR is used.
 */
अटल अंतरभूत व्योम __parport_ip32_frob_control(काष्ठा parport *p,
					       अचिन्हित पूर्णांक mask,
					       अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक c;
	c = (__parport_ip32_पढ़ो_control(p) & ~mask) ^ val;
	__parport_ip32_ग_लिखो_control(p, c);
पूर्ण

/**
 * parport_ip32_पढ़ो_control - वापस cached contents of the DCR रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 *
 * The वापस value is masked so as to only वापस the value of %DCR_STROBE,
 * %DCR_AUTOFD, %DCR_nINIT, and %DCR_SELECT.
 */
अटल अंतरभूत अचिन्हित अक्षर parport_ip32_पढ़ो_control(काष्ठा parport *p)
अणु
	स्थिर अचिन्हित पूर्णांक rm =
		DCR_STROBE | DCR_AUTOFD | DCR_nINIT | DCR_SELECT;
	वापस __parport_ip32_पढ़ो_control(p) & rm;
पूर्ण

/**
 * parport_ip32_ग_लिखो_control - set new contents क्रम the DCR रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @c:		new value to ग_लिखो
 *
 * The value is masked so as to only change the value of %DCR_STROBE,
 * %DCR_AUTOFD, %DCR_nINIT, and %DCR_SELECT.
 */
अटल अंतरभूत व्योम parport_ip32_ग_लिखो_control(काष्ठा parport *p,
					      अचिन्हित अक्षर c)
अणु
	स्थिर अचिन्हित पूर्णांक wm =
		DCR_STROBE | DCR_AUTOFD | DCR_nINIT | DCR_SELECT;
	CHECK_EXTRA_BITS(p, c, wm);
	__parport_ip32_frob_control(p, wm, c & wm);
पूर्ण

/**
 * parport_ip32_frob_control - change bits from the DCR रेजिस्टर
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @mask:	bit mask of bits to change
 * @val:	new value क्रम changed bits
 *
 * This dअगरfers from __parport_ip32_frob_control() in that it only allows to
 * change the value of %DCR_STROBE, %DCR_AUTOFD, %DCR_nINIT, and %DCR_SELECT.
 */
अटल अंतरभूत अचिन्हित अक्षर parport_ip32_frob_control(काष्ठा parport *p,
						      अचिन्हित अक्षर mask,
						      अचिन्हित अक्षर val)
अणु
	स्थिर अचिन्हित पूर्णांक wm =
		DCR_STROBE | DCR_AUTOFD | DCR_nINIT | DCR_SELECT;
	CHECK_EXTRA_BITS(p, mask, wm);
	CHECK_EXTRA_BITS(p, val, wm);
	__parport_ip32_frob_control(p, mask & wm, val & wm);
	वापस parport_ip32_पढ़ो_control(p);
पूर्ण

/**
 * parport_ip32_disable_irq - disable पूर्णांकerrupts on the rising edge of nACK
 * @p:		poपूर्णांकer to &काष्ठा parport
 */
अटल अंतरभूत व्योम parport_ip32_disable_irq(काष्ठा parport *p)
अणु
	__parport_ip32_frob_control(p, DCR_IRQ, 0);
पूर्ण

/**
 * parport_ip32_enable_irq - enable पूर्णांकerrupts on the rising edge of nACK
 * @p:		poपूर्णांकer to &काष्ठा parport
 */
अटल अंतरभूत व्योम parport_ip32_enable_irq(काष्ठा parport *p)
अणु
	__parport_ip32_frob_control(p, DCR_IRQ, DCR_IRQ);
पूर्ण

/**
 * parport_ip32_data_क्रमward - enable host-to-peripheral communications
 * @p:		poपूर्णांकer to &काष्ठा parport
 *
 * Enable the data line drivers, क्रम 8-bit host-to-peripheral communications.
 */
अटल अंतरभूत व्योम parport_ip32_data_क्रमward(काष्ठा parport *p)
अणु
	__parport_ip32_frob_control(p, DCR_सूची, 0);
पूर्ण

/**
 * parport_ip32_data_reverse - enable peripheral-to-host communications
 * @p:		poपूर्णांकer to &काष्ठा parport
 *
 * Place the data bus in a high impedance state, अगर @p->modes has the
 * PARPORT_MODE_TRISTATE bit set.
 */
अटल अंतरभूत व्योम parport_ip32_data_reverse(काष्ठा parport *p)
अणु
	__parport_ip32_frob_control(p, DCR_सूची, DCR_सूची);
पूर्ण

/**
 * parport_ip32_init_state - क्रम core parport code
 * @dev:	poपूर्णांकer to &काष्ठा pardevice
 * @s:		poपूर्णांकer to &काष्ठा parport_state to initialize
 */
अटल व्योम parport_ip32_init_state(काष्ठा pardevice *dev,
				    काष्ठा parport_state *s)
अणु
	s->u.ip32.dcr = DCR_SELECT | DCR_nINIT;
	s->u.ip32.ecr = ECR_MODE_PS2 | ECR_nERRINTR | ECR_SERVINTR;
पूर्ण

/**
 * parport_ip32_save_state - क्रम core parport code
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @s:		poपूर्णांकer to &काष्ठा parport_state to save state to
 */
अटल व्योम parport_ip32_save_state(काष्ठा parport *p,
				    काष्ठा parport_state *s)
अणु
	s->u.ip32.dcr = __parport_ip32_पढ़ो_control(p);
	s->u.ip32.ecr = parport_ip32_पढ़ो_econtrol(p);
पूर्ण

/**
 * parport_ip32_restore_state - क्रम core parport code
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @s:		poपूर्णांकer to &काष्ठा parport_state to restore state from
 */
अटल व्योम parport_ip32_restore_state(काष्ठा parport *p,
				       काष्ठा parport_state *s)
अणु
	parport_ip32_set_mode(p, s->u.ip32.ecr & ECR_MODE_MASK);
	parport_ip32_ग_लिखो_econtrol(p, s->u.ip32.ecr);
	__parport_ip32_ग_लिखो_control(p, s->u.ip32.dcr);
पूर्ण

/*--- EPP mode functions -----------------------------------------------*/

/**
 * parport_ip32_clear_epp_समयout - clear Timeout bit in EPP mode
 * @p:		poपूर्णांकer to &काष्ठा parport
 *
 * Returns 1 अगर the Timeout bit is clear, and 0 otherwise.
 */
अटल अचिन्हित पूर्णांक parport_ip32_clear_epp_समयout(काष्ठा parport *p)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	अचिन्हित पूर्णांक cleared;

	अगर (!(parport_ip32_पढ़ो_status(p) & DSR_TIMEOUT))
		cleared = 1;
	अन्यथा अणु
		अचिन्हित पूर्णांक r;
		/* To clear समयout some chips require द्विगुन पढ़ो */
		parport_ip32_पढ़ो_status(p);
		r = parport_ip32_पढ़ो_status(p);
		/* Some reset by writing 1 */
		ग_लिखोb(r | DSR_TIMEOUT, priv->regs.dsr);
		/* Others by writing 0 */
		ग_लिखोb(r & ~DSR_TIMEOUT, priv->regs.dsr);

		r = parport_ip32_पढ़ो_status(p);
		cleared = !(r & DSR_TIMEOUT);
	पूर्ण

	pr_trace(p, "(): %s", cleared ? "cleared" : "failed");
	वापस cleared;
पूर्ण

/**
 * parport_ip32_epp_पढ़ो - generic EPP पढ़ो function
 * @eppreg:	I/O रेजिस्टर to पढ़ो from
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer to store पढ़ो data
 * @len:	length of buffer @buf
 * @flags:	may be PARPORT_EPP_FAST
 */
अटल माप_प्रकार parport_ip32_epp_पढ़ो(व्योम __iomem *eppreg,
				    काष्ठा parport *p, व्योम *buf,
				    माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	माप_प्रकार got;
	parport_ip32_set_mode(p, ECR_MODE_EPP);
	parport_ip32_data_reverse(p);
	parport_ip32_ग_लिखो_control(p, DCR_nINIT);
	अगर ((flags & PARPORT_EPP_FAST) && (len > 1)) अणु
		पढ़ोsb(eppreg, buf, len);
		अगर (पढ़ोb(priv->regs.dsr) & DSR_TIMEOUT) अणु
			parport_ip32_clear_epp_समयout(p);
			वापस -EIO;
		पूर्ण
		got = len;
	पूर्ण अन्यथा अणु
		u8 *bufp = buf;
		क्रम (got = 0; got < len; got++) अणु
			*bufp++ = पढ़ोb(eppreg);
			अगर (पढ़ोb(priv->regs.dsr) & DSR_TIMEOUT) अणु
				parport_ip32_clear_epp_समयout(p);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	parport_ip32_data_क्रमward(p);
	parport_ip32_set_mode(p, ECR_MODE_PS2);
	वापस got;
पूर्ण

/**
 * parport_ip32_epp_ग_लिखो - generic EPP ग_लिखो function
 * @eppreg:	I/O रेजिस्टर to ग_लिखो to
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer of data to ग_लिखो
 * @len:	length of buffer @buf
 * @flags:	may be PARPORT_EPP_FAST
 */
अटल माप_प्रकार parport_ip32_epp_ग_लिखो(व्योम __iomem *eppreg,
				     काष्ठा parport *p, स्थिर व्योम *buf,
				     माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	माप_प्रकार written;
	parport_ip32_set_mode(p, ECR_MODE_EPP);
	parport_ip32_data_क्रमward(p);
	parport_ip32_ग_लिखो_control(p, DCR_nINIT);
	अगर ((flags & PARPORT_EPP_FAST) && (len > 1)) अणु
		ग_लिखोsb(eppreg, buf, len);
		अगर (पढ़ोb(priv->regs.dsr) & DSR_TIMEOUT) अणु
			parport_ip32_clear_epp_समयout(p);
			वापस -EIO;
		पूर्ण
		written = len;
	पूर्ण अन्यथा अणु
		स्थिर u8 *bufp = buf;
		क्रम (written = 0; written < len; written++) अणु
			ग_लिखोb(*bufp++, eppreg);
			अगर (पढ़ोb(priv->regs.dsr) & DSR_TIMEOUT) अणु
				parport_ip32_clear_epp_समयout(p);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	parport_ip32_set_mode(p, ECR_MODE_PS2);
	वापस written;
पूर्ण

/**
 * parport_ip32_epp_पढ़ो_data - पढ़ो a block of data in EPP mode
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer to store पढ़ो data
 * @len:	length of buffer @buf
 * @flags:	may be PARPORT_EPP_FAST
 */
अटल माप_प्रकार parport_ip32_epp_पढ़ो_data(काष्ठा parport *p, व्योम *buf,
					 माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	वापस parport_ip32_epp_पढ़ो(priv->regs.eppData0, p, buf, len, flags);
पूर्ण

/**
 * parport_ip32_epp_ग_लिखो_data - ग_लिखो a block of data in EPP mode
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer of data to ग_लिखो
 * @len:	length of buffer @buf
 * @flags:	may be PARPORT_EPP_FAST
 */
अटल माप_प्रकार parport_ip32_epp_ग_लिखो_data(काष्ठा parport *p, स्थिर व्योम *buf,
					  माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	वापस parport_ip32_epp_ग_लिखो(priv->regs.eppData0, p, buf, len, flags);
पूर्ण

/**
 * parport_ip32_epp_पढ़ो_addr - पढ़ो a block of addresses in EPP mode
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer to store पढ़ो data
 * @len:	length of buffer @buf
 * @flags:	may be PARPORT_EPP_FAST
 */
अटल माप_प्रकार parport_ip32_epp_पढ़ो_addr(काष्ठा parport *p, व्योम *buf,
					 माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	वापस parport_ip32_epp_पढ़ो(priv->regs.eppAddr, p, buf, len, flags);
पूर्ण

/**
 * parport_ip32_epp_ग_लिखो_addr - ग_लिखो a block of addresses in EPP mode
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer of data to ग_लिखो
 * @len:	length of buffer @buf
 * @flags:	may be PARPORT_EPP_FAST
 */
अटल माप_प्रकार parport_ip32_epp_ग_लिखो_addr(काष्ठा parport *p, स्थिर व्योम *buf,
					  माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	वापस parport_ip32_epp_ग_लिखो(priv->regs.eppAddr, p, buf, len, flags);
पूर्ण

/*--- ECP mode functions (FIFO) ----------------------------------------*/

/**
 * parport_ip32_fअगरo_रुको_अवरोध - check अगर the रुकोing function should वापस
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @expire:	समयout expiring date, in jअगरfies
 *
 * parport_ip32_fअगरo_रुको_अवरोध() checks अगर the रुकोing function should वापस
 * immediately or not.  The अवरोध conditions are:
 *	- expired समयout;
 *	- a pending संकेत;
 *	- nFault निश्चितed low.
 * This function also calls cond_resched().
 */
अटल अचिन्हित पूर्णांक parport_ip32_fअगरo_रुको_अवरोध(काष्ठा parport *p,
						 अचिन्हित दीर्घ expire)
अणु
	cond_resched();
	अगर (समय_after(jअगरfies, expire)) अणु
		pr_debug1(PPIP32 "%s: FIFO write timed out\n", p->name);
		वापस 1;
	पूर्ण
	अगर (संकेत_pending(current)) अणु
		pr_debug1(PPIP32 "%s: Signal pending\n", p->name);
		वापस 1;
	पूर्ण
	अगर (!(parport_ip32_पढ़ो_status(p) & DSR_nFAULT)) अणु
		pr_debug1(PPIP32 "%s: nFault asserted low\n", p->name);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * parport_ip32_fwp_रुको_polling - रुको क्रम FIFO to empty (polling)
 * @p:		poपूर्णांकer to &काष्ठा parport
 *
 * Returns the number of bytes that can safely be written in the FIFO.  A
 * वापस value of zero means that the calling function should terminate as
 * fast as possible.
 */
अटल अचिन्हित पूर्णांक parport_ip32_fwp_रुको_polling(काष्ठा parport *p)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	काष्ठा parport * स्थिर physport = p->physport;
	अचिन्हित दीर्घ expire;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक ecr;

	expire = jअगरfies + physport->cad->समयout;
	count = 0;
	जबतक (1) अणु
		अगर (parport_ip32_fअगरo_रुको_अवरोध(p, expire))
			अवरोध;

		/* Check FIFO state.  We करो nothing when the FIFO is nor full,
		 * nor empty.  It appears that the FIFO full bit is not always
		 * reliable, the FIFO state is someबार wrongly reported, and
		 * the chip माला_लो confused अगर we give it another byte. */
		ecr = parport_ip32_पढ़ो_econtrol(p);
		अगर (ecr & ECR_F_EMPTY) अणु
			/* FIFO is empty, fill it up */
			count = priv->fअगरo_depth;
			अवरोध;
		पूर्ण

		/* Wait a moment... */
		udelay(FIFO_POLLING_INTERVAL);
	पूर्ण /* जबतक (1) */

	वापस count;
पूर्ण

/**
 * parport_ip32_fwp_रुको_पूर्णांकerrupt - रुको क्रम FIFO to empty (पूर्णांकerrupt-driven)
 * @p:		poपूर्णांकer to &काष्ठा parport
 *
 * Returns the number of bytes that can safely be written in the FIFO.  A
 * वापस value of zero means that the calling function should terminate as
 * fast as possible.
 */
अटल अचिन्हित पूर्णांक parport_ip32_fwp_रुको_पूर्णांकerrupt(काष्ठा parport *p)
अणु
	अटल अचिन्हित पूर्णांक lost_पूर्णांकerrupt = 0;
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	काष्ठा parport * स्थिर physport = p->physport;
	अचिन्हित दीर्घ nfault_समयout;
	अचिन्हित दीर्घ expire;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक ecr;

	nfault_समयout = min((अचिन्हित दीर्घ)physport->cad->समयout,
			     msecs_to_jअगरfies(FIFO_NFAULT_TIMEOUT));
	expire = jअगरfies + physport->cad->समयout;
	count = 0;
	जबतक (1) अणु
		अगर (parport_ip32_fअगरo_रुको_अवरोध(p, expire))
			अवरोध;

		/* Initialize mutex used to take पूर्णांकerrupts पूर्णांकo account */
		reinit_completion(&priv->irq_complete);

		/* Enable serviceIntr */
		parport_ip32_frob_econtrol(p, ECR_SERVINTR, 0);

		/* Enabling serviceIntr जबतक the FIFO is empty करोes not
		 * always generate an पूर्णांकerrupt, so check क्रम emptiness
		 * now. */
		ecr = parport_ip32_पढ़ो_econtrol(p);
		अगर (!(ecr & ECR_F_EMPTY)) अणु
			/* FIFO is not empty: रुको क्रम an पूर्णांकerrupt or a
			 * समयout to occur */
			रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&priv->irq_complete, nfault_समयout);
			ecr = parport_ip32_पढ़ो_econtrol(p);
			अगर ((ecr & ECR_F_EMPTY) && !(ecr & ECR_SERVINTR)
			    && !lost_पूर्णांकerrupt) अणु
				pr_warn(PPIP32 "%s: lost interrupt in %s\n",
					p->name, __func__);
				lost_पूर्णांकerrupt = 1;
			पूर्ण
		पूर्ण

		/* Disable serviceIntr */
		parport_ip32_frob_econtrol(p, ECR_SERVINTR, ECR_SERVINTR);

		/* Check FIFO state */
		अगर (ecr & ECR_F_EMPTY) अणु
			/* FIFO is empty, fill it up */
			count = priv->fअगरo_depth;
			अवरोध;
		पूर्ण अन्यथा अगर (ecr & ECR_SERVINTR) अणु
			/* FIFO is not empty, but we know that can safely push
			 * ग_लिखोIntrThreshold bytes पूर्णांकo it */
			count = priv->ग_लिखोIntrThreshold;
			अवरोध;
		पूर्ण
		/* FIFO is not empty, and we did not get any पूर्णांकerrupt.
		 * Either it's समय to check क्रम nFault, or a संकेत is
		 * pending.  This is verअगरied in
		 * parport_ip32_fअगरo_रुको_अवरोध(), so we जारी the loop. */
	पूर्ण /* जबतक (1) */

	वापस count;
पूर्ण

/**
 * parport_ip32_fअगरo_ग_लिखो_block_pio - ग_लिखो a block of data (PIO mode)
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer of data to ग_लिखो
 * @len:	length of buffer @buf
 *
 * Uses PIO to ग_लिखो the contents of the buffer @buf पूर्णांकo the parallel port
 * FIFO.  Returns the number of bytes that were actually written.  It can work
 * with or without the help of पूर्णांकerrupts.  The parallel port must be
 * correctly initialized beक्रमe calling parport_ip32_fअगरo_ग_लिखो_block_pio().
 */
अटल माप_प्रकार parport_ip32_fअगरo_ग_लिखो_block_pio(काष्ठा parport *p,
						स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	स्थिर u8 *bufp = buf;
	माप_प्रकार left = len;

	priv->irq_mode = PARPORT_IP32_IRQ_HERE;

	जबतक (left > 0) अणु
		अचिन्हित पूर्णांक count;

		count = (p->irq == PARPORT_IRQ_NONE) ?
			parport_ip32_fwp_रुको_polling(p) :
			parport_ip32_fwp_रुको_पूर्णांकerrupt(p);
		अगर (count == 0)
			अवरोध;	/* Transmission should be stopped */
		अगर (count > left)
			count = left;
		अगर (count == 1) अणु
			ग_लिखोb(*bufp, priv->regs.fअगरo);
			bufp++, left--;
		पूर्ण अन्यथा अणु
			ग_लिखोsb(priv->regs.fअगरo, bufp, count);
			bufp += count, left -= count;
		पूर्ण
	पूर्ण

	priv->irq_mode = PARPORT_IP32_IRQ_FWD;

	वापस len - left;
पूर्ण

/**
 * parport_ip32_fअगरo_ग_लिखो_block_dma - ग_लिखो a block of data (DMA mode)
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer of data to ग_लिखो
 * @len:	length of buffer @buf
 *
 * Uses DMA to ग_लिखो the contents of the buffer @buf पूर्णांकo the parallel port
 * FIFO.  Returns the number of bytes that were actually written.  The
 * parallel port must be correctly initialized beक्रमe calling
 * parport_ip32_fअगरo_ग_लिखो_block_dma().
 */
अटल माप_प्रकार parport_ip32_fअगरo_ग_लिखो_block_dma(काष्ठा parport *p,
						स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	काष्ठा parport * स्थिर physport = p->physport;
	अचिन्हित दीर्घ nfault_समयout;
	अचिन्हित दीर्घ expire;
	माप_प्रकार written;
	अचिन्हित पूर्णांक ecr;

	priv->irq_mode = PARPORT_IP32_IRQ_HERE;

	parport_ip32_dma_start(p, DMA_TO_DEVICE, (व्योम *)buf, len);
	reinit_completion(&priv->irq_complete);
	parport_ip32_frob_econtrol(p, ECR_DMAEN | ECR_SERVINTR, ECR_DMAEN);

	nfault_समयout = min((अचिन्हित दीर्घ)physport->cad->समयout,
			     msecs_to_jअगरfies(FIFO_NFAULT_TIMEOUT));
	expire = jअगरfies + physport->cad->समयout;
	जबतक (1) अणु
		अगर (parport_ip32_fअगरo_रुको_अवरोध(p, expire))
			अवरोध;
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(&priv->irq_complete,
							  nfault_समयout);
		ecr = parport_ip32_पढ़ो_econtrol(p);
		अगर (ecr & ECR_SERVINTR)
			अवरोध;	/* DMA transfer just finished */
	पूर्ण
	parport_ip32_dma_stop(p);
	written = len - parport_ip32_dma_get_residue();

	priv->irq_mode = PARPORT_IP32_IRQ_FWD;

	वापस written;
पूर्ण

/**
 * parport_ip32_fअगरo_ग_लिखो_block - ग_लिखो a block of data
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer of data to ग_लिखो
 * @len:	length of buffer @buf
 *
 * Uses PIO or DMA to ग_लिखो the contents of the buffer @buf पूर्णांकo the parallel
 * p FIFO.  Returns the number of bytes that were actually written.
 */
अटल माप_प्रकार parport_ip32_fअगरo_ग_लिखो_block(काष्ठा parport *p,
					    स्थिर व्योम *buf, माप_प्रकार len)
अणु
	माप_प्रकार written = 0;
	अगर (len)
		/* FIXME - Maybe some threshold value should be set क्रम @len
		 * under which we revert to PIO mode? */
		written = (p->modes & PARPORT_MODE_DMA) ?
			parport_ip32_fअगरo_ग_लिखो_block_dma(p, buf, len) :
			parport_ip32_fअगरo_ग_लिखो_block_pio(p, buf, len);
	वापस written;
पूर्ण

/**
 * parport_ip32_drain_fअगरo - रुको क्रम FIFO to empty
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @समयout:	समयout, in jअगरfies
 *
 * This function रुकोs क्रम FIFO to empty.  It वापसs 1 when FIFO is empty, or
 * 0 अगर the समयout @समयout is reached beक्रमe, or अगर a संकेत is pending.
 */
अटल अचिन्हित पूर्णांक parport_ip32_drain_fअगरo(काष्ठा parport *p,
					    अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ expire = jअगरfies + समयout;
	अचिन्हित पूर्णांक polling_पूर्णांकerval;
	अचिन्हित पूर्णांक counter;

	/* Busy रुको क्रम approx. 200us */
	क्रम (counter = 0; counter < 40; counter++) अणु
		अगर (parport_ip32_पढ़ो_econtrol(p) & ECR_F_EMPTY)
			अवरोध;
		अगर (समय_after(jअगरfies, expire))
			अवरोध;
		अगर (संकेत_pending(current))
			अवरोध;
		udelay(5);
	पूर्ण
	/* Poll slowly.  Polling पूर्णांकerval starts with 1 millisecond, and is
	 * increased exponentially until 128.  */
	polling_पूर्णांकerval = 1; /* msecs */
	जबतक (!(parport_ip32_पढ़ो_econtrol(p) & ECR_F_EMPTY)) अणु
		अगर (समय_after_eq(jअगरfies, expire))
			अवरोध;
		msleep_पूर्णांकerruptible(polling_पूर्णांकerval);
		अगर (संकेत_pending(current))
			अवरोध;
		अगर (polling_पूर्णांकerval < 128)
			polling_पूर्णांकerval *= 2;
	पूर्ण

	वापस !!(parport_ip32_पढ़ो_econtrol(p) & ECR_F_EMPTY);
पूर्ण

/**
 * parport_ip32_get_fअगरo_residue - reset FIFO
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @mode:	current operation mode (ECR_MODE_PPF or ECR_MODE_ECP)
 *
 * This function resets FIFO, and वापसs the number of bytes reमुख्यing in it.
 */
अटल अचिन्हित पूर्णांक parport_ip32_get_fअगरo_residue(काष्ठा parport *p,
						  अचिन्हित पूर्णांक mode)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	अचिन्हित पूर्णांक residue;
	अचिन्हित पूर्णांक cnfga;

	/* FIXME - We are missing one byte अगर the prपूर्णांकer is off-line.  I
	 * करोn't know how to detect this.  It looks that the full bit is not
	 * always reliable.  For the moment, the problem is aव्योमed in most
	 * हालs by testing क्रम BUSY in parport_ip32_compat_ग_लिखो_data().
	 */
	अगर (parport_ip32_पढ़ो_econtrol(p) & ECR_F_EMPTY)
		residue = 0;
	अन्यथा अणु
		pr_debug1(PPIP32 "%s: FIFO is stuck\n", p->name);

		/* Stop all transfers.
		 *
		 * Microsoft's करोcument inकाष्ठाs to drive DCR_STROBE to 0,
		 * but it करोesn't work (at least in Compatibility mode, not
		 * tested in ECP mode).  Switching directly to Test mode (as
		 * in parport_pc) is not an option: it करोes confuse the port,
		 * ECP service पूर्णांकerrupts are no more working after that.  A
		 * hard reset is then needed to revert to a sane state.
		 *
		 * Let's hope that the FIFO is really stuck and that the
		 * peripheral करोesn't wake up now.
		 */
		parport_ip32_frob_control(p, DCR_STROBE, 0);

		/* Fill up FIFO */
		क्रम (residue = priv->fअगरo_depth; residue > 0; residue--) अणु
			अगर (parport_ip32_पढ़ो_econtrol(p) & ECR_F_FULL)
				अवरोध;
			ग_लिखोb(0x00, priv->regs.fअगरo);
		पूर्ण
	पूर्ण
	अगर (residue)
		pr_debug1(PPIP32 "%s: %d PWord%s left in FIFO\n",
			  p->name, residue,
			  (residue == 1) ? " was" : "s were");

	/* Now reset the FIFO */
	parport_ip32_set_mode(p, ECR_MODE_PS2);

	/* Host recovery क्रम ECP mode */
	अगर (mode == ECR_MODE_ECP) अणु
		parport_ip32_data_reverse(p);
		parport_ip32_frob_control(p, DCR_nINIT, 0);
		अगर (parport_रुको_peripheral(p, DSR_PERROR, 0))
			pr_debug1(PPIP32 "%s: PEerror timeout 1 in %s\n",
				  p->name, __func__);
		parport_ip32_frob_control(p, DCR_STROBE, DCR_STROBE);
		parport_ip32_frob_control(p, DCR_nINIT, DCR_nINIT);
		अगर (parport_रुको_peripheral(p, DSR_PERROR, DSR_PERROR))
			pr_debug1(PPIP32 "%s: PEerror timeout 2 in %s\n",
				  p->name, __func__);
	पूर्ण

	/* Adjust residue अगर needed */
	parport_ip32_set_mode(p, ECR_MODE_CFG);
	cnfga = पढ़ोb(priv->regs.cnfgA);
	अगर (!(cnfga & CNFGA_nBYTEINTRANS)) अणु
		pr_debug1(PPIP32 "%s: cnfgA contains 0x%02x\n",
			  p->name, cnfga);
		pr_debug1(PPIP32 "%s: Accounting for extra byte\n",
			  p->name);
		residue++;
	पूर्ण

	/* Don't care about partial PWords since we करो not support
	 * PWord != 1 byte. */

	/* Back to क्रमward PS2 mode. */
	parport_ip32_set_mode(p, ECR_MODE_PS2);
	parport_ip32_data_क्रमward(p);

	वापस residue;
पूर्ण

/**
 * parport_ip32_compat_ग_लिखो_data - ग_लिखो a block of data in SPP mode
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer of data to ग_लिखो
 * @len:	length of buffer @buf
 * @flags:	ignored
 */
अटल माप_प्रकार parport_ip32_compat_ग_लिखो_data(काष्ठा parport *p,
					     स्थिर व्योम *buf, माप_प्रकार len,
					     पूर्णांक flags)
अणु
	अटल अचिन्हित पूर्णांक पढ़ोy_beक्रमe = 1;
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	काष्ठा parport * स्थिर physport = p->physport;
	माप_प्रकार written = 0;

	/* Special हाल: a समयout of zero means we cannot call schedule().
	 * Also अगर O_NONBLOCK is set then use the शेष implementation. */
	अगर (physport->cad->समयout <= PARPORT_INACTIVITY_O_NONBLOCK)
		वापस parport_ieee1284_ग_लिखो_compat(p, buf, len, flags);

	/* Reset FIFO, go in क्रमward mode, and disable ackIntEn */
	parport_ip32_set_mode(p, ECR_MODE_PS2);
	parport_ip32_ग_लिखो_control(p, DCR_SELECT | DCR_nINIT);
	parport_ip32_data_क्रमward(p);
	parport_ip32_disable_irq(p);
	parport_ip32_set_mode(p, ECR_MODE_PPF);
	physport->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* Wait क्रम peripheral to become पढ़ोy */
	अगर (parport_रुको_peripheral(p, DSR_nBUSY | DSR_nFAULT,
				       DSR_nBUSY | DSR_nFAULT)) अणु
		/* Aव्योम to flood the logs */
		अगर (पढ़ोy_beक्रमe)
			pr_info(PPIP32 "%s: not ready in %s\n",
				p->name, __func__);
		पढ़ोy_beक्रमe = 0;
		जाओ stop;
	पूर्ण
	पढ़ोy_beक्रमe = 1;

	written = parport_ip32_fअगरo_ग_लिखो_block(p, buf, len);

	/* Wait FIFO to empty.  Timeout is proportional to FIFO_depth.  */
	parport_ip32_drain_fअगरo(p, physport->cad->समयout * priv->fअगरo_depth);

	/* Check क्रम a potential residue */
	written -= parport_ip32_get_fअगरo_residue(p, ECR_MODE_PPF);

	/* Then, रुको क्रम BUSY to get low. */
	अगर (parport_रुको_peripheral(p, DSR_nBUSY, DSR_nBUSY))
		prपूर्णांकk(KERN_DEBUG PPIP32 "%s: BUSY timeout in %s\n",
		       p->name, __func__);

stop:
	/* Reset FIFO */
	parport_ip32_set_mode(p, ECR_MODE_PS2);
	physport->ieee1284.phase = IEEE1284_PH_FWD_IDLE;

	वापस written;
पूर्ण

/*
 * FIXME - Insert here parport_ip32_ecp_पढ़ो_data().
 */

/**
 * parport_ip32_ecp_ग_लिखो_data - ग_लिखो a block of data in ECP mode
 * @p:		poपूर्णांकer to &काष्ठा parport
 * @buf:	buffer of data to ग_लिखो
 * @len:	length of buffer @buf
 * @flags:	ignored
 */
अटल माप_प्रकार parport_ip32_ecp_ग_लिखो_data(काष्ठा parport *p,
					  स्थिर व्योम *buf, माप_प्रकार len,
					  पूर्णांक flags)
अणु
	अटल अचिन्हित पूर्णांक पढ़ोy_beक्रमe = 1;
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	काष्ठा parport * स्थिर physport = p->physport;
	माप_प्रकार written = 0;

	/* Special हाल: a समयout of zero means we cannot call schedule().
	 * Also अगर O_NONBLOCK is set then use the शेष implementation. */
	अगर (physport->cad->समयout <= PARPORT_INACTIVITY_O_NONBLOCK)
		वापस parport_ieee1284_ecp_ग_लिखो_data(p, buf, len, flags);

	/* Negotiate to क्रमward mode अगर necessary. */
	अगर (physport->ieee1284.phase != IEEE1284_PH_FWD_IDLE) अणु
		/* Event 47: Set nInit high. */
		parport_ip32_frob_control(p, DCR_nINIT | DCR_AUTOFD,
					     DCR_nINIT | DCR_AUTOFD);

		/* Event 49: PError goes high. */
		अगर (parport_रुको_peripheral(p, DSR_PERROR, DSR_PERROR)) अणु
			prपूर्णांकk(KERN_DEBUG PPIP32 "%s: PError timeout in %s\n",
			       p->name, __func__);
			physport->ieee1284.phase = IEEE1284_PH_ECP_सूची_UNKNOWN;
			वापस 0;
		पूर्ण
	पूर्ण

	/* Reset FIFO, go in क्रमward mode, and disable ackIntEn */
	parport_ip32_set_mode(p, ECR_MODE_PS2);
	parport_ip32_ग_लिखो_control(p, DCR_SELECT | DCR_nINIT);
	parport_ip32_data_क्रमward(p);
	parport_ip32_disable_irq(p);
	parport_ip32_set_mode(p, ECR_MODE_ECP);
	physport->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* Wait क्रम peripheral to become पढ़ोy */
	अगर (parport_रुको_peripheral(p, DSR_nBUSY | DSR_nFAULT,
				       DSR_nBUSY | DSR_nFAULT)) अणु
		/* Aव्योम to flood the logs */
		अगर (पढ़ोy_beक्रमe)
			pr_info(PPIP32 "%s: not ready in %s\n",
				p->name, __func__);
		पढ़ोy_beक्रमe = 0;
		जाओ stop;
	पूर्ण
	पढ़ोy_beक्रमe = 1;

	written = parport_ip32_fअगरo_ग_लिखो_block(p, buf, len);

	/* Wait FIFO to empty.  Timeout is proportional to FIFO_depth.  */
	parport_ip32_drain_fअगरo(p, physport->cad->समयout * priv->fअगरo_depth);

	/* Check क्रम a potential residue */
	written -= parport_ip32_get_fअगरo_residue(p, ECR_MODE_ECP);

	/* Then, रुको क्रम BUSY to get low. */
	अगर (parport_रुको_peripheral(p, DSR_nBUSY, DSR_nBUSY))
		prपूर्णांकk(KERN_DEBUG PPIP32 "%s: BUSY timeout in %s\n",
		       p->name, __func__);

stop:
	/* Reset FIFO */
	parport_ip32_set_mode(p, ECR_MODE_PS2);
	physport->ieee1284.phase = IEEE1284_PH_FWD_IDLE;

	वापस written;
पूर्ण

/*
 * FIXME - Insert here parport_ip32_ecp_ग_लिखो_addr().
 */

/*--- Default parport operations ---------------------------------------*/

अटल स्थिर काष्ठा parport_operations parport_ip32_ops __initस्थिर = अणु
	.ग_लिखो_data		= parport_ip32_ग_लिखो_data,
	.पढ़ो_data		= parport_ip32_पढ़ो_data,

	.ग_लिखो_control		= parport_ip32_ग_लिखो_control,
	.पढ़ो_control		= parport_ip32_पढ़ो_control,
	.frob_control		= parport_ip32_frob_control,

	.पढ़ो_status		= parport_ip32_पढ़ो_status,

	.enable_irq		= parport_ip32_enable_irq,
	.disable_irq		= parport_ip32_disable_irq,

	.data_क्रमward		= parport_ip32_data_क्रमward,
	.data_reverse		= parport_ip32_data_reverse,

	.init_state		= parport_ip32_init_state,
	.save_state		= parport_ip32_save_state,
	.restore_state		= parport_ip32_restore_state,

	.epp_ग_लिखो_data		= parport_ieee1284_epp_ग_लिखो_data,
	.epp_पढ़ो_data		= parport_ieee1284_epp_पढ़ो_data,
	.epp_ग_लिखो_addr		= parport_ieee1284_epp_ग_लिखो_addr,
	.epp_पढ़ो_addr		= parport_ieee1284_epp_पढ़ो_addr,

	.ecp_ग_लिखो_data		= parport_ieee1284_ecp_ग_लिखो_data,
	.ecp_पढ़ो_data		= parport_ieee1284_ecp_पढ़ो_data,
	.ecp_ग_लिखो_addr		= parport_ieee1284_ecp_ग_लिखो_addr,

	.compat_ग_लिखो_data	= parport_ieee1284_ग_लिखो_compat,
	.nibble_पढ़ो_data	= parport_ieee1284_पढ़ो_nibble,
	.byte_पढ़ो_data		= parport_ieee1284_पढ़ो_byte,

	.owner			= THIS_MODULE,
पूर्ण;

/*--- Device detection -------------------------------------------------*/

/**
 * parport_ip32_ecp_supported - check क्रम an ECP port
 * @p:		poपूर्णांकer to the &parport काष्ठाure
 *
 * Returns 1 अगर an ECP port is found, and 0 otherwise.  This function actually
 * checks अगर an Extended Control Register seems to be present.  On successful
 * वापस, the port is placed in SPP mode.
 */
अटल __init अचिन्हित पूर्णांक parport_ip32_ecp_supported(काष्ठा parport *p)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	अचिन्हित पूर्णांक ecr;

	ecr = ECR_MODE_PS2 | ECR_nERRINTR | ECR_SERVINTR;
	ग_लिखोb(ecr, priv->regs.ecr);
	अगर (पढ़ोb(priv->regs.ecr) != (ecr | ECR_F_EMPTY))
		जाओ fail;

	pr_probe(p, "Found working ECR register\n");
	parport_ip32_set_mode(p, ECR_MODE_SPP);
	parport_ip32_ग_लिखो_control(p, DCR_SELECT | DCR_nINIT);
	वापस 1;

fail:
	pr_probe(p, "ECR register not found\n");
	वापस 0;
पूर्ण

/**
 * parport_ip32_fअगरo_supported - check क्रम FIFO parameters
 * @p:		poपूर्णांकer to the &parport काष्ठाure
 *
 * Check क्रम FIFO parameters of an Extended Capabilities Port.  Returns 1 on
 * success, and 0 otherwise.  Adjust FIFO parameters in the parport काष्ठाure.
 * On वापस, the port is placed in SPP mode.
 */
अटल __init अचिन्हित पूर्णांक parport_ip32_fअगरo_supported(काष्ठा parport *p)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	अचिन्हित पूर्णांक configa, configb;
	अचिन्हित पूर्णांक pword;
	अचिन्हित पूर्णांक i;

	/* Configuration mode */
	parport_ip32_set_mode(p, ECR_MODE_CFG);
	configa = पढ़ोb(priv->regs.cnfgA);
	configb = पढ़ोb(priv->regs.cnfgB);

	/* Find out PWord size */
	चयन (configa & CNFGA_ID_MASK) अणु
	हाल CNFGA_ID_8:
		pword = 1;
		अवरोध;
	हाल CNFGA_ID_16:
		pword = 2;
		अवरोध;
	हाल CNFGA_ID_32:
		pword = 4;
		अवरोध;
	शेष:
		pr_probe(p, "Unknown implementation ID: 0x%0x\n",
			 (configa & CNFGA_ID_MASK) >> CNFGA_ID_SHIFT);
		जाओ fail;
		अवरोध;
	पूर्ण
	अगर (pword != 1) अणु
		pr_probe(p, "Unsupported PWord size: %u\n", pword);
		जाओ fail;
	पूर्ण
	priv->pword = pword;
	pr_probe(p, "PWord is %u bits\n", 8 * priv->pword);

	/* Check क्रम compression support */
	ग_लिखोb(configb | CNFGB_COMPRESS, priv->regs.cnfgB);
	अगर (पढ़ोb(priv->regs.cnfgB) & CNFGB_COMPRESS)
		pr_probe(p, "Hardware compression detected (unsupported)\n");
	ग_लिखोb(configb & ~CNFGB_COMPRESS, priv->regs.cnfgB);

	/* Reset FIFO and go in test mode (no पूर्णांकerrupt, no DMA) */
	parport_ip32_set_mode(p, ECR_MODE_TST);

	/* FIFO must be empty now */
	अगर (!(पढ़ोb(priv->regs.ecr) & ECR_F_EMPTY)) अणु
		pr_probe(p, "FIFO not reset\n");
		जाओ fail;
	पूर्ण

	/* Find out FIFO depth. */
	priv->fअगरo_depth = 0;
	क्रम (i = 0; i < 1024; i++) अणु
		अगर (पढ़ोb(priv->regs.ecr) & ECR_F_FULL) अणु
			/* FIFO full */
			priv->fअगरo_depth = i;
			अवरोध;
		पूर्ण
		ग_लिखोb((u8)i, priv->regs.fअगरo);
	पूर्ण
	अगर (i >= 1024) अणु
		pr_probe(p, "Can't fill FIFO\n");
		जाओ fail;
	पूर्ण
	अगर (!priv->fअगरo_depth) अणु
		pr_probe(p, "Can't get FIFO depth\n");
		जाओ fail;
	पूर्ण
	pr_probe(p, "FIFO is %u PWords deep\n", priv->fअगरo_depth);

	/* Enable पूर्णांकerrupts */
	parport_ip32_frob_econtrol(p, ECR_SERVINTR, 0);

	/* Find out ग_लिखोIntrThreshold: number of PWords we know we can ग_लिखो
	 * अगर we get an पूर्णांकerrupt. */
	priv->ग_लिखोIntrThreshold = 0;
	क्रम (i = 0; i < priv->fअगरo_depth; i++) अणु
		अगर (पढ़ोb(priv->regs.fअगरo) != (u8)i) अणु
			pr_probe(p, "Invalid data in FIFO\n");
			जाओ fail;
		पूर्ण
		अगर (!priv->ग_लिखोIntrThreshold
		    && पढ़ोb(priv->regs.ecr) & ECR_SERVINTR)
			/* ग_लिखोIntrThreshold reached */
			priv->ग_लिखोIntrThreshold = i + 1;
		अगर (i + 1 < priv->fअगरo_depth
		    && पढ़ोb(priv->regs.ecr) & ECR_F_EMPTY) अणु
			/* FIFO empty beक्रमe the last byte? */
			pr_probe(p, "Data lost in FIFO\n");
			जाओ fail;
		पूर्ण
	पूर्ण
	अगर (!priv->ग_लिखोIntrThreshold) अणु
		pr_probe(p, "Can't get writeIntrThreshold\n");
		जाओ fail;
	पूर्ण
	pr_probe(p, "writeIntrThreshold is %u\n", priv->ग_लिखोIntrThreshold);

	/* FIFO must be empty now */
	अगर (!(पढ़ोb(priv->regs.ecr) & ECR_F_EMPTY)) अणु
		pr_probe(p, "Can't empty FIFO\n");
		जाओ fail;
	पूर्ण

	/* Reset FIFO */
	parport_ip32_set_mode(p, ECR_MODE_PS2);
	/* Set reverse direction (must be in PS2 mode) */
	parport_ip32_data_reverse(p);
	/* Test FIFO, no पूर्णांकerrupt, no DMA */
	parport_ip32_set_mode(p, ECR_MODE_TST);
	/* Enable पूर्णांकerrupts */
	parport_ip32_frob_econtrol(p, ECR_SERVINTR, 0);

	/* Find out पढ़ोIntrThreshold: number of PWords we can पढ़ो अगर we get
	 * an पूर्णांकerrupt. */
	priv->पढ़ोIntrThreshold = 0;
	क्रम (i = 0; i < priv->fअगरo_depth; i++) अणु
		ग_लिखोb(0xaa, priv->regs.fअगरo);
		अगर (पढ़ोb(priv->regs.ecr) & ECR_SERVINTR) अणु
			/* पढ़ोIntrThreshold reached */
			priv->पढ़ोIntrThreshold = i + 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!priv->पढ़ोIntrThreshold) अणु
		pr_probe(p, "Can't get readIntrThreshold\n");
		जाओ fail;
	पूर्ण
	pr_probe(p, "readIntrThreshold is %u\n", priv->पढ़ोIntrThreshold);

	/* Reset ECR */
	parport_ip32_set_mode(p, ECR_MODE_PS2);
	parport_ip32_data_क्रमward(p);
	parport_ip32_set_mode(p, ECR_MODE_SPP);
	वापस 1;

fail:
	priv->fअगरo_depth = 0;
	parport_ip32_set_mode(p, ECR_MODE_SPP);
	वापस 0;
पूर्ण

/*--- Initialization code ----------------------------------------------*/

/**
 * parport_ip32_make_isa_रेजिस्टरs - compute (ISA) रेजिस्टर addresses
 * @regs:	poपूर्णांकer to &काष्ठा parport_ip32_regs to fill
 * @base:	base address of standard and EPP रेजिस्टरs
 * @base_hi:	base address of ECP रेजिस्टरs
 * @regshअगरt:	how much to shअगरt रेजिस्टर offset by
 *
 * Compute रेजिस्टर addresses, according to the ISA standard.  The addresses
 * of the standard and EPP रेजिस्टरs are computed from address @base.  The
 * addresses of the ECP रेजिस्टरs are computed from address @base_hi.
 */
अटल व्योम __init
parport_ip32_make_isa_रेजिस्टरs(काष्ठा parport_ip32_regs *regs,
				व्योम __iomem *base, व्योम __iomem *base_hi,
				अचिन्हित पूर्णांक regshअगरt)
अणु
#घोषणा r_base(offset)    ((u8 __iomem *)base    + ((offset) << regshअगरt))
#घोषणा r_base_hi(offset) ((u8 __iomem *)base_hi + ((offset) << regshअगरt))
	*regs = (काष्ठा parport_ip32_regs)अणु
		.data		= r_base(0),
		.dsr		= r_base(1),
		.dcr		= r_base(2),
		.eppAddr	= r_base(3),
		.eppData0	= r_base(4),
		.eppData1	= r_base(5),
		.eppData2	= r_base(6),
		.eppData3	= r_base(7),
		.ecpAFअगरo	= r_base(0),
		.fअगरo		= r_base_hi(0),
		.cnfgA		= r_base_hi(0),
		.cnfgB		= r_base_hi(1),
		.ecr		= r_base_hi(2)
	पूर्ण;
#अघोषित r_base_hi
#अघोषित r_base
पूर्ण

/**
 * parport_ip32_probe_port - probe and रेजिस्टर IP32 built-in parallel port
 *
 * Returns the new allocated &parport काष्ठाure.  On error, an error code is
 * encoded in वापस value with the ERR_PTR function.
 */
अटल __init काष्ठा parport *parport_ip32_probe_port(व्योम)
अणु
	काष्ठा parport_ip32_regs regs;
	काष्ठा parport_ip32_निजी *priv = शून्य;
	काष्ठा parport_operations *ops = शून्य;
	काष्ठा parport *p = शून्य;
	पूर्णांक err;

	parport_ip32_make_isa_रेजिस्टरs(&regs, &mace->isa.parallel,
					&mace->isa.ecp1284, 8 /* regshअगरt */);

	ops = kदो_स्मृति(माप(काष्ठा parport_operations), GFP_KERNEL);
	priv = kदो_स्मृति(माप(काष्ठा parport_ip32_निजी), GFP_KERNEL);
	p = parport_रेजिस्टर_port(0, PARPORT_IRQ_NONE, PARPORT_DMA_NONE, ops);
	अगर (ops == शून्य || priv == शून्य || p == शून्य) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण
	p->base = MACE_BASE + दुरत्व(काष्ठा sgi_mace, isa.parallel);
	p->base_hi = MACE_BASE + दुरत्व(काष्ठा sgi_mace, isa.ecp1284);
	p->निजी_data = priv;

	*ops = parport_ip32_ops;
	*priv = (काष्ठा parport_ip32_निजी)अणु
		.regs			= regs,
		.dcr_writable		= DCR_सूची | DCR_SELECT | DCR_nINIT |
					  DCR_AUTOFD | DCR_STROBE,
		.irq_mode		= PARPORT_IP32_IRQ_FWD,
	पूर्ण;
	init_completion(&priv->irq_complete);

	/* Probe port. */
	अगर (!parport_ip32_ecp_supported(p)) अणु
		err = -ENODEV;
		जाओ fail;
	पूर्ण
	parport_ip32_dump_state(p, "begin init", 0);

	/* We found what looks like a working ECR रेजिस्टर.  Simply assume
	 * that all modes are correctly supported.  Enable basic modes. */
	p->modes = PARPORT_MODE_PCSPP | PARPORT_MODE_SAFEININT;
	p->modes |= PARPORT_MODE_TRISTATE;

	अगर (!parport_ip32_fअगरo_supported(p)) अणु
		pr_warn(PPIP32 "%s: error: FIFO disabled\n", p->name);
		/* Disable hardware modes depending on a working FIFO. */
		features &= ~PARPORT_IP32_ENABLE_SPP;
		features &= ~PARPORT_IP32_ENABLE_ECP;
		/* DMA is not needed अगर FIFO is not supported.  */
		features &= ~PARPORT_IP32_ENABLE_DMA;
	पूर्ण

	/* Request IRQ */
	अगर (features & PARPORT_IP32_ENABLE_IRQ) अणु
		पूर्णांक irq = MACEISA_PARALLEL_IRQ;
		अगर (request_irq(irq, parport_ip32_पूर्णांकerrupt, 0, p->name, p)) अणु
			pr_warn(PPIP32 "%s: error: IRQ disabled\n", p->name);
			/* DMA cannot work without पूर्णांकerrupts. */
			features &= ~PARPORT_IP32_ENABLE_DMA;
		पूर्ण अन्यथा अणु
			pr_probe(p, "Interrupt support enabled\n");
			p->irq = irq;
			priv->dcr_writable |= DCR_IRQ;
		पूर्ण
	पूर्ण

	/* Allocate DMA resources */
	अगर (features & PARPORT_IP32_ENABLE_DMA) अणु
		अगर (parport_ip32_dma_रेजिस्टर())
			pr_warn(PPIP32 "%s: error: DMA disabled\n", p->name);
		अन्यथा अणु
			pr_probe(p, "DMA support enabled\n");
			p->dma = 0; /* arbitrary value != PARPORT_DMA_NONE */
			p->modes |= PARPORT_MODE_DMA;
		पूर्ण
	पूर्ण

	अगर (features & PARPORT_IP32_ENABLE_SPP) अणु
		/* Enable compatibility FIFO mode */
		p->ops->compat_ग_लिखो_data = parport_ip32_compat_ग_लिखो_data;
		p->modes |= PARPORT_MODE_COMPAT;
		pr_probe(p, "Hardware support for SPP mode enabled\n");
	पूर्ण
	अगर (features & PARPORT_IP32_ENABLE_EPP) अणु
		/* Set up access functions to use EPP hardware. */
		p->ops->epp_पढ़ो_data = parport_ip32_epp_पढ़ो_data;
		p->ops->epp_ग_लिखो_data = parport_ip32_epp_ग_लिखो_data;
		p->ops->epp_पढ़ो_addr = parport_ip32_epp_पढ़ो_addr;
		p->ops->epp_ग_लिखो_addr = parport_ip32_epp_ग_लिखो_addr;
		p->modes |= PARPORT_MODE_EPP;
		pr_probe(p, "Hardware support for EPP mode enabled\n");
	पूर्ण
	अगर (features & PARPORT_IP32_ENABLE_ECP) अणु
		/* Enable ECP FIFO mode */
		p->ops->ecp_ग_लिखो_data = parport_ip32_ecp_ग_लिखो_data;
		/* FIXME - not implemented */
/*		p->ops->ecp_पढ़ो_data  = parport_ip32_ecp_पढ़ो_data; */
/*		p->ops->ecp_ग_लिखो_addr = parport_ip32_ecp_ग_लिखो_addr; */
		p->modes |= PARPORT_MODE_ECP;
		pr_probe(p, "Hardware support for ECP mode enabled\n");
	पूर्ण

	/* Initialize the port with sensible values */
	parport_ip32_set_mode(p, ECR_MODE_PS2);
	parport_ip32_ग_लिखो_control(p, DCR_SELECT | DCR_nINIT);
	parport_ip32_data_क्रमward(p);
	parport_ip32_disable_irq(p);
	parport_ip32_ग_लिखो_data(p, 0x00);
	parport_ip32_dump_state(p, "end init", 0);

	/* Prपूर्णांक out what we found */
	pr_info("%s: SGI IP32 at 0x%lx (0x%lx)", p->name, p->base, p->base_hi);
	अगर (p->irq != PARPORT_IRQ_NONE)
		pr_cont(", irq %d", p->irq);
	pr_cont(" [");
#घोषणा prपूर्णांकmode(x)							\
करो अणु									\
	अगर (p->modes & PARPORT_MODE_##x)				\
		pr_cont("%s%s", f++ ? "," : "", #x);			\
पूर्ण जबतक (0)
	अणु
		अचिन्हित पूर्णांक f = 0;
		prपूर्णांकmode(PCSPP);
		prपूर्णांकmode(TRISTATE);
		prपूर्णांकmode(COMPAT);
		prपूर्णांकmode(EPP);
		prपूर्णांकmode(ECP);
		prपूर्णांकmode(DMA);
	पूर्ण
#अघोषित prपूर्णांकmode
	pr_cont("]\n");

	parport_announce_port(p);
	वापस p;

fail:
	अगर (p)
		parport_put_port(p);
	kमुक्त(priv);
	kमुक्त(ops);
	वापस ERR_PTR(err);
पूर्ण

/**
 * parport_ip32_unरेजिस्टर_port - unरेजिस्टर a parallel port
 * @p:		poपूर्णांकer to the &काष्ठा parport
 *
 * Unरेजिस्टरs a parallel port and मुक्त previously allocated resources
 * (memory, IRQ, ...).
 */
अटल __निकास व्योम parport_ip32_unरेजिस्टर_port(काष्ठा parport *p)
अणु
	काष्ठा parport_ip32_निजी * स्थिर priv = p->physport->निजी_data;
	काष्ठा parport_operations *ops = p->ops;

	parport_हटाओ_port(p);
	अगर (p->modes & PARPORT_MODE_DMA)
		parport_ip32_dma_unरेजिस्टर();
	अगर (p->irq != PARPORT_IRQ_NONE)
		मुक्त_irq(p->irq, p);
	parport_put_port(p);
	kमुक्त(priv);
	kमुक्त(ops);
पूर्ण

/**
 * parport_ip32_init - module initialization function
 */
अटल पूर्णांक __init parport_ip32_init(व्योम)
अणु
	pr_info(PPIP32 "SGI IP32 built-in parallel port driver v0.6\n");
	this_port = parport_ip32_probe_port();
	वापस PTR_ERR_OR_ZERO(this_port);
पूर्ण

/**
 * parport_ip32_निकास - module termination function
 */
अटल व्योम __निकास parport_ip32_निकास(व्योम)
अणु
	parport_ip32_unरेजिस्टर_port(this_port);
पूर्ण

/*--- Module stuff -----------------------------------------------------*/

MODULE_AUTHOR("Arnaud Giersch <arnaud.giersch@free.fr>");
MODULE_DESCRIPTION("SGI IP32 built-in parallel port driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.6");		/* update in parport_ip32_init() too */

module_init(parport_ip32_init);
module_निकास(parport_ip32_निकास);

module_param(verbose_probing, bool, S_IRUGO);
MODULE_PARM_DESC(verbose_probing, "Log chit-chat during initialization");

module_param(features, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(features,
		 "Bit mask of features to enable"
		 ", bit 0: IRQ support"
		 ", bit 1: DMA support"
		 ", bit 2: hardware SPP mode"
		 ", bit 3: hardware EPP mode"
		 ", bit 4: hardware ECP mode");
