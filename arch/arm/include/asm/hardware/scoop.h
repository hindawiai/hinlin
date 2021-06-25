<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Definitions क्रम the SCOOP पूर्णांकerface found on various Sharp PDAs
 *
 *  Copyright (c) 2004 Riअक्षरd Purdie
 */

#घोषणा SCOOP_MCR  0x00
#घोषणा SCOOP_CDR  0x04
#घोषणा SCOOP_CSR  0x08
#घोषणा SCOOP_CPR  0x0C
#घोषणा SCOOP_CCR  0x10
#घोषणा SCOOP_IRR  0x14
#घोषणा SCOOP_IRM  0x14
#घोषणा SCOOP_IMR  0x18
#घोषणा SCOOP_ISR  0x1C
#घोषणा SCOOP_GPCR 0x20
#घोषणा SCOOP_GPWR 0x24
#घोषणा SCOOP_GPRR 0x28

#घोषणा SCOOP_CPR_OUT	(1 << 7)
#घोषणा SCOOP_CPR_SD_3V	(1 << 2)
#घोषणा SCOOP_CPR_CF_XV	(1 << 1)
#घोषणा SCOOP_CPR_CF_3V	(1 << 0)

#घोषणा SCOOP_GPCR_PA22	(1 << 12)
#घोषणा SCOOP_GPCR_PA21	(1 << 11)
#घोषणा SCOOP_GPCR_PA20	(1 << 10)
#घोषणा SCOOP_GPCR_PA19	(1 << 9)
#घोषणा SCOOP_GPCR_PA18	(1 << 8)
#घोषणा SCOOP_GPCR_PA17	(1 << 7)
#घोषणा SCOOP_GPCR_PA16	(1 << 6)
#घोषणा SCOOP_GPCR_PA15	(1 << 5)
#घोषणा SCOOP_GPCR_PA14	(1 << 4)
#घोषणा SCOOP_GPCR_PA13	(1 << 3)
#घोषणा SCOOP_GPCR_PA12	(1 << 2)
#घोषणा SCOOP_GPCR_PA11	(1 << 1)

काष्ठा scoop_config अणु
	अचिन्हित लघु io_out;
	अचिन्हित लघु io_dir;
	अचिन्हित लघु suspend_clr;
	अचिन्हित लघु suspend_set;
	पूर्णांक gpio_base;
पूर्ण;

/* Structure क्रम linking scoop devices to PCMCIA sockets */
काष्ठा scoop_pcmcia_dev अणु
	काष्ठा device *dev;     /* Poपूर्णांकer to this socket's scoop device */
	पूर्णांक	irq;                /* irq क्रम socket */
	पूर्णांक cd_irq;
	स्थिर अक्षर *cd_irq_str;
	अचिन्हित अक्षर keep_vs;
	अचिन्हित अक्षर keep_rd;
पूर्ण;

काष्ठा scoop_pcmcia_config अणु
	काष्ठा scoop_pcmcia_dev *devs;
	पूर्णांक num_devs;
	व्योम (*घातer_ctrl)(काष्ठा device *scoop, अचिन्हित लघु cpr, पूर्णांक nr);
पूर्ण;

बाह्य काष्ठा scoop_pcmcia_config *platक्रमm_scoop_config;

व्योम reset_scoop(काष्ठा device *dev);
अचिन्हित लघु पढ़ो_scoop_reg(काष्ठा device *dev, अचिन्हित लघु reg);
व्योम ग_लिखो_scoop_reg(काष्ठा device *dev, अचिन्हित लघु reg, अचिन्हित लघु data);
