<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * NXP FlexSPI(FSPI) controller driver.
 *
 * Copyright 2019-2020 NXP
 * Copyright 2020 Puresoftware Ltd.
 *
 * FlexSPI is a flexsible SPI host controller which supports two SPI
 * channels and up to 4 बाह्यal devices. Each channel supports
 * Single/Dual/Quad/Octal mode data transfer (1/2/4/8 bidirectional
 * data lines).
 *
 * FlexSPI controller is driven by the LUT(Look-up Table) रेजिस्टरs
 * LUT रेजिस्टरs are a look-up-table क्रम sequences of inकाष्ठाions.
 * A valid sequence consists of four LUT रेजिस्टरs.
 * Maximum 32 LUT sequences can be programmed simultaneously.
 *
 * LUTs are being created at run-समय based on the commands passed
 * from the spi-mem framework, thus using single LUT index.
 *
 * Software triggered Flash पढ़ो/ग_लिखो access by IP Bus.
 *
 * Memory mapped पढ़ो access by AHB Bus.
 *
 * Based on SPI MEM पूर्णांकerface and spi-fsl-qspi.c driver.
 *
 * Author:
 *     Yogesh Narayan Gaur <yogeshnarayan.gaur@nxp.com>
 *     Boris Brezillon <bbrezillon@kernel.org>
 *     Frieder Schrempf <frieder.schrempf@kontron.de>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sizes.h>
#समावेश <linux/sys_soc.h>

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>

/*
 * The driver only uses one single LUT entry, that is updated on
 * each call of exec_op(). Index 0 is preset at boot with a basic
 * पढ़ो operation, so let's use the last entry (31).
 */
#घोषणा	SEQID_LUT			31

/* Registers used by the driver */
#घोषणा FSPI_MCR0			0x00
#घोषणा FSPI_MCR0_AHB_TIMEOUT(x)	((x) << 24)
#घोषणा FSPI_MCR0_IP_TIMEOUT(x)		((x) << 16)
#घोषणा FSPI_MCR0_LEARN_EN		BIT(15)
#घोषणा FSPI_MCR0_SCRFRUN_EN		BIT(14)
#घोषणा FSPI_MCR0_OCTCOMB_EN		BIT(13)
#घोषणा FSPI_MCR0_DOZE_EN		BIT(12)
#घोषणा FSPI_MCR0_HSEN			BIT(11)
#घोषणा FSPI_MCR0_SERCLKDIV		BIT(8)
#घोषणा FSPI_MCR0_ATDF_EN		BIT(7)
#घोषणा FSPI_MCR0_ARDF_EN		BIT(6)
#घोषणा FSPI_MCR0_RXCLKSRC(x)		((x) << 4)
#घोषणा FSPI_MCR0_END_CFG(x)		((x) << 2)
#घोषणा FSPI_MCR0_MDIS			BIT(1)
#घोषणा FSPI_MCR0_SWRST			BIT(0)

#घोषणा FSPI_MCR1			0x04
#घोषणा FSPI_MCR1_SEQ_TIMEOUT(x)	((x) << 16)
#घोषणा FSPI_MCR1_AHB_TIMEOUT(x)	(x)

#घोषणा FSPI_MCR2			0x08
#घोषणा FSPI_MCR2_IDLE_WAIT(x)		((x) << 24)
#घोषणा FSPI_MCR2_SAMEDEVICEEN		BIT(15)
#घोषणा FSPI_MCR2_CLRLRPHS		BIT(14)
#घोषणा FSPI_MCR2_ABRDATSZ		BIT(8)
#घोषणा FSPI_MCR2_ABRLEARN		BIT(7)
#घोषणा FSPI_MCR2_ABR_READ		BIT(6)
#घोषणा FSPI_MCR2_ABRWRITE		BIT(5)
#घोषणा FSPI_MCR2_ABRDUMMY		BIT(4)
#घोषणा FSPI_MCR2_ABR_MODE		BIT(3)
#घोषणा FSPI_MCR2_ABRCADDR		BIT(2)
#घोषणा FSPI_MCR2_ABRRADDR		BIT(1)
#घोषणा FSPI_MCR2_ABR_CMD		BIT(0)

#घोषणा FSPI_AHBCR			0x0c
#घोषणा FSPI_AHBCR_RDADDROPT		BIT(6)
#घोषणा FSPI_AHBCR_PREF_EN		BIT(5)
#घोषणा FSPI_AHBCR_BUFF_EN		BIT(4)
#घोषणा FSPI_AHBCR_CACH_EN		BIT(3)
#घोषणा FSPI_AHBCR_CLRTXBUF		BIT(2)
#घोषणा FSPI_AHBCR_CLRRXBUF		BIT(1)
#घोषणा FSPI_AHBCR_PAR_EN		BIT(0)

#घोषणा FSPI_INTEN			0x10
#घोषणा FSPI_INTEN_SCLKSBWR		BIT(9)
#घोषणा FSPI_INTEN_SCLKSBRD		BIT(8)
#घोषणा FSPI_INTEN_DATALRNFL		BIT(7)
#घोषणा FSPI_INTEN_IPTXWE		BIT(6)
#घोषणा FSPI_INTEN_IPRXWA		BIT(5)
#घोषणा FSPI_INTEN_AHBCMDERR		BIT(4)
#घोषणा FSPI_INTEN_IPCMDERR		BIT(3)
#घोषणा FSPI_INTEN_AHBCMDGE		BIT(2)
#घोषणा FSPI_INTEN_IPCMDGE		BIT(1)
#घोषणा FSPI_INTEN_IPCMDDONE		BIT(0)

#घोषणा FSPI_INTR			0x14
#घोषणा FSPI_INTR_SCLKSBWR		BIT(9)
#घोषणा FSPI_INTR_SCLKSBRD		BIT(8)
#घोषणा FSPI_INTR_DATALRNFL		BIT(7)
#घोषणा FSPI_INTR_IPTXWE		BIT(6)
#घोषणा FSPI_INTR_IPRXWA		BIT(5)
#घोषणा FSPI_INTR_AHBCMDERR		BIT(4)
#घोषणा FSPI_INTR_IPCMDERR		BIT(3)
#घोषणा FSPI_INTR_AHBCMDGE		BIT(2)
#घोषणा FSPI_INTR_IPCMDGE		BIT(1)
#घोषणा FSPI_INTR_IPCMDDONE		BIT(0)

#घोषणा FSPI_LUTKEY			0x18
#घोषणा FSPI_LUTKEY_VALUE		0x5AF05AF0

#घोषणा FSPI_LCKCR			0x1C

#घोषणा FSPI_LCKER_LOCK			0x1
#घोषणा FSPI_LCKER_UNLOCK		0x2

#घोषणा FSPI_BUFXCR_INVALID_MSTRID	0xE
#घोषणा FSPI_AHBRX_BUF0CR0		0x20
#घोषणा FSPI_AHBRX_BUF1CR0		0x24
#घोषणा FSPI_AHBRX_BUF2CR0		0x28
#घोषणा FSPI_AHBRX_BUF3CR0		0x2C
#घोषणा FSPI_AHBRX_BUF4CR0		0x30
#घोषणा FSPI_AHBRX_BUF5CR0		0x34
#घोषणा FSPI_AHBRX_BUF6CR0		0x38
#घोषणा FSPI_AHBRX_BUF7CR0		0x3C
#घोषणा FSPI_AHBRXBUF0CR7_PREF		BIT(31)

#घोषणा FSPI_AHBRX_BUF0CR1		0x40
#घोषणा FSPI_AHBRX_BUF1CR1		0x44
#घोषणा FSPI_AHBRX_BUF2CR1		0x48
#घोषणा FSPI_AHBRX_BUF3CR1		0x4C
#घोषणा FSPI_AHBRX_BUF4CR1		0x50
#घोषणा FSPI_AHBRX_BUF5CR1		0x54
#घोषणा FSPI_AHBRX_BUF6CR1		0x58
#घोषणा FSPI_AHBRX_BUF7CR1		0x5C

#घोषणा FSPI_FLSHA1CR0			0x60
#घोषणा FSPI_FLSHA2CR0			0x64
#घोषणा FSPI_FLSHB1CR0			0x68
#घोषणा FSPI_FLSHB2CR0			0x6C
#घोषणा FSPI_FLSHXCR0_SZ_KB		10
#घोषणा FSPI_FLSHXCR0_SZ(x)		((x) >> FSPI_FLSHXCR0_SZ_KB)

#घोषणा FSPI_FLSHA1CR1			0x70
#घोषणा FSPI_FLSHA2CR1			0x74
#घोषणा FSPI_FLSHB1CR1			0x78
#घोषणा FSPI_FLSHB2CR1			0x7C
#घोषणा FSPI_FLSHXCR1_CSINTR(x)		((x) << 16)
#घोषणा FSPI_FLSHXCR1_CAS(x)		((x) << 11)
#घोषणा FSPI_FLSHXCR1_WA		BIT(10)
#घोषणा FSPI_FLSHXCR1_TCSH(x)		((x) << 5)
#घोषणा FSPI_FLSHXCR1_TCSS(x)		(x)

#घोषणा FSPI_FLSHA1CR2			0x80
#घोषणा FSPI_FLSHA2CR2			0x84
#घोषणा FSPI_FLSHB1CR2			0x88
#घोषणा FSPI_FLSHB2CR2			0x8C
#घोषणा FSPI_FLSHXCR2_CLRINSP		BIT(24)
#घोषणा FSPI_FLSHXCR2_AWRWAIT		BIT(16)
#घोषणा FSPI_FLSHXCR2_AWRSEQN_SHIFT	13
#घोषणा FSPI_FLSHXCR2_AWRSEQI_SHIFT	8
#घोषणा FSPI_FLSHXCR2_ARDSEQN_SHIFT	5
#घोषणा FSPI_FLSHXCR2_ARDSEQI_SHIFT	0

#घोषणा FSPI_IPCR0			0xA0

#घोषणा FSPI_IPCR1			0xA4
#घोषणा FSPI_IPCR1_IPAREN		BIT(31)
#घोषणा FSPI_IPCR1_SEQNUM_SHIFT		24
#घोषणा FSPI_IPCR1_SEQID_SHIFT		16
#घोषणा FSPI_IPCR1_IDATSZ(x)		(x)

#घोषणा FSPI_IPCMD			0xB0
#घोषणा FSPI_IPCMD_TRG			BIT(0)

#घोषणा FSPI_DLPR			0xB4

#घोषणा FSPI_IPRXFCR			0xB8
#घोषणा FSPI_IPRXFCR_CLR		BIT(0)
#घोषणा FSPI_IPRXFCR_DMA_EN		BIT(1)
#घोषणा FSPI_IPRXFCR_WMRK(x)		((x) << 2)

#घोषणा FSPI_IPTXFCR			0xBC
#घोषणा FSPI_IPTXFCR_CLR		BIT(0)
#घोषणा FSPI_IPTXFCR_DMA_EN		BIT(1)
#घोषणा FSPI_IPTXFCR_WMRK(x)		((x) << 2)

#घोषणा FSPI_DLLACR			0xC0
#घोषणा FSPI_DLLACR_OVRDEN		BIT(8)

#घोषणा FSPI_DLLBCR			0xC4
#घोषणा FSPI_DLLBCR_OVRDEN		BIT(8)

#घोषणा FSPI_STS0			0xE0
#घोषणा FSPI_STS0_DLPHB(x)		((x) << 8)
#घोषणा FSPI_STS0_DLPHA(x)		((x) << 4)
#घोषणा FSPI_STS0_CMD_SRC(x)		((x) << 2)
#घोषणा FSPI_STS0_ARB_IDLE		BIT(1)
#घोषणा FSPI_STS0_SEQ_IDLE		BIT(0)

#घोषणा FSPI_STS1			0xE4
#घोषणा FSPI_STS1_IP_ERRCD(x)		((x) << 24)
#घोषणा FSPI_STS1_IP_ERRID(x)		((x) << 16)
#घोषणा FSPI_STS1_AHB_ERRCD(x)		((x) << 8)
#घोषणा FSPI_STS1_AHB_ERRID(x)		(x)

#घोषणा FSPI_AHBSPNST			0xEC
#घोषणा FSPI_AHBSPNST_DATLFT(x)		((x) << 16)
#घोषणा FSPI_AHBSPNST_BUFID(x)		((x) << 1)
#घोषणा FSPI_AHBSPNST_ACTIVE		BIT(0)

#घोषणा FSPI_IPRXFSTS			0xF0
#घोषणा FSPI_IPRXFSTS_RDCNTR(x)		((x) << 16)
#घोषणा FSPI_IPRXFSTS_FILL(x)		(x)

#घोषणा FSPI_IPTXFSTS			0xF4
#घोषणा FSPI_IPTXFSTS_WRCNTR(x)		((x) << 16)
#घोषणा FSPI_IPTXFSTS_FILL(x)		(x)

#घोषणा FSPI_RFDR			0x100
#घोषणा FSPI_TFDR			0x180

#घोषणा FSPI_LUT_BASE			0x200
#घोषणा FSPI_LUT_OFFSET			(SEQID_LUT * 4 * 4)
#घोषणा FSPI_LUT_REG(idx) \
	(FSPI_LUT_BASE + FSPI_LUT_OFFSET + (idx) * 4)

/* रेजिस्टर map end */

/* Inकाष्ठाion set क्रम the LUT रेजिस्टर. */
#घोषणा LUT_STOP			0x00
#घोषणा LUT_CMD				0x01
#घोषणा LUT_ADDR			0x02
#घोषणा LUT_CADDR_SDR			0x03
#घोषणा LUT_MODE			0x04
#घोषणा LUT_MODE2			0x05
#घोषणा LUT_MODE4			0x06
#घोषणा LUT_MODE8			0x07
#घोषणा LUT_NXP_WRITE			0x08
#घोषणा LUT_NXP_READ			0x09
#घोषणा LUT_LEARN_SDR			0x0A
#घोषणा LUT_DATSZ_SDR			0x0B
#घोषणा LUT_DUMMY			0x0C
#घोषणा LUT_DUMMY_RWDS_SDR		0x0D
#घोषणा LUT_JMP_ON_CS			0x1F
#घोषणा LUT_CMD_DDR			0x21
#घोषणा LUT_ADDR_DDR			0x22
#घोषणा LUT_CADDR_DDR			0x23
#घोषणा LUT_MODE_DDR			0x24
#घोषणा LUT_MODE2_DDR			0x25
#घोषणा LUT_MODE4_DDR			0x26
#घोषणा LUT_MODE8_DDR			0x27
#घोषणा LUT_WRITE_DDR			0x28
#घोषणा LUT_READ_DDR			0x29
#घोषणा LUT_LEARN_DDR			0x2A
#घोषणा LUT_DATSZ_DDR			0x2B
#घोषणा LUT_DUMMY_DDR			0x2C
#घोषणा LUT_DUMMY_RWDS_DDR		0x2D

/*
 * Calculate number of required PAD bits क्रम LUT रेजिस्टर.
 *
 * The pad stands क्रम the number of IO lines [0:7].
 * For example, the octal पढ़ो needs eight IO lines,
 * so you should use LUT_PAD(8). This macro
 * वापसs 3 i.e. use eight (2^3) IP lines क्रम पढ़ो.
 */
#घोषणा LUT_PAD(x) (fls(x) - 1)

/*
 * Macro क्रम स्थिरructing the LUT entries with the following
 * रेजिस्टर layout:
 *
 *  ---------------------------------------------------
 *  | INSTR1 | PAD1 | OPRND1 | INSTR0 | PAD0 | OPRND0 |
 *  ---------------------------------------------------
 */
#घोषणा PAD_SHIFT		8
#घोषणा INSTR_SHIFT		10
#घोषणा OPRND_SHIFT		16

/* Macros क्रम स्थिरructing the LUT रेजिस्टर. */
#घोषणा LUT_DEF(idx, ins, pad, opr)			  \
	((((ins) << INSTR_SHIFT) | ((pad) << PAD_SHIFT) | \
	(opr)) << (((idx) % 2) * OPRND_SHIFT))

#घोषणा POLL_TOUT		5000
#घोषणा NXP_FSPI_MAX_CHIPSELECT		4
#घोषणा NXP_FSPI_MIN_IOMAP	SZ_4M

#घोषणा DCFG_RCWSR1		0x100

/* Access flash memory using IP bus only */
#घोषणा FSPI_QUIRK_USE_IP_ONLY	BIT(0)

काष्ठा nxp_fspi_devtype_data अणु
	अचिन्हित पूर्णांक rxfअगरo;
	अचिन्हित पूर्णांक txfअगरo;
	अचिन्हित पूर्णांक ahb_buf_size;
	अचिन्हित पूर्णांक quirks;
	bool little_endian;
पूर्ण;

अटल काष्ठा nxp_fspi_devtype_data lx2160a_data = अणु
	.rxfअगरo = SZ_512,       /* (64  * 64 bits)  */
	.txfअगरo = SZ_1K,        /* (128 * 64 bits)  */
	.ahb_buf_size = SZ_2K,  /* (256 * 64 bits)  */
	.quirks = 0,
	.little_endian = true,  /* little-endian    */
पूर्ण;

अटल काष्ठा nxp_fspi_devtype_data imx8mm_data = अणु
	.rxfअगरo = SZ_512,       /* (64  * 64 bits)  */
	.txfअगरo = SZ_1K,        /* (128 * 64 bits)  */
	.ahb_buf_size = SZ_2K,  /* (256 * 64 bits)  */
	.quirks = 0,
	.little_endian = true,  /* little-endian    */
पूर्ण;

अटल काष्ठा nxp_fspi_devtype_data imx8qxp_data = अणु
	.rxfअगरo = SZ_512,       /* (64  * 64 bits)  */
	.txfअगरo = SZ_1K,        /* (128 * 64 bits)  */
	.ahb_buf_size = SZ_2K,  /* (256 * 64 bits)  */
	.quirks = 0,
	.little_endian = true,  /* little-endian    */
पूर्ण;

अटल काष्ठा nxp_fspi_devtype_data imx8dxl_data = अणु
	.rxfअगरo = SZ_512,       /* (64  * 64 bits)  */
	.txfअगरo = SZ_1K,        /* (128 * 64 bits)  */
	.ahb_buf_size = SZ_2K,  /* (256 * 64 bits)  */
	.quirks = FSPI_QUIRK_USE_IP_ONLY,
	.little_endian = true,  /* little-endian    */
पूर्ण;

काष्ठा nxp_fspi अणु
	व्योम __iomem *iobase;
	व्योम __iomem *ahb_addr;
	u32 memmap_phy;
	u32 memmap_phy_size;
	u32 memmap_start;
	u32 memmap_len;
	काष्ठा clk *clk, *clk_en;
	काष्ठा device *dev;
	काष्ठा completion c;
	काष्ठा nxp_fspi_devtype_data *devtype_data;
	काष्ठा mutex lock;
	काष्ठा pm_qos_request pm_qos_req;
	पूर्णांक selected;
पूर्ण;

अटल अंतरभूत पूर्णांक needs_ip_only(काष्ठा nxp_fspi *f)
अणु
	वापस f->devtype_data->quirks & FSPI_QUIRK_USE_IP_ONLY;
पूर्ण

/*
 * R/W functions क्रम big- or little-endian रेजिस्टरs:
 * The FSPI controller's endianness is independent of
 * the CPU core's endianness. So far, although the CPU
 * core is little-endian the FSPI controller can use
 * big-endian or little-endian.
 */
अटल व्योम fspi_ग_लिखोl(काष्ठा nxp_fspi *f, u32 val, व्योम __iomem *addr)
अणु
	अगर (f->devtype_data->little_endian)
		ioग_लिखो32(val, addr);
	अन्यथा
		ioग_लिखो32be(val, addr);
पूर्ण

अटल u32 fspi_पढ़ोl(काष्ठा nxp_fspi *f, व्योम __iomem *addr)
अणु
	अगर (f->devtype_data->little_endian)
		वापस ioपढ़ो32(addr);
	अन्यथा
		वापस ioपढ़ो32be(addr);
पूर्ण

अटल irqवापस_t nxp_fspi_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा nxp_fspi *f = dev_id;
	u32 reg;

	/* clear पूर्णांकerrupt */
	reg = fspi_पढ़ोl(f, f->iobase + FSPI_INTR);
	fspi_ग_लिखोl(f, FSPI_INTR_IPCMDDONE, f->iobase + FSPI_INTR);

	अगर (reg & FSPI_INTR_IPCMDDONE)
		complete(&f->c);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक nxp_fspi_check_buswidth(काष्ठा nxp_fspi *f, u8 width)
अणु
	चयन (width) अणु
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल bool nxp_fspi_supports_op(काष्ठा spi_mem *mem,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा nxp_fspi *f = spi_controller_get_devdata(mem->spi->master);
	पूर्णांक ret;

	ret = nxp_fspi_check_buswidth(f, op->cmd.buswidth);

	अगर (op->addr.nbytes)
		ret |= nxp_fspi_check_buswidth(f, op->addr.buswidth);

	अगर (op->dummy.nbytes)
		ret |= nxp_fspi_check_buswidth(f, op->dummy.buswidth);

	अगर (op->data.nbytes)
		ret |= nxp_fspi_check_buswidth(f, op->data.buswidth);

	अगर (ret)
		वापस false;

	/*
	 * The number of address bytes should be equal to or less than 4 bytes.
	 */
	अगर (op->addr.nbytes > 4)
		वापस false;

	/*
	 * If requested address value is greater than controller asचिन्हित
	 * memory mapped space, वापस error as it didn't fit in the range
	 * of asचिन्हित address space.
	 */
	अगर (op->addr.val >= f->memmap_phy_size)
		वापस false;

	/* Max 64 dummy घड़ी cycles supported */
	अगर (op->dummy.buswidth &&
	    (op->dummy.nbytes * 8 / op->dummy.buswidth > 64))
		वापस false;

	/* Max data length, check controller limits and alignment */
	अगर (op->data.dir == SPI_MEM_DATA_IN &&
	    (op->data.nbytes > f->devtype_data->ahb_buf_size ||
	     (op->data.nbytes > f->devtype_data->rxfअगरo - 4 &&
	      !IS_ALIGNED(op->data.nbytes, 8))))
		वापस false;

	अगर (op->data.dir == SPI_MEM_DATA_OUT &&
	    op->data.nbytes > f->devtype_data->txfअगरo)
		वापस false;

	वापस spi_mem_शेष_supports_op(mem, op);
पूर्ण

/* Instead of busy looping invoke पढ़ोl_poll_समयout functionality. */
अटल पूर्णांक fspi_पढ़ोl_poll_tout(काष्ठा nxp_fspi *f, व्योम __iomem *base,
				u32 mask, u32 delay_us,
				u32 समयout_us, bool c)
अणु
	u32 reg;

	अगर (!f->devtype_data->little_endian)
		mask = (u32)cpu_to_be32(mask);

	अगर (c)
		वापस पढ़ोl_poll_समयout(base, reg, (reg & mask),
					  delay_us, समयout_us);
	अन्यथा
		वापस पढ़ोl_poll_समयout(base, reg, !(reg & mask),
					  delay_us, समयout_us);
पूर्ण

/*
 * If the slave device content being changed by Write/Erase, need to
 * invalidate the AHB buffer. This can be achieved by करोing the reset
 * of controller after setting MCR0[SWRESET] bit.
 */
अटल अंतरभूत व्योम nxp_fspi_invalid(काष्ठा nxp_fspi *f)
अणु
	u32 reg;
	पूर्णांक ret;

	reg = fspi_पढ़ोl(f, f->iobase + FSPI_MCR0);
	fspi_ग_लिखोl(f, reg | FSPI_MCR0_SWRST, f->iobase + FSPI_MCR0);

	/* w1c रेजिस्टर, रुको unit clear */
	ret = fspi_पढ़ोl_poll_tout(f, f->iobase + FSPI_MCR0,
				   FSPI_MCR0_SWRST, 0, POLL_TOUT, false);
	WARN_ON(ret);
पूर्ण

अटल व्योम nxp_fspi_prepare_lut(काष्ठा nxp_fspi *f,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	व्योम __iomem *base = f->iobase;
	u32 lutval[4] = अणुपूर्ण;
	पूर्णांक lutidx = 1, i;

	/* cmd */
	lutval[0] |= LUT_DEF(0, LUT_CMD, LUT_PAD(op->cmd.buswidth),
			     op->cmd.opcode);

	/* addr bytes */
	अगर (op->addr.nbytes) अणु
		lutval[lutidx / 2] |= LUT_DEF(lutidx, LUT_ADDR,
					      LUT_PAD(op->addr.buswidth),
					      op->addr.nbytes * 8);
		lutidx++;
	पूर्ण

	/* dummy bytes, अगर needed */
	अगर (op->dummy.nbytes) अणु
		lutval[lutidx / 2] |= LUT_DEF(lutidx, LUT_DUMMY,
		/*
		 * Due to FlexSPI controller limitation number of PAD क्रम dummy
		 * buswidth needs to be programmed as equal to data buswidth.
		 */
					      LUT_PAD(op->data.buswidth),
					      op->dummy.nbytes * 8 /
					      op->dummy.buswidth);
		lutidx++;
	पूर्ण

	/* पढ़ो/ग_लिखो data bytes */
	अगर (op->data.nbytes) अणु
		lutval[lutidx / 2] |= LUT_DEF(lutidx,
					      op->data.dir == SPI_MEM_DATA_IN ?
					      LUT_NXP_READ : LUT_NXP_WRITE,
					      LUT_PAD(op->data.buswidth),
					      0);
		lutidx++;
	पूर्ण

	/* stop condition. */
	lutval[lutidx / 2] |= LUT_DEF(lutidx, LUT_STOP, 0, 0);

	/* unlock LUT */
	fspi_ग_लिखोl(f, FSPI_LUTKEY_VALUE, f->iobase + FSPI_LUTKEY);
	fspi_ग_लिखोl(f, FSPI_LCKER_UNLOCK, f->iobase + FSPI_LCKCR);

	/* fill LUT */
	क्रम (i = 0; i < ARRAY_SIZE(lutval); i++)
		fspi_ग_लिखोl(f, lutval[i], base + FSPI_LUT_REG(i));

	dev_dbg(f->dev, "CMD[%x] lutval[0:%x \t 1:%x \t 2:%x \t 3:%x], size: 0x%08x\n",
		op->cmd.opcode, lutval[0], lutval[1], lutval[2], lutval[3], op->data.nbytes);

	/* lock LUT */
	fspi_ग_लिखोl(f, FSPI_LUTKEY_VALUE, f->iobase + FSPI_LUTKEY);
	fspi_ग_लिखोl(f, FSPI_LCKER_LOCK, f->iobase + FSPI_LCKCR);
पूर्ण

अटल पूर्णांक nxp_fspi_clk_prep_enable(काष्ठा nxp_fspi *f)
अणु
	पूर्णांक ret;

	अगर (is_acpi_node(f->dev->fwnode))
		वापस 0;

	ret = clk_prepare_enable(f->clk_en);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(f->clk);
	अगर (ret) अणु
		clk_disable_unprepare(f->clk_en);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nxp_fspi_clk_disable_unprep(काष्ठा nxp_fspi *f)
अणु
	अगर (is_acpi_node(f->dev->fwnode))
		वापस 0;

	clk_disable_unprepare(f->clk);
	clk_disable_unprepare(f->clk_en);

	वापस 0;
पूर्ण

/*
 * In FlexSPI controller, flash access is based on value of FSPI_FLSHXXCR0
 * रेजिस्टर and start base address of the slave device.
 *
 *							    (Higher address)
 *				--------    <-- FLSHB2CR0
 *				|  B2  |
 *				|      |
 *	B2 start address -->	--------    <-- FLSHB1CR0
 *				|  B1  |
 *				|      |
 *	B1 start address -->	--------    <-- FLSHA2CR0
 *				|  A2  |
 *				|      |
 *	A2 start address -->	--------    <-- FLSHA1CR0
 *				|  A1  |
 *				|      |
 *	A1 start address -->	--------		    (Lower address)
 *
 *
 * Start base address defines the starting address range क्रम given CS and
 * FSPI_FLSHXXCR0 defines the size of the slave device connected at given CS.
 *
 * But, dअगरferent tarमाला_लो are having dअगरferent combinations of number of CS,
 * some tarमाला_लो only have single CS or two CS covering controller's full
 * memory mapped space area.
 * Thus, implementation is being करोne as independent of the size and number
 * of the connected slave device.
 * Assign controller memory mapped space size as the size to the connected
 * slave device.
 * Mark FLSHxxCR0 as zero initially and then assign value only to the selected
 * chip-select Flash configuration रेजिस्टर.
 *
 * For e.g. to access CS2 (B1), FLSHB1CR0 रेजिस्टर would be equal to the
 * memory mapped size of the controller.
 * Value क्रम rest of the CS FLSHxxCR0 रेजिस्टर would be zero.
 *
 */
अटल व्योम nxp_fspi_select_mem(काष्ठा nxp_fspi *f, काष्ठा spi_device *spi)
अणु
	अचिन्हित दीर्घ rate = spi->max_speed_hz;
	पूर्णांक ret;
	uपूर्णांक64_t size_kb;

	/*
	 * Return, अगर previously selected slave device is same as current
	 * requested slave device.
	 */
	अगर (f->selected == spi->chip_select)
		वापस;

	/* Reset FLSHxxCR0 रेजिस्टरs */
	fspi_ग_लिखोl(f, 0, f->iobase + FSPI_FLSHA1CR0);
	fspi_ग_लिखोl(f, 0, f->iobase + FSPI_FLSHA2CR0);
	fspi_ग_लिखोl(f, 0, f->iobase + FSPI_FLSHB1CR0);
	fspi_ग_लिखोl(f, 0, f->iobase + FSPI_FLSHB2CR0);

	/* Assign controller memory mapped space as size, KBytes, of flash. */
	size_kb = FSPI_FLSHXCR0_SZ(f->memmap_phy_size);

	fspi_ग_लिखोl(f, size_kb, f->iobase + FSPI_FLSHA1CR0 +
		    4 * spi->chip_select);

	dev_dbg(f->dev, "Slave device [CS:%x] selected\n", spi->chip_select);

	nxp_fspi_clk_disable_unprep(f);

	ret = clk_set_rate(f->clk, rate);
	अगर (ret)
		वापस;

	ret = nxp_fspi_clk_prep_enable(f);
	अगर (ret)
		वापस;

	f->selected = spi->chip_select;
पूर्ण

अटल पूर्णांक nxp_fspi_पढ़ो_ahb(काष्ठा nxp_fspi *f, स्थिर काष्ठा spi_mem_op *op)
अणु
	u32 start = op->addr.val;
	u32 len = op->data.nbytes;

	/* अगर necessary, ioremap beक्रमe AHB पढ़ो */
	अगर ((!f->ahb_addr) || start < f->memmap_start ||
	     start + len > f->memmap_start + f->memmap_len) अणु
		अगर (f->ahb_addr)
			iounmap(f->ahb_addr);

		f->memmap_start = start;
		f->memmap_len = len > NXP_FSPI_MIN_IOMAP ?
				len : NXP_FSPI_MIN_IOMAP;

		f->ahb_addr = ioremap_wc(f->memmap_phy + f->memmap_start,
					 f->memmap_len);

		अगर (!f->ahb_addr) अणु
			dev_err(f->dev, "failed to alloc memory\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Read out the data directly from the AHB buffer. */
	स_नकल_fromio(op->data.buf.in,
		      f->ahb_addr + start - f->memmap_start, len);

	वापस 0;
पूर्ण

अटल व्योम nxp_fspi_fill_txfअगरo(काष्ठा nxp_fspi *f,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	व्योम __iomem *base = f->iobase;
	पूर्णांक i, ret;
	u8 *buf = (u8 *) op->data.buf.out;

	/* clear the TX FIFO. */
	fspi_ग_लिखोl(f, FSPI_IPTXFCR_CLR, base + FSPI_IPTXFCR);

	/*
	 * Default value of water mark level is 8 bytes, hence in single
	 * ग_लिखो request controller can ग_लिखो max 8 bytes of data.
	 */

	क्रम (i = 0; i < ALIGN_DOWN(op->data.nbytes, 8); i += 8) अणु
		/* Wait क्रम TXFIFO empty */
		ret = fspi_पढ़ोl_poll_tout(f, f->iobase + FSPI_INTR,
					   FSPI_INTR_IPTXWE, 0,
					   POLL_TOUT, true);
		WARN_ON(ret);

		fspi_ग_लिखोl(f, *(u32 *) (buf + i), base + FSPI_TFDR);
		fspi_ग_लिखोl(f, *(u32 *) (buf + i + 4), base + FSPI_TFDR + 4);
		fspi_ग_लिखोl(f, FSPI_INTR_IPTXWE, base + FSPI_INTR);
	पूर्ण

	अगर (i < op->data.nbytes) अणु
		u32 data = 0;
		पूर्णांक j;
		/* Wait क्रम TXFIFO empty */
		ret = fspi_पढ़ोl_poll_tout(f, f->iobase + FSPI_INTR,
					   FSPI_INTR_IPTXWE, 0,
					   POLL_TOUT, true);
		WARN_ON(ret);

		क्रम (j = 0; j < ALIGN(op->data.nbytes - i, 4); j += 4) अणु
			स_नकल(&data, buf + i + j, 4);
			fspi_ग_लिखोl(f, data, base + FSPI_TFDR + j);
		पूर्ण
		fspi_ग_लिखोl(f, FSPI_INTR_IPTXWE, base + FSPI_INTR);
	पूर्ण
पूर्ण

अटल व्योम nxp_fspi_पढ़ो_rxfअगरo(काष्ठा nxp_fspi *f,
			  स्थिर काष्ठा spi_mem_op *op)
अणु
	व्योम __iomem *base = f->iobase;
	पूर्णांक i, ret;
	पूर्णांक len = op->data.nbytes;
	u8 *buf = (u8 *) op->data.buf.in;

	/*
	 * Default value of water mark level is 8 bytes, hence in single
	 * पढ़ो request controller can पढ़ो max 8 bytes of data.
	 */
	क्रम (i = 0; i < ALIGN_DOWN(len, 8); i += 8) अणु
		/* Wait क्रम RXFIFO available */
		ret = fspi_पढ़ोl_poll_tout(f, f->iobase + FSPI_INTR,
					   FSPI_INTR_IPRXWA, 0,
					   POLL_TOUT, true);
		WARN_ON(ret);

		*(u32 *)(buf + i) = fspi_पढ़ोl(f, base + FSPI_RFDR);
		*(u32 *)(buf + i + 4) = fspi_पढ़ोl(f, base + FSPI_RFDR + 4);
		/* move the FIFO poपूर्णांकer */
		fspi_ग_लिखोl(f, FSPI_INTR_IPRXWA, base + FSPI_INTR);
	पूर्ण

	अगर (i < len) अणु
		u32 पंचांगp;
		पूर्णांक size, j;

		buf = op->data.buf.in + i;
		/* Wait क्रम RXFIFO available */
		ret = fspi_पढ़ोl_poll_tout(f, f->iobase + FSPI_INTR,
					   FSPI_INTR_IPRXWA, 0,
					   POLL_TOUT, true);
		WARN_ON(ret);

		len = op->data.nbytes - i;
		क्रम (j = 0; j < op->data.nbytes - i; j += 4) अणु
			पंचांगp = fspi_पढ़ोl(f, base + FSPI_RFDR + j);
			size = min(len, 4);
			स_नकल(buf + j, &पंचांगp, size);
			len -= size;
		पूर्ण
	पूर्ण

	/* invalid the RXFIFO */
	fspi_ग_लिखोl(f, FSPI_IPRXFCR_CLR, base + FSPI_IPRXFCR);
	/* move the FIFO poपूर्णांकer */
	fspi_ग_लिखोl(f, FSPI_INTR_IPRXWA, base + FSPI_INTR);
पूर्ण

अटल पूर्णांक nxp_fspi_करो_op(काष्ठा nxp_fspi *f, स्थिर काष्ठा spi_mem_op *op)
अणु
	व्योम __iomem *base = f->iobase;
	पूर्णांक seqnum = 0;
	पूर्णांक err = 0;
	u32 reg;

	reg = fspi_पढ़ोl(f, base + FSPI_IPRXFCR);
	/* invalid RXFIFO first */
	reg &= ~FSPI_IPRXFCR_DMA_EN;
	reg = reg | FSPI_IPRXFCR_CLR;
	fspi_ग_लिखोl(f, reg, base + FSPI_IPRXFCR);

	init_completion(&f->c);

	fspi_ग_लिखोl(f, op->addr.val, base + FSPI_IPCR0);
	/*
	 * Always start the sequence at the same index since we update
	 * the LUT at each exec_op() call. And also specअगरy the DATA
	 * length, since it's has not been specअगरied in the LUT.
	 */
	fspi_ग_लिखोl(f, op->data.nbytes |
		 (SEQID_LUT << FSPI_IPCR1_SEQID_SHIFT) |
		 (seqnum << FSPI_IPCR1_SEQNUM_SHIFT),
		 base + FSPI_IPCR1);

	/* Trigger the LUT now. */
	fspi_ग_लिखोl(f, FSPI_IPCMD_TRG, base + FSPI_IPCMD);

	/* Wait क्रम the पूर्णांकerrupt. */
	अगर (!रुको_क्रम_completion_समयout(&f->c, msecs_to_jअगरfies(1000)))
		err = -ETIMEDOUT;

	/* Invoke IP data पढ़ो, अगर request is of data पढ़ो. */
	अगर (!err && op->data.nbytes && op->data.dir == SPI_MEM_DATA_IN)
		nxp_fspi_पढ़ो_rxfअगरo(f, op);

	वापस err;
पूर्ण

अटल पूर्णांक nxp_fspi_exec_op(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा nxp_fspi *f = spi_controller_get_devdata(mem->spi->master);
	पूर्णांक err = 0;

	mutex_lock(&f->lock);

	/* Wait क्रम controller being पढ़ोy. */
	err = fspi_पढ़ोl_poll_tout(f, f->iobase + FSPI_STS0,
				   FSPI_STS0_ARB_IDLE, 1, POLL_TOUT, true);
	WARN_ON(err);

	nxp_fspi_select_mem(f, mem->spi);

	nxp_fspi_prepare_lut(f, op);
	/*
	 * If we have large chunks of data, we पढ़ो them through the AHB bus by
	 * accessing the mapped memory. In all other हालs we use IP commands
	 * to access the flash. Read via AHB bus may be corrupted due to
	 * existence of an errata and thereक्रमe discard AHB पढ़ो in such हालs.
	 */
	अगर (op->data.nbytes > (f->devtype_data->rxfअगरo - 4) &&
	    op->data.dir == SPI_MEM_DATA_IN &&
	    !needs_ip_only(f)) अणु
		err = nxp_fspi_पढ़ो_ahb(f, op);
	पूर्ण अन्यथा अणु
		अगर (op->data.nbytes && op->data.dir == SPI_MEM_DATA_OUT)
			nxp_fspi_fill_txfअगरo(f, op);

		err = nxp_fspi_करो_op(f, op);
	पूर्ण

	/* Invalidate the data in the AHB buffer. */
	nxp_fspi_invalid(f);

	mutex_unlock(&f->lock);

	वापस err;
पूर्ण

अटल पूर्णांक nxp_fspi_adjust_op_size(काष्ठा spi_mem *mem, काष्ठा spi_mem_op *op)
अणु
	काष्ठा nxp_fspi *f = spi_controller_get_devdata(mem->spi->master);

	अगर (op->data.dir == SPI_MEM_DATA_OUT) अणु
		अगर (op->data.nbytes > f->devtype_data->txfअगरo)
			op->data.nbytes = f->devtype_data->txfअगरo;
	पूर्ण अन्यथा अणु
		अगर (op->data.nbytes > f->devtype_data->ahb_buf_size)
			op->data.nbytes = f->devtype_data->ahb_buf_size;
		अन्यथा अगर (op->data.nbytes > (f->devtype_data->rxfअगरo - 4))
			op->data.nbytes = ALIGN_DOWN(op->data.nbytes, 8);
	पूर्ण

	/* Limit data bytes to RX FIFO in हाल of IP पढ़ो only */
	अगर (op->data.dir == SPI_MEM_DATA_IN &&
	    needs_ip_only(f) &&
	    op->data.nbytes > f->devtype_data->rxfअगरo)
		op->data.nbytes = f->devtype_data->rxfअगरo;

	वापस 0;
पूर्ण

अटल व्योम erratum_err050568(काष्ठा nxp_fspi *f)
अणु
	स्थिर काष्ठा soc_device_attribute ls1028a_soc_attr[] = अणु
		अणु .family = "QorIQ LS1028A" पूर्ण,
		अणु /* sentinel */ पूर्ण
	पूर्ण;
	काष्ठा device_node *np;
	काष्ठा regmap *map;
	u32 val = 0, sysclk = 0;
	पूर्णांक ret;

	/* Check क्रम LS1028A family */
	अगर (!soc_device_match(ls1028a_soc_attr)) अणु
		dev_dbg(f->dev, "Errata applicable only for LS1028A\n");
		वापस;
	पूर्ण

	/* Compute प्रणाली घड़ी frequency multiplier ratio */
	map = syscon_regmap_lookup_by_compatible("fsl,ls1028a-dcfg");
	अगर (IS_ERR(map)) अणु
		dev_err(f->dev, "No syscon regmap\n");
		जाओ err;
	पूर्ण

	ret = regmap_पढ़ो(map, DCFG_RCWSR1, &val);
	अगर (ret < 0)
		जाओ err;

	/* Strap bits 6:2 define SYS_PLL_RAT i.e frequency multiplier ratio */
	val = (val >> 2) & 0x1F;
	WARN(val == 0, "Strapping is zero: Cannot determine ratio");

	/* Compute प्रणाली घड़ी frequency */
	np = of_find_node_by_name(शून्य, "clock-sysclk");
	अगर (!np)
		जाओ err;

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &sysclk))
		जाओ err;

	sysclk = (sysclk * val) / 1000000; /* Convert sysclk to Mhz */
	dev_dbg(f->dev, "val: 0x%08x, sysclk: %dMhz\n", val, sysclk);

	/* Use IP bus only अगर PLL is 300MHz */
	अगर (sysclk == 300)
		f->devtype_data->quirks |= FSPI_QUIRK_USE_IP_ONLY;

	वापस;

err:
	dev_err(f->dev, "Errata cannot be executed. Read via IP bus may not work\n");
पूर्ण

अटल पूर्णांक nxp_fspi_शेष_setup(काष्ठा nxp_fspi *f)
अणु
	व्योम __iomem *base = f->iobase;
	पूर्णांक ret, i;
	u32 reg;

	/* disable and unprepare घड़ी to aव्योम glitch pass to controller */
	nxp_fspi_clk_disable_unprep(f);

	/* the शेष frequency, we will change it later अगर necessary. */
	ret = clk_set_rate(f->clk, 20000000);
	अगर (ret)
		वापस ret;

	ret = nxp_fspi_clk_prep_enable(f);
	अगर (ret)
		वापस ret;

	/*
	 * ERR050568: Flash access by FlexSPI AHB command may not work with
	 * platक्रमm frequency equal to 300 MHz on LS1028A.
	 * LS1028A reuses LX2160A compatible entry. Make errata applicable क्रम
	 * Layerscape LS1028A platक्रमm.
	 */
	अगर (of_device_is_compatible(f->dev->of_node, "nxp,lx2160a-fspi"))
		erratum_err050568(f);

	/* Reset the module */
	/* w1c रेजिस्टर, रुको unit clear */
	ret = fspi_पढ़ोl_poll_tout(f, f->iobase + FSPI_MCR0,
				   FSPI_MCR0_SWRST, 0, POLL_TOUT, false);
	WARN_ON(ret);

	/* Disable the module */
	fspi_ग_लिखोl(f, FSPI_MCR0_MDIS, base + FSPI_MCR0);

	/* Reset the DLL रेजिस्टर to शेष value */
	fspi_ग_लिखोl(f, FSPI_DLLACR_OVRDEN, base + FSPI_DLLACR);
	fspi_ग_लिखोl(f, FSPI_DLLBCR_OVRDEN, base + FSPI_DLLBCR);

	/* enable module */
	fspi_ग_लिखोl(f, FSPI_MCR0_AHB_TIMEOUT(0xFF) |
		    FSPI_MCR0_IP_TIMEOUT(0xFF) | (u32) FSPI_MCR0_OCTCOMB_EN,
		    base + FSPI_MCR0);

	/*
	 * Disable same device enable bit and configure all slave devices
	 * independently.
	 */
	reg = fspi_पढ़ोl(f, f->iobase + FSPI_MCR2);
	reg = reg & ~(FSPI_MCR2_SAMEDEVICEEN);
	fspi_ग_लिखोl(f, reg, base + FSPI_MCR2);

	/* AHB configuration क्रम access buffer 0~7. */
	क्रम (i = 0; i < 7; i++)
		fspi_ग_लिखोl(f, 0, base + FSPI_AHBRX_BUF0CR0 + 4 * i);

	/*
	 * Set ADATSZ with the maximum AHB buffer size to improve the पढ़ो
	 * perक्रमmance.
	 */
	fspi_ग_लिखोl(f, (f->devtype_data->ahb_buf_size / 8 |
		  FSPI_AHBRXBUF0CR7_PREF), base + FSPI_AHBRX_BUF7CR0);

	/* prefetch and no start address alignment limitation */
	fspi_ग_लिखोl(f, FSPI_AHBCR_PREF_EN | FSPI_AHBCR_RDADDROPT,
		 base + FSPI_AHBCR);

	/* AHB Read - Set lut sequence ID क्रम all CS. */
	fspi_ग_लिखोl(f, SEQID_LUT, base + FSPI_FLSHA1CR2);
	fspi_ग_लिखोl(f, SEQID_LUT, base + FSPI_FLSHA2CR2);
	fspi_ग_लिखोl(f, SEQID_LUT, base + FSPI_FLSHB1CR2);
	fspi_ग_लिखोl(f, SEQID_LUT, base + FSPI_FLSHB2CR2);

	f->selected = -1;

	/* enable the पूर्णांकerrupt */
	fspi_ग_लिखोl(f, FSPI_INTEN_IPCMDDONE, base + FSPI_INTEN);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *nxp_fspi_get_name(काष्ठा spi_mem *mem)
अणु
	काष्ठा nxp_fspi *f = spi_controller_get_devdata(mem->spi->master);
	काष्ठा device *dev = &mem->spi->dev;
	स्थिर अक्षर *name;

	// Set custom name derived from the platक्रमm_device of the controller.
	अगर (of_get_available_child_count(f->dev->of_node) == 1)
		वापस dev_name(f->dev);

	name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
			      "%s-%d", dev_name(f->dev),
			      mem->spi->chip_select);

	अगर (!name) अणु
		dev_err(dev, "failed to get memory for custom flash name\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस name;
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops nxp_fspi_mem_ops = अणु
	.adjust_op_size = nxp_fspi_adjust_op_size,
	.supports_op = nxp_fspi_supports_op,
	.exec_op = nxp_fspi_exec_op,
	.get_name = nxp_fspi_get_name,
पूर्ण;

अटल पूर्णांक nxp_fspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *res;
	काष्ठा nxp_fspi *f;
	पूर्णांक ret;
	u32 reg;

	ctlr = spi_alloc_master(&pdev->dev, माप(*f));
	अगर (!ctlr)
		वापस -ENOMEM;

	ctlr->mode_bits = SPI_RX_DUAL | SPI_RX_QUAD | SPI_RX_OCTAL |
			  SPI_TX_DUAL | SPI_TX_QUAD | SPI_TX_OCTAL;

	f = spi_controller_get_devdata(ctlr);
	f->dev = dev;
	f->devtype_data = (काष्ठा nxp_fspi_devtype_data *)device_get_match_data(dev);
	अगर (!f->devtype_data) अणु
		ret = -ENODEV;
		जाओ err_put_ctrl;
	पूर्ण

	platक्रमm_set_drvdata(pdev, f);

	/* find the resources - configuration रेजिस्टर address space */
	अगर (is_acpi_node(f->dev->fwnode))
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अन्यथा
		res = platक्रमm_get_resource_byname(pdev,
				IORESOURCE_MEM, "fspi_base");

	f->iobase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(f->iobase)) अणु
		ret = PTR_ERR(f->iobase);
		जाओ err_put_ctrl;
	पूर्ण

	/* find the resources - controller memory mapped space */
	अगर (is_acpi_node(f->dev->fwnode))
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अन्यथा
		res = platक्रमm_get_resource_byname(pdev,
				IORESOURCE_MEM, "fspi_mmap");

	अगर (!res) अणु
		ret = -ENODEV;
		जाओ err_put_ctrl;
	पूर्ण

	/* assign memory mapped starting address and mapped size. */
	f->memmap_phy = res->start;
	f->memmap_phy_size = resource_size(res);

	/* find the घड़ीs */
	अगर (dev_of_node(&pdev->dev)) अणु
		f->clk_en = devm_clk_get(dev, "fspi_en");
		अगर (IS_ERR(f->clk_en)) अणु
			ret = PTR_ERR(f->clk_en);
			जाओ err_put_ctrl;
		पूर्ण

		f->clk = devm_clk_get(dev, "fspi");
		अगर (IS_ERR(f->clk)) अणु
			ret = PTR_ERR(f->clk);
			जाओ err_put_ctrl;
		पूर्ण

		ret = nxp_fspi_clk_prep_enable(f);
		अगर (ret) अणु
			dev_err(dev, "can not enable the clock\n");
			जाओ err_put_ctrl;
		पूर्ण
	पूर्ण

	/* Clear potential पूर्णांकerrupts */
	reg = fspi_पढ़ोl(f, f->iobase + FSPI_INTR);
	अगर (reg)
		fspi_ग_लिखोl(f, reg, f->iobase + FSPI_INTR);

	/* find the irq */
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err_disable_clk;

	ret = devm_request_irq(dev, ret,
			nxp_fspi_irq_handler, 0, pdev->name, f);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq: %d\n", ret);
		जाओ err_disable_clk;
	पूर्ण

	mutex_init(&f->lock);

	ctlr->bus_num = -1;
	ctlr->num_chipselect = NXP_FSPI_MAX_CHIPSELECT;
	ctlr->mem_ops = &nxp_fspi_mem_ops;

	nxp_fspi_शेष_setup(f);

	ctlr->dev.of_node = np;

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, ctlr);
	अगर (ret)
		जाओ err_destroy_mutex;

	वापस 0;

err_destroy_mutex:
	mutex_destroy(&f->lock);

err_disable_clk:
	nxp_fspi_clk_disable_unprep(f);

err_put_ctrl:
	spi_controller_put(ctlr);

	dev_err(dev, "NXP FSPI probe failed\n");
	वापस ret;
पूर्ण

अटल पूर्णांक nxp_fspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nxp_fspi *f = platक्रमm_get_drvdata(pdev);

	/* disable the hardware */
	fspi_ग_लिखोl(f, FSPI_MCR0_MDIS, f->iobase + FSPI_MCR0);

	nxp_fspi_clk_disable_unprep(f);

	mutex_destroy(&f->lock);

	अगर (f->ahb_addr)
		iounmap(f->ahb_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक nxp_fspi_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nxp_fspi_resume(काष्ठा device *dev)
अणु
	काष्ठा nxp_fspi *f = dev_get_drvdata(dev);

	nxp_fspi_शेष_setup(f);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nxp_fspi_dt_ids[] = अणु
	अणु .compatible = "nxp,lx2160a-fspi", .data = (व्योम *)&lx2160a_data, पूर्ण,
	अणु .compatible = "nxp,imx8mm-fspi", .data = (व्योम *)&imx8mm_data, पूर्ण,
	अणु .compatible = "nxp,imx8mp-fspi", .data = (व्योम *)&imx8mm_data, पूर्ण,
	अणु .compatible = "nxp,imx8qxp-fspi", .data = (व्योम *)&imx8qxp_data, पूर्ण,
	अणु .compatible = "nxp,imx8dxl-fspi", .data = (व्योम *)&imx8dxl_data, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nxp_fspi_dt_ids);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id nxp_fspi_acpi_ids[] = अणु
	अणु "NXP0009", .driver_data = (kernel_uदीर्घ_t)&lx2160a_data, पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, nxp_fspi_acpi_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops nxp_fspi_pm_ops = अणु
	.suspend	= nxp_fspi_suspend,
	.resume		= nxp_fspi_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver nxp_fspi_driver = अणु
	.driver = अणु
		.name	= "nxp-fspi",
		.of_match_table = nxp_fspi_dt_ids,
		.acpi_match_table = ACPI_PTR(nxp_fspi_acpi_ids),
		.pm =   &nxp_fspi_pm_ops,
	पूर्ण,
	.probe          = nxp_fspi_probe,
	.हटाओ		= nxp_fspi_हटाओ,
पूर्ण;
module_platक्रमm_driver(nxp_fspi_driver);

MODULE_DESCRIPTION("NXP FSPI Controller Driver");
MODULE_AUTHOR("NXP Semiconductor");
MODULE_AUTHOR("Yogesh Narayan Gaur <yogeshnarayan.gaur@nxp.com>");
MODULE_AUTHOR("Boris Brezillon <bbrezillon@kernel.org>");
MODULE_AUTHOR("Frieder Schrempf <frieder.schrempf@kontron.de>");
MODULE_LICENSE("GPL v2");
