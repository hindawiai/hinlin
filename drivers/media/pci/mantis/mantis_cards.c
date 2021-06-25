<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <media/rc-map.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mantis_common.h"

#समावेश "mantis_vp1033.h"
#समावेश "mantis_vp1034.h"
#समावेश "mantis_vp1041.h"
#समावेश "mantis_vp2033.h"
#समावेश "mantis_vp2040.h"
#समावेश "mantis_vp3030.h"

#समावेश "mantis_dma.h"
#समावेश "mantis_ca.h"
#समावेश "mantis_dvb.h"
#समावेश "mantis_uart.h"
#समावेश "mantis_ioc.h"
#समावेश "mantis_pci.h"
#समावेश "mantis_i2c.h"
#समावेश "mantis_reg.h"
#समावेश "mantis_input.h"

अटल अचिन्हित पूर्णांक verbose;
module_param(verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose, "verbose startup messages, default is 0 (no)");

अटल पूर्णांक devs;

#घोषणा DRIVER_NAME	"Mantis"

अटल अक्षर *label[10] = अणु
	"DMA",
	"IRQ-0",
	"IRQ-1",
	"OCERR",
	"PABRT",
	"RIPRR",
	"PPERR",
	"FTRGT",
	"RISCI",
	"RACK"
पूर्ण;

अटल irqवापस_t mantis_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 stat = 0, mask = 0;
	u32 rst_stat = 0, rst_mask = 0;

	काष्ठा mantis_pci *mantis;
	काष्ठा mantis_ca *ca;

	mantis = (काष्ठा mantis_pci *) dev_id;
	अगर (unlikely(!mantis))
		वापस IRQ_NONE;
	ca = mantis->mantis_ca;

	stat = mmपढ़ो(MANTIS_INT_STAT);
	mask = mmपढ़ो(MANTIS_INT_MASK);
	अगर (!(stat & mask))
		वापस IRQ_NONE;

	rst_mask  = MANTIS_GPIF_WRACK  |
		    MANTIS_GPIF_OTHERR |
		    MANTIS_SBUF_WSTO   |
		    MANTIS_GPIF_EXTIRQ;

	rst_stat  = mmपढ़ो(MANTIS_GPIF_STATUS);
	rst_stat &= rst_mask;
	mmग_लिखो(rst_stat, MANTIS_GPIF_STATUS);

	mantis->mantis_पूर्णांक_stat = stat;
	mantis->mantis_पूर्णांक_mask = mask;
	dprपूर्णांकk(MANTIS_DEBUG, 0, "\n-- Stat=<%02x> Mask=<%02x> --", stat, mask);
	अगर (stat & MANTIS_INT_RISCEN) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<%s>", label[0]);
	पूर्ण
	अगर (stat & MANTIS_INT_IRQ0) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<%s>", label[1]);
		mantis->gpअगर_status = rst_stat;
		wake_up(&ca->hअगर_ग_लिखो_wq);
		schedule_work(&ca->hअगर_evm_work);
	पूर्ण
	अगर (stat & MANTIS_INT_IRQ1) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<%s>", label[2]);
		spin_lock(&mantis->पूर्णांकmask_lock);
		mmग_लिखो(mmपढ़ो(MANTIS_INT_MASK) & ~MANTIS_INT_IRQ1,
			MANTIS_INT_MASK);
		spin_unlock(&mantis->पूर्णांकmask_lock);
		schedule_work(&mantis->uart_work);
	पूर्ण
	अगर (stat & MANTIS_INT_OCERR) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<%s>", label[3]);
	पूर्ण
	अगर (stat & MANTIS_INT_PABORT) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<%s>", label[4]);
	पूर्ण
	अगर (stat & MANTIS_INT_RIPERR) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<%s>", label[5]);
	पूर्ण
	अगर (stat & MANTIS_INT_PPERR) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<%s>", label[6]);
	पूर्ण
	अगर (stat & MANTIS_INT_FTRGT) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<%s>", label[7]);
	पूर्ण
	अगर (stat & MANTIS_INT_RISCI) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<%s>", label[8]);
		mantis->busy_block = (stat & MANTIS_INT_RISCSTAT) >> 28;
		tasklet_schedule(&mantis->tasklet);
	पूर्ण
	अगर (stat & MANTIS_INT_I2CDONE) अणु
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<%s>", label[9]);
		wake_up(&mantis->i2c_wq);
	पूर्ण
	mmग_लिखो(stat, MANTIS_INT_STAT);
	stat &= ~(MANTIS_INT_RISCEN   | MANTIS_INT_I2CDONE |
		  MANTIS_INT_I2CRACK  | MANTIS_INT_PCMCIA7 |
		  MANTIS_INT_PCMCIA6  | MANTIS_INT_PCMCIA5 |
		  MANTIS_INT_PCMCIA4  | MANTIS_INT_PCMCIA3 |
		  MANTIS_INT_PCMCIA2  | MANTIS_INT_PCMCIA1 |
		  MANTIS_INT_PCMCIA0  | MANTIS_INT_IRQ1	   |
		  MANTIS_INT_IRQ0     | MANTIS_INT_OCERR   |
		  MANTIS_INT_PABORT   | MANTIS_INT_RIPERR  |
		  MANTIS_INT_PPERR    | MANTIS_INT_FTRGT   |
		  MANTIS_INT_RISCI);

	अगर (stat)
		dprपूर्णांकk(MANTIS_DEBUG, 0, "<Unknown> Stat=<%02x> Mask=<%02x>", stat, mask);

	dprपूर्णांकk(MANTIS_DEBUG, 0, "\n");
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mantis_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा mantis_pci_drvdata *drvdata;
	काष्ठा mantis_pci *mantis;
	काष्ठा mantis_hwconfig *config;
	पूर्णांक err;

	mantis = kzalloc(माप(*mantis), GFP_KERNEL);
	अगर (!mantis)
		वापस -ENOMEM;

	drvdata			= (व्योम *)pci_id->driver_data;
	mantis->num		= devs;
	mantis->verbose		= verbose;
	mantis->pdev		= pdev;
	config			= drvdata->hwconfig;
	config->irq_handler	= &mantis_irq_handler;
	mantis->hwconfig	= config;
	mantis->rc_map_name	= drvdata->rc_map_name;

	spin_lock_init(&mantis->पूर्णांकmask_lock);

	err = mantis_pci_init(mantis);
	अगर (err) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: Mantis PCI initialization failed <%d>", err);
		जाओ err_मुक्त_mantis;
	पूर्ण

	err = mantis_stream_control(mantis, STREAM_TO_HIF);
	अगर (err < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: Mantis stream control failed <%d>", err);
		जाओ err_pci_निकास;
	पूर्ण

	err = mantis_i2c_init(mantis);
	अगर (err < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: Mantis I2C initialization failed <%d>", err);
		जाओ err_pci_निकास;
	पूर्ण

	err = mantis_get_mac(mantis);
	अगर (err < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: Mantis MAC address read failed <%d>", err);
		जाओ err_i2c_निकास;
	पूर्ण

	err = mantis_dma_init(mantis);
	अगर (err < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: Mantis DMA initialization failed <%d>", err);
		जाओ err_i2c_निकास;
	पूर्ण

	err = mantis_dvb_init(mantis);
	अगर (err < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: Mantis DVB initialization failed <%d>", err);
		जाओ err_dma_निकास;
	पूर्ण

	err = mantis_input_init(mantis);
	अगर (err < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1,
			"ERROR: Mantis DVB initialization failed <%d>", err);
		जाओ err_dvb_निकास;
	पूर्ण

	err = mantis_uart_init(mantis);
	अगर (err < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: Mantis UART initialization failed <%d>", err);
		जाओ err_input_निकास;
	पूर्ण

	devs++;

	वापस 0;

err_input_निकास:
	mantis_input_निकास(mantis);

err_dvb_निकास:
	mantis_dvb_निकास(mantis);

err_dma_निकास:
	mantis_dma_निकास(mantis);

err_i2c_निकास:
	mantis_i2c_निकास(mantis);

err_pci_निकास:
	mantis_pci_निकास(mantis);

err_मुक्त_mantis:
	kमुक्त(mantis);

	वापस err;
पूर्ण

अटल व्योम mantis_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mantis_pci *mantis = pci_get_drvdata(pdev);

	अगर (mantis) अणु

		mantis_uart_निकास(mantis);
		mantis_input_निकास(mantis);
		mantis_dvb_निकास(mantis);
		mantis_dma_निकास(mantis);
		mantis_i2c_निकास(mantis);
		mantis_pci_निकास(mantis);
		kमुक्त(mantis);
	पूर्ण
	वापस;
पूर्ण

अटल स्थिर काष्ठा pci_device_id mantis_pci_table[] = अणु
	MAKE_ENTRY(TECHNISAT, CABLESTAR_HD2, &vp2040_config,
		   RC_MAP_TECHNISAT_TS35),
	MAKE_ENTRY(TECHNISAT, SKYSTAR_HD2_10, &vp1041_config,
		   शून्य),
	MAKE_ENTRY(TECHNISAT, SKYSTAR_HD2_20, &vp1041_config,
		   शून्य),
	MAKE_ENTRY(TERRATEC, CINERGY_C, &vp2040_config,
		   RC_MAP_TERRATEC_CINERGY_C_PCI),
	MAKE_ENTRY(TERRATEC, CINERGY_S2_PCI_HD, &vp1041_config,
		   RC_MAP_TERRATEC_CINERGY_S2_HD),
	MAKE_ENTRY(TWINHAN_TECHNOLOGIES, MANTIS_VP_1033_DVB_S, &vp1033_config,
		   शून्य),
	MAKE_ENTRY(TWINHAN_TECHNOLOGIES, MANTIS_VP_1034_DVB_S, &vp1034_config,
		   शून्य),
	MAKE_ENTRY(TWINHAN_TECHNOLOGIES, MANTIS_VP_1041_DVB_S2, &vp1041_config,
		   RC_MAP_TWINHAN_DTV_CAB_CI),
	MAKE_ENTRY(TWINHAN_TECHNOLOGIES, MANTIS_VP_2033_DVB_C, &vp2033_config,
		   RC_MAP_TWINHAN_DTV_CAB_CI),
	MAKE_ENTRY(TWINHAN_TECHNOLOGIES, MANTIS_VP_2040_DVB_C, &vp2040_config,
		   शून्य),
	MAKE_ENTRY(TWINHAN_TECHNOLOGIES, MANTIS_VP_3030_DVB_T, &vp3030_config,
		   शून्य),
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, mantis_pci_table);

अटल काष्ठा pci_driver mantis_pci_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= mantis_pci_table,
	.probe		= mantis_pci_probe,
	.हटाओ		= mantis_pci_हटाओ,
पूर्ण;

module_pci_driver(mantis_pci_driver);

MODULE_DESCRIPTION("MANTIS driver");
MODULE_AUTHOR("Manu Abraham");
MODULE_LICENSE("GPL");
