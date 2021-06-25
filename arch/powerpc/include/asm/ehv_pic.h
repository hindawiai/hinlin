<शैली गुरु>
/*
 * EHV_PIC निजी definitions and काष्ठाure.
 *
 * Copyright 2008-2010 Freescale Semiconductor, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */
#अगर_अघोषित __EHV_PIC_H__
#घोषणा __EHV_PIC_H__

#समावेश <linux/irq.h>

#घोषणा NR_EHV_PIC_INTS 1024

#घोषणा EHV_PIC_INFO(name) EHV_PIC_##name

#घोषणा EHV_PIC_VECPRI_POLARITY_NEGATIVE 0
#घोषणा EHV_PIC_VECPRI_POLARITY_POSITIVE 1
#घोषणा EHV_PIC_VECPRI_SENSE_EDGE 0
#घोषणा EHV_PIC_VECPRI_SENSE_LEVEL 0x2
#घोषणा EHV_PIC_VECPRI_POLARITY_MASK 0x1
#घोषणा EHV_PIC_VECPRI_SENSE_MASK 0x2

काष्ठा ehv_pic अणु
	/* The remapper क्रम this EHV_PIC */
	काष्ठा irq_करोमुख्य	*irqhost;

	/* The "linux" controller काष्ठा */
	काष्ठा irq_chip	hc_irq;

	/* core पूर्णांक flag */
	पूर्णांक coreपूर्णांक_flag;
पूर्ण;

व्योम ehv_pic_init(व्योम);
अचिन्हित पूर्णांक ehv_pic_get_irq(व्योम);

#पूर्ण_अगर /* __EHV_PIC_H__ */
