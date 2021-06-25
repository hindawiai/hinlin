<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel PCH/PCU SPI flash driver.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sizes.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/spi-nor.h>

#समावेश "intel-spi.h"

/* Offsets are from @ispi->base */
#घोषणा BFPREG				0x00

#घोषणा HSFSTS_CTL			0x04
#घोषणा HSFSTS_CTL_FSMIE		BIT(31)
#घोषणा HSFSTS_CTL_FDBC_SHIFT		24
#घोषणा HSFSTS_CTL_FDBC_MASK		(0x3f << HSFSTS_CTL_FDBC_SHIFT)

#घोषणा HSFSTS_CTL_FCYCLE_SHIFT		17
#घोषणा HSFSTS_CTL_FCYCLE_MASK		(0x0f << HSFSTS_CTL_FCYCLE_SHIFT)
/* HW sequencer opcodes */
#घोषणा HSFSTS_CTL_FCYCLE_READ		(0x00 << HSFSTS_CTL_FCYCLE_SHIFT)
#घोषणा HSFSTS_CTL_FCYCLE_WRITE		(0x02 << HSFSTS_CTL_FCYCLE_SHIFT)
#घोषणा HSFSTS_CTL_FCYCLE_ERASE		(0x03 << HSFSTS_CTL_FCYCLE_SHIFT)
#घोषणा HSFSTS_CTL_FCYCLE_ERASE_64K	(0x04 << HSFSTS_CTL_FCYCLE_SHIFT)
#घोषणा HSFSTS_CTL_FCYCLE_RDID		(0x06 << HSFSTS_CTL_FCYCLE_SHIFT)
#घोषणा HSFSTS_CTL_FCYCLE_WRSR		(0x07 << HSFSTS_CTL_FCYCLE_SHIFT)
#घोषणा HSFSTS_CTL_FCYCLE_RDSR		(0x08 << HSFSTS_CTL_FCYCLE_SHIFT)

#घोषणा HSFSTS_CTL_FGO			BIT(16)
#घोषणा HSFSTS_CTL_FLOCKDN		BIT(15)
#घोषणा HSFSTS_CTL_FDV			BIT(14)
#घोषणा HSFSTS_CTL_SCIP			BIT(5)
#घोषणा HSFSTS_CTL_AEL			BIT(2)
#घोषणा HSFSTS_CTL_FCERR		BIT(1)
#घोषणा HSFSTS_CTL_FDONE		BIT(0)

#घोषणा FADDR				0x08
#घोषणा DLOCK				0x0c
#घोषणा FDATA(n)			(0x10 + ((n) * 4))

#घोषणा FRACC				0x50

#घोषणा FREG(n)				(0x54 + ((n) * 4))
#घोषणा FREG_BASE_MASK			0x3fff
#घोषणा FREG_LIMIT_SHIFT		16
#घोषणा FREG_LIMIT_MASK			(0x03fff << FREG_LIMIT_SHIFT)

/* Offset is from @ispi->pregs */
#घोषणा PR(n)				((n) * 4)
#घोषणा PR_WPE				BIT(31)
#घोषणा PR_LIMIT_SHIFT			16
#घोषणा PR_LIMIT_MASK			(0x3fff << PR_LIMIT_SHIFT)
#घोषणा PR_RPE				BIT(15)
#घोषणा PR_BASE_MASK			0x3fff

/* Offsets are from @ispi->sregs */
#घोषणा SSFSTS_CTL			0x00
#घोषणा SSFSTS_CTL_FSMIE		BIT(23)
#घोषणा SSFSTS_CTL_DS			BIT(22)
#घोषणा SSFSTS_CTL_DBC_SHIFT		16
#घोषणा SSFSTS_CTL_SPOP			BIT(11)
#घोषणा SSFSTS_CTL_ACS			BIT(10)
#घोषणा SSFSTS_CTL_SCGO			BIT(9)
#घोषणा SSFSTS_CTL_COP_SHIFT		12
#घोषणा SSFSTS_CTL_FRS			BIT(7)
#घोषणा SSFSTS_CTL_DOFRS		BIT(6)
#घोषणा SSFSTS_CTL_AEL			BIT(4)
#घोषणा SSFSTS_CTL_FCERR		BIT(3)
#घोषणा SSFSTS_CTL_FDONE		BIT(2)
#घोषणा SSFSTS_CTL_SCIP			BIT(0)

#घोषणा PREOP_OPTYPE			0x04
#घोषणा OPMENU0				0x08
#घोषणा OPMENU1				0x0c

#घोषणा OPTYPE_READ_NO_ADDR		0
#घोषणा OPTYPE_WRITE_NO_ADDR		1
#घोषणा OPTYPE_READ_WITH_ADDR		2
#घोषणा OPTYPE_WRITE_WITH_ADDR		3

/* CPU specअगरics */
#घोषणा BYT_PR				0x74
#घोषणा BYT_SSFSTS_CTL			0x90
#घोषणा BYT_BCR				0xfc
#घोषणा BYT_BCR_WPD			BIT(0)
#घोषणा BYT_FREG_NUM			5
#घोषणा BYT_PR_NUM			5

#घोषणा LPT_PR				0x74
#घोषणा LPT_SSFSTS_CTL			0x90
#घोषणा LPT_FREG_NUM			5
#घोषणा LPT_PR_NUM			5

#घोषणा BXT_PR				0x84
#घोषणा BXT_SSFSTS_CTL			0xa0
#घोषणा BXT_FREG_NUM			12
#घोषणा BXT_PR_NUM			6

#घोषणा CNL_PR				0x84
#घोषणा CNL_FREG_NUM			6
#घोषणा CNL_PR_NUM			5

#घोषणा LVSCC				0xc4
#घोषणा UVSCC				0xc8
#घोषणा ERASE_OPCODE_SHIFT		8
#घोषणा ERASE_OPCODE_MASK		(0xff << ERASE_OPCODE_SHIFT)
#घोषणा ERASE_64K_OPCODE_SHIFT		16
#घोषणा ERASE_64K_OPCODE_MASK		(0xff << ERASE_OPCODE_SHIFT)

#घोषणा INTEL_SPI_TIMEOUT		5000 /* ms */
#घोषणा INTEL_SPI_FIFO_SZ		64

/**
 * काष्ठा पूर्णांकel_spi - Driver निजी data
 * @dev: Device poपूर्णांकer
 * @info: Poपूर्णांकer to board specअगरic info
 * @nor: SPI NOR layer काष्ठाure
 * @base: Beginning of MMIO space
 * @pregs: Start of protection रेजिस्टरs
 * @sregs: Start of software sequencer रेजिस्टरs
 * @nregions: Maximum number of regions
 * @pr_num: Maximum number of रक्षित range रेजिस्टरs
 * @ग_लिखोable: Is the chip ग_लिखोable
 * @locked: Is SPI setting locked
 * @swseq_reg: Use SW sequencer in रेजिस्टर पढ़ोs/ग_लिखोs
 * @swseq_erase: Use SW sequencer in erase operation
 * @erase_64k: 64k erase supported
 * @atomic_preopcode: Holds preopcode when atomic sequence is requested
 * @opcodes: Opcodes which are supported. This are programmed by BIOS
 *           beक्रमe it locks करोwn the controller.
 */
काष्ठा पूर्णांकel_spi अणु
	काष्ठा device *dev;
	स्थिर काष्ठा पूर्णांकel_spi_boardinfo *info;
	काष्ठा spi_nor nor;
	व्योम __iomem *base;
	व्योम __iomem *pregs;
	व्योम __iomem *sregs;
	माप_प्रकार nregions;
	माप_प्रकार pr_num;
	bool ग_लिखोable;
	bool locked;
	bool swseq_reg;
	bool swseq_erase;
	bool erase_64k;
	u8 atomic_preopcode;
	u8 opcodes[8];
पूर्ण;

अटल bool ग_लिखोable;
module_param(ग_लिखोable, bool, 0);
MODULE_PARM_DESC(ग_लिखोable, "Enable write access to SPI flash chip (default=0)");

अटल व्योम पूर्णांकel_spi_dump_regs(काष्ठा पूर्णांकel_spi *ispi)
अणु
	u32 value;
	पूर्णांक i;

	dev_dbg(ispi->dev, "BFPREG=0x%08x\n", पढ़ोl(ispi->base + BFPREG));

	value = पढ़ोl(ispi->base + HSFSTS_CTL);
	dev_dbg(ispi->dev, "HSFSTS_CTL=0x%08x\n", value);
	अगर (value & HSFSTS_CTL_FLOCKDN)
		dev_dbg(ispi->dev, "-> Locked\n");

	dev_dbg(ispi->dev, "FADDR=0x%08x\n", पढ़ोl(ispi->base + FADDR));
	dev_dbg(ispi->dev, "DLOCK=0x%08x\n", पढ़ोl(ispi->base + DLOCK));

	क्रम (i = 0; i < 16; i++)
		dev_dbg(ispi->dev, "FDATA(%d)=0x%08x\n",
			i, पढ़ोl(ispi->base + FDATA(i)));

	dev_dbg(ispi->dev, "FRACC=0x%08x\n", पढ़ोl(ispi->base + FRACC));

	क्रम (i = 0; i < ispi->nregions; i++)
		dev_dbg(ispi->dev, "FREG(%d)=0x%08x\n", i,
			पढ़ोl(ispi->base + FREG(i)));
	क्रम (i = 0; i < ispi->pr_num; i++)
		dev_dbg(ispi->dev, "PR(%d)=0x%08x\n", i,
			पढ़ोl(ispi->pregs + PR(i)));

	अगर (ispi->sregs) अणु
		value = पढ़ोl(ispi->sregs + SSFSTS_CTL);
		dev_dbg(ispi->dev, "SSFSTS_CTL=0x%08x\n", value);
		dev_dbg(ispi->dev, "PREOP_OPTYPE=0x%08x\n",
			पढ़ोl(ispi->sregs + PREOP_OPTYPE));
		dev_dbg(ispi->dev, "OPMENU0=0x%08x\n",
			पढ़ोl(ispi->sregs + OPMENU0));
		dev_dbg(ispi->dev, "OPMENU1=0x%08x\n",
			पढ़ोl(ispi->sregs + OPMENU1));
	पूर्ण

	अगर (ispi->info->type == INTEL_SPI_BYT)
		dev_dbg(ispi->dev, "BCR=0x%08x\n", पढ़ोl(ispi->base + BYT_BCR));

	dev_dbg(ispi->dev, "LVSCC=0x%08x\n", पढ़ोl(ispi->base + LVSCC));
	dev_dbg(ispi->dev, "UVSCC=0x%08x\n", पढ़ोl(ispi->base + UVSCC));

	dev_dbg(ispi->dev, "Protected regions:\n");
	क्रम (i = 0; i < ispi->pr_num; i++) अणु
		u32 base, limit;

		value = पढ़ोl(ispi->pregs + PR(i));
		अगर (!(value & (PR_WPE | PR_RPE)))
			जारी;

		limit = (value & PR_LIMIT_MASK) >> PR_LIMIT_SHIFT;
		base = value & PR_BASE_MASK;

		dev_dbg(ispi->dev, " %02d base: 0x%08x limit: 0x%08x [%c%c]\n",
			 i, base << 12, (limit << 12) | 0xfff,
			 value & PR_WPE ? 'W' : '.',
			 value & PR_RPE ? 'R' : '.');
	पूर्ण

	dev_dbg(ispi->dev, "Flash regions:\n");
	क्रम (i = 0; i < ispi->nregions; i++) अणु
		u32 region, base, limit;

		region = पढ़ोl(ispi->base + FREG(i));
		base = region & FREG_BASE_MASK;
		limit = (region & FREG_LIMIT_MASK) >> FREG_LIMIT_SHIFT;

		अगर (base >= limit || (i > 0 && limit == 0))
			dev_dbg(ispi->dev, " %02d disabled\n", i);
		अन्यथा
			dev_dbg(ispi->dev, " %02d base: 0x%08x limit: 0x%08x\n",
				 i, base << 12, (limit << 12) | 0xfff);
	पूर्ण

	dev_dbg(ispi->dev, "Using %cW sequencer for register access\n",
		ispi->swseq_reg ? 'S' : 'H');
	dev_dbg(ispi->dev, "Using %cW sequencer for erase operation\n",
		ispi->swseq_erase ? 'S' : 'H');
पूर्ण

/* Reads max INTEL_SPI_FIFO_SZ bytes from the device fअगरo */
अटल पूर्णांक पूर्णांकel_spi_पढ़ो_block(काष्ठा पूर्णांकel_spi *ispi, व्योम *buf, माप_प्रकार size)
अणु
	माप_प्रकार bytes;
	पूर्णांक i = 0;

	अगर (size > INTEL_SPI_FIFO_SZ)
		वापस -EINVAL;

	जबतक (size > 0) अणु
		bytes = min_t(माप_प्रकार, size, 4);
		स_नकल_fromio(buf, ispi->base + FDATA(i), bytes);
		size -= bytes;
		buf += bytes;
		i++;
	पूर्ण

	वापस 0;
पूर्ण

/* Writes max INTEL_SPI_FIFO_SZ bytes to the device fअगरo */
अटल पूर्णांक पूर्णांकel_spi_ग_लिखो_block(काष्ठा पूर्णांकel_spi *ispi, स्थिर व्योम *buf,
				 माप_प्रकार size)
अणु
	माप_प्रकार bytes;
	पूर्णांक i = 0;

	अगर (size > INTEL_SPI_FIFO_SZ)
		वापस -EINVAL;

	जबतक (size > 0) अणु
		bytes = min_t(माप_प्रकार, size, 4);
		स_नकल_toio(ispi->base + FDATA(i), buf, bytes);
		size -= bytes;
		buf += bytes;
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_spi_रुको_hw_busy(काष्ठा पूर्णांकel_spi *ispi)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout(ispi->base + HSFSTS_CTL, val,
				  !(val & HSFSTS_CTL_SCIP), 0,
				  INTEL_SPI_TIMEOUT * 1000);
पूर्ण

अटल पूर्णांक पूर्णांकel_spi_रुको_sw_busy(काष्ठा पूर्णांकel_spi *ispi)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout(ispi->sregs + SSFSTS_CTL, val,
				  !(val & SSFSTS_CTL_SCIP), 0,
				  INTEL_SPI_TIMEOUT * 1000);
पूर्ण

अटल पूर्णांक पूर्णांकel_spi_init(काष्ठा पूर्णांकel_spi *ispi)
अणु
	u32 opmenu0, opmenu1, lvscc, uvscc, val;
	पूर्णांक i;

	चयन (ispi->info->type) अणु
	हाल INTEL_SPI_BYT:
		ispi->sregs = ispi->base + BYT_SSFSTS_CTL;
		ispi->pregs = ispi->base + BYT_PR;
		ispi->nregions = BYT_FREG_NUM;
		ispi->pr_num = BYT_PR_NUM;
		ispi->swseq_reg = true;

		अगर (ग_लिखोable) अणु
			/* Disable ग_लिखो protection */
			val = पढ़ोl(ispi->base + BYT_BCR);
			अगर (!(val & BYT_BCR_WPD)) अणु
				val |= BYT_BCR_WPD;
				ग_लिखोl(val, ispi->base + BYT_BCR);
				val = पढ़ोl(ispi->base + BYT_BCR);
			पूर्ण

			ispi->ग_लिखोable = !!(val & BYT_BCR_WPD);
		पूर्ण

		अवरोध;

	हाल INTEL_SPI_LPT:
		ispi->sregs = ispi->base + LPT_SSFSTS_CTL;
		ispi->pregs = ispi->base + LPT_PR;
		ispi->nregions = LPT_FREG_NUM;
		ispi->pr_num = LPT_PR_NUM;
		ispi->swseq_reg = true;
		अवरोध;

	हाल INTEL_SPI_BXT:
		ispi->sregs = ispi->base + BXT_SSFSTS_CTL;
		ispi->pregs = ispi->base + BXT_PR;
		ispi->nregions = BXT_FREG_NUM;
		ispi->pr_num = BXT_PR_NUM;
		ispi->erase_64k = true;
		अवरोध;

	हाल INTEL_SPI_CNL:
		ispi->sregs = शून्य;
		ispi->pregs = ispi->base + CNL_PR;
		ispi->nregions = CNL_FREG_NUM;
		ispi->pr_num = CNL_PR_NUM;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Disable #SMI generation from HW sequencer */
	val = पढ़ोl(ispi->base + HSFSTS_CTL);
	val &= ~HSFSTS_CTL_FSMIE;
	ग_लिखोl(val, ispi->base + HSFSTS_CTL);

	/*
	 * Determine whether erase operation should use HW or SW sequencer.
	 *
	 * The HW sequencer has a predefined list of opcodes, with only the
	 * erase opcode being programmable in LVSCC and UVSCC रेजिस्टरs.
	 * If these रेजिस्टरs करोn't contain a valid erase opcode, erase
	 * cannot be करोne using HW sequencer.
	 */
	lvscc = पढ़ोl(ispi->base + LVSCC);
	uvscc = पढ़ोl(ispi->base + UVSCC);
	अगर (!(lvscc & ERASE_OPCODE_MASK) || !(uvscc & ERASE_OPCODE_MASK))
		ispi->swseq_erase = true;
	/* SPI controller on Intel BXT supports 64K erase opcode */
	अगर (ispi->info->type == INTEL_SPI_BXT && !ispi->swseq_erase)
		अगर (!(lvscc & ERASE_64K_OPCODE_MASK) ||
		    !(uvscc & ERASE_64K_OPCODE_MASK))
			ispi->erase_64k = false;

	अगर (ispi->sregs == शून्य && (ispi->swseq_reg || ispi->swseq_erase)) अणु
		dev_err(ispi->dev, "software sequencer not supported, but required\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Some controllers can only करो basic operations using hardware
	 * sequencer. All other operations are supposed to be carried out
	 * using software sequencer.
	 */
	अगर (ispi->swseq_reg) अणु
		/* Disable #SMI generation from SW sequencer */
		val = पढ़ोl(ispi->sregs + SSFSTS_CTL);
		val &= ~SSFSTS_CTL_FSMIE;
		ग_लिखोl(val, ispi->sregs + SSFSTS_CTL);
	पूर्ण

	/* Check controller's lock status */
	val = पढ़ोl(ispi->base + HSFSTS_CTL);
	ispi->locked = !!(val & HSFSTS_CTL_FLOCKDN);

	अगर (ispi->locked && ispi->sregs) अणु
		/*
		 * BIOS programs allowed opcodes and then locks करोwn the
		 * रेजिस्टर. So पढ़ो back what opcodes it decided to support.
		 * That's the set we are going to support as well.
		 */
		opmenu0 = पढ़ोl(ispi->sregs + OPMENU0);
		opmenu1 = पढ़ोl(ispi->sregs + OPMENU1);

		अगर (opmenu0 && opmenu1) अणु
			क्रम (i = 0; i < ARRAY_SIZE(ispi->opcodes) / 2; i++) अणु
				ispi->opcodes[i] = opmenu0 >> i * 8;
				ispi->opcodes[i + 4] = opmenu1 >> i * 8;
			पूर्ण
		पूर्ण
	पूर्ण

	पूर्णांकel_spi_dump_regs(ispi);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_spi_opcode_index(काष्ठा पूर्णांकel_spi *ispi, u8 opcode, पूर्णांक optype)
अणु
	पूर्णांक i;
	पूर्णांक preop;

	अगर (ispi->locked) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ispi->opcodes); i++)
			अगर (ispi->opcodes[i] == opcode)
				वापस i;

		वापस -EINVAL;
	पूर्ण

	/* The lock is off, so just use index 0 */
	ग_लिखोl(opcode, ispi->sregs + OPMENU0);
	preop = पढ़ोw(ispi->sregs + PREOP_OPTYPE);
	ग_लिखोl(optype << 16 | preop, ispi->sregs + PREOP_OPTYPE);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_spi_hw_cycle(काष्ठा पूर्णांकel_spi *ispi, u8 opcode, माप_प्रकार len)
अणु
	u32 val, status;
	पूर्णांक ret;

	val = पढ़ोl(ispi->base + HSFSTS_CTL);
	val &= ~(HSFSTS_CTL_FCYCLE_MASK | HSFSTS_CTL_FDBC_MASK);

	चयन (opcode) अणु
	हाल SPINOR_OP_RDID:
		val |= HSFSTS_CTL_FCYCLE_RDID;
		अवरोध;
	हाल SPINOR_OP_WRSR:
		val |= HSFSTS_CTL_FCYCLE_WRSR;
		अवरोध;
	हाल SPINOR_OP_RDSR:
		val |= HSFSTS_CTL_FCYCLE_RDSR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (len > INTEL_SPI_FIFO_SZ)
		वापस -EINVAL;

	val |= (len - 1) << HSFSTS_CTL_FDBC_SHIFT;
	val |= HSFSTS_CTL_FCERR | HSFSTS_CTL_FDONE;
	val |= HSFSTS_CTL_FGO;
	ग_लिखोl(val, ispi->base + HSFSTS_CTL);

	ret = पूर्णांकel_spi_रुको_hw_busy(ispi);
	अगर (ret)
		वापस ret;

	status = पढ़ोl(ispi->base + HSFSTS_CTL);
	अगर (status & HSFSTS_CTL_FCERR)
		वापस -EIO;
	अन्यथा अगर (status & HSFSTS_CTL_AEL)
		वापस -EACCES;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_spi_sw_cycle(काष्ठा पूर्णांकel_spi *ispi, u8 opcode, माप_प्रकार len,
			      पूर्णांक optype)
अणु
	u32 val = 0, status;
	u8 atomic_preopcode;
	पूर्णांक ret;

	ret = पूर्णांकel_spi_opcode_index(ispi, opcode, optype);
	अगर (ret < 0)
		वापस ret;

	अगर (len > INTEL_SPI_FIFO_SZ)
		वापस -EINVAL;

	/*
	 * Always clear it after each SW sequencer operation regardless
	 * of whether it is successful or not.
	 */
	atomic_preopcode = ispi->atomic_preopcode;
	ispi->atomic_preopcode = 0;

	/* Only mark 'Data Cycle' bit when there is data to be transferred */
	अगर (len > 0)
		val = ((len - 1) << SSFSTS_CTL_DBC_SHIFT) | SSFSTS_CTL_DS;
	val |= ret << SSFSTS_CTL_COP_SHIFT;
	val |= SSFSTS_CTL_FCERR | SSFSTS_CTL_FDONE;
	val |= SSFSTS_CTL_SCGO;
	अगर (atomic_preopcode) अणु
		u16 preop;

		चयन (optype) अणु
		हाल OPTYPE_WRITE_NO_ADDR:
		हाल OPTYPE_WRITE_WITH_ADDR:
			/* Pick matching preopcode क्रम the atomic sequence */
			preop = पढ़ोw(ispi->sregs + PREOP_OPTYPE);
			अगर ((preop & 0xff) == atomic_preopcode)
				; /* Do nothing */
			अन्यथा अगर ((preop >> 8) == atomic_preopcode)
				val |= SSFSTS_CTL_SPOP;
			अन्यथा
				वापस -EINVAL;

			/* Enable atomic sequence */
			val |= SSFSTS_CTL_ACS;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

	पूर्ण
	ग_लिखोl(val, ispi->sregs + SSFSTS_CTL);

	ret = पूर्णांकel_spi_रुको_sw_busy(ispi);
	अगर (ret)
		वापस ret;

	status = पढ़ोl(ispi->sregs + SSFSTS_CTL);
	अगर (status & SSFSTS_CTL_FCERR)
		वापस -EIO;
	अन्यथा अगर (status & SSFSTS_CTL_AEL)
		वापस -EACCES;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_spi_पढ़ो_reg(काष्ठा spi_nor *nor, u8 opcode, u8 *buf,
			      माप_प्रकार len)
अणु
	काष्ठा पूर्णांकel_spi *ispi = nor->priv;
	पूर्णांक ret;

	/* Address of the first chip */
	ग_लिखोl(0, ispi->base + FADDR);

	अगर (ispi->swseq_reg)
		ret = पूर्णांकel_spi_sw_cycle(ispi, opcode, len,
					 OPTYPE_READ_NO_ADDR);
	अन्यथा
		ret = पूर्णांकel_spi_hw_cycle(ispi, opcode, len);

	अगर (ret)
		वापस ret;

	वापस पूर्णांकel_spi_पढ़ो_block(ispi, buf, len);
पूर्ण

अटल पूर्णांक पूर्णांकel_spi_ग_लिखो_reg(काष्ठा spi_nor *nor, u8 opcode, स्थिर u8 *buf,
			       माप_प्रकार len)
अणु
	काष्ठा पूर्णांकel_spi *ispi = nor->priv;
	पूर्णांक ret;

	/*
	 * This is handled with atomic operation and preop code in Intel
	 * controller so we only verअगरy that it is available. If the
	 * controller is not locked, program the opcode to the PREOP
	 * रेजिस्टर क्रम later use.
	 *
	 * When hardware sequencer is used there is no need to program
	 * any opcodes (it handles them स्वतःmatically as part of a command).
	 */
	अगर (opcode == SPINOR_OP_WREN) अणु
		u16 preop;

		अगर (!ispi->swseq_reg)
			वापस 0;

		preop = पढ़ोw(ispi->sregs + PREOP_OPTYPE);
		अगर ((preop & 0xff) != opcode && (preop >> 8) != opcode) अणु
			अगर (ispi->locked)
				वापस -EINVAL;
			ग_लिखोl(opcode, ispi->sregs + PREOP_OPTYPE);
		पूर्ण

		/*
		 * This enables atomic sequence on next SW sycle. Will
		 * be cleared after next operation.
		 */
		ispi->atomic_preopcode = opcode;
		वापस 0;
	पूर्ण

	/*
	 * We hope that HW sequencer will करो the right thing स्वतःmatically and
	 * with the SW sequencer we cannot use preopcode anyway, so just ignore
	 * the Write Disable operation and pretend it was completed
	 * successfully.
	 */
	अगर (opcode == SPINOR_OP_WRDI)
		वापस 0;

	ग_लिखोl(0, ispi->base + FADDR);

	/* Write the value beक्रमehand */
	ret = पूर्णांकel_spi_ग_लिखो_block(ispi, buf, len);
	अगर (ret)
		वापस ret;

	अगर (ispi->swseq_reg)
		वापस पूर्णांकel_spi_sw_cycle(ispi, opcode, len,
					  OPTYPE_WRITE_NO_ADDR);
	वापस पूर्णांकel_spi_hw_cycle(ispi, opcode, len);
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_spi_पढ़ो(काष्ठा spi_nor *nor, loff_t from, माप_प्रकार len,
			      u_अक्षर *पढ़ो_buf)
अणु
	काष्ठा पूर्णांकel_spi *ispi = nor->priv;
	माप_प्रकार block_size, retlen = 0;
	u32 val, status;
	sमाप_प्रकार ret;

	/*
	 * Atomic sequence is not expected with HW sequencer पढ़ोs. Make
	 * sure it is cleared regardless.
	 */
	अगर (WARN_ON_ONCE(ispi->atomic_preopcode))
		ispi->atomic_preopcode = 0;

	चयन (nor->पढ़ो_opcode) अणु
	हाल SPINOR_OP_READ:
	हाल SPINOR_OP_READ_FAST:
	हाल SPINOR_OP_READ_4B:
	हाल SPINOR_OP_READ_FAST_4B:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	जबतक (len > 0) अणु
		block_size = min_t(माप_प्रकार, len, INTEL_SPI_FIFO_SZ);

		/* Read cannot cross 4K boundary */
		block_size = min_t(loff_t, from + block_size,
				   round_up(from + 1, SZ_4K)) - from;

		ग_लिखोl(from, ispi->base + FADDR);

		val = पढ़ोl(ispi->base + HSFSTS_CTL);
		val &= ~(HSFSTS_CTL_FDBC_MASK | HSFSTS_CTL_FCYCLE_MASK);
		val |= HSFSTS_CTL_AEL | HSFSTS_CTL_FCERR | HSFSTS_CTL_FDONE;
		val |= (block_size - 1) << HSFSTS_CTL_FDBC_SHIFT;
		val |= HSFSTS_CTL_FCYCLE_READ;
		val |= HSFSTS_CTL_FGO;
		ग_लिखोl(val, ispi->base + HSFSTS_CTL);

		ret = पूर्णांकel_spi_रुको_hw_busy(ispi);
		अगर (ret)
			वापस ret;

		status = पढ़ोl(ispi->base + HSFSTS_CTL);
		अगर (status & HSFSTS_CTL_FCERR)
			ret = -EIO;
		अन्यथा अगर (status & HSFSTS_CTL_AEL)
			ret = -EACCES;

		अगर (ret < 0) अणु
			dev_err(ispi->dev, "read error: %llx: %#x\n", from,
				status);
			वापस ret;
		पूर्ण

		ret = पूर्णांकel_spi_पढ़ो_block(ispi, पढ़ो_buf, block_size);
		अगर (ret)
			वापस ret;

		len -= block_size;
		from += block_size;
		retlen += block_size;
		पढ़ो_buf += block_size;
	पूर्ण

	वापस retlen;
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_spi_ग_लिखो(काष्ठा spi_nor *nor, loff_t to, माप_प्रकार len,
			       स्थिर u_अक्षर *ग_लिखो_buf)
अणु
	काष्ठा पूर्णांकel_spi *ispi = nor->priv;
	माप_प्रकार block_size, retlen = 0;
	u32 val, status;
	sमाप_प्रकार ret;

	/* Not needed with HW sequencer ग_लिखो, make sure it is cleared */
	ispi->atomic_preopcode = 0;

	जबतक (len > 0) अणु
		block_size = min_t(माप_प्रकार, len, INTEL_SPI_FIFO_SZ);

		/* Write cannot cross 4K boundary */
		block_size = min_t(loff_t, to + block_size,
				   round_up(to + 1, SZ_4K)) - to;

		ग_लिखोl(to, ispi->base + FADDR);

		val = पढ़ोl(ispi->base + HSFSTS_CTL);
		val &= ~(HSFSTS_CTL_FDBC_MASK | HSFSTS_CTL_FCYCLE_MASK);
		val |= HSFSTS_CTL_AEL | HSFSTS_CTL_FCERR | HSFSTS_CTL_FDONE;
		val |= (block_size - 1) << HSFSTS_CTL_FDBC_SHIFT;
		val |= HSFSTS_CTL_FCYCLE_WRITE;

		ret = पूर्णांकel_spi_ग_लिखो_block(ispi, ग_लिखो_buf, block_size);
		अगर (ret) अणु
			dev_err(ispi->dev, "failed to write block\n");
			वापस ret;
		पूर्ण

		/* Start the ग_लिखो now */
		val |= HSFSTS_CTL_FGO;
		ग_लिखोl(val, ispi->base + HSFSTS_CTL);

		ret = पूर्णांकel_spi_रुको_hw_busy(ispi);
		अगर (ret) अणु
			dev_err(ispi->dev, "timeout\n");
			वापस ret;
		पूर्ण

		status = पढ़ोl(ispi->base + HSFSTS_CTL);
		अगर (status & HSFSTS_CTL_FCERR)
			ret = -EIO;
		अन्यथा अगर (status & HSFSTS_CTL_AEL)
			ret = -EACCES;

		अगर (ret < 0) अणु
			dev_err(ispi->dev, "write error: %llx: %#x\n", to,
				status);
			वापस ret;
		पूर्ण

		len -= block_size;
		to += block_size;
		retlen += block_size;
		ग_लिखो_buf += block_size;
	पूर्ण

	वापस retlen;
पूर्ण

अटल पूर्णांक पूर्णांकel_spi_erase(काष्ठा spi_nor *nor, loff_t offs)
अणु
	माप_प्रकार erase_size, len = nor->mtd.erasesize;
	काष्ठा पूर्णांकel_spi *ispi = nor->priv;
	u32 val, status, cmd;
	पूर्णांक ret;

	/* If the hardware can करो 64k erase use that when possible */
	अगर (len >= SZ_64K && ispi->erase_64k) अणु
		cmd = HSFSTS_CTL_FCYCLE_ERASE_64K;
		erase_size = SZ_64K;
	पूर्ण अन्यथा अणु
		cmd = HSFSTS_CTL_FCYCLE_ERASE;
		erase_size = SZ_4K;
	पूर्ण

	अगर (ispi->swseq_erase) अणु
		जबतक (len > 0) अणु
			ग_लिखोl(offs, ispi->base + FADDR);

			ret = पूर्णांकel_spi_sw_cycle(ispi, nor->erase_opcode,
						 0, OPTYPE_WRITE_WITH_ADDR);
			अगर (ret)
				वापस ret;

			offs += erase_size;
			len -= erase_size;
		पूर्ण

		वापस 0;
	पूर्ण

	/* Not needed with HW sequencer erase, make sure it is cleared */
	ispi->atomic_preopcode = 0;

	जबतक (len > 0) अणु
		ग_लिखोl(offs, ispi->base + FADDR);

		val = पढ़ोl(ispi->base + HSFSTS_CTL);
		val &= ~(HSFSTS_CTL_FDBC_MASK | HSFSTS_CTL_FCYCLE_MASK);
		val |= HSFSTS_CTL_AEL | HSFSTS_CTL_FCERR | HSFSTS_CTL_FDONE;
		val |= cmd;
		val |= HSFSTS_CTL_FGO;
		ग_लिखोl(val, ispi->base + HSFSTS_CTL);

		ret = पूर्णांकel_spi_रुको_hw_busy(ispi);
		अगर (ret)
			वापस ret;

		status = पढ़ोl(ispi->base + HSFSTS_CTL);
		अगर (status & HSFSTS_CTL_FCERR)
			वापस -EIO;
		अन्यथा अगर (status & HSFSTS_CTL_AEL)
			वापस -EACCES;

		offs += erase_size;
		len -= erase_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool पूर्णांकel_spi_is_रक्षित(स्थिर काष्ठा पूर्णांकel_spi *ispi,
				   अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक limit)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ispi->pr_num; i++) अणु
		u32 pr_base, pr_limit, pr_value;

		pr_value = पढ़ोl(ispi->pregs + PR(i));
		अगर (!(pr_value & (PR_WPE | PR_RPE)))
			जारी;

		pr_limit = (pr_value & PR_LIMIT_MASK) >> PR_LIMIT_SHIFT;
		pr_base = pr_value & PR_BASE_MASK;

		अगर (pr_base >= base && pr_limit <= limit)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * There will be a single partition holding all enabled flash regions. We
 * call this "BIOS".
 */
अटल व्योम पूर्णांकel_spi_fill_partition(काष्ठा पूर्णांकel_spi *ispi,
				     काष्ठा mtd_partition *part)
अणु
	u64 end;
	पूर्णांक i;

	स_रखो(part, 0, माप(*part));

	/* Start from the mandatory descriptor region */
	part->size = 4096;
	part->name = "BIOS";

	/*
	 * Now try to find where this partition ends based on the flash
	 * region रेजिस्टरs.
	 */
	क्रम (i = 1; i < ispi->nregions; i++) अणु
		u32 region, base, limit;

		region = पढ़ोl(ispi->base + FREG(i));
		base = region & FREG_BASE_MASK;
		limit = (region & FREG_LIMIT_MASK) >> FREG_LIMIT_SHIFT;

		अगर (base >= limit || limit == 0)
			जारी;

		/*
		 * If any of the regions have protection bits set, make the
		 * whole partition पढ़ो-only to be on the safe side.
		 */
		अगर (पूर्णांकel_spi_is_रक्षित(ispi, base, limit))
			ispi->ग_लिखोable = false;

		end = (limit << 12) + 4096;
		अगर (end > part->size)
			part->size = end;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा spi_nor_controller_ops पूर्णांकel_spi_controller_ops = अणु
	.पढ़ो_reg = पूर्णांकel_spi_पढ़ो_reg,
	.ग_लिखो_reg = पूर्णांकel_spi_ग_लिखो_reg,
	.पढ़ो = पूर्णांकel_spi_पढ़ो,
	.ग_लिखो = पूर्णांकel_spi_ग_लिखो,
	.erase = पूर्णांकel_spi_erase,
पूर्ण;

काष्ठा पूर्णांकel_spi *पूर्णांकel_spi_probe(काष्ठा device *dev,
	काष्ठा resource *mem, स्थिर काष्ठा पूर्णांकel_spi_boardinfo *info)
अणु
	स्थिर काष्ठा spi_nor_hwcaps hwcaps = अणु
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_PP,
	पूर्ण;
	काष्ठा mtd_partition part;
	काष्ठा पूर्णांकel_spi *ispi;
	पूर्णांक ret;

	अगर (!info || !mem)
		वापस ERR_PTR(-EINVAL);

	ispi = devm_kzalloc(dev, माप(*ispi), GFP_KERNEL);
	अगर (!ispi)
		वापस ERR_PTR(-ENOMEM);

	ispi->base = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(ispi->base))
		वापस ERR_CAST(ispi->base);

	ispi->dev = dev;
	ispi->info = info;
	ispi->ग_लिखोable = info->ग_लिखोable;

	ret = पूर्णांकel_spi_init(ispi);
	अगर (ret)
		वापस ERR_PTR(ret);

	ispi->nor.dev = ispi->dev;
	ispi->nor.priv = ispi;
	ispi->nor.controller_ops = &पूर्णांकel_spi_controller_ops;

	ret = spi_nor_scan(&ispi->nor, शून्य, &hwcaps);
	अगर (ret) अणु
		dev_info(dev, "failed to locate the chip\n");
		वापस ERR_PTR(ret);
	पूर्ण

	पूर्णांकel_spi_fill_partition(ispi, &part);

	/* Prevent ग_लिखोs अगर not explicitly enabled */
	अगर (!ispi->ग_लिखोable || !ग_लिखोable)
		ispi->nor.mtd.flags &= ~MTD_WRITEABLE;

	ret = mtd_device_रेजिस्टर(&ispi->nor.mtd, &part, 1);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस ispi;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_spi_probe);

पूर्णांक पूर्णांकel_spi_हटाओ(काष्ठा पूर्णांकel_spi *ispi)
अणु
	वापस mtd_device_unरेजिस्टर(&ispi->nor.mtd);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_spi_हटाओ);

MODULE_DESCRIPTION("Intel PCH/PCU SPI flash core driver");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_LICENSE("GPL v2");
