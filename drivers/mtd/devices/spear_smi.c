<शैली गुरु>
/*
 * SMI (Serial Memory Controller) device driver क्रम Serial NOR Flash on
 * SPEAr platक्रमm
 * The serial nor पूर्णांकerface is largely based on m25p80.c, however the SPI
 * पूर्णांकerface has been replaced by SMI.
 *
 * Copyright तऊ 2010 STMicroelectronics.
 * Ashish Priyadarshi
 * Shiraz Hashim <shiraz.linux.kernel@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/param.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/spear_smi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

/* SMI घड़ी rate */
#घोषणा SMI_MAX_CLOCK_FREQ	50000000 /* 50 MHz */

/* MAX समय out to safely come out of a erase or ग_लिखो busy conditions */
#घोषणा SMI_PROBE_TIMEOUT	(HZ / 10)
#घोषणा SMI_MAX_TIME_OUT	(3 * HZ)

/* समयout क्रम command completion */
#घोषणा SMI_CMD_TIMEOUT		(HZ / 10)

/* रेजिस्टरs of smi */
#घोषणा SMI_CR1		0x0	/* SMI control रेजिस्टर 1 */
#घोषणा SMI_CR2		0x4	/* SMI control रेजिस्टर 2 */
#घोषणा SMI_SR		0x8	/* SMI status रेजिस्टर */
#घोषणा SMI_TR		0xC	/* SMI transmit रेजिस्टर */
#घोषणा SMI_RR		0x10	/* SMI receive रेजिस्टर */

/* defines क्रम control_reg 1 */
#घोषणा BANK_EN		(0xF << 0)	/* enables all banks */
#घोषणा DSEL_TIME	(0x6 << 4)	/* Deselect समय 6 + 1 SMI_CK periods */
#घोषणा SW_MODE		(0x1 << 28)	/* enables SW Mode */
#घोषणा WB_MODE		(0x1 << 29)	/* Write Burst Mode */
#घोषणा FAST_MODE	(0x1 << 15)	/* Fast Mode */
#घोषणा HOLD1		(0x1 << 16)	/* Clock Hold period selection */

/* defines क्रम control_reg 2 */
#घोषणा SEND		(0x1 << 7)	/* Send data */
#घोषणा TFIE		(0x1 << 8)	/* Transmission Flag Interrupt Enable */
#घोषणा WCIE		(0x1 << 9)	/* Write Complete Interrupt Enable */
#घोषणा RD_STATUS_REG	(0x1 << 10)	/* पढ़ोs status reg */
#घोषणा WE		(0x1 << 11)	/* Write Enable */

#घोषणा TX_LEN_SHIFT	0
#घोषणा RX_LEN_SHIFT	4
#घोषणा BANK_SHIFT	12

/* defines क्रम status रेजिस्टर */
#घोषणा SR_WIP		0x1	/* Write in progress */
#घोषणा SR_WEL		0x2	/* Write enable latch */
#घोषणा SR_BP0		0x4	/* Block protect 0 */
#घोषणा SR_BP1		0x8	/* Block protect 1 */
#घोषणा SR_BP2		0x10	/* Block protect 2 */
#घोषणा SR_SRWD		0x80	/* SR ग_लिखो protect */
#घोषणा TFF		0x100	/* Transfer Finished Flag */
#घोषणा WCF		0x200	/* Transfer Finished Flag */
#घोषणा ERF1		0x400	/* Forbidden Write Request */
#घोषणा ERF2		0x800	/* Forbidden Access */

#घोषणा WM_SHIFT	12

/* flash opcodes */
#घोषणा OPCODE_RDID	0x9f	/* Read JEDEC ID */

/* Flash Device Ids मुख्यtenance section */

/* data काष्ठाure to मुख्यtain flash ids from dअगरferent venकरोrs */
काष्ठा flash_device अणु
	अक्षर *name;
	u8 erase_cmd;
	u32 device_id;
	u32 pagesize;
	अचिन्हित दीर्घ sectorsize;
	अचिन्हित दीर्घ size_in_bytes;
पूर्ण;

#घोषणा FLASH_ID(n, es, id, psize, ssize, size)	\
अणु				\
	.name = n,		\
	.erase_cmd = es,	\
	.device_id = id,	\
	.pagesize = psize,	\
	.sectorsize = ssize,	\
	.size_in_bytes = size	\
पूर्ण

अटल काष्ठा flash_device flash_devices[] = अणु
	FLASH_ID("st m25p16"     , 0xd8, 0x00152020, 0x100, 0x10000, 0x200000),
	FLASH_ID("st m25p32"     , 0xd8, 0x00162020, 0x100, 0x10000, 0x400000),
	FLASH_ID("st m25p64"     , 0xd8, 0x00172020, 0x100, 0x10000, 0x800000),
	FLASH_ID("st m25p128"    , 0xd8, 0x00182020, 0x100, 0x40000, 0x1000000),
	FLASH_ID("st m25p05"     , 0xd8, 0x00102020, 0x80 , 0x8000 , 0x10000),
	FLASH_ID("st m25p10"     , 0xd8, 0x00112020, 0x80 , 0x8000 , 0x20000),
	FLASH_ID("st m25p20"     , 0xd8, 0x00122020, 0x100, 0x10000, 0x40000),
	FLASH_ID("st m25p40"     , 0xd8, 0x00132020, 0x100, 0x10000, 0x80000),
	FLASH_ID("st m25p80"     , 0xd8, 0x00142020, 0x100, 0x10000, 0x100000),
	FLASH_ID("st m45pe10"    , 0xd8, 0x00114020, 0x100, 0x10000, 0x20000),
	FLASH_ID("st m45pe20"    , 0xd8, 0x00124020, 0x100, 0x10000, 0x40000),
	FLASH_ID("st m45pe40"    , 0xd8, 0x00134020, 0x100, 0x10000, 0x80000),
	FLASH_ID("st m45pe80"    , 0xd8, 0x00144020, 0x100, 0x10000, 0x100000),
	FLASH_ID("sp s25fl004"   , 0xd8, 0x00120201, 0x100, 0x10000, 0x80000),
	FLASH_ID("sp s25fl008"   , 0xd8, 0x00130201, 0x100, 0x10000, 0x100000),
	FLASH_ID("sp s25fl016"   , 0xd8, 0x00140201, 0x100, 0x10000, 0x200000),
	FLASH_ID("sp s25fl032"   , 0xd8, 0x00150201, 0x100, 0x10000, 0x400000),
	FLASH_ID("sp s25fl064"   , 0xd8, 0x00160201, 0x100, 0x10000, 0x800000),
	FLASH_ID("atmel 25f512"  , 0x52, 0x0065001F, 0x80 , 0x8000 , 0x10000),
	FLASH_ID("atmel 25f1024" , 0x52, 0x0060001F, 0x100, 0x8000 , 0x20000),
	FLASH_ID("atmel 25f2048" , 0x52, 0x0063001F, 0x100, 0x10000, 0x40000),
	FLASH_ID("atmel 25f4096" , 0x52, 0x0064001F, 0x100, 0x10000, 0x80000),
	FLASH_ID("atmel 25fs040" , 0xd7, 0x0004661F, 0x100, 0x10000, 0x80000),
	FLASH_ID("mac 25l512"    , 0xd8, 0x001020C2, 0x010, 0x10000, 0x10000),
	FLASH_ID("mac 25l1005"   , 0xd8, 0x001120C2, 0x010, 0x10000, 0x20000),
	FLASH_ID("mac 25l2005"   , 0xd8, 0x001220C2, 0x010, 0x10000, 0x40000),
	FLASH_ID("mac 25l4005"   , 0xd8, 0x001320C2, 0x010, 0x10000, 0x80000),
	FLASH_ID("mac 25l4005a"  , 0xd8, 0x001320C2, 0x010, 0x10000, 0x80000),
	FLASH_ID("mac 25l8005"   , 0xd8, 0x001420C2, 0x010, 0x10000, 0x100000),
	FLASH_ID("mac 25l1605"   , 0xd8, 0x001520C2, 0x100, 0x10000, 0x200000),
	FLASH_ID("mac 25l1605a"  , 0xd8, 0x001520C2, 0x010, 0x10000, 0x200000),
	FLASH_ID("mac 25l3205"   , 0xd8, 0x001620C2, 0x100, 0x10000, 0x400000),
	FLASH_ID("mac 25l3205a"  , 0xd8, 0x001620C2, 0x100, 0x10000, 0x400000),
	FLASH_ID("mac 25l6405"   , 0xd8, 0x001720C2, 0x100, 0x10000, 0x800000),
पूर्ण;

/* Define spear specअगरic काष्ठाures */

काष्ठा spear_snor_flash;

/**
 * काष्ठा spear_smi - Structure क्रम SMI Device
 *
 * @clk: functional घड़ी
 * @status: current status रेजिस्टर of SMI.
 * @clk_rate: functional घड़ी rate of SMI (शेष: SMI_MAX_CLOCK_FREQ)
 * @lock: lock to prevent parallel access of SMI.
 * @io_base: base address क्रम रेजिस्टरs of SMI.
 * @pdev: platक्रमm device
 * @cmd_complete: queue to रुको क्रम command completion of NOR-flash.
 * @num_flashes: number of flashes actually present on board.
 * @flash: separate काष्ठाure क्रम each Serial NOR-flash attached to SMI.
 */
काष्ठा spear_smi अणु
	काष्ठा clk *clk;
	u32 status;
	अचिन्हित दीर्घ clk_rate;
	काष्ठा mutex lock;
	व्योम __iomem *io_base;
	काष्ठा platक्रमm_device *pdev;
	रुको_queue_head_t cmd_complete;
	u32 num_flashes;
	काष्ठा spear_snor_flash *flash[MAX_NUM_FLASH_CHIP];
पूर्ण;

/**
 * काष्ठा spear_snor_flash - Structure क्रम Serial NOR Flash
 *
 * @bank: Bank number(0, 1, 2, 3) क्रम each NOR-flash.
 * @dev_id: Device ID of NOR-flash.
 * @lock: lock to manage flash पढ़ो, ग_लिखो and erase operations
 * @mtd: MTD info क्रम each NOR-flash.
 * @num_parts: Total number of partition in each bank of NOR-flash.
 * @parts: Partition info क्रम each bank of NOR-flash.
 * @page_size: Page size of NOR-flash.
 * @base_addr: Base address of NOR-flash.
 * @erase_cmd: erase command may vary on dअगरferent flash types
 * @fast_mode: flash supports पढ़ो in fast mode
 */
काष्ठा spear_snor_flash अणु
	u32 bank;
	u32 dev_id;
	काष्ठा mutex lock;
	काष्ठा mtd_info mtd;
	u32 num_parts;
	काष्ठा mtd_partition *parts;
	u32 page_size;
	व्योम __iomem *base_addr;
	u8 erase_cmd;
	u8 fast_mode;
पूर्ण;

अटल अंतरभूत काष्ठा spear_snor_flash *get_flash_data(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd, काष्ठा spear_snor_flash, mtd);
पूर्ण

/**
 * spear_smi_पढ़ो_sr - Read status रेजिस्टर of flash through SMI
 * @dev: काष्ठाure of SMI inक्रमmation.
 * @bank: bank to which flash is connected
 *
 * This routine will वापस the status रेजिस्टर of the flash chip present at the
 * given bank.
 */
अटल पूर्णांक spear_smi_पढ़ो_sr(काष्ठा spear_smi *dev, u32 bank)
अणु
	पूर्णांक ret;
	u32 ctrlreg1;

	mutex_lock(&dev->lock);
	dev->status = 0; /* Will be set in पूर्णांकerrupt handler */

	ctrlreg1 = पढ़ोl(dev->io_base + SMI_CR1);
	/* program smi in hw mode */
	ग_लिखोl(ctrlreg1 & ~(SW_MODE | WB_MODE), dev->io_base + SMI_CR1);

	/* perक्रमming a rsr inकाष्ठाion in hw mode */
	ग_लिखोl((bank << BANK_SHIFT) | RD_STATUS_REG | TFIE,
			dev->io_base + SMI_CR2);

	/* रुको क्रम tff */
	ret = रुको_event_पूर्णांकerruptible_समयout(dev->cmd_complete,
			dev->status & TFF, SMI_CMD_TIMEOUT);

	/* copy dev->status (lower 16 bits) in order to release lock */
	अगर (ret > 0)
		ret = dev->status & 0xffff;
	अन्यथा अगर (ret == 0)
		ret = -ETIMEDOUT;

	/* restore the ctrl regs state */
	ग_लिखोl(ctrlreg1, dev->io_base + SMI_CR1);
	ग_लिखोl(0, dev->io_base + SMI_CR2);
	mutex_unlock(&dev->lock);

	वापस ret;
पूर्ण

/**
 * spear_smi_रुको_till_पढ़ोy - रुको till flash is पढ़ोy
 * @dev: काष्ठाure of SMI inक्रमmation.
 * @bank: flash corresponding to this bank
 * @समयout: समयout क्रम busy रुको condition
 *
 * This routine checks क्रम WIP (ग_लिखो in progress) bit in Status रेजिस्टर
 * If successful the routine वापसs 0 अन्यथा -EBUSY
 */
अटल पूर्णांक spear_smi_रुको_till_पढ़ोy(काष्ठा spear_smi *dev, u32 bank,
		अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ finish;
	पूर्णांक status;

	finish = jअगरfies + समयout;
	करो अणु
		status = spear_smi_पढ़ो_sr(dev, bank);
		अगर (status < 0) अणु
			अगर (status == -ETIMEDOUT)
				जारी; /* try till finish */
			वापस status;
		पूर्ण अन्यथा अगर (!(status & SR_WIP)) अणु
			वापस 0;
		पूर्ण

		cond_resched();
	पूर्ण जबतक (!समय_after_eq(jअगरfies, finish));

	dev_err(&dev->pdev->dev, "smi controller is busy, timeout\n");
	वापस -EBUSY;
पूर्ण

/**
 * spear_smi_पूर्णांक_handler - SMI Interrupt Handler.
 * @irq: irq number
 * @dev_id: काष्ठाure of SMI device, embedded in dev_id.
 *
 * The handler clears all पूर्णांकerrupt conditions and records the status in
 * dev->status which is used by the driver later.
 */
अटल irqवापस_t spear_smi_पूर्णांक_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 status = 0;
	काष्ठा spear_smi *dev = dev_id;

	status = पढ़ोl(dev->io_base + SMI_SR);

	अगर (unlikely(!status))
		वापस IRQ_NONE;

	/* clear all पूर्णांकerrupt conditions */
	ग_लिखोl(0, dev->io_base + SMI_SR);

	/* copy the status रेजिस्टर in dev->status */
	dev->status |= status;

	/* send the completion */
	wake_up_पूर्णांकerruptible(&dev->cmd_complete);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * spear_smi_hw_init - initializes the smi controller.
 * @dev: काष्ठाure of smi device
 *
 * this routine initializes the smi controller wit the शेष values
 */
अटल व्योम spear_smi_hw_init(काष्ठा spear_smi *dev)
अणु
	अचिन्हित दीर्घ rate = 0;
	u32 prescale = 0;
	u32 val;

	rate = clk_get_rate(dev->clk);

	/* functional घड़ी of smi */
	prescale = DIV_ROUND_UP(rate, dev->clk_rate);

	/*
	 * setting the standard values, fast mode, prescaler क्रम
	 * SMI_MAX_CLOCK_FREQ (50MHz) operation and bank enable
	 */
	val = HOLD1 | BANK_EN | DSEL_TIME | (prescale << 8);

	mutex_lock(&dev->lock);
	/* clear all पूर्णांकerrupt conditions */
	ग_लिखोl(0, dev->io_base + SMI_SR);

	ग_लिखोl(val, dev->io_base + SMI_CR1);
	mutex_unlock(&dev->lock);
पूर्ण

/**
 * get_flash_index - match chip id from a flash list.
 * @flash_id: a valid nor flash chip id obtained from board.
 *
 * try to validate the chip id by matching from a list, अगर not found then simply
 * वापसs negative. In हाल of success वापसs index in to the flash devices
 * array.
 */
अटल पूर्णांक get_flash_index(u32 flash_id)
अणु
	पूर्णांक index;

	/* Matches chip-id to entire list of 'serial-nor flash' ids */
	क्रम (index = 0; index < ARRAY_SIZE(flash_devices); index++) अणु
		अगर (flash_devices[index].device_id == flash_id)
			वापस index;
	पूर्ण

	/* Memory chip is not listed and not supported */
	वापस -ENODEV;
पूर्ण

/**
 * spear_smi_ग_लिखो_enable - Enable the flash to करो ग_लिखो operation
 * @dev: काष्ठाure of SMI device
 * @bank: enable ग_लिखो क्रम flash connected to this bank
 *
 * Set ग_लिखो enable latch with Write Enable command.
 * Returns 0 on success.
 */
अटल पूर्णांक spear_smi_ग_लिखो_enable(काष्ठा spear_smi *dev, u32 bank)
अणु
	पूर्णांक ret;
	u32 ctrlreg1;

	mutex_lock(&dev->lock);
	dev->status = 0; /* Will be set in पूर्णांकerrupt handler */

	ctrlreg1 = पढ़ोl(dev->io_base + SMI_CR1);
	/* program smi in h/w mode */
	ग_लिखोl(ctrlreg1 & ~SW_MODE, dev->io_base + SMI_CR1);

	/* give the flash, ग_लिखो enable command */
	ग_लिखोl((bank << BANK_SHIFT) | WE | TFIE, dev->io_base + SMI_CR2);

	ret = रुको_event_पूर्णांकerruptible_समयout(dev->cmd_complete,
			dev->status & TFF, SMI_CMD_TIMEOUT);

	/* restore the ctrl regs state */
	ग_लिखोl(ctrlreg1, dev->io_base + SMI_CR1);
	ग_लिखोl(0, dev->io_base + SMI_CR2);

	अगर (ret == 0) अणु
		ret = -EIO;
		dev_err(&dev->pdev->dev,
			"smi controller failed on write enable\n");
	पूर्ण अन्यथा अगर (ret > 0) अणु
		/* check whether ग_लिखो mode status is set क्रम required bank */
		अगर (dev->status & (1 << (bank + WM_SHIFT)))
			ret = 0;
		अन्यथा अणु
			dev_err(&dev->pdev->dev, "couldn't enable write\n");
			ret = -EIO;
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल अंतरभूत u32
get_sector_erase_cmd(काष्ठा spear_snor_flash *flash, u32 offset)
अणु
	u32 cmd;
	u8 *x = (u8 *)&cmd;

	x[0] = flash->erase_cmd;
	x[1] = offset >> 16;
	x[2] = offset >> 8;
	x[3] = offset;

	वापस cmd;
पूर्ण

/**
 * spear_smi_erase_sector - erase one sector of flash
 * @dev: काष्ठाure of SMI inक्रमmation
 * @command: erase command to be send
 * @bank: bank to which this command needs to be send
 * @bytes: size of command
 *
 * Erase one sector of flash memory at offset ``offset'' which is any
 * address within the sector which should be erased.
 * Returns 0 अगर successful, non-zero otherwise.
 */
अटल पूर्णांक spear_smi_erase_sector(काष्ठा spear_smi *dev,
		u32 bank, u32 command, u32 bytes)
अणु
	u32 ctrlreg1 = 0;
	पूर्णांक ret;

	ret = spear_smi_रुको_till_पढ़ोy(dev, bank, SMI_MAX_TIME_OUT);
	अगर (ret)
		वापस ret;

	ret = spear_smi_ग_लिखो_enable(dev, bank);
	अगर (ret)
		वापस ret;

	mutex_lock(&dev->lock);

	ctrlreg1 = पढ़ोl(dev->io_base + SMI_CR1);
	ग_लिखोl((ctrlreg1 | SW_MODE) & ~WB_MODE, dev->io_base + SMI_CR1);

	/* send command in sw mode */
	ग_लिखोl(command, dev->io_base + SMI_TR);

	ग_लिखोl((bank << BANK_SHIFT) | SEND | TFIE | (bytes << TX_LEN_SHIFT),
			dev->io_base + SMI_CR2);

	ret = रुको_event_पूर्णांकerruptible_समयout(dev->cmd_complete,
			dev->status & TFF, SMI_CMD_TIMEOUT);

	अगर (ret == 0) अणु
		ret = -EIO;
		dev_err(&dev->pdev->dev, "sector erase failed\n");
	पूर्ण अन्यथा अगर (ret > 0)
		ret = 0; /* success */

	/* restore ctrl regs */
	ग_लिखोl(ctrlreg1, dev->io_base + SMI_CR1);
	ग_लिखोl(0, dev->io_base + SMI_CR2);

	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

/**
 * spear_mtd_erase - perक्रमm flash erase operation as requested by user
 * @mtd: Provides the memory अक्षरacteristics
 * @e_info: Provides the erase inक्रमmation
 *
 * Erase an address range on the flash chip. The address range may extend
 * one or more erase sectors. Return an error is there is a problem erasing.
 */
अटल पूर्णांक spear_mtd_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *e_info)
अणु
	काष्ठा spear_snor_flash *flash = get_flash_data(mtd);
	काष्ठा spear_smi *dev = mtd->priv;
	u32 addr, command, bank;
	पूर्णांक len, ret;

	अगर (!flash || !dev)
		वापस -ENODEV;

	bank = flash->bank;
	अगर (bank > dev->num_flashes - 1) अणु
		dev_err(&dev->pdev->dev, "Invalid Bank Num");
		वापस -EINVAL;
	पूर्ण

	addr = e_info->addr;
	len = e_info->len;

	mutex_lock(&flash->lock);

	/* now erase sectors in loop */
	जबतक (len) अणु
		command = get_sector_erase_cmd(flash, addr);
		/* preparing the command क्रम flash */
		ret = spear_smi_erase_sector(dev, bank, command, 4);
		अगर (ret) अणु
			mutex_unlock(&flash->lock);
			वापस ret;
		पूर्ण
		addr += mtd->erasesize;
		len -= mtd->erasesize;
	पूर्ण

	mutex_unlock(&flash->lock);

	वापस 0;
पूर्ण

/**
 * spear_mtd_पढ़ो - perक्रमms flash पढ़ो operation as requested by the user
 * @mtd: MTD inक्रमmation of the memory bank
 * @from: Address from which to start पढ़ो
 * @len: Number of bytes to be पढ़ो
 * @retlen: Fills the Number of bytes actually पढ़ो
 * @buf: Fills this after पढ़ोing
 *
 * Read an address range from the flash chip. The address range
 * may be any size provided it is within the physical boundaries.
 * Returns 0 on success, non zero otherwise
 */
अटल पूर्णांक spear_mtd_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, u8 *buf)
अणु
	काष्ठा spear_snor_flash *flash = get_flash_data(mtd);
	काष्ठा spear_smi *dev = mtd->priv;
	व्योम __iomem *src;
	u32 ctrlreg1, val;
	पूर्णांक ret;

	अगर (!flash || !dev)
		वापस -ENODEV;

	अगर (flash->bank > dev->num_flashes - 1) अणु
		dev_err(&dev->pdev->dev, "Invalid Bank Num");
		वापस -EINVAL;
	पूर्ण

	/* select address as per bank number */
	src = flash->base_addr + from;

	mutex_lock(&flash->lock);

	/* रुको till previous ग_लिखो/erase is करोne. */
	ret = spear_smi_रुको_till_पढ़ोy(dev, flash->bank, SMI_MAX_TIME_OUT);
	अगर (ret) अणु
		mutex_unlock(&flash->lock);
		वापस ret;
	पूर्ण

	mutex_lock(&dev->lock);
	/* put smi in hw mode not wbt mode */
	ctrlreg1 = val = पढ़ोl(dev->io_base + SMI_CR1);
	val &= ~(SW_MODE | WB_MODE);
	अगर (flash->fast_mode)
		val |= FAST_MODE;

	ग_लिखोl(val, dev->io_base + SMI_CR1);

	स_नकल_fromio(buf, src, len);

	/* restore ctrl reg1 */
	ग_लिखोl(ctrlreg1, dev->io_base + SMI_CR1);
	mutex_unlock(&dev->lock);

	*retlen = len;
	mutex_unlock(&flash->lock);

	वापस 0;
पूर्ण

/*
 * The purpose of this function is to ensure a स_नकल_toio() with byte ग_लिखोs
 * only. Its काष्ठाure is inspired from the ARM implementation of _स_नकल_toio()
 * which also करोes single byte ग_लिखोs but cannot be used here as this is just an
 * implementation detail and not part of the API. Not mentioning the comment
 * stating that _स_नकल_toio() should be optimized.
 */
अटल व्योम spear_smi_स_नकल_toio_b(अस्थिर व्योम __iomem *dest,
				    स्थिर व्योम *src, माप_प्रकार len)
अणु
	स्थिर अचिन्हित अक्षर *from = src;

	जबतक (len) अणु
		len--;
		ग_लिखोb(*from, dest);
		from++;
		dest++;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक spear_smi_cpy_toio(काष्ठा spear_smi *dev, u32 bank,
		व्योम __iomem *dest, स्थिर व्योम *src, माप_प्रकार len)
अणु
	पूर्णांक ret;
	u32 ctrlreg1;

	/* रुको until finished previous ग_लिखो command. */
	ret = spear_smi_रुको_till_पढ़ोy(dev, bank, SMI_MAX_TIME_OUT);
	अगर (ret)
		वापस ret;

	/* put smi in ग_लिखो enable */
	ret = spear_smi_ग_लिखो_enable(dev, bank);
	अगर (ret)
		वापस ret;

	/* put smi in hw, ग_लिखो burst mode */
	mutex_lock(&dev->lock);

	ctrlreg1 = पढ़ोl(dev->io_base + SMI_CR1);
	ग_लिखोl((ctrlreg1 | WB_MODE) & ~SW_MODE, dev->io_base + SMI_CR1);

	/*
	 * In Write Burst mode (WB_MODE), the specs states that ग_लिखोs must be:
	 * - incremental
	 * - of the same size
	 * The ARM implementation of स_नकल_toio() will optimize the number of
	 * I/O by using as much 4-byte ग_लिखोs as possible, surrounded by
	 * 2-byte/1-byte access अगर:
	 * - the destination is not 4-byte aligned
	 * - the length is not a multiple of 4-byte.
	 * Aव्योम this alternance of ग_लिखो access size by using our own 'byte
	 * access' helper अगर at least one of the two conditions above is true.
	 */
	अगर (IS_ALIGNED(len, माप(u32)) &&
	    IS_ALIGNED((uपूर्णांकptr_t)dest, माप(u32)))
		स_नकल_toio(dest, src, len);
	अन्यथा
		spear_smi_स_नकल_toio_b(dest, src, len);

	ग_लिखोl(ctrlreg1, dev->io_base + SMI_CR1);

	mutex_unlock(&dev->lock);
	वापस 0;
पूर्ण

/**
 * spear_mtd_ग_लिखो - perक्रमms ग_लिखो operation as requested by the user.
 * @mtd: MTD inक्रमmation of the memory bank.
 * @to:	Address to ग_लिखो.
 * @len: Number of bytes to be written.
 * @retlen: Number of bytes actually wrote.
 * @buf: Buffer from which the data to be taken.
 *
 * Write an address range to the flash chip. Data must be written in
 * flash_page_size chunks. The address range may be any size provided
 * it is within the physical boundaries.
 * Returns 0 on success, non zero otherwise
 */
अटल पूर्णांक spear_mtd_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
		माप_प्रकार *retlen, स्थिर u8 *buf)
अणु
	काष्ठा spear_snor_flash *flash = get_flash_data(mtd);
	काष्ठा spear_smi *dev = mtd->priv;
	व्योम __iomem *dest;
	u32 page_offset, page_size;
	पूर्णांक ret;

	अगर (!flash || !dev)
		वापस -ENODEV;

	अगर (flash->bank > dev->num_flashes - 1) अणु
		dev_err(&dev->pdev->dev, "Invalid Bank Num");
		वापस -EINVAL;
	पूर्ण

	/* select address as per bank number */
	dest = flash->base_addr + to;
	mutex_lock(&flash->lock);

	page_offset = (u32)to % flash->page_size;

	/* करो अगर all the bytes fit onto one page */
	अगर (page_offset + len <= flash->page_size) अणु
		ret = spear_smi_cpy_toio(dev, flash->bank, dest, buf, len);
		अगर (!ret)
			*retlen += len;
	पूर्ण अन्यथा अणु
		u32 i;

		/* the size of data reमुख्यing on the first page */
		page_size = flash->page_size - page_offset;

		ret = spear_smi_cpy_toio(dev, flash->bank, dest, buf,
				page_size);
		अगर (ret)
			जाओ err_ग_लिखो;
		अन्यथा
			*retlen += page_size;

		/* ग_लिखो everything in pagesize chunks */
		क्रम (i = page_size; i < len; i += page_size) अणु
			page_size = len - i;
			अगर (page_size > flash->page_size)
				page_size = flash->page_size;

			ret = spear_smi_cpy_toio(dev, flash->bank, dest + i,
					buf + i, page_size);
			अगर (ret)
				अवरोध;
			अन्यथा
				*retlen += page_size;
		पूर्ण
	पूर्ण

err_ग_लिखो:
	mutex_unlock(&flash->lock);

	वापस ret;
पूर्ण

/**
 * spear_smi_probe_flash - Detects the NOR Flash chip.
 * @dev: काष्ठाure of SMI inक्रमmation.
 * @bank: bank on which flash must be probed
 *
 * This routine will check whether there exists a flash chip on a given memory
 * bank ID.
 * Return index of the probed flash in flash devices काष्ठाure
 */
अटल पूर्णांक spear_smi_probe_flash(काष्ठा spear_smi *dev, u32 bank)
अणु
	पूर्णांक ret;
	u32 val = 0;

	ret = spear_smi_रुको_till_पढ़ोy(dev, bank, SMI_PROBE_TIMEOUT);
	अगर (ret)
		वापस ret;

	mutex_lock(&dev->lock);

	dev->status = 0; /* Will be set in पूर्णांकerrupt handler */
	/* put smi in sw mode */
	val = पढ़ोl(dev->io_base + SMI_CR1);
	ग_लिखोl(val | SW_MODE, dev->io_base + SMI_CR1);

	/* send पढ़ोid command in sw mode */
	ग_लिखोl(OPCODE_RDID, dev->io_base + SMI_TR);

	val = (bank << BANK_SHIFT) | SEND | (1 << TX_LEN_SHIFT) |
		(3 << RX_LEN_SHIFT) | TFIE;
	ग_लिखोl(val, dev->io_base + SMI_CR2);

	/* रुको क्रम TFF */
	ret = रुको_event_पूर्णांकerruptible_समयout(dev->cmd_complete,
			dev->status & TFF, SMI_CMD_TIMEOUT);
	अगर (ret <= 0) अणु
		ret = -ENODEV;
		जाओ err_probe;
	पूर्ण

	/* get memory chip id */
	val = पढ़ोl(dev->io_base + SMI_RR);
	val &= 0x00ffffff;
	ret = get_flash_index(val);

err_probe:
	/* clear sw mode */
	val = पढ़ोl(dev->io_base + SMI_CR1);
	ग_लिखोl(val & ~SW_MODE, dev->io_base + SMI_CR1);

	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण


#अगर_घोषित CONFIG_OF
अटल पूर्णांक spear_smi_probe_config_dt(काष्ठा platक्रमm_device *pdev,
				     काष्ठा device_node *np)
अणु
	काष्ठा spear_smi_plat_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *pp;
	स्थिर __be32 *addr;
	u32 val;
	पूर्णांक len;
	पूर्णांक i = 0;

	अगर (!np)
		वापस -ENODEV;

	of_property_पढ़ो_u32(np, "clock-rate", &val);
	pdata->clk_rate = val;

	pdata->board_flash_info = devm_kzalloc(&pdev->dev,
					       माप(*pdata->board_flash_info),
					       GFP_KERNEL);
	अगर (!pdata->board_flash_info)
		वापस -ENOMEM;

	/* Fill काष्ठाs क्रम each subnode (flash device) */
	क्रम_each_child_of_node(np, pp) अणु
		pdata->np[i] = pp;

		/* Read base-addr and size from DT */
		addr = of_get_property(pp, "reg", &len);
		pdata->board_flash_info->mem_base = be32_to_cpup(&addr[0]);
		pdata->board_flash_info->size = be32_to_cpup(&addr[1]);

		अगर (of_get_property(pp, "st,smi-fast-mode", शून्य))
			pdata->board_flash_info->fast_mode = 1;

		i++;
	पूर्ण

	pdata->num_flashes = i;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक spear_smi_probe_config_dt(काष्ठा platक्रमm_device *pdev,
				     काष्ठा device_node *np)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक spear_smi_setup_banks(काष्ठा platक्रमm_device *pdev,
				 u32 bank, काष्ठा device_node *np)
अणु
	काष्ठा spear_smi *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा spear_smi_flash_info *flash_info;
	काष्ठा spear_smi_plat_data *pdata;
	काष्ठा spear_snor_flash *flash;
	काष्ठा mtd_partition *parts = शून्य;
	पूर्णांक count = 0;
	पूर्णांक flash_index;
	पूर्णांक ret = 0;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (bank > pdata->num_flashes - 1)
		वापस -EINVAL;

	flash_info = &pdata->board_flash_info[bank];
	अगर (!flash_info)
		वापस -ENODEV;

	flash = devm_kzalloc(&pdev->dev, माप(*flash), GFP_ATOMIC);
	अगर (!flash)
		वापस -ENOMEM;
	flash->bank = bank;
	flash->fast_mode = flash_info->fast_mode ? 1 : 0;
	mutex_init(&flash->lock);

	/* verअगरy whether nor flash is really present on board */
	flash_index = spear_smi_probe_flash(dev, bank);
	अगर (flash_index < 0) अणु
		dev_info(&dev->pdev->dev, "smi-nor%d not found\n", bank);
		वापस flash_index;
	पूर्ण
	/* map the memory क्रम nor flash chip */
	flash->base_addr = devm_ioremap(&pdev->dev, flash_info->mem_base,
					flash_info->size);
	अगर (!flash->base_addr)
		वापस -EIO;

	dev->flash[bank] = flash;
	flash->mtd.priv = dev;

	अगर (flash_info->name)
		flash->mtd.name = flash_info->name;
	अन्यथा
		flash->mtd.name = flash_devices[flash_index].name;

	flash->mtd.dev.parent = &pdev->dev;
	mtd_set_of_node(&flash->mtd, np);
	flash->mtd.type = MTD_NORFLASH;
	flash->mtd.ग_लिखोsize = 1;
	flash->mtd.flags = MTD_CAP_NORFLASH;
	flash->mtd.size = flash_info->size;
	flash->mtd.erasesize = flash_devices[flash_index].sectorsize;
	flash->page_size = flash_devices[flash_index].pagesize;
	flash->mtd.ग_लिखोbufsize = flash->page_size;
	flash->erase_cmd = flash_devices[flash_index].erase_cmd;
	flash->mtd._erase = spear_mtd_erase;
	flash->mtd._पढ़ो = spear_mtd_पढ़ो;
	flash->mtd._ग_लिखो = spear_mtd_ग_लिखो;
	flash->dev_id = flash_devices[flash_index].device_id;

	dev_info(&dev->pdev->dev, "mtd .name=%s .size=%llx(%lluM)\n",
			flash->mtd.name, flash->mtd.size,
			flash->mtd.size / (1024 * 1024));

	dev_info(&dev->pdev->dev, ".erasesize = 0x%x(%uK)\n",
			flash->mtd.erasesize, flash->mtd.erasesize / 1024);

#अगर_अघोषित CONFIG_OF
	अगर (flash_info->partitions) अणु
		parts = flash_info->partitions;
		count = flash_info->nr_partitions;
	पूर्ण
#पूर्ण_अगर

	ret = mtd_device_रेजिस्टर(&flash->mtd, parts, count);
	अगर (ret) अणु
		dev_err(&dev->pdev->dev, "Err MTD partition=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * spear_smi_probe - Entry routine
 * @pdev: platक्रमm device काष्ठाure
 *
 * This is the first routine which माला_लो invoked during booting and करोes all
 * initialization/allocation work. The routine looks क्रम available memory banks,
 * and करो proper init क्रम any found one.
 * Returns 0 on success, non zero otherwise
 */
अटल पूर्णांक spear_smi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा spear_smi_plat_data *pdata = शून्य;
	काष्ठा spear_smi *dev;
	काष्ठा resource *smi_base;
	पूर्णांक irq, ret = 0;
	पूर्णांक i;

	अगर (np) अणु
		pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		pdev->dev.platक्रमm_data = pdata;
		ret = spear_smi_probe_config_dt(pdev, np);
		अगर (ret) अणु
			ret = -ENODEV;
			dev_err(&pdev->dev, "no platform data\n");
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		pdata = dev_get_platdata(&pdev->dev);
		अगर (!pdata) अणु
			ret = -ENODEV;
			dev_err(&pdev->dev, "no platform data\n");
			जाओ err;
		पूर्ण
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_ATOMIC);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	smi_base = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	dev->io_base = devm_ioremap_resource(&pdev->dev, smi_base);
	अगर (IS_ERR(dev->io_base)) अणु
		ret = PTR_ERR(dev->io_base);
		जाओ err;
	पूर्ण

	dev->pdev = pdev;
	dev->clk_rate = pdata->clk_rate;

	अगर (dev->clk_rate > SMI_MAX_CLOCK_FREQ)
		dev->clk_rate = SMI_MAX_CLOCK_FREQ;

	dev->num_flashes = pdata->num_flashes;

	अगर (dev->num_flashes > MAX_NUM_FLASH_CHIP) अणु
		dev_err(&pdev->dev, "exceeding max number of flashes\n");
		dev->num_flashes = MAX_NUM_FLASH_CHIP;
	पूर्ण

	dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk)) अणु
		ret = PTR_ERR(dev->clk);
		जाओ err;
	पूर्ण

	ret = clk_prepare_enable(dev->clk);
	अगर (ret)
		जाओ err;

	ret = devm_request_irq(&pdev->dev, irq, spear_smi_पूर्णांक_handler, 0,
			       pdev->name, dev);
	अगर (ret) अणु
		dev_err(&dev->pdev->dev, "SMI IRQ allocation failed\n");
		जाओ err_irq;
	पूर्ण

	mutex_init(&dev->lock);
	init_रुकोqueue_head(&dev->cmd_complete);
	spear_smi_hw_init(dev);
	platक्रमm_set_drvdata(pdev, dev);

	/* loop क्रम each serial nor-flash which is connected to smi */
	क्रम (i = 0; i < dev->num_flashes; i++) अणु
		ret = spear_smi_setup_banks(pdev, i, pdata->np[i]);
		अगर (ret) अणु
			dev_err(&dev->pdev->dev, "bank setup failed\n");
			जाओ err_irq;
		पूर्ण
	पूर्ण

	वापस 0;

err_irq:
	clk_disable_unprepare(dev->clk);
err:
	वापस ret;
पूर्ण

/**
 * spear_smi_हटाओ - Exit routine
 * @pdev: platक्रमm device काष्ठाure
 *
 * मुक्त all allocations and delete the partitions.
 */
अटल पूर्णांक spear_smi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spear_smi *dev;
	काष्ठा spear_snor_flash *flash;
	पूर्णांक ret, i;

	dev = platक्रमm_get_drvdata(pdev);
	अगर (!dev) अणु
		dev_err(&pdev->dev, "dev is null\n");
		वापस -ENODEV;
	पूर्ण

	/* clean up क्रम all nor flash */
	क्रम (i = 0; i < dev->num_flashes; i++) अणु
		flash = dev->flash[i];
		अगर (!flash)
			जारी;

		/* clean up mtd stuff */
		ret = mtd_device_unरेजिस्टर(&flash->mtd);
		अगर (ret)
			dev_err(&pdev->dev, "error removing mtd\n");
	पूर्ण

	clk_disable_unprepare(dev->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक spear_smi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spear_smi *sdev = dev_get_drvdata(dev);

	अगर (sdev && sdev->clk)
		clk_disable_unprepare(sdev->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक spear_smi_resume(काष्ठा device *dev)
अणु
	काष्ठा spear_smi *sdev = dev_get_drvdata(dev);
	पूर्णांक ret = -EPERM;

	अगर (sdev && sdev->clk)
		ret = clk_prepare_enable(sdev->clk);

	अगर (!ret)
		spear_smi_hw_init(sdev);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(spear_smi_pm_ops, spear_smi_suspend, spear_smi_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id spear_smi_id_table[] = अणु
	अणु .compatible = "st,spear600-smi" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spear_smi_id_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver spear_smi_driver = अणु
	.driver = अणु
		.name = "smi",
		.bus = &platक्रमm_bus_type,
		.of_match_table = of_match_ptr(spear_smi_id_table),
		.pm = &spear_smi_pm_ops,
	पूर्ण,
	.probe = spear_smi_probe,
	.हटाओ = spear_smi_हटाओ,
पूर्ण;
module_platक्रमm_driver(spear_smi_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ashish Priyadarshi, Shiraz Hashim <shiraz.linux.kernel@gmail.com>");
MODULE_DESCRIPTION("MTD SMI driver for serial nor flash chips");
