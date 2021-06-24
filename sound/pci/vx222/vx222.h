<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram VX222 PCI soundcards
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __VX222_H
#घोषणा __VX222_H

#समावेश <sound/vx_core.h>

काष्ठा snd_vx222 अणु

	काष्ठा vx_core core;

	/* h/w config; क्रम PLX and क्रम DSP */
	काष्ठा pci_dev *pci;
	अचिन्हित दीर्घ port[2];

	अचिन्हित पूर्णांक regCDSP;	/* current CDSP रेजिस्टर */
	अचिन्हित पूर्णांक regCFG;	/* current CFG रेजिस्टर */
	अचिन्हित पूर्णांक regSELMIC;	/* current SELMIC reg. (क्रम VX222 Mic) */

	पूर्णांक input_level[2];	/* input level क्रम vx222 mic */
	पूर्णांक mic_level;		/* mic level क्रम vx222 mic */
पूर्ण;

#घोषणा to_vx222(x)	container_of(x, काष्ठा snd_vx222, core)

/* we use a lookup table with 148 values, see vx_mixer.c */
#घोषणा VX2_AKM_LEVEL_MAX	0x93

बाह्य स्थिर काष्ठा snd_vx_ops vx222_ops;
बाह्य स्थिर काष्ठा snd_vx_ops vx222_old_ops;

/* Offset of रेजिस्टरs with base equal to portDSP. */
#घोषणा VX_RESET_DMA_REGISTER_OFFSET    0x00000008

/* Constants used to access the INTCSR रेजिस्टर. */
#घोषणा VX_INTCSR_VALUE                 0x00000001
#घोषणा VX_PCI_INTERRUPT_MASK           0x00000040

/* Constants used to access the CDSP रेजिस्टर (0x20). */
#घोषणा VX_CDSP_TEST1_MASK              0x00000080
#घोषणा VX_CDSP_TOR1_MASK               0x00000040
#घोषणा VX_CDSP_TOR2_MASK               0x00000020
#घोषणा VX_CDSP_RESERVED0_0_MASK        0x00000010
#घोषणा VX_CDSP_CODEC_RESET_MASK        0x00000008
#घोषणा VX_CDSP_VALID_IRQ_MASK          0x00000004
#घोषणा VX_CDSP_TEST0_MASK              0x00000002
#घोषणा VX_CDSP_DSP_RESET_MASK          0x00000001

#घोषणा VX_CDSP_GPIO_OUT_MASK           0x00000060
#घोषणा VX_GPIO_OUT_BIT_OFFSET          5               // transक्रमm output to bit 0 and 1

/* Constants used to access the CFG रेजिस्टर (0x24). */
#घोषणा VX_CFG_SYNCDSP_MASK             0x00000080
#घोषणा VX_CFG_RESERVED0_0_MASK         0x00000040
#घोषणा VX_CFG_RESERVED1_0_MASK         0x00000020
#घोषणा VX_CFG_RESERVED2_0_MASK         0x00000010
#घोषणा VX_CFG_DATAIN_SEL_MASK          0x00000008     // 0 (ana), 1 (UER)
#घोषणा VX_CFG_RESERVED3_0_MASK         0x00000004
#घोषणा VX_CFG_RESERVED4_0_MASK         0x00000002
#घोषणा VX_CFG_CLOCKIN_SEL_MASK         0x00000001     // 0 (पूर्णांकernal), 1 (AES/EBU)

/* Constants used to access the STATUS रेजिस्टर (0x30). */
#घोषणा VX_STATUS_DATA_XICOR_MASK       0x00000080
#घोषणा VX_STATUS_VAL_TEST1_MASK        0x00000040
#घोषणा VX_STATUS_VAL_TEST0_MASK        0x00000020
#घोषणा VX_STATUS_RESERVED0_MASK        0x00000010
#घोषणा VX_STATUS_VAL_TOR1_MASK         0x00000008
#घोषणा VX_STATUS_VAL_TOR0_MASK         0x00000004
#घोषणा VX_STATUS_LEVEL_IN_MASK         0x00000002    // 6 dBu (0), 22 dBu (1)
#घोषणा VX_STATUS_MEMIRQ_MASK           0x00000001

#घोषणा VX_STATUS_GPIO_IN_MASK          0x0000000C
#घोषणा VX_GPIO_IN_BIT_OFFSET           0             // leave input as bit 2 and 3

/* Constants used to access the MICRO INPUT SELECT रेजिस्टर (0x40). */
#घोषणा MICRO_SELECT_INPUT_NORM        0x00
#घोषणा MICRO_SELECT_INPUT_MUTE        0x01
#घोषणा MICRO_SELECT_INPUT_LIMIT       0x02
#घोषणा MICRO_SELECT_INPUT_MASK        0x03

#घोषणा MICRO_SELECT_PREAMPLI_G_0      0x00
#घोषणा MICRO_SELECT_PREAMPLI_G_1      0x04
#घोषणा MICRO_SELECT_PREAMPLI_G_2      0x08
#घोषणा MICRO_SELECT_PREAMPLI_G_3      0x0C
#घोषणा MICRO_SELECT_PREAMPLI_MASK     0x0C
#घोषणा MICRO_SELECT_PREAMPLI_OFFSET   2

#घोषणा MICRO_SELECT_RAISE_COMPR       0x10

#घोषणा MICRO_SELECT_NOISE_T_52DB      0x00
#घोषणा MICRO_SELECT_NOISE_T_42DB      0x20
#घोषणा MICRO_SELECT_NOISE_T_32DB      0x40
#घोषणा MICRO_SELECT_NOISE_T_MASK      0x60

#घोषणा MICRO_SELECT_PHANTOM_ALIM      0x80


#पूर्ण_अगर /* __VX222_H */
