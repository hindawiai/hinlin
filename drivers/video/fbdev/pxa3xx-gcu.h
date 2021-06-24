<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PXA3XX_GCU_H__
#घोषणा __PXA3XX_GCU_H__

#समावेश <linux/types.h>

/* Number of 32bit words in display list (ring buffer). */
#घोषणा PXA3XX_GCU_BUFFER_WORDS  ((256 * 1024 - 256) / 4)

/* To be increased when अवरोधing the ABI */
#घोषणा PXA3XX_GCU_SHARED_MAGIC  0x30000001

#घोषणा PXA3XX_GCU_BATCH_WORDS   8192

काष्ठा pxa3xx_gcu_shared अणु
	u32            buffer[PXA3XX_GCU_BUFFER_WORDS];

	bool           hw_running;

	अचिन्हित दीर्घ  buffer_phys;

	अचिन्हित पूर्णांक   num_words;
	अचिन्हित पूर्णांक   num_ग_लिखोs;
	अचिन्हित पूर्णांक   num_करोne;
	अचिन्हित पूर्णांक   num_पूर्णांकerrupts;
	अचिन्हित पूर्णांक   num_रुको_idle;
	अचिन्हित पूर्णांक   num_रुको_मुक्त;
	अचिन्हित पूर्णांक   num_idle;

	u32            magic;
पूर्ण;

/* Initialization and synchronization.
 * Hardware is started upon ग_लिखो(). */
#घोषणा PXA3XX_GCU_IOCTL_RESET		_IO('G', 0)
#घोषणा PXA3XX_GCU_IOCTL_WAIT_IDLE	_IO('G', 2)

#पूर्ण_अगर /* __PXA3XX_GCU_H__ */

