<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* -*- linux-c -*- *
 *
 * ALSA driver क्रम the digigram lx6464es पूर्णांकerface
 * low-level पूर्णांकerface
 *
 * Copyright (c) 2009 Tim Blechmann <tim@klingt.org>
 */

#अगर_अघोषित LX_CORE_H
#घोषणा LX_CORE_H

#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "lx_defs.h"

#घोषणा REG_CRM_NUMBER		12

काष्ठा lx6464es;

/* low-level रेजिस्टर access */

/* dsp रेजिस्टर access */
क्रमागत अणु
	eReg_BASE,
	eReg_CSM,
	eReg_CRM1,
	eReg_CRM2,
	eReg_CRM3,
	eReg_CRM4,
	eReg_CRM5,
	eReg_CRM6,
	eReg_CRM7,
	eReg_CRM8,
	eReg_CRM9,
	eReg_CRM10,
	eReg_CRM11,
	eReg_CRM12,

	eReg_ICR,
	eReg_CVR,
	eReg_ISR,
	eReg_RXHTXH,
	eReg_RXMTXM,
	eReg_RHLTXL,
	eReg_RESETDSP,

	eReg_CSUF,
	eReg_CSES,
	eReg_CRESMSB,
	eReg_CRESLSB,
	eReg_ADMACESMSB,
	eReg_ADMACESLSB,
	eReg_CONFES,

	eMaxPortLx
पूर्ण;

अचिन्हित दीर्घ lx_dsp_reg_पढ़ो(काष्ठा lx6464es *chip, पूर्णांक port);
व्योम lx_dsp_reg_ग_लिखो(काष्ठा lx6464es *chip, पूर्णांक port, अचिन्हित data);

/* plx रेजिस्टर access */
क्रमागत अणु
    ePLX_PCICR,

    ePLX_MBOX0,
    ePLX_MBOX1,
    ePLX_MBOX2,
    ePLX_MBOX3,
    ePLX_MBOX4,
    ePLX_MBOX5,
    ePLX_MBOX6,
    ePLX_MBOX7,

    ePLX_L2PCIDB,
    ePLX_IRQCS,
    ePLX_CHIPSC,

    eMaxPort
पूर्ण;

अचिन्हित दीर्घ lx_plx_reg_पढ़ो(काष्ठा lx6464es *chip, पूर्णांक port);
व्योम lx_plx_reg_ग_लिखो(काष्ठा lx6464es *chip, पूर्णांक port, u32 data);

/* rhm */
काष्ठा lx_rmh अणु
	u16	cmd_len;	/* length of the command to send (WORDs) */
	u16	stat_len;	/* length of the status received (WORDs) */
	u16	dsp_stat;	/* status type, RMP_SSIZE_XXX */
	u16	cmd_idx;	/* index of the command */
	u32	cmd[REG_CRM_NUMBER];
	u32	stat[REG_CRM_NUMBER];
पूर्ण;


/* low-level dsp access */
पूर्णांक lx_dsp_get_version(काष्ठा lx6464es *chip, u32 *rdsp_version);
पूर्णांक lx_dsp_get_घड़ी_frequency(काष्ठा lx6464es *chip, u32 *rfreq);
पूर्णांक lx_dsp_set_granularity(काष्ठा lx6464es *chip, u32 gran);
पूर्णांक lx_dsp_पढ़ो_async_events(काष्ठा lx6464es *chip, u32 *data);
पूर्णांक lx_dsp_get_mac(काष्ठा lx6464es *chip);


/* low-level pipe handling */
पूर्णांक lx_pipe_allocate(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		     पूर्णांक channels);
पूर्णांक lx_pipe_release(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture);
पूर्णांक lx_pipe_sample_count(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
			 u64 *rsample_count);
पूर्णांक lx_pipe_state(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture, u16 *rstate);
पूर्णांक lx_pipe_stop(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture);
पूर्णांक lx_pipe_start(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture);
पूर्णांक lx_pipe_छोड़ो(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture);

पूर्णांक lx_pipe_रुको_क्रम_start(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture);
पूर्णांक lx_pipe_रुको_क्रम_idle(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture);

/* low-level stream handling */
पूर्णांक lx_stream_set_क्रमmat(काष्ठा lx6464es *chip, काष्ठा snd_pcm_runसमय *runसमय,
			 u32 pipe, पूर्णांक is_capture);
पूर्णांक lx_stream_state(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		    पूर्णांक *rstate);
पूर्णांक lx_stream_sample_position(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
			      u64 *r_bytepos);

पूर्णांक lx_stream_set_state(काष्ठा lx6464es *chip, u32 pipe,
			पूर्णांक is_capture, क्रमागत stream_state_t state);

अटल अंतरभूत पूर्णांक lx_stream_start(काष्ठा lx6464es *chip, u32 pipe,
				  पूर्णांक is_capture)
अणु
	snd_prपूर्णांकdd("->lx_stream_start\n");
	वापस lx_stream_set_state(chip, pipe, is_capture, SSTATE_RUN);
पूर्ण

अटल अंतरभूत पूर्णांक lx_stream_छोड़ो(काष्ठा lx6464es *chip, u32 pipe,
				  पूर्णांक is_capture)
अणु
	snd_prपूर्णांकdd("->lx_stream_pause\n");
	वापस lx_stream_set_state(chip, pipe, is_capture, SSTATE_PAUSE);
पूर्ण

अटल अंतरभूत पूर्णांक lx_stream_stop(काष्ठा lx6464es *chip, u32 pipe,
				 पूर्णांक is_capture)
अणु
	snd_prपूर्णांकdd("->lx_stream_stop\n");
	वापस lx_stream_set_state(chip, pipe, is_capture, SSTATE_STOP);
पूर्ण

/* low-level buffer handling */
पूर्णांक lx_buffer_ask(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		  u32 *r_needed, u32 *r_मुक्तd, u32 *size_array);
पूर्णांक lx_buffer_give(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		   u32 buffer_size, u32 buf_address_lo, u32 buf_address_hi,
		   u32 *r_buffer_index);
पूर्णांक lx_buffer_मुक्त(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		   u32 *r_buffer_size);
पूर्णांक lx_buffer_cancel(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		     u32 buffer_index);

/* low-level gain/peak handling */
पूर्णांक lx_level_unmute(काष्ठा lx6464es *chip, पूर्णांक is_capture, पूर्णांक unmute);
पूर्णांक lx_level_peaks(काष्ठा lx6464es *chip, पूर्णांक is_capture, पूर्णांक channels,
		   u32 *r_levels);


/* पूर्णांकerrupt handling */
irqवापस_t lx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t lx_thपढ़ोed_irq(पूर्णांक irq, व्योम *dev_id);
व्योम lx_irq_enable(काष्ठा lx6464es *chip);
व्योम lx_irq_disable(काष्ठा lx6464es *chip);


/* Stream Format Header Defines (क्रम LIN and IEEE754) */
#घोषणा HEADER_FMT_BASE		HEADER_FMT_BASE_LIN
#घोषणा HEADER_FMT_BASE_LIN	0xFED00000
#घोषणा HEADER_FMT_BASE_FLOAT	0xFAD00000
#घोषणा HEADER_FMT_MONO		0x00000080 /* bit 23 in header_lo. WARNING: old
					    * bit 22 is ignored in भग्न
					    * क्रमmat */
#घोषणा HEADER_FMT_INTEL	0x00008000
#घोषणा HEADER_FMT_16BITS	0x00002000
#घोषणा HEADER_FMT_24BITS	0x00004000
#घोषणा HEADER_FMT_UPTO11	0x00000200 /* frequency is less or equ. to 11k.
					    * */
#घोषणा HEADER_FMT_UPTO32	0x00000100 /* frequency is over 11k and less
					    * then 32k.*/


#घोषणा BIT_FMP_HEADER          23
#घोषणा BIT_FMP_SD              22
#घोषणा BIT_FMP_MULTICHANNEL    19

#घोषणा START_STATE             1
#घोषणा PAUSE_STATE             0





/* from PcxAll_e.h */
/* Start/Pause condition क्रम pipes (PCXStartPipe, PCXPausePipe) */
#घोषणा START_PAUSE_IMMEDIATE           0
#घोषणा START_PAUSE_ON_SYNCHRO          1
#घोषणा START_PAUSE_ON_TIME_CODE        2


/* Pipe / Stream state */
#घोषणा START_STATE             1
#घोषणा PAUSE_STATE             0

अटल अंतरभूत व्योम unpack_poपूर्णांकer(dma_addr_t ptr, u32 *r_low, u32 *r_high)
अणु
	*r_low = (u32)(ptr & 0xffffffff);
#अगर BITS_PER_LONG == 32
	*r_high = 0;
#अन्यथा
	*r_high = (u32)((u64)ptr>>32);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* LX_CORE_H */
