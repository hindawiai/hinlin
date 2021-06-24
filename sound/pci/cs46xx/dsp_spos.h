<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  The driver क्रम the Cirrus Logic's Sound Fusion CS46XX based soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

/*
 * 2002-07 Benny Sjostअक्रम benny@hosपंचांगobility.com
 */

#अगर_घोषित  CONFIG_SND_CS46XX_NEW_DSP /* hack ... */
#अगर_अघोषित __DSP_SPOS_H__
#घोषणा __DSP_SPOS_H__

#घोषणा DSP_MAX_SYMBOLS 1024
#घोषणा DSP_MAX_MODULES 64

#घोषणा DSP_CODE_BYTE_SIZE             0x00007000UL
#घोषणा DSP_PARAMETER_BYTE_SIZE        0x00003000UL
#घोषणा DSP_SAMPLE_BYTE_SIZE           0x00003800UL
#घोषणा DSP_PARAMETER_BYTE_OFFSET      0x00000000UL
#घोषणा DSP_SAMPLE_BYTE_OFFSET         0x00010000UL
#घोषणा DSP_CODE_BYTE_OFFSET           0x00020000UL

#घोषणा WIDE_INSTR_MASK       0x0040
#घोषणा WIDE_LADD_INSTR_MASK  0x0380

/* this inकाष्ठाion types
   needs to be पुनः_स्मृतिated when load
   code पूर्णांकo DSP */
क्रमागत wide_opcode अणु
	WIDE_FOR_BEGIN_LOOP = 0x20,
	WIDE_FOR_BEGIN_LOOP2,

	WIDE_COND_GOTO_ADDR = 0x30,
	WIDE_COND_GOTO_CALL,

	WIDE_TBEQ_COND_GOTO_ADDR = 0x70,
	WIDE_TBEQ_COND_CALL_ADDR,
	WIDE_TBEQ_NCOND_GOTO_ADDR,
	WIDE_TBEQ_NCOND_CALL_ADDR,
	WIDE_TBEQ_COND_GOTO1_ADDR,
	WIDE_TBEQ_COND_CALL1_ADDR,
	WIDE_TBEQ_NCOND_GOTOI_ADDR,
	WIDE_TBEQ_NCOND_CALL1_ADDR,
पूर्ण;

/* SAMPLE segment */
#घोषणा VARI_DECIMATE_BUF1       0x0000
#घोषणा WRITE_BACK_BUF1          0x0400
#घोषणा CODEC_INPUT_BUF1         0x0500
#घोषणा PCM_READER_BUF1          0x0600
#घोषणा SRC_DELAY_BUF1           0x0680
#घोषणा VARI_DECIMATE_BUF0       0x0780
#घोषणा SRC_OUTPUT_BUF1          0x07A0
#घोषणा ASYNC_IP_OUTPUT_BUFFER1  0x0A00
#घोषणा OUTPUT_SNOOP_BUFFER      0x0B00
#घोषणा SPDIFI_IP_OUTPUT_BUFFER1 0x0E00
#घोषणा SPDIFO_IP_OUTPUT_BUFFER1 0x1000
#घोषणा MIX_SAMPLE_BUF1          0x1400
#घोषणा MIX_SAMPLE_BUF2          0x2E80
#घोषणा MIX_SAMPLE_BUF3          0x2F00
#घोषणा MIX_SAMPLE_BUF4          0x2F80
#घोषणा MIX_SAMPLE_BUF5          0x3000

/* Task stack address */
#घोषणा HFG_STACK                0x066A
#घोषणा FG_STACK                 0x066E
#घोषणा BG_STACK                 0x068E

/* SCB's addresses */
#घोषणा SPOSCB_ADDR              0x070
#घोषणा BG_TREE_SCB_ADDR         0x635
#घोषणा शून्य_SCB_ADDR            0x000
#घोषणा TIMINGMASTER_SCB_ADDR    0x010
#घोषणा CODECOUT_SCB_ADDR        0x020
#घोषणा PCMREADER_SCB_ADDR       0x030
#घोषणा WRITEBACK_SCB_ADDR       0x040
#घोषणा CODECIN_SCB_ADDR         0x080
#घोषणा MASTERMIX_SCB_ADDR       0x090
#घोषणा SRCTASK_SCB_ADDR         0x0A0
#घोषणा VARIDECIMATE_SCB_ADDR    0x0B0
#घोषणा PCMSERIALIN_SCB_ADDR     0x0C0
#घोषणा FG_TASK_HEADER_ADDR      0x600
#घोषणा ASYNCTX_SCB_ADDR         0x0E0
#घोषणा ASYNCRX_SCB_ADDR         0x0F0
#घोषणा SRCTASKII_SCB_ADDR       0x100
#घोषणा OUTPUTSNOOP_SCB_ADDR     0x110
#घोषणा PCMSERIALINII_SCB_ADDR   0x120
#घोषणा SPIOWRITE_SCB_ADDR       0x130
#घोषणा REAR_CODECOUT_SCB_ADDR   0x140
#घोषणा OUTPUTSNOOPII_SCB_ADDR   0x150
#घोषणा PCMSERIALIN_PCM_SCB_ADDR 0x160
#घोषणा RECORD_MIXER_SCB_ADDR    0x170
#घोषणा REAR_MIXER_SCB_ADDR      0x180
#घोषणा CLFE_MIXER_SCB_ADDR      0x190
#घोषणा CLFE_CODEC_SCB_ADDR      0x1A0

/* hyperक्रमground SCB's*/
#घोषणा HFG_TREE_SCB             0xBA0
#घोषणा SPDIFI_SCB_INST          0xBB0
#घोषणा SPDIFO_SCB_INST          0xBC0
#घोषणा WRITE_BACK_SPB           0x0D0

/* offsets */
#घोषणा AsyncCIOFIFOPoपूर्णांकer  0xd
#घोषणा SPDIFOFIFOPoपूर्णांकer    0xd
#घोषणा SPDIFIFIFOPoपूर्णांकer    0xd
#घोषणा TCBData              0xb
#घोषणा HFGFlags             0xa
#घोषणा TCBContextBlk        0x10
#घोषणा AFGTxAccumPhi        0x4
#घोषणा SCBsubListPtr        0x9
#घोषणा SCBfuncEntryPtr      0xA
#घोषणा SRCCorPerGof         0x2
#घोषणा SRCPhiIncr6Int26Frac 0xd
#घोषणा SCBVolumeCtrl        0xe

/* conf */
#घोषणा UseASER1Input 1



/*
 * The following defines are क्रम the flags in the rsConfig01/23 रेजिस्टरs of
 * the SP.
 */

#घोषणा RSCONFIG_MODULO_SIZE_MASK               0x0000000FL
#घोषणा RSCONFIG_MODULO_16                      0x00000001L
#घोषणा RSCONFIG_MODULO_32                      0x00000002L
#घोषणा RSCONFIG_MODULO_64                      0x00000003L
#घोषणा RSCONFIG_MODULO_128                     0x00000004L
#घोषणा RSCONFIG_MODULO_256                     0x00000005L
#घोषणा RSCONFIG_MODULO_512                     0x00000006L
#घोषणा RSCONFIG_MODULO_1024                    0x00000007L
#घोषणा RSCONFIG_MODULO_4                       0x00000008L
#घोषणा RSCONFIG_MODULO_8                       0x00000009L
#घोषणा RSCONFIG_SAMPLE_SIZE_MASK               0x000000C0L
#घोषणा RSCONFIG_SAMPLE_8MONO                   0x00000000L
#घोषणा RSCONFIG_SAMPLE_8STEREO                 0x00000040L
#घोषणा RSCONFIG_SAMPLE_16MONO                  0x00000080L
#घोषणा RSCONFIG_SAMPLE_16STEREO                0x000000C0L
#घोषणा RSCONFIG_UNDERRUN_ZERO                  0x00004000L
#घोषणा RSCONFIG_DMA_TO_HOST                    0x00008000L
#घोषणा RSCONFIG_STREAM_NUM_MASK                0x00FF0000L
#घोषणा RSCONFIG_MAX_DMA_SIZE_MASK              0x1F000000L
#घोषणा RSCONFIG_DMA_ENABLE                     0x20000000L
#घोषणा RSCONFIG_PRIORITY_MASK                  0xC0000000L
#घोषणा RSCONFIG_PRIORITY_HIGH                  0x00000000L
#घोषणा RSCONFIG_PRIORITY_MEDIUM_HIGH           0x40000000L
#घोषणा RSCONFIG_PRIORITY_MEDIUM_LOW            0x80000000L
#घोषणा RSCONFIG_PRIORITY_LOW                   0xC0000000L
#घोषणा RSCONFIG_STREAM_NUM_SHIFT               16L
#घोषणा RSCONFIG_MAX_DMA_SIZE_SHIFT             24L

/* SP स्थिरants */
#घोषणा FG_INTERVAL_TIMER_PERIOD                0x0051
#घोषणा BG_INTERVAL_TIMER_PERIOD                0x0100


/* Only SP accessible रेजिस्टरs */
#घोषणा SP_ASER_COUNTDOWN 0x8040
#घोषणा SP_SPDOUT_FIFO    0x0108
#घोषणा SP_SPDIN_MI_FIFO  0x01E0
#घोषणा SP_SPDIN_D_FIFO   0x01F0
#घोषणा SP_SPDIN_STATUS   0x8048
#घोषणा SP_SPDIN_CONTROL  0x8049
#घोषणा SP_SPDIN_FIFOPTR  0x804A
#घोषणा SP_SPDOUT_STATUS  0x804C
#घोषणा SP_SPDOUT_CONTROL 0x804D
#घोषणा SP_SPDOUT_CSUV    0x808E

अटल अंतरभूत u8 _wrap_all_bits (u8 val)
अणु
	u8 wrapped;
	
	/* wrap all 8 bits */
	wrapped = 
		((val & 0x1 ) << 7) |
		((val & 0x2 ) << 5) |
		((val & 0x4 ) << 3) |
		((val & 0x8 ) << 1) |
		((val & 0x10) >> 1) |
		((val & 0x20) >> 3) |
		((val & 0x40) >> 5) |
		((val & 0x80) >> 7);

	वापस wrapped;
पूर्ण

अटल अंतरभूत व्योम cs46xx_dsp_spos_update_scb (काष्ठा snd_cs46xx * chip,
					       काष्ठा dsp_scb_descriptor * scb) 
अणु
	/* update nextSCB and subListPtr in SCB */
	snd_cs46xx_poke(chip,
			(scb->address + SCBsubListPtr) << 2,
			(scb->sub_list_ptr->address << 0x10) |
			(scb->next_scb_ptr->address));	
	scb->updated = 1;
पूर्ण

अटल अंतरभूत व्योम cs46xx_dsp_scb_set_volume (काष्ठा snd_cs46xx * chip,
					      काष्ठा dsp_scb_descriptor * scb,
					      u16 left, u16 right)
अणु
	अचिन्हित पूर्णांक val = ((0xffff - left) << 16 | (0xffff - right));

	snd_cs46xx_poke(chip, (scb->address + SCBVolumeCtrl) << 2, val);
	snd_cs46xx_poke(chip, (scb->address + SCBVolumeCtrl + 1) << 2, val);
	scb->volume_set = 1;
	scb->volume[0] = left;
	scb->volume[1] = right;
पूर्ण
#पूर्ण_अगर /* __DSP_SPOS_H__ */
#पूर्ण_अगर /* CONFIG_SND_CS46XX_NEW_DSP  */
