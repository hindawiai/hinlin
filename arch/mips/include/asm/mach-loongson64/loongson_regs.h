<शैली गुरु>
/*
 * Read/Write Loongson Extension Registers
 */

#अगर_अघोषित _LOONGSON_REGS_H_
#घोषणा _LOONGSON_REGS_H_

#समावेश <linux/types.h>
#समावेश <linux/bits.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/cpu.h>

अटल अंतरभूत bool cpu_has_cfg(व्योम)
अणु
	वापस ((पढ़ो_c0_prid() & PRID_IMP_MASK) == PRID_IMP_LOONGSON_64G);
पूर्ण

अटल अंतरभूत u32 पढ़ो_cpucfg(u32 reg)
अणु
	u32 __res;

	__यंत्र__ __अस्थिर__(
		"parse_r __res,%0\n\t"
		"parse_r reg,%1\n\t"
		".insn \n\t"
		".word (0xc8080118 | (reg << 21) | (__res << 11))\n\t"
		:"=r"(__res)
		:"r"(reg)
		:
		);
	वापस __res;
पूर्ण

/* Bit Doमुख्यs क्रम CFG रेजिस्टरs */
#घोषणा LOONGSON_CFG0	0x0
#घोषणा LOONGSON_CFG0_PRID GENMASK(31, 0)

#घोषणा LOONGSON_CFG1 0x1
#घोषणा LOONGSON_CFG1_FP	BIT(0)
#घोषणा LOONGSON_CFG1_FPREV	GENMASK(3, 1)
#घोषणा LOONGSON_CFG1_MMI	BIT(4)
#घोषणा LOONGSON_CFG1_MSA1	BIT(5)
#घोषणा LOONGSON_CFG1_MSA2	BIT(6)
#घोषणा LOONGSON_CFG1_CGP	BIT(7)
#घोषणा LOONGSON_CFG1_WRP	BIT(8)
#घोषणा LOONGSON_CFG1_LSX1	BIT(9)
#घोषणा LOONGSON_CFG1_LSX2	BIT(10)
#घोषणा LOONGSON_CFG1_LASX	BIT(11)
#घोषणा LOONGSON_CFG1_R6FXP	BIT(12)
#घोषणा LOONGSON_CFG1_R6CRCP	BIT(13)
#घोषणा LOONGSON_CFG1_R6FPP	BIT(14)
#घोषणा LOONGSON_CFG1_CNT64	BIT(15)
#घोषणा LOONGSON_CFG1_LSLDR0	BIT(16)
#घोषणा LOONGSON_CFG1_LSPREF	BIT(17)
#घोषणा LOONGSON_CFG1_LSPREFX	BIT(18)
#घोषणा LOONGSON_CFG1_LSSYNCI	BIT(19)
#घोषणा LOONGSON_CFG1_LSUCA	BIT(20)
#घोषणा LOONGSON_CFG1_LLSYNC	BIT(21)
#घोषणा LOONGSON_CFG1_TGTSYNC	BIT(22)
#घोषणा LOONGSON_CFG1_LLEXC	BIT(23)
#घोषणा LOONGSON_CFG1_SCRAND	BIT(24)
#घोषणा LOONGSON_CFG1_MUALP	BIT(25)
#घोषणा LOONGSON_CFG1_KMUALEN	BIT(26)
#घोषणा LOONGSON_CFG1_ITLBT	BIT(27)
#घोषणा LOONGSON_CFG1_LSUPERF	BIT(28)
#घोषणा LOONGSON_CFG1_SFBP	BIT(29)
#घोषणा LOONGSON_CFG1_CDMAP	BIT(30)

#घोषणा LOONGSON_CFG1_FPREV_OFFSET	1

#घोषणा LOONGSON_CFG2 0x2
#घोषणा LOONGSON_CFG2_LEXT1	BIT(0)
#घोषणा LOONGSON_CFG2_LEXT2	BIT(1)
#घोषणा LOONGSON_CFG2_LEXT3	BIT(2)
#घोषणा LOONGSON_CFG2_LSPW	BIT(3)
#घोषणा LOONGSON_CFG2_LBT1	BIT(4)
#घोषणा LOONGSON_CFG2_LBT2	BIT(5)
#घोषणा LOONGSON_CFG2_LBT3	BIT(6)
#घोषणा LOONGSON_CFG2_LBTMMU	BIT(7)
#घोषणा LOONGSON_CFG2_LPMP	BIT(8)
#घोषणा LOONGSON_CFG2_LPMREV	GENMASK(11, 9)
#घोषणा LOONGSON_CFG2_LAMO	BIT(12)
#घोषणा LOONGSON_CFG2_LPIXU	BIT(13)
#घोषणा LOONGSON_CFG2_LPIXNU	BIT(14)
#घोषणा LOONGSON_CFG2_LVZP	BIT(15)
#घोषणा LOONGSON_CFG2_LVZREV	GENMASK(18, 16)
#घोषणा LOONGSON_CFG2_LGFTP	BIT(19)
#घोषणा LOONGSON_CFG2_LGFTPREV	GENMASK(22, 20)
#घोषणा LOONGSON_CFG2_LLFTP	BIT(23)
#घोषणा LOONGSON_CFG2_LLFTPREV	GENMASK(26, 24)
#घोषणा LOONGSON_CFG2_LCSRP	BIT(27)
#घोषणा LOONGSON_CFG2_LDISBLIKELY	BIT(28)

#घोषणा LOONGSON_CFG2_LPMREV_OFFSET	9
#घोषणा LOONGSON_CFG2_LPM_REV1		(1 << LOONGSON_CFG2_LPMREV_OFFSET)
#घोषणा LOONGSON_CFG2_LPM_REV2		(2 << LOONGSON_CFG2_LPMREV_OFFSET)
#घोषणा LOONGSON_CFG2_LVZREV_OFFSET	16
#घोषणा LOONGSON_CFG2_LVZ_REV1		(1 << LOONGSON_CFG2_LVZREV_OFFSET)
#घोषणा LOONGSON_CFG2_LVZ_REV2		(2 << LOONGSON_CFG2_LVZREV_OFFSET)

#घोषणा LOONGSON_CFG3 0x3
#घोषणा LOONGSON_CFG3_LCAMP	BIT(0)
#घोषणा LOONGSON_CFG3_LCAMREV	GENMASK(3, 1)
#घोषणा LOONGSON_CFG3_LCAMNUM	GENMASK(11, 4)
#घोषणा LOONGSON_CFG3_LCAMKW	GENMASK(19, 12)
#घोषणा LOONGSON_CFG3_LCAMVW	GENMASK(27, 20)

#घोषणा LOONGSON_CFG3_LCAMREV_OFFSET	1
#घोषणा LOONGSON_CFG3_LCAM_REV1		(1 << LOONGSON_CFG3_LCAMREV_OFFSET)
#घोषणा LOONGSON_CFG3_LCAM_REV2		(2 << LOONGSON_CFG3_LCAMREV_OFFSET)
#घोषणा LOONGSON_CFG3_LCAMNUM_OFFSET	4
#घोषणा LOONGSON_CFG3_LCAMNUM_REV1	(0x3f << LOONGSON_CFG3_LCAMNUM_OFFSET)
#घोषणा LOONGSON_CFG3_LCAMKW_OFFSET	12
#घोषणा LOONGSON_CFG3_LCAMKW_REV1	(0x27 << LOONGSON_CFG3_LCAMKW_OFFSET)
#घोषणा LOONGSON_CFG3_LCAMVW_OFFSET	20
#घोषणा LOONGSON_CFG3_LCAMVW_REV1	(0x3f << LOONGSON_CFG3_LCAMVW_OFFSET)

#घोषणा LOONGSON_CFG4 0x4
#घोषणा LOONGSON_CFG4_CCFREQ	GENMASK(31, 0)

#घोषणा LOONGSON_CFG5 0x5
#घोषणा LOONGSON_CFG5_CFM	GENMASK(15, 0)
#घोषणा LOONGSON_CFG5_CFD	GENMASK(31, 16)

#घोषणा LOONGSON_CFG6 0x6

#घोषणा LOONGSON_CFG7 0x7
#घोषणा LOONGSON_CFG7_GCCAEQRP	BIT(0)
#घोषणा LOONGSON_CFG7_UCAWINP	BIT(1)

अटल अंतरभूत bool cpu_has_csr(व्योम)
अणु
	अगर (cpu_has_cfg())
		वापस (पढ़ो_cpucfg(LOONGSON_CFG2) & LOONGSON_CFG2_LCSRP);

	वापस false;
पूर्ण

अटल अंतरभूत u32 csr_पढ़ोl(u32 reg)
अणु
	u32 __res;

	/* RDCSR reg, val */
	__यंत्र__ __अस्थिर__(
		"parse_r __res,%0\n\t"
		"parse_r reg,%1\n\t"
		".insn \n\t"
		".word (0xc8000118 | (reg << 21) | (__res << 11))\n\t"
		:"=r"(__res)
		:"r"(reg)
		:
		);
	वापस __res;
पूर्ण

अटल अंतरभूत u64 csr_पढ़ोq(u32 reg)
अणु
	u64 __res;

	/* DRDCSR reg, val */
	__यंत्र__ __अस्थिर__(
		"parse_r __res,%0\n\t"
		"parse_r reg,%1\n\t"
		".insn \n\t"
		".word (0xc8020118 | (reg << 21) | (__res << 11))\n\t"
		:"=r"(__res)
		:"r"(reg)
		:
		);
	वापस __res;
पूर्ण

अटल अंतरभूत व्योम csr_ग_लिखोl(u32 val, u32 reg)
अणु
	/* WRCSR reg, val */
	__यंत्र__ __अस्थिर__(
		"parse_r reg,%0\n\t"
		"parse_r val,%1\n\t"
		".insn \n\t"
		".word (0xc8010118 | (reg << 21) | (val << 11))\n\t"
		:
		:"r"(reg),"r"(val)
		:
		);
पूर्ण

अटल अंतरभूत व्योम csr_ग_लिखोq(u64 val, u32 reg)
अणु
	/* DWRCSR reg, val */
	__यंत्र__ __अस्थिर__(
		"parse_r reg,%0\n\t"
		"parse_r val,%1\n\t"
		".insn \n\t"
		".word (0xc8030118 | (reg << 21) | (val << 11))\n\t"
		:
		:"r"(reg),"r"(val)
		:
		);
पूर्ण

/* Public CSR Register can also be accessed with regular addresses */
#घोषणा CSR_PUBLIC_MMIO_BASE 0x1fe00000

#घोषणा MMIO_CSR(x)		(व्योम *)TO_UNCAC(CSR_PUBLIC_MMIO_BASE + x)

#घोषणा LOONGSON_CSR_FEATURES	0x8
#घोषणा LOONGSON_CSRF_TEMP	BIT(0)
#घोषणा LOONGSON_CSRF_NODECNT	BIT(1)
#घोषणा LOONGSON_CSRF_MSI	BIT(2)
#घोषणा LOONGSON_CSRF_EXTIOI	BIT(3)
#घोषणा LOONGSON_CSRF_IPI	BIT(4)
#घोषणा LOONGSON_CSRF_FREQ	BIT(5)

#घोषणा LOONGSON_CSR_VENDOR	0x10 /* Venकरोr name string, should be "Loongson" */
#घोषणा LOONGSON_CSR_CPUNAME	0x20 /* Processor name string */
#घोषणा LOONGSON_CSR_NODECNT	0x408
#घोषणा LOONGSON_CSR_CPUTEMP	0x428

/* PerCore CSR, only accessable by local cores */
#घोषणा LOONGSON_CSR_IPI_STATUS	0x1000
#घोषणा LOONGSON_CSR_IPI_EN	0x1004
#घोषणा LOONGSON_CSR_IPI_SET	0x1008
#घोषणा LOONGSON_CSR_IPI_CLEAR	0x100c
#घोषणा LOONGSON_CSR_IPI_SEND	0x1040
#घोषणा CSR_IPI_SEND_IP_SHIFT	0
#घोषणा CSR_IPI_SEND_CPU_SHIFT	16
#घोषणा CSR_IPI_SEND_BLOCK	BIT(31)

#घोषणा LOONGSON_CSR_MAIL_BUF0		0x1020
#घोषणा LOONGSON_CSR_MAIL_SEND		0x1048
#घोषणा CSR_MAIL_SEND_BLOCK		BIT_ULL(31)
#घोषणा CSR_MAIL_SEND_BOX_LOW(box)	(box << 1)
#घोषणा CSR_MAIL_SEND_BOX_HIGH(box)	((box << 1) + 1)
#घोषणा CSR_MAIL_SEND_BOX_SHIFT		2
#घोषणा CSR_MAIL_SEND_CPU_SHIFT		16
#घोषणा CSR_MAIL_SEND_BUF_SHIFT		32
#घोषणा CSR_MAIL_SEND_H32_MASK		0xFFFFFFFF00000000ULL

अटल अंतरभूत u64 drdसमय(व्योम)
अणु
	पूर्णांक rID = 0;
	u64 val = 0;

	__यंत्र__ __अस्थिर__(
		"parse_r rID,%0\n\t"
		"parse_r val,%1\n\t"
		".insn \n\t"
		".word (0xc8090118 | (rID << 21) | (val << 11))\n\t"
		:"=r"(rID),"=r"(val)
		:
		);
	वापस val;
पूर्ण

#पूर्ण_अगर
