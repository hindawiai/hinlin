<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Broadcom
 */

#अगर_अघोषित __SPI_BCM_QSPI_H__
#घोषणा __SPI_BCM_QSPI_H__

#समावेश <linux/types.h>
#समावेश <linux/पन.स>

/* BSPI पूर्णांकerrupt masks */
#घोषणा INTR_BSPI_LR_OVERREAD_MASK		BIT(4)
#घोषणा INTR_BSPI_LR_SESSION_DONE_MASK		BIT(3)
#घोषणा INTR_BSPI_LR_IMPATIENT_MASK		BIT(2)
#घोषणा INTR_BSPI_LR_SESSION_ABORTED_MASK	BIT(1)
#घोषणा INTR_BSPI_LR_FULLNESS_REACHED_MASK	BIT(0)

#घोषणा BSPI_LR_INTERRUPTS_DATA		       \
	(INTR_BSPI_LR_SESSION_DONE_MASK |	       \
	 INTR_BSPI_LR_FULLNESS_REACHED_MASK)

#घोषणा BSPI_LR_INTERRUPTS_ERROR               \
	(INTR_BSPI_LR_OVERREAD_MASK |	       \
	 INTR_BSPI_LR_IMPATIENT_MASK |	       \
	 INTR_BSPI_LR_SESSION_ABORTED_MASK)

#घोषणा BSPI_LR_INTERRUPTS_ALL                 \
	(BSPI_LR_INTERRUPTS_ERROR |	       \
	 BSPI_LR_INTERRUPTS_DATA)

/* MSPI Interrupt masks */
#घोषणा INTR_MSPI_HALTED_MASK			BIT(6)
#घोषणा INTR_MSPI_DONE_MASK			BIT(5)

#घोषणा MSPI_INTERRUPTS_ALL		       \
	(INTR_MSPI_DONE_MASK |		       \
	 INTR_MSPI_HALTED_MASK)

#घोषणा QSPI_INTERRUPTS_ALL                    \
	(MSPI_INTERRUPTS_ALL |		       \
	 BSPI_LR_INTERRUPTS_ALL)

काष्ठा platक्रमm_device;
काष्ठा dev_pm_ops;

क्रमागत अणु
	MSPI_DONE = 0x1,
	BSPI_DONE = 0x2,
	BSPI_ERR = 0x4,
	MSPI_BSPI_DONE = 0x7
पूर्ण;

काष्ठा bcm_qspi_soc_पूर्णांकc अणु
	व्योम (*bcm_qspi_पूर्णांक_ack)(काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc, पूर्णांक type);
	व्योम (*bcm_qspi_पूर्णांक_set)(काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc, पूर्णांक type,
				 bool en);
	u32 (*bcm_qspi_get_पूर्णांक_status)(काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc);
पूर्ण;

/* Read controller रेजिस्टर*/
अटल अंतरभूत u32 bcm_qspi_पढ़ोl(bool be, व्योम __iomem *addr)
अणु
	अगर (be)
		वापस ioपढ़ो32be(addr);
	अन्यथा
		वापस पढ़ोl_relaxed(addr);
पूर्ण

/* Write controller रेजिस्टर*/
अटल अंतरभूत व्योम bcm_qspi_ग_लिखोl(bool be,
				   अचिन्हित पूर्णांक data, व्योम __iomem *addr)
अणु
	अगर (be)
		ioग_लिखो32be(data, addr);
	अन्यथा
		ग_लिखोl_relaxed(data, addr);
पूर्ण

अटल अंतरभूत u32 get_qspi_mask(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल MSPI_DONE:
		वापस INTR_MSPI_DONE_MASK;
	हाल BSPI_DONE:
		वापस BSPI_LR_INTERRUPTS_ALL;
	हाल MSPI_BSPI_DONE:
		वापस QSPI_INTERRUPTS_ALL;
	हाल BSPI_ERR:
		वापस BSPI_LR_INTERRUPTS_ERROR;
	पूर्ण

	वापस 0;
पूर्ण

/* The common driver functions to be called by the SoC platक्रमm driver */
पूर्णांक bcm_qspi_probe(काष्ठा platक्रमm_device *pdev,
		   काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc);
पूर्णांक bcm_qspi_हटाओ(काष्ठा platक्रमm_device *pdev);

/* pm_ops used by the SoC platक्रमm driver called on PM suspend/resume */
बाह्य स्थिर काष्ठा dev_pm_ops bcm_qspi_pm_ops;

#पूर्ण_अगर /* __SPI_BCM_QSPI_H__ */
