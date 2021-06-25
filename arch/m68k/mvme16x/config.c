<शैली गुरु>
/*
 *  arch/m68k/mvme16x/config.c
 *
 *  Copyright (C) 1995 Riअक्षरd Hirst [riअक्षरd@sleepie.demon.co.uk]
 *
 * Based on:
 *
 *  linux/amiga/config.c
 *
 *  Copyright (C) 1993 Hamish Macकरोnald
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file README.legal in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/tty.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/console.h>
#समावेश <linux/linkage.h>
#समावेश <linux/init.h>
#समावेश <linux/major.h>
#समावेश <linux/genhd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/bootinfo-vme.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mvme16xhw.h>

बाह्य t_bdid mvme_bdid;

अटल MK48T08ptr_t अस्थिर rtc = (MK48T08ptr_t)MVME_RTC_BASE;

अटल व्योम mvme16x_get_model(अक्षर *model);
बाह्य व्योम mvme16x_sched_init(व्योम);
बाह्य पूर्णांक mvme16x_hwclk (पूर्णांक, काष्ठा rtc_समय *);
बाह्य व्योम mvme16x_reset (व्योम);

पूर्णांक bcd2पूर्णांक (अचिन्हित अक्षर b);


अचिन्हित लघु mvme16x_config;
EXPORT_SYMBOL(mvme16x_config);


पूर्णांक __init mvme16x_parse_bootinfo(स्थिर काष्ठा bi_record *bi)
अणु
	uपूर्णांक16_t tag = be16_to_cpu(bi->tag);
	अगर (tag == BI_VME_TYPE || tag == BI_VME_BRDINFO)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

व्योम mvme16x_reset(व्योम)
अणु
	pr_info("\r\n\nCalled mvme16x_reset\r\n"
		"\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r");
	/* The string of वापसs is to delay the reset until the whole
	 * message is output.  Assert reset bit in GCSR */
	*(अस्थिर अक्षर *)0xfff40107 = 0x80;
पूर्ण

अटल व्योम mvme16x_get_model(अक्षर *model)
अणु
    p_bdid p = &mvme_bdid;
    अक्षर suf[4];

    suf[1] = p->brdsuffix[0];
    suf[2] = p->brdsuffix[1];
    suf[3] = '\0';
    suf[0] = suf[1] ? '-' : '\0';

    प्र_लिखो(model, "Motorola MVME%x%s", be16_to_cpu(p->brdno), suf);
पूर्ण


अटल व्योम mvme16x_get_hardware_list(काष्ठा seq_file *m)
अणु
    uपूर्णांक16_t brdno = be16_to_cpu(mvme_bdid.brdno);

    अगर (brdno == 0x0162 || brdno == 0x0172)
    अणु
	अचिन्हित अक्षर rev = *(अचिन्हित अक्षर *)MVME162_VERSION_REG;

	seq_म_लिखो (m, "VMEchip2        %spresent\n",
			rev & MVME16x_CONFIG_NO_VMECHIP2 ? "NOT " : "");
	seq_म_लिखो (m, "SCSI interface  %spresent\n",
			rev & MVME16x_CONFIG_NO_SCSICHIP ? "NOT " : "");
	seq_म_लिखो (m, "Ethernet i/f    %spresent\n",
			rev & MVME16x_CONFIG_NO_ETHERNET ? "NOT " : "");
    पूर्ण
पूर्ण

/*
 * This function is called during kernel startup to initialize
 * the mvme16x IRQ handling routines.  Should probably ensure
 * that the base vectors क्रम the VMEChip2 and PCCChip2 are valid.
 */

अटल व्योम __init mvme16x_init_IRQ (व्योम)
अणु
	m68k_setup_user_पूर्णांकerrupt(VEC_USER, 192);
पूर्ण

#घोषणा PCC2CHIP   (0xfff42000)
#घोषणा PCCSCCMICR (PCC2CHIP + 0x1d)
#घोषणा PCCSCCTICR (PCC2CHIP + 0x1e)
#घोषणा PCCSCCRICR (PCC2CHIP + 0x1f)
#घोषणा PCCTPIACKR (PCC2CHIP + 0x25)

#अगर_घोषित CONFIG_EARLY_PRINTK

/**** cd2401 रेजिस्टरs ****/
#घोषणा CD2401_ADDR	(0xfff45000)

#घोषणा CyGFRCR         (0x81)
#घोषणा CyCCR		(0x13)
#घोषणा      CyCLR_CHAN		(0x40)
#घोषणा      CyINIT_CHAN	(0x20)
#घोषणा      CyCHIP_RESET	(0x10)
#घोषणा      CyENB_XMTR		(0x08)
#घोषणा      CyDIS_XMTR		(0x04)
#घोषणा      CyENB_RCVR		(0x02)
#घोषणा      CyDIS_RCVR		(0x01)
#घोषणा CyCAR		(0xee)
#घोषणा CyIER		(0x11)
#घोषणा      CyMdmCh		(0x80)
#घोषणा      CyRxExc		(0x20)
#घोषणा      CyRxData		(0x08)
#घोषणा      CyTxMpty		(0x02)
#घोषणा      CyTxRdy		(0x01)
#घोषणा CyLICR		(0x26)
#घोषणा CyRISR		(0x89)
#घोषणा      CyTIMEOUT		(0x80)
#घोषणा      CySPECHAR		(0x70)
#घोषणा      CyOVERRUN		(0x08)
#घोषणा      CyPARITY		(0x04)
#घोषणा      CyFRAME		(0x02)
#घोषणा      CyBREAK		(0x01)
#घोषणा CyREOIR		(0x84)
#घोषणा CyTEOIR		(0x85)
#घोषणा CyMEOIR		(0x86)
#घोषणा      CyNOTRANS		(0x08)
#घोषणा CyRFOC		(0x30)
#घोषणा CyRDR		(0xf8)
#घोषणा CyTDR		(0xf8)
#घोषणा CyMISR		(0x8b)
#घोषणा CyRISR		(0x89)
#घोषणा CyTISR		(0x8a)
#घोषणा CyMSVR1		(0xde)
#घोषणा CyMSVR2		(0xdf)
#घोषणा      CyDSR		(0x80)
#घोषणा      CyDCD		(0x40)
#घोषणा      CyCTS		(0x20)
#घोषणा      CyDTR		(0x02)
#घोषणा      CyRTS		(0x01)
#घोषणा CyRTPRL		(0x25)
#घोषणा CyRTPRH		(0x24)
#घोषणा CyCOR1		(0x10)
#घोषणा      CyPARITY_NONE	(0x00)
#घोषणा      CyPARITY_E		(0x40)
#घोषणा      CyPARITY_O		(0xC0)
#घोषणा      Cy_5_BITS		(0x04)
#घोषणा      Cy_6_BITS		(0x05)
#घोषणा      Cy_7_BITS		(0x06)
#घोषणा      Cy_8_BITS		(0x07)
#घोषणा CyCOR2		(0x17)
#घोषणा      CyETC		(0x20)
#घोषणा      CyCtsAE		(0x02)
#घोषणा CyCOR3		(0x16)
#घोषणा      Cy_1_STOP		(0x02)
#घोषणा      Cy_2_STOP		(0x04)
#घोषणा CyCOR4		(0x15)
#घोषणा      CyREC_FIFO		(0x0F)  /* Receive FIFO threshold */
#घोषणा CyCOR5		(0x14)
#घोषणा CyCOR6		(0x18)
#घोषणा CyCOR7		(0x07)
#घोषणा CyRBPR		(0xcb)
#घोषणा CyRCOR		(0xc8)
#घोषणा CyTBPR		(0xc3)
#घोषणा CyTCOR		(0xc0)
#घोषणा CySCHR1		(0x1f)
#घोषणा CySCHR2 	(0x1e)
#घोषणा CyTPR		(0xda)
#घोषणा CyPILR1		(0xe3)
#घोषणा CyPILR2		(0xe0)
#घोषणा CyPILR3		(0xe1)
#घोषणा CyCMR		(0x1b)
#घोषणा      CyASYNC		(0x02)
#घोषणा CyLICR          (0x26)
#घोषणा CyLIVR          (0x09)
#घोषणा CySCRL		(0x23)
#घोषणा CySCRH		(0x22)
#घोषणा CyTFTC		(0x80)

व्योम mvme16x_cons_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *str, अचिन्हित count)
अणु
	अस्थिर अचिन्हित अक्षर *base_addr = (u_अक्षर *)CD2401_ADDR;
	अस्थिर u_अक्षर sink;
	u_अक्षर ier;
	पूर्णांक port;
	u_अक्षर करो_lf = 0;
	पूर्णांक i = 0;

	/* Ensure transmitter is enabled! */

	port = 0;
	base_addr[CyCAR] = (u_अक्षर)port;
	जबतक (base_addr[CyCCR])
		;
	base_addr[CyCCR] = CyENB_XMTR;

	ier = base_addr[CyIER];
	base_addr[CyIER] = CyTxMpty;

	जबतक (1) अणु
		अगर (in_8(PCCSCCTICR) & 0x20)
		अणु
			/* We have a Tx पूर्णांक. Acknowledge it */
			sink = in_8(PCCTPIACKR);
			अगर ((base_addr[CyLICR] >> 2) == port) अणु
				अगर (i == count) अणु
					/* Last अक्षर of string is now output */
					base_addr[CyTEOIR] = CyNOTRANS;
					अवरोध;
				पूर्ण
				अगर (करो_lf) अणु
					base_addr[CyTDR] = '\n';
					str++;
					i++;
					करो_lf = 0;
				पूर्ण
				अन्यथा अगर (*str == '\n') अणु
					base_addr[CyTDR] = '\r';
					करो_lf = 1;
				पूर्ण
				अन्यथा अणु
					base_addr[CyTDR] = *str++;
					i++;
				पूर्ण
				base_addr[CyTEOIR] = 0;
			पूर्ण
			अन्यथा
				base_addr[CyTEOIR] = CyNOTRANS;
		पूर्ण
	पूर्ण

	base_addr[CyIER] = ier;
पूर्ण

#पूर्ण_अगर

व्योम __init config_mvme16x(व्योम)
अणु
    p_bdid p = &mvme_bdid;
    अक्षर id[40];
    uपूर्णांक16_t brdno = be16_to_cpu(p->brdno);

    mach_sched_init      = mvme16x_sched_init;
    mach_init_IRQ        = mvme16x_init_IRQ;
    mach_hwclk           = mvme16x_hwclk;
    mach_reset		 = mvme16x_reset;
    mach_get_model       = mvme16x_get_model;
    mach_get_hardware_list = mvme16x_get_hardware_list;

    /* Report board revision */

    अगर (म_भेदन("BDID", p->bdid, 4))
    अणु
	pr_crit("Bug call .BRD_ID returned garbage - giving up\n");
	जबतक (1)
		;
    पूर्ण
    /* Board type is only set by newer versions of vmelilo/tftplilo */
    अगर (vme_brdtype == 0)
	vme_brdtype = brdno;

    mvme16x_get_model(id);
    pr_info("BRD_ID: %s   BUG %x.%x %02x/%02x/%02x\n", id, p->rev >> 4,
	    p->rev & 0xf, p->yr, p->mth, p->day);
    अगर (brdno == 0x0162 || brdno == 0x172)
    अणु
	अचिन्हित अक्षर rev = *(अचिन्हित अक्षर *)MVME162_VERSION_REG;

	mvme16x_config = rev | MVME16x_CONFIG_GOT_SCCA;

	pr_info("MVME%x Hardware status:\n", brdno);
	pr_info("    CPU Type           68%s040\n",
		rev & MVME16x_CONFIG_GOT_FPU ? "" : "LC");
	pr_info("    CPU clock          %dMHz\n",
		rev & MVME16x_CONFIG_SPEED_32 ? 32 : 25);
	pr_info("    VMEchip2           %spresent\n",
		rev & MVME16x_CONFIG_NO_VMECHIP2 ? "NOT " : "");
	pr_info("    SCSI interface     %spresent\n",
		rev & MVME16x_CONFIG_NO_SCSICHIP ? "NOT " : "");
	pr_info("    Ethernet interface %spresent\n",
		rev & MVME16x_CONFIG_NO_ETHERNET ? "NOT " : "");
    पूर्ण
    अन्यथा
    अणु
	mvme16x_config = MVME16x_CONFIG_GOT_LP | MVME16x_CONFIG_GOT_CD2401;
    पूर्ण
पूर्ण

अटल irqवापस_t mvme16x_पात_पूर्णांक (पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ *new = (अचिन्हित दीर्घ *)vectors;
	अचिन्हित दीर्घ *old = (अचिन्हित दीर्घ *)0xffe00000;
	अस्थिर अचिन्हित अक्षर uc, *ucp;
	uपूर्णांक16_t brdno = be16_to_cpu(mvme_bdid.brdno);

	अगर (brdno == 0x0162 || brdno == 0x172)
	अणु
		ucp = (अस्थिर अचिन्हित अक्षर *)0xfff42043;
		uc = *ucp | 8;
		*ucp = uc;
	पूर्ण
	अन्यथा
	अणु
		*(अस्थिर अचिन्हित दीर्घ *)0xfff40074 = 0x40000000;
	पूर्ण
	*(new+4) = *(old+4);		/* Illegal inकाष्ठाion */
	*(new+9) = *(old+9);		/* Trace */
	*(new+47) = *(old+47);		/* Trap #15 */

	अगर (brdno == 0x0162 || brdno == 0x172)
		*(new+0x5e) = *(old+0x5e);	/* ABORT चयन */
	अन्यथा
		*(new+0x6e) = *(old+0x6e);	/* ABORT चयन */
	वापस IRQ_HANDLED;
पूर्ण

अटल u64 mvme16x_पढ़ो_clk(काष्ठा घड़ीsource *cs);

अटल काष्ठा घड़ीsource mvme16x_clk = अणु
	.name   = "pcc",
	.rating = 250,
	.पढ़ो   = mvme16x_पढ़ो_clk,
	.mask   = CLOCKSOURCE_MASK(32),
	.flags  = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u32 clk_total;

#घोषणा PCC_TIMER_CLOCK_FREQ 1000000
#घोषणा PCC_TIMER_CYCLES     (PCC_TIMER_CLOCK_FREQ / HZ)

#घोषणा PCCTCMP1             (PCC2CHIP + 0x04)
#घोषणा PCCTCNT1             (PCC2CHIP + 0x08)
#घोषणा PCCTOVR1             (PCC2CHIP + 0x17)
#घोषणा PCCTIC1              (PCC2CHIP + 0x1b)

#घोषणा PCCTOVR1_TIC_EN      0x01
#घोषणा PCCTOVR1_COC_EN      0x02
#घोषणा PCCTOVR1_OVR_CLR     0x04

#घोषणा PCCTIC1_INT_LEVEL    6
#घोषणा PCCTIC1_INT_CLR      0x08
#घोषणा PCCTIC1_INT_EN       0x10

अटल irqवापस_t mvme16x_समयr_पूर्णांक (पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	out_8(PCCTOVR1, PCCTOVR1_OVR_CLR | PCCTOVR1_TIC_EN | PCCTOVR1_COC_EN);
	out_8(PCCTIC1, PCCTIC1_INT_EN | PCCTIC1_INT_CLR | PCCTIC1_INT_LEVEL);
	clk_total += PCC_TIMER_CYCLES;
	legacy_समयr_tick(1);
	local_irq_restore(flags);

	वापस IRQ_HANDLED;
पूर्ण

व्योम mvme16x_sched_init(व्योम)
अणु
    uपूर्णांक16_t brdno = be16_to_cpu(mvme_bdid.brdno);
    पूर्णांक irq;

    /* Using PCCchip2 or MC2 chip tick समयr 1 */
    अगर (request_irq(MVME16x_IRQ_TIMER, mvme16x_समयr_पूर्णांक, IRQF_TIMER, "timer",
                    शून्य))
	panic ("Couldn't register timer int");

    out_be32(PCCTCNT1, 0);
    out_be32(PCCTCMP1, PCC_TIMER_CYCLES);
    out_8(PCCTOVR1, PCCTOVR1_OVR_CLR | PCCTOVR1_TIC_EN | PCCTOVR1_COC_EN);
    out_8(PCCTIC1, PCCTIC1_INT_EN | PCCTIC1_INT_CLR | PCCTIC1_INT_LEVEL);

    घड़ीsource_रेजिस्टर_hz(&mvme16x_clk, PCC_TIMER_CLOCK_FREQ);

    अगर (brdno == 0x0162 || brdno == 0x172)
	irq = MVME162_IRQ_ABORT;
    अन्यथा
        irq = MVME167_IRQ_ABORT;
    अगर (request_irq(irq, mvme16x_पात_पूर्णांक, 0,
				"abort", mvme16x_पात_पूर्णांक))
	panic ("Couldn't register abort int");
पूर्ण

अटल u64 mvme16x_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	u8 overflow, पंचांगp;
	u32 ticks;

	local_irq_save(flags);
	पंचांगp = in_8(PCCTOVR1) >> 4;
	ticks = in_be32(PCCTCNT1);
	overflow = in_8(PCCTOVR1) >> 4;
	अगर (overflow != पंचांगp)
		ticks = in_be32(PCCTCNT1);
	ticks += overflow * PCC_TIMER_CYCLES;
	ticks += clk_total;
	local_irq_restore(flags);

	वापस ticks;
पूर्ण

पूर्णांक bcd2पूर्णांक (अचिन्हित अक्षर b)
अणु
	वापस ((b>>4)*10 + (b&15));
पूर्ण

पूर्णांक mvme16x_hwclk(पूर्णांक op, काष्ठा rtc_समय *t)
अणु
#warning check me!
	अगर (!op) अणु
		rtc->ctrl = RTC_READ;
		t->पंचांग_year = bcd2पूर्णांक (rtc->bcd_year);
		t->पंचांग_mon  = bcd2पूर्णांक(rtc->bcd_mth) - 1;
		t->पंचांग_mday = bcd2पूर्णांक (rtc->bcd_करोm);
		t->पंचांग_hour = bcd2पूर्णांक (rtc->bcd_hr);
		t->पंचांग_min  = bcd2पूर्णांक (rtc->bcd_min);
		t->पंचांग_sec  = bcd2पूर्णांक (rtc->bcd_sec);
		rtc->ctrl = 0;
		अगर (t->पंचांग_year < 70)
			t->पंचांग_year += 100;
	पूर्ण
	वापस 0;
पूर्ण
