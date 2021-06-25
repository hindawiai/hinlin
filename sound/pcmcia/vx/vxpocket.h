<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram VXpocket soundcards
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __VXPOCKET_H
#घोषणा __VXPOCKET_H

#समावेश <sound/vx_core.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

काष्ठा snd_vxpocket अणु

	काष्ठा vx_core core;

	अचिन्हित दीर्घ port;

	पूर्णांक mic_level;	/* analog mic level (or boost) */

	अचिन्हित पूर्णांक regCDSP;	/* current CDSP रेजिस्टर */
	अचिन्हित पूर्णांक regDIALOG;	/* current DIALOG रेजिस्टर */

	पूर्णांक index;	/* card index */

	/* pcmcia stuff */
	काष्ठा pcmcia_device	*p_dev;
पूर्ण;

#घोषणा to_vxpocket(x)	container_of(x, काष्ठा snd_vxpocket, core)

बाह्य स्थिर काष्ठा snd_vx_ops snd_vxpocket_ops;

व्योम vx_set_mic_boost(काष्ठा vx_core *chip, पूर्णांक boost);
व्योम vx_set_mic_level(काष्ठा vx_core *chip, पूर्णांक level);

पूर्णांक vxp_add_mic_controls(काष्ठा vx_core *chip);

/* Constants used to access the CDSP रेजिस्टर (0x08). */
#घोषणा CDSP_MAGIC	0xA7	/* magic value (क्रम पढ़ो) */
/* क्रम ग_लिखो */
#घोषणा VXP_CDSP_CLOCKIN_SEL_MASK	0x80	/* 0 (पूर्णांकernal), 1 (AES/EBU) */
#घोषणा VXP_CDSP_DATAIN_SEL_MASK	0x40	/* 0 (analog), 1 (UER) */
#घोषणा VXP_CDSP_SMPTE_SEL_MASK		0x20
#घोषणा VXP_CDSP_RESERVED_MASK		0x10
#घोषणा VXP_CDSP_MIC_SEL_MASK		0x08
#घोषणा VXP_CDSP_VALID_IRQ_MASK		0x04
#घोषणा VXP_CDSP_CODEC_RESET_MASK	0x02
#घोषणा VXP_CDSP_DSP_RESET_MASK		0x01
/* VXPOCKET 240/440 */
#घोषणा P24_CDSP_MICS_SEL_MASK		0x18
#घोषणा P24_CDSP_MIC20_SEL_MASK		0x10
#घोषणा P24_CDSP_MIC38_SEL_MASK		0x08

/* Constants used to access the MEMIRQ रेजिस्टर (0x0C). */
#घोषणा P44_MEMIRQ_MASTER_SLAVE_SEL_MASK 0x08
#घोषणा P44_MEMIRQ_SYNCED_ALONE_SEL_MASK 0x04
#घोषणा P44_MEMIRQ_WCLK_OUT_IN_SEL_MASK  0x02 /* Not used */
#घोषणा P44_MEMIRQ_WCLK_UER_SEL_MASK     0x01 /* Not used */

/* Micro levels (0x0C) */

/* Constants used to access the DIALOG रेजिस्टर (0x0D). */
#घोषणा VXP_DLG_XILINX_REPROG_MASK	0x80	/* W */
#घोषणा VXP_DLG_DATA_XICOR_MASK		0x80	/* R */
#घोषणा VXP_DLG_RESERVED4_0_MASK	0x40
#घोषणा VXP_DLG_RESERVED2_0_MASK	0x20
#घोषणा VXP_DLG_RESERVED1_0_MASK	0x10
#घोषणा VXP_DLG_DMAWRITE_SEL_MASK	0x08	/* W */
#घोषणा VXP_DLG_DMAREAD_SEL_MASK	0x04	/* W */
#घोषणा VXP_DLG_MEMIRQ_MASK		0x02	/* R */
#घोषणा VXP_DLG_DMA16_SEL_MASK		0x02	/* W */
#घोषणा VXP_DLG_ACK_MEMIRQ_MASK		0x01	/* R/W */


#पूर्ण_अगर /* __VXPOCKET_H */
