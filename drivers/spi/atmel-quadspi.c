<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Aपंचांगel QSPI Controller
 *
 * Copyright (C) 2015 Aपंचांगel Corporation
 * Copyright (C) 2018 Cryptera A/S
 *
 * Author: Cyrille Pitchen <cyrille.pitchen@aपंचांगel.com>
 * Author: Piotr Bugalski <bugalski.piotr@gmail.com>
 *
 * This driver is based on drivers/mtd/spi-nor/fsl-quadspi.c from Freescale.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi-स्मृति.स>

/* QSPI रेजिस्टर offsets */
#घोषणा QSPI_CR      0x0000  /* Control Register */
#घोषणा QSPI_MR      0x0004  /* Mode Register */
#घोषणा QSPI_RD      0x0008  /* Receive Data Register */
#घोषणा QSPI_TD      0x000c  /* Transmit Data Register */
#घोषणा QSPI_SR      0x0010  /* Status Register */
#घोषणा QSPI_IER     0x0014  /* Interrupt Enable Register */
#घोषणा QSPI_IDR     0x0018  /* Interrupt Disable Register */
#घोषणा QSPI_IMR     0x001c  /* Interrupt Mask Register */
#घोषणा QSPI_SCR     0x0020  /* Serial Clock Register */

#घोषणा QSPI_IAR     0x0030  /* Inकाष्ठाion Address Register */
#घोषणा QSPI_ICR     0x0034  /* Inकाष्ठाion Code Register */
#घोषणा QSPI_WICR    0x0034  /* Write Inकाष्ठाion Code Register */
#घोषणा QSPI_IFR     0x0038  /* Inकाष्ठाion Frame Register */
#घोषणा QSPI_RICR    0x003C  /* Read Inकाष्ठाion Code Register */

#घोषणा QSPI_SMR     0x0040  /* Scrambling Mode Register */
#घोषणा QSPI_SKR     0x0044  /* Scrambling Key Register */

#घोषणा QSPI_WPMR    0x00E4  /* Write Protection Mode Register */
#घोषणा QSPI_WPSR    0x00E8  /* Write Protection Status Register */

#घोषणा QSPI_VERSION 0x00FC  /* Version Register */


/* Bitfields in QSPI_CR (Control Register) */
#घोषणा QSPI_CR_QSPIEN                  BIT(0)
#घोषणा QSPI_CR_QSPIDIS                 BIT(1)
#घोषणा QSPI_CR_SWRST                   BIT(7)
#घोषणा QSPI_CR_LASTXFER                BIT(24)

/* Bitfields in QSPI_MR (Mode Register) */
#घोषणा QSPI_MR_SMM                     BIT(0)
#घोषणा QSPI_MR_LLB                     BIT(1)
#घोषणा QSPI_MR_WDRBT                   BIT(2)
#घोषणा QSPI_MR_SMRM                    BIT(3)
#घोषणा QSPI_MR_CSMODE_MASK             GENMASK(5, 4)
#घोषणा QSPI_MR_CSMODE_NOT_RELOADED     (0 << 4)
#घोषणा QSPI_MR_CSMODE_LASTXFER         (1 << 4)
#घोषणा QSPI_MR_CSMODE_SYSTEMATICALLY   (2 << 4)
#घोषणा QSPI_MR_NBBITS_MASK             GENMASK(11, 8)
#घोषणा QSPI_MR_NBBITS(n)               ((((n) - 8) << 8) & QSPI_MR_NBBITS_MASK)
#घोषणा QSPI_MR_DLYBCT_MASK             GENMASK(23, 16)
#घोषणा QSPI_MR_DLYBCT(n)               (((n) << 16) & QSPI_MR_DLYBCT_MASK)
#घोषणा QSPI_MR_DLYCS_MASK              GENMASK(31, 24)
#घोषणा QSPI_MR_DLYCS(n)                (((n) << 24) & QSPI_MR_DLYCS_MASK)

/* Bitfields in QSPI_SR/QSPI_IER/QSPI_IDR/QSPI_IMR  */
#घोषणा QSPI_SR_RDRF                    BIT(0)
#घोषणा QSPI_SR_TDRE                    BIT(1)
#घोषणा QSPI_SR_TXEMPTY                 BIT(2)
#घोषणा QSPI_SR_OVRES                   BIT(3)
#घोषणा QSPI_SR_CSR                     BIT(8)
#घोषणा QSPI_SR_CSS                     BIT(9)
#घोषणा QSPI_SR_INSTRE                  BIT(10)
#घोषणा QSPI_SR_QSPIENS                 BIT(24)

#घोषणा QSPI_SR_CMD_COMPLETED	(QSPI_SR_INSTRE | QSPI_SR_CSR)

/* Bitfields in QSPI_SCR (Serial Clock Register) */
#घोषणा QSPI_SCR_CPOL                   BIT(0)
#घोषणा QSPI_SCR_CPHA                   BIT(1)
#घोषणा QSPI_SCR_SCBR_MASK              GENMASK(15, 8)
#घोषणा QSPI_SCR_SCBR(n)                (((n) << 8) & QSPI_SCR_SCBR_MASK)
#घोषणा QSPI_SCR_DLYBS_MASK             GENMASK(23, 16)
#घोषणा QSPI_SCR_DLYBS(n)               (((n) << 16) & QSPI_SCR_DLYBS_MASK)

/* Bitfields in QSPI_ICR (Read/Write Inकाष्ठाion Code Register) */
#घोषणा QSPI_ICR_INST_MASK              GENMASK(7, 0)
#घोषणा QSPI_ICR_INST(inst)             (((inst) << 0) & QSPI_ICR_INST_MASK)
#घोषणा QSPI_ICR_OPT_MASK               GENMASK(23, 16)
#घोषणा QSPI_ICR_OPT(opt)               (((opt) << 16) & QSPI_ICR_OPT_MASK)

/* Bitfields in QSPI_IFR (Inकाष्ठाion Frame Register) */
#घोषणा QSPI_IFR_WIDTH_MASK             GENMASK(2, 0)
#घोषणा QSPI_IFR_WIDTH_SINGLE_BIT_SPI   (0 << 0)
#घोषणा QSPI_IFR_WIDTH_DUAL_OUTPUT      (1 << 0)
#घोषणा QSPI_IFR_WIDTH_QUAD_OUTPUT      (2 << 0)
#घोषणा QSPI_IFR_WIDTH_DUAL_IO          (3 << 0)
#घोषणा QSPI_IFR_WIDTH_QUAD_IO          (4 << 0)
#घोषणा QSPI_IFR_WIDTH_DUAL_CMD         (5 << 0)
#घोषणा QSPI_IFR_WIDTH_QUAD_CMD         (6 << 0)
#घोषणा QSPI_IFR_INSTEN                 BIT(4)
#घोषणा QSPI_IFR_ADDREN                 BIT(5)
#घोषणा QSPI_IFR_OPTEN                  BIT(6)
#घोषणा QSPI_IFR_DATAEN                 BIT(7)
#घोषणा QSPI_IFR_OPTL_MASK              GENMASK(9, 8)
#घोषणा QSPI_IFR_OPTL_1BIT              (0 << 8)
#घोषणा QSPI_IFR_OPTL_2BIT              (1 << 8)
#घोषणा QSPI_IFR_OPTL_4BIT              (2 << 8)
#घोषणा QSPI_IFR_OPTL_8BIT              (3 << 8)
#घोषणा QSPI_IFR_ADDRL                  BIT(10)
#घोषणा QSPI_IFR_TFRTYP_MEM		BIT(12)
#घोषणा QSPI_IFR_SAMA5D2_WRITE_TRSFR	BIT(13)
#घोषणा QSPI_IFR_CRM                    BIT(14)
#घोषणा QSPI_IFR_NBDUM_MASK             GENMASK(20, 16)
#घोषणा QSPI_IFR_NBDUM(n)               (((n) << 16) & QSPI_IFR_NBDUM_MASK)
#घोषणा QSPI_IFR_APBTFRTYP_READ		BIT(24)	/* Defined in SAM9X60 */

/* Bitfields in QSPI_SMR (Scrambling Mode Register) */
#घोषणा QSPI_SMR_SCREN                  BIT(0)
#घोषणा QSPI_SMR_RVDIS                  BIT(1)

/* Bitfields in QSPI_WPMR (Write Protection Mode Register) */
#घोषणा QSPI_WPMR_WPEN                  BIT(0)
#घोषणा QSPI_WPMR_WPKEY_MASK            GENMASK(31, 8)
#घोषणा QSPI_WPMR_WPKEY(wpkey)          (((wpkey) << 8) & QSPI_WPMR_WPKEY_MASK)

/* Bitfields in QSPI_WPSR (Write Protection Status Register) */
#घोषणा QSPI_WPSR_WPVS                  BIT(0)
#घोषणा QSPI_WPSR_WPVSRC_MASK           GENMASK(15, 8)
#घोषणा QSPI_WPSR_WPVSRC(src)           (((src) << 8) & QSPI_WPSR_WPVSRC)

काष्ठा aपंचांगel_qspi_caps अणु
	bool has_qspick;
	bool has_ricr;
पूर्ण;

काष्ठा aपंचांगel_qspi अणु
	व्योम __iomem		*regs;
	व्योम __iomem		*mem;
	काष्ठा clk		*pclk;
	काष्ठा clk		*qspick;
	काष्ठा platक्रमm_device	*pdev;
	स्थिर काष्ठा aपंचांगel_qspi_caps *caps;
	resource_माप_प्रकार		mmap_size;
	u32			pending;
	u32			mr;
	u32			scr;
	काष्ठा completion	cmd_completion;
पूर्ण;

काष्ठा aपंचांगel_qspi_mode अणु
	u8 cmd_buswidth;
	u8 addr_buswidth;
	u8 data_buswidth;
	u32 config;
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_qspi_mode aपंचांगel_qspi_modes[] = अणु
	अणु 1, 1, 1, QSPI_IFR_WIDTH_SINGLE_BIT_SPI पूर्ण,
	अणु 1, 1, 2, QSPI_IFR_WIDTH_DUAL_OUTPUT पूर्ण,
	अणु 1, 1, 4, QSPI_IFR_WIDTH_QUAD_OUTPUT पूर्ण,
	अणु 1, 2, 2, QSPI_IFR_WIDTH_DUAL_IO पूर्ण,
	अणु 1, 4, 4, QSPI_IFR_WIDTH_QUAD_IO पूर्ण,
	अणु 2, 2, 2, QSPI_IFR_WIDTH_DUAL_CMD पूर्ण,
	अणु 4, 4, 4, QSPI_IFR_WIDTH_QUAD_CMD पूर्ण,
पूर्ण;

#अगर_घोषित VERBOSE_DEBUG
अटल स्थिर अक्षर *aपंचांगel_qspi_reg_name(u32 offset, अक्षर *पंचांगp, माप_प्रकार sz)
अणु
	चयन (offset) अणु
	हाल QSPI_CR:
		वापस "CR";
	हाल QSPI_MR:
		वापस "MR";
	हाल QSPI_RD:
		वापस "MR";
	हाल QSPI_TD:
		वापस "TD";
	हाल QSPI_SR:
		वापस "SR";
	हाल QSPI_IER:
		वापस "IER";
	हाल QSPI_IDR:
		वापस "IDR";
	हाल QSPI_IMR:
		वापस "IMR";
	हाल QSPI_SCR:
		वापस "SCR";
	हाल QSPI_IAR:
		वापस "IAR";
	हाल QSPI_ICR:
		वापस "ICR/WICR";
	हाल QSPI_IFR:
		वापस "IFR";
	हाल QSPI_RICR:
		वापस "RICR";
	हाल QSPI_SMR:
		वापस "SMR";
	हाल QSPI_SKR:
		वापस "SKR";
	हाल QSPI_WPMR:
		वापस "WPMR";
	हाल QSPI_WPSR:
		वापस "WPSR";
	हाल QSPI_VERSION:
		वापस "VERSION";
	शेष:
		snम_लिखो(पंचांगp, sz, "0x%02x", offset);
		अवरोध;
	पूर्ण

	वापस पंचांगp;
पूर्ण
#पूर्ण_अगर /* VERBOSE_DEBUG */

अटल u32 aपंचांगel_qspi_पढ़ो(काष्ठा aपंचांगel_qspi *aq, u32 offset)
अणु
	u32 value = पढ़ोl_relaxed(aq->regs + offset);

#अगर_घोषित VERBOSE_DEBUG
	अक्षर पंचांगp[8];

	dev_vdbg(&aq->pdev->dev, "read 0x%08x from %s\n", value,
		 aपंचांगel_qspi_reg_name(offset, पंचांगp, माप(पंचांगp)));
#पूर्ण_अगर /* VERBOSE_DEBUG */

	वापस value;
पूर्ण

अटल व्योम aपंचांगel_qspi_ग_लिखो(u32 value, काष्ठा aपंचांगel_qspi *aq, u32 offset)
अणु
#अगर_घोषित VERBOSE_DEBUG
	अक्षर पंचांगp[8];

	dev_vdbg(&aq->pdev->dev, "write 0x%08x into %s\n", value,
		 aपंचांगel_qspi_reg_name(offset, पंचांगp, माप(पंचांगp)));
#पूर्ण_अगर /* VERBOSE_DEBUG */

	ग_लिखोl_relaxed(value, aq->regs + offset);
पूर्ण

अटल अंतरभूत bool aपंचांगel_qspi_is_compatible(स्थिर काष्ठा spi_mem_op *op,
					    स्थिर काष्ठा aपंचांगel_qspi_mode *mode)
अणु
	अगर (op->cmd.buswidth != mode->cmd_buswidth)
		वापस false;

	अगर (op->addr.nbytes && op->addr.buswidth != mode->addr_buswidth)
		वापस false;

	अगर (op->data.nbytes && op->data.buswidth != mode->data_buswidth)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक aपंचांगel_qspi_find_mode(स्थिर काष्ठा spi_mem_op *op)
अणु
	u32 i;

	क्रम (i = 0; i < ARRAY_SIZE(aपंचांगel_qspi_modes); i++)
		अगर (aपंचांगel_qspi_is_compatible(op, &aपंचांगel_qspi_modes[i]))
			वापस i;

	वापस -ENOTSUPP;
पूर्ण

अटल bool aपंचांगel_qspi_supports_op(काष्ठा spi_mem *mem,
				   स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (aपंचांगel_qspi_find_mode(op) < 0)
		वापस false;

	/* special हाल not supported by hardware */
	अगर (op->addr.nbytes == 2 && op->cmd.buswidth != op->addr.buswidth &&
		op->dummy.nbytes == 0)
		वापस false;

	/* DTR ops not supported. */
	अगर (op->cmd.dtr || op->addr.dtr || op->dummy.dtr || op->data.dtr)
		वापस false;
	अगर (op->cmd.nbytes != 1)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक aपंचांगel_qspi_set_cfg(काष्ठा aपंचांगel_qspi *aq,
			      स्थिर काष्ठा spi_mem_op *op, u32 *offset)
अणु
	u32 iar, icr, अगरr;
	u32 dummy_cycles = 0;
	पूर्णांक mode;

	iar = 0;
	icr = QSPI_ICR_INST(op->cmd.opcode);
	अगरr = QSPI_IFR_INSTEN;

	mode = aपंचांगel_qspi_find_mode(op);
	अगर (mode < 0)
		वापस mode;
	अगरr |= aपंचांगel_qspi_modes[mode].config;

	अगर (op->dummy.buswidth && op->dummy.nbytes)
		dummy_cycles = op->dummy.nbytes * 8 / op->dummy.buswidth;

	/*
	 * The controller allows 24 and 32-bit addressing जबतक न_अंकD-flash
	 * requires 16-bit दीर्घ. Handling 8-bit दीर्घ addresses is करोne using
	 * the option field. For the 16-bit addresses, the workaround depends
	 * of the number of requested dummy bits. If there are 8 or more dummy
	 * cycles, the address is shअगरted and sent with the first dummy byte.
	 * Otherwise opcode is disabled and the first byte of the address
	 * contains the command opcode (works only अगर the opcode and address
	 * use the same buswidth). The limitation is when the 16-bit address is
	 * used without enough dummy cycles and the opcode is using a dअगरferent
	 * buswidth than the address.
	 */
	अगर (op->addr.buswidth) अणु
		चयन (op->addr.nbytes) अणु
		हाल 0:
			अवरोध;
		हाल 1:
			अगरr |= QSPI_IFR_OPTEN | QSPI_IFR_OPTL_8BIT;
			icr |= QSPI_ICR_OPT(op->addr.val & 0xff);
			अवरोध;
		हाल 2:
			अगर (dummy_cycles < 8 / op->addr.buswidth) अणु
				अगरr &= ~QSPI_IFR_INSTEN;
				अगरr |= QSPI_IFR_ADDREN;
				iar = (op->cmd.opcode << 16) |
					(op->addr.val & 0xffff);
			पूर्ण अन्यथा अणु
				अगरr |= QSPI_IFR_ADDREN;
				iar = (op->addr.val << 8) & 0xffffff;
				dummy_cycles -= 8 / op->addr.buswidth;
			पूर्ण
			अवरोध;
		हाल 3:
			अगरr |= QSPI_IFR_ADDREN;
			iar = op->addr.val & 0xffffff;
			अवरोध;
		हाल 4:
			अगरr |= QSPI_IFR_ADDREN | QSPI_IFR_ADDRL;
			iar = op->addr.val & 0x7ffffff;
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	/* offset of the data access in the QSPI memory space */
	*offset = iar;

	/* Set number of dummy cycles */
	अगर (dummy_cycles)
		अगरr |= QSPI_IFR_NBDUM(dummy_cycles);

	/* Set data enable and data transfer type. */
	अगर (op->data.nbytes) अणु
		अगरr |= QSPI_IFR_DATAEN;

		अगर (op->addr.nbytes)
			अगरr |= QSPI_IFR_TFRTYP_MEM;
	पूर्ण

	/*
	 * If the QSPI controller is set in regular SPI mode, set it in
	 * Serial Memory Mode (SMM).
	 */
	अगर (aq->mr != QSPI_MR_SMM) अणु
		aपंचांगel_qspi_ग_लिखो(QSPI_MR_SMM, aq, QSPI_MR);
		aq->mr = QSPI_MR_SMM;
	पूर्ण

	/* Clear pending पूर्णांकerrupts */
	(व्योम)aपंचांगel_qspi_पढ़ो(aq, QSPI_SR);

	/* Set QSPI Inकाष्ठाion Frame रेजिस्टरs. */
	अगर (op->addr.nbytes && !op->data.nbytes)
		aपंचांगel_qspi_ग_लिखो(iar, aq, QSPI_IAR);

	अगर (aq->caps->has_ricr) अणु
		अगर (op->data.dir == SPI_MEM_DATA_IN)
			aपंचांगel_qspi_ग_लिखो(icr, aq, QSPI_RICR);
		अन्यथा
			aपंचांगel_qspi_ग_लिखो(icr, aq, QSPI_WICR);
	पूर्ण अन्यथा अणु
		अगर (op->data.nbytes && op->data.dir == SPI_MEM_DATA_OUT)
			अगरr |= QSPI_IFR_SAMA5D2_WRITE_TRSFR;

		aपंचांगel_qspi_ग_लिखो(icr, aq, QSPI_ICR);
	पूर्ण

	aपंचांगel_qspi_ग_लिखो(अगरr, aq, QSPI_IFR);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_qspi_exec_op(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा aपंचांगel_qspi *aq = spi_controller_get_devdata(mem->spi->master);
	u32 sr, offset;
	पूर्णांक err;

	/*
	 * Check अगर the address exceeds the MMIO winकरोw size. An improvement
	 * would be to add support क्रम regular SPI mode and fall back to it
	 * when the flash memories overrun the controller's memory space.
	 */
	अगर (op->addr.val + op->data.nbytes > aq->mmap_size)
		वापस -ENOTSUPP;

	err = aपंचांगel_qspi_set_cfg(aq, op, &offset);
	अगर (err)
		वापस err;

	/* Skip to the final steps अगर there is no data */
	अगर (op->data.nbytes) अणु
		/* Dummy पढ़ो of QSPI_IFR to synchronize APB and AHB accesses */
		(व्योम)aपंचांगel_qspi_पढ़ो(aq, QSPI_IFR);

		/* Send/Receive data */
		अगर (op->data.dir == SPI_MEM_DATA_IN)
			स_नकल_fromio(op->data.buf.in, aq->mem + offset,
				      op->data.nbytes);
		अन्यथा
			स_नकल_toio(aq->mem + offset, op->data.buf.out,
				    op->data.nbytes);

		/* Release the chip-select */
		aपंचांगel_qspi_ग_लिखो(QSPI_CR_LASTXFER, aq, QSPI_CR);
	पूर्ण

	/* Poll INSTRuction End status */
	sr = aपंचांगel_qspi_पढ़ो(aq, QSPI_SR);
	अगर ((sr & QSPI_SR_CMD_COMPLETED) == QSPI_SR_CMD_COMPLETED)
		वापस err;

	/* Wait क्रम INSTRuction End पूर्णांकerrupt */
	reinit_completion(&aq->cmd_completion);
	aq->pending = sr & QSPI_SR_CMD_COMPLETED;
	aपंचांगel_qspi_ग_लिखो(QSPI_SR_CMD_COMPLETED, aq, QSPI_IER);
	अगर (!रुको_क्रम_completion_समयout(&aq->cmd_completion,
					 msecs_to_jअगरfies(1000)))
		err = -ETIMEDOUT;
	aपंचांगel_qspi_ग_लिखो(QSPI_SR_CMD_COMPLETED, aq, QSPI_IDR);

	वापस err;
पूर्ण

अटल स्थिर अक्षर *aपंचांगel_qspi_get_name(काष्ठा spi_mem *spimem)
अणु
	वापस dev_name(spimem->spi->dev.parent);
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops aपंचांगel_qspi_mem_ops = अणु
	.supports_op = aपंचांगel_qspi_supports_op,
	.exec_op = aपंचांगel_qspi_exec_op,
	.get_name = aपंचांगel_qspi_get_name
पूर्ण;

अटल पूर्णांक aपंचांगel_qspi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_controller *ctrl = spi->master;
	काष्ठा aपंचांगel_qspi *aq = spi_controller_get_devdata(ctrl);
	अचिन्हित दीर्घ src_rate;
	u32 scbr;

	अगर (ctrl->busy)
		वापस -EBUSY;

	अगर (!spi->max_speed_hz)
		वापस -EINVAL;

	src_rate = clk_get_rate(aq->pclk);
	अगर (!src_rate)
		वापस -EINVAL;

	/* Compute the QSPI baudrate */
	scbr = DIV_ROUND_UP(src_rate, spi->max_speed_hz);
	अगर (scbr > 0)
		scbr--;

	aq->scr = QSPI_SCR_SCBR(scbr);
	aपंचांगel_qspi_ग_लिखो(aq->scr, aq, QSPI_SCR);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_qspi_init(काष्ठा aपंचांगel_qspi *aq)
अणु
	/* Reset the QSPI controller */
	aपंचांगel_qspi_ग_लिखो(QSPI_CR_SWRST, aq, QSPI_CR);

	/* Set the QSPI controller by शेष in Serial Memory Mode */
	aपंचांगel_qspi_ग_लिखो(QSPI_MR_SMM, aq, QSPI_MR);
	aq->mr = QSPI_MR_SMM;

	/* Enable the QSPI controller */
	aपंचांगel_qspi_ग_लिखो(QSPI_CR_QSPIEN, aq, QSPI_CR);
पूर्ण

अटल irqवापस_t aपंचांगel_qspi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aपंचांगel_qspi *aq = dev_id;
	u32 status, mask, pending;

	status = aपंचांगel_qspi_पढ़ो(aq, QSPI_SR);
	mask = aपंचांगel_qspi_पढ़ो(aq, QSPI_IMR);
	pending = status & mask;

	अगर (!pending)
		वापस IRQ_NONE;

	aq->pending |= pending;
	अगर ((aq->pending & QSPI_SR_CMD_COMPLETED) == QSPI_SR_CMD_COMPLETED)
		complete(&aq->cmd_completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक aपंचांगel_qspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctrl;
	काष्ठा aपंचांगel_qspi *aq;
	काष्ठा resource *res;
	पूर्णांक irq, err = 0;

	ctrl = devm_spi_alloc_master(&pdev->dev, माप(*aq));
	अगर (!ctrl)
		वापस -ENOMEM;

	ctrl->mode_bits = SPI_RX_DUAL | SPI_RX_QUAD | SPI_TX_DUAL | SPI_TX_QUAD;
	ctrl->setup = aपंचांगel_qspi_setup;
	ctrl->bus_num = -1;
	ctrl->mem_ops = &aपंचांगel_qspi_mem_ops;
	ctrl->num_chipselect = 1;
	ctrl->dev.of_node = pdev->dev.of_node;
	platक्रमm_set_drvdata(pdev, ctrl);

	aq = spi_controller_get_devdata(ctrl);

	init_completion(&aq->cmd_completion);
	aq->pdev = pdev;

	/* Map the रेजिस्टरs */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "qspi_base");
	aq->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(aq->regs)) अणु
		dev_err(&pdev->dev, "missing registers\n");
		वापस PTR_ERR(aq->regs);
	पूर्ण

	/* Map the AHB memory */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "qspi_mmap");
	aq->mem = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(aq->mem)) अणु
		dev_err(&pdev->dev, "missing AHB memory\n");
		वापस PTR_ERR(aq->mem);
	पूर्ण

	aq->mmap_size = resource_size(res);

	/* Get the peripheral घड़ी */
	aq->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(aq->pclk))
		aq->pclk = devm_clk_get(&pdev->dev, शून्य);

	अगर (IS_ERR(aq->pclk)) अणु
		dev_err(&pdev->dev, "missing peripheral clock\n");
		वापस PTR_ERR(aq->pclk);
	पूर्ण

	/* Enable the peripheral घड़ी */
	err = clk_prepare_enable(aq->pclk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable the peripheral clock\n");
		वापस err;
	पूर्ण

	aq->caps = of_device_get_match_data(&pdev->dev);
	अगर (!aq->caps) अणु
		dev_err(&pdev->dev, "Could not retrieve QSPI caps\n");
		err = -EINVAL;
		जाओ disable_pclk;
	पूर्ण

	अगर (aq->caps->has_qspick) अणु
		/* Get the QSPI प्रणाली घड़ी */
		aq->qspick = devm_clk_get(&pdev->dev, "qspick");
		अगर (IS_ERR(aq->qspick)) अणु
			dev_err(&pdev->dev, "missing system clock\n");
			err = PTR_ERR(aq->qspick);
			जाओ disable_pclk;
		पूर्ण

		/* Enable the QSPI प्रणाली घड़ी */
		err = clk_prepare_enable(aq->qspick);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"failed to enable the QSPI system clock\n");
			जाओ disable_pclk;
		पूर्ण
	पूर्ण

	/* Request the IRQ */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		err = irq;
		जाओ disable_qspick;
	पूर्ण
	err = devm_request_irq(&pdev->dev, irq, aपंचांगel_qspi_पूर्णांकerrupt,
			       0, dev_name(&pdev->dev), aq);
	अगर (err)
		जाओ disable_qspick;

	aपंचांगel_qspi_init(aq);

	err = spi_रेजिस्टर_controller(ctrl);
	अगर (err)
		जाओ disable_qspick;

	वापस 0;

disable_qspick:
	clk_disable_unprepare(aq->qspick);
disable_pclk:
	clk_disable_unprepare(aq->pclk);

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_qspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctrl = platक्रमm_get_drvdata(pdev);
	काष्ठा aपंचांगel_qspi *aq = spi_controller_get_devdata(ctrl);

	spi_unरेजिस्टर_controller(ctrl);
	aपंचांगel_qspi_ग_लिखो(QSPI_CR_QSPIDIS, aq, QSPI_CR);
	clk_disable_unprepare(aq->qspick);
	clk_disable_unprepare(aq->pclk);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused aपंचांगel_qspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctrl = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_qspi *aq = spi_controller_get_devdata(ctrl);

	aपंचांगel_qspi_ग_लिखो(QSPI_CR_QSPIDIS, aq, QSPI_CR);
	clk_disable_unprepare(aq->qspick);
	clk_disable_unprepare(aq->pclk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused aपंचांगel_qspi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctrl = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_qspi *aq = spi_controller_get_devdata(ctrl);

	clk_prepare_enable(aq->pclk);
	clk_prepare_enable(aq->qspick);

	aपंचांगel_qspi_init(aq);

	aपंचांगel_qspi_ग_लिखो(aq->scr, aq, QSPI_SCR);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(aपंचांगel_qspi_pm_ops, aपंचांगel_qspi_suspend,
			 aपंचांगel_qspi_resume);

अटल स्थिर काष्ठा aपंचांगel_qspi_caps aपंचांगel_sama5d2_qspi_caps = अणुपूर्ण;

अटल स्थिर काष्ठा aपंचांगel_qspi_caps aपंचांगel_sam9x60_qspi_caps = अणु
	.has_qspick = true,
	.has_ricr = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_qspi_dt_ids[] = अणु
	अणु
		.compatible = "atmel,sama5d2-qspi",
		.data = &aपंचांगel_sama5d2_qspi_caps,
	पूर्ण,
	अणु
		.compatible = "microchip,sam9x60-qspi",
		.data = &aपंचांगel_sam9x60_qspi_caps,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aपंचांगel_qspi_dt_ids);

अटल काष्ठा platक्रमm_driver aपंचांगel_qspi_driver = अणु
	.driver = अणु
		.name	= "atmel_qspi",
		.of_match_table	= aपंचांगel_qspi_dt_ids,
		.pm	= &aपंचांगel_qspi_pm_ops,
	पूर्ण,
	.probe		= aपंचांगel_qspi_probe,
	.हटाओ		= aपंचांगel_qspi_हटाओ,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_qspi_driver);

MODULE_AUTHOR("Cyrille Pitchen <cyrille.pitchen@atmel.com>");
MODULE_AUTHOR("Piotr Bugalski <bugalski.piotr@gmail.com");
MODULE_DESCRIPTION("Atmel QSPI Controller driver");
MODULE_LICENSE("GPL v2");
