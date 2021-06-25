<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bcma/bcma.h>

#समावेश "bcm47xxsflash.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Serial flash driver for BCMA bus");

अटल स्थिर अक्षर * स्थिर probes[] = अणु "bcm47xxpart", शून्य पूर्ण;

/**************************************************
 * Various helpers
 **************************************************/

अटल व्योम bcm47xxsflash_cmd(काष्ठा bcm47xxsflash *b47s, u32 opcode)
अणु
	पूर्णांक i;

	b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHCTL, BCMA_CC_FLASHCTL_START | opcode);
	क्रम (i = 0; i < 1000; i++) अणु
		अगर (!(b47s->cc_पढ़ो(b47s, BCMA_CC_FLASHCTL) &
		      BCMA_CC_FLASHCTL_BUSY))
			वापस;
		cpu_relax();
	पूर्ण
	pr_err("Control command failed (timeout)!\n");
पूर्ण

अटल पूर्णांक bcm47xxsflash_poll(काष्ठा bcm47xxsflash *b47s, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ deadline = jअगरfies + समयout;

	करो अणु
		चयन (b47s->type) अणु
		हाल BCM47XXSFLASH_TYPE_ST:
			bcm47xxsflash_cmd(b47s, OPCODE_ST_RDSR);
			अगर (!(b47s->cc_पढ़ो(b47s, BCMA_CC_FLASHDATA) &
			      SR_ST_WIP))
				वापस 0;
			अवरोध;
		हाल BCM47XXSFLASH_TYPE_ATMEL:
			bcm47xxsflash_cmd(b47s, OPCODE_AT_STATUS);
			अगर (b47s->cc_पढ़ो(b47s, BCMA_CC_FLASHDATA) &
			    SR_AT_READY)
				वापस 0;
			अवरोध;
		पूर्ण

		cpu_relax();
		udelay(1);
	पूर्ण जबतक (!समय_after_eq(jअगरfies, deadline));

	pr_err("Timeout waiting for flash to be ready!\n");

	वापस -EBUSY;
पूर्ण

/**************************************************
 * MTD ops
 **************************************************/

अटल पूर्णांक bcm47xxsflash_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *erase)
अणु
	काष्ठा bcm47xxsflash *b47s = mtd->priv;

	चयन (b47s->type) अणु
	हाल BCM47XXSFLASH_TYPE_ST:
		bcm47xxsflash_cmd(b47s, OPCODE_ST_WREN);
		b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHADDR, erase->addr);
		/* Newer flashes have "sub-sectors" which can be erased
		 * independently with a new command: ST_SSE. The ST_SE command
		 * erases 64KB just as beक्रमe.
		 */
		अगर (b47s->blocksize < (64 * 1024))
			bcm47xxsflash_cmd(b47s, OPCODE_ST_SSE);
		अन्यथा
			bcm47xxsflash_cmd(b47s, OPCODE_ST_SE);
		अवरोध;
	हाल BCM47XXSFLASH_TYPE_ATMEL:
		b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHADDR, erase->addr << 1);
		bcm47xxsflash_cmd(b47s, OPCODE_AT_PAGE_ERASE);
		अवरोध;
	पूर्ण

	वापस bcm47xxsflash_poll(b47s, HZ);
पूर्ण

अटल पूर्णांक bcm47xxsflash_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			      माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा bcm47xxsflash *b47s = mtd->priv;
	माप_प्रकार orig_len = len;

	/* Check address range */
	अगर ((from + len) > mtd->size)
		वापस -EINVAL;

	/* Read as much as possible using fast MMIO winकरोw */
	अगर (from < BCM47XXSFLASH_WINDOW_SZ) अणु
		माप_प्रकार स_नकल_len;

		स_नकल_len = min(len, (माप_प्रकार)(BCM47XXSFLASH_WINDOW_SZ - from));
		स_नकल_fromio(buf, b47s->winकरोw + from, स_नकल_len);
		from += स_नकल_len;
		len -= स_नकल_len;
		buf += स_नकल_len;
	पूर्ण

	/* Use indirect access क्रम content out of the winकरोw */
	क्रम (; len; len--) अणु
		b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHADDR, from++);
		bcm47xxsflash_cmd(b47s, OPCODE_ST_READ4B);
		*buf++ = b47s->cc_पढ़ो(b47s, BCMA_CC_FLASHDATA);
	पूर्ण

	*retlen = orig_len;

	वापस orig_len;
पूर्ण

अटल पूर्णांक bcm47xxsflash_ग_लिखो_st(काष्ठा mtd_info *mtd, u32 offset, माप_प्रकार len,
				  स्थिर u_अक्षर *buf)
अणु
	काष्ठा bcm47xxsflash *b47s = mtd->priv;
	पूर्णांक written = 0;

	/* Enable ग_लिखोs */
	bcm47xxsflash_cmd(b47s, OPCODE_ST_WREN);

	/* Write first byte */
	b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHADDR, offset);
	b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHDATA, *buf++);

	/* Program page */
	अगर (b47s->bcma_cc->core->id.rev < 20) अणु
		bcm47xxsflash_cmd(b47s, OPCODE_ST_PP);
		वापस 1; /* 1B written */
	पूर्ण

	/* Program page and set CSA (on newer chips we can जारी writing) */
	bcm47xxsflash_cmd(b47s, OPCODE_ST_CSA | OPCODE_ST_PP);
	offset++;
	len--;
	written++;

	जबतक (len > 0) अणु
		/* Page boundary, another function call is needed */
		अगर ((offset & 0xFF) == 0)
			अवरोध;

		bcm47xxsflash_cmd(b47s, OPCODE_ST_CSA | *buf++);
		offset++;
		len--;
		written++;
	पूर्ण

	/* All करोne, drop CSA & poll */
	b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHCTL, 0);
	udelay(1);
	अगर (bcm47xxsflash_poll(b47s, HZ / 10))
		pr_err("Flash rejected dropping CSA\n");

	वापस written;
पूर्ण

अटल पूर्णांक bcm47xxsflash_ग_लिखो_at(काष्ठा mtd_info *mtd, u32 offset, माप_प्रकार len,
				  स्थिर u_अक्षर *buf)
अणु
	काष्ठा bcm47xxsflash *b47s = mtd->priv;
	u32 mask = b47s->blocksize - 1;
	u32 page = (offset & ~mask) << 1;
	u32 byte = offset & mask;
	पूर्णांक written = 0;

	/* If we करोn't overग_लिखो whole page, पढ़ो it to the buffer first */
	अगर (byte || (len < b47s->blocksize)) अणु
		पूर्णांक err;

		b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHADDR, page);
		bcm47xxsflash_cmd(b47s, OPCODE_AT_BUF1_LOAD);
		/* 250 us क्रम AT45DB321B */
		err = bcm47xxsflash_poll(b47s, HZ / 1000);
		अगर (err) अणु
			pr_err("Timeout reading page 0x%X info buffer\n", page);
			वापस err;
		पूर्ण
	पूर्ण

	/* Change buffer content with our data */
	जबतक (len > 0) अणु
		/* Page boundary, another function call is needed */
		अगर (byte == b47s->blocksize)
			अवरोध;

		b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHADDR, byte++);
		b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHDATA, *buf++);
		bcm47xxsflash_cmd(b47s, OPCODE_AT_BUF1_WRITE);
		len--;
		written++;
	पूर्ण

	/* Program page with the buffer content */
	b47s->cc_ग_लिखो(b47s, BCMA_CC_FLASHADDR, page);
	bcm47xxsflash_cmd(b47s, OPCODE_AT_BUF1_PROGRAM);

	वापस written;
पूर्ण

अटल पूर्णांक bcm47xxsflash_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
			       माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा bcm47xxsflash *b47s = mtd->priv;
	पूर्णांक written;

	/* Writing functions can वापस without writing all passed data, क्रम
	 * example when the hardware is too old or when we git page boundary.
	 */
	जबतक (len > 0) अणु
		चयन (b47s->type) अणु
		हाल BCM47XXSFLASH_TYPE_ST:
			written = bcm47xxsflash_ग_लिखो_st(mtd, to, len, buf);
			अवरोध;
		हाल BCM47XXSFLASH_TYPE_ATMEL:
			written = bcm47xxsflash_ग_लिखो_at(mtd, to, len, buf);
			अवरोध;
		शेष:
			BUG_ON(1);
		पूर्ण
		अगर (written < 0) अणु
			pr_err("Error writing at offset 0x%llX\n", to);
			वापस written;
		पूर्ण
		to += (loff_t)written;
		len -= written;
		*retlen += written;
		buf += written;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bcm47xxsflash_fill_mtd(काष्ठा bcm47xxsflash *b47s,
				   काष्ठा device *dev)
अणु
	काष्ठा mtd_info *mtd = &b47s->mtd;

	mtd->priv = b47s;
	mtd->dev.parent = dev;
	mtd->name = "bcm47xxsflash";

	mtd->type = MTD_NORFLASH;
	mtd->flags = MTD_CAP_NORFLASH;
	mtd->size = b47s->size;
	mtd->erasesize = b47s->blocksize;
	mtd->ग_लिखोsize = 1;
	mtd->ग_लिखोbufsize = 1;

	mtd->_erase = bcm47xxsflash_erase;
	mtd->_पढ़ो = bcm47xxsflash_पढ़ो;
	mtd->_ग_लिखो = bcm47xxsflash_ग_लिखो;
पूर्ण

/**************************************************
 * BCMA
 **************************************************/

अटल पूर्णांक bcm47xxsflash_bcma_cc_पढ़ो(काष्ठा bcm47xxsflash *b47s, u16 offset)
अणु
	वापस bcma_cc_पढ़ो32(b47s->bcma_cc, offset);
पूर्ण

अटल व्योम bcm47xxsflash_bcma_cc_ग_लिखो(काष्ठा bcm47xxsflash *b47s, u16 offset,
					u32 value)
अणु
	bcma_cc_ग_लिखो32(b47s->bcma_cc, offset, value);
पूर्ण

अटल पूर्णांक bcm47xxsflash_bcma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcma_sflash *sflash = dev_get_platdata(dev);
	काष्ठा bcm47xxsflash *b47s;
	काष्ठा resource *res;
	पूर्णांक err;

	b47s = devm_kzalloc(dev, माप(*b47s), GFP_KERNEL);
	अगर (!b47s)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "invalid resource\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!devm_request_mem_region(dev, res->start, resource_size(res),
				     res->name)) अणु
		dev_err(dev, "can't request region for resource %pR\n", res);
		वापस -EBUSY;
	पूर्ण

	b47s->bcma_cc = container_of(sflash, काष्ठा bcma_drv_cc, sflash);
	b47s->cc_पढ़ो = bcm47xxsflash_bcma_cc_पढ़ो;
	b47s->cc_ग_लिखो = bcm47xxsflash_bcma_cc_ग_लिखो;

	/*
	 * On old MIPS devices cache was magically invalidated when needed,
	 * allowing us to use cached access and gain some perक्रमmance. Trying
	 * the same on ARM based BCM53573 results in flash corruptions, we need
	 * to use uncached access क्रम it.
	 *
	 * It may be arch specअगरic, but right now there is only 1 ARM SoC using
	 * this driver, so let's follow Broadcom's reference code and check
	 * ChipCommon revision.
	 */
	अगर (b47s->bcma_cc->core->id.rev == 54)
		b47s->winकरोw = ioremap(res->start, resource_size(res));
	अन्यथा
		b47s->winकरोw = ioremap_cache(res->start, resource_size(res));
	अगर (!b47s->winकरोw) अणु
		dev_err(dev, "ioremap failed for resource %pR\n", res);
		वापस -ENOMEM;
	पूर्ण

	चयन (b47s->bcma_cc->capabilities & BCMA_CC_CAP_FLASHT) अणु
	हाल BCMA_CC_FLASHT_STSER:
		b47s->type = BCM47XXSFLASH_TYPE_ST;
		अवरोध;
	हाल BCMA_CC_FLASHT_ATSER:
		b47s->type = BCM47XXSFLASH_TYPE_ATMEL;
		अवरोध;
	पूर्ण

	b47s->blocksize = sflash->blocksize;
	b47s->numblocks = sflash->numblocks;
	b47s->size = sflash->size;
	bcm47xxsflash_fill_mtd(b47s, &pdev->dev);

	platक्रमm_set_drvdata(pdev, b47s);

	err = mtd_device_parse_रेजिस्टर(&b47s->mtd, probes, शून्य, शून्य, 0);
	अगर (err) अणु
		pr_err("Failed to register MTD device: %d\n", err);
		iounmap(b47s->winकरोw);
		वापस err;
	पूर्ण

	अगर (bcm47xxsflash_poll(b47s, HZ / 10))
		pr_warn("Serial flash busy\n");

	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xxsflash_bcma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm47xxsflash *b47s = platक्रमm_get_drvdata(pdev);

	mtd_device_unरेजिस्टर(&b47s->mtd);
	iounmap(b47s->winकरोw);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcma_sflash_driver = अणु
	.probe	= bcm47xxsflash_bcma_probe,
	.हटाओ = bcm47xxsflash_bcma_हटाओ,
	.driver = अणु
		.name = "bcma_sflash",
	पूर्ण,
पूर्ण;

/**************************************************
 * Init
 **************************************************/

module_platक्रमm_driver(bcma_sflash_driver);
