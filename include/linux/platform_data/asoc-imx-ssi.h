<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_SSI_H
#घोषणा __MACH_SSI_H

काष्ठा snd_ac97;

बाह्य अचिन्हित अक्षर imx_ssi_fiq_start, imx_ssi_fiq_end;
बाह्य अचिन्हित दीर्घ imx_ssi_fiq_base, imx_ssi_fiq_tx_buffer, imx_ssi_fiq_rx_buffer;

काष्ठा imx_ssi_platक्रमm_data अणु
	अचिन्हित पूर्णांक flags;
#घोषणा IMX_SSI_DMA            (1 << 0)
#घोषणा IMX_SSI_USE_AC97       (1 << 1)
#घोषणा IMX_SSI_NET            (1 << 2)
#घोषणा IMX_SSI_SYN            (1 << 3)
#घोषणा IMX_SSI_USE_I2S_SLAVE  (1 << 4)
	व्योम (*ac97_reset) (काष्ठा snd_ac97 *ac97);
	व्योम (*ac97_warm_reset)(काष्ठा snd_ac97 *ac97);
पूर्ण;

बाह्य पूर्णांक mxc_set_irq_fiq(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक type);

#पूर्ण_अगर /* __MACH_SSI_H */

