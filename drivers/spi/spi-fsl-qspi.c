<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * Freescale QuadSPI driver.
 *
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 * Copyright (C) 2018 Bootlin
 * Copyright (C) 2018 exceet electronics GmbH
 * Copyright (C) 2018 Kontron Electronics GmbH
 *
 * Transition to SPI MEM पूर्णांकerface:
 * Authors:
 *     Boris Brezillon <bbrezillon@kernel.org>
 *     Frieder Schrempf <frieder.schrempf@kontron.de>
 *     Yogesh Gaur <yogeshnarayan.gaur@nxp.com>
 *     Suresh Gupta <suresh.gupta@nxp.com>
 *
 * Based on the original fsl-quadspi.c SPI NOR driver:
 * Author: Freescale Semiconductor, Inc.
 *
 */

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
#समावेश <linux/sizes.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>

/*
 * The driver only uses one single LUT entry, that is updated on
 * each call of exec_op(). Index 0 is preset at boot with a basic
 * पढ़ो operation, so let's use the last entry (15).
 */
#घोषणा	SEQID_LUT			15

/* Registers used by the driver */
#घोषणा QUADSPI_MCR			0x00
#घोषणा QUADSPI_MCR_RESERVED_MASK	GENMASK(19, 16)
#घोषणा QUADSPI_MCR_MDIS_MASK		BIT(14)
#घोषणा QUADSPI_MCR_CLR_TXF_MASK	BIT(11)
#घोषणा QUADSPI_MCR_CLR_RXF_MASK	BIT(10)
#घोषणा QUADSPI_MCR_DDR_EN_MASK		BIT(7)
#घोषणा QUADSPI_MCR_END_CFG_MASK	GENMASK(3, 2)
#घोषणा QUADSPI_MCR_SWRSTHD_MASK	BIT(1)
#घोषणा QUADSPI_MCR_SWRSTSD_MASK	BIT(0)

#घोषणा QUADSPI_IPCR			0x08
#घोषणा QUADSPI_IPCR_SEQID(x)		((x) << 24)

#घोषणा QUADSPI_FLSHCR			0x0c
#घोषणा QUADSPI_FLSHCR_TCSS_MASK	GENMASK(3, 0)
#घोषणा QUADSPI_FLSHCR_TCSH_MASK	GENMASK(11, 8)
#घोषणा QUADSPI_FLSHCR_TDH_MASK		GENMASK(17, 16)

#घोषणा QUADSPI_BUF0CR                  0x10
#घोषणा QUADSPI_BUF1CR                  0x14
#घोषणा QUADSPI_BUF2CR                  0x18
#घोषणा QUADSPI_BUFXCR_INVALID_MSTRID   0xe

#घोषणा QUADSPI_BUF3CR			0x1c
#घोषणा QUADSPI_BUF3CR_ALLMST_MASK	BIT(31)
#घोषणा QUADSPI_BUF3CR_ADATSZ(x)	((x) << 8)
#घोषणा QUADSPI_BUF3CR_ADATSZ_MASK	GENMASK(15, 8)

#घोषणा QUADSPI_BFGENCR			0x20
#घोषणा QUADSPI_BFGENCR_SEQID(x)	((x) << 12)

#घोषणा QUADSPI_BUF0IND			0x30
#घोषणा QUADSPI_BUF1IND			0x34
#घोषणा QUADSPI_BUF2IND			0x38
#घोषणा QUADSPI_SFAR			0x100

#घोषणा QUADSPI_SMPR			0x108
#घोषणा QUADSPI_SMPR_DDRSMP_MASK	GENMASK(18, 16)
#घोषणा QUADSPI_SMPR_FSDLY_MASK		BIT(6)
#घोषणा QUADSPI_SMPR_FSPHS_MASK		BIT(5)
#घोषणा QUADSPI_SMPR_HSENA_MASK		BIT(0)

#घोषणा QUADSPI_RBCT			0x110
#घोषणा QUADSPI_RBCT_WMRK_MASK		GENMASK(4, 0)
#घोषणा QUADSPI_RBCT_RXBRD_USEIPS	BIT(8)

#घोषणा QUADSPI_TBDR			0x154

#घोषणा QUADSPI_SR			0x15c
#घोषणा QUADSPI_SR_IP_ACC_MASK		BIT(1)
#घोषणा QUADSPI_SR_AHB_ACC_MASK		BIT(2)

#घोषणा QUADSPI_FR			0x160
#घोषणा QUADSPI_FR_TFF_MASK		BIT(0)

#घोषणा QUADSPI_RSER			0x164
#घोषणा QUADSPI_RSER_TFIE		BIT(0)

#घोषणा QUADSPI_SPTRCLR			0x16c
#घोषणा QUADSPI_SPTRCLR_IPPTRC		BIT(8)
#घोषणा QUADSPI_SPTRCLR_BFPTRC		BIT(0)

#घोषणा QUADSPI_SFA1AD			0x180
#घोषणा QUADSPI_SFA2AD			0x184
#घोषणा QUADSPI_SFB1AD			0x188
#घोषणा QUADSPI_SFB2AD			0x18c
#घोषणा QUADSPI_RBDR(x)			(0x200 + ((x) * 4))

#घोषणा QUADSPI_LUTKEY			0x300
#घोषणा QUADSPI_LUTKEY_VALUE		0x5AF05AF0

#घोषणा QUADSPI_LCKCR			0x304
#घोषणा QUADSPI_LCKER_LOCK		BIT(0)
#घोषणा QUADSPI_LCKER_UNLOCK		BIT(1)

#घोषणा QUADSPI_LUT_BASE		0x310
#घोषणा QUADSPI_LUT_OFFSET		(SEQID_LUT * 4 * 4)
#घोषणा QUADSPI_LUT_REG(idx) \
	(QUADSPI_LUT_BASE + QUADSPI_LUT_OFFSET + (idx) * 4)

/* Inकाष्ठाion set क्रम the LUT रेजिस्टर */
#घोषणा LUT_STOP		0
#घोषणा LUT_CMD			1
#घोषणा LUT_ADDR		2
#घोषणा LUT_DUMMY		3
#घोषणा LUT_MODE		4
#घोषणा LUT_MODE2		5
#घोषणा LUT_MODE4		6
#घोषणा LUT_FSL_READ		7
#घोषणा LUT_FSL_WRITE		8
#घोषणा LUT_JMP_ON_CS		9
#घोषणा LUT_ADDR_DDR		10
#घोषणा LUT_MODE_DDR		11
#घोषणा LUT_MODE2_DDR		12
#घोषणा LUT_MODE4_DDR		13
#घोषणा LUT_FSL_READ_DDR	14
#घोषणा LUT_FSL_WRITE_DDR	15
#घोषणा LUT_DATA_LEARN		16

/*
 * The PAD definitions क्रम LUT रेजिस्टर.
 *
 * The pad stands क्रम the number of IO lines [0:3].
 * For example, the quad पढ़ो needs four IO lines,
 * so you should use LUT_PAD(4).
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
#घोषणा LUT_DEF(idx, ins, pad, opr)					\
	((((ins) << 10) | ((pad) << 8) | (opr)) << (((idx) % 2) * 16))

/* Controller needs driver to swap endianness */
#घोषणा QUADSPI_QUIRK_SWAP_ENDIAN	BIT(0)

/* Controller needs 4x पूर्णांकernal घड़ी */
#घोषणा QUADSPI_QUIRK_4X_INT_CLK	BIT(1)

/*
 * TKT253890, the controller needs the driver to fill the txfअगरo with
 * 16 bytes at least to trigger a data transfer, even though the extra
 * data won't be transferred.
 */
#घोषणा QUADSPI_QUIRK_TKT253890		BIT(2)

/* TKT245618, the controller cannot wake up from रुको mode */
#घोषणा QUADSPI_QUIRK_TKT245618		BIT(3)

/*
 * Controller adds QSPI_AMBA_BASE (base address of the mapped memory)
 * पूर्णांकernally. No need to add it when setting SFXXAD and SFAR रेजिस्टरs
 */
#घोषणा QUADSPI_QUIRK_BASE_INTERNAL	BIT(4)

/*
 * Controller uses TDH bits in रेजिस्टर QUADSPI_FLSHCR.
 * They need to be set in accordance with the DDR/SDR mode.
 */
#घोषणा QUADSPI_QUIRK_USE_TDH_SETTING	BIT(5)

काष्ठा fsl_qspi_devtype_data अणु
	अचिन्हित पूर्णांक rxfअगरo;
	अचिन्हित पूर्णांक txfअगरo;
	पूर्णांक invalid_mstrid;
	अचिन्हित पूर्णांक ahb_buf_size;
	अचिन्हित पूर्णांक quirks;
	bool little_endian;
पूर्ण;

अटल स्थिर काष्ठा fsl_qspi_devtype_data vybrid_data = अणु
	.rxfअगरo = SZ_128,
	.txfअगरo = SZ_64,
	.invalid_mstrid = QUADSPI_BUFXCR_INVALID_MSTRID,
	.ahb_buf_size = SZ_1K,
	.quirks = QUADSPI_QUIRK_SWAP_ENDIAN,
	.little_endian = true,
पूर्ण;

अटल स्थिर काष्ठा fsl_qspi_devtype_data imx6sx_data = अणु
	.rxfअगरo = SZ_128,
	.txfअगरo = SZ_512,
	.invalid_mstrid = QUADSPI_BUFXCR_INVALID_MSTRID,
	.ahb_buf_size = SZ_1K,
	.quirks = QUADSPI_QUIRK_4X_INT_CLK | QUADSPI_QUIRK_TKT245618,
	.little_endian = true,
पूर्ण;

अटल स्थिर काष्ठा fsl_qspi_devtype_data imx7d_data = अणु
	.rxfअगरo = SZ_128,
	.txfअगरo = SZ_512,
	.invalid_mstrid = QUADSPI_BUFXCR_INVALID_MSTRID,
	.ahb_buf_size = SZ_1K,
	.quirks = QUADSPI_QUIRK_TKT253890 | QUADSPI_QUIRK_4X_INT_CLK |
		  QUADSPI_QUIRK_USE_TDH_SETTING,
	.little_endian = true,
पूर्ण;

अटल स्थिर काष्ठा fsl_qspi_devtype_data imx6ul_data = अणु
	.rxfअगरo = SZ_128,
	.txfअगरo = SZ_512,
	.invalid_mstrid = QUADSPI_BUFXCR_INVALID_MSTRID,
	.ahb_buf_size = SZ_1K,
	.quirks = QUADSPI_QUIRK_TKT253890 | QUADSPI_QUIRK_4X_INT_CLK |
		  QUADSPI_QUIRK_USE_TDH_SETTING,
	.little_endian = true,
पूर्ण;

अटल स्थिर काष्ठा fsl_qspi_devtype_data ls1021a_data = अणु
	.rxfअगरo = SZ_128,
	.txfअगरo = SZ_64,
	.invalid_mstrid = QUADSPI_BUFXCR_INVALID_MSTRID,
	.ahb_buf_size = SZ_1K,
	.quirks = 0,
	.little_endian = false,
पूर्ण;

अटल स्थिर काष्ठा fsl_qspi_devtype_data ls2080a_data = अणु
	.rxfअगरo = SZ_128,
	.txfअगरo = SZ_64,
	.ahb_buf_size = SZ_1K,
	.invalid_mstrid = 0x0,
	.quirks = QUADSPI_QUIRK_TKT253890 | QUADSPI_QUIRK_BASE_INTERNAL,
	.little_endian = true,
पूर्ण;

काष्ठा fsl_qspi अणु
	व्योम __iomem *iobase;
	व्योम __iomem *ahb_addr;
	u32 memmap_phy;
	काष्ठा clk *clk, *clk_en;
	काष्ठा device *dev;
	काष्ठा completion c;
	स्थिर काष्ठा fsl_qspi_devtype_data *devtype_data;
	काष्ठा mutex lock;
	काष्ठा pm_qos_request pm_qos_req;
	पूर्णांक selected;
पूर्ण;

अटल अंतरभूत पूर्णांक needs_swap_endian(काष्ठा fsl_qspi *q)
अणु
	वापस q->devtype_data->quirks & QUADSPI_QUIRK_SWAP_ENDIAN;
पूर्ण

अटल अंतरभूत पूर्णांक needs_4x_घड़ी(काष्ठा fsl_qspi *q)
अणु
	वापस q->devtype_data->quirks & QUADSPI_QUIRK_4X_INT_CLK;
पूर्ण

अटल अंतरभूत पूर्णांक needs_fill_txfअगरo(काष्ठा fsl_qspi *q)
अणु
	वापस q->devtype_data->quirks & QUADSPI_QUIRK_TKT253890;
पूर्ण

अटल अंतरभूत पूर्णांक needs_wakeup_रुको_mode(काष्ठा fsl_qspi *q)
अणु
	वापस q->devtype_data->quirks & QUADSPI_QUIRK_TKT245618;
पूर्ण

अटल अंतरभूत पूर्णांक needs_amba_base_offset(काष्ठा fsl_qspi *q)
अणु
	वापस !(q->devtype_data->quirks & QUADSPI_QUIRK_BASE_INTERNAL);
पूर्ण

अटल अंतरभूत पूर्णांक needs_tdh_setting(काष्ठा fsl_qspi *q)
अणु
	वापस q->devtype_data->quirks & QUADSPI_QUIRK_USE_TDH_SETTING;
पूर्ण

/*
 * An IC bug makes it necessary to rearrange the 32-bit data.
 * Later chips, such as IMX6SLX, have fixed this bug.
 */
अटल अंतरभूत u32 fsl_qspi_endian_xchg(काष्ठा fsl_qspi *q, u32 a)
अणु
	वापस needs_swap_endian(q) ? __swab32(a) : a;
पूर्ण

/*
 * R/W functions क्रम big- or little-endian रेजिस्टरs:
 * The QSPI controller's endianness is independent of
 * the CPU core's endianness. So far, although the CPU
 * core is little-endian the QSPI controller can use
 * big-endian or little-endian.
 */
अटल व्योम qspi_ग_लिखोl(काष्ठा fsl_qspi *q, u32 val, व्योम __iomem *addr)
अणु
	अगर (q->devtype_data->little_endian)
		ioग_लिखो32(val, addr);
	अन्यथा
		ioग_लिखो32be(val, addr);
पूर्ण

अटल u32 qspi_पढ़ोl(काष्ठा fsl_qspi *q, व्योम __iomem *addr)
अणु
	अगर (q->devtype_data->little_endian)
		वापस ioपढ़ो32(addr);

	वापस ioपढ़ो32be(addr);
पूर्ण

अटल irqवापस_t fsl_qspi_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_qspi *q = dev_id;
	u32 reg;

	/* clear पूर्णांकerrupt */
	reg = qspi_पढ़ोl(q, q->iobase + QUADSPI_FR);
	qspi_ग_लिखोl(q, reg, q->iobase + QUADSPI_FR);

	अगर (reg & QUADSPI_FR_TFF_MASK)
		complete(&q->c);

	dev_dbg(q->dev, "QUADSPI_FR : 0x%.8x:0x%.8x\n", 0, reg);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fsl_qspi_check_buswidth(काष्ठा fsl_qspi *q, u8 width)
अणु
	चयन (width) अणु
	हाल 1:
	हाल 2:
	हाल 4:
		वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल bool fsl_qspi_supports_op(काष्ठा spi_mem *mem,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा fsl_qspi *q = spi_controller_get_devdata(mem->spi->master);
	पूर्णांक ret;

	ret = fsl_qspi_check_buswidth(q, op->cmd.buswidth);

	अगर (op->addr.nbytes)
		ret |= fsl_qspi_check_buswidth(q, op->addr.buswidth);

	अगर (op->dummy.nbytes)
		ret |= fsl_qspi_check_buswidth(q, op->dummy.buswidth);

	अगर (op->data.nbytes)
		ret |= fsl_qspi_check_buswidth(q, op->data.buswidth);

	अगर (ret)
		वापस false;

	/*
	 * The number of inकाष्ठाions needed क्रम the op, needs
	 * to fit पूर्णांकo a single LUT entry.
	 */
	अगर (op->addr.nbytes +
	   (op->dummy.nbytes ? 1:0) +
	   (op->data.nbytes ? 1:0) > 6)
		वापस false;

	/* Max 64 dummy घड़ी cycles supported */
	अगर (op->dummy.nbytes &&
	    (op->dummy.nbytes * 8 / op->dummy.buswidth > 64))
		वापस false;

	/* Max data length, check controller limits and alignment */
	अगर (op->data.dir == SPI_MEM_DATA_IN &&
	    (op->data.nbytes > q->devtype_data->ahb_buf_size ||
	     (op->data.nbytes > q->devtype_data->rxfअगरo - 4 &&
	      !IS_ALIGNED(op->data.nbytes, 8))))
		वापस false;

	अगर (op->data.dir == SPI_MEM_DATA_OUT &&
	    op->data.nbytes > q->devtype_data->txfअगरo)
		वापस false;

	वापस spi_mem_शेष_supports_op(mem, op);
पूर्ण

अटल व्योम fsl_qspi_prepare_lut(काष्ठा fsl_qspi *q,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	व्योम __iomem *base = q->iobase;
	u32 lutval[4] = अणुपूर्ण;
	पूर्णांक lutidx = 1, i;

	lutval[0] |= LUT_DEF(0, LUT_CMD, LUT_PAD(op->cmd.buswidth),
			     op->cmd.opcode);

	/*
	 * For some unknown reason, using LUT_ADDR करोesn't work in some
	 * हालs (at least with only one byte दीर्घ addresses), so
	 * let's use LUT_MODE to ग_लिखो the address bytes one by one
	 */
	क्रम (i = 0; i < op->addr.nbytes; i++) अणु
		u8 addrbyte = op->addr.val >> (8 * (op->addr.nbytes - i - 1));

		lutval[lutidx / 2] |= LUT_DEF(lutidx, LUT_MODE,
					      LUT_PAD(op->addr.buswidth),
					      addrbyte);
		lutidx++;
	पूर्ण

	अगर (op->dummy.nbytes) अणु
		lutval[lutidx / 2] |= LUT_DEF(lutidx, LUT_DUMMY,
					      LUT_PAD(op->dummy.buswidth),
					      op->dummy.nbytes * 8 /
					      op->dummy.buswidth);
		lutidx++;
	पूर्ण

	अगर (op->data.nbytes) अणु
		lutval[lutidx / 2] |= LUT_DEF(lutidx,
					      op->data.dir == SPI_MEM_DATA_IN ?
					      LUT_FSL_READ : LUT_FSL_WRITE,
					      LUT_PAD(op->data.buswidth),
					      0);
		lutidx++;
	पूर्ण

	lutval[lutidx / 2] |= LUT_DEF(lutidx, LUT_STOP, 0, 0);

	/* unlock LUT */
	qspi_ग_लिखोl(q, QUADSPI_LUTKEY_VALUE, q->iobase + QUADSPI_LUTKEY);
	qspi_ग_लिखोl(q, QUADSPI_LCKER_UNLOCK, q->iobase + QUADSPI_LCKCR);

	/* fill LUT */
	क्रम (i = 0; i < ARRAY_SIZE(lutval); i++)
		qspi_ग_लिखोl(q, lutval[i], base + QUADSPI_LUT_REG(i));

	/* lock LUT */
	qspi_ग_लिखोl(q, QUADSPI_LUTKEY_VALUE, q->iobase + QUADSPI_LUTKEY);
	qspi_ग_लिखोl(q, QUADSPI_LCKER_LOCK, q->iobase + QUADSPI_LCKCR);
पूर्ण

अटल पूर्णांक fsl_qspi_clk_prep_enable(काष्ठा fsl_qspi *q)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(q->clk_en);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(q->clk);
	अगर (ret) अणु
		clk_disable_unprepare(q->clk_en);
		वापस ret;
	पूर्ण

	अगर (needs_wakeup_रुको_mode(q))
		cpu_latency_qos_add_request(&q->pm_qos_req, 0);

	वापस 0;
पूर्ण

अटल व्योम fsl_qspi_clk_disable_unprep(काष्ठा fsl_qspi *q)
अणु
	अगर (needs_wakeup_रुको_mode(q))
		cpu_latency_qos_हटाओ_request(&q->pm_qos_req);

	clk_disable_unprepare(q->clk);
	clk_disable_unprepare(q->clk_en);
पूर्ण

/*
 * If we have changed the content of the flash by writing or erasing, or अगर we
 * पढ़ो from flash with a dअगरferent offset पूर्णांकo the page buffer, we need to
 * invalidate the AHB buffer. If we करो not करो so, we may पढ़ो out the wrong
 * data. The spec tells us reset the AHB करोमुख्य and Serial Flash करोमुख्य at
 * the same समय.
 */
अटल व्योम fsl_qspi_invalidate(काष्ठा fsl_qspi *q)
अणु
	u32 reg;

	reg = qspi_पढ़ोl(q, q->iobase + QUADSPI_MCR);
	reg |= QUADSPI_MCR_SWRSTHD_MASK | QUADSPI_MCR_SWRSTSD_MASK;
	qspi_ग_लिखोl(q, reg, q->iobase + QUADSPI_MCR);

	/*
	 * The minimum delay : 1 AHB + 2 SFCK घड़ीs.
	 * Delay 1 us is enough.
	 */
	udelay(1);

	reg &= ~(QUADSPI_MCR_SWRSTHD_MASK | QUADSPI_MCR_SWRSTSD_MASK);
	qspi_ग_लिखोl(q, reg, q->iobase + QUADSPI_MCR);
पूर्ण

अटल व्योम fsl_qspi_select_mem(काष्ठा fsl_qspi *q, काष्ठा spi_device *spi)
अणु
	अचिन्हित दीर्घ rate = spi->max_speed_hz;
	पूर्णांक ret;

	अगर (q->selected == spi->chip_select)
		वापस;

	अगर (needs_4x_घड़ी(q))
		rate *= 4;

	fsl_qspi_clk_disable_unprep(q);

	ret = clk_set_rate(q->clk, rate);
	अगर (ret)
		वापस;

	ret = fsl_qspi_clk_prep_enable(q);
	अगर (ret)
		वापस;

	q->selected = spi->chip_select;

	fsl_qspi_invalidate(q);
पूर्ण

अटल व्योम fsl_qspi_पढ़ो_ahb(काष्ठा fsl_qspi *q, स्थिर काष्ठा spi_mem_op *op)
अणु
	स_नकल_fromio(op->data.buf.in,
		      q->ahb_addr + q->selected * q->devtype_data->ahb_buf_size,
		      op->data.nbytes);
पूर्ण

अटल व्योम fsl_qspi_fill_txfअगरo(काष्ठा fsl_qspi *q,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	व्योम __iomem *base = q->iobase;
	पूर्णांक i;
	u32 val;

	क्रम (i = 0; i < ALIGN_DOWN(op->data.nbytes, 4); i += 4) अणु
		स_नकल(&val, op->data.buf.out + i, 4);
		val = fsl_qspi_endian_xchg(q, val);
		qspi_ग_लिखोl(q, val, base + QUADSPI_TBDR);
	पूर्ण

	अगर (i < op->data.nbytes) अणु
		स_नकल(&val, op->data.buf.out + i, op->data.nbytes - i);
		val = fsl_qspi_endian_xchg(q, val);
		qspi_ग_लिखोl(q, val, base + QUADSPI_TBDR);
	पूर्ण

	अगर (needs_fill_txfअगरo(q)) अणु
		क्रम (i = op->data.nbytes; i < 16; i += 4)
			qspi_ग_लिखोl(q, 0, base + QUADSPI_TBDR);
	पूर्ण
पूर्ण

अटल व्योम fsl_qspi_पढ़ो_rxfअगरo(काष्ठा fsl_qspi *q,
			  स्थिर काष्ठा spi_mem_op *op)
अणु
	व्योम __iomem *base = q->iobase;
	पूर्णांक i;
	u8 *buf = op->data.buf.in;
	u32 val;

	क्रम (i = 0; i < ALIGN_DOWN(op->data.nbytes, 4); i += 4) अणु
		val = qspi_पढ़ोl(q, base + QUADSPI_RBDR(i / 4));
		val = fsl_qspi_endian_xchg(q, val);
		स_नकल(buf + i, &val, 4);
	पूर्ण

	अगर (i < op->data.nbytes) अणु
		val = qspi_पढ़ोl(q, base + QUADSPI_RBDR(i / 4));
		val = fsl_qspi_endian_xchg(q, val);
		स_नकल(buf + i, &val, op->data.nbytes - i);
	पूर्ण
पूर्ण

अटल पूर्णांक fsl_qspi_करो_op(काष्ठा fsl_qspi *q, स्थिर काष्ठा spi_mem_op *op)
अणु
	व्योम __iomem *base = q->iobase;
	पूर्णांक err = 0;

	init_completion(&q->c);

	/*
	 * Always start the sequence at the same index since we update
	 * the LUT at each exec_op() call. And also specअगरy the DATA
	 * length, since it's has not been specअगरied in the LUT.
	 */
	qspi_ग_लिखोl(q, op->data.nbytes | QUADSPI_IPCR_SEQID(SEQID_LUT),
		    base + QUADSPI_IPCR);

	/* Wait क्रम the पूर्णांकerrupt. */
	अगर (!रुको_क्रम_completion_समयout(&q->c, msecs_to_jअगरfies(1000)))
		err = -ETIMEDOUT;

	अगर (!err && op->data.nbytes && op->data.dir == SPI_MEM_DATA_IN)
		fsl_qspi_पढ़ो_rxfअगरo(q, op);

	वापस err;
पूर्ण

अटल पूर्णांक fsl_qspi_पढ़ोl_poll_tout(काष्ठा fsl_qspi *q, व्योम __iomem *base,
				    u32 mask, u32 delay_us, u32 समयout_us)
अणु
	u32 reg;

	अगर (!q->devtype_data->little_endian)
		mask = (u32)cpu_to_be32(mask);

	वापस पढ़ोl_poll_समयout(base, reg, !(reg & mask), delay_us,
				  समयout_us);
पूर्ण

अटल पूर्णांक fsl_qspi_exec_op(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा fsl_qspi *q = spi_controller_get_devdata(mem->spi->master);
	व्योम __iomem *base = q->iobase;
	u32 addr_offset = 0;
	पूर्णांक err = 0;
	पूर्णांक invalid_mstrid = q->devtype_data->invalid_mstrid;

	mutex_lock(&q->lock);

	/* रुको क्रम the controller being पढ़ोy */
	fsl_qspi_पढ़ोl_poll_tout(q, base + QUADSPI_SR, (QUADSPI_SR_IP_ACC_MASK |
				 QUADSPI_SR_AHB_ACC_MASK), 10, 1000);

	fsl_qspi_select_mem(q, mem->spi);

	अगर (needs_amba_base_offset(q))
		addr_offset = q->memmap_phy;

	qspi_ग_लिखोl(q,
		    q->selected * q->devtype_data->ahb_buf_size + addr_offset,
		    base + QUADSPI_SFAR);

	qspi_ग_लिखोl(q, qspi_पढ़ोl(q, base + QUADSPI_MCR) |
		    QUADSPI_MCR_CLR_RXF_MASK | QUADSPI_MCR_CLR_TXF_MASK,
		    base + QUADSPI_MCR);

	qspi_ग_लिखोl(q, QUADSPI_SPTRCLR_BFPTRC | QUADSPI_SPTRCLR_IPPTRC,
		    base + QUADSPI_SPTRCLR);

	qspi_ग_लिखोl(q, invalid_mstrid, base + QUADSPI_BUF0CR);
	qspi_ग_लिखोl(q, invalid_mstrid, base + QUADSPI_BUF1CR);
	qspi_ग_लिखोl(q, invalid_mstrid, base + QUADSPI_BUF2CR);

	fsl_qspi_prepare_lut(q, op);

	/*
	 * If we have large chunks of data, we पढ़ो them through the AHB bus
	 * by accessing the mapped memory. In all other हालs we use
	 * IP commands to access the flash.
	 */
	अगर (op->data.nbytes > (q->devtype_data->rxfअगरo - 4) &&
	    op->data.dir == SPI_MEM_DATA_IN) अणु
		fsl_qspi_पढ़ो_ahb(q, op);
	पूर्ण अन्यथा अणु
		qspi_ग_लिखोl(q, QUADSPI_RBCT_WMRK_MASK |
			    QUADSPI_RBCT_RXBRD_USEIPS, base + QUADSPI_RBCT);

		अगर (op->data.nbytes && op->data.dir == SPI_MEM_DATA_OUT)
			fsl_qspi_fill_txfअगरo(q, op);

		err = fsl_qspi_करो_op(q, op);
	पूर्ण

	/* Invalidate the data in the AHB buffer. */
	fsl_qspi_invalidate(q);

	mutex_unlock(&q->lock);

	वापस err;
पूर्ण

अटल पूर्णांक fsl_qspi_adjust_op_size(काष्ठा spi_mem *mem, काष्ठा spi_mem_op *op)
अणु
	काष्ठा fsl_qspi *q = spi_controller_get_devdata(mem->spi->master);

	अगर (op->data.dir == SPI_MEM_DATA_OUT) अणु
		अगर (op->data.nbytes > q->devtype_data->txfअगरo)
			op->data.nbytes = q->devtype_data->txfअगरo;
	पूर्ण अन्यथा अणु
		अगर (op->data.nbytes > q->devtype_data->ahb_buf_size)
			op->data.nbytes = q->devtype_data->ahb_buf_size;
		अन्यथा अगर (op->data.nbytes > (q->devtype_data->rxfअगरo - 4))
			op->data.nbytes = ALIGN_DOWN(op->data.nbytes, 8);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_qspi_शेष_setup(काष्ठा fsl_qspi *q)
अणु
	व्योम __iomem *base = q->iobase;
	u32 reg, addr_offset = 0;
	पूर्णांक ret;

	/* disable and unprepare घड़ी to aव्योम glitch pass to controller */
	fsl_qspi_clk_disable_unprep(q);

	/* the शेष frequency, we will change it later अगर necessary. */
	ret = clk_set_rate(q->clk, 66000000);
	अगर (ret)
		वापस ret;

	ret = fsl_qspi_clk_prep_enable(q);
	अगर (ret)
		वापस ret;

	/* Reset the module */
	qspi_ग_लिखोl(q, QUADSPI_MCR_SWRSTSD_MASK | QUADSPI_MCR_SWRSTHD_MASK,
		    base + QUADSPI_MCR);
	udelay(1);

	/* Disable the module */
	qspi_ग_लिखोl(q, QUADSPI_MCR_MDIS_MASK | QUADSPI_MCR_RESERVED_MASK,
		    base + QUADSPI_MCR);

	/*
	 * Previous boot stages (BootROM, bootloader) might have used DDR
	 * mode and did not clear the TDH bits. As we currently use SDR mode
	 * only, clear the TDH bits अगर necessary.
	 */
	अगर (needs_tdh_setting(q))
		qspi_ग_लिखोl(q, qspi_पढ़ोl(q, base + QUADSPI_FLSHCR) &
			    ~QUADSPI_FLSHCR_TDH_MASK,
			    base + QUADSPI_FLSHCR);

	reg = qspi_पढ़ोl(q, base + QUADSPI_SMPR);
	qspi_ग_लिखोl(q, reg & ~(QUADSPI_SMPR_FSDLY_MASK
			| QUADSPI_SMPR_FSPHS_MASK
			| QUADSPI_SMPR_HSENA_MASK
			| QUADSPI_SMPR_DDRSMP_MASK), base + QUADSPI_SMPR);

	/* We only use the buffer3 क्रम AHB पढ़ो */
	qspi_ग_लिखोl(q, 0, base + QUADSPI_BUF0IND);
	qspi_ग_लिखोl(q, 0, base + QUADSPI_BUF1IND);
	qspi_ग_लिखोl(q, 0, base + QUADSPI_BUF2IND);

	qspi_ग_लिखोl(q, QUADSPI_BFGENCR_SEQID(SEQID_LUT),
		    q->iobase + QUADSPI_BFGENCR);
	qspi_ग_लिखोl(q, QUADSPI_RBCT_WMRK_MASK, base + QUADSPI_RBCT);
	qspi_ग_लिखोl(q, QUADSPI_BUF3CR_ALLMST_MASK |
		    QUADSPI_BUF3CR_ADATSZ(q->devtype_data->ahb_buf_size / 8),
		    base + QUADSPI_BUF3CR);

	अगर (needs_amba_base_offset(q))
		addr_offset = q->memmap_phy;

	/*
	 * In HW there can be a maximum of four chips on two buses with
	 * two chip selects on each bus. We use four chip selects in SW
	 * to dअगरferentiate between the four chips.
	 * We use ahb_buf_size क्रम each chip and set SFA1AD, SFA2AD, SFB1AD,
	 * SFB2AD accordingly.
	 */
	qspi_ग_लिखोl(q, q->devtype_data->ahb_buf_size + addr_offset,
		    base + QUADSPI_SFA1AD);
	qspi_ग_लिखोl(q, q->devtype_data->ahb_buf_size * 2 + addr_offset,
		    base + QUADSPI_SFA2AD);
	qspi_ग_लिखोl(q, q->devtype_data->ahb_buf_size * 3 + addr_offset,
		    base + QUADSPI_SFB1AD);
	qspi_ग_लिखोl(q, q->devtype_data->ahb_buf_size * 4 + addr_offset,
		    base + QUADSPI_SFB2AD);

	q->selected = -1;

	/* Enable the module */
	qspi_ग_लिखोl(q, QUADSPI_MCR_RESERVED_MASK | QUADSPI_MCR_END_CFG_MASK,
		    base + QUADSPI_MCR);

	/* clear all पूर्णांकerrupt status */
	qspi_ग_लिखोl(q, 0xffffffff, q->iobase + QUADSPI_FR);

	/* enable the पूर्णांकerrupt */
	qspi_ग_लिखोl(q, QUADSPI_RSER_TFIE, q->iobase + QUADSPI_RSER);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *fsl_qspi_get_name(काष्ठा spi_mem *mem)
अणु
	काष्ठा fsl_qspi *q = spi_controller_get_devdata(mem->spi->master);
	काष्ठा device *dev = &mem->spi->dev;
	स्थिर अक्षर *name;

	/*
	 * In order to keep mtdparts compatible with the old MTD driver at
	 * mtd/spi-nor/fsl-quadspi.c, we set a custom name derived from the
	 * platक्रमm_device of the controller.
	 */
	अगर (of_get_available_child_count(q->dev->of_node) == 1)
		वापस dev_name(q->dev);

	name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
			      "%s-%d", dev_name(q->dev),
			      mem->spi->chip_select);

	अगर (!name) अणु
		dev_err(dev, "failed to get memory for custom flash name\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस name;
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops fsl_qspi_mem_ops = अणु
	.adjust_op_size = fsl_qspi_adjust_op_size,
	.supports_op = fsl_qspi_supports_op,
	.exec_op = fsl_qspi_exec_op,
	.get_name = fsl_qspi_get_name,
पूर्ण;

अटल पूर्णांक fsl_qspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *res;
	काष्ठा fsl_qspi *q;
	पूर्णांक ret;

	ctlr = spi_alloc_master(&pdev->dev, माप(*q));
	अगर (!ctlr)
		वापस -ENOMEM;

	ctlr->mode_bits = SPI_RX_DUAL | SPI_RX_QUAD |
			  SPI_TX_DUAL | SPI_TX_QUAD;

	q = spi_controller_get_devdata(ctlr);
	q->dev = dev;
	q->devtype_data = of_device_get_match_data(dev);
	अगर (!q->devtype_data) अणु
		ret = -ENODEV;
		जाओ err_put_ctrl;
	पूर्ण

	platक्रमm_set_drvdata(pdev, q);

	/* find the resources */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "QuadSPI");
	q->iobase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(q->iobase)) अणु
		ret = PTR_ERR(q->iobase);
		जाओ err_put_ctrl;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					"QuadSPI-memory");
	q->memmap_phy = res->start;
	/* Since there are 4 cs, map size required is 4 बार ahb_buf_size */
	q->ahb_addr = devm_ioremap(dev, q->memmap_phy,
				   (q->devtype_data->ahb_buf_size * 4));
	अगर (!q->ahb_addr) अणु
		ret = -ENOMEM;
		जाओ err_put_ctrl;
	पूर्ण

	/* find the घड़ीs */
	q->clk_en = devm_clk_get(dev, "qspi_en");
	अगर (IS_ERR(q->clk_en)) अणु
		ret = PTR_ERR(q->clk_en);
		जाओ err_put_ctrl;
	पूर्ण

	q->clk = devm_clk_get(dev, "qspi");
	अगर (IS_ERR(q->clk)) अणु
		ret = PTR_ERR(q->clk);
		जाओ err_put_ctrl;
	पूर्ण

	ret = fsl_qspi_clk_prep_enable(q);
	अगर (ret) अणु
		dev_err(dev, "can not enable the clock\n");
		जाओ err_put_ctrl;
	पूर्ण

	/* find the irq */
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err_disable_clk;

	ret = devm_request_irq(dev, ret,
			fsl_qspi_irq_handler, 0, pdev->name, q);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq: %d\n", ret);
		जाओ err_disable_clk;
	पूर्ण

	mutex_init(&q->lock);

	ctlr->bus_num = -1;
	ctlr->num_chipselect = 4;
	ctlr->mem_ops = &fsl_qspi_mem_ops;

	fsl_qspi_शेष_setup(q);

	ctlr->dev.of_node = np;

	ret = devm_spi_रेजिस्टर_controller(dev, ctlr);
	अगर (ret)
		जाओ err_destroy_mutex;

	वापस 0;

err_destroy_mutex:
	mutex_destroy(&q->lock);

err_disable_clk:
	fsl_qspi_clk_disable_unprep(q);

err_put_ctrl:
	spi_controller_put(ctlr);

	dev_err(dev, "Freescale QuadSPI probe failed\n");
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_qspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_qspi *q = platक्रमm_get_drvdata(pdev);

	/* disable the hardware */
	qspi_ग_लिखोl(q, QUADSPI_MCR_MDIS_MASK, q->iobase + QUADSPI_MCR);
	qspi_ग_लिखोl(q, 0x0, q->iobase + QUADSPI_RSER);

	fsl_qspi_clk_disable_unprep(q);

	mutex_destroy(&q->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_qspi_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_qspi_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_qspi *q = dev_get_drvdata(dev);

	fsl_qspi_शेष_setup(q);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_qspi_dt_ids[] = अणु
	अणु .compatible = "fsl,vf610-qspi", .data = &vybrid_data, पूर्ण,
	अणु .compatible = "fsl,imx6sx-qspi", .data = &imx6sx_data, पूर्ण,
	अणु .compatible = "fsl,imx7d-qspi", .data = &imx7d_data, पूर्ण,
	अणु .compatible = "fsl,imx6ul-qspi", .data = &imx6ul_data, पूर्ण,
	अणु .compatible = "fsl,ls1021a-qspi", .data = &ls1021a_data, पूर्ण,
	अणु .compatible = "fsl,ls2080a-qspi", .data = &ls2080a_data, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_qspi_dt_ids);

अटल स्थिर काष्ठा dev_pm_ops fsl_qspi_pm_ops = अणु
	.suspend	= fsl_qspi_suspend,
	.resume		= fsl_qspi_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_qspi_driver = अणु
	.driver = अणु
		.name	= "fsl-quadspi",
		.of_match_table = fsl_qspi_dt_ids,
		.pm =   &fsl_qspi_pm_ops,
	पूर्ण,
	.probe          = fsl_qspi_probe,
	.हटाओ		= fsl_qspi_हटाओ,
पूर्ण;
module_platक्रमm_driver(fsl_qspi_driver);

MODULE_DESCRIPTION("Freescale QuadSPI Controller Driver");
MODULE_AUTHOR("Freescale Semiconductor Inc.");
MODULE_AUTHOR("Boris Brezillon <bbrezillon@kernel.org>");
MODULE_AUTHOR("Frieder Schrempf <frieder.schrempf@kontron.de>");
MODULE_AUTHOR("Yogesh Gaur <yogeshnarayan.gaur@nxp.com>");
MODULE_AUTHOR("Suresh Gupta <suresh.gupta@nxp.com>");
MODULE_LICENSE("GPL v2");
