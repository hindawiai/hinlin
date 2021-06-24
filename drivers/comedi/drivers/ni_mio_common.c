<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hardware driver क्रम DAQ-STC based boards
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2001 David A. Schleef <ds@schleef.org>
 * Copyright (C) 2002-2006 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

/*
 * This file is meant to be included by another file, e.g.,
 * ni_aपंचांगio.c or ni_pcimio.c.
 *
 * Interrupt support originally added by Truxton Fulton <trux@truxton.com>
 *
 * References (ftp://ftp.natinst.com/support/manuals):
 *   340747b.pdf  AT-MIO E series Register Level Programmer Manual
 *   341079b.pdf  PCI E Series RLPM
 *   340934b.pdf  DAQ-STC reference manual
 *
 * 67xx and 611x रेजिस्टरs (ftp://ftp.ni.com/support/daq/mhddk/करोcumentation/)
 *   release_ni611x.pdf
 *   release_ni67xx.pdf
 *
 * Other possibly relevant info:
 *   320517c.pdf  User manual (obsolete)
 *   320517f.pdf  User manual (new)
 *   320889a.pdf  delete
 *   320906c.pdf  maximum संकेत ratings
 *   321066a.pdf  about 16x
 *   321791a.pdf  discontinuation of at-mio-16e-10 rev. c
 *   321808a.pdf  about at-mio-16e-10 rev P
 *   321837a.pdf  discontinuation of at-mio-16de-10 rev d
 *   321838a.pdf  about at-mio-16de-10 rev N
 *
 * ISSUES:
 *   - the पूर्णांकerrupt routine needs to be cleaned up
 *
 * 2006-02-07: S-Series PCI-6143: Support has been added but is not
 * fully tested as yet. Terry Barnaby, BEAM Ltd.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश "8255.h"
#समावेश "mite.h"

/* A समयout count */
#घोषणा NI_TIMEOUT 1000

/* Note: this table must match the ai_gain_* definitions */
अटल स्थिर लघु ni_gainlkup[][16] = अणु
	[ai_gain_16] = अणु0, 1, 2, 3, 4, 5, 6, 7,
			0x100, 0x101, 0x102, 0x103, 0x104, 0x105, 0x106, 0x107पूर्ण,
	[ai_gain_8] = अणु1, 2, 4, 7, 0x101, 0x102, 0x104, 0x107पूर्ण,
	[ai_gain_14] = अणु1, 2, 3, 4, 5, 6, 7,
			0x101, 0x102, 0x103, 0x104, 0x105, 0x106, 0x107पूर्ण,
	[ai_gain_4] = अणु0, 1, 4, 7पूर्ण,
	[ai_gain_611x] = अणु0x00a, 0x00b, 0x001, 0x002,
			  0x003, 0x004, 0x005, 0x006पूर्ण,
	[ai_gain_622x] = अणु0, 1, 4, 5पूर्ण,
	[ai_gain_628x] = अणु1, 2, 3, 4, 5, 6, 7पूर्ण,
	[ai_gain_6143] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_ni_E_ai = अणु
	16, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1),
		BIP_RANGE(0.5),
		BIP_RANGE(0.25),
		BIP_RANGE(0.1),
		BIP_RANGE(0.05),
		UNI_RANGE(20),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2),
		UNI_RANGE(1),
		UNI_RANGE(0.5),
		UNI_RANGE(0.2),
		UNI_RANGE(0.1)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_ni_E_ai_limited = अणु
	8, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(1),
		UNI_RANGE(0.1)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_ni_E_ai_limited14 = अणु
	14, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2),
		BIP_RANGE(1),
		BIP_RANGE(0.5),
		BIP_RANGE(0.2),
		BIP_RANGE(0.1),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2),
		UNI_RANGE(1),
		UNI_RANGE(0.5),
		UNI_RANGE(0.2),
		UNI_RANGE(0.1)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_ni_E_ai_bipolar4 = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(0.5),
		BIP_RANGE(0.05)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_ni_E_ai_611x = अणु
	8, अणु
		BIP_RANGE(50),
		BIP_RANGE(20),
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2),
		BIP_RANGE(1),
		BIP_RANGE(0.5),
		BIP_RANGE(0.2)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_ni_M_ai_622x = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(1),
		BIP_RANGE(0.2)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_ni_M_ai_628x = अणु
	7, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2),
		BIP_RANGE(1),
		BIP_RANGE(0.5),
		BIP_RANGE(0.2),
		BIP_RANGE(0.1)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_ni_E_ao_ext = अणु
	4, अणु
		BIP_RANGE(10),
		UNI_RANGE(10),
		RANGE_ext(-1, 1),
		RANGE_ext(0, 1)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *स्थिर ni_range_lkup[] = अणु
	[ai_gain_16] = &range_ni_E_ai,
	[ai_gain_8] = &range_ni_E_ai_limited,
	[ai_gain_14] = &range_ni_E_ai_limited14,
	[ai_gain_4] = &range_ni_E_ai_bipolar4,
	[ai_gain_611x] = &range_ni_E_ai_611x,
	[ai_gain_622x] = &range_ni_M_ai_622x,
	[ai_gain_628x] = &range_ni_M_ai_628x,
	[ai_gain_6143] = &range_bipolar5
पूर्ण;

क्रमागत aimodes अणु
	AIMODE_NONE = 0,
	AIMODE_HALF_FULL = 1,
	AIMODE_SCAN = 2,
	AIMODE_SAMPLE = 3,
पूर्ण;

क्रमागत ni_common_subdevices अणु
	NI_AI_SUBDEV,
	NI_AO_SUBDEV,
	NI_DIO_SUBDEV,
	NI_8255_DIO_SUBDEV,
	NI_UNUSED_SUBDEV,
	NI_CALIBRATION_SUBDEV,
	NI_EEPROM_SUBDEV,
	NI_PFI_DIO_SUBDEV,
	NI_CS5529_CALIBRATION_SUBDEV,
	NI_SERIAL_SUBDEV,
	NI_RTSI_SUBDEV,
	NI_GPCT0_SUBDEV,
	NI_GPCT1_SUBDEV,
	NI_FREQ_OUT_SUBDEV,
	NI_NUM_SUBDEVICES
पूर्ण;

#घोषणा NI_GPCT_SUBDEV(x)	(NI_GPCT0_SUBDEV + (x))

क्रमागत समयbase_nanoseconds अणु
	TIMEBASE_1_NS = 50,
	TIMEBASE_2_NS = 10000
पूर्ण;

#घोषणा SERIAL_DISABLED		0
#घोषणा SERIAL_600NS		600
#घोषणा SERIAL_1_2US		1200
#घोषणा SERIAL_10US			10000

अटल स्थिर पूर्णांक num_adc_stages_611x = 3;

अटल व्योम ni_ग_लिखोl(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक data, पूर्णांक reg)
अणु
	अगर (dev->mmio)
		ग_लिखोl(data, dev->mmio + reg);
	अन्यथा
		outl(data, dev->iobase + reg);
पूर्ण

अटल व्योम ni_ग_लिखोw(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक data, पूर्णांक reg)
अणु
	अगर (dev->mmio)
		ग_लिखोw(data, dev->mmio + reg);
	अन्यथा
		outw(data, dev->iobase + reg);
पूर्ण

अटल व्योम ni_ग_लिखोb(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक data, पूर्णांक reg)
अणु
	अगर (dev->mmio)
		ग_लिखोb(data, dev->mmio + reg);
	अन्यथा
		outb(data, dev->iobase + reg);
पूर्ण

अटल अचिन्हित पूर्णांक ni_पढ़ोl(काष्ठा comedi_device *dev, पूर्णांक reg)
अणु
	अगर (dev->mmio)
		वापस पढ़ोl(dev->mmio + reg);

	वापस inl(dev->iobase + reg);
पूर्ण

अटल अचिन्हित पूर्णांक ni_पढ़ोw(काष्ठा comedi_device *dev, पूर्णांक reg)
अणु
	अगर (dev->mmio)
		वापस पढ़ोw(dev->mmio + reg);

	वापस inw(dev->iobase + reg);
पूर्ण

अटल अचिन्हित पूर्णांक ni_पढ़ोb(काष्ठा comedi_device *dev, पूर्णांक reg)
अणु
	अगर (dev->mmio)
		वापस पढ़ोb(dev->mmio + reg);

	वापस inb(dev->iobase + reg);
पूर्ण

/*
 * We स्वतःmatically take advantage of STC रेजिस्टरs that can be
 * पढ़ो/written directly in the I/O space of the board.
 *
 * The AT-MIO and DAQCard devices map the low 8 STC रेजिस्टरs to
 * iobase+reg*2.
 *
 * Most PCIMIO devices also map the low 8 STC रेजिस्टरs but the
 * 611x devices map the पढ़ो रेजिस्टरs to iobase+(addr-1)*2.
 * For now non-winकरोwed STC access is disabled अगर a PCIMIO device
 * is detected (devpriv->mite has been initialized).
 *
 * The M series devices करो not used winकरोwed रेजिस्टरs क्रम the
 * STC रेजिस्टरs. The functions below handle the mapping of the
 * winकरोwed STC रेजिस्टरs to the m series रेजिस्टर offsets.
 */

काष्ठा mio_regmap अणु
	अचिन्हित पूर्णांक mio_reg;
	पूर्णांक size;
पूर्ण;

अटल स्थिर काष्ठा mio_regmap m_series_stc_ग_लिखो_regmap[] = अणु
	[NISTC_INTA_ACK_REG]		= अणु 0x104, 2 पूर्ण,
	[NISTC_INTB_ACK_REG]		= अणु 0x106, 2 पूर्ण,
	[NISTC_AI_CMD2_REG]		= अणु 0x108, 2 पूर्ण,
	[NISTC_AO_CMD2_REG]		= अणु 0x10a, 2 पूर्ण,
	[NISTC_G0_CMD_REG]		= अणु 0x10c, 2 पूर्ण,
	[NISTC_G1_CMD_REG]		= अणु 0x10e, 2 पूर्ण,
	[NISTC_AI_CMD1_REG]		= अणु 0x110, 2 पूर्ण,
	[NISTC_AO_CMD1_REG]		= अणु 0x112, 2 पूर्ण,
	/*
	 * NISTC_DIO_OUT_REG maps to:
	 * अणु NI_M_DIO_REG, 4 पूर्ण and अणु NI_M_SCXI_SER_DO_REG, 1 पूर्ण
	 */
	[NISTC_DIO_OUT_REG]		= अणु 0, 0 पूर्ण, /* DOES NOT MAP CLEANLY */
	[NISTC_DIO_CTRL_REG]		= अणु 0, 0 पूर्ण, /* DOES NOT MAP CLEANLY */
	[NISTC_AI_MODE1_REG]		= अणु 0x118, 2 पूर्ण,
	[NISTC_AI_MODE2_REG]		= अणु 0x11a, 2 पूर्ण,
	[NISTC_AI_SI_LOADA_REG]		= अणु 0x11c, 4 पूर्ण,
	[NISTC_AI_SI_LOADB_REG]		= अणु 0x120, 4 पूर्ण,
	[NISTC_AI_SC_LOADA_REG]		= अणु 0x124, 4 पूर्ण,
	[NISTC_AI_SC_LOADB_REG]		= अणु 0x128, 4 पूर्ण,
	[NISTC_AI_SI2_LOADA_REG]	= अणु 0x12c, 4 पूर्ण,
	[NISTC_AI_SI2_LOADB_REG]	= अणु 0x130, 4 पूर्ण,
	[NISTC_G0_MODE_REG]		= अणु 0x134, 2 पूर्ण,
	[NISTC_G1_MODE_REG]		= अणु 0x136, 2 पूर्ण,
	[NISTC_G0_LOADA_REG]		= अणु 0x138, 4 पूर्ण,
	[NISTC_G0_LOADB_REG]		= अणु 0x13c, 4 पूर्ण,
	[NISTC_G1_LOADA_REG]		= अणु 0x140, 4 पूर्ण,
	[NISTC_G1_LOADB_REG]		= अणु 0x144, 4 पूर्ण,
	[NISTC_G0_INPUT_SEL_REG]	= अणु 0x148, 2 पूर्ण,
	[NISTC_G1_INPUT_SEL_REG]	= अणु 0x14a, 2 पूर्ण,
	[NISTC_AO_MODE1_REG]		= अणु 0x14c, 2 पूर्ण,
	[NISTC_AO_MODE2_REG]		= अणु 0x14e, 2 पूर्ण,
	[NISTC_AO_UI_LOADA_REG]		= अणु 0x150, 4 पूर्ण,
	[NISTC_AO_UI_LOADB_REG]		= अणु 0x154, 4 पूर्ण,
	[NISTC_AO_BC_LOADA_REG]		= अणु 0x158, 4 पूर्ण,
	[NISTC_AO_BC_LOADB_REG]		= अणु 0x15c, 4 पूर्ण,
	[NISTC_AO_UC_LOADA_REG]		= अणु 0x160, 4 पूर्ण,
	[NISTC_AO_UC_LOADB_REG]		= अणु 0x164, 4 पूर्ण,
	[NISTC_CLK_FOUT_REG]		= अणु 0x170, 2 पूर्ण,
	[NISTC_IO_BIसूची_PIN_REG]	= अणु 0x172, 2 पूर्ण,
	[NISTC_RTSI_TRIG_सूची_REG]	= अणु 0x174, 2 पूर्ण,
	[NISTC_INT_CTRL_REG]		= अणु 0x176, 2 पूर्ण,
	[NISTC_AI_OUT_CTRL_REG]		= अणु 0x178, 2 पूर्ण,
	[NISTC_ATRIG_ETC_REG]		= अणु 0x17a, 2 पूर्ण,
	[NISTC_AI_START_STOP_REG]	= अणु 0x17c, 2 पूर्ण,
	[NISTC_AI_TRIG_SEL_REG]		= अणु 0x17e, 2 पूर्ण,
	[NISTC_AI_DIV_LOADA_REG]	= अणु 0x180, 4 पूर्ण,
	[NISTC_AO_START_SEL_REG]	= अणु 0x184, 2 पूर्ण,
	[NISTC_AO_TRIG_SEL_REG]		= अणु 0x186, 2 पूर्ण,
	[NISTC_G0_AUTOINC_REG]		= अणु 0x188, 2 पूर्ण,
	[NISTC_G1_AUTOINC_REG]		= अणु 0x18a, 2 पूर्ण,
	[NISTC_AO_MODE3_REG]		= अणु 0x18c, 2 पूर्ण,
	[NISTC_RESET_REG]		= अणु 0x190, 2 पूर्ण,
	[NISTC_INTA_ENA_REG]		= अणु 0x192, 2 पूर्ण,
	[NISTC_INTA2_ENA_REG]		= अणु 0, 0 पूर्ण, /* E-Series only */
	[NISTC_INTB_ENA_REG]		= अणु 0x196, 2 पूर्ण,
	[NISTC_INTB2_ENA_REG]		= अणु 0, 0 पूर्ण, /* E-Series only */
	[NISTC_AI_PERSONAL_REG]		= अणु 0x19a, 2 पूर्ण,
	[NISTC_AO_PERSONAL_REG]		= अणु 0x19c, 2 पूर्ण,
	[NISTC_RTSI_TRIGA_OUT_REG]	= अणु 0x19e, 2 पूर्ण,
	[NISTC_RTSI_TRIGB_OUT_REG]	= अणु 0x1a0, 2 पूर्ण,
	/* करोc क्रम following line: mhddk/nimseries/ChipObjects/tMSeries.h */
	[NISTC_RTSI_BOARD_REG]		= अणु 0x1a2, 2 पूर्ण,
	[NISTC_CFG_MEM_CLR_REG]		= अणु 0x1a4, 2 पूर्ण,
	[NISTC_ADC_FIFO_CLR_REG]	= अणु 0x1a6, 2 पूर्ण,
	[NISTC_DAC_FIFO_CLR_REG]	= अणु 0x1a8, 2 पूर्ण,
	[NISTC_AO_OUT_CTRL_REG]		= अणु 0x1ac, 2 पूर्ण,
	[NISTC_AI_MODE3_REG]		= अणु 0x1ae, 2 पूर्ण,
पूर्ण;

अटल व्योम m_series_stc_ग_लिखो(काष्ठा comedi_device *dev,
			       अचिन्हित पूर्णांक data, अचिन्हित पूर्णांक reg)
अणु
	स्थिर काष्ठा mio_regmap *regmap;

	अगर (reg < ARRAY_SIZE(m_series_stc_ग_लिखो_regmap)) अणु
		regmap = &m_series_stc_ग_लिखो_regmap[reg];
	पूर्ण अन्यथा अणु
		dev_warn(dev->class_dev, "%s: unhandled register=0x%x\n",
			 __func__, reg);
		वापस;
	पूर्ण

	चयन (regmap->size) अणु
	हाल 4:
		ni_ग_लिखोl(dev, data, regmap->mio_reg);
		अवरोध;
	हाल 2:
		ni_ग_लिखोw(dev, data, regmap->mio_reg);
		अवरोध;
	शेष:
		dev_warn(dev->class_dev, "%s: unmapped register=0x%x\n",
			 __func__, reg);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा mio_regmap m_series_stc_पढ़ो_regmap[] = अणु
	[NISTC_AI_STATUS1_REG]		= अणु 0x104, 2 पूर्ण,
	[NISTC_AO_STATUS1_REG]		= अणु 0x106, 2 पूर्ण,
	[NISTC_G01_STATUS_REG]		= अणु 0x108, 2 पूर्ण,
	[NISTC_AI_STATUS2_REG]		= अणु 0, 0 पूर्ण, /* Unknown */
	[NISTC_AO_STATUS2_REG]		= अणु 0x10c, 2 पूर्ण,
	[NISTC_DIO_IN_REG]		= अणु 0, 0 पूर्ण, /* Unknown */
	[NISTC_G0_HW_SAVE_REG]		= अणु 0x110, 4 पूर्ण,
	[NISTC_G1_HW_SAVE_REG]		= अणु 0x114, 4 पूर्ण,
	[NISTC_G0_SAVE_REG]		= अणु 0x118, 4 पूर्ण,
	[NISTC_G1_SAVE_REG]		= अणु 0x11c, 4 पूर्ण,
	[NISTC_AO_UI_SAVE_REG]		= अणु 0x120, 4 पूर्ण,
	[NISTC_AO_BC_SAVE_REG]		= अणु 0x124, 4 पूर्ण,
	[NISTC_AO_UC_SAVE_REG]		= अणु 0x128, 4 पूर्ण,
	[NISTC_STATUS1_REG]		= अणु 0x136, 2 पूर्ण,
	[NISTC_DIO_SERIAL_IN_REG]	= अणु 0x009, 1 पूर्ण,
	[NISTC_STATUS2_REG]		= अणु 0x13a, 2 पूर्ण,
	[NISTC_AI_SI_SAVE_REG]		= अणु 0x180, 4 पूर्ण,
	[NISTC_AI_SC_SAVE_REG]		= अणु 0x184, 4 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक m_series_stc_पढ़ो(काष्ठा comedi_device *dev,
				      अचिन्हित पूर्णांक reg)
अणु
	स्थिर काष्ठा mio_regmap *regmap;

	अगर (reg < ARRAY_SIZE(m_series_stc_पढ़ो_regmap)) अणु
		regmap = &m_series_stc_पढ़ो_regmap[reg];
	पूर्ण अन्यथा अणु
		dev_warn(dev->class_dev, "%s: unhandled register=0x%x\n",
			 __func__, reg);
		वापस 0;
	पूर्ण

	चयन (regmap->size) अणु
	हाल 4:
		वापस ni_पढ़ोl(dev, regmap->mio_reg);
	हाल 2:
		वापस ni_पढ़ोw(dev, regmap->mio_reg);
	हाल 1:
		वापस ni_पढ़ोb(dev, regmap->mio_reg);
	शेष:
		dev_warn(dev->class_dev, "%s: unmapped register=0x%x\n",
			 __func__, reg);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ni_stc_ग_लिखोw(काष्ठा comedi_device *dev,
			  अचिन्हित पूर्णांक data, पूर्णांक reg)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	अगर (devpriv->is_m_series) अणु
		m_series_stc_ग_लिखो(dev, data, reg);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&devpriv->winकरोw_lock, flags);
		अगर (!devpriv->mite && reg < 8) अणु
			ni_ग_लिखोw(dev, data, reg * 2);
		पूर्ण अन्यथा अणु
			ni_ग_लिखोw(dev, reg, NI_E_STC_WINDOW_ADDR_REG);
			ni_ग_लिखोw(dev, data, NI_E_STC_WINDOW_DATA_REG);
		पूर्ण
		spin_unlock_irqrestore(&devpriv->winकरोw_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम ni_stc_ग_लिखोl(काष्ठा comedi_device *dev,
			  अचिन्हित पूर्णांक data, पूर्णांक reg)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (devpriv->is_m_series) अणु
		m_series_stc_ग_लिखो(dev, data, reg);
	पूर्ण अन्यथा अणु
		ni_stc_ग_लिखोw(dev, data >> 16, reg);
		ni_stc_ग_लिखोw(dev, data & 0xffff, reg + 1);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ni_stc_पढ़ोw(काष्ठा comedi_device *dev, पूर्णांक reg)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	अगर (devpriv->is_m_series) अणु
		val = m_series_stc_पढ़ो(dev, reg);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&devpriv->winकरोw_lock, flags);
		अगर (!devpriv->mite && reg < 8) अणु
			val = ni_पढ़ोw(dev, reg * 2);
		पूर्ण अन्यथा अणु
			ni_ग_लिखोw(dev, reg, NI_E_STC_WINDOW_ADDR_REG);
			val = ni_पढ़ोw(dev, NI_E_STC_WINDOW_DATA_REG);
		पूर्ण
		spin_unlock_irqrestore(&devpriv->winकरोw_lock, flags);
	पूर्ण
	वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक ni_stc_पढ़ोl(काष्ठा comedi_device *dev, पूर्णांक reg)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक val;

	अगर (devpriv->is_m_series) अणु
		val = m_series_stc_पढ़ो(dev, reg);
	पूर्ण अन्यथा अणु
		val = ni_stc_पढ़ोw(dev, reg) << 16;
		val |= ni_stc_पढ़ोw(dev, reg + 1);
	पूर्ण
	वापस val;
पूर्ण

अटल अंतरभूत व्योम ni_set_bitfield(काष्ठा comedi_device *dev, पूर्णांक reg,
				   अचिन्हित पूर्णांक bit_mask,
				   अचिन्हित पूर्णांक bit_values)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->soft_reg_copy_lock, flags);
	चयन (reg) अणु
	हाल NISTC_INTA_ENA_REG:
		devpriv->पूर्णांक_a_enable_reg &= ~bit_mask;
		devpriv->पूर्णांक_a_enable_reg |= bit_values & bit_mask;
		ni_stc_ग_लिखोw(dev, devpriv->पूर्णांक_a_enable_reg, reg);
		अवरोध;
	हाल NISTC_INTB_ENA_REG:
		devpriv->पूर्णांक_b_enable_reg &= ~bit_mask;
		devpriv->पूर्णांक_b_enable_reg |= bit_values & bit_mask;
		ni_stc_ग_लिखोw(dev, devpriv->पूर्णांक_b_enable_reg, reg);
		अवरोध;
	हाल NISTC_IO_BIसूची_PIN_REG:
		devpriv->io_bidirection_pin_reg &= ~bit_mask;
		devpriv->io_bidirection_pin_reg |= bit_values & bit_mask;
		ni_stc_ग_लिखोw(dev, devpriv->io_bidirection_pin_reg, reg);
		अवरोध;
	हाल NI_E_DMA_AI_AO_SEL_REG:
		devpriv->ai_ao_select_reg &= ~bit_mask;
		devpriv->ai_ao_select_reg |= bit_values & bit_mask;
		ni_ग_लिखोb(dev, devpriv->ai_ao_select_reg, reg);
		अवरोध;
	हाल NI_E_DMA_G0_G1_SEL_REG:
		devpriv->g0_g1_select_reg &= ~bit_mask;
		devpriv->g0_g1_select_reg |= bit_values & bit_mask;
		ni_ग_लिखोb(dev, devpriv->g0_g1_select_reg, reg);
		अवरोध;
	हाल NI_M_CDIO_DMA_SEL_REG:
		devpriv->cdio_dma_select_reg &= ~bit_mask;
		devpriv->cdio_dma_select_reg |= bit_values & bit_mask;
		ni_ग_लिखोb(dev, devpriv->cdio_dma_select_reg, reg);
		अवरोध;
	शेष:
		dev_err(dev->class_dev, "called with invalid register %d\n",
			reg);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&devpriv->soft_reg_copy_lock, flags);
पूर्ण

#अगर_घोषित PCIDMA

/* selects the MITE channel to use क्रम DMA */
#घोषणा NI_STC_DMA_CHAN_SEL(x)	(((x) < 4) ? BIT(x) :	\
				 ((x) == 4) ? 0x3 :	\
				 ((x) == 5) ? 0x5 : 0x0)

/* DMA channel setup */
अटल पूर्णांक ni_request_ai_mite_channel(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा mite_channel *mite_chan;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक bits;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	mite_chan = mite_request_channel(devpriv->mite, devpriv->ai_mite_ring);
	अगर (!mite_chan) अणु
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev,
			"failed to reserve mite dma channel for analog input\n");
		वापस -EBUSY;
	पूर्ण
	mite_chan->dir = COMEDI_INPUT;
	devpriv->ai_mite_chan = mite_chan;

	bits = NI_STC_DMA_CHAN_SEL(mite_chan->channel);
	ni_set_bitfield(dev, NI_E_DMA_AI_AO_SEL_REG,
			NI_E_DMA_AI_SEL_MASK, NI_E_DMA_AI_SEL(bits));

	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_request_ao_mite_channel(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा mite_channel *mite_chan;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक bits;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	mite_chan = mite_request_channel(devpriv->mite, devpriv->ao_mite_ring);
	अगर (!mite_chan) अणु
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev,
			"failed to reserve mite dma channel for analog output\n");
		वापस -EBUSY;
	पूर्ण
	mite_chan->dir = COMEDI_OUTPUT;
	devpriv->ao_mite_chan = mite_chan;

	bits = NI_STC_DMA_CHAN_SEL(mite_chan->channel);
	ni_set_bitfield(dev, NI_E_DMA_AI_AO_SEL_REG,
			NI_E_DMA_AO_SEL_MASK, NI_E_DMA_AO_SEL(bits));

	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_request_gpct_mite_channel(काष्ठा comedi_device *dev,
					अचिन्हित पूर्णांक gpct_index,
					क्रमागत comedi_io_direction direction)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा ni_gpct *counter = &devpriv->counter_dev->counters[gpct_index];
	काष्ठा mite_channel *mite_chan;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक bits;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	mite_chan = mite_request_channel(devpriv->mite,
					 devpriv->gpct_mite_ring[gpct_index]);
	अगर (!mite_chan) अणु
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev,
			"failed to reserve mite dma channel for counter\n");
		वापस -EBUSY;
	पूर्ण
	mite_chan->dir = direction;
	ni_tio_set_mite_channel(counter, mite_chan);

	bits = NI_STC_DMA_CHAN_SEL(mite_chan->channel);
	ni_set_bitfield(dev, NI_E_DMA_G0_G1_SEL_REG,
			NI_E_DMA_G0_G1_SEL_MASK(gpct_index),
			NI_E_DMA_G0_G1_SEL(gpct_index, bits));

	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_request_cकरो_mite_channel(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा mite_channel *mite_chan;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक bits;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	mite_chan = mite_request_channel(devpriv->mite, devpriv->cकरो_mite_ring);
	अगर (!mite_chan) अणु
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev,
			"failed to reserve mite dma channel for correlated digital output\n");
		वापस -EBUSY;
	पूर्ण
	mite_chan->dir = COMEDI_OUTPUT;
	devpriv->cकरो_mite_chan = mite_chan;

	/*
	 * XXX just guessing NI_STC_DMA_CHAN_SEL()
	 * वापसs the right bits, under the assumption the cdio dma
	 * selection works just like ai/ao/gpct.
	 * Definitely works क्रम dma channels 0 and 1.
	 */
	bits = NI_STC_DMA_CHAN_SEL(mite_chan->channel);
	ni_set_bitfield(dev, NI_M_CDIO_DMA_SEL_REG,
			NI_M_CDIO_DMA_SEL_CDO_MASK,
			NI_M_CDIO_DMA_SEL_CDO(bits));

	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	वापस 0;
पूर्ण
#पूर्ण_अगर /*  PCIDMA */

अटल व्योम ni_release_ai_mite_channel(काष्ठा comedi_device *dev)
अणु
#अगर_घोषित PCIDMA
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->ai_mite_chan) अणु
		ni_set_bitfield(dev, NI_E_DMA_AI_AO_SEL_REG,
				NI_E_DMA_AI_SEL_MASK, 0);
		mite_release_channel(devpriv->ai_mite_chan);
		devpriv->ai_mite_chan = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
#पूर्ण_अगर /*  PCIDMA */
पूर्ण

अटल व्योम ni_release_ao_mite_channel(काष्ठा comedi_device *dev)
अणु
#अगर_घोषित PCIDMA
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->ao_mite_chan) अणु
		ni_set_bitfield(dev, NI_E_DMA_AI_AO_SEL_REG,
				NI_E_DMA_AO_SEL_MASK, 0);
		mite_release_channel(devpriv->ao_mite_chan);
		devpriv->ao_mite_chan = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
#पूर्ण_अगर /*  PCIDMA */
पूर्ण

#अगर_घोषित PCIDMA
अटल व्योम ni_release_gpct_mite_channel(काष्ठा comedi_device *dev,
					 अचिन्हित पूर्णांक gpct_index)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->counter_dev->counters[gpct_index].mite_chan) अणु
		काष्ठा mite_channel *mite_chan =
		    devpriv->counter_dev->counters[gpct_index].mite_chan;

		ni_set_bitfield(dev, NI_E_DMA_G0_G1_SEL_REG,
				NI_E_DMA_G0_G1_SEL_MASK(gpct_index), 0);
		ni_tio_set_mite_channel(&devpriv->counter_dev->counters[gpct_index],
					शून्य);
		mite_release_channel(mite_chan);
	पूर्ण
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
पूर्ण

अटल व्योम ni_release_cकरो_mite_channel(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->cकरो_mite_chan) अणु
		ni_set_bitfield(dev, NI_M_CDIO_DMA_SEL_REG,
				NI_M_CDIO_DMA_SEL_CDO_MASK, 0);
		mite_release_channel(devpriv->cकरो_mite_chan);
		devpriv->cकरो_mite_chan = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
पूर्ण

अटल व्योम ni_e_series_enable_second_irq(काष्ठा comedi_device *dev,
					  अचिन्हित पूर्णांक gpct_index, लघु enable)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक reg;

	अगर (devpriv->is_m_series || gpct_index > 1)
		वापस;

	/*
	 * e-series boards use the second irq संकेतs to generate
	 * dma requests क्रम their counters
	 */
	अगर (gpct_index == 0) अणु
		reg = NISTC_INTA2_ENA_REG;
		अगर (enable)
			val = NISTC_INTA_ENA_G0_GATE;
	पूर्ण अन्यथा अणु
		reg = NISTC_INTB2_ENA_REG;
		अगर (enable)
			val = NISTC_INTB_ENA_G1_GATE;
	पूर्ण
	ni_stc_ग_लिखोw(dev, val, reg);
पूर्ण
#पूर्ण_अगर /*  PCIDMA */

अटल व्योम ni_clear_ai_fअगरo(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अटल स्थिर पूर्णांक समयout = 10000;
	पूर्णांक i;

	अगर (devpriv->is_6143) अणु
		/*  Flush the 6143 data FIFO */
		ni_ग_लिखोl(dev, 0x10, NI6143_AI_FIFO_CTRL_REG);
		ni_ग_लिखोl(dev, 0x00, NI6143_AI_FIFO_CTRL_REG);
		/*  Wait क्रम complete */
		क्रम (i = 0; i < समयout; i++) अणु
			अगर (!(ni_पढ़ोl(dev, NI6143_AI_FIFO_STATUS_REG) & 0x10))
				अवरोध;
			udelay(1);
		पूर्ण
		अगर (i == समयout)
			dev_err(dev->class_dev, "FIFO flush timeout\n");
	पूर्ण अन्यथा अणु
		ni_stc_ग_लिखोw(dev, 1, NISTC_ADC_FIFO_CLR_REG);
		अगर (devpriv->is_625x) अणु
			ni_ग_लिखोb(dev, 0, NI_M_STATIC_AI_CTRL_REG(0));
			ni_ग_लिखोb(dev, 1, NI_M_STATIC_AI_CTRL_REG(0));
#अगर 0
			/*
			 * The NI example code करोes 3 convert pulses क्रम 625x
			 * boards, But that appears to be wrong in practice.
			 */
			ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);
			ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);
			ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ni_ao_win_outw(काष्ठा comedi_device *dev,
				  अचिन्हित पूर्णांक data, पूर्णांक addr)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->winकरोw_lock, flags);
	ni_ग_लिखोw(dev, addr, NI611X_AO_WINDOW_ADDR_REG);
	ni_ग_लिखोw(dev, data, NI611X_AO_WINDOW_DATA_REG);
	spin_unlock_irqrestore(&devpriv->winकरोw_lock, flags);
पूर्ण

अटल अंतरभूत व्योम ni_ao_win_outl(काष्ठा comedi_device *dev,
				  अचिन्हित पूर्णांक data, पूर्णांक addr)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->winकरोw_lock, flags);
	ni_ग_लिखोw(dev, addr, NI611X_AO_WINDOW_ADDR_REG);
	ni_ग_लिखोl(dev, data, NI611X_AO_WINDOW_DATA_REG);
	spin_unlock_irqrestore(&devpriv->winकरोw_lock, flags);
पूर्ण

अटल अंतरभूत अचिन्हित लघु ni_ao_win_inw(काष्ठा comedi_device *dev, पूर्णांक addr)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु data;

	spin_lock_irqsave(&devpriv->winकरोw_lock, flags);
	ni_ग_लिखोw(dev, addr, NI611X_AO_WINDOW_ADDR_REG);
	data = ni_पढ़ोw(dev, NI611X_AO_WINDOW_DATA_REG);
	spin_unlock_irqrestore(&devpriv->winकरोw_lock, flags);
	वापस data;
पूर्ण

/*
 * ni_set_bits( ) allows dअगरferent parts of the ni_mio_common driver to
 * share रेजिस्टरs (such as Interrupt_A_Register) without पूर्णांकerfering with
 * each other.
 *
 * NOTE: the चयन/हाल statements are optimized out क्रम a स्थिरant argument
 * so this is actually quite fast---  If you must wrap another function around
 * this make it अंतरभूत to aव्योम a large speed penalty.
 *
 * value should only be 1 or 0.
 */
अटल अंतरभूत व्योम ni_set_bits(काष्ठा comedi_device *dev, पूर्णांक reg,
			       अचिन्हित पूर्णांक bits, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक bit_values;

	अगर (value)
		bit_values = bits;
	अन्यथा
		bit_values = 0;
	ni_set_bitfield(dev, reg, bits, bit_values);
पूर्ण

#अगर_घोषित PCIDMA
अटल व्योम ni_sync_ai_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->ai_mite_chan)
		mite_sync_dma(devpriv->ai_mite_chan, s);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
पूर्ण

अटल पूर्णांक ni_ai_drain_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक i;
	अटल स्थिर पूर्णांक समयout = 10000;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->ai_mite_chan) अणु
		क्रम (i = 0; i < समयout; i++) अणु
			अगर ((ni_stc_पढ़ोw(dev, NISTC_AI_STATUS1_REG) &
			     NISTC_AI_STATUS1_FIFO_E) &&
			    mite_bytes_in_transit(devpriv->ai_mite_chan) == 0)
				अवरोध;
			udelay(5);
		पूर्ण
		अगर (i == समयout) अणु
			dev_err(dev->class_dev, "timed out\n");
			dev_err(dev->class_dev,
				"mite_bytes_in_transit=%i, AI_Status1_Register=0x%x\n",
				mite_bytes_in_transit(devpriv->ai_mite_chan),
				ni_stc_पढ़ोw(dev, NISTC_AI_STATUS1_REG));
			retval = -1;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	ni_sync_ai_dma(dev);

	वापस retval;
पूर्ण

अटल पूर्णांक ni_ao_रुको_क्रम_dma_load(काष्ठा comedi_device *dev)
अणु
	अटल स्थिर पूर्णांक समयout = 10000;
	पूर्णांक i;

	क्रम (i = 0; i < समयout; i++) अणु
		अचिन्हित लघु b_status;

		b_status = ni_stc_पढ़ोw(dev, NISTC_AO_STATUS1_REG);
		अगर (b_status & NISTC_AO_STATUS1_FIFO_HF)
			अवरोध;
		/*
		 * If we poll too often, the pci bus activity seems
		 * to slow the dma transfer करोwn.
		 */
		usleep_range(10, 100);
	पूर्ण
	अगर (i == समयout) अणु
		dev_err(dev->class_dev, "timed out waiting for dma load\n");
		वापस -EPIPE;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* PCIDMA */

#अगर_अघोषित PCIDMA

अटल व्योम ni_ao_fअगरo_load(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s, पूर्णांक n)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक i;
	अचिन्हित लघु d;
	अचिन्हित पूर्णांक packed_data;

	क्रम (i = 0; i < n; i++) अणु
		comedi_buf_पढ़ो_samples(s, &d, 1);

		अगर (devpriv->is_6xxx) अणु
			packed_data = d & 0xffff;
			/* 6711 only has 16 bit wide ao fअगरo */
			अगर (!devpriv->is_6711) अणु
				comedi_buf_पढ़ो_samples(s, &d, 1);
				i++;
				packed_data |= (d << 16) & 0xffff0000;
			पूर्ण
			ni_ग_लिखोl(dev, packed_data, NI611X_AO_FIFO_DATA_REG);
		पूर्ण अन्यथा अणु
			ni_ग_लिखोw(dev, d, NI_E_AO_FIFO_DATA_REG);
		पूर्ण
	पूर्ण
पूर्ण

/*
 *  There's a small problem अगर the FIFO माला_लो really low and we
 *  करोn't have the data to fill it.  Basically, अगर after we fill
 *  the FIFO with all the data available, the FIFO is _still_
 *  less than half full, we never clear the पूर्णांकerrupt.  If the
 *  IRQ is in edge mode, we never get another पूर्णांकerrupt, because
 *  this one wasn't cleared.  If in level mode, we get flooded
 *  with पूर्णांकerrupts that we can't fulfill, because nothing ever
 *  माला_लो put पूर्णांकo the buffer.
 *
 *  This kind of situation is recoverable, but it is easier to
 *  just pretend we had a FIFO underrun, since there is a good
 *  chance it will happen anyway.  This is _not_ the हाल क्रम
 *  RT code, as RT code might purposely be running बंद to the
 *  metal.  Needs to be fixed eventually.
 */
अटल पूर्णांक ni_ao_fअगरo_half_empty(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	अचिन्हित पूर्णांक nbytes;
	अचिन्हित पूर्णांक nsamples;

	nbytes = comedi_buf_पढ़ो_n_available(s);
	अगर (nbytes == 0) अणु
		s->async->events |= COMEDI_CB_OVERFLOW;
		वापस 0;
	पूर्ण

	nsamples = comedi_bytes_to_samples(s, nbytes);
	अगर (nsamples > board->ao_fअगरo_depth / 2)
		nsamples = board->ao_fअगरo_depth / 2;

	ni_ao_fअगरo_load(dev, s, nsamples);

	वापस 1;
पूर्ण

अटल पूर्णांक ni_ao_prep_fअगरo(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक nbytes;
	अचिन्हित पूर्णांक nsamples;

	/* reset fअगरo */
	ni_stc_ग_लिखोw(dev, 1, NISTC_DAC_FIFO_CLR_REG);
	अगर (devpriv->is_6xxx)
		ni_ao_win_outl(dev, 0x6, NI611X_AO_FIFO_OFFSET_LOAD_REG);

	/* load some data */
	nbytes = comedi_buf_पढ़ो_n_available(s);
	अगर (nbytes == 0)
		वापस 0;

	nsamples = comedi_bytes_to_samples(s, nbytes);
	अगर (nsamples > board->ao_fअगरo_depth)
		nsamples = board->ao_fअगरo_depth;

	ni_ao_fअगरo_load(dev, s, nsamples);

	वापस nsamples;
पूर्ण

अटल व्योम ni_ai_fअगरo_पढ़ो(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s, पूर्णांक n)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक dl;
	अचिन्हित लघु data;
	पूर्णांक i;

	अगर (devpriv->is_611x) अणु
		क्रम (i = 0; i < n / 2; i++) अणु
			dl = ni_पढ़ोl(dev, NI611X_AI_FIFO_DATA_REG);
			/* This may get the hi/lo data in the wrong order */
			data = (dl >> 16) & 0xffff;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
			data = dl & 0xffff;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
		पूर्ण
		/* Check अगर there's a single sample stuck in the FIFO */
		अगर (n % 2) अणु
			dl = ni_पढ़ोl(dev, NI611X_AI_FIFO_DATA_REG);
			data = dl & 0xffff;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
		पूर्ण
	पूर्ण अन्यथा अगर (devpriv->is_6143) अणु
		/*
		 * This just पढ़ोs the FIFO assuming the data is present,
		 * no checks on the FIFO status are perक्रमmed.
		 */
		क्रम (i = 0; i < n / 2; i++) अणु
			dl = ni_पढ़ोl(dev, NI6143_AI_FIFO_DATA_REG);

			data = (dl >> 16) & 0xffff;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
			data = dl & 0xffff;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
		पूर्ण
		अगर (n % 2) अणु
			/* Assume there is a single sample stuck in the FIFO */
			/* Get stअक्रमed sample पूर्णांकo FIFO */
			ni_ग_लिखोl(dev, 0x01, NI6143_AI_FIFO_CTRL_REG);
			dl = ni_पढ़ोl(dev, NI6143_AI_FIFO_DATA_REG);
			data = (dl >> 16) & 0xffff;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (n > ARRAY_SIZE(devpriv->ai_fअगरo_buffer)) अणु
			dev_err(dev->class_dev,
				"bug! ai_fifo_buffer too small\n");
			async->events |= COMEDI_CB_ERROR;
			वापस;
		पूर्ण
		क्रम (i = 0; i < n; i++) अणु
			devpriv->ai_fअगरo_buffer[i] =
			    ni_पढ़ोw(dev, NI_E_AI_FIFO_DATA_REG);
		पूर्ण
		comedi_buf_ग_लिखो_samples(s, devpriv->ai_fअगरo_buffer, n);
	पूर्ण
पूर्ण

अटल व्योम ni_handle_fअगरo_half_full(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	पूर्णांक n;

	n = board->ai_fअगरo_depth / 2;

	ni_ai_fअगरo_पढ़ो(dev, s, n);
पूर्ण
#पूर्ण_अगर

/* Empties the AI fअगरo */
अटल व्योम ni_handle_fअगरo_dregs(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक dl;
	अचिन्हित लघु data;
	पूर्णांक i;

	अगर (devpriv->is_611x) अणु
		जबतक ((ni_stc_पढ़ोw(dev, NISTC_AI_STATUS1_REG) &
			NISTC_AI_STATUS1_FIFO_E) == 0) अणु
			dl = ni_पढ़ोl(dev, NI611X_AI_FIFO_DATA_REG);

			/* This may get the hi/lo data in the wrong order */
			data = dl >> 16;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
			data = dl & 0xffff;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
		पूर्ण
	पूर्ण अन्यथा अगर (devpriv->is_6143) अणु
		i = 0;
		जबतक (ni_पढ़ोl(dev, NI6143_AI_FIFO_STATUS_REG) & 0x04) अणु
			dl = ni_पढ़ोl(dev, NI6143_AI_FIFO_DATA_REG);

			/* This may get the hi/lo data in the wrong order */
			data = dl >> 16;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
			data = dl & 0xffff;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
			i += 2;
		पूर्ण
		/*  Check अगर stअक्रमed sample is present */
		अगर (ni_पढ़ोl(dev, NI6143_AI_FIFO_STATUS_REG) & 0x01) अणु
			/* Get stअक्रमed sample पूर्णांकo FIFO */
			ni_ग_लिखोl(dev, 0x01, NI6143_AI_FIFO_CTRL_REG);
			dl = ni_पढ़ोl(dev, NI6143_AI_FIFO_DATA_REG);
			data = (dl >> 16) & 0xffff;
			comedi_buf_ग_लिखो_samples(s, &data, 1);
		पूर्ण

	पूर्ण अन्यथा अणु
		अचिन्हित लघु fe;	/* fअगरo empty */

		fe = ni_stc_पढ़ोw(dev, NISTC_AI_STATUS1_REG) &
		     NISTC_AI_STATUS1_FIFO_E;
		जबतक (fe == 0) अणु
			क्रम (i = 0;
			     i < ARRAY_SIZE(devpriv->ai_fअगरo_buffer); i++) अणु
				fe = ni_stc_पढ़ोw(dev, NISTC_AI_STATUS1_REG) &
				     NISTC_AI_STATUS1_FIFO_E;
				अगर (fe)
					अवरोध;
				devpriv->ai_fअगरo_buffer[i] =
				    ni_पढ़ोw(dev, NI_E_AI_FIFO_DATA_REG);
			पूर्ण
			comedi_buf_ग_लिखो_samples(s, devpriv->ai_fअगरo_buffer, i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम get_last_sample_611x(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित लघु data;
	अचिन्हित पूर्णांक dl;

	अगर (!devpriv->is_611x)
		वापस;

	/* Check अगर there's a single sample stuck in the FIFO */
	अगर (ni_पढ़ोb(dev, NI_E_STATUS_REG) & 0x80) अणु
		dl = ni_पढ़ोl(dev, NI611X_AI_FIFO_DATA_REG);
		data = dl & 0xffff;
		comedi_buf_ग_लिखो_samples(s, &data, 1);
	पूर्ण
पूर्ण

अटल व्योम get_last_sample_6143(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित लघु data;
	अचिन्हित पूर्णांक dl;

	अगर (!devpriv->is_6143)
		वापस;

	/* Check अगर there's a single sample stuck in the FIFO */
	अगर (ni_पढ़ोl(dev, NI6143_AI_FIFO_STATUS_REG) & 0x01) अणु
		/* Get stअक्रमed sample पूर्णांकo FIFO */
		ni_ग_लिखोl(dev, 0x01, NI6143_AI_FIFO_CTRL_REG);
		dl = ni_पढ़ोl(dev, NI6143_AI_FIFO_DATA_REG);

		/* This may get the hi/lo data in the wrong order */
		data = (dl >> 16) & 0xffff;
		comedi_buf_ग_लिखो_samples(s, &data, 1);
	पूर्ण
पूर्ण

अटल व्योम shutकरोwn_ai_command(काष्ठा comedi_device *dev)
अणु
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;

#अगर_घोषित PCIDMA
	ni_ai_drain_dma(dev);
#पूर्ण_अगर
	ni_handle_fअगरo_dregs(dev);
	get_last_sample_611x(dev);
	get_last_sample_6143(dev);

	s->async->events |= COMEDI_CB_EOA;
पूर्ण

अटल व्योम ni_handle_eos(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (devpriv->aimode == AIMODE_SCAN) अणु
#अगर_घोषित PCIDMA
		अटल स्थिर पूर्णांक समयout = 10;
		पूर्णांक i;

		क्रम (i = 0; i < समयout; i++) अणु
			ni_sync_ai_dma(dev);
			अगर ((s->async->events & COMEDI_CB_EOS))
				अवरोध;
			udelay(1);
		पूर्ण
#अन्यथा
		ni_handle_fअगरo_dregs(dev);
		s->async->events |= COMEDI_CB_EOS;
#पूर्ण_अगर
	पूर्ण
	/* handle special हाल of single scan */
	अगर (devpriv->ai_cmd2 & NISTC_AI_CMD2_END_ON_EOS)
		shutकरोwn_ai_command(dev);
पूर्ण

अटल व्योम handle_gpct_पूर्णांकerrupt(काष्ठा comedi_device *dev,
				  अचिन्हित लघु counter_index)
अणु
#अगर_घोषित PCIDMA
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s;

	s = &dev->subdevices[NI_GPCT_SUBDEV(counter_index)];

	ni_tio_handle_पूर्णांकerrupt(&devpriv->counter_dev->counters[counter_index],
				s);
	comedi_handle_events(dev, s);
#पूर्ण_अगर
पूर्ण

अटल व्योम ack_a_पूर्णांकerrupt(काष्ठा comedi_device *dev, अचिन्हित लघु a_status)
अणु
	अचिन्हित लघु ack = 0;

	अगर (a_status & NISTC_AI_STATUS1_SC_TC)
		ack |= NISTC_INTA_ACK_AI_SC_TC;
	अगर (a_status & NISTC_AI_STATUS1_START1)
		ack |= NISTC_INTA_ACK_AI_START1;
	अगर (a_status & NISTC_AI_STATUS1_START)
		ack |= NISTC_INTA_ACK_AI_START;
	अगर (a_status & NISTC_AI_STATUS1_STOP)
		ack |= NISTC_INTA_ACK_AI_STOP;
	अगर (a_status & NISTC_AI_STATUS1_OVER)
		ack |= NISTC_INTA_ACK_AI_ERR;
	अगर (ack)
		ni_stc_ग_लिखोw(dev, ack, NISTC_INTA_ACK_REG);
पूर्ण

अटल व्योम handle_a_पूर्णांकerrupt(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       अचिन्हित लघु status)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	/* test क्रम all uncommon पूर्णांकerrupt events at the same समय */
	अगर (status & (NISTC_AI_STATUS1_ERR |
		      NISTC_AI_STATUS1_SC_TC | NISTC_AI_STATUS1_START1)) अणु
		अगर (status == 0xffff) अणु
			dev_err(dev->class_dev, "Card removed?\n");
			/*
			 * We probably aren't even running a command now,
			 * so it's a good idea to be careful.
			 */
			अगर (comedi_is_subdevice_running(s))
				s->async->events |= COMEDI_CB_ERROR;
			वापस;
		पूर्ण
		अगर (status & NISTC_AI_STATUS1_ERR) अणु
			dev_err(dev->class_dev, "ai error a_status=%04x\n",
				status);

			shutकरोwn_ai_command(dev);

			s->async->events |= COMEDI_CB_ERROR;
			अगर (status & NISTC_AI_STATUS1_OVER)
				s->async->events |= COMEDI_CB_OVERFLOW;
			वापस;
		पूर्ण
		अगर (status & NISTC_AI_STATUS1_SC_TC) अणु
			अगर (cmd->stop_src == TRIG_COUNT)
				shutकरोwn_ai_command(dev);
		पूर्ण
	पूर्ण
#अगर_अघोषित PCIDMA
	अगर (status & NISTC_AI_STATUS1_FIFO_HF) अणु
		पूर्णांक i;
		अटल स्थिर पूर्णांक समयout = 10;
		/*
		 * PCMCIA cards (at least 6036) seem to stop producing
		 * पूर्णांकerrupts अगर we fail to get the fअगरo less than half
		 * full, so loop to be sure.
		 */
		क्रम (i = 0; i < समयout; ++i) अणु
			ni_handle_fअगरo_half_full(dev);
			अगर ((ni_stc_पढ़ोw(dev, NISTC_AI_STATUS1_REG) &
			     NISTC_AI_STATUS1_FIFO_HF) == 0)
				अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /*  !PCIDMA */

	अगर (status & NISTC_AI_STATUS1_STOP)
		ni_handle_eos(dev, s);
पूर्ण

अटल व्योम ack_b_पूर्णांकerrupt(काष्ठा comedi_device *dev, अचिन्हित लघु b_status)
अणु
	अचिन्हित लघु ack = 0;

	अगर (b_status & NISTC_AO_STATUS1_BC_TC)
		ack |= NISTC_INTB_ACK_AO_BC_TC;
	अगर (b_status & NISTC_AO_STATUS1_OVERRUN)
		ack |= NISTC_INTB_ACK_AO_ERR;
	अगर (b_status & NISTC_AO_STATUS1_START)
		ack |= NISTC_INTB_ACK_AO_START;
	अगर (b_status & NISTC_AO_STATUS1_START1)
		ack |= NISTC_INTB_ACK_AO_START1;
	अगर (b_status & NISTC_AO_STATUS1_UC_TC)
		ack |= NISTC_INTB_ACK_AO_UC_TC;
	अगर (b_status & NISTC_AO_STATUS1_UI2_TC)
		ack |= NISTC_INTB_ACK_AO_UI2_TC;
	अगर (b_status & NISTC_AO_STATUS1_UPDATE)
		ack |= NISTC_INTB_ACK_AO_UPDATE;
	अगर (ack)
		ni_stc_ग_लिखोw(dev, ack, NISTC_INTB_ACK_REG);
पूर्ण

अटल व्योम handle_b_पूर्णांकerrupt(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       अचिन्हित लघु b_status)
अणु
	अगर (b_status == 0xffff)
		वापस;
	अगर (b_status & NISTC_AO_STATUS1_OVERRUN) अणु
		dev_err(dev->class_dev,
			"AO FIFO underrun status=0x%04x status2=0x%04x\n",
			b_status, ni_stc_पढ़ोw(dev, NISTC_AO_STATUS2_REG));
		s->async->events |= COMEDI_CB_OVERFLOW;
	पूर्ण

	अगर (s->async->cmd.stop_src != TRIG_NONE &&
	    b_status & NISTC_AO_STATUS1_BC_TC)
		s->async->events |= COMEDI_CB_EOA;

#अगर_अघोषित PCIDMA
	अगर (b_status & NISTC_AO_STATUS1_FIFO_REQ) अणु
		पूर्णांक ret;

		ret = ni_ao_fअगरo_half_empty(dev, s);
		अगर (!ret) अणु
			dev_err(dev->class_dev, "AO buffer underrun\n");
			ni_set_bits(dev, NISTC_INTB_ENA_REG,
				    NISTC_INTB_ENA_AO_FIFO |
				    NISTC_INTB_ENA_AO_ERR, 0);
			s->async->events |= COMEDI_CB_OVERFLOW;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम ni_ai_munge(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			व्योम *data, अचिन्हित पूर्णांक num_bytes,
			अचिन्हित पूर्णांक chan_index)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक nsamples = comedi_bytes_to_samples(s, num_bytes);
	अचिन्हित लघु *array = data;
	अचिन्हित पूर्णांक *larray = data;
	अचिन्हित पूर्णांक i;
#अगर_घोषित PCIDMA
	__le16 *barray = data;
	__le32 *blarray = data;
#पूर्ण_अगर

	क्रम (i = 0; i < nsamples; i++) अणु
#अगर_घोषित PCIDMA
		अगर (s->subdev_flags & SDF_LSAMPL)
			larray[i] = le32_to_cpu(blarray[i]);
		अन्यथा
			array[i] = le16_to_cpu(barray[i]);
#पूर्ण_अगर
		अगर (s->subdev_flags & SDF_LSAMPL)
			larray[i] += devpriv->ai_offset[chan_index];
		अन्यथा
			array[i] += devpriv->ai_offset[chan_index];
		chan_index++;
		chan_index %= cmd->chanlist_len;
	पूर्ण
पूर्ण

#अगर_घोषित PCIDMA

अटल पूर्णांक ni_ai_setup_MITE_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	retval = ni_request_ai_mite_channel(dev);
	अगर (retval)
		वापस retval;

	/* ग_लिखो alloc the entire buffer */
	comedi_buf_ग_लिखो_alloc(s, s->async->pपुनः_स्मृति_bufsz);

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (!devpriv->ai_mite_chan) अणु
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		वापस -EIO;
	पूर्ण

	अगर (devpriv->is_611x || devpriv->is_6143)
		mite_prep_dma(devpriv->ai_mite_chan, 32, 16);
	अन्यथा अगर (devpriv->is_628x)
		mite_prep_dma(devpriv->ai_mite_chan, 32, 32);
	अन्यथा
		mite_prep_dma(devpriv->ai_mite_chan, 16, 16);

	/*start the MITE */
	mite_dma_arm(devpriv->ai_mite_chan);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ni_ao_setup_MITE_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->ग_लिखो_subdev;
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	retval = ni_request_ao_mite_channel(dev);
	अगर (retval)
		वापस retval;

	/* पढ़ो alloc the entire buffer */
	comedi_buf_पढ़ो_alloc(s, s->async->pपुनः_स्मृति_bufsz);

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->ao_mite_chan) अणु
		अगर (devpriv->is_611x || devpriv->is_6713) अणु
			mite_prep_dma(devpriv->ao_mite_chan, 32, 32);
		पूर्ण अन्यथा अणु
			/*
			 * Doing 32 instead of 16 bit wide transfers from
			 * memory makes the mite करो 32 bit pci transfers,
			 * करोubling pci bandwidth.
			 */
			mite_prep_dma(devpriv->ao_mite_chan, 16, 32);
		पूर्ण
		mite_dma_arm(devpriv->ao_mite_chan);
	पूर्ण अन्यथा अणु
		retval = -EIO;
	पूर्ण
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	वापस retval;
पूर्ण

#पूर्ण_अगर /*  PCIDMA */

/*
 * used क्रम both cancel ioctl and board initialization
 *
 * this is pretty harsh क्रम a cancel, but it works...
 */
अटल पूर्णांक ni_ai_reset(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक ai_personal;
	अचिन्हित पूर्णांक ai_out_ctrl;

	ni_release_ai_mite_channel(dev);
	/* ai configuration */
	ni_stc_ग_लिखोw(dev, NISTC_RESET_AI_CFG_START | NISTC_RESET_AI,
		      NISTC_RESET_REG);

	ni_set_bits(dev, NISTC_INTA_ENA_REG, NISTC_INTA_ENA_AI_MASK, 0);

	ni_clear_ai_fअगरo(dev);

	अगर (!devpriv->is_6143)
		ni_ग_लिखोb(dev, NI_E_MISC_CMD_EXT_ATRIG, NI_E_MISC_CMD_REG);

	ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_DISARM, NISTC_AI_CMD1_REG);
	ni_stc_ग_लिखोw(dev, NISTC_AI_MODE1_START_STOP |
			   NISTC_AI_MODE1_RSVD
			    /*| NISTC_AI_MODE1_TRIGGER_ONCE */,
		      NISTC_AI_MODE1_REG);
	ni_stc_ग_लिखोw(dev, 0, NISTC_AI_MODE2_REG);
	/* generate FIFO पूर्णांकerrupts on non-empty */
	ni_stc_ग_लिखोw(dev, NISTC_AI_MODE3_FIFO_MODE_NE,
		      NISTC_AI_MODE3_REG);

	ai_personal = NISTC_AI_PERSONAL_SHIFTIN_PW |
		      NISTC_AI_PERSONAL_SOC_POLARITY |
		      NISTC_AI_PERSONAL_LOCALMUX_CLK_PW;
	ai_out_ctrl = NISTC_AI_OUT_CTRL_SCAN_IN_PROG_SEL(3) |
		      NISTC_AI_OUT_CTRL_EXTMUX_CLK_SEL(0) |
		      NISTC_AI_OUT_CTRL_LOCALMUX_CLK_SEL(2) |
		      NISTC_AI_OUT_CTRL_SC_TC_SEL(3);
	अगर (devpriv->is_611x) अणु
		ai_out_ctrl |= NISTC_AI_OUT_CTRL_CONVERT_HIGH;
	पूर्ण अन्यथा अगर (devpriv->is_6143) अणु
		ai_out_ctrl |= NISTC_AI_OUT_CTRL_CONVERT_LOW;
	पूर्ण अन्यथा अणु
		ai_personal |= NISTC_AI_PERSONAL_CONVERT_PW;
		अगर (devpriv->is_622x)
			ai_out_ctrl |= NISTC_AI_OUT_CTRL_CONVERT_HIGH;
		अन्यथा
			ai_out_ctrl |= NISTC_AI_OUT_CTRL_CONVERT_LOW;
	पूर्ण
	ni_stc_ग_लिखोw(dev, ai_personal, NISTC_AI_PERSONAL_REG);
	ni_stc_ग_लिखोw(dev, ai_out_ctrl, NISTC_AI_OUT_CTRL_REG);

	/* the following रेजिस्टरs should not be changed, because there
	 * are no backup रेजिस्टरs in devpriv.  If you want to change
	 * any of these, add a backup रेजिस्टर and other appropriate code:
	 *      NISTC_AI_MODE1_REG
	 *      NISTC_AI_MODE3_REG
	 *      NISTC_AI_PERSONAL_REG
	 *      NISTC_AI_OUT_CTRL_REG
	 */

	/* clear पूर्णांकerrupts */
	ni_stc_ग_लिखोw(dev, NISTC_INTA_ACK_AI_ALL, NISTC_INTA_ACK_REG);

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AI_CFG_END, NISTC_RESET_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक ni_ai_poll(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक count;

	/*  lock to aव्योम race with पूर्णांकerrupt handler */
	spin_lock_irqsave(&dev->spinlock, flags);
#अगर_अघोषित PCIDMA
	ni_handle_fअगरo_dregs(dev);
#अन्यथा
	ni_sync_ai_dma(dev);
#पूर्ण_अगर
	count = comedi_buf_n_bytes_पढ़ोy(s);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस count;
पूर्ण

अटल व्योम ni_prime_channelgain_list(काष्ठा comedi_device *dev)
अणु
	पूर्णांक i;

	ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_CONVERT_PULSE, NISTC_AI_CMD1_REG);
	क्रम (i = 0; i < NI_TIMEOUT; ++i) अणु
		अगर (!(ni_stc_पढ़ोw(dev, NISTC_AI_STATUS1_REG) &
		      NISTC_AI_STATUS1_FIFO_E)) अणु
			ni_stc_ग_लिखोw(dev, 1, NISTC_ADC_FIFO_CLR_REG);
			वापस;
		पूर्ण
		udelay(1);
	पूर्ण
	dev_err(dev->class_dev, "timeout loading channel/gain list\n");
पूर्ण

अटल व्योम ni_m_series_load_channelgain_list(काष्ठा comedi_device *dev,
					      अचिन्हित पूर्णांक n_chan,
					      अचिन्हित पूर्णांक *list)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan, range, aref;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक dither;
	अचिन्हित पूर्णांक range_code;

	ni_stc_ग_लिखोw(dev, 1, NISTC_CFG_MEM_CLR_REG);

	अगर ((list[0] & CR_ALT_SOURCE)) अणु
		अचिन्हित पूर्णांक bypass_bits;

		chan = CR_CHAN(list[0]);
		range = CR_RANGE(list[0]);
		range_code = ni_gainlkup[board->gainlkup][range];
		dither = (list[0] & CR_ALT_FILTER) != 0;
		bypass_bits = NI_M_CFG_BYPASS_FIFO |
			      NI_M_CFG_BYPASS_AI_CHAN(chan) |
			      NI_M_CFG_BYPASS_AI_GAIN(range_code) |
			      devpriv->ai_calib_source;
		अगर (dither)
			bypass_bits |= NI_M_CFG_BYPASS_AI_DITHER;
		/*  करोn't use 2's complement encoding */
		bypass_bits |= NI_M_CFG_BYPASS_AI_POLARITY;
		ni_ग_लिखोl(dev, bypass_bits, NI_M_CFG_BYPASS_FIFO_REG);
	पूर्ण अन्यथा अणु
		ni_ग_लिखोl(dev, 0, NI_M_CFG_BYPASS_FIFO_REG);
	पूर्ण
	क्रम (i = 0; i < n_chan; i++) अणु
		अचिन्हित पूर्णांक config_bits = 0;

		chan = CR_CHAN(list[i]);
		aref = CR_AREF(list[i]);
		range = CR_RANGE(list[i]);
		dither = (list[i] & CR_ALT_FILTER) != 0;

		range_code = ni_gainlkup[board->gainlkup][range];
		devpriv->ai_offset[i] = 0;
		चयन (aref) अणु
		हाल AREF_DIFF:
			config_bits |= NI_M_AI_CFG_CHAN_TYPE_DIFF;
			अवरोध;
		हाल AREF_COMMON:
			config_bits |= NI_M_AI_CFG_CHAN_TYPE_COMMON;
			अवरोध;
		हाल AREF_GROUND:
			config_bits |= NI_M_AI_CFG_CHAN_TYPE_GROUND;
			अवरोध;
		हाल AREF_OTHER:
			अवरोध;
		पूर्ण
		config_bits |= NI_M_AI_CFG_CHAN_SEL(chan);
		config_bits |= NI_M_AI_CFG_BANK_SEL(chan);
		config_bits |= NI_M_AI_CFG_GAIN(range_code);
		अगर (i == n_chan - 1)
			config_bits |= NI_M_AI_CFG_LAST_CHAN;
		अगर (dither)
			config_bits |= NI_M_AI_CFG_DITHER;
		/*  करोn't use 2's complement encoding */
		config_bits |= NI_M_AI_CFG_POLARITY;
		ni_ग_लिखोw(dev, config_bits, NI_M_AI_CFG_FIFO_DATA_REG);
	पूर्ण
	ni_prime_channelgain_list(dev);
पूर्ण

/*
 * Notes on the 6110 and 6111:
 * These boards a slightly dअगरferent than the rest of the series, since
 * they have multiple A/D converters.
 * From the driver side, the configuration memory is a
 * little dअगरferent.
 * Configuration Memory Low:
 *   bits 15-9: same
 *   bit 8: unipolar/bipolar (should be 0 क्रम bipolar)
 *   bits 0-3: gain.  This is 4 bits instead of 3 क्रम the other boards
 *       1001 gain=0.1 (+/- 50)
 *       1010 0.2
 *       1011 0.1
 *       0001 1
 *       0010 2
 *       0011 5
 *       0100 10
 *       0101 20
 *       0110 50
 * Configuration Memory High:
 *   bits 12-14: Channel Type
 *       001 क्रम dअगरferential
 *       000 क्रम calibration
 *   bit 11: coupling  (this is not currently handled)
 *       1 AC coupling
 *       0 DC coupling
 *   bits 0-2: channel
 *       valid channels are 0-3
 */
अटल व्योम ni_load_channelgain_list(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक n_chan, अचिन्हित पूर्णांक *list)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक offset = (s->maxdata + 1) >> 1;
	अचिन्हित पूर्णांक chan, range, aref;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक hi, lo;
	अचिन्हित पूर्णांक dither;

	अगर (devpriv->is_m_series) अणु
		ni_m_series_load_channelgain_list(dev, n_chan, list);
		वापस;
	पूर्ण
	अगर (n_chan == 1 && !devpriv->is_611x && !devpriv->is_6143) अणु
		अगर (devpriv->changain_state &&
		    devpriv->changain_spec == list[0]) अणु
			/*  पढ़ोy to go. */
			वापस;
		पूर्ण
		devpriv->changain_state = 1;
		devpriv->changain_spec = list[0];
	पूर्ण अन्यथा अणु
		devpriv->changain_state = 0;
	पूर्ण

	ni_stc_ग_लिखोw(dev, 1, NISTC_CFG_MEM_CLR_REG);

	/*  Set up Calibration mode अगर required */
	अगर (devpriv->is_6143) अणु
		अगर ((list[0] & CR_ALT_SOURCE) &&
		    !devpriv->ai_calib_source_enabled) अणु
			/*  Strobe Relay enable bit */
			ni_ग_लिखोw(dev, devpriv->ai_calib_source |
				       NI6143_CALIB_CHAN_RELAY_ON,
				  NI6143_CALIB_CHAN_REG);
			ni_ग_लिखोw(dev, devpriv->ai_calib_source,
				  NI6143_CALIB_CHAN_REG);
			devpriv->ai_calib_source_enabled = 1;
			/* Allow relays to change */
			msleep_पूर्णांकerruptible(100);
		पूर्ण अन्यथा अगर (!(list[0] & CR_ALT_SOURCE) &&
			   devpriv->ai_calib_source_enabled) अणु
			/*  Strobe Relay disable bit */
			ni_ग_लिखोw(dev, devpriv->ai_calib_source |
				       NI6143_CALIB_CHAN_RELAY_OFF,
				  NI6143_CALIB_CHAN_REG);
			ni_ग_लिखोw(dev, devpriv->ai_calib_source,
				  NI6143_CALIB_CHAN_REG);
			devpriv->ai_calib_source_enabled = 0;
			/* Allow relays to change */
			msleep_पूर्णांकerruptible(100);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < n_chan; i++) अणु
		अगर (!devpriv->is_6143 && (list[i] & CR_ALT_SOURCE))
			chan = devpriv->ai_calib_source;
		अन्यथा
			chan = CR_CHAN(list[i]);
		aref = CR_AREF(list[i]);
		range = CR_RANGE(list[i]);
		dither = (list[i] & CR_ALT_FILTER) != 0;

		/* fix the बाह्यal/पूर्णांकernal range dअगरferences */
		range = ni_gainlkup[board->gainlkup][range];
		अगर (devpriv->is_611x)
			devpriv->ai_offset[i] = offset;
		अन्यथा
			devpriv->ai_offset[i] = (range & 0x100) ? 0 : offset;

		hi = 0;
		अगर ((list[i] & CR_ALT_SOURCE)) अणु
			अगर (devpriv->is_611x)
				ni_ग_लिखोw(dev, CR_CHAN(list[i]) & 0x0003,
					  NI611X_CALIB_CHAN_SEL_REG);
		पूर्ण अन्यथा अणु
			अगर (devpriv->is_611x)
				aref = AREF_DIFF;
			अन्यथा अगर (devpriv->is_6143)
				aref = AREF_OTHER;
			चयन (aref) अणु
			हाल AREF_DIFF:
				hi |= NI_E_AI_CFG_HI_TYPE_DIFF;
				अवरोध;
			हाल AREF_COMMON:
				hi |= NI_E_AI_CFG_HI_TYPE_COMMON;
				अवरोध;
			हाल AREF_GROUND:
				hi |= NI_E_AI_CFG_HI_TYPE_GROUND;
				अवरोध;
			हाल AREF_OTHER:
				अवरोध;
			पूर्ण
		पूर्ण
		hi |= NI_E_AI_CFG_HI_CHAN(chan);

		ni_ग_लिखोw(dev, hi, NI_E_AI_CFG_HI_REG);

		अगर (!devpriv->is_6143) अणु
			lo = NI_E_AI_CFG_LO_GAIN(range);

			अगर (i == n_chan - 1)
				lo |= NI_E_AI_CFG_LO_LAST_CHAN;
			अगर (dither)
				lo |= NI_E_AI_CFG_LO_DITHER;

			ni_ग_लिखोw(dev, lo, NI_E_AI_CFG_LO_REG);
		पूर्ण
	पूर्ण

	/* prime the channel/gain list */
	अगर (!devpriv->is_611x && !devpriv->is_6143)
		ni_prime_channelgain_list(dev);
पूर्ण

अटल पूर्णांक ni_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn,
			   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक mask = s->maxdata;
	पूर्णांक i, n;
	अचिन्हित पूर्णांक signbits;
	अचिन्हित पूर्णांक d;

	ni_load_channelgain_list(dev, s, 1, &insn->chanspec);

	ni_clear_ai_fअगरo(dev);

	signbits = devpriv->ai_offset[0];
	अगर (devpriv->is_611x) अणु
		क्रम (n = 0; n < num_adc_stages_611x; n++) अणु
			ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);
			udelay(1);
		पूर्ण
		क्रम (n = 0; n < insn->n; n++) अणु
			ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);
			/* The 611x has screwy 32-bit FIFOs. */
			d = 0;
			क्रम (i = 0; i < NI_TIMEOUT; i++) अणु
				अगर (ni_पढ़ोb(dev, NI_E_STATUS_REG) & 0x80) अणु
					d = ni_पढ़ोl(dev,
						     NI611X_AI_FIFO_DATA_REG);
					d >>= 16;
					d &= 0xffff;
					अवरोध;
				पूर्ण
				अगर (!(ni_stc_पढ़ोw(dev, NISTC_AI_STATUS1_REG) &
				      NISTC_AI_STATUS1_FIFO_E)) अणु
					d = ni_पढ़ोl(dev,
						     NI611X_AI_FIFO_DATA_REG);
					d &= 0xffff;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (i == NI_TIMEOUT) अणु
				dev_err(dev->class_dev, "timeout\n");
				वापस -ETIME;
			पूर्ण
			d += signbits;
			data[n] = d & 0xffff;
		पूर्ण
	पूर्ण अन्यथा अगर (devpriv->is_6143) अणु
		क्रम (n = 0; n < insn->n; n++) अणु
			ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);

			/*
			 * The 6143 has 32-bit FIFOs. You need to strobe a
			 * bit to move a single 16bit stअक्रमed sample पूर्णांकo
			 * the FIFO.
			 */
			d = 0;
			क्रम (i = 0; i < NI_TIMEOUT; i++) अणु
				अगर (ni_पढ़ोl(dev, NI6143_AI_FIFO_STATUS_REG) &
				    0x01) अणु
					/* Get stअक्रमed sample पूर्णांकo FIFO */
					ni_ग_लिखोl(dev, 0x01,
						  NI6143_AI_FIFO_CTRL_REG);
					d = ni_पढ़ोl(dev,
						     NI6143_AI_FIFO_DATA_REG);
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (i == NI_TIMEOUT) अणु
				dev_err(dev->class_dev, "timeout\n");
				वापस -ETIME;
			पूर्ण
			data[n] = (((d >> 16) & 0xFFFF) + signbits) & 0xFFFF;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (n = 0; n < insn->n; n++) अणु
			ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_CONVERT_PULSE,
				      NISTC_AI_CMD1_REG);
			क्रम (i = 0; i < NI_TIMEOUT; i++) अणु
				अगर (!(ni_stc_पढ़ोw(dev, NISTC_AI_STATUS1_REG) &
				      NISTC_AI_STATUS1_FIFO_E))
					अवरोध;
			पूर्ण
			अगर (i == NI_TIMEOUT) अणु
				dev_err(dev->class_dev, "timeout\n");
				वापस -ETIME;
			पूर्ण
			अगर (devpriv->is_m_series) अणु
				d = ni_पढ़ोl(dev, NI_M_AI_FIFO_DATA_REG);
				d &= mask;
				data[n] = d;
			पूर्ण अन्यथा अणु
				d = ni_पढ़ोw(dev, NI_E_AI_FIFO_DATA_REG);
				d += signbits;
				data[n] = d & 0xffff;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_ns_to_समयr(स्थिर काष्ठा comedi_device *dev,
			  अचिन्हित पूर्णांक nanosec, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक भागider;

	चयन (flags & CMDF_ROUND_MASK) अणु
	हाल CMDF_ROUND_NEAREST:
	शेष:
		भागider = DIV_ROUND_CLOSEST(nanosec, devpriv->घड़ी_ns);
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		भागider = (nanosec) / devpriv->घड़ी_ns;
		अवरोध;
	हाल CMDF_ROUND_UP:
		भागider = DIV_ROUND_UP(nanosec, devpriv->घड़ी_ns);
		अवरोध;
	पूर्ण
	वापस भागider - 1;
पूर्ण

अटल अचिन्हित पूर्णांक ni_समयr_to_ns(स्थिर काष्ठा comedi_device *dev, पूर्णांक समयr)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	वापस devpriv->घड़ी_ns * (समयr + 1);
पूर्ण

अटल व्योम ni_cmd_set_mite_transfer(काष्ठा mite_ring *ring,
				     काष्ठा comedi_subdevice *sdev,
				     स्थिर काष्ठा comedi_cmd *cmd,
				     अचिन्हित पूर्णांक max_count)
अणु
#अगर_घोषित PCIDMA
	अचिन्हित पूर्णांक nbytes = max_count;

	अगर (cmd->stop_arg > 0 && cmd->stop_arg < max_count)
		nbytes = cmd->stop_arg;
	nbytes *= comedi_bytes_per_scan(sdev);

	अगर (nbytes > sdev->async->pपुनः_स्मृति_bufsz) अणु
		अगर (cmd->stop_arg > 0)
			dev_err(sdev->device->class_dev,
				"%s: tried exact data transfer limits greater than buffer size\n",
				__func__);

		/*
		 * we can only transfer up to the size of the buffer.  In this
		 * हाल, the user is expected to जारी to ग_लिखो पूर्णांकo the
		 * comedi buffer (alपढ़ोy implemented as a ring buffer).
		 */
		nbytes = sdev->async->pपुनः_स्मृति_bufsz;
	पूर्ण

	mite_init_ring_descriptors(ring, sdev, nbytes);
#अन्यथा
	dev_err(sdev->device->class_dev,
		"%s: exact data transfer limits not implemented yet without DMA\n",
		__func__);
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित पूर्णांक ni_min_ai_scan_period_ns(काष्ठा comedi_device *dev,
					     अचिन्हित पूर्णांक num_channels)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;

	/* simultaneously-sampled inमाला_दो */
	अगर (devpriv->is_611x || devpriv->is_6143)
		वापस board->ai_speed;

	/* multiplexed inमाला_दो */
	वापस board->ai_speed * num_channels;
पूर्ण

अटल पूर्णांक ni_ai_cmdtest(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक sources;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src,
					TRIG_NOW | TRIG_INT | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_EXT);

	sources = TRIG_TIMER | TRIG_EXT;
	अगर (devpriv->is_611x || devpriv->is_6143)
		sources |= TRIG_NOW;
	err |= comedi_check_trigger_src(&cmd->convert_src, sources);

	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	चयन (cmd->start_src) अणु
	हाल TRIG_NOW:
	हाल TRIG_INT:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		अवरोध;
	हाल TRIG_EXT:
		err |= ni_check_trigger_arg_roffs(CR_CHAN(cmd->start_arg),
						  NI_AI_StartTrigger,
						  &devpriv->routing_tables, 1);
		अवरोध;
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
			ni_min_ai_scan_period_ns(dev, cmd->chanlist_len));
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
						    devpriv->घड़ी_ns *
						    0xffffff);
	पूर्ण अन्यथा अगर (cmd->scan_begin_src == TRIG_EXT) अणु
		/* बाह्यal trigger */
		err |= ni_check_trigger_arg_roffs(CR_CHAN(cmd->scan_begin_arg),
						  NI_AI_SampleClock,
						  &devpriv->routing_tables, 1);
	पूर्ण अन्यथा अणु		/* TRIG_OTHER */
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	पूर्ण

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अगर (devpriv->is_611x || devpriv->is_6143) अणु
			err |= comedi_check_trigger_arg_is(&cmd->convert_arg,
							   0);
		पूर्ण अन्यथा अणु
			err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
							    board->ai_speed);
			err |= comedi_check_trigger_arg_max(&cmd->convert_arg,
							    devpriv->घड़ी_ns *
							    0xffff);
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->convert_src == TRIG_EXT) अणु
		/* बाह्यal trigger */
		err |= ni_check_trigger_arg_roffs(CR_CHAN(cmd->convert_arg),
						  NI_AI_ConvertClock,
						  &devpriv->routing_tables, 1);
	पूर्ण अन्यथा अगर (cmd->convert_src == TRIG_NOW) अणु
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT) अणु
		अचिन्हित पूर्णांक max_count = 0x01000000;

		अगर (devpriv->is_611x)
			max_count -= num_adc_stages_611x;
		err |= comedi_check_trigger_arg_max(&cmd->stop_arg, max_count);
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	पूर्ण अन्यथा अणु
		/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);
	पूर्ण

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		अचिन्हित पूर्णांक पंचांगp = cmd->scan_begin_arg;

		cmd->scan_begin_arg =
		    ni_समयr_to_ns(dev, ni_ns_to_समयr(dev,
						       cmd->scan_begin_arg,
						       cmd->flags));
		अगर (पंचांगp != cmd->scan_begin_arg)
			err++;
	पूर्ण
	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अगर (!devpriv->is_611x && !devpriv->is_6143) अणु
			अचिन्हित पूर्णांक पंचांगp = cmd->convert_arg;

			cmd->convert_arg =
			    ni_समयr_to_ns(dev, ni_ns_to_समयr(dev,
							       cmd->convert_arg,
							       cmd->flags));
			अगर (पंचांगp != cmd->convert_arg)
				err++;
			अगर (cmd->scan_begin_src == TRIG_TIMER &&
			    cmd->scan_begin_arg <
			    cmd->convert_arg * cmd->scan_end_arg) अणु
				cmd->scan_begin_arg =
				    cmd->convert_arg * cmd->scan_end_arg;
				err++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक ni_ai_पूर्णांकtrig(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	ni_stc_ग_लिखोw(dev, NISTC_AI_CMD2_START1_PULSE | devpriv->ai_cmd2,
		      NISTC_AI_CMD2_REG);
	s->async->पूर्णांकtrig = शून्य;

	वापस 1;
पूर्ण

अटल पूर्णांक ni_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	स्थिर काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक समयr;
	पूर्णांक mode1 = 0;		/* mode1 is needed क्रम both stop and convert */
	पूर्णांक mode2 = 0;
	पूर्णांक start_stop_select = 0;
	अचिन्हित पूर्णांक stop_count;
	पूर्णांक पूर्णांकerrupt_a_enable = 0;
	अचिन्हित पूर्णांक ai_trig;

	अगर (dev->irq == 0) अणु
		dev_err(dev->class_dev, "cannot run command without an irq\n");
		वापस -EIO;
	पूर्ण
	ni_clear_ai_fअगरo(dev);

	ni_load_channelgain_list(dev, s, cmd->chanlist_len, cmd->chanlist);

	/* start configuration */
	ni_stc_ग_लिखोw(dev, NISTC_RESET_AI_CFG_START, NISTC_RESET_REG);

	/*
	 * Disable analog triggering क्रम now, since it पूर्णांकerferes
	 * with the use of pfi0.
	 */
	devpriv->an_trig_etc_reg &= ~NISTC_ATRIG_ETC_ENA;
	ni_stc_ग_लिखोw(dev, devpriv->an_trig_etc_reg, NISTC_ATRIG_ETC_REG);

	ai_trig = NISTC_AI_TRIG_START2_SEL(0) | NISTC_AI_TRIG_START1_SYNC;
	चयन (cmd->start_src) अणु
	हाल TRIG_INT:
	हाल TRIG_NOW:
		ai_trig |= NISTC_AI_TRIG_START1_EDGE |
			   NISTC_AI_TRIG_START1_SEL(0);
		अवरोध;
	हाल TRIG_EXT:
		ai_trig |= NISTC_AI_TRIG_START1_SEL(
				ni_get_reg_value_roffs(
					CR_CHAN(cmd->start_arg),
					NI_AI_StartTrigger,
					&devpriv->routing_tables, 1));

		अगर (cmd->start_arg & CR_INVERT)
			ai_trig |= NISTC_AI_TRIG_START1_POLARITY;
		अगर (cmd->start_arg & CR_EDGE)
			ai_trig |= NISTC_AI_TRIG_START1_EDGE;
		अवरोध;
	पूर्ण
	ni_stc_ग_लिखोw(dev, ai_trig, NISTC_AI_TRIG_SEL_REG);

	mode2 &= ~NISTC_AI_MODE2_PRE_TRIGGER;
	mode2 &= ~NISTC_AI_MODE2_SC_INIT_LOAD_SRC;
	mode2 &= ~NISTC_AI_MODE2_SC_RELOAD_MODE;
	ni_stc_ग_लिखोw(dev, mode2, NISTC_AI_MODE2_REG);

	अगर (cmd->chanlist_len == 1 || devpriv->is_611x || devpriv->is_6143) अणु
		/* logic low */
		start_stop_select |= NISTC_AI_STOP_POLARITY |
				     NISTC_AI_STOP_SEL(31) |
				     NISTC_AI_STOP_SYNC;
	पूर्ण अन्यथा अणु
		/*  ai configuration memory */
		start_stop_select |= NISTC_AI_STOP_SEL(19);
	पूर्ण
	ni_stc_ग_लिखोw(dev, start_stop_select, NISTC_AI_START_STOP_REG);

	devpriv->ai_cmd2 = 0;
	चयन (cmd->stop_src) अणु
	हाल TRIG_COUNT:
		stop_count = cmd->stop_arg - 1;

		अगर (devpriv->is_611x) अणु
			/*  have to take 3 stage adc pipeline पूर्णांकo account */
			stop_count += num_adc_stages_611x;
		पूर्ण
		/* stage number of scans */
		ni_stc_ग_लिखोl(dev, stop_count, NISTC_AI_SC_LOADA_REG);

		mode1 |= NISTC_AI_MODE1_START_STOP |
			 NISTC_AI_MODE1_RSVD |
			 NISTC_AI_MODE1_TRIGGER_ONCE;
		ni_stc_ग_लिखोw(dev, mode1, NISTC_AI_MODE1_REG);
		/* load SC (Scan Count) */
		ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_SC_LOAD, NISTC_AI_CMD1_REG);

		अगर (stop_count == 0) अणु
			devpriv->ai_cmd2 |= NISTC_AI_CMD2_END_ON_EOS;
			पूर्णांकerrupt_a_enable |= NISTC_INTA_ENA_AI_STOP;
			/*
			 * This is required to get the last sample क्रम
			 * chanlist_len > 1, not sure why.
			 */
			अगर (cmd->chanlist_len > 1)
				start_stop_select |= NISTC_AI_STOP_POLARITY |
						     NISTC_AI_STOP_EDGE;
		पूर्ण
		अवरोध;
	हाल TRIG_NONE:
		/* stage number of scans */
		ni_stc_ग_लिखोl(dev, 0, NISTC_AI_SC_LOADA_REG);

		mode1 |= NISTC_AI_MODE1_START_STOP |
			 NISTC_AI_MODE1_RSVD |
			 NISTC_AI_MODE1_CONTINUOUS;
		ni_stc_ग_लिखोw(dev, mode1, NISTC_AI_MODE1_REG);

		/* load SC (Scan Count) */
		ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_SC_LOAD, NISTC_AI_CMD1_REG);
		अवरोध;
	पूर्ण

	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_TIMER:
		/*
		 * stop bits क्रम non 611x boards
		 * NISTC_AI_MODE3_SI_TRIG_DELAY=0
		 * NISTC_AI_MODE2_PRE_TRIGGER=0
		 * NISTC_AI_START_STOP_REG:
		 * NISTC_AI_START_POLARITY=0	(?) rising edge
		 * NISTC_AI_START_EDGE=1	edge triggered
		 * NISTC_AI_START_SYNC=1	(?)
		 * NISTC_AI_START_SEL=0		SI_TC
		 * NISTC_AI_STOP_POLARITY=0	rising edge
		 * NISTC_AI_STOP_EDGE=0		level
		 * NISTC_AI_STOP_SYNC=1
		 * NISTC_AI_STOP_SEL=19		बाह्यal pin (configuration mem)
		 */
		start_stop_select |= NISTC_AI_START_EDGE | NISTC_AI_START_SYNC;
		ni_stc_ग_लिखोw(dev, start_stop_select, NISTC_AI_START_STOP_REG);

		mode2 &= ~NISTC_AI_MODE2_SI_INIT_LOAD_SRC;	/* A */
		mode2 |= NISTC_AI_MODE2_SI_RELOAD_MODE(0);
		/* mode2 |= NISTC_AI_MODE2_SC_RELOAD_MODE; */
		ni_stc_ग_लिखोw(dev, mode2, NISTC_AI_MODE2_REG);

		/* load SI */
		समयr = ni_ns_to_समयr(dev, cmd->scan_begin_arg,
				       CMDF_ROUND_NEAREST);
		ni_stc_ग_लिखोl(dev, समयr, NISTC_AI_SI_LOADA_REG);
		ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_SI_LOAD, NISTC_AI_CMD1_REG);
		अवरोध;
	हाल TRIG_EXT:
		अगर (cmd->scan_begin_arg & CR_EDGE)
			start_stop_select |= NISTC_AI_START_EDGE;
		अगर (cmd->scan_begin_arg & CR_INVERT)	/* falling edge */
			start_stop_select |= NISTC_AI_START_POLARITY;
		अगर (cmd->scan_begin_src != cmd->convert_src ||
		    (cmd->scan_begin_arg & ~CR_EDGE) !=
		    (cmd->convert_arg & ~CR_EDGE))
			start_stop_select |= NISTC_AI_START_SYNC;

		start_stop_select |= NISTC_AI_START_SEL(
					ni_get_reg_value_roffs(
						CR_CHAN(cmd->scan_begin_arg),
						NI_AI_SampleClock,
						&devpriv->routing_tables, 1));
		ni_stc_ग_लिखोw(dev, start_stop_select, NISTC_AI_START_STOP_REG);
		अवरोध;
	पूर्ण

	चयन (cmd->convert_src) अणु
	हाल TRIG_TIMER:
	हाल TRIG_NOW:
		अगर (cmd->convert_arg == 0 || cmd->convert_src == TRIG_NOW)
			समयr = 1;
		अन्यथा
			समयr = ni_ns_to_समयr(dev, cmd->convert_arg,
					       CMDF_ROUND_NEAREST);
		/* 0,0 करोes not work */
		ni_stc_ग_लिखोw(dev, 1, NISTC_AI_SI2_LOADA_REG);
		ni_stc_ग_लिखोw(dev, समयr, NISTC_AI_SI2_LOADB_REG);

		mode2 &= ~NISTC_AI_MODE2_SI2_INIT_LOAD_SRC;	/* A */
		mode2 |= NISTC_AI_MODE2_SI2_RELOAD_MODE;	/* alternate */
		ni_stc_ग_लिखोw(dev, mode2, NISTC_AI_MODE2_REG);

		ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_SI2_LOAD, NISTC_AI_CMD1_REG);

		mode2 |= NISTC_AI_MODE2_SI2_INIT_LOAD_SRC;	/* B */
		mode2 |= NISTC_AI_MODE2_SI2_RELOAD_MODE;	/* alternate */
		ni_stc_ग_लिखोw(dev, mode2, NISTC_AI_MODE2_REG);
		अवरोध;
	हाल TRIG_EXT:
		mode1 |= NISTC_AI_MODE1_CONVERT_SRC(
				ni_get_reg_value_roffs(
						CR_CHAN(cmd->convert_arg),
						NI_AI_ConvertClock,
						&devpriv->routing_tables, 1));
		अगर ((cmd->convert_arg & CR_INVERT) == 0)
			mode1 |= NISTC_AI_MODE1_CONVERT_POLARITY;
		ni_stc_ग_लिखोw(dev, mode1, NISTC_AI_MODE1_REG);

		mode2 |= NISTC_AI_MODE2_SC_GATE_ENA |
			 NISTC_AI_MODE2_START_STOP_GATE_ENA;
		ni_stc_ग_लिखोw(dev, mode2, NISTC_AI_MODE2_REG);

		अवरोध;
	पूर्ण

	अगर (dev->irq) अणु
		/* पूर्णांकerrupt on FIFO, errors, SC_TC */
		पूर्णांकerrupt_a_enable |= NISTC_INTA_ENA_AI_ERR |
				      NISTC_INTA_ENA_AI_SC_TC;

#अगर_अघोषित PCIDMA
		पूर्णांकerrupt_a_enable |= NISTC_INTA_ENA_AI_FIFO;
#पूर्ण_अगर

		अगर ((cmd->flags & CMDF_WAKE_EOS) ||
		    (devpriv->ai_cmd2 & NISTC_AI_CMD2_END_ON_EOS)) अणु
			/* wake on end-of-scan */
			devpriv->aimode = AIMODE_SCAN;
		पूर्ण अन्यथा अणु
			devpriv->aimode = AIMODE_HALF_FULL;
		पूर्ण

		चयन (devpriv->aimode) अणु
		हाल AIMODE_HALF_FULL:
			/* FIFO पूर्णांकerrupts and DMA requests on half-full */
#अगर_घोषित PCIDMA
			ni_stc_ग_लिखोw(dev, NISTC_AI_MODE3_FIFO_MODE_HF_E,
				      NISTC_AI_MODE3_REG);
#अन्यथा
			ni_stc_ग_लिखोw(dev, NISTC_AI_MODE3_FIFO_MODE_HF,
				      NISTC_AI_MODE3_REG);
#पूर्ण_अगर
			अवरोध;
		हाल AIMODE_SAMPLE:
			/* generate FIFO पूर्णांकerrupts on non-empty */
			ni_stc_ग_लिखोw(dev, NISTC_AI_MODE3_FIFO_MODE_NE,
				      NISTC_AI_MODE3_REG);
			अवरोध;
		हाल AIMODE_SCAN:
#अगर_घोषित PCIDMA
			ni_stc_ग_लिखोw(dev, NISTC_AI_MODE3_FIFO_MODE_NE,
				      NISTC_AI_MODE3_REG);
#अन्यथा
			ni_stc_ग_लिखोw(dev, NISTC_AI_MODE3_FIFO_MODE_HF,
				      NISTC_AI_MODE3_REG);
#पूर्ण_अगर
			पूर्णांकerrupt_a_enable |= NISTC_INTA_ENA_AI_STOP;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* clear पूर्णांकerrupts */
		ni_stc_ग_लिखोw(dev, NISTC_INTA_ACK_AI_ALL, NISTC_INTA_ACK_REG);

		ni_set_bits(dev, NISTC_INTA_ENA_REG, पूर्णांकerrupt_a_enable, 1);
	पूर्ण अन्यथा अणु
		/* पूर्णांकerrupt on nothing */
		ni_set_bits(dev, NISTC_INTA_ENA_REG, ~0, 0);

		/* XXX start polling अगर necessary */
	पूर्ण

	/* end configuration */
	ni_stc_ग_लिखोw(dev, NISTC_RESET_AI_CFG_END, NISTC_RESET_REG);

	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_TIMER:
		ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_SI2_ARM |
				   NISTC_AI_CMD1_SI_ARM |
				   NISTC_AI_CMD1_DIV_ARM |
				   NISTC_AI_CMD1_SC_ARM,
			      NISTC_AI_CMD1_REG);
		अवरोध;
	हाल TRIG_EXT:
		ni_stc_ग_लिखोw(dev, NISTC_AI_CMD1_SI2_ARM |
				   NISTC_AI_CMD1_SI_ARM |	/* XXX ? */
				   NISTC_AI_CMD1_DIV_ARM |
				   NISTC_AI_CMD1_SC_ARM,
			      NISTC_AI_CMD1_REG);
		अवरोध;
	पूर्ण

#अगर_घोषित PCIDMA
	अणु
		पूर्णांक retval = ni_ai_setup_MITE_dma(dev);

		अगर (retval)
			वापस retval;
	पूर्ण
#पूर्ण_अगर

	अगर (cmd->start_src == TRIG_NOW) अणु
		ni_stc_ग_लिखोw(dev, NISTC_AI_CMD2_START1_PULSE |
				   devpriv->ai_cmd2,
			      NISTC_AI_CMD2_REG);
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_EXT) अणु
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अणु	/* TRIG_INT */
		s->async->पूर्णांकtrig = ni_ai_पूर्णांकtrig;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ni_ai_insn_config(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (insn->n < 1)
		वापस -EINVAL;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_ALT_SOURCE:
		अगर (devpriv->is_m_series) अणु
			अगर (data[1] & ~NI_M_CFG_BYPASS_AI_CAL_MASK)
				वापस -EINVAL;
			devpriv->ai_calib_source = data[1];
		पूर्ण अन्यथा अगर (devpriv->is_6143) अणु
			अचिन्हित पूर्णांक calib_source;

			calib_source = data[1] & 0xf;

			devpriv->ai_calib_source = calib_source;
			ni_ग_लिखोw(dev, calib_source, NI6143_CALIB_CHAN_REG);
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक calib_source;
			अचिन्हित पूर्णांक calib_source_adjust;

			calib_source = data[1] & 0xf;
			calib_source_adjust = (data[1] >> 4) & 0xff;

			अगर (calib_source >= 8)
				वापस -EINVAL;
			devpriv->ai_calib_source = calib_source;
			अगर (devpriv->is_611x) अणु
				ni_ग_लिखोb(dev, calib_source_adjust,
					  NI611X_CAL_GAIN_SEL_REG);
			पूर्ण
		पूर्ण
		वापस 2;
	हाल INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS:
		/* we करोn't care about actual channels */
		/* data[3] : chanlist_len */
		data[1] = ni_min_ai_scan_period_ns(dev, data[3]);
		अगर (devpriv->is_611x || devpriv->is_6143)
			data[2] = 0; /* simultaneous output */
		अन्यथा
			data[2] = board->ai_speed;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम ni_ao_munge(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			व्योम *data, अचिन्हित पूर्णांक num_bytes,
			अचिन्हित पूर्णांक chan_index)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक nsamples = comedi_bytes_to_samples(s, num_bytes);
	अचिन्हित लघु *array = data;
	अचिन्हित पूर्णांक i;
#अगर_घोषित PCIDMA
	__le16 buf, *barray = data;
#पूर्ण_अगर

	क्रम (i = 0; i < nsamples; i++) अणु
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[chan_index]);
		अचिन्हित लघु val = array[i];

		/*
		 * Munge data from अचिन्हित to two's complement क्रम
		 * bipolar ranges.
		 */
		अगर (comedi_range_is_bipolar(s, range))
			val = comedi_offset_munge(s, val);
#अगर_घोषित PCIDMA
		buf = cpu_to_le16(val);
		barray[i] = buf;
#अन्यथा
		array[i] = val;
#पूर्ण_अगर
		chan_index++;
		chan_index %= cmd->chanlist_len;
	पूर्ण
पूर्ण

अटल पूर्णांक ni_m_series_ao_config_chanlist(काष्ठा comedi_device *dev,
					  काष्ठा comedi_subdevice *s,
					  अचिन्हित पूर्णांक chanspec[],
					  अचिन्हित पूर्णांक n_chans, पूर्णांक समयd)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक range;
	अचिन्हित पूर्णांक chan;
	अचिन्हित पूर्णांक conf;
	पूर्णांक i;
	पूर्णांक invert = 0;

	अगर (समयd) अणु
		क्रम (i = 0; i < s->n_chan; ++i) अणु
			devpriv->ao_conf[i] &= ~NI_M_AO_CFG_BANK_UPDATE_TIMED;
			ni_ग_लिखोb(dev, devpriv->ao_conf[i],
				  NI_M_AO_CFG_BANK_REG(i));
			ni_ग_लिखोb(dev, 0xf, NI_M_AO_WAVEFORM_ORDER_REG(i));
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < n_chans; i++) अणु
		स्थिर काष्ठा comedi_krange *krange;

		chan = CR_CHAN(chanspec[i]);
		range = CR_RANGE(chanspec[i]);
		krange = s->range_table->range + range;
		invert = 0;
		conf = 0;
		चयन (krange->max - krange->min) अणु
		हाल 20000000:
			conf |= NI_M_AO_CFG_BANK_REF_INT_10V;
			ni_ग_लिखोb(dev, 0, NI_M_AO_REF_ATTENUATION_REG(chan));
			अवरोध;
		हाल 10000000:
			conf |= NI_M_AO_CFG_BANK_REF_INT_5V;
			ni_ग_लिखोb(dev, 0, NI_M_AO_REF_ATTENUATION_REG(chan));
			अवरोध;
		हाल 4000000:
			conf |= NI_M_AO_CFG_BANK_REF_INT_10V;
			ni_ग_लिखोb(dev, NI_M_AO_REF_ATTENUATION_X5,
				  NI_M_AO_REF_ATTENUATION_REG(chan));
			अवरोध;
		हाल 2000000:
			conf |= NI_M_AO_CFG_BANK_REF_INT_5V;
			ni_ग_लिखोb(dev, NI_M_AO_REF_ATTENUATION_X5,
				  NI_M_AO_REF_ATTENUATION_REG(chan));
			अवरोध;
		शेष:
			dev_err(dev->class_dev,
				"bug! unhandled ao reference voltage\n");
			अवरोध;
		पूर्ण
		चयन (krange->max + krange->min) अणु
		हाल 0:
			conf |= NI_M_AO_CFG_BANK_OFFSET_0V;
			अवरोध;
		हाल 10000000:
			conf |= NI_M_AO_CFG_BANK_OFFSET_5V;
			अवरोध;
		शेष:
			dev_err(dev->class_dev,
				"bug! unhandled ao offset voltage\n");
			अवरोध;
		पूर्ण
		अगर (समयd)
			conf |= NI_M_AO_CFG_BANK_UPDATE_TIMED;
		ni_ग_लिखोb(dev, conf, NI_M_AO_CFG_BANK_REG(chan));
		devpriv->ao_conf[chan] = conf;
		ni_ग_लिखोb(dev, i, NI_M_AO_WAVEFORM_ORDER_REG(chan));
	पूर्ण
	वापस invert;
पूर्ण

अटल पूर्णांक ni_old_ao_config_chanlist(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक chanspec[],
				     अचिन्हित पूर्णांक n_chans)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक range;
	अचिन्हित पूर्णांक chan;
	अचिन्हित पूर्णांक conf;
	पूर्णांक i;
	पूर्णांक invert = 0;

	क्रम (i = 0; i < n_chans; i++) अणु
		chan = CR_CHAN(chanspec[i]);
		range = CR_RANGE(chanspec[i]);
		conf = NI_E_AO_DACSEL(chan);

		अगर (comedi_range_is_bipolar(s, range)) अणु
			conf |= NI_E_AO_CFG_BIP;
			invert = (s->maxdata + 1) >> 1;
		पूर्ण अन्यथा अणु
			invert = 0;
		पूर्ण
		अगर (comedi_range_is_बाह्यal(s, range))
			conf |= NI_E_AO_EXT_REF;

		/* not all boards can deglitch, but this shouldn't hurt */
		अगर (chanspec[i] & CR_DEGLITCH)
			conf |= NI_E_AO_DEGLITCH;

		/* analog reference */
		/* AREF_OTHER connects AO ground to AI ground, i think */
		अगर (CR_AREF(chanspec[i]) == AREF_OTHER)
			conf |= NI_E_AO_GROUND_REF;

		ni_ग_लिखोw(dev, conf, NI_E_AO_CFG_REG);
		devpriv->ao_conf[chan] = conf;
	पूर्ण
	वापस invert;
पूर्ण

अटल पूर्णांक ni_ao_config_chanlist(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 अचिन्हित पूर्णांक chanspec[], अचिन्हित पूर्णांक n_chans,
				 पूर्णांक समयd)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (devpriv->is_m_series)
		वापस ni_m_series_ao_config_chanlist(dev, s, chanspec, n_chans,
						      समयd);
	अन्यथा
		वापस ni_old_ao_config_chanlist(dev, s, chanspec, n_chans);
पूर्ण

अटल पूर्णांक ni_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s,
			    काष्ठा comedi_insn *insn,
			    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	पूर्णांक reg;
	पूर्णांक i;

	अगर (devpriv->is_6xxx) अणु
		ni_ao_win_outw(dev, 1 << chan, NI671X_AO_IMMEDIATE_REG);

		reg = NI671X_DAC_सूचीECT_DATA_REG(chan);
	पूर्ण अन्यथा अगर (devpriv->is_m_series) अणु
		reg = NI_M_DAC_सूचीECT_DATA_REG(chan);
	पूर्ण अन्यथा अणु
		reg = NI_E_DAC_सूचीECT_DATA_REG(chan);
	पूर्ण

	ni_ao_config_chanlist(dev, s, &insn->chanspec, 1, 0);

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		s->पढ़ोback[chan] = val;

		अगर (devpriv->is_6xxx) अणु
			/*
			 * 6xxx boards have bipolar outमाला_दो, munge the
			 * अचिन्हित comedi values to 2's complement
			 */
			val = comedi_offset_munge(s, val);

			ni_ao_win_outw(dev, val, reg);
		पूर्ण अन्यथा अगर (devpriv->is_m_series) अणु
			/*
			 * M-series boards use offset binary values क्रम
			 * bipolar and uinpolar outमाला_दो
			 */
			ni_ग_लिखोw(dev, val, reg);
		पूर्ण अन्यथा अणु
			/*
			 * Non-M series boards need two's complement values
			 * क्रम bipolar ranges.
			 */
			अगर (comedi_range_is_bipolar(s, range))
				val = comedi_offset_munge(s, val);

			ni_ग_लिखोw(dev, val, reg);
		पूर्ण
	पूर्ण

	वापस insn->n;
पूर्ण

/*
 * Arms the AO device in preparation क्रम a trigger event.
 * This function also allocates and prepares a DMA channel (or FIFO अगर DMA is
 * not used).  As a part of this preparation, this function preloads the DAC
 * रेजिस्टरs with the first values of the output stream.  This ensures that the
 * first घड़ी cycle after the trigger can be used क्रम output.
 *
 * Note that this function _must_ happen after a user has written data to the
 * output buffers via either mmap or ग_लिखो(fileno,...).
 */
अटल पूर्णांक ni_ao_arm(काष्ठा comedi_device *dev,
		     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक ret;
	पूर्णांक पूर्णांकerrupt_b_bits;
	पूर्णांक i;
	अटल स्थिर पूर्णांक समयout = 1000;

	/*
	 * Prevent ao from करोing things like trying to allocate the ao dma
	 * channel multiple बार.
	 */
	अगर (!devpriv->ao_needs_arming) अणु
		dev_dbg(dev->class_dev, "%s: device does not need arming!\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	devpriv->ao_needs_arming = 0;

	ni_set_bits(dev, NISTC_INTB_ENA_REG,
		    NISTC_INTB_ENA_AO_FIFO | NISTC_INTB_ENA_AO_ERR, 0);
	पूर्णांकerrupt_b_bits = NISTC_INTB_ENA_AO_ERR;
#अगर_घोषित PCIDMA
	ni_stc_ग_लिखोw(dev, 1, NISTC_DAC_FIFO_CLR_REG);
	अगर (devpriv->is_6xxx)
		ni_ao_win_outl(dev, 0x6, NI611X_AO_FIFO_OFFSET_LOAD_REG);
	ret = ni_ao_setup_MITE_dma(dev);
	अगर (ret)
		वापस ret;
	ret = ni_ao_रुको_क्रम_dma_load(dev);
	अगर (ret < 0)
		वापस ret;
#अन्यथा
	ret = ni_ao_prep_fअगरo(dev, s);
	अगर (ret == 0)
		वापस -EPIPE;

	पूर्णांकerrupt_b_bits |= NISTC_INTB_ENA_AO_FIFO;
#पूर्ण_अगर

	ni_stc_ग_लिखोw(dev, devpriv->ao_mode3 | NISTC_AO_MODE3_NOT_AN_UPDATE,
		      NISTC_AO_MODE3_REG);
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode3, NISTC_AO_MODE3_REG);
	/* रुको क्रम DACs to be loaded */
	क्रम (i = 0; i < समयout; i++) अणु
		udelay(1);
		अगर ((ni_stc_पढ़ोw(dev, NISTC_STATUS2_REG) &
		     NISTC_STATUS2_AO_TMRDACWRS_IN_PROGRESS) == 0)
			अवरोध;
	पूर्ण
	अगर (i == समयout) अणु
		dev_err(dev->class_dev,
			"timed out waiting for AO_TMRDACWRs_In_Progress_St to clear\n");
		वापस -EIO;
	पूर्ण
	/*
	 * stc manual says we are need to clear error पूर्णांकerrupt after
	 * AO_TMRDACWRs_In_Progress_St clears
	 */
	ni_stc_ग_लिखोw(dev, NISTC_INTB_ACK_AO_ERR, NISTC_INTB_ACK_REG);

	ni_set_bits(dev, NISTC_INTB_ENA_REG, पूर्णांकerrupt_b_bits, 1);

	ni_stc_ग_लिखोw(dev, NISTC_AO_CMD1_UI_ARM |
			   NISTC_AO_CMD1_UC_ARM |
			   NISTC_AO_CMD1_BC_ARM |
			   devpriv->ao_cmd1,
		      NISTC_AO_CMD1_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक ni_ao_insn_config(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक nbytes;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_GET_HARDWARE_BUFFER_SIZE:
		चयन (data[1]) अणु
		हाल COMEDI_OUTPUT:
			nbytes = comedi_samples_to_bytes(s,
							 board->ao_fअगरo_depth);
			data[2] = 1 + nbytes;
			अगर (devpriv->mite)
				data[2] += devpriv->mite->fअगरo_size;
			अवरोध;
		हाल COMEDI_INPUT:
			data[2] = 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	हाल INSN_CONFIG_ARM:
		वापस ni_ao_arm(dev, s);
	हाल INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS:
		/* we करोn't care about actual channels */
		/* data[3] : chanlist_len */
		data[1] = board->ao_speed * data[3];
		data[2] = 0;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ni_ao_पूर्णांकtrig(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक ret;

	/*
	 * Require trig_num == cmd->start_arg when cmd->start_src == TRIG_INT.
	 * For backwards compatibility, also allow trig_num == 0 when
	 * cmd->start_src != TRIG_INT (i.e. when cmd->start_src == TRIG_EXT);
	 * in that हाल, the पूर्णांकernal trigger is being used as a pre-trigger
	 * beक्रमe the बाह्यal trigger.
	 */
	अगर (!(trig_num == cmd->start_arg ||
	      (trig_num == 0 && cmd->start_src != TRIG_INT)))
		वापस -EINVAL;

	/*
	 * Null trig at beginning prevent ao start trigger from executing more
	 * than once per command.
	 */
	s->async->पूर्णांकtrig = शून्य;

	अगर (devpriv->ao_needs_arming) अणु
		/* only arm this device अगर it still needs arming */
		ret = ni_ao_arm(dev, s);
		अगर (ret)
			वापस ret;
	पूर्ण

	ni_stc_ग_लिखोw(dev, NISTC_AO_CMD2_START1_PULSE | devpriv->ao_cmd2,
		      NISTC_AO_CMD2_REG);

	वापस 0;
पूर्ण

/*
 * begin ni_ao_cmd.
 * Organized similar to NI-STC and MHDDK examples.
 * ni_ao_cmd is broken out पूर्णांकo configuration sub-routines क्रम clarity.
 */

अटल व्योम ni_ao_cmd_personalize(काष्ठा comedi_device *dev,
				  स्थिर काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	अचिन्हित पूर्णांक bits;

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	bits =
	  /* fast CPU पूर्णांकerface--only eseries */
	  /* ((slow CPU पूर्णांकerface) ? 0 : AO_Fast_CPU) | */
	  NISTC_AO_PERSONAL_BC_SRC_SEL  |
	  0 /* (use_original_pulse ? 0 : NISTC_AO_PERSONAL_UPDATE_TIMEBASE) */ |
	  /*
	   * FIXME:  start setting following bit when appropriate.  Need to
	   * determine whether board is E4 or E1.
	   * FROM MHHDK:
	   * अगर board is E4 or E1
	   *   Set bit "NISTC_AO_PERSONAL_UPDATE_PW" to 0
	   * अन्यथा
	   *   set it to 1
	   */
	  NISTC_AO_PERSONAL_UPDATE_PW   |
	  /* FIXME:  when should we set following bit to zero? */
	  NISTC_AO_PERSONAL_TMRDACWR_PW |
	  (board->ao_fअगरo_depth ?
	    NISTC_AO_PERSONAL_FIFO_ENA : NISTC_AO_PERSONAL_DMA_PIO_CTRL)
	  ;
#अगर 0
	/*
	 * FIXME:
	 * add something like ".has_individual_dacs = 0" to ni_board_काष्ठा
	 * since, as F Hess poपूर्णांकed out, not all in m series have singles.  not
	 * sure अगर e-series all have duals...
	 */

	/*
	 * F Hess: winकरोws driver करोes not set NISTC_AO_PERSONAL_NUM_DAC bit क्रम
	 * 6281, verअगरied with bus analyzer.
	 */
	अगर (devpriv->is_m_series)
		bits |= NISTC_AO_PERSONAL_NUM_DAC;
#पूर्ण_अगर
	ni_stc_ग_लिखोw(dev, bits, NISTC_AO_PERSONAL_REG);

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
पूर्ण

अटल व्योम ni_ao_cmd_set_trigger(काष्ठा comedi_device *dev,
				  स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक trigsel;

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	/* sync */
	अगर (cmd->stop_src == TRIG_NONE) अणु
		devpriv->ao_mode1 |= NISTC_AO_MODE1_CONTINUOUS;
		devpriv->ao_mode1 &= ~NISTC_AO_MODE1_TRIGGER_ONCE;
	पूर्ण अन्यथा अणु
		devpriv->ao_mode1 &= ~NISTC_AO_MODE1_CONTINUOUS;
		devpriv->ao_mode1 |= NISTC_AO_MODE1_TRIGGER_ONCE;
	पूर्ण
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode1, NISTC_AO_MODE1_REG);

	अगर (cmd->start_src == TRIG_INT) अणु
		trigsel = NISTC_AO_TRIG_START1_EDGE |
			  NISTC_AO_TRIG_START1_SYNC;
	पूर्ण अन्यथा अणु /* TRIG_EXT */
		trigsel = NISTC_AO_TRIG_START1_SEL(
				ni_get_reg_value_roffs(
						CR_CHAN(cmd->start_arg),
						NI_AO_StartTrigger,
						&devpriv->routing_tables, 1));

		/* 0=active high, 1=active low. see daq-stc 3-24 (p186) */
		अगर (cmd->start_arg & CR_INVERT)
			trigsel |= NISTC_AO_TRIG_START1_POLARITY;
		/* 0=edge detection disabled, 1=enabled */
		अगर (cmd->start_arg & CR_EDGE)
			trigsel |= NISTC_AO_TRIG_START1_EDGE;
	पूर्ण
	ni_stc_ग_लिखोw(dev, trigsel, NISTC_AO_TRIG_SEL_REG);

	/* AO_Delayed_START1 = 0, we करो not support delayed start...yet */

	/* sync */
	/* select DA_START1 as PFI6/AO_START1 when configured as an output */
	devpriv->ao_mode3 &= ~NISTC_AO_MODE3_TRIG_LEN;
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode3, NISTC_AO_MODE3_REG);

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
पूर्ण

अटल व्योम ni_ao_cmd_set_counters(काष्ठा comedi_device *dev,
				   स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	/* Not supporting 'waveform staging' or 'local buffer with pauses' */

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);
	/*
	 * This relies on ao_mode1/(Trigger_Once | Continuous) being set in
	 * set_trigger above.  It is unclear whether we really need to re-ग_लिखो
	 * this रेजिस्टर with these values.  The mhddk examples क्रम e-series
	 * show writing this in both places, but the examples क्रम m-series show
	 * a single ग_लिखो in the set_counters function (here).
	 */
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode1, NISTC_AO_MODE1_REG);

	/* sync (upload number of buffer iterations -1) */
	/* indicate that we want to use BC_Load_A_Register as the source */
	devpriv->ao_mode2 &= ~NISTC_AO_MODE2_BC_INIT_LOAD_SRC;
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode2, NISTC_AO_MODE2_REG);

	/*
	 * अगर the BC_TC पूर्णांकerrupt is still issued in spite of UC, BC, UI
	 * ignoring BC_TC, then we will need to find a way to ignore that
	 * पूर्णांकerrupt in continuous mode.
	 */
	ni_stc_ग_लिखोl(dev, 0, NISTC_AO_BC_LOADA_REG); /* iter once */

	/* sync (issue command to load number of buffer iterations -1) */
	ni_stc_ग_लिखोw(dev, NISTC_AO_CMD1_BC_LOAD, NISTC_AO_CMD1_REG);

	/* sync (upload number of updates in buffer) */
	/* indicate that we want to use UC_Load_A_Register as the source */
	devpriv->ao_mode2 &= ~NISTC_AO_MODE2_UC_INIT_LOAD_SRC;
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode2, NISTC_AO_MODE2_REG);

	/*
	 * अगर a user specअगरies '0', this स्वतःmatically assumes the entire 24bit
	 * address space is available क्रम the (multiple iterations of single
	 * buffer) MISB.  Otherwise, stop_arg specअगरies the MISB length that
	 * will be used, regardless of whether we are in continuous mode or not.
	 * In continuous mode, the output will just iterate indefinitely over
	 * the MISB.
	 */
	अणु
		अचिन्हित पूर्णांक stop_arg = cmd->stop_arg > 0 ?
			(cmd->stop_arg & 0xffffff) : 0xffffff;

		अगर (devpriv->is_m_series) अणु
			/*
			 * this is how the NI example code करोes it क्रम m-series
			 * boards, verअगरied correct with 6259
			 */
			ni_stc_ग_लिखोl(dev, stop_arg - 1, NISTC_AO_UC_LOADA_REG);

			/* sync (issue cmd to load number of updates in MISB) */
			ni_stc_ग_लिखोw(dev, NISTC_AO_CMD1_UC_LOAD,
				      NISTC_AO_CMD1_REG);
		पूर्ण अन्यथा अणु
			ni_stc_ग_लिखोl(dev, stop_arg, NISTC_AO_UC_LOADA_REG);

			/* sync (issue cmd to load number of updates in MISB) */
			ni_stc_ग_लिखोw(dev, NISTC_AO_CMD1_UC_LOAD,
				      NISTC_AO_CMD1_REG);

			/*
			 * sync (upload number of updates-1 in MISB)
			 * --eseries only?
			 */
			ni_stc_ग_लिखोl(dev, stop_arg - 1, NISTC_AO_UC_LOADA_REG);
		पूर्ण
	पूर्ण

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
पूर्ण

अटल व्योम ni_ao_cmd_set_update(काष्ठा comedi_device *dev,
				 स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	/*
	 * zero out these bit fields to be set below. Does an ao-reset करो this
	 * स्वतःmatically?
	 */
	devpriv->ao_mode1 &=  ~(NISTC_AO_MODE1_UI_SRC_MASK	   |
				NISTC_AO_MODE1_UI_SRC_POLARITY	   |
				NISTC_AO_MODE1_UPDATE_SRC_MASK	   |
				NISTC_AO_MODE1_UPDATE_SRC_POLARITY);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		अचिन्हित पूर्णांक trigvar;

		devpriv->ao_cmd2  &= ~NISTC_AO_CMD2_BC_GATE_ENA;

		/*
		 * NOTE: there are several other ways of configuring पूर्णांकernal
		 * updates, but we'll only support one क्रम now:  using
		 * AO_IN_TIMEBASE, w/o waveक्रमm staging, w/o a delay between
		 * START1 and first update, and also w/o local buffer mode w/
		 * छोड़ोs.
		 */

		/*
		 * This is alपढ़ोy करोne above:
		 * devpriv->ao_mode1 &= ~(
		 *   // set UPDATE_Source to UI_TC:
		 *   NISTC_AO_MODE1_UPDATE_SRC_MASK |
		 *   // set UPDATE_Source_Polarity to rising (required?)
		 *   NISTC_AO_MODE1_UPDATE_SRC_POLARITY |
		 *   // set UI_Source to AO_IN_TIMEBASE1:
		 *   NISTC_AO_MODE1_UI_SRC_MASK     |
		 *   // set UI_Source_Polarity to rising (required?)
		 *   NISTC_AO_MODE1_UI_SRC_POLARITY
		 * );
		 */

		/*
		 * TODO:  use ao_ui_घड़ी_source to allow all possible संकेतs
		 * to be routed to UI_Source_Select.  See tSTC.h क्रम
		 * eseries/ni67xx and tMSeries.h क्रम mseries.
		 */

		trigvar = ni_ns_to_समयr(dev, cmd->scan_begin_arg,
					 CMDF_ROUND_NEAREST);

		/*
		 * Wait N TB3 ticks after the start trigger beक्रमe
		 * घड़ीing (N must be >=2).
		 */
		/* following line: 2-1 per STC */
		ni_stc_ग_लिखोl(dev, 1, NISTC_AO_UI_LOADA_REG);
		ni_stc_ग_लिखोw(dev, NISTC_AO_CMD1_UI_LOAD, NISTC_AO_CMD1_REG);
		ni_stc_ग_लिखोl(dev, trigvar, NISTC_AO_UI_LOADA_REG);
	पूर्ण अन्यथा अणु /* TRIG_EXT */
		/* FIXME:  निश्चित scan_begin_arg != 0, ret failure otherwise */
		devpriv->ao_cmd2  |= NISTC_AO_CMD2_BC_GATE_ENA;
		devpriv->ao_mode1 |= NISTC_AO_MODE1_UPDATE_SRC(
					ni_get_reg_value(
						CR_CHAN(cmd->scan_begin_arg),
						NI_AO_SampleClock,
						&devpriv->routing_tables));
		अगर (cmd->scan_begin_arg & CR_INVERT)
			devpriv->ao_mode1 |= NISTC_AO_MODE1_UPDATE_SRC_POLARITY;
	पूर्ण

	ni_stc_ग_लिखोw(dev, devpriv->ao_cmd2, NISTC_AO_CMD2_REG);
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode1, NISTC_AO_MODE1_REG);
	devpriv->ao_mode2 &= ~(NISTC_AO_MODE2_UI_RELOAD_MODE(3) |
			       NISTC_AO_MODE2_UI_INIT_LOAD_SRC);
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode2, NISTC_AO_MODE2_REG);

	/* Configure DAQ-STC क्रम Timed update mode */
	devpriv->ao_cmd1 |= NISTC_AO_CMD1_DAC1_UPDATE_MODE |
			    NISTC_AO_CMD1_DAC0_UPDATE_MODE;
	/* We are not using UPDATE2-->करोn't have to set DACx_Source_Select */
	ni_stc_ग_लिखोw(dev, devpriv->ao_cmd1, NISTC_AO_CMD1_REG);

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
पूर्ण

अटल व्योम ni_ao_cmd_set_channels(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	स्थिर काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक bits = 0;

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	अगर (devpriv->is_6xxx) अणु
		अचिन्हित पूर्णांक i;

		bits = 0;
		क्रम (i = 0; i < cmd->chanlist_len; ++i) अणु
			पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);

			bits |= 1 << chan;
			ni_ao_win_outw(dev, chan, NI611X_AO_WAVEFORM_GEN_REG);
		पूर्ण
		ni_ao_win_outw(dev, bits, NI611X_AO_TIMED_REG);
	पूर्ण

	ni_ao_config_chanlist(dev, s, cmd->chanlist, cmd->chanlist_len, 1);

	अगर (cmd->scan_end_arg > 1) अणु
		devpriv->ao_mode1 |= NISTC_AO_MODE1_MULTI_CHAN;
		bits = NISTC_AO_OUT_CTRL_CHANS(cmd->scan_end_arg - 1)
				 | NISTC_AO_OUT_CTRL_UPDATE_SEL_HIGHZ;

	पूर्ण अन्यथा अणु
		devpriv->ao_mode1 &= ~NISTC_AO_MODE1_MULTI_CHAN;
		bits = NISTC_AO_OUT_CTRL_UPDATE_SEL_HIGHZ;
		अगर (devpriv->is_m_series | devpriv->is_6xxx)
			bits |= NISTC_AO_OUT_CTRL_CHANS(0);
		अन्यथा
			bits |= NISTC_AO_OUT_CTRL_CHANS(
					CR_CHAN(cmd->chanlist[0]));
	पूर्ण

	ni_stc_ग_लिखोw(dev, devpriv->ao_mode1, NISTC_AO_MODE1_REG);
	ni_stc_ग_लिखोw(dev, bits,              NISTC_AO_OUT_CTRL_REG);

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
पूर्ण

अटल व्योम ni_ao_cmd_set_stop_conditions(काष्ठा comedi_device *dev,
					  स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	devpriv->ao_mode3 |= NISTC_AO_MODE3_STOP_ON_OVERRUN_ERR;
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode3, NISTC_AO_MODE3_REG);

	/*
	 * Since we are not supporting waveक्रमm staging, we ignore these errors:
	 * NISTC_AO_MODE3_STOP_ON_BC_TC_ERR,
	 * NISTC_AO_MODE3_STOP_ON_BC_TC_TRIG_ERR
	 */

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
पूर्ण

अटल व्योम ni_ao_cmd_set_fअगरo_mode(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	devpriv->ao_mode2 &= ~NISTC_AO_MODE2_FIFO_MODE_MASK;
#अगर_घोषित PCIDMA
	devpriv->ao_mode2 |= NISTC_AO_MODE2_FIFO_MODE_HF_F;
#अन्यथा
	devpriv->ao_mode2 |= NISTC_AO_MODE2_FIFO_MODE_HF;
#पूर्ण_अगर
	/* NOTE:  this is where use_onboard_memory=True would be implemented */
	devpriv->ao_mode2 &= ~NISTC_AO_MODE2_FIFO_REXMIT_ENA;
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode2, NISTC_AO_MODE2_REG);

	/* enable sending of ao fअगरo requests (dma request) */
	ni_stc_ग_लिखोw(dev, NISTC_AO_START_AOFREQ_ENA, NISTC_AO_START_SEL_REG);

	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);

	/* we are not supporting boards with भव fअगरos */
पूर्ण

अटल व्योम ni_ao_cmd_set_पूर्णांकerrupts(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s)
अणु
	अगर (s->async->cmd.stop_src == TRIG_COUNT)
		ni_set_bits(dev, NISTC_INTB_ENA_REG,
			    NISTC_INTB_ENA_AO_BC_TC, 1);

	s->async->पूर्णांकtrig = ni_ao_पूर्णांकtrig;
पूर्ण

अटल पूर्णांक ni_ao_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	स्थिर काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (dev->irq == 0) अणु
		dev_err(dev->class_dev, "cannot run command without an irq");
		वापस -EIO;
	पूर्ण

	/* ni_ao_reset should have alपढ़ोy been करोne */
	ni_ao_cmd_personalize(dev, cmd);
	/* clearing fअगरo and preload happens अन्यथाwhere */

	ni_ao_cmd_set_trigger(dev, cmd);
	ni_ao_cmd_set_counters(dev, cmd);
	ni_ao_cmd_set_update(dev, cmd);
	ni_ao_cmd_set_channels(dev, s);
	ni_ao_cmd_set_stop_conditions(dev, cmd);
	ni_ao_cmd_set_fअगरo_mode(dev);
	ni_cmd_set_mite_transfer(devpriv->ao_mite_ring, s, cmd, 0x00ffffff);
	ni_ao_cmd_set_पूर्णांकerrupts(dev, s);

	/*
	 * arm(ing) must happen later so that DMA can be setup and DACs
	 * preloaded with the actual output buffer beक्रमe starting.
	 *
	 * start(ing) must happen _after_ arming is completed.  Starting can be
	 * करोne either via ni_ao_पूर्णांकtrig, or via an बाह्यal trigger.
	 *
	 * **Currently, ni_ao_पूर्णांकtrig will स्वतःmatically attempt a call to
	 * ni_ao_arm अगर the device still needs arming at that poपूर्णांक.  This
	 * allows backwards compatibility.
	 */
	devpriv->ao_needs_arming = 1;
	वापस 0;
पूर्ण

/* end ni_ao_cmd */

अटल पूर्णांक ni_ao_cmdtest(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक पंचांगp;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	चयन (cmd->start_src) अणु
	हाल TRIG_INT:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		अवरोध;
	हाल TRIG_EXT:
		err |= ni_check_trigger_arg_roffs(CR_CHAN(cmd->start_arg),
						  NI_AO_StartTrigger,
						  &devpriv->routing_tables, 1);
		अवरोध;
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    board->ao_speed);
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
						    devpriv->घड़ी_ns *
						    0xffffff);
	पूर्ण अन्यथा अणु		/* TRIG_EXT */
		err |= ni_check_trigger_arg(CR_CHAN(cmd->scan_begin_arg),
					    NI_AO_SampleClock,
					    &devpriv->routing_tables);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	err |= comedi_check_trigger_arg_max(&cmd->stop_arg, 0x00ffffff);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */
	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		पंचांगp = cmd->scan_begin_arg;
		cmd->scan_begin_arg =
		    ni_समयr_to_ns(dev, ni_ns_to_समयr(dev,
						       cmd->scan_begin_arg,
						       cmd->flags));
		अगर (पंचांगp != cmd->scan_begin_arg)
			err++;
	पूर्ण
	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक ni_ao_reset(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	/* See 3.6.1.2 "Resetting", of DAQ-STC Technical Reference Manual */

	/*
	 * In the following, the "--sync" comments are meant to denote
	 * asynchronous boundaries क्रम setting the रेजिस्टरs as described in the
	 * DAQ-STC mostly in the order also described in the DAQ-STC.
	 */

	काष्ठा ni_निजी *devpriv = dev->निजी;

	ni_release_ao_mite_channel(dev);

	/* --sync (reset AO) */
	अगर (devpriv->is_m_series)
		/* following example in mhddk क्रम m-series */
		ni_stc_ग_लिखोw(dev, NISTC_RESET_AO, NISTC_RESET_REG);

	/*--sync (start config) */
	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	/*--sync (Disarm) */
	ni_stc_ग_लिखोw(dev, NISTC_AO_CMD1_DISARM, NISTC_AO_CMD1_REG);

	/*
	 * --sync
	 * (clear bunch of रेजिस्टरs--mseries mhddk examples करो not include
	 * this)
	 */
	devpriv->ao_cmd1  = 0;
	devpriv->ao_cmd2  = 0;
	devpriv->ao_mode1 = 0;
	devpriv->ao_mode2 = 0;
	अगर (devpriv->is_m_series)
		devpriv->ao_mode3 = NISTC_AO_MODE3_LAST_GATE_DISABLE;
	अन्यथा
		devpriv->ao_mode3 = 0;

	ni_stc_ग_लिखोw(dev, 0, NISTC_AO_PERSONAL_REG);
	ni_stc_ग_लिखोw(dev, 0, NISTC_AO_CMD1_REG);
	ni_stc_ग_लिखोw(dev, 0, NISTC_AO_CMD2_REG);
	ni_stc_ग_लिखोw(dev, 0, NISTC_AO_MODE1_REG);
	ni_stc_ग_लिखोw(dev, 0, NISTC_AO_MODE2_REG);
	ni_stc_ग_लिखोw(dev, 0, NISTC_AO_OUT_CTRL_REG);
	ni_stc_ग_लिखोw(dev, devpriv->ao_mode3, NISTC_AO_MODE3_REG);
	ni_stc_ग_लिखोw(dev, 0, NISTC_AO_START_SEL_REG);
	ni_stc_ग_लिखोw(dev, 0, NISTC_AO_TRIG_SEL_REG);

	/*--sync (disable पूर्णांकerrupts) */
	ni_set_bits(dev, NISTC_INTB_ENA_REG, ~0, 0);

	/*--sync (ack) */
	ni_stc_ग_लिखोw(dev, NISTC_AO_PERSONAL_BC_SRC_SEL, NISTC_AO_PERSONAL_REG);
	ni_stc_ग_लिखोw(dev, NISTC_INTB_ACK_AO_ALL, NISTC_INTB_ACK_REG);

	/*--not in DAQ-STC.  which करोc? */
	अगर (devpriv->is_6xxx) अणु
		ni_ao_win_outw(dev, (1u << s->n_chan) - 1u,
			       NI671X_AO_IMMEDIATE_REG);
		ni_ao_win_outw(dev, NI611X_AO_MISC_CLEAR_WG,
			       NI611X_AO_MISC_REG);
	पूर्ण
	ni_stc_ग_लिखोw(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
	/*--end */

	वापस 0;
पूर्ण

/* digital io */

अटल पूर्णांक ni_dio_insn_config(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	devpriv->dio_control &= ~NISTC_DIO_CTRL_सूची_MASK;
	devpriv->dio_control |= NISTC_DIO_CTRL_सूची(s->io_bits);
	ni_stc_ग_लिखोw(dev, devpriv->dio_control, NISTC_DIO_CTRL_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_dio_insn_bits(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s,
			    काष्ठा comedi_insn *insn,
			    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	/* Make sure we're not using the serial part of the dio */
	अगर ((data[0] & (NISTC_DIO_SDIN | NISTC_DIO_SDOUT)) &&
	    devpriv->serial_पूर्णांकerval_ns)
		वापस -EBUSY;

	अगर (comedi_dio_update_state(s, data)) अणु
		devpriv->dio_output &= ~NISTC_DIO_OUT_PARALLEL_MASK;
		devpriv->dio_output |= NISTC_DIO_OUT_PARALLEL(s->state);
		ni_stc_ग_लिखोw(dev, devpriv->dio_output, NISTC_DIO_OUT_REG);
	पूर्ण

	data[1] = ni_stc_पढ़ोw(dev, NISTC_DIO_IN_REG);

	वापस insn->n;
पूर्ण

#अगर_घोषित PCIDMA
अटल पूर्णांक ni_m_series_dio_insn_config(काष्ठा comedi_device *dev,
				       काष्ठा comedi_subdevice *s,
				       काष्ठा comedi_insn *insn,
				       अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	अगर (data[0] == INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS) अणु
		स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;

		/* we करोn't care about actual channels */
		data[1] = board->dio_speed;
		data[2] = 0;
		वापस 0;
	पूर्ण

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	ni_ग_लिखोl(dev, s->io_bits, NI_M_DIO_सूची_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_m_series_dio_insn_bits(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		ni_ग_लिखोl(dev, s->state, NI_M_DIO_REG);

	data[1] = ni_पढ़ोl(dev, NI_M_DIO_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_cdio_check_chanlist(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cmd->chanlist_len; ++i) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);

		अगर (chan != i)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ni_cdio_cmdtest(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक bytes_per_scan;
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	/*
	 * Although NI_D[IO]_SampleClock are the same, perhaps we should still,
	 * क्रम completeness, test whether the cmd is output or input?
	 */
	err |= ni_check_trigger_arg(CR_CHAN(cmd->scan_begin_arg),
				    NI_DO_SampleClock,
				    &devpriv->routing_tables);
	अगर (CR_RANGE(cmd->scan_begin_arg) != 0 ||
	    CR_AREF(cmd->scan_begin_arg) != 0)
		err |= -EINVAL;

	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	bytes_per_scan = comedi_bytes_per_scan_cmd(s, cmd);
	अगर (bytes_per_scan) अणु
		err |= comedi_check_trigger_arg_max(&cmd->stop_arg,
						    s->async->pपुनः_स्मृति_bufsz /
						    bytes_per_scan);
	पूर्ण

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list अगर it exists */

	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= ni_cdio_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक ni_cकरो_पूर्णांकtrig(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	स्थिर अचिन्हित पूर्णांक समयout = 1000;
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	s->async->पूर्णांकtrig = शून्य;

	/* पढ़ो alloc the entire buffer */
	comedi_buf_पढ़ो_alloc(s, s->async->pपुनः_स्मृति_bufsz);

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->cकरो_mite_chan) अणु
		mite_prep_dma(devpriv->cकरो_mite_chan, 32, 32);
		mite_dma_arm(devpriv->cकरो_mite_chan);
	पूर्ण अन्यथा अणु
		dev_err(dev->class_dev, "BUG: no cdo mite channel?\n");
		retval = -EIO;
	पूर्ण
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	अगर (retval < 0)
		वापस retval;

	/*
	 * XXX not sure what पूर्णांकerrupt C group करोes
	 * रुको क्रम dma to fill output fअगरo
	 * ni_ग_लिखोb(dev, NI_M_INTC_ENA, NI_M_INTC_ENA_REG);
	 */
	क्रम (i = 0; i < समयout; ++i) अणु
		अगर (ni_पढ़ोl(dev, NI_M_CDIO_STATUS_REG) &
		    NI_M_CDIO_STATUS_CDO_FIFO_FULL)
			अवरोध;
		usleep_range(10, 100);
	पूर्ण
	अगर (i == समयout) अणु
		dev_err(dev->class_dev, "dma failed to fill cdo fifo!\n");
		s->cancel(dev, s);
		वापस -EIO;
	पूर्ण
	ni_ग_लिखोl(dev, NI_M_CDO_CMD_ARM |
		       NI_M_CDO_CMD_ERR_INT_ENA_SET |
		       NI_M_CDO_CMD_F_E_INT_ENA_SET,
		  NI_M_CDIO_CMD_REG);
	वापस retval;
पूर्ण

अटल पूर्णांक ni_cdio_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	स्थिर काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक cकरो_mode_bits;
	पूर्णांक retval;

	ni_ग_लिखोl(dev, NI_M_CDO_CMD_RESET, NI_M_CDIO_CMD_REG);
	/*
	 * Although NI_D[IO]_SampleClock are the same, perhaps we should still,
	 * क्रम completeness, test whether the cmd is output or input(?)
	 */
	cकरो_mode_bits = NI_M_CDO_MODE_FIFO_MODE |
			NI_M_CDO_MODE_HALT_ON_ERROR |
			NI_M_CDO_MODE_SAMPLE_SRC(
				ni_get_reg_value(
					CR_CHAN(cmd->scan_begin_arg),
					NI_DO_SampleClock,
					&devpriv->routing_tables));
	अगर (cmd->scan_begin_arg & CR_INVERT)
		cकरो_mode_bits |= NI_M_CDO_MODE_POLARITY;
	ni_ग_लिखोl(dev, cकरो_mode_bits, NI_M_CDO_MODE_REG);
	अगर (s->io_bits) अणु
		ni_ग_लिखोl(dev, s->state, NI_M_CDO_FIFO_DATA_REG);
		ni_ग_लिखोl(dev, NI_M_CDO_CMD_SW_UPDATE, NI_M_CDIO_CMD_REG);
		ni_ग_लिखोl(dev, s->io_bits, NI_M_CDO_MASK_ENA_REG);
	पूर्ण अन्यथा अणु
		dev_err(dev->class_dev,
			"attempted to run digital output command with no lines configured as outputs\n");
		वापस -EIO;
	पूर्ण
	retval = ni_request_cकरो_mite_channel(dev);
	अगर (retval < 0)
		वापस retval;

	ni_cmd_set_mite_transfer(devpriv->cकरो_mite_ring, s, cmd,
				 s->async->pपुनः_स्मृति_bufsz /
				 comedi_bytes_per_scan(s));

	s->async->पूर्णांकtrig = ni_cकरो_पूर्णांकtrig;

	वापस 0;
पूर्ण

अटल पूर्णांक ni_cdio_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	ni_ग_लिखोl(dev, NI_M_CDO_CMD_DISARM |
		       NI_M_CDO_CMD_ERR_INT_ENA_CLR |
		       NI_M_CDO_CMD_F_E_INT_ENA_CLR |
		       NI_M_CDO_CMD_F_REQ_INT_ENA_CLR,
		  NI_M_CDIO_CMD_REG);
	/*
	 * XXX not sure what पूर्णांकerrupt C group करोes
	 * ni_ग_लिखोb(dev, 0, NI_M_INTC_ENA_REG);
	 */
	ni_ग_लिखोl(dev, 0, NI_M_CDO_MASK_ENA_REG);
	ni_release_cकरो_mite_channel(dev);
	वापस 0;
पूर्ण

अटल व्योम handle_cdio_पूर्णांकerrupt(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक cdio_status;
	काष्ठा comedi_subdevice *s = &dev->subdevices[NI_DIO_SUBDEV];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->cकरो_mite_chan)
		mite_ack_linkc(devpriv->cकरो_mite_chan, s, true);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	cdio_status = ni_पढ़ोl(dev, NI_M_CDIO_STATUS_REG);
	अगर (cdio_status & NI_M_CDIO_STATUS_CDO_ERROR) अणु
		/* XXX just guessing this is needed and करोes something useful */
		ni_ग_लिखोl(dev, NI_M_CDO_CMD_ERR_INT_CONFIRM,
			  NI_M_CDIO_CMD_REG);
		s->async->events |= COMEDI_CB_OVERFLOW;
	पूर्ण
	अगर (cdio_status & NI_M_CDIO_STATUS_CDO_FIFO_EMPTY) अणु
		ni_ग_लिखोl(dev, NI_M_CDO_CMD_F_E_INT_ENA_CLR,
			  NI_M_CDIO_CMD_REG);
		/* s->async->events |= COMEDI_CB_EOA; */
	पूर्ण
	comedi_handle_events(dev, s);
पूर्ण
#पूर्ण_अगर /*  PCIDMA */

अटल पूर्णांक ni_serial_hw_पढ़ोग_लिखो8(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित अक्षर data_out,
				   अचिन्हित अक्षर *data_in)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक status1;
	पूर्णांक err = 0, count = 20;

	devpriv->dio_output &= ~NISTC_DIO_OUT_SERIAL_MASK;
	devpriv->dio_output |= NISTC_DIO_OUT_SERIAL(data_out);
	ni_stc_ग_लिखोw(dev, devpriv->dio_output, NISTC_DIO_OUT_REG);

	status1 = ni_stc_पढ़ोw(dev, NISTC_STATUS1_REG);
	अगर (status1 & NISTC_STATUS1_SERIO_IN_PROG) अणु
		err = -EBUSY;
		जाओ error;
	पूर्ण

	devpriv->dio_control |= NISTC_DIO_CTRL_HW_SER_START;
	ni_stc_ग_लिखोw(dev, devpriv->dio_control, NISTC_DIO_CTRL_REG);
	devpriv->dio_control &= ~NISTC_DIO_CTRL_HW_SER_START;

	/* Wait until STC says we're done, but don't loop infinitely. */
	जबतक ((status1 = ni_stc_पढ़ोw(dev, NISTC_STATUS1_REG)) &
	       NISTC_STATUS1_SERIO_IN_PROG) अणु
		/* Delay one bit per loop */
		udelay((devpriv->serial_पूर्णांकerval_ns + 999) / 1000);
		अगर (--count < 0) अणु
			dev_err(dev->class_dev,
				"SPI serial I/O didn't finish in time!\n");
			err = -ETIME;
			जाओ error;
		पूर्ण
	पूर्ण

	/*
	 * Delay क्रम last bit. This delay is असलolutely necessary, because
	 * NISTC_STATUS1_SERIO_IN_PROG goes high one bit too early.
	 */
	udelay((devpriv->serial_पूर्णांकerval_ns + 999) / 1000);

	अगर (data_in)
		*data_in = ni_stc_पढ़ोw(dev, NISTC_DIO_SERIAL_IN_REG);

error:
	ni_stc_ग_लिखोw(dev, devpriv->dio_control, NISTC_DIO_CTRL_REG);

	वापस err;
पूर्ण

अटल पूर्णांक ni_serial_sw_पढ़ोग_लिखो8(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित अक्षर data_out,
				   अचिन्हित अक्षर *data_in)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित अक्षर mask, input = 0;

	/* Wait क्रम one bit beक्रमe transfer */
	udelay((devpriv->serial_पूर्णांकerval_ns + 999) / 1000);

	क्रम (mask = 0x80; mask; mask >>= 1) अणु
		/*
		 * Output current bit; note that we cannot touch s->state
		 * because it is a per-subdevice field, and serial is
		 * a separate subdevice from DIO.
		 */
		devpriv->dio_output &= ~NISTC_DIO_SDOUT;
		अगर (data_out & mask)
			devpriv->dio_output |= NISTC_DIO_SDOUT;
		ni_stc_ग_लिखोw(dev, devpriv->dio_output, NISTC_DIO_OUT_REG);

		/*
		 * Assert SDCLK (active low, inverted), रुको क्रम half of
		 * the delay, deनिश्चित SDCLK, and रुको क्रम the other half.
		 */
		devpriv->dio_control |= NISTC_DIO_SDCLK;
		ni_stc_ग_लिखोw(dev, devpriv->dio_control, NISTC_DIO_CTRL_REG);

		udelay((devpriv->serial_पूर्णांकerval_ns + 999) / 2000);

		devpriv->dio_control &= ~NISTC_DIO_SDCLK;
		ni_stc_ग_लिखोw(dev, devpriv->dio_control, NISTC_DIO_CTRL_REG);

		udelay((devpriv->serial_पूर्णांकerval_ns + 999) / 2000);

		/* Input current bit */
		अगर (ni_stc_पढ़ोw(dev, NISTC_DIO_IN_REG) & NISTC_DIO_SDIN)
			input |= mask;
	पूर्ण

	अगर (data_in)
		*data_in = input;

	वापस 0;
पूर्ण

अटल पूर्णांक ni_serial_insn_config(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक clk_fout = devpriv->घड़ी_and_fout;
	पूर्णांक err = insn->n;
	अचिन्हित अक्षर byte_out, byte_in = 0;

	अगर (insn->n != 2)
		वापस -EINVAL;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_SERIAL_CLOCK:
		devpriv->serial_hw_mode = 1;
		devpriv->dio_control |= NISTC_DIO_CTRL_HW_SER_ENA;

		अगर (data[1] == SERIAL_DISABLED) अणु
			devpriv->serial_hw_mode = 0;
			devpriv->dio_control &= ~(NISTC_DIO_CTRL_HW_SER_ENA |
						  NISTC_DIO_SDCLK);
			data[1] = SERIAL_DISABLED;
			devpriv->serial_पूर्णांकerval_ns = data[1];
		पूर्ण अन्यथा अगर (data[1] <= SERIAL_600NS) अणु
			/*
			 * Warning: this घड़ी speed is too fast to reliably
			 * control SCXI.
			 */
			devpriv->dio_control &= ~NISTC_DIO_CTRL_HW_SER_TIMEBASE;
			clk_fout |= NISTC_CLK_FOUT_SLOW_TIMEBASE;
			clk_fout &= ~NISTC_CLK_FOUT_DIO_SER_OUT_DIV2;
			data[1] = SERIAL_600NS;
			devpriv->serial_पूर्णांकerval_ns = data[1];
		पूर्ण अन्यथा अगर (data[1] <= SERIAL_1_2US) अणु
			devpriv->dio_control &= ~NISTC_DIO_CTRL_HW_SER_TIMEBASE;
			clk_fout |= NISTC_CLK_FOUT_SLOW_TIMEBASE |
				    NISTC_CLK_FOUT_DIO_SER_OUT_DIV2;
			data[1] = SERIAL_1_2US;
			devpriv->serial_पूर्णांकerval_ns = data[1];
		पूर्ण अन्यथा अगर (data[1] <= SERIAL_10US) अणु
			devpriv->dio_control |= NISTC_DIO_CTRL_HW_SER_TIMEBASE;
			clk_fout |= NISTC_CLK_FOUT_SLOW_TIMEBASE |
				    NISTC_CLK_FOUT_DIO_SER_OUT_DIV2;
			/*
			 * Note: NISTC_CLK_FOUT_DIO_SER_OUT_DIV2 only affects
			 * 600ns/1.2us. If you turn भागide_by_2 off with the
			 * slow घड़ी, you will still get 10us, except then
			 * all your delays are wrong.
			 */
			data[1] = SERIAL_10US;
			devpriv->serial_पूर्णांकerval_ns = data[1];
		पूर्ण अन्यथा अणु
			devpriv->dio_control &= ~(NISTC_DIO_CTRL_HW_SER_ENA |
						  NISTC_DIO_SDCLK);
			devpriv->serial_hw_mode = 0;
			data[1] = (data[1] / 1000) * 1000;
			devpriv->serial_पूर्णांकerval_ns = data[1];
		पूर्ण
		devpriv->घड़ी_and_fout = clk_fout;

		ni_stc_ग_लिखोw(dev, devpriv->dio_control, NISTC_DIO_CTRL_REG);
		ni_stc_ग_लिखोw(dev, devpriv->घड़ी_and_fout, NISTC_CLK_FOUT_REG);
		वापस 1;

	हाल INSN_CONFIG_BIसूचीECTIONAL_DATA:

		अगर (devpriv->serial_पूर्णांकerval_ns == 0)
			वापस -EINVAL;

		byte_out = data[1] & 0xFF;

		अगर (devpriv->serial_hw_mode) अणु
			err = ni_serial_hw_पढ़ोग_लिखो8(dev, s, byte_out,
						      &byte_in);
		पूर्ण अन्यथा अगर (devpriv->serial_पूर्णांकerval_ns > 0) अणु
			err = ni_serial_sw_पढ़ोग_लिखो8(dev, s, byte_out,
						      &byte_in);
		पूर्ण अन्यथा अणु
			dev_err(dev->class_dev, "serial disabled!\n");
			वापस -EINVAL;
		पूर्ण
		अगर (err < 0)
			वापस err;
		data[1] = byte_in & 0xFF;
		वापस insn->n;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम init_ao_67xx(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < s->n_chan; i++) अणु
		ni_ao_win_outw(dev, NI_E_AO_DACSEL(i) | 0x0,
			       NI67XX_AO_CFG2_REG);
	पूर्ण
	ni_ao_win_outw(dev, 0x0, NI67XX_AO_SP_UPDATES_REG);
पूर्ण

अटल स्थिर काष्ठा mio_regmap ni_gpct_to_stc_regmap[] = अणु
	[NITIO_G0_AUTO_INC]	= अणु NISTC_G0_AUTOINC_REG, 2 पूर्ण,
	[NITIO_G1_AUTO_INC]	= अणु NISTC_G1_AUTOINC_REG, 2 पूर्ण,
	[NITIO_G0_CMD]		= अणु NISTC_G0_CMD_REG, 2 पूर्ण,
	[NITIO_G1_CMD]		= अणु NISTC_G1_CMD_REG, 2 पूर्ण,
	[NITIO_G0_HW_SAVE]	= अणु NISTC_G0_HW_SAVE_REG, 4 पूर्ण,
	[NITIO_G1_HW_SAVE]	= अणु NISTC_G1_HW_SAVE_REG, 4 पूर्ण,
	[NITIO_G0_SW_SAVE]	= अणु NISTC_G0_SAVE_REG, 4 पूर्ण,
	[NITIO_G1_SW_SAVE]	= अणु NISTC_G1_SAVE_REG, 4 पूर्ण,
	[NITIO_G0_MODE]		= अणु NISTC_G0_MODE_REG, 2 पूर्ण,
	[NITIO_G1_MODE]		= अणु NISTC_G1_MODE_REG, 2 पूर्ण,
	[NITIO_G0_LOADA]	= अणु NISTC_G0_LOADA_REG, 4 पूर्ण,
	[NITIO_G1_LOADA]	= अणु NISTC_G1_LOADA_REG, 4 पूर्ण,
	[NITIO_G0_LOADB]	= अणु NISTC_G0_LOADB_REG, 4 पूर्ण,
	[NITIO_G1_LOADB]	= अणु NISTC_G1_LOADB_REG, 4 पूर्ण,
	[NITIO_G0_INPUT_SEL]	= अणु NISTC_G0_INPUT_SEL_REG, 2 पूर्ण,
	[NITIO_G1_INPUT_SEL]	= अणु NISTC_G1_INPUT_SEL_REG, 2 पूर्ण,
	[NITIO_G0_CNT_MODE]	= अणु 0x1b0, 2 पूर्ण,	/* M-Series only */
	[NITIO_G1_CNT_MODE]	= अणु 0x1b2, 2 पूर्ण,	/* M-Series only */
	[NITIO_G0_GATE2]	= अणु 0x1b4, 2 पूर्ण,	/* M-Series only */
	[NITIO_G1_GATE2]	= अणु 0x1b6, 2 पूर्ण,	/* M-Series only */
	[NITIO_G01_STATUS]	= अणु NISTC_G01_STATUS_REG, 2 पूर्ण,
	[NITIO_G01_RESET]	= अणु NISTC_RESET_REG, 2 पूर्ण,
	[NITIO_G01_STATUS1]	= अणु NISTC_STATUS1_REG, 2 पूर्ण,
	[NITIO_G01_STATUS2]	= अणु NISTC_STATUS2_REG, 2 पूर्ण,
	[NITIO_G0_DMA_CFG]	= अणु 0x1b8, 2 पूर्ण,	/* M-Series only */
	[NITIO_G1_DMA_CFG]	= अणु 0x1ba, 2 पूर्ण,	/* M-Series only */
	[NITIO_G0_DMA_STATUS]	= अणु 0x1b8, 2 पूर्ण,	/* M-Series only */
	[NITIO_G1_DMA_STATUS]	= अणु 0x1ba, 2 पूर्ण,	/* M-Series only */
	[NITIO_G0_ABZ]		= अणु 0x1c0, 2 पूर्ण,	/* M-Series only */
	[NITIO_G1_ABZ]		= अणु 0x1c2, 2 पूर्ण,	/* M-Series only */
	[NITIO_G0_INT_ACK]	= अणु NISTC_INTA_ACK_REG, 2 पूर्ण,
	[NITIO_G1_INT_ACK]	= अणु NISTC_INTB_ACK_REG, 2 पूर्ण,
	[NITIO_G0_STATUS]	= अणु NISTC_AI_STATUS1_REG, 2 पूर्ण,
	[NITIO_G1_STATUS]	= अणु NISTC_AO_STATUS1_REG, 2 पूर्ण,
	[NITIO_G0_INT_ENA]	= अणु NISTC_INTA_ENA_REG, 2 पूर्ण,
	[NITIO_G1_INT_ENA]	= अणु NISTC_INTB_ENA_REG, 2 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक ni_gpct_to_stc_रेजिस्टर(काष्ठा comedi_device *dev,
					    क्रमागत ni_gpct_रेजिस्टर reg)
अणु
	स्थिर काष्ठा mio_regmap *regmap;

	अगर (reg < ARRAY_SIZE(ni_gpct_to_stc_regmap)) अणु
		regmap = &ni_gpct_to_stc_regmap[reg];
	पूर्ण अन्यथा अणु
		dev_warn(dev->class_dev, "%s: unhandled register=0x%x\n",
			 __func__, reg);
		वापस 0;
	पूर्ण

	वापस regmap->mio_reg;
पूर्ण

अटल व्योम ni_gpct_ग_लिखो_रेजिस्टर(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक bits,
				   क्रमागत ni_gpct_रेजिस्टर reg)
अणु
	काष्ठा comedi_device *dev = counter->counter_dev->dev;
	अचिन्हित पूर्णांक stc_रेजिस्टर = ni_gpct_to_stc_रेजिस्टर(dev, reg);

	अगर (stc_रेजिस्टर == 0)
		वापस;

	चयन (reg) अणु
		/* m-series only रेजिस्टरs */
	हाल NITIO_G0_CNT_MODE:
	हाल NITIO_G1_CNT_MODE:
	हाल NITIO_G0_GATE2:
	हाल NITIO_G1_GATE2:
	हाल NITIO_G0_DMA_CFG:
	हाल NITIO_G1_DMA_CFG:
	हाल NITIO_G0_ABZ:
	हाल NITIO_G1_ABZ:
		ni_ग_लिखोw(dev, bits, stc_रेजिस्टर);
		अवरोध;

		/* 32 bit रेजिस्टरs */
	हाल NITIO_G0_LOADA:
	हाल NITIO_G1_LOADA:
	हाल NITIO_G0_LOADB:
	हाल NITIO_G1_LOADB:
		ni_stc_ग_लिखोl(dev, bits, stc_रेजिस्टर);
		अवरोध;

		/* 16 bit रेजिस्टरs */
	हाल NITIO_G0_INT_ENA:
		ni_set_bitfield(dev, stc_रेजिस्टर,
				NISTC_INTA_ENA_G0_GATE | NISTC_INTA_ENA_G0_TC,
				bits);
		अवरोध;
	हाल NITIO_G1_INT_ENA:
		ni_set_bitfield(dev, stc_रेजिस्टर,
				NISTC_INTB_ENA_G1_GATE | NISTC_INTB_ENA_G1_TC,
				bits);
		अवरोध;
	शेष:
		ni_stc_ग_लिखोw(dev, bits, stc_रेजिस्टर);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ni_gpct_पढ़ो_रेजिस्टर(काष्ठा ni_gpct *counter,
					  क्रमागत ni_gpct_रेजिस्टर reg)
अणु
	काष्ठा comedi_device *dev = counter->counter_dev->dev;
	अचिन्हित पूर्णांक stc_रेजिस्टर = ni_gpct_to_stc_रेजिस्टर(dev, reg);

	अगर (stc_रेजिस्टर == 0)
		वापस 0;

	चयन (reg) अणु
		/* m-series only रेजिस्टरs */
	हाल NITIO_G0_DMA_STATUS:
	हाल NITIO_G1_DMA_STATUS:
		वापस ni_पढ़ोw(dev, stc_रेजिस्टर);

		/* 32 bit रेजिस्टरs */
	हाल NITIO_G0_HW_SAVE:
	हाल NITIO_G1_HW_SAVE:
	हाल NITIO_G0_SW_SAVE:
	हाल NITIO_G1_SW_SAVE:
		वापस ni_stc_पढ़ोl(dev, stc_रेजिस्टर);

		/* 16 bit रेजिस्टरs */
	शेष:
		वापस ni_stc_पढ़ोw(dev, stc_रेजिस्टर);
	पूर्ण
पूर्ण

अटल पूर्णांक ni_freq_out_insn_पढ़ो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक val = NISTC_CLK_FOUT_TO_DIVIDER(devpriv->घड़ी_and_fout);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++)
		data[i] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_freq_out_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (insn->n) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];

		devpriv->घड़ी_and_fout &= ~NISTC_CLK_FOUT_ENA;
		ni_stc_ग_लिखोw(dev, devpriv->घड़ी_and_fout, NISTC_CLK_FOUT_REG);
		devpriv->घड़ी_and_fout &= ~NISTC_CLK_FOUT_DIVIDER_MASK;

		/* use the last data value to set the fout भागider */
		devpriv->घड़ी_and_fout |= NISTC_CLK_FOUT_DIVIDER(val);

		devpriv->घड़ी_and_fout |= NISTC_CLK_FOUT_ENA;
		ni_stc_ग_लिखोw(dev, devpriv->घड़ी_and_fout, NISTC_CLK_FOUT_REG);
	पूर्ण
	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_freq_out_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		चयन (data[1]) अणु
		हाल NI_FREQ_OUT_TIMEBASE_1_DIV_2_CLOCK_SRC:
			devpriv->घड़ी_and_fout &= ~NISTC_CLK_FOUT_TIMEBASE_SEL;
			अवरोध;
		हाल NI_FREQ_OUT_TIMEBASE_2_CLOCK_SRC:
			devpriv->घड़ी_and_fout |= NISTC_CLK_FOUT_TIMEBASE_SEL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		ni_stc_ग_लिखोw(dev, devpriv->घड़ी_and_fout, NISTC_CLK_FOUT_REG);
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		अगर (devpriv->घड़ी_and_fout & NISTC_CLK_FOUT_TIMEBASE_SEL) अणु
			data[1] = NI_FREQ_OUT_TIMEBASE_2_CLOCK_SRC;
			data[2] = TIMEBASE_2_NS;
		पूर्ण अन्यथा अणु
			data[1] = NI_FREQ_OUT_TIMEBASE_1_DIV_2_CLOCK_SRC;
			data[2] = TIMEBASE_1_NS * 2;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_8255_callback(काष्ठा comedi_device *dev,
			    पूर्णांक dir, पूर्णांक port, पूर्णांक data, अचिन्हित दीर्घ iobase)
अणु
	अगर (dir) अणु
		ni_ग_लिखोb(dev, data, iobase + 2 * port);
		वापस 0;
	पूर्ण

	वापस ni_पढ़ोb(dev, iobase + 2 * port);
पूर्ण

अटल पूर्णांक ni_get_pwm_config(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	data[1] = devpriv->pwm_up_count * devpriv->घड़ी_ns;
	data[2] = devpriv->pwm_करोwn_count * devpriv->घड़ी_ns;
	वापस 3;
पूर्ण

अटल पूर्णांक ni_m_series_pwm_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक up_count, करोwn_count;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_PWM_OUTPUT:
		चयन (data[1]) अणु
		हाल CMDF_ROUND_NEAREST:
			up_count = DIV_ROUND_CLOSEST(data[2],
						     devpriv->घड़ी_ns);
			अवरोध;
		हाल CMDF_ROUND_DOWN:
			up_count = data[2] / devpriv->घड़ी_ns;
			अवरोध;
		हाल CMDF_ROUND_UP:
			up_count =
			    DIV_ROUND_UP(data[2], devpriv->घड़ी_ns);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		चयन (data[3]) अणु
		हाल CMDF_ROUND_NEAREST:
			करोwn_count = DIV_ROUND_CLOSEST(data[4],
						       devpriv->घड़ी_ns);
			अवरोध;
		हाल CMDF_ROUND_DOWN:
			करोwn_count = data[4] / devpriv->घड़ी_ns;
			अवरोध;
		हाल CMDF_ROUND_UP:
			करोwn_count =
			    DIV_ROUND_UP(data[4], devpriv->घड़ी_ns);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (up_count * devpriv->घड़ी_ns != data[2] ||
		    करोwn_count * devpriv->घड़ी_ns != data[4]) अणु
			data[2] = up_count * devpriv->घड़ी_ns;
			data[4] = करोwn_count * devpriv->घड़ी_ns;
			वापस -EAGAIN;
		पूर्ण
		ni_ग_लिखोl(dev, NI_M_CAL_PWM_HIGH_TIME(up_count) |
			       NI_M_CAL_PWM_LOW_TIME(करोwn_count),
			  NI_M_CAL_PWM_REG);
		devpriv->pwm_up_count = up_count;
		devpriv->pwm_करोwn_count = करोwn_count;
		वापस 5;
	हाल INSN_CONFIG_GET_PWM_OUTPUT:
		वापस ni_get_pwm_config(dev, data);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ni_6143_pwm_config(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक up_count, करोwn_count;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_PWM_OUTPUT:
		चयन (data[1]) अणु
		हाल CMDF_ROUND_NEAREST:
			up_count = DIV_ROUND_CLOSEST(data[2],
						     devpriv->घड़ी_ns);
			अवरोध;
		हाल CMDF_ROUND_DOWN:
			up_count = data[2] / devpriv->घड़ी_ns;
			अवरोध;
		हाल CMDF_ROUND_UP:
			up_count =
			    DIV_ROUND_UP(data[2], devpriv->घड़ी_ns);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		चयन (data[3]) अणु
		हाल CMDF_ROUND_NEAREST:
			करोwn_count = DIV_ROUND_CLOSEST(data[4],
						       devpriv->घड़ी_ns);
			अवरोध;
		हाल CMDF_ROUND_DOWN:
			करोwn_count = data[4] / devpriv->घड़ी_ns;
			अवरोध;
		हाल CMDF_ROUND_UP:
			करोwn_count =
			    DIV_ROUND_UP(data[4], devpriv->घड़ी_ns);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (up_count * devpriv->घड़ी_ns != data[2] ||
		    करोwn_count * devpriv->घड़ी_ns != data[4]) अणु
			data[2] = up_count * devpriv->घड़ी_ns;
			data[4] = करोwn_count * devpriv->घड़ी_ns;
			वापस -EAGAIN;
		पूर्ण
		ni_ग_लिखोl(dev, up_count, NI6143_CALIB_HI_TIME_REG);
		devpriv->pwm_up_count = up_count;
		ni_ग_लिखोl(dev, करोwn_count, NI6143_CALIB_LO_TIME_REG);
		devpriv->pwm_करोwn_count = करोwn_count;
		वापस 5;
	हाल INSN_CONFIG_GET_PWM_OUTPUT:
		वापस ni_get_pwm_config(dev, data);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pack_mb88341(पूर्णांक addr, पूर्णांक val, पूर्णांक *bitstring)
अणु
	/*
	 * Fujitsu MB 88341
	 * Note that address bits are reversed.  Thanks to
	 * Ingo Keen क्रम noticing this.
	 *
	 * Note also that the 88341 expects address values from
	 * 1-12, whereas we use channel numbers 0-11.  The NI
	 * करोcs use 1-12, also, so be careful here.
	 */
	addr++;
	*bitstring = ((addr & 0x1) << 11) |
	    ((addr & 0x2) << 9) |
	    ((addr & 0x4) << 7) | ((addr & 0x8) << 5) | (val & 0xff);
	वापस 12;
पूर्ण

अटल पूर्णांक pack_dac8800(पूर्णांक addr, पूर्णांक val, पूर्णांक *bitstring)
अणु
	*bitstring = ((addr & 0x7) << 8) | (val & 0xff);
	वापस 11;
पूर्ण

अटल पूर्णांक pack_dac8043(पूर्णांक addr, पूर्णांक val, पूर्णांक *bitstring)
अणु
	*bitstring = val & 0xfff;
	वापस 12;
पूर्ण

अटल पूर्णांक pack_ad8522(पूर्णांक addr, पूर्णांक val, पूर्णांक *bitstring)
अणु
	*bitstring = (val & 0xfff) | (addr ? 0xc000 : 0xa000);
	वापस 16;
पूर्ण

अटल पूर्णांक pack_ad8804(पूर्णांक addr, पूर्णांक val, पूर्णांक *bitstring)
अणु
	*bitstring = ((addr & 0xf) << 8) | (val & 0xff);
	वापस 12;
पूर्ण

अटल पूर्णांक pack_ad8842(पूर्णांक addr, पूर्णांक val, पूर्णांक *bitstring)
अणु
	*bitstring = ((addr + 1) << 8) | (val & 0xff);
	वापस 12;
पूर्ण

काष्ठा caldac_काष्ठा अणु
	पूर्णांक n_chans;
	पूर्णांक n_bits;
	पूर्णांक (*packbits)(पूर्णांक address, पूर्णांक value, पूर्णांक *bitstring);
पूर्ण;

अटल काष्ठा caldac_काष्ठा caldacs[] = अणु
	[mb88341] = अणु12, 8, pack_mb88341पूर्ण,
	[dac8800] = अणु8, 8, pack_dac8800पूर्ण,
	[dac8043] = अणु1, 12, pack_dac8043पूर्ण,
	[ad8522] = अणु2, 12, pack_ad8522पूर्ण,
	[ad8804] = अणु12, 8, pack_ad8804पूर्ण,
	[ad8842] = अणु8, 8, pack_ad8842पूर्ण,
	[ad8804_debug] = अणु16, 8, pack_ad8804पूर्ण,
पूर्ण;

अटल व्योम ni_ग_लिखो_caldac(काष्ठा comedi_device *dev, पूर्णांक addr, पूर्णांक val)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक loadbit = 0, bits = 0, bit, bitstring = 0;
	अचिन्हित पूर्णांक cmd;
	पूर्णांक i;
	पूर्णांक type;

	अगर (devpriv->caldacs[addr] == val)
		वापस;
	devpriv->caldacs[addr] = val;

	क्रम (i = 0; i < 3; i++) अणु
		type = board->caldac[i];
		अगर (type == caldac_none)
			अवरोध;
		अगर (addr < caldacs[type].n_chans) अणु
			bits = caldacs[type].packbits(addr, val, &bitstring);
			loadbit = NI_E_SERIAL_CMD_DAC_LD(i);
			अवरोध;
		पूर्ण
		addr -= caldacs[type].n_chans;
	पूर्ण

	/* bits will be 0 अगर there is no caldac क्रम the given addr */
	अगर (bits == 0)
		वापस;

	क्रम (bit = 1 << (bits - 1); bit; bit >>= 1) अणु
		cmd = (bit & bitstring) ? NI_E_SERIAL_CMD_SDATA : 0;
		ni_ग_लिखोb(dev, cmd, NI_E_SERIAL_CMD_REG);
		udelay(1);
		ni_ग_लिखोb(dev, NI_E_SERIAL_CMD_SCLK | cmd, NI_E_SERIAL_CMD_REG);
		udelay(1);
	पूर्ण
	ni_ग_लिखोb(dev, loadbit, NI_E_SERIAL_CMD_REG);
	udelay(1);
	ni_ग_लिखोb(dev, 0, NI_E_SERIAL_CMD_REG);
पूर्ण

अटल पूर्णांक ni_calib_insn_ग_लिखो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अगर (insn->n) अणु
		/* only bother writing the last sample to the channel */
		ni_ग_लिखो_caldac(dev, CR_CHAN(insn->chanspec),
				data[insn->n - 1]);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_calib_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++)
		data[0] = devpriv->caldacs[CR_CHAN(insn->chanspec)];

	वापस insn->n;
पूर्ण

अटल व्योम caldac_setup(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक i, j;
	पूर्णांक n_dacs;
	पूर्णांक n_chans = 0;
	पूर्णांक n_bits;
	पूर्णांक dअगरfbits = 0;
	पूर्णांक type;
	पूर्णांक chan;

	type = board->caldac[0];
	अगर (type == caldac_none)
		वापस;
	n_bits = caldacs[type].n_bits;
	क्रम (i = 0; i < 3; i++) अणु
		type = board->caldac[i];
		अगर (type == caldac_none)
			अवरोध;
		अगर (caldacs[type].n_bits != n_bits)
			dअगरfbits = 1;
		n_chans += caldacs[type].n_chans;
	पूर्ण
	n_dacs = i;
	s->n_chan = n_chans;

	अगर (dअगरfbits) अणु
		अचिन्हित पूर्णांक *maxdata_list = devpriv->caldac_maxdata_list;

		अगर (n_chans > MAX_N_CALDACS)
			dev_err(dev->class_dev,
				"BUG! MAX_N_CALDACS too small\n");
		s->maxdata_list = maxdata_list;
		chan = 0;
		क्रम (i = 0; i < n_dacs; i++) अणु
			type = board->caldac[i];
			क्रम (j = 0; j < caldacs[type].n_chans; j++) अणु
				maxdata_list[chan] =
				    (1 << caldacs[type].n_bits) - 1;
				chan++;
			पूर्ण
		पूर्ण

		क्रम (chan = 0; chan < s->n_chan; chan++)
			ni_ग_लिखो_caldac(dev, i, s->maxdata_list[i] / 2);
	पूर्ण अन्यथा अणु
		type = board->caldac[0];
		s->maxdata = (1 << caldacs[type].n_bits) - 1;

		क्रम (chan = 0; chan < s->n_chan; chan++)
			ni_ग_लिखो_caldac(dev, i, s->maxdata / 2);
	पूर्ण
पूर्ण

अटल पूर्णांक ni_पढ़ो_eeprom(काष्ठा comedi_device *dev, पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक cmd = NI_E_SERIAL_CMD_EEPROM_CS;
	पूर्णांक bit;
	पूर्णांक bitstring;

	bitstring = 0x0300 | ((addr & 0x100) << 3) | (addr & 0xff);
	ni_ग_लिखोb(dev, cmd, NI_E_SERIAL_CMD_REG);
	क्रम (bit = 0x8000; bit; bit >>= 1) अणु
		अगर (bit & bitstring)
			cmd |= NI_E_SERIAL_CMD_SDATA;
		अन्यथा
			cmd &= ~NI_E_SERIAL_CMD_SDATA;

		ni_ग_लिखोb(dev, cmd, NI_E_SERIAL_CMD_REG);
		ni_ग_लिखोb(dev, NI_E_SERIAL_CMD_SCLK | cmd, NI_E_SERIAL_CMD_REG);
	पूर्ण
	cmd = NI_E_SERIAL_CMD_EEPROM_CS;
	bitstring = 0;
	क्रम (bit = 0x80; bit; bit >>= 1) अणु
		ni_ग_लिखोb(dev, cmd, NI_E_SERIAL_CMD_REG);
		ni_ग_लिखोb(dev, NI_E_SERIAL_CMD_SCLK | cmd, NI_E_SERIAL_CMD_REG);
		अगर (ni_पढ़ोb(dev, NI_E_STATUS_REG) & NI_E_STATUS_PROMOUT)
			bitstring |= bit;
	पूर्ण
	ni_ग_लिखोb(dev, 0, NI_E_SERIAL_CMD_REG);

	वापस bitstring;
पूर्ण

अटल पूर्णांक ni_eeprom_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक i;

	अगर (insn->n) अणु
		val = ni_पढ़ो_eeprom(dev, CR_CHAN(insn->chanspec));
		क्रम (i = 0; i < insn->n; i++)
			data[i] = val;
	पूर्ण
	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_m_series_eeprom_insn_पढ़ो(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					काष्ठा comedi_insn *insn,
					अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++)
		data[i] = devpriv->eeprom_buffer[CR_CHAN(insn->chanspec)];

	वापस insn->n;
पूर्ण

अटल अचिन्हित पूर्णांक ni_old_get_pfi_routing(काष्ठा comedi_device *dev,
					   अचिन्हित पूर्णांक chan)
अणु
	/*  pre-m-series boards have fixed संकेतs on pfi pins */
	चयन (chan) अणु
	हाल 0:
		वापस NI_PFI_OUTPUT_AI_START1;
	हाल 1:
		वापस NI_PFI_OUTPUT_AI_START2;
	हाल 2:
		वापस NI_PFI_OUTPUT_AI_CONVERT;
	हाल 3:
		वापस NI_PFI_OUTPUT_G_SRC1;
	हाल 4:
		वापस NI_PFI_OUTPUT_G_GATE1;
	हाल 5:
		वापस NI_PFI_OUTPUT_AO_UPDATE_N;
	हाल 6:
		वापस NI_PFI_OUTPUT_AO_START1;
	हाल 7:
		वापस NI_PFI_OUTPUT_AI_START_PULSE;
	हाल 8:
		वापस NI_PFI_OUTPUT_G_SRC0;
	हाल 9:
		वापस NI_PFI_OUTPUT_G_GATE0;
	शेष:
		dev_err(dev->class_dev, "bug, unhandled case in switch.\n");
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ni_old_set_pfi_routing(काष्ठा comedi_device *dev,
				  अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक source)
अणु
	/*  pre-m-series boards have fixed संकेतs on pfi pins */
	अगर (source != ni_old_get_pfi_routing(dev, chan))
		वापस -EINVAL;
	वापस 2;
पूर्ण

अटल अचिन्हित पूर्णांक ni_m_series_get_pfi_routing(काष्ठा comedi_device *dev,
						अचिन्हित पूर्णांक chan)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	स्थिर अचिन्हित पूर्णांक array_offset = chan / 3;

	वापस NI_M_PFI_OUT_SEL_TO_SRC(chan,
				devpriv->pfi_output_select_reg[array_offset]);
पूर्ण

अटल पूर्णांक ni_m_series_set_pfi_routing(काष्ठा comedi_device *dev,
				       अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक source)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक index = chan / 3;
	अचिन्हित लघु val = devpriv->pfi_output_select_reg[index];

	अगर ((source & 0x1f) != source)
		वापस -EINVAL;

	val &= ~NI_M_PFI_OUT_SEL_MASK(chan);
	val |= NI_M_PFI_OUT_SEL(chan, source);
	ni_ग_लिखोw(dev, val, NI_M_PFI_OUT_SEL_REG(index));
	devpriv->pfi_output_select_reg[index] = val;

	वापस 2;
पूर्ण

अटल अचिन्हित पूर्णांक ni_get_pfi_routing(काष्ठा comedi_device *dev,
				       अचिन्हित पूर्णांक chan)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (chan >= NI_PFI(0)) अणु
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);
	पूर्ण
	वापस (devpriv->is_m_series)
			? ni_m_series_get_pfi_routing(dev, chan)
			: ni_old_get_pfi_routing(dev, chan);
पूर्ण

/* Sets the output mux क्रम the specअगरied PFI channel. */
अटल पूर्णांक ni_set_pfi_routing(काष्ठा comedi_device *dev,
			      अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक source)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (chan >= NI_PFI(0)) अणु
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);
	पूर्ण
	वापस (devpriv->is_m_series)
			? ni_m_series_set_pfi_routing(dev, chan, source)
			: ni_old_set_pfi_routing(dev, chan, source);
पूर्ण

अटल पूर्णांक ni_config_pfi_filter(काष्ठा comedi_device *dev,
				अचिन्हित पूर्णांक chan,
				क्रमागत ni_pfi_filter_select filter)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक bits;

	अगर (!devpriv->is_m_series)
		वापस -ENOTSUPP;

	अगर (chan >= NI_PFI(0)) अणु
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);
	पूर्ण

	bits = ni_पढ़ोl(dev, NI_M_PFI_FILTER_REG);
	bits &= ~NI_M_PFI_FILTER_SEL_MASK(chan);
	bits |= NI_M_PFI_FILTER_SEL(chan, filter);
	ni_ग_लिखोl(dev, bits, NI_M_PFI_FILTER_REG);
	वापस 0;
पूर्ण

अटल व्योम ni_set_pfi_direction(काष्ठा comedi_device *dev, पूर्णांक chan,
				 अचिन्हित पूर्णांक direction)
अणु
	अगर (chan >= NI_PFI(0)) अणु
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);
	पूर्ण
	direction = (direction == COMEDI_OUTPUT) ? 1u : 0u;
	ni_set_bits(dev, NISTC_IO_BIसूची_PIN_REG, 1 << chan, direction);
पूर्ण

अटल पूर्णांक ni_get_pfi_direction(काष्ठा comedi_device *dev, पूर्णांक chan)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (chan >= NI_PFI(0)) अणु
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);
	पूर्ण
	वापस devpriv->io_bidirection_pin_reg & (1 << chan) ?
	       COMEDI_OUTPUT : COMEDI_INPUT;
पूर्ण

अटल पूर्णांक ni_pfi_insn_config(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan;

	अगर (insn->n < 1)
		वापस -EINVAL;

	chan = CR_CHAN(insn->chanspec);

	चयन (data[0]) अणु
	हाल COMEDI_OUTPUT:
	हाल COMEDI_INPUT:
		ni_set_pfi_direction(dev, chan, data[0]);
		अवरोध;
	हाल INSN_CONFIG_DIO_QUERY:
		data[1] = ni_get_pfi_direction(dev, chan);
		अवरोध;
	हाल INSN_CONFIG_SET_ROUTING:
		वापस ni_set_pfi_routing(dev, chan, data[1]);
	हाल INSN_CONFIG_GET_ROUTING:
		data[1] = ni_get_pfi_routing(dev, chan);
		अवरोध;
	हाल INSN_CONFIG_FILTER:
		वापस ni_config_pfi_filter(dev, chan, data[1]);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ni_pfi_insn_bits(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s,
			    काष्ठा comedi_insn *insn,
			    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (!devpriv->is_m_series)
		वापस -ENOTSUPP;

	अगर (comedi_dio_update_state(s, data))
		ni_ग_लिखोw(dev, s->state, NI_M_PFI_DO_REG);

	data[1] = ni_पढ़ोw(dev, NI_M_PFI_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक cs5529_रुको_क्रम_idle(काष्ठा comedi_device *dev)
अणु
	अचिन्हित लघु status;
	स्थिर पूर्णांक समयout = HZ;
	पूर्णांक i;

	क्रम (i = 0; i < समयout; i++) अणु
		status = ni_ao_win_inw(dev, NI67XX_CAL_STATUS_REG);
		अगर ((status & NI67XX_CAL_STATUS_BUSY) == 0)
			अवरोध;
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (schedule_समयout(1))
			वापस -EIO;
	पूर्ण
	अगर (i == समयout) अणु
		dev_err(dev->class_dev, "timeout\n");
		वापस -ETIME;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cs5529_command(काष्ठा comedi_device *dev, अचिन्हित लघु value)
अणु
	अटल स्थिर पूर्णांक समयout = 100;
	पूर्णांक i;

	ni_ao_win_outw(dev, value, NI67XX_CAL_CMD_REG);
	/* give समय क्रम command to start being serially घड़ीed पूर्णांकo cs5529.
	 * this insures that the NI67XX_CAL_STATUS_BUSY bit will get properly
	 * set beक्रमe we निकास this function.
	 */
	क्रम (i = 0; i < समयout; i++) अणु
		अगर (ni_ao_win_inw(dev, NI67XX_CAL_STATUS_REG) &
		    NI67XX_CAL_STATUS_BUSY)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i == समयout)
		dev_err(dev->class_dev,
			"possible problem - never saw adc go busy?\n");
पूर्ण

अटल पूर्णांक cs5529_करो_conversion(काष्ठा comedi_device *dev,
				अचिन्हित लघु *data)
अणु
	पूर्णांक retval;
	अचिन्हित लघु status;

	cs5529_command(dev, CS5529_CMD_CB | CS5529_CMD_SINGLE_CONV);
	retval = cs5529_रुको_क्रम_idle(dev);
	अगर (retval) अणु
		dev_err(dev->class_dev,
			"timeout or signal in %s()\n", __func__);
		वापस -ETIME;
	पूर्ण
	status = ni_ao_win_inw(dev, NI67XX_CAL_STATUS_REG);
	अगर (status & NI67XX_CAL_STATUS_OSC_DETECT) अणु
		dev_err(dev->class_dev,
			"cs5529 conversion error, status CSS_OSC_DETECT\n");
		वापस -EIO;
	पूर्ण
	अगर (status & NI67XX_CAL_STATUS_OVERRANGE) अणु
		dev_err(dev->class_dev,
			"cs5529 conversion error, overrange (ignoring)\n");
	पूर्ण
	अगर (data) अणु
		*data = ni_ao_win_inw(dev, NI67XX_CAL_DATA_REG);
		/* cs5529 वापसs 16 bit चिन्हित data in bipolar mode */
		*data ^= BIT(15);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs5529_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक n, retval;
	अचिन्हित लघु sample;
	अचिन्हित पूर्णांक channel_select;
	स्थिर अचिन्हित पूर्णांक INTERNAL_REF = 0x1000;

	/*
	 * Set calibration adc source.  Docs lie, reference select bits 8 to 11
	 * करो nothing. bit 12 seems to chooses पूर्णांकernal reference voltage, bit
	 * 13 causes the adc input to go overrange (maybe पढ़ोs बाह्यal
	 * reference?)
	 */
	अगर (insn->chanspec & CR_ALT_SOURCE)
		channel_select = INTERNAL_REF;
	अन्यथा
		channel_select = CR_CHAN(insn->chanspec);
	ni_ao_win_outw(dev, channel_select, NI67XX_AO_CAL_CHAN_SEL_REG);

	क्रम (n = 0; n < insn->n; n++) अणु
		retval = cs5529_करो_conversion(dev, &sample);
		अगर (retval < 0)
			वापस retval;
		data[n] = sample;
	पूर्ण
	वापस insn->n;
पूर्ण

अटल व्योम cs5529_config_ग_लिखो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक value,
				अचिन्हित पूर्णांक reg_select_bits)
अणु
	ni_ao_win_outw(dev, (value >> 16) & 0xff, NI67XX_CAL_CFG_HI_REG);
	ni_ao_win_outw(dev, value & 0xffff, NI67XX_CAL_CFG_LO_REG);
	reg_select_bits &= CS5529_CMD_REG_MASK;
	cs5529_command(dev, CS5529_CMD_CB | reg_select_bits);
	अगर (cs5529_रुको_क्रम_idle(dev))
		dev_err(dev->class_dev,
			"timeout or signal in %s\n", __func__);
पूर्ण

अटल पूर्णांक init_cs5529(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक config_bits = CS5529_CFG_PORT_FLAG |
				   CS5529_CFG_WORD_RATE_2180;

#अगर 1
	/* करो self-calibration */
	cs5529_config_ग_लिखो(dev, config_bits | CS5529_CFG_CALIB_BOTH_SELF,
			    CS5529_CFG_REG);
	/* need to क्रमce a conversion क्रम calibration to run */
	cs5529_करो_conversion(dev, शून्य);
#अन्यथा
	/* क्रमce gain calibration to 1 */
	cs5529_config_ग_लिखो(dev, 0x400000, CS5529_GAIN_REG);
	cs5529_config_ग_लिखो(dev, config_bits | CS5529_CFG_CALIB_OFFSET_SELF,
			    CS5529_CFG_REG);
	अगर (cs5529_रुको_क्रम_idle(dev))
		dev_err(dev->class_dev,
			"timeout or signal in %s\n", __func__);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Find best multiplier/भागider to try and get the PLL running at 80 MHz
 * given an arbitrary frequency input घड़ी.
 */
अटल पूर्णांक ni_mseries_get_pll_parameters(अचिन्हित पूर्णांक reference_period_ns,
					 अचिन्हित पूर्णांक *freq_भागider,
					 अचिन्हित पूर्णांक *freq_multiplier,
					 अचिन्हित पूर्णांक *actual_period_ns)
अणु
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक best_भाग = 1;
	अचिन्हित पूर्णांक mult;
	अचिन्हित पूर्णांक best_mult = 1;
	अटल स्थिर अचिन्हित पूर्णांक pico_per_nano = 1000;
	स्थिर अचिन्हित पूर्णांक reference_picosec = reference_period_ns *
					       pico_per_nano;
	/*
	 * m-series wants the phased-locked loop to output 80MHz, which is
	 * भागided by 4 to 20 MHz क्रम most timing घड़ीs
	 */
	अटल स्थिर अचिन्हित पूर्णांक target_picosec = 12500;
	पूर्णांक best_period_picosec = 0;

	क्रम (भाग = 1; भाग <= NI_M_PLL_MAX_DIVISOR; ++भाग) अणु
		क्रम (mult = 1; mult <= NI_M_PLL_MAX_MULTIPLIER; ++mult) अणु
			अचिन्हित पूर्णांक new_period_ps =
			    (reference_picosec * भाग) / mult;
			अगर (असल(new_period_ps - target_picosec) <
			    असल(best_period_picosec - target_picosec)) अणु
				best_period_picosec = new_period_ps;
				best_भाग = भाग;
				best_mult = mult;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (best_period_picosec == 0)
		वापस -EIO;

	*freq_भागider = best_भाग;
	*freq_multiplier = best_mult;
	/* वापस the actual period (* fudge factor क्रम 80 to 20 MHz) */
	*actual_period_ns = DIV_ROUND_CLOSEST(best_period_picosec * 4,
					      pico_per_nano);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_mseries_set_pll_master_घड़ी(काष्ठा comedi_device *dev,
					   अचिन्हित पूर्णांक source,
					   अचिन्हित पूर्णांक period_ns)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अटल स्थिर अचिन्हित पूर्णांक min_period_ns = 50;
	अटल स्थिर अचिन्हित पूर्णांक max_period_ns = 1000;
	अटल स्थिर अचिन्हित पूर्णांक समयout = 1000;
	अचिन्हित पूर्णांक pll_control_bits;
	अचिन्हित पूर्णांक freq_भागider;
	अचिन्हित पूर्णांक freq_multiplier;
	अचिन्हित पूर्णांक rtsi;
	अचिन्हित पूर्णांक i;
	पूर्णांक retval;

	अगर (source == NI_MIO_PLL_PXI10_CLOCK)
		period_ns = 100;
	/*
	 * These limits are somewhat arbitrary, but NI advertises 1 to 20MHz
	 * range so we'll use that.
	 */
	अगर (period_ns < min_period_ns || period_ns > max_period_ns) अणु
		dev_err(dev->class_dev,
			"%s: you must specify an input clock frequency between %i and %i nanosec for the phased-lock loop\n",
			__func__, min_period_ns, max_period_ns);
		वापस -EINVAL;
	पूर्ण
	devpriv->rtsi_trig_direction_reg &= ~NISTC_RTSI_TRIG_USE_CLK;
	ni_stc_ग_लिखोw(dev, devpriv->rtsi_trig_direction_reg,
		      NISTC_RTSI_TRIG_सूची_REG);
	pll_control_bits = NI_M_PLL_CTRL_ENA | NI_M_PLL_CTRL_VCO_MODE_75_150MHZ;
	devpriv->घड़ी_and_fout2 |= NI_M_CLK_FOUT2_TIMEBASE1_PLL |
				    NI_M_CLK_FOUT2_TIMEBASE3_PLL;
	devpriv->घड़ी_and_fout2 &= ~NI_M_CLK_FOUT2_PLL_SRC_MASK;
	चयन (source) अणु
	हाल NI_MIO_PLL_PXI_STAR_TRIGGER_CLOCK:
		devpriv->घड़ी_and_fout2 |= NI_M_CLK_FOUT2_PLL_SRC_STAR;
		अवरोध;
	हाल NI_MIO_PLL_PXI10_CLOCK:
		/* pxi घड़ी is 10MHz */
		devpriv->घड़ी_and_fout2 |= NI_M_CLK_FOUT2_PLL_SRC_PXI10;
		अवरोध;
	शेष:
		क्रम (rtsi = 0; rtsi <= NI_M_MAX_RTSI_CHAN; ++rtsi) अणु
			अगर (source == NI_MIO_PLL_RTSI_CLOCK(rtsi)) अणु
				devpriv->घड़ी_and_fout2 |=
					NI_M_CLK_FOUT2_PLL_SRC_RTSI(rtsi);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (rtsi > NI_M_MAX_RTSI_CHAN)
			वापस -EINVAL;
		अवरोध;
	पूर्ण
	retval = ni_mseries_get_pll_parameters(period_ns,
					       &freq_भागider,
					       &freq_multiplier,
					       &devpriv->घड़ी_ns);
	अगर (retval < 0) अणु
		dev_err(dev->class_dev,
			"bug, failed to find pll parameters\n");
		वापस retval;
	पूर्ण

	ni_ग_लिखोw(dev, devpriv->घड़ी_and_fout2, NI_M_CLK_FOUT2_REG);
	pll_control_bits |= NI_M_PLL_CTRL_DIVISOR(freq_भागider) |
			    NI_M_PLL_CTRL_MULTIPLIER(freq_multiplier);

	ni_ग_लिखोw(dev, pll_control_bits, NI_M_PLL_CTRL_REG);
	devpriv->घड़ी_source = source;
	/* it takes a few hundred microseconds क्रम PLL to lock */
	क्रम (i = 0; i < समयout; ++i) अणु
		अगर (ni_पढ़ोw(dev, NI_M_PLL_STATUS_REG) & NI_M_PLL_STATUS_LOCKED)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i == समयout) अणु
		dev_err(dev->class_dev,
			"%s: timed out waiting for PLL to lock to reference clock source %i with period %i ns\n",
			__func__, source, period_ns);
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 3;
पूर्ण

अटल पूर्णांक ni_set_master_घड़ी(काष्ठा comedi_device *dev,
			       अचिन्हित पूर्णांक source, अचिन्हित पूर्णांक period_ns)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (source == NI_MIO_INTERNAL_CLOCK) अणु
		devpriv->rtsi_trig_direction_reg &= ~NISTC_RTSI_TRIG_USE_CLK;
		ni_stc_ग_लिखोw(dev, devpriv->rtsi_trig_direction_reg,
			      NISTC_RTSI_TRIG_सूची_REG);
		devpriv->घड़ी_ns = TIMEBASE_1_NS;
		अगर (devpriv->is_m_series) अणु
			devpriv->घड़ी_and_fout2 &=
			    ~(NI_M_CLK_FOUT2_TIMEBASE1_PLL |
			      NI_M_CLK_FOUT2_TIMEBASE3_PLL);
			ni_ग_लिखोw(dev, devpriv->घड़ी_and_fout2,
				  NI_M_CLK_FOUT2_REG);
			ni_ग_लिखोw(dev, 0, NI_M_PLL_CTRL_REG);
		पूर्ण
		devpriv->घड़ी_source = source;
	पूर्ण अन्यथा अणु
		अगर (devpriv->is_m_series) अणु
			वापस ni_mseries_set_pll_master_घड़ी(dev, source,
							       period_ns);
		पूर्ण अन्यथा अणु
			अगर (source == NI_MIO_RTSI_CLOCK) अणु
				devpriv->rtsi_trig_direction_reg |=
				    NISTC_RTSI_TRIG_USE_CLK;
				ni_stc_ग_लिखोw(dev,
					      devpriv->rtsi_trig_direction_reg,
					      NISTC_RTSI_TRIG_सूची_REG);
				अगर (period_ns == 0) अणु
					dev_err(dev->class_dev,
						"we don't handle an unspecified clock period correctly yet, returning error\n");
					वापस -EINVAL;
				पूर्ण
				devpriv->घड़ी_ns = period_ns;
				devpriv->घड़ी_source = source;
			पूर्ण अन्यथा अणु
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 3;
पूर्ण

अटल पूर्णांक ni_valid_rtsi_output_source(काष्ठा comedi_device *dev,
				       अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक source)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (chan >= NISTC_RTSI_TRIG_NUM_CHAN(devpriv->is_m_series)) अणु
		अगर (chan == NISTC_RTSI_TRIG_OLD_CLK_CHAN) अणु
			अगर (source == NI_RTSI_OUTPUT_RTSI_OSC)
				वापस 1;

			dev_err(dev->class_dev,
				"%s: invalid source for channel=%i, channel %i is always the RTSI clock for pre-m-series boards\n",
				__func__, chan, NISTC_RTSI_TRIG_OLD_CLK_CHAN);
			वापस 0;
		पूर्ण
		वापस 0;
	पूर्ण
	चयन (source) अणु
	हाल NI_RTSI_OUTPUT_ADR_START1:
	हाल NI_RTSI_OUTPUT_ADR_START2:
	हाल NI_RTSI_OUTPUT_SCLKG:
	हाल NI_RTSI_OUTPUT_DACUPDN:
	हाल NI_RTSI_OUTPUT_DA_START1:
	हाल NI_RTSI_OUTPUT_G_SRC0:
	हाल NI_RTSI_OUTPUT_G_GATE0:
	हाल NI_RTSI_OUTPUT_RGOUT0:
	हाल NI_RTSI_OUTPUT_RTSI_BRD(0):
	हाल NI_RTSI_OUTPUT_RTSI_BRD(1):
	हाल NI_RTSI_OUTPUT_RTSI_BRD(2):
	हाल NI_RTSI_OUTPUT_RTSI_BRD(3):
		वापस 1;
	हाल NI_RTSI_OUTPUT_RTSI_OSC:
		वापस (devpriv->is_m_series) ? 1 : 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ni_set_rtsi_routing(काष्ठा comedi_device *dev,
			       अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक src)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (chan >= TRIGGER_LINE(0))
		/* allow new and old names of rtsi channels to work. */
		chan -= TRIGGER_LINE(0);

	अगर (ni_valid_rtsi_output_source(dev, chan, src) == 0)
		वापस -EINVAL;
	अगर (chan < 4) अणु
		devpriv->rtsi_trig_a_output_reg &= ~NISTC_RTSI_TRIG_MASK(chan);
		devpriv->rtsi_trig_a_output_reg |= NISTC_RTSI_TRIG(chan, src);
		ni_stc_ग_लिखोw(dev, devpriv->rtsi_trig_a_output_reg,
			      NISTC_RTSI_TRIGA_OUT_REG);
	पूर्ण अन्यथा अगर (chan < NISTC_RTSI_TRIG_NUM_CHAN(devpriv->is_m_series)) अणु
		devpriv->rtsi_trig_b_output_reg &= ~NISTC_RTSI_TRIG_MASK(chan);
		devpriv->rtsi_trig_b_output_reg |= NISTC_RTSI_TRIG(chan, src);
		ni_stc_ग_लिखोw(dev, devpriv->rtsi_trig_b_output_reg,
			      NISTC_RTSI_TRIGB_OUT_REG);
	पूर्ण अन्यथा अगर (chan != NISTC_RTSI_TRIG_OLD_CLK_CHAN) अणु
		/* probably should never reach this, since the
		 * ni_valid_rtsi_output_source above errors out अगर chan is too
		 * high
		 */
		dev_err(dev->class_dev, "%s: unknown rtsi channel\n", __func__);
		वापस -EINVAL;
	पूर्ण
	वापस 2;
पूर्ण

अटल अचिन्हित पूर्णांक ni_get_rtsi_routing(काष्ठा comedi_device *dev,
					अचिन्हित पूर्णांक chan)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (chan >= TRIGGER_LINE(0))
		/* allow new and old names of rtsi channels to work. */
		chan -= TRIGGER_LINE(0);

	अगर (chan < 4) अणु
		वापस NISTC_RTSI_TRIG_TO_SRC(chan,
					      devpriv->rtsi_trig_a_output_reg);
	पूर्ण अन्यथा अगर (chan < NISTC_RTSI_TRIG_NUM_CHAN(devpriv->is_m_series)) अणु
		वापस NISTC_RTSI_TRIG_TO_SRC(chan,
					      devpriv->rtsi_trig_b_output_reg);
	पूर्ण अन्यथा अगर (chan == NISTC_RTSI_TRIG_OLD_CLK_CHAN) अणु
		वापस NI_RTSI_OUTPUT_RTSI_OSC;
	पूर्ण

	dev_err(dev->class_dev, "%s: unknown rtsi channel\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल व्योम ni_set_rtsi_direction(काष्ठा comedi_device *dev, पूर्णांक chan,
				  अचिन्हित पूर्णांक direction)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक max_chan = NISTC_RTSI_TRIG_NUM_CHAN(devpriv->is_m_series);

	अगर (chan >= TRIGGER_LINE(0))
		/* allow new and old names of rtsi channels to work. */
		chan -= TRIGGER_LINE(0);

	अगर (direction == COMEDI_OUTPUT) अणु
		अगर (chan < max_chan) अणु
			devpriv->rtsi_trig_direction_reg |=
			    NISTC_RTSI_TRIG_सूची(chan, devpriv->is_m_series);
		पूर्ण अन्यथा अगर (chan == NISTC_RTSI_TRIG_OLD_CLK_CHAN) अणु
			devpriv->rtsi_trig_direction_reg |=
			    NISTC_RTSI_TRIG_DRV_CLK;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chan < max_chan) अणु
			devpriv->rtsi_trig_direction_reg &=
			    ~NISTC_RTSI_TRIG_सूची(chan, devpriv->is_m_series);
		पूर्ण अन्यथा अगर (chan == NISTC_RTSI_TRIG_OLD_CLK_CHAN) अणु
			devpriv->rtsi_trig_direction_reg &=
			    ~NISTC_RTSI_TRIG_DRV_CLK;
		पूर्ण
	पूर्ण
	ni_stc_ग_लिखोw(dev, devpriv->rtsi_trig_direction_reg,
		      NISTC_RTSI_TRIG_सूची_REG);
पूर्ण

अटल पूर्णांक ni_get_rtsi_direction(काष्ठा comedi_device *dev, पूर्णांक chan)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक max_chan = NISTC_RTSI_TRIG_NUM_CHAN(devpriv->is_m_series);

	अगर (chan >= TRIGGER_LINE(0))
		/* allow new and old names of rtsi channels to work. */
		chan -= TRIGGER_LINE(0);

	अगर (chan < max_chan) अणु
		वापस (devpriv->rtsi_trig_direction_reg &
			NISTC_RTSI_TRIG_सूची(chan, devpriv->is_m_series))
			   ? COMEDI_OUTPUT : COMEDI_INPUT;
	पूर्ण अन्यथा अगर (chan == NISTC_RTSI_TRIG_OLD_CLK_CHAN) अणु
		वापस (devpriv->rtsi_trig_direction_reg &
			NISTC_RTSI_TRIG_DRV_CLK)
			   ? COMEDI_OUTPUT : COMEDI_INPUT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ni_rtsi_insn_config(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	चयन (data[0]) अणु
	हाल COMEDI_OUTPUT:
	हाल COMEDI_INPUT:
		ni_set_rtsi_direction(dev, chan, data[0]);
		अवरोध;
	हाल INSN_CONFIG_DIO_QUERY: अणु
		पूर्णांक ret = ni_get_rtsi_direction(dev, chan);

		अगर (ret < 0)
			वापस ret;
		data[1] = ret;
		वापस 2;
	पूर्ण
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		वापस ni_set_master_घड़ी(dev, data[1], data[2]);
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		data[1] = devpriv->घड़ी_source;
		data[2] = devpriv->घड़ी_ns;
		वापस 3;
	हाल INSN_CONFIG_SET_ROUTING:
		वापस ni_set_rtsi_routing(dev, chan, data[1]);
	हाल INSN_CONFIG_GET_ROUTING: अणु
		पूर्णांक ret = ni_get_rtsi_routing(dev, chan);

		अगर (ret < 0)
			वापस ret;
		data[1] = ret;
		वापस 2;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक ni_rtsi_insn_bits(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	data[1] = 0;

	वापस insn->n;
पूर्ण

/*
 * Default routing क्रम RTSI trigger lines.
 *
 * These values are used here in the init function, as well as in the
 * disconnect_route function, after a RTSI route has been disconnected.
 */
अटल स्थिर पूर्णांक शेष_rtsi_routing[] = अणु
	[0] = NI_RTSI_OUTPUT_ADR_START1,
	[1] = NI_RTSI_OUTPUT_ADR_START2,
	[2] = NI_RTSI_OUTPUT_SCLKG,
	[3] = NI_RTSI_OUTPUT_DACUPDN,
	[4] = NI_RTSI_OUTPUT_DA_START1,
	[5] = NI_RTSI_OUTPUT_G_SRC0,
	[6] = NI_RTSI_OUTPUT_G_GATE0,
	[7] = NI_RTSI_OUTPUT_RTSI_OSC,
पूर्ण;

/*
 * Route संकेतs through RGOUT0 terminal.
 * @reg: raw रेजिस्टर value of RGOUT0 bits (only bit0 is important).
 * @dev: comedi device handle.
 */
अटल व्योम set_rgout0_reg(पूर्णांक reg, काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (devpriv->is_m_series) अणु
		devpriv->rtsi_trig_direction_reg &=
			~NISTC_RTSI_TRIG_सूची_SUB_SEL1;
		devpriv->rtsi_trig_direction_reg |=
			(reg << NISTC_RTSI_TRIG_सूची_SUB_SEL1_SHIFT) &
			NISTC_RTSI_TRIG_सूची_SUB_SEL1;
		ni_stc_ग_लिखोw(dev, devpriv->rtsi_trig_direction_reg,
			      NISTC_RTSI_TRIG_सूची_REG);
	पूर्ण अन्यथा अणु
		devpriv->rtsi_trig_b_output_reg &= ~NISTC_RTSI_TRIGB_SUB_SEL1;
		devpriv->rtsi_trig_b_output_reg |=
			(reg << NISTC_RTSI_TRIGB_SUB_SEL1_SHIFT) &
			NISTC_RTSI_TRIGB_SUB_SEL1;
		ni_stc_ग_लिखोw(dev, devpriv->rtsi_trig_b_output_reg,
			      NISTC_RTSI_TRIGB_OUT_REG);
	पूर्ण
पूर्ण

अटल पूर्णांक get_rgout0_reg(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक reg;

	अगर (devpriv->is_m_series)
		reg = (devpriv->rtsi_trig_direction_reg &
		       NISTC_RTSI_TRIG_सूची_SUB_SEL1)
		    >> NISTC_RTSI_TRIG_सूची_SUB_SEL1_SHIFT;
	अन्यथा
		reg = (devpriv->rtsi_trig_b_output_reg &
		       NISTC_RTSI_TRIGB_SUB_SEL1)
		    >> NISTC_RTSI_TRIGB_SUB_SEL1_SHIFT;
	वापस reg;
पूर्ण

अटल अंतरभूत पूर्णांक get_rgout0_src(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक reg = get_rgout0_reg(dev);

	वापस ni_find_route_source(reg, NI_RGOUT0, &devpriv->routing_tables);
पूर्ण

/*
 * Route संकेतs through RGOUT0 terminal and increment the RGOUT0 use क्रम this
 * particular route.
 * @src: device-global संकेत name
 * @dev: comedi device handle
 *
 * Return: -EINVAL अगर the source is not valid to route to RGOUT0;
 *	   -EBUSY अगर the RGOUT0 is alपढ़ोy used;
 *	   0 अगर successful.
 */
अटल पूर्णांक incr_rgout0_src_use(पूर्णांक src, काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	s8 reg = ni_lookup_route_रेजिस्टर(CR_CHAN(src), NI_RGOUT0,
					  &devpriv->routing_tables);

	अगर (reg < 0)
		वापस -EINVAL;

	अगर (devpriv->rgout0_usage > 0 && get_rgout0_reg(dev) != reg)
		वापस -EBUSY;

	++devpriv->rgout0_usage;
	set_rgout0_reg(reg, dev);
	वापस 0;
पूर्ण

/*
 * Unroute संकेतs through RGOUT0 terminal and deccrement the RGOUT0 use क्रम
 * this particular source.  This function करोes not actually unroute anything
 * with respect to RGOUT0.  It करोes, on the other hand, decrement the usage
 * counter क्रम the current src->RGOUT0 mapping.
 *
 * Return: -EINVAL अगर the source is not alपढ़ोy routed to RGOUT0 (or usage is
 *	alपढ़ोy at zero); 0 अगर successful.
 */
अटल पूर्णांक decr_rgout0_src_use(पूर्णांक src, काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	s8 reg = ni_lookup_route_रेजिस्टर(CR_CHAN(src), NI_RGOUT0,
					  &devpriv->routing_tables);

	अगर (devpriv->rgout0_usage > 0 && get_rgout0_reg(dev) == reg) अणु
		--devpriv->rgout0_usage;
		अगर (!devpriv->rgout0_usage)
			set_rgout0_reg(0, dev); /* ok शेष? */
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Route संकेतs through given NI_RTSI_BRD mux.
 * @i: index of mux to route
 * @reg: raw रेजिस्टर value of RTSI_BRD bits
 * @dev: comedi device handle
 */
अटल व्योम set_ith_rtsi_brd_reg(पूर्णांक i, पूर्णांक reg, काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक reg_i_sz = 3; /* value क्रम e-series */
	पूर्णांक reg_i_mask;
	पूर्णांक reg_i_shअगरt;

	अगर (devpriv->is_m_series)
		reg_i_sz = 4;
	reg_i_mask = ~((~0) << reg_i_sz);
	reg_i_shअगरt = i * reg_i_sz;

	/* clear out the current reg_i क्रम ith brd */
	devpriv->rtsi_shared_mux_reg &= ~(reg_i_mask       << reg_i_shअगरt);
	/* (softcopy) ग_लिखो the new reg_i क्रम ith brd */
	devpriv->rtsi_shared_mux_reg |= (reg & reg_i_mask) << reg_i_shअगरt;
	/* (hardcopy) ग_लिखो the new reg_i क्रम ith brd */
	ni_stc_ग_लिखोw(dev, devpriv->rtsi_shared_mux_reg, NISTC_RTSI_BOARD_REG);
पूर्ण

अटल पूर्णांक get_ith_rtsi_brd_reg(पूर्णांक i, काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक reg_i_sz = 3; /* value क्रम e-series */
	पूर्णांक reg_i_mask;
	पूर्णांक reg_i_shअगरt;

	अगर (devpriv->is_m_series)
		reg_i_sz = 4;
	reg_i_mask = ~((~0) << reg_i_sz);
	reg_i_shअगरt = i * reg_i_sz;

	वापस (devpriv->rtsi_shared_mux_reg >> reg_i_shअगरt) & reg_i_mask;
पूर्ण

अटल अंतरभूत पूर्णांक get_rtsi_brd_src(पूर्णांक brd, काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक brd_index = brd;
	पूर्णांक reg;

	अगर (brd >= NI_RTSI_BRD(0))
		brd_index = brd - NI_RTSI_BRD(0);
	अन्यथा
		brd = NI_RTSI_BRD(brd);
	/*
	 * And now:
	 * brd : device-global name
	 * brd_index : index number of RTSI_BRD mux
	 */

	reg = get_ith_rtsi_brd_reg(brd_index, dev);

	वापस ni_find_route_source(reg, brd, &devpriv->routing_tables);
पूर्ण

/*
 * Route संकेतs through NI_RTSI_BRD mux and increment the use counter क्रम this
 * particular route.
 *
 * Return: -EINVAL अगर the source is not valid to route to NI_RTSI_BRD(i);
 *	   -EBUSY अगर all NI_RTSI_BRD muxes are alपढ़ोy used;
 *	   NI_RTSI_BRD(i) of allocated ith mux अगर successful.
 */
अटल पूर्णांक incr_rtsi_brd_src_use(पूर्णांक src, काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक first_available = -1;
	पूर्णांक err = -EINVAL;
	s8 reg;
	पूर्णांक i;

	/* first look क्रम a mux that is alपढ़ोy configured to provide src */
	क्रम (i = 0; i < NUM_RTSI_SHARED_MUXS; ++i) अणु
		reg = ni_lookup_route_रेजिस्टर(CR_CHAN(src), NI_RTSI_BRD(i),
					       &devpriv->routing_tables);

		अगर (reg < 0)
			जारी; /* invalid route */

		अगर (!devpriv->rtsi_shared_mux_usage[i]) अणु
			अगर (first_available < 0)
				/* found the first unused, but usable mux */
				first_available = i;
		पूर्ण अन्यथा अणु
			/*
			 * we've seen at least one possible route, so change the
			 * final error to -EBUSY in हाल there are no muxes
			 * available.
			 */
			err = -EBUSY;

			अगर (get_ith_rtsi_brd_reg(i, dev) == reg) अणु
				/*
				 * we've found a mux that is alपढ़ोy being used
				 * to provide the requested संकेत.  Reuse it.
				 */
				जाओ success;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (first_available < 0)
		वापस err;

	/* we did not find a mux to reuse, but there is at least one usable */
	i = first_available;

success:
	++devpriv->rtsi_shared_mux_usage[i];
	set_ith_rtsi_brd_reg(i, reg, dev);
	वापस NI_RTSI_BRD(i);
पूर्ण

/*
 * Unroute संकेतs through NI_RTSI_BRD mux and decrement the user counter क्रम
 * this particular route.
 *
 * Return: -EINVAL अगर the source is not alपढ़ोy routed to rtsi_brd(i) (or usage
 *	is alपढ़ोy at zero); 0 अगर successful.
 */
अटल पूर्णांक decr_rtsi_brd_src_use(पूर्णांक src, पूर्णांक rtsi_brd,
				 काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	s8 reg = ni_lookup_route_रेजिस्टर(CR_CHAN(src), rtsi_brd,
					  &devpriv->routing_tables);
	स्थिर पूर्णांक i = rtsi_brd - NI_RTSI_BRD(0);

	अगर (devpriv->rtsi_shared_mux_usage[i] > 0 &&
	    get_ith_rtsi_brd_reg(i, dev) == reg) अणु
		--devpriv->rtsi_shared_mux_usage[i];
		अगर (!devpriv->rtsi_shared_mux_usage[i])
			set_ith_rtsi_brd_reg(i, 0, dev); /* ok शेष? */
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम ni_rtsi_init(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	/*  Initialises the RTSI bus संकेत चयन to a शेष state */

	/*
	 * Use 10MHz instead of 20MHz क्रम RTSI घड़ी frequency. Appears
	 * to have no effect, at least on pxi-6281, which always uses
	 * 20MHz rtsi घड़ी frequency
	 */
	devpriv->घड़ी_and_fout2 = NI_M_CLK_FOUT2_RTSI_10MHZ;
	/*  Set घड़ी mode to पूर्णांकernal */
	अगर (ni_set_master_घड़ी(dev, NI_MIO_INTERNAL_CLOCK, 0) < 0)
		dev_err(dev->class_dev, "ni_set_master_clock failed, bug?\n");

	/* शेष पूर्णांकernal lines routing to RTSI bus lines */
	क्रम (i = 0; i < 8; ++i) अणु
		ni_set_rtsi_direction(dev, i, COMEDI_INPUT);
		ni_set_rtsi_routing(dev, i, शेष_rtsi_routing[i]);
	पूर्ण

	/*
	 * Sets the source and direction of the 4 on board lines.
	 * This configures all board lines to be:
	 * क्रम e-series:
	 *   1) inमाला_दो (not sure what "output" would mean)
	 *   2) copying TRIGGER_LINE(0) (or RTSI0) output
	 * क्रम m-series:
	 *   copying NI_PFI(0) output
	 */
	devpriv->rtsi_shared_mux_reg = 0;
	क्रम (i = 0; i < 4; ++i)
		set_ith_rtsi_brd_reg(i, 0, dev);
	स_रखो(devpriv->rtsi_shared_mux_usage, 0,
	       माप(devpriv->rtsi_shared_mux_usage));

	/* initialize rgout0 pin as unused. */
	devpriv->rgout0_usage = 0;
	set_rgout0_reg(0, dev);
पूर्ण

/* Get route of GPFO_i/CtrOut pins */
अटल अंतरभूत पूर्णांक ni_get_gout_routing(अचिन्हित पूर्णांक dest,
				      काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक reg = devpriv->an_trig_etc_reg;

	चयन (dest) अणु
	हाल 0:
		अगर (reg & NISTC_ATRIG_ETC_GPFO_0_ENA)
			वापस NISTC_ATRIG_ETC_GPFO_0_SEL_TO_SRC(reg);
		अवरोध;
	हाल 1:
		अगर (reg & NISTC_ATRIG_ETC_GPFO_1_ENA)
			वापस NISTC_ATRIG_ETC_GPFO_1_SEL_TO_SRC(reg);
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Set route of GPFO_i/CtrOut pins */
अटल अंतरभूत पूर्णांक ni_disable_gout_routing(अचिन्हित पूर्णांक dest,
					  काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	चयन (dest) अणु
	हाल 0:
		devpriv->an_trig_etc_reg &= ~NISTC_ATRIG_ETC_GPFO_0_ENA;
		अवरोध;
	हाल 1:
		devpriv->an_trig_etc_reg &= ~NISTC_ATRIG_ETC_GPFO_1_ENA;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ni_stc_ग_लिखोw(dev, devpriv->an_trig_etc_reg, NISTC_ATRIG_ETC_REG);
	वापस 0;
पूर्ण

/* Set route of GPFO_i/CtrOut pins */
अटल अंतरभूत पूर्णांक ni_set_gout_routing(अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dest,
				      काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	चयन (dest) अणु
	हाल 0:
		/* clear reg */
		devpriv->an_trig_etc_reg &= ~NISTC_ATRIG_ETC_GPFO_0_SEL(-1);
		/* set reg */
		devpriv->an_trig_etc_reg |= NISTC_ATRIG_ETC_GPFO_0_ENA
					 |  NISTC_ATRIG_ETC_GPFO_0_SEL(src);
		अवरोध;
	हाल 1:
		/* clear reg */
		devpriv->an_trig_etc_reg &= ~NISTC_ATRIG_ETC_GPFO_1_SEL;
		src = src ? NISTC_ATRIG_ETC_GPFO_1_SEL : 0;
		/* set reg */
		devpriv->an_trig_etc_reg |= NISTC_ATRIG_ETC_GPFO_1_ENA | src;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ni_stc_ग_लिखोw(dev, devpriv->an_trig_etc_reg, NISTC_ATRIG_ETC_REG);
	वापस 0;
पूर्ण

/*
 * Retrieves the current source of the output selector क्रम the given
 * destination.  If the terminal क्रम the destination is not alपढ़ोy configured
 * as an output, this function वापसs -EINVAL as error.
 *
 * Return: the रेजिस्टर value of the destination output selector;
 *	   -EINVAL अगर terminal is not configured क्रम output.
 */
अटल पूर्णांक get_output_select_source(पूर्णांक dest, काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	पूर्णांक reg = -1;

	अगर (channel_is_pfi(dest)) अणु
		अगर (ni_get_pfi_direction(dev, dest) == COMEDI_OUTPUT)
			reg = ni_get_pfi_routing(dev, dest);
	पूर्ण अन्यथा अगर (channel_is_rtsi(dest)) अणु
		अगर (ni_get_rtsi_direction(dev, dest) == COMEDI_OUTPUT) अणु
			reg = ni_get_rtsi_routing(dev, dest);

			अगर (reg == NI_RTSI_OUTPUT_RGOUT0) अणु
				dest = NI_RGOUT0; /* prepare क्रम lookup below */
				reg = get_rgout0_reg(dev);
			पूर्ण अन्यथा अगर (reg >= NI_RTSI_OUTPUT_RTSI_BRD(0) &&
				   reg <= NI_RTSI_OUTPUT_RTSI_BRD(3)) अणु
				स्थिर पूर्णांक i = reg - NI_RTSI_OUTPUT_RTSI_BRD(0);

				dest = NI_RTSI_BRD(i); /* prepare क्रम lookup */
				reg = get_ith_rtsi_brd_reg(i, dev);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (dest >= NI_CtrOut(0) && dest <= NI_CtrOut(-1)) अणु
		/*
		 * not handled by ni_tio.  Only available क्रम GPFO रेजिस्टरs in
		 * e/m series.
		 */
		dest -= NI_CtrOut(0);
		अगर (dest > 1)
			/* there are only two g_out outमाला_दो. */
			वापस -EINVAL;
		reg = ni_get_gout_routing(dest, dev);
	पूर्ण अन्यथा अगर (channel_is_ctr(dest)) अणु
		reg = ni_tio_get_routing(devpriv->counter_dev, dest);
	पूर्ण अन्यथा अणु
		dev_dbg(dev->class_dev, "%s: unhandled destination (%d) queried\n",
			__func__, dest);
	पूर्ण

	अगर (reg >= 0)
		वापस ni_find_route_source(CR_CHAN(reg), dest,
					    &devpriv->routing_tables);
	वापस -EINVAL;
पूर्ण

/*
 * Test a route:
 *
 * Return: -1 अगर not connectible;
 *	    0 अगर connectible and not connected;
 *	    1 अगर connectible and connected.
 */
अटल पूर्णांक test_route(अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dest,
		      काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	s8 reg = ni_route_to_रेजिस्टर(CR_CHAN(src), dest,
				      &devpriv->routing_tables);

	अगर (reg < 0)
		वापस -1;
	अगर (get_output_select_source(dest, dev) != CR_CHAN(src))
		वापस 0;
	वापस 1;
पूर्ण

/* Connect the actual route.  */
अटल पूर्णांक connect_route(अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dest,
			 काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	s8 reg = ni_route_to_रेजिस्टर(CR_CHAN(src), dest,
				      &devpriv->routing_tables);
	s8 current_src;

	अगर (reg < 0)
		/* route is not valid */
		वापस -EINVAL;

	current_src = get_output_select_source(dest, dev);
	अगर (current_src == CR_CHAN(src))
		वापस -EALREADY;
	अगर (current_src >= 0)
		/* destination mux is alपढ़ोy busy. complain, करोn't overग_लिखो */
		वापस -EBUSY;

	/* The route is valid and available. Now connect... */
	अगर (channel_is_pfi(dest)) अणु
		/* set routing source, then खोलो output */
		ni_set_pfi_routing(dev, dest, reg);
		ni_set_pfi_direction(dev, dest, COMEDI_OUTPUT);
	पूर्ण अन्यथा अगर (channel_is_rtsi(dest)) अणु
		अगर (reg == NI_RTSI_OUTPUT_RGOUT0) अणु
			पूर्णांक ret = incr_rgout0_src_use(src, dev);

			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अगर (ni_rtsi_route_requires_mux(reg)) अणु
			/* Attempt to allocate and  route (src->brd) */
			पूर्णांक brd = incr_rtsi_brd_src_use(src, dev);

			अगर (brd < 0)
				वापस brd;

			/* Now lookup the रेजिस्टर value क्रम (brd->dest) */
			reg = ni_lookup_route_रेजिस्टर(
				brd, dest, &devpriv->routing_tables);
		पूर्ण

		ni_set_rtsi_direction(dev, dest, COMEDI_OUTPUT);
		ni_set_rtsi_routing(dev, dest, reg);
	पूर्ण अन्यथा अगर (dest >= NI_CtrOut(0) && dest <= NI_CtrOut(-1)) अणु
		/*
		 * not handled by ni_tio.  Only available क्रम GPFO रेजिस्टरs in
		 * e/m series.
		 */
		dest -= NI_CtrOut(0);
		अगर (dest > 1)
			/* there are only two g_out outमाला_दो. */
			वापस -EINVAL;
		अगर (ni_set_gout_routing(src, dest, dev))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (channel_is_ctr(dest)) अणु
		/*
		 * we are adding back the channel modअगरier info to set
		 * invert/edge info passed by the user
		 */
		ni_tio_set_routing(devpriv->counter_dev, dest,
				   reg | (src & ~CR_CHAN(-1)));
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक disconnect_route(अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dest,
			    काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;
	s8 reg = ni_route_to_रेजिस्टर(CR_CHAN(src), dest,
				      &devpriv->routing_tables);

	अगर (reg < 0)
		/* route is not valid */
		वापस -EINVAL;
	अगर (get_output_select_source(dest, dev) != src)
		/* cannot disconnect something not connected */
		वापस -EINVAL;

	/* The route is valid and is connected.  Now disconnect... */
	अगर (channel_is_pfi(dest)) अणु
		/* set the pfi to high impedance, and disconnect */
		ni_set_pfi_direction(dev, dest, COMEDI_INPUT);
		ni_set_pfi_routing(dev, dest, NI_PFI_OUTPUT_PFI_DEFAULT);
	पूर्ण अन्यथा अगर (channel_is_rtsi(dest)) अणु
		अगर (reg == NI_RTSI_OUTPUT_RGOUT0) अणु
			पूर्णांक ret = decr_rgout0_src_use(src, dev);

			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अगर (ni_rtsi_route_requires_mux(reg)) अणु
			/* find which RTSI_BRD line is source क्रम rtsi pin */
			पूर्णांक brd = ni_find_route_source(
				ni_get_rtsi_routing(dev, dest), dest,
				&devpriv->routing_tables);

			अगर (brd < 0)
				वापस brd;

			/* decrement/disconnect RTSI_BRD line from source */
			decr_rtsi_brd_src_use(src, brd, dev);
		पूर्ण

		/* set rtsi output selector to शेष state */
		reg = शेष_rtsi_routing[dest - TRIGGER_LINE(0)];
		ni_set_rtsi_direction(dev, dest, COMEDI_INPUT);
		ni_set_rtsi_routing(dev, dest, reg);
	पूर्ण अन्यथा अगर (dest >= NI_CtrOut(0) && dest <= NI_CtrOut(-1)) अणु
		/*
		 * not handled by ni_tio.  Only available क्रम GPFO रेजिस्टरs in
		 * e/m series.
		 */
		dest -= NI_CtrOut(0);
		अगर (dest > 1)
			/* there are only two g_out outमाला_दो. */
			वापस -EINVAL;
		reg = ni_disable_gout_routing(dest, dev);
	पूर्ण अन्यथा अगर (channel_is_ctr(dest)) अणु
		ni_tio_unset_routing(devpriv->counter_dev, dest);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ni_global_insn_config(काष्ठा comedi_device *dev,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	चयन (data[0]) अणु
	हाल INSN_DEVICE_CONFIG_TEST_ROUTE:
		data[0] = test_route(data[1], data[2], dev);
		वापस 2;
	हाल INSN_DEVICE_CONFIG_CONNECT_ROUTE:
		वापस connect_route(data[1], data[2], dev);
	हाल INSN_DEVICE_CONFIG_DISCONNECT_ROUTE:
		वापस disconnect_route(data[1], data[2], dev);
	/*
	 * This हाल is alपढ़ोy handled one level up.
	 * हाल INSN_DEVICE_CONFIG_GET_ROUTES:
	 */
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 1;
पूर्ण

#अगर_घोषित PCIDMA
अटल पूर्णांक ni_gpct_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	पूर्णांक retval;

	retval = ni_request_gpct_mite_channel(dev, counter->counter_index,
					      COMEDI_INPUT);
	अगर (retval) अणु
		dev_err(dev->class_dev,
			"no dma channel available for use by counter\n");
		वापस retval;
	पूर्ण
	ni_tio_acknowledge(counter);
	ni_e_series_enable_second_irq(dev, counter->counter_index, 1);

	वापस ni_tio_cmd(dev, s);
पूर्ण

अटल पूर्णांक ni_gpct_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	पूर्णांक retval;

	retval = ni_tio_cancel(counter);
	ni_e_series_enable_second_irq(dev, counter->counter_index, 0);
	ni_release_gpct_mite_channel(dev, counter->counter_index);
	वापस retval;
पूर्ण
#पूर्ण_अगर

अटल irqवापस_t ni_E_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s_ai = dev->पढ़ो_subdev;
	काष्ठा comedi_subdevice *s_ao = dev->ग_लिखो_subdev;
	अचिन्हित लघु a_status;
	अचिन्हित लघु b_status;
	अचिन्हित दीर्घ flags;
#अगर_घोषित PCIDMA
	काष्ठा ni_निजी *devpriv = dev->निजी;
#पूर्ण_अगर

	अगर (!dev->attached)
		वापस IRQ_NONE;
	smp_mb();		/* make sure dev->attached is checked */

	/*  lock to aव्योम race with comedi_poll */
	spin_lock_irqsave(&dev->spinlock, flags);
	a_status = ni_stc_पढ़ोw(dev, NISTC_AI_STATUS1_REG);
	b_status = ni_stc_पढ़ोw(dev, NISTC_AO_STATUS1_REG);
#अगर_घोषित PCIDMA
	अगर (devpriv->mite) अणु
		अचिन्हित दीर्घ flags_too;

		spin_lock_irqsave(&devpriv->mite_channel_lock, flags_too);
		अगर (s_ai && devpriv->ai_mite_chan)
			mite_ack_linkc(devpriv->ai_mite_chan, s_ai, false);
		अगर (s_ao && devpriv->ao_mite_chan)
			mite_ack_linkc(devpriv->ao_mite_chan, s_ao, false);
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags_too);
	पूर्ण
#पूर्ण_अगर
	ack_a_पूर्णांकerrupt(dev, a_status);
	ack_b_पूर्णांकerrupt(dev, b_status);
	अगर (s_ai) अणु
		अगर (a_status & NISTC_AI_STATUS1_INTA)
			handle_a_पूर्णांकerrupt(dev, s_ai, a_status);
		/* handle any पूर्णांकerrupt or dma events */
		comedi_handle_events(dev, s_ai);
	पूर्ण
	अगर (s_ao) अणु
		अगर (b_status & NISTC_AO_STATUS1_INTB)
			handle_b_पूर्णांकerrupt(dev, s_ao, b_status);
		/* handle any पूर्णांकerrupt or dma events */
		comedi_handle_events(dev, s_ao);
	पूर्ण
	handle_gpct_पूर्णांकerrupt(dev, 0);
	handle_gpct_पूर्णांकerrupt(dev, 1);
#अगर_घोषित PCIDMA
	अगर (devpriv->is_m_series)
		handle_cdio_पूर्णांकerrupt(dev);
#पूर्ण_अगर

	spin_unlock_irqrestore(&dev->spinlock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ni_alloc_निजी(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	spin_lock_init(&devpriv->winकरोw_lock);
	spin_lock_init(&devpriv->soft_reg_copy_lock);
	spin_lock_init(&devpriv->mite_channel_lock);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक _ni_get_valid_routes(काष्ठा comedi_device *dev,
					 अचिन्हित पूर्णांक n_pairs,
					 अचिन्हित पूर्णांक *pair_data)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	वापस ni_get_valid_routes(&devpriv->routing_tables, n_pairs,
				   pair_data);
पूर्ण

अटल पूर्णांक ni_E_init(काष्ठा comedi_device *dev,
		     अचिन्हित पूर्णांक पूर्णांकerrupt_pin, अचिन्हित पूर्णांक irq_polarity)
अणु
	स्थिर काष्ठा ni_board_काष्ठा *board = dev->board_ptr;
	काष्ठा ni_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;
	पूर्णांक i;
	स्थिर अक्षर *dev_family = devpriv->is_m_series ? "ni_mseries"
						      : "ni_eseries";

	/* prepare the device क्रम globally-named routes. */
	अगर (ni_assign_device_routes(dev_family, board->name,
				    board->alt_route_name,
				    &devpriv->routing_tables) < 0) अणु
		dev_warn(dev->class_dev, "%s: %s device has no signal routing table.\n",
			 __func__, board->name);
		dev_warn(dev->class_dev, "%s: High level NI signal names will not be available for this %s board.\n",
			 __func__, board->name);
	पूर्ण अन्यथा अणु
		/*
		 * only(?) assign insn_device_config अगर we have global names क्रम
		 * this device.
		 */
		dev->insn_device_config = ni_global_insn_config;
		dev->get_valid_routes = _ni_get_valid_routes;
	पूर्ण

	अगर (board->n_aochan > MAX_N_AO_CHAN) अणु
		dev_err(dev->class_dev, "bug! n_aochan > MAX_N_AO_CHAN\n");
		वापस -EINVAL;
	पूर्ण

	/* initialize घड़ी भागiders */
	devpriv->घड़ी_and_fout = NISTC_CLK_FOUT_SLOW_DIV2 |
				  NISTC_CLK_FOUT_SLOW_TIMEBASE |
				  NISTC_CLK_FOUT_TO_BOARD_DIV2 |
				  NISTC_CLK_FOUT_TO_BOARD;
	अगर (!devpriv->is_6xxx) अणु
		/* BEAM is this needed क्रम PCI-6143 ?? */
		devpriv->घड़ी_and_fout |= (NISTC_CLK_FOUT_AI_OUT_DIV2 |
					    NISTC_CLK_FOUT_AO_OUT_DIV2);
	पूर्ण
	ni_stc_ग_लिखोw(dev, devpriv->घड़ी_and_fout, NISTC_CLK_FOUT_REG);

	ret = comedi_alloc_subdevices(dev, NI_NUM_SUBDEVICES);
	अगर (ret)
		वापस ret;

	/* Analog Input subdevice */
	s = &dev->subdevices[NI_AI_SUBDEV];
	अगर (board->n_adchan) अणु
		s->type		= COMEDI_SUBD_AI;
		s->subdev_flags	= SDF_READABLE | SDF_DIFF | SDF_DITHER;
		अगर (!devpriv->is_611x)
			s->subdev_flags	|= SDF_GROUND | SDF_COMMON | SDF_OTHER;
		अगर (board->ai_maxdata > 0xffff)
			s->subdev_flags	|= SDF_LSAMPL;
		अगर (devpriv->is_m_series)
			s->subdev_flags	|= SDF_SOFT_CALIBRATED;
		s->n_chan	= board->n_adchan;
		s->maxdata	= board->ai_maxdata;
		s->range_table	= ni_range_lkup[board->gainlkup];
		s->insn_पढ़ो	= ni_ai_insn_पढ़ो;
		s->insn_config	= ni_ai_insn_config;
		अगर (dev->irq) अणु
			dev->पढ़ो_subdev = s;
			s->subdev_flags	|= SDF_CMD_READ;
			s->len_chanlist	= 512;
			s->करो_cmdtest	= ni_ai_cmdtest;
			s->करो_cmd	= ni_ai_cmd;
			s->cancel	= ni_ai_reset;
			s->poll		= ni_ai_poll;
			s->munge	= ni_ai_munge;

			अगर (devpriv->mite)
				s->async_dma_dir = DMA_FROM_DEVICE;
		पूर्ण

		/* reset the analog input configuration */
		ni_ai_reset(dev, s);
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[NI_AO_SUBDEV];
	अगर (board->n_aochan) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_DEGLITCH | SDF_GROUND;
		अगर (devpriv->is_m_series)
			s->subdev_flags	|= SDF_SOFT_CALIBRATED;
		s->n_chan	= board->n_aochan;
		s->maxdata	= board->ao_maxdata;
		s->range_table	= board->ao_range_table;
		s->insn_config	= ni_ao_insn_config;
		s->insn_ग_लिखो	= ni_ao_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		/*
		 * Aदीर्घ with the IRQ we need either a FIFO or DMA क्रम
		 * async command support.
		 */
		अगर (dev->irq && (board->ao_fअगरo_depth || devpriv->mite)) अणु
			dev->ग_लिखो_subdev = s;
			s->subdev_flags	|= SDF_CMD_WRITE;
			s->len_chanlist	= s->n_chan;
			s->करो_cmdtest	= ni_ao_cmdtest;
			s->करो_cmd	= ni_ao_cmd;
			s->cancel	= ni_ao_reset;
			अगर (!devpriv->is_m_series)
				s->munge	= ni_ao_munge;

			अगर (devpriv->mite)
				s->async_dma_dir = DMA_TO_DEVICE;
		पूर्ण

		अगर (devpriv->is_67xx)
			init_ao_67xx(dev, s);

		/* reset the analog output configuration */
		ni_ao_reset(dev, s);
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Digital I/O subdevice */
	s = &dev->subdevices[NI_DIO_SUBDEV];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
	s->n_chan	= board->has_32dio_chan ? 32 : 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	अगर (devpriv->is_m_series) अणु
#अगर_घोषित PCIDMA
		s->subdev_flags	|= SDF_LSAMPL;
		s->insn_bits	= ni_m_series_dio_insn_bits;
		s->insn_config	= ni_m_series_dio_insn_config;
		अगर (dev->irq) अणु
			s->subdev_flags	|= SDF_CMD_WRITE /* | SDF_CMD_READ */;
			s->len_chanlist	= s->n_chan;
			s->करो_cmdtest	= ni_cdio_cmdtest;
			s->करो_cmd	= ni_cdio_cmd;
			s->cancel	= ni_cdio_cancel;

			/* M-series boards use DMA */
			s->async_dma_dir = DMA_BIसूचीECTIONAL;
		पूर्ण

		/* reset DIO and set all channels to inमाला_दो */
		ni_ग_लिखोl(dev, NI_M_CDO_CMD_RESET |
			       NI_M_CDI_CMD_RESET,
			  NI_M_CDIO_CMD_REG);
		ni_ग_लिखोl(dev, s->io_bits, NI_M_DIO_सूची_REG);
#पूर्ण_अगर /* PCIDMA */
	पूर्ण अन्यथा अणु
		s->insn_bits	= ni_dio_insn_bits;
		s->insn_config	= ni_dio_insn_config;

		/* set all channels to inमाला_दो */
		devpriv->dio_control = NISTC_DIO_CTRL_सूची(s->io_bits);
		ni_ग_लिखोw(dev, devpriv->dio_control, NISTC_DIO_CTRL_REG);
	पूर्ण

	/* 8255 device */
	s = &dev->subdevices[NI_8255_DIO_SUBDEV];
	अगर (board->has_8255) अणु
		ret = subdev_8255_init(dev, s, ni_8255_callback,
				       NI_E_8255_BASE);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* क्रमmerly general purpose counter/समयr device, but no दीर्घer used */
	s = &dev->subdevices[NI_UNUSED_SUBDEV];
	s->type = COMEDI_SUBD_UNUSED;

	/* Calibration subdevice */
	s = &dev->subdevices[NI_CALIBRATION_SUBDEV];
	s->type		= COMEDI_SUBD_CALIB;
	s->subdev_flags	= SDF_INTERNAL;
	s->n_chan	= 1;
	s->maxdata	= 0;
	अगर (devpriv->is_m_series) अणु
		/* पूर्णांकernal PWM output used क्रम AI nonlinearity calibration */
		s->insn_config	= ni_m_series_pwm_config;

		ni_ग_लिखोl(dev, 0x0, NI_M_CAL_PWM_REG);
	पूर्ण अन्यथा अगर (devpriv->is_6143) अणु
		/* पूर्णांकernal PWM output used क्रम AI nonlinearity calibration */
		s->insn_config	= ni_6143_pwm_config;
	पूर्ण अन्यथा अणु
		s->subdev_flags	|= SDF_WRITABLE;
		s->insn_पढ़ो	= ni_calib_insn_पढ़ो;
		s->insn_ग_लिखो	= ni_calib_insn_ग_लिखो;

		/* setup the caldacs and find the real n_chan and maxdata */
		caldac_setup(dev, s);
	पूर्ण

	/* EEPROM subdevice */
	s = &dev->subdevices[NI_EEPROM_SUBDEV];
	s->type		= COMEDI_SUBD_MEMORY;
	s->subdev_flags	= SDF_READABLE | SDF_INTERNAL;
	s->maxdata	= 0xff;
	अगर (devpriv->is_m_series) अणु
		s->n_chan	= M_SERIES_EEPROM_SIZE;
		s->insn_पढ़ो	= ni_m_series_eeprom_insn_पढ़ो;
	पूर्ण अन्यथा अणु
		s->n_chan	= 512;
		s->insn_पढ़ो	= ni_eeprom_insn_पढ़ो;
	पूर्ण

	/* Digital I/O (PFI) subdevice */
	s = &dev->subdevices[NI_PFI_DIO_SUBDEV];
	s->type		= COMEDI_SUBD_DIO;
	s->maxdata	= 1;
	अगर (devpriv->is_m_series) अणु
		s->n_chan	= 16;
		s->insn_bits	= ni_pfi_insn_bits;
		s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_INTERNAL;

		ni_ग_लिखोw(dev, s->state, NI_M_PFI_DO_REG);
		क्रम (i = 0; i < NUM_PFI_OUTPUT_SELECT_REGS; ++i) अणु
			ni_ग_लिखोw(dev, devpriv->pfi_output_select_reg[i],
				  NI_M_PFI_OUT_SEL_REG(i));
		पूर्ण
	पूर्ण अन्यथा अणु
		s->n_chan	= 10;
		s->subdev_flags	= SDF_INTERNAL;
	पूर्ण
	s->insn_config	= ni_pfi_insn_config;

	ni_set_bits(dev, NISTC_IO_BIसूची_PIN_REG, ~0, 0);

	/* cs5529 calibration adc */
	s = &dev->subdevices[NI_CS5529_CALIBRATION_SUBDEV];
	अगर (devpriv->is_67xx) अणु
		s->type = COMEDI_SUBD_AI;
		s->subdev_flags = SDF_READABLE | SDF_DIFF | SDF_INTERNAL;
		/*  one channel क्रम each analog output channel */
		s->n_chan = board->n_aochan;
		s->maxdata = BIT(16) - 1;
		s->range_table = &range_unknown;	/* XXX */
		s->insn_पढ़ो = cs5529_ai_insn_पढ़ो;
		s->insn_config = शून्य;
		init_cs5529(dev);
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Serial */
	s = &dev->subdevices[NI_SERIAL_SUBDEV];
	s->type = COMEDI_SUBD_SERIAL;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE | SDF_INTERNAL;
	s->n_chan = 1;
	s->maxdata = 0xff;
	s->insn_config = ni_serial_insn_config;
	devpriv->serial_पूर्णांकerval_ns = 0;
	devpriv->serial_hw_mode = 0;

	/* RTSI */
	s = &dev->subdevices[NI_RTSI_SUBDEV];
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE | SDF_INTERNAL;
	s->n_chan = 8;
	s->maxdata = 1;
	s->insn_bits = ni_rtsi_insn_bits;
	s->insn_config = ni_rtsi_insn_config;
	ni_rtsi_init(dev);

	/* allocate and initialize the gpct counter device */
	devpriv->counter_dev = ni_gpct_device_स्थिरruct(dev,
					ni_gpct_ग_लिखो_रेजिस्टर,
					ni_gpct_पढ़ो_रेजिस्टर,
					(devpriv->is_m_series)
						? ni_gpct_variant_m_series
						: ni_gpct_variant_e_series,
					NUM_GPCT,
					NUM_GPCT,
					&devpriv->routing_tables);
	अगर (!devpriv->counter_dev)
		वापस -ENOMEM;

	/* Counter (gpct) subdevices */
	क्रम (i = 0; i < NUM_GPCT; ++i) अणु
		काष्ठा ni_gpct *gpct = &devpriv->counter_dev->counters[i];

		/* setup and initialize the counter */
		ni_tio_init_counter(gpct);

		s = &dev->subdevices[NI_GPCT_SUBDEV(i)];
		s->type		= COMEDI_SUBD_COUNTER;
		s->subdev_flags	= SDF_READABLE | SDF_WRITABLE | SDF_LSAMPL;
		s->n_chan	= 3;
		s->maxdata	= (devpriv->is_m_series) ? 0xffffffff
							 : 0x00ffffff;
		s->insn_पढ़ो	= ni_tio_insn_पढ़ो;
		s->insn_ग_लिखो	= ni_tio_insn_ग_लिखो;
		s->insn_config	= ni_tio_insn_config;
#अगर_घोषित PCIDMA
		अगर (dev->irq && devpriv->mite) अणु
			s->subdev_flags	|= SDF_CMD_READ /* | SDF_CMD_WRITE */;
			s->len_chanlist	= 1;
			s->करो_cmdtest	= ni_tio_cmdtest;
			s->करो_cmd	= ni_gpct_cmd;
			s->cancel	= ni_gpct_cancel;

			s->async_dma_dir = DMA_BIसूचीECTIONAL;
		पूर्ण
#पूर्ण_अगर
		s->निजी	= gpct;
	पूर्ण

	/* Initialize GPFO_अणु0,1पूर्ण to produce output of counters */
	ni_set_gout_routing(0, 0, dev); /* output of counter 0; DAQ STC, p338 */
	ni_set_gout_routing(0, 1, dev); /* output of counter 1; DAQ STC, p338 */

	/* Frequency output subdevice */
	s = &dev->subdevices[NI_FREQ_OUT_SUBDEV];
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 1;
	s->maxdata	= 0xf;
	s->insn_पढ़ो	= ni_freq_out_insn_पढ़ो;
	s->insn_ग_लिखो	= ni_freq_out_insn_ग_लिखो;
	s->insn_config	= ni_freq_out_insn_config;

	अगर (dev->irq) अणु
		ni_stc_ग_लिखोw(dev,
			      (irq_polarity ? NISTC_INT_CTRL_INT_POL : 0) |
			      (NISTC_INT_CTRL_3PIN_INT & 0) |
			      NISTC_INT_CTRL_INTA_ENA |
			      NISTC_INT_CTRL_INTB_ENA |
			      NISTC_INT_CTRL_INTA_SEL(पूर्णांकerrupt_pin) |
			      NISTC_INT_CTRL_INTB_SEL(पूर्णांकerrupt_pin),
			      NISTC_INT_CTRL_REG);
	पूर्ण

	/* DMA setup */
	ni_ग_लिखोb(dev, devpriv->ai_ao_select_reg, NI_E_DMA_AI_AO_SEL_REG);
	ni_ग_लिखोb(dev, devpriv->g0_g1_select_reg, NI_E_DMA_G0_G1_SEL_REG);

	अगर (devpriv->is_6xxx) अणु
		ni_ग_लिखोb(dev, 0, NI611X_MAGIC_REG);
	पूर्ण अन्यथा अगर (devpriv->is_m_series) अणु
		पूर्णांक channel;

		क्रम (channel = 0; channel < board->n_aochan; ++channel) अणु
			ni_ग_लिखोb(dev, 0xf,
				  NI_M_AO_WAVEFORM_ORDER_REG(channel));
			ni_ग_लिखोb(dev, 0x0,
				  NI_M_AO_REF_ATTENUATION_REG(channel));
		पूर्ण
		ni_ग_लिखोb(dev, 0x0, NI_M_AO_CALIB_REG);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mio_common_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_निजी *devpriv = dev->निजी;

	अगर (devpriv)
		ni_gpct_device_destroy(devpriv->counter_dev);
पूर्ण
