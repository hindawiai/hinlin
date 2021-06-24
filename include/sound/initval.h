<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_INITVAL_H
#घोषणा __SOUND_INITVAL_H

/*
 *  Init values क्रम soundcard modules
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#घोषणा SNDRV_AUTO_PORT		1
#घोषणा SNDRV_AUTO_IRQ		0xffff
#घोषणा SNDRV_AUTO_DMA		0xffff
#घोषणा SNDRV_AUTO_DMA_SIZE	(0x7fffffff)

#घोषणा SNDRV_DEFAULT_IDX1	(-1)
#घोषणा SNDRV_DEFAULT_STR1	शून्य
#घोषणा SNDRV_DEFAULT_ENABLE1	1
#घोषणा SNDRV_DEFAULT_PORT1	SNDRV_AUTO_PORT
#घोषणा SNDRV_DEFAULT_IRQ1	SNDRV_AUTO_IRQ
#घोषणा SNDRV_DEFAULT_DMA1	SNDRV_AUTO_DMA
#घोषणा SNDRV_DEFAULT_DMA_SIZE1	SNDRV_AUTO_DMA_SIZE
#घोषणा SNDRV_DEFAULT_PTR1	SNDRV_DEFAULT_STR1

#घोषणा SNDRV_DEFAULT_IDX	अणु [0 ... (SNDRV_CARDS-1)] = -1 पूर्ण
#घोषणा SNDRV_DEFAULT_STR	अणु [0 ... (SNDRV_CARDS-1)] = शून्य पूर्ण
#घोषणा SNDRV_DEFAULT_ENABLE	अणु 1, [1 ... (SNDRV_CARDS-1)] = 0 पूर्ण
#घोषणा SNDRV_DEFAULT_ENABLE_PNP अणु [0 ... (SNDRV_CARDS-1)] = 1 पूर्ण
#अगर_घोषित CONFIG_PNP
#घोषणा SNDRV_DEFAULT_ENABLE_ISAPNP SNDRV_DEFAULT_ENABLE_PNP
#अन्यथा
#घोषणा SNDRV_DEFAULT_ENABLE_ISAPNP SNDRV_DEFAULT_ENABLE
#पूर्ण_अगर
#घोषणा SNDRV_DEFAULT_PORT	अणु [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_PORT पूर्ण
#घोषणा SNDRV_DEFAULT_IRQ	अणु [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_IRQ पूर्ण
#घोषणा SNDRV_DEFAULT_DMA	अणु [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_DMA पूर्ण
#घोषणा SNDRV_DEFAULT_DMA_SIZE	अणु [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_DMA_SIZE पूर्ण
#घोषणा SNDRV_DEFAULT_PTR	SNDRV_DEFAULT_STR

#अगर_घोषित SNDRV_LEGACY_FIND_FREE_IOPORT
अटल दीर्घ snd_legacy_find_मुक्त_ioport(स्थिर दीर्घ *port_table, दीर्घ size)
अणु
	जबतक (*port_table != -1) अणु
		अगर (request_region(*port_table, size, "ALSA test")) अणु
			release_region(*port_table, size);
			वापस *port_table;
		पूर्ण
		port_table++;
	पूर्ण
	वापस -1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित SNDRV_LEGACY_FIND_FREE_IRQ
#समावेश <linux/पूर्णांकerrupt.h>

अटल irqवापस_t snd_legacy_empty_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक snd_legacy_find_मुक्त_irq(स्थिर पूर्णांक *irq_table)
अणु
	जबतक (*irq_table != -1) अणु
		अगर (!request_irq(*irq_table, snd_legacy_empty_irq_handler,
				 IRQF_PROBE_SHARED, "ALSA Test IRQ",
				 (व्योम *) irq_table)) अणु
			मुक्त_irq(*irq_table, (व्योम *) irq_table);
			वापस *irq_table;
		पूर्ण
		irq_table++;
	पूर्ण
	वापस -1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित SNDRV_LEGACY_FIND_FREE_DMA
अटल पूर्णांक snd_legacy_find_मुक्त_dma(स्थिर पूर्णांक *dma_table)
अणु
	जबतक (*dma_table != -1) अणु
		अगर (!request_dma(*dma_table, "ALSA Test DMA")) अणु
			मुक्त_dma(*dma_table);
			वापस *dma_table;
		पूर्ण
		dma_table++;
	पूर्ण
	वापस -1;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_INITVAL_H */
