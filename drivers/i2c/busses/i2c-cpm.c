<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale CPM1/CPM2 I2C पूर्णांकerface.
 * Copyright (c) 1999 Dan Malek (dmalek@jlc.net).
 *
 * moved पूर्णांकo proper i2c पूर्णांकerface;
 * Brad Parker (brad@heeltoe.com)
 *
 * Parts from dbox2_i2c.c (cvs.tuxbox.org)
 * (C) 2000-2001 Felix Domke (पंचांगbinc@gmx.net), Gillem (htoa@gmx.net)
 *
 * (C) 2007 Montavista Software, Inc.
 * Vitaly Bordug <vitb@kernel.crashing.org>
 *
 * Converted to of_platक्रमm_device. Renamed to i2c-cpm.c.
 * (C) 2007,2008 Jochen Friedrich <jochen@scram.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <यंत्र/cpm.h>

/* Try to define this अगर you have an older CPU (earlier than rev D4) */
/* However, better use a GPIO based bitbang driver in this हाल :/   */
#अघोषित	I2C_CHIP_ERRATA

#घोषणा CPM_MAX_READ    513
#घोषणा CPM_MAXBD       4

#घोषणा I2C_EB			(0x10) /* Big endian mode */
#घोषणा I2C_EB_CPM2		(0x30) /* Big endian mode, memory snoop */

#घोषणा DPRAM_BASE		((u8 __iomem __क्रमce *)cpm_muram_addr(0))

/* I2C parameter RAM. */
काष्ठा i2c_ram अणु
	uलघु  rbase;		/* Rx Buffer descriptor base address */
	uलघु  tbase;		/* Tx Buffer descriptor base address */
	u_अक्षर  rfcr;		/* Rx function code */
	u_अक्षर  tfcr;		/* Tx function code */
	uलघु  mrblr;		/* Max receive buffer length */
	uपूर्णांक    rstate;		/* Internal */
	uपूर्णांक    rdp;		/* Internal */
	uलघु  rbptr;		/* Rx Buffer descriptor poपूर्णांकer */
	uलघु  rbc;		/* Internal */
	uपूर्णांक    rxपंचांगp;		/* Internal */
	uपूर्णांक    tstate;		/* Internal */
	uपूर्णांक    tdp;		/* Internal */
	uलघु  tbptr;		/* Tx Buffer descriptor poपूर्णांकer */
	uलघु  tbc;		/* Internal */
	uपूर्णांक    txपंचांगp;		/* Internal */
	अक्षर    res1[4];	/* Reserved */
	uलघु  rpbase;		/* Relocation poपूर्णांकer */
	अक्षर    res2[2];	/* Reserved */
	/* The following elements are only क्रम CPM2 */
	अक्षर    res3[4];	/* Reserved */
	uपूर्णांक    sdmaपंचांगp;	/* Internal */
पूर्ण;

#घोषणा I2COM_START	0x80
#घोषणा I2COM_MASTER	0x01
#घोषणा I2CER_TXE	0x10
#घोषणा I2CER_BUSY	0x04
#घोषणा I2CER_TXB	0x02
#घोषणा I2CER_RXB	0x01
#घोषणा I2MOD_EN	0x01

/* I2C Registers */
काष्ठा i2c_reg अणु
	u8	i2mod;
	u8	res1[3];
	u8	i2add;
	u8	res2[3];
	u8	i2brg;
	u8	res3[3];
	u8	i2com;
	u8	res4[3];
	u8	i2cer;
	u8	res5[3];
	u8	i2cmr;
पूर्ण;

काष्ठा cpm_i2c अणु
	अक्षर *base;
	काष्ठा platक्रमm_device *ofdev;
	काष्ठा i2c_adapter adap;
	uपूर्णांक dp_addr;
	पूर्णांक version; /* CPM1=1, CPM2=2 */
	पूर्णांक irq;
	पूर्णांक cp_command;
	पूर्णांक freq;
	काष्ठा i2c_reg __iomem *i2c_reg;
	काष्ठा i2c_ram __iomem *i2c_ram;
	u16 i2c_addr;
	रुको_queue_head_t i2c_रुको;
	cbd_t __iomem *tbase;
	cbd_t __iomem *rbase;
	u_अक्षर *txbuf[CPM_MAXBD];
	u_अक्षर *rxbuf[CPM_MAXBD];
	dma_addr_t txdma[CPM_MAXBD];
	dma_addr_t rxdma[CPM_MAXBD];
पूर्ण;

अटल irqवापस_t cpm_i2c_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cpm_i2c *cpm;
	काष्ठा i2c_reg __iomem *i2c_reg;
	काष्ठा i2c_adapter *adap = dev_id;
	पूर्णांक i;

	cpm = i2c_get_adapdata(dev_id);
	i2c_reg = cpm->i2c_reg;

	/* Clear पूर्णांकerrupt. */
	i = in_8(&i2c_reg->i2cer);
	out_8(&i2c_reg->i2cer, i);

	dev_dbg(&adap->dev, "Interrupt: %x\n", i);

	wake_up(&cpm->i2c_रुको);

	वापस i ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम cpm_reset_i2c_params(काष्ठा cpm_i2c *cpm)
अणु
	काष्ठा i2c_ram __iomem *i2c_ram = cpm->i2c_ram;

	/* Set up the I2C parameters in the parameter ram. */
	out_be16(&i2c_ram->tbase, (u8 __iomem *)cpm->tbase - DPRAM_BASE);
	out_be16(&i2c_ram->rbase, (u8 __iomem *)cpm->rbase - DPRAM_BASE);

	अगर (cpm->version == 1) अणु
		out_8(&i2c_ram->tfcr, I2C_EB);
		out_8(&i2c_ram->rfcr, I2C_EB);
	पूर्ण अन्यथा अणु
		out_8(&i2c_ram->tfcr, I2C_EB_CPM2);
		out_8(&i2c_ram->rfcr, I2C_EB_CPM2);
	पूर्ण

	out_be16(&i2c_ram->mrblr, CPM_MAX_READ);

	out_be32(&i2c_ram->rstate, 0);
	out_be32(&i2c_ram->rdp, 0);
	out_be16(&i2c_ram->rbptr, 0);
	out_be16(&i2c_ram->rbc, 0);
	out_be32(&i2c_ram->rxपंचांगp, 0);
	out_be32(&i2c_ram->tstate, 0);
	out_be32(&i2c_ram->tdp, 0);
	out_be16(&i2c_ram->tbptr, 0);
	out_be16(&i2c_ram->tbc, 0);
	out_be32(&i2c_ram->txपंचांगp, 0);
पूर्ण

अटल व्योम cpm_i2c_क्रमce_बंद(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा cpm_i2c *cpm = i2c_get_adapdata(adap);
	काष्ठा i2c_reg __iomem *i2c_reg = cpm->i2c_reg;

	dev_dbg(&adap->dev, "cpm_i2c_force_close()\n");

	cpm_command(cpm->cp_command, CPM_CR_CLOSE_RX_BD);

	out_8(&i2c_reg->i2cmr, 0x00);	/* Disable all पूर्णांकerrupts */
	out_8(&i2c_reg->i2cer, 0xff);
पूर्ण

अटल व्योम cpm_i2c_parse_message(काष्ठा i2c_adapter *adap,
	काष्ठा i2c_msg *pmsg, पूर्णांक num, पूर्णांक tx, पूर्णांक rx)
अणु
	cbd_t __iomem *tbdf;
	cbd_t __iomem *rbdf;
	u_अक्षर addr;
	u_अक्षर *tb;
	u_अक्षर *rb;
	काष्ठा cpm_i2c *cpm = i2c_get_adapdata(adap);

	tbdf = cpm->tbase + tx;
	rbdf = cpm->rbase + rx;

	addr = i2c_8bit_addr_from_msg(pmsg);

	tb = cpm->txbuf[tx];
	rb = cpm->rxbuf[rx];

	/* Align पढ़ो buffer */
	rb = (u_अक्षर *) (((uदीर्घ) rb + 1) & ~1);

	tb[0] = addr;		/* Device address byte w/rw flag */

	out_be16(&tbdf->cbd_datlen, pmsg->len + 1);
	out_be16(&tbdf->cbd_sc, 0);

	अगर (!(pmsg->flags & I2C_M_NOSTART))
		setbits16(&tbdf->cbd_sc, BD_I2C_START);

	अगर (tx + 1 == num)
		setbits16(&tbdf->cbd_sc, BD_SC_LAST | BD_SC_WRAP);

	अगर (pmsg->flags & I2C_M_RD) अणु
		/*
		 * To पढ़ो, we need an empty buffer of the proper length.
		 * All that is used is the first byte क्रम address, the reमुख्यder
		 * is just used क्रम timing (and करोesn't really have to exist).
		 */

		dev_dbg(&adap->dev, "cpm_i2c_read(abyte=0x%x)\n", addr);

		out_be16(&rbdf->cbd_datlen, 0);
		out_be16(&rbdf->cbd_sc, BD_SC_EMPTY | BD_SC_INTRPT);

		अगर (rx + 1 == CPM_MAXBD)
			setbits16(&rbdf->cbd_sc, BD_SC_WRAP);

		eieio();
		setbits16(&tbdf->cbd_sc, BD_SC_READY);
	पूर्ण अन्यथा अणु
		dev_dbg(&adap->dev, "cpm_i2c_write(abyte=0x%x)\n", addr);

		स_नकल(tb+1, pmsg->buf, pmsg->len);

		eieio();
		setbits16(&tbdf->cbd_sc, BD_SC_READY | BD_SC_INTRPT);
	पूर्ण
पूर्ण

अटल पूर्णांक cpm_i2c_check_message(काष्ठा i2c_adapter *adap,
	काष्ठा i2c_msg *pmsg, पूर्णांक tx, पूर्णांक rx)
अणु
	cbd_t __iomem *tbdf;
	cbd_t __iomem *rbdf;
	u_अक्षर *tb;
	u_अक्षर *rb;
	काष्ठा cpm_i2c *cpm = i2c_get_adapdata(adap);

	tbdf = cpm->tbase + tx;
	rbdf = cpm->rbase + rx;

	tb = cpm->txbuf[tx];
	rb = cpm->rxbuf[rx];

	/* Align पढ़ो buffer */
	rb = (u_अक्षर *) (((uपूर्णांक) rb + 1) & ~1);

	eieio();
	अगर (pmsg->flags & I2C_M_RD) अणु
		dev_dbg(&adap->dev, "tx sc 0x%04x, rx sc 0x%04x\n",
			in_be16(&tbdf->cbd_sc), in_be16(&rbdf->cbd_sc));

		अगर (in_be16(&tbdf->cbd_sc) & BD_SC_NAK) अणु
			dev_dbg(&adap->dev, "I2C read; No ack\n");
			वापस -ENXIO;
		पूर्ण
		अगर (in_be16(&rbdf->cbd_sc) & BD_SC_EMPTY) अणु
			dev_err(&adap->dev,
				"I2C read; complete but rbuf empty\n");
			वापस -EREMOTEIO;
		पूर्ण
		अगर (in_be16(&rbdf->cbd_sc) & BD_SC_OV) अणु
			dev_err(&adap->dev, "I2C read; Overrun\n");
			वापस -EREMOTEIO;
		पूर्ण
		स_नकल(pmsg->buf, rb, pmsg->len);
	पूर्ण अन्यथा अणु
		dev_dbg(&adap->dev, "tx sc %d 0x%04x\n", tx,
			in_be16(&tbdf->cbd_sc));

		अगर (in_be16(&tbdf->cbd_sc) & BD_SC_NAK) अणु
			dev_dbg(&adap->dev, "I2C write; No ack\n");
			वापस -ENXIO;
		पूर्ण
		अगर (in_be16(&tbdf->cbd_sc) & BD_SC_UN) अणु
			dev_err(&adap->dev, "I2C write; Underrun\n");
			वापस -EIO;
		पूर्ण
		अगर (in_be16(&tbdf->cbd_sc) & BD_SC_CL) अणु
			dev_err(&adap->dev, "I2C write; Collision\n");
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cpm_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा cpm_i2c *cpm = i2c_get_adapdata(adap);
	काष्ठा i2c_reg __iomem *i2c_reg = cpm->i2c_reg;
	काष्ठा i2c_ram __iomem *i2c_ram = cpm->i2c_ram;
	काष्ठा i2c_msg *pmsg;
	पूर्णांक ret;
	पूर्णांक tptr;
	पूर्णांक rptr;
	cbd_t __iomem *tbdf;
	cbd_t __iomem *rbdf;

	/* Reset to use first buffer */
	out_be16(&i2c_ram->rbptr, in_be16(&i2c_ram->rbase));
	out_be16(&i2c_ram->tbptr, in_be16(&i2c_ram->tbase));

	tbdf = cpm->tbase;
	rbdf = cpm->rbase;

	tptr = 0;
	rptr = 0;

	/*
	 * If there was a collision in the last i2c transaction,
	 * Set I2COM_MASTER as it was cleared during collision.
	 */
	अगर (in_be16(&tbdf->cbd_sc) & BD_SC_CL) अणु
		out_8(&cpm->i2c_reg->i2com, I2COM_MASTER);
	पूर्ण

	जबतक (tptr < num) अणु
		pmsg = &msgs[tptr];
		dev_dbg(&adap->dev, "R: %d T: %d\n", rptr, tptr);

		cpm_i2c_parse_message(adap, pmsg, num, tptr, rptr);
		अगर (pmsg->flags & I2C_M_RD)
			rptr++;
		tptr++;
	पूर्ण
	/* Start transfer now */
	/* Enable RX/TX/Error पूर्णांकerupts */
	out_8(&i2c_reg->i2cmr, I2CER_TXE | I2CER_TXB | I2CER_RXB);
	out_8(&i2c_reg->i2cer, 0xff);	/* Clear पूर्णांकerrupt status */
	/* Chip bug, set enable here */
	setbits8(&i2c_reg->i2mod, I2MOD_EN);	/* Enable */
	/* Begin transmission */
	setbits8(&i2c_reg->i2com, I2COM_START);

	tptr = 0;
	rptr = 0;

	जबतक (tptr < num) अणु
		/* Check क्रम outstanding messages */
		dev_dbg(&adap->dev, "test ready.\n");
		pmsg = &msgs[tptr];
		अगर (pmsg->flags & I2C_M_RD)
			ret = रुको_event_समयout(cpm->i2c_रुको,
				(in_be16(&tbdf[tptr].cbd_sc) & BD_SC_NAK) ||
				!(in_be16(&rbdf[rptr].cbd_sc) & BD_SC_EMPTY),
				1 * HZ);
		अन्यथा
			ret = रुको_event_समयout(cpm->i2c_रुको,
				!(in_be16(&tbdf[tptr].cbd_sc) & BD_SC_READY),
				1 * HZ);
		अगर (ret == 0) अणु
			ret = -EREMOTEIO;
			dev_err(&adap->dev, "I2C transfer: timeout\n");
			जाओ out_err;
		पूर्ण
		अगर (ret > 0) अणु
			dev_dbg(&adap->dev, "ready.\n");
			ret = cpm_i2c_check_message(adap, pmsg, tptr, rptr);
			tptr++;
			अगर (pmsg->flags & I2C_M_RD)
				rptr++;
			अगर (ret)
				जाओ out_err;
		पूर्ण
	पूर्ण
#अगर_घोषित I2C_CHIP_ERRATA
	/*
	 * Chip errata, clear enable. This is not needed on rev D4 CPUs.
	 * Disabling I2C too early may cause too लघु stop condition
	 */
	udelay(4);
	clrbits8(&i2c_reg->i2mod, I2MOD_EN);
#पूर्ण_अगर
	वापस (num);

out_err:
	cpm_i2c_क्रमce_बंद(adap);
#अगर_घोषित I2C_CHIP_ERRATA
	/*
	 * Chip errata, clear enable. This is not needed on rev D4 CPUs.
	 */
	clrbits8(&i2c_reg->i2mod, I2MOD_EN);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल u32 cpm_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK);
पूर्ण

/* -----exported algorithm data: -------------------------------------	*/

अटल स्थिर काष्ठा i2c_algorithm cpm_i2c_algo = अणु
	.master_xfer = cpm_i2c_xfer,
	.functionality = cpm_i2c_func,
पूर्ण;

/* CPM_MAX_READ is also limiting ग_लिखोs according to the code! */
अटल स्थिर काष्ठा i2c_adapter_quirks cpm_i2c_quirks = अणु
	.max_num_msgs = CPM_MAXBD,
	.max_पढ़ो_len = CPM_MAX_READ,
	.max_ग_लिखो_len = CPM_MAX_READ,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter cpm_ops = अणु
	.owner		= THIS_MODULE,
	.name		= "i2c-cpm",
	.algo		= &cpm_i2c_algo,
	.quirks		= &cpm_i2c_quirks,
पूर्ण;

अटल पूर्णांक cpm_i2c_setup(काष्ठा cpm_i2c *cpm)
अणु
	काष्ठा platक्रमm_device *ofdev = cpm->ofdev;
	स्थिर u32 *data;
	पूर्णांक len, ret, i;
	व्योम __iomem *i2c_base;
	cbd_t __iomem *tbdf;
	cbd_t __iomem *rbdf;
	अचिन्हित अक्षर brg;

	dev_dbg(&cpm->ofdev->dev, "cpm_i2c_setup()\n");

	init_रुकोqueue_head(&cpm->i2c_रुको);

	cpm->irq = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	अगर (!cpm->irq)
		वापस -EINVAL;

	/* Install पूर्णांकerrupt handler. */
	ret = request_irq(cpm->irq, cpm_i2c_पूर्णांकerrupt, 0, "cpm_i2c",
			  &cpm->adap);
	अगर (ret)
		वापस ret;

	/* I2C parameter RAM */
	i2c_base = of_iomap(ofdev->dev.of_node, 1);
	अगर (i2c_base == शून्य) अणु
		ret = -EINVAL;
		जाओ out_irq;
	पूर्ण

	अगर (of_device_is_compatible(ofdev->dev.of_node, "fsl,cpm1-i2c")) अणु

		/* Check क्रम and use a microcode relocation patch. */
		cpm->i2c_ram = i2c_base;
		cpm->i2c_addr = in_be16(&cpm->i2c_ram->rpbase);

		/*
		 * Maybe should use cpm_muram_alloc instead of hardcoding
		 * this in micropatch.c
		 */
		अगर (cpm->i2c_addr) अणु
			cpm->i2c_ram = cpm_muram_addr(cpm->i2c_addr);
			iounmap(i2c_base);
		पूर्ण

		cpm->version = 1;

	पूर्ण अन्यथा अगर (of_device_is_compatible(ofdev->dev.of_node, "fsl,cpm2-i2c")) अणु
		cpm->i2c_addr = cpm_muram_alloc(माप(काष्ठा i2c_ram), 64);
		cpm->i2c_ram = cpm_muram_addr(cpm->i2c_addr);
		out_be16(i2c_base, cpm->i2c_addr);
		iounmap(i2c_base);

		cpm->version = 2;

	पूर्ण अन्यथा अणु
		iounmap(i2c_base);
		ret = -EINVAL;
		जाओ out_irq;
	पूर्ण

	/* I2C control/status रेजिस्टरs */
	cpm->i2c_reg = of_iomap(ofdev->dev.of_node, 0);
	अगर (cpm->i2c_reg == शून्य) अणु
		ret = -EINVAL;
		जाओ out_ram;
	पूर्ण

	data = of_get_property(ofdev->dev.of_node, "fsl,cpm-command", &len);
	अगर (!data || len != 4) अणु
		ret = -EINVAL;
		जाओ out_reg;
	पूर्ण
	cpm->cp_command = *data;

	data = of_get_property(ofdev->dev.of_node, "linux,i2c-class", &len);
	अगर (data && len == 4)
		cpm->adap.class = *data;

	data = of_get_property(ofdev->dev.of_node, "clock-frequency", &len);
	अगर (data && len == 4)
		cpm->freq = *data;
	अन्यथा
		cpm->freq = 60000; /* use 60kHz i2c घड़ी by शेष */

	/*
	 * Allocate space क्रम CPM_MAXBD transmit and receive buffer
	 * descriptors in the DP ram.
	 */
	cpm->dp_addr = cpm_muram_alloc(माप(cbd_t) * 2 * CPM_MAXBD, 8);
	अगर (!cpm->dp_addr) अणु
		ret = -ENOMEM;
		जाओ out_reg;
	पूर्ण

	cpm->tbase = cpm_muram_addr(cpm->dp_addr);
	cpm->rbase = cpm_muram_addr(cpm->dp_addr + माप(cbd_t) * CPM_MAXBD);

	/* Allocate TX and RX buffers */

	tbdf = cpm->tbase;
	rbdf = cpm->rbase;

	क्रम (i = 0; i < CPM_MAXBD; i++) अणु
		cpm->rxbuf[i] = dma_alloc_coherent(&cpm->ofdev->dev,
						   CPM_MAX_READ + 1,
						   &cpm->rxdma[i], GFP_KERNEL);
		अगर (!cpm->rxbuf[i]) अणु
			ret = -ENOMEM;
			जाओ out_muram;
		पूर्ण
		out_be32(&rbdf[i].cbd_bufaddr, ((cpm->rxdma[i] + 1) & ~1));

		cpm->txbuf[i] = dma_alloc_coherent(&cpm->ofdev->dev,
						   CPM_MAX_READ + 1,
						   &cpm->txdma[i], GFP_KERNEL);
		अगर (!cpm->txbuf[i]) अणु
			ret = -ENOMEM;
			जाओ out_muram;
		पूर्ण
		out_be32(&tbdf[i].cbd_bufaddr, cpm->txdma[i]);
	पूर्ण

	/* Initialize Tx/Rx parameters. */

	cpm_reset_i2c_params(cpm);

	dev_dbg(&cpm->ofdev->dev, "i2c_ram 0x%p, i2c_addr 0x%04x, freq %d\n",
		cpm->i2c_ram, cpm->i2c_addr, cpm->freq);
	dev_dbg(&cpm->ofdev->dev, "tbase 0x%04x, rbase 0x%04x\n",
		(u8 __iomem *)cpm->tbase - DPRAM_BASE,
		(u8 __iomem *)cpm->rbase - DPRAM_BASE);

	cpm_command(cpm->cp_command, CPM_CR_INIT_TRX);

	/*
	 * Select an invalid address. Just make sure we करोn't use loopback mode
	 */
	out_8(&cpm->i2c_reg->i2add, 0x7f << 1);

	/*
	 * PDIV is set to 00 in i2mod, so brgclk/32 is used as input to the
	 * i2c baud rate generator. This is भागided by 2 x (DIV + 3) to get
	 * the actual i2c bus frequency.
	 */
	brg = get_brgfreq() / (32 * 2 * cpm->freq) - 3;
	out_8(&cpm->i2c_reg->i2brg, brg);

	out_8(&cpm->i2c_reg->i2mod, 0x00);
	out_8(&cpm->i2c_reg->i2com, I2COM_MASTER);	/* Master mode */

	/* Disable पूर्णांकerrupts. */
	out_8(&cpm->i2c_reg->i2cmr, 0);
	out_8(&cpm->i2c_reg->i2cer, 0xff);

	वापस 0;

out_muram:
	क्रम (i = 0; i < CPM_MAXBD; i++) अणु
		अगर (cpm->rxbuf[i])
			dma_मुक्त_coherent(&cpm->ofdev->dev, CPM_MAX_READ + 1,
				cpm->rxbuf[i], cpm->rxdma[i]);
		अगर (cpm->txbuf[i])
			dma_मुक्त_coherent(&cpm->ofdev->dev, CPM_MAX_READ + 1,
				cpm->txbuf[i], cpm->txdma[i]);
	पूर्ण
	cpm_muram_मुक्त(cpm->dp_addr);
out_reg:
	iounmap(cpm->i2c_reg);
out_ram:
	अगर ((cpm->version == 1) && (!cpm->i2c_addr))
		iounmap(cpm->i2c_ram);
	अगर (cpm->version == 2)
		cpm_muram_मुक्त(cpm->i2c_addr);
out_irq:
	मुक्त_irq(cpm->irq, &cpm->adap);
	वापस ret;
पूर्ण

अटल व्योम cpm_i2c_shutकरोwn(काष्ठा cpm_i2c *cpm)
अणु
	पूर्णांक i;

	/* Shut करोwn I2C. */
	clrbits8(&cpm->i2c_reg->i2mod, I2MOD_EN);

	/* Disable पूर्णांकerrupts */
	out_8(&cpm->i2c_reg->i2cmr, 0);
	out_8(&cpm->i2c_reg->i2cer, 0xff);

	मुक्त_irq(cpm->irq, &cpm->adap);

	/* Free all memory */
	क्रम (i = 0; i < CPM_MAXBD; i++) अणु
		dma_मुक्त_coherent(&cpm->ofdev->dev, CPM_MAX_READ + 1,
			cpm->rxbuf[i], cpm->rxdma[i]);
		dma_मुक्त_coherent(&cpm->ofdev->dev, CPM_MAX_READ + 1,
			cpm->txbuf[i], cpm->txdma[i]);
	पूर्ण

	cpm_muram_मुक्त(cpm->dp_addr);
	iounmap(cpm->i2c_reg);

	अगर ((cpm->version == 1) && (!cpm->i2c_addr))
		iounmap(cpm->i2c_ram);
	अगर (cpm->version == 2)
		cpm_muram_मुक्त(cpm->i2c_addr);
पूर्ण

अटल पूर्णांक cpm_i2c_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	पूर्णांक result, len;
	काष्ठा cpm_i2c *cpm;
	स्थिर u32 *data;

	cpm = kzalloc(माप(काष्ठा cpm_i2c), GFP_KERNEL);
	अगर (!cpm)
		वापस -ENOMEM;

	cpm->ofdev = ofdev;

	platक्रमm_set_drvdata(ofdev, cpm);

	cpm->adap = cpm_ops;
	i2c_set_adapdata(&cpm->adap, cpm);
	cpm->adap.dev.parent = &ofdev->dev;
	cpm->adap.dev.of_node = of_node_get(ofdev->dev.of_node);

	result = cpm_i2c_setup(cpm);
	अगर (result) अणु
		dev_err(&ofdev->dev, "Unable to init hardware\n");
		जाओ out_मुक्त;
	पूर्ण

	/* रेजिस्टर new adapter to i2c module... */

	data = of_get_property(ofdev->dev.of_node, "linux,i2c-index", &len);
	cpm->adap.nr = (data && len == 4) ? be32_to_cpup(data) : -1;
	result = i2c_add_numbered_adapter(&cpm->adap);

	अगर (result < 0)
		जाओ out_shut;

	dev_dbg(&ofdev->dev, "hw routines for %s registered.\n",
		cpm->adap.name);

	वापस 0;
out_shut:
	cpm_i2c_shutकरोwn(cpm);
out_मुक्त:
	kमुक्त(cpm);

	वापस result;
पूर्ण

अटल पूर्णांक cpm_i2c_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा cpm_i2c *cpm = platक्रमm_get_drvdata(ofdev);

	i2c_del_adapter(&cpm->adap);

	cpm_i2c_shutकरोwn(cpm);

	kमुक्त(cpm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cpm_i2c_match[] = अणु
	अणु
		.compatible = "fsl,cpm1-i2c",
	पूर्ण,
	अणु
		.compatible = "fsl,cpm2-i2c",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, cpm_i2c_match);

अटल काष्ठा platक्रमm_driver cpm_i2c_driver = अणु
	.probe		= cpm_i2c_probe,
	.हटाओ		= cpm_i2c_हटाओ,
	.driver = अणु
		.name = "fsl-i2c-cpm",
		.of_match_table = cpm_i2c_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cpm_i2c_driver);

MODULE_AUTHOR("Jochen Friedrich <jochen@scram.de>");
MODULE_DESCRIPTION("I2C-Bus adapter routines for CPM boards");
MODULE_LICENSE("GPL");
