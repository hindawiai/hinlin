<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ASPEED Static Memory Controller driver
 *
 * Copyright (c) 2015-2016, IBM Corporation.
 */

#समावेश <linux/bug.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/spi-nor.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/sizes.h>
#समावेश <linux/sysfs.h>

#घोषणा DEVICE_NAME	"aspeed-smc"

/*
 * The driver only support SPI flash
 */
क्रमागत aspeed_smc_flash_type अणु
	smc_type_nor  = 0,
	smc_type_nand = 1,
	smc_type_spi  = 2,
पूर्ण;

काष्ठा aspeed_smc_chip;

काष्ठा aspeed_smc_info अणु
	u32 maxsize;		/* maximum size of chip winकरोw */
	u8 nce;			/* number of chip enables */
	bool hastype;		/* flash type field exists in config reg */
	u8 we0;			/* shअगरt क्रम ग_लिखो enable bit क्रम CE0 */
	u8 ctl0;		/* offset in regs of ctl क्रम CE0 */

	व्योम (*set_4b)(काष्ठा aspeed_smc_chip *chip);
पूर्ण;

अटल व्योम aspeed_smc_chip_set_4b_spi_2400(काष्ठा aspeed_smc_chip *chip);
अटल व्योम aspeed_smc_chip_set_4b(काष्ठा aspeed_smc_chip *chip);

अटल स्थिर काष्ठा aspeed_smc_info fmc_2400_info = अणु
	.maxsize = 64 * 1024 * 1024,
	.nce = 5,
	.hastype = true,
	.we0 = 16,
	.ctl0 = 0x10,
	.set_4b = aspeed_smc_chip_set_4b,
पूर्ण;

अटल स्थिर काष्ठा aspeed_smc_info spi_2400_info = अणु
	.maxsize = 64 * 1024 * 1024,
	.nce = 1,
	.hastype = false,
	.we0 = 0,
	.ctl0 = 0x04,
	.set_4b = aspeed_smc_chip_set_4b_spi_2400,
पूर्ण;

अटल स्थिर काष्ठा aspeed_smc_info fmc_2500_info = अणु
	.maxsize = 256 * 1024 * 1024,
	.nce = 3,
	.hastype = true,
	.we0 = 16,
	.ctl0 = 0x10,
	.set_4b = aspeed_smc_chip_set_4b,
पूर्ण;

अटल स्थिर काष्ठा aspeed_smc_info spi_2500_info = अणु
	.maxsize = 128 * 1024 * 1024,
	.nce = 2,
	.hastype = false,
	.we0 = 16,
	.ctl0 = 0x10,
	.set_4b = aspeed_smc_chip_set_4b,
पूर्ण;

क्रमागत aspeed_smc_ctl_reg_value अणु
	smc_base,		/* base value without mode क्रम other commands */
	smc_पढ़ो,		/* command reg क्रम (maybe fast) पढ़ोs */
	smc_ग_लिखो,		/* command reg क्रम ग_लिखोs */
	smc_max,
पूर्ण;

काष्ठा aspeed_smc_controller;

काष्ठा aspeed_smc_chip अणु
	पूर्णांक cs;
	काष्ठा aspeed_smc_controller *controller;
	व्योम __iomem *ctl;			/* control रेजिस्टर */
	व्योम __iomem *ahb_base;			/* base of chip winकरोw */
	u32 ahb_winकरोw_size;			/* chip mapping winकरोw size */
	u32 ctl_val[smc_max];			/* control settings */
	क्रमागत aspeed_smc_flash_type type;	/* what type of flash */
	काष्ठा spi_nor nor;
पूर्ण;

काष्ठा aspeed_smc_controller अणु
	काष्ठा device *dev;

	काष्ठा mutex mutex;			/* controller access mutex */
	स्थिर काष्ठा aspeed_smc_info *info;	/* type info of controller */
	व्योम __iomem *regs;			/* controller रेजिस्टरs */
	व्योम __iomem *ahb_base;			/* per-chip winकरोws resource */
	u32 ahb_winकरोw_size;			/* full mapping winकरोw size */

	काष्ठा aspeed_smc_chip *chips[];	/* poपूर्णांकers to attached chips */
पूर्ण;

/*
 * SPI Flash Configuration Register (AST2500 SPI)
 *     or
 * Type setting Register (AST2500 FMC).
 * CE0 and CE1 can only be of type SPI. CE2 can be of type NOR but the
 * driver करोes not support it.
 */
#घोषणा CONFIG_REG			0x0
#घोषणा CONFIG_DISABLE_LEGACY		BIT(31) /* 1 */

#घोषणा CONFIG_CE2_WRITE		BIT(18)
#घोषणा CONFIG_CE1_WRITE		BIT(17)
#घोषणा CONFIG_CE0_WRITE		BIT(16)

#घोषणा CONFIG_CE2_TYPE			BIT(4) /* AST2500 FMC only */
#घोषणा CONFIG_CE1_TYPE			BIT(2) /* AST2500 FMC only */
#घोषणा CONFIG_CE0_TYPE			BIT(0) /* AST2500 FMC only */

/*
 * CE Control Register
 */
#घोषणा CE_CONTROL_REG			0x4

/*
 * CEx Control Register
 */
#घोषणा CONTROL_AAF_MODE		BIT(31)
#घोषणा CONTROL_IO_MODE_MASK		GENMASK(30, 28)
#घोषणा CONTROL_IO_DUAL_DATA		BIT(29)
#घोषणा CONTROL_IO_DUAL_ADDR_DATA	(BIT(29) | BIT(28))
#घोषणा CONTROL_IO_QUAD_DATA		BIT(30)
#घोषणा CONTROL_IO_QUAD_ADDR_DATA	(BIT(30) | BIT(28))
#घोषणा CONTROL_CE_INACTIVE_SHIFT	24
#घोषणा CONTROL_CE_INACTIVE_MASK	GENMASK(27, \
					CONTROL_CE_INACTIVE_SHIFT)
/* 0 = 16T ... 15 = 1T   T=HCLK */
#घोषणा CONTROL_COMMAND_SHIFT		16
#घोषणा CONTROL_DUMMY_COMMAND_OUT	BIT(15)
#घोषणा CONTROL_IO_DUMMY_HI		BIT(14)
#घोषणा CONTROL_IO_DUMMY_HI_SHIFT	14
#घोषणा CONTROL_CLK_DIV4		BIT(13) /* others */
#घोषणा CONTROL_IO_ADDRESS_4B		BIT(13) /* AST2400 SPI */
#घोषणा CONTROL_RW_MERGE		BIT(12)
#घोषणा CONTROL_IO_DUMMY_LO_SHIFT	6
#घोषणा CONTROL_IO_DUMMY_LO		GENMASK(7, \
						CONTROL_IO_DUMMY_LO_SHIFT)
#घोषणा CONTROL_IO_DUMMY_MASK		(CONTROL_IO_DUMMY_HI | \
					 CONTROL_IO_DUMMY_LO)
#घोषणा CONTROL_IO_DUMMY_SET(dummy)				 \
	(((((dummy) >> 2) & 0x1) << CONTROL_IO_DUMMY_HI_SHIFT) | \
	 (((dummy) & 0x3) << CONTROL_IO_DUMMY_LO_SHIFT))

#घोषणा CONTROL_CLOCK_FREQ_SEL_SHIFT	8
#घोषणा CONTROL_CLOCK_FREQ_SEL_MASK	GENMASK(11, \
						CONTROL_CLOCK_FREQ_SEL_SHIFT)
#घोषणा CONTROL_LSB_FIRST		BIT(5)
#घोषणा CONTROL_CLOCK_MODE_3		BIT(4)
#घोषणा CONTROL_IN_DUAL_DATA		BIT(3)
#घोषणा CONTROL_CE_STOP_ACTIVE_CONTROL	BIT(2)
#घोषणा CONTROL_COMMAND_MODE_MASK	GENMASK(1, 0)
#घोषणा CONTROL_COMMAND_MODE_NORMAL	0
#घोषणा CONTROL_COMMAND_MODE_FREAD	1
#घोषणा CONTROL_COMMAND_MODE_WRITE	2
#घोषणा CONTROL_COMMAND_MODE_USER	3

#घोषणा CONTROL_KEEP_MASK						\
	(CONTROL_AAF_MODE | CONTROL_CE_INACTIVE_MASK | CONTROL_CLK_DIV4 | \
	 CONTROL_CLOCK_FREQ_SEL_MASK | CONTROL_LSB_FIRST | CONTROL_CLOCK_MODE_3)

/*
 * The Segment Register uses a 8MB unit to encode the start address
 * and the end address of the mapping winकरोw of a flash SPI slave :
 *
 *        | byte 1 | byte 2 | byte 3 | byte 4 |
 *        +--------+--------+--------+--------+
 *        |  end   |  start |   0    |   0    |
 */
#घोषणा SEGMENT_ADDR_REG0		0x30
#घोषणा SEGMENT_ADDR_START(_r)		((((_r) >> 16) & 0xFF) << 23)
#घोषणा SEGMENT_ADDR_END(_r)		((((_r) >> 24) & 0xFF) << 23)
#घोषणा SEGMENT_ADDR_VALUE(start, end)					\
	(((((start) >> 23) & 0xFF) << 16) | ((((end) >> 23) & 0xFF) << 24))
#घोषणा SEGMENT_ADDR_REG(controller, cs)	\
	((controller)->regs + SEGMENT_ADDR_REG0 + (cs) * 4)

/*
 * In user mode all data bytes पढ़ो or written to the chip decode address
 * range are transferred to or from the SPI bus. The range is treated as a
 * fअगरo of arbitratry 1, 2, or 4 byte width but each ग_लिखो has to be aligned
 * to its size. The address within the multiple 8kB range is ignored when
 * sending bytes to the SPI bus.
 *
 * On the arm architecture, as of Linux version 4.3, स_नकल_fromio and
 * स_नकल_toio on little endian tarमाला_लो use the optimized स_नकल routines
 * that were deचिन्हित क्रम well behavied memory storage. These routines
 * have a stutter अगर the source and destination are not both word aligned,
 * once with a duplicate access to the source after aligning to the
 * destination to a word boundary, and again with a duplicate access to
 * the source when the final byte count is not word aligned.
 *
 * When writing or पढ़ोing the fअगरo this stutter discards data or sends
 * too much data to the fअगरo and can not be used by this driver.
 *
 * While the low level io string routines that implement the insl family करो
 * the desired accesses and memory increments, the cross architecture io
 * macros make them essentially impossible to use on a memory mapped address
 * instead of a a token from the call to iomap of an io port.
 *
 * These fअगरo routines use पढ़ोl and मित्रs to a स्थिरant io port and update
 * the memory buffer poपूर्णांकer and count via explicit code. The final updates
 * to len are optimistically suppressed.
 */
अटल पूर्णांक aspeed_smc_पढ़ो_from_ahb(व्योम *buf, व्योम __iomem *src, माप_प्रकार len)
अणु
	माप_प्रकार offset = 0;

	अगर (IS_ALIGNED((uपूर्णांकptr_t)src, माप(uपूर्णांकptr_t)) &&
	    IS_ALIGNED((uपूर्णांकptr_t)buf, माप(uपूर्णांकptr_t))) अणु
		ioपढ़ो32_rep(src, buf, len >> 2);
		offset = len & ~0x3;
		len -= offset;
	पूर्ण
	ioपढ़ो8_rep(src, (u8 *)buf + offset, len);
	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_smc_ग_लिखो_to_ahb(व्योम __iomem *dst, स्थिर व्योम *buf,
				   माप_प्रकार len)
अणु
	माप_प्रकार offset = 0;

	अगर (IS_ALIGNED((uपूर्णांकptr_t)dst, माप(uपूर्णांकptr_t)) &&
	    IS_ALIGNED((uपूर्णांकptr_t)buf, माप(uपूर्णांकptr_t))) अणु
		ioग_लिखो32_rep(dst, buf, len >> 2);
		offset = len & ~0x3;
		len -= offset;
	पूर्ण
	ioग_लिखो8_rep(dst, (स्थिर u8 *)buf + offset, len);
	वापस 0;
पूर्ण

अटल अंतरभूत u32 aspeed_smc_chip_ग_लिखो_bit(काष्ठा aspeed_smc_chip *chip)
अणु
	वापस BIT(chip->controller->info->we0 + chip->cs);
पूर्ण

अटल व्योम aspeed_smc_chip_check_config(काष्ठा aspeed_smc_chip *chip)
अणु
	काष्ठा aspeed_smc_controller *controller = chip->controller;
	u32 reg;

	reg = पढ़ोl(controller->regs + CONFIG_REG);

	अगर (reg & aspeed_smc_chip_ग_लिखो_bit(chip))
		वापस;

	dev_dbg(controller->dev, "config write is not set ! @%p: 0x%08x\n",
		controller->regs + CONFIG_REG, reg);
	reg |= aspeed_smc_chip_ग_लिखो_bit(chip);
	ग_लिखोl(reg, controller->regs + CONFIG_REG);
पूर्ण

अटल व्योम aspeed_smc_start_user(काष्ठा spi_nor *nor)
अणु
	काष्ठा aspeed_smc_chip *chip = nor->priv;
	u32 ctl = chip->ctl_val[smc_base];

	/*
	 * When the chip is controlled in user mode, we need ग_लिखो
	 * access to send the opcodes to it. So check the config.
	 */
	aspeed_smc_chip_check_config(chip);

	ctl |= CONTROL_COMMAND_MODE_USER |
		CONTROL_CE_STOP_ACTIVE_CONTROL;
	ग_लिखोl(ctl, chip->ctl);

	ctl &= ~CONTROL_CE_STOP_ACTIVE_CONTROL;
	ग_लिखोl(ctl, chip->ctl);
पूर्ण

अटल व्योम aspeed_smc_stop_user(काष्ठा spi_nor *nor)
अणु
	काष्ठा aspeed_smc_chip *chip = nor->priv;

	u32 ctl = chip->ctl_val[smc_पढ़ो];
	u32 ctl2 = ctl | CONTROL_COMMAND_MODE_USER |
		CONTROL_CE_STOP_ACTIVE_CONTROL;

	ग_लिखोl(ctl2, chip->ctl);	/* stop user CE control */
	ग_लिखोl(ctl, chip->ctl);		/* शेष to ख_पढ़ो or पढ़ो mode */
पूर्ण

अटल पूर्णांक aspeed_smc_prep(काष्ठा spi_nor *nor)
अणु
	काष्ठा aspeed_smc_chip *chip = nor->priv;

	mutex_lock(&chip->controller->mutex);
	वापस 0;
पूर्ण

अटल व्योम aspeed_smc_unprep(काष्ठा spi_nor *nor)
अणु
	काष्ठा aspeed_smc_chip *chip = nor->priv;

	mutex_unlock(&chip->controller->mutex);
पूर्ण

अटल पूर्णांक aspeed_smc_पढ़ो_reg(काष्ठा spi_nor *nor, u8 opcode, u8 *buf,
			       माप_प्रकार len)
अणु
	काष्ठा aspeed_smc_chip *chip = nor->priv;

	aspeed_smc_start_user(nor);
	aspeed_smc_ग_लिखो_to_ahb(chip->ahb_base, &opcode, 1);
	aspeed_smc_पढ़ो_from_ahb(buf, chip->ahb_base, len);
	aspeed_smc_stop_user(nor);
	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_smc_ग_लिखो_reg(काष्ठा spi_nor *nor, u8 opcode, स्थिर u8 *buf,
				माप_प्रकार len)
अणु
	काष्ठा aspeed_smc_chip *chip = nor->priv;

	aspeed_smc_start_user(nor);
	aspeed_smc_ग_लिखो_to_ahb(chip->ahb_base, &opcode, 1);
	aspeed_smc_ग_लिखो_to_ahb(chip->ahb_base, buf, len);
	aspeed_smc_stop_user(nor);
	वापस 0;
पूर्ण

अटल व्योम aspeed_smc_send_cmd_addr(काष्ठा spi_nor *nor, u8 cmd, u32 addr)
अणु
	काष्ठा aspeed_smc_chip *chip = nor->priv;
	__be32 temp;
	u32 cmdaddr;

	चयन (nor->addr_width) अणु
	शेष:
		WARN_ONCE(1, "Unexpected address width %u, defaulting to 3\n",
			  nor->addr_width);
		fallthrough;
	हाल 3:
		cmdaddr = addr & 0xFFFFFF;
		cmdaddr |= cmd << 24;

		temp = cpu_to_be32(cmdaddr);
		aspeed_smc_ग_लिखो_to_ahb(chip->ahb_base, &temp, 4);
		अवरोध;
	हाल 4:
		temp = cpu_to_be32(addr);
		aspeed_smc_ग_लिखो_to_ahb(chip->ahb_base, &cmd, 1);
		aspeed_smc_ग_लिखो_to_ahb(chip->ahb_base, &temp, 4);
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार aspeed_smc_पढ़ो_user(काष्ठा spi_nor *nor, loff_t from,
				    माप_प्रकार len, u_अक्षर *पढ़ो_buf)
अणु
	काष्ठा aspeed_smc_chip *chip = nor->priv;
	पूर्णांक i;
	u8 dummy = 0xFF;

	aspeed_smc_start_user(nor);
	aspeed_smc_send_cmd_addr(nor, nor->पढ़ो_opcode, from);
	क्रम (i = 0; i < chip->nor.पढ़ो_dummy / 8; i++)
		aspeed_smc_ग_लिखो_to_ahb(chip->ahb_base, &dummy, माप(dummy));

	aspeed_smc_पढ़ो_from_ahb(पढ़ो_buf, chip->ahb_base, len);
	aspeed_smc_stop_user(nor);
	वापस len;
पूर्ण

अटल sमाप_प्रकार aspeed_smc_ग_लिखो_user(काष्ठा spi_nor *nor, loff_t to,
				     माप_प्रकार len, स्थिर u_अक्षर *ग_लिखो_buf)
अणु
	काष्ठा aspeed_smc_chip *chip = nor->priv;

	aspeed_smc_start_user(nor);
	aspeed_smc_send_cmd_addr(nor, nor->program_opcode, to);
	aspeed_smc_ग_लिखो_to_ahb(chip->ahb_base, ग_लिखो_buf, len);
	aspeed_smc_stop_user(nor);
	वापस len;
पूर्ण

अटल पूर्णांक aspeed_smc_unरेजिस्टर(काष्ठा aspeed_smc_controller *controller)
अणु
	काष्ठा aspeed_smc_chip *chip;
	पूर्णांक n;

	क्रम (n = 0; n < controller->info->nce; n++) अणु
		chip = controller->chips[n];
		अगर (chip)
			mtd_device_unरेजिस्टर(&chip->nor.mtd);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_smc_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	वापस aspeed_smc_unरेजिस्टर(platक्रमm_get_drvdata(dev));
पूर्ण

अटल स्थिर काष्ठा of_device_id aspeed_smc_matches[] = अणु
	अणु .compatible = "aspeed,ast2400-fmc", .data = &fmc_2400_info पूर्ण,
	अणु .compatible = "aspeed,ast2400-spi", .data = &spi_2400_info पूर्ण,
	अणु .compatible = "aspeed,ast2500-fmc", .data = &fmc_2500_info पूर्ण,
	अणु .compatible = "aspeed,ast2500-spi", .data = &spi_2500_info पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aspeed_smc_matches);

/*
 * Each chip has a mapping winकरोw defined by a segment address
 * रेजिस्टर defining a start and an end address on the AHB bus. These
 * addresses can be configured to fit the chip size and offer a
 * contiguous memory region across chips. For the moment, we only
 * check that each chip segment is valid.
 */
अटल व्योम __iomem *aspeed_smc_chip_base(काष्ठा aspeed_smc_chip *chip,
					  काष्ठा resource *res)
अणु
	काष्ठा aspeed_smc_controller *controller = chip->controller;
	u32 offset = 0;
	u32 reg;

	अगर (controller->info->nce > 1) अणु
		reg = पढ़ोl(SEGMENT_ADDR_REG(controller, chip->cs));

		अगर (SEGMENT_ADDR_START(reg) >= SEGMENT_ADDR_END(reg))
			वापस शून्य;

		offset = SEGMENT_ADDR_START(reg) - res->start;
	पूर्ण

	वापस controller->ahb_base + offset;
पूर्ण

अटल u32 aspeed_smc_ahb_base_phy(काष्ठा aspeed_smc_controller *controller)
अणु
	u32 seg0_val = पढ़ोl(SEGMENT_ADDR_REG(controller, 0));

	वापस SEGMENT_ADDR_START(seg0_val);
पूर्ण

अटल u32 chip_set_segment(काष्ठा aspeed_smc_chip *chip, u32 cs, u32 start,
			    u32 size)
अणु
	काष्ठा aspeed_smc_controller *controller = chip->controller;
	व्योम __iomem *seg_reg;
	u32 seg_oldval, seg_newval, ahb_base_phy, end;

	ahb_base_phy = aspeed_smc_ahb_base_phy(controller);

	seg_reg = SEGMENT_ADDR_REG(controller, cs);
	seg_oldval = पढ़ोl(seg_reg);

	/*
	 * If the chip size is not specअगरied, use the शेष segment
	 * size, but take पूर्णांकo account the possible overlap with the
	 * previous segment
	 */
	अगर (!size)
		size = SEGMENT_ADDR_END(seg_oldval) - start;

	/*
	 * The segment cannot exceed the maximum winकरोw size of the
	 * controller.
	 */
	अगर (start + size > ahb_base_phy + controller->ahb_winकरोw_size) अणु
		size = ahb_base_phy + controller->ahb_winकरोw_size - start;
		dev_warn(chip->nor.dev, "CE%d window resized to %dMB",
			 cs, size >> 20);
	पूर्ण

	end = start + size;
	seg_newval = SEGMENT_ADDR_VALUE(start, end);
	ग_लिखोl(seg_newval, seg_reg);

	/*
	 * Restore शेष value अगर something goes wrong. The chip
	 * might have set some bogus value and we would loose access
	 * to the chip.
	 */
	अगर (seg_newval != पढ़ोl(seg_reg)) अणु
		dev_err(chip->nor.dev, "CE%d window invalid", cs);
		ग_लिखोl(seg_oldval, seg_reg);
		start = SEGMENT_ADDR_START(seg_oldval);
		end = SEGMENT_ADDR_END(seg_oldval);
		size = end - start;
	पूर्ण

	dev_info(chip->nor.dev, "CE%d window [ 0x%.8x - 0x%.8x ] %dMB",
		 cs, start, end, size >> 20);

	वापस size;
पूर्ण

/*
 * The segment रेजिस्टर defines the mapping winकरोw on the AHB bus and
 * it needs to be configured depending on the chip size. The segment
 * रेजिस्टर of the following CE also needs to be tuned in order to
 * provide a contiguous winकरोw across multiple chips.
 *
 * This is expected to be called in increasing CE order
 */
अटल u32 aspeed_smc_chip_set_segment(काष्ठा aspeed_smc_chip *chip)
अणु
	काष्ठा aspeed_smc_controller *controller = chip->controller;
	u32 ahb_base_phy, start;
	u32 size = chip->nor.mtd.size;

	/*
	 * Each controller has a chip size limit क्रम direct memory
	 * access
	 */
	अगर (size > controller->info->maxsize)
		size = controller->info->maxsize;

	/*
	 * The AST2400 SPI controller only handles one chip and करोes
	 * not have segment रेजिस्टरs. Let's use the chip size क्रम the
	 * AHB winकरोw.
	 */
	अगर (controller->info == &spi_2400_info)
		जाओ out;

	/*
	 * The AST2500 SPI controller has a HW bug when the CE0 chip
	 * size reaches 128MB. Enक्रमce a size limit of 120MB to
	 * prevent the controller from using bogus settings in the
	 * segment रेजिस्टर.
	 */
	अगर (chip->cs == 0 && controller->info == &spi_2500_info &&
	    size == SZ_128M) अणु
		size = 120 << 20;
		dev_info(chip->nor.dev,
			 "CE%d window resized to %dMB (AST2500 HW quirk)",
			 chip->cs, size >> 20);
	पूर्ण

	ahb_base_phy = aspeed_smc_ahb_base_phy(controller);

	/*
	 * As a start address क्रम the current segment, use the शेष
	 * start address अगर we are handling CE0 or use the previous
	 * segment ending address
	 */
	अगर (chip->cs) अणु
		u32 prev = पढ़ोl(SEGMENT_ADDR_REG(controller, chip->cs - 1));

		start = SEGMENT_ADDR_END(prev);
	पूर्ण अन्यथा अणु
		start = ahb_base_phy;
	पूर्ण

	size = chip_set_segment(chip, chip->cs, start, size);

	/* Update chip base address on the AHB bus */
	chip->ahb_base = controller->ahb_base + (start - ahb_base_phy);

	/*
	 * Now, make sure the next segment करोes not overlap with the
	 * current one we just configured, even अगर there is no
	 * available chip. That could अवरोध access in Command Mode.
	 */
	अगर (chip->cs < controller->info->nce - 1)
		chip_set_segment(chip, chip->cs + 1, start + size, 0);

out:
	अगर (size < chip->nor.mtd.size)
		dev_warn(chip->nor.dev,
			 "CE%d window too small for chip %dMB",
			 chip->cs, (u32)chip->nor.mtd.size >> 20);

	वापस size;
पूर्ण

अटल व्योम aspeed_smc_chip_enable_ग_लिखो(काष्ठा aspeed_smc_chip *chip)
अणु
	काष्ठा aspeed_smc_controller *controller = chip->controller;
	u32 reg;

	reg = पढ़ोl(controller->regs + CONFIG_REG);

	reg |= aspeed_smc_chip_ग_लिखो_bit(chip);
	ग_लिखोl(reg, controller->regs + CONFIG_REG);
पूर्ण

अटल व्योम aspeed_smc_chip_set_type(काष्ठा aspeed_smc_chip *chip, पूर्णांक type)
अणु
	काष्ठा aspeed_smc_controller *controller = chip->controller;
	u32 reg;

	chip->type = type;

	reg = पढ़ोl(controller->regs + CONFIG_REG);
	reg &= ~(3 << (chip->cs * 2));
	reg |= chip->type << (chip->cs * 2);
	ग_लिखोl(reg, controller->regs + CONFIG_REG);
पूर्ण

/*
 * The first chip of the AST2500 FMC flash controller is strapped by
 * hardware, or स्वतःdetected, but other chips need to be set. Enक्रमce
 * the 4B setting क्रम all chips.
 */
अटल व्योम aspeed_smc_chip_set_4b(काष्ठा aspeed_smc_chip *chip)
अणु
	काष्ठा aspeed_smc_controller *controller = chip->controller;
	u32 reg;

	reg = पढ़ोl(controller->regs + CE_CONTROL_REG);
	reg |= 1 << chip->cs;
	ग_लिखोl(reg, controller->regs + CE_CONTROL_REG);
पूर्ण

/*
 * The AST2400 SPI flash controller करोes not have a CE Control
 * रेजिस्टर. It uses the CE0 control रेजिस्टर to set 4Byte mode at the
 * controller level.
 */
अटल व्योम aspeed_smc_chip_set_4b_spi_2400(काष्ठा aspeed_smc_chip *chip)
अणु
	chip->ctl_val[smc_base] |= CONTROL_IO_ADDRESS_4B;
	chip->ctl_val[smc_पढ़ो] |= CONTROL_IO_ADDRESS_4B;
पूर्ण

अटल पूर्णांक aspeed_smc_chip_setup_init(काष्ठा aspeed_smc_chip *chip,
				      काष्ठा resource *res)
अणु
	काष्ठा aspeed_smc_controller *controller = chip->controller;
	स्थिर काष्ठा aspeed_smc_info *info = controller->info;
	u32 reg, base_reg;

	/*
	 * Always turn on the ग_लिखो enable bit to allow opcodes to be
	 * sent in user mode.
	 */
	aspeed_smc_chip_enable_ग_लिखो(chip);

	/* The driver only supports SPI type flash */
	अगर (info->hastype)
		aspeed_smc_chip_set_type(chip, smc_type_spi);

	/*
	 * Configure chip base address in memory
	 */
	chip->ahb_base = aspeed_smc_chip_base(chip, res);
	अगर (!chip->ahb_base) अणु
		dev_warn(chip->nor.dev, "CE%d window closed", chip->cs);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Get value of the inherited control रेजिस्टर. U-Boot usually
	 * करोes some timing calibration on the FMC chip, so it's good
	 * to keep them. In the future, we should handle calibration
	 * from Linux.
	 */
	reg = पढ़ोl(chip->ctl);
	dev_dbg(controller->dev, "control register: %08x\n", reg);

	base_reg = reg & CONTROL_KEEP_MASK;
	अगर (base_reg != reg) अणु
		dev_dbg(controller->dev,
			"control register changed to: %08x\n",
			base_reg);
	पूर्ण
	chip->ctl_val[smc_base] = base_reg;

	/*
	 * Retain the prior value of the control रेजिस्टर as the
	 * शेष अगर it was normal access mode. Otherwise start with
	 * the sanitized base value set to पढ़ो mode.
	 */
	अगर ((reg & CONTROL_COMMAND_MODE_MASK) ==
	    CONTROL_COMMAND_MODE_NORMAL)
		chip->ctl_val[smc_पढ़ो] = reg;
	अन्यथा
		chip->ctl_val[smc_पढ़ो] = chip->ctl_val[smc_base] |
			CONTROL_COMMAND_MODE_NORMAL;

	dev_dbg(controller->dev, "default control register: %08x\n",
		chip->ctl_val[smc_पढ़ो]);
	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_smc_chip_setup_finish(काष्ठा aspeed_smc_chip *chip)
अणु
	काष्ठा aspeed_smc_controller *controller = chip->controller;
	स्थिर काष्ठा aspeed_smc_info *info = controller->info;
	u32 cmd;

	अगर (chip->nor.addr_width == 4 && info->set_4b)
		info->set_4b(chip);

	/* This is क्रम direct AHB access when using Command Mode. */
	chip->ahb_winकरोw_size = aspeed_smc_chip_set_segment(chip);

	/*
	 * base mode has not been optimized yet. use it क्रम ग_लिखोs.
	 */
	chip->ctl_val[smc_ग_लिखो] = chip->ctl_val[smc_base] |
		chip->nor.program_opcode << CONTROL_COMMAND_SHIFT |
		CONTROL_COMMAND_MODE_WRITE;

	dev_dbg(controller->dev, "write control register: %08x\n",
		chip->ctl_val[smc_ग_लिखो]);

	/*
	 * TODO: Adjust घड़ीs अगर fast पढ़ो is supported and पूर्णांकerpret
	 * SPI NOR flags to adjust controller settings.
	 */
	अगर (chip->nor.पढ़ो_proto == SNOR_PROTO_1_1_1) अणु
		अगर (chip->nor.पढ़ो_dummy == 0)
			cmd = CONTROL_COMMAND_MODE_NORMAL;
		अन्यथा
			cmd = CONTROL_COMMAND_MODE_FREAD;
	पूर्ण अन्यथा अणु
		dev_err(chip->nor.dev, "unsupported SPI read mode\n");
		वापस -EINVAL;
	पूर्ण

	chip->ctl_val[smc_पढ़ो] |= cmd |
		CONTROL_IO_DUMMY_SET(chip->nor.पढ़ो_dummy / 8);

	dev_dbg(controller->dev, "base control register: %08x\n",
		chip->ctl_val[smc_पढ़ो]);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_nor_controller_ops aspeed_smc_controller_ops = अणु
	.prepare = aspeed_smc_prep,
	.unprepare = aspeed_smc_unprep,
	.पढ़ो_reg = aspeed_smc_पढ़ो_reg,
	.ग_लिखो_reg = aspeed_smc_ग_लिखो_reg,
	.पढ़ो = aspeed_smc_पढ़ो_user,
	.ग_लिखो = aspeed_smc_ग_लिखो_user,
पूर्ण;

अटल पूर्णांक aspeed_smc_setup_flash(काष्ठा aspeed_smc_controller *controller,
				  काष्ठा device_node *np, काष्ठा resource *r)
अणु
	स्थिर काष्ठा spi_nor_hwcaps hwcaps = अणु
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_PP,
	पूर्ण;
	स्थिर काष्ठा aspeed_smc_info *info = controller->info;
	काष्ठा device *dev = controller->dev;
	काष्ठा device_node *child;
	अचिन्हित पूर्णांक cs;
	पूर्णांक ret = -ENODEV;

	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा aspeed_smc_chip *chip;
		काष्ठा spi_nor *nor;
		काष्ठा mtd_info *mtd;

		/* This driver करोes not support न_अंकD or NOR flash devices. */
		अगर (!of_device_is_compatible(child, "jedec,spi-nor"))
			जारी;

		ret = of_property_पढ़ो_u32(child, "reg", &cs);
		अगर (ret) अणु
			dev_err(dev, "Couldn't not read chip select.\n");
			अवरोध;
		पूर्ण

		अगर (cs >= info->nce) अणु
			dev_err(dev, "Chip select %d out of range.\n",
				cs);
			ret = -दुस्फल;
			अवरोध;
		पूर्ण

		अगर (controller->chips[cs]) अणु
			dev_err(dev, "Chip select %d already in use by %s\n",
				cs, dev_name(controller->chips[cs]->nor.dev));
			ret = -EBUSY;
			अवरोध;
		पूर्ण

		chip = devm_kzalloc(controller->dev, माप(*chip), GFP_KERNEL);
		अगर (!chip) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		chip->controller = controller;
		chip->ctl = controller->regs + info->ctl0 + cs * 4;
		chip->cs = cs;

		nor = &chip->nor;
		mtd = &nor->mtd;

		nor->dev = dev;
		nor->priv = chip;
		spi_nor_set_flash_node(nor, child);
		nor->controller_ops = &aspeed_smc_controller_ops;

		ret = aspeed_smc_chip_setup_init(chip, r);
		अगर (ret)
			अवरोध;

		/*
		 * TODO: Add support क्रम Dual and Quad SPI protocols
		 * attach when board support is present as determined
		 * by of property.
		 */
		ret = spi_nor_scan(nor, शून्य, &hwcaps);
		अगर (ret)
			अवरोध;

		ret = aspeed_smc_chip_setup_finish(chip);
		अगर (ret)
			अवरोध;

		ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
		अगर (ret)
			अवरोध;

		controller->chips[cs] = chip;
	पूर्ण

	अगर (ret) अणु
		of_node_put(child);
		aspeed_smc_unरेजिस्टर(controller);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aspeed_smc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा aspeed_smc_controller *controller;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा aspeed_smc_info *info;
	काष्ठा resource *res;
	पूर्णांक ret;

	match = of_match_device(aspeed_smc_matches, &pdev->dev);
	अगर (!match || !match->data)
		वापस -ENODEV;
	info = match->data;

	controller = devm_kzalloc(&pdev->dev,
				  काष्ठा_size(controller, chips, info->nce),
				  GFP_KERNEL);
	अगर (!controller)
		वापस -ENOMEM;
	controller->info = info;
	controller->dev = dev;

	mutex_init(&controller->mutex);
	platक्रमm_set_drvdata(pdev, controller);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	controller->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(controller->regs))
		वापस PTR_ERR(controller->regs);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	controller->ahb_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(controller->ahb_base))
		वापस PTR_ERR(controller->ahb_base);

	controller->ahb_winकरोw_size = resource_size(res);

	ret = aspeed_smc_setup_flash(controller, np, res);
	अगर (ret)
		dev_err(dev, "Aspeed SMC probe failed %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver aspeed_smc_driver = अणु
	.probe = aspeed_smc_probe,
	.हटाओ = aspeed_smc_हटाओ,
	.driver = अणु
		.name = DEVICE_NAME,
		.of_match_table = aspeed_smc_matches,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(aspeed_smc_driver);

MODULE_DESCRIPTION("ASPEED Static Memory Controller Driver");
MODULE_AUTHOR("Cedric Le Goater <clg@kaod.org>");
MODULE_LICENSE("GPL v2");
