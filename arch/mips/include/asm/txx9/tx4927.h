<शैली गुरु>
/*
 * Author: MontaVista Software, Inc.
 *	   source@mvista.com
 *
 * Copyright 2001-2006 MontaVista Software Inc.
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */
#अगर_अघोषित __ASM_TXX9_TX4927_H
#घोषणा __ASM_TXX9_TX4927_H

#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/txx9irq.h>
#समावेश <यंत्र/txx9/tx4927pcic.h>

#अगर_घोषित CONFIG_64BIT
#घोषणा TX4927_REG_BASE 0xffffffffff1f0000UL
#अन्यथा
#घोषणा TX4927_REG_BASE 0xff1f0000UL
#पूर्ण_अगर
#घोषणा TX4927_REG_SIZE 0x00010000

#घोषणा TX4927_SDRAMC_REG	(TX4927_REG_BASE + 0x8000)
#घोषणा TX4927_EBUSC_REG	(TX4927_REG_BASE + 0x9000)
#घोषणा TX4927_DMA_REG		(TX4927_REG_BASE + 0xb000)
#घोषणा TX4927_PCIC_REG		(TX4927_REG_BASE + 0xd000)
#घोषणा TX4927_CCFG_REG		(TX4927_REG_BASE + 0xe000)
#घोषणा TX4927_IRC_REG		(TX4927_REG_BASE + 0xf600)
#घोषणा TX4927_NR_TMR	3
#घोषणा TX4927_TMR_REG(ch)	(TX4927_REG_BASE + 0xf000 + (ch) * 0x100)
#घोषणा TX4927_NR_SIO	2
#घोषणा TX4927_SIO_REG(ch)	(TX4927_REG_BASE + 0xf300 + (ch) * 0x100)
#घोषणा TX4927_PIO_REG		(TX4927_REG_BASE + 0xf500)
#घोषणा TX4927_ACLC_REG		(TX4927_REG_BASE + 0xf700)

#घोषणा TX4927_IR_ECCERR	0
#घोषणा TX4927_IR_WTOERR	1
#घोषणा TX4927_NUM_IR_INT	6
#घोषणा TX4927_IR_INT(n)	(2 + (n))
#घोषणा TX4927_NUM_IR_SIO	2
#घोषणा TX4927_IR_SIO(n)	(8 + (n))
#घोषणा TX4927_NUM_IR_DMA	4
#घोषणा TX4927_IR_DMA(n)	(10 + (n))
#घोषणा TX4927_IR_PIO		14
#घोषणा TX4927_IR_PDMAC		15
#घोषणा TX4927_IR_PCIC		16
#घोषणा TX4927_NUM_IR_TMR	3
#घोषणा TX4927_IR_TMR(n)	(17 + (n))
#घोषणा TX4927_IR_PCIERR	22
#घोषणा TX4927_IR_PCIPME	23
#घोषणा TX4927_IR_ACLC		24
#घोषणा TX4927_IR_ACLCPME	25
#घोषणा TX4927_NUM_IR	32

#घोषणा TX4927_IRC_INT	2	/* IP[2] in Status रेजिस्टर */

#घोषणा TX4927_NUM_PIO	16

काष्ठा tx4927_sdramc_reg अणु
	u64 cr[4];
	u64 unused0[4];
	u64 tr;
	u64 unused1[2];
	u64 cmd;
पूर्ण;

काष्ठा tx4927_ebusc_reg अणु
	u64 cr[8];
पूर्ण;

काष्ठा tx4927_ccfg_reg अणु
	u64 ccfg;
	u64 crir;
	u64 pcfg;
	u64 toea;
	u64 clkctr;
	u64 unused0;
	u64 garbc;
	u64 unused1;
	u64 unused2;
	u64 ramp;
पूर्ण;

/*
 * CCFG
 */
/* CCFG : Chip Configuration */
#घोषणा TX4927_CCFG_WDRST	0x0000020000000000ULL
#घोषणा TX4927_CCFG_WDREXEN	0x0000010000000000ULL
#घोषणा TX4927_CCFG_BCFG_MASK	0x000000ff00000000ULL
#घोषणा TX4927_CCFG_TINTDIS	0x01000000
#घोषणा TX4927_CCFG_PCI66	0x00800000
#घोषणा TX4927_CCFG_PCIMODE	0x00400000
#घोषणा TX4927_CCFG_DIVMODE_MASK	0x000e0000
#घोषणा TX4927_CCFG_DIVMODE_8	(0x0 << 17)
#घोषणा TX4927_CCFG_DIVMODE_12	(0x1 << 17)
#घोषणा TX4927_CCFG_DIVMODE_16	(0x2 << 17)
#घोषणा TX4927_CCFG_DIVMODE_10	(0x3 << 17)
#घोषणा TX4927_CCFG_DIVMODE_2	(0x4 << 17)
#घोषणा TX4927_CCFG_DIVMODE_3	(0x5 << 17)
#घोषणा TX4927_CCFG_DIVMODE_4	(0x6 << 17)
#घोषणा TX4927_CCFG_DIVMODE_2_5 (0x7 << 17)
#घोषणा TX4927_CCFG_BEOW	0x00010000
#घोषणा TX4927_CCFG_WR	0x00008000
#घोषणा TX4927_CCFG_TOE 0x00004000
#घोषणा TX4927_CCFG_PCIARB	0x00002000
#घोषणा TX4927_CCFG_PCIDIVMODE_MASK	0x00001800
#घोषणा TX4927_CCFG_PCIDIVMODE_2_5	0x00000000
#घोषणा TX4927_CCFG_PCIDIVMODE_3	0x00000800
#घोषणा TX4927_CCFG_PCIDIVMODE_5	0x00001000
#घोषणा TX4927_CCFG_PCIDIVMODE_6	0x00001800
#घोषणा TX4927_CCFG_SYSSP_MASK	0x000000c0
#घोषणा TX4927_CCFG_ENDIAN	0x00000004
#घोषणा TX4927_CCFG_HALT	0x00000002
#घोषणा TX4927_CCFG_ACEHOLD	0x00000001
#घोषणा TX4927_CCFG_W1CBITS	(TX4927_CCFG_WDRST | TX4927_CCFG_BEOW)

/* PCFG : Pin Configuration */
#घोषणा TX4927_PCFG_SDCLKDLY_MASK	0x30000000
#घोषणा TX4927_PCFG_SDCLKDLY(d) ((d)<<28)
#घोषणा TX4927_PCFG_SYSCLKEN	0x08000000
#घोषणा TX4927_PCFG_SDCLKEN_ALL 0x07800000
#घोषणा TX4927_PCFG_SDCLKEN(ch) (0x00800000<<(ch))
#घोषणा TX4927_PCFG_PCICLKEN_ALL	0x003f0000
#घोषणा TX4927_PCFG_PCICLKEN(ch)	(0x00010000<<(ch))
#घोषणा TX4927_PCFG_SEL2	0x00000200
#घोषणा TX4927_PCFG_SEL1	0x00000100
#घोषणा TX4927_PCFG_DMASEL_ALL	0x000000ff
#घोषणा TX4927_PCFG_DMASEL0_MASK	0x00000003
#घोषणा TX4927_PCFG_DMASEL1_MASK	0x0000000c
#घोषणा TX4927_PCFG_DMASEL2_MASK	0x00000030
#घोषणा TX4927_PCFG_DMASEL3_MASK	0x000000c0
#घोषणा TX4927_PCFG_DMASEL0_DRQ0	0x00000000
#घोषणा TX4927_PCFG_DMASEL0_SIO1	0x00000001
#घोषणा TX4927_PCFG_DMASEL0_ACL0	0x00000002
#घोषणा TX4927_PCFG_DMASEL0_ACL2	0x00000003
#घोषणा TX4927_PCFG_DMASEL1_DRQ1	0x00000000
#घोषणा TX4927_PCFG_DMASEL1_SIO1	0x00000004
#घोषणा TX4927_PCFG_DMASEL1_ACL1	0x00000008
#घोषणा TX4927_PCFG_DMASEL1_ACL3	0x0000000c
#घोषणा TX4927_PCFG_DMASEL2_DRQ2	0x00000000	/* SEL2=0 */
#घोषणा TX4927_PCFG_DMASEL2_SIO0	0x00000010	/* SEL2=0 */
#घोषणा TX4927_PCFG_DMASEL2_ACL1	0x00000000	/* SEL2=1 */
#घोषणा TX4927_PCFG_DMASEL2_ACL2	0x00000020	/* SEL2=1 */
#घोषणा TX4927_PCFG_DMASEL2_ACL0	0x00000030	/* SEL2=1 */
#घोषणा TX4927_PCFG_DMASEL3_DRQ3	0x00000000
#घोषणा TX4927_PCFG_DMASEL3_SIO0	0x00000040
#घोषणा TX4927_PCFG_DMASEL3_ACL3	0x00000080
#घोषणा TX4927_PCFG_DMASEL3_ACL1	0x000000c0

/* CLKCTR : Clock Control */
#घोषणा TX4927_CLKCTR_ACLCKD	0x02000000
#घोषणा TX4927_CLKCTR_PIOCKD	0x01000000
#घोषणा TX4927_CLKCTR_DMACKD	0x00800000
#घोषणा TX4927_CLKCTR_PCICKD	0x00400000
#घोषणा TX4927_CLKCTR_TM0CKD	0x00100000
#घोषणा TX4927_CLKCTR_TM1CKD	0x00080000
#घोषणा TX4927_CLKCTR_TM2CKD	0x00040000
#घोषणा TX4927_CLKCTR_SIO0CKD	0x00020000
#घोषणा TX4927_CLKCTR_SIO1CKD	0x00010000
#घोषणा TX4927_CLKCTR_ACLRST	0x00000200
#घोषणा TX4927_CLKCTR_PIORST	0x00000100
#घोषणा TX4927_CLKCTR_DMARST	0x00000080
#घोषणा TX4927_CLKCTR_PCIRST	0x00000040
#घोषणा TX4927_CLKCTR_TM0RST	0x00000010
#घोषणा TX4927_CLKCTR_TM1RST	0x00000008
#घोषणा TX4927_CLKCTR_TM2RST	0x00000004
#घोषणा TX4927_CLKCTR_SIO0RST	0x00000002
#घोषणा TX4927_CLKCTR_SIO1RST	0x00000001

#घोषणा tx4927_sdramcptr \
		((काष्ठा tx4927_sdramc_reg __iomem *)TX4927_SDRAMC_REG)
#घोषणा tx4927_pcicptr \
		((काष्ठा tx4927_pcic_reg __iomem *)TX4927_PCIC_REG)
#घोषणा tx4927_ccfgptr \
		((काष्ठा tx4927_ccfg_reg __iomem *)TX4927_CCFG_REG)
#घोषणा tx4927_ebuscptr \
		((काष्ठा tx4927_ebusc_reg __iomem *)TX4927_EBUSC_REG)
#घोषणा tx4927_pioptr		((काष्ठा txx9_pio_reg __iomem *)TX4927_PIO_REG)

#घोषणा TX4927_REV_PCODE()	\
	((__u32)__raw_पढ़ोq(&tx4927_ccfgptr->crir) >> 16)

#घोषणा TX4927_SDRAMC_CR(ch)	__raw_पढ़ोq(&tx4927_sdramcptr->cr[(ch)])
#घोषणा TX4927_SDRAMC_BA(ch)	((TX4927_SDRAMC_CR(ch) >> 49) << 21)
#घोषणा TX4927_SDRAMC_SIZE(ch)	\
	((((TX4927_SDRAMC_CR(ch) >> 33) & 0x7fff) + 1) << 21)

#घोषणा TX4927_EBUSC_CR(ch)	__raw_पढ़ोq(&tx4927_ebuscptr->cr[(ch)])
#घोषणा TX4927_EBUSC_BA(ch)	((TX4927_EBUSC_CR(ch) >> 48) << 20)
#घोषणा TX4927_EBUSC_SIZE(ch)	\
	(0x00100000 << ((अचिन्हित दीर्घ)(TX4927_EBUSC_CR(ch) >> 8) & 0xf))
#घोषणा TX4927_EBUSC_WIDTH(ch)	\
	(64 >> ((__u32)(TX4927_EBUSC_CR(ch) >> 20) & 0x3))

/* utilities */
अटल अंतरभूत व्योम txx9_clear64(__u64 __iomem *adr, __u64 bits)
अणु
#अगर_घोषित CONFIG_32BIT
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
#पूर्ण_अगर
	____raw_ग_लिखोq(____raw_पढ़ोq(adr) & ~bits, adr);
#अगर_घोषित CONFIG_32BIT
	local_irq_restore(flags);
#पूर्ण_अगर
पूर्ण
अटल अंतरभूत व्योम txx9_set64(__u64 __iomem *adr, __u64 bits)
अणु
#अगर_घोषित CONFIG_32BIT
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
#पूर्ण_अगर
	____raw_ग_लिखोq(____raw_पढ़ोq(adr) | bits, adr);
#अगर_घोषित CONFIG_32BIT
	local_irq_restore(flags);
#पूर्ण_अगर
पूर्ण

/* These functions are not पूर्णांकerrupt safe. */
अटल अंतरभूत व्योम tx4927_ccfg_clear(__u64 bits)
अणु
	____raw_ग_लिखोq(____raw_पढ़ोq(&tx4927_ccfgptr->ccfg)
		       & ~(TX4927_CCFG_W1CBITS | bits),
		       &tx4927_ccfgptr->ccfg);
पूर्ण
अटल अंतरभूत व्योम tx4927_ccfg_set(__u64 bits)
अणु
	____raw_ग_लिखोq((____raw_पढ़ोq(&tx4927_ccfgptr->ccfg)
			& ~TX4927_CCFG_W1CBITS) | bits,
		       &tx4927_ccfgptr->ccfg);
पूर्ण
अटल अंतरभूत व्योम tx4927_ccfg_change(__u64 change, __u64 new)
अणु
	____raw_ग_लिखोq((____raw_पढ़ोq(&tx4927_ccfgptr->ccfg)
			& ~(TX4927_CCFG_W1CBITS | change)) |
		       new,
		       &tx4927_ccfgptr->ccfg);
पूर्ण

अचिन्हित पूर्णांक tx4927_get_mem_size(व्योम);
व्योम tx4927_wdt_init(व्योम);
व्योम tx4927_setup(व्योम);
व्योम tx4927_समय_init(अचिन्हित पूर्णांक पंचांगrnr);
व्योम tx4927_sio_init(अचिन्हित पूर्णांक sclk, अचिन्हित पूर्णांक cts_mask);
पूर्णांक tx4927_report_pciclk(व्योम);
पूर्णांक tx4927_pciclk66_setup(व्योम);
व्योम tx4927_setup_pcierr_irq(व्योम);
व्योम tx4927_irq_init(व्योम);
व्योम tx4927_mtd_init(पूर्णांक ch);
व्योम tx4927_dmac_init(पूर्णांक स_नकल_chan);
व्योम tx4927_aclc_init(अचिन्हित पूर्णांक dma_chan_out, अचिन्हित पूर्णांक dma_chan_in);

#पूर्ण_अगर /* __ASM_TXX9_TX4927_H */
