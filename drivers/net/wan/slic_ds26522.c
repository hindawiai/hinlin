<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/wan/slic_ds26522.c
 *
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 *
 * Author:Zhao Qiang<qiang.zhao@nxp.com>
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/रुको.h>
#समावेश <linux/param.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश "slic_ds26522.h"

#घोषणा SLIC_TRANS_LEN 1
#घोषणा SLIC_TWO_LEN 2
#घोषणा SLIC_THREE_LEN 3

अटल काष्ठा spi_device *g_spi;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zhao Qiang<B45475@freescale.com>");

/* the पढ़ो/ग_लिखो क्रमmat of address is
 * w/r|A13|A12|A11|A10|A9|A8|A7|A6|A5|A4|A3|A2|A1|A0|x
 */
अटल व्योम slic_ग_लिखो(काष्ठा spi_device *spi, u16 addr,
		       u8 data)
अणु
	u8 temp[3];

	addr = bitrev16(addr) >> 1;
	data = bitrev8(data);
	temp[0] = (u8)((addr >> 8) & 0x7f);
	temp[1] = (u8)(addr & 0xfe);
	temp[2] = data;

	/* ग_लिखो spi addr and value */
	spi_ग_लिखो(spi, &temp[0], SLIC_THREE_LEN);
पूर्ण

अटल u8 slic_पढ़ो(काष्ठा spi_device *spi, u16 addr)
अणु
	u8 temp[2];
	u8 data;

	addr = bitrev16(addr) >> 1;
	temp[0] = (u8)(((addr >> 8) & 0x7f) | 0x80);
	temp[1] = (u8)(addr & 0xfe);

	spi_ग_लिखो_then_पढ़ो(spi, &temp[0], SLIC_TWO_LEN, &data,
			    SLIC_TRANS_LEN);

	data = bitrev8(data);
	वापस data;
पूर्ण

अटल bool get_slic_product_code(काष्ठा spi_device *spi)
अणु
	u8 device_id;

	device_id = slic_पढ़ो(spi, DS26522_IDR_ADDR);
	अगर ((device_id & 0xf8) == 0x68)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम ds26522_e1_spec_config(काष्ठा spi_device *spi)
अणु
	/* Receive E1 Mode, Framer Disabled */
	slic_ग_लिखो(spi, DS26522_RMMR_ADDR, DS26522_RMMR_E1);

	/* Transmit E1 Mode, Framer Disable */
	slic_ग_लिखो(spi, DS26522_TMMR_ADDR, DS26522_TMMR_E1);

	/* Receive E1 Mode Framer Enable */
	slic_ग_लिखो(spi, DS26522_RMMR_ADDR,
		   slic_पढ़ो(spi, DS26522_RMMR_ADDR) | DS26522_RMMR_FRM_EN);

	/* Transmit E1 Mode Framer Enable */
	slic_ग_लिखो(spi, DS26522_TMMR_ADDR,
		   slic_पढ़ो(spi, DS26522_TMMR_ADDR) | DS26522_TMMR_FRM_EN);

	/* RCR1, receive E1 B8zs & ESF */
	slic_ग_लिखो(spi, DS26522_RCR1_ADDR,
		   DS26522_RCR1_E1_HDB3 | DS26522_RCR1_E1_CCS);

	/* RSYSCLK=2.048MHz, RSYNC-Output */
	slic_ग_लिखो(spi, DS26522_RIOCR_ADDR,
		   DS26522_RIOCR_2048KHZ | DS26522_RIOCR_RSIO_OUT);

	/* TCR1 Transmit E1 b8zs */
	slic_ग_लिखो(spi, DS26522_TCR1_ADDR, DS26522_TCR1_TB8ZS);

	/* TSYSCLK=2.048MHz, TSYNC-Output */
	slic_ग_लिखो(spi, DS26522_TIOCR_ADDR,
		   DS26522_TIOCR_2048KHZ | DS26522_TIOCR_TSIO_OUT);

	/* Set E1TAF */
	slic_ग_लिखो(spi, DS26522_E1TAF_ADDR, DS26522_E1TAF_DEFAULT);

	/* Set E1TNAF रेजिस्टर */
	slic_ग_लिखो(spi, DS26522_E1TNAF_ADDR, DS26522_E1TNAF_DEFAULT);

	/* Receive E1 Mode Framer Enable & init Done */
	slic_ग_लिखो(spi, DS26522_RMMR_ADDR, slic_पढ़ो(spi, DS26522_RMMR_ADDR) |
		   DS26522_RMMR_INIT_DONE);

	/* Transmit E1 Mode Framer Enable & init Done */
	slic_ग_लिखो(spi, DS26522_TMMR_ADDR, slic_पढ़ो(spi, DS26522_TMMR_ADDR) |
		   DS26522_TMMR_INIT_DONE);

	/* Configure LIU E1 mode */
	slic_ग_लिखो(spi, DS26522_LTRCR_ADDR, DS26522_LTRCR_E1);

	/* E1 Mode शेष 75 ohm w/Transmit Impedance Matlinking */
	slic_ग_लिखो(spi, DS26522_LTITSR_ADDR,
		   DS26522_LTITSR_TLIS_75OHM | DS26522_LTITSR_LBOS_75OHM);

	/* E1 Mode शेष 75 ohm Long Haul w/Receive Impedance Matlinking */
	slic_ग_लिखो(spi, DS26522_LRISMR_ADDR,
		   DS26522_LRISMR_75OHM | DS26522_LRISMR_MAX);

	/* Enable Transmit output */
	slic_ग_लिखो(spi, DS26522_LMCR_ADDR, DS26522_LMCR_TE);
पूर्ण

अटल पूर्णांक slic_ds26522_init_configure(काष्ठा spi_device *spi)
अणु
	u16 addr;

	/* set घड़ी */
	slic_ग_लिखो(spi, DS26522_GTCCR_ADDR, DS26522_GTCCR_BPREFSEL_REFCLKIN |
			DS26522_GTCCR_BFREQSEL_2048KHZ |
			DS26522_GTCCR_FREQSEL_2048KHZ);
	slic_ग_लिखो(spi, DS26522_GTCR2_ADDR, DS26522_GTCR2_TSSYNCOUT);
	slic_ग_लिखो(spi, DS26522_GFCR_ADDR, DS26522_GFCR_BPCLK_2048KHZ);

	/* set gtcr */
	slic_ग_लिखो(spi, DS26522_GTCR1_ADDR, DS26522_GTCR1);

	/* Global LIU Software Reset Register */
	slic_ग_लिखो(spi, DS26522_GLSRR_ADDR, DS26522_GLSRR_RESET);

	/* Global Framer and BERT Software Reset Register */
	slic_ग_लिखो(spi, DS26522_GFSRR_ADDR, DS26522_GFSRR_RESET);

	usleep_range(100, 120);

	slic_ग_लिखो(spi, DS26522_GLSRR_ADDR, DS26522_GLSRR_NORMAL);
	slic_ग_लिखो(spi, DS26522_GFSRR_ADDR, DS26522_GFSRR_NORMAL);

	/* Perक्रमm RX/TX SRESET,Reset receiver */
	slic_ग_लिखो(spi, DS26522_RMMR_ADDR, DS26522_RMMR_SFTRST);

	/* Reset tranceiver */
	slic_ग_लिखो(spi, DS26522_TMMR_ADDR, DS26522_TMMR_SFTRST);

	usleep_range(100, 120);

	/* Zero all Framer Registers */
	क्रम (addr = DS26522_RF_ADDR_START; addr <= DS26522_RF_ADDR_END;
	     addr++)
		slic_ग_लिखो(spi, addr, 0);

	क्रम (addr = DS26522_TF_ADDR_START; addr <= DS26522_TF_ADDR_END;
	     addr++)
		slic_ग_लिखो(spi, addr, 0);

	क्रम (addr = DS26522_LIU_ADDR_START; addr <= DS26522_LIU_ADDR_END;
	     addr++)
		slic_ग_लिखो(spi, addr, 0);

	क्रम (addr = DS26522_BERT_ADDR_START; addr <= DS26522_BERT_ADDR_END;
	     addr++)
		slic_ग_लिखो(spi, addr, 0);

	/* setup ds26522 क्रम E1 specअगरication */
	ds26522_e1_spec_config(spi);

	slic_ग_लिखो(spi, DS26522_GTCR1_ADDR, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक slic_ds26522_हटाओ(काष्ठा spi_device *spi)
अणु
	pr_info("DS26522 module uninstalled\n");
	वापस 0;
पूर्ण

अटल पूर्णांक slic_ds26522_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret = 0;

	g_spi = spi;
	spi->bits_per_word = 8;

	अगर (!get_slic_product_code(spi))
		वापस ret;

	ret = slic_ds26522_init_configure(spi);
	अगर (ret == 0)
		pr_info("DS26522 cs%d configured\n", spi->chip_select);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा spi_device_id slic_ds26522_id[] = अणु
	अणु .name = "ds26522" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, slic_ds26522_id);

अटल स्थिर काष्ठा of_device_id slic_ds26522_match[] = अणु
	अणु
	 .compatible = "maxim,ds26522",
	 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, slic_ds26522_match);

अटल काष्ठा spi_driver slic_ds26522_driver = अणु
	.driver = अणु
		   .name = "ds26522",
		   .bus = &spi_bus_type,
		   .of_match_table = slic_ds26522_match,
		   पूर्ण,
	.probe = slic_ds26522_probe,
	.हटाओ = slic_ds26522_हटाओ,
	.id_table = slic_ds26522_id,
पूर्ण;

module_spi_driver(slic_ds26522_driver);
