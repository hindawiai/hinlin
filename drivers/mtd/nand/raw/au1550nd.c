<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2004 Embedded Edge, LLC
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1550nd.h>


काष्ठा au1550nd_ctx अणु
	काष्ठा nand_controller controller;
	काष्ठा nand_chip chip;

	पूर्णांक cs;
	व्योम __iomem *base;
पूर्ण;

अटल काष्ठा au1550nd_ctx *chip_to_au_ctx(काष्ठा nand_chip *this)
अणु
	वापस container_of(this, काष्ठा au1550nd_ctx, chip);
पूर्ण

/**
 * au_ग_लिखो_buf -  ग_लिखो buffer to chip
 * @this:	न_अंकD chip object
 * @buf:	data buffer
 * @len:	number of bytes to ग_लिखो
 *
 * ग_लिखो function क्रम 8bit buswidth
 */
अटल व्योम au_ग_लिखो_buf(काष्ठा nand_chip *this, स्थिर व्योम *buf,
			 अचिन्हित पूर्णांक len)
अणु
	काष्ठा au1550nd_ctx *ctx = chip_to_au_ctx(this);
	स्थिर u8 *p = buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		ग_लिखोb(p[i], ctx->base + MEM_STन_अंकD_DATA);
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण
पूर्ण

/**
 * au_पढ़ो_buf -  पढ़ो chip data पूर्णांकo buffer
 * @this:	न_अंकD chip object
 * @buf:	buffer to store date
 * @len:	number of bytes to पढ़ो
 *
 * पढ़ो function क्रम 8bit buswidth
 */
अटल व्योम au_पढ़ो_buf(काष्ठा nand_chip *this, व्योम *buf,
			अचिन्हित पूर्णांक len)
अणु
	काष्ठा au1550nd_ctx *ctx = chip_to_au_ctx(this);
	u8 *p = buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		p[i] = पढ़ोb(ctx->base + MEM_STन_अंकD_DATA);
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण
पूर्ण

/**
 * au_ग_लिखो_buf16 -  ग_लिखो buffer to chip
 * @this:	न_अंकD chip object
 * @buf:	data buffer
 * @len:	number of bytes to ग_लिखो
 *
 * ग_लिखो function क्रम 16bit buswidth
 */
अटल व्योम au_ग_लिखो_buf16(काष्ठा nand_chip *this, स्थिर व्योम *buf,
			   अचिन्हित पूर्णांक len)
अणु
	काष्ठा au1550nd_ctx *ctx = chip_to_au_ctx(this);
	स्थिर u16 *p = buf;
	अचिन्हित पूर्णांक i;

	len >>= 1;
	क्रम (i = 0; i < len; i++) अणु
		ग_लिखोw(p[i], ctx->base + MEM_STन_अंकD_DATA);
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण
पूर्ण

/**
 * au_पढ़ो_buf16 -  पढ़ो chip data पूर्णांकo buffer
 * @this:	न_अंकD chip object
 * @buf:	buffer to store date
 * @len:	number of bytes to पढ़ो
 *
 * पढ़ो function क्रम 16bit buswidth
 */
अटल व्योम au_पढ़ो_buf16(काष्ठा nand_chip *this, व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा au1550nd_ctx *ctx = chip_to_au_ctx(this);
	अचिन्हित पूर्णांक i;
	u16 *p = buf;

	len >>= 1;
	क्रम (i = 0; i < len; i++) अणु
		p[i] = पढ़ोw(ctx->base + MEM_STन_अंकD_DATA);
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण
पूर्ण

अटल पूर्णांक find_nand_cs(अचिन्हित दीर्घ nand_base)
अणु
	व्योम __iomem *base =
			(व्योम __iomem *)KSEG1ADDR(AU1000_STATIC_MEM_PHYS_ADDR);
	अचिन्हित दीर्घ addr, staddr, start, mask, end;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		addr = 0x1000 + (i * 0x10);			/* CSx */
		staddr = __raw_पढ़ोl(base + addr + 0x08);	/* STADDRx */
		/* figure out the decoded range of this CS */
		start = (staddr << 4) & 0xfffc0000;
		mask = (staddr << 18) & 0xfffc0000;
		end = (start | (start - 1)) & ~(start ^ mask);
		अगर ((nand_base >= start) && (nand_base < end))
			वापस i;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक au1550nd_रुकोrdy(काष्ठा nand_chip *this, अचिन्हित पूर्णांक समयout_ms)
अणु
	अचिन्हित दीर्घ समयout_jअगरfies = jअगरfies;

	समयout_jअगरfies += msecs_to_jअगरfies(समयout_ms) + 1;
	करो अणु
		अगर (alchemy_rdsmem(AU1000_MEM_STSTAT) & 0x1)
			वापस 0;

		usleep_range(10, 100);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout_jअगरfies));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक au1550nd_exec_instr(काष्ठा nand_chip *this,
			       स्थिर काष्ठा nand_op_instr *instr)
अणु
	काष्ठा au1550nd_ctx *ctx = chip_to_au_ctx(this);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		ग_लिखोb(instr->ctx.cmd.opcode,
		       ctx->base + MEM_STन_अंकD_CMD);
		/* Drain the ग_लिखोbuffer */
		wmb();
		अवरोध;

	हाल न_अंकD_OP_ADDR_INSTR:
		क्रम (i = 0; i < instr->ctx.addr.naddrs; i++) अणु
			ग_लिखोb(instr->ctx.addr.addrs[i],
			       ctx->base + MEM_STन_अंकD_ADDR);
			/* Drain the ग_लिखोbuffer */
			wmb();
		पूर्ण
		अवरोध;

	हाल न_अंकD_OP_DATA_IN_INSTR:
		अगर ((this->options & न_अंकD_BUSWIDTH_16) &&
		    !instr->ctx.data.क्रमce_8bit)
			au_पढ़ो_buf16(this, instr->ctx.data.buf.in,
				      instr->ctx.data.len);
		अन्यथा
			au_पढ़ो_buf(this, instr->ctx.data.buf.in,
				    instr->ctx.data.len);
		अवरोध;

	हाल न_अंकD_OP_DATA_OUT_INSTR:
		अगर ((this->options & न_अंकD_BUSWIDTH_16) &&
		    !instr->ctx.data.क्रमce_8bit)
			au_ग_लिखो_buf16(this, instr->ctx.data.buf.out,
				       instr->ctx.data.len);
		अन्यथा
			au_ग_लिखो_buf(this, instr->ctx.data.buf.out,
				     instr->ctx.data.len);
		अवरोध;

	हाल न_अंकD_OP_WAITRDY_INSTR:
		ret = au1550nd_रुकोrdy(this, instr->ctx.रुकोrdy.समयout_ms);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (instr->delay_ns)
		ndelay(instr->delay_ns);

	वापस ret;
पूर्ण

अटल पूर्णांक au1550nd_exec_op(काष्ठा nand_chip *this,
			    स्थिर काष्ठा nand_operation *op,
			    bool check_only)
अणु
	काष्ठा au1550nd_ctx *ctx = chip_to_au_ctx(this);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (check_only)
		वापस 0;

	/* निश्चित (क्रमce निश्चित) chip enable */
	alchemy_wrsmem((1 << (4 + ctx->cs)), AU1000_MEM_STNDCTL);
	/* Drain the ग_लिखोbuffer */
	wmb();

	क्रम (i = 0; i < op->ninstrs; i++) अणु
		ret = au1550nd_exec_instr(this, &op->instrs[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	/* deनिश्चित chip enable */
	alchemy_wrsmem(0, AU1000_MEM_STNDCTL);
	/* Drain the ग_लिखोbuffer */
	wmb();

	वापस ret;
पूर्ण

अटल पूर्णांक au1550nd_attach_chip(काष्ठा nand_chip *chip)
अणु
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_UNKNOWN)
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops au1550nd_ops = अणु
	.exec_op = au1550nd_exec_op,
	.attach_chip = au1550nd_attach_chip,
पूर्ण;

अटल पूर्णांक au1550nd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1550nd_platdata *pd;
	काष्ठा au1550nd_ctx *ctx;
	काष्ठा nand_chip *this;
	काष्ठा mtd_info *mtd;
	काष्ठा resource *r;
	पूर्णांक ret, cs;

	pd = dev_get_platdata(&pdev->dev);
	अगर (!pd) अणु
		dev_err(&pdev->dev, "missing platform data\n");
		वापस -ENODEV;
	पूर्ण

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "no NAND memory resource\n");
		ret = -ENODEV;
		जाओ out1;
	पूर्ण
	अगर (request_mem_region(r->start, resource_size(r), "au1550-nand")) अणु
		dev_err(&pdev->dev, "cannot claim NAND memory area\n");
		ret = -ENOMEM;
		जाओ out1;
	पूर्ण

	ctx->base = ioremap(r->start, 0x1000);
	अगर (!ctx->base) अणु
		dev_err(&pdev->dev, "cannot remap NAND memory area\n");
		ret = -ENODEV;
		जाओ out2;
	पूर्ण

	this = &ctx->chip;
	mtd = nand_to_mtd(this);
	mtd->dev.parent = &pdev->dev;

	/* figure out which CS# r->start beदीर्घs to */
	cs = find_nand_cs(r->start);
	अगर (cs < 0) अणु
		dev_err(&pdev->dev, "cannot detect NAND chipselect\n");
		ret = -ENODEV;
		जाओ out3;
	पूर्ण
	ctx->cs = cs;

	nand_controller_init(&ctx->controller);
	ctx->controller.ops = &au1550nd_ops;
	this->controller = &ctx->controller;

	अगर (pd->devwidth)
		this->options |= न_अंकD_BUSWIDTH_16;

	ret = nand_scan(this, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "NAND scan failed with %d\n", ret);
		जाओ out3;
	पूर्ण

	mtd_device_रेजिस्टर(mtd, pd->parts, pd->num_parts);

	platक्रमm_set_drvdata(pdev, ctx);

	वापस 0;

out3:
	iounmap(ctx->base);
out2:
	release_mem_region(r->start, resource_size(r));
out1:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक au1550nd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1550nd_ctx *ctx = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	काष्ठा nand_chip *chip = &ctx->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);
	iounmap(ctx->base);
	release_mem_region(r->start, 0x1000);
	kमुक्त(ctx);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver au1550nd_driver = अणु
	.driver = अणु
		.name	= "au1550-nand",
	पूर्ण,
	.probe		= au1550nd_probe,
	.हटाओ		= au1550nd_हटाओ,
पूर्ण;

module_platक्रमm_driver(au1550nd_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Embedded Edge, LLC");
MODULE_DESCRIPTION("Board-specific glue layer for NAND flash on Pb1550 board");
