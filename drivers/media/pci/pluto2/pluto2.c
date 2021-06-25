<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pluto2.c - Satelco Easywatch Mobile Terrestrial Receiver [DVB-T]
 *
 * Copyright (C) 2005 Andreas Oberritter <obi@linuxtv.org>
 *
 * based on pluto2.c 1.10 - http://instinct-wp8.no-ip.org/pluto/
 *	by Dany Salman <salmandany@yahoo.fr>
 *	Copyright (c) 2004 TDF
 */

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

#समावेश <media/demux.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvbdev.h>
#समावेश "tda1004x.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा DRIVER_NAME		"pluto2"

#घोषणा REG_PIDn(n)		((n) << 2)	/* PID n pattern रेजिस्टरs */
#घोषणा REG_PCAR		0x0020		/* PC address रेजिस्टर */
#घोषणा REG_TSCR		0x0024		/* TS ctrl & status */
#घोषणा REG_MISC		0x0028		/* miscellaneous */
#घोषणा REG_MMAC		0x002c		/* MSB MAC address */
#घोषणा REG_IMAC		0x0030		/* ISB MAC address */
#घोषणा REG_LMAC		0x0034		/* LSB MAC address */
#घोषणा REG_SPID		0x0038		/* SPI data */
#घोषणा REG_SLCS		0x003c		/* serial links ctrl/status */

#घोषणा PID0_NOFIL		(0x0001 << 16)
#घोषणा PIDn_ENP		(0x0001 << 15)
#घोषणा PID0_END		(0x0001 << 14)
#घोषणा PID0_AFIL		(0x0001 << 13)
#घोषणा PIDn_PID		(0x1fff <<  0)

#घोषणा TSCR_NBPACKETS		(0x00ff << 24)
#घोषणा TSCR_DEM		(0x0001 << 17)
#घोषणा TSCR_DE			(0x0001 << 16)
#घोषणा TSCR_RSTN		(0x0001 << 15)
#घोषणा TSCR_MSKO		(0x0001 << 14)
#घोषणा TSCR_MSKA		(0x0001 << 13)
#घोषणा TSCR_MSKL		(0x0001 << 12)
#घोषणा TSCR_OVR		(0x0001 << 11)
#घोषणा TSCR_AFUL		(0x0001 << 10)
#घोषणा TSCR_LOCK		(0x0001 <<  9)
#घोषणा TSCR_IACK		(0x0001 <<  8)
#घोषणा TSCR_ADEF		(0x007f <<  0)

#घोषणा MISC_DVR		(0x0fff <<  4)
#घोषणा MISC_ALED		(0x0001 <<  3)
#घोषणा MISC_FRST		(0x0001 <<  2)
#घोषणा MISC_LED1		(0x0001 <<  1)
#घोषणा MISC_LED0		(0x0001 <<  0)

#घोषणा SPID_SPIDR		(0x00ff <<  0)

#घोषणा SLCS_SCL		(0x0001 <<  7)
#घोषणा SLCS_SDA		(0x0001 <<  6)
#घोषणा SLCS_CSN		(0x0001 <<  2)
#घोषणा SLCS_OVR		(0x0001 <<  1)
#घोषणा SLCS_SWC		(0x0001 <<  0)

#घोषणा TS_DMA_PACKETS		(8)
#घोषणा TS_DMA_BYTES		(188 * TS_DMA_PACKETS)

#घोषणा I2C_ADDR_TDA10046	0x10
#घोषणा I2C_ADDR_TUA6034	0xc2
#घोषणा NHWFILTERS		8

काष्ठा pluto अणु
	/* pci */
	काष्ठा pci_dev *pdev;
	u8 __iomem *io_mem;

	/* dvb */
	काष्ठा dmx_frontend hw_frontend;
	काष्ठा dmx_frontend mem_frontend;
	काष्ठा dmxdev dmxdev;
	काष्ठा dvb_adapter dvb_adapter;
	काष्ठा dvb_demux demux;
	काष्ठा dvb_frontend *fe;
	काष्ठा dvb_net dvbnet;
	अचिन्हित पूर्णांक full_ts_users;
	अचिन्हित पूर्णांक users;

	/* i2c */
	काष्ठा i2c_algo_bit_data i2c_bit;
	काष्ठा i2c_adapter i2c_adap;
	अचिन्हित पूर्णांक i2cbug;

	/* irq */
	अचिन्हित पूर्णांक overflow;
	अचिन्हित पूर्णांक dead;

	/* dma */
	dma_addr_t dma_addr;
	u8 dma_buf[TS_DMA_BYTES];
	u8 dummy[4096];
पूर्ण;

अटल अंतरभूत काष्ठा pluto *feed_to_pluto(काष्ठा dvb_demux_feed *feed)
अणु
	वापस container_of(feed->demux, काष्ठा pluto, demux);
पूर्ण

अटल अंतरभूत काष्ठा pluto *frontend_to_pluto(काष्ठा dvb_frontend *fe)
अणु
	वापस container_of(fe->dvb, काष्ठा pluto, dvb_adapter);
पूर्ण

अटल अंतरभूत u32 pluto_पढ़ोreg(काष्ठा pluto *pluto, u32 reg)
अणु
	वापस पढ़ोl(&pluto->io_mem[reg]);
पूर्ण

अटल अंतरभूत व्योम pluto_ग_लिखोreg(काष्ठा pluto *pluto, u32 reg, u32 val)
अणु
	ग_लिखोl(val, &pluto->io_mem[reg]);
पूर्ण

अटल अंतरभूत व्योम pluto_rw(काष्ठा pluto *pluto, u32 reg, u32 mask, u32 bits)
अणु
	u32 val = पढ़ोl(&pluto->io_mem[reg]);
	val &= ~mask;
	val |= bits;
	ग_लिखोl(val, &pluto->io_mem[reg]);
पूर्ण

अटल व्योम pluto_ग_लिखो_tscr(काष्ठा pluto *pluto, u32 val)
अणु
	/* set the number of packets */
	val &= ~TSCR_ADEF;
	val |= TS_DMA_PACKETS / 2;

	pluto_ग_लिखोreg(pluto, REG_TSCR, val);
पूर्ण

अटल व्योम pluto_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा pluto *pluto = data;

	अगर (state)
		pluto_rw(pluto, REG_SLCS, SLCS_SDA, SLCS_SDA);
	अन्यथा
		pluto_rw(pluto, REG_SLCS, SLCS_SDA, 0);
पूर्ण

अटल व्योम pluto_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा pluto *pluto = data;

	अगर (state)
		pluto_rw(pluto, REG_SLCS, SLCS_SCL, SLCS_SCL);
	अन्यथा
		pluto_rw(pluto, REG_SLCS, SLCS_SCL, 0);

	/* try to detect i2c_inb() to workaround hardware bug:
	 * reset SDA to high after SCL has been set to low */
	अगर ((state) && (pluto->i2cbug == 0)) अणु
		pluto->i2cbug = 1;
	पूर्ण अन्यथा अणु
		अगर ((!state) && (pluto->i2cbug == 1))
			pluto_setsda(pluto, 1);
		pluto->i2cbug = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक pluto_माला_लोda(व्योम *data)
अणु
	काष्ठा pluto *pluto = data;

	वापस pluto_पढ़ोreg(pluto, REG_SLCS) & SLCS_SDA;
पूर्ण

अटल पूर्णांक pluto_माला_लोcl(व्योम *data)
अणु
	काष्ठा pluto *pluto = data;

	वापस pluto_पढ़ोreg(pluto, REG_SLCS) & SLCS_SCL;
पूर्ण

अटल व्योम pluto_reset_frontend(काष्ठा pluto *pluto, पूर्णांक reenable)
अणु
	u32 val = pluto_पढ़ोreg(pluto, REG_MISC);

	अगर (val & MISC_FRST) अणु
		val &= ~MISC_FRST;
		pluto_ग_लिखोreg(pluto, REG_MISC, val);
	पूर्ण
	अगर (reenable) अणु
		val |= MISC_FRST;
		pluto_ग_लिखोreg(pluto, REG_MISC, val);
	पूर्ण
पूर्ण

अटल व्योम pluto_reset_ts(काष्ठा pluto *pluto, पूर्णांक reenable)
अणु
	u32 val = pluto_पढ़ोreg(pluto, REG_TSCR);

	अगर (val & TSCR_RSTN) अणु
		val &= ~TSCR_RSTN;
		pluto_ग_लिखो_tscr(pluto, val);
	पूर्ण
	अगर (reenable) अणु
		val |= TSCR_RSTN;
		pluto_ग_लिखो_tscr(pluto, val);
	पूर्ण
पूर्ण

अटल व्योम pluto_set_dma_addr(काष्ठा pluto *pluto)
अणु
	pluto_ग_लिखोreg(pluto, REG_PCAR, pluto->dma_addr);
पूर्ण

अटल पूर्णांक pluto_dma_map(काष्ठा pluto *pluto)
अणु
	pluto->dma_addr = pci_map_single(pluto->pdev, pluto->dma_buf,
			TS_DMA_BYTES, PCI_DMA_FROMDEVICE);

	वापस pci_dma_mapping_error(pluto->pdev, pluto->dma_addr);
पूर्ण

अटल व्योम pluto_dma_unmap(काष्ठा pluto *pluto)
अणु
	pci_unmap_single(pluto->pdev, pluto->dma_addr,
			TS_DMA_BYTES, PCI_DMA_FROMDEVICE);
पूर्ण

अटल पूर्णांक pluto_start_feed(काष्ठा dvb_demux_feed *f)
अणु
	काष्ठा pluto *pluto = feed_to_pluto(f);

	/* enable PID filtering */
	अगर (pluto->users++ == 0)
		pluto_rw(pluto, REG_PIDn(0), PID0_AFIL | PID0_NOFIL, 0);

	अगर ((f->pid < 0x2000) && (f->index < NHWFILTERS))
		pluto_rw(pluto, REG_PIDn(f->index), PIDn_ENP | PIDn_PID, PIDn_ENP | f->pid);
	अन्यथा अगर (pluto->full_ts_users++ == 0)
		pluto_rw(pluto, REG_PIDn(0), PID0_NOFIL, PID0_NOFIL);

	वापस 0;
पूर्ण

अटल पूर्णांक pluto_stop_feed(काष्ठा dvb_demux_feed *f)
अणु
	काष्ठा pluto *pluto = feed_to_pluto(f);

	/* disable PID filtering */
	अगर (--pluto->users == 0)
		pluto_rw(pluto, REG_PIDn(0), PID0_AFIL, PID0_AFIL);

	अगर ((f->pid < 0x2000) && (f->index < NHWFILTERS))
		pluto_rw(pluto, REG_PIDn(f->index), PIDn_ENP | PIDn_PID, 0x1fff);
	अन्यथा अगर (--pluto->full_ts_users == 0)
		pluto_rw(pluto, REG_PIDn(0), PID0_NOFIL, 0);

	वापस 0;
पूर्ण

अटल व्योम pluto_dma_end(काष्ठा pluto *pluto, अचिन्हित पूर्णांक nbpackets)
अणु
	/* synchronize the DMA transfer with the CPU
	 * first so that we see updated contents. */
	pci_dma_sync_single_क्रम_cpu(pluto->pdev, pluto->dma_addr,
			TS_DMA_BYTES, PCI_DMA_FROMDEVICE);

	/* Workaround क्रम broken hardware:
	 * [1] On startup NBPACKETS seems to contain an uninitialized value,
	 *     but no packets have been transferred.
	 * [2] Someबार (actually very often) NBPACKETS stays at zero
	 *     although one packet has been transferred.
	 * [3] Someबार (actually rarely), the card माला_लो पूर्णांकo an erroneous
	 *     mode where it continuously generates पूर्णांकerrupts, claiming it
	 *     has received nbpackets>TS_DMA_PACKETS packets, but no packet
	 *     has been transferred. Only a reset seems to solve this
	 */
	अगर ((nbpackets == 0) || (nbpackets > TS_DMA_PACKETS)) अणु
		अचिन्हित पूर्णांक i = 0;
		जबतक (pluto->dma_buf[i] == 0x47)
			i += 188;
		nbpackets = i / 188;
		अगर (i == 0) अणु
			pluto_reset_ts(pluto, 1);
			dev_prपूर्णांकk(KERN_DEBUG, &pluto->pdev->dev, "resetting TS because of invalid packet counter\n");
		पूर्ण
	पूर्ण

	dvb_dmx_swfilter_packets(&pluto->demux, pluto->dma_buf, nbpackets);

	/* clear the dma buffer. this is needed to be able to identअगरy
	 * new valid ts packets above */
	स_रखो(pluto->dma_buf, 0, nbpackets * 188);

	/* reset the dma address */
	pluto_set_dma_addr(pluto);

	/* sync the buffer and give it back to the card */
	pci_dma_sync_single_क्रम_device(pluto->pdev, pluto->dma_addr,
			TS_DMA_BYTES, PCI_DMA_FROMDEVICE);
पूर्ण

अटल irqवापस_t pluto_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pluto *pluto = dev_id;
	u32 tscr;

	/* check whether an पूर्णांकerrupt occurred on this device */
	tscr = pluto_पढ़ोreg(pluto, REG_TSCR);
	अगर (!(tscr & (TSCR_DE | TSCR_OVR)))
		वापस IRQ_NONE;

	अगर (tscr == 0xffffffff) अणु
		अगर (pluto->dead == 0)
			dev_err(&pluto->pdev->dev, "card has hung or been ejected.\n");
		/* It's dead Jim */
		pluto->dead = 1;
		वापस IRQ_HANDLED;
	पूर्ण

	/* dma end पूर्णांकerrupt */
	अगर (tscr & TSCR_DE) अणु
		pluto_dma_end(pluto, (tscr & TSCR_NBPACKETS) >> 24);
		/* overflow पूर्णांकerrupt */
		अगर (tscr & TSCR_OVR)
			pluto->overflow++;
		अगर (pluto->overflow) अणु
			dev_err(&pluto->pdev->dev, "overflow irq (%d)\n",
					pluto->overflow);
			pluto_reset_ts(pluto, 1);
			pluto->overflow = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (tscr & TSCR_OVR) अणु
		pluto->overflow++;
	पूर्ण

	/* ACK the पूर्णांकerrupt */
	pluto_ग_लिखो_tscr(pluto, tscr | TSCR_IACK);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pluto_enable_irqs(काष्ठा pluto *pluto)
अणु
	u32 val = pluto_पढ़ोreg(pluto, REG_TSCR);

	/* disable AFUL and LOCK पूर्णांकerrupts */
	val |= (TSCR_MSKA | TSCR_MSKL);
	/* enable DMA and OVERFLOW पूर्णांकerrupts */
	val &= ~(TSCR_DEM | TSCR_MSKO);
	/* clear pending पूर्णांकerrupts */
	val |= TSCR_IACK;

	pluto_ग_लिखो_tscr(pluto, val);
पूर्ण

अटल व्योम pluto_disable_irqs(काष्ठा pluto *pluto)
अणु
	u32 val = pluto_पढ़ोreg(pluto, REG_TSCR);

	/* disable all पूर्णांकerrupts */
	val |= (TSCR_DEM | TSCR_MSKO | TSCR_MSKA | TSCR_MSKL);
	/* clear pending पूर्णांकerrupts */
	val |= TSCR_IACK;

	pluto_ग_लिखो_tscr(pluto, val);
पूर्ण

अटल पूर्णांक pluto_hw_init(काष्ठा pluto *pluto)
अणु
	pluto_reset_frontend(pluto, 1);

	/* set स्वतःmatic LED control by FPGA */
	pluto_rw(pluto, REG_MISC, MISC_ALED, MISC_ALED);

	/* set data endianness */
#अगर_घोषित __LITTLE_ENDIAN
	pluto_rw(pluto, REG_PIDn(0), PID0_END, PID0_END);
#अन्यथा
	pluto_rw(pluto, REG_PIDn(0), PID0_END, 0);
#पूर्ण_अगर
	/* map DMA and set address */
	pluto_dma_map(pluto);
	pluto_set_dma_addr(pluto);

	/* enable पूर्णांकerrupts */
	pluto_enable_irqs(pluto);

	/* reset TS logic */
	pluto_reset_ts(pluto, 1);

	वापस 0;
पूर्ण

अटल व्योम pluto_hw_निकास(काष्ठा pluto *pluto)
अणु
	/* disable पूर्णांकerrupts */
	pluto_disable_irqs(pluto);

	pluto_reset_ts(pluto, 0);

	/* LED: disable स्वतःmatic control, enable yellow, disable green */
	pluto_rw(pluto, REG_MISC, MISC_ALED | MISC_LED1 | MISC_LED0, MISC_LED1);

	/* unmap DMA */
	pluto_dma_unmap(pluto);

	pluto_reset_frontend(pluto, 0);
पूर्ण

अटल अंतरभूत u32 भागide(u32 numerator, u32 denominator)
अणु
	अगर (denominator == 0)
		वापस ~0;

	वापस DIV_ROUND_CLOSEST(numerator, denominator);
पूर्ण

/* LG Innotek TDTE-E001P (Infineon TUA6034) */
अटल पूर्णांक lg_tdtpe001p_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा pluto *pluto = frontend_to_pluto(fe);
	काष्ठा i2c_msg msg;
	पूर्णांक ret;
	u8 buf[4];
	u32 भाग;

	// Fref = 166.667 Hz
	// Fref * 3 = 500.000 Hz
	// IF = 36166667
	// IF / Fref = 217
	//भाग = भागide(p->frequency + 36166667, 166667);
	भाग = भागide(p->frequency * 3, 500000) + 217;
	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = (भाग >> 0) & 0xff;

	अगर (p->frequency < 611000000)
		buf[2] = 0xb4;
	अन्यथा अगर (p->frequency < 811000000)
		buf[2] = 0xbc;
	अन्यथा
		buf[2] = 0xf4;

	// VHF: 174-230 MHz
	// center: 350 MHz
	// UHF: 470-862 MHz
	अगर (p->frequency < 350000000)
		buf[3] = 0x02;
	अन्यथा
		buf[3] = 0x04;

	अगर (p->bandwidth_hz == 8000000)
		buf[3] |= 0x08;

	msg.addr = I2C_ADDR_TUA6034 >> 1;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = माप(buf);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	ret = i2c_transfer(&pluto->i2c_adap, &msg, 1);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret == 0)
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

अटल पूर्णांक pluto2_request_firmware(काष्ठा dvb_frontend *fe,
				   स्थिर काष्ठा firmware **fw, अक्षर *name)
अणु
	काष्ठा pluto *pluto = frontend_to_pluto(fe);

	वापस request_firmware(fw, name, &pluto->pdev->dev);
पूर्ण

अटल काष्ठा tda1004x_config pluto2_fe_config = अणु
	.demod_address = I2C_ADDR_TDA10046 >> 1,
	.invert = 1,
	.invert_oclk = 0,
	.xtal_freq = TDA10046_XTAL_16M,
	.agc_config = TDA10046_AGC_DEFAULT,
	.अगर_freq = TDA10046_FREQ_3617,
	.request_firmware = pluto2_request_firmware,
पूर्ण;

अटल पूर्णांक frontend_init(काष्ठा pluto *pluto)
अणु
	पूर्णांक ret;

	pluto->fe = tda10046_attach(&pluto2_fe_config, &pluto->i2c_adap);
	अगर (!pluto->fe) अणु
		dev_err(&pluto->pdev->dev, "could not attach frontend\n");
		वापस -ENODEV;
	पूर्ण
	pluto->fe->ops.tuner_ops.set_params = lg_tdtpe001p_tuner_set_params;

	ret = dvb_रेजिस्टर_frontend(&pluto->dvb_adapter, pluto->fe);
	अगर (ret < 0) अणु
		अगर (pluto->fe->ops.release)
			pluto->fe->ops.release(pluto->fe);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pluto_पढ़ो_rev(काष्ठा pluto *pluto)
अणु
	u32 val = pluto_पढ़ोreg(pluto, REG_MISC) & MISC_DVR;
	dev_info(&pluto->pdev->dev, "board revision %d.%d\n",
			(val >> 12) & 0x0f, (val >> 4) & 0xff);
पूर्ण

अटल व्योम pluto_पढ़ो_mac(काष्ठा pluto *pluto, u8 *mac)
अणु
	u32 val = pluto_पढ़ोreg(pluto, REG_MMAC);
	mac[0] = (val >> 8) & 0xff;
	mac[1] = (val >> 0) & 0xff;

	val = pluto_पढ़ोreg(pluto, REG_IMAC);
	mac[2] = (val >> 8) & 0xff;
	mac[3] = (val >> 0) & 0xff;

	val = pluto_पढ़ोreg(pluto, REG_LMAC);
	mac[4] = (val >> 8) & 0xff;
	mac[5] = (val >> 0) & 0xff;

	dev_info(&pluto->pdev->dev, "MAC %pM\n", mac);
पूर्ण

अटल पूर्णांक pluto_पढ़ो_serial(काष्ठा pluto *pluto)
अणु
	काष्ठा pci_dev *pdev = pluto->pdev;
	अचिन्हित पूर्णांक i, j;
	u8 __iomem *cis;

	cis = pci_iomap(pdev, 1, 0);
	अगर (!cis)
		वापस -EIO;

	dev_info(&pdev->dev, "S/N ");

	क्रम (i = 0xe0; i < 0x100; i += 4) अणु
		u32 val = पढ़ोl(&cis[i]);
		क्रम (j = 0; j < 32; j += 8) अणु
			अगर ((val & 0xff) == 0xff)
				जाओ out;
			prपूर्णांकk(KERN_CONT "%c", val & 0xff);
			val >>= 8;
		पूर्ण
	पूर्ण
out:
	prपूर्णांकk(KERN_CONT "\n");
	pci_iounmap(pdev, cis);

	वापस 0;
पूर्ण

अटल पूर्णांक pluto2_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा pluto *pluto;
	काष्ठा dvb_adapter *dvb_adapter;
	काष्ठा dvb_demux *dvbdemux;
	काष्ठा dmx_demux *dmx;
	पूर्णांक ret = -ENOMEM;

	pluto = kzalloc(माप(काष्ठा pluto), GFP_KERNEL);
	अगर (!pluto)
		जाओ out;

	pluto->pdev = pdev;

	ret = pci_enable_device(pdev);
	अगर (ret < 0)
		जाओ err_kमुक्त;

	/* enable पूर्णांकerrupts */
	pci_ग_लिखो_config_dword(pdev, 0x6c, 0x8000);

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret < 0)
		जाओ err_pci_disable_device;

	pci_set_master(pdev);

	ret = pci_request_regions(pdev, DRIVER_NAME);
	अगर (ret < 0)
		जाओ err_pci_disable_device;

	pluto->io_mem = pci_iomap(pdev, 0, 0x40);
	अगर (!pluto->io_mem) अणु
		ret = -EIO;
		जाओ err_pci_release_regions;
	पूर्ण

	pci_set_drvdata(pdev, pluto);

	ret = request_irq(pdev->irq, pluto_irq, IRQF_SHARED, DRIVER_NAME, pluto);
	अगर (ret < 0)
		जाओ err_pci_iounmap;

	ret = pluto_hw_init(pluto);
	अगर (ret < 0)
		जाओ err_मुक्त_irq;

	/* i2c */
	i2c_set_adapdata(&pluto->i2c_adap, pluto);
	strscpy(pluto->i2c_adap.name, DRIVER_NAME, माप(pluto->i2c_adap.name));
	pluto->i2c_adap.owner = THIS_MODULE;
	pluto->i2c_adap.dev.parent = &pdev->dev;
	pluto->i2c_adap.algo_data = &pluto->i2c_bit;
	pluto->i2c_bit.data = pluto;
	pluto->i2c_bit.setsda = pluto_setsda;
	pluto->i2c_bit.setscl = pluto_setscl;
	pluto->i2c_bit.माला_लोda = pluto_माला_लोda;
	pluto->i2c_bit.माला_लोcl = pluto_माला_लोcl;
	pluto->i2c_bit.udelay = 10;
	pluto->i2c_bit.समयout = 10;

	/* Raise SCL and SDA */
	pluto_setsda(pluto, 1);
	pluto_setscl(pluto, 1);

	ret = i2c_bit_add_bus(&pluto->i2c_adap);
	अगर (ret < 0)
		जाओ err_pluto_hw_निकास;

	/* dvb */
	ret = dvb_रेजिस्टर_adapter(&pluto->dvb_adapter, DRIVER_NAME,
				   THIS_MODULE, &pdev->dev, adapter_nr);
	अगर (ret < 0)
		जाओ err_i2c_del_adapter;

	dvb_adapter = &pluto->dvb_adapter;

	pluto_पढ़ो_rev(pluto);
	pluto_पढ़ो_serial(pluto);
	pluto_पढ़ो_mac(pluto, dvb_adapter->proposed_mac);

	dvbdemux = &pluto->demux;
	dvbdemux->filternum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->start_feed = pluto_start_feed;
	dvbdemux->stop_feed = pluto_stop_feed;
	dvbdemux->dmx.capabilities = (DMX_TS_FILTERING |
			DMX_SECTION_FILTERING | DMX_MEMORY_BASED_FILTERING);
	ret = dvb_dmx_init(dvbdemux);
	अगर (ret < 0)
		जाओ err_dvb_unरेजिस्टर_adapter;

	dmx = &dvbdemux->dmx;

	pluto->hw_frontend.source = DMX_FRONTEND_0;
	pluto->mem_frontend.source = DMX_MEMORY_FE;
	pluto->dmxdev.filternum = NHWFILTERS;
	pluto->dmxdev.demux = dmx;

	ret = dvb_dmxdev_init(&pluto->dmxdev, dvb_adapter);
	अगर (ret < 0)
		जाओ err_dvb_dmx_release;

	ret = dmx->add_frontend(dmx, &pluto->hw_frontend);
	अगर (ret < 0)
		जाओ err_dvb_dmxdev_release;

	ret = dmx->add_frontend(dmx, &pluto->mem_frontend);
	अगर (ret < 0)
		जाओ err_हटाओ_hw_frontend;

	ret = dmx->connect_frontend(dmx, &pluto->hw_frontend);
	अगर (ret < 0)
		जाओ err_हटाओ_mem_frontend;

	ret = frontend_init(pluto);
	अगर (ret < 0)
		जाओ err_disconnect_frontend;

	dvb_net_init(dvb_adapter, &pluto->dvbnet, dmx);
out:
	वापस ret;

err_disconnect_frontend:
	dmx->disconnect_frontend(dmx);
err_हटाओ_mem_frontend:
	dmx->हटाओ_frontend(dmx, &pluto->mem_frontend);
err_हटाओ_hw_frontend:
	dmx->हटाओ_frontend(dmx, &pluto->hw_frontend);
err_dvb_dmxdev_release:
	dvb_dmxdev_release(&pluto->dmxdev);
err_dvb_dmx_release:
	dvb_dmx_release(dvbdemux);
err_dvb_unरेजिस्टर_adapter:
	dvb_unरेजिस्टर_adapter(dvb_adapter);
err_i2c_del_adapter:
	i2c_del_adapter(&pluto->i2c_adap);
err_pluto_hw_निकास:
	pluto_hw_निकास(pluto);
err_मुक्त_irq:
	मुक्त_irq(pdev->irq, pluto);
err_pci_iounmap:
	pci_iounmap(pdev, pluto->io_mem);
err_pci_release_regions:
	pci_release_regions(pdev);
err_pci_disable_device:
	pci_disable_device(pdev);
err_kमुक्त:
	kमुक्त(pluto);
	जाओ out;
पूर्ण

अटल व्योम pluto2_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pluto *pluto = pci_get_drvdata(pdev);
	काष्ठा dvb_adapter *dvb_adapter = &pluto->dvb_adapter;
	काष्ठा dvb_demux *dvbdemux = &pluto->demux;
	काष्ठा dmx_demux *dmx = &dvbdemux->dmx;

	dmx->बंद(dmx);
	dvb_net_release(&pluto->dvbnet);
	अगर (pluto->fe)
		dvb_unरेजिस्टर_frontend(pluto->fe);

	dmx->disconnect_frontend(dmx);
	dmx->हटाओ_frontend(dmx, &pluto->mem_frontend);
	dmx->हटाओ_frontend(dmx, &pluto->hw_frontend);
	dvb_dmxdev_release(&pluto->dmxdev);
	dvb_dmx_release(dvbdemux);
	dvb_unरेजिस्टर_adapter(dvb_adapter);
	i2c_del_adapter(&pluto->i2c_adap);
	pluto_hw_निकास(pluto);
	मुक्त_irq(pdev->irq, pluto);
	pci_iounmap(pdev, pluto->io_mem);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kमुक्त(pluto);
पूर्ण

#अगर_अघोषित PCI_VENDOR_ID_SCM
#घोषणा PCI_VENDOR_ID_SCM	0x0432
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_PLUTO2
#घोषणा PCI_DEVICE_ID_PLUTO2	0x0001
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id pluto2_id_table[] = अणु
	अणु
		.venकरोr = PCI_VENDOR_ID_SCM,
		.device = PCI_DEVICE_ID_PLUTO2,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	पूर्ण, अणु
		/* empty */
	पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, pluto2_id_table);

अटल काष्ठा pci_driver pluto2_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pluto2_id_table,
	.probe = pluto2_probe,
	.हटाओ = pluto2_हटाओ,
पूर्ण;

module_pci_driver(pluto2_driver);

MODULE_AUTHOR("Andreas Oberritter <obi@linuxtv.org>");
MODULE_DESCRIPTION("Pluto2 driver");
MODULE_LICENSE("GPL");
