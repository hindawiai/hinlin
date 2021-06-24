<शैली गुरु>
/*
** atariपूर्णांकs.h -- Atari Linux पूर्णांकerrupt handling काष्ठाs and prototypes
**
** Copyright 1994 by Bjथघrn Brauel
**
** 5/2/94 Roman Hodek:
**   TT पूर्णांकerrupt definitions added.
**
** 12/02/96: (Roman)
**   Adapted to new पूर्णांक handling scheme (see ataपूर्णांकs.c); revised numbering
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
**
*/

#अगर_अघोषित _LINUX_ATARIINTS_H_
#घोषणा _LINUX_ATARIINTS_H_

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/atarihw.h>

/*
** Atari Interrupt sources.
**
*/

#घोषणा STMFP_SOURCE_BASE  8
#घोषणा TTMFP_SOURCE_BASE  24
#घोषणा SCC_SOURCE_BASE    40
#घोषणा VME_SOURCE_BASE    56
#घोषणा VME_MAX_SOURCES    16

#घोषणा NUM_ATARI_SOURCES  141

/* convert vector number to पूर्णांक source number */
#घोषणा IRQ_VECTOR_TO_SOURCE(v)	((v) - ((v) < 0x20 ? 0x18 : (0x40-8)))

/* convert irq_handler index to vector number */
#घोषणा IRQ_SOURCE_TO_VECTOR(i)	((i) + ((i) < 8 ? 0x18 : (0x40-8)))

/* ST-MFP पूर्णांकerrupts */
#घोषणा IRQ_MFP_BUSY      (8)
#घोषणा IRQ_MFP_DCD       (9)
#घोषणा IRQ_MFP_CTS	  (10)
#घोषणा IRQ_MFP_GPU	  (11)
#घोषणा IRQ_MFP_TIMD      (12)
#घोषणा IRQ_MFP_TIMC	  (13)
#घोषणा IRQ_MFP_ACIA	  (14)
#घोषणा IRQ_MFP_FDC       (15)
#घोषणा IRQ_MFP_ACSI      IRQ_MFP_FDC
#घोषणा IRQ_MFP_FSCSI     IRQ_MFP_FDC
#घोषणा IRQ_MFP_IDE       IRQ_MFP_FDC
#घोषणा IRQ_MFP_TIMB      (16)
#घोषणा IRQ_MFP_SERERR    (17)
#घोषणा IRQ_MFP_SEREMPT   (18)
#घोषणा IRQ_MFP_RECERR    (19)
#घोषणा IRQ_MFP_RECFULL   (20)
#घोषणा IRQ_MFP_TIMA      (21)
#घोषणा IRQ_MFP_RI        (22)
#घोषणा IRQ_MFP_MMD       (23)

/* TT-MFP पूर्णांकerrupts */
#घोषणा IRQ_TT_MFP_IO0       (24)
#घोषणा IRQ_TT_MFP_IO1       (25)
#घोषणा IRQ_TT_MFP_SCC	     (26)
#घोषणा IRQ_TT_MFP_RI	     (27)
#घोषणा IRQ_TT_MFP_TIMD      (28)
#घोषणा IRQ_TT_MFP_TIMC	     (29)
#घोषणा IRQ_TT_MFP_DRVRDY    (30)
#घोषणा IRQ_TT_MFP_SCSIDMA   (31)
#घोषणा IRQ_TT_MFP_TIMB      (32)
#घोषणा IRQ_TT_MFP_SERERR    (33)
#घोषणा IRQ_TT_MFP_SEREMPT   (34)
#घोषणा IRQ_TT_MFP_RECERR    (35)
#घोषणा IRQ_TT_MFP_RECFULL   (36)
#घोषणा IRQ_TT_MFP_TIMA      (37)
#घोषणा IRQ_TT_MFP_RTC       (38)
#घोषणा IRQ_TT_MFP_SCSI      (39)

/* SCC पूर्णांकerrupts */
#घोषणा IRQ_SCCB_TX	     (40)
#घोषणा IRQ_SCCB_STAT	     (42)
#घोषणा IRQ_SCCB_RX	     (44)
#घोषणा IRQ_SCCB_SPCOND	     (46)
#घोषणा IRQ_SCCA_TX	     (48)
#घोषणा IRQ_SCCA_STAT	     (50)
#घोषणा IRQ_SCCA_RX	     (52)
#घोषणा IRQ_SCCA_SPCOND	     (54)

/* shared MFP समयr D पूर्णांकerrupts - hires समयr क्रम EtherNEC et al. */
#घोषणा IRQ_MFP_TIMER1       (64)
#घोषणा IRQ_MFP_TIMER2       (65)
#घोषणा IRQ_MFP_TIMER3       (66)
#घोषणा IRQ_MFP_TIMER4       (67)
#घोषणा IRQ_MFP_TIMER5       (68)
#घोषणा IRQ_MFP_TIMER6       (69)
#घोषणा IRQ_MFP_TIMER7       (70)
#घोषणा IRQ_MFP_TIMER8       (71)

#घोषणा INT_CLK   24576	    /* CLK जबतक पूर्णांक_clk =2.456MHz and भागide = 100 */
#घोषणा INT_TICKS 246	    /* to make sched_समय = 99.902... HZ */


#घोषणा MFP_ENABLE	0
#घोषणा MFP_PENDING	1
#घोषणा MFP_SERVICE	2
#घोषणा MFP_MASK	3

/* Utility functions क्रम setting/clearing bits in the पूर्णांकerrupt रेजिस्टरs of
 * the MFP. 'type' should be constant, if 'irq' is स्थिरant, too, code size is
 * reduced. set_mfp_bit() is nonsense क्रम PENDING and SERVICE रेजिस्टरs. */

अटल अंतरभूत पूर्णांक get_mfp_bit( अचिन्हित irq, पूर्णांक type )

अणु	अचिन्हित अक्षर	mask, *reg;

	mask = 1 << (irq & 7);
	reg = (अचिन्हित अक्षर *)&st_mfp.पूर्णांक_en_a + type*4 +
		  ((irq & 8) >> 2) + (((irq-8) & 16) << 3);
	वापस( *reg & mask );
पूर्ण

अटल अंतरभूत व्योम set_mfp_bit( अचिन्हित irq, पूर्णांक type )

अणु	अचिन्हित अक्षर	mask, *reg;

	mask = 1 << (irq & 7);
	reg = (अचिन्हित अक्षर *)&st_mfp.पूर्णांक_en_a + type*4 +
		  ((irq & 8) >> 2) + (((irq-8) & 16) << 3);
	__यंत्र__ __अस्थिर__ ( "orb %0,%1"
			      : : "di" (mask), "m" (*reg) : "memory" );
पूर्ण

अटल अंतरभूत व्योम clear_mfp_bit( अचिन्हित irq, पूर्णांक type )

अणु	अचिन्हित अक्षर	mask, *reg;

	mask = ~(1 << (irq & 7));
	reg = (अचिन्हित अक्षर *)&st_mfp.पूर्णांक_en_a + type*4 +
		  ((irq & 8) >> 2) + (((irq-8) & 16) << 3);
	अगर (type == MFP_PENDING || type == MFP_SERVICE)
		__यंत्र__ __अस्थिर__ ( "moveb %0,%1"
				      : : "di" (mask), "m" (*reg) : "memory" );
	अन्यथा
		__यंत्र__ __अस्थिर__ ( "andb %0,%1"
				      : : "di" (mask), "m" (*reg) : "memory" );
पूर्ण

/*
 * अणुen,disपूर्णable_irq have the usual semantics of temporary blocking the
 * पूर्णांकerrupt, but not losing requests that happen between disabling and
 * enabling. This is करोne with the MFP mask रेजिस्टरs.
 */

अटल अंतरभूत व्योम atari_enable_irq( अचिन्हित irq )

अणु
	अगर (irq < STMFP_SOURCE_BASE || irq >= SCC_SOURCE_BASE) वापस;
	set_mfp_bit( irq, MFP_MASK );
पूर्ण

अटल अंतरभूत व्योम atari_disable_irq( अचिन्हित irq )

अणु
	अगर (irq < STMFP_SOURCE_BASE || irq >= SCC_SOURCE_BASE) वापस;
	clear_mfp_bit( irq, MFP_MASK );
पूर्ण

/*
 * In opposite to अणुen,disपूर्णable_irq, requests between turnअणुoff,onपूर्ण_irq are not
 * "stored"
 */

अटल अंतरभूत व्योम atari_turnon_irq( अचिन्हित irq )

अणु
	अगर (irq < STMFP_SOURCE_BASE || irq >= SCC_SOURCE_BASE) वापस;
	set_mfp_bit( irq, MFP_ENABLE );
पूर्ण

अटल अंतरभूत व्योम atari_turnoff_irq( अचिन्हित irq )

अणु
	अगर (irq < STMFP_SOURCE_BASE || irq >= SCC_SOURCE_BASE) वापस;
	clear_mfp_bit( irq, MFP_ENABLE );
	clear_mfp_bit( irq, MFP_PENDING );
पूर्ण

अटल अंतरभूत व्योम atari_clear_pending_irq( अचिन्हित irq )

अणु
	अगर (irq < STMFP_SOURCE_BASE || irq >= SCC_SOURCE_BASE) वापस;
	clear_mfp_bit( irq, MFP_PENDING );
पूर्ण

अटल अंतरभूत पूर्णांक atari_irq_pending( अचिन्हित irq )

अणु
	अगर (irq < STMFP_SOURCE_BASE || irq >= SCC_SOURCE_BASE) वापस( 0 );
	वापस( get_mfp_bit( irq, MFP_PENDING ) );
पूर्ण

अचिन्हित पूर्णांक atari_रेजिस्टर_vme_पूर्णांक(व्योम);
व्योम atari_unरेजिस्टर_vme_पूर्णांक(अचिन्हित पूर्णांक);

#पूर्ण_अगर /* linux/atariपूर्णांकs.h */
